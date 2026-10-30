// Tartarus, second pass (slice tartarus2): the rest of the Y band 0x421770-0x45A3A4 that the tartarus and social_map
// slices left -- the mini-map task ("y_smap draw proc": its update / create / destroy and file loads), the party
// members' AI ("npc think proc": follow, explore, skirmish, support skills; "treasure free proc"), the task creators
// of the enemy band ("ene think proc", "y_ene_dead effect proc", "smap_symbol_dirp"), the stratum-parts helpers, the
// Kyoto NPCs ("Kyoto_NpcModeRead proc", "Kyoto_NpcThink proc", "y wait task") and the time-limit creator. The
// stratum-parts update itself is in tartarus2_stparts.cpp. docs/ANALYSIS/27_unmapped_bands.md section 8; records in
// tartarus2.h.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass adds the role of each function above it, comments on the main blocks (`// 0x00xxxxxx` names
// the original basic block a C++ block comes from) and named record offsets (tartarus2.h, namespace tart2: constexpr
// values equal to the instructions' offsets); it changes no statement. Names in [brackets] are proposals (ADR-0009),
// not code identifiers. Kept as the original does: the debug printf of the mini-map ("len = %f\n"), the jump tables'
// out-of-table fallback (the dispatch table, as the recompiled body).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/tartarus2.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_Battle_CreateBattleTask_001d8b00(p3fes::EEContext&);
void fn_K_Battle_FindTaskOfUnit_001d8d80(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_FldFrame_CtlGetXGrid_001ad910(p3fes::EEContext&);
void fn_K_FldFrame_CtlGetZGrid_001ad920(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0(p3fes::EEContext&);
void fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630(p3fes::EEContext&);
void fn_Y_Kyoto_CreateWaitTask_00459f60(p3fes::EEContext&);
void fn_Y_Kyoto_UpdateKyotoNpcModeReadTask_004575e0(p3fes::EEContext&);
void fn_Y_Kyoto_UpdateKyotoNpcThinkTask_00457a40(p3fes::EEContext&);
void fn_Y_Kyoto_UpdateWaitTask_00459e80(p3fes::EEContext&);
void fn_Y_LMap_CreateBoxfillTasks_004229d0(p3fes::EEContext&);
void fn_Y_Npc_CreateNpcThinkTask_00431670(p3fes::EEContext&);
void fn_Y_Npc_CreateTreasureFreeTask_0043c690(p3fes::EEContext&);
void fn_Y_Npc_UpdateNpcThinkTask_004312b0(p3fes::EEContext&);
void fn_Y_Npc_UpdateTreasureFreeTask_0043c500(p3fes::EEContext&);
void fn_Y_SMap_CreateSmapDrawTask_00429d40(p3fes::EEContext&);
void fn_Y_SMap_CreateSmapMaskDrawTask_00431110(p3fes::EEContext&);
void fn_Y_SMap_CreateStaireDispTask_00430180(p3fes::EEContext&);
void fn_Y_SMap_UpdateSmapDrawTask_004281f0(p3fes::EEContext&);
void fn_Y_Stratum_CreateEneDeadEffectTask_004542c0(p3fes::EEContext&);
void fn_Y_Stratum_CreateEneThinkTask_0044ad20(p3fes::EEContext&);
void fn_Y_Stratum_CreateSmapSymbolDirpTask_004560d0(p3fes::EEContext&);
void fn_Y_Stratum_CreateStratumPartsTask_00447e70(p3fes::EEContext&);
void fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_datUnitCreatePc_002ff340(p3fes::EEContext&);
void fn_datUnitDestroyGenus_002ff760(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_drawIm2DIndexedTriList_002699d0(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromHeader_0035bb40(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_scrSetUserData_0035c1a0(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1120C0_001120c0(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16F490_0016f490(p3fes::EEContext&);
void fn_sub_170A40_00170a40(p3fes::EEContext&);
void fn_sub_170AB0_00170ab0(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_173300_00173300(p3fes::EEContext&);
void fn_sub_173380_00173380(p3fes::EEContext&);
void fn_sub_17B500_0017b500(p3fes::EEContext&);
void fn_sub_17B5B0_0017b5b0(p3fes::EEContext&);
void fn_sub_17B660_0017b660(p3fes::EEContext&);
void fn_sub_17B860_0017b860(p3fes::EEContext&);
void fn_sub_17BE10_0017be10(p3fes::EEContext&);
void fn_sub_1831E0_001831e0(p3fes::EEContext&);
void fn_sub_18C0C0_0018c0c0(p3fes::EEContext&);
void fn_sub_18EB30_0018eb30(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_1A0040_001a0040(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);
void fn_sub_1A5320_001a5320(p3fes::EEContext&);
void fn_sub_1A56B0_001a56b0(p3fes::EEContext&);
void fn_sub_1A56C0_001a56c0(p3fes::EEContext&);
void fn_sub_1A56D0_001a56d0(p3fes::EEContext&);
void fn_sub_1A5700_001a5700(p3fes::EEContext&);
void fn_sub_1A57A0_001a57a0(p3fes::EEContext&);
void fn_sub_1A5AA0_001a5aa0(p3fes::EEContext&);
void fn_sub_1AAA20_001aaa20(p3fes::EEContext&);
void fn_sub_1AD940_001ad940(p3fes::EEContext&);
void fn_sub_1AFA20_001afa20(p3fes::EEContext&);
void fn_sub_1AFF70_001aff70(p3fes::EEContext&);
void fn_sub_1B0020_001b0020(p3fes::EEContext&);
void fn_sub_1B00C0_001b00c0(p3fes::EEContext&);
void fn_sub_1B01B0_001b01b0(p3fes::EEContext&);
void fn_sub_1B01D0_001b01d0(p3fes::EEContext&);
void fn_sub_1B0220_001b0220(p3fes::EEContext&);
void fn_sub_1B0230_001b0230(p3fes::EEContext&);
void fn_sub_1B0240_001b0240(p3fes::EEContext&);
void fn_sub_1B0250_001b0250(p3fes::EEContext&);
void fn_sub_1B0260_001b0260(p3fes::EEContext&);
void fn_sub_1BF220_001bf220(p3fes::EEContext&);
void fn_sub_1C6450_001c6450(p3fes::EEContext&);
void fn_sub_1C6720_001c6720(p3fes::EEContext&);
void fn_sub_1C7130_001c7130(p3fes::EEContext&);
void fn_sub_1C7160_001c7160(p3fes::EEContext&);
void fn_sub_1C7270_001c7270(p3fes::EEContext&);
void fn_sub_1CD670_001cd670(p3fes::EEContext&);
void fn_sub_1D0110_001d0110(p3fes::EEContext&);
void fn_sub_1D22A0_001d22a0(p3fes::EEContext&);
void fn_sub_1D3810_001d3810(p3fes::EEContext&);
void fn_sub_1D8C60_001d8c60(p3fes::EEContext&);
void fn_sub_1D8E60_001d8e60(p3fes::EEContext&);
void fn_sub_1DDD30_001ddd30(p3fes::EEContext&);
void fn_sub_1DDE00_001dde00(p3fes::EEContext&);
void fn_sub_1DED40_001ded40(p3fes::EEContext&);
void fn_sub_1E1360_001e1360(p3fes::EEContext&);
void fn_sub_1E13C0_001e13c0(p3fes::EEContext&);
void fn_sub_269690_00269690(p3fes::EEContext&);
void fn_sub_2699A0_002699a0(p3fes::EEContext&);
void fn_sub_269A10_00269a10(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_318540_00318540(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_31C1D0_0031c1d0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3BB010_003bb010(p3fes::EEContext&);
void fn_sub_422C10_00422c10(p3fes::EEContext&);
void fn_sub_422C30_00422c30(p3fes::EEContext&);
void fn_sub_422CD0_00422cd0(p3fes::EEContext&);
void fn_sub_423FE0_00423fe0(p3fes::EEContext&);
void fn_sub_429C60_00429c60(p3fes::EEContext&);
void fn_sub_429E80_00429e80(p3fes::EEContext&);
void fn_sub_429EF0_00429ef0(p3fes::EEContext&);
void fn_sub_429FE0_00429fe0(p3fes::EEContext&);
void fn_sub_42A0D0_0042a0d0(p3fes::EEContext&);
void fn_sub_42A180_0042a180(p3fes::EEContext&);
void fn_sub_42A230_0042a230(p3fes::EEContext&);
void fn_sub_42A310_0042a310(p3fes::EEContext&);
void fn_sub_42A3F0_0042a3f0(p3fes::EEContext&);
void fn_sub_42A4A0_0042a4a0(p3fes::EEContext&);
void fn_sub_42A550_0042a550(p3fes::EEContext&);
void fn_sub_42AA40_0042aa40(p3fes::EEContext&);
void fn_sub_42AC60_0042ac60(p3fes::EEContext&);
void fn_sub_42ADB0_0042adb0(p3fes::EEContext&);
void fn_sub_42B050_0042b050(p3fes::EEContext&);
void fn_sub_42B540_0042b540(p3fes::EEContext&);
void fn_sub_42BA50_0042ba50(p3fes::EEContext&);
void fn_sub_42BC10_0042bc10(p3fes::EEContext&);
void fn_sub_42BD80_0042bd80(p3fes::EEContext&);
void fn_sub_42BFD0_0042bfd0(p3fes::EEContext&);
void fn_sub_42C0A0_0042c0a0(p3fes::EEContext&);
void fn_sub_42CD80_0042cd80(p3fes::EEContext&);
void fn_sub_42CFC0_0042cfc0(p3fes::EEContext&);
void fn_sub_42DD90_0042dd90(p3fes::EEContext&);
void fn_sub_42EA60_0042ea60(p3fes::EEContext&);
void fn_sub_42F440_0042f440(p3fes::EEContext&);
void fn_sub_42FD80_0042fd80(p3fes::EEContext&);
void fn_sub_430220_00430220(p3fes::EEContext&);
void fn_sub_430270_00430270(p3fes::EEContext&);
void fn_sub_4302A0_004302a0(p3fes::EEContext&);
void fn_sub_4302B0_004302b0(p3fes::EEContext&);
void fn_sub_430630_00430630(p3fes::EEContext&);
void fn_sub_430A40_00430a40(p3fes::EEContext&);
void fn_sub_4311F0_004311f0(p3fes::EEContext&);
void fn_sub_431630_00431630(p3fes::EEContext&);
void fn_sub_431880_00431880(p3fes::EEContext&);
void fn_sub_431AA0_00431aa0(p3fes::EEContext&);
void fn_sub_432050_00432050(p3fes::EEContext&);
void fn_sub_432600_00432600(p3fes::EEContext&);
void fn_sub_432BB0_00432bb0(p3fes::EEContext&);
void fn_sub_433160_00433160(p3fes::EEContext&);
void fn_sub_4332F0_004332f0(p3fes::EEContext&);
void fn_sub_4333D0_004333d0(p3fes::EEContext&);
void fn_sub_4334D0_004334d0(p3fes::EEContext&);
void fn_sub_433810_00433810(p3fes::EEContext&);
void fn_sub_4339D0_004339d0(p3fes::EEContext&);
void fn_sub_433DE0_00433de0(p3fes::EEContext&);
void fn_sub_4343D0_004343d0(p3fes::EEContext&);
void fn_sub_4344F0_004344f0(p3fes::EEContext&);
void fn_sub_434770_00434770(p3fes::EEContext&);
void fn_sub_434920_00434920(p3fes::EEContext&);
void fn_sub_434C90_00434c90(p3fes::EEContext&);
void fn_sub_434D30_00434d30(p3fes::EEContext&);
void fn_sub_434E60_00434e60(p3fes::EEContext&);
void fn_sub_434F60_00434f60(p3fes::EEContext&);
void fn_sub_435060_00435060(p3fes::EEContext&);
void fn_sub_4350E0_004350e0(p3fes::EEContext&);
void fn_sub_435260_00435260(p3fes::EEContext&);
void fn_sub_4352E0_004352e0(p3fes::EEContext&);
void fn_sub_435370_00435370(p3fes::EEContext&);
void fn_sub_4353F0_004353f0(p3fes::EEContext&);
void fn_sub_435440_00435440(p3fes::EEContext&);
void fn_sub_435660_00435660(p3fes::EEContext&);
void fn_sub_435810_00435810(p3fes::EEContext&);
void fn_sub_4359F0_004359f0(p3fes::EEContext&);
void fn_sub_435C00_00435c00(p3fes::EEContext&);
void fn_sub_437E00_00437e00(p3fes::EEContext&);
void fn_sub_437E20_00437e20(p3fes::EEContext&);
void fn_sub_437E80_00437e80(p3fes::EEContext&);
void fn_sub_438010_00438010(p3fes::EEContext&);
void fn_sub_439400_00439400(p3fes::EEContext&);
void fn_sub_439520_00439520(p3fes::EEContext&);
void fn_sub_439F60_00439f60(p3fes::EEContext&);
void fn_sub_43A0B0_0043a0b0(p3fes::EEContext&);
void fn_sub_43A1A0_0043a1a0(p3fes::EEContext&);
void fn_sub_43A230_0043a230(p3fes::EEContext&);
void fn_sub_43A2F0_0043a2f0(p3fes::EEContext&);
void fn_sub_43A960_0043a960(p3fes::EEContext&);
void fn_sub_43A9D0_0043a9d0(p3fes::EEContext&);
void fn_sub_43B980_0043b980(p3fes::EEContext&);
void fn_sub_43BC20_0043bc20(p3fes::EEContext&);
void fn_sub_43BDA0_0043bda0(p3fes::EEContext&);
void fn_sub_43BF50_0043bf50(p3fes::EEContext&);
void fn_sub_43C180_0043c180(p3fes::EEContext&);
void fn_sub_43C340_0043c340(p3fes::EEContext&);
void fn_sub_43C660_0043c660(p3fes::EEContext&);
void fn_sub_43C730_0043c730(p3fes::EEContext&);
void fn_sub_43C7A0_0043c7a0(p3fes::EEContext&);
void fn_sub_43C7F0_0043c7f0(p3fes::EEContext&);
void fn_sub_43C910_0043c910(p3fes::EEContext&);
void fn_sub_447AD0_00447ad0(p3fes::EEContext&);
void fn_sub_449ED0_00449ed0(p3fes::EEContext&);
void fn_sub_449FA0_00449fa0(p3fes::EEContext&);
void fn_sub_44A990_0044a990(p3fes::EEContext&);
void fn_sub_44ACF0_0044acf0(p3fes::EEContext&);
void fn_sub_44E530_0044e530(p3fes::EEContext&);
void fn_sub_44F120_0044f120(p3fes::EEContext&);
void fn_sub_44F170_0044f170(p3fes::EEContext&);
void fn_sub_44F1C0_0044f1c0(p3fes::EEContext&);
void fn_sub_452F70_00452f70(p3fes::EEContext&);
void fn_sub_4532D0_004532d0(p3fes::EEContext&);
void fn_sub_453490_00453490(p3fes::EEContext&);
void fn_sub_454290_00454290(p3fes::EEContext&);
void fn_sub_455E00_00455e00(p3fes::EEContext&);
void fn_sub_456050_00456050(p3fes::EEContext&);
void fn_sub_4561D0_004561d0(p3fes::EEContext&);
void fn_sub_4561F0_004561f0(p3fes::EEContext&);
void fn_sub_456400_00456400(p3fes::EEContext&);
void fn_sub_456410_00456410(p3fes::EEContext&);
void fn_sub_4564E0_004564e0(p3fes::EEContext&);
void fn_sub_456530_00456530(p3fes::EEContext&);
void fn_sub_456580_00456580(p3fes::EEContext&);
void fn_sub_4565D0_004565d0(p3fes::EEContext&);
void fn_sub_456620_00456620(p3fes::EEContext&);
void fn_sub_456670_00456670(p3fes::EEContext&);
void fn_sub_456A90_00456a90(p3fes::EEContext&);
void fn_sub_456EA0_00456ea0(p3fes::EEContext&);
void fn_sub_457410_00457410(p3fes::EEContext&);
void fn_sub_457470_00457470(p3fes::EEContext&);
void fn_sub_457980_00457980(p3fes::EEContext&);
void fn_sub_458600_00458600(p3fes::EEContext&);
void fn_sub_458850_00458850(p3fes::EEContext&);
void fn_sub_458870_00458870(p3fes::EEContext&);
void fn_sub_458890_00458890(p3fes::EEContext&);
void fn_sub_458920_00458920(p3fes::EEContext&);
void fn_sub_458930_00458930(p3fes::EEContext&);
void fn_sub_4589D0_004589d0(p3fes::EEContext&);
void fn_sub_4589E0_004589e0(p3fes::EEContext&);
void fn_sub_458A80_00458a80(p3fes::EEContext&);
void fn_sub_458B00_00458b00(p3fes::EEContext&);
void fn_sub_458B60_00458b60(p3fes::EEContext&);
void fn_sub_458BB0_00458bb0(p3fes::EEContext&);
void fn_sub_458CB0_00458cb0(p3fes::EEContext&);
void fn_sub_459790_00459790(p3fes::EEContext&);
void fn_sub_459D60_00459d60(p3fes::EEContext&);
void fn_sub_459E00_00459e00(p3fes::EEContext&);
void fn_sub_459F30_00459f30(p3fes::EEContext&);
void fn_sub_45A220_0045a220(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1260_004d1260(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace tart2;  // the named record offsets (tartarus2.h)

// 0x004281F0 Y_SMap_UpdateSmapDrawTask -- 6756 bytes; frame 0x180: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_UpdateSmapDrawTask] (bands.sym) The update of the Tartarus mini-map task "y_smap draw proc" ($a0 = the
// task, work = task +60, 2996 bytes, see the group doc); returns $v0 = 0 (stay) or -1 (state 19: this scene has no
// map, the task ends). Every frame it first clears the party marks' drawn flags (+2360..+2362). While the map is
// hidden (+2148 == 0) and the map is up (state 14 = random floor, 18 = fixed map) it hides everything -- every cell
// / layer tmx task (+336 = 1), the hero's direction arrow (sub_456400(+2200, 0)), the four frame corners (sprite +24
// = 255) and the stair icon (sub_4302A0) -- and returns 0; in the loading states it carries on hidden. While shown
// it makes the frame corners visible (+24 = 0) and runs the state +0 through the jump table 0x7BC340: 0 picks the
// map kind (sub_1A01C0 [K_Scene_IsTartarus]: random floor (K_Scene_IsRandomFloor) or fixed Tartarus floor
// (sub_1A02C0) -> 1, any other Tartarus scene (majors 30..38) -> 15, else 19); 1 -> 2 -> the mask task (layout 0) ->
// 13; 3..11 a chain polling nine texture requests (+2164..) into +40.. and destroying the files +4.. (nothing in
// this update enters 3: inf. a leftover) -> 12, which adds the background box-fill and the mask -> 13; 13 sets up
// the random-floor map (room tmx tasks sub_42BD80 [Y_SMap_CreateRoomTmx], the stair icon task, the direction arrow
// sub_42BFD0 [Y_SMap_CreateSymbol], the first positions of the party / shadow / treasure / exit marks, the stairs
// sub_42FD80 [Y_SMap_FindStairs], the frame sub_430630 [Y_SMap_CreateFrame], gp-0x4614 = 1) -> 14; 14 is the
// per-frame random-floor draw (seen cells sub_42A550 [Y_SMap_MarkSeen] for each party member, the stairs-found and
// exit-reached flags gp-0x462C / gp-0x4628, the 11 x 11 cells around the hero with their marks sub_42C0A0 /
// sub_42CFC0 / sub_42DD90 / sub_42EA60 / sub_42F440, the stair icon, the sparkles sub_42CD80); 15 requests the fixed
// map's files (sub_42AA40) -> 16 waits for them, makes the textures (sub_42AC60) and the background -> 17 creates
// the layers (sub_42BA50 [Y_SMap_CreateLayers]), the mask (layout 1), the arrow and layers (sub_42BC10
// [Y_SMap_SetUpSymbol]), the frame -> 18 is the per-frame fixed-map draw (layers shown and placed sub_42ADB0
// [Y_SMap_PlaceLayers], party marks sub_42B050, shadow marks sub_42B540). Every state that returns 0 ends in a debug
// print: with bit 0x10 of the u16 at 0x7E0988 set it prints printf("len = %f\n", |{0, 0, 0}|) (sub_4C6AC0, the
// vector length; always 0.0).
void Y_SMap_UpdateSmapDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x004281f0: work = task +60; clear the party marks' drawn flags +2360..+2362; branch on the shown flag +2148
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
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
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(s1, a0, kTaskWork);
    sb(zero, s1, kSmapWorkPcDrawn1);
    sb(zero, s1, kSmapWorkPcDrawn2);
    sb(zero, s1, kSmapWorkPcDrawn3);
    lb(v0, s1, kSmapWorkShown);
    if (v0 != 0) {
        // 0x00428354: map shown: the four frame corner sprites (+76 + 4 i) get +24 = 0 (drawn), then the state dispatch
        charge(ctx, 3);
        v1 = 0;
        for (;;) {
            // 0x0042837c
            charge(ctx, 3);
            v0 = slti(v1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00428360
            charge(ctx, 5);
            v0 = sll(v1, 2);
            v0 = addu(s1, v0);
            lw(v0, v0, kSmapWorkCorners);
            if (v0 != 0) {
                // 0x00428374
                charge(ctx, 1);
                sb(zero, v0, kSmapSprFade);
            }
            // 0x00428378
            charge(ctx, 1);
            v1 = addiu(v1, 1);
        }
    L_00428388:
        charge(ctx, 4);
        lb(v0, s1, kSmapWorkState);
        at = sltiu(v0, 20);
        if (at != 0) {
            // 0x00428398: the state +0 (0..19; 20 and above skip to the debug print) through the jump table 0x7BC340
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -15552);  // &0x7BC340
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x4283B4u:  // table[0]
                // 0x004283b4: state 0: default 19 (no map); sub_1A01C0 [K_Scene_IsTartarus] == 1 picks the map kind
                charge(ctx, 7);
                v0 = 19;
                sb(v0, s1, kSmapWorkState);
                jal(ctx, 0x4283BCu, gen::fn_sub_1A01C0_001a01c0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x004283d0: a Tartarus scene: random floor (K_Scene_IsRandomFloor) -> 1, else fixed Tartarus floor (sub_1A02C0) -> 1
                    charge(ctx, 5);
                    jal(ctx, 0x4283D0u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x004283f0
                        charge(ctx, 5);
                        jal(ctx, 0x4283F0u, gen::fn_sub_1A02C0_001a02c0);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x00428410: any other Tartarus scene (majors 30..38): the hand-drawn map from smap/sMMM_NNN.tmx -> state 15
                            charge(ctx, 4);
                            v0 = 15;
                            sb(v0, s1, kSmapWorkState);
                        } else {
                            // 0x00428404
                            charge(ctx, 3);
                            sb(v1, s1, kSmapWorkState);
                        }
                    } else {
                        // 0x004283e4
                        charge(ctx, 3);
                        sb(v1, s1, kSmapWorkState);
                    }
                }
            L_00429bcc:
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2440);  // 0x7E0988
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    // 0x00429be0: debug (bit 0x10 of the u16 at 0x7E0988): printf("len = %f\n") of the length (sub_4C6AC0) of the zero vector at sp+0x128
                    charge(ctx, 14);
                    sw(zero, sp, 0x128);
                    sw(zero, sp, 0x12C);
                    sw(zero, sp, 0x130);
                    a0 = addiu(sp, 0x128);
                    jal(ctx, 0x429BF0u, gen::fn_sub_4C6AC0_004c6ac0);
                    mov_s(f12, f0);
                    jal(ctx, 0x429BFCu, gen::fn_fptodp_00530da0);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, 17496);  // "len = %f\n"
                    a1 = v0;
                    jal(ctx, 0x429C10u, gen::fn_printf_005225a8);
                }
                // 0x00429c18: return 0 (stay)
                charge(ctx, 1);
                v0 = 0;
                break;
            case 0x428420u:  // table[1]
                // 0x00428420: state 1: -> 2 and fall into state 2
                charge(ctx, 2);
                v0 = 2;
                sb(v0, s1, kSmapWorkState);
            L_00428428:
                charge(ctx, 12);
                a0 = s4;
                ldr(a1, s1, kSmapWorkCornerX);
                ldl(a1, s1, kSmapWorkCornerEnd);
                lb(a2, s1, kSmapWorkViewCells);
                a3 = 0;
                jal(ctx, 0x42843Cu, gen::fn_Y_SMap_CreateSmapMaskDrawTask_00431110);
                sw(v0, s1, kSmapWorkMaskTask);
                v0 = 13;
                sb(v0, s1, kSmapWorkState);
                goto L_00429bcc;
            case 0x428428u:  // table[2]
                goto L_00428428;
            case 0x428458u:  // table[3]
                // 0x00428458: state 3 (no path enters it): texture request +2164 polled (sub_10C3A0) into +40; when done destroy file +4 -> 4
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq0);
                a1 = addiu(sp, 0x17C);
                a2 = 0;
                jal(ctx, 0x428464u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex0);
                lw(v0, sp, 0x17C);
                if (v0 != 0) {
                    // 0x0042847c
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile0);
                    jal(ctx, 0x428480u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 4;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428498u:  // table[4]
                // 0x00428498: state 4: texture request +2168 -> +44; when done destroy file +8 -> 5
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq1);
                a1 = addiu(sp, 0x178);
                a2 = 0;
                jal(ctx, 0x4284A4u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex1);
                lw(v0, sp, 0x178);
                if (v0 != 0) {
                    // 0x004284bc
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile1);
                    jal(ctx, 0x4284C0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 5;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x4284D8u:  // table[5]
                // 0x004284d8: state 5: texture request +2172 -> +48; destroy file +12 -> 6
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq2);
                a1 = addiu(sp, 0x174);
                a2 = 0;
                jal(ctx, 0x4284E4u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex2);
                lw(v0, sp, 0x174);
                if (v0 != 0) {
                    // 0x004284fc
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile2);
                    jal(ctx, 0x428500u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 6;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428518u:  // table[6]
                // 0x00428518: state 6: texture request +2176 -> +52; destroy file +16 -> 7
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq3);
                a1 = addiu(sp, 0x170);
                a2 = 0;
                jal(ctx, 0x428524u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex3);
                lw(v0, sp, 0x170);
                if (v0 != 0) {
                    // 0x0042853c
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile3);
                    jal(ctx, 0x428540u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 7;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428558u:  // table[7]
                // 0x00428558: state 7: texture request +2180 -> +56; destroy file +20 -> 8
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq4);
                a1 = addiu(sp, 0x16C);
                a2 = 0;
                jal(ctx, 0x428564u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex4);
                lw(v0, sp, 0x16C);
                if (v0 != 0) {
                    // 0x0042857c
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile4);
                    jal(ctx, 0x428580u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 8;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428598u:  // table[8]
                // 0x00428598: state 8: texture request +2184 -> +60; destroy file +24 -> 9
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq5);
                a1 = addiu(sp, 0x168);
                a2 = 0;
                jal(ctx, 0x4285A4u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex5);
                lw(v0, sp, 0x168);
                if (v0 != 0) {
                    // 0x004285bc
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile5);
                    jal(ctx, 0x4285C0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 9;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x4285D8u:  // table[9]
                // 0x004285d8: state 9: texture request +2188 -> +64; destroy file +28 -> 10
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq6);
                a1 = addiu(sp, 0x164);
                a2 = 0;
                jal(ctx, 0x4285E4u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex6);
                lw(v0, sp, 0x164);
                if (v0 != 0) {
                    // 0x004285fc
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile6);
                    jal(ctx, 0x428600u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 10;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428618u:  // table[10]
                // 0x00428618: state 10: texture request +2192 -> +68; destroy file +32 -> 11
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq7);
                a1 = addiu(sp, 0x160);
                a2 = 0;
                jal(ctx, 0x428624u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex7);
                lw(v0, sp, 0x160);
                if (v0 != 0) {
                    // 0x0042863c
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile7);
                    jal(ctx, 0x428640u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 11;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428658u:  // table[11]
                // 0x00428658: state 11: texture request +2196 -> +72; destroy file +36 -> 12
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkTexReq8);
                a1 = addiu(sp, 0x15C);
                a2 = 0;
                jal(ctx, 0x428664u, gen::fn_sub_10C3A0_0010c3a0);
                sw(v0, s1, kSmapWorkTex8);
                lw(v0, sp, 0x15C);
                if (v0 != 0) {
                    // 0x0042867c
                    charge(ctx, 7);
                    lw(a0, s1, kSmapWorkFile8);
                    jal(ctx, 0x428680u, gen::fn_H_Cdvd_Destroy_00100ec0);
                    v0 = 12;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x428698u:  // table[12]
                // 0x00428698: state 12: the background: box size {126, 126} at sp+0x108; the old box-fill pointer +2848 dropped (not destroyed)
                charge(ctx, 6);
                v0 = 126;
                sw(v0, sp, 0x108);
                sw(v0, sp, 0x10C);
                lw(v0, s1, kSmapWorkBoxfill);
                if (v0 != 0) {
                    // 0x004286b0
                    charge(ctx, 1);
                    sw(zero, s1, kSmapWorkBoxfill);
                }
                // 0x004286b4: box-fill task (Y_LMap_CreateBoxfillTasks(task, corner, 2)) -> +2848, placed (sub_422C30), sub_422C10(10), sub_422CD0(1); the mask task (layout 0) -> +2852; -> 13
                charge(ctx, 33);
                a0 = s4;
                ldr(a1, s1, kSmapWorkCornerX);
                ldl(a1, s1, kSmapWorkCornerEnd);
                a2 = 2;
                jal(ctx, 0x4286C4u, gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                sw(v0, s1, kSmapWorkBoxfill);
                a0 = v0;
                ldr(a1, s1, kSmapWorkCornerX);
                ldl(a1, s1, kSmapWorkCornerEnd);
                a2 = addiu(sp, 0x100);
                jal(ctx, 0x4286E0u, gen::fn_sub_422C30_00422c30);
                lw(a0, s1, kSmapWorkBoxfill);
                a1 = 10;
                jal(ctx, 0x4286F0u, gen::fn_sub_422C10_00422c10);
                lw(a0, s1, kSmapWorkBoxfill);
                a1 = 1;
                jal(ctx, 0x428700u, gen::fn_sub_422CD0_00422cd0);
                a0 = s4;
                ldr(a1, s1, kSmapWorkCornerX);
                ldl(a1, s1, kSmapWorkCornerEnd);
                lb(a2, s1, kSmapWorkViewCells);
                a3 = 0;
                jal(ctx, 0x42871Cu, gen::fn_Y_SMap_CreateSmapMaskDrawTask_00431110);
                sw(v0, s1, kSmapWorkMaskTask);
                v0 = 13;
                sb(v0, s1, kSmapWorkState);
                goto L_00429bcc;
            case 0x428738u:  // table[13]
                // 0x00428738: state 13 (random-floor set-up): the room tmx tasks (sub_42BD80 [Y_SMap_CreateRoomTmx])
                charge(ctx, 6);
                a0 = s4;
                jal(ctx, 0x42873Cu, gen::fn_sub_42BD80_0042bd80);
                lw(v0, s1, kSmapWorkStairTask);
                if (v0 != 0) {
                    // 0x00428750
                    charge(ctx, 1);
                    sw(zero, s1, kSmapWorkStairTask);
                }
                // 0x00428754: the stair icon task (Y_SMap_CreateStaireDispTask) -> +2844; the direction arrow (sub_42BFD0 [Y_SMap_CreateSymbol])
                charge(ctx, 10);
                a0 = s4;
                jal(ctx, 0x428758u, gen::fn_Y_SMap_CreateStaireDispTask_00430180);
                sw(v0, s1, kSmapWorkStairTask);
                a0 = s4;
                jal(ctx, 0x428768u, gen::fn_sub_42BFD0_0042bfd0);
                s2 = 0;
                for (;;) {
                    // 0x004288f4: loop m = 0..2 over party members m + 1
                    charge(ctx, 3);
                    v0 = slti(s2, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042877c
                    charge(ctx, 10);
                    a0 = 0;
                    v0 = sll(s2, 3);
                    v0 = subu(v0, s2);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    v1 = addu(v0, v1);
                    lw(v0, v1, kSmapPc1Used);
                    if (v0 != 0) {
                        // 0x004287a4
                        charge(ctx, 3);
                        lw(v0, v1, kSmapPc1SceneRes);
                        if (v0 != 0) {
                            // 0x004287b0
                            charge(ctx, 1);
                            a0 = 1;
                        }
                    }
                    // 0x004287b4
                    charge(ctx, 4);
                    v1 = sltu(0, a0);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x004287c4: member m + 1 used (+72 and +84): its first mark position +2240 + 8 m / +2244 + 8 m = corner + the hero's cell offset - its own + size / 4 + 2; seed its sparkles (sub_430A40(m + 1))
                        charge(ctx, 25);
                        v0 = sll(s2, 3);
                        s0 = addu(s1, v0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x4287E0u, gen::fn_sub_429EF0_00429ef0);
                        lwc1(f1, s1, kSmapWorkCornerX);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        v0 = addiu(s2, 1);
                        a0 = dsll32(v0, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x42880Cu, gen::fn_sub_429EF0_00429ef0);
                        sub_s(f1, f20, f0);
                        lb(v1, s1, kSmapWorkCellPx);
                        v0 = sra(v1, 2);
                        if (i64(v1) < 0) {
                            // 0x00428828
                            charge(ctx, 2);
                            v0 = addiu(v1, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x00428830
                        charge(ctx, 32);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, s0, kSmapWorkPcMark1X);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x428868u, gen::fn_sub_429FE0_00429fe0);
                        lwc1(f1, s1, kSmapWorkCornerY);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        v0 = addiu(s2, 1);
                        a0 = dsll32(v0, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x428894u, gen::fn_sub_429FE0_00429fe0);
                        sub_s(f1, f20, f0);
                        lb(v1, s1, kSmapWorkCellPx);
                        v0 = sra(v1, 2);
                        if (i64(v1) < 0) {
                            // 0x004288b0
                            charge(ctx, 2);
                            v0 = addiu(v1, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x004288b8
                        charge(ctx, 14);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, s0, kSmapWorkPcMark1Y);
                        v0 = addiu(s2, 1);
                        a0 = dsll32(v0, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x4288E8u, gen::fn_sub_430A40_00430a40);
                    }
                    // 0x004288f0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00428900
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00428a98: loop i = 0..23 over the shadows gFldUnitsEc[i]
                    charge(ctx, 3);
                    v0 = slti(s0, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042890c
                    charge(ctx, 10);
                    a0 = 0;
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, -4704);  // &gFldUnitsEc
                    v1 = addu(v0, v1);
                    lw(v0, v1, kUnitUsed);
                    if (v0 != 0) {
                        // 0x00428934
                        charge(ctx, 3);
                        lw(v0, v1, kUnitSceneRes);
                        if (v0 != 0) {
                            // 0x00428940
                            charge(ctx, 1);
                            a0 = 1;
                        }
                    }
                    // 0x00428944
                    charge(ctx, 4);
                    v1 = sltu(0, a0);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00428954: shadow i used (+72 and +84): its mark +2364 + 8 i / +2368 + 8 i = corner + the hero's cell offset - its offset (sub_42A230 / sub_42A310) + size / 4 + 2 - 2 size
                        charge(ctx, 23);
                        lb(s2, s1, kSmapWorkCellPx);
                        v0 = sll(s0, 3);
                        s3 = addu(s1, v0);
                        mtc1(s2, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x428970u, gen::fn_sub_429EF0_00429ef0);
                        lwc1(f1, s1, kSmapWorkCornerX);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = dsll32(s0, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x428998u, gen::fn_sub_42A230_0042a230);
                        sub_s(f1, f20, f0);
                        v0 = sra(s2, 2);
                        if (i64(s2) < 0) {
                            // 0x004289b0
                            charge(ctx, 2);
                            v0 = addiu(s2, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x004289b8
                        charge(ctx, 35);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s2, 1);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, s3, kSmapWorkEcMarkX);
                        lb(s2, s1, kSmapWorkCellPx);
                        mtc1(s2, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x428A04u, gen::fn_sub_429FE0_00429fe0);
                        lwc1(f1, s1, kSmapWorkCornerY);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = dsll32(s0, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x428A2Cu, gen::fn_sub_42A310_0042a310);
                        sub_s(f1, f20, f0);
                        v0 = sra(s2, 2);
                        if (i64(s2) < 0) {
                            // 0x00428a44
                            charge(ctx, 2);
                            v0 = addiu(s2, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x00428a4c
                        charge(ctx, 14);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s2, 1);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, s3, kSmapWorkEcMarkY);
                    }
                    // 0x00428a84: the per-shadow byte 0x95C210 + i = 0
                    charge(ctx, 5);
                    v0 = 0x960000;
                    v0 = addiu(v0, -15856);  // &0x95C210
                    v0 = addu(v0, s0);
                    sb(zero, v0, 0);
                    s0 = addiu(s0, 1);
                }
                // 0x00428aa4
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00428c0c: loop i = 0..31 over the treasure records at 0x86BE80 (312 bytes each)
                    charge(ctx, 3);
                    v0 = slti(s0, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00428ab0
                    charge(ctx, 11);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 3);
                    v0 = subu(v0, s0);
                    v1 = sll(v0, 3);
                    v0 = 0x870000;
                    v0 = addiu(v0, -16768);  // &0x86BE80
                    v1 = addu(v0, v1);
                    lw(v0, v1, 0);
                    if (v0 != 0) {
                        // 0x00428adc: a used record: its mark +2560 + 8 i / +2564 + 8 i from its position +268 (sub_42A3F0 / sub_42A4A0), same formula
                        charge(ctx, 23);
                        s2 = addiu(v1, kSmapChestPos);
                        lb(s3, s1, kSmapWorkCellPx);
                        v0 = sll(s0, 3);
                        s5 = addu(s1, v0);
                        mtc1(s3, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x428AFCu, gen::fn_sub_429EF0_00429ef0);
                        lwc1(f1, s1, kSmapWorkCornerX);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = s2;
                        jal(ctx, 0x428B20u, gen::fn_sub_42A3F0_0042a3f0);
                        sub_s(f1, f20, f0);
                        v0 = sra(s3, 2);
                        if (i64(s3) < 0) {
                            // 0x00428b38
                            charge(ctx, 2);
                            v0 = addiu(s3, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x00428b40
                        charge(ctx, 34);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s3, 1);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, s5, kSmapWorkChestMarkX);
                        lb(s3, s1, kSmapWorkCellPx);
                        mtc1(s3, f0);
                        cvt_s_w(f12, f0);
                        a0 = 0;
                        jal(ctx, 0x428B8Cu, gen::fn_sub_429FE0_00429fe0);
                        lwc1(f1, s1, kSmapWorkCornerY);
                        add_s(f20, f1, f0);
                        lb(v0, s1, kSmapWorkCellPx);
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        a0 = s2;
                        jal(ctx, 0x428BB0u, gen::fn_sub_42A4A0_0042a4a0);
                        sub_s(f1, f20, f0);
                        v0 = sra(s3, 2);
                        if (i64(s3) < 0) {
                            // 0x00428bc8
                            charge(ctx, 2);
                            v0 = addiu(s3, 3);
                            v0 = sra(v0, 2);
                        }
                        // 0x00428bd0
                        charge(ctx, 14);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40000000;
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s3, 1);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, s5, kSmapWorkChestMarkY);
                    }
                    // 0x00428c08
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x00428c18: the floor exit: only while 0x86E580 == 1
                charge(ctx, 5);
                v0 = 0x870000;
                lw(v1, v0, -6784);  // 0x86E580
                v0 = 1;
                if (v1 == v0) {
                    // 0x00428c2c: the exit's mark +2816 / +2820 from the position 0x86E684, and its grid cell +2824 / +2825 (sub_44F120 / sub_44F170)
                    charge(ctx, 21);
                    lb(s0, s1, kSmapWorkCellPx);
                    mtc1(s0, f0);
                    cvt_s_w(f12, f0);
                    a0 = 0;
                    jal(ctx, 0x428C40u, gen::fn_sub_429EF0_00429ef0);
                    lwc1(f1, s1, kSmapWorkCornerX);
                    add_s(f20, f1, f0);
                    lb(v0, s1, kSmapWorkCellPx);
                    mtc1(v0, f0);
                    cvt_s_w(f12, f0);
                    a0 = 0x870000;
                    a0 = addiu(a0, -6524);  // &0x86E684
                    jal(ctx, 0x428C68u, gen::fn_sub_42A3F0_0042a3f0);
                    sub_s(f1, f20, f0);
                    v0 = sra(s0, 2);
                    if (i64(s0) < 0) {
                        // 0x00428c80
                        charge(ctx, 2);
                        v0 = addiu(s0, 3);
                        v0 = sra(v0, 2);
                    }
                    // 0x00428c88
                    charge(ctx, 35);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x40000000;
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = sll(s0, 1);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, s1, kSmapWorkExitMarkX);
                    lb(s0, s1, kSmapWorkCellPx);
                    mtc1(s0, f0);
                    cvt_s_w(f12, f0);
                    a0 = 0;
                    jal(ctx, 0x428CD4u, gen::fn_sub_429FE0_00429fe0);
                    lwc1(f1, s1, kSmapWorkCornerY);
                    add_s(f20, f1, f0);
                    lb(v0, s1, kSmapWorkCellPx);
                    mtc1(v0, f0);
                    cvt_s_w(f12, f0);
                    a0 = 0x870000;
                    a0 = addiu(a0, -6524);  // &0x86E684
                    jal(ctx, 0x428CFCu, gen::fn_sub_42A4A0_0042a4a0);
                    sub_s(f1, f20, f0);
                    v0 = sra(s0, 2);
                    if (i64(s0) < 0) {
                        // 0x00428d14
                        charge(ctx, 2);
                        v0 = addiu(s0, 3);
                        v0 = sra(v0, 2);
                    }
                    // 0x00428d1c
                    charge(ctx, 24);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x40000000;
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = sll(s0, 1);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, s1, kSmapWorkExitMarkY);
                    a0 = 0x870000;
                    a0 = addiu(a0, -6524);  // &0x86E684
                    jal(ctx, 0x428D5Cu, gen::fn_sub_44F120_0044f120);
                    sb(v0, s1, kSmapWorkExitCellX);
                    a0 = 0x870000;
                    a0 = addiu(a0, -6524);  // &0x86E684
                    jal(ctx, 0x428D70u, gen::fn_sub_44F170_0044f170);
                    sb(v0, s1, kSmapWorkExitCellZ);
                }
                // 0x00428d7c: the stairs: sub_42FD80 [Y_SMap_FindStairs] -> the door position next to them (sp+0x118, copied to sp+0x150) -> its cell +2827 / +2828; the frame (sub_430630); -> 14; gp-0x4614 (0x7CE6DC) = 1
                charge(ctx, 27);
                a0 = addiu(sp, 0x118);
                a1 = s4;
                jal(ctx, 0x428D84u, gen::fn_sub_42FD80_0042fd80);
                a0 = addiu(sp, 0x150);
                lwc1(f2, sp, 0x118);
                lwc1(f1, sp, 0x11C);
                lwc1(f0, sp, 0x120);
                swc1(f2, sp, 0x150);
                swc1(f1, sp, 0x154);
                swc1(f0, sp, 0x158);
                jal(ctx, 0x428DA8u, gen::fn_sub_44F120_0044f120);
                sb(v0, s1, kSmapWorkStairDoorX);
                a0 = addiu(sp, 0x150);
                jal(ctx, 0x428DB8u, gen::fn_sub_44F170_0044f170);
                sb(v0, s1, kSmapWorkStairDoorZ);
                a0 = s4;
                jal(ctx, 0x428DC8u, gen::fn_sub_430630_00430630);
                v0 = 14;
                sb(v0, s1, kSmapWorkState);
                v0 = 1;
                sb(v0, gp, -17940);  // 0x7CE6DC
                goto L_00429bcc;
            case 0x428DE8u:  // table[14]
                // 0x00428de8: state 14 (random-floor draw, every frame): every existing cell tmx task (+92 + 128 z + 8 x, kwlnTaskExists) hidden (+336 = 1)
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x00428e4c
                    charge(ctx, 3);
                    v0 = slti(s3, 16);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00428df4
                    charge(ctx, 5);
                    s2 = 0;
                    v0 = sll(s3, 7);
                    s0 = addu(s1, v0);
                    for (;;) {
                        // 0x00428e3c
                        charge(ctx, 3);
                        v0 = slti(s2, 16);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00428e08
                        charge(ctx, 9);
                        v0 = sll(s2, 3);
                        v0 = addu(s0, v0);
                        s5 = addiu(v0, kSmapWorkCellTasks);
                        lw(a0, v0, kSmapWorkCellTasks);
                        jal(ctx, 0x428E18u, gen::fn_kwlnTaskExists_00195460);
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x00428e2c
                            charge(ctx, 3);
                            lw(v0, s5, 0);
                            lw(v0, v0, kTaskWork);
                            sb(v1, v0, kSmapTmxHidden);
                        }
                        // 0x00428e38
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x00428e48
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x00428e58: the hero exists (gFldUnitsPc[0] +72 / +84)?
                charge(ctx, 5);
                v0 = 0x870000;
                lw(v0, v0, 6120);  // 0x8717E8
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00428e6c
                    charge(ctx, 3);
                    v0 = 0x870000;
                    lw(v0, v0, 6132);  // 0x8717F4
                    v0 = sltu(0, v0);
                }
                // 0x00428e78
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00428e80: direction arrow: a 4 x 4 box centred in the 126 x 126 map (sub_423FE0) -> +2204 / +2208, sub_4561D0 places it, sub_456400(+2200, 1) shows it; the hero's cell marked seen (sub_42A550(task, 0, x, z))
                    charge(ctx, 47);
                    a0 = addiu(sp, 0x148);
                    a1 = 0;
                    a2 = 126;
                    a3 = a2;
                    t0 = 4;
                    t1 = t0;
                    jal(ctx, 0x428E98u, gen::fn_sub_423FE0_00423fe0);
                    lwc1(f1, s1, kSmapWorkCornerX);
                    lwc1(f0, sp, 0x148);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, kSmapWorkSymbolX);
                    lwc1(f1, s1, kSmapWorkCornerY);
                    lwc1(f0, sp, 0x14C);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, kSmapWorkSymbolY);
                    lw(a0, s1, kSmapWorkSymbolTask);
                    lwc1(f12, s1, kSmapWorkSymbolX);
                    lwc1(f13, s1, kSmapWorkSymbolY);
                    jal(ctx, 0x428ECCu, gen::fn_sub_4561D0_004561d0);
                    lw(a0, s1, kSmapWorkSymbolTask);
                    a1 = 1;
                    jal(ctx, 0x428EDCu, gen::fn_sub_456400_00456400);
                    v0 = 0x870000;
                    lw(v0, v0, 6132);  // 0x8717F4
                    lw(a0, v0, kResController);
                    jal(ctx, 0x428EF0u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    v0 = 0x870000;
                    lw(v0, v0, 6132);  // 0x8717F4
                    lw(a0, v0, kResController);
                    jal(ctx, 0x428F0Cu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    a3 = dsll32(v0, 24);
                    a3 = dsra32(a3, 24);
                    a0 = s4;
                    a1 = 0;
                    a2 = s0;
                    jal(ctx, 0x428F28u, gen::fn_sub_42A550_0042a550);
                    lb(v0, gp, -17964);  // 0x7CE6C4
                    if (v0 == 0) {
                        // 0x00428f3c: stairs-found flag gp-0x462C (0x7CE6C4) still clear: is the hero on the stair-door cell +2827 / +2828?
                        charge(ctx, 8);
                        lb(s0, s1, kSmapWorkStairDoorX);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x428F4Cu, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        if (s0 == v0) {
                            // 0x00428f5c
                            charge(ctx, 8);
                            lb(s0, s1, kSmapWorkStairDoorZ);
                            v0 = 0x870000;
                            lw(v0, v0, 6132);  // 0x8717F4
                            lw(a0, v0, kResController);
                            jal(ctx, 0x428F6Cu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            if (s0 != v0) {
                                goto L_00428f90;
                            }
                            // 0x00428f7c: yes: stairs found -- gp-0x462C = 1 and gp-0x4618 (0x7CE6D8) = 1
                            charge(ctx, 5);
                            v0 = 1;
                            sb(v0, gp, -17964);  // 0x7CE6C4
                            sb(v0, gp, -17944);  // 0x7CE6D8
                            goto L_00428fec;
                        }
                    L_00428f90:
                        charge(ctx, 20);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x428F9Cu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        s0 = sll(v0, 8);
                        jal(ctx, 0x428FA8u, gen::fn_K_Field_Get_001b9120);
                        s0 = addu(v0, s0);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x428FC0u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        v0 = sll(v0, 4);
                        v0 = addu(s0, v0);
                        lbu(v1, v0, kGridCellKind);
                        v0 = 8;
                        if (v1 == v0) {
                            // 0x00428fe0: the hero stands on a stair cell (kind 8): the same two flags = 1
                            charge(ctx, 3);
                            v0 = 1;
                            sb(v0, gp, -17964);  // 0x7CE6C4
                            sb(v0, gp, -17944);  // 0x7CE6D8
                        }
                    }
                L_00428fec:
                    charge(ctx, 3);
                    lb(v0, gp, -17960);  // 0x7CE6C8
                    if (v0 == 0) {
                        // 0x00428ff8: exit flag gp-0x4628 (0x7CE6C8) clear: the hero on the exit cell +2824 / +2825 sets it
                        charge(ctx, 8);
                        lb(s0, s1, kSmapWorkExitCellX);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x429008u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        if (s0 == v0) {
                            // 0x00429018
                            charge(ctx, 8);
                            lb(s0, s1, kSmapWorkExitCellZ);
                            v0 = 0x870000;
                            lw(v0, v0, 6132);  // 0x8717F4
                            lw(a0, v0, kResController);
                            jal(ctx, 0x429028u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                            if (s0 == v0) {
                                // 0x00429038
                                charge(ctx, 2);
                                v0 = 1;
                                sb(v0, gp, -17960);  // 0x7CE6C8
                            }
                        }
                    }
                }
                // 0x00429040: party member 1 (gFldUnitsPc[1] +72 0x8719A8 / +84 0x8719B4) used?
                charge(ctx, 5);
                v0 = 0x870000;
                lw(v0, v0, 6568);  // 0x8719A8
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00429054
                    charge(ctx, 3);
                    v0 = 0x870000;
                    lw(v0, v0, 6580);  // 0x8719B4
                    v0 = sltu(0, v0);
                }
                // 0x00429060
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00429068: its cell marked seen: sub_42A550(task, 1, x, z)
                    charge(ctx, 19);
                    v0 = 0x870000;
                    lw(v0, v0, 6580);  // 0x8719B4
                    lw(a0, v0, kResController);
                    jal(ctx, 0x429074u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    v0 = 0x870000;
                    lw(v0, v0, 6580);  // 0x8719B4
                    lw(a0, v0, kResController);
                    jal(ctx, 0x429090u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    a3 = dsll32(v0, 24);
                    a3 = dsra32(a3, 24);
                    a0 = s4;
                    a1 = 1;
                    a2 = s0;
                    jal(ctx, 0x4290ACu, gen::fn_sub_42A550_0042a550);
                }
                // 0x004290b4
                charge(ctx, 5);
                v0 = 0x870000;
                lw(v0, v0, 7016);  // 0x871B68
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x004290c8
                    charge(ctx, 3);
                    v0 = 0x870000;
                    lw(v0, v0, 7028);  // 0x871B74
                    v0 = sltu(0, v0);
                }
                // 0x004290d4
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004290dc: party member 2 (0x871B68 / 0x871B74): sub_42A550(task, 2, x, z)
                    charge(ctx, 19);
                    v0 = 0x870000;
                    lw(v0, v0, 7028);  // 0x871B74
                    lw(a0, v0, kResController);
                    jal(ctx, 0x4290E8u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    v0 = 0x870000;
                    lw(v0, v0, 7028);  // 0x871B74
                    lw(a0, v0, kResController);
                    jal(ctx, 0x429104u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    a3 = dsll32(v0, 24);
                    a3 = dsra32(a3, 24);
                    a0 = s4;
                    a1 = 2;
                    a2 = s0;
                    jal(ctx, 0x429120u, gen::fn_sub_42A550_0042a550);
                }
                // 0x00429128
                charge(ctx, 5);
                v0 = 0x870000;
                lw(v0, v0, 7464);  // 0x871D28
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x0042913c
                    charge(ctx, 3);
                    v0 = 0x870000;
                    lw(v0, v0, 7476);  // 0x871D34
                    v0 = sltu(0, v0);
                }
                // 0x00429148
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00429150: party member 3 (0x871D28 / 0x871D34): sub_42A550(task, 3, x, z)
                    charge(ctx, 19);
                    v0 = 0x870000;
                    lw(v0, v0, 7476);  // 0x871D34
                    lw(a0, v0, kResController);
                    jal(ctx, 0x42915Cu, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    v0 = 0x870000;
                    lw(v0, v0, 7476);  // 0x871D34
                    lw(a0, v0, kResController);
                    jal(ctx, 0x429178u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    a3 = dsll32(v0, 24);
                    a3 = dsra32(a3, 24);
                    a0 = s4;
                    a1 = 3;
                    a2 = s0;
                    jal(ctx, 0x429194u, gen::fn_sub_42A550_0042a550);
                }
                // 0x0042919c: the view window: rows / columns 0 .. view + 3 (+2856 = 7: 11 x 11 cells) around the hero
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x0042993c: row loop head (s3 = row)
                    charge(ctx, 5);
                    lb(v0, s1, kSmapWorkViewCells);
                    v0 = addiu(v0, kSmapWorkFile0);
                    v0 = slt(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004291a8
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x00429924: column loop head (s2 = column)
                        charge(ctx, 5);
                        lb(v0, s1, kSmapWorkViewCells);
                        v0 = addiu(v0, kSmapWorkFile0);
                        v0 = slt(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004291b4: grid cell x = hero x - view / 2 - 2 + column (s0), z = hero z - view / 2 - 2 + row (s5)
                        charge(ctx, 9);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x4291C0u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                        lb(a0, s1, kSmapWorkViewCells);
                        v1 = sra(a0, 1);
                        if (i64(a0) < 0) {
                            // 0x004291d8
                            charge(ctx, 2);
                            v1 = addiu(a0, 1);
                            v1 = sra(v1, 1);
                        }
                        // 0x004291e0
                        charge(ctx, 12);
                        v0 = subu(v0, v1);
                        v0 = addu(s2, v0);
                        s0 = addiu(v0, -2);
                        v0 = 0x870000;
                        lw(v0, v0, 6132);  // 0x8717F4
                        lw(a0, v0, kResController);
                        jal(ctx, 0x4291F8u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                        lb(a0, s1, kSmapWorkViewCells);
                        v1 = sra(a0, 1);
                        if (i64(a0) < 0) {
                            // 0x00429210
                            charge(ctx, 2);
                            v1 = addiu(a0, 1);
                            v1 = sra(v1, 1);
                        }
                        // 0x00429218
                        charge(ctx, 5);
                        v0 = subu(v0, v1);
                        v0 = addu(s3, v0);
                        s5 = addiu(v0, -2);
                        if (i64(s0) >= 0) {
                            // 0x0042922c
                            charge(ctx, 2);
                            if (i64(s5) >= 0) {
                                // 0x00429234
                                charge(ctx, 3);
                                at = slti(s0, 16);
                                if (at != 0) {
                                    // 0x00429240
                                    charge(ctx, 3);
                                    at = slti(s5, 16);
                                    if (at != 0) {
                                        // 0x0042924c: inside the 16 x 16 grid: a floor cell (+0 == 1) and +1 == 1?
                                        charge(ctx, 10);
                                        s7 = sll(s5, 8);
                                        fp = sll(s0, 4);
                                        jal(ctx, 0x429254u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s7);
                                        v0 = addu(v0, fp);
                                        lbu(v1, v0, kSmapCellFloor);
                                        v0 = 1;
                                        if (v1 == v0) {
                                            // 0x00429274
                                            charge(ctx, 8);
                                            jal(ctx, 0x429274u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s7);
                                            v0 = addu(v0, fp);
                                            lbu(v1, v0, kSmapCellB1);
                                            v0 = 1;
                                            if (v1 == v0) {
                                                // 0x00429294: its tmx task (+92 + 128 z + 8 x, address kept in a quadword at sp+0xD0) still exists?
                                                charge(ctx, 12);
                                                v0 = sll(s5, 4);
                                                v0 = addu(s0, v0);
                                                v0 = sll(v0, 3);
                                                v1 = addu(s1, v0);
                                                v0 = addiu(v1, kSmapWorkCellTasks);
                                                sq(v0, sp, 0xD0);
                                                lw(a0, v1, kSmapWorkCellTasks);
                                                jal(ctx, 0x4292B0u, gen::fn_kwlnTaskExists_00195460);
                                                a0 = 1;
                                                if (v0 == a0) {
                                                    // 0x004292c4: show it (+336 = 0); seen-cells grid 0x95C110[z][x] == 1?
                                                    charge(ctx, 12);
                                                    v1 = sll(s5, 4);
                                                    lq(v0, sp, 0xD0);
                                                    lw(v0, v0, 0);
                                                    lw(v0, v0, kTaskWork);
                                                    sb(zero, v0, kSmapTmxHidden);
                                                    v0 = 0x960000;
                                                    v0 = addiu(v0, -16112);  // &0x95C110
                                                    v0 = addu(v0, s0);
                                                    v0 = addu(v1, v0);
                                                    lb(v0, v0, 0);
                                                    if (v0 != a0) {
                                                        // 0x00429340: not seen: white with alpha 0 (+275 + 4 k = 0) -- the room stays invisible
                                                        charge(ctx, 7);
                                                        lq(v0, sp, 0xD0);
                                                        lw(v0, v0, 0);
                                                        lw(a0, v0, kTaskWork);
                                                        a1 = 0;
                                                        v1 = 255;
                                                        for (;;) {
                                                            // 0x00429378
                                                            charge(ctx, 3);
                                                            v0 = slti(a1, 4);
                                                            if (v0 == 0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                            // 0x0042935c
                                                            charge(ctx, 7);
                                                            v0 = sll(a1, 2);
                                                            v0 = addu(a0, v0);
                                                            sb(v1, v0, kSmapTmxColR);
                                                            sb(v1, v0, kSmapTmxColB);
                                                            sb(v1, v0, kSmapTmxColG);
                                                            sb(zero, v0, kSmapTmxColA);
                                                            a1 = addiu(a1, 1);
                                                        }
                                                    } else {
                                                        // 0x004292f4: seen: the four vertex colours = opaque white (+272..+275 = 255)
                                                        charge(ctx, 7);
                                                        lq(v0, sp, 0xD0);
                                                        lw(v0, v0, 0);
                                                        lw(a0, v0, kTaskWork);
                                                        a1 = 0;
                                                        v1 = 255;
                                                        for (;;) {
                                                            // 0x0042932c
                                                            charge(ctx, 3);
                                                            v0 = slti(a1, 4);
                                                            if (v0 == 0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                            // 0x00429310
                                                            charge(ctx, 7);
                                                            v0 = sll(a1, 2);
                                                            v0 = addu(a0, v0);
                                                            sb(v1, v0, kSmapTmxColR);
                                                            sb(v1, v0, kSmapTmxColB);
                                                            sb(v1, v0, kSmapTmxColG);
                                                            sb(v1, v0, kSmapTmxColA);
                                                            a1 = addiu(a1, 1);
                                                        }
                                                        // 0x00429338
                                                        charge(ctx, 2);
                                                    }
                                                    // 0x00429384: the room's screen position: from the frozen centre (+2149 set) or the hero
                                                    charge(ctx, 3);
                                                    lb(v0, s1, kSmapWorkFrozen);
                                                    if (v0 != 0) {
                                                        // 0x00429444: frozen: x = corner + size * column + the frozen centre's cell offset (sub_42A0D0(+2152)) - 2 size (y the same with sub_42A180)
                                                        charge(ctx, 43);
                                                        lb(s6, s1, kSmapWorkCellPx);
                                                        mtc1(s6, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkFrozenPos);
                                                        jal(ctx, 0x429458u, gen::fn_sub_42A0D0_0042a0d0);
                                                        lwc1(f2, s1, kSmapWorkCornerX);
                                                        mult(v0, s6, s2);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f1, f1, f0);
                                                        v0 = sll(s6, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x140);
                                                        lb(v0, s1, kSmapWorkCellPx);
                                                        sq(v0, sp, 0xB0);
                                                        mtc1(s6, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkFrozenPos);
                                                        jal(ctx, 0x4294ACu, gen::fn_sub_42A180_0042a180);
                                                        lwc1(f2, s1, kSmapWorkCornerY);
                                                        lq(v0, sp, 0xB0);
                                                        mult(v0, v0, s3);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f1, f1, f0);
                                                        lq(v0, sp, 0xB0);
                                                        v0 = sll(v0, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x144);
                                                    } else {
                                                        // 0x00429390: not frozen: the same with the hero's cell offset (sub_429EF0(0) / sub_429FE0(0))
                                                        charge(ctx, 45);
                                                        lb(s6, s1, kSmapWorkCellPx);
                                                        mtc1(s6, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = 0;
                                                        jal(ctx, 0x4293A4u, gen::fn_sub_429EF0_00429ef0);
                                                        lwc1(f2, s1, kSmapWorkCornerX);
                                                        mult(v0, s6, s2);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f1, f1, f0);
                                                        v0 = sll(s6, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x140);
                                                        lb(v0, s1, kSmapWorkCellPx);
                                                        sq(v0, sp, 0xC0);
                                                        mtc1(s6, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = 0;
                                                        jal(ctx, 0x4293F8u, gen::fn_sub_429FE0_00429fe0);
                                                        lwc1(f2, s1, kSmapWorkCornerY);
                                                        lq(v0, sp, 0xC0);
                                                        mult(v0, v0, s3);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f1, f1, f0);
                                                        lq(v0, sp, 0xC0);
                                                        v0 = sll(v0, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x144);
                                                    }
                                                    // 0x004294f0: the tmx work +308 / +312 = that position
                                                    charge(ctx, 7);
                                                    lq(v0, sp, 0xD0);
                                                    lw(v0, v0, 0);
                                                    lw(v0, v0, kTaskWork);
                                                    lwc1(f1, sp, 0x140);
                                                    lwc1(f0, sp, 0x144);
                                                    swc1(f1, v0, kSmapTmxX);
                                                    swc1(f0, v0, kSmapTmxY);
                                                }
                                            }
                                        }
                                        // 0x0042950c: every in-grid cell: party marks 1..3 (sub_42C0A0), shadow marks (sub_42CFC0), field objects (sub_42DD90), treasure (sub_42EA60), the exit (sub_42F440)
                                        charge(ctx, 70);
                                        a2 = dsll32(s0, 16);
                                        a2 = dsra32(a2, 16);
                                        a3 = dsll32(s5, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = s4;
                                        a1 = 1;
                                        t0 = s2;
                                        t1 = s3;
                                        jal(ctx, 0x42952Cu, gen::fn_sub_42C0A0_0042c0a0);
                                        a2 = dsll32(s0, 16);
                                        a2 = dsra32(a2, 16);
                                        a3 = dsll32(s5, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = s4;
                                        a1 = 2;
                                        t0 = s2;
                                        t1 = s3;
                                        jal(ctx, 0x429554u, gen::fn_sub_42C0A0_0042c0a0);
                                        a2 = dsll32(s0, 16);
                                        a2 = dsra32(a2, 16);
                                        a3 = dsll32(s5, 16);
                                        a3 = dsra32(a3, 16);
                                        a0 = s4;
                                        a1 = 3;
                                        t0 = s2;
                                        t1 = s3;
                                        jal(ctx, 0x42957Cu, gen::fn_sub_42C0A0_0042c0a0);
                                        a1 = dsll32(s0, 16);
                                        a1 = dsra32(a1, 16);
                                        a2 = dsll32(s5, 16);
                                        a2 = dsra32(a2, 16);
                                        a0 = s4;
                                        a3 = s2;
                                        t0 = s3;
                                        jal(ctx, 0x4295A0u, gen::fn_sub_42CFC0_0042cfc0);
                                        a1 = dsll32(s0, 16);
                                        a1 = dsra32(a1, 16);
                                        a2 = dsll32(s5, 16);
                                        a2 = dsra32(a2, 16);
                                        a0 = s4;
                                        a3 = s2;
                                        t0 = s3;
                                        jal(ctx, 0x4295C4u, gen::fn_sub_42DD90_0042dd90);
                                        a1 = dsll32(s0, 16);
                                        a1 = dsra32(a1, 16);
                                        a2 = dsll32(s5, 16);
                                        a2 = dsra32(a2, 16);
                                        a0 = s4;
                                        a3 = s2;
                                        t0 = s3;
                                        jal(ctx, 0x4295E8u, gen::fn_sub_42EA60_0042ea60);
                                        a1 = dsll32(s0, 16);
                                        a1 = dsra32(a1, 16);
                                        a2 = dsll32(s5, 16);
                                        a2 = dsra32(a2, 16);
                                        a0 = s4;
                                        a3 = s2;
                                        t0 = s3;
                                        jal(ctx, 0x42960Cu, gen::fn_sub_42F440_0042f440);
                                        lb(v1, gp, -17964);  // 0x7CE6C4
                                        v0 = 1;
                                        if (v1 == v0) {
                                            // 0x00429624: stairs found (gp-0x462C == 1) and this cell is the stair cell (kind 8, +1 == 1)?
                                            charge(ctx, 8);
                                            jal(ctx, 0x429624u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s7);
                                            v0 = addu(v0, fp);
                                            lbu(v1, v0, kGridCellKind);
                                            v0 = 8;
                                            if (v1 == v0) {
                                                // 0x00429644
                                                charge(ctx, 8);
                                                jal(ctx, 0x429644u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s7);
                                                v0 = addu(v0, fp);
                                                lbu(v1, v0, kSmapCellB1);
                                                v0 = 1;
                                                if (v1 == v0) {
                                                    // 0x00429664: read the icon's rect (sub_430270 into sp+0xE0); the icon's position from the frozen centre or the hero
                                                    charge(ctx, 7);
                                                    a0 = addiu(sp, 0xE0);
                                                    lw(a1, s1, kSmapWorkStairTask);
                                                    jal(ctx, 0x42966Cu, gen::fn_sub_430270_00430270);
                                                    lb(v0, s1, kSmapWorkFrozen);
                                                    if (v0 != 0) {
                                                        // 0x004297cc: frozen: corner + size * column + centre offset - the stairs' offset (sub_42A3F0(+2832)) - 2 size + size / 2 - 6 (y likewise) -> sp+0x138
                                                        charge(ctx, 30);
                                                        lb(s0, s1, kSmapWorkCellPx);
                                                        mtc1(s0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkFrozenPos);
                                                        jal(ctx, 0x4297E0u, gen::fn_sub_42A0D0_0042a0d0);
                                                        lwc1(f2, s1, kSmapWorkCornerX);
                                                        mult(v0, s0, s2);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f20, f1, f0);
                                                        lb(v0, s1, kSmapWorkCellPx);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkStairPos);
                                                        jal(ctx, 0x429818u, gen::fn_sub_42A3F0_0042a3f0);
                                                        sub_s(f1, f20, f0);
                                                        v0 = sll(s0, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f1, f1, f0);
                                                        v0 = sra(s0, 1);
                                                        if (i64(s0) < 0) {
                                                            // 0x00429844
                                                            charge(ctx, 2);
                                                            v0 = addiu(s0, 1);
                                                            v0 = sra(v0, 1);
                                                        }
                                                        // 0x0042984c
                                                        charge(ctx, 38);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f1, f0, f1);
                                                        v0 = 0x40C00000;
                                                        mtc1(v0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x138);
                                                        lb(s5, s1, kSmapWorkCellPx);
                                                        mtc1(s5, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkFrozenPos);
                                                        jal(ctx, 0x429884u, gen::fn_sub_42A180_0042a180);
                                                        lwc1(f2, s1, kSmapWorkCornerY);
                                                        mult(v0, s5, s3);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f20, f1, f0);
                                                        mtc1(s0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkStairPos);
                                                        jal(ctx, 0x4298B8u, gen::fn_sub_42A4A0_0042a4a0);
                                                        sub_s(f1, f20, f0);
                                                        v0 = sll(s5, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f1, f1, f0);
                                                        v0 = sra(s5, 1);
                                                        if (i64(s5) < 0) {
                                                            // 0x004298e4
                                                            charge(ctx, 2);
                                                            v0 = addiu(s5, 1);
                                                            v0 = sra(v0, 1);
                                                        }
                                                        // 0x004298ec
                                                        charge(ctx, 9);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f1, f0, f1);
                                                        v0 = 0x40C00000;
                                                        mtc1(v0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x13C);
                                                    } else {
                                                        // 0x00429680: not frozen: the same with the hero's cell offset
                                                        charge(ctx, 30);
                                                        lb(s0, s1, kSmapWorkCellPx);
                                                        mtc1(s0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = 0;
                                                        jal(ctx, 0x429694u, gen::fn_sub_429EF0_00429ef0);
                                                        lwc1(f2, s1, kSmapWorkCornerX);
                                                        mult(v0, s0, s2);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f20, f1, f0);
                                                        lb(v0, s1, kSmapWorkCellPx);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkStairPos);
                                                        jal(ctx, 0x4296CCu, gen::fn_sub_42A3F0_0042a3f0);
                                                        sub_s(f1, f20, f0);
                                                        v0 = sll(s0, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f1, f1, f0);
                                                        v0 = sra(s0, 1);
                                                        if (i64(s0) < 0) {
                                                            // 0x004296f8
                                                            charge(ctx, 2);
                                                            v0 = addiu(s0, 1);
                                                            v0 = sra(v0, 1);
                                                        }
                                                        // 0x00429700
                                                        charge(ctx, 38);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f1, f0, f1);
                                                        v0 = 0x40C00000;
                                                        mtc1(v0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x138);
                                                        lb(s5, s1, kSmapWorkCellPx);
                                                        mtc1(s5, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = 0;
                                                        jal(ctx, 0x429738u, gen::fn_sub_429FE0_00429fe0);
                                                        lwc1(f2, s1, kSmapWorkCornerY);
                                                        mult(v0, s5, s3);
                                                        mtc1(v0, f1);
                                                        cvt_s_w(f1, f1);
                                                        add_s(f1, f2, f1);
                                                        add_s(f20, f1, f0);
                                                        mtc1(s0, f0);
                                                        cvt_s_w(f12, f0);
                                                        a0 = addiu(s1, kSmapWorkStairPos);
                                                        jal(ctx, 0x42976Cu, gen::fn_sub_42A4A0_0042a4a0);
                                                        sub_s(f1, f20, f0);
                                                        v0 = sll(s5, 1);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        sub_s(f1, f1, f0);
                                                        v0 = sra(s5, 1);
                                                        if (i64(s5) < 0) {
                                                            // 0x00429798
                                                            charge(ctx, 2);
                                                            v0 = addiu(s5, 1);
                                                            v0 = sra(v0, 1);
                                                        }
                                                        // 0x004297a0
                                                        charge(ctx, 11);
                                                        mtc1(v0, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f1, f0, f1);
                                                        v0 = 0x40C00000;
                                                        mtc1(v0, f0);
                                                        sub_s(f0, f1, f0);
                                                        swc1(f0, sp, 0x13C);
                                                    }
                                                    // 0x00429910: show the stair icon there: sub_430220(+2844, the f32 pair at sp+0x138)
                                                    charge(ctx, 4);
                                                    lw(a0, s1, kSmapWorkStairTask);
                                                    ld(a1, sp, 0x138);
                                                    jal(ctx, 0x429918u, gen::fn_sub_430220_00430220);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // 0x00429920
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x00429938
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x00429950: after the window: the party members' sparkles (sub_42CD80 [Y_SMap_DrawSparkles])
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x429954u, gen::fn_sub_42CD80_0042cd80);
                goto L_00429bcc;
            case 0x429964u:  // table[15]
                // 0x00429964: state 15 (fixed map): sub_42AA40(task, scene major, minor) (the scene record *(gp-0x57B0)) requests the map files -> +2858 = their count; -> 16
                charge(ctx, 11);
                lw(v0, gp, -22448);  // 0x7CD540
                a0 = s4;
                lw(a1, v0, 0);
                lw(a2, v0, kSmapWorkFile0);
                jal(ctx, 0x429974u, gen::fn_sub_42AA40_0042aa40);
                sb(v0, s1, kSmapWorkLayerCount);
                v0 = 16;
                sb(v0, s1, kSmapWorkState);
                goto L_00429bcc;
            case 0x429990u:  // table[16]
                // 0x00429990: state 16: count the loaded files among +4 + 4 i (H_Cdvd_IsFileLoaded)
                charge(ctx, 4);
                s0 = 0;
                s2 = 0;
                for (;;) {
                    // 0x004299c8
                    charge(ctx, 4);
                    lb(v1, s1, kSmapWorkLayerCount);
                    v0 = slt(s0, v1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004299a0
                    charge(ctx, 8);
                    v0 = sll(s0, 2);
                    v0 = addu(s1, v0);
                    lw(a0, v0, kSmapWorkFile0);
                    jal(ctx, 0x4299ACu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x004299c0
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x004299c4
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x004299d8: all +2858 loaded?
                charge(ctx, 2);
                if (s2 == v1) {
                    // 0x004299e0: textures by name (sub_42AC60); the background box-fill (+2848, 126 x 126 at the corner, sub_422C30 / sub_422C10(10) / sub_422CD0(1))
                    charge(ctx, 12);
                    lw(v0, gp, -22448);  // 0x7CD540
                    a0 = s4;
                    lw(a1, v0, 0);
                    lw(a2, v0, kSmapWorkFile0);
                    jal(ctx, 0x4299F0u, gen::fn_sub_42AC60_0042ac60);
                    v0 = 126;
                    sw(v0, sp, 0xF8);
                    sw(v0, sp, 0xFC);
                    lw(v0, s1, kSmapWorkBoxfill);
                    if (v0 != 0) {
                        // 0x00429a10
                        charge(ctx, 1);
                        sw(zero, s1, kSmapWorkBoxfill);
                    }
                    // 0x00429a14
                    charge(ctx, 24);
                    a0 = s4;
                    ldr(a1, s1, kSmapWorkCornerX);
                    ldl(a1, s1, kSmapWorkCornerEnd);
                    a2 = 2;
                    jal(ctx, 0x429A24u, gen::fn_Y_LMap_CreateBoxfillTasks_004229d0);
                    sw(v0, s1, kSmapWorkBoxfill);
                    a0 = v0;
                    ldr(a1, s1, kSmapWorkCornerX);
                    ldl(a1, s1, kSmapWorkCornerEnd);
                    a2 = addiu(sp, 0xF0);
                    jal(ctx, 0x429A40u, gen::fn_sub_422C30_00422c30);
                    lw(a0, s1, kSmapWorkBoxfill);
                    a1 = 10;
                    jal(ctx, 0x429A50u, gen::fn_sub_422C10_00422c10);
                    lw(a0, s1, kSmapWorkBoxfill);
                    a1 = 1;
                    jal(ctx, 0x429A60u, gen::fn_sub_422CD0_00422cd0);
                    s0 = 0;
                    for (;;) {
                        // 0x00429a9c
                        charge(ctx, 4);
                        lb(v0, s1, kSmapWorkLayerCount);
                        v0 = slt(s0, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00429a74: destroy each file handle +4 + 4 i and clear it
                        charge(ctx, 6);
                        v0 = sll(s0, 2);
                        v0 = addu(s1, v0);
                        s2 = addiu(v0, kSmapWorkFile0);
                        lw(a0, v0, kSmapWorkFile0);
                        if (a0 != 0) {
                            // 0x00429a8c
                            charge(ctx, 3);
                            jal(ctx, 0x429A8Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                            sw(zero, s2, 0);
                        }
                        // 0x00429a98
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                    }
                    // 0x00429aac: -> 17
                    charge(ctx, 4);
                    v0 = 17;
                    sb(v0, s1, kSmapWorkState);
                }
                goto L_00429bcc;
            case 0x429ABCu:  // table[17]
                // 0x00429abc: state 17: the layer tasks (sub_42BA50), the mask task (layout 1) -> +2852, the arrow + layers (sub_42BC10), gp-0x4614 = 1, the frame (sub_430630); -> 18
                charge(ctx, 23);
                a0 = s4;
                jal(ctx, 0x429AC0u, gen::fn_sub_42BA50_0042ba50);
                a0 = s4;
                ldr(a1, s1, kSmapWorkCornerX);
                ldl(a1, s1, kSmapWorkCornerEnd);
                lb(a2, s1, kSmapWorkViewCells);
                a3 = 1;
                jal(ctx, 0x429ADCu, gen::fn_Y_SMap_CreateSmapMaskDrawTask_00431110);
                sw(v0, s1, kSmapWorkMaskTask);
                a0 = s4;
                jal(ctx, 0x429AECu, gen::fn_sub_42BC10_0042bc10);
                v0 = 1;
                sb(v0, gp, -17940);  // 0x7CE6DC
                a0 = s4;
                jal(ctx, 0x429B00u, gen::fn_sub_430630_00430630);
                v0 = 18;
                sb(v0, s1, kSmapWorkState);
                goto L_00429bcc;
            case 0x429B18u:  // table[18]
                // 0x00429b18: state 18 (fixed-map draw, every frame): background sub_422CD0(+2848, 1); the arrow shown when the hero exists
                charge(ctx, 9);
                lw(a0, s1, kSmapWorkBoxfill);
                a1 = 1;
                jal(ctx, 0x429B20u, gen::fn_sub_422CD0_00422cd0);
                v0 = 0x870000;
                lw(v0, v0, 6120);  // 0x8717E8
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00429b3c
                    charge(ctx, 3);
                    v0 = 0x870000;
                    lw(v0, v0, 6132);  // 0x8717F4
                    v0 = sltu(0, v0);
                }
                // 0x00429b48
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x00429b50
                    charge(ctx, 4);
                    lw(a0, s1, kSmapWorkSymbolTask);
                    a1 = 1;
                    jal(ctx, 0x429B58u, gen::fn_sub_456400_00456400);
                }
                // 0x00429b60: every layer task (+92 + 8 i, i < +2858) shown (+336 = 0)
                charge(ctx, 3);
                v1 = 0;
                for (;;) {
                    // 0x00429b84
                    charge(ctx, 4);
                    lb(v0, s1, kSmapWorkLayerCount);
                    v0 = slt(v1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00429b6c
                    charge(ctx, 6);
                    v0 = sll(v1, 3);
                    v0 = addu(s1, v0);
                    lw(v0, v0, kSmapWorkCellTasks);
                    lw(v0, v0, kTaskWork);
                    sb(zero, v0, kSmapTmxHidden);
                    v1 = addiu(v1, 1);
                }
                // 0x00429b94: place the layers (sub_42ADB0), draw the party marks (sub_42B050) and the shadow marks (sub_42B540)
                charge(ctx, 11);
                a0 = s4;
                jal(ctx, 0x429B98u, gen::fn_sub_42ADB0_0042adb0);
                a0 = s4;
                jal(ctx, 0x429BA4u, gen::fn_sub_42B050_0042b050);
                a0 = s4;
                jal(ctx, 0x429BB0u, gen::fn_sub_42B540_0042b540);
                goto L_00429bcc;
            case 0x429BC0u:  // table[19]
                // 0x00429bc0: state 19: return -1 (no map in this scene: the task ends)
                charge(ctx, 3);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x00429c1c (the shared epilogue, written out on this path)
            charge(ctx, 14);
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
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x180);
            return;
        }
        goto L_00429bcc;
    }
    // 0x00428240: map hidden: only the drawn states 14 (random floor) / 18 (fixed map) hide things; any other state goes on to the dispatch
    charge(ctx, 4);
    lb(v1, s1, kSmapWorkState);
    v0 = 14;
    if (v1 != v0) {
        // 0x00428250
        charge(ctx, 3);
        v0 = 18;
        if (v1 != v0) {
            goto L_00428388;
        }
        goto L_0042825c;
    }
L_0042825c:
    charge(ctx, 4);
    a1 = 0;
    v1 = 1;
    for (;;) {
        // 0x004282b0
        charge(ctx, 3);
        v0 = slti(a1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0042826c: hide every cell / layer tmx task: +92 + 128 z + 8 x (16 x 16 slots), its work +336 = 1
        charge(ctx, 5);
        a2 = 0;
        v0 = sll(a1, 7);
        a0 = addu(s1, v0);
        for (;;) {
            // 0x004282a0
            charge(ctx, 3);
            v0 = slti(a2, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00428280
            charge(ctx, 5);
            v0 = sll(a2, 3);
            v0 = addu(a0, v0);
            lw(v0, v0, kSmapWorkCellTasks);
            if (v0 != 0) {
                // 0x00428294
                charge(ctx, 2);
                lw(v0, v0, kTaskWork);
                sb(v1, v0, kSmapTmxHidden);
            }
            // 0x0042829c
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x004282ac
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x004282bc: the hero exists (gFldUnitsPc[0] +72 0x8717E8 and +84 0x8717F4): hide the direction arrow sub_456400(+2200, 0)
    charge(ctx, 5);
    v0 = 0x870000;
    lw(v0, v0, 6120);  // 0x8717E8
    v0 = sltu(0, v0);
    if (v0 != 0) {
        // 0x004282d0
        charge(ctx, 3);
        v0 = 0x870000;
        lw(v0, v0, 6132);  // 0x8717F4
        v0 = sltu(0, v0);
    }
    // 0x004282dc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004282e4
        charge(ctx, 3);
        lw(a0, s1, kSmapWorkSymbolTask);
        if (a0 != 0) {
            // 0x004282f0
            charge(ctx, 3);
            a1 = 0;
            jal(ctx, 0x4282F4u, gen::fn_sub_456400_00456400);
        }
    }
    // 0x004282fc: the four frame corner sprites (+76 + 4 i): +24 = 255 (hidden)
    charge(ctx, 4);
    a0 = 0;
    v1 = 255;
    for (;;) {
        // 0x00428328
        charge(ctx, 3);
        v0 = slti(a0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0042830c
        charge(ctx, 5);
        v0 = sll(a0, 2);
        v0 = addu(s1, v0);
        lw(v0, v0, kSmapWorkCorners);
        if (v0 != 0) {
            // 0x00428320
            charge(ctx, 1);
            sb(v1, v0, kSmapSprFade);
        }
        // 0x00428324
        charge(ctx, 1);
        a0 = addiu(a0, 1);
    }
    // 0x00428334: the stair icon task (+2844): sub_4302A0 [Y_Stair_Hide]; return 0 (no debug print on this path)
    charge(ctx, 3);
    lw(a0, s1, kSmapWorkStairTask);
    if (a0 != 0) {
        // 0x00428340
        charge(ctx, 2);
        jal(ctx, 0x428340u, gen::fn_sub_4302A0_004302a0);
    }
    // 0x00428348
    charge(ctx, 3);
    v0 = 0;
    // 0x00429c1c (the shared epilogue, written out on this path)
    charge(ctx, 14);
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
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x00429C60 sub_429C60 -- 212 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_DestroySmapDrawTask] The destroy callback of the "y_smap draw proc" task (passed to
// kwlnTaskCreateWithAutoPriority by Y_SMap_CreateSmapDrawTask; no direct caller). $a0 = the task. Releases the fixed
// map's nine textures at work +40 + 4 i (sub_4D0F00, the texture destroy) and the four frame corner sprite handles
// at +76 + 4 i (sub_115980), clearing each slot, then frees the work block through the RW free slot 0x96017C. The
// child tasks (cell tmx, stair icon, mask, box-fill, arrow) are not touched here.
void sub_429C60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00429c60: s2 = the task, s0 = its work
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, kTaskWork);
    s1 = 0;
    for (;;) {
        // 0x00429cb4
        charge(ctx, 3);
        v0 = slti(s1, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00429c8c: texture i (+40 + 4 i, i < 9): sub_4D0F00 and clear
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s3 = addiu(v0, kSmapWorkTex0);
        lw(a0, v0, kSmapWorkTex0);
        if (a0 != 0) {
            // 0x00429ca4
            charge(ctx, 3);
            jal(ctx, 0x429CA4u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s3, 0);
        }
        // 0x00429cb0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00429cc0
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00429cf4
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00429ccc: corner sprite i (+76 + 4 i, i < 4): sub_115980 and clear
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s3 = addiu(v0, kSmapWorkCorners);
        lw(a0, v0, kSmapWorkCorners);
        if (a0 != 0) {
            // 0x00429ce4
            charge(ctx, 3);
            jal(ctx, 0x429CE4u, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00429cf0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00429d00: free the work (*(task +60)) through 0x96017C
    charge(ctx, 13);
    lw(a0, s2, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x429D0Cu, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00429D40 Y_SMap_CreateSmapDrawTask -- 312 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_CreateSmapDrawTask] (bands.sym) Creates the Tartarus mini-map task. $a0 = the parent task, $a1 = the map's
// screen corner as two f32 (x low, y high; spilled to sp+0x38). Called by K_Field_UpdateFieldRootTask and
// K_FldEvent_UpdateFldEventTask. Only when sub_1DDD30 [K_Scene_HasMiniMap] says yes (sub_1A01C0
// [K_Scene_IsTartarus], except scenes 31/1, 32/2, 33/any, 35/1, 37/1): allocates the 2996-byte work (calloc-like
// 0x960184(1, 2996, 0x40000)) and creates "y_smap draw proc" (kwlnTaskCreateWithAutoPriority(parent, 4207, name,
// Y_SMap_UpdateSmapDrawTask, sub_429C60, work)). Initialises: corner +2140 / +2144, state 0, +2558 / +2559 = 0, view
// 7 cells (+2856), cell size 126 / 7 = 18 px (+2857), scene entry +2960 = -1, +2826 = 1, the shadow blink +2556 = 0,
// the party blinks +2354..+2358 = 0, frozen +2149 = 0, shown +2148 = 0 (the caller shows it later through
// sub_429E80) and the global gp-0x4614 (0x7CE6DC, tart::kGpSmapLock) = 0 until the map is set up. Returns $v0 = the
// task, or 0 (no map here / no memory).
void Y_SMap_CreateSmapDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00429d40: spill the corner pair ($a1) to sp+0x38; sub_1DDD30: does this scene have a mini-map?
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sd(a1, sp, 0x38);
    jal(ctx, 0x429D58u, gen::fn_sub_1DDD30_001ddd30);
    if (v0 != 0) {
        // 0x00429d74: allocate the 2996-byte work (0x960184)
        charge(ctx, 10);
        a0 = 1;
        a1 = 2996;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x429D88u, v0.u());
        s0 = v0;
        if (s0 != 0) {
            // 0x00429da8: create the task (priority 4207) and initialise the work: corner, state 0, 7 cells of 18 px, entry -1
            charge(ctx, 32);
            a0 = s1;
            a1 = 4207;
            a2 = 0x6B0000;
            a2 = addiu(a2, 17520);  // "y_smap draw proc"
            a3 = 0x430000;
            a3 = addiu(a3, -32272);  // &Y_SMap_UpdateSmapDrawTask
            t0 = 0x430000;
            t0 = addiu(t0, -25504);  // &sub_429C60
            t1 = s0;
            jal(ctx, 0x429DCCu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
            lwc1(f1, sp, 0x38);
            lwc1(f0, sp, 0x3C);
            swc1(f1, s0, kSmapWorkCornerX);
            swc1(f0, s0, kSmapWorkCornerY);
            sb(zero, s0, kSmapWorkState);
            sb(zero, s0, 2558);
            sb(zero, s0, 2559);
            a0 = 7;
            sb(a0, s0, kSmapWorkViewCells);
            v1 = 126;
            div(v1, a0);
            mflo(v1);
            sb(v1, s0, kSmapWorkCellPx);
            v1 = si(-1);
            sh(v1, s0, kSmapWorkSceneEntry);
            v1 = 1;
            sb(v1, s0, 2826);
            sh(zero, s0, kSmapWorkEcBlink);
            a1 = 0;
            for (;;) {
                // 0x00429e40
                charge(ctx, 5);
                a0 = dsll32(a1, 16);
                a0 = dsra32(a0, 16);
                v1 = slti(a0, 3);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00429e28: party blink phases +2354 + 2 i = 0 (i < 3)
                charge(ctx, 6);
                v1 = sll(a0, 1);
                v1 = addu(s0, v1);
                sh(zero, v1, kSmapWorkPcBlink1);
                v1 = addiu(a1, 1);
                a1 = dsll32(v1, 16);
                a1 = dsra32(a1, 16);
            }
            // 0x00429e54: not frozen, not shown; gp-0x4614 = 0
            charge(ctx, 3);
            sb(zero, s0, kSmapWorkFrozen);
            sb(zero, s0, kSmapWorkShown);
            sb(zero, gp, -17940);  // 0x7CE6DC
        } else {
            // 0x00429d9c: no memory: return 0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00429d68: no mini-map in this scene: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00429e60 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0042AA40 sub_42AA40 -- 540 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_RequestFixedMapFiles] For a non-floor Tartarus scene (state 15 of the mini-map update): $a0 = the mini-map
// task, $a1 = the scene major, $a2 = the minor (both from the scene record *(gp-0x57B0)). Clears the layer entries
// +2940..+2958 and the scene entry +2960 to -1, then scans the layout record of major - 31 in the table *(gp-0x4A40)
// (0x7CE2B0; 964-byte records: s32 count, 40-byte entries) for the entry whose u16 major / minor equal ($a1, $a2) ->
// +2960. If none, returns 0. Otherwise every entry with the same group (entry +4) is requested: its index -> +2940 +
// 2 k, "smap/s%03d_%03d.tmx" (major, entry minor) formatted into 0x95BEE0 (cleared first) and H_Cdvd_Request(name,
// 0) -> work +4 + 4 k. Returns $v0 = k, the number of files requested (s8; the update keeps it in +2858).
void sub_42AA40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0042aa40: s0 = the work, s4 = major; layer entries +2940 + 2 i = -1 (i < 10)
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    lw(s0, a0, kTaskWork);
    v0 = addiu(s4, -31);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    a1 = 0;
    v1 = si(-1);
    for (;;) {
        // 0x0042aa94
        charge(ctx, 3);
        v0 = slti(a1, 10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0042aa84
        charge(ctx, 4);
        v0 = sll(a1, 1);
        v0 = addu(s0, v0);
        sh(v1, v0, kSmapWorkLayerEntry);
        a1 = addiu(a1, 1);
    }
    // 0x0042aaa0: scene entry +2960 = -1; s2 = 964 (major - 31): the layout record's offset
    charge(ctx, 12);
    v0 = si(-1);
    sh(v0, s0, kSmapWorkSceneEntry);
    a3 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 4);
    v0 = subu(v0, v1);
    v0 = sll(v0, 4);
    v0 = addu(v0, v1);
    s2 = sll(v0, 2);
    for (;;) {
        // 0x0042ab00: loop over the record's entries (count at rec +0)
        charge(ctx, 6);
        lw(a1, gp, -19008);  // 0x7CE2B0
        v1 = addu(s2, a1);
        lw(v0, v1, kSmapLayoutCount);
        v0 = slt(a3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0042aad0: entry a3 (rec + 40 a3): major +8 == $a1 and minor +10 == $a2 -> +2960 = a3
        charge(ctx, 7);
        v0 = sll(a3, 2);
        v0 = addu(v0, a3);
        v0 = sll(v0, 3);
        v1 = addu(v1, v0);
        lhu(v0, v1, kSmapLayoutMajor);
        if (s4 == v0) {
            // 0x0042aaec
            charge(ctx, 3);
            lhu(v0, v1, kSmapLayoutMinor);
            if (a2 == v0) {
                // 0x0042aaf8
                charge(ctx, 1);
                sh(a3, s0, kSmapWorkSceneEntry);
            }
        }
        // 0x0042aafc
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x0042ab18
    charge(ctx, 4);
    lh(a0, s0, kSmapWorkSceneEntry);
    v0 = si(-1);
    if (a0 == v0) {
        // 0x0042ab44: no entry for this scene: return 0
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x0042ab28: the scene entry's group (+4)
        charge(ctx, 7);
        v0 = sll(a0, 2);
        v0 = addu(v0, a0);
        v0 = sll(v0, 3);
        v0 = addu(v0, v1);
        lb(v0, v0, kSmapLayoutGroup);
        // 0x0042ab50
        charge(ctx, 6);
        s1 = 0;
        s3 = 0;
        s5 = dsll32(v0, 24);
        s5 = dsra32(s5, 24);
        for (;;) {
            // 0x0042ac14: loop over the entries again
            charge(ctx, 6);
            lw(v0, gp, -19008);  // 0x7CE2B0
            v1 = addu(s2, v0);
            lw(v0, v1, kSmapLayoutCount);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0042ab68
            charge(ctx, 7);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            a0 = sll(v0, 3);
            v0 = addu(v1, a0);
            lw(v0, v0, kSmapLayoutGroup);
            if (s5 == v0) {
                // 0x0042ab84: same group: clear the name buffer 0x95BEE0 (255 bytes)
                charge(ctx, 5);
                a1 = 0;
                v1 = 0x960000;
                v1 = addiu(v1, -16672);  // &0x95BEE0
                for (;;) {
                    // 0x0042aba4
                    charge(ctx, 4);
                    v0 = slti(a1, 255);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042ab98
                    charge(ctx, 3);
                    v0 = addu(v1, a1);
                    sb(zero, v0, 0);
                    a1 = addiu(a1, 1);
                }
                // 0x0042abb4: +2940 + 2 k = the entry; sprintf "smap/s%03d_%03d.tmx" (major, entry minor); H_Cdvd_Request -> +4 + 4 k; k++
                charge(ctx, 23);
                v0 = sll(s3, 1);
                v0 = addu(s0, v0);
                sh(s1, v0, kSmapWorkLayerEntry);
                lw(v0, gp, -19008);  // 0x7CE2B0
                v0 = addu(s2, v0);
                v0 = addu(v0, a0);
                lhu(a3, v0, kSmapLayoutMinor);
                a0 = 0x960000;
                a0 = addiu(a0, -16672);  // &0x95BEE0
                a1 = 0x6B0000;
                a1 = addiu(a1, 17552);  // "smap/s%03d_%03d.tmx"
                a2 = s4;
                jal(ctx, 0x42ABE4u, gen::fn_sprintf_00523ac8);
                a0 = 0x960000;
                a0 = addiu(a0, -16672);  // &0x95BEE0
                a1 = 0;
                jal(ctx, 0x42ABF8u, gen::fn_H_Cdvd_Request_00100d80);
                v1 = sll(s3, 2);
                v1 = addu(s0, v1);
                sw(v0, v1, kSmapWorkFile0);
                s3 = addiu(s3, 1);
            }
            // 0x0042ac10
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x0042ac2c: return k (sign-extended byte)
        charge(ctx, 2);
        v0 = dsll32(s3, 24);
        v0 = dsra32(v0, 24);
    }
    // 0x0042ac34 (the shared epilogue, written out on this path)
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

// 0x0042AC60 sub_42AC60 -- 332 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_LoadFixedMapTextures] State 16 of the mini-map update, once every file of sub_42AA40 is loaded: $a0 = the
// mini-map task, $a1 = the scene major ($a2 the minor is passed but not used). Takes the group of the scene's layout
// entry (+2960) in the layout record of major - 31 (*(gp-0x4A40)) and, for every entry of that group in table order,
// formats "smap/s%03d_%03d" (major, entry minor) into 0x95BFE0 (cleared first) and loads the texture by that name
// (sub_4D1260(name, 0), the texture-by-name loader) into work +40 + 4 k. The same walk as sub_42AA40, so texture k
// matches file k.
void sub_42AC60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0042ac60: s1 = the work (a0 +60), s0 = 964 (major - 31); s5 = the group of the scene entry (+2960)
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    lw(s1, a0, kTaskWork);
    v1 = addiu(s4, -31);
    a0 = dsll32(v1, 24);
    a0 = dsra32(a0, 24);
    v1 = sll(a0, 4);
    v1 = subu(v1, a0);
    v1 = sll(v1, 4);
    v1 = addu(v1, a0);
    s0 = sll(v1, 2);
    lw(v1, gp, -19008);  // 0x7CE2B0
    a1 = addu(s0, v1);
    lh(a0, s1, kSmapWorkSceneEntry);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 3);
    v1 = addu(v1, a1);
    lb(s5, v1, kSmapLayoutGroup);
    s3 = 0;
    s2 = 0;
    for (;;) {
        // 0x0042ad6c: loop over the record's entries (count at rec +0)
        charge(ctx, 6);
        lw(v1, gp, -19008);  // 0x7CE2B0
        a0 = addu(s0, v1);
        lw(v1, a0, kSmapLayoutCount);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0042acd8
        charge(ctx, 7);
        v1 = sll(s3, 2);
        v1 = addu(v1, s3);
        v1 = sll(v1, 3);
        a0 = addu(a0, v1);
        lw(v1, a0, kSmapLayoutGroup);
        if (s5 == v1) {
            // 0x0042acf4: same group: clear the name buffer 0x95BFE0 (255 bytes)
            charge(ctx, 5);
            a1 = 0;
            v1 = 0x960000;
            v1 = addiu(v1, -16416);  // &0x95BFE0
            for (;;) {
                // 0x0042ad14
                charge(ctx, 4);
                v0 = slti(a1, 255);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0042ad08
                charge(ctx, 3);
                v0 = addu(v1, a1);
                sb(zero, v0, 0);
                a1 = addiu(a1, 1);
            }
            // 0x0042ad24: sprintf "smap/s%03d_%03d" (major, entry minor); sub_4D1260 -> texture +40 + 4 k; k++
            charge(ctx, 17);
            lhu(a3, a0, kSmapLayoutMinor);
            a0 = 0x960000;
            a0 = addiu(a0, -16416);  // &0x95BFE0
            a1 = 0x6B0000;
            a1 = addiu(a1, 17584);  // "smap/s%03d_%03d"
            a2 = s4;
            jal(ctx, 0x42AD3Cu, gen::fn_sprintf_00523ac8);
            a0 = 0x960000;
            a0 = addiu(a0, -16416);  // &0x95BFE0
            a1 = 0;
            jal(ctx, 0x42AD50u, gen::fn_sub_4D1260_004d1260);
            v1 = sll(s2, 2);
            v1 = addu(s1, v1);
            sw(v0, v1, kSmapWorkTex0);
            s2 = addiu(s2, 1);
        }
        // 0x0042ad68
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x0042ad84
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

// 0x004302B0 sub_4302B0 -- 892 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_LoadResources] Boot-time load of the mini-map's shared resources, called once from kwlnInitMain; no
// arguments. Reads smap/i_mini_map01.spr synchronously (H_Cdvd_Request + H_Cdvd_ReadSync), adds it as a sprite file
// (sprAddFile -> gp-0x460C 0x7CE6E4, tart::kGpSmapSprite) and spins (sub_1120C0) until sprFileIsReady, then loads
// nine textures smap/smap0.tmx .. smap/smap8.tmx by name (sub_4D1260) into the table 0x95C0E0..0x95C100 (u32 [9])
// and smap/symbol/smap_p.tmx into gp-0x4610 (0x7CE6E0; tartarus.h calls it symbol_smap.tmx), destroying each file
// handle after use. Note: nine room textures (0..8), not eight.
void sub_4302B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004302b0: read smap/i_mini_map01.spr and add it as the sprite file gp-0x460C
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17680);  // "smap/i_mini_map01.spr"
    a1 = 0;
    jal(ctx, 0x4302C8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4302D8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17680);  // "smap/i_mini_map01.spr"
    jal(ctx, 0x4302E8u, gen::fn_sprAddFile_00112370);
    sw(v0, gp, -17932);  // 0x7CE6E4
    for (;;) {
        // 0x004302f4: spin (sub_1120C0) until sprFileIsReady
        charge(ctx, 9);
        jal(ctx, 0x4302F4u, gen::fn_sub_1120C0_001120c0);
        lw(a0, gp, -17932);  // 0x7CE6E4
        jal(ctx, 0x430300u, gen::fn_sprFileIsReady_00111f30);
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00430318: smap0..smap8.tmx -> 0x95C0E0 + 4 i, then smap/symbol/smap_p.tmx -> gp-0x4610; each read sync, loaded by name, destroyed
    charge(ctx, 197);
    a0 = s0;
    jal(ctx, 0x43031Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17704);  // "smap/smap0.tmx"
    a1 = 0;
    jal(ctx, 0x430330u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x430340u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17704);  // "smap/smap0.tmx"
    a1 = 0;
    jal(ctx, 0x430354u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16160);  // 0x95C0E0
    a0 = s0;
    jal(ctx, 0x430368u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17720);  // "smap/smap1.tmx"
    a1 = 0;
    jal(ctx, 0x43037Cu, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x43038Cu, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17720);  // "smap/smap1.tmx"
    a1 = 0;
    jal(ctx, 0x4303A0u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16156);  // 0x95C0E4
    a0 = s0;
    jal(ctx, 0x4303B4u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17736);  // "smap/smap2.tmx"
    a1 = 0;
    jal(ctx, 0x4303C8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4303D8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17736);  // "smap/smap2.tmx"
    a1 = 0;
    jal(ctx, 0x4303ECu, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16152);  // 0x95C0E8
    a0 = s0;
    jal(ctx, 0x430400u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17752);  // "smap/smap3.tmx"
    a1 = 0;
    jal(ctx, 0x430414u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x430424u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17752);  // "smap/smap3.tmx"
    a1 = 0;
    jal(ctx, 0x430438u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16148);  // 0x95C0EC
    a0 = s0;
    jal(ctx, 0x43044Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17768);  // "smap/smap4.tmx"
    a1 = 0;
    jal(ctx, 0x430460u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x430470u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17768);  // "smap/smap4.tmx"
    a1 = 0;
    jal(ctx, 0x430484u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16144);  // 0x95C0F0
    a0 = s0;
    jal(ctx, 0x430498u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17784);  // "smap/smap5.tmx"
    a1 = 0;
    jal(ctx, 0x4304ACu, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4304BCu, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17784);  // "smap/smap5.tmx"
    a1 = 0;
    jal(ctx, 0x4304D0u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16140);  // 0x95C0F4
    a0 = s0;
    jal(ctx, 0x4304E4u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17800);  // "smap/smap6.tmx"
    a1 = 0;
    jal(ctx, 0x4304F8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x430508u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17800);  // "smap/smap6.tmx"
    a1 = 0;
    jal(ctx, 0x43051Cu, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16136);  // 0x95C0F8
    a0 = s0;
    jal(ctx, 0x430530u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17816);  // "smap/smap7.tmx"
    a1 = 0;
    jal(ctx, 0x430544u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x430554u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17816);  // "smap/smap7.tmx"
    a1 = 0;
    jal(ctx, 0x430568u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16132);  // 0x95C0FC
    a0 = s0;
    jal(ctx, 0x43057Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17832);  // "smap/smap8.tmx"
    a1 = 0;
    jal(ctx, 0x430590u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4305A0u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17832);  // "smap/smap8.tmx"
    a1 = 0;
    jal(ctx, 0x4305B4u, gen::fn_sub_4D1260_004d1260);
    v1 = 0x960000;
    sw(v0, v1, -16128);  // 0x95C100
    a0 = s0;
    jal(ctx, 0x4305C8u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17856);  // "smap/symbol/smap_p.tmx"
    a1 = 0;
    jal(ctx, 0x4305DCu, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x4305ECu, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6B0000;
    a0 = addiu(a0, 17856);  // "smap/symbol/smap_p.tmx"
    a1 = 0;
    jal(ctx, 0x430600u, gen::fn_sub_4D1260_004d1260);
    sw(v0, gp, -17936);  // 0x7CE6E0
    a0 = s0;
    jal(ctx, 0x430610u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00431110 Y_SMap_CreateSmapMaskDrawTask -- 224 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SMap_CreateSmapMaskDrawTask] (bands.sym) Creates the "y_smap mask draw " task that masks the screen around the
// mini-map: $a0 = the parent (the mini-map task), $a1 = the map corner as two f32 (spilled to sp+0x58), $a2 = the
// view size in cells (s8, the map's +2856 = 7), $a3 = the layout (0 random floor from states 2 / 12, 1 fixed map
// from state 17). Allocates 128 bytes (0x960184), kwlnTaskCreate(parent, name, 6310, Y_SMap_UpdateSmapMaskDrawTask
// 0x430BB0, sub_4310E0 = free the work, work), then work +0 = 0, +20 / +24 = the corner, +124 = cells / 2 (rounded
// toward zero), +125 = the layout. Returns $v0 = the task (the mini-map keeps it in +2852), 0 without memory.
void Y_SMap_CreateSmapMaskDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00431110: spill the corner pair; allocate the 128-byte work
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    sd(a1, sp, 0x58);
    s2 = a2;
    s0 = a3;
    a0 = 1;
    a1 = 128;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x43114Cu, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x0043116c: create the task (priority 6310); state 0, corner +20 / +24
        charge(ctx, 21);
        a0 = s3;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17888);  // "y_smap mask draw "
        a2 = 6310;
        a3 = 0x430000;
        a3 = addiu(a3, 2992);  // &Y_SMap_UpdateSmapMaskDrawTask
        t0 = 0x430000;
        t0 = addiu(t0, 4320);  // &sub_4310E0
        t1 = s1;
        jal(ctx, 0x431190u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s1, kSmapMaskState);
        lwc1(f1, sp, 0x58);
        lwc1(f0, sp, 0x5C);
        swc1(f1, s1, kSmapMaskCornerX);
        swc1(f0, s1, kSmapMaskCornerY);
        a0 = dsll32(s2, 24);
        a0 = dsra32(a0, 24);
        v1 = sra(a0, 1);
        if (i64(a0) < 0) {
            // 0x004311c0
            charge(ctx, 2);
            v1 = addiu(a0, 1);
            v1 = sra(v1, 1);
        }
        // 0x004311c8: +124 = cells / 2, +125 = the layout
        charge(ctx, 2);
        sb(v1, s1, kSmapMaskHalfCells);
        sb(s0, s1, kSmapMaskLayout);
    } else {
        // 0x00431160: no memory: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004311d0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004312B0 Y_Npc_UpdateNpcThinkTask -- 896 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateNpcThinkTask] The update of a party member's "npc think proc" task ($a0 = the task; work = task +60,
// the party think work). Only while the member's field unit is live (+72 and +84 of gFldUnitsPc[pc]) and not held
// (kNpcHeld): a member at 0 HP (sub_43C910) goes to mode 6; a pending mode-change script (sub_43A2F0), skill use
// (sub_43A960) or support-skill walk (sub_43BF50) runs instead of the mode; else the mode: 6 back to follow /
// explore once revived, 5 the skirmish (sub_439520), 2 explore (sub_438010, kNpcExploring = 1), 1 follow
// (sub_435C00, kNpcExploring = 0), 0 place the member on the hero's cell and pick follow / explore from the tactic
// 0x7CE6BC. Returns 0.
void Y_Npc_UpdateNpcThinkTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004312b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    a1 = 0;
    lw(a0, s0, kNpcPc);
    v0 = sll(a0, 3);
    v0 = subu(v0, a0);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6120);  // &0x8717E8
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x004312f4
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6132);  // &0x8717F4
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x0043130c
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x00431310
    charge(ctx, 3);
    v0 = sltu(0, a1);
    if (v0 != 0) {
        // 0x00431328
        charge(ctx, 4);
        lb(v1, s0, kNpcHeld);
        v0 = 1;
        if (v1 != v0) {
            // 0x00431344
            charge(ctx, 7);
            a0 = dsll32(a0, 24);
            a0 = dsra32(a0, 24);
            jal(ctx, 0x43134Cu, gen::fn_sub_43C910_0043c910);
            v0 = v0 & 0xFFFF;
            if (i64(v0) > 0) {
                // 0x00431374
                charge(ctx, 4);
                lb(v0, s0, kNpcModeChange);
                a0 = 1;
                if (v0 != a0) {
                    // 0x0043139c
                    charge(ctx, 3);
                    lb(v0, s0, kNpcSkillUse);
                    if (v0 != a0) {
                        // 0x004313c0
                        charge(ctx, 3);
                        lb(v0, s0, kNpcSupport);
                        if (v0 != a0) {
                            // 0x004313e4
                            charge(ctx, 4);
                            lb(v1, s0, kNpcMode);
                            v0 = 6;
                            if (v1 == v0) {
                                // 0x004315b0: mode 6 (down): back to follow / explore when alive again
                                charge(ctx, 12);
                                lw(v1, s0, kNpcPc);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = 0x870000;
                                v0 = addiu(v0, 6120);  // &0x8717E8
                                v0 = addu(v0, v1);
                                lw(a0, v0, 0);
                                jal(ctx, 0x4315D0u, gen::fn_datUnitIsGenusDead_002ff790);
                                if (v0 == 0) {
                                    // 0x004315e0
                                    charge(ctx, 3);
                                    lb(v0, gp, -17972);  // 0x7CE6BC
                                    if (v0 != 0) {
                                        // 0x00431604
                                        charge(ctx, 4);
                                        lb(a0, s0, kNpcPc);
                                        a1 = 2;
                                        jal(ctx, 0x43160Cu, gen::fn_sub_43C7A0_0043c7a0);
                                    } else {
                                        // 0x004315ec
                                        charge(ctx, 6);
                                        lb(a0, s0, kNpcPc);
                                        a1 = 1;
                                        jal(ctx, 0x4315F4u, gen::fn_sub_43C7A0_0043c7a0);
                                    }
                                }
                            } else {
                                // 0x004313f4
                                charge(ctx, 3);
                                v0 = 5;
                                if (v1 == v0) {
                                    // 0x0043159c: mode 5: the skirmish
                                    charge(ctx, 5);
                                    a0 = s1;
                                    jal(ctx, 0x4315A0u, gen::fn_sub_439520_00439520);
                                } else {
                                    // 0x00431400
                                    charge(ctx, 3);
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x00431580: mode 2: explore
                                        charge(ctx, 7);
                                        a0 = s1;
                                        jal(ctx, 0x431584u, gen::fn_sub_438010_00438010);
                                        v0 = 1;
                                        sb(v0, s0, kNpcExploring);
                                    } else {
                                        // 0x0043140c
                                        charge(ctx, 2);
                                        if (v1 == a0) {
                                            // 0x00431568: mode 1: follow the hero
                                            charge(ctx, 6);
                                            a0 = s1;
                                            jal(ctx, 0x43156Cu, gen::fn_sub_435C00_00435c00);
                                            sb(zero, s0, kNpcExploring);
                                        } else {
                                            // 0x00431414
                                            charge(ctx, 2);
                                            if (v1 == 0) {
                                                // 0x00431424: mode 0: start on the hero's cell, then the tactic picks mode 1 or 2 (6 when dead)
                                                charge(ctx, 37);
                                                v0 = 0x870000;
                                                lw(v0, v0, 6132);  // 0x8717F4
                                                lw(a0, v0, 480);
                                                jal(ctx, 0x431430u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                                                s1 = v0 & 0xFF;
                                                v0 = 0x870000;
                                                lw(v0, v0, 6132);  // 0x8717F4
                                                lw(a0, v0, 480);
                                                jal(ctx, 0x431448u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                                                a2 = v0 & 0xFF;
                                                a0 = addiu(sp, 0x30);
                                                a1 = s1;
                                                jal(ctx, 0x43145Cu, gen::fn_sub_4311F0_004311f0);
                                                a0 = addiu(s0, kNpcCellPosX);
                                                lwc1(f2, sp, 0x30);
                                                lwc1(f1, sp, 0x34);
                                                lwc1(f0, sp, 0x38);
                                                swc1(f2, s0, kNpcCellPosX);
                                                swc1(f1, s0, kNpcCellPosY);
                                                swc1(f0, s0, kNpcCellPosZ);
                                                jal(ctx, 0x431480u, gen::fn_sub_44F120_0044f120);
                                                sb(v0, s0, kNpcCellX);
                                                a0 = addiu(s0, kNpcCellPosX);
                                                jal(ctx, 0x431490u, gen::fn_sub_44F170_0044f170);
                                                sb(v0, s0, kNpcCellZ);
                                                lb(v0, s0, kNpcCellX);
                                                sb(v0, s0, kNpcWalkX);
                                                lb(v0, s0, kNpcCellZ);
                                                sb(v0, s0, kNpcWalkZ);
                                                lb(v1, gp, -17972);  // 0x7CE6BC
                                                if (v1 != 0) {
                                                    // 0x004314d4
                                                    charge(ctx, 3);
                                                    a1 = 1;
                                                    if (v1 != a1) {
                                                        // 0x00431500
                                                        charge(ctx, 3);
                                                        v0 = 2;
                                                        if (v1 == v0) {
                                                            // 0x0043150c
                                                            charge(ctx, 4);
                                                            lb(a0, s0, kNpcPc);
                                                            jal(ctx, 0x431510u, gen::fn_sub_43C7A0_0043c7a0);
                                                            sb(zero, s0, kNpcExploring);
                                                        }
                                                    } else {
                                                        // 0x004314e0
                                                        charge(ctx, 8);
                                                        lb(a0, s0, kNpcPc);
                                                        a1 = 2;
                                                        jal(ctx, 0x4314E8u, gen::fn_sub_43C7A0_0043c7a0);
                                                        v0 = 1;
                                                        sb(v0, s0, kNpcExploring);
                                                    }
                                                } else {
                                                    // 0x004314b8
                                                    charge(ctx, 7);
                                                    lb(a0, s0, kNpcPc);
                                                    a1 = 1;
                                                    jal(ctx, 0x4314C0u, gen::fn_sub_43C7A0_0043c7a0);
                                                    sb(zero, s0, kNpcExploring);
                                                }
                                                // 0x0043151c
                                                charge(ctx, 13);
                                                lw(v1, s0, kNpcPc);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = 0x870000;
                                                v0 = addiu(v0, 6120);  // &0x8717E8
                                                v0 = addu(v0, v1);
                                                lw(a0, v0, 0);
                                                jal(ctx, 0x43153Cu, gen::fn_datUnitIsGenusDead_002ff790);
                                                v1 = 1;
                                                if (v0 == v1) {
                                                    // 0x00431550
                                                    charge(ctx, 6);
                                                    lb(a0, s0, kNpcPc);
                                                    a1 = 6;
                                                    jal(ctx, 0x431558u, gen::fn_sub_43C7A0_0043c7a0);
                                                }
                                            } else {
                                                // 0x0043141c
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                            // 0x00431614
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x004313cc: support-skill walk pending
                            charge(ctx, 6);
                            a0 = s1;
                            jal(ctx, 0x4313D0u, gen::fn_sub_43BF50_0043bf50);
                            v0 = 0;
                        }
                    } else {
                        // 0x004313a8: skill use pending
                        charge(ctx, 6);
                        a0 = s1;
                        jal(ctx, 0x4313ACu, gen::fn_sub_43A960_0043a960);
                        v0 = 0;
                    }
                } else {
                    // 0x00431384: mode-change script pending
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x431388u, gen::fn_sub_43A2F0_0043a2f0);
                    v0 = 0;
                }
            } else {
                // 0x00431360: HP 0 (sub_43C910): mode 6
                charge(ctx, 5);
                v0 = 6;
                sb(v0, s0, kNpcMode);
                v0 = 0;
            }
        } else {
            // 0x00431338: held (kNpcHeld == 1): return 0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0043131c: the unit is not live: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00431618 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00431630 sub_431630 -- 64 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_DestroyNpcThinkTask] Destroy callback of "npc think proc": the member's place in the hero's column
// (0x7CE6E7 + pc) = 0, then frees the work through the RW free slot 0x96017C (jalr).
void sub_431630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00431630
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v0 = addiu(gp, -17929);  // &0x7CE6E7
    v0 = addu(v0, v1);
    sb(zero, v0, 0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x431658u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00431670 Y_Npc_CreateNpcThinkTask -- 516 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CreateNpcThinkTask] ($a0 parent, $a1 party slot pc, $a2 the member's field unit) calloc(1, 4708) through
// the RW slot 0x960184, the task "npc think proc" (priority 10, update Y_Npc_UpdateNpcThinkTask, destroy
// sub_431630), the hero's and the member's scene resources, mode 0, the wall-following rule by slot (1 -> 0, 2 -> 1,
// 3 -> 2), facing 1; a mode kept in the unit (+410 of gFldUnitsPc[pc]) is restored with kNpcExploring from the
// tactic; held when the unit's +412 == 1. Returns the task (0 when the allocation failed). Called by the field-unit
// band (sub_1CE960, sub_1D0E50).
void Y_Npc_CreateNpcThinkTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00431670
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    s3 = a2;
    a0 = 1;
    a1 = 4708;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x4316A8u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x004316c8
        charge(ctx, 33);
        a0 = s2;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 17912);  // "npc think proc"
        a3 = 0x430000;
        a3 = addiu(a3, 4784);  // &Y_Npc_UpdateNpcThinkTask
        t0 = 0x430000;
        t0 = addiu(t0, 5680);  // &sub_431630
        t1 = s1;
        jal(ctx, 0x4316ECu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s2 = v0;
        a0 = 1024;
        jal(ctx, 0x4316FCu, gen::fn_sub_3B5D10_003b5d10);
        sw(v0, s1, kNpcHeroRes);
        s0 = dsll32(s0, 24);
        s0 = dsra32(s0, 24);
        v0 = s0 & 0x3FF;
        v0 = v0 | 0x400;
        a0 = v0 & 0xFFFF;
        jal(ctx, 0x43171Cu, gen::fn_sub_3B5D10_003b5d10);
        sw(v0, s1, kNpcOwnRes);
        sb(zero, s1, kNpcByte0);
        sb(zero, s1, kNpcFollowState);
        sb(zero, s1, kNpcExploreState);
        sb(zero, s1, kNpcMode);
        sw(s0, s1, kNpcPc);
        sw(s3, s1, kNpcUnit);
        v0 = 3;
        if (s0 == v0) {
            // 0x00431788
            charge(ctx, 2);
            v0 = 2;
            sb(v0, s1, kNpcHand);
        } else {
            // 0x0043174c
            charge(ctx, 3);
            v0 = 2;
            if (s0 == v0) {
                // 0x00431778
                charge(ctx, 4);
                v0 = 1;
                sb(v0, s1, kNpcHand);
            } else {
                // 0x00431758
                charge(ctx, 3);
                v0 = 1;
                if (s0 == v0) {
                    // 0x0043176c
                    charge(ctx, 3);
                    sb(zero, s1, kNpcHand);
                } else {
                    // 0x00431764
                    charge(ctx, 2);
                }
            }
        }
        // 0x00431790
        charge(ctx, 24);
        a1 = 1;
        sb(a1, s1, kNpcFacing);
        sb(zero, s1, kNpcByte263);
        sb(zero, s1, 264);
        sb(zero, s1, kNpcExploring);
        lw(v1, s1, kNpcPc);
        v0 = addiu(gp, -17929);  // &0x7CE6E7
        v0 = addu(v0, v1);
        sb(zero, v0, 0);
        sb(zero, s1, kNpcHeld);
        lb(v0, gp, -20960);  // 0x7CDB10
        sb(v0, s1, kNpcAvoidFights);
        sb(zero, s1, kNpcModeChange);
        sb(zero, s1, kNpcSkillUse);
        sb(zero, s1, kNpcByte4667);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        a0 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6458);  // &0x87193A
        v0 = addu(v0, a0);
        lb(v0, v0, 0);
        if (v0 != 0) {
            // 0x004317f0
            charge(ctx, 4);
            sb(v0, s1, kNpcMode);
            lb(v1, gp, -17972);  // 0x7CE6BC
            if (v1 != 0) {
                // 0x0043180c
                charge(ctx, 2);
                if (v1 != a1) {
                    // 0x00431820
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x0043182c
                        charge(ctx, 1);
                        sb(zero, s1, kNpcExploring);
                    }
                } else {
                    // 0x00431814
                    charge(ctx, 3);
                    sb(a1, s1, kNpcExploring);
                }
            } else {
                // 0x00431800
                charge(ctx, 3);
                sb(zero, s1, kNpcExploring);
            }
        }
        // 0x00431830
        charge(ctx, 7);
        v0 = 0x870000;
        v0 = addiu(v0, 6460);  // &0x87193C
        v0 = addu(v0, a0);
        lb(v1, v0, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x0043184c
            charge(ctx, 1);
            sb(v0, s1, kNpcHeld);
        }
        // 0x00431850
        charge(ctx, 1);
        v0 = s2;
    } else {
        // 0x004316bc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00431854 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00431880 sub_431880 -- 540 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CountVisit] Explore helper ($a0 task): the current cell from +208, the walk cell = it, +1 on its visit
// count; returns 1 on every 3rd visit of a kind-3 cell or every 4th of a kind-1 cell for member 2, every 5th / 9th
// for the others (the caller then turns towards the least visited side, sub_4339D0), else 0.
void sub_431880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00431880
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 60);
    a0 = addiu(s2, kNpcCellPosX);
    jal(ctx, 0x43189Cu, gen::fn_sub_44F120_0044f120);
    sb(v0, s2, kNpcCellX);
    a0 = addiu(s2, kNpcCellPosX);
    jal(ctx, 0x4318ACu, gen::fn_sub_44F170_0044f170);
    sb(v0, s2, kNpcCellZ);
    lb(v0, s2, kNpcCellX);
    sb(v0, s2, kNpcWalkX);
    lb(v0, s2, kNpcCellZ);
    sb(v0, s2, kNpcWalkZ);
    lb(v0, s2, kNpcCellX);
    v1 = addu(v0, s2);
    lb(v0, s2, kNpcCellZ);
    v0 = sll(v0, 4);
    v1 = addu(v0, v1);
    lbu(v0, v1, 265);
    v0 = addiu(v0, 1);
    sb(v0, v1, 265);
    lw(v1, s2, kNpcPc);
    v0 = 2;
    if (v1 == v0) {
        // 0x004319b4
        charge(ctx, 11);
        lb(s1, s2, kNpcCellZ);
        lb(s0, s2, kNpcCellX);
        v1 = addu(s0, s2);
        v0 = sll(s1, 4);
        v0 = addu(v0, v1);
        lbu(v1, v0, 265);
        v0 = 3;
        div(v1, v0);
        mfhi(v0);
        if (v0 == 0) {
            // 0x004319e0
            charge(ctx, 10);
            jal(ctx, 0x4319E0u, gen::fn_K_Field_Get_001b9120);
            v1 = sll(s1, 8);
            v1 = addu(v0, v1);
            v0 = sll(s0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 3;
            if (v1 != v0) {
                goto L_00431a14;
            }
            // 0x00431a08
            charge(ctx, 3);
            v0 = 1;
            // 0x00431a80 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_00431a14:
        charge(ctx, 7);
        v1 = addu(s0, s2);
        v0 = sll(s1, 4);
        v0 = addu(v0, v1);
        lbu(v1, v0, 265);
        v0 = v1 & 0x3;
        if (i64(v1) < 0) {
            // 0x00431a30
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x00431a38
                charge(ctx, 1);
                v0 = addiu(v0, -4);
            }
        }
        // 0x00431a3c
        charge(ctx, 2);
        if (v0 != 0) {
        L_00431a7c:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00431a44
            charge(ctx, 12);
            jal(ctx, 0x431A44u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s2, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s2, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 1;
            if (v1 != v0) {
                goto L_00431a7c;
            }
            // 0x00431a74
            charge(ctx, 2);
        }
    } else {
        // 0x004318f8
        charge(ctx, 11);
        lb(s1, s2, kNpcCellZ);
        lb(s0, s2, kNpcCellX);
        v1 = addu(s0, s2);
        v0 = sll(s1, 4);
        v0 = addu(v0, v1);
        lbu(v1, v0, 265);
        v0 = 5;
        div(v1, v0);
        mfhi(v0);
        if (v0 == 0) {
            // 0x00431924
            charge(ctx, 10);
            jal(ctx, 0x431924u, gen::fn_K_Field_Get_001b9120);
            v1 = sll(s1, 8);
            v1 = addu(v0, v1);
            v0 = sll(s0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 3;
            if (v1 != v0) {
                goto L_00431958;
            }
            // 0x0043194c
            charge(ctx, 3);
            v0 = 1;
            // 0x00431a80 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_00431958:
        charge(ctx, 9);
        v1 = addu(s0, s2);
        v0 = sll(s1, 4);
        v0 = addu(v0, v1);
        lbu(v1, v0, 265);
        v0 = 9;
        div(v1, v0);
        mfhi(v0);
        if (v0 != 0) {
            goto L_00431a7c;
        }
        // 0x0043197c
        charge(ctx, 12);
        jal(ctx, 0x43197Cu, gen::fn_K_Field_Get_001b9120);
        lb(v1, s2, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s2, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v1, v0, 74);
        v0 = 1;
        if (v1 != v0) {
            goto L_00431a7c;
        }
        // 0x004319ac
        charge(ctx, 2);
    }
    // 0x00431a80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00431AA0 sub_431AA0 -- 1456 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WallFollow0] Explore helper ($a0 task), wall-following rule 0: by the facing (+258, 1..4) it tries the
// current cell's open sides (grid cell +11 bits 1 / 2 / 4 / 8) in this rule's order, steps the walk cell (+248 /
// +249) to the first open one and returns its direction 1..4 (0 when none); the step runs the rule-flip check
// (sub_4332F0 for rules 0 / 1, sub_4333D0 for 2 / 3).
void sub_431AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00431aa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lb(v1, s0, kNpcFacing);
    v0 = 4;
    if (v1 == v0) {
        // 0x00431ee4
        charge(ctx, 12);
        jal(ctx, 0x431EE4u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s0, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00431f38
            charge(ctx, 12);
            jal(ctx, 0x431F38u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x8;
            if (v0 == 0) {
                // 0x00431f8c
                charge(ctx, 12);
                jal(ctx, 0x431F8Cu, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x00431fe0
                    charge(ctx, 12);
                    jal(ctx, 0x431FE0u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                    L_00432034:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x00432010
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x432020u, gen::fn_sub_4332F0_004332f0);
                        v0 = 2;
                    }
                } else {
                    // 0x00431fbc
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x431FCCu, gen::fn_sub_4332F0_004332f0);
                    v0 = 3;
                }
            } else {
                // 0x00431f68
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkX);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkX);
                a0 = s1;
                jal(ctx, 0x431F78u, gen::fn_sub_4332F0_004332f0);
                v0 = 4;
            }
        } else {
            // 0x00431f14
            charge(ctx, 9);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, -1);
            sb(v0, s0, kNpcWalkZ);
            a0 = s1;
            jal(ctx, 0x431F24u, gen::fn_sub_4332F0_004332f0);
            v0 = 1;
        }
    } else {
        // 0x00431ac8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00431d94
            charge(ctx, 12);
            jal(ctx, 0x431D94u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x8;
            if (v0 == 0) {
                // 0x00431de8
                charge(ctx, 12);
                jal(ctx, 0x431DE8u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x00431e3c
                    charge(ctx, 12);
                    jal(ctx, 0x431E3Cu, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x00431e90
                        charge(ctx, 12);
                        jal(ctx, 0x431E90u, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            goto L_00432034;
                        }
                        // 0x00431ec0
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x431ED0u, gen::fn_sub_4332F0_004332f0);
                        v0 = 1;
                    } else {
                        // 0x00431e6c
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x431E7Cu, gen::fn_sub_4332F0_004332f0);
                        v0 = 2;
                    }
                } else {
                    // 0x00431e18
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x431E28u, gen::fn_sub_4332F0_004332f0);
                    v0 = 3;
                }
            } else {
                // 0x00431dc4
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkX);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkX);
                a0 = s1;
                jal(ctx, 0x431DD4u, gen::fn_sub_4332F0_004332f0);
                v0 = 4;
            }
        } else {
            // 0x00431ad4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00431c44
                charge(ctx, 12);
                jal(ctx, 0x431C44u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x00431c98
                    charge(ctx, 12);
                    jal(ctx, 0x431C98u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x00431cec
                        charge(ctx, 12);
                        jal(ctx, 0x431CECu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            // 0x00431d40
                            charge(ctx, 12);
                            jal(ctx, 0x431D40u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x8;
                            if (v0 == 0) {
                                goto L_00432034;
                            }
                            // 0x00431d70
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x431D80u, gen::fn_sub_4332F0_004332f0);
                            v0 = 4;
                        } else {
                            // 0x00431d1c
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, -1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x431D2Cu, gen::fn_sub_4332F0_004332f0);
                            v0 = 1;
                        }
                    } else {
                        // 0x00431cc8
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x431CD8u, gen::fn_sub_4332F0_004332f0);
                        v0 = 2;
                    }
                } else {
                    // 0x00431c74
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x431C84u, gen::fn_sub_4332F0_004332f0);
                    v0 = 3;
                }
            } else {
                // 0x00431ae0
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x00431aec
                    charge(ctx, 2);
                    goto L_00432034;
                }
                // 0x00431af4
                charge(ctx, 12);
                jal(ctx, 0x431AF4u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x00431b48
                    charge(ctx, 12);
                    jal(ctx, 0x431B48u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x00431b9c
                        charge(ctx, 12);
                        jal(ctx, 0x431B9Cu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x8;
                        if (v0 == 0) {
                            // 0x00431bf0
                            charge(ctx, 12);
                            jal(ctx, 0x431BF0u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x4;
                            if (v0 == 0) {
                                goto L_00432034;
                            }
                            // 0x00431c20
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x431C30u, gen::fn_sub_4332F0_004332f0);
                            v0 = 3;
                        } else {
                            // 0x00431bcc
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x431BDCu, gen::fn_sub_4332F0_004332f0);
                            v0 = 4;
                        }
                    } else {
                        // 0x00431b78
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x431B88u, gen::fn_sub_4332F0_004332f0);
                        v0 = 1;
                    }
                } else {
                    // 0x00431b24
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x431B34u, gen::fn_sub_4332F0_004332f0);
                    v0 = 2;
                }
            }
        }
    }
    // 0x00432038 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00432050 sub_432050 -- 1456 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WallFollow1] Explore helper ($a0 task), wall-following rule 1: by the facing (+258, 1..4) it tries the
// current cell's open sides (grid cell +11 bits 1 / 2 / 4 / 8) in this rule's order, steps the walk cell (+248 /
// +249) to the first open one and returns its direction 1..4 (0 when none); the step runs the rule-flip check
// (sub_4332F0 for rules 0 / 1, sub_4333D0 for 2 / 3).
void sub_432050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00432050
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lb(v1, s0, kNpcFacing);
    v0 = 4;
    if (v1 == v0) {
        // 0x00432494
        charge(ctx, 12);
        jal(ctx, 0x432494u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s0, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x004324e8
            charge(ctx, 12);
            jal(ctx, 0x4324E8u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x8;
            if (v0 == 0) {
                // 0x0043253c
                charge(ctx, 12);
                jal(ctx, 0x43253Cu, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00432590
                    charge(ctx, 12);
                    jal(ctx, 0x432590u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                    L_004325e4:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x004325c0
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x4325D0u, gen::fn_sub_4332F0_004332f0);
                        v0 = 2;
                    }
                } else {
                    // 0x0043256c
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x43257Cu, gen::fn_sub_4332F0_004332f0);
                    v0 = 1;
                }
            } else {
                // 0x00432518
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkX);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkX);
                a0 = s1;
                jal(ctx, 0x432528u, gen::fn_sub_4332F0_004332f0);
                v0 = 4;
            }
        } else {
            // 0x004324c4
            charge(ctx, 9);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkZ);
            a0 = s1;
            jal(ctx, 0x4324D4u, gen::fn_sub_4332F0_004332f0);
            v0 = 3;
        }
    } else {
        // 0x00432078
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00432344
            charge(ctx, 12);
            jal(ctx, 0x432344u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x00432398
                charge(ctx, 12);
                jal(ctx, 0x432398u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x004323ec
                    charge(ctx, 12);
                    jal(ctx, 0x4323ECu, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x8;
                    if (v0 == 0) {
                        // 0x00432440
                        charge(ctx, 12);
                        jal(ctx, 0x432440u, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            goto L_004325e4;
                        }
                        // 0x00432470
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432480u, gen::fn_sub_4332F0_004332f0);
                        v0 = 1;
                    } else {
                        // 0x0043241c
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, 1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x43242Cu, gen::fn_sub_4332F0_004332f0);
                        v0 = 4;
                    }
                } else {
                    // 0x004323c8
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x4323D8u, gen::fn_sub_4332F0_004332f0);
                    v0 = 3;
                }
            } else {
                // 0x00432374
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkX);
                v0 = addiu(v0, -1);
                sb(v0, s0, kNpcWalkX);
                a0 = s1;
                jal(ctx, 0x432384u, gen::fn_sub_4332F0_004332f0);
                v0 = 2;
            }
        } else {
            // 0x00432084
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x004321f4
                charge(ctx, 12);
                jal(ctx, 0x4321F4u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00432248
                    charge(ctx, 12);
                    jal(ctx, 0x432248u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x0043229c
                        charge(ctx, 12);
                        jal(ctx, 0x43229Cu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x4;
                        if (v0 == 0) {
                            // 0x004322f0
                            charge(ctx, 12);
                            jal(ctx, 0x4322F0u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x8;
                            if (v0 == 0) {
                                goto L_004325e4;
                            }
                            // 0x00432320
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x432330u, gen::fn_sub_4332F0_004332f0);
                            v0 = 4;
                        } else {
                            // 0x004322cc
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x4322DCu, gen::fn_sub_4332F0_004332f0);
                            v0 = 3;
                        }
                    } else {
                        // 0x00432278
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x432288u, gen::fn_sub_4332F0_004332f0);
                        v0 = 2;
                    }
                } else {
                    // 0x00432224
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x432234u, gen::fn_sub_4332F0_004332f0);
                    v0 = 1;
                }
            } else {
                // 0x00432090
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0043209c
                    charge(ctx, 2);
                    goto L_004325e4;
                }
                // 0x004320a4
                charge(ctx, 12);
                jal(ctx, 0x4320A4u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x8;
                if (v0 == 0) {
                    // 0x004320f8
                    charge(ctx, 12);
                    jal(ctx, 0x4320F8u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x0043214c
                        charge(ctx, 12);
                        jal(ctx, 0x43214Cu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x2;
                        if (v0 == 0) {
                            // 0x004321a0
                            charge(ctx, 12);
                            jal(ctx, 0x4321A0u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x4;
                            if (v0 == 0) {
                                goto L_004325e4;
                            }
                            // 0x004321d0
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x4321E0u, gen::fn_sub_4332F0_004332f0);
                            v0 = 3;
                        } else {
                            // 0x0043217c
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, -1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x43218Cu, gen::fn_sub_4332F0_004332f0);
                            v0 = 2;
                        }
                    } else {
                        // 0x00432128
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432138u, gen::fn_sub_4332F0_004332f0);
                        v0 = 1;
                    }
                } else {
                    // 0x004320d4
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x4320E4u, gen::fn_sub_4332F0_004332f0);
                    v0 = 4;
                }
            }
        }
    }
    // 0x004325e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00432600 sub_432600 -- 1456 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WallFollow2] Explore helper ($a0 task), wall-following rule 2: by the facing (+258, 1..4) it tries the
// current cell's open sides (grid cell +11 bits 1 / 2 / 4 / 8) in this rule's order, steps the walk cell (+248 /
// +249) to the first open one and returns its direction 1..4 (0 when none); the step runs the rule-flip check
// (sub_4332F0 for rules 0 / 1, sub_4333D0 for 2 / 3).
void sub_432600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00432600
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lb(v1, s0, kNpcFacing);
    v0 = 4;
    if (v1 == v0) {
        // 0x00432a44
        charge(ctx, 12);
        jal(ctx, 0x432A44u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s0, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00432a98
            charge(ctx, 12);
            jal(ctx, 0x432A98u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x00432aec
                charge(ctx, 12);
                jal(ctx, 0x432AECu, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00432b40
                    charge(ctx, 12);
                    jal(ctx, 0x432B40u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                    L_00432b94:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x00432b70
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x432B80u, gen::fn_sub_4333D0_004333d0);
                        v0 = 2;
                    }
                } else {
                    // 0x00432b1c
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x432B2Cu, gen::fn_sub_4333D0_004333d0);
                    v0 = 1;
                }
            } else {
                // 0x00432ac8
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkZ);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkZ);
                a0 = s1;
                jal(ctx, 0x432AD8u, gen::fn_sub_4333D0_004333d0);
                v0 = 3;
            }
        } else {
            // 0x00432a74
            charge(ctx, 9);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkX);
            a0 = s1;
            jal(ctx, 0x432A84u, gen::fn_sub_4333D0_004333d0);
            v0 = 4;
        }
    } else {
        // 0x00432628
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004328f4
            charge(ctx, 12);
            jal(ctx, 0x4328F4u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x00432948
                charge(ctx, 12);
                jal(ctx, 0x432948u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x0043299c
                    charge(ctx, 12);
                    jal(ctx, 0x43299Cu, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x8;
                    if (v0 == 0) {
                        // 0x004329f0
                        charge(ctx, 12);
                        jal(ctx, 0x4329F0u, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            goto L_00432b94;
                        }
                        // 0x00432a20
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432A30u, gen::fn_sub_4333D0_004333d0);
                        v0 = 1;
                    } else {
                        // 0x004329cc
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, 1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x4329DCu, gen::fn_sub_4333D0_004333d0);
                        v0 = 4;
                    }
                } else {
                    // 0x00432978
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x432988u, gen::fn_sub_4333D0_004333d0);
                    v0 = 2;
                }
            } else {
                // 0x00432924
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkZ);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkZ);
                a0 = s1;
                jal(ctx, 0x432934u, gen::fn_sub_4333D0_004333d0);
                v0 = 3;
            }
        } else {
            // 0x00432634
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x004327a4
                charge(ctx, 12);
                jal(ctx, 0x4327A4u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x004327f8
                    charge(ctx, 12);
                    jal(ctx, 0x4327F8u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x0043284c
                        charge(ctx, 12);
                        jal(ctx, 0x43284Cu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x4;
                        if (v0 == 0) {
                            // 0x004328a0
                            charge(ctx, 12);
                            jal(ctx, 0x4328A0u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x8;
                            if (v0 == 0) {
                                goto L_00432b94;
                            }
                            // 0x004328d0
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x4328E0u, gen::fn_sub_4333D0_004333d0);
                            v0 = 4;
                        } else {
                            // 0x0043287c
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x43288Cu, gen::fn_sub_4333D0_004333d0);
                            v0 = 3;
                        }
                    } else {
                        // 0x00432828
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432838u, gen::fn_sub_4333D0_004333d0);
                        v0 = 1;
                    }
                } else {
                    // 0x004327d4
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x4327E4u, gen::fn_sub_4333D0_004333d0);
                    v0 = 2;
                }
            } else {
                // 0x00432640
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0043264c
                    charge(ctx, 2);
                    goto L_00432b94;
                }
                // 0x00432654
                charge(ctx, 12);
                jal(ctx, 0x432654u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x004326a8
                    charge(ctx, 12);
                    jal(ctx, 0x4326A8u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x8;
                    if (v0 == 0) {
                        // 0x004326fc
                        charge(ctx, 12);
                        jal(ctx, 0x4326FCu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x2;
                        if (v0 == 0) {
                            // 0x00432750
                            charge(ctx, 12);
                            jal(ctx, 0x432750u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x4;
                            if (v0 == 0) {
                                goto L_00432b94;
                            }
                            // 0x00432780
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x432790u, gen::fn_sub_4333D0_004333d0);
                            v0 = 3;
                        } else {
                            // 0x0043272c
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, -1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x43273Cu, gen::fn_sub_4333D0_004333d0);
                            v0 = 2;
                        }
                    } else {
                        // 0x004326d8
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, 1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x4326E8u, gen::fn_sub_4333D0_004333d0);
                        v0 = 4;
                    }
                } else {
                    // 0x00432684
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x432694u, gen::fn_sub_4333D0_004333d0);
                    v0 = 1;
                }
            }
        }
    }
    // 0x00432b98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00432BB0 sub_432BB0 -- 1456 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WallFollow3] Explore helper ($a0 task), wall-following rule 3: by the facing (+258, 1..4) it tries the
// current cell's open sides (grid cell +11 bits 1 / 2 / 4 / 8) in this rule's order, steps the walk cell (+248 /
// +249) to the first open one and returns its direction 1..4 (0 when none); the step runs the rule-flip check
// (sub_4332F0 for rules 0 / 1, sub_4333D0 for 2 / 3).
void sub_432BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00432bb0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lb(v1, s0, kNpcFacing);
    v0 = 4;
    if (v1 == v0) {
        // 0x00432ff4
        charge(ctx, 12);
        jal(ctx, 0x432FF4u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s0, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00433048
            charge(ctx, 12);
            jal(ctx, 0x433048u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0043309c
                charge(ctx, 12);
                jal(ctx, 0x43309Cu, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x004330f0
                    charge(ctx, 12);
                    jal(ctx, 0x4330F0u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                    L_00433144:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x00433120
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x433130u, gen::fn_sub_4333D0_004333d0);
                        v0 = 2;
                    }
                } else {
                    // 0x004330cc
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x4330DCu, gen::fn_sub_4333D0_004333d0);
                    v0 = 3;
                }
            } else {
                // 0x00433078
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkZ);
                v0 = addiu(v0, -1);
                sb(v0, s0, kNpcWalkZ);
                a0 = s1;
                jal(ctx, 0x433088u, gen::fn_sub_4333D0_004333d0);
                v0 = 1;
            }
        } else {
            // 0x00433024
            charge(ctx, 9);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkX);
            a0 = s1;
            jal(ctx, 0x433034u, gen::fn_sub_4333D0_004333d0);
            v0 = 4;
        }
    } else {
        // 0x00432bd8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00432ea4
            charge(ctx, 12);
            jal(ctx, 0x432EA4u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v0, v0, 83);
            v0 = v0 & 0x4;
            if (v0 == 0) {
                // 0x00432ef8
                charge(ctx, 12);
                jal(ctx, 0x432EF8u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x8;
                if (v0 == 0) {
                    // 0x00432f4c
                    charge(ctx, 12);
                    jal(ctx, 0x432F4Cu, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x00432fa0
                        charge(ctx, 12);
                        jal(ctx, 0x432FA0u, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            goto L_00433144;
                        }
                        // 0x00432fd0
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432FE0u, gen::fn_sub_4333D0_004333d0);
                        v0 = 1;
                    } else {
                        // 0x00432f7c
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x432F8Cu, gen::fn_sub_4333D0_004333d0);
                        v0 = 2;
                    }
                } else {
                    // 0x00432f28
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, 1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x432F38u, gen::fn_sub_4333D0_004333d0);
                    v0 = 4;
                }
            } else {
                // 0x00432ed4
                charge(ctx, 9);
                lbu(v0, s0, kNpcWalkZ);
                v0 = addiu(v0, 1);
                sb(v0, s0, kNpcWalkZ);
                a0 = s1;
                jal(ctx, 0x432EE4u, gen::fn_sub_4333D0_004333d0);
                v0 = 3;
            }
        } else {
            // 0x00432be4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00432d54
                charge(ctx, 12);
                jal(ctx, 0x432D54u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x00432da8
                    charge(ctx, 12);
                    jal(ctx, 0x432DA8u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x00432dfc
                        charge(ctx, 12);
                        jal(ctx, 0x432DFCu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            // 0x00432e50
                            charge(ctx, 12);
                            jal(ctx, 0x432E50u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x8;
                            if (v0 == 0) {
                                goto L_00433144;
                            }
                            // 0x00432e80
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x432E90u, gen::fn_sub_4333D0_004333d0);
                            v0 = 4;
                        } else {
                            // 0x00432e2c
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, -1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x432E3Cu, gen::fn_sub_4333D0_004333d0);
                            v0 = 1;
                        }
                    } else {
                        // 0x00432dd8
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkZ);
                        v0 = addiu(v0, 1);
                        sb(v0, s0, kNpcWalkZ);
                        a0 = s1;
                        jal(ctx, 0x432DE8u, gen::fn_sub_4333D0_004333d0);
                        v0 = 3;
                    }
                } else {
                    // 0x00432d84
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkX);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkX);
                    a0 = s1;
                    jal(ctx, 0x432D94u, gen::fn_sub_4333D0_004333d0);
                    v0 = 2;
                }
            } else {
                // 0x00432bf0
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x00432bfc
                    charge(ctx, 2);
                    goto L_00433144;
                }
                // 0x00432c04
                charge(ctx, 12);
                jal(ctx, 0x432C04u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                v1 = addu(v0, v1);
                lb(v0, s0, kNpcCellX);
                v0 = sll(v0, 4);
                v0 = addu(v1, v0);
                lbu(v0, v0, 83);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00432c58
                    charge(ctx, 12);
                    jal(ctx, 0x432C58u, gen::fn_K_Field_Get_001b9120);
                    lb(v1, s0, kNpcCellZ);
                    v1 = sll(v1, 8);
                    v1 = addu(v0, v1);
                    lb(v0, s0, kNpcCellX);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 83);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        // 0x00432cac
                        charge(ctx, 12);
                        jal(ctx, 0x432CACu, gen::fn_K_Field_Get_001b9120);
                        lb(v1, s0, kNpcCellZ);
                        v1 = sll(v1, 8);
                        v1 = addu(v0, v1);
                        lb(v0, s0, kNpcCellX);
                        v0 = sll(v0, 4);
                        v0 = addu(v1, v0);
                        lbu(v0, v0, 83);
                        v0 = v0 & 0x8;
                        if (v0 == 0) {
                            // 0x00432d00
                            charge(ctx, 12);
                            jal(ctx, 0x432D00u, gen::fn_K_Field_Get_001b9120);
                            lb(v1, s0, kNpcCellZ);
                            v1 = sll(v1, 8);
                            v1 = addu(v0, v1);
                            lb(v0, s0, kNpcCellX);
                            v0 = sll(v0, 4);
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 83);
                            v0 = v0 & 0x4;
                            if (v0 == 0) {
                                goto L_00433144;
                            }
                            // 0x00432d30
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkZ);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkZ);
                            a0 = s1;
                            jal(ctx, 0x432D40u, gen::fn_sub_4333D0_004333d0);
                            v0 = 3;
                        } else {
                            // 0x00432cdc
                            charge(ctx, 9);
                            lbu(v0, s0, kNpcWalkX);
                            v0 = addiu(v0, 1);
                            sb(v0, s0, kNpcWalkX);
                            a0 = s1;
                            jal(ctx, 0x432CECu, gen::fn_sub_4333D0_004333d0);
                            v0 = 4;
                        }
                    } else {
                        // 0x00432c88
                        charge(ctx, 9);
                        lbu(v0, s0, kNpcWalkX);
                        v0 = addiu(v0, -1);
                        sb(v0, s0, kNpcWalkX);
                        a0 = s1;
                        jal(ctx, 0x432C98u, gen::fn_sub_4333D0_004333d0);
                        v0 = 2;
                    }
                } else {
                    // 0x00432c34
                    charge(ctx, 9);
                    lbu(v0, s0, kNpcWalkZ);
                    v0 = addiu(v0, -1);
                    sb(v0, s0, kNpcWalkZ);
                    a0 = s1;
                    jal(ctx, 0x432C44u, gen::fn_sub_4333D0_004333d0);
                    v0 = 1;
                }
            }
        }
    }
    // 0x00433148 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00433160 sub_433160 -- 396 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_FindUnvisitedSide] Explore helper ($a0 task): checks the open sides of the current cell in the order +x
// (8), -x (2), -z (1), +z (4) and returns the first whose neighbour has a zero visit count (direction 4, 2, 1 or 3),
// else 0.
void sub_433160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00433160
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    s3 = 0;
    lb(s2, s0, kNpcCellZ);
    lb(s1, s0, kNpcCellX);
    v1 = addu(s1, s0);
    v0 = sll(s2, 4);
    v0 = addu(v0, v1);
    lbu(v0, v0, 266);
    if (v0 == 0) {
        // 0x004331a0
        charge(ctx, 10);
        jal(ctx, 0x4331A0u, gen::fn_K_Field_Get_001b9120);
        v1 = sll(s2, 8);
        v1 = addu(v0, v1);
        v0 = sll(s1, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            goto L_004331d4;
        }
        // 0x004331c8
        charge(ctx, 3);
        s3 = 4;
        // 0x004332c8 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v0 = s3;
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004331d4:
    charge(ctx, 6);
    v1 = addu(s1, s0);
    v0 = sll(s2, 4);
    v0 = addu(v0, v1);
    lbu(v0, v0, 264);
    if (v0 == 0) {
        // 0x004331ec
        charge(ctx, 12);
        lb(s2, s0, kNpcCellZ);
        lb(s1, s0, kNpcCellX);
        jal(ctx, 0x4331F4u, gen::fn_K_Field_Get_001b9120);
        v1 = sll(s2, 8);
        v1 = addu(v0, v1);
        v0 = sll(s1, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            goto L_00433228;
        }
        // 0x0043321c
        charge(ctx, 3);
        s3 = 2;
        // 0x004332c8 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v0 = s3;
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00433228:
    charge(ctx, 6);
    v1 = addu(s1, s0);
    v0 = sll(s2, 4);
    v0 = addu(v0, v1);
    lbu(v0, v0, 249);
    if (v0 == 0) {
        // 0x00433240
        charge(ctx, 12);
        lb(s2, s0, kNpcCellZ);
        lb(s1, s0, kNpcCellX);
        jal(ctx, 0x433248u, gen::fn_K_Field_Get_001b9120);
        v1 = sll(s2, 8);
        v1 = addu(v0, v1);
        v0 = sll(s1, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            goto L_0043327c;
        }
        // 0x00433270
        charge(ctx, 3);
        s3 = 1;
        // 0x004332c8 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        v0 = s3;
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0043327c:
    charge(ctx, 6);
    v1 = addu(s1, s0);
    v0 = sll(s2, 4);
    v0 = addu(v0, v1);
    lbu(v0, v0, 281);
    if (v0 == 0) {
        // 0x00433294
        charge(ctx, 12);
        jal(ctx, 0x433294u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s0, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(v0, v0, 83);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x004332c4
            charge(ctx, 1);
            s3 = 3;
        }
    }
    // 0x004332c8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s3;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004332F0 sub_4332F0 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CheckRuleFlip01] When the current cell is part of a wide block (cell +7 == 2) and the next cell has the
// same kind, counts +524; at 9 the rule +257 flips (^1) and the count restarts; any other step resets the count.
void sub_4332F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004332f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    jal(ctx, 0x433304u, gen::fn_K_Field_Get_001b9120);
    lb(v1, s1, kNpcCellZ);
    v1 = sll(v1, 8);
    a0 = addu(v0, v1);
    lb(v1, s1, kNpcCellX);
    v1 = sll(v1, 4);
    v1 = addu(a0, v1);
    lbu(a0, v1, 79);
    v1 = 2;
    if (a0 == v1) {
        // 0x00433334
        charge(ctx, 20);
        jal(ctx, 0x433334u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s1, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s1, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(s0, v0, 74);
        jal(ctx, 0x433358u, gen::fn_K_Field_Get_001b9120);
        lbu(v1, s1, kNpcWalkZ);
        v1 = sll(v1, 8);
        a0 = addu(v0, v1);
        lbu(v1, s1, kNpcWalkX);
        v1 = sll(v1, 4);
        v1 = addu(a0, v1);
        lbu(v1, v1, 74);
        if (s0 != v1) {
            // 0x004333b4
            charge(ctx, 1);
            sw(zero, s1, kNpcCount);
        } else {
            // 0x00433384
            charge(ctx, 6);
            lw(v1, s1, kNpcCount);
            v1 = addiu(v1, 1);
            sw(v1, s1, kNpcCount);
            at = slti(v1, 9);
            if (at == 0) {
                // 0x0043339c
                charge(ctx, 6);
                lb(v1, s1, kNpcHand);
                v1 = v1 ^ 0x1;
                sb(v1, s1, kNpcHand);
                sw(zero, s1, kNpcCount);
            }
        }
    }
    // 0x004333b8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004333D0 sub_4333D0 -- 248 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CheckRuleFlip23] The same as sub_4332F0 for the rules 2 / 3.
void sub_4333D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004333d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    jal(ctx, 0x4333E4u, gen::fn_K_Field_Get_001b9120);
    lb(v1, s1, kNpcCellZ);
    v1 = sll(v1, 8);
    a0 = addu(v0, v1);
    lb(v1, s1, kNpcCellX);
    v1 = sll(v1, 4);
    v1 = addu(a0, v1);
    lbu(a0, v1, 79);
    v1 = 2;
    if (a0 == v1) {
        // 0x00433414
        charge(ctx, 20);
        jal(ctx, 0x433414u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s1, kNpcCellZ);
        v1 = sll(v1, 8);
        v1 = addu(v0, v1);
        lb(v0, s1, kNpcCellX);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        lbu(s0, v0, 74);
        jal(ctx, 0x433438u, gen::fn_K_Field_Get_001b9120);
        lbu(v1, s1, kNpcWalkZ);
        v1 = sll(v1, 8);
        a0 = addu(v0, v1);
        lbu(v1, s1, kNpcWalkX);
        v1 = sll(v1, 4);
        v1 = addu(a0, v1);
        lbu(v1, v1, 74);
        if (s0 != v1) {
            // 0x004334ac
            charge(ctx, 1);
            sw(zero, s1, kNpcCount);
        } else {
            // 0x00433464
            charge(ctx, 6);
            lw(v1, s1, kNpcCount);
            v1 = addiu(v1, 1);
            sw(v1, s1, kNpcCount);
            at = slti(v1, 9);
            if (at == 0) {
                // 0x0043347c
                charge(ctx, 4);
                lb(a0, s1, kNpcHand);
                v1 = 2;
                if (a0 != v1) {
                    // 0x0043349c
                    charge(ctx, 1);
                    sb(v1, s1, kNpcHand);
                } else {
                    // 0x0043348c
                    charge(ctx, 4);
                    v1 = 3;
                    sb(v1, s1, kNpcHand);
                }
                // 0x004334a0
                charge(ctx, 3);
                sw(zero, s1, kNpcCount);
            }
        }
    }
    // 0x004334b0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004334D0 sub_4334D0 -- 828 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_MarkBlockVisited] When the current cell belongs to a 2 x 2 block (cell +7 == 2), finds the block's corner
// from the neighbours' +1 / +7 bytes and adds one visit to its other three cells as well.
void sub_4334D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004334d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    jal(ctx, 0x4334E0u, gen::fn_K_Field_Get_001b9120);
    lb(v1, s0, kNpcCellZ);
    v1 = sll(v1, 8);
    a0 = addu(v0, v1);
    lb(v1, s0, kNpcCellX);
    v1 = sll(v1, 4);
    v1 = addu(a0, v1);
    lbu(a0, v1, 79);
    v1 = 2;
    if (a0 == v1) {
        // 0x00433510
        charge(ctx, 12);
        jal(ctx, 0x433510u, gen::fn_K_Field_Get_001b9120);
        lb(v1, s0, kNpcCellZ);
        v1 = sll(v1, 8);
        a0 = addu(v0, v1);
        lb(v1, s0, kNpcCellX);
        v1 = sll(v1, 4);
        v1 = addu(a0, v1);
        lbu(a0, v1, 73);
        v1 = 1;
        if (a0 != v1) {
            // 0x004335a8
            charge(ctx, 12);
            jal(ctx, 0x4335A8u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, -183);
            v0 = 1;
            if (v1 == v0) {
                // 0x004335d8
                charge(ctx, 12);
                jal(ctx, 0x4335D8u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                a0 = addu(v0, v1);
                lb(v1, s0, kNpcCellX);
                v1 = sll(v1, 4);
                v1 = addu(a0, v1);
                lbu(a0, v1, -177);
                v1 = 2;
                if (a0 != v1) {
                    goto L_00433670;
                }
                // 0x00433608
                charge(ctx, 26);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 266);
                v1 = addiu(v1, 1);
                sb(v1, a0, 266);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 249);
                v1 = addiu(v1, 1);
                sb(v1, a0, 249);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 250);
                v1 = addiu(v1, 1);
                sb(v1, a0, 250);
                // 0x004337f8 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00433670:
            charge(ctx, 12);
            jal(ctx, 0x433670u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            lb(v0, s0, kNpcCellX);
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 57);
            v0 = 1;
            if (v1 == v0) {
                // 0x004336a0
                charge(ctx, 12);
                jal(ctx, 0x4336A0u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                a0 = addu(v0, v1);
                lb(v1, s0, kNpcCellX);
                v1 = sll(v1, 4);
                v1 = addu(a0, v1);
                lbu(a0, v1, 63);
                v1 = 2;
                if (a0 != v1) {
                    goto L_00433738;
                }
                // 0x004336d0
                charge(ctx, 26);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 264);
                v1 = addiu(v1, 1);
                sb(v1, a0, 264);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 281);
                v1 = addiu(v1, 1);
                sb(v1, a0, 281);
                lbu(v1, s0, kNpcWalkX);
                a0 = addu(v1, s0);
                lbu(v1, s0, kNpcWalkZ);
                v1 = sll(v1, 4);
                a0 = addu(v1, a0);
                lbu(v1, a0, 280);
                v1 = addiu(v1, 1);
                sb(v1, a0, 280);
                // 0x004337f8 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00433738:
            charge(ctx, 12);
            jal(ctx, 0x433738u, gen::fn_K_Field_Get_001b9120);
            lb(v1, s0, kNpcCellZ);
            v1 = sll(v1, 8);
            a0 = addu(v0, v1);
            lb(v1, s0, kNpcCellX);
            v1 = sll(v1, 4);
            v1 = addu(a0, v1);
            lbu(a0, v1, -199);
            v1 = 1;
            if (a0 == v1) {
                // 0x00433768
                charge(ctx, 12);
                jal(ctx, 0x433768u, gen::fn_K_Field_Get_001b9120);
                lb(v1, s0, kNpcCellZ);
                v1 = sll(v1, 8);
                a0 = addu(v0, v1);
                lb(v1, s0, kNpcCellX);
                v1 = sll(v1, 4);
                v1 = addu(a0, v1);
                lbu(a0, v1, -193);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00433798
                    charge(ctx, 24);
                    lbu(v1, s0, kNpcWalkX);
                    a0 = addu(v1, s0);
                    lbu(v1, s0, kNpcWalkZ);
                    v1 = sll(v1, 4);
                    a0 = addu(v1, a0);
                    lbu(v1, a0, 264);
                    v1 = addiu(v1, 1);
                    sb(v1, a0, 264);
                    lbu(v1, s0, kNpcWalkX);
                    a0 = addu(v1, s0);
                    lbu(v1, s0, kNpcWalkZ);
                    v1 = sll(v1, 4);
                    a0 = addu(v1, a0);
                    lbu(v1, a0, 249);
                    v1 = addiu(v1, 1);
                    sb(v1, a0, 249);
                    lbu(v1, s0, kNpcWalkX);
                    a0 = addu(v1, s0);
                    lbu(v1, s0, kNpcWalkZ);
                    v1 = sll(v1, 4);
                    a0 = addu(v1, a0);
                    lbu(v1, a0, 248);
                    v1 = addiu(v1, 1);
                    sb(v1, a0, 248);
                }
            }
        } else {
            // 0x00433540
            charge(ctx, 26);
            lbu(v1, s0, kNpcWalkX);
            a0 = addu(v1, s0);
            lbu(v1, s0, kNpcWalkZ);
            v1 = sll(v1, 4);
            a0 = addu(v1, a0);
            lbu(v1, a0, 266);
            v1 = addiu(v1, 1);
            sb(v1, a0, 266);
            lbu(v1, s0, kNpcWalkX);
            a0 = addu(v1, s0);
            lbu(v1, s0, kNpcWalkZ);
            v1 = sll(v1, 4);
            a0 = addu(v1, a0);
            lbu(v1, a0, 281);
            v1 = addiu(v1, 1);
            sb(v1, a0, 281);
            lbu(v1, s0, kNpcWalkX);
            a0 = addu(v1, s0);
            lbu(v1, s0, kNpcWalkZ);
            v1 = sll(v1, 4);
            a0 = addu(v1, a0);
            lbu(v1, a0, 282);
            v1 = addiu(v1, 1);
            sb(v1, a0, 282);
        }
    }
    // 0x004337f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00433810 sub_433810 -- 440 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Grid_BlockOrigin] ($a0 x, $a1 z) when the cell is part of a 2 x 2 block (cell +7 == 2), returns the block's
// origin cell as 16 z + x (the cell itself or its -z / -x / -x-z neighbour, by their +1 / +7 bytes), else 0. Used by
// the mini-map.
void sub_433810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00433810
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = 0;
    s3 = dsll32(a1, 24);
    s3 = dsra32(s3, 24);
    s2 = sll(s3, 8);
    s1 = dsll32(a0, 24);
    s1 = dsra32(s1, 24);
    s0 = sll(s1, 4);
    jal(ctx, 0x433848u, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s2);
    v0 = addu(v0, s0);
    lbu(v1, v0, 79);
    v0 = 2;
    if (v1 == v0) {
        // 0x00433868
        charge(ctx, 8);
        jal(ctx, 0x433868u, gen::fn_K_Field_Get_001b9120);
        v0 = addu(v0, s2);
        v0 = addu(v0, s0);
        lbu(v1, v0, 73);
        v0 = 1;
        if (v1 != v0) {
            // 0x0043389c
            charge(ctx, 8);
            jal(ctx, 0x43389Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s0);
            lbu(v1, v0, -183);
            v0 = 1;
            if (v1 == v0) {
                // 0x004338bc
                charge(ctx, 8);
                jal(ctx, 0x4338BCu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s2);
                v0 = addu(v0, s0);
                lbu(v1, v0, -177);
                v0 = 2;
                if (v1 != v0) {
                    goto L_004338f4;
                }
                // 0x004338dc
                charge(ctx, 6);
                v0 = addiu(s3, -1);
                v0 = sll(v0, 4);
                v0 = addu(s1, v0);
                s4 = v0 & 0xFF;
                // 0x004339a0 (the shared epilogue, written out on this path)
                charge(ctx, 10);
                v0 = s4;
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_004338f4:
            charge(ctx, 8);
            jal(ctx, 0x4338F4u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s0);
            lbu(v1, v0, 57);
            v0 = 1;
            if (v1 == v0) {
                // 0x00433914
                charge(ctx, 8);
                jal(ctx, 0x433914u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s2);
                v0 = addu(v0, s0);
                lbu(v1, v0, 63);
                v0 = 2;
                if (v1 != v0) {
                    goto L_0043394c;
                }
                // 0x00433934
                charge(ctx, 6);
                v1 = addiu(s1, -1);
                v0 = sll(s3, 4);
                v0 = addu(v1, v0);
                s4 = v0 & 0xFF;
                // 0x004339a0 (the shared epilogue, written out on this path)
                charge(ctx, 10);
                v0 = s4;
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_0043394c:
            charge(ctx, 8);
            jal(ctx, 0x43394Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            v0 = addu(v0, s0);
            lbu(v1, v0, -199);
            v0 = 1;
            if (v1 == v0) {
                // 0x0043396c
                charge(ctx, 8);
                jal(ctx, 0x43396Cu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s2);
                v0 = addu(v0, s0);
                lbu(v1, v0, -193);
                v0 = 2;
                if (v1 == v0) {
                    // 0x0043398c
                    charge(ctx, 5);
                    v1 = addiu(s1, -1);
                    v0 = addiu(s3, -1);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    s4 = v0 & 0xFF;
                }
            }
        } else {
            // 0x00433888
            charge(ctx, 5);
            v0 = sll(s3, 4);
            v0 = addu(s1, v0);
            s4 = v0 & 0xFF;
        }
    }
    // 0x004339a0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004339D0 sub_4339D0 -- 1040 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_TurnToLeastVisited] Explore helper ($a0 task): over the open sides -z, -x, +x, +z (in that order) keeps the
// one whose neighbour has the fewest visits (ties go to the later side), sets the facing +258 to it and returns the
// direction (0 none).
void sub_4339D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004339d0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s0, a0, 60);
    lb(s5, s0, kNpcCellX);
    v1 = addu(s5, s0);
    lb(s4, s0, kNpcCellZ);
    v0 = sll(s4, 4);
    v0 = addu(v0, v1);
    lbu(v0, v0, 265);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    s1 = 0;
    jal(ctx, 0x433A1Cu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s4, 8);
    v1 = addu(v0, v1);
    v0 = sll(s5, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00433a44
        charge(ctx, 9);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        v1 = addu(s5, s0);
        v0 = sll(s4, 4);
        v0 = addu(v0, v1);
        lbu(v0, v0, 249);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            // 0x00433a68
            charge(ctx, 18);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, -1);
            sb(v0, s0, kNpcWalkZ);
            lw(v0, s3, 60);
            lbu(s5, v0, 249);
            lbu(s4, v0, 248);
            jal(ctx, 0x433A80u, gen::fn_K_Field_Get_001b9120);
            v1 = s5 & 0xFF;
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            v0 = s4 & 0xFF;
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 4;
            if (v1 != v0) {
                // 0x00433abc
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00433ab0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00433ac0
            charge(ctx, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                // 0x00433ad0
                charge(ctx, 10);
                lb(v0, s0, kNpcCellX);
                v1 = addu(v0, s0);
                lb(v0, s0, kNpcCellZ);
                v0 = sll(v0, 4);
                v0 = addu(v0, v1);
                lbu(v0, v0, 249);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                s1 = 1;
                sb(s1, s0, kNpcFacing);
            }
            // 0x00433af8
            charge(ctx, 3);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkZ);
        }
    }
    // 0x00433b04
    charge(ctx, 12);
    lb(s5, s0, kNpcCellZ);
    lb(s4, s0, kNpcCellX);
    jal(ctx, 0x433B0Cu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s5, 8);
    v1 = addu(v0, v1);
    v0 = sll(s4, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00433b34
        charge(ctx, 9);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        v1 = addu(s4, s0);
        v0 = sll(s5, 4);
        v0 = addu(v0, v1);
        lbu(v0, v0, 264);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            // 0x00433b58
            charge(ctx, 18);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, -1);
            sb(v0, s0, kNpcWalkX);
            lw(v0, s3, 60);
            lbu(s5, v0, 249);
            lbu(s4, v0, 248);
            jal(ctx, 0x433B70u, gen::fn_K_Field_Get_001b9120);
            v1 = s5 & 0xFF;
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            v0 = s4 & 0xFF;
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 4;
            if (v1 != v0) {
                // 0x00433bac
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00433ba0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00433bb0
            charge(ctx, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                // 0x00433bc0
                charge(ctx, 10);
                lb(v0, s0, kNpcCellX);
                v1 = addu(v0, s0);
                lb(v0, s0, kNpcCellZ);
                v0 = sll(v0, 4);
                v0 = addu(v0, v1);
                lbu(v0, v0, 264);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                s1 = 2;
                sb(s1, s0, kNpcFacing);
            }
            // 0x00433be8
            charge(ctx, 3);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkX);
        }
    }
    // 0x00433bf4
    charge(ctx, 12);
    lb(s5, s0, kNpcCellZ);
    lb(s4, s0, kNpcCellX);
    jal(ctx, 0x433BFCu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s5, 8);
    v1 = addu(v0, v1);
    v0 = sll(s4, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x00433c24
        charge(ctx, 9);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        v1 = addu(s4, s0);
        v0 = sll(s5, 4);
        v0 = addu(v0, v1);
        lbu(v0, v0, 266);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            // 0x00433c48
            charge(ctx, 18);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkX);
            lw(v0, s3, 60);
            lbu(s5, v0, 249);
            lbu(s4, v0, 248);
            jal(ctx, 0x433C60u, gen::fn_K_Field_Get_001b9120);
            v1 = s5 & 0xFF;
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            v0 = s4 & 0xFF;
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 4;
            if (v1 != v0) {
                // 0x00433c9c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00433c90
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00433ca0
            charge(ctx, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                // 0x00433cb0
                charge(ctx, 10);
                lb(v0, s0, kNpcCellX);
                v1 = addu(v0, s0);
                lb(v0, s0, kNpcCellZ);
                v0 = sll(v0, 4);
                v0 = addu(v0, v1);
                lbu(v0, v0, 266);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                s1 = 4;
                sb(s1, s0, kNpcFacing);
            }
            // 0x00433cd8
            charge(ctx, 3);
            lbu(v0, s0, kNpcWalkX);
            v0 = addiu(v0, -1);
            sb(v0, s0, kNpcWalkX);
        }
    }
    // 0x00433ce4
    charge(ctx, 12);
    lb(s5, s0, kNpcCellZ);
    lb(s4, s0, kNpcCellX);
    jal(ctx, 0x433CECu, gen::fn_K_Field_Get_001b9120);
    v1 = sll(s5, 8);
    v1 = addu(v0, v1);
    v0 = sll(s4, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00433d14
        charge(ctx, 9);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        v1 = addu(s4, s0);
        v0 = sll(s5, 4);
        v0 = addu(v0, v1);
        lbu(v0, v0, 281);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            // 0x00433d38
            charge(ctx, 18);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, 1);
            sb(v0, s0, kNpcWalkZ);
            lw(v0, s3, 60);
            lbu(s3, v0, 249);
            lbu(s2, v0, 248);
            jal(ctx, 0x433D50u, gen::fn_K_Field_Get_001b9120);
            v1 = s3 & 0xFF;
            v1 = sll(v1, 8);
            v1 = addu(v0, v1);
            v0 = s2 & 0xFF;
            v0 = sll(v0, 4);
            v0 = addu(v1, v0);
            lbu(v1, v0, 74);
            v0 = 4;
            if (v1 != v0) {
                // 0x00433d8c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00433d80
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00433d90
            charge(ctx, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                // 0x00433da0
                charge(ctx, 2);
                s1 = 3;
                sb(s1, s0, kNpcFacing);
            }
            // 0x00433da8
            charge(ctx, 3);
            lbu(v0, s0, kNpcWalkZ);
            v0 = addiu(v0, -1);
            sb(v0, s0, kNpcWalkZ);
        }
    }
    // 0x00433db4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00433DE0 sub_433DE0 -- 1512 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_PathExpand] One step of the breadth-first search from the walk cell (+248 / +249): every open side whose
// neighbour has no path record gets one ({x, z, from x, from z} at +528 + 8 cell) and is queued (+2576, count +524);
// 2 when the goal (+259 / +260) was reached (its record points back), 1 when the walk cell is (0, 0) (+0 = 32), else
// 0.
void sub_433DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00433de0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lbu(v1, s1, kNpcGoalX);
    lbu(v0, s1, kNpcGoalZ);
    v0 = sll(v0, 4);
    v0 = addu(v1, v0);
    s0 = v0 & 0xFF;
    lbu(v0, s1, kNpcWalkX);
    if (v0 == 0) {
        // 0x00433e1c
        charge(ctx, 3);
        lbu(v0, s1, kNpcWalkZ);
        if (v0 != 0) {
            goto L_00433e3c;
        }
        // 0x00433e28
        charge(ctx, 5);
        v0 = 32;
        sb(v0, s1, kNpcByte0);
        v0 = 1;
        // 0x004343a8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00433e3c:
    charge(ctx, 14);
    lbu(s3, s1, kNpcWalkZ);
    lbu(s2, s1, kNpcWalkX);
    jal(ctx, 0x433E44u, gen::fn_K_Field_Get_001b9120);
    a0 = s3 & 0xFF;
    v1 = sll(a0, 8);
    v1 = addu(v0, v1);
    a3 = s2 & 0xFF;
    v0 = sll(a3, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00433e74
        charge(ctx, 10);
        v0 = addiu(a0, -1);
        v0 = sll(v0, 4);
        v0 = addu(a3, v0);
        a2 = v0 & 0xFF;
        v0 = sll(a2, 3);
        a0 = addu(v0, s1);
        a1 = addiu(a0, 528);
        lh(v0, a0, 528);
        if (v0 != 0) {
            goto L_00433f40;
        }
        // 0x00433e9c
        charge(ctx, 4);
        v1 = addiu(a0, 530);
        lh(v0, a0, 530);
        if (v0 != 0) {
            goto L_00433f40;
        }
        // 0x00433eac
        charge(ctx, 19);
        sh(a3, a1, 0);
        lbu(v0, s1, kNpcWalkZ);
        v0 = addiu(v0, -1);
        sh(v0, v1, 0);
        lbu(v0, s1, kNpcWalkX);
        sh(v0, a0, 532);
        lbu(v0, s1, kNpcWalkZ);
        sh(v0, a0, 534);
        lw(v0, s1, kNpcCount);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        sw(a2, v0, 2576);
        lw(v0, s1, kNpcCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, kNpcCount);
        lbu(a0, s1, kNpcGoalX);
        lh(v0, a1, 0);
        if (v0 != a0) {
            goto L_00433f40;
        }
        // 0x00433ef8
        charge(ctx, 4);
        lh(v1, v1, 0);
        lbu(v0, s1, kNpcGoalZ);
        if (v1 != v0) {
            goto L_00433f40;
        }
        // 0x00433f08
        charge(ctx, 14);
        v0 = s0 & 0xFF;
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        sh(a0, v1, 528);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 530);
        lbu(v0, s1, kNpcGoalX);
        sh(v0, v1, 532);
        lbu(v0, s1, kNpcGoalZ);
        v0 = addiu(v0, 1);
        sh(v0, v1, 534);
        v0 = 2;
        // 0x004343a8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00433f40:
    charge(ctx, 14);
    lbu(s3, s1, kNpcWalkZ);
    lbu(s2, s1, kNpcWalkX);
    jal(ctx, 0x433F48u, gen::fn_K_Field_Get_001b9120);
    a1 = s3 & 0xFF;
    v1 = sll(a1, 8);
    v1 = addu(v0, v1);
    a0 = s2 & 0xFF;
    v0 = sll(a0, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00433f78
        charge(ctx, 9);
        v1 = sll(a1, 4);
        v0 = addiu(a0, -1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        a0 = addu(v0, s1);
        v1 = addiu(a0, 528);
        lh(v0, a0, 528);
        if (v0 != 0) {
            goto L_004340b8;
        }
        // 0x00433f9c
        charge(ctx, 3);
        lh(v0, a0, 530);
        if (v0 != 0) {
            goto L_004340b8;
        }
        // 0x00433fa8
        charge(ctx, 50);
        lbu(v0, s1, kNpcWalkX);
        v0 = addiu(v0, -1);
        sh(v0, v1, 0);
        lbu(a0, s1, kNpcWalkZ);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, -1);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 530);
        lbu(a0, s1, kNpcWalkX);
        lbu(v0, s1, kNpcWalkZ);
        v1 = sll(v0, 4);
        v0 = addiu(a0, -1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 532);
        lbu(a0, s1, kNpcWalkZ);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, -1);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 534);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, -1);
        lbu(v0, s1, kNpcWalkZ);
        v0 = sll(v0, 4);
        v1 = addu(v1, v0);
        lw(v0, s1, kNpcCount);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        sw(v1, v0, 2576);
        lw(v0, s1, kNpcCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, kNpcCount);
        lbu(a0, s1, kNpcGoalX);
        lbu(v0, s1, kNpcWalkZ);
        v1 = sll(v0, 4);
        lbu(v0, s1, kNpcWalkX);
        v0 = addiu(v0, -1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        lh(v0, v1, 528);
        if (v0 != a0) {
            goto L_004340b8;
        }
        // 0x00434070
        charge(ctx, 4);
        lh(v1, v1, 530);
        lbu(v0, s1, kNpcGoalZ);
        if (v1 != v0) {
            goto L_004340b8;
        }
        // 0x00434080
        charge(ctx, 14);
        v0 = s0 & 0xFF;
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        sh(a0, v1, 528);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 530);
        lbu(v0, s1, kNpcGoalX);
        v0 = addiu(v0, 1);
        sh(v0, v1, 532);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 534);
        v0 = 2;
        // 0x004343a8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004340b8:
    charge(ctx, 14);
    lbu(s3, s1, kNpcWalkZ);
    lbu(s2, s1, kNpcWalkX);
    jal(ctx, 0x4340C0u, gen::fn_K_Field_Get_001b9120);
    a1 = s3 & 0xFF;
    v1 = sll(a1, 8);
    v1 = addu(v0, v1);
    a0 = s2 & 0xFF;
    v0 = sll(a0, 4);
    v0 = addu(v1, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x004340f0
        charge(ctx, 9);
        v1 = sll(a1, 4);
        v0 = addiu(a0, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        a0 = addu(v0, s1);
        v1 = addiu(a0, 528);
        lh(v0, a0, 528);
        if (v0 != 0) {
            goto L_00434230;
        }
        // 0x00434114
        charge(ctx, 3);
        lh(v0, a0, 530);
        if (v0 != 0) {
            goto L_00434230;
        }
        // 0x00434120
        charge(ctx, 50);
        lbu(v0, s1, kNpcWalkX);
        v0 = addiu(v0, 1);
        sh(v0, v1, 0);
        lbu(a0, s1, kNpcWalkZ);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, 1);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 530);
        lbu(a0, s1, kNpcWalkX);
        lbu(v0, s1, kNpcWalkZ);
        v1 = sll(v0, 4);
        v0 = addiu(a0, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 532);
        lbu(a0, s1, kNpcWalkZ);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, 1);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 534);
        lbu(v0, s1, kNpcWalkX);
        v1 = addiu(v0, 1);
        lbu(v0, s1, kNpcWalkZ);
        v0 = sll(v0, 4);
        v1 = addu(v1, v0);
        lw(v0, s1, kNpcCount);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        sw(v1, v0, 2576);
        lw(v0, s1, kNpcCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, kNpcCount);
        lbu(a0, s1, kNpcGoalX);
        lbu(v0, s1, kNpcWalkZ);
        v1 = sll(v0, 4);
        lbu(v0, s1, kNpcWalkX);
        v0 = addiu(v0, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        lh(v0, v1, 528);
        if (v0 != a0) {
            goto L_00434230;
        }
        // 0x004341e8
        charge(ctx, 4);
        lh(v1, v1, 530);
        lbu(v0, s1, kNpcGoalZ);
        if (v1 != v0) {
            goto L_00434230;
        }
        // 0x004341f8
        charge(ctx, 14);
        v0 = s0 & 0xFF;
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        sh(a0, v1, 528);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 530);
        lbu(v0, s1, kNpcGoalX);
        v0 = addiu(v0, -1);
        sh(v0, v1, 532);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 534);
        v0 = 2;
        // 0x004343a8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00434230:
    charge(ctx, 14);
    lbu(s3, s1, kNpcWalkZ);
    lbu(s2, s1, kNpcWalkX);
    jal(ctx, 0x434238u, gen::fn_K_Field_Get_001b9120);
    a1 = s3 & 0xFF;
    v1 = sll(a1, 8);
    a0 = addu(v0, v1);
    v1 = s2 & 0xFF;
    v0 = sll(v1, 4);
    v0 = addu(a0, v0);
    lbu(v0, v0, 83);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00434268
        charge(ctx, 9);
        v0 = addiu(a1, 1);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        a0 = addu(v0, s1);
        v1 = addiu(a0, 528);
        lh(v0, a0, 528);
        if (v0 != 0) {
            goto L_004343a4;
        }
        // 0x0043428c
        charge(ctx, 3);
        lh(v0, a0, 530);
        if (v0 != 0) {
            goto L_004343a4;
        }
        // 0x00434298
        charge(ctx, 49);
        lbu(v0, s1, kNpcWalkX);
        sh(v0, v1, 0);
        lbu(v0, s1, kNpcWalkZ);
        a0 = addiu(v0, 1);
        lbu(v1, s1, kNpcWalkX);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 530);
        lbu(v1, s1, kNpcWalkX);
        lbu(v0, s1, kNpcWalkZ);
        v0 = addiu(v0, 1);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(v1, v0, 532);
        lbu(a0, s1, kNpcWalkZ);
        lbu(v1, s1, kNpcWalkX);
        v0 = addiu(a0, 1);
        v0 = sll(v0, 4);
        v0 = addu(v1, v0);
        v0 = sll(v0, 3);
        v0 = addu(v0, s1);
        sh(a0, v0, 534);
        lbu(v0, s1, kNpcWalkZ);
        v0 = addiu(v0, 1);
        v1 = sll(v0, 4);
        lbu(v0, s1, kNpcWalkX);
        v1 = addu(v0, v1);
        lw(v0, s1, kNpcCount);
        v0 = sll(v0, 2);
        v0 = addu(v0, s1);
        sw(v1, v0, 2576);
        lw(v0, s1, kNpcCount);
        v0 = addiu(v0, 1);
        sw(v0, s1, kNpcCount);
        lbu(a0, s1, kNpcGoalX);
        lbu(v0, s1, kNpcWalkZ);
        v0 = addiu(v0, 1);
        v1 = sll(v0, 4);
        lbu(v0, s1, kNpcWalkX);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        lh(v0, v1, 528);
        if (v0 != a0) {
            goto L_004343a4;
        }
        // 0x0043435c
        charge(ctx, 4);
        lh(v1, v1, 530);
        lbu(v0, s1, kNpcGoalZ);
        if (v1 != v0) {
            goto L_004343a4;
        }
        // 0x0043436c
        charge(ctx, 14);
        v0 = s0 & 0xFF;
        v0 = sll(v0, 3);
        v1 = addu(v0, s1);
        sh(a0, v1, 528);
        lbu(v0, s1, kNpcGoalZ);
        sh(v0, v1, 530);
        lbu(v0, s1, kNpcGoalX);
        sh(v0, v1, 532);
        lbu(v0, s1, kNpcGoalZ);
        v0 = addiu(v0, -1);
        sh(v0, v1, 534);
        v0 = 2;
        // 0x004343a8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004343a4:
    charge(ctx, 1);
    v0 = 0;
    // 0x004343a8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004343D0 sub_4343D0 -- 284 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_PathBuildSteps] Clears the step list +3600 (256 entries), then from the goal (+259 / +260) follows each
// record's "from" cell until the start (+261 / +262), storing {x, z} per step; stops after 100 steps. +524 = the
// step count.
void sub_4343D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x004343d0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    a1 = 0;
    a0 = 0;
    sw(zero, v1, kNpcCount);
    a3 = 0;
    for (;;) {
        // 0x00434400
        charge(ctx, 3);
        a2 = slti(a3, 256);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004343ec
        charge(ctx, 5);
        a2 = sll(a3, 2);
        a2 = addu(v1, a2);
        sh(zero, a2, 3600);
        sh(zero, a2, 3602);
        a3 = addiu(a3, 1);
    }
    // 0x0043440c
    charge(ctx, 11);
    lbu(t0, v1, kNpcGoalX);
    lbu(a3, v1, kNpcGoalZ);
    lw(a2, v1, kNpcCount);
    a2 = sll(a2, 2);
    a2 = addu(a2, v1);
    sh(t0, a2, 3600);
    lw(a2, v1, kNpcCount);
    a2 = sll(a2, 2);
    a2 = addu(a2, v1);
    sh(a3, a2, 3602);
    t1 = 1;
    for (;;) {
        // 0x00434438
        charge(ctx, 16);
        lw(t2, v1, kNpcCount);
        a2 = sll(t2, 2);
        t0 = addu(v1, a2);
        lh(a2, t0, 3602);
        a3 = sll(a2, 4);
        lh(a2, t0, 3600);
        a2 = addu(a2, a3);
        a2 = sll(a2, 3);
        a2 = addu(v1, a2);
        lh(t0, a2, 532);
        lh(a3, a2, 534);
        a2 = addiu(t2, 1);
        sw(a2, v1, kNpcCount);
        lbu(a2, v1, kNpcStartX);
        if (t0 == a2) {
            // 0x00434478
            charge(ctx, 3);
            lbu(a2, v1, kNpcStartZ);
            if (a3 != a2) {
                goto L_00434490;
            }
            // 0x00434484
            charge(ctx, 3);
            a1 = t1;
            goto L_004344c8;
        }
    L_00434490:
        charge(ctx, 14);
        a2 = sll(a3, 4);
        a2 = addu(t0, a2);
        a2 = sll(a2, 3);
        t0 = addu(v1, a2);
        lh(a3, t0, 528);
        lw(a2, v1, kNpcCount);
        a2 = sll(a2, 2);
        a2 = addu(v1, a2);
        sh(a3, a2, 3600);
        lh(a3, t0, 530);
        lw(a2, v1, kNpcCount);
        a2 = sll(a2, 2);
        a2 = addu(v1, a2);
        sh(a3, a2, 3602);
    L_004344c8:
        charge(ctx, 4);
        a0 = addiu(a0, 1);
        a2 = slti(a0, 100);
        if (a2 == 0) {
            // 0x004344d8
            charge(ctx, 1);
            a1 = t1;
        }
        // 0x004344dc
        charge(ctx, 2);
        if (a1 != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004344e4
    charge(ctx, 2);
}

// 0x004344F0 sub_4344F0 -- 628 bytes; frame 0xA0: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_ColumnPoint] ($a0 out, $a1 task, $a2 from, $a3 to, $f12 distance) the point `distance` short of `to` on the
// line from `from`, moved sideways (the cross product with the up axis 0x6B4608) by 20, -40 or 60 for column places
// 1 / 2 / 3 (0x7CE6E7 + pc). R5900 multiply-accumulate (mula.s / msub.s) kept as the original.
void sub_4344F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004344f0
    enter(ctx, 91);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f22, f12);
    lwc1(f2, a2, 0);
    lwc1(f1, a2, 4);
    lwc1(f0, a2, 8);
    swc1(f2, sp, 0x90);
    swc1(f1, sp, 0x94);
    swc1(f0, sp, 0x98);
    lwc1(f2, a3, 0);
    lwc1(f1, a3, 4);
    lwc1(f0, a3, 8);
    swc1(f2, sp, 0x80);
    swc1(f1, sp, 0x84);
    swc1(f0, sp, 0x88);
    lw(s1, a1, 60);
    v0 = 0x6B0000;
    ld(v1, v0, 17928);  // 0x6B4608
    v0 = 0x6B0000;
    lwc1(f0, v0, 17936);  // 0x6B4610
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    lwc1(f1, sp, 0x90);
    lwc1(f0, sp, 0x80);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    lwc1(f20, sp, 0x94);
    lwc1(f0, sp, 0x84);
    sub_s(f0, f20, f0);
    swc1(f0, sp, 0x74);
    lwc1(f21, sp, 0x98);
    lwc1(f0, sp, 0x88);
    sub_s(f0, f21, f0);
    swc1(f0, sp, 0x78);
    a0 = addiu(sp, 0x70);
    a1 = a0;
    jal(ctx, 0x434598u, gen::fn_sub_4C69F0_004c69f0);
    sub_s(f1, f0, f22);
    lwc1(f0, sp, 0x70);
    mul_s(f4, f0, f1);
    swc1(f4, sp, 0x50);
    lwc1(f0, sp, 0x74);
    mul_s(f3, f0, f1);
    swc1(f3, sp, 0x54);
    lwc1(f0, sp, 0x78);
    mul_s(f1, f0, f1);
    swc1(f1, sp, 0x58);
    lwc1(f2, sp, 0x90);
    sub_s(f0, f2, f4);
    swc1(f0, sp, 0x50);
    sub_s(f1, f21, f1);
    swc1(f1, sp, 0x58);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x60);
    sub_s(f0, f20, f3);
    swc1(f0, sp, 0x64);
    sub_s(f0, f21, f1);
    swc1(f0, sp, 0x68);
    a0 = addiu(sp, 0x60);
    a1 = a0;
    jal(ctx, 0x4345FCu, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f6, sp, 0x44);
    lwc1(f5, sp, 0x68);
    lwc1(f3, sp, 0x48);
    lwc1(f2, sp, 0x64);
    mula_s(f2, f3);
    msub_s(f4, f5, f6);
    swc1(f4, sp, 0x70);
    lwc1(f1, sp, 0x60);
    lwc1(f0, sp, 0x40);
    mula_s(f5, f0);
    msub_s(f3, f1, f3);
    swc1(f3, sp, 0x74);
    mula_s(f1, f6);
    msub_s(f2, f2, f0);
    swc1(f2, sp, 0x78);
    lw(a0, s1, 4);
    v1 = addiu(gp, -17929);  // &0x7CE6E7
    v1 = addu(v1, a0);
    lb(a0, v1, 0);
    v1 = 3;
    if (a0 == v1) {
        // 0x004346d4
        charge(ctx, 9);
        v1 = 0x42700000;
        mtc1(v1, f1);
        mul_s(f0, f1, f4);
        swc1(f0, sp, 0x60);
        mul_s(f0, f1, f3);
        swc1(f0, sp, 0x64);
        mul_s(f0, f1, f2);
        swc1(f0, sp, 0x68);
    } else {
        // 0x0043465c
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x004346a8
            charge(ctx, 11);
            v1 = lui(0xC220);
            mtc1(v1, f1);
            mul_s(f0, f1, f4);
            swc1(f0, sp, 0x60);
            mul_s(f0, f1, f3);
            swc1(f0, sp, 0x64);
            mul_s(f0, f1, f2);
            swc1(f0, sp, 0x68);
        } else {
            // 0x00434668
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x0043467c
                charge(ctx, 11);
                v1 = 0x41A00000;
                mtc1(v1, f1);
                mul_s(f0, f1, f4);
                swc1(f0, sp, 0x60);
                mul_s(f0, f1, f3);
                swc1(f0, sp, 0x64);
                mul_s(f0, f1, f2);
                swc1(f0, sp, 0x68);
            } else {
                // 0x00434674
                charge(ctx, 2);
            }
        }
    }
    // 0x004346f8
    charge(ctx, 27);
    lwc1(f1, sp, 0x50);
    lwc1(f0, sp, 0x60);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    lwc1(f1, sp, 0x54);
    lwc1(f0, sp, 0x64);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x54);
    lwc1(f1, sp, 0x58);
    lwc1(f0, sp, 0x68);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    lwc1(f2, sp, 0x50);
    lwc1(f1, sp, 0x54);
    lwc1(f0, sp, 0x58);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00434770 sub_434770 -- 424 bytes; frame 0x80: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WalkInColumn] ($a0 task, $a1 target, $f13 range) flattened distance from the walk point (+224) to the
// target: under the range, returns 1 when the member's model is within the range of the target too; else the column
// point (sub_4344F0), grounded (sub_1E13C0), queued on the mover (sub_1AFA20) and kept in +224; 0.
void sub_434770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00434770
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    mov_s(f21, f12);
    mov_s(f20, f13);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, sp, 0x70);
    swc1(f1, sp, 0x74);
    swc1(f0, sp, 0x78);
    lw(s0, a0, 60);
    s1 = 0;
    sw(zero, sp, 0x74);
    sw(zero, s0, kNpcWalkPosY);
    lwc1(f1, s0, kNpcWalkPosX);
    lwc1(f0, sp, 0x70);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x60);
    lwc1(f1, s0, kNpcWalkPosY);
    lwc1(f0, sp, 0x74);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x64);
    lwc1(f1, s0, kNpcWalkPosZ);
    lwc1(f0, sp, 0x78);
    sub_s(f0, f0, f1);
    swc1(f0, sp, 0x68);
    a0 = addiu(sp, 0x60);
    a1 = a0;
    jal(ctx, 0x4347F8u, gen::fn_sub_4C69F0_004c69f0);
    sw(zero, sp, 0x64);
    c_lt_s(f0, f20);
    if (cond(ctx)) {
        // 0x0043486c
        charge(ctx, 32);
        lw(v0, s0, kNpcOwnRes);
        lw(a0, v0, 296);
        jal(ctx, 0x434874u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 48);
        lwc1(f0, sp, 0x70);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x60);
        lw(v0, s0, kNpcOwnRes);
        lw(a0, v0, 296);
        jal(ctx, 0x434894u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 52);
        lwc1(f0, sp, 0x74);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x64);
        lw(v0, s0, kNpcOwnRes);
        lw(a0, v0, 296);
        jal(ctx, 0x4348B4u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 56);
        lwc1(f0, sp, 0x78);
        sub_s(f0, f0, f1);
        swc1(f0, sp, 0x68);
        a0 = addiu(sp, 0x60);
        a1 = a0;
        jal(ctx, 0x4348D4u, gen::fn_sub_4C69F0_004c69f0);
        sw(zero, sp, 0x64);
        c_lt_s(f0, f21);
        if (cond(ctx)) {
            // 0x004348ec
            charge(ctx, 1);
            s1 = 1;
        }
    } else {
        // 0x00434810
        charge(ctx, 23);
        a0 = addiu(sp, 0x50);
        a1 = s2;
        a2 = addiu(s0, kNpcWalkPosX);
        a3 = addiu(sp, 0x70);
        mov_s(f12, f21);
        jal(ctx, 0x434824u, gen::fn_sub_4344F0_004344f0);
        jal(ctx, 0x43482Cu, gen::fn_sub_1E13C0_001e13c0);
        lw(v0, s0, kNpcUnit);
        lw(a0, v0, 368);
        a1 = addiu(sp, 0x50);
        mov_s(f12, f0);
        jal(ctx, 0x434844u, gen::fn_sub_1AFA20_001afa20);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s0, kNpcWalkPosX);
        swc1(f1, s0, kNpcWalkPosY);
        swc1(f0, s0, kNpcWalkPosZ);
    }
    // 0x004348f0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00434920 sub_434920 -- 872 bytes; frame 0x80: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_WalkBehindHero] ($a0 task, $a1 target, $f13 range) like sub_434770 measured from the member's model: column
// place 3 walks straight, places 1 / 2 aim 150 behind and 80 to the left / right (mula.s / msub.s as the original).
void sub_434920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00434920
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f23, f12);
    mov_s(f22, f13);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, sp, 0x70);
    swc1(f1, sp, 0x74);
    swc1(f0, sp, 0x78);
    lw(s0, a0, 60);
    s1 = 0;
    lw(v0, s0, kNpcOwnRes);
    lw(a0, v0, 296);
    jal(ctx, 0x434970u, gen::fn_sub_318B60_00318b60);
    v0 = 0x6B0000;
    ld(v1, v0, 17944);  // 0x6B4618
    v0 = 0x6B0000;
    lwc1(f0, v0, 17952);  // 0x6B4620
    sd(v1, sp, 0x40);
    swc1(f0, sp, 0x48);
    lwc1(f1, s0, kNpcWalkPosX);
    lwc1(f0, sp, 0x70);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    lwc1(f21, sp, 0x74);
    lwc1(f0, s0, kNpcWalkPosY);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x64);
    lwc1(f20, sp, 0x78);
    lwc1(f0, s0, kNpcWalkPosZ);
    sub_s(f0, f0, f20);
    swc1(f0, sp, 0x68);
    a0 = addiu(sp, 0x60);
    a1 = a0;
    jal(ctx, 0x4349C8u, gen::fn_sub_4C69F0_004c69f0);
    c_lt_s(f0, f22);
    if (cond(ctx)) {
        // 0x00434c4c
        charge(ctx, 3);
        c_lt_s(f0, f23);
        if (cond(ctx)) {
            // 0x00434c58
            charge(ctx, 1);
            s1 = 1;
        }
    } else {
        // 0x004349dc
        charge(ctx, 7);
        lw(v1, s0, kNpcPc);
        v0 = addiu(gp, -17929);  // &0x7CE6E7
        v0 = addu(v0, v1);
        lb(v1, v0, 0);
        v0 = 3;
        if (v1 == v0) {
            // 0x00434bd8
            charge(ctx, 13);
            lwc1(f0, sp, 0x60);
            mul_s(f3, f0, f23);
            lwc1(f0, sp, 0x64);
            mul_s(f2, f0, f23);
            lwc1(f0, sp, 0x68);
            mul_s(f1, f0, f23);
            lwc1(f0, sp, 0x70);
            add_s(f0, f0, f3);
            swc1(f0, sp, 0x50);
            add_s(f0, f21, f2);
            swc1(f0, sp, 0x54);
            add_s(f0, f20, f1);
            swc1(f0, sp, 0x58);
        } else {
            // 0x004349f8
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00434af8
                charge(ctx, 56);
                v0 = 0x43160000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x60);
                mul_s(f3, f1, f0);
                lwc1(f0, sp, 0x64);
                mul_s(f2, f1, f0);
                lwc1(f0, sp, 0x68);
                mul_s(f1, f1, f0);
                lwc1(f5, sp, 0x70);
                add_s(f0, f5, f3);
                swc1(f0, sp, 0x50);
                mov_s(f4, f21);
                add_s(f3, f4, f2);
                swc1(f3, sp, 0x54);
                mov_s(f2, f20);
                add_s(f1, f2, f1);
                swc1(f1, sp, 0x58);
                sub_s(f0, f5, f0);
                swc1(f0, sp, 0x60);
                sub_s(f0, f4, f3);
                swc1(f0, sp, 0x64);
                sub_s(f0, f2, f1);
                swc1(f0, sp, 0x68);
                a0 = addiu(sp, 0x60);
                a1 = a0;
                jal(ctx, 0x434B5Cu, gen::fn_sub_4C69F0_004c69f0);
                lwc1(f6, sp, 0x44);
                lwc1(f5, sp, 0x68);
                lwc1(f2, sp, 0x48);
                lwc1(f4, sp, 0x64);
                mula_s(f4, f2);
                msub_s(f3, f5, f6);
                lwc1(f1, sp, 0x60);
                lwc1(f0, sp, 0x40);
                mula_s(f5, f0);
                msub_s(f2, f1, f2);
                mula_s(f1, f6);
                msub_s(f1, f4, f0);
                v0 = 0x42A00000;
                mtc1(v0, f0);
                mul_s(f3, f3, f0);
                mul_s(f2, f2, f0);
                mul_s(f1, f1, f0);
                lwc1(f0, sp, 0x50);
                add_s(f0, f0, f3);
                swc1(f0, sp, 0x50);
                lwc1(f0, sp, 0x54);
                add_s(f0, f0, f2);
                swc1(f0, sp, 0x54);
                lwc1(f0, sp, 0x58);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x58);
            } else {
                // 0x00434a04
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00434a18
                    charge(ctx, 56);
                    v0 = 0x43160000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x60);
                    mul_s(f3, f1, f0);
                    lwc1(f0, sp, 0x64);
                    mul_s(f2, f1, f0);
                    lwc1(f0, sp, 0x68);
                    mul_s(f1, f1, f0);
                    lwc1(f5, sp, 0x70);
                    add_s(f0, f5, f3);
                    swc1(f0, sp, 0x50);
                    mov_s(f4, f21);
                    add_s(f3, f4, f2);
                    swc1(f3, sp, 0x54);
                    mov_s(f2, f20);
                    add_s(f1, f2, f1);
                    swc1(f1, sp, 0x58);
                    sub_s(f0, f5, f0);
                    swc1(f0, sp, 0x60);
                    sub_s(f0, f4, f3);
                    swc1(f0, sp, 0x64);
                    sub_s(f0, f2, f1);
                    swc1(f0, sp, 0x68);
                    a0 = addiu(sp, 0x60);
                    a1 = a0;
                    jal(ctx, 0x434A7Cu, gen::fn_sub_4C69F0_004c69f0);
                    lwc1(f6, sp, 0x44);
                    lwc1(f5, sp, 0x68);
                    lwc1(f2, sp, 0x48);
                    lwc1(f4, sp, 0x64);
                    mula_s(f4, f2);
                    msub_s(f3, f5, f6);
                    lwc1(f1, sp, 0x60);
                    lwc1(f0, sp, 0x40);
                    mula_s(f5, f0);
                    msub_s(f2, f1, f2);
                    mula_s(f1, f6);
                    msub_s(f1, f4, f0);
                    v0 = lui(0xC2A0);
                    mtc1(v0, f0);
                    mul_s(f3, f3, f0);
                    mul_s(f2, f2, f0);
                    mul_s(f1, f1, f0);
                    lwc1(f0, sp, 0x50);
                    add_s(f0, f0, f3);
                    swc1(f0, sp, 0x50);
                    lwc1(f0, sp, 0x54);
                    add_s(f0, f0, f2);
                    swc1(f0, sp, 0x54);
                    lwc1(f0, sp, 0x58);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x58);
                } else {
                    // 0x00434a10
                    charge(ctx, 2);
                }
            }
        }
        // 0x00434c0c
        charge(ctx, 16);
        jal(ctx, 0x434C0Cu, gen::fn_sub_1E13C0_001e13c0);
        lw(v0, s0, kNpcUnit);
        lw(a0, v0, 368);
        a1 = addiu(sp, 0x50);
        mov_s(f12, f0);
        jal(ctx, 0x434C24u, gen::fn_sub_1AFA20_001afa20);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s0, kNpcWalkPosX);
        swc1(f1, s0, kNpcWalkPosY);
        swc1(f0, s0, kNpcWalkPosZ);
    }
    // 0x00434c5c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00434C90 sub_434C90 -- 152 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_TakeColumnPlace] ($a0 pc) the first place 1..3 that no entry of 0x7CE6E8[0..2] holds goes to entry pc - 1.
void sub_434C90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x00434c90
    enter(ctx, 5);  // entry check point + this block's cycles
    t0 = 1;
    a1 = t0;
    a2 = addiu(gp, -17928);  // &0x7CE6E8
    for (;;) {
        // 0x00434d14
        charge(ctx, 3);
        v1 = slti(t0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00434ca4
        charge(ctx, 4);
        a3 = 0;
        t1 = 0;
        for (;;) {
            // 0x00434ccc
            charge(ctx, 3);
            v1 = slti(t1, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00434cb4
            charge(ctx, 4);
            v1 = addu(a2, t1);
            lb(v1, v1, 0);
            if (v1 == t0) {
                // 0x00434cc4
                charge(ctx, 1);
                a3 = a1;
            }
            // 0x00434cc8
            charge(ctx, 1);
            t1 = addiu(t1, 1);
        }
        // 0x00434cd8
        charge(ctx, 4);
        v1 = dsll32(a3, 24);
        v1 = dsra32(v1, 24);
        if (v1 == 0) {
            goto L_00434ce8_7;
        }
        // 0x00434d10
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x00434d20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00434ce8_7:
    charge(ctx, 10);
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v1 = addiu(v1, -1);
    a0 = dsll32(v1, 24);
    a0 = dsra32(a0, 24);
    v1 = addiu(gp, -17928);  // &0x7CE6E8
    v1 = addu(v1, a0);
    sb(t0, v1, 0);
    // 0x00434d20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00434D30 sub_434D30 -- 296 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_OrderExplore] For members 1..3 with a think task that are not down: a fighting member (mode 5) only gets
// kNpcExploring = 1, an idle one (kNpcBusy == 0) mode 2 (sub_43C7A0). Then the tactic 0x7CE6BC = 1 and the column
// 0x7CE6E8[0..2] = 0. Called from the field event code (sub_1C3EB0) and follow states 8 / 9.
void sub_434D30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00434d30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 1;
    for (;;) {
        // 0x00434e00
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00434d4c
        charge(ctx, 10);
        v1 = sll(s1, 3);
        v1 = subu(v1, s1);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, 6048);  // &gFldUnitsPc
        v1 = addu(v1, a0);
        s0 = addiu(v1, 364);
        lw(v1, v1, 364);
        if (v1 != 0) {
            // 0x00434d74
            charge(ctx, 9);
            a0 = dsll32(s1, 24);
            a0 = dsra32(a0, 24);
            jal(ctx, 0x434D7Cu, gen::fn_sub_43C7F0_0043c7f0);
            a0 = dsll32(v0, 24);
            a0 = dsra32(a0, 24);
            v1 = 6;
            if (a0 != v1) {
                // 0x00434d98
                charge(ctx, 9);
                a0 = dsll32(s1, 24);
                a0 = dsra32(a0, 24);
                jal(ctx, 0x434DA0u, gen::fn_sub_43C7F0_0043c7f0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = 5;
                if (a0 != v1) {
                    // 0x00434dd4
                    charge(ctx, 5);
                    lw(v1, s0, 0);
                    lw(v1, v1, 60);
                    lb(v1, v1, kNpcBusy);
                    if (v1 == 0) {
                        // 0x00434de8
                        charge(ctx, 5);
                        a0 = dsll32(s1, 24);
                        a0 = dsra32(a0, 24);
                        a1 = 2;
                        jal(ctx, 0x434DF4u, gen::fn_sub_43C7A0_0043c7a0);
                    }
                } else {
                    // 0x00434dbc
                    charge(ctx, 6);
                    a0 = 1;
                    lw(v1, s0, 0);
                    lw(v1, v1, 60);
                    sb(a0, v1, kNpcExploring);
                }
            }
        }
        // 0x00434dfc
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00434e0c
    charge(ctx, 6);
    v1 = 1;
    sb(v1, gp, -17972);  // 0x7CE6BC
    a1 = 0;
    a0 = addiu(gp, -17928);  // &0x7CE6E8
    for (;;) {
        // 0x00434e30
        charge(ctx, 4);
        v1 = slti(a1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00434e24
        charge(ctx, 3);
        v1 = addu(a0, a1);
        sb(zero, v1, 0);
        a1 = addiu(a1, 1);
    }
    // 0x00434e40
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00434E60 sub_434E60 -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_OrderFollow] As sub_434D30 with mode 1 / kNpcExploring = 0 and the tactic 0.
void sub_434E60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00434e60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 1;
    for (;;) {
        // 0x00434f2c
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00434e7c
        charge(ctx, 10);
        v1 = sll(s1, 3);
        v1 = subu(v1, s1);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, 6048);  // &gFldUnitsPc
        v1 = addu(v1, a0);
        s0 = addiu(v1, 364);
        lw(v1, v1, 364);
        if (v1 != 0) {
            // 0x00434ea4
            charge(ctx, 9);
            a0 = dsll32(s1, 24);
            a0 = dsra32(a0, 24);
            jal(ctx, 0x434EACu, gen::fn_sub_43C7F0_0043c7f0);
            a0 = dsll32(v0, 24);
            a0 = dsra32(a0, 24);
            v1 = 6;
            if (a0 != v1) {
                // 0x00434ec8
                charge(ctx, 9);
                a0 = dsll32(s1, 24);
                a0 = dsra32(a0, 24);
                jal(ctx, 0x434ED0u, gen::fn_sub_43C7F0_0043c7f0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = 5;
                if (a0 != v1) {
                    // 0x00434f00
                    charge(ctx, 5);
                    lw(v1, s0, 0);
                    lw(v1, v1, 60);
                    lb(v1, v1, kNpcBusy);
                    if (v1 == 0) {
                        // 0x00434f14
                        charge(ctx, 5);
                        a0 = dsll32(s1, 24);
                        a0 = dsra32(a0, 24);
                        a1 = 1;
                        jal(ctx, 0x434F20u, gen::fn_sub_43C7A0_0043c7a0);
                    }
                } else {
                    // 0x00434eec
                    charge(ctx, 5);
                    lw(v1, s0, 0);
                    lw(v1, v1, 60);
                    sb(zero, v1, kNpcExploring);
                }
            }
        }
        // 0x00434f28
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00434f38
    charge(ctx, 7);
    sb(zero, gp, -17972);  // 0x7CE6BC
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00434F60 sub_434F60 -- 12 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_SetFormationFlag] *(s8 *)0x7CE6C0 = $a0 (follow state 0: 1 = keep the column formation states 10..12).
void sub_434F60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x00434f60
    enter(ctx, 3);  // entry check point + this block's cycles
    sb(a0, gp, -17968);  // 0x7CE6C0
}

// 0x00435060 sub_435060 -- 124 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_SetAllHeld] For members 1..3 with a live unit: think work kNpcHeld = $a0. (The enemy contact sub_44DFC0.)
void sub_435060(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x00435060
    enter(ctx, 7);  // entry check point + this block's cycles
    t2 = 1;
    a2 = t2;
    t0 = 0x870000;
    t0 = addiu(t0, 6048);  // &gFldUnitsPc
    a1 = t2;
    for (;;) {
        // 0x004350c8
        charge(ctx, 3);
        v1 = slti(t2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043507c
        charge(ctx, 8);
        t1 = 0;
        v1 = sll(t2, 3);
        v1 = subu(v1, t2);
        v1 = sll(v1, 6);
        a3 = addu(t0, v1);
        lw(v1, a3, 72);
        if (v1 != 0) {
            // 0x0043509c
            charge(ctx, 3);
            lw(v1, a3, 84);
            if (v1 != 0) {
                // 0x004350a8
                charge(ctx, 1);
                t1 = a2;
            }
        }
        // 0x004350ac
        charge(ctx, 3);
        v1 = sltu(0, t1);
        if (v1 == a1) {
            // 0x004350b8
            charge(ctx, 3);
            lw(v1, a3, 364);
            lw(v1, v1, 60);
            sb(a0, v1, kNpcHeld);
        }
        // 0x004350c4
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x004350d4
    charge(ctx, 2);
}

// 0x004350E0 sub_4350E0 -- 372 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_HoldOthers] ($a0 the member left out, $a1 held) for the other live members 1..3: kNpcHeld = held and the
// mover paused (sub_1B0260); when holding, a member playing its walk animation (sub_1DED40 of its persona) switches
// to the idle one (sub_1DDE00, sub_3182D0). From the field root / event tasks.
void sub_4350E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004350e0
    enter(ctx, 17);  // entry check point + this block's cycles
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
    s4 = 1;
    s3 = dsll32(a0, 24);
    s3 = dsra32(s3, 24);
    s2 = dsll32(s5, 24);
    s2 = dsra32(s2, 24);
    for (;;) {
        // 0x0043521c
        charge(ctx, 3);
        v1 = slti(s4, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00435124
        charge(ctx, 10);
        a1 = 0;
        v1 = sll(s4, 3);
        v1 = subu(v1, s4);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, 6048);  // &gFldUnitsPc
        s0 = addu(v1, a0);
        lw(v1, s0, 72);
        if (v1 != 0) {
            // 0x0043514c
            charge(ctx, 3);
            lw(v1, s0, 84);
            if (v1 != 0) {
                // 0x00435158
                charge(ctx, 1);
                a1 = 1;
            }
        }
        // 0x0043515c
        charge(ctx, 4);
        v1 = sltu(0, a1);
        a1 = 1;
        if (v1 == a1) {
            // 0x0043516c
            charge(ctx, 2);
            if (s3 != s4) {
                // 0x00435174
                charge(ctx, 5);
                lw(v0, s0, 364);
                lw(s1, v0, 60);
                sb(s5, s1, kNpcHeld);
                if (s2 != a1) {
                    // 0x00435204
                    charge(ctx, 5);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    a1 = 0;
                    jal(ctx, 0x435210u, gen::fn_sub_1B0260_001b0260);
                } else {
                    // 0x00435188
                    charge(ctx, 17);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    jal(ctx, 0x435190u, gen::fn_sub_1B0260_001b0260);
                    s0 = addiu(s0, 424);
                    lw(v0, s1, kNpcOwnRes);
                    lw(a0, v0, 296);
                    a1 = 0;
                    jal(ctx, 0x4351A8u, gen::fn_sub_318540_00318540);
                    s6 = dsll32(v0, 16);
                    s6 = dsra32(s6, 16);
                    lhu(a0, s0, 0);
                    jal(ctx, 0x4351BCu, gen::fn_sub_1DED40_001ded40);
                    if (s6 == v0) {
                        // 0x004351cc
                        charge(ctx, 14);
                        lhu(a0, s0, 0);
                        jal(ctx, 0x4351D0u, gen::fn_sub_1DDE00_001dde00);
                        a2 = dsll32(v0, 16);
                        a2 = dsra32(a2, 16);
                        lw(v0, s1, kNpcOwnRes);
                        lw(a0, v0, 296);
                        a1 = 0;
                        a3 = 8;
                        t0 = 1;
                        jal(ctx, 0x4351F4u, gen::fn_sub_3182D0_003182d0);
                    }
                }
            }
        }
        // 0x00435218
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x00435228
    charge(ctx, 11);
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

// 0x00435260 sub_435260 -- 124 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsHeld] Returns the s8 kNpcHeld of member $a0, or 1 when its unit is not live.
void sub_435260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00435260
    enter(ctx, 12);  // entry check point + this block's cycles
    a1 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    a0 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6120);  // &0x8717E8
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x00435290
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6132);  // &0x8717F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x004352a8
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x004352ac
    charge(ctx, 4);
    v1 = sltu(0, a1);
    v0 = 1;
    if (v1 == v0) {
        // 0x004352bc
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6412);  // &0x87190C
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        lw(v0, v0, 60);
        lb(v0, v0, kNpcHeld);
    }
    // 0x004352d4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004352E0 sub_4352E0 -- 144 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_AnyHeld] 1 when a live member 1..3 has kNpcHeld == 1, else 0.
void sub_4352E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x004352e0
    enter(ctx, 7);  // entry check point + this block's cycles
    t0 = 1;
    a0 = t0;
    a2 = 0x870000;
    a2 = addiu(a2, 6048);  // &gFldUnitsPc
    v0 = t0;
    for (;;) {
        // 0x00435358
        charge(ctx, 3);
        v1 = slti(t0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004352fc
        charge(ctx, 8);
        a3 = 0;
        v1 = sll(t0, 3);
        v1 = subu(v1, t0);
        v1 = sll(v1, 6);
        a1 = addu(a2, v1);
        lw(v1, a1, 72);
        if (v1 != 0) {
            // 0x0043531c
            charge(ctx, 3);
            lw(v1, a1, 84);
            if (v1 != 0) {
                // 0x00435328
                charge(ctx, 1);
                a3 = a0;
            }
        }
        // 0x0043532c
        charge(ctx, 3);
        v1 = sltu(0, a3);
        if (v1 == v0) {
            // 0x00435338
            charge(ctx, 5);
            lw(v1, a1, 364);
            lw(v1, v1, 60);
            lb(v1, v1, kNpcHeld);
            if (v1 != v0) {
                goto L_00435354;
            }
            goto L_0043534c_6;
        }
    L_00435354:
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x00435364
    charge(ctx, 1);
    v0 = 0;
    // 0x00435368 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0043534c_6:
    charge(ctx, 2);
    // 0x00435368 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00435370 sub_435370 -- 128 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_SetAvoidFights] For members 1..3 with a live unit: kNpcAvoidFights = $a0; then *(u8 *)0x7CDB10 = $a0.
// (sub_1C3F10.)
void sub_435370(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28};
    // 0x00435370
    enter(ctx, 7);  // entry check point + this block's cycles
    t2 = 1;
    a2 = t2;
    t0 = 0x870000;
    t0 = addiu(t0, 6048);  // &gFldUnitsPc
    a1 = t2;
    for (;;) {
        // 0x004353d8
        charge(ctx, 3);
        v1 = slti(t2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043538c
        charge(ctx, 8);
        t1 = 0;
        v1 = sll(t2, 3);
        v1 = subu(v1, t2);
        v1 = sll(v1, 6);
        a3 = addu(t0, v1);
        lw(v1, a3, 72);
        if (v1 != 0) {
            // 0x004353ac
            charge(ctx, 3);
            lw(v1, a3, 84);
            if (v1 != 0) {
                // 0x004353b8
                charge(ctx, 1);
                t1 = a2;
            }
        }
        // 0x004353bc
        charge(ctx, 3);
        v1 = sltu(0, t1);
        if (v1 == a1) {
            // 0x004353c8
            charge(ctx, 3);
            lw(v1, a3, 364);
            lw(v1, v1, 60);
            sb(a0, v1, kNpcAvoidFights);
        }
        // 0x004353d4
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x004353e4
    charge(ctx, 3);
    sb(a0, gp, -20960);  // 0x7CDB10
}

// 0x004353F0 sub_4353F0 -- 72 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Unit_GetThinkMode] ($a0 field unit) the unit's DatUnit kind (u16 at *(unit +72)): 0 (party) -> its think work
// +1 (the mode), 1 (shadow) -> +2 (the shadow think state); else 0.
void sub_4353F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004353f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    lw(v1, a0, 72);
    lhu(a1, v1, 0);
    if (a1 != 0) {
        // 0x00435418
        charge(ctx, 3);
        v1 = 1;
        if (a1 == v1) {
            // 0x00435424
            charge(ctx, 3);
            lw(v0, a0, 364);
            lw(v0, v0, 60);
            lb(v0, v0, 2);
        }
    } else {
        // 0x00435404
        charge(ctx, 5);
        lw(v0, a0, 364);
        lw(v0, v0, 60);
        lb(v0, v0, 1);
    }
    // 0x00435430 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00435440 sub_435440 -- 540 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CountHurtInReach] ($a0 pc) over the 4 party units: the live ones whose HP (sub_16C4F0 for the hero,
// sub_43C910) is below 100 % of the maximum (sub_16C5F0) and that member pc can reach (sub_1C7160 == 1). Used by the
// heal choice sub_43A9D0.
void sub_435440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00435440
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 0;
    s3 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s1 = addu(v0, v1);
    for (;;) {
        // 0x00435628
        charge(ctx, 3);
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043548c
        charge(ctx, 10);
        a0 = 0;
        v0 = sll(s3, 3);
        v0 = subu(v0, s3);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6048);  // &gFldUnitsPc
        s0 = addu(v0, v1);
        lw(v0, s0, 72);
        if (v0 != 0) {
            // 0x004354b4
            charge(ctx, 3);
            lw(v0, s0, 84);
            if (v0 != 0) {
                // 0x004354c0
                charge(ctx, 1);
                a0 = 1;
            }
        }
        // 0x004354c4
        charge(ctx, 4);
        v0 = sltu(0, a0);
        a0 = 1;
        if (v0 == a0) {
            // 0x004354d4
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00435570
                charge(ctx, 33);
                v1 = dsll32(s3, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                v0 = addu(v0, v1);
                lh(a0, v0, 424);
                jal(ctx, 0x435594u, gen::fn_sub_16C5F0_0016c5f0);
                v1 = v0 & 0xFFFF;
                v0 = sll(v1, 2);
                v1 = addu(v0, v1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 2);
                v0 = 100;
                div(v1, v0);
                mflo(v0);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                a0 = dsll32(s3, 24);
                a0 = dsra32(a0, 24);
                jal(ctx, 0x4355D0u, gen::fn_sub_43C910_0043c910);
                v1 = v0 & 0xFFFF;
                v0 = dsll32(s4, 16);
                v0 = dsra32(v0, 16);
                v1 = slt(v1, v0);
                v0 = 1;
                if (v1 == v0) {
                    // 0x004355f4
                    charge(ctx, 9);
                    v0 = 0x43FA0000;
                    mtc1(v0, f12);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x435604u, gen::fn_sub_1C7160_001c7160);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00435618
                        charge(ctx, 3);
                        v0 = addiu(s2, 1);
                        s2 = dsll32(v0, 24);
                        s2 = dsra32(s2, 24);
                    }
                }
            } else {
                // 0x004354dc
                charge(ctx, 23);
                jal(ctx, 0x4354DCu, gen::fn_sub_16C5F0_0016c5f0);
                v1 = v0 & 0xFFFF;
                v0 = sll(v1, 2);
                v1 = addu(v0, v1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 2);
                v0 = 100;
                div(v1, v0);
                mflo(v0);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                a0 = 1;
                jal(ctx, 0x435514u, gen::fn_sub_16C4F0_0016c4f0);
                v1 = v0 & 0xFFFF;
                v0 = dsll32(s4, 16);
                v0 = dsra32(v0, 16);
                v1 = slt(v1, v0);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00435538
                    charge(ctx, 9);
                    v0 = 0x43FA0000;
                    mtc1(v0, f12);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x435548u, gen::fn_sub_1C7160_001c7160);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x0043555c
                        charge(ctx, 5);
                        v0 = addiu(s2, 1);
                        s2 = dsll32(v0, 24);
                        s2 = dsra32(s2, 24);
                    }
                }
            }
        }
        // 0x00435624
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00435634
    charge(ctx, 10);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00435660 sub_435660 -- 432 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_FindAilingNear] ($a0 pc) the first other party unit (the hero included) whose think mode is 1 (follow) and
// whose persona status (sub_16C970) has bit 0x80, within reach (sub_1C7160); its index, else -1. (Inf: an ailment to
// cure.)
void sub_435660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00435660
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 0;
    s0 = dsll32(a0, 24);
    s0 = dsra32(s0, 24);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s2 = addu(v0, v1);
    for (;;) {
        // 0x004357e0
        charge(ctx, 3);
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004356a4
        charge(ctx, 2);
        if (s3 != s0) {
            // 0x004356ac
            charge(ctx, 10);
            a0 = 0;
            v0 = sll(s3, 3);
            v0 = subu(v0, s3);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            s1 = addu(v0, v1);
            lw(v1, s1, 72);
            if (v1 != 0) {
                // 0x004356d4
                charge(ctx, 3);
                lw(v0, s1, 84);
                if (v0 != 0) {
                    // 0x004356e0
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x004356e4
            charge(ctx, 4);
            v0 = sltu(0, a0);
            a0 = 1;
            if (v0 != a0) {
                goto L_004357dc;
            }
            // 0x004356f4
            charge(ctx, 2);
            if (s3 == 0) {
                // 0x004356fc
                charge(ctx, 5);
                jal(ctx, 0x4356FCu, gen::fn_sub_16C970_0016c970);
                v0 = v0 & 0x80;
                if (v0 == 0) {
                    goto L_004357dc;
                }
                // 0x00435710
                charge(ctx, 9);
                v0 = 0x43FA0000;
                mtc1(v0, f12);
                a0 = s2;
                a1 = s1;
                jal(ctx, 0x435720u, gen::fn_sub_1C7160_001c7160);
                v1 = 1;
                if (v0 != v1) {
                    goto L_004357dc;
                }
                goto L_00435734_9;
            }
            // 0x00435744
            charge(ctx, 4);
            a1 = 0;
            lhu(v0, v1, 0);
            if (v0 != 0) {
                // 0x00435768
                charge(ctx, 2);
                if (v0 == a0) {
                    // 0x00435770
                    charge(ctx, 3);
                    lw(v0, s1, 364);
                    lw(v0, v0, 60);
                    lb(a1, v0, 2);
                }
            } else {
                // 0x00435754
                charge(ctx, 5);
                lw(v0, s1, 364);
                lw(v0, v0, 60);
                lb(a1, v0, 1);
            }
            // 0x0043577c
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            v0 = 1;
            if (v1 != v0) {
                goto L_004357dc;
            }
            // 0x00435790
            charge(ctx, 6);
            lh(a0, s1, 424);
            jal(ctx, 0x435794u, gen::fn_sub_16C970_0016c970);
            v0 = v0 & 0x80;
            if (v0 == 0) {
                goto L_004357dc;
            }
            // 0x004357a8
            charge(ctx, 9);
            v0 = 0x43FA0000;
            mtc1(v0, f12);
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x4357B8u, gen::fn_sub_1C7160_001c7160);
            v1 = 1;
            if (v0 != v1) {
                goto L_004357dc;
            }
            goto L_004357cc_17;
        }
    L_004357dc:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x004357ec
    charge(ctx, 1);
    v0 = si(-1);
    // 0x004357f0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_00435734_9:
    charge(ctx, 4);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    // 0x004357f0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004357cc_17:
    charge(ctx, 4);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    // 0x004357f0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00435810 sub_435810 -- 472 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_FindCurer] Among members 1..3 in follow mode, the one whose skill list (sub_173380, 8 u16) holds skill 202
// or 203 and whose SP (sub_16C570) is the highest; -1 when none.
void sub_435810(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00435810
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = 0;
    s4 = si(-1);
    s0 = 1;
    for (;;) {
        // 0x004359b0
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00435844
        charge(ctx, 11);
        a0 = 0;
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6048);  // &gFldUnitsPc
        s3 = addu(v0, v1);
        s2 = addiu(s3, 72);
        lw(v0, s3, 72);
        if (v0 != 0) {
            // 0x00435870
            charge(ctx, 3);
            lw(v0, s3, 84);
            if (v0 != 0) {
                // 0x0043587c
                charge(ctx, 1);
                a0 = 1;
            }
        }
        // 0x00435880
        charge(ctx, 4);
        v1 = sltu(0, a0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00435890
            charge(ctx, 15);
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            v0 = addu(v0, v1);
            lhu(a0, v0, 424);
            jal(ctx, 0x4358ACu, gen::fn_sub_173380_00173380);
            s1 = v0;
            a0 = 0;
            lw(v0, s2, 0);
            lhu(v1, v0, 0);
            if (v1 != 0) {
                // 0x004358e0
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x004358ec
                    charge(ctx, 3);
                    lw(v0, s3, 364);
                    lw(v0, v0, 60);
                    lb(a0, v0, 2);
                }
            } else {
                // 0x004358cc
                charge(ctx, 5);
                lw(v0, s3, 364);
                lw(v0, v0, 60);
                lb(a0, v0, 1);
            }
            // 0x004358f8
            charge(ctx, 5);
            v1 = dsll32(a0, 24);
            v1 = dsra32(v1, 24);
            v0 = 1;
            if (v1 == v0) {
                // 0x0043590c
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x004359a0
                    charge(ctx, 3);
                    v0 = slti(s2, 8);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00435918
                    charge(ctx, 5);
                    v0 = sll(s2, 1);
                    v0 = addu(s1, v0);
                    lhu(v1, v0, 0);
                    if (v1 != 0) {
                        // 0x0043592c
                        charge(ctx, 3);
                        v0 = 202;
                        if (v1 != v0) {
                            // 0x00435968
                            charge(ctx, 3);
                            v0 = 203;
                            if (v1 == v0) {
                                // 0x00435974
                                charge(ctx, 7);
                                lh(a0, s3, 424);
                                jal(ctx, 0x435978u, gen::fn_sub_16C570_0016c570);
                                v0 = v0 & 0xFFFF;
                                at = slt(s5, v0);
                                if (at != 0) {
                                    // 0x00435990
                                    charge(ctx, 3);
                                    s4 = dsll32(s0, 24);
                                    s4 = dsra32(s4, 24);
                                    s5 = v0;
                                }
                            }
                        } else {
                            // 0x00435938
                            charge(ctx, 7);
                            lh(a0, s3, 424);
                            jal(ctx, 0x43593Cu, gen::fn_sub_16C570_0016c570);
                            v0 = v0 & 0xFFFF;
                            at = slt(s5, v0);
                            if (at != 0) {
                                // 0x00435954
                                charge(ctx, 5);
                                s4 = dsll32(s0, 24);
                                s4 = dsra32(s4, 24);
                                s5 = v0;
                            }
                        }
                    }
                    // 0x0043599c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
            }
        }
        // 0x004359ac
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x004359bc
    charge(ctx, 11);
    v0 = s4;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004359F0 sub_4359F0 -- 516 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_PlanPath] ($a0 task, $a1 x, $a2 z, $a3 pos (f32[3]), $t0 gx, $t1 gz) resets the cell / walk positions, the
// mover, the path records and queue; then expands (sub_433DE0) and pops the queue until the goal is reached or the
// start fails; 1 (the steps built by sub_4343D0) or 0.
void sub_4359F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004359f0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s5 = a1;
    s4 = a2;
    s3 = t0;
    s2 = t1;
    lwc1(f2, a3, 0);
    lwc1(f1, a3, 4);
    lwc1(f0, a3, 8);
    swc1(f2, sp, 0x70);
    swc1(f1, sp, 0x74);
    swc1(f0, sp, 0x78);
    lw(s1, a0, 60);
    sb(s5, s1, kNpcCellX);
    sb(s5, s1, kNpcWalkX);
    sb(s4, s1, kNpcCellZ);
    sb(s4, s1, kNpcWalkZ);
    lwc1(f0, sp, 0x70);
    swc1(f0, s1, kNpcCellPosX);
    lwc1(f0, sp, 0x78);
    swc1(f0, s1, kNpcCellPosZ);
    lw(v0, s1, kNpcUnit);
    lw(a0, v0, 368);
    jal(ctx, 0x435A68u, gen::fn_sub_1B00C0_001b00c0);
    lw(v0, s1, kNpcUnit);
    lw(a0, v0, 368);
    a1 = 0;
    jal(ctx, 0x435A7Cu, gen::fn_sub_1B0240_001b0240);
    v1 = 0;
    for (;;) {
        // 0x00435ab8
        charge(ctx, 3);
        v0 = slti(v1, 256);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00435a90
        charge(ctx, 10);
        v0 = sll(v1, 3);
        v0 = addu(s1, v0);
        sh(zero, v0, 528);
        sh(zero, v0, 530);
        sh(zero, v0, 532);
        sh(zero, v0, 534);
        v0 = sll(v1, 2);
        v0 = addu(s1, v0);
        sw(zero, v0, 2576);
        v1 = addiu(v1, 1);
    }
    // 0x00435ac4
    charge(ctx, 12);
    sw(zero, s1, kNpcCount);
    sb(s5, s1, kNpcStartX);
    sb(s4, s1, kNpcStartZ);
    sb(s3, s1, kNpcGoalX);
    sb(s2, s1, kNpcGoalZ);
    lwc1(f2, sp, 0x70);
    lwc1(f1, sp, 0x74);
    lwc1(f0, sp, 0x78);
    swc1(f2, s1, kNpcWalkPosX);
    swc1(f1, s1, kNpcWalkPosY);
    swc1(f0, s1, kNpcWalkPosZ);
    s1 = 0;
    for (;;) {
        // 0x00435af4
        charge(ctx, 11);
        a0 = s0;
        jal(ctx, 0x435AF8u, gen::fn_sub_433DE0_00433de0);
        a3 = dsll32(v0, 24);
        a3 = dsra32(a3, 24);
        lw(a1, s0, 60);
        lw(a0, a1, 2576);
        sw(zero, a1, 524);
        a2 = 0;
        for (;;) {
            // 0x00435b48
            charge(ctx, 3);
            v0 = slti(a2, 255);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00435b20
            charge(ctx, 6);
            v0 = sll(a2, 2);
            v1 = addu(a1, v0);
            lw(v0, v1, 2580);
            sw(v0, v1, 2576);
            if (v0 != 0) {
                // 0x00435b38
                charge(ctx, 3);
                lw(v0, a1, 524);
                v0 = addiu(v0, 1);
                sw(v0, a1, 524);
            }
            // 0x00435b44
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x00435b54
        charge(ctx, 11);
        v0 = sll(a0, 3);
        v1 = addu(a1, v0);
        lh(v0, v1, 528);
        sb(v0, a1, 248);
        lh(v0, v1, 530);
        sb(v0, a1, 249);
        v1 = dsll32(a3, 24);
        v1 = dsra32(v1, 24);
        v0 = 1;
        if (v1 == v0) {
            // 0x00435b80
            charge(ctx, 3);
            a3 = 2;
            s1 = dsll32(v0, 24);
            s1 = dsra32(s1, 24);
        }
        // 0x00435b8c
        charge(ctx, 5);
        v1 = dsll32(a3, 24);
        v1 = dsra32(v1, 24);
        v0 = 2;
        if (v1 == v0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00435ba0
    charge(ctx, 4);
    v0 = dsll32(s1, 24);
    v0 = dsra32(v0, 24);
    if (v0 != 0) {
        // 0x00435bc8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00435bb0
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x435BB4u, gen::fn_sub_4343D0_004343d0);
        v0 = 1;
    }
    // 0x00435bcc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00435C00 sub_435C00 -- 8692 bytes; frame 0x2B0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateFollow] Think mode 1 ($a0 task): first the support checks (a self skill when this member is the best
// curer, sub_456670; a cure on an ailing member, sub_456A90; a revive / heal walk towards a down member,
// kNpcSupport). Then the follow states (kNpcFollowState, jump table 0x7BC390): 0 decide (close to the hero -> the
// column states 7 / 10, else a path 1, or 13 off random floors), 1 plan a path to the hero (directly or through the
// nearest kind-8 cell), 3 / 4 walk the path step by step, 5 / 6 the last stretch to the hero, 7 / 8 / 9 walk beside
// the hero (explore order from the tactic, a nearby shadow -> mode 5), 10 / 11 / 12 take a place in the column and
// keep it (more than 800 away -> plan again), 13 / 14 / 15 off random floors: walk to the nearest cover point
// (type-18 scene resources) and stay there.
void sub_435C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00435c00
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2B0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(s1, a0, 60);
    lw(s6, gp, -19040);  // 0x7CE290
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    jal(ctx, 0x435C5Cu, gen::fn_sub_16C970_0016c970);
    if (v0 != 0) {
        // 0x00435c6c
        charge(ctx, 7);
        lw(s0, s1, kNpcPc);
        jal(ctx, 0x435C70u, gen::fn_sub_435810_00435810);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        if (s0 == v0) {
            // 0x00435c88
            charge(ctx, 5);
            a1 = dsll32(s0, 24);
            a1 = dsra32(a1, 24);
            a0 = s4;
            jal(ctx, 0x435C94u, gen::fn_sub_456670_00456670);
        }
    }
    // 0x00435c9c
    charge(ctx, 8);
    lb(a0, s1, kNpcPc);
    jal(ctx, 0x435CA0u, gen::fn_sub_435660_00435660);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x00435cbc
        charge(ctx, 7);
        lw(s0, s1, kNpcPc);
        jal(ctx, 0x435CC0u, gen::fn_sub_435810_00435810);
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        if (s0 == v1) {
            // 0x00435cd8
            charge(ctx, 11);
            a0 = dsll32(s0, 24);
            a0 = dsra32(a0, 24);
            jal(ctx, 0x435CE0u, gen::fn_sub_435660_00435660);
            sh(v0, s1, kNpcSkillTarget);
            lb(a1, s1, kNpcPc);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s4;
            jal(ctx, 0x435CFCu, gen::fn_sub_456A90_00456a90);
        }
    }
    // 0x00435d04
    charge(ctx, 10);
    lb(s0, s1, kNpcPc);
    s3 = 1;
    v1 = sll(s0, 3);
    v1 = subu(v1, s0);
    a0 = sll(v1, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 6048);  // &gFldUnitsPc
    s5 = addu(v1, a0);
    for (;;) {
        // 0x00435dd4
        charge(ctx, 3);
        v1 = slti(s3, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00435d2c
        charge(ctx, 2);
        if (s3 != s0) {
            // 0x00435d34
            charge(ctx, 10);
            a1 = 0;
            v1 = sll(s3, 3);
            v1 = subu(v1, s3);
            a0 = sll(v1, 6);
            v1 = 0x870000;
            v1 = addiu(v1, 6048);  // &gFldUnitsPc
            s2 = addu(v1, a0);
            lw(v1, s2, 72);
            if (v1 != 0) {
                // 0x00435d5c
                charge(ctx, 3);
                lw(v1, s2, 84);
                if (v1 != 0) {
                    // 0x00435d68
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x00435d6c
            charge(ctx, 4);
            a0 = sltu(0, a1);
            v1 = 1;
            if (a0 != v1) {
                goto L_00435dd0;
            }
            // 0x00435d7c
            charge(ctx, 8);
            a0 = s2;
            jal(ctx, 0x435D80u, gen::fn_sub_4353F0_004353f0);
            a0 = dsll32(v0, 24);
            a0 = dsra32(a0, 24);
            v1 = 6;
            if (a0 != v1) {
                goto L_00435dd0;
            }
            // 0x00435d9c
            charge(ctx, 9);
            v0 = 0x43FA0000;
            mtc1(v0, f12);
            a0 = s5;
            a1 = s2;
            jal(ctx, 0x435DACu, gen::fn_sub_1C7160_001c7160);
            v1 = 1;
            if (v0 != v1) {
                goto L_00435dd0;
            }
            goto L_00435dc0_14;
        }
    L_00435dd0:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00435de0
    charge(ctx, 1);
    v1 = 0;
L_00435de4:
    charge(ctx, 4);
    v1 = dsll32(v1, 24);
    v1 = dsra32(v1, 24);
    if (v1 != 0) {
        // 0x00435df4
        charge(ctx, 10);
        lb(s0, s1, kNpcPc);
        s3 = 1;
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6048);  // &gFldUnitsPc
        s5 = addu(v0, v1);
        for (;;) {
            // 0x00435ec4
            charge(ctx, 3);
            v0 = slti(s3, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00435e1c
            charge(ctx, 2);
            if (s3 != s0) {
                // 0x00435e24
                charge(ctx, 10);
                a0 = 0;
                v0 = sll(s3, 3);
                v0 = subu(v0, s3);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                s2 = addu(v0, v1);
                lw(v0, s2, 72);
                if (v0 != 0) {
                    // 0x00435e4c
                    charge(ctx, 3);
                    lw(v0, s2, 84);
                    if (v0 != 0) {
                        // 0x00435e58
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x00435e5c
                charge(ctx, 4);
                v1 = sltu(0, a0);
                v0 = 1;
                if (v1 != v0) {
                    goto L_00435ec0;
                }
                // 0x00435e6c
                charge(ctx, 8);
                a0 = s2;
                jal(ctx, 0x435E70u, gen::fn_sub_4353F0_004353f0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = 6;
                if (v1 != v0) {
                    goto L_00435ec0;
                }
                // 0x00435e8c
                charge(ctx, 9);
                v0 = 0x43FA0000;
                mtc1(v0, f12);
                a0 = s5;
                a1 = s2;
                jal(ctx, 0x435E9Cu, gen::fn_sub_1C7160_001c7160);
                v1 = 1;
                if (v0 != v1) {
                    goto L_00435ec0;
                }
                goto L_00435eb0_27;
            }
        L_00435ec0:
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x00435ed0
        charge(ctx, 1);
        a0 = 0;
    L_00435ed4:
        charge(ctx, 5);
        jal(ctx, 0x435ED4u, gen::fn_sub_43C910_0043c910);
        v1 = v0 & 0xFFFF;
        if (v1 == 0) {
            // 0x00435ee8
            charge(ctx, 10);
            lb(s0, s1, kNpcPc);
            s3 = 1;
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            s5 = addu(v0, v1);
            for (;;) {
                // 0x00435fb8
                charge(ctx, 3);
                v0 = slti(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00435f10
                charge(ctx, 2);
                if (s3 != s0) {
                    // 0x00435f18
                    charge(ctx, 10);
                    a0 = 0;
                    v0 = sll(s3, 3);
                    v0 = subu(v0, s3);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s2 = addu(v0, v1);
                    lw(v0, s2, 72);
                    if (v0 != 0) {
                        // 0x00435f40
                        charge(ctx, 3);
                        lw(v0, s2, 84);
                        if (v0 != 0) {
                            // 0x00435f4c
                            charge(ctx, 1);
                            a0 = 1;
                        }
                    }
                    // 0x00435f50
                    charge(ctx, 4);
                    v1 = sltu(0, a0);
                    v0 = 1;
                    if (v1 != v0) {
                        goto L_00435fb4;
                    }
                    // 0x00435f60
                    charge(ctx, 8);
                    a0 = s2;
                    jal(ctx, 0x435F64u, gen::fn_sub_4353F0_004353f0);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = 6;
                    if (v1 != v0) {
                        goto L_00435fb4;
                    }
                    // 0x00435f80
                    charge(ctx, 9);
                    v0 = 0x43FA0000;
                    mtc1(v0, f12);
                    a0 = s5;
                    a1 = s2;
                    jal(ctx, 0x435F90u, gen::fn_sub_1C7160_001c7160);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_00435fb4;
                    }
                    goto L_00435fa4_40;
                }
            L_00435fb4:
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x00435fc4
            charge(ctx, 1);
            a0 = 0;
        L_00435fc8:
            charge(ctx, 6);
            jal(ctx, 0x435FC8u, gen::fn_sub_43C180_0043c180);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (v0 != 0) {
                // 0x004361e0
                charge(ctx, 10);
                lb(s0, s1, kNpcPc);
                s3 = 1;
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                s5 = addu(v0, v1);
                for (;;) {
                    // 0x004362b0
                    charge(ctx, 3);
                    v0 = slti(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00436208
                    charge(ctx, 2);
                    if (s3 != s0) {
                        // 0x00436210
                        charge(ctx, 10);
                        a0 = 0;
                        v0 = sll(s3, 3);
                        v0 = subu(v0, s3);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6048);  // &gFldUnitsPc
                        s2 = addu(v0, v1);
                        lw(v0, s2, 72);
                        if (v0 != 0) {
                            // 0x00436238
                            charge(ctx, 3);
                            lw(v0, s2, 84);
                            if (v0 != 0) {
                                // 0x00436244
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00436248
                        charge(ctx, 4);
                        v1 = sltu(0, a0);
                        v0 = 1;
                        if (v1 != v0) {
                            goto L_004362ac;
                        }
                        // 0x00436258
                        charge(ctx, 8);
                        a0 = s2;
                        jal(ctx, 0x43625Cu, gen::fn_sub_4353F0_004353f0);
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = 6;
                        if (v1 != v0) {
                            goto L_004362ac;
                        }
                        // 0x00436278
                        charge(ctx, 9);
                        v0 = 0x43FA0000;
                        mtc1(v0, f12);
                        a0 = s5;
                        a1 = s2;
                        jal(ctx, 0x436288u, gen::fn_sub_1C7160_001c7160);
                        v1 = 1;
                        if (v0 != v1) {
                            goto L_004362ac;
                        }
                        goto L_0043629c_79;
                    }
                L_004362ac:
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x004362bc
                charge(ctx, 1);
                a0 = 0;
            L_004362c0:
                charge(ctx, 7);
                lw(s0, s1, kNpcPc);
                jal(ctx, 0x4362C4u, gen::fn_sub_43C180_0043c180);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                if (s0 == v1) {
                    // 0x004362dc
                    charge(ctx, 11);
                    s0 = dsll32(s0, 24);
                    s0 = dsra32(s0, 24);
                    s3 = 1;
                    v1 = sll(s0, 3);
                    v1 = subu(v1, s0);
                    a0 = sll(v1, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6048);  // &gFldUnitsPc
                    s5 = addu(v1, a0);
                    for (;;) {
                        // 0x004363b0
                        charge(ctx, 3);
                        v1 = slti(s3, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00436308
                        charge(ctx, 2);
                        if (s3 != s0) {
                            // 0x00436310
                            charge(ctx, 10);
                            a1 = 0;
                            v1 = sll(s3, 3);
                            v1 = subu(v1, s3);
                            a0 = sll(v1, 6);
                            v1 = 0x870000;
                            v1 = addiu(v1, 6048);  // &gFldUnitsPc
                            s2 = addu(v1, a0);
                            lw(v1, s2, 72);
                            if (v1 != 0) {
                                // 0x00436338
                                charge(ctx, 3);
                                lw(v1, s2, 84);
                                if (v1 != 0) {
                                    // 0x00436344
                                    charge(ctx, 1);
                                    a1 = 1;
                                }
                            }
                            // 0x00436348
                            charge(ctx, 4);
                            a0 = sltu(0, a1);
                            v1 = 1;
                            if (a0 != v1) {
                                goto L_004363ac;
                            }
                            // 0x00436358
                            charge(ctx, 8);
                            a0 = s2;
                            jal(ctx, 0x43635Cu, gen::fn_sub_4353F0_004353f0);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = 6;
                            if (a0 != v1) {
                                goto L_004363ac;
                            }
                            // 0x00436378
                            charge(ctx, 9);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s5;
                            a1 = s2;
                            jal(ctx, 0x436388u, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_004363ac;
                            }
                            goto L_0043639c_92;
                        }
                    L_004363ac:
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                    // 0x004363bc
                    charge(ctx, 1);
                    v1 = 0;
                L_004363c0:
                    charge(ctx, 6);
                    v1 = dsll32(v1, 24);
                    v1 = dsra32(v1, 24);
                    sh(v1, s1, kNpcSkillTarget);
                    v1 = 1;
                    sb(v1, s1, kNpcSupport);
                    sb(zero, s1, kNpcSupportState);
                }
            } else {
                // 0x00435fe0
                charge(ctx, 10);
                lb(s0, s1, kNpcPc);
                s3 = 1;
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                s5 = addu(v0, v1);
                for (;;) {
                    // 0x004360b0
                    charge(ctx, 3);
                    v0 = slti(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00436008
                    charge(ctx, 2);
                    if (s3 != s0) {
                        // 0x00436010
                        charge(ctx, 10);
                        a0 = 0;
                        v0 = sll(s3, 3);
                        v0 = subu(v0, s3);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6048);  // &gFldUnitsPc
                        s2 = addu(v0, v1);
                        lw(v0, s2, 72);
                        if (v0 != 0) {
                            // 0x00436038
                            charge(ctx, 3);
                            lw(v0, s2, 84);
                            if (v0 != 0) {
                                // 0x00436044
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00436048
                        charge(ctx, 4);
                        v1 = sltu(0, a0);
                        v0 = 1;
                        if (v1 != v0) {
                            goto L_004360ac;
                        }
                        // 0x00436058
                        charge(ctx, 8);
                        a0 = s2;
                        jal(ctx, 0x43605Cu, gen::fn_sub_4353F0_004353f0);
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = 6;
                        if (v1 != v0) {
                            goto L_004360ac;
                        }
                        // 0x00436078
                        charge(ctx, 9);
                        v0 = 0x43FA0000;
                        mtc1(v0, f12);
                        a0 = s5;
                        a1 = s2;
                        jal(ctx, 0x436088u, gen::fn_sub_1C7160_001c7160);
                        v1 = 1;
                        if (v0 != v1) {
                            goto L_004360ac;
                        }
                        goto L_0043609c_53;
                    }
                L_004360ac:
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x004360bc
                charge(ctx, 1);
                a0 = 0;
            L_004360c0:
                charge(ctx, 7);
                lw(s0, s1, kNpcPc);
                jal(ctx, 0x4360C4u, gen::fn_sub_43C340_0043c340);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                if (s0 == v1) {
                    // 0x004360dc
                    charge(ctx, 11);
                    s0 = dsll32(s0, 24);
                    s0 = dsra32(s0, 24);
                    s3 = 1;
                    v1 = sll(s0, 3);
                    v1 = subu(v1, s0);
                    a0 = sll(v1, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6048);  // &gFldUnitsPc
                    s5 = addu(v1, a0);
                    for (;;) {
                        // 0x004361b0
                        charge(ctx, 3);
                        v1 = slti(s3, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00436108
                        charge(ctx, 2);
                        if (s3 != s0) {
                            // 0x00436110
                            charge(ctx, 10);
                            a1 = 0;
                            v1 = sll(s3, 3);
                            v1 = subu(v1, s3);
                            a0 = sll(v1, 6);
                            v1 = 0x870000;
                            v1 = addiu(v1, 6048);  // &gFldUnitsPc
                            s2 = addu(v1, a0);
                            lw(v1, s2, 72);
                            if (v1 != 0) {
                                // 0x00436138
                                charge(ctx, 3);
                                lw(v1, s2, 84);
                                if (v1 != 0) {
                                    // 0x00436144
                                    charge(ctx, 1);
                                    a1 = 1;
                                }
                            }
                            // 0x00436148
                            charge(ctx, 4);
                            a0 = sltu(0, a1);
                            v1 = 1;
                            if (a0 != v1) {
                                goto L_004361ac;
                            }
                            // 0x00436158
                            charge(ctx, 8);
                            a0 = s2;
                            jal(ctx, 0x43615Cu, gen::fn_sub_4353F0_004353f0);
                            a0 = dsll32(v0, 24);
                            a0 = dsra32(a0, 24);
                            v1 = 6;
                            if (a0 != v1) {
                                goto L_004361ac;
                            }
                            // 0x00436178
                            charge(ctx, 9);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s5;
                            a1 = s2;
                            jal(ctx, 0x436188u, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_004361ac;
                            }
                            goto L_0043619c_66;
                        }
                    L_004361ac:
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                    // 0x004361bc
                    charge(ctx, 1);
                    v1 = 0;
                L_004361c0:
                    charge(ctx, 8);
                    v1 = dsll32(v1, 24);
                    v1 = dsra32(v1, 24);
                    sh(v1, s1, kNpcSkillTarget);
                    v1 = 1;
                    sb(v1, s1, kNpcSupport);
                    sb(zero, s1, kNpcSupportState);
                }
            }
        }
    }
    // 0x004363d8
    charge(ctx, 4);
    lb(v1, s1, kNpcFollowState);
    at = sltiu(v1, 16);
    if (at != 0) {
        // 0x004363e8
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -15472);  // &0x7BC390
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x436404u:  // table[0]
            // 0x00436404: follow state 0: decide
            charge(ctx, 16);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = 1;
            jal(ctx, 0x436410u, gen::fn_sub_1B0240_001b0240);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            jal(ctx, 0x436420u, gen::fn_sub_1B00C0_001b00c0);
            v0 = 0x44480000;
            mtc1(v0, f12);
            lw(a0, s1, kNpcUnit);
            jal(ctx, 0x436434u, gen::fn_sub_1C7130_001c7130);
            if (v0 != 0) {
                // 0x0043648c
                charge(ctx, 24);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x4364ACu, gen::fn_sub_318B60_00318b60);
                s0 = v0;
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                jal(ctx, 0x4364C0u, gen::fn_sub_318B60_00318b60);
                a0 = s0;
                a1 = addiu(v0, 48);
                lwc1(f12, s6, 16);
                lwc1(f13, s6, 20);
                jal(ctx, 0x4364D8u, gen::fn_sub_1C6450_001c6450);
                a1 = 1;
                if (v0 != a1) {
                    // 0x004365e0
                    charge(ctx, 5);
                    jal(ctx, 0x4365E0u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x004365f4
                        charge(ctx, 5);
                        jal(ctx, 0x4365F4u, gen::fn_sub_1A02C0_001a02c0);
                        v1 = 1;
                        if (v0 == v1) {
                            goto L_00436608;
                        }
                        // 0x00436618
                        charge(ctx, 2);
                        v1 = 13;
                        sb(v1, s1, kNpcFollowState);
                        goto L_00436620;
                    }
                L_00436608:
                    charge(ctx, 4);
                    v1 = 1;
                    sb(v1, s1, kNpcFollowState);
                } else {
                    // 0x004364ec
                    charge(ctx, 3);
                    lb(v1, gp, -17968);  // 0x7CE6C0
                    if (v1 == a1) {
                        // 0x004365b4
                        charge(ctx, 4);
                        lb(a0, s1, kNpcFollowState);
                        v1 = slti(a0, 10);
                        if (v1 == 0) {
                            // 0x004365c4
                            charge(ctx, 3);
                            at = slti(a0, 13);
                            if (at == 0) {
                                goto L_004365d0;
                            }
                            goto L_00436620;
                        }
                    L_004365d0:
                        charge(ctx, 4);
                        v1 = 10;
                        sb(v1, s1, kNpcFollowState);
                    } else {
                        // 0x004364f8
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00436508
                            charge(ctx, 4);
                            lb(a0, s1, kNpcFollowState);
                            v1 = 7;
                            if (a0 != v1) {
                                // 0x00436518
                                charge(ctx, 5);
                                sb(v1, s1, kNpcFollowState);
                                lw(a0, s1, kNpcPc);
                                v1 = 3;
                                if (a0 == v1) {
                                    // 0x00436590
                                    charge(ctx, 3);
                                    lb(v1, gp, -17948);  // 0x7CE6D4
                                    if (v1 == a1) {
                                        // 0x0043659c
                                        charge(ctx, 6);
                                        a0 = dsll32(a0, 24);
                                        a0 = dsra32(a0, 24);
                                        jal(ctx, 0x4365A4u, gen::fn_sub_437E00_00437e00);
                                    }
                                } else {
                                    // 0x0043652c
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (a0 == v1) {
                                        // 0x0043656c
                                        charge(ctx, 3);
                                        lb(v1, gp, -17952);  // 0x7CE6D0
                                        if (v1 == a1) {
                                            // 0x00436578
                                            charge(ctx, 6);
                                            a0 = dsll32(a0, 24);
                                            a0 = dsra32(a0, 24);
                                            jal(ctx, 0x436580u, gen::fn_sub_437E00_00437e00);
                                        }
                                    } else {
                                        // 0x00436538
                                        charge(ctx, 2);
                                        if (a0 == a1) {
                                            // 0x00436548
                                            charge(ctx, 3);
                                            lb(v1, gp, -17956);  // 0x7CE6CC
                                            if (v1 == a1) {
                                                // 0x00436554
                                                charge(ctx, 6);
                                                a0 = dsll32(a0, 24);
                                                a0 = dsra32(a0, 24);
                                                jal(ctx, 0x43655Cu, gen::fn_sub_437E00_00437e00);
                                            }
                                        } else {
                                            // 0x00436540
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        } else {
                            // 0x00436500
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x00436444
                charge(ctx, 5);
                jal(ctx, 0x436444u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                v1 = 1;
                if (v0 != v1) {
                    // 0x00436458
                    charge(ctx, 5);
                    jal(ctx, 0x436458u, gen::fn_sub_1A02C0_001a02c0);
                    v1 = 1;
                    if (v0 == v1) {
                        goto L_0043646c;
                    }
                    // 0x0043647c
                    charge(ctx, 4);
                    v1 = 13;
                    sb(v1, s1, kNpcFollowState);
                    goto L_00436620;
                }
            L_0043646c:
                charge(ctx, 4);
                v1 = 1;
                sb(v1, s1, kNpcFollowState);
            }
        L_00436620:
            charge(ctx, 4);
            lb(a0, s1, kNpcBusy);
            v1 = 1;
            if (a0 == v1) {
                // 0x00436630
                charge(ctx, 3);
                sb(zero, s1, kNpcBusy);
            }
            break;
        case 0x43663Cu:  // table[7]
            // 0x0043663c: state 7: join the hero
            charge(ctx, 50);
            lw(v1, s1, kNpcPc);
            v0 = addiu(gp, -17929);  // &0x7CE6E7
            v0 = addu(v0, v1);
            sb(zero, v0, 0);
            lw(s0, s1, kNpcUnit);
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            jal(ctx, 0x436658u, gen::fn_sub_318B60_00318b60);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0x220);
            swc1(f1, sp, 0x224);
            swc1(f0, sp, 0x228);
            v0 = 0x870000;
            lw(a0, v0, 6576);  // 0x8719B0
            jal(ctx, 0x436680u, gen::fn_sub_318B60_00318b60);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0x210);
            swc1(f1, sp, 0x214);
            swc1(f0, sp, 0x218);
            lwc1(f1, sp, 0x220);
            lwc1(f0, sp, 0x210);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x230);
            lwc1(f1, sp, 0x224);
            lwc1(f0, sp, 0x214);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x234);
            lwc1(f1, sp, 0x228);
            lwc1(f0, sp, 0x218);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x238);
            a0 = addiu(sp, 0x230);
            a1 = a0;
            jal(ctx, 0x4366D8u, gen::fn_sub_4C69F0_004c69f0);
            v0 = 0x44480000;
            mtc1(v0, f12);
            a0 = s0;
            jal(ctx, 0x4366ECu, gen::fn_sub_1C7130_001c7130);
            a0 = sltu(0, v0);
            v1 = 1;
            if (a0 != v1) {
                // 0x00436770
                charge(ctx, 3);
                sb(v1, s1, kNpcFollowState);
            } else {
                // 0x00436704
                charge(ctx, 27);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                a1 = 0;
                jal(ctx, 0x436710u, gen::fn_sub_1B0240_001b0240);
                lw(v1, s1, kNpcPc);
                v0 = addiu(gp, -17929);  // &0x7CE6E7
                v0 = addu(v0, v1);
                sb(v1, v0, 0);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x436730u, gen::fn_sub_1B00C0_001b00c0);
                lw(v0, s1, kNpcOwnRes);
                lw(a0, v0, 296);
                jal(ctx, 0x436740u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, s1, kNpcWalkPosX);
                swc1(f1, s1, kNpcWalkPosY);
                swc1(f0, s1, kNpcWalkPosZ);
                v1 = 8;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x43677Cu:  // table[8]
            // 0x0043677c: state 8: beside the hero
            charge(ctx, 4);
            lb(v1, gp, -17972);  // 0x7CE6BC
            v0 = 1;
            if (v1 != v0) {
                // 0x0043679c
                charge(ctx, 7);
                lb(a1, s1, kNpcPc);
                a0 = s4;
                jal(ctx, 0x4367A4u, gen::fn_sub_43A0B0_0043a0b0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x004367d0
                    charge(ctx, 7);
                    v0 = 0x44480000;
                    mtc1(v0, f12);
                    lw(a0, s1, kNpcUnit);
                    jal(ctx, 0x4367DCu, gen::fn_sub_1C7130_001c7130);
                    if (v0 != 0) {
                        // 0x004367fc
                        charge(ctx, 45);
                        lw(s0, s1, kNpcUnit);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x436808u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x1F0);
                        swc1(f1, sp, 0x1F4);
                        swc1(f0, sp, 0x1F8);
                        v0 = 0x870000;
                        lw(a0, v0, 6576);  // 0x8719B0
                        jal(ctx, 0x436830u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x1E0);
                        swc1(f1, sp, 0x1E4);
                        swc1(f0, sp, 0x1E8);
                        lwc1(f1, sp, 0x1F0);
                        lwc1(f0, sp, 0x1E0);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x200);
                        lwc1(f1, sp, 0x1F4);
                        lwc1(f0, sp, 0x1E4);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x204);
                        lwc1(f1, sp, 0x1F8);
                        lwc1(f0, sp, 0x1E8);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x208);
                        a0 = addiu(sp, 0x200);
                        a1 = a0;
                        jal(ctx, 0x436888u, gen::fn_sub_4C69F0_004c69f0);
                        v0 = 0x43160000;
                        mtc1(v0, f12);
                        a0 = s0;
                        jal(ctx, 0x43689Cu, gen::fn_sub_1C7130_001c7130);
                        v1 = sltu(0, v0);
                        if (v1 != 0) {
                            // 0x004368c0
                            charge(ctx, 6);
                            lw(v0, s1, kNpcUnit);
                            lw(a0, v0, 368);
                            jal(ctx, 0x4368C8u, gen::fn_sub_1B00C0_001b00c0);
                        } else {
                            // 0x004368b0
                            charge(ctx, 4);
                            v1 = 9;
                            sb(v1, s1, kNpcFollowState);
                        }
                    } else {
                        // 0x004367ec
                        charge(ctx, 4);
                        v1 = 1;
                        sb(v1, s1, kNpcFollowState);
                    }
                } else {
                    // 0x004367b8
                    charge(ctx, 6);
                    lb(a0, s1, kNpcPc);
                    a1 = 5;
                    jal(ctx, 0x4367C0u, gen::fn_sub_43C7A0_0043c7a0);
                }
            } else {
                // 0x0043678c
                charge(ctx, 4);
                jal(ctx, 0x43678Cu, gen::fn_sub_434D30_00434d30);
            }
            break;
        case 0x4368D8u:  // table[9]
            // 0x004368d8: state 9: walk behind the hero
            charge(ctx, 4);
            lb(v1, gp, -17972);  // 0x7CE6BC
            v0 = 1;
            if (v1 != v0) {
                // 0x004368f8
                charge(ctx, 7);
                lb(a1, s1, kNpcPc);
                a0 = s4;
                jal(ctx, 0x436900u, gen::fn_sub_43A0B0_0043a0b0);
                a0 = 1;
                if (v0 != a0) {
                    // 0x0043692c
                    charge(ctx, 4);
                    lw(v1, s1, kNpcPc);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x00436988
                        charge(ctx, 4);
                        v0 = 0x43960000;
                        mtc1(v0, f21);
                        v0 = 0x43C80000;
                        mtc1(v0, f20);
                    } else {
                        // 0x0043693c
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00436970
                            charge(ctx, 6);
                            v0 = 0x43480000;
                            mtc1(v0, f21);
                            v0 = 0x437A0000;
                            mtc1(v0, f20);
                        } else {
                            // 0x00436948
                            charge(ctx, 2);
                            if (v1 == a0) {
                                // 0x00436958
                                charge(ctx, 6);
                                v0 = 0x43480000;
                                mtc1(v0, f21);
                                v0 = 0x437A0000;
                                mtc1(v0, f20);
                            } else {
                                // 0x00436950
                                charge(ctx, 2);
                            }
                        }
                    }
                    // 0x00436998
                    charge(ctx, 12);
                    lw(v0, s1, kNpcHeroRes);
                    lw(a0, v0, 296);
                    jal(ctx, 0x4369A0u, gen::fn_sub_318B60_00318b60);
                    a0 = s4;
                    a1 = addiu(v0, 48);
                    mov_s(f12, f21);
                    mov_s(f13, f20);
                    jal(ctx, 0x4369B8u, gen::fn_sub_434920_00434920);
                    if (v0 != 0) {
                        // 0x004369c8
                        charge(ctx, 4);
                        v1 = 8;
                        sb(v1, s1, kNpcFollowState);
                    }
                } else {
                    // 0x00436914
                    charge(ctx, 6);
                    lb(a0, s1, kNpcPc);
                    a1 = 5;
                    jal(ctx, 0x43691Cu, gen::fn_sub_43C7A0_0043c7a0);
                }
            } else {
                // 0x004368e8
                charge(ctx, 4);
                jal(ctx, 0x4368E8u, gen::fn_sub_434D30_00434d30);
            }
            break;
        case 0x4369D8u:  // table[10]
            // 0x004369d8: state 10: take a column place
            charge(ctx, 50);
            lw(v1, s1, kNpcPc);
            v0 = addiu(gp, -17929);  // &0x7CE6E7
            v0 = addu(v0, v1);
            sb(zero, v0, 0);
            lw(s0, s1, kNpcUnit);
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            jal(ctx, 0x4369F4u, gen::fn_sub_318B60_00318b60);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0x1C0);
            swc1(f1, sp, 0x1C4);
            swc1(f0, sp, 0x1C8);
            v0 = 0x870000;
            lw(a0, v0, 6576);  // 0x8719B0
            jal(ctx, 0x436A1Cu, gen::fn_sub_318B60_00318b60);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0x1B0);
            swc1(f1, sp, 0x1B4);
            swc1(f0, sp, 0x1B8);
            lwc1(f1, sp, 0x1C0);
            lwc1(f0, sp, 0x1B0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1D0);
            lwc1(f1, sp, 0x1C4);
            lwc1(f0, sp, 0x1B4);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1D4);
            lwc1(f1, sp, 0x1C8);
            lwc1(f0, sp, 0x1B8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1D8);
            a0 = addiu(sp, 0x1D0);
            a1 = a0;
            jal(ctx, 0x436A74u, gen::fn_sub_4C69F0_004c69f0);
            v0 = 0x44480000;
            mtc1(v0, f12);
            a0 = s0;
            jal(ctx, 0x436A88u, gen::fn_sub_1C7130_001c7130);
            v1 = sltu(0, v0);
            v0 = 1;
            if (v1 != v0) {
                // 0x00436acc
                charge(ctx, 5);
                jal(ctx, 0x436ACCu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                v1 = 1;
                if (v0 != v1) {
                    // 0x00436ae0
                    charge(ctx, 5);
                    jal(ctx, 0x436AE0u, gen::fn_sub_1A02C0_001a02c0);
                    v1 = 1;
                    if (v0 == v1) {
                        goto L_00436af4;
                    }
                    // 0x00436b04
                    charge(ctx, 2);
                    v0 = 13;
                    sb(v0, s1, kNpcFollowState);
                    goto L_00436b0c;
                }
            L_00436af4:
                charge(ctx, 4);
                v0 = 1;
                sb(v0, s1, kNpcFollowState);
            } else {
                // 0x00436aa0
                charge(ctx, 11);
                lb(a0, s1, kNpcPc);
                jal(ctx, 0x436AA4u, gen::fn_sub_434C90_00434c90);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x436AB4u, gen::fn_sub_1B00C0_001b00c0);
                v0 = 11;
                sb(v0, s1, kNpcFollowState);
            }
        L_00436b0c:
            charge(ctx, 7);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = 0;
            jal(ctx, 0x436B18u, gen::fn_sub_1B0240_001b0240);
            break;
        case 0x436B28u:  // table[11]
            // 0x00436b28: state 11: in the column
            charge(ctx, 7);
            lw(a0, s1, kNpcPc);
            v1 = addiu(gp, -17929);  // &0x7CE6E7
            v1 = addu(v1, a0);
            lb(a0, v1, 0);
            v1 = 3;
            if (a0 == v1) {
                // 0x00436d54
                charge(ctx, 45);
                lw(s0, s1, kNpcUnit);
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                jal(ctx, 0x436D60u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x130);
                swc1(f1, sp, 0x134);
                swc1(f0, sp, 0x138);
                v0 = 0x870000;
                lw(a0, v0, 6576);  // 0x8719B0
                jal(ctx, 0x436D88u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x120);
                swc1(f1, sp, 0x124);
                swc1(f0, sp, 0x128);
                lwc1(f1, sp, 0x130);
                lwc1(f0, sp, 0x120);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x140);
                lwc1(f1, sp, 0x134);
                lwc1(f0, sp, 0x124);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x144);
                lwc1(f1, sp, 0x138);
                lwc1(f0, sp, 0x128);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x148);
                a0 = addiu(sp, 0x140);
                a1 = a0;
                jal(ctx, 0x436DE0u, gen::fn_sub_4C69F0_004c69f0);
                v0 = 0x43160000;
                mtc1(v0, f12);
                a0 = s0;
                jal(ctx, 0x436DF4u, gen::fn_sub_1C7130_001c7130);
                v1 = sltu(0, v0);
                if (v1 == 0) {
                    // 0x00436e08
                    charge(ctx, 14);
                    lw(v0, s1, kNpcOwnRes);
                    lw(a0, v0, 296);
                    jal(ctx, 0x436E10u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, s1, kNpcWalkPosX);
                    swc1(f1, s1, kNpcWalkPosY);
                    swc1(f0, s1, kNpcWalkPosZ);
                    v1 = 12;
                    sb(v1, s1, kNpcFollowState);
                }
            } else {
                // 0x00436b44
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00436c68
                    charge(ctx, 45);
                    lw(s0, s1, kNpcUnit);
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    jal(ctx, 0x436C74u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0x160);
                    swc1(f1, sp, 0x164);
                    swc1(f0, sp, 0x168);
                    v0 = 0x870000;
                    lw(a0, v0, 6576);  // 0x8719B0
                    jal(ctx, 0x436C9Cu, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0x150);
                    swc1(f1, sp, 0x154);
                    swc1(f0, sp, 0x158);
                    lwc1(f1, sp, 0x160);
                    lwc1(f0, sp, 0x150);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x170);
                    lwc1(f1, sp, 0x164);
                    lwc1(f0, sp, 0x154);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x174);
                    lwc1(f1, sp, 0x168);
                    lwc1(f0, sp, 0x158);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x178);
                    a0 = addiu(sp, 0x170);
                    a1 = a0;
                    jal(ctx, 0x436CF4u, gen::fn_sub_4C69F0_004c69f0);
                    v0 = 0x43160000;
                    mtc1(v0, f12);
                    a0 = s0;
                    jal(ctx, 0x436D08u, gen::fn_sub_1C7130_001c7130);
                    v1 = sltu(0, v0);
                    if (v1 == 0) {
                        // 0x00436d1c
                        charge(ctx, 14);
                        lw(v0, s1, kNpcOwnRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x436D24u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, s1, kNpcWalkPosX);
                        swc1(f1, s1, kNpcWalkPosY);
                        swc1(f0, s1, kNpcWalkPosZ);
                        v1 = 12;
                        sb(v1, s1, kNpcFollowState);
                    }
                } else {
                    // 0x00436b50
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00436b64
                        charge(ctx, 45);
                        lw(s0, s1, kNpcUnit);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x436B70u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x190);
                        swc1(f1, sp, 0x194);
                        swc1(f0, sp, 0x198);
                        v0 = 0x870000;
                        lw(a0, v0, 6576);  // 0x8719B0
                        jal(ctx, 0x436B98u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x180);
                        swc1(f1, sp, 0x184);
                        swc1(f0, sp, 0x188);
                        lwc1(f1, sp, 0x190);
                        lwc1(f0, sp, 0x180);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x1A0);
                        lwc1(f1, sp, 0x194);
                        lwc1(f0, sp, 0x184);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x1A4);
                        lwc1(f1, sp, 0x198);
                        lwc1(f0, sp, 0x188);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x1A8);
                        a0 = addiu(sp, 0x1A0);
                        a1 = a0;
                        jal(ctx, 0x436BF0u, gen::fn_sub_4C69F0_004c69f0);
                        v0 = 0x43160000;
                        mtc1(v0, f12);
                        a0 = s0;
                        jal(ctx, 0x436C04u, gen::fn_sub_1C7130_001c7130);
                        v0 = sltu(0, v0);
                        if (v0 != 0) {
                            // 0x00436c50
                            charge(ctx, 6);
                            lw(v0, s1, kNpcUnit);
                            lw(a0, v0, 368);
                            jal(ctx, 0x436C58u, gen::fn_sub_1B00C0_001b00c0);
                        } else {
                            // 0x00436c18
                            charge(ctx, 14);
                            lw(v0, s1, kNpcOwnRes);
                            lw(a0, v0, 296);
                            jal(ctx, 0x436C20u, gen::fn_sub_318B60_00318b60);
                            lwc1(f2, v0, 48);
                            lwc1(f1, v0, 52);
                            lwc1(f0, v0, 56);
                            swc1(f2, s1, kNpcWalkPosX);
                            swc1(f1, s1, kNpcWalkPosY);
                            swc1(f0, s1, kNpcWalkPosZ);
                            v1 = 12;
                            sb(v1, s1, kNpcFollowState);
                        }
                    } else {
                        // 0x00436b5c
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x436E40u:  // table[12]
            // 0x00436e40: state 12: keep the column place
            charge(ctx, 7);
            lw(a0, s1, kNpcPc);
            v1 = addiu(gp, -17929);  // &0x7CE6E7
            v1 = addu(v1, a0);
            lb(a0, v1, 0);
            v1 = 3;
            if (a0 == v1) {
                // 0x00437214
                charge(ctx, 6);
                a1 = 0;
                a2 = 0;
                a0 = addiu(gp, -17928);  // &0x7CE6E8
                v1 = 2;
                for (;;) {
                    // 0x00437248
                    charge(ctx, 3);
                    v0 = slti(a2, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0043722c
                    charge(ctx, 4);
                    v0 = addu(a0, a2);
                    lb(v0, v0, 0);
                    if (v0 == v1) {
                        // 0x0043723c
                        charge(ctx, 2);
                        a1 = dsll32(a2, 24);
                        a1 = dsra32(a1, 24);
                    }
                    // 0x00437244
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                }
                // 0x00437254
                charge(ctx, 24);
                v0 = dsll32(a1, 24);
                v0 = dsra32(v0, 24);
                v0 = addiu(v0, 1);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x437284u, gen::fn_sub_318B60_00318b60);
                v1 = 0x42FA0000;
                mtc1(v1, f12);
                v1 = 0x43480000;
                mtc1(v1, f13);
                a0 = s4;
                a1 = addiu(v0, 48);
                jal(ctx, 0x4372A4u, gen::fn_sub_434770_00434770);
                if (v0 != 0) {
                    // 0x004372b4
                    charge(ctx, 2);
                    v0 = 11;
                    sb(v0, s1, kNpcFollowState);
                }
                // 0x004372bc
                charge(ctx, 6);
                s2 = 0;
                a1 = 0;
                a0 = addiu(gp, -17928);  // &0x7CE6E8
                v1 = 2;
                for (;;) {
                    // 0x004372f0
                    charge(ctx, 3);
                    v0 = slti(a1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004372d4
                    charge(ctx, 4);
                    v0 = addu(a0, a1);
                    lb(v0, v0, 0);
                    if (v0 == v1) {
                        // 0x004372e4
                        charge(ctx, 2);
                        s2 = dsll32(a1, 24);
                        s2 = dsra32(s2, 24);
                    }
                    // 0x004372ec
                    charge(ctx, 1);
                    a1 = addiu(a1, 1);
                }
                // 0x004372fc
                charge(ctx, 61);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x43731Cu, gen::fn_sub_318B60_00318b60);
                s0 = addiu(v0, 48);
                v0 = dsll32(s2, 24);
                v0 = dsra32(v0, 24);
                v0 = addiu(v0, 1);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x437358u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0xB0);
                swc1(f1, sp, 0xB4);
                swc1(f0, sp, 0xB8);
                lwc1(f2, s0, 0);
                lwc1(f1, s0, 4);
                lwc1(f0, s0, 8);
                swc1(f2, sp, 0xA0);
                swc1(f1, sp, 0xA4);
                swc1(f0, sp, 0xA8);
                lwc1(f1, sp, 0xB0);
                lwc1(f0, sp, 0xA0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x90);
                lwc1(f1, sp, 0xB4);
                lwc1(f0, sp, 0xA4);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x94);
                lwc1(f1, sp, 0xB8);
                lwc1(f0, sp, 0xA8);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x98);
                a0 = addiu(sp, 0x90);
                a1 = a0;
                jal(ctx, 0x4373C8u, gen::fn_sub_4C69F0_004c69f0);
                sw(zero, sp, 0x94);
                v1 = 0x44480000;
                mtc1(v1, f1);
                c_lt_s(f0, f1);
                v1 = 1;
                if (cond(ctx)) {
                    // 0x004373f0
                    charge(ctx, 1);
                    v1 = 0;
                }
                // 0x004373f4
                charge(ctx, 3);
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    // 0x00437400
                    charge(ctx, 5);
                    jal(ctx, 0x437400u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x00437414
                        charge(ctx, 5);
                        jal(ctx, 0x437414u, gen::fn_sub_1A02C0_001a02c0);
                        v1 = 1;
                        if (v0 == v1) {
                            goto L_00437428;
                        }
                        // 0x00437438
                        charge(ctx, 4);
                        v1 = 13;
                        sb(v1, s1, kNpcFollowState);
                        break;
                    }
                L_00437428:
                    charge(ctx, 4);
                    v1 = 1;
                    sb(v1, s1, kNpcFollowState);
                }
            } else {
                // 0x00436e5c
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00436fe0
                    charge(ctx, 6);
                    a1 = 0;
                    a2 = 0;
                    a0 = addiu(gp, -17928);  // &0x7CE6E8
                    v1 = 1;
                    for (;;) {
                        // 0x00437014
                        charge(ctx, 3);
                        v0 = slti(a2, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00436ff8
                        charge(ctx, 4);
                        v0 = addu(a0, a2);
                        lb(v0, v0, 0);
                        if (v0 == v1) {
                            // 0x00437008
                            charge(ctx, 2);
                            a1 = dsll32(a2, 24);
                            a1 = dsra32(a1, 24);
                        }
                        // 0x00437010
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    }
                    // 0x00437020
                    charge(ctx, 24);
                    v0 = dsll32(a1, 24);
                    v0 = dsra32(v0, 24);
                    v0 = addiu(v0, 1);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6128);  // &0x8717F0
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    jal(ctx, 0x437050u, gen::fn_sub_318B60_00318b60);
                    v1 = 0x42FA0000;
                    mtc1(v1, f12);
                    v1 = 0x43480000;
                    mtc1(v1, f13);
                    a0 = s4;
                    a1 = addiu(v0, 48);
                    jal(ctx, 0x437070u, gen::fn_sub_434770_00434770);
                    if (v0 != 0) {
                        // 0x00437080
                        charge(ctx, 2);
                        v0 = 11;
                        sb(v0, s1, kNpcFollowState);
                    }
                    // 0x00437088
                    charge(ctx, 6);
                    s2 = 0;
                    a1 = 0;
                    a0 = addiu(gp, -17928);  // &0x7CE6E8
                    v1 = 1;
                    for (;;) {
                        // 0x004370bc
                        charge(ctx, 3);
                        v0 = slti(a1, 3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004370a0
                        charge(ctx, 4);
                        v0 = addu(a0, a1);
                        lb(v0, v0, 0);
                        if (v0 == v1) {
                            // 0x004370b0
                            charge(ctx, 2);
                            s2 = dsll32(a1, 24);
                            s2 = dsra32(s2, 24);
                        }
                        // 0x004370b8
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                    // 0x004370c8
                    charge(ctx, 61);
                    lw(v1, s1, kNpcPc);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6128);  // &0x8717F0
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    jal(ctx, 0x4370E8u, gen::fn_sub_318B60_00318b60);
                    s0 = addiu(v0, 48);
                    v0 = dsll32(s2, 24);
                    v0 = dsra32(v0, 24);
                    v0 = addiu(v0, 1);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6128);  // &0x8717F0
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    jal(ctx, 0x437124u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0xE0);
                    swc1(f1, sp, 0xE4);
                    swc1(f0, sp, 0xE8);
                    lwc1(f2, s0, 0);
                    lwc1(f1, s0, 4);
                    lwc1(f0, s0, 8);
                    swc1(f2, sp, 0xD0);
                    swc1(f1, sp, 0xD4);
                    swc1(f0, sp, 0xD8);
                    lwc1(f1, sp, 0xE0);
                    lwc1(f0, sp, 0xD0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xC0);
                    lwc1(f1, sp, 0xE4);
                    lwc1(f0, sp, 0xD4);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xC4);
                    lwc1(f1, sp, 0xE8);
                    lwc1(f0, sp, 0xD8);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xC8);
                    a0 = addiu(sp, 0xC0);
                    a1 = a0;
                    jal(ctx, 0x437194u, gen::fn_sub_4C69F0_004c69f0);
                    sw(zero, sp, 0xC4);
                    v1 = 0x44480000;
                    mtc1(v1, f1);
                    c_lt_s(f0, f1);
                    v1 = 1;
                    if (cond(ctx)) {
                        // 0x004371bc
                        charge(ctx, 1);
                        v1 = 0;
                    }
                    // 0x004371c0
                    charge(ctx, 3);
                    v1 = v1 ^ 0x1;
                    if (v1 == 0) {
                        // 0x004371cc
                        charge(ctx, 5);
                        jal(ctx, 0x4371CCu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x004371e0
                            charge(ctx, 5);
                            jal(ctx, 0x4371E0u, gen::fn_sub_1A02C0_001a02c0);
                            v1 = 1;
                            if (v0 == v1) {
                                goto L_004371f4;
                            }
                            // 0x00437204
                            charge(ctx, 4);
                            v1 = 13;
                            sb(v1, s1, kNpcFollowState);
                            break;
                        }
                    L_004371f4:
                        charge(ctx, 4);
                        v1 = 1;
                        sb(v1, s1, kNpcFollowState);
                    }
                } else {
                    // 0x00436e68
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00436e7c
                        charge(ctx, 14);
                        lw(v0, s1, kNpcHeroRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x436E84u, gen::fn_sub_318B60_00318b60);
                        v1 = 0x42FA0000;
                        mtc1(v1, f12);
                        v1 = 0x43480000;
                        mtc1(v1, f13);
                        a0 = s4;
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x436EA4u, gen::fn_sub_434770_00434770);
                        if (v0 != 0) {
                            // 0x00436eb4
                            charge(ctx, 2);
                            v0 = 11;
                            sb(v0, s1, kNpcFollowState);
                        }
                        // 0x00436ebc
                        charge(ctx, 51);
                        lw(v1, s1, kNpcPc);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6128);  // &0x8717F0
                        v0 = addu(v0, v1);
                        lw(a0, v0, 0);
                        jal(ctx, 0x436EDCu, gen::fn_sub_318B60_00318b60);
                        s0 = addiu(v0, 48);
                        lw(v0, s1, kNpcHeroRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x436EF0u, gen::fn_sub_318B60_00318b60);
                        lwc1(f2, v0, 48);
                        lwc1(f1, v0, 52);
                        lwc1(f0, v0, 56);
                        swc1(f2, sp, 0x110);
                        swc1(f1, sp, 0x114);
                        swc1(f0, sp, 0x118);
                        lwc1(f2, s0, 0);
                        lwc1(f1, s0, 4);
                        lwc1(f0, s0, 8);
                        swc1(f2, sp, 0x100);
                        swc1(f1, sp, 0x104);
                        swc1(f0, sp, 0x108);
                        lwc1(f1, sp, 0x110);
                        lwc1(f0, sp, 0x100);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xF0);
                        lwc1(f1, sp, 0x114);
                        lwc1(f0, sp, 0x104);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xF4);
                        lwc1(f1, sp, 0x118);
                        lwc1(f0, sp, 0x108);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0xF8);
                        a0 = addiu(sp, 0xF0);
                        a1 = a0;
                        jal(ctx, 0x436F60u, gen::fn_sub_4C69F0_004c69f0);
                        sw(zero, sp, 0xF4);
                        v1 = 0x44480000;
                        mtc1(v1, f1);
                        c_lt_s(f0, f1);
                        v1 = 1;
                        if (cond(ctx)) {
                            // 0x00436f88
                            charge(ctx, 1);
                            v1 = 0;
                        }
                        // 0x00436f8c
                        charge(ctx, 3);
                        v1 = v1 ^ 0x1;
                        if (v1 == 0) {
                            // 0x00436f98
                            charge(ctx, 5);
                            jal(ctx, 0x436F98u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x00436fac
                                charge(ctx, 5);
                                jal(ctx, 0x436FACu, gen::fn_sub_1A02C0_001a02c0);
                                v1 = 1;
                                if (v0 == v1) {
                                    goto L_00436fc0;
                                }
                                // 0x00436fd0
                                charge(ctx, 4);
                                v1 = 13;
                                sb(v1, s1, kNpcFollowState);
                                break;
                            }
                        L_00436fc0:
                            charge(ctx, 4);
                            v1 = 1;
                            sb(v1, s1, kNpcFollowState);
                        }
                    } else {
                        // 0x00436e74
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x437448u:  // table[1]
            // 0x00437448: state 1: plan a path to the hero
            charge(ctx, 54);
            lb(v0, s1, kNpcCellX);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            v0 = 0x44480000;
            mtc1(v0, f1);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x2A0);
            lb(v0, s1, kNpcCellZ);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            swc1(f0, sp, 0x2A8);
            sb(zero, s1, kNpcViaStairs);
            lw(v0, s1, kNpcUnit);
            lw(v0, v0, 84);
            lw(a0, v0, 480);
            jal(ctx, 0x437494u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            s3 = dsll32(v0, 24);
            s3 = dsra32(s3, 24);
            lw(v0, s1, kNpcUnit);
            lw(v0, v0, 84);
            lw(a0, v0, 480);
            jal(ctx, 0x4374B0u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
            s2 = dsll32(v0, 24);
            s2 = dsra32(s2, 24);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            lw(a0, v0, 480);
            jal(ctx, 0x4374CCu, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            s0 = dsll32(v0, 24);
            s0 = dsra32(s0, 24);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            lw(a0, v0, 480);
            jal(ctx, 0x4374E8u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
            t1 = dsll32(v0, 24);
            t1 = dsra32(t1, 24);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            a3 = addiu(sp, 0x2A0);
            t0 = s0;
            jal(ctx, 0x43750Cu, gen::fn_sub_4359F0_004359f0);
            v1 = 1;
            if (v0 != v1) {
                // 0x00437530
                charge(ctx, 23);
                a0 = addiu(sp, 0x290);
                a1 = 0;
                jal(ctx, 0x437538u, gen::fn_sub_437E80_00437e80);
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x43754Cu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s0 = sll(v0, 8);
                jal(ctx, 0x437558u, gen::fn_K_Field_Get_001b9120);
                s0 = addu(v0, s0);
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x437570u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                v0 = sll(v0, 4);
                v0 = addu(s0, v0);
                lbu(v0, v0, 83);
                if (v0 != 0) {
                    // 0x004375cc
                    charge(ctx, 14);
                    lw(v0, s1, kNpcUnit);
                    lw(v0, v0, 84);
                    lw(a0, v0, 480);
                    jal(ctx, 0x4375D8u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    lw(v0, s1, kNpcUnit);
                    lw(v0, v0, 84);
                    lw(a0, v0, 480);
                    jal(ctx, 0x4375F4u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    s3 = dsll32(v0, 24);
                    s3 = dsra32(s3, 24);
                } else {
                    // 0x0043758c
                    charge(ctx, 16);
                    lb(a1, s1, kNpcPc);
                    a0 = addiu(sp, 0x280);
                    jal(ctx, 0x437594u, gen::fn_sub_437E80_00437e80);
                    a0 = addiu(sp, 0x280);
                    jal(ctx, 0x4375A0u, gen::fn_sub_44F120_0044f120);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    a0 = addiu(sp, 0x280);
                    jal(ctx, 0x4375B4u, gen::fn_sub_44F170_0044f170);
                    s3 = dsll32(v0, 24);
                    s3 = dsra32(s3, 24);
                }
                // 0x00437604
                charge(ctx, 20);
                a0 = addiu(sp, 0x290);
                jal(ctx, 0x437608u, gen::fn_sub_44F120_0044f120);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
                a0 = addiu(sp, 0x290);
                jal(ctx, 0x43761Cu, gen::fn_sub_44F170_0044f170);
                t1 = dsll32(v0, 24);
                t1 = dsra32(t1, 24);
                a0 = s4;
                a1 = s0;
                a2 = s3;
                a3 = addiu(sp, 0x2A0);
                t0 = s2;
                jal(ctx, 0x437640u, gen::fn_sub_4359F0_004359f0);
                a0 = 1;
                if (v0 != a0) {
                    // 0x00437668
                    charge(ctx, 4);
                    v1 = 5;
                    sb(v1, s1, kNpcFollowState);
                } else {
                    // 0x00437654
                    charge(ctx, 5);
                    v1 = 3;
                    sb(v1, s1, kNpcFollowState);
                    sb(a0, s1, kNpcViaStairs);
                }
            } else {
                // 0x00437520
                charge(ctx, 4);
                v1 = 3;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437678u:  // table[3]
            // 0x00437678: state 3: the next step of the path
            charge(ctx, 3);
            lw(v1, s1, kNpcCount);
            if (v1 == 0) {
                // 0x00437734
                charge(ctx, 4);
                v1 = 5;
                sb(v1, s1, kNpcFollowState);
            } else {
                // 0x00437684
                charge(ctx, 44);
                v0 = addiu(v1, -1);
                sw(v0, s1, kNpcCount);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lh(v0, v0, 3600);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                v0 = 0x44480000;
                mtc1(v0, f1);
                mul_s(f0, f1, f0);
                swc1(f0, s1, kNpcStepPosX);
                lw(v0, s1, kNpcCount);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lh(v0, v0, 3602);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, s1, kNpcStepPosZ);
                a0 = addiu(s1, kNpcStepPosX);
                jal(ctx, 0x4376E0u, gen::fn_sub_44F120_0044f120);
                s0 = v0 & 0xFFFF;
                a0 = addiu(s1, kNpcStepPosX);
                jal(ctx, 0x4376F0u, gen::fn_sub_44F170_0044f170);
                a2 = v0 & 0xFFFF;
                a0 = addiu(sp, 0x240);
                a1 = s0;
                jal(ctx, 0x437704u, gen::fn_sub_1BF220_001bf220);
                lwc1(f2, sp, 0x240);
                lwc1(f1, sp, 0x244);
                lwc1(f0, sp, 0x248);
                swc1(f2, s1, kNpcStepPosX);
                swc1(f1, s1, kNpcStepPosY);
                swc1(f0, s1, kNpcStepPosZ);
                v1 = 4;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437744u:  // table[4]
            // 0x00437744: state 4: walking a step
            charge(ctx, 8);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = addiu(s1, kNpcStepPosX);
            lwc1(f12, gp, -32072);  // 0x7CAFA8
            jal(ctx, 0x437754u, gen::fn_sub_1AFA20_001afa20);
            if (v0 != 0) {
                // 0x004377d8
                charge(ctx, 17);
                lwc1(f2, s1, kNpcStepPosX);
                lwc1(f1, s1, kNpcStepPosY);
                lwc1(f0, s1, kNpcStepPosZ);
                swc1(f2, s1, kNpcWalkPosX);
                swc1(f1, s1, kNpcWalkPosY);
                swc1(f0, s1, kNpcWalkPosZ);
                lwc1(f2, s1, kNpcStepPosX);
                lwc1(f1, s1, kNpcStepPosY);
                lwc1(f0, s1, kNpcStepPosZ);
                swc1(f2, s1, kNpcCellPosX);
                swc1(f1, s1, kNpcCellPosY);
                swc1(f0, s1, kNpcCellPosZ);
                v1 = 3;
                sb(v1, s1, kNpcFollowState);
                sw(zero, s1, kNpcTimer);
            } else {
                // 0x00437764
                charge(ctx, 13);
                v0 = 0x870000;
                lw(v0, v0, 6132);  // 0x8717F4
                lw(a0, v0, 480);
                jal(ctx, 0x437770u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s0 = v0;
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x437788u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                if (s0 == v0) {
                    // 0x00437798
                    charge(ctx, 13);
                    v0 = 0x870000;
                    lw(v0, v0, 6132);  // 0x8717F4
                    lw(a0, v0, 480);
                    jal(ctx, 0x4377A4u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    s0 = v0;
                    lw(v0, s1, kNpcUnit);
                    lw(v0, v0, 84);
                    lw(a0, v0, 480);
                    jal(ctx, 0x4377BCu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                    if (s0 == v0) {
                        // 0x004377cc
                        charge(ctx, 3);
                        sb(zero, s1, kNpcFollowState);
                    }
                }
            }
            break;
        case 0x43781Cu:  // table[5]
            // 0x0043781c: state 5: the last stretch to the hero
            charge(ctx, 13);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            lw(a0, v0, 480);
            jal(ctx, 0x437828u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            s0 = v0;
            lw(v0, s1, kNpcUnit);
            lw(v0, v0, 84);
            lw(a0, v0, 480);
            jal(ctx, 0x437840u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            if (s0 == v0) {
                // 0x00437850
                charge(ctx, 13);
                v0 = 0x870000;
                lw(v0, v0, 6132);  // 0x8717F4
                lw(a0, v0, 480);
                jal(ctx, 0x43785Cu, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s0 = v0;
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x437874u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                if (s0 != v0) {
                    goto L_00437890;
                }
                // 0x00437884
                charge(ctx, 3);
                sb(zero, s1, kNpcFollowState);
            L_00437940:
                charge(ctx, 6);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x437948u, gen::fn_sub_1B0220_001b0220);
                if (v0 == 0) {
                    // 0x00437958
                    charge(ctx, 4);
                    v1 = 1;
                    sb(v1, s1, kNpcFollowState);
                }
                break;
            }
        L_00437890:
            charge(ctx, 8);
            lbu(s0, s1, kNpcGoalZ);
            lw(v0, s1, kNpcUnit);
            lw(v0, v0, 84);
            lw(a0, v0, 480);
            jal(ctx, 0x4378A0u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
            if (s0 != v0) {
                goto L_00437940;
            }
            // 0x004378b0
            charge(ctx, 8);
            lbu(s0, s1, kNpcGoalX);
            lw(v0, s1, kNpcUnit);
            lw(v0, v0, 84);
            lw(a0, v0, 480);
            jal(ctx, 0x4378C0u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            if (s0 != v0) {
                goto L_00437940;
            }
            // 0x004378d0
            charge(ctx, 3);
            lb(v0, s1, kNpcViaStairs);
            if (v0 == 0) {
                // 0x004378dc
                charge(ctx, 4);
                v0 = 1;
                sb(v0, s1, kNpcFollowState);
                goto L_00437940;
            }
            // 0x004378ec
            charge(ctx, 17);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = 0;
            jal(ctx, 0x4378F8u, gen::fn_sub_1B0240_001b0240);
            lw(v0, s1, kNpcHeroRes);
            lw(a0, v0, 296);
            jal(ctx, 0x437908u, gen::fn_sub_318B60_00318b60);
            lw(v1, s1, kNpcUnit);
            lw(a0, v1, 368);
            a1 = addiu(v0, 48);
            lwc1(f12, gp, -32072);  // 0x7CAFA8
            jal(ctx, 0x437920u, gen::fn_sub_1AFA20_001afa20);
            if (v0 != 0) {
                // 0x00437930
                charge(ctx, 4);
                v1 = 6;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437968u:  // table[6]
            // 0x00437968: state 6: wait for the mover
            charge(ctx, 6);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            jal(ctx, 0x437970u, gen::fn_sub_1B0220_001b0220);
            if (v0 == 0) {
                // 0x00437980
                charge(ctx, 4);
                v1 = 1;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437990u:  // table[13]
            // 0x00437990: state 13: off random floors: the nearest cover point
            charge(ctx, 12);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            jal(ctx, 0x437998u, gen::fn_sub_1B00C0_001b00c0);
            a0 = 18;
            jal(ctx, 0x4379A4u, gen::fn_sub_3B5D50_003b5d50);
            s0 = v0;
            v0 = 0x45FA0000;
            mtc1(v0, f20);
            for (;;) {
                // 0x00437aa4
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004379c0
                charge(ctx, 49);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                v0 = addu(v0, v1);
                lw(a0, v0, 80);
                jal(ctx, 0x4379E0u, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 48);
                lwc1(f0, s0, 256);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x270);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                v0 = addu(v0, v1);
                lw(a0, v0, 80);
                jal(ctx, 0x437A18u, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 52);
                lwc1(f0, s0, 260);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x274);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                v0 = addu(v0, v1);
                lw(a0, v0, 80);
                jal(ctx, 0x437A50u, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 56);
                lwc1(f0, s0, 264);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x278);
                a0 = addiu(sp, 0x270);
                a1 = a0;
                jal(ctx, 0x437A70u, gen::fn_sub_4C69F0_004c69f0);
                c_lt_s(f0, f20);
                if (cond(ctx)) {
                    // 0x00437a84
                    charge(ctx, 7);
                    mov_s(f20, f0);
                    lwc1(f2, s0, 256);
                    lwc1(f1, s0, 260);
                    lwc1(f0, s0, 264);
                    swc1(f2, s1, kNpcHidePosX);
                    swc1(f1, s1, kNpcHidePosY);
                    swc1(f0, s1, kNpcHidePosZ);
                }
                // 0x00437aa0
                charge(ctx, 1);
                lw(s0, s0, 248);
            }
            // 0x00437aac
            charge(ctx, 8);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = addiu(s1, kNpcHidePosX);
            lwc1(f12, gp, -32072);  // 0x7CAFA8
            jal(ctx, 0x437ABCu, gen::fn_sub_1AFA20_001afa20);
            if (v0 != 0) {
                // 0x00437acc
                charge(ctx, 4);
                v1 = 14;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437ADCu:  // table[14]
            // 0x00437adc: state 14: move between cover points
            charge(ctx, 39);
            a0 = 18;
            jal(ctx, 0x437AE0u, gen::fn_sub_3B5D50_003b5d50);
            s3 = v0;
            v0 = 0x45FA0000;
            mtc1(v0, f21);
            s2 = 0;
            s0 = 0;
            lw(v0, s1, kNpcHeroRes);
            lw(a0, v0, 296);
            jal(ctx, 0x437B04u, gen::fn_sub_318B60_00318b60);
            lwc1(f1, v0, 48);
            lwc1(f0, s1, kNpcHidePosX);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x260);
            lw(v0, s1, kNpcHeroRes);
            lw(a0, v0, 296);
            jal(ctx, 0x437B24u, gen::fn_sub_318B60_00318b60);
            lwc1(f1, v0, 52);
            lwc1(f0, s1, kNpcHidePosY);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x264);
            lw(v0, s1, kNpcHeroRes);
            lw(a0, v0, 296);
            jal(ctx, 0x437B44u, gen::fn_sub_318B60_00318b60);
            lwc1(f1, v0, 56);
            lwc1(f0, s1, kNpcHidePosZ);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x268);
            a0 = addiu(sp, 0x260);
            a1 = a0;
            jal(ctx, 0x437B64u, gen::fn_sub_4C69F0_004c69f0);
            mov_s(f20, f0);
            for (;;) {
                // 0x00437cac
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00437b78
                charge(ctx, 5);
                lwc1(f1, s1, kNpcHidePosX);
                lwc1(f0, s3, 256);
                c_eq_s(f0, f1);
                if (!cond(ctx)) {
                    // 0x00437b8c
                    charge(ctx, 5);
                    lwc1(f3, s3, 264);
                    lwc1(f2, s1, kNpcHidePosZ);
                    c_eq_s(f3, f2);
                    if (!cond(ctx)) {
                        // 0x00437ba0
                        charge(ctx, 44);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x260);
                        lwc1(f1, s3, 260);
                        lwc1(f0, s1, kNpcHidePosY);
                        sub_s(f0, f1, f0);
                        swc1(f0, sp, 0x264);
                        sub_s(f0, f3, f2);
                        swc1(f0, sp, 0x268);
                        a0 = addiu(sp, 0x260);
                        a1 = a0;
                        jal(ctx, 0x437BC8u, gen::fn_sub_4C69F0_004c69f0);
                        mov_s(f22, f0);
                        lw(v0, s1, kNpcHeroRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x437BDCu, gen::fn_sub_318B60_00318b60);
                        lwc1(f1, v0, 48);
                        lwc1(f0, s3, 256);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x260);
                        lw(v0, s1, kNpcHeroRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x437BFCu, gen::fn_sub_318B60_00318b60);
                        lwc1(f1, v0, 52);
                        lwc1(f0, s3, 260);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x264);
                        lw(v0, s1, kNpcHeroRes);
                        lw(a0, v0, 296);
                        jal(ctx, 0x437C1Cu, gen::fn_sub_318B60_00318b60);
                        lwc1(f1, v0, 56);
                        lwc1(f0, s3, 264);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x268);
                        a0 = addiu(sp, 0x260);
                        a1 = a0;
                        jal(ctx, 0x437C3Cu, gen::fn_sub_4C69F0_004c69f0);
                        c_lt_s(f0, f20);
                        if (cond(ctx)) {
                            // 0x00437c50
                            charge(ctx, 4);
                            add_s(f3, f22, f0);
                            c_lt_s(f3, f21);
                            if (cond(ctx)) {
                                // 0x00437c60
                                charge(ctx, 15);
                                lwc1(f2, s3, 256);
                                lwc1(f1, s3, 260);
                                lwc1(f0, s3, 264);
                                swc1(f2, sp, 0x250);
                                swc1(f1, sp, 0x254);
                                swc1(f0, sp, 0x258);
                                mov_s(f21, f3);
                                lwc1(f2, s3, 256);
                                lwc1(f1, s3, 260);
                                lwc1(f0, s3, 264);
                                swc1(f2, s1, kNpcHidePosX);
                                swc1(f1, s1, kNpcHidePosY);
                                swc1(f0, s1, kNpcHidePosZ);
                                sb(s2, s1, kNpcHideIndex);
                                s0 = 1;
                            }
                        }
                    }
                }
                // 0x00437c9c
                charge(ctx, 4);
                lw(s3, s3, 248);
                v0 = addiu(s2, 1);
                s2 = dsll32(v0, 24);
                s2 = dsra32(s2, 24);
            }
            // 0x00437cb4
            charge(ctx, 8);
            v0 = 0x43FA0000;
            mtc1(v0, f12);
            lw(a0, s1, kNpcUnit);
            jal(ctx, 0x437CC0u, gen::fn_sub_1C7130_001c7130);
            v1 = 1;
            if (v0 != v1) {
                // 0x00437ce4
                charge(ctx, 6);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x437CECu, gen::fn_sub_1B0220_001b0220);
                if (v0 != 0) {
                    // 0x00437d3c
                    charge(ctx, 4);
                    v1 = dsll32(s0, 24);
                    v1 = dsra32(v1, 24);
                    if (v1 != 0) {
                        // 0x00437d4c
                        charge(ctx, 8);
                        lw(v0, s1, kNpcUnit);
                        lw(a0, v0, 368);
                        a1 = addiu(sp, 0x250);
                        lwc1(f12, gp, -32072);  // 0x7CAFA8
                        jal(ctx, 0x437D5Cu, gen::fn_sub_1AFA20_001afa20);
                    }
                } else {
                    // 0x00437cfc
                    charge(ctx, 12);
                    lw(v0, s1, kNpcHeroRes);
                    lw(a0, v0, 296);
                    jal(ctx, 0x437D04u, gen::fn_sub_318B60_00318b60);
                    lw(v1, s1, kNpcUnit);
                    lw(a0, v1, 368);
                    a1 = addiu(v0, 48);
                    lwc1(f12, gp, -32072);  // 0x7CAFA8
                    jal(ctx, 0x437D1Cu, gen::fn_sub_1AFA20_001afa20);
                    if (v0 != 0) {
                        // 0x00437d2c
                        charge(ctx, 4);
                        v1 = 15;
                        sb(v1, s1, kNpcFollowState);
                    }
                }
            } else {
                // 0x00437cd4
                charge(ctx, 4);
                v1 = 10;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437D6Cu:  // table[15]
            // 0x00437d6c: state 15: wait for the mover
            charge(ctx, 8);
            v0 = 0x43FA0000;
            mtc1(v0, f12);
            lw(a0, s1, kNpcUnit);
            jal(ctx, 0x437D78u, gen::fn_sub_1C7130_001c7130);
            v1 = 1;
            if (v0 != v1) {
                // 0x00437d9c
                charge(ctx, 6);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x437DA4u, gen::fn_sub_1B0220_001b0220);
                if (v0 == 0) {
                    // 0x00437db4
                    charge(ctx, 2);
                    v1 = 14;
                    sb(v1, s1, kNpcFollowState);
                }
            } else {
                // 0x00437d8c
                charge(ctx, 4);
                v1 = 10;
                sb(v1, s1, kNpcFollowState);
            }
            break;
        case 0x437DBCu:  // table[2]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00437dbc (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x2B0);
    return;
L_00435dc0_14:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_00435de4;
L_00435eb0_27:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00435ed4;
L_00435fa4_40:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00435fc8;
L_0043609c_53:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_004360c0;
L_0043619c_66:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_004361c0;
L_0043629c_79:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_004362c0;
L_0043639c_92:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_004363c0;
}

// 0x00437E00 sub_437E00 -- 32 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_SetMode0] A thunk: sub_456410($a0) (tartarus.h: mode +4704 = 0, kNpcModeChange = 1).
void sub_437E00(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00437e00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x437E08u, gen::fn_sub_456410_00456410);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00437E20 sub_437E20 -- 92 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsOutOfColumn] 1 when kNpcFollowState of member $a0 is below 7 or 13 and above, else 0. (Shadow sight
// checks.)
void sub_437E20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00437e20
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6412);  // &0x87190C
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    lw(v0, v0, 60);
    lb(v1, v0, kNpcFollowState);
    v0 = slti(v1, 7);
    if (v0 == 0) {
        // 0x00437e58
        charge(ctx, 3);
        at = slti(v1, 13);
        if (at == 0) {
            goto L_00437e70;
        }
        // 0x00437e64
        charge(ctx, 3);
        v0 = 0;
        // 0x00437e74 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00437e70:
    charge(ctx, 1);
    v0 = 1;
    // 0x00437e74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00437E80 sub_437E80 -- 400 bytes; frame 0xA0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_NearestKind8Cell] ($a0 out f32[3], $a1 pc) over the 16 x 16 grid the cells of kind 8 (cell +2), the door
// point of each (sub_1BF220) and the nearest to the member's model (start 8000.0); out = its point (0 when none).
void sub_437E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    // 0x00437e80
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    v1 = 0x45FA0000;
    mtc1(v1, f20);
    sw(zero, sp, 0x78);
    sw(zero, sp, 0x74);
    sw(zero, sp, 0x70);
    s3 = 0;
    a0 = dsll32(a1, 24);
    a0 = dsra32(a0, 24);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 6048);  // &gFldUnitsPc
    s1 = addu(v1, a0);
    for (;;) {
        // 0x00437fc4
        charge(ctx, 3);
        v1 = slti(s3, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00437ee4
        charge(ctx, 4);
        s2 = 0;
        s0 = sll(s3, 4);
        for (;;) {
            // 0x00437fb4
            charge(ctx, 3);
            v1 = slti(s2, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00437ef4
            charge(ctx, 9);
            jal(ctx, 0x437EF4u, gen::fn_K_Field_Get_001b9120);
            a0 = addu(s0, v0);
            v1 = sll(s2, 8);
            v1 = addu(a0, v1);
            lbu(a0, v1, 74);
            v1 = 8;
            if (a0 == v1) {
                // 0x00437f18
                charge(ctx, 33);
                a1 = s3 & 0xFFFF;
                a2 = s2 & 0xFFFF;
                a0 = addiu(sp, 0x90);
                jal(ctx, 0x437F24u, gen::fn_sub_1BF220_001bf220);
                lw(a0, s1, 80);
                jal(ctx, 0x437F30u, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 48);
                lwc1(f0, sp, 0x90);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x80);
                lw(a0, s1, 80);
                jal(ctx, 0x437F4Cu, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 52);
                lwc1(f0, sp, 0x94);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x84);
                lw(a0, s1, 80);
                jal(ctx, 0x437F68u, gen::fn_sub_318B60_00318b60);
                lwc1(f1, v0, 56);
                lwc1(f0, sp, 0x98);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x88);
                a0 = addiu(sp, 0x80);
                a1 = a0;
                jal(ctx, 0x437F88u, gen::fn_sub_4C69F0_004c69f0);
                c_lt_s(f0, f20);
                if (cond(ctx)) {
                    // 0x00437f9c
                    charge(ctx, 5);
                    mov_s(f20, f0);
                    ld(v1, sp, 0x90);
                    lwc1(f0, sp, 0x98);
                    sd(v1, sp, 0x70);
                    swc1(f0, sp, 0x78);
                }
            }
            // 0x00437fb0
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x00437fc0
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00437fd0
    charge(ctx, 16);
    lwc1(f2, sp, 0x70);
    lwc1(f1, sp, 0x74);
    lwc1(f0, sp, 0x78);
    swc1(f2, s4, 0);
    swc1(f1, s4, 4);
    swc1(f0, s4, 8);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00438010 sub_438010 -- 5092 bytes; frame 0x100: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateExplore] Think mode 2 ($a0 task): a shadow touching the member (sub_439F60) -> mode 5; a chest in
// reach (sub_439400) -> state 6; the self / support skills as in follow mode. Then kNpcExploreState (jump table
// 0x7BC3D0): 0 start on the current cell (rule by slot), 1 choose the next direction (the wall-following rule
// sub_431AA0 .. sub_432BB0, or an unvisited side, sub_433160, which flips the rule; nothing open -> walk to the
// nearest kind-8 cell, state 5), 2 / 3 walk to the next cell (an occasional 60-frame pause, 10 % by RpRandom), count
// the visit (sub_431880 -> 4: turn to the least visited side), 6 / 7 walk to the chest, open it ("treasure free
// proc"), give its item to the member's list (the 0x7CE6CC + 4 (pc - 1) flags) and leave, 8 wait for the chest task,
// then back to follow / explore by the tactic.
void sub_438010(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00438010
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(s1, a0, 60);
    lw(s6, gp, -19040);  // 0x7CE290
    lb(a1, s1, kNpcPc);
    jal(ctx, 0x43804Cu, gen::fn_sub_439F60_00439f60);
    v1 = 1;
    if (v0 != v1) {
        // 0x00438078
        charge(ctx, 15);
        lb(a0, s1, kNpcPc);
        jal(ctx, 0x43807Cu, gen::fn_sub_439400_00439400);
        lw(v1, s1, kNpcPc);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6472);  // &0x871948
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        jal(ctx, 0x4380A4u, gen::fn_sub_16C970_0016c970);
        if (v0 != 0) {
            // 0x004380b4
            charge(ctx, 4);
            lb(a1, s1, kNpcPc);
            a0 = s4;
            jal(ctx, 0x4380BCu, gen::fn_sub_456670_00456670);
        }
        // 0x004380c4
        charge(ctx, 10);
        lb(s0, s1, kNpcPc);
        s3 = 1;
        v1 = sll(s0, 3);
        v1 = subu(v1, s0);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, 6048);  // &gFldUnitsPc
        s5 = addu(v1, a0);
        for (;;) {
            // 0x00438194
            charge(ctx, 3);
            v1 = slti(s3, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x004380ec
            charge(ctx, 2);
            if (s3 != s0) {
                // 0x004380f4
                charge(ctx, 10);
                a1 = 0;
                v1 = sll(s3, 3);
                v1 = subu(v1, s3);
                a0 = sll(v1, 6);
                v1 = 0x870000;
                v1 = addiu(v1, 6048);  // &gFldUnitsPc
                s2 = addu(v1, a0);
                lw(v1, s2, 72);
                if (v1 != 0) {
                    // 0x0043811c
                    charge(ctx, 3);
                    lw(v1, s2, 84);
                    if (v1 != 0) {
                        // 0x00438128
                        charge(ctx, 1);
                        a1 = 1;
                    }
                }
                // 0x0043812c
                charge(ctx, 4);
                a0 = sltu(0, a1);
                v1 = 1;
                if (a0 != v1) {
                    goto L_00438190;
                }
                // 0x0043813c
                charge(ctx, 8);
                a0 = s2;
                jal(ctx, 0x438140u, gen::fn_sub_4353F0_004353f0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = 6;
                if (a0 != v1) {
                    goto L_00438190;
                }
                // 0x0043815c
                charge(ctx, 9);
                v0 = 0x43FA0000;
                mtc1(v0, f12);
                a0 = s5;
                a1 = s2;
                jal(ctx, 0x43816Cu, gen::fn_sub_1C7160_001c7160);
                v1 = 1;
                if (v0 != v1) {
                    goto L_00438190;
                }
                goto L_00438180_12;
            }
        L_00438190:
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x004381a0
        charge(ctx, 1);
        v1 = 0;
    L_004381a4:
        charge(ctx, 4);
        v1 = dsll32(v1, 24);
        v1 = dsra32(v1, 24);
        if (v1 != 0) {
            // 0x004381b4
            charge(ctx, 10);
            lb(s0, s1, kNpcPc);
            s3 = 1;
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            s5 = addu(v0, v1);
            for (;;) {
                // 0x00438284
                charge(ctx, 3);
                v0 = slti(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004381dc
                charge(ctx, 2);
                if (s3 != s0) {
                    // 0x004381e4
                    charge(ctx, 10);
                    a0 = 0;
                    v0 = sll(s3, 3);
                    v0 = subu(v0, s3);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s2 = addu(v0, v1);
                    lw(v0, s2, 72);
                    if (v0 != 0) {
                        // 0x0043820c
                        charge(ctx, 3);
                        lw(v0, s2, 84);
                        if (v0 != 0) {
                            // 0x00438218
                            charge(ctx, 1);
                            a0 = 1;
                        }
                    }
                    // 0x0043821c
                    charge(ctx, 4);
                    v1 = sltu(0, a0);
                    v0 = 1;
                    if (v1 != v0) {
                        goto L_00438280;
                    }
                    // 0x0043822c
                    charge(ctx, 8);
                    a0 = s2;
                    jal(ctx, 0x438230u, gen::fn_sub_4353F0_004353f0);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = 6;
                    if (v1 != v0) {
                        goto L_00438280;
                    }
                    // 0x0043824c
                    charge(ctx, 9);
                    v0 = 0x43FA0000;
                    mtc1(v0, f12);
                    a0 = s5;
                    a1 = s2;
                    jal(ctx, 0x43825Cu, gen::fn_sub_1C7160_001c7160);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_00438280;
                    }
                    goto L_00438270_25;
                }
            L_00438280:
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x00438290
            charge(ctx, 1);
            a0 = 0;
        L_00438294:
            charge(ctx, 5);
            jal(ctx, 0x438294u, gen::fn_sub_43C910_0043c910);
            v1 = v0 & 0xFFFF;
            if (v1 == 0) {
                // 0x004382a8
                charge(ctx, 10);
                lb(s0, s1, kNpcPc);
                s3 = 1;
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                s5 = addu(v0, v1);
                for (;;) {
                    // 0x00438378
                    charge(ctx, 3);
                    v0 = slti(s3, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004382d0
                    charge(ctx, 2);
                    if (s3 != s0) {
                        // 0x004382d8
                        charge(ctx, 10);
                        a0 = 0;
                        v0 = sll(s3, 3);
                        v0 = subu(v0, s3);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6048);  // &gFldUnitsPc
                        s2 = addu(v0, v1);
                        lw(v0, s2, 72);
                        if (v0 != 0) {
                            // 0x00438300
                            charge(ctx, 3);
                            lw(v0, s2, 84);
                            if (v0 != 0) {
                                // 0x0043830c
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00438310
                        charge(ctx, 4);
                        v1 = sltu(0, a0);
                        v0 = 1;
                        if (v1 != v0) {
                            goto L_00438374;
                        }
                        // 0x00438320
                        charge(ctx, 8);
                        a0 = s2;
                        jal(ctx, 0x438324u, gen::fn_sub_4353F0_004353f0);
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        v0 = 6;
                        if (v1 != v0) {
                            goto L_00438374;
                        }
                        // 0x00438340
                        charge(ctx, 9);
                        v0 = 0x43FA0000;
                        mtc1(v0, f12);
                        a0 = s5;
                        a1 = s2;
                        jal(ctx, 0x438350u, gen::fn_sub_1C7160_001c7160);
                        v1 = 1;
                        if (v0 != v1) {
                            goto L_00438374;
                        }
                        goto L_00438364_38;
                    }
                L_00438374:
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x00438384
                charge(ctx, 1);
                a0 = 0;
            L_00438388:
                charge(ctx, 6);
                jal(ctx, 0x438388u, gen::fn_sub_43C180_0043c180);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (v0 != 0) {
                    // 0x004385a0
                    charge(ctx, 10);
                    lb(s0, s1, kNpcPc);
                    s3 = 1;
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s5 = addu(v0, v1);
                    for (;;) {
                        // 0x00438670
                        charge(ctx, 3);
                        v0 = slti(s3, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004385c8
                        charge(ctx, 2);
                        if (s3 != s0) {
                            // 0x004385d0
                            charge(ctx, 10);
                            a0 = 0;
                            v0 = sll(s3, 3);
                            v0 = subu(v0, s3);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6048);  // &gFldUnitsPc
                            s2 = addu(v0, v1);
                            lw(v0, s2, 72);
                            if (v0 != 0) {
                                // 0x004385f8
                                charge(ctx, 3);
                                lw(v0, s2, 84);
                                if (v0 != 0) {
                                    // 0x00438604
                                    charge(ctx, 1);
                                    a0 = 1;
                                }
                            }
                            // 0x00438608
                            charge(ctx, 4);
                            v1 = sltu(0, a0);
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_0043866c;
                            }
                            // 0x00438618
                            charge(ctx, 8);
                            a0 = s2;
                            jal(ctx, 0x43861Cu, gen::fn_sub_4353F0_004353f0);
                            v1 = dsll32(v0, 24);
                            v1 = dsra32(v1, 24);
                            v0 = 6;
                            if (v1 != v0) {
                                goto L_0043866c;
                            }
                            // 0x00438638
                            charge(ctx, 9);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s5;
                            a1 = s2;
                            jal(ctx, 0x438648u, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_0043866c;
                            }
                            goto L_0043865c_77;
                        }
                    L_0043866c:
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                    // 0x0043867c
                    charge(ctx, 1);
                    a0 = 0;
                L_00438680:
                    charge(ctx, 7);
                    lw(s0, s1, kNpcPc);
                    jal(ctx, 0x438684u, gen::fn_sub_43C180_0043c180);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    if (s0 == v1) {
                        // 0x0043869c
                        charge(ctx, 11);
                        s0 = dsll32(s0, 24);
                        s0 = dsra32(s0, 24);
                        s3 = 1;
                        v1 = sll(s0, 3);
                        v1 = subu(v1, s0);
                        a0 = sll(v1, 6);
                        v1 = 0x870000;
                        v1 = addiu(v1, 6048);  // &gFldUnitsPc
                        s5 = addu(v1, a0);
                        for (;;) {
                            // 0x00438770
                            charge(ctx, 3);
                            v1 = slti(s3, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x004386c8
                            charge(ctx, 2);
                            if (s3 != s0) {
                                // 0x004386d0
                                charge(ctx, 10);
                                a1 = 0;
                                v1 = sll(s3, 3);
                                v1 = subu(v1, s3);
                                a0 = sll(v1, 6);
                                v1 = 0x870000;
                                v1 = addiu(v1, 6048);  // &gFldUnitsPc
                                s2 = addu(v1, a0);
                                lw(v1, s2, 72);
                                if (v1 != 0) {
                                    // 0x004386f8
                                    charge(ctx, 3);
                                    lw(v1, s2, 84);
                                    if (v1 != 0) {
                                        // 0x00438704
                                        charge(ctx, 1);
                                        a1 = 1;
                                    }
                                }
                                // 0x00438708
                                charge(ctx, 4);
                                a0 = sltu(0, a1);
                                v1 = 1;
                                if (a0 != v1) {
                                    goto L_0043876c;
                                }
                                // 0x00438718
                                charge(ctx, 8);
                                a0 = s2;
                                jal(ctx, 0x43871Cu, gen::fn_sub_4353F0_004353f0);
                                a0 = dsll32(v0, 24);
                                a0 = dsra32(a0, 24);
                                v1 = 6;
                                if (a0 != v1) {
                                    goto L_0043876c;
                                }
                                // 0x00438738
                                charge(ctx, 9);
                                v0 = 0x43FA0000;
                                mtc1(v0, f12);
                                a0 = s5;
                                a1 = s2;
                                jal(ctx, 0x438748u, gen::fn_sub_1C7160_001c7160);
                                v1 = 1;
                                if (v0 != v1) {
                                    goto L_0043876c;
                                }
                                goto L_0043875c_90;
                            }
                        L_0043876c:
                            charge(ctx, 1);
                            s3 = addiu(s3, 1);
                        }
                        // 0x0043877c
                        charge(ctx, 1);
                        v1 = 0;
                    L_00438780:
                        charge(ctx, 6);
                        v1 = dsll32(v1, 24);
                        v1 = dsra32(v1, 24);
                        sh(v1, s1, kNpcSkillTarget);
                        v1 = 1;
                        sb(v1, s1, kNpcSupport);
                        sb(zero, s1, kNpcSupportState);
                    }
                } else {
                    // 0x004383a0
                    charge(ctx, 10);
                    lb(s0, s1, kNpcPc);
                    s3 = 1;
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s5 = addu(v0, v1);
                    for (;;) {
                        // 0x00438470
                        charge(ctx, 3);
                        v0 = slti(s3, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004383c8
                        charge(ctx, 2);
                        if (s3 != s0) {
                            // 0x004383d0
                            charge(ctx, 10);
                            a0 = 0;
                            v0 = sll(s3, 3);
                            v0 = subu(v0, s3);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6048);  // &gFldUnitsPc
                            s2 = addu(v0, v1);
                            lw(v0, s2, 72);
                            if (v0 != 0) {
                                // 0x004383f8
                                charge(ctx, 3);
                                lw(v0, s2, 84);
                                if (v0 != 0) {
                                    // 0x00438404
                                    charge(ctx, 1);
                                    a0 = 1;
                                }
                            }
                            // 0x00438408
                            charge(ctx, 4);
                            v1 = sltu(0, a0);
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_0043846c;
                            }
                            // 0x00438418
                            charge(ctx, 8);
                            a0 = s2;
                            jal(ctx, 0x43841Cu, gen::fn_sub_4353F0_004353f0);
                            v1 = dsll32(v0, 24);
                            v1 = dsra32(v1, 24);
                            v0 = 6;
                            if (v1 != v0) {
                                goto L_0043846c;
                            }
                            // 0x00438438
                            charge(ctx, 9);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s5;
                            a1 = s2;
                            jal(ctx, 0x438448u, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_0043846c;
                            }
                            goto L_0043845c_51;
                        }
                    L_0043846c:
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                    // 0x0043847c
                    charge(ctx, 1);
                    a0 = 0;
                L_00438480:
                    charge(ctx, 7);
                    lw(s0, s1, kNpcPc);
                    jal(ctx, 0x438484u, gen::fn_sub_43C340_0043c340);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    if (s0 == v1) {
                        // 0x0043849c
                        charge(ctx, 11);
                        s0 = dsll32(s0, 24);
                        s0 = dsra32(s0, 24);
                        s3 = 1;
                        v1 = sll(s0, 3);
                        v1 = subu(v1, s0);
                        a0 = sll(v1, 6);
                        v1 = 0x870000;
                        v1 = addiu(v1, 6048);  // &gFldUnitsPc
                        s5 = addu(v1, a0);
                        for (;;) {
                            // 0x00438570
                            charge(ctx, 3);
                            v1 = slti(s3, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x004384c8
                            charge(ctx, 2);
                            if (s3 != s0) {
                                // 0x004384d0
                                charge(ctx, 10);
                                a1 = 0;
                                v1 = sll(s3, 3);
                                v1 = subu(v1, s3);
                                a0 = sll(v1, 6);
                                v1 = 0x870000;
                                v1 = addiu(v1, 6048);  // &gFldUnitsPc
                                s2 = addu(v1, a0);
                                lw(v1, s2, 72);
                                if (v1 != 0) {
                                    // 0x004384f8
                                    charge(ctx, 3);
                                    lw(v1, s2, 84);
                                    if (v1 != 0) {
                                        // 0x00438504
                                        charge(ctx, 1);
                                        a1 = 1;
                                    }
                                }
                                // 0x00438508
                                charge(ctx, 4);
                                a0 = sltu(0, a1);
                                v1 = 1;
                                if (a0 != v1) {
                                    goto L_0043856c;
                                }
                                // 0x00438518
                                charge(ctx, 8);
                                a0 = s2;
                                jal(ctx, 0x43851Cu, gen::fn_sub_4353F0_004353f0);
                                a0 = dsll32(v0, 24);
                                a0 = dsra32(a0, 24);
                                v1 = 6;
                                if (a0 != v1) {
                                    goto L_0043856c;
                                }
                                // 0x00438538
                                charge(ctx, 9);
                                v0 = 0x43FA0000;
                                mtc1(v0, f12);
                                a0 = s5;
                                a1 = s2;
                                jal(ctx, 0x438548u, gen::fn_sub_1C7160_001c7160);
                                v1 = 1;
                                if (v0 != v1) {
                                    goto L_0043856c;
                                }
                                goto L_0043855c_64;
                            }
                        L_0043856c:
                            charge(ctx, 1);
                            s3 = addiu(s3, 1);
                        }
                        // 0x0043857c
                        charge(ctx, 1);
                        v1 = 0;
                    L_00438580:
                        charge(ctx, 8);
                        v1 = dsll32(v1, 24);
                        v1 = dsra32(v1, 24);
                        sh(v1, s1, kNpcSkillTarget);
                        v1 = 1;
                        sb(v1, s1, kNpcSupport);
                        sb(zero, s1, kNpcSupportState);
                    }
                }
            }
        }
        // 0x00438798
        charge(ctx, 4);
        lb(v1, s1, kNpcExploreState);
        at = sltiu(v1, 9);
        if (at != 0) {
            // 0x004387a8
            charge(ctx, 7);
            a0 = 0x7C0000;
            a0 = addiu(a0, -15408);  // &0x7BC3D0
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x4387C4u:  // table[0]
                // 0x004387c4: explore state 0: start on the current cell
                charge(ctx, 42);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                a1 = 1;
                jal(ctx, 0x4387D0u, gen::fn_sub_1B0240_001b0240);
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x4387E4u, gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                sb(v0, s1, kNpcCellX);
                sb(v0, s1, kNpcWalkX);
                lw(v0, s1, kNpcUnit);
                lw(v0, v0, 84);
                lw(a0, v0, 480);
                jal(ctx, 0x438800u, gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                sb(v0, s1, kNpcCellZ);
                sb(v0, s1, kNpcWalkZ);
                lb(v0, s1, kNpcCellX);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                v0 = 0x44480000;
                mtc1(v0, f1);
                mul_s(f0, f1, f0);
                swc1(f0, s1, kNpcCellPosX);
                lb(v0, s1, kNpcCellZ);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f1, f0);
                swc1(f0, s1, kNpcCellPosZ);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x438854u, gen::fn_sub_1B00C0_001b00c0);
                lw(v1, s1, kNpcPc);
                v0 = 3;
                if (v1 == v0) {
                    // 0x004388a8
                    charge(ctx, 2);
                    v0 = 2;
                    sb(v0, s1, kNpcHand);
                } else {
                    // 0x0043886c
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00438898
                        charge(ctx, 4);
                        v0 = 1;
                        sb(v0, s1, kNpcHand);
                    } else {
                        // 0x00438878
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x0043888c
                            charge(ctx, 3);
                            sb(zero, s1, kNpcHand);
                        } else {
                            // 0x00438884
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x004388b0
                charge(ctx, 3);
                v0 = 1;
                sb(v0, s1, kNpcFacing);
                sb(v0, s1, kNpcExploreState);
                for (;;) {
                L_004388bc:
                    charge(ctx, 3);
                    lb(v1, s1, kNpcHand);
                    if (v1 != 0) {
                        // 0x004388e4
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x0043890c
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 != v0) {
                                // 0x00438934
                                charge(ctx, 3);
                                v0 = 3;
                                if (v1 == v0) {
                                    // 0x00438940
                                    charge(ctx, 5);
                                    a0 = s4;
                                    jal(ctx, 0x438944u, gen::fn_sub_432BB0_00432bb0);
                                    sb(v0, s1, kNpcStepDir);
                                    sb(v0, s1, kNpcFacing);
                                }
                            } else {
                                // 0x00438918
                                charge(ctx, 7);
                                a0 = s4;
                                jal(ctx, 0x43891Cu, gen::fn_sub_432600_00432600);
                                sb(v0, s1, kNpcStepDir);
                                sb(v0, s1, kNpcFacing);
                            }
                        } else {
                            // 0x004388f0
                            charge(ctx, 7);
                            a0 = s4;
                            jal(ctx, 0x4388F4u, gen::fn_sub_432050_00432050);
                            sb(v0, s1, kNpcStepDir);
                            sb(v0, s1, kNpcFacing);
                        }
                    } else {
                        // 0x004388c8
                        charge(ctx, 7);
                        a0 = s4;
                        jal(ctx, 0x4388CCu, gen::fn_sub_431AA0_00431aa0);
                        sb(v0, s1, kNpcStepDir);
                        sb(v0, s1, kNpcFacing);
                    }
                    // 0x00438954
                    charge(ctx, 9);
                    lw(a0, s4, 60);
                    lbu(v0, a0, 248);
                    v1 = addu(a0, v0);
                    lbu(v0, a0, 249);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lb(v0, v0, 265);
                    if (i64(v0) > 0) {
                        // 0x00438978
                        charge(ctx, 7);
                        a0 = s4;
                        jal(ctx, 0x43897Cu, gen::fn_sub_433160_00433160);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        if (v0 != 0) {
                            // 0x00438994
                            charge(ctx, 5);
                            sb(v0, s1, kNpcStepDir);
                            sb(v0, s1, kNpcFacing);
                            lb(v0, s1, kNpcHand);
                            v0 = v0 ^ 0x1;
                            sb(v0, s1, kNpcHand);
                        }
                    }
                    // 0x004389a8
                    charge(ctx, 3);
                    lb(v0, s1, kNpcStepDir);
                    if (v0 == 0) {
                        goto L_004389b4_117;
                    }
                    // 0x00438a18
                    charge(ctx, 2);
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
            L_00438a20:
                charge(ctx, 2);
                v0 = 2;
                sb(v0, s1, kNpcExploreState);
            L_00438a28:
                charge(ctx, 22);
                a0 = addiu(s1, kNpcCellPosX);
                jal(ctx, 0x438A2Cu, gen::fn_sub_44F120_0044f120);
                s0 = v0 & 0xFFFF;
                a0 = addiu(s1, kNpcCellPosX);
                jal(ctx, 0x438A3Cu, gen::fn_sub_44F170_0044f170);
                a2 = v0 & 0xFFFF;
                a0 = addiu(sp, 0xA0);
                a1 = s0;
                jal(ctx, 0x438A50u, gen::fn_sub_1BF220_001bf220);
                lwc1(f2, sp, 0xA0);
                lwc1(f1, sp, 0xA4);
                lwc1(f0, sp, 0xA8);
                swc1(f2, s1, kNpcWalkPosX);
                swc1(f1, s1, kNpcWalkPosY);
                swc1(f0, s1, kNpcWalkPosZ);
                lb(v1, s1, kNpcStepDir);
                v0 = 4;
                if (v1 == v0) {
                    // 0x00438b24
                    charge(ctx, 8);
                    lwc1(f1, s1, kNpcCellPosX);
                    v0 = 0x44480000;
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, s1, kNpcStepPosX);
                    lwc1(f0, s1, kNpcCellPosZ);
                    swc1(f0, s1, kNpcStepPosZ);
                } else {
                    // 0x00438a80
                    charge(ctx, 3);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x00438afc
                        charge(ctx, 10);
                        lwc1(f0, s1, kNpcCellPosX);
                        swc1(f0, s1, kNpcStepPosX);
                        lwc1(f1, s1, kNpcCellPosZ);
                        v0 = 0x44480000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, s1, kNpcStepPosZ);
                    } else {
                        // 0x00438a8c
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x00438ad4
                            charge(ctx, 10);
                            lwc1(f1, s1, kNpcCellPosX);
                            v0 = 0x44480000;
                            mtc1(v0, f0);
                            sub_s(f0, f1, f0);
                            swc1(f0, s1, kNpcStepPosX);
                            lwc1(f0, s1, kNpcCellPosZ);
                            swc1(f0, s1, kNpcStepPosZ);
                        } else {
                            // 0x00438a98
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00438aac
                                charge(ctx, 10);
                                lwc1(f0, s1, kNpcCellPosX);
                                swc1(f0, s1, kNpcStepPosX);
                                lwc1(f1, s1, kNpcCellPosZ);
                                v0 = 0x44480000;
                                mtc1(v0, f0);
                                sub_s(f0, f1, f0);
                                swc1(f0, s1, kNpcStepPosZ);
                            } else {
                                // 0x00438aa4
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00438b44
                charge(ctx, 22);
                a0 = addiu(s1, kNpcStepPosX);
                jal(ctx, 0x438B48u, gen::fn_sub_44F120_0044f120);
                s0 = v0 & 0xFFFF;
                a0 = addiu(s1, kNpcStepPosX);
                jal(ctx, 0x438B58u, gen::fn_sub_44F170_0044f170);
                a2 = v0 & 0xFFFF;
                a0 = addiu(sp, 0x90);
                a1 = s0;
                jal(ctx, 0x438B6Cu, gen::fn_sub_1BF220_001bf220);
                lwc1(f2, sp, 0x90);
                lwc1(f1, sp, 0x94);
                lwc1(f0, sp, 0x98);
                swc1(f2, s1, kNpcStepPosX);
                swc1(f1, s1, kNpcStepPosY);
                swc1(f0, s1, kNpcStepPosZ);
                v1 = 3;
                sb(v1, s1, kNpcExploreState);
                break;
            case 0x4388BCu:  // table[1]
                goto L_004388bc;
            case 0x438A28u:  // table[2]
                goto L_00438a28;
            case 0x438B9Cu:  // table[3]
                // 0x00438b9c: states 2 / 3: towards the next cell
                charge(ctx, 8);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                a1 = addiu(s1, kNpcStepPosX);
                lwc1(f12, gp, -32072);  // 0x7CAFA8
                jal(ctx, 0x438BACu, gen::fn_sub_1AFA20_001afa20);
                if (v0 != 0) {
                    // 0x00438bbc
                    charge(ctx, 10);
                    jal(ctx, 0x438BBCu, gen::fn_sub_488F30_00488f30);
                    v1 = 100;
                    divu(v0, v1);
                    mfhi(v0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    at = slti(v0, 10);
                    if (at != 0) {
                        // 0x00438be4
                        charge(ctx, 7);
                        lw(v0, s1, kNpcUnit);
                        lw(a0, v0, 368);
                        a1 = 60;
                        jal(ctx, 0x438BF0u, gen::fn_sub_1AFF70_001aff70);
                        if (v0 != 0) {
                            goto L_00438c00;
                        }
                        break;
                    }
                L_00438c00:
                    charge(ctx, 16);
                    lwc1(f2, s1, kNpcStepPosX);
                    lwc1(f1, s1, kNpcStepPosY);
                    lwc1(f0, s1, kNpcStepPosZ);
                    swc1(f2, s1, kNpcCellPosX);
                    swc1(f1, s1, kNpcCellPosY);
                    swc1(f0, s1, kNpcCellPosZ);
                    v0 = 1;
                    sb(v0, s1, kNpcExploreState);
                    a0 = s4;
                    jal(ctx, 0x438C24u, gen::fn_sub_431880_00431880);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00438c40
                        charge(ctx, 2);
                        v0 = 4;
                        sb(v0, s1, kNpcExploreState);
                    }
                    // 0x00438c48
                    charge(ctx, 6);
                    a0 = s4;
                    jal(ctx, 0x438C4Cu, gen::fn_sub_4334D0_004334d0);
                    sw(zero, s1, kNpcTimer);
                }
                break;
            case 0x438C60u:  // table[4]
                // 0x00438c60: state 4: turn to the least visited side
                charge(ctx, 8);
                a0 = s4;
                jal(ctx, 0x438C64u, gen::fn_sub_4339D0_004339d0);
                sb(v0, s1, kNpcStepDir);
                v1 = 2;
                sb(v1, s1, kNpcExploreState);
                break;
            case 0x438C80u:  // table[5]
            L_00438c80:
                charge(ctx, 6);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x438C88u, gen::fn_sub_1B0220_001b0220);
                if (v0 == 0) {
                    // 0x00438c98
                    charge(ctx, 3);
                    sb(zero, s1, kNpcExploreState);
                }
                break;
            case 0x438CA4u:  // table[6]
                // 0x00438ca4: state 6: a chest: walk to it
                charge(ctx, 7);
                lw(a0, s1, kNpcUnit);
                lwc1(f12, s6, 20);
                jal(ctx, 0x438CACu, gen::fn_sub_1C7270_001c7270);
                sw(v0, s1, kNpcChest);
                if (v0 != 0) {
                    // 0x00438d18
                    charge(ctx, 68);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    jal(ctx, 0x438D20u, gen::fn_sub_1B00C0_001b00c0);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    a1 = 0;
                    jal(ctx, 0x438D34u, gen::fn_sub_1B0240_001b0240);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 80);
                    jal(ctx, 0x438D44u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0xF0);
                    swc1(f1, sp, 0xF4);
                    swc1(f0, sp, 0xF8);
                    lw(v0, s1, kNpcChest);
                    lwc1(f2, v0, 268);
                    lwc1(f1, v0, 272);
                    lwc1(f0, v0, 276);
                    swc1(f2, sp, 0xE0);
                    swc1(f1, sp, 0xE4);
                    swc1(f0, sp, 0xE8);
                    lwc1(f1, sp, 0xF0);
                    lwc1(f0, sp, 0xE0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xD0);
                    lwc1(f21, sp, 0xE4);
                    lwc1(f0, sp, 0xF4);
                    sub_s(f0, f0, f21);
                    swc1(f0, sp, 0xD4);
                    lwc1(f20, sp, 0xE8);
                    lwc1(f0, sp, 0xF8);
                    sub_s(f0, f0, f20);
                    swc1(f0, sp, 0xD8);
                    a0 = addiu(sp, 0xD0);
                    a1 = a0;
                    jal(ctx, 0x438DB8u, gen::fn_sub_4C69F0_004c69f0);
                    v0 = 0x43480000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xD0);
                    mul_s(f3, f1, f0);
                    swc1(f3, sp, 0xC0);
                    lwc1(f0, sp, 0xD4);
                    mul_s(f2, f1, f0);
                    swc1(f2, sp, 0xC4);
                    lwc1(f0, sp, 0xD8);
                    mul_s(f1, f1, f0);
                    swc1(f1, sp, 0xC8);
                    lwc1(f0, sp, 0xE0);
                    add_s(f0, f3, f0);
                    swc1(f0, sp, 0xC0);
                    add_s(f0, f2, f21);
                    swc1(f0, sp, 0xC4);
                    add_s(f0, f1, f20);
                    swc1(f0, sp, 0xC8);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    a1 = addiu(sp, 0xC0);
                    lwc1(f12, gp, -32072);  // 0x7CAFA8
                    jal(ctx, 0x438E18u, gen::fn_sub_1AFA20_001afa20);
                    v0 = 7;
                    sb(v0, s1, kNpcExploreState);
                L_00438e28:
                    charge(ctx, 6);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    jal(ctx, 0x438E30u, gen::fn_sub_1B0220_001b0220);
                    if (v0 == 0) {
                        // 0x00438e40
                        charge(ctx, 3);
                        lw(a0, s1, kNpcChest);
                        if (a0 != 0) {
                            // 0x00438ea4
                            charge(ctx, 3);
                            lw(v1, a0, 0);
                            if (v1 != 0) {
                                // 0x00438f08
                                charge(ctx, 4);
                                lw(v1, a0, 4);
                                a1 = 1;
                                if (v1 != a1) {
                                    // 0x00438f68
                                    charge(ctx, 6);
                                    lb(a0, s1, kNpcPc);
                                    jal(ctx, 0x438F6Cu, gen::fn_sub_456620_00456620);
                                    lw(v0, s1, kNpcTreasureTask);
                                    if (v0 != 0) {
                                        // 0x00438f80
                                        charge(ctx, 1);
                                        sw(zero, s1, kNpcTreasureTask);
                                    }
                                    // 0x00438f84
                                    charge(ctx, 10);
                                    lw(a0, s1, kNpcChest);
                                    jal(ctx, 0x438F88u, gen::fn_Y_Npc_CreateTreasureFreeTask_0043c690);
                                    sw(v0, s1, kNpcTreasureTask);
                                    lw(v1, s1, kNpcChest);
                                    lw(v1, v1, 284);
                                    lhu(a0, v1, 2);
                                    v1 = 4021;
                                    if (a0 != v1) {
                                        // 0x00438fac
                                        charge(ctx, 3);
                                        at = slti(a0, 4000);
                                        if (at == 0) {
                                            // 0x0043907c
                                            charge(ctx, 4);
                                            lw(a1, s1, kNpcPc);
                                            a0 = 1;
                                            if (a1 != a0) {
                                                // 0x00439098
                                                charge(ctx, 3);
                                                v1 = 2;
                                                if (a1 != v1) {
                                                    // 0x004390b0
                                                    charge(ctx, 3);
                                                    v1 = 3;
                                                    if (a1 == v1) {
                                                        // 0x004390bc
                                                        charge(ctx, 1);
                                                        sb(a0, gp, -17948);  // 0x7CE6D4
                                                    }
                                                } else {
                                                    // 0x004390a4
                                                    charge(ctx, 3);
                                                    sb(a0, gp, -17952);  // 0x7CE6D0
                                                }
                                            } else {
                                                // 0x0043908c
                                                charge(ctx, 3);
                                                sb(a0, gp, -17956);  // 0x7CE6CC
                                            }
                                            // 0x004390c0
                                            charge(ctx, 4);
                                            s0 = 0;
                                            s3 = 0;
                                            for (;;) {
                                                // 0x004391ec
                                                charge(ctx, 3);
                                                v1 = slti(s3, 20);
                                                if (v1 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x004390d0
                                                charge(ctx, 18);
                                                lw(v0, s1, kNpcChest);
                                                lw(v0, v0, 284);
                                                lhu(s2, v0, 2);
                                                lw(v1, s1, kNpcPc);
                                                v0 = sll(v1, 3);
                                                v0 = subu(v0, v1);
                                                v1 = sll(v0, 6);
                                                v0 = 0x870000;
                                                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                                v0 = addu(v0, v1);
                                                lh(a0, v0, 424);
                                                a1 = dsll32(s3, 16);
                                                a1 = dsra32(a1, 16);
                                                jal(ctx, 0x439104u, gen::fn_sub_170A40_00170a40);
                                                v1 = v0 & 0xFFFF;
                                                if (s2 == v1) {
                                                    goto L_00439118_185;
                                                }
                                                // 0x004391e8
                                                charge(ctx, 1);
                                                s3 = addiu(s3, 1);
                                            }
                                        L_004391f8:
                                            charge(ctx, 4);
                                            v1 = dsll32(s0, 24);
                                            v1 = dsra32(v1, 24);
                                            if (v1 == 0) {
                                                // 0x00439208
                                                charge(ctx, 3);
                                                s0 = 0;
                                                for (;;) {
                                                    // 0x004392d8
                                                    charge(ctx, 3);
                                                    v1 = slti(s0, 20);
                                                    if (v1 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                    // 0x00439214
                                                    charge(ctx, 16);
                                                    lw(v1, s1, kNpcPc);
                                                    v0 = sll(v1, 3);
                                                    v0 = subu(v0, v1);
                                                    v1 = sll(v0, 6);
                                                    v0 = 0x870000;
                                                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                                    v0 = addu(v0, v1);
                                                    lh(a0, v0, 424);
                                                    a1 = dsll32(s0, 16);
                                                    a1 = dsra32(a1, 16);
                                                    jal(ctx, 0x43923Cu, gen::fn_sub_170AB0_00170ab0);
                                                    v1 = dsll32(v0, 16);
                                                    v1 = dsra32(v1, 16);
                                                    if (i64(v1) <= 0) {
                                                        goto L_00439254_193;
                                                    }
                                                    // 0x004392d4
                                                    charge(ctx, 1);
                                                    s0 = addiu(s0, 1);
                                                }
                                            }
                                        } else {
                                            // 0x00438fb8
                                            charge(ctx, 4);
                                            lw(a0, s1, kNpcPc);
                                            v1 = 1;
                                            if (a0 != v1) {
                                                // 0x00438fd4
                                                charge(ctx, 3);
                                                v0 = 2;
                                                if (a0 != v0) {
                                                    // 0x00438fec
                                                    charge(ctx, 3);
                                                    v0 = 3;
                                                    if (a0 == v0) {
                                                        // 0x00438ff8
                                                        charge(ctx, 1);
                                                        sb(v1, gp, -17948);  // 0x7CE6D4
                                                    }
                                                } else {
                                                    // 0x00438fe0
                                                    charge(ctx, 3);
                                                    sb(v1, gp, -17952);  // 0x7CE6D0
                                                }
                                            } else {
                                                // 0x00438fc8
                                                charge(ctx, 3);
                                                sb(v1, gp, -17956);  // 0x7CE6CC
                                            }
                                            // 0x00438ffc
                                            charge(ctx, 32);
                                            lw(v1, s1, kNpcPc);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = 0x870000;
                                            v0 = addiu(v0, 6472);  // &0x871948
                                            v0 = addu(v0, v1);
                                            lhu(v0, v0, 0);
                                            v0 = addiu(v0, 256);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            jal(ctx, 0x439028u, gen::fn_sub_16F490_0016f490);
                                            a1 = dsll32(v0, 16);
                                            a1 = dsra32(a1, 16);
                                            lw(v1, s1, kNpcPc);
                                            v0 = sll(v1, 3);
                                            v0 = subu(v0, v1);
                                            v1 = sll(v0, 6);
                                            v0 = 0x870000;
                                            v0 = addiu(v0, 6472);  // &0x871948
                                            v0 = addu(v0, v1);
                                            lhu(v0, v0, 0);
                                            v0 = addiu(v0, 256);
                                            a0 = dsll32(v0, 16);
                                            a0 = dsra32(a0, 16);
                                            lw(v0, s1, kNpcChest);
                                            a2 = addiu(v0, 288);
                                            jal(ctx, 0x43906Cu, gen::fn_sub_1831E0_001831e0);
                                        }
                                    }
                                L_004392e4:
                                    charge(ctx, 30);
                                    lw(v1, s1, kNpcChest);
                                    lw(v1, v1, 284);
                                    lhu(a1, v1, 2);
                                    lw(a0, s1, kNpcPc);
                                    v1 = sll(a0, 3);
                                    v1 = subu(v1, a0);
                                    a0 = sll(v1, 6);
                                    v1 = 0x870000;
                                    v1 = addiu(v1, 6474);  // &0x87194A
                                    v1 = addu(v1, a0);
                                    sh(a1, v1, 0);
                                    lw(v1, s1, kNpcChest);
                                    lw(v1, v1, 284);
                                    lbu(a1, v1, 7);
                                    lw(a0, s1, kNpcPc);
                                    v1 = sll(a0, 3);
                                    v1 = subu(v1, a0);
                                    a0 = sll(v1, 6);
                                    v1 = 0x870000;
                                    v1 = addiu(v1, 6476);  // &0x87194C
                                    v1 = addu(v1, a0);
                                    sh(a1, v1, 0);
                                    a0 = 1;
                                    lw(v1, s1, kNpcChest);
                                    sw(a0, v1, 4);
                                    v1 = 8;
                                    sb(v1, s1, kNpcExploreState);
                                    sb(zero, s1, kNpcBusy);
                                } else {
                                    // 0x00438f18
                                    charge(ctx, 3);
                                    lb(v1, gp, -17972);  // 0x7CE6BC
                                    if (v1 != 0) {
                                        // 0x00438f3c
                                        charge(ctx, 2);
                                        if (v1 == a1) {
                                            // 0x00438f44
                                            charge(ctx, 6);
                                            lb(a0, s1, kNpcPc);
                                            a1 = 2;
                                            jal(ctx, 0x438F4Cu, gen::fn_sub_43C7A0_0043c7a0);
                                            v1 = 1;
                                            sb(v1, s1, kNpcExploring);
                                        }
                                    } else {
                                        // 0x00438f24
                                        charge(ctx, 6);
                                        lb(a0, s1, kNpcPc);
                                        jal(ctx, 0x438F28u, gen::fn_sub_43C7A0_0043c7a0);
                                        sb(zero, s1, kNpcExploring);
                                    }
                                    // 0x00438f5c
                                    charge(ctx, 3);
                                    sb(zero, s1, kNpcBusy);
                                }
                            } else {
                                // 0x00438eb0
                                charge(ctx, 3);
                                lb(a0, gp, -17972);  // 0x7CE6BC
                                if (a0 != 0) {
                                    // 0x00438ed8
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (a0 == v1) {
                                        // 0x00438ee4
                                        charge(ctx, 6);
                                        lb(a0, s1, kNpcPc);
                                        a1 = 2;
                                        jal(ctx, 0x438EECu, gen::fn_sub_43C7A0_0043c7a0);
                                        v1 = 1;
                                        sb(v1, s1, kNpcExploring);
                                    }
                                } else {
                                    // 0x00438ebc
                                    charge(ctx, 7);
                                    lb(a0, s1, kNpcPc);
                                    a1 = 1;
                                    jal(ctx, 0x438EC4u, gen::fn_sub_43C7A0_0043c7a0);
                                    sb(zero, s1, kNpcExploring);
                                }
                                // 0x00438efc
                                charge(ctx, 3);
                                sb(zero, s1, kNpcBusy);
                            }
                        } else {
                            // 0x00438e4c
                            charge(ctx, 3);
                            lb(a0, gp, -17972);  // 0x7CE6BC
                            if (a0 != 0) {
                                // 0x00438e74
                                charge(ctx, 3);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x00438e80
                                    charge(ctx, 6);
                                    lb(a0, s1, kNpcPc);
                                    a1 = 2;
                                    jal(ctx, 0x438E88u, gen::fn_sub_43C7A0_0043c7a0);
                                    v1 = 1;
                                    sb(v1, s1, kNpcExploring);
                                }
                            } else {
                                // 0x00438e58
                                charge(ctx, 7);
                                lb(a0, s1, kNpcPc);
                                a1 = 1;
                                jal(ctx, 0x438E60u, gen::fn_sub_43C7A0_0043c7a0);
                                sb(zero, s1, kNpcExploring);
                            }
                            // 0x00438e98
                            charge(ctx, 3);
                            sb(zero, s1, kNpcBusy);
                        }
                    }
                } else {
                    // 0x00438cc0
                    charge(ctx, 3);
                    lb(a0, gp, -17972);  // 0x7CE6BC
                    if (a0 != 0) {
                        // 0x00438ce8
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x00438cf4
                            charge(ctx, 6);
                            lb(a0, s1, kNpcPc);
                            a1 = 2;
                            jal(ctx, 0x438CFCu, gen::fn_sub_43C7A0_0043c7a0);
                            v1 = 1;
                            sb(v1, s1, kNpcExploring);
                        }
                    } else {
                        // 0x00438ccc
                        charge(ctx, 7);
                        lb(a0, s1, kNpcPc);
                        a1 = 1;
                        jal(ctx, 0x438CD4u, gen::fn_sub_43C7A0_0043c7a0);
                        sb(zero, s1, kNpcExploring);
                    }
                    // 0x00438d0c
                    charge(ctx, 3);
                    sb(zero, s1, kNpcBusy);
                }
                break;
            case 0x438E28u:  // table[7]
                goto L_00438e28;
            case 0x43935Cu:  // table[8]
                // 0x0043935c: state 8: wait for the treasure task
                charge(ctx, 5);
                lw(a0, s1, kNpcTreasureTask);
                jal(ctx, 0x439360u, gen::fn_kwlnTaskExists_00195460);
                if (v0 == 0) {
                    // 0x00439370
                    charge(ctx, 3);
                    lb(a0, gp, -17972);  // 0x7CE6BC
                    if (a0 != 0) {
                        // 0x00439398
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x004393a4
                            charge(ctx, 6);
                            lb(a0, s1, kNpcPc);
                            a1 = 2;
                            jal(ctx, 0x4393ACu, gen::fn_sub_43C7A0_0043c7a0);
                            v1 = 1;
                            sb(v1, s1, kNpcExploring);
                        }
                    } else {
                        // 0x0043937c
                        charge(ctx, 7);
                        lb(a0, s1, kNpcPc);
                        a1 = 1;
                        jal(ctx, 0x439384u, gen::fn_sub_43C7A0_0043c7a0);
                        sb(zero, s1, kNpcExploring);
                    }
                    // 0x004393bc
                    charge(ctx, 1);
                    sw(zero, s1, kNpcTreasureTask);
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
    } else {
        // 0x00438060
        charge(ctx, 6);
        lb(a0, s1, kNpcPc);
        a1 = 5;
        jal(ctx, 0x438068u, gen::fn_sub_43C7A0_0043c7a0);
    }
    // 0x004393c0 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
    return;
L_00438180_12:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_004381a4;
L_00438270_25:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00438294;
L_00438364_38:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00438388;
L_0043845c_51:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00438480;
L_0043855c_64:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_00438580;
L_0043865c_77:
    charge(ctx, 4);
    a0 = dsll32(s3, 24);
    a0 = dsra32(a0, 24);
    goto L_00438680;
L_0043875c_90:
    charge(ctx, 4);
    v1 = dsll32(s3, 24);
    v1 = dsra32(v1, 24);
    goto L_00438780;
L_004389b4_117:
    charge(ctx, 21);
    lw(v0, s1, kNpcUnit);
    lw(a0, v0, 368);
    a1 = 0;
    jal(ctx, 0x4389C0u, gen::fn_sub_1B0240_001b0240);
    lw(v0, s1, kNpcUnit);
    lw(a0, v0, 368);
    jal(ctx, 0x4389D0u, gen::fn_sub_1B00C0_001b00c0);
    lb(a1, s1, kNpcPc);
    a0 = addiu(sp, 0xB0);
    jal(ctx, 0x4389E0u, gen::fn_sub_437E80_00437e80);
    lw(v0, s1, kNpcUnit);
    lw(a0, v0, 368);
    a1 = addiu(sp, 0xB0);
    lwc1(f12, gp, -32072);  // 0x7CAFA8
    jal(ctx, 0x4389F8u, gen::fn_sub_1AFA20_001afa20);
    if (v0 == 0) {
        goto L_00438a20;
    }
    // 0x00438a08
    charge(ctx, 4);
    v0 = 5;
    sb(v0, s1, kNpcExploreState);
    goto L_00438c80;
L_00439118_185:
    charge(ctx, 34);
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    a1 = dsll32(s3, 16);
    a1 = dsra32(a1, 16);
    a2 = s2;
    jal(ctx, 0x439144u, gen::fn_sub_170B20_00170b20);
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    a1 = dsll32(s3, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x439174u, gen::fn_sub_170AB0_00170ab0);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    lw(v0, s1, kNpcChest);
    lw(v0, v0, 284);
    lbu(v0, v0, 6);
    a2 = addu(v1, v0);
    at = slti(a2, 100);
    if (at == 0) {
        // 0x004391a0
        charge(ctx, 1);
        a2 = 99;
    }
    // 0x004391a4
    charge(ctx, 17);
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    a1 = dsll32(s3, 16);
    a1 = dsra32(a1, 16);
    a2 = dsll32(a2, 16);
    a2 = dsra32(a2, 16);
    jal(ctx, 0x4391D4u, gen::fn_sub_170B90_00170b90);
    s0 = 1;
    goto L_004391f8;
L_00439254_193:
    charge(ctx, 32);
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    lw(v0, s1, kNpcChest);
    lw(v0, v0, 284);
    lhu(a2, v0, 2);
    jal(ctx, 0x439288u, gen::fn_sub_170B20_00170b20);
    lw(v1, s1, kNpcPc);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    lw(v0, s1, kNpcChest);
    lw(v0, v0, 284);
    lbu(a2, v0, 6);
    jal(ctx, 0x4392C4u, gen::fn_sub_170B90_00170b90);
    goto L_004392e4;
}

// 0x00439400 sub_439400 -- 280 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CheckChest] ($a0 pc) unless busy: the nearest unopened chest (sub_1C7270, record +4 != 1) within reach of
// the member's model (sub_1C6450 on its +268 position) sets kNpcBusy and explore state 6.
void sub_439400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00439400
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = dsll32(a0, 24);
    a0 = dsra32(a0, 24);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    s3 = sll(v1, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 6412);  // &0x87190C
    v1 = addu(v1, s3);
    lw(v1, v1, 0);
    lw(s2, v1, 60);
    lw(s1, gp, -19040);  // 0x7CE290
    lb(a0, s2, kNpcBusy);
    v1 = 1;
    if (a0 != v1) {
        // 0x00439454
        charge(ctx, 7);
        lw(a0, s2, kNpcUnit);
        lwc1(f12, s1, 20);
        jal(ctx, 0x43945Cu, gen::fn_sub_1C7270_001c7270);
        s0 = v0;
        if (s0 != 0) {
            // 0x00439470
            charge(ctx, 4);
            lw(a0, s0, 4);
            v1 = 1;
            if (a0 != v1) {
                // 0x00439480
                charge(ctx, 7);
                v1 = 0x870000;
                v1 = addiu(v1, 6120);  // &0x8717E8
                v1 = addu(v1, s3);
                lw(v1, v1, 0);
                v1 = sltu(0, v1);
                if (v1 != 0) {
                    // 0x0043949c
                    charge(ctx, 5);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6132);  // &0x8717F4
                    v1 = addu(v1, s3);
                    lw(v1, v1, 0);
                    v1 = sltu(0, v1);
                }
                // 0x004394b0
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x004394b8
                    charge(ctx, 13);
                    lw(v0, s2, kNpcUnit);
                    lw(a0, v0, 80);
                    jal(ctx, 0x4394C0u, gen::fn_sub_318B60_00318b60);
                    a0 = v0;
                    a1 = addiu(s0, 268);
                    lwc1(f12, s1, 16);
                    lwc1(f13, s1, 20);
                    jal(ctx, 0x4394D8u, gen::fn_sub_1C6450_001c6450);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x004394ec
                        charge(ctx, 3);
                        sb(v1, s2, kNpcBusy);
                        v1 = 6;
                        sb(v1, s2, kNpcExploreState);
                    }
                }
            }
        }
    }
    // 0x004394f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00439520 sub_439520 -- 2616 bytes; frame 0x100: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateSkirmish] Think mode 5 ($a0 task), kNpcFightState (jump table 0x7BC400): 0 find the touching shadow
// (or the hero's) and walk 200 short of it (1), back to follow / explore when none; 1 wait for the mover; 2 join its
// "battle kosaka" task or create one (K_Battle_CreateBattleTask), the shadow into contact (sub_44E530, sub_453490),
// the member's fight mode (sub_456530 / sub_456580); 3 / 6 wait for the battle task (down -> mode 6); 4 the
// persona's status after the fight (sub_4564E0 / sub_4565D0), back to follow / explore; 5 join the battle of shadow
// kNpcFightEnemy.
void sub_439520(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00439520
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    lw(s1, a0, 60);
    lw(s0, gp, -19040);  // 0x7CE290
    lb(v1, s1, kNpcFightState);
    at = sltiu(v1, 7);
    if (at != 0) {
        // 0x0043955c
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -15360);  // &0x7BC400
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x439578u:  // table[0]
            // 0x00439578: skirmish state 0: find the shadow
            charge(ctx, 6);
            lw(a0, s1, kNpcUnit);
            lwc1(f12, s0, 4);
            jal(ctx, 0x439580u, gen::fn_sub_1C6720_001c6720);
            if (v0 == 0) {
                // 0x004395a0
                charge(ctx, 12);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                a1 = 0;
                jal(ctx, 0x4395ACu, gen::fn_sub_1B0240_001b0240);
                lw(v0, s1, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x4395BCu, gen::fn_sub_1B00C0_001b00c0);
                lb(v0, gp, -17972);  // 0x7CE6BC
                if (v0 != 0) {
                    // 0x00439620
                    charge(ctx, 5);
                    lw(a0, s1, kNpcUnit);
                    lwc1(f12, s0, 20);
                    jal(ctx, 0x439628u, gen::fn_sub_1C6720_001c6720);
                    s2 = v0;
                } else {
                    // 0x004395d0
                    charge(ctx, 13);
                    a0 = 0x870000;
                    a0 = addiu(a0, 6048);  // &gFldUnitsPc
                    lwc1(f12, s0, 20);
                    jal(ctx, 0x4395DCu, gen::fn_sub_1C6720_001c6720);
                    s2 = v0;
                    v0 = 0x44480000;
                    mtc1(v0, f12);
                    lw(a0, s1, kNpcUnit);
                    jal(ctx, 0x4395F4u, gen::fn_sub_1C7130_001c7130);
                    if (v0 == 0) {
                        // 0x00439604
                        charge(ctx, 7);
                        lw(a0, s1, kNpcUnit);
                        lwc1(f12, s0, 20);
                        jal(ctx, 0x43960Cu, gen::fn_sub_1C6720_001c6720);
                        s2 = v0;
                    }
                }
                // 0x00439634
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x0043974c
                    charge(ctx, 4);
                    lb(v1, s1, kNpcExploring);
                    a1 = 1;
                    if (v1 == a1) {
                        // 0x00439780
                        charge(ctx, 6);
                        lb(a0, s1, kNpcPc);
                        a1 = 2;
                        jal(ctx, 0x439788u, gen::fn_sub_43C7A0_0043c7a0);
                    } else {
                        // 0x0043975c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0043976c
                            charge(ctx, 5);
                            lb(a0, s1, kNpcPc);
                            jal(ctx, 0x439770u, gen::fn_sub_43C7A0_0043c7a0);
                        } else {
                            // 0x00439764
                            charge(ctx, 2);
                        }
                    }
                } else {
                    // 0x0043963c
                    charge(ctx, 68);
                    lw(a0, s2, 80);
                    jal(ctx, 0x439640u, gen::fn_sub_318B60_00318b60);
                    s0 = addiu(v0, 48);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 80);
                    jal(ctx, 0x439654u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0xD0);
                    swc1(f1, sp, 0xD4);
                    swc1(f0, sp, 0xD8);
                    lwc1(f2, s0, 0);
                    lwc1(f1, s0, 4);
                    lwc1(f0, s0, 8);
                    swc1(f2, sp, 0xC0);
                    swc1(f1, sp, 0xC4);
                    swc1(f0, sp, 0xC8);
                    lwc1(f1, sp, 0xD0);
                    lwc1(f0, sp, 0xC0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0xB0);
                    lwc1(f21, sp, 0xC4);
                    lwc1(f0, sp, 0xD4);
                    sub_s(f0, f0, f21);
                    swc1(f0, sp, 0xB4);
                    lwc1(f20, sp, 0xC8);
                    lwc1(f0, sp, 0xD8);
                    sub_s(f0, f0, f20);
                    swc1(f0, sp, 0xB8);
                    a0 = addiu(sp, 0xB0);
                    a1 = a0;
                    jal(ctx, 0x4396C4u, gen::fn_sub_4C69F0_004c69f0);
                    v0 = 0x43480000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xB0);
                    mul_s(f3, f1, f0);
                    swc1(f3, sp, 0xA0);
                    lwc1(f0, sp, 0xB4);
                    mul_s(f2, f1, f0);
                    swc1(f2, sp, 0xA4);
                    lwc1(f0, sp, 0xB8);
                    mul_s(f1, f1, f0);
                    swc1(f1, sp, 0xA8);
                    lwc1(f0, sp, 0xC0);
                    add_s(f0, f3, f0);
                    swc1(f0, sp, 0xA0);
                    add_s(f0, f2, f21);
                    swc1(f0, sp, 0xA4);
                    add_s(f0, f1, f20);
                    swc1(f0, sp, 0xA8);
                    a1 = addiu(sp, 0xF0);
                    ld(v0, sp, 0xA0);
                    lwc1(f0, sp, 0xA8);
                    sd(v0, sp, 0xF0);
                    swc1(f0, sp, 0xF8);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    lwc1(f12, gp, -32072);  // 0x7CAFA8
                    jal(ctx, 0x439734u, gen::fn_sub_1AFA20_001afa20);
                    v1 = 1;
                    sb(v1, s1, kNpcFightState);
                }
            } else {
                // 0x00439590
                charge(ctx, 4);
                v1 = 2;
                sb(v1, s1, kNpcFightState);
            }
            break;
        case 0x439798u:  // table[1]
            // 0x00439798: state 1: wait for the mover
            charge(ctx, 6);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            jal(ctx, 0x4397A0u, gen::fn_sub_1B0220_001b0220);
            if (v0 == 0) {
                // 0x004397b0
                charge(ctx, 3);
                lw(v1, s1, kNpcFightTask);
                if (v1 != 0) {
                    // 0x004397bc
                    charge(ctx, 1);
                    sw(zero, s1, kNpcFightTask);
                }
                // 0x004397c0
                charge(ctx, 4);
                v1 = 2;
                sb(v1, s1, kNpcFightState);
            }
            break;
        case 0x4397D0u:  // table[2]
            // 0x004397d0: state 2: start or join the battle
            charge(ctx, 12);
            lw(v0, s1, kNpcUnit);
            lw(a0, v0, 368);
            a1 = 0;
            jal(ctx, 0x4397DCu, gen::fn_sub_1B0240_001b0240);
            lw(a0, s1, kNpcUnit);
            lwc1(f12, s0, 20);
            jal(ctx, 0x4397ECu, gen::fn_sub_1C6720_001c6720);
            s2 = v0;
            if (s2 != 0) {
                // 0x00439810
                charge(ctx, 6);
                lw(a0, s1, kNpcUnit);
                lwc1(f12, s0, 4);
                jal(ctx, 0x439818u, gen::fn_sub_1C6720_001c6720);
                if (v0 != 0) {
                    // 0x00439948
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x43994Cu, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                    if (v0 != 0) {
                        // 0x00439a54
                        charge(ctx, 30);
                        a0 = s2;
                        jal(ctx, 0x439A58u, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                        a0 = v0;
                        lw(a1, s1, kNpcUnit);
                        a2 = 0;
                        jal(ctx, 0x439A6Cu, gen::fn_sub_1D8E60_001d8e60);
                        a0 = s2;
                        jal(ctx, 0x439A78u, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                        sw(v0, s1, kNpcFightTask);
                        lw(a0, s2, 364);
                        jal(ctx, 0x439A88u, gen::fn_sub_453490_00453490);
                        v0 = 3;
                        sb(v0, s1, kNpcFightState);
                        lw(v1, s1, kNpcPc);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6472);  // &0x871948
                        v0 = addu(v0, v1);
                        lh(a0, v0, 0);
                        jal(ctx, 0x439AB8u, gen::fn_sub_16C470_0016c470);
                        sb(v0, s1, kNpcFightLevel);
                    } else {
                        // 0x0043995c
                        charge(ctx, 15);
                        a0 = s3;
                        lw(a1, s1, kNpcUnit);
                        a2 = s2;
                        jal(ctx, 0x439968u, gen::fn_K_Battle_CreateBattleTask_001d8b00);
                        sw(v0, s1, kNpcFightTask);
                        v0 = 3;
                        sb(v0, s1, kNpcFightState);
                        lw(a0, s2, 364);
                        jal(ctx, 0x439980u, gen::fn_sub_453490_00453490);
                        lw(v1, s2, 396);
                        v0 = 4;
                        if (v1 != v0) {
                            // 0x004399d8
                            charge(ctx, 10);
                            lw(a0, s1, kNpcPc);
                            v0 = sll(a0, 3);
                            v0 = subu(v0, a0);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6459);  // &0x87193B
                            v0 = addu(v0, v1);
                            lb(v0, v0, 0);
                            if (v0 == 0) {
                                // 0x00439a00
                                charge(ctx, 4);
                                a0 = dsll32(a0, 24);
                                a0 = dsra32(a0, 24);
                                jal(ctx, 0x439A08u, gen::fn_sub_456580_00456580);
                            }
                        } else {
                            // 0x00439998
                            charge(ctx, 10);
                            lw(a0, s1, kNpcPc);
                            v0 = sll(a0, 3);
                            v0 = subu(v0, a0);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6459);  // &0x87193B
                            v0 = addu(v0, v1);
                            lb(v0, v0, 0);
                            if (v0 == 0) {
                                // 0x004399c0
                                charge(ctx, 6);
                                a0 = dsll32(a0, 24);
                                a0 = dsra32(a0, 24);
                                jal(ctx, 0x4399C8u, gen::fn_sub_456530_00456530);
                            }
                        }
                        // 0x00439a10
                        charge(ctx, 17);
                        lb(a1, s1, kNpcPc);
                        a0 = s2;
                        jal(ctx, 0x439A18u, gen::fn_sub_44E530_0044e530);
                        lw(v1, s1, kNpcPc);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6472);  // &0x871948
                        v0 = addu(v0, v1);
                        lh(a0, v0, 0);
                        jal(ctx, 0x439A40u, gen::fn_sub_16C470_0016c470);
                        sb(v0, s1, kNpcFightLevel);
                    }
                } else {
                    // 0x00439828
                    charge(ctx, 72);
                    lw(a0, s1, kNpcUnit);
                    lwc1(f12, s0, 20);
                    jal(ctx, 0x439830u, gen::fn_sub_1C6720_001c6720);
                    lw(a0, v0, 80);
                    jal(ctx, 0x43983Cu, gen::fn_sub_318B60_00318b60);
                    s0 = addiu(v0, 48);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 80);
                    jal(ctx, 0x439850u, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0x90);
                    swc1(f1, sp, 0x94);
                    swc1(f0, sp, 0x98);
                    lwc1(f2, s0, 0);
                    lwc1(f1, s0, 4);
                    lwc1(f0, s0, 8);
                    swc1(f2, sp, 0x80);
                    swc1(f1, sp, 0x84);
                    swc1(f0, sp, 0x88);
                    lwc1(f1, sp, 0x90);
                    lwc1(f0, sp, 0x80);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x70);
                    lwc1(f21, sp, 0x84);
                    lwc1(f0, sp, 0x94);
                    sub_s(f0, f0, f21);
                    swc1(f0, sp, 0x74);
                    lwc1(f20, sp, 0x88);
                    lwc1(f0, sp, 0x98);
                    sub_s(f0, f0, f20);
                    swc1(f0, sp, 0x78);
                    a0 = addiu(sp, 0x70);
                    a1 = a0;
                    jal(ctx, 0x4398C0u, gen::fn_sub_4C69F0_004c69f0);
                    v0 = 0x43480000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x70);
                    mul_s(f3, f1, f0);
                    swc1(f3, sp, 0x60);
                    lwc1(f0, sp, 0x74);
                    mul_s(f2, f1, f0);
                    swc1(f2, sp, 0x64);
                    lwc1(f0, sp, 0x78);
                    mul_s(f1, f1, f0);
                    swc1(f1, sp, 0x68);
                    lwc1(f0, sp, 0x80);
                    add_s(f0, f3, f0);
                    swc1(f0, sp, 0x60);
                    add_s(f0, f2, f21);
                    swc1(f0, sp, 0x64);
                    add_s(f0, f1, f20);
                    swc1(f0, sp, 0x68);
                    a1 = addiu(sp, 0xE0);
                    ld(v0, sp, 0x60);
                    lwc1(f0, sp, 0x68);
                    sd(v0, sp, 0xE0);
                    swc1(f0, sp, 0xE8);
                    lw(v0, s1, kNpcUnit);
                    lw(a0, v0, 368);
                    lwc1(f12, gp, -32072);  // 0x7CAFA8
                    jal(ctx, 0x439930u, gen::fn_sub_1AFA20_001afa20);
                    v1 = 1;
                    sb(v1, s1, kNpcFightState);
                }
            } else {
                // 0x00439800
                charge(ctx, 4);
                v1 = 4;
                sb(v1, s1, kNpcFightState);
            }
            break;
        case 0x439ACCu:  // table[3]
            // 0x00439acc: state 3: wait for the battle
            charge(ctx, 5);
            lw(a0, s1, kNpcFightTask);
            jal(ctx, 0x439AD0u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x00439ae0
                charge(ctx, 15);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6459);  // &0x87193B
                v0 = addu(v0, v1);
                sb(zero, v0, 0);
                v0 = 4;
                sb(v0, s1, kNpcFightState);
                sb(zero, s1, kNpcHeld);
                lb(v1, s1, kNpcBusy);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00439b1c
                    charge(ctx, 1);
                    sb(zero, s1, kNpcBusy);
                }
                // 0x00439b20
                charge(ctx, 13);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6120);  // &0x8717E8
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x439B40u, gen::fn_datUnitIsGenusDead_002ff790);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00439b54
                    charge(ctx, 7);
                    v0 = 4;
                    sb(v0, s1, kNpcFightState);
                    v0 = 6;
                    sb(v0, s1, kNpcMode);
                    sb(zero, s1, kNpcFollowState);
                    sb(zero, s1, kNpcExploreState);
                    sb(zero, s1, kNpcFightState);
                }
            }
            // 0x00439b70
            charge(ctx, 13);
            lw(v1, s1, kNpcPc);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6120);  // &0x8717E8
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x439B90u, gen::fn_datUnitIsGenusDead_002ff790);
            a1 = 1;
            if (v0 == a1) {
                // 0x00439ba4
                charge(ctx, 18);
                lw(a0, s1, kNpcPc);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 6);
                v1 = 0x870000;
                v1 = addiu(v1, 6459);  // &0x87193B
                v1 = addu(v1, a0);
                sb(zero, v1, 0);
                v1 = 4;
                sb(v1, s1, kNpcFightState);
                v1 = 6;
                sb(v1, s1, kNpcMode);
                sb(zero, s1, kNpcFollowState);
                sb(zero, s1, kNpcExploreState);
                sb(zero, s1, kNpcFightState);
                lb(v1, s1, kNpcBusy);
                if (v1 == a1) {
                    // 0x00439bec
                    charge(ctx, 3);
                    sb(zero, s1, kNpcBusy);
                }
            }
            break;
        case 0x439BF8u:  // table[4]
            // 0x00439bf8: state 4: after the battle
            charge(ctx, 14);
            lw(v1, s1, kNpcPc);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6472);  // &0x871948
            v0 = addu(v0, v1);
            lh(a0, v0, 0);
            jal(ctx, 0x439C18u, gen::fn_sub_16C920_0016c920);
            v1 = v0 & 0xFFFF;
            v0 = 3;
            if (v1 == v0) {
                // 0x00439c30
                charge(ctx, 3);
                lb(a0, s1, kNpcPc);
                jal(ctx, 0x439C34u, gen::fn_sub_4564E0_004564e0);
            }
            // 0x00439c3c
            charge(ctx, 14);
            lw(v1, s1, kNpcPc);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6472);  // &0x871948
            v0 = addu(v0, v1);
            lh(a0, v0, 0);
            jal(ctx, 0x439C5Cu, gen::fn_sub_16C920_0016c920);
            v1 = v0 & 0xFFFF;
            v0 = 4;
            if (v1 != v0) {
                // 0x00439c88
                charge(ctx, 14);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6472);  // &0x871948
                v0 = addu(v0, v1);
                lh(a0, v0, 0);
                jal(ctx, 0x439CA8u, gen::fn_sub_16C920_0016c920);
                a0 = v0 & 0xFFFF;
                v1 = 5;
                if (a0 == v1) {
                    // 0x00439cc0
                    charge(ctx, 3);
                    lb(a0, s1, kNpcPc);
                    jal(ctx, 0x439CC4u, gen::fn_sub_4565D0_004565d0);
                }
            } else {
                // 0x00439c74
                charge(ctx, 5);
                lb(a0, s1, kNpcPc);
                jal(ctx, 0x439C78u, gen::fn_sub_4565D0_004565d0);
            }
            // 0x00439ccc
            charge(ctx, 4);
            lb(v1, s1, kNpcExploring);
            a1 = 1;
            if (v1 == a1) {
                // 0x00439d00
                charge(ctx, 6);
                lb(a0, s1, kNpcPc);
                a1 = 2;
                jal(ctx, 0x439D08u, gen::fn_sub_43C7A0_0043c7a0);
            } else {
                // 0x00439cdc
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00439cec
                    charge(ctx, 5);
                    lb(a0, s1, kNpcPc);
                    jal(ctx, 0x439CF0u, gen::fn_sub_43C7A0_0043c7a0);
                } else {
                    // 0x00439ce4
                    charge(ctx, 2);
                }
            }
            break;
        case 0x439D18u:  // table[5]
            // 0x00439d18: state 5: join shadow kNpcFightEnemy's battle
            charge(ctx, 12);
            lb(v1, s1, kNpcFightEnemy);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, -4704);  // &gFldUnitsEc
            a0 = addu(v0, v1);
            jal(ctx, 0x439D34u, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
            sw(v0, s1, kNpcFightTask);
            if (v0 == 0) {
                // 0x00439dfc
                charge(ctx, 4);
                v1 = 4;
                sb(v1, s1, kNpcFightState);
            } else {
                // 0x00439d48
                charge(ctx, 13);
                v1 = 6;
                sb(v1, s1, kNpcFightState);
                lb(a0, s1, kNpcFightEnemy);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 6);
                v1 = 0x870000;
                v1 = addiu(v1, -4308);  // &0x86EF2C
                v1 = addu(v1, a0);
                lw(a0, v1, 0);
                v1 = 4;
                if (a0 != v1) {
                    // 0x00439dbc
                    charge(ctx, 10);
                    lw(a1, s1, kNpcPc);
                    v1 = sll(a1, 3);
                    v1 = subu(v1, a1);
                    a0 = sll(v1, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6459);  // &0x87193B
                    v1 = addu(v1, a0);
                    lb(v1, v1, 0);
                    if (v1 == 0) {
                        // 0x00439de4
                        charge(ctx, 6);
                        a0 = dsll32(a1, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x439DECu, gen::fn_sub_456580_00456580);
                    }
                } else {
                    // 0x00439d7c
                    charge(ctx, 10);
                    lw(a1, s1, kNpcPc);
                    v1 = sll(a1, 3);
                    v1 = subu(v1, a1);
                    a0 = sll(v1, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6459);  // &0x87193B
                    v1 = addu(v1, a0);
                    lb(v1, v1, 0);
                    if (v1 == 0) {
                        // 0x00439da4
                        charge(ctx, 6);
                        a0 = dsll32(a1, 24);
                        a0 = dsra32(a0, 24);
                        jal(ctx, 0x439DACu, gen::fn_sub_456530_00456530);
                    }
                }
            }
            break;
        case 0x439E0Cu:  // table[6]
            // 0x00439e0c: state 6: wait for the battle
            charge(ctx, 5);
            lw(a0, s1, kNpcFightTask);
            jal(ctx, 0x439E10u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x00439e20
                charge(ctx, 15);
                v0 = 4;
                sb(v0, s1, kNpcFightState);
                sb(zero, s1, kNpcHeld);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6459);  // &0x87193B
                v0 = addu(v0, v1);
                sb(zero, v0, 0);
                lb(v1, s1, kNpcBusy);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00439e5c
                    charge(ctx, 1);
                    sb(zero, s1, kNpcBusy);
                }
                // 0x00439e60
                charge(ctx, 13);
                lw(v1, s1, kNpcPc);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6120);  // &0x8717E8
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x439E80u, gen::fn_datUnitIsGenusDead_002ff790);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00439e94
                    charge(ctx, 7);
                    v0 = 4;
                    sb(v0, s1, kNpcFightState);
                    v0 = 6;
                    sb(v0, s1, kNpcMode);
                    sb(zero, s1, kNpcFollowState);
                    sb(zero, s1, kNpcExploreState);
                    sb(zero, s1, kNpcFightState);
                }
            }
            // 0x00439eb0
            charge(ctx, 13);
            lw(v1, s1, kNpcPc);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6120);  // &0x8717E8
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x439ED0u, gen::fn_datUnitIsGenusDead_002ff790);
            a1 = 1;
            if (v0 == a1) {
                // 0x00439ee4
                charge(ctx, 18);
                lw(a0, s1, kNpcPc);
                v1 = sll(a0, 3);
                v1 = subu(v1, a0);
                a0 = sll(v1, 6);
                v1 = 0x870000;
                v1 = addiu(v1, 6459);  // &0x87193B
                v1 = addu(v1, a0);
                sb(zero, v1, 0);
                v1 = 4;
                sb(v1, s1, kNpcFightState);
                v1 = 6;
                sb(v1, s1, kNpcMode);
                sb(zero, s1, kNpcFollowState);
                sb(zero, s1, kNpcExploreState);
                sb(zero, s1, kNpcFightState);
                lb(v1, s1, kNpcBusy);
                if (v1 == a1) {
                    // 0x00439f2c
                    charge(ctx, 1);
                    sb(zero, s1, kNpcBusy);
                }
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00439f30 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x00439F60 sub_439F60 -- 324 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsShadowTouching] ($a1 pc) the shadow nearest the member (sub_1C6720) within contact range of its model
// (sub_1C6450): 1, or with kNpcAvoidFights set only when that shadow already has a battle task. 0 otherwise.
void sub_439F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00439f60
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = dsll32(a1, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6412);  // &0x87190C
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    lw(s2, v0, 60);
    lw(s0, gp, -19040);  // 0x7CE290
    lw(a0, s2, kNpcUnit);
    lwc1(f12, s0, 20);
    jal(ctx, 0x439FA8u, gen::fn_sub_1C6720_001c6720);
    s1 = v0;
    lb(v0, s2, kNpcAvoidFights);
    if (v0 != 0) {
        // 0x0043a018
        charge(ctx, 2);
        if (s1 == 0) {
        L_0043a084:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0043a020
            charge(ctx, 17);
            lw(v0, s2, kNpcUnit);
            lw(a0, v0, 80);
            jal(ctx, 0x43A028u, gen::fn_sub_318B60_00318b60);
            s2 = v0;
            lw(a0, s1, 80);
            jal(ctx, 0x43A038u, gen::fn_sub_318B60_00318b60);
            a0 = s2;
            a1 = addiu(v0, 48);
            lwc1(f12, s0, 16);
            lwc1(f13, s0, 20);
            jal(ctx, 0x43A050u, gen::fn_sub_1C6450_001c6450);
            v1 = 1;
            if (v0 != v1) {
                goto L_0043a084;
            }
            // 0x0043a064
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x43A068u, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
            if (v0 == 0) {
                goto L_0043a084;
            }
            // 0x0043a078
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x00439fc0
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_0043a084;
        }
        // 0x00439fc8
        charge(ctx, 17);
        lw(v0, s2, kNpcUnit);
        lw(a0, v0, 80);
        jal(ctx, 0x439FD0u, gen::fn_sub_318B60_00318b60);
        s2 = v0;
        lw(a0, s1, 80);
        jal(ctx, 0x439FE0u, gen::fn_sub_318B60_00318b60);
        a0 = s2;
        a1 = addiu(v0, 48);
        lwc1(f12, s0, 16);
        lwc1(f13, s0, 20);
        jal(ctx, 0x439FF8u, gen::fn_sub_1C6450_001c6450);
        v1 = 1;
        if (v0 != v1) {
            goto L_0043a084;
        }
        // 0x0043a00c
        charge(ctx, 3);
        v0 = v1;
    }
    // 0x0043a088 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0043A0B0 sub_43A0B0 -- 236 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsShadowAtHero] ($a1 pc) without kNpcAvoidFights: 1 when the shadow nearest the hero
// (sub_1C6720(gFldUnitsPc)) is within contact range of the member's model.
void sub_43A0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x0043a0b0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = dsll32(a1, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s2 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6412);  // &0x87190C
    v0 = addu(v0, s2);
    lw(v0, v0, 0);
    lw(s3, v0, 60);
    lw(s1, gp, -19040);  // 0x7CE290
    a0 = 0x870000;
    a0 = addiu(a0, 6048);  // &gFldUnitsPc
    lwc1(f12, s1, 20);
    jal(ctx, 0x43A100u, gen::fn_sub_1C6720_001c6720);
    s0 = v0;
    lb(v0, s3, kNpcAvoidFights);
    if (v0 == 0) {
        // 0x0043a118
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_0043a178;
        }
        // 0x0043a120
        charge(ctx, 19);
        v0 = 0x870000;
        v0 = addiu(v0, 6128);  // &0x8717F0
        v0 = addu(v0, s2);
        lw(a0, v0, 0);
        jal(ctx, 0x43A130u, gen::fn_sub_318B60_00318b60);
        s2 = v0;
        lw(a0, s0, 80);
        jal(ctx, 0x43A140u, gen::fn_sub_318B60_00318b60);
        a0 = s2;
        a1 = addiu(v0, 48);
        lwc1(f12, s1, 16);
        lwc1(f13, s1, 20);
        jal(ctx, 0x43A158u, gen::fn_sub_1C6450_001c6450);
        v1 = 1;
        if (v0 != v1) {
            goto L_0043a178;
        }
        // 0x0043a16c
        charge(ctx, 3);
        v0 = v1;
        // 0x0043a17c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0043a178:
    charge(ctx, 1);
    v0 = 0;
    // 0x0043a17c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0043A1A0 sub_43A1A0 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_StartSkirmish] ($a0 pc, $a1 shadow index) for pc != 0: mode 5, kNpcFightState 5, kNpcFightEnemy = shadow,
// kNpcFightLevel = sub_16C470 of the persona. (The enemy contact sub_44DFC0.)
void sub_43A1A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043a1a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = dsll32(a0, 24);
    a2 = dsra32(a2, 24);
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    a0 = sll(v1, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 6412);  // &0x87190C
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    lw(s0, v1, 60);
    if (a2 != 0) {
        // 0x0043a1dc
        charge(ctx, 15);
        v0 = 5;
        sb(v0, s0, kNpcMode);
        sb(v0, s0, kNpcFightState);
        sb(a1, s0, kNpcFightEnemy);
        lw(v1, s0, kNpcPc);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6472);  // &0x871948
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        jal(ctx, 0x43A20Cu, gen::fn_sub_16C470_0016c470);
        sb(v0, s0, kNpcFightLevel);
    }
    // 0x0043a218 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0043A230 sub_43A230 -- 180 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsInBattle] 1 when member $a0's unit is live, its mode is 5 and kNpcFightState is 3 or 6.
void sub_43A230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0043a230
    enter(ctx, 12);  // entry check point + this block's cycles
    a1 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    a0 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6120);  // &0x8717E8
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0043a260
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6132);  // &0x8717F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x0043a278
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x0043a27c
    charge(ctx, 4);
    v1 = sltu(0, a1);
    v0 = 1;
    if (v1 == v0) {
        // 0x0043a28c
        charge(ctx, 9);
        v0 = 0x870000;
        v0 = addiu(v0, 6412);  // &0x87190C
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        lw(a0, v0, 60);
        lb(v1, a0, kNpcMode);
        v0 = 5;
        if (v1 != v0) {
            goto L_0043a2d8;
        }
        // 0x0043a2b0
        charge(ctx, 4);
        lb(v1, a0, kNpcFightState);
        v0 = 3;
        if (v1 != v0) {
            // 0x0043a2c0
            charge(ctx, 3);
            v0 = 6;
            if (v1 != v0) {
                goto L_0043a2d8;
            }
            goto L_0043a2cc;
        }
    L_0043a2cc:
        charge(ctx, 3);
        v0 = 1;
        // 0x0043a2dc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0043a2d8:
    charge(ctx, 1);
    v0 = 0;
    // 0x0043a2dc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0043A2F0 sub_43A2F0 -- 1648 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_RunModeScript] kNpcModeScriptState: 0 -> an ordered mode 3..7 runs the member's script from memory
// (gFldUnitsPc +436 / +440) at once; modes 0..2 (with the camera / event / panel tasks of K_Field_Get) run the
// header script of the mode, hold the other members, pause the shadows (sub_4532D0), the camera, the event and pad
// tasks, the battle tasks, hide the mini-map and two panels; 1 -> when the script task ended, undo all of it (mode 0
// also clears the 0x7CE6CC + 4 (pc - 1) flag). Clears kNpcModeChange.
void sub_43A2F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043a2f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s3, a0, 60);
    lb(a1, s3, kNpcModeScriptState);
    a0 = 2;
    if (a1 != a0) {
        // 0x0043a324
        charge(ctx, 3);
        v1 = 1;
        if (a1 != v1) {
            // 0x0043a330
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x0043a340
                charge(ctx, 3);
                lb(a3, s3, kNpcModeOrder);
                if (a3 != 0) {
                    // 0x0043a34c
                    charge(ctx, 2);
                    if (a3 == v1) {
                        goto L_0043a35c;
                    }
                    // 0x0043a354
                    charge(ctx, 2);
                    if (a3 == a0) {
                        goto L_0043a35c;
                    }
                    // 0x0043a6a4
                    charge(ctx, 28);
                    lw(v1, s3, kNpcPc);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    a0 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6484);  // &0x871954
                    v1 = addu(v0, a0);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6488);  // &0x871958
                    v0 = addu(v0, a0);
                    a0 = 10;
                    lw(a1, v1, 0);
                    lw(a2, v0, 0);
                    jal(ctx, 0x43A6D8u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                    lw(a0, s3, kNpcPc);
                    v1 = sll(a0, 3);
                    v1 = subu(v1, a0);
                    a0 = sll(v1, 6);
                    v1 = 0x870000;
                    v1 = addiu(v1, 6048);  // &gFldUnitsPc
                    a1 = addu(v1, a0);
                    a0 = v0;
                    jal(ctx, 0x43A700u, gen::fn_scrSetUserData_0035c1a0);
                    sb(zero, s3, kNpcModeChange);
                    // 0x0043a938 (the shared epilogue, written out on this path)
                    charge(ctx, 10);
                    ld(ra, sp, 0x60);
                    lq(s5, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x70);
                    return;
                }
            L_0043a35c:
                charge(ctx, 5);
                jal(ctx, 0x43A35Cu, gen::fn_K_Field_Get_001b9120);
                lw(v1, v0, 12);
                if (v1 != 0) {
                    // 0x0043a370
                    charge(ctx, 5);
                    jal(ctx, 0x43A370u, gen::fn_K_Field_Get_001b9120);
                    lw(v1, v0, 36);
                    if (v1 != 0) {
                        // 0x0043a384
                        charge(ctx, 5);
                        jal(ctx, 0x43A384u, gen::fn_K_Field_Get_001b9120);
                        lw(v1, v0, 8);
                        if (v1 != 0) {
                            // 0x0043a398
                            charge(ctx, 3);
                            lw(v0, s3, kNpcScriptTask);
                            if (v0 != 0) {
                                // 0x0043a3a4
                                charge(ctx, 1);
                                sw(zero, s3, kNpcScriptTask);
                            }
                            // 0x0043a3a8
                            charge(ctx, 47);
                            lw(v1, s3, kNpcPc);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6484);  // &0x871954
                            v0 = addu(v0, v1);
                            lb(a2, s3, kNpcModeOrder);
                            a0 = 10;
                            lw(a1, v0, 0);
                            jal(ctx, 0x43A3D0u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                            sw(v0, s3, kNpcScriptTask);
                            lw(a0, s3, kNpcPc);
                            v1 = sll(a0, 3);
                            v1 = subu(v1, a0);
                            a0 = sll(v1, 6);
                            v1 = 0x870000;
                            v1 = addiu(v1, 6048);  // &gFldUnitsPc
                            a1 = addu(v1, a0);
                            a0 = v0;
                            jal(ctx, 0x43A3FCu, gen::fn_scrSetUserData_0035c1a0);
                            lw(v0, s3, kNpcUnit);
                            lw(a0, v0, 368);
                            a1 = 1;
                            jal(ctx, 0x43A410u, gen::fn_sub_1B0260_001b0260);
                            lw(v0, s3, kNpcOwnRes);
                            lw(a0, v0, 296);
                            a1 = 0;
                            jal(ctx, 0x43A424u, gen::fn_sub_318540_00318540);
                            s0 = dsll32(v0, 16);
                            s0 = dsra32(s0, 16);
                            lw(v1, s3, kNpcPc);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6472);  // &0x871948
                            v0 = addu(v0, v1);
                            lhu(a0, v0, 0);
                            jal(ctx, 0x43A454u, gen::fn_sub_1DED40_001ded40);
                            if (s0 == v0) {
                                // 0x0043a464
                                charge(ctx, 19);
                                lw(v1, s3, kNpcPc);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                v1 = sll(v0, 6);
                                v0 = 0x870000;
                                v0 = addiu(v0, 6472);  // &0x871948
                                v0 = addu(v0, v1);
                                lhu(a0, v0, 0);
                                jal(ctx, 0x43A484u, gen::fn_sub_1DDE00_001dde00);
                                a2 = dsll32(v0, 16);
                                a2 = dsra32(a2, 16);
                                lw(v0, s3, kNpcOwnRes);
                                lw(a0, v0, 296);
                                a1 = 0;
                                a3 = 8;
                                t0 = 1;
                                jal(ctx, 0x43A4A8u, gen::fn_sub_3182D0_003182d0);
                            }
                            // 0x0043a4b0
                            charge(ctx, 4);
                            lb(s2, s3, kNpcPc);
                            s4 = 1;
                            for (;;) {
                                // 0x0043a5ac
                                charge(ctx, 3);
                                v0 = slti(s4, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0043a4c0
                                charge(ctx, 10);
                                a0 = 0;
                                v0 = sll(s4, 3);
                                v0 = subu(v0, s4);
                                v1 = sll(v0, 6);
                                v0 = 0x870000;
                                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                v1 = addu(v0, v1);
                                lw(v0, v1, 72);
                                if (v0 != 0) {
                                    // 0x0043a4e8
                                    charge(ctx, 3);
                                    lw(v0, v1, 84);
                                    if (v0 != 0) {
                                        // 0x0043a4f4
                                        charge(ctx, 1);
                                        a0 = 1;
                                    }
                                }
                                // 0x0043a4f8
                                charge(ctx, 4);
                                v0 = sltu(0, a0);
                                a1 = 1;
                                if (v0 == a1) {
                                    // 0x0043a508
                                    charge(ctx, 2);
                                    if (s2 != s4) {
                                        // 0x0043a510
                                        charge(ctx, 26);
                                        v0 = sll(s4, 3);
                                        v0 = subu(v0, s4);
                                        v1 = sll(v0, 6);
                                        v0 = 0x870000;
                                        v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                        s0 = addu(v0, v1);
                                        lw(v0, s0, 364);
                                        lw(s1, v0, 60);
                                        sb(a1, s1, 4629);
                                        lw(v0, s1, 36);
                                        lw(a0, v0, 368);
                                        jal(ctx, 0x43A53Cu, gen::fn_sub_1B0260_001b0260);
                                        s0 = addiu(s0, 424);
                                        lw(v0, s1, 12);
                                        lw(a0, v0, 296);
                                        a1 = 0;
                                        jal(ctx, 0x43A554u, gen::fn_sub_318540_00318540);
                                        s5 = dsll32(v0, 16);
                                        s5 = dsra32(s5, 16);
                                        lhu(a0, s0, 0);
                                        jal(ctx, 0x43A568u, gen::fn_sub_1DED40_001ded40);
                                        if (s5 == v0) {
                                            // 0x0043a578
                                            charge(ctx, 12);
                                            lhu(a0, s0, 0);
                                            jal(ctx, 0x43A57Cu, gen::fn_sub_1DDE00_001dde00);
                                            a2 = dsll32(v0, 16);
                                            a2 = dsra32(a2, 16);
                                            lw(v0, s1, 12);
                                            lw(a0, v0, 296);
                                            a1 = 0;
                                            a3 = 8;
                                            t0 = 1;
                                            jal(ctx, 0x43A5A0u, gen::fn_sub_3182D0_003182d0);
                                        }
                                    }
                                }
                                // 0x0043a5a8
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                            // 0x0043a5b8
                            charge(ctx, 29);
                            a0 = 1;
                            jal(ctx, 0x43A5BCu, gen::fn_sub_4532D0_004532d0);
                            jal(ctx, 0x43A5C4u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, 12);
                            a1 = 1;
                            jal(ctx, 0x43A5D4u, gen::fn_sub_1E1360_001e1360);
                            jal(ctx, 0x43A5DCu, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, 36);
                            a1 = 1;
                            jal(ctx, 0x43A5ECu, gen::fn_sub_1D3810_001d3810);
                            jal(ctx, 0x43A5F4u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, 8);
                            a1 = 1;
                            jal(ctx, 0x43A604u, gen::fn_sub_1CD670_001cd670);
                            a0 = 1;
                            jal(ctx, 0x43A610u, gen::fn_sub_1D8C60_001d8c60);
                            jal(ctx, 0x43A618u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, 24);
                            if (v0 != 0) {
                                // 0x0043a62c
                                charge(ctx, 6);
                                jal(ctx, 0x43A62Cu, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, 24);
                                a1 = 0;
                                jal(ctx, 0x43A63Cu, gen::fn_sub_429E80_00429e80);
                            }
                            // 0x0043a644
                            charge(ctx, 5);
                            jal(ctx, 0x43A644u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, 40);
                            if (v0 != 0) {
                                // 0x0043a658
                                charge(ctx, 6);
                                jal(ctx, 0x43A658u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, 40);
                                a1 = 0;
                                jal(ctx, 0x43A668u, gen::fn_sub_18C0C0_0018c0c0);
                            }
                            // 0x0043a670
                            charge(ctx, 5);
                            jal(ctx, 0x43A670u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, 44);
                            if (v0 != 0) {
                                // 0x0043a684
                                charge(ctx, 8);
                                jal(ctx, 0x43A684u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, 44);
                                a1 = 0;
                                jal(ctx, 0x43A694u, gen::fn_sub_18EB30_0018eb30);
                            }
                            // 0x0043a714
                            charge(ctx, 2);
                            v0 = 1;
                            sb(v0, s3, kNpcModeScriptState);
                            goto L_0043a71c;
                        }
                    }
                }
            } else {
                // 0x0043a338
                charge(ctx, 2);
            }
            // 0x0043a938 (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_0043a71c:
        charge(ctx, 5);
        lw(a0, s3, kNpcScriptTask);
        jal(ctx, 0x43A720u, gen::fn_kwlnTaskExists_00195460);
        if (v0 == 0) {
            // 0x0043a730
            charge(ctx, 3);
            lb(v1, s3, kNpcModeOrder);
            if (v1 == 0) {
                // 0x0043a73c
                charge(ctx, 4);
                lw(a0, s3, kNpcPc);
                v1 = 3;
                if (a0 == v1) {
                    // 0x0043a784
                    charge(ctx, 1);
                    sb(zero, gp, -17948);  // 0x7CE6D4
                } else {
                    // 0x0043a74c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x0043a778
                        charge(ctx, 3);
                        sb(zero, gp, -17952);  // 0x7CE6D0
                    } else {
                        // 0x0043a758
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0043a76c
                            charge(ctx, 3);
                            sb(zero, gp, -17956);  // 0x7CE6CC
                        } else {
                            // 0x0043a764
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0043a788
            charge(ctx, 3);
            lb(a0, s3, kNpcModeOrder);
            if (a0 != 0) {
                // 0x0043a794
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    goto L_0043a7ac;
                }
                // 0x0043a7a0
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_0043a7ac;
                }
                goto L_0043a934;
            }
        L_0043a7ac:
            charge(ctx, 4);
            lb(s0, s3, kNpcPc);
            s1 = 1;
            for (;;) {
                // 0x0043a830
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0043a7bc
                charge(ctx, 10);
                a1 = 0;
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                a0 = addu(v0, v1);
                lw(v0, a0, 72);
                if (v0 != 0) {
                    // 0x0043a7e4
                    charge(ctx, 3);
                    lw(v0, a0, 84);
                    if (v0 != 0) {
                        // 0x0043a7f0
                        charge(ctx, 1);
                        a1 = 1;
                    }
                }
                // 0x0043a7f4
                charge(ctx, 4);
                v1 = sltu(0, a1);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0043a804
                    charge(ctx, 2);
                    if (s0 != s1) {
                        // 0x0043a80c
                        charge(ctx, 8);
                        lw(v0, a0, 364);
                        lw(v0, v0, 60);
                        sb(zero, v0, 4629);
                        lw(v0, v0, 36);
                        lw(a0, v0, 368);
                        a1 = 0;
                        jal(ctx, 0x43A824u, gen::fn_sub_1B0260_001b0260);
                    }
                }
                // 0x0043a82c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0043a83c
            charge(ctx, 34);
            lw(v0, s3, kNpcUnit);
            lw(a0, v0, 368);
            a1 = 0;
            jal(ctx, 0x43A848u, gen::fn_sub_1B0260_001b0260);
            a0 = 0;
            jal(ctx, 0x43A854u, gen::fn_sub_4532D0_004532d0);
            jal(ctx, 0x43A85Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 12);
            a1 = 0;
            jal(ctx, 0x43A86Cu, gen::fn_sub_1E1360_001e1360);
            jal(ctx, 0x43A874u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 36);
            a1 = 0;
            jal(ctx, 0x43A884u, gen::fn_sub_1D3810_001d3810);
            jal(ctx, 0x43A88Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 8);
            a1 = 0;
            jal(ctx, 0x43A89Cu, gen::fn_sub_1CD670_001cd670);
            a0 = 0;
            jal(ctx, 0x43A8A8u, gen::fn_sub_1D8C60_001d8c60);
            jal(ctx, 0x43A8B0u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, 24);
            if (v0 != 0) {
                // 0x0043a8c4
                charge(ctx, 6);
                jal(ctx, 0x43A8C4u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, 24);
                a1 = 1;
                jal(ctx, 0x43A8D4u, gen::fn_sub_429E80_00429e80);
            }
            // 0x0043a8dc
            charge(ctx, 5);
            jal(ctx, 0x43A8DCu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, 40);
            if (v0 != 0) {
                // 0x0043a8f0
                charge(ctx, 6);
                jal(ctx, 0x43A8F0u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, 40);
                a1 = 1;
                jal(ctx, 0x43A900u, gen::fn_sub_18C0C0_0018c0c0);
            }
            // 0x0043a908
            charge(ctx, 5);
            jal(ctx, 0x43A908u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, 44);
            if (v1 != 0) {
                // 0x0043a91c
                charge(ctx, 6);
                jal(ctx, 0x43A91Cu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, 44);
                a1 = 1;
                jal(ctx, 0x43A92Cu, gen::fn_sub_18EB30_0018eb30);
            }
        L_0043a934:
            charge(ctx, 1);
            sb(zero, s3, kNpcModeChange);
        }
    }
    // 0x0043a938 (the shared epilogue, written out on this path)
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

// 0x0043A960 sub_43A960 -- 104 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_StepSkillUse] kNpcSkillState 0 -> 1 -> 2; at 2 the use ends: kNpcSkillUse = 0, kNpcSkillKind = -1,
// kNpcSkillTarget = -1.
void sub_43A960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0043a960
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    lb(a0, a1, kNpcSkillState);
    v1 = 2;
    if (a0 == v1) {
        // 0x0043a9b0
        charge(ctx, 4);
        sb(zero, a1, kNpcSkillUse);
        v1 = si(-1);
        sb(v1, a1, kNpcSkillKind);
        sh(v1, a1, kNpcSkillTarget);
    } else {
        // 0x0043a974
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x0043a9a0
            charge(ctx, 4);
            v1 = addiu(a0, 1);
            sb(v1, a1, kNpcSkillState);
        } else {
            // 0x0043a980
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0043a990
                charge(ctx, 4);
                v1 = addiu(a0, 1);
                sb(v1, a1, kNpcSkillState);
            } else {
                // 0x0043a988
                charge(ctx, 2);
            }
        }
    }
    // 0x0043a9c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0043A9D0 sub_43A9D0 -- 4016 bytes; frame 0x1C0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_HealWithSkills] ($a0 caster pc, $a1 target pc, $a2 1 = count the hurt members) the caster's skills
// 0xC0..0xC5 (inf: the healing skills): 3 none known, 4 no SP for any, 2 the target is down / out of reach / not
// hurt; else repeatedly the skill with the best heal-per-cost rating is cast (SP paid, sub_17B860; the party
// versions also on every member in reach) until the target is full: 1, 5 when a party-wide skill was used, 0 when
// nothing could be cast. Called by the COMM handler sub_424B60 (two jump tables 0x7BC440 / 0x7BC420 of six identical
// cases).
void sub_43A9D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0043a9d0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
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
    swc1(f20, sp, 0x0);
    s4 = a0;
    s1 = a1;
    sb(a2, sp, 0x18F);
    s7 = si(-1);
    s6 = 0;
    v0 = 1;
    sb(v0, sp, 0x150);
    fp = 0;
    sb(zero, sp, 0x140);
    v1 = dsll32(s4, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s2 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, s2);
    lhu(a0, v0, 0);
    jal(ctx, 0x43AA48u, gen::fn_sub_173380_00173380);
    s5 = v0;
    s0 = 0;
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s2 = addu(v0, s2);
    for (;;) {
        // 0x0043aacc
        charge(ctx, 3);
        v0 = slti(s0, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043aa6c
        charge(ctx, 5);
        v0 = sll(s0, 1);
        v0 = addu(s5, v0);
        lhu(a1, v0, 0);
        if (a1 != 0) {
            // 0x0043aa80
            charge(ctx, 4);
            v0 = addiu(a1, -192);
            at = sltiu(v0, 6);
            if (at != 0) {
                // 0x0043aa90
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -15296);  // &0x7BC440
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x43AAACu:  // table[0, 1, 2, 3, 4, 5]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                // 0x0043aaac
                charge(ctx, 5);
                lh(a0, s2, 424);
                jal(ctx, 0x43AAB0u, gen::fn_sub_17B660_0017b660);
                if (v0 == 0) {
                    // 0x0043aac0
                    charge(ctx, 1);
                    fp = 0x1;
                }
                // 0x0043aac4
                charge(ctx, 1);
                s6 = 1;
            }
        }
        // 0x0043aac8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0043aad8
    charge(ctx, 4);
    v0 = dsll32(s6, 24);
    v0 = dsra32(v0, 24);
    if (v0 != 0) {
        // 0x0043aaf4
        charge(ctx, 4);
        v0 = dsll32(fp, 24);
        v0 = dsra32(v0, 24);
        if (v0 != 0) {
            // 0x0043ab10
            charge(ctx, 7);
            a0 = s4;
            jal(ctx, 0x43AB14u, gen::fn_sub_435440_00435440);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (v0 != 0) {
                // 0x0043ab38
                charge(ctx, 15);
                v0 = dsll32(s1, 24);
                v0 = dsra32(v0, 24);
                sw(v0, sp, 0x120);
                v1 = sll(v0, 3);
                v0 = subu(v1, v0);
                s0 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6120);  // &0x8717E8
                s6 = addu(v0, s0);
                lw(a0, s6, 0);
                jal(ctx, 0x43AB60u, gen::fn_datUnitIsGenusDead_002ff790);
                v1 = 1;
                if (v0 != v1) {
                    // 0x0043ab80
                    charge(ctx, 4);
                    lw(v0, s6, 0);
                    v0 = sltu(0, v0);
                    if (v0 != 0) {
                        // 0x0043ab90
                        charge(ctx, 5);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6132);  // &0x8717F4
                        v0 = addu(v0, s0);
                        lw(v0, v0, 0);
                        v0 = sltu(0, v0);
                    }
                    // 0x0043aba4
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x0043abac
                        charge(ctx, 3);
                        lw(v0, sp, 0x120);
                        if (v0 != 0) {
                            // 0x0043ac48
                            charge(ctx, 27);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6472);  // &0x871948
                            v0 = addu(v0, s0);
                            lh(a0, v0, 0);
                            jal(ctx, 0x43AC58u, gen::fn_sub_16C5F0_0016c5f0);
                            v1 = v0 & 0xFFFF;
                            v0 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v1 = sll(v0, 2);
                            v0 = 100;
                            div(v1, v0);
                            mflo(v0);
                            s6 = dsll32(v0, 16);
                            s6 = dsra32(s6, 16);
                            a0 = s1;
                            jal(ctx, 0x43AC90u, gen::fn_sub_43C910_0043c910);
                            v1 = v0 & 0xFFFF;
                            v0 = dsll32(s6, 16);
                            v0 = dsra32(v0, 16);
                            v1 = slt(v1, v0);
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_0043ace8;
                            }
                            // 0x0043acb4
                            charge(ctx, 11);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6048);  // &gFldUnitsPc
                            a1 = addu(v0, s0);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s2;
                            jal(ctx, 0x43ACCCu, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_0043ace8;
                            }
                            // 0x0043ace0
                            charge(ctx, 2);
                        } else {
                            // 0x0043abb8
                            charge(ctx, 24);
                            a0 = 1;
                            jal(ctx, 0x43ABBCu, gen::fn_sub_16C5F0_0016c5f0);
                            v1 = v0 & 0xFFFF;
                            v0 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v1 = sll(v0, 2);
                            v0 = 100;
                            div(v1, v0);
                            mflo(v0);
                            s0 = dsll32(v0, 16);
                            s0 = dsra32(s0, 16);
                            a0 = 1;
                            jal(ctx, 0x43ABF4u, gen::fn_sub_16C4F0_0016c4f0);
                            v1 = v0 & 0xFFFF;
                            v0 = dsll32(s0, 16);
                            v0 = dsra32(v0, 16);
                            v1 = slt(v1, v0);
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_0043ace8;
                            }
                            // 0x0043ac18
                            charge(ctx, 10);
                            v0 = 0x43FA0000;
                            mtc1(v0, f12);
                            a0 = s2;
                            a1 = 0x870000;
                            a1 = addiu(a1, 6048);  // &gFldUnitsPc
                            jal(ctx, 0x43AC2Cu, gen::fn_sub_1C7160_001c7160);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_0043ace8;
                            }
                            // 0x0043ac40
                            charge(ctx, 2);
                        }
                        goto L_0043acec;
                    }
                L_0043ace8:
                    charge(ctx, 1);
                    v1 = 0;
                } else {
                    // 0x0043ab74
                    charge(ctx, 3);
                    v1 = 0;
                }
            L_0043acec:
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0043ad00
                    charge(ctx, 5);
                    lb(v0, sp, 0x18F);
                    v1 = v0;
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0043ad14
                        charge(ctx, 4);
                        a0 = s4;
                        jal(ctx, 0x43AD18u, gen::fn_sub_435440_00435440);
                        sb(v0, sp, 0x150);
                    }
                    // 0x0043ad24
                    charge(ctx, 3);
                    lw(v0, sp, 0x120);
                    if (v0 != 0) {
                        // 0x0043adb4
                        charge(ctx, 39);
                        v1 = dsll32(s1, 24);
                        v1 = dsra32(v1, 24);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, 6472);  // &0x871948
                        s0 = addu(v0, v1);
                        lh(a0, s0, 0);
                        jal(ctx, 0x43ADD8u, gen::fn_sub_16C5F0_0016c5f0);
                        s4 = v0 & 0xFFFF;
                        a0 = s1;
                        jal(ctx, 0x43ADE8u, gen::fn_sub_43C910_0043c910);
                        v0 = v0 & 0xFFFF;
                        v0 = subu(s4, v0);
                        sh(v0, sp, 0x170);
                        lh(a0, s0, 0);
                        jal(ctx, 0x43AE00u, gen::fn_sub_16C4F0_0016c4f0);
                        fp = dsll32(v0, 16);
                        fp = dsra32(fp, 16);
                        lh(a0, s0, 0);
                        jal(ctx, 0x43AE14u, gen::fn_sub_16C5F0_0016c5f0);
                        v1 = v0 & 0xFFFF;
                        v0 = sll(v1, 2);
                        v1 = addu(v0, v1);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v1 = sll(v0, 2);
                        v0 = 100;
                        div(v1, v0);
                        mflo(v0);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        lh(v0, s0, 0);
                        sh(v0, sp, 0x160);
                    } else {
                        // 0x0043ad30
                        charge(ctx, 33);
                        a0 = 1;
                        jal(ctx, 0x43AD34u, gen::fn_sub_16C5F0_0016c5f0);
                        s0 = v0 & 0xFFFF;
                        a0 = 1;
                        jal(ctx, 0x43AD44u, gen::fn_sub_16C4F0_0016c4f0);
                        v0 = v0 & 0xFFFF;
                        v0 = subu(s0, v0);
                        sh(v0, sp, 0x170);
                        a0 = 1;
                        jal(ctx, 0x43AD5Cu, gen::fn_sub_16C4F0_0016c4f0);
                        fp = dsll32(v0, 16);
                        fp = dsra32(fp, 16);
                        a0 = 1;
                        jal(ctx, 0x43AD70u, gen::fn_sub_16C5F0_0016c5f0);
                        v1 = v0 & 0xFFFF;
                        v0 = sll(v1, 2);
                        v1 = addu(v0, v1);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v1 = sll(v0, 2);
                        v0 = 100;
                        div(v1, v0);
                        mflo(v0);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 1;
                        sh(v0, sp, 0x160);
                    }
                    // 0x0043ae50
                    charge(ctx, 6);
                    v0 = dsll32(v1, 16);
                    v0 = dsra32(v0, 16);
                    sq(v0, sp, 0x110);
                    lb(v0, sp, 0x150);
                    // daddu v0: a 64-bit move to itself (no effect)
                    sw(v0, sp, 0x130);
                    for (;;) {
                        // 0x0043ae68
                        charge(ctx, 11);
                        v1 = dsll32(fp, 16);
                        v1 = dsra32(v1, 16);
                        lq(v0, sp, 0x110);
                        v0 = subu(v0, v1);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        s4 = si(-1);
                        s1 = 0;
                        s6 = subu(v0, v1);
                        for (;;) {
                            // 0x0043b6fc
                            charge(ctx, 3);
                            v0 = slti(s1, 8);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0043ae94
                            charge(ctx, 5);
                            v0 = sll(s1, 1);
                            s0 = addu(s5, v0);
                            lhu(a1, s0, 0);
                            if (a1 != 0) {
                                // 0x0043aea8
                                charge(ctx, 4);
                                v0 = addiu(a1, -192);
                                at = sltiu(v0, 6);
                                if (at != 0) {
                                    // 0x0043aeb8
                                    charge(ctx, 7);
                                    v1 = 0x7C0000;
                                    v1 = addiu(v1, -15328);  // &0x7BC420
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x43AED4u:  // table[0]
                                        // 0x0043aed4
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43AED8u, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043aee8
                                            charge(ctx, 22);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0x100);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43AF10u, gen::fn_sub_17BE10_0017be10);
                                            lwc1(f0, sp, 0x1BC);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x190);
                                            a0 = 1;
                                            lq(v0, sp, 0x100);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43AF30u, gen::fn_sub_17B5B0_0017b5b0);
                                            if (i64(v0) < 0) {
                                                // 0x0043af54
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043af40
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043af70
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x190);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043afa0
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043afd8
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b008
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b014
                                                    charge(ctx, 5);
                                                    mov_s(f20, f0);
                                                    s4 = 0;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043aff4
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 0;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    case 0x43B028u:  // table[1]
                                        // 0x0043b028
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43B02Cu, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043b03c
                                            charge(ctx, 22);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0xF0);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43B064u, gen::fn_sub_17BE10_0017be10);
                                            lwc1(f0, sp, 0x1BC);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x194);
                                            a0 = 1;
                                            lq(v0, sp, 0xF0);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43B084u, gen::fn_sub_17B5B0_0017b5b0);
                                            if (i64(v0) < 0) {
                                                // 0x0043b0a8
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043b094
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043b0c4
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x194);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043b0f4
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043b12c
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b15c
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b168
                                                    charge(ctx, 5);
                                                    mov_s(f20, f0);
                                                    s4 = 1;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043b148
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 1;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    case 0x43B17Cu:  // table[2]
                                        // 0x0043b17c
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43B180u, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043b190
                                            charge(ctx, 24);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0xE0);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43B1B8u, gen::fn_sub_17BE10_0017be10);
                                            lh(v0, sp, 0x170);
                                            mtc1(v0, f0);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x198);
                                            a0 = 1;
                                            lq(v0, sp, 0xE0);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43B1E0u, gen::fn_sub_17B5B0_0017b5b0);
                                            if (i64(v0) < 0) {
                                                // 0x0043b204
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043b1f0
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043b220
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x198);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043b250
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043b288
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b2b8
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b2c4
                                                    charge(ctx, 5);
                                                    mov_s(f20, f0);
                                                    s4 = 2;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043b2a4
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 2;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    case 0x43B2D8u:  // table[3]
                                        // 0x0043b2d8
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43B2DCu, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043b2ec
                                            charge(ctx, 25);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0xD0);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43B314u, gen::fn_sub_17BE10_0017be10);
                                            lwc1(f0, sp, 0x1BC);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x19C);
                                            a0 = 1;
                                            lq(v0, sp, 0xD0);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43B334u, gen::fn_sub_17B5B0_0017b5b0);
                                            lw(v1, sp, 0x130);
                                            divu(v0, v1);
                                            mflo(v0);
                                            if (i64(v0) < 0) {
                                                // 0x0043b364
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043b350
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043b380
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x19C);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043b3b0
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043b3e8
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b418
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b424
                                                    charge(ctx, 5);
                                                    mov_s(f20, f0);
                                                    s4 = 3;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043b404
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 3;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    case 0x43B438u:  // table[4]
                                        // 0x0043b438
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43B43Cu, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043b44c
                                            charge(ctx, 25);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0xC0);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43B474u, gen::fn_sub_17BE10_0017be10);
                                            lwc1(f0, sp, 0x1BC);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x1A0);
                                            a0 = 1;
                                            lq(v0, sp, 0xC0);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43B494u, gen::fn_sub_17B5B0_0017b5b0);
                                            lw(v1, sp, 0x130);
                                            divu(v0, v1);
                                            mflo(v0);
                                            if (i64(v0) < 0) {
                                                // 0x0043b4c4
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043b4b0
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043b4e0
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x1A0);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043b510
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043b548
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b578
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b584
                                                    charge(ctx, 5);
                                                    mov_s(f20, f0);
                                                    s4 = 4;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043b564
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 4;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    case 0x43B598u:  // table[5]
                                        // 0x0043b598
                                        charge(ctx, 5);
                                        lh(a0, s2, 424);
                                        jal(ctx, 0x43B59Cu, gen::fn_sub_17B660_0017b660);
                                        if (v0 == 0) {
                                            // 0x0043b5ac
                                            charge(ctx, 27);
                                            v0 = sll(s1, 1);
                                            v0 = addu(s5, v0);
                                            sq(v0, sp, 0xB0);
                                            a0 = 1;
                                            a1 = a0;
                                            lhu(a2, v0, 0);
                                            a3 = 0;
                                            t0 = addiu(sp, 0x1BC);
                                            t1 = addiu(sp, 0x1B8);
                                            t2 = addiu(sp, 0x1B4);
                                            jal(ctx, 0x43B5D4u, gen::fn_sub_17BE10_0017be10);
                                            lh(v0, sp, 0x170);
                                            mtc1(v0, f0);
                                            cvt_s_w(f0, f0);
                                            swc1(f0, sp, 0x1A4);
                                            a0 = 1;
                                            lq(v0, sp, 0xB0);
                                            lhu(a1, v0, 0);
                                            jal(ctx, 0x43B5FCu, gen::fn_sub_17B5B0_0017b5b0);
                                            lw(v1, sp, 0x130);
                                            divu(v0, v1);
                                            mflo(v0);
                                            if (i64(v0) < 0) {
                                                // 0x0043b62c
                                                charge(ctx, 7);
                                                v1 = srl(v0, 1);
                                                v0 = v0 & 0x1;
                                                v1 = v1 | v0;
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                add_s(f3, f3, f3);
                                            } else {
                                                // 0x0043b618
                                                charge(ctx, 5);
                                                mtc1(v0, f0);
                                                cvt_s_w(f3, f0);
                                            }
                                            // 0x0043b648
                                            charge(ctx, 12);
                                            mtc1(s6, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, sp, 0x1A4);
                                            div_s(f2, f1, f0);
                                            mtc1(zero, f1);
                                            v0 = 0x3F800000;
                                            mtc1(v0, f0);
                                            c_lt_s(f2, f0);
                                            if (cond(ctx)) {
                                                // 0x0043b678
                                                charge(ctx, 14);
                                                v0 = 0x41200000;
                                                mtc1(v0, f1);
                                                sub_s(f0, f0, f2);
                                                mul_s(f0, f1, f0);
                                                cvt_w_s(f0, f0);
                                                mfc1(v0, f0);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                mtc1(v0, f0);
                                                cvt_s_w(f0, f0);
                                                div_s(f1, f0, f1);
                                            }
                                            // 0x0043b6b0
                                            charge(ctx, 7);
                                            mula_s(f1, f3);
                                            madd_s(f0, f3, f2);
                                            v1 = dsll32(s4, 16);
                                            v1 = dsra32(v1, 16);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x0043b6e0
                                                charge(ctx, 3);
                                                c_le_s(f20, f0);
                                                if (!cond(ctx)) {
                                                    // 0x0043b6ec
                                                    charge(ctx, 3);
                                                    mov_s(f20, f0);
                                                    s4 = 5;
                                                    lh(s3, s0, 0);
                                                }
                                            } else {
                                                // 0x0043b6cc
                                                charge(ctx, 5);
                                                mov_s(f20, f0);
                                                s4 = 5;
                                                lh(s3, s0, 0);
                                            }
                                        }
                                        break;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                            }
                            // 0x0043b6f8
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x0043b708
                        charge(ctx, 5);
                        s0 = dsll32(s4, 16);
                        s0 = dsra32(s0, 16);
                        v0 = si(-1);
                        if (s0 != v0) {
                            // 0x0043b71c
                            charge(ctx, 27);
                            v0 = sll(s0, 2);
                            v0 = addu(v0, sp);
                            lwc1(f1, v0, 400);
                            mtc1(fp, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                            fp = dsll32(v0, 16);
                            fp = dsra32(fp, 16);
                            s4 = s3 & 0xFFFF;
                            lh(a0, s2, 424);
                            lh(a1, sp, 0x160);
                            a2 = s4;
                            a3 = 0;
                            jal(ctx, 0x43B760u, gen::fn_sub_17B860_0017b860);
                            lh(a0, s2, 424);
                            a1 = s4;
                            jal(ctx, 0x43B770u, gen::fn_sub_17B500_0017b500);
                            v1 = v0 & 0xFFFF;
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x0043b7c8
                                charge(ctx, 3);
                                v0 = 2;
                                if (v1 == v0) {
                                    // 0x0043b7d4
                                    charge(ctx, 14);
                                    lh(a0, s2, 424);
                                    jal(ctx, 0x43B7D8u, gen::fn_sub_16C570_0016c570);
                                    s1 = v0 & 0xFFFF;
                                    lh(a0, s2, 424);
                                    a1 = s4;
                                    jal(ctx, 0x43B7ECu, gen::fn_sub_17B5B0_0017b5b0);
                                    v0 = subu(s1, v0);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    lh(a0, s2, 424);
                                    jal(ctx, 0x43B804u, gen::fn_sub_16CF90_0016cf90);
                                }
                            } else {
                                // 0x0043b788
                                charge(ctx, 16);
                                lh(a0, s2, 424);
                                jal(ctx, 0x43B78Cu, gen::fn_sub_16C4F0_0016c4f0);
                                s1 = v0 & 0xFFFF;
                                lh(a0, s2, 424);
                                a1 = s4;
                                jal(ctx, 0x43B7A0u, gen::fn_sub_17B5B0_0017b5b0);
                                v0 = subu(s1, v0);
                                a1 = dsll32(v0, 16);
                                a1 = dsra32(a1, 16);
                                lh(a0, s2, 424);
                                jal(ctx, 0x43B7B8u, gen::fn_sub_16CF40_0016cf40);
                            }
                            // 0x0043b80c
                            charge(ctx, 3);
                            v0 = 5;
                            if (s0 != v0) {
                                // 0x0043b818
                                charge(ctx, 3);
                                v0 = 4;
                                if (s0 == v0) {
                                    goto L_0043b838;
                                }
                                // 0x0043b824
                                charge(ctx, 3);
                                v0 = 3;
                                if (s0 == v0) {
                                    goto L_0043b838;
                                }
                                // 0x0043b830
                                charge(ctx, 2);
                                goto L_0043b8f0;
                            }
                        L_0043b838:
                            charge(ctx, 4);
                            s1 = 0;
                            s6 = s4 & 0xFFFF;
                            for (;;) {
                                // 0x0043b8dc
                                charge(ctx, 3);
                                v0 = slti(s1, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0043b848
                                charge(ctx, 3);
                                lw(v0, sp, 0x120);
                                if (s1 != v0) {
                                    // 0x0043b854
                                    charge(ctx, 10);
                                    a0 = 0;
                                    v0 = sll(s1, 3);
                                    v0 = subu(v0, s1);
                                    v1 = sll(v0, 6);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                    s4 = addu(v0, v1);
                                    lw(v0, s4, 72);
                                    if (v0 != 0) {
                                        // 0x0043b87c
                                        charge(ctx, 3);
                                        lw(v0, s4, 84);
                                        if (v0 != 0) {
                                            // 0x0043b888
                                            charge(ctx, 1);
                                            a0 = 1;
                                        }
                                    }
                                    // 0x0043b88c
                                    charge(ctx, 4);
                                    v1 = sltu(0, a0);
                                    v0 = 1;
                                    if (v1 == v0) {
                                        // 0x0043b89c
                                        charge(ctx, 9);
                                        v0 = 0x43FA0000;
                                        mtc1(v0, f12);
                                        a0 = s2;
                                        a1 = s4;
                                        jal(ctx, 0x43B8ACu, gen::fn_sub_1C7160_001c7160);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            // 0x0043b8c0
                                            charge(ctx, 6);
                                            lh(a0, s2, 424);
                                            lh(a1, s4, 424);
                                            a2 = s6;
                                            a3 = 0;
                                            jal(ctx, 0x43B8D0u, gen::fn_sub_17B860_0017b860);
                                        }
                                    }
                                }
                                // 0x0043b8d8
                                charge(ctx, 1);
                                s1 = addiu(s1, 1);
                            }
                            // 0x0043b8e8
                            charge(ctx, 2);
                            v0 = 1;
                            sb(v0, sp, 0x140);
                        L_0043b8f0:
                            charge(ctx, 7);
                            s7 = 1;
                            v1 = dsll32(fp, 16);
                            v1 = dsra32(v1, 16);
                            lq(v0, sp, 0x110);
                            at = slt(v1, v0);
                            if (at != 0) {
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x0043b90c
                    charge(ctx, 3);
                    v0 = si(-1);
                    if (s0 == v0) {
                        // 0x0043b918
                        charge(ctx, 1);
                        s7 = 0;
                    }
                    // 0x0043b91c
                    charge(ctx, 5);
                    v0 = dsll32(s7, 16);
                    v0 = dsra32(v0, 16);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x0043b930
                        charge(ctx, 4);
                        lb(v0, sp, 0x140);
                        // daddu v0: a 64-bit move to itself (no effect)
                        if (v0 == v1) {
                            // 0x0043b940
                            charge(ctx, 1);
                            s7 = 5;
                        }
                    }
                    // 0x0043b944
                    charge(ctx, 1);
                    v0 = s7;
                } else {
                    // 0x0043acf4
                    charge(ctx, 3);
                    v0 = 2;
                }
            } else {
                // 0x0043ab2c
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x0043ab04
            charge(ctx, 3);
            v0 = 4;
        }
    } else {
        // 0x0043aae8
        charge(ctx, 3);
        v0 = 3;
    }
    // 0x0043b948 (the shared epilogue, written out on this path)
    charge(ctx, 14);
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
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1C0);
}

// 0x0043B980 sub_43B980 -- 660 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_PickCureSkill] ($a0 caster, $a1 target pc) over the caster's 8 skills: 202 when the target's status is
// exactly 0x80, or with more than one ailment (sub_43BC20) and bit 0x80; 203 for any ailment (returned at once when
// the target has two or more); the skill is cast through sub_17BE10. -1 when none.
void sub_43B980(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043b980
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a1;
    s3 = si(-1);
    v1 = dsll32(s5, 24);
    v1 = dsra32(v1, 24);
    if (v1 != 0) {
        // 0x0043b9cc
        charge(ctx, 7);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6472);  // &0x871948
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0043b9c0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0043b9e8
    charge(ctx, 20);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s0 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    s7 = addu(v0, s0);
    lhu(a0, s7, 0);
    jal(ctx, 0x43BA14u, gen::fn_sub_173380_00173380);
    s6 = v0;
    s4 = 0;
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s1 = addu(v0, s0);
    for (;;) {
        // 0x0043bbd4
        charge(ctx, 3);
        v0 = slti(s4, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043ba38
        charge(ctx, 5);
        v0 = sll(s4, 1);
        s0 = addu(s6, v0);
        lhu(v1, s0, 0);
        if (v1 != 0) {
            // 0x0043ba4c
            charge(ctx, 3);
            v0 = 202;
            if (v1 != v0) {
                // 0x0043bb44
                charge(ctx, 3);
                v0 = 203;
                if (v1 != v0) {
                    goto L_0043bbd0;
                }
                // 0x0043bb50
                charge(ctx, 5);
                a0 = s2;
                jal(ctx, 0x43BB54u, gen::fn_sub_16C970_0016c970);
                if (v0 == 0) {
                    goto L_0043bbd0;
                }
                // 0x0043bb64
                charge(ctx, 6);
                lh(a0, s1, 424);
                lhu(a1, s0, 0);
                jal(ctx, 0x43BB6Cu, gen::fn_sub_17B660_0017b660);
                if (v0 != 0) {
                    goto L_0043bbd0;
                }
                // 0x0043bb7c
                charge(ctx, 17);
                lh(a0, s1, 424);
                a1 = s2;
                lhu(a2, s0, 0);
                a3 = 0;
                t0 = addiu(sp, 0x9C);
                t1 = addiu(sp, 0x98);
                t2 = addiu(sp, 0x94);
                jal(ctx, 0x43BB98u, gen::fn_sub_17BE10_0017be10);
                a0 = s5;
                jal(ctx, 0x43BBA4u, gen::fn_sub_43BC20_0043bc20);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                at = slti(v0, 2);
                if (at == 0) {
                    goto L_0043bbc0_17;
                }
                // 0x0043bbcc
                charge(ctx, 1);
                lh(s3, s0, 0);
                goto L_0043bbd0;
            }
            // 0x0043ba58
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x43BA5Cu, gen::fn_sub_16C970_0016c970);
            v1 = 128;
            if (v0 == v1) {
                // 0x0043ba70
                charge(ctx, 6);
                lh(a0, s1, 424);
                lhu(a1, s0, 0);
                jal(ctx, 0x43BA78u, gen::fn_sub_17B660_0017b660);
                if (v0 != 0) {
                    goto L_0043bac0;
                }
                goto L_0043ba88_8;
            }
        L_0043bac0:
            charge(ctx, 7);
            a0 = s5;
            jal(ctx, 0x43BAC4u, gen::fn_sub_43BC20_0043bc20);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x0043badc
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x43BAE0u, gen::fn_sub_16C970_0016c970);
                v0 = v0 & 0x80;
                if (v0 != 0) {
                    // 0x0043baf4
                    charge(ctx, 6);
                    lh(a0, s1, 424);
                    lhu(a1, s0, 0);
                    jal(ctx, 0x43BAFCu, gen::fn_sub_17B660_0017b660);
                    if (v0 == 0) {
                        // 0x0043bb0c
                        charge(ctx, 14);
                        v0 = sll(s4, 1);
                        s0 = addu(s6, v0);
                        lh(a0, s1, 424);
                        a1 = s2;
                        lhu(a2, s0, 0);
                        a3 = 0;
                        t0 = addiu(sp, 0x9C);
                        t1 = addiu(sp, 0x98);
                        t2 = addiu(sp, 0x94);
                        jal(ctx, 0x43BB30u, gen::fn_sub_17BE10_0017be10);
                        lh(s3, s0, 0);
                    }
                }
            }
            goto L_0043bbd0;
        }
    L_0043bbd0:
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x0043bbe0
    charge(ctx, 1);
    v0 = s3;
    // 0x0043bbe4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
    return;
L_0043ba88_8:
    charge(ctx, 14);
    v0 = sll(s4, 1);
    s0 = addu(s6, v0);
    lh(a0, s7, 0);
    a1 = s2;
    lhu(a2, s0, 0);
    a3 = 0;
    t0 = addiu(sp, 0x9C);
    t1 = addiu(sp, 0x98);
    t2 = addiu(sp, 0x94);
    jal(ctx, 0x43BAACu, gen::fn_sub_17BE10_0017be10);
    lh(v0, s0, 0);
    // 0x0043bbe4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
    return;
L_0043bbc0_17:
    charge(ctx, 3);
    lh(v0, s0, 0);
    // 0x0043bbe4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
}

// 0x0043BC20 sub_43BC20 -- 376 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CountAilments] Counts the bits 0x01, 0x02, 0x04, 0x08, 0x20, 0x40, 0x80 of sub_16C970 (the status) of
// member $a0 (0 = the hero); bit 0x10 is read and ignored, as the original.
void sub_43BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043bc20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    if (v1 != 0) {
        // 0x0043bc50
        charge(ctx, 7);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6472);  // &0x871948
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0043bc44
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0043bc6c
    charge(ctx, 8);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    a0 = s0;
    jal(ctx, 0x43BC78u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0043bc8c
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bc98
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x43BC9Cu, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x0043bcb0
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bcbc
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x43BCC0u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0043bcd4
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bce0
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x43BCE4u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x0043bcf8
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bd04
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x43BD08u, gen::fn_sub_16C970_0016c970);
    a0 = s0;
    jal(ctx, 0x43BD14u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x0043bd28
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bd34
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x43BD38u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x0043bd4c
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bd58
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x43BD5Cu, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x0043bd70
        charge(ctx, 3);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x0043bd7c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0043BDA0 sub_43BDA0 -- 432 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_PickReviveSkill] ($a0 caster, $a1 target) skill 205 (cast and returned at once) or 204 (kept unless 205
// follows), each cast through sub_17BE10 when usable (sub_17B660 == 0). (Inf: the revive skills.)
void sub_43BDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043bda0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    s4 = si(-1);
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    s3 = addu(v0, s1);
    lhu(a0, s3, 0);
    jal(ctx, 0x43BDF4u, gen::fn_sub_173380_00173380);
    s2 = v0;
    s5 = 0;
    a0 = 0x870000;
    a0 = addiu(a0, 6048);  // &gFldUnitsPc
    s1 = addu(a0, s1);
    v1 = dsll32(s0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    s6 = sll(v0, 6);
    s7 = addu(a0, s6);
    for (;;) {
        // 0x0043bf10
        charge(ctx, 3);
        v0 = slti(s5, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043be30
        charge(ctx, 5);
        v0 = sll(s5, 1);
        s0 = addu(s2, v0);
        lhu(a1, s0, 0);
        if (a1 != 0) {
            // 0x0043be44
            charge(ctx, 3);
            v0 = 204;
            if (a1 != v0) {
                // 0x0043bea8
                charge(ctx, 3);
                v0 = 205;
                if (a1 != v0) {
                    goto L_0043bf0c;
                }
                // 0x0043beb4
                charge(ctx, 5);
                lh(a0, s1, 424);
                jal(ctx, 0x43BEB8u, gen::fn_sub_17B660_0017b660);
                if (v0 != 0) {
                    goto L_0043bf0c;
                }
                goto L_0043bec8_8;
            }
            // 0x0043be50
            charge(ctx, 5);
            lh(a0, s1, 424);
            jal(ctx, 0x43BE54u, gen::fn_sub_17B660_0017b660);
            if (v0 == 0) {
                // 0x0043be64
                charge(ctx, 14);
                lh(a0, s1, 424);
                lh(a1, s7, 424);
                lhu(a2, s0, 0);
                a3 = 0;
                t0 = addiu(sp, 0x9C);
                t1 = addiu(sp, 0x98);
                t2 = addiu(sp, 0x94);
                jal(ctx, 0x43BE80u, gen::fn_sub_17BE10_0017be10);
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                v0 = 205;
                if (v1 != v0) {
                    // 0x0043be9c
                    charge(ctx, 3);
                    lh(s4, s0, 0);
                }
            }
            goto L_0043bf0c;
        }
    L_0043bf0c:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0043bf1c
    charge(ctx, 1);
    v0 = s4;
    // 0x0043bf20 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
    return;
L_0043bec8_8:
    charge(ctx, 17);
    v0 = sll(s5, 1);
    s0 = addu(s2, v0);
    lh(a0, s3, 0);
    v0 = 0x870000;
    v0 = addiu(v0, 6472);  // &0x871948
    v0 = addu(v0, s6);
    lh(a1, v0, 0);
    lhu(a2, s0, 0);
    a3 = 0;
    t0 = addiu(sp, 0x9C);
    t1 = addiu(sp, 0x98);
    t2 = addiu(sp, 0x94);
    jal(ctx, 0x43BEF8u, gen::fn_sub_17BE10_0017be10);
    lh(v0, s0, 0);
    // 0x0043bf20 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xA0);
}

// 0x0043BF50 sub_43BF50 -- 548 bytes; frame 0x90: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateSupportWalk] kNpcSupportState 0: walk 200 short of the target member (kNpcSkillTarget) (1); 1: when
// the mover is idle cast (sub_456EA0), state 2, mode from the tactic; 2: kNpcSupport = 0.
void sub_43BF50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0043bf50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lb(a0, s0, kNpcSupportState);
    v1 = 2;
    if (a0 == v1) {
        // 0x0043c150
        charge(ctx, 1);
        sb(zero, s0, kNpcSupport);
    } else {
        // 0x0043bf80
        charge(ctx, 3);
        v1 = 1;
        if (a0 != v1) {
            // 0x0043bf8c
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0043bf9c
                charge(ctx, 79);
                lw(v0, s0, kNpcUnit);
                lw(a0, v0, 368);
                jal(ctx, 0x43BFA4u, gen::fn_sub_1B00C0_001b00c0);
                lw(v0, s0, kNpcUnit);
                lw(a0, v0, 368);
                a1 = 0;
                jal(ctx, 0x43BFB8u, gen::fn_sub_1B0240_001b0240);
                lw(v0, s0, kNpcUnit);
                lw(a0, v0, 80);
                jal(ctx, 0x43BFC8u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x80);
                swc1(f1, sp, 0x84);
                swc1(f0, sp, 0x88);
                lh(v1, s0, kNpcSkillTarget);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6132);  // &0x8717F4
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                a0 = addiu(sp, 0x40);
                lw(a1, v0, 480);
                jal(ctx, 0x43C010u, gen::fn_sub_1AD940_001ad940);
                lwc1(f2, sp, 0x40);
                lwc1(f1, sp, 0x44);
                lwc1(f0, sp, 0x48);
                swc1(f2, sp, 0x70);
                swc1(f1, sp, 0x74);
                swc1(f0, sp, 0x78);
                lwc1(f1, sp, 0x80);
                lwc1(f0, sp, 0x70);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x60);
                lwc1(f21, sp, 0x74);
                lwc1(f0, sp, 0x84);
                sub_s(f0, f0, f21);
                swc1(f0, sp, 0x64);
                lwc1(f20, sp, 0x78);
                lwc1(f0, sp, 0x88);
                sub_s(f0, f0, f20);
                swc1(f0, sp, 0x68);
                a0 = addiu(sp, 0x60);
                a1 = a0;
                jal(ctx, 0x43C068u, gen::fn_sub_4C69F0_004c69f0);
                v0 = 0x43480000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x60);
                mul_s(f3, f1, f0);
                swc1(f3, sp, 0x50);
                lwc1(f0, sp, 0x64);
                mul_s(f2, f1, f0);
                swc1(f2, sp, 0x54);
                lwc1(f0, sp, 0x68);
                mul_s(f1, f1, f0);
                swc1(f1, sp, 0x58);
                lwc1(f0, sp, 0x70);
                add_s(f0, f3, f0);
                swc1(f0, sp, 0x50);
                add_s(f0, f2, f21);
                swc1(f0, sp, 0x54);
                add_s(f0, f1, f20);
                swc1(f0, sp, 0x58);
                lw(v0, s0, kNpcUnit);
                lw(a0, v0, 368);
                a1 = addiu(sp, 0x50);
                lwc1(f12, gp, -32072);  // 0x7CAFA8
                jal(ctx, 0x43C0C8u, gen::fn_sub_1AFA20_001afa20);
                v0 = 1;
                sb(v0, s0, kNpcSupportState);
                goto L_0043c0d8;
            }
            // 0x0043bf94
            charge(ctx, 2);
            // 0x0043c154 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x90);
            return;
        }
    L_0043c0d8:
        charge(ctx, 6);
        lw(v0, s0, kNpcUnit);
        lw(a0, v0, 368);
        jal(ctx, 0x43C0E0u, gen::fn_sub_1B0220_001b0220);
        if (v0 == 0) {
            // 0x0043c0f0
            charge(ctx, 11);
            lb(a1, s0, kNpcPc);
            lb(a2, s0, kNpcSkillTarget);
            a0 = s1;
            jal(ctx, 0x43C0FCu, gen::fn_sub_456EA0_00456ea0);
            a1 = 2;
            sb(a1, s0, kNpcSupportState);
            lb(a0, gp, -17972);  // 0x7CE6BC
            v1 = 1;
            if (a0 != v1) {
                // 0x0043c130
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0043c138
                    charge(ctx, 6);
                    lb(a0, s0, kNpcPc);
                    a1 = v1;
                    jal(ctx, 0x43C140u, gen::fn_sub_43C7A0_0043c7a0);
                }
            } else {
                // 0x0043c11c
                charge(ctx, 5);
                lb(a0, s0, kNpcPc);
                jal(ctx, 0x43C120u, gen::fn_sub_43C7A0_0043c7a0);
            }
        }
    }
    // 0x0043c154 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0043C180 sub_43C180 -- 436 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_FindReviverA] ($a0 pc) among the other live members 1..3 within reach, the one with a usable skill 205 and
// the most SP.
void sub_43C180(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0043c180
    enter(ctx, 23);  // entry check point + this block's cycles
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
    s3 = 0;
    s2 = 0;
    s5 = 1;
    s0 = dsll32(a0, 24);
    s0 = dsra32(s0, 24);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s6 = addu(v0, v1);
    for (;;) {
        // 0x0043c2f4
        charge(ctx, 3);
        v0 = slti(s5, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043c1dc
        charge(ctx, 2);
        if (s0 != s5) {
            // 0x0043c1e4
            charge(ctx, 10);
            a0 = 0;
            v0 = sll(s5, 3);
            v0 = subu(v0, s5);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            a1 = addu(v0, v1);
            lw(v0, a1, 72);
            if (v0 != 0) {
                // 0x0043c20c
                charge(ctx, 3);
                lw(v0, a1, 84);
                if (v0 != 0) {
                    // 0x0043c218
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x0043c21c
            charge(ctx, 4);
            v1 = sltu(0, a0);
            v0 = 1;
            if (v1 == v0) {
                // 0x0043c22c
                charge(ctx, 8);
                v0 = 0x43FA0000;
                mtc1(v0, f12);
                a0 = s6;
                jal(ctx, 0x43C238u, gen::fn_sub_1C7160_001c7160);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0043c24c
                    charge(ctx, 13);
                    v0 = sll(s5, 3);
                    v0 = subu(v0, s5);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s1 = addu(v0, v1);
                    lhu(a0, s1, 424);
                    jal(ctx, 0x43C268u, gen::fn_sub_173380_00173380);
                    s7 = v0;
                    s4 = 0;
                    for (;;) {
                        // 0x0043c2e4
                        charge(ctx, 3);
                        v0 = slti(s4, 8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0043c280
                        charge(ctx, 5);
                        v0 = sll(s4, 1);
                        v0 = addu(s7, v0);
                        lhu(a1, v0, 0);
                        if (a1 != 0) {
                            // 0x0043c294
                            charge(ctx, 3);
                            v0 = 205;
                            if (a1 == v0) {
                                // 0x0043c2a0
                                charge(ctx, 5);
                                lh(a0, s1, 424);
                                jal(ctx, 0x43C2A4u, gen::fn_sub_17B660_0017b660);
                                if (v0 == 0) {
                                    // 0x0043c2b4
                                    charge(ctx, 8);
                                    lh(a0, s1, 424);
                                    jal(ctx, 0x43C2B8u, gen::fn_sub_16C570_0016c570);
                                    v1 = v0 & 0xFFFF;
                                    v0 = s2 & 0xFFFF;
                                    at = slt(v0, v1);
                                    if (at != 0) {
                                        // 0x0043c2d4
                                        charge(ctx, 3);
                                        s3 = dsll32(s5, 16);
                                        s3 = dsra32(s3, 16);
                                        s2 = v1;
                                    }
                                }
                            }
                        }
                        // 0x0043c2e0
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                }
            }
        }
        // 0x0043c2f0
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0043c300
    charge(ctx, 13);
    v0 = s3;
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

// 0x0043C340 sub_43C340 -- 436 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_FindReviverB] The same for skill 204.
void sub_43C340(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0043c340
    enter(ctx, 23);  // entry check point + this block's cycles
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
    s3 = 0;
    s2 = 0;
    s5 = 1;
    s0 = dsll32(a0, 24);
    s0 = dsra32(s0, 24);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s6 = addu(v0, v1);
    for (;;) {
        // 0x0043c4b4
        charge(ctx, 3);
        v0 = slti(s5, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0043c39c
        charge(ctx, 2);
        if (s0 != s5) {
            // 0x0043c3a4
            charge(ctx, 10);
            a0 = 0;
            v0 = sll(s5, 3);
            v0 = subu(v0, s5);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            a1 = addu(v0, v1);
            lw(v0, a1, 72);
            if (v0 != 0) {
                // 0x0043c3cc
                charge(ctx, 3);
                lw(v0, a1, 84);
                if (v0 != 0) {
                    // 0x0043c3d8
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x0043c3dc
            charge(ctx, 4);
            v1 = sltu(0, a0);
            v0 = 1;
            if (v1 == v0) {
                // 0x0043c3ec
                charge(ctx, 8);
                v0 = 0x43FA0000;
                mtc1(v0, f12);
                a0 = s6;
                jal(ctx, 0x43C3F8u, gen::fn_sub_1C7160_001c7160);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0043c40c
                    charge(ctx, 13);
                    v0 = sll(s5, 3);
                    v0 = subu(v0, s5);
                    v1 = sll(v0, 6);
                    v0 = 0x870000;
                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                    s1 = addu(v0, v1);
                    lhu(a0, s1, 424);
                    jal(ctx, 0x43C428u, gen::fn_sub_173380_00173380);
                    s7 = v0;
                    s4 = 0;
                    for (;;) {
                        // 0x0043c4a4
                        charge(ctx, 3);
                        v0 = slti(s4, 8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0043c440
                        charge(ctx, 5);
                        v0 = sll(s4, 1);
                        v0 = addu(s7, v0);
                        lhu(a1, v0, 0);
                        if (a1 != 0) {
                            // 0x0043c454
                            charge(ctx, 3);
                            v0 = 204;
                            if (a1 == v0) {
                                // 0x0043c460
                                charge(ctx, 5);
                                lh(a0, s1, 424);
                                jal(ctx, 0x43C464u, gen::fn_sub_17B660_0017b660);
                                if (v0 == 0) {
                                    // 0x0043c474
                                    charge(ctx, 8);
                                    lh(a0, s1, 424);
                                    jal(ctx, 0x43C478u, gen::fn_sub_16C570_0016c570);
                                    v1 = v0 & 0xFFFF;
                                    v0 = s2 & 0xFFFF;
                                    at = slt(v0, v1);
                                    if (at != 0) {
                                        // 0x0043c494
                                        charge(ctx, 3);
                                        s3 = dsll32(s5, 16);
                                        s3 = dsra32(s3, 16);
                                        s2 = v1;
                                    }
                                }
                            }
                        }
                        // 0x0043c4a0
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                }
            }
        }
        // 0x0043c4b0
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x0043c4c0
    charge(ctx, 13);
    v0 = s3;
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

// 0x0043C500 Y_Npc_UpdateTreasureFreeTask -- 344 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_UpdateTreasureFreeTask] kNpcTfState 0: the chest's scene resource (sub_3B5D10 [MT_Scene_GetRes] of the
// record's u16 +8); with a model, its opening animation (sub_3182D0), state 1; 1: when the animation finished (model
// +40 bit 1 clear, or its +260 +238 == 1) the chest is released (sub_1D22A0), state 2; 2: returns -1 (done); else 0.
void Y_Npc_UpdateTreasureFreeTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043c500
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lb(v1, s0, kNpcTfState);
    v0 = 3;
    if (v1 != v0) {
        // 0x0043c520
        charge(ctx, 3);
        v0 = 2;
        if (v1 != v0) {
            // 0x0043c52c
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x0043c538
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0043c548
                    charge(ctx, 7);
                    lw(v0, s0, kNpcTfChest);
                    lhu(a0, v0, 8);
                    jal(ctx, 0x43C550u, gen::fn_sub_3B5D10_003b5d10);
                    sw(v0, s0, kNpcTfRes);
                    if (v0 != 0) {
                        // 0x0043c574
                        charge(ctx, 3);
                        lw(a0, v0, 260);
                        if (a0 != 0) {
                            // 0x0043c590
                            charge(ctx, 8);
                            a1 = 0;
                            a2 = 1;
                            a3 = 0;
                            t0 = 0;
                            jal(ctx, 0x43C5A0u, gen::fn_sub_3182D0_003182d0);
                            v0 = 1;
                            sb(v0, s0, kNpcTfState);
                            goto L_0043c5b0;
                        }
                        // 0x0043c580
                        charge(ctx, 4);
                        v0 = 2;
                        sb(v0, s0, kNpcTfState);
                    } else {
                        // 0x0043c564
                        charge(ctx, 4);
                        v0 = 2;
                        sb(v0, s0, kNpcTfState);
                    }
                } else {
                    // 0x0043c540
                    charge(ctx, 2);
                }
                goto L_0043c640;
            }
        L_0043c5b0:
            charge(ctx, 4);
            lw(v0, s0, kNpcTfRes);
            lw(v1, v0, 260);
            if (v1 != 0) {
                // 0x0043c5dc
                charge(ctx, 4);
                lw(v0, v0, 40);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x0043c618
                    charge(ctx, 7);
                    lw(a0, s0, kNpcTfChest);
                    jal(ctx, 0x43C61Cu, gen::fn_sub_1D22A0_001d22a0);
                    v0 = 2;
                    sb(v0, s0, kNpcTfState);
                } else {
                    // 0x0043c5ec
                    charge(ctx, 4);
                    lbu(v1, v1, 238);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0043c5fc
                        charge(ctx, 7);
                        lw(a0, s0, kNpcTfChest);
                        jal(ctx, 0x43C600u, gen::fn_sub_1D22A0_001d22a0);
                        v0 = 2;
                        sb(v0, s0, kNpcTfState);
                    }
                }
            } else {
                // 0x0043c5c0
                charge(ctx, 7);
                v0 = 2;
                sb(v0, s0, kNpcTfState);
                lw(a0, s0, kNpcTfChest);
                jal(ctx, 0x43C5CCu, gen::fn_sub_1D22A0_001d22a0);
            }
            goto L_0043c640;
        }
        // 0x0043c634
        charge(ctx, 3);
        v0 = si(-1);
        // 0x0043c644 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0043c640:
    charge(ctx, 1);
    v0 = 0;
    // 0x0043c644 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0043C660 sub_43C660 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_DestroyTreasureFreeTask] Frees the task's work through the RW free slot 0x96017C (jalr).
void sub_43C660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043c660
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x43C674u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0043C690 Y_Npc_CreateTreasureFreeTask -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_CreateTreasureFreeTask] calloc(1, 12), the task "treasure free proc" (no parent, priority 10), state 0, +8
// = the record. Returns the task or 0.
void Y_Npc_CreateTreasureFreeTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043c690
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x43C6B8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0043c6d8
        charge(ctx, 13);
        a0 = 0;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 17968);  // "treasure free proc"
        a3 = 0x440000;
        a3 = addiu(a3, -15104);  // &Y_Npc_UpdateTreasureFreeTask
        t0 = 0x440000;
        t0 = addiu(t0, -14752);  // &sub_43C660
        t1 = s0;
        jal(ctx, 0x43C6FCu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sb(zero, s0, kNpcTfState);
        sw(s1, s0, kNpcTfChest);
    } else {
        // 0x0043c6cc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0043c70c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0043C730 sub_43C730 -- 112 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_IsFree] 0 when member $a0's kNpcModeChange, kNpcSkillUse or kNpcSupport is 1, else 1. (Mini-map.)
void sub_43C730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0043c730
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6412);  // &0x87190C
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    lw(a0, v0, 60);
    lb(v0, a0, kNpcModeChange);
    v1 = 1;
    if (v0 != v1) {
        // 0x0043c774
        charge(ctx, 3);
        lb(v0, a0, kNpcSkillUse);
        if (v0 != v1) {
            // 0x0043c78c
            charge(ctx, 3);
            lb(v0, a0, kNpcSupport);
            v0 = v0 ^ 0x1;
            v0 = sltu(0, v0);
        } else {
            // 0x0043c780
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0043c768
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0043c798 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0043C7A0 sub_43C7A0 -- 72 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Npc_SetMode] ($a0 pc, $a1 mode) think work: kNpcMode = mode; kNpcFollowState, kNpcByte4644, kNpcExploreState,
// kNpcByte4641, kNpcFightState = 0.
void sub_43C7A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0043c7a0
    enter(ctx, 18);  // entry check point + this block's cycles
    a0 = dsll32(a0, 24);
    a0 = dsra32(a0, 24);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a0 = sll(v1, 6);
    v1 = 0x870000;
    v1 = addiu(v1, 6412);  // &0x87190C
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    lw(v1, v1, 60);
    sb(a1, v1, kNpcMode);
    sb(zero, v1, kNpcFollowState);
    sb(zero, v1, kNpcByte4644);
    sb(zero, v1, kNpcExploreState);
    sb(zero, v1, kNpcByte4641);
    sb(zero, v1, kNpcFightState);
}

// 0x0043C7F0 sub_43C7F0 -- 288 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Unit_GetMode] ($a0 index) 0 -> 0; 1..3 -> the party member's kNpcMode, 4.. -> the NPC unit's think byte +2
// (0x86E6A0 table); 6 when the unit is not live.
void sub_43C7F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0043c7f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    if (v1 != 0) {
        // 0x0043c80c
        charge(ctx, 3);
        at = slti(v1, 4);
        if (at == 0) {
            // 0x0043c894
            charge(ctx, 10);
            a0 = 0;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, -6424);  // &0x86E6E8
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x0043c8bc
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, -6412);  // &0x86E6F4
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                if (v0 != 0) {
                    // 0x0043c8d4
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x0043c8d8
            charge(ctx, 3);
            v0 = sltu(0, a0);
            if (v0 != 0) {
                // 0x0043c8f0
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, -6132);  // &0x86E80C
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                lw(v0, v0, 60);
                lb(v0, v0, 2);
            } else {
                // 0x0043c8e4
                charge(ctx, 3);
                v0 = 6;
            }
        } else {
            // 0x0043c818
            charge(ctx, 10);
            a0 = 0;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6120);  // &0x8717E8
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x0043c840
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6132);  // &0x8717F4
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                if (v0 != 0) {
                    // 0x0043c858
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x0043c85c
            charge(ctx, 3);
            v0 = sltu(0, a0);
            if (v0 != 0) {
                // 0x0043c874
                charge(ctx, 8);
                v0 = 0x870000;
                v0 = addiu(v0, 6412);  // &0x87190C
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                lw(v0, v0, 60);
                lb(v0, v0, 1);
            } else {
                // 0x0043c868
                charge(ctx, 3);
                v0 = 6;
            }
        }
    } else {
        // 0x0043c800
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0043c908 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0043C910 sub_43C910 -- 280 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Unit_GetHp] ($a0 index) 0 -> sub_16C5F0(1); 1..3 -> the u16 +8 of the party member's DatUnit; 4.. -> the NPC
// unit's; 0 when not live.
void sub_43C910(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0043c910
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    if (v1 != 0) {
        // 0x0043c93c
        charge(ctx, 3);
        at = slti(v1, 4);
        if (at == 0) {
            // 0x0043c9b4
            charge(ctx, 10);
            a1 = 0;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            a0 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, -6424);  // &0x86E6E8
            v0 = addu(v0, a0);
            lw(v1, v0, 0);
            if (v1 != 0) {
                // 0x0043c9dc
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, -6412);  // &0x86E6F4
                v0 = addu(v0, a0);
                lw(v0, v0, 0);
                if (v0 != 0) {
                    // 0x0043c9f4
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x0043c9f8
            charge(ctx, 3);
            v0 = sltu(0, a1);
            if (v0 != 0) {
                // 0x0043ca10
                charge(ctx, 2);
                lw(v0, v1, 4);
                lhu(v0, v0, 8);
            } else {
                // 0x0043ca04
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x0043c948
            charge(ctx, 10);
            a1 = 0;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            a0 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6120);  // &0x8717E8
            v0 = addu(v0, a0);
            lw(v1, v0, 0);
            if (v1 != 0) {
                // 0x0043c970
                charge(ctx, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6132);  // &0x8717F4
                v0 = addu(v0, a0);
                lw(v0, v0, 0);
                if (v0 != 0) {
                    // 0x0043c988
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x0043c98c
            charge(ctx, 3);
            v0 = sltu(0, a1);
            if (v0 != 0) {
                // 0x0043c9a4
                charge(ctx, 4);
                lw(v0, v1, 4);
                lhu(v0, v0, 8);
            } else {
                // 0x0043c998
                charge(ctx, 3);
                v0 = 0;
            }
        }
    } else {
        // 0x0043c928
        charge(ctx, 5);
        a0 = 1;
        jal(ctx, 0x43C92Cu, gen::fn_sub_16C5F0_0016c5f0);
    }
    // 0x0043ca18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00447AD0 sub_447AD0 -- 920 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_StParts_DestroyTask] Destroys the textures (+628 x 6, +968 x 5, +1060 x 2; sub_4D0F00), the sprite files (+4,
// +232; sub_1124B0), every sprite handle (the 56 parts, the per-block and per-row handles from +1192, the cursors;
// sub_115980); when not opened from the map: sub_1A0040(1, 0), the stratum record (sub_449FA0) and the script copy;
// the gp task 0x7CE6AC; the triangle list (sub_2699A0); then frees the work.
void sub_447AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00447ad0
    enter(ctx, 15);  // entry check point + this block's cycles
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
    s4 = a0;
    lw(s0, a0, 60);
    s1 = 0;
    for (;;) {
        // 0x00447b34
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447b0c
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 628);
        lw(a0, v0, 628);
        if (a0 != 0) {
            // 0x00447b24
            charge(ctx, 3);
            jal(ctx, 0x447B24u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s2, 0);
        }
        // 0x00447b30
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447b40
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00447b74
        charge(ctx, 3);
        v0 = slti(s1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447b4c
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 968);
        lw(a0, v0, 968);
        if (a0 != 0) {
            // 0x00447b64
            charge(ctx, 3);
            jal(ctx, 0x447B64u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s2, 0);
        }
        // 0x00447b70
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447b80
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00447bb4
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447b8c
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 1060);
        lw(a0, v0, 1060);
        if (a0 != 0) {
            // 0x00447ba4
            charge(ctx, 3);
            jal(ctx, 0x447BA4u, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s2, 0);
        }
        // 0x00447bb0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447bc0
    charge(ctx, 3);
    lw(a0, s0, kSpSprites);
    if (a0 != 0) {
        // 0x00447bcc
        charge(ctx, 3);
        jal(ctx, 0x447BCCu, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, kSpSprites);
    }
    // 0x00447bd8
    charge(ctx, 3);
    lw(a0, s0, kSpSprites2);
    if (a0 != 0) {
        // 0x00447be4
        charge(ctx, 3);
        jal(ctx, 0x447BE4u, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, kSpSprites2);
    }
    // 0x00447bf0
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00447c24
        charge(ctx, 3);
        v0 = slti(s1, 56);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447bfc
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 8);
        lw(a0, v0, 8);
        if (a0 != 0) {
            // 0x00447c14
            charge(ctx, 3);
            jal(ctx, 0x447C14u, gen::fn_sub_115980_00115980);
            sw(zero, s2, 0);
        }
        // 0x00447c20
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447c30
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00447d4c
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447c3c
        charge(ctx, 6);
        v0 = sll(s1, 2);
        s2 = addu(s0, v0);
        s3 = addiu(s2, 1192);
        lw(a0, s2, 1192);
        if (a0 != 0) {
            // 0x00447c54
            charge(ctx, 3);
            jal(ctx, 0x447C54u, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00447c60
        charge(ctx, 3);
        lw(a0, s2, 1216);
        if (a0 != 0) {
            // 0x00447c6c
            charge(ctx, 6);
            v0 = sll(s1, 2);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 1216);
            jal(ctx, 0x447C78u, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00447c84
        charge(ctx, 3);
        lw(a0, s2, 1264);
        if (a0 != 0) {
            // 0x00447c90
            charge(ctx, 6);
            v0 = sll(s1, 2);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 1264);
            jal(ctx, 0x447C9Cu, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00447ca8
        charge(ctx, 3);
        lw(a0, s2, 1240);
        if (a0 != 0) {
            // 0x00447cb4
            charge(ctx, 6);
            v0 = sll(s1, 2);
            v0 = addu(s0, v0);
            s2 = addiu(v0, 1240);
            jal(ctx, 0x447CC0u, gen::fn_sub_115980_00115980);
            sw(zero, s2, 0);
        }
        // 0x00447ccc
        charge(ctx, 7);
        s3 = 0;
        v0 = sll(s1, 3);
        v0 = addu(v0, s1);
        v0 = sll(v0, 4);
        s5 = addu(s0, v0);
        for (;;) {
            // 0x00447d3c
            charge(ctx, 3);
            v0 = slti(s3, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00447ce8
            charge(ctx, 7);
            s2 = 0;
            v0 = sll(s3, 1);
            v0 = addu(v0, s3);
            v0 = sll(v0, 4);
            s6 = addu(s5, v0);
            for (;;) {
                // 0x00447d2c
                charge(ctx, 3);
                v0 = slti(s2, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00447d04
                charge(ctx, 6);
                v0 = sll(s2, 2);
                v0 = addu(s6, v0);
                s7 = addiu(v0, 1288);
                lw(a0, v0, 1288);
                if (a0 != 0) {
                    // 0x00447d1c
                    charge(ctx, 3);
                    jal(ctx, 0x447D1Cu, gen::fn_sub_115980_00115980);
                    sw(zero, s7, 0);
                }
                // 0x00447d28
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00447d38
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x00447d48
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447d58
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00447d8c
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00447d64
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 828);
        lw(a0, v0, 828);
        if (a0 != 0) {
            // 0x00447d7c
            charge(ctx, 3);
            jal(ctx, 0x447D7Cu, gen::fn_sub_115980_00115980);
            sw(zero, s2, 0);
        }
        // 0x00447d88
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00447d98
    charge(ctx, 3);
    lw(a0, s0, kSpCursorA);
    if (a0 != 0) {
        // 0x00447da4
        charge(ctx, 3);
        jal(ctx, 0x447DA4u, gen::fn_sub_115980_00115980);
        sw(zero, s0, kSpCursorA);
    }
    // 0x00447db0
    charge(ctx, 3);
    lw(a0, s0, kSpCursorB);
    if (a0 != 0) {
        // 0x00447dbc
        charge(ctx, 3);
        jal(ctx, 0x447DBCu, gen::fn_sub_115980_00115980);
        sw(zero, s0, kSpCursorB);
    }
    // 0x00447dc8
    charge(ctx, 3);
    lb(v0, s0, kSpFromMap);
    if (v0 == 0) {
        // 0x00447dd4
        charge(ctx, 11);
        a0 = 1;
        a1 = 0;
        jal(ctx, 0x447DDCu, gen::fn_sub_1A0040_001a0040);
        jal(ctx, 0x447DE4u, gen::fn_sub_449FA0_00449fa0);
        lw(a0, s0, kSpScriptCopy);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x447DF8u, v0.u());
    }
    // 0x00447e00
    charge(ctx, 3);
    lw(a0, gp, -17988);  // 0x7CE6AC
    if (a0 != 0) {
        // 0x00447e0c
        charge(ctx, 3);
        jal(ctx, 0x447E0Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, gp, -17988);  // 0x7CE6AC
    }
    // 0x00447e18
    charge(ctx, 20);
    lw(a0, s0, kSpTriList);
    jal(ctx, 0x447E1Cu, gen::fn_sub_2699A0_002699a0);
    lw(a0, s4, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x447E30u, v0.u());
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

// 0x00447E70 Y_Stratum_CreateStratumPartsTask -- 280 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_CreateStratumPartsTask] ($a0 parent, $a1 mode, $a2 from-map) calloc(1, 2396), the task
// "y_StratumParts_proc" (priority 4207, update Y_StParts_UpdateStratumPartsTask, destroy sub_447AD0), state 0, +780
// = 1.0, the cursor / scroll 0, the triangle list (sub_269690(1, 24, 16)), +2394 = 6; datSetFlag(5149, 1). Returns
// the task or 0.
void Y_Stratum_CreateStratumPartsTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00447e70
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 1;
    a1 = 2396;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x447EA8u, v0.u());
    s2 = v0;
    if (s2 != 0) {
        // 0x00447ec8
        charge(ctx, 40);
        a0 = s3;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 18944);  // "y_StratumParts_proc"
        a3 = 0x440000;
        a3 = addiu(a3, -13776);  // &Y_StParts_UpdateStratumPartsTask
        t0 = 0x440000;
        t0 = addiu(t0, 31440);  // &sub_447AD0
        t1 = s2;
        jal(ctx, 0x447EECu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s3 = v0;
        sb(zero, s2, kSpState);
        v0 = 0x3F800000;
        sw(v0, s2, 780);
        sb(zero, s2, kSpCursor);
        sb(zero, s2, kSpScroll);
        sb(s0, s2, kSpFromMap);
        sb(s1, s2, kSpMode);
        sb(zero, s2, kSpEndWait);
        sh(zero, s2, 598);
        sb(zero, s2, 600);
        sb(zero, s2, 601);
        sw(zero, s2, kSpWobbleFrame);
        a0 = 1;
        a1 = 24;
        a2 = 16;
        jal(ctx, 0x447F34u, gen::fn_sub_269690_00269690);
        sw(v0, s2, kSpTriList);
        sh(zero, s2, 2392);
        v0 = 6;
        sh(v0, s2, 2394);
        sh(zero, s2, 2390);
        sh(zero, s2, 2388);
        a0 = 5149;
        a1 = 1;
        jal(ctx, 0x447F5Cu, gen::fn_datSetFlag_0016f1f0);
        v0 = s3;
    } else {
        // 0x00447ebc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00447f68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00449ED0 sub_449ED0 -- 208 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_CreateRecord] calloc(1, 200) into 0x7CE6EC; the 30 list entries cleared, +160 = 0, +162 = 1 (floor 1),
// +164 = 1, +165 = 0, +172 = 0, +173 = 1 block open, the six block states = 2.
void sub_449ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00449ed0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 200;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x449EECu, v0.u());
    sw(v0, gp, -17924);  // 0x7CE6EC
    a1 = 0;
    for (;;) {
        // 0x00449f24
        charge(ctx, 3);
        v1 = slti(a1, 30);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00449f04
        charge(ctx, 8);
        a0 = sll(a1, 2);
        lw(v1, gp, -17924);  // 0x7CE6EC
        v1 = addu(v1, a0);
        sb(zero, v1, kStRecEntryBlock);
        lw(v1, gp, -17924);  // 0x7CE6EC
        v1 = addu(v1, a0);
        sh(zero, v1, kStRecEntryFloor);
        a1 = addiu(a1, 1);
    }
    // 0x00449f30
    charge(ctx, 17);
    lw(v1, gp, -17924);  // 0x7CE6EC
    sb(zero, v1, kStRecCount);
    a0 = 1;
    lw(v1, gp, -17924);  // 0x7CE6EC
    sh(a0, v1, kStRecFloor);
    lw(v1, gp, -17924);  // 0x7CE6EC
    sb(a0, v1, kStRecBlock);
    lw(v1, gp, -17924);  // 0x7CE6EC
    sb(zero, v1, kStRecDone);
    lw(v1, gp, -17924);  // 0x7CE6EC
    sb(zero, v1, kStRecLayout);
    lw(v1, gp, -17924);  // 0x7CE6EC
    sb(a0, v1, kStRecBlocksOpen);
    a1 = 0;
    a0 = 2;
    for (;;) {
        // 0x00449f84
        charge(ctx, 3);
        v1 = slti(a1, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00449f74
        charge(ctx, 4);
        lw(v1, gp, -17924);  // 0x7CE6EC
        v1 = addu(v1, a1);
        sb(a0, v1, kStRecBlockStates);
        a1 = addiu(a1, 1);
    }
    // 0x00449f90
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00449FA0 sub_449FA0 -- 56 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_FreeRecord] Frees 0x7CE6EC through the RW free slot 0x96017C and clears it.
void sub_449FA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00449fa0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -17924);  // 0x7CE6EC
    if (a0 != 0) {
        // 0x00449fb4
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x449FBCu, v0.u());
        sw(zero, gp, -17924);  // 0x7CE6EC
    }
    // 0x00449fc8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0044A990 sub_44A990 -- 352 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s2 sp+0x4C
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_DrawWobble] ($a0 work, $a1 a texture pointer) +1152 = (+1152 + 1) % 180; the RW render states (slot
// 0x960090) and two sky driver states (RpSkyRenderStateSet 2 / 3), the raster *($a1); draws the list +1148
// (drawIm2DIndexedTriList) and walks its vertices with the callback sub_44A790 (sub_269A10).
void sub_44A990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0044a990
    enter(ctx, 88);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(v0, a0, kSpWobbleFrame);
    v1 = addiu(v0, 1);
    sw(v1, a0, kSpWobbleFrame);
    v0 = 180;
    div(v1, v0);
    mfhi(v0);
    sw(v0, a0, kSpWobbleFrame);
    sw(s2, sp, 0x4C);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44A9E0u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44A9F4u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA08u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA1Cu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA30u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA44u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA58u, v0.u());
    a0 = 2;
    a1 = 4;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AA6Cu, v0.u());
    a0 = 2;
    a1 = 68;
    jal(ctx, 0x44AA7Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x17FB;
    jal(ctx, 0x44AA90u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    lw(a1, s1, 0);
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x44AAA4u, v0.u());
    lw(a0, s2, kSpTriList);
    jal(ctx, 0x44AAB0u, gen::fn_drawIm2DIndexedTriList_002699d0);
    v0 = 0x450000;
    v0 = addiu(v0, -22640);  // &sub_44A790
    sw(v0, sp, 0x48);
    lw(a0, s2, kSpTriList);
    a1 = addiu(sp, 0x48);
    jal(ctx, 0x44AACCu, gen::fn_sub_269A10_00269a10);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0044ACF0 sub_44ACF0 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [destroy callback of "ene think proc"] Frees the task's work (+60) through the RW free slot 0x96017C (a jalr
// tail).
void sub_44ACF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0044acf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x44AD04u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0044AD20 Y_Stratum_CreateEneThinkTask -- 572 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_CreateEneThinkTask] ($a0 parent, $a1 shadow index) calloc(1, 4248) (RW slot 0x960184), the task "ene
// think proc" (priority 10, update Y_Stratum_UpdateEneThinkTask, destroy sub_44ACF0). State 4 (roam), or 3 for a
// kind-4 shadow (unit +396) with sub_1AAA20 in +16; a state kept in the unit (+410) is restored with its behaviour
// (+408) and target cell (+409); paused when the unit's +412 == 1; a kind-4 shadow gets the stair door point
// (sub_452F70). Returns the task or 0. (sub_1CFDD0 / sub_1D1360 in the field unit band.)
void Y_Stratum_CreateEneThinkTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0044ad20
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s4 = a1;
    a0 = 1;
    a1 = 4248;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x44AD58u, v0.u());
    s2 = v0;
    if (s2 != 0) {
        // 0x0044ad78
        charge(ctx, 26);
        a0 = s0;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 18968);  // "ene think proc"
        a3 = 0x450000;
        a3 = addiu(a3, -21776);  // &Y_Stratum_UpdateEneThinkTask
        t0 = 0x450000;
        t0 = addiu(t0, -21264);  // &sub_44ACF0
        t1 = s2;
        jal(ctx, 0x44AD9Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s3 = v0;
        sb(zero, s2, kEneByte0);
        a0 = 4;
        sb(a0, s2, kEneState);
        v1 = dsll32(s4, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        s1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -4308);  // &0x86EF2C
        s0 = addu(v0, s1);
        lw(v0, s0, 0);
        if (v0 == a0) {
            // 0x0044ade0
            charge(ctx, 9);
            v0 = 3;
            sb(v0, s2, kEneState);
            v0 = 0x870000;
            v0 = addiu(v0, -4704);  // &gFldUnitsEc
            a1 = addu(v0, s1);
            a0 = s3;
            jal(ctx, 0x44ADF8u, gen::fn_sub_1AAA20_001aaa20);
            sw(v0, s2, kEneKind4Word);
        }
        // 0x0044ae04
        charge(ctx, 11);
        sb(zero, s2, kEneSubState);
        sb(zero, s2, kEneSubState2);
        sb(zero, s2, kEneSubState3);
        sb(s4, s2, kEneUnit);
        sb(zero, s2, kEnePaused);
        v0 = 0x870000;
        v0 = addiu(v0, -4294);  // &0x86EF3A
        a0 = addu(v0, s1);
        lb(v0, a0, 0);
        if (v0 != 0) {
            // 0x0044ae30
            charge(ctx, 20);
            v1 = dsll32(s4, 24);
            v1 = dsra32(v1, 24);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, -4296);  // &0x86EF38
            v0 = addu(v0, v1);
            lb(v0, v0, 0);
            sb(v0, s2, kEneBehaviour);
            v0 = 0x870000;
            v0 = addiu(v0, -4295);  // &0x86EF39
            v1 = addu(v0, v1);
            lbu(v0, v1, 0);
            v0 = srl(v0, 4);
            sb(v0, s2, kEneTargetZ);
            lbu(v1, v1, 0);
            v0 = v1 & 0xF;
            if (i64(v1) < 0) {
                // 0x0044ae80
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0044ae88
                    charge(ctx, 1);
                    v0 = addiu(v0, -16);
                }
            }
            // 0x0044ae8c
            charge(ctx, 7);
            sb(v0, s2, kEneTargetX);
            lb(v0, a0, 0);
            sb(v0, s2, kEneState);
            lw(v0, s0, 0);
            v1 = 3;
            if (v0 != v1) {
                // 0x0044aec4
                charge(ctx, 3);
                lb(v0, s2, kEneState);
                if (v0 == v1) {
                    // 0x0044aed0
                    charge(ctx, 3);
                    sb(zero, s2, kEneByte7);
                    v0 = 1;
                    sb(v0, s2, kEneSubState);
                }
            } else {
                // 0x0044aea8
                charge(ctx, 3);
                lb(v0, s2, kEneState);
                if (v0 == v1) {
                    // 0x0044aeb4
                    charge(ctx, 4);
                    v0 = 17;
                    sb(v0, s2, kEneSubState);
                }
            }
        }
        // 0x0044aedc
        charge(ctx, 7);
        v0 = 0x870000;
        v0 = addiu(v0, -4292);  // &0x86EF3C
        v0 = addu(v0, s1);
        lb(v1, v0, 0);
        v0 = 1;
        if (v1 == v0) {
            // 0x0044aef8
            charge(ctx, 1);
            sb(v0, s2, kEnePaused);
        }
        // 0x0044aefc
        charge(ctx, 4);
        lw(v1, s0, 0);
        v0 = 4;
        if (v1 == v0) {
            // 0x0044af0c
            charge(ctx, 10);
            a0 = addiu(sp, 0x60);
            a1 = s3;
            jal(ctx, 0x44AF14u, gen::fn_sub_452F70_00452f70);
            lwc1(f2, sp, 0x60);
            lwc1(f1, sp, 0x64);
            lwc1(f0, sp, 0x68);
            swc1(f2, s2, kEneStairPosX);
            swc1(f1, s2, kEneStairPosY);
            swc1(f0, s2, kEneStairPosZ);
        }
        // 0x0044af34
        charge(ctx, 1);
        v0 = s3;
    } else {
        // 0x0044ad6c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0044af38 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00454290 sub_454290 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [destroy callback of "y_ene_dead effect proc"] Frees the task's work (+60) through the RW free slot 0x96017C (a
// jalr tail).
void sub_454290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00454290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x4542A4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004542C0 Y_Stratum_CreateEneDeadEffectTask -- 256 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_CreateEneDeadEffectTask] ($a0 shadow index) calloc(1, 16), the task "y_ene_dead effect proc" (no
// parent, priority 4207), state 0, the position of the shadow's controller (sub_1AD940 on its scene resource +480);
// then sub_1D0110 on the unit. Returns the task or 0. (The chase update sub_44BEB0.)
void Y_Stratum_CreateEneDeadEffectTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004542c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 16;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x4542ECu, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x0045430c
        charge(ctx, 38);
        a0 = 0;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 18992);  // "y_ene_dead effect proc"
        a3 = 0x450000;
        a3 = addiu(a3, 16880);  // &Y_Stratum_UpdateEneDeadEffectTask
        t0 = 0x450000;
        t0 = addiu(t0, 17040);  // &sub_454290
        t1 = s1;
        jal(ctx, 0x454330u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s2 = v0;
        sb(zero, s1, kEneDeadState);
        v1 = dsll32(s0, 24);
        v1 = dsra32(v1, 24);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        s0 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -4620);  // &0x86EDF4
        v0 = addu(v0, s0);
        lw(v0, v0, 0);
        a0 = addiu(sp, 0x40);
        lw(a1, v0, 480);
        jal(ctx, 0x45436Cu, gen::fn_sub_1AD940_001ad940);
        lwc1(f2, sp, 0x40);
        lwc1(f1, sp, 0x44);
        lwc1(f0, sp, 0x48);
        swc1(f2, s1, kEneDeadPosX);
        swc1(f1, s1, kEneDeadPosY);
        swc1(f0, s1, kEneDeadPosZ);
        v0 = 0x870000;
        v0 = addiu(v0, -4704);  // &gFldUnitsEc
        a0 = addu(v0, s0);
        jal(ctx, 0x454398u, gen::fn_sub_1D0110_001d0110);
        v0 = s2;
    } else {
        // 0x00454300
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004543a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00455E00 sub_455E00 -- 584 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SymbolDirp_UpdateTask] While shown (kEneDirpShown): state 0 -> 1 -> the hero's scene resource, 2; state 2 sets
// the RW render states (through the slot 0x960090, the raster from the word at gp-0x4610), the four vertices (screen
// z, recip camera z, white), their texture u / v from +316 / +320, the hero's model matrix (sub_1A5AA0), the corners
// (sub_4561F0), and draws a triangle fan of 4 vertices (RwIm2DRenderPrimitive slot 0x9600A0). Returns 0.
void sub_455E00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00455e00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, 60);
    lb(v0, s1, kEneDirpShown);
    if (v0 != 0) {
        // 0x00455e34
        charge(ctx, 4);
        lb(v1, s1, kEneDirpState);
        v0 = 3;
        if (v1 != v0) {
            // 0x00455e44
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x00455e50
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x00455e5c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00455e6c
                        charge(ctx, 1);
                        sb(v0, s1, kEneDirpState);
                        goto L_00455e70;
                    }
                    // 0x00455e64
                    charge(ctx, 2);
                    goto L_00456028;
                }
            L_00455e70:
                charge(ctx, 6);
                a0 = 1024;
                jal(ctx, 0x455E74u, gen::fn_sub_3B5D10_003b5d10);
                sw(v0, s1, kEneDirpHeroRes);
                v0 = 2;
                sb(v0, s1, kEneDirpState);
            }
            // 0x00455e88
            charge(ctx, 59);
            s0 = 0x960000;
            s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
            a0 = 6;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455E9Cu, v0.u());
            a0 = 7;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455EB0u, v0.u());
            a0 = 8;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455EC4u, v0.u());
            a0 = 10;
            a1 = 5;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455ED8u, v0.u());
            a0 = 11;
            a1 = 6;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455EECu, v0.u());
            a0 = 9;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455F00u, v0.u());
            a0 = 12;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455F14u, v0.u());
            lw(v0, gp, -17936);  // 0x7CE6E0
            a0 = 1;
            lw(a1, v0, 0);
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455F2Cu, v0.u());
            a0 = 2;
            a1 = 3;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x455F40u, v0.u());
            jal(ctx, 0x455F48u, gen::fn_sub_198590_00198590);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, v0, 128);
            div_s(f2, f1, f0);
            a1 = 0;
            v0 = 0x960000;
            a0 = 0x437F0000;
            for (;;) {
                // 0x00455fa4
                charge(ctx, 3);
                v1 = slti(a1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00455f74
                charge(ctx, 12);
                v1 = sll(a1, 6);
                v1 = addu(s1, v1);
                lwc1(f1, v0, 136);
                lwc1(f0, s1, kEneDirpDepth);
                sub_s(f0, f1, f0);
                swc1(f0, v1, 24);
                swc1(f2, v1, 40);
                sw(a0, v1, 48);
                sw(a0, v1, 52);
                sw(a0, v1, 56);
                sw(a0, v1, 60);
                a1 = addiu(a1, 1);
            }
            // 0x00455fb0
            charge(ctx, 30);
            sw(zero, s1, 32);
            sw(zero, s1, 36);
            lwc1(f0, s1, kEneDirpU);
            swc1(f0, s1, 96);
            sw(zero, s1, 100);
            sw(zero, s1, 160);
            lwc1(f0, s1, kEneDirpV);
            swc1(f0, s1, 164);
            lwc1(f0, s1, kEneDirpU);
            swc1(f0, s1, 224);
            lwc1(f0, s1, kEneDirpV);
            swc1(f0, s1, 228);
            lw(v0, s1, kEneDirpHeroRes);
            lw(a0, v0, 296);
            jal(ctx, 0x455FE8u, gen::fn_sub_318B60_00318b60);
            a0 = v0;
            jal(ctx, 0x455FF4u, gen::fn_sub_1A5AA0_001a5aa0);
            a0 = s2;
            mov_s(f12, f0);
            jal(ctx, 0x456004u, gen::fn_sub_4561F0_004561f0);
            a0 = 4;
            a1 = addiu(s1, 16);
            a2 = a0;
            v0 = 0x960000;
            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x456020u, v0.u());
        }
    L_00456028:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00455e28
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0045602c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00456050 sub_456050 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_SymbolDirp_DestroyTask] Destroys the H_Cdvd file +4 (H_Cdvd_Destroy) and the texture +8 (sub_4D0F00) when set,
// then frees the work.
void sub_456050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00456050
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(a0, s0, kEneDirpFile);
    if (a0 != 0) {
        // 0x00456074
        charge(ctx, 3);
        jal(ctx, 0x456074u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, kEneDirpFile);
    }
    // 0x00456080
    charge(ctx, 3);
    lw(a0, s0, kEneDirpTexture);
    if (a0 != 0) {
        // 0x0045608c
        charge(ctx, 3);
        jal(ctx, 0x45608Cu, gen::fn_sub_4D0F00_004d0f00);
        sw(zero, s0, kEneDirpTexture);
    }
    // 0x00456098
    charge(ctx, 11);
    lw(a0, s1, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x4560A4u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004560D0 Y_Stratum_CreateSmapSymbolDirpTask -- 244 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Stratum_CreateSmapSymbolDirpTask] ($a0 parent, $a1 / $a2 kept at +280 / +284, $f12 / $f13 the centre, $f14 the
// depth) calloc(1, 336), kwlnTaskCreate(parent, "smap_symbol_dirp", priority 6310, update sub_455E00, destroy
// sub_456050), angle 0, hidden, u / v 0.75. Returns the task or 0. (The mini-map set-up sub_42BC10 / sub_42BFD0.)
void Y_Stratum_CreateSmapSymbolDirpTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004560d0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    mov_s(f22, f12);
    mov_s(f21, f13);
    s2 = a1;
    s1 = a2;
    mov_s(f20, f14);
    a0 = 1;
    a1 = 336;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x456120u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00456140
        charge(ctx, 22);
        a0 = s3;
        a1 = 0x6B0000;
        a1 = addiu(a1, 19040);  // "smap_symbol_dirp"
        a2 = 6310;
        a3 = 0x450000;
        a3 = addiu(a3, 24064);  // &sub_455E00
        t0 = 0x450000;
        t0 = addiu(t0, 24656);  // &sub_456050
        t1 = s0;
        jal(ctx, 0x456164u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, kEneDirpState);
        swc1(f22, s0, kEneDirpCentreX);
        swc1(f21, s0, kEneDirpCentreY);
        sw(s2, s0, kEneDirpArg1);
        sw(s1, s0, kEneDirpArg2);
        sw(zero, s0, kEneDirpAngle);
        sb(zero, s0, kEneDirpShown);
        swc1(f20, s0, kEneDirpDepth);
        v1 = 0x3F500000;
        sw(v1, s0, kEneDirpU);
        sw(v1, s0, kEneDirpV);
    } else {
        // 0x00456134
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00456198 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004575E0 Y_Kyoto_UpdateKyotoNpcModeReadTask -- 920 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_UpdateKyotoNpcModeReadTask] States (jump table 0x7BC6C0): 1 / 3 / 5 / 7 take a free NPC slot (sub_457410)
// and build NPC 0..3 there -- DatUnit (datUnitCreatePc 2 / 4 / 6 / 3), model (sub_316E00(9, 0x200 / 0x400 / 0x600 /
// 0x300)), its persona id, the scene resource 0x3C00 / 0x4400 / 0x4000 / 0x4401 --; 2 / 4 / 6 / 8 wait for the model
// (sub_457470) and create the NPC's "Kyoto_NpcThink proc" (route 0, 2, 1, 2) into the unit's think slot; 9 returns
// -1.
void Y_Kyoto_UpdateKyotoNpcModeReadTask(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004575e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lb(v0, s0, kKyotoState);
    at = sltiu(v0, 10);
    if (at != 0) {
        // 0x0045760c
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -14656);  // "(vE"
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x457628u:  // table[0]
            // 0x00457628: state 0: start
            charge(ctx, 4);
            v0 = 1;
            sb(v0, s0, kKyotoState);
        L_00457954:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x457638u:  // table[1]
            // 0x00457638: state 1: NPC 0's unit and model
            charge(ctx, 9);
            a0 = 15360;
            jal(ctx, 0x45763Cu, gen::fn_sub_3B5D10_003b5d10);
            s2 = v0;
            jal(ctx, 0x457648u, gen::fn_sub_457410_00457410);
            s1 = v0;
            if (s1 != 0) {
                // 0x0045765c
                charge(ctx, 21);
                a0 = 2;
                jal(ctx, 0x457660u, gen::fn_datUnitCreatePc_002ff340);
                sw(v0, s1, 72);
                a0 = 9;
                a1 = 513;
                a2 = 0;
                jal(ctx, 0x457678u, gen::fn_sub_316E00_00316e00);
                s3 = v0;
                a0 = s3;
                jal(ctx, 0x457688u, gen::fn_sub_31C1D0_0031c1d0);
                sw(s3, s1, 80);
                a0 = 2;
                sh(a0, s1, 424);
                jal(ctx, 0x45769Cu, gen::fn_sub_173300_00173300);
                v0 = v0 & 0xFF;
                sw(v0, s1, 388);
                sw(s2, s1, 360);
            }
            // 0x004576b0
            charge(ctx, 2);
            v0 = 2;
            sb(v0, s0, kKyotoState);
        L_004576b8:
            charge(ctx, 6);
            a0 = 0;
            jal(ctx, 0x4576BCu, gen::fn_sub_457470_00457470);
            v1 = 1;
            if (v0 == v1) {
                // 0x004576d0
                charge(ctx, 11);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x4576DCu, gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630);
                v1 = 0x870000;
                sw(v0, v1, -6132);  // 0x86E80C
                v0 = 3;
                sb(v0, s0, kKyotoState);
            }
            goto L_00457954;
        case 0x4576B8u:  // table[2]
            goto L_004576b8;
        case 0x4576FCu:  // table[3]
            // 0x004576fc: states 2 / 3: NPC 0's think task, NPC 1's unit
            charge(ctx, 9);
            a0 = 17408;
            jal(ctx, 0x457700u, gen::fn_sub_3B5D10_003b5d10);
            s2 = v0;
            jal(ctx, 0x45770Cu, gen::fn_sub_457410_00457410);
            s1 = v0;
            if (s1 != 0) {
                // 0x00457720
                charge(ctx, 21);
                a0 = 4;
                jal(ctx, 0x457724u, gen::fn_datUnitCreatePc_002ff340);
                sw(v0, s1, 72);
                a0 = 9;
                a1 = 1024;
                a2 = 0;
                jal(ctx, 0x45773Cu, gen::fn_sub_316E00_00316e00);
                s3 = v0;
                a0 = s3;
                jal(ctx, 0x45774Cu, gen::fn_sub_31C1D0_0031c1d0);
                sw(s3, s1, 80);
                a0 = 4;
                sh(a0, s1, 424);
                jal(ctx, 0x457760u, gen::fn_sub_173300_00173300);
                v0 = v0 & 0xFF;
                sw(v0, s1, 388);
                sw(s2, s1, 360);
            }
            // 0x00457774
            charge(ctx, 2);
            v0 = 4;
            sb(v0, s0, kKyotoState);
        L_0045777c:
            charge(ctx, 6);
            a0 = 1;
            jal(ctx, 0x457780u, gen::fn_sub_457470_00457470);
            a1 = 1;
            if (v0 == a1) {
                // 0x00457794
                charge(ctx, 10);
                a0 = 0;
                a2 = 2;
                jal(ctx, 0x45779Cu, gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630);
                v1 = 0x870000;
                sw(v0, v1, -5684);  // 0x86E9CC
                v0 = 5;
                sb(v0, s0, kKyotoState);
            }
            goto L_00457954;
        case 0x45777Cu:  // table[4]
            goto L_0045777c;
        case 0x4577BCu:  // table[5]
            // 0x004577bc: states 4 / 5
            charge(ctx, 9);
            a0 = 16384;
            jal(ctx, 0x4577C0u, gen::fn_sub_3B5D10_003b5d10);
            s2 = v0;
            jal(ctx, 0x4577CCu, gen::fn_sub_457410_00457410);
            s1 = v0;
            if (s1 != 0) {
                // 0x004577e0
                charge(ctx, 21);
                a0 = 6;
                jal(ctx, 0x4577E4u, gen::fn_datUnitCreatePc_002ff340);
                sw(v0, s1, 72);
                a0 = 9;
                a1 = 1536;
                a2 = 0;
                jal(ctx, 0x4577FCu, gen::fn_sub_316E00_00316e00);
                s3 = v0;
                a0 = s3;
                jal(ctx, 0x45780Cu, gen::fn_sub_31C1D0_0031c1d0);
                sw(s3, s1, 80);
                a0 = 6;
                sh(a0, s1, 424);
                jal(ctx, 0x457820u, gen::fn_sub_173300_00173300);
                v0 = v0 & 0xFF;
                sw(v0, s1, 388);
                sw(s2, s1, 360);
            }
            // 0x00457834
            charge(ctx, 2);
            v0 = 6;
            sb(v0, s0, kKyotoState);
        L_0045783c:
            charge(ctx, 6);
            a0 = 2;
            jal(ctx, 0x457840u, gen::fn_sub_457470_00457470);
            a2 = 1;
            if (v0 == a2) {
                // 0x00457854
                charge(ctx, 10);
                a0 = 0;
                a1 = 2;
                jal(ctx, 0x45785Cu, gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630);
                v1 = 0x870000;
                sw(v0, v1, -5236);  // 0x86EB8C
                v0 = 7;
                sb(v0, s0, kKyotoState);
            }
            goto L_00457954;
        case 0x45783Cu:  // table[6]
            goto L_0045783c;
        case 0x45787Cu:  // table[7]
            // 0x0045787c: states 6 / 7
            charge(ctx, 9);
            a0 = 17409;
            jal(ctx, 0x457880u, gen::fn_sub_3B5D10_003b5d10);
            s2 = v0;
            jal(ctx, 0x45788Cu, gen::fn_sub_457410_00457410);
            s1 = v0;
            if (s1 != 0) {
                // 0x004578a0
                charge(ctx, 21);
                a0 = 3;
                jal(ctx, 0x4578A4u, gen::fn_datUnitCreatePc_002ff340);
                sw(v0, s1, 72);
                a0 = 9;
                a1 = 768;
                a2 = 0;
                jal(ctx, 0x4578BCu, gen::fn_sub_316E00_00316e00);
                s3 = v0;
                a0 = s3;
                jal(ctx, 0x4578CCu, gen::fn_sub_31C1D0_0031c1d0);
                sw(s3, s1, 80);
                a0 = 3;
                sh(a0, s1, 424);
                jal(ctx, 0x4578E0u, gen::fn_sub_173300_00173300);
                v0 = v0 & 0xFF;
                sw(v0, s1, 388);
                sw(s2, s1, 360);
            }
            // 0x004578f4
            charge(ctx, 4);
            v0 = 8;
            sb(v0, s0, kKyotoState);
            goto L_00457954;
        case 0x457904u:  // table[8]
            // 0x00457904: state 8: NPC 3's think task
            charge(ctx, 6);
            a0 = 3;
            jal(ctx, 0x457908u, gen::fn_sub_457470_00457470);
            v1 = 1;
            if (v0 == v1) {
                // 0x0045791c
                charge(ctx, 11);
                a0 = 0;
                a1 = 3;
                a2 = 2;
                jal(ctx, 0x457928u, gen::fn_Y_Kyoto_CreateKyotoNpcThinkTask_00458630);
                v1 = 0x870000;
                sw(v0, v1, -4788);  // 0x86ED4C
                v0 = 9;
                sb(v0, s0, kKyotoState);
            }
            goto L_00457954;
        case 0x457948u:  // table[9]
            // 0x00457948: state 9: done (-1)
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00457958 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    goto L_00457954;
}

// 0x00457980 sub_457980 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [destroy callback of "Kyoto_NpcModeRead proc"] Frees the task's work (+60) through the RW free slot 0x96017C (a
// jalr tail).
void sub_457980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00457980
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x457994u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004579B0 Y_Kyoto_CreateKyotoNpcModeReadTask -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_CreateKyotoNpcModeReadTask] calloc(1, 1), the task "Kyoto_NpcModeRead proc" (priority 10, update
// Y_Kyoto_UpdateKyotoNpcModeReadTask, destroy sub_457980), state 0. Returns the task or 0.
// (K_Field_UpdateFieldRootTask.)
void Y_Kyoto_CreateKyotoNpcModeReadTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004579b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = a0;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x4579D8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004579f8
        charge(ctx, 12);
        a0 = s1;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 19248);  // "Kyoto_NpcModeRead proc"
        a3 = 0x450000;
        a3 = addiu(a3, 30176);  // &Y_Kyoto_UpdateKyotoNpcModeReadTask
        t0 = 0x450000;
        t0 = addiu(t0, 31104);  // &sub_457980
        t1 = s0;
        jal(ctx, 0x457A1Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sb(zero, s0, 0);
    } else {
        // 0x004579ec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00457a28 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00457A40 Y_Kyoto_UpdateKyotoNpcThinkTask -- 3004 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_UpdateKyotoNpcThinkTask] Nothing while paused. kKyotoCatch 1..8 (jump table 0x7BC6F0) steps the catch
// sequence: each step waits for its "y wait task" (frame counts from 0x6B4AB0) and re-checks the catch (sub_458CB0):
// the saved path, an event bit (sub_3BB010), the return walk to the home point (17410 / 17411 resources for NPCs 1 /
// 3), the mover steps restored, and when every other NPC is done (sub_459E00) all resume; 8 = sub_459790. Otherwise
// the route: 1 start the mover, 2 walk to waypoint n (pausing 60 frames at the 0x7BC610 ones) until 8 (lap + 1) or
// 32 waypoints, 3 when all NPCs are idle (sub_4589E0) the lap script (procedure lap + 17: the last lap from memory,
// with every NPC caught), 4 after it: next lap.
void Y_Kyoto_UpdateKyotoNpcThinkTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00457a40
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s2, a0, 60);
    lb(a1, s2, kKyotoIndex);
    v0 = sll(a1, 3);
    a2 = subu(v0, a1);
    v1 = sll(a2, 6);
    v0 = 0x870000;
    v0 = addiu(v0, -6496);  // &0x86E6A0
    s1 = addu(v0, v1);
    v1 = sll(a2, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, 19120);  // &0x6B4AB0
    s0 = addu(v0, v1);
    lb(v0, s2, kKyotoPaused);
    a2 = 1;
    if (v0 != a2) {
        // 0x00457aa8
        charge(ctx, 3);
        lb(v1, s2, kKyotoCatch);
        if (v1 != a2) {
            // 0x00457acc
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x00457b64
                charge(ctx, 3);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00457be8
                    charge(ctx, 3);
                    v0 = 4;
                    if (v1 != v0) {
                        // 0x00457c80
                        charge(ctx, 3);
                        v0 = 5;
                        if (v1 != v0) {
                            // 0x00457d04
                            charge(ctx, 3);
                            v0 = 6;
                            if (v1 != v0) {
                                // 0x00457e34
                                charge(ctx, 3);
                                v0 = 7;
                                if (v1 != v0) {
                                    // 0x00457f60
                                    charge(ctx, 3);
                                    v0 = 8;
                                    if (v1 != v0) {
                                        // 0x00457f80
                                        charge(ctx, 3);
                                        lw(v0, s2, kKyotoScriptTask);
                                        if (v0 == 0) {
                                            // 0x00457f8c
                                            charge(ctx, 5);
                                            jal(ctx, 0x457F8Cu, gen::fn_sub_458CB0_00458cb0);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_00457fac;
                                            }
                                            // 0x00457fa0
                                            charge(ctx, 3);
                                            v0 = 0;
                                            // 0x004585dc (the shared epilogue, written out on this path)
                                            charge(ctx, 8);
                                            ld(ra, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x60);
                                            return;
                                        }
                                    L_00457fac:
                                        charge(ctx, 4);
                                        lb(v0, s2, kKyotoState);
                                        at = sltiu(v0, 7);
                                        if (at != 0) {
                                            // 0x00457fbc
                                            charge(ctx, 7);
                                            v1 = 0x7C0000;
                                            v1 = addiu(v1, -14608);  // &0x7BC6F0
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, v1);
                                            lw(v0, v0, 0);
                                            switch (v0.u()) {
                                            case 0x457FD8u:  // table[1]
                                                // 0x00457fd8: catch step 1: wait
                                                charge(ctx, 4);
                                                lb(v1, s2, kKyotoRoute);
                                                v0 = 2;
                                                if (v1 != v0) {
                                                    // 0x00457fe8
                                                    charge(ctx, 9);
                                                    sh(zero, s2, kKyotoWaypoint);
                                                    lw(a0, s1, 368);
                                                    a1 = 1;
                                                    jal(ctx, 0x457FF4u, gen::fn_sub_1B0240_001b0240);
                                                    v0 = 2;
                                                    sb(v0, s2, kKyotoState);
                                                }
                                                break;
                                            case 0x45800Cu:  // table[2]
                                                // 0x0045800c: catch step 2
                                                charge(ctx, 4);
                                                lb(v1, s2, kKyotoIndex);
                                                v0 = 3;
                                                if (v1 != v0) {
                                                    // 0x0045801c
                                                    charge(ctx, 3);
                                                    v0 = 2;
                                                    if (v1 == v0) {
                                                        // 0x00458160
                                                        charge(ctx, 8);
                                                        lh(v0, s2, kKyotoWaypoint);
                                                        v0 = v0 & 0x3FF;
                                                        v0 = v0 | 0x4000;
                                                        a0 = v0 & 0xFFFF;
                                                        jal(ctx, 0x458170u, gen::fn_sub_3B5D10_003b5d10);
                                                        if (v0 != 0) {
                                                            // 0x00458180
                                                            charge(ctx, 4);
                                                            lb(v1, s2, kKyotoWaiting);
                                                            v0 = 1;
                                                            if (v1 != v0) {
                                                                // 0x004581d0
                                                                charge(ctx, 29);
                                                                lh(v0, s2, kKyotoWaypoint);
                                                                v0 = v0 & 0x3FF;
                                                                v0 = v0 | 0x4000;
                                                                a0 = v0 & 0xFFFF;
                                                                jal(ctx, 0x4581E0u, gen::fn_sub_3B5D10_003b5d10);
                                                                lwc1(f2, v0, 256);
                                                                lwc1(f1, v0, 260);
                                                                lwc1(f0, v0, 264);
                                                                swc1(f2, sp, 0x50);
                                                                swc1(f1, sp, 0x54);
                                                                swc1(f0, sp, 0x58);
                                                                lw(a0, s1, 368);
                                                                a1 = 5;
                                                                jal(ctx, 0x458208u, gen::fn_sub_1B0250_001b0250);
                                                                lb(v0, s2, kKyotoLap);
                                                                v1 = sll(v0, 2);
                                                                v0 = 0x7C0000;
                                                                v0 = addiu(v0, -14672);  // &0x7BC6B0
                                                                v0 = addu(v0, v1);
                                                                lwc1(f0, v0, 0);
                                                                cvt_s_w(f12, f0);
                                                                lw(a0, s1, 368);
                                                                a1 = addiu(sp, 0x50);
                                                                jal(ctx, 0x458234u, gen::fn_sub_1AFA20_001afa20);
                                                                if (v0 != 0) {
                                                                    // 0x00458244
                                                                    charge(ctx, 10);
                                                                    lh(v0, s2, kKyotoSteps);
                                                                    v0 = addiu(v0, 1);
                                                                    sh(v0, s2, kKyotoSteps);
                                                                    lb(a1, s2, kKyotoWaypoint);
                                                                    lb(a0, s2, kKyotoIndex);
                                                                    jal(ctx, 0x458258u, gen::fn_sub_458A80_00458a80);
                                                                    v1 = 1;
                                                                    if (v0 == v1) {
                                                                        // 0x0045826c
                                                                        charge(ctx, 2);
                                                                        sb(v1, s2, kKyotoWaiting);
                                                                        sh(zero, s2, kKyotoWaitFrames);
                                                                    }
                                                                    // 0x00458274
                                                                    charge(ctx, 3);
                                                                    lh(v0, s2, kKyotoWaypoint);
                                                                    v0 = addiu(v0, 1);
                                                                    sh(v0, s2, kKyotoWaypoint);
                                                                }
                                                            } else {
                                                                // 0x00458190
                                                                charge(ctx, 5);
                                                                lw(a0, s1, 368);
                                                                jal(ctx, 0x458194u, gen::fn_sub_1B0220_001b0220);
                                                                if (v0 == 0) {
                                                                    // 0x004581a4
                                                                    charge(ctx, 4);
                                                                    lh(v1, s2, kKyotoWaitFrames);
                                                                    v0 = slti(v1, 60);
                                                                    if (v0 != 0) {
                                                                        // 0x004581c0
                                                                        charge(ctx, 4);
                                                                        v0 = addiu(v1, 1);
                                                                        sh(v0, s2, kKyotoWaitFrames);
                                                                    } else {
                                                                        // 0x004581b4
                                                                        charge(ctx, 3);
                                                                        sb(zero, s2, kKyotoWaiting);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        // 0x00458028
                                                        charge(ctx, 3);
                                                        v0 = 1;
                                                        if (v1 != v0) {
                                                            // 0x00458034
                                                            charge(ctx, 2);
                                                            if (v1 == 0) {
                                                                // 0x00458044
                                                                charge(ctx, 8);
                                                                lh(v0, s2, kKyotoWaypoint);
                                                                v0 = v0 & 0x3FF;
                                                                v0 = v0 | 0x3C00;
                                                                a0 = v0 & 0xFFFF;
                                                                jal(ctx, 0x458054u, gen::fn_sub_3B5D10_003b5d10);
                                                                if (v0 != 0) {
                                                                    // 0x00458064
                                                                    charge(ctx, 4);
                                                                    lb(v1, s2, kKyotoWaiting);
                                                                    v0 = 1;
                                                                    if (v1 != v0) {
                                                                        // 0x004580b4
                                                                        charge(ctx, 29);
                                                                        lh(v0, s2, kKyotoWaypoint);
                                                                        v0 = v0 & 0x3FF;
                                                                        v0 = v0 | 0x3C00;
                                                                        a0 = v0 & 0xFFFF;
                                                                        jal(ctx, 0x4580C4u, gen::fn_sub_3B5D10_003b5d10);
                                                                        lwc1(f2, v0, 256);
                                                                        lwc1(f1, v0, 260);
                                                                        lwc1(f0, v0, 264);
                                                                        swc1(f2, sp, 0x50);
                                                                        swc1(f1, sp, 0x54);
                                                                        swc1(f0, sp, 0x58);
                                                                        lw(a0, s1, 368);
                                                                        a1 = 5;
                                                                        jal(ctx, 0x4580ECu, gen::fn_sub_1B0250_001b0250);
                                                                        lb(v0, s2, kKyotoLap);
                                                                        v1 = sll(v0, 2);
                                                                        v0 = 0x7C0000;
                                                                        v0 = addiu(v0, -14672);  // &0x7BC6B0
                                                                        v0 = addu(v0, v1);
                                                                        lwc1(f0, v0, 0);
                                                                        cvt_s_w(f12, f0);
                                                                        lw(a0, s1, 368);
                                                                        a1 = addiu(sp, 0x50);
                                                                        jal(ctx, 0x458118u, gen::fn_sub_1AFA20_001afa20);
                                                                        if (v0 != 0) {
                                                                            // 0x00458128
                                                                            charge(ctx, 7);
                                                                            lb(a1, s2, kKyotoWaypoint);
                                                                            lb(a0, s2, kKyotoIndex);
                                                                            jal(ctx, 0x458130u, gen::fn_sub_458A80_00458a80);
                                                                            v1 = 1;
                                                                            if (v0 == v1) {
                                                                                // 0x00458144
                                                                                charge(ctx, 2);
                                                                                sb(v1, s2, kKyotoWaiting);
                                                                                sh(zero, s2, kKyotoWaitFrames);
                                                                            }
                                                                            // 0x0045814c
                                                                            charge(ctx, 5);
                                                                            lh(v0, s2, kKyotoWaypoint);
                                                                            v0 = addiu(v0, 1);
                                                                            sh(v0, s2, kKyotoWaypoint);
                                                                        }
                                                                    } else {
                                                                        // 0x00458074
                                                                        charge(ctx, 5);
                                                                        lw(a0, s1, 368);
                                                                        jal(ctx, 0x458078u, gen::fn_sub_1B0220_001b0220);
                                                                        if (v0 == 0) {
                                                                            // 0x00458088
                                                                            charge(ctx, 4);
                                                                            lh(v1, s2, kKyotoWaitFrames);
                                                                            v0 = slti(v1, 60);
                                                                            if (v0 != 0) {
                                                                                // 0x004580a4
                                                                                charge(ctx, 4);
                                                                                v0 = addiu(v1, 1);
                                                                                sh(v0, s2, kKyotoWaitFrames);
                                                                            } else {
                                                                                // 0x00458098
                                                                                charge(ctx, 3);
                                                                                sb(zero, s2, kKyotoWaiting);
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                // 0x0045803c
                                                                charge(ctx, 2);
                                                            }
                                                        }
                                                    }
                                                }
                                                // 0x00458280
                                                charge(ctx, 4);
                                                lb(a0, s2, kKyotoLap);
                                                v0 = 2;
                                                if (a0 != v0) {
                                                    // 0x004582b8
                                                    charge(ctx, 6);
                                                    lh(v1, s2, kKyotoWaypoint);
                                                    v0 = addiu(a0, 1);
                                                    v0 = sll(v0, 3);
                                                    v0 = slt(v1, v0);
                                                    if (v0 == 0) {
                                                        // 0x004582d0
                                                        charge(ctx, 4);
                                                        v0 = 3;
                                                        sb(v0, s2, kKyotoState);
                                                    }
                                                } else {
                                                    // 0x00458290
                                                    charge(ctx, 6);
                                                    lh(v1, s2, kKyotoWaypoint);
                                                    v0 = addiu(a0, 2);
                                                    v0 = sll(v0, 3);
                                                    v0 = slt(v1, v0);
                                                    if (v0 == 0) {
                                                        // 0x004582a8
                                                        charge(ctx, 4);
                                                        v0 = 3;
                                                        sb(v0, s2, kKyotoState);
                                                    }
                                                }
                                                break;
                                            case 0x4582E0u:  // table[3]
                                                // 0x004582e0: catch step 3
                                                charge(ctx, 3);
                                                lb(v0, s2, kKyotoIndex);
                                                if (v0 == 0) {
                                                    // 0x004582ec
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x4582ECu, gen::fn_sub_4589E0_004589e0);
                                                    v1 = 1;
                                                    if (v0 == v1) {
                                                        // 0x00458300
                                                        charge(ctx, 3);
                                                        lw(v0, s2, kKyotoScriptTask);
                                                        if (v0 != 0) {
                                                            // 0x0045830c
                                                            charge(ctx, 1);
                                                            sw(zero, s2, kKyotoScriptTask);
                                                        }
                                                        // 0x00458310
                                                        charge(ctx, 4);
                                                        lb(v1, s2, kKyotoLap);
                                                        v0 = 2;
                                                        if (v1 == v0) {
                                                            // 0x004583fc
                                                            charge(ctx, 5);
                                                            jal(ctx, 0x4583FCu, gen::fn_sub_459D60_00459d60);
                                                            s0 = 0;
                                                            for (;;) {
                                                                // 0x00458448
                                                                charge(ctx, 3);
                                                                v0 = slti(s0, 4);
                                                                if (v0 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                                // 0x00458410
                                                                charge(ctx, 14);
                                                                v0 = sll(s0, 3);
                                                                v0 = subu(v0, s0);
                                                                v1 = sll(v0, 6);
                                                                v0 = 0x870000;
                                                                v0 = addiu(v0, -6496);  // &0x86E6A0
                                                                s1 = addu(v0, v1);
                                                                lw(a0, s1, 368);
                                                                a1 = 1;
                                                                jal(ctx, 0x458430u, gen::fn_sub_1B0260_001b0260);
                                                                lw(a0, s1, 364);
                                                                jal(ctx, 0x45843Cu, gen::fn_sub_458870_00458870);
                                                                s0 = addiu(s0, 1);
                                                            }
                                                            // 0x00458454
                                                            charge(ctx, 3);
                                                            lw(v0, s2, kKyotoScriptTask);
                                                            if (v0 != 0) {
                                                                // 0x00458460
                                                                charge(ctx, 1);
                                                                sw(zero, s2, kKyotoScriptTask);
                                                            }
                                                            // 0x00458464
                                                            charge(ctx, 35);
                                                            jal(ctx, 0x458464u, gen::fn_K_Field_Get_001b9120);
                                                            s0 = v0;
                                                            jal(ctx, 0x458470u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a2, v0, 4172);
                                                            lb(v0, s2, kKyotoLap);
                                                            a3 = addiu(v0, 17);
                                                            a0 = 10;
                                                            lw(a1, s0, 4168);
                                                            jal(ctx, 0x45848Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                            sw(v0, s2, kKyotoScriptTask);
                                                            jal(ctx, 0x458498u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 12);
                                                            a1 = 1;
                                                            jal(ctx, 0x4584A8u, gen::fn_sub_1E1360_001e1360);
                                                            jal(ctx, 0x4584B0u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 36);
                                                            a1 = 1;
                                                            jal(ctx, 0x4584C0u, gen::fn_sub_1D3810_001d3810);
                                                            jal(ctx, 0x4584C8u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 8);
                                                            a1 = 1;
                                                            jal(ctx, 0x4584D8u, gen::fn_sub_1CD670_001cd670);
                                                            v0 = 5;
                                                            sb(v0, s2, kKyotoState);
                                                        } else {
                                                            // 0x00458320
                                                            charge(ctx, 3);
                                                            s0 = 0;
                                                            for (;;) {
                                                                // 0x00458374
                                                                charge(ctx, 3);
                                                                v0 = slti(s0, 4);
                                                                if (v0 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                                // 0x0045832c
                                                                charge(ctx, 3);
                                                                lb(v0, s2, kKyotoIndex);
                                                                if (v0 != s0) {
                                                                    // 0x00458338
                                                                    charge(ctx, 14);
                                                                    v0 = sll(s0, 3);
                                                                    v0 = subu(v0, s0);
                                                                    v1 = sll(v0, 6);
                                                                    v0 = 0x870000;
                                                                    v0 = addiu(v0, -6496);  // &0x86E6A0
                                                                    s1 = addu(v0, v1);
                                                                    lw(a0, s1, 368);
                                                                    a1 = 1;
                                                                    jal(ctx, 0x458358u, gen::fn_sub_1B0260_001b0260);
                                                                    lw(a0, s1, 364);
                                                                    a1 = 1;
                                                                    jal(ctx, 0x458368u, gen::fn_sub_4589D0_004589d0);
                                                                }
                                                                // 0x00458370
                                                                charge(ctx, 1);
                                                                s0 = addiu(s0, 1);
                                                            }
                                                            // 0x00458380
                                                            charge(ctx, 31);
                                                            jal(ctx, 0x458380u, gen::fn_K_Field_Get_001b9120);
                                                            lb(v1, s2, kKyotoLap);
                                                            a2 = addiu(v1, 17);
                                                            a0 = 10;
                                                            lw(a1, v0, 4168);
                                                            jal(ctx, 0x458398u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                                                            sw(v0, s2, kKyotoScriptTask);
                                                            jal(ctx, 0x4583A4u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 12);
                                                            a1 = 1;
                                                            jal(ctx, 0x4583B4u, gen::fn_sub_1E1360_001e1360);
                                                            jal(ctx, 0x4583BCu, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 36);
                                                            a1 = 1;
                                                            jal(ctx, 0x4583CCu, gen::fn_sub_1D3810_001d3810);
                                                            jal(ctx, 0x4583D4u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, 8);
                                                            a1 = 1;
                                                            jal(ctx, 0x4583E4u, gen::fn_sub_1CD670_001cd670);
                                                            v0 = 4;
                                                            sb(v0, s2, kKyotoState);
                                                        }
                                                    }
                                                }
                                                break;
                                            case 0x4584F0u:  // table[4]
                                                // 0x004584f0: catch step 4
                                                charge(ctx, 5);
                                                lw(a0, s2, kKyotoScriptTask);
                                                jal(ctx, 0x4584F4u, gen::fn_kwlnTaskExists_00195460);
                                                if (v0 == 0) {
                                                    // 0x00458504
                                                    charge(ctx, 23);
                                                    sw(zero, s2, kKyotoScriptTask);
                                                    jal(ctx, 0x458508u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, 12);
                                                    a1 = 0;
                                                    jal(ctx, 0x458518u, gen::fn_sub_1E1360_001e1360);
                                                    jal(ctx, 0x458520u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, 36);
                                                    a1 = 0;
                                                    jal(ctx, 0x458530u, gen::fn_sub_1D3810_001d3810);
                                                    jal(ctx, 0x458538u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, 8);
                                                    a1 = 0;
                                                    jal(ctx, 0x458548u, gen::fn_sub_1CD670_001cd670);
                                                    lb(v1, s2, kKyotoLap);
                                                    v0 = 2;
                                                    if (v1 != v0) {
                                                        // 0x00458570
                                                        charge(ctx, 5);
                                                        jal(ctx, 0x458570u, gen::fn_sub_458B00_00458b00);
                                                        s0 = 0;
                                                        for (;;) {
                                                            // 0x004585cc
                                                            charge(ctx, 3);
                                                            v0 = slti(s0, 4);
                                                            if (v0 == 0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                            // 0x00458584
                                                            charge(ctx, 3);
                                                            lb(v0, s2, kKyotoIndex);
                                                            if (v0 != s0) {
                                                                // 0x00458590
                                                                charge(ctx, 14);
                                                                v0 = sll(s0, 3);
                                                                v0 = subu(v0, s0);
                                                                v1 = sll(v0, 6);
                                                                v0 = 0x870000;
                                                                v0 = addiu(v0, -6496);  // &0x86E6A0
                                                                s1 = addu(v0, v1);
                                                                lw(a0, s1, 368);
                                                                a1 = 0;
                                                                jal(ctx, 0x4585B0u, gen::fn_sub_1B0260_001b0260);
                                                                lw(a0, s1, 364);
                                                                a1 = 0;
                                                                jal(ctx, 0x4585C0u, gen::fn_sub_4589D0_004589d0);
                                                            }
                                                            // 0x004585c8
                                                            charge(ctx, 1);
                                                            s0 = addiu(s0, 1);
                                                        }
                                                    } else {
                                                        // 0x00458560
                                                        charge(ctx, 4);
                                                        jal(ctx, 0x458560u, gen::fn_sub_458B60_00458b60);
                                                    }
                                                }
                                                break;
                                            case 0x4585D8u:  // table[0, 5, 6]
                                                break;
                                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                                tail(ctx, v0.u());
                                                return;
                                            }
                                        }
                                        // 0x004585d8
                                        charge(ctx, 1);
                                        v0 = 0;
                                    } else {
                                        // 0x00457f6c
                                        charge(ctx, 5);
                                        jal(ctx, 0x457F6Cu, gen::fn_sub_459790_00459790);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x00457e40
                                    charge(ctx, 6);
                                    a2 = 0;
                                    jal(ctx, 0x457E44u, gen::fn_sub_458CB0_00458cb0);
                                    v1 = 1;
                                    if (v0 != v1) {
                                        // 0x00457e64
                                        charge(ctx, 5);
                                        lw(a0, s2, kKyotoWaitTask);
                                        jal(ctx, 0x457E68u, gen::fn_kwlnTaskExists_00195460);
                                        if (v0 == 0) {
                                            // 0x00457e78
                                            charge(ctx, 4);
                                            sw(zero, s2, kKyotoWaitTask);
                                            s0 = 0;
                                            for (;;) {
                                                // 0x00457eb0
                                                charge(ctx, 4);
                                                lh(a1, s2, kKyotoMoveCount);
                                                v0 = slt(s0, a1);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x00457e88
                                                charge(ctx, 10);
                                                v0 = sll(s0, 1);
                                                v0 = addu(v0, s0);
                                                v0 = sll(v0, 3);
                                                v0 = addu(s2, v0);
                                                lw(a0, s1, 368);
                                                a1 = s0;
                                                a2 = addiu(v0, 44);
                                                jal(ctx, 0x457EA4u, gen::fn_sub_1B01D0_001b01d0);
                                                s0 = addiu(s0, 1);
                                            }
                                            // 0x00457ec0
                                            charge(ctx, 13);
                                            lw(a0, s1, 368);
                                            jal(ctx, 0x457EC4u, gen::fn_sub_1B0230_001b0230);
                                            lw(a0, s1, 368);
                                            a1 = 1;
                                            jal(ctx, 0x457ED4u, gen::fn_sub_1B0260_001b0260);
                                            lb(a0, s2, kKyotoIndex);
                                            jal(ctx, 0x457EE0u, gen::fn_sub_459E00_00459e00);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                // 0x00457f4c
                                                charge(ctx, 2);
                                                v0 = 8;
                                                sb(v0, s2, kKyotoCatch);
                                            } else {
                                                // 0x00457ef4
                                                charge(ctx, 3);
                                                s0 = 0;
                                                for (;;) {
                                                    // 0x00457f38
                                                    charge(ctx, 3);
                                                    v0 = slti(s0, 4);
                                                    if (v0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                    // 0x00457f00
                                                    charge(ctx, 14);
                                                    v0 = sll(s0, 3);
                                                    v0 = subu(v0, s0);
                                                    v1 = sll(v0, 6);
                                                    v0 = 0x870000;
                                                    v0 = addiu(v0, -6496);  // &0x86E6A0
                                                    s1 = addu(v0, v1);
                                                    lw(a0, s1, 368);
                                                    a1 = 0;
                                                    jal(ctx, 0x457F20u, gen::fn_sub_1B0260_001b0260);
                                                    lw(a0, s1, 364);
                                                    jal(ctx, 0x457F2Cu, gen::fn_sub_458920_00458920);
                                                    s0 = addiu(s0, 1);
                                                }
                                                // 0x00457f44
                                                charge(ctx, 2);
                                            }
                                        }
                                        // 0x00457f54
                                        charge(ctx, 3);
                                        v0 = 0;
                                    } else {
                                        // 0x00457e58
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                }
                            } else {
                                // 0x00457d10
                                charge(ctx, 6);
                                a2 = 0;
                                jal(ctx, 0x457D14u, gen::fn_sub_458CB0_00458cb0);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x00457d34
                                    charge(ctx, 5);
                                    lw(a0, s2, kKyotoWaitTask);
                                    jal(ctx, 0x457D38u, gen::fn_kwlnTaskExists_00195460);
                                    if (v0 == 0) {
                                        // 0x00457d48
                                        charge(ctx, 4);
                                        lb(v1, s2, kKyotoIndex);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            // 0x00457d98
                                            charge(ctx, 3);
                                            v0 = 3;
                                            if (v1 != v0) {
                                                // 0x00457de4
                                                charge(ctx, 5);
                                                lh(a2, s0, 22);
                                                lw(a0, s1, 368);
                                                a1 = addiu(s2, kKyotoHomePosX);
                                                jal(ctx, 0x457DF0u, gen::fn_sub_1B0020_001b0020);
                                            } else {
                                                // 0x00457da4
                                                charge(ctx, 16);
                                                a0 = 17411;
                                                jal(ctx, 0x457DA8u, gen::fn_sub_3B5D10_003b5d10);
                                                a1 = addiu(sp, 0x50);
                                                lwc1(f2, v0, 256);
                                                lwc1(f1, v0, 260);
                                                lwc1(f0, v0, 264);
                                                swc1(f2, sp, 0x50);
                                                swc1(f1, sp, 0x54);
                                                swc1(f0, sp, 0x58);
                                                lh(a2, s0, 22);
                                                lw(a0, s1, 368);
                                                jal(ctx, 0x457DD4u, gen::fn_sub_1B0020_001b0020);
                                            }
                                        } else {
                                            // 0x00457d58
                                            charge(ctx, 16);
                                            a0 = 17410;
                                            jal(ctx, 0x457D5Cu, gen::fn_sub_3B5D10_003b5d10);
                                            a1 = addiu(sp, 0x50);
                                            lwc1(f2, v0, 256);
                                            lwc1(f1, v0, 260);
                                            lwc1(f0, v0, 264);
                                            swc1(f2, sp, 0x50);
                                            swc1(f1, sp, 0x54);
                                            swc1(f0, sp, 0x58);
                                            lh(a2, s0, 22);
                                            lw(a0, s1, 368);
                                            jal(ctx, 0x457D88u, gen::fn_sub_1B0020_001b0020);
                                        }
                                        // 0x00457df8
                                        charge(ctx, 5);
                                        v0 = 7;
                                        sb(v0, s2, kKyotoCatch);
                                        lw(v0, s2, kKyotoWaitTask);
                                        if (v0 != 0) {
                                            // 0x00457e0c
                                            charge(ctx, 1);
                                            sw(zero, s2, kKyotoWaitTask);
                                        }
                                        // 0x00457e10
                                        charge(ctx, 6);
                                        a0 = s3;
                                        lh(a1, s0, 22);
                                        a2 = 0;
                                        jal(ctx, 0x457E1Cu, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                                        sw(v0, s2, kKyotoWaitTask);
                                    }
                                    // 0x00457e28
                                    charge(ctx, 3);
                                    v0 = 0;
                                } else {
                                    // 0x00457d28
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                            }
                        } else {
                            // 0x00457c8c
                            charge(ctx, 6);
                            a2 = 0;
                            jal(ctx, 0x457C90u, gen::fn_sub_458CB0_00458cb0);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x00457cb0
                                charge(ctx, 5);
                                lw(a0, s2, kKyotoWaitTask);
                                jal(ctx, 0x457CB4u, gen::fn_kwlnTaskExists_00195460);
                                if (v0 == 0) {
                                    // 0x00457cc4
                                    charge(ctx, 6);
                                    sw(zero, s2, kKyotoWaitTask);
                                    v0 = 6;
                                    sb(v0, s2, kKyotoCatch);
                                    lw(v0, s2, kKyotoWaitTask);
                                    if (v0 != 0) {
                                        // 0x00457cdc
                                        charge(ctx, 1);
                                        sw(zero, s2, kKyotoWaitTask);
                                    }
                                    // 0x00457ce0
                                    charge(ctx, 6);
                                    a0 = s3;
                                    lh(a1, s0, 20);
                                    a2 = 0;
                                    jal(ctx, 0x457CECu, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                                    sw(v0, s2, kKyotoWaitTask);
                                }
                                // 0x00457cf8
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x00457ca4
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        }
                    } else {
                        // 0x00457bf4
                        charge(ctx, 6);
                        a2 = 0;
                        jal(ctx, 0x457BF8u, gen::fn_sub_458CB0_00458cb0);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x00457c18
                            charge(ctx, 5);
                            lw(a0, s2, kKyotoWaitTask);
                            jal(ctx, 0x457C1Cu, gen::fn_kwlnTaskExists_00195460);
                            if (v0 == 0) {
                                // 0x00457c2c
                                charge(ctx, 11);
                                sw(zero, s2, kKyotoWaitTask);
                                lw(v0, s1, 84);
                                lhu(a0, v0, 0);
                                a1 = 2;
                                jal(ctx, 0x457C3Cu, gen::fn_sub_3BB010_003bb010);
                                v0 = 5;
                                sb(v0, s2, kKyotoCatch);
                                lw(v0, s2, kKyotoWaitTask);
                                if (v0 != 0) {
                                    // 0x00457c58
                                    charge(ctx, 1);
                                    sw(zero, s2, kKyotoWaitTask);
                                }
                                // 0x00457c5c
                                charge(ctx, 6);
                                a0 = s3;
                                lh(a1, s0, 24);
                                a2 = 0;
                                jal(ctx, 0x457C68u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                                sw(v0, s2, kKyotoWaitTask);
                            }
                            // 0x00457c74
                            charge(ctx, 3);
                            v0 = 0;
                        } else {
                            // 0x00457c0c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    }
                } else {
                    // 0x00457b70
                    charge(ctx, 6);
                    a2 = 0;
                    jal(ctx, 0x457B74u, gen::fn_sub_458CB0_00458cb0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x00457b94
                        charge(ctx, 5);
                        lw(a0, s2, kKyotoWaitTask);
                        jal(ctx, 0x457B98u, gen::fn_kwlnTaskExists_00195460);
                        if (v0 == 0) {
                            // 0x00457ba8
                            charge(ctx, 6);
                            sw(zero, s2, kKyotoWaitTask);
                            v0 = 4;
                            sb(v0, s2, kKyotoCatch);
                            lw(v0, s2, kKyotoWaitTask);
                            if (v0 != 0) {
                                // 0x00457bc0
                                charge(ctx, 1);
                                sw(zero, s2, kKyotoWaitTask);
                            }
                            // 0x00457bc4
                            charge(ctx, 6);
                            a0 = s3;
                            lh(a1, s0, 24);
                            a2 = 0;
                            jal(ctx, 0x457BD0u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                            sw(v0, s2, kKyotoWaitTask);
                        }
                        // 0x00457bdc
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x00457b88
                        charge(ctx, 3);
                        v0 = 0;
                    }
                }
            } else {
                // 0x00457ad8
                charge(ctx, 6);
                a2 = 0;
                jal(ctx, 0x457ADCu, gen::fn_sub_458CB0_00458cb0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x00457afc
                    charge(ctx, 5);
                    lw(a0, s2, kKyotoWaitTask);
                    jal(ctx, 0x457B00u, gen::fn_kwlnTaskExists_00195460);
                    if (v0 == 0) {
                        // 0x00457b10
                        charge(ctx, 11);
                        sw(zero, s2, kKyotoWaitTask);
                        lh(a2, s0, 22);
                        lw(a0, s1, 368);
                        a1 = addiu(s2, kKyotoSavedPosX);
                        jal(ctx, 0x457B20u, gen::fn_sub_1B0020_001b0020);
                        v0 = 3;
                        sb(v0, s2, kKyotoCatch);
                        lw(v0, s2, kKyotoWaitTask);
                        if (v0 != 0) {
                            // 0x00457b3c
                            charge(ctx, 1);
                            sw(zero, s2, kKyotoWaitTask);
                        }
                        // 0x00457b40
                        charge(ctx, 6);
                        a0 = s3;
                        lh(a1, s0, 22);
                        a2 = 0;
                        jal(ctx, 0x457B4Cu, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
                        sw(v0, s2, kKyotoWaitTask);
                    }
                    // 0x00457b58
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x00457af0
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
        } else {
            // 0x00457ab4
            charge(ctx, 6);
            lw(a0, s2, kKyotoWaitTask);
            jal(ctx, 0x457AB8u, gen::fn_kwlnTaskExists_00195460);
            v0 = 0;
        }
    } else {
        // 0x00457a9c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004585dc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00458600 sub_458600 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [destroy callback of "Kyoto_NpcThink proc"] Frees the task's work (+60) through the RW free slot 0x96017C (a jalr
// tail).
void sub_458600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00458600
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x458614u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00458630 Y_Kyoto_CreateKyotoNpcThinkTask -- 536 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_CreateKyotoNpcThinkTask] ($a0 parent, $a1 NPC slot, $a2 route) calloc(1, 1204), the task "Kyoto_NpcThink
// proc" (priority 10, destroy sub_458600), the fields cleared, and two field markers (sub_1A5320 .. sub_1A56B0) on
// the NPC's model, red and green, 50 above. Returns the task or 0.
void Y_Kyoto_CreateKyotoNpcThinkTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00458630
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s5 = a1;
    s4 = a2;
    v1 = dsll32(s5, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 3);
    a0 = subu(v0, v1);
    v1 = sll(a0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, -6496);  // &0x86E6A0
    s1 = addu(v0, v1);
    v1 = sll(a0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, 19120);  // &0x6B4AB0
    s0 = addu(v0, v1);
    a0 = 1;
    a1 = 1204;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x4586A0u, v0.u());
    s2 = v0;
    if (s2 != 0) {
        // 0x004586c0
        charge(ctx, 88);
        a0 = s3;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 19280);  // "Kyoto_NpcThink proc"
        a3 = 0x450000;
        a3 = addiu(a3, 31296);  // &Y_Kyoto_UpdateKyotoNpcThinkTask
        t0 = 0x460000;
        t0 = addiu(t0, -31232);  // &sub_458600
        t1 = s2;
        jal(ctx, 0x4586E4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s3 = v0;
        sb(zero, s2, kKyotoState);
        sb(s4, s2, kKyotoRoute);
        sb(s5, s2, kKyotoIndex);
        sb(zero, s2, kKyotoLap);
        sb(zero, s2, kKyotoCatch);
        sb(zero, s2, kKyotoWaiting);
        sh(zero, s2, kKyotoWaitFrames);
        sw(zero, s2, kKyotoWaitTask);
        sh(zero, s2, kKyotoSteps);
        sb(zero, s2, kKyotoPaused);
        v0 = 0x42480000;
        sw(v0, sp, 0x7C);
        sw(zero, sp, 0x80);
        sw(zero, sp, 0x78);
        v1 = 255;
        sb(v1, sp, 0x8C);
        sb(zero, sp, 0x8D);
        sb(zero, sp, 0x8E);
        v0 = 128;
        sb(v0, sp, 0x8F);
        sb(zero, sp, 0x88);
        sb(v1, sp, 0x89);
        sb(zero, sp, 0x8A);
        sb(v0, sp, 0x8B);
        a0 = s3;
        jal(ctx, 0x458754u, gen::fn_sub_1A5320_001a5320);
        sw(v0, s2, kKyotoMarkerA);
        a0 = v0;
        lw(a1, s1, 80);
        jal(ctx, 0x458768u, gen::fn_sub_1A56C0_001a56c0);
        lw(a0, s2, kKyotoMarkerA);
        a1 = addiu(sp, 0x8C);
        jal(ctx, 0x458778u, gen::fn_sub_1A5700_001a5700);
        lw(a0, s2, kKyotoMarkerA);
        a1 = addiu(sp, 0x78);
        jal(ctx, 0x458788u, gen::fn_sub_1A56D0_001a56d0);
        lw(a0, s2, kKyotoMarkerA);
        lwc1(f12, s0, 8);
        lwc1(f13, s0, 4);
        jal(ctx, 0x45879Cu, gen::fn_sub_1A57A0_001a57a0);
        lw(a0, s2, kKyotoMarkerA);
        a1 = 0;
        jal(ctx, 0x4587ACu, gen::fn_sub_1A56B0_001a56b0);
        a0 = s3;
        jal(ctx, 0x4587B8u, gen::fn_sub_1A5320_001a5320);
        sw(v0, s2, kKyotoMarkerB);
        a0 = v0;
        lw(a1, s1, 80);
        jal(ctx, 0x4587CCu, gen::fn_sub_1A56C0_001a56c0);
        lw(a0, s2, kKyotoMarkerB);
        a1 = addiu(sp, 0x88);
        jal(ctx, 0x4587DCu, gen::fn_sub_1A5700_001a5700);
        lw(a0, s2, kKyotoMarkerB);
        a1 = addiu(sp, 0x78);
        jal(ctx, 0x4587ECu, gen::fn_sub_1A56D0_001a56d0);
        v0 = 0x43B40000;
        mtc1(v0, f12);
        lw(a0, s2, kKyotoMarkerB);
        lwc1(f13, s0, 0);
        jal(ctx, 0x458804u, gen::fn_sub_1A57A0_001a57a0);
        lw(a0, s2, kKyotoMarkerB);
        a1 = 0;
        jal(ctx, 0x458814u, gen::fn_sub_1A56B0_001a56b0);
        v0 = s3;
    } else {
        // 0x004586b4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00458820 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00458850 sub_458850 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_Start] Work +0 = 1. (The COMM handler sub_425360.)
void sub_458850(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00458850
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, 60);
    sb(a1, v1, kKyotoState);
}

// 0x00458870 sub_458870 -- 20 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_SetCaught] Work +7 = 1.
void sub_458870(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00458870
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, 60);
    sb(a1, v1, kKyotoCatch);
}

// 0x00458890 sub_458890 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_PauseAll] For the 4 NPC units with a DatUnit: mover paused (sub_1B0260(+368, 1)) and kKyotoPaused = 1.
// (Field event task.)
void sub_458890(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00458890
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x004588f4
        charge(ctx, 3);
        v1 = slti(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004588ac
        charge(ctx, 9);
        v1 = sll(s0, 3);
        v1 = subu(v1, s0);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, -6496);  // &0x86E6A0
        s1 = addu(v1, a0);
        lw(v1, s1, 72);
        if (v1 != 0) {
            // 0x004588d0
            charge(ctx, 8);
            lw(a0, s1, 368);
            a1 = 1;
            jal(ctx, 0x4588D8u, gen::fn_sub_1B0260_001b0260);
            lw(a0, s1, 364);
            a1 = 1;
            jal(ctx, 0x4588E8u, gen::fn_sub_4589D0_004589d0);
        }
        // 0x004588f0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00458900
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00458920 sub_458920 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_ClearCaught] Work +7 = 0.
void sub_458920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00458920
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sb(zero, v1, kKyotoCatch);
}

// 0x00458930 sub_458930 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_ResumeAll] For the 4 NPC units with a DatUnit: the mover resumed unless kKyotoCatch == 8, and
// kKyotoPaused = 0.
void sub_458930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00458930
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    for (;;) {
        // 0x004589ac
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0045894c
        charge(ctx, 9);
        v1 = sll(s1, 3);
        v1 = subu(v1, s1);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, -6496);  // &0x86E6A0
        s0 = addu(v1, a0);
        lw(v1, s0, 72);
        if (v1 != 0) {
            // 0x00458970
            charge(ctx, 6);
            lw(v0, s0, 364);
            lw(v0, v0, 60);
            lb(v1, v0, kKyotoCatch);
            v0 = 8;
            if (v1 != v0) {
                // 0x00458988
                charge(ctx, 4);
                lw(a0, s0, 368);
                a1 = 0;
                jal(ctx, 0x458990u, gen::fn_sub_1B0260_001b0260);
            }
            // 0x00458998
            charge(ctx, 4);
            lw(a0, s0, 364);
            a1 = 0;
            jal(ctx, 0x4589A0u, gen::fn_sub_4589D0_004589d0);
        }
        // 0x004589a8
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004589b8
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004589D0 sub_4589D0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_SetPaused] Work +8 = $a1.
void sub_4589D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004589d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sb(a1, v1, kKyotoPaused);
}

// 0x004589E0 sub_4589E0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_AllIdle] 0 when an NPC's mover still moves (sub_1B0220) or its kKyotoCatch is above 0, else 1.
void sub_4589E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004589e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x00458a58
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004589fc
        charge(ctx, 11);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, v1);
        lw(a0, s1, 368);
        jal(ctx, 0x458A18u, gen::fn_sub_1B0220_001b0220);
        if (v0 != 0) {
            goto L_00458a28_2;
        }
        // 0x00458a34
        charge(ctx, 5);
        lw(v0, s1, 364);
        lw(v0, v0, 60);
        lb(v0, v0, kKyotoCatch);
        if (i64(v0) > 0) {
            goto L_00458a48_4;
        }
        // 0x00458a54
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00458a64
    charge(ctx, 1);
    v0 = 1;
    // 0x00458a68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00458a28_2:
    charge(ctx, 3);
    v0 = 0;
    // 0x00458a68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00458a48_4:
    charge(ctx, 3);
    v0 = 0;
    // 0x00458a68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00458A80 sub_458A80 -- 116 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_IsPausePoint] Scans NPC $a0's row of 0x7BC610 (10 words, -1 ended) for $a1.
void sub_458A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00458a80
    enter(ctx, 12);  // entry check point + this block's cycles
    a3 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x7C0000;
    v0 = addiu(v0, -14832);  // &0x7BC610
    a2 = addu(v0, v1);
    a0 = dsll32(a1, 24);
    a0 = dsra32(a0, 24);
    v0 = si(-1);
    for (;;) {
        // 0x00458ab0
        charge(ctx, 5);
        v1 = sll(a3, 2);
        v1 = addu(a2, v1);
        lw(v1, v1, 0);
        if (a0 == v1) {
            goto L_00458ac4_2;
        }
        // 0x00458ad0
        charge(ctx, 6);
        a3 = addiu(a3, 1);
        v1 = sll(a3, 2);
        v1 = addu(a2, v1);
        lw(v1, v1, 0);
        if (v1 == v0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00458ae8
    charge(ctx, 1);
    v0 = 0;
    // 0x00458aec (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00458ac4_2:
    charge(ctx, 3);
    v0 = 1;
    // 0x00458aec (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00458B00 sub_458B00 -- 88 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_NextLap] For the 4 NPCs: kKyotoLap + 1, state 2.
void sub_458B00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00458b00
    enter(ctx, 6);  // entry check point + this block's cycles
    a3 = 0;
    a2 = 0x870000;
    a2 = addiu(a2, -6496);  // &0x86E6A0
    a0 = 2;
    for (;;) {
        // 0x00458b44
        charge(ctx, 3);
        v1 = slti(a3, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00458b18
        charge(ctx, 11);
        v1 = sll(a3, 3);
        v1 = subu(v1, a3);
        v1 = sll(v1, 6);
        v1 = addu(a2, v1);
        lw(v1, v1, 364);
        lw(a1, v1, 60);
        lb(v1, a1, kKyotoLap);
        v1 = addiu(v1, 1);
        sb(v1, a1, kKyotoLap);
        sb(a0, a1, kKyotoState);
        a3 = addiu(a3, 1);
    }
    // 0x00458b50
    charge(ctx, 2);
}

// 0x00458B60 sub_458B60 -- 76 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_SetAllState6] For the 4 NPCs: work +0 = 6 (no case handles it: they stop).
void sub_458B60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00458b60
    enter(ctx, 6);  // entry check point + this block's cycles
    a2 = 0;
    a1 = 6;
    a0 = 0x870000;
    a0 = addiu(a0, -6496);  // &0x86E6A0
    for (;;) {
        // 0x00458b98
        charge(ctx, 3);
        v1 = slti(a2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00458b78
        charge(ctx, 8);
        v1 = sll(a2, 3);
        v1 = subu(v1, a2);
        v1 = sll(v1, 6);
        v1 = addu(a0, v1);
        lw(v1, v1, 364);
        lw(v1, v1, 60);
        sb(a1, v1, kKyotoState);
        a2 = addiu(a2, 1);
    }
    // 0x00458ba4
    charge(ctx, 2);
}

// 0x00458BB0 sub_458BB0 -- 256 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_DestroyNpcs] For the live NPC units: datUnitDestroyGenus, the model (sub_3174E0), the scene resource
// (sub_3B7090), the mover and think tasks; the unit's slots cleared. (K_Field_DestroyFieldRootTask.)
void sub_458BB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00458bb0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    for (;;) {
        // 0x00458c8c
        charge(ctx, 3);
        v1 = slti(s1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00458bcc
        charge(ctx, 10);
        a1 = 0;
        v1 = sll(s1, 3);
        v1 = subu(v1, s1);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, -6496);  // &0x86E6A0
        s0 = addu(v1, a0);
        lw(v1, s0, 72);
        if (v1 != 0) {
            // 0x00458bf4
            charge(ctx, 3);
            lw(v1, s0, 84);
            if (v1 != 0) {
                // 0x00458c00
                charge(ctx, 1);
                a1 = 1;
            }
        }
        // 0x00458c04
        charge(ctx, 4);
        a0 = sltu(0, a1);
        v1 = 1;
        if (a0 == v1) {
            // 0x00458c14
            charge(ctx, 6);
            lw(a0, s0, 72);
            jal(ctx, 0x458C18u, gen::fn_datUnitDestroyGenus_002ff760);
            lw(a0, s0, 80);
            if (a0 != 0) {
                // 0x00458c2c
                charge(ctx, 2);
                jal(ctx, 0x458C2Cu, gen::fn_sub_3174E0_003174e0);
            }
            // 0x00458c34
            charge(ctx, 3);
            lw(v1, s0, 84);
            if (v1 != 0) {
                // 0x00458c40
                charge(ctx, 3);
                lhu(a0, v1, 0);
                jal(ctx, 0x458C44u, gen::fn_sub_3B7090_003b7090);
            }
            // 0x00458c4c
            charge(ctx, 3);
            lw(a0, s0, 368);
            if (a0 != 0) {
                // 0x00458c58
                charge(ctx, 2);
                jal(ctx, 0x458C58u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            // 0x00458c60
            charge(ctx, 3);
            lw(a0, s0, 364);
            if (a0 != 0) {
                // 0x00458c6c
                charge(ctx, 2);
                jal(ctx, 0x458C6Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            }
            // 0x00458c74
            charge(ctx, 5);
            sw(zero, s0, 80);
            sw(zero, s0, 84);
            sw(zero, s0, 364);
            sw(zero, s0, 368);
            sw(zero, s0, 72);
        }
        // 0x00458c88
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00458c98
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00458CB0 sub_458CB0 -- 2772 bytes; frame 0x160: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_CheckCatch] ($a0 task, $a1 NPC, $a2 route) for each live party member: when the NPC's model is within
// reach of the member (sub_44F1C0): catch state 1, a reaction animation, the markers removed (sub_459D60), an event
// bit (sub_3BB010), a "y wait task" with the procedure 13..16, the camera / event / pad tasks paused, the positions
// and mover steps saved ...; returns 1, else 0.
void sub_458CB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00458cb0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
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
    s7 = a0;
    s4 = dsll32(a1, 24);
    s4 = dsra32(s4, 24);
    v0 = sll(s4, 3);
    a0 = subu(v0, s4);
    v1 = sll(a0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, 19120);  // &0x6B4AB0
    s3 = addu(v0, v1);
    v1 = 0;
    a0 = sll(a0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, -6424);  // &0x86E6E8
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x00458d20
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6412);  // &0x86E6F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x00458d38
            charge(ctx, 1);
            v1 = 1;
        }
    }
    // 0x00458d3c
    charge(ctx, 4);
    v1 = sltu(0, v1);
    v0 = 1;
    if (v1 == v0) {
        // 0x00458d4c
        charge(ctx, 8);
        s6 = 0;
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s2 = addu(v0, a0);
        fp = dsll32(a2, 24);
        fp = dsra32(fp, 24);
        for (;;) {
            // 0x00459740
            charge(ctx, 3);
            v0 = slti(s6, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00458d6c
            charge(ctx, 10);
            a1 = 0;
            v0 = sll(s6, 3);
            v0 = subu(v0, s6);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            a0 = addu(v0, v1);
            lw(v0, a0, 72);
            if (v0 != 0) {
                // 0x00458d94
                charge(ctx, 3);
                lw(v0, a0, 84);
                if (v0 != 0) {
                    // 0x00458da0
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x00458da4
            charge(ctx, 4);
            v1 = sltu(0, a1);
            v0 = 1;
            if (v1 == v0) {
                // 0x00458db4
                charge(ctx, 22);
                lw(v0, s2, 364);
                lw(s1, v0, 60);
                s0 = addiu(a0, 84);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x458DC8u, gen::fn_sub_318B60_00318b60);
                sq(v0, sp, 0xE0);
                lw(v0, s0, 0);
                a0 = addiu(sp, 0x150);
                lw(a1, v0, 480);
                jal(ctx, 0x458DE0u, gen::fn_sub_1AD940_001ad940);
                lq(v0, sp, 0xE0);
                a0 = addiu(v0, 48);
                a1 = addiu(sp, 0x150);
                lwc1(f12, s3, 12);
                jal(ctx, 0x458DF8u, gen::fn_sub_44F1C0_0044f1c0);
                a2 = 1;
                if (v0 == a2) {
                    goto L_00458e0c_10;
                }
                // 0x00458fdc
                charge(ctx, 19);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x458FE4u, gen::fn_sub_318B60_00318b60);
                sq(v0, sp, 0xD0);
                lw(v0, s0, 0);
                a0 = addiu(sp, 0x140);
                lw(a1, v0, 480);
                jal(ctx, 0x458FFCu, gen::fn_sub_1AD940_001ad940);
                lq(v0, sp, 0xD0);
                a0 = addiu(v0, 48);
                a1 = addiu(sp, 0x140);
                lwc1(f12, s3, 4);
                jal(ctx, 0x459014u, gen::fn_sub_44F1C0_0044f1c0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x004594c0
                    charge(ctx, 19);
                    lw(v0, s2, 84);
                    lw(a0, v0, 296);
                    jal(ctx, 0x4594C8u, gen::fn_sub_318B60_00318b60);
                    sq(v0, sp, 0xA0);
                    lw(v0, s0, 0);
                    a0 = addiu(sp, 0x100);
                    lw(a1, v0, 480);
                    jal(ctx, 0x4594E0u, gen::fn_sub_1AD940_001ad940);
                    lq(v0, sp, 0xA0);
                    a0 = addiu(v0, 48);
                    a1 = addiu(sp, 0x100);
                    lwc1(f12, s3, 0);
                    jal(ctx, 0x4594F8u, gen::fn_sub_44F1C0_0044f1c0);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_0045973c;
                    }
                    // 0x0045950c
                    charge(ctx, 2);
                    if (fp != v1) {
                        goto L_0045973c;
                    }
                    goto L_00459514_65;
                }
                // 0x00459028
                charge(ctx, 19);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x459030u, gen::fn_sub_318B60_00318b60);
                sq(v0, sp, 0xC0);
                lw(v0, s0, 0);
                a0 = addiu(sp, 0x130);
                lw(a1, v0, 480);
                jal(ctx, 0x459048u, gen::fn_sub_1AD940_001ad940);
                lq(a0, sp, 0xC0);
                a1 = addiu(sp, 0x130);
                lwc1(f12, s3, 8);
                lwc1(f13, s3, 4);
                jal(ctx, 0x459060u, gen::fn_sub_1C6450_001c6450);
                a2 = 1;
                if (v0 == a2) {
                    goto L_00459074_28;
                }
                // 0x00459244
                charge(ctx, 19);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x45924Cu, gen::fn_sub_318B60_00318b60);
                sq(v0, sp, 0xB0);
                lw(v0, s0, 0);
                a0 = addiu(sp, 0x120);
                lw(a1, v0, 480);
                jal(ctx, 0x459264u, gen::fn_sub_1AD940_001ad940);
                lq(v0, sp, 0xB0);
                a0 = addiu(v0, 48);
                a1 = addiu(sp, 0x120);
                lwc1(f12, s3, 0);
                jal(ctx, 0x45927Cu, gen::fn_sub_44F1C0_0044f1c0);
                v1 = 1;
                if (v0 != v1) {
                    goto L_0045973c;
                }
                // 0x00459290
                charge(ctx, 2);
                if (fp != v1) {
                    goto L_0045973c;
                }
                goto L_00459298_46;
            }
        L_0045973c:
            charge(ctx, 1);
            s6 = addiu(s6, 1);
        }
    }
    // 0x0045974c
    charge(ctx, 1);
    v0 = 0;
    // 0x00459750 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
    return;
L_00458e0c_10:
    charge(ctx, 3);
    sb(a2, s1, kKyotoCatch);
    if (s4 != 0) {
        // 0x00458e44
        charge(ctx, 2);
        if (s4 != a2) {
            // 0x00458e74
            charge(ctx, 3);
            a2 = 2;
            if (s4 != a2) {
                // 0x00458ea8
                charge(ctx, 3);
                v0 = 3;
                if (s4 == v0) {
                    // 0x00458eb4
                    charge(ctx, 1);
                    s5 = 16;
                }
            } else {
                // 0x00458e80
                charge(ctx, 10);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                a1 = 0;
                a3 = 8;
                t0 = 0;
                jal(ctx, 0x458E94u, gen::fn_sub_3182D0_003182d0);
                s5 = 14;
            }
        } else {
            // 0x00458e4c
            charge(ctx, 10);
            lw(v0, s2, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 0;
            jal(ctx, 0x458E60u, gen::fn_sub_3182D0_003182d0);
            s5 = 15;
        }
    } else {
        // 0x00458e18
        charge(ctx, 11);
        s5 = 13;
        lw(v0, s2, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a2 = 2;
        a3 = 8;
        t0 = 0;
        jal(ctx, 0x458E34u, gen::fn_sub_3182D0_003182d0);
    }
    // 0x00458eb8
    charge(ctx, 10);
    jal(ctx, 0x458EB8u, gen::fn_sub_459D60_00459d60);
    lw(v0, s2, 84);
    lhu(a0, v0, 0);
    a1 = 1;
    jal(ctx, 0x458ECCu, gen::fn_sub_3BB010_003bb010);
    lw(v0, s1, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x00458ee0
        charge(ctx, 1);
        sw(zero, s1, kKyotoWaitTask);
    }
    // 0x00458ee4
    charge(ctx, 27);
    a0 = s7;
    lh(a1, s3, 16);
    a2 = s5;
    jal(ctx, 0x458EF0u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s1, kKyotoWaitTask);
    jal(ctx, 0x458EFCu, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 12);
    a1 = 1;
    jal(ctx, 0x458F0Cu, gen::fn_sub_1E1360_001e1360);
    jal(ctx, 0x458F14u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 36);
    a1 = 1;
    jal(ctx, 0x458F24u, gen::fn_sub_1D3810_001d3810);
    jal(ctx, 0x458F2Cu, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 8);
    a1 = 1;
    jal(ctx, 0x458F3Cu, gen::fn_sub_1CD670_001cd670);
    s0 = 0;
    for (;;) {
        // 0x00458fc4
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00458f50
        charge(ctx, 12);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, v1);
        lw(a0, s1, 368);
        a1 = 1;
        jal(ctx, 0x458F70u, gen::fn_sub_1B0260_001b0260);
        if (s4 != s0) {
            // 0x00458f80
            charge(ctx, 16);
            lhu(a0, s1, 424);
            jal(ctx, 0x458F84u, gen::fn_sub_1DDE00_001dde00);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 1;
            jal(ctx, 0x458FA8u, gen::fn_sub_3182D0_003182d0);
            v1 = 1;
            lw(v0, s1, 364);
            lw(v0, v0, 60);
            sb(v1, v0, 7);
        }
        // 0x00458fc0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00458fd0
    charge(ctx, 3);
    v0 = 1;
    // 0x00459750 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
    return;
L_00459074_28:
    charge(ctx, 3);
    sb(a2, s1, kKyotoCatch);
    if (s4 != 0) {
        // 0x004590ac
        charge(ctx, 2);
        if (s4 != a2) {
            // 0x004590dc
            charge(ctx, 3);
            a2 = 2;
            if (s4 != a2) {
                // 0x00459110
                charge(ctx, 3);
                v0 = 3;
                if (s4 == v0) {
                    // 0x0045911c
                    charge(ctx, 1);
                    s5 = 16;
                }
            } else {
                // 0x004590e8
                charge(ctx, 10);
                lw(v0, s2, 84);
                lw(a0, v0, 296);
                a1 = 0;
                a3 = 8;
                t0 = 0;
                jal(ctx, 0x4590FCu, gen::fn_sub_3182D0_003182d0);
                s5 = 14;
            }
        } else {
            // 0x004590b4
            charge(ctx, 10);
            lw(v0, s2, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 0;
            jal(ctx, 0x4590C8u, gen::fn_sub_3182D0_003182d0);
            s5 = 15;
        }
    } else {
        // 0x00459080
        charge(ctx, 11);
        s5 = 13;
        lw(v0, s2, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a2 = 2;
        a3 = 8;
        t0 = 0;
        jal(ctx, 0x45909Cu, gen::fn_sub_3182D0_003182d0);
    }
    // 0x00459120
    charge(ctx, 10);
    jal(ctx, 0x459120u, gen::fn_sub_459D60_00459d60);
    lw(v0, s2, 84);
    lhu(a0, v0, 0);
    a1 = 1;
    jal(ctx, 0x459134u, gen::fn_sub_3BB010_003bb010);
    lw(v0, s1, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x00459148
        charge(ctx, 1);
        sw(zero, s1, kKyotoWaitTask);
    }
    // 0x0045914c
    charge(ctx, 27);
    a0 = s7;
    lh(a1, s3, 16);
    a2 = s5;
    jal(ctx, 0x459158u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s1, kKyotoWaitTask);
    jal(ctx, 0x459164u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 12);
    a1 = 1;
    jal(ctx, 0x459174u, gen::fn_sub_1E1360_001e1360);
    jal(ctx, 0x45917Cu, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 36);
    a1 = 1;
    jal(ctx, 0x45918Cu, gen::fn_sub_1D3810_001d3810);
    jal(ctx, 0x459194u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 8);
    a1 = 1;
    jal(ctx, 0x4591A4u, gen::fn_sub_1CD670_001cd670);
    s0 = 0;
    for (;;) {
        // 0x0045922c
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004591b8
        charge(ctx, 12);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, v1);
        lw(a0, s1, 368);
        a1 = 1;
        jal(ctx, 0x4591D8u, gen::fn_sub_1B0260_001b0260);
        if (s4 != s0) {
            // 0x004591e8
            charge(ctx, 16);
            lhu(a0, s1, 424);
            jal(ctx, 0x4591ECu, gen::fn_sub_1DDE00_001dde00);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 1;
            jal(ctx, 0x459210u, gen::fn_sub_3182D0_003182d0);
            v1 = 1;
            lw(v0, s1, 364);
            lw(v0, v0, 60);
            sb(v1, v0, 7);
        }
        // 0x00459228
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00459238
    charge(ctx, 3);
    v0 = 1;
    // 0x00459750 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
    return;
L_00459298_46:
    charge(ctx, 8);
    lw(v0, s2, 84);
    lhu(a0, v0, 0);
    a1 = 0;
    jal(ctx, 0x4592A4u, gen::fn_sub_3BB010_003bb010);
    lw(v0, s1, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x004592b8
        charge(ctx, 1);
        sw(zero, s1, kKyotoWaitTask);
    }
    // 0x004592bc
    charge(ctx, 11);
    a0 = s7;
    lh(a1, s3, 18);
    a2 = 0;
    jal(ctx, 0x4592C8u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s1, kKyotoWaitTask);
    v0 = 2;
    sb(v0, s1, kKyotoCatch);
    s5 = 0;
    for (;;) {
        // 0x00459374
        charge(ctx, 3);
        v0 = slti(s5, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004592e8
        charge(ctx, 24);
        v0 = sll(s5, 3);
        v0 = subu(v0, s5);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s3 = addu(v0, v1);
        lw(a0, s3, 368);
        a1 = 1;
        jal(ctx, 0x459308u, gen::fn_sub_1B0260_001b0260);
        lhu(a0, s3, 424);
        jal(ctx, 0x459314u, gen::fn_sub_1DDE00_001dde00);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        lw(v0, s3, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a3 = 8;
        t0 = 1;
        jal(ctx, 0x459338u, gen::fn_sub_3182D0_003182d0);
        if (s4 != s5) {
            // 0x00459348
            charge(ctx, 5);
            lw(v0, s3, 364);
            lw(a0, v0, 60);
            lb(v1, a0, 7);
            if (v1 != 0) {
                // 0x0045935c
                charge(ctx, 3);
                v0 = 8;
                if (v1 == v0) {
                    goto L_00459368;
                }
                goto L_00459370;
            }
        L_00459368:
            charge(ctx, 2);
            v0 = 8;
            sb(v0, a0, 7);
        }
    L_00459370:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x00459380
    charge(ctx, 19);
    lw(v0, s0, 0);
    a0 = addiu(sp, 0x110);
    lw(a1, v0, 480);
    jal(ctx, 0x45938Cu, gen::fn_sub_1AD940_001ad940);
    lwc1(f2, sp, 0x110);
    lwc1(f1, sp, 0x114);
    lwc1(f0, sp, 0x118);
    swc1(f2, s1, kKyotoSavedPosX);
    swc1(f1, s1, kKyotoSavedPosY);
    swc1(f0, s1, kKyotoSavedPosZ);
    lw(a0, s2, 368);
    jal(ctx, 0x4593B0u, gen::fn_sub_1B0220_001b0220);
    sh(v0, s1, 40);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    if (v0 == 0) {
        // 0x004593cc
        charge(ctx, 8);
        lh(v0, s1, 4);
        v0 = v0 & 0x3FF;
        v0 = v0 | 0x3C00;
        a0 = v0 & 0xFFFF;
        jal(ctx, 0x4593DCu, gen::fn_sub_3B5D10_003b5d10);
        if (v0 == 0) {
            // 0x00459424
            charge(ctx, 6);
            lwc1(f2, s1, kKyotoSavedPosX);
            lwc1(f1, s1, kKyotoSavedPosY);
            lwc1(f0, s1, kKyotoSavedPosZ);
            swc1(f2, s1, kKyotoHomePosX);
            swc1(f1, s1, kKyotoHomePosY);
            swc1(f0, s1, kKyotoHomePosZ);
        } else {
            // 0x004593ec
            charge(ctx, 14);
            lh(v0, s1, 4);
            v0 = v0 & 0x3FF;
            v0 = v0 | 0x3C00;
            a0 = v0 & 0xFFFF;
            jal(ctx, 0x4593FCu, gen::fn_sub_3B5D10_003b5d10);
            lwc1(f2, v0, 256);
            lwc1(f1, v0, 260);
            lwc1(f0, v0, 264);
            swc1(f2, s1, kKyotoHomePosX);
            swc1(f1, s1, kKyotoHomePosY);
            swc1(f0, s1, kKyotoHomePosZ);
        }
    }
    // 0x0045943c
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00459480
        charge(ctx, 6);
        lw(a0, s2, 368);
        jal(ctx, 0x459484u, gen::fn_sub_1B0220_001b0220);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459448
        charge(ctx, 14);
        lw(a0, s2, 368);
        a1 = s0;
        jal(ctx, 0x459450u, gen::fn_sub_1B01B0_001b01b0);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        v1 = addu(s1, v1);
        a0 = addiu(v1, 44);
        a1 = v0;
        a2 = 24;
        jal(ctx, 0x459474u, gen::fn_memcpy_00521250);
        s0 = addiu(s0, 1);
    }
    // 0x00459498
    charge(ctx, 10);
    lw(a0, s2, 368);
    jal(ctx, 0x45949Cu, gen::fn_sub_1B00C0_001b00c0);
    lw(a0, s2, 368);
    a1 = 0;
    jal(ctx, 0x4594ACu, gen::fn_sub_1B0260_001b0260);
    v0 = 1;
    // 0x00459750 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
    return;
L_00459514_65:
    charge(ctx, 8);
    lw(v0, s2, 84);
    lhu(a0, v0, 0);
    a1 = 0;
    jal(ctx, 0x459520u, gen::fn_sub_3BB010_003bb010);
    lw(v0, s1, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x00459534
        charge(ctx, 1);
        sw(zero, s1, kKyotoWaitTask);
    }
    // 0x00459538
    charge(ctx, 11);
    a0 = s7;
    lh(a1, s3, 18);
    a2 = 0;
    jal(ctx, 0x459544u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s1, kKyotoWaitTask);
    v0 = 2;
    sb(v0, s1, kKyotoCatch);
    s5 = 0;
    for (;;) {
        // 0x004595f0
        charge(ctx, 3);
        v0 = slti(s5, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459564
        charge(ctx, 24);
        v0 = sll(s5, 3);
        v0 = subu(v0, s5);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s3 = addu(v0, v1);
        lw(a0, s3, 368);
        a1 = 1;
        jal(ctx, 0x459584u, gen::fn_sub_1B0260_001b0260);
        lhu(a0, s3, 424);
        jal(ctx, 0x459590u, gen::fn_sub_1DDE00_001dde00);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        lw(v0, s3, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a3 = 8;
        t0 = 1;
        jal(ctx, 0x4595B4u, gen::fn_sub_3182D0_003182d0);
        if (s4 != s5) {
            // 0x004595c4
            charge(ctx, 5);
            lw(v0, s3, 364);
            lw(a0, v0, 60);
            lb(v1, a0, 7);
            if (v1 != 0) {
                // 0x004595d8
                charge(ctx, 3);
                v0 = 8;
                if (v1 == v0) {
                    goto L_004595e4;
                }
                goto L_004595ec;
            }
        L_004595e4:
            charge(ctx, 2);
            v0 = 8;
            sb(v0, a0, 7);
        }
    L_004595ec:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x004595fc
    charge(ctx, 19);
    lw(v0, s0, 0);
    a0 = addiu(sp, 0xF0);
    lw(a1, v0, 480);
    jal(ctx, 0x459608u, gen::fn_sub_1AD940_001ad940);
    lwc1(f2, sp, 0xF0);
    lwc1(f1, sp, 0xF4);
    lwc1(f0, sp, 0xF8);
    swc1(f2, s1, kKyotoSavedPosX);
    swc1(f1, s1, kKyotoSavedPosY);
    swc1(f0, s1, kKyotoSavedPosZ);
    lw(a0, s2, 368);
    jal(ctx, 0x45962Cu, gen::fn_sub_1B0220_001b0220);
    sh(v0, s1, 40);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    if (v0 == 0) {
        // 0x00459648
        charge(ctx, 8);
        lh(v0, s1, 4);
        v0 = v0 & 0x3FF;
        v0 = v0 | 0x3C00;
        a0 = v0 & 0xFFFF;
        jal(ctx, 0x459658u, gen::fn_sub_3B5D10_003b5d10);
        if (v0 == 0) {
            // 0x004596a0
            charge(ctx, 6);
            lwc1(f2, s1, kKyotoSavedPosX);
            lwc1(f1, s1, kKyotoSavedPosY);
            lwc1(f0, s1, kKyotoSavedPosZ);
            swc1(f2, s1, kKyotoHomePosX);
            swc1(f1, s1, kKyotoHomePosY);
            swc1(f0, s1, kKyotoHomePosZ);
        } else {
            // 0x00459668
            charge(ctx, 14);
            lh(v0, s1, 4);
            v0 = v0 & 0x3FF;
            v0 = v0 | 0x3C00;
            a0 = v0 & 0xFFFF;
            jal(ctx, 0x459678u, gen::fn_sub_3B5D10_003b5d10);
            lwc1(f2, v0, 256);
            lwc1(f1, v0, 260);
            lwc1(f0, v0, 264);
            swc1(f2, s1, kKyotoHomePosX);
            swc1(f1, s1, kKyotoHomePosY);
            swc1(f0, s1, kKyotoHomePosZ);
        }
    }
    // 0x004596b8
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x004596fc
        charge(ctx, 6);
        lw(a0, s2, 368);
        jal(ctx, 0x459700u, gen::fn_sub_1B0220_001b0220);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004596c4
        charge(ctx, 14);
        lw(a0, s2, 368);
        a1 = s0;
        jal(ctx, 0x4596CCu, gen::fn_sub_1B01B0_001b01b0);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        v1 = addu(s1, v1);
        a0 = addiu(v1, 44);
        a1 = v0;
        a2 = 24;
        jal(ctx, 0x4596F0u, gen::fn_memcpy_00521250);
        s0 = addiu(s0, 1);
    }
    // 0x00459714
    charge(ctx, 10);
    lw(a0, s2, 368);
    jal(ctx, 0x459718u, gen::fn_sub_1B00C0_001b00c0);
    lw(a0, s2, 368);
    a1 = 0;
    jal(ctx, 0x459728u, gen::fn_sub_1B0260_001b0260);
    v0 = 1;
    // 0x00459750 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x160);
}

// 0x00459790 sub_459790 -- 1484 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_FinishCatch] The catch's last step: like sub_458CB0's contact path for the NPC that caught (wait task,
// script), then the field tasks resumed and the catch state cleared.
void sub_459790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00459790
    enter(ctx, 28);  // entry check point + this block's cycles
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
    s7 = a0;
    s3 = dsll32(a1, 24);
    s3 = dsra32(s3, 24);
    v0 = sll(s3, 3);
    a0 = subu(v0, s3);
    v1 = sll(a0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, 19120);  // &0x6B4AB0
    s2 = addu(v0, v1);
    v1 = 0;
    a0 = sll(a0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, -6424);  // &0x86E6E8
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x00459800
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6412);  // &0x86E6F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x00459818
            charge(ctx, 1);
            v1 = 1;
        }
    }
    // 0x0045981c
    charge(ctx, 4);
    v1 = sltu(0, v1);
    v0 = 1;
    if (v1 == v0) {
        // 0x0045982c
        charge(ctx, 6);
        s5 = 0;
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, a0);
        for (;;) {
            // 0x00459d18
            charge(ctx, 3);
            v0 = slti(s5, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00459844
            charge(ctx, 10);
            a1 = 0;
            v0 = sll(s5, 3);
            v0 = subu(v0, s5);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            a0 = addu(v0, v1);
            lw(v0, a0, 72);
            if (v0 != 0) {
                // 0x0045986c
                charge(ctx, 3);
                lw(v0, a0, 84);
                if (v0 != 0) {
                    // 0x00459878
                    charge(ctx, 1);
                    a1 = 1;
                }
            }
            // 0x0045987c
            charge(ctx, 4);
            v1 = sltu(0, a1);
            v0 = 1;
            if (v1 == v0) {
                // 0x0045988c
                charge(ctx, 21);
                lw(v0, s1, 364);
                lw(s0, v0, 60);
                s6 = addiu(a0, 84);
                lw(v0, s1, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x4598A0u, gen::fn_sub_318B60_00318b60);
                fp = v0;
                lw(v0, s6, 0);
                a0 = addiu(sp, 0xC0);
                lw(a1, v0, 480);
                jal(ctx, 0x4598B8u, gen::fn_sub_1AD940_001ad940);
                a0 = addiu(fp, 0x30);
                a1 = addiu(sp, 0xC0);
                lwc1(f12, s2, 12);
                jal(ctx, 0x4598CCu, gen::fn_sub_44F1C0_0044f1c0);
                a2 = 1;
                if (v0 == a2) {
                    goto L_004598e0_10;
                }
                // 0x00459ab0
                charge(ctx, 18);
                lw(v0, s1, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x459AB8u, gen::fn_sub_318B60_00318b60);
                fp = v0;
                lw(v0, s6, 0);
                a0 = addiu(sp, 0xB0);
                lw(a1, v0, 480);
                jal(ctx, 0x459AD0u, gen::fn_sub_1AD940_001ad940);
                a0 = addiu(fp, 0x30);
                a1 = addiu(sp, 0xB0);
                lwc1(f12, s2, 4);
                jal(ctx, 0x459AE4u, gen::fn_sub_44F1C0_0044f1c0);
                v1 = 1;
                if (v0 != v1) {
                    goto L_00459d14;
                }
                // 0x00459af8
                charge(ctx, 19);
                lw(v0, s1, 84);
                lw(a0, v0, 296);
                jal(ctx, 0x459B00u, gen::fn_sub_318B60_00318b60);
                fp = v0;
                lw(v0, s6, 0);
                a0 = addiu(sp, 0xA0);
                lw(a1, v0, 480);
                jal(ctx, 0x459B18u, gen::fn_sub_1AD940_001ad940);
                a0 = fp;
                a1 = addiu(sp, 0xA0);
                lwc1(f12, s2, 8);
                lwc1(f13, s2, 4);
                jal(ctx, 0x459B30u, gen::fn_sub_1C6450_001c6450);
                a2 = 1;
                if (v0 != a2) {
                    goto L_00459d14;
                }
                goto L_00459b44_28;
            }
        L_00459d14:
            charge(ctx, 1);
            s5 = addiu(s5, 1);
        }
    }
    // 0x00459d24
    charge(ctx, 1);
    v0 = 0;
    // 0x00459d28 (the shared epilogue, written out on this path)
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
    return;
L_004598e0_10:
    charge(ctx, 3);
    sb(a2, s0, kKyotoCatch);
    if (s3 != 0) {
        // 0x00459918
        charge(ctx, 2);
        if (s3 != a2) {
            // 0x00459948
            charge(ctx, 3);
            a2 = 2;
            if (s3 != a2) {
                // 0x0045997c
                charge(ctx, 3);
                v0 = 3;
                if (s3 == v0) {
                    // 0x00459988
                    charge(ctx, 1);
                    s4 = 16;
                }
            } else {
                // 0x00459954
                charge(ctx, 10);
                lw(v0, s1, 84);
                lw(a0, v0, 296);
                a1 = 0;
                a3 = 8;
                t0 = 0;
                jal(ctx, 0x459968u, gen::fn_sub_3182D0_003182d0);
                s4 = 14;
            }
        } else {
            // 0x00459920
            charge(ctx, 10);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 0;
            jal(ctx, 0x459934u, gen::fn_sub_3182D0_003182d0);
            s4 = 15;
        }
    } else {
        // 0x004598ec
        charge(ctx, 11);
        s4 = 13;
        lw(v0, s1, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a2 = 2;
        a3 = 8;
        t0 = 0;
        jal(ctx, 0x459908u, gen::fn_sub_3182D0_003182d0);
    }
    // 0x0045998c
    charge(ctx, 10);
    jal(ctx, 0x45998Cu, gen::fn_sub_459D60_00459d60);
    lw(v0, s1, 84);
    lhu(a0, v0, 0);
    a1 = 1;
    jal(ctx, 0x4599A0u, gen::fn_sub_3BB010_003bb010);
    lw(v0, s0, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x004599b4
        charge(ctx, 1);
        sw(zero, s0, kKyotoWaitTask);
    }
    // 0x004599b8
    charge(ctx, 27);
    a0 = s7;
    lh(a1, s2, 16);
    a2 = s4;
    jal(ctx, 0x4599C4u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s0, kKyotoWaitTask);
    jal(ctx, 0x4599D0u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 12);
    a1 = 1;
    jal(ctx, 0x4599E0u, gen::fn_sub_1E1360_001e1360);
    jal(ctx, 0x4599E8u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 36);
    a1 = 1;
    jal(ctx, 0x4599F8u, gen::fn_sub_1D3810_001d3810);
    jal(ctx, 0x459A00u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 8);
    a1 = 1;
    jal(ctx, 0x459A10u, gen::fn_sub_1CD670_001cd670);
    s0 = 0;
    for (;;) {
        // 0x00459a98
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459a24
        charge(ctx, 12);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, v1);
        lw(a0, s1, 368);
        a1 = 1;
        jal(ctx, 0x459A44u, gen::fn_sub_1B0260_001b0260);
        if (s3 != s0) {
            // 0x00459a54
            charge(ctx, 16);
            lhu(a0, s1, 424);
            jal(ctx, 0x459A58u, gen::fn_sub_1DDE00_001dde00);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 1;
            jal(ctx, 0x459A7Cu, gen::fn_sub_3182D0_003182d0);
            v1 = 1;
            lw(v0, s1, 364);
            lw(v0, v0, 60);
            sb(v1, v0, 7);
        }
        // 0x00459a94
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00459aa4
    charge(ctx, 3);
    v0 = 1;
    // 0x00459d28 (the shared epilogue, written out on this path)
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
    return;
L_00459b44_28:
    charge(ctx, 3);
    sb(a2, s0, kKyotoCatch);
    if (s3 != 0) {
        // 0x00459b7c
        charge(ctx, 2);
        if (s3 != a2) {
            // 0x00459bac
            charge(ctx, 3);
            a2 = 2;
            if (s3 != a2) {
                // 0x00459be0
                charge(ctx, 3);
                v0 = 3;
                if (s3 == v0) {
                    // 0x00459bec
                    charge(ctx, 1);
                    s4 = 16;
                }
            } else {
                // 0x00459bb8
                charge(ctx, 10);
                lw(v0, s1, 84);
                lw(a0, v0, 296);
                a1 = 0;
                a3 = 8;
                t0 = 0;
                jal(ctx, 0x459BCCu, gen::fn_sub_3182D0_003182d0);
                s4 = 14;
            }
        } else {
            // 0x00459b84
            charge(ctx, 10);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 0;
            jal(ctx, 0x459B98u, gen::fn_sub_3182D0_003182d0);
            s4 = 15;
        }
    } else {
        // 0x00459b50
        charge(ctx, 11);
        s4 = 13;
        lw(v0, s1, 84);
        lw(a0, v0, 296);
        a1 = 0;
        a2 = 2;
        a3 = 8;
        t0 = 0;
        jal(ctx, 0x459B6Cu, gen::fn_sub_3182D0_003182d0);
    }
    // 0x00459bf0
    charge(ctx, 10);
    jal(ctx, 0x459BF0u, gen::fn_sub_459D60_00459d60);
    lw(v0, s1, 84);
    lhu(a0, v0, 0);
    a1 = 1;
    jal(ctx, 0x459C04u, gen::fn_sub_3BB010_003bb010);
    lw(v0, s0, kKyotoWaitTask);
    if (v0 != 0) {
        // 0x00459c18
        charge(ctx, 1);
        sw(zero, s0, kKyotoWaitTask);
    }
    // 0x00459c1c
    charge(ctx, 27);
    a0 = s7;
    lh(a1, s2, 16);
    a2 = s4;
    jal(ctx, 0x459C28u, gen::fn_Y_Kyoto_CreateWaitTask_00459f60);
    sw(v0, s0, kKyotoWaitTask);
    jal(ctx, 0x459C34u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 12);
    a1 = 1;
    jal(ctx, 0x459C44u, gen::fn_sub_1E1360_001e1360);
    jal(ctx, 0x459C4Cu, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 36);
    a1 = 1;
    jal(ctx, 0x459C5Cu, gen::fn_sub_1D3810_001d3810);
    jal(ctx, 0x459C64u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, 8);
    a1 = 1;
    jal(ctx, 0x459C74u, gen::fn_sub_1CD670_001cd670);
    s0 = 0;
    for (;;) {
        // 0x00459cfc
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459c88
        charge(ctx, 12);
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, -6496);  // &0x86E6A0
        s1 = addu(v0, v1);
        lw(a0, s1, 368);
        a1 = 1;
        jal(ctx, 0x459CA8u, gen::fn_sub_1B0260_001b0260);
        if (s3 != s0) {
            // 0x00459cb8
            charge(ctx, 16);
            lhu(a0, s1, 424);
            jal(ctx, 0x459CBCu, gen::fn_sub_1DDE00_001dde00);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
            lw(v0, s1, 84);
            lw(a0, v0, 296);
            a1 = 0;
            a3 = 8;
            t0 = 1;
            jal(ctx, 0x459CE0u, gen::fn_sub_3182D0_003182d0);
            v1 = 1;
            lw(v0, s1, 364);
            lw(v0, v0, 60);
            sb(v1, v0, 7);
        }
        // 0x00459cf8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00459d08
    charge(ctx, 3);
    v0 = 1;
    // 0x00459d28 (the shared epilogue, written out on this path)
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

// 0x00459D60 sub_459D60 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_RemoveMarkers] For the 4 NPCs: kKyotoMarkerA / kKyotoMarkerB destroyed (kwlnTaskDestroyWithHierarchy) and
// cleared.
void sub_459D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00459d60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x00459dd0
        charge(ctx, 3);
        v1 = slti(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459d7c
        charge(ctx, 11);
        v1 = sll(s0, 3);
        v1 = subu(v1, s0);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, -6496);  // &0x86E6A0
        v1 = addu(v1, a0);
        lw(v1, v1, 364);
        lw(s1, v1, 60);
        lw(a0, s1, kKyotoMarkerA);
        if (a0 != 0) {
            // 0x00459da8
            charge(ctx, 3);
            jal(ctx, 0x459DA8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, s1, kKyotoMarkerA);
        }
        // 0x00459db4
        charge(ctx, 3);
        lw(a0, s1, kKyotoMarkerB);
        if (a0 != 0) {
            // 0x00459dc0
            charge(ctx, 3);
            jal(ctx, 0x459DC0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, s1, kKyotoMarkerB);
        }
        // 0x00459dcc
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00459ddc
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00459E00 sub_459E00 -- 116 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_OthersDone] 0 when an NPC other than $a0 has kKyotoCatch != 8, else 1.
void sub_459E00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00459e00
    enter(ctx, 8);  // entry check point + this block's cycles
    a2 = 0;
    a1 = dsll32(a0, 24);
    a1 = dsra32(a1, 24);
    a0 = 0x870000;
    a0 = addiu(a0, -6496);  // &0x86E6A0
    v1 = 8;
    for (;;) {
        // 0x00459e5c
        charge(ctx, 3);
        v0 = slti(a2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00459e20
        charge(ctx, 2);
        if (a1 != a2) {
            // 0x00459e28
            charge(ctx, 9);
            v0 = sll(a2, 3);
            v0 = subu(v0, a2);
            v0 = sll(v0, 6);
            v0 = addu(a0, v0);
            lw(v0, v0, 364);
            lw(v0, v0, 60);
            lb(v0, v0, kKyotoCatch);
            if (v0 == v1) {
                goto L_00459e58;
            }
            goto L_00459e4c_3;
        }
    L_00459e58:
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x00459e68
    charge(ctx, 1);
    v0 = 1;
    // 0x00459e6c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00459e4c_3:
    charge(ctx, 3);
    v0 = 0;
    // 0x00459e6c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00459E80 Y_Kyoto_UpdateWaitTask -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_UpdateWaitTask] Counts kWaitCount up to kWaitFrames (0); then, with a procedure, runs it from the field
// script in memory (K_Field_Get +4168 / +4172) into kWaitScript; returns -1.
void Y_Kyoto_UpdateWaitTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00459e80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lh(v1, s0, kWaitCount);
    lh(v0, s0, kWaitFrames);
    at = slt(v1, v0);
    if (at == 0) {
        // 0x00459eb8
        charge(ctx, 3);
        lh(v0, s0, kWaitProc);
        if (v0 != 0) {
            // 0x00459ec4
            charge(ctx, 3);
            lw(v0, s0, kWaitScript);
            if (v0 != 0) {
                // 0x00459ed0
                charge(ctx, 1);
                sw(zero, s0, kWaitScript);
            }
            // 0x00459ed4
            charge(ctx, 12);
            jal(ctx, 0x459ED4u, gen::fn_K_Field_Get_001b9120);
            s1 = v0;
            jal(ctx, 0x459EE0u, gen::fn_K_Field_Get_001b9120);
            lw(a2, v0, 4172);
            lh(a3, s0, kWaitProc);
            a0 = 10;
            lw(a1, s1, 4168);
            jal(ctx, 0x459EF8u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
            sw(v0, s0, kWaitScript);
        }
        // 0x00459f04
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x00459ea8
        charge(ctx, 4);
        v0 = addiu(v1, 1);
        sh(v0, s0, kWaitCount);
        // 0x00459f10
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00459f14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00459F30 sub_459F30 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [destroy callback of "y wait task"] Frees the task's work (+60) through the RW free slot 0x96017C (a jalr tail).
void sub_459F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00459f30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x459F44u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00459F60 Y_Kyoto_CreateWaitTask -- 184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_Kyoto_CreateWaitTask] ($a0 parent, $a1 frames, $a2 procedure) calloc(1, 12), the task "y wait task" (priority
// 10, destroy sub_459F30). Returns the task or 0. Also used by the shadow chase sub_44BEB0.
void Y_Kyoto_CreateWaitTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00459f60
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x459F98u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00459fb8
        charge(ctx, 16);
        a0 = s3;
        a1 = 10;
        a2 = 0x6B0000;
        a2 = addiu(a2, 19304);  // "y wait task"
        a3 = 0x460000;
        a3 = addiu(a3, -24960);  // &Y_Kyoto_UpdateWaitTask
        t0 = 0x460000;
        t0 = addiu(t0, -24784);  // &sub_459F30
        t1 = s0;
        jal(ctx, 0x459FDCu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sh(s2, s0, kWaitFrames);
        sh(zero, s0, kWaitCount);
        v1 = dsll32(s1, 24);
        v1 = dsra32(v1, 24);
        sh(v1, s0, kWaitProc);
    } else {
        // 0x00459fac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00459ff8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0045A220 sub_45A220 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_TimeLimit_DestroyTask] Releases the sprite handle +0 (sub_1124B0) when set, frees the work, clears the task
// word 0x7CE6F8 (gp-0x45F8).
void sub_45A220(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045a220
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x0045a244
        charge(ctx, 3);
        jal(ctx, 0x45A244u, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 0);
    }
    // 0x0045a250
    charge(ctx, 12);
    lw(a0, s1, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x45A25Cu, v0.u());
    sw(zero, gp, -17912);  // 0x7CE6F8
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0045A280 Y_TimeLimit_CreateTimeLimitDrawTask -- 292 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// [Y_TimeLimit_CreateTimeLimitDrawTask] ($a0 parent, $a1 seconds) calloc(1, 96), the task "y_TimeLimit draw"
// (priority 4207, update Y_TimeLimit_UpdateTimeLimitDrawTask, destroy sub_45A220) into 0x7CE6F8; the four digits of
// mm:ss. Returns the task or 0. (The COMM handler sub_425480.)
void Y_TimeLimit_CreateTimeLimitDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045a280
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 96;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x45A2B0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0045a2d0
        charge(ctx, 46);
        a0 = s2;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 19424);  // "y_TimeLimit draw"
        a3 = 0x460000;
        a3 = addiu(a3, -24544);  // &Y_TimeLimit_UpdateTimeLimitDrawTask
        t0 = 0x460000;
        t0 = addiu(t0, -24032);  // &sub_45A220
        t1 = s0;
        jal(ctx, 0x45A2F4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(v0, gp, -17912);  // 0x7CE6F8
        sb(zero, s0, kTlByte4);
        sb(zero, s0, kTlByte5);
        sh(zero, s0, kTlWord68);
        sw(zero, s0, kTlWord72);
        sb(zero, s0, kTlByte66);
        sb(zero, s0, kTlByte67);
        v0 = 1;
        sb(v0, s0, kTlByte76);
        sw(s1, s0, kTlSeconds);
        v1 = 60;
        divu(s1, v1);
        mflo(v0);
        a1 = dsll32(v0, 24);
        a1 = dsra32(a1, 24);
        divu(s1, v1);
        mfhi(v0);
        a0 = dsll32(v0, 24);
        a0 = dsra32(a0, 24);
        v1 = 10;
        div(a1, v1);
        mflo(v0);
        sb(v0, s0, kTlMinTens);
        div(a1, v1);
        mfhi(v0);
        sb(v0, s0, kTlMinOnes);
        div(a0, v1);
        mflo(v0);
        sb(v0, s0, kTlSecTens);
        div(a0, v1);
        mfhi(v0);
        sb(v0, s0, kTlSecOnes);
        sb(zero, s0, kTlByte92);
        sb(zero, s0, kTlByte93);
        lw(v0, gp, -17912);  // 0x7CE6F8
    } else {
        // 0x0045a2c4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0045a388 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game
