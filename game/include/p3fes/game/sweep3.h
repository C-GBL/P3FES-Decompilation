// Slice sweep3 (game/src/battle/sweep3.cpp): the last free game-code functions below the RenderWare band -- eight
// btlAction state bodies, nine battle camera shots, the gBtl+400 record release (the flag-gated call sub_2DCE90 stays recompiled: test_battle9.cpp stands it in). Register-ABI bodies
// (arguments in $a0.., the result in $v0), written by p3fes_handgen and made readable on top (role comments, named
// packet offsets); each equals its recompiled body (tests/game/test_sweep3.cpp, the faithfulness audit).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace sw3 {
// btl packet fields the action-state bodies write (the values of battle_actions.h's kPkt*, as the s32 offsets of the
// hg_cpu.h memory ops). A packet comes back from its constructor in $v0 and goes to sub_27ED20(packet, queue).
inline constexpr s32 kPktWaitKind0 = 0;  // u8: first dependency kind (4 / 5 / 11)
inline constexpr s32 kPktWaitId0 = 8;    // u64: the id of the packet waited for
inline constexpr s32 kPktWaitKind1 = 16; // u8: second dependency kind
inline constexpr s32 kPktWaitId1 = 24;   // u64
inline constexpr s32 kPktTime = 72;      // u16: a frame / ordering word
inline constexpr s32 kPktId = 88;        // u64: the packet's own id (what a later packet waits for)
inline constexpr s32 kPktOwner = 96;     // u64: the uid (+0) of the btlAction the packet belongs to
}  // namespace sw3

void sub_294D40(EEContext& ctx);  // 0x294D40 (register ABI: arguments in $a0.., the result in $v0)
void sub_295160(EEContext& ctx);  // 0x295160 (register ABI: arguments in $a0.., the result in $v0)
void sub_295A10(EEContext& ctx);  // 0x295A10 (register ABI: arguments in $a0.., the result in $v0)
void sub_295C00(EEContext& ctx);  // 0x295C00 (register ABI: arguments in $a0.., the result in $v0)
void sub_295FA0(EEContext& ctx);  // 0x295FA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2964F0(EEContext& ctx);  // 0x2964F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_296660(EEContext& ctx);  // 0x296660 (register ABI: arguments in $a0.., the result in $v0)
void sub_297760(EEContext& ctx);  // 0x297760 (register ABI: arguments in $a0.., the result in $v0)
void sub_2A6EE0(EEContext& ctx);  // 0x2A6EE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B1BC0(EEContext& ctx);  // 0x2B1BC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B47B0(EEContext& ctx);  // 0x2B47B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B4C00(EEContext& ctx);  // 0x2B4C00 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B5000(EEContext& ctx);  // 0x2B5000 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B5240(EEContext& ctx);  // 0x2B5240 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B56E0(EEContext& ctx);  // 0x2B56E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B5CD0(EEContext& ctx);  // 0x2B5CD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_2B6070(EEContext& ctx);  // 0x2B6070 (register ABI: arguments in $a0.., the result in $v0)
void sub_2BB610(EEContext& ctx);  // 0x2BB610 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
