# `runtime/hle/kernel/` — EE kernel / timing HLE (`p3fes_kernel`)

_ADR-0013 §3 owner of: the `HwBus`, the virtual time base, INTC + timers, the DMAC register block + tag chains +
SPR channels, the EE syscalls, the fiber scheduler and the `RtHooks` implementation. Rules: `docs/ANALYSIS/15`
(BIOS v02.30 kernel, **obs**), `docs/RUNTIME_CONTRACT.md` §1, §3, §5.1, §5.5, §8.5, `docs/ANALYSIS/12` §4-5.
Public API: `runtime/include/p3fes/hle/kernel.h`. Tests: `tests/kernel/` (doctest, no game data)._

Tags: **obs** = read from the BIOS/ELF instructions (`15`, or ps2dev objdump of the verified ELF here), **der** =
derived from obs, **inf** = inferred (a choice; listed in "Choices and divergences").

## Files

| File | Concern |
|---|---|
| `kernel_core.h` | `KernelHooks`: the one class (RtHooks + HwBus) and all kernel state; time-base constants |
| `bus_timebase.cpp` | range map, width-exact dispatch, unhandled ring log, `raise_intc`/`dma_complete`, VBLANK events, event loop, check-point slow path |
| `intc_timers.cpp` | INTC_STAT / INTC_MASK, timers T0-T3 |
| `dmac.cpp` | DMAC registers, transfer engine, SPR channels, completion |
| `interrupts.cpp` | handler lists, delivery, chains |
| `scheduler.cpp` | ready queues, pick/activate/block/exit, fibers, harness `start`/`run_until` |
| `fiber.h`, `fiber_switch_x64.asm` | the kernel's own fibers: a MASM stack switch with a plain-data context |
| `kernel_state.cpp` | machine state save/load (`runtime/STATE.md`): every field + each live fiber's host stack |
| `syscalls.cpp` | dispatch and every syscall service |
| `kernel.cpp` | construction, `~Kernel`, diagnostics, the `Kernel` facade |

## Execution model (ADR-0013 §1-2)

* **One host thread, one fiber per guest thread.** The host thread that calls `Kernel::run`/`run_until` is the
  *host fiber* and never runs guest code; the main thread (tid 1) runs `start_fn` on its own fiber, so `run` can
  return when it exits, stops or dies. A switch saves the whole `EEContext` into the outgoing TCB, loads the incoming
  one (keeping `cycles` and `memory`) and switches stacks. Since 2026-10-21 the fibers are the kernel's own
  (`fiber.h`: `p3fes_fiber_switch` saves rbx rbp rdi rsi r12-r15, xmm6-15, MXCSR, the x87 control word and the TEB
  stack bounds, as `FIBER_FLAG_FLOAT_SWITCH` Win32 fibers did) so a machine state can carry each suspended guest
  thread's host stack: with `p3fes::pinned::enable()` (the game host) a fiber is a fixed 1 MiB stack slot (64 KiB
  guard below) and the kernel object is allocated in the fixed-address arena; otherwise (tests) stacks of
  `KernelOptions::fiber_stack_bytes` come from VirtualAlloc.
* **Virtual time.** `hlines = floor(cycles·1125/21086208)` (18,743.296 cycles/line), VBLANK_START *k* at
  `ceil(k·24600576/5)` (4,920,115.2 cycles/field = 262.5 lines; 60000/1001 Hz), exact; `field` toggles and
  `vblanks` counts at each VBLANK_START (what the GS device must report as `CSR.FIELD`). VBLANK_END 22 lines later
  (**inf**, unused by the game; bit 3 appears).
* **Check points.** `check_events(ctx)` = `if (ctx.cycles < next_deadline_) return;` — 4 instructions in the callee
  (`mov`/`cmp`/`jae`-tail-jump/`ret`, MSVC `/O2`, inspected in the generated assembly) plus the adapter's indirect
  call. The slow path processes due events in deadline order, delivers interrupts (one cause per delivery, re-tested
  after each chain), takes a preemption flagged inside a chain, and tests a `run_until` predicate. Syscalls end with
  a check point. Anything that may make work deliverable (`raise_intc`, `dma_complete`, mask/STAT writes) forces the
  next check point onto the slow path. While an interrupt is deliverable but the CPU masks it (`Status`: EIE, IE,
  EXL, ERL), the next re-test is at most `masked_poll_cycles` (64) later — the adapter need not call `check_events`
  after `EI`.
* **Idle rule.** When no thread is READY the scheduler runs the idle thread (tid 0, priority 128) inline: it jumps
  `cycles` to the next deadline, processes it and delivers what became pending; it never spins the host. No event at
  all, or no thread readied within `idle_limit_cycles` (30 virtual s), is a deadlock → fatal.
* **Handler chains** are nested host calls on the current fiber (`lookup(handler)(ctx)`); the interrupted context
  is saved before the chain and restored after (everything but `cycles`, H-05), `Status.IE = 0` during the chain.

## Rules implemented (docs/ANALYSIS/15 §8)

| Rule | Where | Test (`tests/kernel/`) |
|---|---|---|
| H-01 lists: next 0 head / −1 tail / id before id; ids 1-128 shared INTC+DMAC, FIFO free list; cause ≥ 15 or 1 → −1 | `interrupts.cpp add_handler` | `test_interrupts` H-01/H-02 |
| H-02 head → tail, negative return stops, args `(cause\|ch, arg, EPC)`, registrant `$gp`, stack 0x81FC0 | `run_chain` | H-03 case, H-01/H-02 case, DMAC chain case |
| H-03 cause-2 [gate, RW, cb] → RW on odd fields only (10 flips / 20 fields) | (falls out of H-01/H-02) | H-03 case |
| H-04 one cause per delivery, DMAC (IP3) before INTC (IP2), highest first, ack before dispatch, no nesting | `deliver_one`, `slow_check` | H-04 case |
| H-05 save everything around the chain | `run_chain` | H-03 case (`$s0`, `$gp` preserved) |
| H-06 SetVSyncFlag serviced before the cause-2 handlers, one-shot | `service_vsync_flag` | H-06 case |
| H-07 Enable/Disable return 1 only when the bit changed | `sc_enable_intc/dmac` | H-07 case |
| H-08 priorities 0-127 FIFO, RUN stays at its head, pick = lowest non-empty | `scheduler.cpp` | `test_scheduler` H-08 case |
| H-09 positive switching set reschedules at once when ≥ 0; `i*` only flags; flag honoured only at interrupt exit | `syscall`, `ready_insert`, `slow_check` | H-08, H-09/H-11 handler case, H-11 (`iWakeupThread` from a thread), H-16 (`iSignalSema`) |
| H-10 ChangeThreadPriority re-appends at tail (yield), returns old, rejects DORMANT / ≥ 128 | `sc_change_priority` | H-08, H-10 cases |
| H-11 wakeup counts unbounded, SleepThread consumes, waking RUN → −1 lost | `sc_wakeup`, `sc_sleep` | H-11 cases |
| H-12 entry return → root_func → ExitThread → DORMANT (restartable, priority reset) | `thread_fiber_main`, `exit_current` | H-12/13/14 case, lifecycle cases |
| H-13 SetupThread returns stack+size−0x2A0, stack −1 → top − 4 KiB − size, argv block | `sc_setup_thread` | H-12/13/14 case |
| H-14 SetupHeap(x, −1) → stack base; heap end inherited | `sc_setup_heap`, `sc_create_thread` | H-12/13/14 case |
| H-15 main at priority 0, tid 1; sema ids from 0; thread ids FIFO from 2 | `start`, ctor | H-08, H-16 cases |
| H-16 semaphores: init ≥ 0, max never enforced, FIFO waiters, Wait → id / −1 on delete or release; **LIFO free list** (a deleted id is reused first: `iDeleteSema 0x80004B7C` pushes the head `CreateSema 0x800049B8` pops) | `sc_*_sema` | H-16 case, H-17 case |
| H-17 SuspendThread(self) traps, TerminateThread(self) → −1 | `sc_suspend`, `sc_terminate_thread` | H-17 cases |
| H-18 SetSyscall: 256-entry record, no bounds check (0x12C → cause-12 dispatcher, negative n), mirror at 0x80015500+4n | `sc_set_syscall` | `test_syscalls` H-18/H-20, B-06 shape |
| H-19 never-installed slots trap; Copy/GetEntryAddress/FindAddress only once installed | `installed_syscall`, `stock_syscall` | H-19 case, B-11 / B-06 shape cases |
| H-20 alarm patch installs (T3_MODE reads 0) and never runs: 0xFC-0xFF, 0x08 trap; cause 12 enabled/pending traps | `set_intc_mask`, `raise_intc`, `installed_syscall` | H-18/H-20 case |
| H-21 GsGetIMR returns the GsPutIMR cache; GsPutIMR writes 0x12001010 through the bus | `stock_syscall 0x70/0x71` | H-21..H-25 case |
| H-22 OSD config word verbatim | `0x4A/0x4B` | H-21..H-25 case |
| H-23 `_GetGsDxDyOffset` → 0 (GS revision < 0x19; Q-03 default `gs_early_model = true`) | `0x80` | H-21..H-25 case |
| H-24 MachineType 0 (PSMode sets bit 15), GetMemorySize 0x2000000 | `0x7D-0x7F` | H-21..H-25 case |
| H-25 FlushCache any mode → no-op | `0x64/0x68` | H-21..H-25 case |

## Syscalls: implemented / stubbed / trapped (256 slots)

Dispatch (`15` §7): `$v1 < 0` → same slot, no reschedule; a positive call in {0x21 0x22 0x25 0x29 0x2B 0x2D 0x33 0x39
0x41 0x42} reschedules when its result is ≥ 0; 0x32/0x44 block; 0x23/0x24 never return; a positive
switching/blocking call inside a handler, or a negative blocking one, is fatal. Precedence per slot: a host
`SyscallFn` (`install_syscall`) > a guest `SetSyscall` installation > the stock service.

* **Implemented, 71 slots** (3 only after the guest's `SetSyscall`, 1 negative-only): 0x02; 0x10-0x17; 0x1A-0x1D;
  0x20-0x26; 0x29-0x3A; 0x3C-0x3E; 0x40-0x48; −0x49 (iDeleteSema); 0x4A-0x4B; 0x5A/0x5B/0x83 (installed); 0x5C-0x5F
  (Enable/DisableIntc/DmacHandler mode bits — the brief's item 4; contract K-45 listed them as traps); 0x64/0x68;
  0x70, 0x71, 0x73, 0x74, 0x75; 0x7D-0x80.
* **Stubbed with success (group B), 17 slots**: 0x27/0x28 (BIOS: "not supported", return the tid), 0x4C-0x4F → 0,
  0x60-0x62 → 0, 0x63/0x67 GetCop0 → `cop0[a0]`, 0x66/0x6A → 0, 0x6B → 0, 0x6E/0x6F → 0, 0x7C Deci2Call → 0
  (replaceable by the SIF module).
* **Trapped by name, 168 slots**: group C (0x00, 0x01, 0x03-0x09, 0x0A-0x0F, 0x3B, 0x3F, +0x49, 0x50-0x59, 0x65, 0x69,
  0x6C, 0x6D, 0x72, 0x7B, 0x81, 0x82), the stock alarm calls 0x18/0x19/0x1E/0x1F, SIF 0x76-0x7A until
  `install_syscall`, and 0x84-0xFF (incl. the alarm patch's 0xFC-0xFF). Undefined slots say "slot never installed".

### Installed syscalls (K-11; `12` §5; ELF obs)
libkernel's `_InitSys` installs its own handlers with `SetSyscall` and calls them (B-06, B-11, B-12):
* a handler inside the recompiled code band (`code_begin..code_end`, default `0x100000-0x5A1400`) is executed as a
  recompiled function in kernel mode (`$sp = 0x80019440`, `$sp/$ra/$at` restored, interrupts held): the four
  `kCopy*` (`0x50CC20/0x50D488/0x50D6D0/0x50DAF0`, word copy of `a2/4` words), `SetArg`'s byte copy `0x50D840`,
  `kFindAddress 0x50D4C0`;
* `GetEntryAddress` installed at the TLB / alarm payloads (`0x80075000` / `0x80076000`) is the payload's 6-entry
  `{id, addr}` lookup at `+0x300` / `+0x710` read from guest RAM (obs: ELF `0x77F568` / `0x7803A0`);
* the TLB/xlaunch slots 0x54-0x59, 0x08 and 0xFC-0xFF trap when called (never executed after `_InitSys`); a stock
  service replaced by `SetSyscall` traps.
`SetSyscall` also writes the word into guest RAM at `0x80015500 + 4n` (the kernel's table image) so libkernel's
`FindAddress(0x80000000, 0x80080000, kFindAddress)` finds slot 0x83 and computes the table base as on hardware.

## DMAC (contract §5.1, `10` §5 item 5)

* Registers: per channel CHCR/MADR/QWC/TADR/ASR0/ASR1/SADR; D_CTRL, D_STAT (bits 0-15 W1C, 16-31 toggle on 1),
  D_PCR (storage; `CPCOND0` is the adapter's), D_SQWC, D_RBSR, D_RBOR, D_STADR, D_ENABLER/W (0x1201 at reset, **inf**).
* Start on CHCR.STR 0→1 (held while D_CTRL.DMAE = 0 or D_ENABLEW.CPND). The whole transfer runs synchronously:
  normal mode (MADR/QWC) or source chain (refe, cnt, next, ref, refs, call, ret, end; ASR stack; TIE + tag IRQ ends;
  TTE delivers the tag qword with its DMAtag half zeroed before the data). Data go to the channel's
  `DmaChannelHandler` (`tag` = current DMAtag, 0 in normal mode), split at the end of RAM/SPR; MADR bit 31 selects
  the scratchpad, RAM addresses are masked to 32 MiB (**inf**). A handler consuming fewer qwords stalls the channel;
  it is retried at the first check point ≥ `dma_stall_retry_cycles` later. Completion (STR clear, D_STAT.CIS) is an
  event `dma_base_cycles + qwords·dma_cycles_per_qword` (64 + 2/qword, **inf**) after the data finished; the DMAC
  handler chain runs when `D_STAT & (D_STAT>>16 | 0x8000)` (`15` §2.1). CHCR.STR written 0 stops the channel.
* **Re-arm window** (`docs/INTEGRATION_LOG.md` M3-FMV #1): between the end of a transfer's data phase and its
  completion event, reads still show STR = 1 (the modelled latency; RW spins on it), but a CHCR **write** addresses
  an idle channel, as on hardware where STR clears when the transfer ends: the pending completion is taken at the
  write (STR clear, D_STAT.CIS; the handler chain runs at the next check point) and the write is then applied —
  STR = 1 starts the new transfer, STR = 0 leaves the channel idle with the completion delivered (no longer
  cancelled). Needed by libmpeg's `_slice0 0x4FC3A8`, which waits only for `D3_QWC == 0` before re-arming D3 for the
  next macroblock. Not applied to the device-driven SIF0 chain.
* Channels 8 (fromSPR: normal, destination chain cnts/cnt/end read from SPR) and 9 (toSPR: normal, source chain) are
  performed here. Channel 5 (SIF0) in chain mode is device-driven: STR stays set until the SIF module calls
  `dma_complete(5)`. `dma_complete(ch)` on an active channel completes it.
* Traps: a start with no data path installed, interleave/reserved mode, D_CTRL MFD/STS/STD ≠ 0, fromIPU chain,
  toSPR chain with TTE, ASR overflow, an unknown fromSPR destination-chain tag.

## Fiber lifecycle invariants (tested in `test_scheduler.cpp`)

* **L1** A fiber is never deleted while executing: an exiting or terminated thread whose fiber is the executing one
  (its own exit; or an interrupt handler terminating the thread whose stack hosts the idle loop) becomes a zombie,
  deleted by the next fiber that resumes, by the host on return, or by `~Kernel`. The host's resume target is never
  reaped.
* **L2** A thread restarted after Exit/Terminate gets a new fiber (created on activation); old stacks never resume.
* **L3** No RAII state lives on a guest fiber's stack across a switch (abandoned fibers are deleted without
  unwinding). The kernel's own frames hold none; **the adapter must not hold any across `syscall`/`check_events`**.
* **L4** `~Kernel` runs on the host fiber and deletes every fiber exactly once (TCBs, zombies, a stopped resume
  target).
* Terminating a suspended (not executing) thread deletes its fiber at once. A fatal with a sink switches to the host
  fiber and abandons the guest fiber (sticky `RunStatus::Fatal`); without a sink: stderr + `std::abort()`.

## Harness API (`kernel.h`)

`Kernel(EEMemory&, EEContext&, KernelOptions)`, `bus()`, `hooks()`, `try_map`, `start(fn)`, `run(fn)` (until the main
thread exits or a fatal), `run_until(pred)` (resumable `Stopped`), `step_to_next_event()`, `snapshot_eemem(path)`
(32 MiB RAM image, PCSX2 `eeMemory.bin` layout), `install_syscall(n, fn)`, inspection (`time`, `current_thread`,
`thread(tid)`, `intc_stat/mask`, `d_stat`, `unhandled_log`, `syscall_installed/address`, `cause12_dispatcher`,
`gs_crt`, `gs_imr`, `handler_count`, `next_deadline` for an adapter that wants to inline the compare).

## Integration contract (for the lead / other owners)

* `set_hooks()`/`hooks()` are defined by `runtime/rt/`; install `&kernel.hooks()`. The kernel calls
  `p3fes::rt::lookup_func` unless `KernelOptions::lookup` is set (link the generated `dispatch.cpp`).
* Interrupt delivery reads `ctx.cop0[12]`: EIE (16) and IE (0) set, EXL (1)/ERL (2) clear. `start` sets the main
  thread's Status to `main_status` (EIE clear until crt0's `ei` at `0x1001F8`, **inf**); created threads get
  `thread_status` (EIE set).
* The GS device owns `CSR` and must report `FIELD` (bit 13) from `bus().time().field`; SetVSyncFlag stores
  `read64(0x12001000)`. GsPutIMR writes `0x12001010` through the bus.
* SIF: `install_syscall(0x76..0x7A, …)`; SIF0 chain completion via `dma_complete(5)`.
* **Device services** (`Kernel::add_device_service(u64())`): a device's periodic work, returning the next cycle it
  needs (event `kEvService`; also run once at `start`, right after each VBLANK_START and after every installed
  syscall). The host registers `SifHle::service` + `next_event_cycles` here (runtime/app/game_host.cpp).
* **`Kernel::request_stop()`**: the running `run_until` returns `Stopped` at the next thread-level check point
  (before that point's interrupt delivery when requested from a service/event) — host stop conditions without a
  per-check-point predicate.
* **VU1 control**: `RtHooks::vu_control_write` (CTC2 to vi28 FBRST) goes to `Kernel::set_vu_control_handler`; the
  host maps bit 9 (RS1) to `GsSystem::vu1().reset()`.

## Choices and divergences (inf; Phase 4 checks)

Context frames (`KernelOptions::context_frames`, default on; obs from the BIOS, `docs/INTEGRATION_LOG.md` #4): the
positive switching set, SleepThread, WaitSema, Exit(Delete)Thread and interrupt-exit preemption save the full context
at the thread's `sp − 0x280` in the BIOS layout (`0x80003680`: SA, FCSR, ACC, GPR r at 16·r, HI/HI1/LO/LO1 at
416–447, gp/sp/fp/ra, FPRs at 512+); the frame's `$v0` is `$a0` (`move v0,a0` in the wrapper's delay slot) except
ChangeThreadPriority/ExitThread (unchanged) and SleepThread (the tid); `sd v0` writes results back
(ChangeThreadPriority, SleepThread, failed switching calls) and a released wait gets `sw −1` (so
`$v0 = 0x00000000FFFFFFFF`); a successful switching call and WaitSema — even on an invalid id — return the frame's
`$v0`. CreateThread/SetupThread/reset write gp/sp/fp/ra at `stack+size−0x2A0`, StartThread the argument at +64, and a
thread's first activation loads its registers from that frame. Not modelled: the frames the BIOS `i*` workers leave
on the caller's stack when called from thread context. `ReferThreadStatus` reports the entry address as PC.
Timer interrupts fire on the flag's 0→1 edge. VBLANK_END at +22 lines. DMA costs 64 + 2/qword. T3_MODE = 0 at boot
(CMPE clear → the alarm patch installs, as PCSX2 shows). D_ENABLER = 0x1201. OSD config word starts at 0. argv =
`{"cdrom0:\SLUS_216.21;1"}`. RemoveXxxHandler returns 0 on success; Enable/DisableXxxHandler return 0; void kernel
calls leave `$v0` unchanged. `EnableIntc`/`EnableDmac` with an out-of-range number return −1. Thread ids: main 1,
created from 2 (fast-boot order, `15` §3). Kernel table words other than those `SetSyscall` writes are zero in RAM
(PCSX2 has the BIOS kernel at 0x0-0x80000).

## Open questions

1. ~~A device timer API~~ — added as `Kernel::add_device_service` (integration, `docs/INTEGRATION_LOG.md` #9).
2. `syscall_cycles` (0) and the DMA costs are placeholders until PCSX2 measurements (ADR-0013 §2).
3. Whether hardware raises a timer interrupt on every match or only on the flag edge (the game clears the flags).
4. ExecPS2's argv string and the main thread's initial Status under PCSX2 (affect the args block bytes / early
   delivery during `_InitSys`).
