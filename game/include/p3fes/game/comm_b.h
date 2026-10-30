// BF script COMM handlers of sScrCommandTable 0x7B92B0, indices 251-501 (slice script_comm_b),
// hand-decompiled from SLUS_216.21 (docs/ANALYSIS/18_script_vm.md sections 2.4 and 3).
//
// CodeFunc_Comm 0x35CF20 sets g_scrCurrentTask and calls the handler with no arguments; a handler reads
// its arguments in place through scrGetIntPara / scrGetFloatPara (argument i = slot sp - 1 - i), may read
// the task's user word (scrGetUserData: the battle unit / field object the script runs for), writes its
// result through scrSetIntReturnVal and returns 1 (done: CodeFunc_Comm drops `argc` slots and steps the
// pc) or 0 (re-run next frame with the same arguments). Every handler below is the only table entry of its
// function; none appears at an index <= 250. Names are the functions.json names (all `sub_*` except
// clndScrCmd_TIME_SKIP); a proposed name, where the body makes the role plain, is given in brackets.
// Each comment gives [COMM index, argc] and what the body does.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace comm_b {
// $gp-relative words (crt0's $gp = 0x7D2CF0).
inline constexpr u32 kGp = 0x7D2CF0u;
inline constexpr u32 kEventWork = kGp - 19052;     // 0x7CE284: event/field work record; +284 -> the current field descriptor
inline constexpr u32 kFieldParams = kGp - 17924;   // 0x7CE6EC: record written by the 0x425xxx handlers
inline constexpr u32 kBattleWork = kGp - 18692;    // 0x7CE3EC: battle work (+332 unit list, +3004, +3376 s32[] script words)
inline constexpr u32 kBattleTable44 = kGp - 18680; // 0x7CE3F8: 44-byte records, byte 0 bit 1 = valid (sub_2D0A30's assert)
inline constexpr u32 kBattleTable28 = kGp - 18504; // 0x7CE4A8: 28-byte records indexed by a u16 of the +3004 record
inline constexpr u32 kFieldTask = kGp - 19932;     // 0x7CDF14: object whose work (+60) holds an s16 at +484 (sub_10BF40)
inline constexpr u32 kCalendarTask = kGp - 19716;  // 0x7CDFEC: object whose work (+60) sub_17F990 writes
inline constexpr u32 kSavedWords = kGp - 19784;    // 0x7CDFA8: s16[4], copied to / from kGdataWords
inline constexpr u32 kGdataWords = 0x83A6E0u;      // s16[4] in g_data (0x836200 + 17632)
inline constexpr u32 kFieldTable = 0x8717E8u;      // 448-byte records: +0 word, +12 pointer to a u16 (sub_1C4080)
inline constexpr u32 kVec4Table = 0x86BE00u;       // 16-byte records { s32, f32, ?, f32 } (sub_4253D0)
inline constexpr u32 kBattleFloatsA = 0x957170u;   // sub_2D0EF0: f32 x3 at +0, f32 x3 at -0x20
inline constexpr u32 kBattleFloatsB = 0x957160u;   // sub_2D0F90: f32 x3 at +0, f32 x3 at -0x20
inline constexpr u32 kSkillRowTable = 0x5E3C20u;   // .data: 48-byte rows of s16 pairs read by sub_17FD30 (rows 2..10, at -96)
inline constexpr u32 kSourceFileBattle = 0x697720u;  // the K_Assert file argument of sub_2D0A30 (line 4491)
inline constexpr u16 kField4021 = 4021;            // field id compared by sub_1C3990 / sub_424F10
}  // namespace comm_b

// --- leaves (no callee but the scr accessors) --------------------------------------------------------
void sub_1C3A10_regs(EEContext& ctx);  // [register ABI] [278, 0] fd = *(kEventWork)->+284; return fd->u16[+2] < 4000 ? work->u8[+296] : 0
void sub_2CD8C0_regs(EEContext& ctx);  // [register ABI] [302, 1] unit flags (user->+48->+2604)->u16[+0]: arg0 & 0xFFFF == 0 sets bit 0x10, else clears it
void sub_2CD940_regs(EEContext& ctx);  // [register ABI] [303, 1] the same with bit 0x20
void sub_1C3F60_regs(EEContext& ctx);  // [register ABI] [304, 0] return user->s32[+0] (the count of the user's id list)
void sub_1C3F90_regs(EEContext& ctx);  // [register ABI] [305, 1] return user->s32[+4 + 4*arg0]
void sub_1C3FE0_regs(EEContext& ctx);  // [register ABI] [306, 1] return 1 if arg0 is among user->s32[+4 + 4i] for i < user->s32[+0], else 0
void sub_1C4080_regs(EEContext& ctx);  // [register ABI] [311, 1] r = kFieldTable[arg0]; return (r.+0 && r.+12) ? *(u16*)r.+12 : 0
void sub_2CDA10_regs(EEContext& ctx);  // [register ABI] [318, 0] return (user->+48->+2604)->u16[+4]
void sub_16EB80_regs(EEContext& ctx);  // [register ABI] [326, 0] kSavedWords[0..3] = kGdataWords[0..3] (leaf, no frame)
void sub_16EBE0_regs(EEContext& ctx);  // [register ABI] [327, 0] kGdataWords[0..3] = kSavedWords[0..3] (leaf, no frame)
void sub_1C3950_regs(EEContext& ctx);  // [register ABI] [361, 0] return fd->u8[+7] & 1 (fd as in sub_1C3A10)
void sub_4250B0_regs(EEContext& ctx);  // [register ABI] [364, 1] (*kFieldParams)->u8[+173] = arg0
void sub_4250E0_regs(EEContext& ctx);  // [register ABI] [365, 3] i = (s8)((s8)arg0 - 1); p = *kFieldParams: u16[+124+6i] = arg2, [+126+6i] = [+128+6i] = 0, u8[+166+i] = arg1
void sub_425190_regs(EEContext& ctx);  // [register ABI] [366, 2] arg0 != 0: append { u8 arg0 @+4, u16 arg1 @+6 } at slot p->s8[+160] (4-byte slots), count++
void sub_425220_regs(EEContext& ctx);  // [register ABI] [367, 2] p->u8[+164] = arg0, p->u16[+162] = arg1
void sub_425270_regs(EEContext& ctx);  // [register ABI] [368, 1] p->u8[+174] = arg0
void sub_4252A0_regs(EEContext& ctx);  // [register ABI] [379, 1] p->u8[+175] = arg0
void sub_2D0A30_regs(EEContext& ctx);  // [register ABI] [385, 1] assert kBattleTable44[arg0] bit 1 (K_Assert line 4491, no-op); user->u16[+108] = 1, [+110] = arg0
void sub_2D14D0_regs(EEContext& ctx);  // [register ABI] [402, 1] return (*kBattleWork)->s32[+3376 + 4*arg0]
void sub_2D1510_regs(EEContext& ctx);  // [register ABI] [403, 2] (*kBattleWork)->s32[+3376 + 4*arg0] = arg1
void sub_2D0CB0_regs(EEContext& ctx);  // [register ABI] [413, 0] return (kBattleTable28[(*kBattleWork)->+3004->u16[+8]].+0 & 0x20) != 0
void sub_4253D0_regs(EEContext& ctx);  // [register ABI] [415, 4] r = kVec4Table + 16*(s16)arg0: s32 +0 = arg1, f32 +4 = arg2, f32 +12 = arg3 (cvt.s.w; $f0 = arg3)
void sub_1C3990_regs(EEContext& ctx);  // [register ABI] [416, 0] return fd->u16[+2] == 4021 ? fd->s32[+8] : 0
void sub_424F10_regs(EEContext& ctx);  // [register ABI] [417, 0] return user->u16[+426] == 4021 ? 0 : (user->u16[+428] & 1 ? 1 : 2)
u32 sub_10BF40(EEContext& ctx);  // [427, 0] leaf: done (1) when *kFieldTask == 0 or its work's s16 +484 is 0; else 0 (wait)
u32 sub_2D1560(EEContext& ctx);  // [429, 0] leaf: return 1
void sub_2D0EF0_regs(EEContext& ctx);  // [register ABI] [435, 6] f32 args 0..2 -> kBattleFloatsA +0/+4/+8, args 3..5 -> -0x20/-0x1C/-0x18
void sub_2D0F90_regs(EEContext& ctx);  // [register ABI] [436, 6] the same at kBattleFloatsB
void sub_2CD9C0_regs(EEContext& ctx);  // [register ABI] [493, 2] user->u16[+128] = arg0, user->u8[+130] = arg1

// --- one or two g_data / battle callees ----------------------------------------------------------------
void sub_1C3C40_regs(EEContext& ctx);  // [register ABI] [276, 1] return sub_16F380(arg0) [the counter kCounters[arg0]]
void sub_1C3C80_regs(EEContext& ctx);  // [register ABI] [277, 2] sub_16F3E0(arg0, arg1) [set counter arg0]
void sub_1C2FF0_regs(EEContext& ctx);  // [register ABI] [279, 2] sub_16CF40((s16)arg0, (s16)arg1) [a character's u16 at +0 of its 868-byte record]
void sub_1C30F0_regs(EEContext& ctx);  // [register ABI] [280, 2] sub_16CF90((s16)arg0, (s16)arg1)
void sub_1C3590_regs(EEContext& ctx);  // [register ABI] [282, 2] return sub_170760((s16)arg0, (s16)arg1) & 0xFFFF
void sub_1C3600_regs(EEContext& ctx);  // [register ABI] [283, 3] sub_170860((s16)arg0, (s16)arg1, min(arg2, 99) & 0xFFFF)
void clndScrCmd_TIME_SKIP_regs(EEContext& ctx);  // [register ABI] [295, 1] t = datGetTime() + arg0; while t >= 9: t -= 9, days++; skip targets (today + days, t, 1)
void sub_1C4D10_regs(EEContext& ctx);  // [register ABI] [339, 2] return sub_177A40(arg0 & 0xFFFF, arg1) != 0
void sub_1C4D90_regs(EEContext& ctx);  // [register ABI] [340, 2] return sub_177A90(arg0 & 0xFFFF, arg1)->u8[+8]
void sub_1C4DF0_regs(EEContext& ctx);  // [register ABI] [341, 2] return sub_177A90(arg0 & 0xFFFF, arg1)->u16[+0]
void sub_17F990_regs(EEContext& ctx);  // [register ABI] [396, 0] *kCalendarTask's work: The Answer -> +8 = 60, +0 = 8; The Journey -> +32 = 60, +0 = 24
void sub_1C58D0_regs(EEContext& ctx);  // [register ABI] [398, 0] return clndGetCurrentMoonPhase() & 0xFF
void sub_1C5E60_regs(EEContext& ctx);  // [register ABI] [489, 0] return sub_17D800() == 1 [scenario is The Answer]
void sub_27D840_regs(EEContext& ctx);  // [register ABI] [451, 0] done (sub_2FF310() != 0) once the command timer is > 0; 0 on the first frame
void sub_2CE4E0_regs(EEContext& ctx);  // [register ABI] [255, 0] the living unit (flags 1|8, side byte == 1) with the lowest HP: its id | 0x80000000
void sub_2CFA40_regs(EEContext& ctx);  // [register ABI] [320, 0] the same for side byte == 0
void sub_1C3270_regs(EEContext& ctx);  // [register ABI] [483, 2] arg1 0/1/2: academic/charm/courage level of character arg0's points; other -> 0
void sub_2D1490_regs(EEContext& ctx);  // [register ABI] [307, 1] return datCalcRand(arg0)
void sub_17FD30_regs(EEContext& ctx);  // [register ABI] [494, 0] for characters 2..10, slots 0..11: the s16 pair of kSkillRowTable row -> sub_170620(c, s)

}  // namespace p3fes::game
