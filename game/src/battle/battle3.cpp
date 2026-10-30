// The battle core and enemy AI, third pass (slice battle3; docs/ANALYSIS/21_battle.md, game/include/p3fes/game/battle3.h
// for the layouts and the battle state a co-op server would own): the unit / camera / effect / sound packets of the
// battle task with their hold / update / release callbacks, the all-out attack (check and state), the advantage and
// escape rolls, the ailment skip / recovery rolls, the support and voice line pickers, the battle grid, the boss rules
// of the band, the AI unit finders, conditions, default target pick, best-skill pick, command decoding and AICALC row
// evaluation. Every function the battle replay (first battle) or the Tartarus climb reaches and whose callees are
// already hand-written. The bodies are p3fes_handgen's (frame, spills, $ra links, every register, cycle charges, check
// points); this file names their offsets and gives each its role -- proposed names in brackets (ADR-0009), symbols in
// code are functions.json's.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle3.h"

namespace p3fes::recomp_gen {
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_btlCountActiveUnits_002d4e10(p3fes::EEContext&);
void fn_btlGetMeanLevel_002d4cf0(p3fes::EEContext&);
void fn_datCalcAddHp_00300410(p3fes::EEContext&);
void fn_datCalcAddSp_00300480(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcDamage_00303130(p3fes::EEContext&);
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(p3fes::EEContext&);
void fn_datCalcGetBadStatus_00300550(p3fes::EEContext&);
void fn_datCalcGetEffectState_00301750(p3fes::EEContext&);
void fn_datCalcGetElementBit_003080c0(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
void fn_datCalcGetSp_002ffd80(p3fes::EEContext&);
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);
void fn_datCalcIsLowHp_0030b5e0(p3fes::EEContext&);
void fn_datCalcIsPhysicalSkill_003088b0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetUnit_0016cd60(p3fes::EEContext&);
void fn_datScriptCalc_0030fc40(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_170670_00170670(p3fes::EEContext&);
void fn_sub_1706C0_001706c0(p3fes::EEContext&);
void fn_sub_170710_00170710(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175130_00175130(p3fes::EEContext&);
void fn_sub_1756F0_001756f0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_1A0DC0_001a0dc0(p3fes::EEContext&);
void fn_sub_1FDDA0_001fdda0(p3fes::EEContext&);
void fn_sub_1FE650_001fe650(p3fes::EEContext&);
void fn_sub_1FE9B0_001fe9b0(p3fes::EEContext&);
void fn_sub_1FEB50_001feb50(p3fes::EEContext&);
void fn_sub_1FECE0_001fece0(p3fes::EEContext&);
void fn_sub_1FED60_001fed60(p3fes::EEContext&);
void fn_sub_1FEDA0_001feda0(p3fes::EEContext&);
void fn_sub_1FEDE0_001fede0(p3fes::EEContext&);
void fn_sub_1FEE20_001fee20(p3fes::EEContext&);
void fn_sub_1FEE60_001fee60(p3fes::EEContext&);
void fn_sub_1FEF90_001fef90(p3fes::EEContext&);
void fn_sub_1FF100_001ff100(p3fes::EEContext&);
void fn_sub_1FF120_001ff120(p3fes::EEContext&);
void fn_sub_1FF140_001ff140(p3fes::EEContext&);
void fn_sub_1FF370_001ff370(p3fes::EEContext&);
void fn_sub_27E390_0027e390(p3fes::EEContext&);
void fn_sub_27E470_0027e470(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27F410_0027f410(p3fes::EEContext&);
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);
void fn_sub_281270_00281270(p3fes::EEContext&);
void fn_sub_2819D0_002819d0(p3fes::EEContext&);
void fn_sub_2821B0_002821b0(p3fes::EEContext&);
void fn_sub_282650_00282650(p3fes::EEContext&);
void fn_sub_282BC0_00282bc0(p3fes::EEContext&);
void fn_sub_282C30_00282c30(p3fes::EEContext&);
void fn_sub_282C60_00282c60(p3fes::EEContext&);
void fn_sub_2835E0_002835e0(p3fes::EEContext&);
void fn_sub_2838D0_002838d0(p3fes::EEContext&);
void fn_sub_283A70_00283a70(p3fes::EEContext&);
void fn_sub_283C00_00283c00(p3fes::EEContext&);
void fn_sub_284040_00284040(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_2843E0_002843e0(p3fes::EEContext&);
void fn_sub_284C00_00284c00(p3fes::EEContext&);
void fn_sub_285670_00285670(p3fes::EEContext&);
void fn_sub_285690_00285690(p3fes::EEContext&);
void fn_sub_285730_00285730(p3fes::EEContext&);
void fn_sub_2857D0_002857d0(p3fes::EEContext&);
void fn_sub_2857F0_002857f0(p3fes::EEContext&);
void fn_sub_285860_00285860(p3fes::EEContext&);
void fn_sub_285880_00285880(p3fes::EEContext&);
void fn_sub_285D10_00285d10(p3fes::EEContext&);
void fn_sub_285D30_00285d30(p3fes::EEContext&);
void fn_sub_285F80_00285f80(p3fes::EEContext&);
void fn_sub_285FA0_00285fa0(p3fes::EEContext&);
void fn_sub_286090_00286090(p3fes::EEContext&);
void fn_sub_2860B0_002860b0(p3fes::EEContext&);
void fn_sub_286110_00286110(p3fes::EEContext&);
void fn_sub_286130_00286130(p3fes::EEContext&);
void fn_sub_286220_00286220(p3fes::EEContext&);
void fn_sub_286240_00286240(p3fes::EEContext&);
void fn_sub_2862A0_002862a0(p3fes::EEContext&);
void fn_sub_2862C0_002862c0(p3fes::EEContext&);
void fn_sub_286300_00286300(p3fes::EEContext&);
void fn_sub_286320_00286320(p3fes::EEContext&);
void fn_sub_287490_00287490(p3fes::EEContext&);
void fn_sub_287B20_00287b20(p3fes::EEContext&);
void fn_sub_287CF0_00287cf0(p3fes::EEContext&);
void fn_sub_2880E0_002880e0(p3fes::EEContext&);
void fn_sub_288170_00288170(p3fes::EEContext&);
void fn_sub_288190_00288190(p3fes::EEContext&);
void fn_sub_288340_00288340(p3fes::EEContext&);
void fn_sub_288360_00288360(p3fes::EEContext&);
void fn_sub_288400_00288400(p3fes::EEContext&);
void fn_sub_288430_00288430(p3fes::EEContext&);
void fn_sub_2886B0_002886b0(p3fes::EEContext&);
void fn_sub_2886E0_002886e0(p3fes::EEContext&);
void fn_sub_288760_00288760(p3fes::EEContext&);
void fn_sub_288780_00288780(p3fes::EEContext&);
void fn_sub_288930_00288930(p3fes::EEContext&);
void fn_sub_288950_00288950(p3fes::EEContext&);
void fn_sub_288DA0_00288da0(p3fes::EEContext&);
void fn_sub_288F80_00288f80(p3fes::EEContext&);
void fn_sub_288FE0_00288fe0(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_2899E0_002899e0(p3fes::EEContext&);
void fn_sub_289F40_00289f40(p3fes::EEContext&);
void fn_sub_28A0F0_0028a0f0(p3fes::EEContext&);
void fn_sub_28A200_0028a200(p3fes::EEContext&);
void fn_sub_28A3E0_0028a3e0(p3fes::EEContext&);
void fn_sub_28A540_0028a540(p3fes::EEContext&);
void fn_sub_28A780_0028a780(p3fes::EEContext&);
void fn_sub_28BA50_0028ba50(p3fes::EEContext&);
void fn_sub_297480_00297480(p3fes::EEContext&);
void fn_sub_297A50_00297a50(p3fes::EEContext&);
void fn_sub_298060_00298060(p3fes::EEContext&);
void fn_sub_299990_00299990(p3fes::EEContext&);
void fn_sub_29A2C0_0029a2c0(p3fes::EEContext&);
void fn_sub_29A380_0029a380(p3fes::EEContext&);
void fn_sub_29EA20_0029ea20(p3fes::EEContext&);
void fn_sub_29EA30_0029ea30(p3fes::EEContext&);
void fn_sub_29EA40_0029ea40(p3fes::EEContext&);
void fn_sub_29EA60_0029ea60(p3fes::EEContext&);
void fn_sub_29EC00_0029ec00(p3fes::EEContext&);
void fn_sub_29EC50_0029ec50(p3fes::EEContext&);
void fn_sub_29EC80_0029ec80(p3fes::EEContext&);
void fn_sub_29F4B0_0029f4b0(p3fes::EEContext&);
void fn_sub_29FA50_0029fa50(p3fes::EEContext&);
void fn_sub_2A1DB0_002a1db0(p3fes::EEContext&);
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2A54F0_002a54f0(p3fes::EEContext&);
void fn_sub_2A5EE0_002a5ee0(p3fes::EEContext&);
void fn_sub_2A7830_002a7830(p3fes::EEContext&);
void fn_sub_2A79F0_002a79f0(p3fes::EEContext&);
void fn_sub_2A8150_002a8150(p3fes::EEContext&);
void fn_sub_2A95D0_002a95d0(p3fes::EEContext&);
void fn_sub_2AA2B0_002aa2b0(p3fes::EEContext&);
void fn_sub_2AB330_002ab330(p3fes::EEContext&);
void fn_sub_2AC540_002ac540(p3fes::EEContext&);
void fn_sub_2AE740_002ae740(p3fes::EEContext&);
void fn_sub_2AEF80_002aef80(p3fes::EEContext&);
void fn_sub_2AF850_002af850(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);
void fn_sub_2B8F40_002b8f40(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B9220_002b9220(p3fes::EEContext&);
void fn_sub_2B9600_002b9600(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB2F0_002bb2f0(p3fes::EEContext&);
void fn_sub_2BB580_002bb580(p3fes::EEContext&);
void fn_sub_2BB8F0_002bb8f0(p3fes::EEContext&);
void fn_sub_2BBBC0_002bbbc0(p3fes::EEContext&);
void fn_sub_2BBD00_002bbd00(p3fes::EEContext&);
void fn_sub_2BC7E0_002bc7e0(p3fes::EEContext&);
void fn_sub_2BD4F0_002bd4f0(p3fes::EEContext&);
void fn_sub_2BD780_002bd780(p3fes::EEContext&);
void fn_sub_2BD8E0_002bd8e0(p3fes::EEContext&);
void fn_sub_2BDDD0_002bddd0(p3fes::EEContext&);
void fn_sub_2BF370_002bf370(p3fes::EEContext&);
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext&);
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);
void fn_sub_2C0880_002c0880(p3fes::EEContext&);
void fn_sub_2C08A0_002c08a0(p3fes::EEContext&);
void fn_sub_2C0970_002c0970(p3fes::EEContext&);
void fn_sub_2C09F0_002c09f0(p3fes::EEContext&);
void fn_sub_2C0AC0_002c0ac0(p3fes::EEContext&);
void fn_sub_2C0E30_002c0e30(p3fes::EEContext&);
void fn_sub_2C0F40_002c0f40(p3fes::EEContext&);
void fn_sub_2C12F0_002c12f0(p3fes::EEContext&);
void fn_sub_2C13D0_002c13d0(p3fes::EEContext&);
void fn_sub_2C1590_002c1590(p3fes::EEContext&);
void fn_sub_2C1650_002c1650(p3fes::EEContext&);
void fn_sub_2C16A0_002c16a0(p3fes::EEContext&);
void fn_sub_2C1D90_002c1d90(p3fes::EEContext&);
void fn_sub_2C1E10_002c1e10(p3fes::EEContext&);
void fn_sub_2C1ED0_002c1ed0(p3fes::EEContext&);
void fn_sub_2C24D0_002c24d0(p3fes::EEContext&);
void fn_sub_2C3300_002c3300(p3fes::EEContext&);
void fn_sub_2C3400_002c3400(p3fes::EEContext&);
void fn_sub_2C3770_002c3770(p3fes::EEContext&);
void fn_sub_2C48A0_002c48a0(p3fes::EEContext&);
void fn_sub_2C6A00_002c6a00(p3fes::EEContext&);
void fn_sub_2C6BA0_002c6ba0(p3fes::EEContext&);
void fn_sub_2C6E30_002c6e30(p3fes::EEContext&);
void fn_sub_2C7250_002c7250(p3fes::EEContext&);
void fn_sub_2C7280_002c7280(p3fes::EEContext&);
void fn_sub_2D0D00_002d0d00(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
void fn_sub_2D2280_002d2280(p3fes::EEContext&);
void fn_sub_2D2340_002d2340(p3fes::EEContext&);
void fn_sub_2D2990_002d2990(p3fes::EEContext&);
void fn_sub_2D3E00_002d3e00(p3fes::EEContext&);
void fn_sub_2D4040_002d4040(p3fes::EEContext&);
void fn_sub_2D4ED0_002d4ed0(p3fes::EEContext&);
void fn_sub_2D50C0_002d50c0(p3fes::EEContext&);
void fn_sub_2D5570_002d5570(p3fes::EEContext&);
void fn_sub_2D56A0_002d56a0(p3fes::EEContext&);
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);
void fn_sub_2D6290_002d6290(p3fes::EEContext&);
void fn_sub_2D63B0_002d63b0(p3fes::EEContext&);
void fn_sub_2D6460_002d6460(p3fes::EEContext&);
void fn_sub_2D7FB0_002d7fb0(p3fes::EEContext&);
void fn_sub_2D8040_002d8040(p3fes::EEContext&);
void fn_sub_2D8090_002d8090(p3fes::EEContext&);
void fn_sub_2D8110_002d8110(p3fes::EEContext&);
void fn_sub_2D8330_002d8330(p3fes::EEContext&);
void fn_sub_2D8B40_002d8b40(p3fes::EEContext&);
void fn_sub_2D8F70_002d8f70(p3fes::EEContext&);
void fn_sub_2D9CA0_002d9ca0(p3fes::EEContext&);
void fn_sub_2DB480_002db480(p3fes::EEContext&);
void fn_sub_2DB740_002db740(p3fes::EEContext&);
void fn_sub_2DB890_002db890(p3fes::EEContext&);
void fn_sub_2DBFE0_002dbfe0(p3fes::EEContext&);
void fn_sub_2DC070_002dc070(p3fes::EEContext&);
void fn_sub_2DC180_002dc180(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DD4A0_002dd4a0(p3fes::EEContext&);
void fn_sub_2DD5E0_002dd5e0(p3fes::EEContext&);
void fn_sub_2DDC10_002ddc10(p3fes::EEContext&);
void fn_sub_2DDC80_002ddc80(p3fes::EEContext&);
void fn_sub_2DE150_002de150(p3fes::EEContext&);
void fn_sub_2DE3C0_002de3c0(p3fes::EEContext&);
void fn_sub_2DE4E0_002de4e0(p3fes::EEContext&);
void fn_sub_2E2A10_002e2a10(p3fes::EEContext&);
void fn_sub_2E2BE0_002e2be0(p3fes::EEContext&);
void fn_sub_2E2EC0_002e2ec0(p3fes::EEContext&);
void fn_sub_2E38A0_002e38a0(p3fes::EEContext&);
void fn_sub_2E3990_002e3990(p3fes::EEContext&);
void fn_sub_2E3A90_002e3a90(p3fes::EEContext&);
void fn_sub_2E3B50_002e3b50(p3fes::EEContext&);
void fn_sub_2E3CD0_002e3cd0(p3fes::EEContext&);
void fn_sub_2E3D10_002e3d10(p3fes::EEContext&);
void fn_sub_2E4220_002e4220(p3fes::EEContext&);
void fn_sub_2E4250_002e4250(p3fes::EEContext&);
void fn_sub_2E42C0_002e42c0(p3fes::EEContext&);
void fn_sub_2E4520_002e4520(p3fes::EEContext&);
void fn_sub_2E4720_002e4720(p3fes::EEContext&);
void fn_sub_2E47A0_002e47a0(p3fes::EEContext&);
void fn_sub_2E4910_002e4910(p3fes::EEContext&);
void fn_sub_2F6C50_002f6c50(p3fes::EEContext&);
void fn_sub_2F9BC0_002f9bc0(p3fes::EEContext&);
void fn_sub_2FA510_002fa510(p3fes::EEContext&);
void fn_sub_2FB860_002fb860(p3fes::EEContext&);
void fn_sub_2FC410_002fc410(p3fes::EEContext&);
void fn_sub_2FC520_002fc520(p3fes::EEContext&);
void fn_sub_2FCAA0_002fcaa0(p3fes::EEContext&);
void fn_sub_2FCF50_002fcf50(p3fes::EEContext&);
void fn_sub_2FD220_002fd220(p3fes::EEContext&);
void fn_sub_2FD4A0_002fd4a0(p3fes::EEContext&);
void fn_sub_2FD7C0_002fd7c0(p3fes::EEContext&);
void fn_sub_2FD820_002fd820(p3fes::EEContext&);
void fn_sub_2FDBB0_002fdbb0(p3fes::EEContext&);
void fn_sub_2FDFE0_002fdfe0(p3fes::EEContext&);
void fn_sub_301870_00301870(p3fes::EEContext&);
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);
void fn_sub_302C50_00302c50(p3fes::EEContext&);
void fn_sub_3068D0_003068d0(p3fes::EEContext&);
void fn_sub_3083F0_003083f0(p3fes::EEContext&);
void fn_sub_308930_00308930(p3fes::EEContext&);
void fn_sub_308A80_00308a80(p3fes::EEContext&);
void fn_sub_3093A0_003093a0(p3fes::EEContext&);
void fn_sub_30AF00_0030af00(p3fes::EEContext&);
void fn_sub_318910_00318910(p3fes::EEContext&);
void fn_sub_319010_00319010(p3fes::EEContext&);
void fn_sub_319030_00319030(p3fes::EEContext&);
void fn_sub_319050_00319050(p3fes::EEContext&);
void fn_sub_319070_00319070(p3fes::EEContext&);
void fn_sub_319090_00319090(p3fes::EEContext&);
void fn_sub_3190A0_003190a0(p3fes::EEContext&);
void fn_sub_319190_00319190(p3fes::EEContext&);
void fn_sub_3191B0_003191b0(p3fes::EEContext&);
void fn_sub_3191F0_003191f0(p3fes::EEContext&);
void fn_sub_319200_00319200(p3fes::EEContext&);
void fn_sub_319770_00319770(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h

// 0x002821B0 sub_2821B0 -- 224 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateMove] Update of the unit move packet: on the first frame (counter +20 == 0) takes the target point
// (the unit's own position through sub_27F7C0 when flag 0x20 is set), writes it to the unit's walk target
// (+208..+216), clears +1272 / +232, copies the speed word (+16) to +196 and sets the walking bit (+200 bit 1); done
// once the unit cleared that bit.
// Arguments: a0 packet data {unit, f32[3], u32 flags, u32 counter}.
void sub_2821B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002821b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 0);
    lw(v0, a0, 20);
    if (v0 == 0) {
        // 0x002821d4
        charge(ctx, 4);
        lw(v0, s1, 16);
        v0 = v0 & 0x20;
        if (v0 != 0) {
            // 0x002821e4
            charge(ctx, 12);
            a0 = s0;
            a1 = 0;
            a2 = 0;
            a3 = addiu(sp, 0x30);
            jal(ctx, 0x2821F4u, gen::fn_sub_27F7C0_0027f7c0);
            lwc1(f2, sp, 0x30);
            lwc1(f1, sp, 0x34);
            lwc1(f0, sp, 0x38);
            swc1(f2, s1, 4);
            swc1(f1, s1, 8);
            swc1(f0, s1, 12);
        }
        // 0x00282214
        charge(ctx, 13);
        lw(v0, s1, 16);
        lwc1(f2, s1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, s1, 12);
        swc1(f2, s0, unit::kWalkTarget);
        swc1(f1, s0, unit::kWalkTarget + 4);
        swc1(f0, s0, unit::kWalkTarget + 8);
        sw(zero, s0, unit::kWalkStep);
        sw(zero, s0, unit::kWalkTimer);
        sw(v0, s0, unit::kWalkSpeed);
        lhu(v0, s0, unit::kWalkFlags);
        v0 = v0 | 0x2;
        sh(v0, s0, unit::kWalkFlags);
    }
    // 0x00282248
    charge(ctx, 5);
    lhu(v0, s0, unit::kWalkFlags);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
    if (v0 != 0) {
        // 0x00282268
        charge(ctx, 4);
        lw(v0, s1, 20);
        v0 = addiu(v0, 1);
        sw(v0, s1, 20);
        v0 = 0;
    } else {
        // 0x0028225c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00282278 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00282BC0 sub_282BC0 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitRandomizeIdleFrame] Puts a unit at a random frame of its current motion: frames = sub_2838D0(unit,
// sub_282C30(unit)), then sub_283C00(unit, datCalcRand(frames)).
// Arguments: a0 btlUnit.
void sub_282BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00282bc0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x282BD0u, gen::fn_sub_282C30_00282c30);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    a1 = v0 & 0xFFFF;
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s0;
    jal(ctx, 0x282BF0u, gen::fn_sub_2838D0_002838d0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x282C00u, gen::fn_datCalcRand_002ffbc0);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    jal(ctx, 0x282C14u, gen::fn_sub_283C00_00283c00);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002835E0 sub_2835E0 -- 356 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlUnitGetMotionFrames] Length in frames of a unit's motion at a playback speed: the motion row is the side's row
// of the table 0x693290 (26 per side), or for enemies the boss remap sub_2FB860 when it gives one; frames =
// row.frames / (speed * row.speed% / 100) as s16, 0 when the row is beyond the unit's motion table.
// Arguments: a0 btlUnit, a1 motion, f12 speed.
void sub_2835E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002835e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mov_s(f20, f12);
    // the motion row v1: personas (side 2) and the party (side 0) take the side's row of the table 0x693290 (26
    // bytes per side); an enemy (side 1) the boss remap sub_2FB860 unless it answers -1; any other side row 0
    lbu(v1, a0, unit::kSide);
    v0 = 2;
    bool from_table = true;  // host only: the paths that reach 0x283650
    if (v1 != v0) {
        // 0x00283610
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00283618
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0028362c
                charge(ctx, 7);
                jal(ctx, 0x28362Cu, gen::fn_sub_2FB860_002fb860);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x00283648
                    charge(ctx, 2);
                    from_table = false;
                }
            } else {
                // 0x00283624
                charge(ctx, 2);
                // 0x00283690
                charge(ctx, 3);
                v1 = 0;
                from_table = false;
            }
        }
    }
    if (from_table) {
        // 0x00283650: table 0x693290 [26 * side + motion]
        charge(ctx, 16);
        lbu(v1, s1, unit::kSide);
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
        // 0x0028369c
        charge(ctx, 2);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
    }
    // 0x002836a4
    charge(ctx, 6);
    v1 = dsll32(v1, 16);
    v1 = dsra32(v1, 16);
    lhu(v0, s1, unit::kMotionCount);
    at = slt(v1, v0);
    if (at == 0) {
        // 0x00283724
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002836bc
        charge(ctx, 26);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 1);
        lw(v0, s1, unit::kMotionTbl);
        v1 = addu(v1, v0);
        lh(v0, v1, 2);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x42C80000;
        mtc1(v0, f0);
        div_s(f0, f1, f0);
        mul_s(f1, f20, f0);
        lh(v0, v1, 0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
    }
    // 0x00283728 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002838D0 sub_2838D0 -- 412 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlUnitGetMotionClipFrames] As sub_2835E0 but from the model's own clip length (sub_318910): 0 when the unit has
// no model; the clip length divided by speed * row.speed% / 100, or the clip length when the row is beyond the table.
// Arguments: a0 btlUnit, a1 motion, f12 speed.
void sub_2838D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002838d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mov_s(f20, f12);
    lw(v0, a0, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00283910
        charge(ctx, 4);
        // the motion row s2, chosen as in sub_2835E0
        lbu(v1, s1, unit::kSide);
        v0 = 2;
        bool from_table = true;  // host only: the paths that reach 0x283960
        if (v1 != v0) {
            // 0x00283920
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00283928
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0028393c
                    charge(ctx, 7);
                    jal(ctx, 0x28393Cu, gen::fn_sub_2FB860_002fb860);
                    s2 = dsll32(v0, 16);
                    s2 = dsra32(s2, 16);
                    v0 = si(-1);
                    if (s2 != v0) {
                        // 0x00283958
                        charge(ctx, 2);
                        from_table = false;
                    }
                } else {
                    // 0x00283934
                    charge(ctx, 2);
                    // 0x002839a0
                    charge(ctx, 3);
                    s2 = 0;
                    from_table = false;
                }
            }
        }
        if (from_table) {
            // 0x00283960: table 0x693290 [26 * side + motion]
            charge(ctx, 16);
            lbu(v1, s1, unit::kSide);
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
            // 0x002839ac
            charge(ctx, 2);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
        }
        // 0x002839b4
        charge(ctx, 11);
        lw(a0, s1, unit::kModel);
        a1 = 0;
        a2 = s2;
        jal(ctx, 0x2839C0u, gen::fn_sub_318910_00318910);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        lhu(v0, s1, unit::kMotionCount);
        at = slt(a0, v0);
        if (at == 0) {
            // 0x00283a38
            charge(ctx, 5);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        } else {
            // 0x002839e0
            charge(ctx, 22);
            lw(v1, s1, unit::kMotionTbl);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            lh(v0, v0, 2);
            mtc1(v0, f1);
            cvt_s_w(f2, f1);
            v0 = 0x42C80000;
            mtc1(v0, f1);
            div_s(f1, f2, f1);
            mul_s(f1, f20, f1);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
        }
    } else {
        // 0x00283904
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00283a4c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00283A70 sub_283A70 -- 300 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetMotionBlend] The blend word (+8) of a unit's motion row (same row choice as sub_2835E0); 6 without a
// model or a row.
// Arguments: a0 btlUnit, a1 motion.
void sub_283A70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00283a70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, a0, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00283aa4
        charge(ctx, 4);
        // the motion row v1, chosen as in sub_2835E0
        lbu(v1, s1, unit::kSide);
        v0 = 2;
        bool from_table = true;  // host only: the paths that reach 0x283af4
        if (v1 != v0) {
            // 0x00283ab4
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00283abc
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00283ad0
                    charge(ctx, 7);
                    jal(ctx, 0x283AD0u, gen::fn_sub_2FB860_002fb860);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = si(-1);
                    if (v1 != v0) {
                        // 0x00283aec
                        charge(ctx, 2);
                        from_table = false;
                    }
                } else {
                    // 0x00283ac8
                    charge(ctx, 2);
                    // 0x00283b34
                    charge(ctx, 3);
                    v1 = 0;
                    from_table = false;
                }
            }
        }
        if (from_table) {
            // 0x00283af4: table 0x693290 [26 * side + motion]
            charge(ctx, 16);
            lbu(v1, s1, unit::kSide);
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
            // 0x00283b40
            charge(ctx, 2);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
        }
        // 0x00283b48
        charge(ctx, 6);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        lhu(v0, s1, unit::kMotionCount);
        at = slt(a0, v0);
        if (at == 0) {
            // 0x00283b80
            charge(ctx, 1);
            v0 = 6;
        } else {
            // 0x00283b60
            charge(ctx, 8);
            lw(v1, s1, unit::kMotionTbl);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            lh(v0, v0, 8);
        }
    } else {
        // 0x00283a98
        charge(ctx, 3);
        v0 = 6;
    }
    // 0x00283b84 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00284040 sub_284040 -- 300 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSkillGetCastClass] Cast-motion class of a skill: 1 for no skill / an id >= 464 / almighty or recovery elements;
// for HP skills the EFFECT.TBL row's flags (+2): 0x200 -> 0, bit 0 with a3 set -> 2, else 1; other skills 3.
// Arguments: a1 btlUnit, a2 skill, a3 flag.
void sub_284040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00284040
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = dsll32(s2, 16);
    s0 = dsra32(s0, 16);
    v0 = si(-1);
    if (s0 != v0) {
        // 0x00284078
        charge(ctx, 3);
        v0 = slti(s0, 464);
        if (v0 == 0) {
            goto L_00284084;
        }
        // 0x00284090
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x284094u, gen::fn_datCalcIsHpSkill_002d6370);
        if (v0 == 0) {
            // 0x00284104
            charge(ctx, 9);
            a1 = s2 & 0xFFFF;
            lw(a0, s3, unit::kDat);
            jal(ctx, 0x28410Cu, gen::fn_datCalcGetSkillElement_003082f0);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 17;
            if (v1 != v0) {
                // 0x00284128
                charge(ctx, 3);
                v0 = 16;
                if (v1 == v0) {
                    goto L_0028413c;
                }
                // 0x00284134
                charge(ctx, 2);
                // 0x00284148
                charge(ctx, 1);
                v0 = 3;
                // 0x0028414c (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x50);
                return;
            }
        L_0028413c:
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x002840a4
            charge(ctx, 10);
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
            v0 = addiu(v0, 2);
            v0 = addu(v0, v1);
            lhu(v1, v0, 0);
            v0 = v1 & 0x200;
            if (v0 != 0) {
                // 0x002840f8
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x002840cc
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x002840d4
                    charge(ctx, 3);
                    v0 = v1 & 0x1;
                    if (v0 == 0) {
                        goto L_002840e0;
                    }
                    // 0x002840ec
                    charge(ctx, 3);
                    v0 = 2;
                    // 0x0028414c (the shared epilogue, written out on this path)
                    charge(ctx, 8);
                    ld(ra, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x50);
                    return;
                }
            L_002840e0:
                charge(ctx, 3);
                v0 = 1;
            }
        }
        // 0x0028414c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00284084:
    charge(ctx, 3);
    v0 = 1;
    // 0x0028414c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00284C00 sub_284C00 -- 108 bytes; leaf frame (no stack)
// [btlUnitPktUpdateWaitMotion] Update callback: a party / enemy unit's wanted motion (+2528) equals its current one
// (+2510 when it has a model, else 0).
// Arguments: a0 packet data {unit}.
void sub_284C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00284c00
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lbu(v1, a0, unit::kSide);
    v0 = 1;
    if (v1 != v0) {
        // 0x00284c14
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00284c24;
        }
        // 0x00284c1c
        charge(ctx, 2);
        // 0x00284c60
        charge(ctx, 1);
        v0 = 0;
        // 0x00284c64 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_00284c24:
    charge(ctx, 4);
    lw(v0, a0, 152);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00284c40
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00284c34
        charge(ctx, 3);
        lh(v0, a0, 2510);
    }
    // 0x00284c44
    charge(ctx, 7);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    lh(v0, a0, 2528);
    v0 = v0 ^ v1;
    v0 = sltiu(v0, 1);
    // 0x00284c64 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00285670 sub_285670 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 271: the unit's busy count -1.
// Arguments: a0 packet data.
void sub_285670(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285670
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285690 sub_285690 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktCreate271] Creates unit packet 271 (16 bytes: unit, u16 side + 1, u16 a1, u16 a2; clears live bit 0)
// with the hold / update / release callbacks sub_284FE0 / sub_2850F0 / sub_285670.
// Arguments: a0 btlUnit, a1, a2.
void sub_285690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285690
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 271;
    a1 = 16;
    jal(ctx, 0x2856B8u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x280000;
    v1 = addiu(v1, 20448);  // &sub_284FE0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 20720);  // &sub_2850F0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 22128);  // &sub_285670
    sw(v1, v0, pkt::kOnEnd);
    lw(a0, v0, pkt::kData);
    sw(s2, a0, 0);
    sh(s0, a0, 8);
    lbu(v1, s2, unit::kSide);
    v1 = addiu(v1, 1);
    sh(v1, a0, 4);
    sh(s1, a0, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00285730 sub_285730 -- 24 bytes; leaf frame (no stack)
// Hold callback of packet 272: busy +1.
// Arguments: a0 packet data.
void sub_285730(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285730
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x002857D0 sub_2857D0 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 272: busy -1.
// Arguments: a0 packet data.
void sub_2857D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002857d0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x002857F0 sub_2857F0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitPktCreate272] Creates unit packet 272 (4 bytes: unit; clears live bit 0), callbacks sub_285730 / sub_285750
// / sub_2857D0.
// Arguments: a0 btlUnit.
void sub_2857F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002857f0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 272;
    a1 = 4;
    jal(ctx, 0x285808u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x280000;
    v1 = addiu(v1, 22320);  // &sub_285730
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 22352);  // &sub_285750
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 22480);  // &sub_2857D0
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00285860 sub_285860 -- 24 bytes; leaf frame (no stack)
// Hold callback of the tint fade packet 274: busy +1.
// Arguments: a0 packet data.
void sub_285860(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285860
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285880 sub_285880 -- 1164 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateTintFade] Update of the tint fade packet 274: on frame 0 takes the start colour (the unit's +48,
// with the alpha / colour forced by flags +17), then each frame lerps the colour part and the alpha part separately
// (VU0, byte <-> float through 1/255) towards the target (+8) over the durations +12 / +14 by mode +16 (1 colour
// after alpha, 2 alpha after colour, 3 / 4 together), writes the unit's tint, sets model flag 0x4; done after the
// longer duration.
// Arguments: a0 packet data.
void sub_285880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00285880
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
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
    lw(s3, a0, 0);
    lh(s0, a0, 18);
    lbu(v1, a0, 16);
    v0 = 4;
    if (v1 != v0) {
        // 0x002858c4
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            goto L_00285928;
        }
        // 0x002858d0
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x0028590c
            charge(ctx, 7);
            lh(s1, s4, 14);
            s6 = 0;
            lh(s2, s4, 12);
            s5 = addiu(s1, 1);
            s7 = addu(s1, s2);
        } else {
            // 0x002858dc
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x002858f0
                charge(ctx, 7);
                lh(s2, s4, 12);
                s5 = 0;
                lh(s1, s4, 14);
                s6 = addiu(s2, 1);
                s7 = addu(s1, s2);
            } else {
                // 0x002858e8
                charge(ctx, 2);
            }
        }
        goto L_00285954;
    }
L_00285928:
    charge(ctx, 7);
    lh(s2, s4, 12);
    s5 = 0;
    lh(s1, s4, 14);
    s6 = 0;
    at = slt(s1, s2);
    if (at == 0) {
        // 0x00285950
        charge(ctx, 1);
        s7 = s1;
    } else {
        // 0x00285944
        charge(ctx, 3);
        s7 = s2;
    }
L_00285954:
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0028595c
        charge(ctx, 15);
        lbu(v0, s3, 51);
        v1 = sll(v0, 24);
        lbu(v0, s3, 50);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, s3, 49);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, s3, unit::kColour);
        v0 = v0 | v1;
        sw(v0, s4, 4);
        lbu(v0, s4, 17);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x00285998
            charge(ctx, 4);
            lw(v0, s4, 4);
            v0 = dsll32(v0, 8);
            v0 = dsrl32(v0, 8);
            sw(v0, s4, 4);
        }
        // 0x002859a8
        charge(ctx, 4);
        lbu(v0, s4, 17);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002859b8
            charge(ctx, 6);
            lw(v0, s4, 4);
            v1 = dsll32(v0, 8);
            v1 = dsrl32(v1, 8);
            v0 = lui(0xFF00);
            v0 = v1 | v0;
            sw(v0, s4, 4);
        }
        // 0x002859d0
        charge(ctx, 4);
        lbu(v0, s4, 17);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x002859e0
            charge(ctx, 1);
            sw(zero, s4, 4);
        }
        // 0x002859e4
        charge(ctx, 4);
        lbu(v0, s4, 17);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002859f4
            charge(ctx, 2);
            v0 = si(-1);
            sw(v0, s4, 4);
        }
        // 0x002859fc
        charge(ctx, 3);
        a0 = s3;
        jal(ctx, 0x285A00u, gen::fn_sub_287490_00287490);
    }
    // 0x00285a08
    charge(ctx, 4);
    lw(v1, s4, 4);
    v0 = slt(s0, s6);
    if (v0 == 0) {
        // 0x00285a18
        charge(ctx, 2);
        if (i64(s1) > 0) {
            // 0x00285a20
            charge(ctx, 4);
            v0 = addu(s6, s1);
            at = slt(s0, v0);
            if (at == 0) {
                goto L_00285a64;
            }
            // 0x00285a30
            charge(ctx, 13);
            v0 = subu(s0, s6);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            mtc1(s1, f0);
            cvt_s_w(f0, f0);
            div_s(f1, f1, f0);
            goto L_00285a6c;
        }
    L_00285a64:
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f1);
    L_00285a6c:
        charge(ctx, 52);
        lw(v0, s4, 8);
        sw(v0, sp, 0xA8);
        v0 = addiu(sp, 0xA8);
        lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf11, false);  // qmtc2
        vitof0(0xF, vf11, vf11);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        lw(v0, s4, 4);
        sw(v0, sp, 0xA4);
        v0 = addiu(sp, 0xA4);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f0, f0, f1);
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        mfc1(v0, f1);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        v0 = 0x437F0000;
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0xA0);
        lw(a0, sp, 0xA0);
        v0 = lui(0xFF00);
        v1 = v1 & v0;
        v0 = dsll32(a0, 8);
        v0 = dsrl32(v0, 8);
        v1 = v1 | v0;
    }
    // 0x00285b3c
    charge(ctx, 3);
    v0 = slt(s0, s5);
    if (v0 == 0) {
        // 0x00285b48
        charge(ctx, 2);
        if (i64(s2) > 0) {
            // 0x00285b50
            charge(ctx, 4);
            v0 = addu(s5, s2);
            at = slt(s0, v0);
            if (at == 0) {
                goto L_00285b94;
            }
            // 0x00285b60
            charge(ctx, 13);
            v0 = subu(s0, s5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            mtc1(s2, f0);
            cvt_s_w(f0, f0);
            div_s(f1, f1, f0);
            goto L_00285b9c;
        }
    L_00285b94:
        charge(ctx, 2);
        v0 = 0x3F800000;
        mtc1(v0, f1);
    L_00285b9c:
        charge(ctx, 52);
        lw(v0, s4, 8);
        sw(v0, sp, 0x9C);
        v0 = addiu(sp, 0x9C);
        lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf11, false);  // qmtc2
        vitof0(0xF, vf11, vf11);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        lw(v0, s4, 4);
        sw(v0, sp, 0x98);
        v0 = addiu(sp, 0x98);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f0, f0, f1);
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        mfc1(v0, f1);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        v0 = 0x437F0000;
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0x94);
        lw(a0, sp, 0x94);
        v1 = dsll32(v1, 8);
        v1 = dsrl32(v1, 8);
        v0 = lui(0xFF00);
        v0 = a0 & v0;
        v1 = v1 | v0;
    }
    // 0x00285c6c
    charge(ctx, 21);
    sb(v1, sp, 0xAC);
    v0 = srl(v1, 8);
    sb(v0, sp, 0xAD);
    v0 = srl(v1, 16);
    sb(v0, sp, 0xAE);
    v0 = srl(v1, 24);
    sb(v0, sp, 0xAF);
    lbu(a1, sp, 0xAC);
    lbu(a0, sp, 0xAD);
    lbu(v1, sp, 0xAE);
    lbu(v0, sp, 0xAF);
    sb(a1, s3, unit::kColour);
    sb(a0, s3, 49);
    sb(v1, s3, 50);
    sb(v0, s3, 51);
    lw(v0, s3, unit::kModelFlags);
    v0 = v0 | 0x4;
    sw(v0, s3, unit::kModelFlags);
    at = slt(s7, s0);
    if (at == 0) {
        // 0x00285ccc
        charge(ctx, 4);
        lh(v0, s4, 18);
        v0 = addiu(v0, 1);
        sh(v0, s4, 18);
        v0 = 0;
    } else {
        // 0x00285cc0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00285cdc (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x00285D10 sub_285D10 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 274: busy -1.
// Arguments: a0 packet data.
void sub_285D10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285d10
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285D30 sub_285D30 -- 176 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktCreateTintFade] Creates the tint fade packet 274 (20 bytes: unit, target RGBA, s16 durations, u8 mode,
// u8 flags).
// Arguments: a0 btlUnit, a1 colour, a2 / a3 frames, t0 mode, t1 flags.
void sub_285D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285d30
    enter(ctx, 44);  // entry check point + this block's cycles
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
    s2 = a3;
    s1 = t0;
    s0 = t1;
    a0 = 274;
    a1 = 20;
    jal(ctx, 0x285D70u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 22624);  // &sub_285860
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 22656);  // &sub_285880
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 23824);  // &sub_285D10
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s5, v1, 0);
    sw(s4, v1, 8);
    sh(s3, v1, 12);
    sh(s2, v1, 14);
    sb(s1, v1, 16);
    sb(s0, v1, 17);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00285F80 sub_285F80 -- 24 bytes; leaf frame (no stack)
// Hold callback of packet 277: busy +1.
// Arguments: a0 packet data.
void sub_285F80(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00285f80
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00285FA0 sub_285FA0 -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateShowParts] Update of packet 277: shows the unit's five model attachments (clears bit 1 of
// attachment +216 where sub_319770 agrees). Done at once.
// Arguments: a0 packet data.
void sub_285FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00285fa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 0);
    lw(v0, s1, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00285fd4
        charge(ctx, 3);
        lw(v0, s1, unit::kModel);
        if (v0 != 0) {
            // 0x00285fec
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00286060
                charge(ctx, 4);
                v0 = s2 & 0xFFFF;
                v0 = slti(v0, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00285ff8
                charge(ctx, 10);
                lw(a0, s1, unit::kModel);
                v1 = s2 & 0xFFFF;
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                s0 = sll(v0, 2);
                v1 = addu(a0, s0);
                lbu(v0, v1, 948);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x00286020
                    charge(ctx, 3);
                    lw(v0, v1, 952);
                    if (v0 != 0) {
                        // 0x0028602c
                        charge(ctx, 5);
                        a1 = s2;
                        jal(ctx, 0x286030u, gen::fn_sub_319770_00319770);
                        if (v0 != 0) {
                            // 0x00286040
                            charge(ctx, 6);
                            lw(v0, s1, unit::kModel);
                            v0 = addu(v0, s0);
                            lw(v1, v0, 952);
                            lhu(v0, v1, 216);
                            v0 = v0 & 0xFFFD;
                            sh(v0, v1, 216);
                        }
                    }
                }
                // 0x00286058
                charge(ctx, 2);
                v0 = addiu(s2, 1);
                s2 = v0 & 0xFFFF;
            }
            // 0x00286070
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00285fe0
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x00285fc8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00286074 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00286090 sub_286090 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 277: busy -1.
// Arguments: a0 packet data.
void sub_286090(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00286090
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x002860B0 sub_2860B0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitPktCreateShowParts] Creates packet 277 (4 bytes: unit).
// Arguments: a0 btlUnit.
void sub_2860B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002860b0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 277;
    a1 = 4;
    jal(ctx, 0x2860C8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 24448);  // &sub_285F80
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 24480);  // &sub_285FA0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 24720);  // &sub_286090
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00286110 sub_286110 -- 24 bytes; leaf frame (no stack)
// Hold callback of packet 278: busy +1.
// Arguments: a0 packet data.
void sub_286110(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00286110
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x00286130 sub_286130 -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateHideParts] Update of packet 278: hides the five model attachments (sets bit 1 of +216). Done at
// once.
// Arguments: a0 packet data.
void sub_286130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00286130
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 0);
    lw(v0, s1, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x00286164
        charge(ctx, 3);
        lw(v0, s1, unit::kModel);
        if (v0 != 0) {
            // 0x0028617c
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x002861f0
                charge(ctx, 4);
                v0 = s2 & 0xFFFF;
                v0 = slti(v0, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00286188
                charge(ctx, 10);
                lw(a0, s1, unit::kModel);
                v1 = s2 & 0xFFFF;
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                s0 = sll(v0, 2);
                v1 = addu(a0, s0);
                lbu(v0, v1, 948);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x002861b0
                    charge(ctx, 3);
                    lw(v0, v1, 952);
                    if (v0 != 0) {
                        // 0x002861bc
                        charge(ctx, 5);
                        a1 = s2;
                        jal(ctx, 0x2861C0u, gen::fn_sub_319770_00319770);
                        if (v0 != 0) {
                            // 0x002861d0
                            charge(ctx, 6);
                            lw(v0, s1, unit::kModel);
                            v0 = addu(v0, s0);
                            lw(v1, v0, 952);
                            lhu(v0, v1, 216);
                            v0 = v0 | 0x2;
                            sh(v0, v1, 216);
                        }
                    }
                }
                // 0x002861e8
                charge(ctx, 2);
                v0 = addiu(s2, 1);
                s2 = v0 & 0xFFFF;
            }
            // 0x00286200
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00286170
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x00286158
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00286204 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00286220 sub_286220 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 278: busy -1.
// Arguments: a0 packet data.
void sub_286220(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00286220
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00286240 sub_286240 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitPktCreateHideParts] Creates packet 278 (4 bytes: unit).
// Arguments: a0 btlUnit.
void sub_286240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00286240
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 278;
    a1 = 4;
    jal(ctx, 0x286258u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 24848);  // &sub_286110
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 24880);  // &sub_286130
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 25120);  // &sub_286220
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002862A0 sub_2862A0 -- 24 bytes; leaf frame (no stack)
// Hold callback of packet 282: busy +1.
// Arguments: a0 packet data.
void sub_2862A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x002862a0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, 1);
    sh(v1, a0, unit::kBusy);
}

// 0x002862C0 sub_2862C0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlUnitPktUpdateAuraOff] Update of packet 282: removes the unit's aura effect (sub_2BBBC0) when it has one
// (+2556). Done at once.
// Arguments: a0 packet data.
void sub_2862C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002862c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 0);
    lw(a0, v0, unit::kAura);
    if (a0 != 0) {
        // 0x002862d8
        charge(ctx, 2);
        jal(ctx, 0x2862D8u, gen::fn_sub_2BBBC0_002bbbc0);
    }
    // 0x002862e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00286300 sub_286300 -- 24 bytes; leaf frame (no stack)
// Release callback of packet 282: busy -1.
// Arguments: a0 packet data.
void sub_286300(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00286300
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    lhu(v1, a0, unit::kBusy);
    v1 = addiu(v1, -1);
    sh(v1, a0, unit::kBusy);
}

// 0x00286320 sub_286320 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitPktCreateAuraOff] Creates packet 282 (4 bytes: unit).
// Arguments: a0 btlUnit.
void sub_286320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00286320
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 282;
    a1 = 4;
    jal(ctx, 0x286338u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x280000;
    v1 = addiu(v1, 25248);  // &sub_2862A0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x280000;
    v1 = addiu(v1, 25280);  // &sub_2862C0
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x280000;
    v1 = addiu(v1, 25344);  // &sub_286300
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00287B20 sub_287B20 -- 452 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitModelFeatureOn] Switches a model feature on (unit with a model only): 1 the outline (sub_319010, widths 0.4
// / 1.0), 2 sub_319050, 3 the model flags 0x1000 | 0x2000 and ~0x800, 4 model +1022 bit 4, 5 the shadow (sub_1A0DC0)
// for a placed unit that has one.
// Arguments: a0 btlUnit, a1 feature 1..5.
void sub_287B20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00287b20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, unit::kModelFlags);
    a2 = v1 & 0x2;
    if (a2 != 0) {
        // 0x00287b40
        charge(ctx, 4);
        a0 = a1 & 0xFFFF;
        v1 = 4;
        if (a0 == v1) {
            // 0x00287cc0
            charge(ctx, 4);
            lw(a0, s0, unit::kModel);
            lhu(v1, a0, 1022);
            v1 = v1 | 0x10;
            sh(v1, a0, 1022);
        } else {
            // 0x00287b50
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                // 0x00287c48
                charge(ctx, 30);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287C4Cu, gen::fn_sub_319200_00319200);
                v0 = v0 & 0xFFFF;
                v0 = v0 | 0x1000;
                a1 = v0 & 0xFFFF;
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287C64u, gen::fn_sub_3191F0_003191f0);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287C70u, gen::fn_sub_319200_00319200);
                v0 = v0 & 0xFFFF;
                v0 = v0 | 0x2000;
                a1 = v0 & 0xFFFF;
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287C88u, gen::fn_sub_3191F0_003191f0);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287C94u, gen::fn_sub_319200_00319200);
                v1 = v0 & 0xFFFF;
                v0 = si(-2049);
                v0 = v1 & v0;
                a1 = v0 & 0xFFFF;
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287CB0u, gen::fn_sub_3191F0_003191f0);
            } else {
                // 0x00287b5c
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00287c34
                    charge(ctx, 5);
                    lw(a0, s0, unit::kModel);
                    jal(ctx, 0x287C38u, gen::fn_sub_319050_00319050);
                } else {
                    // 0x00287b68
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00287bfc
                        charge(ctx, 14);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x287C00u, gen::fn_sub_319010_00319010);
                        lwc1(f0, gp, kGpF04);  // f32 0.4: model +924 / +928 of sub_287B20 feature 1 0x7CAD78
                        lw(v1, s0, unit::kModel);
                        swc1(f0, v1, 924);
                        lw(v1, s0, unit::kModel);
                        lwc1(f0, v1, 924);
                        swc1(f0, v1, 928);
                        a0 = 0x3F800000;
                        lw(v1, s0, unit::kModel);
                        sw(a0, v1, 932);
                    } else {
                        // 0x00287b74
                        charge(ctx, 3);
                        v1 = 5;
                        if (a0 == v1) {
                            // 0x00287b88
                            charge(ctx, 4);
                            lw(a1, s0, unit::kFlags);
                            v1 = a1 & 0x800;
                            if (v1 == 0) {
                                // 0x00287b98
                                charge(ctx, 3);
                                lhu(a0, s0, unit::kShadow);
                                if (a0 != 0) {
                                    // 0x00287ba4
                                    charge(ctx, 3);
                                    v1 = a1 & 0x8;
                                    if (v1 != 0) {
                                        // 0x00287bb0
                                        charge(ctx, 2);
                                        if (a2 == 0) {
                                            // 0x00287bc4
                                            charge(ctx, 1);
                                            v1 = 0;
                                        } else {
                                            // 0x00287bb8
                                            charge(ctx, 3);
                                            lh(v1, s0, unit::kMotion);
                                        }
                                        // 0x00287bc8
                                        charge(ctx, 5);
                                        a1 = dsll32(v1, 16);
                                        a1 = dsra32(a1, 16);
                                        v1 = 18;
                                        if (a1 != v1) {
                                            // 0x00287bdc
                                            charge(ctx, 8);
                                            a1 = 0;
                                            jal(ctx, 0x287BE0u, gen::fn_sub_1A0DC0_001a0dc0);
                                            lw(v1, s0, unit::kFlags);
                                            v1 = v1 | 0x800;
                                            sw(v1, s0, unit::kFlags);
                                        }
                                    }
                                }
                            }
                        } else {
                            // 0x00287b80
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00287cd0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00287CF0 sub_287CF0 -- 428 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlUnitModelFeatureOff] Switches the same features off (3 also clears the look mode +176).
// Arguments: a0 btlUnit, a1 feature 1..5.
void sub_287CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00287cf0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, unit::kModelFlags);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x00287d10
        charge(ctx, 4);
        a0 = a1 & 0xFFFF;
        v1 = 4;
        if (a0 == v1) {
            // 0x00287e78
            charge(ctx, 4);
            lw(a0, s0, unit::kModel);
            lhu(v1, a0, 1022);
            v1 = v1 & 0xFFEF;
            sh(v1, a0, 1022);
        } else {
            // 0x00287d20
            charge(ctx, 3);
            v1 = 3;
            if (a0 == v1) {
                // 0x00287dd8
                charge(ctx, 40);
                lw(a0, s0, unit::kModel);
                lwc1(f12, gp, kGpF02);  // f32 0.2: sub_319090's argument in sub_287CF0 feature 3 0x7CADA4
                jal(ctx, 0x287DE0u, gen::fn_sub_319090_00319090);
                v0 = 0x428C0000;
                mtc1(v0, f12);
                v0 = 0x42A00000;
                mtc1(v0, f13);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287DFCu, gen::fn_sub_3190A0_003190a0);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E08u, gen::fn_sub_3191B0_003191b0);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E14u, gen::fn_sub_319190_00319190);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E20u, gen::fn_sub_319200_00319200);
                v1 = v0 & 0xFFFF;
                v0 = si(-8193);
                v0 = v1 & v0;
                a1 = v0 & 0xFFFF;
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E3Cu, gen::fn_sub_3191F0_003191f0);
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E48u, gen::fn_sub_319200_00319200);
                v1 = v0 & 0xFFFF;
                v0 = si(-4097);
                v0 = v1 & v0;
                a1 = v0 & 0xFFFF;
                lw(a0, s0, unit::kModel);
                jal(ctx, 0x287E64u, gen::fn_sub_3191F0_003191f0);
                sh(zero, s0, unit::kLookMode);
            } else {
                // 0x00287d2c
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00287dc4
                    charge(ctx, 5);
                    lw(a0, s0, unit::kModel);
                    jal(ctx, 0x287DC8u, gen::fn_sub_319070_00319070);
                } else {
                    // 0x00287d38
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00287da0
                        charge(ctx, 9);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x287DA4u, gen::fn_sub_319030_00319030);
                        lw(a0, s0, unit::kModel);
                        lbu(v1, a0, 904);
                        v1 = v1 & 0xE2;
                        sb(v1, a0, 904);
                    } else {
                        // 0x00287d44
                        charge(ctx, 3);
                        v1 = 5;
                        if (a0 == v1) {
                            // 0x00287d58
                            charge(ctx, 4);
                            lw(a1, s0, unit::kFlags);
                            v1 = a1 & 0x800;
                            if (v1 != 0) {
                                // 0x00287d68
                                charge(ctx, 3);
                                lhu(a0, s0, unit::kShadow);
                                if (a0 != 0) {
                                    // 0x00287d74
                                    charge(ctx, 11);
                                    v0 = a1 & 0x1000;
                                    v0 = sltu(0, v0);
                                    a1 = v0 ^ 0x1;
                                    jal(ctx, 0x287D80u, gen::fn_sub_1A0DC0_001a0dc0);
                                    lw(a0, s0, unit::kFlags);
                                    v1 = si(-2049);
                                    v1 = a0 & v1;
                                    sw(v1, s0, unit::kFlags);
                                }
                            }
                        } else {
                            // 0x00287d50
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00287e88 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002880E0 sub_2880E0 -- 36 bytes; leaf frame (no stack)
// Sets the pose byte (+172) of a persona unit (side 2); nothing for a null unit or another side.
// Arguments: a0 btlUnit, a1 byte.
void sub_2880E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x002880e0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 != 0) {
        // 0x002880e8
        charge(ctx, 4);
        lbu(a2, a0, unit::kSide);
        v1 = 2;
        if (a2 == v1) {
            // 0x002880f8
            charge(ctx, 1);
            sb(a1, a0, unit::kPersonaPose);
        }
    }
    // 0x002880fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00288170 sub_288170 -- 32 bytes; leaf frame (no stack)
// Hold callback of the look-at-point packet 279 (the unit may be null).
// Arguments: a0 packet data.
void sub_288170(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00288170
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x0028817c
        charge(ctx, 3);
        lhu(v1, a0, unit::kBusy);
        v1 = addiu(v1, 1);
        sh(v1, a0, unit::kBusy);
    }
    // 0x00288188 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00288190 sub_288190 -- 432 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateLookAtPoint] Update of packet 279: makes the unit (or, with flag bit 0, every placed party unit)
// look at the point (+4): look mode 1, +184 = the point, feature 3 on; resets the head-turn limits first. Done at
// once.
// Arguments: a0 packet data {unit, f32[3], u16 flags}.
void sub_288190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00288190
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(v0, a0, 16);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x00288284
        charge(ctx, 4);
        lw(s0, s1, 0);
        v0 = addiu(sp, 0x34);
        if (v0 != 0) {
            // 0x00288294
            charge(ctx, 2);
            v0 = 0x428C0000;
            sw(v0, sp, 0x34);
        }
        // 0x0028829c
        charge(ctx, 3);
        v0 = addiu(sp, 0x30);
        if (v0 != 0) {
            // 0x002882a8
            charge(ctx, 2);
            v0 = 0x42960000;
            sw(v0, sp, 0x30);
        }
        // 0x002882b0
        charge(ctx, 6);
        lwc1(f13, sp, 0x30);
        lwc1(f12, sp, 0x34);
        lw(v0, s0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002882c8
            charge(ctx, 3);
            lw(a0, s0, unit::kModel);
            jal(ctx, 0x2882CCu, gen::fn_sub_3190A0_003190a0);
        }
        // 0x002882d4
        charge(ctx, 4);
        lw(v0, s0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002882e4
            charge(ctx, 4);
            lw(a0, s0, unit::kModel);
            lwc1(f12, gp, kGpF03b);  // f32 0.3: sub_319090's argument in sub_288190 / sub_288430 0x7CB080
            jal(ctx, 0x2882ECu, gen::fn_sub_319090_00319090);
        }
        // 0x002882f4
        charge(ctx, 12);
        v0 = 1;
        sh(v0, s0, unit::kLookMode);
        lwc1(f2, s1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, s1, 12);
        swc1(f2, s0, unit::kLookPos);
        swc1(f1, s0, unit::kLookPos + 4);
        swc1(f0, s0, unit::kLookPos + 8);
        a0 = s0;
        a1 = 3;
        jal(ctx, 0x28831Cu, gen::fn_sub_287B20_00287b20);
    } else {
        // 0x002881b4
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s0, v0, gbtl::kUnitHead0);
        for (;;) {
            // 0x00288274
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002881c4
            charge(ctx, 4);
            lw(v0, s0, unit::kFlags);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                // 0x002881d4
                charge(ctx, 3);
                v0 = addiu(sp, 0x3C);
                if (v0 != 0) {
                    // 0x002881e0
                    charge(ctx, 2);
                    v0 = 0x428C0000;
                    sw(v0, sp, 0x3C);
                }
                // 0x002881e8
                charge(ctx, 3);
                v0 = addiu(sp, 0x38);
                if (v0 != 0) {
                    // 0x002881f4
                    charge(ctx, 2);
                    v0 = 0x42960000;
                    sw(v0, sp, 0x38);
                }
                // 0x002881fc
                charge(ctx, 6);
                lwc1(f13, sp, 0x38);
                lwc1(f12, sp, 0x3C);
                lw(v0, s0, unit::kModelFlags);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x00288214
                    charge(ctx, 3);
                    lw(a0, s0, unit::kModel);
                    jal(ctx, 0x288218u, gen::fn_sub_3190A0_003190a0);
                }
                // 0x00288220
                charge(ctx, 4);
                lw(v0, s0, unit::kModelFlags);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x00288230
                    charge(ctx, 4);
                    lw(a0, s0, unit::kModel);
                    lwc1(f12, gp, kGpF03b);  // f32 0.3: sub_319090's argument in sub_288190 / sub_288430 0x7CB080
                    jal(ctx, 0x288238u, gen::fn_sub_319090_00319090);
                }
                // 0x00288240
                charge(ctx, 12);
                v0 = 1;
                sh(v0, s0, unit::kLookMode);
                lwc1(f2, s1, 4);
                lwc1(f1, s1, 8);
                lwc1(f0, s1, 12);
                swc1(f2, s0, unit::kLookPos);
                swc1(f1, s0, unit::kLookPos + 4);
                swc1(f0, s0, unit::kLookPos + 8);
                a0 = s0;
                a1 = 3;
                jal(ctx, 0x288268u, gen::fn_sub_287B20_00287b20);
            }
            // 0x00288270
            charge(ctx, 1);
            lw(s0, s0, unit::kNext);
        }
        // 0x0028827c
        charge(ctx, 2);
    }
    // 0x00288324 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00288340 sub_288340 -- 32 bytes; leaf frame (no stack)
// Release callback of packet 279.
// Arguments: a0 packet data.
void sub_288340(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00288340
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x0028834c
        charge(ctx, 3);
        lhu(v1, a0, unit::kBusy);
        v1 = addiu(v1, -1);
        sh(v1, a0, unit::kBusy);
    }
    // 0x00288358 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00288360 sub_288360 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktCreateLookAtPoint] Creates the look-at-point packet 279 (20 bytes: unit, the point, u16 flags).
// Arguments: a0 btlUnit, a1 f32[3]*, a2 flags.
void sub_288360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00288360
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 279;
    a1 = 20;
    jal(ctx, 0x288388u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x290000;
    v1 = addiu(v1, -32400);  // &sub_288170
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x290000;
    v1 = addiu(v1, -32368);  // &sub_288190
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x290000;
    v1 = addiu(v1, -31936);  // &sub_288340
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s2, v1, 0);
    sh(s0, v1, 16);
    lwc1(f2, s1, 0);
    lwc1(f1, s1, 4);
    lwc1(f0, s1, 8);
    swc1(f2, v1, 4);
    swc1(f1, v1, 8);
    swc1(f0, v1, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00288400 sub_288400 -- 48 bytes; leaf frame (no stack)
// Hold callback of the look-at-unit packet 280: busy +1 on both units (the first may be null).
// Arguments: a0 packet data.
void sub_288400(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00288400
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a0, 0);
    if (a1 != 0) {
        // 0x0028840c
        charge(ctx, 3);
        lhu(v1, a1, unit::kBusy);
        v1 = addiu(v1, 1);
        sh(v1, a1, unit::kBusy);
    }
    // 0x00288418 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(a0, a0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, 1);
    sh(v1, a0, 160);
}

// 0x00288430 sub_288430 -- 632 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateLookAtUnit] Update of packet 280: makes the unit (or the party side with flag bit 0 and / or the
// enemy side with bit 1) look at the target unit: look mode 2, +180 = the target's uid, feature 3 on. Done at once.
// Arguments: a0 packet data {unit, target, u16 flags}.
void sub_288430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00288430
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v1, a0, 8);
    v0 = v1 & 0x3;
    if (v0 == 0) {
        // 0x002885f4
        charge(ctx, 5);
        lw(s1, s0, 4);
        lw(s0, s0, 0);
        v0 = addiu(sp, 0x4C);
        if (v0 != 0) {
            // 0x00288608
            charge(ctx, 2);
            v0 = 0x428C0000;
            sw(v0, sp, 0x4C);
        }
        // 0x00288610
        charge(ctx, 3);
        v0 = addiu(sp, 0x48);
        if (v0 != 0) {
            // 0x0028861c
            charge(ctx, 2);
            v0 = 0x42960000;
            sw(v0, sp, 0x48);
        }
        // 0x00288624
        charge(ctx, 6);
        lwc1(f13, sp, 0x48);
        lwc1(f12, sp, 0x4C);
        lw(v0, s0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x0028863c
            charge(ctx, 3);
            lw(a0, s0, unit::kModel);
            jal(ctx, 0x288640u, gen::fn_sub_3190A0_003190a0);
        }
        // 0x00288648
        charge(ctx, 4);
        lw(v0, s0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x00288658
            charge(ctx, 4);
            lw(a0, s0, unit::kModel);
            lwc1(f12, gp, kGpF03b);  // f32 0.3: sub_319090's argument in sub_288190 / sub_288430 0x7CB080
            jal(ctx, 0x288660u, gen::fn_sub_319090_00319090);
        }
        // 0x00288668
        charge(ctx, 8);
        v0 = 2;
        sh(v0, s0, unit::kLookMode);
        lw(v0, s1, 168);
        sw(v0, s0, unit::kLookUid);
        a0 = s0;
        a1 = 3;
        jal(ctx, 0x288680u, gen::fn_sub_287B20_00287b20);
    } else {
        // 0x00288458
        charge(ctx, 3);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x00288464
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(s2, v0, gbtl::kUnitHead0);
            for (;;) {
                // 0x00288518
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00288474
                charge(ctx, 4);
                lw(v0, s2, unit::kFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x00288484
                    charge(ctx, 4);
                    lw(s1, s0, 4);
                    v0 = addiu(sp, 0x5C);
                    if (v0 != 0) {
                        // 0x00288494
                        charge(ctx, 2);
                        v0 = 0x428C0000;
                        sw(v0, sp, 0x5C);
                    }
                    // 0x0028849c
                    charge(ctx, 3);
                    v0 = addiu(sp, 0x58);
                    if (v0 != 0) {
                        // 0x002884a8
                        charge(ctx, 2);
                        v0 = 0x42960000;
                        sw(v0, sp, 0x58);
                    }
                    // 0x002884b0
                    charge(ctx, 6);
                    lwc1(f13, sp, 0x58);
                    lwc1(f12, sp, 0x5C);
                    lw(v0, s2, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002884c8
                        charge(ctx, 3);
                        lw(a0, s2, unit::kModel);
                        jal(ctx, 0x2884CCu, gen::fn_sub_3190A0_003190a0);
                    }
                    // 0x002884d4
                    charge(ctx, 4);
                    lw(v0, s2, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002884e4
                        charge(ctx, 4);
                        lw(a0, s2, unit::kModel);
                        lwc1(f12, gp, kGpF03b);  // f32 0.3: sub_319090's argument in sub_288190 / sub_288430 0x7CB080
                        jal(ctx, 0x2884ECu, gen::fn_sub_319090_00319090);
                    }
                    // 0x002884f4
                    charge(ctx, 8);
                    v0 = 2;
                    sh(v0, s2, unit::kLookMode);
                    lw(v0, s1, 168);
                    sw(v0, s2, unit::kLookUid);
                    a0 = s2;
                    a1 = 3;
                    jal(ctx, 0x28850Cu, gen::fn_sub_287B20_00287b20);
                }
                // 0x00288514
                charge(ctx, 1);
                lw(s2, s2, unit::kNext);
            }
        }
        // 0x00288520
        charge(ctx, 4);
        lhu(v0, s0, 8);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x00288530
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(s2, v0, gbtl::kUnitHead1);
            for (;;) {
                // 0x002885e4
                charge(ctx, 2);
                if (s2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00288540
                charge(ctx, 4);
                lw(v0, s2, unit::kFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x00288550
                    charge(ctx, 4);
                    lw(s1, s0, 4);
                    v0 = addiu(sp, 0x54);
                    if (v0 != 0) {
                        // 0x00288560
                        charge(ctx, 2);
                        v0 = 0x428C0000;
                        sw(v0, sp, 0x54);
                    }
                    // 0x00288568
                    charge(ctx, 3);
                    v0 = addiu(sp, 0x50);
                    if (v0 != 0) {
                        // 0x00288574
                        charge(ctx, 2);
                        v0 = 0x42960000;
                        sw(v0, sp, 0x50);
                    }
                    // 0x0028857c
                    charge(ctx, 6);
                    lwc1(f13, sp, 0x50);
                    lwc1(f12, sp, 0x54);
                    lw(v0, s2, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x00288594
                        charge(ctx, 3);
                        lw(a0, s2, unit::kModel);
                        jal(ctx, 0x288598u, gen::fn_sub_3190A0_003190a0);
                    }
                    // 0x002885a0
                    charge(ctx, 4);
                    lw(v0, s2, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002885b0
                        charge(ctx, 4);
                        lw(a0, s2, unit::kModel);
                        lwc1(f12, gp, kGpF03b);  // f32 0.3: sub_319090's argument in sub_288190 / sub_288430 0x7CB080
                        jal(ctx, 0x2885B8u, gen::fn_sub_319090_00319090);
                    }
                    // 0x002885c0
                    charge(ctx, 8);
                    v0 = 2;
                    sh(v0, s2, unit::kLookMode);
                    lw(v0, s1, 168);
                    sw(v0, s2, unit::kLookUid);
                    a0 = s2;
                    a1 = 3;
                    jal(ctx, 0x2885D8u, gen::fn_sub_287B20_00287b20);
                }
                // 0x002885e0
                charge(ctx, 1);
                lw(s2, s2, unit::kNext);
            }
            // 0x002885ec
            charge(ctx, 2);
        }
    }
    // 0x00288688 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002886B0 sub_2886B0 -- 48 bytes; leaf frame (no stack)
// Release callback of packet 280: busy -1 on both units.
// Arguments: a0 packet data.
void sub_2886B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002886b0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a0, 0);
    if (a1 != 0) {
        // 0x002886bc
        charge(ctx, 3);
        lhu(v1, a1, unit::kBusy);
        v1 = addiu(v1, -1);
        sh(v1, a1, unit::kBusy);
    }
    // 0x002886c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(a0, a0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
}

// 0x002886E0 sub_2886E0 -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktCreateLookAtUnit] Creates the look-at-unit packet 280 (12 bytes).
// Arguments: a0 btlUnit, a1 target, a2 flags.
void sub_2886E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002886e0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 280;
    a1 = 12;
    jal(ctx, 0x288708u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x290000;
    v1 = addiu(v1, -31744);  // &sub_288400
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x290000;
    v1 = addiu(v1, -31696);  // &sub_288430
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x290000;
    v1 = addiu(v1, -31056);  // &sub_2886B0
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s2, v1, 0);
    sw(s1, v1, 4);
    sh(s0, v1, 8);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00288760 sub_288760 -- 32 bytes; leaf frame (no stack)
// Hold callback of the stop-looking packet 281.
// Arguments: a0 packet data.
void sub_288760(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00288760
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x0028876c
        charge(ctx, 3);
        lhu(v1, a0, unit::kBusy);
        v1 = addiu(v1, 1);
        sh(v1, a0, unit::kBusy);
    }
    // 0x00288778 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00288780 sub_288780 -- 420 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktUpdateLookEnd] Update of packet 281: ends the look (features off, look mode 0) for the unit or for the
// sides its flags name. Done at once.
// Arguments: a0 packet data {unit, u16 flags}.
void sub_288780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x00288780
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(v1, a0, 4);
    v0 = v1 & 0x3;
    if (v0 == 0) {
        // 0x002888b8
        charge(ctx, 5);
        lw(s0, s1, 0);
        lw(v0, s0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002888cc
            charge(ctx, 15);
            lw(a0, s0, unit::kModel);
            lwc1(f12, gp, kGpF03a);  // f32 0.3: sub_319090's argument in sub_288780 0x7CAD7C
            jal(ctx, 0x2888D4u, gen::fn_sub_319090_00319090);
            v0 = 0x428C0000;
            mtc1(v0, f12);
            v0 = 0x42960000;
            mtc1(v0, f13);
            lw(a0, s0, unit::kModel);
            jal(ctx, 0x2888F0u, gen::fn_sub_3190A0_003190a0);
            lw(a0, s0, unit::kModel);
            jal(ctx, 0x2888FCu, gen::fn_sub_319190_00319190);
            sh(zero, s0, unit::kLookMode);
        }
    } else {
        // 0x002887a4
        charge(ctx, 3);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002887b0
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(s0, v0, gbtl::kUnitHead0);
            for (;;) {
                // 0x00288820
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002887c0
                charge(ctx, 4);
                lw(v0, s0, unit::kFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x002887d0
                    charge(ctx, 4);
                    lw(v0, s0, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002887e0
                        charge(ctx, 15);
                        lw(a0, s0, unit::kModel);
                        lwc1(f12, gp, kGpF03a);  // f32 0.3: sub_319090's argument in sub_288780 0x7CAD7C
                        jal(ctx, 0x2887E8u, gen::fn_sub_319090_00319090);
                        v0 = 0x428C0000;
                        mtc1(v0, f12);
                        v0 = 0x42960000;
                        mtc1(v0, f13);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x288804u, gen::fn_sub_3190A0_003190a0);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x288810u, gen::fn_sub_319190_00319190);
                        sh(zero, s0, unit::kLookMode);
                    }
                }
                // 0x0028881c
                charge(ctx, 1);
                lw(s0, s0, unit::kNext);
            }
        }
        // 0x00288828
        charge(ctx, 4);
        lhu(v0, s1, 4);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x00288838
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(s0, v0, gbtl::kUnitHead1);
            for (;;) {
                // 0x002888a8
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00288848
                charge(ctx, 4);
                lw(v0, s0, unit::kFlags);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    // 0x00288858
                    charge(ctx, 4);
                    lw(v0, s0, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x00288868
                        charge(ctx, 15);
                        lw(a0, s0, unit::kModel);
                        lwc1(f12, gp, kGpF03a);  // f32 0.3: sub_319090's argument in sub_288780 0x7CAD7C
                        jal(ctx, 0x288870u, gen::fn_sub_319090_00319090);
                        v0 = 0x428C0000;
                        mtc1(v0, f12);
                        v0 = 0x42960000;
                        mtc1(v0, f13);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x28888Cu, gen::fn_sub_3190A0_003190a0);
                        lw(a0, s0, unit::kModel);
                        jal(ctx, 0x288898u, gen::fn_sub_319190_00319190);
                        sh(zero, s0, unit::kLookMode);
                    }
                }
                // 0x002888a4
                charge(ctx, 1);
                lw(s0, s0, unit::kNext);
            }
            // 0x002888b0
            charge(ctx, 2);
        }
    }
    // 0x00288908 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00288930 sub_288930 -- 32 bytes; leaf frame (no stack)
// Release callback of packet 281.
// Arguments: a0 packet data.
void sub_288930(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00288930
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x0028893c
        charge(ctx, 3);
        lhu(v1, a0, unit::kBusy);
        v1 = addiu(v1, -1);
        sh(v1, a0, unit::kBusy);
    }
    // 0x00288948 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00288950 sub_288950 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitPktCreateLookEnd] Creates the stop-looking packet 281 (8 bytes).
// Arguments: a0 btlUnit, a1 flags.
void sub_288950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00288950
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 281;
    a1 = 8;
    jal(ctx, 0x288970u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x290000;
    v1 = addiu(v1, -30880);  // &sub_288760
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x290000;
    v1 = addiu(v1, -30848);  // &sub_288780
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x290000;
    v1 = addiu(v1, -30416);  // &sub_288930
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00288DA0 sub_288DA0 -- 480 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitGetModelRow] The unit's MODEL.TBL row: persona -> section 3 row + 2; enemy -> the boss override sub_2FC410,
// else section 2 (+10 for kind 9); the hero -> section 0 by held weapon type; other party members -> section 1 (+10
// for kind 9).
// Arguments: a0 btlUnit, a1 kind.
void sub_288DA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00288da0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(s0, a0, unit::kId);
    v1 = a1 & 0xFFFF;
    v0 = 9;
    if (v1 == v0) {
        // 0x00288dcc
        charge(ctx, 3);
        s1 = 1;
    } else {
        // 0x00288dc4
        charge(ctx, 2);
        // 0x00288dd8
        charge(ctx, 1);
        s1 = 0;
    }
    // 0x00288ddc
    charge(ctx, 4);
    lbu(v1, a0, unit::kSide);
    v0 = 2;
    if (v1 == v0) {
        // 0x00288f3c
        charge(ctx, 10);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 3);
        lw(v0, gp, kGpModelPersona);  // MODEL.TBL section 3 (88-byte rows by persona id) 0x7CE42C
        v0 = addu(v0, v1);
        v0 = addiu(v0, 2);
    } else {
        // 0x00288dec
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00288ed0
            charge(ctx, 4);
            jal(ctx, 0x288ED0u, gen::fn_sub_2FC410_002fc410);
            if (v0 == 0) {
                // 0x00288ee8
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x00288f18
                    charge(ctx, 7);
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    v1 = sll(v0, 3);
                    lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
                    v0 = addu(v0, v1);
                } else {
                    // 0x00288ef0
                    charge(ctx, 10);
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    v1 = sll(v0, 3);
                    lw(v0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
                    v0 = addu(v0, v1);
                    v0 = addiu(v0, 10);
                }
                // 0x00288f34
                charge(ctx, 2);
            } else {
                // 0x00288ee0
                charge(ctx, 2);
            }
        } else {
            // 0x00288df8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00288e08
                charge(ctx, 2);
                if (s0 != v0) {
                    // 0x00288e7c
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x00288eac
                        charge(ctx, 7);
                        v0 = sll(s0, 5);
                        v0 = addu(v0, s0);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s0);
                        v1 = sll(v0, 1);
                        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1 (266-byte rows by party id) 0x7CE40C
                        v0 = addu(v0, v1);
                    } else {
                        // 0x00288e84
                        charge(ctx, 10);
                        v0 = sll(s0, 5);
                        v0 = addu(v0, s0);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s0);
                        v1 = sll(v0, 1);
                        lw(v0, gp, kGpModelParty);  // MODEL.TBL section 1 (266-byte rows by party id) 0x7CE40C
                        v0 = addu(v0, v1);
                        v0 = addiu(v0, 10);
                    }
                    // 0x00288ec8
                    charge(ctx, 2);
                } else {
                    // 0x00288e10
                    charge(ctx, 6);
                    lw(a0, a0, unit::kDat);
                    jal(ctx, 0x288E14u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                    v0 = v0 & 0xFF;
                    if (s1 == 0) {
                        // 0x00288e54
                        charge(ctx, 8);
                        v1 = v0 & 0xFF;
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 3);
                        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0 (296-byte rows by weapon type) 0x7CE408
                        v0 = addu(v0, v1);
                    } else {
                        // 0x00288e28
                        charge(ctx, 11);
                        v1 = v0 & 0xFF;
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 3);
                        lw(v0, gp, kGpModelWeapon);  // MODEL.TBL section 0 (296-byte rows by weapon type) 0x7CE408
                        v0 = addu(v0, v1);
                        v0 = addiu(v0, 10);
                    }
                    // 0x00288e74
                    charge(ctx, 2);
                }
            } else {
                // 0x00288e00
                charge(ctx, 2);
                // 0x00288f64
                charge(ctx, 1);
                v0 = 0;
            }
        }
    }
    // 0x00288f68 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00288FE0 sub_288FE0 -- 76 bytes; leaf frame (no stack)
// [btlUnitFindById] Finds the btlUnit of a side with a unit id (0 when none).
// Arguments: a0 side, a1 id.
void sub_288FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x00288fe0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = a0 & 0xFFFF;
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    lw(v0, v0, 340);
    a0 = a1 & 0xFFFF;
    for (;;) {
        // 0x00289018
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00289000
        charge(ctx, 3);
        lhu(v1, v0, 164);
        if (v1 == a0) {
            goto L_0028900c_2;
        }
        // 0x00289014
        charge(ctx, 1);
        lw(v0, v0, 2608);
    }
    // 0x00289020
    charge(ctx, 1);
    v0 = 0;
    // 0x00289024 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_0028900c_2:
    charge(ctx, 2);
    // 0x00289024 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00289030 sub_289030 -- 100 bytes; leaf frame (no stack)
// [btlUnitFindByUid] Finds the btlUnit with a uid on any of the four sides (0 when none).
// Arguments: a0 uid.
void sub_289030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x00289030
    enter(ctx, 5);  // entry check point + this block's cycles
    a2 = 0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = a0 & 0xFFFF;
    for (;;) {
        // 0x0028907c
        charge(ctx, 3);
        v0 = sltiu(a2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00289044
        charge(ctx, 5);
        v0 = sll(a2, 3);
        v0 = addu(a1, v0);
        lw(v0, v0, 340);
        for (;;) {
            // 0x00289070
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00289058
            charge(ctx, 3);
            lw(v1, v0, 168);
            if (v1 == a0) {
                goto L_00289064_3;
            }
            // 0x0028906c
            charge(ctx, 1);
            lw(v0, v0, 2608);
        }
        // 0x00289078
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x00289088
    charge(ctx, 1);
    v0 = 0;
    // 0x0028908c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_00289064_3:
    charge(ctx, 2);
    // 0x0028908c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002899E0 sub_2899E0 -- 368 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionResetIdleLooks] Re-aims the idle party: every combatant whose unit is placed, visible (sub_282C60), not
// busy (sub_281270), not down, without ailments, not at low HP and alive, in state 1 / 5 / 6 and not the given
// action, looks at its own position (a look-at-point packet on queue 1).
// Arguments: a0 btlAction (excluded).
void sub_2899E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002899e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kActionList);
    for (;;) {
        // 0x00289b2c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00289a08
        charge(ctx, 4);
        lhu(v1, s1, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x00289a18
            charge(ctx, 5);
            lw(s0, s1, act::kUnit);
            lw(v1, s0, unit::kFlags);
            v1 = v1 & 0x8;
            if (v1 != 0) {
                // 0x00289a2c
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x289A30u, gen::fn_sub_282C60_00282c60);
                if (v0 != 0) {
                    // 0x00289a40
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x289A44u, gen::fn_sub_281270_00281270);
                    if (v0 == 0) {
                        // 0x00289a54
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = 0x100000;
                        jal(ctx, 0x289A5Cu, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x00289a6c
                            charge(ctx, 7);
                            lw(a0, s0, unit::kDat);
                            v0 = 0xF0000;
                            a1 = v0 | 0xFFFF;
                            jal(ctx, 0x289A78u, gen::fn_datCalcChkBadStatus_00300580);
                            if (v0 == 0) {
                                // 0x00289a88
                                charge(ctx, 5);
                                lw(a0, s0, unit::kDat);
                                jal(ctx, 0x289A8Cu, gen::fn_datCalcIsLowHp_0030b5e0);
                                if (v0 == 0) {
                                    // 0x00289a9c
                                    charge(ctx, 6);
                                    lw(a0, s0, unit::kDat);
                                    a1 = 0;
                                    jal(ctx, 0x289AA4u, gen::fn_datCalcIsDead_0030b5a0);
                                    if (v0 == 0) {
                                        // 0x00289ab4
                                        charge(ctx, 4);
                                        lhu(a0, s1, act::kState);
                                        v1 = 6;
                                        if (a0 != v1) {
                                            // 0x00289ac4
                                            charge(ctx, 3);
                                            v1 = 5;
                                            if (a0 == v1) {
                                                goto L_00289ae4;
                                            }
                                            // 0x00289ad0
                                            charge(ctx, 3);
                                            v1 = 1;
                                            if (a0 == v1) {
                                                goto L_00289ae4;
                                            }
                                            // 0x00289adc
                                            charge(ctx, 2);
                                            goto L_00289b28;
                                        }
                                    L_00289ae4:
                                        charge(ctx, 2);
                                        if (s2 != s1) {
                                            // 0x00289aec
                                            charge(ctx, 15);
                                            a0 = s0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = addiu(sp, 0x40);
                                            jal(ctx, 0x289AFCu, gen::fn_sub_27F7C0_0027f7c0);
                                            a0 = s0;
                                            a1 = addiu(sp, 0x40);
                                            a2 = 0;
                                            jal(ctx, 0x289B10u, gen::fn_sub_288360_00288360);
                                            a0 = v0;
                                            a1 = 1;
                                            jal(ctx, 0x289B20u, gen::fn_sub_27ED20_0027ed20);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    L_00289b28:
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x00289b34
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00289F40 sub_289F40 -- 428 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionNeedsApproach] Whether the action's attacker runs up to its target: not for multi-target commands
// (sub_2BFF60); physical skills unless an enemy whose model row says ranged (+34 == 1); HP skills whose EFFECT row
// has bit 0, again unless ranged (+38).
// Arguments: a0 btlAction.
void sub_289F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00289f40
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lhu(s2, a0, act::kCmdSkill);
    a1 = 0;
    a2 = s2;
    a3 = 0;
    jal(ctx, 0x289F6Cu, gen::fn_sub_2BFF60_002bff60);
    v1 = v0 & 0xFFFF;
    lw(a0, s3, act::kUnit);
    lw(v0, a0, unit::kDat);
    lhu(s1, v0, dat::kId);
    if (v1 == 0) {
        // 0x00289f8c
        charge(ctx, 12);
        s0 = s2 & 0xFFFF;
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x0028a018
            charge(ctx, 6);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x28A020u, gen::fn_datCalcIsHpSkill_002d6370);
            if (v0 == 0) {
                goto L_0028a0c8;
            }
            // 0x0028a030
            charge(ctx, 9);
            lw(v1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
            v0 = sll(s0, 3);
            v0 = subu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lhu(v0, v0, 2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x0028a060
                charge(ctx, 5);
                lw(v0, s3, act::kUnit);
                lbu(v0, v0, unit::kSide);
                a1 = 1;
                if (v0 != a1) {
                    // 0x0028a074
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x0028a07c
                        charge(ctx, 2);
                    }
                    goto L_0028a0bc;
                }
                // 0x0028a084
                charge(ctx, 11);
                lw(a0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
                v1 = s1 & 0xFFFF;
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(v0, a0);
                lh(v0, v0, 38);
                if (v0 != a1) {
                L_0028a0bc:
                    charge(ctx, 3);
                    v0 = 1;
                } else {
                    // 0x0028a0b0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x0028a054
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x00289fbc
            charge(ctx, 4);
            lbu(v0, a0, unit::kSide);
            a1 = 1;
            if (v0 != a1) {
                // 0x00289fcc
                charge(ctx, 2);
                goto L_0028a00c;
            }
            // 0x00289fd4
            charge(ctx, 11);
            lw(a0, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
            v1 = s1 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            lh(v0, v0, 34);
            if (v0 != a1) {
            L_0028a00c:
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x0028a000
                charge(ctx, 3);
                v0 = 0;
            }
        }
        // 0x0028a0cc (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0028a0c8:
    charge(ctx, 1);
    v0 = 0;
    // 0x0028a0cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0028A0F0 sub_28A0F0 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionIsRanged] Whether the attacker attacks from range: enemies by their model row (+34 == 1); party members 2
// and 3 (bow, guns), sub_2D5BF0, or the hero holding weapon type 6 / 7.
// Arguments: a0 btlAction.
void sub_28A0F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028a0f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, act::kUnit);
    lw(v0, a0, unit::kDat);
    lhu(a2, v0, dat::kId);
    lbu(v1, a0, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // 0x0028a1b0
        charge(ctx, 11);
        lw(a1, gp, kGpModelEnemy);  // MODEL.TBL section 2 (232-byte rows by enemy id) 0x7CE418
        a0 = a2 & 0xFFFF;
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        v1 = sll(v1, 3);
        v1 = addu(v1, a1);
        lh(v1, v1, 34);
        if (v1 != v0) {
        L_0028a1e4:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0028a1dc
            charge(ctx, 2);
        }
    } else {
        // 0x0028a120
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x0028a128
            charge(ctx, 2);
            goto L_0028a1e4;
        }
        // 0x0028a130
        charge(ctx, 4);
        s0 = a2 & 0xFFFF;
        v0 = 2;
        if (s0 != v0) {
            // 0x0028a140
            charge(ctx, 3);
            v0 = 3;
            if (s0 == v0) {
                goto L_0028a15c;
            }
            // 0x0028a14c
            charge(ctx, 4);
            jal(ctx, 0x28A14Cu, gen::fn_sub_2D5BF0_002d5bf0);
            if (v0 != 0) {
                goto L_0028a15c;
            }
            // 0x0028a168
            charge(ctx, 8);
            lw(v0, s1, act::kUnit);
            lw(a0, v0, unit::kDat);
            jal(ctx, 0x28A170u, gen::fn_datCalcGetHeldWeaponType_00308c60);
            v1 = v0 & 0xFF;
            v0 = 1;
            if (s0 != v0) {
                goto L_0028a1e4;
            }
            // 0x0028a188
            charge(ctx, 4);
            v1 = v1 & 0xFF;
            v0 = 6;
            if (v1 != v0) {
                // 0x0028a198
                charge(ctx, 3);
                v0 = 7;
                if (v1 != v0) {
                    goto L_0028a1e4;
                }
                goto L_0028a1a4;
            }
        L_0028a1a4:
            charge(ctx, 3);
            v0 = 1;
            // 0x0028a1e8 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0028a15c:
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0028a1e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0028A200 sub_28A200 -- 476 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCheckAllOutAttack] The all-out attack check: the hero alive and free of the blocking ailments (0x100261), the
// acting unit not a dead enemy, every living enemy knocked down (0x100000); collects the other able party members
// into gBtl's all-out list. 1 when at least one enemy is down and someone joins.
// Arguments: a0 btlAction.
void sub_28A200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028a3bc: the epilogue (one copy; every path ends in it)
    auto epilogue = [&] {
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // the "no all-out attack" blocks 0x28a260 / 0x28a298 / 0x28a324 / 0x28a3a0: 3 cycles each, $v0 = 0
    auto no = [&] {
        charge(ctx, 3);
        v0 = 0;
        epilogue();
    };
    // 0x0028a200
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kPlayerAction);  // s1 = the hero's action
    lw(v0, s1, act::kUnit);
    lw(a0, v0, unit::kDat);
    a1 = 0;
    jal(ctx, 0x28A230u, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 != 0) {
        no();  // 0x28a260: the hero is dead
        return;
    }
    // 0x0028a240: the hero must be free of the blocking ailments
    charge(ctx, 8);
    lw(v0, s1, act::kUnit);
    lw(a0, v0, unit::kDat);
    v0 = 0x100000;
    a1 = v0 | 0x261;  // &0x100261
    jal(ctx, 0x28A250u, gen::fn_datCalcChkBadStatus_00300580);
    if (v0 != 0) {
        no();  // 0x28a260
        return;
    }
    // 0x0028a26c: a dead enemy actor ends it
    charge(ctx, 5);
    lw(a0, s0, act::kUnit);
    lbu(v1, a0, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // 0x0028a280
        charge(ctx, 6);
        lw(a0, a0, unit::kDat);
        a1 = 0;
        jal(ctx, 0x28A288u, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {
            no();  // 0x28a298
            return;
        }
    }
    // 0x0028a2a4: empty the all-out list, then walk the actions (s3) counting the downed enemies (s2)
    charge(ctx, 7);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sh(zero, v0, gbtl::kAllOutCount);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s3, v0, gbtl::kActionList);
    for (;;) {
        // 0x0028a38c: the loop test
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0028a2c0: a combatant ...
        charge(ctx, 4);
        lhu(v0, s3, act::kFlags2);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x0028a2d0: ... in the battle (unit flag 0x8) ...
            charge(ctx, 5);
            lw(s0, s3, act::kUnit);
            lw(v0, s0, unit::kFlags);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                // 0x0028a2e4: ... and alive
                charge(ctx, 6);
                lw(a0, s0, unit::kDat);
                a1 = 0;
                jal(ctx, 0x28A2ECu, gen::fn_datCalcIsDead_0030b5a0);
                if (v0 == 0) {
                    // 0x0028a2fc
                    charge(ctx, 4);
                    lbu(v1, s0, unit::kSide);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0028a30c: every living enemy must be down
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = 0x100000;
                        jal(ctx, 0x28A314u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            no();  // 0x28a324: an enemy still stands
                            return;
                        }
                        // 0x0028a330
                        charge(ctx, 4);
                        v0 = addiu(s2, 1);
                        s2 = v0 & 0xFFFF;
                    } else {
                        // 0x0028a340: an able party member other than the hero joins
                        charge(ctx, 7);
                        lw(a0, s0, unit::kDat);
                        v0 = 0x100000;
                        a1 = v0 | 0x261;  // &0x100261
                        jal(ctx, 0x28A34Cu, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x0028a35c
                            charge(ctx, 2);
                            if (s1 != s3) {
                                // 0x0028a364: kAllOutList[kAllOutCount++] = the action
                                charge(ctx, 9);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lhu(v0, v1, gbtl::kAllOutCount);
                                v0 = sll(v0, 2);
                                v0 = addu(v1, v0);
                                sw(s3, v0, gbtl::kAllOutList);
                                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lhu(v0, v1, gbtl::kAllOutCount);
                                v0 = addiu(v0, 1);
                                sh(v0, v1, gbtl::kAllOutCount);
                            }
                        }
                    }
                }
            }
        }
        // 0x0028a388: the next action
        charge(ctx, 1);
        lw(s3, s3, act::kNext);
    }
    // 0x0028a394: 1 when an enemy is down and someone joined
    charge(ctx, 3);
    v0 = s2 & 0xFFFF;
    if (v0 != 0) {
        // 0x0028a3ac
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v0, v0, gbtl::kAllOutCount);
        v0 = slti(v0, 1);
        v0 = v0 ^ 0x1;
        epilogue();
    } else {
        no();  // 0x28a3a0
    }
}

// 0x0028A3E0 sub_28A3E0 -- 348 bytes; leaf frame (no stack)
// [btlActionHasOneMore] Whether a hit knocked a target down ("one more"): enemy attacker -> a result's flag +250 bit
// 2; party attacker -> a result's status word +232 bit 0x100000, over every target and result.
// Arguments: a0 btlAction.
void sub_28A3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // the two endings, each followed by the epilogue block 0x28a534 (2 cycles)
    auto yes = [&] {  // 0x28a45c / 0x28a4f4
        charge(ctx, 3);
        v0 = 1;
        charge(ctx, 2);
    };
    auto no = [&] {  // 0x28a530
        charge(ctx, 1);
        v0 = 0;
        charge(ctx, 2);
    };
    // 0x0028a3e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    if (v1 != v0) {
        // 0x0028a3f4
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x0028a3fc: neither side: no
            charge(ctx, 2);
            no();
            return;
        }
        // 0x0028a404: a party attacker -- any target's result status word (+232) with 0x100000 (knocked down)
        charge(ctx, 5);
        t2 = 0;
        lhu(t0, a0, act::kTargetCount);
        v1 = 0x100000;
        for (;;) {
            // 0x0028a488: over the targets (t2)
            charge(ctx, 4);
            v0 = t2 & 0xFFFF;
            v0 = slt(v0, t0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0028a418: the target action a3, its result count (+200)
            charge(ctx, 8);
            v0 = t2 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(a0, v0);
            lw(a3, v0, act::kTargets);
            lbu(a2, a3, 200);
            t1 = 0;
            for (;;) {
                // 0x0028a470: over its 28-byte results (t1)
                charge(ctx, 4);
                v0 = t1 & 0xFFFF;
                v0 = slt(v0, a2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0028a438
                charge(ctx, 9);
                a1 = t1 & 0xFFFF;
                v0 = sll(a1, 3);
                v0 = subu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(a3, v0);
                lw(v0, v0, 232);
                v0 = v0 & v1;
                if (v0 != 0) {
                    yes();
                    return;
                }
                // 0x0028a468
                charge(ctx, 2);
                v0 = addiu(t1, 1);
                t1 = v0 & 0xFFFF;
            }
            // 0x0028a480
            charge(ctx, 2);
            v0 = addiu(t2, 1);
            t2 = v0 & 0xFFFF;
        }
        // 0x0028a498
        charge(ctx, 2);
        no();
        return;
    }
    // 0x0028a4a0: an enemy attacker -- any target's result flags (+250) with bit 2
    charge(ctx, 4);
    t1 = 0;
    lhu(a3, a0, act::kTargetCount);
    for (;;) {
        // 0x0028a520: over the targets (t1)
        charge(ctx, 4);
        v0 = t1 & 0xFFFF;
        v0 = slt(v0, a3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0028a4b0
        charge(ctx, 8);
        v0 = t1 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(a0, v0);
        lw(a2, v0, act::kTargets);
        lbu(a1, a2, 200);
        t0 = 0;
        for (;;) {
            // 0x0028a508: over its results (t0)
            charge(ctx, 4);
            v0 = t0 & 0xFFFF;
            v0 = slt(v0, a1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0028a4d0
            charge(ctx, 9);
            v1 = t0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(a2, v0);
            lhu(v0, v0, 250);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                yes();
                return;
            }
            // 0x0028a500
            charge(ctx, 2);
            v0 = addiu(t0, 1);
            t0 = v0 & 0xFFFF;
        }
        // 0x0028a518
        charge(ctx, 2);
        v0 = addiu(t1, 1);
        t1 = v0 & 0xFFFF;
    }
    no();
}

// 0x0028A540 sub_28A540 -- 576 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionGetAttackMotions] The four motion ids of an attack: defaults {0, 1, 7, 9}; physical skills of party
// member 3 / sub_2D5BF0 units by the weapon class sub_3093A0 (1 -> 14.., 2 -> 15.., 3 -> 16..); other physical skills
// by element (slash / fire 2.., pierce / wind 4..).
// Arguments: a0 btlAction, a1 skill, a2..a5 u16* out.
void sub_28A540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028a540
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
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
    sh(zero, a2, 0);
    v1 = 1;
    sh(v1, a3, 0);
    v1 = 7;
    sh(v1, t0, 0);
    v1 = 9;
    sh(v1, t1, 0);
    a1 = s5 & 0xFFFF;
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    v1 = sll(v1, 1);
    v1 = addu(v1, a1);
    a1 = sll(v1, 2);
    lw(v1, gp, kGpSkillTbl);  // gBtlSkillTbl
    v1 = addu(v1, a1);
    lbu(v1, v1, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        // 0x0028a5c0
        charge(ctx, 4);
        lw(s0, a0, act::kUnit);
        lbu(v0, s0, unit::kSide);
        if (v0 == 0) {
            // 0x0028a5d0
            charge(ctx, 5);
            lw(v0, s0, unit::kDat);
            lhu(v1, v0, dat::kId);
            v0 = 3;
            if (v1 != v0) {
                // 0x0028a5e4
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x28A5E8u, gen::fn_sub_2D5BF0_002d5bf0);
                if (v0 == 0) {
                    goto L_0028a6ac;
                }
                goto L_0028a5f8;
            }
        L_0028a5f8:
            charge(ctx, 7);
            lw(a0, s0, unit::kDat);
            jal(ctx, 0x28A5FCu, gen::fn_sub_3093A0_003093a0);
            a0 = v0 & 0xFF;
            v1 = 1;
            if (a0 != v1) {
                // 0x0028a614
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x0028a65c
                    charge(ctx, 10);
                    v1 = 16;
                    sh(v1, s4, 0);
                    v1 = 19;
                    sh(v1, s3, 0);
                    v1 = 22;
                    sh(v1, s2, 0);
                    v1 = 25;
                    sh(v1, s1, 0);
                } else {
                    // 0x0028a620
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x0028a62c
                        charge(ctx, 2);
                        goto L_0028a684;
                    }
                    // 0x0028a634
                    charge(ctx, 10);
                    v1 = 15;
                    sh(v1, s4, 0);
                    v1 = 18;
                    sh(v1, s3, 0);
                    v1 = 21;
                    sh(v1, s2, 0);
                    v1 = 24;
                    sh(v1, s1, 0);
                }
                goto L_0028a6a4;
            }
        L_0028a684:
            charge(ctx, 8);
            v1 = 14;
            sh(v1, s4, 0);
            v1 = 17;
            sh(v1, s3, 0);
            v1 = 20;
            sh(v1, s2, 0);
            v1 = 23;
            sh(v1, s1, 0);
        L_0028a6a4:
            charge(ctx, 2);
            // 0x0028a758 (the shared epilogue, written out on this path)
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
    L_0028a6ac:
        charge(ctx, 9);
        lw(a0, s0, 2604);
        a1 = s5;
        jal(ctx, 0x28A6B4u, gen::fn_datCalcGetSkillElement_003082f0);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        at = sltiu(v1, 7);
        if (at != 0) {
            // 0x0028a6d0
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 31552);  // &0x7B7B40
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x28A6ECu:  // table[0, 3]
                // 0x0028a6ec
                charge(ctx, 10);
                v1 = 2;
                sh(v1, s4, 0);
                v1 = 3;
                sh(v1, s3, 0);
                v1 = 6;
                sh(v1, s2, 0);
                v1 = 8;
                sh(v1, s1, 0);
                break;
            case 0x28A714u:  // table[2, 6]
                // 0x0028a714
                charge(ctx, 10);
                v1 = 4;
                sh(v1, s4, 0);
                v1 = 5;
                sh(v1, s3, 0);
                v1 = 7;
                sh(v1, s2, 0);
                v1 = 9;
                sh(v1, s1, 0);
                break;
            case 0x28A73Cu:  // table[1, 4, 5]
            L_0028a73c:
                charge(ctx, 7);
                sh(zero, s4, 0);
                v1 = 1;
                sh(v1, s3, 0);
                v1 = 7;
                sh(v1, s2, 0);
                v1 = 9;
                sh(v1, s1, 0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            // 0x0028a758 (the shared epilogue, written out on this path)
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
        goto L_0028a73c;
    }
    // 0x0028a758 (the shared epilogue, written out on this path)
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

// 0x0028A780 sub_28A780 -- 516 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionFlushFxRequests] Flushes gBtl's pending effect requests (kFxRequest, when kFlags 0x400000): queues, owned
// by the action, the look reset (0x20), camera 3 / 4095 (0x02), a stop-looking packet per living combatant (0x01),
// the effect packets of 0x10 / 0x08 and the camera 31 (0x04); then clears the request.
// Arguments: a0 btlAction.
void sub_28A780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028a780
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, a1, gbtl::kFlags);
    v1 = 0x400000;
    v1 = a0 & v1;
    if (v1 != 0) {
        // 0x0028a7ac
        charge(ctx, 4);
        lhu(v1, a1, gbtl::kFxRequest);
        v1 = v1 & 0x20;
        if (v1 != 0) {
            // 0x0028a7bc
            charge(ctx, 10);
            a0 = 0;
            a1 = 3;
            jal(ctx, 0x28A7C4u, gen::fn_sub_288950_00288950);
            a0 = v0;
            ld(v1, s1, act::kUid);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x28A7DCu, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028a7e4
        charge(ctx, 5);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, v1, gbtl::kFxRequest);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            // 0x0028a7f8
            charge(ctx, 10);
            a0 = 3;
            a1 = 4095;
            jal(ctx, 0x28A800u, gen::fn_sub_2B8D60_002b8d60);
            a0 = v0;
            ld(v1, s1, act::kUid);
            sd(v1, v0, 96);
            a1 = 0;
            jal(ctx, 0x28A818u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028a820
        charge(ctx, 5);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, a0, gbtl::kFxRequest);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x0028a834
            charge(ctx, 3);
            lw(s0, a0, gbtl::kActionList);
            for (;;) {
                // 0x0028a898
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0028a840
                charge(ctx, 4);
                lhu(v1, s0, act::kFlags2);
                v1 = v1 & 0x1;
                if (v1 != 0) {
                    // 0x0028a850
                    charge(ctx, 7);
                    lw(v0, s0, act::kUnit);
                    lw(a0, v0, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x28A85Cu, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x0028a86c
                        charge(ctx, 10);
                        lw(a0, s0, act::kUnit);
                        a1 = 0;
                        jal(ctx, 0x28A874u, gen::fn_sub_2843E0_002843e0);
                        a0 = v0;
                        ld(v1, s1, act::kUid);
                        sd(v1, v0, 96);
                        a1 = 1;
                        jal(ctx, 0x28A88Cu, gen::fn_sub_27ED20_0027ed20);
                    }
                }
                // 0x0028a894
                charge(ctx, 1);
                lw(s0, s0, act::kNext);
            }
        }
        // 0x0028a8a0
        charge(ctx, 5);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, v1, gbtl::kFxRequest);
        v1 = v1 & 0x10;
        if (v1 != 0) {
            // 0x0028a8b4
            charge(ctx, 9);
            a0 = 0;
            jal(ctx, 0x28A8B8u, gen::fn_sub_2A1DB0_002a1db0);
            a0 = v0;
            ld(v1, s1, act::kUid);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x28A8D0u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028a8d8
        charge(ctx, 5);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, v1, gbtl::kFxRequest);
        v1 = v1 & 0x8;
        if (v1 != 0) {
            // 0x0028a8ec
            charge(ctx, 9);
            a0 = 8;
            jal(ctx, 0x28A8F0u, gen::fn_sub_2BC7E0_002bc7e0);
            a0 = v0;
            ld(v1, s1, act::kUid);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x28A908u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028a910
        charge(ctx, 5);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v1, v1, gbtl::kFxRequest);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0028a924
            charge(ctx, 10);
            a0 = s1;
            a1 = 31;
            jal(ctx, 0x28A92Cu, gen::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            ld(v1, s1, act::kUid);
            sd(v1, v0, 96);
            a1 = 0;
            jal(ctx, 0x28A944u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028a94c
        charge(ctx, 8);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        sh(zero, v1, gbtl::kFxRequest);
        lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, a1, gbtl::kFlags);
        v1 = lui(0xFFBF);
        v1 = v1 | 0xFFFF;
        v1 = a0 & v1;
        sw(v1, a1, gbtl::kFlags);
    }
    // 0x0028a96c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0028BA50 sub_28BA50 -- 584 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionInitStateChangeFormation] btlAction state CHANGE FORMATION, init: flushes the requests, queues the
// formation camera, the opening line, a walk for every able party unit, the enemy reactions (a death motion or a look
// at the actor) and camera 35, all chained to the camera packet.
// Arguments: a0 btlAction.
void sub_28BA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0028ba50
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x28BA68u, gen::fn_sub_28A780_0028a780);
    a0 = 1;
    jal(ctx, 0x28BA74u, gen::fn_sub_2B8F40_002b8f40);
    s1 = v0;
    ld(v1, s2, act::kUid);
    sd(v1, v0, 96);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x28BA90u, gen::fn_sub_27ED20_0027ed20);
    lbu(v0, s2, act::kOneMore);
    if (v0 == 0) {
        // 0x0028baa4
        charge(ctx, 11);
        a0 = s2;
        a1 = 23;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x28BAB8u, gen::fn_sub_2E2BE0_002e2be0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x28BAC8u, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x0028bad0
    charge(ctx, 4);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v0, gbtl::kUnitTail0);
    for (;;) {
        // 0x0028bb58
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0028bae0
        charge(ctx, 7);
        lw(a0, s0, unit::kDat);
        v0 = 0x180000;
        a1 = v0 | 0x271;  // &0x180271
        jal(ctx, 0x28BAECu, gen::fn_datCalcChkBadStatus_00300580);
        if (v0 == 0) {
            // 0x0028bafc
            charge(ctx, 6);
            lw(a0, s0, unit::kDat);
            a1 = 0;
            jal(ctx, 0x28BB04u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                // 0x0028bb14
                charge(ctx, 16);
                a0 = s0;
                a1 = 0;
                lwc1(f12, gp, kGpF07);  // f32 0.7: an argument in sub_28BA50 0x7CADD0
                a2 = 24;
                jal(ctx, 0x28BB24u, gen::fn_sub_2819D0_002819d0);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, 88);
                sd(v1, v0, 8);
                ld(v1, s2, act::kUid);
                sd(v1, v0, 96);
                a1 = 1;
                jal(ctx, 0x28BB4Cu, gen::fn_sub_27ED20_0027ed20);
            }
        }
        // 0x0028bb54
        charge(ctx, 1);
        lw(s0, s0, unit::kPrev);
    }
    // 0x0028bb60
    charge(ctx, 18);
    a0 = 2;
    a1 = 1;
    jal(ctx, 0x28BB68u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, 88);
    sd(v1, v0, 8);
    ld(v1, s2, act::kUid);
    sd(v1, v0, 96);
    a1 = 0;
    jal(ctx, 0x28BB90u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v0, 344);
    for (;;) {
        // 0x0028bc3c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0028bba8
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 0;
        jal(ctx, 0x28BBB0u, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 == 0) {
            // 0x0028bbfc
            charge(ctx, 15);
            a0 = s0;
            lw(a1, s2, act::kUnit);
            a2 = 34;
            jal(ctx, 0x28BC08u, gen::fn_sub_282650_00282650);
            a0 = v0;
            v1 = 4;
            sb(v1, v0, 0);
            ld(v1, s1, 88);
            sd(v1, v0, 8);
            ld(v1, s2, act::kUid);
            sd(v1, v0, 96);
            a1 = 0;
            jal(ctx, 0x28BC30u, gen::fn_sub_27ED20_0027ed20);
        } else {
            // 0x0028bbc0
            charge(ctx, 15);
            a0 = s0;
            jal(ctx, 0x28BBC4u, gen::fn_sub_286320_00286320);
            a0 = v0;
            v1 = 4;
            sb(v1, v0, 0);
            ld(v1, s1, 88);
            sd(v1, v0, 8);
            ld(v1, s2, act::kUid);
            sd(v1, v0, 96);
            a1 = 0;
            jal(ctx, 0x28BBECu, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x0028bc38
        charge(ctx, 1);
        lw(s0, s0, unit::kPrev);
    }
    // 0x0028bc44
    charge(ctx, 21);
    a0 = s2;
    a1 = 35;
    jal(ctx, 0x28BC4Cu, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, 88);
    sd(v1, v0, 8);
    ld(v1, s2, act::kUid);
    sd(v1, v0, 96);
    a1 = 0;
    jal(ctx, 0x28BC74u, gen::fn_sub_27ED20_0027ed20);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00297480 sub_297480 -- 592 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionInitStatePersona] btlAction state PERSONA, init: flushes the requests, summons the persona (sub_2BD780),
// the camera 26, the user's motion, the cut-in line, the persona card for party members (sub_175130 / sub_288F80),
// the summon effect, the sound and the card flash; requests the 0x04 camera at the end.
// Arguments: a0 btlAction.
void sub_297480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00297480
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x297494u, gen::fn_sub_28A780_0028a780);
    lw(a0, s1, act::kUnit);
    lhu(a1, s1, act::kCmdKind);
    jal(ctx, 0x2974A4u, gen::fn_sub_2BD780_002bd780);
    a0 = v0;
    ld(v1, s1, act::kUid);
    sd(v1, v0, 96);
    a1 = 3;
    jal(ctx, 0x2974BCu, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = 26;
    jal(ctx, 0x2974CCu, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    ld(v1, s1, act::kUid);
    sd(v1, v0, 96);
    a1 = 0;
    jal(ctx, 0x2974E4u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s1, act::kUnit);
    lbu(v0, a0, unit::kSide);
    if (v0 != 0) {
        // 0x00297528
        charge(ctx, 13);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a1 = 23;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x29753Cu, gen::fn_sub_284200_00284200);
        a0 = v0;
        ld(v1, s1, act::kUid);
        sd(v1, v0, 96);
        a1 = 1;
        jal(ctx, 0x297554u, gen::fn_sub_27ED20_0027ed20);
    } else {
        // 0x002974fc
        charge(ctx, 11);
        a1 = 6;
        jal(ctx, 0x297500u, gen::fn_sub_2843E0_002843e0);
        a0 = v0;
        ld(v1, s1, act::kUid);
        sd(v1, v0, 96);
        a1 = 1;
        jal(ctx, 0x297518u, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x0029755c
    charge(ctx, 17);
    a0 = s1;
    a1 = 25;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x297570u, gen::fn_sub_2E2BE0_002e2be0);
    a0 = v0;
    ld(v1, s1, act::kUid);
    sd(v1, v0, 96);
    a1 = 1;
    jal(ctx, 0x297588u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, s1, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002975a0
        charge(ctx, 7);
        lhu(a0, s1, 116);
        jal(ctx, 0x2975A4u, gen::fn_sub_175130_00175130);
        lhu(a1, s1, 116);
        lw(a0, s1, act::kUnit);
        jal(ctx, 0x2975B4u, gen::fn_sub_288F80_00288f80);
    }
    // 0x002975bc
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x2975C0u, gen::fn_sub_2FCF50_002fcf50);
    if (v0 == 0) {
        // 0x002975d0
        charge(ctx, 2);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, 3236);
    }
    // 0x002975d8
    charge(ctx, 35);
    lw(a1, s1, act::kUnit);
    a0 = v0;
    a2 = a1;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2975ECu, gen::fn_sub_2BAF90_002baf90);
    s0 = v0;
    v1 = 15;
    sh(v1, v0, 72);
    ld(v1, s1, act::kUid);
    sd(v1, v0, 96);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x297610u, gen::fn_sub_27ED20_0027ed20);
    a0 = 10;
    a1 = 2;
    a2 = 4;
    jal(ctx, 0x297624u, gen::fn_sub_2DD100_002dd100);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s0, 88);
    sd(v1, v0, 8);
    ld(v1, s1, act::kUid);
    sd(v1, v0, 96);
    a1 = 1;
    jal(ctx, 0x29764Cu, gen::fn_sub_27ED20_0027ed20);
    lw(v1, s1, act::kUnit);
    lbu(v1, v1, unit::kSide);
    if (v1 == 0) {
        // 0x00297664
        charge(ctx, 12);
        jal(ctx, 0x297664u, gen::fn_sub_2BDDD0_002bddd0);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, 0);
        ld(v1, s0, 88);
        sd(v1, v0, 8);
        ld(v1, s1, act::kUid);
        sd(v1, v0, 96);
        a1 = 3;
        jal(ctx, 0x29768Cu, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x00297694 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, a1, gbtl::kFlags);
    v1 = 0x400000;
    v1 = a0 | v1;
    sw(v1, a1, gbtl::kFlags);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, a0, gbtl::kFxRequest);
    v1 = v1 | 0x4;
    sh(v1, a0, gbtl::kFxRequest);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00297A50 sub_297A50 -- 12 bytes; leaf frame (no stack)
// Packet callback of the all-out attack: the action's done word (+1164).
// Arguments: a0 btlAction.
void sub_297A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00297a50
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, act::kAoaDone);
}

// 0x00298060 sub_298060 -- 1144 bytes; frame 0x90: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateStateRoundUpMes] btlAction state ROUNDUP_MES (the all-out attack), update: phase 0 queues the
// portraits of the joining members, the event, the line, the sound and the dust-cloud camera (matrix 0x7CB050); phase
// 1 counts down to the cloud cue; when the packets end, either hands the turn to the hero (state 29 through
// sub_29A380) or plays the finish, then marks the action done; a finished battle sets kFlags 0x4000 and closes the
// command task.
// Arguments: a0 btlAction.
void sub_298060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00298060
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act::kAoaPhase);
    if (v0 == 0) {
        // 0x00298080
        charge(ctx, 5);
        a0 = 3075;
        jal(ctx, 0x298084u, gen::fn_sub_27E470_0027e470);
        if (v0 == 0) {
            // 0x00298094
            charge(ctx, 5);
            a3 = 0;
            lw(a2, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a1, a2, gbtl::kAllOutCount);
            for (;;) {
                // 0x002980d4
                charge(ctx, 4);
                v0 = a3 & 0xFFFF;
                v0 = slt(v0, a1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002980a8
                charge(ctx, 11);
                a0 = a3 & 0xFFFF;
                v0 = sll(a0, 2);
                v0 = addu(a2, v0);
                lw(v0, v0, 2952);
                lw(v0, v0, 48);
                lhu(v1, v0, 164);
                v0 = sll(a0, 1);
                v0 = addu(v0, sp);
                sh(v1, v0, 120);
                v0 = addiu(a3, 1);
                a3 = v0 & 0xFFFF;
            }
            // 0x002980e4
            charge(ctx, 2);
            for (;;) {
                // 0x00298104
                charge(ctx, 4);
                v0 = a3 & 0xFFFF;
                v0 = sltiu(v0, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002980ec
                charge(ctx, 6);
                v0 = a3 & 0xFFFF;
                v0 = sll(v0, 1);
                v0 = addu(v0, sp);
                sh(zero, v0, 120);
                v0 = addiu(a3, 1);
                a3 = v0 & 0xFFFF;
            }
            // 0x00298114
            charge(ctx, 99);
            lhu(a0, sp, 0x78);
            lhu(a1, sp, 0x7A);
            lhu(a2, sp, 0x7C);
            jal(ctx, 0x298120u, gen::fn_sub_2E3B50_002e3b50);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x298130u, gen::fn_sub_27ED20_0027ed20);
            jal(ctx, 0x298138u, gen::fn_sub_2E3990_002e3990);
            a0 = v0;
            ld(v1, s0, act::kUid);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x298150u, gen::fn_sub_27ED20_0027ed20);
            lw(a0, s0, act::kAoaLeader);
            a1 = 4;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x29816Cu, gen::fn_sub_2E2BE0_002e2be0);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x29817Cu, gen::fn_sub_27ED20_0027ed20);
            a0 = 10;
            a1 = 2;
            a2 = 18;
            jal(ctx, 0x298190u, gen::fn_sub_2DD100_002dd100);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2981A0u, gen::fn_sub_27ED20_0027ed20);
            a0 = 0x290000;
            a0 = addiu(a0, 31312);  // &sub_297A50
            a1 = s0;
            jal(ctx, 0x2981B4u, gen::fn_sub_27F410_0027f410);
            s1 = v0;
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x2981C8u, gen::fn_sub_27ED20_0027ed20);
            lwc1(f0, gp, kGpAoaCamera);  // f32[12]: the all-out attack camera (3x3 rotation, translation; sub_298060) 0x7CB050
            swc1(f0, sp, 0x30);
            lwc1(f0, gp, kGpAoaCamera + 4);  // the all-out attack camera 0x7CB054
            swc1(f0, sp, 0x34);
            lwc1(f0, gp, kGpAoaCamera + 8);  // the all-out attack camera 0x7CB058
            swc1(f0, sp, 0x38);
            lwc1(f0, gp, kGpAoaCamera + 12);  // the all-out attack camera 0x7CB05C
            swc1(f0, sp, 0x40);
            lwc1(f0, gp, kGpAoaCamera + 16);  // the all-out attack camera 0x7CB060
            swc1(f0, sp, 0x44);
            lwc1(f0, gp, kGpAoaCamera + 20);  // the all-out attack camera 0x7CB064
            swc1(f0, sp, 0x48);
            lwc1(f0, gp, kGpAoaCamera + 24);  // the all-out attack camera 0x7CB068
            swc1(f0, sp, 0x50);
            lwc1(f0, gp, kGpAoaCamera + 28);  // the all-out attack camera 0x7CB06C
            swc1(f0, sp, 0x54);
            lwc1(f0, gp, kGpAoaCamera + 32);  // the all-out attack camera 0x7CB070
            swc1(f0, sp, 0x58);
            sw(zero, sp, 0x60);
            sw(zero, sp, 0x64);
            sw(zero, sp, 0x68);
            v0 = 3;
            sw(v0, sp, 0x3C);
            lwc1(f0, gp, kGpAoaCamera + 36);  // the all-out attack camera 0x7CB074
            swc1(f0, sp, 0x80);
            lwc1(f0, gp, kGpAoaCamera + 40);  // the all-out attack camera 0x7CB078
            swc1(f0, sp, 0x84);
            lwc1(f0, gp, kGpAoaCamera + 44);  // the all-out attack camera 0x7CB07C
            swc1(f0, sp, 0x88);
            lwc1(f2, sp, 0x80);
            lwc1(f1, sp, 0x84);
            lwc1(f0, sp, 0x88);
            swc1(f2, sp, 0x60);
            swc1(f1, sp, 0x64);
            swc1(f0, sp, 0x68);
            a0 = addiu(sp, 0x30);
            jal(ctx, 0x298260u, gen::fn_sub_2B9600_002b9600);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(a0, v0, gbtl::kSceneTask);
            lw(a1, s0, act::kUnit);
            a2 = 0;
            ld(a3, s1, 88);
            t0 = 0xC000;
            jal(ctx, 0x298280u, gen::fn_sub_2BB2F0_002bb2f0);
            a0 = v0;
            a1 = 2;
            jal(ctx, 0x298290u, gen::fn_sub_27ED20_0027ed20);
            v0 = 1;
            sw(v0, s0, act::kAoaPhase);
            goto L_002982a0;
        }
        // 0x002984c0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_002982a0:
    charge(ctx, 4);
    lw(v1, s0, 1160);
    v0 = 1;
    if (v1 == v0) {
        // 0x002982b0
        charge(ctx, 3);
        lh(v0, s0, 1168);
        if (v0 != 0) {
            // 0x002982e0
            charge(ctx, 2);
            if (i64(v0) > 0) {
                // 0x002982e8
                charge(ctx, 2);
                v0 = addiu(v0, -1);
                sh(v0, s0, 1168);
            }
        } else {
            // 0x002982bc
            charge(ctx, 9);
            lw(v0, s0, 1156);
            lw(v0, v0, 48);
            lhu(a0, v0, 164);
            jal(ctx, 0x2982C8u, gen::fn_sub_1FEF90_001fef90);
            v0 = si(-1);
            sh(v0, s0, 1168);
        }
    }
    // 0x002982f0
    charge(ctx, 12);
    ld(a0, s0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x298310u, gen::fn_sub_27E390_0027e390);
    if (v0 == 0) {
        // 0x00298320
        charge(ctx, 3);
        lw(v0, s0, 1164);
        if (v0 != 0) {
            // 0x002984b0
            charge(ctx, 4);
            a0 = s0;
            a1 = 30;
            jal(ctx, 0x2984B8u, gen::fn_btlActionSetState_00299d60);
        } else {
            // 0x0029832c
            charge(ctx, 4);
            jal(ctx, 0x29832Cu, gen::fn_sub_1FF100_001ff100);
            if (v0 != 0) {
                // 0x0029833c
                charge(ctx, 4);
                jal(ctx, 0x29833Cu, gen::fn_sub_1FF120_001ff120);
                if (v0 != 0) {
                    // 0x002983b0
                    charge(ctx, 24);
                    lw(a0, s0, 1156);
                    a1 = 6;
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x2983C4u, gen::fn_sub_2E2BE0_002e2be0);
                    a0 = v0;
                    a1 = 1;
                    jal(ctx, 0x2983D4u, gen::fn_sub_27ED20_0027ed20);
                    jal(ctx, 0x2983DCu, gen::fn_sub_2E3D10_002e3d10);
                    a0 = v0;
                    v1 = 10;
                    sb(v1, v0, 0);
                    v1 = 3078;
                    sh(v1, v0, 8);
                    ld(v1, s0, 0);
                    sd(v1, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x298404u, gen::fn_sub_27ED20_0027ed20);
                    s1 = 1;
                } else {
                    // 0x0029834c
                    charge(ctx, 25);
                    a0 = s0;
                    a1 = 2;
                    jal(ctx, 0x298354u, gen::fn_sub_2D7FB0_002d7fb0);
                    a0 = v0;
                    ld(v1, s0, 0);
                    sd(v1, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x29836Cu, gen::fn_sub_27ED20_0027ed20);
                    lw(v1, s0, 1156);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kPlayerAction);
                    sw(v1, v0, act::kAoaLinked);
                    v1 = 29;
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kPlayerAction);
                    sh(v1, v0, act::kResumeState);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(a0, v0, gbtl::kPlayerAction);
                    jal(ctx, 0x29839Cu, gen::fn_sub_29A380_0029a380);
                    s1 = 0;
                }
                // 0x00298410
                charge(ctx, 6);
                jal(ctx, 0x298410u, gen::fn_sub_1FF140_001ff140);
                jal(ctx, 0x298418u, gen::fn_sub_2E3A90_002e3a90);
                if (s1 != 0) {
                    // 0x00298428
                    charge(ctx, 2);
                    ld(v1, s0, 0);
                    sd(v1, v0, 96);
                }
                // 0x00298430
                charge(ctx, 22);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x298438u, gen::fn_sub_27ED20_0027ed20);
                a0 = 0;
                a1 = 1;
                jal(ctx, 0x298448u, gen::fn_sub_288950_00288950);
                a0 = v0;
                ld(v1, s0, 0);
                sd(v1, v0, 96);
                a1 = 1;
                jal(ctx, 0x298460u, gen::fn_sub_27ED20_0027ed20);
                lhu(v0, s0, 24);
                v0 = v0 & 0xFFF7;
                sh(v0, s0, 24);
                jal(ctx, 0x298474u, gen::fn_sub_2D1A70_002d1a70);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00298488
                    charge(ctx, 6);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v1, gbtl::kFlags);
                    v0 = v0 | 0x4000;
                    sw(v0, v1, gbtl::kFlags);
                    jal(ctx, 0x298498u, gen::fn_sub_1FF370_001ff370);
                }
                // 0x002984a0
                charge(ctx, 4);
                v1 = 1;
                sw(v1, s0, 1164);
            }
        }
    }
    // 0x002984c0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00299990 sub_299990 -- 260 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateStateDead] btlAction state DEAD, update: a dead enemy leaves (state 34) unless it is a boss-rule
// unit (flag 0x40); a unit that is alive again (revived) is shown, re-queued (sub_29A2C0) and returns to state 1.
// Arguments: a0 btlAction.
void sub_299990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299990
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, act::kUnit);
    lbu(a1, s0, unit::kSide);
    v1 = 1;
    if (a1 == v1) {
        // 0x00299a14
        charge(ctx, 4);
        lw(v0, s0, unit::kFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) {
            // 0x00299a38
            charge(ctx, 6);
            lw(a0, s0, unit::kDat);
            a1 = 0;
            jal(ctx, 0x299A40u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                // 0x00299a50
                charge(ctx, 11);
                lw(v1, s0, unit::kFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s0, unit::kFlags);
                a0 = s1;
                jal(ctx, 0x299A64u, gen::fn_sub_29A2C0_0029a2c0);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x299A74u, gen::fn_btlActionSetState_00299d60);
            }
        } else {
            // 0x00299a24
            charge(ctx, 5);
            a1 = 34;
            jal(ctx, 0x299A28u, gen::fn_btlActionSetState_00299d60);
        }
    } else {
        // 0x002999b8
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x002999c8
            charge(ctx, 6);
            lw(a0, s0, unit::kDat);
            a1 = 0;
            jal(ctx, 0x2999D0u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                // 0x002999e0
                charge(ctx, 13);
                lw(v1, s0, unit::kFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s0, unit::kFlags);
                a0 = s1;
                jal(ctx, 0x2999F4u, gen::fn_sub_29A2C0_0029a2c0);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x299A04u, gen::fn_btlActionSetState_00299d60);
            }
        } else {
            // 0x002999c0
            charge(ctx, 2);
        }
    }
    // 0x00299a7c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0029EA20 sub_29EA20 -- 16 bytes; leaf frame (no stack)
// &gBtl->kFadeColA.
void sub_29EA20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0029ea20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = addiu(v0, 404);
}

// 0x0029EA30 sub_29EA30 -- 16 bytes; leaf frame (no stack)
// &gBtl->kSceneVecA.
void sub_29EA30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0029ea30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = addiu(v0, 452);
}

// 0x0029EA40 sub_29EA40 -- 16 bytes; leaf frame (no stack)
// &gBtl->kFadeColC.
void sub_29EA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x0029ea40
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = addiu(v0, 500);
}

// 0x0029EA60 sub_29EA60 -- 416 bytes; frame 0x10
// [btlEffectGetFadeColours] The two fade colours of a skill's EFFECT row (+8 / +12): a word with alpha bits is used
// as is, otherwise gBtl's colour A / B converted to bytes (x 255 + 0.5).
// Arguments: a0 row, a1 / a2 u32* out.
void sub_29EA60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0029ea60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a0 & 0xFFFF;
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a3 = sll(v1, 2);
    lw(v1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = addiu(v1, 8);
    v1 = addu(v1, a3);
    lw(a0, v1, 0);
    v1 = lui(0xFF00);
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x0029eaa0
        charge(ctx, 37);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f0, a0, gbtl::kFadeColA);
        v1 = 0x437F0000;
        mtc1(v1, f3);
        v1 = 0x3F000000;
        mtc1(v1, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xC);
        lwc1(f0, a0, gbtl::kFadeColA + 4);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xD);
        lwc1(f0, a0, gbtl::kFadeColA + 8);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xE);
        lwc1(f0, a0, gbtl::kFadeColA + 12);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xF);
        lw(v1, sp, 0xC);
        sw(v1, a1, 0);
    } else {
        // 0x0029ea94
        charge(ctx, 3);
        sw(a0, a1, 0);
    }
    // 0x0029eb34
    charge(ctx, 8);
    lw(v1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = addiu(v1, 12);
    v1 = addu(v1, a3);
    lw(a0, v1, 0);
    v1 = lui(0xFF00);
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x0029eb60
        charge(ctx, 37);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f0, a0, gbtl::kFadeColB);
        v1 = 0x437F0000;
        mtc1(v1, f3);
        v1 = 0x3F000000;
        mtc1(v1, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xC);
        lwc1(f0, a0, gbtl::kFadeColB + 4);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xD);
        lwc1(f0, a0, gbtl::kFadeColB + 8);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xE);
        lwc1(f0, a0, gbtl::kFadeColB + 12);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xF);
        lw(v1, sp, 0xC);
        sw(v1, a2, 0);
    } else {
        // 0x0029eb54
        charge(ctx, 3);
        sw(a0, a2, 0);
    }
    // 0x0029ebf4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x0029EC00 sub_29EC00 -- 80 bytes; leaf frame (no stack)
// EFFECT row +4 with the alpha forced to 0xFF when it has alpha bits, else -1.
// Arguments: a0 row.
void sub_29EC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0029ec00
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = a0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v0 = addiu(v0, 4);
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    v1 = lui(0xFF00);
    v0 = a0 & v1;
    if (v0 == 0) {
        // 0x0029ec44
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x0029ec30
        charge(ctx, 5);
        v0 = dsll32(a0, 8);
        v0 = dsrl32(v0, 8);
        v0 = v0 | v1;
    }
    // 0x0029ec48 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0029EC50 sub_29EC50 -- 36 bytes; leaf frame (no stack)
// EFFECT row +24.
// Arguments: a0 row.
void sub_29EC50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0029ec50
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = a0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    lw(v0, v0, 24);
}

// 0x0029EC80 sub_29EC80 -- 416 bytes; frame 0x10
// [btlEffectGetFadeColours2] As sub_29EA60 for the row's +16 / +20 and colours C / D.
// Arguments: a0 row, a1 / a2 u32* out.
void sub_29EC80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0029ec80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a0 & 0xFFFF;
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    a3 = sll(v1, 2);
    lw(v1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = addiu(v1, 16);
    v1 = addu(v1, a3);
    lw(a0, v1, 0);
    v1 = lui(0xFF00);
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x0029ecc0
        charge(ctx, 37);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f0, a0, gbtl::kFadeColC);
        v1 = 0x437F0000;
        mtc1(v1, f3);
        v1 = 0x3F000000;
        mtc1(v1, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xC);
        lwc1(f0, a0, gbtl::kFadeColC + 4);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xD);
        lwc1(f0, a0, gbtl::kFadeColC + 8);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xE);
        lwc1(f0, a0, gbtl::kFadeColC + 12);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xF);
        lw(v1, sp, 0xC);
        sw(v1, a1, 0);
    } else {
        // 0x0029ecb4
        charge(ctx, 3);
        sw(a0, a1, 0);
    }
    // 0x0029ed54
    charge(ctx, 8);
    lw(v1, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = addiu(v1, 20);
    v1 = addu(v1, a3);
    lw(a0, v1, 0);
    v1 = lui(0xFF00);
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x0029ed80
        charge(ctx, 37);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lwc1(f0, a0, gbtl::kFadeColD);
        v1 = 0x437F0000;
        mtc1(v1, f3);
        v1 = 0x3F000000;
        mtc1(v1, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xC);
        lwc1(f0, a0, gbtl::kFadeColD + 4);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xD);
        lwc1(f0, a0, gbtl::kFadeColD + 8);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xE);
        lwc1(f0, a0, gbtl::kFadeColD + 12);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sb(v1, sp, 0xF);
        lw(v1, sp, 0xC);
        sw(v1, a2, 0);
    } else {
        // 0x0029ed74
        charge(ctx, 3);
        sw(a0, a2, 0);
    }
    // 0x0029ee14 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x0029F4B0 sub_29F4B0 -- 680 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s2 sp+0x4C
// [btlFxPktCreateFade] Creates the fade packet 1536 (104 bytes: two colours as floats x 1/255, the frame count at
// +96), update sub_29F150.
// Arguments: a0 / a1 RGBA, a2 frames.
void sub_29F4B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0029f4b0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 1536;
    a1 = 104;
    jal(ctx, 0x29F4D8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2A0000;
    v1 = addiu(v1, -3760);  // &sub_29F150
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s2, sp, 0x4C);
    lbu(a0, sp, 0x4C);
    if (i64(a0) < 0) {
        // 0x0029f514
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f500
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f530
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 0);
    lbu(a0, sp, 0x4D);
    if (i64(a0) < 0) {
        // 0x0029f55c
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f548
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f578
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 4);
    lbu(a0, sp, 0x4E);
    if (i64(a0) < 0) {
        // 0x0029f5a4
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f590
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f5c0
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 8);
    lbu(a0, sp, 0x4F);
    if (i64(a0) < 0) {
        // 0x0029f5ec
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f5d8
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f608
    charge(ctx, 7);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 12);
    sw(s1, sp, 0x4C);
    lbu(a0, sp, 0x4C);
    if (i64(a0) < 0) {
        // 0x0029f638
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f624
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f654
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 16);
    lbu(a0, sp, 0x4D);
    if (i64(a0) < 0) {
        // 0x0029f680
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f66c
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f69c
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 20);
    lbu(a0, sp, 0x4E);
    if (i64(a0) < 0) {
        // 0x0029f6c8
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f6b4
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f6e4
    charge(ctx, 6);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 24);
    lbu(a0, sp, 0x4F);
    if (i64(a0) < 0) {
        // 0x0029f710
        charge(ctx, 7);
        a1 = srl(a0, 1);
        a0 = a0 & 0x1;
        a1 = a1 | a0;
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0029f6fc
        charge(ctx, 5);
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0029f72c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lwc1(f0, gp, kGpByteToUnit);  // f32 1/255 0x7CAF08
    mul_s(f0, f0, f1);
    swc1(f0, v1, 28);
    sw(s0, v1, 96);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0029FA50 sub_29FA50 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlFxPktCreateFadeBack] Creates the fade-back packet 1537 (40 bytes, frames at +32), update sub_29F760.
// Arguments: a0 frames.
void sub_29FA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029fa50
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1537;
    a1 = 40;
    jal(ctx, 0x29FA68u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2A0000;
    v1 = addiu(v1, -2208);  // &sub_29F760
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 32);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002A5EE0 sub_2A5EE0 -- 84 bytes; frame 0x10: ra sp+0x0
// Camera hook: sub_2A54F0(a0, camera state == 29, 40, 70).
// Arguments: a0 camera.
void sub_2A5EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002a5ee0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, v0, gbtl::kCameraState);
    v0 = 29;
    if (v1 == v0) {
        // 0x002a5f04
        charge(ctx, 3);
        a1 = 1;
    } else {
        // 0x002a5efc
        charge(ctx, 2);
        // 0x002a5f10
        charge(ctx, 1);
        a1 = 0;
    }
    // 0x002a5f14
    charge(ctx, 8);
    a2 = 40;
    a3 = 70;
    jal(ctx, 0x2A5F1Cu, gen::fn_sub_2A54F0_002a54f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002AC540 sub_2AC540 -- 408 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCameraStartActionShot] Camera: picks the shot of an action (sub_2A7830 -> +272), notes whether the unit's
// camera object accepts it (sub_2FDBB0 -> +276) and runs the shot's set-up (sub_2A8150 / sub_2A95D0 / sub_2AA2B0 /
// sub_2AB330 / sub_2A79F0); state 25 disables both blends.
// Arguments: a0 camera.
void sub_2AC540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ac540
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, a0, 224);
    lw(v0, v0, 48);
    lw(s2, v0, 2560);
    s1 = 1;
    s0 = s1;
    jal(ctx, 0x2AC570u, gen::fn_sub_2A7830_002a7830);
    sh(v0, s3, 272);
    lhu(a0, s3, 228);
    v1 = 25;
    if (a0 == v1) {
        // 0x002ac58c
        charge(ctx, 2);
        s1 = 0;
        s0 = 0;
    }
    // 0x002ac594
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x002ac59c
        charge(ctx, 6);
        lw(a0, s3, 224);
        a1 = s2;
        jal(ctx, 0x2AC5A4u, gen::fn_sub_2FDBB0_002fdbb0);
        if (v0 == 0) {
            goto L_002ac5c4;
        }
        // 0x002ac5b4
        charge(ctx, 4);
        v1 = 1;
        sw(v1, s3, 276);
        goto L_002ac5c8;
    }
L_002ac5c4:
    charge(ctx, 1);
    sw(zero, s3, 276);
L_002ac5c8:
    charge(ctx, 4);
    lhu(v1, s3, 272);
    at = sltiu(v1, 7);
    if (at != 0) {
        // 0x002ac5d8
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 31824);  // &0x7B7C50
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2AC5F4u:  // table[1]
            // 0x002ac5f4
            charge(ctx, 7);
            a0 = s3;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x2AC600u, gen::fn_sub_2A8150_002a8150);
            break;
        case 0x2AC610u:  // table[2]
            // 0x002ac610
            charge(ctx, 7);
            a0 = s3;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x2AC61Cu, gen::fn_sub_2A95D0_002a95d0);
            break;
        case 0x2AC62Cu:  // table[3]
            // 0x002ac62c
            charge(ctx, 7);
            a0 = s3;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x2AC638u, gen::fn_sub_2AA2B0_002aa2b0);
            break;
        case 0x2AC648u:  // table[4]
            // 0x002ac648
            charge(ctx, 3);
            lw(v0, s3, 276);
            if (v0 != 0) {
                // 0x002ac670
                charge(ctx, 7);
                a0 = s3;
                a1 = s1;
                a2 = s0;
                jal(ctx, 0x2AC67Cu, gen::fn_sub_2A95D0_002a95d0);
            } else {
                // 0x002ac654
                charge(ctx, 7);
                a0 = s3;
                a1 = s1;
                a2 = s0;
                jal(ctx, 0x2AC660u, gen::fn_sub_2AB330_002ab330);
            }
            break;
        case 0x2AC68Cu:  // table[5]
            // 0x002ac68c
            charge(ctx, 7);
            a0 = s3;
            a1 = s1;
            a2 = s0;
            jal(ctx, 0x2AC698u, gen::fn_sub_2AA2B0_002aa2b0);
            break;
        case 0x2AC6A8u:  // table[6]
            // 0x002ac6a8
            charge(ctx, 4);
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x2AC6B0u, gen::fn_sub_2A79F0_002a79f0);
            break;
        case 0x2AC6B8u:  // table[0]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002ac6b8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002AF850 sub_2AF850 -- 272 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlCameraFollowTarget] Camera: follows the AI target record's current candidate (sub_2C0880): when it changed,
// re-aims with or without a blend by the camera state.
// Arguments: a0 camera.
void sub_2AF850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002af850
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 224);
    a0 = addiu(v0, 136);
    jal(ctx, 0x2AF868u, gen::fn_sub_2C0880_002c0880);
    if (v0 != 0) {
        // 0x002af878
        charge(ctx, 3);
        lw(a0, s0, 256);
        if (a0 == v0) {
            goto L_002af898;
        }
        // 0x002af884
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x002af88c
            charge(ctx, 3);
            lhu(v1, s0, 262);
            if (v1 == 0) {
                goto L_002af8a0;
            }
            goto L_002af898;
        }
    L_002af8a0:
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x002af900
            charge(ctx, 1);
            a1 = 0;
        } else {
            // 0x002af8a8
            charge(ctx, 5);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a0, v1, gbtl::kCameraState);
            v1 = 35;
            if (a0 != v1) {
                // 0x002af8bc
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_002af8e8;
                }
                // 0x002af8c8
                charge(ctx, 3);
                v1 = 34;
                if (a0 == v1) {
                    goto L_002af8e8;
                }
                // 0x002af8d4
                charge(ctx, 3);
                v1 = 28;
                if (a0 == v1) {
                    goto L_002af8e8;
                }
                // 0x002af8e0
                charge(ctx, 2);
                // 0x002af8f4
                charge(ctx, 3);
                a1 = 1;
                goto L_002af904;
            }
        L_002af8e8:
            charge(ctx, 3);
            a1 = 0;
        }
    L_002af904:
        charge(ctx, 5);
        sw(v0, s0, 256);
        lhu(v1, s0, 260);
        v0 = 1;
        if (v1 != v0) {
            // 0x002af918
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x002af924
                charge(ctx, 2);
                goto L_002af940;
            }
            // 0x002af92c
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x2AF930u, gen::fn_sub_2AEF80_002aef80);
            // 0x002af94c (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_002af940:
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x2AF944u, gen::fn_sub_2AE740_002ae740);
        // 0x002af94c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_002af898:
    charge(ctx, 2);
    // 0x002af94c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002B8F90 sub_2B8F90 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlFxHandleCreate] Allocates a 1,592-byte effect handle (RwMalloc, hint 0x40000): flags 8 for mode 2 else 0,
// reference count 1.
// Arguments: a0 mode.
void sub_2B8F90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002b8f90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1592;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x2B8FB0u, v0.u());
    a0 = s0 & 0xFFFF;
    v1 = 2;
    if (a0 == v1) {
        // 0x002b8ffc
        charge(ctx, 2);
        v1 = 8;
        sh(v1, v0, 1584);
    } else {
        // 0x002b8fc8
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x002b8ff0
            charge(ctx, 3);
            sh(zero, v0, 1584);
        } else {
            // 0x002b8fd4
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x002b8fe4
                charge(ctx, 3);
                sh(zero, v0, 1584);
            } else {
                // 0x002b8fdc
                charge(ctx, 2);
            }
        }
    }
    // 0x002b9004 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v1 = 1;
    sh(v1, v0, 1586);
    sw(zero, v0, 1588);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002B9030 sub_2B9030 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlFxHandleRelease] Drops a reference of an effect handle: at 1 with flag 8 stops it (sub_2B9220); at 0 frees it
// (stops it first with flag 2).
// Arguments: a0 handle.
void sub_2B9030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002b9030
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v1, a0, 1586);
    v1 = addiu(v1, -1);
    sh(v1, a0, 1586);
    lhu(v1, a0, 1584);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        // 0x002b905c
        charge(ctx, 4);
        lhu(a1, s0, 1586);
        v1 = 1;
        if (a1 == v1) {
            // 0x002b906c
            charge(ctx, 2);
            jal(ctx, 0x2B906Cu, gen::fn_sub_2B9220_002b9220);
        }
    }
    // 0x002b9074
    charge(ctx, 3);
    lhu(v1, s0, 1586);
    if (v1 == 0) {
        // 0x002b9080
        charge(ctx, 4);
        lhu(v0, s0, 1584);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002b9090
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x2B9094u, gen::fn_sub_2B9220_002b9220);
        }
        // 0x002b909c
        charge(ctx, 5);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x2B90A8u, v0.u());
    }
    // 0x002b90b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BB8F0 sub_2BB8F0 -- 204 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxObjFreeArray] Frees an array of 48 effect objects: each stopped (sub_2BB580), unlinked from gBtl's
// effect-object list and freed; then the array.
// Arguments: a0 u32[48]*.
void sub_2BB8F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bb8f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = 0;
    for (;;) {
        // 0x002bb980
        charge(ctx, 3);
        v0 = sltiu(s1, 48);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002bb914
        charge(ctx, 9);
        v0 = sll(s1, 2);
        v0 = addu(s2, v0);
        lw(s0, v0, 0);
        a0 = s0;
        jal(ctx, 0x2BB924u, gen::fn_sub_2BB580_002bb580);
        lw(v1, s0, 32);
        if (v1 != 0) {
            // 0x002bb938
            charge(ctx, 2);
            lw(v0, s0, 28);
            sw(v0, v1, 28);
        }
        // 0x002bb940
        charge(ctx, 3);
        lw(v1, s0, 28);
        if (v1 == 0) {
            // 0x002bb95c
            charge(ctx, 3);
            lw(v1, s0, 32);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(v1, v0, gbtl::kFxObjList);
        } else {
            // 0x002bb94c
            charge(ctx, 4);
            lw(v0, s0, 32);
            sw(v0, v1, 32);
        }
        // 0x002bb968
        charge(ctx, 6);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x2BB974u, v0.u());
        s1 = addiu(s1, 1);
    }
    // 0x002bb98c
    charge(ctx, 12);
    a0 = s2;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x2BB998u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002BBD00 sub_2BBD00 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxObjFreeGroup] Frees an effect object group: the object (+8, unlinked and freed), its handle (+12, released),
// then the group.
// Arguments: a0 group.
void sub_2BBD00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bbd00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 8);
    a0 = s0;
    jal(ctx, 0x2BBD20u, gen::fn_sub_2BB580_002bb580);
    lw(v1, s0, 32);
    if (v1 != 0) {
        // 0x002bbd34
        charge(ctx, 2);
        lw(v0, s0, 28);
        sw(v0, v1, 28);
    }
    // 0x002bbd3c
    charge(ctx, 3);
    lw(v1, s0, 28);
    if (v1 == 0) {
        // 0x002bbd58
        charge(ctx, 3);
        lw(v1, s0, 32);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v1, v0, gbtl::kFxObjList);
    } else {
        // 0x002bbd48
        charge(ctx, 4);
        lw(v0, s0, 32);
        sw(v0, v1, 32);
    }
    // 0x002bbd64
    charge(ctx, 9);
    s2 = 0x960000;
    s2 = addiu(s2, 380);  // &0x96017C
    a0 = s0;
    lw(v0, s2, 0);  // 0x96017C
    jalr(ctx, 0x2BBD74u, v0.u());
    lw(a0, s1, 12);
    if (a0 != 0) {
        // 0x002bbd88
        charge(ctx, 3);
        jal(ctx, 0x2BBD88u, gen::fn_sub_2B9030_002b9030);
        sw(zero, s1, 12);
    }
    // 0x002bbd94
    charge(ctx, 11);
    a0 = s1;
    lw(v0, s2, 0);
    jalr(ctx, 0x2BBD9Cu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002BD4F0 sub_2BD4F0 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlFxPktUpdateSkillName] Update of the skill-name banner packet: with names shown (kFlags 0x200) shows the skill's
// name on the first frame (sub_1FE9B0, MSG.TBL section 1) and runs 45 frames.
// Arguments: a0 packet data {.., u16 skill +4, u32 frames +8}.
void sub_2BD4F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bd4f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kFlags);
    v0 = v0 & 0x200;
    if (v0 != 0) {
        // 0x002bd520
        charge(ctx, 3);
        lw(v0, s0, 8);
        if (v0 == 0) {
            // 0x002bd52c
            charge(ctx, 9);
            lhu(v1, s0, 4);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v1 = addu(v0, v1);
            lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
            a0 = addu(v0, v1);
            jal(ctx, 0x2BD548u, gen::fn_sub_1FE9B0_001fe9b0);
        }
        // 0x002bd550
        charge(ctx, 6);
        lw(v0, s0, 8);
        v0 = addiu(v0, 1);
        sw(v0, s0, 8);
        v0 = sltiu(v0, 45);
        if (v0 != 0) {
            // 0x002bd574
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x002bd568
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002bd514
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002bd578 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BD8E0 sub_2BD8E0 -- 704 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFxPktUpdateResultPopup] Update of the result pop-up packet: builds the pop-up flags (miss / evade / weak /
// resist / critical / down / support kinds from the result words and the skill's element and class) and calls
// sub_1FE650 once; then waits for the panel (sub_1FEB50) while packets may start.
// Arguments: a0 packet data.
void sub_2BD8E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bd8e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, a0, 48);
    if (v0 != 0) {
        // 0x002bd908
        charge(ctx, 5);
        s0 = 0;
        lhu(a0, s3, 40);
        v0 = a0 & 0x4;
        if (v0 == 0) {
            // 0x002bd91c
            charge(ctx, 3);
            lw(v0, s3, 8);
            if (v0 == 0) {
                // 0x002bd928
                charge(ctx, 3);
                lw(v0, s3, 12);
                if (v0 != 0) {
                    goto L_002bd964;
                }
                // 0x002bd934
                charge(ctx, 3);
                lw(v0, s3, 16);
                if (v0 != 0) {
                    goto L_002bd964;
                }
                // 0x002bd940
                charge(ctx, 3);
                lw(v0, s3, 20);
                if (v0 != 0) {
                    goto L_002bd964;
                }
                // 0x002bd94c
                charge(ctx, 3);
                lw(v0, s3, 24);
                if (v0 != 0) {
                    goto L_002bd964;
                }
                goto L_002bd958;
            }
        L_002bd964:
            charge(ctx, 1);
            a1 = 0;
            goto L_002bd968;
        }
    L_002bd958:
        charge(ctx, 3);
        a1 = 1;
    L_002bd968:
        charge(ctx, 3);
        lw(s2, s3, 8);
        if (s2 == 0) {
            // 0x002bd980
            charge(ctx, 1);
            s2 = 0;
        } else {
            // 0x002bd974
            charge(ctx, 3);
            s0 = s0 | 0x10;
        }
        // 0x002bd984
        charge(ctx, 3);
        lw(s1, s3, 12);
        if (s1 == 0) {
            // 0x002bd99c
            charge(ctx, 1);
            s1 = 0;
        } else {
            // 0x002bd990
            charge(ctx, 3);
            s0 = s0 | 0x20;
        }
        // 0x002bd9a0
        charge(ctx, 5);
        lhu(v1, s3, 46);
        lhu(v0, s3, 44);
        v0 = addiu(v0, 1);
        if (v1 == v0) {
            // 0x002bd9b4
            charge(ctx, 4);
            lhu(v1, s3, 42);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x002bd9c4
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x002bd9cc
                    charge(ctx, 1);
                    s0 = s0 | 0x1;
                }
            }
            // 0x002bd9d0
            charge(ctx, 3);
            v0 = v1 & 0x4;
            if (v0 != 0) {
                // 0x002bd9dc
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x002bd9e4
                    charge(ctx, 1);
                    s0 = s0 | 0x2;
                }
            }
            // 0x002bd9e8
            charge(ctx, 3);
            v0 = a0 & 0x100;
            if (v0 == 0) {
                // 0x002bda68
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x002bda70
                    charge(ctx, 1);
                    s0 = s0 | 0x4;
                }
            } else {
                // 0x002bd9f4
                charge(ctx, 4);
                lw(v1, s3, 36);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x002bda04
                    charge(ctx, 4);
                    lw(v0, s3, 0);
                    lw(a0, v0, 2604);
                    if (a0 == 0) {
                        goto L_002bda38;
                    }
                    // 0x002bda14
                    charge(ctx, 9);
                    a1 = v1 & 0xFFFF;
                    jal(ctx, 0x2BDA18u, gen::fn_datCalcGetSkillElement_003082f0);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x2BDA28u, gen::fn_datCalcGetElementBit_003080c0);
                    goto L_002bda3c;
                }
            L_002bda38:
                charge(ctx, 1);
                v0 = 0;
            L_002bda3c:
                charge(ctx, 5);
                v1 = 0x10000;
                v1 = v1 | 0xF800;
                v0 = v0 & v1;
                if (v0 != 0) {
                    // 0x002bda5c
                    charge(ctx, 3);
                    s0 = s0 | 0x4;
                } else {
                    // 0x002bda50
                    charge(ctx, 3);
                    s0 = s0 | 0x8;
                }
            }
            // 0x002bda74
            charge(ctx, 5);
            lw(v1, s3, 16);
            v0 = 0x100000;
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x002bda88
                charge(ctx, 1);
                s0 = s0 | 0x40;
            }
        }
        // 0x002bda8c
        charge(ctx, 3);
        lw(v1, s3, 36);
        if (i64(v1) >= 0) {
            // 0x002bda98
            charge(ctx, 11);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            a1 = sll(v0, 2);
            lw(a0, gp, kGpSkillTbl);  // gBtlSkillTbl
            v0 = addu(a1, a0);
            lbu(v1, v0, 8);
            v0 = 2;
            if (v1 != v0) {
                // 0x002bdac4
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_002bdad8;
                }
                // 0x002bdad0
                charge(ctx, 2);
                goto L_002bdadc;
            }
        L_002bdad8:
            charge(ctx, 1);
            s0 = s0 | 0x80;
        L_002bdadc:
            charge(ctx, 5);
            v0 = addu(a0, a1);
            lbu(v0, v0, 0);
            v0 = v0 & 0x20;
            if (v0 != 0) {
                // 0x002bdaf0
                charge(ctx, 2);
                v0 = si(-5);
                s0 = s0 & v0;
            }
        }
        // 0x002bdaf8
        charge(ctx, 19);
        sw(s2, sp, 0x50);
        sw(s1, sp, 0x54);
        sw(s0, sp, 0x58);
        lw(v0, s3, 0);
        lw(v0, v0, 168);
        sw(v0, sp, 0x5C);
        lw(v0, s3, 4);
        lw(v0, v0, 168);
        sw(v0, sp, 0x60);
        lhu(v0, s3, 44);
        sw(v0, sp, 0x68);
        lhu(v0, s3, 46);
        sw(v0, sp, 0x64);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x2BDB30u, gen::fn_sub_1FE650_001fe650);
        sw(zero, s3, 48);
        goto L_002bdb7c;
    }
    // 0x002bdb44
    charge(ctx, 6);
    lw(v0, s3, 4);
    lw(a0, v0, 168);
    jal(ctx, 0x2BDB4Cu, gen::fn_sub_1FEB50_001feb50);
    if (v0 != 0) {
        // 0x002bdb5c
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kFlags);
        v0 = v0 & 0x800;
        if (v0 == 0) {
            goto L_002bdb70;
        }
    L_002bdb7c:
        charge(ctx, 1);
        v0 = 0;
        // 0x002bdb80 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_002bdb70:
    charge(ctx, 3);
    v0 = 1;
    // 0x002bdb80 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002BF370 sub_2BF370 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlCommandCalcTaskDestroy] Destroy callback of the "battle_command_calc" task: closes the panel; a finished battle
// sets kFlags 0x4000 and closes the command task; frees the work and clears gBtl->kCmdCalcTask.
// Arguments: a0 task.
void sub_2BF370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf370
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2BF380u, gen::fn_sub_1FDDA0_001fdda0);
    jal(ctx, 0x2BF388u, gen::fn_sub_2D1A70_002d1a70);
    v1 = 1;
    if (v0 == v1) {
        // 0x002bf39c
        charge(ctx, 6);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl::kFlags);
        v0 = v0 | 0x4000;
        sw(v0, v1, gbtl::kFlags);
        jal(ctx, 0x2BF3ACu, gen::fn_sub_1FF370_001ff370);
    }
    // 0x002bf3b4
    charge(ctx, 15);
    a0 = s0;
    jal(ctx, 0x2BF3B8u, gen::fn_kwlnTaskGetWorkData_00195540);
    a0 = v0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x2BF3CCu, v0.u());
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(zero, v1, gbtl::kCmdCalcTask);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C0880 sub_2C0880 -- 24 bytes; leaf frame (no stack)
// [btlAITargetGetCurrent] The current candidate of an AI target record (record[record +58]).
// Arguments: a0 record.
void sub_2C0880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c0880
    enter(ctx, 6);  // entry check point + this block's cycles
    lhu(v0, a0, airec::kIndex);
    v0 = sll(v0, 2);
    v0 = addu(a0, v0);
    lw(v0, v0, 0);
}

// 0x002C08A0 sub_2C08A0 -- 16 bytes; leaf frame (no stack)
// [btlAITargetSetUid] Stores the chosen uid (u64) in an AI target record (+48).
// Arguments: a0 record, a1 u64*.
void sub_2C08A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c08a0
    enter(ctx, 4);  // entry check point + this block's cycles
    ld(v1, a1, 0);
    sd(v1, a0, airec::kUid);
}

// 0x002C0970 sub_2C0970 -- 124 bytes; leaf frame (no stack)
// [btlAITargetSelectByUid] Selects the candidate whose action uid equals the record's stored uid (+48): index -> +58,
// 1; else index 0, 0.
// Arguments: a0 record.
void sub_2C0970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x002c0970
    enter(ctx, 4);  // entry check point + this block's cycles
    sh(zero, a0, airec::kIndex);
    ld(a1, a0, airec::kUid);
    if (a1 != 0) {
        // 0x002c098c
        charge(ctx, 4);
        a2 = 0;
        lhu(v1, a0, airec::kCount);
        for (;;) {
            // 0x002c09d0
            charge(ctx, 4);
            v0 = a2 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c099c
            charge(ctx, 7);
            v0 = a2 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(a0, v0);
            lw(v0, v0, 0);
            ld(v0, v0, 0);
            if (a1 == v0) {
                goto L_002c09b8_4;
            }
            // 0x002c09c8
            charge(ctx, 2);
            v0 = addiu(a2, 1);
            a2 = v0 & 0xFFFF;
        }
        // 0x002c09e0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c0980
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002c09e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_002c09b8_4:
    charge(ctx, 4);
    sh(a2, a0, 58);
    v0 = 1;
    // 0x002c09e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002C09F0 sub_2C09F0 -- 96 bytes; leaf frame (no stack)
// [btlAITargetGetSideMask] The side mask of an AI target record's candidates (1 << unit side, or-ed).
// Arguments: a0 record.
void sub_2C09F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x002c09f0
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0;
    a3 = 0;
    lhu(a2, a0, airec::kCount);
    a1 = 1;
    for (;;) {
        // 0x002c0a38
        charge(ctx, 4);
        v1 = a3 & 0xFFFF;
        v1 = slt(v1, a2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c0a08
        charge(ctx, 12);
        v1 = a3 & 0xFFFF;
        v1 = sll(v1, 2);
        v1 = addu(a0, v1);
        lw(v1, v1, 0);
        lw(v1, v1, 48);
        lbu(v1, v1, 162);
        v1 = sllv(a1, v1);
        v1 = v1 & 0xFFFF;
        v0 = v0 | v1;
        v0 = v0 & 0xFFFF;
        v1 = addiu(a3, 1);
        a3 = v1 & 0xFFFF;
    }
    // 0x002c0a48
    charge(ctx, 2);
}

// 0x002C0AC0 sub_2C0AC0 -- 876 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAITargetPickSupport] Auto-target for a support skill (records with two or more candidates, commands 1..3, a
// single-target skill): a cure skill (+24 == 2) picks the first candidate with its status (+28), a buff the first
// without its effect (+32); HP formulas 2/5/9/11/15 the lowest HP; SP formulas the lowest SP.
// Arguments: a0 btlAction, a1 record.
void sub_2C0AC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c0e08: the epilogue (one copy; every path ends in it)
    auto epilogue = [&] {
        charge(ctx, 9);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
    };
    // 0x2c0ba8 / 0x2c0c20: select candidate s2 (record +58) and leave
    auto select_s2 = [&] {
        charge(ctx, 3);
        sh(s2, s0, airec::kIndex);
        epilogue();
    };
    // the formula ladder of 0x2c0c48 / 0x2c0d2c: 15, 11, 9, 5, 2 are the formulas that pick the lowest value (each
    // compare block 3 cycles; the miss block 2)
    auto lowest_formula = [&]() -> bool {
        v1 = 15;
        if (a0 == v1) return true;
        for (s32 f : {11, 9, 5, 2}) {
            charge(ctx, 3);
            v1 = f;
            if (a0 == v1) return true;
        }
        charge(ctx, 2);
        return false;
    };
    // 0x002c0ac0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // s0 = the AI target record
    lhu(v1, a1, airec::kCount);
    at = slti(v1, 2);
    if (at != 0) {
        epilogue();  // fewer than two candidates: nothing to choose
        return;
    }
    // 0x002c0af0: commands 2 (skill), 3 (item) and 1 (attack) only
    charge(ctx, 4);
    lhu(a1, a0, act::kCmdKind);
    v1 = 2;
    if (a1 != v1) {
        // 0x002c0b00
        charge(ctx, 3);
        v1 = 3;
        if (a1 != v1) {
            // 0x002c0b0c
            charge(ctx, 3);
            v1 = 1;
            if (a1 != v1) {
                // 0x002c0b18
                charge(ctx, 2);
                epilogue();
                return;
            }
        }
    }
    // 0x002c0b20: s1 = 44 * skill (the SkillRecord offset); a single-target skill (+8 == 0) only
    charge(ctx, 11);
    lhu(a0, a0, act::kCmdSkill);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    v1 = addu(v1, a0);
    s1 = sll(v1, 2);
    lw(a1, gp, kGpSkillTbl);  // gBtlSkillTbl
    a0 = addu(s1, a1);
    lbu(v1, a0, 8);
    if (v1 != 0) {
        epilogue();
        return;
    }
    // 0x002c0b4c: a cure skill (+24 == 2) picks the first candidate with its status (+28)
    charge(ctx, 4);
    lbu(a0, a0, 24);
    v1 = 2;
    if (a0 == v1) {
        // 0x002c0b5c
        charge(ctx, 5);
        v1 = addiu(a1, 28);
        v1 = addu(v1, s1);
        lw(s3, v1, 0);
        if (s3 != 0) {
            // 0x002c0b70
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x002c0bbc: over the candidates (s2)
                charge(ctx, 5);
                a0 = s2 & 0xFFFF;
                lhu(v1, s0, airec::kCount);
                v1 = slt(a0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002c0b7c
                charge(ctx, 11);
                v0 = s2 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, airec::kCands);
                lw(v0, v0, act::kUnit);
                lw(a0, v0, unit::kDat);
                a1 = s3;
                jal(ctx, 0x2C0B98u, gen::fn_datCalcChkBadStatus_00300580);
                if (v0 != 0) {
                    select_s2();
                    return;
                }
                // 0x002c0bb4
                charge(ctx, 2);
                v1 = addiu(s2, 1);
                s2 = v1 & 0xFFFF;
            }
        }
    }
    // 0x002c0bd0: a buff (+32) picks the first candidate without that effect (sub_301CA0)
    charge(ctx, 6);
    lw(v1, gp, kGpSkillTbl);  // gBtlSkillTbl
    v1 = addiu(v1, 32);
    v1 = addu(v1, s1);
    lw(s3, v1, 0);
    if (s3 != 0) {
        // 0x002c0be8
        charge(ctx, 3);
        s2 = 0;
        for (;;) {
            // 0x002c0c34
            charge(ctx, 5);
            a0 = s2 & 0xFFFF;
            lhu(v1, s0, airec::kCount);
            v1 = slt(a0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c0bf4
            charge(ctx, 11);
            v0 = s2 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            lw(v0, v0, airec::kCands);
            lw(v0, v0, act::kUnit);
            lw(a0, v0, unit::kDat);
            a1 = s3;
            jal(ctx, 0x2C0C10u, gen::fn_sub_301CA0_00301ca0);
            if (v0 == 0) {
                select_s2();
                return;
            }
            // 0x002c0c2c
            charge(ctx, 2);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
    }
    // 0x002c0c48: the HP formula (+17)
    charge(ctx, 6);
    lw(v1, gp, kGpSkillTbl);  // gBtlSkillTbl
    v1 = addu(s1, v1);
    lbu(a0, v1, 17);
    if (lowest_formula()) {
        // 0x002c0c98: the candidate with the lowest HP (s3 = its index, s4 = the HP)
        charge(ctx, 6);
        v1 = 0xFFFF;
        s4 = v1 & 0xFFFF;
        s3 = si(-1);
        s2 = 0;
        for (;;) {
            // 0x002c0cf8
            charge(ctx, 5);
            a0 = s2 & 0xFFFF;
            lhu(v1, s0, airec::kCount);
            v1 = slt(a0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c0cb0
            charge(ctx, 13);
            v0 = s2 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            lw(v0, v0, airec::kCands);
            lw(v0, v0, act::kUnit);
            lw(a0, v0, unit::kDat);
            jal(ctx, 0x2C0CC8u, gen::fn_datCalcGetHp_002ffd70);
            a0 = v0 & 0xFFFF;
            v1 = s4 & 0xFFFF;
            at = slt(a0, v1);
            if (at != 0) {
                // 0x002c0ce4
                charge(ctx, 3);
                s4 = a0;
                s3 = dsll32(s2, 16);
                s3 = dsra32(s3, 16);
            }
            // 0x002c0cf0
            charge(ctx, 2);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
        // 0x002c0d0c
        charge(ctx, 5);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        v1 = si(-1);
        if (a0 != v1) {
            // 0x002c0d20
            charge(ctx, 3);
            sh(s3, s0, airec::kIndex);
            epilogue();
            return;
        }
        // none found: on to the SP formula
    }
    // 0x002c0d2c: the SP formula (+20)
    charge(ctx, 6);
    lw(v1, gp, kGpSkillTbl);  // gBtlSkillTbl
    v1 = addu(s1, v1);
    lbu(a0, v1, 20);
    if (!lowest_formula()) {
        epilogue();  // after the 0x2c0d74 miss block
        return;
    }
    // 0x002c0d7c: the candidate with the lowest SP (s1 = its index, s3 = the SP)
    charge(ctx, 6);
    v1 = 0xFFFF;
    s3 = v1 & 0xFFFF;
    s1 = si(-1);
    s2 = 0;
    for (;;) {
        // 0x002c0ddc
        charge(ctx, 5);
        a0 = s2 & 0xFFFF;
        lhu(v1, s0, airec::kCount);
        v1 = slt(a0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c0d94
        charge(ctx, 13);
        v0 = s2 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, airec::kCands);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2C0DACu, gen::fn_datCalcGetSp_002ffd80);
        a0 = v0 & 0xFFFF;
        v1 = s3 & 0xFFFF;
        at = slt(a0, v1);
        if (at != 0) {
            // 0x002c0dc8
            charge(ctx, 3);
            s3 = a0;
            s1 = dsll32(s2, 16);
            s1 = dsra32(s1, 16);
        }
        // 0x002c0dd4
        charge(ctx, 2);
        v1 = addiu(s2, 1);
        s2 = v1 & 0xFFFF;
    }
    // 0x002c0df0
    charge(ctx, 5);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v1 = si(-1);
    if (a0 != v1) {
        // 0x002c0e04
        charge(ctx, 1);
        sh(s1, s0, airec::kIndex);
    }
    epilogue();
}

// 0x002C0E30 sub_2C0E30 -- 260 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIFindUnit] The AI unit finder: the first combatant action whose unit is on a side of the mask, alive when the
// status mask holds 0x80000, without the masked statuses, with the unit id.
// Arguments: a0 id, a1 side mask, a2 status mask.
void sub_2C0E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c0e30
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s5, v0, gbtl::kActionList);
    s4 = a1 & 0xFFFF;
    v0 = 0x80000;
    s3 = s0 & v0;
    s2 = a0 & 0xFFFF;
    bool found = false;  // host only: the original branches from the id test to 0x2c0ef0
    for (;;) {
        // 0x002c0f00: the loop test (s5 = the action)
        charge(ctx, 2);
        if (s5 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c0e74: a combatant (kFlags2 bit 0) ...
        charge(ctx, 4);
        lhu(v1, s5, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c0e84: ... that is placed (bit 3) ...
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c0e90: ... whose unit's side is in the mask ...
                charge(ctx, 7);
                lw(s1, s5, act::kUnit);
                lbu(v1, s1, unit::kSide);
                v0 = 1;
                v0 = sllv(v0, v1);
                v0 = s4 & v0;
                if (v0 != 0) {
                    // 0x002c0eac: ... alive when the status mask holds 0x80000 ...
                    charge(ctx, 2);
                    bool alive = true;
                    if (s3 != 0) {
                        // 0x002c0eb4
                        charge(ctx, 6);
                        lw(a0, s1, unit::kDat);
                        a1 = 0;
                        jal(ctx, 0x2C0EBCu, gen::fn_datCalcIsDead_0030b5a0);
                        alive = v0 == 0;
                    }
                    if (alive) {
                        // 0x002c0ecc: ... without the masked statuses ...
                        charge(ctx, 6);
                        lw(a0, s1, unit::kDat);
                        a1 = s0;
                        jal(ctx, 0x2C0ED4u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c0ee4: ... and with the id
                            charge(ctx, 3);
                            lhu(v0, s1, unit::kId);
                            if (v0 == s2) {
                                found = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        // 0x002c0efc: the next action
        charge(ctx, 1);
        lw(s5, s5, act::kNext);
    }
    if (found) {
        // 0x002c0ef0: the action
        charge(ctx, 3);
        v0 = s5;
    } else {
        // 0x002c0f08: none
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x002c0f0c: the epilogue
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

// 0x002C0F40 sub_2C0F40 -- 308 bytes; frame 0xD0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICountUnits] Counts the candidates (collected by sub_2BFCB0) that are combatants, free of the status mask and
// for which the condition fn(candidate, param) differs from 'expect'; stores them when an output array is given.
// Arguments: a0 action, a1 param, a2 status, a3 side mask, t0 expect, t1 fn, t2 out.
void sub_2C0F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c0f40
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a2;
    s1 = t0;
    s7 = t1;
    s0 = t2;
    a1 = addiu(sp, 0x90);
    a2 = a3;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2C0F8Cu, gen::fn_sub_2BFCB0_002bfcb0);
    s4 = 0;
    s5 = 0;
    for (;;) {
        // 0x002c102c
        charge(ctx, 5);
        v1 = s5 & 0xFFFF;
        lhu(v0, sp, 0xC8);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c0fa4
        charge(ctx, 8);
        v0 = s5 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(s6, v0, 144);
        lhu(v1, s6, 26);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c0fc4
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c0fd0
                charge(ctx, 7);
                lw(v0, s6, 48);
                lw(a0, v0, 2604);
                a1 = s2;
                jal(ctx, 0x2C0FDCu, gen::fn_datCalcChkBadStatus_00300580);
                if (v0 == 0) {
                    // 0x002c0fec
                    charge(ctx, 6);
                    a0 = s6;
                    a1 = s3;
                    jalr(ctx, 0x2C0FF4u, s7.u());
                    if (s1 != v0) {
                        // 0x002c1004
                        charge(ctx, 2);
                        if (s0 != 0) {
                            // 0x002c100c
                            charge(ctx, 4);
                            v0 = s4 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(s0, v0);
                            sw(s6, v0, 0);
                        }
                        // 0x002c101c
                        charge(ctx, 2);
                        v0 = addiu(s4, 1);
                        s4 = v0 & 0xFFFF;
                    }
                }
            }
        }
        // 0x002c1024
        charge(ctx, 2);
        v0 = addiu(s5, 1);
        s5 = v0 & 0xFFFF;
    }
    // 0x002c1040
    charge(ctx, 13);
    v0 = s4;
    ld(ra, sp, 0x80);
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

// 0x002C12F0 sub_2C12F0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICondMyHp] AI condition MYHP (row 1): 100 * HP <= max HP * param.
// Arguments: a0 btlAction, a1 param.
void sub_2C12F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c12f0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    lhu(s1, a0, dat::kHp);
    jal(ctx, 0x2C1310u, gen::fn_datCalcGetMaxHp_002ffdf0);
    a0 = v0 & 0xFFFF;
    v0 = sll(s1, 2);
    v1 = addu(v0, s1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    mult(v0, a0, s0);
    v0 = sltu(v0, v1);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C13D0 sub_2C13D0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICondMySp] AI condition MYMP (row 2): 100 * SP <= max SP * param.
// Arguments: a0 btlAction, a1 param.
void sub_2C13D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c13d0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    lhu(s1, a0, dat::kSp);
    jal(ctx, 0x2C13F0u, gen::fn_datCalcGetMaxSp_00300100);
    a0 = v0 & 0xFFFF;
    v0 = sll(s1, 2);
    v1 = addu(v0, s1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    mult(v0, a0, s0);
    v0 = sltu(v0, v1);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C1590 sub_2C1590 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICondAllyLevelOver] AI condition FRLV_O (row 7): the mean level of the acting unit's side (living units) >=
// param.
// Arguments: a0 btlAction, a1 param.
void sub_2C1590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1590
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a0 = v0 & 0xFFFF;
    a1 = 0x80000;
    jal(ctx, 0x2C15B8u, gen::fn_btlGetMeanLevel_002d4cf0);
    v0 = v0 & 0xFFFF;
    v0 = sltu(v0, s0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C1650 sub_2C1650 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICondAllyCount] AI condition FRCNT (row 9): living units on the acting unit's side <= param.
// Arguments: a0 btlAction, a1 param.
void sub_2C1650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1650
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a0 = v0 & 0xFFFF;
    a1 = 0x80000;
    jal(ctx, 0x2C1678u, gen::fn_btlCountActiveUnits_002d4e10);
    v0 = v0 & 0xFFFF;
    v0 = sltu(s0, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C16A0 sub_2C16A0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICondEnemyCount] AI condition ENCNT (row 10): living units on the other side <= param.
// Arguments: a0 btlAction, a1 param.
void sub_2C16A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c16a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c16cc
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c16c0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c16d0
    charge(ctx, 15);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a0 = v0 & 0xFFFF;
    a1 = 0x80000;
    jal(ctx, 0x2C16E4u, gen::fn_btlCountActiveUnits_002d4e10);
    v0 = v0 & 0xFFFF;
    v0 = sltu(s0, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C1D90 sub_2C1D90 -- 120 bytes; leaf frame (no stack)
// [btlAICondFirstStrike] AI condition SENSEI (row 21, first strike): the unit has not acted yet and its side won the
// advantage roll (+26 == 2 enemies / 1 party).
// Arguments: a0 btlAction.
void sub_2C1D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x002c1d90
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, act::kTurnsTaken);
    if (i64(v0) <= 0) {
        // 0x002c1da8
        charge(ctx, 5);
        lw(v0, a0, act::kUnit);
        lbu(v1, v0, unit::kSide);
        v0 = 1;
        if (v1 == v0) {
            // 0x002c1de4
            charge(ctx, 6);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v0, v0, gbtl::kAdvantage);
            v0 = v0 ^ 0x2;
            v0 = sltiu(v0, 1);
        } else {
            // 0x002c1dbc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002c1dcc
                charge(ctx, 6);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lhu(v0, v0, gbtl::kAdvantage);
                v0 = v0 ^ 0x1;
                v0 = sltiu(v0, 1);
            } else {
                // 0x002c1dc4
                charge(ctx, 2);
                // 0x002c1dfc
                charge(ctx, 1);
                v0 = 0;
            }
        }
    } else {
        // 0x002c1d9c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002c1e00 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002C1E10 sub_2C1E10 -- 60 bytes; frame 0x10: ra sp+0x0
// [btlAICondMyRepel] AI condition MYHANSYA (row 22): the unit repels the element (affinity bit 0x2000000).
// Arguments: a0 btlAction, a1 element.
void sub_2C1E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1e10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    a1 = dsll32(a1, 16);
    a1 = dsra32(a1, 16);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1E28u, gen::fn_datCalcGetAffinity_00306e80);
    v1 = 0x2000000;
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1ED0 sub_2C1ED0 -- 60 bytes; frame 0x10: ra sp+0x0
// [btlAICondMyWeak] AI condition MYWEAK (row 25): the unit is weak to the element (affinity bit 0x8000000).
// Arguments: a0 btlAction, a1 element.
void sub_2C1ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1ed0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    a1 = dsll32(a1, 16);
    a1 = dsra32(a1, 16);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1EE8u, gen::fn_datCalcGetAffinity_00306e80);
    v1 = 0x8000000;
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C24D0 sub_2C24D0 -- 20 bytes; leaf frame (no stack)
// [btlAICondTurn] AI condition TURN (row 43): turns taken (+32) <= param.
// Arguments: a0 btlAction, a1 param.
void sub_2C24D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c24d0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, act::kTurnsTaken);
    v0 = sltu(a1, v0);
    v0 = v0 ^ 0x1;
}

// 0x002C3300 sub_2C3300 -- 248 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICondEnemyOverLevel] AI condition ENOVERLV (row 70): some opposing combatant is at least param levels above
// the acting unit.
// Arguments: a0 btlAction, a1 param.
void sub_2C3300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3300
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 != 0) {
        // 0x002c3338
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c332c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c333c
    charge(ctx, 10);
    s0 = v0 & 0xFFFF;
    lw(a0, v1, unit::kDat);
    jal(ctx, 0x2C3344u, gen::fn_datCalcGetLevel_002ffcc0);
    s1 = v0 & 0xFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s2, v0, gbtl::kActionList);
    s0 = s0 & 0xFFFF;
    bool over = false;  // host only: the original branches from the level test to 0x2c33bc
    for (;;) {
        // 0x002c33cc: the loop test (s2 = the action)
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c3364: a placed combatant ...
        charge(ctx, 4);
        lhu(v1, s2, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c3374
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c3380: ... of the other side (s0) ...
                charge(ctx, 4);
                lw(v1, s2, act::kUnit);
                lbu(v0, v1, unit::kSide);
                if (v0 == s0) {
                    // 0x002c3390: ... at the acting unit's level (s1) or above ...
                    charge(ctx, 7);
                    lw(a0, v1, unit::kDat);
                    jal(ctx, 0x2C3394u, gen::fn_datCalcGetLevel_002ffcc0);
                    v1 = v0 & 0xFF;
                    v0 = sltu(v1, s1);
                    if (v0 == 0) {
                        // 0x002c33ac: ... by at least the parameter (s3)
                        charge(ctx, 4);
                        v0 = subu(v1, s1);
                        v0 = sltu(v0, s3);
                        if (v0 == 0) {
                            over = true;
                            break;
                        }
                    }
                }
            }
        }
        // 0x002c33c8: the next action
        charge(ctx, 1);
        lw(s2, s2, act::kNext);
    }
    if (over) {
        // 0x002c33bc
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x002c33d4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x002c33d8: the epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C3400 sub_2C3400 -- 44 bytes; frame 0x10: ra sp+0x0
// [btlAICondMyEffect] AI condition MYHOJO (row 71): the unit has an active effect of the mask (sub_301CA0).
// Arguments: a0 btlAction, a1 mask.
void sub_2C3400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3400
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C3410u, gen::fn_sub_301CA0_00301ca0);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3770 sub_2C3770 -- 1124 bytes; frame 0xF0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAITargetPickDefault] AI target selector AI (row 0, the fallback): all candidates for a multi-target skill; the
// only one; otherwise a random one -- or, for the damage formulas against party members with fewer than five
// candidates, a pick weighted towards the lowest HP ratio (the weights 0x696FA0 by candidate count, the list
// bubble-sorted by HP / max HP).
// Arguments: a0 btlAction.
void sub_2C3770(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002c3770
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(s0, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C37A8u, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c3808
        charge(ctx, 4);
        lhu(s4, s0, act::kTargetRecCount);
        v0 = 1;
        if (s4 != v0) {
            // 0x002c382c
            charge(ctx, 4);
            lw(v1, s0, act::kUnit);
            lbu(v1, v1, unit::kSide);
            if (v1 == v0) {
                // 0x002c383c
                charge(ctx, 3);
                a1 = 0;
                for (;;) {
                    // 0x002c3870
                    charge(ctx, 4);
                    a0 = a1 & 0xFFFF;
                    v1 = slt(a0, s4);
                    if (v1 != 0) {
                        backedge(ctx);
                        // 0x002c3848
                        charge(ctx, 8);
                        v1 = a1 & 0xFFFF;
                        v1 = sll(v1, 2);
                        v1 = addu(s0, v1);
                        lw(v1, v1, 136);
                        lw(v1, v1, 48);
                        lbu(v1, v1, 162);
                        if (v1 == 0) {
                            // 0x002c3868
                            charge(ctx, 2);
                            v1 = addiu(a1, 1);
                            a1 = v1 & 0xFFFF;
                            continue;
                        }
                    }
                    break;
                }
                // 0x002c3880
                charge(ctx, 2);
                if (a0 == s4) {
                    // 0x002c3888
                    charge(ctx, 1);
                    v0 = 0;
                }
            }
            // 0x002c388c
            charge(ctx, 12);
            lhu(a0, s0, act::kCmdSkill);
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 1);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            lw(v1, gp, kGpSkillTbl);  // gBtlSkillTbl
            v1 = addu(a0, v1);
            lbu(a0, v1, 17);
            v1 = 16;
            if (a0 != v1) {
                // 0x002c38bc
                charge(ctx, 3);
                v1 = 14;
                if (a0 != v1) {
                    // 0x002c38c8
                    charge(ctx, 3);
                    v1 = 13;
                    if (a0 != v1) {
                        // 0x002c38d4
                        charge(ctx, 3);
                        v1 = 12;
                        if (a0 != v1) {
                            // 0x002c38e0
                            charge(ctx, 3);
                            v1 = 10;
                            if (a0 != v1) {
                                // 0x002c38ec
                                charge(ctx, 3);
                                v1 = 8;
                                if (a0 != v1) {
                                    // 0x002c38f8
                                    charge(ctx, 3);
                                    v1 = 4;
                                    if (a0 != v1) {
                                        // 0x002c3904
                                        charge(ctx, 3);
                                        v1 = 3;
                                        if (a0 != v1) {
                                            // 0x002c3910
                                            charge(ctx, 3);
                                            v1 = 1;
                                            if (a0 != v1) {
                                                // 0x002c391c
                                                charge(ctx, 1);
                                                v0 = v1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x002c3920
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x002c3928
                charge(ctx, 3);
                at = slti(s4, 5);
                if (at == 0) {
                    goto L_002c3934;
                }
                // 0x002c3964
                charge(ctx, 4);
                s5 = 0;
                s3 = s4 & 0xFFFF;
                for (;;) {
                    // 0x002c3a4c
                    charge(ctx, 4);
                    v0 = s5 & 0xFFFF;
                    v0 = slt(v0, s3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002c3974
                    charge(ctx, 22);
                    s2 = s5 & 0xFFFF;
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    s7 = addiu(v0, 136);
                    lw(s6, v0, 136);
                    lw(v0, s6, 48);
                    lw(a0, v0, 2604);
                    jal(ctx, 0x2C3990u, gen::fn_datCalcGetMaxHp_002ffdf0);
                    s1 = v0 & 0xFFFF;
                    lw(v0, s6, 48);
                    lw(a0, v0, 2604);
                    jal(ctx, 0x2C39A4u, gen::fn_datCalcGetHp_002ffd70);
                    a1 = v0 & 0xFFFF;
                    v0 = sll(s2, 3);
                    v0 = addu(v0, sp);
                    a0 = addiu(v0, 144);
                    lw(v0, s7, 0);
                    sw(v0, a0, 0);
                    if (i64(a1) < 0) {
                        // 0x002c39e0
                        charge(ctx, 7);
                        v1 = srl(a1, 1);
                        v0 = a1 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x002c39cc
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x002c39fc
                    charge(ctx, 2);
                    if (i64(s1) < 0) {
                        // 0x002c3a18
                        charge(ctx, 7);
                        v1 = srl(s1, 1);
                        v0 = s1 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x002c3a04
                        charge(ctx, 5);
                        mtc1(s1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x002c3a34
                    charge(ctx, 6);
                    div_s(f0, f1, f0);
                    swc1(f0, a0, 4);
                    v0 = addiu(s5, 1);
                    s5 = v0 & 0xFFFF;
                }
                // 0x002c3a5c
                charge(ctx, 2);
                t0 = addiu(s3, -1);
                a0 = 1;
                for (;;) {
                    // 0x002c3a64
                    charge(ctx, 4);
                    t1 = 0;
                    a3 = 0;
                    for (;;) {
                        // 0x002c3ad0
                        charge(ctx, 4);
                        v1 = a3 & 0xFFFF;
                        v0 = slt(v1, t0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002c3a74
                        charge(ctx, 13);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, sp);
                        v1 = addiu(v0, 144);
                        v0 = a3 & 0xFFFF;
                        v0 = sll(v0, 3);
                        v0 = addu(v0, sp);
                        a2 = addiu(v0, 144);
                        a1 = addiu(a2, 4);
                        lwc1(f1, a2, 4);
                        lwc1(f0, v1, 12);
                        c_lt_s(f1, f0);
                        if (cond(ctx)) {
                            // 0x002c3aa8
                            charge(ctx, 8);
                            lw(v1, a2, 0);
                            lw(v0, a2, 8);
                            sw(v0, a2, 0);
                            lwc1(f0, a2, 12);
                            swc1(f0, a1, 0);
                            sw(v1, a2, 8);
                            swc1(f1, a2, 12);
                            t1 = a0;
                        }
                        // 0x002c3ac8
                        charge(ctx, 2);
                        v0 = addiu(a3, 1);
                        a3 = v0 & 0xFFFF;
                    }
                    // 0x002c3ae0
                    charge(ctx, 2);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x002c3ae8
                charge(ctx, 13);
                a0 = 100;
                jal(ctx, 0x2C3AECu, gen::fn_datCalcRand_002ffbc0);
                a2 = v0 & 0xFFFF;
                t0 = 0;
                a3 = 0;
                a1 = s4 & 0xFFFF;
                v1 = sll(a1, 2);
                v0 = 0x690000;
                v0 = addiu(v0, 28576);  // &0x696FA0
                a0 = addu(v0, v1);
                for (;;) {
                    // 0x002c3b40
                    charge(ctx, 4);
                    v1 = a3 & 0xFFFF;
                    v0 = slt(v1, a1);
                    if (v0 != 0) {
                        backedge(ctx);
                        // 0x002c3b1c
                        charge(ctx, 7);
                        v0 = addu(a0, v1);
                        lbu(v0, v0, -4);
                        v0 = addu(t0, v0);
                        t0 = v0 & 0xFFFF;
                        at = slt(t0, a2);
                        if (at != 0) {
                            // 0x002c3b38
                            charge(ctx, 2);
                            v0 = addiu(a3, 1);
                            a3 = v0 & 0xFFFF;
                            continue;
                        }
                    }
                    break;
                }
                // 0x002c3b50
                charge(ctx, 2);
                if (s3 == v1) {
                    // 0x002c3b7c
                    charge(ctx, 9);
                    a0 = s4 & 0xFFFF;
                    jal(ctx, 0x2C3B80u, gen::fn_datCalcRand_002ffbc0);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, sp);
                    lw(v0, v0, 144);
                    sw(v0, s0, act::kTargets);
                    v0 = 1;
                    sh(v0, s0, act::kTargetCount);
                } else {
                    // 0x002c3b58
                    charge(ctx, 9);
                    v0 = a3 & 0xFFFF;
                    v0 = sll(v0, 3);
                    v0 = addu(v0, sp);
                    lw(v0, v0, 144);
                    sw(v0, s0, act::kTargets);
                    v0 = 1;
                    sh(v0, s0, act::kTargetCount);
                }
                goto L_002c3ba0;
            }
        L_002c3934:
            charge(ctx, 12);
            a0 = s4 & 0xFFFF;
            jal(ctx, 0x2C3938u, gen::fn_datCalcRand_002ffbc0);
            v0 = v0 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(v0, v0, 136);
            sw(v0, s0, act::kTargets);
            v0 = 1;
            sh(v0, s0, act::kTargetCount);
        } else {
            // 0x002c3818
            charge(ctx, 5);
            lw(v1, s0, act::kTargetRec);
            sw(v1, s0, act::kTargets);
            sh(v0, s0, act::kTargetCount);
        }
    L_002c3ba0:
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002c37bc
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c37e4
            charge(ctx, 5);
            lhu(v1, s0, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c37c8
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c37f8
        charge(ctx, 4);
        sh(v1, s0, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c3ba4 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xF0);
}

// 0x002C48A0 sub_2C48A0 -- 484 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickBestSkill] Of a skill list, the skill (0 entries skipped) whose damage (HP + datCalcDamage(skill, me, it,
// 1, 1, 1, 0, 1)) leaves the target with the least HP; the first kill beats any survivor and a kill with less
// overkill beats an earlier kill; -1 when none. Kind 0 keeps only all-target skills (SkillRecord +8 == 1), kind 1
// only single-target ones (+8 == 0), others every skill. Then sub_301870 on both units.
// Arguments: a0 me, a1 target, a2 u16 skills*, a3 count, t0 kind.
void sub_2C48A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c48a0
    enter(ctx, 30);  // entry check point + this block's cycles
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
    s4 = a0;
    s5 = a1;
    fp = a2;
    s7 = a3;
    s0 = t0;
    lw(v0, a1, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C48E8u, gen::fn_datCalcGetHp_002ffd70);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xA0);
    s2 = si(-1);
    v0 = 0xFF0000;
    s3 = v0 | 0xFFFF;  // &0xFFFFFF
    s1 = 0;
    s6 = s0 & 0xFFFF;
    s7 = s7 & 0xFFFF;
    for (;;) {
        // 0x002c4a1c
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slt(v0, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c4918
        charge(ctx, 6);
        v0 = s1 & 0xFFFF;
        v0 = sll(v0, 1);
        s0 = addu(fp, v0);
        lhu(a0, s0, 0);
        if (a0 != 0) {
            // 0x002c493c
            charge(ctx, 8);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, a0);
            v1 = sll(v0, 2);
            lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
            v0 = addu(v0, v1);
            lbu(v0, v0, 8);
        } else {
            // 0x002c4930
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x002c495c: the scope filter on the record's +8 (0 one target, 1 all): kind 0 keeps the all-target skills,
        // kind 1 the single-target ones, any other kind every skill
        charge(ctx, 3);
        a1 = v0 & 0xFF;
        bool keep = true;  // host only: the paths that reach 0x2c4990
        if (s6 == 0) {
            // 0x002c4968
            charge(ctx, 4);
            v1 = a1 & 0xFF;
            v0 = 1;
            keep = v1 == v0;
        }
        if (keep) {
            // 0x002c4978
            charge(ctx, 3);
            v0 = 1;
            if (s6 == v0) {
                // 0x002c4984
                charge(ctx, 3);
                v0 = a1 & 0xFF;
                keep = v0 == 0;
            }
        }
        if (keep) {
            // 0x002c4990: the target's HP after the skill: HP + datCalcDamage(skill, me, it, 1, 1, 1, 0, 1)
            charge(ctx, 15);
            lw(v1, s4, act::kUnit);
            lw(v0, s5, act::kUnit);
            lw(a1, v1, unit::kDat);
            lw(a2, v0, unit::kDat);
            a3 = 1;
            t0 = a3;
            t1 = a3;
            t2 = 0;
            t3 = a3;
            jal(ctx, 0x2C49B4u, gen::fn_datCalcDamage_00303130);
            lq(v1, sp, 0xA0);
            v0 = addu(v1, v0);
            // keep the skill (s2, its HP after in s3) when it leaves less HP while nothing kills yet, when it is the
            // first kill, or when it kills with less overkill than the kill found so far
            bool kill_check = true;  // host only: the paths that reach 0x2c49f0
            if (i64(v0) > 0) {
                // 0x002c49cc
                charge(ctx, 2);
                if (i64(s3) > 0) {
                    kill_check = false;
                    // 0x002c49d4
                    charge(ctx, 3);
                    at = slt(v0, s3);
                    if (at != 0) {
                        // 0x002c49e0
                        charge(ctx, 4);
                        lhu(s2, s0, 0);
                        s3 = v0;
                    }
                }
            }
            if (kill_check) {
                // 0x002c49f0
                charge(ctx, 2);
                if (i64(v0) <= 0) {
                    // 0x002c49f8
                    charge(ctx, 2);
                    bool better = true;
                    if (i64(s3) <= 0) {
                        // 0x002c4a00
                        charge(ctx, 3);
                        at = slt(s3, v0);
                        better = at != 0;
                    }
                    if (better) {
                        // 0x002c4a0c
                        charge(ctx, 2);
                        lhu(s2, s0, 0);
                        s3 = v0;
                    }
                }
            }
        }
        // 0x002c4a14: the next skill
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x002c4a2c
    charge(ctx, 22);
    lw(v0, s4, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4A34u, gen::fn_sub_301870_00301870);
    lw(v0, s5, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4A44u, gen::fn_sub_301870_00301870);
    v0 = s2;
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

// 0x002C6A00 sub_2C6A00 -- 408 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAISetCommand] Decodes an AI command code into the command record (+52 command, +54 skill, +62 argument): 0x8000
// attack (the weapon's attack skill, command 1), 0x8001 / 0x8006 / 0x8007 / 0x8008 the commands 6 / 11 / 8 / 12,
// 0x8002 command 7, 0x8005 nothing, 0x8004 a random Mix-Raid skill (command 2), 0x1xxx command 9 with skill 341 and
// argument xxx, 0x2xxx command 7 with action +220 = xxx, any other code the skill itself (command 2).
// Arguments: a0 btlAction, a1 command record, a2 code.
void sub_2C6A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c6a00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    v1 = a2 & 0xFFFF;
    a3 = v1 & 0xF000;
    a1 = 0x8000;
    if (a3 != a1) {
        // 0x002c6a30
        charge(ctx, 1);
        a1 = a3 & 0xFFFF;
    } else {
        // 0x002c6a24
        charge(ctx, 3);
        a1 = a2;
    }
    // 0x002c6a34
    charge(ctx, 4);
    a3 = a1 & 0xFFFF;
    a1 = 0x8004;
    if (a3 == a1) {
        // 0x002c6b64
        charge(ctx, 5);
        lw(v0, a0, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2C6B6Cu, gen::fn_sub_308A80_00308a80);
        a2 = v0 & 0xFFFF;
    L_002c6b78:
        charge(ctx, 3);
        v1 = 2;
        sh(v1, s0, 52);
        sh(a2, s0, 54);
    } else {
        // 0x002c6a44
        charge(ctx, 3);
        a1 = 0x8008;
        if (a3 == a1) {
            // 0x002c6b54
            charge(ctx, 4);
            v1 = 12;
            sh(v1, s0, 52);
        } else {
            // 0x002c6a50
            charge(ctx, 3);
            a1 = 0x8001;
            if (a3 == a1) {
                // 0x002c6b44
                charge(ctx, 4);
                v1 = 6;
                sh(v1, s0, 52);
            } else {
                // 0x002c6a5c
                charge(ctx, 3);
                a1 = 0x8006;
                if (a3 == a1) {
                    // 0x002c6b34
                    charge(ctx, 4);
                    v1 = 11;
                    sh(v1, s0, 52);
                } else {
                    // 0x002c6a68
                    charge(ctx, 3);
                    a1 = 0x8005;
                    if (a3 != a1) {
                        // 0x002c6a74
                        charge(ctx, 3);
                        a1 = 0x8007;
                        if (a3 == a1) {
                            // 0x002c6b24
                            charge(ctx, 4);
                            v1 = 8;
                            sh(v1, s0, 52);
                        } else {
                            // 0x002c6a80
                            charge(ctx, 3);
                            a1 = 0x8002;
                            if (a3 != a1) {
                                // 0x002c6a8c
                                charge(ctx, 3);
                                a1 = 8192;
                                if (a3 == a1) {
                                    // 0x002c6b04
                                    charge(ctx, 4);
                                    a1 = lui(0xFFFF);
                                    a1 = a1 | 0xFFF;
                                    v1 = v1 & a1;
                                    sh(v1, a0, 220);
                                    goto L_002c6b14;
                                }
                                // 0x002c6a98
                                charge(ctx, 3);
                                a1 = 4096;
                                if (a3 == a1) {
                                    // 0x002c6adc
                                    charge(ctx, 10);
                                    a0 = 9;
                                    sh(a0, s0, 52);
                                    a0 = 341;
                                    sh(a0, s0, 54);
                                    a0 = lui(0xFFFF);
                                    a0 = a0 | 0xFFF;
                                    v1 = v1 & a0;
                                    sh(v1, s0, 62);
                                } else {
                                    // 0x002c6aa4
                                    charge(ctx, 3);
                                    v1 = 0x8000;
                                    if (a3 != v1) {
                                        // 0x002c6ab0
                                        charge(ctx, 2);
                                        goto L_002c6b78;
                                    }
                                    // 0x002c6ab8
                                    charge(ctx, 9);
                                    v0 = 1;
                                    sh(v0, s0, 52);
                                    lw(v0, a0, act::kUnit);
                                    lw(a0, v0, unit::kDat);
                                    jal(ctx, 0x2C6AC8u, gen::fn_sub_308930_00308930);
                                    sh(v0, s0, 54);
                                }
                                // 0x002c6b84 (the shared epilogue, written out on this path)
                                charge(ctx, 5);
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_002c6b14:
                            charge(ctx, 4);
                            v1 = 7;
                            sh(v1, s0, 52);
                        }
                    }
                }
            }
        }
    }
    // 0x002c6b84 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C6BA0 sub_2C6BA0 -- 648 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIEvalRow] The unit's AICALC section-15 row (164 bytes per enemy id): for set 0 then set 1, three conditions
// (query words kind << 24 | parameter through the table 0x6971B0; kind 0 = false) and eight answer bytes for the
// combinations c0&c1&c2, c0&c1, c0&c2, c1&c2, c0, c1, c2, always; the first true combination whose answer is not 8
// gives the answer, 0 when none.
// Arguments: a0 btlAction.
void sub_2C6BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c6e00: the epilogue (one copy; every path ends in it)
    auto epilogue = [&] {
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
    };
    // an answer byte (in $v0) that is not 8: the 2-cycle exit blocks 0x2c6ccc, 0x2c6cfc, 0x2c6d2c, 0x2c6d5c, 0x2c6d80,
    // 0x2c6da0, 0x2c6dc4, 0x2c6ddc
    auto answer = [&] {
        charge(ctx, 2);
        epilogue();
    };
    // 0x002c6ba0: s3 = the unit's 164-byte row of AICALC section 15 (by enemy id)
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act::kUnit);
    lhu(v1, v0, unit::kId);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpAiBossRows);  // AICALC.TBL section 15: 164-byte AI rows by enemy id (sub_2C6BA0 / sub_2C6E30) 0x7CE41C
    s3 = addu(v0, v1);
    s5 = 0;
    for (;;) {
        // 0x002c6dec: the two condition sets (s5)
        charge(ctx, 4);
        v0 = s5 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c6bf4: s2 = the set (row + 20 * s5 + 4): three query words, then eight answer bytes at +12..+19
        charge(ctx, 9);
        v1 = s5 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(s3, v0);
        s2 = addiu(v0, 4);
        s4 = 0;
        for (;;) {
            // 0x002c6c88: the three conditions (s4) into the stack words c[0..2] at sp + 0x70
            charge(ctx, 4);
            v0 = s4 & 0xFFFF;
            v0 = slti(v0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c6c18: a query word: kind << 24 | parameter
            charge(ctx, 11);
            v0 = s4 & 0xFFFF;
            s1 = sll(v0, 2);
            v0 = addu(s2, s1);
            lw(a0, v0, 0);
            v0 = lui(0xFF00);
            v0 = a0 & v0;
            v1 = srl(v0, 24);
            a1 = dsll32(a0, 8);
            a1 = dsrl32(a1, 8);
            if (v1 != 0) {
                // 0x002c6c50: condition table 0x6971B0 [kind].fn(action, parameter)
                charge(ctx, 10);
                a0 = s0;
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                v0 = 0x690000;
                v0 = addiu(v0, 29104);  // &0x6971B0
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                jalr(ctx, 0x2C6C70u, v0.u());
            } else {
                // 0x002c6c44: kind 0 = false
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002c6c78
            charge(ctx, 4);
            v1 = addu(s1, sp);
            sw(v0, v1, 112);
            v0 = addiu(s4, 1);
            s4 = v0 & 0xFFFF;
        }
        // the combinations in order -- c0 && c1 && c2 (+12), c0 && c1 (+13), c0 && c2 (+14), c1 && c2 (+15), c0 (+16),
        // c1 (+17), c2 (+18), always (+19) -- the first whose answer byte is not 8
        // 0x002c6c98
        charge(ctx, 3);
        lw(v0, sp, 0x70);
        if (v0 != 0) {
            // 0x002c6ca4
            charge(ctx, 3);
            lw(v0, sp, 0x74);
            if (v0 != 0) {
                // 0x002c6cb0
                charge(ctx, 3);
                lw(v0, sp, 0x78);
                if (v0 != 0) {
                    // 0x002c6cbc
                    charge(ctx, 4);
                    lbu(v0, s2, 12);
                    v1 = 8;
                    if (v0 != v1) {
                        answer();
                        return;
                    }
                }
            }
        }
        // 0x002c6cd4
        charge(ctx, 3);
        lw(v0, sp, 0x70);
        if (v0 != 0) {
            // 0x002c6ce0
            charge(ctx, 3);
            lw(v0, sp, 0x74);
            if (v0 != 0) {
                // 0x002c6cec
                charge(ctx, 4);
                lbu(v0, s2, 13);
                v1 = 8;
                if (v0 != v1) {
                    answer();
                    return;
                }
            }
        }
        // 0x002c6d04
        charge(ctx, 3);
        lw(v0, sp, 0x70);
        if (v0 != 0) {
            // 0x002c6d10
            charge(ctx, 3);
            lw(v0, sp, 0x78);
            if (v0 != 0) {
                // 0x002c6d1c
                charge(ctx, 4);
                lbu(v0, s2, 14);
                v1 = 8;
                if (v0 != v1) {
                    answer();
                    return;
                }
            }
        }
        // 0x002c6d34 (a0 keeps c1 for 0x2c6d88)
        charge(ctx, 3);
        lw(a0, sp, 0x74);
        if (a0 != 0) {
            // 0x002c6d40
            charge(ctx, 3);
            lw(v0, sp, 0x78);
            if (v0 != 0) {
                // 0x002c6d4c
                charge(ctx, 4);
                lbu(v0, s2, 15);
                v1 = 8;
                if (v0 != v1) {
                    answer();
                    return;
                }
            }
        }
        // 0x002c6d64
        charge(ctx, 3);
        lw(v0, sp, 0x70);
        if (v0 != 0) {
            // 0x002c6d70
            charge(ctx, 4);
            lbu(v0, s2, 16);
            v1 = 8;
            if (v0 != v1) {
                answer();
                return;
            }
        }
        // 0x002c6d88
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x002c6d90
            charge(ctx, 4);
            lbu(v0, s2, 17);
            v1 = 8;
            if (v0 != v1) {
                answer();
                return;
            }
        }
        // 0x002c6da8
        charge(ctx, 3);
        lw(v0, sp, 0x78);
        if (v0 != 0) {
            // 0x002c6db4
            charge(ctx, 4);
            lbu(v0, s2, 18);
            v1 = 8;
            if (v0 != v1) {
                answer();
                return;
            }
        }
        // 0x002c6dcc
        charge(ctx, 4);
        lbu(v0, s2, 19);
        v1 = 8;
        if (v0 != v1) {
            answer();
            return;
        }
        // 0x002c6de4: the next set
        charge(ctx, 2);
        v0 = addiu(s5, 1);
        s5 = v0 & 0xFFFF;
    }
    // 0x002c6dfc: no answer
    charge(ctx, 1);
    v0 = 0;
    epilogue();
}

// 0x002C6E30 sub_2C6E30 -- 288 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAIPickRowEntry] Weighted random pick among the five 8-byte entries of a row's set (weights at +44): the entry,
// or the default 0x7CC740 when all weights are 0.
// Arguments: a0 btlAction, a1 set.
void sub_2C6E30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c6e30
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lhu(v1, v0, unit::kId);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpAiBossRows);  // AICALC.TBL section 15: 164-byte AI rows by enemy id (sub_2C6BA0 / sub_2C6E30) 0x7CE41C
    a0 = addu(v0, v1);
    a2 = 0;
    a3 = 0;
    v1 = a1 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    s0 = addu(a0, v0);
    for (;;) {
        // 0x002c6ea4
        charge(ctx, 4);
        v0 = a3 & 0xFFFF;
        v0 = slti(v0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c6e84
        charge(ctx, 8);
        v0 = a3 & 0xFFFF;
        v0 = sll(v0, 3);
        v0 = addu(s0, v0);
        lbu(v0, v0, 44);
        v0 = addu(a2, v0);
        a2 = v0 & 0xFFFF;
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFFFF;
    }
    // 0x002c6eb4
    charge(ctx, 3);
    a0 = a2 & 0xFFFF;
    if (a0 != 0) {
        // 0x002c6ecc
        charge(ctx, 7);
        jal(ctx, 0x2C6ECCu, gen::fn_datCalcRand_002ffbc0);
        a1 = v0 & 0xFFFF;
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x002c6f28
            charge(ctx, 4);
            v0 = a2 & 0xFFFF;
            v0 = slti(v0, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c6ee8
            charge(ctx, 9);
            v0 = a2 & 0xFFFF;
            v0 = sll(v0, 3);
            a0 = addu(s0, v0);
            lbu(v1, a0, 44);
            v0 = addu(a3, v1);
            a3 = v0 & 0xFFFF;
            at = slt(a3, a1);
            if (at == 0) {
                // 0x002c6f0c
                charge(ctx, 2);
                if (i64(v1) <= 0) {
                    goto L_002c6f20;
                }
                goto L_002c6f14_8;
            }
        L_002c6f20:
            charge(ctx, 2);
            v0 = addiu(a2, 1);
            a2 = v0 & 0xFFFF;
        }
        // 0x002c6f38
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c6ec0
        charge(ctx, 3);
        v0 = addiu(gp, -26032);  // &0x7CC740
    }
    // 0x002c6f3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_002c6f14_8:
    charge(ctx, 3);
    v0 = addiu(a0, 44);
    // 0x002c6f3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C7250 sub_2C7250 -- 40 bytes; leaf frame (no stack)
// Whether an AI script wait is active (+48 or a task at +76).
// Arguments: a0 work.
void sub_2C7250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c7250
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v0, a0, 48);
    if (v0 == 0) {
        // 0x002c7268
        charge(ctx, 2);
        lw(v0, a0, 76);
        v0 = sltu(0, v0);
    } else {
        // 0x002c725c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c7270 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002C7280 sub_2C7280 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Polls the AI script wait: 1 when there is none or its task ended (then clears it).
// Arguments: a0 work.
void sub_2C7280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c7280
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v0, a0, 48);
    if (v0 != 0) {
        // 0x002c72a8
        charge(ctx, 3);
        lw(a0, s0, 76);
        if (a0 != 0) {
            // 0x002c72c0
            charge(ctx, 4);
            jal(ctx, 0x2C72C0u, gen::fn_kwlnTaskExists_00195460);
            if (v0 != 0) {
                // 0x002c72e4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002c72d0
                charge(ctx, 5);
                sb(zero, s0, 48);
                sw(zero, s0, 76);
                v0 = 1;
            }
        } else {
            // 0x002c72b4
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002c729c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c72e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D0D00 sub_2D0D00 -- 112 bytes; frame 0x10: ra sp+0x0
// AI command: flushes the hero's requests and queues the camera 3 / 4095 and the hero's camera 28.
void sub_2D0D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d0d00
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    jal(ctx, 0x2D0D10u, gen::fn_sub_28A780_0028a780);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2D0D20u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0D30u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    a1 = 28;
    jal(ctx, 0x2D0D44u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0D54u, gen::fn_sub_27ED20_0027ed20);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D1A70 sub_2D1A70 -- 68 bytes; frame 0x10: ra sp+0x0
// 1 when the battle is not over (kFlags 0x80 clear) and sub_2FD7C0 holds.
void sub_2D1A70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1a70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kFlags);
    v0 = v0 & 0x80;
    if (v0 == 0) {
        // 0x002d1a98
        charge(ctx, 3);
        jal(ctx, 0x2D1A98u, gen::fn_sub_2FD7C0_002fd7c0);
        v0 = sltu(0, v0);
    } else {
        // 0x002d1a8c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002d1aa4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D2280 sub_2D2280 -- 184 bytes; leaf frame (no stack)
// [btlGridFromPos] A world position to the battle grid: cell = round((x + 1750) / 25) for x and z (out pointers
// optional).
// Arguments: a0 s16* x, a1 s16* z, a2 f32[3]*.
void sub_2D2280(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d2280
    enter(ctx, 26);  // entry check point + this block's cycles
    v1 = 1750;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, a2, 0);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(t0, f0);
    lwc1(f0, a2, 8);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a3, f0);
    a2 = 25;
    div(t0, a2);
    mflo(v1);
    t2 = dsll32(v1, 16);
    t2 = dsra32(t2, 16);
    div1(a3, a2);
    mflo1(v1);
    t1 = dsll32(v1, 16);
    t1 = dsra32(t1, 16);
    div(t0, a2);
    mfhi(v1);
    at = slti(v1, 13);
    if (at == 0) {
        // 0x002d22e8
        charge(ctx, 3);
        v1 = addiu(t2, 1);
        t2 = dsll32(v1, 16);
        t2 = dsra32(t2, 16);
    }
    // 0x002d22f4
    charge(ctx, 6);
    v1 = 25;
    div(a3, v1);
    mfhi(v1);
    at = slti(v1, 13);
    if (at == 0) {
        // 0x002d230c
        charge(ctx, 3);
        v1 = addiu(t1, 1);
        t1 = dsll32(v1, 16);
        t1 = dsra32(t1, 16);
    }
    // 0x002d2318
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x002d2320
        charge(ctx, 1);
        sh(t2, a0, 0);
    }
    // 0x002d2324
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x002d232c
        charge(ctx, 1);
        sh(t1, a1, 0);
    }
    // 0x002d2330 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D2340 sub_2D2340 -- 292 bytes; leaf frame (no stack)
// [btlGridSetCorners] Writes a unit's four grid corner points from its cell and its size in cells (rounded up).
// Arguments: a0 btlUnit, a1 x, a2 z, f12 size.
void sub_2D2340(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x002d2340
    enter(ctx, 11);  // entry check point + this block's cycles
    cvt_w_s(f0, f12);
    mfc1(t0, f0);
    a3 = 25;
    div(t0, a3);
    mflo(v1);
    t1 = dsll32(v1, 16);
    t1 = dsra32(t1, 16);
    div(t0, a3);
    mfhi(v1);
    if (v1 != 0) {
        // 0x002d236c
        charge(ctx, 3);
        v1 = addiu(t1, 1);
        t1 = dsll32(v1, 16);
        t1 = dsra32(t1, 16);
    }
    // 0x002d2378
    charge(ctx, 59);
    v1 = subu(a1, t1);
    t0 = dsll32(v1, 16);
    t0 = dsra32(t0, 16);
    v1 = subu(a2, t1);
    a3 = dsll32(v1, 16);
    a3 = dsra32(a3, 16);
    v1 = sll(t0, 2);
    a1 = addu(v1, t0);
    v1 = sll(a1, 2);
    v1 = addu(a1, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f3, f0);
    v1 = sll(a3, 2);
    a1 = addu(v1, a3);
    v1 = sll(a1, 2);
    v1 = addu(a1, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f2, f0);
    v1 = dsll32(t1, 16);
    v1 = dsra32(v1, 16);
    v1 = sll(v1, 1);
    a2 = dsll32(v1, 16);
    a2 = dsra32(a2, 16);
    v1 = addu(t0, a2);
    a1 = dsll32(v1, 16);
    a1 = dsra32(a1, 16);
    v1 = addu(a3, a2);
    a2 = dsll32(v1, 16);
    a2 = dsra32(a2, 16);
    v1 = sll(a1, 2);
    a1 = addu(v1, a1);
    v1 = sll(a1, 2);
    v1 = addu(a1, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    v1 = sll(a2, 2);
    a1 = addu(v1, a2);
    v1 = sll(a1, 2);
    v1 = addu(a1, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f3, a0, 1284);
    swc1(f2, a0, 1288);
    swc1(f1, a0, 1588);
    swc1(f2, a0, 1592);
    swc1(f1, a0, 1892);
    swc1(f0, a0, 1896);
    swc1(f3, a0, 2196);
    swc1(f0, a0, 2200);
}

// 0x002D2990 sub_2D2990 -- 108 bytes; leaf frame (no stack)
// [btlGridSide] Side of a point against a segment on the grid plane: the sign of the 2D cross product (-1 / 0 / 1).
// Arguments: a0 / a1 / a2 f32[2]*.
void sub_2D2990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x002d2990
    enter(ctx, 16);  // entry check point + this block's cycles
    lwc1(f1, a0, 0);
    lwc1(f4, a0, 4);
    lwc1(f0, a1, 4);
    sub_s(f3, f0, f4);
    lwc1(f0, a2, 0);
    sub_s(f2, f0, f1);
    lwc1(f0, a1, 0);
    sub_s(f1, f0, f1);
    lwc1(f0, a2, 4);
    sub_s(f0, f0, f4);
    mula_s(f1, f0);
    mtc1(zero, f0);
    msub_s(f1, f3, f2);
    c_le_s(f1, f0);
    if (cond(ctx)) {
        // 0x002d29dc
        charge(ctx, 4);
        c_lt_s(f1, f0);
        v0 = 1;
        if (!cond(ctx)) {
            // 0x002d29ec
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x002d29f0
        charge(ctx, 1);
        v0 = subu(0, v0);
    } else {
        // 0x002d29d0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002d29f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D3E00 sub_2D3E00 -- 476 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlGridPlaceUnit] Places a unit on the grid: its cell from its position, the corners, optionally the cell centre,
// the size; links its grid record into gBtl's list.
// Arguments: a0 btlUnit, a1 f32[3]* out.
void sub_2D3E00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d3e00
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x2D3E20u, gen::fn_sub_27FFB0_0027ffb0);
    lwc1(f1, s1, unit::kRadius);
    lwc1(f0, s1, unit::kScale);
    mul_s(f20, f1, f0);
    v0 = 1750;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x40);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    lwc1(f0, sp, 0x48);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    v1 = 25;
    div(a1, v1);
    mflo(v0);
    a3 = dsll32(v0, 16);
    a3 = dsra32(a3, 16);
    div1(a0, v1);
    mflo1(v0);
    a2 = dsll32(v0, 16);
    a2 = dsra32(a2, 16);
    div(a1, v1);
    mfhi(v0);
    at = slti(v0, 13);
    if (at == 0) {
        // 0x002d3e9c
        charge(ctx, 3);
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
    }
    // 0x002d3ea8
    charge(ctx, 6);
    v0 = 25;
    div(a0, v0);
    mfhi(v0);
    at = slti(v0, 13);
    if (at == 0) {
        // 0x002d3ec0
        charge(ctx, 3);
        v0 = addiu(a2, 1);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
    }
    // 0x002d3ecc
    charge(ctx, 3);
    v0 = addiu(sp, 0x4E);
    if (v0 != 0) {
        // 0x002d3ed8
        charge(ctx, 1);
        sh(a3, sp, 0x4E);
    }
    // 0x002d3edc
    charge(ctx, 3);
    v0 = addiu(sp, 0x4C);
    if (v0 != 0) {
        // 0x002d3ee8
        charge(ctx, 1);
        sh(a2, sp, 0x4C);
    }
    // 0x002d3eec
    charge(ctx, 8);
    a0 = s1;
    lh(a1, sp, 0x4E);
    lh(a2, sp, 0x4C);
    mov_s(f12, f20);
    jal(ctx, 0x2D3EFCu, gen::fn_sub_2D2340_002d2340);
    if (s0 != 0) {
        // 0x002d3f0c
        charge(ctx, 21);
        lh(a0, sp, 0x4E);
        v1 = sll(a0, 2);
        a0 = addu(v1, a0);
        v1 = sll(a0, 2);
        v1 = addu(a0, v1);
        v1 = addiu(v1, -1750);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, s0, 0);
        sw(zero, s0, 4);
        lh(a0, sp, 0x4C);
        v1 = sll(a0, 2);
        a0 = addu(v1, a0);
        v1 = sll(a0, 2);
        v1 = addu(a0, v1);
        v1 = addiu(v1, -1750);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, s0, 8);
    }
    // 0x002d3f60
    charge(ctx, 13);
    lh(v1, sp, 0x4E);
    sh(v1, s1, unit::kGridX);
    lh(v1, sp, 0x4C);
    sh(v1, s1, unit::kGridZ);
    swc1(f20, s1, unit::kGridSize);
    lw(v1, s1, unit::kFlags);
    v1 = v1 | 0x4;
    sw(v1, s1, unit::kFlags);
    sw(zero, s1, unit::kGridMark);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v1, gbtl::kGridList);
    if (a0 == 0) {
        // 0x002d3fb0
        charge(ctx, 1);
        sw(zero, s1, unit::kGridNext);
    } else {
        // 0x002d3f94
        charge(ctx, 7);
        v1 = addiu(s1, 1276);
        sw(v1, a0, 1224);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, v1, gbtl::kGridList);
        sw(v1, s1, unit::kGridNext);
    }
    // 0x002d3fb4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    a0 = addiu(s1, 1276);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(a0, v1, gbtl::kGridList);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002D4040 sub_2D4040 -- 384 bytes; frame 0x40: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [btlGridUpdateUnit] Re-places a placed unit when its cell or size changed: 1 when it moved.
// Arguments: a0 btlUnit.
void sub_2D4040(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002d4040
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lw(v0, a0, unit::kFlags);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x002d4070
        charge(ctx, 32);
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x2D4074u, gen::fn_sub_27FFB0_0027ffb0);
        lwc1(f1, s0, unit::kRadius);
        lwc1(f0, s0, unit::kScale);
        mul_s(f20, f1, f0);
        v0 = 1750;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x30);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        lwc1(f0, sp, 0x38);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v1 = 25;
        div(a1, v1);
        mflo(v0);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        div1(a0, v1);
        mflo1(v0);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        div(a1, v1);
        mfhi(v0);
        at = slti(v0, 13);
        if (at == 0) {
            // 0x002d40f0
            charge(ctx, 3);
            v0 = addiu(a3, 1);
            a3 = dsll32(v0, 16);
            a3 = dsra32(a3, 16);
        }
        // 0x002d40fc
        charge(ctx, 6);
        v0 = 25;
        div(a0, v0);
        mfhi(v0);
        at = slti(v0, 13);
        if (at == 0) {
            // 0x002d4114
            charge(ctx, 3);
            v0 = addiu(a2, 1);
            a2 = dsll32(v0, 16);
            a2 = dsra32(a2, 16);
        }
        // 0x002d4120
        charge(ctx, 3);
        v0 = addiu(sp, 0x3E);
        if (v0 != 0) {
            // 0x002d412c
            charge(ctx, 1);
            sh(a3, sp, 0x3E);
        }
        // 0x002d4130
        charge(ctx, 3);
        v0 = addiu(sp, 0x3C);
        if (v0 != 0) {
            // 0x002d413c
            charge(ctx, 1);
            sh(a2, sp, 0x3C);
        }
        // 0x002d4140
        charge(ctx, 4);
        lh(a1, sp, 0x3E);
        lh(v0, s0, unit::kGridX);
        if (v0 == a1) {
            // 0x002d4150
            charge(ctx, 4);
            lh(v1, s0, unit::kGridZ);
            lh(v0, sp, 0x3C);
            if (v1 != v0) {
                goto L_002d4170;
            }
            // 0x002d4160
            charge(ctx, 4);
            lwc1(f0, s0, unit::kGridSize);
            c_eq_s(f0, f20);
            if (!cond(ctx)) {
                goto L_002d4170;
            }
            // 0x002d41a4
            charge(ctx, 1);
            v0 = 0;
            // 0x002d41a8 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_002d4170:
        charge(ctx, 13);
        a0 = s0;
        lh(a2, sp, 0x3C);
        mov_s(f12, f20);
        jal(ctx, 0x2D417Cu, gen::fn_sub_2D2340_002d2340);
        lh(v0, sp, 0x3E);
        sh(v0, s0, 1276);
        lh(v0, sp, 0x3C);
        sh(v0, s0, 1278);
        swc1(f20, s0, 1280);
        v0 = 1;
    } else {
        // 0x002d4064
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002d41a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002D4ED0 sub_2D4ED0 -- 484 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlEscapeRoll] The escape roll: encounter 469 escapes only when no entry of the sub_1756F0 / sub_174A90 list has
// id 76, 468 always; otherwise nothing while gBtl kEscRowA is 0, then ENCOUNT flag 2 never / 4 always, the hero's own
// turn always, else datCalcRand(100) < AICALC section 6 [kEscRowA - 1 (max 8)] + [9 + kEscRowB - 1 (max 5)] (a zero
// kEscRowB adds nothing).
// Arguments: a0 btlAction.
void sub_2D4ED0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d4ed0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kSetupEnemies);
    lhu(a2, v1, 8);
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    a1 = sll(v1, 2);
    lw(v1, gp, kGpEncountTbl);  // gEncountTbl
    a1 = addu(v1, a1);
    v1 = 469;
    if (a2 == v1) {
        // 0x002d4f2c
        charge(ctx, 6);
        jal(ctx, 0x2D4F2Cu, gen::fn_sub_1756F0_001756f0);
        s0 = v0 & 0xFFFF;
        s1 = 0;
        for (;;) {
            // 0x002d4f68
            charge(ctx, 3);
            v0 = slt(s1, s0);
            if (v0 != 0) {
                backedge(ctx);
                // 0x002d4f44
                charge(ctx, 8);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x2D4F4Cu, gen::fn_sub_174A90_00174a90);
                lhu(v1, v0, 2);
                v0 = 76;
                if (v1 != v0) {
                    // 0x002d4f64
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x002d4f74
        charge(ctx, 2);
        if (s1 != s0) {
            // 0x002d4f88
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x002d4f7c
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002d4f0c
        charge(ctx, 3);
        v1 = 468;
        if (a2 == v1) {
            // 0x002d4f20
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x002d4f18
            charge(ctx, 2);
            // 0x002d4f94
            charge(ctx, 3);
            lhu(a2, v0, gbtl::kEscRowA);
            if (a2 != 0) {
                // 0x002d4fac
                charge(ctx, 4);
                lw(a1, a1, 0);
                v1 = a1 & 0x2;
                if (v1 == 0) {
                    // 0x002d4fc8
                    charge(ctx, 3);
                    v1 = a1 & 0x4;
                    if (v1 == 0) {
                        // 0x002d4fe0
                        charge(ctx, 3);
                        lw(v1, v0, gbtl::kPlayerAction);
                        if (v1 != a0) {
                            // 0x002d4ff8
                            charge(ctx, 3);
                            s0 = 0;
                            if (i64(a2) > 0) {
                                // 0x002d5004
                                charge(ctx, 5);
                                v1 = addiu(a2, -1);
                                a0 = v1 & 0xFFFF;
                                v1 = slti(a0, 9);
                                if (v1 == 0) {
                                    // 0x002d5018
                                    charge(ctx, 1);
                                    a0 = 8;
                                }
                                // 0x002d501c
                                charge(ctx, 6);
                                a0 = a0 & 0xFFFF;
                                lw(v1, gp, kGpAiEscape);  // AICALC.TBL section 6: escape chance rows (9 by round + 6 by attempt) 0x7CE488
                                v1 = addu(v1, a0);
                                lbu(v1, v1, 0);
                                v1 = addu(s0, v1);
                                s0 = v1 & 0xFFFF;
                            }
                            // 0x002d5034
                            charge(ctx, 3);
                            lhu(v0, v0, gbtl::kEscRowB);
                            if (i64(v0) > 0) {
                                // 0x002d5040
                                charge(ctx, 5);
                                v0 = addiu(v0, -1);
                                a0 = v0 & 0xFFFF;
                                v0 = slti(a0, 6);
                                if (v0 == 0) {
                                    // 0x002d5054
                                    charge(ctx, 1);
                                    a0 = 5;
                                }
                                // 0x002d5058
                                charge(ctx, 6);
                                lw(v1, gp, kGpAiEscape);  // AICALC.TBL section 6: escape chance rows (9 by round + 6 by attempt) 0x7CE488
                                v0 = a0 & 0xFFFF;
                                v0 = addu(v0, v1);
                                lbu(v0, v0, 9);
                                v0 = addu(s0, v0);
                                s0 = v0 & 0xFFFF;
                            }
                            // 0x002d5070
                            charge(ctx, 7);
                            a0 = 100;
                            jal(ctx, 0x2D5074u, gen::fn_datCalcRand_002ffbc0);
                            v1 = s0 & 0xFFFF;
                            at = sltu(v0, v1);
                            if (at == 0) {
                                // 0x002d5098
                                charge(ctx, 1);
                                v0 = 0;
                            } else {
                                // 0x002d508c
                                charge(ctx, 3);
                                v0 = 1;
                            }
                        } else {
                            // 0x002d4fec
                            charge(ctx, 3);
                            v0 = 1;
                        }
                    } else {
                        // 0x002d4fd4
                        charge(ctx, 3);
                        v0 = 1;
                    }
                } else {
                    // 0x002d4fbc
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002d4fa0
                charge(ctx, 3);
                v0 = 0;
            }
        }
    }
    // 0x002d509c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D50C0 sub_2D50C0 -- 1168 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAdvantageRoll] The advantage roll at the battle start (stored in gBtl kAdvantage): 0 normal, 1 the party
// strikes first, 2 the enemies strike first. Encounter 506 with flag 4889 -> 2; ENCOUNT flags 0x8 -> 0, 0x10 -> 2, 0x800 -> 1; setup flag 4 ->
// 0; setup flag 1: c = 20 * party mean level / enemy mean level (halved when a party unit has skill 560), 2 with flag
// 4889, else datCalcRand(100) < c ? 0 : 2; setup flag 2: 0 without flag 4889 or with setup flag 8, else c = 20 *
// enemy mean / party mean and datCalcRand(100) <= c ? 2 : 0; neither flag -> 1.
void sub_2D50C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002d50c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 506;
    if (v1 == v0) {
        // 0x002d50ec
        charge(ctx, 5);
        a0 = 4889;
        jal(ctx, 0x2D50F0u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            goto L_002d510c;
        }
        // 0x002d5100
        charge(ctx, 3);
        v0 = 2;
        // 0x002d5534 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_002d510c:
    charge(ctx, 13);
    s2 = 0;
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, a0, gbtl::kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpEncountTbl);  // gEncountTbl
    v0 = addu(v0, v1);
    lw(v1, v0, 0);
    v0 = v1 & 0x8;
    if (v0 == 0) {
        // 0x002d514c
        charge(ctx, 3);
        v0 = v1 & 0x10;
        if (v0 == 0) {
            // 0x002d5164
            charge(ctx, 3);
            v0 = v1 & 0x800;
            if (v0 == 0) {
                // 0x002d517c
                charge(ctx, 4);
                lhu(v0, a0, gbtl::kSetupFlags);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x002d5198
                    charge(ctx, 3);
                    lw(s0, a0, gbtl::kUnitHead0);
                    for (;;) {
                        // 0x002d51d4
                        charge(ctx, 2);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002d51a4
                        charge(ctx, 3);
                        lw(a0, s0, unit::kDat);
                        if (a0 != 0) {
                            // 0x002d51b0
                            charge(ctx, 5);
                            a1 = 560;
                            jal(ctx, 0x2D51B4u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 == 0) {
                                goto L_002d51d0;
                            }
                            goto L_002d51c4_14;
                        }
                    L_002d51d0:
                        charge(ctx, 1);
                        lw(s0, s0, unit::kNext);
                    }
                L_002d51dc:
                    charge(ctx, 15);
                    a0 = 1;
                    a1 = 0;
                    jal(ctx, 0x2D51E4u, gen::fn_btlGetMeanLevel_002d4cf0);
                    s1 = v0 & 0xFFFF;
                    a0 = 2;
                    a1 = 0;
                    jal(ctx, 0x2D51F8u, gen::fn_btlGetMeanLevel_002d4cf0);
                    s0 = v0 & 0xFFFF;
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lhu(v1, v0, gbtl::kSetupFlags);
                    v0 = v1 & 0x1;
                    if (v0 == 0) {
                        // 0x002d53e0
                        charge(ctx, 3);
                        v0 = v1 & 0x2;
                        if (v0 == 0) {
                            // 0x002d5530
                            charge(ctx, 1);
                            v0 = 1;
                        } else {
                            // 0x002d53ec
                            charge(ctx, 5);
                            a0 = 4889;
                            jal(ctx, 0x2D53F0u, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x002d5400
                                charge(ctx, 5);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lhu(v0, v0, gbtl::kSetupFlags);
                                v0 = v0 & 0x8;
                                if (v0 != 0) {
                                    goto L_002d5524;
                                }
                                // 0x002d5414
                                charge(ctx, 2);
                                if (i64(s0) < 0) {
                                    // 0x002d5430
                                    charge(ctx, 7);
                                    v1 = srl(s0, 1);
                                    v0 = s0 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f1, f0);
                                    add_s(f1, f1, f1);
                                } else {
                                    // 0x002d541c
                                    charge(ctx, 5);
                                    mtc1(s0, f0);
                                    cvt_s_w(f1, f0);
                                }
                                // 0x002d544c
                                charge(ctx, 2);
                                if (i64(s1) < 0) {
                                    // 0x002d5468
                                    charge(ctx, 7);
                                    v1 = srl(s1, 1);
                                    v0 = s1 & 0x1;
                                    v1 = v1 | v0;
                                    mtc1(v1, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f0, f0, f0);
                                } else {
                                    // 0x002d5454
                                    charge(ctx, 5);
                                    mtc1(s1, f0);
                                    cvt_s_w(f0, f0);
                                }
                                // 0x002d5484
                                charge(ctx, 13);
                                div_s(f1, f1, f0);
                                v0 = 0x41A00000;
                                mtc1(v0, f0);
                                mul_s(f1, f0, f1);
                                v0 = 0x4F000000;
                                mtc1(v0, f0);
                                c_le_s(f0, f1);
                                if (cond(ctx)) {
                                    // 0x002d54d0
                                    charge(ctx, 6);
                                    sub_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(v1, f0);
                                    v0 = lui(0x8000);
                                    v1 = v1 | v0;
                                    v1 = v1 & 0xFFFF;
                                } else {
                                    // 0x002d54b8
                                    charge(ctx, 6);
                                    cvt_w_s(f0, f1);
                                    mfc1(v1, f0);
                                    v1 = v1 & 0xFFFF;
                                }
                                // 0x002d54e8
                                charge(ctx, 8);
                                s0 = v1 & 0xFFFF;
                                a0 = 100;
                                jal(ctx, 0x2D54F0u, gen::fn_datCalcRand_002ffbc0);
                                v1 = s0 & 0xFFFF;
                                at = sltu(v1, v0);
                                if (at == 0) {
                                    // 0x002d5514
                                    charge(ctx, 1);
                                    v0 = 2;
                                } else {
                                    // 0x002d5508
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x002d5518
                                charge(ctx, 3);
                                v0 = v0 & 0xFFFF;
                                // 0x002d5534 (the shared epilogue, written out on this path)
                                charge(ctx, 7);
                                ld(ra, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x40);
                                return;
                            }
                        L_002d5524:
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    } else {
                        // 0x002d5218
                        charge(ctx, 2);
                        if (i64(s1) < 0) {
                            // 0x002d5234
                            charge(ctx, 7);
                            v1 = srl(s1, 1);
                            v0 = s1 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x002d5220
                            charge(ctx, 5);
                            mtc1(s1, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x002d5250
                        charge(ctx, 2);
                        if (i64(s0) < 0) {
                            // 0x002d526c
                            charge(ctx, 7);
                            v1 = srl(s0, 1);
                            v0 = s0 & 0x1;
                            v1 = v1 | v0;
                            mtc1(v1, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x002d5258
                            charge(ctx, 5);
                            mtc1(s0, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x002d5288
                        charge(ctx, 13);
                        div_s(f1, f1, f0);
                        v0 = 0x41A00000;
                        mtc1(v0, f0);
                        mul_s(f1, f0, f1);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x002d52d4
                            charge(ctx, 6);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                            v1 = v1 & 0xFFFF;
                        } else {
                            // 0x002d52bc
                            charge(ctx, 6);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                            v1 = v1 & 0xFFFF;
                        }
                        // 0x002d52ec
                        charge(ctx, 3);
                        s0 = v1 & 0xFFFF;
                        if (s2 != 0) {
                            // 0x002d52f8
                            charge(ctx, 4);
                            v0 = 0x3F000000;
                            mtc1(v0, f1);
                            if (i64(s0) < 0) {
                                // 0x002d531c
                                charge(ctx, 7);
                                v1 = srl(s0, 1);
                                v0 = s0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f0, f0);
                                add_s(f0, f0, f0);
                            } else {
                                // 0x002d5308
                                charge(ctx, 5);
                                mtc1(s0, f0);
                                cvt_s_w(f0, f0);
                            }
                            // 0x002d5338
                            charge(ctx, 7);
                            mul_s(f1, f1, f0);
                            v0 = 0x4F000000;
                            mtc1(v0, f0);
                            c_le_s(f0, f1);
                            if (cond(ctx)) {
                                // 0x002d536c
                                charge(ctx, 6);
                                sub_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(v1, f0);
                                v0 = lui(0x8000);
                                v1 = v1 | v0;
                                v1 = v1 & 0xFFFF;
                            } else {
                                // 0x002d5354
                                charge(ctx, 6);
                                cvt_w_s(f0, f1);
                                mfc1(v1, f0);
                                v1 = v1 & 0xFFFF;
                            }
                            // 0x002d5384
                            charge(ctx, 1);
                            s0 = v1 & 0xFFFF;
                        }
                        // 0x002d5388
                        charge(ctx, 5);
                        a0 = 4889;
                        jal(ctx, 0x2D538Cu, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            // 0x002d53a8
                            charge(ctx, 7);
                            a0 = 100;
                            jal(ctx, 0x2D53ACu, gen::fn_datCalcRand_002ffbc0);
                            v1 = s0 & 0xFFFF;
                            at = sltu(v0, v1);
                            if (at == 0) {
                                // 0x002d53d0
                                charge(ctx, 1);
                                v0 = 2;
                            } else {
                                // 0x002d53c4
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x002d53d4
                            charge(ctx, 3);
                            v0 = v0 & 0xFFFF;
                        } else {
                            // 0x002d539c
                            charge(ctx, 3);
                            v0 = 2;
                        }
                    }
                } else {
                    // 0x002d518c
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002d5170
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x002d5158
            charge(ctx, 3);
            v0 = 2;
        }
    } else {
        // 0x002d5140
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002d5534 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_002d51c4_14:
    charge(ctx, 3);
    s2 = 1;
    goto L_002d51dc;
}

// 0x002D5570 sub_2D5570 -- 296 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlEnemyPickVariant] A Tartarus shadow's variant: enemy 277 becomes one of eight (256..262, 265) at random, 274
// becomes 290 with 5 %; -1 otherwise.
// Arguments: a0 enemy id.
void sub_2D5570(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d5570
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = slti(a0, 272);
    if (v0 == 0) {
        // 0x002d5588
        charge(ctx, 3);
        at = slti(a0, 305);
        if (at == 0) {
            goto L_002d5594;
        }
        // 0x002d55a0
        charge(ctx, 4);
        s0 = si(-1);
        v0 = 277;
        if (a0 != v0) {
            // 0x002d55b0
            charge(ctx, 3);
            v0 = 274;
            if (a0 == v0) {
                // 0x002d55c4
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2D55C8u, gen::fn_datCalcRand_002ffbc0);
                at = slti(v0, 5);
                if (at != 0) {
                    // 0x002d55dc
                    charge(ctx, 3);
                    s0 = 290;
                }
            } else {
                // 0x002d55bc
                charge(ctx, 2);
            }
            goto L_002d567c;
        }
        // 0x002d55e8
        charge(ctx, 6);
        a0 = 8;
        jal(ctx, 0x2D55ECu, gen::fn_datCalcRand_002ffbc0);
        at = sltiu(v0, 8);
        if (at == 0) {
        L_002d567c:
            charge(ctx, 2);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
        } else {
            // 0x002d5600
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32128);  // &0x7B7D80
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D561Cu:  // table[0]
                // 0x002d561c
                charge(ctx, 3);
                v0 = 256;
                break;
            case 0x2D5628u:  // table[1]
                // 0x002d5628
                charge(ctx, 3);
                v0 = 257;
                break;
            case 0x2D5634u:  // table[2]
                // 0x002d5634
                charge(ctx, 3);
                v0 = 258;
                break;
            case 0x2D5640u:  // table[3]
                // 0x002d5640
                charge(ctx, 3);
                v0 = 259;
                break;
            case 0x2D564Cu:  // table[4]
                // 0x002d564c
                charge(ctx, 3);
                v0 = 260;
                break;
            case 0x2D5658u:  // table[5]
                // 0x002d5658
                charge(ctx, 3);
                v0 = 261;
                break;
            case 0x2D5664u:  // table[6]
                // 0x002d5664
                charge(ctx, 3);
                v0 = 262;
                break;
            case 0x2D5670u:  // table[7]
                // 0x002d5670
                charge(ctx, 3);
                v0 = 265;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x002d5684 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_002d5594:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d5684 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D56A0 sub_2D56A0 -- 1192 bytes; leaf frame (no stack)
// [btlEnemyGetVoiceSet] Enemy id -> its sound / voice set (a compare ladder; 0 for none).
// Arguments: a0 enemy id.
void sub_2D56A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d56a0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 331;
    if (a0 == v0) {
        // 0x002d5b30
        charge(ctx, 3);
        v0 = 152;
    } else {
        // 0x002d56ac
        charge(ctx, 3);
        v0 = 330;
        if (a0 == v0) {
            // 0x002d5b24
            charge(ctx, 3);
            v0 = 150;
        } else {
            // 0x002d56b8
            charge(ctx, 3);
            v0 = 329;
            if (a0 == v0) {
                // 0x002d5b18
                charge(ctx, 3);
                v0 = 148;
            } else {
                // 0x002d56c4
                charge(ctx, 3);
                v0 = 328;
                if (a0 == v0) {
                    // 0x002d5b0c
                    charge(ctx, 3);
                    v0 = 146;
                } else {
                    // 0x002d56d0
                    charge(ctx, 3);
                    v0 = 327;
                    if (a0 == v0) {
                        // 0x002d5b00
                        charge(ctx, 3);
                        v0 = 144;
                    } else {
                        // 0x002d56dc
                        charge(ctx, 3);
                        v0 = 103;
                        if (a0 != v0) {
                            // 0x002d56e8
                            charge(ctx, 3);
                            v0 = 102;
                            if (a0 == v0) {
                                goto L_002d5af4;
                            }
                            // 0x002d56f4
                            charge(ctx, 3);
                            v1 = 368;
                            if (a0 == v1) {
                                // 0x002d5ae8
                                charge(ctx, 3);
                                v0 = 164;
                            } else {
                                // 0x002d5700
                                charge(ctx, 3);
                                v1 = 308;
                                if (a0 == v1) {
                                    // 0x002d5adc
                                    charge(ctx, 3);
                                    v0 = 134;
                                } else {
                                    // 0x002d570c
                                    charge(ctx, 3);
                                    v1 = 290;
                                    if (a0 == v1) {
                                        // 0x002d5ad0
                                        charge(ctx, 3);
                                        v0 = 132;
                                    } else {
                                        // 0x002d5718
                                        charge(ctx, 3);
                                        v1 = 288;
                                        if (a0 == v1) {
                                            // 0x002d5ac4
                                            charge(ctx, 3);
                                            v0 = 174;
                                        } else {
                                            // 0x002d5724
                                            charge(ctx, 3);
                                            v1 = 270;
                                            if (a0 == v1) {
                                                // 0x002d5ab8
                                                charge(ctx, 3);
                                                v0 = 130;
                                            } else {
                                                // 0x002d5730
                                                charge(ctx, 3);
                                                v1 = 269;
                                                if (a0 == v1) {
                                                    // 0x002d5aac
                                                    charge(ctx, 3);
                                                    v0 = 128;
                                                } else {
                                                    // 0x002d573c
                                                    charge(ctx, 3);
                                                    v1 = 268;
                                                    if (a0 == v1) {
                                                        // 0x002d5aa0
                                                        charge(ctx, 3);
                                                        v0 = 126;
                                                    } else {
                                                        // 0x002d5748
                                                        charge(ctx, 3);
                                                        v1 = 267;
                                                        if (a0 == v1) {
                                                            // 0x002d5a94
                                                            charge(ctx, 3);
                                                            v0 = 124;
                                                        } else {
                                                            // 0x002d5754
                                                            charge(ctx, 3);
                                                            v1 = 266;
                                                            if (a0 == v1) {
                                                                // 0x002d5a88
                                                                charge(ctx, 3);
                                                                v0 = 122;
                                                            } else {
                                                                // 0x002d5760
                                                                charge(ctx, 3);
                                                                v1 = 265;
                                                                if (a0 == v1) {
                                                                    // 0x002d5a7c
                                                                    charge(ctx, 3);
                                                                    v0 = 118;
                                                                } else {
                                                                    // 0x002d576c
                                                                    charge(ctx, 3);
                                                                    v1 = 264;
                                                                    if (a0 == v1) {
                                                                        // 0x002d5a70
                                                                        charge(ctx, 3);
                                                                        v0 = 116;
                                                                    } else {
                                                                        // 0x002d5778
                                                                        charge(ctx, 3);
                                                                        v1 = 263;
                                                                        if (a0 == v1) {
                                                                            // 0x002d5a64
                                                                            charge(ctx, 3);
                                                                            v0 = 114;
                                                                        } else {
                                                                            // 0x002d5784
                                                                            charge(ctx, 3);
                                                                            v1 = 262;
                                                                            if (a0 == v1) {
                                                                                // 0x002d5a58
                                                                                charge(ctx, 3);
                                                                                v0 = 112;
                                                                            } else {
                                                                                // 0x002d5790
                                                                                charge(ctx, 3);
                                                                                v1 = 261;
                                                                                if (a0 == v1) {
                                                                                    // 0x002d5a4c
                                                                                    charge(ctx, 3);
                                                                                    v0 = 110;
                                                                                } else {
                                                                                    // 0x002d579c
                                                                                    charge(ctx, 3);
                                                                                    v1 = 260;
                                                                                    if (a0 == v1) {
                                                                                        // 0x002d5a40
                                                                                        charge(ctx, 3);
                                                                                        v0 = 108;
                                                                                    } else {
                                                                                        // 0x002d57a8
                                                                                        charge(ctx, 3);
                                                                                        v1 = 259;
                                                                                        if (a0 == v1) {
                                                                                            // 0x002d5a34
                                                                                            charge(ctx, 3);
                                                                                            v0 = 106;
                                                                                        } else {
                                                                                            // 0x002d57b4
                                                                                            charge(ctx, 3);
                                                                                            v1 = 258;
                                                                                            if (a0 == v1) {
                                                                                                // 0x002d5a28
                                                                                                charge(ctx, 3);
                                                                                                v0 = 104;
                                                                                            } else {
                                                                                                // 0x002d57c0
                                                                                                charge(ctx, 3);
                                                                                                v1 = 257;
                                                                                                if (a0 == v1) {
                                                                                                    // 0x002d5a20
                                                                                                    charge(ctx, 2);
                                                                                                } else {
                                                                                                    // 0x002d57cc
                                                                                                    charge(ctx, 3);
                                                                                                    v0 = 256;
                                                                                                    if (a0 == v0) {
                                                                                                        // 0x002d5a14
                                                                                                        charge(ctx, 3);
                                                                                                        v0 = 100;
                                                                                                    } else {
                                                                                                        // 0x002d57d8
                                                                                                        charge(ctx, 3);
                                                                                                        v0 = 232;
                                                                                                        if (a0 == v0) {
                                                                                                            // 0x002d5a08
                                                                                                            charge(ctx, 3);
                                                                                                            v0 = 170;
                                                                                                        } else {
                                                                                                            // 0x002d57e4
                                                                                                            charge(ctx, 3);
                                                                                                            v0 = 231;
                                                                                                            if (a0 == v0) {
                                                                                                                // 0x002d59fc
                                                                                                                charge(ctx, 3);
                                                                                                                v0 = 172;
                                                                                                            } else {
                                                                                                                // 0x002d57f0
                                                                                                                charge(ctx, 3);
                                                                                                                v0 = 230;
                                                                                                                if (a0 == v0) {
                                                                                                                    // 0x002d59f0
                                                                                                                    charge(ctx, 3);
                                                                                                                    v0 = 168;
                                                                                                                } else {
                                                                                                                    // 0x002d57fc
                                                                                                                    charge(ctx, 3);
                                                                                                                    v0 = 229;
                                                                                                                    if (a0 == v0) {
                                                                                                                        // 0x002d59e4
                                                                                                                        charge(ctx, 3);
                                                                                                                        v0 = 166;
                                                                                                                    } else {
                                                                                                                        // 0x002d5808
                                                                                                                        charge(ctx, 3);
                                                                                                                        v0 = 279;
                                                                                                                        if (a0 == v0) {
                                                                                                                            // 0x002d59d8
                                                                                                                            charge(ctx, 3);
                                                                                                                            v0 = 88;
                                                                                                                        } else {
                                                                                                                            // 0x002d5814
                                                                                                                            charge(ctx, 3);
                                                                                                                            v0 = 276;
                                                                                                                            if (a0 == v0) {
                                                                                                                                // 0x002d59cc
                                                                                                                                charge(ctx, 3);
                                                                                                                                v0 = 86;
                                                                                                                            } else {
                                                                                                                                // 0x002d5820
                                                                                                                                charge(ctx, 3);
                                                                                                                                v0 = 275;
                                                                                                                                if (a0 == v0) {
                                                                                                                                    // 0x002d59c0
                                                                                                                                    charge(ctx, 3);
                                                                                                                                    v0 = 84;
                                                                                                                                } else {
                                                                                                                                    // 0x002d582c
                                                                                                                                    charge(ctx, 3);
                                                                                                                                    v0 = 74;
                                                                                                                                    if (a0 != v0) {
                                                                                                                                        // 0x002d5838
                                                                                                                                        charge(ctx, 3);
                                                                                                                                        v0 = 73;
                                                                                                                                        if (a0 == v0) {
                                                                                                                                            goto L_002d59b4;
                                                                                                                                        }
                                                                                                                                        // 0x002d5844
                                                                                                                                        charge(ctx, 3);
                                                                                                                                        v0 = 221;
                                                                                                                                        if (a0 == v0) {
                                                                                                                                            // 0x002d59a8
                                                                                                                                            charge(ctx, 3);
                                                                                                                                            v0 = 160;
                                                                                                                                        } else {
                                                                                                                                            // 0x002d5850
                                                                                                                                            charge(ctx, 3);
                                                                                                                                            v0 = 220;
                                                                                                                                            if (a0 == v0) {
                                                                                                                                                // 0x002d599c
                                                                                                                                                charge(ctx, 3);
                                                                                                                                                v0 = 158;
                                                                                                                                            } else {
                                                                                                                                                // 0x002d585c
                                                                                                                                                charge(ctx, 3);
                                                                                                                                                v0 = 227;
                                                                                                                                                if (a0 == v0) {
                                                                                                                                                    // 0x002d5990
                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                    v0 = 80;
                                                                                                                                                } else {
                                                                                                                                                    // 0x002d5868
                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                    v0 = 226;
                                                                                                                                                    if (a0 == v0) {
                                                                                                                                                        // 0x002d5984
                                                                                                                                                        charge(ctx, 3);
                                                                                                                                                        v0 = 78;
                                                                                                                                                    } else {
                                                                                                                                                        // 0x002d5874
                                                                                                                                                        charge(ctx, 3);
                                                                                                                                                        v0 = 212;
                                                                                                                                                        if (a0 == v0) {
                                                                                                                                                            // 0x002d5978
                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                            v0 = 156;
                                                                                                                                                        } else {
                                                                                                                                                            // 0x002d5880
                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                            v0 = 211;
                                                                                                                                                            if (a0 != v0) {
                                                                                                                                                                // 0x002d588c
                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                v0 = 210;
                                                                                                                                                                if (a0 == v0) {
                                                                                                                                                                    goto L_002d596c;
                                                                                                                                                                }
                                                                                                                                                                // 0x002d5898
                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                v0 = 209;
                                                                                                                                                                if (a0 != v0) {
                                                                                                                                                                    // 0x002d58a4
                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                    v0 = 208;
                                                                                                                                                                    if (a0 == v0) {
                                                                                                                                                                        goto L_002d5960;
                                                                                                                                                                    }
                                                                                                                                                                    // 0x002d58b0
                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                    v0 = 207;
                                                                                                                                                                    if (a0 != v0) {
                                                                                                                                                                        // 0x002d58bc
                                                                                                                                                                        charge(ctx, 3);
                                                                                                                                                                        v0 = 206;
                                                                                                                                                                        if (a0 == v0) {
                                                                                                                                                                            goto L_002d5954;
                                                                                                                                                                        }
                                                                                                                                                                        // 0x002d58c8
                                                                                                                                                                        charge(ctx, 3);
                                                                                                                                                                        v0 = 223;
                                                                                                                                                                        if (a0 == v0) {
                                                                                                                                                                            // 0x002d5948
                                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                                            v0 = 154;
                                                                                                                                                                        } else {
                                                                                                                                                                            // 0x002d58d4
                                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                                            v0 = 219;
                                                                                                                                                                            if (a0 != v0) {
                                                                                                                                                                                // 0x002d58e0
                                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                                v0 = 218;
                                                                                                                                                                                if (a0 == v0) {
                                                                                                                                                                                    goto L_002d593c;
                                                                                                                                                                                }
                                                                                                                                                                                // 0x002d58ec
                                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                                v0 = 217;
                                                                                                                                                                                if (a0 != v0) {
                                                                                                                                                                                    // 0x002d58f8
                                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                                    v0 = 216;
                                                                                                                                                                                    if (a0 == v0) {
                                                                                                                                                                                        goto L_002d5930;
                                                                                                                                                                                    }
                                                                                                                                                                                    // 0x002d5904
                                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                                    v0 = 215;
                                                                                                                                                                                    if (a0 != v0) {
                                                                                                                                                                                        // 0x002d5910
                                                                                                                                                                                        charge(ctx, 3);
                                                                                                                                                                                        v0 = 214;
                                                                                                                                                                                        if (a0 == v0) {
                                                                                                                                                                                            goto L_002d5924;
                                                                                                                                                                                        }
                                                                                                                                                                                        // 0x002d591c
                                                                                                                                                                                        charge(ctx, 2);
                                                                                                                                                                                        // 0x002d5b3c
                                                                                                                                                                                        charge(ctx, 1);
                                                                                                                                                                                        v0 = 0;
                                                                                                                                                                                        // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                                        charge(ctx, 2);
                                                                                                                                                                                        return;
                                                                                                                                                                                    }
                                                                                                                                                                                L_002d5924:
                                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                                    v0 = 72;
                                                                                                                                                                                    // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                                    charge(ctx, 2);
                                                                                                                                                                                    return;
                                                                                                                                                                                }
                                                                                                                                                                            L_002d5930:
                                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                                v0 = 74;
                                                                                                                                                                                // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                                charge(ctx, 2);
                                                                                                                                                                                return;
                                                                                                                                                                            }
                                                                                                                                                                        L_002d593c:
                                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                                            v0 = 76;
                                                                                                                                                                        }
                                                                                                                                                                        // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                        charge(ctx, 2);
                                                                                                                                                                        return;
                                                                                                                                                                    }
                                                                                                                                                                L_002d5954:
                                                                                                                                                                    charge(ctx, 3);
                                                                                                                                                                    v0 = 138;
                                                                                                                                                                    // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                    charge(ctx, 2);
                                                                                                                                                                    return;
                                                                                                                                                                }
                                                                                                                                                            L_002d5960:
                                                                                                                                                                charge(ctx, 3);
                                                                                                                                                                v0 = 140;
                                                                                                                                                                // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                                                charge(ctx, 2);
                                                                                                                                                                return;
                                                                                                                                                            }
                                                                                                                                                        L_002d596c:
                                                                                                                                                            charge(ctx, 3);
                                                                                                                                                            v0 = 142;
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        // 0x002d5b40 (the shared epilogue, written out on this path)
                                                                                                                                        charge(ctx, 2);
                                                                                                                                        return;
                                                                                                                                    }
                                                                                                                                L_002d59b4:
                                                                                                                                    charge(ctx, 3);
                                                                                                                                    v0 = 82;
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
                            // 0x002d5b40 (the shared epilogue, written out on this path)
                            charge(ctx, 2);
                            return;
                        }
                    L_002d5af4:
                        charge(ctx, 3);
                        v0 = 68;
                    }
                }
            }
        }
    }
    // 0x002d5b40 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D6290 sub_2D6290 -- 60 bytes; frame 0x10: ra sp+0x0
// 1 when sub_2BFF60 returns 0 (a single-target command).
void sub_2D6290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d6290
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, 110);
    a2 = v0;
    a1 = 0;
    a3 = 0;
    jal(ctx, 0x2D62A8u, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D6460 sub_2D6460 -- 440 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlResultGetReaction] The hit-reaction kind of a result: miss / dodge (-2), down 8, dead 2, knocked down 10, a
// guard (22 / -4), a weak hit (22 / -3), a counter (18 / 2), the boss reaction 19.
// Arguments: a0 btlAction, a1 result, a2 kind, a3, t0 counter.
void sub_2D6460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d6460
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = si(-1);
    lw(a0, a1, 8);
    if (a0 == 0) {
        // 0x002d6484
        charge(ctx, 6);
        lw(v1, a1, 16);
        v0 = 0x3C0000;
        v0 = v0 | 0x2AA;  // &0x3C02AA
        v0 = v1 & v0;
        if (v0 != 0) {
            goto L_002d649c;
        }
        goto L_002d64a0;
    }
L_002d649c:
    charge(ctx, 1);
    s0 = si(-2);
L_002d64a0:
    charge(ctx, 4);
    v1 = 0x100000;
    v0 = a0 & v1;
    if (v0 == 0) {
        // 0x002d64bc
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (i64(v0) >= 0) {
            // 0x002d64c8
            charge(ctx, 4);
            v0 = 0x80000;
            v0 = a0 & v0;
            if (v0 != 0) {
                goto L_002d64d8;
            }
            // 0x002d64e4
            charge(ctx, 4);
            lw(v0, a1, 12);
            v0 = v0 & v1;
            if (v0 != 0) {
                // 0x002d64f4
                charge(ctx, 1);
                s0 = 10;
            }
            goto L_002d64f8;
        }
    L_002d64d8:
        charge(ctx, 3);
        s0 = 2;
    } else {
        // 0x002d64b0
        charge(ctx, 3);
        s0 = 8;
    }
L_002d64f8:
    charge(ctx, 4);
    v1 = a2 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        // 0x002d6508
        charge(ctx, 3);
        v0 = 4;
        if (v1 == v0) {
            goto L_002d651c;
        }
        // 0x002d6514
        charge(ctx, 2);
        goto L_002d6548;
    }
L_002d651c:
    charge(ctx, 5);
    lw(v0, s1, act::kUnit);
    lw(v0, v0, unit::kFlags);
    v0 = v0 & 0x80;
    if (v0 == 0) {
        // 0x002d653c
        charge(ctx, 1);
        v0 = si(-4);
    } else {
        // 0x002d6530
        charge(ctx, 3);
        v0 = 22;
    }
    // 0x002d6540
    charge(ctx, 2);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
L_002d6548:
    charge(ctx, 4);
    lhu(v0, a1, 26);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x002d6558
        charge(ctx, 5);
        lw(v0, s1, act::kUnit);
        lw(v0, v0, unit::kFlags);
        v0 = v0 & 0x80;
        if (v0 == 0) {
            // 0x002d6578
            charge(ctx, 1);
            v0 = si(-3);
        } else {
            // 0x002d656c
            charge(ctx, 3);
            v0 = 22;
        }
        // 0x002d657c
        charge(ctx, 2);
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
    }
    // 0x002d6584
    charge(ctx, 2);
    if (t0 != 0) {
        // 0x002d658c
        charge(ctx, 5);
        lw(v0, s1, act::kUnit);
        lw(v0, v0, unit::kFlags);
        v0 = v0 & 0x20;
        if (v0 == 0) {
            // 0x002d65ac
            charge(ctx, 1);
            v0 = 2;
        } else {
            // 0x002d65a0
            charge(ctx, 3);
            v0 = 18;
        }
        // 0x002d65b0
        charge(ctx, 2);
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
    }
    // 0x002d65b8
    charge(ctx, 5);
    lw(v0, a1, 12);
    a1 = 0x80000;
    v0 = v0 & a1;
    if (v0 != 0) {
        // 0x002d65cc
        charge(ctx, 6);
        lw(v0, s1, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2D65D4u, gen::fn_datCalcChkBadStatus_00300580);
        if (v0 != 0) {
            // 0x002d65e4
            charge(ctx, 5);
            lw(v0, s1, act::kUnit);
            lw(v0, v0, unit::kFlags);
            v0 = v0 & 0x200;
            if (v0 != 0) {
                // 0x002d65f8
                charge(ctx, 1);
                s0 = 19;
            }
        }
    }
    // 0x002d65fc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D7FB0 sub_2D7FB0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates packet 1793 (8 bytes: the action, a byte).
// Arguments: a0 btlAction, a1 byte.
void sub_2D7FB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d7fb0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 1793;
    a1 = 8;
    jal(ctx, 0x2D7FD0u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2D0000;
    v1 = addiu(v1, 32496);  // &sub_2D7EF0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2D0000;
    v1 = addiu(v1, 32528);  // &sub_2D7F10
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x2D0000;
    v1 = addiu(v1, 32656);  // &sub_2D7F90
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s1, v1, 0);
    sb(s0, v1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D8040 sub_2D8040 -- 48 bytes; frame 0x10: ra sp+0x0
// Update of packet 1795: sub_302C50 on the action's DatUnit. Done at once.
// Arguments: a0 packet data.
void sub_2D8040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8040
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 0);
    lw(v0, v0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2D8054u, gen::fn_sub_302C50_00302c50);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D8090 sub_2D8090 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates packet 1795 (4 bytes: the action).
// Arguments: a0 btlAction.
void sub_2D8090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8090
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1795;
    a1 = 4;
    jal(ctx, 0x2D80A8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -32736);  // &sub_2D8020
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, -32704);  // &sub_2D8040
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x2E0000;
    v1 = addiu(v1, -32656);  // &sub_2D8070
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D8110 sub_2D8110 -- 504 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionPktUpdatePayCost] Update of the cost packet 1794: an item command uses up the item (the hero's stock or
// the member's 12 slots); a skill pays its cost (sub_3083F0) from SP or HP by the skill's cost kind (+3). Done at
// once.
// Arguments: a0 packet data {action}.
void sub_2D8110(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8110
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a0, 0);
    lw(s1, a1, act::kUnit);
    lhu(v1, a1, act::kCmdKind);
    a0 = 1;
    if (v1 != a0) {
        // 0x002d813c
        charge(ctx, 3);
        v0 = 9;
        if (v1 != v0) {
            // 0x002d8148
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x002d81f8
                charge(ctx, 3);
                lbu(v0, s1, unit::kSide);
                if (v0 == 0) {
                    // 0x002d8204
                    charge(ctx, 5);
                    lhu(v1, a1, act::kCmdItem);
                    lw(v0, s1, unit::kDat);
                    lhu(v0, v0, dat::kId);
                    if (v0 != a0) {
                        // 0x002d825c
                        charge(ctx, 4);
                        s2 = 0;
                        s0 = v1 & 0xFFFF;
                        for (;;) {
                            // 0x002d8298
                            charge(ctx, 4);
                            v0 = s2 & 0xFFFF;
                            v0 = slti(v0, 12);
                            if (v0 != 0) {
                                backedge(ctx);
                                // 0x002d826c
                                charge(ctx, 9);
                                lw(v0, s1, unit::kDat);
                                lh(a0, v0, dat::kId);
                                a1 = dsll32(s2, 16);
                                a1 = dsra32(a1, 16);
                                jal(ctx, 0x2D827Cu, gen::fn_sub_170670_00170670);
                                v0 = v0 & 0xFFFF;
                                if (s0 != v0) {
                                    // 0x002d8290
                                    charge(ctx, 2);
                                    v0 = addiu(s2, 1);
                                    s2 = v0 & 0xFFFF;
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x002d82a8
                        charge(ctx, 16);
                        s0 = dsll32(s2, 16);
                        s0 = dsra32(s0, 16);
                        lw(v0, s1, unit::kDat);
                        lh(a0, v0, dat::kId);
                        a1 = s0;
                        jal(ctx, 0x2D82BCu, gen::fn_sub_1706C0_001706c0);
                        v1 = v0 & 0xFFFF;
                        lw(v0, s1, unit::kDat);
                        lh(a0, v0, dat::kId);
                        v0 = addiu(v1, -1);
                        a2 = dsll32(v0, 16);
                        a2 = dsra32(a2, 16);
                        a1 = s0;
                        jal(ctx, 0x2D82E0u, gen::fn_sub_170710_00170710);
                    } else {
                        // 0x002d8218
                        charge(ctx, 17);
                        s0 = dsll32(v1, 16);
                        s0 = dsra32(s0, 16);
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        a1 = s0;
                        jal(ctx, 0x2D822Cu, gen::fn_sub_170760_00170760);
                        v1 = v0 & 0xFFFF;
                        lw(v0, s1, unit::kDat);
                        lh(a0, v0, dat::kId);
                        v0 = addiu(v1, -1);
                        a2 = v0 & 0xFFFF;
                        a1 = s0;
                        jal(ctx, 0x2D824Cu, gen::fn_sub_170860_00170860);
                    }
                }
            } else {
                // 0x002d8154
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x002d8168
                    charge(ctx, 7);
                    lhu(s0, a1, act::kCmdSkill);
                    lw(a0, s1, unit::kDat);
                    a1 = s0;
                    jal(ctx, 0x2D8174u, gen::fn_sub_3083F0_003083f0);
                    if (v0 != 0) {
                        // 0x002d8184
                        charge(ctx, 12);
                        lw(a1, gp, kGpSkillTbl);  // gBtlSkillTbl
                        a0 = s0 & 0xFFFF;
                        v1 = sll(a0, 2);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a1);
                        lbu(a0, v1, 3);
                        v1 = 2;
                        if (a0 == v1) {
                            // 0x002d81e0
                            charge(ctx, 6);
                            a1 = subu(0, v0);
                            lw(a0, s1, unit::kDat);
                            jal(ctx, 0x2D81E8u, gen::fn_datCalcAddSp_00300480);
                        } else {
                            // 0x002d81b4
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x002d81c8
                                charge(ctx, 6);
                                a1 = subu(0, v0);
                                lw(a0, s1, unit::kDat);
                                jal(ctx, 0x2D81D0u, gen::fn_datCalcAddHp_00300410);
                            } else {
                                // 0x002d81c0
                                charge(ctx, 2);
                            }
                        }
                    }
                } else {
                    // 0x002d8160
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x002d82e8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002D8330 sub_2D8330 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlActionPktCreatePayCost] Creates the cost packet 1794 (4 bytes: the action).
// Arguments: a0 btlAction.
void sub_2D8330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8330
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1794;
    a1 = 4;
    jal(ctx, 0x2D8348u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -32528);  // &sub_2D80F0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, -32496);  // &sub_2D8110
    sw(v1, v0, pkt::kUpdate);
    v1 = 0x2E0000;
    v1 = addiu(v1, -31984);  // &sub_2D8310
    sw(v1, v0, pkt::kOnEnd);
    lw(v1, v0, pkt::kData);
    sw(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D8B40 sub_2D8B40 -- 428 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportLineHeroTurn] Support line picker 15 (the hero's turn): flags 4960..4962 lines, line 108 while gBtl
// kEscRowA is 0, else by HP (> 70 %, 31..70 %, <= 30 %) and the navigator flag sub_2DDC10(6).
// Arguments: a0 btlAction.
void sub_2D8B40(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8b40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kPlayerAction);
    if (v0 == s0) {
        // 0x002d8b70
        charge(ctx, 5);
        a0 = 4962;
        jal(ctx, 0x2D8B74u, gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            // 0x002d8b84
            charge(ctx, 5);
            a0 = 4961;
            jal(ctx, 0x2D8B88u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x002d8ba4
                charge(ctx, 5);
                a0 = 4960;
                jal(ctx, 0x2D8BA8u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    goto L_002d8bc4;
                }
                // 0x002d8bb8
                charge(ctx, 3);
                v0 = 444;
            } else {
                // 0x002d8b98
                charge(ctx, 3);
                v0 = 442;
            }
            // 0x002d8cd4 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_002d8bc4:
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v0, v0, gbtl::kEscRowA);
        if (v0 != 0) {
            // 0x002d8be0
            charge(ctx, 21);
            lw(v0, s0, 48);
            lw(s1, v0, 2604);
            a0 = s1;
            jal(ctx, 0x2D8BECu, gen::fn_datCalcGetHp_002ffd70);
            s0 = v0 & 0xFFFF;
            a0 = s1;
            jal(ctx, 0x2D8BFCu, gen::fn_datCalcGetMaxHp_002ffdf0);
            a0 = v0 & 0xFFFF;
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            div(v0, a0);
            mflo(v1);
            at = slti(v1, 71);
            if (at == 0) {
                // 0x002d8c34
                charge(ctx, 6);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kPlayerAction);
                lw(v0, v0, act::kTurnsTaken);
                at = slti(v0, 3);
                if (at == 0) {
                    goto L_002d8c78;
                }
                // 0x002d8c4c
                charge(ctx, 5);
                a0 = 6;
                jal(ctx, 0x2D8C50u, gen::fn_sub_2DDC10_002ddc10);
                if (v0 != 0) {
                    // 0x002d8c6c
                    charge(ctx, 1);
                    v0 = 209;
                } else {
                    // 0x002d8c60
                    charge(ctx, 3);
                    v0 = 206;
                }
                // 0x002d8c70
                charge(ctx, 2);
                // 0x002d8cd4 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_002d8c78:
            charge(ctx, 3);
            at = slti(v1, 31);
            if (at != 0) {
                // 0x002d8cb0
                charge(ctx, 5);
                a0 = 6;
                jal(ctx, 0x2D8CB4u, gen::fn_sub_2DDC10_002ddc10);
                if (v0 != 0) {
                    // 0x002d8cd0
                    charge(ctx, 1);
                    v0 = 211;
                } else {
                    // 0x002d8cc4
                    charge(ctx, 3);
                    v0 = 208;
                }
            } else {
                // 0x002d8c84
                charge(ctx, 5);
                a0 = 6;
                jal(ctx, 0x2D8C88u, gen::fn_sub_2DDC10_002ddc10);
                if (v0 != 0) {
                    // 0x002d8ca4
                    charge(ctx, 1);
                    v0 = 210;
                } else {
                    // 0x002d8c98
                    charge(ctx, 3);
                    v0 = 207;
                }
                // 0x002d8ca8
                charge(ctx, 2);
            }
        } else {
            // 0x002d8bd4
            charge(ctx, 3);
            v0 = 108;
        }
    } else {
        // 0x002d8b64
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002d8cd4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D8F70 sub_2D8F70 -- 2852 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlSupportLineChain] Support line picker 22 (a member's one-more chain): by party id, the chain count (+40) and
// the living enemies; marks the action voiced (+26 bit 6).
// Arguments: a0 btlAction.
void sub_2D8F70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8f70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002d8f9c
        charge(ctx, 15);
        a0 = 2;
        a1 = 0x80000;
        jal(ctx, 0x2D8FA4u, gen::fn_btlCountActiveUnits_002d4e10);
        v0 = v0 & 0xFFFF;
        lhu(a0, s0, act::kFlags2);
        v1 = a0 & 0x40;
        a1 = sltu(0, v1);
        v1 = a0 | 0x40;
        sh(v1, s0, act::kFlags2);
        lw(v1, s0, act::kUnit);
        lhu(v1, v1, unit::kId);
        at = sltiu(v1, 11);
        if (at != 0) {
            // 0x002d8fd8
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 32400);  // &0x7B7E90
            v1 = sll(v1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x2D8FF4u:  // table[1]
                // 0x002d8ff4
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d9004
                    charge(ctx, 2);
                    if (a1 == 0) {
                        goto L_002d900c;
                    }
                    // 0x002d903c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9078
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d90b4
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d90f0
                                charge(ctx, 3);
                                v0 = si(-1);
                            } else {
                                // 0x002d90c0
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d90cc
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d90d4;
                                    }
                                    // 0x002d90e0
                                    charge(ctx, 4);
                                    v1 = 246;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d90d4:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d9084
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d9090
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d9098;
                                }
                                // 0x002d90a4
                                charge(ctx, 4);
                                v1 = 245;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d9098:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9048
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9054
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d905c;
                            }
                            // 0x002d9068
                            charge(ctx, 4);
                            v1 = 243;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d905c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                    break;
                }
            L_002d900c:
                charge(ctx, 3);
                at = slti(v0, 5);
                if (at != 0) {
                    // 0x002d9018
                    charge(ctx, 2);
                    if (v0 == 0) {
                        goto L_002d9020;
                    }
                    // 0x002d902c
                    charge(ctx, 4);
                    v1 = 240;
                    v0 = subu(v1, v0);
                    break;
                }
            L_002d9020:
                charge(ctx, 3);
                v0 = si(-1);
                break;
            case 0x2D90FCu:  // table[2]
                // 0x002d90fc
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d913c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9178
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d91b4
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d91f0
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9220
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d91fc
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9210
                                        charge(ctx, 2);
                                        v1 = 257;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9204
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9218
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d91c0
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d91cc
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d91d4;
                                    }
                                    // 0x002d91e0
                                    charge(ctx, 4);
                                    v1 = 257;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d91d4:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d9184
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d9190
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d9198;
                                }
                                // 0x002d91a4
                                charge(ctx, 4);
                                v1 = 256;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d9198:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9148
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9154
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d915c;
                            }
                            // 0x002d9168
                            charge(ctx, 4);
                            v1 = 254;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d915c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d910c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9118
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9120;
                        }
                        // 0x002d912c
                        charge(ctx, 4);
                        v1 = 251;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9120:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D922Cu:  // table[3]
                // 0x002d922c
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d926c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d92a8
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d92e4
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d9320
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9350
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d932c
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9340
                                        charge(ctx, 2);
                                        v1 = 268;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9334
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9348
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d92f0
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d92fc
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d9304;
                                    }
                                    // 0x002d9310
                                    charge(ctx, 4);
                                    v1 = 268;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d9304:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d92b4
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d92c0
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d92c8;
                                }
                                // 0x002d92d4
                                charge(ctx, 4);
                                v1 = 267;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d92c8:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9278
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9284
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d928c;
                            }
                            // 0x002d9298
                            charge(ctx, 4);
                            v1 = 265;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d928c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d923c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9248
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9250;
                        }
                        // 0x002d925c
                        charge(ctx, 4);
                        v1 = 262;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9250:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D935Cu:  // table[4]
                // 0x002d935c
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d939c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d93d8
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d9414
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d9450
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9480
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d945c
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9470
                                        charge(ctx, 2);
                                        v1 = 279;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9464
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9478
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d9420
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d942c
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d9434;
                                    }
                                    // 0x002d9440
                                    charge(ctx, 4);
                                    v1 = 279;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d9434:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d93e4
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d93f0
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d93f8;
                                }
                                // 0x002d9404
                                charge(ctx, 4);
                                v1 = 278;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d93f8:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d93a8
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d93b4
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d93bc;
                            }
                            // 0x002d93c8
                            charge(ctx, 4);
                            v1 = 276;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d93bc:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d936c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9378
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9380;
                        }
                        // 0x002d938c
                        charge(ctx, 4);
                        v1 = 273;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9380:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D948Cu:  // table[5]
                // 0x002d948c
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d94cc
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9508
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d9544
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d9580
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d95b0
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d958c
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d95a0
                                        charge(ctx, 2);
                                        v1 = 290;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9594
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d95a8
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d9550
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d955c
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d9564;
                                    }
                                    // 0x002d9570
                                    charge(ctx, 4);
                                    v1 = 290;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d9564:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d9514
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d9520
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d9528;
                                }
                                // 0x002d9534
                                charge(ctx, 4);
                                v1 = 289;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d9528:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d94d8
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d94e4
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d94ec;
                            }
                            // 0x002d94f8
                            charge(ctx, 4);
                            v1 = 287;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d94ec:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d949c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d94a8
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d94b0;
                        }
                        // 0x002d94bc
                        charge(ctx, 4);
                        v1 = 284;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d94b0:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D95BCu:  // table[7]
                // 0x002d95bc
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d95fc
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9638
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d9674
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d96b0
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d96e0
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d96bc
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d96d0
                                        charge(ctx, 2);
                                        v1 = 301;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d96c4
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d96d8
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d9680
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d968c
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d9694;
                                    }
                                    // 0x002d96a0
                                    charge(ctx, 4);
                                    v1 = 301;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d9694:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d9644
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d9650
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d9658;
                                }
                                // 0x002d9664
                                charge(ctx, 4);
                                v1 = 300;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d9658:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9608
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9614
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d961c;
                            }
                            // 0x002d9628
                            charge(ctx, 4);
                            v1 = 298;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d961c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d95cc
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d95d8
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d95e0;
                        }
                        // 0x002d95ec
                        charge(ctx, 4);
                        v1 = 295;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d95e0:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D96ECu:  // table[8]
                // 0x002d96ec
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d972c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9768
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d97a4
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d97e0
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9810
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d97ec
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9800
                                        charge(ctx, 2);
                                        v1 = 312;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d97f4
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9808
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d97b0
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d97bc
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d97c4;
                                    }
                                    // 0x002d97d0
                                    charge(ctx, 4);
                                    v1 = 312;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d97c4:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d9774
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d9780
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d9788;
                                }
                                // 0x002d9794
                                charge(ctx, 4);
                                v1 = 311;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d9788:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9738
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9744
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d974c;
                            }
                            // 0x002d9758
                            charge(ctx, 4);
                            v1 = 309;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d974c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d96fc
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9708
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9710;
                        }
                        // 0x002d971c
                        charge(ctx, 4);
                        v1 = 306;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9710:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D981Cu:  // table[9]
                // 0x002d981c
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d985c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d9898
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d98d4
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d9910
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9940
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d991c
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9930
                                        charge(ctx, 2);
                                        v1 = 323;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9924
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9938
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d98e0
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d98ec
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d98f4;
                                    }
                                    // 0x002d9900
                                    charge(ctx, 4);
                                    v1 = 323;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d98f4:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d98a4
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d98b0
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d98b8;
                                }
                                // 0x002d98c4
                                charge(ctx, 4);
                                v1 = 322;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d98b8:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9868
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d9874
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d987c;
                            }
                            // 0x002d9888
                            charge(ctx, 4);
                            v1 = 320;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d987c:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d982c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9838
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9840;
                        }
                        // 0x002d984c
                        charge(ctx, 4);
                        v1 = 317;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9840:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D994Cu:  // table[10]
                // 0x002d994c
                charge(ctx, 4);
                lbu(a0, s0, act::kOneMore);
                at = slti(a0, 2);
                if (at == 0) {
                    // 0x002d998c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 != v1) {
                        // 0x002d99c8
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 != v1) {
                            // 0x002d9a04
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 != v1) {
                                // 0x002d9a40
                                charge(ctx, 3);
                                v1 = 5;
                                if (a0 != v1) {
                                    // 0x002d9a70
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                } else {
                                    // 0x002d9a4c
                                    charge(ctx, 2);
                                    if (i64(v0) <= 0) {
                                        // 0x002d9a60
                                        charge(ctx, 2);
                                        v1 = 334;
                                        v0 = subu(v1, v0);
                                    } else {
                                        // 0x002d9a54
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                    }
                                    // 0x002d9a68
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x002d9a10
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                if (at != 0) {
                                    // 0x002d9a1c
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        goto L_002d9a24;
                                    }
                                    // 0x002d9a30
                                    charge(ctx, 4);
                                    v1 = 334;
                                    v0 = subu(v1, v0);
                                    break;
                                }
                            L_002d9a24:
                                charge(ctx, 3);
                                v0 = si(-1);
                            }
                        } else {
                            // 0x002d99d4
                            charge(ctx, 3);
                            at = slti(v0, 3);
                            if (at != 0) {
                                // 0x002d99e0
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    goto L_002d99e8;
                                }
                                // 0x002d99f4
                                charge(ctx, 4);
                                v1 = 333;
                                v0 = subu(v1, v0);
                                break;
                            }
                        L_002d99e8:
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                    } else {
                        // 0x002d9998
                        charge(ctx, 3);
                        at = slti(v0, 4);
                        if (at != 0) {
                            // 0x002d99a4
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_002d99ac;
                            }
                            // 0x002d99b8
                            charge(ctx, 4);
                            v1 = 331;
                            v0 = subu(v1, v0);
                            break;
                        }
                    L_002d99ac:
                        charge(ctx, 3);
                        v0 = si(-1);
                    }
                } else {
                    // 0x002d995c
                    charge(ctx, 3);
                    at = slti(v0, 5);
                    if (at != 0) {
                        // 0x002d9968
                        charge(ctx, 2);
                        if (v0 == 0) {
                            goto L_002d9970;
                        }
                        // 0x002d997c
                        charge(ctx, 4);
                        v1 = 328;
                        v0 = subu(v1, v0);
                        break;
                    }
                L_002d9970:
                    charge(ctx, 3);
                    v0 = si(-1);
                }
                break;
            case 0x2D9A7Cu:  // table[0, 6]
            L_002d9a7c:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
            // 0x002d9a80 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
        goto L_002d9a7c;
    }
    // 0x002d8f90
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d9a80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D9CA0 sub_2D9CA0 -- 192 bytes; leaf frame (no stack)
// [btlSupportLineMember] Support line picker 27: a line per party id 2..10 (355..369).
// Arguments: a0 btlAction.
void sub_2D9CA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d9ca0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002d9cbc
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d9ccc
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32544);  // &0x7B7F20
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D9CE8u:  // table[1]
                // 0x002d9ce8
                charge(ctx, 3);
                v0 = si(-1);
                break;
            case 0x2D9CF4u:  // table[2]
                // 0x002d9cf4
                charge(ctx, 3);
                v0 = 355;
                break;
            case 0x2D9D00u:  // table[3]
                // 0x002d9d00
                charge(ctx, 3);
                v0 = 357;
                break;
            case 0x2D9D0Cu:  // table[4]
                // 0x002d9d0c
                charge(ctx, 3);
                v0 = 359;
                break;
            case 0x2D9D18u:  // table[5]
                // 0x002d9d18
                charge(ctx, 3);
                v0 = 361;
                break;
            case 0x2D9D24u:  // table[7]
                // 0x002d9d24
                charge(ctx, 3);
                v0 = 363;
                break;
            case 0x2D9D30u:  // table[8]
                // 0x002d9d30
                charge(ctx, 3);
                v0 = 365;
                break;
            case 0x2D9D3Cu:  // table[9]
                // 0x002d9d3c
                charge(ctx, 3);
                v0 = 367;
                break;
            case 0x2D9D48u:  // table[10]
                // 0x002d9d48
                charge(ctx, 3);
                v0 = 369;
                break;
            case 0x2D9D54u:  // table[0, 6]
            L_002d9d54:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d9d58 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d9d54;
    }
    // 0x002d9cb0
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d9d58 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002DB480 sub_2DB480 -- 456 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportGetPartyState] Party state for the support lines: 0 a live reinforcement without flag bit 0, 2 all live
// reinforcements flagged, 3 a dead party member missing from the battle, else 1.
void sub_2DB480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db480
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s3 = 0;
    s2 = 0;
    s4 = 0;
    for (;;) {
        // 0x002db528
        charge(ctx, 4);
        v0 = s4 & 0xFFFF;
        v0 = sltiu(v0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002db4b4
        charge(ctx, 7);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        v0 = s4 & 0xFFFF;
        s0 = sll(v0, 3);
        v0 = addu(v1, s0);
        lw(a0, v0, 3012);
        if (a0 != 0) {
            // 0x002db4d0
            charge(ctx, 4);
            jal(ctx, 0x2DB4D0u, gen::fn_datUnitIsGenusDead_002ff790);
            if (v0 != 0) {
                goto L_002db520;
            }
            // 0x002db4e0
            charge(ctx, 9);
            v0 = addiu(s1, 1);
            s1 = v0 & 0xFFFF;
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v0 = addu(v0, s0);
            lw(v0, v0, 3012);
            lhu(v0, v0, 10);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                goto L_002db514;
            }
            // 0x002db504
            charge(ctx, 4);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
            goto L_002db520;
        }
    L_002db520:
        charge(ctx, 2);
        v0 = addiu(s4, 1);
        s4 = v0 & 0xFFFF;
    }
    // 0x002db538
    charge(ctx, 3);
    v1 = s1 & 0xFFFF;
    if (v1 != 0) {
        // 0x002db544
        charge(ctx, 3);
        v0 = s3 & 0xFFFF;
        if (v1 != v0) {
            goto L_002db55c;
        }
        // 0x002db550
        charge(ctx, 3);
        v0 = 2;
        // 0x002db624 (the shared epilogue, written out on this path)
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
L_002db55c:
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x002db5ec
        charge(ctx, 4);
        s1 = s0 & 0xFFFF;
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002db568
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x2DB56Cu, gen::fn_sub_16DD60_0016dd60);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        if (a0 != 0) {
            // 0x002db584
            charge(ctx, 4);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, v0, gbtl::kUnitTail0);
            for (;;) {
                // 0x002db5a4
                charge(ctx, 4);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x002db594
                    charge(ctx, 3);
                    lhu(v0, v1, unit::kId);
                    if (v0 != a0) {
                        // 0x002db5a0
                        charge(ctx, 1);
                        lw(v1, v1, unit::kPrev);
                        continue;
                    }
                }
                break;
            }
            // 0x002db5b4
            charge(ctx, 2);
            if (v1 != 0) {
                goto L_002db5e4;
            }
            // 0x002db5bc
            charge(ctx, 10);
            jal(ctx, 0x2DB5BCu, gen::fn_datGetUnit_0016cd60);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x2DB5D4u, gen::fn_datCalcIsDead_0030b5a0);
            if (v0 != 0) {
                goto L_002db5e4;
            }
            break;
        }
    L_002db5e4:
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x002db5fc
    charge(ctx, 3);
    v0 = s2 & 0xFFFF;
    if (i64(v0) > 0) {
        // 0x002db608
        charge(ctx, 3);
        v0 = 4;
        if (s1 != v0) {
            goto L_002db620;
        }
        // 0x002db614
        charge(ctx, 3);
        v0 = 3;
        // 0x002db624 (the shared epilogue, written out on this path)
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
L_002db620:
    charge(ctx, 1);
    v0 = 1;
    // 0x002db624 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002db514:
    charge(ctx, 3);
    v0 = 0;
    // 0x002db624 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002DB740 sub_2DB740 -- 140 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportPktCreateLine] Creates the support line packet 2048 (24 bytes), update sub_2DB6A0.
// Arguments: a0, a1, a2, a3, t0.
void sub_2DB740(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db740
    enter(ctx, 35);  // entry check point + this block's cycles
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
    s0 = t0;
    a0 = 2048;
    a1 = 24;
    jal(ctx, 0x2DB778u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -18784);  // &sub_2DB6A0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s4, v1, 0);
    sh(s3, v1, 4);
    sw(s2, v1, 8);
    sw(s1, v1, 12);
    sw(s0, v1, 16);
    sw(zero, v1, 20);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002DB890 sub_2DB890 -- 52 bytes; frame 0x10: ra sp+0x0
// Creates packet 2050 (no data), update sub_2DB860.
void sub_2DB890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db890
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2050;
    a1 = 0;
    jal(ctx, 0x2DB8A0u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -18336);  // &sub_2DB860
    sw(v1, v0, pkt::kUpdate);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DBFE0 sub_2DBFE0 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates packet 2051 (8 bytes: the mode, 2 in The Answer).
// Arguments: a0 mode.
void sub_2DBFE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dbfe0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 2051;
    a1 = 8;
    jal(ctx, 0x2DC000u, gen::fn_sub_27EC10_0027ec10);
    s1 = v0;
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, -16720);  // &sub_2DBEB0
    sw(v1, v0, pkt::kUpdate);
    lw(s0, v0, pkt::kData);
    jal(ctx, 0x2DC028u, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        // 0x002dc044
        charge(ctx, 1);
        v0 = s2 & 0xFFFF;
    } else {
        // 0x002dc038
        charge(ctx, 3);
        v0 = 2;
    }
    // 0x002dc048 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    sh(v0, s0, 4);
    sh(zero, s0, 6);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DC070 sub_2DC070 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAilmentSkipsTurn] Whether an ailment costs the unit its turn: down (0x100000) -> 1; the ailments 0x37F ->
// datCalcRand(100) < 100 (50 when the low status bits are exactly 8).
// Arguments: a0 btlAction.
void sub_2DC070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dc070
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lw(s1, v0, unit::kDat);
    a0 = s1;
    a1 = 0x100000;
    jal(ctx, 0x2DC090u, gen::fn_datCalcChkBadStatus_00300580);
    if (v0 == 0) {
        // 0x002dc0ac
        charge(ctx, 7);
        a0 = s1;
        v0 = 0x100000;
        a1 = v0 | 0x37F;  // &0x10037F
        jal(ctx, 0x2DC0B8u, gen::fn_datCalcChkBadStatus_00300580);
        if (v0 != 0) {
            // 0x002dc0d4
            charge(ctx, 7);
            s0 = 100;
            a0 = s1;
            jal(ctx, 0x2DC0DCu, gen::fn_datCalcGetBadStatusNoDown_00300530);
            v1 = 8;
            if (v0 == v1) {
                // 0x002dc0f8
                charge(ctx, 1);
                s0 = 50;
            } else {
                // 0x002dc0f0
                charge(ctx, 2);
            }
            // 0x002dc0fc
            charge(ctx, 5);
            a0 = 100;
            jal(ctx, 0x2DC100u, gen::fn_datCalcRand_002ffbc0);
            v1 = s0 & 0xFFFF;
            v0 = sltu(v0, v1);
        } else {
            // 0x002dc0c8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002dc0a0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002dc110 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002DC180 sub_2DC180 -- 976 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAilmentRecoverRoll] The ailment recovery roll: for each status bit a chance (datScriptCalc formulas 8..14, or
// none) and a turn limit (halved by skill 610, 1 with 611); returns the bits that recover this turn (limit reached or
// the roll won).
// Arguments: a0 btlAction.
void sub_2DC180(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002dc180
    enter(ctx, 21);  // entry check point + this block's cycles
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
    s7 = a0;
    lw(s1, a0, act::kUnit);
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2DC1B8u, gen::fn_datCalcGetBadStatus_00300550);
    fp = v0;
    s6 = 0;
    s5 = 0;
    for (;;) {
        // 0x002dc50c
        charge(ctx, 3);
        v0 = sltiu(s5, 24);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002dc1d4
        charge(ctx, 5);
        t0 = 1;
        s0 = sllv(t0, s5);
        v0 = fp & s0;
        if (v0 != 0) {
            // 0x002dc1e8
            charge(ctx, 3);
            v0 = 256;
            if (s0 == v0) {
                // 0x002dc408
                charge(ctx, 5);
                s4 = 0;
                jal(ctx, 0x2DC40Cu, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002dc428
                    charge(ctx, 1);
                    s3 = 4;
                } else {
                    // 0x002dc41c
                    charge(ctx, 3);
                    s3 = 5;
                }
                // 0x002dc42c
                charge(ctx, 4);
                s2 = 1;
                v1 = 0;
            } else {
                // 0x002dc1f4
                charge(ctx, 3);
                v0 = 512;
                if (s0 == v0) {
                    // 0x002dc3f0
                    charge(ctx, 6);
                    s4 = 0;
                    s3 = 3;
                    s2 = t0;
                    v1 = 0;
                } else {
                    // 0x002dc200
                    charge(ctx, 3);
                    v0 = 64;
                    if (s0 == v0) {
                        // 0x002dc3bc
                        charge(ctx, 13);
                        lw(a1, s1, unit::kDat);
                        a0 = 14;
                        a2 = a1;
                        a3 = 0;
                        t0 = v0;
                        jal(ctx, 0x2DC3D0u, gen::fn_datScriptCalc_0030fc40);
                        s4 = v0;
                        s3 = 2;
                        s2 = 0;
                        v1 = 1;
                    } else {
                        // 0x002dc20c
                        charge(ctx, 3);
                        v0 = 32;
                        if (s0 == v0) {
                            // 0x002dc388
                            charge(ctx, 13);
                            lw(a1, s1, unit::kDat);
                            a0 = 13;
                            a2 = a1;
                            a3 = 0;
                            t0 = v0;
                            jal(ctx, 0x2DC39Cu, gen::fn_datScriptCalc_0030fc40);
                            s4 = v0;
                            s3 = 2;
                            s2 = 0;
                            v1 = 1;
                        } else {
                            // 0x002dc218
                            charge(ctx, 3);
                            v1 = 16;
                            if (s0 == v1) {
                                // 0x002dc324
                                charge(ctx, 3);
                                lbu(v0, s7, act::kOneMore);
                                if (v0 == 0) {
                                    // 0x002dc330
                                    charge(ctx, 3);
                                    lbu(v0, s7, 41);
                                    if (v0 != 0) {
                                        goto L_002dc370;
                                    }
                                    // 0x002dc33c
                                    charge(ctx, 13);
                                    lw(a1, s1, unit::kDat);
                                    a0 = 12;
                                    a2 = a1;
                                    a3 = 0;
                                    t0 = v1;
                                    jal(ctx, 0x2DC350u, gen::fn_datScriptCalc_0030fc40);
                                    s4 = v0;
                                    s3 = 4;
                                    s2 = 1;
                                    v1 = s2;
                                    goto L_002dc44c;
                                }
                            L_002dc370:
                                charge(ctx, 6);
                                s4 = 0;
                                s3 = 0;
                                s2 = 1;
                                v1 = 0;
                            } else {
                                // 0x002dc224
                                charge(ctx, 3);
                                v1 = 8;
                                if (s0 == v1) {
                                    // 0x002dc2f0
                                    charge(ctx, 13);
                                    lw(a1, s1, unit::kDat);
                                    a0 = 11;
                                    a2 = a1;
                                    a3 = 0;
                                    t0 = v1;
                                    jal(ctx, 0x2DC304u, gen::fn_datScriptCalc_0030fc40);
                                    s4 = v0;
                                    s3 = 3;
                                    s2 = 1;
                                    v1 = s2;
                                } else {
                                    // 0x002dc230
                                    charge(ctx, 3);
                                    v0 = 4;
                                    if (s0 == v0) {
                                        // 0x002dc2bc
                                        charge(ctx, 13);
                                        lw(a1, s1, unit::kDat);
                                        a0 = 10;
                                        a2 = a1;
                                        a3 = 0;
                                        t0 = v0;
                                        jal(ctx, 0x2DC2D0u, gen::fn_datScriptCalc_0030fc40);
                                        s4 = v0;
                                        s3 = 3;
                                        s2 = 1;
                                        v1 = s2;
                                    } else {
                                        // 0x002dc23c
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (s0 == v0) {
                                            // 0x002dc288
                                            charge(ctx, 13);
                                            lw(a1, s1, unit::kDat);
                                            a0 = 9;
                                            a2 = a1;
                                            a3 = 0;
                                            t0 = v0;
                                            jal(ctx, 0x2DC29Cu, gen::fn_datScriptCalc_0030fc40);
                                            s4 = v0;
                                            s3 = 3;
                                            s2 = 1;
                                            v1 = s2;
                                        } else {
                                            // 0x002dc248
                                            charge(ctx, 2);
                                            if (s0 == t0) {
                                                // 0x002dc258
                                                charge(ctx, 12);
                                                lw(a1, s1, unit::kDat);
                                                a0 = v1;
                                                a2 = a1;
                                                a3 = 0;
                                                jal(ctx, 0x2DC268u, gen::fn_datScriptCalc_0030fc40);
                                                s4 = v0;
                                                s3 = 4;
                                                s2 = 1;
                                                v1 = s2;
                                            } else {
                                                // 0x002dc250
                                                charge(ctx, 2);
                                                // 0x002dc43c
                                                charge(ctx, 4);
                                                s4 = 0;
                                                s3 = 0;
                                                s2 = t0;
                                                v1 = 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        L_002dc44c:
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x002dc458
                charge(ctx, 2);
                if (s3 != 0) {
                    // 0x002dc460
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 610;
                    jal(ctx, 0x2DC468u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x002dc478
                        charge(ctx, 3);
                        s3 = sra(s3, 1);
                        if (i64(s3) <= 0) {
                            // 0x002dc484
                            charge(ctx, 1);
                            s3 = 1;
                        }
                    }
                    // 0x002dc488
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 611;
                    jal(ctx, 0x2DC490u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x002dc4a0
                        charge(ctx, 1);
                        s3 = 1;
                    }
                }
            }
            // 0x002dc4a4
            charge(ctx, 3);
            v0 = 1;
            if (s2 == v0) {
                // 0x002dc4b0
                charge(ctx, 5);
                v0 = addu(s7, s5);
                lbu(v0, v0, 1122);
                at = slti(v0, 2);
                if (at == 0) {
                    goto L_002dc4c4;
                }
                goto L_002dc508;
            }
        L_002dc4c4:
            charge(ctx, 5);
            v0 = addu(s7, s5);
            lbu(v0, v0, 1122);
            v0 = slt(v0, s3);
            if (v0 == 0) {
                // 0x002dc4d8
                charge(ctx, 2);
                if (s3 == 0) {
                    goto L_002dc4ec;
                }
                // 0x002dc4e0
                charge(ctx, 3);
                s6 = s6 | s0;
                goto L_002dc508;
            }
        L_002dc4ec:
            charge(ctx, 6);
            a0 = 100;
            jal(ctx, 0x2DC4F0u, gen::fn_datCalcRand_002ffbc0);
            at = slt(v0, s4);
            if (at != 0) {
                // 0x002dc504
                charge(ctx, 1);
                s6 = s6 | s0;
            }
        }
    L_002dc508:
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x002dc518
    charge(ctx, 14);
    v0 = s6;
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

// 0x002DD100 sub_2DD100 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSoundPktCreate2306] Creates the sound packet 2306 (6 bytes: three ids).
// Arguments: a0, a1, a2.
void sub_2DD100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd100
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 2306;
    a1 = 6;
    jal(ctx, 0x2DD128u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -12368);  // &sub_2DCFB0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, -12256);  // &sub_2DD020
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s2, v1, 0);
    sh(s1, v1, 2);
    sh(s0, v1, 4);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DD4A0 sub_2DD4A0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSoundPktCreate2307] Creates the sound packet 2307 (16 bytes).
// Arguments: a0, a1.
void sub_2DD4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd4a0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 2307;
    a1 = 16;
    jal(ctx, 0x2DD4C0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, -11664);  // &sub_2DD270
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, -11536);  // &sub_2DD2F0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s1, v1, 4);
    sh(s0, v1, 12);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002DD5E0 sub_2DD5E0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlSoundPktCreate2308] Creates the sound packet 2308 (2 bytes).
// Arguments: a0.
void sub_2DD5E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd5e0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2308;
    a1 = 2;
    jal(ctx, 0x2DD5F8u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, -10992);  // &sub_2DD510
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DDC10 sub_2DDC10 -- 104 bytes; frame 0x10: ra sp+0x0
// [btlVoiceGetMemberFlag] The party member's voice flag (table 0x697BD8 by id >= 2; -1 none) through datGetFlag.
// Arguments: a0 party id.
void sub_2DDC10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ddc10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0 & 0xFFFF;
    at = slti(v0, 2);
    if (at == 0) {
        // 0x002ddc34
        charge(ctx, 8);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, 31704);  // &0x697BD8
        v0 = addu(v0, v1);
        lw(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x002ddc60
            charge(ctx, 2);
            jal(ctx, 0x2DDC60u, gen::fn_datGetFlag_0016f190);
        } else {
            // 0x002ddc54
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002ddc28
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002ddc68 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DDC80 sub_2DDC80 -- 308 bytes; frame 0x10: ra sp+0x0
// [btlVoiceIsFirstLineDue] Whether a party member's first-battle line is still due (flags 4951..4958 clear).
// Arguments: a0 party id.
void sub_2DDC80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ddc80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0 & 0xFFFF;
    at = sltiu(v0, 11);
    if (at != 0) {
        // 0x002ddc98
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -32752);  // &0x7B8010
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2DDCB4u:  // table[1]
            // 0x002ddcb4
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x2DDCC0u:  // table[2]
            // 0x002ddcc0
            charge(ctx, 7);
            a0 = 4951;
            jal(ctx, 0x2DDCC4u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDCDCu:  // table[3]
            // 0x002ddcdc
            charge(ctx, 7);
            a0 = 4952;
            jal(ctx, 0x2DDCE0u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDCF8u:  // table[4]
            // 0x002ddcf8
            charge(ctx, 7);
            a0 = 4953;
            jal(ctx, 0x2DDCFCu, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDD14u:  // table[5]
            // 0x002ddd14
            charge(ctx, 7);
            a0 = 4954;
            jal(ctx, 0x2DDD18u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDD30u:  // table[7]
            // 0x002ddd30
            charge(ctx, 7);
            a0 = 4955;
            jal(ctx, 0x2DDD34u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDD4Cu:  // table[8]
            // 0x002ddd4c
            charge(ctx, 7);
            a0 = 4956;
            jal(ctx, 0x2DDD50u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDD68u:  // table[9]
            // 0x002ddd68
            charge(ctx, 7);
            a0 = 4957;
            jal(ctx, 0x2DDD6Cu, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDD84u:  // table[10]
            // 0x002ddd84
            charge(ctx, 7);
            a0 = 4958;
            jal(ctx, 0x2DDD88u, gen::fn_datGetFlag_0016f190);
            // xor v0: a 64-bit move to itself (no effect)
            v0 = sltiu(v0, 1);
            break;
        case 0x2DDDA0u:  // table[0, 6]
        L_002ddda0:
            charge(ctx, 1);
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x002ddda4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    goto L_002ddda0;
}

// 0x002DE150 sub_2DE150 -- 328 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlVoiceLineA] Voice line of a party member (flag 388 required), by id.
// Arguments: a0 btlAction.
void sub_2DE150(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002de150
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 388;
    jal(ctx, 0x2DE164u, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x002de180
        charge(ctx, 4);
        lw(v1, s0, act::kUnit);
        lbu(v0, v1, unit::kSide);
        if (v0 == 0) {
            // 0x002de19c
            charge(ctx, 4);
            lhu(v0, v1, unit::kId);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x002de1ac
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -32560);  // &0x7B80D0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2DE1C8u:  // table[2]
                    // 0x002de1c8
                    charge(ctx, 3);
                    v0 = 174;
                    break;
                case 0x2DE1D4u:  // table[3]
                    // 0x002de1d4
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31716);  // 0x697BE4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de1f4
                        charge(ctx, 2);
                        jal(ctx, 0x2DE1F4u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de1e8
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de1fc
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de210
                        charge(ctx, 1);
                        v0 = 255;
                    } else {
                        // 0x002de204
                        charge(ctx, 3);
                        v0 = 256;
                    }
                    // 0x002de214
                    charge(ctx, 2);
                    break;
                case 0x2DE21Cu:  // table[4]
                    // 0x002de21c
                    charge(ctx, 3);
                    v0 = 356;
                    break;
                case 0x2DE228u:  // table[5]
                    // 0x002de228
                    charge(ctx, 3);
                    v0 = 429;
                    break;
                case 0x2DE234u:  // table[7]
                    // 0x002de234
                    charge(ctx, 3);
                    v0 = 502;
                    break;
                case 0x2DE240u:  // table[8]
                    // 0x002de240
                    charge(ctx, 3);
                    v0 = 575;
                    break;
                case 0x2DE24Cu:  // table[9]
                    // 0x002de24c
                    charge(ctx, 4);
                    jal(ctx, 0x2DE24Cu, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x002de268
                        charge(ctx, 1);
                        v0 = 640;
                    } else {
                        // 0x002de25c
                        charge(ctx, 3);
                        v0 = 1137;
                    }
                    // 0x002de26c
                    charge(ctx, 2);
                    break;
                case 0x2DE274u:  // table[10]
                    // 0x002de274
                    charge(ctx, 3);
                    v0 = 712;
                    break;
                case 0x2DE280u:  // table[0, 1, 6]
                L_002de280:
                    charge(ctx, 1);
                    v0 = si(-1);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                // 0x002de284 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
            goto L_002de280;
        }
        // 0x002de190
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x002de174
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002de284 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DE3C0 sub_2DE3C0 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoiceLineB] Voice line of a party member, by id.
// Arguments: a0 btlAction.
void sub_2DE3C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002de3c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002de3e4
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002de3f4
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -32464);  // &0x7B8130
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2DE410u:  // table[2]
                // 0x002de410
                charge(ctx, 3);
                v0 = 175;
                break;
            case 0x2DE41Cu:  // table[3]
                // 0x002de41c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002de43c
                    charge(ctx, 2);
                    jal(ctx, 0x2DE43Cu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002de430
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002de444
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002de458
                    charge(ctx, 1);
                    v0 = 257;
                } else {
                    // 0x002de44c
                    charge(ctx, 3);
                    v0 = 258;
                }
                // 0x002de45c
                charge(ctx, 2);
                break;
            case 0x2DE464u:  // table[4]
                // 0x002de464
                charge(ctx, 3);
                v0 = 357;
                break;
            case 0x2DE470u:  // table[5]
                // 0x002de470
                charge(ctx, 3);
                v0 = 430;
                break;
            case 0x2DE47Cu:  // table[7]
                // 0x002de47c
                charge(ctx, 3);
                v0 = 503;
                break;
            case 0x2DE488u:  // table[8]
                // 0x002de488
                charge(ctx, 3);
                v0 = 576;
                break;
            case 0x2DE494u:  // table[9]
                // 0x002de494
                charge(ctx, 4);
                jal(ctx, 0x2DE494u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002de4b0
                    charge(ctx, 1);
                    v0 = 641;
                } else {
                    // 0x002de4a4
                    charge(ctx, 3);
                    v0 = 1138;
                }
                // 0x002de4b4
                charge(ctx, 2);
                break;
            case 0x2DE4BCu:  // table[10]
                // 0x002de4bc
                charge(ctx, 3);
                v0 = 713;
                break;
            case 0x2DE4C8u:  // table[0, 1, 6]
            L_002de4c8:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002de4cc (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002de4c8;
    }
    // 0x002de3d8
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002de4cc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DE4E0 sub_2DE4E0 -- 2164 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlVoiceLineTurn] Voice line of a party member's turn by HP (> 70 %, 31..70 %, <= 30 %; tired after 3 turns) and
// the member's flag.
// Arguments: a0 btlAction.
void sub_2DE4E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002de4e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002de514
        charge(ctx, 4);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kPlayerAction);
        if (v0 != s0) {
            // 0x002de530
            charge(ctx, 20);
            lw(s2, v1, unit::kDat);
            a0 = s2;
            jal(ctx, 0x2DE538u, gen::fn_datCalcGetHp_002ffd70);
            s1 = v0 & 0xFFFF;
            a0 = s2;
            jal(ctx, 0x2DE548u, gen::fn_datCalcGetMaxHp_002ffdf0);
            a0 = v0 & 0xFFFF;
            v1 = s1 & 0xFFFF;
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            div(v0, a0);
            mflo(v1);
            at = slti(v1, 71);
            if (at == 0) {
                // 0x002de580
                charge(ctx, 4);
                lw(v0, s0, act::kTurnsTaken);
                at = slti(v0, 3);
                if (at == 0) {
                    goto L_002de818;
                }
                // 0x002de590
                charge(ctx, 5);
                lw(v0, s0, act::kUnit);
                lhu(v0, v0, unit::kId);
                at = sltiu(v0, 11);
                if (at == 0) {
                L_002ded34:
                    charge(ctx, 1);
                    v0 = si(-1);
                } else {
                    // 0x002de5a4
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -32320);  // &0x7B81C0
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2DE5C0u:  // table[2]
                        // 0x002de5c0
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31712);  // 0x697BE0
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de5e0
                            charge(ctx, 2);
                            jal(ctx, 0x2DE5E0u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de5d4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de5e8
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de5fc
                            charge(ctx, 1);
                            v0 = 156;
                        } else {
                            // 0x002de5f0
                            charge(ctx, 3);
                            v0 = 159;
                        }
                        // 0x002de600
                        charge(ctx, 2);
                        break;
                    case 0x2DE608u:  // table[3]
                        // 0x002de608
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31716);  // 0x697BE4
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de628
                            charge(ctx, 2);
                            jal(ctx, 0x2DE628u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de61c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de630
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de644
                            charge(ctx, 1);
                            v0 = 237;
                        } else {
                            // 0x002de638
                            charge(ctx, 3);
                            v0 = 240;
                        }
                        // 0x002de648
                        charge(ctx, 2);
                        break;
                    case 0x2DE650u:  // table[4]
                        // 0x002de650
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31720);  // 0x697BE8
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de670
                            charge(ctx, 2);
                            jal(ctx, 0x2DE670u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de664
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de678
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de68c
                            charge(ctx, 1);
                            v0 = 338;
                        } else {
                            // 0x002de680
                            charge(ctx, 3);
                            v0 = 341;
                        }
                        // 0x002de690
                        charge(ctx, 2);
                        break;
                    case 0x2DE698u:  // table[5]
                        // 0x002de698
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31724);  // 0x697BEC
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de6b8
                            charge(ctx, 2);
                            jal(ctx, 0x2DE6B8u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de6ac
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de6c0
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de6d4
                            charge(ctx, 1);
                            v0 = 411;
                        } else {
                            // 0x002de6c8
                            charge(ctx, 3);
                            v0 = 414;
                        }
                        // 0x002de6d8
                        charge(ctx, 2);
                        break;
                    case 0x2DE6E0u:  // table[7]
                        // 0x002de6e0
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31732);  // 0x697BF4
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de700
                            charge(ctx, 2);
                            jal(ctx, 0x2DE700u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de6f4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de708
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de71c
                            charge(ctx, 1);
                            v0 = 484;
                        } else {
                            // 0x002de710
                            charge(ctx, 3);
                            v0 = 487;
                        }
                        // 0x002de720
                        charge(ctx, 2);
                        break;
                    case 0x2DE728u:  // table[8]
                        // 0x002de728
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31736);  // 0x697BF8
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de748
                            charge(ctx, 2);
                            jal(ctx, 0x2DE748u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de73c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de750
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de764
                            charge(ctx, 1);
                            v0 = 557;
                        } else {
                            // 0x002de758
                            charge(ctx, 3);
                            v0 = 560;
                        }
                        // 0x002de768
                        charge(ctx, 2);
                        break;
                    case 0x2DE770u:  // table[9]
                        // 0x002de770
                        charge(ctx, 4);
                        jal(ctx, 0x2DE770u, gen::fn_sub_17D800_0017d800);
                        if (v0 != 0) {
                            // 0x002de7a8
                            charge(ctx, 5);
                            v0 = 0x690000;
                            lw(a0, v0, 31740);  // 0x697BFC
                            v0 = si(-1);
                            if (a0 != v0) {
                                // 0x002de7bc
                                charge(ctx, 2);
                                jal(ctx, 0x2DE7BCu, gen::fn_datGetFlag_0016f190);
                            }
                            // 0x002de7c4
                            charge(ctx, 3);
                            v0 = 1127;
                        } else {
                            // 0x002de780
                            charge(ctx, 5);
                            v0 = 0x690000;
                            lw(a0, v0, 31740);  // 0x697BFC
                            v0 = si(-1);
                            if (a0 != v0) {
                                // 0x002de794
                                charge(ctx, 2);
                                jal(ctx, 0x2DE794u, gen::fn_datGetFlag_0016f190);
                            }
                            // 0x002de79c
                            charge(ctx, 3);
                            v0 = 630;
                        }
                        break;
                    case 0x2DE7D0u:  // table[10]
                        // 0x002de7d0
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31744);  // 0x697C00
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002de7f0
                            charge(ctx, 2);
                            jal(ctx, 0x2DE7F0u, gen::fn_datGetFlag_0016f190);
                        } else {
                            // 0x002de7e4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x002de7f8
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x002de80c
                            charge(ctx, 1);
                            v0 = 695;
                        } else {
                            // 0x002de800
                            charge(ctx, 3);
                            v0 = 698;
                        }
                        // 0x002de810
                        charge(ctx, 2);
                        break;
                    case 0x2DED34u:  // table[0, 1, 6]
                        goto L_002ded34;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x002ded38 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
        L_002de818:
            charge(ctx, 3);
            at = slti(v1, 31);
            if (at != 0) {
                // 0x002deaac
                charge(ctx, 5);
                lw(v0, s0, 48);
                lhu(v0, v0, 164);
                at = sltiu(v0, 11);
                if (at == 0) {
                    goto L_002ded34;
                }
                // 0x002deac0
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -32416);  // &0x7B8160
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2DEADCu:  // table[2]
                    // 0x002deadc
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31712);  // 0x697BE0
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002deafc
                        charge(ctx, 2);
                        jal(ctx, 0x2DEAFCu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002deaf0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002deb04
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002deb18
                        charge(ctx, 1);
                        v0 = 158;
                    } else {
                        // 0x002deb0c
                        charge(ctx, 3);
                        v0 = 161;
                    }
                    // 0x002deb1c
                    charge(ctx, 2);
                    break;
                case 0x2DEB24u:  // table[3]
                    // 0x002deb24
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31716);  // 0x697BE4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002deb44
                        charge(ctx, 2);
                        jal(ctx, 0x2DEB44u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002deb38
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002deb4c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002deb60
                        charge(ctx, 1);
                        v0 = 239;
                    } else {
                        // 0x002deb54
                        charge(ctx, 3);
                        v0 = 242;
                    }
                    // 0x002deb64
                    charge(ctx, 2);
                    break;
                case 0x2DEB6Cu:  // table[4]
                    // 0x002deb6c
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31720);  // 0x697BE8
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002deb8c
                        charge(ctx, 2);
                        jal(ctx, 0x2DEB8Cu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002deb80
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002deb94
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002deba8
                        charge(ctx, 1);
                        v0 = 340;
                    } else {
                        // 0x002deb9c
                        charge(ctx, 3);
                        v0 = 343;
                    }
                    // 0x002debac
                    charge(ctx, 2);
                    break;
                case 0x2DEBB4u:  // table[5]
                    // 0x002debb4
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31724);  // 0x697BEC
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002debd4
                        charge(ctx, 2);
                        jal(ctx, 0x2DEBD4u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002debc8
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002debdc
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002debf0
                        charge(ctx, 1);
                        v0 = 413;
                    } else {
                        // 0x002debe4
                        charge(ctx, 3);
                        v0 = 416;
                    }
                    // 0x002debf4
                    charge(ctx, 2);
                    break;
                case 0x2DEBFCu:  // table[7]
                    // 0x002debfc
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31732);  // 0x697BF4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002dec1c
                        charge(ctx, 2);
                        jal(ctx, 0x2DEC1Cu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002dec10
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002dec24
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002dec38
                        charge(ctx, 1);
                        v0 = 486;
                    } else {
                        // 0x002dec2c
                        charge(ctx, 3);
                        v0 = 489;
                    }
                    // 0x002dec3c
                    charge(ctx, 2);
                    break;
                case 0x2DEC44u:  // table[8]
                    // 0x002dec44
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31736);  // 0x697BF8
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002dec64
                        charge(ctx, 2);
                        jal(ctx, 0x2DEC64u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002dec58
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002dec6c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002dec80
                        charge(ctx, 1);
                        v0 = 559;
                    } else {
                        // 0x002dec74
                        charge(ctx, 3);
                        v0 = 562;
                    }
                    // 0x002dec84
                    charge(ctx, 2);
                    break;
                case 0x2DEC8Cu:  // table[9]
                    // 0x002dec8c
                    charge(ctx, 4);
                    jal(ctx, 0x2DEC8Cu, gen::fn_sub_17D800_0017d800);
                    if (v0 != 0) {
                        // 0x002decc4
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31740);  // 0x697BFC
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002decd8
                            charge(ctx, 2);
                            jal(ctx, 0x2DECD8u, gen::fn_datGetFlag_0016f190);
                        }
                        // 0x002dece0
                        charge(ctx, 3);
                        v0 = 1129;
                    } else {
                        // 0x002dec9c
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31740);  // 0x697BFC
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002decb0
                            charge(ctx, 2);
                            jal(ctx, 0x2DECB0u, gen::fn_datGetFlag_0016f190);
                        }
                        // 0x002decb8
                        charge(ctx, 3);
                        v0 = 632;
                    }
                    break;
                case 0x2DECECu:  // table[10]
                    // 0x002decec
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31744);  // 0x697C00
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002ded0c
                        charge(ctx, 2);
                        jal(ctx, 0x2DED0Cu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002ded00
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002ded14
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002ded28
                        charge(ctx, 1);
                        v0 = 697;
                    } else {
                        // 0x002ded1c
                        charge(ctx, 3);
                        v0 = 700;
                    }
                    // 0x002ded2c
                    charge(ctx, 2);
                    break;
                case 0x2DED34u:  // table[0, 1, 6]
                    goto L_002ded34;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            } else {
                // 0x002de824
                charge(ctx, 5);
                lw(v0, s0, 48);
                lhu(v0, v0, 164);
                at = sltiu(v0, 11);
                if (at == 0) {
                    goto L_002ded34;
                }
                // 0x002de838
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -32368);  // &0x7B8190
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2DE854u:  // table[2]
                    // 0x002de854
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31712);  // 0x697BE0
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de874
                        charge(ctx, 2);
                        jal(ctx, 0x2DE874u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de868
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de87c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de890
                        charge(ctx, 1);
                        v0 = 157;
                    } else {
                        // 0x002de884
                        charge(ctx, 3);
                        v0 = 160;
                    }
                    // 0x002de894
                    charge(ctx, 2);
                    break;
                case 0x2DE89Cu:  // table[3]
                    // 0x002de89c
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31716);  // 0x697BE4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de8bc
                        charge(ctx, 2);
                        jal(ctx, 0x2DE8BCu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de8b0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de8c4
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de8d8
                        charge(ctx, 1);
                        v0 = 238;
                    } else {
                        // 0x002de8cc
                        charge(ctx, 3);
                        v0 = 241;
                    }
                    // 0x002de8dc
                    charge(ctx, 2);
                    break;
                case 0x2DE8E4u:  // table[4]
                    // 0x002de8e4
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31720);  // 0x697BE8
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de904
                        charge(ctx, 2);
                        jal(ctx, 0x2DE904u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de8f8
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de90c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de920
                        charge(ctx, 1);
                        v0 = 339;
                    } else {
                        // 0x002de914
                        charge(ctx, 3);
                        v0 = 342;
                    }
                    // 0x002de924
                    charge(ctx, 2);
                    break;
                case 0x2DE92Cu:  // table[5]
                    // 0x002de92c
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31724);  // 0x697BEC
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de94c
                        charge(ctx, 2);
                        jal(ctx, 0x2DE94Cu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de940
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de954
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de968
                        charge(ctx, 1);
                        v0 = 412;
                    } else {
                        // 0x002de95c
                        charge(ctx, 3);
                        v0 = 415;
                    }
                    // 0x002de96c
                    charge(ctx, 2);
                    break;
                case 0x2DE974u:  // table[7]
                    // 0x002de974
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31732);  // 0x697BF4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de994
                        charge(ctx, 2);
                        jal(ctx, 0x2DE994u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de988
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de99c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de9b0
                        charge(ctx, 1);
                        v0 = 485;
                    } else {
                        // 0x002de9a4
                        charge(ctx, 3);
                        v0 = 488;
                    }
                    // 0x002de9b4
                    charge(ctx, 2);
                    break;
                case 0x2DE9BCu:  // table[8]
                    // 0x002de9bc
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31736);  // 0x697BF8
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002de9dc
                        charge(ctx, 2);
                        jal(ctx, 0x2DE9DCu, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002de9d0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002de9e4
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002de9f8
                        charge(ctx, 1);
                        v0 = 558;
                    } else {
                        // 0x002de9ec
                        charge(ctx, 3);
                        v0 = 561;
                    }
                    // 0x002de9fc
                    charge(ctx, 2);
                    break;
                case 0x2DEA04u:  // table[9]
                    // 0x002dea04
                    charge(ctx, 4);
                    jal(ctx, 0x2DEA04u, gen::fn_sub_17D800_0017d800);
                    if (v0 != 0) {
                        // 0x002dea3c
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31740);  // 0x697BFC
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002dea50
                            charge(ctx, 2);
                            jal(ctx, 0x2DEA50u, gen::fn_datGetFlag_0016f190);
                        }
                        // 0x002dea58
                        charge(ctx, 3);
                        v0 = 1128;
                    } else {
                        // 0x002dea14
                        charge(ctx, 5);
                        v0 = 0x690000;
                        lw(a0, v0, 31740);  // 0x697BFC
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x002dea28
                            charge(ctx, 2);
                            jal(ctx, 0x2DEA28u, gen::fn_datGetFlag_0016f190);
                        }
                        // 0x002dea30
                        charge(ctx, 3);
                        v0 = 631;
                    }
                    break;
                case 0x2DEA64u:  // table[10]
                    // 0x002dea64
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31744);  // 0x697C00
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002dea84
                        charge(ctx, 2);
                        jal(ctx, 0x2DEA84u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002dea78
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002dea8c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002deaa0
                        charge(ctx, 1);
                        v0 = 696;
                    } else {
                        // 0x002dea94
                        charge(ctx, 3);
                        v0 = 699;
                    }
                    // 0x002deaa4
                    charge(ctx, 2);
                    break;
                case 0x2DED34u:  // table[0, 1, 6]
                    goto L_002ded34;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
        } else {
            // 0x002de524
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002de508
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002ded38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E2A10 sub_2E2A10 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates the sound packet 2560 (8 bytes).
void sub_2E2A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2a10
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2560;
    a1 = 8;
    jal(ctx, 0x2E2A20u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 10528);  // &sub_2E2920
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 0);
    sw(zero, v1, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2BE0 sub_2E2BE0 -- 140 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSoundPktCreateCue] Creates the sound packet 2561 (24 bytes: action, cue, two words, a short).
// Arguments: a0, a1, a2, a3, t0.
void sub_2E2BE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2be0
    enter(ctx, 35);  // entry check point + this block's cycles
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
    s0 = t0;
    a0 = 2561;
    a1 = 24;
    jal(ctx, 0x2E2C18u, gen::fn_sub_27EC10_0027ec10);
    v1 = 0x2E0000;
    v1 = addiu(v1, 10848);  // &sub_2E2A60
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s4, v1, 0);
    sh(s3, v1, 4);
    sw(s2, v1, 8);
    sw(s1, v1, 12);
    sh(s0, v1, 16);
    sw(zero, v1, 20);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002E2EC0 sub_2E2EC0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates the sound packet 2563 (12 bytes).
// Arguments: a0.
void sub_2E2EC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2ec0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2563;
    a1 = 12;
    jal(ctx, 0x2E2ED8u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 11632);  // &sub_2E2D70
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s0, v1, 8);
    sw(zero, v1, 0);
    sw(zero, v1, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E38A0 sub_2E38A0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates the event packet 3075 (2 bytes).
// Arguments: a0.
void sub_2E38A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e38a0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 3075;
    a1 = 2;
    jal(ctx, 0x2E38B8u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 14384);  // &sub_2E3830
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, 14448);  // &sub_2E3870
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E3990 sub_2E3990 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates the event packet 3076 (8 bytes).
void sub_2E3990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3990
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3076;
    a1 = 8;
    jal(ctx, 0x2E39A0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 14592);  // &sub_2E3900
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3A90 sub_2E3A90 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates the event packet 3077 (8 bytes).
void sub_2E3A90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3a90
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3077;
    a1 = 8;
    jal(ctx, 0x2E3AA0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 14816);  // &sub_2E39E0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(zero, v1, 4);
    sh(zero, v1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3B50 sub_2E3B50 -- 144 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the event packet 3078 (16 bytes: three party ids, the all-out portraits).
// Arguments: a0, a1, a2.
void sub_2E3B50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3b50
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 3078;
    a1 = 16;
    jal(ctx, 0x2E3B78u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15072);  // &sub_2E3AE0
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15136);  // &sub_2E3B20
    sw(v1, v0, pkt::kUpdate);
    lw(a0, v0, pkt::kData);
    v1 = s2 & 0xFFFF;
    sw(v1, a0, 0);
    v1 = s1 & 0xFFFF;
    sw(v1, a0, 4);
    v1 = s0 & 0xFFFF;
    sw(v1, a0, 8);
    sh(zero, a0, 12);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E3CD0 sub_2E3CD0 -- 52 bytes; frame 0x10: ra sp+0x0
// Update of packet 3080: destroys gBtl's event task. Done at once.
void sub_2E3CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3cd0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kEventTask);
    jal(ctx, 0x2E3CE0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(zero, v0, gbtl::kEventTask);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3D10 sub_2E3D10 -- 64 bytes; frame 0x10: ra sp+0x0
// Creates packet 3080 (no data).
void sub_2E3D10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3d10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3080;
    a1 = 0;
    jal(ctx, 0x2E3D20u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2E0000;
    v1 = addiu(v1, 15568);  // &sub_2E3CD0
    sw(v1, v0, pkt::kUpdate);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E42C0 sub_2E42C0 -- 32 bytes; frame 0x10: ra sp+0x0
// Returns sub_2FD4A0().
void sub_2E42C0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x002e42c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2E42C8u, gen::fn_sub_2FD4A0_002fd4a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E4520 sub_2E4520 -- 508 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIStatusSkillCheck] Whether a status skill is worth casting on the action's targets: 3 / 5 when every target
// already has every effect bit, 4 when sub_3068D0 gives every target a value, else 0.
// Arguments: a0 btlAction, a1 skill, a2.
void sub_2E4520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4520
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s6 = a2;
    if (i64(s0) > 0) {
        // 0x002e4564
        charge(ctx, 11);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002e459c
            charge(ctx, 5);
            lw(s2, v1, 32);
            v0 = dsll32(s2, 6);
            v0 = dsrl32(v0, 6);
            if (v0 != 0) {
                // 0x002e45b0
                charge(ctx, 4);
                v0 = lui(0xFC00);
                v0 = s2 & v0;
                if (v0 != 0) {
                    goto L_002e4674;
                }
                // 0x002e45c0
                charge(ctx, 3);
                s5 = 0;
                for (;;) {
                    // 0x002e4638
                    charge(ctx, 3);
                    v0 = sltiu(s5, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002e45cc
                    charge(ctx, 5);
                    v0 = 1;
                    s3 = sllv(v0, s5);
                    v0 = s2 & s3;
                    if (v0 != 0) {
                        // 0x002e45e0
                        charge(ctx, 3);
                        s4 = 0;
                        for (;;) {
                            // 0x002e4618
                            charge(ctx, 4);
                            lhu(v0, s1, act::kTargetCount);
                            v0 = sltu(s4, v0);
                            if (v0 != 0) {
                                backedge(ctx);
                                // 0x002e45ec
                                charge(ctx, 10);
                                v0 = sll(s4, 2);
                                v0 = addu(s1, v0);
                                lw(v0, v0, 56);
                                lw(v0, v0, 48);
                                lw(a0, v0, 2604);
                                a1 = s3;
                                jal(ctx, 0x2E4604u, gen::fn_sub_301CA0_00301ca0);
                                if (v0 != 0) {
                                    // 0x002e4614
                                    charge(ctx, 1);
                                    s4 = addiu(s4, 1);
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x002e4628
                        charge(ctx, 3);
                        lhu(v0, s1, act::kTargetCount);
                        if (s4 != v0) {
                            break;
                        }
                        goto L_002e4634;
                    }
                L_002e4634:
                    charge(ctx, 1);
                    s5 = addiu(s5, 1);
                }
                // 0x002e4644
                charge(ctx, 3);
                v0 = 32;
                if (s5 != v0) {
                    goto L_002e4674;
                }
                // 0x002e4650
                charge(ctx, 3);
                v0 = s2 & 0x3000;
                if (v0 == 0) {
                    // 0x002e4668
                    charge(ctx, 1);
                    v0 = 3;
                } else {
                    // 0x002e465c
                    charge(ctx, 3);
                    v0 = 5;
                }
                // 0x002e466c
                charge(ctx, 2);
                // 0x002e46f0 (the shared epilogue, written out on this path)
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
            }
        L_002e4674:
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x002e46c4
                charge(ctx, 4);
                lhu(v0, s1, 106);
                v0 = sltu(s2, v0);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x002e4680
                    charge(ctx, 13);
                    a0 = s0 & 0xFFFF;
                    lw(v1, s1, 48);
                    v0 = sll(s2, 2);
                    v0 = addu(s1, v0);
                    lw(v0, v0, 56);
                    lw(v0, v0, 48);
                    lw(a1, v1, 2604);
                    lw(a2, v0, 2604);
                    a3 = s6;
                    jal(ctx, 0x2E46A4u, gen::fn_sub_3068D0_003068d0);
                    if (v0 != 0) {
                        // 0x002e46b4
                        charge(ctx, 3);
                        v1 = 0xFFFF;
                        if (v0 != v1) {
                            // 0x002e46c0
                            charge(ctx, 1);
                            s2 = addiu(s2, 1);
                            continue;
                        }
                    }
                }
                break;
            }
            // 0x002e46d4
            charge(ctx, 3);
            lhu(v0, s1, 106);
            if (s2 != v0) {
                // 0x002e46ec
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002e46e0
                charge(ctx, 3);
                v0 = 4;
            }
        } else {
            // 0x002e4590
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002e4558
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002e46f0 (the shared epilogue, written out on this path)
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

// 0x002E4720 sub_2E4720 -- 128 bytes; leaf frame (no stack)
// Small id map: 2..6 -> 200..204, 7 -> 217, else 0.
// Arguments: a0 id.
void sub_2E4720(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002e4720
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = a0 & 0xFFFF;
    at = sltiu(v0, 8);
    if (at != 0) {
        // 0x002e4730
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -30336);  // &0x7B8980
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2E474Cu:  // table[2]
            // 0x002e474c
            charge(ctx, 3);
            v0 = 200;
            break;
        case 0x2E4758u:  // table[3]
            // 0x002e4758
            charge(ctx, 3);
            v0 = 201;
            break;
        case 0x2E4764u:  // table[4]
            // 0x002e4764
            charge(ctx, 3);
            v0 = 202;
            break;
        case 0x2E4770u:  // table[5]
            // 0x002e4770
            charge(ctx, 3);
            v0 = 203;
            break;
        case 0x2E477Cu:  // table[6]
            // 0x002e477c
            charge(ctx, 3);
            v0 = 204;
            break;
        case 0x2E4788u:  // table[7]
            // 0x002e4788
            charge(ctx, 3);
            v0 = 217;
            break;
        case 0x2E4794u:  // table[0, 1]
        L_002e4794:
            charge(ctx, 1);
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x002e4798 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    goto L_002e4794;
}

// 0x002E47A0 sub_2E47A0 -- 364 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// As sub_2E4520 without the formula pass: 3 / 7 when every target already has the effect, else 0.
// Arguments: a0 btlAction, a1 skill.
void sub_2E47A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e47a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    if (i64(a1) > 0) {
        // 0x002e47d4
        charge(ctx, 11);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002e480c
            charge(ctx, 5);
            lw(s0, v1, 32);
            v0 = dsll32(s0, 6);
            v0 = dsrl32(v0, 6);
            if (v0 != 0) {
                // 0x002e4820
                charge(ctx, 4);
                v0 = lui(0xFC00);
                v0 = s0 & v0;
                if (v0 != 0) {
                    goto L_002e48e4;
                }
                // 0x002e4830
                charge(ctx, 3);
                s3 = 0;
                for (;;) {
                    // 0x002e48a8
                    charge(ctx, 3);
                    v0 = sltiu(s3, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002e483c
                    charge(ctx, 5);
                    v0 = 1;
                    s1 = sllv(v0, s3);
                    v0 = s0 & s1;
                    if (v0 != 0) {
                        // 0x002e4850
                        charge(ctx, 3);
                        s2 = 0;
                        for (;;) {
                            // 0x002e4888
                            charge(ctx, 4);
                            lhu(v0, s4, act::kTargetCount);
                            v0 = sltu(s2, v0);
                            if (v0 != 0) {
                                backedge(ctx);
                                // 0x002e485c
                                charge(ctx, 10);
                                v0 = sll(s2, 2);
                                v0 = addu(s4, v0);
                                lw(v0, v0, 56);
                                lw(v0, v0, 48);
                                lw(a0, v0, 2604);
                                a1 = s1;
                                jal(ctx, 0x2E4874u, gen::fn_sub_301CA0_00301ca0);
                                if (v0 != 0) {
                                    // 0x002e4884
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 1);
                                    continue;
                                }
                            }
                            break;
                        }
                        // 0x002e4898
                        charge(ctx, 3);
                        lhu(v0, s4, act::kTargetCount);
                        if (s2 != v0) {
                            break;
                        }
                        goto L_002e48a4;
                    }
                L_002e48a4:
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x002e48b4
                charge(ctx, 3);
                v0 = 32;
                if (s3 != v0) {
                    goto L_002e48e4;
                }
                // 0x002e48c0
                charge(ctx, 3);
                v0 = s0 & 0x3000;
                if (v0 == 0) {
                    // 0x002e48d8
                    charge(ctx, 1);
                    v0 = 3;
                } else {
                    // 0x002e48cc
                    charge(ctx, 3);
                    v0 = 7;
                }
                // 0x002e48dc
                charge(ctx, 2);
                // 0x002e48e8 (the shared epilogue, written out on this path)
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
        L_002e48e4:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x002e4800
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002e47c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002e48e8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002E4910 sub_2E4910 -- 288 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// As sub_2E47A0 for the acting unit itself.
// Arguments: a0 btlAction, a1 skill.
void sub_2E4910(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4910
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    if (i64(a1) > 0) {
        // 0x002e493c
        charge(ctx, 11);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002e4974
            charge(ctx, 5);
            lw(s0, v1, 32);
            v0 = dsll32(s0, 6);
            v0 = dsrl32(v0, 6);
            if (v0 != 0) {
                // 0x002e4988
                charge(ctx, 4);
                v0 = lui(0xFC00);
                v0 = s0 & v0;
                if (v0 != 0) {
                    goto L_002e4a10;
                }
                // 0x002e4998
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x002e49d4
                    charge(ctx, 3);
                    v0 = sltiu(s1, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002e49a4
                    charge(ctx, 5);
                    v0 = 1;
                    a1 = sllv(v0, s1);
                    v0 = s0 & a1;
                    if (v0 != 0) {
                        // 0x002e49b8
                        charge(ctx, 6);
                        lw(v0, s2, act::kUnit);
                        lw(a0, v0, unit::kDat);
                        jal(ctx, 0x2E49C0u, gen::fn_sub_301CA0_00301ca0);
                        if (v0 == 0) {
                            break;
                        }
                        goto L_002e49d0;
                    }
                L_002e49d0:
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x002e49e0
                charge(ctx, 3);
                v0 = 32;
                if (s1 != v0) {
                    goto L_002e4a10;
                }
                // 0x002e49ec
                charge(ctx, 3);
                v0 = s0 & 0x3000;
                if (v0 == 0) {
                    // 0x002e4a04
                    charge(ctx, 1);
                    v0 = 3;
                } else {
                    // 0x002e49f8
                    charge(ctx, 3);
                    v0 = 7;
                }
                // 0x002e4a08
                charge(ctx, 2);
                // 0x002e4a14 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
        L_002e4a10:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x002e4968
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002e4930
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002e4a14 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F6C50 sub_2F6C50 -- 432 bytes; leaf frame (no stack)
// [btlBossGetIndex] Boss enemy id -> boss index 0..30 (-1 for none).
// Arguments: a0 enemy id.
void sub_2F6C50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002f6c50
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = a0 & 0xFFFF;
    v0 = addiu(v0, -233);
    at = sltiu(v0, 64);
    if (at != 0) {
        // 0x002f6c64
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -29936);  // &0x7B8B10
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2F6C80u:  // table[23]
            // 0x002f6c80
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x2F6C8Cu:  // table[24]
            // 0x002f6c8c
            charge(ctx, 3);
            v0 = 1;
            break;
        case 0x2F6C98u:  // table[25]
            // 0x002f6c98
            charge(ctx, 3);
            v0 = 2;
            break;
        case 0x2F6CA4u:  // table[26]
            // 0x002f6ca4
            charge(ctx, 3);
            v0 = 3;
            break;
        case 0x2F6CB0u:  // table[27]
            // 0x002f6cb0
            charge(ctx, 3);
            v0 = 4;
            break;
        case 0x2F6CBCu:  // table[28]
            // 0x002f6cbc
            charge(ctx, 3);
            v0 = 5;
            break;
        case 0x2F6CC8u:  // table[29]
            // 0x002f6cc8
            charge(ctx, 3);
            v0 = 6;
            break;
        case 0x2F6CD4u:  // table[30]
            // 0x002f6cd4
            charge(ctx, 3);
            v0 = 8;
            break;
        case 0x2F6CE0u:  // table[31]
            // 0x002f6ce0
            charge(ctx, 3);
            v0 = 14;
            break;
        case 0x2F6CECu:  // table[32]
            // 0x002f6cec
            charge(ctx, 3);
            v0 = 9;
            break;
        case 0x2F6CF8u:  // table[33]
            // 0x002f6cf8
            charge(ctx, 3);
            v0 = 10;
            break;
        case 0x2F6D04u:  // table[34]
            // 0x002f6d04
            charge(ctx, 3);
            v0 = 11;
            break;
        case 0x2F6D10u:  // table[35]
            // 0x002f6d10
            charge(ctx, 3);
            v0 = 12;
            break;
        case 0x2F6D1Cu:  // table[36]
            // 0x002f6d1c
            charge(ctx, 3);
            v0 = 13;
            break;
        case 0x2F6D28u:  // table[38]
            // 0x002f6d28
            charge(ctx, 3);
            v0 = 15;
            break;
        case 0x2F6D34u:  // table[39]
            // 0x002f6d34
            charge(ctx, 3);
            v0 = 16;
            break;
        case 0x2F6D40u:  // table[41]
            // 0x002f6d40
            charge(ctx, 3);
            v0 = 18;
            break;
        case 0x2F6D4Cu:  // table[44]
            // 0x002f6d4c
            charge(ctx, 3);
            v0 = 7;
            break;
        case 0x2F6D58u:  // table[40, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 63]
            // 0x002f6d58
            charge(ctx, 3);
            v0 = 17;
            break;
        case 0x2F6D64u:  // table[61]
            // 0x002f6d64
            charge(ctx, 3);
            v0 = 19;
            break;
        case 0x2F6D70u:  // table[45, 46, 47]
            // 0x002f6d70
            charge(ctx, 3);
            v0 = 20;
            break;
        case 0x2F6D7Cu:  // table[48, 62]
            // 0x002f6d7c
            charge(ctx, 3);
            v0 = 21;
            break;
        case 0x2F6D88u:  // table[0]
            // 0x002f6d88
            charge(ctx, 3);
            v0 = 22;
            break;
        case 0x2F6D94u:  // table[1]
            // 0x002f6d94
            charge(ctx, 3);
            v0 = 23;
            break;
        case 0x2F6DA0u:  // table[2]
            // 0x002f6da0
            charge(ctx, 3);
            v0 = 24;
            break;
        case 0x2F6DACu:  // table[3]
            // 0x002f6dac
            charge(ctx, 3);
            v0 = 25;
            break;
        case 0x2F6DB8u:  // table[4]
            // 0x002f6db8
            charge(ctx, 3);
            v0 = 26;
            break;
        case 0x2F6DC4u:  // table[5]
            // 0x002f6dc4
            charge(ctx, 3);
            v0 = 27;
            break;
        case 0x2F6DD0u:  // table[6]
            // 0x002f6dd0
            charge(ctx, 3);
            v0 = 28;
            break;
        case 0x2F6DDCu:  // table[7]
            // 0x002f6ddc
            charge(ctx, 3);
            v0 = 29;
            break;
        case 0x2F6DE8u:  // table[8]
            // 0x002f6de8
            charge(ctx, 3);
            v0 = 30;
            break;
        case 0x2F6DF4u:  // table[9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 37, 42, 43]
        L_002f6df4:
            charge(ctx, 1);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x002f6df8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    goto L_002f6df4;
}

// 0x002F9BC0 sub_2F9BC0 -- 76 bytes; frame 0x10: ra sp+0x0
// Creates packet 3584 (no data), callbacks sub_2F9710 / sub_2F9B60.
void sub_2F9BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f9bc0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3584;
    a1 = 0;
    jal(ctx, 0x2F9BD0u, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xFE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x300000;
    v1 = addiu(v1, -26864);  // &sub_2F9710
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x300000;
    v1 = addiu(v1, -25760);  // &sub_2F9B60
    sw(v1, v0, pkt::kUpdate);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FA510 sub_2FA510 -- 1344 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlBossScheduleEvent] Boss event scheduler: for the boss encounters 417..436, starts the boss's scripted sequence
// (sub_2E4220 with a pair of callbacks) at the right moment of a boss unit's turn.
// Arguments: a0 btlAction, a1 moment.
void sub_2FA510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fa510
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v1, gbtl::kSetupEnemies);
    lhu(a0, v1, 8);
    v1 = 436;
    if (a0 == v1) {
        // 0x002fa9c4
        charge(ctx, 4);
        lhu(v1, s0, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002fa9d4
            charge(ctx, 5);
            lw(a2, s0, act::kUnit);
            lbu(a0, a2, unit::kSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fa9e8
                charge(ctx, 4);
                lhu(a0, a2, unit::kId);
                v1 = 241;
                if (a0 == v1) {
                    // 0x002faa00
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x002faa08
                        charge(ctx, 4);
                        jal(ctx, 0x2FAA08u, gen::fn_sub_2E4250_002e4250);
                        if (v0 == 0) {
                            // 0x002faa18
                            charge(ctx, 9);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            sw(zero, v0, gbtl::kBossWork2);
                            a0 = 0x2F0000;
                            a0 = addiu(a0, 26688);  // &sub_2F6840
                            a1 = 0x2F0000;
                            a1 = addiu(a1, 27312);  // &sub_2F6AB0
                            a2 = s0;
                            jal(ctx, 0x2FAA34u, gen::fn_sub_2E4220_002e4220);
                        }
                    }
                } else {
                    // 0x002fa9f8
                    charge(ctx, 2);
                }
            }
        }
    } else {
        // 0x002fa538
        charge(ctx, 3);
        v1 = 435;
        if (a0 != v1) {
            // 0x002fa544
            charge(ctx, 3);
            v1 = 434;
            if (a0 == v1) {
                goto L_002fa934;
            }
            // 0x002fa550
            charge(ctx, 3);
            v1 = 433;
            if (a0 == v1) {
                goto L_002fa934;
            }
            // 0x002fa55c
            charge(ctx, 3);
            v1 = 428;
            if (a0 == v1) {
                // 0x002fa894
                charge(ctx, 4);
                lhu(v1, s0, act::kFlags2);
                v1 = v1 & 0x1;
                if (v1 != 0) {
                    // 0x002fa8a4
                    charge(ctx, 5);
                    lw(v1, s0, act::kUnit);
                    lbu(a0, v1, unit::kSide);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x002fa8b8
                        charge(ctx, 4);
                        jal(ctx, 0x2FA8B8u, gen::fn_sub_2E4250_002e4250);
                        if (v0 == 0) {
                            // 0x002fa8c8
                            charge(ctx, 9);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lhu(v0, v0, gbtl::kBossWork1);
                            v1 = sll(v0, 2);
                            v0 = 0x6A0000;
                            v0 = addiu(v0, -24112);  // &0x69A1D0
                            v0 = addu(v0, v1);
                            lhu(v0, v0, 0);
                            if (v0 != 0) {
                                // 0x002fa910
                                charge(ctx, 9);
                                a0 = 0x2F0000;
                                a0 = addiu(a0, 11152);  // &sub_2F2B90
                                a1 = 0x2F0000;
                                a1 = addiu(a1, 12688);  // &sub_2F3190
                                a2 = s0;
                                jal(ctx, 0x2FA924u, gen::fn_sub_2E4220_002e4220);
                            } else {
                                // 0x002fa8ec
                                charge(ctx, 9);
                                a0 = 0x2F0000;
                                a0 = addiu(a0, 13088);  // &sub_2F3320
                                a1 = 0x2F0000;
                                a1 = addiu(a1, 13600);  // &sub_2F3520
                                a2 = s0;
                                jal(ctx, 0x2FA900u, gen::fn_sub_2E4220_002e4220);
                            }
                        }
                    }
                }
            } else {
                // 0x002fa568
                charge(ctx, 3);
                v1 = 424;
                if (a0 == v1) {
                    // 0x002fa7f0
                    charge(ctx, 4);
                    lhu(v1, s0, act::kFlags2);
                    v1 = v1 & 0x1;
                    if (v1 != 0) {
                        // 0x002fa800
                        charge(ctx, 5);
                        lw(a2, s0, act::kUnit);
                        lbu(a0, a2, unit::kSide);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x002fa814
                            charge(ctx, 4);
                            lhu(a0, a2, unit::kId);
                            v1 = 280;
                            if (a0 != v1) {
                                // 0x002fa824
                                charge(ctx, 3);
                                v1 = 279;
                                if (a0 == v1) {
                                    goto L_002fa844;
                                }
                                // 0x002fa830
                                charge(ctx, 3);
                                v1 = 278;
                                if (a0 == v1) {
                                    goto L_002fa844;
                                }
                                // 0x002fa83c
                                charge(ctx, 2);
                                // 0x002faa3c (the shared epilogue, written out on this path)
                                charge(ctx, 5);
                                ld(ra, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x20);
                                return;
                            }
                        L_002fa844:
                            charge(ctx, 3);
                            v1 = 1;
                            if (a1 == v1) {
                                // 0x002fa850
                                charge(ctx, 17);
                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lhu(v1, a0, gbtl::kBossWork3);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, a0);
                                sw(s0, v0, 2884);
                                v1 = addiu(v1, 1);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                sh(v1, v0, gbtl::kBossWork3);
                                a0 = 0x2F0000;
                                a0 = addiu(a0, 3744);  // &sub_2F0EA0
                                a1 = 0x2F0000;
                                a1 = addiu(a1, 5280);  // &sub_2F14A0
                                a2 = s0;
                                jal(ctx, 0x2FA884u, gen::fn_sub_2E4220_002e4220);
                            }
                        }
                    }
                } else {
                    // 0x002fa574
                    charge(ctx, 3);
                    v1 = 423;
                    if (a0 == v1) {
                        // 0x002fa76c
                        charge(ctx, 4);
                        lhu(v1, s0, act::kFlags2);
                        v1 = v1 & 0x1;
                        if (v1 != 0) {
                            // 0x002fa77c
                            charge(ctx, 5);
                            lw(a2, s0, act::kUnit);
                            lbu(a0, a2, unit::kSide);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x002fa790
                                charge(ctx, 4);
                                lhu(a0, a2, unit::kId);
                                v1 = 268;
                                if (a0 != v1) {
                                    // 0x002fa7a0
                                    charge(ctx, 3);
                                    v1 = 267;
                                    if (a0 == v1) {
                                        goto L_002fa7b4;
                                    }
                                    // 0x002fa7ac
                                    charge(ctx, 2);
                                    // 0x002faa3c (the shared epilogue, written out on this path)
                                    charge(ctx, 5);
                                    ld(ra, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x20);
                                    return;
                                }
                            L_002fa7b4:
                                charge(ctx, 2);
                                if (a1 != 0) {
                                    // 0x002fa7bc
                                    charge(ctx, 4);
                                    jal(ctx, 0x2FA7BCu, gen::fn_sub_2E4250_002e4250);
                                    if (v0 == 0) {
                                        // 0x002fa7cc
                                        charge(ctx, 9);
                                        a0 = 0x2F0000;
                                        a0 = addiu(a0, -4096);  // &sub_2EF000
                                        a1 = 0x2F0000;
                                        a1 = addiu(a1, -3504);  // &sub_2EF250
                                        a2 = s0;
                                        jal(ctx, 0x2FA7E0u, gen::fn_sub_2E4220_002e4220);
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x002fa580
                        charge(ctx, 3);
                        v1 = 422;
                        if (a0 == v1) {
                            // 0x002fa6e4
                            charge(ctx, 4);
                            lhu(v1, s0, act::kFlags2);
                            v1 = v1 & 0x1;
                            if (v1 != 0) {
                                // 0x002fa6f4
                                charge(ctx, 5);
                                lw(a2, s0, act::kUnit);
                                lbu(a0, a2, unit::kSide);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x002fa708
                                    charge(ctx, 4);
                                    lhu(a0, a2, unit::kId);
                                    v1 = 266;
                                    if (a0 != v1) {
                                        // 0x002fa718
                                        charge(ctx, 3);
                                        v1 = 265;
                                        if (a0 == v1) {
                                            goto L_002fa72c;
                                        }
                                        // 0x002fa724
                                        charge(ctx, 2);
                                        // 0x002faa3c (the shared epilogue, written out on this path)
                                        charge(ctx, 5);
                                        ld(ra, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x20);
                                        return;
                                    }
                                L_002fa72c:
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (a1 == v1) {
                                        // 0x002fa738
                                        charge(ctx, 4);
                                        jal(ctx, 0x2FA738u, gen::fn_sub_2E4250_002e4250);
                                        if (v0 == 0) {
                                            // 0x002fa748
                                            charge(ctx, 9);
                                            a0 = 0x2F0000;
                                            a0 = addiu(a0, -6592);  // &sub_2EE640
                                            a1 = 0x2F0000;
                                            a1 = addiu(a1, -5616);  // &sub_2EEA10
                                            a2 = s0;
                                            jal(ctx, 0x2FA75Cu, gen::fn_sub_2E4220_002e4220);
                                        }
                                    }
                                }
                            }
                        } else {
                            // 0x002fa58c
                            charge(ctx, 3);
                            v1 = 420;
                            if (a0 == v1) {
                                // 0x002fa624
                                charge(ctx, 4);
                                lhu(v1, s0, act::kFlags2);
                                v1 = v1 & 0x1;
                                if (v1 != 0) {
                                    // 0x002fa634
                                    charge(ctx, 5);
                                    lw(a0, s0, act::kUnit);
                                    lbu(v1, a0, unit::kSide);
                                    a2 = 1;
                                    if (v1 == a2) {
                                        // 0x002fa648
                                        charge(ctx, 4);
                                        lhu(a0, a0, unit::kId);
                                        v1 = 262;
                                        if (a0 != v1) {
                                            // 0x002fa658
                                            charge(ctx, 3);
                                            v1 = 261;
                                            if (a0 == v1) {
                                                goto L_002fa6a4;
                                            }
                                            // 0x002fa664
                                            charge(ctx, 3);
                                            v1 = 277;
                                            if (a0 == v1) {
                                                // 0x002fa678
                                                charge(ctx, 2);
                                                if (a1 == a2) {
                                                    // 0x002fa680
                                                    charge(ctx, 9);
                                                    a0 = 0x2F0000;
                                                    a0 = addiu(a0, -21520);  // &sub_2EABF0
                                                    a1 = 0x2F0000;
                                                    a1 = addiu(a1, -19888);  // &sub_2EB250
                                                    a2 = s0;
                                                    jal(ctx, 0x2FA694u, gen::fn_sub_2E4220_002e4220);
                                                }
                                            } else {
                                                // 0x002fa670
                                                charge(ctx, 2);
                                            }
                                            // 0x002faa3c (the shared epilogue, written out on this path)
                                            charge(ctx, 5);
                                            ld(ra, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x20);
                                            return;
                                        }
                                    L_002fa6a4:
                                        charge(ctx, 2);
                                        if (a1 == 0) {
                                            // 0x002fa6ac
                                            charge(ctx, 4);
                                            jal(ctx, 0x2FA6ACu, gen::fn_sub_2E4250_002e4250);
                                            if (v0 != 0) {
                                                // 0x002fa6bc
                                                charge(ctx, 1);
                                                s0 = 0;
                                            }
                                            // 0x002fa6c0
                                            charge(ctx, 9);
                                            a0 = 0x2F0000;
                                            a0 = addiu(a0, -17840);  // &sub_2EBA50
                                            a1 = 0x2F0000;
                                            a1 = addiu(a1, -16704);  // &sub_2EBEC0
                                            a2 = s0;
                                            jal(ctx, 0x2FA6D4u, gen::fn_sub_2E4220_002e4220);
                                        }
                                    }
                                }
                            } else {
                                // 0x002fa598
                                charge(ctx, 3);
                                v1 = 417;
                                if (a0 == v1) {
                                    // 0x002fa5ac
                                    charge(ctx, 4);
                                    lhu(v1, s0, act::kFlags2);
                                    v1 = v1 & 0x1;
                                    if (v1 != 0) {
                                        // 0x002fa5bc
                                        charge(ctx, 5);
                                        lw(a2, s0, act::kUnit);
                                        lbu(a0, a2, unit::kSide);
                                        v1 = 1;
                                        if (a0 == v1) {
                                            // 0x002fa5d0
                                            charge(ctx, 4);
                                            lhu(a0, a2, unit::kId);
                                            v1 = 258;
                                            if (a0 != v1) {
                                                // 0x002fa5e0
                                                charge(ctx, 3);
                                                v1 = 257;
                                                if (a0 == v1) {
                                                    goto L_002fa5f4;
                                                }
                                                // 0x002fa5ec
                                                charge(ctx, 2);
                                                // 0x002faa3c (the shared epilogue, written out on this path)
                                                charge(ctx, 5);
                                                ld(ra, sp, 0x10);
                                                lq(s0, sp, 0x0);
                                                sp = addiu(sp, 0x20);
                                                return;
                                            }
                                        L_002fa5f4:
                                            charge(ctx, 3);
                                            v1 = 1;
                                            if (a1 == v1) {
                                                // 0x002fa600
                                                charge(ctx, 9);
                                                a0 = 0x2F0000;
                                                a0 = addiu(a0, -25568);  // &sub_2E9C20
                                                a1 = 0x2F0000;
                                                a1 = addiu(a1, -24816);  // &sub_2E9F10
                                                a2 = s0;
                                                jal(ctx, 0x2FA614u, gen::fn_sub_2E4220_002e4220);
                                            }
                                        }
                                    }
                                } else {
                                    // 0x002fa5a4
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
            // 0x002faa3c (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_002fa934:
        charge(ctx, 4);
        lhu(v1, s0, 26);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002fa944
            charge(ctx, 5);
            lw(a2, s0, 48);
            lbu(a0, a2, 162);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fa958
                charge(ctx, 5);
                lhu(v1, a2, 164);
                v1 = addiu(v1, -235);
                at = sltiu(v1, 6);
                if (at != 0) {
                    // 0x002fa96c
                    charge(ctx, 7);
                    a0 = 0x7C0000;
                    a0 = addiu(a0, -29424);  // &0x7B8D10
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x2FA988u:  // table[0, 1, 2, 3, 4, 5]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                    // 0x002fa988
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x002fa990
                        charge(ctx, 4);
                        jal(ctx, 0x2FA990u, gen::fn_sub_2E4250_002e4250);
                        if (v0 == 0) {
                            // 0x002fa9a0
                            charge(ctx, 9);
                            a0 = 0x2F0000;
                            a0 = addiu(a0, 22112);  // &sub_2F5660
                            a1 = 0x2F0000;
                            a1 = addiu(a1, 22640);  // &sub_2F5870
                            a2 = s0;
                            jal(ctx, 0x2FA9B4u, gen::fn_sub_2E4220_002e4220);
                        }
                    }
                }
            }
        }
    }
    // 0x002faa3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002FB860 sub_2FB860 -- 2992 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossRemapMotion] Boss motion remap: for the boss encounters 0x1A0..0x1B4 a boss unit's motion through its table
// (some by the boss work words or effect / HP state); -1 when not remapped.
// Arguments: a0 btlUnit, a1 motion.
void sub_2FB860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fb860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kSetupEnemies);
    lhu(a1, v1, 8);
    v1 = addiu(a1, -416);
    at = sltiu(v1, 21);
    if (at == 0) {
        // 0x002fc3f4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x002fb894
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -29360);  // &0x7B8D50
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2FB8B0u:  // table[0]
            // 0x002fb8b0
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fb8cc
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 256;
                if (v1 == v0) {
                    // 0x002fb8e4
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -25616);  // &0x699BF0
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fb8dc
                    charge(ctx, 2);
                    // 0x002fb908
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fb8c0
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fb90c
            charge(ctx, 2);
            break;
        case 0x2FB914u:  // table[2]
            // 0x002fb914
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fb930
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 259;
                if (v1 == v0) {
                    // 0x002fb948
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -25456);  // &0x699C90
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fb940
                    charge(ctx, 2);
                    // 0x002fb96c
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fb924
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fb970
            charge(ctx, 2);
            break;
        case 0x2FB978u:  // table[1]
            // 0x002fb978
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fb994
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 258;
                if (v1 == v0) {
                    // 0x002fb9dc
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -25542);  // &0x699C3A
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fb9a4
                    charge(ctx, 3);
                    v0 = 257;
                    if (v1 == v0) {
                        // 0x002fb9b8
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -25568);  // &0x699C20
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x002fb9b0
                        charge(ctx, 2);
                        // 0x002fba00
                        charge(ctx, 1);
                        v0 = si(-1);
                    }
                }
            } else {
                // 0x002fb988
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fba04
            charge(ctx, 2);
            break;
        case 0x2FBA0Cu:  // table[3]
            // 0x002fba0c
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fba28
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 260;
                if (v1 == v0) {
                    // 0x002fba44
                    charge(ctx, 7);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -25376);  // &0x699CE0
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fba38
                    charge(ctx, 3);
                    v0 = si(-1);
                }
            } else {
                // 0x002fba1c
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fba60
            charge(ctx, 2);
            break;
        case 0x2FBA68u:  // table[4]
            // 0x002fba68
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fba84
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 277;
                if (v1 == v0) {
                    // 0x002fbafc
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -25244);  // &0x699D64
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fba94
                    charge(ctx, 3);
                    v0 = 262;
                    if (v1 == v0) {
                        // 0x002fbad8
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -25270);  // &0x699D4A
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x002fbaa0
                        charge(ctx, 3);
                        v0 = 261;
                        if (v1 == v0) {
                            // 0x002fbab4
                            charge(ctx, 9);
                            v1 = s0 & 0xFFFF;
                            v0 = 0x6A0000;
                            v0 = addiu(v0, -25296);  // &0x699D30
                            v0 = addu(v0, v1);
                            lbu(v0, v0, 0);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                        } else {
                            // 0x002fbaac
                            charge(ctx, 2);
                            // 0x002fbb20
                            charge(ctx, 1);
                            v0 = si(-1);
                        }
                    }
                }
            } else {
                // 0x002fba78
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fbb24
            charge(ctx, 2);
            break;
        case 0x2FBB2Cu:  // table[5]
            // 0x002fbb2c
            charge(ctx, 4);
            lbu(a0, s1, unit::kSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fbb48
                charge(ctx, 4);
                lhu(a0, s1, unit::kId);
                v1 = 263;
                if (a0 == v1) {
                    // 0x002fbb64
                    charge(ctx, 4);
                    a0 = s0 & 0xFFFF;
                    v1 = 17;
                    if (a0 != v1) {
                        // 0x002fbb74
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 == v1) {
                            goto L_002fbb90;
                        }
                        // 0x002fbb80
                        charge(ctx, 2);
                        if (a0 == 0) {
                            goto L_002fbb90;
                        }
                        // 0x002fbb88
                        charge(ctx, 2);
                    L_002fbbc8:
                        charge(ctx, 3);
                        v1 = 421;
                        if (a1 != v1) {
                            // 0x002fbbe0
                            charge(ctx, 1);
                            v1 = 0;
                        } else {
                            // 0x002fbbd4
                            charge(ctx, 3);
                            lw(v1, v0, 2884);
                        }
                        // 0x002fbbe4
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x002fbbec
                            charge(ctx, 1);
                            sw(zero, v0, 2892);
                        }
                        // 0x002fbbf0
                        charge(ctx, 7);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -25136);  // &0x699DD0
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        goto L_002fbc0c;
                    }
                L_002fbb90:
                    charge(ctx, 3);
                    v1 = 421;
                    if (a1 != v1) {
                        // 0x002fbba8
                        charge(ctx, 1);
                        v1 = 0;
                    } else {
                        // 0x002fbb9c
                        charge(ctx, 3);
                        lw(v1, v0, 2884);
                    }
                    // 0x002fbbac
                    charge(ctx, 2);
                    if (v1 == 0) {
                        goto L_002fbbc8;
                    }
                    // 0x002fbbb4
                    charge(ctx, 5);
                    v1 = 1;
                    sw(v1, v0, 2892);
                    v0 = 15;
                } else {
                    // 0x002fbb58
                    charge(ctx, 3);
                    v0 = si(-1);
                }
            } else {
                // 0x002fbb3c
                charge(ctx, 3);
                v0 = si(-1);
            }
        L_002fbc0c:
            charge(ctx, 2);
            break;
        case 0x2FBC14u:  // table[6]
            // 0x002fbc14
            charge(ctx, 4);
            lbu(a0, s1, unit::kSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fbc30
                charge(ctx, 4);
                lhu(a0, s1, unit::kId);
                v1 = 232;
                if (a0 != v1) {
                    // 0x002fbc40
                    charge(ctx, 3);
                    v1 = 231;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc4c
                    charge(ctx, 3);
                    v1 = 230;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc58
                    charge(ctx, 3);
                    v1 = 229;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc64
                    charge(ctx, 3);
                    v1 = 228;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc70
                    charge(ctx, 3);
                    v1 = 227;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc7c
                    charge(ctx, 3);
                    v1 = 226;
                    if (a0 == v1) {
                        goto L_002fbd44;
                    }
                    // 0x002fbc88
                    charge(ctx, 3);
                    v1 = 266;
                    if (a0 == v1) {
                        // 0x002fbd20
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -25030);  // &0x699E3A
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x002fbc94
                        charge(ctx, 3);
                        v1 = 265;
                        if (a0 == v1) {
                            // 0x002fbca8
                            charge(ctx, 4);
                            a0 = s0 & 0xFFFF;
                            v1 = 9;
                            if (a0 != v1) {
                                // 0x002fbcb8
                                charge(ctx, 3);
                                v1 = 17;
                                if (a0 == v1) {
                                    goto L_002fbce0;
                                }
                                // 0x002fbcc4
                                charge(ctx, 3);
                                v1 = 3;
                                if (a0 == v1) {
                                    goto L_002fbce0;
                                }
                                // 0x002fbcd0
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    goto L_002fbce0;
                                }
                                // 0x002fbcd8
                                charge(ctx, 2);
                            L_002fbcfc:
                                charge(ctx, 9);
                                v1 = s0 & 0xFFFF;
                                v0 = 0x6A0000;
                                v0 = addiu(v0, -25056);  // &0x699E20
                                v0 = addu(v0, v1);
                                lbu(v0, v0, 0);
                                v0 = dsll32(v0, 16);
                                v0 = dsra32(v0, 16);
                                goto L_002fbd54;
                            }
                        L_002fbce0:
                            charge(ctx, 4);
                            lw(v1, v0, 2896);
                            v0 = 1;
                            if (v1 != v0) {
                                goto L_002fbcfc;
                            }
                            // 0x002fbcf0
                            charge(ctx, 3);
                            v0 = 6;
                        } else {
                            // 0x002fbca0
                            charge(ctx, 2);
                            // 0x002fbd50
                            charge(ctx, 1);
                            v0 = si(-1);
                        }
                    }
                    goto L_002fbd54;
                }
            L_002fbd44:
                charge(ctx, 3);
                v0 = si(-1);
            } else {
                // 0x002fbc24
                charge(ctx, 3);
                v0 = si(-1);
            }
        L_002fbd54:
            charge(ctx, 2);
            break;
        case 0x2FBD5Cu:  // table[7]
            // 0x002fbd5c
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fbd78
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 268;
                if (v1 == v0) {
                    // 0x002fbdc0
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24518);  // &0x69A03A
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fbd88
                    charge(ctx, 3);
                    v0 = 267;
                    if (v1 == v0) {
                        // 0x002fbd9c
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -24544);  // &0x69A020
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x002fbd94
                        charge(ctx, 2);
                        // 0x002fbde4
                        charge(ctx, 1);
                        v0 = si(-1);
                    }
                }
            } else {
                // 0x002fbd6c
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fbde8
            charge(ctx, 2);
            break;
        case 0x2FBDF0u:  // table[8]
            // 0x002fbdf0
            charge(ctx, 4);
            lbu(a0, s1, unit::kSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fbe0c
                charge(ctx, 4);
                lhu(a0, s1, unit::kId);
                v1 = 295;
                if (a0 != v1) {
                    // 0x002fbe1c
                    charge(ctx, 3);
                    v1 = 281;
                    if (a0 == v1) {
                        goto L_002fbed8;
                    }
                    // 0x002fbe28
                    charge(ctx, 3);
                    v1 = 280;
                    if (a0 != v1) {
                        // 0x002fbe34
                        charge(ctx, 3);
                        v1 = 279;
                        if (a0 == v1) {
                            goto L_002fbeb4;
                        }
                        // 0x002fbe40
                        charge(ctx, 3);
                        v1 = 278;
                        if (a0 == v1) {
                            goto L_002fbeb4;
                        }
                        // 0x002fbe4c
                        charge(ctx, 3);
                        v1 = 269;
                        if (a0 == v1) {
                            // 0x002fbe60
                            charge(ctx, 3);
                            lw(v0, v0, gbtl::kBossWork4);
                            if (v0 != 0) {
                                // 0x002fbe90
                                charge(ctx, 9);
                                v1 = s0 & 0xFFFF;
                                v0 = 0x6A0000;
                                v0 = addiu(v0, -24422);  // &0x69A09A
                                v0 = addu(v0, v1);
                                lbu(v0, v0, 0);
                                v0 = dsll32(v0, 16);
                                v0 = dsra32(v0, 16);
                            } else {
                                // 0x002fbe6c
                                charge(ctx, 9);
                                v1 = s0 & 0xFFFF;
                                v0 = 0x6A0000;
                                v0 = addiu(v0, -24448);  // &0x69A080
                                v0 = addu(v0, v1);
                                lbu(v0, v0, 0);
                                v0 = dsll32(v0, 16);
                                v0 = dsra32(v0, 16);
                            }
                        } else {
                            // 0x002fbe58
                            charge(ctx, 2);
                            // 0x002fbf30
                            charge(ctx, 1);
                            v0 = si(-1);
                        }
                        goto L_002fbf34;
                    }
                L_002fbeb4:
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24396);  // &0x69A0B4
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    goto L_002fbf34;
                }
            L_002fbed8:
                charge(ctx, 4);
                v1 = s0 & 0xFFFF;
                v0 = 3;
                if (v1 == v0) {
                    // 0x002fbee8
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 1024;
                    jal(ctx, 0x2FBEF0u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        goto L_002fbf0c;
                    }
                    // 0x002fbf00
                    charge(ctx, 3);
                    v0 = 15;
                    goto L_002fbf34;
                }
            L_002fbf0c:
                charge(ctx, 9);
                v1 = s0 & 0xFFFF;
                v0 = 0x6A0000;
                v0 = addiu(v0, -24370);  // &0x69A0CE
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
            } else {
                // 0x002fbe00
                charge(ctx, 3);
                v0 = si(-1);
            }
        L_002fbf34:
            charge(ctx, 2);
            break;
        case 0x2FBF3Cu:  // table[12]
            // 0x002fbf3c
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fbf58
                charge(ctx, 4);
                v1 = s0 & 0xFFFF;
                v0 = 17;
                if (v1 != v0) {
                    // 0x002fbf68
                    charge(ctx, 3);
                    v0 = 3;
                    if (v1 == v0) {
                        goto L_002fbf84;
                    }
                    // 0x002fbf74
                    charge(ctx, 2);
                    if (v1 == 0) {
                        goto L_002fbf84;
                    }
                    // 0x002fbf7c
                    charge(ctx, 2);
                L_002fbfbc:
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 11;
                    jal(ctx, 0x2FBFC4u, gen::fn_datCalcGetEffectState_00301750);
                    if (v0 == 0) {
                        // 0x002fbfd4
                        charge(ctx, 2);
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        sw(zero, v0, gbtl::kBossWork3);
                    }
                    // 0x002fbfdc
                    charge(ctx, 7);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24016);  // &0x69A230
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    goto L_002fbff8;
                }
            L_002fbf84:
                charge(ctx, 8);
                lw(a0, s1, unit::kDat);
                a1 = 11;
                jal(ctx, 0x2FBF8Cu, gen::fn_datCalcGetEffectState_00301750);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                if (i64(v0) <= 0) {
                    goto L_002fbfbc;
                }
                // 0x002fbfa4
                charge(ctx, 6);
                v1 = 1;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v1, v0, gbtl::kBossWork3);
                v0 = 15;
            } else {
                // 0x002fbf4c
                charge(ctx, 3);
                v0 = si(-1);
            }
        L_002fbff8:
            charge(ctx, 2);
            break;
        case 0x2FC000u:  // table[13]
            // 0x002fc000
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc01c
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 274;
                if (v1 == v0) {
                    // 0x002fc038
                    charge(ctx, 7);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -23680);  // &0x69A380
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc02c
                    charge(ctx, 3);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc010
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc054
            charge(ctx, 2);
            break;
        case 0x2FC05Cu:  // table[9]
            // 0x002fc05c
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc078
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 264;
                if (v1 == v0) {
                    // 0x002fc090
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24272);  // &0x69A130
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc088
                    charge(ctx, 2);
                    // 0x002fc0b4
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc06c
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc0b8
            charge(ctx, 2);
            break;
        case 0x2FC0C0u:  // table[10]
            // 0x002fc0c0
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc0dc
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 271;
                if (v1 == v0) {
                    // 0x002fc0f4
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24208);  // &0x69A170
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc0ec
                    charge(ctx, 2);
                    // 0x002fc118
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc0d0
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc11c
            charge(ctx, 2);
            break;
        case 0x2FC124u:  // table[11]
            // 0x002fc124
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc140
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 272;
                if (v1 == v0) {
                    // 0x002fc158
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -24144);  // &0x69A1B0
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc150
                    charge(ctx, 2);
                    // 0x002fc17c
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc134
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc180
            charge(ctx, 2);
            break;
        case 0x2FC188u:  // table[14]
            // 0x002fc188
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc1a4
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 294;
                if (v1 == v0) {
                    // 0x002fc1bc
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -23408);  // &0x69A490
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc1b4
                    charge(ctx, 2);
                    // 0x002fc1e0
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc198
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc1e4
            charge(ctx, 2);
            break;
        case 0x2FC1ECu:  // table[15]
            // 0x002fc1ec
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc208
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 233;
                if (v1 == v0) {
                    // 0x002fc220
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -23344);  // &0x69A4D0
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc218
                    charge(ctx, 2);
                    // 0x002fc244
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc1fc
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc248
            charge(ctx, 2);
            break;
        case 0x2FC250u:  // table[16]
            // 0x002fc250
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc26c
                charge(ctx, 4);
                lhu(v1, s1, unit::kId);
                v0 = 234;
                if (v1 == v0) {
                    // 0x002fc284
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -23280);  // &0x69A510
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                } else {
                    // 0x002fc27c
                    charge(ctx, 2);
                    // 0x002fc2a8
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc260
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc2ac
            charge(ctx, 2);
            break;
        case 0x2FC2B4u:  // table[17, 18, 19]
            // 0x002fc2b4
            charge(ctx, 4);
            lbu(v1, s1, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fc2d0
                charge(ctx, 5);
                lhu(v0, s1, unit::kId);
                v0 = addiu(v0, -235);
                at = sltiu(v0, 6);
                if (at == 0) {
                    // 0x002fc324
                    charge(ctx, 1);
                    v0 = si(-1);
                } else {
                    // 0x002fc2e4
                    charge(ctx, 7);
                    v1 = 0x7C0000;
                    v1 = addiu(v1, -29392);  // &0x7B8D30
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x2FC300u:  // table[0, 1, 2, 3, 4, 5]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    // 0x002fc300
                    charge(ctx, 9);
                    v1 = s0 & 0xFFFF;
                    v0 = 0x6A0000;
                    v0 = addiu(v0, -23248);  // &0x69A530
                    v0 = addu(v0, v1);
                    lbu(v0, v0, 0);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                }
            } else {
                // 0x002fc2c4
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x002fc328
            charge(ctx, 2);
            break;
        case 0x2FC330u:  // table[20]
            // 0x002fc330
            charge(ctx, 4);
            lbu(a0, s1, unit::kSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002fc34c
                charge(ctx, 4);
                lhu(a0, s1, unit::kId);
                v1 = 241;
                if (a0 == v1) {
                    // 0x002fc364
                    charge(ctx, 3);
                    lw(v0, v0, gbtl::kBossWork1);
                    if (v0 != 0) {
                        // 0x002fc3c4
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -23158);  // &0x69A58A
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    } else {
                        // 0x002fc370
                        charge(ctx, 4);
                        v1 = s0 & 0xFFFF;
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x002fc380
                            charge(ctx, 5);
                            lw(a0, s1, unit::kDat);
                            jal(ctx, 0x2FC384u, gen::fn_datCalcIsLowHp_0030b5e0);
                            if (v0 == 0) {
                                goto L_002fc3a0;
                            }
                            // 0x002fc394
                            charge(ctx, 3);
                            v0 = 6;
                            goto L_002fc3ec;
                        }
                    L_002fc3a0:
                        charge(ctx, 9);
                        v1 = s0 & 0xFFFF;
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -23184);  // &0x69A570
                        v0 = addu(v0, v1);
                        lbu(v0, v0, 0);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                    }
                } else {
                    // 0x002fc35c
                    charge(ctx, 2);
                    // 0x002fc3e8
                    charge(ctx, 1);
                    v0 = si(-1);
                }
            } else {
                // 0x002fc340
                charge(ctx, 3);
                v0 = si(-1);
            }
        L_002fc3ec:
            charge(ctx, 2);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002fc3f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002FC520 sub_2FC520 -- 164 bytes; frame 0x10: ra sp+0x0
// [btlBossGetEffectRow] A boss unit's EFFECT.TBL section-5 row (+2), 0 for others and indices 20 / 21.
// Arguments: a0 btlUnit.
void sub_2FC520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fc520
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lbu(v1, a0, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // 0x002fc544
        charge(ctx, 8);
        lhu(a0, a0, unit::kId);
        jal(ctx, 0x2FC548u, gen::fn_sub_2F6C50_002f6c50);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x002fc570
            charge(ctx, 3);
            v0 = 21;
            if (v1 != v0) {
                // 0x002fc57c
                charge(ctx, 3);
                v0 = 20;
                if (v1 == v0) {
                    goto L_002fc590;
                }
                // 0x002fc588
                charge(ctx, 2);
                // 0x002fc59c
                charge(ctx, 6);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, gp, kGpEffectSec5);  // EFFECT.TBL section 5: 31 x 12-byte boss rows (sub_2FC520) 0x7CE4C0
                v0 = addu(v0, v1);
                v0 = addiu(v0, 2);
                // 0x002fc5b4 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x10);
                return;
            }
        L_002fc590:
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x002fc564
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002fc538
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002fc5b4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FCAA0 sub_2FCAA0 -- 1196 bytes; leaf frame (no stack)
// [btlBossGetWork] Copies the boss work words (gBtl +2884..+2892) for a boss unit of encounters 0x1A7..0x1B3; 1 when
// copied.
// Arguments: a0 btlAction, a1 u32[3]* out.
void sub_2FCAA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x002fcaa0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v1, gbtl::kSetupEnemies);
    lhu(v0, v0, 8);
    v0 = addiu(v0, -423);
    at = sltiu(v0, 13);
    if (at != 0) {
        // 0x002fcabc
        charge(ctx, 7);
        a2 = 0x7C0000;
        a2 = addiu(a2, -29232);  // &0x7B8DD0
        v0 = sll(v0, 2);
        v0 = addu(v0, a2);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2FCAD8u:  // table[0]
            // 0x002fcad8
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcaf4
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcb14
                    charge(ctx, 4);
                    lhu(a0, a2, unit::kId);
                    v0 = 268;
                    if (a0 != v0) {
                        // 0x002fcb24
                        charge(ctx, 3);
                        v0 = 267;
                        if (a0 == v0) {
                            goto L_002fcb38;
                        }
                        // 0x002fcb30
                        charge(ctx, 2);
                        // 0x002fcb64
                        charge(ctx, 1);
                        v0 = 0;
                        goto L_002fcb68;
                    }
                L_002fcb38:
                    charge(ctx, 11);
                    lw(v0, v1, 2884);
                    sw(v0, a1, 0);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kBossWork1);
                    sw(v0, a1, 4);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kBossWork2);
                    sw(v0, a1, 8);
                    v0 = 1;
                } else {
                    // 0x002fcb08
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcae8
                charge(ctx, 3);
                v0 = 0;
            }
        L_002fcb68:
            charge(ctx, 2);
            break;
        case 0x2FCB70u:  // table[2]
            // 0x002fcb70
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcb8c
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcbac
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 264;
                    if (a2 == a0) {
                        // 0x002fcbc4
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fcbbc
                        charge(ctx, 2);
                        // 0x002fcbec
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fcba0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcb80
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fcbf0
            charge(ctx, 2);
            break;
        case 0x2FCBF8u:  // table[3]
            // 0x002fcbf8
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcc14
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcc34
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 271;
                    if (a2 == a0) {
                        // 0x002fcc4c
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fcc44
                        charge(ctx, 2);
                        // 0x002fcc74
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fcc28
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcc08
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fcc78
            charge(ctx, 2);
            break;
        case 0x2FCC80u:  // table[4]
            // 0x002fcc80
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcc9c
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fccbc
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 272;
                    if (a2 == a0) {
                        // 0x002fccd4
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fcccc
                        charge(ctx, 2);
                        // 0x002fccfc
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fccb0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcc90
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fcd00
            charge(ctx, 2);
            break;
        case 0x2FCD08u:  // table[7]
            // 0x002fcd08
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcd24
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcd44
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 294;
                    if (a2 == a0) {
                        // 0x002fcd5c
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fcd54
                        charge(ctx, 2);
                        // 0x002fcd84
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fcd38
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcd18
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fcd88
            charge(ctx, 2);
            break;
        case 0x2FCD90u:  // table[8]
            // 0x002fcd90
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcdac
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcdcc
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 233;
                    if (a2 == a0) {
                        // 0x002fcde4
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fcddc
                        charge(ctx, 2);
                        // 0x002fce0c
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fcdc0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fcda0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fce10
            charge(ctx, 2);
            break;
        case 0x2FCE18u:  // table[9]
            // 0x002fce18
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fce34
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fce54
                    charge(ctx, 4);
                    lhu(a2, a2, unit::kId);
                    a0 = 234;
                    if (a2 == a0) {
                        // 0x002fce6c
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    } else {
                        // 0x002fce64
                        charge(ctx, 2);
                        // 0x002fce94
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x002fce48
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fce28
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fce98
            charge(ctx, 2);
            break;
        case 0x2FCEA0u:  // table[10, 11, 12]
            // 0x002fcea0
            charge(ctx, 4);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002fcebc
                charge(ctx, 5);
                lw(a2, a0, act::kUnit);
                lbu(a0, a2, unit::kSide);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002fcedc
                    charge(ctx, 5);
                    lhu(a0, a2, unit::kId);
                    a0 = addiu(a0, -235);
                    at = sltiu(a0, 6);
                    if (at == 0) {
                        // 0x002fcf34
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x002fcef0
                        charge(ctx, 7);
                        a2 = 0x7C0000;
                        a2 = addiu(a2, -29264);  // &0x7B8DB0
                        a0 = sll(a0, 2);
                        a0 = addu(a0, a2);
                        lw(a0, a0, 0);
                        switch (a0.u()) {
                        case 0x2FCF0Cu:  // table[0, 1, 2, 3, 4, 5]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, a0.u());
                            return;
                        }
                        // 0x002fcf0c
                        charge(ctx, 10);
                        lw(v1, v1, gbtl::kBossWork0);
                        sw(v1, a1, 0);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork1);
                        sw(v1, a1, 4);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lw(v1, v1, gbtl::kBossWork2);
                        sw(v1, a1, 8);
                    }
                } else {
                    // 0x002fced0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x002fceb0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x002fcf38
            charge(ctx, 2);
            break;
        case 0x2FCF40u:  // table[1, 5, 6]
        L_002fcf40:
            charge(ctx, 1);
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x002fcf44 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    goto L_002fcf40;
}

// 0x002FD220 sub_2FD220 -- 184 bytes; frame 0x10: ra sp+0x0
// Encounter 421 rule: sub_30AF00 between the two units and a pending boss action without a phase.
// Arguments: a0 / a1 btlAction.
void sub_2FD220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd220
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 421;
    if (v1 == v0) {
        // 0x002fd248
        charge(ctx, 8);
        lw(v1, a0, act::kUnit);
        lw(v0, a1, act::kUnit);
        lw(a0, v1, unit::kDat);
        lw(a1, v0, unit::kDat);
        jal(ctx, 0x2FD258u, gen::fn_sub_30AF00_0030af00);
        if (v0 != 0) {
            // 0x002fd274
            charge(ctx, 6);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, a0, gbtl::kSetupEnemies);
            lhu(v1, v0, 8);
            v0 = 421;
            if (v1 != v0) {
                // 0x002fd298
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002fd28c
                charge(ctx, 3);
                lw(v0, a0, gbtl::kBossWork0);
            }
            // 0x002fd29c
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x002fd2b0
                charge(ctx, 3);
                lw(v0, a0, gbtl::kBossWork1);
                // xor v0: a 64-bit move to itself (no effect)
                v0 = sltiu(v0, 1);
            } else {
                // 0x002fd2a4
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002fd268
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x002fd2bc
        charge(ctx, 2);
    } else {
        // 0x002fd240
        charge(ctx, 2);
        // 0x002fd2c4
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x002fd2c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FD4A0 sub_2FD4A0 -- 92 bytes; frame 0x10: ra sp+0x0
// [btlBossTaskAlive] Whether gBtl's boss task still exists (clears it when it ended).
void sub_2FD4A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd4a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kBossTask);
    if (a0 != 0) {
        // 0x002fd4c4
        charge(ctx, 4);
        jal(ctx, 0x2FD4C4u, gen::fn_kwlnTaskExists_00195460);
        if (v0 != 0) {
            // 0x002fd4e8
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002fd4d4
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(zero, v0, gbtl::kBossTask);
            v0 = 0;
        }
    } else {
        // 0x002fd4b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002fd4ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FD820 sub_2FD820 -- 120 bytes; frame 0x10: ra sp+0x0
// Encounter 429: the panel set-up calls (sub_1FECE0 / sub_1FEE20 from the fourth phase on).
void sub_2FD820(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd820
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kSetupEnemies);
    lhu(a0, v1, 8);
    v1 = 429;
    if (a0 == v1) {
        // 0x002fd848
        charge(ctx, 4);
        lhu(v0, a1, gbtl::kBossWork1);
        at = slti(v0, 4);
        if (at == 0) {
            // 0x002fd858
            charge(ctx, 4);
            jal(ctx, 0x2FD858u, gen::fn_sub_1FECE0_001fece0);
            jal(ctx, 0x2FD860u, gen::fn_sub_1FEE20_001fee20);
        }
        // 0x002fd868
        charge(ctx, 8);
        jal(ctx, 0x2FD868u, gen::fn_sub_1FED60_001fed60);
        jal(ctx, 0x2FD870u, gen::fn_sub_1FEDA0_001feda0);
        jal(ctx, 0x2FD878u, gen::fn_sub_1FEE60_001fee60);
        jal(ctx, 0x2FD880u, gen::fn_sub_1FEDE0_001fede0);
    } else {
        // 0x002fd840
        charge(ctx, 2);
    }
    // 0x002fd888 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FDBB0 sub_2FDBB0 -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Whether a persona model accepts the action's shot (boss rules on: model row flags 1 / 0x20 with sub_2D63B0 /
// sub_2D6290).
// Arguments: a0 btlAction, a1 btlUnit.
void sub_2FDBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fdbb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kFlags);
    v0 = 0x200000;
    v0 = v1 & v0;
    if (v0 != 0) {
        // 0x002fdbe0
        charge(ctx, 12);
        lhu(v1, s0, unit::kId);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, gp, kGpModelPersona);  // MODEL.TBL section 3 (88-byte rows by persona id) 0x7CE42C
        v0 = addu(v0, v1);
        lhu(v0, v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x002fdc3c
            charge(ctx, 4);
            jal(ctx, 0x2FDC3Cu, gen::fn_sub_2D6290_002d6290);
            if (v0 != 0) {
                goto L_002fdc88;
            }
            // 0x002fdc4c
            charge(ctx, 12);
            lhu(v1, s0, unit::kId);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, kGpModelPersona);  // MODEL.TBL section 3 (88-byte rows by persona id) 0x7CE42C
            v0 = addu(v0, v1);
            lhu(v0, v0, 0);
            v0 = v0 & 0x20;
            if (v0 == 0) {
                goto L_002fdc88;
            }
            // 0x002fdc7c
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x002fdc10
            charge(ctx, 11);
            jal(ctx, 0x2FDC10u, gen::fn_sub_2D6290_002d6290);
            lh(a1, s1, act::kCmdSkill);
            a0 = s0;
            a2 = v0;
            jal(ctx, 0x2FDC24u, gen::fn_sub_2D63B0_002d63b0);
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
        }
        // 0x002fdc8c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_002fdc88:
    charge(ctx, 1);
    v0 = 0;
    // 0x002fdc8c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002FDFE0 sub_2FDFE0 -- 204 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Encounter 436 rule: a single-target magic HP skill aimed at boss 241.
// Arguments: a0 camera.
void sub_2FDFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fdfe0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 436;
    if (v1 != v0) {
        // 0x002fe00c
        charge(ctx, 2);
        goto L_002fe090;
    }
    // 0x002fe014
    charge(ctx, 4);
    lw(a0, s0, 224);
    lw(s1, a0, 56);
    if (s1 == 0) {
    L_002fe090:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002fe024
        charge(ctx, 4);
        lhu(v1, a0, 106);
        v0 = 1;
        if (v1 != v0) {
            goto L_002fe090;
        }
        // 0x002fe034
        charge(ctx, 6);
        lh(a0, a0, 110);
        jal(ctx, 0x2FE038u, gen::fn_datCalcIsHpSkill_002d6370);
        v1 = 1;
        if (v0 != v1) {
            goto L_002fe090;
        }
        // 0x002fe04c
        charge(ctx, 6);
        lw(v0, s0, 224);
        lhu(a0, v0, 110);
        jal(ctx, 0x2FE054u, gen::fn_datCalcIsPhysicalSkill_003088b0);
        if (v0 != 0) {
            goto L_002fe090;
        }
        // 0x002fe064
        charge(ctx, 5);
        lw(a0, s1, 48);
        lbu(v1, a0, 162);
        v0 = 1;
        if (v1 != v0) {
            goto L_002fe090;
        }
        // 0x002fe078
        charge(ctx, 4);
        lhu(a0, a0, 164);
        v1 = 241;
        if (a0 != v1) {
            goto L_002fe090;
        }
        // 0x002fe088
        charge(ctx, 2);
    }
    // 0x002fe094 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
