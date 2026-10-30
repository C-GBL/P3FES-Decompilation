// Phase 5 slice unblock (game/src/unblock/unblock_*.cpp): functions other slices' pair tests used to stand in with
// recorders, freed by rewriting those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Every function
// keeps the register ABI of its recompiled original (arguments in $a0.. / $f12.., the result in $v0 / $f0); the role of
// each is in its source file.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace ub {
// RenderWare's memory-function slots (0x960178 + offset, the low half of the address the bodies load through 0x960000).
constexpr s32 kRwSlotFree = 380;    // 0x96017C: RwFree(ptr)
constexpr s32 kRwSlotCalloc = 388;  // 0x960184: RwCalloc(count, size, hint)

// The sprite handle (52 bytes, sprCreateHandle): a node of the global handle list (gp-19892 = 0x7CDF3C) or of a parent.
namespace spr {
constexpr s32 kNext = 0;      // u32: the next handle
constexpr s32 kPrev = 4;      // u32: the previous handle (0: the list head is gp-19892)
constexpr s32 kFile = 8;      // u32: the sprite file
constexpr s32 kSprite = 12;   // s32: the sprite index in the file
constexpr s32 kX = 16;        // f32: position
constexpr s32 kY = 20;        // f32
constexpr s32 kColour = 24;   // u8: the colour / alpha byte the drawers pass first
constexpr s32 kScaleX = 40;   // s16: scale, 0x1000 = 1.0
constexpr s32 kScaleY = 42;   // s16
constexpr s32 kDepth = 44;    // f32
constexpr s32 kRgb = 48;      // u8[3]: the colour bytes (0xFF each when created)
constexpr s32 kSize = 52;
constexpr s32 kGpHandleList = -19892;  // 0x7CDF3C: the global list head
}  // namespace spr
}  // namespace ub

void H_Cursor_CreateTask(EEContext& ctx);  // 0x1005B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_103C30(EEContext& ctx);  // 0x103C30 (register ABI: arguments in $a0.., the result in $v0)
void sub_103CB0(EEContext& ctx);  // 0x103CB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_104D10(EEContext& ctx);  // 0x104D10 (register ABI: arguments in $a0.., the result in $v0)
void sub_1071B0(EEContext& ctx);  // 0x1071B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_108570(EEContext& ctx);  // 0x108570 (register ABI: arguments in $a0.., the result in $v0)
void sub_1085C0(EEContext& ctx);  // 0x1085C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_108670(EEContext& ctx);  // 0x108670 (register ABI: arguments in $a0.., the result in $v0)
void sub_1086A0(EEContext& ctx);  // 0x1086A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1086D0(EEContext& ctx);  // 0x1086D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_108710(EEContext& ctx);  // 0x108710 (register ABI: arguments in $a0.., the result in $v0)
void sub_10A4E0(EEContext& ctx);  // 0x10A4E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_10A770(EEContext& ctx);  // 0x10A770 (register ABI: arguments in $a0.., the result in $v0)
void sub_10BC20(EEContext& ctx);  // 0x10BC20 (register ABI: arguments in $a0.., the result in $v0)
void sub_10BDA0(EEContext& ctx);  // 0x10BDA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_110F80(EEContext& ctx);  // 0x110F80 (register ABI: arguments in $a0.., the result in $v0)
void sub_1114B0(EEContext& ctx);  // 0x1114B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_111500(EEContext& ctx);  // 0x111500 (register ABI: arguments in $a0.., the result in $v0)
void sub_111530(EEContext& ctx);  // 0x111530 (register ABI: arguments in $a0.., the result in $v0)
void sub_111580(EEContext& ctx);  // 0x111580 (register ABI: arguments in $a0.., the result in $v0)
void sub_111CA0(EEContext& ctx);  // 0x111CA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_111F00(EEContext& ctx);  // 0x111F00 (register ABI: arguments in $a0.., the result in $v0)
void sub_111F10(EEContext& ctx);  // 0x111F10 (register ABI: arguments in $a0.., the result in $v0)
void sprCreateHandle(EEContext& ctx);  // 0x1158B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_115980(EEContext& ctx);  // 0x115980 (register ABI: arguments in $a0.., the result in $v0)
void sub_115DE0(EEContext& ctx);  // 0x115DE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_16D2F0(EEContext& ctx);  // 0x16D2F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_16DBC0(EEContext& ctx);  // 0x16DBC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_250CF0(EEContext& ctx);  // 0x250CF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_25F570(EEContext& ctx);  // 0x25F570 (register ABI: arguments in $a0.., the result in $v0)
void sub_2FF260(EEContext& ctx);  // 0x2FF260 (register ABI: arguments in $a0.., the result in $v0)
void sub_3580B0(EEContext& ctx);  // 0x3580B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_37CF50(EEContext& ctx);  // 0x37CF50 (register ABI: arguments in $a0.., the result in $v0)
void sub_3B32D0(EEContext& ctx);  // 0x3B32D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C7850(EEContext& ctx);  // 0x3C7850 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C7C90(EEContext& ctx);  // 0x3C7C90 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C83B0(EEContext& ctx);  // 0x3C83B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF120(EEContext& ctx);  // 0x3CF120 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF3A0(EEContext& ctx);  // 0x3CF3A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF440(EEContext& ctx);  // 0x3CF440 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF5D0(EEContext& ctx);  // 0x3CF5D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3EB9B0(EEContext& ctx);  // 0x3EB9B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3EC030(EEContext& ctx);  // 0x3EC030 (register ABI: arguments in $a0.., the result in $v0)
void sub_3ED380(EEContext& ctx);  // 0x3ED380 (register ABI: arguments in $a0.., the result in $v0)
void sub_3EE670(EEContext& ctx);  // 0x3EE670 (register ABI: arguments in $a0.., the result in $v0)
void sub_3EED50(EEContext& ctx);  // 0x3EED50 (register ABI: arguments in $a0.., the result in $v0)
void sub_3EF970(EEContext& ctx);  // 0x3EF970 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F00B0(EEContext& ctx);  // 0x3F00B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F04F0(EEContext& ctx);  // 0x3F04F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F0AC0(EEContext& ctx);  // 0x3F0AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F0EC0(EEContext& ctx);  // 0x3F0EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F12A0(EEContext& ctx);  // 0x3F12A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F1520(EEContext& ctx);  // 0x3F1520 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F1690(EEContext& ctx);  // 0x3F1690 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F5830(EEContext& ctx);  // 0x3F5830 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F9E30(EEContext& ctx);  // 0x3F9E30 (register ABI: arguments in $a0.., the result in $v0)
void sub_3FD8A0(EEContext& ctx);  // 0x3FD8A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3FDF80(EEContext& ctx);  // 0x3FDF80 (register ABI: arguments in $a0.., the result in $v0)
void sub_3FE2B0(EEContext& ctx);  // 0x3FE2B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4003F0(EEContext& ctx);  // 0x4003F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_400E90(EEContext& ctx);  // 0x400E90 (register ABI: arguments in $a0.., the result in $v0)
void sub_401890(EEContext& ctx);  // 0x401890 (register ABI: arguments in $a0.., the result in $v0)
void sub_401950(EEContext& ctx);  // 0x401950 (register ABI: arguments in $a0.., the result in $v0)
void sub_402480(EEContext& ctx);  // 0x402480 (register ABI: arguments in $a0.., the result in $v0)
void sub_403380(EEContext& ctx);  // 0x403380 (register ABI: arguments in $a0.., the result in $v0)
void sub_403520(EEContext& ctx);  // 0x403520 (register ABI: arguments in $a0.., the result in $v0)
void sub_403610(EEContext& ctx);  // 0x403610 (register ABI: arguments in $a0.., the result in $v0)
void sub_403740(EEContext& ctx);  // 0x403740 (register ABI: arguments in $a0.., the result in $v0)
void sub_403800(EEContext& ctx);  // 0x403800 (register ABI: arguments in $a0.., the result in $v0)
void sub_403830(EEContext& ctx);  // 0x403830 (register ABI: arguments in $a0.., the result in $v0)
void sub_403880(EEContext& ctx);  // 0x403880 (register ABI: arguments in $a0.., the result in $v0)
void sub_4038A0(EEContext& ctx);  // 0x4038A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_403900(EEContext& ctx);  // 0x403900 (register ABI: arguments in $a0.., the result in $v0)
void sub_403920(EEContext& ctx);  // 0x403920 (register ABI: arguments in $a0.., the result in $v0)
void sub_40C170(EEContext& ctx);  // 0x40C170 (register ABI: arguments in $a0.., the result in $v0)
void sub_40C310(EEContext& ctx);  // 0x40C310 (register ABI: arguments in $a0.., the result in $v0)
void sub_40C490(EEContext& ctx);  // 0x40C490 (register ABI: arguments in $a0.., the result in $v0)
void sub_434F70(EEContext& ctx);  // 0x434F70 (register ABI: arguments in $a0.., the result in $v0)
void sub_45EC00(EEContext& ctx);  // 0x45EC00 (register ABI: arguments in $a0.., the result in $v0)
void sub_469A90(EEContext& ctx);  // 0x469A90 (register ABI: arguments in $a0.., the result in $v0)
void sub_474210(EEContext& ctx);  // 0x474210 (register ABI: arguments in $a0.., the result in $v0)
void sub_474640(EEContext& ctx);  // 0x474640 (register ABI: arguments in $a0.., the result in $v0)
void sub_4747F0(EEContext& ctx);  // 0x4747F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_48D270(EEContext& ctx);  // 0x48D270 (register ABI: arguments in $a0.., the result in $v0)
void sub_491A80(EEContext& ctx);  // 0x491A80 (register ABI: arguments in $a0.., the result in $v0)
void sub_492D10(EEContext& ctx);  // 0x492D10 (register ABI: arguments in $a0.., the result in $v0)
void sub_494CC0(EEContext& ctx);  // 0x494CC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_494D50(EEContext& ctx);  // 0x494D50 (register ABI: arguments in $a0.., the result in $v0)
void sub_4CA030(EEContext& ctx);  // 0x4CA030 (register ABI: arguments in $a0.., the result in $v0)
void sub_4D0BE0(EEContext& ctx);  // 0x4D0BE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4D1840(EEContext& ctx);  // 0x4D1840 (register ABI: arguments in $a0.., the result in $v0)
void sub_4E3E40(EEContext& ctx);  // 0x4E3E40 (register ABI: arguments in $a0.., the result in $v0)
void sub_4E3EC0(EEContext& ctx);  // 0x4E3EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4E3F20(EEContext& ctx);  // 0x4E3F20 (register ABI: arguments in $a0.., the result in $v0)
void sub_4E3FC0(EEContext& ctx);  // 0x4E3FC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4E4020(EEContext& ctx);  // 0x4E4020 (register ABI: arguments in $a0.., the result in $v0)
void isinf(EEContext& ctx);  // 0x523730 (register ABI: arguments in $a0.., the result in $v0)
void isnan(EEContext& ctx);  // 0x523778 (register ABI: arguments in $a0.., the result in $v0)
void strncmp(EEContext& ctx);  // 0x524670 (register ABI: arguments in $a0.., the result in $v0)
void cos(EEContext& ctx);  // 0x52E038 (register ABI: arguments in $a0.., the result in $v0)
void fabs(EEContext& ctx);  // 0x52E118 (register ABI: arguments in $a0.., the result in $v0)
void sin(EEContext& ctx);  // 0x52E328 (register ABI: arguments in $a0.., the result in $v0)
void __fixunssfdi(EEContext& ctx);  // 0x52EDA0 (register ABI: arguments in $a0.., the result in $v0)
void fptodp(EEContext& ctx);  // 0x530DA0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
