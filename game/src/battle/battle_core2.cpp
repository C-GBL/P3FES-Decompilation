// The core battle band 0x270000-0x2D0000, second pass (slice battle_core2): the admini sequence driver, the btl root,
// the .TBL loader, the btl packet queue, the btlUnit accessors and unit packets, unit / action creation and the turn
// order -- hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1.1-1.4, 3.1); the layouts and the
// names of the offsets are in game/include/p3fes/game/battle_core2.h. tests/game/test_battle_core2.cpp pairs every
// function with its recompiled body (__recomp).
//
// Each body started as p3fes_handgen's output: register for register and block for block the recompiled body (frame,
// spills, $ra links, cycle charges, check points), on the register view of game/include/p3fes/game/hg_cpu.h. The
// readability pass on top names what the instructions already do -- the role of each function (proposed names in
// brackets), the record offsets and $gp slots as constants of the same value, block roles -- without moving a load,
// store, call, charge or check point.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle_core2.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_adminiSeqCallBtl_0027ca70(p3fes::EEContext&);
void fn_adminiSeqExitBtl_0027caa0(p3fes::EEContext&);
void fn_adminiUpdateTask_Call_0027c3b0(p3fes::EEContext&);
void fn_btlActionCreate_00299e90(p3fes::EEContext&);
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_btlActionUpdateAll_00299fb0(p3fes::EEContext&);
void fn_btlCreate_0027ced0(p3fes::EEContext&);
void fn_btlMainSetStateNon_0029df40(p3fes::EEContext&);
void fn_btlOrderSortByAgility_0029a570(p3fes::EEContext&);
void fn_btlScrCmd_CALL_BATTLE_0027d5e0(p3fes::EEContext&);
void fn_btlStart_0027d1d0(p3fes::EEContext&);
void fn_btlSupportResetTimers_002dcbc0(p3fes::EEContext&);
void fn_btlTableInit_0027e180(p3fes::EEContext&);
void fn_btlTableLoadAll_0027de40(p3fes::EEContext&);
void fn_btlTableLoad_0027dcd0(p3fes::EEContext&);
void fn_btlTablePatchForAnswer_0027df20(p3fes::EEContext&);
void fn_btlUnitCreate_002875a0(p3fes::EEContext&);
void fn_btlUpdateDraw2DTask_0027cda0(p3fes::EEContext&);
void fn_btlUpdateDraw3DFrontTask_0027cd70(p3fes::EEContext&);
void fn_btlUpdateTableReloadTask_0027e1d0(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetUnit_0016cd60(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_datUnitCreateEc_002ff3e0(p3fes::EEContext&);
void fn_datUnitCreatePc_002ff340(p3fes::EEContext&);
void fn_datUnitDestroyGenus_002ff760(p3fes::EEContext&);
void fn_datUnitInit_002ff890(p3fes::EEContext&);
void fn_fclShop_CreateShopDrawTasks_003e0780(p3fes::EEContext&);
void fn_itfMesMngDestroyHandle_003a3060(p3fes::EEContext&);
void fn_itfMesMngInitialize_003a2d80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nullsub_12_0027edf0(p3fes::EEContext&);
void fn_nullsub_13_0029dfb0(p3fes::EEContext&);
void fn_nullsub_14_002bb760(p3fes::EEContext&);
void fn_nullsub_15_002bf970(p3fes::EEContext&);
void fn_nullsub_16_002bf980(p3fes::EEContext&);
void fn_nullsub_18_002bf9a0(p3fes::EEContext&);
void fn_nullsub_19_002dcd20(p3fes::EEContext&);
void fn_nullsub_4_00177270(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_scrGetCmdTimer_0035f130(p3fes::EEContext&);
void fn_scrGetCurrent_0035f150(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16D930_0016d930(p3fes::EEContext&);
void fn_sub_16D980_0016d980(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A09D0_001a09d0(p3fes::EEContext&);
void fn_sub_1A0A10_001a0a10(p3fes::EEContext&);
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext&);
void fn_sub_1A62C0_001a62c0(p3fes::EEContext&);
void fn_sub_1F1C20_001f1c20(p3fes::EEContext&);
void fn_sub_27C020_0027c020(p3fes::EEContext&);
void fn_sub_27C220_0027c220(p3fes::EEContext&);
void fn_sub_27C2B0_0027c2b0(p3fes::EEContext&);
void fn_sub_27C330_0027c330(p3fes::EEContext&);
void fn_sub_27C5A0_0027c5a0(p3fes::EEContext&);
void fn_sub_27C650_0027c650(p3fes::EEContext&);
void fn_sub_27C840_0027c840(p3fes::EEContext&);
void fn_sub_27C8F0_0027c8f0(p3fes::EEContext&);
void fn_sub_27C9E0_0027c9e0(p3fes::EEContext&);
void fn_sub_27CA10_0027ca10(p3fes::EEContext&);
void fn_sub_27CA40_0027ca40(p3fes::EEContext&);
void fn_sub_27CAE0_0027cae0(p3fes::EEContext&);
void fn_sub_27CB10_0027cb10(p3fes::EEContext&);
void fn_sub_27CB40_0027cb40(p3fes::EEContext&);
void fn_sub_27CB50_0027cb50(p3fes::EEContext&);
void fn_sub_27CB80_0027cb80(p3fes::EEContext&);
void fn_sub_27CBD0_0027cbd0(p3fes::EEContext&);
void fn_sub_27CE50_0027ce50(p3fes::EEContext&);
void fn_sub_27D020_0027d020(p3fes::EEContext&);
void fn_sub_27D730_0027d730(p3fes::EEContext&);
void fn_sub_27D810_0027d810(p3fes::EEContext&);
void fn_sub_27D880_0027d880(p3fes::EEContext&);
void fn_sub_27D8B0_0027d8b0(p3fes::EEContext&);
void fn_sub_27D8D0_0027d8d0(p3fes::EEContext&);
void fn_sub_27DC00_0027dc00(p3fes::EEContext&);
void fn_sub_27DC80_0027dc80(p3fes::EEContext&);
void fn_sub_27E270_0027e270(p3fes::EEContext&);
void fn_sub_27E2C0_0027e2c0(p3fes::EEContext&);
void fn_sub_27E530_0027e530(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27EE00_0027ee00(p3fes::EEContext&);
void fn_sub_27F160_0027f160(p3fes::EEContext&);
void fn_sub_27F1C0_0027f1c0(p3fes::EEContext&);
void fn_sub_27F2E0_0027f2e0(p3fes::EEContext&);
void fn_sub_27F2F0_0027f2f0(p3fes::EEContext&);
void fn_sub_27F3E0_0027f3e0(p3fes::EEContext&);
void fn_sub_27F410_0027f410(p3fes::EEContext&);
void fn_sub_27F530_0027f530(p3fes::EEContext&);
void fn_sub_27F650_0027f650(p3fes::EEContext&);
void fn_sub_27F680_0027f680(p3fes::EEContext&);
void fn_sub_27F6D0_0027f6d0(p3fes::EEContext&);
void fn_sub_27F710_0027f710(p3fes::EEContext&);
void fn_sub_27F730_0027f730(p3fes::EEContext&);
void fn_sub_27F770_0027f770(p3fes::EEContext&);
void fn_sub_27F790_0027f790(p3fes::EEContext&);
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);
void fn_sub_27F930_0027f930(p3fes::EEContext&);
void fn_sub_27FC80_0027fc80(p3fes::EEContext&);
void fn_sub_27FCF0_0027fcf0(p3fes::EEContext&);
void fn_sub_27FD70_0027fd70(p3fes::EEContext&);
void fn_sub_27FD90_0027fd90(p3fes::EEContext&);
void fn_sub_27FE70_0027fe70(p3fes::EEContext&);
void fn_sub_27FE90_0027fe90(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);
void fn_sub_280050_00280050(p3fes::EEContext&);
void fn_sub_280870_00280870(p3fes::EEContext&);
void fn_sub_281270_00281270(p3fes::EEContext&);
void fn_sub_281290_00281290(p3fes::EEContext&);
void fn_sub_2812B0_002812b0(p3fes::EEContext&);
void fn_sub_2813D0_002813d0(p3fes::EEContext&);
void fn_sub_2819B0_002819b0(p3fes::EEContext&);
void fn_sub_2819D0_002819d0(p3fes::EEContext&);
void fn_sub_281AB0_00281ab0(p3fes::EEContext&);
void fn_sub_281E60_00281e60(p3fes::EEContext&);
void fn_sub_281E80_00281e80(p3fes::EEContext&);
void fn_sub_282130_00282130(p3fes::EEContext&);
void fn_sub_282190_00282190(p3fes::EEContext&);
void fn_sub_282290_00282290(p3fes::EEContext&);
void fn_sub_2822B0_002822b0(p3fes::EEContext&);
void fn_sub_282380_00282380(p3fes::EEContext&);
void fn_sub_282620_00282620(p3fes::EEContext&);
void fn_sub_282650_00282650(p3fes::EEContext&);
void fn_sub_282C30_00282c30(p3fes::EEContext&);
void fn_sub_282C60_00282c60(p3fes::EEContext&);
void fn_sub_282CD0_00282cd0(p3fes::EEContext&);
void fn_sub_282D40_00282d40(p3fes::EEContext&);
void fn_sub_283510_00283510(p3fes::EEContext&);
void fn_sub_283BA0_00283ba0(p3fes::EEContext&);
void fn_sub_283C00_00283c00(p3fes::EEContext&);
void fn_sub_283C50_00283c50(p3fes::EEContext&);
void fn_sub_283FE0_00283fe0(p3fes::EEContext&);
void fn_sub_284170_00284170(p3fes::EEContext&);
void fn_sub_284190_00284190(p3fes::EEContext&);
void fn_sub_2841E0_002841e0(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_284330_00284330(p3fes::EEContext&);
void fn_sub_284350_00284350(p3fes::EEContext&);
void fn_sub_2843C0_002843c0(p3fes::EEContext&);
void fn_sub_2843E0_002843e0(p3fes::EEContext&);
void fn_sub_284450_00284450(p3fes::EEContext&);
void fn_sub_2845E0_002845e0(p3fes::EEContext&);
void fn_sub_284600_00284600(p3fes::EEContext&);
void fn_sub_284670_00284670(p3fes::EEContext&);
void fn_sub_2848E0_002848e0(p3fes::EEContext&);
void fn_sub_284900_00284900(p3fes::EEContext&);
void fn_sub_284980_00284980(p3fes::EEContext&);
void fn_sub_284B50_00284b50(p3fes::EEContext&);
void fn_sub_284B70_00284b70(p3fes::EEContext&);
void fn_sub_284BE0_00284be0(p3fes::EEContext&);
void fn_sub_284C70_00284c70(p3fes::EEContext&);
void fn_sub_284C90_00284c90(p3fes::EEContext&);
void fn_sub_284CF0_00284cf0(p3fes::EEContext&);
void fn_sub_287400_00287400(p3fes::EEContext&);
void fn_sub_287490_00287490(p3fes::EEContext&);
void fn_sub_287510_00287510(p3fes::EEContext&);
void fn_sub_287580_00287580(p3fes::EEContext&);
void fn_sub_2879F0_002879f0(p3fes::EEContext&);
void fn_sub_287CF0_00287cf0(p3fes::EEContext&);
void fn_sub_287EA0_00287ea0(p3fes::EEContext&);
void fn_sub_288110_00288110(p3fes::EEContext&);
void fn_sub_2889C0_002889c0(p3fes::EEContext&);
void fn_sub_288F80_00288f80(p3fes::EEContext&);
void fn_sub_2891E0_002891e0(p3fes::EEContext&);
void fn_sub_289650_00289650(p3fes::EEContext&);
void fn_sub_299E30_00299e30(p3fes::EEContext&);
void fn_sub_299E70_00299e70(p3fes::EEContext&);
void fn_sub_29A140_0029a140(p3fes::EEContext&);
void fn_sub_29A250_0029a250(p3fes::EEContext&);
void fn_sub_29A2C0_0029a2c0(p3fes::EEContext&);
void fn_sub_29A4F0_0029a4f0(p3fes::EEContext&);
void fn_sub_29A750_0029a750(p3fes::EEContext&);
void fn_sub_29ABE0_0029abe0(p3fes::EEContext&);
void fn_sub_29AC70_0029ac70(p3fes::EEContext&);
void fn_sub_29AE40_0029ae40(p3fes::EEContext&);
void fn_sub_29B090_0029b090(p3fes::EEContext&);
void fn_sub_29E370_0029e370(p3fes::EEContext&);
void fn_sub_29E390_0029e390(p3fes::EEContext&);
void fn_sub_29E3C0_0029e3c0(p3fes::EEContext&);
void fn_sub_29E400_0029e400(p3fes::EEContext&);
void fn_sub_29E420_0029e420(p3fes::EEContext&);
void fn_sub_29E4B0_0029e4b0(p3fes::EEContext&);
void fn_sub_2A4A70_002a4a70(p3fes::EEContext&);
void fn_sub_2A4C20_002a4c20(p3fes::EEContext&);
void fn_sub_2B6490_002b6490(p3fes::EEContext&);
void fn_sub_2BB770_002bb770(p3fes::EEContext&);
void fn_sub_2BB7D0_002bb7d0(p3fes::EEContext&);
void fn_sub_2BBC00_002bbc00(p3fes::EEContext&);
void fn_sub_2BC6D0_002bc6d0(p3fes::EEContext&);
void fn_sub_2BCDE0_002bcde0(p3fes::EEContext&);
void fn_sub_2D1570_002d1570(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D3D70_002d3d70(p3fes::EEContext&);
void fn_sub_2DB8D0_002db8d0(p3fes::EEContext&);
void fn_sub_2DB980_002db980(p3fes::EEContext&);
void fn_sub_2DD9B0_002dd9b0(p3fes::EEContext&);
void fn_sub_2E2F30_002e2f30(p3fes::EEContext&);
void fn_sub_2E2F80_002e2f80(p3fes::EEContext&);
void fn_sub_2F8790_002f8790(p3fes::EEContext&);
void fn_sub_2F8EA0_002f8ea0(p3fes::EEContext&);
void fn_sub_2F9C10_002f9c10(p3fes::EEContext&);
void fn_sub_2FB860_002fb860(p3fes::EEContext&);
void fn_sub_2FF260_002ff260(p3fes::EEContext&);
void fn_sub_318770_00318770(p3fes::EEContext&);
void fn_sub_318990_00318990(p3fes::EEContext&);
void fn_sub_321120_00321120(p3fes::EEContext&);
void fn_sub_3951A0_003951a0(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3E0920_003e0920(p3fes::EEContext&);
void fn_sub_45A400_0045a400(p3fes::EEContext&);
void fn_sub_4BDCB0_004bdcb0(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace bcore;

// 0x0027C020 sub_27C020 -- 88 bytes; frame 0x10: ra sp+0x0
// [sflPersonaIsBusy] (sfl_persona.c line 41, the K_Assert): the shuffle persona work *(gp-18696) has bit 2 or bit 3 of its
// flags word set ($v0 = 1 / 0). K_Assert when the work is absent (retail continues and reads through the null pointer).
void sub_27C020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c020
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona work
    if (v0 == 0) {
        // 0x0027c034
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 41;
        jal(ctx, 0x27C040u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c048
    charge(ctx, 6);
    lw(v0, gp, kGpSflPersona);  // the shuffle persona work
    lw(v1, v0, 0);
    v0 = v1 & 0x4;
    v0 = sltu(0, v0);
    if (v0 == 0) {
        // 0x0027c060
        charge(ctx, 2);
        v0 = v1 & 0x8;
        v0 = sltu(0, v0);
    }
    // 0x0027c068 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027C080 adminiChangeSeq -- 404 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// adminiChangeSeq(a0 = sequence, a1 = parameter block or 0, a2 = its size, a3 = push): asks the "admini" task to switch
// to sequence a0 (row of sSequenceList 0x68F020; 6 = battle, btlScrCmd_CALL_BATTLE). Work flags: |= 1 (change pending),
// &= ~8, &= ~0x10000; next = a0, delay = 1. A previous parameter block is freed (RwFree slot 0x96017C); a new one is
// allocated with RwMalloc(a2, 0x40000) (slot 0x960178), filled by memcpy and its size kept (+32). a3 != 0 sets flag 4:
// the sequence being left is marked as a return point in the history ring when the change happens.
void adminiChangeSeq(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c080
    enter(ctx, 17);  // entry check point + this block's cycles
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
    a0 = addiu(gp, -26608);  // "admini"
    jal(ctx, 0x27C0B0u, gen::fn_kwlnTaskGetTaskByName_00195340);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c0c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 46;
        jal(ctx, 0x27C0D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c0d8
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x27C0DCu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c0f0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 48;
        jal(ctx, 0x27C0FCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c104
    charge(ctx, 16);
    lw(v1, s0, kAdmFlags);
    a0 = v1 | 0x1;
    sw(a0, s0, kAdmFlags);
    v1 = si(-9);
    a0 = a0 & v1;
    sw(a0, s0, kAdmFlags);
    v1 = lui(0xFFFE);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, s0, kAdmFlags);
    sb(s4, s0, kAdmNextSeq);
    v1 = 1;
    sb(v1, s0, kAdmDelay);
    lw(a0, s0, kAdmParam);
    if (a0 != 0) {
        // 0x0027c144
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, kRwFreeLo);  // 0x96017C
        jalr(ctx, 0x27C14Cu, v0.u());
        sw(zero, s0, kAdmParam);
        sb(zero, s0, kAdmParamSize);
    }
    // 0x0027c15c
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x0027c1bc
        charge(ctx, 2);
        sw(zero, s0, kAdmParam);
        sb(zero, s0, kAdmParamSize);
    } else {
        // 0x0027c164
        charge(ctx, 9);
        a0 = s2;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, kRwMallocLo);  // 0x960178
        jalr(ctx, 0x27C174u, v0.u());
        sw(v0, s0, kAdmParam);
        if (v0 == 0) {
            // 0x0027c188
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -4120);  // "admini.c"
            a1 = 93;
            jal(ctx, 0x27C194u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0027c19c
        charge(ctx, 8);
        lw(a0, s0, kAdmParam);
        a1 = s3;
        a2 = s2;
        jal(ctx, 0x27C1A8u, gen::fn_memcpy_00521250);
        sb(s2, s0, kAdmParamSize);
    }
    // 0x0027c1c4
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x0027c1e0
        charge(ctx, 4);
        lw(a0, s0, kAdmFlags);
        v1 = si(-5);
        v1 = a0 & v1;
        sw(v1, s0, kAdmFlags);
    } else {
        // 0x0027c1cc
        charge(ctx, 5);
        lw(v1, s0, kAdmFlags);
        v1 = v1 | 0x4;
        sw(v1, s0, kAdmFlags);
    }
    // 0x0027c1f0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0027C220 sub_27C220 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [adminiSetSeqDone]: work flags |= 2 -- the running sequence reports it is finished (the main update then pops the
// history ring, sub_27C650).
void sub_27C220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c220
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(gp, -26608);  // "admini"
    jal(ctx, 0x27C230u, gen::fn_kwlnTaskGetTaskByName_00195340);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c244
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 46;
        jal(ctx, 0x27C250u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c258
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x27C25Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c270
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 48;
        jal(ctx, 0x27C27Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c284 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, kAdmFlags);
    v1 = v1 | 0x2;
    sw(v1, s0, kAdmFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C2B0 sub_27C2B0 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [adminiGetSeq]: the running sequence (work +8, s8; -1 = none). 26 callers in the field / event / shop code.
void sub_27C2B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c2b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(gp, -26608);  // "admini"
    jal(ctx, 0x27C2C0u, gen::fn_kwlnTaskGetTaskByName_00195340);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c2d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 46;
        jal(ctx, 0x27C2E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c2e8
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x27C2ECu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c300
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 48;
        jal(ctx, 0x27C30Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c314 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lb(v0, s0, kAdmSeq);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C330 sub_27C330 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [adminiGetNextSeq]: the requested sequence (work +9, s8; -1 = none).
void sub_27C330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c330
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(gp, -26608);  // "admini"
    jal(ctx, 0x27C340u, gen::fn_kwlnTaskGetTaskByName_00195340);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c354
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 46;
        jal(ctx, 0x27C360u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c368
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x27C36Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c380
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 48;
        jal(ctx, 0x27C38Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c394 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lb(v0, s0, kAdmNextSeq);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C3B0 adminiUpdateTask_Call -- 492 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// adminiUpdateTask_Call(task): the "call" step of the admini task (its update function after an exit). With a pending
// change (flags bit 0) and a requested sequence: counts the delay (+33) down first (returns 0 = stay); then frames = 0,
// seq = next, next = -1, flags &= ~3; flag 4 marks the current history slot (ring +20) as a return point; the ring index
// (+10, 0..7) steps back on a restore (flag 0x10000, which it clears; $a0 = 1), stays on flag 8 (cleared), else steps
// forward; the slot records the sequence (+12) and a clear mark; then sSequenceList[seq].call(restoring, parameter block)
// runs (jalr). Returns sub_27C650 (the main update) as the task's next update function.
void adminiUpdateTask_Call(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c3b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x27C3BCu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c3d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 217;
        jal(ctx, 0x27C3DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c3e4
    charge(ctx, 4);
    lw(v0, s0, kAdmFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {  // a change is pending
        // 0x0027c3f4
        charge(ctx, 3);
        lb(v0, s0, kAdmNextSeq);
        if (i64(v0) < 0) {
            goto L_0027c400;
        }
        // 0x0027c410
        charge(ctx, 3);
        lbu(v0, s0, kAdmDelay);
        if (i64(v0) <= 0) {  // the delay is over: switch
            // 0x0027c430
            charge(ctx, 15);
            sw(zero, s0, kAdmFrames);
            lb(v0, s0, kAdmNextSeq);
            sb(v0, s0, kAdmSeq);
            v0 = si(-1);
            sb(v0, s0, kAdmNextSeq);
            lw(v1, s0, kAdmFlags);
            v0 = si(-2);
            v1 = v1 & v0;
            sw(v1, s0, kAdmFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s0, kAdmFlags);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                // 0x0027c46c
                charge(ctx, 9);  // flag 4: the slot being left becomes a return point
                lbu(v0, s0, kAdmRing);
                v1 = addu(v0, s0);
                lbu(v0, v1, kAdmRingFlags);
                v0 = v0 | 0x1;
                sb(v0, v1, kAdmRingFlags);
                lw(v1, s0, kAdmFlags);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s0, kAdmFlags);
            }
            // 0x0027c490
            charge(ctx, 5);
            lw(v1, s0, kAdmFlags);
            v0 = 0x10000;
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0027c4e8
                charge(ctx, 4);
                a0 = 0;
                v0 = v1 & 0x8;
                if (v0 == 0) {
                    // 0x0027c50c -- the ring index one forward ((i + 1) & 7, as the signed modulo)
                    charge(ctx, 5);
                    lbu(v0, s0, kAdmRing);
                    v1 = addiu(v0, 1);
                    v0 = v1 & 0x7;
                    if (i64(v1) < 0) {
                        // 0x0027c520
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x0027c528
                            charge(ctx, 1);
                            v0 = addiu(v0, -8);
                        }
                    }
                    // 0x0027c52c
                    charge(ctx, 1);
                    sb(v0, s0, kAdmRing);
                } else {
                    // 0x0027c4f8
                    charge(ctx, 5);
                    v0 = si(-9);
                    v0 = v1 & v0;
                    sw(v0, s0, kAdmFlags);
                }
            } else {
                // 0x0027c4a4 -- restoring: the ring index one back ((i + 7) & 7); $a0 = 1
                charge(ctx, 6);
                a0 = 1;
                lbu(v0, s0, kAdmRing);
                v1 = addiu(v0, 7);
                v0 = v1 & 0x7;
                if (i64(v1) < 0) {
                    // 0x0027c4bc
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x0027c4c4
                        charge(ctx, 1);
                        v0 = addiu(v0, -8);
                    }
                }
                // 0x0027c4c8
                charge(ctx, 8);
                sb(v0, s0, kAdmRing);
                lw(v1, s0, kAdmFlags);
                v0 = lui(0xFFFE);
                v0 = v0 | 0xFFFF;
                v0 = v1 & v0;
                sw(v0, s0, kAdmFlags);
            }
            // 0x0027c530 -- record the sequence in the ring, then sSequenceList[seq].call(restoring, block)
            charge(ctx, 17);
            lb(v1, s0, kAdmSeq);
            lbu(v0, s0, kAdmRing);
            v0 = addu(v0, s0);
            sb(v1, v0, kAdmRingSeq);
            lbu(v0, s0, kAdmRing);
            v0 = addu(v0, s0);
            sb(zero, v0, kAdmRingFlags);
            lb(v1, s0, kAdmSeq);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -4064);  // &sSequenceList
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x0027c574
                charge(ctx, 3);
                lw(a1, s0, kAdmParam);
                jalr(ctx, 0x27C578u, v0.u());
            }
            // 0x0027c580
            charge(ctx, 2);
            v0 = 0x280000;
            v0 = addiu(v0, -14768);  // &sub_27C650
        } else {
            // 0x0027c41c -- count the delay down, stay
            charge(ctx, 5);
            v0 = addiu(v0, -1);
            sb(v0, s0, kAdmDelay);
            v0 = 0;
        }
        // 0x0027c588 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0027c400:
    charge(ctx, 4);
    v0 = 0x280000;
    v0 = addiu(v0, -14768);  // &sub_27C650
    // 0x0027c588 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C5A0 sub_27C5A0 -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [adminiUpdateTask_Exit](task): the "exit" step: sSequenceList[seq].exit() (row +4) when the running sequence has one; a
// result >= 0 means "left": delay = result + 1, seq = -1, and the task goes on with adminiUpdateTask_Call; a result < 0
// keeps this step (returns 0).
void sub_27C5A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c5a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x27C5ACu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    if (s0 == 0) {
        // 0x0027c5c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 296;
        jal(ctx, 0x27C5CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c5d4
    charge(ctx, 3);
    lb(v1, s0, kAdmSeq);
    if (i64(v1) >= 0) {
        // 0x0027c5e0
        charge(ctx, 9);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -4060);  // &0x68F024
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        if (v0 == 0) {
            goto L_0027c630;
        }
        // 0x0027c604
        charge(ctx, 4);
        jalr(ctx, 0x27C604u, v0.u());
        if (i64(v0) >= 0) {
            // 0x0027c620
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            sb(v0, s0, kAdmDelay);
            v0 = si(-1);
            sb(v0, s0, kAdmSeq);
            goto L_0027c630;
        }
        // 0x0027c614
        charge(ctx, 3);
        v0 = 0;
        // 0x0027c638 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0027c630:
    charge(ctx, 2);
    v0 = 0x280000;
    v0 = addiu(v0, -15440);  // &adminiUpdateTask_Call
    // 0x0027c638 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C650 sub_27C650 -- 492 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [adminiUpdateTask_Main](task): the admini task's main update. While the running sequence is not done: its check
// function (row +8) returning non-zero sets flags bit 1, and frames (+4) counts up. Once done: the previous history slot
// ((ring + 7) & 7) with a sequence and a return mark is restored ("restore sequence!!\n" by printf; flags |= 1 | 0x10000,
// next = that sequence, delay = 1, flag 4 cleared, the parameter block freed); without one, a change to sequence 0 is
// requested (adminiChangeSeq(0, 0, 0, 0)); flags &= ~2. A pending change returns sub_27C5A0 (the exit step), else 0.
void sub_27C650(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c650
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x27C660u, gen::fn_kwlnTaskGetWorkData_00195540);
    s1 = v0;
    if (s1 == 0) {
        // 0x0027c674
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4120);  // "admini.c"
        a1 = 333;
        jal(ctx, 0x27C680u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027c688
    charge(ctx, 4);
    lw(v0, s1, kAdmFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0027c698
        charge(ctx, 3);
        lb(v1, s1, kAdmSeq);
        if (i64(v1) >= 0) {
            // 0x0027c6a4
            charge(ctx, 9);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -4056);  // &0x68F028
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            if (v0 != 0) {
                // 0x0027c6c8
                charge(ctx, 4);
                jalr(ctx, 0x27C6C8u, v0.u());
                if (v0 != 0) {
                    // 0x0027c6d8
                    charge(ctx, 3);
                    lw(v0, s1, kAdmFlags);
                    v0 = v0 | 0x2;
                    sw(v0, s1, kAdmFlags);
                }
            }
            // 0x0027c6e4
            charge(ctx, 3);
            lw(v0, s1, kAdmFrames);
            v0 = addiu(v0, 1);
            sw(v0, s1, kAdmFrames);
        }
    }
    // 0x0027c6f0
    charge(ctx, 4);
    lw(v0, s1, kAdmFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x0027c700
        charge(ctx, 3);
        lb(v0, s1, kAdmSeq);
        if (i64(v0) >= 0) {
            // 0x0027c70c
            charge(ctx, 5);
            lbu(v0, s1, kAdmRing);
            v1 = addiu(v0, 7);
            v0 = v1 & 0x7;
            if (i64(v1) < 0) {
                // 0x0027c720
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0027c728
                    charge(ctx, 1);
                    v0 = addiu(v0, -8);
                }
            }
            // 0x0027c72c
            charge(ctx, 5);
            v1 = addu(v0, s1);
            s0 = addiu(v1, 12);
            lb(v0, v1, kAdmRingSeq);
            if (i64(v0) >= 0) {
                // 0x0027c740
                charge(ctx, 4);
                lbu(v0, v1, kAdmRingFlags);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x0027c750
                    charge(ctx, 21);
                    a0 = 0x690000;
                    a0 = addiu(a0, -4096);  // "restore sequence!!\n"
                    jal(ctx, 0x27C758u, gen::fn_printf_005225a8);
                    lw(v0, s1, kAdmFlags);
                    v1 = v0 | 0x1;
                    sw(v1, s1, kAdmFlags);
                    v0 = 0x10000;
                    v0 = v1 | v0;
                    sw(v0, s1, kAdmFlags);
                    lb(v0, s0, 0);
                    sb(v0, s1, kAdmNextSeq);
                    v0 = 1;
                    sb(v0, s1, kAdmDelay);
                    lw(v1, s1, kAdmFlags);
                    v0 = si(-5);
                    v0 = v1 & v0;
                    sw(v0, s1, kAdmFlags);
                    lw(a0, s1, kAdmParam);
                    if (a0 != 0) {
                        // 0x0027c7a4
                        charge(ctx, 6);
                        v0 = 0x960000;
                        lw(v0, v0, kRwFreeLo);  // 0x96017C
                        jalr(ctx, 0x27C7ACu, v0.u());
                        sw(zero, s1, kAdmParam);
                        sb(zero, s1, kAdmParamSize);
                    }
                }
            }
            // 0x0027c7bc
            charge(ctx, 4);
            lw(v0, s1, kAdmFlags);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0027c7cc
                charge(ctx, 6);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x27C7DCu, gen::fn_adminiChangeSeq_0027c080);
            }
            // 0x0027c7e4
            charge(ctx, 4);
            lw(v1, s1, kAdmFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s1, kAdmFlags);
        }
    }
    // 0x0027c7f4
    charge(ctx, 4);
    lw(v0, s1, kAdmFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0027c804
        charge(ctx, 3);
        lb(v0, s1, kAdmNextSeq);
        if (i64(v0) < 0) {
            goto L_0027c820;
        }
        // 0x0027c810
        charge(ctx, 4);
        v0 = 0x280000;
        v0 = addiu(v0, -14944);  // &sub_27C5A0
        // 0x0027c824 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_0027c820:
    charge(ctx, 1);
    v0 = 0;
    // 0x0027c824 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027C840 sub_27C840 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [adminiDestroyTask](task): the admini task's destroy function: the running sequence's exit function, then RwFree of the
// parameter block and of the work itself (the work is fetched twice, as the original does).
void sub_27C840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c840
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x27C854u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lb(v1, v0, kAdmSeq);
    if (i64(v1) >= 0) {
        // 0x0027c86c
        charge(ctx, 9);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -4060);  // &0x68F024
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x0027c890
            charge(ctx, 2);
            jalr(ctx, 0x27C890u, v0.u());
        }
    }
    // 0x0027c898
    charge(ctx, 3);
    lw(a0, s0, kAdmParam);
    if (a0 != 0) {
        // 0x0027c8a4
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, kRwFreeLo);  // 0x96017C
        jalr(ctx, 0x27C8ACu, v0.u());
    }
    // 0x0027c8b4
    charge(ctx, 14);
    a0 = s1;
    jal(ctx, 0x27C8B8u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    v0 = 0x960000;
    lw(v0, v0, kRwFreeLo);  // 0x96017C
    jalr(ctx, 0x27C8CCu, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027C8F0 sub_27C8F0 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [adminiCreateTask] (kwlnInitMain): creates the "admini" task once (kwlnTaskGetTaskByName first): a 36-byte work from
// RwMalloc (flags 0, frames 0, seq / next -1, ring 0, the eight history slots -1 / 0, no parameter block) and
// kwlnTaskCreate(0, "admini", 1, sub_27C650, sub_27C840, work). Returns the task (0 when it already existed).
void sub_27C8F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c8f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(gp, -26608);  // "admini"
    jal(ctx, 0x27C900u, gen::fn_kwlnTaskGetTaskByName_00195340);
    if (v0 == 0) {
        // 0x0027c91c
        charge(ctx, 9);
        a0 = 36;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, kRwMallocLo);  // 0x960178
        jalr(ctx, 0x27C92Cu, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x0027c940
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -4120);  // "admini.c"
            a1 = 435;
            jal(ctx, 0x27C94Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0027c954
        charge(ctx, 9);
        sw(zero, s0, kAdmFlags);
        sw(zero, s0, kAdmFrames);
        v1 = si(-1);
        sb(v1, s0, kAdmSeq);
        sb(v1, s0, kAdmNextSeq);
        sb(zero, s0, kAdmRing);
        a0 = 0;
        for (;;) {
            // 0x0027c988
            charge(ctx, 3);
            v0 = slti(a0, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027c978
            charge(ctx, 4);
            v0 = addu(s0, a0);
            sb(v1, v0, kAdmRingSeq);
            sb(zero, v0, kAdmRingFlags);
            a0 = addiu(a0, 1);
        }
        // 0x0027c994
        charge(ctx, 12);
        sw(zero, s0, kAdmParam);
        sb(zero, s0, kAdmParamSize);
        a0 = 0;
        a1 = addiu(gp, -26608);  // "admini"
        a2 = 1;
        a3 = 0x280000;
        a3 = addiu(a3, -14768);  // &sub_27C650
        t0 = 0x280000;
        t0 = addiu(t0, -14272);  // &sub_27C840
        t1 = s0;
        jal(ctx, 0x27C9BCu, gen::fn_kwlnTaskCreate_00194b20);
    } else {
        // 0x0027c910
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0027c9c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027C9E0 sub_27C9E0 -- 40 bytes; frame 0x10: ra sp+0x0
// [adminiSeqDebug_Call] (sSequenceList row, a test sequence): printf("+++ call\n").
void sub_27C9E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027c9e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, -3968);  // "+++ call\n"
    jal(ctx, 0x27C9F0u, gen::fn_printf_005225a8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CA10 sub_27CA10 -- 44 bytes; frame 0x10: ra sp+0x0
// [adminiSeqDebug_Exit]: printf("+++ exit\n"); returns 0 (left at once).
void sub_27CA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ca10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, -3952);  // "+++ exit\n"
    jal(ctx, 0x27CA20u, gen::fn_printf_005225a8);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CA40 sub_27CA40 -- 44 bytes; frame 0x10: ra sp+0x0
// [adminiSeqDebug_Check]: printf("+++ check\n"); returns 1 (done at once).
void sub_27CA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ca40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x690000;
    a0 = addiu(a0, -3936);  // "+++ check\n"
    jal(ctx, 0x27CA50u, gen::fn_printf_005225a8);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CA70 adminiSeqCallBtl -- 44 bytes; frame 0x10: ra sp+0x0
// adminiSeqCallBtl(restoring, setup block): the battle sequence's call function: btlStart(a1) and sub_27D8B0 (gBtl+12 |=
// 0x8000: the setup's units belong to this battle and are destroyed with it, sub_27D020).
void adminiSeqCallBtl(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ca70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x27CA7Cu, gen::fn_btlStart_0027d1d0);
    jal(ctx, 0x27CA84u, gen::fn_sub_27D8B0_0027d8b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CAA0 adminiSeqExitBtl -- 56 bytes; frame 0x10: ra sp+0x0
// adminiSeqExitBtl(): the battle sequence's exit function: destroys the battle's task tree (sub_27D880 = gBtl+3352, when
// gBtl exists) with kwlnTaskDestroyWithHierarchy; returns 0.
void adminiSeqExitBtl(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027caa0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27CAA8u, gen::fn_sub_27D880_0027d880);
    if (v0 != 0) {
        // 0x0027cab8
        charge(ctx, 3);
        a0 = v0;
        jal(ctx, 0x27CABCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    // 0x0027cac4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CAE0 sub_27CAE0 -- 40 bytes; frame 0x10: ra sp+0x0
// [adminiSeqCheckBtl]: the battle sequence's check function: 1 once the battle's task tree is gone (sub_27D880() == 0).
void sub_27CAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cae0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27CAE8u, gen::fn_sub_27D880_0027d880);
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CB10 sub_27CB10 -- 36 bytes; frame 0x10: ra sp+0x0
// [adminiSeqCallShop](restoring, parameter block): the shop sequence's call function: fclShop_CreateShopDrawTasks(*block).
void sub_27CB10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cb10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a1, 0);
    jal(ctx, 0x27CB1Cu, gen::fn_fclShop_CreateShopDrawTasks_003e0780);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CB40 sub_27CB40 -- 12 bytes; leaf frame (no stack)
// [adminiSeqExitNone]: an exit function that leaves at once (returns 0).
void sub_27CB40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0027cb40
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0027CB50 sub_27CB50 -- 40 bytes; frame 0x10: ra sp+0x0
// [adminiSeqCheckShop]: the shop sequence's check function: 1 once sub_3E0920() returns 0.
void sub_27CB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cb50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27CB58u, gen::fn_sub_3E0920_003e0920);
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CB80 sub_27CB80 -- 72 bytes; leaf frame (no stack)
// [btlGetUID]: the next battle-wide id from the u64 counter at gp-26592 (0x7CC510): ++counter, wrapped to 1 at
// 0x3FFFFFFFFFFFFFFF (the top two bits stay free: the packet conditions mask them, sub_27E530). btlCreate resets it to 1.
// Used for packet ids (sub_27ED20) and btlAction uids (btlActionCreate).
void sub_27CB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0027cb80
    enter(ctx, 13);  // entry check point + this block's cycles
    ld(v0, gp, kGpUidCounter);  // btlGetUID counter (u64)
    a0 = daddiu(v0, 1);
    sd(a0, gp, kGpUidCounter);  // btlGetUID counter (u64)
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    v0 = v0 | v1;
    v0 = sltu(a0, v0);
    if (v0 == 0) {
        // 0x0027cbb4
        charge(ctx, 2);
        v0 = 1;
        sd(v0, gp, kGpUidCounter);  // btlGetUID counter (u64)
    }
    // 0x0027cbbc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(v0, gp, kGpUidCounter);  // btlGetUID counter (u64)
}

// 0x0027CBD0 sub_27CBD0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAllocModelId]: the next free battle model id: the u16 at gp-26584 counts up in 256..511 (wrapping to 256) until
// sub_3B5D10((id & 0x3FF) | 0x400) reports the slot free; returns the id. btlCreate resets the counter to 256.
void sub_27CBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cbd0
    enter(ctx, 2);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    for (;;) {
        // 0x0027cbd8
        charge(ctx, 7);
        lhu(v0, gp, kGpModelIdCounter);  // model id counter (u16)
        v0 = addiu(v0, 1);
        sh(v0, gp, kGpModelIdCounter);  // model id counter (u16)
        v0 = v0 & 0xFFFF;
        v0 = slti(v0, 512);
        if (v0 == 0) {
            // 0x0027cbf4
            charge(ctx, 2);
            v0 = 256;
            sh(v0, gp, kGpModelIdCounter);  // model id counter (u16)
        }
        // 0x0027cbfc
        charge(ctx, 8);
        lhu(v0, gp, kGpModelIdCounter);  // model id counter (u16)
        v0 = v0 & 0x3FF;
        v0 = v0 | 0x400;
        a0 = v0 & 0xFFFF;
        jal(ctx, 0x27CC0Cu, gen::fn_sub_3B5D10_003b5d10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0027cc1c
    charge(ctx, 5);
    lhu(v0, gp, kGpModelIdCounter);  // model id counter (u16)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CD70 btlUpdateDraw3DFrontTask -- 48 bytes; frame 0x10: ra sp+0x0
// btlUpdateDraw3DFrontTask (task "battle_draw_3d_front"): sub_321120(3) then the unit front-layer draw sub_2891E0.
void btlUpdateDraw3DFrontTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cd70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3;
    jal(ctx, 0x27CD7Cu, gen::fn_sub_321120_00321120);
    jal(ctx, 0x27CD84u, gen::fn_sub_2891E0_002891e0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CDA0 btlUpdateDraw2DTask -- 68 bytes; frame 0x10: ra sp+0x0
// btlUpdateDraw2DTask (task "battle_draw_2d"): sub_321120(5), the packet queue 3 (sub_27F160(3)), the battle HUD
// sub_29E4B0 and nullsub_18.
void btlUpdateDraw2DTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027cda0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x27CDACu, gen::fn_sub_321120_00321120);
    a0 = 3;
    jal(ctx, 0x27CDB8u, gen::fn_sub_27F160_0027f160);
    jal(ctx, 0x27CDC0u, gen::fn_sub_29E4B0_0029e4b0);
    jal(ctx, 0x27CDC8u, gen::fn_nullsub_18_002bf9a0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027CE50 sub_27CE50 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlReleaseModelSlots]: sub_3951A0(id) for ids 5440..5567 and 5568..5631 (the same two loops btlCreate runs).
void sub_27CE50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ce50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 5440;
    for (;;) {
        // 0x0027ce78
        charge(ctx, 4);
        at = slti(s0, 5568);
        if (at == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027ce68
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x27CE6Cu, gen::fn_sub_3951A0_003951a0);
        s0 = addiu(s0, 1);
    }
    // 0x0027ce88
    charge(ctx, 3);
    s0 = 5568;
    for (;;) {
        // 0x0027cea4
        charge(ctx, 4);
        at = slti(s0, 5632);
        if (at == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027ce94
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x27CE98u, gen::fn_sub_3951A0_003951a0);
        s0 = addiu(s0, 1);
    }
    // 0x0027ceb4
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027CED0 btlCreate -- 324 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// btlCreate(): allocates and zeroes the 3,440-byte battle context gBtl (RwMalloc; gp-18692), resets the uid counter (1)
// and the model-id counter (256), opens the message manager (gBtl+2976 = itfMesMngInitialize(*(gp-18448), the MSG.TBL
// text block)), releases the model slots 5440..5631, runs the sub-systems' init functions (sub_2D3D70, nullsub_12,
// sub_2A4A70, btlSupportResetTimers, sub_2E2F30, nullsub_14, sub_29B090, btlMainSetStateNon, sub_2DB8D0, nullsub_15),
// sets flag 5127 and ORs 0x481077C into gBtl+12.
void btlCreate(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ced0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 1;
    sd(v0, gp, kGpUidCounter);  // btlGetUID counter (u64)
    v0 = 256;
    sh(v0, gp, kGpModelIdCounter);  // model id counter (u16)
    a0 = 3440;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x27CEFCu, v0.u());
    sw(v0, gp, kGpBtl);  // gBtl
    a0 = v0;
    a1 = 0;
    a2 = 3440;
    jal(ctx, 0x27CF14u, gen::fn_memset_00521408);
    lw(a0, gp, kGpMsgText);  // MSG.TBL section 4
    jal(ctx, 0x27CF20u, gen::fn_itfMesMngInitialize_003a2d80);
    lw(v1, gp, kGpBtl);  // gBtl
    sw(v0, v1, kBtlMesMng);
    s0 = 5440;
    for (;;) {
        // 0x0027cf4c
        charge(ctx, 4);
        at = slti(s0, 5568);
        if (at == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027cf3c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x27CF40u, gen::fn_sub_3951A0_003951a0);
        s0 = addiu(s0, 1);
    }
    // 0x0027cf5c
    charge(ctx, 3);
    s0 = 5568;
    for (;;) {
        // 0x0027cf78
        charge(ctx, 4);
        at = slti(s0, 5632);
        if (at == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027cf68
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x27CF6Cu, gen::fn_sub_3951A0_003951a0);
        s0 = addiu(s0, 1);
    }
    // 0x0027cf88
    charge(ctx, 35);
    jal(ctx, 0x27CF88u, gen::fn_sub_2D3D70_002d3d70);
    jal(ctx, 0x27CF90u, gen::fn_nullsub_12_0027edf0);
    jal(ctx, 0x27CF98u, gen::fn_sub_2A4A70_002a4a70);
    jal(ctx, 0x27CFA0u, gen::fn_btlSupportResetTimers_002dcbc0);
    jal(ctx, 0x27CFA8u, gen::fn_sub_2E2F30_002e2f30);
    jal(ctx, 0x27CFB0u, gen::fn_nullsub_14_002bb760);
    jal(ctx, 0x27CFB8u, gen::fn_sub_29B090_0029b090);
    jal(ctx, 0x27CFC0u, gen::fn_btlMainSetStateNon_0029df40);
    jal(ctx, 0x27CFC8u, gen::fn_sub_2DB8D0_002db8d0);
    jal(ctx, 0x27CFD0u, gen::fn_nullsub_15_002bf970);
    a0 = 5127;
    a1 = 1;
    jal(ctx, 0x27CFE0u, gen::fn_datSetFlag_0016f1f0);
    lw(a1, gp, kGpBtl);  // gBtl
    lw(a0, a1, kBtlFlags);
    v1 = 0x4810000;
    v1 = v1 | 0x77C;
    v1 = a0 | v1;
    sw(v1, a1, kBtlFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027D020 sub_27D020 -- 428 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlDestroy] (btlDestroyTask): the reverse of btlCreate: frees the btlActions (sub_29A140) and the units (sub_2879F0),
// closes the scene (sub_29E370), the sub-systems' exit functions, frees the packets (sub_27F1C0), closes the message
// manager, clears flag 5127, closes the result screen (sub_1F1C20, when gBtl+3368), destroys the setup's genus when the
// battle owns them (gBtl+12 bit 15: the four party records +2988, three reinforcement slots +3012 (stride 8) and the
// enemy genus +3004), destroys the "battle" task tree (gBtl+3352) when the task exists, frees gBtl and clears the slot.
// Returns 0.
void sub_27D020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d020
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x27D02Cu, gen::fn_sub_29A140_0029a140);
    jal(ctx, 0x27D034u, gen::fn_sub_2879F0_002879f0);
    jal(ctx, 0x27D03Cu, gen::fn_sub_29E370_0029e370);
    jal(ctx, 0x27D044u, gen::fn_nullsub_13_0029dfb0);
    jal(ctx, 0x27D04Cu, gen::fn_sub_2BB770_002bb770);
    jal(ctx, 0x27D054u, gen::fn_sub_2E2F80_002e2f80);
    jal(ctx, 0x27D05Cu, gen::fn_nullsub_19_002dcd20);
    jal(ctx, 0x27D064u, gen::fn_sub_2A4C20_002a4c20);
    jal(ctx, 0x27D06Cu, gen::fn_sub_2DB980_002db980);
    jal(ctx, 0x27D074u, gen::fn_nullsub_16_002bf980);
    jal(ctx, 0x27D07Cu, gen::fn_sub_2F8790_002f8790);
    jal(ctx, 0x27D084u, gen::fn_sub_27F1C0_0027f1c0);
    lw(v0, gp, kGpBtl);  // gBtl
    lw(a0, v0, kBtlMesMng);
    jal(ctx, 0x27D094u, gen::fn_itfMesMngDestroyHandle_003a3060);
    a0 = 5127;
    a1 = 0;
    jal(ctx, 0x27D0A4u, gen::fn_datSetFlag_0016f1f0);
    lw(v0, gp, kGpBtl);  // gBtl
    lw(a0, v0, kBtlResultTask);
    if (a0 != 0) {
        // 0x0027d0bc
        charge(ctx, 2);
        jal(ctx, 0x27D0BCu, gen::fn_sub_1F1C20_001f1c20);
    }
    // 0x0027d0c4
    charge(ctx, 5);
    lw(v0, gp, kGpBtl);  // gBtl
    lw(v0, v0, kBtlFlags);
    v0 = v0 & 0x8000;
    if (v0 != 0) {
        // 0x0027d0d8
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0027d110
            charge(ctx, 4);
            v0 = s0 & 0xFFFF;
            v0 = slti(v0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027d0e4
            charge(ctx, 7);
            lw(v1, gp, kGpBtl);  // gBtl
            v0 = s0 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(a0, v0, kBtlSetupParty);
            if (a0 != 0) {
                // 0x0027d100
                charge(ctx, 2);
                jal(ctx, 0x27D100u, gen::fn_datUnitDestroyGenus_002ff760);
            }
            // 0x0027d108
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x0027d120
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0027d158
            charge(ctx, 4);
            v0 = s0 & 0xFFFF;
            v0 = sltiu(v0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027d12c
            charge(ctx, 7);
            lw(v1, gp, kGpBtl);  // gBtl
            v0 = s0 & 0xFFFF;
            v0 = sll(v0, 3);
            v0 = addu(v1, v0);
            lw(a0, v0, kBtlSetupReinforce);
            if (a0 != 0) {
                // 0x0027d148
                charge(ctx, 2);
                jal(ctx, 0x27D148u, gen::fn_datUnitDestroyGenus_002ff760);
            }
            // 0x0027d150
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x0027d168
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl
        lw(a0, v0, kBtlSetupEnemies);
        jal(ctx, 0x27D170u, gen::fn_datUnitDestroyGenus_002ff760);
    }
    // 0x0027d178
    charge(ctx, 5);
    a0 = addiu(gp, -26600);  // "battle"
    jal(ctx, 0x27D17Cu, gen::fn_kwlnTaskGetTaskByName_00195340);
    if (v0 != 0) {
        // 0x0027d18c
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl
        lw(a0, v0, kBtlRootTask);
        jal(ctx, 0x27D194u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    // 0x0027d19c
    charge(ctx, 12);
    lw(a0, gp, kGpBtl);  // gBtl
    v0 = 0x960000;
    lw(v0, v0, kRwFreeLo);  // 0x96017C
    jalr(ctx, 0x27D1A8u, v0.u());
    sw(zero, gp, kGpBtl);  // gBtl
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027D5E0 btlScrCmd_CALL_BATTLE -- 324 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlScrCmd_CALL_BATTLE (BF COMM): starts a battle with encounter scrGetIntPara(0): the encounter fade task
// (sub_2FF260(1)), a 52-byte setup block on the stack (+4 the hero datUnitCreatePc(1), +8.. the party members
// datUnitCreatePc(sub_16DD60(i)) for i < 4 when non-zero, +20 the enemy genus datUnitCreateEc(encounter) -- it overwrites
// the fourth party slot --, +24 / +26 the ENCOUNT record's field / room, 221 / 1 when both are 0) handed to
// adminiChangeSeq(6, block, 52, 0). Returns 1.
void btlScrCmd_CALL_BATTLE(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d5e0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x27D5FCu, gen::fn_sub_2FF260_002ff260);
    a0 = 0;
    jal(ctx, 0x27D608u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0 & 0xFFFF;
    v0 = sll(s1, 3);
    v0 = subu(v0, s1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpEncountTbl);  // gEncountTbl
    s0 = addu(v0, v1);
    a0 = addiu(sp, 0x50);
    a1 = 0;
    a2 = 52;
    jal(ctx, 0x27D634u, gen::fn_memset_00521408);
    a0 = 1;
    jal(ctx, 0x27D640u, gen::fn_datUnitCreatePc_002ff340);
    sw(v0, sp, 0x54);
    s2 = 0;
    for (;;) {
        // 0x0027d68c
        charge(ctx, 4);
        s3 = s2 & 0xFFFF;
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027d658
        charge(ctx, 6);
        a0 = s3;
        jal(ctx, 0x27D65Cu, gen::fn_sub_16DD60_0016dd60);
        a0 = v0 & 0xFFFF;
        if (a0 != 0) {
            // 0x0027d670
            charge(ctx, 5);
            jal(ctx, 0x27D670u, gen::fn_datUnitCreatePc_002ff340);
            v1 = sll(s3, 2);
            v1 = addu(v1, sp);
            sw(v0, v1, 88);
        }
        // 0x0027d684
        charge(ctx, 2);
        v0 = addiu(s2, 1);
        s2 = v0 & 0xFFFF;
    }
    // 0x0027d69c
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x27D6A0u, gen::fn_datUnitCreateEc_002ff3e0);
    sw(v0, sp, 0x64);
    lhu(v1, s0, kEncField);
    if (v1 == 0) {
        // 0x0027d6b8
        charge(ctx, 3);
        lhu(v0, s0, kEncRoom);
        if (v0 != 0) {
            goto L_0027d6dc;
        }
        // 0x0027d6c4
        charge(ctx, 6);
        v0 = 221;
        sh(v0, sp, 0x68);
        v0 = 1;
        sh(v0, sp, 0x6A);
        goto L_0027d6e8;
    }
L_0027d6dc:
    charge(ctx, 3);
    sh(v1, sp, 0x68);
    lhu(v0, s0, kEncRoom);
    sh(v0, sp, 0x6A);
L_0027d6e8:
    charge(ctx, 15);
    a0 = 6;
    a1 = addiu(sp, 0x50);
    a2 = 52;
    a3 = 0;
    jal(ctx, 0x27D6F8u, gen::fn_adminiChangeSeq_0027c080);
    v0 = 1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0027D730 sub_27D730 -- 220 bytes; frame 0x10: ra sp+0x0
// [btlScrCmd_WAIT_BATTLE] (BF COMM): waits for the battle to end: nothing before the command's 11th frame
// (scrGetCmdTimer); while gBtl exists the game-over latch *(gp-18688) is cleared and it waits; afterwards a living hero
// ends the command (1); a dead hero (datCalcIsDead(datGetUnit(1), 0)) starts the game over once: flag 5149, sub_45A400,
// the field's main script as a script task (scrCreateTaskFromScriptMemory(10, g_fldMainScriptPtr, size, 1)),
// sub_1A62C0(current script +228), the latch = 1. Returns 0 while waiting.
void sub_27D730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d730
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27D738u, gen::fn_scrGetCmdTimer_0035f130);
    at = slti(v0, 11);
    if (at == 0) {
        // 0x0027d74c
        charge(ctx, 3);
        lw(v0, gp, kGpBtl);  // gBtl
        if (v0 == 0) {
            // 0x0027d768
            charge(ctx, 3);
            lw(v0, gp, kGpGameOverLatch);  // game-over script started
            if (v0 != 0) {
                goto L_0027d7f8;
            }
            // 0x0027d774
            charge(ctx, 9);
            a0 = 1;
            jal(ctx, 0x27D778u, gen::fn_datGetUnit_0016cd60);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x27D788u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 != 0) {
                // 0x0027d798
                charge(ctx, 21);
                a0 = 5149;
                a1 = 1;
                jal(ctx, 0x27D7A0u, gen::fn_datSetFlag_0016f1f0);
                jal(ctx, 0x27D7A8u, gen::fn_sub_45A400_0045a400);
                lw(a2, gp, -19148);  // g_fldMainScriptSize
                a0 = 10;
                lw(a1, gp, -19144);  // g_fldMainScriptPtr
                a3 = 1;
                jal(ctx, 0x27D7C0u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                jal(ctx, 0x27D7C8u, gen::fn_scrGetCurrent_0035f150);
                lw(a0, v0, 228);
                jal(ctx, 0x27D7D4u, gen::fn_sub_1A62C0_001a62c0);
                v0 = 1;
                sw(v0, gp, kGpGameOverLatch);  // game-over script started
                goto L_0027d7f8;
            }
            // 0x0027d7ec
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0027d758
            charge(ctx, 4);
            sw(zero, gp, kGpGameOverLatch);  // game-over script started
            v0 = 0;
        }
        // 0x0027d7fc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0027d7f8:
    charge(ctx, 1);
    v0 = 0;
    // 0x0027d7fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027D810 sub_27D810 -- 40 bytes; frame 0x10: ra sp+0x0
// [btlScrCmd_ENCOUNT_FADE] (BF COMM): the encounter fade task sub_2FF260(1); returns 1.
void sub_27D810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d810
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x27D81Cu, gen::fn_sub_2FF260_002ff260);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027D8D0 sub_27D8D0 -- 780 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUpdatePartyAfterBattle] (two field callers): for the ten party members i = 1..10: x = sub_16C470(i) (u32 -> float,
// the R5900 mula / madd with the $gp constant at gp-32656) + datCalcRand(8) + 1, clamped to the AICALC section-9 pair
// {min, max} of member i (u16 at *(gp-18528) + 4i / + 4i + 2), doubled with flag 3026, plus 20 / 50 / 100 % with the
// skills 522 / 523 / 524 (datCalcHasSkill on datGetUnit(i)); the result goes to sub_16D930(i, v) and sub_16D980(i, v).
void sub_27D8D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0027d8d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 1;
    for (;;) {
        // 0x0027dbb0
        charge(ctx, 3);
        v1 = slti(s2, 11);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027d8f4
        charge(ctx, 6);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x27D8FCu, gen::fn_sub_16C470_0016c470);
        if (i64(v0) < 0) {
            // 0x0027d920
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x0027d90c
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x0027d93c
        charge(ctx, 11);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        lwc1(f0, gp, kGpPartyRangeScale);  // f32 constant
        mula_s(f0, f2);
        madd_s(f1, f1, f2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0027d980
            charge(ctx, 6);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFFFF;
        } else {
            // 0x0027d968
            charge(ctx, 6);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            v1 = v1 & 0xFFFF;
        }
        // 0x0027d998
        charge(ctx, 17);
        s0 = v1 & 0xFFFF;
        a0 = 8;
        jal(ctx, 0x27D9A0u, gen::fn_datCalcRand_002ffbc0);
        v0 = v0 & 0xFFFF;
        v0 = addiu(v0, 1);
        v0 = v0 & 0xFFFF;
        v0 = addu(s0, v0);
        s0 = v0 & 0xFFFF;
        lw(v1, gp, kGpAiPartyRange);  // AICALC.TBL section 9
        v0 = sll(s2, 2);
        v0 = addu(v1, v0);
        lhu(v1, v0, 0);
        lhu(v0, v0, 2);
        at = slt(s0, v1);
        if (at == 0) {
            // 0x0027d9e8
            charge(ctx, 4);
            v0 = v0 & 0xFFFF;
            at = slt(v0, s0);
            if (at != 0) {
                // 0x0027d9f8
                charge(ctx, 1);
                s0 = v0;
            }
        } else {
            // 0x0027d9dc
            charge(ctx, 3);
            s0 = v1;
        }
        // 0x0027d9fc
        charge(ctx, 5);
        a0 = 3026;
        jal(ctx, 0x27DA00u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x0027da10
            charge(ctx, 4);
            v0 = 0x40000000;
            mtc1(v0, f1);
            if (i64(s0) < 0) {
                // 0x0027da34
                charge(ctx, 7);
                v1 = srl(s0, 1);
                v0 = s0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x0027da20
                charge(ctx, 5);
                mtc1(s0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x0027da50
            charge(ctx, 7);
            mul_s(f1, f1, f0);
            v0 = 0x4F000000;
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0027da84
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x0027da6c
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFFFF;
            }
            // 0x0027da9c
            charge(ctx, 1);
            s0 = v1 & 0xFFFF;
        }
        // 0x0027daa0
        charge(ctx, 12);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x27DAA8u, gen::fn_datGetUnit_0016cd60);
        s3 = v0;
        s1 = 0;
        a0 = s3;
        a1 = 522;
        jal(ctx, 0x27DAC0u, gen::fn_datCalcHasSkill_003005e0);
        if (v0 != 0) {
            // 0x0027dad0
            charge(ctx, 8);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 100;
            div(v1, v0);
            mflo(v0);
            s1 = addu(s1, v0);
        }
        // 0x0027daf0
        charge(ctx, 6);
        a0 = s3;
        a1 = 523;
        jal(ctx, 0x27DAF8u, gen::fn_datCalcHasSkill_003005e0);
        if (v0 != 0) {
            // 0x0027db08
            charge(ctx, 10);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 1);
            v0 = 100;
            div(v1, v0);
            mflo(v0);
            s1 = addu(s1, v0);
        }
        // 0x0027db30
        charge(ctx, 6);
        a0 = s3;
        a1 = 524;
        jal(ctx, 0x27DB38u, gen::fn_datCalcHasSkill_003005e0);
        if (v0 != 0) {
            // 0x0027db48
            charge(ctx, 10);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 2);
            v0 = 100;
            div(v1, v0);
            mflo(v0);
            s1 = addu(s1, v0);
        }
        // 0x0027db70
        charge(ctx, 16);
        v0 = s1 & 0xFFFF;
        v0 = addu(s0, v0);
        v0 = v0 & 0xFFFF;
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        a1 = s0;
        jal(ctx, 0x27DB90u, gen::fn_sub_16D930_0016d930);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        a1 = s0;
        jal(ctx, 0x27DBA4u, gen::fn_sub_16D980_0016d980);
        s2 = addiu(s2, 1);
    }
    // 0x0027dbbc
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027DC00 sub_27DC00 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketCreate_FF02](a0): a packet of kind 0xFF02 (4 data bytes = a0) whose update is sub_27DBE0.
void sub_27DC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027dc00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0xFF02;
    a1 = 4;
    jal(ctx, 0x27DC18u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, -9248);  // &sub_27DBE0
    sw(v1, v0, kPktUpdate);
    lw(v1, v0, kPktData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027DC80 sub_27DC80 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketCreate_FF03](a0): a packet of kind 0xFF03 (4 data bytes = a0) whose update is sub_27DC50.
void sub_27DC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027dc80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0xFF03;
    a1 = 4;
    jal(ctx, 0x27DC98u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, -9136);  // &sub_27DC50
    sw(v1, v0, kPktUpdate);
    lw(v1, v0, kPktData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027DCD0 btlTableLoad -- 368 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlTableLoad(a0 = row of the table-file list 0x692D40, a1 = sync): loads one battle .TBL file into the table arena
// 0x875D00. The request (*(gp-18456)) is made once: the row's _F name when sub_17D800() (The Answer), else its name. Sync
// waits (H_Cdvd_ReadSync); async returns 0 until H_Cdvd_IsFileLoaded. Then the file's sections ({u32 size, bytes}, each
// padded to 16) go one by one to the row's destinations while dst[k] (+8 + 8k) != 0: *dst[k] = 0x875D00 + arena offset
// (*(gp-18460)), memcpy(size), offset += align16(size), section += align16(size + 4). The request is destroyed and
// cleared; returns 1.
void btlTableLoad(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027dcd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    lw(v0, gp, kGpTblRequest);  // table file request
    if (v0 == 0) {
        // 0x0027dcfc
        charge(ctx, 4);
        jal(ctx, 0x27DCFCu, gen::fn_sub_17D800_0017d800);
        if (v0 == 0) {
            // 0x0027dd28
            charge(ctx, 5);
            lw(a0, s3, kTblName);
            a1 = 0;
            jal(ctx, 0x27DD30u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, gp, kGpTblRequest);  // table file request
        } else {
            // 0x0027dd0c
            charge(ctx, 7);
            lw(a0, s3, kTblNameF);
            a1 = 0;
            jal(ctx, 0x27DD14u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, gp, kGpTblRequest);  // table file request
        }
    }
    // 0x0027dd3c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0027dd44
        charge(ctx, 5);
        lw(a0, gp, kGpTblRequest);  // table file request
        jal(ctx, 0x27DD48u, gen::fn_H_Cdvd_ReadSync_001023a0);
        goto L_0027dd78;
    }
    // 0x0027dd58
    charge(ctx, 5);
    lw(a0, gp, kGpTblRequest);  // table file request
    jal(ctx, 0x27DD5Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
    if (v0 != 0) {
    L_0027dd78:
        charge(ctx, 5);
        lw(v0, gp, kGpTblRequest);  // table file request
        lw(s2, v0, kCdvdData);
        s1 = 0;
        for (;;) {
            // 0x0027ddf8
            charge(ctx, 5);
            v0 = sll(s1, 3);
            v0 = addu(s3, v0);
            lw(v0, v0, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027dd8c
            charge(ctx, 27);
            lw(s0, s2, 0);
            lw(a0, gp, kGpTblArenaOff);  // table arena offset
            v1 = 0x870000;
            v1 = addiu(v1, 23808);  // &0x875D00
            v1 = addu(v1, a0);
            sw(v1, v0, 0);
            v1 = s0 & 0xF;
            a0 = sltu(0, v1);
            v1 = srl(s0, 4);
            v1 = addu(v1, a0);
            a0 = sll(v1, 4);
            lw(v1, gp, kGpTblArenaOff);  // table arena offset
            v1 = addu(v1, a0);
            sw(v1, gp, kGpTblArenaOff);  // table arena offset
            lw(a0, v0, 0);
            a1 = addiu(s2, 4);
            a2 = s0;
            jal(ctx, 0x27DDD0u, gen::fn_memcpy_00521250);
            a0 = addiu(s0, 4);
            v0 = a0 & 0xF;
            v1 = sltu(0, v0);
            v0 = srl(a0, 4);
            v0 = addu(v0, v1);
            v0 = sll(v0, 4);
            s2 = addu(s2, v0);
            s1 = addiu(s1, 1);
        }
        // 0x0027de0c
        charge(ctx, 5);
        lw(a0, gp, kGpTblRequest);  // table file request
        jal(ctx, 0x27DE10u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, gp, kGpTblRequest);  // table file request
        v0 = 1;
    } else {
        // 0x0027dd6c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0027de20 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027DE40 btlTableLoadAll -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// btlTableLoadAll(a0 = sync): a0 != 0 loads the eight rows of 0x692D40 (SKILL, UNIT, MSG, PERSONA, ENCOUNT, EFFECT, MODEL,
// AICALC) synchronously and returns 1; a0 == 0 loads the row of the reload index *(gp-18452) asynchronously and returns 1
// once the index reaches 8.
void btlTableLoadAll(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027de40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 == 0) {
        // 0x0027dea8
        charge(ctx, 14);
        lw(v1, gp, kGpTblReloadIdx);  // table reload index
        v0 = sll(v1, 3);
        v1 = subu(v0, v1);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x690000;
        v0 = addiu(v0, 11584);  // &tbl_btlTableFiles
        a0 = addu(v0, v1);
        a1 = 0;
        jal(ctx, 0x27DED0u, gen::fn_btlTableLoad_0027dcd0);
        if (v0 != 0) {
            // 0x0027dee0
            charge(ctx, 6);
            lw(v0, gp, kGpTblReloadIdx);  // table reload index
            v1 = addiu(v0, 1);
            sw(v1, gp, kGpTblReloadIdx);  // table reload index
            v0 = 8;
            if (v1 != v0) {
                goto L_0027df04;
            }
            // 0x0027def8
            charge(ctx, 3);
            v0 = 1;
            // 0x0027df08 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_0027df04:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0027de54
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0027de90
            charge(ctx, 3);
            v0 = sltiu(s0, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027de60
            charge(ctx, 12);
            v0 = sll(s0, 3);
            v1 = subu(v0, s0);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v1 = sll(v0, 3);
            v0 = 0x690000;
            v0 = addiu(v0, 11584);  // &tbl_btlTableFiles
            a0 = addu(v0, v1);
            a1 = 1;
            jal(ctx, 0x27DE84u, gen::fn_btlTableLoad_0027dcd0);
            s0 = addiu(s0, 1);
        }
        // 0x0027de9c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0027df08 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027DF20 btlTablePatchForAnswer -- 608 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// btlTablePatchForAnswer(): with sub_17D800() (The Answer) copies the Answer's rows over the main game's: MODEL.TBL
// section 0 (296-byte weapon records, *(gp-18664)) +2072.. from section 1 (266-byte party records, *(gp-18660)) +798..
// (two 10-byte, two u16, three 4-byte fields and 23 10-byte rows), 23 12-byte rows of the static table 0x68F0F0 from
// 0x68FAB0, section 1's first record into its record 9 (+2394), EFFECT.TBL section 3 +40 into section 4 +56 (8 bytes),
// sub_2B6490, 23 rows back from 0x68F0F0 to 0x68FAB0, 0x68FA80 -> 0x68FA68 (24 bytes) and 18 12-byte moves inside the
// 0x114-byte rows of 0x68FAB0 (+264 -> +240). Then nullsub_4.
void btlTablePatchForAnswer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027df20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x27DF2Cu, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0027df3c
        charge(ctx, 46);
        lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(v1, 2072);
        a1 = addiu(v0, 798);
        a2 = 10;
        jal(ctx, 0x27DF50u, gen::fn_memcpy_00521250);
        lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(v1, 2082);
        a1 = addiu(v0, 808);
        a2 = 10;
        jal(ctx, 0x27DF6Cu, gen::fn_memcpy_00521250);
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        lhu(v1, v0, 818);
        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0
        sh(v1, v0, 2092);
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        lh(v1, v0, 820);
        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0
        sh(v1, v0, 2094);
        lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(v1, 2096);
        a1 = addiu(v0, 822);
        a2 = 4;
        jal(ctx, 0x27DFA8u, gen::fn_memcpy_00521250);
        lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(v1, 2100);
        a1 = addiu(v0, 826);
        a2 = 4;
        jal(ctx, 0x27DFC4u, gen::fn_memcpy_00521250);
        lw(v1, gp, kGpModelWeapon);  // MODEL.TBL section 0
        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(v1, 2104);
        a1 = addiu(v0, 830);
        a2 = 4;
        jal(ctx, 0x27DFE0u, gen::fn_memcpy_00521250);
        s0 = 0;
        for (;;) {
            // 0x0027e060
            charge(ctx, 3);
            v0 = sltiu(s0, 23);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027dff4
            charge(ctx, 27);
            v0 = sll(s0, 2);
            v0 = addu(v0, s0);
            a0 = sll(v0, 1);
            lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0
            v1 = addu(v0, a0);
            lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
            v0 = addu(v0, a0);
            a0 = addiu(v1, 2108);
            a1 = addiu(v0, 834);
            a2 = 10;
            jal(ctx, 0x27E01Cu, gen::fn_memcpy_00521250);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            a0 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -3856);  // &0x68F0F0
            v1 = addu(v0, a0);
            v0 = 0x690000;
            v0 = addiu(v0, -1360);  // &0x68FAB0
            v0 = addu(v0, a0);
            a0 = addiu(v1, 2184);
            a1 = addiu(v0, 2760);
            a2 = 12;
            jal(ctx, 0x27E054u, gen::fn_memcpy_00521250);
            s0 = addiu(s0, 1);
        }
        // 0x0027e06c
        charge(ctx, 17);
        lw(a1, gp, kGpModelParty);  // MODEL.TBL section 1
        a0 = addiu(a1, 2394);
        a2 = 266;
        jal(ctx, 0x27E078u, gen::fn_memcpy_00521250);
        lw(v1, gp, kGpEffect4);  // EFFECT.TBL section 4
        lw(v0, gp, kGpEffect3);  // EFFECT.TBL section 3
        a0 = addiu(v1, 56);
        a1 = addiu(v0, 40);
        a2 = 8;
        jal(ctx, 0x27E094u, gen::fn_memcpy_00521250);
        jal(ctx, 0x27E09Cu, gen::fn_sub_2B6490_002b6490);
        s0 = 0;
        for (;;) {
            // 0x0027e0ec
            charge(ctx, 3);
            v0 = sltiu(s0, 23);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027e0b0
            charge(ctx, 15);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            a0 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -1360);  // &0x68FAB0
            v1 = addu(v0, a0);
            v0 = 0x690000;
            v0 = addiu(v0, -3856);  // &0x68F0F0
            v0 = addu(v0, a0);
            a0 = addiu(v1, 1932);
            a1 = addiu(v0, 1560);
            a2 = 12;
            jal(ctx, 0x27E0E0u, gen::fn_memcpy_00521250);
            s0 = addiu(s0, 1);
        }
        // 0x0027e0f8
        charge(ctx, 10);
        a0 = 0x690000;
        a0 = addiu(a0, -1432);  // &0x68FA68
        a1 = 0x690000;
        a1 = addiu(a1, -1408);  // &0x68FA80
        a2 = 12;
        jal(ctx, 0x27E10Cu, gen::fn_memcpy_00521250);
        s0 = 0;
        for (;;) {
            // 0x0027e158
            charge(ctx, 3);
            v0 = sltiu(s0, 18);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027e120
            charge(ctx, 14);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, -1360);  // &0x68FAB0
            v0 = addu(v0, v1);
            a0 = addiu(v0, 240);
            a1 = addiu(v0, 264);
            a2 = 12;
            jal(ctx, 0x27E14Cu, gen::fn_memcpy_00521250);
            s0 = addiu(s0, 1);
        }
    }
    // 0x0027e164
    charge(ctx, 7);
    jal(ctx, 0x27E164u, gen::fn_nullsub_4_00177270);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027E180 btlTableInit -- 72 bytes; frame 0x10: ra sp+0x0
// btlTableInit() (kwlnInitMain): zeroes the arena offset, the request and the reload index (gp-18460 / -18456 / -18452),
// loads every table synchronously (btlTableLoadAll(1)), patches them for The Answer, then sub_2BC6D0 and sub_2DD9B0.
void btlTableInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027e180
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sw(zero, gp, kGpTblArenaOff);  // table arena offset
    sw(zero, gp, kGpTblRequest);  // table file request
    sw(zero, gp, kGpTblReloadIdx);  // table reload index
    a0 = 1;
    jal(ctx, 0x27E198u, gen::fn_btlTableLoadAll_0027de40);
    jal(ctx, 0x27E1A0u, gen::fn_btlTablePatchForAnswer_0027df20);
    jal(ctx, 0x27E1A8u, gen::fn_sub_2BC6D0_002bc6d0);
    jal(ctx, 0x27E1B0u, gen::fn_sub_2DD9B0_002dd9b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027E1D0 btlUpdateTableReloadTask -- 152 bytes; frame 0x10: ra sp+0x0
// btlUpdateTableReloadTask (task "btlTableReload"): one async btlTableLoad per frame on the row of the reload index;
// after the eighth row the Answer patch and -1 (the task ends); else 0.
void btlUpdateTableReloadTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027e1d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpTblReloadIdx);  // table reload index
    v0 = sll(v1, 3);
    v1 = subu(v0, v1);
    v0 = sll(v1, 2);
    v0 = subu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x690000;
    v0 = addiu(v0, 11584);  // &tbl_btlTableFiles
    a0 = addu(v0, v1);
    a1 = 0;
    jal(ctx, 0x27E200u, gen::fn_btlTableLoad_0027dcd0);
    if (v0 != 0) {
        // 0x0027e210
        charge(ctx, 6);
        lw(v0, gp, kGpTblReloadIdx);  // table reload index
        v1 = addiu(v0, 1);
        sw(v1, gp, kGpTblReloadIdx);  // table reload index
        v0 = 8;
        if (v1 != v0) {
            goto L_0027e234;
        }
        // 0x0027e228
        charge(ctx, 3);
        v0 = 1;
        goto L_0027e238;
    }
L_0027e234:
    charge(ctx, 1);
    v0 = 0;
L_0027e238:
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x0027e254
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0027e240
        charge(ctx, 5);
        jal(ctx, 0x27E240u, gen::fn_btlTablePatchForAnswer_0027df20);
        v0 = si(-1);
    }
    // 0x0027e258 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027E270 sub_27E270 -- 72 bytes; frame 0x10: ra sp+0x0
// [btlTableCreateReloadTask](parent): zeroes the arena offset, request and reload index and creates the
// "btlTableReload" task (kwlnTaskCreate(a0, name, 10, btlUpdateTableReloadTask, 0, 0)).
void sub_27E270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027e270
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sw(zero, gp, kGpTblArenaOff);  // table arena offset
    sw(zero, gp, kGpTblRequest);  // table file request
    sw(zero, gp, kGpTblReloadIdx);  // table reload index
    a1 = 0x690000;
    a1 = addiu(a1, 12928);  // "btlTableReload"
    a2 = 10;
    a3 = 0x280000;
    a3 = addiu(a3, -7728);  // &btlUpdateTableReloadTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x27E2A0u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027E2C0 sub_27E2C0 -- 72 bytes; frame 0x10: ra sp+0x0
// [btlTableCreateReloadTask2](parent): the same body as sub_27E270 (a second copy in the binary).
void sub_27E2C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027e2c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sw(zero, gp, kGpTblArenaOff);  // table arena offset
    sw(zero, gp, kGpTblRequest);  // table file request
    sw(zero, gp, kGpTblReloadIdx);  // table reload index
    a1 = 0x690000;
    a1 = addiu(a1, 12928);  // "btlTableReload"
    a2 = 10;
    a3 = 0x280000;
    a3 = addiu(a3, -7728);  // &btlUpdateTableReloadTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x27E2F0u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027E530 sub_27E530 -- 1752 bytes; frame 0x10: ra sp+0x0
// [btlPacketTestCond](a0 = condition, a1 = the packet's age): one start / end condition of a packet (16 bytes: kind
// byte, u64 argument at +8), through the 12-entry jump table 0x7B7AC0 (kind - 1): 1 always; 2 age >= arg (s32); 3 / 4 a
// live packet (flag 0x20) whose id (+88, top two bits masked) == arg exists / does not; 5 none such or it is running
// (phase 2); 6 / 7 / 8 the same on the owner id (+96); 9 / 10 a live packet of kind (u16 +64) arg exists / does not; 11 /
// 12 the first live packet with that id / owner: its query callback (+116, $a0 = its data, $a1 = gBtl, $a2 = arg) decides,
// 0 without one (true when none is found). Kind 0 and > 12: false. The four queues are searched head to tail.
void sub_27E530(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027e530
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0;
    lbu(v1, a0, kCondKind);
    at = sltiu(v1, 13);
    if (at != 0) {
        // 0x0027e54c
        charge(ctx, 7);
        a2 = 0x7B0000;
        a2 = addiu(a2, 31424);  // &0x7B7AC0
        v1 = sll(v1, 2);
        v1 = addu(v1, a2);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x27E568u:  // table[1] -- kind 1: always
            // 0x0027e568
            charge(ctx, 3);
            v0 = 1;
            break;
        case 0x27E574u:  // table[2] -- kind 2: the packet's age >= arg (s32 compare)
            // 0x0027e574
            charge(ctx, 4);
            lw(v1, a0, kCondArg);
            at = slt(a1, v1);
            if (at == 0) {
                // 0x0027e584
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E590u:  // table[3] -- kind 3: a live packet with id arg exists
            // 0x0027e590
            charge(ctx, 12);
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e60c
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e5c0
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e600
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e5d4
                    charge(ctx, 4);
                    ld(v1, t0, kPktId);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e5e4
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e61c;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e608
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e618
            charge(ctx, 1);
            t0 = 0;
        L_0027e61c:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027e624
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E630u:  // table[4] -- kind 4: no live packet with id arg
            // 0x0027e630
            charge(ctx, 12);
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e6ac
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e660
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e6a0
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e674
                    charge(ctx, 4);
                    ld(v1, t0, kPktId);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e684
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e6bc;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e6a8
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e6b8
            charge(ctx, 1);
            t0 = 0;
        L_0027e6bc:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 == 0) {
                // 0x0027e6c4
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E6D0u:  // table[5] -- kind 5: no live packet with id arg, or it is running (phase 2)
            // 0x0027e6d0
            charge(ctx, 13);
            v0 = 1;
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e750
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e704
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e744
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e718
                    charge(ctx, 4);
                    ld(v1, t0, kPktId);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e728
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e760;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e74c
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e75c
            charge(ctx, 1);
            t0 = 0;
        L_0027e760:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027e768
                charge(ctx, 4);
                lbu(a0, t0, kPktPhase);
                v1 = 2;
                if (a0 != v1) {
                    // 0x0027e778
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
            break;
        case 0x27E784u:  // table[6] -- kind 6: a live packet with owner arg exists
            // 0x0027e784
            charge(ctx, 12);
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e800
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e7b4
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e7f4
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e7c8
                    charge(ctx, 4);
                    ld(v1, t0, kPktOwner);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e7d8
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e810;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e7fc
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e80c
            charge(ctx, 1);
            t0 = 0;
        L_0027e810:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027e818
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E824u:  // table[7] -- kind 7: no live packet with owner arg
            // 0x0027e824
            charge(ctx, 12);
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e8a0
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e854
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e894
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e868
                    charge(ctx, 4);
                    ld(v1, t0, kPktOwner);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e878
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e8b0;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e89c
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e8ac
            charge(ctx, 1);
            t0 = 0;
        L_0027e8b0:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 == 0) {
                // 0x0027e8b8
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E8C4u:  // table[8] -- kind 8: no live packet with owner arg, or it is running
            // 0x0027e8c4
            charge(ctx, 13);
            v0 = 1;
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027e944
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e8f8
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e938
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e90c
                    charge(ctx, 4);
                    ld(v1, t0, kPktOwner);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027e91c
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e954;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027e940
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027e950
            charge(ctx, 1);
            t0 = 0;
        L_0027e954:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027e95c
                charge(ctx, 4);
                lbu(a0, t0, kPktPhase);
                v1 = 2;
                if (a0 != v1) {
                    // 0x0027e96c
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
            break;
        case 0x27E978u:  // table[9] -- kind 9: a live packet of kind arg (u16) exists
            // 0x0027e978
            charge(ctx, 5);
            lhu(a1, a0, kCondArg);
            a2 = 0;
            lw(a0, gp, kGpBtl);  // gBtl
            for (;;) {
                // 0x0027e9d4
                charge(ctx, 3);
                v1 = sltiu(a2, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027e98c
                charge(ctx, 5);
                v1 = sll(a2, 3);
                v1 = addu(a0, v1);
                lw(a3, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027e9c8
                    charge(ctx, 2);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027e9a0
                    charge(ctx, 3);
                    lhu(v1, a3, kPktKind);
                    if (v1 == a1) {
                        // 0x0027e9ac
                        charge(ctx, 4);
                        lbu(v1, a3, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027e9e4;
                        }
                    }
                    charge(ctx, 1);
                    lw(a3, a3, kPktNext);
                }
                // 0x0027e9d0
                charge(ctx, 1);
                a2 = addiu(a2, 1);
            }
            // 0x0027e9e0
            charge(ctx, 1);
            a3 = 0;
        L_0027e9e4:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (a3 != 0) {
                // 0x0027e9ec
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27E9F8u:  // table[10] -- kind 10: no live packet of kind arg
            // 0x0027e9f8
            charge(ctx, 5);
            lhu(a1, a0, kCondArg);
            a2 = 0;
            lw(a0, gp, kGpBtl);  // gBtl
            for (;;) {
                // 0x0027ea54
                charge(ctx, 3);
                v1 = sltiu(a2, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027ea0c
                charge(ctx, 5);
                v1 = sll(a2, 3);
                v1 = addu(a0, v1);
                lw(a3, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027ea48
                    charge(ctx, 2);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027ea20
                    charge(ctx, 3);
                    lhu(v1, a3, kPktKind);
                    if (v1 == a1) {
                        // 0x0027ea2c
                        charge(ctx, 4);
                        lbu(v1, a3, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027ea64;
                        }
                    }
                    charge(ctx, 1);
                    lw(a3, a3, kPktNext);
                }
                // 0x0027ea50
                charge(ctx, 1);
                a2 = addiu(a2, 1);
            }
            // 0x0027ea60
            charge(ctx, 1);
            a3 = 0;
        L_0027ea64:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x0027ea6c
                charge(ctx, 3);
                v0 = 1;
            }
            break;
        case 0x27EA78u:  // table[11] -- kind 11: the live packet with id arg answers its query callback (true when none)
            // 0x0027ea78
            charge(ctx, 13);
            v0 = 1;
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027eaf8
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027eaac
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027eaec
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027eac0
                    charge(ctx, 4);
                    ld(v1, t0, kPktId);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027ead0
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027eb08;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027eaf4
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027eb04
            charge(ctx, 1);
            t0 = 0;
        L_0027eb08:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027eb10
                charge(ctx, 3);
                lw(v0, t0, kPktQuery);
                if (v0 == 0) {
                    // 0x0027eb30
                    charge(ctx, 3);
                    v0 = 0;
                } else {
                    // 0x0027eb1c
                    charge(ctx, 5);
                    lw(a0, t0, kPktData);
                    jalr(ctx, 0x27EB20u, v0.u());
                }
            }
            break;
        case 0x27EB3Cu:  // table[12] -- kind 12: the live packet with owner arg answers its query callback (true when none)
            // 0x0027eb3c
            charge(ctx, 13);
            v0 = 1;
            ld(a2, a0, kCondArg);
            a3 = 0;
            lw(a1, gp, kGpBtl);  // gBtl
            v1 = 0x3FFF0000;
            v1 = v1 | 0xFFFF;
            a0 = dsll32(v1, 0);
            v1 = 0xFFFF;
            v1 = dsll(v1, 16);
            v1 = v1 | 0xFFFF;
            a0 = v1 | a0;
            for (;;) {
                // 0x0027ebbc
                charge(ctx, 3);
                v1 = sltiu(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0027eb70
                charge(ctx, 5);
                v1 = sll(a3, 3);
                v1 = addu(a1, v1);
                lw(t0, v1, kBtlPktHead);
                for (;;) {
                    // 0x0027ebb0
                    charge(ctx, 2);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0027eb84
                    charge(ctx, 4);
                    ld(v1, t0, kPktOwner);
                    v1 = v1 & a0;
                    if (a2 == v1) {
                        // 0x0027eb94
                        charge(ctx, 4);
                        lbu(v1, t0, kPktFlags);
                        v1 = v1 & 0x20;
                        if (v1 != 0) {  // a live packet: found
                            charge(ctx, 2);
                            goto L_0027ebcc;
                        }
                    }
                    charge(ctx, 1);
                    lw(t0, t0, kPktNext);
                }
                // 0x0027ebb8
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0027ebc8
            charge(ctx, 1);
            t0 = 0;
        L_0027ebcc:  // found (t0 = the packet) or not (t0 = 0)
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x0027ebd4
                charge(ctx, 3);
                lw(v0, t0, kPktQuery);
                if (v0 == 0) {
                    // 0x0027ebf4
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x0027ebe0
                    charge(ctx, 5);
                    lw(a0, t0, kPktData);
                    jalr(ctx, 0x27EBE4u, v0.u());
                }
            }
            break;
        case 0x27EBF8u:  // table[0] -- kind 0: false
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0027ebf8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
}

// 0x0027EC10 sub_27EC10 -- 264 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketAlloc](a0 = kind, a1 = data size): RwMalloc(144 + size), zeroed: kind (+64), both start and end conditions
// "always" (kind 1), the data pointer (+120) = packet + 144 when size > 0, flags (+71) |= 0x31. Not queued yet (see
// sub_27ED20). 99 callers: every packet creator.
void sub_27EC10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ec10
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s1 = a1;
    s2 = addiu(s1, 144);
    a0 = s2;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x27EC44u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = s2;
    jal(ctx, 0x27EC5Cu, gen::fn_memset_00521408);
    sw(s3, s0, kPktKind);
    a0 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027ec90
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027ec78
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        sb(v1, v0, 0);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x0027eca0
    charge(ctx, 4);
    a0 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027ecc8
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027ecb0
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        sb(v1, v0, 32);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x0027ecd8
    charge(ctx, 2);
    if (i64(s1) > 0) {
        // 0x0027ece0
        charge(ctx, 2);
        v0 = addiu(s0, 144);
        sw(v0, s0, kPktData);
    }
    // 0x0027ece8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    lbu(v0, s0, kPktFlags);
    v0 = v0 | 0x31;
    sb(v0, s0, kPktFlags);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027ED20 sub_27ED20 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketQueue](a0 = packet, a1 = queue 0..3): gives the packet its id (btlGetUID, +88), age / run frames 0, phase 0,
// queue a1, flag 8 (queued), runs its on-queue callback (+104, with its data), and appends it at the tail of queue a1
// (gBtl+372 + 8q head, +368 + 8q tail; +124 next, +128 prev). Returns the id (ld +88).
void sub_27ED20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ed20
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    jal(ctx, 0x27ED38u, gen::fn_sub_27CB80_0027cb80);
    sd(v0, s0, kPktId);
    sw(zero, s0, kPktAge);
    sw(zero, s0, kPktRunFrames);
    sb(zero, s0, kPktPhase);
    sb(s1, s0, kPktQueue);
    lbu(v0, s0, kPktFlags);
    v0 = v0 | 0x8;
    sb(v0, s0, kPktFlags);
    lw(v0, s0, kPktOnQueue);
    if (v0 != 0) {
        // 0x0027ed6c
        charge(ctx, 3);
        lw(a0, s0, kPktData);
        jalr(ctx, 0x27ED70u, v0.u());
    }
    // 0x0027ed78
    charge(ctx, 9);
    sw(zero, s0, kPktNext);
    v0 = s1 & 0xFF;
    a0 = sll(v0, 3);
    lw(v1, gp, kGpBtl);  // gBtl
    v0 = addiu(v1, 368);
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 == 0) {
        // 0x0027edb8
        charge(ctx, 3);
        v0 = addu(a0, v1);
        sw(s0, v0, kBtlPktHead);
        sw(zero, s0, kPktPrev);
    } else {
        // 0x0027ed9c
        charge(ctx, 7);
        sw(s0, v0, kPktNext);  // the old tail's next
        lw(v0, gp, kGpBtl);  // gBtl
        v0 = addu(a0, v0);
        lw(v0, v0, kBtlPktTail);
        sw(v0, s0, kPktPrev);
    }
    // 0x0027edc4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v0, gp, kGpBtl);  // gBtl
    v0 = addu(a0, v0);
    sw(s0, v0, kBtlPktTail);
    ld(v0, s0, kPktId);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027EDF0 nullsub_12 -- 8 bytes; leaf frame (no stack)
// nullsub_12: an empty init hook (btlCreate).
void nullsub_12(EEContext& ctx) {
    using namespace hg;
    // 0x0027edf0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0027EE00 sub_27EE00 -- 852 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketUpdate](a0 = packet): one frame of a queued packet, unless paused (+70) or not queued (flag 8 clear). A
// packet flagged 4 (kill) runs its end callback (+112), is unlinked and freed. Else age++, then by phase (+69): 0 waits
// until both start conditions hold (sub_27E530 on +0 / +16 with the age) -> 1; 1 counts the start delay (+72) down -> 2;
// 2 runs the update callback (+108, with the data; run frames +80 count) until it returns non-zero -> 3; 3 waits for both
// end conditions (+32 / +48) -> 4; 4 counts the end delay (+74) down, then the end callback, unlink, RwFree.
void sub_27EE00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027ee00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lbu(v1, a0, kPktPaused);  // nothing while paused or not queued
    if (v1 == 0) {
        // 0x0027ee24
        charge(ctx, 4);
        lbu(a0, s2, kPktFlags);
        v1 = a0 & 0x8;
        if (v1 != 0) {
            // 0x0027ee34
            charge(ctx, 3);
            v1 = a0 & 0x4;
            if (v1 == 0) {  // the phase machine (kill flag clear)
                // 0x0027eef0
                charge(ctx, 7);
                lw(s1, s2, kPktAge);
                v1 = addiu(s1, 1);
                sw(v1, s2, kPktAge);
                lbu(a0, s2, kPktPhase);  // 4, 3, 2, 1, 0: tested from the last
                v1 = 4;
                if (a0 != v1) {
                    // 0x0027ef0c
                    charge(ctx, 3);
                    v1 = 3;
                    if (a0 != v1) {
                        // 0x0027ef18
                        charge(ctx, 3);
                        v1 = 2;
                        if (a0 != v1) {
                            // 0x0027ef24
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 != v1) {
                                // 0x0027ef30
                                charge(ctx, 2);
                                if (a0 == 0) {  // phase 0: both start conditions
                                    // 0x0027ef40
                                    charge(ctx, 3);
                                    s0 = 0;
                                    for (;;) {
                                        // 0x0027ef80
                                        charge(ctx, 4);
                                        v1 = s0 & 0xFFFF;
                                        v1 = slti(v1, 2);
                                        if (v1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                        // 0x0027ef4c
                                        charge(ctx, 8);
                                        v0 = s0 & 0xFFFF;
                                        v0 = sll(v0, 4);
                                        a0 = addu(s2, v0);
                                        a1 = s1;
                                        jal(ctx, 0x27EF5Cu, gen::fn_sub_27E530_0027e530);
                                        if (v0 == 0) {
                                            goto L_0027ef6c_21;
                                        }
                                        // 0x0027ef78
                                        charge(ctx, 2);
                                        v1 = addiu(s0, 1);
                                        s0 = v1 & 0xFFFF;
                                    }
                                    // 0x0027ef90
                                    charge(ctx, 1);
                                    v1 = 1;
                                L_0027ef94:
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        // 0x0027ef9c
                                        charge(ctx, 2);
                                        v1 = 1;
                                        sb(v1, s2, kPktPhase);
                                        goto L_0027efa4;
                                    }
                                } else {
                                    // 0x0027ef38
                                    charge(ctx, 2);
                                }
                                // 0x0027f138 (the shared epilogue, written out on this path)
                                charge(ctx, 7);
                                ld(ra, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x40);
                                return;
                            }
                        L_0027efa4:  // phase 1: the start delay
                            charge(ctx, 3);
                            lh(v1, s2, kPktStartDelay);
                            if (i64(v1) <= 0) {
                                // 0x0027efb0
                                charge(ctx, 4);
                                v0 = 2;
                                sb(v0, s2, kPktPhase);
                                goto L_0027efd0;
                            }
                            // 0x0027efc0
                            charge(ctx, 4);
                            v1 = addiu(v1, -1);
                            sh(v1, s2, kPktStartDelay);
                            // 0x0027f138 (the shared epilogue, written out on this path)
                            charge(ctx, 7);
                            ld(ra, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x40);
                            return;
                        }
                    L_0027efd0:  // phase 2: the update callback until it returns non-zero
                        charge(ctx, 6);
                        lw(a0, s2, kPktData);
                        lw(v0, s2, kPktUpdate);
                        jalr(ctx, 0x27EFD8u, v0.u());
                        if (v0 != 0) {
                            // 0x0027efe8
                            charge(ctx, 4);
                            v1 = 3;
                            sb(v1, s2, kPktPhase);
                            goto L_0027f00c;
                        }
                        // 0x0027eff8
                        charge(ctx, 5);
                        lw(v1, s2, kPktRunFrames);
                        v1 = addiu(v1, 1);
                        sw(v1, s2, kPktRunFrames);
                        // 0x0027f138 (the shared epilogue, written out on this path)
                        charge(ctx, 7);
                        ld(ra, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x40);
                        return;
                    }
                L_0027f00c:  // phase 3: both end conditions
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x0027f050
                        charge(ctx, 4);
                        v1 = s0 & 0xFFFF;
                        v1 = slti(v1, 2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0027f018
                        charge(ctx, 9);
                        v0 = s0 & 0xFFFF;
                        v0 = sll(v0, 4);
                        v0 = addu(v0, s2);
                        a0 = addiu(v0, 32);
                        a1 = s1;
                        jal(ctx, 0x27F02Cu, gen::fn_sub_27E530_0027e530);
                        if (v0 == 0) {
                            goto L_0027f03c_35;
                        }
                        // 0x0027f048
                        charge(ctx, 2);
                        v1 = addiu(s0, 1);
                        s0 = v1 & 0xFFFF;
                    }
                    // 0x0027f060
                    charge(ctx, 1);
                    v1 = 1;
                L_0027f064:
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x0027f06c
                        charge(ctx, 2);
                        v1 = 4;
                        sb(v1, s2, kPktPhase);
                        goto L_0027f074;
                    }
                    // 0x0027f138 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x40);
                    return;
                }
            L_0027f074:  // phase 4: the end delay, then the end callback, unlink, RwFree
                charge(ctx, 3);
                lh(v1, s2, kPktEndDelay);
                if (i64(v1) > 0) {
                    // 0x0027f130
                    charge(ctx, 2);
                    v1 = addiu(v1, -1);
                    sh(v1, s2, kPktEndDelay);
                } else {
                    // 0x0027f080
                    charge(ctx, 3);
                    lw(v0, s2, kPktOnEnd);
                    if (v0 != 0) {
                        // 0x0027f08c
                        charge(ctx, 3);
                        lw(a0, s2, kPktData);
                        jalr(ctx, 0x27F090u, v0.u());
                    }
                    // 0x0027f098
                    charge(ctx, 4);
                    lbu(v0, s2, kPktFlags);
                    v0 = v0 & 0x8;
                    if (v0 != 0) {
                        // 0x0027f0a8
                        charge(ctx, 4);
                        lbu(a1, s2, kPktQueue);
                        lw(v1, s2, kPktPrev);
                        if (v1 == 0) {
                            // 0x0027f0c8
                            charge(ctx, 6);
                            lw(a0, s2, kPktNext);
                            lw(v1, gp, kGpBtl);  // gBtl
                            v0 = a1 & 0xFF;
                            v0 = sll(v0, 3);
                            v0 = addu(v0, v1);
                            sw(a0, v0, kBtlPktHead);
                        } else {
                            // 0x0027f0b8
                            charge(ctx, 4);
                            lw(v0, s2, kPktNext);
                            sw(v0, v1, kPktNext);
                        }
                        // 0x0027f0e0
                        charge(ctx, 3);
                        lw(v1, s2, kPktNext);
                        if (v1 == 0) {
                            // 0x0027f0fc
                            charge(ctx, 6);
                            lw(a0, s2, kPktPrev);
                            lw(v1, gp, kGpBtl);  // gBtl
                            v0 = a1 & 0xFF;
                            v0 = sll(v0, 3);
                            v0 = addu(v0, v1);
                            sw(a0, v0, kBtlPktTail);
                        } else {
                            // 0x0027f0ec
                            charge(ctx, 4);
                            lw(v0, s2, kPktPrev);
                            sw(v0, v1, kPktPrev);
                        }
                    }
                    // 0x0027f114
                    charge(ctx, 7);
                    a0 = s2;
                    v0 = 0x960000;
                    lw(v0, v0, kRwFreeLo);  // 0x96017C
                    jalr(ctx, 0x27F120u, v0.u());
                }
            } else {  // flag 4 (kill): the end callback, unlink, RwFree at once
                // 0x0027ee40
                charge(ctx, 3);
                lw(v0, s2, kPktOnEnd);
                if (v0 != 0) {
                    // 0x0027ee4c
                    charge(ctx, 3);
                    lw(a0, s2, kPktData);
                    jalr(ctx, 0x27EE50u, v0.u());
                }
                // 0x0027ee58
                charge(ctx, 4);
                lbu(v0, s2, kPktFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x0027ee68
                    charge(ctx, 4);
                    lbu(a1, s2, kPktQueue);
                    lw(v1, s2, kPktPrev);
                    if (v1 == 0) {
                        // 0x0027ee88
                        charge(ctx, 6);
                        lw(a0, s2, kPktNext);
                        lw(v1, gp, kGpBtl);  // gBtl
                        v0 = a1 & 0xFF;
                        v0 = sll(v0, 3);
                        v0 = addu(v0, v1);
                        sw(a0, v0, kBtlPktHead);
                    } else {
                        // 0x0027ee78
                        charge(ctx, 4);
                        lw(v0, s2, kPktNext);
                        sw(v0, v1, kPktNext);
                    }
                    // 0x0027eea0
                    charge(ctx, 3);
                    lw(v1, s2, kPktNext);
                    if (v1 == 0) {
                        // 0x0027eebc
                        charge(ctx, 6);
                        lw(a0, s2, kPktPrev);
                        lw(v1, gp, kGpBtl);  // gBtl
                        v0 = a1 & 0xFF;
                        v0 = sll(v0, 3);
                        v0 = addu(v0, v1);
                        sw(a0, v0, kBtlPktTail);
                    } else {
                        // 0x0027eeac
                        charge(ctx, 4);
                        lw(v0, s2, kPktPrev);
                        sw(v0, v1, kPktPrev);
                    }
                }
                // 0x0027eed4
                charge(ctx, 7);
                a0 = s2;
                v0 = 0x960000;
                lw(v0, v0, kRwFreeLo);  // 0x96017C
                jalr(ctx, 0x27EEE0u, v0.u());
            }
        }
    }
    // 0x0027f138 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_0027ef6c_21:  // a start condition is false
    charge(ctx, 3);
    v1 = 0;
    goto L_0027ef94;
L_0027f03c_35:  // an end condition is false
    charge(ctx, 3);
    v1 = 0;
    goto L_0027f064;
}

// 0x0027F160 sub_27F160 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketUpdateQueue](a0 = queue): btlPacketUpdate for every packet of queue a0, head to tail (the next link read
// first: an update may free the packet). btlUpdateTask runs queues 0 / 1, btlUpdateDraw3DTask 2, btlUpdateDraw2DTask 3.
void sub_27F160(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f160
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, gp, kGpBtl);  // gBtl
    v1 = a0 & 0xFF;
    v1 = sll(v1, 3);
    v1 = addu(v1, a1);
    lw(a0, v1, kBtlPktHead);
    for (;;) {
        // 0x0027f198
        charge(ctx, 4);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f188
        charge(ctx, 4);
        lw(s0, a0, kPktNext);
        jal(ctx, 0x27F18Cu, gen::fn_sub_27EE00_0027ee00);
        a0 = s0;
    }
    // 0x0027f1a8
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027F1C0 sub_27F1C0 -- 284 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketFreeAll]: for the four queues, from the head along the prev link (+128; so in a well-formed queue only the head
// is visited, as in sub_27E4D0): end callback, unlink when queued, RwFree.
void sub_27F1C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f1c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x0027f2b4
        charge(ctx, 3);
        v1 = sltiu(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f1e0
        charge(ctx, 6);
        a0 = sll(s0, 3);
        lw(v1, gp, kGpBtl);  // gBtl
        v1 = addu(v1, a0);
        lw(s2, v1, kBtlPktHead);
        for (;;) {
            // 0x0027f2a8
            charge(ctx, 2);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027f1f8
            charge(ctx, 4);
            lw(s1, s2, kPktPrev);
            lw(v0, s2, kPktOnEnd);
            if (v0 != 0) {
                // 0x0027f208
                charge(ctx, 3);
                lw(a0, s2, kPktData);
                jalr(ctx, 0x27F20Cu, v0.u());
            }
            // 0x0027f214
            charge(ctx, 4);
            lbu(v0, s2, kPktFlags);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                // 0x0027f224
                charge(ctx, 4);
                lbu(a1, s2, kPktQueue);
                lw(v1, s2, kPktPrev);
                if (v1 == 0) {
                    // 0x0027f244
                    charge(ctx, 6);
                    lw(a0, s2, kPktNext);
                    v0 = a1 & 0xFF;
                    v1 = sll(v0, 3);
                    lw(v0, gp, kGpBtl);  // gBtl
                    v0 = addu(v0, v1);
                    sw(a0, v0, kBtlPktHead);
                } else {
                    // 0x0027f234
                    charge(ctx, 4);
                    lw(v0, s2, kPktNext);
                    sw(v0, v1, kPktNext);
                }
                // 0x0027f25c
                charge(ctx, 3);
                lw(v1, s2, kPktNext);
                if (v1 == 0) {
                    // 0x0027f278
                    charge(ctx, 6);
                    lw(a0, s2, kPktPrev);
                    v0 = a1 & 0xFF;
                    v1 = sll(v0, 3);
                    lw(v0, gp, kGpBtl);  // gBtl
                    v0 = addu(v0, v1);
                    sw(a0, v0, kBtlPktTail);
                } else {
                    // 0x0027f268
                    charge(ctx, 4);
                    lw(v0, s2, kPktPrev);
                    sw(v0, v1, kPktPrev);
                }
            }
            // 0x0027f290
            charge(ctx, 6);
            a0 = s2;
            v0 = 0x960000;
            lw(v0, v0, kRwFreeLo);  // 0x96017C
            jalr(ctx, 0x27F29Cu, v0.u());
            s2 = s1;
        }
        // 0x0027f2b0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0027f2c0
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0027F2E0 sub_27F2E0 -- 12 bytes; leaf frame (no stack)
// [btlPacketUpdateDone]: an update callback that finishes at once (returns 1).
void sub_27F2E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0027f2e0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0027F2F0 sub_27F2F0 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketCreateEmpty](): a 144-byte packet of kind 0xFF00 without data (the body of sub_27EC10 inlined) whose update
// finishes at once (sub_27F2E0): a pure synchronisation point for the conditions.
void sub_27F2F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f2f0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 144;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x27F30Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 144;
    jal(ctx, 0x27F324u, gen::fn_memset_00521408);
    v0 = 0xFF00;
    sw(v0, s0, kPktKind);
    a0 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027f35c
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f344
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        sb(v1, v0, 0);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x0027f36c
    charge(ctx, 5);
    a0 = addiu(s0, 32);
    a1 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027f398
        charge(ctx, 4);
        v0 = a1 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f380
        charge(ctx, 6);
        v0 = a1 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(a0, v0);
        sb(v1, v0, 0);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFFFF;
    }
    // 0x0027f3a8
    charge(ctx, 12);
    lbu(v0, s0, kPktFlags);
    v0 = v0 | 0x31;
    sb(v0, s0, kPktFlags);
    v0 = 0x280000;
    v0 = addiu(v0, -3360);  // &sub_27F2E0
    sw(v0, s0, kPktUpdate);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027F3E0 sub_27F3E0 -- 44 bytes; frame 0x10: ra sp+0x0
// [btlPacketUpdateCall](data): the update callback of sub_27F410's packets: returns data->fn(data->arg) (jalr).
void sub_27F3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f3e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    lw(a0, a0, kCallArg);
    lw(v0, v0, kCallFn);
    jalr(ctx, 0x27F3F4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027F410 sub_27F410 -- 276 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreateCall](a0 = fn, a1 = arg): a packet of kind 0xFF01 with 8 data bytes (sub_27EC10 inlined): its update
// calls fn(arg) every frame until it returns non-zero (sub_27F3E0).
void sub_27F410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f410
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 152;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x27F43Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 152;
    jal(ctx, 0x27F454u, gen::fn_memset_00521408);
    v0 = 0xFF01;
    sw(v0, s0, kPktKind);
    a0 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027f48c
        charge(ctx, 4);
        v0 = a0 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f474
        charge(ctx, 6);
        v0 = a0 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        sb(v1, v0, 0);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x0027f49c
    charge(ctx, 5);
    a0 = addiu(s0, 32);
    a1 = 0;
    v1 = 1;
    for (;;) {
        // 0x0027f4c8
        charge(ctx, 4);
        v0 = a1 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027f4b0
        charge(ctx, 6);
        v0 = a1 & 0xFFFF;
        v0 = sll(v0, 4);
        v0 = addu(a0, v0);
        sb(v1, v0, 0);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFFFF;
    }
    // 0x0027f4d8
    charge(ctx, 19);
    v0 = addiu(s0, 144);
    sw(v0, s0, kPktData);
    lbu(v0, s0, kPktFlags);
    v0 = v0 | 0x31;
    sb(v0, s0, kPktFlags);
    v0 = 0x280000;
    v0 = addiu(v0, -3104);  // &sub_27F3E0
    sw(v0, s0, kPktUpdate);
    lw(v0, s0, kPktData);
    sw(s2, v0, kCallFn);
    sw(s1, v0, kCallArg);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0027F530 sub_27F530 -- 280 bytes; leaf frame (no stack)
// [btlUnitInitTransform](unit): position and home position = the zero vector (0x957180), rotation (0, 0, 0, 1), scale
// 1, colour 0xFFFFFFFF copied to the base / from / to colours, colour time 0, the light vector = zero, +112..+120 = 0,
// +124 = 0.5.
void sub_27F530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0027f530
    enter(ctx, 70);  // entry check point + this block's cycles
    a1 = 0x3F800000;
    sw(a1, a0, kUnScale);
    v1 = 0x950000;
    lwc1(f2, v1, kZeroVecLo);  // 0x957180
    v1 = 0x950000;
    lwc1(f1, v1, kZeroVecLo + 4);  // 0x957184
    v1 = 0x950000;
    lwc1(f0, v1, kZeroVecLo + 8);  // 0x957188
    swc1(f2, a0, kUnPos);
    swc1(f1, a0, kUnPos + 4);
    swc1(f0, a0, kUnPos + 8);
    v1 = 0x950000;
    lwc1(f2, v1, kZeroVecLo);  // 0x957180
    v1 = 0x950000;
    lwc1(f1, v1, kZeroVecLo + 4);  // 0x957184
    v1 = 0x950000;
    lwc1(f0, v1, kZeroVecLo + 8);  // 0x957188
    swc1(f2, a0, kUnHome);
    swc1(f1, a0, kUnHome + 4);
    swc1(f0, a0, kUnHome + 8);
    sw(a1, a0, kUnRot + 12);
    sw(zero, a0, kUnRot);
    sw(zero, a0, kUnRot + 4);
    sw(zero, a0, kUnRot + 8);
    v1 = 255;
    sb(v1, a0, kUnColour);
    sb(v1, a0, kUnColour + 1);
    sb(v1, a0, kUnColour + 2);
    sb(v1, a0, kUnColour + 3);
    lbu(a3, a0, kUnColour);
    lbu(a2, a0, kUnColour + 1);
    lbu(a1, a0, kUnColour + 2);
    lbu(v1, a0, kUnColour + 3);
    sb(a3, a0, kUnColourBase);
    sb(a2, a0, kUnColourBase + 1);
    sb(a1, a0, kUnColourBase + 2);
    sb(v1, a0, kUnColourBase + 3);
    lbu(a3, a0, kUnColour);
    lbu(a2, a0, kUnColour + 1);
    lbu(a1, a0, kUnColour + 2);
    lbu(v1, a0, kUnColour + 3);
    sb(a3, a0, kUnColourFrom);
    sb(a2, a0, kUnColourFrom + 1);
    sb(a1, a0, kUnColourFrom + 2);
    sb(v1, a0, kUnColourFrom + 3);
    lbu(a3, a0, kUnColour);
    lbu(a2, a0, kUnColour + 1);
    lbu(a1, a0, kUnColour + 2);
    lbu(v1, a0, kUnColour + 3);
    sb(a3, a0, kUnColourTo);
    sb(a2, a0, kUnColourTo + 1);
    sb(a1, a0, kUnColourTo + 2);
    sb(v1, a0, kUnColourTo + 3);
    sh(zero, a0, kUnColourTime);
    v1 = 0x950000;
    lwc1(f2, v1, kZeroVecLo);  // 0x957180
    v1 = 0x950000;
    lwc1(f1, v1, kZeroVecLo + 4);  // 0x957184
    v1 = 0x950000;
    lwc1(f0, v1, kZeroVecLo + 8);  // 0x957188
    swc1(f2, a0, kUnLight);
    swc1(f1, a0, kUnLight + 4);
    swc1(f0, a0, kUnLight + 8);
    sw(zero, a0, kUn112);
    sw(zero, a0, kUn116);
    sw(zero, a0, kUn120);
    v1 = 0x3F000000;
    sw(v1, a0, kUn124);
}

// 0x0027F650 sub_27F650 -- 44 bytes; leaf frame (no stack)
// [btlUnitSetPos](unit, vec3*): position = *a1; dirty |= 4 (transform changed).
void sub_27F650(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0027f650
    enter(ctx, 11);  // entry check point + this block's cycles
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, a0, kUnPos);
    swc1(f1, a0, kUnPos + 4);
    swc1(f0, a0, kUnPos + 8);
    lw(v1, a0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, a0, kUnDirty);
}

// 0x0027F680 sub_27F680 -- 68 bytes; leaf frame (no stack)
// [btlUnitSetRot](unit, quat*): rotation = *a1 unless the rotation is locked (flags bit 13); dirty |= 4.
void sub_27F680(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0027f680
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kUnFlags);
    v1 = v1 & 0x2000;
    if (v1 == 0) {
        // 0x0027f690
        charge(ctx, 11);
        lwc1(f3, a1, 0);
        lwc1(f2, a1, 4);
        lwc1(f1, a1, 8);
        lwc1(f0, a1, 12);
        swc1(f3, a0, kUnRot);
        swc1(f2, a0, kUnRot + 4);
        swc1(f1, a0, kUnRot + 8);
        swc1(f0, a0, kUnRot + 12);
        lw(v1, a0, kUnDirty);
        v1 = v1 | 0x4;
        sw(v1, a0, kUnDirty);
    }
    // 0x0027f6bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0027F6D0 sub_27F6D0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitResetRot](unit): sub_4BDCB0(&rotation) (the identity), dirty |= 4.
void sub_27F6D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027f6d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, 28);
    jal(ctx, 0x27F6E4u, gen::fn_sub_4BDCB0_004bdcb0);
    lw(v1, s0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, s0, kUnDirty);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027F710 sub_27F710 -- 24 bytes; leaf frame (no stack)
// [btlUnitSetScale](unit, $f12): scale = f12, dirty |= 4.
void sub_27F710(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x0027f710
    enter(ctx, 6);  // entry check point + this block's cycles
    swc1(f12, a0, kUnScale);
    lw(v1, a0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, a0, kUnDirty);
}

// 0x0027F730 sub_27F730 -- 64 bytes; frame 0x10
// [btlUnitSetColour](unit, rgba): the colour bytes = a1 (four sb), dirty |= 4.
void sub_27F730(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    // 0x0027f730
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sw(a1, sp, 0xC);
    lbu(a3, sp, 0xC);
    lbu(a2, sp, 0xD);
    lbu(a1, sp, 0xE);
    lbu(v1, sp, 0xF);
    sb(a3, a0, kUnColour);
    sb(a2, a0, kUnColour + 1);
    sb(a1, a0, kUnColour + 2);
    sb(v1, a0, kUnColour + 3);
    lw(v1, a0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, a0, kUnDirty);
    sp = addiu(sp, 0x10);
}

// 0x0027F770 sub_27F770 -- 32 bytes; leaf frame (no stack)
// [btlUnitShowFlagsSet](unit, bits): u16 +0 |= a1, dirty |= 4.
void sub_27F770(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0027f770
    enter(ctx, 8);  // entry check point + this block's cycles
    lhu(v1, a0, kUnShowFlags);
    v1 = v1 | a1;
    sh(v1, a0, kUnShowFlags);
    lw(v1, a0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, a0, kUnDirty);
}

// 0x0027F790 sub_27F790 -- 44 bytes; leaf frame (no stack)
// [btlUnitShowFlagsClear](unit, bits): u16 +0 &= ~a1, dirty |= 4.
void sub_27F790(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0027f790
    enter(ctx, 11);  // entry check point + this block's cycles
    v1 = a1 & 0xFFFF;
    v1 = nor(v1, 0);
    a1 = v1 & 0xFFFF;
    lhu(v1, a0, kUnShowFlags);
    v1 = v1 & a1;
    sh(v1, a0, kUnShowFlags);
    lw(v1, a0, kUnDirty);
    v1 = v1 | 0x4;
    sw(v1, a0, kUnDirty);
}

// 0x0027F7C0 sub_27F7C0 -- 360 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetGridPos](unit, a1 = vec3 out or 0, a2 = screen out or 0, a3 = target out or 0): the grid position
// (25 * grid x - 1750, position y, 25 * grid z - 1750) into a1; with a2 or a3, a look-at point on the stack: an enemy
// (side 1) asks sub_2F8EA0() and, unless it returns 1, takes the player action's unit's position (sub_280050 on gBtl+328's
// +48); a party unit (side 0) takes sub_280870(2, 1, point, 0, 0, 1); a3 gets the point, a2 = sub_2D1DE0(a2, grid
// position, point).
void sub_27F7C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0027f7c0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    lh(a2, a0, kUnGridX);
    v1 = sll(a2, 2);
    a2 = addu(v1, a2);
    v1 = sll(a2, 2);
    v1 = addu(a2, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x40);
    lwc1(f0, a0, kUnPos + 4);
    swc1(f0, sp, 0x44);
    lh(a2, a0, kUnGridZ);
    v1 = sll(a2, 2);
    a2 = addu(v1, a2);
    v1 = sll(a2, 2);
    v1 = addu(a2, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    if (a1 != 0) {
        // 0x0027f838
        charge(ctx, 6);
        lwc1(f2, sp, 0x40);
        lwc1(f1, sp, 0x44);
        lwc1(f0, sp, 0x48);
        swc1(f2, a1, 0);
        swc1(f1, a1, 4);
        swc1(f0, a1, 8);
    }
    // 0x0027f850
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0027f858
        charge(ctx, 2);
        if (s1 != 0) {
            goto L_0027f860;
        }
        // 0x0027f910 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0027f860:
    charge(ctx, 4);
    lbu(v1, a0, kUnSide);
    a1 = 1;
    if (v1 == a1) {
        // 0x0027f8a4
        charge(ctx, 6);
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x27F8A8u, gen::fn_sub_2F8EA0_002f8ea0);
        v1 = 1;
        if (v0 != v1) {
            // 0x0027f8bc
            charge(ctx, 6);
            lw(v0, gp, kGpBtl);  // gBtl
            lw(v0, v0, kBtlPlayerAction);
            lw(a0, v0, kActUnit);
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x27F8CCu, gen::fn_sub_280050_00280050);
        }
    } else {
        // 0x0027f870
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0027f880
            charge(ctx, 9);
            a0 = 2;
            a2 = addiu(sp, 0x30);
            a3 = 0;
            t0 = 0;
            t1 = a1;
            jal(ctx, 0x27F894u, gen::fn_sub_280870_00280870);
        } else {
            // 0x0027f878
            charge(ctx, 2);
        }
    }
    // 0x0027f8d4
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0027f8dc
        charge(ctx, 6);
        lwc1(f2, sp, 0x30);
        lwc1(f1, sp, 0x34);
        lwc1(f0, sp, 0x38);
        swc1(f2, s0, 0);
        swc1(f1, s0, 4);
        swc1(f0, s0, 8);
    }
    // 0x0027f8f4
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0027f8fc
        charge(ctx, 5);
        a0 = s1;
        a1 = addiu(sp, 0x40);
        a2 = addiu(sp, 0x30);
        jal(ctx, 0x27F908u, gen::fn_sub_2D1DE0_002d1de0);
    }
    // 0x0027f910 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027F930 sub_27F930 -- 12 bytes; leaf frame (no stack)
// [btlUnitGetSub78](unit): the address of the object embedded at +78.
void sub_27F930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0027f930
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = addiu(a0, 78);
}

// 0x0027FC80 sub_27FC80 -- 112 bytes; leaf frame (no stack)
// [btlUnitGetPersonaColour](unit): a persona (side 2) other than id 207 gives its MODEL.TBL section-3 record's byte +86
// as alpha over white ((b << 24) | 0xFFFFFF); everything else -1.
void sub_27FC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0027fc80
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v1, a0, kUnSide);
    v0 = 2;
    if (v1 == v0) {
        // 0x0027fc9c
        charge(ctx, 4);
        lhu(a0, a0, kUnId);
        v0 = 207;
        if (a0 != v0) {
            // 0x0027fcb8
            charge(ctx, 12);
            lw(v1, gp, kGpModelPersona);  // MODEL.TBL section 3
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 3);
            v0 = addu(v0, v1);
            lbu(v0, v0, 86);  // MODEL.TBL section-3 record +86
            v1 = sll(v0, 24);
            v0 = 0xFF0000;
            v0 = v0 | 0xFFFF;  // &0xFFFFFF
            v0 = v1 | v0;
        } else {
            // 0x0027fcac
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x0027fc90
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x0027fce8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0027FCF0 sub_27FCF0 -- 128 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitSetRotFromDir](unit, a1): sub_2D1DE0(stack quat, &position, a1) and, unless the rotation is locked, rotation =
// that quaternion (dirty |= 4); then sub_288110(unit).
void sub_27FCF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0027fcf0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a2 = a1;
    a0 = addiu(sp, 0x20);
    a1 = addiu(s0, 4);
    jal(ctx, 0x27FD0Cu, gen::fn_sub_2D1DE0_002d1de0);
    lw(v0, s0, kUnFlags);
    v0 = v0 & 0x2000;
    if (v0 == 0) {
        // 0x0027fd24
        charge(ctx, 11);
        lwc1(f3, sp, 0x20);
        lwc1(f2, sp, 0x24);
        lwc1(f1, sp, 0x28);
        lwc1(f0, sp, 0x2C);
        swc1(f3, s0, kUnRot);
        swc1(f2, s0, kUnRot + 4);
        swc1(f1, s0, kUnRot + 8);
        swc1(f0, s0, kUnRot + 12);
        lw(v0, s0, kUnDirty);
        v0 = v0 | 0x4;
        sw(v0, s0, kUnDirty);
    }
    // 0x0027fd50
    charge(ctx, 8);
    a0 = s0;
    jal(ctx, 0x27FD54u, gen::fn_sub_288110_00288110);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0027FD70 sub_27FD70 -- 24 bytes; leaf frame (no stack)
// [btlPktXform_OnQueue](data): the transform packet holds its unit: busy counter (+160) ++.
void sub_27FD70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0027fd70
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x0027FD90 sub_27FD90 -- 212 bytes; leaf frame (no stack)
// [btlPktXform_Update](data): applies the transform packet (sub_27FE90) once: mask bit 0 the position, bit 1 the rotation
// (unless locked), bit 2 the colour (dirty |= 4 each); returns 1 (done).
void sub_27FD90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0027fd90
    enter(ctx, 4);  // entry check point + this block's cycles
    lhu(v0, a0, kXfMask);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x0027fda0
        charge(ctx, 10);
        lw(v1, a0, kPdUnit);
        lwc1(f2, a0, kXfPos);
        lwc1(f1, a0, kXfPos + 4);
        lwc1(f0, a0, kXfPos + 8);
        swc1(f2, v1, kUnPos);
        swc1(f1, v1, kUnPos + 4);
        swc1(f0, v1, kUnPos + 8);
        lw(v0, v1, kUnDirty);
        v0 = v0 | 0x4;
        sw(v0, v1, kUnDirty);
    }
    // 0x0027fdc8
    charge(ctx, 4);
    lhu(v0, a0, kXfMask);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x0027fdd8
        charge(ctx, 5);
        lw(v1, a0, kPdUnit);
        lw(v0, v1, kUnFlags);
        v0 = v0 & 0x2000;
        if (v0 == 0) {
            // 0x0027fdec
            charge(ctx, 11);
            lwc1(f3, a0, kXfRot);
            lwc1(f2, a0, kXfRot + 4);
            lwc1(f1, a0, kXfRot + 8);
            lwc1(f0, a0, kXfRot + 12);
            swc1(f3, v1, kUnRot);
            swc1(f2, v1, kUnRot + 4);
            swc1(f1, v1, kUnRot + 8);
            swc1(f0, v1, kUnRot + 12);
            lw(v0, v1, kUnDirty);
            v0 = v0 | 0x4;
            sw(v0, v1, kUnDirty);
        }
    }
    // 0x0027fe18
    charge(ctx, 4);
    lhu(v0, a0, kXfMask);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x0027fe28
        charge(ctx, 12);
        lw(a3, a0, kPdUnit);
        lbu(a2, a0, kXfColour);
        lbu(a1, a0, kXfColour + 1);
        lbu(v1, a0, kXfColour + 2);
        lbu(v0, a0, kXfColour + 3);
        sb(a2, a3, kUnColour);
        sb(a1, a3, kUnColour + 1);
        sb(v1, a3, kUnColour + 2);
        sb(v0, a3, kUnColour + 3);
        lw(v0, a3, kUnDirty);
        v0 = v0 | 0x4;
        sw(v0, a3, kUnDirty);
    }
    // 0x0027fe58 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = 1;
}

// 0x0027FE70 sub_27FE70 -- 24 bytes; leaf frame (no stack)
// [btlPktXform_OnEnd](data): busy counter (+160) --.
void sub_27FE70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0027fe70
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x0027FE90 sub_27FE90 -- 284 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreateXform](unit, pos* or 0, quat* or 0, rgba* or 0): a transform packet (kind 283, 40 data bytes): the unit
// and the given position / rotation / colour with the mask (+36) of the parts given; callbacks sub_27FD70 / sub_27FD90 /
// sub_27FE70.
void sub_27FE90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0027fe90
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a0 = 283;
    a1 = 40;
    jal(ctx, 0x27FEC0u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, -656);  // &sub_27FD70
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, -624);  // &sub_27FD90
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, -400);  // &sub_27FE70
    sw(v1, v0, kPktOnEnd);
    lw(a3, v0, kPktData);
    sw(s3, a3, kPdUnit);
    sh(zero, a3, kXfMask);
    if (s2 != 0) {
        // 0x0027ff00
        charge(ctx, 9);
        lwc1(f2, s2, 0);
        lwc1(f1, s2, 4);
        lwc1(f0, s2, 8);
        swc1(f2, a3, kXfPos);
        swc1(f1, a3, kXfPos + 4);
        swc1(f0, a3, kXfPos + 8);
        lhu(v1, a3, kXfMask);
        v1 = v1 | 0x1;
        sh(v1, a3, kXfMask);
    }
    // 0x0027ff24
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0027ff2c
        charge(ctx, 11);
        lwc1(f3, s1, 0);
        lwc1(f2, s1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, s1, 12);
        swc1(f3, a3, kXfRot);
        swc1(f2, a3, kXfRot + 4);
        swc1(f1, a3, kXfRot + 8);
        swc1(f0, a3, kXfRot + 12);
        lhu(v1, a3, kXfMask);
        v1 = v1 | 0x2;
        sh(v1, a3, kXfMask);
    }
    // 0x0027ff58
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0027ff60
        charge(ctx, 11);
        lbu(a2, s0, 0);
        lbu(a1, s0, 1);
        lbu(a0, s0, 2);
        lbu(v1, s0, 3);
        sb(a2, a3, kXfColour);
        sb(a1, a3, kXfColour + 1);
        sb(a0, a3, kXfColour + 2);
        sb(v1, a3, kXfColour + 3);
        lhu(v1, a3, kXfMask);
        v1 = v1 | 0x4;
        sh(v1, a3, kXfMask);
    }
    // 0x0027ff8c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027FFB0 sub_27FFB0 -- 160 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetCentre](unit, vec3 out): out = position + rotate(centre offset (+128..+136) * scale, rotation) (sub_4BE1E0
// with the stack vectors). 49 callers.
void sub_27FFB0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0027ffb0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lwc1(f0, a0, kUnCentre);
    lwc1(f1, a0, kUnScale);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x40);
    lwc1(f0, a0, kUnCentre + 4);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x44);
    lwc1(f0, a0, kUnCentre + 8);
    mul_s(f0, f0, f1);
    swc1(f0, sp, 0x48);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x40);
    a2 = 1;
    a3 = addiu(s1, 28);
    jal(ctx, 0x280000u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f1, s1, kUnPos);
    lwc1(f0, sp, 0x30);
    add_s(f0, f0, f1);
    swc1(f0, s0, 0);
    lwc1(f1, s1, kUnPos + 4);
    lwc1(f0, sp, 0x34);
    add_s(f0, f0, f1);
    swc1(f0, s0, 4);
    lwc1(f1, s1, kUnPos + 8);
    lwc1(f0, sp, 0x38);
    add_s(f0, f0, f1);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00281270 sub_281270 -- 20 bytes; leaf frame (no stack)
// [btlUnitIsMoving](unit): move flags (+200) bit 0.
void sub_281270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00281270
    enter(ctx, 5);  // entry check point + this block's cycles
    lhu(v0, a0, kUnMoveFlags);
    v0 = v0 & 0x1;
    v0 = sltu(0, v0);
}

// 0x00281290 sub_281290 -- 20 bytes; leaf frame (no stack)
// [btlUnitClearMoving](unit): move flags (+200) &= ~1.
void sub_281290(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00281290
    enter(ctx, 5);  // entry check point + this block's cycles
    lhu(v1, a0, kUnMoveFlags);
    v1 = v1 & 0xFFFE;
    sh(v1, a0, kUnMoveFlags);
}

// 0x002812B0 sub_2812B0 -- 20 bytes; leaf frame (no stack)
// [btlUnitClearTurning](unit): move flags (+200) &= ~2.
void sub_2812B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002812b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lhu(v1, a0, kUnMoveFlags);
    v1 = v1 & 0xFFFD;
    sh(v1, a0, kUnMoveFlags);
}

// 0x002813D0 sub_2813D0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_2819D0 (move) packet holds its unit (data +0): busy counter (+160) ++.
void sub_2813D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002813d0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x002819B0 sub_2819B0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_2819D0 (move) packet releases its unit (data +0): busy counter (+160) --.
void sub_2819B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002819b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x002819D0 sub_2819D0 -- 216 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlPacketCreateMove](unit, vec3* target or 0 (= the zero vector), a2 = frames, $f12 = speed): a unit move packet
// (kind 266, 36 data bytes: unit, target, frames +16, speed +32); callbacks sub_2813D0 / sub_2813F0 / sub_2819B0.
void sub_2819D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002819d0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    mov_s(f20, f12);
    s0 = a2;
    a0 = 266;
    a1 = 36;
    jal(ctx, 0x281A00u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 5072);  // &sub_2813D0
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 5104);  // &sub_2813F0
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 6576);  // &sub_2819B0
    sw(v1, v0, kPktOnEnd);
    lw(a0, v0, kPktData);
    sw(s2, a0, kPdUnit);
    swc1(f20, a0, kMvSpeed);
    sw(s0, a0, kMvFrames);
    if (s1 == 0) {
        // 0x00281a64
        charge(ctx, 9);
        v1 = 0x950000;
        lwc1(f2, v1, kZeroVecLo);  // 0x957180
        v1 = 0x950000;
        lwc1(f1, v1, kZeroVecLo + 4);  // 0x957184
        v1 = 0x950000;
        lwc1(f0, v1, kZeroVecLo + 8);  // 0x957188
        swc1(f2, a0, kMvTarget);
        swc1(f1, a0, kMvTarget + 4);
        swc1(f0, a0, kMvTarget + 8);
    } else {
        // 0x00281a44
        charge(ctx, 8);
        lwc1(f2, s1, 0);
        lwc1(f1, s1, 4);
        lwc1(f0, s1, 8);
        swc1(f2, a0, kMvTarget);
        swc1(f1, a0, kMvTarget + 4);
        swc1(f0, a0, kMvTarget + 8);
    }
    // 0x00281a88 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00281AB0 sub_281AB0 -- 24 bytes; leaf frame (no stack)
// [btlPktLook_OnQueue](data): the look packet (sub_281E80) holds its unit (data +36): busy counter (+160) ++.
void sub_281AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00281ab0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit36);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00281E60 sub_281E60 -- 24 bytes; leaf frame (no stack)
// [btlPktLook_OnEnd](data): busy counter of the unit at data +36 --.
void sub_281E60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00281e60
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit36);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00281E80 sub_281E80 -- 160 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [btlPacketCreateLook](a0 = unit, a1 = the unit looked at, a2 = frames, $f12 / $f13): a kind-267 packet (40 data bytes:
// a0 at +0, frames +16, f12 at +28, f13 at +32, a1 at +36); callbacks sub_281AB0 / sub_281AD0 / sub_281E60.
void sub_281E80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00281e80
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    mov_s(f21, f12);
    mov_s(f20, f13);
    s0 = a2;
    a0 = 267;
    a1 = 40;
    jal(ctx, 0x281EB8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 6832);  // &sub_281AB0
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 6864);  // &sub_281AD0
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 7776);  // &sub_281E60
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s2, v1, kPdUnit);
    swc1(f21, v1, kLkF28);
    swc1(f20, v1, kLkF32);
    sw(s0, v1, kLkFrames);
    sw(s1, v1, kPdUnit36);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00282130 sub_282130 -- 92 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreate268](a0, a1): a kind-268 packet (36 data bytes: a0 at +24, u16 a1 at +28, 0 at +30) whose update is
// sub_281F20 (no hold / release callbacks).
void sub_282130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00282130
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 268;
    a1 = 36;
    jal(ctx, 0x282150u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 7968);  // &sub_281F20
    sw(v1, v0, kPktUpdate);
    lw(v1, v0, kPktData);
    sw(s1, v1, kP268Arg);
    sh(s0, v1, kP268Value);
    sh(zero, v1, kP268Counter);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00282190 sub_282190 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_2822B0 (turn) packet holds its unit (data +0): busy counter (+160) ++.
void sub_282190(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00282190
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00282290 sub_282290 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_2822B0 (turn) packet releases its unit (data +0): busy counter (+160) --.
void sub_282290(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00282290
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x002822B0 sub_2822B0 -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreateTurn](unit, vec3* or 0 (= the zero vector), a2 = frames): a unit turn packet (kind 269, 24 data bytes);
// callbacks sub_282190 / sub_2821B0 / sub_282290.
void sub_2822B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002822b0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 269;
    a1 = 24;
    jal(ctx, 0x2822D8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 8592);  // &sub_282190
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 8624);  // &sub_2821B0
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 8848);  // &sub_282290
    sw(v1, v0, kPktOnEnd);
    lw(a0, v0, kPktData);
    sw(s2, a0, kPdUnit);
    sw(s0, a0, kTnFrames);
    if (s1 == 0) {
        // 0x00282338
        charge(ctx, 9);
        v1 = 0x950000;
        lwc1(f2, v1, kZeroVecLo);  // 0x957180
        v1 = 0x950000;
        lwc1(f1, v1, kZeroVecLo + 4);  // 0x957184
        v1 = 0x950000;
        lwc1(f0, v1, kZeroVecLo + 8);  // 0x957188
        swc1(f2, a0, kTnDir);
        swc1(f1, a0, kTnDir + 4);
        swc1(f0, a0, kTnDir + 8);
    } else {
        // 0x00282318
        charge(ctx, 8);
        lwc1(f2, s1, 0);
        lwc1(f1, s1, 4);
        lwc1(f0, s1, 8);
        swc1(f2, a0, kTnDir);
        swc1(f1, a0, kTnDir + 4);
        swc1(f0, a0, kTnDir + 8);
    }
    // 0x0028235c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00282380 sub_282380 -- 40 bytes; leaf frame (no stack)
// [btlPktPair_OnQueue](data): the two-unit packet (sub_282650) holds both units (data +0, +4): their busy counters ++.
void sub_282380(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00282380
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a1, a0, kPdUnit);
    lhu(v1, a1, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a1, kUnBusy);
    lw(a0, a0, kPdUnit2);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00282620 sub_282620 -- 40 bytes; leaf frame (no stack)
// [btlPktPair_OnEnd](data): both units' busy counters --.
void sub_282620(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00282620
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a1, a0, kPdUnit);
    lhu(v1, a1, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a1, kUnBusy);
    lw(a0, a0, kPdUnit2);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00282650 sub_282650 -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreateFace](a0 = unit, a1 = unit, a2): a kind-270 packet (16 data bytes: a0, a1, a2) holding both units;
// callbacks sub_282380 / sub_2823B0 / sub_282620.
void sub_282650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00282650
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 270;
    a1 = 16;
    jal(ctx, 0x282678u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 9088);  // &sub_282380
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 9136);  // &sub_2823B0
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 9760);  // &sub_282620
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s2, v1, kPdUnit);
    sw(s1, v1, kPdUnit2);
    sw(s0, v1, kFcArg);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00282C30 sub_282C30 -- 40 bytes; leaf frame (no stack)
// [btlUnitGetMotion](unit): the current motion (s16 +2510) when the unit has a model (dirty bit 1), else 0.
void sub_282C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00282c30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kUnDirty);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00282c4c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00282c40
        charge(ctx, 3);
        lh(v0, a0, kUnMotion);
    }
    // 0x00282c50 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00282C60 sub_282C60 -- 104 bytes; leaf frame (no stack)
// [btlUnitIsIdle](unit): a party or enemy unit (side 0 / 1) whose current motion (0 without a model) equals its idle
// motion (s16 +2528); 0 otherwise.
void sub_282C60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00282c60
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v1, a0, kUnSide);
    v0 = 1;
    if (v1 != v0) {
        // 0x00282c70
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00282c80;
        }
        // 0x00282c78
        charge(ctx, 2);
        // 0x00282cbc
        charge(ctx, 1);
        v0 = 0;
        // 0x00282cc0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00282c80:
    charge(ctx, 4);
    lw(v0, a0, kUnDirty);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00282c9c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00282c90
        charge(ctx, 3);
        lh(v0, a0, kUnMotion);
    }
    // 0x00282ca0
    charge(ctx, 7);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    lh(v0, a0, kUnIdleMotion);
    v0 = v0 ^ v1;
    v0 = sltiu(v0, 1);
    // 0x00282cc0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00282CD0 sub_282CD0 -- 100 bytes; leaf frame (no stack)
// [btlUnitIsMotion1](unit): a party or enemy unit whose current motion is 1.
void sub_282CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00282cd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v1, a0, kUnSide);
    v0 = 1;
    if (v1 != v0) {
        // 0x00282ce0
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00282cf0;
        }
        // 0x00282ce8
        charge(ctx, 2);
        // 0x00282d28
        charge(ctx, 1);
        v0 = 0;
        // 0x00282d2c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00282cf0:
    charge(ctx, 4);
    lw(v0, a0, kUnDirty);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00282d0c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00282d00
        charge(ctx, 3);
        lh(v0, a0, kUnMotion);
    }
    // 0x00282d10
    charge(ctx, 6);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
    // 0x00282d2c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00283510 sub_283510 -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetMotionId](unit, a1 = motion slot): enemies (side 1) ask sub_2FB860 first (a result other than -1 wins);
// party, enemy and persona units (sides 0..2) read the byte of the 26-byte row of their side in 0x693290; other sides 0.
void sub_283510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00283510
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lbu(v1, a0, kUnSide);
    v0 = 2;
    if (v1 != v0) {
        // 0x00283538
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00283578;
        }
        // 0x00283540
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00283554
            charge(ctx, 7);
            jal(ctx, 0x283554u, gen::fn_sub_2FB860_002fb860);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v1 = si(-1);
            if (v0 == v1) {
                goto L_00283578;
            }
            // 0x00283570
            charge(ctx, 2);
        } else {
            // 0x0028354c
            charge(ctx, 2);
            // 0x002835b8
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x002835bc (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_00283578:
    charge(ctx, 16);
    lbu(v1, s1, kUnSide);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 1);
    v0 = 0x690000;
    v0 = addiu(v0, 12944);  // &0x693290
    v1 = addu(v0, v1);
    v0 = s0 & 0xFFFF;
    v0 = addu(v0, v1);
    lbu(v0, v0, 0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    // 0x002835bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00283BA0 sub_283BA0 -- 88 bytes; frame 0x10: ra sp+0x0
// [btlUnitGetMotionFrame](unit): with a model, sub_318990(model, 0)'s float result truncated to an int and sign-extended
// from 16 bits; 0 without one.
void sub_283BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00283ba0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, kUnDirty);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00283be4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00283bb8
        charge(ctx, 11);
        lw(a0, a0, kUnModel);
        a1 = 0;
        jal(ctx, 0x283BC0u, gen::fn_sub_318990_00318990);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
    }
    // 0x00283be8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00283C00 sub_283C00 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlUnitSetMotionFrame](unit, a1): with a model, sub_318770(model, 0) with $f12 = (float)a1 (cvt.s.w); $v0 is left as
// the model test leaves it.
void sub_283C00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00283c00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, kUnDirty);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x00283c18
        charge(ctx, 7);
        mtc1(a1, f0);
        cvt_s_w(f12, f0);
        lw(a0, a0, kUnModel);
        a1 = 0;
        jal(ctx, 0x283C2Cu, gen::fn_sub_318770_00318770);
    }
    // 0x00283c34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00283C50 sub_283C50 -- 28 bytes; leaf frame (no stack)
// [btlUnitSetMotionSpeed](unit, $f12): the motion speed (+2516) = f12 when the unit has a model.
void sub_283C50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x00283c50
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kUnDirty);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x00283c60
        charge(ctx, 1);
        swc1(f12, a0, kUnMotionSpeed);
    }
    // 0x00283c64 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00283FE0 sub_283FE0 -- 96 bytes; leaf frame (no stack)
// [btlUnitGetWeaponFxRow](unit, a1): for a non-enemy unit with id 4, the address of the 8-byte row a1 - 4 of 0x6932E0;
// else 0.
void sub_283FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00283fe0
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v1, a0, kUnSide);
    v0 = 1;
    if (v1 != v0) {
        // 0x00283ffc
        charge(ctx, 4);
        lhu(v1, a0, kUnId);
        v0 = 4;
        if (v1 == v0) {
            // 0x00284014
            charge(ctx, 8);
            v0 = a1 & 0xFFFF;
            v0 = addiu(v0, -4);
            v1 = sll(v0, 3);
            v0 = 0x690000;
            v0 = addiu(v0, 13024);  // &0x6932E0
            v0 = addu(v0, v1);
        } else {
            // 0x0028400c
            charge(ctx, 2);
            // 0x00284034
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x00283ff0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00284038 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00284170 sub_284170 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_284200 (motion) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284170(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284170
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00284190 sub_284190 -- 80 bytes; frame 0x10: ra sp+0x0
// [btlPktMotion_Update](data): plays the motion packet's motion once (sub_282D40(unit, motion, mode, flags) when motion
// <= 25 as signed s16; -5 was stored as -1); returns 1.
void sub_284190(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00284190
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    lh(a1, a0, kMoMotion);
    if (i64(a1) >= 0) {
        // 0x002841a8
        charge(ctx, 3);
        at = slti(a1, 26);
        if (at != 0) {
            // 0x002841b4
            charge(ctx, 6);
            lw(a0, v0, kPdUnit);
            lhu(a2, v0, kMoMode);
            lwc1(f12, v0, kMoSpeed);
            lhu(a3, v0, kMoFlags);
            jal(ctx, 0x2841C4u, gen::fn_sub_282D40_00282d40);
        }
    }
    // 0x002841cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002841E0 sub_2841E0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_284200 (motion) packet releases its unit (data +0): busy counter (+160) --.
void sub_2841E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002841e0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00284200 sub_284200 -- 296 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlPacketCreateMotion](unit, a1 = motion, a2 = mode, a3 = flags, $f12 = speed): -4 -> sub_284B70(unit, 6), -3 ->
// sub_284900(unit, 6), -2 -> sub_284600(unit, f12); else a kind-256 packet (16 data bytes: unit, s16 motion (-5 stored
// as -1), mode, speed, flags) with callbacks sub_284170 / sub_284190 / sub_2841E0. 43 callers.
void sub_284200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x00284200
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a2;
    mov_s(f20, f12);
    s1 = a3;
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-4);
    if (s0 == v0) {
        // 0x0028428c
        charge(ctx, 5);
        a1 = 6;
        jal(ctx, 0x284290u, gen::fn_sub_284B70_00284b70);
    } else {
        // 0x00284240
        charge(ctx, 3);
        v0 = si(-3);
        if (s0 == v0) {
            // 0x00284278
            charge(ctx, 5);
            a1 = 6;
            jal(ctx, 0x28427Cu, gen::fn_sub_284900_00284900);
        } else {
            // 0x0028424c
            charge(ctx, 3);
            v0 = si(-2);
            if (s0 == v0) {
                // 0x00284260
                charge(ctx, 6);
                v0 = 0x42000000;
                mtc1(v0, f12);
                jal(ctx, 0x284268u, gen::fn_sub_284600_00284600);
            } else {
                // 0x00284258
                charge(ctx, 2);
                // 0x002842a0
                charge(ctx, 18);
                a0 = 256;
                a1 = 16;
                jal(ctx, 0x2842A8u, gen::fn_sub_27EC10_0027ec10);
                v1 = 0x280000;
                v1 = addiu(v1, 16752);  // &sub_284170
                sw(v1, v0, kPktOnQueue);
                v1 = 0x280000;
                v1 = addiu(v1, 16784);  // &sub_284190
                sw(v1, v0, kPktUpdate);
                v1 = 0x280000;
                v1 = addiu(v1, 16864);  // &sub_2841E0
                sw(v1, v0, kPktOnEnd);
                lw(a0, v0, kPktData);
                sw(s3, a0, kPdUnit);
                v1 = si(-5);
                if (s0 == v1) {
                    // 0x002842f0
                    charge(ctx, 1);
                    s0 = si(-1);
                } else {
                    // 0x002842e8
                    charge(ctx, 2);
                }
                // 0x002842f4
                charge(ctx, 4);
                sh(s0, a0, kMoMotion);
                sh(s2, a0, kMoMode);
                swc1(f20, a0, kMoSpeed);
                sh(s1, a0, kMoFlags);
            }
        }
    }
    // 0x00284304 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00284330 sub_284330 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_2843E0 (idle motion) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284330(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284330
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00284350 sub_284350 -- 108 bytes; frame 0x10: ra sp+0x0
// [btlPktIdle_Update](data): unless the unit already plays its idle motion, sub_282D40 (the motion call, with $a1.. as
// the caller left them); returns 1.
void sub_284350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00284350
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = a0;
    lw(a0, a0, kPdUnit);
    lw(v0, a0, kUnDirty);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0028437c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00284370
        charge(ctx, 3);
        lh(v0, a0, kUnMotion);
    }
    // 0x00284380
    charge(ctx, 5);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    lh(a1, a0, kUnIdleMotion);
    if (a1 != v0) {
        // 0x00284394
        charge(ctx, 5);
        lb(a3, a0, kUnIdleFlags);
        lhu(a2, v1, 4);
        lwc1(f12, a0, kUnIdleSpeed);
        jal(ctx, 0x2843A0u, gen::fn_sub_282D40_00282d40);
    }
    // 0x002843a8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002843C0 sub_2843C0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_2843E0 (idle motion) packet releases its unit (data +0): busy counter (+160) --.
void sub_2843C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002843c0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x002843E0 sub_2843E0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreateIdle](unit, a1): a kind-260 packet (8 data bytes: unit, u16 a1); callbacks sub_284330 / sub_284350 /
// sub_2843C0.
void sub_2843E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002843e0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 260;
    a1 = 8;
    jal(ctx, 0x284400u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 17200);  // &sub_284330
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 17232);  // &sub_284350
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 17344);  // &sub_2843C0
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s1, v1, kPdUnit);
    sh(s0, v1, kIdMode);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00284450 sub_284450 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_284600 (motion speed) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284450(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284450
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x002845E0 sub_2845E0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_284600 (motion speed) packet releases its unit (data +0): busy counter (+160) --.
void sub_2845E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002845e0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00284600 sub_284600 -- 112 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [btlPacketCreateMotionSpeed](unit, $f12): a kind-263 packet (12 data bytes: unit, f12); callbacks sub_284450 /
// sub_284470 / sub_2845E0.
void sub_284600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x00284600
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    a0 = 263;
    a1 = 12;
    jal(ctx, 0x284620u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 17488);  // &sub_284450
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 17520);  // &sub_284470
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 17888);  // &sub_2845E0
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s0, v1, kPdUnit);
    swc1(f20, v1, kSpSpeed);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00284670 sub_284670 -- 24 bytes; leaf frame (no stack)
// [btlPktFade_OnQueue](data): the kind-264 packet (sub_284900) holds its unit (data +12): busy counter (+160) ++.
void sub_284670(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284670
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit12);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x002848E0 sub_2848E0 -- 24 bytes; leaf frame (no stack)
// [btlPktFade_OnEnd](data): busy counter of the unit at data +12 --.
void sub_2848E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002848e0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit12);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00284900 sub_284900 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPacketCreate264](unit, a1): a kind-264 packet (24 data bytes: unit at +12, u16 a1 at +16, 0 at +18); callbacks
// sub_284670 / sub_284690 / sub_2848E0.
void sub_284900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284900
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 264;
    a1 = 24;
    jal(ctx, 0x284920u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 18032);  // &sub_284670
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 18064);  // &sub_284690
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 18656);  // &sub_2848E0
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s1, v1, kPdUnit12);
    sh(s0, v1, kP264Arg);
    sh(zero, v1, kP264Counter);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00284980 sub_284980 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_284B70 (kind 265) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284980(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284980
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00284B50 sub_284B50 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_284B70 (kind 265) packet releases its unit (data +0): busy counter (+160) --.
void sub_284B50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284b50
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00284B70 sub_284B70 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketCreate265](unit): a kind-265 packet (16 data bytes: the unit as a 64-bit sd at +0); callbacks sub_284980 /
// sub_2849A0 / sub_284B50.
void sub_284B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284b70
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 265;
    a1 = 16;
    jal(ctx, 0x284B88u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 18816);  // &sub_284980
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 18848);  // &sub_2849A0
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 19280);  // &sub_284B50
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s0, v1, kPdUnit);
    sw(zero, v1, kPdUnit + 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00284BE0 sub_284BE0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_284C90 (kind 261) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284be0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00284C70 sub_284C70 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnEnd](data): the sub_284C90 (kind 261) packet releases its unit (data +0): busy counter (+160) --.
void sub_284C70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284c70
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, kUnBusy);
}

// 0x00284C90 sub_284C90 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlPacketCreate261](unit): a kind-261 packet (4 data bytes: the unit); callbacks sub_284BE0 / sub_284C00 / sub_284C70.
void sub_284C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284c90
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 261;
    a1 = 4;
    jal(ctx, 0x284CA8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 19424);  // &sub_284BE0
    sw(v1, v0, kPktOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 19456);  // &sub_284C00
    sw(v1, v0, kPktUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 19568);  // &sub_284C70
    sw(v1, v0, kPktOnEnd);
    lw(v1, v0, kPktData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00284CF0 sub_284CF0 -- 24 bytes; leaf frame (no stack)
// [btlPktUnit_OnQueue](data): the sub_284D80 (kind 262) packet holds its unit (data +0): busy counter (+160) ++.
void sub_284CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00284cf0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kPdUnit);
    lhu(v1, a0, kUnBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, kUnBusy);
}

// 0x00287400 sub_287400 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitDrawAll] (btlUpdateDraw3DTask): sub_287EA0(unit) for every unit with a model (dirty bit 1) of the four side
// lists (gBtl+340 + 8s heads, +2608 next).
void sub_287400(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00287400
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x00287460
        charge(ctx, 3);
        v1 = sltiu(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0028741c
        charge(ctx, 6);
        a0 = sll(s0, 3);
        lw(v1, gp, kGpBtl);  // gBtl
        v1 = addu(v1, a0);
        lw(s1, v1, kBtlUnitHead);
        for (;;) {
            // 0x00287454
            charge(ctx, 2);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00287434
            charge(ctx, 4);
            lw(v1, s1, kUnDirty);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x00287444
                charge(ctx, 3);
                a0 = s1;
                jal(ctx, 0x287448u, gen::fn_sub_287EA0_00287ea0);
            }
            // 0x00287450
            charge(ctx, 1);
            lw(s1, s1, kUnNext);
        }
        // 0x0028745c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0028746c
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00287490 sub_287490 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitShowModel](unit): flags &= ~0x1000 (shown), sub_287CF0 (the model state); with a model id (+2546) sub_1A0DC0
// and flags &= ~2, else flags |= 2 (no model).
void sub_287490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00287490
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, kUnFlags);
    v0 = si(-4097);
    v0 = v1 & v0;
    sw(v0, a0, kUnFlags);
    a1 = 5;
    jal(ctx, 0x2874B4u, gen::fn_sub_287CF0_00287cf0);
    lhu(a0, s0, kUnModelId);
    if (a0 == 0) {
        // 0x002874ec
        charge(ctx, 3);
        lw(v1, s0, kUnFlags);
        v1 = v1 | 0x2;
        sw(v1, s0, kUnFlags);
    } else {
        // 0x002874c8
        charge(ctx, 9);
        a1 = 1;
        jal(ctx, 0x2874CCu, gen::fn_sub_1A0DC0_001a0dc0);
        lw(a0, s0, kUnFlags);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, s0, kUnFlags);
    }
    // 0x002874f8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00287510 sub_287510 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitHideModel](unit): flags |= 0x1000 (hidden), sub_287CF0, sub_1A0DC0 with a model id; flags &= ~2.
void sub_287510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00287510
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, kUnFlags);
    v0 = v0 | 0x1000;
    sw(v0, a0, kUnFlags);
    a1 = 5;
    jal(ctx, 0x287530u, gen::fn_sub_287CF0_00287cf0);
    lhu(a0, s0, kUnModelId);
    if (a0 != 0) {
        // 0x00287544
        charge(ctx, 3);
        a1 = 0;
        jal(ctx, 0x287548u, gen::fn_sub_1A0DC0_001a0dc0);
    }
    // 0x00287550 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, s0, kUnFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, kUnFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00287580 sub_287580 -- 24 bytes; leaf frame (no stack)
// [btlUnitIsShown](unit): flags bit 12 (0x1000) clear.
void sub_287580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00287580
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, kUnFlags);
    v0 = v0 & 0x1000;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
}

// 0x002875A0 btlUnitCreate -- 404 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlUnitCreate(side): RwMalloc(2616), zeroed: side (+162), serial (+168) from the counter at gp-26580 (1..0xFFFFFFE),
// the default transform (sub_27F530), height 150 (+140), size 50 (+144), centre offset (0, 75, 0), move flags 0, +204 =
// 27.0, half width 0.5 * (8 for the party, 14 otherwise) (+1268), motion speed 1 (+2516), formation slot -1 (+2544), the
// two BED pools (+2552 = sub_2BBC00(unit), +2556 = sub_2BB7D0()); appended at the tail of the side's list (gBtl+336 + 8s
// tail, +340 + 8s head; +2608 next, +2612 prev). Returns the unit.
void btlUnitCreate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002875a0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 2616;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x2875C4u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 2616;
    jal(ctx, 0x2875DCu, gen::fn_memset_00521408);
    sb(s1, s0, kUnSide);
    lw(v1, gp, kGpUnitSerial);  // btlUnit serial counter
    v0 = 0xFFF0000;
    v0 = v0 | 0xFFFF;
    v0 = sltu(v1, v0);
    if (v0 == 0) {
        // 0x00287600
        charge(ctx, 2);
        v0 = 1;
        sw(v0, gp, kGpUnitSerial);  // btlUnit serial counter
    }
    // 0x00287608
    charge(ctx, 24);
    lw(v1, gp, kGpUnitSerial);  // btlUnit serial counter
    v0 = addiu(v1, 1);
    sw(v0, gp, kGpUnitSerial);  // btlUnit serial counter
    sw(v1, s0, kUnSerial);
    a0 = s0;
    jal(ctx, 0x28761Cu, gen::fn_sub_27F530_0027f530);
    v0 = 0x43160000;
    sw(v0, s0, kUnHeight);
    v0 = 0x42480000;
    sw(v0, s0, kUnSize);
    sw(zero, s0, kUnCentre);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    lwc1(f0, s0, kUnHeight);
    mul_s(f0, f1, f0);
    swc1(f0, s0, kUnCentre + 4);
    sw(zero, s0, kUnCentre + 8);
    sh(zero, s0, kUnMoveFlags);
    v0 = 0x41D80000;
    sw(v0, s0, kUn204);
    lbu(v0, s0, kUnSide);
    if (v0 != 0) {
        // 0x00287678
        charge(ctx, 2);
        v0 = 0x41600000;
        mtc1(v0, f1);
    } else {
        // 0x00287668
        charge(ctx, 4);
        v0 = 0x41000000;
        mtc1(v0, f1);
    }
    // 0x00287680
    charge(ctx, 25);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f0, f0, f1);
    swc1(f0, s0, kUnHalfWidth);
    v0 = 0x3F800000;
    sw(v0, s0, kUnMotionSpeed);
    v0 = si(-1);
    sb(v0, s0, kUnFormSlot);
    a0 = s0;
    jal(ctx, 0x2876A8u, gen::fn_sub_2BBC00_002bbc00);
    sw(v0, s0, kUnBedA);
    jal(ctx, 0x2876B4u, gen::fn_sub_2BB7D0_002bb7d0);
    sw(v0, s0, kUnBedB);
    sw(zero, s0, kUnNext);
    v0 = s1 & 0xFF;
    a0 = sll(v0, 3);
    lw(v1, gp, kGpBtl);  // gBtl
    v0 = addiu(v1, 336);
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    if (v0 == 0) {
        // 0x00287700
        charge(ctx, 3);
        v0 = addu(a0, v1);
        sw(s0, v0, kBtlUnitHead);
        sw(zero, s0, kUnPrev);
    } else {
        // 0x002876e4
        charge(ctx, 7);
        sw(s0, v0, kUnNext);  // the old tail's next
        lw(v0, gp, kGpBtl);  // gBtl
        v0 = addu(a0, v0);
        lw(v0, v0, kBtlUnitTail);
        sw(v0, s0, kUnPrev);
    }
    // 0x0028770c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v0, gp, kGpBtl);  // gBtl
    v0 = addu(a0, v0);
    sw(s0, v0, kBtlUnitTail);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002889C0 sub_2889C0 -- 984 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitSetId](unit, a1 = id): id (+164) = a1 and, by side, the model record that gives the scale (u16 +20 / 100, or
// +24 for a persona) and the centre / size words: persona (2) MODEL.TBL section 3 (88-byte records, record +2, motion
// table +26, 6 motions); enemy (1) the DatUnit's id too, MODEL.TBL section 2 (232-byte records, +42, 19 motions); party
// (0) the DatUnit's id, datUnitInit, then the hero (id 1) the section-0 record of his weapon type (datCalcGetHeldWeaponType;
// 296 bytes, +36, 26 motions) and the others section 1 (266 bytes, +36, 23 motions); any other side reads the words
// from the unit itself (the register still holds it). Centre = the record's s16 x / y / z, height / size its u16 +6 / +8 (as floats); then sub_2BCDE0(unit,
// unit + 2564, id).
void sub_2889C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002889c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a2 = s0 & 0xFFFF;
    sh(s0, a0, kUnId);
    lbu(v1, a0, kUnSide);
    v0 = 3;
    if (v1 != v0) {
        // 0x002889f0
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x00288c20
            charge(ctx, 10);
            v0 = sll(s0, 2);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            a0 = sll(v0, 3);
            lw(v0, gp, kGpModelPersona);  // MODEL.TBL section 3
            v0 = addu(a0, v0);
            lhu(v0, v0, 24);
            if (i64(v0) < 0) {
                // 0x00288c5c
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x00288c48
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x00288c78
            charge(ctx, 15);
            v0 = 0x42C80000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            swc1(f0, s1, kUnScale);
            lw(v0, s1, kUnDirty);
            v0 = v0 | 0x4;
            sw(v0, s1, kUnDirty);
            lw(v0, gp, kGpModelPersona);  // MODEL.TBL section 3
            v0 = addu(v0, a0);
            a0 = addiu(v0, 2);
            v0 = addiu(v0, 26);
            sw(v0, s1, kUnModelRec);
            v0 = 6;
            sh(v0, s1, kUnMotionCount);
        } else {
            // 0x002889fc
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00288b80
                charge(ctx, 12);
                lw(v0, s1, kUnDat);
                sh(a2, v0, kDatId);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                a0 = sll(v0, 3);
                lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2
                v0 = addu(a0, v0);
                lhu(v0, v0, 20);
                if (i64(v0) < 0) {
                    // 0x00288bc4
                    charge(ctx, 7);
                    v1 = srl(v0, 1);
                    v0 = v0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x00288bb0
                    charge(ctx, 5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x00288be0
                charge(ctx, 16);
                v0 = 0x42C80000;
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                swc1(f0, s1, kUnScale);
                lw(v0, s1, kUnDirty);
                v0 = v0 | 0x4;
                sw(v0, s1, kUnDirty);
                lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2
                a0 = addu(v0, a0);
                v0 = addiu(a0, 42);
                sw(v0, s1, kUnModelRec);
                v0 = 19;
                sh(v0, s1, kUnMotionCount);
            } else {
                // 0x00288a08
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00288a18
                    charge(ctx, 10);
                    lw(v0, s1, kUnDat);
                    sh(a2, v0, kDatId);
                    lw(a0, s1, kUnDat);
                    a1 = 0;
                    jal(ctx, 0x288A28u, gen::fn_datUnitInit_002ff890);
                    lhu(v1, s1, kUnId);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x00288ae8
                        charge(ctx, 10);
                        v0 = sll(s0, 5);
                        v0 = addu(v0, s0);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s0);
                        a0 = sll(v0, 1);
                        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
                        v0 = addu(a0, v0);
                        lhu(v0, v0, 20);
                        if (i64(v0) < 0) {
                            // 0x00288b24
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x00288b10
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x00288b40
                        charge(ctx, 16);
                        v0 = 0x42C80000;
                        mtc1(v0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s1, kUnScale);
                        lw(v0, s1, kUnDirty);
                        v0 = v0 | 0x4;
                        sw(v0, s1, kUnDirty);
                        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1
                        a0 = addu(v0, a0);
                        v0 = addiu(a0, 36);
                        sw(v0, s1, kUnModelRec);
                        v0 = 23;
                        sh(v0, s1, kUnMotionCount);
                    } else {
                        // 0x00288a40
                        charge(ctx, 14);
                        lw(a0, s1, kUnDat);
                        jal(ctx, 0x288A44u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                        v1 = v0 & 0xFF;
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        a0 = sll(v0, 3);
                        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0
                        v0 = addu(a0, v0);
                        lhu(v0, v0, 20);
                        if (i64(v0) < 0) {
                            // 0x00288a8c
                            charge(ctx, 7);
                            v1 = srl(v0, 1);
                            v0 = v0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x00288a78
                            charge(ctx, 5);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x00288aa8
                        charge(ctx, 16);
                        v0 = 0x42C80000;
                        mtc1(v0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s1, kUnScale);
                        lw(v0, s1, kUnDirty);
                        v0 = v0 | 0x4;
                        sw(v0, s1, kUnDirty);
                        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0
                        a0 = addu(v0, a0);
                        v0 = addiu(a0, 36);
                        sw(v0, s1, kUnModelRec);
                        v0 = 26;
                        sh(v0, s1, kUnMotionCount);
                    }
                } else {
                    // 0x00288a10
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00288cb4
    charge(ctx, 18);
    lh(v0, a0, kUnShowFlags);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s1, kUnCentre);
    lh(v0, a0, 2);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s1, kUnCentre + 4);
    lh(v0, a0, kUnPos);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, s1, kUnCentre + 8);
    lhu(v0, a0, 6);
    if (i64(v0) < 0) {
        // 0x00288d10
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00288cfc
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00288d2c
    charge(ctx, 4);
    swc1(f0, s1, kUnHeight);
    lhu(v0, a0, kUnPos + 4);
    if (i64(v0) < 0) {
        // 0x00288d50
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00288d3c
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00288d6c
    charge(ctx, 11);
    swc1(f0, s1, kUnSize);
    a0 = s1;
    a1 = addiu(s1, 2564);
    jal(ctx, 0x288D78u, gen::fn_sub_2BCDE0_002bcde0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00288F80 sub_288F80 -- 92 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitSetPersona](unit, a1 = persona id): creates the unit's persona sub-unit (btlUnitCreate(2), +2560) when it has
// none, then btlUnitSetId(persona unit, a1).
void sub_288F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00288f80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, a0, kUnPersona);
    if (v0 == 0) {
        // 0x00288fa4
        charge(ctx, 4);
        a0 = 2;
        jal(ctx, 0x288FA8u, gen::fn_btlUnitCreate_002875a0);
        sw(v0, s1, kUnPersona);
    }
    // 0x00288fb4
    charge(ctx, 10);
    lw(a0, s1, kUnPersona);
    a1 = s0;
    jal(ctx, 0x288FBCu, gen::fn_sub_2889C0_002889c0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00289650 sub_289650 -- 524 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCreateCombatant](a0 = side, a1 = id, a2 = DatUnit or 0): an enemy (side 1) or a party member (side 0): a unit and a
// btlAction bound to it (sub_299E70), added to the turn order (sub_29A2C0), activated (sub_299E30) and set to state 1
// (StandBy); party: the hero (id 1) is the player action (gBtl+328, return state 5 = Command), the persona
// (datPersonaGetByPcId(id) +2) as sub-unit, action flags2 |= 0x10; with a DatUnit: unit +2604, btlUnitSetId, flag 1 when
// it is dead. Then unit flags |= 8, action flags2 |= 8, party units flags |= 0x20 | 0x40 | 0x80 | 0x200, and sub_2F9C10
// (the boss hooks). Returns the action.
void sub_289650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00289650
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = 0;
    s0 = a0 & 0xFFFF;
    a0 = 1;
    if (s0 == a0) {
        // 0x0028973c
        charge(ctx, 20);
        jal(ctx, 0x28973Cu, gen::fn_btlUnitCreate_002875a0);
        s1 = v0;
        jal(ctx, 0x289748u, gen::fn_btlActionCreate_00299e90);
        s2 = v0;
        a0 = s2;
        a1 = s1;
        jal(ctx, 0x28975Cu, gen::fn_sub_299E70_00299e70);
        a0 = s2;
        jal(ctx, 0x289768u, gen::fn_sub_29A2C0_0029a2c0);
        a0 = s2;
        jal(ctx, 0x289774u, gen::fn_sub_299E30_00299e30);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x289784u, gen::fn_btlActionSetState_00299d60);
    } else {
        // 0x00289688
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x00289698
            charge(ctx, 25);
            a0 = 0;
            jal(ctx, 0x28969Cu, gen::fn_btlUnitCreate_002875a0);
            s1 = v0;
            jal(ctx, 0x2896A8u, gen::fn_btlActionCreate_00299e90);
            s2 = v0;
            a0 = s2;
            a1 = s1;
            jal(ctx, 0x2896BCu, gen::fn_sub_299E70_00299e70);
            a0 = s2;
            jal(ctx, 0x2896C8u, gen::fn_sub_29A2C0_0029a2c0);
            a0 = s2;
            jal(ctx, 0x2896D4u, gen::fn_sub_299E30_00299e30);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x2896E4u, gen::fn_btlActionSetState_00299d60);
            v1 = s4 & 0xFFFF;
            v0 = 1;
            if (v1 == v0) {
                // 0x002896fc
                charge(ctx, 4);
                v0 = 5;
                sh(v0, s2, kActReturn);
                lw(v0, gp, kGpBtl);  // gBtl
                sw(s2, v0, kBtlPlayerAction);
            }
            // 0x0028970c
            charge(ctx, 12);
            a0 = s4;
            jal(ctx, 0x289710u, gen::fn_datPersonaGetByPcId_00174800);
            lhu(a1, v0, 2);  // the persona's id
            a0 = s1;
            jal(ctx, 0x289720u, gen::fn_sub_288F80_00288f80);
            lhu(v0, s2, kActFlags2);
            v0 = v0 | 0x10;
            sh(v0, s2, kActFlags2);
        } else {
            // 0x00289690
            charge(ctx, 2);
        }
    }
    // 0x0028978c
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x00289794
        charge(ctx, 11);
        sw(s3, s1, kUnDat);
        a1 = s4 & 0xFFFF;
        a0 = s1;
        jal(ctx, 0x2897A0u, gen::fn_sub_2889C0_002889c0);
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x2897B0u, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {
            // 0x002897c0
            charge(ctx, 3);
            lw(v0, s1, kUnFlags);
            v0 = v0 | 0x1;
            sw(v0, s1, kUnFlags);
        }
    }
    // 0x002897cc
    charge(ctx, 10);
    lw(v1, s2, kActUnit);
    lw(v0, v1, kUnFlags);
    v0 = v0 | 0x8;
    sw(v0, v1, kUnFlags);
    lhu(v0, s2, kActFlags2);
    v0 = v0 | 0x8;
    sh(v0, s2, kActFlags2);
    v0 = 1;
    if (s0 != v0) {
        // 0x002897f4
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x00289804
            charge(ctx, 9);
            lw(v0, s1, kUnFlags);
            v0 = v0 | 0x20;
            sw(v0, s1, kUnFlags);
            v0 = v0 | 0x40;
            sw(v0, s1, kUnFlags);
            v0 = v0 | 0x80;
            sw(v0, s1, kUnFlags);
            v0 = v0 | 0x200;
            sw(v0, s1, kUnFlags);
        } else {
            // 0x002897fc
            charge(ctx, 2);
        }
    }
    // 0x00289828
    charge(ctx, 13);
    a0 = s2;
    jal(ctx, 0x28982Cu, gen::fn_sub_2F9C10_002f9c10);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00299E90 btlActionCreate -- 284 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// btlActionCreate(): RwMalloc(1200), zeroed; the target record (sub_2D1570(action + 56)); next state 0, return state 8;
// uid (btlGetUID), serial (+8) from the counter at gp-26560; +36 = -1; +54 = datCalcRand(60); linked at the head of
// gBtl+332 (+1188 prev, +1192 next); previous state = state, state 0, frames 0, sBtlActionTbl[0].init (jalr). Returns it.
void btlActionCreate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299e90
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 1200;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, kRwMallocLo);  // 0x960178
    jalr(ctx, 0x299EACu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 1200;
    jal(ctx, 0x299EC4u, gen::fn_memset_00521408);
    a0 = addiu(s0, 56);
    jal(ctx, 0x299ED0u, gen::fn_sub_2D1570_002d1570);
    sh(zero, s0, kActNextState);
    v0 = 8;
    sh(v0, s0, kActReturn);
    jal(ctx, 0x299EE4u, gen::fn_sub_27CB80_0027cb80);
    sd(v0, s0, kActUid);
    lw(v1, gp, kGpActionSerial);  // btlAction serial counter
    v0 = 0xFFF0000;
    v0 = v0 | 0xFFFF;
    v0 = sltu(v1, v0);
    if (v0 == 0) {
        // 0x00299f08
        charge(ctx, 2);
        v0 = 1;
        sw(v0, gp, kGpActionSerial);  // btlAction serial counter
    }
    // 0x00299f10
    charge(ctx, 15);
    lw(v1, gp, kGpActionSerial);  // btlAction serial counter
    v0 = addiu(v1, 1);
    sw(v0, gp, kGpActionSerial);  // btlAction serial counter
    sw(v1, s0, kActSerial);
    v0 = si(-1);
    sw(v0, s0, kAct36);
    a0 = 60;
    jal(ctx, 0x299F2Cu, gen::fn_datCalcRand_002ffbc0);
    sh(v0, s0, kActRand);
    sw(zero, s0, kActLinkPrev);
    lw(v0, gp, kGpBtl);  // gBtl
    lw(v0, v0, kBtlActionList);
    if (v0 == 0) {
        // 0x00299f64
        charge(ctx, 1);
        sw(zero, s0, kActLinkNext);
    } else {
        // 0x00299f4c
        charge(ctx, 6);
        sw(s0, v0, kActLinkPrev);
        lw(v0, gp, kGpBtl);  // gBtl
        lw(v0, v0, kBtlActionList);
        sw(v0, s0, kActLinkNext);
    }
    // 0x00299f68
    charge(ctx, 17);
    lw(v0, gp, kGpBtl);  // gBtl
    sw(s0, v0, kBtlActionList);
    lhu(v0, s0, kActState);
    sh(v0, s0, kActPrevState);
    sh(zero, s0, kActState);
    sw(zero, s0, kActFrames);
    a0 = s0;
    v0 = 0x690000;
    lw(v0, v0, kActionStateTblLo);  // sBtlActionTbl
    jalr(ctx, 0x299F8Cu, v0.u());
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00299FB0 btlActionUpdateAll -- 400 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlActionUpdateAll() (btlUpdateTask): for every btlAction of gBtl+332 (next read first): a pending state (+14) with a
// delay (+18) counts down and, at 0, is entered (prev = state, state = pending, frames 0, sBtlActionTbl[s].init, pending
// = 0); unless frozen (flags2 bit 2): an active action (flags bit 0) runs sBtlActionTbl[state].update and frames += 2; an
// inactive one flagged for removal (flags2 bit 1) is unlinked and freed (RwFree).
void btlActionUpdateAll(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299fb0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl
    lw(s2, v1, kBtlActionList);
    for (;;) {
        // 0x0029a11c
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00299fd4
        charge(ctx, 5);
        lw(s1, s2, kActLinkNext);
        s0 = 1;
        lhu(v1, s2, kActNextState);
        if (v1 != 0) {
            // 0x00299fe8
            charge(ctx, 3);
            lhu(v1, s2, kActDelay);
            if (i64(v1) > 0) {
                // 0x00299ff4
                charge(ctx, 5);
                v1 = addiu(v1, -1);
                sh(v1, s2, kActDelay);
                v1 = v1 & 0xFFFF;
                if (v1 != 0) {
                    // 0x0029a050
                    charge(ctx, 1);
                    s0 = 0;
                } else {
                    // 0x0029a008
                    charge(ctx, 18);
                    lhu(v1, s2, kActNextState);
                    lhu(v0, s2, kActState);
                    sh(v0, s2, kActPrevState);
                    sh(v1, s2, kActState);
                    sw(zero, s2, kActFrames);
                    a0 = s2;
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x690000;
                    v0 = addiu(v0, 13328);  // &sBtlActionTbl
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    jalr(ctx, 0x29A03Cu, v0.u());
                    sh(zero, s2, kActNextState);
                }
            }
        }
        // 0x0029a054
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0029a05c
            charge(ctx, 4);
            lhu(a0, s2, kActFlags2);
            v1 = a0 & 0x4;
            if (v1 == 0) {
                // 0x0029a06c
                charge(ctx, 4);
                lhu(v1, s2, kActFlags);
                v1 = v1 & 0x1;
                if (v1 == 0) {
                    // 0x0029a0bc
                    charge(ctx, 3);
                    v1 = a0 & 0x2;
                    if (v1 != 0) {
                        // 0x0029a0c8
                        charge(ctx, 3);
                        lw(v1, s2, kActLinkNext);
                        if (v1 != 0) {
                            // 0x0029a0d4
                            charge(ctx, 2);
                            lw(v0, s2, kActLinkPrev);
                            sw(v0, v1, kActLinkPrev);
                        }
                        // 0x0029a0dc
                        charge(ctx, 3);
                        lw(v1, s2, kActLinkPrev);
                        if (v1 == 0) {
                            // 0x0029a0f8
                            charge(ctx, 3);
                            lw(v1, s2, kActLinkNext);
                            lw(v0, gp, kGpBtl);  // gBtl
                            sw(v1, v0, kBtlActionList);
                        } else {
                            // 0x0029a0e8
                            charge(ctx, 4);
                            lw(v0, s2, kActLinkNext);
                            sw(v0, v1, kActLinkNext);
                        }
                        // 0x0029a104
                        charge(ctx, 5);
                        a0 = s2;
                        v0 = 0x960000;
                        lw(v0, v0, kRwFreeLo);  // 0x96017C
                        jalr(ctx, 0x29A110u, v0.u());
                    }
                } else {
                    // 0x0029a07c
                    charge(ctx, 16);
                    a0 = s2;
                    lhu(v1, s2, kActState);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x690000;
                    v0 = addiu(v0, 13328);  // &sBtlActionTbl
                    v0 = addu(v0, v1);
                    lw(v0, v0, 4);
                    jalr(ctx, 0x29A0A0u, v0.u());
                    lw(v1, s2, kActFrames);
                    v1 = addiu(v1, 2);
                    sw(v1, s2, kActFrames);
                }
            }
        }
        // 0x0029a118
        charge(ctx, 1);
        s2 = s1;
    }
    // 0x0029a124
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0029A140 sub_29A140 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionFreeAll] (btlDestroy): unlinks and frees (RwFree) every btlAction of gBtl+332.
void sub_29A140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029a140
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl
    lw(a0, v1, kBtlActionList);
    for (;;) {
        // 0x0029a1ac
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a15c
        charge(ctx, 3);
        lw(s0, a0, kActLinkNext);
        if (s0 != 0) {
            // 0x0029a168
            charge(ctx, 2);
            lw(v0, a0, kActLinkPrev);
            sw(v0, s0, kActLinkPrev);
        }
        // 0x0029a170
        charge(ctx, 3);
        lw(v1, a0, kActLinkPrev);
        if (v1 == 0) {
            // 0x0029a18c
            charge(ctx, 3);
            lw(v1, a0, kActLinkNext);
            lw(v0, gp, kGpBtl);  // gBtl
            sw(v1, v0, kBtlActionList);
        } else {
            // 0x0029a17c
            charge(ctx, 4);
            lw(v0, a0, kActLinkNext);
            sw(v0, v1, kActLinkNext);
        }
        // 0x0029a198
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, kRwFreeLo);  // 0x96017C
        jalr(ctx, 0x29A1A0u, v0.u());
        a0 = s0;
    }
    // 0x0029a1b4
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0029A750 sub_29A750 -- 1168 bytes; frame 0x1C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlOrderShuffle]: rebuilds the turn order gBtl+596 (12 slots): sorts it by agility (btlOrderSortByAgility), then
// splits the actions other than the player's (gBtl+328) into enemies (side 1, weight 10 each) and party members (side 0,
// weights from the byte table at gp-26344), draws each group into a stack array by weighted lottery (datCalcRand(total
// weight) walked cumulatively, a drawn entry's weight zeroed), and writes the player action first, then the two drawn
// lists interleaved: while both have entries, datCalcRand(100) < 50 (first pick), 80 (odd picks) or 20 (even picks)
// takes a party member, else an enemy; the rest of the longer list follows; the free slots are cleared.
void sub_29A750(EEContext& ctx) {
    using namespace hg;
    // The stack arrays: the candidates {btlAction*, u8 weight} (8-byte entries) and the drawn lists (u32).
    constexpr s32 kEnemyDrawn = 160, kPartyDrawn = 208, kEnemyPool = 256, kPartyPool = 352;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0029a750
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
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
    jal(ctx, 0x29A77Cu, gen::fn_btlOrderSortByAgility_0029a570);
    // 1. the order's actions other than the player's: enemies (weight 10) and party members (the weights at
    //    gp-26344); fp counts both
    lw(a1, gp, kGpBtl);  // gBtl
    s7 = addiu(a1, 596);
    a3 = 0;
    s4 = 0;
    s2 = 0;
    s1 = 0;
    fp = 0;
    a2 = 0;
    a0 = 1;
    t1 = 10;
    v1 = addiu(gp, -26344);  // &0x7CC608
    for (;;) {
        // 0x0029a874
        charge(ctx, 4);
        t0 = a2 & 0xFFFF;
        t0 = slti(t0, 12);
        if (t0 != 0) {
            backedge(ctx);
            // 0x0029a7b8
            charge(ctx, 6);
            t0 = a2 & 0xFFFF;
            t0 = sll(t0, 2);
            t0 = addu(s7, t0);
            lw(s0, t0, 0);
            if (s0 != 0) {
                // 0x0029a7d0
                charge(ctx, 3);
                lw(t0, a1, kBtlPlayerAction);
                if (t0 != s0) {
                    // 0x0029a7dc
                    charge(ctx, 4);
                    lw(t0, s0, 48);
                    lbu(t0, t0, 162);
                    if (t0 == a0) {
                        // 0x0029a838
                        charge(ctx, 11);
                        t0 = s4 & 0xFFFF;
                        t0 = sll(t0, 3);
                        t0 = addu(t0, sp);
                        t0 = addiu(t0, kEnemyPool);
                        sw(s0, t0, 0);
                        sb(t1, t0, 4);
                        lbu(t0, t0, 4);
                        t0 = addu(s1, t0);
                        s1 = t0 & 0xFFFF;
                        t0 = addiu(s4, 1);
                        s4 = t0 & 0xFFFF;
                    } else {
                        // 0x0029a7ec
                        charge(ctx, 2);
                        if (t0 == 0) {
                            // 0x0029a7fc
                            charge(ctx, 15);
                            t3 = a3 & 0xFFFF;
                            t0 = sll(t3, 3);
                            t0 = addu(t0, sp);
                            t2 = addiu(t0, kPartyPool);
                            sw(s0, t2, 0);
                            t0 = addu(v1, t3);
                            lbu(t0, t0, 0);
                            sb(t0, t2, 4);
                            lbu(t0, t2, 4);
                            t0 = addu(s2, t0);
                            s2 = t0 & 0xFFFF;
                            a3 = addiu(a3, 1);
                            a3 = a3 & 0xFFFF;
                        } else {
                            // 0x0029a7f4
                            charge(ctx, 2);
                        }
                    }
                    // 0x0029a864
                    charge(ctx, 2);
                    t0 = addiu(fp, 0x1);
                    fp = t0 & 0xFFFF;
                }
                // 0x0029a86c
                charge(ctx, 2);
                a2 = addiu(a2, 1);
                a2 = a2 & 0xFFFF;
                continue;
            }
        }
        break;
    }
    // 0x0029a884 -- 2. draw the party members one by one: datCalcRand(total weight) walked cumulatively
    charge(ctx, 5);
    s3 = 0;
    s5 = 0;
    s6 = a3 & 0xFFFF;
    for (;;) {
        // 0x0029a940
        charge(ctx, 4);
        v1 = s5 & 0xFFFF;
        v1 = slt(v1, s6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a898
        charge(ctx, 7);
        a0 = s2 & 0xFFFF;
        jal(ctx, 0x29A89Cu, gen::fn_datCalcRand_002ffbc0);
        v1 = v0 & 0xFFFF;
        a0 = 0;
        for (;;) {
            // 0x0029a928
            charge(ctx, 4);
            a1 = a0 & 0xFFFF;
            a1 = slt(a1, s6);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a8b4
            charge(ctx, 8);
            a1 = a0 & 0xFFFF;
            a1 = sll(a1, 3);
            a1 = addu(a1, sp);
            t0 = addiu(a1, kPartyPool);
            a3 = addiu(t0, 4);
            lbu(a2, t0, 4);
            if (i64(a2) > 0) {
                // 0x0029a8d4
                charge(ctx, 4);
                a1 = v1 & 0xFFFF;
                at = slt(a1, a2);
                if (at == 0) {
                    goto L_0029a914;
                }
                goto L_0029a8e4_15;
            }
        L_0029a914:
            charge(ctx, 5);
            a1 = a2 & 0xFF;
            v1 = subu(v1, a1);
            v1 = v1 & 0xFFFF;
            a0 = addiu(a0, 1);
            a0 = a0 & 0xFFFF;
        }
    L_0029a938:
        charge(ctx, 2);
        v1 = addiu(s5, 1);
        s5 = v1 & 0xFFFF;
    }
    // 0x0029a950 -- 3. the same for the enemies
    charge(ctx, 5);
    s2 = 0;
    s3 = 0;
    s4 = s4 & 0xFFFF;
    for (;;) {
        // 0x0029aa0c
        charge(ctx, 4);
        v1 = s3 & 0xFFFF;
        v1 = slt(v1, s4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a964
        charge(ctx, 7);
        a0 = s1 & 0xFFFF;
        jal(ctx, 0x29A968u, gen::fn_datCalcRand_002ffbc0);
        t0 = v0 & 0xFFFF;
        a3 = 0;
        for (;;) {
            // 0x0029a9f4
            charge(ctx, 4);
            v1 = a3 & 0xFFFF;
            v1 = slt(v1, s4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a980
            charge(ctx, 8);
            v1 = a3 & 0xFFFF;
            v1 = sll(v1, 3);
            v1 = addu(v1, sp);
            a2 = addiu(v1, kEnemyPool);
            a1 = addiu(a2, 4);
            lbu(a0, a2, 4);
            if (i64(a0) > 0) {
                // 0x0029a9a0
                charge(ctx, 4);
                v1 = t0 & 0xFFFF;
                at = slt(v1, a0);
                if (at == 0) {
                    goto L_0029a9e0;
                }
                goto L_0029a9b0_24;
            }
        L_0029a9e0:
            charge(ctx, 5);
            v1 = a0 & 0xFF;
            v1 = subu(t0, v1);
            t0 = v1 & 0xFFFF;
            v1 = addiu(a3, 1);
            a3 = v1 & 0xFFFF;
        }
    L_0029aa04:
        charge(ctx, 2);
        v1 = addiu(s3, 1);
        s3 = v1 & 0xFFFF;
    }
    // 0x0029aa1c -- 4. the player first, then the drawn lists interleaved: a party member when datCalcRand(100)
    //    < 50 (first pick), 80 (odd picks), 20 (even picks); the longer list's rest after
    charge(ctx, 10);
    s2 = 0;
    s1 = 0;
    lw(v1, gp, kGpBtl);  // gBtl
    lw(v1, v1, kBtlPlayerAction);
    sw(v1, s7, 0);
    s5 = 1;
    s3 = 0;
    fp = fp & 0xFFFF;
    for (;;) {
        // 0x0029ab68
        charge(ctx, 4);
        a0 = s3 & 0xFFFF;
        v1 = slt(a0, fp);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029aa44
        charge(ctx, 4);
        a1 = s2 & 0xFFFF;
        at = slt(a1, s6);
        if (at != 0) {
            // 0x0029aa54
            charge(ctx, 4);
            v1 = s1 & 0xFFFF;
            at = slt(v1, s4);
            if (at == 0) {
                goto L_0029aaf8;
            }
            // 0x0029aa64
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x0029aa78
                charge(ctx, 3);
                v0 = a0 & 0x1;
                if (v0 == 0) {
                    // 0x0029aa90
                    charge(ctx, 1);
                    v0 = 20;
                } else {
                    // 0x0029aa84
                    charge(ctx, 3);
                    v0 = 80;
                }
                // 0x0029aa94
                charge(ctx, 1);
                v0 = v0 & 0xFFFF;
            } else {
                // 0x0029aa6c
                charge(ctx, 3);
                v0 = 50;
            }
            // 0x0029aa98
            charge(ctx, 8);
            s0 = v0 & 0xFFFF;
            a0 = 100;
            jal(ctx, 0x29AAA0u, gen::fn_datCalcRand_002ffbc0);
            v1 = s0 & 0xFFFF;
            at = sltu(v0, v1);
            if (at == 0) {
                // 0x0029aad8
                charge(ctx, 8);
                v1 = s1 & 0xFFFF;
                v1 = sll(v1, 2);
                v1 = addu(v1, sp);
                lw(s0, v1, kEnemyDrawn);
                v1 = addiu(s1, 1);
                s1 = v1 & 0xFFFF;
            } else {
                // 0x0029aab8
                charge(ctx, 8);
                v1 = s2 & 0xFFFF;
                v1 = sll(v1, 2);
                v1 = addu(v1, sp);
                lw(s0, v1, kPartyDrawn);
                v1 = addiu(s2, 1);
                s2 = v1 & 0xFFFF;
            }
            goto L_0029ab48;
        }
    L_0029aaf8:
        charge(ctx, 3);
        at = slt(a1, s6);
        if (at == 0) {
            // 0x0029ab24
            charge(ctx, 4);
            v1 = s1 & 0xFFFF;
            at = slt(v1, s4);
            if (at != 0) {
                // 0x0029ab34
                charge(ctx, 5);
                v1 = sll(v1, 2);
                v1 = addu(v1, sp);
                lw(s0, v1, kEnemyDrawn);
                v1 = addiu(s1, 1);
                s1 = v1 & 0xFFFF;
            }
        } else {
            // 0x0029ab04
            charge(ctx, 8);
            v1 = s2 & 0xFFFF;
            v1 = sll(v1, 2);
            v1 = addu(v1, sp);
            lw(s0, v1, kPartyDrawn);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
    L_0029ab48:
        charge(ctx, 8);
        v1 = s5 & 0xFFFF;
        v1 = sll(v1, 2);
        v1 = addu(s7, v1);
        sw(s0, v1, 0);
        v1 = addiu(s5, 1);
        s5 = v1 & 0xFFFF;
        v1 = addiu(s3, 1);
        s3 = v1 & 0xFFFF;
    }
    // 0x0029ab78 -- 5. clear the free slots
    charge(ctx, 3);
    a0 = s5 & 0xFFFF;
    for (;;) {
        // 0x0029ab9c
        charge(ctx, 4);
        v1 = a0 & 0xFFFF;
        v1 = slti(v1, 12);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029ab84
        charge(ctx, 6);
        v1 = a0 & 0xFFFF;
        v1 = sll(v1, 2);
        v1 = addu(s7, v1);
        sw(zero, v1, 0);
        v1 = addiu(a0, 1);
        a0 = v1 & 0xFFFF;
    }
    // 0x0029abac
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
    sp = addiu(sp, 0x1C0);
    return;
L_0029a8e4_15:  // a party member drawn: its weight leaves the total, it is appended and zeroed
    charge(ctx, 12);
    v1 = subu(s2, a2);
    s2 = v1 & 0xFFFF;
    lw(a0, t0, 0);
    v1 = s3 & 0xFFFF;
    v1 = sll(v1, 2);
    v1 = addu(v1, sp);
    sw(a0, v1, kPartyDrawn);
    sb(zero, a3, 0);
    v1 = addiu(s3, 1);
    s3 = v1 & 0xFFFF;
    goto L_0029a938;
L_0029a9b0_24:  // an enemy drawn
    charge(ctx, 12);
    v1 = subu(s1, a0);
    s1 = v1 & 0xFFFF;
    lw(a0, a2, 0);
    v1 = s2 & 0xFFFF;
    v1 = sll(v1, 2);
    v1 = addu(v1, sp);
    sw(a0, v1, kEnemyDrawn);
    sb(zero, a1, 0);
    v1 = addiu(s2, 1);
    s2 = v1 & 0xFFFF;
    goto L_0029aa04;
}

// 0x0029ABE0 sub_29ABE0 -- 132 bytes; frame 0x10: ra sp+0x0
// [btlOrderOnActionEnd](action): an action queued for the next round (flags bit 2) is removed from gBtl+644 (sub_29A250,
// 12 slots) and loses the flag; else with gBtl+12 bit 3 gBtl+592 = action and sub_29A4F0 moves it to the end of the
// order. Then order flags (gBtl+584) |= 8 (the next turn may start).
void sub_29ABE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029abe0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lhu(v1, a0, kActFlags);
    v1 = v1 & 0x4;
    if (v1 == 0) {
        // 0x0029ac24
        charge(ctx, 5);
        lw(a1, gp, kGpBtl);  // gBtl
        lw(v1, a1, kBtlFlags);
        v1 = v1 & 0x8;
        if (v1 != 0) {
            // 0x0029ac38
            charge(ctx, 3);
            sw(a2, a1, kBtlOrderActor);
            jal(ctx, 0x29AC3Cu, gen::fn_sub_29A4F0_0029a4f0);
        }
    } else {
        // 0x0029abfc
        charge(ctx, 10);
        lw(v0, gp, kGpBtl);  // gBtl
        a0 = addiu(v0, 644);
        a1 = 12;
        jal(ctx, 0x29AC08u, gen::fn_sub_29A250_0029a250);
        lhu(v1, a2, kActFlags);  // $a2 = the action (sub_29A250 leaves it)
        v1 = v1 & 0xFFFB;
        sh(v1, a2, kActFlags);
    }
    // 0x0029ac44 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBtl);  // gBtl
    lhu(v1, a0, kBtlOrderFlags);
    v1 = v1 | 0x8;
    sh(v1, a0, kBtlOrderFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029AC70 sub_29AC70 -- 164 bytes; frame 0x10: ra sp+0x0
// [btlOrderOnActionEnd2](action): sub_29ABE0 without the move to the end: the next-round removal, then order flags |= 8.
void sub_29AC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029ac70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lhu(v1, a0, kActFlags);
    v1 = v1 & 0x4;
    if (v1 == 0) {
        // 0x0029acf4
        charge(ctx, 4);
        lw(a0, gp, kGpBtl);  // gBtl
        lhu(v1, a0, kBtlOrderFlags);
        v1 = v1 | 0x8;
        sh(v1, a0, kBtlOrderFlags);
    } else {
        // 0x0029ac8c
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0029acbc
            charge(ctx, 5);
            lw(a1, gp, kGpBtl);  // gBtl
            lw(v1, a1, kBtlFlags);
            v1 = v1 & 0x8;
            if (v1 != 0) {
                // 0x0029acd0
                charge(ctx, 3);
                sw(a2, a1, kBtlOrderActor);
                jal(ctx, 0x29ACD4u, gen::fn_sub_29A4F0_0029a4f0);
            }
        } else {
            // 0x0029ac94
            charge(ctx, 10);
            lw(v0, gp, kGpBtl);  // gBtl
            a0 = addiu(v0, 644);
            a1 = 12;
            jal(ctx, 0x29ACA0u, gen::fn_sub_29A250_0029a250);
            lhu(v1, a2, kActFlags);  // $a2 = the action (sub_29A250 leaves it)
            v1 = v1 & 0xFFFB;
            sh(v1, a2, kActFlags);
        }
        // 0x0029acdc
        charge(ctx, 6);
        lw(a0, gp, kGpBtl);  // gBtl
        lhu(v1, a0, kBtlOrderFlags);
        v1 = v1 | 0x8;
        sh(v1, a0, kBtlOrderFlags);
    }
    // 0x0029ad04 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029AE40 sub_29AE40 -- 504 bytes; frame 0x10: ra sp+0x0
// [btlOrderUpdate] (btlUpdateTask): starts the next turn. Only with the order active (gBtl+584 bit 0), not paused (gBtl+12
// bit 19) and a turn allowed (bit 3): an action queued for the next round (gBtl+644) in StandBy (state 1) is flagged 4 and
// resumes its saved state (+22); else, after the first turn (gBtl+588 != 0), a pending reshuffle for the enemies (bit 1,
// head on side 1) or the party (bit 2, head on side 0) runs sub_29A750; then the head of gBtl+596 in StandBy gets its
// return state (8 = AI for enemies, 9 = Auto in an auto battle (gBtl+12 bit 13), 5 = Command for the player action, 8
// otherwise) and enters state 2 (Start). Each start clears bit 3 and counts gBtl+588.
void sub_29AE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029ae40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t0, gp, kGpBtl);  // gBtl
    lhu(a3, t0, kBtlOrderFlags);
    v1 = a3 & 0x1;
    if (v1 != 0) {  // the order is active
        // 0x0029ae5c
        charge(ctx, 5);
        lw(a0, t0, kBtlFlags);
        v1 = 0x80000;
        v1 = a0 & v1;
        if (v1 == 0) {  // not paused
            // 0x0029ae70
            charge(ctx, 3);
            v1 = a3 & 0x8;
            if (v1 != 0) {  // a turn may start
                // 0x0029ae7c
                charge(ctx, 4);
                a2 = addiu(t0, 644);
                lw(a1, t0, kBtlOrderNext);
                if (a1 == 0) {  // nobody queued for the next round: the head of the order
                    // 0x0029aee0
                    charge(ctx, 4);
                    v1 = addiu(t0, 596);
                    lw(a0, t0, kBtlOrderTurns);
                    if (a0 != 0) {  // after the first turn: the pending reshuffles
                        // 0x0029aef0
                        charge(ctx, 3);
                        a0 = a3 & 0x2;
                        if (a0 != 0) {
                            // 0x0029aefc
                            charge(ctx, 6);
                            lw(a0, v1, 0);
                            lw(a0, a0, kActUnit);
                            lbu(a1, a0, kUnSide);
                            a0 = 1;
                            if (a1 == a0) {
                                // 0x0029af14
                                charge(ctx, 7);
                                jal(ctx, 0x29AF14u, gen::fn_sub_29A750_0029a750);
                                lw(a1, gp, kGpBtl);  // gBtl
                                v1 = addiu(a1, 596);
                                lhu(a0, a1, kBtlOrderFlags);
                                a0 = a0 & 0xFFFD;
                                sh(a0, a1, kBtlOrderFlags);
                            }
                        }
                        // 0x0029af30
                        charge(ctx, 5);
                        lw(a0, gp, kGpBtl);  // gBtl
                        lhu(a0, a0, kBtlOrderFlags);
                        a0 = a0 & 0x4;
                        if (a0 != 0) {
                            // 0x0029af44
                            charge(ctx, 5);
                            lw(a0, v1, 0);
                            lw(a0, a0, kActUnit);
                            lbu(a0, a0, kUnSide);
                            if (a0 == 0) {
                                // 0x0029af58
                                charge(ctx, 7);
                                jal(ctx, 0x29AF58u, gen::fn_sub_29A750_0029a750);
                                lw(a1, gp, kGpBtl);  // gBtl
                                v1 = addiu(a1, 596);
                                lhu(a0, a1, kBtlOrderFlags);
                                a0 = a0 & 0xFFFB;
                                sh(a0, a1, kBtlOrderFlags);
                            }
                        }
                    }
                    // 0x0029af74
                    charge(ctx, 3);
                    lw(a2, v1, 0);
                    if (a2 != 0) {
                        // 0x0029af80
                        charge(ctx, 4);
                        lhu(a1, a2, kActState);
                        a0 = 1;
                        if (a1 == a0) {
                            // 0x0029af90
                            charge(ctx, 4);
                            lw(v0, a2, kActUnit);
                            lbu(v0, v0, kUnSide);
                            if (v0 != 0) {
                                // 0x0029aff0
                                charge(ctx, 2);
                                v0 = 8;
                                sh(v0, a2, kActReturn);
                            } else {
                                // 0x0029afa0
                                charge(ctx, 5);
                                lw(a0, gp, kGpBtl);  // gBtl
                                lw(v0, a0, kBtlFlags);
                                v0 = v0 & 0x2000;
                                if (v0 == 0) {
                                    // 0x0029afc4
                                    charge(ctx, 3);
                                    lw(v0, a0, kBtlPlayerAction);
                                    if (v0 != a2) {
                                        // 0x0029afe0
                                        charge(ctx, 4);
                                        v0 = 8;
                                        sh(v0, a2, kActReturn);
                                    } else {
                                        // 0x0029afd0
                                        charge(ctx, 4);
                                        v0 = 5;
                                        sh(v0, a2, kActReturn);
                                    }
                                } else {
                                    // 0x0029afb4
                                    charge(ctx, 4);
                                    v0 = 9;
                                    sh(v0, a2, kActReturn);
                                }
                            }
                            // 0x0029aff8 -- Start (state 2); the turn is taken
                            charge(ctx, 12);
                            lw(a0, v1, 0);
                            a1 = 2;
                            jal(ctx, 0x29B000u, gen::fn_btlActionSetState_00299d60);
                            lw(a0, gp, kGpBtl);  // gBtl
                            lhu(v1, a0, kBtlOrderFlags);
                            v1 = v1 & 0xFFF7;
                            sh(v1, a0, kBtlOrderFlags);
                            lw(a0, gp, kGpBtl);  // gBtl
                            lw(v1, a0, kBtlOrderTurns);
                            v1 = addiu(v1, 1);
                            sw(v1, a0, kBtlOrderTurns);
                        }
                    }
                } else {  // the action queued for the next round resumes its saved state
                    // 0x0029ae8c
                    charge(ctx, 4);
                    lhu(a0, a1, kActState);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0029ae9c
                        charge(ctx, 17);
                        lhu(v0, a1, kActFlags);
                        v0 = v0 | 0x4;
                        sh(v0, a1, kActFlags);
                        lw(a0, a2, 0);
                        lhu(a1, a0, kActResume);
                        jal(ctx, 0x29AEB0u, gen::fn_btlActionSetState_00299d60);
                        lw(a0, gp, kGpBtl);  // gBtl
                        lw(v1, a0, kBtlOrderTurns);
                        v1 = addiu(v1, 1);
                        sw(v1, a0, kBtlOrderTurns);
                        lw(a0, gp, kGpBtl);  // gBtl
                        lhu(v1, a0, kBtlOrderFlags);
                        v1 = v1 & 0xFFF7;
                        sh(v1, a0, kBtlOrderFlags);
                    }
                }
            }
        }
    }
    // 0x0029b028 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029DFB0 nullsub_13 -- 8 bytes; leaf frame (no stack)
// nullsub_13: an empty exit hook (btlDestroy).
void nullsub_13(EEContext& ctx) {
    using namespace hg;
    // 0x0029dfb0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0029E370 sub_29E370 -- 32 bytes; frame 0x10: ra sp+0x0
// [btlSceneClose] (btlDestroy): sub_3B5AB0 (the scene teardown).
void sub_29E370(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0029e370
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x29E378u, gen::fn_sub_3B5AB0_003b5ab0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029E390 sub_29E390 -- 44 bytes; frame 0x10: ra sp+0x0
// [btlSceneLoad] (SCENE_SET init): MT_Scene_Load(gBtl+580 field, gBtl+582 room).
void sub_29E390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029e390
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl
    lhu(a0, v0, kBtlSceneField);
    lhu(a1, v0, kBtlSceneRoom);
    jal(ctx, 0x29E3A4u, gen::fn_MT_Scene_Load_003b5760);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029E3C0 sub_29E3C0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlSceneEnd] (END update): gBtl+12 &= ~2 (scene active), sub_3B5AB0.
void sub_29E3C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029e3c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl
    lw(v1, a0, kBtlFlags);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(v0, a0, kBtlFlags);
    jal(ctx, 0x29E3DCu, gen::fn_sub_3B5AB0_003b5ab0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029E400 sub_29E400 -- 32 bytes; frame 0x10: ra sp+0x0
// [btlSceneIsReady] (SCENE_SET update): sub_3B5A10().
void sub_29E400(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0029e400
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x29E408u, gen::fn_sub_3B5A10_003b5a10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029E420 sub_29E420 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlSceneUpdateVectors] (btlUpdateTask): with the scene active (gBtl+12 bit 1), copies the two vec4 of gBtl+452 /
// +468 to the scene object's +256 (sub_1A09D0) and +272 (sub_1A0A10).
void sub_29E420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0029e420
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, kGpBtl);  // gBtl
    lw(v1, s0, kBtlFlags);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0029e440
        charge(ctx, 21);
        jal(ctx, 0x29E440u, gen::fn_sub_1A09D0_001a09d0);
        lwc1(f3, s0, kBtlSceneVecA);
        lwc1(f2, s0, kBtlSceneVecA + 4);
        lwc1(f1, s0, kBtlSceneVecA + 8);
        lwc1(f0, s0, kBtlSceneVecA + 12);
        swc1(f3, v0, 0);
        swc1(f2, v0, 4);
        swc1(f1, v0, 8);
        swc1(f0, v0, 12);
        lw(s0, gp, kGpBtl);  // gBtl
        jal(ctx, 0x29E46Cu, gen::fn_sub_1A0A10_001a0a10);
        lwc1(f3, s0, kBtlSceneVecB);
        lwc1(f2, s0, kBtlSceneVecB + 4);
        lwc1(f1, s0, kBtlSceneVecB + 8);
        lwc1(f0, s0, kBtlSceneVecB + 12);
        swc1(f3, v0, 0);
        swc1(f2, v0, 4);
        swc1(f1, v0, 8);
        swc1(f0, v0, 12);
    }
    // 0x0029e494 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
