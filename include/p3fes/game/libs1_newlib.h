// The newlib tail 0x51E178-0x51FFF0 that the libc slice left: _calloc_r, the _close_r / _kill_r errno wrappers,
// _dtoa_r, exit, the stdio glue (fflush, __sfmoreglue, __sfp, _cleanup(_r), __sinit, fread) and dlmalloc's _free_r /
// _malloc_trim_r (libc.h's `reent::` / `file::` records). Kept recompiled below them: _malloc_r, __malloc_lock / unlock
// (interrupt masking), _sbrk_r, __srefill, _fwalk, the FILE callbacks.
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// calloc on a reentrancy record: _malloc_r(n x size), then zero the chunk's usable size (memset from 37 bytes,
// unrolled stores below).
void _calloc_r(EEContext& ctx);  // 0x51E178 (register ABI: arguments in $a0.., the result in $v0)
// close(fd) with errno cleared first and copied into the reentrancy record on -1.
void _close_r(EEContext& ctx);  // 0x51E230 (register ABI: arguments in $a0.., the result in $v0)
// newlib's double to decimal digits (David Gay's dtoa): mode / ndigits, decimal point position, sign, end pointer;
// Bigints from the reentrancy record's pool.
void _dtoa_r(EEContext& ctx);  // 0x51E4B0 (register ABI: arguments in $a0.., the result in $v0)
// Run the atexit handlers (newest first, every block), the cleanup hook, then _exit (sub_100218).
void exit(EEContext& ctx);  // 0x51F6A0 (register ABI: arguments in $a0.., the result in $v0)
// Flush a FILE (all FILEs through _fwalk for NULL): writes the buffered bytes through its write callback, sets the
// error flag on a failure.
void fflush(EEContext& ctx);  // 0x51F728 (register ABI: arguments in $a0.., the result in $v0)
// Allocate a glue block of N zeroed FILEs.
void __sfmoreglue(EEContext& ctx);  // 0x51F898 (register ABI: arguments in $a0.., the result in $v0)
// Find a free FILE (flags 0) in the glue chain, adding a block of 4 when all are used; initialises it.
void __sfp(EEContext& ctx);  // 0x51F908 (register ABI: arguments in $a0.., the result in $v0)
// Flush every FILE of a reentrancy record.
void _cleanup_r(EEContext& ctx);  // 0x51F9E0 (register ABI: arguments in $a0.., the result in $v0)
// Flush every FILE of the global reentrancy record.
void _cleanup(EEContext& ctx);  // 0x51FA00 (register ABI: arguments in $a0.., the result in $v0)
// Initialise a reentrancy record's stdio: the cleanup hook, the three standard FILEs (std with flags 4 / 9 / 10).
void __sinit(EEContext& ctx);  // 0x51FA20 (register ABI: arguments in $a0.., the result in $v0)
// Read N items: copy what the buffer holds, refill (__srefill) until done or EOF; returns whole items read.
void fread(EEContext& ctx);  // 0x51FAA0 (register ABI: arguments in $a0.., the result in $v0)
// dlmalloc free: coalesce with free neighbours and the top chunk, bin the result, trim when the top grows past the
// threshold.
void _free_r(EEContext& ctx);  // 0x51FBB0 (register ABI: arguments in $a0.., the result in $v0)
// dlmalloc trim: give whole pages above the top chunk back with sbrk.
void _malloc_trim_r(EEContext& ctx);  // 0x51FE90 (register ABI: arguments in $a0.., the result in $v0)
// The reentrant wrapper around fstat (sic: this build's _kill_r calls fstat), errno handled like _close_r.
void _kill_r(EEContext& ctx);  // 0x51FFF0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
