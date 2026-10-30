// The social-link code 0x3C03F0-0x3C442C and the area map 0x421770-0x4281E4 (slice social_map; social_map.h has the data
// each group works on). docs/ANALYSIS/27_unmapped_bands.md section 8.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass (slice social_map) adds the role of each function above it, names the record offsets
// (social_map.h: the comu timer work block, the comu data tables, the Y map records) and notes what each callee and
// global is; it changes no statement. `// 0x00xxxxxx` lines name the original basic block a C++ block comes from.
//
// Kept as they are by the original: the K_Assert calls (sub_19D3F0, `jr $ra` in retail: a failed check continues),
// the phase-0 store of sub_3C03F0 that the next store overwrites, sub_3C15D0's phase 0 that jumps to phase 3.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/social_map.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);
void fn_Y_LMap_CreateBoxfillTasks_004229d0(p3fes::EEContext&);
void fn_Y_LMap_CreateLMapMenuTask_004238b0(p3fes::EEContext&);
void fn_Y_LMap_CreateLmapModelMoveTask_004264d0(p3fes::EEContext&);
void fn_Y_LMap_CreateLmapModelTask_00425c60(p3fes::EEContext&);
void fn_Y_LMap_CreateLmapTask_00421de0(p3fes::EEContext&);
void fn_Y_LMap_CreateTmxDispTask_00427670(p3fes::EEContext&);
void fn_Y_LMap_UpdateLMapMenuTask_00422ce0(p3fes::EEContext&);
void fn_Y_LMap_UpdateLmapTask_00421770(p3fes::EEContext&);
void fn_Y_Stratum_CreateStratumPartsTask_00447e70(p3fes::EEContext&);
void fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetWeekDay_0017dae0(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_comu_CreateComuTimerProcessTask_003c1ab0(p3fes::EEContext&);
void fn_comu_CreateRevMailSeqTask_003c2350(p3fes::EEContext&);
void fn_comu_UpdateRevMailSeqTask_003c1d20(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetArcanaName_0030bbb0(p3fes::EEContext&);
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_frFontGetStyleSize_003b35c0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_1099D0_001099d0(p3fes::EEContext&);
void fn_sub_109F60_00109f60(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DCE0_0016dce0(p3fes::EEContext&);
void fn_sub_16DD40_0016dd40(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16E670_0016e670(p3fes::EEContext&);
void fn_sub_16E7A0_0016e7a0(p3fes::EEContext&);
void fn_sub_16E850_0016e850(p3fes::EEContext&);
void fn_sub_16E920_0016e920(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_1717B0_001717b0(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_171AC0_00171ac0(p3fes::EEContext&);
void fn_sub_171B50_00171b50(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_1720C0_001720c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_172200_00172200(p3fes::EEContext&);
void fn_sub_1725A0_001725a0(p3fes::EEContext&);
void fn_sub_172660_00172660(p3fes::EEContext&);
void fn_sub_172750_00172750(p3fes::EEContext&);
void fn_sub_1727E0_001727e0(p3fes::EEContext&);
void fn_sub_172860_00172860(p3fes::EEContext&);
void fn_sub_172890_00172890(p3fes::EEContext&);
void fn_sub_1728D0_001728d0(p3fes::EEContext&);
void fn_sub_1729A0_001729a0(p3fes::EEContext&);
void fn_sub_172A30_00172a30(p3fes::EEContext&);
void fn_sub_172A50_00172a50(p3fes::EEContext&);
void fn_sub_172AB0_00172ab0(p3fes::EEContext&);
void fn_sub_172AE0_00172ae0(p3fes::EEContext&);
void fn_sub_172B20_00172b20(p3fes::EEContext&);
void fn_sub_172B80_00172b80(p3fes::EEContext&);
void fn_sub_172C50_00172c50(p3fes::EEContext&);
void fn_sub_172CC0_00172cc0(p3fes::EEContext&);
void fn_sub_172D70_00172d70(p3fes::EEContext&);
void fn_sub_17DDF0_0017ddf0(p3fes::EEContext&);
void fn_sub_17E050_0017e050(p3fes::EEContext&);
void fn_sub_17E520_0017e520(p3fes::EEContext&);
void fn_sub_198540_00198540(p3fes::EEContext&);
void fn_sub_198560_00198560(p3fes::EEContext&);
void fn_sub_198570_00198570(p3fes::EEContext&);
void fn_sub_198580_00198580(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);
void fn_sub_1A1150_001a1150(p3fes::EEContext&);
void fn_sub_1A1190_001a1190(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_1A9760_001a9760(p3fes::EEContext&);
void fn_sub_1AD940_001ad940(p3fes::EEContext&);
void fn_sub_1B00C0_001b00c0(p3fes::EEContext&);
void fn_sub_1B6EB0_001b6eb0(p3fes::EEContext&);
void fn_sub_1C7160_001c7160(p3fes::EEContext&);
void fn_sub_27C2B0_0027c2b0(p3fes::EEContext&);
void fn_sub_27C330_0027c330(p3fes::EEContext&);
void fn_sub_316BD0_00316bd0(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_317A20_00317a20(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_38D6F0_0038d6f0(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);
void fn_sub_3951A0_003951a0(p3fes::EEContext&);
void fn_sub_395200_00395200(p3fes::EEContext&);
void fn_sub_395230_00395230(p3fes::EEContext&);
void fn_sub_3952D0_003952d0(p3fes::EEContext&);
void fn_sub_39EC70_0039ec70(p3fes::EEContext&);
void fn_sub_39EE80_0039ee80(p3fes::EEContext&);
void fn_sub_39EF30_0039ef30(p3fes::EEContext&);
void fn_sub_39F210_0039f210(p3fes::EEContext&);
void fn_sub_39F410_0039f410(p3fes::EEContext&);
void fn_sub_39F6E0_0039f6e0(p3fes::EEContext&);
void fn_sub_3A2090_003a2090(p3fes::EEContext&);
void fn_sub_3B5980_003b5980(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B91C0_003b91c0(p3fes::EEContext&);
void fn_sub_3B9320_003b9320(p3fes::EEContext&);
void fn_sub_3BB010_003bb010(p3fes::EEContext&);
void fn_sub_3BD870_003bd870(p3fes::EEContext&);
void fn_sub_3BDBD0_003bdbd0(p3fes::EEContext&);
void fn_sub_3BDD50_003bdd50(p3fes::EEContext&);
void fn_sub_3BDDE0_003bdde0(p3fes::EEContext&);
void fn_sub_3BDFC0_003bdfc0(p3fes::EEContext&);
void fn_sub_3BE1A0_003be1a0(p3fes::EEContext&);
void fn_sub_3BE2A0_003be2a0(p3fes::EEContext&);
void fn_sub_3BE8E0_003be8e0(p3fes::EEContext&);
void fn_sub_3BEBD0_003bebd0(p3fes::EEContext&);
void fn_sub_3BEC50_003bec50(p3fes::EEContext&);
void fn_sub_3BF130_003bf130(p3fes::EEContext&);
void fn_sub_3BF180_003bf180(p3fes::EEContext&);
void fn_sub_3BF200_003bf200(p3fes::EEContext&);
void fn_sub_3BFFA0_003bffa0(p3fes::EEContext&);
void fn_sub_3C03F0_003c03f0(p3fes::EEContext&);
void fn_sub_3C0570_003c0570(p3fes::EEContext&);
void fn_sub_3C07C0_003c07c0(p3fes::EEContext&);
void fn_sub_3C09A0_003c09a0(p3fes::EEContext&);
void fn_sub_3C0B30_003c0b30(p3fes::EEContext&);
void fn_sub_3C0BD0_003c0bd0(p3fes::EEContext&);
void fn_sub_3C0C30_003c0c30(p3fes::EEContext&);
void fn_sub_3C0D20_003c0d20(p3fes::EEContext&);
void fn_sub_3C0DB0_003c0db0(p3fes::EEContext&);
void fn_sub_3C0F20_003c0f20(p3fes::EEContext&);
void fn_sub_3C1150_003c1150(p3fes::EEContext&);
void fn_sub_3C1300_003c1300(p3fes::EEContext&);
void fn_sub_3C1340_003c1340(p3fes::EEContext&);
void fn_sub_3C1430_003c1430(p3fes::EEContext&);
void fn_sub_3C1440_003c1440(p3fes::EEContext&);
void fn_sub_3C15D0_003c15d0(p3fes::EEContext&);
void fn_sub_3C1810_003c1810(p3fes::EEContext&);
void fn_sub_3C18C0_003c18c0(p3fes::EEContext&);
void fn_sub_3C1A70_003c1a70(p3fes::EEContext&);
void fn_sub_3C22F0_003c22f0(p3fes::EEContext&);
void fn_sub_3C23F0_003c23f0(p3fes::EEContext&);
void fn_sub_3C2570_003c2570(p3fes::EEContext&);
void fn_sub_3C2630_003c2630(p3fes::EEContext&);
void fn_sub_3C2770_003c2770(p3fes::EEContext&);
void fn_sub_3C2780_003c2780(p3fes::EEContext&);
void fn_sub_3C28A0_003c28a0(p3fes::EEContext&);
void fn_sub_3C2AB0_003c2ab0(p3fes::EEContext&);
void fn_sub_3C2B40_003c2b40(p3fes::EEContext&);
void fn_sub_3C2C50_003c2c50(p3fes::EEContext&);
void fn_sub_3C2DF0_003c2df0(p3fes::EEContext&);
void fn_sub_3C2EE0_003c2ee0(p3fes::EEContext&);
void fn_sub_3C3050_003c3050(p3fes::EEContext&);
void fn_sub_3C30B0_003c30b0(p3fes::EEContext&);
void fn_sub_3C3120_003c3120(p3fes::EEContext&);
void fn_sub_3C3190_003c3190(p3fes::EEContext&);
void fn_sub_3C3390_003c3390(p3fes::EEContext&);
void fn_sub_3C33C0_003c33c0(p3fes::EEContext&);
void fn_sub_3C3E80_003c3e80(p3fes::EEContext&);
void fn_sub_3C3F40_003c3f40(p3fes::EEContext&);
void fn_sub_3C3F80_003c3f80(p3fes::EEContext&);
void fn_sub_3C3FE0_003c3fe0(p3fes::EEContext&);
void fn_sub_3C4040_003c4040(p3fes::EEContext&);
void fn_sub_3C40F0_003c40f0(p3fes::EEContext&);
void fn_sub_3C4110_003c4110(p3fes::EEContext&);
void fn_sub_3C4130_003c4130(p3fes::EEContext&);
void fn_sub_3C4210_003c4210(p3fes::EEContext&);
void fn_sub_3C4270_003c4270(p3fes::EEContext&);
void fn_sub_3C4390_003c4390(p3fes::EEContext&);
void fn_sub_3C43F0_003c43f0(p3fes::EEContext&);
void fn_sub_3C4400_003c4400(p3fes::EEContext&);
void fn_sub_3C4410_003c4410(p3fes::EEContext&);
void fn_sub_3C4420_003c4420(p3fes::EEContext&);
void fn_sub_421760_00421760(p3fes::EEContext&);
void fn_sub_421D70_00421d70(p3fes::EEContext&);
void fn_sub_421EF0_00421ef0(p3fes::EEContext&);
void fn_sub_421F10_00421f10(p3fes::EEContext&);
void fn_sub_421F20_00421f20(p3fes::EEContext&);
void fn_sub_421FB0_00421fb0(p3fes::EEContext&);
void fn_sub_421FE0_00421fe0(p3fes::EEContext&);
void fn_sub_4221A0_004221a0(p3fes::EEContext&);
void fn_sub_4222D0_004222d0(p3fes::EEContext&);
void fn_sub_4229A0_004229a0(p3fes::EEContext&);
void fn_sub_422C10_00422c10(p3fes::EEContext&);
void fn_sub_422C30_00422c30(p3fes::EEContext&);
void fn_sub_422C90_00422c90(p3fes::EEContext&);
void fn_sub_422CD0_00422cd0(p3fes::EEContext&);
void fn_sub_423790_00423790(p3fes::EEContext&);
void fn_sub_423B50_00423b50(p3fes::EEContext&);
void fn_sub_423B70_00423b70(p3fes::EEContext&);
void fn_sub_423BA0_00423ba0(p3fes::EEContext&);
void fn_sub_423BF0_00423bf0(p3fes::EEContext&);
void fn_sub_423C10_00423c10(p3fes::EEContext&);
void fn_sub_423CD0_00423cd0(p3fes::EEContext&);
void fn_sub_423FC0_00423fc0(p3fes::EEContext&);
void fn_sub_423FE0_00423fe0(p3fes::EEContext&);
void fn_sub_4241E0_004241e0(p3fes::EEContext&);
void fn_sub_424230_00424230(p3fes::EEContext&);
void fn_sub_4242B0_004242b0(p3fes::EEContext&);
void fn_sub_424310_00424310(p3fes::EEContext&);
void fn_sub_424370_00424370(p3fes::EEContext&);
void fn_sub_424B60_00424b60(p3fes::EEContext&);
void fn_sub_424F80_00424f80(p3fes::EEContext&);
void fn_sub_425020_00425020(p3fes::EEContext&);
void fn_sub_425070_00425070(p3fes::EEContext&);
void fn_sub_4252D0_004252d0(p3fes::EEContext&);
void fn_sub_425320_00425320(p3fes::EEContext&);
void fn_sub_425480_00425480(p3fes::EEContext&);
void fn_sub_425690_00425690(p3fes::EEContext&);
void fn_sub_425BA0_00425ba0(p3fes::EEContext&);
void fn_sub_425D10_00425d10(p3fes::EEContext&);
void fn_sub_425D30_00425d30(p3fes::EEContext&);
void fn_sub_425D50_00425d50(p3fes::EEContext&);
void fn_sub_426040_00426040(p3fes::EEContext&);
void fn_sub_426050_00426050(p3fes::EEContext&);
void fn_sub_426070_00426070(p3fes::EEContext&);
void fn_sub_426090_00426090(p3fes::EEContext&);
void fn_sub_4260A0_004260a0(p3fes::EEContext&);
void fn_sub_4264A0_004264a0(p3fes::EEContext&);
void fn_sub_426590_00426590(p3fes::EEContext&);
void fn_sub_427640_00427640(p3fes::EEContext&);
void fn_sub_427830_00427830(p3fes::EEContext&);
void fn_sub_427A10_00427a10(p3fes::EEContext&);
void fn_sub_427BF0_00427bf0(p3fes::EEContext&);
void fn_sub_427DB0_00427db0(p3fes::EEContext&);
void fn_sub_427DE0_00427de0(p3fes::EEContext&);
void fn_sub_427E20_00427e20(p3fes::EEContext&);
void fn_sub_427E50_00427e50(p3fes::EEContext&);
void fn_sub_427E60_00427e60(p3fes::EEContext&);
void fn_sub_427E70_00427e70(p3fes::EEContext&);
void fn_sub_43A9D0_0043a9d0(p3fes::EEContext&);
void fn_sub_449FA0_00449fa0(p3fes::EEContext&);
void fn_sub_4944B0_004944b0(p3fes::EEContext&);
void fn_sub_49C3D0_0049c3d0(p3fes::EEContext&);
void fn_sub_49C480_0049c480(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x003C03F0 sub_3C03F0 -- 376 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateEvent8C] Phase 0: if the word at gp-0x4680 (0x7CE670) is 0 the phase is first set to 3,
// then overwritten: wait 2 frames (+4 counter, +8 limit), phase 1. Phase 1: after the wait, sequence 3 with event
// 0x8C (words 0x8C, 4, 0 at param +12/+16/+20), phase 2. Phase 2: phase 3 once the sequence manager is idle. Phase 3:
// returns -1 (finished).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C03F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c03f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C03FCu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(a0, v0, 0);
    v1 = 3;
    if (a0 == v1) {
        // 0x003c0544
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x003c0418
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x003c04f4
            charge(ctx, 4);
            jal(ctx, 0x3C04F4u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c0504
                charge(ctx, 5);
                jal(ctx, 0x3C0504u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c0524;
                }
                // 0x003c0518
                charge(ctx, 3);
                v1 = 1;
                goto L_003c0528;
            }
        L_003c0524:
            charge(ctx, 1);
            v1 = 0;
        L_003c0528:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c0534
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c0424
            charge(ctx, 3);
            a1 = 1;
            if (a0 == a1) {
                // 0x003c046c
                charge(ctx, 5);
                lw(v1, s0, kComuWorkWait);
                lw(v0, s0, kComuWorkWaitLimit);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003c0490
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, kComuWorkWait);
                    a1 = 0;
                } else {
                    // 0x003c0480
                    charge(ctx, 4);
                    sw(zero, s0, kComuWorkWait);
                    sw(zero, s0, kComuWorkWaitLimit);
                }
                // 0x003c049c
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x003c04a4
                    charge(ctx, 20);
                    a0 = addiu(sp, 0x20);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3C04B0u, gen::fn_memset_00521408);
                    v0 = 140;
                    sw(v0, sp, 0x2C);
                    v0 = 4;
                    sw(v0, sp, 0x30);
                    sw(zero, sp, 0x34);
                    a0 = 3;
                    a1 = addiu(sp, 0x20);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3C04DCu, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                    v0 = 2;
                    sw(v0, s0, kComuWorkPhase);
                }
            } else {
                // 0x003c0430
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x003c0440
                    charge(ctx, 3);
                    lw(v0, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
                    if (v0 == 0) {
                        // 0x003c044c
                        charge(ctx, 1);
                        sw(v1, s0, kComuWorkPhase);
                    }
                    // 0x003c0450
                    charge(ctx, 7);
                    sw(zero, s0, kComuWorkWait);
                    v0 = 2;
                    sw(v0, s0, kComuWorkWaitLimit);
                    v0 = 1;
                    sw(v0, s0, kComuWorkPhase);
                } else {
                    // 0x003c0438
                    charge(ctx, 2);
                }
            }
        }
        // 0x003c0550
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003c0554 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C0570 sub_3C0570 -- 584 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuTimerStateApril] After a 2-frame wait: on April 21 sets flag bit 0x24, clears gp-0x4680 and starts
// event 0x8D (1); on April 27 flag bit 0x10A and event 0x6F (2); any other day goes straight to phase 3. Phase 3
// clears the six work words and returns the next state sub_3C03F0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0570
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0580u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 3;
    if (v1 == v0) {
        // 0x003c0774
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 1008);  // &sub_3C03F0
    } else {
        // 0x003c059c
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003c0724
            charge(ctx, 4);
            jal(ctx, 0x3C0724u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c0734
                charge(ctx, 5);
                jal(ctx, 0x3C0734u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c0754;
                }
                // 0x003c0748
                charge(ctx, 3);
                v1 = 1;
                goto L_003c0758;
            }
        L_003c0754:
            charge(ctx, 1);
            v1 = 0;
        L_003c0758:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c0764
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c05a8
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x003c05d8
                charge(ctx, 5);
                lw(v1, s0, kComuWorkWait);
                lw(v0, s0, kComuWorkWaitLimit);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003c05fc
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, kComuWorkWait);
                    a0 = 0;
                } else {
                    // 0x003c05ec
                    charge(ctx, 4);
                    sw(zero, s0, kComuWorkWait);
                    sw(zero, s0, kComuWorkWaitLimit);
                }
                // 0x003c0608
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x003c0610
                    charge(ctx, 8);
                    jal(ctx, 0x3C0610u, gen::fn_clndGetCurrentMonth_0017d920);
                    s1 = v0;
                    jal(ctx, 0x3C061Cu, gen::fn_clndGetCurrentDay_0017da40);
                    v1 = 4;
                    if (s1 == v1) {
                        // 0x003c0630
                        charge(ctx, 3);
                        v1 = 21;
                        if (v0 != v1) {
                            goto L_003c069c;
                        }
                        // 0x003c063c
                        charge(ctx, 24);
                        a0 = 36;
                        jal(ctx, 0x3C0640u, gen::fn_sub_395170_00395170);  // flag bit on
                        sw(zero, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
                        a0 = addiu(sp, 0x50);
                        a1 = 0;
                        a2 = 28;
                        jal(ctx, 0x3C0658u, gen::fn_memset_00521408);
                        v0 = 141;
                        sw(v0, sp, 0x5C);
                        v0 = 1;
                        sw(v0, sp, 0x60);
                        sw(zero, sp, 0x64);
                        a0 = 3;
                        a1 = addiu(sp, 0x50);
                        a2 = 28;
                        a3 = 0;
                        jal(ctx, 0x3C0684u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                        v0 = 2;
                        sw(v0, s0, kComuWorkPhase);
                        goto L_003c079c;
                    }
                L_003c069c:
                    charge(ctx, 3);
                    v1 = 4;
                    if (s1 == v1) {
                        // 0x003c06a8
                        charge(ctx, 3);
                        v1 = 27;
                        if (v0 != v1) {
                            goto L_003c0714;
                        }
                        // 0x003c06b4
                        charge(ctx, 24);
                        a0 = 266;
                        jal(ctx, 0x3C06B8u, gen::fn_sub_395170_00395170);  // flag bit on
                        sw(zero, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
                        a0 = addiu(sp, 0x30);
                        a1 = 0;
                        a2 = 28;
                        jal(ctx, 0x3C06D0u, gen::fn_memset_00521408);
                        v0 = 111;
                        sw(v0, sp, 0x3C);
                        v0 = 2;
                        sw(v0, sp, 0x40);
                        sw(zero, sp, 0x44);
                        a0 = 3;
                        a1 = addiu(sp, 0x30);
                        a2 = 28;
                        a3 = 0;
                        jal(ctx, 0x3C06FCu, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                        v0 = 2;
                        sw(v0, s0, kComuWorkPhase);
                        goto L_003c079c;
                    }
                L_003c0714:
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, kComuWorkPhase);
                }
            } else {
                // 0x003c05b4
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003c05c4
                    charge(ctx, 5);
                    sw(zero, s0, kComuWorkWait);
                    sw(v0, s0, kComuWorkWaitLimit);
                    sw(a0, s0, kComuWorkPhase);
                } else {
                    // 0x003c05bc
                    charge(ctx, 2);
                }
            }
        }
    L_003c079c:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003c07a0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003C07C0 sub_3C07C0 -- 468 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuTimerStateDaily] After the wait asks sub_3BFFA0 for today's event (three words through its frame at
// sp+0x7C/0x78/0x74); none: phase 3; one: clears gp-0x4680, sequence 3 with those words, phase 2. Phase 3 returns
// sub_3C0570.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C07C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c07c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C07D8u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    sw(zero, sp, 0x7C);
    sw(zero, sp, 0x78);
    sw(zero, sp, 0x74);
    lw(v1, v0, 0);
    v0 = 3;
    if (v1 == v0) {
        // 0x003c0948
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 1392);  // &sub_3C0570
    } else {
        // 0x003c0800
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003c08f8
            charge(ctx, 4);
            jal(ctx, 0x3C08F8u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c0908
                charge(ctx, 5);
                jal(ctx, 0x3C0908u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c0928;
                }
                // 0x003c091c
                charge(ctx, 3);
                v1 = 1;
                goto L_003c092c;
            }
        L_003c0928:
            charge(ctx, 1);
            v1 = 0;
        L_003c092c:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c0938
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c080c
            charge(ctx, 3);
            a0 = 1;
            if (v1 == a0) {
                // 0x003c083c
                charge(ctx, 5);
                lw(v1, s0, kComuWorkWait);
                lw(v0, s0, kComuWorkWaitLimit);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003c0860
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, kComuWorkWait);
                    a0 = 0;
                } else {
                    // 0x003c0850
                    charge(ctx, 4);
                    sw(zero, s0, kComuWorkWait);
                    sw(zero, s0, kComuWorkWaitLimit);
                }
                // 0x003c086c
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x003c0874
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x7C);
                    a1 = addiu(sp, 0x78);
                    a2 = addiu(sp, 0x74);
                    jal(ctx, 0x3C0880u, gen::fn_sub_3BFFA0_003bffa0);
                    if (v0 != 0) {
                        // 0x003c08a0
                        charge(ctx, 22);
                        sw(zero, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
                        lw(s3, sp, 0x74);
                        lw(s2, sp, 0x78);
                        lw(s1, sp, 0x7C);
                        a0 = addiu(sp, 0x50);
                        a1 = 0;
                        a2 = 28;
                        jal(ctx, 0x3C08BCu, gen::fn_memset_00521408);
                        sw(s1, sp, 0x5C);
                        sw(s2, sp, 0x60);
                        sw(s3, sp, 0x64);
                        a0 = 3;
                        a1 = addiu(sp, 0x50);
                        a2 = 28;
                        a3 = 0;
                        jal(ctx, 0x3C08E0u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                        v0 = 2;
                        sw(v0, s0, kComuWorkPhase);
                    } else {
                        // 0x003c0890
                        charge(ctx, 4);
                        v0 = 3;
                        sw(v0, s0, kComuWorkPhase);
                    }
                }
            } else {
                // 0x003c0818
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003c0828
                    charge(ctx, 5);
                    sw(zero, s0, kComuWorkWait);
                    sw(v0, s0, kComuWorkWaitLimit);
                    sw(a0, s0, kComuWorkPhase);
                } else {
                    // 0x003c0820
                    charge(ctx, 2);
                }
            }
        }
        // 0x003c0970
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003c0974 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003C09A0 sub_3C09A0 -- 388 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateEvent321] Event 0x321 (1) after the wait; once idle: sub_38D6F0(0) == 0 finishes (-1),
// otherwise the next state is sub_3C07C0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C09A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c09a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C09ACu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x003c09c8
        charge(ctx, 3);
        a0 = 1;
        if (v1 == a0) {
            // 0x003c09f8
            charge(ctx, 5);
            lw(v1, s0, kComuWorkWait);
            lw(v0, s0, kComuWorkWaitLimit);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003c0a1c
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s0, kComuWorkWait);
                a0 = 0;
            } else {
                // 0x003c0a0c
                charge(ctx, 4);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
            }
            // 0x003c0a28
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x003c0a30
                charge(ctx, 21);
                sw(zero, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
                a0 = addiu(sp, 0x20);
                a1 = 0;
                a2 = 28;
                jal(ctx, 0x3C0A40u, gen::fn_memset_00521408);
                v0 = 801;
                sw(v0, sp, 0x2C);
                v0 = 1;
                sw(v0, sp, 0x30);
                sw(zero, sp, 0x34);
                a0 = 3;
                a1 = addiu(sp, 0x20);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x3C0A6Cu, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                v0 = 2;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c09d4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003c09e4
                charge(ctx, 5);
                sw(zero, s0, kComuWorkWait);
                sw(v0, s0, kComuWorkWaitLimit);
                sw(a0, s0, kComuWorkPhase);
            } else {
                // 0x003c09dc
                charge(ctx, 2);
            }
        }
        goto L_003c0b0c;
    }
    // 0x003c0a84
    charge(ctx, 4);
    jal(ctx, 0x3C0A84u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
    if (v0 == 0) {
        // 0x003c0a94
        charge(ctx, 5);
        jal(ctx, 0x3C0A94u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003c0ab4;
        }
        // 0x003c0aa8
        charge(ctx, 3);
        v1 = 1;
        goto L_003c0ab8;
    }
L_003c0ab4:
    charge(ctx, 1);
    v1 = 0;
L_003c0ab8:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003c0b0c:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c0ac4
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x3C0AC8u, gen::fn_sub_38D6F0_0038d6f0);
        if (v0 != 0) {
            // 0x003c0ae4
            charge(ctx, 10);
            sw(zero, s0, kComuWorkPhase);
            sw(zero, s0, kComuWorkWait);
            sw(zero, s0, kComuWorkWaitLimit);
            sw(zero, s0, kComuWorkWord3);
            sw(zero, s0, kComuWorkWord4);
            sw(zero, s0, kComuWorkWord5);
            v0 = 0x3C0000;
            v0 = addiu(v0, 1984);  // &sub_3C07C0
        } else {
            // 0x003c0ad8
            charge(ctx, 3);
            v0 = si(-1);
        }
    }
    // 0x003c0b10 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C0B30 sub_3C0B30 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateCheckFlag] Calls datGetPhysicalCondition(1) (result unused), then flag 0xBDE set ->
// next state sub_3C09A0, else sub_3C07C0 (the work words cleared either way).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0B30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0b30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0B3Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x3C0B4Cu, gen::fn_sub_16C920_0016c920);
    a0 = 3038;
    jal(ctx, 0x3C0B58u, gen::fn_MT_Misc_BitChk_003951d0);
    v1 = 1;
    if (v0 != v1) {
        // 0x003c0b94
        charge(ctx, 8);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 1984);  // &sub_3C07C0
    } else {
        // 0x003c0b6c
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 2464);  // &sub_3C09A0
    }
    // 0x003c0bb4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C0BD0 sub_3C0BD0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateKind1] The entry state of timer kind 1 (comu_CreateComuTimerProcessTask case 1): sub_3BDDE0(), gp-0x4680 = 1,
// next state sub_3C0B30.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0BD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0bd0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0BDCu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    jal(ctx, 0x3C0BE8u, gen::fn_sub_3BDDE0_003bdde0);
    v0 = 1;
    sw(v0, gp, -18048);  // 0x7CE670 gp-0x4680: the comu event word (1 while a kind-1 timer runs)
    sw(zero, s0, kComuWorkPhase);
    sw(zero, s0, kComuWorkWait);
    sw(zero, s0, kComuWorkWaitLimit);
    sw(zero, s0, kComuWorkWord3);
    sw(zero, s0, kComuWorkWord4);
    sw(zero, s0, kComuWorkWord5);
    v0 = 0x3C0000;
    v0 = addiu(v0, 2864);  // &sub_3C0B30
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C0C30 sub_3C0C30 -- 240 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateSeq2_7_1] Phase 0: sequence 2 with the halfword parameter (7, 1, 0, 0), phase 1; phase 1
// finishes once the sequence manager is idle.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0c30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0C3Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 1;
    if (v1 != v0) {
        // 0x003c0c58
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x003c0c68
            charge(ctx, 21);
            a0 = addiu(sp, 0x20);
            a1 = 0;
            a2 = 28;
            jal(ctx, 0x3C0C74u, gen::fn_memset_00521408);
            v0 = 7;
            sh(v0, sp, 0x20);
            v0 = 1;
            sh(v0, sp, 0x22);
            sh(zero, sp, 0x24);
            sh(zero, sp, 0x28);
            a0 = 2;
            a1 = addiu(sp, 0x20);
            a2 = 28;
            a3 = 0;
            jal(ctx, 0x3C0CA4u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
            v0 = 1;
            sw(v0, s0, kComuWorkPhase);
        } else {
            // 0x003c0c60
            charge(ctx, 2);
        }
        goto L_003c0d08;
    }
    // 0x003c0cbc
    charge(ctx, 4);
    jal(ctx, 0x3C0CBCu, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
    if (v0 == 0) {
        // 0x003c0ccc
        charge(ctx, 5);
        jal(ctx, 0x3C0CCCu, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003c0cec;
        }
        // 0x003c0ce0
        charge(ctx, 3);
        v1 = 1;
        goto L_003c0cf0;
    }
L_003c0cec:
    charge(ctx, 1);
    v1 = 0;
L_003c0cf0:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003c0d08:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c0cfc
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003c0d0c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C0D20 sub_3C0D20 -- 136 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateKind4] sub_172C50(&id at sp+0x2E) nonzero -> next state sub_3BF510, else sub_3C0C30.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0D20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0d20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0D2Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    a0 = addiu(sp, 0x2E);
    jal(ctx, 0x3C0D3Cu, gen::fn_sub_172C50_00172c50);
    if (v0 == 0) {
        // 0x003c0d74
        charge(ctx, 8);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 3120);  // &sub_3C0C30
    } else {
        // 0x003c0d4c
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, -2800);  // &sub_3BF510
    }
    // 0x003c0d94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C0DB0 sub_3C0DB0 -- 360 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuFindDateEvent] Walks the timer-event rows of the comu data (+0x660, 12-byte rows, count +0x664)
// for today's month / day: a row with +4 == 0 needs the after-school time slot (datGetTime() & 0xFF == 2), any other
// the evening slot (4). The first match writes the u16 at +8 to *$a0 and the bytes +10 / +11 to *$a1 / *$a2 and returns
// 1; no match returns 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0db0
    enter(ctx, 30);  // entry check point + this block's cycles
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
    s4 = a1;
    s3 = a2;
    jal(ctx, 0x3C0DE0u, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    s2 = v0;
    lw(s1, v0, kComuEventCount);
    jal(ctx, 0x3C0DF0u, gen::fn_clndGetCurrentMonth_0017d920);
    s0 = v0;
    jal(ctx, 0x3C0DFCu, gen::fn_clndGetCurrentDay_0017da40);
    s6 = v0;
    jal(ctx, 0x3C0E08u, gen::fn_datGetTime_0016ef30);
    a3 = v0 & 0xFF;
    t0 = 0;
    v1 = 4;
    a0 = 2;
    for (;;) {
        // 0x003c0edc
        charge(ctx, 3);
        v0 = slt(t0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c0e28
        charge(ctx, 8);
        lw(a1, s2, kComuEventRows);
        v0 = sll(t0, 1);
        v0 = addu(v0, t0);
        v0 = sll(v0, 2);
        a2 = addu(a1, v0);
        lbu(a1, a2, kEventMonth);
        if (s0 == a1) {
            // 0x003c0e48
            charge(ctx, 3);
            lbu(a1, a2, kEventDay);
            if (s6 != a1) {
                goto L_003c0ed8;
            }
            // 0x003c0e54
            charge(ctx, 3);
            lw(a1, a2, kEventKind);
            if (a1 != 0) {
                // 0x003c0e9c
                charge(ctx, 2);
                if (a3 != v1) {
                    goto L_003c0ed8;
                }
                goto L_003c0ea4_7;
            }
            // 0x003c0e60
            charge(ctx, 2);
            if (a3 != a0) {
                goto L_003c0ed8;
            }
            goto L_003c0e68_5;
        }
    L_003c0ed8:
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x003c0ee8
    charge(ctx, 1);
    v0 = 0;
    // 0x003c0eec (the shared epilogue, written out on this path)
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
    return;
L_003c0e68_5:
    charge(ctx, 13);
    lhu(v1, a2, kEventId);
    sw(v1, s5, 0);
    lw(v1, s2, kComuEventRows);
    v1 = addu(v0, v1);
    lbu(v1, v1, 10);
    sw(v1, s4, 0);
    lw(v1, s2, kComuEventRows);
    v0 = addu(v0, v1);
    lbu(v0, v0, 11);
    sw(v0, s3, 0);
    v0 = 1;
    // 0x003c0eec (the shared epilogue, written out on this path)
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
    return;
L_003c0ea4_7:
    charge(ctx, 13);
    lhu(v1, a2, kEventId);
    sw(v1, s5, 0);
    lw(v1, s2, kComuEventRows);
    v1 = addu(v0, v1);
    lbu(v1, v1, 10);
    sw(v1, s4, 0);
    lw(v1, s2, kComuEventRows);
    v0 = addu(v0, v1);
    lbu(v0, v0, 11);
    sw(v0, s3, 0);
    v0 = 1;
    // 0x003c0eec (the shared epilogue, written out on this path)
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

// 0x003C0F20 sub_3C0F20 -- 552 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuTimerStateDateEvent] Phase 0: in the evening with flag 0x98C set it finishes at once; otherwise the
// 2-frame wait. Phase 1: sub_3C0DB0's event for today -> sequence 3, phase 2; none -> finished. Phase 3: in the
// after-school slot sets flag 0x98C, then finishes (the event runs once a day).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C0F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c0f20
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C0F38u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    jal(ctx, 0x3C0F44u, gen::fn_sub_1717B0_001717b0);
    jal(ctx, 0x3C0F4Cu, gen::fn_clndGetCurrentMonth_0017d920);
    jal(ctx, 0x3C0F54u, gen::fn_clndGetCurrentDay_0017da40);
    lw(v1, s0, kComuWorkPhase);
    v0 = 3;
    if (v1 == v0) {
        // 0x003c10f4
        charge(ctx, 6);
        jal(ctx, 0x3C10F4u, gen::fn_datGetTime_0016ef30);
        v1 = v0 & 0xFF;
        v0 = 2;
        if (v1 == v0) {
            // 0x003c110c
            charge(ctx, 3);
            a0 = 2444;
            jal(ctx, 0x3C1110u, gen::fn_sub_395170_00395170);  // flag bit on
        }
        // 0x003c1118
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x003c0f6c
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x003c10a4
            charge(ctx, 4);
            jal(ctx, 0x3C10A4u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c10b4
                charge(ctx, 5);
                jal(ctx, 0x3C10B4u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c10d4;
                }
                // 0x003c10c8
                charge(ctx, 3);
                v1 = 1;
                goto L_003c10d8;
            }
        L_003c10d4:
            charge(ctx, 1);
            v1 = 0;
        L_003c10d8:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c10e4
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
            }
        L_003c1124:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003c0f78
            charge(ctx, 3);
            a0 = 1;
            if (v1 != a0) {
                // 0x003c0f84
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x003c0f8c
                    charge(ctx, 2);
                    goto L_003c1124;
                }
                // 0x003c0f94
                charge(ctx, 6);
                jal(ctx, 0x3C0F94u, gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFF;
                v0 = 4;
                if (v1 == v0) {
                    // 0x003c0fac
                    charge(ctx, 6);
                    a0 = 2444;
                    jal(ctx, 0x3C0FB0u, gen::fn_MT_Misc_BitChk_003951d0);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_003c0fd0;
                    }
                    // 0x003c0fc4
                    charge(ctx, 3);
                    v0 = si(-1);
                    // 0x003c1128 (the shared epilogue, written out on this path)
                    charge(ctx, 8);
                    ld(ra, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x80);
                    return;
                }
            L_003c0fd0:
                charge(ctx, 7);
                sw(zero, s0, kComuWorkWait);
                v0 = 2;
                sw(v0, s0, kComuWorkWaitLimit);
                v0 = 1;
                sw(v0, s0, kComuWorkPhase);
                goto L_003c1124;
            }
            // 0x003c0fec
            charge(ctx, 5);
            lw(v1, s0, kComuWorkWait);
            lw(v0, s0, kComuWorkWaitLimit);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003c1010
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s0, kComuWorkWait);
                a0 = 0;
            } else {
                // 0x003c1000
                charge(ctx, 4);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
            }
            // 0x003c101c
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_003c1124;
            }
            // 0x003c1024
            charge(ctx, 8);
            a0 = addiu(sp, 0x7C);
            a1 = addiu(sp, 0x78);
            a2 = addiu(sp, 0x74);
            jal(ctx, 0x3C1030u, gen::fn_sub_3C0DB0_003c0db0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c1044
                charge(ctx, 21);
                lw(s3, sp, 0x74);
                lw(s2, sp, 0x78);
                lw(s1, sp, 0x7C);
                a0 = addiu(sp, 0x50);
                a1 = 0;
                a2 = 28;
                jal(ctx, 0x3C105Cu, gen::fn_memset_00521408);
                sw(s1, sp, 0x5C);
                sw(s2, sp, 0x60);
                sw(s3, sp, 0x64);
                a0 = 3;
                a1 = addiu(sp, 0x50);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x3C1080u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                v0 = 2;
                sw(v0, s0, kComuWorkPhase);
                goto L_003c1124;
            }
            // 0x003c1098
            charge(ctx, 3);
            v0 = si(-1);
        }
    }
    // 0x003c1128 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003C1150 sub_3C1150 -- 424 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateSasoi] After the wait builds today's invitation list (sub_3C2630(0, 0, 0)); none ->
// finished. Then event 0x32C (2), wait idle, phase 4 finishes.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C115Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 4;
    if (v1 == v0) {
        // 0x003c12d4
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x003c1178
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x003c1284
            charge(ctx, 4);
            jal(ctx, 0x3C1284u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c1294
                charge(ctx, 5);
                jal(ctx, 0x3C1294u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c12b4;
                }
                // 0x003c12a8
                charge(ctx, 3);
                v1 = 1;
                goto L_003c12b8;
            }
        L_003c12b4:
            charge(ctx, 1);
            v1 = 0;
        L_003c12b8:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c12c4
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, kComuWorkPhase);
            }
        L_003c12e0:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003c1184
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x003c1234
                charge(ctx, 20);
                a0 = addiu(sp, 0x20);
                a1 = 0;
                a2 = 28;
                jal(ctx, 0x3C1240u, gen::fn_memset_00521408);
                v0 = 812;
                sw(v0, sp, 0x2C);
                v0 = 2;
                sw(v0, sp, 0x30);
                sw(zero, sp, 0x34);
                a0 = 3;
                a1 = addiu(sp, 0x20);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x3C126Cu, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
                goto L_003c12e0;
            }
            // 0x003c1190
            charge(ctx, 3);
            a0 = 1;
            if (v1 != a0) {
                // 0x003c119c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003c11ac
                    charge(ctx, 5);
                    sw(zero, s0, kComuWorkWait);
                    sw(v0, s0, kComuWorkWaitLimit);
                    sw(a0, s0, kComuWorkPhase);
                } else {
                    // 0x003c11a4
                    charge(ctx, 2);
                }
                goto L_003c12e0;
            }
            // 0x003c11c0
            charge(ctx, 5);
            lw(v1, s0, kComuWorkWait);
            lw(v0, s0, kComuWorkWaitLimit);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003c11e4
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s0, kComuWorkWait);
                a0 = 0;
            } else {
                // 0x003c11d4
                charge(ctx, 4);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
            }
            // 0x003c11f0
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_003c12e0;
            }
            // 0x003c11f8
            charge(ctx, 8);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            jal(ctx, 0x3C1204u, gen::fn_sub_3C2630_003c2630);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c1218
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, kComuWorkPhase);
                goto L_003c12e0;
            }
            // 0x003c1228
            charge(ctx, 3);
            v0 = si(-1);
        }
    }
    // 0x003c12e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C1300 sub_3C1300 -- 64 bytes; frame 0x10: ra sp+0x0
// [comuTimerStateKind3] The entry state of timer kind 3: clears the work words, next state sub_3C1150.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1300
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C1308u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    sw(zero, v0, kComuWorkPhase);
    sw(zero, v0, kComuWorkWait);
    sw(zero, v0, kComuWorkWaitLimit);
    sw(zero, v0, kComuWorkWord3);
    sw(zero, v0, kComuWorkWord4);
    sw(zero, v0, kComuWorkWord5);
    v0 = 0x3C0000;
    v0 = addiu(v0, 4432);  // &sub_3C1150
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C1340 sub_3C1340 -- 240 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateSeq2_6_3] Phase 0: sequence 2 with (6, 3, 2, 0); phase 1 finishes once idle.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1340
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C134Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 1;
    if (v1 != v0) {
        // 0x003c1368
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x003c1378
            charge(ctx, 21);
            a0 = addiu(sp, 0x20);
            a1 = 0;
            a2 = 28;
            jal(ctx, 0x3C1384u, gen::fn_memset_00521408);
            v0 = 6;
            sh(v0, sp, 0x20);
            v0 = 3;
            sh(v0, sp, 0x22);
            a0 = 2;
            sh(a0, sp, 0x24);
            sh(zero, sp, 0x28);
            a1 = addiu(sp, 0x20);
            a2 = 28;
            a3 = 0;
            jal(ctx, 0x3C13B4u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
            v0 = 1;
            sw(v0, s0, kComuWorkPhase);
        } else {
            // 0x003c1370
            charge(ctx, 2);
        }
        goto L_003c1418;
    }
    // 0x003c13cc
    charge(ctx, 4);
    jal(ctx, 0x3C13CCu, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
    if (v0 == 0) {
        // 0x003c13dc
        charge(ctx, 5);
        jal(ctx, 0x3C13DCu, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003c13fc;
        }
        // 0x003c13f0
        charge(ctx, 3);
        v1 = 1;
        goto L_003c1400;
    }
L_003c13fc:
    charge(ctx, 1);
    v1 = 0;
L_003c1400:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003c1418:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c140c
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003c141c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C1430 sub_3C1430 -- 16 bytes; leaf frame (no stack)
// [comuGetPendingRecord] Returns 0x95B750 (the record sub_3C1440 hands to sub_1728D0).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c1430
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18608);  // &0x95B750 kComuPending
}

// 0x003C1440 sub_3C1440 -- 388 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateNight] After the wait: next state sub_3C1340. Phase 2 (once idle): sub_38D6F0(0) == 0 ->
// sub_1728D0(0x95B750), next state sub_3BF370; otherwise sub_3C1340.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1440(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1440
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C144Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x003c14f8
        charge(ctx, 4);
        jal(ctx, 0x3C14F8u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
        if (v0 == 0) {
            // 0x003c1508
            charge(ctx, 5);
            jal(ctx, 0x3C1508u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
            v1 = si(-1);
            if (v0 != v1) {
                goto L_003c1528;
            }
            // 0x003c151c
            charge(ctx, 3);
            v1 = 1;
            goto L_003c152c;
        }
    L_003c1528:
        charge(ctx, 1);
        v1 = 0;
    L_003c152c:
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
        L_003c15ac:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003c1538
            charge(ctx, 5);
            a0 = 0;
            jal(ctx, 0x3C153Cu, gen::fn_sub_38D6F0_0038d6f0);
            if (v0 != 0) {
                // 0x003c1584
                charge(ctx, 10);
                sw(zero, s0, kComuWorkPhase);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
                sw(zero, s0, kComuWorkWord3);
                sw(zero, s0, kComuWorkWord4);
                sw(zero, s0, kComuWorkWord5);
                v0 = 0x3C0000;
                v0 = addiu(v0, 4928);  // &sub_3C1340
            } else {
                // 0x003c154c
                charge(ctx, 14);
                a0 = 0x960000;
                a0 = addiu(a0, -18608);  // &0x95B750 kComuPending
                jal(ctx, 0x3C1554u, gen::fn_sub_1728D0_001728d0);
                sw(zero, s0, kComuWorkPhase);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
                sw(zero, s0, kComuWorkWord3);
                sw(zero, s0, kComuWorkWord4);
                sw(zero, s0, kComuWorkWord5);
                v0 = 0x3C0000;
                v0 = addiu(v0, -3216);  // &sub_3BF370
            }
        }
    } else {
        // 0x003c1468
        charge(ctx, 3);
        a0 = 1;
        if (v1 != a0) {
            // 0x003c1474
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003c1484
                charge(ctx, 5);
                sw(zero, s0, kComuWorkWait);
                sw(v0, s0, kComuWorkWaitLimit);
                sw(a0, s0, kComuWorkPhase);
            } else {
                // 0x003c147c
                charge(ctx, 2);
            }
            goto L_003c15ac;
        }
        // 0x003c1498
        charge(ctx, 5);
        lw(v1, s0, kComuWorkWait);
        lw(v0, s0, kComuWorkWaitLimit);
        v0 = slt(v1, v0);
        if (v0 != 0) {
            // 0x003c14bc
            charge(ctx, 3);
            v0 = addiu(v1, 1);
            sw(v0, s0, kComuWorkWait);
            a0 = 0;
        } else {
            // 0x003c14ac
            charge(ctx, 4);
            sw(zero, s0, kComuWorkWait);
            sw(zero, s0, kComuWorkWaitLimit);
        }
        // 0x003c14c8
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_003c15ac;
        }
        // 0x003c14d0
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, 4928);  // &sub_3C1340
    }
    // 0x003c15b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C15D0 sub_3C15D0 -- 572 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuTimerStateInvite] Copies 56 bytes from sub_1717B0() + 0x1E4 to work +0x20 (7 x 8 bytes), the social
// link is its first byte. Phase 0 sets phase 3 directly (retail: phases 1 and 2 are not reached from 0): phase 3 returns
// sub_3BF370. Phase 1: invitation kind sub_3C40F0(link) 1 -> event 0x335, 0 or 2 -> event 0x334 (word 1, the link).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C15D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c15d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C15E0u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    jal(ctx, 0x3C15ECu, gen::fn_sub_1717B0_001717b0);
    a2 = addiu(v0, 484);
    a1 = addiu(s0, 32);
    a0 = 7;
    for (;;) {
        // 0x003c1600
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
    // 0x003c1624
    charge(ctx, 5);
    lbu(s1, s0, 32);
    lw(a0, s0, kComuWorkPhase);
    v1 = 3;
    if (a0 == v1) {
        // 0x003c17c8
        charge(ctx, 10);
        sw(zero, s0, kComuWorkPhase);
        sw(zero, s0, kComuWorkWait);
        sw(zero, s0, kComuWorkWaitLimit);
        sw(zero, s0, kComuWorkWord3);
        sw(zero, s0, kComuWorkWord4);
        sw(zero, s0, kComuWorkWord5);
        v0 = 0x3C0000;
        v0 = addiu(v0, -3216);  // &sub_3BF370
    } else {
        // 0x003c1638
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x003c1778
            charge(ctx, 4);
            jal(ctx, 0x3C1778u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
            if (v0 == 0) {
                // 0x003c1788
                charge(ctx, 5);
                jal(ctx, 0x3C1788u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
                v1 = si(-1);
                if (v0 != v1) {
                    goto L_003c17a8;
                }
                // 0x003c179c
                charge(ctx, 3);
                v1 = 1;
                goto L_003c17ac;
            }
        L_003c17a8:
            charge(ctx, 1);
            v1 = 0;
        L_003c17ac:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c17b8
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c1644
            charge(ctx, 3);
            a1 = 1;
            if (a0 == a1) {
                // 0x003c1674
                charge(ctx, 5);
                lw(v1, s0, kComuWorkWait);
                lw(v0, s0, kComuWorkWaitLimit);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    // 0x003c1698
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, kComuWorkWait);
                    a1 = 0;
                } else {
                    // 0x003c1688
                    charge(ctx, 4);
                    sw(zero, s0, kComuWorkWait);
                    sw(zero, s0, kComuWorkWaitLimit);
                }
                // 0x003c16a4
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x003c16ac
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x3C16B0u, gen::fn_sub_3C40F0_003c40f0);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x003c1728
                        charge(ctx, 16);
                        a0 = addiu(sp, 0x30);
                        a1 = 0;
                        a2 = 28;
                        jal(ctx, 0x3C1734u, gen::fn_memset_00521408);
                        v0 = 821;
                        sw(v0, sp, 0x3C);
                        v0 = 1;
                        sw(v0, sp, 0x40);
                        sw(s1, sp, 0x44);
                        a0 = 3;
                        a1 = addiu(sp, 0x30);
                        a2 = 28;
                        a3 = 0;
                        jal(ctx, 0x3C1760u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                    } else {
                        // 0x003c16c4
                        charge(ctx, 3);
                        v1 = 2;
                        if (v0 != v1) {
                            // 0x003c16d0
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_003c16e0;
                            }
                            // 0x003c16d8
                            charge(ctx, 2);
                            goto L_003c1768;
                        }
                    L_003c16e0:
                        charge(ctx, 18);
                        a0 = addiu(sp, 0x50);
                        a1 = 0;
                        a2 = 28;
                        jal(ctx, 0x3C16ECu, gen::fn_memset_00521408);
                        v0 = 820;
                        sw(v0, sp, 0x5C);
                        v0 = 1;
                        sw(v0, sp, 0x60);
                        sw(s1, sp, 0x64);
                        a0 = 3;
                        a1 = addiu(sp, 0x50);
                        a2 = 28;
                        a3 = 0;
                        jal(ctx, 0x3C1718u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                    }
                L_003c1768:
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s0, kComuWorkPhase);
                }
            } else {
                // 0x003c1650
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x003c1660
                    charge(ctx, 5);
                    sw(zero, s0, kComuWorkWait);
                    sw(v0, s0, kComuWorkWaitLimit);
                    sw(v1, s0, kComuWorkPhase);
                } else {
                    // 0x003c1658
                    charge(ctx, 2);
                }
            }
        }
        // 0x003c17f0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003c17f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003C1810 sub_3C1810 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateKind5] Phase 0: sub_1729A0() == 1 -> next state sub_3C15D0, else sub_3C1440.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1810
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C181Cu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v0, v0, 0);
    if (v0 == 0) {
        // 0x003c183c
        charge(ctx, 5);
        jal(ctx, 0x3C183Cu, gen::fn_sub_1729A0_001729a0);
        v1 = 1;
        if (v0 != v1) {
            // 0x003c1878
            charge(ctx, 10);
            sw(zero, s0, kComuWorkPhase);
            sw(zero, s0, kComuWorkWait);
            sw(zero, s0, kComuWorkWaitLimit);
            sw(zero, s0, kComuWorkWord3);
            sw(zero, s0, kComuWorkWord4);
            sw(zero, s0, kComuWorkWord5);
            v0 = 0x3C0000;
            v0 = addiu(v0, 5184);  // &sub_3C1440
        } else {
            // 0x003c1850
            charge(ctx, 10);
            sw(zero, s0, kComuWorkPhase);
            sw(zero, s0, kComuWorkWait);
            sw(zero, s0, kComuWorkWaitLimit);
            sw(zero, s0, kComuWorkWord3);
            sw(zero, s0, kComuWorkWord4);
            sw(zero, s0, kComuWorkWord5);
            v0 = 0x3C0000;
            v0 = addiu(v0, 5584);  // &sub_3C15D0
        }
    } else {
        // 0x003c1834
        charge(ctx, 2);
        // 0x003c18a0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x003c18a4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C18C0 sub_3C18C0 -- 428 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// [comuTimerStateKind6] After the wait: flag 0xBD4 set -> sequence 2 (7, 1, 5, 0), else (7, 2, 0, 0); finishes
// once idle.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C18C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c18c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C18CCu, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    s0 = v0;
    lw(v1, v0, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x003c18e8
        charge(ctx, 3);
        a0 = 1;
        if (v1 == a0) {
            // 0x003c1918
            charge(ctx, 5);
            lw(v1, s0, kComuWorkWait);
            lw(v0, s0, kComuWorkWaitLimit);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003c193c
                charge(ctx, 3);
                v0 = addiu(v1, 1);
                sw(v0, s0, kComuWorkWait);
                a0 = 0;
            } else {
                // 0x003c192c
                charge(ctx, 4);
                sw(zero, s0, kComuWorkWait);
                sw(zero, s0, kComuWorkWaitLimit);
            }
            // 0x003c1948
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x003c1950
                charge(ctx, 6);
                a0 = 3028;
                jal(ctx, 0x3C1954u, gen::fn_MT_Misc_BitChk_003951d0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003c19b8
                    charge(ctx, 16);
                    a0 = addiu(sp, 0x20);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3C19C4u, gen::fn_memset_00521408);
                    v0 = 7;
                    sh(v0, sp, 0x20);
                    a0 = 2;
                    sh(a0, sp, 0x22);
                    sh(zero, sp, 0x24);
                    sh(zero, sp, 0x28);
                    a1 = addiu(sp, 0x20);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3C19F0u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                } else {
                    // 0x003c1968
                    charge(ctx, 20);
                    a0 = addiu(sp, 0x40);
                    a1 = 0;
                    a2 = 28;
                    jal(ctx, 0x3C1974u, gen::fn_memset_00521408);
                    v0 = 7;
                    sh(v0, sp, 0x40);
                    v0 = 1;
                    sh(v0, sp, 0x42);
                    v0 = 5;
                    sh(v0, sp, 0x44);
                    sh(zero, sp, 0x48);
                    a0 = 2;
                    a1 = addiu(sp, 0x40);
                    a2 = 28;
                    a3 = 0;
                    jal(ctx, 0x3C19A8u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
                }
                // 0x003c19f8
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, kComuWorkPhase);
            }
        } else {
            // 0x003c18f4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003c1904
                charge(ctx, 5);
                sw(zero, s0, kComuWorkWait);
                sw(v0, s0, kComuWorkWaitLimit);
                sw(a0, s0, kComuWorkPhase);
            } else {
                // 0x003c18fc
                charge(ctx, 2);
            }
        }
        goto L_003c1a54;
    }
    // 0x003c1a08
    charge(ctx, 4);
    jal(ctx, 0x3C1A08u, gen::fn_sub_27C2B0_0027c2b0);  // the sequence manager's current sequence id
    if (v0 == 0) {
        // 0x003c1a18
        charge(ctx, 5);
        jal(ctx, 0x3C1A18u, gen::fn_sub_27C330_0027c330);  // its next sequence id (-1: none)
        v1 = si(-1);
        if (v0 != v1) {
            goto L_003c1a38;
        }
        // 0x003c1a2c
        charge(ctx, 3);
        v1 = 1;
        goto L_003c1a3c;
    }
L_003c1a38:
    charge(ctx, 1);
    v1 = 0;
L_003c1a3c:
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
    L_003c1a54:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003c1a48
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003c1a58 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C1A70 sub_3C1A70 -- 52 bytes; frame 0x10: ra sp+0x0
// [comuTimerDestroy] The destroy callback of "comuTimerProcess": RwFree(work).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C1A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1a70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C1A78u, gen::fn_kwlnTaskGetWorkData_00195540);  // the task's work block
    a0 = v0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x3C1A8Cu, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C1AB0 comu_CreateComuTimerProcessTask -- 624 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// comu_CreateComuTimerProcessTask(parent, kind): picks the entry state by kind 1..7 (jump table 0x7BB370,
// day rules through sub_17E050(100, month, day) and the weekday) and creates "comuTimerProcess" (priority 14) with an
// 0x58-byte RwMalloc'd, zeroed work block; returns the task (also stored at work +0x18), 0 when no state applies.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void comu_CreateComuTimerProcessTask(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c1ab0
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
    s2 = 0;
    jal(ctx, 0x3C1AD8u, gen::fn_clndGetCurrentMonth_0017d920);
    s1 = v0;
    jal(ctx, 0x3C1AE4u, gen::fn_clndGetCurrentDay_0017da40);
    s0 = v0;
    at = sltiu(s3, 9);
    if (at != 0) {
        // 0x003c1afc
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -19600);  // &0x7BB370
        v0 = sll(s3, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3C1B18u:  // table[1]
            // 0x003c1b18
            charge(ctx, 8);
            a0 = 100;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C1B24u, gen::fn_sub_17E050_0017e050);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c1b48
                charge(ctx, 4);
                s2 = 0x3C0000;
                s2 = addiu(s2, 3024);  // &sub_3C0BD0
            } else {
                // 0x003c1b38
                charge(ctx, 4);
                s2 = 0x3C0000;
                s2 = addiu(s2, -192);  // &sub_3BFF40
            }
            break;
        case 0x3C1B58u:  // table[2]
            // 0x003c1b58
            charge(ctx, 8);
            a0 = 100;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C1B64u, gen::fn_sub_17E050_0017e050);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c1b78
                charge(ctx, 4);
                s2 = 0x3C0000;
                s2 = addiu(s2, 3872);  // &sub_3C0F20
            }
            break;
        case 0x3C1B88u:  // table[3]
            // 0x003c1b88
            charge(ctx, 7);
            a0 = 100;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C1B94u, gen::fn_sub_17E050_0017e050);
            if (v0 == 0) {
                // 0x003c1ba4
                charge(ctx, 4);
                s2 = 0x3C0000;
                s2 = addiu(s2, 4864);  // &sub_3C1300
            }
            break;
        case 0x3C1BB4u:  // table[4]
            // 0x003c1bb4
            charge(ctx, 8);
            a0 = 100;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C1BC0u, gen::fn_sub_17E050_0017e050);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c1bec
                charge(ctx, 5);
                jal(ctx, 0x3C1BECu, gen::fn_clndGetCurrentWeekDay_0017db00);
                v1 = 6;
                if (v0 != v1) {
                    // 0x003c1c00
                    charge(ctx, 7);
                    a0 = 100;
                    a1 = s1;
                    a2 = s0;
                    jal(ctx, 0x3C1C0Cu, gen::fn_sub_17E050_0017e050);
                    if (v0 == 0) {
                        // 0x003c1c1c
                        charge(ctx, 4);
                        s2 = 0x3C0000;
                        s2 = addiu(s2, 3872);  // &sub_3C0F20
                    }
                }
            } else {
                // 0x003c1bd4
                charge(ctx, 6);
                jal(ctx, 0x3C1BD4u, gen::fn_sub_3BEC50_003bec50);
                s2 = 0x3C0000;
                s2 = addiu(s2, 3360);  // &sub_3C0D20
            }
            break;
        case 0x3C1C2Cu:  // table[5]
            // 0x003c1c2c
            charge(ctx, 7);
            a0 = 100;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x3C1C38u, gen::fn_sub_17E050_0017e050);
            if (v0 == 0) {
                // 0x003c1c48
                charge(ctx, 4);
                s2 = 0x3C0000;
                s2 = addiu(s2, 6160);  // &sub_3C1810
            }
            break;
        case 0x3C1C58u:  // table[6]
            // 0x003c1c58
            charge(ctx, 4);
            s2 = 0x3C0000;
            s2 = addiu(s2, 6336);  // &sub_3C18C0
            break;
        case 0x3C1C68u:  // table[7]
            // 0x003c1c68
            charge(ctx, 2);
            s2 = 0x3C0000;
            s2 = addiu(s2, -2544);  // &sub_3BF610
            break;
        case 0x3C1C70u:  // table[0, 8]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x003c1c70
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x003c1c84
        charge(ctx, 9);
        a0 = 88;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 RwMalloc slot
        jalr(ctx, 0x3C1C94u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x003c1ca8
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 12944);  // "comuTimerSequence.c"
            a1 = 2102;
            jal(ctx, 0x3C1CB4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
        }
        // 0x003c1cbc
        charge(ctx, 16);
        a0 = s0;
        a1 = 0;
        a2 = 88;
        jal(ctx, 0x3C1CC8u, gen::fn_memset_00521408);
        a0 = s4;
        a1 = 0x6A0000;
        a1 = addiu(a1, 12976);  // "comuTimerProcess"
        a2 = 14;
        a3 = s2;
        t0 = 0x3C0000;
        t0 = addiu(t0, 6768);  // &sub_3C1A70
        t1 = s0;
        jal(ctx, 0x3C1CF0u, gen::fn_kwlnTaskCreate_00194b20);
        sw(v0, s0, 24);
    } else {
        // 0x003c1c78
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c1cfc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C1D20 comu_UpdateRevMailSeqTask -- 1476 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// comu_UpdateRevMailSeqTask: the "RevMailSeq" update (22 phases, jump table at 0x7BB398): loads
// event/sys/revmail.pak, binds revmail.bmd, then for each reversed link shows the mail, the arcana name, the card effect
// and marks it read (sub_171C40).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void comu_UpdateRevMailSeqTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003c1d20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    s1 = addiu(s0, 148);
    lw(v0, s0, 0);
    at = sltiu(v0, 22);
    if (at != 0) {
        // 0x003c1d4c
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -19552);  // &0x7BB3A0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3C1D68u:  // table[0]
            // 0x003c1d68
            charge(ctx, 6);
            a0 = addiu(s0, 24);
            jal(ctx, 0x3C1D6Cu, gen::fn_sub_172D70_00172d70);
            sw(v0, s0, 16);
            if (v0 != 0) {
                // 0x003c1d90
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 0);
            } else {
                // 0x003c1d80
                charge(ctx, 4);
                v0 = 21;
                sw(v0, s0, 0);
            }
        L_003c22b8:
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x3C22BCu, gen::fn_sub_39F410_0039f410);
            v0 = 0;
            break;
        case 0x3C1DA0u:  // table[1]
            // 0x003c1da0
            charge(ctx, 10);
            a0 = 0x6A0000;
            a0 = addiu(a0, 13008);  // "event/sys/revmail.pak"
            a1 = 1;
            jal(ctx, 0x3C1DACu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 180);
            v0 = 2;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C1DC8u:  // table[2]
            // 0x003c1dc8
            charge(ctx, 6);
            lw(a0, s0, 180);
            jal(ctx, 0x3C1DCCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c1de0
                charge(ctx, 13);
                a0 = 0x6A0000;
                a0 = addiu(a0, 13040);  // "event/sys/revmail.bmd"
                a1 = addiu(sp, 0x4C);
                jal(ctx, 0x3C1DECu, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x3C1DFCu, gen::fn_sub_39EC70_0039ec70);
                v0 = 3;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C1E14u:  // table[3]
            // 0x003c1e14
            charge(ctx, 5);
            sw(zero, s0, 20);
            v0 = 4;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C1E28u:  // table[4]
            // 0x003c1e28
            charge(ctx, 10);
            a0 = s1;
            a1 = 3;
            a2 = si(-1);
            a3 = a2;
            jal(ctx, 0x3C1E38u, gen::fn_sub_39F210_0039f210);
            v0 = 5;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C1E50u:  // table[5]
            // 0x003c1e50
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x3C1E54u, gen::fn_sub_39F6E0_0039f6e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c1e68
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C1E78u:  // table[6]
            // 0x003c1e78
            charge(ctx, 5);
            lw(v1, s0, 20);
            lw(v0, s0, 16);
            v0 = slt(v1, v0);
            if (v0 != 0) {
                // 0x003c1e9c
                charge(ctx, 9);
                v0 = sll(v1, 2);
                v0 = addu(v0, s0);
                lw(a0, v0, 24);
                jal(ctx, 0x3C1EA8u, gen::fn_sub_3BDFC0_003bdfc0);
                v0 = 7;
                sw(v0, s0, 0);
            } else {
                // 0x003c1e8c
                charge(ctx, 4);
                v0 = 21;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C1EC0u:  // table[7]
            // 0x003c1ec0
            charge(ctx, 16);
            lhu(a0, s0, 12);
            a1 = 17;
            jal(ctx, 0x3C1EC8u, gen::fn_sub_3BB010_003bb010);
            a0 = 0;
            a1 = 101;
            a2 = 3;
            jal(ctx, 0x3C1EDCu, gen::fn_sub_3952D0_003952d0);
            sw(zero, s0, 4);
            v0 = 50;
            sw(v0, s0, 8);
            v0 = 8;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C1F00u:  // table[8]
            // 0x003c1f00
            charge(ctx, 5);
            lw(v1, s0, 8);
            lw(v0, s0, 4);
            at = slt(v0, v1);
            if (at != 0) {
                // 0x003c1f20
                charge(ctx, 3);
                v0 = addiu(v0, 1);
                sw(v0, s0, 4);
                v0 = 0;
            } else {
                // 0x003c1f14
                charge(ctx, 3);
                v0 = 1;
            }
            // 0x003c1f2c
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003c1f34
                charge(ctx, 24);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lhu(a0, s0, 12);
                a1 = 0;
                a2 = 19;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x3C1F54u, gen::fn_sub_3B91C0_003b91c0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lhu(a0, s0, 12);
                a1 = 0;
                a2 = 20;
                a3 = 0;
                t0 = 1;
                t1 = 0;
                jal(ctx, 0x3C1F7Cu, gen::fn_sub_3B9320_003b9320);
                v0 = 9;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C1F94u:  // table[9]
            // 0x003c1f94
            charge(ctx, 37);
            lw(v0, s0, 20);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(a0, v0, 24);
            jal(ctx, 0x3C1FA4u, gen::fn_sub_3C3FE0_003c3fe0);
            a0 = s1;
            a1 = 0;
            a2 = v0;
            jal(ctx, 0x3C1FB8u, gen::fn_sub_39EF30_0039ef30);
            lw(v0, s0, 20);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lh(a0, v0, 24);
            jal(ctx, 0x3C1FD0u, gen::fn_sub_16DF30_0016df30);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            a0 = v0 & 0xFF;
            jal(ctx, 0x3C1FE4u, gen::fn_datGetArcanaName_0030bbb0);
            a0 = s1;
            a1 = 1;
            a2 = v0;
            jal(ctx, 0x3C1FF8u, gen::fn_sub_39EF30_0039ef30);
            a0 = s1;
            a1 = 0;
            a2 = si(-1);
            a3 = a2;
            jal(ctx, 0x3C2010u, gen::fn_sub_39F210_0039f210);
            v0 = 10;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C2028u:  // table[10]
            // 0x003c2028
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x3C202Cu, gen::fn_sub_39F6E0_0039f6e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c2040
                charge(ctx, 4);
                v0 = 11;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C2050u:  // table[11]
            // 0x003c2050
            charge(ctx, 14);
            lw(v0, s0, 20);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(v0, v0, 24);
            a1 = addiu(v0, 5);
            a0 = s1;
            a2 = si(-1);
            a3 = a2;
            jal(ctx, 0x3C2070u, gen::fn_sub_39F210_0039f210);
            v0 = 12;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C2088u:  // table[12]
            // 0x003c2088
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x3C208Cu, gen::fn_sub_39F6E0_0039f6e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c20a0
                charge(ctx, 11);
                lw(v0, s0, 20);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                lw(s2, v0, 24);
                a0 = s2;
                jal(ctx, 0x3C20B4u, gen::fn_sub_171AC0_00171ac0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (i64(v0) <= 0) {
                    // 0x003c20dc
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x3C20E0u, gen::fn_sub_1717C0_001717c0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x003c20f4
                        charge(ctx, 6);
                        a0 = s2;
                        jal(ctx, 0x3C20F8u, gen::fn_sub_172160_00172160);
                        v1 = 1;
                        if (v0 == v1) {
                            goto L_003c210c;
                        }
                        // 0x003c211c
                        charge(ctx, 4);
                        v0 = 13;
                        sw(v0, s0, 0);
                        goto L_003c22b8;
                    }
                L_003c210c:
                    charge(ctx, 4);
                    v0 = 19;
                    sw(v0, s0, 0);
                } else {
                    // 0x003c20cc
                    charge(ctx, 4);
                    v0 = 19;
                    sw(v0, s0, 0);
                }
            }
            goto L_003c22b8;
        case 0x3C212Cu:  // table[13]
            // 0x003c212c
            charge(ctx, 10);
            a0 = s1;
            a1 = 1;
            a2 = si(-1);
            a3 = a2;
            jal(ctx, 0x3C213Cu, gen::fn_sub_39F210_0039f210);
            v0 = 14;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C2154u:  // table[14]
            // 0x003c2154
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x3C2158u, gen::fn_sub_39F6E0_0039f6e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003c216c
                charge(ctx, 4);
                v0 = 15;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C217Cu:  // table[15]
            // 0x003c217c
            charge(ctx, 13);
            lw(v0, s0, 20);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(a1, v0, 24);
            a2 = 2;
            lhu(a3, s0, 12);
            jal(ctx, 0x3C2194u, gen::fn_sub_3A2090_003a2090);
            sw(v0, s0, 144);
            v0 = 16;
            sw(v0, s0, 0);
            goto L_003c22b8;
        case 0x3C21B0u:  // table[16]
            // 0x003c21b0
            charge(ctx, 5);
            lw(a0, s0, 144);
            jal(ctx, 0x3C21B4u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x003c21c4
                charge(ctx, 11);
                lw(v0, s0, 20);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                lw(a0, v0, 24);
                a1 = 1;
                jal(ctx, 0x3C21D8u, gen::fn_sub_171C40_00171c40);
                v0 = 19;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C21F0u:  // table[19]
            // 0x003c21f0
            charge(ctx, 27);
            v0 = 20;
            sw(v0, s0, 0);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lhu(a0, s0, 12);
            a1 = 0;
            a2 = 21;
            a3 = 0;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x3C2218u, gen::fn_sub_3B91C0_003b91c0);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lhu(a0, s0, 12);
            a1 = 0;
            a2 = 0;
            a3 = 0;
            t0 = 1;
            t1 = 0;
            jal(ctx, 0x3C2240u, gen::fn_sub_3B9320_003b9320);
            sw(zero, s0, 4);
            v0 = 30;
            sw(v0, s0, 8);
            goto L_003c22b8;
        case 0x3C225Cu:  // table[20]
            // 0x003c225c
            charge(ctx, 5);
            lw(v1, s0, 8);
            lw(v0, s0, 4);
            at = slt(v0, v1);
            if (at != 0) {
                // 0x003c227c
                charge(ctx, 3);
                v0 = addiu(v0, 1);
                sw(v0, s0, 4);
                v0 = 0;
            } else {
                // 0x003c2270
                charge(ctx, 3);
                v0 = 1;
            }
            // 0x003c2288
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003c2290
                charge(ctx, 7);
                lw(v0, s0, 20);
                v0 = addiu(v0, 1);
                sw(v0, s0, 20);
                v0 = 6;
                sw(v0, s0, 0);
            }
            goto L_003c22b8;
        case 0x3C22ACu:  // table[21]
            // 0x003c22ac
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x3C22B8u:  // table[17, 18]
            goto L_003c22b8;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x003c22c8 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    goto L_003c22b8;
}

// 0x003C22F0 sub_3C22F0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuRevMailDestroy] The destroy callback of "RevMailSeq": releases the file node, the message slot and
// the work block.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C22F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c22f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 180);
    if (a0 != 0) {
        // 0x003c230c
        charge(ctx, 3);
        jal(ctx, 0x3C230Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 180);
    }
    // 0x003c2318
    charge(ctx, 13);
    a0 = addiu(s0, 148);
    jal(ctx, 0x3C231Cu, gen::fn_sub_39EE80_0039ee80);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x3C2330u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C2350 comu_CreateRevMailSeqTask -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// comu_CreateRevMailSeqTask(parent, arg): an 0xB8-byte zeroed work block (+12 = arg), task "RevMailSeq"
// (priority 16).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void comu_CreateRevMailSeqTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2350
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 184;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 RwMalloc slot
    jalr(ctx, 0x3C237Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 184;
    jal(ctx, 0x3C2394u, gen::fn_memset_00521408);
    sh(s1, s0, 12);
    a0 = s2;
    a1 = 0x6A0000;
    a1 = addiu(a1, 13064);  // "RevMailSeq"
    a2 = 16;
    a3 = 0x3C0000;
    a3 = addiu(a3, 7456);  // &comu_UpdateRevMailSeqTask
    t0 = 0x3C0000;
    t0 = addiu(t0, 8944);  // &sub_3C22F0
    t1 = s0;
    jal(ctx, 0x3C23C4u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C23F0 sub_3C23F0 -- 380 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuIsUnavailable] Whether an availability row of the comu data (+0x628, 5-byte rows {link, month,
// day, end month, end day}, count +0x62C) for `link` matches the date (month $a1, day $a2): end month 0xFF with a month
// -> sub_3BF200(month, day, row month, row day); both 0xFF -> sub_3BF200(month, day, 0xFF, row day); else the range
// test clndIsDateInRangeFromDate. 1 on the first match, else 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C23F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c23f0
    enter(ctx, 20);  // entry check point + this block's cycles
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
    jal(ctx, 0x3C241Cu, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    lw(s1, v0, kComuAvailRows);
    jal(ctx, 0x3C2428u, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    lw(s0, v0, kComuAvailCount);
    s2 = 0;
    for (;;) {
        // 0x003c2534
        charge(ctx, 3);
        v0 = slt(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c2440
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(v0, s2);
        v1 = addu(s1, v0);
        lbu(v0, v1, 0);
        if (s5 == v0) {
            // 0x003c2458
            charge(ctx, 4);
            lbu(t0, v1, 3);
            v0 = 255;
            if (t0 == v0) {
                // 0x003c2468
                charge(ctx, 3);
                lbu(a2, v1, 1);
                if (a2 == v0) {
                    goto L_003c24a0;
                }
                // 0x003c2474
                charge(ctx, 8);
                lbu(a3, v1, 2);
                a0 = s4;
                a1 = s3;
                jal(ctx, 0x3C2480u, gen::fn_sub_3BF200_003bf200);
                v1 = 1;
                if (v0 != v1) {
                    goto L_003c2530;
                }
                goto L_003c2494_5;
            }
        L_003c24a0:
            charge(ctx, 3);
            v0 = 255;
            if (t0 == v0) {
                // 0x003c24ac
                charge(ctx, 3);
                lbu(a2, v1, 1);
                if (a2 != v0) {
                    goto L_003c24f0;
                }
                // 0x003c24b8
                charge(ctx, 11);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = addu(s1, v0);
                lbu(a3, v0, 2);
                a0 = s4;
                a1 = s3;
                jal(ctx, 0x3C24D0u, gen::fn_sub_3BF200_003bf200);
                v1 = 1;
                if (v0 != v1) {
                    goto L_003c2530;
                }
                goto L_003c24e4_9;
            }
        L_003c24f0:
            charge(ctx, 13);
            v0 = sll(s2, 2);
            v0 = addu(v0, s2);
            v0 = addu(s1, v0);
            lbu(a2, v0, 1);
            lbu(a3, v0, 2);
            lbu(t1, v0, 4);
            a0 = s4;
            a1 = s3;
            jal(ctx, 0x3C2510u, gen::fn_sub_17E520_0017e520);
            v1 = 1;
            if (v0 != v1) {
                goto L_003c2530;
            }
            goto L_003c2524_11;
        }
    L_003c2530:
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x003c2540
    charge(ctx, 1);
    v0 = 0;
    // 0x003c2544 (the shared epilogue, written out on this path)
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
L_003c2494_5:
    charge(ctx, 3);
    v0 = v1;
    // 0x003c2544 (the shared epilogue, written out on this path)
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
L_003c24e4_9:
    charge(ctx, 3);
    v0 = v1;
    // 0x003c2544 (the shared epilogue, written out on this path)
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
L_003c2524_11:
    charge(ctx, 3);
    v0 = v1;
    // 0x003c2544 (the shared epilogue, written out on this path)
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

// 0x003C2570 sub_3C2570 -- 180 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuSasoiTier] sub_1720C0(link, &tmp) as a tier: < 2 -> 0, < 3 -> 1, < 4 -> 2, else 3 (sub_172A50(link)
// asserted, comuSasoi.c line 0x104).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2570(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2570
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x3C2588u, gen::fn_sub_1720C0_001720c0);
    s0 = v0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C259Cu, gen::fn_sub_172A50_00172a50);
    if (v0 == 0) {
        // 0x003c25ac
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 13080);  // "comuSasoi.c"
        a1 = 260;
        jal(ctx, 0x3C25B8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    }
    // 0x003c25c0
    charge(ctx, 3);
    at = slti(s0, 2);
    if (at == 0) {
        // 0x003c25d8
        charge(ctx, 3);
        at = slti(s0, 3);
        if (at == 0) {
            // 0x003c25f0
            charge(ctx, 3);
            at = slti(s0, 4);
            if (at == 0) {
                // 0x003c2608
                charge(ctx, 1);
                v0 = 3;
            } else {
                // 0x003c25fc
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x003c25e4
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x003c25cc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c260c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C2630 sub_3C2630 -- 312 bytes; frame 0xE0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuBuildSasoiList] Clears the invitation list 0x95B7E0 (0x698 bytes), stores $a0 at 0x95BE74, collects
// today's eligible links (sub_3C28A0 with the excluded list $a1 / count $a2) and fills one 56-byte entry per link
// through sub_3BE8E0 (asserted). Returns 1 when any.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2630
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    sw(zero, sp, 0xDC);
    jal(ctx, 0x3C265Cu, gen::fn_clndGetCurrentMonth_0017d920);
    s1 = v0;
    jal(ctx, 0x3C2668u, gen::fn_clndGetCurrentDay_0017da40);
    s0 = v0;
    a0 = 0x960000;
    a0 = addiu(a0, -18464);  // &0x95B7E0 kComuSasoiList
    a1 = 0;
    a2 = 1688;
    jal(ctx, 0x3C2684u, gen::fn_memset_00521408);
    v0 = 0x960000;
    sw(s4, v0, -16780);  // 0x95BE74 kComuSasoiOwner
    a0 = s1;
    a1 = s0;
    a2 = s3;
    a3 = s2;
    t0 = addiu(sp, 0x60);
    t1 = addiu(sp, 0xDC);
    jal(ctx, 0x3C26ACu, gen::fn_sub_3C28A0_003c28a0);
    if (v0 != 0) {
        // 0x003c26c8
        charge(ctx, 6);
        lw(v1, sp, 0xDC);
        v0 = 0x960000;
        sw(v1, v0, -18464);  // 0x95B7E0 kComuSasoiList count
        s0 = 0;
        for (;;) {
            // 0x003c2730
            charge(ctx, 4);
            lw(v0, sp, 0xDC);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c26e0
            charge(ctx, 14);
            v0 = sll(s0, 2);
            a0 = addu(v0, sp);
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 3);
            v0 = 0x960000;
            v0 = addiu(v0, -18464);  // &0x95B7E0 kComuSasoiList
            v0 = addu(v0, v1);
            lw(a0, a0, 96);
            a1 = addiu(v0, 4);
            jal(ctx, 0x3C2708u, gen::fn_sub_3BE8E0_003be8e0);
            if (v0 == 0) {
                // 0x003c2718
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 13080);  // "comuSasoi.c"
                a1 = 842;
                jal(ctx, 0x3C2724u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
            }
            // 0x003c272c
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x003c2740
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x003c26bc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c2744 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x003C2770 sub_3C2770 -- 16 bytes; leaf frame (no stack)
// [comuGetSasoiList] Returns 0x95B7E0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c2770
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -18464);  // &0x95B7E0 kComuSasoiList
}

// 0x003C2780 sub_3C2780 -- 284 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuFindSasoiRow] The invitation row (+0x674, 12-byte rows, count +0x678) of `link` whose rank range
// [+1, +2] holds datGetSocialLinkLevel(link); asserts the link is started; no row asserts (line 0x3CD) and returns 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2780(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2780
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    jal(ctx, 0x3C27A0u, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    lw(s1, v0, kComuSasoiRows);
    jal(ctx, 0x3C27ACu, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    lw(s0, v0, kComuSasoiCount);
    s3 = 0;
    for (;;) {
        // 0x003c2854
        charge(ctx, 3);
        v0 = slt(s3, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c27c4
        charge(ctx, 7);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        s2 = addu(s1, v0);
        lbu(v0, s2, 0);
        if (v0 == s4) {
            // 0x003c27e0
            charge(ctx, 6);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3C27E8u, gen::fn_sub_16E100_0016e100);
            if (v0 == 0) {
                // 0x003c27f8
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 13080);  // "comuSasoi.c"
                a1 = 961;
                jal(ctx, 0x3C2804u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
            }
            // 0x003c280c
            charge(ctx, 10);
            a0 = dsll32(s4, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3C2814u, gen::fn_sub_16DBA0_0016dba0);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            lbu(v0, s2, 1);
            at = slt(v1, v0);
            if (at != 0) {
                goto L_003c2850;
            }
            // 0x003c2834
            charge(ctx, 4);
            lbu(v0, s2, 2);
            v0 = slt(v0, v1);
            if (v0 != 0) {
                goto L_003c2850;
            }
            goto L_003c2844_6;
        }
    L_003c2850:
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x003c2860
    charge(ctx, 6);
    a0 = 0x6A0000;
    a0 = addiu(a0, 13080);  // "comuSasoi.c"
    a1 = 973;
    jal(ctx, 0x3C286Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    v0 = 0;
    // 0x003c2878 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_003c2844_6:
    charge(ctx, 3);
    v0 = s2;
    // 0x003c2878 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003C28A0 sub_3C28A0 -- 516 bytes; frame 0x110: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuCollectSasoi] For links 0..29: started, rank below 10, an invitation kind, not sub_1717C0 /
// sub_172160, not in the excluded list ($a2, $a3 entries), not unavailable today (sub_3C23F0), sub_172660 nonzero and
// flag 0x990 + link clear -> appended to a frame list; copies it to $a4 and the count to *$a5; returns 1 when any.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C28A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c28a0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
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
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s6 = t0;
    s7 = t1;
    s0 = 0;
    s1 = 0;
    for (;;) {
        // 0x003c2a1c
        charge(ctx, 3);
        v0 = slti(s1, 30);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c28f0
        charge(ctx, 6);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3C28F8u, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x003c2908
            charge(ctx, 9);
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3C2910u, gen::fn_sub_16DBA0_0016dba0);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            v0 = 10;
            if (v1 != v0) {
                // 0x003c292c
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x3C2930u, gen::fn_sub_3C40F0_003c40f0);
                if (v0 != 0) {
                    // 0x003c2940
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x3C2944u, gen::fn_sub_1717C0_001717c0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x003c2958
                        charge(ctx, 6);
                        a0 = s1;
                        jal(ctx, 0x3C295Cu, gen::fn_sub_172160_00172160);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x003c2970
                            charge(ctx, 3);
                            v1 = 0;
                            for (;;) {
                                // 0x003c29a0
                                charge(ctx, 3);
                                v0 = slt(v1, s2);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x003c297c
                                charge(ctx, 5);
                                v0 = sll(v1, 2);
                                v0 = addu(s3, v0);
                                lw(v0, v0, 0);
                                if (s1 == v0) {
                                    goto L_003c2990_8;
                                }
                                // 0x003c299c
                                charge(ctx, 1);
                                v1 = addiu(v1, 1);
                            }
                            // 0x003c29ac
                            charge(ctx, 1);
                            v1 = 0;
                        L_003c29b0:
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x003c29bc
                                charge(ctx, 8);
                                a0 = s1;
                                a1 = s5;
                                a2 = s4;
                                jal(ctx, 0x3C29C8u, gen::fn_sub_3C23F0_003c23f0);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x003c29dc
                                    charge(ctx, 5);
                                    a0 = s1;
                                    jal(ctx, 0x3C29E0u, gen::fn_sub_172660_00172660);
                                    if (v0 != 0) {
                                        // 0x003c29f0
                                        charge(ctx, 6);
                                        a0 = addiu(s1, 2448);
                                        jal(ctx, 0x3C29F4u, gen::fn_MT_Misc_BitChk_003951d0);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x003c2a08
                                            charge(ctx, 4);
                                            v0 = sll(s0, 2);
                                            v0 = addu(v0, sp);
                                            sw(s1, v0, 144);
                                            s0 = addiu(s0, 1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // 0x003c2a18
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003c2a28
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003c2a3c
        charge(ctx, 3);
        a1 = 0;
        for (;;) {
            // 0x003c2a60
            charge(ctx, 3);
            v0 = slt(a1, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c2a48
            charge(ctx, 6);
            a0 = sll(a1, 2);
            v0 = addu(a0, sp);
            lw(v1, v0, 144);
            v0 = addu(s6, a0);
            sw(v1, v0, 0);
            a1 = addiu(a1, 1);
        }
        // 0x003c2a6c
        charge(ctx, 2);
        sw(s0, s7, 0);
        v0 = 1;
    } else {
        // 0x003c2a30
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c2a74 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x110);
    return;
L_003c2990_8:
    charge(ctx, 3);
    v1 = 1;
    goto L_003c29b0;
}

// 0x003C2AB0 sub_3C2AB0 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuIsNoCallDay] Whether (month, day) is one of the 2-byte dates of 0x95B6A8 +8 (count +12).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2AB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2ab0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x3C2AC8u, gen::fn_sub_3BDD50_003bdd50);  // -> kComuData2
    lw(a1, v0, 8);
    lw(a0, v0, 12);
    a2 = 0;
    for (;;) {
        // 0x003c2b14
        charge(ctx, 3);
        v0 = slt(a2, a0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c2ae4
        charge(ctx, 5);
        v0 = sll(a2, 1);
        v1 = addu(a1, v0);
        lbu(v0, v1, 0);
        if (s1 == v0) {
            // 0x003c2af8
            charge(ctx, 3);
            lbu(v0, v1, 1);
            if (s0 != v0) {
                goto L_003c2b10;
            }
            goto L_003c2b04_3;
        }
    L_003c2b10:
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x003c2b20
    charge(ctx, 1);
    v0 = 0;
    // 0x003c2b24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003c2b04_3:
    charge(ctx, 3);
    v0 = 1;
    // 0x003c2b24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C2B40 sub_3C2B40 -- 264 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuNextCallDay] sub_17DDF0(&month, &day) gives the candidate date (two halfwords on the frame); 0
// when there is none or it is a no-call day, else *$a0 = month, *$a1 = day and 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2B40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2b40
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sh(zero, sp, 0x5E);
    sh(zero, sp, 0x5C);
    jal(ctx, 0x3C2B68u, gen::fn_clndGetCurrentMonth_0017d920);
    jal(ctx, 0x3C2B70u, gen::fn_clndGetCurrentDay_0017da40);
    a0 = addiu(sp, 0x5E);
    a1 = addiu(sp, 0x5C);
    jal(ctx, 0x3C2B80u, gen::fn_sub_17DDF0_0017ddf0);
    if (v0 != 0) {
        // 0x003c2b9c
        charge(ctx, 9);
        lh(s1, sp, 0x5C);
        lh(s0, sp, 0x5E);
        jal(ctx, 0x3C2BA4u, gen::fn_sub_3BDD50_003bdd50);  // -> kComuData2
        lw(a1, v0, 8);
        lw(a0, v0, 12);
        a2 = 0;
        for (;;) {
            // 0x003c2bf0
            charge(ctx, 3);
            v0 = slt(a2, a0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c2bc0
            charge(ctx, 5);
            v0 = sll(a2, 1);
            v1 = addu(a1, v0);
            lbu(v0, v1, 0);
            if (s0 == v0) {
                // 0x003c2bd4
                charge(ctx, 3);
                lbu(v0, v1, 1);
                if (s1 != v0) {
                    goto L_003c2bec;
                }
                goto L_003c2be0_5;
            }
        L_003c2bec:
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x003c2bfc
        charge(ctx, 1);
        v1 = 0;
    L_003c2c00:
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x003c2c18
            charge(ctx, 4);
            lh(v1, sp, 0x5E);
            sw(v1, s3, 0);
            lh(v1, sp, 0x5C);
            sw(v1, s2, 0);
        } else {
            // 0x003c2c0c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c2b90
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c2c28 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_003c2be0_5:
    charge(ctx, 3);
    v1 = 1;
    goto L_003c2c00;
}

// 0x003C2C50 sub_3C2C50 -- 412 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [comuCanCall] 0 when the link is the one sub_172C50 reports, not started, sub_1717C0 / sub_172160, at
// rank 1 or 10, without a phone row (0x95B6A8 +0, 24-byte rows), or flag 0x960 + link is set; otherwise 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2c50
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(sp, 0x2E);
    jal(ctx, 0x3C2C64u, gen::fn_sub_172C50_00172c50);
    if (v0 != 0) {
        // 0x003c2c74
        charge(ctx, 3);
        lh(v0, sp, 0x2E);
        if (s0 != v0) {
            goto L_003c2c8c;
        }
        // 0x003c2c80
        charge(ctx, 3);
        v0 = 0;
        // 0x003c2dd8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003c2c8c:
    charge(ctx, 6);
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C2C94u, gen::fn_sub_16E100_0016e100);
    if (v0 != 0) {
        // 0x003c2cb0
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x3C2CB4u, gen::fn_sub_1717C0_001717c0);
        v1 = 1;
        if (v0 != v1) {
            // 0x003c2cd4
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x3C2CD8u, gen::fn_sub_172160_00172160);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c2cf8
                charge(ctx, 9);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3C2D00u, gen::fn_sub_16DBA0_0016dba0);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = 1;
                if (v1 != v0) {
                    // 0x003c2d28
                    charge(ctx, 9);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3C2D30u, gen::fn_sub_16DBA0_0016dba0);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = 10;
                    if (v1 != v0) {
                        // 0x003c2d58
                        charge(ctx, 7);
                        jal(ctx, 0x3C2D58u, gen::fn_sub_3BDD50_003bdd50);  // -> kComuData2
                        lw(a0, v0, 0);
                        lw(v1, v0, 4);
                        a1 = 0;
                        for (;;) {
                            // 0x003c2da0
                            charge(ctx, 3);
                            v0 = slt(a1, v1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003c2d74
                            charge(ctx, 7);
                            v0 = sll(a1, 1);
                            v0 = addu(v0, a1);
                            v0 = sll(v0, 3);
                            v0 = addu(a0, v0);
                            lbu(v0, v0, 0);
                            if (s0 == v0) {
                                goto L_003c2d90_15;
                            }
                            // 0x003c2d9c
                            charge(ctx, 1);
                            a1 = addiu(a1, 1);
                        }
                        // 0x003c2dac
                        charge(ctx, 1);
                        v0 = 0;
                    L_003c2db0:
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x003c2dc4
                            charge(ctx, 5);
                            a0 = addiu(s0, 2400);
                            jal(ctx, 0x3C2DC8u, gen::fn_MT_Misc_BitChk_003951d0);
                            v0 = v0 ^ 0x1;
                            v0 = sltu(0, v0);
                        } else {
                            // 0x003c2db8
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x003c2d4c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x003c2d1c
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x003c2cec
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c2cc8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c2ca4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c2dd8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003c2d90_15:
    charge(ctx, 3);
    v0 = 1;
    goto L_003c2db0;
}

// 0x003C2DF0 sub_3C2DF0 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuIsBusyToday] Whether a no-call row (+0x650, 3 bytes {month, day, link}, count +0x654) names today
// and the link, or today and 0xFF.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2df0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x3C2E08u, gen::fn_sub_3BD870_003bd870);  // -> kComuData
    s1 = v0;
    jal(ctx, 0x3C2E14u, gen::fn_clndGetCurrentMonth_0017d920);
    s0 = v0;
    jal(ctx, 0x3C2E20u, gen::fn_clndGetCurrentDay_0017da40);
    t0 = 0;
    lw(a3, s1, kComuBusyCount);
    a0 = 255;
    for (;;) {
        // 0x003c2eac
        charge(ctx, 3);
        v1 = slt(t0, a3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003c2e3c
        charge(ctx, 7);
        lw(a1, s1, kComuBusyRows);
        v1 = sll(t0, 1);
        v1 = addu(v1, t0);
        a2 = addu(a1, v1);
        lbu(a1, a2, 0);
        if (s0 == a1) {
            // 0x003c2e58
            charge(ctx, 3);
            lbu(v1, a2, 1);
            if (v0 != v1) {
                goto L_003c2e7c;
            }
            // 0x003c2e64
            charge(ctx, 3);
            lbu(v1, a2, 2);
            if (s2 != v1) {
                goto L_003c2e7c;
            }
            goto L_003c2e70_4;
        }
    L_003c2e7c:
        charge(ctx, 2);
        if (s0 == a1) {
            // 0x003c2e84
            charge(ctx, 3);
            lbu(v1, a2, 1);
            if (v0 != v1) {
                goto L_003c2ea8;
            }
            // 0x003c2e90
            charge(ctx, 3);
            lbu(v1, a2, 2);
            if (v1 != a0) {
                goto L_003c2ea8;
            }
            goto L_003c2e9c_8;
        }
    L_003c2ea8:
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x003c2eb8
    charge(ctx, 1);
    v0 = 0;
    // 0x003c2ebc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003c2e70_4:
    charge(ctx, 3);
    v0 = 1;
    // 0x003c2ebc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003c2e9c_8:
    charge(ctx, 3);
    v0 = 1;
    // 0x003c2ebc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003C2EE0 sub_3C2EE0 -- 356 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuMakeCall] For a link that can call (sub_3C2C50; link < 30 asserted, line 0x558) and a next call
// day: sub_3BE2A0(0, 0, link, 7, 0x95B79C) fills the call data; then 0x95B790 = {1, month, day} and returns 0x95B790
// (0 otherwise).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C2EE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c2ee0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x3C2EF8u, gen::fn_sub_1717B0_001717b0);
    s1 = 0;
    s0 = 0;
    v0 = 0x960000;
    sw(zero, v0, -18544);  // 0x95B790 kComuCall.valid
    v0 = slti(s2, 30);
    if (v0 == 0) {
        // 0x003c2f1c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 13080);  // "comuSasoi.c"
        a1 = 1368;
        jal(ctx, 0x3C2F28u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    }
    // 0x003c2f30
    charge(ctx, 5);
    a0 = s2;
    jal(ctx, 0x3C2F34u, gen::fn_sub_3C2C50_003c2c50);
    if (v0 != 0) {
        // 0x003c2f50
        charge(ctx, 12);
        sh(zero, sp, 0x4E);
        sh(zero, sp, 0x4C);
        jal(ctx, 0x3C2F58u, gen::fn_clndGetCurrentMonth_0017d920);
        jal(ctx, 0x3C2F60u, gen::fn_clndGetCurrentDay_0017da40);
        a0 = addiu(sp, 0x4E);
        a1 = addiu(sp, 0x4C);
        jal(ctx, 0x3C2F70u, gen::fn_sub_17DDF0_0017ddf0);
        if (v0 != 0) {
            // 0x003c2f8c
            charge(ctx, 7);
            lh(a0, sp, 0x4E);
            lh(a1, sp, 0x4C);
            jal(ctx, 0x3C2F94u, gen::fn_sub_3C2AB0_003c2ab0);
            v1 = 1;
            if (v0 != v1) {
                // 0x003c2fb4
                charge(ctx, 2);
                lh(s1, sp, 0x4E);
                lh(s0, sp, 0x4C);
            } else {
                // 0x003c2fa8
                charge(ctx, 3);
                v1 = 0;
            }
        } else {
            // 0x003c2f80
            charge(ctx, 3);
            v1 = 0;
        }
        // 0x003c2fbc
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x003c2fd0
            charge(ctx, 10);
            a0 = 0;
            a1 = 0;
            a2 = s2;
            a3 = 7;
            t0 = 0x960000;
            t0 = addiu(t0, -18532);  // &0x95B79C kComuCall.data
            jal(ctx, 0x3C2FE8u, gen::fn_sub_3BE2A0_003be2a0);
            if (v0 != 0) {
                // 0x003c3004
                charge(ctx, 9);
                v1 = 1;
                v0 = 0x960000;
                sw(v1, v0, -18544);  // 0x95B790 kComuCall.valid
                v0 = 0x960000;
                sw(s1, v0, -18540);  // 0x95B794 kComuCall.month
                v0 = 0x960000;
                sw(s0, v0, -18536);  // 0x95B798 kComuCall.day
                v0 = 0x960000;
                v0 = addiu(v0, -18544);  // &0x95B790 kComuCall
            } else {
                // 0x003c2ff8
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c2fc4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c2f44
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3028 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003C3050 sub_3C3050 -- 96 bytes; frame 0x10: ra sp+0x0
// [comuMakeCallNow] sub_3BE2A0(0, 0, link, 7, 0x95B79C); success marks 0x95B790 valid and returns it.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3050
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    a0 = 0;
    a1 = 0;
    a3 = 7;
    t0 = 0x960000;
    t0 = addiu(t0, -18532);  // &0x95B79C kComuCall.data
    jal(ctx, 0x3C3070u, gen::fn_sub_3BE2A0_003be2a0);
    if (v0 != 0) {
        // 0x003c308c
        charge(ctx, 5);
        v1 = 1;
        v0 = 0x960000;
        sw(v1, v0, -18544);  // 0x95B790 kComuCall.valid
        v0 = 0x960000;
        v0 = addiu(v0, -18544);  // &0x95B790 kComuCall
    } else {
        // 0x003c3080
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c30a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C30B0 sub_3C30B0 -- 100 bytes; frame 0x10: ra sp+0x0
// [comuAcceptCall] With a valid call: sub_172B80(month, day, 0x95B79C, 1), clears the valid word, returns 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C30B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c30b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, -18544);  // 0x95B790 kComuCall.valid
    if (v0 != 0) {
        // 0x003c30d4
        charge(ctx, 12);
        v0 = 0x960000;
        lw(a0, v0, -18540);  // 0x95B794 kComuCall.month
        v0 = 0x960000;
        lw(a1, v0, -18536);  // 0x95B798 kComuCall.day
        a2 = 0x960000;
        a2 = addiu(a2, -18532);  // &0x95B79C kComuCall.data
        a3 = 1;
        jal(ctx, 0x3C30F0u, gen::fn_sub_172B80_00172b80);
        v0 = 0x960000;
        sw(zero, v0, -18544);  // 0x95B790 kComuCall.valid
        v0 = 1;
    } else {
        // 0x003c30c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3104 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C3120 sub_3C3120 -- 100 bytes; frame 0x10: ra sp+0x0
// [comuDeclineCall] As sub_3C30B0 with 0 as the last argument.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3120
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, -18544);  // 0x95B790 kComuCall.valid
    if (v0 != 0) {
        // 0x003c3144
        charge(ctx, 12);
        v0 = 0x960000;
        lw(a0, v0, -18540);  // 0x95B794 kComuCall.month
        v0 = 0x960000;
        lw(a1, v0, -18536);  // 0x95B798 kComuCall.day
        a2 = 0x960000;
        a2 = addiu(a2, -18532);  // &0x95B79C kComuCall.data
        a3 = 0;
        jal(ctx, 0x3C3160u, gen::fn_sub_172B80_00172b80);
        v0 = 0x960000;
        sw(zero, v0, -18544);  // 0x95B790 kComuCall.valid
        v0 = 1;
    } else {
        // 0x003c3138
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3174 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C3190 sub_3C3190 -- 512 bytes; frame 0xD0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuPickRandomCall] A 1-in-100 chance (sub_395230(100)), no current call (asserted), today not a no-call
// day; collects links with !sub_3BEBD0, sub_3C2C50 and !sub_3C2DF0, picks one with sub_395200(count), writes it to
// *$a0 and prepares its call data (sub_3BE2A0, asserted); 1 on success.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3190
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = 0;
    jal(ctx, 0x3C31B0u, gen::fn_clndGetCurrentMonth_0017d920);
    s1 = v0;
    jal(ctx, 0x3C31BCu, gen::fn_clndGetCurrentDay_0017da40);
    s0 = v0;
    v0 = 0x960000;
    sw(zero, v0, -18544);  // 0x95B790 kComuCall.valid
    a0 = 100;
    jal(ctx, 0x3C31D4u, gen::fn_sub_395230_00395230);  // random chance(n)
    if (v0 != 0) {
        // 0x003c31f0
        charge(ctx, 5);
        a0 = addiu(sp, 0xCE);
        jal(ctx, 0x3C31F4u, gen::fn_sub_172C50_00172c50);
        if (v0 != 0) {
            // 0x003c3204
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 13080);  // "comuSasoi.c"
            a1 = 1461;
            jal(ctx, 0x3C3210u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
        }
        // 0x003c3218
        charge(ctx, 7);
        jal(ctx, 0x3C3218u, gen::fn_sub_3BDD50_003bdd50);  // -> kComuData2
        lw(a1, v0, 8);
        lw(a0, v0, 12);
        a2 = 0;
        for (;;) {
            // 0x003c3264
            charge(ctx, 3);
            v0 = slt(a2, a0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003c3234
            charge(ctx, 5);
            v0 = sll(a2, 1);
            v1 = addu(a1, v0);
            lbu(v0, v1, 0);
            if (s1 == v0) {
                // 0x003c3248
                charge(ctx, 3);
                lbu(v0, v1, 1);
                if (s0 != v0) {
                    goto L_003c3260;
                }
                goto L_003c3254_7;
            }
        L_003c3260:
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x003c3270
        charge(ctx, 1);
        v1 = 0;
    L_003c3274:
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x003c328c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x003c32f0
                charge(ctx, 3);
                v0 = slti(s0, 30);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003c3298
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x3C329Cu, gen::fn_sub_3BEBD0_003bebd0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003c32b0
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x3C32B4u, gen::fn_sub_3C2C50_003c2c50);
                    if (v0 != 0) {
                        // 0x003c32c4
                        charge(ctx, 6);
                        a0 = s0;
                        jal(ctx, 0x3C32C8u, gen::fn_sub_3C2DF0_003c2df0);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x003c32dc
                            charge(ctx, 4);
                            v0 = sll(s2, 2);
                            v0 = addu(v0, sp);
                            sw(s0, v0, 80);
                            s2 = addiu(s2, 1);
                        }
                    }
                }
                // 0x003c32ec
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x003c32fc
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x003c3310
                charge(ctx, 16);
                a0 = s2;
                jal(ctx, 0x3C3314u, gen::fn_sub_395200_00395200);  // random(n)
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(a2, v0, 80);
                sw(a2, s3, 0);
                a0 = 0;
                a1 = 0;
                a3 = 7;
                t0 = 0x960000;
                t0 = addiu(t0, -18532);  // &0x95B79C kComuCall.data
                jal(ctx, 0x3C3340u, gen::fn_sub_3BE2A0_003be2a0);
                if (v0 == 0) {
                    // 0x003c3350
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 13080);  // "comuSasoi.c"
                    a1 = 1494;
                    jal(ctx, 0x3C335Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                }
                // 0x003c3364
                charge(ctx, 3);
                v0 = 1;
                v1 = 0x960000;
                sw(v0, v1, -18544);  // 0x95B790 kComuCall.valid
            } else {
                // 0x003c3304
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003c3280
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c31e4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3370 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_003c3254_7:
    charge(ctx, 3);
    v1 = 1;
    goto L_003c3274;
}

// 0x003C3390 sub_3C3390 -- 44 bytes; leaf frame (no stack)
// [comuGetCall] 0x95B790 when its valid word is set, else 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c3390
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, -18544);  // 0x95B790 kComuCall.valid
    if (v0 != 0) {
        // 0x003c33ac
        charge(ctx, 2);
        v0 = 0x960000;
        v0 = addiu(v0, -18544);  // &0x95B790 kComuCall
    } else {
        // 0x003c33a0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c33b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003C33C0 sub_3C33C0 -- 2752 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuEventExecStep] One step of a social-link event (record $a0: +0 link, +1 partner link, +2 type 0..7,
// +8 step result, +12 phase; *$a1 = 0 first). Phase 0 activates the link and sets flag 0xA2D when sub_16E850(link)
// exceeds the per-link byte of 0x6A3340 (30 for every link). Phase 1 picks phase 2 or 3 by the result (< 4) and on
// phase 2 reports result + 1 and clears flags 0xA14..0xA17. Phase 2 (with $a2 set) runs the type's checks (jump table)
// and applies the result flags 0xA14..0xA17 to the active link. Phase 3 finishes the event (type-specific bookkeeping,
// the date stamp sub_16E7A0, datGetPhysicalCondition(1)). Returns phase != 3.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C33C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c33c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a0, kExecPhase);
    sw(zero, a1, 0);
    lbu(a3, a0, kExecResult);
    lw(v1, a0, kExecPhase);
    a1 = 3;
    if (v1 == a1) {
        // 0x003c3c78
        charge(ctx, 4);
        lbu(v0, s2, kExecType);
        at = sltiu(v0, 8);
        if (at == 0) {
            // 0x003c3d44
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 13104);  // "comuEventExec.c"
            a1 = 502;
            jal(ctx, 0x3C3D50u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
        } else {
            // 0x003c3c88
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -19424);  // &0x7BB420
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3C3CA4u:  // table[0]
                // 0x003c3ca4
                charge(ctx, 8);
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3CA8u, gen::fn_sub_16E670_0016e670);
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3CB4u, gen::fn_sub_171B50_00171b50);
                break;
            case 0x3C3CC4u:  // table[1]
                // 0x003c3cc4
                charge(ctx, 13);
                lbu(v0, s2, kExecLink);
                a0 = addiu(v0, 2400);
                jal(ctx, 0x3C3CCCu, gen::fn_sub_3951A0_003951a0);  // flag bit off
                lbu(v0, s2, kExecLink);
                a0 = addiu(v0, 2448);
                jal(ctx, 0x3C3CDCu, gen::fn_sub_3951A0_003951a0);  // flag bit off
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3CE8u, gen::fn_sub_171B50_00171b50);
                break;
            case 0x3C3CF8u:  // table[2]
                // 0x003c3cf8
                charge(ctx, 5);
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3CFCu, gen::fn_sub_171B50_00171b50);
                break;
            case 0x3C3D0Cu:  // table[5]
                // 0x003c3d0c
                charge(ctx, 5);
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3D10u, gen::fn_sub_171B50_00171b50);
                break;
            case 0x3C3D20u:  // table[7]
                // 0x003c3d20
                charge(ctx, 9);
                lbu(v0, s2, kExecLink);
                a0 = addiu(v0, 2400);
                jal(ctx, 0x3C3D28u, gen::fn_sub_395170_00395170);  // flag bit on
                lbu(a0, s2, kExecLink);
                jal(ctx, 0x3C3D34u, gen::fn_sub_171B50_00171b50);
                break;
            case 0x3C3D58u:  // table[3, 4, 6]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x003c3d58
        charge(ctx, 4);
        lbu(v1, s2, kExecType);
        v0 = 7;
        if (v1 != v0) {
            // 0x003c3d68
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003c3d84;
            }
            // 0x003c3d74
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003c3d84;
            }
            // 0x003c3d7c
            charge(ctx, 2);
            goto L_003c3db4;
        }
    L_003c3d84:
        charge(ctx, 6);
        lbu(a0, s2, kExecLink);
        jal(ctx, 0x3C3D88u, gen::fn_sub_172A50_00172a50);
        v1 = 1;
        if (v0 == v1) {
            // 0x003c3d9c
            charge(ctx, 6);
            lbu(a0, s2, kExecLink);
            jal(ctx, 0x3C3DA0u, gen::fn_sub_172AB0_00172ab0);
            lbu(a0, s2, kExecLink);
            jal(ctx, 0x3C3DACu, gen::fn_sub_3BDBD0_003bdbd0);
        }
    L_003c3db4:
        charge(ctx, 15);
        jal(ctx, 0x3C3DB4u, gen::fn_datGetDaysSinceApr5_0016ef20);
        lbu(a0, s2, kExecLink);
        a1 = v0;
        jal(ctx, 0x3C3DC4u, gen::fn_sub_16E7A0_0016e7a0);
        a0 = 1;
        jal(ctx, 0x3C3DD0u, gen::fn_sub_16C920_0016c920);
        jal(ctx, 0x3C3DD8u, gen::fn_sub_172860_00172860);
        lbu(v0, s2, kExecType);
        at = sltiu(v0, 8);
        if (at == 0) {
            // 0x003c3e2c
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, 13104);  // "comuEventExec.c"
            a1 = 536;
            jal(ctx, 0x3C3E38u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
        } else {
            // 0x003c3df0
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -19456);  // &0x7BB400
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3C3E0Cu:  // table[0, 1, 2, 3, 4, 5, 6]
                // 0x003c3e0c
                charge(ctx, 4);
                jal(ctx, 0x3C3E0Cu, gen::fn_sub_172890_00172890);
                break;
            case 0x3C3E1Cu:  // table[7]
                // 0x003c3e1c
                charge(ctx, 4);
                jal(ctx, 0x3C3E1Cu, gen::fn_sub_172AE0_00172ae0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    } else {
        // 0x003c33f8
        charge(ctx, 3);
        a0 = 2;
        if (v1 == a0) {
            // 0x003c3688
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x003c3690
                charge(ctx, 4);
                lbu(v0, s2, kExecType);
                at = sltiu(v0, 8);
                if (at == 0) {
                    // 0x003c3ae0
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 13104);  // "comuEventExec.c"
                    a1 = 426;
                    jal(ctx, 0x3C3AECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                } else {
                    // 0x003c36a0
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -19392);  // &0x7BB440
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x3C36BCu:  // table[0]
                        // 0x003c36bc
                        charge(ctx, 2);
                        if (a3 == a0) {
                            // 0x003c3854
                            charge(ctx, 6);
                            lbu(a0, s2, kExecPartner);
                            jal(ctx, 0x3C3858u, gen::fn_sub_16E100_0016e100);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x003c386c
                                charge(ctx, 6);
                                jal(ctx, 0x3C386Cu, gen::fn_datGetDaysSinceApr5_0016ef20);
                                lbu(a0, s2, kExecPartner);
                                a1 = v0;
                                jal(ctx, 0x3C387Cu, gen::fn_sub_16E7A0_0016e7a0);
                            }
                            // 0x003c3884
                            charge(ctx, 4);
                            v0 = 4;
                            sb(v0, s2, kExecResult);
                        } else {
                            // 0x003c36c4
                            charge(ctx, 3);
                            v0 = 1;
                            if (a3 == v0) {
                                // 0x003c37a0
                                charge(ctx, 9);
                                a0 = 2441;
                                jal(ctx, 0x3C37A4u, gen::fn_sub_395170_00395170);  // flag bit on
                                a0 = s2;
                                jal(ctx, 0x3C37B0u, gen::fn_sub_3BE1A0_003be1a0);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x003c3844
                                    charge(ctx, 4);
                                    v0 = 4;
                                    sb(v0, s2, kExecResult);
                                } else {
                                    // 0x003c37c4
                                    charge(ctx, 18);
                                    lbu(v0, s2, kExecPartner);
                                    s1 = dsll32(v0, 16);
                                    s1 = dsra32(s1, 16);
                                    a0 = s1;
                                    jal(ctx, 0x3C37D4u, gen::fn_sub_16E920_0016e920);
                                    a0 = s1;
                                    jal(ctx, 0x3C37E0u, gen::fn_sub_16E850_0016e850);
                                    a0 = dsll32(s1, 16);
                                    a0 = dsra32(a0, 16);
                                    v1 = 0x6A0000;
                                    v1 = addiu(v1, 13120);  // &0x6A3340
                                    v1 = addu(v1, a0);
                                    lb(v1, v1, 0);
                                    at = slt(v1, v0);
                                    if (at == 0) {
                                        // 0x003c3824
                                        charge(ctx, 4);
                                        a0 = 2605;
                                        a1 = 0;
                                        jal(ctx, 0x3C382Cu, gen::fn_datSetFlag_0016f1f0);
                                    } else {
                                        // 0x003c380c
                                        charge(ctx, 6);
                                        a0 = 2605;
                                        a1 = 1;
                                        jal(ctx, 0x3C3814u, gen::fn_datSetFlag_0016f1f0);
                                    }
                                    // 0x003c3834
                                    charge(ctx, 4);
                                    v0 = 2;
                                    sb(v0, s2, kExecResult);
                                }
                            } else {
                                // 0x003c36d0
                                charge(ctx, 2);
                                if (a3 == 0) {
                                    // 0x003c36e0
                                    charge(ctx, 6);
                                    a0 = addiu(s2, 36);
                                    jal(ctx, 0x3C36E4u, gen::fn_sub_172750_00172750);
                                    v1 = 1;
                                    if (v0 != v1) {
                                        // 0x003c375c
                                        charge(ctx, 6);
                                        a0 = s2;
                                        jal(ctx, 0x3C3760u, gen::fn_sub_3BE1A0_003be1a0);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x003c3790
                                            charge(ctx, 4);
                                            v0 = 4;
                                            sb(v0, s2, kExecResult);
                                        } else {
                                            // 0x003c3774
                                            charge(ctx, 7);
                                            lbu(a0, s2, kExecPartner);
                                            jal(ctx, 0x3C3778u, gen::fn_sub_16E920_0016e920);
                                            v0 = 2;
                                            sb(v0, s2, kExecResult);
                                        }
                                    } else {
                                        // 0x003c36f8
                                        charge(ctx, 5);
                                        jal(ctx, 0x3C36F8u, gen::fn_sub_172A30_00172a30);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x003c3718
                                            charge(ctx, 6);
                                            a0 = s2;
                                            jal(ctx, 0x3C371Cu, gen::fn_sub_3BE1A0_003be1a0);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                // 0x003c374c
                                                charge(ctx, 4);
                                                v0 = 4;
                                                sb(v0, s2, kExecResult);
                                            } else {
                                                // 0x003c3730
                                                charge(ctx, 7);
                                                lbu(a0, s2, kExecPartner);
                                                jal(ctx, 0x3C3734u, gen::fn_sub_16E920_0016e920);
                                                v0 = 2;
                                                sb(v0, s2, kExecResult);
                                            }
                                        } else {
                                            // 0x003c370c
                                            charge(ctx, 3);
                                            sb(v1, s2, kExecResult);
                                        }
                                    }
                                } else {
                                    // 0x003c36d8
                                    charge(ctx, 2);
                                    // 0x003c3894
                                    charge(ctx, 7);
                                    a0 = 0x6A0000;
                                    a0 = addiu(a0, 13104);  // "comuEventExec.c"
                                    a1 = 330;
                                    jal(ctx, 0x3C38A0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                                }
                            }
                        }
                        break;
                    case 0x3C38B0u:  // table[1]
                        // 0x003c38b0
                        charge(ctx, 2);
                        if (a3 == a1) {
                            // 0x003c39e8
                            charge(ctx, 4);
                            v0 = 4;
                            sb(v0, s2, kExecResult);
                        } else {
                            // 0x003c38b8
                            charge(ctx, 2);
                            if (a3 == a0) {
                                // 0x003c39b0
                                charge(ctx, 6);
                                a0 = addiu(s2, 48);
                                jal(ctx, 0x3C39B4u, gen::fn_sub_172750_00172750);
                                v1 = 1;
                                if (v0 != v1) {
                                    // 0x003c39d8
                                    charge(ctx, 4);
                                    v0 = 4;
                                    sb(v0, s2, kExecResult);
                                } else {
                                    // 0x003c39c8
                                    charge(ctx, 4);
                                    v0 = 3;
                                    sb(v0, s2, kExecResult);
                                }
                            } else {
                                // 0x003c38c0
                                charge(ctx, 3);
                                v0 = 1;
                                if (a3 == v0) {
                                    // 0x003c3978
                                    charge(ctx, 6);
                                    a0 = addiu(s2, 42);
                                    jal(ctx, 0x3C397Cu, gen::fn_sub_172750_00172750);
                                    v1 = 1;
                                    if (v0 != v1) {
                                        // 0x003c39a0
                                        charge(ctx, 4);
                                        v0 = 4;
                                        sb(v0, s2, kExecResult);
                                    } else {
                                        // 0x003c3990
                                        charge(ctx, 4);
                                        v0 = 2;
                                        sb(v0, s2, kExecResult);
                                    }
                                } else {
                                    // 0x003c38cc
                                    charge(ctx, 2);
                                    if (a3 == 0) {
                                        // 0x003c38dc
                                        charge(ctx, 6);
                                        a0 = addiu(s2, 36);
                                        jal(ctx, 0x3C38E0u, gen::fn_sub_172750_00172750);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x003c3968
                                            charge(ctx, 4);
                                            v0 = 4;
                                            sb(v0, s2, kExecResult);
                                        } else {
                                            // 0x003c38f4
                                            charge(ctx, 5);
                                            a0 = 9;
                                            jal(ctx, 0x3C38F8u, gen::fn_sub_38D6F0_0038d6f0);
                                            if (v0 != 0) {
                                                // 0x003c3918
                                                charge(ctx, 3);
                                                v1 = 1;
                                                if (v0 != v1) {
                                                    // 0x003c395c
                                                    charge(ctx, 3);
                                                    sb(v1, s2, kExecResult);
                                                } else {
                                                    // 0x003c3924
                                                    charge(ctx, 6);
                                                    a0 = addiu(s2, 42);
                                                    jal(ctx, 0x3C3928u, gen::fn_sub_172750_00172750);
                                                    v1 = 1;
                                                    if (v0 != v1) {
                                                        // 0x003c394c
                                                        charge(ctx, 4);
                                                        v0 = 4;
                                                        sb(v0, s2, kExecResult);
                                                    } else {
                                                        // 0x003c393c
                                                        charge(ctx, 4);
                                                        v0 = 2;
                                                        sb(v0, s2, kExecResult);
                                                    }
                                                }
                                            } else {
                                                // 0x003c3908
                                                charge(ctx, 4);
                                                v0 = 1;
                                                sb(v0, s2, kExecResult);
                                            }
                                        }
                                    } else {
                                        // 0x003c38d4
                                        charge(ctx, 2);
                                        // 0x003c39f8
                                        charge(ctx, 7);
                                        a0 = 0x6A0000;
                                        a0 = addiu(a0, 13104);  // "comuEventExec.c"
                                        a1 = 386;
                                        jal(ctx, 0x3C3A04u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                                    }
                                }
                            }
                        }
                        break;
                    case 0x3C3A14u:  // table[2]
                        // 0x003c3a14
                        charge(ctx, 4);
                        v0 = 4;
                        sb(v0, s2, kExecResult);
                        break;
                    case 0x3C3A24u:  // table[3]
                        // 0x003c3a24
                        charge(ctx, 4);
                        v0 = 4;
                        sb(v0, s2, kExecResult);
                        break;
                    case 0x3C3A34u:  // table[4]
                        // 0x003c3a34
                        charge(ctx, 4);
                        v0 = 4;
                        sb(v0, s2, kExecResult);
                        break;
                    case 0x3C3A44u:  // table[5]
                        // 0x003c3a44
                        charge(ctx, 4);
                        v0 = 4;
                        sb(v0, s2, kExecResult);
                        break;
                    case 0x3C3A54u:  // table[6]
                        // 0x003c3a54
                        charge(ctx, 4);
                        v0 = 4;
                        sb(v0, s2, kExecResult);
                        break;
                    case 0x3C3A64u:  // table[7]
                        // 0x003c3a64
                        charge(ctx, 2);
                        if (a3 == 0) {
                            // 0x003c3a74
                            charge(ctx, 5);
                            a0 = addiu(s2, 36);
                            jal(ctx, 0x3C3A78u, gen::fn_sub_172750_00172750);
                            if (v0 == 0) {
                                // 0x003c3a88
                                charge(ctx, 5);
                                a0 = 0x6A0000;
                                a0 = addiu(a0, 13104);  // "comuEventExec.c"
                                a1 = 409;
                                jal(ctx, 0x3C3A94u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                            }
                            // 0x003c3a9c
                            charge(ctx, 5);
                            a0 = 8;
                            jal(ctx, 0x3C3AA0u, gen::fn_sub_38D6F0_0038d6f0);
                            if (v0 != 0) {
                                // 0x003c3ac0
                                charge(ctx, 4);
                                v0 = 4;
                                sb(v0, s2, kExecResult);
                            } else {
                                // 0x003c3ab0
                                charge(ctx, 4);
                                v0 = 1;
                                sb(v0, s2, kExecResult);
                            }
                        } else {
                            // 0x003c3a6c
                            charge(ctx, 2);
                            // 0x003c3ad0
                            charge(ctx, 4);
                            v0 = 4;
                            sb(v0, s2, kExecResult);
                        }
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x003c3af4
                charge(ctx, 8);
                v0 = 1;
                sw(v0, s2, kExecPhase);
                a0 = 2580;
                jal(ctx, 0x3C3B00u, gen::fn_MT_Misc_BitChk_003951d0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x003c3b14
                    charge(ctx, 7);
                    jal(ctx, 0x3C3B14u, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = 1;
                    jal(ctx, 0x3C3B28u, gen::fn_sub_171C40_00171c40);
                }
                // 0x003c3b30
                charge(ctx, 6);
                a0 = 2581;
                jal(ctx, 0x3C3B34u, gen::fn_MT_Misc_BitChk_003951d0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x003c3b48
                    charge(ctx, 7);
                    jal(ctx, 0x3C3B48u, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = 0;
                    jal(ctx, 0x3C3B5Cu, gen::fn_sub_171C40_00171c40);
                }
                // 0x003c3b64
                charge(ctx, 6);
                a0 = 2582;
                jal(ctx, 0x3C3B68u, gen::fn_MT_Misc_BitChk_003951d0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x003c3b7c
                    charge(ctx, 7);
                    jal(ctx, 0x3C3B7Cu, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = 1;
                    jal(ctx, 0x3C3B90u, gen::fn_sub_172200_00172200);
                }
                // 0x003c3b98
                charge(ctx, 6);
                a0 = 2583;
                jal(ctx, 0x3C3B9Cu, gen::fn_MT_Misc_BitChk_003951d0);
                v1 = 1;
                if (v0 == v1) {
                    // 0x003c3bb0
                    charge(ctx, 7);
                    jal(ctx, 0x3C3BB0u, gen::fn_sub_16DD40_0016dd40);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = 0;
                    jal(ctx, 0x3C3BC4u, gen::fn_sub_172200_00172200);
                }
                // 0x003c3bcc
                charge(ctx, 5);
                a0 = 7;
                jal(ctx, 0x3C3BD0u, gen::fn_sub_38D6F0_0038d6f0);
                if (v0 != 0) {
                    // 0x003c3be0
                    charge(ctx, 6);
                    a0 = 7;
                    jal(ctx, 0x3C3BE4u, gen::fn_sub_38D6F0_0038d6f0);
                    v1 = 2;
                    if (v0 == v1) {
                        goto L_003c3bf8;
                    }
                    // 0x003c3e5c (the shared epilogue, written out on this path)
                    charge(ctx, 9);
                    v0 = s0 ^ 0x3;
                    v0 = sltu(0, v0);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x50);
                    return;
                }
            L_003c3bf8:
                charge(ctx, 6);
                a0 = 7;
                jal(ctx, 0x3C3BFCu, gen::fn_sub_38D6F0_0038d6f0);
                v1 = 2;
                if (v0 == v1) {
                    // 0x003c3c10
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x4E);
                    jal(ctx, 0x3C3C14u, gen::fn_sub_172C50_00172c50);
                    if (v0 == 0) {
                        // 0x003c3c24
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 13104);  // "comuEventExec.c"
                        a1 = 458;
                        jal(ctx, 0x3C3C30u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                    }
                    // 0x003c3c38
                    charge(ctx, 5);
                    lh(a0, sp, 0x4E);
                    jal(ctx, 0x3C3C3Cu, gen::fn_sub_172CC0_00172cc0);
                    jal(ctx, 0x3C3C44u, gen::fn_sub_172B20_00172b20);
                }
                // 0x003c3c4c
                charge(ctx, 4);
                jal(ctx, 0x3C3C4Cu, gen::fn_sub_3C30B0_003c30b0);
                if (v0 == 0) {
                    // 0x003c3c5c
                    charge(ctx, 7);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 13104);  // "comuEventExec.c"
                    a1 = 464;
                    jal(ctx, 0x3C3C68u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                }
            }
        } else {
            // 0x003c3404
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x003c34ac
                charge(ctx, 4);
                lbu(v0, s2, kExecType);
                at = sltiu(v0, 8);
                if (at == 0) {
                    // 0x003c3610
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 13104);  // "comuEventExec.c"
                    a1 = 251;
                    jal(ctx, 0x3C361Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                } else {
                    // 0x003c34bc
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -19360);  // &0x7BB460
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x3C34D8u:  // table[0]
                        // 0x003c34d8
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c34f0
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c34e4
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C34FCu:  // table[1]
                        // 0x003c34fc
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c352c
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c3508
                            charge(ctx, 2);
                            if (a3 == 0) {
                                // 0x003c3510
                                charge(ctx, 3);
                                lbu(a0, s2, kExecLink);
                                jal(ctx, 0x3C3514u, gen::fn_sub_1725A0_001725a0);
                            }
                            // 0x003c351c
                            charge(ctx, 4);
                            v0 = 2;
                            sw(v0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C3538u:  // table[2]
                        // 0x003c3538
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c3550
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c3544
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C355Cu:  // table[3]
                        // 0x003c355c
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c3574
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c3568
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C3580u:  // table[4]
                        // 0x003c3580
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c3598
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c358c
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C35A4u:  // table[5]
                        // 0x003c35a4
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c35bc
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c35b0
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C35C8u:  // table[6]
                        // 0x003c35c8
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c35e0
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c35d4
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    case 0x3C35ECu:  // table[7]
                        // 0x003c35ec
                        charge(ctx, 3);
                        at = slti(a3, 4);
                        if (at == 0) {
                            // 0x003c3604
                            charge(ctx, 3);
                            sw(a1, s2, kExecPhase);
                        } else {
                            // 0x003c35f8
                            charge(ctx, 3);
                            sw(a0, s2, kExecPhase);
                        }
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x003c3624
                charge(ctx, 4);
                lw(v1, s2, kExecPhase);
                v0 = 2;
                if (v1 == v0) {
                    // 0x003c3634
                    charge(ctx, 21);
                    lbu(v0, s2, kExecResult);
                    v0 = addiu(v0, 1);
                    sw(v0, s1, 0);
                    a0 = 2580;
                    a1 = 0;
                    jal(ctx, 0x3C3648u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 2581;
                    a1 = 0;
                    jal(ctx, 0x3C3658u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 2582;
                    a1 = 0;
                    jal(ctx, 0x3C3668u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 2583;
                    a1 = 0;
                    jal(ctx, 0x3C3678u, gen::fn_datSetFlag_0016f1f0);
                }
            } else {
                // 0x003c3410
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x003c3420
                    charge(ctx, 20);
                    lbu(a0, s2, kExecLink);
                    jal(ctx, 0x3C3424u, gen::fn_sub_16E920_0016e920);
                    jal(ctx, 0x3C342Cu, gen::fn_sub_1727E0_001727e0);
                    lbu(v0, s2, kExecLink);
                    s1 = dsll32(v0, 16);
                    s1 = dsra32(s1, 16);
                    a0 = s1;
                    jal(ctx, 0x3C3444u, gen::fn_sub_16E850_0016e850);
                    a0 = dsll32(s1, 16);
                    a0 = dsra32(a0, 16);
                    v1 = 0x6A0000;
                    v1 = addiu(v1, 13120);  // &0x6A3340
                    v1 = addu(v1, a0);
                    lb(v1, v1, 0);
                    at = slt(v1, v0);
                    if (at == 0) {
                        // 0x003c3488
                        charge(ctx, 4);
                        a0 = 2605;
                        a1 = 0;
                        jal(ctx, 0x3C3490u, gen::fn_datSetFlag_0016f1f0);
                    } else {
                        // 0x003c3470
                        charge(ctx, 6);
                        a0 = 2605;
                        a1 = 1;
                        jal(ctx, 0x3C3478u, gen::fn_datSetFlag_0016f1f0);
                    }
                    // 0x003c3498
                    charge(ctx, 5);
                    sb(zero, s2, kExecResult);
                    v0 = 1;
                    sw(v0, s2, kExecPhase);
                } else {
                    // 0x003c3418
                    charge(ctx, 2);
                    // 0x003c3e48
                    charge(ctx, 5);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 13104);  // "comuEventExec.c"
                    a1 = 540;
                    jal(ctx, 0x3C3E54u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
                }
            }
        }
    }
    // 0x003c3e5c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0 ^ 0x3;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003C3E80 sub_3C3E80 -- 180 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [comuEventExecUpdate] Runs one step with $a2 = (phase == 2 && sub_3BF130() == 1); on 1 with a reported
// step n, sub_3BF180 gets the n-th 6-byte row at record +0x20; returns 1, or 0 when the step returned 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3e80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, sp, 0x2C);
    lw(v0, a0, 12);
    v0 = v0 ^ 0x2;
    a2 = sltiu(v0, 1);
    if (a2 != 0) {
        // 0x003c3ea8
        charge(ctx, 4);
        jal(ctx, 0x3C3EA8u, gen::fn_sub_3BF130_003bf130);
        v0 = v0 ^ 0x1;
        a2 = sltiu(v0, 1);
    }
    // 0x003c3eb8
    charge(ctx, 7);
    a0 = s0;
    a1 = addiu(sp, 0x2C);
    jal(ctx, 0x3C3EC0u, gen::fn_sub_3C33C0_003c33c0);
    v1 = 1;
    if (v0 != v1) {
        // 0x003c3f10
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x003c3ed4
        charge(ctx, 3);
        lw(v0, sp, 0x2C);
        if (v0 != 0) {
            // 0x003c3ee0
            charge(ctx, 12);
            v1 = addiu(v0, -1);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(s0, v0);
            lhu(a0, v0, 32);
            lbu(a1, v0, 34);
            lbu(a2, v0, 35);
            jal(ctx, 0x3C3F00u, gen::fn_sub_3BF180_003bf180);
        }
        // 0x003c3f1c
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x003c3f20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C3F40 sub_3C3F40 -- 56 bytes; leaf frame (no stack)
// [comuGetPlaceName] 0x6A3590[place & 0xFF] ("Club", "Rooftop", ...); 0 for 42 and up.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003c3f40
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a0 & 0xFF;
    v0 = slti(v1, 42);
    if (v0 != 0) {
        // 0x003c3f5c
        charge(ctx, 5);
        v1 = sll(v1, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 13712);  // &0x6A3590
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
    } else {
        // 0x003c3f50
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3f70 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003C3F80 sub_3C3F80 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetLinkTitle] 0x6A38E0[link] ("SEES", "Classmate", ...) when sub_16DCE0(link), else 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3f80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C3F98u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 != 0) {
        // 0x003c3fb4
        charge(ctx, 5);
        v1 = sll(s0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 14560);  // &0x6A38E0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
    } else {
        // 0x003c3fa8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c3fc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C3FE0 sub_3C3FE0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetPartnerName] 0x6A36A0[link] ("SEES", "Kenji", ...) when sub_16DCE0(link), else 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C3FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c3fe0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C3FF8u, gen::fn_sub_16DCE0_0016dce0);
    if (v0 != 0) {
        // 0x003c4014
        charge(ctx, 5);
        v1 = sll(s0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 13984);  // &0x6A36A0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
    } else {
        // 0x003c4008
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c4028 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C4040 sub_3C4040 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [comuGetGridText] 0x6A38E8[24 b + 4 a]; both links asserted with sub_172A50 (comuData.c lines 0x30,
// 0x32).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4040
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C4060u, gen::fn_sub_172A50_00172a50);
    if (v0 == 0) {
        // 0x003c4070
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15704);  // "comuData.c"
        a1 = 48;
        jal(ctx, 0x3C407Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    }
    // 0x003c4084
    charge(ctx, 6);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3C408Cu, gen::fn_sub_172A50_00172a50);
    if (v0 == 0) {
        // 0x003c409c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15704);  // "comuData.c"
        a1 = 50;
        jal(ctx, 0x3C40A8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    }
    // 0x003c40b0 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v0 = sll(s1, 1);
    v0 = addu(v0, s1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, 14568);  // "86j"
    v1 = addu(v0, v1);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C40F0 sub_3C40F0 -- 28 bytes; leaf frame (no stack)
// [comuGetSasoiKind] The signed byte 0x6A3D70[4 link] (0 none, 2 for links 1, 4, 6..14, 17..19, 23, 27).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C40F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003c40f0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 15728);  // &0x6A3D70
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
}

// 0x003C4110 sub_3C4110 -- 28 bytes; leaf frame (no stack)
// [comuGetSasoiMessage] The u16 0x6A3D72[4 link].
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003c4110
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 15730);  // &0x6A3D72
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
}

// 0x003C4130 sub_3C4130 -- 220 bytes; frame 0x10: ra sp+0x0
// [comuGetWeekdayName] The weekday name ("Sunday" ...) of a date (clndGetDaysSinceStartFromDate ->
// clndGetWeekDay, jump table 0x7BB3F0); asserts (line 0x88) and returns 0 out of range.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4130(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4130
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C4138u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    a0 = v0;
    jal(ctx, 0x3C4144u, gen::fn_clndGetWeekDay_0017dae0);
    at = sltiu(v0, 7);
    if (at == 0) {
        // 0x003c41e4
        charge(ctx, 6);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15704);  // "comuData.c"
        a1 = 136;
        jal(ctx, 0x3C41F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
        v0 = 0;
    } else {
        // 0x003c4158
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -19328);  // "tA<"
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3C4174u:  // table[0]
            // 0x003c4174
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14928);  // 0x6A3A50
            break;
        case 0x3C4184u:  // table[1]
            // 0x003c4184
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14932);  // 0x6A3A54
            break;
        case 0x3C4194u:  // table[2]
            // 0x003c4194
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14936);  // 0x6A3A58
            break;
        case 0x3C41A4u:  // table[3]
            // 0x003c41a4
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14940);  // 0x6A3A5C
            break;
        case 0x3C41B4u:  // table[4]
            // 0x003c41b4
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14944);  // 0x6A3A60
            break;
        case 0x3C41C4u:  // table[5]
            // 0x003c41c4
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14948);  // 0x6A3A64
            break;
        case 0x3C41D4u:  // table[6]
            // 0x003c41d4
            charge(ctx, 4);
            v0 = 0x6A0000;
            lw(v0, v0, 14952);  // 0x6A3A68
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x003c41fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C4210 sub_3C4210 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetGiftText] 0x6A3B40[i] (i < 6 asserted, line 0x93).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4210
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = slti(s0, 6);
    if (v0 == 0) {
        // 0x003c422c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15704);  // "comuData.c"
        a1 = 147;
        jal(ctx, 0x3C4238u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    }
    // 0x003c4240 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = sll(s0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 15168);  // "p:j"
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C4270 sub_3C4270 -- 280 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetWhenText] "tomorrow" when the date is the day after today, else "next <weekday>" (jump table
// 0x7BB410; out of range asserts, line 0xBA, and gives "next Sunday").
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4270(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4270
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3C427Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    s0 = v0;
    jal(ctx, 0x3C4288u, gen::fn_datGetDaysSinceApr5_0016ef20);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = addiu(v0, 1);
    if (s0 != v0) {
        // 0x003c42b4
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x3C42B8u, gen::fn_clndGetWeekDay_0017dae0);
        at = sltiu(v0, 7);
        if (at == 0) {
            // 0x003c4358
            charge(ctx, 7);
            a0 = 0x6A0000;
            a0 = addiu(a0, 15704);  // "comuData.c"
            a1 = 186;
            jal(ctx, 0x3C4364u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
            v0 = 0x6A0000;
            lw(v0, v0, 15328);  // 0x6A3BE0
        } else {
            // 0x003c42cc
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -19296);  // &0x7BB4A0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3C42E8u:  // table[0]
                // 0x003c42e8
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15328);  // 0x6A3BE0
                break;
            case 0x3C42F8u:  // table[1]
                // 0x003c42f8
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15332);  // 0x6A3BE4
                break;
            case 0x3C4308u:  // table[2]
                // 0x003c4308
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15336);  // 0x6A3BE8
                break;
            case 0x3C4318u:  // table[3]
                // 0x003c4318
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15340);  // 0x6A3BEC
                break;
            case 0x3C4328u:  // table[4]
                // 0x003c4328
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15344);  // 0x6A3BF0
                break;
            case 0x3C4338u:  // table[5]
                // 0x003c4338
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15348);  // 0x6A3BF4
                break;
            case 0x3C4348u:  // table[6]
                // 0x003c4348
                charge(ctx, 4);
                v0 = 0x6A0000;
                lw(v0, v0, 15352);  // 0x6A3BF8
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    } else {
        // 0x003c42a4
        charge(ctx, 4);
        v0 = 0x6A0000;
        lw(v0, v0, 15356);  // 0x6A3BFC
    }
    // 0x003c4374 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C4390 sub_3C4390 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [comuGetUltimatePersonaName] 0x6A3CA0[i - 1] ("Susano-o" ...), 1 <= i <= 22 asserted (line 0xC6).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4390(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c4390
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(a0, -1);
    at = slti(s0, 22);
    if (at != 0) {
        // 0x003c43ac
        charge(ctx, 2);
        if (i64(s0) < 0) {
            goto L_003c43b4;
        }
        // 0x003c43c8 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        v1 = sll(s0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 15520);  // &0x6A3CA0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_003c43b4:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 15704);  // "comuData.c"
    a1 = 198;
    jal(ctx, 0x3C43C0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail
    // 0x003c43c8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v1 = sll(s0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 15520);  // &0x6A3CA0
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003C43F0 sub_3C43F0 -- 12 bytes; leaf frame (no stack)
// [comuGetGpWord] The word at gp-0x5604.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C43F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003c43f0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -22020);  // 0x7CD6EC
}

// 0x003C4400 sub_3C4400 -- 12 bytes; leaf frame (no stack)
// Returns 0 (one of the nmlist default callbacks nmCmdListCreate installs).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c4400
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003C4410 sub_3C4410 -- 12 bytes; leaf frame (no stack)
// Returns 0 (an nmlist default callback).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c4410
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003C4420 sub_3C4420 -- 12 bytes; leaf frame (no stack)
// Returns 0 (an nmlist default callback).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_3C4420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003c4420
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00421770 Y_LMap_UpdateLmapTask -- 1536 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_UpdateLmapTask: the "y_lmap proc" update -- loads field/script/lmap.bf and lmap/lmap_dat, the
// scene, runs the script task, the menu and model tasks, fades in / out (jump table 0x7BC1E0 over the phase word).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_UpdateLmapTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00421770
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, kTaskWork);
    lw(v0, s0, 0);
    at = sltiu(v0, 17);
    if (at != 0) {
        // 0x0042179c
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -15920);  // &0x7BC1D0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x4217B8u:  // table[0]
            // 0x004217b8
            charge(ctx, 12);
            jal(ctx, 0x4217B8u, gen::fn_sub_421F20_00421f20);
            a0 = 0x6B0000;
            a0 = addiu(a0, 17312);  // "field/script/lmap.bf"
            a1 = 0;
            jal(ctx, 0x4217CCu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 96);
            v0 = 1;
            sw(v0, s0, 0);
            break;
        case 0x4217E8u:  // table[1]
            // 0x004217e8
            charge(ctx, 5);
            lw(a0, s0, 96);
            jal(ctx, 0x4217ECu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x004217fc
                charge(ctx, 8);
                a0 = 0x6B0000;
                a0 = addiu(a0, 17336);  // "lmap/lmap_dat"
                a1 = 1;
                jal(ctx, 0x421808u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 112);
                v0 = 2;
                sw(v0, s0, 0);
            L_0042181c:
                charge(ctx, 5);
                lw(a0, s0, 112);
                jal(ctx, 0x421820u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x00421830
                    charge(ctx, 28);
                    lw(v0, s0, 96);
                    lhu(a1, v0, 280);
                    a0 = 1;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
                    jalr(ctx, 0x421848u, v0.u());
                    sw(v0, s0, 104);
                    lw(v0, s0, 96);
                    lw(v0, v0, 280);
                    sw(v0, s0, 100);
                    lw(v0, s0, 96);
                    lhu(a2, v0, 280);
                    lw(a0, s0, 104);
                    lw(a1, v0, 272);
                    jal(ctx, 0x421870u, gen::fn_memcpy_00521250);
                    a0 = 10;
                    lw(a1, s0, 104);
                    lw(a2, s0, 100);
                    a3 = 0;
                    jal(ctx, 0x421888u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                    sw(v0, s0, 92);
                    lw(a0, s0, 96);
                    if (a0 != 0) {
                        // 0x004218a0
                        charge(ctx, 3);
                        jal(ctx, 0x4218A0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s0, 96);
                    }
                    // 0x004218ac
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            }
            break;
        case 0x42181Cu:  // table[2]
            goto L_0042181c;
        case 0x4218BCu:  // table[3]
            // 0x004218bc
            charge(ctx, 5);
            lw(a0, s0, 92);
            jal(ctx, 0x4218C0u, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x004218d0
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, 0);
            }
            break;
        case 0x4218E0u:  // table[4]
            // 0x004218e0
            charge(ctx, 14);
            a0 = 1;
            a1 = a0;
            jal(ctx, 0x4218E8u, gen::fn_MT_Scene_Load_003b5760);
            a0 = 1;
            a1 = a0;
            jal(ctx, 0x4218F8u, gen::fn_sub_1B6EB0_001b6eb0);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x421908u, gen::fn_sub_3B5980_003b5980);
            v0 = 5;
            sw(v0, s0, 0);
        L_00421918:
            charge(ctx, 5);
            jal(ctx, 0x421918u, gen::fn_sub_3B5A10_003b5a10);
            v1 = 1;
            if (v0 == v1) {
                // 0x0042192c
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s0, 0);
            }
            break;
        case 0x421918u:  // table[5]
            goto L_00421918;
        case 0x42193Cu:  // table[6]
            // 0x0042193c
            charge(ctx, 4);
            jal(ctx, 0x42193Cu, gen::fn_sub_1A1150_001a1150);
            a2 = addiu(sp, 0x40);
            a1 = 8;
            for (;;) {
                // 0x0042194c
                charge(ctx, 9);
                lw(a0, v0, 0);
                lw(v1, v0, 4);
                v0 = addiu(v0, 8);
                a1 = addiu(a1, -1);
                sw(a0, a2, 0);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00421970
            charge(ctx, 25);
            jal(ctx, 0x421970u, gen::fn_sub_198590_00198590);
            s2 = v0;
            jal(ctx, 0x42197Cu, gen::fn_sub_1A1190_001a1190);
            a0 = s2;
            mov_s(f12, f0);
            jal(ctx, 0x42198Cu, gen::fn_sub_1A4580_001a4580);
            jal(ctx, 0x421994u, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            a1 = addiu(sp, 0x40);
            a2 = 0;
            jal(ctx, 0x4219A8u, gen::fn_sub_4CB7F0_004cb7f0);
            a0 = 4;
            a1 = 5;
            a2 = 12;
            a3 = 31;
            jal(ctx, 0x4219C0u, gen::fn_clndIsDateInRange_0017e480);
            v1 = 1;
            if (v0 != v1) {
                // 0x004219d4
                charge(ctx, 9);
                a0 = 4;
                a1 = 5;
                a2 = 12;
                a3 = 31;
                jal(ctx, 0x4219E4u, gen::fn_clndIsDateInRange_0017e480);
                a1 = 1;
                if (v0 == a1) {
                    goto L_00421a18;
                }
                // 0x004219f8
                charge(ctx, 8);
                a0 = 3;
                a2 = a0;
                a3 = 5;
                jal(ctx, 0x421A04u, gen::fn_clndIsDateInRange_0017e480);
                a0 = 1;
                if (v0 == a0) {
                    goto L_00421a18;
                }
                // 0x00421a30
                charge(ctx, 8);
                a1 = a0;
                a2 = 2;
                a3 = 28;
                jal(ctx, 0x421A3Cu, gen::fn_clndIsDateInRange_0017e480);
                a1 = 1;
                if (v0 == a1) {
                    // 0x00421a50
                    charge(ctx, 3);
                    a0 = 80;
                    jal(ctx, 0x421A54u, gen::fn_sub_1099D0_001099d0);
                }
                goto L_00421a5c;
            }
        L_00421a18:
            charge(ctx, 6);
            a0 = 25;
            a1 = 1;
            jal(ctx, 0x421A20u, gen::fn_sub_1099D0_001099d0);
        L_00421a5c:
            charge(ctx, 2);
            v0 = 7;
            sw(v0, s0, 0);
        L_00421a64:
            charge(ctx, 3);
            lw(v0, s0, 144);
            if (v0 != 0) {
                // 0x00421a70
                charge(ctx, 1);
                sw(zero, s0, 144);
            }
            // 0x00421a74
            charge(ctx, 8);
            a0 = s1;
            lb(a1, s0, 60);
            jal(ctx, 0x421A7Cu, gen::fn_Y_LMap_CreateLmapModelTask_00425c60);
            sw(v0, s0, 144);
            lw(v0, s0, 64);
            if (v0 != 0) {
                // 0x00421a94
                charge(ctx, 1);
                sw(zero, s0, 64);
            }
            // 0x00421a98
            charge(ctx, 16);
            lw(v0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
            a0 = s1;
            lb(a1, v0, 0);
            lb(a2, v0, 1);
            lb(a3, v0, 2);
            lb(t0, v0, 3);
            lb(t1, v0, 4);
            lb(t2, v0, 5);
            lb(t3, s0, 60);
            jal(ctx, 0x421ABCu, gen::fn_Y_LMap_CreateLMapMenuTask_004238b0);
            sw(v0, s0, 64);
            v0 = 8;
            sw(v0, s0, 0);
            break;
        case 0x421A64u:  // table[7]
            goto L_00421a64;
        case 0x421AD8u:  // table[8]
            // 0x00421ad8
            charge(ctx, 15);
            lw(a0, s0, 64);
            jal(ctx, 0x421ADCu, gen::fn_sub_423B50_00423b50);
            lw(a0, s0, 144);
            a1 = v0;
            jal(ctx, 0x421AECu, gen::fn_sub_426040_00426040);
            lw(a0, s0, 144);
            jal(ctx, 0x421AF8u, gen::fn_sub_426070_00426070);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            v0 = 1;
            if (v1 != v0) {
                // 0x00421b14
                charge(ctx, 5);
                lw(a0, s0, 64);
                jal(ctx, 0x421B18u, gen::fn_sub_423BF0_00423bf0);
                if (v0 != 0) {
                    // 0x00421b28
                    charge(ctx, 3);
                    lw(a0, s0, 112);
                    if (a0 != 0) {
                        // 0x00421b34
                        charge(ctx, 3);
                        jal(ctx, 0x421B34u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s0, 112);
                    }
                    // 0x00421b40
                    charge(ctx, 6);
                    jal(ctx, 0x421B40u, gen::fn_sub_1085C0_001085c0);
                    v0 = 9;
                    sw(v0, s0, 0);
                }
            }
            break;
        case 0x421B58u:  // table[9]
            // 0x00421b58
            charge(ctx, 4);
            jal(ctx, 0x421B58u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x00421b68
                charge(ctx, 8);
                lw(a0, s0, 64);
                jal(ctx, 0x421B6Cu, gen::fn_sub_423FC0_00423fc0);
                lw(a1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
                lb(v1, a1, 9);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00421b88
                    charge(ctx, 4);
                    lw(a0, s0, 64);
                    lb(a1, a1, 10);
                    jal(ctx, 0x421B90u, gen::fn_sub_423C10_00423c10);
                }
                // 0x00421b98
                charge(ctx, 4);
                v0 = 10;
                sw(v0, s0, 0);
            }
            break;
        case 0x421BA8u:  // table[10]
            // 0x00421ba8
            charge(ctx, 15);
            lw(a0, s0, 64);
            jal(ctx, 0x421BACu, gen::fn_sub_423B50_00423b50);
            lw(a0, s0, 144);
            a1 = v0;
            jal(ctx, 0x421BBCu, gen::fn_sub_426040_00426040);
            lw(a0, s0, 64);
            jal(ctx, 0x421BC8u, gen::fn_sub_423B70_00423b70);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            v0 = 1;
            if (v1 == v0) {
                // 0x00421be4
                charge(ctx, 27);
                lw(a0, s0, 144);
                jal(ctx, 0x421BE8u, gen::fn_sub_426050_00426050);
                lw(a0, s0, 64);
                jal(ctx, 0x421BF4u, gen::fn_sub_423B50_00423b50);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                a3 = addiu(v0, 1);
                a0 = 10;
                lw(a1, s0, 104);
                lw(a2, s0, 100);
                jal(ctx, 0x421C14u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                sw(v0, s0, 92);
                lw(a0, s0, 64);
                jal(ctx, 0x421C24u, gen::fn_sub_423B50_00423b50);
                lw(a0, s0, 144);
                lb(a1, s0, 60);
                a2 = v0;
                jal(ctx, 0x421C38u, gen::fn_sub_425D30_00425d30);
                v0 = 11;
                sw(v0, s0, 0);
            }
            break;
        case 0x421C50u:  // table[11]
            // 0x00421c50
            charge(ctx, 2);
            v0 = 12;
            sw(v0, s0, 0);
        L_00421c58:
            charge(ctx, 5);
            lw(a0, s0, 92);
            jal(ctx, 0x421C5Cu, gen::fn_kwlnTaskExists_00195460);
            if (v0 == 0) {
                // 0x00421c6c
                charge(ctx, 15);
                lw(a0, s0, 64);
                jal(ctx, 0x421C70u, gen::fn_sub_423B50_00423b50);
                sb(v0, s0, 60);
                lw(a0, s0, 144);
                a1 = dsll32(v0, 24);
                a1 = dsra32(a1, 24);
                jal(ctx, 0x421C88u, gen::fn_sub_425D10_00425d10);
                v0 = 10;
                sw(v0, s0, 0);
                lb(v1, gp, -17984);  // 0x7CE6B0
                v0 = 1;
                if (v1 != v0) {
                    // 0x00421d34
                    charge(ctx, 5);
                    lw(a0, s0, 64);
                    jal(ctx, 0x421D38u, gen::fn_sub_423BA0_00423ba0);
                } else {
                    // 0x00421ca8
                    charge(ctx, 8);
                    v0 = 14;
                    sw(v0, s0, 0);
                    lw(a0, s0, 64);
                    jal(ctx, 0x421CB4u, gen::fn_kwlnTaskExists_00195460);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00421cc8
                        charge(ctx, 3);
                        lw(a0, s0, 64);
                        jal(ctx, 0x421CCCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x00421cd4
                    charge(ctx, 8);
                    jal(ctx, 0x421CD4u, gen::fn_sub_426090_00426090);  // -> the lmap_model_move task slot
                    lw(a0, v0, 0);
                    jal(ctx, 0x421CE0u, gen::fn_kwlnTaskExists_00195460);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00421cf4
                        charge(ctx, 5);
                        jal(ctx, 0x421CF4u, gen::fn_sub_426090_00426090);  // -> the lmap_model_move task slot
                        lw(a0, v0, 0);
                        jal(ctx, 0x421D00u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x00421d08
                    charge(ctx, 6);
                    lw(a0, s0, 144);
                    jal(ctx, 0x421D0Cu, gen::fn_kwlnTaskExists_00195460);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00421d20
                        charge(ctx, 5);
                        lw(a0, s0, 144);
                        jal(ctx, 0x421D24u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                }
            }
            break;
        case 0x421C58u:  // table[12]
            goto L_00421c58;
        case 0x421D48u:  // table[14]
            // 0x00421d48
            charge(ctx, 2);
            v0 = 15;
            sw(v0, s0, 0);
            break;
        case 0x421D50u:  // table[13, 15, 16]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00421d50 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00421D70 sub_421D70 -- 112 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapDestroy] The destroy callback of "y_lmap proc": releases the scene, the shared record and the work.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00421d70
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, kTaskWork);
    jal(ctx, 0x421D8Cu, gen::fn_sub_421FB0_00421fb0);
    jal(ctx, 0x421D94u, gen::fn_sub_3B5AB0_003b5ab0);
    s0 = 0x960000;
    s0 = addiu(s0, 380);  // &0x96017C
    lw(a0, s1, 104);
    lw(v0, s0, 0);  // 0x96017C RwFree slot
    jalr(ctx, 0x421DACu, v0.u());
    lw(a0, s2, kTaskWork);
    lw(v0, s0, 0);  // 0x96017C RwFree slot
    jalr(ctx, 0x421DBCu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00421DE0 Y_LMap_CreateLmapTask -- 272 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_CreateLmapTask(a, b, c, d, e): RwCalloc'd work with the five bytes, task "y_lmap proc".
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateLmapTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00421de0
    enter(ctx, 28);  // entry check point + this block's cycles
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
    s5 = t0;
    a0 = addiu(gp, -17996);  // &0x7CE6A4
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x421E20u, gen::fn_memset_00521408);
    a0 = 1;
    a1 = 156;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x421E3Cu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00421e5c
        charge(ctx, 25);
        a0 = 0;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 17352);  // "y_lmap proc"
        a3 = 0x420000;
        a3 = addiu(a3, 6000);  // &Y_LMap_UpdateLmapTask
        t0 = 0x420000;
        t0 = addiu(t0, 7536);  // &sub_421D70
        t1 = s0;
        jal(ctx, 0x421E80u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(zero, s0, 0);
        v1 = 1;
        sb(v1, s0, 16);
        sb(s3, s0, 56);
        sb(s2, s0, 57);
        sb(s1, s0, 58);
        sb(s5, s0, 59);
        sb(s4, s0, 60);
        v1 = 6;
        sb(v1, s0, 17);
        lb(a0, s0, 59);
        v1 = 2;
        if (a0 == v1) {
            // 0x00421ec0
            charge(ctx, 1);
            sb(v1, s0, 17);
        }
        // 0x00421ec4
        charge(ctx, 1);
        sw(v0, gp, -17996);  // 0x7CE6A4
    } else {
        // 0x00421e50
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00421ec8 (the shared epilogue, written out on this path)
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

// 0x00421EF0 sub_421EF0 -- 24 bytes; leaf frame (no stack)
// [lmapIsPhase15] Whether the task's record (+0x3C) has phase word 15.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00421ef0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 0);
    v0 = v0 ^ 0xF;
    v0 = sltiu(v0, 1);
}

// 0x00421F10 sub_421F10 -- 16 bytes; leaf frame (no stack)
// [lmapGetRecord112] The word at +0x70 of the task's record.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00421f10
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 112);
}

// 0x00421F20 sub_421F20 -- 132 bytes; frame 0x10: ra sp+0x0
// [lmapAllocShared] RwCalloc(1, 11) into gp-0x4648 and zeroes its bytes 0..5 and 7..10.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00421f20
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 11;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x421F3Cu, v0.u());
    sw(v0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v0, 0);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 1);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 2);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 3);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 4);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 5);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 7);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 8);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 9);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(zero, v1, 10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00421FB0 sub_421FB0 -- 48 bytes; frame 0x10: ra sp+0x0
// [lmapFreeShared] RwFree(gp-0x4648).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421FB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00421fb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x421FC4u, v0.u());
    sw(zero, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00421FE0 sub_421FE0 -- 444 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapEase] Eases from $a1 to $a2 (s16) over frame $a3 of $a4 (s16) by kind $a0 (s8): 0 linear (integer
// math), 1 sine ease-out, 2 cosine ease-in (gp-0x7DB8 = pi as the half-period scale); frame == length gives the end
// value; another kind gives -1.0. Result in $f0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_421FE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x00421fe0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a2 = dsll32(t0, 16);
    a2 = dsra32(a2, 16);
    a1 = dsll32(a3, 16);
    a1 = dsra32(a1, 16);
    if (a1 != a2) {
        // 0x00422024
        charge(ctx, 5);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = 2;
        if (v1 == v0) {
            // 0x00422108
            charge(ctx, 29);
            v0 = sll(a2, 1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
            div_s(f1, f0, f1);
            mtc1(a3, f0);
            cvt_s_w(f0, f0);
            mul_s(f12, f0, f1);
            jal(ctx, 0x422130u, gen::fn_cosf_0052e6d8);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s1, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            mtc1(v0, f1);
            cvt_s_w(f3, f1);
            mtc1(s0, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
        } else {
            // 0x00422038
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00422094
                charge(ctx, 29);
                v0 = sll(a2, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
                div_s(f1, f0, f1);
                mtc1(a3, f0);
                cvt_s_w(f0, f0);
                mul_s(f12, f0, f1);
                jal(ctx, 0x4220BCu, gen::fn_sinf_0052e878);
                v1 = dsll32(s0, 16);
                v1 = dsra32(v1, 16);
                v0 = dsll32(s1, 16);
                v0 = dsra32(v0, 16);
                v0 = subu(v1, v0);
                mtc1(v0, f1);
                cvt_s_w(f3, f1);
                mtc1(s1, f1);
                cvt_s_w(f2, f1);
                mtc1(zero, f1);
                adda_s(f1, f2);
                madd_s(f0, f3, f0);
            } else {
                // 0x00422044
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00422054
                    charge(ctx, 16);
                    v1 = dsll32(s1, 16);
                    v1 = dsra32(v1, 16);
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = subu(v0, v1);
                    mult(v0, a1, v0);
                    div(v0, a2);
                    mflo(v0);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                } else {
                    // 0x0042204c
                    charge(ctx, 2);
                    // 0x0042217c
                    charge(ctx, 2);
                    v0 = lui(0xBF80);
                    mtc1(v0, f0);
                }
            }
        }
    } else {
        // 0x00422010
        charge(ctx, 5);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00422184 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004221A0 sub_4221A0 -- 304 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// [lmapEaseF] The float version: from $f12 to $f13, frame $f14 of $f15, kind $a0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4221A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004221a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f20, f12);
    mov_s(f21, f13);
    c_eq_s(f14, f15);
    if (!cond(ctx)) {
        // 0x004221d0
        charge(ctx, 5);
        v1 = dsll32(a0, 24);
        v1 = dsra32(v1, 24);
        v0 = 2;
        if (v1 == v0) {
            // 0x00422268
            charge(ctx, 18);
            v0 = 0x40000000;
            mtc1(v0, f0);
            mul_s(f1, f0, f15);
            lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
            div_s(f0, f0, f1);
            mul_s(f12, f0, f14);
            jal(ctx, 0x42228Cu, gen::fn_cosf_0052e6d8);
            sub_s(f2, f21, f20);
            mtc1(zero, f1);
            adda_s(f1, f21);
            msub_s(f0, f2, f0);
        } else {
            // 0x004221e4
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x00422220
                charge(ctx, 18);
                v0 = 0x40000000;
                mtc1(v0, f0);
                mul_s(f1, f0, f15);
                lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
                div_s(f0, f0, f1);
                mul_s(f12, f0, f14);
                jal(ctx, 0x422244u, gen::fn_sinf_0052e878);
                sub_s(f2, f21, f20);
                mtc1(zero, f1);
                adda_s(f1, f20);
                madd_s(f0, f2, f0);
            } else {
                // 0x004221f0
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00422200
                    charge(ctx, 8);
                    sub_s(f0, f21, f20);
                    mul_s(f0, f14, f0);
                    div_s(f0, f0, f15);
                    add_s(f0, f20, f0);
                } else {
                    // 0x004221f8
                    charge(ctx, 2);
                    // 0x004222b0
                    charge(ctx, 2);
                    v0 = lui(0xBF80);
                    mtc1(v0, f0);
                }
            }
        }
    } else {
        // 0x004221c4
        charge(ctx, 3);
        mov_s(f0, f21);
    }
    // 0x004222b8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004222D0 sub_4222D0 -- 924 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapEase2] Two eased values at once (x from $a2 to $a3, y from $a4 to $a5, frame $a6 of $a7, kind $a1)
// stored as two floats at $a0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4222D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x004222d0
    enter(ctx, 24);  // entry check point + this block's cycles
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
    s7 = a0;
    fp = a1;
    s4 = a2;
    s3 = a3;
    s5 = t0;
    s2 = t1;
    s1 = t2;
    s0 = dsll32(t3, 16);
    s0 = dsra32(s0, 16);
    s6 = dsll32(s1, 16);
    s6 = dsra32(s6, 16);
    if (s6 != s0) {
        // 0x00422344
        charge(ctx, 5);
        a0 = dsll32(fp, 24);
        a0 = dsra32(a0, 24);
        v1 = 2;
        if (a0 == v1) {
            // 0x00422428
            charge(ctx, 29);
            v0 = sll(s0, 1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
            div_s(f1, f0, f1);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            mul_s(f12, f0, f1);
            jal(ctx, 0x422450u, gen::fn_cosf_0052e6d8);
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            v1 = dsll32(s4, 16);
            v1 = dsra32(v1, 16);
            v1 = subu(a0, v1);
            mtc1(v1, f1);
            cvt_s_w(f3, f1);
            mtc1(s3, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
        } else {
            // 0x00422358
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x004223b4
                charge(ctx, 29);
                v0 = sll(s0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
                div_s(f1, f0, f1);
                mtc1(s1, f0);
                cvt_s_w(f0, f0);
                mul_s(f12, f0, f1);
                jal(ctx, 0x4223DCu, gen::fn_sinf_0052e878);
                a0 = dsll32(s3, 16);
                a0 = dsra32(a0, 16);
                v1 = dsll32(s4, 16);
                v1 = dsra32(v1, 16);
                v1 = subu(a0, v1);
                mtc1(v1, f1);
                cvt_s_w(f3, f1);
                mtc1(s4, f1);
                cvt_s_w(f2, f1);
                mtc1(zero, f1);
                adda_s(f1, f2);
                madd_s(f0, f3, f0);
            } else {
                // 0x00422364
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x00422374
                    charge(ctx, 16);
                    a0 = dsll32(s4, 16);
                    a0 = dsra32(a0, 16);
                    v1 = dsll32(s3, 16);
                    v1 = dsra32(v1, 16);
                    v1 = subu(v1, a0);
                    mult(v1, s6, v1);
                    div(v1, s0);
                    mflo(v1);
                    v1 = addu(a0, v1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                } else {
                    // 0x0042236c
                    charge(ctx, 2);
                    // 0x0042249c
                    charge(ctx, 2);
                    v1 = lui(0xBF80);
                    mtc1(v1, f0);
                }
            }
        }
    } else {
        // 0x00422330
        charge(ctx, 5);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x004224a4
    charge(ctx, 3);
    swc1(f0, sp, 0xA8);
    if (s6 != s0) {
        // 0x004224c4
        charge(ctx, 5);
        a0 = dsll32(fp, 24);
        a0 = dsra32(a0, 24);
        v1 = 2;
        if (a0 == v1) {
            // 0x004225a8
            charge(ctx, 29);
            v0 = sll(s0, 1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
            div_s(f1, f0, f1);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            mul_s(f12, f0, f1);
            jal(ctx, 0x4225D0u, gen::fn_cosf_0052e6d8);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            v1 = dsll32(s5, 16);
            v1 = dsra32(v1, 16);
            v1 = subu(a0, v1);
            mtc1(v1, f1);
            cvt_s_w(f3, f1);
            mtc1(s2, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            msub_s(f0, f3, f0);
        } else {
            // 0x004224d8
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x00422534
                charge(ctx, 29);
                v0 = sll(s0, 1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, -32184);  // 0x7CAF38 gp-0x7DB8: pi
                div_s(f1, f0, f1);
                mtc1(s1, f0);
                cvt_s_w(f0, f0);
                mul_s(f12, f0, f1);
                jal(ctx, 0x42255Cu, gen::fn_sinf_0052e878);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                v1 = dsll32(s5, 16);
                v1 = dsra32(v1, 16);
                v1 = subu(a0, v1);
                mtc1(v1, f1);
                cvt_s_w(f3, f1);
                mtc1(s5, f1);
                cvt_s_w(f2, f1);
                mtc1(zero, f1);
                adda_s(f1, f2);
                madd_s(f0, f3, f0);
            } else {
                // 0x004224e4
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x004224f4
                    charge(ctx, 16);
                    a0 = dsll32(s5, 16);
                    a0 = dsra32(a0, 16);
                    v1 = dsll32(s2, 16);
                    v1 = dsra32(v1, 16);
                    v1 = subu(v1, a0);
                    mult(v1, s6, v1);
                    div(v1, s0);
                    mflo(v1);
                    v1 = addu(a0, v1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                } else {
                    // 0x004224ec
                    charge(ctx, 2);
                    // 0x0042261c
                    charge(ctx, 2);
                    v1 = lui(0xBF80);
                    mtc1(v1, f0);
                }
            }
        }
    } else {
        // 0x004224b0
        charge(ctx, 5);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00422624 (the shared epilogue, written out on this path)
    charge(ctx, 18);
    swc1(f0, sp, 0xAC);
    lwc1(f1, sp, 0xA8);
    lwc1(f0, sp, 0xAC);
    swc1(f1, s7, 0);
    swc1(f0, s7, 4);
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

// 0x004229A0 sub_4229A0 -- 44 bytes; frame 0x10: ra sp+0x0
// [boxfillDestroy] The destroy callback of "y_boxfill proc": RwFree(work).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4229A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004229a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x4229B4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004229D0 Y_LMap_CreateBoxfillTasks -- 568 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Y_LMap_CreateBoxfillTasks: creates "y_boxfill proc" (four kwlnTaskCreate call sites by the caller's kind)
// with an RwCalloc'd record, sized from frFontGetStyleSize.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateBoxfillTasks(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20};
    // 0x004229d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0x68);
    s3 = a2;
    lwc1(f20, sp, 0x6C);
    s1 = 0;
    a0 = 1;
    a1 = 320;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x422A14u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00422a34
        charge(ctx, 5);
        v1 = dsll32(s3, 24);
        v1 = dsra32(v1, 24);
        v0 = 3;
        if (v1 == v0) {
            // 0x00422b18
            charge(ctx, 12);
            a0 = s2;
            a1 = 0x6B0000;
            a1 = addiu(a1, 17368);  // "y_boxfill proc"
            a2 = 6310;
            a3 = 0x420000;
            a3 = addiu(a3, 9840);  // &sub_422670
            t0 = 0x420000;
            t0 = addiu(t0, 10656);  // &sub_4229A0
            t1 = s0;
            jal(ctx, 0x422B3Cu, gen::fn_kwlnTaskCreate_00194b20);
            s1 = v0;
        } else {
            // 0x00422a48
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00422ae0
                charge(ctx, 14);
                a0 = s2;
                a1 = 0x6B0000;
                a1 = addiu(a1, 17368);  // "y_boxfill proc"
                a2 = 6311;
                a3 = 0x420000;
                a3 = addiu(a3, 9840);  // &sub_422670
                t0 = 0x420000;
                t0 = addiu(t0, 10656);  // &sub_4229A0
                t1 = s0;
                jal(ctx, 0x422B04u, gen::fn_kwlnTaskCreate_00194b20);
                s1 = v0;
            } else {
                // 0x00422a54
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00422aa8
                    charge(ctx, 14);
                    a0 = s2;
                    a1 = 0x6B0000;
                    a1 = addiu(a1, 17368);  // "y_boxfill proc"
                    a2 = 4197;
                    a3 = 0x420000;
                    a3 = addiu(a3, 9840);  // &sub_422670
                    t0 = 0x420000;
                    t0 = addiu(t0, 10656);  // &sub_4229A0
                    t1 = s0;
                    jal(ctx, 0x422ACCu, gen::fn_kwlnTaskCreate_00194b20);
                    s1 = v0;
                } else {
                    // 0x00422a60
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00422a70
                        charge(ctx, 14);
                        a0 = s2;
                        a1 = 4207;
                        a2 = 0x6B0000;
                        a2 = addiu(a2, 17368);  // "y_boxfill proc"
                        a3 = 0x420000;
                        a3 = addiu(a3, 9840);  // &sub_422670
                        t0 = 0x420000;
                        t0 = addiu(t0, 10656);  // &sub_4229A0
                        t1 = s0;
                        jal(ctx, 0x422A94u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
                        s1 = v0;
                    } else {
                        // 0x00422a68
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00422b48
        charge(ctx, 6);
        sb(zero, s0, 0);
        a1 = 0;
        a0 = 255;
        v1 = 128;
        for (;;) {
            // 0x00422b8c
            charge(ctx, 5);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v0 = slti(v0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00422b60
            charge(ctx, 11);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            sb(a0, v0, 273);
            sb(a0, v0, 274);
            sb(a0, v0, 272);
            sb(v1, v0, 275);
            v0 = addiu(a1, 1);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
        }
        // 0x00422ba0
        charge(ctx, 17);
        v0 = 0x3F800000;
        sw(v0, s0, 304);
        a0 = 1;
        jal(ctx, 0x422BACu, gen::fn_frFontGetStyleSize_003b35c0);
        sw(v0, s0, 300);
        a0 = 1;
        jal(ctx, 0x422BBCu, gen::fn_frFontGetStyleSize_003b35c0);
        v0 = sll(v0, 3);
        sw(v0, s0, 296);
        lwc1(f0, sp, 0x68);
        swc1(f0, s0, 308);
        swc1(f20, s0, 312);
        sh(zero, s0, 316);
        sb(zero, s0, 318);
        v0 = s1;
    } else {
        // 0x00422a28
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00422be4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00422C10 sub_422C10 -- 28 bytes; leaf frame (no stack)
// [boxfillSetAlpha] Record +304 = (float)$a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_422C10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0};
    // 0x00422c10
    enter(ctx, 7);  // entry check point + this block's cycles
    mtc1(a1, f0);
    cvt_s_w(f0, f0);
    lw(v1, a0, kTaskWork);
    swc1(f0, v1, 304);
}

// 0x00422C30 sub_422C30 -- 88 bytes; frame 0x20
// [boxfillSetRect] Stores the 8-byte $a1 (two floats) at record +308 / +312 and words 2, 3 of the 16-byte
// rectangle at $a2 to +296 / +300 (copied through its 32-byte frame).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_422C30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00422c30
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(a1, sp, 0x8);
    lwc1(f3, a2, 0);
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 8);
    lwc1(f0, a2, 12);
    swc1(f3, sp, 0x10);
    swc1(f2, sp, 0x14);
    swc1(f1, sp, 0x18);
    swc1(f0, sp, 0x1C);
    lw(a0, a0, kTaskWork);
    lwc1(f0, sp, 0x8);
    swc1(f0, a0, 308);
    lwc1(f0, sp, 0xC);
    swc1(f0, a0, 312);
    lw(v1, sp, 0x1C);
    sw(v1, a0, 300);
    lw(v1, sp, 0x18);
    sw(v1, a0, 296);
    sp = addiu(sp, 0x20);
}

// 0x00422C90 sub_422C90 -- 64 bytes; leaf frame (no stack)
// [boxfillSetColor] The four corner colours (r, g, b, a = $a1..$a4) at record +272 + 4 i.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_422C90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00422c90
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    t1 = 0;
    for (;;) {
        // 0x00422cbc
        charge(ctx, 3);
        v1 = slti(t1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00422ca0
        charge(ctx, 7);
        v1 = sll(t1, 2);
        v1 = addu(a0, v1);
        sb(a1, v1, 272);
        sb(a2, v1, 273);
        sb(a3, v1, 274);
        sb(t0, v1, 275);
        t1 = addiu(t1, 1);
    }
    // 0x00422cc8
    charge(ctx, 2);
}

// 0x00422CD0 sub_422CD0 -- 16 bytes; leaf frame (no stack)
// [boxfillSetFlag] Record byte +318 = $a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_422CD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00422cd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 318);
}

// 0x00422CE0 Y_LMap_UpdateLMapMenuTask -- 2736 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_UpdateLMapMenuTask: the "y_LMapMenu proc" update (sprites, cursor sounds, selection).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_UpdateLMapMenuTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00422ce0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    s0 = a0;
    lw(s2, a0, kTaskWork);
    lb(v0, s2, 0);
    at = sltiu(v0, 14);
    if (at != 0) {
        // 0x00422d24
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -15840);  // "@-B"
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x422D40u:  // table[0]
            // 0x00422d40
            charge(ctx, 16);
            jal(ctx, 0x422D40u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
            lw(a0, v0, 0);
            jal(ctx, 0x422D4Cu, gen::fn_sub_421F10_00421f10);
            a0 = v0;
            a1 = 12;
            a2 = addiu(sp, 0xBC);
            jal(ctx, 0x422D60u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
            a0 = v0;
            jal(ctx, 0x422D6Cu, gen::fn_sprCreateHandleFromData_00112420);
            sw(v0, s2, 200);
            v0 = 1;
            sb(v0, s2, 0);
        L_00422d80:
            charge(ctx, 6);
            lw(a0, s2, 200);
            jal(ctx, 0x422D84u, gen::fn_sprFileIsReady_00111f30);
            v1 = 1;
            if (v0 == v1) {
                // 0x00422d98
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00422e98
                    charge(ctx, 3);
                    v0 = slti(s1, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00422da4
                    charge(ctx, 4);
                    a2 = addiu(s1, 1);
                    v0 = 6;
                    if (a2 != v0) {
                        // 0x00422e04
                        charge(ctx, 3);
                        v0 = 7;
                        if (a2 != v0) {
                            // 0x00422e60
                            charge(ctx, 3);
                            v0 = 24;
                            if (a2 != v0) {
                                // 0x00422e6c
                                charge(ctx, 10);
                                v0 = sll(s1, 2);
                                v0 = addu(s2, v0);
                                s0 = addiu(v0, 208);
                                a0 = 0;
                                lw(a1, s2, 200);
                                jal(ctx, 0x422E80u, gen::fn_sprCreateHandle_001158b0);
                                sw(v0, s0, 0);
                                v1 = 255;
                                sb(v1, v0, 24);
                            }
                        } else {
                            // 0x00422e10
                            charge(ctx, 3);
                            s0 = 0;
                            for (;;) {
                                // 0x00422e4c
                                charge(ctx, 3);
                                v0 = slti(s0, 6);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x00422e1c
                                charge(ctx, 12);
                                v0 = sll(s0, 2);
                                v0 = addu(s2, v0);
                                s3 = addiu(v0, 328);
                                a0 = 0;
                                lw(a1, s2, 200);
                                a2 = 7;
                                jal(ctx, 0x422E34u, gen::fn_sprCreateHandle_001158b0);
                                sw(v0, s3, 0);
                                v1 = 255;
                                sb(v1, v0, 24);
                                s0 = addiu(s0, 1);
                            }
                            // 0x00422e58
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x00422db4
                        charge(ctx, 3);
                        s0 = 0;
                        for (;;) {
                            // 0x00422df0
                            charge(ctx, 3);
                            v0 = slti(s0, 6);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00422dc0
                            charge(ctx, 12);
                            v0 = sll(s0, 2);
                            v0 = addu(s2, v0);
                            s3 = addiu(v0, 304);
                            a0 = 0;
                            lw(a1, s2, 200);
                            a2 = 6;
                            jal(ctx, 0x422DD8u, gen::fn_sprCreateHandle_001158b0);
                            sw(v0, s3, 0);
                            v1 = 255;
                            sb(v1, v0, 24);
                            s0 = addiu(s0, 1);
                        }
                        // 0x00422dfc
                        charge(ctx, 2);
                    }
                    // 0x00422e94
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x00422ea4
                charge(ctx, 4);
                a1 = 0;
                v1 = lui(0xC35B);
                for (;;) {
                    // 0x00422ee0
                    charge(ctx, 3);
                    v0 = slti(a1, 6);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00422eb4
                    charge(ctx, 11);
                    v0 = sll(a1, 3);
                    a0 = addu(s2, v0);
                    sw(v1, a0, 396);
                    v0 = sll(a1, 5);
                    v0 = addu(v0, a1);
                    v0 = addiu(v0, 233);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, a0, 400);
                    a1 = addiu(a1, 1);
                }
                // 0x00422eec
                charge(ctx, 23);
                a0 = 0;
                lw(a1, s2, 200);
                a2 = 24;
                jal(ctx, 0x422EF8u, gen::fn_sprCreateHandle_001158b0);
                s0 = v0;
                v1 = 0x42A20000;
                sw(v1, v0, 16);
                sw(zero, v0, 20);
                v1 = 0x41200000;
                sw(v1, v0, 44);
                sb(zero, v0, 24);
                a0 = s0;
                a1 = 1;
                jal(ctx, 0x422F24u, gen::fn_sub_1127D0_001127d0);
                a0 = s0;
                jal(ctx, 0x422F30u, gen::fn_sub_115980_00115980);
                v0 = 2;
                sb(v0, s2, 0);
            }
        L_00423758:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x422D80u:  // table[1]
            goto L_00422d80;
        case 0x422F48u:  // table[2]
            // 0x00422f48
            charge(ctx, 6);
            sh(zero, s2, 352);
            sh(zero, s2, 356);
            sh(zero, s2, 354);
            a0 = 0;
            for (;;) {
                // 0x00422f90
                charge(ctx, 3);
                v0 = slti(a0, 6);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00422f60
                charge(ctx, 12);
                v0 = sll(a0, 1);
                v0 = addu(v0, a0);
                v0 = sll(v0, 1);
                v0 = addu(s2, v0);
                sh(zero, v0, 358);
                sh(zero, v0, 362);
                sh(zero, v0, 360);
                v0 = sll(a0, 2);
                v1 = addu(v0, a0);
                v0 = addu(s2, a0);
                sb(v1, v0, 444);
                a0 = addiu(a0, 1);
            }
            // 0x00422f9c
            charge(ctx, 23);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x422FA8u, gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x422FD4u, gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(ctx, 0x422FE0u, gen::fn_sub_115980_00115980);
            v0 = 3;
            sb(v0, s2, 0);
            goto L_00423758;
        case 0x422FF8u:  // table[3]
            // 0x00422ff8
            charge(ctx, 22);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x423004u, gen::fn_sprCreateHandle_001158b0);
            s1 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x423030u, gen::fn_sub_1127D0_001127d0);
            a0 = s1;
            jal(ctx, 0x42303Cu, gen::fn_sub_115980_00115980);
            lb(v0, s2, 149);
            if (v0 != 0) {
                // 0x0042305c
                charge(ctx, 20);
                s5 = 0;
                v1 = 0x43D50000;
                lw(v0, s2, 208);
                sw(v1, v0, 16);
                v1 = 0x43CB0000;
                lw(v0, s2, 208);
                sw(v1, v0, 20);
                lh(v1, s2, 356);
                v0 = 255;
                v1 = subu(v0, v1);
                lw(v0, s2, 208);
                sb(v1, v0, 24);
                lb(v1, s2, 142);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                lh(v1, s2, 352);
                if (v1 != a0) {
                    // 0x004230bc
                    charge(ctx, 7);
                    v0 = sll(v1, 8);
                    v0 = subu(v0, v1);
                    div(v0, a0);
                    mflo(v0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                } else {
                    // 0x004230ac
                    charge(ctx, 4);
                    v0 = 0x437F0000;
                    mtc1(v0, f1);
                }
                // 0x004230d8
                charge(ctx, 6);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x00423108
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x004230f0
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x00423120
                charge(ctx, 9);
                v0 = v1 & 0xFF;
                sh(v0, s2, 356);
                lb(v1, s2, 142);
                v0 = sll(v1, 2);
                a0 = addu(v0, v1);
                lh(v1, s2, 352);
                v0 = slt(v1, a0);
                if (v0 != 0) {
                    // 0x00423150
                    charge(ctx, 3);
                    v0 = addiu(v1, 1);
                    sh(v0, s2, 352);
                    s5 = 1;
                } else {
                    // 0x00423144
                    charge(ctx, 3);
                    sh(a0, s2, 352);
                }
                // 0x0042315c
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x00423238
                    charge(ctx, 4);
                    lb(v0, s2, 142);
                    v0 = slt(s3, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00423168
                    charge(ctx, 5);
                    v0 = addu(s2, s3);
                    v1 = addiu(v0, 444);
                    lb(v0, v0, 444);
                    if (i64(v0) > 0) {
                        // 0x00423228
                        charge(ctx, 3);
                        v0 = addiu(v0, -1);
                        sb(v0, v1, 0);
                        s5 = 1;
                    } else {
                        // 0x0042317c
                        charge(ctx, 38);
                        v0 = sll(s3, 1);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 1);
                        v0 = addu(s2, v0);
                        s7 = addiu(v0, 360);
                        lh(s6, v0, 360);
                        v0 = sll(s3, 3);
                        s1 = addu(s2, v0);
                        lwc1(f0, s1, 400);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        s4 = dsll32(v0, 16);
                        s4 = dsra32(s4, 16);
                        a0 = 1;
                        a1 = si(-219);
                        a2 = 19;
                        a3 = s6;
                        t0 = 15;
                        jal(ctx, 0x4231C8u, gen::fn_sub_421FE0_00421fe0);
                        swc1(f0, sp, 0xB0);
                        a0 = 1;
                        a1 = s4;
                        a2 = s4;
                        a3 = s6;
                        t0 = 15;
                        jal(ctx, 0x4231E8u, gen::fn_sub_421FE0_00421fe0);
                        swc1(f0, sp, 0xB4);
                        lwc1(f1, sp, 0xB0);
                        lwc1(f0, sp, 0xB4);
                        swc1(f1, s1, 396);
                        swc1(f0, s1, 400);
                        lh(v0, s7, 0);
                        at = slti(v0, 15);
                        if (at != 0) {
                            // 0x00423214
                            charge(ctx, 5);
                            v0 = addiu(v0, 1);
                            sh(v0, s7, 0);
                            s5 = 1;
                        }
                    }
                    // 0x00423234
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x00423248
                charge(ctx, 7);
                a0 = s0;
                jal(ctx, 0x42324Cu, gen::fn_sub_423CD0_00423cd0);
                v0 = dsll32(s5, 24);
                v0 = dsra32(v0, 24);
                if (v0 == 0) {
                    // 0x00423264
                    charge(ctx, 6);
                    v0 = 4;
                    sb(v0, s2, 0);
                    a0 = 0;
                    v1 = 0x41980000;
                    for (;;) {
                        // 0x0042328c
                        charge(ctx, 4);
                        lb(v0, s2, 142);
                        v0 = slt(a0, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0042327c
                        charge(ctx, 4);
                        v0 = sll(a0, 3);
                        v0 = addu(s2, v0);
                        sw(v1, v0, 396);
                        a0 = addiu(a0, 1);
                    }
                    // 0x0042329c
                    charge(ctx, 3);
                    v1 = 0;
                    for (;;) {
                        // 0x004232c8
                        charge(ctx, 3);
                        v0 = slti(v1, 6);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x004232a8
                        charge(ctx, 8);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        v0 = addu(s2, v0);
                        sh(zero, v0, 358);
                        sh(zero, v0, 362);
                        sh(zero, v0, 360);
                        v1 = addiu(v1, 1);
                    }
                    // 0x004232d4
                    charge(ctx, 2);
                }
                goto L_00423758;
            }
            // 0x00423050
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x4232DCu:  // table[4]
            // 0x004232dc
            charge(ctx, 25);
            jal(ctx, 0x4232DCu, gen::fn_sub_423CD0_00423cd0);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x4232F0u, gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x42331Cu, gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(ctx, 0x423328u, gen::fn_sub_115980_00115980);
            v0 = 5;
            sb(v0, s2, 0);
            goto L_00423758;
        case 0x423340u:  // table[5]
            // 0x00423340
            charge(ctx, 5);
            lw(v0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
            lb(v1, v0, 9);
            v0 = 1;
            if (v1 != v0) {
                // 0x00423354
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(a0, v0, 2386);  // 0x7E0952 pad: pressed
                v0 = a0 & 0x1000;
                if (v0 == 0) {
                    // 0x00423368
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v1, v0, 2394);  // 0x7E095A pad: repeat
                    v0 = v1 & 0x1000;
                    if (v0 != 0) {
                        goto L_0042337c;
                    }
                    // 0x004233c4
                    charge(ctx, 3);
                    v0 = a0 & 0x4000;
                    if (v0 == 0) {
                        // 0x004233d0
                        charge(ctx, 3);
                        v0 = v1 & 0x4000;
                        if (v0 != 0) {
                            goto L_004233dc;
                        }
                        // 0x00423428
                        charge(ctx, 3);
                        v0 = a0 & 0x40;
                        if (v0 != 0) {
                            // 0x00423434
                            charge(ctx, 3);
                            v1 = 0;
                            for (;;) {
                                // 0x00423458
                                charge(ctx, 4);
                                lb(v0, s2, 142);
                                v0 = slt(v1, v0);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x00423440
                                charge(ctx, 6);
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 1);
                                v0 = addu(s2, v0);
                                sh(zero, v0, 82);
                                v1 = addiu(v1, 1);
                            }
                            // 0x00423468
                            charge(ctx, 8);
                            v0 = 6;
                            sb(v0, s2, 0);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 1;
                            jal(ctx, 0x423480u, gen::fn_sub_10A4E0_0010a4e0);
                        }
                        goto L_00423488;
                    }
                L_004233dc:
                    charge(ctx, 6);
                    lb(v1, s2, 150);
                    lb(v0, s2, 142);
                    v0 = addiu(v0, -1);
                    at = slt(v1, v0);
                    if (at == 0) {
                        // 0x00423404
                        charge(ctx, 1);
                        sb(zero, s2, 150);
                    } else {
                        // 0x004233f4
                        charge(ctx, 4);
                        v0 = addiu(v1, 1);
                        sb(v0, s2, 150);
                    }
                    // 0x00423408
                    charge(ctx, 8);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x423418u, gen::fn_sub_10A4E0_0010a4e0);
                    goto L_00423488;
                }
            L_0042337c:
                charge(ctx, 3);
                lb(v0, s2, 150);
                if (i64(v0) <= 0) {
                    // 0x00423398
                    charge(ctx, 3);
                    lb(v0, s2, 142);
                    v0 = addiu(v0, -1);
                    sb(v0, s2, 150);
                } else {
                    // 0x00423388
                    charge(ctx, 4);
                    v0 = addiu(v0, -1);
                    sb(v0, s2, 150);
                }
                // 0x004233a4
                charge(ctx, 8);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                jal(ctx, 0x4233B4u, gen::fn_sub_10A4E0_0010a4e0);
            }
        L_00423488:
            charge(ctx, 24);
            a0 = s0;
            jal(ctx, 0x42348Cu, gen::fn_sub_423CD0_00423cd0);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x4234A0u, gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x4234CCu, gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(ctx, 0x4234D8u, gen::fn_sub_115980_00115980);
            goto L_00423758;
        case 0x4234E8u:  // table[6]
            // 0x004234e8
            charge(ctx, 3);
            s4 = 0;
            for (;;) {
                // 0x004235f4
                charge(ctx, 4);
                lb(v0, s2, 142);
                v0 = slt(s4, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004234f4
                charge(ctx, 58);
                v0 = sll(s4, 1);
                v0 = addu(v0, s4);
                v0 = sll(v0, 1);
                v0 = addu(s2, v0);
                s3 = addiu(v0, 360);
                lh(s5, v0, 360);
                lb(v0, s2, 150);
                v0 = sll(v0, 3);
                v0 = addu(s2, v0);
                lwc1(f0, v0, 400);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                s7 = dsll32(v0, 16);
                s7 = dsra32(s7, 16);
                v0 = sll(s4, 3);
                v1 = addu(s2, v0);
                fp = addiu(v1, 0x190);
                lwc1(f0, v1, 400);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                s6 = dsll32(v0, 16);
                s6 = dsra32(s6, 16);
                s1 = addiu(v1, 396);
                lwc1(f0, v1, 396);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = 1;
                a2 = a1;
                a3 = s5;
                t0 = 15;
                jal(ctx, 0x423580u, gen::fn_sub_421FE0_00421fe0);
                swc1(f0, sp, 0xA8);
                a0 = 1;
                a1 = s6;
                a2 = s7;
                a3 = s5;
                t0 = 15;
                jal(ctx, 0x4235A0u, gen::fn_sub_421FE0_00421fe0);
                swc1(f0, sp, 0xAC);
                lwc1(f1, sp, 0xA8);
                lwc1(f0, sp, 0xAC);
                swc1(f1, s1, 0);
                swc1(f0, s1, 4);
                lh(v0, s3, 0);
                v0 = addiu(v0, 1);
                sh(v0, s3, 0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = slti(v0, 15);
                if (v0 == 0) {
                    // 0x004235dc
                    charge(ctx, 5);
                    lb(v0, s2, 150);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lwc1(f0, v0, 400);
                    swc1(f0, fp, 0x0);
                }
                // 0x004235f0
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x00423604
            charge(ctx, 4);
            lh(v0, s2, 360);
            at = slti(v0, 11);
            if (at == 0) {
                // 0x00423614
                charge(ctx, 3);
                v1 = 0;
                for (;;) {
                    // 0x00423640
                    charge(ctx, 4);
                    lb(v0, s2, 142);
                    v0 = slt(v1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00423620
                    charge(ctx, 8);
                    lb(v0, s2, 150);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lwc1(f0, v0, 400);
                    v0 = sll(v1, 3);
                    v0 = addu(s2, v0);
                    swc1(f0, v0, 400);
                    v1 = addiu(v1, 1);
                }
                // 0x00423650
                charge(ctx, 3);
                v1 = 0;
                for (;;) {
                    // 0x0042367c
                    charge(ctx, 3);
                    v0 = slti(v1, 6);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042365c
                    charge(ctx, 8);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(s2, v0);
                    sh(zero, v0, 358);
                    sh(zero, v0, 362);
                    sh(zero, v0, 360);
                    v1 = addiu(v1, 1);
                }
                // 0x00423688
                charge(ctx, 2);
                v0 = 12;
                sb(v0, s2, 0);
            }
            // 0x00423690
            charge(ctx, 24);
            a0 = s0;
            jal(ctx, 0x423694u, gen::fn_sub_423CD0_00423cd0);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x4236A8u, gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x4236D4u, gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(ctx, 0x4236E0u, gen::fn_sub_115980_00115980);
            goto L_00423758;
        case 0x4236F0u:  // table[12]
            // 0x004236f0
            charge(ctx, 23);
            jal(ctx, 0x4236F0u, gen::fn_sub_423CD0_00423cd0);
            a0 = 0;
            lw(a1, s2, 200);
            a2 = 24;
            jal(ctx, 0x423704u, gen::fn_sprCreateHandle_001158b0);
            s0 = v0;
            v1 = 0x42A20000;
            sw(v1, v0, 16);
            sw(zero, v0, 20);
            v1 = 0x41200000;
            sw(v1, v0, 44);
            sb(zero, v0, 24);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x423730u, gen::fn_sub_1127D0_001127d0);
            a0 = s0;
            jal(ctx, 0x42373Cu, gen::fn_sub_115980_00115980);
            goto L_00423758;
        case 0x42374Cu:  // table[13]
            // 0x0042374c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x423758u:  // table[7, 8, 9, 10, 11]
            goto L_00423758;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0042375c (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xC0);
        return;
    }
    goto L_00423758;
}

// 0x00423790 sub_423790 -- 280 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapMenuDestroy] The destroy callback of "y_LMapMenu proc": sprite handles and file, then the work.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00423790
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, kTaskWork);
    s1 = 0;
    for (;;) {
        // 0x004237e8
        charge(ctx, 3);
        v0 = slti(s1, 25);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004237c0
        charge(ctx, 6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        s3 = addiu(v0, 204);
        lw(a0, v0, 204);
        if (a0 != 0) {
            // 0x004237d8
            charge(ctx, 3);
            jal(ctx, 0x4237D8u, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x004237e4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004237f4
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0042384c
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00423800
        charge(ctx, 6);
        v0 = sll(s1, 2);
        s4 = addu(s0, v0);
        s3 = addiu(s4, 304);
        lw(a0, s4, 304);
        if (a0 != 0) {
            // 0x00423818
            charge(ctx, 3);
            jal(ctx, 0x423818u, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00423824
        charge(ctx, 3);
        lw(a0, s4, 328);
        if (a0 != 0) {
            // 0x00423830
            charge(ctx, 6);
            v0 = sll(s1, 2);
            v0 = addu(s0, v0);
            s3 = addiu(v0, 328);
            jal(ctx, 0x42383Cu, gen::fn_sub_115980_00115980);
            sw(zero, s3, 0);
        }
        // 0x00423848
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00423858
    charge(ctx, 3);
    lw(a0, s0, 200);
    if (a0 != 0) {
        // 0x00423864
        charge(ctx, 3);
        jal(ctx, 0x423864u, gen::fn_sub_1124B0_001124b0);
        sw(zero, s0, 200);
    }
    // 0x00423870
    charge(ctx, 14);
    lw(a0, s2, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x42387Cu, v0.u());
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004238B0 Y_LMap_CreateLMapMenuTask -- 668 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_CreateLMapMenuTask: the menu task and its RwCalloc'd work.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateLMapMenuTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004238b0
    enter(ctx, 29);  // entry check point + this block's cycles
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
    s6 = t1;
    s7 = t2;
    fp = t3;
    a0 = 1;
    a1 = 452;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x423910u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00423930
        charge(ctx, 17);
        a0 = s5;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 17392);  // "y_LMapMenu proc"
        a3 = 0x420000;
        a3 = addiu(a3, 11488);  // &Y_LMap_UpdateLMapMenuTask
        t0 = 0x420000;
        t0 = addiu(t0, 14224);  // &sub_423790
        t1 = s0;
        jal(ctx, 0x423954u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sb(zero, s0, 0);
        sb(zero, s0, 150);
        a2 = 0;
        a1 = si(-1);
        for (;;) {
            // 0x0042398c
            charge(ctx, 5);
            a0 = dsll32(a2, 16);
            a0 = dsra32(a0, 16);
            v1 = slti(a0, 6);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00423974
            charge(ctx, 6);
            v1 = sll(a0, 2);
            v1 = addu(s0, v1);
            sw(a1, v1, 116);
            v1 = addiu(a2, 1);
            a2 = dsll32(v1, 16);
            a2 = dsra32(a2, 16);
        }
        // 0x004239a0
        charge(ctx, 9);
        sh(zero, s0, 140);
        sb(zero, s0, 196);
        sb(zero, s0, 149);
        sb(zero, s0, 142);
        a0 = dsll32(s4, 24);
        a0 = dsra32(a0, 24);
        v1 = 1;
        if (a0 == v1) {
            // 0x004239c4
            charge(ctx, 6);
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(zero, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x004239dc
        charge(ctx, 5);
        v1 = dsll32(s3, 24);
        v1 = dsra32(v1, 24);
        a0 = 1;
        if (v1 == a0) {
            // 0x004239f0
            charge(ctx, 6);
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(a0, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x00423a08
        charge(ctx, 5);
        a0 = dsll32(s2, 24);
        a0 = dsra32(a0, 24);
        v1 = 1;
        if (a0 == v1) {
            // 0x00423a1c
            charge(ctx, 7);
            a0 = 2;
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(a0, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x00423a38
        charge(ctx, 5);
        a0 = dsll32(s1, 24);
        a0 = dsra32(a0, 24);
        v1 = 1;
        if (a0 == v1) {
            // 0x00423a4c
            charge(ctx, 7);
            a0 = 3;
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(a0, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x00423a68
        charge(ctx, 5);
        a0 = dsll32(s6, 24);
        a0 = dsra32(a0, 24);
        v1 = 1;
        if (a0 == v1) {
            // 0x00423a7c
            charge(ctx, 7);
            a0 = 4;
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(a0, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x00423a98
        charge(ctx, 5);
        a0 = dsll32(s7, 24);
        a0 = dsra32(a0, 24);
        v1 = 1;
        if (a0 == v1) {
            // 0x00423aac
            charge(ctx, 7);
            a0 = 5;
            lb(v1, s0, 142);
            v1 = addu(v1, s0);
            sb(a0, v1, 143);
            lb(v1, s0, 142);
            v1 = addiu(v1, 1);
            sb(v1, s0, 142);
        }
        // 0x00423ac8
        charge(ctx, 5);
        a2 = 0;
        a1 = dsll32(fp, 24);
        a1 = dsra32(a1, 24);
        for (;;) {
            // 0x00423b00
            charge(ctx, 6);
            a0 = dsll32(a2, 16);
            a0 = dsra32(a0, 16);
            lb(v1, s0, 142);
            v1 = slt(a0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00423adc
            charge(ctx, 4);
            v1 = addu(s0, a0);
            lb(v1, v1, 143);
            if (v1 == a1) {
                // 0x00423aec
                charge(ctx, 2);
                sb(a2, s0, 150);
                lb(a2, s0, 142);
            }
            // 0x00423af4
            charge(ctx, 3);
            v1 = addiu(a2, 1);
            a2 = dsll32(v1, 16);
            a2 = dsra32(a2, 16);
        }
    } else {
        // 0x00423924
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00423b18 (the shared epilogue, written out on this path)
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

// 0x00423B50 sub_423B50 -- 24 bytes; leaf frame (no stack)
// [lmapMenuSelected] record[143 + record[150]] (signed bytes): the selected entry's id.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423B50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00423b50
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    lb(v0, v1, 150);
    v0 = addu(v0, v1);
    lb(v0, v0, 143);
}

// 0x00423B70 sub_423B70 -- 48 bytes; leaf frame (no stack)
// [lmapMenuIsDone] Record byte 0 is 6 or 12.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00423b70
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lb(v1, v0, 0);
    v0 = 6;
    if (v1 != v0) {
        // 0x00423b90
        charge(ctx, 2);
        v0 = v1 ^ 0xC;
        v0 = sltiu(v0, 1);
    } else {
        // 0x00423b84
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00423b98 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00423BA0 sub_423BA0 -- 72 bytes; leaf frame (no stack)
// [lmapMenuClose] Zeroes the halfword +82 of each of the record +142 entries (6-byte stride), state 10.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00423ba0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    a1 = 0;
    for (;;) {
        // 0x00423bc8
        charge(ctx, 4);
        lb(v1, a0, 142);
        v1 = slt(a1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00423bb0
        charge(ctx, 6);
        v1 = sll(a1, 1);
        v1 = addu(v1, a1);
        v1 = sll(v1, 1);
        v1 = addu(a0, v1);
        sh(zero, v1, 82);
        a1 = addiu(a1, 1);
    }
    // 0x00423bd8
    charge(ctx, 4);
    v1 = 10;
    sb(v1, a0, 0);
}

// 0x00423BF0 sub_423BF0 -- 24 bytes; leaf frame (no stack)
// [lmapMenuIsOpen] Record byte 0 >= 2.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00423bf0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lb(v0, v0, 0);
    v0 = slti(v0, 2);
    v0 = v0 ^ 0x1;
}

// 0x00423C10 sub_423C10 -- 180 bytes; leaf frame (no stack)
// [lmapMenuSelect] Finds the entry whose id (+143 + i) is $a1, makes it the selection (+150) and on a match
// zeroes the entries' halfwords +82, sets state 6 and byte 7 of the shared record gp-0x4648.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00423c10
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(a2, a0, kTaskWork);
    a3 = 0;
    t0 = 0;
    a1 = dsll32(a1, 24);
    a1 = dsra32(a1, 24);
    a0 = 1;
    for (;;) {
        // 0x00423c50
        charge(ctx, 4);
        lb(v1, a2, 142);
        v1 = slt(t0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00423c30
        charge(ctx, 4);
        v1 = addu(a2, t0);
        lb(v1, v1, 143);
        if (v1 == a1) {
            // 0x00423c40
            charge(ctx, 3);
            sb(t0, a2, 150);
            lb(t0, a2, 142);
            a3 = a0;
        }
        // 0x00423c4c
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x00423c60
    charge(ctx, 5);
    a0 = dsll32(a3, 24);
    a0 = dsra32(a0, 24);
    v1 = 1;
    if (a0 == v1) {
        // 0x00423c74
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x00423c98
            charge(ctx, 4);
            lb(v1, a2, 142);
            v1 = slt(a0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00423c80
            charge(ctx, 6);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 1);
            v1 = addu(a2, v1);
            sh(zero, v1, 82);
            a0 = addiu(a0, 1);
        }
        // 0x00423ca8
        charge(ctx, 5);
        v1 = 6;
        sb(v1, a2, 0);
        a0 = 1;
        lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
        sb(a0, v1, 7);
    }
    // 0x00423cbc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00423CD0 sub_423CD0 -- 740 bytes; leaf frame (no stack)
// [lmapMenuLayout] Places the menu's sprite records (+204.. pointers): positions from the entry table
// +396 / +400 plus fixed offsets, alpha bytes +24, the selected entry's extra parts.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x00423cd0
    enter(ctx, 20);  // entry check point + this block's cycles
    lw(t0, a0, kTaskWork);
    t1 = 0;
    a1 = 0x41200000;
    v1 = 0x41500000;
    mtc1(v1, f1);
    v1 = 0x40400000;
    mtc1(v1, f0);
    a2 = 255;
    v1 = 0x41300000;
    a0 = 0x43350000;
    mtc1(a0, f6);
    a0 = 0x40800000;
    mtc1(a0, f5);
    a0 = 0x41980000;
    mtc1(a0, f4);
    a0 = 0x43370000;
    mtc1(a0, f3);
    a3 = 0x41400000;
    for (;;) {
        // 0x00423f78
        charge(ctx, 4);
        lb(a0, t0, 142);
        a0 = slt(t1, a0);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00423d20
        charge(ctx, 3);
        lb(a0, t0, 150);
        if (t1 == a0) {
            // 0x00423dc8
            charge(ctx, 82);
            t4 = addu(t0, t1);
            lb(a0, t4, 143);
            a0 = sll(a0, 1);
            a0 = addiu(a0, 12);
            a0 = sll(a0, 2);
            t3 = addu(t0, a0);
            lw(a0, t3, 204);
            sb(zero, a0, 24);
            lw(a0, t3, 204);
            sw(a1, a0, 44);
            a0 = sll(t1, 3);
            a0 = addu(t0, a0);
            lwc1(f2, a0, 396);
            add_s(f2, f1, f2);
            lw(t2, t3, 204);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            add_s(f2, f0, f2);
            lw(t2, t3, 204);
            swc1(f2, t2, 20);
            lb(t2, t4, 143);
            t2 = sll(t2, 1);
            t2 = addiu(t2, 11);
            t2 = sll(t2, 2);
            t3 = addu(t0, t2);
            lw(t2, t3, 204);
            sb(a2, t2, 24);
            lw(t2, t3, 204);
            sw(a1, t2, 44);
            lwc1(f2, a0, 396);
            add_s(f2, f1, f2);
            lw(t2, t3, 204);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            add_s(f2, f0, f2);
            lw(t2, t3, 204);
            swc1(f2, t2, 20);
            lw(t2, t0, 236);
            sb(zero, t2, 24);
            lw(t2, t0, 236);
            sw(v1, t2, 44);
            lwc1(f2, a0, 396);
            lw(t2, t0, 236);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            lw(t2, t0, 236);
            swc1(f2, t2, 20);
            lw(t2, t0, 240);
            sb(zero, t2, 24);
            lw(t2, t0, 240);
            sw(v1, t2, 44);
            lwc1(f2, a0, 396);
            add_s(f2, f6, f2);
            lw(t2, t0, 240);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            lw(t2, t0, 240);
            swc1(f2, t2, 20);
            lw(t2, t0, 220);
            sb(zero, t2, 24);
            lw(t2, t0, 220);
            sw(v1, t2, 44);
            lwc1(f2, a0, 396);
            add_s(f2, f5, f2);
            lw(t2, t0, 220);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            add_s(f2, f4, f2);
            lw(t2, t0, 220);
            swc1(f2, t2, 20);
            lw(t2, t0, 224);
            sb(zero, t2, 24);
            lw(t2, t0, 224);
            sw(v1, t2, 44);
            lwc1(f2, a0, 396);
            add_s(f2, f3, f2);
            lw(t2, t0, 224);
            swc1(f2, t2, 16);
            lwc1(f2, a0, 400);
            add_s(f2, f4, f2);
            lw(a0, t0, 224);
            swc1(f2, a0, 20);
        } else {
            // 0x00423d2c
            charge(ctx, 39);
            t4 = addu(t0, t1);
            lb(a0, t4, 143);
            a0 = sll(a0, 1);
            a0 = addiu(a0, 11);
            a0 = sll(a0, 2);
            t2 = addu(t0, a0);
            lw(a0, t2, 204);
            sb(zero, a0, 24);
            lw(a0, t2, 204);
            sw(a3, a0, 44);
            a0 = sll(t1, 3);
            t3 = addu(t0, a0);
            lwc1(f2, t3, 396);
            add_s(f2, f1, f2);
            lw(a0, t2, 204);
            swc1(f2, a0, 16);
            lwc1(f2, t3, 400);
            add_s(f2, f0, f2);
            lw(a0, t2, 204);
            swc1(f2, a0, 20);
            lb(a0, t4, 143);
            a0 = sll(a0, 1);
            a0 = addiu(a0, 12);
            a0 = sll(a0, 2);
            t2 = addu(t0, a0);
            lw(a0, t2, 204);
            sb(a2, a0, 24);
            lw(a0, t2, 204);
            sw(a3, a0, 44);
            lwc1(f2, t3, 396);
            add_s(f2, f1, f2);
            lw(a0, t2, 204);
            swc1(f2, a0, 16);
            lwc1(f2, t3, 400);
            add_s(f2, f0, f2);
            lw(a0, t2, 204);
            swc1(f2, a0, 20);
        }
        // 0x00423f10
        charge(ctx, 26);
        a0 = sll(t1, 2);
        t3 = addu(t0, a0);
        lw(a0, t3, 304);
        sb(zero, a0, 24);
        lw(a0, t3, 304);
        sw(a3, a0, 44);
        a0 = sll(t1, 3);
        t2 = addu(t0, a0);
        lwc1(f2, t2, 396);
        lw(a0, t3, 304);
        swc1(f2, a0, 16);
        lwc1(f2, t2, 400);
        lw(a0, t3, 304);
        swc1(f2, a0, 20);
        lw(a0, t3, 328);
        sb(zero, a0, 24);
        lw(a0, t3, 328);
        sw(a3, a0, 44);
        lwc1(f2, t2, 396);
        add_s(f2, f6, f2);
        lw(a0, t3, 328);
        swc1(f2, a0, 16);
        lwc1(f2, t2, 400);
        lw(a0, t3, 328);
        swc1(f2, a0, 20);
        t1 = addiu(t1, 1);
    }
    // 0x00423f88
    charge(ctx, 11);
    a0 = 0x41200000;
    lw(v1, t0, 208);
    sw(a0, v1, 44);
    a0 = 0x43D50000;
    lw(v1, t0, 208);
    sw(a0, v1, 16);
    a0 = 0x43CB0000;
    lw(v1, t0, 208);
    sw(a0, v1, 20);
}

// 0x00423FC0 sub_423FC0 -- 20 bytes; leaf frame (no stack)
// [lmapMenuSetFlag149] Record byte +149 = 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00423fc0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 149);
}

// 0x00423FE0 sub_423FE0 -- 488 bytes; frame 0x10
// [lmapAlign] By mode $a1 (s8): 0 centre ((w/2, h/2) of $a2 / $a3), 1 (x + (w - x)/2 ...), 2 (w/2 - x/2 ...);
// the two floats go to $a0 (C division toward zero, as `sra` with the negative fix-up).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_423FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00423fe0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = dsll32(a1, 24);
    a1 = dsra32(a1, 24);
    if (a1 != 0) {
        // 0x00424054
        charge(ctx, 3);
        v1 = 1;
        if (a1 != v1) {
            // 0x00424108
            charge(ctx, 3);
            v1 = 2;
            if (a1 == v1) {
                // 0x00424114
                charge(ctx, 5);
                v1 = dsll32(a2, 16);
                v1 = dsra32(v1, 16);
                a2 = sra(v1, 1);
                if (i64(v1) < 0) {
                    // 0x00424128
                    charge(ctx, 2);
                    v1 = addiu(v1, 1);
                    a2 = sra(v1, 1);
                }
                // 0x00424130
                charge(ctx, 5);
                a1 = dsll32(t0, 16);
                a1 = dsra32(a1, 16);
                v1 = sra(a1, 1);
                if (i64(a1) < 0) {
                    // 0x00424144
                    charge(ctx, 2);
                    v1 = addiu(a1, 1);
                    v1 = sra(v1, 1);
                }
                // 0x0042414c
                charge(ctx, 10);
                v1 = subu(a2, v1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x8);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                a2 = sra(v1, 1);
                if (i64(v1) < 0) {
                    // 0x00424174
                    charge(ctx, 2);
                    v1 = addiu(v1, 1);
                    a2 = sra(v1, 1);
                }
                // 0x0042417c
                charge(ctx, 5);
                a1 = dsll32(t1, 16);
                a1 = dsra32(a1, 16);
                v1 = sra(a1, 1);
                if (i64(a1) < 0) {
                    // 0x00424190
                    charge(ctx, 2);
                    v1 = addiu(a1, 1);
                    v1 = sra(v1, 1);
                }
                // 0x00424198
                charge(ctx, 5);
                v1 = subu(a2, v1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xC);
            }
        } else {
            // 0x00424060
            charge(ctx, 8);
            t0 = dsll32(t0, 16);
            t0 = dsra32(t0, 16);
            v1 = dsll32(a2, 16);
            v1 = dsra32(v1, 16);
            v1 = subu(v1, t0);
            a1 = sra(v1, 1);
            if (i64(v1) < 0) {
                // 0x00424080
                charge(ctx, 2);
                v1 = addiu(v1, 1);
                a1 = sra(v1, 1);
            }
            // 0x00424088
            charge(ctx, 3);
            v1 = sra(t0, 1);
            if (i64(t0) < 0) {
                // 0x00424094
                charge(ctx, 2);
                v1 = addiu(t0, 1);
                v1 = sra(v1, 1);
            }
            // 0x0042409c
            charge(ctx, 13);
            v1 = addu(v1, a1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x8);
            a2 = dsll32(t1, 16);
            a2 = dsra32(a2, 16);
            v1 = dsll32(a3, 16);
            v1 = dsra32(v1, 16);
            v1 = subu(v1, a2);
            a1 = sra(v1, 1);
            if (i64(v1) < 0) {
                // 0x004240d0
                charge(ctx, 2);
                v1 = addiu(v1, 1);
                a1 = sra(v1, 1);
            }
            // 0x004240d8
            charge(ctx, 3);
            v1 = sra(a2, 1);
            if (i64(a2) < 0) {
                // 0x004240e4
                charge(ctx, 2);
                v1 = addiu(a2, 1);
                v1 = sra(v1, 1);
            }
            // 0x004240ec
            charge(ctx, 7);
            v1 = addu(v1, a1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xC);
        }
    } else {
        // 0x00423ff4
        charge(ctx, 5);
        a1 = dsll32(a2, 16);
        a1 = dsra32(a1, 16);
        v1 = sra(a1, 1);
        if (i64(a1) < 0) {
            // 0x00424008
            charge(ctx, 2);
            v1 = addiu(a1, 1);
            v1 = sra(v1, 1);
        }
        // 0x00424010
        charge(ctx, 9);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x8);
        a1 = dsll32(a3, 16);
        a1 = dsra32(a1, 16);
        v1 = sra(a1, 1);
        if (i64(a1) < 0) {
            // 0x00424034
            charge(ctx, 2);
            v1 = addiu(a1, 1);
            v1 = sra(v1, 1);
        }
        // 0x0042403c
        charge(ctx, 6);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0xC);
    }
    // 0x004241ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, a0, 0);
    swc1(f0, a0, 4);
    sp = addiu(sp, 0x10);
}

// 0x004241E0 sub_4241E0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [seq4Create] Sequence 4 (the Y map task), row 0x68F050: Y_LMap_CreateLmapTask with the five signed bytes
// of the parameter at $a1, the task stored in sub_421760()'s slot.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4241E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004241e0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a1;
    lb(a0, a1, 0);
    lb(a1, a1, 1);
    lb(a2, v0, 2);
    lb(a3, v0, 3);
    lb(t0, v0, 4);
    jal(ctx, 0x424204u, gen::fn_Y_LMap_CreateLmapTask_00421de0);
    s0 = v0;
    jal(ctx, 0x424210u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
    sw(s0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00424230 sub_424230 -- 124 bytes; frame 0x10: ra sp+0x0
// [seq4Destroy] With a task in the slot that is in phase 15 (sub_421EF0): destroys it with its hierarchy,
// clears the slot, 0; otherwise -1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_424230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00424230
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x424238u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0042424c
        charge(ctx, 8);
        jal(ctx, 0x42424Cu, gen::fn_sub_421760_00421760);  // -> the Y map task slot
        lw(a0, v0, 0);
        jal(ctx, 0x424258u, gen::fn_sub_421EF0_00421ef0);
        v1 = 1;
        if (v0 != v1) {
            goto L_00424298;
        }
        // 0x0042426c
        charge(ctx, 11);
        jal(ctx, 0x42426Cu, gen::fn_sub_421760_00421760);  // -> the Y map task slot
        lw(a0, v0, 0);
        jal(ctx, 0x424278u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        jal(ctx, 0x424280u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
        sw(zero, v0, 0);
        v0 = 0;
        // 0x0042429c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00424298:
    charge(ctx, 1);
    v0 = si(-1);
    // 0x0042429c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004242B0 sub_4242B0 -- 84 bytes; frame 0x10: ra sp+0x0
// [seq4Poll] 0 while the slot's task exists, else clears the slot and returns 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4242B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004242b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4242B8u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
    lw(a0, v0, 0);
    jal(ctx, 0x4242C4u, gen::fn_kwlnTaskExists_00195460);
    v1 = 1;
    if (v0 != v1) {
        // 0x004242e4
        charge(ctx, 4);
        jal(ctx, 0x4242E4u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
        sw(zero, v0, 0);
        v0 = 1;
    } else {
        // 0x004242d8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004242f4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00424310 sub_424310 -- 84 bytes; frame 0x20: ra sp+0x0
// COMM: stops a sound channel (H_Snd_StopChannel(script int 0)) and changes the sequence (adminiChangeSeq).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_424310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00424310
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x42431Cu, gen::fn_scrGetIntPara_0035ed20);
    sb(v0, sp, 0x18);
    a0 = 4;
    a1 = 0;
    jal(ctx, 0x424330u, gen::fn_sub_109F60_00109f60);
    a0 = 4;
    a1 = addiu(sp, 0x18);
    a2 = 5;
    a3 = 0;
    jal(ctx, 0x424348u, gen::fn_adminiChangeSeq_0027c080);  // adminiChangeSeq(sequence, param, 28, 0)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00424370 sub_424370 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM: the shared record's byte 6 = script int 0; creates the "lmap_model_move" task for it and stores the
// task at gp-0x4638 (sub_426090); returns 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_424370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00424370
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x424380u, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    sb(v0, v1, 6);
    lw(v0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
    a0 = 0;
    lb(a1, v0, 6);
    jal(ctx, 0x42439Cu, gen::fn_Y_LMap_CreateLmapModelMoveTask_004264d0);
    s0 = v0;
    jal(ctx, 0x4243A8u, gen::fn_sub_426090_00426090);  // -> the lmap_model_move task slot
    sw(s0, v0, 0);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00424B60 sub_424B60 -- 932 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM: the party members (field units 0x8717A0, 448-byte records, 4 of them) near the unit whose +424 id is
// script int 0 (within 500.0, sub_1C7160): the encounter answer of sub_43A9D0 (2 default, 1 / 0 mark the member, 5
// scans again, 4 -> 0 when one was marked, 5 -> 1), the marked members' positions to the field (sub_1A9760) and the
// count (sub_16F3E0); returns the answer through scrSetIntReturnVal.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_424B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00424b60
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = 2;
    s2 = 0;
    s1 = 0;
    a0 = 0;
    a1 = 0;
    jal(ctx, 0x424B98u, gen::fn_sub_16F3E0_0016f3e0);
    a0 = 0;
    jal(ctx, 0x424BA4u, gen::fn_scrGetIntPara_0035ed20);
    a2 = dsll32(v0, 16);
    a2 = dsra32(a2, 16);
    t0 = 0;
    v1 = 1;
    a1 = 0x870000;
    a1 = addiu(a1, 6048);  // &gFldUnitsPc
    for (;;) {
        // 0x00424c28
        charge(ctx, 3);
        v0 = slti(t0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00424bcc
        charge(ctx, 10);
        v0 = addu(t0, sp);
        sb(zero, v0, 156);
        a3 = 0;
        v0 = sll(t0, 3);
        v0 = subu(v0, t0);
        v0 = sll(v0, 6);
        a0 = addu(a1, v0);
        lw(v0, a0, 72);
        if (v0 != 0) {
            // 0x00424bf4
            charge(ctx, 3);
            lw(v0, a0, 84);
            if (v0 != 0) {
                // 0x00424c00
                charge(ctx, 1);
                a3 = v1;
            }
        }
        // 0x00424c04
        charge(ctx, 3);
        v0 = sltu(0, a3);
        if (v0 == v1) {
            // 0x00424c10
            charge(ctx, 3);
            lhu(v0, a0, 424);
            if (a2 == v0) {
                // 0x00424c1c
                charge(ctx, 2);
                s5 = dsll32(t0, 16);
                s5 = dsra32(s5, 16);
            }
        }
        // 0x00424c24
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x00424c34
    charge(ctx, 11);
    s0 = 0;
    v1 = dsll32(s5, 16);
    v1 = dsra32(v1, 16);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6048);  // &gFldUnitsPc
    s6 = addu(v0, v1);
    for (;;) {
        // 0x00424dc8
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00424c60
        charge(ctx, 10);
        a0 = 0;
        v0 = sll(s0, 3);
        v0 = subu(v0, s0);
        v1 = sll(v0, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6048);  // &gFldUnitsPc
        a1 = addu(v0, v1);
        lw(v0, a1, 72);
        if (v0 != 0) {
            // 0x00424c88
            charge(ctx, 3);
            lw(v0, a1, 84);
            if (v0 != 0) {
                // 0x00424c94
                charge(ctx, 1);
                a0 = 1;
            }
        }
        // 0x00424c98
        charge(ctx, 4);
        v1 = sltu(0, a0);
        v0 = 1;
        if (v1 == v0) {
            // 0x00424ca8
            charge(ctx, 8);
            v0 = 0x43FA0000;
            mtc1(v0, f12);
            a0 = s6;
            jal(ctx, 0x424CB4u, gen::fn_sub_1C7160_001c7160);
            v1 = 1;
            if (v0 == v1) {
                // 0x00424cc8
                charge(ctx, 12);
                a0 = dsll32(s5, 24);
                a0 = dsra32(a0, 24);
                a1 = dsll32(s0, 24);
                a1 = dsra32(a1, 24);
                a2 = 0;
                jal(ctx, 0x424CDCu, gen::fn_sub_43A9D0_0043a9d0);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = 2;
                if (v1 != v0) {
                    // 0x00424cf8
                    charge(ctx, 1);
                    s3 = v1;
                }
                // 0x00424cfc
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x00424d04
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        goto L_00424d10;
                    }
                    // 0x00424d24
                    charge(ctx, 3);
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x00424d30
                        charge(ctx, 3);
                        s4 = 0;
                        for (;;) {
                            // 0x00424db8
                            charge(ctx, 3);
                            v0 = slti(s4, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00424d3c
                            charge(ctx, 10);
                            a0 = 0;
                            v0 = sll(s4, 3);
                            v0 = subu(v0, s4);
                            v1 = sll(v0, 6);
                            v0 = 0x870000;
                            v0 = addiu(v0, 6048);  // &gFldUnitsPc
                            a1 = addu(v0, v1);
                            lw(v0, a1, 72);
                            if (v0 != 0) {
                                // 0x00424d64
                                charge(ctx, 3);
                                lw(v0, a1, 84);
                                if (v0 != 0) {
                                    // 0x00424d70
                                    charge(ctx, 1);
                                    a0 = 1;
                                }
                            }
                            // 0x00424d74
                            charge(ctx, 4);
                            v1 = sltu(0, a0);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x00424d84
                                charge(ctx, 8);
                                v0 = 0x43FA0000;
                                mtc1(v0, f12);
                                a0 = s6;
                                jal(ctx, 0x424D90u, gen::fn_sub_1C7160_001c7160);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x00424da4
                                    charge(ctx, 4);
                                    v0 = addu(s4, sp);
                                    sb(v1, v0, 156);
                                    s2 = dsll32(v1, 24);
                                    s2 = dsra32(s2, 24);
                                }
                            }
                            // 0x00424db4
                            charge(ctx, 1);
                            s4 = addiu(s4, 1);
                        }
                    }
                    goto L_00424dc4;
                }
            L_00424d10:
                charge(ctx, 5);
                s2 = 1;
                v0 = addu(s0, sp);
                sb(s2, v0, 156);
            }
        }
    L_00424dc4:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00424dd4
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00424e74
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00424de0
        charge(ctx, 5);
        v0 = addu(s0, sp);
        lb(v1, v0, 156);
        v0 = 1;
        if (v1 == v0) {
            // 0x00424df4
            charge(ctx, 31);
            s1 = addiu(s1, 1);
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 6);
            v0 = 0x870000;
            v0 = addiu(v0, 6048);  // &gFldUnitsPc
            v0 = addu(v0, v1);
            lw(v0, v0, 84);
            a0 = addiu(sp, 0x80);
            lw(a1, v0, 480);
            jal(ctx, 0x424E1Cu, gen::fn_sub_1AD940_001ad940);
            lwc1(f2, sp, 0x80);
            lwc1(f1, sp, 0x84);
            lwc1(f0, sp, 0x88);
            swc1(f2, sp, 0x90);
            swc1(f1, sp, 0x94);
            swc1(f0, sp, 0x98);
            jal(ctx, 0x424E3Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 16);
            a1 = 6;
            a2 = addiu(sp, 0x90);
            a3 = 3;
            t0 = 1;
            jal(ctx, 0x424E58u, gen::fn_sub_1A9760_001a9760);
            a0 = 0;
            a1 = s1;
            jal(ctx, 0x424E68u, gen::fn_sub_16F3E0_0016f3e0);
        }
        // 0x00424e70
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00424e80
    charge(ctx, 5);
    v1 = dsll32(s2, 24);
    v1 = dsra32(v1, 24);
    v0 = 1;
    if (v1 == v0) {
        // 0x00424e94
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 4;
        if (v1 == v0) {
            // 0x00424ea8
            charge(ctx, 1);
            s3 = 0;
        }
    }
    // 0x00424eac
    charge(ctx, 5);
    v1 = dsll32(s3, 16);
    v1 = dsra32(v1, 16);
    v0 = 5;
    if (v1 == v0) {
        // 0x00424ec0
        charge(ctx, 1);
        s3 = 1;
    }
    // 0x00424ec4
    charge(ctx, 16);
    a0 = dsll32(s3, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x424ECCu, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00424F80 sub_424F80 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM: for party slots 1..3 that are present, sub_1B00C0 on their model's +368.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_424F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00424f80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 1;
    for (;;) {
        // 0x00424ffc
        charge(ctx, 3);
        v1 = slti(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00424f98
        charge(ctx, 10);
        a2 = 0;
        v1 = sll(s0, 3);
        v1 = subu(v1, s0);
        a0 = sll(v1, 6);
        v1 = 0x870000;
        v1 = addiu(v1, 6048);  // &gFldUnitsPc
        a1 = addu(v1, a0);
        lw(v1, a1, 72);
        if (v1 != 0) {
            // 0x00424fc0
            charge(ctx, 3);
            lw(v1, a1, 84);
            if (v1 != 0) {
                // 0x00424fcc
                charge(ctx, 1);
                a2 = 1;
            }
        }
        // 0x00424fd0
        charge(ctx, 4);
        a0 = sltu(0, a2);
        v1 = 1;
        if (a0 == v1) {
            // 0x00424fe0
            charge(ctx, 6);
            lw(v0, a1, 364);
            lw(v0, v0, kTaskWork);
            lw(v0, v0, 36);
            lw(a0, v0, 368);
            jal(ctx, 0x424FF0u, gen::fn_sub_1B00C0_001b00c0);
        }
        // 0x00424ff8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00425008
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00425020 sub_425020 -- 68 bytes; frame 0x10: ra sp+0x0
// COMM: creates the stratum parts task (mode 1) into gp-0x4644 (cleared first); returns 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425020(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425020
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    if (v0 != 0) {
        // 0x00425034
        charge(ctx, 1);
        sw(zero, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    }
    // 0x00425038
    charge(ctx, 11);
    a0 = 0;
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x425044u, gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70);
    sw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00425070 sub_425070 -- 60 bytes; frame 0x10: ra sp+0x0
// COMM: without a stratum parts task runs sub_449FA0 and returns 1, else 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425070
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    if (v0 == 0) {
        // 0x00425090
        charge(ctx, 3);
        jal(ctx, 0x425090u, gen::fn_sub_449FA0_00449fa0);
        v0 = 1;
    } else {
        // 0x00425084
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0042509c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004252D0 sub_4252D0 -- 68 bytes; frame 0x10: ra sp+0x0
// COMM: as sub_425020 with mode 0.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4252D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004252d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    if (v0 != 0) {
        // 0x004252e4
        charge(ctx, 1);
        sw(zero, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    }
    // 0x004252e8
    charge(ctx, 11);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x4252F4u, gen::fn_Y_Stratum_CreateStratumPartsTask_00447e70);
    sw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00425320 sub_425320 -- 60 bytes; frame 0x10: ra sp+0x0
// COMM: as sub_425070.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425320
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -17988);  // 0x7CE6AC gp-0x4644: the stratum parts task
    if (v0 == 0) {
        // 0x00425340
        charge(ctx, 3);
        jal(ctx, 0x425340u, gen::fn_sub_449FA0_00449fa0);
        v0 = 1;
    } else {
        // 0x00425334
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0042534c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00425480 sub_425480 -- 56 bytes; frame 0x10: ra sp+0x0
// COMM TIME_LIMIT: creates the time-limit display (Y_TimeLimit_CreateTimeLimitDrawTask(0, script int 0)); returns 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425480
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x42548Cu, gen::fn_scrGetIntPara_0035ed20);
    a0 = 0;
    a1 = v0;
    jal(ctx, 0x42549Cu, gen::fn_Y_TimeLimit_CreateTimeLimitDrawTask_0045a280);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00425690 sub_425690 -- 1284 bytes; frame 0xB0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapModelUpdate] The "y_lmap_model proc" update: loads the model from the menu archive, lights it from
// the scene and draws it with the main camera.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00425690
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, kTaskWork);
    a0 = 4;
    jal(ctx, 0x4256ACu, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    jal(ctx, 0x4256B8u, gen::fn_sub_198560_00198560);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x90);
    swc1(f2, sp, 0x94);
    swc1(f1, sp, 0x98);
    swc1(f0, sp, 0x9C);
    jal(ctx, 0x4256E0u, gen::fn_sub_198570_00198570);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x80);
    swc1(f2, sp, 0x84);
    swc1(f1, sp, 0x88);
    swc1(f0, sp, 0x8C);
    jal(ctx, 0x425708u, gen::fn_sub_198570_00198570);
    lw(v0, v0, 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, 0x40);
    a0 = 8;
    for (;;) {
        // 0x00425720
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
    // 0x00425744
    charge(ctx, 39);
    lw(a0, gp, -19492);  // 0x7CE0CC
    jal(ctx, 0x425748u, gen::fn_sub_198540_00198540);
    s2 = v0;
    jal(ctx, 0x425754u, gen::fn_sub_198580_00198580);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x425764u, gen::fn_sub_49C480_0049c480);
    jal(ctx, 0x42576Cu, gen::fn_sub_198560_00198560);
    s2 = v0;
    jal(ctx, 0x425778u, gen::fn_sub_19FD40_0019fd40);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x425788u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x425790u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(s0, 272);
    jal(ctx, 0x4257A0u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x4257A8u, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(s0, 288);
    a2 = 0;
    jal(ctx, 0x4257BCu, gen::fn_sub_4CB7F0_004cb7f0);
    jal(ctx, 0x4257C4u, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x4257D0u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 != 0) {
        // 0x004257e0
        charge(ctx, 4);
        lb(v1, s1, 0);
        v0 = 4;
        if (v1 == v0) {
            // 0x00425acc
            charge(ctx, 8);
            lb(v0, s1, 2);
            v1 = sll(v0, 2);
            v0 = 0x960000;
            v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x425AE4u, gen::fn_sub_317A20_00317a20);
        } else {
            // 0x004257f0
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x00425aa4
                charge(ctx, 10);
                lb(v0, s1, 3);
                v1 = sll(v0, 2);
                v0 = 0x960000;
                v0 = addiu(v0, -16736);  // &0x95BEA0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x425ABCu, gen::fn_sub_317A20_00317a20);
            } else {
                // 0x004257fc
                charge(ctx, 3);
                v0 = 2;
                if (v1 != v0) {
                    // 0x00425808
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x00425814
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00425824
                            charge(ctx, 9);
                            jal(ctx, 0x425824u, gen::fn_sub_421760_00421760);  // -> the Y map task slot
                            lw(a0, v0, 0);
                            jal(ctx, 0x425830u, gen::fn_sub_421F10_00421f10);
                            s2 = v0;
                            s0 = 1;
                            for (;;) {
                                // 0x00425890
                                charge(ctx, 3);
                                v0 = slti(s0, 7);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x00425848
                                charge(ctx, 18);
                                a1 = addiu(s0, -1);
                                a0 = s2;
                                a2 = addiu(sp, 0xAC);
                                jal(ctx, 0x425854u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                a0 = 0;
                                a1 = 0;
                                a2 = v0;
                                lw(a3, sp, 0xAC);
                                t0 = 0;
                                jal(ctx, 0x425870u, gen::fn_sub_316BD0_00316bd0);
                                a0 = sll(s0, 2);
                                v1 = 0x960000;
                                v1 = addiu(v1, -16736);  // &0x95BEA0
                                v1 = addu(v1, a0);
                                sw(v0, v1, -4);
                                s0 = addiu(s0, 1);
                            }
                            // 0x0042589c
                            charge(ctx, 3);
                            s0 = 0;
                            for (;;) {
                                // 0x004258f0
                                charge(ctx, 3);
                                v0 = slti(s0, 6);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x004258a8
                                charge(ctx, 18);
                                a1 = addiu(s0, 6);
                                a0 = s2;
                                a2 = addiu(sp, 0xAC);
                                jal(ctx, 0x4258B4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                a0 = 0;
                                a1 = 0;
                                a2 = v0;
                                lw(a3, sp, 0xAC);
                                t0 = 0;
                                jal(ctx, 0x4258D0u, gen::fn_sub_316BD0_00316bd0);
                                a0 = sll(s0, 2);
                                v1 = 0x960000;
                                v1 = addiu(v1, -16704);  // &0x95BEC0 kLmapModels: the area models
                                v1 = addu(v1, a0);
                                sw(v0, v1, 0);
                                s0 = addiu(s0, 1);
                            }
                            // 0x004258fc
                            charge(ctx, 2);
                            v0 = 1;
                            sb(v0, s1, 0);
                            goto L_00425904;
                        }
                        // 0x0042581c
                        charge(ctx, 2);
                        goto L_00425aec;
                    }
                L_00425904:
                    charge(ctx, 6);
                    v0 = 0x960000;
                    lw(a0, v0, -16704);  // 0x95BEC0
                    jal(ctx, 0x42590Cu, gen::fn_sub_316F70_00316f70);
                    if (v0 != 0) {
                        // 0x0042591c
                        charge(ctx, 6);
                        v0 = 0x960000;
                        lw(a0, v0, -16700);  // 0x95BEC4
                        jal(ctx, 0x425924u, gen::fn_sub_316F70_00316f70);
                        if (v0 != 0) {
                            // 0x00425934
                            charge(ctx, 6);
                            v0 = 0x960000;
                            lw(a0, v0, -16696);  // 0x95BEC8
                            jal(ctx, 0x42593Cu, gen::fn_sub_316F70_00316f70);
                            if (v0 != 0) {
                                // 0x0042594c
                                charge(ctx, 6);
                                v0 = 0x960000;
                                lw(a0, v0, -16692);  // 0x95BECC
                                jal(ctx, 0x425954u, gen::fn_sub_316F70_00316f70);
                                if (v0 != 0) {
                                    // 0x00425964
                                    charge(ctx, 6);
                                    v0 = 0x960000;
                                    lw(a0, v0, -16688);  // 0x95BED0
                                    jal(ctx, 0x42596Cu, gen::fn_sub_316F70_00316f70);
                                    if (v0 != 0) {
                                        // 0x0042597c
                                        charge(ctx, 6);
                                        v0 = 0x960000;
                                        lw(a0, v0, -16684);  // 0x95BED4
                                        jal(ctx, 0x425984u, gen::fn_sub_316F70_00316f70);
                                        if (v0 != 0) {
                                            // 0x00425994
                                            charge(ctx, 6);
                                            v0 = 0x960000;
                                            lw(a0, v0, -16736);  // 0x95BEA0
                                            jal(ctx, 0x42599Cu, gen::fn_sub_316F70_00316f70);
                                            if (v0 != 0) {
                                                // 0x004259ac
                                                charge(ctx, 6);
                                                v0 = 0x960000;
                                                lw(a0, v0, -16732);  // 0x95BEA4
                                                jal(ctx, 0x4259B4u, gen::fn_sub_316F70_00316f70);
                                                if (v0 != 0) {
                                                    // 0x004259c4
                                                    charge(ctx, 6);
                                                    v0 = 0x960000;
                                                    lw(a0, v0, -16728);  // 0x95BEA8
                                                    jal(ctx, 0x4259CCu, gen::fn_sub_316F70_00316f70);
                                                    if (v0 != 0) {
                                                        // 0x004259dc
                                                        charge(ctx, 6);
                                                        v0 = 0x960000;
                                                        lw(a0, v0, -16724);  // 0x95BEAC
                                                        jal(ctx, 0x4259E4u, gen::fn_sub_316F70_00316f70);
                                                        if (v0 != 0) {
                                                            // 0x004259f4
                                                            charge(ctx, 6);
                                                            v0 = 0x960000;
                                                            lw(a0, v0, -16720);  // 0x95BEB0
                                                            jal(ctx, 0x4259FCu, gen::fn_sub_316F70_00316f70);
                                                            if (v0 != 0) {
                                                                // 0x00425a0c
                                                                charge(ctx, 6);
                                                                v0 = 0x960000;
                                                                lw(a0, v0, -16716);  // 0x95BEB4
                                                                jal(ctx, 0x425A14u, gen::fn_sub_316F70_00316f70);
                                                                if (v0 != 0) {
                                                                    // 0x00425a24
                                                                    charge(ctx, 14);
                                                                    lb(v0, s1, 1);
                                                                    v1 = sll(v0, 2);
                                                                    v0 = 0x960000;
                                                                    v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                                                                    v0 = addu(v0, v1);
                                                                    lw(a0, v0, 0);
                                                                    a1 = 0;
                                                                    a2 = 0;
                                                                    a3 = 0;
                                                                    t0 = 1;
                                                                    jal(ctx, 0x425A4Cu, gen::fn_sub_3182D0_003182d0);
                                                                    v0 = 2;
                                                                    sb(v0, s1, 0);
                                                                    goto L_00425a5c;
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
                    goto L_00425aec;
                }
            L_00425a5c:
                charge(ctx, 18);
                lb(v0, s1, 1);
                v1 = sll(v0, 2);
                v0 = 0x960000;
                v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x425A74u, gen::fn_sub_317A20_00317a20);
                lb(v0, s1, 3);
                v1 = sll(v0, 2);
                v0 = 0x960000;
                v0 = addiu(v0, -16736);  // &0x95BEA0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x425A94u, gen::fn_sub_317A20_00317a20);
            }
        }
    }
L_00425aec:
    charge(ctx, 42);
    jal(ctx, 0x425AECu, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x425AF8u, gen::fn_RwCameraEndUpdate_004c9d00);
    lw(a0, gp, -19492);  // 0x7CE0CC
    jal(ctx, 0x425B04u, gen::fn_sub_198540_00198540);
    s0 = v0;
    jal(ctx, 0x425B10u, gen::fn_sub_198580_00198580);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x425B20u, gen::fn_sub_49C3D0_0049c3d0);
    jal(ctx, 0x425B28u, gen::fn_sub_198560_00198560);
    a0 = v0;
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x425B38u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x425B40u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x425B50u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x425B58u, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x40);
    a2 = 0;
    jal(ctx, 0x425B6Cu, gen::fn_sub_4CB7F0_004cb7f0);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00425BA0 sub_425BA0 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapModelDestroy] The destroy callback of "y_lmap_model proc".
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425ba0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = 0;
    for (;;) {
        // 0x00425be8
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00425bc0
        charge(ctx, 7);
        v1 = sll(s1, 2);
        v0 = 0x960000;
        v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        if (a0 != 0) {
            // 0x00425bdc
            charge(ctx, 2);
            jal(ctx, 0x425BDCu, gen::fn_sub_3174E0_003174e0);
        }
        // 0x00425be4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00425bf4
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00425c28
        charge(ctx, 3);
        v0 = slti(s1, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00425c00
        charge(ctx, 7);
        v1 = sll(s1, 2);
        v0 = 0x960000;
        v0 = addiu(v0, -16736);  // &0x95BEA0
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        if (a0 != 0) {
            // 0x00425c1c
            charge(ctx, 2);
            jal(ctx, 0x425C1Cu, gen::fn_sub_3174E0_003174e0);
        }
        // 0x00425c24
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00425c34
    charge(ctx, 11);
    lw(a0, s0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x425C40u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00425C60 Y_LMap_CreateLmapModelTask -- 164 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_CreateLmapModelTask: the model task and its work.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateLmapModelTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425c60
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 4;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x425C90u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00425cb0
        charge(ctx, 14);
        a0 = s2;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17408);  // "y_lmap_model proc"
        a2 = 2097;
        a3 = 0x420000;
        a3 = addiu(a3, 22160);  // &sub_425690
        t0 = 0x420000;
        t0 = addiu(t0, 23456);  // &sub_425BA0
        t1 = s0;
        jal(ctx, 0x425CD4u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, 0);
        sb(s1, s0, 1);
        sb(zero, s0, 2);
    } else {
        // 0x00425ca4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00425ce8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00425D10 sub_425D10 -- 24 bytes; leaf frame (no stack)
// [lmapModelSetTarget] Record byte 1 = $a1, state 1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425D10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00425d10
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    sb(a1, a0, 1);
    v1 = 1;
    sb(v1, a0, 0);
}

// 0x00425D30 sub_425D30 -- 24 bytes; leaf frame (no stack)
// [lmapModelSetPos] Record bytes 1 / 2 = $a1 / $a2, and the current position byte gp-0x463C = $a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425D30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00425d30
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 1);
    sb(a2, v1, 2);
    sb(a1, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
}

// 0x00425D50 sub_425D50 -- 740 bytes; leaf frame (no stack)
// [lmapPathStep] The animation from area $a0 to area $a1 (both 0..5, s8): a 6 x 6 matrix of nested jump
// tables (0x7BC320, then 0x7BC300 / ... per row) giving 0..5; 0 out of range.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_425D50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00425d50
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;
    v1 = dsll32(a0, 24);
    v1 = dsra32(v1, 24);
    at = sltiu(v1, 6);
    if (at != 0) {
        // 0x00425d68
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -15584);  // &0x7BC320
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x425D84u:  // table[0]
            // 0x00425d84
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425d98
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15616);  // &0x7BC300
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425DB4u:  // table[0]
                    // 0x00425db4
                    charge(ctx, 2);
                    break;
                case 0x425DBCu:  // table[1]
                    // 0x00425dbc
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x425DC8u:  // table[2]
                    // 0x00425dc8
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x425DD4u:  // table[3]
                    // 0x00425dd4
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x425DE0u:  // table[4]
                    // 0x00425de0
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x425DECu:  // table[5]
                    // 0x00425dec
                    charge(ctx, 3);
                    v0 = 5;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x425DF8u:  // table[1]
            // 0x00425df8
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425e0c
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15648);  // "(^B"
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425E28u:  // table[0]
                    // 0x00425e28
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x425E34u:  // table[1]
                    // 0x00425e34
                    charge(ctx, 2);
                    break;
                case 0x425E3Cu:  // table[2]
                    // 0x00425e3c
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x425E48u:  // table[3]
                    // 0x00425e48
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x425E54u:  // table[4]
                    // 0x00425e54
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x425E60u:  // table[5]
                    // 0x00425e60
                    charge(ctx, 3);
                    v0 = 5;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x425E6Cu:  // table[2]
            // 0x00425e6c
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425e80
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15680);  // &0x7BC2C0
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425E9Cu:  // table[0]
                    // 0x00425e9c
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x425EA8u:  // table[1]
                    // 0x00425ea8
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x425EB4u:  // table[2]
                    // 0x00425eb4
                    charge(ctx, 2);
                    break;
                case 0x425EBCu:  // table[3]
                    // 0x00425ebc
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x425EC8u:  // table[4]
                    // 0x00425ec8
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x425ED4u:  // table[5]
                    // 0x00425ed4
                    charge(ctx, 3);
                    v0 = 5;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x425EE0u:  // table[3]
            // 0x00425ee0
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425ef4
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15712);  // &0x7BC2A0
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425F10u:  // table[0]
                    // 0x00425f10
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x425F1Cu:  // table[1]
                    // 0x00425f1c
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x425F28u:  // table[2]
                    // 0x00425f28
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x425F34u:  // table[3]
                    // 0x00425f34
                    charge(ctx, 2);
                    break;
                case 0x425F3Cu:  // table[4]
                    // 0x00425f3c
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x425F48u:  // table[5]
                    // 0x00425f48
                    charge(ctx, 3);
                    v0 = 5;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x425F54u:  // table[4]
            // 0x00425f54
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425f68
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15744);  // &0x7BC280
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425F84u:  // table[0]
                    // 0x00425f84
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x425F90u:  // table[1]
                    // 0x00425f90
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x425F9Cu:  // table[2]
                    // 0x00425f9c
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x425FA8u:  // table[3]
                    // 0x00425fa8
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x425FB4u:  // table[4]
                    // 0x00425fb4
                    charge(ctx, 2);
                    break;
                case 0x425FBCu:  // table[5]
                    // 0x00425fbc
                    charge(ctx, 3);
                    v0 = 5;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x425FC8u:  // table[5]
            // 0x00425fc8
            charge(ctx, 5);
            v1 = dsll32(a1, 24);
            v1 = dsra32(v1, 24);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x00425fdc
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -15776);  // &0x7BC260
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x425FF8u:  // table[0]
                    // 0x00425ff8
                    charge(ctx, 3);
                    v0 = 1;
                    break;
                case 0x426004u:  // table[1]
                    // 0x00426004
                    charge(ctx, 3);
                    v0 = 2;
                    break;
                case 0x426010u:  // table[2]
                    // 0x00426010
                    charge(ctx, 3);
                    v0 = 3;
                    break;
                case 0x42601Cu:  // table[3]
                    // 0x0042601c
                    charge(ctx, 3);
                    v0 = 4;
                    break;
                case 0x426028u:  // table[4]
                    // 0x00426028
                    charge(ctx, 1);
                    v0 = 5;
                    break;
                case 0x42602Cu:  // table[5]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0042602c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00426040 sub_426040 -- 16 bytes; leaf frame (no stack)
// [lmapModelSetByte3] Record byte 3 = $a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_426040(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00426040
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 3);
}

// 0x00426050 sub_426050 -- 20 bytes; leaf frame (no stack)
// [lmapModelSetState3] Record byte 0 = 3.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_426050(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00426050
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 3;
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 0);
}

// 0x00426070 sub_426070 -- 24 bytes; leaf frame (no stack)
// [lmapModelIsMoving] Record byte 0 != 2.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_426070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00426070
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lb(v0, v0, 0);
    v0 = v0 ^ 0x2;
    v0 = sltu(0, v0);
}

// 0x00426090 sub_426090 -- 12 bytes; leaf frame (no stack)
// [lmapGetModelMoveSlot] Returns gp-0x4638 (the "lmap_model_move" task slot).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_426090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00426090
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = addiu(gp, -17976);  // &0x7CE6B8 gp-0x4638: the lmap_model_move task slot
}

// 0x004260A0 sub_4260A0 -- 1020 bytes; frame 0xA0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [lmapModelMoveUpdate] The "lmap_model_move" update: saves the lights and camera, plays the path animation
// (sub_425D50) of the model 0x95BEC0[current] toward the target, sets the shared record's byte 8 when done, restores
// the lights and camera.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4260A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x004260a0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 4;
    jal(ctx, 0x4260BCu, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    lw(s0, s0, kTaskWork);
    jal(ctx, 0x4260CCu, gen::fn_sub_198560_00198560);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x90);
    swc1(f2, sp, 0x94);
    swc1(f1, sp, 0x98);
    swc1(f0, sp, 0x9C);
    jal(ctx, 0x4260F4u, gen::fn_sub_198570_00198570);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x80);
    swc1(f2, sp, 0x84);
    swc1(f1, sp, 0x88);
    swc1(f0, sp, 0x8C);
    jal(ctx, 0x42611Cu, gen::fn_sub_198570_00198570);
    lw(v0, v0, 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, 0x40);
    a0 = 8;
    for (;;) {
        // 0x00426134
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
    // 0x00426158
    charge(ctx, 39);
    lw(a0, gp, -19492);  // 0x7CE0CC
    jal(ctx, 0x42615Cu, gen::fn_sub_198540_00198540);
    s2 = v0;
    jal(ctx, 0x426168u, gen::fn_sub_198580_00198580);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x426178u, gen::fn_sub_49C480_0049c480);
    jal(ctx, 0x426180u, gen::fn_sub_198560_00198560);
    s2 = v0;
    jal(ctx, 0x42618Cu, gen::fn_sub_19FD40_0019fd40);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x42619Cu, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x4261A4u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(s1, 272);
    jal(ctx, 0x4261B4u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x4261BCu, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(s1, 288);
    a2 = 0;
    jal(ctx, 0x4261D0u, gen::fn_sub_4CB7F0_004cb7f0);
    jal(ctx, 0x4261D8u, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x4261E4u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 != 0) {
        // 0x004261f4
        charge(ctx, 4);
        lb(v1, s0, 0);
        v0 = 2;
        if (v1 == v0) {
            // 0x004263c8
            charge(ctx, 11);
            lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
            v1 = sll(v0, 2);
            v0 = 0x960000;
            v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x4263E0u, gen::fn_sub_317A20_00317a20);
            v1 = 1;
            lw(v0, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
            sb(v1, v0, 8);
        } else {
            // 0x00426204
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x004262d0
                charge(ctx, 13);
                lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                v1 = sll(v0, 2);
                v0 = 0x960000;
                v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x4262E8u, gen::fn_sub_317A20_00317a20);
                v0 = 0x7E0000;
                lhu(v0, v0, 2380);  // 0x7E094C pad: held
                v0 = v0 & 0x20;
                if (v0 == 0) {
                    // 0x00426338
                    charge(ctx, 11);
                    lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    v1 = sll(v0, 2);
                    v0 = 0x960000;
                    v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                    v1 = addu(v0, v1);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, v1, 0);
                    a1 = 0;
                    jal(ctx, 0x42635Cu, gen::fn_sub_3189F0_003189f0);
                } else {
                    // 0x00426304
                    charge(ctx, 13);
                    lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    v1 = sll(v0, 2);
                    v0 = 0x960000;
                    v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                    v1 = addu(v0, v1);
                    v0 = 0x40000000;
                    mtc1(v0, f12);
                    lw(a0, v1, 0);
                    a1 = 0;
                    jal(ctx, 0x426328u, gen::fn_sub_3189F0_003189f0);
                }
                // 0x00426364
                charge(ctx, 10);
                lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                v0 = sll(v0, 2);
                a0 = 0x960000;
                a0 = addiu(a0, -16704);  // &0x95BEC0 kLmapModels: the area models
                v0 = addu(a0, v0);
                lw(v0, v0, 0);
                lbu(v1, v0, 238);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0042638c
                    charge(ctx, 15);
                    v0 = 2;
                    sb(v0, s0, 0);
                    lb(v0, s0, 1);
                    sb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    v0 = sll(v0, 2);
                    v0 = addu(a0, v0);
                    lw(a0, v0, 0);
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x4263B8u, gen::fn_sub_3182D0_003182d0);
                }
            } else {
                // 0x00426210
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00426220
                    charge(ctx, 27);
                    lb(a0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    lb(a1, s0, 1);
                    jal(ctx, 0x426228u, gen::fn_sub_425D50_00425d50);
                    a2 = dsll32(v0, 24);
                    a2 = dsra32(a2, 24);
                    lb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    v1 = sll(v0, 2);
                    v0 = 0x960000;
                    v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                    v0 = addu(v0, v1);
                    lw(a0, v0, 0);
                    a1 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x42625Cu, gen::fn_sub_3182D0_003182d0);
                    v0 = 1;
                    sb(v0, s0, 0);
                    lb(a0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                    lb(a1, s0, 1);
                    jal(ctx, 0x426274u, gen::fn_sub_425D50_00425d50);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (v0 == 0) {
                        // 0x0042628c
                        charge(ctx, 17);
                        lb(v0, s0, 1);
                        sb(v0, gp, -17980);  // 0x7CE6B4 gp-0x463C: the model's current area
                        v1 = sll(v0, 2);
                        v0 = 0x960000;
                        v0 = addiu(v0, -16704);  // &0x95BEC0 kLmapModels: the area models
                        v0 = addu(v0, v1);
                        lw(a0, v0, 0);
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        jal(ctx, 0x4262B8u, gen::fn_sub_3182D0_003182d0);
                        v0 = 2;
                        sb(v0, s0, 0);
                    }
                } else {
                    // 0x00426218
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x004263f4
    charge(ctx, 42);
    jal(ctx, 0x4263F4u, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x426400u, gen::fn_RwCameraEndUpdate_004c9d00);
    lw(a0, gp, -19492);  // 0x7CE0CC
    jal(ctx, 0x42640Cu, gen::fn_sub_198540_00198540);
    s0 = v0;
    jal(ctx, 0x426418u, gen::fn_sub_198580_00198580);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x426428u, gen::fn_sub_49C3D0_0049c3d0);
    jal(ctx, 0x426430u, gen::fn_sub_198560_00198560);
    a0 = v0;
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x426440u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x426448u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(sp, 0x80);
    jal(ctx, 0x426458u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x426460u, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x40);
    a2 = 0;
    jal(ctx, 0x426474u, gen::fn_sub_4CB7F0_004cb7f0);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004264A0 sub_4264A0 -- 44 bytes; frame 0x10: ra sp+0x0
// [lmapModelMoveDestroy] The destroy callback of "lmap_model_move": RwFree(work).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_4264A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004264a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x4264B4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004264D0 Y_LMap_CreateLmapModelMoveTask -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Y_LMap_CreateLmapModelMoveTask: the move task and its work.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateLmapModelMoveTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004264d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = addiu(gp, -17976);  // &0x7CE6B8 gp-0x4638: the lmap_model_move task slot
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x4264F8u, gen::fn_memset_00521408);
    a0 = 1;
    a1 = 2;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x426514u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00426534
        charge(ctx, 16);
        a0 = s2;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17440);  // "lmap_model_move"
        a2 = 2097;
        a3 = 0x420000;
        a3 = addiu(a3, 24736);  // &sub_4260A0
        t0 = 0x420000;
        t0 = addiu(t0, 25760);  // &sub_4264A0
        t1 = s0;
        jal(ctx, 0x426558u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, 0);
        sb(s1, s0, 1);
        sw(v0, gp, -17976);  // 0x7CE6B8
        lw(v1, gp, -17992);  // 0x7CE6A8 gp-0x4648: the Y map shared record (sub_421F20)
        sb(zero, v1, 8);
    } else {
        // 0x00426528
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00426574 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00426590 sub_426590 -- 4260 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [tmxDispUpdate] The "y_tmx_disp_proc" update: render states by the blend mode +396, then the texture
// quad(s) by the shape +321 through RwIm2DRenderPrimitive, unless hidden (+336).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_426590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x00426590
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, kTaskWork);
    lb(v1, s1, 396);
    if (v1 != 0) {
        // 0x0042669c
        charge(ctx, 3);
        a1 = 1;
        if (v1 != a1) {
            // 0x00426790
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x0042679c
                charge(ctx, 56);
                s0 = 0x960000;
                s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
                a0 = 6;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x4267ACu, v0.u());
                a0 = 7;
                a1 = 2;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x4267C0u, v0.u());
                a0 = 8;
                a1 = 1;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x4267D4u, v0.u());
                a0 = 10;
                a1 = 5;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x4267E8u, v0.u());
                a0 = 11;
                a1 = 6;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x4267FCu, v0.u());
                a0 = 9;
                a1 = 2;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x426810u, v0.u());
                a0 = 12;
                a1 = 1;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x426824u, v0.u());
                lw(v0, s1, 316);
                a0 = 1;
                lw(a1, v0, 0);
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x42683Cu, v0.u());
                a0 = 2;
                a1 = 3;
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x426850u, v0.u());
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x426860u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x426874u, gen::fn_RpSkyRenderStateSet_004d7f60);
            }
        } else {
            // 0x004266a8
            charge(ctx, 58);
            s0 = 0x960000;
            s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
            a0 = 6;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x4266B8u, v0.u());
            a0 = 7;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x4266CCu, v0.u());
            a0 = 8;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x4266E0u, v0.u());
            a0 = 10;
            a1 = 5;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x4266F4u, v0.u());
            a0 = 11;
            a1 = 6;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x426708u, v0.u());
            a0 = 9;
            a1 = 2;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x42671Cu, v0.u());
            a0 = 12;
            a1 = 1;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x426730u, v0.u());
            lw(v0, s1, 316);
            a0 = 1;
            lw(a1, v0, 0);
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x426748u, v0.u());
            a0 = 2;
            a1 = 3;
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            jalr(ctx, 0x42675Cu, v0.u());
            a0 = 2;
            a1 = 68;
            jal(ctx, 0x42676Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
            a0 = 3;
            v0 = 0x70000;
            a1 = v0 | 0x17FB;
            jal(ctx, 0x426780u, gen::fn_RpSkyRenderStateSet_004d7f60);
        }
    } else {
        // 0x004265b0
        charge(ctx, 59);
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 6;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x4265C4u, v0.u());
        a0 = 7;
        a1 = 2;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x4265D8u, v0.u());
        a0 = 8;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x4265ECu, v0.u());
        a0 = 10;
        a1 = 5;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x426600u, v0.u());
        a0 = 11;
        a1 = 6;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x426614u, v0.u());
        a0 = 9;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x426628u, v0.u());
        a0 = 12;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x42663Cu, v0.u());
        lw(v0, s1, 316);
        a0 = 1;
        lw(a1, v0, 0);
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x426654u, v0.u());
        a0 = 2;
        a1 = 3;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x426668u, v0.u());
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x426678u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x42668Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    // 0x0042687c
    charge(ctx, 4);
    lb(v0, s1, 336);
    a0 = 1;
    if (v0 != a0) {
        // 0x00426898
        charge(ctx, 4);
        lb(v1, s1, 0);
        v0 = 2;
        if (v1 == v0) {
            // 0x0042760c
            charge(ctx, 3);
            v0 = si(-1);
        } else {
            // 0x004268a8
            charge(ctx, 2);
            if (v1 != a0) {
                // 0x004268b0
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_004268c0;
                }
                // 0x004268b8
                charge(ctx, 2);
            L_00427618:
                charge(ctx, 1);
                v0 = 0;
                // 0x0042761c (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_004268c0:
            charge(ctx, 11);
            jal(ctx, 0x4268C0u, gen::fn_sub_198590_00198590);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, v0, 128);
            div_s(f0, f1, f0);
            lb(a0, s1, 321);
            v0 = 4;
            if (a0 == v0) {
                // 0x0042738c
                charge(ctx, 4);
                a3 = 0;
                v0 = 0x960000;
                for (;;) {
                    // 0x004274c4
                    charge(ctx, 3);
                    v1 = slti(a3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042739c
                    charge(ctx, 12);
                    v1 = sll(a3, 6);
                    a2 = addu(s1, v1);
                    lwc1(f2, v0, 136);
                    lwc1(f1, s1, 304);
                    sub_s(f1, f2, f1);
                    swc1(f1, a2, 24);
                    swc1(f0, a2, 40);
                    v1 = sll(a3, 2);
                    a1 = addu(s1, v1);
                    lbu(v1, a1, 272);
                    if (i64(v1) < 0) {
                        // 0x004273e0
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x004273cc
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x004273fc
                    charge(ctx, 4);
                    swc1(f1, a2, 48);
                    lbu(v1, a1, 273);
                    if (i64(v1) < 0) {
                        // 0x00427420
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x0042740c
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x0042743c
                    charge(ctx, 4);
                    swc1(f1, a2, 52);
                    lbu(v1, a1, 274);
                    if (i64(v1) < 0) {
                        // 0x00427460
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x0042744c
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x0042747c
                    charge(ctx, 4);
                    swc1(f1, a2, 56);
                    lbu(v1, a1, 275);
                    if (i64(v1) < 0) {
                        // 0x004274a0
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x0042748c
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x004274bc
                    charge(ctx, 2);
                    swc1(f1, a2, 60);
                    a3 = addiu(a3, 1);
                }
                // 0x004274d0
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x004275ec
                    charge(ctx, 4);
                    lw(v0, s1, 300);
                    v0 = slt(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004274dc
                    charge(ctx, 68);
                    sw(zero, s1, 32);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    v1 = 0x3F800000;
                    mtc1(v1, f4);
                    div_s(f1, f4, f0);
                    mtc1(s0, f0);
                    cvt_s_w(f3, f0);
                    mul_s(f0, f1, f3);
                    swc1(f0, s1, 36);
                    sw(v1, s1, 96);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    div_s(f0, f4, f0);
                    mul_s(f0, f0, f3);
                    swc1(f0, s1, 100);
                    sw(zero, s1, 160);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    div_s(f1, f4, f0);
                    v0 = addiu(s0, 1);
                    mtc1(v0, f0);
                    cvt_s_w(f2, f0);
                    mul_s(f0, f1, f2);
                    swc1(f0, s1, 164);
                    sw(v1, s1, 224);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    div_s(f0, f4, f0);
                    mul_s(f0, f0, f2);
                    swc1(f0, s1, 228);
                    lwc1(f0, s1, 308);
                    swc1(f0, s1, 16);
                    lwc1(f0, s1, 312);
                    add_s(f0, f0, f3);
                    swc1(f0, s1, 20);
                    lwc1(f1, s1, 308);
                    lwc1(f0, s1, 296);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 80);
                    lwc1(f0, s1, 312);
                    add_s(f0, f0, f3);
                    swc1(f0, s1, 84);
                    lwc1(f0, s1, 308);
                    swc1(f0, s1, 144);
                    lwc1(f0, s1, 312);
                    add_s(f0, f0, f2);
                    swc1(f0, s1, 148);
                    lwc1(f1, s1, 308);
                    lwc1(f0, s1, 296);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 208);
                    lwc1(f0, s1, 312);
                    add_s(f0, f0, f2);
                    swc1(f0, s1, 212);
                    a0 = 4;
                    a1 = addiu(s1, 16);
                    a2 = a0;
                    v0 = 0x960000;
                    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                    jalr(ctx, 0x4275E0u, v0.u());
                    s0 = addiu(s0, 1);
                }
            L_004275fc:
                charge(ctx, 4);
                v0 = 1;
                sb(v0, s1, 0);
                goto L_00427618;
            }
            // 0x004268ec
            charge(ctx, 3);
            v0 = 3;
            if (a0 == v0) {
                // 0x00427194
                charge(ctx, 4);
                a3 = 0;
                v0 = 0x960000;
                for (;;) {
                    // 0x004272cc
                    charge(ctx, 3);
                    v1 = slti(a3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x004271a4
                    charge(ctx, 12);
                    v1 = sll(a3, 6);
                    a2 = addu(s1, v1);
                    lwc1(f2, v0, 136);
                    lwc1(f1, s1, 304);
                    sub_s(f1, f2, f1);
                    swc1(f1, a2, 24);
                    swc1(f0, a2, 40);
                    v1 = sll(a3, 2);
                    a1 = addu(s1, v1);
                    lbu(v1, a1, 272);
                    if (i64(v1) < 0) {
                        // 0x004271e8
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x004271d4
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427204
                    charge(ctx, 4);
                    swc1(f1, a2, 48);
                    lbu(v1, a1, 273);
                    if (i64(v1) < 0) {
                        // 0x00427228
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427214
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427244
                    charge(ctx, 4);
                    swc1(f1, a2, 52);
                    lbu(v1, a1, 274);
                    if (i64(v1) < 0) {
                        // 0x00427268
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427254
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427284
                    charge(ctx, 4);
                    swc1(f1, a2, 56);
                    lbu(v1, a1, 275);
                    if (i64(v1) < 0) {
                        // 0x004272a8
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427294
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x004272c4
                    charge(ctx, 2);
                    swc1(f1, a2, 60);
                    a3 = addiu(a3, 1);
                }
                // 0x004272d8
                charge(ctx, 45);
                sw(zero, s1, 32);
                sw(zero, s1, 36);
                lwc1(f0, s1, 308);
                swc1(f0, s1, 16);
                lwc1(f0, s1, 312);
                swc1(f0, s1, 20);
                lwc1(f0, s1, 372);
                swc1(f0, s1, 96);
                sw(zero, s1, 100);
                lwc1(f1, s1, 308);
                lwc1(f0, s1, 388);
                add_s(f0, f1, f0);
                swc1(f0, s1, 80);
                lwc1(f0, s1, 312);
                swc1(f0, s1, 84);
                sw(zero, s1, 160);
                lwc1(f0, s1, 376);
                swc1(f0, s1, 164);
                lwc1(f0, s1, 308);
                swc1(f0, s1, 144);
                lwc1(f1, s1, 312);
                lwc1(f0, s1, 392);
                add_s(f0, f1, f0);
                swc1(f0, s1, 148);
                lwc1(f0, s1, 372);
                swc1(f0, s1, 224);
                lwc1(f0, s1, 376);
                swc1(f0, s1, 228);
                lwc1(f1, s1, 308);
                lwc1(f0, s1, 388);
                add_s(f0, f1, f0);
                swc1(f0, s1, 208);
                lwc1(f1, s1, 312);
                lwc1(f0, s1, 392);
                add_s(f0, f1, f0);
                swc1(f0, s1, 212);
                a0 = 4;
                a1 = addiu(s1, 16);
                a2 = a0;
                v0 = 0x960000;
                lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                jalr(ctx, 0x42737Cu, v0.u());
                goto L_004275fc;
            }
            // 0x004268f8
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x00426f98
                charge(ctx, 4);
                a3 = 0;
                v0 = 0x960000;
                for (;;) {
                    // 0x004270d0
                    charge(ctx, 3);
                    v1 = slti(a3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00426fa8
                    charge(ctx, 12);
                    v1 = sll(a3, 6);
                    a2 = addu(s1, v1);
                    lwc1(f2, v0, 136);
                    lwc1(f1, s1, 304);
                    sub_s(f1, f2, f1);
                    swc1(f1, a2, 24);
                    swc1(f0, a2, 40);
                    v1 = sll(a3, 2);
                    a1 = addu(s1, v1);
                    lbu(v1, a1, 272);
                    if (i64(v1) < 0) {
                        // 0x00426fec
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426fd8
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427008
                    charge(ctx, 4);
                    swc1(f1, a2, 48);
                    lbu(v1, a1, 273);
                    if (i64(v1) < 0) {
                        // 0x0042702c
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427018
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427048
                    charge(ctx, 4);
                    swc1(f1, a2, 52);
                    lbu(v1, a1, 274);
                    if (i64(v1) < 0) {
                        // 0x0042706c
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427058
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00427088
                    charge(ctx, 4);
                    swc1(f1, a2, 56);
                    lbu(v1, a1, 275);
                    if (i64(v1) < 0) {
                        // 0x004270ac
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00427098
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x004270c8
                    charge(ctx, 2);
                    swc1(f1, a2, 60);
                    a3 = addiu(a3, 1);
                }
                // 0x004270dc
                charge(ctx, 46);
                sw(zero, s1, 32);
                sw(zero, s1, 36);
                lwc1(f0, s1, 308);
                swc1(f0, s1, 16);
                lwc1(f0, s1, 312);
                swc1(f0, s1, 20);
                v0 = 0x3F800000;
                sw(v0, s1, 96);
                sw(zero, s1, 100);
                lwc1(f1, s1, 308);
                lwc1(f0, s1, 296);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, s1, 80);
                lwc1(f0, s1, 312);
                swc1(f0, s1, 84);
                sw(zero, s1, 160);
                sw(v0, s1, 164);
                lwc1(f0, s1, 308);
                swc1(f0, s1, 144);
                lwc1(f1, s1, 312);
                lwc1(f0, s1, 300);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, s1, 148);
                sw(v0, s1, 224);
                sw(v0, s1, 228);
                lwc1(f1, s1, 308);
                lwc1(f0, s1, 296);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, s1, 208);
                lwc1(f1, s1, 312);
                lwc1(f0, s1, 300);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, s1, 212);
                a0 = 4;
                a1 = addiu(s1, 16);
                a2 = a0;
                v0 = 0x960000;
                lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                jalr(ctx, 0x427184u, v0.u());
                goto L_004275fc;
            }
            // 0x00426904
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x00426d00
                charge(ctx, 4);
                a3 = 0;
                v0 = 0x960000;
                for (;;) {
                    // 0x00426e38
                    charge(ctx, 3);
                    v1 = slti(a3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00426d10
                    charge(ctx, 12);
                    v1 = sll(a3, 6);
                    a2 = addu(s1, v1);
                    lwc1(f2, v0, 136);
                    lwc1(f1, s1, 304);
                    sub_s(f1, f2, f1);
                    swc1(f1, a2, 24);
                    swc1(f0, a2, 40);
                    v1 = sll(a3, 2);
                    a1 = addu(s1, v1);
                    lbu(v1, a1, 272);
                    if (i64(v1) < 0) {
                        // 0x00426d54
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426d40
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426d70
                    charge(ctx, 4);
                    swc1(f1, a2, 48);
                    lbu(v1, a1, 273);
                    if (i64(v1) < 0) {
                        // 0x00426d94
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426d80
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426db0
                    charge(ctx, 4);
                    swc1(f1, a2, 52);
                    lbu(v1, a1, 274);
                    if (i64(v1) < 0) {
                        // 0x00426dd4
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426dc0
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426df0
                    charge(ctx, 4);
                    swc1(f1, a2, 56);
                    lbu(v1, a1, 275);
                    if (i64(v1) < 0) {
                        // 0x00426e14
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426e00
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426e30
                    charge(ctx, 2);
                    swc1(f1, a2, 60);
                    a3 = addiu(a3, 1);
                }
                // 0x00426e44
                charge(ctx, 85);
                sw(zero, s1, 32);
                sw(zero, s1, 36);
                lwc1(f0, s1, 296);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, 332);
                mul_s(f1, f1, f0);
                v0 = 0x40000000;
                mtc1(v0, f0);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 308);
                sub_s(f1, f1, f2);
                swc1(f1, s1, 16);
                lwc1(f1, s1, 300);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 312);
                sub_s(f1, f1, f2);
                swc1(f1, s1, 20);
                v0 = 0x3F800000;
                sw(v0, s1, 96);
                sw(zero, s1, 100);
                lwc1(f1, s1, 296);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 308);
                add_s(f1, f1, f2);
                swc1(f1, s1, 80);
                lwc1(f1, s1, 300);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 312);
                sub_s(f1, f1, f2);
                swc1(f1, s1, 84);
                sw(zero, s1, 160);
                sw(v0, s1, 164);
                lwc1(f1, s1, 296);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 308);
                sub_s(f1, f1, f2);
                swc1(f1, s1, 144);
                lwc1(f1, s1, 300);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 312);
                add_s(f1, f1, f2);
                swc1(f1, s1, 148);
                sw(v0, s1, 224);
                sw(v0, s1, 228);
                lwc1(f1, s1, 296);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f2, f1, f0);
                lwc1(f1, s1, 308);
                add_s(f1, f1, f2);
                swc1(f1, s1, 208);
                lwc1(f1, s1, 300);
                cvt_s_w(f2, f1);
                lwc1(f1, s1, 332);
                mul_s(f1, f2, f1);
                div_s(f1, f1, f0);
                lwc1(f0, s1, 312);
                add_s(f0, f0, f1);
                swc1(f0, s1, 212);
                a0 = 4;
                a1 = addiu(s1, 16);
                a2 = a0;
                v0 = 0x960000;
                lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                jalr(ctx, 0x426F88u, v0.u());
                goto L_004275fc;
            }
            // 0x00426910
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x00426918
                charge(ctx, 2);
                goto L_004275fc;
            }
            // 0x00426920
            charge(ctx, 3);
            lb(v0, s1, 336);
            if (v0 == 0) {
                // 0x0042692c
                charge(ctx, 4);
                a3 = 0;
                v0 = 0x960000;
                for (;;) {
                    // 0x00426a64
                    charge(ctx, 3);
                    v1 = slti(a3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0042693c
                    charge(ctx, 12);
                    v1 = sll(a3, 6);
                    a2 = addu(s1, v1);
                    lwc1(f2, v0, 136);
                    lwc1(f1, s1, 304);
                    sub_s(f1, f2, f1);
                    swc1(f1, a2, 24);
                    swc1(f0, a2, 40);
                    v1 = sll(a3, 2);
                    a1 = addu(s1, v1);
                    lbu(v1, a1, 272);
                    if (i64(v1) < 0) {
                        // 0x00426980
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x0042696c
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x0042699c
                    charge(ctx, 4);
                    swc1(f1, a2, 48);
                    lbu(v1, a1, 273);
                    if (i64(v1) < 0) {
                        // 0x004269c0
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x004269ac
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x004269dc
                    charge(ctx, 4);
                    swc1(f1, a2, 52);
                    lbu(v1, a1, 274);
                    if (i64(v1) < 0) {
                        // 0x00426a00
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x004269ec
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426a1c
                    charge(ctx, 4);
                    swc1(f1, a2, 56);
                    lbu(v1, a1, 275);
                    if (i64(v1) < 0) {
                        // 0x00426a40
                        charge(ctx, 7);
                        a0 = srl(v1, 1);
                        v1 = v1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f1);
                        cvt_s_w(f1, f1);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x00426a2c
                        charge(ctx, 5);
                        mtc1(v1, f1);
                        cvt_s_w(f1, f1);
                    }
                    // 0x00426a5c
                    charge(ctx, 2);
                    swc1(f1, a2, 60);
                    a3 = addiu(a3, 1);
                }
                // 0x00426a70
                charge(ctx, 2);
                goto L_00426a8c;
            }
            // 0x00426a78
            charge(ctx, 2);
            if (v0 != v1) {
            L_00426a8c:
                charge(ctx, 20);
                lwc1(f0, s1, 380);
                swc1(f0, s1, 32);
                lwc1(f0, s1, 384);
                swc1(f0, s1, 36);
                lwc1(f0, s1, 372);
                swc1(f0, s1, 96);
                lwc1(f0, s1, 384);
                swc1(f0, s1, 100);
                lwc1(f0, s1, 380);
                swc1(f0, s1, 160);
                lwc1(f0, s1, 376);
                swc1(f0, s1, 164);
                lwc1(f0, s1, 372);
                swc1(f0, s1, 224);
                lwc1(f0, s1, 376);
                swc1(f0, s1, 228);
                lb(v1, s1, 320);
                v0 = 3;
                if (v1 == v0) {
                    // 0x00426c6c
                    charge(ctx, 28);
                    lwc1(f0, s1, 308);
                    swc1(f0, s1, 144);
                    lwc1(f0, s1, 312);
                    swc1(f0, s1, 148);
                    lwc1(f1, s1, 308);
                    lwc1(f0, s1, 296);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 16);
                    lwc1(f0, s1, 312);
                    swc1(f0, s1, 20);
                    lwc1(f0, s1, 308);
                    swc1(f0, s1, 208);
                    lwc1(f1, s1, 312);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 212);
                    lwc1(f1, s1, 308);
                    lwc1(f0, s1, 296);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 80);
                    lwc1(f1, s1, 312);
                    lwc1(f0, s1, 300);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 84);
                } else {
                    // 0x00426adc
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00426bf4
                        charge(ctx, 30);
                        lwc1(f0, s1, 308);
                        swc1(f0, s1, 208);
                        lwc1(f0, s1, 312);
                        swc1(f0, s1, 212);
                        lwc1(f1, s1, 308);
                        lwc1(f0, s1, 296);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 144);
                        lwc1(f0, s1, 312);
                        swc1(f0, s1, 148);
                        lwc1(f0, s1, 308);
                        swc1(f0, s1, 80);
                        lwc1(f1, s1, 312);
                        lwc1(f0, s1, 300);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 84);
                        lwc1(f1, s1, 308);
                        lwc1(f0, s1, 296);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 16);
                        lwc1(f1, s1, 312);
                        lwc1(f0, s1, 300);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s1, 20);
                    } else {
                        // 0x00426ae8
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x00426b7c
                            charge(ctx, 30);
                            lwc1(f0, s1, 308);
                            swc1(f0, s1, 80);
                            lwc1(f0, s1, 312);
                            swc1(f0, s1, 84);
                            lwc1(f1, s1, 308);
                            lwc1(f0, s1, 296);
                            cvt_s_w(f0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, s1, 208);
                            lwc1(f0, s1, 312);
                            swc1(f0, s1, 212);
                            lwc1(f0, s1, 308);
                            swc1(f0, s1, 16);
                            lwc1(f1, s1, 312);
                            lwc1(f0, s1, 300);
                            cvt_s_w(f0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, s1, 20);
                            lwc1(f1, s1, 308);
                            lwc1(f0, s1, 296);
                            cvt_s_w(f0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, s1, 144);
                            lwc1(f1, s1, 312);
                            lwc1(f0, s1, 300);
                            cvt_s_w(f0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, s1, 148);
                        } else {
                            // 0x00426af4
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x00426b04
                                charge(ctx, 30);
                                lwc1(f0, s1, 308);
                                swc1(f0, s1, 16);
                                lwc1(f0, s1, 312);
                                swc1(f0, s1, 20);
                                lwc1(f1, s1, 308);
                                lwc1(f0, s1, 296);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                swc1(f0, s1, 80);
                                lwc1(f0, s1, 312);
                                swc1(f0, s1, 84);
                                lwc1(f0, s1, 308);
                                swc1(f0, s1, 144);
                                lwc1(f1, s1, 312);
                                lwc1(f0, s1, 300);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                swc1(f0, s1, 148);
                                lwc1(f1, s1, 308);
                                lwc1(f0, s1, 296);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                swc1(f0, s1, 208);
                                lwc1(f1, s1, 312);
                                lwc1(f0, s1, 300);
                                cvt_s_w(f0, f0);
                                add_s(f0, f1, f0);
                                swc1(f0, s1, 212);
                            } else {
                                // 0x00426afc
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00426cdc
                charge(ctx, 9);
                a0 = 4;
                a1 = addiu(s1, 16);
                a2 = a0;
                v0 = 0x960000;
                lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
                jalr(ctx, 0x426CF0u, v0.u());
                goto L_004275fc;
            }
            // 0x00426a80
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0042688c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0042761c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00427640 sub_427640 -- 44 bytes; frame 0x10: ra sp+0x0
// [tmxDispDestroy] The destroy callback of "y_tmx_disp_proc": RwFree(work).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00427640
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C RwFree slot
    jalr(ctx, 0x427654u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00427670 Y_LMap_CreateTmxDispTask -- 436 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Y_LMap_CreateTmxDispTask: "y_tmx_disp_proc" with its record.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void Y_LMap_CreateTmxDispTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00427670
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    mov_s(f21, f12);
    mov_s(f20, f13);
    a0 = 1;
    a1 = 400;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x4276C0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004276e0
        charge(ctx, 16);
        a0 = s4;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17456);  // "y_tmx_disp_proc"
        a2 = 6311;
        a3 = 0x420000;
        a3 = addiu(a3, 26000);  // &sub_426590
        t0 = 0x420000;
        t0 = addiu(t0, 30272);  // &sub_427640
        t1 = s0;
        jal(ctx, 0x427704u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, 0);
        a1 = 0;
        a0 = 255;
        for (;;) {
            // 0x0042774c
            charge(ctx, 3);
            v1 = slti(a1, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00427720
            charge(ctx, 11);
            v1 = sll(a1, 2);
            v1 = addu(s0, v1);
            sb(a0, v1, 273);
            sb(a0, v1, 274);
            sb(a0, v1, 272);
            sb(a0, v1, 275);
            v1 = sll(a1, 3);
            v1 = addu(s0, v1);
            sw(zero, v1, 344);
            sw(zero, v1, 340);
            a1 = addiu(a1, 1);
        }
        // 0x00427758
        charge(ctx, 8);
        v1 = 0x42C80000;
        sw(v1, s0, 308);
        sw(v1, s0, 312);
        v1 = dsll32(s2, 24);
        v1 = dsra32(v1, 24);
        v1 = slti(v1, 5);
        if (v1 != 0) {
            // 0x004277a4
            charge(ctx, 9);
            v1 = 0x3D000000;
            sw(v1, s0, 380);
            sw(v1, s0, 384);
            v1 = 0x3F180000;
            sw(v1, s0, 376);
            sw(v1, s0, 372);
            v1 = 19;
            sw(v1, s0, 300);
            sw(v1, s0, 296);
        } else {
            // 0x00427778
            charge(ctx, 11);
            v1 = 0x3C800000;
            sw(v1, s0, 380);
            sw(v1, s0, 384);
            v1 = 0x3F140000;
            sw(v1, s0, 376);
            sw(v1, s0, 372);
            v1 = 37;
            sw(v1, s0, 300);
            sw(v1, s0, 296);
        }
        // 0x004277c8
        charge(ctx, 12);
        v1 = 0x40A00000;
        sw(v1, s0, 304);
        v1 = 0x3F800000;
        sw(v1, s0, 332);
        swc1(f21, s0, 372);
        swc1(f20, s0, 376);
        sw(s3, s0, 316);
        sb(s1, s0, 320);
        sb(zero, s0, 321);
        v1 = 1;
        sb(v1, s0, 336);
        sb(zero, s0, 396);
    } else {
        // 0x004276d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004277f8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00427830 sub_427830 -- 472 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [tmxDispCreateEx3] Another "y_tmx_disp" creator (auto priority).
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00427830
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sd(a2, sp, 0x60);
    sw(a3, sp, 0x6C);
    mov_s(f20, f12);
    s1 = t2;
    lwc1(f3, t0, 0);
    lwc1(f2, t0, 4);
    lwc1(f1, t0, 8);
    lwc1(f0, t0, 12);
    swc1(f3, sp, 0x80);
    swc1(f2, sp, 0x84);
    swc1(f1, sp, 0x88);
    swc1(f0, sp, 0x8C);
    lwc1(f3, t1, 0);
    lwc1(f2, t1, 4);
    lwc1(f1, t1, 8);
    lwc1(f0, t1, 12);
    swc1(f3, sp, 0x70);
    swc1(f2, sp, 0x74);
    swc1(f1, sp, 0x78);
    swc1(f0, sp, 0x7C);
    a0 = 1;
    a1 = 400;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x4278B8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004278d8
        charge(ctx, 15);
        a0 = s3;
        a1 = 4207;
        a2 = 0x6B0000;
        a2 = addiu(a2, 17472);  // "y_tmx_disp_ex_proc"
        a3 = 0x420000;
        a3 = addiu(a3, 26000);  // &sub_426590
        t0 = 0x420000;
        t0 = addiu(t0, 30272);  // &sub_427640
        t1 = s0;
        jal(ctx, 0x4278FCu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sb(zero, s0, 0);
        t0 = 0;
        for (;;) {
            // 0x00427950
            charge(ctx, 3);
            v1 = slti(t0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00427914
            charge(ctx, 15);
            v1 = sll(t0, 2);
            a3 = addu(s0, v1);
            lbu(a2, sp, 0x6C);
            lbu(a1, sp, 0x6D);
            lbu(a0, sp, 0x6E);
            lbu(v1, sp, 0x6F);
            sb(a2, a3, 272);
            sb(a1, a3, 273);
            sb(a0, a3, 274);
            sb(v1, a3, 275);
            v1 = sll(t0, 3);
            v1 = addu(s0, v1);
            sw(zero, v1, 344);
            sw(zero, v1, 340);
            t0 = addiu(t0, 1);
        }
        // 0x0042795c
        charge(ctx, 34);
        lwc1(f1, sp, 0x60);
        lwc1(f0, sp, 0x64);
        swc1(f1, s0, 308);
        swc1(f0, s0, 312);
        lwc1(f3, sp, 0x70);
        lwc1(f2, sp, 0x74);
        lwc1(f1, sp, 0x78);
        lwc1(f0, sp, 0x7C);
        swc1(f3, s0, 288);
        swc1(f2, s0, 292);
        swc1(f1, s0, 296);
        swc1(f0, s0, 300);
        swc1(f20, s0, 304);
        sw(s2, s0, 316);
        sb(s1, s0, 321);
        v1 = 0x3F800000;
        mtc1(v1, f2);
        sw(v1, s0, 332);
        lwc1(f0, sp, 0x88);
        cvt_s_w(f0, f0);
        div_s(f1, f2, f0);
        lwc1(f0, sp, 0x78);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        swc1(f0, s0, 324);
        lwc1(f0, sp, 0x8C);
        cvt_s_w(f0, f0);
        div_s(f1, f2, f0);
        lwc1(f0, sp, 0x7C);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        swc1(f0, s0, 328);
        sb(zero, s0, 336);
        sb(zero, s0, 396);
    } else {
        // 0x004278cc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004279e4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00427A10 sub_427A10 -- 472 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [tmxDispCreateEx] Another "y_tmx_disp" creator.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00427a10
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sd(a2, sp, 0x60);
    sw(a3, sp, 0x6C);
    mov_s(f20, f12);
    s1 = t2;
    lwc1(f3, t0, 0);
    lwc1(f2, t0, 4);
    lwc1(f1, t0, 8);
    lwc1(f0, t0, 12);
    swc1(f3, sp, 0x80);
    swc1(f2, sp, 0x84);
    swc1(f1, sp, 0x88);
    swc1(f0, sp, 0x8C);
    lwc1(f3, t1, 0);
    lwc1(f2, t1, 4);
    lwc1(f1, t1, 8);
    lwc1(f0, t1, 12);
    swc1(f3, sp, 0x70);
    swc1(f2, sp, 0x74);
    swc1(f1, sp, 0x78);
    swc1(f0, sp, 0x7C);
    a0 = 1;
    a1 = 400;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x427A98u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00427ab8
        charge(ctx, 15);
        a0 = s3;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17472);  // "y_tmx_disp_ex_proc"
        a2 = 6310;
        a3 = 0x420000;
        a3 = addiu(a3, 26000);  // &sub_426590
        t0 = 0x420000;
        t0 = addiu(t0, 30272);  // &sub_427640
        t1 = s0;
        jal(ctx, 0x427ADCu, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, 0);
        t0 = 0;
        for (;;) {
            // 0x00427b30
            charge(ctx, 3);
            v1 = slti(t0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00427af4
            charge(ctx, 15);
            v1 = sll(t0, 2);
            a3 = addu(s0, v1);
            lbu(a2, sp, 0x6C);
            lbu(a1, sp, 0x6D);
            lbu(a0, sp, 0x6E);
            lbu(v1, sp, 0x6F);
            sb(a2, a3, 272);
            sb(a1, a3, 273);
            sb(a0, a3, 274);
            sb(v1, a3, 275);
            v1 = sll(t0, 3);
            v1 = addu(s0, v1);
            sw(zero, v1, 344);
            sw(zero, v1, 340);
            t0 = addiu(t0, 1);
        }
        // 0x00427b3c
        charge(ctx, 34);
        lwc1(f1, sp, 0x60);
        lwc1(f0, sp, 0x64);
        swc1(f1, s0, 308);
        swc1(f0, s0, 312);
        lwc1(f3, sp, 0x70);
        lwc1(f2, sp, 0x74);
        lwc1(f1, sp, 0x78);
        lwc1(f0, sp, 0x7C);
        swc1(f3, s0, 288);
        swc1(f2, s0, 292);
        swc1(f1, s0, 296);
        swc1(f0, s0, 300);
        swc1(f20, s0, 304);
        sw(s2, s0, 316);
        sb(s1, s0, 321);
        v1 = 0x3F800000;
        mtc1(v1, f2);
        sw(v1, s0, 332);
        lwc1(f0, sp, 0x88);
        cvt_s_w(f0, f0);
        div_s(f1, f2, f0);
        lwc1(f0, sp, 0x78);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        swc1(f0, s0, 324);
        lwc1(f0, sp, 0x8C);
        cvt_s_w(f0, f0);
        div_s(f1, f2, f0);
        lwc1(f0, sp, 0x7C);
        cvt_s_w(f0, f0);
        mul_s(f0, f1, f0);
        swc1(f0, s0, 328);
        sb(zero, s0, 336);
        sb(zero, s0, 396);
    } else {
        // 0x00427aac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00427bc4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00427BF0 sub_427BF0 -- 440 bytes; frame 0x80: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [tmxDispCreateEx2] Another "y_tmx_disp" creator.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427BF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00427bf0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    sd(a2, sp, 0x60);
    sw(a3, sp, 0x6C);
    mov_s(f24, f12);
    mov_s(f23, f13);
    mov_s(f22, f14);
    mov_s(f21, f15);
    mov_s(f20, f16);
    lwc1(f3, t0, 0);
    lwc1(f2, t0, 4);
    lwc1(f1, t0, 8);
    lwc1(f0, t0, 12);
    swc1(f3, sp, 0x70);
    swc1(f2, sp, 0x74);
    swc1(f1, sp, 0x78);
    swc1(f0, sp, 0x7C);
    a0 = 1;
    a1 = 400;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184 RwCalloc slot
    jalr(ctx, 0x427C70u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00427c90
        charge(ctx, 15);
        a0 = s2;
        a1 = 0x6B0000;
        a1 = addiu(a1, 17472);  // "y_tmx_disp_ex_proc"
        a2 = 6311;
        a3 = 0x420000;
        a3 = addiu(a3, 26000);  // &sub_426590
        t0 = 0x420000;
        t0 = addiu(t0, 30272);  // &sub_427640
        t1 = s0;
        jal(ctx, 0x427CB4u, gen::fn_kwlnTaskCreate_00194b20);
        sb(zero, s0, 0);
        t0 = 0;
        for (;;) {
            // 0x00427d08
            charge(ctx, 3);
            v1 = slti(t0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00427ccc
            charge(ctx, 15);
            v1 = sll(t0, 2);
            a3 = addu(s0, v1);
            lbu(a2, sp, 0x6C);
            lbu(a1, sp, 0x6D);
            lbu(a0, sp, 0x6E);
            lbu(v1, sp, 0x6F);
            sb(a2, a3, 272);
            sb(a1, a3, 273);
            sb(a0, a3, 274);
            sb(v1, a3, 275);
            v1 = sll(t0, 3);
            v1 = addu(s0, v1);
            sw(zero, v1, 344);
            sw(zero, v1, 340);
            t0 = addiu(t0, 1);
        }
        // 0x00427d14
        charge(ctx, 25);
        lwc1(f1, sp, 0x60);
        lwc1(f0, sp, 0x64);
        swc1(f1, s0, 308);
        swc1(f0, s0, 312);
        lwc1(f3, sp, 0x70);
        lwc1(f2, sp, 0x74);
        lwc1(f1, sp, 0x78);
        lwc1(f0, sp, 0x7C);
        swc1(f3, s0, 288);
        swc1(f2, s0, 292);
        swc1(f1, s0, 296);
        swc1(f0, s0, 300);
        swc1(f24, s0, 304);
        sw(s1, s0, 316);
        v1 = 3;
        sb(v1, s0, 321);
        v1 = 0x3F800000;
        sw(v1, s0, 332);
        v1 = 1;
        sb(v1, s0, 336);
        swc1(f21, s0, 372);
        swc1(f20, s0, 376);
        swc1(f23, s0, 388);
        swc1(f22, s0, 392);
        sb(zero, s0, 396);
    } else {
        // 0x00427c84
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00427d78 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00427DB0 sub_427DB0 -- 40 bytes; frame 0x10
// [tmxDispSetPos] The 8-byte $a1 (two floats) to record +308 / +312.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427DB0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00427db0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(a1, sp, 0x8);
    lw(v1, a0, kTaskWork);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, v1, 308);
    swc1(f0, v1, 312);
    sp = addiu(sp, 0x10);
}

// 0x00427DE0 sub_427DE0 -- 64 bytes; leaf frame (no stack)
// [tmxDispSetColor] The four corner colours (r $a1, g $a2, b $a3, a $a4) at record +272 + 4 i.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00427de0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    t1 = 0;
    for (;;) {
        // 0x00427e0c
        charge(ctx, 3);
        v1 = slti(t1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00427df0
        charge(ctx, 7);
        v1 = sll(t1, 2);
        v1 = addu(a0, v1);
        sb(a1, v1, 272);
        sb(a3, v1, 274);
        sb(a2, v1, 273);
        sb(t0, v1, 275);
        t1 = addiu(t1, 1);
    }
    // 0x00427e18
    charge(ctx, 2);
}

// 0x00427E20 sub_427E20 -- 44 bytes; leaf frame (no stack)
// [tmxDispSetSize] (int)$f12 / (int)$f13 to record +296 / +300.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427E20(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00427e20
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    cvt_w_s(f0, f12);
    mfc1(v1, f0);
    sw(v1, a0, 296);
    cvt_w_s(f0, f13);
    mfc1(v1, f0);
    sw(v1, a0, 300);
}

// 0x00427E50 sub_427E50 -- 16 bytes; leaf frame (no stack)
// [tmxDispSetHidden] Record byte +336 = $a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427E50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00427e50
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 336);
}

// 0x00427E60 sub_427E60 -- 16 bytes; leaf frame (no stack)
// [tmxDispSetBlend] Record byte +396 = $a1.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427E60(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00427e60
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sb(a1, v1, 396);
}

// 0x00427E70 sub_427E70 -- 884 bytes; frame 0x1C0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0, f23 sp+0xA0, f22 sp+0xA4, f22 sp+0xAC, f23 sp+0xB0
// [tmxDrawQuad] Draws one textured quad: colour $a0 (RGBA bytes), x $f12.. size $a1 / $a2, texture *$a3; the
// render states through RwRenderStateSet (0x960090) and RpSkyRenderStateSet, four Im2D vertices on the frame
// (1/w from the camera +128), RwIm2DRenderPrimitive (0x9600A0) as a triangle strip.
// (p3fes_handgen body: register for register and block for block the recompiled one.)
void sub_427E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00427e70
    enter(ctx, 120);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    sd(ra, sp, 0x90);
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
    mov_s(f21, f12);
    s0 = a0;
    mov_s(f23, f13);
    mov_s(f22, f14);
    s5 = a1;
    s6 = a2;
    s7 = a3;
    jal(ctx, 0x427EC4u, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f20, f1, f0);
    v0 = lui(0xFF00);
    v0 = s0 & v0;
    v0 = srl(v0, 24);
    s4 = v0 & 0xFF;
    v0 = 0xFF0000;
    v0 = s0 & v0;
    v0 = srl(v0, 16);
    s3 = v0 & 0xFF;
    v0 = s0 & 0xFF00;
    v0 = srl(v0, 8);
    s2 = v0 & 0xFF;
    s1 = s0 & 0xFF;
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F20u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F34u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F48u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F5Cu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F70u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F84u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427F98u, v0.u());
    a0 = 2;
    a1 = 4;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x427FACu, v0.u());
    a0 = 2;
    a1 = 72;
    jal(ctx, 0x427FBCu, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = 0x70000;
    a1 = v0 | 0x1801;
    jal(ctx, 0x427FD0u, gen::fn_RpSkyRenderStateSet_004d7f60);
    swc1(f23, sp, 0xA0);
    swc1(f22, sp, 0xA4);
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f23, f0);
    swc1(f1, sp, 0xB8);
    mtc1(s6, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f22, f0);
    swc1(f0, sp, 0xBC);
    swc1(f1, sp, 0xA8);
    swc1(f22, sp, 0xAC);
    swc1(f23, sp, 0xB0);
    swc1(f0, sp, 0xB4);
    t0 = 0;
    v0 = 0x960000;
    lwc1(f0, v0, 136);  // g_rwIm2DNearScreenZ
    sub_s(f5, f0, f21);
    a2 = s4 & 0x1;
    mtc1(s4, f4);
    a1 = s3 & 0x1;
    mtc1(s3, f3);
    a0 = s2 & 0x1;
    mtc1(s2, f2);
    v1 = s1 & 0x1;
    mtc1(s1, f1);
    for (;;) {
        // 0x00428144
        charge(ctx, 3);
        v0 = slti(t0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00428050
        charge(ctx, 7);
        v0 = sll(t0, 6);
        v0 = addu(v0, sp);
        a3 = addiu(v0, 192);
        swc1(f5, a3, 8);
        swc1(f20, a3, 24);
        if (i64(s4) < 0) {
            // 0x00428078
            charge(ctx, 6);
            v0 = srl(s4, 1);
            v0 = v0 | a2;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x0042806c
            charge(ctx, 3);
            cvt_s_w(f0, f4);
        }
        // 0x00428090
        charge(ctx, 3);
        swc1(f0, a3, 32);
        if (i64(s3) < 0) {
            // 0x004280a8
            charge(ctx, 6);
            v0 = srl(s3, 1);
            v0 = v0 | a1;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x0042809c
            charge(ctx, 3);
            cvt_s_w(f0, f3);
        }
        // 0x004280c0
        charge(ctx, 3);
        swc1(f0, a3, 36);
        if (i64(s2) < 0) {
            // 0x004280d8
            charge(ctx, 6);
            v0 = srl(s2, 1);
            v0 = v0 | a0;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x004280cc
            charge(ctx, 3);
            cvt_s_w(f0, f2);
        }
        // 0x004280f0
        charge(ctx, 3);
        swc1(f0, a3, 40);
        if (i64(s1) < 0) {
            // 0x00428108
            charge(ctx, 6);
            v0 = srl(s1, 1);
            v0 = v0 | v1;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x004280fc
            charge(ctx, 3);
            cvt_s_w(f0, f1);
        }
        // 0x00428120
        charge(ctx, 9);
        swc1(f0, a3, 44);
        v0 = sll(t0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 160);
        lwc1(f0, v0, 0);
        swc1(f0, a3, 0);
        lwc1(f0, v0, 4);
        swc1(f0, a3, 4);
        t0 = addiu(t0, 1);
    }
    // 0x00428150
    charge(ctx, 37);
    sw(zero, sp, 0xD0);
    sw(zero, sp, 0xD4);
    v0 = 0x3F800000;
    sw(v0, sp, 0x110);
    sw(zero, sp, 0x114);
    sw(zero, sp, 0x150);
    sw(v0, sp, 0x154);
    sw(v0, sp, 0x190);
    sw(v0, sp, 0x194);
    a0 = 1;
    lw(a1, s7, 0);
    lw(v0, s0, 0);
    jalr(ctx, 0x428180u, v0.u());
    a0 = 4;
    a1 = addiu(sp, 0xC0);
    a2 = a0;
    v0 = 0x960000;
    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x42819Cu, v0.u());
    ld(ra, sp, 0x90);
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
    sp = addiu(sp, 0x1C0);
}

}  // namespace p3fes::game
