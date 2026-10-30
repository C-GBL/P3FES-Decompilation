// libpad's EE-side readers (0x511988-0x512838): every reader takes the newest of the two 128-byte DMA frames padman
// writes for an open port / slot (through scePadGetDmaStr, still recompiled: it masks interrupts and syncs the cache)
// and decodes it -- the button data, the state and request state, the actuator / combination / mode tables and the
// pressure-button capability of a DualShock 2. The port / slot table is libs1::pad::kPortTable (0x96DD10).
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs1::pad {
constexpr u32 kPortTable = 0x96DD10u;  // per port 112 bytes, per slot 28: +0 the DMA area (two 128-byte frames), +16 open
constexpr s32 kPortStride = 112, kSlotStride = 28, kOpen = 16;
// a DMA frame (128 bytes; the newer of the two by the frame counter)
constexpr s32 kFrameCount = 88, kDataLen = 96, kMode = 100, kModeCur = 101, kPressCaps = 102, kModeCount = 104;
constexpr s32 kModeIndex = 105, kActCount = 106, kCombCount = 107, kState = 112, kReqState = 113, kExtMode = 114;
constexpr s32 kActTable = 48, kCombTable = 64, kModeTable = 80, kButtonMask = 121;
constexpr u32 kStateNames = 0x782758u, kReqNames = 0x782778u, kFlushRate = 0x782754u;
}  // namespace libs1::pad


// The frame counter of the newest DMA frame (+88) of an open port / slot; 0 when it is not open.
void scePadGetFrameCount(EEContext& ctx);  // 0x511988 (register ABI: arguments in $a0.., the result in $v0)
// Copy the newest pad data of an open port / slot (the DMA frame through scePadGetDmaStr into a stack copy, then its
// length (+96) bytes from it) to the caller's buffer; returns the length, 0 when the port is not open.
void scePadRead(EEContext& ctx);  // 0x5119E0 (register ABI: arguments in $a0.., the result in $v0)
// The pad state of a port / slot: 99 when it is not open, 5 ("stable") for a frame in state 6 with sub-state 2, else
// the frame's state byte (+112).
void scePadGetState(EEContext& ctx);  // 0x511A58 (register ABI: arguments in $a0.., the result in $v0)
// The name of a pad state 0..7 (the string table 0x782758) copied with strcpy; an empty string otherwise.
void scePadStateIntToStr(EEContext& ctx);  // 0x511AD0 (register ABI: arguments in $a0.., the result in $v0)
// The request state of an open port / slot (the newest frame's byte +113); 0 when not open.
void scePadGetReqState(EEContext& ctx);  // 0x511BC0 (register ABI: arguments in $a0.., the result in $v0)
// The name of a request state 0..3 (table 0x782778); an empty string otherwise.
void scePadReqIntToStr(EEContext& ctx);  // 0x511C18 (register ABI: arguments in $a0.., the result in $v0)
// Actuator information of a DualShock in extended mode (state byte +114 == 1, mode +100 >= 2): -1 asks for the
// actuator count (+106), 1..4 the actuator's four description bytes (+48.. + 4 x index); 0 otherwise.
void scePadInfoAct(EEContext& ctx);  // 0x511C50 (register ABI: arguments in $a0.., the result in $v0)
// Actuator combination information (count +107; -1 / 0 / 1 / 2 pick the bytes +64 / +65 / +66 / +67 of the entry); 0
// outside extended mode.
void scePadInfoComb(EEContext& ctx);  // 0x511D68 (register ABI: arguments in $a0.., the result in $v0)
// Mode information: 1 the current mode id (high nibble of +101, 0 for 0xF3), 2 / 3 / 4 the mode table (+80.., count
// +104, current index +105); 0 when the pad is not ready or in config mode.
void scePadInfoMode(EEContext& ctx);  // 0x511E80 (register ABI: arguments in $a0.., the result in $v0)
// The pressure-button mask of a DualShock 2 (+121..+124, little-endian) in extended mode with the pressure capability
// (+102 >= 2); 0 otherwise.
void scePadGetButtonMask(EEContext& ctx);  // 0x512210 (register ABI: arguments in $a0.., the result in $v0)
// 1 when the pad reports pressure-sensitive buttons (+102 bit 1) in extended mode, else 0.
void scePadInfoPressMode(EEContext& ctx);  // 0x512370 (register ABI: arguments in $a0.., the result in $v0)
// Turn the pressure-sensitive buttons on (scePadSetButtonInfo with the 12-button mask 0xFFF) for an open port; 0
// otherwise.
void scePadEnterPressMode(EEContext& ctx);  // 0x5123F0 (register ABI: arguments in $a0.., the result in $v0)
// Turn the pressure-sensitive buttons off (scePadSetButtonInfo with mask 0) for an open port; 0 otherwise.
void scePadExitPressMode(EEContext& ctx);  // 0x512448 (register ABI: arguments in $a0.., the result in $v0)
// Set the pad flush rate (0x782754): accepts 0 or a value in 16675..66675; returns 1 when set, 0 (unchanged)
// otherwise.
void scePadSetFlushRate(EEContext& ctx);  // 0x512838 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
