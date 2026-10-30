// BF script COMM handlers of sScrCommandTable 0x7B92B0, third pass (slice comm_c): 59 of the handlers the slices
// script_comm_a / script_comm_b / comm_b2 / comm_ai left (docs/INTEGRATION_LOG.md, their "not replaced" lists),
// hand-decompiled from SLUS_216.21 (docs/ANALYSIS/18_script_vm.md sections 2.4 and 3, 21_battle.md section 3.2).
//
// Calling convention (18_script_vm.md 2.4): CodeFunc_Comm calls the handler with no arguments; it reads its arguments
// in place through scrGetIntPara(i), its user word through scrGetUserData() (for the battle-AI scripts: the acting
// btlAction, comm_ai.h "The acting unit"), writes the script's result through scrSetIntReturnVal and returns 1 (done)
// -- a few return -1 or a condition (sub_1C3D60 returns 0 = "run me again next frame" while its record exists).
//
// Families (the header comment of each function gives [COMM index, argc] and what it does):
//   * AI conditions through the condition table comm_ai::kCondTable (kind << 24 | param & 0xFFFFFF, `jalr`): about
//     a unit found by id (sub_2C0E30 [btlAIFindUnit]), about the acting unit, about an action found by id
//     (sub_29A210 [btlActionFindById]);
//   * AI target choices through the selector table comm_ai::kTargetTable, falling back to row 0 (AI) when the chosen
//     selector finds nothing; the stage-specific commands sub_2D05C0 / sub_2D0760 / sub_2D0AF0 through row 8 (MYAI);
//   * AI target pickers that return a unit id (`unit +8 | 0x80000000`, or -1): sub_2C3430 [btlAIFilterTargets]
//     (action, param, excluded status, flags, wanted result, predicate) fills the action's candidate list (+0x38,
//     count u16 +0x6A) and returns 1 when it is not empty; the handler takes the only one, a random one
//     (datCalcRand), the one with the lowest HP / highest level ...; sub_2C0F40 [btlAICountUnits] counts units;
//   * field / g_data handlers whose callees are pure (the field unit records gFldUnitsPc 0x8717A0, sField);
//   * two message-window handlers whose path is pure (the manager slot of the script's message handle).
// All are `sub_*` under their functions.json names; a proposed name is given in brackets (ours, not imported).
//
// Fidelity (wave 7): at every check point, call and return each handler leaves every register as the original does
// -- the prologue's spills on the guest stack, the s-registers and $ra the original holds, every scratch register it
// writes ($v0/$v1/$a0-$a3/$t0-$t2/$at) -- because a preempting check point stores the whole register file in guest
// memory. tests/game/test_comm_c.cpp compares the register file at every check point.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace comm_c {
inline constexpr u32 kCondTable = 0x6971B0u;    // AI conditions: {fn, name, flag}[72]
inline constexpr u32 kTargetTable = 0x6975E0u;  // AI target selectors: {fn, name}[37]; row 0 = AI (the fallback)
inline constexpr u32 kSelMyAi = kTargetTable + 8 * 8;    // row 8 MYAI: the stage commands' target choice
inline constexpr u32 kSelRow34 = kTargetTable + 8 * 34;  // row 34: sub_2CD620's selector
inline constexpr u32 kCondRow67 = kCondTable + 12 * 67;  // the condition sub_2CBFD0 asks about a unit
inline constexpr u32 kFldUnitsPc = 0x8717A0u;   // gFldUnitsPc: 448-byte field unit records (0 = the leader)
inline constexpr u32 kField = 0x869F60u;        // sField (K_Field_Get): +0x14 a flag word, +0x18 the field object
inline constexpr u32 kStatusDead = 0x80000u;    // the status mask sub_2C0E30 excludes / sub_2C0F40 is given
}  // namespace comm_c

// All 59 handlers: X(name, addr8, index, argc), addr8 the start address in eight hex digits (fn_<name>_<addr8>).
#define P3FES_COMM_C_HANDLERS(X)   \
    X(sub_2CE170, 002ce170, 251, 2) \
    X(sub_2CE210, 002ce210, 252, 2) \
    X(sub_2CE380, 002ce380, 253, 1) \
    X(sub_2CE5C0, 002ce5c0, 256, 1) \
    X(sub_2CE6C0, 002ce6c0, 257, 1) \
    X(sub_2CE7A0, 002ce7a0, 258, 1) \
    X(sub_2CF450, 002cf450, 259, 1) \
    X(sub_2CF580, 002cf580, 260, 1) \
    X(sub_2CF6B0, 002cf6b0, 261, 1) \
    X(sub_2CFB20, 002cfb20, 262, 1) \
    X(sub_2CFC50, 002cfc50, 263, 1) \
    X(sub_2CFD80, 002cfd80, 264, 1) \
    X(sub_2CF7E0, 002cf7e0, 265, 3) \
    X(sub_2CF890, 002cf890, 266, 3) \
    X(sub_2CF940, 002cf940, 267, 3) \
    X(sub_2CFFC0, 002cffc0, 269, 1) \
    X(sub_2D0270, 002d0270, 271, 0) \
    X(sub_2CE880, 002ce880, 272, 1) \
    X(sub_2CE960, 002ce960, 273, 1) \
    X(sub_2CEA40, 002cea40, 274, 1) \
    X(sub_1C3EB0, 001c3eb0, 287, 1) \
    X(sub_1C3F10, 001c3f10, 288, 1) \
    X(sub_1C3DF0, 001c3df0, 291, 1) \
    X(sub_1C3D60, 001c3d60, 315, 2) \
    X(sub_2CD570, 002cd570, 317, 1) \
    X(sub_2CD620, 002cd620, 319, 0) \
    X(sub_2D05C0, 002d05c0, 323, 4) \
    X(sub_2CE2B0, 002ce2b0, 328, 2) \
    X(sub_360250, 00360250, 333, 0) \
    X(sub_2CA7B0, 002ca7b0, 347, 2) \
    X(sub_1C5600, 001c5600, 371, 1) \
    X(sub_2D0760, 002d0760, 373, 1) \
    X(sub_2D0AF0, 002d0af0, 380, 1) \
    X(sub_1C57B0, 001c57b0, 395, 2) \
    X(sub_2CBAF0, 002cbaf0, 404, 1) \
    X(sub_2CDB70, 002cdb70, 405, 1) \
    X(sub_2CDBE0, 002cdbe0, 406, 1) \
    X(sub_2CDC50, 002cdc50, 407, 1) \
    X(sub_2CDCC0, 002cdcc0, 408, 1) \
    X(sub_2CDD30, 002cdd30, 409, 1) \
    X(sub_2CEB20, 002ceb20, 410, 1) \
    X(sub_2CEC30, 002cec30, 411, 1) \
    X(sub_2CED60, 002ced60, 412, 0) \
    X(sub_2CBBA0, 002cbba0, 430, 3) \
    X(sub_2CD690, 002cd690, 443, 1) \
    X(sub_2CD740, 002cd740, 444, 1) \
    X(sub_2CBFD0, 002cbfd0, 446, 2) \
    X(sub_2CC0A0, 002cc0a0, 454, 2) \
    X(sub_2CC190, 002cc190, 455, 1) \
    X(sub_2CDDA0, 002cdda0, 456, 1) \
    X(sub_2CEF10, 002cef10, 460, 1) \
    X(sub_2CF070, 002cf070, 461, 1) \
    X(sub_2CF1D0, 002cf1d0, 462, 1) \
    X(sub_2CC240, 002cc240, 463, 2) \
    X(sub_2D09D0, 002d09d0, 479, 0) \
    X(sub_2CF340, 002cf340, 485, 1) \
    X(sub_1C5EB0, 001c5eb0, 498, 0) \
    X(sub_3A28A0, 003a28a0, 6, 1)   \
    X(sub_3A2C10, 003a2c10, 40, 2)

// --- AI conditions (comm_c::kCondTable through `jalr`) -------------------------------------------------------------
u32 sub_2CA7B0(EEContext& ctx);  // [347, 2] other side's unit id arg0 (dead ones too when arg1 has bit 0x80000): condition 0x0B MYBAD (arg1 & 0xFFFFFF)
u32 sub_2CE2B0(EEContext& ctx);  // [328, 2] the action with id arg0: condition 0x3F (arg1)
u32 sub_2CBAF0(EEContext& ctx);  // [404, 1] the acting unit: condition 0x46 (arg0)
u32 sub_2CC190(EEContext& ctx);  // [455, 1] the acting unit: condition 0x47 (arg0)
u32 sub_2CBBA0(EEContext& ctx);  // [430, 3] the unit of side arg0 (0/1, else none) with id arg1: condition 0x19 (arg2)
u32 sub_2CBFD0(EEContext& ctx);  // [446, 2] the unit of side arg0 with id arg1: condition row 67 (argument 0)
u32 sub_2CC0A0(EEContext& ctx);  // [454, 2] own side's unit with id arg0: condition 0x3A (arg1)
u32 sub_2CC240(EEContext& ctx);  // [463, 2] own side's unit with id arg0: condition 0x3E (arg1)

// --- AI target choices (comm_c::kTargetTable through `jalr`; none chosen -> row 0, AI) ---------------------------
u32 sub_2CD570(EEContext& ctx);  // [317, 1] selector 0x21 (arg0)
u32 sub_2CD690(EEContext& ctx);  // [443, 1] selector 0x23 (arg0)
u32 sub_2CD740(EEContext& ctx);  // [444, 1] selector 0x24 (arg0)
u32 sub_2CD620(EEContext& ctx);  // [319, 0] selector row 34 (argument 0)
u32 sub_2CE380(EEContext& ctx);  // [253, 1] skill (action u16 +0x6E) without candidates (sub_2BFF60 == 0): target = the action with id arg0 (+0x38, count +0x6A = 1); else row 0 twice
u32 sub_2D05C0(EEContext& ctx);  // [323, 4] skill = arg0 (+0x6E): 0x68 / 0x132 -> command 8 + sub_2EFC90, 0x133 -> command 8 + sub_2EFCD0, else command 9; +0x76/+0x78/+0x7A = arg1..3; target MYAI
u32 sub_2D0760(EEContext& ctx);  // [373, 1] stage 0x1A5: skill 0x16B + sub_2EC560(arg0); stage 0x1B4: skill 0x126 + sub_2F6BF0(arg0); target MYAI
u32 sub_2D0AF0(EEContext& ctx);  // [380, 1] sub_2ECB30(action, (s16)arg0) != 0 -> command 8, target MYAI

// --- AI target pickers: return a unit id (unit +8 | 0x80000000) or -1 ------------------------------------------------
u32 sub_2CE170(EEContext& ctx);  // [251, 2] return sub_2C5FC0(me, action id arg0, (s16)arg1, 0) != -1
u32 sub_2CE210(EEContext& ctx);  // [252, 2] return sub_2C6300(me, action id arg0, (s16)arg1, 0) != -1
u32 sub_2CF7E0(EEContext& ctx);  // [265, 3] return sub_2C5FC0(me, action id arg0, (s16)arg1, arg2)
u32 sub_2CF890(EEContext& ctx);  // [266, 3] return sub_2C6300(me, action id arg0, (s16)arg1, arg2)
u32 sub_2CF940(EEContext& ctx);  // [267, 3] return sub_2C5030(me, action id arg0, arg1, arg2)
u32 sub_2CE5C0(EEContext& ctx);  // [256, 1] candidates (0, 0x2E, sub_2C1ED0): one -> it; arg0 & 0xE -> sub_2C65D0(me); else random
u32 sub_2CE6C0(EEContext& ctx);  // [257, 1] candidates (0x100000, 0x2E, sub_2C1ED0): one -> it, else a random one
u32 sub_2CE7A0(EEContext& ctx);  // [258, 1] candidates (0, 0x2F, sub_2C1ED0): the same
u32 sub_2CE880(EEContext& ctx);  // [272, 1] candidates (0, 0x2C, sub_2C30F0): the same
u32 sub_2CE960(EEContext& ctx);  // [273, 1] candidates (0x100000, 0x2C, sub_2C30F0): the same
u32 sub_2CEA40(EEContext& ctx);  // [274, 1] candidates (0, 0x2D, sub_2C30F0): the same
u32 sub_2CF450(EEContext& ctx);  // [259, 1] candidates (0, 0x2E, sub_2C1ED0): the one with the lowest HP
u32 sub_2CF580(EEContext& ctx);  // [260, 1] candidates (0x100000, 0x2E, sub_2C1ED0): the same
u32 sub_2CF6B0(EEContext& ctx);  // [261, 1] candidates (0, 0x2F, sub_2C1ED0): the same
u32 sub_2CFB20(EEContext& ctx);  // [262, 1] candidates (0, 0x2C, sub_2C30F0): the same
u32 sub_2CFC50(EEContext& ctx);  // [263, 1] candidates (0x100000, 0x2C, sub_2C30F0): the same
u32 sub_2CFD80(EEContext& ctx);  // [264, 1] candidates (0, 0x2D, sub_2C30F0): the same
u32 sub_2CEF10(EEContext& ctx);  // [460, 1] candidates (0, 0x2C, sub_2C30F0): the highest level, ties to the higher HP; returns -1
u32 sub_2CF070(EEContext& ctx);  // [461, 1] the same candidates: a random one without a bad status (bits but 0x100000); returns -1
u32 sub_2CF1D0(EEContext& ctx);  // [462, 1] candidates (0, 0x2C, sub_2C3120, want 1): a random one of the highest level; returns -1
u32 sub_2CF340(EEContext& ctx);  // [485, 1] the count of candidates (0, 0x2C, sub_2C30F0) without a bad status; returns -1
u32 sub_2D0270(EEContext& ctx);  // [271, 0] the living active enemy with the lowest HP that sub_2C5030 accepts, else the lowest HP of all
u32 sub_2CEB20(EEContext& ctx);  // [410, 1] units counted by sub_2C0F40 (1, 1, sub_2C3400): the battle's current unit (+0x148) if listed, else a random one
u32 sub_2CEC30(EEContext& ctx);  // [411, 1] units counted by sub_2C0F40 (2, 1, sub_2C3400): the last with level > 0, else a random one
u32 sub_2CED60(EEContext& ctx);  // [412, 0] the other side's living active units (sub_2BFCB0): a random one of the highest level
u32 sub_2CFFC0(EEContext& ctx);  // [269, 1] the acting unit's skill element that the action with id arg0 is weak to (affinity bit 0x8000000): the element, else -1
u32 sub_2CDB70(EEContext& ctx);  // [405, 1] return (u16)sub_2C0F40(me, arg0, 0x80000, 1, 0, sub_2C3400, 0)
u32 sub_2CDBE0(EEContext& ctx);  // [406, 1] ... (1, 1, sub_2C3400)
u32 sub_2CDC50(EEContext& ctx);  // [407, 1] ... (1, 0, sub_2C1710)
u32 sub_2CDCC0(EEContext& ctx);  // [408, 1] ... (2, 0, sub_2C3400)
u32 sub_2CDD30(EEContext& ctx);  // [409, 1] ... (2, 1, sub_2C3400)
u32 sub_2CDDA0(EEContext& ctx);  // [456, 1] ... (1, 0, sub_2C12F0)
u32 sub_2D09D0(EEContext& ctx);  // [479, 0] stage 0x1B0 -> sub_2F5030(me); command 5

// --- field / g_data -------------------------------------------------------------------------------------------------
u32 sub_1C3EB0(EEContext& ctx);  // [287, 1] arg0 == 0 -> sub_434E60() else sub_434D30() [the field party's follow mode off / on]; return arg0
u32 sub_1C3F10(EEContext& ctx);  // [288, 1] sub_435370((s8)arg0) [the party records' byte +0x1216]; return arg0
u32 sub_1C3DF0(EEContext& ctx);  // [291, 1] sub_429E80(field object, arg0 != 0) when there is one; sField +0x14 = (arg0 == 0)
u32 sub_1C3D60(EEContext& ctx);  // [315, 2] return sub_3C8EC0(arg0, arg1) == 0 [wait while the record exists]
u32 sub_1C5600(EEContext& ctx);  // [371, 1] return sub_43A230((s8)(arg0 + 1)) != 0 [party unit arg0 + 1 in state 5 / 3 or 6]
u32 sub_1C57B0(EEContext& ctx);  // [395, 2] persona of pc arg0 (sub_173380) has skill arg1 among its 8
u32 sub_360250(EEContext& ctx);  // [333, 0] sub_1717B0(); sub_173040(*($gp - 0x471C)) [social link reward]
u32 sub_1C5EB0(EEContext& ctx);  // [498, 0] sub_27D8D0()

// --- message windows (the script's message handle: scrGetMessageID(), < 0 = none -> nothing) -----------------------
u32 sub_3A28A0(EEContext& ctx);  // [6, 1] itfMesMngSetChoiceMask(handle, arg0)
u32 sub_3A2C10(EEContext& ctx);  // [40, 2] sub_3A4A70(handle, arg0, arg1) [set or add the handle's {s16 key, s16 value} pair, up to 15]

}  // namespace p3fes::game
