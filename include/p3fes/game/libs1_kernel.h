// Two small EE-side managers of the kernel / sound libraries: the timer alarms' counter operations
// (0x50E850-0x50F358, on sce1's alarm pool: records at (id >> 10) << 6 with a 10-bit tag; the timer itself --
// sub_50E508 reads it, sub_50E000 programs the compare -- stays recompiled) and the SPU2 memory manager sceSpu2Mem*
// (0x51D5B0-0x51D908: a caller table of 12-byte blocks, all bookkeeping on the EE).
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs1::spu2 {
constexpr u32 kTable = 0x782B18u;      // the caller's block table; then the bounds below
constexpr s32 kReserved = 0x5010;      // the first allocatable address (SPU2 RAM below it is reserved)
constexpr u32 kTop = 0x782B38u;        // the top of the used area, then (+4) the size left above it
}  // namespace libs1::spu2


// Start a counter: valid id (tag), not the running handler's; when stopped, stamps the start time and sets the
// running bit, and an armed alarm goes back into the pending list (the timer reprogrammed). [StartTimerCounter]
void sub_50E850(EEContext& ctx);  // 0x50E850 (register ABI: arguments in $a0.., the result in $v0)
// Stop a counter: adds the elapsed time to its total, clears the running bit, takes an armed alarm off the pending
// list. [StopTimerCounter]
void sub_50E950(EEContext& ctx);  // 0x50E950 (register ABI: arguments in $a0.., the result in $v0)
// A counter's total time, including the running stretch. [GetTimerCounterTime]
void sub_50EBE8(EEContext& ctx);  // 0x50EBE8 (register ABI: arguments in $a0.., the result in $v0)
// Arm or disarm a counter's alarm (target time, handler, argument, the caller's $gp) and reprogram the timer.
// [SetTimerCounterHandler]
void sub_50ECA8(EEContext& ctx);  // 0x50ECA8 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context alarm: takes an alarm record from the free list, allocates a counter, arms it with AlarmHandler
// and starts it; returns record << 4 | tag | 1, or an error.
void iSetTimerAlarm(EEContext& ctx);  // 0x50F1C0 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context release: frees the alarm's counter and returns its record to the free list.
void iReleaseTimerAlarm(EEContext& ctx);  // 0x50F358 (register ABI: arguments in $a0.., the result in $v0)
// Set up the SPU2 memory manager over a caller table of N + 1 entries: one free block from 0x5010 (after the reserved
// area) to the end of SPU2 RAM (1.75 MiB, or 2 MiB with the flag).
void sceSpu2MemInit(EEContext& ctx);  // 0x51D5B0 (register ABI: arguments in $a0.., the result in $v0)
// Clear the block table.
void sceSpu2MemQuit(EEContext& ctx);  // 0x51D6B0 (register ABI: arguments in $a0.., the result in $v0)
// Free a block by address: marks it free, merges it with free neighbours, lowers the top when it was the last block.
void sceSpu2MemFree(EEContext& ctx);  // 0x51D908 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
