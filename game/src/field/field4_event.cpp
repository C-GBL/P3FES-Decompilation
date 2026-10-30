// The field event task K_FldEvent_UpdateFldEventTask (slice field4; k_event.c; 26_field.md 5 / 7): exploring
// (contact, scripts, the camp menu, stairs, treasure, NPC talk, field hits and doors, the attack swing), the battle
// hand-off (btlStart from state 14) and the return, the camp menu, the game over. The p3fes_handgen body (hg_cpu.h),
// statement for statement the original's, with the 33 states annotated at their cases and goto entries and the sField
// task table, the event work and the exit record named (field4.h evt / exitrec).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field4.h"

namespace p3fes::recomp_gen {
void fn_H_Camp_CreateDrawTask_0011a770(p3fes::EEContext&);
void fn_H_Cdvd_FileExists_001008b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_Battle_FindTaskOfUnit_001d8d80(p3fes::EEContext&);
void fn_K_Field_GetMajorId_001bab20(p3fes::EEContext&);
void fn_K_Field_GetMinorId_001bab30(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90(p3fes::EEContext&);
void fn_K_FldDungeon_GetScrMemory_001bffe0(p3fes::EEContext&);
void fn_K_FldDungeon_GetScrSize_001c0010(p3fes::EEContext&);
void fn_K_FldEvent_FindFldHitAt_001c5ee0(p3fes::EEContext&);
void fn_K_FldEvent_IsUnitNearFldHit_001c7b30(p3fes::EEContext&);
void fn_K_FldEvent_UpdateFldEventTask_001c8620(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_Y_SMap_CreateSmapDrawTask_00429d40(p3fes::EEContext&);
void fn_btlStart_0027d1d0(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcRestorePartyAll_0030c440(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_datUnitIsGenusDead_002ff790(p3fes::EEContext&);
void fn_kwlnTaskClearFlags_00195710(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskSetFlags_001956d0(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromHeader_0035bb40(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_scrSetUserData_0035c1a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_103C30_00103c30(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_108FD0_00108fd0(p3fes::EEContext&);
void fn_sub_109F60_00109f60(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A720_0010a720(p3fes::EEContext&);
void fn_sub_10A770_0010a770(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16D9D0_0016d9d0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18BFF0_0018bff0(p3fes::EEContext&);
void fn_sub_18C0A0_0018c0a0(p3fes::EEContext&);
void fn_sub_18C0C0_0018c0c0(p3fes::EEContext&);
void fn_sub_18EB30_0018eb30(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);
void fn_sub_1A91B0_001a91b0(p3fes::EEContext&);
void fn_sub_1A9330_001a9330(p3fes::EEContext&);
void fn_sub_1A9390_001a9390(p3fes::EEContext&);
void fn_sub_1A93D0_001a93d0(p3fes::EEContext&);
void fn_sub_1A9470_001a9470(p3fes::EEContext&);
void fn_sub_1A9850_001a9850(p3fes::EEContext&);
void fn_sub_1ACC30_001acc30(p3fes::EEContext&);
void fn_sub_1B0870_001b0870(p3fes::EEContext&);
void fn_sub_1B08D0_001b08d0(p3fes::EEContext&);
void fn_sub_1B0910_001b0910(p3fes::EEContext&);
void fn_sub_1B0920_001b0920(p3fes::EEContext&);
void fn_sub_1B09B0_001b09b0(p3fes::EEContext&);
void fn_sub_1B09F0_001b09f0(p3fes::EEContext&);
void fn_sub_1B3C90_001b3c90(p3fes::EEContext&);
void fn_sub_1B8FD0_001b8fd0(p3fes::EEContext&);
void fn_sub_1BAAA0_001baaa0(p3fes::EEContext&);
void fn_sub_1BAB40_001bab40(p3fes::EEContext&);
void fn_sub_1BAB50_001bab50(p3fes::EEContext&);
void fn_sub_1C00D0_001c00d0(p3fes::EEContext&);
void fn_sub_1C0110_001c0110(p3fes::EEContext&);
void fn_sub_1C03F0_001c03f0(p3fes::EEContext&);
void fn_sub_1C0440_001c0440(p3fes::EEContext&);
void fn_sub_1C0740_001c0740(p3fes::EEContext&);
void fn_sub_1C07F0_001c07f0(p3fes::EEContext&);
void fn_sub_1C1F30_001c1f30(p3fes::EEContext&);
void fn_sub_1C2000_001c2000(p3fes::EEContext&);
void fn_sub_1C6080_001c6080(p3fes::EEContext&);
void fn_sub_1C6200_001c6200(p3fes::EEContext&);
void fn_sub_1C65E0_001c65e0(p3fes::EEContext&);
void fn_sub_1C6A20_001c6a20(p3fes::EEContext&);
void fn_sub_1C6F50_001c6f50(p3fes::EEContext&);
void fn_sub_1C74C0_001c74c0(p3fes::EEContext&);
void fn_sub_1C7830_001c7830(p3fes::EEContext&);
void fn_sub_1C7F20_001c7f20(p3fes::EEContext&);
void fn_sub_1C8120_001c8120(p3fes::EEContext&);
void fn_sub_1CD650_001cd650(p3fes::EEContext&);
void fn_sub_1CD790_001cd790(p3fes::EEContext&);
void fn_sub_1CD870_001cd870(p3fes::EEContext&);
void fn_sub_1CD9A0_001cd9a0(p3fes::EEContext&);
void fn_sub_1CE880_001ce880(p3fes::EEContext&);
void fn_sub_1CE960_001ce960(p3fes::EEContext&);
void fn_sub_1D00B0_001d00b0(p3fes::EEContext&);
void fn_sub_1D0110_001d0110(p3fes::EEContext&);
void fn_sub_1D0E50_001d0e50(p3fes::EEContext&);
void fn_sub_1D11B0_001d11b0(p3fes::EEContext&);
void fn_sub_1D12D0_001d12d0(p3fes::EEContext&);
void fn_sub_1D1360_001d1360(p3fes::EEContext&);
void fn_sub_1D1780_001d1780(p3fes::EEContext&);
void fn_sub_1D17F0_001d17f0(p3fes::EEContext&);
void fn_sub_1D1860_001d1860(p3fes::EEContext&);
void fn_sub_1D1910_001d1910(p3fes::EEContext&);
void fn_sub_1D19D0_001d19d0(p3fes::EEContext&);
void fn_sub_1D1A90_001d1a90(p3fes::EEContext&);
void fn_sub_1D1B60_001d1b60(p3fes::EEContext&);
void fn_sub_1D1C20_001d1c20(p3fes::EEContext&);
void fn_sub_1D1CE0_001d1ce0(p3fes::EEContext&);
void fn_sub_1D2210_001d2210(p3fes::EEContext&);
void fn_sub_1D2610_001d2610(p3fes::EEContext&);
void fn_sub_1D2A10_001d2a10(p3fes::EEContext&);
void fn_sub_1D37F0_001d37f0(p3fes::EEContext&);
void fn_sub_1D38D0_001d38d0(p3fes::EEContext&);
void fn_sub_1D39C0_001d39c0(p3fes::EEContext&);
void fn_sub_1D4180_001d4180(p3fes::EEContext&);
void fn_sub_1D5C00_001d5c00(p3fes::EEContext&);
void fn_sub_1D5C10_001d5c10(p3fes::EEContext&);
void fn_sub_1D5F30_001d5f30(p3fes::EEContext&);
void fn_sub_1D68E0_001d68e0(p3fes::EEContext&);
void fn_sub_1D69E0_001d69e0(p3fes::EEContext&);
void fn_sub_1D8C60_001d8c60(p3fes::EEContext&);
void fn_sub_1D8CF0_001d8cf0(p3fes::EEContext&);
void fn_sub_1DA000_001da000(p3fes::EEContext&);
void fn_sub_1DD530_001dd530(p3fes::EEContext&);
void fn_sub_1DD5E0_001dd5e0(p3fes::EEContext&);
void fn_sub_1DD600_001dd600(p3fes::EEContext&);
void fn_sub_1DD8E0_001dd8e0(p3fes::EEContext&);
void fn_sub_1DDCA0_001ddca0(p3fes::EEContext&);
void fn_sub_1DDE00_001dde00(p3fes::EEContext&);
void fn_sub_1E1230_001e1230(p3fes::EEContext&);
void fn_sub_1E1300_001e1300(p3fes::EEContext&);
void fn_sub_1E7200_001e7200(p3fes::EEContext&);
void fn_sub_1E7290_001e7290(p3fes::EEContext&);
void fn_sub_1E7410_001e7410(p3fes::EEContext&);
void fn_sub_2FF260_002ff260(p3fes::EEContext&);
void fn_sub_2FF310_002ff310(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_318540_00318540(p3fes::EEContext&);
void fn_sub_318770_00318770(p3fes::EEContext&);
void fn_sub_318990_00318990(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318D10_00318d10(p3fes::EEContext&);
void fn_sub_3191F0_003191f0(p3fes::EEContext&);
void fn_sub_319200_00319200(p3fes::EEContext&);
void fn_sub_3196F0_003196f0(p3fes::EEContext&);
void fn_sub_319770_00319770(p3fes::EEContext&);
void fn_sub_31C1D0_0031c1d0(p3fes::EEContext&);
void fn_sub_350080_00350080(p3fes::EEContext&);
void fn_sub_3952D0_003952d0(p3fes::EEContext&);
void fn_sub_396F50_00396f50(p3fes::EEContext&);
void fn_sub_3B58C0_003b58c0(p3fes::EEContext&);
void fn_sub_3B5980_003b5980(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7B90_003c7b90(p3fes::EEContext&);
void fn_sub_3C8F20_003c8f20(p3fes::EEContext&);
void fn_sub_3C8F70_003c8f70(p3fes::EEContext&);
void fn_sub_429E80_00429e80(p3fes::EEContext&);
void fn_sub_429E90_00429e90(p3fes::EEContext&);
void fn_sub_42BA30_0042ba30(p3fes::EEContext&);
void fn_sub_4350E0_004350e0(p3fes::EEContext&);
void fn_sub_4352E0_004352e0(p3fes::EEContext&);
void fn_sub_4353F0_004353f0(p3fes::EEContext&);
void fn_sub_4532D0_004532d0(p3fes::EEContext&);
void fn_sub_4533E0_004533e0(p3fes::EEContext&);
void fn_sub_453460_00453460(p3fes::EEContext&);
void fn_sub_453470_00453470(p3fes::EEContext&);
void fn_sub_453480_00453480(p3fes::EEContext&);
void fn_sub_455B50_00455b50(p3fes::EEContext&);
void fn_sub_458890_00458890(p3fes::EEContext&);
void fn_sub_458930_00458930(p3fes::EEContext&);
void fn_sub_45A400_0045a400(p3fes::EEContext&);
void fn_sub_45A430_0045a430(p3fes::EEContext&);
void fn_sub_45AF40_0045af40(p3fes::EEContext&);
void fn_sub_45AF70_0045af70(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C43B0_004c43b0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001C8620 K_FldEvent_UpdateFldEventTask -- 20296 bytes; frame 0x360: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// K_FldEvent_UpdateFldEventTask(task) -> 0 (the field event task, sField +8; 26_field.md 5.1 / 7.1; work: field4.h
// evt). Every frame, before the 33-state switch (jump table 0x7B6BD0): the draw-command task (sField +8 -> sub_1CD650);
// the game-over check (state > 0, no battle +100, sub_45AF40() == 0 and the latch +16 clear: sounds off, fade 90,
// flag 5149, the script task +96 destroyed, state 29, +16 = 1); the two count-downs +248 (0 -> sub_4533E0(0), -1)
// and +252 (the talk cool-down). The states (the case comments below):
//   0 the hero's character resource (id 1024) -> +20                                                       -> 1
//   1 exploring (unless paused by +4 / +8): in this order
//     a. a shadow contact (sub_453460 >= 0): +36 = gFldUnitsEc[i]; alive -> the 52-byte battle packet at +40
//        (sub_1C7830; flags bits 0 / 1; background field = ENCOUNT +18 / +20, or major + 200 / 1), pad / scheduler /
//        enemies / footsteps paused, the hero's attack pose                                               -> 4
//     b. pad 0x80 in a scene that allows it (sub_1C6080): the field's header script (g_fldMainScriptPtr,
//        procedure 2) -> +96, everything paused                                                           -> 2
//     c. pad 0x10 and flag 369 clear: the camp menu (pad / mini-map / party panel destroyed, the area panel off,
//        the field paused, the pre-battle task lists sField +4308 [4] / +4324 [24] destroyed)             -> 23
//     d. the held weapon type (datCalcGetHeldWeaponType) -> +236 and its swing record 0x7CE294 + 24 type -> +256;
//        the nearest interactable unit (sub_1C6A20) -> +36; pad 0x40 with none: an attack swing (below)
//     e. a dungeon field hit under the hero (K_FldEvent_IsUnitNearFldHit): the prompt (+224); confirm -> the
//        dungeon script procedure 0 (stairs / transporter)                                                -> 2
//     f. random floors: scene resource 11263 within 200 of the hero: confirm -> dungeon script procedure 1 -> 2
//     g. treasure: the hero's 4 x 4-cell bucket (0x86B180 + 4 (49 bx + 196 bz)), an unopened box within 200
//        (0x7CE284): confirm -> opened, the field script procedure 0                                       -> 2
//     h. an NPC to talk to (sub_1C74C0 -> +28; its FBN slot kind +500): a schedule NPC (+504) or a social-link
//        NPC (+508): a message (msgWinRequestMessage; sub_1B8FD0 picks a conditional one) -> 21, or its script
//        procedure -> 22; the NPC turns (pose +32)
//     i. a field hit at the hero's feet (K_FldEvent_FindFldHitAt on the resource +20): its 44-byte exit record
//        (sField +4424 + 44 id; K_Assert k_event.c 1878; field4.h exitrec): all its flags set, the area name
//        (+228), the facing test (kind +12 == 1: the side +32 must be in view, sub_1C6200); confirm (when +13);
//        a door (procedure 0xFFFF): the door object animates, its sound, state 3; else the field script
//        procedure                                                                                     -> 3 / 2
//     j. a unit with a header script (sub_1C6F50 / sub_4353F0): its procedure 9                            -> 2
//     k. the attack swing (step d, Tartarus-type scenes only): the swing pose and sound per weapon type, the
//        swing record's timings, the camera mode saved (+244)                                             -> 8
//     then the prompt icon (0x871914) above the hero while +224 is set.
//   2 the script task (+96) done: everything unpaused                                                      -> 1
//   3 a door: K_Field_RequestNextField(root, exit +18 / +20 / +22)                                        -> 32
//   4 the player struck first: at frame 13 of the enemy's pose the encounter flash EPL (sField +4596) 100 above the
//     contacted unit, SFX, the hero's pose 2, pauses                                                        -> 5
//   5 the flash has run 5 frames: sub_2FF260(0) (the encounter fade)                                        -> 9
//   6 the enemy struck first (ambush): pauses, the flash at the enemy (The Answer: +4628 turned by the hero's
//     matrix and 0x683740)                                                                                   -> 7
//   7 the flash has run 5 (The Answer 4) frames: sub_2FF260(0)                                              -> 9
//   8 the attack swing: hit test against the shadows while the swing runs (a hit -> the packet, 4 or the ambush
//     path 6), else back                                                                                   -> 1
//   9 the field torn down for the battle: mini-map, walls, panels, pad, camera (its matrices saved,
//     sub_1D68E0), the exit table, the Tartarus block models, the scene unloaded (sub_3B5AB0)              -> 10
//  10..13 one frame each                                                                                   -> 14
//  14 the tutorial encounters 466..469 clear flags 3574..3577; the pre-battle tasks; btlStart(+40) -> +100 -> 15
//  15 the battle done and the packs resident: victory / escape (sub_45AF40) -> the enemy destroyed (not the
//     Reaper 506), the party revived (flag 3105), sub_1D11B0 -> 16; the hero dead -> the game-over script
//     procedure 1 -> 31; else fade -> 30
//  16 the exit table "field/table/h%03d_%03d.bin", the field script, MT_Scene_Load + sub-ids                -> 17
//  17 all loaded (sub_1C7F20, sub_1E7290, sub_1C0740, sub_1D12D0, sub_3B5A10)                             -> 18
//  18 the camera (K_FldCamera_CreateFieldCameraControlerTask), walls, mini-map, pad recreated, flag 5137   -> 19
//  19 / 20 the fade in, the party panel                                                                   -> 1
//  21 the NPC message window closed ("---->%d")                                                            -> 1
//  22 the NPC script done                                                                                  -> 1
//  23 the field units settled: walls / camera paused, the held weapon and equipment remembered (+236 / +240),
//     the camp menu (H_Camp_CreateDrawTask -> +104)                                                       -> 24
//  24 the menu closed: flag 5143 -> the header script procedure 3 -> 28; else the hero's model reloaded when the
//     weapon / the listed equipment changed                                                                -> 25
//  25 the model ready: the party panel recreated, the panels on, the party restored at 32/2, 39/1, 39/3   -> 26
//  26 the party field units, panel, enemies and mini-map recreated                                        -> 27
//  27 all ready: the hero's resource (+20), walls and camera resumed, the virtual pad recreated             -> 1
//  28 wait for that script
//  29 / 30 the game-over / fade-out: the field script procedure 1 (g_fldMainScriptPtr)                     -> 31
//  31 the end script runs
//  32 a door: wait for the root to change the field.
void K_FldEvent_UpdateFldEventTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x001c8620
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x360);
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lw(s3, a0, f4::kTaskWork);
    s7 = 0;
    jal(ctx, 0x1C8658u, gen::fn_K_Field_Get_001b9120);
    lw(a0, v0, f4::fld::kEventTask);
    lw(a1, gp, -19172);  // 0x7CE20C
    jal(ctx, 0x1C8668u, gen::fn_sub_1CD650_001cd650);
    lw(v0, s3, f4::evt::kState);
    if (i64(v0) > 0) {
        // 0x001c867c
        charge(ctx, 3);
        lw(v0, s3, f4::evt::kBattle);
        if (v0 == 0) {
            // 0x001c8688
            charge(ctx, 4);
            jal(ctx, 0x1C8688u, gen::fn_sub_45AF40_0045af40);
            if (v0 == 0) {
                // 0x001c8698
                charge(ctx, 3);
                lw(v0, s3, f4::evt::kGameOver);
                if (v0 == 0) {
                    // 0x001c86a4
                    charge(ctx, 30);
                    a0 = 3;
                    a1 = 0;
                    jal(ctx, 0x1C86ACu, gen::fn_sub_109F60_00109f60);
                    a0 = 0;
                    a1 = 135;
                    a2 = 3;
                    jal(ctx, 0x1C86C0u, gen::fn_sub_3952D0_003952d0);
                    jal(ctx, 0x1C86C8u, gen::fn_sub_108570_00108570);
                    a0 = 90;
                    jal(ctx, 0x1C86D4u, gen::fn_sub_1086A0_001086a0);
                    a0 = 6;
                    jal(ctx, 0x1C86E0u, gen::fn_sub_108670_00108670);
                    a0 = 90;
                    jal(ctx, 0x1C86ECu, gen::fn_sub_108FD0_00108fd0);
                    a0 = 0;
                    jal(ctx, 0x1C86F8u, gen::fn_sub_396F50_00396f50);
                    jal(ctx, 0x1C8700u, gen::fn_sub_3C8F70_003c8f70);
                    jal(ctx, 0x1C8708u, gen::fn_sub_3C8F20_003c8f20);
                    lw(a0, s3, f4::evt::kScript);
                    if (a0 != 0) {
                        // 0x001c871c
                        charge(ctx, 2);
                        jal(ctx, 0x1C871Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x001c8724
                    charge(ctx, 8);
                    a0 = 5149;
                    a1 = 1;
                    jal(ctx, 0x1C872Cu, gen::fn_datSetFlag_0016f1f0);
                    v0 = 29;
                    sw(v0, s3, f4::evt::kState);
                    v0 = 1;
                    sw(v0, s3, f4::evt::kGameOver);
                }
            }
        }
    }
    // 0x001c8744
    charge(ctx, 3);
    lw(v0, s3, f4::evt::kCountdown);
    if (v0 != 0) {
        // 0x001c876c
        charge(ctx, 2);
        if (i64(v0) > 0) {
            // 0x001c8774
            charge(ctx, 2);
            v0 = addiu(v0, -1);
            sw(v0, s3, f4::evt::kCountdown);
        }
    } else {
        // 0x001c8750
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x1C8754u, gen::fn_sub_4533E0_004533e0);
        v0 = si(-1);
        sw(v0, s3, f4::evt::kCountdown);
    }
    // 0x001c877c
    charge(ctx, 3);
    lw(v0, s3, f4::evt::kTalkCooldown);
    if (i64(v0) > 0) {
        // 0x001c8788
        charge(ctx, 2);
        v0 = addiu(v0, -1);
        sw(v0, s3, f4::evt::kTalkCooldown);
    }
    // 0x001c8790
    charge(ctx, 4);
    lw(a0, s3, f4::evt::kState);
    at = sltiu(a0, 33);
    if (at != 0) {
        // 0x001c87a0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27600);  // &0x7B6BD0
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1C87BCu:  // table[0]  -- state 0: the hero's character resource (scene id 1024) -> +20; then the prompt icon epilogue
            // 0x001c87bc
            charge(ctx, 9);
            a0 = 1024;
            jal(ctx, 0x1C87C0u, gen::fn_sub_3B5D10_003b5d10);
            sw(v0, s3, f4::evt::kHero);
            lw(v0, s3, f4::evt::kState);
            v0 = addiu(v0, 1);
            sw(v0, s3, f4::evt::kState);
        // the shared tail of every state (state 31 jumps here directly): the prompt icon (0x871914) above the hero while +224 is set
        L_001cd48c:
            charge(ctx, 4);
            lw(v1, s3, f4::evt::kPrompt);
            v0 = 1;
            if (v1 != v0) {
                // 0x001cd514
                charge(ctx, 4);
                v0 = 0x870000;
                lw(a0, v0, 6420);  // 0x871914
                if (a0 != 0) {
                    // 0x001cd524
                    charge(ctx, 3);
                    a1 = 0;
                    jal(ctx, 0x1CD528u, gen::fn_sub_1DD5E0_001dd5e0);
                }
            } else {
                // 0x001cd49c
                charge(ctx, 21);
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                jal(ctx, 0x1CD4A4u, gen::fn_sub_318B60_00318b60);
                a1 = addiu(sp, 0x290);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x290);
                swc1(f1, sp, 0x294);
                swc1(f0, sp, 0x298);
                lwc1(f1, sp, 0x294);
                v0 = 0x43480000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x294);
                v0 = 0x870000;
                lw(a0, v0, 6420);  // 0x871914
                if (a0 != 0) {
                    // 0x001cd4f0
                    charge(ctx, 9);
                    jal(ctx, 0x1CD4F0u, gen::fn_sub_1DD530_001dd530);
                    v0 = 0x870000;
                    lw(a0, v0, 6420);  // 0x871914
                    a1 = 1;
                    jal(ctx, 0x1CD504u, gen::fn_sub_1DD5E0_001dd5e0);
                }
            }
            // 0x001cd530
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1C87E0u:  // table[1]  -- state 1: exploring -- contact, header script, camp menu, stairs, terminal, treasure, NPC, field hits, swing
            // 0x001c87e0
            charge(ctx, 4);
            lw(v0, s3, f4::evt::kPauseA);
            v1 = 1;
            if (v0 != v1) {
                // 0x001c87f0
                charge(ctx, 3);
                lw(v0, s3, f4::evt::kPauseB);
                if (v0 != v1) {
                    // 0x001c87fc
                    charge(ctx, 12);
                    lw(a0, s3, f4::evt::kDrawCmd);
                    a1 = 0;
                    jal(ctx, 0x1C8804u, gen::fn_sub_1CD790_001cd790);
                    sw(zero, s3, f4::evt::kPrompt);
                    jal(ctx, 0x1C8810u, gen::fn_sub_453460_00453460);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    at = slti(v0, 0);
                    if (at != 0) {
                        // 0x001c8978
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x80;
                        if (v0 != 0) {
                            // 0x001c898c
                            charge(ctx, 5);
                            jal(ctx, 0x1C898Cu, gen::fn_sub_1C6080_001c6080);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_001c8ae4;
                            }
                            // 0x001c89a0
                            charge(ctx, 49);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x1C89B0u, gen::fn_sub_10A4E0_0010a4e0);
                            a0 = 10;
                            lw(a1, gp, -19144);  // g_fldMainScriptPtr
                            a2 = 2;
                            jal(ctx, 0x1C89C4u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                            sw(v0, s3, f4::evt::kScript);
                            a0 = v0;
                            a1 = 0;
                            jal(ctx, 0x1C89D8u, gen::fn_scrSetUserData_0035c1a0);
                            jal(ctx, 0x1C89E0u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kVirtualPad);
                            a1 = 1;
                            jal(ctx, 0x1C89F0u, gen::fn_sub_1E1300_001e1300);
                            a0 = 1;
                            jal(ctx, 0x1C89FCu, gen::fn_sub_1D8C60_001d8c60);
                            jal(ctx, 0x1C8A04u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kFootstep);
                            a1 = 1;
                            jal(ctx, 0x1C8A14u, gen::fn_sub_1DA000_001da000);
                            jal(ctx, 0x1C8A1Cu, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEnemySched);
                            a1 = 1;
                            jal(ctx, 0x1C8A2Cu, gen::fn_sub_1D37F0_001d37f0);
                            a0 = 1;
                            jal(ctx, 0x1C8A38u, gen::fn_sub_4532D0_004532d0);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x1C8A48u, gen::fn_sub_4350E0_004350e0);
                            jal(ctx, 0x1C8A50u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kSmap);
                            if (v0 != 0) {
                                // 0x001c8a64
                                charge(ctx, 6);
                                jal(ctx, 0x1C8A64u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kSmap);
                                a1 = 0;
                                jal(ctx, 0x1C8A74u, gen::fn_sub_429E80_00429e80);
                            }
                            // 0x001c8a7c
                            charge(ctx, 5);
                            jal(ctx, 0x1C8A7Cu, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kPartyPanel);
                            if (v0 != 0) {
                                // 0x001c8a90
                                charge(ctx, 6);
                                jal(ctx, 0x1C8A90u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kPartyPanel);
                                a1 = 0;
                                jal(ctx, 0x1C8AA0u, gen::fn_sub_18C0C0_0018c0c0);
                            }
                            // 0x001c8aa8
                            charge(ctx, 5);
                            jal(ctx, 0x1C8AA8u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kAreaPanel);
                            if (v0 != 0) {
                                // 0x001c8abc
                                charge(ctx, 6);
                                jal(ctx, 0x1C8ABCu, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kAreaPanel);
                                a1 = 0;
                                jal(ctx, 0x1C8ACCu, gen::fn_sub_18EB30_0018eb30);
                            }
                            // 0x001c8ad4
                            charge(ctx, 4);
                            v0 = 2;
                            sw(v0, s3, f4::evt::kState);
                            goto L_001cd48c;
                        }
                    L_001c8ae4:
                        charge(ctx, 5);
                        a0 = 369;
                        jal(ctx, 0x1C8AE8u, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            // 0x001c8af8
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, 2382);  // gPadFlags
                            v0 = v0 & 0x10;
                            if (v0 == 0) {
                                goto L_001c8d60;
                            }
                            // 0x001c8b0c
                            charge(ctx, 5);
                            jal(ctx, 0x1C8B0Cu, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kVirtualPad);
                            if (v0 != 0) {
                                // 0x001c8b20
                                charge(ctx, 8);
                                jal(ctx, 0x1C8B20u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kVirtualPad);
                                jal(ctx, 0x1C8B2Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                jal(ctx, 0x1C8B34u, gen::fn_K_Field_Get_001b9120);
                                sw(zero, v0, f4::fld::kVirtualPad);
                            }
                            // 0x001c8b40
                            charge(ctx, 5);
                            jal(ctx, 0x1C8B40u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kSmap);
                            if (v0 != 0) {
                                // 0x001c8b54
                                charge(ctx, 8);
                                jal(ctx, 0x1C8B54u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kSmap);
                                jal(ctx, 0x1C8B60u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                jal(ctx, 0x1C8B68u, gen::fn_K_Field_Get_001b9120);
                                sw(zero, v0, f4::fld::kSmap);
                            }
                            // 0x001c8b74
                            charge(ctx, 5);
                            jal(ctx, 0x1C8B74u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kPartyPanel);
                            if (v0 != 0) {
                                // 0x001c8b88
                                charge(ctx, 8);
                                jal(ctx, 0x1C8B88u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kPartyPanel);
                                jal(ctx, 0x1C8B94u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                jal(ctx, 0x1C8B9Cu, gen::fn_K_Field_Get_001b9120);
                                sw(zero, v0, f4::fld::kPartyPanel);
                            }
                            // 0x001c8ba8
                            charge(ctx, 5);
                            jal(ctx, 0x1C8BA8u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kAreaPanel);
                            if (v0 != 0) {
                                // 0x001c8bbc
                                charge(ctx, 6);
                                jal(ctx, 0x1C8BBCu, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kAreaPanel);
                                a1 = 0;
                                jal(ctx, 0x1C8BCCu, gen::fn_sub_18EB30_0018eb30);
                            }
                            // 0x001c8bd4
                            charge(ctx, 39);
                            a0 = 1;
                            jal(ctx, 0x1C8BD8u, gen::fn_sub_1D1860_001d1860);
                            jal(ctx, 0x1C8BE0u, gen::fn_sub_1D1910_001d1910);
                            jal(ctx, 0x1C8BE8u, gen::fn_sub_1D1B60_001d1b60);
                            jal(ctx, 0x1C8BF0u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEnemySched);
                            a1 = 1;
                            jal(ctx, 0x1C8C00u, gen::fn_sub_1D37F0_001d37f0);
                            a0 = 1;
                            jal(ctx, 0x1C8C0Cu, gen::fn_sub_4532D0_004532d0);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x1C8C1Cu, gen::fn_sub_4350E0_004350e0);
                            jal(ctx, 0x1C8C24u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kFootstep);
                            a1 = 1;
                            jal(ctx, 0x1C8C34u, gen::fn_sub_1DA000_001da000);
                            a0 = 1;
                            jal(ctx, 0x1C8C40u, gen::fn_sub_45A430_0045a430);
                            a0 = 1;
                            jal(ctx, 0x1C8C4Cu, gen::fn_sub_45AF70_0045af70);
                            jal(ctx, 0x1C8C54u, gen::fn_sub_1D4180_001d4180);
                            jal(ctx, 0x1C8C5Cu, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kEplDamage);
                            if (v0 != 0) {
                                // 0x001c8c70
                                charge(ctx, 5);
                                jal(ctx, 0x1C8C70u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kEplDamage);
                                jal(ctx, 0x1C8C7Cu, gen::fn_sub_1A9470_001a9470);
                            }
                            // 0x001c8c84
                            charge(ctx, 9);
                            jal(ctx, 0x1C8C84u, gen::fn_sub_3C8F70_003c8f70);
                            jal(ctx, 0x1C8C8Cu, gen::fn_sub_3C8F20_003c8f20);
                            jal(ctx, 0x1C8C94u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kBattleTasks);
                            if (v0 != 0) {
                                // 0x001c8ca8
                                charge(ctx, 3);
                                s1 = 0;
                                for (;;) {
                                    // 0x001c8ce4
                                    charge(ctx, 3);
                                    v0 = slti(s1, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001c8cb4
                                    charge(ctx, 12);
                                    s0 = sll(s1, 2);
                                    jal(ctx, 0x1C8CB8u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s0);
                                    lw(a0, v0, f4::fld::kBattleTasks);
                                    jal(ctx, 0x1C8CC8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                    jal(ctx, 0x1C8CD0u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s0);
                                    sw(zero, v0, f4::fld::kBattleTasks);
                                    s1 = addiu(s1, 1);
                                }
                                // 0x001c8cf0
                                charge(ctx, 3);
                                s0 = 0;
                                for (;;) {
                                    // 0x001c8d44
                                    charge(ctx, 3);
                                    v0 = slti(s0, 24);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001c8cfc
                                    charge(ctx, 7);
                                    s1 = sll(s0, 2);
                                    jal(ctx, 0x1C8D00u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kBattleTasks2);
                                    if (v0 != 0) {
                                        // 0x001c8d18
                                        charge(ctx, 10);
                                        jal(ctx, 0x1C8D18u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        lw(a0, v0, f4::fld::kBattleTasks2);
                                        jal(ctx, 0x1C8D28u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                                        jal(ctx, 0x1C8D30u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        sw(zero, v0, f4::fld::kBattleTasks2);
                                    }
                                    // 0x001c8d40
                                    charge(ctx, 1);
                                    s0 = addiu(s0, 1);
                                }
                            }
                            // 0x001c8d50
                            charge(ctx, 4);
                            v0 = 23;
                            sw(v0, s3, f4::evt::kState);
                            goto L_001cd48c;
                        }
                    L_001c8d60:
                        charge(ctx, 26);
                        v0 = 0x870000;
                        lw(v0, v0, 6120);  // 0x8717E8
                        lw(a0, v0, 4);
                        jal(ctx, 0x1C8D6Cu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                        v1 = v0 & 0xFF;
                        sw(v1, s3, f4::evt::kWeapon);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 3);
                        lw(v0, gp, -19036);  // 0x7CE294
                        v1 = addu(v0, v1);
                        sw(v1, s3, f4::evt::kSwing);
                        v0 = 0x43340000;
                        mtc1(v0, f13);
                        a0 = 0x870000;
                        a0 = addiu(a0, 6048);  // &gFldUnitsPc
                        lwc1(f12, v1, 20);
                        jal(ctx, 0x1C8DA8u, gen::fn_sub_1C6A20_001c6a20);
                        sw(v0, s3, f4::evt::kTarget);
                        v0 = 0x7E0000;
                        lhu(v0, v0, 2382);  // gPadFlags
                        v0 = v0 & 0x40;
                        if (v0 != 0) {
                            // 0x001c8dc8
                            charge(ctx, 3);
                            lw(v0, s3, f4::evt::kTarget);
                            if (v0 == 0) {
                                // 0x001c8dd4
                                charge(ctx, 1);
                                s7 = 1;
                                goto L_001c8dd8;
                            }
                        L_001ca5a8:
                            charge(ctx, 4);
                            jal(ctx, 0x1CA5A8u, gen::fn_sub_1A01C0_001a01c0);
                            if (v0 != 0) {
                                // 0x001ca5b8
                                charge(ctx, 5);
                                lw(a1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(a0, a1, f4::scene::kMajor);
                                v0 = 32;
                                if (a0 == v0) {
                                    // 0x001ca5cc
                                    charge(ctx, 4);
                                    lw(v1, a1, 4);
                                    v0 = 2;
                                    if (v1 != v0) {
                                        goto L_001ca5dc;
                                    }
                                    goto L_001cd48c;
                                }
                            L_001ca5dc:
                                charge(ctx, 3);
                                v0 = 35;
                                if (a0 == v0) {
                                    // 0x001ca5e8
                                    charge(ctx, 4);
                                    lw(v1, a1, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001ca5f8;
                                    }
                                    goto L_001cd48c;
                                }
                            L_001ca5f8:
                                charge(ctx, 3);
                                v0 = 37;
                                if (a0 == v0) {
                                    // 0x001ca604
                                    charge(ctx, 4);
                                    lw(v1, a1, 4);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        goto L_001ca614;
                                    }
                                    goto L_001cd48c;
                                }
                            L_001ca614:
                                charge(ctx, 3);
                                v0 = 33;
                                if (a0 != v0) {
                                    // 0x001ca620
                                    charge(ctx, 11);
                                    jal(ctx, 0x1CA620u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kVirtualPad);
                                    a1 = 1;
                                    jal(ctx, 0x1CA630u, gen::fn_sub_1E1300_001e1300);
                                    jal(ctx, 0x1CA638u, gen::fn_sub_17D800_0017d800);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x001ca64c
                                        charge(ctx, 8);
                                        v0 = 0x40000000;
                                        mtc1(v0, f12);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        a1 = 0;
                                        jal(ctx, 0x1CA660u, gen::fn_sub_3189F0_003189f0);
                                        sw(zero, s3, 232);
                                    }
                                    // 0x001ca66c
                                    charge(ctx, 34);
                                    v0 = 0x870000;
                                    lw(a0, v0, 6128);  // 0x8717F0
                                    a1 = 0;
                                    a2 = 4;
                                    a3 = 0;
                                    t0 = 32;
                                    jal(ctx, 0x1CA684u, gen::fn_sub_3182D0_003182d0);
                                    v0 = 0x870000;
                                    lw(v0, v0, 6120);  // 0x8717E8
                                    lw(a0, v0, 4);
                                    jal(ctx, 0x1CA698u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                                    v1 = v0 & 0xFF;
                                    sw(v1, s3, f4::evt::kWeapon);
                                    v0 = sll(v1, 1);
                                    v0 = addu(v0, v1);
                                    v1 = sll(v0, 3);
                                    lw(v0, gp, -19036);  // 0x7CE294
                                    v0 = addu(v0, v1);
                                    sw(v0, s3, f4::evt::kSwing);
                                    lh(v0, v0, 0);
                                    mtc1(v0, f0);
                                    cvt_s_w(f12, f0);
                                    v0 = 0x870000;
                                    lw(a0, v0, 6128);  // 0x8717F0
                                    a1 = 0;
                                    jal(ctx, 0x1CA6DCu, gen::fn_sub_318770_00318770);
                                    lw(v0, s3, f4::evt::kWeapon);
                                    at = sltiu(v0, 8);
                                    if (at != 0) {
                                        // 0x001ca6f4
                                        charge(ctx, 7);
                                        v1 = 0x7B0000;
                                        v1 = addiu(v1, 27568);  // &0x7B6BB0
                                        v0 = sll(v0, 2);
                                        v0 = addu(v0, v1);
                                        lw(v0, v0, 0);
                                        switch (v0.u()) {
                                        case 0x1CA710u:  // table[0]
                                            // 0x001ca710
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 68;
                                            jal(ctx, 0x1CA720u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA730u:  // table[1]
                                            // 0x001ca730
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 69;
                                            jal(ctx, 0x1CA740u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA750u:  // table[2]
                                            // 0x001ca750
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 70;
                                            jal(ctx, 0x1CA760u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA770u:  // table[3]
                                            // 0x001ca770
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 71;
                                            jal(ctx, 0x1CA780u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA790u:  // table[4]
                                            // 0x001ca790
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 72;
                                            jal(ctx, 0x1CA7A0u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA7B0u:  // table[5, 6]
                                            // 0x001ca7b0
                                            charge(ctx, 8);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = a0;
                                            a3 = 73;
                                            jal(ctx, 0x1CA7C0u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        case 0x1CA7D0u:  // table[7]
                                            // 0x001ca7d0
                                            charge(ctx, 6);
                                            a0 = 1;
                                            a1 = 8;
                                            a2 = 4;
                                            a3 = 10;
                                            jal(ctx, 0x1CA7E0u, gen::fn_sub_10A4E0_0010a4e0);
                                            break;
                                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                            tail(ctx, v0.u());
                                            return;
                                        }
                                    }
                                    // 0x001ca7e8
                                    charge(ctx, 7);
                                    lw(v0, s3, f4::evt::kSwing);
                                    lh(v1, v0, 4);
                                    lh(v0, v0, 0);
                                    v1 = subu(v1, v0);
                                    sw(v1, s3, 260);
                                    if (v1 == 0) {
                                        // 0x001ca830
                                        charge(ctx, 1);
                                        sw(zero, s3, 268);
                                    } else {
                                        // 0x001ca804
                                        charge(ctx, 11);
                                        lw(v0, s3, f4::evt::kSwing);
                                        mtc1(v1, f0);
                                        cvt_s_w(f1, f0);
                                        lwc1(f0, v0, 8);
                                        div_s(f0, f0, f1);
                                        swc1(f0, s3, 268);
                                    }
                                    // 0x001ca834
                                    charge(ctx, 7);
                                    lw(v0, s3, f4::evt::kSwing);
                                    lh(v1, v0, 2);
                                    lh(v0, v0, 6);
                                    v1 = subu(v1, v0);
                                    sw(v1, s3, 264);
                                    if (v1 == 0) {
                                        // 0x001ca87c
                                        charge(ctx, 1);
                                        sw(zero, s3, 272);
                                    } else {
                                        // 0x001ca850
                                        charge(ctx, 11);
                                        lw(v0, s3, f4::evt::kSwing);
                                        mtc1(v1, f0);
                                        cvt_s_w(f1, f0);
                                        lwc1(f0, v0, 8);
                                        div_s(f0, f0, f1);
                                        swc1(f0, s3, 272);
                                    }
                                    // 0x001ca880
                                    charge(ctx, 30);
                                    v0 = 0x870000;
                                    lw(a0, v0, 6128);  // 0x8717F0
                                    jal(ctx, 0x1CA888u, gen::fn_sub_318B60_00318b60);
                                    lwc1(f2, v0, 48);
                                    lwc1(f1, v0, 52);
                                    lwc1(f0, v0, 56);
                                    swc1(f2, s3, 276);
                                    swc1(f1, s3, 280);
                                    swc1(f0, s3, 284);
                                    a0 = 1;
                                    jal(ctx, 0x1CA8ACu, gen::fn_sub_1D8C60_001d8c60);
                                    jal(ctx, 0x1CA8B4u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kCamera);
                                    jal(ctx, 0x1CA8C0u, gen::fn_sub_1D5C00_001d5c00);
                                    sw(v0, s3, f4::evt::kCameraMode);
                                    jal(ctx, 0x1CA8CCu, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kCamera);
                                    a1 = 1;
                                    jal(ctx, 0x1CA8DCu, gen::fn_sub_1D5C10_001d5c10);
                                    jal(ctx, 0x1CA8E4u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kSmap);
                                    if (v0 != 0) {
                                        // 0x001ca8f8
                                        charge(ctx, 6);
                                        jal(ctx, 0x1CA8F8u, gen::fn_K_Field_Get_001b9120);
                                        lw(a0, v0, f4::fld::kSmap);
                                        a1 = 1;
                                        jal(ctx, 0x1CA908u, gen::fn_sub_429E90_00429e90);
                                    }
                                    // 0x001ca910
                                    charge(ctx, 4);
                                    v0 = 8;
                                    sw(v0, s3, f4::evt::kState);
                                }
                            }
                            goto L_001cd48c;
                        }
                    L_001c8dd8:
                        charge(ctx, 7);
                        a0 = 0x870000;
                        a0 = addiu(a0, 6048);  // &gFldUnitsPc
                        jal(ctx, 0x1C8DE0u, gen::fn_K_FldEvent_IsUnitNearFldHit_001c7b30);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x001c8f50
                            charge(ctx, 5);
                            s1 = 0;
                            jal(ctx, 0x1C8F54u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                            if (v0 != 0) {
                                // 0x001c8f6c
                                charge(ctx, 4);
                                v0 = 0x870000;
                                lw(v0, v0, 6120);  // 0x8717E8
                                if (v0 != 0) {
                                    // 0x001c8f7c
                                    charge(ctx, 6);
                                    a0 = 11263;
                                    jal(ctx, 0x1C8F80u, gen::fn_sub_3B5D10_003b5d10);
                                    s0 = v0;
                                    if (s0 != 0) {
                                        // 0x001c8f9c
                                        charge(ctx, 42);
                                        lw(a0, s0, 260);
                                        jal(ctx, 0x1C8FA0u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f20, v0, 48);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C8FB4u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f0, v0, 48);
                                        sub_s(f0, f20, f0);
                                        swc1(f0, sp, 0x280);
                                        lw(a0, s0, 260);
                                        jal(ctx, 0x1C8FCCu, gen::fn_sub_318B60_00318b60);
                                        lwc1(f20, v0, 52);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C8FE0u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f0, v0, 52);
                                        sub_s(f0, f20, f0);
                                        swc1(f0, sp, 0x284);
                                        lw(a0, s0, 260);
                                        jal(ctx, 0x1C8FF8u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f20, v0, 56);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C900Cu, gen::fn_sub_318B60_00318b60);
                                        lwc1(f0, v0, 56);
                                        sub_s(f0, f20, f0);
                                        swc1(f0, sp, 0x288);
                                        a0 = addiu(sp, 0x280);
                                        jal(ctx, 0x1C9024u, gen::fn_sub_4C6AC0_004c6ac0);
                                        v0 = 0x43480000;
                                        mtc1(v0, f1);
                                        c_lt_s(f0, f1);
                                        if (cond(ctx)) {
                                            // 0x001c9044
                                            charge(ctx, 1);
                                            s1 = 1;
                                        }
                                    } else {
                                        // 0x001c8f94
                                        charge(ctx, 2);
                                    }
                                }
                            } else {
                                // 0x001c8f64
                                charge(ctx, 2);
                            }
                            // 0x001c9048
                            charge(ctx, 3);
                            v1 = 1;
                            if (s1 != v1) {
                                // 0x001c91b0
                                charge(ctx, 10);
                                v0 = 0x870000;
                                lw(a0, v0, 6128);  // 0x8717F0
                                jal(ctx, 0x1C91B8u, gen::fn_sub_318B60_00318b60);
                                s1 = addiu(v0, 48);
                                s0 = 0;
                                jal(ctx, 0x1C91C8u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                                if (v0 != 0) {
                                    // 0x001c91d8
                                    charge(ctx, 16);
                                    v0 = 0x43C80000;
                                    mtc1(v0, f1);
                                    lwc1(f0, s1, 0);
                                    add_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x44480000;
                                    mtc1(v0, f0);
                                    div_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(v0, f0);
                                    s0 = sra(v0, 2);
                                    if (i64(v0) < 0) {
                                        // 0x001c9218
                                        charge(ctx, 2);
                                        v0 = addiu(v0, 3);
                                        s0 = sra(v0, 2);
                                    }
                                }
                                // 0x001c9220
                                charge(ctx, 10);
                                v0 = 0x870000;
                                lw(a0, v0, 6128);  // 0x8717F0
                                jal(ctx, 0x1C9228u, gen::fn_sub_318B60_00318b60);
                                s2 = addiu(v0, 48);
                                s1 = 0;
                                jal(ctx, 0x1C9238u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                                if (v0 != 0) {
                                    // 0x001c9248
                                    charge(ctx, 17);
                                    lwc1(f1, s2, 8);
                                    v0 = 0x43C80000;
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    cvt_w_s(f0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x44480000;
                                    mtc1(v0, f0);
                                    div_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(v0, f0);
                                    s1 = sra(v0, 2);
                                    if (i64(v0) < 0) {
                                        // 0x001c928c
                                        charge(ctx, 2);
                                        v0 = addiu(v0, 3);
                                        s1 = sra(v0, 2);
                                    }
                                }
                                // 0x001c9294
                                charge(ctx, 17);
                                s4 = 0;
                                v0 = sll(s1, 3);
                                v1 = subu(v0, s1);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                s2 = sll(v0, 4);
                                v0 = sll(s0, 3);
                                v1 = subu(v0, s0);
                                v0 = sll(v1, 3);
                                v0 = subu(v0, v1);
                                s1 = sll(v0, 2);
                                v0 = 0x870000;
                                v0 = addiu(v0, -20096);  // &0x86B180
                                v0 = addu(v0, s2);
                                s5 = addu(s1, v0);
                                for (;;) {
                                    // 0x001c93a4
                                    charge(ctx, 5);
                                    s6 = sll(s4, 2);
                                    v0 = addu(s5, s6);
                                    lw(v0, v0, 96);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001c92d8
                                    charge(ctx, 3);
                                    lw(v0, v0, 0);
                                    if (v0 != 0) {
                                        // 0x001c92e4
                                        charge(ctx, 39);
                                        v0 = sll(s4, 2);
                                        v0 = addu(s5, v0);
                                        s0 = addiu(v0, 96);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C92F8u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f1, v0, 48);
                                        lw(v0, s0, 0);
                                        lwc1(f0, v0, 268);
                                        sub_s(f0, f0, f1);
                                        swc1(f0, sp, 0x270);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C931Cu, gen::fn_sub_318B60_00318b60);
                                        lwc1(f1, v0, 52);
                                        lw(v0, s0, 0);
                                        lwc1(f0, v0, 272);
                                        sub_s(f0, f0, f1);
                                        swc1(f0, sp, 0x274);
                                        v0 = 0x870000;
                                        lw(a0, v0, 6128);  // 0x8717F0
                                        jal(ctx, 0x1C9340u, gen::fn_sub_318B60_00318b60);
                                        lwc1(f1, v0, 56);
                                        lw(v0, s0, 0);
                                        lwc1(f0, v0, 276);
                                        sub_s(f0, f0, f1);
                                        swc1(f0, sp, 0x278);
                                        a0 = addiu(sp, 0x270);
                                        jal(ctx, 0x1C9360u, gen::fn_sub_4C6AC0_004c6ac0);
                                        v0 = 0x43480000;
                                        mtc1(v0, f1);
                                        c_lt_s(f0, f1);
                                        if (!cond(ctx)) {
                                            goto L_001c93a0;
                                        }
                                        goto L_001c9380_97;
                                    }
                                L_001c93a0:
                                    charge(ctx, 1);
                                    s4 = addiu(s4, 1);
                                }
                                // 0x001c93b8
                                charge(ctx, 1);
                                v1 = 0;
                            L_001c93bc:
                                charge(ctx, 3);
                                sw(v1, gp, -19052);  // 0x7CE284
                                if (v1 == 0) {
                                    // 0x001c9528
                                    charge(ctx, 5);
                                    jal(ctx, 0x1C9528u, gen::fn_sub_1C74C0_001c74c0);
                                    sw(v0, s3, f4::evt::kNpc);
                                    if (v0 != 0) {
                                        // 0x001c953c
                                        charge(ctx, 3);
                                        lw(v0, v0, 500);
                                        if (v0 == 0) {
                                            goto L_001c9cf0;
                                        }
                                        // 0x001c9548
                                        charge(ctx, 7);
                                        a0 = 1;
                                        sw(a0, s3, f4::evt::kPrompt);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, 2382);  // gPadFlags
                                        v0 = v0 & 0x40;
                                        if (v0 == 0) {
                                            goto L_001c9cf0;
                                        }
                                        // 0x001c9564
                                        charge(ctx, 3);
                                        lw(v0, s3, f4::evt::kTalkCooldown);
                                        if (v0 != 0) {
                                            goto L_001c9cf0;
                                        }
                                        // 0x001c9570
                                        charge(ctx, 5);
                                        sw(zero, s3, f4::evt::kPrompt);
                                        lw(a1, s3, f4::evt::kNpc);
                                        lw(v1, a1, 500);
                                        if (v1 != a0) {
                                            // 0x001c99ac
                                            charge(ctx, 3);
                                            v0 = 2;
                                            if (v1 == v0) {
                                                // 0x001c99b8
                                                charge(ctx, 5);
                                                lw(a0, a1, 508);
                                                lw(v1, a0, 108);
                                                v0 = si(-1);
                                                if (v1 == v0) {
                                                    // 0x001c9b64
                                                    charge(ctx, 3);
                                                    lw(a3, a0, 112);
                                                    if (a3 != v0) {
                                                        // 0x001c9b70
                                                        charge(ctx, 31);
                                                        lw(a2, gp, -19128);  // 0x7CE238
                                                        a0 = 10;
                                                        lw(a1, gp, -19124);  // 0x7CE23C
                                                        jal(ctx, 0x1C9B7Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                        sw(v0, s3, f4::evt::kScript);
                                                        jal(ctx, 0x1C9B88u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kVirtualPad);
                                                        a1 = 1;
                                                        jal(ctx, 0x1C9B98u, gen::fn_sub_1E1300_001e1300);
                                                        jal(ctx, 0x1C9BA0u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kFootstep);
                                                        a1 = 1;
                                                        jal(ctx, 0x1C9BB0u, gen::fn_sub_1DA000_001da000);
                                                        lw(v0, s3, f4::evt::kNpc);
                                                        lw(a0, v0, 296);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9BC4u, gen::fn_sub_318540_00318540);
                                                        a0 = dsll32(v0, 16);
                                                        a0 = dsra32(a0, 16);
                                                        sw(a0, s3, f4::evt::kNpcPose);
                                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                        lw(v1, v0, f4::scene::kMajor);
                                                        v0 = 7;
                                                        if (v1 != v0) {
                                                            // 0x001c9bec
                                                            charge(ctx, 3);
                                                            v0 = 4;
                                                            if (v1 == v0) {
                                                                goto L_001c9bf8;
                                                            }
                                                            // 0x001c9c04
                                                            charge(ctx, 2);
                                                            if (a0 != 0) {
                                                                // 0x001c9c18
                                                                charge(ctx, 1);
                                                                v1 = addiu(a0, 1);
                                                            } else {
                                                                // 0x001c9c0c
                                                                charge(ctx, 3);
                                                                v1 = 3;
                                                            }
                                                            goto L_001c9c1c;
                                                        }
                                                    L_001c9bf8:
                                                        charge(ctx, 3);
                                                        v1 = addiu(a0, 1);
                                                    L_001c9c1c:
                                                        charge(ctx, 13);
                                                        lw(v0, s3, f4::evt::kNpc);
                                                        a2 = dsll32(v1, 16);
                                                        a2 = dsra32(a2, 16);
                                                        lw(a0, v0, 296);
                                                        a1 = 0;
                                                        a3 = 7;
                                                        t0 = 0;
                                                        jal(ctx, 0x1C9C38u, gen::fn_sub_3182D0_003182d0);
                                                        lw(v0, s3, f4::evt::kNpc);
                                                        lw(a0, v0, 528);
                                                        if (a0 != 0) {
                                                            // 0x001c9c50
                                                            charge(ctx, 3);
                                                            a1 = 0;
                                                            jal(ctx, 0x1C9C54u, gen::fn_sub_1DD5E0_001dd5e0);
                                                        }
                                                        // 0x001c9c5c
                                                        charge(ctx, 5);
                                                        jal(ctx, 0x1C9C5Cu, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kSmap);
                                                        if (v0 != 0) {
                                                            // 0x001c9c70
                                                            charge(ctx, 6);
                                                            jal(ctx, 0x1C9C70u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, f4::fld::kSmap);
                                                            a1 = 0;
                                                            jal(ctx, 0x1C9C80u, gen::fn_sub_429E80_00429e80);
                                                        }
                                                        // 0x001c9c88
                                                        charge(ctx, 5);
                                                        jal(ctx, 0x1C9C88u, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kPartyPanel);
                                                        if (v0 != 0) {
                                                            // 0x001c9c9c
                                                            charge(ctx, 6);
                                                            jal(ctx, 0x1C9C9Cu, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, f4::fld::kPartyPanel);
                                                            a1 = 0;
                                                            jal(ctx, 0x1C9CACu, gen::fn_sub_18C0C0_0018c0c0);
                                                        }
                                                        // 0x001c9cb4
                                                        charge(ctx, 5);
                                                        jal(ctx, 0x1C9CB4u, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kAreaPanel);
                                                        if (v0 != 0) {
                                                            // 0x001c9cc8
                                                            charge(ctx, 6);
                                                            jal(ctx, 0x1C9CC8u, gen::fn_K_Field_Get_001b9120);
                                                            lw(a0, v0, f4::fld::kAreaPanel);
                                                            a1 = 0;
                                                            jal(ctx, 0x1C9CD8u, gen::fn_sub_18EB30_0018eb30);
                                                        }
                                                        // 0x001c9ce0
                                                        charge(ctx, 4);
                                                        v0 = 22;
                                                        sw(v0, s3, f4::evt::kState);
                                                    }
                                                } else {
                                                    // 0x001c99cc
                                                    charge(ctx, 37);
                                                    lw(a0, a1, 520);
                                                    jal(ctx, 0x1C99D0u, gen::fn_sub_3C72D0_003c72d0);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 508);
                                                    lw(a1, v0, 512);
                                                    lw(a2, v0, 516);
                                                    jal(ctx, 0x1C99E8u, gen::fn_sub_1B8FD0_001b8fd0);
                                                    a0 = v0;
                                                    jal(ctx, 0x1C99F4u, gen::fn_msgWinRequestMessage_003c7430);
                                                    jal(ctx, 0x1C99FCu, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kVirtualPad);
                                                    a1 = 1;
                                                    jal(ctx, 0x1C9A0Cu, gen::fn_sub_1E1300_001e1300);
                                                    jal(ctx, 0x1C9A14u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kFootstep);
                                                    a1 = 1;
                                                    jal(ctx, 0x1C9A24u, gen::fn_sub_1DA000_001da000);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 296);
                                                    a1 = 0;
                                                    jal(ctx, 0x1C9A38u, gen::fn_sub_318540_00318540);
                                                    a0 = dsll32(v0, 16);
                                                    a0 = dsra32(a0, 16);
                                                    sw(a0, s3, f4::evt::kNpcPose);
                                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                    lw(v1, v0, f4::scene::kMajor);
                                                    v0 = 7;
                                                    if (v1 != v0) {
                                                        // 0x001c9a60
                                                        charge(ctx, 3);
                                                        v0 = 4;
                                                        if (v1 == v0) {
                                                            goto L_001c9a6c;
                                                        }
                                                        // 0x001c9a78
                                                        charge(ctx, 2);
                                                        if (a0 != 0) {
                                                            // 0x001c9a8c
                                                            charge(ctx, 1);
                                                            v1 = addiu(a0, 1);
                                                        } else {
                                                            // 0x001c9a80
                                                            charge(ctx, 3);
                                                            v1 = 3;
                                                        }
                                                        goto L_001c9a90;
                                                    }
                                                L_001c9a6c:
                                                    charge(ctx, 3);
                                                    v1 = addiu(a0, 1);
                                                L_001c9a90:
                                                    charge(ctx, 13);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    a2 = dsll32(v1, 16);
                                                    a2 = dsra32(a2, 16);
                                                    lw(a0, v0, 296);
                                                    a1 = 0;
                                                    a3 = 7;
                                                    t0 = 0;
                                                    jal(ctx, 0x1C9AACu, gen::fn_sub_3182D0_003182d0);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 528);
                                                    if (a0 != 0) {
                                                        // 0x001c9ac4
                                                        charge(ctx, 3);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9AC8u, gen::fn_sub_1DD5E0_001dd5e0);
                                                    }
                                                    // 0x001c9ad0
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9AD0u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kSmap);
                                                    if (v0 != 0) {
                                                        // 0x001c9ae4
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C9AE4u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kSmap);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9AF4u, gen::fn_sub_429E80_00429e80);
                                                    }
                                                    // 0x001c9afc
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9AFCu, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kPartyPanel);
                                                    if (v0 != 0) {
                                                        // 0x001c9b10
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C9B10u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kPartyPanel);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9B20u, gen::fn_sub_18C0C0_0018c0c0);
                                                    }
                                                    // 0x001c9b28
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9B28u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kAreaPanel);
                                                    if (v0 != 0) {
                                                        // 0x001c9b3c
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C9B3Cu, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kAreaPanel);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9B4Cu, gen::fn_sub_18EB30_0018eb30);
                                                    }
                                                    // 0x001c9b54
                                                    charge(ctx, 4);
                                                    v0 = 21;
                                                    sw(v0, s3, f4::evt::kState);
                                                }
                                            }
                                        } else {
                                            // 0x001c9584
                                            charge(ctx, 5);
                                            lw(a0, a1, 504);
                                            lw(v1, a0, 8);
                                            v0 = si(-1);
                                            if (v1 == v0) {
                                                // 0x001c9798
                                                charge(ctx, 3);
                                                lw(s1, a0, 12);
                                                if (s1 != v0) {
                                                    // 0x001c97a4
                                                    charge(ctx, 37);
                                                    jal(ctx, 0x1C97A4u, gen::fn_K_Field_Get_001b9120);
                                                    s0 = v0;
                                                    jal(ctx, 0x1C97B0u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a2, v0, f4::fld::kNpcScriptSize);
                                                    a0 = 10;
                                                    lw(a1, s0, f4::fld::kNpcScript);
                                                    a3 = s1;
                                                    jal(ctx, 0x1C97C8u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                    sw(v0, s3, f4::evt::kScript);
                                                    jal(ctx, 0x1C97D4u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kVirtualPad);
                                                    a1 = 1;
                                                    jal(ctx, 0x1C97E4u, gen::fn_sub_1E1300_001e1300);
                                                    jal(ctx, 0x1C97ECu, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kFootstep);
                                                    a1 = 1;
                                                    jal(ctx, 0x1C97FCu, gen::fn_sub_1DA000_001da000);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 296);
                                                    a1 = 0;
                                                    jal(ctx, 0x1C9810u, gen::fn_sub_318540_00318540);
                                                    v0 = dsll32(v0, 16);
                                                    v0 = dsra32(v0, 16);
                                                    sw(v0, s3, f4::evt::kNpcPose);
                                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                    lw(a0, v0, f4::scene::kMajor);
                                                    v0 = 7;
                                                    if (a0 != v0) {
                                                        // 0x001c9838
                                                        charge(ctx, 3);
                                                        v0 = 4;
                                                        if (a0 == v0) {
                                                            goto L_001c9844;
                                                        }
                                                    L_001c987c:
                                                        charge(ctx, 4);
                                                        lw(v1, s3, f4::evt::kNpcPose);
                                                        v0 = 7;
                                                        if (a0 != v0) {
                                                            // 0x001c988c
                                                            charge(ctx, 3);
                                                            v0 = 4;
                                                            if (a0 == v0) {
                                                                goto L_001c9898;
                                                            }
                                                            // 0x001c98a4
                                                            charge(ctx, 2);
                                                            if (v1 != 0) {
                                                                // 0x001c98b8
                                                                charge(ctx, 1);
                                                                v1 = addiu(v1, 1);
                                                            } else {
                                                                // 0x001c98ac
                                                                charge(ctx, 3);
                                                                v1 = 3;
                                                            }
                                                            goto L_001c98bc;
                                                        }
                                                    L_001c9898:
                                                        charge(ctx, 3);
                                                        v1 = addiu(v1, 1);
                                                    L_001c98bc:
                                                        charge(ctx, 11);
                                                        lw(v0, s3, f4::evt::kNpc);
                                                        a2 = dsll32(v1, 16);
                                                        a2 = dsra32(a2, 16);
                                                        lw(a0, v0, 296);
                                                        a1 = 0;
                                                        a3 = 7;
                                                        t0 = 0;
                                                        jal(ctx, 0x1C98D8u, gen::fn_sub_3182D0_003182d0);
                                                        goto L_001c9918;
                                                    }
                                                L_001c9844:
                                                    charge(ctx, 3);
                                                    v0 = 7;
                                                    if (a0 == v0) {
                                                        // 0x001c9850
                                                        charge(ctx, 4);
                                                        lw(v0, s3, f4::evt::kNpcPose);
                                                        v0 = sltiu(v0, 4);
                                                        if (v0 != 0) {
                                                            goto L_001c987c;
                                                        }
                                                        goto L_001c9860;
                                                    }
                                                L_001c9860:
                                                    charge(ctx, 3);
                                                    v0 = 4;
                                                    if (a0 == v0) {
                                                        // 0x001c986c
                                                        charge(ctx, 4);
                                                        lw(v0, s3, f4::evt::kNpcPose);
                                                        at = sltiu(v0, 4);
                                                        if (at == 0) {
                                                            goto L_001c98e8;
                                                        }
                                                        goto L_001c987c;
                                                    }
                                                L_001c98e8:
                                                    charge(ctx, 12);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 296);
                                                    jal(ctx, 0x1C98F0u, gen::fn_sub_319200_00319200);
                                                    v1 = v0 & 0xFFFF;
                                                    v0 = si(-2049);
                                                    v0 = v1 & v0;
                                                    a1 = v0 & 0xFFFF;
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    lw(a0, v0, 296);
                                                    jal(ctx, 0x1C9910u, gen::fn_sub_3191F0_003191f0);
                                                L_001c9918:
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9918u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kSmap);
                                                    if (v0 != 0) {
                                                        // 0x001c992c
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C992Cu, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kSmap);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C993Cu, gen::fn_sub_429E80_00429e80);
                                                    }
                                                    // 0x001c9944
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9944u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kPartyPanel);
                                                    if (v0 != 0) {
                                                        // 0x001c9958
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C9958u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kPartyPanel);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9968u, gen::fn_sub_18C0C0_0018c0c0);
                                                    }
                                                    // 0x001c9970
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x1C9970u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kAreaPanel);
                                                    if (v0 != 0) {
                                                        // 0x001c9984
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1C9984u, gen::fn_K_Field_Get_001b9120);
                                                        lw(a0, v0, f4::fld::kAreaPanel);
                                                        a1 = 0;
                                                        jal(ctx, 0x1C9994u, gen::fn_sub_18EB30_0018eb30);
                                                    }
                                                    // 0x001c999c
                                                    charge(ctx, 4);
                                                    v0 = 22;
                                                    sw(v0, s3, f4::evt::kState);
                                                }
                                            } else {
                                                // 0x001c9598
                                                charge(ctx, 35);
                                                jal(ctx, 0x1C9598u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kNpcMessages);
                                                jal(ctx, 0x1C95A4u, gen::fn_sub_3C72D0_003c72d0);
                                                lw(v0, s3, f4::evt::kNpc);
                                                lw(v0, v0, 504);
                                                lw(a0, v0, 8);
                                                jal(ctx, 0x1C95B8u, gen::fn_msgWinRequestMessage_003c7430);
                                                jal(ctx, 0x1C95C0u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kVirtualPad);
                                                a1 = 1;
                                                jal(ctx, 0x1C95D0u, gen::fn_sub_1E1300_001e1300);
                                                jal(ctx, 0x1C95D8u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kFootstep);
                                                a1 = 1;
                                                jal(ctx, 0x1C95E8u, gen::fn_sub_1DA000_001da000);
                                                lw(v0, s3, f4::evt::kNpc);
                                                lw(a0, v0, 296);
                                                a1 = 0;
                                                jal(ctx, 0x1C95FCu, gen::fn_sub_318540_00318540);
                                                v0 = dsll32(v0, 16);
                                                v0 = dsra32(v0, 16);
                                                sw(v0, s3, f4::evt::kNpcPose);
                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                lw(a0, v0, f4::scene::kMajor);
                                                v0 = 7;
                                                if (a0 != v0) {
                                                    // 0x001c9624
                                                    charge(ctx, 3);
                                                    v0 = 4;
                                                    if (a0 == v0) {
                                                        goto L_001c9630;
                                                    }
                                                L_001c9668:
                                                    charge(ctx, 4);
                                                    lw(v1, s3, f4::evt::kNpcPose);
                                                    v0 = 7;
                                                    if (a0 != v0) {
                                                        // 0x001c9678
                                                        charge(ctx, 3);
                                                        v0 = 4;
                                                        if (a0 == v0) {
                                                            goto L_001c9684;
                                                        }
                                                        // 0x001c9690
                                                        charge(ctx, 2);
                                                        if (v1 != 0) {
                                                            // 0x001c96a4
                                                            charge(ctx, 1);
                                                            v1 = addiu(v1, 1);
                                                        } else {
                                                            // 0x001c9698
                                                            charge(ctx, 3);
                                                            v1 = 3;
                                                        }
                                                        goto L_001c96a8;
                                                    }
                                                L_001c9684:
                                                    charge(ctx, 3);
                                                    v1 = addiu(v1, 1);
                                                L_001c96a8:
                                                    charge(ctx, 11);
                                                    lw(v0, s3, f4::evt::kNpc);
                                                    a2 = dsll32(v1, 16);
                                                    a2 = dsra32(a2, 16);
                                                    lw(a0, v0, 296);
                                                    a1 = 0;
                                                    a3 = 7;
                                                    t0 = 0;
                                                    jal(ctx, 0x1C96C4u, gen::fn_sub_3182D0_003182d0);
                                                    goto L_001c9704;
                                                }
                                            L_001c9630:
                                                charge(ctx, 3);
                                                v0 = 7;
                                                if (a0 == v0) {
                                                    // 0x001c963c
                                                    charge(ctx, 4);
                                                    lw(v0, s3, f4::evt::kNpcPose);
                                                    v0 = sltiu(v0, 4);
                                                    if (v0 != 0) {
                                                        goto L_001c9668;
                                                    }
                                                    goto L_001c964c;
                                                }
                                            L_001c964c:
                                                charge(ctx, 3);
                                                v0 = 4;
                                                if (a0 == v0) {
                                                    // 0x001c9658
                                                    charge(ctx, 4);
                                                    lw(v0, s3, f4::evt::kNpcPose);
                                                    at = sltiu(v0, 4);
                                                    if (at == 0) {
                                                        goto L_001c96d4;
                                                    }
                                                    goto L_001c9668;
                                                }
                                            L_001c96d4:
                                                charge(ctx, 12);
                                                lw(v0, s3, f4::evt::kNpc);
                                                lw(a0, v0, 296);
                                                jal(ctx, 0x1C96DCu, gen::fn_sub_319200_00319200);
                                                v1 = v0 & 0xFFFF;
                                                v0 = si(-2049);
                                                v0 = v1 & v0;
                                                a1 = v0 & 0xFFFF;
                                                lw(v0, s3, f4::evt::kNpc);
                                                lw(a0, v0, 296);
                                                jal(ctx, 0x1C96FCu, gen::fn_sub_3191F0_003191f0);
                                            L_001c9704:
                                                charge(ctx, 5);
                                                jal(ctx, 0x1C9704u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kSmap);
                                                if (v0 != 0) {
                                                    // 0x001c9718
                                                    charge(ctx, 6);
                                                    jal(ctx, 0x1C9718u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kSmap);
                                                    a1 = 0;
                                                    jal(ctx, 0x1C9728u, gen::fn_sub_429E80_00429e80);
                                                }
                                                // 0x001c9730
                                                charge(ctx, 5);
                                                jal(ctx, 0x1C9730u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kPartyPanel);
                                                if (v0 != 0) {
                                                    // 0x001c9744
                                                    charge(ctx, 6);
                                                    jal(ctx, 0x1C9744u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kPartyPanel);
                                                    a1 = 0;
                                                    jal(ctx, 0x1C9754u, gen::fn_sub_18C0C0_0018c0c0);
                                                }
                                                // 0x001c975c
                                                charge(ctx, 5);
                                                jal(ctx, 0x1C975Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kAreaPanel);
                                                if (v0 != 0) {
                                                    // 0x001c9770
                                                    charge(ctx, 6);
                                                    jal(ctx, 0x1C9770u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kAreaPanel);
                                                    a1 = 0;
                                                    jal(ctx, 0x1C9780u, gen::fn_sub_18EB30_0018eb30);
                                                }
                                                // 0x001c9788
                                                charge(ctx, 4);
                                                v0 = 21;
                                                sw(v0, s3, f4::evt::kState);
                                            }
                                        }
                                        goto L_001cd48c;
                                    }
                                L_001c9cf0:
                                    charge(ctx, 12);
                                    lw(v0, s3, f4::evt::kHero);
                                    lw(a0, v0, 296);
                                    jal(ctx, 0x1C9CF8u, gen::fn_sub_318B60_00318b60);
                                    a0 = addiu(v0, 48);
                                    a1 = addiu(sp, 0x35C);
                                    jal(ctx, 0x1C9D08u, gen::fn_K_FldEvent_FindFldHitAt_001c5ee0);
                                    s0 = v0 & 0xFFFF;
                                    v0 = 0xFFFF;
                                    if (s0 == v0) {
                                        // 0x001ca3e8
                                        charge(ctx, 3);
                                        lw(v0, s3, f4::evt::kAreaName);
                                        if (v0 != 0) {
                                            // 0x001ca3f4
                                            charge(ctx, 4);
                                            sw(zero, s3, f4::evt::kAreaName);
                                            a0 = si(-1);
                                            jal(ctx, 0x1CA3FCu, gen::fn_sub_1DDCA0_001ddca0);
                                        }
                                    L_001ca404:
                                        charge(ctx, 11);
                                        v0 = 0x42B40000;
                                        mtc1(v0, f12);
                                        v0 = 0x43480000;
                                        mtc1(v0, f13);
                                        a0 = 0x870000;
                                        a0 = addiu(a0, 6048);  // &gFldUnitsPc
                                        jal(ctx, 0x1CA41Cu, gen::fn_sub_1C6F50_001c6f50);
                                        s0 = v0;
                                        if (s0 != 0) {
                                            // 0x001ca430
                                            charge(ctx, 8);
                                            a0 = s0;
                                            jal(ctx, 0x1CA434u, gen::fn_sub_4353F0_004353f0);
                                            v0 = dsll32(v0, 24);
                                            v0 = dsra32(v0, 24);
                                            v1 = 1;
                                            if (v0 != v1) {
                                                goto L_001ca59c;
                                            }
                                            // 0x001ca450
                                            charge(ctx, 3);
                                            lw(v0, s3, f4::evt::kTarget);
                                            if (v0 == 0) {
                                                // 0x001ca45c
                                                charge(ctx, 1);
                                                sw(v1, s3, f4::evt::kPrompt);
                                            }
                                            // 0x001ca460
                                            charge(ctx, 5);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, 2382);  // gPadFlags
                                            v0 = v0 & 0x40;
                                            if (v0 == 0) {
                                                goto L_001ca59c;
                                            }
                                            // 0x001ca474
                                            charge(ctx, 39);
                                            a0 = 10;
                                            lw(a1, s0, 436);
                                            a2 = 9;
                                            jal(ctx, 0x1CA480u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                                            sw(v0, s3, f4::evt::kScript);
                                            jal(ctx, 0x1CA48Cu, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kVirtualPad);
                                            a1 = 1;
                                            jal(ctx, 0x1CA49Cu, gen::fn_sub_1E1300_001e1300);
                                            a0 = 1;
                                            jal(ctx, 0x1CA4A8u, gen::fn_sub_1D8C60_001d8c60);
                                            jal(ctx, 0x1CA4B0u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kFootstep);
                                            a1 = 1;
                                            jal(ctx, 0x1CA4C0u, gen::fn_sub_1DA000_001da000);
                                            jal(ctx, 0x1CA4C8u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kEnemySched);
                                            a1 = 1;
                                            jal(ctx, 0x1CA4D8u, gen::fn_sub_1D37F0_001d37f0);
                                            a0 = 1;
                                            jal(ctx, 0x1CA4E4u, gen::fn_sub_4532D0_004532d0);
                                            a0 = 0;
                                            a1 = 1;
                                            jal(ctx, 0x1CA4F4u, gen::fn_sub_4350E0_004350e0);
                                            jal(ctx, 0x1CA4FCu, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kSmap);
                                            if (v0 != 0) {
                                                // 0x001ca510
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA510u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kSmap);
                                                a1 = 0;
                                                jal(ctx, 0x1CA520u, gen::fn_sub_429E80_00429e80);
                                            }
                                            // 0x001ca528
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CA528u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kPartyPanel);
                                            if (v0 != 0) {
                                                // 0x001ca53c
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA53Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kPartyPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1CA54Cu, gen::fn_sub_18C0C0_0018c0c0);
                                            }
                                            // 0x001ca554
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CA554u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kAreaPanel);
                                            if (v0 != 0) {
                                                // 0x001ca568
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA568u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kAreaPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1CA578u, gen::fn_sub_18EB30_0018eb30);
                                            }
                                            // 0x001ca580
                                            charge(ctx, 7);
                                            jal(ctx, 0x1CA580u, gen::fn_sub_458890_00458890);
                                            sw(zero, s3, f4::evt::kPrompt);
                                            v0 = 2;
                                            sw(v0, s3, f4::evt::kState);
                                            goto L_001cd48c;
                                        }
                                    L_001ca59c:
                                        charge(ctx, 3);
                                        v0 = 1;
                                        if (s7 == v0) {
                                            goto L_001ca5a8;
                                        }
                                    } else {
                                        // 0x001c9d20
                                        charge(ctx, 7);
                                        s1 = s0 & 0x3FF;
                                        jal(ctx, 0x1C9D24u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExitCount);
                                        v0 = sltu(s1, v0);
                                        if (v0 == 0) {
                                            // 0x001c9d3c
                                            charge(ctx, 5);
                                            a0 = 0x680000;
                                            a0 = addiu(a0, 14128);  // "k_event.c"
                                            a1 = 1878;
                                            jal(ctx, 0x1C9D48u, gen::fn_sub_19D3F0_0019d3f0);
                                        }
                                        // 0x001c9d50
                                        charge(ctx, 14);
                                        v0 = sll(s1, 2);
                                        v0 = addu(v0, s1);
                                        v0 = sll(v0, 1);
                                        v0 = addu(v0, s1);
                                        s2 = sll(v0, 2);
                                        jal(ctx, 0x1C9D64u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExits);
                                        a1 = addu(v0, s2);
                                        a2 = 0;
                                        s4 = 0;
                                        v1 = si(-1);
                                        for (;;) {
                                            // 0x001c9dac
                                            charge(ctx, 3);
                                            v0 = sltiu(a2, 3);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                            // 0x001c9d88
                                            charge(ctx, 3);
                                            lw(a0, a1, 0);
                                            if (a0 != v1) {
                                                // 0x001c9d94
                                                charge(ctx, 4);
                                                v0 = sll(s4, 2);
                                                v0 = addu(v0, sp);
                                                sw(a0, v0, 848);
                                                s4 = addiu(s4, 1);
                                            }
                                            // 0x001c9da4
                                            charge(ctx, 2);
                                            a2 = addiu(a2, 1);
                                            a1 = addiu(a1, 4);
                                        }
                                        // 0x001c9db8
                                        charge(ctx, 3);
                                        s1 = 0;
                                        for (;;) {
                                            // 0x001c9de4
                                            charge(ctx, 3);
                                            v0 = sltu(s1, s4);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                            // 0x001c9dc4
                                            charge(ctx, 7);
                                            v0 = sll(s1, 2);
                                            v0 = addu(v0, sp);
                                            lw(a0, v0, 848);
                                            jal(ctx, 0x1C9DD0u, gen::fn_datGetFlag_0016f190);
                                            if (v0 == 0) {
                                                goto L_001ca404;
                                            }
                                            // 0x001c9de0
                                            charge(ctx, 1);
                                            s1 = addiu(s1, 1);
                                        }
                                        // 0x001c9df0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            goto L_001ca404;
                                        }
                                        // 0x001c9df8
                                        charge(ctx, 7);
                                        jal(ctx, 0x1C9DF8u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExits);
                                        v0 = addu(s2, v0);
                                        lhu(v0, v0, f4::exitrec::kAreaName);
                                        if (v0 != 0) {
                                            // 0x001c9e14
                                            charge(ctx, 8);
                                            lw(s1, s3, f4::evt::kAreaName);
                                            jal(ctx, 0x1C9E18u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lhu(v0, v0, f4::exitrec::kAreaName);
                                            if (s1 != v0) {
                                                // 0x001c9e34
                                                charge(ctx, 8);
                                                jal(ctx, 0x1C9E34u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kExits);
                                                v0 = addu(s2, v0);
                                                lhu(a0, v0, f4::exitrec::kAreaName);
                                                sw(a0, s3, f4::evt::kAreaName);
                                                jal(ctx, 0x1C9E4Cu, gen::fn_sub_1DDCA0_001ddca0);
                                            }
                                        }
                                        // 0x001c9e54
                                        charge(ctx, 8);
                                        jal(ctx, 0x1C9E54u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExits);
                                        v0 = addu(s2, v0);
                                        lbu(v1, v0, f4::exitrec::kKind);
                                        v0 = 1;
                                        if (v1 == v0) {
                                            // 0x001c9e74
                                            charge(ctx, 8);
                                            jal(ctx, 0x1C9E74u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lw(v1, v0, f4::exitrec::kSide);
                                            v0 = 4;
                                            if (v1 == v0) {
                                                // 0x001ca024
                                                charge(ctx, 22);
                                                lw(v0, sp, 0x35C);
                                                lwc1(f1, v0, 296);
                                                lwc1(f0, v0, 320);
                                                add_s(f4, f1, f0);
                                                swc1(f4, sp, 0x340);
                                                lwc1(f1, v0, 300);
                                                lwc1(f0, v0, 324);
                                                add_s(f3, f1, f0);
                                                swc1(f3, sp, 0x344);
                                                lwc1(f1, v0, 304);
                                                lwc1(f0, v0, 328);
                                                add_s(f2, f1, f0);
                                                swc1(f2, sp, 0x348);
                                                v0 = 0x40000000;
                                                mtc1(v0, f1);
                                                div_s(f0, f4, f1);
                                                swc1(f0, sp, 0x340);
                                                div_s(f0, f3, f1);
                                                swc1(f0, sp, 0x344);
                                                div_s(f0, f2, f1);
                                                swc1(f0, sp, 0x348);
                                            } else {
                                                // 0x001c9e94
                                                charge(ctx, 3);
                                                v0 = 3;
                                                if (v1 == v0) {
                                                    // 0x001c9fbc
                                                    charge(ctx, 26);
                                                    lw(v0, sp, 0x35C);
                                                    lwc1(f1, v0, 308);
                                                    lwc1(f0, v0, 320);
                                                    add_s(f4, f1, f0);
                                                    swc1(f4, sp, 0x340);
                                                    lwc1(f1, v0, 312);
                                                    lwc1(f0, v0, 324);
                                                    add_s(f3, f1, f0);
                                                    swc1(f3, sp, 0x344);
                                                    lwc1(f1, v0, 316);
                                                    lwc1(f0, v0, 328);
                                                    add_s(f2, f1, f0);
                                                    swc1(f2, sp, 0x348);
                                                    v0 = 0x40000000;
                                                    mtc1(v0, f1);
                                                    div_s(f0, f4, f1);
                                                    swc1(f0, sp, 0x340);
                                                    div_s(f0, f3, f1);
                                                    swc1(f0, sp, 0x344);
                                                    div_s(f0, f2, f1);
                                                    swc1(f0, sp, 0x348);
                                                } else {
                                                    // 0x001c9ea0
                                                    charge(ctx, 3);
                                                    v0 = 2;
                                                    if (v1 == v0) {
                                                        // 0x001c9f54
                                                        charge(ctx, 26);
                                                        lw(v0, sp, 0x35C);
                                                        lwc1(f1, v0, 284);
                                                        lwc1(f0, v0, 308);
                                                        add_s(f4, f1, f0);
                                                        swc1(f4, sp, 0x340);
                                                        lwc1(f1, v0, 288);
                                                        lwc1(f0, v0, 312);
                                                        add_s(f3, f1, f0);
                                                        swc1(f3, sp, 0x344);
                                                        lwc1(f1, v0, 292);
                                                        lwc1(f0, v0, 316);
                                                        add_s(f2, f1, f0);
                                                        swc1(f2, sp, 0x348);
                                                        v0 = 0x40000000;
                                                        mtc1(v0, f1);
                                                        div_s(f0, f4, f1);
                                                        swc1(f0, sp, 0x340);
                                                        div_s(f0, f3, f1);
                                                        swc1(f0, sp, 0x344);
                                                        div_s(f0, f2, f1);
                                                        swc1(f0, sp, 0x348);
                                                    } else {
                                                        // 0x001c9eac
                                                        charge(ctx, 3);
                                                        v0 = 1;
                                                        if (v1 == v0) {
                                                            // 0x001c9eec
                                                            charge(ctx, 26);
                                                            lw(v0, sp, 0x35C);
                                                            lwc1(f1, v0, 284);
                                                            lwc1(f0, v0, 296);
                                                            add_s(f4, f1, f0);
                                                            swc1(f4, sp, 0x340);
                                                            lwc1(f1, v0, 288);
                                                            lwc1(f0, v0, 300);
                                                            add_s(f3, f1, f0);
                                                            swc1(f3, sp, 0x344);
                                                            lwc1(f1, v0, 292);
                                                            lwc1(f0, v0, 304);
                                                            add_s(f2, f1, f0);
                                                            swc1(f2, sp, 0x348);
                                                            v0 = 0x40000000;
                                                            mtc1(v0, f1);
                                                            div_s(f0, f4, f1);
                                                            swc1(f0, sp, 0x340);
                                                            div_s(f0, f3, f1);
                                                            swc1(f0, sp, 0x344);
                                                            div_s(f0, f2, f1);
                                                            swc1(f0, sp, 0x348);
                                                        } else {
                                                            // 0x001c9eb8
                                                            charge(ctx, 2);
                                                            if (v1 == 0) {
                                                                // 0x001c9ec8
                                                                charge(ctx, 9);
                                                                lw(v0, sp, 0x35C);
                                                                lwc1(f2, v0, 260);
                                                                lwc1(f1, v0, 264);
                                                                lwc1(f0, v0, 268);
                                                                swc1(f2, sp, 0x340);
                                                                swc1(f1, sp, 0x344);
                                                                swc1(f0, sp, 0x348);
                                                            } else {
                                                                // 0x001c9ec0
                                                                charge(ctx, 2);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            // 0x001ca07c
                                            charge(ctx, 12);
                                            v0 = 0x870000;
                                            lw(a0, v0, 6128);  // 0x8717F0
                                            jal(ctx, 0x1CA084u, gen::fn_sub_318B60_00318b60);
                                            v1 = 0x42F00000;
                                            mtc1(v1, f12);
                                            a0 = v0;
                                            a1 = addiu(sp, 0x340);
                                            jal(ctx, 0x1CA09Cu, gen::fn_sub_1C6200_001c6200);
                                            if (v0 == 0) {
                                                goto L_001ca404;
                                            }
                                            goto L_001ca0ac;
                                        }
                                    L_001ca0ac:
                                        charge(ctx, 7);
                                        jal(ctx, 0x1CA0ACu, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExits);
                                        v0 = addu(s2, v0);
                                        lbu(v0, v0, f4::exitrec::kConfirm);
                                        if (v0 != 0) {
                                            // 0x001ca0c8
                                            charge(ctx, 2);
                                            v0 = 1;
                                            sw(v0, s3, f4::evt::kPrompt);
                                        }
                                        // 0x001ca0d0
                                        charge(ctx, 8);
                                        jal(ctx, 0x1CA0D0u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kExits);
                                        v0 = addu(s2, v0);
                                        lhu(v1, v0, f4::exitrec::kProcedure);
                                        v0 = 0xFFFF;
                                        if (v1 != v0) {
                                            // 0x001ca264
                                            charge(ctx, 7);
                                            jal(ctx, 0x1CA264u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lbu(v0, v0, f4::exitrec::kConfirm);
                                            if (v0 != 0) {
                                                // 0x001ca280
                                                charge(ctx, 5);
                                                v0 = 0x7E0000;
                                                lhu(v0, v0, 2382);  // gPadFlags
                                                v0 = v0 & 0x40;
                                                if (v0 != 0) {
                                                    goto L_001ca294;
                                                }
                                                goto L_001cd48c;
                                            }
                                        L_001ca294:
                                            charge(ctx, 50);
                                            jal(ctx, 0x1CA294u, gen::fn_K_Field_Get_001b9120);
                                            s1 = v0;
                                            jal(ctx, 0x1CA2A0u, gen::fn_K_Field_Get_001b9120);
                                            lw(s0, v0, f4::fld::kFieldScriptSize);
                                            jal(ctx, 0x1CA2ACu, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lhu(a3, v0, f4::exitrec::kProcedure);
                                            a0 = 10;
                                            lw(a1, s1, f4::fld::kFieldScript);
                                            a2 = s0;
                                            jal(ctx, 0x1CA2CCu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                            sw(v0, s3, f4::evt::kScript);
                                            a0 = 1;
                                            jal(ctx, 0x1CA2DCu, gen::fn_sub_1D8C60_001d8c60);
                                            jal(ctx, 0x1CA2E4u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kFootstep);
                                            a1 = 1;
                                            jal(ctx, 0x1CA2F4u, gen::fn_sub_1DA000_001da000);
                                            jal(ctx, 0x1CA2FCu, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kVirtualPad);
                                            a1 = 1;
                                            jal(ctx, 0x1CA30Cu, gen::fn_sub_1E1300_001e1300);
                                            jal(ctx, 0x1CA314u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kEnemySched);
                                            a1 = 1;
                                            jal(ctx, 0x1CA324u, gen::fn_sub_1D37F0_001d37f0);
                                            a0 = 1;
                                            jal(ctx, 0x1CA330u, gen::fn_sub_4532D0_004532d0);
                                            a0 = 0;
                                            a1 = 1;
                                            jal(ctx, 0x1CA340u, gen::fn_sub_4350E0_004350e0);
                                            jal(ctx, 0x1CA348u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kSmap);
                                            if (v0 != 0) {
                                                // 0x001ca35c
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA35Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kSmap);
                                                a1 = 0;
                                                jal(ctx, 0x1CA36Cu, gen::fn_sub_429E80_00429e80);
                                            }
                                            // 0x001ca374
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CA374u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kPartyPanel);
                                            if (v0 != 0) {
                                                // 0x001ca388
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA388u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kPartyPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1CA398u, gen::fn_sub_18C0C0_0018c0c0);
                                            }
                                            // 0x001ca3a0
                                            charge(ctx, 5);
                                            jal(ctx, 0x1CA3A0u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kAreaPanel);
                                            if (v0 != 0) {
                                                // 0x001ca3b4
                                                charge(ctx, 6);
                                                jal(ctx, 0x1CA3B4u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kAreaPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1CA3C4u, gen::fn_sub_18EB30_0018eb30);
                                            }
                                            // 0x001ca3cc
                                            charge(ctx, 7);
                                            jal(ctx, 0x1CA3CCu, gen::fn_sub_458890_00458890);
                                            sw(zero, s3, f4::evt::kPrompt);
                                            v0 = 2;
                                            sw(v0, s3, f4::evt::kState);
                                        } else {
                                            // 0x001ca0f0
                                            charge(ctx, 7);
                                            jal(ctx, 0x1CA0F0u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lbu(v0, v0, f4::exitrec::kConfirm);
                                            if (v0 != 0) {
                                                // 0x001ca10c
                                                charge(ctx, 5);
                                                v0 = 0x7E0000;
                                                lhu(v0, v0, 2382);  // gPadFlags
                                                v0 = v0 & 0x40;
                                                if (v0 != 0) {
                                                    goto L_001ca120;
                                                }
                                                goto L_001cd48c;
                                            }
                                        L_001ca120:
                                            charge(ctx, 8);
                                            sw(zero, s3, f4::evt::kDoorObj);
                                            jal(ctx, 0x1CA124u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lhu(v0, v0, f4::exitrec::kDoorObj);
                                            if (v0 == 0) {
                                                // 0x001ca1e8
                                                charge(ctx, 1);
                                                sw(zero, s3, f4::evt::kDoorObj);
                                            } else {
                                                // 0x001ca140
                                                charge(ctx, 6);
                                                a0 = 10;
                                                jal(ctx, 0x1CA144u, gen::fn_sub_3B5D50_003b5d50);
                                                sw(v0, s3, f4::evt::kDoorObj);
                                                for (;;) {
                                                    // 0x001ca184
                                                    charge(ctx, 3);
                                                    lw(s4, s3, f4::evt::kDoorObj);
                                                    if (s4 != 0) {
                                                        backedge(ctx);
                                                        // 0x001ca158
                                                        charge(ctx, 9);
                                                        lw(s4, s3, f4::evt::kDoorObj);
                                                        lhu(s1, s4, 0);
                                                        jal(ctx, 0x1CA160u, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kExits);
                                                        v0 = addu(s2, v0);
                                                        lhu(v0, v0, f4::exitrec::kDoorObj);
                                                        if (s1 != v0) {
                                                            // 0x001ca17c
                                                            charge(ctx, 2);
                                                            lw(v0, s4, 248);
                                                            sw(v0, s3, f4::evt::kDoorObj);
                                                            continue;
                                                        }
                                                    }
                                                    break;
                                                }
                                                // 0x001ca190
                                                charge(ctx, 2);
                                                if (s4 != 0) {
                                                    // 0x001ca198
                                                    charge(ctx, 20);
                                                    v0 = 0x3F800000;
                                                    mtc1(v0, f12);
                                                    lw(a0, s4, 260);
                                                    a1 = 0;
                                                    jal(ctx, 0x1CA1A8u, gen::fn_sub_3189F0_003189f0);
                                                    jal(ctx, 0x1CA1B0u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kExits);
                                                    v0 = addu(s2, v0);
                                                    lh(a2, v0, f4::exitrec::kDoorAnim);
                                                    lw(v0, s3, f4::evt::kDoorObj);
                                                    lw(a0, v0, 260);
                                                    a1 = 0;
                                                    a3 = 0;
                                                    t0 = 0;
                                                    jal(ctx, 0x1CA1D8u, gen::fn_sub_3182D0_003182d0);
                                                }
                                            }
                                            // 0x001ca1ec
                                            charge(ctx, 8);
                                            jal(ctx, 0x1CA1ECu, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kExits);
                                            v0 = addu(s2, v0);
                                            lw(v1, v0, f4::exitrec::kSound);
                                            v0 = si(-1);
                                            if (v1 != v0) {
                                                // 0x001ca20c
                                                charge(ctx, 10);
                                                jal(ctx, 0x1CA20Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kExits);
                                                v0 = addu(s2, v0);
                                                lh(a3, v0, f4::exitrec::kSound);
                                                a0 = 0;
                                                a1 = 6;
                                                a2 = 2;
                                                jal(ctx, 0x1CA22Cu, gen::fn_sub_10A4E0_0010a4e0);
                                            }
                                            // 0x001ca234
                                            charge(ctx, 12);
                                            sw(zero, s3, f4::evt::kPrompt);
                                            sh(s0, s3, f4::evt::kMode);
                                            v0 = 3;
                                            sw(v0, s3, f4::evt::kState);
                                            jal(ctx, 0x1CA244u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kVirtualPad);
                                            a1 = 1;
                                            jal(ctx, 0x1CA254u, gen::fn_sub_1E1300_001e1300);
                                        }
                                    }
                                } else {
                                    // 0x001c93c8
                                    charge(ctx, 3);
                                    lw(v0, v1, 4);
                                    if (v0 == 0) {
                                        // 0x001c93d4
                                        charge(ctx, 3);
                                        lw(v0, s3, f4::evt::kTarget);
                                        if (v0 == 0) {
                                            // 0x001c93e0
                                            charge(ctx, 2);
                                            v0 = 1;
                                            sw(v0, s3, f4::evt::kPrompt);
                                        }
                                        // 0x001c93e8
                                        charge(ctx, 5);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, 2382);  // gPadFlags
                                        v0 = v0 & 0x40;
                                        if (v0 != 0) {
                                            // 0x001c93fc
                                            charge(ctx, 42);
                                            v0 = 1;
                                            sw(v0, v1, 4);
                                            lw(a2, gp, -19148);  // g_fldMainScriptSize
                                            a0 = 10;
                                            lw(a1, gp, -19144);  // g_fldMainScriptPtr
                                            a3 = 0;
                                            jal(ctx, 0x1C9414u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                            sw(v0, s3, f4::evt::kScript);
                                            jal(ctx, 0x1C9420u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kVirtualPad);
                                            a1 = 1;
                                            jal(ctx, 0x1C9430u, gen::fn_sub_1E1300_001e1300);
                                            a0 = 1;
                                            jal(ctx, 0x1C943Cu, gen::fn_sub_1D8C60_001d8c60);
                                            jal(ctx, 0x1C9444u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kFootstep);
                                            a1 = 1;
                                            jal(ctx, 0x1C9454u, gen::fn_sub_1DA000_001da000);
                                            jal(ctx, 0x1C945Cu, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kEnemySched);
                                            a1 = 1;
                                            jal(ctx, 0x1C946Cu, gen::fn_sub_1D37F0_001d37f0);
                                            a0 = 1;
                                            jal(ctx, 0x1C9478u, gen::fn_sub_4532D0_004532d0);
                                            a0 = 0;
                                            a1 = 1;
                                            jal(ctx, 0x1C9488u, gen::fn_sub_4350E0_004350e0);
                                            jal(ctx, 0x1C9490u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kSmap);
                                            if (v0 != 0) {
                                                // 0x001c94a4
                                                charge(ctx, 6);
                                                jal(ctx, 0x1C94A4u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kSmap);
                                                a1 = 0;
                                                jal(ctx, 0x1C94B4u, gen::fn_sub_429E80_00429e80);
                                            }
                                            // 0x001c94bc
                                            charge(ctx, 5);
                                            jal(ctx, 0x1C94BCu, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kPartyPanel);
                                            if (v0 != 0) {
                                                // 0x001c94d0
                                                charge(ctx, 6);
                                                jal(ctx, 0x1C94D0u, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kPartyPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1C94E0u, gen::fn_sub_18C0C0_0018c0c0);
                                            }
                                            // 0x001c94e8
                                            charge(ctx, 5);
                                            jal(ctx, 0x1C94E8u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kAreaPanel);
                                            if (v0 != 0) {
                                                // 0x001c94fc
                                                charge(ctx, 6);
                                                jal(ctx, 0x1C94FCu, gen::fn_K_Field_Get_001b9120);
                                                lw(a0, v0, f4::fld::kAreaPanel);
                                                a1 = 0;
                                                jal(ctx, 0x1C950Cu, gen::fn_sub_18EB30_0018eb30);
                                            }
                                            // 0x001c9514
                                            charge(ctx, 5);
                                            sw(zero, s3, f4::evt::kPrompt);
                                            v0 = 2;
                                            sw(v0, s3, f4::evt::kState);
                                        }
                                    }
                                }
                            } else {
                                // 0x001c9054
                                charge(ctx, 3);
                                lw(v0, s3, f4::evt::kTarget);
                                if (v0 == 0) {
                                    // 0x001c9060
                                    charge(ctx, 1);
                                    sw(v1, s3, f4::evt::kPrompt);
                                }
                                // 0x001c9064
                                charge(ctx, 5);
                                v0 = 0x7E0000;
                                lhu(v0, v0, 2382);  // gPadFlags
                                v0 = v0 & 0x40;
                                if (v0 != 0) {
                                    // 0x001c9078
                                    charge(ctx, 45);
                                    jal(ctx, 0x1C9078u, gen::fn_K_FldDungeon_GetScrMemory_001bffe0);
                                    s0 = v0;
                                    jal(ctx, 0x1C9084u, gen::fn_K_FldDungeon_GetScrSize_001c0010);
                                    a0 = 10;
                                    a1 = s0;
                                    a2 = v0;
                                    a3 = 1;
                                    jal(ctx, 0x1C909Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                    sw(v0, s3, f4::evt::kScript);
                                    jal(ctx, 0x1C90A8u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kVirtualPad);
                                    a1 = 1;
                                    jal(ctx, 0x1C90B8u, gen::fn_sub_1E1300_001e1300);
                                    a0 = 1;
                                    jal(ctx, 0x1C90C4u, gen::fn_sub_1D8C60_001d8c60);
                                    jal(ctx, 0x1C90CCu, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kFootstep);
                                    a1 = 1;
                                    jal(ctx, 0x1C90DCu, gen::fn_sub_1DA000_001da000);
                                    jal(ctx, 0x1C90E4u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kEnemySched);
                                    a1 = 1;
                                    jal(ctx, 0x1C90F4u, gen::fn_sub_1D37F0_001d37f0);
                                    a0 = 1;
                                    jal(ctx, 0x1C9100u, gen::fn_sub_4532D0_004532d0);
                                    a0 = 0;
                                    a1 = 1;
                                    jal(ctx, 0x1C9110u, gen::fn_sub_4350E0_004350e0);
                                    jal(ctx, 0x1C9118u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kSmap);
                                    if (v0 != 0) {
                                        // 0x001c912c
                                        charge(ctx, 6);
                                        jal(ctx, 0x1C912Cu, gen::fn_K_Field_Get_001b9120);
                                        lw(a0, v0, f4::fld::kSmap);
                                        a1 = 0;
                                        jal(ctx, 0x1C913Cu, gen::fn_sub_429E80_00429e80);
                                    }
                                    // 0x001c9144
                                    charge(ctx, 5);
                                    jal(ctx, 0x1C9144u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kPartyPanel);
                                    if (v0 != 0) {
                                        // 0x001c9158
                                        charge(ctx, 6);
                                        jal(ctx, 0x1C9158u, gen::fn_K_Field_Get_001b9120);
                                        lw(a0, v0, f4::fld::kPartyPanel);
                                        a1 = 0;
                                        jal(ctx, 0x1C9168u, gen::fn_sub_18C0C0_0018c0c0);
                                    }
                                    // 0x001c9170
                                    charge(ctx, 5);
                                    jal(ctx, 0x1C9170u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kAreaPanel);
                                    if (v0 != 0) {
                                        // 0x001c9184
                                        charge(ctx, 6);
                                        jal(ctx, 0x1C9184u, gen::fn_K_Field_Get_001b9120);
                                        lw(a0, v0, f4::fld::kAreaPanel);
                                        a1 = 0;
                                        jal(ctx, 0x1C9194u, gen::fn_sub_18EB30_0018eb30);
                                    }
                                    // 0x001c919c
                                    charge(ctx, 5);
                                    sw(zero, s3, f4::evt::kPrompt);
                                    v0 = 2;
                                    sw(v0, s3, f4::evt::kState);
                                }
                            }
                        } else {
                            // 0x001c8df4
                            charge(ctx, 3);
                            lw(v0, s3, f4::evt::kTarget);
                            if (v0 == 0) {
                                // 0x001c8e00
                                charge(ctx, 1);
                                sw(v1, s3, f4::evt::kPrompt);
                            }
                            // 0x001c8e04
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, 2382);  // gPadFlags
                            v0 = v0 & 0x40;
                            if (v0 != 0) {
                                // 0x001c8e18
                                charge(ctx, 45);
                                jal(ctx, 0x1C8E18u, gen::fn_K_FldDungeon_GetScrMemory_001bffe0);
                                s0 = v0;
                                jal(ctx, 0x1C8E24u, gen::fn_K_FldDungeon_GetScrSize_001c0010);
                                a0 = 10;
                                a1 = s0;
                                a2 = v0;
                                a3 = 0;
                                jal(ctx, 0x1C8E3Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                sw(v0, s3, f4::evt::kScript);
                                jal(ctx, 0x1C8E48u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kVirtualPad);
                                a1 = 1;
                                jal(ctx, 0x1C8E58u, gen::fn_sub_1E1300_001e1300);
                                a0 = 1;
                                jal(ctx, 0x1C8E64u, gen::fn_sub_1D8C60_001d8c60);
                                jal(ctx, 0x1C8E6Cu, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kFootstep);
                                a1 = 1;
                                jal(ctx, 0x1C8E7Cu, gen::fn_sub_1DA000_001da000);
                                jal(ctx, 0x1C8E84u, gen::fn_K_Field_Get_001b9120);
                                lw(a0, v0, f4::fld::kEnemySched);
                                a1 = 1;
                                jal(ctx, 0x1C8E94u, gen::fn_sub_1D37F0_001d37f0);
                                a0 = 1;
                                jal(ctx, 0x1C8EA0u, gen::fn_sub_4532D0_004532d0);
                                a0 = 0;
                                a1 = 1;
                                jal(ctx, 0x1C8EB0u, gen::fn_sub_4350E0_004350e0);
                                jal(ctx, 0x1C8EB8u, gen::fn_K_Field_Get_001b9120);
                                lw(v0, v0, f4::fld::kSmap);
                                if (v0 != 0) {
                                    // 0x001c8ecc
                                    charge(ctx, 6);
                                    jal(ctx, 0x1C8ECCu, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kSmap);
                                    a1 = 0;
                                    jal(ctx, 0x1C8EDCu, gen::fn_sub_429E80_00429e80);
                                }
                                // 0x001c8ee4
                                charge(ctx, 5);
                                jal(ctx, 0x1C8EE4u, gen::fn_K_Field_Get_001b9120);
                                lw(v0, v0, f4::fld::kPartyPanel);
                                if (v0 != 0) {
                                    // 0x001c8ef8
                                    charge(ctx, 6);
                                    jal(ctx, 0x1C8EF8u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kPartyPanel);
                                    a1 = 0;
                                    jal(ctx, 0x1C8F08u, gen::fn_sub_18C0C0_0018c0c0);
                                }
                                // 0x001c8f10
                                charge(ctx, 5);
                                jal(ctx, 0x1C8F10u, gen::fn_K_Field_Get_001b9120);
                                lw(v0, v0, f4::fld::kAreaPanel);
                                if (v0 != 0) {
                                    // 0x001c8f24
                                    charge(ctx, 6);
                                    jal(ctx, 0x1C8F24u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kAreaPanel);
                                    a1 = 0;
                                    jal(ctx, 0x1C8F34u, gen::fn_sub_18EB30_0018eb30);
                                }
                                // 0x001c8f3c
                                charge(ctx, 5);
                                sw(zero, s3, f4::evt::kPrompt);
                                v0 = 2;
                                sw(v0, s3, f4::evt::kState);
                            }
                        }
                    } else {
                        // 0x001c882c
                        charge(ctx, 17);
                        jal(ctx, 0x1C882Cu, gen::fn_sub_453460_00453460);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sll(v1, 3);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 6);
                        v0 = 0x870000;
                        v0 = addiu(v0, -4704);  // &gFldUnitsEc
                        v0 = addu(v0, v1);
                        sw(v0, s3, f4::evt::kTarget);
                        lw(a0, v0, 72);
                        jal(ctx, 0x1C885Cu, gen::fn_datUnitIsGenusDead_002ff790);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x001c8870
                            charge(ctx, 15);
                            a0 = addiu(s3, 40);
                            lw(a1, s3, f4::evt::kTarget);
                            jal(ctx, 0x1C8878u, gen::fn_sub_1C7830_001c7830);
                            lhu(v0, s3, f4::evt::kPacket);
                            v0 = v0 | 0x1;
                            sh(v0, s3, f4::evt::kPacket);
                            lhu(v0, s3, f4::evt::kPacket);
                            v0 = v0 | 0x2;
                            sh(v0, s3, f4::evt::kPacket);
                            lw(v0, s3, f4::evt::kTarget);
                            lw(a0, v0, 76);
                            lhu(v1, a0, 18);
                            if (v1 == 0) {
                                // 0x001c88ac
                                charge(ctx, 3);
                                lhu(v0, a0, 20);
                                if (v0 != 0) {
                                    goto L_001c88b8;
                                }
                                // 0x001c88cc
                                charge(ctx, 6);
                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v0, v0, f4::scene::kMajor);
                                v0 = addiu(v0, 200);
                                sh(v0, s3, 64);
                                v0 = 1;
                                sh(v0, s3, 66);
                                goto L_001c88e4;
                            }
                        L_001c88b8:
                            charge(ctx, 5);
                            sh(v1, s3, 64);
                            lhu(v0, a0, 20);
                            sh(v0, s3, 66);
                        L_001c88e4:
                            charge(ctx, 37);
                            jal(ctx, 0x1C88E4u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kVirtualPad);
                            a1 = 1;
                            jal(ctx, 0x1C88F4u, gen::fn_sub_1E1300_001e1300);
                            jal(ctx, 0x1C88FCu, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEnemySched);
                            a1 = 1;
                            jal(ctx, 0x1C890Cu, gen::fn_sub_1D37F0_001d37f0);
                            a0 = 1;
                            jal(ctx, 0x1C8918u, gen::fn_sub_4532D0_004532d0);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x1C8928u, gen::fn_sub_4350E0_004350e0);
                            jal(ctx, 0x1C8930u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kFootstep);
                            a1 = 1;
                            jal(ctx, 0x1C8940u, gen::fn_sub_1DA000_001da000);
                            lw(v0, s3, f4::evt::kTarget);
                            lw(a0, v0, 80);
                            a1 = 0;
                            a2 = 3;
                            a3 = 0;
                            t0 = 0;
                            jal(ctx, 0x1C8960u, gen::fn_sub_3182D0_003182d0);
                            v0 = 4;
                            sw(v0, s3, f4::evt::kState);
                        }
                    }
                }
            }
            goto L_001cd48c;
        case 0x1CA920u:  // table[2]  -- state 2: wait for the script task (+96); unpause everything -> 1
            // 0x001ca920
            charge(ctx, 6);
            lw(a0, s3, f4::evt::kScript);
            jal(ctx, 0x1CA924u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001ca938
                charge(ctx, 33);
                jal(ctx, 0x1CA938u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kVirtualPad);
                a1 = 0;
                jal(ctx, 0x1CA948u, gen::fn_sub_1E1300_001e1300);
                a0 = 0;
                jal(ctx, 0x1CA954u, gen::fn_sub_1D8C60_001d8c60);
                jal(ctx, 0x1CA95Cu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kFootstep);
                a1 = 0;
                jal(ctx, 0x1CA96Cu, gen::fn_sub_1DA000_001da000);
                jal(ctx, 0x1CA974u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEnemySched);
                a1 = 0;
                jal(ctx, 0x1CA984u, gen::fn_sub_1D37F0_001d37f0);
                a0 = 0;
                jal(ctx, 0x1CA990u, gen::fn_sub_4532D0_004532d0);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x1CA9A0u, gen::fn_sub_4350E0_004350e0);
                jal(ctx, 0x1CA9A8u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kSmap);
                if (v0 != 0) {
                    // 0x001ca9bc
                    charge(ctx, 6);
                    jal(ctx, 0x1CA9BCu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kSmap);
                    a1 = 1;
                    jal(ctx, 0x1CA9CCu, gen::fn_sub_429E80_00429e80);
                }
                // 0x001ca9d4
                charge(ctx, 5);
                jal(ctx, 0x1CA9D4u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kPartyPanel);
                if (v0 != 0) {
                    // 0x001ca9e8
                    charge(ctx, 6);
                    jal(ctx, 0x1CA9E8u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kPartyPanel);
                    a1 = 1;
                    jal(ctx, 0x1CA9F8u, gen::fn_sub_18C0C0_0018c0c0);
                }
                // 0x001caa00
                charge(ctx, 5);
                jal(ctx, 0x1CAA00u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kAreaPanel);
                if (v0 != 0) {
                    // 0x001caa14
                    charge(ctx, 6);
                    jal(ctx, 0x1CAA14u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kAreaPanel);
                    a1 = 1;
                    jal(ctx, 0x1CAA24u, gen::fn_sub_18EB30_0018eb30);
                }
                // 0x001caa2c
                charge(ctx, 7);
                jal(ctx, 0x1CAA2Cu, gen::fn_sub_458930_00458930);
                sw(zero, s3, f4::evt::kScript);
                v0 = 1;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CAA48u:  // table[3]  -- state 3: a door: K_Field_RequestNextField(sField.root, exit +18 / +20 / +22) -> 32
            // 0x001caa48
            charge(ctx, 46);
            jal(ctx, 0x1CAA48u, gen::fn_K_Field_Get_001b9120);
            s2 = v0;
            jal(ctx, 0x1CAA54u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kExits);
            lhu(v0, s3, f4::evt::kMode);
            v1 = v0 & 0x3FF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            s1 = addu(v0, a0);
            jal(ctx, 0x1CAA80u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kExits);
            lhu(v0, s3, f4::evt::kMode);
            v1 = v0 & 0x3FF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            s0 = addu(v0, a0);
            jal(ctx, 0x1CAAACu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kExits);
            lhu(v0, s3, f4::evt::kMode);
            v1 = v0 & 0x3FF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            lw(a0, s2, f4::fld::kRoot);
            lhu(a1, s1, f4::exitrec::kNextMajor);
            lhu(a2, s0, f4::exitrec::kNextMinor);
            lhu(a3, v0, f4::exitrec::kNextEntry);
            jal(ctx, 0x1CAAE8u, gen::fn_sub_1BAAA0_001baaa0);
            v0 = 32;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CAB00u:  // table[4]  -- state 4: first strike: the encounter flash at the enemy's frame 13 -> 5
            // 0x001cab00
            charge(ctx, 11);
            lw(v0, s3, f4::evt::kTarget);
            lw(a0, v0, 80);
            a1 = 0;
            jal(ctx, 0x1CAB0Cu, gen::fn_sub_318990_00318990);
            v0 = 0x41500000;
            mtc1(v0, f1);
            c_lt_s(f0, f1);
            if (!cond(ctx)) {
                // 0x001cab2c
                charge(ctx, 79);
                jal(ctx, 0x1CAB2Cu, gen::fn_sub_453480_00453480);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x1CAB58u, gen::fn_sub_318B60_00318b60);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x330);
                swc1(f1, sp, 0x334);
                swc1(f0, sp, 0x338);
                lwc1(f1, sp, 0x334);
                v0 = 0x42C80000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x334);
                jal(ctx, 0x1CAB90u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kBtlEpl);
                a1 = addiu(sp, 0x330);
                jal(ctx, 0x1CABA0u, gen::fn_sub_1A91B0_001a91b0);
                s0 = v0;
                jal(ctx, 0x1CABACu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kBtlEpl);
                a1 = s0;
                a2 = 3;
                jal(ctx, 0x1CABC0u, gen::fn_sub_1A9390_001a9390);
                a0 = 3;
                a1 = 255;
                a2 = a0;
                a3 = 0;
                jal(ctx, 0x1CABD8u, gen::fn_sub_103C30_00103c30);
                a0 = 0;
                a1 = 7;
                a2 = 3;
                a3 = 0;
                jal(ctx, 0x1CABF0u, gen::fn_sub_10A4E0_0010a4e0);
                jal(ctx, 0x1CABF8u, gen::fn_sub_453480_00453480);
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, 6128);  // &0x8717F0
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                a1 = 0;
                a2 = 2;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x1CAC34u, gen::fn_sub_3182D0_003182d0);
                a0 = 1;
                jal(ctx, 0x1CAC40u, gen::fn_sub_45A430_0045a430);
                jal(ctx, 0x1CAC48u, gen::fn_sub_3C8F70_003c8f70);
                jal(ctx, 0x1CAC50u, gen::fn_sub_3C8F20_003c8f20);
                v0 = 5;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CAC68u:  // table[5]  -- state 5: the flash ran 5 frames: the encounter fade (sub_2FF260) -> 9
            // 0x001cac68
            charge(ctx, 9);
            jal(ctx, 0x1CAC68u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kBtlEpl);
            a1 = si(-1);
            jal(ctx, 0x1CAC78u, gen::fn_sub_1A93D0_001a93d0);
            v0 = slti(v0, 5);
            if (v0 == 0) {
                // 0x001cac8c
                charge(ctx, 7);
                a0 = 0;
                jal(ctx, 0x1CAC90u, gen::fn_sub_2FF260_002ff260);
                v0 = 9;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CACA8u:  // table[6]  -- state 6: ambush: pauses, the flash (The Answer: sField +4628) -> 7
            // 0x001caca8
            charge(ctx, 52);
            jal(ctx, 0x1CACA8u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kVirtualPad);
            a1 = 1;
            jal(ctx, 0x1CACB8u, gen::fn_sub_1E1300_001e1300);
            jal(ctx, 0x1CACC0u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kEnemySched);
            a1 = 1;
            jal(ctx, 0x1CACD0u, gen::fn_sub_1D37F0_001d37f0);
            a0 = 1;
            jal(ctx, 0x1CACDCu, gen::fn_sub_4532D0_004532d0);
            a0 = 0;
            a1 = 1;
            jal(ctx, 0x1CACECu, gen::fn_sub_4350E0_004350e0);
            jal(ctx, 0x1CACF4u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kFootstep);
            a1 = 1;
            jal(ctx, 0x1CAD04u, gen::fn_sub_1DA000_001da000);
            mtc1(zero, f12);
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            a1 = 0;
            jal(ctx, 0x1CAD1Cu, gen::fn_sub_3189F0_003189f0);
            lw(v0, s3, f4::evt::kTarget);
            lw(a0, v0, 80);
            jal(ctx, 0x1CAD2Cu, gen::fn_sub_318B60_00318b60);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0x320);
            swc1(f1, sp, 0x324);
            swc1(f0, sp, 0x328);
            lwc1(f1, sp, 0x324);
            v0 = 0x42480000;
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x324);
            jal(ctx, 0x1CAD64u, gen::fn_sub_17D800_0017d800);
            v1 = 1;
            if (v0 != v1) {
                // 0x001cae68
                charge(ctx, 14);
                jal(ctx, 0x1CAE68u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kBtlEpl);
                a1 = addiu(sp, 0x320);
                jal(ctx, 0x1CAE78u, gen::fn_sub_1A91B0_001a91b0);
                s0 = v0;
                jal(ctx, 0x1CAE84u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kBtlEpl);
                a1 = s0;
                a2 = 3;
                jal(ctx, 0x1CAE98u, gen::fn_sub_1A9390_001a9390);
            } else {
                // 0x001cad78
                charge(ctx, 19);
                v0 = 0x680000;
                ld(v1, v0, 14144);  // 0x683740
                v0 = 0x680000;
                lwc1(f0, v0, 14152);  // 0x683748
                sd(v1, sp, 0x310);
                swc1(f0, sp, 0x318);
                jal(ctx, 0x1CAD90u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEplAnswer2);
                a1 = addiu(sp, 0x320);
                jal(ctx, 0x1CADA0u, gen::fn_sub_1A91B0_001a91b0);
                s0 = v0;
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                jal(ctx, 0x1CADB4u, gen::fn_sub_318B60_00318b60);
                a2 = addiu(sp, 0x220);
                a1 = 8;
                for (;;) {
                    // 0x001cadc4
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
                // 0x001cade8
                charge(ctx, 32);
                sw(zero, sp, 0x258);
                sw(zero, sp, 0x254);
                sw(zero, sp, 0x250);
                v0 = 0x43340000;
                mtc1(v0, f12);
                a0 = addiu(sp, 0x220);
                a1 = addiu(sp, 0x310);
                a2 = 2;
                jal(ctx, 0x1CAE08u, gen::fn_sub_4C31B0_004c31b0);
                lwc1(f2, sp, 0x320);
                lwc1(f1, sp, 0x324);
                lwc1(f0, sp, 0x328);
                swc1(f2, sp, 0x250);
                swc1(f1, sp, 0x254);
                swc1(f0, sp, 0x258);
                jal(ctx, 0x1CAE28u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEplAnswer2);
                a1 = s0;
                a2 = addiu(sp, 0x220);
                jal(ctx, 0x1CAE3Cu, gen::fn_sub_1A9330_001a9330);
                jal(ctx, 0x1CAE44u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEplAnswer2);
                a1 = s0;
                a2 = 3;
                jal(ctx, 0x1CAE58u, gen::fn_sub_1A9390_001a9390);
            }
            // 0x001caea0
            charge(ctx, 25);
            a0 = 0;
            a1 = 7;
            a2 = 3;
            a3 = 0;
            jal(ctx, 0x1CAEB0u, gen::fn_sub_10A4E0_0010a4e0);
            lw(v0, s3, f4::evt::kTarget);
            lw(a0, v0, 80);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x1CAED0u, gen::fn_sub_3182D0_003182d0);
            a0 = 1;
            jal(ctx, 0x1CAEDCu, gen::fn_sub_45A430_0045a430);
            jal(ctx, 0x1CAEE4u, gen::fn_sub_3C8F70_003c8f70);
            jal(ctx, 0x1CAEECu, gen::fn_sub_3C8F20_003c8f20);
            v0 = 7;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CAF04u:  // table[7]  -- state 7: the flash ran 5 (4) frames: the encounter fade -> 9
            // 0x001caf04
            charge(ctx, 5);
            jal(ctx, 0x1CAF04u, gen::fn_sub_17D800_0017d800);
            v1 = 1;
            if (v0 != v1) {
                // 0x001caf44
                charge(ctx, 9);
                jal(ctx, 0x1CAF44u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kBtlEpl);
                a1 = si(-1);
                jal(ctx, 0x1CAF54u, gen::fn_sub_1A93D0_001a93d0);
                v0 = slti(v0, 5);
                if (v0 == 0) {
                L_001caf68:
                    charge(ctx, 14);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    a1 = 0;
                    jal(ctx, 0x1CAF7Cu, gen::fn_sub_3189F0_003189f0);
                    a0 = 0;
                    jal(ctx, 0x1CAF88u, gen::fn_sub_2FF260_002ff260);
                    v0 = 9;
                    sw(v0, s3, f4::evt::kState);
                }
            } else {
                // 0x001caf18
                charge(ctx, 9);
                jal(ctx, 0x1CAF18u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEplAnswer2);
                a1 = si(-1);
                jal(ctx, 0x1CAF28u, gen::fn_sub_1A93D0_001a93d0);
                at = slti(v0, 4);
                if (at == 0) {
                    goto L_001caf68;
                }
                // 0x001caf3c
                charge(ctx, 2);
            }
            goto L_001cd48c;
        case 0x1CAFA0u:  // table[8]  -- state 8: the attack swing: hit test against the shadows (-> 4 / 6) or back to 1
            // 0x001cafa0
            charge(ctx, 11);
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            a1 = 0;
            jal(ctx, 0x1CAFACu, gen::fn_sub_318990_00318990);
            v0 = 0x4F000000;
            mtc1(v0, f1);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x001cafdc
                charge(ctx, 5);
                sub_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(s1, f0);
                v0 = lui(0x8000);
                s1 = s1 | v0;
            } else {
                // 0x001cafcc
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(s1, f0);
            }
            // 0x001caff0
            charge(ctx, 17);
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            jal(ctx, 0x1CAFF8u, gen::fn_sub_318B60_00318b60);
            s0 = v0;
            lwc1(f2, v0, 32);
            lwc1(f1, v0, 36);
            lwc1(f0, v0, 40);
            swc1(f2, sp, 0x300);
            swc1(f1, sp, 0x304);
            swc1(f0, sp, 0x308);
            s4 = 4;
            lw(v0, s3, f4::evt::kSwing);
            lh(v0, v0, 4);
            at = sltu(s1, v0);
            if (at != 0) {
                // 0x001cb034
                charge(ctx, 29);
                lwc1(f0, sp, 0x300);
                neg_s(f0, f0);
                swc1(f0, sp, 0x2F0);
                lwc1(f0, sp, 0x304);
                neg_s(f0, f0);
                swc1(f0, sp, 0x2F4);
                lwc1(f0, sp, 0x308);
                neg_s(f0, f0);
                swc1(f0, sp, 0x2F8);
                a0 = addiu(sp, 0x2F0);
                a1 = a0;
                jal(ctx, 0x1CB060u, gen::fn_sub_4C69F0_004c69f0);
                lwc1(f0, sp, 0x2F0);
                lwc1(f1, s3, 268);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x2F0);
                lwc1(f0, sp, 0x2F4);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x2F4);
                lwc1(f0, sp, 0x2F8);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x2F8);
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                a1 = addiu(sp, 0x2F0);
                a2 = 2;
                jal(ctx, 0x1CB0A0u, gen::fn_sub_318A30_00318a30);
            }
            // 0x001cb0a8
            charge(ctx, 5);
            lw(v0, s3, f4::evt::kSwing);
            lh(v0, v0, 6);
            at = sltu(v0, s1);
            if (at != 0) {
                // 0x001cb0bc
                charge(ctx, 20);
                a0 = addiu(sp, 0x300);
                a1 = a0;
                jal(ctx, 0x1CB0C4u, gen::fn_sub_4C69F0_004c69f0);
                lwc1(f0, sp, 0x300);
                lwc1(f1, s3, 272);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x300);
                lwc1(f0, sp, 0x304);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x304);
                lwc1(f0, sp, 0x308);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x308);
                v0 = 0x870000;
                lw(a0, v0, 6128);  // 0x8717F0
                a1 = addiu(sp, 0x300);
                a2 = 2;
                jal(ctx, 0x1CB104u, gen::fn_sub_318A30_00318a30);
            }
            // 0x001cb10c
            charge(ctx, 5);
            jal(ctx, 0x1CB10Cu, gen::fn_sub_17D800_0017d800);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cb120
                charge(ctx, 3);
                lw(v0, s3, 232);
                if (v0 == 0) {
                    // 0x001cb12c
                    charge(ctx, 2);
                    if (i64(s1) < 0) {
                        // 0x001cb148
                        charge(ctx, 7);
                        v1 = srl(s1, 1);
                        v0 = s1 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x001cb134
                        charge(ctx, 5);
                        mtc1(s1, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x001cb164
                    charge(ctx, 6);
                    v0 = 0x41A00000;
                    mtc1(v0, f0);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x001cb17c
                        charge(ctx, 17);
                        a0 = 1;
                        a1 = 9;
                        a2 = 2;
                        a3 = 12;
                        jal(ctx, 0x1CB18Cu, gen::fn_sub_10A4E0_0010a4e0);
                        v0 = 1;
                        sw(v0, s3, 232);
                        v0 = 0x870000;
                        lw(v0, v0, 6128);  // 0x8717F0
                        lw(a0, v0, 952);
                        a1 = 300;
                        a2 = addiu(sp, 0x1E0);
                        jal(ctx, 0x1CB1B0u, gen::fn_sub_318D10_00318d10);
                        if (v0 != 0) {
                            // 0x001cb1c0
                            charge(ctx, 14);
                            jal(ctx, 0x1CB1C0u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEplAnswer1);
                            a1 = addiu(sp, 0x210);
                            jal(ctx, 0x1CB1D0u, gen::fn_sub_1A91B0_001a91b0);
                            s2 = v0;
                            jal(ctx, 0x1CB1DCu, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEplAnswer1);
                            a1 = s2;
                            a2 = addiu(sp, 0x1E0);
                            jal(ctx, 0x1CB1F0u, gen::fn_sub_1A9330_001a9330);
                        }
                    }
                }
            }
            // 0x001cb1f8
            charge(ctx, 5);
            jal(ctx, 0x1CB1F8u, gen::fn_sub_17D800_0017d800);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cb20c
                charge(ctx, 5);
                lw(v0, s3, f4::evt::kSwing);
                lw(v0, v0, 12);
                v0 = addiu(v0, 5);
                if (s1 == v0) {
                    // 0x001cb220
                    charge(ctx, 6);
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    jal(ctx, 0x1CB228u, gen::fn_sub_318B60_00318b60);
                    a2 = addiu(sp, 0x1A0);
                    a1 = 8;
                    for (;;) {
                        // 0x001cb238
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
                    // 0x001cb25c
                    charge(ctx, 69);
                    lwc1(f2, sp, 0x1D0);
                    lwc1(f1, sp, 0x1D4);
                    lwc1(f0, sp, 0x1D8);
                    swc1(f2, sp, 0x260);
                    swc1(f1, sp, 0x264);
                    swc1(f0, sp, 0x268);
                    ld(v0, sp, 0x260);
                    lwc1(f0, sp, 0x268);
                    sd(v0, sp, 0x2E0);
                    swc1(f0, sp, 0x2E8);
                    a0 = addiu(sp, 0x2D0);
                    lwc1(f2, sp, 0x1C0);
                    lwc1(f1, sp, 0x1C4);
                    lwc1(f0, sp, 0x1C8);
                    swc1(f2, sp, 0x2D0);
                    swc1(f1, sp, 0x2D4);
                    swc1(f0, sp, 0x2D8);
                    a1 = a0;
                    jal(ctx, 0x1CB2A4u, gen::fn_sub_4C69F0_004c69f0);
                    lw(v0, s3, f4::evt::kSwing);
                    lwc1(f1, v0, 20);
                    v0 = 0x42480000;
                    mtc1(v0, f0);
                    sub_s(f1, f1, f0);
                    lwc1(f0, sp, 0x2D0);
                    mul_s(f3, f0, f1);
                    swc1(f3, sp, 0x2D0);
                    lwc1(f0, sp, 0x2D4);
                    mul_s(f2, f0, f1);
                    swc1(f2, sp, 0x2D4);
                    lwc1(f0, sp, 0x2D8);
                    mul_s(f1, f0, f1);
                    swc1(f1, sp, 0x2D8);
                    lwc1(f0, sp, 0x2E0);
                    add_s(f0, f0, f3);
                    swc1(f0, sp, 0x2E0);
                    lwc1(f0, sp, 0x2E4);
                    add_s(f0, f0, f2);
                    swc1(f0, sp, 0x2E4);
                    lwc1(f0, sp, 0x2E8);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x2E8);
                    a0 = addiu(sp, 0x180);
                    ld(v0, sp, 0x260);
                    lwc1(f0, sp, 0x268);
                    sd(v0, sp, 0x180);
                    swc1(f0, sp, 0x188);
                    lwc1(f2, sp, 0x2E0);
                    lwc1(f1, sp, 0x2E4);
                    lwc1(f0, sp, 0x2E8);
                    swc1(f2, sp, 0x18C);
                    swc1(f1, sp, 0x190);
                    swc1(f0, sp, 0x194);
                    lwc1(f0, sp, 0x184);
                    v0 = 0x43960000;
                    mtc1(v0, f1);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x184);
                    lwc1(f0, sp, 0x190);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x190);
                    a1 = addiu(sp, 0x2C0);
                    jal(ctx, 0x1CB360u, gen::fn_sub_1ACC30_001acc30);
                    if (v0 == 0) {
                        // 0x001cb370
                        charge(ctx, 28);
                        lwc1(f2, sp, 0x2E0);
                        lwc1(f1, sp, 0x2E4);
                        lwc1(f0, sp, 0x2E8);
                        swc1(f2, sp, 0x18C);
                        swc1(f1, sp, 0x190);
                        swc1(f0, sp, 0x194);
                        a0 = addiu(sp, 0x180);
                        lwc1(f2, sp, 0x18C);
                        lwc1(f1, sp, 0x190);
                        lwc1(f0, sp, 0x194);
                        swc1(f2, sp, 0x180);
                        swc1(f1, sp, 0x184);
                        swc1(f0, sp, 0x188);
                        lwc1(f0, sp, 0x184);
                        v0 = 0x447A0000;
                        mtc1(v0, f1);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x184);
                        lwc1(f0, sp, 0x190);
                        sub_s(f0, f0, f1);
                        swc1(f0, sp, 0x190);
                        a1 = addiu(sp, 0x2C0);
                        jal(ctx, 0x1CB3CCu, gen::fn_sub_1ACC30_001acc30);
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x001cb3e0
                            charge(ctx, 2);
                            lwc1(f0, sp, 0x2C4);
                            swc1(f0, sp, 0x2E4);
                        }
                        // 0x001cb3e8
                        charge(ctx, 14);
                        jal(ctx, 0x1CB3E8u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kEplAnswer3);
                        a1 = addiu(sp, 0x2E0);
                        jal(ctx, 0x1CB3F8u, gen::fn_sub_1A91B0_001a91b0);
                        s2 = v0;
                        jal(ctx, 0x1CB404u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kEplAnswer3);
                        a1 = s2;
                        a2 = 3;
                        jal(ctx, 0x1CB418u, gen::fn_sub_1A9390_001a9390);
                    }
                }
            }
            // 0x001cb420
            charge(ctx, 5);
            lw(v0, s3, f4::evt::kSwing);
            lw(v1, v0, 12);
            v0 = sltu(s1, v1);
            if (v0 == 0) {
                // 0x001cb434
                charge(ctx, 4);
                v0 = addiu(v1, 5);
                at = sltu(s1, v0);
                if (at == 0) {
                    goto L_001cb78c;
                }
                // 0x001cb444
                charge(ctx, 4);
                jal(ctx, 0x1CB444u, gen::fn_sub_4352E0_004352e0);
                if (v0 != 0) {
                    goto L_001cb78c;
                }
                // 0x001cb454
                charge(ctx, 10);
                lw(v0, s3, f4::evt::kSwing);
                a0 = 0x870000;
                a0 = addiu(a0, 6048);  // &gFldUnitsPc
                lwc1(f12, v0, 20);
                lwc1(f13, v0, 16);
                jal(ctx, 0x1CB468u, gen::fn_sub_1C6A20_001c6a20);
                s2 = v0;
                if (s2 != 0) {
                    // 0x001cb47c
                    charge(ctx, 6);
                    lw(a0, s2, 72);
                    jal(ctx, 0x1CB480u, gen::fn_datUnitIsGenusDead_002ff790);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cb494
                        charge(ctx, 1);
                        s2 = 0;
                    }
                }
                // 0x001cb498
                charge(ctx, 3);
                sw(s2, s3, f4::evt::kTarget);
                if (s2 == 0) {
                    goto L_001cb78c;
                }
                // 0x001cb4a4
                charge(ctx, 3);
                lw(v0, gp, -19168);  // 0x7CE210
                if (v0 != 0) {
                    // 0x001cb628
                    charge(ctx, 34);
                    lw(a0, s2, 80);
                    jal(ctx, 0x1CB62Cu, gen::fn_sub_318B60_00318b60);
                    lwc1(f2, v0, 48);
                    lwc1(f1, v0, 52);
                    lwc1(f0, v0, 56);
                    swc1(f2, sp, 0x2B0);
                    swc1(f1, sp, 0x2B4);
                    swc1(f0, sp, 0x2B8);
                    lwc1(f1, sp, 0x2B4);
                    v0 = 0x42480000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x2B4);
                    a0 = 1;
                    a1 = 8;
                    a2 = 2;
                    a3 = a1;
                    jal(ctx, 0x1CB674u, gen::fn_sub_10A4E0_0010a4e0);
                    jal(ctx, 0x1CB67Cu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kEplDeath);
                    a1 = addiu(sp, 0x2B0);
                    jal(ctx, 0x1CB68Cu, gen::fn_sub_1A91B0_001a91b0);
                    lw(a0, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB698u, gen::fn_sub_1D0110_001d0110);
                    lw(v1, s3, f4::evt::kWeapon);
                    v0 = 6;
                    if (v1 == v0) {
                        // 0x001cb6b0
                        charge(ctx, 1);
                        s4 = 0;
                    }
                    // 0x001cb6b4
                    charge(ctx, 5);
                    jal(ctx, 0x1CB6B4u, gen::fn_sub_17D800_0017d800);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cb6c8
                        charge(ctx, 7);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        a1 = 0;
                        jal(ctx, 0x1CB6DCu, gen::fn_sub_3189F0_003189f0);
                    }
                    // 0x001cb6e4
                    charge(ctx, 32);
                    a0 = 1;
                    jal(ctx, 0x1CB6E8u, gen::fn_sub_1DDE00_001dde00);
                    a2 = dsll32(v0, 16);
                    a2 = dsra32(a2, 16);
                    a3 = s4 & 0xFFFF;
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    a1 = 0;
                    t0 = 1;
                    jal(ctx, 0x1CB70Cu, gen::fn_sub_3182D0_003182d0);
                    jal(ctx, 0x1CB714u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kVirtualPad);
                    a1 = 0;
                    jal(ctx, 0x1CB724u, gen::fn_sub_1E1300_001e1300);
                    a0 = 0;
                    jal(ctx, 0x1CB730u, gen::fn_sub_1D8C60_001d8c60);
                    jal(ctx, 0x1CB738u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kCamera);
                    lw(a1, s3, f4::evt::kCameraMode);
                    jal(ctx, 0x1CB748u, gen::fn_sub_1D5C10_001d5c10);
                    jal(ctx, 0x1CB750u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kSmap);
                    if (v0 != 0) {
                        // 0x001cb764
                        charge(ctx, 6);
                        jal(ctx, 0x1CB764u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kSmap);
                        a1 = 0;
                        jal(ctx, 0x1CB774u, gen::fn_sub_429E90_00429e90);
                    }
                    // 0x001cb77c
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s3, f4::evt::kState);
                } else {
                    // 0x001cb4b0
                    charge(ctx, 31);
                    jal(ctx, 0x1CB4B0u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kEnemySched);
                    a1 = 1;
                    jal(ctx, 0x1CB4C0u, gen::fn_sub_1D37F0_001d37f0);
                    a0 = 1;
                    jal(ctx, 0x1CB4CCu, gen::fn_sub_4532D0_004532d0);
                    a0 = 0;
                    a1 = 1;
                    jal(ctx, 0x1CB4DCu, gen::fn_sub_4350E0_004350e0);
                    jal(ctx, 0x1CB4E4u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kFootstep);
                    a1 = 1;
                    jal(ctx, 0x1CB4F4u, gen::fn_sub_1DA000_001da000);
                    a0 = addiu(s3, 40);
                    lw(a1, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB504u, gen::fn_sub_1C7830_001c7830);
                    lw(a0, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB510u, gen::fn_sub_4353F0_004353f0);
                    v1 = dsll32(v0, 24);
                    v1 = dsra32(v1, 24);
                    v0 = 3;
                    if (v1 != v0) {
                        // 0x001cb52c
                        charge(ctx, 3);
                        v0 = 5;
                        if (v1 == v0) {
                            goto L_001cb538;
                        }
                        goto L_001cb544;
                    }
                L_001cb538:
                    charge(ctx, 3);
                    lhu(v0, s3, f4::evt::kPacket);
                    v0 = v0 | 0x2;
                    sh(v0, s3, f4::evt::kPacket);
                L_001cb544:
                    charge(ctx, 5);
                    lw(a0, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB548u, gen::fn_K_Battle_FindTaskOfUnit_001d8d80);
                    if (v0 != 0) {
                        // 0x001cb558
                        charge(ctx, 3);
                        lhu(v0, s3, f4::evt::kPacket);
                        v0 = v0 | 0x4;
                        sh(v0, s3, f4::evt::kPacket);
                    }
                    // 0x001cb564
                    charge(ctx, 5);
                    lw(a0, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB568u, gen::fn_sub_1C65E0_001c65e0);
                    if (v0 == 0) {
                        // 0x001cb578
                        charge(ctx, 3);
                        lhu(v0, s3, f4::evt::kPacket);
                        v0 = v0 | 0x8;
                        sh(v0, s3, f4::evt::kPacket);
                    }
                    // 0x001cb584
                    charge(ctx, 5);
                    lw(v0, s3, f4::evt::kTarget);
                    lw(a0, v0, 76);
                    lhu(v1, a0, 18);
                    if (v1 == 0) {
                        // 0x001cb598
                        charge(ctx, 3);
                        lhu(v0, a0, 20);
                        if (v0 != 0) {
                            goto L_001cb5a4;
                        }
                        // 0x001cb5b8
                        charge(ctx, 6);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v0, v0, f4::scene::kMajor);
                        v0 = addiu(v0, 200);
                        sh(v0, s3, 64);
                        v0 = 1;
                        sh(v0, s3, 66);
                        goto L_001cb5d0;
                    }
                L_001cb5a4:
                    charge(ctx, 5);
                    sh(v1, s3, 64);
                    lhu(v0, a0, 20);
                    sh(v0, s3, 66);
                L_001cb5d0:
                    charge(ctx, 11);
                    jal(ctx, 0x1CB5D0u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kCamera);
                    lw(a1, s3, f4::evt::kCameraMode);
                    jal(ctx, 0x1CB5E0u, gen::fn_sub_1D5C10_001d5c10);
                    jal(ctx, 0x1CB5E8u, gen::fn_sub_17D800_0017d800);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cb5fc
                        charge(ctx, 7);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        a1 = 0;
                        jal(ctx, 0x1CB610u, gen::fn_sub_3189F0_003189f0);
                    }
                    // 0x001cb618
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s3, f4::evt::kState);
                }
                goto L_001cd48c;
            }
        L_001cb78c:
            charge(ctx, 7);
            jal(ctx, 0x1CB78Cu, gen::fn_sub_453460_00453460);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 0);
            if (at != 0) {
                // 0x001cb93c
                charge(ctx, 5);
                lw(v0, s3, f4::evt::kSwing);
                lh(v0, v0, 2);
                v0 = sltu(s1, v0);
                if (v0 == 0) {
                    // 0x001cb950
                    charge(ctx, 4);
                    lw(v1, s3, f4::evt::kWeapon);
                    v0 = 6;
                    if (v1 == v0) {
                        // 0x001cb960
                        charge(ctx, 1);
                        s4 = 0;
                    }
                    // 0x001cb964
                    charge(ctx, 5);
                    jal(ctx, 0x1CB964u, gen::fn_sub_17D800_0017d800);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cb978
                        charge(ctx, 7);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        a1 = 0;
                        jal(ctx, 0x1CB98Cu, gen::fn_sub_3189F0_003189f0);
                    }
                    // 0x001cb994
                    charge(ctx, 38);
                    lwc1(f2, s3, 276);
                    lwc1(f1, s3, 280);
                    lwc1(f0, s3, 284);
                    swc1(f2, s0, 48);
                    swc1(f1, s0, 52);
                    swc1(f0, s0, 56);
                    a0 = 1;
                    jal(ctx, 0x1CB9B0u, gen::fn_sub_1DDE00_001dde00);
                    a2 = dsll32(v0, 16);
                    a2 = dsra32(a2, 16);
                    a3 = s4 & 0xFFFF;
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    a1 = 0;
                    t0 = 1;
                    jal(ctx, 0x1CB9D4u, gen::fn_sub_3182D0_003182d0);
                    jal(ctx, 0x1CB9DCu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kVirtualPad);
                    a1 = 0;
                    jal(ctx, 0x1CB9ECu, gen::fn_sub_1E1300_001e1300);
                    a0 = 0;
                    jal(ctx, 0x1CB9F8u, gen::fn_sub_1D8C60_001d8c60);
                    jal(ctx, 0x1CBA00u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kCamera);
                    lw(a1, s3, f4::evt::kCameraMode);
                    jal(ctx, 0x1CBA10u, gen::fn_sub_1D5C10_001d5c10);
                    jal(ctx, 0x1CBA18u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kSmap);
                    if (v0 != 0) {
                        // 0x001cba2c
                        charge(ctx, 6);
                        jal(ctx, 0x1CBA2Cu, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kSmap);
                        a1 = 0;
                        jal(ctx, 0x1CBA3Cu, gen::fn_sub_429E90_00429e90);
                    }
                    // 0x001cba44
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s3, f4::evt::kState);
                }
            } else {
                // 0x001cb7a8
                charge(ctx, 17);
                jal(ctx, 0x1CB7A8u, gen::fn_sub_453460_00453460);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 6);
                v0 = 0x870000;
                v0 = addiu(v0, -4704);  // &gFldUnitsEc
                v0 = addu(v0, v1);
                sw(v0, s3, f4::evt::kTarget);
                lw(a0, v0, 72);
                jal(ctx, 0x1CB7D8u, gen::fn_datUnitIsGenusDead_002ff790);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001cb7ec
                    charge(ctx, 15);
                    a0 = addiu(s3, 40);
                    lw(a1, s3, f4::evt::kTarget);
                    jal(ctx, 0x1CB7F4u, gen::fn_sub_1C7830_001c7830);
                    lhu(v0, s3, f4::evt::kPacket);
                    v0 = v0 | 0x1;
                    sh(v0, s3, f4::evt::kPacket);
                    lhu(v0, s3, f4::evt::kPacket);
                    v0 = v0 | 0x2;
                    sh(v0, s3, f4::evt::kPacket);
                    lw(v0, s3, f4::evt::kTarget);
                    lw(a0, v0, 76);
                    lhu(v1, a0, 18);
                    if (v1 == 0) {
                        // 0x001cb828
                        charge(ctx, 3);
                        lhu(v0, a0, 20);
                        if (v0 != 0) {
                            goto L_001cb834;
                        }
                        // 0x001cb848
                        charge(ctx, 6);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(v0, v0, f4::scene::kMajor);
                        v0 = addiu(v0, 200);
                        sh(v0, s3, 64);
                        v0 = 1;
                        sh(v0, s3, 66);
                        goto L_001cb860;
                    }
                L_001cb834:
                    charge(ctx, 5);
                    sh(v1, s3, 64);
                    lhu(v0, a0, 20);
                    sh(v0, s3, 66);
                L_001cb860:
                    charge(ctx, 44);
                    jal(ctx, 0x1CB860u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kVirtualPad);
                    a1 = 1;
                    jal(ctx, 0x1CB870u, gen::fn_sub_1E1300_001e1300);
                    jal(ctx, 0x1CB878u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kEnemySched);
                    a1 = 1;
                    jal(ctx, 0x1CB888u, gen::fn_sub_1D37F0_001d37f0);
                    a0 = 1;
                    jal(ctx, 0x1CB894u, gen::fn_sub_4532D0_004532d0);
                    a0 = 0;
                    a1 = 1;
                    jal(ctx, 0x1CB8A4u, gen::fn_sub_4350E0_004350e0);
                    jal(ctx, 0x1CB8ACu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kFootstep);
                    a1 = 1;
                    jal(ctx, 0x1CB8BCu, gen::fn_sub_1DA000_001da000);
                    lw(v0, s3, f4::evt::kTarget);
                    lw(a0, v0, 80);
                    a1 = 0;
                    a2 = 3;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x1CB8DCu, gen::fn_sub_3182D0_003182d0);
                    jal(ctx, 0x1CB8E4u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kCamera);
                    lw(a1, s3, f4::evt::kCameraMode);
                    jal(ctx, 0x1CB8F4u, gen::fn_sub_1D5C10_001d5c10);
                    jal(ctx, 0x1CB8FCu, gen::fn_sub_17D800_0017d800);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cb910
                        charge(ctx, 7);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        a1 = 0;
                        jal(ctx, 0x1CB924u, gen::fn_sub_3189F0_003189f0);
                    }
                    // 0x001cb92c
                    charge(ctx, 4);
                    v0 = 4;
                    sw(v0, s3, f4::evt::kState);
                }
            }
            goto L_001cd48c;
        case 0x1CBA54u:  // table[9]  -- state 9: tear the field down for the battle (camera saved, scene unloaded) -> 10
            // 0x001cba54
            charge(ctx, 4);
            jal(ctx, 0x1CBA54u, gen::fn_sub_2FF310_002ff310);
            if (v0 != 0) {
                // 0x001cba64
                charge(ctx, 4);
                jal(ctx, 0x1CBA64u, gen::fn_sub_1D00B0_001d00b0);
                if (v0 != 0) {
                    // 0x001cba74
                    charge(ctx, 11);
                    jal(ctx, 0x1CBA74u, gen::fn_sub_1C00D0_001c00d0);
                    lw(a0, s3, f4::evt::kDrawCmd);
                    a1 = 0;
                    jal(ctx, 0x1CBA84u, gen::fn_sub_1CD790_001cd790);
                    jal(ctx, 0x1CBA8Cu, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kWalls);
                    if (v0 != 0) {
                        // 0x001cbaa0
                        charge(ctx, 8);
                        jal(ctx, 0x1CBAA0u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kWalls);
                        jal(ctx, 0x1CBAACu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBAB4u, gen::fn_K_Field_Get_001b9120);
                        sw(zero, v0, f4::fld::kWalls);
                    }
                    // 0x001cbac0
                    charge(ctx, 5);
                    jal(ctx, 0x1CBAC0u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kSmap);
                    if (v0 != 0) {
                        // 0x001cbad4
                        charge(ctx, 8);
                        jal(ctx, 0x1CBAD4u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kSmap);
                        jal(ctx, 0x1CBAE0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBAE8u, gen::fn_K_Field_Get_001b9120);
                        sw(zero, v0, f4::fld::kSmap);
                    }
                    // 0x001cbaf4
                    charge(ctx, 5);
                    jal(ctx, 0x1CBAF4u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kPartyPanel);
                    if (v0 != 0) {
                        // 0x001cbb08
                        charge(ctx, 8);
                        jal(ctx, 0x1CBB08u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kPartyPanel);
                        jal(ctx, 0x1CBB14u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBB1Cu, gen::fn_K_Field_Get_001b9120);
                        sw(zero, v0, f4::fld::kPartyPanel);
                    }
                    // 0x001cbb28
                    charge(ctx, 5);
                    jal(ctx, 0x1CBB28u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kVirtualPad);
                    if (v0 != 0) {
                        // 0x001cbb3c
                        charge(ctx, 8);
                        jal(ctx, 0x1CBB3Cu, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kVirtualPad);
                        jal(ctx, 0x1CBB48u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBB50u, gen::fn_K_Field_Get_001b9120);
                        sw(zero, v0, f4::fld::kVirtualPad);
                    }
                    // 0x001cbb5c
                    charge(ctx, 5);
                    jal(ctx, 0x1CBB5Cu, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kCamera);
                    if (v0 != 0) {
                        // 0x001cbb70
                        charge(ctx, 9);
                        jal(ctx, 0x1CBB70u, gen::fn_K_Field_Get_001b9120);
                        a0 = addiu(sp, 0x120);
                        lw(a1, v0, f4::fld::kCamera);
                        jal(ctx, 0x1CBB80u, gen::fn_sub_1D68E0_001d68e0);
                        a2 = addiu(sp, 0x120);
                        a1 = addiu(s3, 128);
                        a0 = 3;
                        for (;;) {
                            // 0x001cbb94
                            charge(ctx, 9);
                            lq(v1, a2, 0);
                            lq(v0, a2, 16);
                            a2 = addiu(a2, 32);
                            a0 = addiu(a0, -1);
                            sq(v1, a1, 0);
                            sq(v0, a1, 16);
                            a1 = addiu(a1, 32);
                            if (i64(a0) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x001cbbb8
                        charge(ctx, 8);
                        jal(ctx, 0x1CBBB8u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kCamera);
                        jal(ctx, 0x1CBBC4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBBCCu, gen::fn_K_Field_Get_001b9120);
                        sw(zero, v0, f4::fld::kCamera);
                    }
                    // 0x001cbbd8
                    charge(ctx, 7);
                    jal(ctx, 0x1CBBD8u, gen::fn_sub_1E7410_001e7410);
                    jal(ctx, 0x1CBBE0u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kAreaPanel);
                    if (v0 != 0) {
                        // 0x001cbbf4
                        charge(ctx, 6);
                        jal(ctx, 0x1CBBF4u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kAreaPanel);
                        a1 = 0;
                        jal(ctx, 0x1CBC04u, gen::fn_sub_18EB30_0018eb30);
                    }
                    // 0x001cbc0c
                    charge(ctx, 21);
                    jal(ctx, 0x1CBC0Cu, gen::fn_sub_1D4180_001d4180);
                    jal(ctx, 0x1CBC14u, gen::fn_sub_455B50_00455b50);
                    jal(ctx, 0x1CBC1Cu, gen::fn_sub_1CE880_001ce880);
                    a0 = 1;
                    jal(ctx, 0x1CBC28u, gen::fn_sub_1D1780_001d1780);
                    a0 = 1;
                    jal(ctx, 0x1CBC34u, gen::fn_sub_1D17F0_001d17f0);
                    jal(ctx, 0x1CBC3Cu, gen::fn_sub_1D8CF0_001d8cf0);
                    jal(ctx, 0x1CBC44u, gen::fn_sub_1C07F0_001c07f0);
                    jal(ctx, 0x1CBC4Cu, gen::fn_K_Scene_IsRandomFloor_001a0250);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x001cbc60
                        charge(ctx, 5);
                        jal(ctx, 0x1CBC60u, gen::fn_sub_1A02C0_001a02c0);
                        v1 = 1;
                        if (v0 == v1) {
                            goto L_001cbc74;
                        }
                        goto L_001cbcb8;
                    }
                L_001cbc74:
                    charge(ctx, 3);
                    s1 = 0;
                    for (;;) {
                        // 0x001cbcac
                        charge(ctx, 3);
                        v0 = sltiu(s1, 9);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001cbc80
                        charge(ctx, 7);
                        v1 = sll(s1, 2);
                        v0 = 0x870000;
                        v0 = addiu(v0, -16960);  // &0x86BDC0
                        s0 = addu(v0, v1);
                        lw(a0, s0, 0);
                        if (a0 != 0) {
                            // 0x001cbc9c
                            charge(ctx, 3);
                            jal(ctx, 0x1CBC9Cu, gen::fn_sub_1B3C90_001b3c90);
                            sw(zero, s0, 0);
                        }
                        // 0x001cbca8
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                    }
                L_001cbcb8:
                    charge(ctx, 10);
                    jal(ctx, 0x1CBCB8u, gen::fn_sub_3B5AB0_003b5ab0);
                    a0 = 2;
                    jal(ctx, 0x1CBCC4u, gen::fn_sub_350080_00350080);
                    lw(v0, s3, f4::evt::kState);
                    v0 = addiu(v0, 1);
                    sw(v0, s3, f4::evt::kState);
                }
            }
            goto L_001cd48c;
        case 0x1CBCE0u:  // table[10, 11, 12, 13]  -- states 10..13: one frame each -> 14
            // 0x001cbce0
            charge(ctx, 4);
            v0 = addiu(a0, 1);
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CBCF0u:  // table[14]  -- state 14: tutorial flags 3574..3577, the pre-battle tasks, btlStart(+40) -> +100 -> 15
            // 0x001cbcf0
            charge(ctx, 5);
            lw(v0, s3, 60);
            lhu(v1, v0, 8);
            v0 = 469;
            if (v1 == v0) {
                // 0x001cbd78
                charge(ctx, 4);
                a0 = 3577;
                a1 = 0;
                jal(ctx, 0x1CBD80u, gen::fn_datSetFlag_0016f1f0);
            } else {
                // 0x001cbd04
                charge(ctx, 3);
                v0 = 468;
                if (v1 == v0) {
                    // 0x001cbd60
                    charge(ctx, 6);
                    a0 = 3576;
                    a1 = 0;
                    jal(ctx, 0x1CBD68u, gen::fn_datSetFlag_0016f1f0);
                } else {
                    // 0x001cbd10
                    charge(ctx, 3);
                    v0 = 467;
                    if (v1 == v0) {
                        // 0x001cbd48
                        charge(ctx, 6);
                        a0 = 3575;
                        a1 = 0;
                        jal(ctx, 0x1CBD50u, gen::fn_datSetFlag_0016f1f0);
                    } else {
                        // 0x001cbd1c
                        charge(ctx, 3);
                        v0 = 466;
                        if (v1 == v0) {
                            // 0x001cbd30
                            charge(ctx, 6);
                            a0 = 3574;
                            a1 = 0;
                            jal(ctx, 0x1CBD38u, gen::fn_datSetFlag_0016f1f0);
                        } else {
                            // 0x001cbd28
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x001cbd88
            charge(ctx, 5);
            jal(ctx, 0x1CBD88u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kBattleTasks);
            if (v0 != 0) {
                // 0x001cbd9c
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x001cbdd8
                    charge(ctx, 3);
                    v0 = slti(s1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001cbda8
                    charge(ctx, 12);
                    s0 = sll(s1, 2);
                    jal(ctx, 0x1CBDACu, gen::fn_K_Field_Get_001b9120);
                    v0 = addu(v0, s0);
                    lw(a0, v0, f4::fld::kBattleTasks);
                    jal(ctx, 0x1CBDBCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    jal(ctx, 0x1CBDC4u, gen::fn_K_Field_Get_001b9120);
                    v0 = addu(v0, s0);
                    sw(zero, v0, f4::fld::kBattleTasks);
                    s1 = addiu(s1, 1);
                }
                // 0x001cbde4
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001cbe38
                    charge(ctx, 3);
                    v0 = slti(s0, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001cbdf0
                    charge(ctx, 7);
                    s1 = sll(s0, 2);
                    jal(ctx, 0x1CBDF4u, gen::fn_K_Field_Get_001b9120);
                    v0 = addu(v0, s1);
                    lw(v0, v0, f4::fld::kBattleTasks2);
                    if (v0 != 0) {
                        // 0x001cbe0c
                        charge(ctx, 10);
                        jal(ctx, 0x1CBE0Cu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s1);
                        lw(a0, v0, f4::fld::kBattleTasks2);
                        jal(ctx, 0x1CBE1Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        jal(ctx, 0x1CBE24u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s1);
                        sw(zero, v0, f4::fld::kBattleTasks2);
                    }
                    // 0x001cbe34
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
            }
            // 0x001cbe44
            charge(ctx, 8);
            a0 = addiu(s3, 40);
            jal(ctx, 0x1CBE48u, gen::fn_btlStart_0027d1d0);
            sw(v0, s3, f4::evt::kBattle);
            v0 = 15;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CBE64u:  // table[15]  -- state 15: the battle ended: victory / escape -> 16, game over -> 31, else -> 30
            // 0x001cbe64
            charge(ctx, 6);
            lw(a0, s3, f4::evt::kBattle);
            jal(ctx, 0x1CBE68u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001cbe7c
                charge(ctx, 4);
                jal(ctx, 0x1CBE7Cu, gen::fn_sub_1B08D0_001b08d0);
                if (v0 != 0) {
                    // 0x001cbe8c
                    charge(ctx, 4);
                    jal(ctx, 0x1CBE8Cu, gen::fn_sub_1B09B0_001b09b0);
                    if (v0 != 0) {
                        // 0x001cbe9c
                        charge(ctx, 21);
                        jal(ctx, 0x1CBE9Cu, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kRoot);
                        jal(ctx, 0x1CBEA8u, gen::fn_K_Field_GetMajorId_001bab20);
                        s0 = dsll32(v0, 16);
                        s0 = dsra32(s0, 16);
                        jal(ctx, 0x1CBEB8u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kRoot);
                        jal(ctx, 0x1CBEC4u, gen::fn_K_Field_GetMinorId_001bab30);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = s0;
                        jal(ctx, 0x1CBED8u, gen::fn_sub_1B0870_001b0870);
                        jal(ctx, 0x1CBEE0u, gen::fn_sub_45AF40_0045af40);
                        if (v0 != 0) {
                            // 0x001cbf5c
                            charge(ctx, 2);
                            if (i64(v0) > 0) {
                                // 0x001cbf64
                                charge(ctx, 6);
                                a0 = 0;
                                jal(ctx, 0x1CBF68u, gen::fn_sub_45A430_0045a430);
                                a0 = 0;
                                jal(ctx, 0x1CBF74u, gen::fn_sub_45AF70_0045af70);
                            }
                            // 0x001cbf7c
                            charge(ctx, 5);
                            lw(v0, s3, 60);
                            lhu(v1, v0, 8);
                            v0 = 506;
                            if (v1 != v0) {
                                // 0x001cbf90
                                charge(ctx, 4);
                                lw(a0, s3, f4::evt::kTarget);
                                jal(ctx, 0x1CBF94u, gen::fn_sub_1D0110_001d0110);
                                sw(zero, s3, f4::evt::kTarget);
                            }
                            // 0x001cbfa0
                            charge(ctx, 7);
                            v0 = 0x870000;
                            lw(a0, v0, 6120);  // 0x8717E8
                            jal(ctx, 0x1CBFA8u, gen::fn_datUnitIsGenusDead_002ff790);
                            s0 = 1;
                            if (v0 != s0) {
                                // 0x001cc010
                                charge(ctx, 2);
                                for (;;) {
                                    // 0x001cc0a4
                                    charge(ctx, 3);
                                    v0 = sltiu(s0, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001cc018
                                    charge(ctx, 9);
                                    v0 = sll(s0, 3);
                                    v0 = subu(v0, s0);
                                    v1 = sll(v0, 6);
                                    v0 = 0x870000;
                                    v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                    v0 = addu(v0, v1);
                                    lw(a0, v0, 72);
                                    if (a0 != 0) {
                                        // 0x001cc03c
                                        charge(ctx, 5);
                                        jal(ctx, 0x1CC03Cu, gen::fn_datUnitIsGenusDead_002ff790);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            // 0x001cc050
                                            charge(ctx, 6);
                                            a0 = 3105;
                                            jal(ctx, 0x1CC054u, gen::fn_datGetFlag_0016f190);
                                            a1 = 1;
                                            if (v0 == a1) {
                                                // 0x001cc068
                                                charge(ctx, 14);
                                                v0 = sll(s0, 3);
                                                v0 = subu(v0, s0);
                                                v1 = sll(v0, 6);
                                                v0 = 0x870000;
                                                v0 = addiu(v0, 6048);  // &gFldUnitsPc
                                                v0 = addu(v0, v1);
                                                s1 = addiu(v0, 424);
                                                lh(a0, v0, 424);
                                                jal(ctx, 0x1CC088u, gen::fn_sub_16CF40_0016cf40);
                                                lh(a0, s1, 0);
                                                a1 = 0x80000;
                                                jal(ctx, 0x1CC098u, gen::fn_sub_16D9D0_0016d9d0);
                                            }
                                        }
                                    }
                                    // 0x001cc0a0
                                    charge(ctx, 1);
                                    s0 = addiu(s0, 1);
                                }
                                // 0x001cc0b0
                                charge(ctx, 9);
                                jal(ctx, 0x1CC0B0u, gen::fn_sub_1C03F0_001c03f0);
                                jal(ctx, 0x1CC0B8u, gen::fn_sub_1D11B0_001d11b0);
                                sw(zero, s3, f4::evt::kBattle);
                                v0 = 16;
                                sw(v0, s3, f4::evt::kState);
                            } else {
                                // 0x001cbfbc
                                charge(ctx, 21);
                                jal(ctx, 0x1CBFBCu, gen::fn_sub_45A400_0045a400);
                                jal(ctx, 0x1CBFC4u, gen::fn_sub_1B0920_001b0920);
                                jal(ctx, 0x1CBFCCu, gen::fn_sub_1B09F0_001b09f0);
                                lw(a2, gp, -19148);  // g_fldMainScriptSize
                                a0 = 10;
                                lw(a1, gp, -19144);  // g_fldMainScriptPtr
                                a3 = s0;
                                jal(ctx, 0x1CBFE4u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                sw(v0, s3, f4::evt::kScript);
                                a0 = 5149;
                                a1 = s0;
                                jal(ctx, 0x1CBFF8u, gen::fn_datSetFlag_0016f1f0);
                                v0 = 31;
                                sw(v0, s3, f4::evt::kState);
                            }
                        } else {
                            // 0x001cbef0
                            charge(ctx, 17);
                            jal(ctx, 0x1CBEF0u, gen::fn_sub_1B0920_001b0920);
                            jal(ctx, 0x1CBEF8u, gen::fn_sub_1B09F0_001b09f0);
                            a0 = 3;
                            a1 = 0;
                            jal(ctx, 0x1CBF08u, gen::fn_sub_109F60_00109f60);
                            a0 = 0;
                            a1 = 135;
                            a2 = 3;
                            jal(ctx, 0x1CBF1Cu, gen::fn_sub_3952D0_003952d0);
                            sw(zero, gp, -19060);  // 0x7CE27C
                            lw(a0, s3, f4::evt::kScript);
                            if (a0 != 0) {
                                // 0x001cbf34
                                charge(ctx, 2);
                                jal(ctx, 0x1CBF34u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                            }
                            // 0x001cbf3c
                            charge(ctx, 8);
                            a0 = 5149;
                            a1 = 1;
                            jal(ctx, 0x1CBF44u, gen::fn_datSetFlag_0016f1f0);
                            v0 = 30;
                            sw(v0, s3, f4::evt::kState);
                        }
                    }
                }
            }
            goto L_001cd48c;
        case 0x1CC0D4u:  // table[16]  -- state 16: reload the exit table, the field script and the scene -> 17
            // 0x001cc0d4
            charge(ctx, 4);
            jal(ctx, 0x1CC0D4u, gen::fn_sub_1B08D0_001b08d0);
            if (v0 != 0) {
                // 0x001cc0e4
                charge(ctx, 15);
                jal(ctx, 0x1CC0E4u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC0F0u, gen::fn_K_Field_GetMinorId_001bab30);
                s0 = v0 & 0xFFFF;
                jal(ctx, 0x1CC0FCu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC108u, gen::fn_K_Field_GetMajorId_001bab20);
                s1 = v0 & 0xFFFF;
                v0 = si(-1);
                if (s1 != v0) {
                    // 0x001cc12c
                    charge(ctx, 4);
                    jal(ctx, 0x1CC12Cu, gen::fn_sub_1B0910_001b0910);
                    if (v0 != 0) {
                        // 0x001cc190
                        charge(ctx, 1);
                        v0 = 1;
                    } else {
                        // 0x001cc13c
                        charge(ctx, 12);
                        a3 = s0 & 0xFFFF;
                        a0 = addiu(sp, 0xA0);
                        a1 = 0x680000;
                        a1 = addiu(a1, 14064);  // "field/table/h%03d_%03d.bin"
                        a2 = s1;
                        jal(ctx, 0x1CC150u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0xA0);
                        jal(ctx, 0x1CC15Cu, gen::fn_H_Cdvd_FileExists_001008b0);
                        if (v0 != 0) {
                            // 0x001cc178
                            charge(ctx, 6);
                            a0 = addiu(sp, 0xA0);
                            a1 = 0;
                            jal(ctx, 0x1CC180u, gen::fn_H_Cdvd_Request_00100d80);
                        } else {
                            // 0x001cc16c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                    }
                } else {
                    // 0x001cc120
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x001cc194
                charge(ctx, 53);
                sw(v0, s3, 108);
                jal(ctx, 0x1CC198u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC1A4u, gen::fn_K_Field_GetMajorId_001bab20);
                a0 = v0;
                jal(ctx, 0x1CC1B0u, gen::fn_sub_1E7200_001e7200);
                sw(v0, s3, 112);
                jal(ctx, 0x1CC1BCu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kFlags);
                v1 = lui(0x8000);
                v1 = a0 | v1;
                sw(v1, v0, f4::fld::kFlags);
                jal(ctx, 0x1CC1D4u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC1E0u, gen::fn_K_Field_GetMajorId_001bab20);
                s0 = v0 & 0xFFFF;
                jal(ctx, 0x1CC1ECu, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC1F8u, gen::fn_K_Field_GetMinorId_001bab30);
                a1 = v0 & 0xFFFF;
                a0 = s0;
                jal(ctx, 0x1CC208u, gen::fn_MT_Scene_Load_003b5760);
                jal(ctx, 0x1CC210u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC21Cu, gen::fn_sub_1BAB40_001bab40);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1CC22Cu, gen::fn_sub_3B58C0_003b58c0);
                jal(ctx, 0x1CC234u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC240u, gen::fn_sub_1BAB50_001bab50);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1CC250u, gen::fn_sub_3B5980_003b5980);
                v0 = 17;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CC268u:  // table[17]  -- state 17: all reloaded -> 18
            // 0x001cc268
            charge(ctx, 5);
            lw(a0, s3, 108);
            jal(ctx, 0x1CC26Cu, gen::fn_sub_1C7F20_001c7f20);
            if (v0 != 0) {
                // 0x001cc27c
                charge(ctx, 12);
                sw(zero, s3, 108);
                jal(ctx, 0x1CC280u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kRoot);
                jal(ctx, 0x1CC28Cu, gen::fn_K_Field_GetMajorId_001bab20);
                lw(a0, s3, 112);
                a1 = v0;
                jal(ctx, 0x1CC29Cu, gen::fn_sub_1E7290_001e7290);
                if (v0 != 0) {
                    // 0x001cc2ac
                    charge(ctx, 5);
                    sw(zero, s3, 112);
                    jal(ctx, 0x1CC2B0u, gen::fn_sub_1C0440_001c0440);
                    if (v0 != 0) {
                        // 0x001cc2c0
                        charge(ctx, 4);
                        jal(ctx, 0x1CC2C0u, gen::fn_sub_1C0740_001c0740);
                        if (v0 != 0) {
                            // 0x001cc2d0
                            charge(ctx, 4);
                            jal(ctx, 0x1CC2D0u, gen::fn_sub_1D12D0_001d12d0);
                            if (v0 != 0) {
                                // 0x001cc2e0
                                charge(ctx, 4);
                                jal(ctx, 0x1CC2E0u, gen::fn_sub_3B5A10_003b5a10);
                                if (v0 != 0) {
                                    // 0x001cc2f0
                                    charge(ctx, 5);
                                    jal(ctx, 0x1CC2F0u, gen::fn_sub_1DD600_001dd600);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x001cc304
                                        charge(ctx, 7);
                                        a0 = s2;
                                        jal(ctx, 0x1CC308u, gen::fn_sub_18BFF0_0018bff0);
                                        s0 = v0;
                                        jal(ctx, 0x1CC314u, gen::fn_K_Field_Get_001b9120);
                                        sw(s0, v0, f4::fld::kPartyPanel);
                                    }
                                    // 0x001cc320
                                    charge(ctx, 4);
                                    v0 = 18;
                                    sw(v0, s3, f4::evt::kState);
                                }
                            }
                        }
                    }
                }
            }
            goto L_001cd48c;
        case 0x1CC330u:  // table[18]  -- state 18: camera, walls, mini-map, pad recreated -> 19
            // 0x001cc330
            charge(ctx, 5);
            jal(ctx, 0x1CC330u, gen::fn_sub_1DD600_001dd600);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cc344
                charge(ctx, 7);
                jal(ctx, 0x1CC344u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kPartyPanel);
                jal(ctx, 0x1CC350u, gen::fn_sub_18C0A0_0018c0a0);
                if (v0 != 0) {
                    goto L_001cc360;
                }
                goto L_001cd48c;
            }
        L_001cc360:
            charge(ctx, 14);
            a0 = si(-1);
            jal(ctx, 0x1CC364u, gen::fn_sub_453470_00453470);
            a0 = addiu(s3, 40);
            jal(ctx, 0x1CC370u, gen::fn_sub_1C8120_001c8120);
            a0 = 1;
            jal(ctx, 0x1CC37Cu, gen::fn_sub_1D0E50_001d0e50);
            jal(ctx, 0x1CC384u, gen::fn_sub_1DD600_001dd600);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cc398
                charge(ctx, 2);
                jal(ctx, 0x1CC398u, gen::fn_sub_1DD8E0_001dd8e0);
            }
            // 0x001cc3a0
            charge(ctx, 8);
            jal(ctx, 0x1CC3A0u, gen::fn_sub_1D1360_001d1360);
            a0 = 5137;
            jal(ctx, 0x1CC3ACu, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cc3c0
                charge(ctx, 10);
                jal(ctx, 0x1CC3C0u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kEnemySched);
                a1 = 2;
                jal(ctx, 0x1CC3D0u, gen::fn_sub_1D38D0_001d38d0);
                a0 = 5137;
                a1 = 0;
                jal(ctx, 0x1CC3E0u, gen::fn_datSetFlag_0016f1f0);
            }
            // 0x001cc3e8
            charge(ctx, 3);
            lw(v0, s3, f4::evt::kTarget);
            if (v0 != 0) {
                // 0x001cc3f4
                charge(ctx, 5);
                lw(a0, s3, 60);
                jal(ctx, 0x1CC3F8u, gen::fn_datUnitIsGenusDead_002ff790);
                if (v0 == 0) {
                    // 0x001cc408
                    charge(ctx, 5);
                    jal(ctx, 0x1CC408u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kEnemySched);
                    jal(ctx, 0x1CC414u, gen::fn_sub_1D39C0_001d39c0);
                }
                // 0x001cc41c
                charge(ctx, 3);
                lw(a0, s3, f4::evt::kTarget);
                jal(ctx, 0x1CC420u, gen::fn_sub_1D0110_001d0110);
            }
            // 0x001cc428
            charge(ctx, 30);
            jal(ctx, 0x1CC428u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kEnemySched);
            a1 = 0;
            jal(ctx, 0x1CC438u, gen::fn_sub_1D37F0_001d37f0);
            a0 = 0;
            jal(ctx, 0x1CC444u, gen::fn_sub_4532D0_004532d0);
            a0 = 0;
            a1 = 0;
            jal(ctx, 0x1CC454u, gen::fn_sub_4350E0_004350e0);
            jal(ctx, 0x1CC45Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kFootstep);
            a1 = 0;
            jal(ctx, 0x1CC46Cu, gen::fn_sub_1DA000_001da000);
            jal(ctx, 0x1CC474u, gen::fn_sub_1D2610_001d2610);
            jal(ctx, 0x1CC47Cu, gen::fn_sub_1D2210_001d2210);
            jal(ctx, 0x1CC484u, gen::fn_sub_1D2A10_001d2a10);
            jal(ctx, 0x1CC48Cu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kAreaPanel);
            if (v0 != 0) {
                // 0x001cc4a0
                charge(ctx, 6);
                jal(ctx, 0x1CC4A0u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kAreaPanel);
                a1 = 1;
                jal(ctx, 0x1CC4B0u, gen::fn_sub_18EB30_0018eb30);
            }
            // 0x001cc4b8
            charge(ctx, 28);
            jal(ctx, 0x1CC4B8u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kRoot);
            jal(ctx, 0x1CC4C4u, gen::fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90);
            s0 = v0;
            jal(ctx, 0x1CC4D0u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kCamera);
            jal(ctx, 0x1CC4DCu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kCamera);
            a1 = addiu(s3, 128);
            jal(ctx, 0x1CC4ECu, gen::fn_sub_1D69E0_001d69e0);
            jal(ctx, 0x1CC4F4u, gen::fn_K_Field_Get_001b9120);
            v1 = 0x870000;
            lw(v1, v1, 6132);  // 0x8717F4
            lw(a0, v0, f4::fld::kCamera);
            lhu(a1, v1, 0);
            jal(ctx, 0x1CC50Cu, gen::fn_sub_1D5F30_001d5f30);
            jal(ctx, 0x1CC514u, gen::fn_sub_1A01C0_001a01c0);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cc528
                charge(ctx, 9);
                ld(a1, gp, -27200);  // 0x7CC2B0
                sd(a1, sp, 0x2A8);
                a0 = s2;
                jal(ctx, 0x1CC534u, gen::fn_Y_SMap_CreateSmapDrawTask_00429d40);
                s0 = v0;
                jal(ctx, 0x1CC540u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kSmap);
            }
            // 0x001cc54c
            charge(ctx, 16);
            a0 = s2;
            a1 = 2;
            a2 = 0;
            a3 = a1;
            t0 = 490;
            t1 = 1;
            jal(ctx, 0x1CC564u, gen::fn_sub_10A770_0010a770);
            s0 = v0;
            jal(ctx, 0x1CC570u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, 4180);
            v0 = 19;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CC58Cu:  // table[19]  -- state 19: the fade in -> 20
            // 0x001cc58c
            charge(ctx, 5);
            jal(ctx, 0x1CC58Cu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kSmap);
            if (v0 != 0) {
                // 0x001cc5a0
                charge(ctx, 4);
                jal(ctx, 0x1CC5A0u, gen::fn_sub_42BA30_0042ba30);
                if (v0 != 0) {
                    goto L_001cc5b0;
                }
                goto L_001cd48c;
            }
        L_001cc5b0:
            charge(ctx, 5);
            jal(ctx, 0x1CC5B0u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, 4180);
            if (v0 != 0) {
                // 0x001cc5c4
                charge(ctx, 7);
                jal(ctx, 0x1CC5C4u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, 4180);
                jal(ctx, 0x1CC5D0u, gen::fn_sub_10A720_0010a720);
                if (v0 != 0) {
                    // 0x001cc5e0
                    charge(ctx, 3);
                    jal(ctx, 0x1CC5E0u, gen::fn_K_Field_Get_001b9120);
                    sw(zero, v0, 4180);
                    goto L_001cc5ec;
                }
                goto L_001cd48c;
            }
        L_001cc5ec:
            charge(ctx, 13);
            jal(ctx, 0x1CC5ECu, gen::fn_K_Field_Get_001b9120);
            v1 = 0x870000;
            lw(v1, v1, 6132);  // 0x8717F4
            lw(a0, v0, f4::fld::kCamera);
            lhu(a1, v1, 0);
            jal(ctx, 0x1CC604u, gen::fn_sub_1D5F30_001d5f30);
            jal(ctx, 0x1CC60Cu, gen::fn_sub_1A01C0_001a01c0);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cc620
                charge(ctx, 5);
                jal(ctx, 0x1CC620u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, 20);
                if (v0 == 0) {
                    // 0x001cc634
                    charge(ctx, 6);
                    jal(ctx, 0x1CC634u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kSmap);
                    a1 = 1;
                    jal(ctx, 0x1CC644u, gen::fn_sub_429E80_00429e80);
                }
            }
            // 0x001cc64c
            charge(ctx, 37);
            jal(ctx, 0x1CC64Cu, gen::fn_K_Field_Get_001b9120);
            v1 = 0x870000;
            lw(v1, v1, 6132);  // 0x8717F4
            lw(a0, v0, f4::fld::kRoot);
            lw(a1, v1, 480);
            v0 = 0x870000;
            lw(a2, v0, 6128);  // 0x8717F0
            jal(ctx, 0x1CC66Cu, gen::fn_sub_1E1230_001e1230);
            s0 = v0;
            jal(ctx, 0x1CC678u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kVirtualPad);
            jal(ctx, 0x1CC684u, gen::fn_K_Field_Get_001b9120);
            v1 = 0x870000;
            lw(v1, v1, 6132);  // 0x8717F4
            lw(a0, v0, f4::fld::kRoot);
            lw(a1, v1, 480);
            jal(ctx, 0x1CC69Cu, gen::fn_sub_1C1F30_001c1f30);
            s0 = v0;
            jal(ctx, 0x1CC6A8u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kWalls);
            a0 = 1024;
            jal(ctx, 0x1CC6B8u, gen::fn_sub_3B5D10_003b5d10);
            sw(v0, s3, f4::evt::kHero);
            jal(ctx, 0x1CC6C4u, gen::fn_sub_1A9850_001a9850);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = 31;
            if (v1 == v0) {
                // 0x001cc6e0
                charge(ctx, 5);
                a0 = 3641;
                jal(ctx, 0x1CC6E4u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x001cc710
                    charge(ctx, 5);
                    a0 = 0;
                    a1 = 720;
                    a2 = 3;
                    jal(ctx, 0x1CC71Cu, gen::fn_sub_3952D0_003952d0);
                } else {
                    // 0x001cc6f4
                    charge(ctx, 7);
                    a0 = 0;
                    a1 = 719;
                    a2 = 3;
                    jal(ctx, 0x1CC700u, gen::fn_sub_3952D0_003952d0);
                }
            }
            // 0x001cc724
            charge(ctx, 11);
            jal(ctx, 0x1CC724u, gen::fn_sub_1C0110_001c0110);
            a0 = 1;
            jal(ctx, 0x1CC730u, gen::fn_sub_4533E0_004533e0);
            jal(ctx, 0x1CC738u, gen::fn_sub_1085C0_001085c0);
            v0 = 20;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CC750u:  // table[20]  -- state 20: the party panel -> 1
            // 0x001cc750
            charge(ctx, 4);
            jal(ctx, 0x1CC750u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x001cc760
                charge(ctx, 6);
                v0 = 150;
                sw(v0, s3, f4::evt::kCountdown);
                v0 = 1;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CC778u:  // table[21]  -- state 21: the NPC message closed -> 1
            // 0x001cc778
            charge(ctx, 7);
            jal(ctx, 0x1CC778u, gen::fn_sub_3C7B90_003c7b90);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = 7;
            if (v1 != v0) {
                // 0x001cc794
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    goto L_001cc7a0;
                }
            L_001cc7d8:
                charge(ctx, 6);
                lw(v0, s3, f4::evt::kNpc);
                lw(a0, v0, 296);
                lbu(v1, a0, 238);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001cc7f0
                    charge(ctx, 8);
                    lw(s0, s3, f4::evt::kNpcPose);
                    a1 = 0;
                    jal(ctx, 0x1CC7F8u, gen::fn_sub_318540_00318540);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (s0 != v0) {
                        // 0x001cc810
                        charge(ctx, 20);
                        lw(v0, s3, f4::evt::kNpc);
                        a2 = dsll32(s0, 16);
                        a2 = dsra32(a2, 16);
                        lw(a0, v0, 296);
                        a1 = 0;
                        a3 = 7;
                        t0 = 1;
                        jal(ctx, 0x1CC82Cu, gen::fn_sub_3182D0_003182d0);
                        lw(v0, s3, f4::evt::kNpc);
                        lw(a0, v0, 296);
                        a1 = 0;
                        jal(ctx, 0x1CC840u, gen::fn_sub_318540_00318540);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = 0x680000;
                        a0 = addiu(a0, 14160);  // "---->%d\n"
                        jal(ctx, 0x1CC858u, gen::fn_printf_005225a8);
                    }
                }
                goto L_001cc860;
            }
        L_001cc7a0:
            charge(ctx, 3);
            v0 = 7;
            if (v1 == v0) {
                // 0x001cc7ac
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpcPose);
                v0 = sltiu(v0, 4);
                if (v0 != 0) {
                    goto L_001cc7d8;
                }
                goto L_001cc7bc;
            }
        L_001cc7bc:
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x001cc7c8
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpcPose);
                at = sltiu(v0, 4);
                if (at != 0) {
                    goto L_001cc7d8;
                }
            }
        L_001cc860:
            charge(ctx, 4);
            jal(ctx, 0x1CC860u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x001cc870
                charge(ctx, 9);
                jal(ctx, 0x1CC870u, gen::fn_sub_3C7700_003c7700);
                jal(ctx, 0x1CC878u, gen::fn_sub_3C77A0_003c77a0);
                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(v1, v0, f4::scene::kMajor);
                v0 = 7;
                if (v1 != v0) {
                    // 0x001cc894
                    charge(ctx, 3);
                    v0 = 4;
                    if (v1 == v0) {
                        goto L_001cc8a0;
                    }
                L_001cc8d8:
                    charge(ctx, 10);
                    lw(s0, s3, f4::evt::kNpcPose);
                    lw(v0, s3, f4::evt::kNpc);
                    lw(a0, v0, 296);
                    a1 = 0;
                    jal(ctx, 0x1CC8E8u, gen::fn_sub_318540_00318540);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (s0 != v0) {
                        // 0x001cc900
                        charge(ctx, 9);
                        lw(v0, s3, f4::evt::kNpc);
                        a2 = dsll32(s0, 16);
                        a2 = dsra32(a2, 16);
                        lw(a0, v0, 296);
                        a1 = 0;
                        a3 = 16;
                        t0 = 1;
                        jal(ctx, 0x1CC91Cu, gen::fn_sub_3182D0_003182d0);
                    }
                    goto L_001cc924;
                }
            L_001cc8a0:
                charge(ctx, 3);
                v0 = 7;
                if (v1 == v0) {
                    // 0x001cc8ac
                    charge(ctx, 4);
                    lw(v0, s3, f4::evt::kNpcPose);
                    v0 = sltiu(v0, 4);
                    if (v0 != 0) {
                        goto L_001cc8d8;
                    }
                    goto L_001cc8bc;
                }
            L_001cc8bc:
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    // 0x001cc8c8
                    charge(ctx, 4);
                    lw(v0, s3, f4::evt::kNpcPose);
                    at = sltiu(v0, 4);
                    if (at != 0) {
                        goto L_001cc8d8;
                    }
                }
            L_001cc924:
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpc);
                lw(a0, v0, 528);
                if (a0 != 0) {
                    // 0x001cc934
                    charge(ctx, 3);
                    a1 = 1;
                    jal(ctx, 0x1CC938u, gen::fn_sub_1DD5E0_001dd5e0);
                }
                // 0x001cc940
                charge(ctx, 17);
                jal(ctx, 0x1CC940u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kFootstep);
                a1 = 0;
                jal(ctx, 0x1CC950u, gen::fn_sub_1DA000_001da000);
                jal(ctx, 0x1CC958u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kVirtualPad);
                a1 = 0;
                jal(ctx, 0x1CC968u, gen::fn_sub_1E1300_001e1300);
                jal(ctx, 0x1CC970u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kSmap);
                if (v0 != 0) {
                    // 0x001cc984
                    charge(ctx, 6);
                    jal(ctx, 0x1CC984u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kSmap);
                    a1 = 1;
                    jal(ctx, 0x1CC994u, gen::fn_sub_429E80_00429e80);
                }
                // 0x001cc99c
                charge(ctx, 5);
                jal(ctx, 0x1CC99Cu, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kPartyPanel);
                if (v0 != 0) {
                    // 0x001cc9b0
                    charge(ctx, 6);
                    jal(ctx, 0x1CC9B0u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kPartyPanel);
                    a1 = 1;
                    jal(ctx, 0x1CC9C0u, gen::fn_sub_18C0C0_0018c0c0);
                }
                // 0x001cc9c8
                charge(ctx, 5);
                jal(ctx, 0x1CC9C8u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kAreaPanel);
                if (v0 != 0) {
                    // 0x001cc9dc
                    charge(ctx, 6);
                    jal(ctx, 0x1CC9DCu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kAreaPanel);
                    a1 = 1;
                    jal(ctx, 0x1CC9ECu, gen::fn_sub_18EB30_0018eb30);
                }
                // 0x001cc9f4
                charge(ctx, 6);
                v0 = 10;
                sw(v0, s3, f4::evt::kTalkCooldown);
                v0 = 1;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CCA0Cu:  // table[22]  -- state 22: the NPC script done -> 1
            // 0x001cca0c
            charge(ctx, 5);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = 7;
            if (v1 != v0) {
                // 0x001cca20
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    goto L_001cca2c;
                }
            L_001cca64:
                charge(ctx, 6);
                lw(v0, s3, f4::evt::kNpc);
                lw(a0, v0, 296);
                lbu(v1, a0, 238);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001cca7c
                    charge(ctx, 8);
                    lw(s0, s3, f4::evt::kNpcPose);
                    a1 = 0;
                    jal(ctx, 0x1CCA84u, gen::fn_sub_318540_00318540);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (s0 != v0) {
                        // 0x001cca9c
                        charge(ctx, 9);
                        lw(v0, s3, f4::evt::kNpc);
                        a2 = dsll32(s0, 16);
                        a2 = dsra32(a2, 16);
                        lw(a0, v0, 296);
                        a1 = 0;
                        a3 = 7;
                        t0 = 1;
                        jal(ctx, 0x1CCAB8u, gen::fn_sub_3182D0_003182d0);
                    }
                }
                goto L_001ccac0;
            }
        L_001cca2c:
            charge(ctx, 3);
            v0 = 7;
            if (v1 == v0) {
                // 0x001cca38
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpcPose);
                v0 = sltiu(v0, 4);
                if (v0 != 0) {
                    goto L_001cca64;
                }
                goto L_001cca48;
            }
        L_001cca48:
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x001cca54
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpcPose);
                at = sltiu(v0, 4);
                if (at != 0) {
                    goto L_001cca64;
                }
            }
        L_001ccac0:
            charge(ctx, 6);
            lw(a0, s3, f4::evt::kScript);
            jal(ctx, 0x1CCAC4u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001ccad8
                charge(ctx, 5);
                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                lw(v1, v0, f4::scene::kMajor);
                v0 = 7;
                if (v1 != v0) {
                    // 0x001ccaec
                    charge(ctx, 3);
                    v0 = 4;
                    if (v1 == v0) {
                        goto L_001ccaf8;
                    }
                L_001ccb30:
                    charge(ctx, 10);
                    lw(s0, s3, f4::evt::kNpcPose);
                    lw(v0, s3, f4::evt::kNpc);
                    lw(a0, v0, 296);
                    a1 = 0;
                    jal(ctx, 0x1CCB40u, gen::fn_sub_318540_00318540);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (s0 != v0) {
                        // 0x001ccb58
                        charge(ctx, 9);
                        lw(v0, s3, f4::evt::kNpc);
                        a2 = dsll32(s0, 16);
                        a2 = dsra32(a2, 16);
                        lw(a0, v0, 296);
                        a1 = 0;
                        a3 = 16;
                        t0 = 1;
                        jal(ctx, 0x1CCB74u, gen::fn_sub_3182D0_003182d0);
                    }
                    goto L_001ccb7c;
                }
            L_001ccaf8:
                charge(ctx, 3);
                v0 = 7;
                if (v1 == v0) {
                    // 0x001ccb04
                    charge(ctx, 4);
                    lw(v0, s3, f4::evt::kNpcPose);
                    v0 = sltiu(v0, 4);
                    if (v0 != 0) {
                        goto L_001ccb30;
                    }
                    goto L_001ccb14;
                }
            L_001ccb14:
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    // 0x001ccb20
                    charge(ctx, 4);
                    lw(v0, s3, f4::evt::kNpcPose);
                    at = sltiu(v0, 4);
                    if (at != 0) {
                        goto L_001ccb30;
                    }
                }
            L_001ccb7c:
                charge(ctx, 4);
                lw(v0, s3, f4::evt::kNpc);
                lw(a0, v0, 528);
                if (a0 != 0) {
                    // 0x001ccb8c
                    charge(ctx, 3);
                    a1 = 1;
                    jal(ctx, 0x1CCB90u, gen::fn_sub_1DD5E0_001dd5e0);
                }
                // 0x001ccb98
                charge(ctx, 18);
                jal(ctx, 0x1CCB98u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kFootstep);
                a1 = 0;
                jal(ctx, 0x1CCBA8u, gen::fn_sub_1DA000_001da000);
                jal(ctx, 0x1CCBB0u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kVirtualPad);
                a1 = 0;
                jal(ctx, 0x1CCBC0u, gen::fn_sub_1E1300_001e1300);
                sw(zero, s3, f4::evt::kScript);
                jal(ctx, 0x1CCBCCu, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kSmap);
                if (v0 != 0) {
                    // 0x001ccbe0
                    charge(ctx, 6);
                    jal(ctx, 0x1CCBE0u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kSmap);
                    a1 = 1;
                    jal(ctx, 0x1CCBF0u, gen::fn_sub_429E80_00429e80);
                }
                // 0x001ccbf8
                charge(ctx, 5);
                jal(ctx, 0x1CCBF8u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kPartyPanel);
                if (v0 != 0) {
                    // 0x001ccc0c
                    charge(ctx, 6);
                    jal(ctx, 0x1CCC0Cu, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kPartyPanel);
                    a1 = 1;
                    jal(ctx, 0x1CCC1Cu, gen::fn_sub_18C0C0_0018c0c0);
                }
                // 0x001ccc24
                charge(ctx, 5);
                jal(ctx, 0x1CCC24u, gen::fn_K_Field_Get_001b9120);
                lw(v0, v0, f4::fld::kAreaPanel);
                if (v0 != 0) {
                    // 0x001ccc38
                    charge(ctx, 6);
                    jal(ctx, 0x1CCC38u, gen::fn_K_Field_Get_001b9120);
                    lw(a0, v0, f4::fld::kAreaPanel);
                    a1 = 1;
                    jal(ctx, 0x1CCC48u, gen::fn_sub_18EB30_0018eb30);
                }
                // 0x001ccc50
                charge(ctx, 6);
                v0 = 10;
                sw(v0, s3, f4::evt::kTalkCooldown);
                v0 = 1;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CCC68u:  // table[23]  -- state 23: open the camp menu (H_Camp_CreateDrawTask -> +104) -> 24
            // 0x001ccc68
            charge(ctx, 4);
            jal(ctx, 0x1CCC68u, gen::fn_sub_1D1A90_001d1a90);
            if (v0 != 0) {
                // 0x001ccc78
                charge(ctx, 4);
                jal(ctx, 0x1CCC78u, gen::fn_sub_1D1CE0_001d1ce0);
                if (v0 != 0) {
                    // 0x001ccc88
                    charge(ctx, 4);
                    jal(ctx, 0x1CCC88u, gen::fn_sub_1D00B0_001d00b0);
                    if (v0 != 0) {
                        // 0x001ccc98
                        charge(ctx, 48);
                        jal(ctx, 0x1CCC98u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kWalls);
                        a1 = 32;
                        a2 = 2;
                        jal(ctx, 0x1CCCACu, gen::fn_kwlnTaskSetFlags_001956d0);
                        jal(ctx, 0x1CCCB4u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kCamera);
                        a1 = 32;
                        a2 = 2;
                        jal(ctx, 0x1CCCC8u, gen::fn_kwlnTaskSetFlags_001956d0);
                        jal(ctx, 0x1CCCD0u, gen::fn_sub_455B50_00455b50);
                        a0 = 1;
                        jal(ctx, 0x1CCCDCu, gen::fn_sub_1D1780_001d1780);
                        a0 = 0;
                        jal(ctx, 0x1CCCE8u, gen::fn_sub_1D17F0_001d17f0);
                        v0 = 0x870000;
                        lw(v0, v0, 6120);  // 0x8717E8
                        lw(a0, v0, 4);
                        jal(ctx, 0x1CCCFCu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                        v0 = v0 & 0xFF;
                        sw(v0, s3, f4::evt::kWeapon);
                        a0 = 1;
                        a1 = a0;
                        jal(ctx, 0x1CCD14u, gen::fn_datGetEquipmentIdx_0016cb80);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = 1;
                        jal(ctx, 0x1CCD28u, gen::fn_sub_16F630_0016f630);
                        v0 = v0 & 0xFFFF;
                        sw(v0, s3, f4::evt::kWeaponItem);
                        a0 = s2;
                        jal(ctx, 0x1CCD3Cu, gen::fn_H_Camp_CreateDrawTask_0011a770);
                        sw(v0, s3, f4::evt::kCamp);
                        v0 = 24;
                        sw(v0, s3, f4::evt::kState);
                    }
                }
            }
            goto L_001cd48c;
        case 0x1CCD58u:  // table[24]  -- state 24: the camp menu closed: header script procedure 3 -> 28, or reload the hero's model -> 25
            // 0x001ccd58
            charge(ctx, 6);
            lw(a0, s3, f4::evt::kCamp);
            jal(ctx, 0x1CCD5Cu, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001ccd70
                charge(ctx, 6);
                a0 = 5143;
                jal(ctx, 0x1CCD74u, gen::fn_datGetFlag_0016f190);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001ccdc0
                    charge(ctx, 19);
                    v0 = 0x870000;
                    lw(v0, v0, 6120);  // 0x8717E8
                    lw(a0, v0, 4);
                    jal(ctx, 0x1CCDCCu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                    s0 = v0 & 0xFF;
                    a0 = 1;
                    a1 = a0;
                    jal(ctx, 0x1CCDE0u, gen::fn_datGetEquipmentIdx_0016cb80);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    a0 = 1;
                    jal(ctx, 0x1CCDF4u, gen::fn_sub_16F630_0016f630);
                    v0 = v0 & 0xFFFF;
                    lw(v1, s3, f4::evt::kWeapon);
                    if (v1 == s0) {
                        // 0x001cce0c
                        charge(ctx, 3);
                        a0 = 1081;
                        if (v0 == a0) {
                            // 0x001cce18
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce24;
                        }
                    L_001cce24:
                        charge(ctx, 3);
                        a0 = 1081;
                        if (v0 != a0) {
                            // 0x001cce30
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce3c;
                        }
                    L_001cce3c:
                        charge(ctx, 3);
                        a0 = 1106;
                        if (v0 == a0) {
                            // 0x001cce48
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce54;
                        }
                    L_001cce54:
                        charge(ctx, 3);
                        a0 = 1106;
                        if (v0 != a0) {
                            // 0x001cce60
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce6c;
                        }
                    L_001cce6c:
                        charge(ctx, 3);
                        a0 = 1107;
                        if (v0 == a0) {
                            // 0x001cce78
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce84;
                        }
                    L_001cce84:
                        charge(ctx, 3);
                        a0 = 1107;
                        if (v0 != a0) {
                            // 0x001cce90
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cce9c;
                        }
                    L_001cce9c:
                        charge(ctx, 3);
                        a0 = 1038;
                        if (v0 == a0) {
                            // 0x001ccea8
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001cceb4;
                        }
                    L_001cceb4:
                        charge(ctx, 3);
                        a0 = 1038;
                        if (v0 != a0) {
                            // 0x001ccec0
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccecc;
                        }
                    L_001ccecc:
                        charge(ctx, 3);
                        a0 = 1126;
                        if (v0 == a0) {
                            // 0x001cced8
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccee4;
                        }
                    L_001ccee4:
                        charge(ctx, 3);
                        a0 = 1126;
                        if (v0 != a0) {
                            // 0x001ccef0
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccefc;
                        }
                    L_001ccefc:
                        charge(ctx, 3);
                        a0 = 1085;
                        if (v0 == a0) {
                            // 0x001ccf08
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccf14;
                        }
                    L_001ccf14:
                        charge(ctx, 3);
                        a0 = 1085;
                        if (v0 != a0) {
                            // 0x001ccf20
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 == a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccf2c;
                        }
                    L_001ccf2c:
                        charge(ctx, 3);
                        a0 = 1124;
                        if (v0 == a0) {
                            // 0x001ccf38
                            charge(ctx, 3);
                            lw(v1, s3, f4::evt::kWeaponItem);
                            if (v1 != a0) {
                                goto L_001ccf5c;
                            }
                            goto L_001ccf44;
                        }
                    L_001ccf44:
                        charge(ctx, 3);
                        v1 = 1124;
                        if (v0 != v1) {
                            // 0x001ccf50
                            charge(ctx, 3);
                            lw(v0, s3, f4::evt::kWeaponItem);
                            if (v0 != v1) {
                                goto L_001ccf8c;
                            }
                            goto L_001ccf5c;
                        }
                    L_001ccf8c:
                        charge(ctx, 3);
                        s0 = 0;
                        for (;;) {
                            // 0x001ccfb0
                            charge(ctx, 3);
                            v0 = sltiu(s0, 5);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001ccf98
                            charge(ctx, 6);
                            a1 = s0 & 0xFFFF;
                            v0 = 0x870000;
                            lw(a0, v0, 6128);  // 0x8717F0
                            jal(ctx, 0x1CCFA4u, gen::fn_sub_3196F0_003196f0);
                            s0 = addiu(s0, 1);
                        }
                        // 0x001ccfbc
                        charge(ctx, 6);
                        jal(ctx, 0x1CCFBCu, gen::fn_sub_4C43B0_004c43b0);
                        v0 = 0x870000;
                        lw(a0, v0, 6128);  // 0x8717F0
                        jal(ctx, 0x1CCFCCu, gen::fn_sub_31C1D0_0031c1d0);
                        goto L_001ccfd4;
                    }
                L_001ccf5c:
                    charge(ctx, 12);
                    a0 = 0;
                    jal(ctx, 0x1CCF60u, gen::fn_sub_1CD870_001cd870);
                    jal(ctx, 0x1CCF68u, gen::fn_sub_4C43B0_004c43b0);
                    a0 = 1;
                    jal(ctx, 0x1CCF74u, gen::fn_sub_1CD9A0_001cd9a0);
                    v1 = 0x870000;
                    sw(v0, v1, 6128);  // 0x8717F0
                L_001ccfd4:
                    charge(ctx, 4);
                    v0 = 25;
                    sw(v0, s3, f4::evt::kState);
                } else {
                    // 0x001ccd88
                    charge(ctx, 14);
                    a0 = 5143;
                    a1 = 0;
                    jal(ctx, 0x1CCD90u, gen::fn_datSetFlag_0016f1f0);
                    a0 = 10;
                    lw(a1, gp, -19144);  // g_fldMainScriptPtr
                    a2 = 3;
                    jal(ctx, 0x1CCDA4u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                    sw(v0, s3, f4::evt::kScript);
                    v0 = 28;
                    sw(v0, s3, f4::evt::kState);
                }
            }
            goto L_001cd48c;
        case 0x1CCFE4u:  // table[25]  -- state 25: the model ready: panels back -> 26
            // 0x001ccfe4
            charge(ctx, 7);
            s1 = 1;
            v0 = 0x870000;
            lw(a0, v0, 6128);  // 0x8717F0
            jal(ctx, 0x1CCFF0u, gen::fn_sub_316F70_00316f70);
            if (v0 != 0) {
                // 0x001cd000
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x001cd038
                    charge(ctx, 3);
                    v0 = sltiu(s0, 5);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001cd00c
                    charge(ctx, 7);
                    a1 = s0 & 0xFFFF;
                    v0 = 0x870000;
                    lw(a0, v0, 6128);  // 0x8717F0
                    jal(ctx, 0x1CD018u, gen::fn_sub_319770_00319770);
                    if (v0 == 0) {
                        goto L_001cd028_597;
                    }
                    // 0x001cd034
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
            L_001cd044:
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001cd04c
                    charge(ctx, 5);
                    jal(ctx, 0x1CD04Cu, gen::fn_sub_1DD600_001dd600);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001cd060
                        charge(ctx, 7);
                        a0 = s2;
                        jal(ctx, 0x1CD064u, gen::fn_sub_18BFF0_0018bff0);
                        s0 = v0;
                        jal(ctx, 0x1CD070u, gen::fn_K_Field_Get_001b9120);
                        sw(s0, v0, f4::fld::kPartyPanel);
                    }
                    // 0x001cd07c
                    charge(ctx, 5);
                    jal(ctx, 0x1CD07Cu, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kAreaPanel);
                    if (v0 != 0) {
                        // 0x001cd090
                        charge(ctx, 6);
                        jal(ctx, 0x1CD090u, gen::fn_K_Field_Get_001b9120);
                        lw(a0, v0, f4::fld::kAreaPanel);
                        a1 = 1;
                        jal(ctx, 0x1CD0A0u, gen::fn_sub_18EB30_0018eb30);
                    }
                    // 0x001cd0a8
                    charge(ctx, 5);
                    lw(a1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(a0, a1, f4::scene::kMajor);
                    v0 = 32;
                    if (a0 == v0) {
                        // 0x001cd0bc
                        charge(ctx, 4);
                        lw(v1, a1, 4);
                        v0 = 2;
                        if (v1 != v0) {
                            goto L_001cd0cc;
                        }
                    L_001cd104:
                        charge(ctx, 2);
                        jal(ctx, 0x1CD104u, gen::fn_datCalcRestorePartyAll_0030c440);
                        goto L_001cd10c;
                    }
                L_001cd0cc:
                    charge(ctx, 3);
                    v0 = 39;
                    if (a0 == v0) {
                        // 0x001cd0d8
                        charge(ctx, 4);
                        lw(v1, a1, 4);
                        v0 = 1;
                        if (v1 == v0) {
                            goto L_001cd104;
                        }
                        goto L_001cd0e8;
                    }
                L_001cd0e8:
                    charge(ctx, 3);
                    v0 = 39;
                    if (a0 == v0) {
                        // 0x001cd0f4
                        charge(ctx, 4);
                        lw(v1, a1, 4);
                        v0 = 3;
                        if (v1 == v0) {
                            goto L_001cd104;
                        }
                    }
                L_001cd10c:
                    charge(ctx, 4);
                    v0 = 26;
                    sw(v0, s3, f4::evt::kState);
                }
            }
            goto L_001cd48c;
        case 0x1CD11Cu:  // table[26]  -- state 26: party units, enemies, mini-map recreated -> 27
            // 0x001cd11c
            charge(ctx, 5);
            jal(ctx, 0x1CD11Cu, gen::fn_sub_1DD600_001dd600);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cd130
                charge(ctx, 7);
                jal(ctx, 0x1CD130u, gen::fn_K_Field_Get_001b9120);
                lw(a0, v0, f4::fld::kPartyPanel);
                jal(ctx, 0x1CD13Cu, gen::fn_sub_18C0A0_0018c0a0);
                if (v0 != 0) {
                    goto L_001cd14c;
                }
                goto L_001cd48c;
            }
        L_001cd14c:
            charge(ctx, 10);
            a0 = 1;
            jal(ctx, 0x1CD150u, gen::fn_sub_1D0E50_001d0e50);
            jal(ctx, 0x1CD158u, gen::fn_sub_1D19D0_001d19d0);
            jal(ctx, 0x1CD160u, gen::fn_sub_1DD600_001dd600);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cd174
                charge(ctx, 2);
                jal(ctx, 0x1CD174u, gen::fn_sub_1DD8E0_001dd8e0);
            }
            // 0x001cd17c
            charge(ctx, 15);
            jal(ctx, 0x1CD17Cu, gen::fn_sub_1D1360_001d1360);
            jal(ctx, 0x1CD184u, gen::fn_sub_1D1C20_001d1c20);
            jal(ctx, 0x1CD18Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kEnemySched);
            a1 = 0;
            jal(ctx, 0x1CD19Cu, gen::fn_sub_1D37F0_001d37f0);
            jal(ctx, 0x1CD1A4u, gen::fn_sub_1A01C0_001a01c0);
            v1 = 1;
            if (v0 == v1) {
                // 0x001cd1b8
                charge(ctx, 9);
                ld(a1, gp, -27192);  // 0x7CC2B8
                sd(a1, sp, 0x2A0);
                a0 = s2;
                jal(ctx, 0x1CD1C4u, gen::fn_Y_SMap_CreateSmapDrawTask_00429d40);
                s0 = v0;
                jal(ctx, 0x1CD1D0u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kSmap);
            }
            // 0x001cd1dc
            charge(ctx, 4);
            v0 = 27;
            sw(v0, s3, f4::evt::kState);
            goto L_001cd48c;
        case 0x1CD1ECu:  // table[27]  -- state 27: walls, camera, virtual pad back -> 1
            // 0x001cd1ec
            charge(ctx, 4);
            jal(ctx, 0x1CD1ECu, gen::fn_sub_1CE960_001ce960);
            if (v0 != 0) {
                // 0x001cd1fc
                charge(ctx, 4);
                jal(ctx, 0x1CD1FCu, gen::fn_sub_1D00B0_001d00b0);
                if (v0 != 0) {
                    // 0x001cd20c
                    charge(ctx, 4);
                    jal(ctx, 0x1CD20Cu, gen::fn_sub_1D1A90_001d1a90);
                    if (v0 != 0) {
                        // 0x001cd21c
                        charge(ctx, 4);
                        jal(ctx, 0x1CD21Cu, gen::fn_sub_1D1CE0_001d1ce0);
                        if (v0 != 0) {
                            // 0x001cd22c
                            charge(ctx, 5);
                            jal(ctx, 0x1CD22Cu, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kSmap);
                            if (v0 != 0) {
                                // 0x001cd240
                                charge(ctx, 4);
                                jal(ctx, 0x1CD240u, gen::fn_sub_42BA30_0042ba30);
                                if (v0 != 0) {
                                    goto L_001cd250;
                                }
                                goto L_001cd48c;
                            }
                        L_001cd250:
                            charge(ctx, 42);
                            a0 = 1024;
                            jal(ctx, 0x1CD254u, gen::fn_sub_3B5D10_003b5d10);
                            sw(v0, s3, f4::evt::kHero);
                            jal(ctx, 0x1CD260u, gen::fn_K_Field_Get_001b9120);
                            v1 = 0x870000;
                            lw(v1, v1, 6132);  // 0x8717F4
                            lw(a0, v0, f4::fld::kWalls);
                            lw(a1, v1, 480);
                            jal(ctx, 0x1CD278u, gen::fn_sub_1C2000_001c2000);
                            jal(ctx, 0x1CD280u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kWalls);
                            a1 = 32;
                            a2 = 2;
                            jal(ctx, 0x1CD294u, gen::fn_kwlnTaskClearFlags_00195710);
                            jal(ctx, 0x1CD29Cu, gen::fn_K_Field_Get_001b9120);
                            v1 = 0x870000;
                            lw(v1, v1, 6132);  // 0x8717F4
                            lw(a0, v0, f4::fld::kCamera);
                            lhu(a1, v1, 0);
                            jal(ctx, 0x1CD2B4u, gen::fn_sub_1D5F30_001d5f30);
                            jal(ctx, 0x1CD2BCu, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kCamera);
                            a1 = 32;
                            a2 = 2;
                            jal(ctx, 0x1CD2D0u, gen::fn_kwlnTaskClearFlags_00195710);
                            a0 = 0;
                            jal(ctx, 0x1CD2DCu, gen::fn_sub_1D1860_001d1860);
                            jal(ctx, 0x1CD2E4u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kSmap);
                            if (v0 != 0) {
                                // 0x001cd2f8
                                charge(ctx, 5);
                                jal(ctx, 0x1CD2F8u, gen::fn_K_Field_Get_001b9120);
                                lw(v0, v0, 20);
                                if (v0 == 0) {
                                    // 0x001cd30c
                                    charge(ctx, 6);
                                    jal(ctx, 0x1CD30Cu, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kSmap);
                                    a1 = 1;
                                    jal(ctx, 0x1CD31Cu, gen::fn_sub_429E80_00429e80);
                                }
                            }
                            // 0x001cd324
                            charge(ctx, 43);
                            a0 = 0;
                            jal(ctx, 0x1CD328u, gen::fn_sub_45A430_0045a430);
                            a0 = 0;
                            jal(ctx, 0x1CD334u, gen::fn_sub_45AF70_0045af70);
                            jal(ctx, 0x1CD33Cu, gen::fn_K_Field_Get_001b9120);
                            v1 = 0x870000;
                            lw(v1, v1, 6132);  // 0x8717F4
                            lw(a0, v0, f4::fld::kRoot);
                            lw(a1, v1, 480);
                            v0 = 0x870000;
                            lw(a2, v0, 6128);  // 0x8717F0
                            jal(ctx, 0x1CD35Cu, gen::fn_sub_1E1230_001e1230);
                            s0 = v0;
                            jal(ctx, 0x1CD368u, gen::fn_K_Field_Get_001b9120);
                            sw(s0, v0, f4::fld::kVirtualPad);
                            jal(ctx, 0x1CD374u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kEventTask);
                            a1 = 0;
                            jal(ctx, 0x1CD384u, gen::fn_sub_1CD650_001cd650);
                            a0 = 0;
                            jal(ctx, 0x1CD390u, gen::fn_sub_4532D0_004532d0);
                            a0 = 0;
                            a1 = 0;
                            jal(ctx, 0x1CD3A0u, gen::fn_sub_4350E0_004350e0);
                            jal(ctx, 0x1CD3A8u, gen::fn_K_Field_Get_001b9120);
                            lw(a0, v0, f4::fld::kFootstep);
                            a1 = 0;
                            jal(ctx, 0x1CD3B8u, gen::fn_sub_1DA000_001da000);
                            v0 = 1;
                            sw(v0, s3, f4::evt::kState);
                        }
                    }
                }
            }
            goto L_001cd48c;
        case 0x1CD3D0u:  // table[28]  -- state 28: wait for the camp's script
            // 0x001cd3d0
            charge(ctx, 5);
            lw(a0, s3, f4::evt::kScript);
            jal(ctx, 0x1CD3D4u, gen::fn_kwlnTaskExists_00195460);
            goto L_001cd48c;
        case 0x1CD3E4u:  // table[29]  -- state 29: game over: the field script procedure 1 -> 31
            // 0x001cd3e4
            charge(ctx, 4);
            jal(ctx, 0x1CD3E4u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x001cd3f4
                charge(ctx, 13);
                jal(ctx, 0x1CD3F4u, gen::fn_sub_45A400_0045a400);
                lw(a2, gp, -19148);  // g_fldMainScriptSize
                a0 = 10;
                lw(a1, gp, -19144);  // g_fldMainScriptPtr
                a3 = 1;
                jal(ctx, 0x1CD40Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                sw(v0, s3, f4::evt::kScript);
                v0 = 31;
                sw(v0, s3, f4::evt::kState);
            }
            goto L_001cd48c;
        case 0x1CD428u:  // table[30]  -- state 30: fade out: the field script procedure 1 -> 31
            // 0x001cd428
            charge(ctx, 4);
            lw(v0, gp, -19060);  // 0x7CE27C
            at = slti(v0, 90);
            if (at == 0) {
                // 0x001cd454
                charge(ctx, 11);
                lw(a2, gp, -19148);  // g_fldMainScriptSize
                a0 = 10;
                lw(a1, gp, -19144);  // g_fldMainScriptPtr
                a3 = 1;
                jal(ctx, 0x1CD464u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                sw(v0, s3, f4::evt::kScript);
                v0 = 31;
                sw(v0, s3, f4::evt::kState);
            } else {
                // 0x001cd438
                charge(ctx, 7);
                jal(ctx, 0x1CD438u, gen::fn_sub_45A400_0045a400);
                lw(v0, gp, -19060);  // 0x7CE27C
                v0 = addiu(v0, 1);
                sw(v0, gp, -19060);  // 0x7CE27C
            }
            goto L_001cd48c;
        case 0x1CD480u:  // table[32]  -- state 32: a door: wait for the root to change the field
            // 0x001cd480
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x1CD48Cu:  // table[31]  -- state 31: only the shared tail (the end script runs as its own task)
            goto L_001cd48c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001cd534 (the shared epilogue, written out on this path)
        charge(ctx, 13);
        ld(ra, sp, 0x90);
        lq(s7, sp, 0x80);
        lq(s6, sp, 0x70);
        lq(s5, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x360);
        return;
    }
    goto L_001cd48c;
L_001c9380_97:
    charge(ctx, 8);
    v0 = 0x870000;
    v0 = addiu(v0, -20000);  // &0x86B1E0
    v0 = addu(v0, s2);
    v0 = addu(s1, v0);
    v0 = addu(s6, v0);
    lw(v1, v0, 0);
    goto L_001c93bc;
L_001cd028_597:
    charge(ctx, 3);
    s1 = 0;
    goto L_001cd044;
}

}  // namespace p3fes::game
