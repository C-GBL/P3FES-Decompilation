// BF script COMM handlers of sScrCommandTable 0x7B92B0, indices 251-501, second pass (slice comm_b2):
// the handlers script_comm_b left (docs/INTEGRATION_LOG.md "script_comm_b"), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/18_script_vm.md sections 2.4 and 3).
//
// CodeFunc_Comm 0x35CF20 sets g_scrCurrentTask and calls the handler with no arguments; a handler reads its
// arguments in place through scrGetIntPara (argument i = slot sp - 1 - i), may read the task's user word
// (scrGetUserData: the battle AI action record or field object the script runs for), writes its result through
// scrSetIntReturnVal and returns 1 (done) or 0 (run again next frame); sub_2CDED0 / sub_2CDE10 / sub_2CDE60 return
// -1. Every handler here is the only table entry of its function and none appears at an index <= 250. The 0x2CA480 ..
// 0x2CDED0 handlers sit inside the battle-AI address band but are COMM handlers of this index range; the AI functions
// they reach (sub_2C0E30, the condition table's functions) stay where they are and are called through their symbols.
//
// Names are the functions.json names (all `sub_*`); a proposed name, where the body makes the role plain, is
// given in brackets (ours, not imported). Each comment gives [COMM index, argc] and what the body does.
//
// Fidelity (wave 7): at every check point, call and return each handler leaves every register as the original
// does -- the prologue's spills on the guest stack, the s-registers and $ra the original holds, and every scratch
// register it writes ($v0/$v1/$a0-$a3 ...) -- because a preempting check point stores the whole register file in
// guest memory. tests/game/test_comm_b2.cpp compares the register file at every check point.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace comm_b2 {
inline constexpr u32 kGp = 0x7D2CF0u;              // crt0's $gp
inline constexpr u32 kBattleWork = kGp - 18692;    // 0x7CE3EC: battle work (+12 flags, +328 / +332 units, +3004 stage)
inline constexpr u32 kFieldFx = kGp - 17912;       // 0x7CE6F8: object whose work (+60) the 0x45A3xx accessors read
inline constexpr u32 kBtlFlagsA = kGp - 18820;     // 0x7CE36C: word pointer (bit 0x20) of sub_25D760 / sub_25D7B0
inline constexpr u32 kBtlFlagsB = kGp - 18940;     // 0x7CE2F4: word pointer (bit 0x40) of sub_20FD80 / sub_20FDD0
inline constexpr u32 kAiConditions = 0x6971B0u;    // the AI condition table: 12-byte entries, +0 the function
inline constexpr u32 kFieldObjTable = 0x86E6A0u;   // 448-byte records; +364 -> an object whose work (+60) byte 0 is set
inline constexpr u32 kStatusDown = 0x80000;        // the bad-status mask the unit finders pass (sub_2C0E30's third argument)
inline constexpr u16 kStage421 = 421, kStage432 = 432, kStage436 = 436;  // battle stage ids (+3004 record, u16 +8)
}  // namespace comm_b2

// --- battle: units found by id (sub_2C0E30 [btlFindUnitById]: first listed, living unit of a side mask whose
// owner's u16 +164 equals the id and whose status lacks 0x80000) ------------------------------------------------
u32 sub_2CE440(EEContext& ctx);  // [254, 2] side arg0 (1 -> mask 2, 0 -> mask 1, else none), id arg1: return unit->+8 | 0x80000000
u32 sub_2CBCD0(EEContext& ctx);  // [431, 2] the same search: return (unit->u16[+24] & 0x1800) != 0
u32 sub_2CBD90(EEContext& ctx);  // [474, 2] ... & 0x1000
u32 sub_2CBE50(EEContext& ctx);  // [475, 2] ... & 0x0800
u32 sub_2CBF10(EEContext& ctx);  // [476, 2] ... & 0x2000
u32 sub_2CDA50(EEContext& ctx);  // [392, 1] id arg0 on the user's own side: return unit->s32[+32] or 0
u32 sub_2CDAD0(EEContext& ctx);  // [393, 1] id arg0 on the other side: return unit->s32[+32] or 0
u32 sub_2CA900(EEContext& ctx);  // [348, 2] id arg0 on the other side: return sub_301CA0(unit's DatUnit, arg1) != 0
u32 sub_2D12E0(EEContext& ctx);  // [445, 2] the current actor (sub_29AD20) is on side arg0 (0/1; else any) and has id arg1

// --- battle: units picked at random / scanned ---------------------------------------------------------------------
void sub_2CFEB0_regs(EEContext& ctx);  // [register ABI] [268, 0] the user's target (sub_2C08C0(user + 136)) if on side 1, else a random living side-1 unit: id | 0x80000000
void sub_2D0150_regs(EEContext& ctx);  // [register ABI] [270, 0] the same for the battle's current unit (+328)
u32 sub_2CC330(EEContext& ctx);  // [478, 0] the user is one of the turn-order slots 1..11 (sub_29AD60) before the current unit
u32 sub_2CF9F0(EEContext& ctx);  // [275, 0] return (s16)datCalcGetSkillElement(user's DatUnit, 0)
u32 sub_2CDED0(EEContext& ctx);  // [459, 1] return (s16)datCalcGetSkillElement(user's DatUnit, (u16)arg0); returns -1

// --- battle: stage words and flags ----------------------------------------------------------------------------------
u32 sub_2D06E0(EEContext& ctx);  // [329, 0] sub_2EAB70() [three stage callbacks]; user->u16[+108] = 8
u32 sub_2D0720(EEContext& ctx);  // [330, 0] sub_2EABB0(); user->u16[+108] = 8
u32 sub_2D0B90(EEContext& ctx);  // [383, 0] user->u16[+108] = 8; sub_2F2450(user)
u32 sub_2D0BD0(EEContext& ctx);  // [384, 0] user->u16[+108] = 8; sub_2F2490(user)
u32 sub_2D0C10(EEContext& ctx);  // [453, 0] return sub_2F2510(user)
u32 sub_2D0C80(EEContext& ctx);  // [452, 0] sub_2F39B0(battle->+328)
u32 sub_2D0860(EEContext& ctx);  // [374, 0] stage 436 -> return sub_2F6C20() != 0; stage 421 -> sub_2EC590() != 0; else nothing
u32 sub_2D0970(EEContext& ctx);  // [492, 0] stage 432 -> return sub_2F5320(); else return 7
u32 sub_2D0AC0(EEContext& ctx);  // [378, 0] return sub_2EFD10() != 0 [battle->+2900]
u32 sub_2D0C50(EEContext& ctx);  // [386, 0] return sub_2F24D0() != 0
u32 sub_2D11D0(EEContext& ctx);  // [439, 0] sub_2D1A70() == 1 -> battle->+12 |= 0x4000
u32 sub_2D1260(EEContext& ctx);  // [441, 0] sub_1FF3B0(); sub_2D1A70() == 1 -> sub_1FF370()
u32 sub_2D12A0(EEContext& ctx);  // [442, 0] sub_1FF390(); sub_2D1A70() == 1 -> sub_1FF350()

// --- field / event --------------------------------------------------------------------------------------------------
u32 sub_1C5670(EEContext& ctx);  // [372, 0] return K_FldDungeon_GetFloorKind() [the current floor's kind]
u32 sub_425360(EEContext& ctx);  // [382, 0] for i < 4: sub_458850(kFieldObjTable[i].+364)
u32 sub_4254C0(EEContext& ctx);  // [419, 0] no kFieldFx object -> return -1 first; return sub_45A3B0() == 1
u32 sub_425530(EEContext& ctx);  // [420, 0] (-1 first as above) sub_45A3E0(); return 0
u32 sub_425580(EEContext& ctx);  // [421, 0] (-1 first) sub_45A400(); return 0
u32 sub_4255D0(EEContext& ctx);  // [422, 1] (-1 first) sub_45A430((s8)arg0); return 0
u32 sub_425640(EEContext& ctx);  // [423, 0] (-1 first) return sub_45AF40()
u32 sub_1C5460(EEContext& ctx);  // [482, 0] return (s16)sub_1099A0()
u32 sub_35FD80(EEContext& ctx);  // [496, 0] return sub_1752B0() & 0xFFFF

// --- g_data: the party members' 20 item slot pairs ({ u16 item, s16 count } at 0x833C58 + 868 * pc); every handler
// takes pc in 1..11 (else it returns 0) and sub_16F490(pc + 256) as the count of the member's other list ----------
u32 sub_4244E0(EEContext& ctx);  // [334, 1] return sub_16F490(pc + 256) + the number of slots with a positive count
u32 sub_4245C0(EEContext& ctx);  // [335, 2] item k: k < n -> sub_16F630(pc + 256, k) & 0xFFFF; else the (k - n)-th positive slot's item, or -1
u32 sub_424730(EEContext& ctx);  // [336, 2] the same index: k < n -> 1; else that slot's (s16) count, or -1
u32 sub_424880(EEContext& ctx);  // [338, 2] k < n -> sub_16F810(pc + 256, k) & 0xFF; else 0
u32 sub_4249B0(EEContext& ctx);  // [337, 1] clear all 20 slot pairs and the pc + 256 list; field party slots 1..3 holding pc -> their flag bytes 0 (all three when none)

// --- g_data: Koromaru's (pc 9) persona slots and equipment ----------------------------------------------------------
u32 sub_1C4F70(EEContext& ctx);  // [464, 0] return the used persona slots + the flagged equipment slots of pc 9
u32 sub_1C5040(EEContext& ctx);  // [465, 1] the item id of the arg0-th of them (persona record u16 +0 / equipment item), or 0
u32 sub_1C5180(EEContext& ctx);  // [473, 0] copy each of them into the first free inventory slot (sub_1831E0(-1, slot, record))
u32 sub_1C4E50(EEContext& ctx);  // [342, 1] copy pc arg0's used persona slots into free inventory slots and clear them (sub_177B50)

// --- party members, battle units, persona, social links ---------------------------------------------------------------
u32 sub_1C2F20(EEContext& ctx);  // [281, 1] party member arg0 down (status 0x80000) -> HP 1 and clear the status [revive]
u32 sub_2CD7F0(EEContext& ctx);  // [286, 1] stage != 436 -> sub_17B220(owner id); clear the user's buff slots 13..16; DatUnit u16 +4 = arg0
u32 sub_2D03E0(EEContext& ctx);  // [343, 3] the party unit with the lowest HP >= arg0 and HP <= arg1 % of max (and status arg2): id | 0x80000000, or -1
u32 sub_2CDE10(EEContext& ctx);  // [457, 0] return (u16)btlGetMeanLevel(1 << own side, 0x80000) [average level]; returns -1
u32 sub_2CDE60(EEContext& ctx);  // [458, 0] the same for the other side; returns -1
u32 sub_35FC70(EEContext& ctx);  // [497, 3] sub_173BB0(pc arg0, stat arg1, delta arg2) (K_Assert stat < 5)
u32 sub_360090(EEContext& ctx);  // [331, 0] sub_172F70(&i) == 1 -> $gp-18204 = i, return 1; else return 0

// --- battle AI conditions through the condition table comm_b2::kAiConditions (12-byte entries; a `jalr` with the
// original frame and $ra): the condition function (subject, argument) answers yes / no ----- ---------------------------------
u32 sub_2CA480(EEContext& ctx);  // [344, 2] the other side's unit with id arg0, condition type 0x01 with argument arg1 & 0xFFFFFF
u32 sub_2CA590(EEContext& ctx);  // [345, 2] the other side's unit with id arg0, condition type 0x02 with argument arg1 & 0xFFFFFF
u32 sub_2CA6A0(EEContext& ctx);  // [346, 2] the other side's unit with id arg0, condition type 0x06 with argument arg1 & 0xFFFFFF
u32 sub_2CA9D0(EEContext& ctx);  // [349, 2] the other side's unit with id arg0, condition type 0x16 with argument arg1 & 0xFFFFFF
u32 sub_2CAAE0(EEContext& ctx);  // [350, 2] the other side's unit with id arg0, condition type 0x17 with argument arg1 & 0xFFFFFF
u32 sub_2CABF0(EEContext& ctx);  // [351, 2] the other side's unit with id arg0, condition type 0x18 with argument arg1 & 0xFFFFFF
u32 sub_2CAD00(EEContext& ctx);  // [352, 2] the other side's unit with id arg0, condition type 0x19 with argument arg1 & 0xFFFFFF
u32 sub_2CAE10(EEContext& ctx);  // [353, 2] the other side's unit with id arg0, condition type 0x22 with argument arg1 & 0xFFFFFF
u32 sub_2CAF20(EEContext& ctx);  // [354, 2] the other side's unit with id arg0, condition type 0x25 with argument arg1 & 0xFFFFFF
u32 sub_2CB030(EEContext& ctx);  // [355, 1] the other side's unit with id arg0, condition entry 40 (argument 0)
u32 sub_2CB0E0(EEContext& ctx);  // [356, 1] the other side's unit with id arg0, condition entry 45 (argument 0)
u32 sub_2CBA00(EEContext& ctx);  // [299, 0] the user, condition entry 67 (argument 0)
u32 sub_2CBA50(EEContext& ctx);  // [300, 0] the user, condition entry 68 (argument 0)
u32 sub_2CBAA0(EEContext& ctx);  // [301, 0] the user, condition entry 69 (argument 0)

}  // namespace p3fes::game
