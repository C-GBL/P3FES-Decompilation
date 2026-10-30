// Slice finalB (the final wave, 2026-10-29): the 15 functions other tests had held as "stays recompiled" -- the debug-log
// ring formatter, the fclBankManager request logger, the facility panel mover, the message-tag scene call, a fusion
// list creator, newlib's printf, two CRI thunks, the tween stepper, the battle-panel resource release, the death-scene
// sound trigger, the animation slot update and the three RpPTank scratchpad streamers (game/src/fx/finalB.cpp).
// p3fes_handgen bodies (register ABI: arguments in $a0.., the result in $v0) with a role comment each and the layouts
// below named from the bodies' own loads and stores.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace finalB {

// --- sub_1052B0: the debug-log ring ($gp - 20012 = 0x7CDEC4 count byte, 0x7E0A30 lines) -------------------------------
inline constexpr s32 kGpLogCount = -20012;    // 0x7CDEC4: s8 count of the lines held (0..15)
inline constexpr u32 kLogRing = 0x7E0A30u;    // 15 lines of 256 bytes
inline constexpr s32 kLogLine = 256;
inline constexpr s32 kLogLines = 15;          // a full ring drops its oldest line before the new one is appended

// --- sub_18B700: the tween record (type_197, 0x44 bytes) ------------------------------------------------------------
namespace tween {
inline constexpr s32 kActive = 4;   // 0: the step returns 0 at once
inline constexpr s32 kKind = 8;     // 0: sub_18BB20 (the linear tween), 1: sub_18BB80, else the step returns 0
inline constexpr s32 kFrame = 24;   // stepped by one while below kLimit
inline constexpr s32 kLast = 28;    // the step returns 0 while kFrame < kLast
inline constexpr s32 kLimit = 32;   // kFrame never passes it
}  // namespace tween

// --- sub_21BB60: the battle-panel resource work (bp_res.c, *(u32*)($gp - 18924) = 0x7CE304) ---------------------------
namespace bpres {
inline constexpr s32 kGpWork = -18924;  // 0x7CE304: the work, null when nothing is loaded (bp_res.c:89 asserts)
inline constexpr s32 kFlags = 4;        // bit 0: the seven rasters at kRasters and the six RW blocks at kBlocks are live;
                                        // bits 4..6: the rasters at kRaster4..6; bit 7: nullsub_11; bit 8: sub_21C930
inline constexpr s32 kRasters = 16;     // 7 raster handles (sub_21CC20 releases each)
inline constexpr s32 kRasterCount = 7;
inline constexpr s32 kRaster4 = 56, kRaster5 = 60, kRaster6 = 64;
inline constexpr s32 kBlocks = 84;      // 6 blocks freed through the RwFree slot (0x96017C)
inline constexpr s32 kBlockCount = 6;
}  // namespace bpres

// --- sub_313490: the animation slot (type_232) ----------------------------------------------------------------------
namespace aslot {
inline constexpr s32 kFlags = 0;        // u16: bit 1 forces a step, bit 2 (cleared by the step) forces it once, bit 4 sub_312D40
inline constexpr s32 kKind = 2;         // u8: 1 = only the hierarchy update (sub_466EF0 on the pointer at kClump)
inline constexpr s32 kNode = 4;         // s16: the hierarchy node; negative = an idle slot (returns $a1)
inline constexpr s32 kRate = 8;         // f32: multiplied by the frame delta (0x7CADD4)
inline constexpr s32 kTime = 12;        // f32: advanced by the speed once the blend is complete
inline constexpr s32 kPrevNode = 16;    // s16
inline constexpr s32 kBlendSteps = 24;  // u16: the blend advances by 1 / steps per step
inline constexpr s32 kBlend = 28;       // f32: < 1.0 while blending
inline constexpr s32 kClump = 32;       // the object whose +32 is the RpHAnim hierarchy
inline constexpr s32 kTable = 44;       // the node table (+4 u16 count, +0 -> 80-byte records with a pointer at +64)
inline constexpr s32 kAnimFlags = 76;   // u16: 0x1E0 selects sub_311730, bit 14 marks it applied
inline constexpr u32 kFrameDelta = 0x7CADD4u;  // f32 ($gp - 1612)
}  // namespace aslot

// --- the CRI handle field sub_54D220 sets -----------------------------------------------------------------------------
inline constexpr s32 kCriHandleSlot168 = 168;

// --- the RpPTank scratchpad streamers (sub_476140 / sub_476720 / sub_476C20): DMAC channels 8 (fromSPR) and 9 (toSPR) ---
inline constexpr u32 kD8Chcr = 0x1000D000u, kD8Madr = 0x1000D010u, kD8Qwc = 0x1000D020u, kD8Sadr = 0x1000D080u;
inline constexpr u32 kD9Chcr = 0x1000D400u, kD9Madr = 0x1000D410u, kD9Qwc = 0x1000D420u, kD9Sadr = 0x1000D480u;
inline constexpr u32 kDStat = 0x1000E010u, kDEnableW = 0x1000E020u;
inline constexpr u32 kSprBase = 0x70000000u;  // the scratchpad window the fills stage their quadwords in
inline constexpr u32 kChunkQw = 1024;         // one DMA burst: 1024 quadwords (16 KiB)

}  // namespace finalB

void sub_1052B0(EEContext& ctx);  // 0x1052B0 the debug-log ring formatter (fmt, ...) -> the line
void sub_343B60(EEContext& ctx);  // 0x343B60 fusion list creator (work, raster) -> the list block
void sub_3B93C0(EEContext& ctx);  // 0x3B93C0 message-tag scene call (id, a, b, c, d) -> the last call's result
void sub_3CF160(EEContext& ctx);  // 0x3CF160 fclBankManager request logger (packed id, arg) -> 0 / 1
void sub_3E0C20(EEContext& ctx);  // 0x3E0C20 facility panel mover (panel, kind 0..17, mode)
void printf(EEContext& ctx);      // 0x5225A8 newlib printf(fmt, ...) -> chars written
void atan2l_4(EEContext& ctx);    // 0x54D100 CRI thunk (IDA's FLIRT name): tail call to sub_532F60
void sub_54D220(EEContext& ctx);  // 0x54D220 CRI handle setter: *(handle + 168) = value
void sub_18B700(EEContext& ctx);  // 0x18B700 tween stepper (record) -> 0 or the kind's step result
void sub_21BB60(EEContext& ctx);  // 0x21BB60 battle-panel resource release (bp_res.c)
void sub_2DCE90(EEContext& ctx);  // 0x2DCE90 death-scene sound trigger (gBtl flag 0x40 -> sub_108F70)
void sub_313490(EEContext& ctx);  // 0x313490 animation slot update (slot, other) -> slot or other
void sub_476140(EEContext& ctx);  // 0x476140 RpPTank scratchpad word fill (dst, bytes, word)
void sub_476720(EEContext& ctx);  // 0x476720 RpPTank scratchpad quadword-pattern fill (dst, bytes, pattern)
void sub_476C20(EEContext& ctx);  // 0x476C20 RpPTank scratchpad copy (dst, src, bytes)

}  // namespace p3fes::game
