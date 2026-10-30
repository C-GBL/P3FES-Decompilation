// The battle code, eighth pass (slice battle8; docs/ANALYSIS/21_battle.md): 62 functions of 0x2E4A40..0x2F0000, the
// boss fights' camera shots and their scripted events. game/src/battle/battle8.cpp; the bodies come from p3fes_handgen
// (register ABI: arguments in $a0.., the result in $v0), with the record offsets named (battle3.h's b3::, battle4.h's
// b4::, battle5.h's b5::, battle7.h's b7::, battle_core2.h's bcore:: and the additions below) and each function's role
// given. Names: functions.json's in code; roles in the comments (ADR-0009).
//
// Chosen by the packet (F:\P3FES-PORT\lead\packets\battle8): no replay route reaches them (the boss fights are not on
// the six routes); they are the unreached siblings of the replaced battle bands, by caller count.
//
// Groups (by the tables that call them):
//   * camera shots (the shot callbacks' $a0 = a camera shot, b7::shot): sub_2E4A40 .. sub_2E8F40 -- target, attacker,
//     actor-and-target and boss-row shots, the boss shot dispatcher sub_2E82B0 and the look-point helper sub_2E6130;
//   * placement (sub_2FA240's table, no arguments): the party and the boss units at fixed points at the battle start
//     (the cell through sub_2D2280, the position through sub_27F650, the formation slot);
//   * opening shots (sub_2FACC0's table) and boss talks (sub_2FB690's table): a camera sequence (sub_2B8F90 + the
//     script sub_2F87E0(n)), the event voice file (E1A0_99.ADX .. E1A8_99.ADX through sub_2DD690), the boss motion 18
//     and the packets chained on it (start condition kind 4 + the motion packet's id: bcore::kCondKind / kCondArg);
//   * event packets (data refs): the boss talk packets owned by an action and their updates (wait for the action's
//     packets, then the kill, the colour fades), the form change of enemies 261 / 262 / 277, the call packets that flip
//     gBtl +2896 / +2900, the action start hooks (sub_2F9C10's table) and the boss event state machines (gBtl
//     +2902 / +2904).
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h .. battle7.h's lists)
//   * the kills of the talk packets (sub_2D7890 after the talk), the form change's HP hand-over (datCalcSetHp) and the
//     status changes of the call packets (status 0x100000) change DatUnits: server logic;
//   * the boss event states (gBtl +2902 / +2904, the picks +2912 / +2914) choose the boss's next command (sub_2ED360
//     sets kind 2 with the picked skill): server logic;
//   * the camera shots draw from datCalcRand (sub_2E5060, sub_2E7890, sub_2E8E20 / sub_2E8F40): presentation, but the
//     draws share the battle's random stream, so clients must agree on which shots run.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"
#include "p3fes/game/battle7.h"
#include "p3fes/game/battle_core2.h"

namespace p3fes::game {

namespace b8 {

// --- gBtl additions (b3::gbtl, b4::gbtl4, b5::gbtl5, b7::gbtl7) --------------------------------------------------------
namespace gbtl8 {
inline constexpr s32 kUnitTail1 = 344;      // u32: tail of side 1's (the enemies') btlUnit list (+2612 prev; b3 kUnitTail0 + 8)
inline constexpr s32 kEvState = 2902;       // u16: the boss event state of sub_2ECF80 (3 = follow and pick)
inline constexpr s32 kEvState2 = 2904;      // u16: the boss event state of sub_2ED360 (2 = run sub_2ED360's command step)
inline constexpr s32 kEvTimer = 2908;       // f32: the event's timer (counts down by the $gp step; sub_2EF5A0 zeroes it)
inline constexpr s32 kEvPick = 2912;        // s16: the picked node / skill (-1 none; sub_2ECC60's first output)
inline constexpr s32 kEvPick2 = 2914;       // s16: the second pick
inline constexpr s32 kShotSerial = 2940;    // u32: the serial (act +8) of the action the boss target shot last framed
inline constexpr s32 kShotCut = 2944;       // u32: 1 once that shot cut
}  // namespace gbtl8

// --- a camera shot's additions (b7::shot) -------------------------------------------------------------------------------
namespace shot8 {
inline constexpr s32 kKind = 272;           // u16: sub_2A7830's shot kind (0..4; 1 skips the child unit's motion)
}  // namespace shot8

// The enemy genus (gBtl +3004): +8 the encounter id (436 hands some shots to sub_2F6330 / sub_2F6510).
inline constexpr s32 kGenusEncounter = 8;

}  // namespace b8

void sub_2E4A40(EEContext& ctx);  // 0x2E4A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E4F50(EEContext& ctx);  // 0x2E4F50 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E5060(EEContext& ctx);  // 0x2E5060 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E58A0(EEContext& ctx);  // 0x2E58A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E6130(EEContext& ctx);  // 0x2E6130 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E7210(EEContext& ctx);  // 0x2E7210 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E7330(EEContext& ctx);  // 0x2E7330 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E7890(EEContext& ctx);  // 0x2E7890 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E7DB0(EEContext& ctx);  // 0x2E7DB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E82B0(EEContext& ctx);  // 0x2E82B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E8820(EEContext& ctx);  // 0x2E8820 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E8A40(EEContext& ctx);  // 0x2E8A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E8E20(EEContext& ctx);  // 0x2E8E20 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E8F40(EEContext& ctx);  // 0x2E8F40 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9170(EEContext& ctx);  // 0x2E9170 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E92C0(EEContext& ctx);  // 0x2E92C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9450(EEContext& ctx);  // 0x2E9450 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E95F0(EEContext& ctx);  // 0x2E95F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9950(EEContext& ctx);  // 0x2E9950 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9AC0(EEContext& ctx);  // 0x2E9AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9C20(EEContext& ctx);  // 0x2E9C20 (register ABI: arguments in $a0.., the result in $v0)
void sub_2E9F10(EEContext& ctx);  // 0x2E9F10 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA060(EEContext& ctx);  // 0x2EA060 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA210(EEContext& ctx);  // 0x2EA210 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA400(EEContext& ctx);  // 0x2EA400 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA590(EEContext& ctx);  // 0x2EA590 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA780(EEContext& ctx);  // 0x2EA780 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EA860(EEContext& ctx);  // 0x2EA860 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EAB70(EEContext& ctx);  // 0x2EAB70 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EABB0(EEContext& ctx);  // 0x2EABB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EABF0(EEContext& ctx);  // 0x2EABF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EB250(EEContext& ctx);  // 0x2EB250 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EB2C0(EEContext& ctx);  // 0x2EB2C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EB9E0(EEContext& ctx);  // 0x2EB9E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EBA50(EEContext& ctx);  // 0x2EBA50 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EBEC0(EEContext& ctx);  // 0x2EBEC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EC000(EEContext& ctx);  // 0x2EC000 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EC2C0(EEContext& ctx);  // 0x2EC2C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EC5C0(EEContext& ctx);  // 0x2EC5C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EC790(EEContext& ctx);  // 0x2EC790 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EC990(EEContext& ctx);  // 0x2EC990 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ECB30(EEContext& ctx);  // 0x2ECB30 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ECBE0(EEContext& ctx);  // 0x2ECBE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ECC20(EEContext& ctx);  // 0x2ECC20 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ECC60(EEContext& ctx);  // 0x2ECC60 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ECF80(EEContext& ctx);  // 0x2ECF80 (register ABI: arguments in $a0.., the result in $v0)
void sub_2ED360(EEContext& ctx);  // 0x2ED360 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EE640(EEContext& ctx);  // 0x2EE640 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EEA10(EEContext& ctx);  // 0x2EEA10 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EEB70(EEContext& ctx);  // 0x2EEB70 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EEC60(EEContext& ctx);  // 0x2EEC60 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF000(EEContext& ctx);  // 0x2EF000 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF250(EEContext& ctx);  // 0x2EF250 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF360(EEContext& ctx);  // 0x2EF360 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF5A0(EEContext& ctx);  // 0x2EF5A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF670(EEContext& ctx);  // 0x2EF670 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EF7E0(EEContext& ctx);  // 0x2EF7E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EFC90(EEContext& ctx);  // 0x2EFC90 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EFCD0(EEContext& ctx);  // 0x2EFCD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EFD20(EEContext& ctx);  // 0x2EFD20 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EFDB0(EEContext& ctx);  // 0x2EFDB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2EFE50(EEContext& ctx);  // 0x2EFE50 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
