// BF script COMM handlers, table indices 0-250 (slice script_comm_a): the pure handlers of sScrCommandTable
// 0x7B92B0 (502 x {fn, argc}, docs/ANALYSIS/18_script_vm.md section 2.4) hand-decompiled from SLUS_216.21.
// A handler reads its arguments in place through scrGetIntPara (argument i = slot sp - 1 - i), computes, touches
// game state in guest RAM (the party list, the money word, calendar, social-stat and persona data, the dungeon
// floor record) and leaves its result through scrSetIntReturnVal / scrSetFloatReturnVal; its own return value is
// 1 ("done", CodeFunc_Comm drops the arguments and advances the pc) or 0 ("not yet", re-run next frame).
//
// Names are the IDA names of symbols/functions.json (all still sub_*); the comment of each gives its COMM index,
// argc and what it does; proposed names are given in brackets (our own, from the behaviour; not imported).
// Every handler is referenced only by the COMM table (no direct jal in the ELF), so its only caller is
// CodeFunc_Comm's jalr, which reads $v0 alone.
//
// Not replaced from indices 0-250 (PHASE5_AGENT_BRIEF step 7 and the slice rules) -- see comm_a.cpp's header.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace comm_a {
// Guest words the handlers read and write ($gp = 0x7D2CF0).
inline constexpr u32 kMoney = 0x83A6DCu;          // s32: the money counter, kept below 10,000,000 (asserted)
inline constexpr u32 kParty = 0x83A6E0u;          // s16[4]: the party member ids (0 = empty slot)
inline constexpr u32 kPartyAddMax = 3;            // sub_16EA80 looks at the first three slots
inline constexpr u32 kPartyCount = 4;
inline constexpr u32 kFieldPtr = 0x7CE284u;       // u32 ($gp - 19052): the field/dungeon work record
inline constexpr u32 kFieldFloorPtr = 284;        //   +284: u32 pointer to the floor record (u16 +2 floor id, u8 +6)
inline constexpr u32 kFieldFloorBase = 288;       //   +288: handed to sub_1831E0
inline constexpr u32 kEventCfgPtr = 0x7CE6A8u;    // u32 ($gp - 17992): six config bytes +0..5, +8, +9, +10
inline constexpr u32 kEventCfgDirty = 0x7CE6B0u;  // u8 ($gp - 17984)
inline constexpr u32 kSocialCtxPtr = 0x7CE5B8u;   // u32 ($gp - 18232): words +16 + 4*i (i < 3)
inline constexpr u32 kSocialCtxArg = 0x7CE5B4u;   // u32 ($gp - 18236): first argument of sub_172E50
inline constexpr u32 kSeqRecord = 0x957BC0u;      // sub_350190's record: s32 +0, s16 +4, s32 +8, s32 +12
inline constexpr u32 kSeqWord0 = 0x7CE574u;       // s32 ($gp - 18300), cleared by sub_350190
inline constexpr u32 kSeqWord1 = 0x7CE578u;       // s32 ($gp - 18296), set to 1 by sub_350190
inline constexpr u32 kPersonaIds6 = 0x69D518u;    // .rodata s16[6]: the candidates of sub_35F210
inline constexpr u32 kPersonaIds4 = 0x7CCA60u;    // .sdata s16[4] ($gp - 25232): the candidates of sub_35F360
inline constexpr u32 kMoneyLimit = 10000000;
// K_Assert file arguments (.rodata strings).
inline constexpr u32 kFileDatMisc = 0x5E3098u;    // the money functions' source file
inline constexpr u32 kFileScrCommand = 0x69D530u; // the 0x35F/0x360 band's source file
inline constexpr u32 kFileFieldCommand = 0x683660u;
}  // namespace comm_a

// Each returns the handler's result (1 = done, 0 = run again next frame). [index] argc in the comments.
u32 sub_1C2500(EEContext& ctx);  // [121] 2: sub_1A0150(u16 arg0, arg1): set/clear bit 1 of +40 of the object with id arg0
u32 sub_1C2610(EEContext& ctx);  // [14]  2: sub_108570(); sub_108670((s16)arg0); arg1 != 0 -> sub_1086A0((s16)arg1)
u32 sub_1C2690(EEContext& ctx);  // [127] 0: done when sub_108710() != 0 (blocks until it reports ready)
u32 sub_1C26C0(EEContext& ctx);  // [128] 0: return clndGetCurrentMonth()
u32 sub_1C26F0(EEContext& ctx);  // [129] 0: return clndGetCurrentDay()
u32 sub_1C2720(EEContext& ctx);  // [130] 0: return clndGetCurrentWeekDay()
u32 sub_1C2750(EEContext& ctx);  // [131] 0: return datGetTime() & 0xFF
u32 sub_1C2780(EEContext& ctx);  // [132] 4: return clndIsDateInRange(arg0..arg3) == 1
void sub_16EA80_regs(EEContext& ctx);  // [register ABI] [133] 2: add party member arg1 (first empty of slots 0-2, else slot 2) [datPartyAdd]
void sub_16EC40_regs(EEContext& ctx);  // [register ABI] [134] 1: party slot arg0 := 0
u32 sub_1C2830(EEContext& ctx);  // [135] 4: sub_103C30((s16)arg0..(s16)arg3)
u32 sub_1C28D0(EEContext& ctx);  // [136] 0: sub_103CB0()
u32 sub_1C2EA0(EEContext& ctx);  // [138] 0: return K_FldDungeon_GetCurrentFloor()
u32 sub_3111C0(EEContext& ctx);  // [48]  0: return 1 (int)
u32 sub_30FDC0(EEContext& ctx);  // [50]  2: return 0.0f (float; the two arguments are not read)
void sub_350190_regs(EEContext& ctx);  // [register ABI] [145] 2: record := {arg0, (s16)arg1, 0, 0}; word0 := 0; word1 := 1
u32 sub_3112E0(EEContext& ctx);  // [147] 0: datCalcRestorePartyAll()
void sub_4243D0_regs(EEContext& ctx);  // [register ABI] [189] 6: cfg[0..5] := (u8)arg0..arg5; dirty := 0
u32 sub_424470(EEContext& ctx);  // [190] 0: dirty := 1 (leaf)
u32 sub_424480(EEContext& ctx);  // [191] 0: done when (s8)cfg[8] == 1 (leaf)
void sub_4244A0_regs(EEContext& ctx);  // [register ABI] [206] 1: cfg[10] := (u8)arg0; cfg[9] := 1
u32 sub_1C2ED0(EEContext& ctx);  // [192] 1: return sub_16C470((s16)arg0) & 0xFF   [party member level]
u32 sub_1C2FA0(EEContext& ctx);  // [193] 1: return sub_16C4F0((s16)arg0) & 0xFFFF [HP]
u32 sub_1C3050(EEContext& ctx);  // [194] 1: return sub_16C5F0((s16)arg0) & 0xFFFF [max HP]
u32 sub_1C30A0(EEContext& ctx);  // [195] 1: return sub_16C570((s16)arg0) & 0xFFFF [SP]
u32 sub_1C3150(EEContext& ctx);  // [196] 1: return sub_16C670((s16)arg0) & 0xFFFF [max SP]
void sub_1C31A0_regs(EEContext& ctx);  // [register ABI] [197] 2: return the academic (0) / charm (1) / courage (2) points of arg0, else 0
u32 sub_1C3370(EEContext& ctx);  // [198] 1: return sub_16C9F0((s16)arg0) & 0xFFFF
u32 sub_1C33C0(EEContext& ctx);  // [199] 1: return sub_16CA40((s16)arg0) & 0xFFFF
u32 sub_1C3410(EEContext& ctx);  // [200] 1: return sub_16C7E0((s16)arg0)
u32 sub_1C3460(EEContext& ctx);  // [201] 1: return sub_16C920((s16)arg0) & 0xFFFF
void sub_1C34B0_regs(EEContext& ctx);  // [register ABI] [202] 2: return sub_16C920((s16)arg0) & 0xFFFF; then sub_16D6B0((s16)arg0, (u16)arg1)
u32 sub_1C3540(EEContext& ctx);  // [203] 1: return sub_16C970((s16)arg0)
u32 sub_1C3690(EEContext& ctx);  // [204] 2: return the item id of equipment slot arg1 of arg0 (sub_16F630 of datGetEquipmentIdx)
u32 sub_1C3710(EEContext& ctx);  // [205] 3: sub_16DA50((s16)arg0, (s16)arg1, (s16)arg2)
void sub_35FBD0_regs(EEContext& ctx);  // [register ABI] [208] 2: assert arg0 < 5; sub_174710((u16)sub_175360(), (u16)arg0, (s8)arg1)
void sub_16EDD0_regs(EEContext& ctx);  // [register ABI] [209] 0: return money [datGetMoney]
void sub_16EE00_regs(EEContext& ctx);  // [register ABI] [210] 1: money += arg0, clamped at 9,999,999 [datAddMoney]
void sub_16EE90_regs(EEContext& ctx);  // [register ABI] [211] 1: money -= arg0, 0 when money < arg0 [datSubMoney]
void sub_16EC80_regs(EEContext& ctx);  // [register ABI] [212] 1: return party slot arg0
void sub_16ECD0_regs(EEContext& ctx);  // [register ABI] [213] 1: remove member arg0 from the party and close the gap [datPartyRemove]
u32 sub_1C3790(EEContext& ctx);  // [215] 0: return K_Fld_GetPhase()
void sub_1C3880_regs(EEContext& ctx);  // [register ABI] [226] 0: return u16 field +8
void sub_1C38B0_regs(EEContext& ctx);  // [register ABI] [227] 0: floor id: 4021 -> 3; >= 5000 -> 0; >= 4000 -> 1; else 2
void sub_1C39E0_regs(EEContext& ctx);  // [register ABI] [228] 0: return the floor id (u16 floor +2)
void sub_1C3A70_regs(EEContext& ctx);  // [register ABI] [229] 0: the same as [228] (a second, identical function)
void sub_1C3AA0_regs(EEContext& ctx);  // [register ABI] [230] 0: return u8 floor +6
void sub_1C3B00_regs(EEContext& ctx);  // [register ABI] [232] 0: per floor id: sub_1831E0 / sub_170760 + sub_170860 update; return 1
u32 sub_35F1B0(EEContext& ctx);  // [124] 1: return sub_16E100((s16)arg0) == 1
void sub_35F210_regs(EEContext& ctx);  // [register ABI] [186] 0: 1 + index of the best of six candidates (sub_16DBA0), 0 when none
void sub_35F360_regs(EEContext& ctx);  // [register ABI] [187] 0: the same over the four candidates at $gp - 25232
void sub_35FF80_regs(EEContext& ctx);  // [register ABI] [224] 1: assert ctx && 0 <= arg0 < 3; return ctx word +16 + 4*arg0
void sub_360020_regs(EEContext& ctx);  // [register ABI] [225] 1: assert ctx; sub_172E50(word, arg0, ctx word +16 + 4*arg0)
u32 sub_360280(EEContext& ctx);  // [218] 1: assert sub_16DCE0(arg0); return (s8)sub_16DBA0((s16)arg0)
u32 sub_360300(EEContext& ctx);  // [219] 1: assert sub_16DCE0(arg0); return sub_16E100(arg0) && sub_1717C0(arg0) == 1
u32 sub_3603D0(EEContext& ctx);  // [220] 1: the same with sub_172160

}  // namespace p3fes::game
