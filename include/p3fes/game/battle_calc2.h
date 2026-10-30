// The battle data / calculation band 0x2D0000-0x31FFFF, second pass (slice battle_calc2): 97 pure functions of the
// targeting / efficacy / support band (btlTarget*, btlEfficacy.c 0x6978E0, btlSupport.c 0x697B18: 0x2D1570-0x2DD9B0)
// and of the boss-rule band (btlBoss*, btlBossElizabeth.c 0x69A4B0: 0x2DD9B0-0x2FF260), hand-decompiled from
// SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1.1-1.4, 2). The datUnit / datCalc / datScript bands
// (0x2FF260-0x311310) were already replaced by the earlier battle slices except four functions that free or
// allocate through the heap hooks (left recompiled, see game/README.md).
//
// The objects these functions read (21_battle.md section 1, comm_c.h; offsets are decimal where the instructions
// give them so, hex in brackets):
//   gBtl      *(u32*)0x7CE3EC ($gp - 18692): +12 [0xC] flags (bit 21 = 0x200000 tested by the side helpers), +16 [0x10]
//             flags (bit 4 = 0x10: the boss line table), +328 [0x148], +332 [0x14C] the btlAction list head, +344
//             [0x158] the btlUnit list head, +2564..+2604 [0xA04..] the support (navigator) state, +2704.. [0xA90] the
//             16 support slots, +2824..+2948 [0xB08..] the boss-script words, +3004 [0xBBC] the battle setup block
//             (u16 +8 = the encounter id: 416..436 / 456 are the bosses, 21_battle.md 1.2 state 2);
//   btlAction (1,200 bytes): +24 / +26 flags (+26 bit 0 = active, bit 3), +48 [0x30] its btlUnit, +1192 the next
//             action;
//   btlUnit   (the 3D unit, btlUnitCreate 0x2875A0): +26 flags, +152 flags, +160 u16 a counter, +162 [0xA2] the side
//             (0 party, 1 enemy), +164 [0xA4] the unit id (party 1..10, enemy UNIT.TBL ids), +1122.. 24 status
//             counters, +2548 its model record, +2604 [0xA2C] the DatUnit, +2612 the next btlUnit;
//   btlTarget (btlTargetInit(action + 56)): u32 entries at +0 (the target btlActions), u16 count +50 (= action +106),
//             +52/+54 -> +68/+70; a target action's results: count byte +200, 28-byte records from +224 (+224 s32,
//             +232 / +236 words, +250 u16 flags).
// The support line pickers are the 36-row table 0x6978F0 that the support request sub_2DAA20 calls as
// `fn(a0, a1, a2, 0)`; a result < 0 means "no line" (row 0 is sub_2D8390).
//
// Every function is `void name(EEContext&)`: the arguments are read from $a0..$a3 and the result is left in $v0 by
// the very instructions of the original (the header comment of each gives the C view). All keep their
// functions.json names (`sub_*`); a role is given in brackets, proposed names with evidence are in
// symbols/deltas/battle_calc2.sym (ours, not imported).
//
// Fidelity (wave 7): the register transfers are written with the rt:: operations of the instructions they stand for,
// in the original order, so every GPR (in 128 bits), HI/LO and $at holds the original value at every check point,
// call and return; the functions with a frame perform the original prologue / epilogue (the spill slots hold what
// the original stored) and call their callees through the generated symbols with $ra = the original link.
// tests/game/test_battle_calc2.cpp compares the whole register file at every check point and at the return.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace bc2 {
inline constexpr u32 kGBtlPtr = 0x7CE3ECu;       // gBtl ($gp - 18692)
inline constexpr u32 kSupportLineTbl = 0x6978F0u;  // the 36 support line pickers (sub_2DAA20)
inline constexpr s32 kGpGBtl = -18692;            // $gp offsets of the battle globals
inline constexpr s32 kGpSkillElemTbl = -18684;    // 0x7CE3F4: SKILL.TBL section 0, {s8 element, u8}[624]
inline constexpr s32 kGpTbl3F8 = -18680;          // 0x7CE3F8: 44-byte records by unit id (byte +2 = 1 / 2 tested)
inline constexpr s32 kGpTbl400 = -18672;          // 0x7CE400: 28-byte records by unit id
inline constexpr s32 kGpTbl42C = -18628;          // 0x7CE42C: 88-byte records by id (u16 +0, bit 4 tested)
}  // namespace bc2

// All 97 functions: X(name, addr8), addr8 the start address in eight hex digits (fn_<name>_<addr8>).
#define P3FES_BATTLE_CALC2_FUNCS(X) \
    X(sub_2D15E0, 002d15e0)         \
    X(btlTargetGetSideMask, 002d1600)         \
    X(sub_2D3FE0, 002d3fe0)         \
    X(sub_2D4800, 002d4800)         \
    X(sub_2D4CC0, 002d4cc0)         \
    X(btlGetMeanLevel, 002d4cf0)         \
    X(btlCountActiveUnits, 002d4e10)         \
    X(btlGetEncounterId, 002d5550)         \
    X(sub_2D5B50, 002d5b50)         \
    X(sub_2D5BC0, 002d5bc0)         \
    X(sub_2D5BF0, 002d5bf0)         \
    X(sub_2D5C70, 002d5c70)         \
    X(sub_2D5E00, 002d5e00)         \
    X(sub_2D5E10, 002d5e10)         \
    X(sub_2D5EB0, 002d5eb0)         \
    X(sub_2D5F50, 002d5f50)         \
    X(sub_2D5FB0, 002d5fb0)         \
    X(sub_2D6090, 002d6090)         \
    X(sub_2D6130, 002d6130)         \
    X(sub_2D6210, 002d6210)         \
    X(sub_2D62D0, 002d62d0)         \
    X(datCalcIsHpSkill, 002d6370)         \
    X(sub_2D63B0, 002d63b0)         \
    X(sub_2D7970, 002d7970)         \
    X(sub_2D7DF0, 002d7df0)         \
    X(sub_2D7EF0, 002d7ef0)         \
    X(sub_2D7F10, 002d7f10)         \
    X(sub_2D7F90, 002d7f90)         \
    X(sub_2D8020, 002d8020)         \
    X(sub_2D8070, 002d8070)         \
    X(sub_2D80F0, 002d80f0)         \
    X(sub_2D8310, 002d8310)         \
    X(sub_2D8680, 002d8680)         \
    X(sub_2D8A80, 002d8a80)         \
    X(sub_2D8AC0, 002d8ac0)         \
    X(sub_2D8B00, 002d8b00)         \
    X(sub_2D8B10, 002d8b10)         \
    X(sub_2D8B20, 002d8b20)         \
    X(sub_2D8B30, 002d8b30)         \
    X(sub_2D8DB0, 002d8db0)         \
    X(sub_2D8EF0, 002d8ef0)         \
    X(sub_2D8F40, 002d8f40)         \
    X(sub_2D9AA0, 002d9aa0)         \
    X(sub_2D9D60, 002d9d60)         \
    X(btlSupportClearFlag, 002db420)         \
    X(btlSupportTestFlag, 002db450)         \
    X(sub_2DB690, 002db690)         \
    X(btlSupportRequestLine, 002db9f0)         \
    X(btlSupportIsBusy, 002dba60)         \
    X(sub_2DC130, 002dc130)         \
    X(sub_2DC550, 002dc550)         \
    X(sub_2DC5E0, 002dc5e0)         \
    X(btlSupportResetTimers, 002dcbc0)         \
    X(btlSupportTickTimers, 002dcc40)         \
    X(nullsub_19, 002dcd20)         \
    X(sub_2DD8B0, 002dd8b0)         \
    X(sub_2DD930, 002dd930)         \
    X(sub_2E2630, 002e2630)         \
    X(nullsub_20, 002e2f20)         \
    X(sub_2E33F0, 002e33f0)         \
    X(sub_2E4220, 002e4220)         \
    X(sub_2E4240, 002e4240)         \
    X(sub_2E4250, 002e4250)         \
    X(sub_2EC4B0, 002ec4b0)         \
    X(sub_2EC560, 002ec560)         \
    X(sub_2EC590, 002ec590)         \
    X(sub_2ECAC0, 002ecac0)         \
    X(sub_2ED350, 002ed350)         \
    X(sub_2EFD10, 002efd10)         \
    X(sub_2F23D0, 002f23d0)         \
    X(sub_2F2410, 002f2410)         \
    X(sub_2F24D0, 002f24d0)         \
    X(sub_2F2510, 002f2510)         \
    X(sub_2F4480, 002f4480)         \
    X(sub_2F5320, 002f5320)         \
    X(btlBossResetCounters, 002f6bc0)         \
    X(sub_2F6BF0, 002f6bf0)         \
    X(sub_2F6C20, 002f6c20)         \
    X(sub_2F8840, 002f8840)         \
    X(sub_2F8EA0, 002f8ea0)         \
    X(sub_2F8EB0, 002f8eb0)         \
    X(sub_2F9560, 002f9560)         \
    X(sub_2F9690, 002f9690)         \
    X(sub_2FC410, 002fc410)         \
    X(sub_2FCF50, 002fcf50)         \
    X(sub_2FD060, 002fd060)         \
    X(sub_2FD500, 002fd500)         \
    X(sub_2FD7C0, 002fd7c0)         \
    X(sub_2FDB70, 002fdb70)         \
    X(sub_2FDB90, 002fdb90)         \
    X(sub_2FDCB0, 002fdcb0)         \
    X(sub_2FDCF0, 002fdcf0)         \
    X(sub_2FDD40, 002fdd40)         \
    X(sub_2FDED0, 002fded0)         \
    X(sub_2FDFA0, 002fdfa0)         \
    X(nullsub_52, 003140a0)         \
    X(nullsub_53, 003140b0)

// --- btlTarget / btlEfficacy: the target list and unit-table helpers ($a0 = a btlTarget unless noted) ---------------
void sub_2D15E0(EEContext& ctx);  // t +68 = t +52; t +70 = t +54 (u16 copies)
void btlTargetGetSideMask(EEContext& ctx);  // the u16 mask of 1 << side (+48 -> +162) over the t->count (u16 +50) entries [btlTargetGetSideMask]
void sub_2D3FE0(EEContext& ctx);  // a0 = a node (flag word +156, links +2500 prev / +2504 next): bit 2 set -> clear it and unlink (next +1224 = prev; prev ? prev +1228 = next : gBtl +716 = next)
void sub_2D4800(EEContext& ctx);  // a0 +1024 = a0 +1026 = 0 (u16)
void sub_2D4CC0(EEContext& ctx);  // (u16 skill): byte 0 of the EFFECT.TBL section 0 record (28 bytes, $gp - 18672), 0 -> 1
void btlGetMeanLevel(EEContext& ctx);  // (u16 side mask, status): the mean level of the active units on those sides without the status (datCalcGetLevel), 0 -> 1 [btlGetMeanLevel]
void btlCountActiveUnits(EEContext& ctx);  // (u16 side mask, status): the count of active units (+26 bits 0 and 3) on those sides without the status [btlCountActiveUnits]
void btlGetEncounterId(EEContext& ctx);  // the encounter id: u16 +8 of the setup block gBtl +3004 [btlGetEncounterId]
void sub_2D5B50(EEContext& ctx);  // (skill): 331 -> 13; 327..330 -> 12; else -1
void sub_2D5BC0(EEContext& ctx);  // 327 + datCalcRand(5)
void sub_2D5BF0(EEContext& ctx);  // (btlUnit): sub_17D800() (The Answer) && DatUnit && DatUnit id == 1 (the hero) && side 0
void sub_2D5C70(EEContext& ctx);  // the same for unit id 9
void sub_2D5E00(EEContext& ctx);  // a0 +20 = 0 (u16)
void sub_2D5E10(EEContext& ctx);  // (btlAction a): any target action (a +56, count u16 a +106) with a result (+224 + 28 j, count byte +200) whose u16 +250 has bit 2
void sub_2D5EB0(EEContext& ctx);  // (btlAction a): any target result whose word +232 has bit 20
void sub_2D5F50(EEContext& ctx);  // (btlAction a): any target action with word +212 != 0
void sub_2D5FB0(EEContext& ctx);  // (btlAction a): over the targets but a itself: one on another side -> 0; else 1 when (while still 0) a result has +224 > 0 or +236 != 0
void sub_2D6090(EEContext& ctx);  // (btlAction a): any target result whose word +236 has bit 19
void sub_2D6130(EEContext& ctx);  // (btlAction a): a target with +212 != 0 or u16 +204 & 0x500 -> 0; else 1 when (while still 0) a result has +224 < 0
void sub_2D6210(EEContext& ctx);  // (btlAction a): any target with +212 != 0 or u16 +204 & 0x500
void sub_2D62D0(EEContext& ctx);  // (btlAction a): fewer than 2 targets -> 0; an active target (+26 bit 0) on another side than a -> 0; else 1
void datCalcIsHpSkill(EEContext& ctx);  // ((s16) skill): SkillRecord kind (byte +2, SKILL.TBL section 1 at $gp - 18680) == 1, an HP skill [datCalcIsHpSkill]
void sub_2D63B0(EEContext& ctx);  // (btlUnit u, (s16) skill, flag): SkillRecord kind == 1 and flag and MODEL.TBL section 3 ($gp - 18628, 88 bytes by u id) u16 +0 bit 4 clear and EFFECT.TBL section 0 u16 +2 bit 0 set

// --- the per-unit counters (+160) of a pair / a single object, and the +40 step byte ----------------------------------
void sub_2D7970(EEContext& ctx);  // (u32 pair[2]): ++ (pair[0] +48) +160, ++ (pair[1] +48) +160
void sub_2D7DF0(EEContext& ctx);  // the same, -- both
void sub_2D7EF0(EEContext& ctx);  // ++ (*a0 +48) +160
void sub_2D7F10(EEContext& ctx);  // byte a0 +4: bit 1 -> (*a0) +40 = 0; bit 0 -> ++ +40; else +40 = max(+40, 1) - 1 when > 0; returns 1
void sub_2D7F90(EEContext& ctx);  // -- (*a0 +48) +160
void sub_2D8020(EEContext& ctx);  // ++ (*a0 +48) +160
void sub_2D8070(EEContext& ctx);  // -- (*a0 +48) +160
void sub_2D80F0(EEContext& ctx);  // ++ (*a0 +48) +160
void sub_2D8310(EEContext& ctx);  // -- (*a0 +48) +160

// --- support (navigator) line pickers, rows of 0x6978F0 (a0 = the btlAction unless noted; < 0 = no line) -----------
void sub_2D8680(EEContext& ctx);  // row 2: a1 == 1 -> -1; a1 == 0 -> 95; else -1
void sub_2D8A80(EEContext& ctx);  // row 8: encounter 417 -> 136, else 135
void sub_2D8AC0(EEContext& ctx);  // row 9: encounter 417 -> 132, else 131
void sub_2D8B00(EEContext& ctx);  // row 10: 143
void sub_2D8B10(EEContext& ctx);  // row 11: 182
void sub_2D8B20(EEContext& ctx);  // row 12: 177
void sub_2D8B30(EEContext& ctx);  // row 13: 178
void sub_2D8DB0(EEContext& ctx);  // row 17: -1
void sub_2D8EF0(EEContext& ctx);  // row 20: a is gBtl's current action (+328) -> 234; else a's unit an enemy -> 235; else -1
void sub_2D8F40(EEContext& ctx);  // row 21: a is gBtl's current action -> 398, else -1
void sub_2D9AA0(EEContext& ctx);  // row 23: a party unit and gBtl's current action: a1 bit 1 -> 336, bit 2 -> 335; else -1
void sub_2D9D60(EEContext& ctx);  // row 28: -1

// --- the support state in gBtl ---------------------------------------------------------------------------------------
void btlSupportClearFlag(EEContext& ctx);  // (u16 n): gBtl +2564 &= ~(1 << n) (u16) [btlSupportClearFlag]
void btlSupportTestFlag(EEContext& ctx);  // (u16 n): gBtl +2564 bit n != 0 [btlSupportTestFlag]
void sub_2DB690(EEContext& ctx);  // gBtl +2568
void btlSupportRequestLine(EEContext& ctx);  // (u16 line, id): a line playing (+2582 bit 0) for this id (+2592 or +2600 == id) -> 1; else +2604 = line, +2600 = id, +2584 = 1; returns 1 [btlSupportRequestLine]
void btlSupportIsBusy(EEContext& ctx);  // gBtl +2582 bit 0 != 0 [btlSupportIsBusy]
void sub_2DC130(EEContext& ctx);  // (btlAction a): a +24 bit 2 -> 0; else datCalcChkBadStatus(a's DatUnit, 0x80) != 0
void sub_2DC550(EEContext& ctx);  // (btlAction a, bits): bits != 0: for k < 24, a bit of `bits` that the DatUnit's status word lacks clears the byte a +1122 + k
void sub_2DC5E0(EEContext& ctx);  // (btlAction a): for k < 24, a bit of the DatUnit's status word counts the byte a +1122 + k up (below 255)
void btlSupportResetTimers(EEContext& ctx);  // gBtl +2704 = 5, +2706 = -1, the 16 six-byte slots +2708 = {-1, -1, 3} [btlSupportResetTimers]
void btlSupportTickTimers(EEContext& ctx);  // the support timers: +2706 and each slot's +2712 count up while >= 0 and reset to -1 (the slot to {-1, -1, -1}) once they reach 3 or more [btlSupportTickTimers]
void nullsub_19(EEContext& ctx);  // empty
void sub_2DD8B0(EEContext& ctx);  // (u32* p): (*p) +152 bit 1 -> its model record +1022 |= 0x20; returns 1
void sub_2DD930(EEContext& ctx);  // the same, &= ~0x20

// --- boss rules (a0 = a btlUnit unless noted) ---------------------------------------------------------------------------
void sub_2E2630(EEContext& ctx);  // (btlAction): its unit is enemy 294 -> 828, else -1
void nullsub_20(EEContext& ctx);  // empty
void sub_2E33F0(EEContext& ctx);  // (btlAction): an enemy id -> a code (240 -> 4, 239 -> 2, 238 -> 10, 237 -> 5, 236 -> 8, 235 -> 7, 234 / 233 -> themselves, 294 -> 103, 264 -> 17, 271 / 268 -> 16, 272 / 267 -> 15, other -> -1); a party unit -> its (s16) id
void sub_2E4220(EEContext& ctx);  // (a, b, c): gBtl +2824/+2828/+2832 = a, b, c
void sub_2E4240(EEContext& ctx);  // (c): gBtl +2832 = c
void sub_2E4250(EEContext& ctx);  // gBtl +2824 != 0 || +2828 != 0
void sub_2EC4B0(EEContext& ctx);  // enemy 263 with +152 bit 1: its model byte +1053 += 32 (up to 255) when gBtl +2892, else -= 32 (down to 0)
void sub_2EC560(EEContext& ctx);  // (x): encounter 421 -> gBtl +2884 = 1, +2888 = x
void sub_2EC590(EEContext& ctx);  // encounter 421 -> gBtl +2884, else 0
void sub_2ECAC0(EEContext& ctx);  // the first btlUnit of gBtl +344 with id 266: !datCalcIsDead(its DatUnit, 0); none -> 0
void sub_2ED350(EEContext& ctx);  // gBtl +2904 = 0 (u16)
void sub_2EFD10(EEContext& ctx);  // gBtl +2900
void sub_2F23D0(EEContext& ctx);  // sub_302380(DatUnit, 0x4000000, 1); gBtl +2896 = 1
void sub_2F2410(EEContext& ctx);  // datCalcClearEffect(DatUnit, 11); gBtl +2896 = 0; returns 1
void sub_2F24D0(EEContext& ctx);  // (s8) datCalcGetEffectState(first btlUnit's DatUnit, 11) > 0
void sub_2F2510(EEContext& ctx);  // (p): p +32 < gBtl +2892 -> gBtl +2892 = p +32, return 0; else the difference
void sub_2F4480(EEContext& ctx);  // 0
void sub_2F5320(EEContext& ctx);  // gBtl +2904
void btlBossResetCounters(EEContext& ctx);  // gBtl +2896 = 0, +2900 = 40, +2902 = 0, +2904 = 0; returns 1 [btlBossResetCounters]
void sub_2F6BF0(EEContext& ctx);  // (x): encounter 436 -> gBtl +2888 = 0, +2892 = x
void sub_2F6C20(EEContext& ctx);  // encounter 436 -> gBtl +2888, else 0
void sub_2F8840(EEContext& ctx);  // (u16 k): gBtl +16 bit 4: row k (20 bytes) of block (s16) gBtl +2948 (800 bytes each) of 0x699280 when its word 0 or 1 is non-zero (the row address), else 0
void sub_2F8EA0(EEContext& ctx);  // 0
void sub_2F8EB0(EEContext& ctx);  // (btlUnit, (s16) skill): encounter 430: enemy 294's skill element (SKILL.TBL section 0, K_Assert skill < 464) 0 / 1 / 2 -> 4 / 5 / 6, else -1 (u16 -> s16); other encounters -1
void sub_2F9560(EEContext& ctx);  // (btlUnit, u16* p): encounter 421 / enemy 263: p[1] == 23 -> 0, else gBtl +2884 ? 12 : -1; encounter 424 / enemy 269: p[1] == 25 -> 0; else -1
void sub_2F9690(EEContext& ctx);  // encounters 431..435 and an enemy -> 0, else -1
void sub_2FC410(EEContext& ctx);  // encounter 424 / enemy 269 / gBtl +2900 == 1 -> 0x69A0E8; encounter 436 / enemy 241 / gBtl +2888 == 1 -> 0x69A5A8 (boss data records); else 0
void sub_2FCF50(EEContext& ctx);  // (btlAction, active +26 bit 0): encounter 430 / enemy 294 or encounter 432 / enemy 234 -> gBtl +2896, else 0
void sub_2FD060(EEContext& ctx);  // the same for encounter 429 / enemy 274 and 436 / enemy 241 -> gBtl +2884
void sub_2FD500(EEContext& ctx);  // gBtl +2856 != 0
void sub_2FD7C0(EEContext& ctx);  // no setup block -> 0; encounter 429 or 456 -> 0; else 1
void sub_2FDB70(EEContext& ctx);  // !(gBtl +12 & 0x200000)
void sub_2FDB90(EEContext& ctx);  // the same (a second copy)
void sub_2FDCB0(EEContext& ctx);  // gBtl +12 & 0x200000 ? side == 1 : 0
void sub_2FDCF0(EEContext& ctx);  // (u, v): gBtl +12 & 0x200000 and u, v both enemies -> 0, else 1
void sub_2FDD40(EEContext& ctx);  // (u, v): gBtl +12 & 0x200000 and u not an enemy and u != v -> u and v on the same side; else 0
void sub_2FDED0(EEContext& ctx);  // ((s16) id): encounter 436: gBtl +2908 = id for 294 / 296 / 295 / 293 else -1; 296 / 295 / 293 return the address of btlBossResetCounters, else 0
void sub_2FDFA0(EEContext& ctx);  // encounter 436 -> 0, else 1
void nullsub_52(EEContext& ctx);  // empty
void nullsub_53(EEContext& ctx);  // empty

}  // namespace p3fes::game
