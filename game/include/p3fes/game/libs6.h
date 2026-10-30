// Slice libs6: SDK-library runtime functions (libkernel, libsif, sceFs, libcdvd, libpad, libsdr, libmc2 / libdbc,
// newlib glue); see game/src/lib/libs6.cpp. Register ABI (arguments in $a0.., the result in $v0); one role comment per
// function, a proposed SDK name in [brackets].
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs6 {
// The low half of a global the bodies reach as lui(hi) + lo: the signed 16-bit offset the instruction holds.
constexpr s32 lo(u32 address) { return static_cast<s32>(address & 0xFFFFu) - ((address & 0x8000u) != 0 ? 0x10000 : 0); }
constexpr u32 kTtyReady = 0x77F490u;  // write / read: 1 once sceTtyInit succeeded
constexpr u32 kTopThreadId = 0x77F498u;  // InitThread: the top thread's id (0 before it exists)
constexpr u32 kTopThreadSema = 0x966100u;  // the top thread's request semaphore
constexpr u32 kRpcQueueList = 0x9684A8u;  // libsif: the head of the RPC queue list
constexpr u32 kIobSema = 0x77F548u;  // sceFs: the iob table's semaphore (-1 before _sceFsIobSemaMK)
constexpr u32 kFioSema = 0x77F544u;  // sceFs: the file I/O semaphore (-1 before _sceFsSemInit)
constexpr u32 kAlarmFreeList = 0x96D7C0u;  // SetTimerAlarm: the free list of 16-byte alarm records
constexpr u32 kMc2Ready = 0x7827D8u;  // libmc2: 1 between sceMc2Init and sceMc2End
constexpr u32 kMc2Command = 0x96F144u;  // libmc2: the pending worker command (0 idle)
constexpr u32 kMc2Thread = 0x96F660u;  // libmc2: the worker thread id
constexpr u32 kMallocIntrWasOn = 0x78339Cu;  // __malloc_lock: the interrupt state the first lock saw
constexpr u32 kErrno = 0x9ACC20u;  // newlib errno (the _r wrappers clear it and copy it into the reent record)
}  // namespace libs6

// libmpeg's default stop-DMA callback: sceIpuStopDMA on the decoder's IPU state ($a0->+64, +104); returns 1.
void _sceMpegDefaultStopDMA(EEContext& ctx);  // 0x501128 (register ABI: arguments in $a0.., the result in $v0)
// libmpeg's default restart-DMA callback: sceIpuRestartDMA on the same IPU state; returns 1.
void _sceMpegDefaultRestartDMA(EEContext& ctx);  // 0x501150 (register ABI: arguments in $a0.., the result in $v0)
// newlib write() for the console: fd 1 or 2 go to sceTtyWrite (sceTtyInit once, flag 0x77F490); any other fd -1.
void write(EEContext& ctx);  // 0x503728 (register ABI: arguments in $a0.., the result in $v0)
// newlib read() for the console: fd 0 goes to sceTtyRead (sceTtyInit once, flag 0x77F490); any other fd -1.
void read(EEContext& ctx);  // 0x5037A8 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context data cache write-back: both bounds aligned down to 64 bytes, then the _sceSDC loop.
void iSyncDCache(EEContext& ctx);  // 0x503AD8 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context data cache invalidate: both bounds aligned down to 64 bytes, then the _sceIDC loop.
void iInvalidDCache(EEContext& ctx);  // 0x503C18 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context INTC enable (the kernel call, then a sync).
void iEnableIntc(EEContext& ctx);  // 0x503DE0 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context INTC disable (the kernel call, then a sync).
void iDisableIntc(EEContext& ctx);  // 0x503E00 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context DMAC enable (the kernel call, then a sync).
void iEnableDmac(EEContext& ctx);  // 0x503E20 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context DMAC disable (the kernel call, then a sync).
void iDisableDmac(EEContext& ctx);  // 0x503E40 (register ABI: arguments in $a0.., the result in $v0)
// libkernel's helper thread: waits on its semaphore, pops a 2-byte request (kind, thread id) from the 512-entry
// ring at $a0 and runs it: 1 rotate the ready queue, 0 wake up, 2 suspend; another kind prints the internal-error
// message. Never returns.
void topThread(EEContext& ctx);  // 0x503E60 (register ABI: arguments in $a0.., the result in $v0)
// Create and start the top thread once ("SceKerneltopThread", priority 0, 1 KiB stack at 0x965D00) with its
// semaphore and request ring at 0x966108, then raise the caller to priority 1; returns the thread id or -1.
void InitThread(EEContext& ctx);  // 0x503F38 (register ABI: arguments in $a0.., the result in $v0)
// Interrupt-context ready-queue rotation: queues request (1, priority) to the top thread and signals it; priority
// must be < 128 and the thread must exist (else -1).
void iRotateThreadReadyQueue(EEContext& ctx);  // 0x5040C0 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 open: (protocol, opaque, handler) plus the reply area 0x20966510 (uncached) through _sceDeci2Call 1.
void sceDeci2Open(EEContext& ctx);  // 0x504440 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 close (socket) through _sceDeci2Call 2.
void sceDeci2Close(EEContext& ctx);  // 0x504488 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 send request (socket, destination byte) through _sceDeci2Call 3.
void sceDeci2ReqSend(EEContext& ctx);  // 0x5044B0 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 poll (socket) through _sceDeci2Call 4.
void sceDeci2Poll(EEContext& ctx);  // 0x5044E0 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 group open (group byte, opaque, handler) through _sceDeci2Call 32.
void sceDeci2GrpOpen(EEContext& ctx);  // 0x504508 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 group close through _sceDeci2Call 33.
void sceDeci2GrpClose(EEContext& ctx);  // 0x504538 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 receive into a buffer (socket, address, 16-bit length) through _sceDeci2Call -5.
void sceDeci2ExRecv(EEContext& ctx);  // 0x504560 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 send from a buffer (socket, address, 16-bit length) through _sceDeci2Call -6.
void sceDeci2ExSend(EEContext& ctx);  // 0x504598 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 send request, extended form, through _sceDeci2Call -7.
void sceDeci2ExReqSend(EEContext& ctx);  // 0x5045D0 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 lock (socket) through _sceDeci2Call -8.
void sceDeci2ExLock(EEContext& ctx);  // 0x504600 (register ABI: arguments in $a0.., the result in $v0)
// DECI2 unlock (socket) through _sceDeci2Call -9.
void sceDeci2ExUnLock(EEContext& ctx);  // 0x504628 (register ABI: arguments in $a0.., the result in $v0)
// The TTY's DECI2 event handler ($a0 event, $a1 length, $a2 the tty record): 1/2 receive (a header chunk, then the
// payload bytes pushed into the read queue), 3 send the pending write and advance it, 4 the send is done (clears
// the busy flag; prints when bytes are left).
void sceTtyHandler(EEContext& ctx);  // 0x504720 (register ABI: arguments in $a0.., the result in $v0)
// Write to the TTY: interrupts off, copies up to 256 bytes into the uncached packet at 0x2096668C (LF becomes CR
// LF), sends the request and polls until the handler clears the busy flag; returns the bytes taken, or -1 when busy
// or the send fails.
void sceTtyWrite(EEContext& ctx);  // 0x5048B8 (register ABI: arguments in $a0.., the result in $v0)
// Open the TTY's DECI2 socket (protocol 0x210, handler sceTtyHandler), clear its record, build the packet header
// (0x210, 'E', 'H') and make the 256-byte read queue; 1, or 0 when the open fails.
void sceTtyInit(EEContext& ctx);  // 0x504B00 (register ABI: arguments in $a0.., the result in $v0)
// Kernel vprintf: interrupts off, _sceSnprintf to the printf_char sink, interrupts back on when they were.
void sceVprintf(EEContext& ctx);  // 0x505DD8 (register ABI: arguments in $a0.., the result in $v0)
// Kernel printf (varargs spilled to the frame): interrupts off, _sceSnprintf to the kprintf_char sink, interrupts
// back on when they were.
void kprintf(EEContext& ctx);  // 0x505EC8 (register ABI: arguments in $a0.., the result in $v0)
// SIF command layer shutdown: disables DMAC channel 5 (SIF0), removes its handler, clears the initialised flag
// 0x77F4A8. [sceSifExitCmd]
void sub_5063C8(EEContext& ctx);  // 0x5063C8 (register ABI: arguments in $a0.., the result in $v0)
// Clears a SIF command handler slot: a non-negative id indexes the user table, a negative one (bit 31 off) the
// system table; 12-byte entries. Named sceSifSendCmd in symbols/, the body is the SDK's [sceSifRemoveCmdHandler].
void sceSifSendCmd(EEContext& ctx);  // 0x5064A8 (register ABI: arguments in $a0.., the result in $v0)
// Send a SIF command in thread context: _sceSifSendCmd with mode 0 (the arguments shifted up). [sceSifSendCmd]
void sub_506630(EEContext& ctx);  // 0x506630 (register ABI: arguments in $a0.., the result in $v0)
// Send a SIF command in interrupt context: _sceSifSendCmd with mode 1. Named sceSifWriteBackDCache in symbols/, the
// body is the SDK's [isceSifSendCmd].
void sceSifWriteBackDCache(EEContext& ctx);  // 0x506670 (register ABI: arguments in $a0.., the result in $v0)
// Write back and invalidate the data cache over [$a0, $a0 + $a1): 64-byte lines, the odd lines first, then eight
// per pass. [sceSifWriteBackDCache]
void sub_5067F8(EEContext& ctx);  // 0x5067F8 (register ABI: arguments in $a0.., the result in $v0)
// SIF RPC shutdown: the command layer's exit, then the RPC initialised flag 0x77F4B0 cleared.
void sceSifExitRpc(EEContext& ctx);  // 0x506A48 (register ABI: arguments in $a0.., the result in $v0)
// Take a free 64-byte RPC packet from the client's pool ($a0: next id, pool, count): marks it busy with its index,
// stamps the next packet id; null when all are busy. Interrupts off.
void _sceRpcGetPacket(EEContext& ctx);  // 0x506A70 (register ABI: arguments in $a0.., the result in $v0)
// Release an RPC packet: clears its id and the busy bit.
void _sceRpcFreePacket(EEContext& ctx);  // 0x506B18 (register ABI: arguments in $a0.., the result in $v0)
// The next packet of a server's receive ring (round robin over its count).
void _sceRpcGetFPacket(EEContext& ctx);  // 0x506B38 (register ABI: arguments in $a0.., the result in $v0)
// Find the RPC server bound to a command id: walks the queues from the request's queue and each queue's server
// list.
void _search_svdata(EEContext& ctx);  // 0x506EF0 (register ABI: arguments in $a0.., the result in $v0)
// SIF RPC call request handler: appends the server to its queue's pending list, copies the request (function,
// buffers, sizes, client packet) into the server record, wakes the queue's thread when it is idle.
void _request_call(EEContext& ctx);  // 0x5071A0 (register ABI: arguments in $a0.., the result in $v0)
// 1 while the client's call is in flight: the packet exists, its id still matches and it is busy.
void sceSifCheckStatRpc(EEContext& ctx);  // 0x507430 (register ABI: arguments in $a0.., the result in $v0)
// Initialise an RPC queue for a thread and append it to the global queue list (0x9684A8). Interrupts off.
void sceSifSetRpcQueue(EEContext& ctx);  // 0x507470 (register ABI: arguments in $a0.., the result in $v0)
// Register an RPC server (command, function, buffer, callbacks) and append it to the queue's server list.
// Interrupts off.
void sceSifRegisterRpc(EEContext& ctx);  // 0x507508 (register ABI: arguments in $a0.., the result in $v0)
// Unlink a server from its queue's list; returns the node it was found after (or the head). Interrupts off.
void sceSifRemoveRpc(EEContext& ctx);  // 0x5075D8 (register ABI: arguments in $a0.., the result in $v0)
// Unlink a queue from the global queue list. Interrupts off.
void sceSifRemoveRpcQueue(EEContext& ctx);  // 0x507670 (register ABI: arguments in $a0.., the result in $v0)
// Pop the queue's next pending server (marks the queue active, or idle when empty). Interrupts off.
void sceSifGetNextRequest(EEContext& ctx);  // 0x507700 (register ABI: arguments in $a0.., the result in $v0)
// Create the stdio iob semaphores once ("SceStdioIobSema", "SceStdioQueSema").
void _sceFsIobSemaMK(EEContext& ctx);  // 0x507960 (register ABI: arguments in $a0.., the result in $v0)
// Count the open file slots (32 16-byte iob records at 0x969A00), under the iob semaphore.
void use_iob_cnt(EEContext& ctx);  // 0x5079D0 (register ABI: arguments in $a0.., the result in $v0)
// Take a free iob record (marks it 0x10000000 in use), under the iob semaphore; null when full.
void new_iob(EEContext& ctx);  // 0x507A50 (register ABI: arguments in $a0.., the result in $v0)
// The iob record of a descriptor (< 32), or null; takes and releases the iob semaphore.
void get_iob(EEContext& ctx);  // 0x507BC8 (register ABI: arguments in $a0.., the result in $v0)
// File I/O RPC receive interrupt: picks the reply slot (0x969180 + 1088 * slot, uncached), copies the result data
// back per command (2 read's unaligned edges, 11 getstat / 12 dread records, 23/25/26 strings up to 1 KiB) and
// signals the waiter; a negative result clears the matching descriptor from the 32-entry table at 0x77F4B8.
void _sceFs_Rcv_Intr(EEContext& ctx);  // 0x507C38 (register ABI: arguments in $a0.., the result in $v0)
// Create the file I/O semaphore once ("SceStdioFioSema").
void _sceFsSemInit(EEContext& ctx);  // 0x507FF0 (register ABI: arguments in $a0.., the result in $v0)
// Take the file I/O semaphore (created on first use); returns 0.
void _sceFsWaitS(EEContext& ctx);  // 0x508048 (register ABI: arguments in $a0.., the result in $v0)
// Release the file I/O semaphore.
void _sceFsSigSema(EEContext& ctx);  // 0x508078 (register ABI: arguments in $a0.., the result in $v0)
// Install the power-off handler (function, argument, the caller's $gp) under the file semaphore; returns the
// previous function.
void scePowerOffHandler(EEContext& ctx);  // 0x508088 (register ABI: arguments in $a0.., the result in $v0)
// Mark the file layer uninitialised and clear its state block.
void sceFsReset(EEContext& ctx);  // 0x508408 (register ABI: arguments in $a0.., the result in $v0)
// remove(name): _sceCallCode 6.
void sceRemove(EEContext& ctx);  // 0x509908 (register ABI: arguments in $a0.., the result in $v0)
// rmdir(name): _sceCallCode 8.
void sceRmdir(EEContext& ctx);  // 0x509AE0 (register ABI: arguments in $a0.., the result in $v0)
// Delete a device driver: _sceCallCode 16.
void sceDelDrv(EEContext& ctx);  // 0x509EB0 (register ABI: arguments in $a0.., the result in $v0)
// Open a directory: a new iob, _sceCallCode 9; on success the IOP descriptor goes in the iob and the result is its
// index, on failure the iob is freed. -19 when no iob is free.
void sceDopen(EEContext& ctx);  // 0x509ED0 (register ABI: arguments in $a0.., the result in $v0)
// chdir(name): _sceCallCode 18.
void sceChdir(EEContext& ctx);  // 0x50A868 (register ABI: arguments in $a0.., the result in $v0)
// Unmount: _sceCallCode 21.
void sceUmount(EEContext& ctx);  // 0x50ACB8 (register ABI: arguments in $a0.., the result in $v0)
// Forget the module loader's binding (0x77F560 = -1) and clear its client data.
void sceSifLoadFileReset(EEContext& ctx);  // 0x50BC78 (register ABI: arguments in $a0.., the result in $v0)
// Install a TLB exception handler: stores it, points the TLB modified / refill (load, store) vectors 1-3 at
// _kTLBException.
void SetTLBHandler(EEContext& ctx);  // 0x50CB28 (register ABI: arguments in $a0.., the result in $v0)
// Install a debug handler for exception codes 1..13: stores it in the table at 0x77F8A0 and points the vector at
// _kDebugException (TLB vectors for 1-3, common for the rest); returns the old one.
void SetDebugHandler(EEContext& ctx);  // 0x50CB88 (register ABI: arguments in $a0.., the result in $v0)
// Kernel-mode word copy (dst, src, bytes): the syscall body used to patch kernel memory; returns 0.
void kCopy(EEContext& ctx);  // 0x50CC20 (register ABI: arguments in $a0.., the result in $v0)
// Install the TLB kernel patch: kCopy as syscall 0x5A, the payload copied to 0x80075000, the caches flushed, then
// the patch table's syscalls; keeps the kernel's syscall table base.
void InitTLBFunctions(EEContext& ctx);  // 0x50CC78 (register ABI: arguments in $a0.., the result in $v0)
// Set a TLB entry: index 13..47 only (else -1).
void SetTLBEntry(EEContext& ctx);  // 0x50CD70 (register ABI: arguments in $a0.., the result in $v0)
// Reinitialise the TLB: the 32 MiB layout when the memory size is 32 MiB, else the kernel's.
void InitTLB(EEContext& ctx);  // 0x50CE00 (register ABI: arguments in $a0.., the result in $v0)
// Debug exception dispatch: calls the handler of the cause's exception code (table at 0x77F8A0), then breaks.
// [kDebugExceptionDispatch]
void sub_50D37C(EEContext& ctx);  // 0x50D37C (register ABI: arguments in $a0.., the result in $v0)
// Create libc's two semaphores ("SceKernelLibc", "SceKernelLibcEh").
void supplement_crt0(EEContext& ctx);  // 0x50D408 (register ABI: arguments in $a0.., the result in $v0)
// Kernel-mode word copy, the copy used by the syscall table search.
void kCopy_0(EEContext& ctx);  // 0x50D488 (register ABI: arguments in $a0.., the result in $v0)
// Kernel-mode search for a word in [$a0, $a1); returns its address or 0.
void kFindAddress(EEContext& ctx);  // 0x50D4C0 (register ABI: arguments in $a0.., the result in $v0)
// Read the kernel's syscall table entry n (a kernel-mode copy from the found table).
void GetSystemCallEntry(EEContext& ctx);  // 0x50D510 (register ABI: arguments in $a0.., the result in $v0)
// Locate the kernel's syscall table: installs the find / copy syscalls, then searches kernel memory for both and
// lines the two results up (0x77FBB8).
void InitSystemCallTableAddress(EEContext& ctx);  // 0x50D548 (register ABI: arguments in $a0.., the result in $v0)
// libkernel's runtime start-up: libc semaphores, the syscall table, alarms, timer 2 and the system time, the top
// thread, the ExecPS2 and TLB patches, then the reboot-notify state cleared.
void crt_init_runtime(EEContext& ctx);  // 0x50D658 (register ABI: arguments in $a0.., the result in $v0)
// Kernel-mode word copy, the ExecPS2 patch's.
void kCopy_1(EEContext& ctx);  // 0x50D6D0 (register ABI: arguments in $a0.., the result in $v0)
// 1 when the kernel needs the ExecPS2 patch: writes the OSD config bits 13-15 as 1, reads them back (0 on an old
// kernel) and restores the config.
void PatchIsNeeded(EEContext& ctx);  // 0x50D718 (register ABI: arguments in $a0.., the result in $v0)
// Install the ExecPS2 kernel patch when it is needed: the payload to 0x80074000, caches flushed, the patch table's
// syscalls set.
void InitExecPS2(EEContext& ctx);  // 0x50D780 (register ABI: arguments in $a0.., the result in $v0)
// Copy ExecPS2's argument strings into the kernel's argument area (the program name then up to 15 arguments, each
// through a kernel-mode copy); returns the area.
void SetArg(EEContext& ctx);  // 0x50D880 (register ABI: arguments in $a0.., the result in $v0)
// Thunk to InitTLB (the exec paths call it before leaving the program). [ResetTLB]
void sub_50D998(EEContext& ctx);  // 0x50D998 (register ABI: arguments in $a0.., the result in $v0)
// Execute a loaded program: arguments into the kernel area, the TLB reset, then the ExecPS2 syscall.
void ExecPS2(EEContext& ctx);  // 0x50D9A0 (register ABI: arguments in $a0.., the result in $v0)
// Kernel-mode word copy, a fourth copy of kCopy.
void kCopy_3(EEContext& ctx);  // 0x50DAF0 (register ABI: arguments in $a0.., the result in $v0)
// Shut the system timer down: when it is set up and no counter is in use, removes the timer 2 interrupt handler,
// disables it and stops the counter. [EndTimer]
void sub_50DE08(EEContext& ctx);  // 0x50DE08 (register ABI: arguments in $a0.., the result in $v0)
// Allocate a timer counter with interrupts off (the i-form inside). [AllocTimerCounter]
void sub_50E648(EEContext& ctx);  // 0x50E648 (register ABI: arguments in $a0.., the result in $v0)
// Free a timer counter with interrupts off. [FreeTimerCounter]
void sub_50E750(EEContext& ctx);  // 0x50E750 (register ABI: arguments in $a0.., the result in $v0)
// A timer counter query with interrupts off (two arguments, sub_50E7A0 inside). [GetTimerUsedUnusedCounters]
void sub_50E7F0(EEContext& ctx);  // 0x50E7F0 (register ABI: arguments in $a0.., the result in $v0)
// Start a timer counter with interrupts off. [StartTimerCounter]
void sub_50E900(EEContext& ctx);  // 0x50E900 (register ABI: arguments in $a0.., the result in $v0)
// Stop a timer counter with interrupts off. [StopTimerCounter]
void sub_50EA30(EEContext& ctx);  // 0x50EA30 (register ABI: arguments in $a0.., the result in $v0)
// Set a timer counter's accumulated time: returns the old total (the running stretch included, the start
// re-stamped) or -1 for a bad id. Interrupts off. [SetTimerCount]
void sub_50EA80(EEContext& ctx);  // 0x50EA80 (register ABI: arguments in $a0.., the result in $v0)
// A timer counter's base time with interrupts off (sub_50EB50 inside). [GetTimerBaseTime]
void sub_50EB98(EEContext& ctx);  // 0x50EB98 (register ABI: arguments in $a0.., the result in $v0)
// A timer counter's total time with interrupts off. [GetTimerCount]
void sub_50EC58(EEContext& ctx);  // 0x50EC58 (register ABI: arguments in $a0.., the result in $v0)
// Arm a timer counter's handler with interrupts off. [SetTimerHandler]
void sub_50EDB8(EEContext& ctx);  // 0x50EDB8 (register ABI: arguments in $a0.., the result in $v0)
// Thread-context alarm: an alarm record from the free list (0x96D7C0), a counter allocated, armed with AlarmHandler
// and started; returns record << 4 | tag | 1, or an error code.
void SetTimerAlarm(EEContext& ctx);  // 0x50F090 (register ABI: arguments in $a0.., the result in $v0)
// Release an alarm: checks the tag, frees its counter and returns the record to the free list.
void ReleaseTimerAlarm(EEContext& ctx);  // 0x50F2B0 (register ABI: arguments in $a0.., the result in $v0)
// Install the user reboot-notify table (address, count; cleared); returns the old one.
void sceSifSetRebootNotifyBuffer(EEContext& ctx);  // 0x50F3F8 (register ABI: arguments in $a0.., the result in $v0)
// Set a reboot-notify entry (function, argument, the caller's $gp): a non-negative index in the user table, a
// negative one in the 32-entry system table.
void sceSifAddRebootNotifyHandler(EEContext& ctx);  // 0x50F478 (register ABI: arguments in $a0.., the result in $v0)
// Clear a reboot-notify entry (same index rule); -105 when out of range.
void sceSifRemoveRebootNotifyHandler(EEContext& ctx);  // 0x50F530 (register ABI: arguments in $a0.., the result in $v0)
// Call every reboot-notify handler of the system ($a0 != 0) or user table with ($a1, its argument) and its $gp.
void sceSifExecNotifyHandler(EEContext& ctx);  // 0x50F588 (register ABI: arguments in $a0.., the result in $v0)
// CD/DVD command-end interrupt: records the function number; 11 just clears the state, others signal the N-command
// semaphore and the callback thread's semaphore when a callback is set.
void _sceCd_cd_callback(EEContext& ctx);  // 0x50F698 (register ABI: arguments in $a0.., the result in $v0)
// The CD/DVD callback thread: waits on its semaphore, calls the user callback with the finished function number; -1
// exits and deletes the thread.
void _sceCd_cbLoop(EEContext& ctx);  // 0x50F738 (register ABI: arguments in $a0.., the result in $v0)
// Start the CD/DVD callback thread once ("SceCdCallbackThread", the caller's priority, stack and size); when it
// exists, only changes its priority.
void sceCdInitEeCB(EEContext& ctx);  // 0x50F808 (register ABI: arguments in $a0.., the result in $v0)
// Create the CD/DVD semaphores when any is missing (N-command, S-command, R-command, callback).
void cmd_sem_init(EEContext& ctx);  // 0x50F960 (register ABI: arguments in $a0.., the result in $v0)
// Install the CD power-off callback (function, argument, $gp); registers the SIF handler first when needed; returns
// the old function.
void sceCdPOffCallback(EEContext& ctx);  // 0x50FAE8 (register ABI: arguments in $a0.., the result in $v0)
// SIF power-off command handler: calls the user's power-off callback unless it is being installed.
void _sceCd_Poff_Intr(EEContext& ctx);  // 0x50FB68 (register ABI: arguments in $a0.., the result in $v0)
// Register the CD power-off SIF command handler (system command 0x80000012) with interrupts off.
void PowerOffCB(EEContext& ctx);  // 0x50FBC0 (register ABI: arguments in $a0.., the result in $v0)
// libcdvd's internal query: stores the address of an internal variable selected by code 0x8001-0x8014.
void _sceCdSC(EEContext& ctx);  // 0x5103B0 (register ABI: arguments in $a0.., the result in $v0)
// Unsupported in this library: prints the illegal-call message, returns 2.
void sceCdChgSys(EEContext& ctx);  // 0x511110 (register ABI: arguments in $a0.., the result in $v0)
// Set a pad's request state byte (DMA area +113) and write the area back, when the port/slot is open (table
// 0x96DD10, 112 bytes per port, 28 per slot).
void scePadSetReqState(EEContext& ctx);  // 0x511B08 (register ABI: arguments in $a0.., the result in $v0)
// Set the actuator values of a pad: when its DMA status says ready, copies 6 bytes into the port's send buffer and
// sends it to the IOP; 1 on success.
void scePadSetActDirect(EEContext& ctx);  // 0x512070 (register ABI: arguments in $a0.., the result in $v0)
// Install the sound driver's callback (and the caller's $gp); returns the previous one.
void sceSdCallBack(EEContext& ctx);  // 0x5129A0 (register ABI: arguments in $a0.., the result in $v0)
// Sound driver remote callback: bit 0x100 calls the core 0 DMA end handler, 0x200 core 1, 0x400 the IRQ handler,
// each with its argument.
void _sdrCB(EEContext& ctx);  // 0x512FF0 (register ABI: arguments in $a0.., the result in $v0)
// Shut libmc2 down: waits for a pending command, terminates and deletes the worker thread, deletes the three
// semaphores, ends the core.
void sceMc2End(EEContext& ctx);  // 0x513290 (register ABI: arguments in $a0.., the result in $v0)
// Find the memory card socket of a port/slot (sceDbcSearchPortSpecific) under the API semaphore; an error when not
// initialised, busy or not found.
void sceMc2SearchSocket(EEContext& ctx);  // 0x513478 (register ABI: arguments in $a0.., the result in $v0)
// Change the worker thread's priority (> 0).
void sceMc2ChangeThreadPriority(EEContext& ctx);  // 0x513528 (register ABI: arguments in $a0.., the result in $v0)
// Change the worker thread's priority from interrupt context (> 0).
void sceMc2iChangeThreadPriority(EEContext& ctx);  // 0x513560 (register ABI: arguments in $a0.., the result in $v0)
// Queue a whole-directory read (command 100) on the socket and wake the worker.
void sceMc2GetDirAllAsync(EEContext& ctx);  // 0x5138B8 (register ABI: arguments in $a0.., the result in $v0)
// libmc2's worker thread: waits for a command, runs the matching _sceMcFat* call with the request's arguments (2
// info, 3 format, 4 unformat, 5/6 read/write, 7/11 create, 8 delete, 9 rename, 10 getdir, 12 chdir, 13 setattr, 14
// search, 15 entry space, 32/33 fast read/write), stores the result and signals the done semaphore.
void basic_thread(EEContext& ctx);  // 0x5145F8 (register ABI: arguments in $a0.., the result in $v0)
// Format a memory card: reads the card spec and system info (bad-block list rebuilt when the superblock is not
// "Sony PS2 Memory Card Format"), fills the superblock ("1.2.0.0"), places the indirect FAT, the FAT and the root
// directory around the bad blocks, writes them and flushes.
void _sceMcFatFormat(EEContext& ctx);  // 0x516118 (register ABI: arguments in $a0.., the result in $v0)
// Wait for the memory card core's SIF reply and pick the newer of the two reply buffers (by sequence).
void SyncDma(EEContext& ctx);  // 0x51AD10 (register ABI: arguments in $a0.., the result in $v0)
// Wait for the memory card core's read reply; returns the reply buffer.
void SyncDmaForRead(EEContext& ctx);  // 0x51ADE0 (register ABI: arguments in $a0.., the result in $v0)
// Create the core's reply semaphore ("sceMc2_sema_subs") and reset the two socket records.
void _sceMcCoreInit(EEContext& ctx);  // 0x51AE68 (register ABI: arguments in $a0.., the result in $v0)
// Delete the reply semaphore and the two sockets' DBC connections.
void _sceMcCoreEnd(EEContext& ctx);  // 0x51AEF8 (register ABI: arguments in $a0.., the result in $v0)
// Fill a card range with one value: builds the write-same request for the socket, sends it (retrying) and waits for
// the reply; returns the count on success.
void _sceMcCoreWriteSameData(EEContext& ctx);  // 0x51BA88 (register ABI: arguments in $a0.., the result in $v0)
// End libdbc: deletes its semaphore when initialised.
void sceDbcEnd(EEContext& ctx);  // 0x51C658 (register ABI: arguments in $a0.., the result in $v0)
// A socket's connection state from the IOP-written table (copied under interrupts off): 1 connected, 3 otherwise.
void sceDbcGetConnection(EEContext& ctx);  // 0x51CAD0 (register ABI: arguments in $a0.., the result in $v0)
// Sound kernel quit stub: returns 0.
void sceSkQuit(EEContext& ctx);  // 0x51DAD8 (register ABI: arguments in $a0.., the result in $v0)
// newlib malloc lock: outside interrupts, nests a count and disables interrupts on the first lock.
void __malloc_lock(EEContext& ctx);  // 0x5214C8 (register ABI: arguments in $a0.., the result in $v0)
// newlib malloc unlock: outside interrupts, re-enables interrupts when the count drops to 0.
void __malloc_unlock(EEContext& ctx);  // 0x521520 (register ABI: arguments in $a0.., the result in $v0)
// Reentrant read: clears errno, calls read, copies errno into the reent record on -1.
void _read_r(EEContext& ctx);  // 0x522F38 (register ABI: arguments in $a0.., the result in $v0)
// Reentrant sbrk: clears errno, calls sbrk, copies errno into the reent record on -1.
void _sbrk_r(EEContext& ctx);  // 0x523930 (register ABI: arguments in $a0.., the result in $v0)
// Reentrant write: clears errno, calls write, copies errno into the reent record on -1.
void _write_r(EEContext& ctx);  // 0x528970 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
