// The big battle state bodies (game/include/p3fes/game/battle_actions.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md sections 1.2-1.3). Phase 5 slice `battle_actions`: these replace the recompiled bodies
// listed in game/replaced.txt; tests/game/test_battle_actions.cpp runs each against its __recomp body.
//
// Virtual time (ADR-0013): every enter / charge below is one `ctx.cycles += N` block of the recompiled body on the
// executed path, charged where the block starts (before its calls); backedge() sits where the recompiled body checks
// before a backward jump (the test-first loops check before every iteration, the first one included).
//
// Registers: register-faithful by construction. Each body runs on a Cpu view of the guest context: one variable per
// GPR (64-bit writes keep bits 64..127 as the EE does; LQ writes all 128), the loads and stores through the runtime's
// own instructions (so a wild pointer faults, and a hardware window is served, exactly as in the recompiled body), the
// prologue spills and epilogue reloads on the guest stack, and every callee through its generated entry point with
// $ra = the original link (the value the generated body hands rt::jal). A scratch register the original writes holds
// the original's value at every call, check point and return; one it leaves alone keeps what the caller or the last
// callee left there. Structure offsets are named in battle_actions.h / battle_task.h.
//
// The packet idiom. Most states queue animation / camera / sound / message packets for the btlUnit drivers: a creator
// returns a packet (sub_2A3B40 message, sub_2DB740 sound, sub_2838D0 / sub_284200 motion, sub_2E2BE0 camera, ...),
// the state stamps it with its own state number (+72) and the acting btlAction's uid (+96), and sub_27ED20(packet, q)
// appends it to queue q of gBtl+372. The btlMain states then wait until sub_27E410 counts no queued packet.
#include "p3fes/game/battle_actions.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include <cstddef>

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_datUnitIsGenusReady_002ff320(p3fes::EEContext&);  // battle_data
void fn_sub_1FEC50_001fec50(p3fes::EEContext&);           // battle panel
void fn_sub_27E410_0027e410(p3fes::EEContext&);           // queued packets (battle_task)
void fn_sub_1FEEC0_001feec0(p3fes::EEContext&);           // battle panel busy
void fn_sub_2DB740_002db740(p3fes::EEContext&);           // a sound packet
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);           // queue a packet (packet, queue)
void fn_sub_287490_00287490(p3fes::EEContext&);           // btlUnit: show
void fn_sub_287510_00287510(p3fes::EEContext&);           // btlUnit: hide
void fn_sub_2FAAB0_002faab0(p3fes::EEContext&);           // the battle start hook
void fn_sub_27E390_0027e390(p3fes::EEContext&);           // btlPacketFindFirstByActionUID (battle_data)
void fn_sub_170760_00170760(p3fes::EEContext&);           // inventory count (character, item)
void fn_sub_170860_00170860(p3fes::EEContext&);           // inventory set (character, item, count)
void fn_sub_2BFC50_002bfc50(p3fes::EEContext&);
void fn_sub_29B040_0029b040(p3fes::EEContext&);           // battle_task
void fn_sub_2FD7C0_002fd7c0(p3fes::EEContext&);
void fn_sub_1FF370_001ff370(p3fes::EEContext&);           // battle panel
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);           // a message packet (action, message)
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);           // the first actor of the turn order (battle_task)
void fn_sub_29AD50_0029ad50(p3fes::EEContext&);           // battle_task
void fn_sub_2838D0_002838d0(p3fes::EEContext&);           // a motion packet (unit, motion; $f12 speed)
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);        // (DatUnit, delta) (battle)
void fn_sub_286320_00286320(p3fes::EEContext&);           // a pose packet (unit)
void fn_sub_2E2BE0_002e2be0(p3fes::EEContext&);           // a camera packet
void fn_sub_284200_00284200(p3fes::EEContext&);           // a motion packet (unit, motion, a2, a3; $f12 speed)
void fn_sub_285690_00285690(p3fes::EEContext&);           // a model-load packet (unit, id, 62)
void fn_sub_2BB2F0_002bb2f0(p3fes::EEContext&);           // an entry-camera packet
void fn_sub_285D30_00285d30(p3fes::EEContext&);           // an appear-motion packet
void fn_sub_2BC680_002bc680(p3fes::EEContext&);           // a battle-start packet
void fn_sub_2BFC00_002bfc00(p3fes::EEContext&);           // a battle-start packet
void fn_datGetFlag_0016f190(p3fes::EEContext&);           // (flag) (menu_ui)
void fn_sub_2DBFE0_002dbfe0(p3fes::EEContext&);           // the battle music packet
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);      // (DatUnit, skill) (battle_data)
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);      // battle_data
void fn_datCalcSetHp_002ffd90(p3fes::EEContext&);         // battle
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);      // battle_data
void fn_datCalcSetSp_002ffdc0(p3fes::EEContext&);         // battle
void fn_datCalcAddHp_00300410(p3fes::EEContext&);         // battle_data
void fn_datCalcAddSp_00300480(p3fes::EEContext&);         // battle_data
void fn_sub_2A4C50_002a4c50(p3fes::EEContext&);
void fn_sub_2BF650_002bf650(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);           // (flag, on) (ui2)
void fn_datCalcClearAllEffects_00301690(p3fes::EEContext&);  // battle_data
void fn_datGetUnit_0016cd60(p3fes::EEContext&);           // party record (id) (battle_data)
void fn_btlActionSetState_00299d60(p3fes::EEContext&);    // (action, state) (battle_data)
void fn_sub_27E4D0_0027e4d0(p3fes::EEContext&);           // battle_task
void fn_sub_28A780_0028a780(p3fes::EEContext&);           // (action)
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);           // btlUnit position -> a 16-byte vector (battle_task)
void fn_sub_2822B0_002822b0(p3fes::EEContext&);           // a "move to" packet (unit, vector, kind)
void fn_sub_281270_00281270(p3fes::EEContext&);           // btlUnit: still moving
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);           // a camera packet (kind, id)
void fn_sub_2886E0_002886e0(p3fes::EEContext&);           // a panel packet (0, unit, 2)
void fn_sub_288950_00288950(p3fes::EEContext&);           // a panel packet (unit, kind)
void fn_sub_2D15A0_002d15a0(p3fes::EEContext&);           // btlTarget reset (target record)
void fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0(p3fes::EEContext&);           // (action)
void fn_sub_2899E0_002899e0(p3fes::EEContext&);           // (action)
void fn_sub_289B50_00289b50(p3fes::EEContext&);           // the command menu step (action)
void fn_sub_1FEF50_001fef50(p3fes::EEContext&);           // battle panel step
void fn_sub_2BED10_002bed10(p3fes::EEContext&);           // the refused command's end
void fn_sub_1FE220_001fe220(p3fes::EEContext&);           // help allowed
void fn_sub_1FE120_001fe120(p3fes::EEContext&);           // help on
void fn_sub_1FE1A0_001fe1a0(p3fes::EEContext&);           // help off
void fn_sub_2BECC0_002becc0(p3fes::EEContext&);           // the command menu's result
void fn_sub_2D19B0_002d19b0(p3fes::EEContext&);
void fn_sub_1FEF70_001fef70(p3fes::EEContext&);           // panel close
void fn_sub_1FEA70_001fea70(p3fes::EEContext&);           // panel close
void fn_btlSupportClearFlag_002db420(p3fes::EEContext&);           // (2)
void fn_sub_2E4430_002e4430(p3fes::EEContext&);           // (action, skill, kind)
void fn_sub_2E4720_002e4720(p3fes::EEContext&);           // a command refused? (code)
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);           // a system sound (0, 15, 0, 8)
void fn_sub_2BCCD0_002bccd0(p3fes::EEContext&);           // the unit's refusal (unit, code)
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext&);           // candidates: a side (action, record, a2, a3, t0)
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);           // candidates: by skill (action, record, skill, 0)
void fn_sub_2C0970_002c0970(p3fes::EEContext&);           // (record)
void fn_sub_1FE7F0_001fe7f0(p3fes::EEContext&);           // cursor on (panel slot)
void fn_sub_2C0AC0_002c0ac0(p3fes::EEContext&);           // the first candidate (action, record)
void fn_sub_2C0880_002c0880(p3fes::EEContext&);           // the current candidate (record)
void fn_sub_1FE810_001fe810(p3fes::EEContext&);           // (skill / item)
void fn_sub_2C0070_002c0070(p3fes::EEContext&);           // the cursor step (action, record)
void fn_sub_2C08A0_002c08a0(p3fes::EEContext&);           // (record, candidate)
void fn_sub_1FE990_001fe990(p3fes::EEContext&);           // the cursor's slot
void fn_sub_1FE970_001fe970(p3fes::EEContext&);           // cursor to (slot)
void fn_sub_1FE920_001fe920(p3fes::EEContext&);
void fn_sub_2E4520_002e4520(p3fes::EEContext&);           // (action, skill, kind)
void fn_sub_1FE8D0_001fe8d0(p3fes::EEContext&);
void fn_sub_2BEDD0_002bedd0(p3fes::EEContext&);           // (target)
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);           // a camera set (0)
void fn_sub_2BB6F0_002bb6f0(p3fes::EEContext&);           // an effect's camera data (effect, buffer)
void fn_sub_2BAC00_002bac00(p3fes::EEContext&);           // a camera packet (set, data, 0)
void fn_sub_2DD4A0_002dd4a0(p3fes::EEContext&);           // an effect packet (effect, 0)
void fn_sub_29EA60_0029ea60(p3fes::EEContext&);           // (effect, out, out)
void fn_sub_29F4B0_0029f4b0(p3fes::EEContext&);           // a screen-effect packet
void fn_sub_29EC00_0029ec00(p3fes::EEContext&);           // (effect)
void fn_sub_29EC80_0029ec80(p3fes::EEContext&);           // (effect, out, out)
void fn_sub_2A0050_002a0050(p3fes::EEContext&);           // a screen-effect packet
void fn_sub_29EC50_0029ec50(p3fes::EEContext&);           // (effect)
void fn_sub_2A1280_002a1280(p3fes::EEContext&);           // a screen-effect packet
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);           // a unit camera packet (set, unit, unit, a3, t0)
void fn_sub_2DD5E0_002dd5e0(p3fes::EEContext&);           // a sound packet (kind)
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);           // the btlAction of a unit (battle_data)
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);           // result record reset (record)
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);         // battle
void fn_datCalcGetSp_002ffd80(p3fes::EEContext&);         // battle
void fn_sub_2BD480_002bd480(p3fes::EEContext&);           // a revive packet (unit)
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);           // the result-number packet (action, action, record, 1, 1)
void fn_sub_2BD230_002bd230(p3fes::EEContext&);           // a unit packet (unit, 0, 0)
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext&);           // a unit status packet (8 arguments)
void fn_sub_29FA50_0029fa50(p3fes::EEContext&);           // screen-effect end (16)
void fn_sub_2A1080_002a1080(p3fes::EEContext&);           // screen-effect end (16, 0)
void fn_sub_2A16C0_002a16c0(p3fes::EEContext&);           // screen-effect end (16)
void fn_sub_2B9030_002b9030(p3fes::EEContext&);           // camera set release (set)
void fn_sub_16C920_0016c920(p3fes::EEContext&);           // a character's condition (character)
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_16CA90_0016ca90(p3fes::EEContext&);           // (character, -1)
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);          // (n) (battle_data)
void fn_sub_16C9F0_0016c9f0(p3fes::EEContext&);           // (character)
void fn_sub_17B170_0017b170(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);           // set a character's condition (character, condition)
void fn_sub_2BC7E0_002bc7e0(p3fes::EEContext&);           // (8)
void fn_sub_2DD100_002dd100(p3fes::EEContext&);           // an effect packet (14, 2, 9)
void fn_sub_289650_00289650(p3fes::EEContext&);           // btlAction / btlUnit create (side, id, DatUnit record)
void fn_sub_316910_00316910(p3fes::EEContext&);           // a resident model (kind, id, 0)
void fn_sub_3B6000_003b6000(p3fes::EEContext&);           // (character, model)
void fn_sub_1A0590_001a0590(p3fes::EEContext&);           // (id, 1)
void fn_sub_287B20_00287b20(p3fes::EEContext&);           // btlUnit (unit, kind)
void fn_sub_2831C0_002831c0(p3fes::EEContext&);           // btlUnit (unit, 0)
void fn_sub_282D40_00282d40(p3fes::EEContext&);           // btlUnit placement (unit, a1, 0, a3; $f12)
void fn_sub_282BC0_00282bc0(p3fes::EEContext&);           // btlUnit (unit)
void fn_sub_31C7E0_0031c7e0(p3fes::EEContext&);           // (model)
void fn_sub_2B71E0_002b71e0(p3fes::EEContext&);           // the formation
void fn_sub_29A690_0029a690(p3fes::EEContext&);           // the turn order (side first) (battle_data)
void fn_sub_2FAC80_002fac80(p3fes::EEContext&);
void fn_sub_2D50C0_002d50c0(p3fes::EEContext&);           // the advantage roll
void fn_sub_29A750_0029a750(p3fes::EEContext&);           // the turn order (normal)
void fn_sub_29ABE0_0029abe0(p3fes::EEContext&);           // a turn-order step (action)
void fn_sub_29A470_0029a470(p3fes::EEContext&);           // (action) (battle_data)
void fn_sub_1FEBF0_001febf0(p3fes::EEContext&);           // the advantage panel (kind)
void fn_btlGetMeanLevel_002d4cf0(p3fes::EEContext&);           // (1, 0): the party's level
void fn_datCalcGetElementForStatus_00308120(p3fes::EEContext&);  // (skill, status) (battle)
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);   // (DatUnit, element) (battle_calc)
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);      // (DatUnit) (battle_data)
void fn_datCalcSetBadStatus_003004f0(p3fes::EEContext&);  // (DatUnit, bits) (battle)
void fn_sub_1FEC30_001fec30(p3fes::EEContext&);           // panel busy
void fn_sub_2DCD30_002dcd30(p3fes::EEContext&);           // sound
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);           // auto battle on?
void fn_sub_2D1A10_002d1a10(p3fes::EEContext&);
void fn_sub_2D3E00_002d3e00(p3fes::EEContext&);           // (unit, 0)
void fn_sub_27F680_0027f680(p3fes::EEContext&);           // btlUnit home position (unit, vector)
void fn_sub_280870_00280870(p3fes::EEContext&);           // a side's centre (side, 0, out, 0, 0, 1)
void fn_sub_2DD960_002dd960(p3fes::EEContext&);           // a down packet (unit)
void fn_sub_284D80_00284d80(p3fes::EEContext&);           // a motion packet (unit, motion)
void fn_sub_2DD8E0_002dd8e0(p3fes::EEContext&);           // a down packet (unit)
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);           // vector normalise (out, in)
void fn_sub_27F650_0027f650(p3fes::EEContext&);           // btlUnit position (unit, vector)
void fn_sub_2819D0_002819d0(p3fes::EEContext&);           // a walk packet (unit, target, 8; speed in f12)
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);  // (DatUnit, mask) (battle)
void fn_datCalcIsLowHp_0030b5e0(p3fes::EEContext&);       // (DatUnit) (battle_calc)
void fn_datCalcCountEquipmentWithEffect_003009a0(p3fes::EEContext&);  // (DatUnit, effect) (battle_data)
void fn_sub_302380_00302380(p3fes::EEContext&);           // [datCalcApplyEffectMask] (DatUnit, mask, delta) (battle_rest)
void fn_sub_2FF2F0_002ff2f0(p3fes::EEContext&);           // battle_data
void fn_sub_2BFC70_002bfc70(p3fes::EEContext&);           // (0)
void fn_sub_2BD780_002bd780(p3fes::EEContext&);           // the escape packet (unit, kind)
void fn_sub_30C2A0_0030c2a0(p3fes::EEContext&);           // the escape roll (DatUnit) (battle_rest)
void fn_sub_2DD1F0_002dd1f0(p3fes::EEContext&);           // a sound packet (15, 2, 0)
void fn_sub_2BFB50_002bfb50(p3fes::EEContext&);           // an escape packet
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);           // btlUnit position (unit, out)
void fn_sub_280050_00280050(p3fes::EEContext&);           // btlUnit position (unit, out)
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);           // a direction (out, 0x6978A0, 1, home)
void fn_sub_27DC00_0027dc00(p3fes::EEContext&);           // the end packet (128)
void fn_sub_2BFAE0_002bfae0(p3fes::EEContext&);           // a failed-escape packet
void fn_sub_2BD850_002bd850(p3fes::EEContext&);           // a unit packet (unit, 216)
void fn_sub_2D7FB0_002d7fb0(p3fes::EEContext&);           // the result packet (action, 0)
void fn_sub_2BD590_002bd590(p3fes::EEContext&);           // a unit packet (unit, skill)
void fn_sub_282650_00282650(p3fes::EEContext&);           // a face-to packet (unit, unit, kind)
void fn_sub_308F80_00308f80(p3fes::EEContext&);           // (DatUnit) (battle_calc)
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);  // (DatUnit) (battle_calc)
void fn_sub_28A0F0_0028a0f0(p3fes::EEContext&);           // (action)
void fn_sub_2F8EB0_002f8eb0(p3fes::EEContext&);           // an enemy's swing motion (unit, skill)
void fn_sub_3093A0_003093a0(p3fes::EEContext&);           // (DatUnit) (battle_calc)
void fn_sub_283FE0_00283fe0(p3fes::EEContext&);           // the strike timing table (unit, motion)
void fn_sub_283E40_00283e40(p3fes::EEContext&);           // the strike step (unit, motion)
void fn_sub_283C70_00283c70(p3fes::EEContext&);           // the strikes (unit, motion)
void fn_sub_2835E0_002835e0(p3fes::EEContext&);           // a motion's strike time (unit, motion; speed in f12)
void fn_sub_2B7BD0_002b7bd0(p3fes::EEContext&);           // a critical-hit camera packet
void fn_sub_28A540_0028a540(p3fes::EEContext&);           // the camera set (action, skill, 4 out halfwords)
void fn_sub_283750_00283750(p3fes::EEContext&);           // the guard motion (unit, motion)
void fn_sub_27F2F0_0027f2f0(p3fes::EEContext&);           // a packet
void fn_sub_2FD160_002fd160(p3fes::EEContext&);           // a counter camera (target)
void fn_sub_308ED0_00308ed0(p3fes::EEContext&);           // (DatUnit) (battle_calc)
void fn_sub_282130_00282130(p3fes::EEContext&);           // a down packet (unit, 16)
void fn_sub_284C90_00284c90(p3fes::EEContext&);           // a motion packet (unit)
void fn_sub_2D8090_002d8090(p3fes::EEContext&);           // an HP gauge packet (action)
void fn_btlCountActiveUnits_002d4e10(p3fes::EEContext&);           // (2, 0x80000)
void fn_sub_2B7060_002b7060(p3fes::EEContext&);
void fn_sub_2D6130_002d6130(p3fes::EEContext&);           // (action)
void fn_sub_2D6210_002d6210(p3fes::EEContext&);           // (action)
void fn_sub_2D5F50_002d5f50(p3fes::EEContext&);           // (action)
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);  // (DatUnit, skill) (battle_calc)
void fn_sub_2DC130_002dc130(p3fes::EEContext&);           // a bad-status reaction wanted (action)
// btlActionUpdateStateSkill
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_27F410_0027f410(p3fes::EEContext&);
void fn_sub_27FC80_0027fc80(p3fes::EEContext&);
void fn_sub_283A70_00283a70(p3fes::EEContext&);
void fn_sub_284040_00284040(p3fes::EEContext&);
void fn_sub_2843E0_002843e0(p3fes::EEContext&);
void fn_sub_284F50_00284f50(p3fes::EEContext&);
void fn_sub_2857F0_002857f0(p3fes::EEContext&);
void fn_sub_2860B0_002860b0(p3fes::EEContext&);
void fn_sub_286240_00286240(p3fes::EEContext&);
void fn_sub_288360_00288360(p3fes::EEContext&);
void fn_sub_2A1B00_002a1b00(p3fes::EEContext&);
void fn_sub_2A1DB0_002a1db0(p3fes::EEContext&);
void fn_sub_2B8900_002b8900(p3fes::EEContext&);
void fn_sub_2B8B70_002b8b70(p3fes::EEContext&);
void fn_sub_2B9590_002b9590(p3fes::EEContext&);
void fn_sub_2B9640_002b9640(p3fes::EEContext&);
void fn_sub_2BD690_002bd690(p3fes::EEContext&);
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_sub_2D4CC0_002d4cc0(p3fes::EEContext&);
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);
void fn_sub_2D5C70_002d5c70(p3fes::EEContext&);
void fn_sub_2D5EB0_002d5eb0(p3fes::EEContext&);
void fn_sub_2D5FB0_002d5fb0(p3fes::EEContext&);
void fn_sub_2D6090_002d6090(p3fes::EEContext&);
void fn_sub_2D6290_002d6290(p3fes::EEContext&);
void fn_sub_2D62D0_002d62d0(p3fes::EEContext&);
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);
void fn_sub_2D8330_002d8330(p3fes::EEContext&);
void fn_sub_2DD690_002dd690(p3fes::EEContext&);
void fn_sub_2DDC80_002ddc80(p3fes::EEContext&);
void fn_sub_2E33F0_002e33f0(p3fes::EEContext&);
void fn_sub_2E35D0_002e35d0(p3fes::EEContext&);
void fn_sub_2E36F0_002e36f0(p3fes::EEContext&);
void fn_sub_2E37E0_002e37e0(p3fes::EEContext&);
void fn_sub_2E3DE0_002e3de0(p3fes::EEContext&);
void fn_sub_2E3F20_002e3f20(p3fes::EEContext&);
void fn_sub_2F8FD0_002f8fd0(p3fes::EEContext&);
void fn_sub_2F9690_002f9690(p3fes::EEContext&);
void fn_sub_2FCAA0_002fcaa0(p3fes::EEContext&);
void fn_sub_2FD060_002fd060(p3fes::EEContext&);
void fn_sub_2FDBB0_002fdbb0(p3fes::EEContext&);
void fn_sub_2FDCB0_002fdcb0(p3fes::EEContext&);
void fn_sub_2FDDB0_002fddb0(p3fes::EEContext&);
void fn_sub_2FDED0_002fded0(p3fes::EEContext&);
void fn_sub_308A50_00308a50(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace core = ee::core;
namespace rg = ::p3fes::recomp_gen;
using namespace btl_act;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ---------------------------------
constexpr u64 li(s32 i) { return core::add32i(0, i); }  // `addiu rX, zero, imm`
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 daddiu(u64 a, s32 i) { return core::add64i(a, i); }
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr bool gtz(u64 a) { return static_cast<s64>(a) > 0; }
constexpr bool gez(u64 a) { return static_cast<s64>(a) >= 0; }

// The uid mask `lui v0, 0x3FFF; ori v0, 0xFFFF; dsll32 v1, v0, 0; ori v0, zero, 0xFFFF; dsll v0, 16; ori v0, 0xFFFF;
// or a1, v0, v1`: the 62-bit uid of a btlAction, as btlPacketFindFirstByActionUID takes it.
constexpr u64 kUidMaskHi = 0x3FFFFFFF00000000ull;
constexpr u64 kUidMaskLo = 0xFFFFFFFFull;

// One GPR of the guest context.
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return c.gpr[r].u64[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

enum : unsigned { F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
                  F21, F22, F23, F24 };

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time
    // (not guest::enter / guest::backedge: those are noexcept, and a test hook may stop the run at a check point)
    void enter(u64 n) {
        rt::check_events(c);
        c.cycles += n;
    }
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { rt::check_events(c); }

    // loads / stores: the runtime's instructions (alignment faults, unmapped faults, hardware windows)
    void lb(Gpr& d, const Gpr& b, s32 o) { rt::lb(c, d.r, b.r, o); }
    void lbu(Gpr& d, const Gpr& b, s32 o) { rt::lbu(c, d.r, b.r, o); }
    void lh(Gpr& d, const Gpr& b, s32 o) { rt::lh(c, d.r, b.r, o); }
    void lhu(Gpr& d, const Gpr& b, s32 o) { rt::lhu(c, d.r, b.r, o); }
    void lw(Gpr& d, const Gpr& b, s32 o) { rt::lw(c, d.r, b.r, o); }
    void ld(Gpr& d, const Gpr& b, s32 o) { rt::ld(c, d.r, b.r, o); }
    void lq(Gpr& d, const Gpr& b, s32 o) { rt::lq(c, d.r, b.r, o); }
    void sb(const Gpr& s, const Gpr& b, s32 o) { rt::sb(c, s.r, b.r, o); }
    void sh(const Gpr& s, const Gpr& b, s32 o) { rt::sh(c, s.r, b.r, o); }
    void sw(const Gpr& s, const Gpr& b, s32 o) { rt::sw(c, s.r, b.r, o); }
    void sd(const Gpr& s, const Gpr& b, s32 o) { rt::sd(c, s.r, b.r, o); }
    void sq(const Gpr& s, const Gpr& b, s32 o) { rt::sq(c, s.r, b.r, o); }

    // FPU, HI/LO, MMI (the runtime's instruction semantics)
    void lwc1(unsigned f, const Gpr& b, s32 o) { rt::lwc1(c, f, b.r, o); }
    void swc1(unsigned f, const Gpr& b, s32 o) { rt::swc1(c, f, b.r, o); }
    void mtc1(const Gpr& g, unsigned f) { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) { rt::cvt_w_s(c, d, s); }
    void mov_s(unsigned d, unsigned s) { rt::mov_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) { rt::div_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) { rt::c_eq_s(c, s, t); }
    bool cop1_cond() const { return rt::cop1_cond(c); }
    void div(const Gpr& s, const Gpr& t) { rt::div(c, s.r, t.r); }
    void mflo(Gpr& d) { rt::mflo(c, d.r); }
    void paddub(Gpr& d, const Gpr& s, const Gpr& t) { rt::paddub(c, d.r, s.r, t.r); }

    // `jal fn` with $ra = the original link
    void jal(u32 link, rt::Fn fn) {
        rt::jal(c, link);
        fn(c);
    }

    // `lw rX, -18692(gp)`: gBtl, through the guest $gp as the original reads it
    void gbtl(Gpr& d) { lw(d, gp, kGBtlGpOffset); }

    // The packet stamp after a creator returned the packet in $v0 (+72 = the state's +12 word, +96 = the owner action's
    // uid; the other order, owner first, is written out where it occurs: $v1 differs at the queue call).
    void stamp_state_owner(const Gpr& state, const Gpr& owner) {
        lhu(v1, state, 12);
        sh(v1, v0, kPktTime);
        ld(v1, owner, kActUid);
        sd(v1, v0, kPktOwner);
    }
    // Only the owner: `ld v1, 0(owner); sd v1, 96(v0)`.
    void stamp_owner(const Gpr& owner) {
        ld(v1, owner, kActUid);
        sd(v1, v0, kPktOwner);
    }
    // A dependency of the packet in $v0 (slot k: kind byte at +16k, id at +16k+8): "after the packet `src`" (its +88
    // id) / "after the packet whose id `id` holds". The kind goes through $v1.
    void depend(unsigned slot, s32 kind, const Gpr& src) {
        v1 = li(kind);
        sb(v1, v0, static_cast<s32>(16 * slot));
        ld(v1, src, kPktId);
        sd(v1, v0, static_cast<s32>(16 * slot + 8));
    }
    void depend_id(unsigned slot, s32 kind, const Gpr& id) {
        v1 = li(kind);
        sb(v1, v0, static_cast<s32>(16 * slot));
        sd(id, v0, static_cast<s32>(16 * slot + 8));
    }
    // `move a0, v0; ...; li a1, q; jal sub_27ED20`
    void enqueue(u32 link, s32 queue) {
        a1 = li(queue);
        jal(link, rg::fn_sub_27ED20_0027ed20);
    }

    // --- the bodies (battle_actions.h documents each) ---
    void unit_load_update();  // btlMainUpdateStateUnitLoad
    void revival_update();    // btlMainUpdateStateRevival
    void win_init();          // btlMainInitStateWin
    void unit_load_init();    // btlMainInitStateUnitLoad
    void end_init();          // btlMainInitStateEnd
    void command_init();      // sub_28BD10 [btlActionInitStateCommand]
    void command_update();    // sub_28BF80 [btlActionUpdateStateCommand]
    void revival_init();      // btlMainInitStateRevival
    void condition_init();    // btlMainInitStateCondition
    void unit_create_init();  // btlMainInitStateUnitCreate
    void unit_create_update();  // btlMainUpdateStateUnitCreate
    void escape_update();     // btlActionUpdateStateEscape
    void attack_update();     // btlActionUpdateStateAttack
    void skill_update();      // btlActionUpdateStateSkill
    // `dsll32 x, y, 24; dsra32 x, x, 24`: the low byte sign-extended
    static u64 sx8(u64 v) { return dsra32(dsll32(v, 24), 24); }
    void attack_hit();        //   one hit of the current target record (with its strikes)
    void attack_strike();     //   one strike of a hit
    void attack_record_end(); //   the current target record's results
    // "after the packet whose address the frame word sp+off holds": `lw v1, off(sp); ld v1, 88(v1)`
    void depend_at(unsigned slot, s32 kind, s32 off) {
        v1 = li(kind);
        sb(v1, v0, static_cast<s32>(16 * slot));
        lw(v1, sp, off);
        ld(v1, v1, kPktId);
        sd(v1, v0, static_cast<s32>(16 * slot + 8));
    }
    // "after the packet whose id the frame doubleword sp+off holds": `ld v1, off(sp)`
    void depend_id_at(unsigned slot, s32 kind, s32 off) {
        v1 = li(kind);
        sb(v1, v0, static_cast<s32>(16 * slot));
        ld(v1, sp, off);
        sd(v1, v0, static_cast<s32>(16 * slot + 8));
    }
    // `lbu v1, 71(v0); andi v1, 0xDF; sb v1, 71(v0)`: the packet's +71 bit 5 cleared
    void clear_bit5_71() {
        lbu(v1, v0, 71);
        v1 = v1 & 0xDF;
        sb(v1, v0, 71);
    }
    // `dsll32 x, y, 16; dsra32 x, x, 16`: the low halfword sign-extended
    static u64 sx16(u64 v) { return dsra32(dsll32(v, 16), 16); }
    // a camera of the gBtl camera table (gBtl+3108 + 4 * the frame halfword at sp+off) on the actor and the victim
    // (s6), after the strike's motion (s2), queue 2
    void attack_camera(s32 off, u32 link, u32 link_queue);
    // ESCAPE's run-away target: the direction at sp+208 scaled in place by $f1 (x, y, z left in $f3, $f2, $f1) and
    // the target sp+240 = the position at sp+224 + it, as compiled.
    void scale_dir_add() {
        lwc1(F0, sp, 208);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 208);
        lwc1(F0, sp, 212);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 212);
        lwc1(F0, sp, 216);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 216);
        lwc1(F0, sp, 224);
        add_s(F0, F0, F3);
        swc1(F0, sp, 240);
        lwc1(F0, sp, 228);
        add_s(F0, F0, F2);
        swc1(F0, sp, 244);
        lwc1(F0, sp, 232);
        add_s(F0, F0, F1);
        swc1(F0, sp, 248);
    }
    // the run direction of the unit `unit`: its position (`pos`: sub_27FFB0 or sub_280050) into sp+224, its home
    // (sub_27F7C0) into sp+144, and the direction sub_4BE1E0(sp+208, 0x6978A0, 1, sp+144)
    void run_direction(const Gpr& action, u32 link_pos, rt::Fn pos, u32 link_home, u32 link_dir) {
        lw(a0, action, kActUnit);
        a1 = addiu(sp, 224);
        jal(link_pos, pos);
        lw(a0, action, kActUnit);
        a1 = 0;
        a2 = addiu(sp, 144);
        a3 = 0;
        jal(link_home, rg::fn_sub_27F7C0_0027f7c0);
        a0 = addiu(sp, 208);
        a1 = lui(0x69);
        a1 = addiu(a1, 30880);
        a2 = li(1);
        a3 = addiu(sp, 144);
        jal(link_dir, rg::fn_sub_4BE1E0_004be1e0);
    }
    // A `jr` through a jump table whose target is not one of the listed labels: the recompiled body's tail jump.
    void jr_unknown(const Gpr& target) { rt::lookup_func(static_cast<u32>(target))(c); }
    void target_init();       // sub_28C310 [btlActionInitStateTarget]
    void target_update();     // sub_28C590 [btlActionUpdateStateTarget]

    // The SKILL.TBL record of skill `id` (44-byte records at *(gp-18680)), as compiled: `out = id * 11` by shifts and
    // adds, `tmp = out * 4`, `out = *(gp-18680) + tmp` (id may be tmp itself: it is read before tmp is written).
    void skill_rec(Gpr& out, Gpr& tmp, const Gpr& id) {
        out = sll(id, 2);
        out = addu(out, id);
        out = sll(out, 1);
        out = addu(out, id);
        tmp = sll(out, 2);
        lw(out, gp, kGpSkillTbl);
        out = addu(tmp, out);
    }
    // the action-list walk that does nothing (the compiled loop of COMMAND's cases 5 and 8): v0 = the list end
    void walk_action_list();

    // `div v1, v0` by 1250 of 100 * (x & 0xFFFF), the compiled shift-add chain: 8 % of a maximum (END's passive 605)
    void eight_percent(Gpr& out) {
        v1 = v0 & 0xFFFF;
        v0 = sll(v1, 2);
        v1 = addu(v0, v1);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 2);
        v0 = li(1250);
        div(v1, v0);
        mflo(out);
    }
};

// =====================================================================================================================
// btlMain states
// =====================================================================================================================

// 0x29C110 btlMainUpdateStateUnitLoad(state): UNIT_LOAD. While gBtl+12 bit 20 (models loading) is set, unless
// datUnitIsGenusReady() says 1, the panel step sub_1FEC50 runs and the bit is cleared. Once no packet is queued and the
// bit is clear: a sound packet for the current action when the panel is idle (sub_1FEEC0() == 0), every btlUnit of
// the all-units list shown (flag 8: sub_287490) or hidden (sub_287510), the start hook sub_2FAAB0, and -> START (6).
// Otherwise stay (0).
void Cpu::unit_load_update() {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    gbtl(v0);
    lw(v1, v0, kFlags);
    v0 = lui(0x10);
    v0 = v1 & v0;  // kFlagLoading
    if (v0 != 0) {
        charge(5);
        jal(0x29c134, rg::fn_datUnitIsGenusReady_002ff320);
        v1 = li(1);
        if (v0 != v1) {
            charge(8);
            jal(0x29c148, rg::fn_sub_1FEC50_001fec50);
            gbtl(a0);
            lw(v1, a0, kFlags);
            v0 = lui(0xFFEF);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, kFlags);
        }
    }
    charge(4);
    bool start = false;
    jal(0x29c168, rg::fn_sub_27E410_0027e410);
    if (v0 == 0) {
        charge(6);
        gbtl(v0);
        lw(v1, v0, kFlags);
        v0 = lui(0x10);
        v0 = v1 & v0;
        start = v0 == 0;
    }
    if (start) {
        charge(4);
        jal(0x29c190, rg::fn_sub_1FEEC0_001feec0);
        if (v0 == 0) {
            charge(12);
            gbtl(v0);
            lw(a0, v0, kCurrentAction);
            a1 = 0;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(0x29c1b8, rg::fn_sub_2DB740_002db740);
            a0 = v0;
            enqueue(0x29c1c8, 1);
        }
        charge(4);
        gbtl(v0);
        lw(s0, v0, kSideListB + 8);  // the enemy side's units (+2612)
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(4);
            lw(v0, s0, kUnitFlags);
            v0 = v0 & 0x8;
            a0 = s0;
            if (v0 != 0) {
                charge(5);
                jal(0x29c1f4, rg::fn_sub_287490_00287490);
            } else {
                charge(3);
                jal(0x29c208, rg::fn_sub_287510_00287510);
            }
            charge(1);
            lw(s0, s0, kUnitNextB);
        }
        charge(5);
        jal(0x29c21c, rg::fn_sub_2FAAB0_002faab0);
        v0 = li(6);
    } else {
        charge(1);
        v0 = 0;
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x29CCD0 btlMainUpdateStateRevival(state): REVIVAL. Waits until no packet of the current action is queued; then
// one revival item 4040 of the reviving character (DatUnit +2) is used up (sub_170760 count, sub_170860 count - 1),
// sub_2BFC50(0), the turn-order reset sub_29B040, the panel refresh sub_1FF370 when sub_2FD7C0() == 1, the battle-over
// bit 0x80 of gBtl+12 cleared, the message packet 31 queued, and -> ACTION (7). Otherwise stay (0).
void Cpu::revival_update() {
    enter(17);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    gbtl(v0);
    lw(s0, v0, kCurrentAction);
    ld(a0, s0, kActUid);
    v0 = lui(0x3FFF);
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(0x29cd04, rg::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        charge(1);
        v0 = 0;
    } else {
        charge(25);
        // the reviving character's item count (DatUnit +2 = character id)
        lw(v0, s0, kActUnit);
        lw(v0, v0, kUnitDat);
        lh(a0, v0, 2);
        a1 = li(4040);
        jal(0x29cd24, rg::fn_sub_170760_00170760);
        v1 = v0 & 0xFFFF;
        lw(v0, s0, kActUnit);
        lw(v0, v0, kUnitDat);
        lh(a0, v0, 2);
        v0 = addiu(v1, -1);
        a2 = v0 & 0xFFFF;
        a1 = li(4040);
        jal(0x29cd48, rg::fn_sub_170860_00170860);
        a0 = 0;
        jal(0x29cd54, rg::fn_sub_2BFC50_002bfc50);
        jal(0x29cd5c, rg::fn_sub_29B040_0029b040);
        jal(0x29cd64, rg::fn_sub_2FD7C0_002fd7c0);
        v1 = li(1);
        if (v0 == v1) {
            charge(2);
            jal(0x29cd78, rg::fn_sub_1FF370_001ff370);
        }
        charge(16);
        gbtl(a0);
        lw(v1, a0, kFlags);
        v0 = li(-129);  // ~kFlagOver
        v0 = v1 & v0;
        sw(v0, a0, kFlags);
        a0 = s0;
        a1 = li(31);
        jal(0x29cd9c, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        enqueue(0x29cdac, 0);
        v0 = li(7);
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// 0x29CE90 btlMainInitStateWin(state): WIN. The pose leader is the first actor of the turn order (or the next one,
// sub_29AD50, when its +24 bit 2 is set); when there is none or it is an enemy, the current actor. state+12 = 24 (the
// pose frames), state+16 = the leader's victory motion (sub_2838D0(unit, 20), $f12 = 1.0), state+20 = 0, state+14 =
// 48 when the leader is the current actor, else 24. Every combatant (+26 bit 0) on the enemy side
// (+162 == 1) that is dead gets a pose packet (sub_286320, queue 0); then the victory sound (sub_2DB740(leader, 15,
// 0, 0, 3), queue 1), the victory camera (sub_2E2BE0(leader, 7, 0, 0, 0), queue 1), the leader's motion 20
// (sub_284200(unit, 20, 0, 2), $f12 = 1.0, queue 0) and the message packet 32 (queue 0), each stamped with the state
// and the leader's uid.
void Cpu::win_init() {
    enter(13);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    jal(0x29cea8, rg::fn_sub_29AD20_0029ad20);
    s1 = v0;
    lhu(v0, v0, kActFlags);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        charge(3);
        jal(0x29cec4, rg::fn_sub_29AD50_0029ad50);
        s1 = v0;
    }
    charge(2);
    bool use_current = s1 == 0;
    if (!use_current) {
        charge(5);
        lw(v0, s1, kActUnit);
        lbu(v1, v0, kUnitSide);
        v0 = li(1);
        use_current = v1 == v0;
    }
    if (use_current) {
        charge(2);
        gbtl(v0);
        lw(s1, v0, kCurrentAction);
    }
    charge(14);
    v0 = li(24);
    sh(v0, s2, 12);
    v0 = lui(0x3F80);  // 1.0f
    mtc1(v0, F12);
    lw(a0, s1, kActUnit);
    a1 = li(20);
    jal(0x29cf0c, rg::fn_sub_2838D0_002838d0);
    sh(v0, s2, 16);
    sw(zero, s2, 20);
    gbtl(v0);
    lw(v0, v0, kCurrentAction);
    if (s1 == v0) {
        charge(3);
        v0 = li(48);
    } else {
        charge(1);
        v0 = li(24);
    }
    charge(5);
    sh(v0, s2, 14);
    gbtl(v0);
    lw(s0, v0, kActionList);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(4);
        lhu(v0, s0, kActFlags2);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            charge(5);
            lw(a0, s0, kActUnit);
            lbu(v1, a0, kUnitSide);
            v0 = li(1);
            if (v1 == v0) {
                charge(6);
                lw(a0, a0, kUnitDat);
                a1 = 0;
                jal(0x29cf7c, rg::fn_datCalcIsDead_0030b5a0);
                if (v0 != 0) {
                    charge(11);
                    lw(a0, s0, kActUnit);
                    jal(0x29cf90, rg::fn_sub_286320_00286320);
                    a0 = v0;
                    ld(v1, s1, kActUid);
                    sd(v1, v0, kPktOwner);
                    lhu(v1, s2, 12);
                    sh(v1, v0, kPktTime);
                    enqueue(0x29cfb0, 0);
                }
            }
        }
        charge(1);
        lw(s0, s0, kActNextInList);
    }
    charge(65);
    a0 = s1;
    a1 = li(15);
    a2 = 0;
    a3 = 0;
    t0 = li(3);
    jal(0x29cfd8, rg::fn_sub_2DB740_002db740);
    a0 = v0;
    stamp_state_owner(s2, s1);
    enqueue(0x29cff8, 1);
    a0 = s1;
    a1 = li(7);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(0x29d014, rg::fn_sub_2E2BE0_002e2be0);
    a0 = v0;
    stamp_state_owner(s2, s1);
    enqueue(0x29d034, 1);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s1, kActUnit);
    a1 = li(20);
    a2 = 0;
    a3 = li(2);
    jal(0x29d054, rg::fn_sub_284200_00284200);
    a0 = v0;
    stamp_state_owner(s2, s1);
    enqueue(0x29d074, 0);
    a0 = s1;
    a1 = li(32);
    jal(0x29d084, rg::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    stamp_state_owner(s2, s1);
    enqueue(0x29d0a4, 0);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x29B280 btlMainInitStateUnitCreate(state): UNIT_CREATE. The party: for each of the setup block's up to four party
// records (gBtl+2988 + 4i, stopping at the first null), the btlAction/btlUnit sub_289650(0, character, record), the
// unit's model sub_316910(side + 1, character, 0) -> unit+2548; a model not resident yet gets a load packet
// sub_285690(unit, character, 54) after the previous one (queue 1); a resident one is set up at once (+152 |= 2 | 8,
// sub_3B6000 -> +2546, sub_1A0590(+2546, 1), sub_287B20(unit, 1), sub_2831C0(unit, 0), sub_282D40(unit, +2528,
// 0, +2536; $f12 = +2532), sub_282BC0, sub_31C7E0 when the model's +1016 is 0, sub_287B20(unit, 4), shown with
// sub_287490). gBtl+2980 = the party count. The enemies: the six 60-byte DatUnits of the setup's enemy group
// (*(gBtl+3004) + 4) that have an id and are alive get sub_289650(1, id, DatUnit). The formation sub_2B71E0. With
// gBtl+12 bit 8 the advantage: the ENCOUNT record (28 bytes at *(gp-18504), index group +8) flag 0x20 scripts it
// (0x10 -> the order sub_29A690(1), else sub_2FAC80 and gBtl+26 = 0); otherwise gBtl+26 = sub_2D50C0(): 0 -> the
// order sub_29A750 and, with setup flag 4, datCalcRand(12) turns of sub_29ABE0(sub_29AD20()); 1 -> sub_29A690(0),
// sub_29A470(current action), +584 |= 2, unless ENCOUNT flag 0x200 the panel sub_1FEBF0(0) and gBtl+12 |= 0x100000,
// and the distress roll; 2 -> sub_29A690(1), +584 |= 4, unless 0x200 sub_1FEBF0(1) and the loading bit. The distress
// roll (also forced by setup flag 8; never with ENCOUNT flag 0x100): every enemy (the B list +344) whose affinity to
// the element sub_308120(-1, 2) has none of the bits 0x27000000 and whose level + 2 <= btlGetMeanLevel(1, 0) is
// distressed (datCalcSetBadStatus(DatUnit, 2)) when datCalcRand(100) < 33.
void Cpu::unit_create_init() {
    enter(10);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = 0;  // the id of the previous load packet
    s1 = 0;
    for (;;) {  // the party
        charge(3);
        v0 = sltiu(s1, 4);
        if (v0 == 0) break;
        backedge();
        charge(6);
        gbtl(v1);
        v0 = sll(s1, 2);
        v0 = addu(v1, v0);
        lw(v0, v0, kSetupParty);
        if (v0 == 0) break;
        charge(17);
        lw(a2, v0, 4);
        lhu(s0, a2, 2);  // the character
        a0 = 0;
        a1 = s0;
        jal(0x29b2d0, rg::fn_sub_289650_00289650);
        lw(s3, v0, kActUnit);
        lbu(v0, s3, kUnitSide);
        v0 = addiu(v0, 1);
        a0 = v0 & 0xFFFF;
        a1 = s0;
        a2 = 0;
        jal(0x29b2f0, rg::fn_sub_316910_00316910);
        sw(v0, s3, kUnitModel);
        if (v0 == 0) {  // not resident: a load packet
            charge(16);
            a0 = s3;
            a1 = s0;
            a2 = li(54);
            jal(0x29b310, rg::fn_sub_285690_00285690);
            s0 = v0;
            depend_id(0, 4, s2);
            a0 = s0;
            enqueue(0x29b330, 1);
            ld(s2, s0, kPktId);
        } else {
            charge(36);
            lw(v0, s3, 152);
            v0 = v0 | 0x2;
            sw(v0, s3, 152);
            v0 = v0 | 0x8;
            sw(v0, s3, 152);
            a0 = s0;
            lw(a1, s3, kUnitModel);
            jal(0x29b360, rg::fn_sub_3B6000_003b6000);
            sh(v0, s3, 2546);
            lhu(a0, s3, 2546);
            a1 = li(1);
            jal(0x29b374, rg::fn_sub_1A0590_001a0590);
            a0 = s3;
            a1 = li(1);
            jal(0x29b384, rg::fn_sub_287B20_00287b20);
            a0 = s3;
            a1 = 0;
            jal(0x29b394, rg::fn_sub_2831C0_002831c0);
            lb(a3, s3, 2536);
            a0 = s3;
            lh(a1, s3, 2528);
            a2 = 0;
            lwc1(F12, s3, 2532);
            jal(0x29b3b0, rg::fn_sub_282D40_00282d40);
            a0 = s3;
            jal(0x29b3bc, rg::fn_sub_282BC0_00282bc0);
            lw(a0, s3, kUnitModel);
            lw(v0, a0, 1016);
            if (v0 == 0) {
                charge(2);
                jal(0x29b3d4, rg::fn_sub_31C7E0_0031c7e0);
            }
            charge(7);
            a0 = s3;
            a1 = li(4);
            jal(0x29b3e4, rg::fn_sub_287B20_00287b20);
            a0 = s3;
            jal(0x29b3f0, rg::fn_sub_287490_00287490);
        }
        charge(1);
        s1 = addiu(s1, 1);
    }
    charge(8);
    gbtl(v0);
    sb(s1, v0, kPartyCount);
    gbtl(v0);
    lw(v0, v0, kSetupEnemies);
    lw(s0, v0, 4);  // the enemy group's DatUnits
    s1 = 0;
    for (;;) {
        charge(3);
        v0 = sltiu(s1, 6);
        if (v0 == 0) break;
        backedge();
        charge(3);
        lhu(v0, s0, 2);
        if (v0 != 0) {
            charge(6);
            a0 = s0;
            a1 = 0;
            jal(0x29b43c, rg::fn_datCalcIsDead_0030b5a0);
            if (v0 == 0) {
                charge(5);
                lhu(a1, s0, 2);
                a0 = li(1);
                a2 = s0;
                jal(0x29b458, rg::fn_sub_289650_00289650);
            }
        }
        charge(2);
        s1 = addiu(s1, 1);
        s0 = addiu(s0, 60);
    }
    charge(7);
    jal(0x29b474, rg::fn_sub_2B71E0_002b71e0);  // the formation
    gbtl(a0);
    lw(v1, a0, kFlags);
    v1 = v1 & 0x100;
    if (v1 == 0) goto out;
    // the advantage
    charge(12);
    s1 = 0;  // the distress roll
    lw(v0, a0, kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpEncountTbl);
    s0 = addu(v0, v1);  // the ENCOUNT record
    lw(v1, s0, 0);
    v0 = v1 & 0x20;
    if (v0 != 0) {  // scripted
        charge(3);
        v0 = v1 & 0x10;
        if (v0 != 0) {
            charge(5);
            a0 = li(1);
            jal(0x29b4d0, rg::fn_sub_29A690_0029a690);
        } else {
            charge(6);
            jal(0x29b4e0, rg::fn_sub_2FAC80_002fac80);
            gbtl(v1);
            sh(zero, v1, kAdvantage);
        }
    } else {
        charge(9);
        jal(0x29b4f8, rg::fn_sub_2D50C0_002d50c0);
        gbtl(v1);
        sh(v0, v1, kAdvantage);
        gbtl(v1);
        lhu(a0, v1, kAdvantage);
        v1 = li(2);
        if (a0 == v1) {
            charge(11);
            a0 = li(1);
            jal(0x29b608, rg::fn_sub_29A690_0029a690);
            gbtl(a0);
            lhu(v1, a0, kOrderFlags);
            v1 = v1 | 0x4;
            sh(v1, a0, kOrderFlags);
            lw(v1, s0, 0);
            v1 = v1 & 0x200;
            if (v1 == 0) {
                charge(8);
                a0 = li(1);
                jal(0x29b634, rg::fn_sub_1FEBF0_001febf0);
                gbtl(a1);
                lw(a0, a1, kFlags);
                v1 = lui(0x10);
                v1 = a0 | v1;
                sw(v1, a1, kFlags);
            }
        } else if (charge(3), v1 = li(1), a0 == v1) {
            charge(15);
            a0 = 0;
            jal(0x29b5a0, rg::fn_sub_29A690_0029a690);
            gbtl(v0);
            lw(a0, v0, kCurrentAction);
            jal(0x29b5b0, rg::fn_sub_29A470_0029a470);
            gbtl(a0);
            lhu(v1, a0, kOrderFlags);
            v1 = v1 | 0x2;
            sh(v1, a0, kOrderFlags);
            lw(v1, s0, 0);
            v1 = v1 & 0x200;
            if (v1 == 0) {
                charge(8);
                a0 = 0;
                jal(0x29b5dc, rg::fn_sub_1FEBF0_001febf0);
                gbtl(a1);
                lw(a0, a1, kFlags);
                v1 = lui(0x10);
                v1 = a0 | v1;
                sw(v1, a1, kFlags);
            }
            charge(3);
            s1 = li(1);
        } else if (charge(2), a0 == 0) {
            charge(7);
            jal(0x29b538, rg::fn_sub_29A750_0029a750);
            gbtl(v1);
            lhu(v1, v1, kSetupFlags);
            v1 = v1 & 0x4;
            if (v1 != 0) {
                charge(7);
                a0 = li(12);
                jal(0x29b558, rg::fn_datCalcRand_002ffbc0);
                s2 = v0 & 0xFFFF;
                s3 = 0;
                for (;;) {
                    charge(3);
                    v1 = sltu(s3, s2);
                    if (v1 == 0) break;
                    backedge();
                    charge(6);
                    jal(0x29b570, rg::fn_sub_29AD20_0029ad20);
                    a0 = v0;
                    jal(0x29b57c, rg::fn_sub_29ABE0_0029abe0);
                    s3 = addiu(s3, 1);
                }
                charge(2);
            }
        } else {
            charge(2);
        }
    }
    charge(5);
    gbtl(v1);
    lhu(v1, v1, kSetupFlags);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        charge(1);
        s1 = li(1);
    }
    charge(2);
    if (s1 == 0) goto out;
    charge(4);
    lw(v1, s0, 0);
    v1 = v1 & 0x100;
    if (v1 != 0) goto out;
    // the distress roll
    charge(16);
    a0 = li(1);
    a1 = 0;
    jal(0x29b688, rg::fn_btlGetMeanLevel_002d4cf0);
    s0 = v0 & 0xFFFF;
    a0 = li(-1);
    a1 = li(2);
    jal(0x29b69c, rg::fn_datCalcGetElementForStatus_00308120);
    s2 = dsll32(v0, 16);
    s2 = dsra32(s2, 16);
    gbtl(v1);
    lw(s1, v1, kSideListB + 8);  // the enemy side's units (+2612)
    s0 = s0 & 0xFFFF;
    for (;;) {
        charge(2);
        if (s1 == 0) break;
        backedge();
        charge(3);
        lw(a0, s1, kUnitDat);
        if (a0 != 0) {
            charge(7);
            a1 = s2;
            jal(0x29b6d0, rg::fn_datCalcGetAffinity_00306e80);
            v1 = lui(0x2700);
            v1 = v0 & v1;
            if (v1 == 0) {
                charge(8);
                lw(a0, s1, kUnitDat);
                jal(0x29b6ec, rg::fn_datCalcGetLevel_002ffcc0);
                v1 = v0 & 0xFF;
                v1 = addiu(v1, 2);
                v1 = slt(s0, v1);
                if (v1 == 0) {
                    charge(6);
                    a0 = li(100);
                    jal(0x29b70c, rg::fn_datCalcRand_002ffbc0);
                    at = slti(v0, 33);
                    if (at != 0) {
                        charge(4);
                        lw(a0, s1, kUnitDat);
                        a1 = li(2);
                        jal(0x29b728, rg::fn_datCalcSetBadStatus_003004f0);
                    }
                }
            }
        }
        charge(1);
        lw(s1, s1, kUnitNextB);
    }
out:
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// 0x29B760 btlMainUpdateStateUnitCreate(state): UNIT_CREATE, once the queues are empty and sub_1FEC30() is 0: sound
// sub_2DCD30; the auto-battle mark (gBtl+12 bit 14 set and the panel sub_1FF370 when the panel is idle and
// sub_2D1A70() == 1, else cleared and sub_2D1A10). Every unit of both sides' B lists: sub_2D3E00(unit, 0) and its
// home position (sub_27F7C0 into sp+112, sub_27F680). The party's centre sub_280870(2, 0, sp+144, 0, 0, 1); per party
// unit: shown (sub_287490); a dead one keeps the dead bit (datCalcSetBadStatus 0x80000, HP 0, +156 |= 1,
// sub_2831C0(unit, 0)) and gets its down packets (sub_2DD960, the motion 18 sub_284200(unit, 18, 0, 2) / sub_2838D0 ->
// sub_284D80, sub_2DD8E0; queue 1 each, $f12 = 1.0); a living one, with two or more party members and gBtl+16 bit 0
// clear, walks in: from 150 units out along (its position - the centre), normalised by sub_4C69F0 (sub_27F650 places
// it there; the walk sub_2819D0(unit, position, 8; $f12 = *(gp-32632)) and the turn sub_2822B0(unit, sp+160, 0) after
// it, queue 1), and unless it has a bad status in 0xFFFFF or low HP the ready motion sub_284200(unit, 16, 4, 0)
// ($f12 = 1.0, after the walk, +72 = 4). Per side the passives 589 / 590 / 591 of any unit enable the auto-buffs of
// all: 557 or equipment effect 180 or 590 -> sub_302380(DatUnit, 5, 1); 558 / 181 / 589 -> (64, 1); 559 / 182 / 591 ->
// (272, 1); DatUnit +0 &= 0xFBF7. An ENCOUNT record with a +4 word and a positive +6 copies them to gBtl+3040 / +3044
// and sets +3064 = 1. Then the message packet 2 (queue 0), sub_2FF2F0 unless gBtl+16 bit 0, sub_2BFC70(0),
// sub_2BFC50(0) -> UNIT_LOAD (5). Otherwise stay (0).
void Cpu::unit_create_update() {
    enter(12);
    sp = addiu(sp, -192);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    jal(0x29b780, rg::fn_sub_27E410_0027e410);
    if (v0 != 0) goto stay;
    charge(4);
    jal(0x29b790, rg::fn_sub_1FEC30_001fec30);
    if (v0 != 0) goto stay;
    {
        charge(6);
        jal(0x29b7a0, rg::fn_sub_2DCD30_002dcd30);
        jal(0x29b7a8, rg::fn_sub_1FEEC0_001feec0);
        bool mark = false;
        if (v0 == 0) {
            charge(5);
            jal(0x29b7b8, rg::fn_sub_2D1A70_002d1a70);
            v1 = li(1);
            mark = v0 == v1;
        }
        if (mark) {
            charge(8);
            gbtl(v1);
            lw(v0, v1, kFlags);
            v0 = v0 | 0x4000;
            sw(v0, v1, kFlags);
            jal(0x29b7dc, rg::fn_sub_1FF370_001ff370);
        } else {
            charge(7);
            gbtl(a0);
            lw(v1, a0, kFlags);
            v0 = li(-16385);
            v0 = v1 & v0;
            sw(v0, a0, kFlags);
            jal(0x29b800, rg::fn_sub_2D1A10_002d1a10);
        }
    }
    // both sides: the home positions
    charge(3);
    s0 = 0;
    for (;;) {
        charge(4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = s0 & 0xFFFF;
        v1 = sll(v0, 3);
        gbtl(v0);
        v0 = addu(v0, v1);
        lw(s1, v0, kSideListB);
        for (;;) {
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(15);
            a0 = s1;
            a1 = 0;
            jal(0x29b838, rg::fn_sub_2D3E00_002d3e00);
            a0 = s1;
            a1 = 0;
            a2 = addiu(sp, 112);
            a3 = 0;
            jal(0x29b850, rg::fn_sub_27F7C0_0027f7c0);
            a0 = s1;
            a1 = addiu(sp, 112);
            jal(0x29b860, rg::fn_sub_27F680_0027f680);
            lw(s1, s1, kUnitNextB);
        }
        charge(2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // the party
    charge(12);
    a0 = li(2);
    a1 = 0;
    a2 = addiu(sp, 144);
    a3 = 0;
    t0 = 0;
    t1 = li(1);
    jal(0x29b8a4, rg::fn_sub_280870_00280870);  // the party's centre -> sp+144
    gbtl(v0);
    lw(s0, v0, kSideListB);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(9);
        a0 = s0;
        jal(0x29b8c0, rg::fn_sub_287490_00287490);
        lw(a0, s0, kUnitDat);
        a1 = 0;
        jal(0x29b8d0, rg::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {  // dead: stays down
            charge(57);
            lw(a0, s0, kUnitDat);
            a1 = lui(0x8);
            jal(0x29b8e8, rg::fn_datCalcSetBadStatus_003004f0);
            lw(a0, s0, kUnitDat);
            a1 = 0;
            jal(0x29b8f8, rg::fn_datCalcSetHp_002ffd90);
            lw(v0, s0, kUnitFlags);
            v0 = v0 | 0x1;
            sw(v0, s0, kUnitFlags);
            a0 = s0;
            a1 = 0;
            jal(0x29b914, rg::fn_sub_2831C0_002831c0);
            a0 = s0;
            jal(0x29b920, rg::fn_sub_2DD960_002dd960);
            a0 = v0;
            enqueue(0x29b930, 1);
            v0 = lui(0x3F80);  // 1.0f
            mtc1(v0, F12);
            a0 = s0;
            a1 = li(18);
            a2 = 0;
            a3 = li(2);
            jal(0x29b950, rg::fn_sub_284200_00284200);
            a0 = v0;
            enqueue(0x29b960, 1);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            a0 = s0;
            a1 = li(18);
            jal(0x29b978, rg::fn_sub_2838D0_002838d0);
            a0 = s0;
            a1 = v0;
            jal(0x29b988, rg::fn_sub_284D80_00284d80);
            a0 = v0;
            enqueue(0x29b998, 1);
            a0 = s0;
            jal(0x29b9a4, rg::fn_sub_2DD8E0_002dd8e0);
            a0 = v0;
            enqueue(0x29b9b4, 1);
        } else {
            charge(5);
            gbtl(v1);
            lbu(v0, v1, kPartyCount);
            at = slti(v0, 2);
            if (at == 0) {
                charge(4);
                lw(v0, v1, kFlags2);
                v0 = v0 & 0x1;
                if (v0 == 0) {  // the walk-in from 150 units out
                    charge(77);
                    a0 = s0;
                    a1 = addiu(sp, 176);
                    a2 = 0;
                    a3 = addiu(sp, 160);
                    jal(0x29b9f8, rg::fn_sub_27F7C0_0027f7c0);
                    lwc1(F2, sp, 180);
                    swc1(F2, sp, 148);
                    lwc1(F1, sp, 176);
                    lwc1(F0, sp, 144);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 128);
                    sub_s(F0, F2, F2);
                    swc1(F0, sp, 132);
                    lwc1(F1, sp, 184);
                    lwc1(F0, sp, 152);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 136);
                    a0 = addiu(sp, 128);
                    a1 = a0;
                    jal(0x29ba38, rg::fn_sub_4C69F0_004c69f0);  // normalise
                    v0 = lui(0x4316);  // 150.0f
                    mtc1(v0, F1);
                    lwc1(F0, sp, 128);
                    mul_s(F3, F0, F1);
                    swc1(F3, sp, 128);
                    lwc1(F0, sp, 132);
                    mul_s(F2, F0, F1);
                    swc1(F2, sp, 132);
                    lwc1(F0, sp, 136);
                    mul_s(F1, F0, F1);
                    swc1(F1, sp, 136);
                    lwc1(F0, sp, 144);
                    add_s(F0, F3, F0);
                    swc1(F0, sp, 128);
                    lwc1(F0, sp, 148);
                    add_s(F0, F2, F0);
                    swc1(F0, sp, 132);
                    lwc1(F0, sp, 152);
                    add_s(F0, F1, F0);
                    swc1(F0, sp, 136);
                    a0 = s0;
                    a1 = addiu(sp, 128);
                    jal(0x29ba98, rg::fn_sub_27F650_0027f650);
                    a0 = s0;
                    a1 = addiu(sp, 176);
                    lwc1(F12, gp, -32632);
                    a2 = li(8);
                    jal(0x29bab0, rg::fn_sub_2819D0_002819d0);  // the walk
                    s1 = v0;
                    a0 = s1;
                    enqueue(0x29bac4, 1);
                    a0 = s0;
                    a1 = addiu(sp, 160);
                    a2 = 0;
                    jal(0x29bad8, rg::fn_sub_2822B0_002822b0);  // the turn, after the walk
                    a0 = v0;
                    depend(0, 4, s1);
                    enqueue(0x29baf8, 1);
                    lw(a0, s0, kUnitDat);
                    v0 = lui(0xF);
                    a1 = v0 | 0xFFFF;
                    jal(0x29bb0c, rg::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        charge(5);
                        lw(a0, s0, kUnitDat);
                        jal(0x29bb20, rg::fn_datCalcIsLowHp_0030b5e0);
                        if (v0 == 0) {  // the ready motion
                            charge(17);
                            v0 = lui(0x3F80);
                            mtc1(v0, F12);
                            a0 = s0;
                            a1 = li(16);
                            a2 = li(4);
                            a3 = 0;
                            jal(0x29bb48, rg::fn_sub_284200_00284200);
                            a0 = v0;
                            a1 = li(4);
                            sb(a1, v0, kPktWaitKind0);
                            ld(v1, s1, kPktId);
                            sd(v1, v0, kPktWaitId0);
                            sh(a1, v0, kPktTime);
                            enqueue(0x29bb6c, 1);
                        }
                    }
                }
            }
        }
        charge(1);
        lw(s0, s0, kUnitNextB);
    }
    // both sides: the auto-buff passives
    charge(3);
    s1 = 0;
    for (;;) {
        charge(4);
        v0 = s1 & 0xFFFF;
        v0 = slti(v0, 2);
        if (v0 == 0) break;
        backedge();
        charge(10);
        s4 = 0;  // 589 on the side
        s3 = 0;  // 590
        s2 = 0;  // 591
        v0 = s1 & 0xFFFF;
        s5 = sll(v0, 3);
        gbtl(v0);
        v0 = addu(v0, s5);
        lw(s0, v0, kSideListB);
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(3);
            lw(a0, s0, kUnitDat);
            if (a0 != 0) {
                charge(5);
                a1 = li(589);
                jal(0x29bbc4, rg::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    charge(1);
                    s4 = li(1);
                }
                charge(6);
                lw(a0, s0, kUnitDat);
                a1 = li(590);
                jal(0x29bbe0, rg::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    charge(1);
                    s3 = li(1);
                }
                charge(6);
                lw(a0, s0, kUnitDat);
                a1 = li(591);
                jal(0x29bbfc, rg::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    charge(1);
                    s2 = li(1);
                }
            }
            charge(1);
            lw(s0, s0, kUnitNextB);
        }
        charge(5);
        gbtl(v0);
        v0 = addu(v0, s5);
        lw(s0, v0, kSideListB);
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(3);
            lw(a0, s0, kUnitDat);
            if (a0 != 0) {
                static constexpr struct {
                    s32 skill, equip;
                    u32 link_skill, link_equip, link_apply;
                    s32 mask;
                } kBuffs[] = {{557, 180, 0x29bc40, 0x29bc58, 0x29bc80, 5},
                              {558, 181, 0x29bc90, 0x29bca8, 0x29bcd0, 64},
                              {559, 182, 0x29bce0, 0x29bcf8, 0x29bd20, 272}};
                Gpr* const side_flag[3] = {&s3, &s4, &s2};  // 590 / 589 / 591 enable the three
                for (std::size_t k = 0; k < 3; ++k) {
                    const auto& b = kBuffs[k];
                    if (k == 0) {
                        charge(5);
                    } else {
                        charge(6);
                        lw(a0, s0, kUnitDat);
                    }
                    a1 = li(b.skill);
                    jal(b.link_skill, rg::fn_datCalcHasSkill_003005e0);
                    bool apply = v0 != 0;
                    if (!apply) {
                        charge(6);
                        lw(a0, s0, kUnitDat);
                        a1 = li(b.equip);
                        jal(b.link_equip, rg::fn_datCalcCountEquipmentWithEffect_003009a0);
                        apply = v0 != 0;
                    }
                    if (!apply) {
                        charge(3);
                        v0 = li(1);
                        apply = *side_flag[k] == v0;
                    }
                    if (apply) {
                        charge(5);
                        lw(a0, s0, kUnitDat);
                        a1 = li(b.mask);
                        a2 = li(1);
                        jal(b.link_apply, rg::fn_sub_302380_00302380);
                    }
                }
                charge(4);
                lw(v1, s0, kUnitDat);
                lhu(v0, v1, 0);
                v0 = v0 & 0xFBF7;
                sh(v0, v1, 0);
            }
            charge(1);
            lw(s0, s0, kUnitNextB);
        }
        charge(2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // the ENCOUNT record's +4 / +6
    charge(11);
    gbtl(a1);
    lw(v0, a1, kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpEncountTbl);
    a0 = addu(v0, v1);
    lhu(v1, a0, 4);
    if (v1 != 0) {
        charge(3);
        lhu(v0, a0, 6);
        if (!lez(v0)) {
            charge(7);
            sh(v1, a1, 3040);
            lhu(v1, a0, 6);
            gbtl(v0);
            sw(v1, v0, 3044);
            v1 = li(1);
            gbtl(v0);
            sw(v1, v0, 3064);
        }
    }
    charge(13);
    a0 = 0;
    a1 = li(2);
    jal(0x29bdb8, rg::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    a1 = 0;
    jal(0x29bdc8, rg::fn_sub_27ED20_0027ed20);
    gbtl(v0);
    lw(v0, v0, kFlags2);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        charge(2);
        jal(0x29bde4, rg::fn_sub_2FF2F0_002ff2f0);
    }
    charge(9);
    a0 = 0;
    jal(0x29bdf0, rg::fn_sub_2BFC70_002bfc70);
    a0 = 0;
    jal(0x29bdfc, rg::fn_sub_2BFC50_002bfc50);
    v0 = li(5);
    goto out;
stay:
    charge(1);
    v0 = 0;
out:
    charge(10);
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 192);
}

// 0x29BE40 btlMainInitStateUnitLoad(state): UNIT_LOAD. Queues the appearance of every btlUnit of the all-units list
// as chains of dependent packets (+0/+8 and +16/+24: "after the packet with this id"): per unit the model load
// sub_285690(unit, unit+164, 62) after the previous unit's load (queue 1); then, unless gBtl+16 bit 0 is set, the
// unit's entry camera sub_2BB2F0(*(gp-18428), unit, 0, 0, 0) after the load and (from the second unit on) after the
// previous camera, +72 = 1 for the first unit, else 8 (4 would be left when sub_29BE40's unit count term were 0, which
// the `slti + 1` never gives), queue 2, and the appear motion sub_285D30(unit, -1, 8, 0, 3, 1) after the load and the
// camera, +72 = 29, queue 1; with bit 0 set only the motion sub_285D30(unit, -1, 0, 0, 3, 1) after the load, +72 = 2.
// Then the battle start packets after the last load: sub_2BC680 (queue 1), sub_2BFC00 after it (queue 1), and the
// battle music sub_2DBFE0(flag 321 clear) after that (queue 1).
void Cpu::unit_load_init() {
    enter(18);
    sp = addiu(sp, -128);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s5 = li(1);  // the first unit
    s2 = 0;      // the id of the previous unit's load packet
    s1 = 0;      // the id of the previous unit's camera (or motion) packet
    v1 = 0;
    gbtl(v0);
    lw(s0, v0, kSideListB + 8);  // the enemy side's units (+2612)
    a0 = s0;
    for (;;) {  // count the units (u16)
        charge(4);
        if (a0 == 0) break;
        backedge();
        charge(3);
        v0 = addiu(v1, 1);
        v1 = v0 & 0xFFFF;
        lw(a0, a0, kUnitNextB);
    }
    charge(5);
    v0 = v1 & 0xFFFF;
    v0 = slti(v0, 4);
    s6 = addiu(v0, 1);  // 1 or 2, never 0
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(19);
        a0 = s0;
        lhu(a1, s0, 164);
        a2 = li(62);
        jal(0x29bec4, rg::fn_sub_285690_00285690);  // the model load
        s4 = v0;
        v1 = li(4);
        sb(v1, v0, kPktWaitKind0);
        sd(s2, v0, kPktWaitId0);
        a0 = s4;
        enqueue(0x29bee4, 1);
        ld(s2, s4, kPktId);
        gbtl(v0);
        lw(v0, v0, kFlags2);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            charge(15);
            lw(a0, gp, -18428);
            a1 = s0;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(0x29bf18, rg::fn_sub_2BB2F0_002bb2f0);  // the entry camera
            s3 = v0;
            a0 = li(4);
            sb(a0, v0, kPktWaitKind0);
            ld(v1, s4, kPktId);
            sd(v1, v0, kPktWaitId0);
            v0 = li(1);
            if (s5 == v0) {
                charge(3);
                sh(v0, s3, kPktTime);
            } else {
                charge(5);
                v0 = li(5);
                sb(v0, s3, kPktWaitKind1);
                sd(s1, s3, kPktWaitId1);
                if (s6 != 0) {
                    charge(1);
                    a0 = li(8);
                }
                charge(1);
                sh(a0, s3, kPktTime);
            }
            charge(28);
            a0 = s3;
            enqueue(0x29bf70, 2);
            ld(s1, s3, kPktId);
            a0 = s0;
            a1 = li(-1);
            a2 = li(8);
            a3 = 0;
            t0 = li(3);
            t1 = li(1);
            jal(0x29bf94, rg::fn_sub_285D30_00285d30);  // the appear motion
            a0 = v0;
            v1 = li(4);
            sb(v1, v0, kPktWaitKind0);
            ld(v1, s4, kPktId);
            sd(v1, v0, kPktWaitId0);
            v1 = li(5);
            sb(v1, v0, kPktWaitKind1);
            sd(s1, v0, kPktWaitId1);
            v1 = li(29);
            sh(v1, v0, kPktTime);
            enqueue(0x29bfc8, 1);
        } else {
            charge(20);
            a0 = s0;
            a1 = li(-1);
            a2 = 0;
            a3 = 0;
            t0 = li(3);
            t1 = li(1);
            jal(0x29bff0, rg::fn_sub_285D30_00285d30);
            s1 = v0;
            v1 = li(4);
            sb(v1, v0, kPktWaitKind0);
            ld(v1, s4, kPktId);
            sd(v1, v0, kPktWaitId0);
            v1 = li(2);
            sh(v1, v0, kPktTime);
            a0 = s1;
            enqueue(0x29c01c, 1);
            ld(s1, s1, kPktId);
        }
        charge(2);
        s5 = 0;
        lw(s0, s0, kUnitNextB);
    }
    charge(26);
    jal(0x29c038, rg::fn_sub_2BC680_002bc680);
    s1 = v0;
    v1 = li(4);
    sb(v1, v0, kPktWaitKind0);
    sd(s2, v0, kPktWaitId0);
    a0 = s1;
    enqueue(0x29c058, 1);
    jal(0x29c060, rg::fn_sub_2BFC00_002bfc00);
    s0 = v0;
    v1 = li(4);
    sb(v1, v0, kPktWaitKind0);
    ld(v1, s1, kPktId);
    sd(v1, v0, kPktWaitId0);
    a0 = s0;
    enqueue(0x29c084, 1);
    a0 = li(321);
    jal(0x29c090, rg::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(1);
        v0 = li(1);
    }
    charge(22);
    a0 = v0 & 0xFFFF;
    jal(0x29c0b4, rg::fn_sub_2DBFE0_002dbfe0);
    a0 = v0;
    v1 = li(4);
    sb(v1, v0, kPktWaitKind0);
    ld(v1, s0, kPktId);
    sd(v1, v0, kPktWaitId0);
    enqueue(0x29c0d4, 1);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// 0x29D870 btlMainInitStateEnd(state): END. After a won battle (gBtl+28 == 1) every unit of the +336 list with a
// DatUnit gets its end-of-battle passive: 606 -> HP and SP set to their maxima; else 605 -> HP and SP + 8 % of the
// maxima (datCalcAddHp/AddSp). Then sub_2A4C50, sub_2BF650; after a win with gBtl+3104 != 0, its bits 0..3 set the
// flags 4097..4100. Every unit of the +336 list with a DatUnit loses its buffs (datCalcClearAllEffects); the party
// records 1..10 (datGetUnit) whose +16 byte is 10 or 7 -- or anything else while flag 391 is clear -- get +16 = 1;
// every btlAction not already in state 34 (EXIT) enters it; finally sub_27E4D0.
void Cpu::end_init() {
    enter(9);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    gbtl(a0);
    lhu(v1, a0, kOutcome);
    v0 = li(1);
    if (v1 == v0) {
        charge(3);
        lw(s0, a0, kSideListB);  // the party's units (+2612)
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(3);
            lw(a0, s0, kUnitDat);
            if (a0 != 0) {
                charge(5);
                a1 = li(606);
                jal(0x29d8b0, rg::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    charge(16);
                    lw(a0, s0, kUnitDat);
                    jal(0x29d8c4, rg::fn_datCalcGetMaxHp_002ffdf0);
                    lw(a0, s0, kUnitDat);
                    a1 = v0;
                    jal(0x29d8d4, rg::fn_datCalcSetHp_002ffd90);
                    lw(a0, s0, kUnitDat);
                    jal(0x29d8e0, rg::fn_datCalcGetMaxSp_00300100);
                    lw(a0, s0, kUnitDat);
                    a1 = v0;
                    jal(0x29d8f0, rg::fn_datCalcSetSp_002ffdc0);
                } else {
                    charge(6);
                    lw(a0, s0, kUnitDat);
                    a1 = li(605);
                    jal(0x29d908, rg::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        charge(30);
                        lw(a0, s0, kUnitDat);
                        jal(0x29d91c, rg::fn_datCalcGetMaxHp_002ffdf0);
                        eight_percent(a1);
                        lw(a0, s0, kUnitDat);
                        jal(0x29d94c, rg::fn_datCalcAddHp_00300410);
                        lw(a0, s0, kUnitDat);
                        jal(0x29d958, rg::fn_datCalcGetMaxSp_00300100);
                        eight_percent(a1);
                        lw(a0, s0, kUnitDat);
                        jal(0x29d988, rg::fn_datCalcAddSp_00300480);
                    }
                }
            }
            charge(1);
            lw(s0, s0, kUnitNextB);
        }
    }
    charge(8);
    jal(0x29d99c, rg::fn_sub_2A4C50_002a4c50);
    jal(0x29d9a4, rg::fn_sub_2BF650_002bf650);
    gbtl(v0);
    lw(v1, v0, kResultFlags);
    bool flags = false;
    if (v1 != 0) {
        charge(4);
        lhu(v0, v0, kOutcome);
        a1 = li(1);
        flags = v0 == a1;
    }
    if (flags) {
        charge(3);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            charge(3);
            a0 = li(4097);
            jal(0x29d9dc, rg::fn_datSetFlag_0016f1f0);  // ($a1 = 1 from the outcome compare)
        }
        static constexpr struct {
            u32 bit, flag, link;
        } kMore[] = {{0x2, 4098, 0x29da00}, {0x4, 4099, 0x29da24}, {0x8, 4100, 0x29da48}};
        for (const auto& k : kMore) {
            charge(5);
            gbtl(v0);
            lw(v0, v0, kResultFlags);
            v0 = v0 & k.bit;
            if (v0 != 0) {
                charge(4);
                a0 = li(static_cast<s32>(k.flag));
                a1 = li(1);
                jal(k.link, rg::fn_datSetFlag_0016f1f0);
            }
        }
    }
    charge(4);
    gbtl(v0);
    lw(s0, v0, kSideListB);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(3);
        lw(a0, s0, kUnitDat);
        if (a0 != 0) {
            charge(2);
            jal(0x29da6c, rg::fn_datCalcClearAllEffects_00301690);
        }
        charge(1);
        lw(s0, s0, kUnitNextB);
    }
    charge(3);
    s1 = daddiu(zero, 1);
    for (;;) {  // the party records 1..10
        charge(4);
        v0 = s1 & 0xFFFF;
        at = slti(v0, 11);
        if (at == 0) break;
        backedge();
        charge(9);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        jal(0x29da94, rg::fn_datGetUnit_0016cd60);
        s0 = v0;
        lb(v1, v0, 16);
        v0 = li(10);
        bool set = v1 == v0;
        if (!set) {
            charge(3);
            v0 = li(7);
            set = v1 == v0;
        }
        if (set) {
            charge(4);
            v0 = li(1);
            sb(v0, s0, 16);
        } else {
            charge(2);
            charge(5);
            a0 = li(391);
            jal(0x29dad8, rg::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                charge(2);
                v0 = li(1);
                sb(v0, s0, 16);
            }
        }
        charge(2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    charge(4);
    gbtl(v0);
    lw(s0, v0, kActionList);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(4);
        lhu(v0, s0, kActState);
        a1 = li(34);
        if (v0 != a1) {
            charge(3);
            a0 = s0;
            jal(0x29db2c, rg::fn_btlActionSetState_00299d60);
        }
        charge(1);
        lw(s0, s0, kActNextInList);
    }
    charge(8);
    jal(0x29db40, rg::fn_sub_27E4D0_0027e4d0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x29C700 btlMainInitStateRevival(state): REVIVAL, the revival item's scene: chains of dependent packets, all owned by
// the current action. The scene's camera set s2 = sub_2B8F90(0) with the camera data of effect 439 (sub_2BB6F0 into the
// buffer at sp+144; sub_2BAC00, queue 1), the effect 439 (sub_2DD4A0, after the camera; queue 1), the effect's
// screen work (sub_29EA60 into the words at sp+316 / sp+312 -> sub_29F4B0(..., 16); sub_29EC00 / sub_29EC80 ->
// sub_2A0050(..., 16, 0); sub_29EC50 -> sub_2A1280(..., 16); queue 1 each), the actor's camera sub_2BAF90(s2, unit,
// unit, 0, 0) after the effect (queue 2) and its sound sub_2DD5E0(0) (kind 5 after it; queue 1). Then per party unit
// (the B list +336): the 40-byte result record at sp+272 (sub_2D5DC0) gets the HP and SP missing to the maxima
// (+0 / +4) and 0x80000 at +12 when the unit is dead; its revive packet sub_2BD480(unit) (queue 1), its camera
// sub_2BAF90(s2, unit, unit, 1, 0) after the effect and the previous unit's message (queue 2), the sound
// sub_2DD5E0(1) (queue 1), the message 23 of the unit's action (sub_29A1D0) after the camera (5) and (11, +32/+40),
// +74 = 18 (queue 0, its id kept for the next unit); a dead unit with flag 0x200 its get-up motion sub_284200(unit, 19,
// 0, 0), $f12 = 1.0, (11 after the camera, queue 1); the recovery numbers sub_2D7E20(action, action, record, 1, 1)
// (11 after the camera, queue 1), then -- with HP restored -- sub_2BD230(unit, 0, 0) and always sub_2BDBD0(unit, unit,
// -1, 0, 0, 0, 1, record), both after the numbers with +71 bit 5 cleared (queue 3). Finally the effect's end
// (sub_29FA50(16), sub_2A1080(16, 0), sub_2A16C0(16), each after the last message; queue 1) and sub_2B9030(s2).
void Cpu::revival_init() {
    enter(132);
    sp = addiu(sp, -320);
    sd(ra, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    gbtl(v0);
    lw(s0, v0, kCurrentAction);
    s3 = 0;  // the id of the previous unit's message packet
    a0 = 0;
    jal(0x29c738, rg::fn_sub_2B8F90_002b8f90);
    s2 = v0;  // the camera set
    a0 = li(439);
    a1 = addiu(sp, 144);
    jal(0x29c74c, rg::fn_sub_2BB6F0_002bb6f0);
    a0 = s2;
    a1 = addiu(sp, 144);
    a2 = 0;
    jal(0x29c760, rg::fn_sub_2BAC00_002bac00);
    s1 = v0;
    stamp_owner(s0);
    a0 = s1;
    enqueue(0x29c77c, 1);
    a0 = li(439);
    a1 = 0;
    jal(0x29c78c, rg::fn_sub_2DD4A0_002dd4a0);  // the effect
    s6 = v0;
    depend(0, 4, s1);
    stamp_owner(s0);
    a0 = s6;
    enqueue(0x29c7b8, 1);
    a0 = li(439);
    a1 = addiu(sp, 316);
    a2 = addiu(sp, 312);
    jal(0x29c7cc, rg::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 316);
    lw(a1, sp, 312);
    a2 = li(16);
    jal(0x29c7e0, rg::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    stamp_owner(s0);
    enqueue(0x29c7f8, 1);
    a0 = li(439);
    jal(0x29c804, rg::fn_sub_29EC00_0029ec00);
    s1 = v0;
    a0 = li(439);
    a1 = addiu(sp, 316);
    a2 = addiu(sp, 312);
    jal(0x29c81c, rg::fn_sub_29EC80_0029ec80);
    a0 = s1;
    lw(a1, sp, 316);
    lw(a2, sp, 312);
    a3 = li(16);
    t0 = 0;
    jal(0x29c838, rg::fn_sub_2A0050_002a0050);
    a0 = v0;
    stamp_owner(s0);
    enqueue(0x29c850, 1);
    a0 = li(439);
    jal(0x29c85c, rg::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = li(16);
    jal(0x29c86c, rg::fn_sub_2A1280_002a1280);
    a0 = v0;
    stamp_owner(s0);
    enqueue(0x29c884, 1);
    lw(a1, s0, kActUnit);
    a0 = s2;
    a2 = a1;
    a3 = 0;
    t0 = 0;
    jal(0x29c8a0, rg::fn_sub_2BAF90_002baf90);  // the actor's camera
    s1 = v0;
    depend(0, 4, s6);
    stamp_owner(s0);
    a0 = s1;
    enqueue(0x29c8cc, 2);
    a0 = 0;
    jal(0x29c8d8, rg::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    depend(0, 5, s1);
    enqueue(0x29c8f8, 1);
    gbtl(v0);
    lw(s4, v0, kSideListB);  // the party's units (+2612)
    for (;;) {
        charge(2);
        if (s4 == 0) break;
        backedge();
        charge(35);
        a0 = s4;
        jal(0x29c914, rg::fn_sub_29A1D0_0029a1d0);  // the unit's btlAction
        s5 = v0;
        a0 = addiu(sp, 272);
        jal(0x29c924, rg::fn_sub_2D5DC0_002d5dc0);  // clear the result record
        lw(a0, s4, kUnitDat);
        jal(0x29c930, rg::fn_datCalcGetMaxHp_002ffdf0);
        s1 = v0 & 0xFFFF;
        lw(a0, s4, kUnitDat);
        jal(0x29c940, rg::fn_datCalcGetMaxSp_00300100);
        s7 = v0 & 0xFFFF;
        lw(a0, s4, kUnitDat);
        jal(0x29c950, rg::fn_datCalcGetHp_002ffd70);
        v1 = v0 & 0xFFFF;
        v0 = s1 & 0xFFFF;
        v0 = subu(v0, v1);
        sw(v0, sp, 272);  // HP to restore
        lw(a0, s4, kUnitDat);
        jal(0x29c96c, rg::fn_datCalcGetSp_002ffd80);
        v1 = v0 & 0xFFFF;
        v0 = s7 & 0xFFFF;
        v0 = subu(v0, v1);
        sw(v0, sp, 276);  // SP to restore
        lw(a0, s4, kUnitDat);
        a1 = 0;
        jal(0x29c98c, rg::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {
            charge(2);
            v0 = lui(0x8);
            sw(v0, sp, 284);  // the dead bit cured
        }
        charge(67);
        a0 = s4;
        jal(0x29c9a8, rg::fn_sub_2BD480_002bd480);
        a0 = v0;
        stamp_owner(s0);
        enqueue(0x29c9c0, 1);
        a0 = s2;
        a1 = s4;
        a2 = s4;
        a3 = li(1);
        t0 = 0;
        jal(0x29c9dc, rg::fn_sub_2BAF90_002baf90);
        s1 = v0;
        a0 = li(4);
        sb(a0, v0, kPktWaitKind0);
        ld(v1, s6, kPktId);
        sd(v1, v0, kPktWaitId0);
        sb(a0, v0, kPktWaitKind1);
        sd(s3, v0, kPktWaitId1);
        stamp_owner(s0);
        a0 = s1;
        enqueue(0x29ca10, 2);
        a0 = li(1);
        jal(0x29ca1c, rg::fn_sub_2DD5E0_002dd5e0);
        a0 = v0;
        depend(0, 5, s1);
        enqueue(0x29ca3c, 1);
        a0 = s5;
        a1 = li(23);
        jal(0x29ca4c, rg::fn_sub_2A3B40_002a3b40);
        s3 = v0;
        depend(0, 5, s1);
        depend(2, 11, s1);
        v1 = li(18);
        sh(v1, v0, 74);
        stamp_owner(s0);
        a0 = s3;
        a1 = 0;
        jal(0x29ca90, rg::fn_sub_27ED20_0027ed20);
        ld(s3, s3, kPktId);
        lw(v1, sp, 284);
        v0 = lui(0x8);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(4);
            lw(v0, s4, kUnitFlags);
            v0 = v0 & 0x200;
            if (v0 != 0) {
                charge(18);
                v0 = lui(0x3F80);  // 1.0f
                mtc1(v0, F12);
                a0 = s4;
                a1 = li(19);
                a2 = 0;
                a3 = 0;
                jal(0x29cad8, rg::fn_sub_284200_00284200);
                a0 = v0;
                depend(0, 11, s1);
                stamp_owner(s0);
                enqueue(0x29cb00, 1);
            }
        }
        charge(21);
        a0 = s5;
        a1 = s5;
        a2 = addiu(sp, 272);
        a3 = li(1);
        t0 = a3;
        jal(0x29cb1c, rg::fn_sub_2D7E20_002d7e20);  // the recovery numbers
        s5 = v0;
        depend(0, 11, s1);
        stamp_owner(s0);
        a0 = s5;
        enqueue(0x29cb48, 1);
        lw(v0, sp, 272);
        if (v0 != 0) {
            charge(16);
            a0 = s4;
            a1 = 0;
            a2 = 0;
            jal(0x29cb68, rg::fn_sub_2BD230_002bd230);
            a0 = v0;
            depend(0, 4, s5);
            lbu(v1, v0, 71);
            v1 = v1 & 0xDF;
            sb(v1, v0, 71);
            enqueue(0x29cb94, 3);
        }
        charge(22);
        a0 = s4;
        a1 = s4;
        a2 = li(-1);
        a3 = 0;
        t0 = 0;
        t1 = 0;
        t2 = li(1);
        t3 = addiu(sp, 272);
        jal(0x29cbbc, rg::fn_sub_2BDBD0_002bdbd0);
        a0 = v0;
        depend(0, 4, s5);
        lbu(v1, v0, 71);
        v1 = v1 & 0xDF;
        sb(v1, v0, 71);
        enqueue(0x29cbe8, 3);
        lw(s4, s4, kUnitNextB);
    }
    charge(52);
    a0 = li(16);
    jal(0x29cc00, rg::fn_sub_29FA50_0029fa50);
    a0 = v0;
    depend_id(0, 4, s3);
    stamp_owner(s0);
    enqueue(0x29cc24, 1);
    a0 = li(16);
    a1 = 0;
    jal(0x29cc34, rg::fn_sub_2A1080_002a1080);
    a0 = v0;
    depend_id(0, 4, s3);
    stamp_owner(s0);
    enqueue(0x29cc58, 1);
    a0 = li(16);
    jal(0x29cc64, rg::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    depend_id(0, 4, s3);
    stamp_owner(s0);
    enqueue(0x29cc88, 1);
    a0 = s2;
    jal(0x29cc94, rg::fn_sub_2B9030_002b9030);
    ld(ra, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 320);
}

// 0x29D1F0 btlMainInitStateCondition(state): CONDITION, the party's daily condition after the battle (sub_16C920
// reads a character's condition 0..5, sub_16D6B0 sets it). Nothing with flag 370. First pass over the party (B list
// +336): when sub_17D800() is 0 a character whose condition is not 5, 4 or 3 gets sub_16CA90(character, -1); the living
// ones in condition 5 are counted, and with any of them a 10 % roll (datCalcRand(100) < 10, then datCalcRand(count))
// sets the "recovery" word at sp+160. Second pass, until one changes: a living character's new condition by its old
// one (the jump table 0x7B7C30): 0..2 -> 3 when sub_16C9F0(character) is 0, then with the recovery word a roll against
// 25 / 10 / 5 / 60 % (old 0 / 1 / 2 / 3) -> 5 unless the stored condition is 3; 4 -> a roll against 10 +
// sub_17B170() % -> 5 unless 3; 5 stays. The first character whose condition changes gets it (sub_16D6B0), and its
// scene is queued: message 33 of its action (+72 = 8, queue 0), sub_2BC7E0(8), its motion sub_284200(unit, 3, 0, 1)
// ($f12 = 1.0) and the effect sub_2DD100(14, 2, 9) after the message (kind 5, queue 1 each), and by the new condition
// (the jump table 0x7B7C10: 3 -> 18 / 19, 4 and 5 -> 16 / 18; 0..2 leave s5 / s7 as the caller had them) the camera
// sub_2E2BE0(action, s7, 0, 0, 0) after the message and the sound sub_2DB740(action, s5, 0, 0, 1) after the camera.
void Cpu::condition_init() {
    enter(18);
    sp = addiu(sp, -176);
    sd(ra, sp, 144);
    sq(s8, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = 0;             // the unit whose condition changed
    sw(zero, sp, 160);  // the recovery word
    a0 = li(370);
    jal(0x29d228, rg::fn_datGetFlag_0016f190);
    if (v0 != 0) goto out;
    // first pass
    charge(5);
    s2 = 0;  // living characters in condition 5
    gbtl(v1);
    lw(s3, v1, kSideListB);
    for (;;) {
        charge(2);
        if (s3 == 0) break;
        backedge();
        charge(11);
        lw(v0, s3, kUnitDat);
        lh(v0, v0, 2);
        s4 = v0;  // the character
        a0 = s4;
        jal(0x29d25c, rg::fn_sub_16C920_0016c920);
        s6 = v0 & 0xFFFF;
        jal(0x29d268, rg::fn_sub_17D800_0017d800);
        if (v0 == 0) {
            charge(4);
            v1 = s6 & 0xFFFF;
            v0 = li(5);
            bool keep = v1 == v0;
            if (!keep) {
                charge(3);
                v0 = li(4);
                keep = v1 == v0;
            }
            if (!keep) {
                charge(3);
                v0 = li(3);
                keep = v1 == v0;
            }
            if (!keep) {
                charge(4);
                a0 = s4;
                a1 = li(-1);
                jal(0x29d2a8, rg::fn_sub_16CA90_0016ca90);
            }
        }
        charge(6);
        lw(a0, s3, kUnitDat);
        a1 = 0;
        jal(0x29d2b8, rg::fn_datCalcIsDead_0030b5a0);
        if (v0 == 0) {
            charge(4);
            a0 = s6 & 0xFFFF;
            v1 = li(5);
            if (a0 == v1) {
                charge(2);
                v1 = addiu(s2, 1);
                s2 = v1 & 0xFFFF;
            }
        }
        charge(1);
        lw(s3, s3, kUnitNextB);
    }
    charge(3);
    v1 = s2 & 0xFFFF;
    if (!lez(v1)) {
        charge(6);
        a0 = li(100);
        jal(0x29d2fc, rg::fn_datCalcRand_002ffbc0);
        at = slti(v0, 10);
        if (at != 0) {
            charge(5);
            a0 = s2 & 0xFFFF;
            jal(0x29d314, rg::fn_datCalcRand_002ffbc0);
            v1 = li(1);
            sw(v1, sp, 160);
        }
    }
    // second pass: the first character whose condition changes
    charge(4);
    gbtl(v1);
    lw(s3, v1, kSideListB);
    for (;;) {
        charge(2);
        if (s3 == 0) break;
        backedge();
        charge(14);
        lw(v0, s3, kUnitDat);
        lhu(s6, v0, 2);
        s4 = dsll32(s6, 16);
        s4 = dsra32(s4, 16);
        a0 = s4;
        jal(0x29d348, rg::fn_sub_16C920_0016c920);
        s0 = v0 & 0xFFFF;  // the new condition (starts as the old one)
        lw(a0, s3, kUnitDat);
        a1 = 0;
        jal(0x29d35c, rg::fn_datCalcIsDead_0030b5a0);
        if (v0 == 0) {
            charge(4);
            s2 = s0 & 0xFFFF;  // the old condition
            at = sltiu(s2, 6);
            if (at != 0) {
                charge(7);
                a0 = lui(0x7B);
                a0 = addiu(a0, 0x7C30);
                v1 = sll(s2, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (static_cast<u32>(v1)) {
                case 0x29d398u:  // 0..2
                    charge(6);
                    a0 = s4;
                    jal(0x29d39c, rg::fn_sub_16C9F0_0016c9f0);
                    v1 = v0 & 0xFFFF;
                    if (v1 == 0) {
                        charge(1);
                        s0 = daddiu(zero, 3);
                    }
                    [[fallthrough]];
                case 0x29d3b4u:  // 3
                    charge(3);
                    lw(v1, sp, 160);
                    if (v1 != 0) {
                        charge(3);
                        v1 = li(3);
                        if (s2 == v1) {
                            charge(3);
                            v1 = daddiu(zero, 60);
                        } else if (charge(3), v1 = li(2), s2 == v1) {
                            charge(3);
                            v1 = daddiu(zero, 5);
                        } else if (charge(3), v1 = li(1), s2 == v1) {
                            charge(3);
                            v1 = daddiu(zero, 10);
                        } else if (charge(2), s2 == 0) {
                            charge(3);
                            v1 = daddiu(zero, 25);
                        } else {
                            charge(2);
                            charge(1);
                            v1 = 0;
                        }
                        charge(3);
                        s8 = v1 & 0xFFFF;  // the recovery chance
                        if (!lez(s8)) {
                            charge(6);
                            a0 = li(100);
                            jal(0x29d438, rg::fn_datCalcRand_002ffbc0);
                            at = slt(v0, s8);
                            if (at != 0) {
                                charge(4);
                                a0 = s6 & 0xFFFF;
                                v1 = li(3);
                                if (a0 != v1) {
                                    charge(3);
                                    s0 = daddiu(zero, 5);
                                }
                            }
                        }
                    }
                    break;
                case 0x29d468u:  // 4
                    charge(13);
                    s8 = daddiu(zero, 10);
                    jal(0x29d46c, rg::fn_sub_17B170_0017b170);
                    v0 = v0 & 0xFFFF;
                    v0 = addu(s8, v0);
                    s8 = v0 & 0xFFFF;
                    a0 = li(100);
                    jal(0x29d484, rg::fn_datCalcRand_002ffbc0);
                    v1 = s8 & 0xFFFF;
                    at = slt(v0, v1);
                    if (at != 0) {
                        charge(4);
                        a0 = s6 & 0xFFFF;
                        v1 = li(3);
                        if (a0 != v1) {
                            charge(1);
                            s0 = daddiu(zero, 5);
                        }
                    }
                    break;
                case 0x29d4b0u:  // 5
                    break;
                default:
                    jr_unknown(v1);
                    return;
                }
            }
            charge(3);
            v1 = s0 & 0xFFFF;
            if (v1 != s2) {
                charge(7);
                s1 = s3;
                a0 = s4;
                a1 = s0;
                jal(0x29d4c8, rg::fn_sub_16D6B0_0016d6b0);
                break;
            }
        }
        charge(1);
        lw(s3, s3, kUnitNextB);
    }
    charge(2);
    if (s1 == 0) goto out;
    // the scene of the character whose condition changed
    charge(61);
    a0 = s1;
    jal(0x29d4f0, rg::fn_sub_29A1D0_0029a1d0);
    s3 = v0;  // its action
    a0 = s3;
    a1 = li(33);
    jal(0x29d504, rg::fn_sub_2A3B40_002a3b40);
    s2 = v0;
    stamp_owner(s3);
    v1 = li(8);
    sh(v1, v0, kPktTime);
    a0 = s2;
    a1 = 0;
    jal(0x29d528, rg::fn_sub_27ED20_0027ed20);
    a0 = li(8);
    jal(0x29d534, rg::fn_sub_2BC7E0_002bc7e0);
    a0 = v0;
    depend(0, 5, s2);
    enqueue(0x29d554, 1);
    v0 = lui(0x3F80);  // 1.0f
    mtc1(v0, F12);
    a0 = s1;
    a1 = li(3);
    a2 = 0;
    a3 = li(1);
    jal(0x29d574, rg::fn_sub_284200_00284200);
    a0 = v0;
    depend(0, 5, s2);
    enqueue(0x29d594, 1);
    a0 = li(14);
    a1 = li(2);
    a2 = li(9);
    jal(0x29d5a8, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 5, s2);
    enqueue(0x29d5c8, 1);
    v0 = s0 & 0xFFFF;
    at = sltiu(v0, 6);
    if (at != 0) {
        charge(7);
        v1 = lui(0x7B);
        v1 = addiu(v1, 0x7C10);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (static_cast<u32>(v0)) {
        case 0x29d5fcu:  // 3
            charge(4);
            s5 = li(18);
            s7 = li(19);
            break;
        case 0x29d60cu:  // 4
            charge(4);
            s5 = li(16);
            s7 = li(18);
            break;
        case 0x29d61cu:  // 5
            charge(2);
            s5 = li(16);
            s7 = li(18);
            break;
        case 0x29d624u:  // 0..2
            break;
        default:
            jr_unknown(v0);
            return;
        }
    }
    charge(31);
    a1 = s7 & 0xFFFF;
    a0 = s3;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(0x29d638, rg::fn_sub_2E2BE0_002e2be0);
    s0 = v0;
    depend(0, 5, s2);
    a0 = s0;
    enqueue(0x29d65c, 1);
    a1 = s5 & 0xFFFF;
    a0 = s3;
    a2 = 0;
    a3 = 0;
    t0 = li(1);
    jal(0x29d678, rg::fn_sub_2DB740_002db740);
    a0 = v0;
    depend(0, 4, s0);
    enqueue(0x29d698, 1);
out:
    charge(13);
    ld(ra, sp, 144);
    lq(s8, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 176);
}

// =====================================================================================================================
// btlAction states ($a0 = the btlAction)
// =====================================================================================================================

// --- ATTACK -----------------------------------------------------------------------------------------------------------
// The frame of btlActionUpdateStateAttack (704 bytes; the compiled code keeps its locals there, quadwords spilled
// with `sq` and read back with `lq`): offsets from the lowered $sp.
namespace atk {
constexpr s32 kGuardTime = 176;   // q: the guard's delay
constexpr s32 kHitLen = 192;      // q: this hit's motion length + the step
constexpr s32 kRec = 208;         // q: the current 28-byte result record (target +200 + 28 k)
constexpr s32 kWeapon3 = 224;     // q: 3 * the held weapon type
constexpr s32 kWeapon = 240;      // q: the held weapon type
constexpr s32 kWeak = 256;        // q: target +206 & 6 (a weakness / technical hit)
constexpr s32 kCritical = 272;    // q: target +232 & 0x100000
constexpr s32 kHitsMax = 288;     // q: sub_308F80(actor) or 1
constexpr s32 kHits = 304;        // q: hits per record (target +201, or 1)
constexpr s32 kRecords = 320;     // q: result records (target +200)
constexpr s32 kQuick = 336;       // q: the action's +24 bit 14 (no animation)
constexpr s32 kCamera = 352;      // w: the per-hit camera wanted
constexpr s32 kStrikeTbl = 380;   // w: the strike timing table (sub_283FE0) or 0
constexpr s32 kEffA = 384;        // h: an effect argument (-1 = none)
constexpr s32 kEffB = 400;        // h: an effect argument (-1 = none)
constexpr s32 kEff2 = 430;        // h
constexpr s32 kCamFinal = 432;    // h: the final camera index
constexpr s32 kNumTime = 448;     // h: the result numbers' time
constexpr s32 kTime = 464;        // h: the accumulated hit time
constexpr s32 kDelay = 480;       // h
constexpr s32 kCross = 496;       // w: target +208 set and the victim on the other side
constexpr s32 kReaction = 512;    // w: the victim's reaction motion
constexpr s32 kStrikeStep = 528;  // w
constexpr s32 kStrikes = 544;     // w: strikes per hit
constexpr s32 kNextDelay = 560;   // w: the next hit's delay (4 by default)
constexpr s32 kRecIndex = 576;    // w: k
constexpr s32 kFirstId = 600;     // d: the id of the first strike's reaction packet
constexpr s32 kLastId = 608;      // d: the id of the last reaction packet
constexpr s32 kMotionTbl = 624;   // w: the actor's 8-byte motion records per hit
constexpr s32 kHitPkt = 652;      // w: the hit's motion packet
constexpr s32 kResult = 656;      // the 40-byte result record (sub_2D5DC0)
constexpr s32 kCam0 = 702, kCam1 = 700, kCam2 = 698, kCam3 = 696;  // h: the camera indices of sub_28A540
}  // namespace atk

void Cpu::attack_camera(s32 off, u32 link, u32 link_queue) {
    lh(v0, sp, off);
    v1 = sll(v0, 2);
    gbtl(v0);
    v0 = addu(v0, v1);
    lw(a0, v0, kCameraTbl);
    lw(a1, s4, kActUnit);
    lw(a2, s6, kActUnit);
    a3 = li(1);
    t0 = 0;
    jal(link, rg::fn_sub_2BAF90_002baf90);
    a0 = v0;
    depend(0, 5, s2);
    a1 = li(2);
    jal(link_queue, rg::fn_sub_27ED20_0027ed20);
}

// 0x28EB50 btlActionUpdateStateAttack(action): ATTACK, the normal attack, played out in one frame as packets (then ->
// PACKET 30, or BAD DAMAGE 25 when sub_2DC130 says so). datCalcDamage / datCalcCheckHit have already filled the target's
// result block (the first chosen target s3 = +56: +200 records, +201 hits, +204 / +206 result flags, +208 / +212
// counter flags, +224 damage, +232 status bits, 28-byte records from +200 with +248 reaction / +250 flags). The victim
// s6 is the target, or the actor itself for a counter (+212). Per record and per hit: the actor's swing motion (the
// weapon's motion table: the hero by weapon type at *(gp-18476), the others by id at *(gp-18472), enemies gp-26568;
// SKILL.TBL-like overrides for the ids 8 / 7 / 4), the first-hit messages (critical 12 / weak 13 / 11 / 10), the camera
// set of sub_28A540, a guard sequence for a blocked record (+250 bit 2); per strike the victim's reaction (+248), the
// intermediate damage numbers (the damage per hit F22 accumulated in F21), the counter / repel effects, and the camera
// cuts; per record the result numbers sub_2D7E20, the down / knock-back / status packets and the enemy-side reaction
// sounds and cameras.
void Cpu::attack_update() {
    enter(30);
    sp = addiu(sp, -704);
    sd(ra, sp, 160);
    sq(s8, sp, 144);
    sq(s7, sp, 128);
    sq(s6, sp, 112);
    sq(s5, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a0;  // the action
    jal(0x28eb8c, rg::fn_sub_28A780_0028a780);
    ld(s0, s4, kActUid);  // the owner uid of every packet
    sd(zero, sp, atk::kLastId);
    sh(zero, sp, atk::kNumTime);
    sd(zero, sp, atk::kFirstId);
    v0 = li(-1);
    sh(v0, sp, atk::kEffB);
    sh(v0, sp, atk::kEffA);
    lhu(v0, s4, kActFlags);
    v0 = v0 & 0x4000;
    v0 = sltu(zero, v0);
    sq(v0, sp, atk::kQuick);
    if (v0 != 0) {
        charge(4);
        v0 = lui(0x3FE0);  // 1.75f: the motion speed
        mtc1(v0, F20);
    } else {
        charge(2);
        v0 = lui(0x3F80);  // 1.0f
        mtc1(v0, F20);
    }
    charge(5);
    lw(s7, s4, kActUnit);  // the actor's unit
    lw(s3, s4, kActTarget);  // the target
    lw(v0, s3, 212);
    if (v0 != 0) {
        charge(3);
        s6 = s4;  // a counter: the actor is hit
    } else {
        charge(1);
        s6 = s3;
    }
    charge(3);
    lw(v0, s3, 208);
    bool cross = false;
    if (v0 != 0) {
        charge(5);
        lbu(v1, s7, kUnitSide);
        lw(v0, s6, kActUnit);
        lbu(v0, v0, kUnitSide);
        cross = v1 != v0;
    }
    if (cross) {
        charge(4);
        v0 = li(1);
        sw(v0, sp, atk::kCross);
    } else {
        charge(1);
        sw(zero, sp, atk::kCross);
    }
    charge(24);
    a0 = s7;
    lhu(a1, s4, kActSkill);
    jal(0x28ec40, rg::fn_sub_2BD590_002bd590);
    a0 = v0;
    a1 = li(3);
    jal(0x28ec50, rg::fn_sub_27ED20_0027ed20);
    lw(a0, s4, kActUnit);
    lw(a1, s3, kActUnit);
    a2 = 0;
    jal(0x28ec64, rg::fn_sub_282650_00282650);  // face the target
    a0 = v0;
    sd(s0, v0, kPktOwner);
    a1 = 0;
    jal(0x28ec78, rg::fn_sub_27ED20_0027ed20);
    sh(zero, sp, atk::kTime);
    lbu(v0, s3, 200);
    sq(v0, sp, atk::kRecords);
    lq(v0, sp, atk::kQuick);
    if (v0 != 0) {
        charge(4);
        v0 = li(1);
        sq(v0, sp, atk::kHits);
    } else {
        charge(2);
        lbu(v0, s3, 201);
        sq(v0, sp, atk::kHits);
    }
    charge(3);
    lq(v0, sp, atk::kQuick);
    if (v0 != 0) {
        charge(4);
        v0 = li(1);
        sq(v0, sp, atk::kHitsMax);
    } else {
        charge(5);
        lw(a0, s7, kUnitDat);
        jal(0x28ecd0, rg::fn_sub_308F80_00308f80);
        v0 = v0 & 0xFF;
        sq(v0, sp, atk::kHitsMax);
    }
    charge(12);
    lwc1(F0, s3, 224);
    cvt_s_w(F1, F0);
    lq(v0, sp, atk::kHits);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    div_s(F22, F1, F0);  // the damage per hit
    mtc1(zero, F21);     // the damage shown so far
    lhu(v0, s3, 206);
    v0 = v0 & 0x6;
    if (v0 != 0) {
        charge(2);
        lwc1(F0, gp, -31844);
        mul_s(F22, F22, F0);
    }
    charge(15);
    lw(a0, s6, kActUnit);
    jal(0x28ed1c, rg::fn_sub_2BD480_002bd480);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    a1 = li(1);
    jal(0x28ed30, rg::fn_sub_27ED20_0027ed20);
    lw(a0, s7, kUnitDat);
    jal(0x28ed3c, rg::fn_datCalcGetHeldWeaponType_00308c60);
    s1 = v0 & 0xFF;
    lbu(v0, s7, kUnitSide);
    if (v0 == 0) {
        charge(4);
        lhu(v1, s7, 164);
        v0 = li(1);
        if (v1 == v0) {  // the hero: by weapon type
            charge(7);
            v0 = s1 & 0xFF;
            v1 = sll(v0, 3);
            lw(v0, gp, -18476);
            v0 = addu(v0, v1);
            sw(v0, sp, atk::kMotionTbl);
        } else {  // the others: by id
            charge(7);
            v0 = addiu(v1, -2);
            v1 = sll(v0, 3);
            lw(v0, gp, -18472);
            v0 = addu(v0, v1);
            sw(v0, sp, atk::kMotionTbl);
        }
    } else {
        charge(2);
        v0 = addiu(gp, -26568);
        sw(v0, sp, atk::kMotionTbl);
    }
    charge(14);
    lw(v1, s3, 232);
    v0 = lui(0x10);
    v0 = v1 & v0;
    v0 = sltu(zero, v0);
    sq(v0, sp, atk::kCritical);
    lhu(v0, s3, 206);
    v0 = v0 & 0x6;
    v0 = sltu(zero, v0);
    sq(v0, sp, atk::kWeak);
    a0 = s4;
    jal(0x28edcc, rg::fn_sub_28A0F0_0028a0f0);
    if (v0 != 0) {
        charge(4);
        v1 = li(1);
        lq(v0, sp, atk::kQuick);
        bool msg = v0 == v1;
        if (!msg) {
            charge(3);
            lq(v0, sp, atk::kWeak);
            if (v0 == 0) {
                charge(3);
                lq(v0, sp, atk::kCritical);
                msg = v0 == 0;
            }
        }
        if (msg) {
            charge(9);
            a0 = s4;
            a1 = li(11);
            jal(0x28ee0c, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            sd(s0, v0, kPktOwner);
            a1 = 0;
            jal(0x28ee20, rg::fn_sub_27ED20_0027ed20);
        }
    }
    charge(14);
    a0 = 0;
    lw(a1, s3, kActUnit);
    a2 = li(3);
    jal(0x28ee34, rg::fn_sub_2886E0_002886e0);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    a1 = li(1);
    jal(0x28ee48, rg::fn_sub_27ED20_0027ed20);
    lhu(v0, s3, 250);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        charge(10);
        lw(a0, s3, kActUnit);
        lw(a1, s4, kActUnit);
        a2 = 0;
        jal(0x28ee6c, rg::fn_sub_2886E0_002886e0);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        a1 = li(1);
        jal(0x28ee80, rg::fn_sub_27ED20_0027ed20);
    }
    charge(21);
    lw(a0, s4, kActUnit);
    a1 = 0;
    jal(0x28ee90, rg::fn_sub_288950_00288950);
    a0 = v0;
    stamp_owner(s4);
    a1 = li(1);
    jal(0x28eea8, rg::fn_sub_27ED20_0027ed20);
    lhu(v0, s4, kActFlags);
    v0 = v0 | 0x200;
    sh(v0, s4, kActFlags);
    sw(zero, sp, atk::kRecIndex);
    v0 = s1 & 0xFF;
    sq(v0, sp, atk::kWeapon);
    v1 = sll(v0, 1);
    v0 = addu(v1, v0);
    sq(v0, sp, atk::kWeapon3);
    for (;;) {  // the result records
        charge(5);
        lw(v1, sp, atk::kRecIndex);
        lq(v0, sp, atk::kRecords);
        v0 = slt(v1, v0);
        if (v0 == 0) break;
        backedge();
        charge(11);
        v0 = li(4);
        sw(v0, sp, atk::kNextDelay);
        s5 = 0;  // the hit
        lw(v0, sp, atk::kRecIndex);
        v1 = sll(v0, 3);
        v0 = subu(v1, v0);
        v0 = sll(v0, 2);
        v0 = addu(s3, v0);
        sq(v0, sp, atk::kRec);
        for (;;) {  // the hits
            charge(4);
            lq(v0, sp, atk::kHits);
            v0 = slt(s5, v0);
            if (v0 == 0) break;
            backedge();
            attack_hit();
            charge(1);
            s5 = addiu(s5, 1);
        }
        attack_record_end();
    }
    charge(5);
    a0 = s4;
    jal(0x290b18, rg::fn_sub_2DC130_002dc130);
    if (v0 != 0) {
        charge(6);
        a0 = s4;
        a1 = li(25);
        jal(0x290b30, rg::fn_btlActionSetState_00299d60);
    } else {
        charge(4);
        lhu(v1, s4, kActMoveKind);
        v0 = li(2);
        bool kind = v1 == v0;
        if (!kind) {
            charge(3);
            v0 = li(3);
            kind = v1 == v0;
        }
        if (!kind) {
            charge(3);
            v0 = li(1);
            kind = v1 == v0;
        }
        if (kind) {
            charge(3);
            a1 = daddiu(zero, 30);
        } else {
            charge(2);
            charge(1);
            a1 = daddiu(zero, 30);
        }
        charge(3);
        a0 = s4;
        jal(0x290b84, rg::fn_btlActionSetState_00299d60);
    }
    charge(16);
    ld(ra, sp, 160);
    lq(s8, sp, 144);
    lq(s7, sp, 128);
    lq(s6, sp, 112);
    lq(s5, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 704);
}

// One hit (s5) of the current record: the actor's swing motion s1 (+250 bit 2 blocked -> 11; an enemy by
// sub_2F8EB0(unit, skill), -1 -> 4; a party member by its weapon's swing table *(gp-18540) [3 * weapon + hit] +24,
// with the ids 8 / 7 / 4 / 1 overriding on a technical record (+204 bit 2), and weapon type 7 by sub_3093A0 with the
// effects 12 / 13 / 14); the strike timing (motions 4..6: sub_283FE0 table, sub_283E40 step, sub_283C70 strikes; else
// one strike), its start time s8 (sub_2835E0 or the table) + the delay, the swing packet sub_284200 (kept at sp+652),
// the first hit's messages, the camera set, the hit's length and the victim's delay, the guard sequence of a blocked
// record, then each strike.
void Cpu::attack_hit() {
    charge(7);
    v0 = li(1);
    sw(v0, sp, atk::kCamera);
    lq(v0, sp, atk::kRec);
    lhu(v0, v0, 250);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        charge(1);
        s1 = li(11);
    } else {
        charge(3);
        lbu(v0, s7, kUnitSide);
        if (v0 != 0) {  // an enemy
            charge(9);
            lh(a1, s4, kActSkill);
            lw(a0, s4, kActUnit);
            jal(0x28f070, rg::fn_sub_2F8EB0_002f8eb0);
            s1 = sx16(v0);
            v0 = li(-1);
            if (s1 == v0) {
                charge(3);
                s1 = li(4);
            }
        } else {
            charge(4);
            a0 = li(7);
            lq(v0, sp, atk::kWeapon);
            if (v0 == a0) {  // weapon type 7
                charge(9);
                v0 = li(2);
                sh(v0, sp, atk::kEffB);
                lw(a0, s7, kUnitDat);
                jal(0x28eff4, rg::fn_sub_3093A0_003093a0);
                v1 = v0 & 0xFF;
                v0 = li(1);
                s32 motion = 4, eff = 12;
                if (v1 != v0) {
                    charge(3);
                    v0 = li(3);
                    if (v1 == v0) {
                        motion = 6;
                        eff = 14;
                    } else {
                        charge(3);
                        v0 = li(2);
                        if (v1 == v0) {
                            motion = 5;
                            eff = 13;
                        } else {
                            charge(2);
                        }
                    }
                }
                charge(5);
                s1 = li(motion);
                v0 = li(eff);
                sh(v0, sp, atk::kEffA);
            } else {
                charge(9);
                lw(v1, gp, -18540);
                lq(v0, sp, atk::kWeapon3);
                v0 = addu(v0, v1);
                v0 = addu(v0, s5);
                lbu(s1, v0, 24);
                lhu(v0, s3, 204);
                v0 = v0 & 0x4;
                if (v0 != 0) {
                    charge(4);
                    lhu(v1, s7, 164);
                    v0 = li(8);
                    if (v1 == v0) {
                        charge(3);
                        s1 = li(5);
                    } else {
                        charge(2);
                        if (v1 == a0) {  // 7
                            charge(3);
                            s1 = li(5);
                        } else {
                            charge(3);
                            v0 = li(4);
                            if (v1 == v0) {
                                charge(3);
                                s1 = li(6);
                            } else {
                                charge(3);
                                lw(v0, sp, atk::kCamera);  // 1
                                if (v1 == v0) {
                                    charge(7);
                                    lw(a0, s7, kUnitDat);
                                    jal(0x28efa0, rg::fn_datCalcGetHeldWeaponType_00308c60);
                                    v1 = v0 & 0xFF;
                                    v0 = li(3);
                                    if (v1 == v0) {
                                        charge(3);
                                        s1 = li(5);
                                    }
                                } else {
                                    charge(2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // the strike timing of the swing motion s1
    charge(3);
    v0 = li(6);
    bool timed = s1 == v0;
    if (!timed) {
        charge(3);
        v0 = li(5);
        timed = s1 == v0;
    }
    if (!timed) {
        charge(3);
        v0 = li(4);
        timed = s1 == v0;
    }
    if (timed) {
        charge(7);
        a1 = s1 & 0xFFFF;
        a0 = s7;
        jal(0x28f0d0, rg::fn_sub_283FE0_00283fe0);
        sw(v0, sp, atk::kStrikeTbl);
        if (v0 == 0) {
            charge(9);
            a1 = s1 & 0xFFFF;
            a0 = s7;
            jal(0x28f0ec, rg::fn_sub_283E40_00283e40);
            v0 = sx16(v0);
            sw(v0, sp, atk::kStrikeStep);
        } else {
            charge(1);
            sw(zero, sp, atk::kStrikeStep);
        }
        charge(9);
        a1 = s1 & 0xFFFF;
        a0 = s7;
        jal(0x28f114, rg::fn_sub_283C70_00283c70);
        v0 = sx16(v0);
        sw(v0, sp, atk::kStrikes);
    } else {
        charge(2);
        charge(4);
        sw(zero, sp, atk::kStrikeTbl);
        sw(zero, sp, atk::kStrikeStep);
        v0 = li(1);
        sw(v0, sp, atk::kStrikes);
    }
    charge(3);
    lw(v0, sp, atk::kStrikeTbl);
    if (v0 == 0) {
        charge(9);
        a1 = s1 & 0xFFFF;
        lw(a0, s4, kActUnit);
        mov_s(F12, F20);
        jal(0x28f158, rg::fn_sub_2835E0_002835e0);
        s8 = sx16(v0);
    } else {
        charge(1);
        lh(s8, v0, 0);
    }
    charge(5);
    lw(v0, sp, atk::kNextDelay);
    s8 = addu(s8, v0);  // the first strike's time
    v0 = li(11);
    if (s1 == v0) {
        charge(3);
        v1 = li(2);
    } else {
        charge(2);
        charge(1);
        v1 = 0;
    }
    charge(20);
    a1 = sx16(s1);
    lhu(v0, sp, atk::kNextDelay);
    a2 = v0;
    a3 = v1 & 0xFFFF;
    lw(a0, s4, kActUnit);
    mov_s(F12, F20);
    jal(0x28f1bc, rg::fn_sub_284200_00284200);  // the swing
    sw(v0, sp, atk::kHitPkt);
    lh(v1, sp, atk::kTime);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = v0;
    a1 = li(1);
    jal(0x28f1dc, rg::fn_sub_27ED20_0027ed20);
    // the first hit's messages
    lw(v0, sp, atk::kRecIndex);
    if (v0 == 0) {
        charge(2);
        if (s5 == 0) {
            charge(4);
            v1 = li(1);
            lq(v0, sp, atk::kWeak);
            bool special = v0 == v1;
            if (!special) {
                charge(3);
                lq(v0, sp, atk::kCritical);
                special = v0 == v1;
            }
            if (special) {
                charge(3);
                lq(v0, sp, atk::kQuick);
                if (v0 == 0) {
                    charge(3);
                    lbu(v0, s7, kUnitSide);
                    if (v0 == 0) {
                        charge(3);
                        lq(v0, sp, atk::kCritical);
                        if (v0 != 0) {
                            charge(17);
                            v0 = lui(0x43C8);  // 400.0f
                            mtc1(v0, F12);
                            a0 = s7;
                            lw(a1, s3, kActUnit);
                            a2 = li(3);
                            jal(0x28f24c, rg::fn_sub_2B7BD0_002b7bd0);
                            a0 = v0;
                            depend_at(0, 5, atk::kHitPkt);
                            sd(s0, v0, kPktOwner);
                            a1 = 0;
                            jal(0x28f274, rg::fn_sub_27ED20_0027ed20);
                        }
                        charge(16);
                        a0 = s4;
                        a1 = li(12);
                        jal(0x28f284, rg::fn_sub_2A3B40_002a3b40);
                        a0 = v0;
                        depend_at(0, 5, atk::kHitPkt);
                        sd(s0, v0, kPktOwner);
                        a1 = 0;
                        jal(0x28f2ac, rg::fn_sub_27ED20_0027ed20);
                    } else {
                        charge(3);
                        lq(v0, sp, atk::kCritical);
                        if (v0 != 0) {
                            charge(25);
                            a0 = s4;
                            a1 = li(13);
                            jal(0x28f2d0, rg::fn_sub_2A3B40_002a3b40);
                            a0 = v0;
                            depend_at(0, 5, atk::kHitPkt);
                            sd(s0, v0, kPktOwner);
                            a1 = 0;
                            jal(0x28f2f8, rg::fn_sub_27ED20_0027ed20);
                            gbtl(a0);
                            lw(v1, a0, kFlags);
                            v0 = lui(0x40);
                            v0 = v1 | v0;
                            sw(v0, a0, kFlags);
                            gbtl(v1);
                            lhu(v0, v1, kEndFlags);
                            v0 = v0 | 0xE;
                            sh(v0, v1, kEndFlags);
                        } else {
                            charge(5);
                            a0 = s4;
                            jal(0x28f330, rg::fn_sub_28A0F0_0028a0f0);
                            const bool eleven = v0 != 0;
                            charge(eleven ? 16 : 14);
                            a0 = s4;
                            a1 = li(eleven ? 11 : 10);
                            jal(eleven ? 0x28f348 : 0x28f388, rg::fn_sub_2A3B40_002a3b40);
                            a0 = v0;
                            depend_at(0, 5, atk::kHitPkt);
                            sd(s0, v0, kPktOwner);
                            a1 = 0;
                            jal(eleven ? 0x28f370 : 0x28f3b0, rg::fn_sub_27ED20_0027ed20);
                        }
                    }
                }
            }
        }
    }
    // the camera set of the command
    charge(31);
    a0 = s4;
    lhu(a1, s4, kActSkill);
    a2 = addiu(sp, atk::kCam0);
    a3 = addiu(sp, atk::kCam1);
    t0 = addiu(sp, atk::kCam2);
    t1 = addiu(sp, atk::kCam3);
    jal(0x28f3d0, rg::fn_sub_28A540_0028a540);
    lh(v0, sp, atk::kCam0);
    v1 = sll(v0, 2);
    gbtl(v0);
    v0 = addu(v0, v1);
    lw(a0, v0, kCameraTbl);
    lw(a1, s4, kActUnit);
    lw(a2, s3, kActUnit);
    a3 = 0;
    t0 = 0;
    jal(0x28f3fc, rg::fn_sub_2BAF90_002baf90);
    a0 = v0;
    depend_at(0, 5, atk::kHitPkt);
    a1 = li(2);
    jal(0x28f420, rg::fn_sub_27ED20_0027ed20);
    lw(v0, sp, atk::kRecIndex);
    bool plain = false;
    if (v0 == 0) {
        charge(2);
        if (s5 == 0) {
            charge(5);
            a0 = s4;
            jal(0x28f440, rg::fn_sub_28A0F0_0028a0f0);
            if (v0 == 0) {
                charge(3);
                lq(v0, sp, atk::kWeak);
                if (v0 == 0) {
                    charge(3);
                    lq(v0, sp, atk::kCritical);
                    if (v0 == 0) {
                        charge(3);
                        lq(v0, sp, atk::kQuick);
                        plain = v0 == 0;
                    }
                }
            }
        }
    }
    if (plain) {  // message 10, 15 frames before the strike
        charge(13);
        a0 = s4;
        a1 = li(10);
        jal(0x28f47c, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_at(0, 5, atk::kHitPkt);
        at = slti(s8, 15);
        if (at != 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(1);
            v0 = addiu(s8, -15);
        }
        charge(5);
        sh(v0, a0, kPktTime);
        sd(s0, a0, kPktOwner);
        a1 = 0;
        jal(0x28f4c4, rg::fn_sub_27ED20_0027ed20);
    }
    // the hit's length (v1): the motion table's halfword, or the swing's length on the last hit / at -1
    charge(4);
    lq(v0, sp, atk::kHits);
    v0 = addiu(v0, -1);
    bool len_of_motion = s5 == v0;
    if (!len_of_motion) {
        charge(7);
        v1 = sll(s5, 2);
        lw(v0, sp, atk::kMotionTbl);
        v0 = addu(v0, v1);
        lh(v1, v0, 0);
        v0 = li(-1);
        len_of_motion = v1 == v0;
    }
    if (len_of_motion) {
        charge(7);
        a1 = s1 & 0xFFFF;
        lw(a0, s4, kActUnit);
        mov_s(F12, F20);
        jal(0x28f504, rg::fn_sub_2838D0_002838d0);
        v1 = sx16(v0);
    }
    charge(14);
    lw(v0, sp, atk::kNextDelay);
    v0 = sx16(v0);
    v0 = addu(v1, v0);
    v0 = sx16(v0);
    sq(v0, sp, atk::kHitLen);
    lh(v1, sp, atk::kTime);
    v0 = addu(v1, v0);
    sh(v0, sp, atk::kTime);
    lq(v0, sp, atk::kHits);
    v0 = addiu(v0, -1);
    bool default_delay = s5 == v0;
    if (!default_delay) {
        charge(8);
        v1 = sll(s5, 2);
        lw(v0, sp, atk::kMotionTbl);
        v0 = addu(v0, v1);
        lb(v0, v0, 2);
        sw(v0, sp, atk::kNextDelay);
        v1 = li(-1);
        default_delay = v0 == v1;
    }
    if (default_delay) {
        charge(2);
        v0 = li(4);
        sw(v0, sp, atk::kNextDelay);
    }
    charge(6);
    lq(v0, sp, atk::kHitLen);
    v0 = sx16(v0);
    at = slt(s8, v0);
    if (at != 0) {
        charge(12);
        v0 = subu(v0, s8);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        lwc1(F0, gp, -31844);
        mul_s(F0, F0, F1);
        cvt_w_s(F0, F0);
        mfc1(v0, F0);
        sh(v0, sp, atk::kDelay);
    } else {
        charge(1);
        sh(zero, sp, atk::kDelay);
    }
    charge(3);
    lw(v0, s3, 208);
    bool longer = v0 != 0;
    if (!longer) {
        charge(3);
        lw(v0, s3, 212);
        longer = v0 != 0;
    }
    if (longer) {
        charge(3);
        lh(v0, sp, atk::kDelay);
        v0 = addiu(v0, 12);
        sh(v0, sp, atk::kDelay);
    }
    charge(3);
    lw(v0, s3, 212);
    bool check_1024 = true;
    if (v0 != 0) {
        charge(4);
        lhu(v1, s3, 204);
        v0 = li(1024);
        if (v1 != v0) {
            charge(4);
            v0 = li(1);
            sw(v0, sp, atk::kStrikes);
            check_1024 = false;
        }
    }
    if (check_1024) {
        charge(4);
        lhu(v1, s3, 204);
        v0 = li(1024);
        if (v1 == v0) {
            charge(3);
            v0 = li(1);
            sw(v0, sp, atk::kStrikes);
            sw(zero, sp, atk::kCamera);
        }
    }
    charge(3);
    v0 = v1 & 0x4;
    bool no_camera = v0 != 0;
    if (!no_camera) {
        charge(5);
        lq(v0, sp, atk::kRec);
        lhu(v0, v0, 250);
        v0 = v0 & 0x4;
        no_camera = v0 != 0;
    }
    if (no_camera) {
        charge(1);
        sw(zero, sp, atk::kCamera);
    }
    charge(5);
    lq(v0, sp, atk::kRec);
    lhu(v0, v0, 250);
    v0 = v0 & 0x4;
    if (v0 != 0) {  // a blocked record: the guard sequence
        charge(3);
        at = slti(s8, 7);
        if (at == 0) {
            charge(3);
            v0 = addiu(s8, -6);
        } else {
            charge(1);
            v0 = 0;
        }
        charge(13);
        v0 = sx16(v0);
        sq(v0, sp, atk::kGuardTime);
        a1 = s1 & 0xFFFF;
        lw(a0, s4, kActUnit);
        mov_s(F12, F20);
        jal(0x28f698, rg::fn_sub_283750_00283750);
        s1 = sx16(v0);
        lbu(v0, s7, kUnitSide);
        if (v0 == 0) {
            charge(16);
            a0 = s4;
            a1 = li(14);
            jal(0x28f6bc, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            depend_at(0, 4, atk::kHitPkt);
            lq(v1, sp, atk::kGuardTime);
            sh(v1, v0, kPktTime);
            sd(s0, v0, kPktOwner);
            a1 = 0;
            jal(0x28f6ec, rg::fn_sub_27ED20_0027ed20);
        }
        charge(16);
        a0 = li(12);
        a1 = li(2);
        a2 = li(9);
        jal(0x28f700, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend_at(0, 4, atk::kHitPkt);
        v0 = sx16(s1);
        at = slti(v0, 9);
        if (at == 0) {
            charge(3);
            v0 = addiu(v0, -8);
        } else {
            charge(1);
            v0 = 0;
        }
        charge(79);
        sh(v0, a0, kPktTime);
        ld(v0, s4, kActUid);
        sd(v0, a0, kPktOwner);
        a1 = li(1);
        jal(0x28f754, rg::fn_sub_27ED20_0027ed20);
        lw(a1, s4, kActUnit);
        gbtl(v0);
        lw(a0, v0, 3320);
        a2 = a1;
        a3 = li(1);
        t0 = 0;
        jal(0x28f774, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend_at(0, 4, atk::kHitPkt);
        sh(s1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a1 = li(2);
        jal(0x28f7a0, rg::fn_sub_27ED20_0027ed20);
        lw(a1, s4, kActUnit);
        gbtl(v0);
        lw(a0, v0, 3312);
        a2 = a1;
        a3 = li(1);
        t0 = 0;
        jal(0x28f7c0, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend_at(0, 4, atk::kHitPkt);
        lq(v1, sp, atk::kGuardTime);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a1 = li(2);
        jal(0x28f7f0, rg::fn_sub_27ED20_0027ed20);
        a0 = addiu(sp, atk::kResult);
        jal(0x28f7fc, rg::fn_sub_2D5DC0_002d5dc0);
        v0 = lui(0x10);
        sw(v0, sp, atk::kResult + 8);
        a0 = s4;
        a1 = s4;
        a2 = addiu(sp, atk::kResult);
        a3 = li(1);
        t0 = a3;
        jal(0x28f820, rg::fn_sub_2D7E20_002d7e20);
        s1 = v0;
        depend_at(0, 4, atk::kHitPkt);
        lq(v1, sp, atk::kHitLen);
        a0 = sx16(v1);
        v1 = sra(a0, 2);
        v1 = subu(a0, v1);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a0 = s1;
        a1 = li(1);
        jal(0x28f864, rg::fn_sub_27ED20_0027ed20);
        lw(v0, s4, kActUnit);
        lbu(v1, v0, kUnitSide);
        v0 = li(1);
        if (v1 == v0) {
            charge(3);
            lq(v0, sp, atk::kQuick);
            if (v0 == 0) {
                charge(16);
                a0 = s3;
                a1 = li(24);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(0x28f8a0, rg::fn_sub_2DB740_002db740);
                a0 = v0;
                depend(0, 4, s1);
                sd(s0, v0, kPktOwner);
                a1 = li(1);
                jal(0x28f8c4, rg::fn_sub_27ED20_0027ed20);
            }
        }
        charge(20);
        jal(0x28f8cc, rg::fn_sub_27F2F0_0027f2f0);
        s1 = v0;
        depend_at(0, 5, atk::kHitPkt);
        lq(v1, sp, atk::kHitLen);
        sh(v1, v0, kPktTime);
        v1 = li(12);
        sh(v1, v0, 74);
        sd(s0, v0, kPktOwner);
        a0 = s1;
        a1 = li(1);
        jal(0x28f908, rg::fn_sub_27ED20_0027ed20);
        lq(v0, sp, atk::kQuick);
        if (v0 == 0) {
            charge(15);
            a0 = s4;
            a1 = li(10);
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(0x28f930, rg::fn_sub_2E2BE0_002e2be0);
            a0 = v0;
            depend(0, 4, s1);
            a1 = li(1);
            jal(0x28f950, rg::fn_sub_27ED20_0027ed20);
        }
        charge(9);
        gbtl(a0);
        lw(v1, a0, kFlags);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, kFlags);
        gbtl(v1);
        lhu(v0, v1, kEndFlags);
        v0 = v0 | 0xF;
        sh(v0, v1, kEndFlags);
    }
    charge(3);
    s1 = 0;  // the strike
    for (;;) {
        charge(4);
        lw(v0, sp, atk::kStrikes);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        attack_strike();
    }
}

// One strike (s1) of the hit s5: the victim's reaction motion (+248; 18 / 8 become 2 before the last strike) after the
// swing (s2, its time s8 or s8 - 6 for -3 / 22, + 5 for a counter), the first / last reaction ids, the technical camera
// 24, an intermediate damage number (F21 += F22 / strikes with gBtl+12 bit 4) before the last strike, the counter
// camera / effect, the repel camera / effect (+204 == 1024, numbers' time 10), the pending effect of weapon type 7,
// the camera cuts (the critical / weak finisher camera +3160, the multi-hit camera +3156 with message 15, the set's
// camera, the enemy-id effect 10 / the character effect of sub_308ED0, +3148, the weak finisher camera / effect, the
// final camera), the victim's knock-back sub_282650(target, actor, 2), and the next strike's time.
void Cpu::attack_strike() {
    charge(6);
    lq(v0, sp, atk::kRec);
    lb(v0, v0, 248);
    sw(v0, sp, atk::kReaction);
    v1 = li(18);
    bool repeat = v0 == v1;
    if (!repeat) {
        charge(3);
        v1 = li(8);
        repeat = v0 == v1;
    }
    if (repeat) {
        charge(4);
        lq(v0, sp, atk::kHits);
        v0 = addiu(v0, -1);
        bool not_last = s5 != v0;
        if (!not_last) {
            charge(4);
            lw(v0, sp, atk::kStrikes);
            v0 = addiu(v0, -1);
            not_last = s1 != v0;
        }
        if (not_last) {
            charge(2);
            v0 = li(2);
            sw(v0, sp, atk::kReaction);
        }
    } else {
        charge(2);
    }
    charge(19);
    lh(v0, sp, atk::kReaction);
    a1 = v0;
    v0 = lui(0x3F80);  // 1.0f
    mtc1(v0, F12);
    lw(a0, s6, kActUnit);
    a2 = 0;
    a3 = 0;
    jal(0x28f9f8, rg::fn_sub_284200_00284200);  // the reaction
    s2 = v0;
    depend_at(0, 4, atk::kHitPkt);
    v1 = li(-3);
    lw(v0, sp, atk::kReaction);
    bool early = v0 == v1;
    if (!early) {
        charge(3);
        v1 = li(22);
        early = v0 == v1;
    }
    if (early) {
        charge(3);
        at = slti(s8, 7);
        if (at == 0) {
            charge(3);
            v0 = addiu(s8, -6);
        } else {
            charge(1);
            v0 = 0;
        }
        charge(3);
        sh(v0, s2, kPktTime);
    } else {
        charge(2);
        charge(1);
        sh(s8, s2, kPktTime);
    }
    charge(3);
    lw(v0, s3, 212);
    if (v0 != 0) {
        charge(3);
        lh(v0, s2, kPktTime);
        v0 = addiu(v0, 5);
        sh(v0, s2, kPktTime);
    }
    charge(10);
    sd(s0, s2, kPktOwner);
    a0 = s2;
    a1 = li(1);
    jal(0x28fa8c, rg::fn_sub_27ED20_0027ed20);
    ld(v0, s2, kPktId);
    sd(v0, sp, atk::kLastId);
    lw(v0, sp, atk::kRecIndex);
    if (v0 == 0) {
        charge(2);
        if (s5 == 0) {
            charge(2);
            if (s1 == 0) {
                charge(2);
                ld(v0, sp, atk::kLastId);
                sd(v0, sp, atk::kFirstId);
            }
        }
    }
    charge(4);
    lhu(v0, s3, 204);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        charge(5);
        lq(v0, sp, atk::kRec);
        lhu(v0, v0, 250);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(3);
            lq(v0, sp, atk::kQuick);
            if (v0 == 0) {
                charge(15);
                a0 = s4;
                a1 = li(24);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(0x28fb04, rg::fn_sub_2E2BE0_002e2be0);
                a0 = v0;
                depend(0, 5, s2);
                a1 = li(1);
                jal(0x28fb24, rg::fn_sub_27ED20_0027ed20);
            }
        }
    }
    charge(4);
    lw(v0, sp, atk::kStrikes);
    v0 = addiu(v0, -1);
    bool number = s1 != v0;
    if (!number) {
        charge(4);
        lq(v0, sp, atk::kHits);
        v0 = addiu(v0, -1);
        number = s5 != v0;
    }
    if (number) {  // an intermediate damage number
        charge(5);
        gbtl(v0);
        lw(v0, v0, kFlags);
        v0 = v0 & 0x10;
        if (v0 != 0) {
            charge(6);
            lw(v0, sp, atk::kStrikes);
            mtc1(v0, F0);
            cvt_s_w(F0, F0);
            div_s(F0, F22, F0);
            add_s(F21, F21, F0);
        }
        charge(21);
        cvt_w_s(F0, F21);
        mfc1(v0, F0);
        a2 = sx16(v0);
        lw(a0, s6, kActUnit);
        a1 = 0;
        jal(0x28fb94, rg::fn_sub_2BD230_002bd230);
        a0 = v0;
        depend(0, 5, s2);
        clear_bit5_71();
        sd(s0, v0, kPktOwner);
        a1 = li(3);
        jal(0x28fbc4, rg::fn_sub_27ED20_0027ed20);
    }
    charge(3);
    lw(v0, s3, 212);
    if (v0 != 0) {  // the counter
        charge(5);
        a0 = s3;
        jal(0x28fbdc, rg::fn_sub_2FD160_002fd160);
        if (v0 == 0) {
            charge(2);
            gbtl(v0);
            lw(v0, v0, 3212);
        }
        charge(40);
        a0 = v0;
        lw(a1, s4, kActUnit);
        lw(a2, s3, kActUnit);
        a3 = li(1);
        t0 = 0;
        jal(0x28fc08, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend_at(0, 4, atk::kHitPkt);
        sh(s8, v0, kPktTime);
        v1 = sx16(s8);
        v1 = addiu(v1, 5);
        sh(v1, v0, kPktTime);
        a1 = li(1);
        jal(0x28fc40, rg::fn_sub_27ED20_0027ed20);
        a0 = li(13);
        a1 = li(2);
        a2 = li(6);
        jal(0x28fc54, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend_at(0, 4, atk::kHitPkt);
        sh(s8, v0, kPktTime);
        v1 = sx16(s8);
        v1 = addiu(v1, 5);
        sh(v1, v0, kPktTime);
        a1 = li(1);
        jal(0x28fc8c, rg::fn_sub_27ED20_0027ed20);
    }
    charge(4);
    lhu(v1, s3, 204);
    v0 = li(1024);
    if (v1 == v0) {  // repelled
        charge(31);
        gbtl(v0);
        lw(a0, v0, 3216);
        lw(a1, s4, kActUnit);
        lw(a2, s6, kActUnit);
        a3 = li(1);
        t0 = 0;
        jal(0x28fcbc, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend(0, 5, s2);
        a1 = li(1);
        jal(0x28fcdc, rg::fn_sub_27ED20_0027ed20);
        a0 = li(12);
        a1 = li(2);
        a2 = li(7);
        jal(0x28fcf0, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend(0, 5, s2);
        a1 = li(1);
        jal(0x28fd10, rg::fn_sub_27ED20_0027ed20);
        v0 = li(10);
        sh(v0, sp, atk::kNumTime);
    }
    charge(4);
    lh(v0, sp, atk::kEffB);
    if (!ltz(v0)) {
        charge(4);
        lh(v0, sp, atk::kEffA);
        if (!ltz(v0)) {
            charge(18);
            lhu(v0, sp, atk::kEffB);
            a1 = v0;
            lhu(v0, sp, atk::kEffA);
            a2 = v0;
            a0 = li(12);
            jal(0x28fd54, rg::fn_sub_2DD100_002dd100);
            a0 = v0;
            depend(0, 5, s2);
            a1 = li(1);
            jal(0x28fd74, rg::fn_sub_27ED20_0027ed20);
            v0 = li(-1);
            sh(v0, sp, atk::kEffB);
            sh(v0, sp, atk::kEffA);
        }
    }
    charge(3);
    lw(v0, sp, atk::kCamera);
    if (v0 != 0) {  // the camera cuts
        charge(4);
        v1 = li(1);
        lq(v0, sp, atk::kCritical);
        bool special = v0 == v1;
        if (!special) {
            charge(3);
            lq(v0, sp, atk::kWeak);
            special = v0 == v1;
        }
        bool finisher = false;
        if (special) {
            charge(4);
            lq(v1, sp, atk::kHits);
            lq(v0, sp, atk::kHitsMax);
            if (v1 == v0) {
                charge(4);
                lw(v0, sp, atk::kStrikes);
                v0 = addiu(v0, -1);
                if (s1 == v0) {
                    charge(4);
                    paddub(v0, v1, zero);
                    v0 = addiu(v0, -1);
                    finisher = s5 == v0;
                }
            }
        }
        if (finisher) {
            charge(19);
            gbtl(v0);
            lw(a0, v0, 3160);
            lw(a1, s4, kActUnit);
            lw(a2, s6, kActUnit);
            a3 = li(1);
            t0 = 0;
            jal(0x28fdf8, rg::fn_sub_2BAF90_002baf90);
            a0 = v0;
            depend(0, 5, s2);
            sd(s0, v0, kPktOwner);
            a1 = li(2);
            jal(0x28fe1c, rg::fn_sub_27ED20_0027ed20);
        } else {
            charge(4);
            lq(v0, sp, atk::kHits);
            at = slti(v0, 2);
            if (at == 0) {
                charge(2);
                bool later = s5 != 0;
                if (!later) {
                    charge(2);
                    later = s1 != 0;
                }
                if (later) {
                    charge(20);
                    gbtl(v0);
                    lw(a0, v0, 3156);
                    lw(a1, s4, kActUnit);
                    lw(a2, s6, kActUnit);
                    a3 = li(1);
                    t0 = 0;
                    jal(0x28fe64, rg::fn_sub_2BAF90_002baf90);
                    a0 = v0;
                    depend(0, 5, s2);
                    a1 = li(2);
                    jal(0x28fe84, rg::fn_sub_27ED20_0027ed20);
                    v1 = li(1);
                    lq(v0, sp, atk::kCritical);
                    if (v0 != v1) {
                        charge(3);
                        lq(v0, sp, atk::kWeak);
                        if (v0 != v1) {
                            charge(12);
                            a0 = s4;
                            a1 = li(15);
                            jal(0x28feb0, rg::fn_sub_2A3B40_002a3b40);
                            a0 = v0;
                            depend(0, 5, s2);
                            a1 = 0;
                            jal(0x28fed0, rg::fn_sub_27ED20_0027ed20);
                        }
                    }
                }
            }
        }
        charge(22);
        attack_camera(atk::kCam0, 0x28fefc, 0x28ff1c);
        lbu(v0, s7, kUnitSide);
        if (v0 == 0) {  // a party actor: the hit effect of its last strike
            charge(6);
            sh(zero, sp, atk::kEff2);
            v0 = 0;
            lhu(a1, s7, 164);
            v1 = li(9);
            if (a1 == v1) {
                charge(3);
                v1 = li(1);
                if (s5 == v1) {
                    charge(4);
                    lw(v1, sp, atk::kStrikes);
                    v1 = addiu(v1, -1);
                    if (s1 == v1) {
                        charge(1);
                        v0 = li(4);
                    }
                }
            } else {
                charge(3);
                v1 = li(8);
                if (a1 == v1) {
                    charge(3);
                    v1 = li(1);
                    if (s5 == v1) {
                        charge(4);
                        lw(v1, sp, atk::kStrikes);
                        v1 = addiu(v1, -1);
                        if (s1 == v1) {
                            charge(3);
                            v0 = li(4);
                        }
                    }
                } else {
                    charge(3);
                    a0 = li(4);
                    if (a1 == a0) {
                        charge(3);
                        v1 = li(2);
                        if (s5 == v1) {
                            charge(4);
                            lw(v1, sp, atk::kStrikes);
                            v1 = addiu(v1, -1);
                            if (s1 == v1) {
                                charge(4);
                                v0 = sx16(a0);
                            }
                        }
                    } else {
                        charge(2);
                    }
                }
            }
            charge(4);
            v1 = sx16(v0);
            if (v1 == 0) {
                charge(11);
                lw(a0, s7, kUnitDat);
                jal(0x28fff0, rg::fn_sub_308ED0_00308ed0);
                v0 = v0 & 0xFFFF;
                v1 = sll(v0, 1);
                v0 = lui(0x69);
                v0 = addiu(v0, 3616);
                v0 = addu(v0, v1);
                lh(v0, v0, 0);  // the table 0x690E20
            }
        } else {
            charge(2);
            sh(zero, sp, atk::kEff2);
            v0 = 0;
        }
        charge(4);
        lh(v1, sp, atk::kEff2);
        if (!ltz(v1)) {
            charge(4);
            v1 = sx16(v0);
            if (!ltz(v1)) {
                charge(14);
                lhu(v1, sp, atk::kEff2);
                a1 = v1;
                a2 = v0 & 0xFFFF;
                a0 = li(10);
                jal(0x290050, rg::fn_sub_2DD100_002dd100);
                a0 = v0;
                depend(0, 5, s2);
                a1 = li(1);
                jal(0x290070, rg::fn_sub_27ED20_0027ed20);
            }
        }
        charge(20);
        gbtl(v0);
        lw(a0, v0, 3148);
        lw(a1, s4, kActUnit);
        lw(a2, s6, kActUnit);
        a3 = li(1);
        t0 = 0;
        jal(0x290090, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend(0, 5, s2);
        a1 = li(2);
        jal(0x2900b0, rg::fn_sub_27ED20_0027ed20);
        lq(v0, sp, atk::kHits);
        v0 = addiu(v0, -1);
        if (s5 == v0) {
            charge(4);
            lw(v0, sp, atk::kStrikes);
            v0 = addiu(v0, -1);
            if (s1 == v0) {
                charge(4);
                lhu(v0, s3, 206);
                v0 = v0 & 0x6;
                if (v0 != 0) {  // the weak finisher
                    charge(32);
                    attack_camera(atk::kCam1, 0x29010c, 0x29012c);
                    a0 = li(12);
                    a1 = 0;
                    a2 = li(9);
                    jal(0x290140, rg::fn_sub_2DD100_002dd100);
                    a0 = v0;
                    depend(0, 5, s2);
                    a1 = li(1);
                    jal(0x290160, rg::fn_sub_27ED20_0027ed20);
                }
            }
        }
        charge(4);
        lw(v0, sp, atk::kStrikes);
        v0 = addiu(v0, -1);
        if (s1 == v0) {
            charge(4);
            lq(v0, sp, atk::kHits);
            v0 = addiu(v0, -1);
            if (s5 == v0) {  // the final camera
                charge(6);
                v0 = li(-1);
                sh(v0, sp, atk::kCamFinal);
                lhu(v0, s3, 206);
                v0 = v0 & 0x6;
                if (v0 != 0) {
                    charge(4);
                    lh(v0, sp, atk::kCam3);
                    sh(v0, sp, atk::kCamFinal);
                } else {
                    charge(4);
                    lq(v0, sp, atk::kHits);
                    at = slti(v0, 2);
                    bool cam2 = at == 0;
                    if (!cam2) {
                        charge(4);
                        lw(v0, s4, kActUnit);
                        lbu(v0, v0, kUnitSide);
                        if (v0 == 0) {
                            charge(5);
                            a0 = s4;
                            jal(0x2901d4, rg::fn_sub_28A0F0_0028a0f0);
                            cam2 = v0 != 0;
                        }
                    }
                    if (cam2) {
                        charge(2);
                        lh(v0, sp, atk::kCam2);
                        sh(v0, sp, atk::kCamFinal);
                    }
                }
                charge(4);
                lh(v0, sp, atk::kCamFinal);
                if (!ltz(v0)) {
                    charge(18);
                    v1 = sll(v0, 2);
                    gbtl(v0);
                    v0 = addu(v0, v1);
                    lw(a0, v0, kCameraTbl);
                    lw(a1, s4, kActUnit);
                    lw(a2, s6, kActUnit);
                    a3 = li(1);
                    t0 = 0;
                    jal(0x29021c, rg::fn_sub_2BAF90_002baf90);
                    a0 = v0;
                    depend(0, 5, s2);
                    a1 = li(2);
                    jal(0x29023c, rg::fn_sub_27ED20_0027ed20);
                }
            }
        }
    }
    // the victim's knock-back after the last reaction
    charge(21);
    lw(a0, s3, kActUnit);
    lw(a1, s4, kActUnit);
    a2 = li(2);
    jal(0x290250, rg::fn_sub_282650_00282650);
    a0 = v0;
    depend_id_at(0, 5, atk::kLastId);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    a1 = li(1);
    jal(0x290280, rg::fn_sub_27ED20_0027ed20);
    lw(v0, sp, atk::kStrikes);
    v0 = addiu(v0, -1);
    if (s1 != v0) {  // the next strike's time
        charge(3);
        lw(v0, sp, atk::kStrikeTbl);
        if (v0 != 0) {
            charge(7);
            v1 = sll(s1, 1);
            v0 = addu(v0, v1);
            lh(v1, v0, 2);
            lh(v0, v0, 0);
            v1 = subu(v1, v0);
        } else {
            charge(1);
            lw(v1, sp, atk::kStrikeStep);
        }
        charge(6);
        v0 = lui(0x3F80);
        mtc1(v0, F0);
        c_eq_s(F0, F20);
        if (!cop1_cond()) {  // scaled by the speed
            charge(6);
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            div_s(F0, F0, F20);
            cvt_w_s(F0, F0);
            mfc1(v1, F0);
        }
        charge(6);
        s8 = addu(s8, v1);
        lh(v0, sp, atk::kDelay);
        at = slt(v1, v0);
        if (at != 0) {
            charge(7);
            v1 = sx16(v1);
            lh(v0, sp, atk::kDelay);
            v0 = subu(v0, v1);
            sh(v0, sp, atk::kDelay);
        } else {
            charge(1);
            sh(zero, sp, atk::kDelay);
        }
    }
    charge(1);
    s1 = addiu(s1, 1);
}

// The current record's results (after its hits): a critical's down sequence (sub_282130(victim, 16), +72 = 1, +74 =
// 12; the down camera +3316 without +208; sub_284C90), the result numbers sub_2D7E20(action, victim, record +224,
// +204, +206) at the numbers' time with the delay, the HP gauges sub_2D8090 (target, and the actor after the last
// record), the actor's result sub_2D7FB0(action, +202) on the first record unless +24 bit 2, the status icon
// sub_2BD850 (actor +220, else target +220) after the last record, the status packet sub_2BDBD0, the target's
// sub_2BD230 on the first record with damage, the enemy victim's reactions (a crossed counter: the party sound 22 or
// camera 13 by the rule below; a critical: the sound 23; else the cameras 14 / 15 of sub_2D6130 / sub_2D6210 /
// sub_2D5F50), and the knocked-down record (+250 bit 0: the numbers again with 0x100000, bit 1: the down motion 10 and
// sub_284C90).
void Cpu::attack_record_end() {
    charge(7);
    lq(v0, sp, atk::kRec);
    s5 = addiu(v0, 232);
    lw(v1, v0, 232);
    v0 = lui(0x10);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(3);
        lq(v0, sp, atk::kQuick);
        if (v0 == 0) {
            charge(20);
            lw(a0, s6, kActUnit);
            a1 = li(16);
            jal(0x290384, rg::fn_sub_282130_00282130);
            s1 = v0;
            depend_id_at(0, 5, atk::kLastId);
            a1 = li(1);
            sh(a1, v0, kPktTime);
            v1 = li(12);
            sh(v1, v0, 74);
            sd(s0, v0, kPktOwner);
            a0 = s1;
            jal(0x2903b8, rg::fn_sub_27ED20_0027ed20);
            lw(v0, s3, 208);
            if (v0 == 0) {
                charge(17);
                lw(a1, s6, kActUnit);
                gbtl(v0);
                lw(a0, v0, 3316);
                a2 = a1;
                a3 = li(1);
                t0 = 0;
                jal(0x2903e4, rg::fn_sub_2BAF90_002baf90);
                a0 = v0;
                depend(0, 5, s1);
                sd(s0, v0, kPktOwner);
                a1 = li(2);
                jal(0x290408, rg::fn_sub_27ED20_0027ed20);
            }
            charge(12);
            lw(a0, s6, kActUnit);
            jal(0x290414, rg::fn_sub_284C90_00284c90);
            a0 = v0;
            depend(0, 5, s1);
            sd(s0, v0, kPktOwner);
            a1 = li(1);
            jal(0x290438, rg::fn_sub_27ED20_0027ed20);
        }
    }
    charge(41);
    lq(v0, sp, atk::kRec);
    s1 = addiu(v0, 224);
    a0 = s4;
    a1 = s6;
    a2 = s1;
    lhu(a3, s3, 204);
    lhu(t0, s3, 206);
    jal(0x29045c, rg::fn_sub_2D7E20_002d7e20);  // the result numbers
    a0 = v0;
    depend_id_at(0, 5, atk::kLastId);
    lh(v1, sp, atk::kNumTime);
    sh(v1, v0, kPktTime);
    lh(v1, sp, atk::kDelay);
    sh(v1, v0, 74);
    sd(s0, v0, kPktOwner);
    a1 = li(1);
    jal(0x290490, rg::fn_sub_27ED20_0027ed20);
    a0 = s3;
    jal(0x29049c, rg::fn_sub_2D8090_002d8090);
    a0 = v0;
    depend_id_at(0, 5, atk::kLastId);
    lh(v1, sp, atk::kNumTime);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a1 = li(1);
    jal(0x2904c8, rg::fn_sub_27ED20_0027ed20);
    lq(v0, sp, atk::kRecords);
    v1 = addiu(v0, -1);
    lw(v0, sp, atk::kRecIndex);
    if (v0 == v1) {
        charge(14);
        a0 = s4;
        jal(0x2904e8, rg::fn_sub_2D8090_002d8090);
        a0 = v0;
        depend_id_at(0, 5, atk::kLastId);
        lh(v1, sp, atk::kNumTime);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a1 = li(1);
        jal(0x290514, rg::fn_sub_27ED20_0027ed20);
    }
    charge(3);
    lw(v0, sp, atk::kRecIndex);
    if (v0 == 0) {
        charge(4);
        lhu(v0, s4, kActFlags);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(15);
            a0 = s4;
            lbu(a1, s4, 202);
            jal(0x290540, rg::fn_sub_2D7FB0_002d7fb0);
            a0 = v0;
            depend_id_at(0, 5, atk::kLastId);
            lh(v1, sp, atk::kNumTime);
            sh(v1, v0, kPktTime);
            sd(s0, v0, kPktOwner);
            a1 = li(1);
            jal(0x29056c, rg::fn_sub_27ED20_0027ed20);
        }
    }
    charge(5);
    lq(v0, sp, atk::kRecords);
    v1 = addiu(v0, -1);
    lw(v0, sp, atk::kRecIndex);
    if (v0 == v1) {
        charge(3);
        lh(a1, s4, 220);
        if (a1 != 0) {
            charge(17);
            lw(a0, s4, kActUnit);
            jal(0x290598, rg::fn_sub_2BD850_002bd850);
            a0 = v0;
            depend_id_at(0, 5, atk::kLastId);
            clear_bit5_71();
            sd(s0, v0, kPktOwner);
            a1 = li(3);
            jal(0x2905c8, rg::fn_sub_27ED20_0027ed20);
        } else {
            charge(3);
            lh(a1, s3, 220);
            if (a1 != 0) {
                charge(15);
                lw(a0, s3, kActUnit);
                jal(0x2905e8, rg::fn_sub_2BD850_002bd850);
                a0 = v0;
                depend_id_at(0, 5, atk::kLastId);
                clear_bit5_71();
                sd(s0, v0, kPktOwner);
                a1 = li(3);
                jal(0x290618, rg::fn_sub_27ED20_0027ed20);
            }
        }
    }
    charge(27);
    lhu(a2, s4, kActSkill);
    lw(a0, s4, kActUnit);
    lw(a1, s6, kActUnit);
    lhu(a3, s3, 204);
    lhu(t0, s3, 206);
    t1 = 0;
    t2 = li(1);
    t3 = s1;
    jal(0x290640, rg::fn_sub_2BDBD0_002bdbd0);
    a0 = v0;
    depend(0, 5, s2);
    lh(v1, sp, atk::kNumTime);
    sh(v1, v0, kPktTime);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    a1 = li(3);
    jal(0x290678, rg::fn_sub_27ED20_0027ed20);
    lw(v0, sp, atk::kRecIndex);
    if (v0 == 0) {
        charge(4);
        lq(v0, sp, atk::kRec);
        lw(v0, v0, 224);
        if (v0 != 0) {
            charge(19);
            lw(a0, s6, kActUnit);
            a1 = 0;
            a2 = 0;
            jal(0x2906a8, rg::fn_sub_2BD230_002bd230);
            a0 = v0;
            depend(0, 5, s2);
            lh(v1, sp, atk::kNumTime);
            sh(v1, v0, kPktTime);
            clear_bit5_71();
            sd(s0, v0, kPktOwner);
            a1 = li(3);
            jal(0x2906e0, rg::fn_sub_27ED20_0027ed20);
        }
    }
    charge(3);
    lq(v0, sp, atk::kQuick);
    if (v0 == 0) {
        charge(5);
        lw(v0, s6, kActUnit);
        lbu(v1, v0, kUnitSide);
        v0 = li(1);
        if (v1 == v0) {  // an enemy victim
            charge(3);
            lw(v0, sp, atk::kCross);
            if (!lez(v0)) {
                charge(4);
                lw(v0, s4, kActUnit);
                lbu(v0, v0, kUnitSide);
                if (v0 == 0) {
                    charge(8);
                    a0 = li(2);
                    a1 = lui(0x8);
                    jal(0x29072c, rg::fn_btlCountActiveUnits_002d4e10);
                    s1 = v0 & 0xFFFF;
                    lbu(v0, s4, 40);
                    bool sound = gtz(v0);
                    if (!sound) {
                        charge(5);
                        lw(v0, s4, kActUnit);
                        lhu(v1, v0, 164);
                        v0 = li(1);
                        sound = v1 == v0;
                    }
                    if (!sound) {
                        charge(6);
                        a0 = li(100);
                        jal(0x29075c, rg::fn_datCalcRand_002ffbc0);
                        at = sltiu(v0, 50);
                        sound = at == 0;
                    }
                    if (!sound) {
                        charge(4);
                        lw(v0, s4, kActUnit);
                        lbu(v0, v0, kUnitSide);
                        if (v0 != 0) {
                            charge(3);
                            v0 = 0;
                        } else {
                            charge(5);
                            gbtl(a0);
                            lh(v1, a0, 2616);
                            v0 = li(-1);
                            bool none = v1 == v0;
                            if (!none) {
                                charge(6);
                                lw(v0, sp, atk::kCross);
                                v0 = subu(s1, v0);
                                v1 = sx16(v0);
                                if (gtz(v1)) {
                                    charge(5);
                                    lh(v0, a0, 2618);
                                    v0 = sra(v0, 1);
                                    v0 = slt(v0, v1);
                                    none = v0 != 0;
                                } else {
                                    charge(11);
                                    a0 = li(2);
                                    a1 = lui(0x8);
                                    jal(0x2907c0, rg::fn_btlCountActiveUnits_002d4e10);
                                    a0 = v0 & 0xFFFF;
                                    gbtl(v1);
                                    lh(v0, v1, 2618);
                                    v0 = sra(v0, 1);
                                    v0 = sltu(v0, a0);
                                    none = v0 != 0;
                                    if (!none) {
                                        charge(7);
                                        lh(s1, v1, 2616);
                                        jal(0x2907e8, rg::fn_sub_2B7060_002b7060);
                                        v0 = sx16(v0);
                                        none = s1 == v0;
                                    }
                                }
                            }
                            if (none) {
                                charge(1);
                                v0 = 0;
                            } else {
                                charge(3);
                                v0 = li(1);
                            }
                        }
                        charge(2);
                        sound = v0 != 0;
                    }
                    if (sound) {
                        charge(18);
                        a0 = s4;
                        a1 = li(22);
                        lw(a2, sp, atk::kCross);
                        a3 = 0;
                        t0 = 0;
                        jal(0x29084c, rg::fn_sub_2DB740_002db740);
                        a0 = v0;
                        depend_id_at(0, 5, atk::kLastId);
                        sd(s0, v0, kPktOwner);
                        a1 = li(1);
                        jal(0x290870, rg::fn_sub_27ED20_0027ed20);
                    } else {
                        charge(17);
                        a0 = s4;
                        a1 = li(13);
                        lw(a2, sp, atk::kCross);
                        a3 = 0;
                        t0 = 0;
                        jal(0x290894, rg::fn_sub_2E2BE0_002e2be0);
                        a0 = v0;
                        depend_id_at(0, 5, atk::kLastId);
                        a1 = li(1);
                        jal(0x2908b4, rg::fn_sub_27ED20_0027ed20);
                    }
                }
            } else {
                charge(5);
                lw(v1, s5, 0);
                v0 = lui(0x10);
                v0 = v1 & v0;
                if (v0 != 0) {  // a critical
                    charge(18);
                    lhu(a2, s3, 206);
                    a0 = s4;
                    a1 = li(23);
                    a3 = 0;
                    t0 = 0;
                    jal(0x2908ec, rg::fn_sub_2DB740_002db740);
                    a0 = v0;
                    depend_id_at(0, 5, atk::kLastId);
                    sd(s0, v0, kPktOwner);
                    a1 = li(1);
                    jal(0x290910, rg::fn_sub_27ED20_0027ed20);
                } else {
                    charge(3);
                    lw(v0, sp, atk::kCross);
                    if (v0 == 0) {
                        charge(5);
                        a0 = s4;
                        jal(0x290930, rg::fn_sub_2D6130_002d6130);
                        if (v0 != 0) {
                            charge(17);
                            a0 = s4;
                            a1 = li(14);
                            a2 = 0;
                            a3 = 0;
                            t0 = 0;
                            jal(0x290954, rg::fn_sub_2E2BE0_002e2be0);
                            a0 = v0;
                            depend_id_at(0, 5, atk::kLastId);
                            a1 = li(1);
                            jal(0x290974, rg::fn_sub_27ED20_0027ed20);
                        } else {
                            charge(6);
                            a0 = s4;
                            jal(0x290988, rg::fn_sub_2D6210_002d6210);
                            v1 = li(1);
                            if (v0 == v1) {
                                charge(5);
                                a0 = s4;
                                jal(0x2909a0, rg::fn_sub_2D5F50_002d5f50);
                                if (v0 == 0) {
                                    charge(21);
                                    lw(v0, s4, kActUnit);
                                    lw(a0, v0, kUnitDat);
                                    lhu(a1, s4, kActSkill);
                                    jal(0x2909bc, rg::fn_datCalcGetSkillElement_003082f0);
                                    a2 = sx16(v0);
                                    a0 = s4;
                                    a1 = li(15);
                                    a3 = 0;
                                    t0 = 0;
                                    jal(0x2909dc, rg::fn_sub_2E2BE0_002e2be0);
                                    a0 = v0;
                                    depend_id_at(0, 5, atk::kLastId);
                                    a1 = li(1);
                                    jal(0x2909fc, rg::fn_sub_27ED20_0027ed20);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    charge(6);
    lq(v0, sp, atk::kRec);
    s1 = addiu(v0, 250);
    lhu(v0, v0, 250);
    v0 = v0 & 0x1;
    if (v0 != 0) {  // knocked down
        charge(25);
        a0 = addiu(sp, atk::kResult);
        jal(0x290a20, rg::fn_sub_2D5DC0_002d5dc0);
        v0 = lui(0x10);
        sw(v0, sp, atk::kResult + 12);
        a0 = s3;
        a1 = s3;
        a2 = addiu(sp, atk::kResult);
        a3 = li(1);
        t0 = a3;
        jal(0x290a44, rg::fn_sub_2D7E20_002d7e20);
        a0 = v0;
        depend_id_at(0, 4, atk::kFirstId);
        sd(s0, v0, kPktOwner);
        a1 = li(1);
        jal(0x290a68, rg::fn_sub_27ED20_0027ed20);
        lhu(v0, s1, 0);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            charge(29);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            lw(a0, s3, kActUnit);
            a1 = li(10);
            a2 = 0;
            a3 = 0;
            jal(0x290a98, rg::fn_sub_284200_00284200);
            a0 = v0;
            depend_id_at(0, 4, atk::kFirstId);
            sd(s0, v0, kPktOwner);
            a1 = li(1);
            jal(0x290abc, rg::fn_sub_27ED20_0027ed20);
            lw(a0, s3, kActUnit);
            jal(0x290ac8, rg::fn_sub_284C90_00284c90);
            a0 = v0;
            depend_id_at(0, 4, atk::kFirstId);
            sd(s0, v0, kPktOwner);
            a1 = li(1);
            jal(0x290aec, rg::fn_sub_27ED20_0027ed20);
        }
    }
    charge(3);
    lw(v0, sp, atk::kRecIndex);
    v0 = addiu(v0, 1);
    sw(v0, sp, atk::kRecIndex);
}

// 0x290BE0 btlActionUpdateStateSkill(action): SKILL, a skill / item use played out in one frame as chains of dependent
// packets (the largest btlAction state, 16,684 bytes; then -> PACKET 30, or the state the result asks for). Inputs: the
// actor's side s6 (forced to -1 by +24 bit 8), the skill s7 (+110) with its SKILL.TBL record (*(gp-18680), 44 bytes:
// +0 bit 1) and its 28-byte effect record (*(gp-18672) + 28 * skill: +2 flags 0x100 / 0x4000 / 0x40), the chosen
// targets (+56..), the persona unit (unit +2560 -> sp+1104), the item flag (+108 == 3 -> sp+448), sub_308A50(+114)
// (sp+416), sub_2D6290 / datCalcIsHpSkill (sp+748 / sp+432), the camera set s = sub_2B8F90(1) (sp+1080).
//   * The approach: the actor faces the target (sub_282650) or walks to its side's spot (sub_280870 / sub_2822B0,
//     enemies by sub_2FDCB0 / sub_2FDDB0), the panel packets, +24 |= 0x200, sub_2D8330; the cast effect sub_2BD590 /
//     an item's sub_2BD690 (+72 = 3 for an effect record flag 0x100, else 1).
//   * L_00291040 onward, the summon (+26 bit 4 without SKILL.TBL bit 1, not an item, sub_308A50 0): the persona's
//     appearance (a cut-in for the party with 20 % / forced chances, sub_2E33F0 / sub_2E35D0 / sub_2E36F0 /
//     sub_2E37E0), the camera triple of sub_2FCAA0 (default gBtl+3220..3228) on the actor, the evoker / card motions
//     (sub_284200 12 / 14, sub_2838D0 lengths), the persona model load sub_285690(persona, id, 13 / 29), its motion,
//     the shatter effects, the messages 16 / 17 / 21 / 22.
//   * L_00291b4c, an item or a direct skill (sub_308A50 == 1): the throw motion and message 16, the item effect
//     sub_2E3DE0; L_0029229c / L_002924c4 the other casts.
//   * L_0029299c the per-target part: the effect animation (sub_29EA60 .. sub_2A16C0 screen work, sub_2BAF90 cameras,
//     sub_2DD4A0 / sub_2DD5E0 sounds), then for every target record (the loop at L_00292d60) and every hit (the loop
//     at L_0029361c) the reactions, the damage numbers sub_2D7E20 with the 40-byte result records on the frame, the
//     HP gauges sub_2D8090, the status icons sub_2BD850 / sub_2BDBD0, knock-downs and the down sequences.
//   * L_00294b78 onward the follow-ups (the 1 More / down checks sub_2DC130), the state change.
// Every packet carries the action's uid (s0). The compiled control flow is kept: where it is not a plain if / else
// the original block addresses are the labels (L_<address>), so each part can be read next to the disassembly.
void Cpu::skill_update() {
    enter(54);
    sp = addiu(sp, -1344);
    sd(ra, sp, 160);
    sq(s8, sp, 144);
    sq(s7, sp, 128);
    sq(s6, sp, 112);
    sq(s5, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s4 = a0;
    lw(v0, a0, 48);
    lb(s6, v0, kUnitSide);
    lw(v0, v0, 2560);
    sw(v0, sp, 1104);
    lh(s7, a0, 110);
    lw(v0, a0, 56);
    sw(v0, sp, 1120);
    sd(zero, sp, 1040);
    sd(zero, sp, 1024);
    sw(zero, sp, 912);
    sw(zero, sp, 896);
    sh(zero, sp, 800);
    sh(zero, sp, 976);
    sw(zero, sp, 928);
    sw(zero, sp, 752);
    sw(zero, sp, 720);
    sw(zero, sp, 704);
    sw(zero, sp, 688);
    sw(zero, sp, 684);
    sw(zero, sp, 656);
    sw(zero, sp, 640);
    sw(zero, sp, 636);
    v0 = daddiu(zero, 6);
    sh(v0, sp, 768);
    skill_rec(v0, v1, s7);
    lbu(v0, v0, 0);
    v0 = v0 & 0x2;
    v0 = sltu(zero, v0);
    sq(v0, sp, 480);
    lhu(v0, a0, 26);
    v0 = v0 & 0x10;
    v0 = sltu(zero, v0);
    sq(v0, sp, 464);
    if (v0 != 0) {
        charge(4);
        lq(v0, sp, 480);
        v0 = v0 ^ zero;
        v0 = sltiu(v0, 1);
        sq(v0, sp, 464);
    }
    charge(29);
    lhu(v0, s4, kActMoveKind);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
    sq(v0, sp, 448);
    a0 = s4;
    jal(0x290cdc, rg::fn_sub_2D6290_002d6290);
    sw(v0, sp, 748);
    a0 = s7;
    jal(0x290cec, rg::fn_datCalcIsHpSkill_002d6370);
    sq(v0, sp, 432);
    lhu(a0, s4, 114);
    jal(0x290cfc, rg::fn_sub_308A50_00308a50);
    sq(v0, sp, 416);
    sw(zero, sp, 1088);
    ld(s0, s4, kActUid);
    a0 = s4;
    jal(0x290d14, rg::fn_sub_28A780_0028a780);
    a0 = li(1);
    jal(0x290d20, rg::fn_sub_2B8F90_002b8f90);
    sw(v0, sp, 1080);
    lhu(v0, s4, kActFlags);
    v0 = v0 & 0x100;
    if (v0 != 0) {
        charge(1);
        s6 = li(-1);
    }
    charge(7);
    v1 = li(1);
    v0 = daddiu(zero, 1);
    sh(v0, sp, 784);
    s6 = sx8(s6);
    if (s6 != 0) goto L_00290dc0;
    charge(5);
    lw(a0, s4, kActUnit);
    lhu(v1, a0, 164);
    v0 = li(10);
    if (v1 != v0) {
        charge(3);
        v0 = li(3);
        if (v1 == v0) goto L_00290d84;
        charge(2);
        goto L_00290d8c;
    }
L_00290d84:
    charge(2);
    v0 = daddiu(zero, 16);
    sh(v0, sp, 784);
L_00290d8c:
    charge(4);
    jal(0x290d8c, rg::fn_sub_2D5BF0_002d5bf0);
    if (v0 == 0) {
        charge(5);
        lw(a0, s4, kActUnit);
        jal(0x290da0, rg::fn_sub_2D5C70_002d5c70);
        if (v0 == 0) goto L_00290e1c;
    }
    charge(4);
    v0 = daddiu(zero, 16);
    sh(v0, sp, 784);
    goto L_00290e1c;
L_00290dc0:
    charge(2);
    if (s6 != v1) goto L_00290e1c;
    charge(5);
    lw(v0, s4, kActUnit);
    lhu(v1, v0, 164);
    v0 = li(238);
    if (v1 != v0) {
        charge(3);
        v0 = li(233);
        if (v1 == v0) goto L_00290e14;
        charge(3);
        v0 = li(294);
        if (v1 == v0) goto L_00290e14;
        charge(3);
        v0 = li(272);
        if (v1 == v0) goto L_00290e14;
        charge(3);
        v0 = li(267);
        if (v1 == v0) goto L_00290e14;
        charge(2);
        goto L_00290e1c;
    }
L_00290e14:
    charge(2);
    v0 = daddiu(zero, 16);
    sh(v0, sp, 784);
L_00290e1c:
    charge(2);
    if (ltz(s6)) goto L_00290f94;
    charge(3);
    lw(v0, sp, 748);
    if (v0 != 0) {
        charge(13);
        lw(v0, s4, kActTarget);
        lw(a0, s4, kActUnit);
        lw(a1, v0, 48);
        a2 = 0;
        jal(0x290e40, rg::fn_sub_282650_00282650);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        enqueue(0x290e54, 0);
        goto L_00290f14;
    }
    charge(2);
    if (s6 != 0) {
        charge(5);
        lw(a0, s4, kActUnit);
        jal(0x290ecc, rg::fn_sub_2FDCB0_002fdcb0);
        if (v0 == 0) goto L_00290f14;
        charge(14);
        lw(a0, s4, kActUnit);
        a1 = addiu(sp, 1304);
        jal(0x290ee4, rg::fn_sub_2FDDB0_002fddb0);
        lw(a0, s4, kActUnit);
        a1 = addiu(sp, 1304);
        a2 = 0;
        jal(0x290ef8, rg::fn_sub_2822B0_002822b0);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        enqueue(0x290f0c, 0);
    } else {
        charge(23);
        a0 = addiu(s4, 56);
        jal(0x290e70, rg::fn_btlTargetGetSideMask_002d1600);
        a0 = v0 & 0xFFFF;
        a1 = li(1);
        a2 = addiu(sp, 1304);
        a3 = 0;
        t0 = 0;
        t1 = a1;
        jal(0x290e90, rg::fn_sub_280870_00280870);
        lw(a0, s4, kActUnit);
        a1 = addiu(sp, 1304);
        a2 = 0;
        jal(0x290ea4, rg::fn_sub_2822B0_002822b0);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        enqueue(0x290eb8, 0);
    }
L_00290f14:
    charge(32);
    a0 = 0;
    lw(a1, s4, kActUnit);
    a2 = li(3);
    jal(0x290f20, rg::fn_sub_2886E0_002886e0);
    a0 = v0;
    stamp_owner(s4);
    enqueue(0x290f38, 1);
    lw(a0, s4, kActUnit);
    a1 = 0;
    jal(0x290f48, rg::fn_sub_288950_00288950);
    a0 = v0;
    stamp_owner(s4);
    enqueue(0x290f60, 1);
    lhu(v0, s4, kActFlags);
    v0 = v0 | 0x200;
    sh(v0, s4, kActFlags);
    a0 = s4;
    jal(0x290f78, rg::fn_sub_2D8330_002d8330);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x290f8c, 1);
    // ---- the cast effect packet (+72 = 3 with the effect record flag 0x100, else 1): an item's sub_2BD690 or sub_2BD590
L_00290f94:
    charge(9);
    v0 = sll(s7, 3);
    v0 = subu(v0, s7);
    s8 = sll(v0, 2);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x100;
    if (v0 == 0) {
        charge(1);
        v0 = li(1);
    } else {
        charge(3);
        v0 = li(3);
    }
    charge(6);
    v0 = sx16(v0);
    sq(v0, sp, 400);
    lq(v0, sp, 448);
    if (v0 != 0) {
        charge(11);
        lw(a0, s4, kActUnit);
        lhu(a1, s4, 112);
        jal(0x29101c, rg::fn_sub_2BD690_002bd690);
        a0 = v0;
        lq(v1, sp, 400);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x291038, 3);
    } else {
        charge(13);
        a1 = s7 & 0xFFFF;
        lw(a0, s4, kActUnit);
        jal(0x290fe8, rg::fn_sub_2BD590_002bd590);
        a0 = v0;
        lq(v1, sp, 400);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x291004, 3);
    }
    charge(4);
    v1 = li(1);
    lq(v0, sp, 464);
    if (v0 != v1) goto L_002924c4;
    charge(3);
    v0 = li(-1);
    if (s6 == v0) goto L_002924c4;
    charge(3);
    lq(v0, sp, 448);
    if (v0 != 0) goto L_00291b4c;
    charge(3);
    lq(v0, sp, 416);
    if (v0 != 0) goto L_00291b4c;
    charge(2);
    if (s6 != 0) {
        charge(2);
        if (s6 != v1) goto L_00291164;
        charge(4);
        lhu(v0, s4, kActFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) goto L_00291164;
        charge(8);
        a0 = s4;
        jal(0x291134, rg::fn_sub_2E33F0_002e33f0);
        s1 = sx16(v0);
        v0 = li(-1);
        if (s1 == v0) goto L_00291164;
        charge(5);
        v0 = li(1);
        sw(v0, sp, 752);
        lhu(v0, s4, kActFlags);
        v0 = v0 | 0x40;
        sh(v0, s4, kActFlags);
    } else {
        charge(4);
        lhu(v0, s4, kActFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) goto L_00291164;
        charge(10);
        lw(v0, s4, kActUnit);
        lhu(a0, v0, 164);
        jal(0x291094, rg::fn_sub_2DDC80_002ddc80);
        s2 = v0;
        a0 = s4;
        jal(0x2910a4, rg::fn_sub_2D5EB0_002d5eb0);
        if (v0 == 0) {
            charge(2);
            if (s2 == 0) goto L_00291164;
        }
        charge(8);
        a0 = s4;
        jal(0x2910c0, rg::fn_sub_2E33F0_002e33f0);
        s1 = sx16(v0);
        v0 = li(-1);
        if (s1 == v0) goto L_00291164;
        charge(6);
        a0 = li(100);
        jal(0x2910e0, rg::fn_datCalcRand_002ffbc0);
        v0 = sltiu(v0, 20);
        if (v0 == 0) {
            charge(2);
            if (s2 == 0) goto L_00291164;
        }
        charge(7);
        v0 = li(1);
        sw(v0, sp, 752);
        lhu(v0, s4, kActFlags);
        v0 = v0 | 0x40;
        sh(v0, s4, kActFlags);
    }
    // ---- the summon: the camera triple of sub_2FCAA0 (default gBtl+3220..3228) and the cut-in / follow-up flags (sp+720)
L_00291164:
    charge(6);
    a0 = s4;
    a1 = addiu(sp, 1320);
    jal(0x29116c, rg::fn_sub_2FCAA0_002fcaa0);
    if (v0 == 0) {
        charge(7);
        gbtl(v1);
        lw(v0, v1, 3220);
        sw(v0, sp, 1320);
        lw(v0, v1, 3224);
        sw(v0, sp, 1324);
        lw(v0, v1, 3228);
        sw(v0, sp, 1328);
    }
    charge(5);
    a0 = s7;
    jal(0x29119c, rg::fn_datCalcIsHpSkill_002d6370);
    if (v0 != 0) goto L_00291224;
    charge(5);
    a0 = s4;
    jal(0x2911b0, rg::fn_sub_2D5F50_002d5f50);
    if (v0 != 0) goto L_00291224;
    charge(6);
    a0 = addiu(s4, 56);
    jal(0x2911c4, rg::fn_btlTargetGetSideMask_002d1600);
    a0 = v0 & 0xFFFF;
    if (s6 == 0) {
        charge(4);
        v1 = a0 & 0xFFFF;
        v0 = li(2);
        if (v1 != v0) goto L_00291208;
        charge(8);
        a0 = 0;
        jal(0x2911ec, rg::fn_sub_357FD0_00357fd0);
        v0 = v0 & 0x1;
        v0 = sltu(zero, v0);
        sw(v0, sp, 720);
        goto L_00291224;
    }
L_00291208:
    charge(3);
    v1 = li(1);
    if (s6 == v1) {
        charge(3);
        v0 = a0 & 0xFFFF;
        if (v0 != v1) goto L_00291224;
        charge(1);
        sw(v1, sp, 720);
    }
L_00291224:
    charge(6);
    a0 = s4;
    lw(a1, sp, 1104);
    jal(0x29122c, rg::fn_sub_2FDBB0_002fdbb0);
    if (v0 == 0) {
        charge(5);
        gbtl(v0);
        lw(v0, v0, 16);
        v0 = v0 & 0x40;
        if (v0 == 0) goto L_00291258;
    }
    charge(2);
    v0 = li(1);
    sw(v0, sp, 720);
L_00291258:
    charge(6);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x4000;
    if (v0 != 0) {
        charge(4);
        v0 = li(1);
        sw(v0, sp, 720);
        v0 = li(12);
        sw(v0, sp, 928);
    }
    charge(2);
    if (s6 == 0) {
        charge(5);
        a0 = s4;
        jal(0x29128c, rg::fn_sub_2D62D0_002d62d0);
        if (v0 == 0) goto L_00291304;
        charge(3);
        v0 = li(234);
        if (s7 == v0) goto L_00291304;
        charge(23);
        v0 = li(1);
        sw(v0, sp, 640);
        sw(v0, sp, 720);
        sw(zero, sp, 752);
        a0 = 0;
        a1 = li(3);
        jal(0x2912c0, rg::fn_sub_288950_00288950);
        a0 = v0;
        stamp_owner(s4);
        enqueue(0x2912d8, 1);
        gbtl(a0);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        gbtl(v1);
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
    }
L_00291304:
    charge(2);
    if (s6 == 0) {
        charge(5);
        a0 = s4;
        jal(0x291310, rg::fn_sub_2D5FB0_002d5fb0);
        if (v0 == 0) goto L_00291354;
        charge(13);
        a0 = s4;
        a1 = li(16);
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(0x291334, rg::fn_sub_2E2BE0_002e2be0);
        a0 = v0;
        enqueue(0x291344, 1);
        goto L_00291380;
    }
L_00291354:
    charge(3);
    lw(v0, sp, 752);
    if (v0 != 0) {
        charge(8);
        lw(a0, s4, kActUnit);
        jal(0x291364, rg::fn_sub_2DD960_002dd960);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        enqueue(0x291378, 1);
    }
L_00291380:
    charge(3);
    v0 = li(1);
    if (s6 != v0) {
        charge(1);
        v1 = li(6);
    } else {
        charge(8);
        lw(a0, s4, kActUnit);
        jal(0x291390, rg::fn_sub_2F9690_002f9690);
        v1 = sx16(v0);
        v0 = li(-1);
        if (v1 != v0) goto L_002913bc;
        charge(3);
        v1 = li(6);
    }
L_002913bc:
    charge(17);
    a2 = v1 & 0xFFFF;
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(12);
    a3 = li(4);
    jal(0x2913d4, rg::fn_sub_284200_00284200);
    s3 = v0;
    sd(s0, v0, kPktOwner);
    a0 = s3;
    enqueue(0x2913ec, 1);
    ld(s3, s3, kPktId);
    if (s6 == 0) {
        charge(24);
        lw(a0, s4, kActUnit);
        jal(0x291404, rg::fn_sub_286240_00286240);
        a0 = v0;
        depend_id(0, 4, s3);
        sd(s0, v0, kPktOwner);
        enqueue(0x291424, 1);
        lw(a0, s4, kActUnit);
        jal(0x291430, rg::fn_sub_2860B0_002860b0);
        a0 = v0;
        depend_id(0, 4, s3);
        v1 = li(6);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x291458, 1);
    }
    charge(11);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(12);
    jal(0x291470, rg::fn_sub_2838D0_002838d0);
    v0 = sx16(v0);
    s2 = addiu(v0, 6);
    if (s6 != 0) {
        charge(1);
        v0 = li(17);
    } else {
        charge(3);
        v0 = li(16);
    }
    charge(14);
    a1 = v0 & 0xFFFF;
    a0 = s4;
    jal(0x2914a4, rg::fn_sub_2A3B40_002a3b40);
    s5 = v0;
    sd(s0, v0, kPktOwner);
    a0 = s5;
    enqueue(0x2914bc, 0);
    ld(s5, s5, kPktId);
    lw(v0, sp, 752);
    if (v0 != 0) {
        charge(83);
        a0 = s1 & 0xFFFF;
        lw(v0, sp, 1104);
        lhu(a1, v0, 164);
        jal(0x2914e0, rg::fn_sub_2E35D0_002e35d0);
        s2 = v0;
        depend_id(0, 4, s3);
        sd(s0, v0, kPktOwner);
        a0 = s2;
        enqueue(0x291504, 1);
        jal(0x29150c, rg::fn_sub_2E36F0_002e36f0);
        s1 = v0;
        depend(0, 4, s2);
        sd(s0, v0, kPktOwner);
        a0 = s1;
        enqueue(0x291534, 1);
        lw(v0, sp, 1104);
        lhu(a2, v0, 164);
        a0 = s4;
        a1 = li(12);
        a3 = 0;
        t0 = 0;
        jal(0x291554, rg::fn_sub_2E2BE0_002e2be0);
        a0 = v0;
        depend(0, 5, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x291578, 1);
        a0 = li(10);
        a1 = li(2);
        a2 = li(18);
        jal(0x29158c, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        a1 = li(5);
        sb(a1, v0, 0);
        ld(v1, s1, kPktId);
        sd(v1, v0, 8);
        sh(a1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x2915b4, 1);
        lw(a0, s4, kActUnit);
        jal(0x2915c0, rg::fn_sub_2DD8E0_002dd8e0);
        a0 = v0;
        depend(0, 4, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x2915e4, 1);
        ld(s3, s1, kPktId);
        sd(s3, sp, 1024);
        s2 = 0;
        jal(0x2915f8, rg::fn_sub_2E37E0_002e37e0);
        a0 = v0;
        depend_id(0, 4, s3);
        sd(s0, v0, kPktOwner);
        enqueue(0x291618, 1);
    }
    charge(24);
    lhu(v0, s4, kActFlags);
    v0 = v0 & 0x10;
    a1 = sltu(zero, v0);
    a0 = s4;
    a2 = li(1);
    jal(0x291634, rg::fn_sub_2B8900_002b8900);
    s1 = v0;
    depend_id(0, 4, s3);
    v1 = sra(s2, 3);
    v1 = subu(s2, v1);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s1;
    enqueue(0x291664, 0);
    ld(v0, s1, kPktId);
    sd(v0, sp, 1040);
    lw(v0, sp, 748);
    if (v0 == 0) {
        charge(1);
        a2 = 0;
    } else {
        charge(3);
        lw(a2, s4, kActTarget);
    }
    charge(17);
    a3 = s7 & 0xFFFF;
    lw(a0, sp, 1104);
    a1 = s4;
    jal(0x29169c, rg::fn_sub_2B8B70_002b8b70);
    a0 = v0;
    depend_id_at(0, 5, 1040);
    sd(s0, v0, kPktOwner);
    enqueue(0x2916c0, 0);
    lw(v0, sp, 752);
    if (v0 == 0) {
        charge(8);
        lw(a0, sp, 1104);
        v0 = a0;
        lhu(a1, v0, 164);
        a2 = li(13);
        jal(0x291724, rg::fn_sub_285690_00285690);
        s1 = v0;
        sh(s2, v0, kPktTime);
    } else {
        charge(16);
        lw(a0, sp, 1104);
        v0 = a0;
        lhu(a1, v0, 164);
        a2 = li(29);
        jal(0x2916e4, rg::fn_sub_285690_00285690);
        s1 = v0;
        a0 = li(5);
        sb(a0, v0, 0);
        ld(v1, sp, 1024);
        sd(v1, v0, 8);
        sb(a0, v0, 32);
        ld(v1, sp, 1040);
        sd(v1, v0, 40);
    }
    charge(73);
    sd(s0, s1, 96);
    a0 = s1;
    enqueue(0x291740, 1);
    jal(0x291748, rg::fn_sub_27F2F0_0027f2f0);
    s2 = v0;
    depend(0, 4, s1);
    v1 = li(12);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s2;
    enqueue(0x291778, 1);
    lw(a0, sp, 1320);
    lw(a1, s4, kActUnit);
    a2 = 0;
    ld(a3, s2, kPktId);
    t0 = li(256);
    jal(0x291794, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x2917a8, 2);
    a0 = li(10);
    a1 = li(2);
    a2 = 0;
    jal(0x2917bc, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x2917d0, 1);
    lw(a1, s4, kActUnit);
    lw(a0, a1, 2560);
    a2 = s7;
    lw(a3, sp, 748);
    jal(0x2917e8, rg::fn_sub_284040_00284040);
    v0 = sx16(v0);
    sh(v0, sp, 1008);
    lw(v1, s4, kActUnit);
    v0 = v0;
    a1 = v0 & 0xFFFF;
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, v1, 2560);
    jal(0x291814, rg::fn_sub_2835E0_002835e0);
    v0 = sx16(v0);
    sw(v0, sp, 944);
    lw(a0, s4, kActUnit);
    a1 = li(15);
    jal(0x291830, rg::fn_sub_283A70_00283a70);
    sh(v0, sp, 768);
    ld(s1, s1, kPktId);
    lw(v0, sp, 944);
    v1 = addiu(v0, 18);
    lw(v0, sp, 928);
    at = slt(v0, v1);
    if (at == 0) {
        charge(1);
        s2 = 0;
    } else {
        charge(3);
        s2 = subu(v1, v0);
    }
    charge(142);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(14);
    a2 = 0;
    a3 = li(5);
    jal(0x291880, rg::fn_sub_284200_00284200);
    a0 = v0;
    depend_id(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x2918a0, 1);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(14);
    jal(0x2918b8, rg::fn_sub_2835E0_002835e0);
    s3 = sx16(v0);
    lw(a0, sp, 1324);
    lw(a1, s4, kActUnit);
    a2 = 0;
    a3 = 0;
    t0 = li(256);
    jal(0x2918dc, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend_id(0, 4, s1);
    sh(s3, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x291900, 2);
    a0 = li(12);
    a1 = li(2);
    lhu(a2, sp, 784);
    jal(0x291914, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend_id(0, 4, s1);
    sh(s3, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x291938, 1);
    lw(a0, sp, 1328);
    lw(a1, s4, kActUnit);
    a2 = 0;
    a3 = 0;
    t0 = li(256);
    jal(0x291954, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend_id(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x291974, 2);
    a0 = li(13);
    a1 = li(2);
    a2 = a1;
    jal(0x291988, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend_id(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x2919a8, 1);
    lw(a0, s4, kActUnit);
    v0 = lui(0xFF80);
    a1 = v0 | 0x8080;
    a2 = 0;
    a3 = li(12);
    t0 = li(4);
    t1 = 0;
    jal(0x2919cc, rg::fn_sub_285D30_00285d30);
    a0 = v0;
    depend_id(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x2919ec, 1);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, sp, 1104);
    lh(a1, sp, 1008);
    a2 = 0;
    a3 = li(2);
    jal(0x291a0c, rg::fn_sub_284200_00284200);
    s3 = v0;
    depend_id(0, 4, s1);
    v1 = li(15);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s3;
    enqueue(0x291a38, 1);
    lw(a0, sp, 1104);
    jal(0x291a44, rg::fn_sub_27FC80_0027fc80);
    lw(a0, sp, 1104);
    a1 = v0;
    a2 = li(8);
    a3 = 0;
    t0 = li(3);
    t1 = li(1);
    jal(0x291a64, rg::fn_sub_285D30_00285d30);
    a0 = v0;
    depend(0, 4, s3);
    sd(s0, v0, kPktOwner);
    enqueue(0x291a88, 1);
    v1 = li(1);
    lw(v0, sp, 720);
    if (v0 == v1) {
        charge(3);
        lw(v0, sp, 640);
        if (v0 != 0) goto L_00291b3c;
        charge(6);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x40;
        if (v0 != 0) goto L_00291b3c;
        charge(2);
        if (s6 != 0) {
            charge(1);
            v0 = li(22);
        } else {
            charge(3);
            v0 = li(21);
        }
        charge(14);
        a1 = v0 & 0xFFFF;
        a0 = s4;
        jal(0x291ae4, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend(0, 4, s3);
        lw(v1, sp, 944);
        lw(v0, sp, 928);
        v0 = slt(v1, v0);
        if (v0 != 0) {
            charge(1);
            v0 = 0;
        } else {
            charge(4);
            lw(v0, sp, 928);
            v0 = subu(v1, v0);
        }
        charge(5);
        sh(v0, a0, kPktTime);
        sd(s0, a0, 96);
        enqueue(0x291b34, 0);
    }
L_00291b3c:
    charge(4);
    ld(v0, s3, kPktId);
    sd(v0, sp, 1056);
    goto L_0029299c;
    // ---- an item, or a direct skill (sub_308A50(+114) == 1): the use motion 12, message 16, the item effect sub_2E3DE0 / sub_2E3F20 and its name (sprintf into the frame, sub_2DD690)
L_00291b4c:
    charge(3);
    lq(v0, sp, 448);
    if (v0 != 0) goto L_0029229c;
    charge(4);
    v1 = li(1);
    lq(v0, sp, 416);
    if (v0 != v1) goto L_0029229c;
    charge(85);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(12);
    a2 = li(6);
    a3 = li(4);
    jal(0x291b80, rg::fn_sub_284200_00284200);
    s1 = v0;
    sd(s0, v0, kPktOwner);
    a0 = s1;
    enqueue(0x291b98, 1);
    ld(s2, s1, kPktId);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(12);
    jal(0x291bb4, rg::fn_sub_2838D0_002838d0);
    s3 = sx16(v0);
    a0 = s4;
    a1 = li(16);
    jal(0x291bcc, rg::fn_sub_2A3B40_002a3b40);
    s1 = v0;
    depend_id(0, 4, s2);
    sd(s0, v0, kPktOwner);
    a0 = s1;
    enqueue(0x291bf0, 0);
    ld(s5, s1, kPktId);
    lw(v0, s4, kActUnit);
    lhu(a0, v0, 164);
    lhu(a1, s4, 114);
    jal(0x291c08, rg::fn_sub_2E3DE0_002e3de0);
    s1 = v0;
    depend_id(0, 4, s2);
    v1 = addiu(s3, 6);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s1;
    enqueue(0x291c34, 1);
    jal(0x291c3c, rg::fn_sub_2E3F20_002e3f20);
    s2 = v0;
    depend(0, 4, s1);
    v1 = li(23);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s2;
    enqueue(0x291c6c, 1);
    a0 = li(3);
    a1 = lui(0x69);
    a1 = addiu(a1, 13096);
    jal(0x291c80, rg::fn_sub_2DD690_002dd690);
    a0 = v0;
    depend(0, 5, s2);
    sd(s0, v0, kPktOwner);
    enqueue(0x291ca4, 1);
    lhu(a2, s4, 114);
    v0 = li(285);
    if (a2 != v0) {
        charge(3);
        v0 = li(284);
        if (a2 == v0) goto L_00291d40;
        charge(3);
        v0 = li(279);
        if (a2 == v0) goto L_00291d40;
        charge(3);
        v0 = li(276);
        if (a2 == v0) goto L_00291d40;
        charge(3);
        v0 = li(275);
        if (a2 == v0) goto L_00291d40;
        charge(21);
        a0 = addiu(sp, 1136);
        a1 = lui(0x69);
        a1 = addiu(a1, 13112);
        jal(0x291cf8, rg::fn_sprintf_00523ac8);
        a0 = li(3);
        a1 = addiu(sp, 1136);
        jal(0x291d08, rg::fn_sub_2DD690_002dd690);
        a0 = v0;
        a1 = li(10);
        sb(a1, v0, 0);
        v1 = li(1024);
        sh(v1, v0, 8);
        sb(a1, v0, 16);
        v1 = li(2307);
        sh(v1, v0, 24);
        sd(s0, v0, kPktOwner);
        enqueue(0x291d38, 1);
    }
L_00291d40:
    charge(11);
    ld(v0, s1, kPktId);
    sd(v0, sp, 1024);
    v0 = li(1);
    sw(v0, sp, 752);
    lw(v0, gp, -18672);
    v0 = addiu(v0, 2);
    v0 = addu(v0, s8);
    lhu(v1, v0, 0);
    v0 = v1 & 0x400;
    if (v0 == 0) {
        charge(3);
        s1 = li(2);
        v0 = li(25);
        sh(v0, sp, 512);
    } else {
        charge(5);
        s1 = li(2);
        v0 = li(24);
        sh(v0, sp, 512);
    }
    charge(3);
    v0 = v1 & 0x1000;
    if (v0 != 0) {
        charge(6);
        a0 = s4;
        jal(0x291d9c, rg::fn_sub_2D62D0_002d62d0);
        sw(v0, sp, 636);
        if (v0 != 0) {
            charge(2);
            v0 = li(1);
            sw(v0, sp, 640);
        }
        charge(19);
        a0 = 0;
        a1 = li(3);
        jal(0x291dc0, rg::fn_sub_288950_00288950);
        a0 = v0;
        stamp_owner(s4);
        enqueue(0x291dd8, 1);
        gbtl(a0);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        gbtl(v1);
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
    }
    charge(257);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    a3 = s1 & 0xFFFF;
    lw(a0, s4, kActUnit);
    a1 = li(23);
    a2 = 0;
    jal(0x291e1c, rg::fn_sub_284200_00284200);
    s1 = v0;
    depend_id_at(0, 4, 1024);
    sd(s0, v0, kPktOwner);
    a0 = s1;
    enqueue(0x291e44, 1);
    jal(0x291e4c, rg::fn_sub_27F2F0_0027f2f0);
    s3 = v0;
    depend(0, 4, s1);
    v1 = li(12);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = s3;
    enqueue(0x291e7c, 1);
    gbtl(v0);
    lw(a0, v0, 3220);
    lw(a1, s4, kActUnit);
    a2 = 0;
    ld(a3, s3, kPktId);
    t0 = li(256);
    jal(0x291e9c, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x291eb0, 2);
    a0 = li(10);
    a1 = li(2);
    a2 = 0;
    jal(0x291ec4, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x291ed8, 1);
    gbtl(v0);
    lw(a0, v0, 3224);
    lw(a1, s4, kActUnit);
    a2 = 0;
    a3 = 0;
    t0 = li(256);
    jal(0x291ef8, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x291f1c, 2);
    a0 = li(12);
    a1 = li(2);
    lhu(a2, sp, 784);
    jal(0x291f30, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x291f54, 1);
    gbtl(v0);
    lw(a0, v0, 3228);
    lw(a1, s4, kActUnit);
    a2 = 0;
    a3 = 0;
    t0 = li(256);
    jal(0x291f74, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x291f98, 2);
    a0 = li(13);
    a1 = li(2);
    a2 = a1;
    jal(0x291fac, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 4, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x291fd0, 1);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    lh(a1, sp, 512);
    a2 = 0;
    a3 = li(2);
    jal(0x291ff0, rg::fn_sub_284200_00284200);
    s3 = v0;
    depend(0, 4, s2);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(23);
    jal(0x29201c, rg::fn_sub_2838D0_002838d0);
    sh(v0, s3, kPktTime);
    sd(s0, s3, 96);
    a0 = s3;
    enqueue(0x292034, 1);
    ld(s1, s3, kPktId);
    s2 = 0;
    lhu(v0, sp, 512);
    a1 = v0;
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    jal(0x292058, rg::fn_sub_2835E0_002835e0);
    v0 = sx16(v0);
    s2 = addu(s2, v0);
    jal(0x29206c, rg::fn_sub_27F2F0_0027f2f0);
    sw(v0, sp, 532);
    depend(0, 4, s3);
    v1 = li(12);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    a0 = v0;
    enqueue(0x29209c, 1);
    gbtl(v0);
    lw(a0, v0, 3220);
    lw(a1, s4, kActUnit);
    a2 = 0;
    lw(v0, sp, 532);
    ld(a3, v0, kPktId);
    t0 = li(256);
    jal(0x2920c0, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend_id_at(0, 4, 1024);
    sd(s0, v0, kPktOwner);
    enqueue(0x2920e4, 2);
    a0 = li(10);
    a1 = li(2);
    a2 = 0;
    jal(0x2920f8, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend_id_at(0, 4, 1024);
    sd(s0, v0, kPktOwner);
    enqueue(0x29211c, 1);
    gbtl(v0);
    lw(a0, v0, 3340);
    lw(a1, s4, kActUnit);
    a2 = 0;
    a3 = 0;
    t0 = li(256);
    jal(0x29213c, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend(0, 4, s3);
    sh(zero, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x292164, 2);
    a0 = li(14);
    a1 = li(2);
    a2 = li(3);
    jal(0x292178, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 4, s3);
    sh(zero, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x2921a0, 1);
    lw(a0, s4, kActUnit);
    v0 = lui(0xFF80);
    a1 = v0 | 0x8080;
    a2 = 0;
    a3 = li(12);
    t0 = li(4);
    t1 = 0;
    jal(0x2921c4, rg::fn_sub_285D30_00285d30);
    a0 = v0;
    depend(0, 4, s3);
    sd(s0, v0, kPktOwner);
    enqueue(0x2921e8, 1);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x1000;
    if (v0 != 0) {
        charge(3);
        lw(v0, sp, 636);
        if (v0 != 0) goto L_0029228c;
        charge(30);
        lw(v0, s4, kActTarget);
        sw(v0, sp, 1120);
        a0 = s4;
        a1 = li(21);
        jal(0x292224, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_id(0, 4, s1);
        sh(s2, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x292248, 0);
        lw(v0, sp, 1120);
        lw(a0, v0, 48);
        lw(a1, s4, kActUnit);
        a2 = li(2);
        jal(0x292260, rg::fn_sub_282650_00282650);
        a0 = v0;
        depend_id(0, 4, s1);
        sh(s2, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x292284, 0);
    }
L_0029228c:
    charge(4);
    ld(v0, s3, kPktId);
    sd(v0, sp, 1040);
    goto L_0029299c;
    // ---- the other casts: motions 21 / 23 and their cameras
L_0029229c:
    charge(4);
    v1 = li(1);
    lq(v0, sp, 448);
    if (v0 != v1) goto L_0029299c;
    charge(3);
    lq(v0, sp, 416);
    if (v0 != 0) goto L_0029299c;
    charge(2);
    if (s6 == 0) {
        charge(5);
        a0 = s4;
        jal(0x2922c4, rg::fn_sub_2D62D0_002d62d0);
        if (v0 == 0) goto L_00292338;
        charge(3);
        v0 = li(234);
        if (s7 == v0) goto L_00292338;
        charge(22);
        v0 = li(1);
        sw(v0, sp, 640);
        sw(v0, sp, 720);
        a0 = 0;
        a1 = li(3);
        jal(0x2922f4, rg::fn_sub_288950_00288950);
        a0 = v0;
        stamp_owner(s4);
        enqueue(0x29230c, 1);
        gbtl(a0);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        gbtl(v1);
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
    }
L_00292338:
    charge(31);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(21);
    a2 = li(6);
    a3 = 0;
    jal(0x292350, rg::fn_sub_284200_00284200);
    s3 = v0;
    sd(s0, v0, kPktOwner);
    a0 = s3;
    enqueue(0x292368, 1);
    ld(s5, s3, kPktId);
    s1 = 0;
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    a1 = li(21);
    jal(0x292388, rg::fn_sub_2838D0_002838d0);
    v0 = sx16(v0);
    s2 = addiu(v0, 6);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x40;
    if (v0 == 0) {
        charge(6);
        a0 = s4;
        jal(0x2923b8, rg::fn_sub_2D6290_002d6290);
        a2 = li(1);
        if (v0 == a2) {
            charge(13);
            a0 = s4;
            a1 = 0;
            jal(0x2923d4, rg::fn_sub_2B8900_002b8900);
            a0 = v0;
            depend(0, 4, s3);
            sd(s0, v0, kPktOwner);
            enqueue(0x2923f8, 0);
        }
        charge(3);
        lw(v0, sp, 720);
        if (v0 != 0) {
            charge(13);
            a0 = s4;
            a1 = li(23);
            jal(0x292450, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            depend(0, 4, s3);
            sd(s0, v0, kPktOwner);
            enqueue(0x292474, 0);
        } else {
            charge(15);
            a0 = s4;
            a1 = li(21);
            jal(0x292414, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            depend(0, 4, s3);
            sd(s0, v0, kPktOwner);
            enqueue(0x292438, 0);
        }
    }
    charge(18);
    a2 = addiu(s2, 6);
    gbtl(v0);
    lw(a0, v0, 3332);
    lw(a1, s4, kActUnit);
    a3 = 0;
    t0 = li(256);
    jal(0x292494, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend(0, 4, s3);
    enqueue(0x2924b4, 1);
    goto L_0029299c;
    // ---- no summon animation (+26 bit 4 clear, or side -1): the enemy / plain cast (sub_2F8FD0, sub_2FD060)
L_002924c4:
    charge(3);
    lq(v0, sp, 464);
    if (v0 != 0) goto L_002927f4;
    charge(3);
    v0 = li(-1);
    if (s6 == v0) goto L_002927f4;
    charge(5);
    v0 = li(1);
    sw(v0, sp, 688);
    lq(v1, sp, 480);
    if (v1 != v0) {
        charge(5);
        a0 = s7;
        jal(0x2924f4, rg::fn_datCalcIsHpSkill_002d6370);
        if (v0 == 0) goto L_00292548;
    }
    charge(4);
    v1 = li(1);
    lq(v0, sp, 480);
    if (v0 != v1) {
        charge(9);
        lw(a0, s4, kActUnit);
        a1 = s7;
        jal(0x29251c, rg::fn_sub_2F8FD0_002f8fd0);
        s2 = sx16(v0);
        v0 = li(-1);
        if (s2 != v0) goto L_0029253c;
    }
    charge(1);
    s2 = li(4);
L_0029253c:
    charge(3);
    a3 = daddiu(zero, 2);
    goto L_00292574;
L_00292548:
    charge(9);
    lw(a0, s4, kActUnit);
    a1 = s7;
    jal(0x292550, rg::fn_sub_2F8FD0_002f8fd0);
    s2 = sx16(v0);
    v0 = li(-1);
    if (s2 == v0) {
        charge(1);
        s2 = li(7);
    }
    charge(1);
    a3 = daddiu(zero, 3);
L_00292574:
    charge(5);
    lw(a0, s4, kActUnit);
    lbu(v0, a0, kUnitSide);
    a1 = li(1);
    if (v0 == a1) {
        charge(12);
        lhu(v1, a0, 164);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, gp, -18648);
        v0 = addu(v1, v0);
        lh(v0, v0, 24);
        v0 = v0 & 0x1;
        if (v0 == 0) goto L_002925c4;
        charge(3);
        a3 = 0;
        sw(a1, sp, 684);
        sw(zero, sp, 688);
    }
L_002925c4:
    charge(6);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x100;
    if (v0 != 0) {
        charge(8);
        jal(0x292648, rg::fn_sub_27F2F0_0027f2f0);
        s3 = v0;
        sd(s0, v0, kPktOwner);
        a0 = s3;
        enqueue(0x292660, 1);
    } else {
        charge(27);
        v0 = lui(0x3F80);
        mtc1(v0, F12);
        a1 = s2;
        a2 = li(6);
        jal(0x2925ec, rg::fn_sub_284200_00284200);
        s3 = v0;
        sd(s0, v0, kPktOwner);
        a0 = s3;
        enqueue(0x292604, 1);
        a0 = s4;
        a1 = li(17);
        jal(0x292614, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend(0, 4, s3);
        sd(s0, v0, kPktOwner);
        enqueue(0x292638, 0);
    }
    charge(17);
    ld(s5, s3, kPktId);
    s1 = 0;
    a1 = s2 & 0xFFFF;
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s4, kActUnit);
    jal(0x292680, rg::fn_sub_2835E0_002835e0);
    v0 = sx16(v0);
    s2 = addiu(v0, 6);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x40;
    if (v0 == 0) {
        charge(15);
        lhu(v0, s4, kActFlags);
        v0 = v0 & 0x10;
        a1 = sltu(zero, v0);
        a0 = s4;
        a2 = li(1);
        jal(0x2926c0, rg::fn_sub_2B8900_002b8900);
        sw(v0, sp, 536);
        depend(0, 4, s3);
        at = slti(s2, 13);
        if (at != 0) {
            charge(1);
            v1 = 0;
        } else {
            charge(3);
            v1 = addiu(s2, -12);
        }
        charge(23);
        lw(v0, sp, 536);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a0 = v0;
        enqueue(0x29270c, 0);
        lw(v0, sp, 536);
        ld(v0, v0, kPktId);
        sd(v0, sp, 1040);
        a0 = s4;
        a1 = li(22);
        jal(0x292728, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_id_at(0, 4, 1040);
        sd(s0, v0, kPktOwner);
        enqueue(0x29274c, 0);
    }
    charge(3);
    lq(v0, sp, 480);
    if (v0 != 0) goto L_0029299c;
    charge(5);
    a0 = s4;
    jal(0x292764, rg::fn_sub_2FD060_002fd060);
    if (v0 == 0) {
        charge(2);
        gbtl(v0);
        lw(v0, v0, 3240);
    }
    charge(30);
    a2 = addiu(s2, 6);
    a0 = v0;
    lw(a1, s4, kActUnit);
    a3 = 0;
    t0 = li(256);
    jal(0x292790, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend(0, 4, s3);
    enqueue(0x2927b0, 1);
    a0 = li(10);
    a1 = li(2);
    a2 = li(5);
    jal(0x2927c4, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 4, s3);
    enqueue(0x2927e4, 1);
    goto L_0029299c;
    // ---- the persona cut-in of a follow-up (datPersonaGetByPcId, sub_2E35D0 / sub_2E36F0 / sub_2E37E0; messages 37 / 4)
L_002927f4:
    charge(7);
    s5 = 0;
    s1 = 0;
    s2 = 0;
    lhu(v0, s4, kActFlags);
    v0 = v0 & 0x100;
    if (v0 == 0) {
        charge(9);
        a0 = s4;
        a1 = li(37);
        jal(0x292980, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        sd(s0, v0, kPktOwner);
        enqueue(0x292994, 0);
    } else {
        charge(90);
        a0 = li(6);
        jal(0x292814, rg::fn_datPersonaGetByPcId_00174800);
        a0 = li(6);
        lhu(a1, v0, 2);
        jal(0x292824, rg::fn_sub_2E35D0_002e35d0);
        sw(v0, sp, 540);
        depend_id(0, 4, s3);
        sd(s0, v0, kPktOwner);
        a0 = v0;
        enqueue(0x292848, 1);
        jal(0x292850, rg::fn_sub_2E36F0_002e36f0);
        s1 = v0;
        depend_at(0, 4, 540);
        sd(s0, v0, kPktOwner);
        a0 = s1;
        enqueue(0x29287c, 1);
        a0 = li(3);
        a1 = lui(0x69);
        a1 = addiu(a1, 13128);
        jal(0x292890, rg::fn_sub_2DD690_002dd690);
        a0 = v0;
        depend(0, 5, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x2928b4, 1);
        ld(s1, s1, kPktId);
        jal(0x2928c0, rg::fn_sub_2E37E0_002e37e0);
        a0 = v0;
        depend_id(0, 4, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x2928e0, 1);
        a0 = s4;
        a1 = li(4);
        jal(0x2928f0, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_id(0, 4, s1);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x292914, 0);
        v0 = li(1);
        sw(v0, sp, 640);
        a0 = 0;
        a1 = li(3);
        jal(0x29292c, rg::fn_sub_288950_00288950);
        a0 = v0;
        stamp_owner(s4);
        enqueue(0x292944, 1);
        gbtl(a0);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        gbtl(v1);
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
    }
    // ---- the effect: the screen work (sub_29EA60 .. sub_2A1B00), its camera data (sub_2BB6F0 / sub_2BAC00), the effect and sound packets, the actor's cameras
L_0029299c:
    charge(86);
    v0 = s7 & 0xFFFF;
    sh(v0, sp, 592);
    lhu(a0, sp, 592);
    a1 = addiu(sp, 1340);
    a2 = addiu(sp, 1336);
    jal(0x2929b0, rg::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 1340);
    lw(a1, sp, 1336);
    a2 = li(16);
    jal(0x2929c4, rg::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    depend_id(0, 4, s5);
    sd(s0, v0, kPktOwner);
    enqueue(0x2929e4, 1);
    lhu(a0, sp, 592);
    jal(0x2929f0, rg::fn_sub_29EC00_0029ec00);
    sw(v0, sp, 508);
    lhu(a0, sp, 592);
    a1 = addiu(sp, 1340);
    a2 = addiu(sp, 1336);
    jal(0x292a08, rg::fn_sub_29EC80_0029ec80);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x2;
    v0 = sltu(zero, v0);
    t0 = v0 & 0xFFFF;
    lw(a0, sp, 508);
    lw(a1, sp, 1340);
    lw(a2, sp, 1336);
    a3 = li(16);
    jal(0x292a38, rg::fn_sub_2A0050_002a0050);
    a0 = v0;
    depend_id(0, 4, s5);
    sd(s0, v0, kPktOwner);
    enqueue(0x292a58, 1);
    v0 = s7 & 0xFFFF;
    sh(v0, sp, 576);
    lhu(a0, sp, 576);
    jal(0x292a6c, rg::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = li(16);
    jal(0x292a7c, rg::fn_sub_2A1280_002a1280);
    a0 = v0;
    depend_id(0, 4, s5);
    sd(s0, v0, kPktOwner);
    enqueue(0x292a9c, 1);
    a0 = s4;
    lhu(a1, sp, 576);
    a2 = li(8);
    jal(0x292ab0, rg::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    depend_id(0, 4, s5);
    sd(s0, v0, kPktOwner);
    enqueue(0x292ad0, 1);
    lhu(a0, sp, 576);
    a1 = addiu(sp, 1136);
    jal(0x292ae0, rg::fn_sub_2BB6F0_002bb6f0);
    lw(v0, sp, 752);
    if (v0 == 0) {
        charge(29);
        lw(a0, sp, 1080);
        a1 = addiu(sp, 1136);
        a2 = 0;
        jal(0x292bb0, rg::fn_sub_2BAC00_002bac00);
        sw(v0, sp, 1100);
        depend_id(0, 4, s1);
        sh(s2, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a0 = v0;
        enqueue(0x292bd8, 1);
        lhu(a0, sp, 592);
        a1 = 0;
        jal(0x292be8, rg::fn_sub_2DD4A0_002dd4a0);
        sw(v0, sp, 1096);
        depend_at(0, 4, 1100);
        a0 = v0;
        enqueue(0x292c10, 1);
    } else {
        charge(44);
        jal(0x292af4, rg::fn_sub_27F2F0_0027f2f0);
        s5 = v0;
        depend_id(0, 4, s1);
        sh(s2, v0, kPktTime);
        a0 = s5;
        enqueue(0x292b18, 1);
        lw(a0, sp, 1080);
        a1 = addiu(sp, 1136);
        a2 = li(1);
        jal(0x292b2c, rg::fn_sub_2BAC00_002bac00);
        sw(v0, sp, 1100);
        a0 = li(5);
        sb(a0, v0, 0);
        ld(v1, sp, 1024);
        sd(v1, v0, 8);
        sb(a0, v0, 32);
        ld(v1, s5, kPktId);
        sd(v1, v0, 40);
        sd(s0, v0, kPktOwner);
        a0 = v0;
        enqueue(0x292b60, 1);
        lhu(a0, sp, 592);
        a1 = li(1);
        jal(0x292b70, rg::fn_sub_2DD4A0_002dd4a0);
        sw(v0, sp, 1096);
        depend_id_at(0, 5, 1024);
        a0 = v0;
        enqueue(0x292b94, 1);
    }
    charge(4);
    lhu(v1, s4, 106);
    v0 = li(1);
    if (v1 != v0) {
        charge(1);
        lw(a2, s4, kActUnit);
    } else {
        charge(4);
        lw(v0, sp, 1120);
        lw(a2, v0, 48);
    }
    charge(22);
    lw(a0, sp, 1080);
    lw(a1, s4, kActUnit);
    a3 = 0;
    t0 = 0;
    jal(0x292c4c, rg::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = li(4);
    sb(a0, v0, 0);
    lw(v1, sp, 1100);
    ld(v1, v1, kPktId);
    sd(v1, v0, 8);
    sb(a0, v0, 16);
    lw(v1, sp, 1096);
    ld(v1, v1, kPktId);
    sd(v1, v0, 24);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        charge(1);
        sd(s0, s1, 96);
    }
    charge(22);
    a0 = s1;
    enqueue(0x292ca0, 2);
    ld(v0, s1, kPktId);
    sq(v0, sp, 384);
    a0 = 0;
    jal(0x292cb4, rg::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    depend(0, 5, s1);
    enqueue(0x292cd4, 1);
    a0 = s7;
    jal(0x292ce0, rg::fn_sub_2FDED0_002fded0);
    if (v0 != 0) {
        charge(12);
        a0 = v0;
        a1 = s4;
        jal(0x292cf8, rg::fn_sub_27F410_0027f410);
        a0 = v0;
        depend(0, 5, s1);
        enqueue(0x292d18, 1);
    }
    charge(16);
    sw(zero, sp, 1092);
    v0 = li(30);
    sh(v0, sp, 992);
    sh(zero, sp, 816);
    lhu(a0, sp, 592);
    jal(0x292d34, rg::fn_sub_2D4CC0_002d4cc0);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 368);
    sh(zero, sp, 960);
    sh(zero, sp, 880);
    v0 = sx16(s7);
    sw(v0, sp, 608);
    goto L_00293fa0;
    // ---- every chosen target (the loop closes at L_00293fa0)
L_00292d60:
    charge(15);
    lhu(v0, sp, 880);
    v0 = v0;
    v0 = sll(v0, 2);
    v0 = addu(s4, v0);
    lw(s2, v0, 56);
    lbu(v0, s2, 200);
    sh(v0, sp, 848);
    sh(zero, sp, 832);
    a0 = addiu(s2, 200);
    jal(0x292d84, rg::fn_sub_2B9640_002b9640);
    sq(v0, sp, 352);
    lw(v1, s2, 212);
    if (v1 == 0) {
        charge(1);
        s5 = s2;
    } else {
        charge(3);
        s5 = s4;
    }
    charge(3);
    lw(v0, s2, 208);
    if (v0 != 0) {
        charge(6);
        lw(a0, s4, kActUnit);
        lbu(a1, a0, kUnitSide);
        lw(a0, s5, 48);
        lbu(a0, a0, kUnitSide);
        if (a1 == a0) goto L_00292ddc;
        charge(3);
        lw(a0, sp, 912);
        a0 = addiu(a0, 1);
        sw(a0, sp, 912);
    }
L_00292ddc:
    charge(11);
    lhu(a0, sp, 848);
    a1 = a0;
    a0 = sll(a1, 3);
    a0 = subu(a0, a1);
    a0 = sll(a0, 2);
    a0 = addu(s2, a0);
    lw(a1, a0, 204);
    a0 = lui(0x10);
    a0 = a1 & a0;
    if (a0 != 0) {
        charge(7);
        lw(a0, sp, 896);
        a0 = addiu(a0, 1);
        sw(a0, sp, 896);
        lhu(a1, s2, 206);
        lhu(a0, sp, 800);
        a0 = a0 | a1;
        sh(a0, sp, 800);
    }
    charge(6);
    lw(a0, s5, 48);
    lbu(a2, a0, kUnitSide);
    a1 = li(1);
    sq(a1, sp, 336);
    if (a2 == a1) {
        charge(13);
        lhu(a2, a0, 164);
        a1 = sll(a2, 3);
        a1 = addu(a1, a2);
        a1 = sll(a1, 1);
        a1 = addu(a1, a2);
        a2 = sll(a1, 2);
        lw(a1, gp, -18668);
        a1 = addu(a1, a2);
        lbu(a1, a1, 0);
        a1 = a1 & 0x1;
        a1 = sltu(zero, a1);
        a1 = a1 ^ 0x1;
        sq(a1, sp, 336);
    }
    charge(2);
    if (v0 == 0) {
        charge(2);
        if (v1 == 0) goto L_00292e88;
    }
    charge(2);
    v0 = li(45);
    sh(v0, sp, 992);
L_00292e88:
    charge(11);
    jal(0x292e88, rg::fn_sub_2BD480_002bd480);
    a0 = v0;
    sd(s0, v0, kPktOwner);
    enqueue(0x292e9c, 1);
    lhu(v1, s2, 204);
    v0 = li(1024);
    if (v1 != v0) {
        charge(4);
        lw(v0, s2, 212);
        a3 = li(1);
        if (v0 == a3) goto L_00292fc8;
        charge(11);
        lq(v0, sp, 352);
        t0 = v0 | 0x1000;
        lw(a0, sp, 1080);
        lw(a1, s4, kActUnit);
        lw(a2, s5, 48);
        jal(0x292ed8, rg::fn_sub_2BAF90_002baf90);
        s1 = v0;
        lw(v0, sp, 1092);
        if (v0 != 0) {
            charge(5);
            v0 = li(4);
            sb(v0, s1, 0);
            lw(v0, sp, 1092);
            ld(v0, v0, kPktId);
            sd(v0, s1, 8);
        } else {
            charge(6);
            lw(v0, gp, -18672);
            v0 = addu(s8, v0);
            lhu(v0, v0, 2);
            v0 = v0 & 0x2000;
            if (v0 != 0) {
                charge(4);
                v0 = li(4);
                sb(v0, s1, 0);
                lq(v0, sp, 384);
                sd(v0, s1, 8);
            } else {
                charge(11);
                v1 = li(4);
                sb(v1, s1, 0);
                lw(v0, sp, 1100);
                ld(v0, v0, kPktId);
                sd(v0, s1, 8);
                sb(v1, s1, 16);
                lw(v0, sp, 1096);
                ld(v0, v0, kPktId);
                sd(v0, s1, 24);
            }
            charge(4);
            lhu(v0, sp, 816);
            sh(v0, s1, kPktTime);
        }
        charge(6);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x80;
        if (v0 != 0) {
            charge(1);
            sd(s0, s1, 96);
        }
        charge(17);
        a0 = s1;
        enqueue(0x292f8c, 2);
        a0 = li(1);
        jal(0x292f98, rg::fn_sub_2DD5E0_002dd5e0);
        a0 = v0;
        depend(0, 5, s1);
        enqueue(0x292fb8, 1);
        goto L_00293118;
    }
L_00292fc8:
    charge(26);
    lq(v0, sp, 352);
    t0 = v0 | 0xC00;
    lw(a0, sp, 1080);
    lw(a1, s4, kActUnit);
    lw(a2, s5, 48);
    a3 = li(1);
    jal(0x292fe0, rg::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = li(4);
    sb(a0, v0, 0);
    lw(v1, sp, 1100);
    ld(v1, v1, kPktId);
    sd(v1, v0, 8);
    sb(a0, v0, 16);
    lw(v1, sp, 1096);
    ld(v1, v1, kPktId);
    sd(v1, v0, 24);
    lhu(v1, sp, 816);
    sh(v1, v0, kPktTime);
    lw(v0, gp, -18672);
    v0 = addu(s8, v0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        charge(1);
        sd(s0, s1, 96);
    }
    charge(8);
    a0 = s1;
    enqueue(0x29303c, 2);
    lhu(v1, s2, 204);
    v0 = li(1024);
    if (v1 == v0) goto L_00293118;
    charge(4);
    lw(v0, s2, 212);
    a3 = li(1);
    if (v0 != a3) goto L_00293118;
    charge(3);
    lw(v0, sp, 560);
    if (v0 != 0) goto L_00293118;
    charge(15);
    lq(v0, sp, 352);
    t0 = v0 | 0x1000;
    lw(a0, sp, 1080);
    lw(a1, s4, kActUnit);
    lw(a2, s5, 48);
    jal(0x293084, rg::fn_sub_2BAF90_002baf90);
    sw(v0, sp, 1084);
    depend(0, 5, s1);
    lw(v0, s2, 212);
    if (v0 != 0) {
        charge(6);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x8;
        if (v0 == 0) goto L_002930d0;
        charge(3);
        v1 = li(8);
        lw(v0, sp, 1084);
        sh(v1, v0, kPktTime);
    }
L_002930d0:
    charge(18);
    lw(v0, sp, 1084);
    sd(s0, v0, kPktOwner);
    a0 = v0;
    enqueue(0x2930e0, 2);
    a0 = li(1);
    jal(0x2930ec, rg::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    depend_at(0, 5, 1084);
    enqueue(0x293110, 1);
L_00293118:
    charge(3);
    lw(v0, sp, 748);
    if (v0 == 0) {
        charge(3);
        lw(v0, sp, 560);
        if (v0 != 0) goto L_00293280;
        charge(2);
        if (s6 != 0) goto L_00293280;
        charge(7);
        a0 = addiu(s4, 56);
        jal(0x293210, rg::fn_btlTargetGetSideMask_002d1600);
        a0 = v0 & 0xFFFF;
        v0 = li(2);
        if (a0 != v0) goto L_00293280;
        charge(22);
        a1 = li(1);
        a2 = addiu(sp, 1304);
        a3 = 0;
        t0 = 0;
        t1 = a1;
        jal(0x29323c, rg::fn_sub_280870_00280870);
        a0 = 0;
        a1 = addiu(sp, 1304);
        a2 = li(1);
        jal(0x293250, rg::fn_sub_288360_00288360);
        a0 = v0;
        depend(0, 5, s1);
        stamp_owner(s4);
        enqueue(0x293278, 1);
    } else {
        charge(17);
        a0 = 0;
        lw(a1, s5, 48);
        a2 = li(3);
        jal(0x293130, rg::fn_sub_2886E0_002886e0);
        a0 = v0;
        depend(0, 5, s1);
        stamp_owner(s4);
        enqueue(0x293158, 1);
        if (s5 == s4) {
            charge(14);
            lw(a0, s5, 48);
            a1 = 0;
            jal(0x2931b4, rg::fn_sub_288950_00288950);
            a0 = v0;
            depend(0, 5, s1);
            stamp_owner(s4);
            enqueue(0x2931dc, 1);
        } else {
            charge(17);
            lw(a0, s5, 48);
            lw(a1, s4, kActUnit);
            a2 = 0;
            jal(0x293174, rg::fn_sub_2886E0_002886e0);
            a0 = v0;
            depend(0, 5, s1);
            stamp_owner(s4);
            enqueue(0x29319c, 1);
        }
        charge(5);
        lhu(v0, s4, kActFlags);
        v0 = v0 | 0x200;
        sh(v0, s4, kActFlags);
    }
L_00293280:
    charge(4);
    v1 = li(1);
    lw(v0, sp, 640);
    if (v0 != v1) goto L_00293448;
    charge(3);
    lw(v0, sp, 1092);
    if (v0 != 0) goto L_002933b8;
    charge(3);
    v0 = li(-1);
    if (s6 == v0) goto L_002933b8;
    charge(3);
    lq(v0, sp, 464);
    if (v0 == v1) {
        charge(3);
        lq(v0, sp, 416);
        if (v0 != 0) goto L_00293310;
        charge(3);
        lq(v0, sp, 448);
        if (v0 != 0) goto L_00293310;
        charge(17);
        lw(a0, sp, 1104);
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = li(4);
        t1 = 0;
        jal(0x2932e4, rg::fn_sub_285D30_00285d30);
        a0 = v0;
        depend(0, 5, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x293308, 0);
    }
L_00293310:
    charge(3);
    lw(v0, sp, 688);
    if (v0 != 0) {
        charge(7);
        v0 = lui(0x3F80);
        mtc1(v0, F12);
        lw(a0, s4, kActUnit);
        a1 = 0;
        a2 = 0;
        jal(0x293348, rg::fn_sub_284F50_00284f50);
    } else {
        charge(6);
        lw(a0, s4, kActUnit);
        lhu(a1, sp, 768);
        jal(0x293324, rg::fn_sub_2843E0_002843e0);
    }
    charge(26);
    depend(0, 5, s1);
    sd(s0, v0, kPktOwner);
    a0 = v0;
    enqueue(0x29336c, 1);
    lw(a0, s4, kActUnit);
    a1 = li(-1);
    a2 = 0;
    a3 = 0;
    t0 = li(3);
    t1 = 0;
    jal(0x29338c, rg::fn_sub_285D30_00285d30);
    a0 = v0;
    depend(0, 5, s1);
    sd(s0, v0, kPktOwner);
    enqueue(0x2933b0, 1);
L_002933b8:
    charge(2);
    if (s5 != s4) {
        charge(14);
        lw(a0, s5, 48);
        lw(a1, s4, kActUnit);
        a2 = li(2);
        jal(0x2933cc, rg::fn_sub_282650_00282650);
        a0 = v0;
        depend(0, 5, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x2933f0, 0);
    }
    charge(20);
    a0 = s5;
    a1 = li(24);
    jal(0x293400, rg::fn_sub_2A3B40_002a3b40);
    sw(v0, sp, 1092);
    depend(0, 5, s1);
    depend(2, 11, s1);
    v1 = li(18);
    sh(v1, v0, 74);
    sd(s0, v0, kPktOwner);
    a0 = v0;
    enqueue(0x293440, 0);
L_00293448:
    charge(3);
    lw(v0, s2, 212);
    if (v0 != 0) {
        charge(5);
        a0 = s2;
        jal(0x293458, rg::fn_sub_2FD160_002fd160);
        if (v0 == 0) {
            charge(2);
            gbtl(v0);
            lw(v0, v0, 3212);
        }
        charge(14);
        a0 = v0;
        lw(a1, s4, kActUnit);
        lw(a2, s2, 48);
        a3 = li(1);
        t0 = 0;
        jal(0x293484, rg::fn_sub_2BAF90_002baf90);
        sw(v0, sp, 1088);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(5);
            v1 = li(5);
            lw(v0, sp, 1088);
            sb(v1, v0, 0);
            lq(v1, sp, 384);
            sd(v1, v0, 8);
        } else {
            charge(7);
            v1 = li(11);
            lw(v0, sp, 1088);
            sb(v1, v0, 0);
            ld(v1, s1, kPktId);
            sd(v1, v0, 8);
        }
        charge(18);
        lw(a0, sp, 1088);
        enqueue(0x2934e0, 1);
        a0 = li(13);
        a1 = li(2);
        a2 = li(6);
        jal(0x2934f4, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend_at(0, 5, 1088);
        enqueue(0x293518, 1);
    }
    charge(4);
    lhu(v1, s2, 204);
    v0 = li(1024);
    if (v1 == v0) {
        charge(15);
        gbtl(v0);
        lw(a0, v0, 3216);
        lw(a1, s4, kActUnit);
        lw(a2, s5, 48);
        a3 = li(1);
        t0 = 0;
        jal(0x293548, rg::fn_sub_2BAF90_002baf90);
        sw(v0, sp, 1088);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(5);
            v1 = li(5);
            lw(v0, sp, 1088);
            sb(v1, v0, 0);
            lq(v1, sp, 384);
            sd(v1, v0, 8);
        } else {
            charge(7);
            v1 = li(11);
            lw(v0, sp, 1088);
            sb(v1, v0, 0);
            ld(v1, s1, kPktId);
            sd(v1, v0, 8);
        }
        charge(20);
        lw(a0, sp, 1088);
        enqueue(0x2935a4, 1);
        a0 = li(12);
        a1 = li(2);
        a2 = li(7);
        jal(0x2935b8, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend_at(0, 5, 1088);
        enqueue(0x2935dc, 1);
        v0 = li(10);
        sh(v0, sp, 976);
    }
    charge(12);
    sh(zero, sp, 864);
    lhu(v0, sp, 848);
    v0 = v0;
    sq(v0, sp, 320);
    v0 = addiu(v0, -1);
    sq(v0, sp, 304);
    lh(v0, sp, 976);
    v0 = v0;
    v0 = addiu(v0, 43);
    sq(v0, sp, 288);
    goto L_00293f40;
    // ---- every hit on this target (the loop closes at L_00293f40)
L_0029361c:
    charge(28);
    lhu(v0, sp, 864);
    v1 = v0;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    sq(v0, sp, 272);
    v0 = addiu(v0, 248);
    sq(v0, sp, 256);
    lq(v0, sp, 272);
    lb(a1, v0, 248);
    v0 = lui(0x3F80);
    mtc1(v0, F12);
    lw(a0, s5, 48);
    a2 = 0;
    a3 = 0;
    jal(0x29365c, rg::fn_sub_284200_00284200);
    s3 = v0;
    depend(0, 11, s1);
    lhu(v1, sp, 832);
    sh(v1, v0, kPktTime);
    lw(v0, s2, 212);
    if (v0 != 0) {
        charge(6);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x8;
        if (v0 == 0) goto L_002936b0;
        charge(3);
        lh(v0, s3, 72);
        v0 = addiu(v0, 8);
        sh(v0, s3, kPktTime);
    }
L_002936b0:
    charge(9);
    sd(s0, s3, 96);
    a0 = s3;
    enqueue(0x2936bc, 1);
    lq(v1, sp, 176);
    lq(v0, sp, 304);
    if (v1 != v0) goto L_002938b4;
    charge(6);
    lq(v0, sp, 272);
    lw(v1, v0, 232);
    v0 = lui(0x10);
    v0 = v1 & v0;
    if (v0 == 0) goto L_002938b4;
    charge(3);
    lq(v0, sp, 336);
    if (v0 != 0) {
        charge(3);
        lw(v0, sp, 748);
        if (v0 == 0) {
            charge(19);
            lw(a1, s5, 48);
            gbtl(v0);
            lw(a0, v0, 3324);
            a2 = a1;
            a3 = li(1);
            t0 = 0;
            jal(0x2937f8, rg::fn_sub_2BAF90_002baf90);
            a0 = v0;
            depend(0, 5, s3);
            v1 = li(1);
            sh(v1, v0, kPktTime);
            sd(s0, v0, kPktOwner);
            enqueue(0x293824, 2);
        } else {
            charge(3);
            ld(v0, sp, 1040);
            if (v0 != 0) {
                charge(12);
                lw(a0, s5, 48);
                jal(0x293714, rg::fn_sub_2B9590_002b9590);
                v0 = lui(0x42C8);
                mtc1(v0, F1);
                mul_s(F20, F1, F0);
                a0 = s7;
                jal(0x293730, rg::fn_datCalcIsHpSkill_002d6370);
                if (v0 == 0) {
                    charge(1);
                    v0 = li(2);
                } else {
                    charge(3);
                    v0 = li(3);
                }
                charge(15);
                a2 = v0 & 0xFFFF;
                lw(a0, s4, kActUnit);
                lw(a1, s5, 48);
                mov_s(F12, F20);
                jal(0x293760, rg::fn_sub_2B7BD0_002b7bd0);
                a0 = v0;
                depend_id_at(0, 5, 1040);
                sd(s0, v0, kPktOwner);
                enqueue(0x293784, 0);
            }
            charge(21);
            lw(a1, s5, 48);
            gbtl(v0);
            lw(a0, v0, 3328);
            a2 = a1;
            a3 = li(1);
            t0 = 0;
            jal(0x2937a4, rg::fn_sub_2BAF90_002baf90);
            a0 = v0;
            depend(0, 5, s3);
            v1 = li(1);
            sh(v1, v0, kPktTime);
            sd(s0, v0, kPktOwner);
            enqueue(0x2937d0, 2);
        }
        charge(3);
        lw(v0, s2, 208);
        if (v0 != 0) goto L_00293884;
        charge(19);
        lw(a1, s5, 48);
        gbtl(v0);
        lw(a0, v0, 3320);
        a2 = a1;
        a3 = li(1);
        t0 = 0;
        jal(0x293850, rg::fn_sub_2BAF90_002baf90);
        a0 = v0;
        depend(0, 5, s3);
        v1 = li(16);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x29387c, 2);
    }
L_00293884:
    charge(12);
    lw(a0, s5, 48);
    jal(0x293888, rg::fn_sub_284C90_00284c90);
    a0 = v0;
    depend(0, 5, s3);
    sd(s0, v0, kPktOwner);
    enqueue(0x2938ac, 1);
L_002938b4:
    charge(3);
    lw(v0, sp, 640);
    if (v0 != 0) goto L_00293980;
    charge(5);
    lq(v0, sp, 256);
    lb(v1, v0, 0);
    v0 = li(-1);
    if (v1 == v0) {
        charge(6);
        lw(v0, s2, 48);
        lbu(v1, v0, kUnitSide);
        lw(v0, s4, kActUnit);
        lbu(v0, v0, kUnitSide);
        if (v1 == v0) goto L_00293980;
    }
    charge(7);
    lw(v0, s2, 48);
    lw(a0, v0, kUnitDat);
    a1 = lui(0x18);
    jal(0x2938f8, rg::fn_datCalcChkBadStatus_00300580);
    if (v0 != 0) goto L_00293980;
    charge(8);
    lw(a0, s2, 48);
    lw(a1, s4, kActUnit);
    a2 = li(2);
    jal(0x293914, rg::fn_sub_282650_00282650);
    lw(v1, s2, 212);
    if (v1 != 0) {
        charge(3);
        lw(v1, sp, 1088);
        if (v1 == 0) goto L_00293950;
        charge(7);
        depend_at(0, 5, 1088);
        goto L_00293960;
    }
L_00293950:
    charge(4);
    depend(0, 5, s3);
L_00293960:
    charge(8);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    a0 = v0;
    enqueue(0x293978, 1);
L_00293980:
    charge(40);
    lq(v0, sp, 272);
    v0 = addiu(v0, 224);
    sw(v0, sp, 544);
    a0 = s4;
    a1 = s5;
    a2 = v0;
    lhu(a3, s2, 204);
    lhu(t0, s2, 206);
    jal(0x2939a0, rg::fn_sub_2D7E20_002d7e20);
    a0 = v0;
    depend(0, 5, s3);
    lh(v1, sp, 976);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x2939cc, 1);
    a0 = s2;
    jal(0x2939d8, rg::fn_sub_2D8090_002d8090);
    a0 = v0;
    depend(0, 5, s3);
    lh(v1, sp, 976);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x293a04, 1);
    lhu(v0, s4, 106);
    v1 = addiu(v0, -1);
    lw(v0, sp, 560);
    if (v0 == v1) {
        charge(5);
        lbu(v0, s2, 200);
        v1 = addiu(v0, -1);
        lq(v0, sp, 176);
        if (v0 != v1) goto L_00293a6c;
        charge(14);
        a0 = s4;
        jal(0x293a38, rg::fn_sub_2D8090_002d8090);
        a0 = v0;
        depend(0, 5, s3);
        lh(v1, sp, 976);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x293a64, 1);
    }
L_00293a6c:
    charge(3);
    lw(v0, sp, 560);
    if (v0 == 0) {
        charge(3);
        lq(v0, sp, 176);
        if (v0 != 0) goto L_00293ad0;
        charge(4);
        lhu(v0, s4, kActFlags);
        v0 = v0 & 0x4;
        if (v0 != 0) goto L_00293ad0;
        charge(15);
        a0 = s4;
        lbu(a1, s4, 202);
        jal(0x293a9c, rg::fn_sub_2D7FB0_002d7fb0);
        a0 = v0;
        depend(0, 5, s3);
        lh(v1, sp, 976);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x293ac8, 1);
    }
L_00293ad0:
    charge(5);
    lbu(v0, s2, 200);
    v1 = addiu(v0, -1);
    lq(v0, sp, 176);
    if (v0 == v1) {
        charge(3);
        lh(a1, s4, 220);
        if (a1 == 0) {
            charge(3);
            lh(a1, s2, 220);
            if (a1 == 0) goto L_00293b7c;
            charge(15);
            lw(a0, s2, 48);
            jal(0x293b44, rg::fn_sub_2BD850_002bd850);
            a0 = v0;
            depend(0, 5, s3);
            clear_bit5_71();
            sd(s0, v0, kPktOwner);
            enqueue(0x293b74, 3);
        } else {
            charge(17);
            lw(a0, s4, kActUnit);
            jal(0x293af4, rg::fn_sub_2BD850_002bd850);
            a0 = v0;
            depend(0, 5, s3);
            clear_bit5_71();
            sd(s0, v0, kPktOwner);
            enqueue(0x293b24, 3);
        }
    }
L_00293b7c:
    charge(3);
    lq(v0, sp, 176);
    if (v0 == 0) {
        charge(4);
        lw(v0, sp, 544);
        lw(v0, v0, 0);
        if (v0 == 0) goto L_00293be4;
        charge(19);
        lw(a0, s5, 48);
        a1 = 0;
        a2 = 0;
        jal(0x293ba4, rg::fn_sub_2BD230_002bd230);
        a0 = v0;
        depend(0, 5, s3);
        lh(v1, sp, 976);
        sh(v1, v0, kPktTime);
        clear_bit5_71();
        sd(s0, v0, kPktOwner);
        enqueue(0x293bdc, 3);
    }
L_00293be4:
    charge(8);
    lq(v0, sp, 272);
    v0 = addiu(v0, 250);
    sq(v0, sp, 240);
    lq(v0, sp, 272);
    lhu(v0, v0, 250);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(26);
        a0 = addiu(sp, 1264);
        jal(0x293c08, rg::fn_sub_2D5DC0_002d5dc0);
        v0 = lui(0x10);
        sw(v0, sp, 1276);
        a0 = s2;
        a1 = s2;
        a2 = addiu(sp, 1264);
        a3 = li(1);
        t0 = a3;
        jal(0x293c2c, rg::fn_sub_2D7E20_002d7e20);
        a0 = v0;
        depend(0, 4, s3);
        sd(s0, v0, kPktOwner);
        enqueue(0x293c50, 1);
        lq(v0, sp, 240);
        lhu(v0, v0, 0);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            charge(17);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            lw(a0, s2, 48);
            a1 = li(10);
            a2 = 0;
            a3 = 0;
            jal(0x293c84, rg::fn_sub_284200_00284200);
            a0 = v0;
            depend(0, 4, s3);
            sd(s0, v0, kPktOwner);
            enqueue(0x293ca8, 1);
        }
        charge(12);
        lw(a0, s2, 48);
        jal(0x293cb4, rg::fn_sub_284C90_00284c90);
        a0 = v0;
        depend(0, 4, s3);
        sd(s0, v0, kPktOwner);
        enqueue(0x293cd8, 1);
    }
    charge(5);
    lq(v0, sp, 240);
    lhu(v0, v0, 0);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        charge(5);
        v0 = li(1);
        sw(v0, sp, 704);
        v1 = li(3);
        gbtl(v0);
        sh(v1, v0, 28);
    }
    charge(5);
    lq(v0, sp, 240);
    lhu(v0, v0, 0);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        charge(2);
        v0 = li(1);
        sw(v0, sp, 656);
    }
    charge(38);
    lhu(v0, sp, 864);
    v1 = v0;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    sq(v0, sp, 224);
    lw(a0, s4, kActUnit);
    lw(a1, s5, 48);
    lw(a2, sp, 608);
    lhu(a3, s2, 204);
    lhu(t0, s2, 206);
    lhu(t1, sp, 864);
    lhu(t2, sp, 848);
    lw(t3, sp, 544);
    jal(0x293d60, rg::fn_sub_2BDBD0_002bdbd0);
    a0 = v0;
    depend(0, 5, s3);
    lh(v1, sp, 976);
    sh(v1, v0, kPktTime);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    enqueue(0x293d98, 3);
    lq(v0, sp, 224);
    v0 = addiu(v0, 244);
    sq(v0, sp, 208);
    lq(v0, sp, 224);
    lh(v0, v0, 244);
    if (!gtz(v0)) {
        charge(4);
        lq(v0, sp, 272);
        lh(v0, v0, 246);
        if (lez(v0)) goto L_00293f28;
    }
    charge(60);
    lq(v0, sp, 288);
    v0 = sx16(v0);
    sq(v0, sp, 192);
    a0 = addiu(sp, 1264);
    jal(0x293de0, rg::fn_sub_2D5DC0_002d5dc0);
    lhu(v0, sp, 864);
    v1 = v0;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v1 = addu(s2, v0);
    lq(v0, sp, 208);
    lh(v0, v0, 0);
    sw(v0, sp, 1264);
    lh(v0, v1, 246);
    sw(v0, sp, 1268);
    a0 = s4;
    a1 = s4;
    a2 = addiu(sp, 1264);
    a3 = li(1);
    t0 = a3;
    jal(0x293e28, rg::fn_sub_2D7E20_002d7e20);
    a0 = v0;
    depend(0, 4, s3);
    lq(v1, sp, 192);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x293e54, 1);
    lw(a0, s4, kActUnit);
    a1 = a0;
    a2 = li(-1);
    a3 = li(1);
    t0 = a3;
    lhu(t1, sp, 864);
    lhu(t2, sp, 848);
    t3 = addiu(sp, 1264);
    jal(0x293e7c, rg::fn_sub_2BDBD0_002bdbd0);
    a0 = v0;
    depend(0, 4, s3);
    lq(v1, sp, 192);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x293ea8, 3);
    lw(v0, sp, 1264);
    if (v0 != 0) {
        charge(3);
        lq(v0, sp, 176);
        if (v0 == 0) {
            charge(8);
            lw(a0, s4, kActUnit);
            jal(0x293ecc, rg::fn_sub_2BD480_002bd480);
            a0 = v0;
            sd(s0, v0, kPktOwner);
            enqueue(0x293ee0, 1);
        }
        charge(16);
        lw(a0, s4, kActUnit);
        a1 = 0;
        a2 = 0;
        jal(0x293ef4, rg::fn_sub_2BD230_002bd230);
        a0 = v0;
        depend(0, 4, s3);
        lq(v1, sp, 192);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x293f20, 3);
    }
L_00293f28:
    charge(6);
    lhu(v0, sp, 832);
    v0 = addiu(v0, 7);
    sh(v0, sp, 832);
    lhu(v0, sp, 864);
    v0 = addiu(v0, 1);
    sh(v0, sp, 864);
L_00293f40:
    charge(8);
    lhu(v0, sp, 864);
    v0 = v0;
    sq(v0, sp, 176);
    paddub(v1, v0, zero);
    lq(v0, sp, 320);
    v0 = slt(v1, v0);
    if (v0 != 0) { backedge(); goto L_0029361c; }
    charge(7);
    lh(v0, sp, 960);
    v1 = v0;
    lhu(v0, sp, 832);
    v0 = v0;
    at = slt(v1, v0);
    if (at != 0) {
        charge(2);
        lhu(v0, sp, 832);
        sh(v0, sp, 960);
    }
    charge(7);
    lhu(v1, sp, 816);
    lq(v0, sp, 368);
    v0 = addu(v1, v0);
    sh(v0, sp, 816);
    lhu(v0, sp, 880);
    v0 = addiu(v0, 1);
    sh(v0, sp, 880);
    // ---- the target done: the enemy-side reactions (sound 22 / camera 13 by the rule of ATTACK, 23 for a critical, the cameras 17 / 15 / 14)
L_00293fa0:
    charge(7);
    lhu(v0, sp, 880);
    v0 = v0;
    sw(v0, sp, 560);
    lhu(v1, s4, 106);
    v0 = slt(v0, v1);
    if (v0 != 0) { backedge(); goto L_00292d60; }
    charge(5);
    ld(s2, s3, kPktId);
    lh(v1, s4, 222);
    v0 = li(-1);
    if (v1 != v0) {
        charge(19);
        a1 = v1 & 0xFFFF;
        a0 = s4;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(0x293fe4, rg::fn_sub_2DB740_002db740);
        a0 = v0;
        depend_id(0, 5, s2);
        lh(v1, sp, 960);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x29400c, 1);
        goto L_002943e0;
    }
    charge(3);
    lw(v0, sp, 912);
    if (lez(v0)) goto L_002941d8;
    charge(2);
    if (s6 != 0) goto L_002943e0;
    charge(8);
    a0 = li(2);
    a1 = lui(0x8);
    jal(0x294038, rg::fn_btlCountActiveUnits_002d4e10);
    s3 = v0 & 0xFFFF;
    lbu(v0, s4, 40);
    if (gtz(v0)) goto L_00294144;
    charge(5);
    lw(v0, s4, kActUnit);
    lhu(v1, v0, 164);
    v0 = li(1);
    if (v1 == v0) goto L_00294144;
    charge(6);
    a0 = li(100);
    jal(0x294068, rg::fn_datCalcRand_002ffbc0);
    at = sltiu(v0, 50);
    if (at == 0) goto L_00294144;
    charge(4);
    lw(v0, s4, kActUnit);
    lbu(v0, v0, kUnitSide);
    if (v0 != 0) {
        charge(3);
        v0 = 0;
        goto L_0029413c;
    }
    charge(5);
    gbtl(a0);
    lh(v1, a0, 2616);
    v0 = li(-1);
    if (v1 != v0) {
        charge(6);
        lw(v0, sp, 912);
        v0 = subu(s3, v0);
        v1 = sx16(v0);
        if (!gtz(v1)) {
            charge(11);
            a0 = li(2);
            a1 = lui(0x8);
            jal(0x2940cc, rg::fn_btlCountActiveUnits_002d4e10);
            a0 = v0 & 0xFFFF;
            gbtl(v1);
            lh(v0, v1, 2618);
            v0 = sra(v0, 1);
            v0 = sltu(v0, a0);
            if (v0 != 0) goto L_00294138;
            charge(7);
            lh(s3, v1, 2616);
            jal(0x2940f4, rg::fn_sub_2B7060_002b7060);
            v0 = sx16(v0);
            if (s3 == v0) goto L_00294138;
            charge(3);
            v0 = li(1);
            goto L_0029413c;
        }
        charge(5);
        lh(v0, a0, 2618);
        v0 = sra(v0, 1);
        v0 = slt(v0, v1);
        if (v0 != 0) goto L_00294138;
        charge(3);
        v0 = li(1);
        goto L_0029413c;
    }
L_00294138:
    charge(1);
    v0 = 0;
L_0029413c:
    charge(2);
    if (v0 == 0) goto L_00294190;
L_00294144:
    charge(19);
    a0 = s4;
    a1 = li(22);
    lw(a2, sp, 912);
    a3 = 0;
    t0 = 0;
    jal(0x294158, rg::fn_sub_2DB740_002db740);
    a0 = v0;
    depend_id(0, 5, s2);
    lh(v1, sp, 960);
    sh(v1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    enqueue(0x294180, 1);
    goto L_002943e0;
L_00294190:
    charge(18);
    a0 = s4;
    a1 = li(13);
    lw(a2, sp, 912);
    a3 = 0;
    t0 = 0;
    jal(0x2941a4, rg::fn_sub_2E2BE0_002e2be0);
    a0 = v0;
    depend_id(0, 5, s2);
    lh(v1, sp, 960);
    sh(v1, v0, kPktTime);
    enqueue(0x2941c8, 1);
    goto L_002943e0;
L_002941d8:
    charge(3);
    lw(v0, sp, 896);
    if (!lez(v0)) {
        charge(4);
        lbu(v1, s4, 202);
        v0 = v1 & 0x1;
        if (v0 == 0) goto L_00294250;
        charge(3);
        v0 = v1 & 0x2;
        if (v0 != 0) goto L_00294250;
        charge(20);
        lhu(v0, sp, 800);
        a2 = v0;
        a0 = s4;
        a1 = li(23);
        a3 = 0;
        t0 = 0;
        jal(0x294218, rg::fn_sub_2DB740_002db740);
        a0 = v0;
        depend_id(0, 5, s2);
        lh(v1, sp, 960);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x294240, 1);
        goto L_002943e0;
    }
L_00294250:
    charge(3);
    lw(v0, sp, 748);
    if (v0 != 0) {
        charge(5);
        lw(v0, s4, kActUnit);
        lhu(v1, v0, 164);
        v0 = li(1);
        if (v1 != v0) goto L_002942e8;
        charge(2);
        if (s6 != 0) goto L_002942e8;
        charge(5);
        a0 = s4;
        jal(0x29427c, rg::fn_sub_2D5FB0_002d5fb0);
        if (v0 == 0) goto L_002942e8;
        charge(5);
        a0 = s4;
        jal(0x294290, rg::fn_sub_2D6090_002d6090);
        if (v0 != 0) goto L_002942e8;
        charge(18);
        lw(a0, s4, kActTarget);
        a1 = li(17);
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(0x2942b4, rg::fn_sub_2E2BE0_002e2be0);
        a0 = v0;
        depend_id(0, 5, s2);
        lh(v1, sp, 960);
        sh(v1, v0, kPktTime);
        enqueue(0x2942d8, 1);
        goto L_002943e0;
    }
L_002942e8:
    charge(3);
    lw(v0, sp, 912);
    if (v0 == 0) {
        charge(5);
        a0 = s4;
        jal(0x2942f8, rg::fn_sub_2D6130_002d6130);
        if (v0 == 0) {
            charge(6);
            a0 = s4;
            jal(0x294354, rg::fn_sub_2D6210_002d6210);
            v1 = li(1);
            if (v0 != v1) goto L_002943e0;
            charge(5);
            a0 = s4;
            jal(0x29436c, rg::fn_sub_2D5F50_002d5f50);
            if (v0 != 0) goto L_002943e0;
            charge(3);
            lw(v0, sp, 656);
            if (v0 != 0) goto L_002943e0;
            charge(22);
            lw(v0, s4, kActUnit);
            lw(a0, v0, kUnitDat);
            lhu(a1, sp, 592);
            jal(0x294394, rg::fn_datCalcGetSkillElement_003082f0);
            a2 = sx16(v0);
            a0 = s4;
            a1 = li(15);
            a3 = 0;
            t0 = 0;
            jal(0x2943b4, rg::fn_sub_2E2BE0_002e2be0);
            a0 = v0;
            depend_id(0, 5, s2);
            lh(v1, sp, 960);
            sh(v1, v0, kPktTime);
            enqueue(0x2943d8, 1);
        } else {
            charge(18);
            a0 = s4;
            a1 = li(14);
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(0x29431c, rg::fn_sub_2E2BE0_002e2be0);
            a0 = v0;
            depend_id(0, 5, s2);
            lh(v1, sp, 960);
            sh(v1, v0, kPktTime);
            enqueue(0x294340, 1);
        }
    }
    // ---- the numbers, gauges and status packets of the target (sub_2D7E20 with the 40-byte result records, sub_2BDBD0, sub_2BD230)
L_002943e0:
    charge(3);
    lw(v0, sp, 656);
    if (v0 == 0) goto L_002947ec;
    charge(4);
    v1 = li(1);
    lw(v0, sp, 640);
    if (v0 == v1) {
        charge(16);
        a0 = s4;
        a1 = li(23);
        jal(0x294404, rg::fn_sub_2A3B40_002a3b40);
        sw(v0, sp, 1092);
        depend(0, 11, s1);
        v1 = li(24);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a0 = v0;
        enqueue(0x294434, 0);
    }
    charge(4);
    lw(v0, s4, kActUnit);
    lbu(v0, v0, kUnitSide);
    if (v0 == 0) {
        charge(23);
        a0 = addiu(sp, 1264);
        jal(0x294450, rg::fn_sub_2D5DC0_002d5dc0);
        lw(v0, s4, kActUnit);
        lw(a0, v0, kUnitDat);
        jal(0x294460, rg::fn_datCalcGetHp_002ffd70);
        v0 = v0 & 0xFFFF;
        v0 = addiu(v0, -1);
        v0 = subu(zero, v0);
        sw(v0, sp, 1264);
        a0 = s4;
        a1 = s4;
        a2 = addiu(sp, 1264);
        a3 = li(1);
        t0 = a3;
        jal(0x29448c, rg::fn_sub_2D7E20_002d7e20);
        s2 = v0;
        v1 = li(1);
        lw(v0, sp, 640);
        if (v0 != v1) {
            charge(4);
            v0 = li(11);
            sb(v0, s2, 0);
            ld(v0, s1, kPktId);
            sd(v0, s2, 8);
        } else {
            charge(7);
            v0 = li(4);
            sb(v0, s2, 0);
            lw(v0, sp, 1092);
            ld(v0, v0, kPktId);
            sd(v0, s2, 8);
        }
        charge(46);
        sd(s0, s2, 96);
        a0 = s2;
        enqueue(0x2944e0, 1);
        lw(a0, s4, kActUnit);
        a1 = a0;
        a2 = li(-1);
        a3 = 0;
        t0 = 0;
        t1 = 0;
        t2 = li(1);
        t3 = addiu(sp, 1264);
        jal(0x294508, rg::fn_sub_2BDBD0_002bdbd0);
        a0 = v0;
        depend(0, 4, s2);
        clear_bit5_71();
        sd(s0, v0, kPktOwner);
        enqueue(0x294538, 3);
        lw(a0, s4, kActUnit);
        a1 = 0;
        a2 = 0;
        jal(0x29454c, rg::fn_sub_2BD230_002bd230);
        a0 = v0;
        depend(0, 4, s2);
        clear_bit5_71();
        sd(s0, v0, kPktOwner);
        enqueue(0x29457c, 3);
        goto L_00294610;
    }
    charge(17);
    a0 = addiu(sp, 1264);
    jal(0x294590, rg::fn_sub_2D5DC0_002d5dc0);
    v0 = lui(0x8);
    sw(v0, sp, 1272);
    a0 = s4;
    a1 = s4;
    a2 = addiu(sp, 1264);
    a3 = li(1);
    t0 = a3;
    jal(0x2945b4, rg::fn_sub_2D7E20_002d7e20);
    s2 = v0;
    v1 = li(1);
    lw(v0, sp, 640);
    if (v0 != v1) {
        charge(4);
        v0 = li(11);
        sb(v0, s2, 0);
        ld(v0, s1, kPktId);
        sd(v0, s2, 8);
    } else {
        charge(7);
        v0 = li(4);
        sb(v0, s2, 0);
        lw(v0, sp, 1092);
        ld(v0, v0, kPktId);
        sd(v0, s2, 8);
    }
    charge(5);
    sd(s0, s2, 96);
    a0 = s2;
    enqueue(0x294608, 1);
    // ---- the knock-down (sub_284C90 / sub_284F50 / sub_2843E0) and its camera and effect
L_00294610:
    charge(3);
    lw(v0, sp, 684);
    if (v0 != 0) {
        charge(13);
        lw(a0, s4, kActUnit);
        jal(0x294694, rg::fn_sub_284C90_00284c90);
        s3 = v0;
        depend(0, 4, s2);
        sd(s0, v0, kPktOwner);
        a0 = s3;
        enqueue(0x2946bc, 1);
    } else {
        charge(3);
        lw(v0, sp, 688);
        if (v0 != 0) {
            charge(8);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            lw(a0, s4, kActUnit);
            a1 = 0;
            a2 = 0;
            jal(0x294658, rg::fn_sub_284F50_00284f50);
            s3 = v0;
        } else {
            charge(7);
            lw(a0, s4, kActUnit);
            lhu(a1, sp, 768);
            jal(0x294630, rg::fn_sub_2843E0_002843e0);
            s3 = v0;
        }
        charge(11);
        v0 = li(4);
        sb(v0, s3, 0);
        ld(v0, s2, kPktId);
        sd(v0, s3, 8);
        sd(s0, s3, 96);
        a0 = s3;
        enqueue(0x294680, 1);
    }
    charge(5);
    lw(a0, s4, kActUnit);
    lw(v0, a0, 156);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        charge(15);
        jal(0x2946d8, rg::fn_sub_27F2F0_0027f2f0);
        a0 = v0;
        depend(0, 4, s2);
        v1 = li(60);
        sh(v1, v0, 74);
        sd(s0, v0, kPktOwner);
        enqueue(0x294704, 1);
        goto L_002948d0;
    }
    charge(54);
    v0 = lui(0xFF);
    a1 = v0 | 0xFFFF;
    a2 = li(6);
    a3 = 0;
    t0 = li(4);
    t1 = 0;
    jal(0x29472c, rg::fn_sub_285D30_00285d30);
    a0 = v0;
    depend(0, 4, s2);
    sd(s0, v0, kPktOwner);
    enqueue(0x294750, 1);
    lw(a1, s4, kActUnit);
    gbtl(v0);
    lw(a0, v0, 3248);
    a2 = a1;
    a3 = 0;
    t0 = 0;
    jal(0x294770, rg::fn_sub_2BAF90_002baf90);
    a0 = v0;
    depend(0, 4, s2);
    sd(s0, v0, kPktOwner);
    enqueue(0x294794, 2);
    a0 = li(10);
    a1 = li(2);
    a2 = li(8);
    jal(0x2947a8, rg::fn_sub_2DD100_002dd100);
    a0 = v0;
    depend(0, 4, s2);
    sd(s0, v0, kPktOwner);
    enqueue(0x2947cc, 1);
    lw(v1, s4, kActUnit);
    lw(v0, v1, 156);
    v0 = v0 | 0x100;
    sw(v0, v1, 156);
    goto L_002948d0;
L_002947ec:
    charge(3);
    lw(v0, sp, 684);
    if (v0 != 0) {
        charge(15);
        lw(a0, s4, kActUnit);
        jal(0x294898, rg::fn_sub_284C90_00284c90);
        s3 = v0;
        depend(0, 11, s1);
        lh(v1, sp, 992);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        a0 = s3;
        enqueue(0x2948c8, 1);
    } else {
        charge(3);
        lw(v0, sp, 688);
        if (v0 != 0) {
            charge(8);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            lw(a0, s4, kActUnit);
            a1 = 0;
            a2 = 0;
            jal(0x294834, rg::fn_sub_284F50_00284f50);
            s3 = v0;
        } else {
            charge(7);
            lw(a0, s4, kActUnit);
            lhu(a1, sp, 768);
            jal(0x29480c, rg::fn_sub_2843E0_002843e0);
            s3 = v0;
        }
        charge(6);
        v0 = li(11);
        sb(v0, s3, 0);
        ld(v0, s1, kPktId);
        sd(v0, s3, 8);
        if (s6 != 0) {
            charge(4);
            v0 = li(8);
            sh(v0, s3, kPktTime);
            lh(v0, sp, 992);
            sh(v0, s3, 74);
        } else {
            charge(4);
            lh(v0, sp, 992);
            sh(v0, s3, kPktTime);
        }
        charge(7);
        sd(s0, s3, 96);
        a0 = s3;
        enqueue(0x294884, 1);
    }
    // ---- all targets done: the effect ends (sub_29FA50, sub_2A1080, sub_2A16C0, sub_2A1DB0), the closing messages, the actor's return (sub_285D30)
L_002948d0:
    charge(18);
    a0 = li(16);
    jal(0x2948d4, rg::fn_sub_29FA50_0029fa50);
    a0 = v0;
    depend(0, 4, s3);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    enqueue(0x294904, 1);
    lw(v0, sp, 704);
    if (v0 == 0) {
        charge(1);
        v0 = 0;
    } else {
        charge(3);
        v0 = li(2);
    }
    charge(50);
    a1 = v0 & 0xFFFF;
    a0 = li(16);
    jal(0x294930, rg::fn_sub_2A1080_002a1080);
    a0 = v0;
    depend(0, 4, s3);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    enqueue(0x294960, 1);
    a0 = li(16);
    jal(0x29496c, rg::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    depend(0, 4, s3);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    enqueue(0x29499c, 1);
    a0 = li(8);
    jal(0x2949a8, rg::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    depend(0, 4, s1);
    clear_bit5_71();
    sd(s0, v0, kPktOwner);
    enqueue(0x2949d8, 0);
    v1 = li(1);
    lq(v0, sp, 464);
    if (v0 != v1) goto L_00294c08;
    charge(3);
    v0 = li(-1);
    if (s6 == v0) goto L_00294c08;
    charge(3);
    lq(v0, sp, 448);
    if (v0 != 0) goto L_00294c08;
    charge(3);
    lw(v0, sp, 720);
    if (v0 != 0) {
        charge(13);
        a0 = s4;
        a1 = li(25);
        jal(0x294a88, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_id_at(0, 5, 1040);
        sd(s0, v0, kPktOwner);
        enqueue(0x294aac, 0);
    } else {
        charge(6);
        lw(v0, gp, -18672);
        v0 = addu(s8, v0);
        lhu(v0, v0, 2);
        v0 = v0 & 0x40;
        if (v0 != 0) goto L_00294ab4;
        charge(2);
        if (s6 != 0) {
            charge(1);
            v0 = li(22);
        } else {
            charge(3);
            v0 = li(21);
        }
        charge(15);
        a1 = v0 & 0xFFFF;
        a0 = s4;
        jal(0x294a4c, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        depend_id_at(0, 5, 1040);
        sd(s0, v0, kPktOwner);
        enqueue(0x294a70, 0);
    }
L_00294ab4:
    charge(3);
    lw(v0, sp, 704);
    if (v0 == 0) {
        charge(17);
        lw(a0, s4, kActUnit);
        a1 = li(-1);
        a2 = 0;
        a3 = li(12);
        t0 = li(3);
        t1 = 0;
        jal(0x294ad8, rg::fn_sub_285D30_00285d30);
        a0 = v0;
        depend(0, 11, s1);
        sd(s0, v0, kPktOwner);
        enqueue(0x294afc, 1);
    }
    charge(3);
    lq(v0, sp, 416);
    if (v0 != 0) goto L_00294c08;
    charge(17);
    lw(a0, sp, 1104);
    v0 = lui(0xFF);
    a1 = v0 | 0xFFFF;
    a2 = li(8);
    a3 = 0;
    t0 = li(4);
    t1 = 0;
    jal(0x294b2c, rg::fn_sub_285D30_00285d30);
    s2 = v0;
    depend(0, 11, s1);
    lw(v0, sp, 748);
    if (v0 != 0) {
        charge(3);
        lq(v0, sp, 432);
        if (v0 != 0) {
            charge(3);
            v0 = li(7);
            goto L_00294b78;
        } else {
            charge(2);
        }
    }
    charge(1);
    v0 = li(15);
    // ---- the last camera and sub_2857F0, the end packet sub_27DC00, the camera set released (sub_2B9030), and the next state (BAD DAMAGE 25 when sub_2DC130 asks, else 30)
L_00294b78:
    charge(36);
    sh(v0, s2, kPktTime);
    sd(s0, s2, 96);
    a0 = s2;
    enqueue(0x294b88, 1);
    gbtl(v0);
    lw(a0, v0, 3308);
    lw(a1, sp, 1104);
    lw(a2, sp, 944);
    a3 = 0;
    t0 = li(8448);
    jal(0x294ba8, rg::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    depend_id_at(0, 4, 1056);
    sd(s0, v0, kPktOwner);
    enqueue(0x294bcc, 2);
    lw(a0, sp, 1104);
    jal(0x294bd8, rg::fn_sub_2857F0_002857f0);
    a0 = v0;
    depend(0, 4, s2);
    a1 = li(1);
    sh(a1, v0, kPktTime);
    sd(s0, v0, kPktOwner);
    jal(0x294c00, rg::fn_sub_27ED20_0027ed20);
L_00294c08:
    charge(4);
    v1 = li(1);
    lw(v0, sp, 704);
    if (v0 == v1) {
        charge(14);
        a0 = li(128);
        jal(0x294c1c, rg::fn_sub_27DC00_0027dc00);
        a0 = v0;
        depend(0, 4, s1);
        v1 = li(12);
        sh(v1, v0, kPktTime);
        sd(s0, v0, kPktOwner);
        enqueue(0x294c48, 1);
    }
    charge(8);
    lw(a0, sp, 1080);
    jal(0x294c54, rg::fn_sub_2B9030_002b9030);
    a0 = s4;
    jal(0x294c60, rg::fn_sub_2DC130_002dc130);
    if (v0 != 0) {
        charge(6);
        a0 = s4;
        a1 = li(25);
        jal(0x294c78, rg::fn_btlActionSetState_00299d60);
        goto L_00294cd4;
    }
    charge(4);
    lhu(v1, s4, kActMoveKind);
    v0 = li(2);
    if (v1 != v0) {
        charge(3);
        v0 = li(3);
        if (v1 == v0) goto L_00294cb8;
        charge(3);
        v0 = li(1);
        if (v1 == v0) goto L_00294cb8;
        charge(2);
        goto L_00294cc4;
    }
L_00294cb8:
    charge(3);
    a1 = daddiu(zero, 30);
    goto L_00294cc8;
L_00294cc4:
    charge(1);
    a1 = daddiu(zero, 30);
L_00294cc8:
    charge(3);
    a0 = s4;
    jal(0x294ccc, rg::fn_btlActionSetState_00299d60);
L_00294cd4:
    charge(14);
    ld(ra, sp, 160);
    lq(s8, sp, 144);
    lq(s7, sp, 128);
    lq(s6, sp, 112);
    lq(s5, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 1344);
}


// 0x296890 btlActionUpdateStateEscape(action): ESCAPE, the escape attempt (one frame: everything is queued, then ->
// PACKET 30). sub_28A780(action); the escape packet sub_2BD780(unit, +108) (queue 3). An enemy actor (side 1) or a
// party member other than the hero (+164 != 1) runs alone: the run list at sp+160 holds it, +24 |= 0x20 (gone),
// +26 &= ~8. The hero tries for the party: gBtl+2974 (attempts) + 1; an active enemy with a DatUnit and without
// the 0x100000 status makes the escape uncertain (s0 = 0); it succeeds (s6) when sub_30C2A0(DatUnit) says so, when no
// such enemy exists, or with gBtl+26 == 1; it fails (s5) otherwise. Every active living party member goes into the run
// list (on a failure the others get +24 |= 0x8000); gBtl+584 bit 1 (an advantage order) is replaced by the normal
// order sub_29A750. The run list then runs:
//   success / a lone runner: message 7 (the hero) or 9 (the runner); for a party actor the sound sub_2DD1F0(15, 2, 0)
//     after the escape packet (+72 = 32, queue 1) and -- on success sub_2BFB50 (+72 = 22), else, coming from
//     ESCAPE_MES (+16 == 26), the camera sub_2E2BE0(action, 2) and the sound sub_2DB740(action, 3) after it; an enemy
//     actor gets the effect sub_2DD100(12, 2, 22) (+72 = 28) and the sound sub_2DB740(action, 4) (+72 = 12). Each runner
//     walks off: its position (sub_27FFB0) + its run direction (sub_4BE1E0 from its home) x 500 at speed 0.5 for a
//     party runner; an enemy runner whose ENEMY record (232 bytes at *(gp-18648), +34) is not 1 x *(gp-31852) at speed
//     *(gp-32004) (kind 4), else to its own position; the walk after the escape packet (+72 = 22), then the vanish
//     sub_285D30(unit, 0xFFFFFF, 8, 0, 4, 0) after the walk (+72 = 12). On success the end packet sub_27DC00(128)
//     after the last vanish, and gBtl+28 = 3 (escaped).
//   failure: message 7, sub_2BFB50 (+72 = 22); each runner starts off (x 500, speed 0.5, kind 8, +72 = 11) and turns
//     back (sub_285D30 after it, +72 = 12); sub_2BFAE0 (+72 = 12), the stumble sub_2BD850(unit, 216) (+72 = 4, queue 3),
//     the sound sub_2DB740(action, 2, 0, 0, 2); then each runner walks back from its position (sub_280050) along the
//     direction x 250 (speed 1.0, kind 9), again (speed 0.5, kind 24), turns (sub_2822B0(unit, 0, 32)) and settles
//     (sub_285D30(unit, -1, 4, 0, 4, 0), +72 = 12), each after the previous one.
// Finally the result packet sub_2D7FB0(action, 0) (queue 1) and -> PACKET (30). Every packet carries the action's uid.
void Cpu::escape_update() {
    enter(34);
    sp = addiu(sp, -256);
    sd(ra, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;  // the action
    jal(0x2968bc, rg::fn_sub_28A780_0028a780);
    lw(a0, s4, kActUnit);
    lhu(a1, s4, kActMoveKind);
    jal(0x2968cc, rg::fn_sub_2BD780_002bd780);  // the escape packet
    s3 = v0;
    stamp_owner(s4);
    a0 = s3;
    enqueue(0x2968e8, 3);
    a0 = 0;   // 1: the hero tried for the party
    s5 = 0;   // the attempt failed
    s6 = 0;   // the attempt succeeded
    s1 = 0;   // runners at sp+160
    s7 = 0;   // the id of the last vanish packet
    lw(v1, s4, kActUnit);
    lbu(v0, v1, kUnitSide);
    s0 = li(1);
    if (v0 == s0) {  // an enemy runs alone
        charge(8);
        sw(s4, sp, 160);
        s1 = s0 & 0xFFFF;
        lhu(v0, s4, kActFlags);
        v0 = v0 | 0x20;
        sh(v0, s4, kActFlags);
        lhu(v0, s4, kActFlags2);
        v0 = v0 & 0xFFF7;
        sh(v0, s4, kActFlags2);
    } else if (charge(2), v0 == 0) {
        charge(3);
        lhu(v0, v1, 164);
        if (v0 != s0) {  // a party member other than the hero runs alone
            charge(10);
            sw(s4, sp, 160);
            s1 = s0 & 0xFFFF;
            lhu(v0, s4, kActFlags);
            v0 = v0 | 0x20;
            sh(v0, s4, kActFlags);
            lhu(v0, s4, kActFlags2);
            v0 = v0 & 0xFFF7;
            sh(v0, s4, kActFlags2);
        } else {  // the hero: the party tries to escape
            charge(8);
            gbtl(v1);
            lhu(v0, v1, 2974);
            v0 = addiu(v0, 1);
            sh(v0, v1, 2974);
            gbtl(v0);
            lw(s2, v0, kActionList);
            for (;;) {
                charge(2);
                if (s2 == 0) break;
                backedge();
                charge(4);
                lhu(v0, s2, kActFlags2);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    charge(5);
                    lw(a0, s2, kActUnit);
                    lbu(v1, a0, kUnitSide);
                    v0 = li(1);
                    if (v1 == v0) {
                        charge(3);
                        lw(a0, a0, kUnitDat);
                        if (a0 != 0) {
                            charge(5);
                            a1 = lui(0x10);
                            jal(0x296988, rg::fn_datCalcChkBadStatus_00300580);
                            if (v0 == 0) {
                                charge(3);
                                s0 = 0;
                                break;
                            }
                        }
                    }
                }
                charge(1);
                lw(s2, s2, kActNextInList);
            }
            charge(6);
            lw(v0, s4, kActUnit);
            lw(a0, v0, kUnitDat);
            jal(0x2969b8, rg::fn_sub_30C2A0_0030c2a0);  // the escape roll
            bool ok = v0 != 0;
            if (!ok) {
                charge(2);
                ok = s0 != 0;
            }
            if (!ok) {
                charge(5);
                gbtl(v0);
                lhu(v1, v0, kAdvantage);
                v0 = li(1);
                ok = v1 == v0;
            }
            if (ok) {
                charge(3);
                s6 = li(1);
            } else {
                charge(1);
                s5 = v0;
            }
            charge(4);
            gbtl(v0);
            lw(s0, v0, kActionList);
            for (;;) {  // the living party members run
                charge(2);
                if (s0 == 0) break;
                backedge();
                charge(4);
                lhu(v0, s0, kActFlags2);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    charge(4);
                    lw(v1, s0, kActUnit);
                    lbu(v0, v1, kUnitSide);
                    if (v0 == 0) {
                        charge(6);
                        lw(a0, v1, kUnitDat);
                        a1 = 0;
                        jal(0x296a2c, rg::fn_datCalcIsDead_0030b5a0);
                        if (v0 == 0) {
                            charge(2);
                            if (s5 != 0) {
                                charge(2);
                                if (s4 != s0) {
                                    charge(3);
                                    lhu(v0, s0, kActFlags);
                                    v0 = v0 | 0x8000;
                                    sh(v0, s0, kActFlags);
                                }
                            }
                            charge(6);
                            v0 = s1 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(v0, sp);
                            sw(s0, v0, 160);
                            v0 = addiu(s1, 1);
                            s1 = v0 & 0xFFFF;
                        }
                    }
                }
                charge(1);
                lw(s0, s0, kActNextInList);
            }
            charge(5);
            gbtl(v0);
            lhu(v0, v0, kOrderFlags);
            v0 = v0 & 0x2;
            if (v0 != 0) {
                charge(6);
                jal(0x296a90, rg::fn_sub_29A750_0029a750);
                gbtl(v1);
                lhu(v0, v1, kOrderFlags);
                v0 = v0 & 0xFFFD;
                sh(v0, v1, kOrderFlags);
            }
            charge(3);
            a0 = li(1);
        }
    } else {
        charge(2);
    }
    charge(2);
    if (s5 != 0) goto failed;
    // success, or a lone runner
    charge(2);
    if (a0 != 0) {
        charge(10);
        a0 = s4;
        a1 = li(7);
        jal(0x296b44, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        stamp_owner(s4);
        a1 = 0;
        jal(0x296b5c, rg::fn_sub_27ED20_0027ed20);
    } else {
        charge(12);
        lw(a0, sp, 160);
        a1 = li(9);
        jal(0x296b14, rg::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        stamp_owner(s4);
        a1 = 0;
        jal(0x296b2c, rg::fn_sub_27ED20_0027ed20);
    }
    charge(4);
    lw(v0, s4, kActUnit);
    lbu(v0, v0, kUnitSide);
    if (v0 == 0) {
        charge(20);
        a0 = li(15);
        a1 = li(2);
        a2 = 0;
        jal(0x296b80, rg::fn_sub_2DD1F0_002dd1f0);
        a0 = v0;
        depend(0, 5, s3);
        v1 = li(32);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        enqueue(0x296bb0, 1);
        v0 = li(1);
        if (s6 == v0) {
            charge(16);
            jal(0x296c58, rg::fn_sub_2BFB50_002bfb50);
            a0 = v0;
            depend(0, 5, s3);
            v1 = li(22);
            sh(v1, v0, kPktTime);
            stamp_owner(s4);
            enqueue(0x296c88, 1);
        } else {
            charge(4);
            lhu(v1, s4, kActPrev);
            v0 = li(26);
            if (v1 == v0) {  // from ESCAPE_MES
                charge(33);
                a0 = s4;
                a1 = li(2);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(0x296be8, rg::fn_sub_2E2BE0_002e2be0);
                s0 = v0;
                stamp_owner(s4);
                a0 = s0;
                enqueue(0x296c04, 1);
                a0 = s4;
                a1 = li(3);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(0x296c20, rg::fn_sub_2DB740_002db740);
                a0 = v0;
                depend(0, 4, s0);
                stamp_owner(s4);
                enqueue(0x296c48, 1);
            }
        }
    } else {
        charge(32);
        a0 = li(12);
        a1 = li(2);
        a2 = li(22);
        jal(0x296ca4, rg::fn_sub_2DD100_002dd100);
        a0 = v0;
        depend(0, 5, s3);
        v1 = li(28);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        enqueue(0x296cd4, 1);
        a0 = s4;
        a1 = li(4);
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(0x296cf0, rg::fn_sub_2DB740_002db740);
        a0 = v0;
        stamp_owner(s4);
        v1 = li(12);
        sh(v1, v0, kPktTime);
        enqueue(0x296d10, 1);
    }
    charge(4);
    s2 = 0;
    s5 = s1 & 0xFFFF;
    for (;;) {  // each runner walks off and vanishes
        charge(4);
        v0 = s2 & 0xFFFF;
        v0 = slt(v0, s5);
        if (v0 == 0) break;
        backedge();
        charge(25);
        v0 = s2 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(s0, v0, 160);
        run_direction(s0, 0x296d40, rg::fn_sub_27FFB0_0027ffb0, 0x296d58, 0x296d74);
        lw(v0, s4, kActUnit);
        lbu(v0, v0, kUnitSide);
        if (v0 == 0) {
            charge(30);
            v0 = lui(0x43FA);  // 500.0f
            mtc1(v0, F1);
            scale_dir_add();
            v0 = lui(0x3F00);  // 0.5f
            mtc1(v0, F12);
            lw(a0, s0, kActUnit);
            a1 = addiu(sp, 240);
            a2 = 0;
            jal(0x296df0, rg::fn_sub_2819D0_002819d0);
            s1 = v0;
        } else {
            charge(13);
            lw(v0, s0, kActUnit);
            lhu(v1, v0, 164);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, kGpEnemyTbl);
            v0 = addu(v0, v1);  // the ENEMY record (232 bytes)
            lh(v1, v0, 34);
            v0 = li(1);
            if (v1 != v0) {
                charge(21);
                lwc1(F0, sp, 208);
                lwc1(F1, gp, -31852);
                scale_dir_add();
            } else {
                charge(4);
                ld(v0, sp, 224);
                lwc1(F0, sp, 232);
                sd(v0, sp, 240);
                swc1(F0, sp, 248);
            }
            charge(7);
            lw(a0, s0, kActUnit);
            a1 = addiu(sp, 240);
            lwc1(F12, gp, -32004);
            a2 = li(4);
            jal(0x296eac, rg::fn_sub_2819D0_002819d0);
            s1 = v0;
        }
        charge(37);
        v0 = li(5);
        sb(v0, s1, kPktWaitKind0);
        ld(v0, s3, kPktId);
        sd(v0, s1, kPktWaitId0);
        v0 = li(22);
        sh(v0, s1, kPktTime);
        ld(v0, s4, kActUid);
        sd(v0, s1, kPktOwner);
        a0 = s1;
        enqueue(0x296ee0, 1);
        lw(a0, s0, kActUnit);
        v0 = lui(0xFF);
        a1 = v0 | 0xFFFF;
        a2 = li(8);
        a3 = 0;
        t0 = li(4);
        t1 = 0;
        jal(0x296f04, rg::fn_sub_285D30_00285d30);  // the vanish
        s0 = v0;
        depend(0, 5, s1);
        v1 = li(12);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        a0 = s0;
        enqueue(0x296f38, 1);
        ld(s7, s0, kPktId);
        v0 = addiu(s2, 1);
        s2 = v0 & 0xFFFF;
    }
    charge(2);
    if (s6 != 0) {
        charge(17);
        a0 = li(128);
        jal(0x296f68, rg::fn_sub_27DC00_0027dc00);
        a0 = v0;
        depend_id(0, 4, s7);
        stamp_owner(s4);
        enqueue(0x296f8c, 1);
        v1 = li(3);
        gbtl(v0);
        sh(v1, v0, kOutcome);  // escaped
    }
    goto done;
failed:
    charge(28);
    a0 = s4;
    a1 = li(7);
    jal(0x296fb0, rg::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    stamp_owner(s4);
    a1 = 0;
    jal(0x296fc8, rg::fn_sub_27ED20_0027ed20);
    jal(0x296fd0, rg::fn_sub_2BFB50_002bfb50);
    a0 = v0;
    depend(0, 5, s3);
    v1 = li(22);
    sh(v1, v0, kPktTime);
    stamp_owner(s4);
    enqueue(0x297000, 1);
    s0 = 0;
    s5 = s1 & 0xFFFF;
    for (;;) {  // each runner starts off and turns back
        charge(4);
        v0 = s0 & 0xFFFF;
        v0 = slt(v0, s5);
        if (v0 == 0) break;
        backedge();
        charge(84);
        v0 = s0 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(s1, v0, 160);
        run_direction(s1, 0x297030, rg::fn_sub_27FFB0_0027ffb0, 0x297048, 0x297064);
        v0 = lui(0x43FA);  // 500.0f
        mtc1(v0, F1);
        scale_dir_add();
        v0 = lui(0x3F00);  // 0.5f
        mtc1(v0, F12);
        lw(a0, s1, kActUnit);
        a1 = addiu(sp, 240);
        a2 = li(8);
        jal(0x2970d0, rg::fn_sub_2819D0_002819d0);
        s2 = v0;
        depend(0, 5, s3);
        v1 = li(11);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        a0 = s2;
        enqueue(0x297104, 1);
        lw(a0, s1, kActUnit);
        v0 = lui(0xFF);
        a1 = v0 | 0xFFFF;
        a2 = li(8);
        a3 = 0;
        t0 = li(4);
        t1 = 0;
        jal(0x297128, rg::fn_sub_285D30_00285d30);
        a0 = v0;
        depend(0, 5, s2);
        v1 = li(12);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        enqueue(0x297158, 1);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    charge(49);
    jal(0x297178, rg::fn_sub_2BFAE0_002bfae0);
    a0 = v0;
    depend(0, 4, s3);
    v1 = li(12);
    sh(v1, v0, kPktTime);
    stamp_owner(s4);
    enqueue(0x2971a8, 1);
    lw(a0, s4, kActUnit);
    a1 = li(216);
    jal(0x2971b8, rg::fn_sub_2BD850_002bd850);  // the stumble
    a0 = v0;
    a1 = li(4);
    sb(a1, v0, kPktWaitKind0);
    ld(v1, s3, kPktId);
    sd(v1, v0, kPktWaitId0);
    sh(a1, v0, kPktTime);
    stamp_owner(s4);
    enqueue(0x2971e4, 3);
    a0 = s4;
    a1 = li(2);
    a2 = 0;
    a3 = 0;
    t0 = a1;
    jal(0x297200, rg::fn_sub_2DB740_002db740);
    a0 = v0;
    depend(0, 4, s3);
    stamp_owner(s4);
    enqueue(0x297228, 1);
    s1 = 0;
    for (;;) {  // each runner walks back and settles
        charge(4);
        v0 = s1 & 0xFFFF;
        v0 = slt(v0, s5);
        if (v0 == 0) break;
        backedge();
        charge(114);
        v0 = s1 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(s0, v0, 160);
        run_direction(s0, 0x297254, rg::fn_sub_280050_00280050, 0x29726c, 0x297288);
        v0 = lui(0x437A);  // 250.0f
        mtc1(v0, F1);
        scale_dir_add();
        v0 = lui(0x3F80);  // 1.0f
        mtc1(v0, F12);
        lw(a0, s0, kActUnit);
        a1 = addiu(sp, 240);
        a2 = li(9);
        jal(0x2972f4, rg::fn_sub_2819D0_002819d0);
        s2 = v0;
        depend(0, 4, s3);
        stamp_owner(s4);
        a0 = s2;
        enqueue(0x297320, 1);
        v0 = lui(0x3F00);  // 0.5f
        mtc1(v0, F12);
        lw(a0, s0, kActUnit);
        a1 = addiu(sp, 240);
        a2 = li(24);
        jal(0x29733c, rg::fn_sub_2819D0_002819d0);
        s6 = v0;
        depend(0, 4, s2);
        stamp_owner(s4);
        a0 = s6;
        enqueue(0x297368, 1);
        lw(a0, s0, kActUnit);
        a1 = 0;
        a2 = li(32);
        jal(0x29737c, rg::fn_sub_2822B0_002822b0);
        a0 = v0;
        depend(0, 4, s6);
        stamp_owner(s4);
        enqueue(0x2973a4, 1);
        lw(a0, s0, kActUnit);
        a1 = li(-1);
        a2 = li(4);
        a3 = 0;
        t0 = a2;
        t1 = 0;
        jal(0x2973c4, rg::fn_sub_285D30_00285d30);
        a0 = v0;
        depend(0, 4, s3);
        v1 = li(12);
        sh(v1, v0, kPktTime);
        stamp_owner(s4);
        enqueue(0x2973f4, 1);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
done:
    charge(26);
    a0 = s4;
    a1 = 0;
    jal(0x29741c, rg::fn_sub_2D7FB0_002d7fb0);
    a0 = v0;
    stamp_owner(s4);
    enqueue(0x297434, 1);
    a0 = s4;
    a1 = li(30);
    jal(0x297444, rg::fn_btlActionSetState_00299d60);
    ld(ra, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 256);
}

// 0x28BD10 sub_28BD10 [btlActionInitStateCommand](action): COMMAND, the player's command menu opens. sub_28A780(action);
// unless the action comes from state 4, 6 or 5 (+16) or gBtl+240 is 2: the actor and every enemy unit that is not moving
// (sub_281270) turn to their own position (sub_27F7C0 into the 16-byte vector at sp+48, sub_2822B0(unit, vector, 2),
// queue 0), the menu camera sub_2B8D60(3, 0x8001) (queue 0), and when the panel is idle the menu sound
// sub_2DB740(action, 29, 0, 0, 0) (queue 1). Then the panel packet sub_2886E0(0, unit, 2) for a party actor or
// sub_288950(0, 2) otherwise (queue 1), sub_288950(unit, 0) (queue 1, not stamped), the message packet 28 (queue 0),
// the target record's reset sub_2D15A0(action + 56), btlCommand_CreateBattleCommandCalcTasks(action), sub_2899E0(action), and the wait words +1156
// (u16) / +1160 cleared. Packets carry the action's uid.
void Cpu::command_init() {
    enter(11);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x28bd24, rg::fn_sub_28A780_0028a780);
    lhu(v1, s0, kActPrev);
    static constexpr s32 kKeepPrev[] = {4, 6, 5};
    bool keep = false;
    for (std::size_t i = 0; i < 3 && !keep; ++i) {
        if (i != 0) charge(3);
        v0 = li(kKeepPrev[i]);
        keep = v1 == v0;
    }
    if (!keep) {
        charge(5);
        gbtl(v0);
        lhu(v1, v0, 240);
        v0 = li(2);
        keep = v1 == v0;
    }
    if (!keep) {
        charge(21);
        lw(a0, s0, kActUnit);
        a1 = 0;
        a2 = 0;
        a3 = addiu(sp, 48);
        jal(0x28bd78, rg::fn_sub_27F7C0_0027f7c0);
        lw(a0, s0, kActUnit);
        a1 = addiu(sp, 48);
        a2 = li(2);
        jal(0x28bd8c, rg::fn_sub_2822B0_002822b0);
        a0 = v0;
        stamp_owner(s0);
        a1 = 0;
        jal(0x28bda4, rg::fn_sub_27ED20_0027ed20);
        gbtl(v0);
        lw(s1, v0, kSideListA + 8);  // the enemy side's units (+2608)
        for (;;) {
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(5);
            a0 = s1;
            jal(0x28bdc0, rg::fn_sub_281270_00281270);
            if (v0 == 0) {
                charge(17);
                a0 = s1;
                a1 = 0;
                a2 = 0;
                a3 = addiu(sp, 48);
                jal(0x28bde0, rg::fn_sub_27F7C0_0027f7c0);
                a0 = s1;
                a1 = addiu(sp, 48);
                a2 = li(2);
                jal(0x28bdf4, rg::fn_sub_2822B0_002822b0);
                a0 = v0;
                stamp_owner(s0);
                a1 = 0;
                jal(0x28be0c, rg::fn_sub_27ED20_0027ed20);
            }
            charge(1);
            lw(s1, s1, kUnitNext);
        }
        charge(14);
        a0 = li(3);
        a1 = 0x8001;
        jal(0x28be28, rg::fn_sub_2B8D60_002b8d60);
        a0 = v0;
        stamp_owner(s0);
        a1 = 0;
        jal(0x28be40, rg::fn_sub_27ED20_0027ed20);
        jal(0x28be48, rg::fn_sub_1FEEC0_001feec0);
        if (v0 == 0) {
            charge(13);
            a0 = s0;
            a1 = li(29);
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(0x28be6c, rg::fn_sub_2DB740_002db740);
            a0 = v0;
            stamp_owner(s0);
            enqueue(0x28be84, 1);
        }
    }
    charge(4);
    lw(a1, s0, kActUnit);
    lbu(v0, a1, kUnitSide);
    if (v0 == 0) {
        charge(12);
        a0 = 0;
        a2 = li(2);
        jal(0x28bea4, rg::fn_sub_2886E0_002886e0);
        a0 = v0;
        stamp_owner(s0);
        enqueue(0x28bebc, 1);
    } else {
        charge(10);
        a0 = 0;
        a1 = li(2);
        jal(0x28bed4, rg::fn_sub_288950_00288950);
        a0 = v0;
        stamp_owner(s0);
        enqueue(0x28beec, 1);
    }
    charge(35);
    lw(a0, s0, kActUnit);
    a1 = 0;
    jal(0x28befc, rg::fn_sub_288950_00288950);
    a0 = v0;
    enqueue(0x28bf0c, 1);
    a0 = s0;
    a1 = li(28);
    jal(0x28bf1c, rg::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    stamp_owner(s0);
    a1 = 0;
    jal(0x28bf34, rg::fn_sub_27ED20_0027ed20);
    a0 = addiu(s0, kActTarget);
    jal(0x28bf40, rg::fn_sub_2D15A0_002d15a0);
    a0 = s0;
    jal(0x28bf4c, rg::fn_btlCommand_CreateBattleCommandCalcTasks_002bf3f0);
    a0 = s0;
    jal(0x28bf58, rg::fn_sub_2899E0_002899e0);
    sh(zero, s0, kActWait);
    sw(zero, s0, kActWaitOn);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

void Cpu::walk_action_list() {
    gbtl(v0);
    lw(v0, v0, kActionList);
    for (;;) {
        charge(6);
        if (v0 == 0) break;
        backedge();
        charge(1);
        lw(v0, v0, kActNextInList);
    }
}

// 0x28BF80 sub_28BF80 [btlActionUpdateStateCommand](action): COMMAND, one frame of the command menu. The menu steps
// (sub_289B50(action), sub_1FEF50). While a chosen command waits (+1160 == 1) the countdown +1156 runs down and at 0
// sub_2BED10 ends the wait (+1160 = 0). Otherwise the pad bit 3 (0x7E094C / 0x7E0956) toggles the menu's "help" mode
// (gBtl+12 bit 17) when sub_1FE220() allows it -- on: sub_1FE120, message packet 34; off (bit 3 released): sub_1FE1A0,
// message packet 28 -- and the menu result sub_2BECC0() & 0xFFFF picks the next step:
//   3 (a command chosen): the command kind +108 (3 -> sub_2E4430(action, skill +110, 1), 2 / 1 -> sub_2E4430(action,
//     skill, 0), else 0) goes through sub_2E4720; a non-zero answer s1 refuses it (system sound sub_10A4E0(0, 15, 0, 8),
//     the unit's refusal sub_2BCCD0(unit, s1), wait 24 frames: +1156 = 24, +1160 = 1), 0 -> TARGET (6);
//   5: +24 |= 2, the panel closes (sub_1FEF70, sub_1FEA70, sub_2BF650) -> READY (12);
//   7: btlSupportClearFlag(2) -> ANALYZE (7);
//   8: sub_2D19B0, the panel closes -> AI (9) ... the names of the sBtlActionTbl rows 6 / 12 / 7 / 9.
void Cpu::command_update() {
    enter(13);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x28bf94, rg::fn_sub_289B50_00289b50);
    jal(0x28bf9c, rg::fn_sub_1FEF50_001fef50);
    lw(a0, s0, kActWaitOn);
    v1 = li(1);
    if (a0 == v1) {
        charge(3);
        lhu(v1, s0, kActWait);
        if (v1 == 0) {
            charge(5);
            jal(0x28bfc0, rg::fn_sub_2BED10_002bed10);
            sw(zero, s0, kActWaitOn);
        } else {
            charge(2);
            v1 = addiu(v1, -1);
            sh(v1, s0, kActWait);
        }
        charge(2);
        goto out;
    }
    charge(5);
    v0 = lui(0x7E);
    lhu(v0, v0, static_cast<s32>(kPadHeld1 & 0xFFFF));
    v0 = v0 & 0x8;
    if (v0 == 0) {
        charge(5);
        v0 = lui(0x7E);
        lhu(v0, v0, static_cast<s32>(kPadHeld2 & 0xFFFF));
        v0 = v0 & 0x8;
    }
    if (v0 != 0) {  // bit 3 held: the help mode on
        charge(4);
        jal(0x28c00c, rg::fn_sub_1FE220_001fe220);
        if (v0 != 0) {
            charge(6);
            gbtl(v1);
            lw(a0, v1, kFlags);
            v1 = lui(0x2);
            v1 = a0 & v1;
            if (v1 == 0) {
                charge(17);
                jal(0x28c034, rg::fn_sub_1FE120_001fe120);
                gbtl(a0);
                lw(v1, a0, kFlags);
                v0 = lui(0x2);
                v0 = v1 | v0;
                sw(v0, a0, kFlags);
                a0 = s0;
                a1 = li(34);
                jal(0x28c058, rg::fn_sub_2A3B40_002a3b40);
                a0 = v0;
                stamp_owner(s0);
                a1 = 0;
                jal(0x28c070, rg::fn_sub_27ED20_0027ed20);
            }
            charge(2);
            goto out;
        }
    } else {  // released: the help mode off
        charge(6);
        gbtl(v0);
        lw(v1, v0, kFlags);
        v0 = lui(0x2);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(18);
            jal(0x28c098, rg::fn_sub_1FE1A0_001fe1a0);
            gbtl(a0);
            lw(v1, a0, kFlags);
            v0 = lui(0xFFFD);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, kFlags);
            a0 = s0;
            a1 = li(28);
            jal(0x28c0c0, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            stamp_owner(s0);
            a1 = 0;
            jal(0x28c0d8, rg::fn_sub_27ED20_0027ed20);
        }
    }
    // the menu's result
    charge(6);
    jal(0x28c0e0, rg::fn_sub_2BECC0_002becc0);
    a1 = v0 & 0xFFFF;
    v1 = li(8);
    if (a1 == v1) {
        charge(12);
        jal(0x28c290, rg::fn_sub_2D19B0_002d19b0);
        jal(0x28c298, rg::fn_sub_1FEF70_001fef70);
        jal(0x28c2a0, rg::fn_sub_1FEA70_001fea70);
        jal(0x28c2a8, rg::fn_sub_2BF650_002bf650);
        walk_action_list();
        charge(4);
        a0 = s0;
        a1 = li(9);
        jal(0x28c2e4, rg::fn_btlActionSetState_00299d60);
        goto out;
    }
    charge(3);
    v1 = li(7);
    if (a1 == v1) {
        charge(9);
        a0 = li(2);
        jal(0x28c270, rg::fn_btlSupportClearFlag_002db420);
        a0 = s0;
        a1 = li(7);
        jal(0x28c280, rg::fn_btlActionSetState_00299d60);
        goto out;
    }
    charge(3);
    v1 = li(5);
    if (a1 == v1) {
        charge(13);
        lhu(v0, s0, kActFlags);
        v0 = v0 | 0x2;
        sh(v0, s0, kActFlags);
        jal(0x28c210, rg::fn_sub_1FEF70_001fef70);
        jal(0x28c218, rg::fn_sub_1FEA70_001fea70);
        jal(0x28c220, rg::fn_sub_2BF650_002bf650);
        walk_action_list();
        charge(6);
        a0 = s0;
        a1 = li(12);
        jal(0x28c25c, rg::fn_btlActionSetState_00299d60);
        goto out;
    }
    charge(3);
    a0 = li(3);
    if (a1 != a0) {
        charge(2);
        goto out;
    }
    // 3: a command was chosen; may the actor use it?
    charge(3);
    lhu(v1, s0, kActMoveKind);
    if (v1 == a0) {  // 3
        charge(8);
        lhu(a1, s0, kActSkill);
        a0 = s0;
        a2 = li(1);
        jal(0x28c17c, rg::fn_sub_2E4430_002e4430);
        a0 = v0 & 0xFFFF;
    } else {
        charge(3);
        v0 = li(2);
        bool skill = v1 == v0;
        if (!skill) {
            charge(3);
            v0 = li(1);
            skill = v1 == v0;
        }
        if (skill) {  // 2 or 1
            charge(8);
            lhu(a1, s0, kActSkill);
            a0 = s0;
            a2 = 0;
            jal(0x28c15c, rg::fn_sub_2E4430_002e4430);
            a0 = v0 & 0xFFFF;
        } else {
            charge(2);
            charge(1);
            a0 = 0;
        }
    }
    charge(6);
    jal(0x28c194, rg::fn_sub_2E4720_002e4720);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    if (s1 != 0) {
        charge(16);
        a0 = 0;
        a1 = li(15);
        a2 = 0;
        a3 = li(8);
        jal(0x28c1bc, rg::fn_sub_10A4E0_0010a4e0);
        lw(a0, s0, kActUnit);
        a1 = s1;
        jal(0x28c1cc, rg::fn_sub_2BCCD0_002bccd0);
        v1 = li(24);
        sh(v1, s0, kActWait);
        v1 = li(1);
        sw(v1, s0, kActWaitOn);
    } else {
        charge(6);
        a0 = s0;
        a1 = li(6);
        jal(0x28c1f4, rg::fn_btlActionSetState_00299d60);
    }
out:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x28C310 sub_28C310 [btlActionInitStateTarget](action): TARGET, the target cursor opens. The candidate record at
// +136 is filled: an item command (+108 == 4) through sub_2BFCB0(action, +136, 2, 0, 0) with s1 = the item +110 (0 ->
// -1); a skill whose SKILL.TBL record targets a whole side (+8 == 2 or 1) through sub_2BFCB0(action, +136, rec+9,
// rec+10, 0); any other through sub_2BFF60(action, +136, skill, 0). sub_2C0970(+136). For a whole-side skill every
// candidate's unit gets the cursor (sub_1FE7F0(unit+168)) and there is no single target; otherwise sub_2C0AC0(action,
// +136) picks the first, sub_2C0880(+136) returns it and its unit gets the cursor. Then sub_1FE810(s1), the message
// packet 29 (queue 0), sub_1FEF50, sub_2899E0(action), and for a single target its panel packets sub_2886E0(0, unit, 1)
// and sub_288950(unit, 0) (queue 1, not stamped).
void Cpu::target_init() {
    enter(10);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    lhu(v1, a0, kActMoveKind);
    v0 = li(4);
    if (v1 == v0) {  // an item
        charge(9);
        a1 = addiu(s2, kActCandidates);
        a2 = li(2);
        a3 = 0;
        t0 = 0;
        jal(0x28c350, rg::fn_sub_2BFCB0_002bfcb0);
        lhu(s1, s2, kActSkill);
        if (s1 == 0) {
            charge(1);
            s1 = li(-1);
        }
        charge(2);
    } else {
        charge(2);
        charge(12);
        lhu(s1, s2, kActSkill);
        skill_rec(v0, v1, s1);
        lbu(v1, v0, kSkillTarget);
        v0 = li(2);
        bool side = v1 == v0;
        if (!side) {
            charge(3);
            v0 = li(1);
            side = v1 == v0;
        }
        if (side) {
            charge(16);
            skill_rec(v0, v1, s1);
            a0 = s2;
            a1 = addiu(s2, kActCandidates);
            lbu(a2, v0, kSkillTarget + 1);
            lbu(a3, v0, kSkillTarget + 2);
            t0 = 0;
            jal(0x28c3e4, rg::fn_sub_2BFCB0_002bfcb0);
        } else {
            charge(2);
            charge(5);
            a2 = s1 & 0xFFFF;
            a1 = addiu(s2, kActCandidates);
            a3 = 0;
            jal(0x28c400, rg::fn_sub_2BFF60_002bff60);
        }
    }
    charge(15);
    a0 = addiu(s2, kActCandidates);
    jal(0x28c40c, rg::fn_sub_2C0970_002c0970);
    lhu(v1, s2, kActSkill);
    skill_rec(v0, v1, v1);
    lbu(v1, v0, kSkillTarget);
    v0 = li(2);
    bool side = v1 == v0;
    if (!side) {
        charge(3);
        v0 = li(1);
        side = v1 == v0;
    }
    if (side) {
        charge(3);
        s0 = 0;
        for (;;) {
            charge(5);
            v1 = s0 & 0xFFFF;
            lhu(v0, s2, kActCandidateCount);
            v0 = slt(v1, v0);
            if (v0 == 0) break;
            backedge();
            charge(10);
            v0 = s0 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(s2, v0);
            lw(v0, v0, kActCandidates);
            lw(v0, v0, kActUnit);
            lw(a0, v0, kUnitPanelSlot);
            jal(0x28c47c, rg::fn_sub_1FE7F0_001fe7f0);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        charge(3);
        s0 = 0;
    } else {
        charge(2);
        charge(12);
        a0 = s2;
        a1 = addiu(s2, kActCandidates);
        jal(0x28c4b4, rg::fn_sub_2C0AC0_002c0ac0);
        a0 = addiu(s2, kActCandidates);
        jal(0x28c4c0, rg::fn_sub_2C0880_002c0880);
        s0 = v0;
        lw(v0, v0, kActUnit);
        lw(a0, v0, kUnitPanelSlot);
        jal(0x28c4d4, rg::fn_sub_1FE7F0_001fe7f0);
    }
    charge(20);
    a0 = s1;
    jal(0x28c4e0, rg::fn_sub_1FE810_001fe810);
    a0 = s2;
    a1 = li(29);
    jal(0x28c4f0, rg::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    stamp_owner(s2);
    a1 = 0;
    jal(0x28c508, rg::fn_sub_27ED20_0027ed20);
    jal(0x28c510, rg::fn_sub_1FEF50_001fef50);
    a0 = s2;
    jal(0x28c51c, rg::fn_sub_2899E0_002899e0);
    if (s0 != 0) {
        charge(17);
        a0 = 0;
        lw(a1, s0, kActUnit);
        a2 = li(1);
        jal(0x28c538, rg::fn_sub_2886E0_002886e0);
        a0 = v0;
        enqueue(0x28c548, 1);
        lw(a0, s0, kActUnit);
        a1 = 0;
        jal(0x28c558, rg::fn_sub_288950_00288950);
        a0 = v0;
        enqueue(0x28c568, 1);
    }
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x28C590 sub_28C590 [btlActionUpdateStateTarget](action): TARGET, one frame of the target cursor. The menu step
// sub_289B50(action) and the help mode toggle as in COMMAND (message packets 34 / 29). A whole-side skill takes every
// candidate as a target (+56.. = +136.., +106 = the count); otherwise the cursor moves (sub_2C0070(action, +136)), the
// current candidate becomes the only target (+56, +106 = 1, sub_2C08A0(+136, it)) and, when its unit's cursor slot
// (+168) is not the panel's current one (sub_1FE990), the cursor moves there (sub_1FE970) with the panel packets
// sub_2886E0(0, unit, 1) / sub_288950(unit, 0). Then the pads (0x7E094E / 0x7E0958): bit 5 cancels (panel packet
// sub_288950(0, 1), sub_1FE920, sub_2BED10 -> COMMAND 5); bit 6 confirms: the command check sub_2E4520 / sub_2E4720 as
// in COMMAND (a refusal: system sound, sub_2BCCD0(unit, code), stay); an item (+108 == 4): sub_1FE8D0,
// sub_2BEDD0(+56) -> COMMAND (5); else +24 |= 2, the panel closes (sub_1FEF70, sub_1FEA70, sub_1FE8D0, sub_2BF650)
// -> READY (12).
void Cpu::target_update() {
    enter(13);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x28c5a8, rg::fn_sub_289B50_00289b50);
    v1 = lui(0x7E);
    lhu(v1, v1, static_cast<s32>(kPadHeld1 & 0xFFFF));
    v1 = v1 & 0x8;
    if (v1 == 0) {
        charge(5);
        v1 = lui(0x7E);
        lhu(v1, v1, static_cast<s32>(kPadHeld2 & 0xFFFF));
        v1 = v1 & 0x8;
    }
    if (v1 != 0) {  // bit 3 held: the help mode on
        charge(4);
        jal(0x28c5d8, rg::fn_sub_1FE220_001fe220);
        if (v0 != 0) {
            charge(6);
            gbtl(v1);
            lw(a0, v1, kFlags);
            v1 = lui(0x2);
            v1 = a0 & v1;
            if (v1 == 0) {
                charge(17);
                jal(0x28c600, rg::fn_sub_1FE120_001fe120);
                gbtl(a0);
                lw(v1, a0, kFlags);
                v0 = lui(0x2);
                v0 = v1 | v0;
                sw(v0, a0, kFlags);
                a0 = s0;
                a1 = li(34);
                jal(0x28c624, rg::fn_sub_2A3B40_002a3b40);
                a0 = v0;
                stamp_owner(s0);
                a1 = 0;
                jal(0x28c63c, rg::fn_sub_27ED20_0027ed20);
            }
            charge(2);
            goto out;
        }
    } else {  // released: the help mode off
        charge(6);
        gbtl(v1);
        lw(a0, v1, kFlags);
        v1 = lui(0x2);
        v1 = a0 & v1;
        if (v1 != 0) {
            charge(18);
            jal(0x28c664, rg::fn_sub_1FE1A0_001fe1a0);
            gbtl(a0);
            lw(v1, a0, kFlags);
            v0 = lui(0xFFFD);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, kFlags);
            a0 = s0;
            a1 = li(29);
            jal(0x28c68c, rg::fn_sub_2A3B40_002a3b40);
            a0 = v0;
            stamp_owner(s0);
            a1 = 0;
            jal(0x28c6a4, rg::fn_sub_27ED20_0027ed20);
        }
    }
    {
        charge(12);
        lhu(a0, s0, kActSkill);
        skill_rec(v1, a0, a0);
        lbu(a0, v1, kSkillTarget);
        v1 = li(2);
        bool side = a0 == v1;
        if (!side) {
            charge(3);
            v1 = li(1);
            side = a0 == v1;
        }
        if (side) {  // every candidate is a target
            charge(3);
            a1 = 0;
            for (;;) {
                charge(5);
                lhu(a0, s0, kActCandidateCount);
                v1 = a1 & 0xFFFF;
                v1 = slt(v1, a0);
                if (v1 == 0) break;
                backedge();
                charge(7);
                v1 = a1 & 0xFFFF;
                v1 = sll(v1, 2);
                a0 = addu(s0, v1);
                lw(v1, a0, kActCandidates);
                sw(v1, a0, kActTarget);
                v1 = addiu(a1, 1);
                a1 = v1 & 0xFFFF;
            }
            charge(3);
            sh(a0, s0, kActTargetCount);
        } else {  // the cursor
            charge(2);
            charge(21);
            a0 = s0;
            a1 = addiu(s0, kActCandidates);
            jal(0x28c740, rg::fn_sub_2C0070_002c0070);
            a0 = addiu(s0, kActCandidates);
            jal(0x28c74c, rg::fn_sub_2C0880_002c0880);
            s2 = v0;
            sw(s2, s0, kActTarget);
            v0 = li(1);
            sh(v0, s0, kActTargetCount);
            a0 = addiu(s0, kActCandidates);
            a1 = s2;
            jal(0x28c76c, rg::fn_sub_2C08A0_002c08a0);
            lw(v0, s2, kActUnit);
            lw(s1, v0, kUnitPanelSlot);
            jal(0x28c77c, rg::fn_sub_1FE990_001fe990);
            if (s1 != v0) {
                charge(20);
                a0 = s1;
                jal(0x28c790, rg::fn_sub_1FE970_001fe970);
                a0 = 0;
                lw(a1, s2, kActUnit);
                a2 = li(1);
                jal(0x28c7a4, rg::fn_sub_2886E0_002886e0);
                a0 = v0;
                enqueue(0x28c7b4, 1);
                lw(a0, s2, kActUnit);
                a1 = 0;
                jal(0x28c7c4, rg::fn_sub_288950_00288950);
                a0 = v0;
                enqueue(0x28c7d4, 1);
            }
        }
    }
    // cancel (bit 5) / confirm (bit 6)
    charge(5);
    v1 = lui(0x7E);
    lhu(a1, v1, static_cast<s32>(kPadPressed1 & 0xFFFF));
    v1 = a1 & 0x20;
    if (v1 == 0) {
        charge(5);
        v1 = lui(0x7E);
        lhu(a0, v1, static_cast<s32>(kPadPressed2 & 0xFFFF));
        v1 = a0 & 0x20;
    }
    if (v1 != 0) {
        charge(18);
        a0 = 0;
        a1 = li(1);
        jal(0x28c80c, rg::fn_sub_288950_00288950);
        a0 = v0;
        enqueue(0x28c81c, 1);
        jal(0x28c824, rg::fn_sub_1FE920_001fe920);
        jal(0x28c82c, rg::fn_sub_2BED10_002bed10);
        a0 = s0;
        a1 = li(5);
        jal(0x28c83c, rg::fn_btlActionSetState_00299d60);
        goto out;
    }
    charge(3);
    v1 = a1 & 0x40;
    if (v1 == 0) {
        charge(3);
        v1 = a0 & 0x40;
        if (v1 == 0) goto out;
    }
    // confirmed: may the actor use the command on it?
    charge(4);
    lhu(v1, s0, kActMoveKind);
    v0 = li(3);
    if (v1 == v0) {
        charge(8);
        lhu(a1, s0, kActSkill);
        a0 = s0;
        a2 = li(1);
        jal(0x28c8c0, rg::fn_sub_2E4520_002e4520);
        a0 = v0 & 0xFFFF;
    } else {
        charge(3);
        v0 = li(2);
        bool skill = v1 == v0;
        if (!skill) {
            charge(3);
            v0 = li(1);
            skill = v1 == v0;
        }
        if (skill) {
            charge(8);
            lhu(a1, s0, kActSkill);
            a0 = s0;
            a2 = 0;
            jal(0x28c8a0, rg::fn_sub_2E4520_002e4520);
            a0 = v0 & 0xFFFF;
        } else {
            charge(2);
            charge(1);
            a0 = 0;
        }
    }
    charge(6);
    jal(0x28c8d8, rg::fn_sub_2E4720_002e4720);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    if (s1 != 0) {
        charge(12);
        a0 = 0;
        a1 = li(15);
        a2 = 0;
        a3 = li(8);
        jal(0x28c900, rg::fn_sub_10A4E0_0010a4e0);
        lw(a0, s0, kActUnit);
        a1 = s1;
        jal(0x28c910, rg::fn_sub_2BCCD0_002bccd0);
        goto out;
    }
    charge(4);
    lhu(v1, s0, kActMoveKind);
    v0 = li(4);
    if (v1 == v0) {  // an item
        charge(11);
        jal(0x28c938, rg::fn_sub_1FE8D0_001fe8d0);
        lw(a0, s0, kActTarget);
        jal(0x28c944, rg::fn_sub_2BEDD0_002bedd0);
        a0 = s0;
        a1 = li(5);
        jal(0x28c954, rg::fn_btlActionSetState_00299d60);
        goto out;
    }
    charge(2);
    charge(15);
    lhu(v0, s0, kActFlags);
    v0 = v0 | 0x2;
    sh(v0, s0, kActFlags);
    jal(0x28c970, rg::fn_sub_1FEF70_001fef70);
    jal(0x28c978, rg::fn_sub_1FEA70_001fea70);
    jal(0x28c980, rg::fn_sub_1FE8D0_001fe8d0);
    jal(0x28c988, rg::fn_sub_2BF650_002bf650);
    walk_action_list();
    charge(4);
    a0 = s0;
    a1 = li(12);
    jal(0x28c9c4, rg::fn_btlActionSetState_00299d60);
out:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

}  // namespace

// --- host entry points (typed arguments written to the argument registers, sign-extended) ------------------------------
namespace {
void set_a0(EEContext& ctx, u32 v) { core::set_gpr64(ctx, GPR_A0, core::sext32(v)); }
u32 ret(const EEContext& ctx) { return static_cast<u32>(ctx.gpr[GPR_V0].u64[0]); }
}  // namespace

u32 btlMainUpdateStateUnitLoad(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).unit_load_update();
    return ret(ctx);
}
u32 btlMainUpdateStateRevival(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).revival_update();
    return ret(ctx);
}
void btlMainInitStateWin(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).win_init();
}
void btlMainInitStateUnitLoad(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).unit_load_init();
}
void btlMainInitStateEnd(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).end_init();
}
void btlMainInitStateRevival(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).revival_init();
}
void btlMainInitStateCondition(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).condition_init();
}
void btlMainInitStateUnitCreate(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).unit_create_init();
}
u32 btlMainUpdateStateUnitCreate(EEContext& ctx, u32 state) {
    set_a0(ctx, state);
    Cpu(ctx).unit_create_update();
    return ret(ctx);
}
void sub_28BD10(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).command_init();
}
void sub_28BF80(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).command_update();
}
void sub_28C310(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).target_init();
}
void sub_28C590(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).target_update();
}
void btlActionUpdateStateEscape(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).escape_update();
}
void btlActionUpdateStateAttack(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).attack_update();
}
void btlActionUpdateStateSkill(EEContext& ctx, u32 action) {
    set_a0(ctx, action);
    Cpu(ctx).skill_update();
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
namespace g = ::p3fes::game;

void fn_btlMainUpdateStateUnitLoad_0029c110(p3fes::EEContext& ctx) { g::Cpu(ctx).unit_load_update(); }
void fn_btlMainUpdateStateRevival_0029ccd0(p3fes::EEContext& ctx) { g::Cpu(ctx).revival_update(); }
void fn_btlMainInitStateWin_0029ce90(p3fes::EEContext& ctx) { g::Cpu(ctx).win_init(); }
void fn_btlMainInitStateUnitLoad_0029be40(p3fes::EEContext& ctx) { g::Cpu(ctx).unit_load_init(); }
void fn_btlMainInitStateEnd_0029d870(p3fes::EEContext& ctx) { g::Cpu(ctx).end_init(); }
void fn_btlMainInitStateRevival_0029c700(p3fes::EEContext& ctx) { g::Cpu(ctx).revival_init(); }
void fn_btlMainInitStateCondition_0029d1f0(p3fes::EEContext& ctx) { g::Cpu(ctx).condition_init(); }
void fn_btlMainInitStateUnitCreate_0029b280(p3fes::EEContext& ctx) { g::Cpu(ctx).unit_create_init(); }
void fn_btlMainUpdateStateUnitCreate_0029b760(p3fes::EEContext& ctx) { g::Cpu(ctx).unit_create_update(); }
void fn_sub_28BD10_0028bd10(p3fes::EEContext& ctx) { g::Cpu(ctx).command_init(); }
void fn_sub_28BF80_0028bf80(p3fes::EEContext& ctx) { g::Cpu(ctx).command_update(); }
void fn_sub_28C310_0028c310(p3fes::EEContext& ctx) { g::Cpu(ctx).target_init(); }
void fn_sub_28C590_0028c590(p3fes::EEContext& ctx) { g::Cpu(ctx).target_update(); }
void fn_btlActionUpdateStateEscape_00296890(p3fes::EEContext& ctx) { g::Cpu(ctx).escape_update(); }
void fn_btlActionUpdateStateAttack_0028eb50(p3fes::EEContext& ctx) { g::Cpu(ctx).attack_update(); }
void fn_btlActionUpdateStateSkill_00290be0(p3fes::EEContext& ctx) { g::Cpu(ctx).skill_update(); }

}  // namespace p3fes::recomp_gen
