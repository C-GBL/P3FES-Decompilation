# 15 — EE kernel semantics (BIOS v02.30 USA, the ROM PCSX2 booted)

_Source: the user's own dump `tools/third_party/pcsx2/bios/ps2-0230a-20080220.bin` (not committed), analysed in `ida/work_bios_kernel.i64` (gitignored), built by `tools/ours/ida/open_bios_kernel.py`. No ROM bytes are reproduced here: findings are kernel VAs (kseg0) plus our own pseudocode. **obs** = read from the kernel instructions; **der** = obs combined with game-side facts from `10`/`12`; **inf** = inferred. Kernel-internal names (`k*`, `g_k*`) are ours._

## 0. ROM contents, kernel image and load address

`python -I tools/ours/ida/bios_romdir.py <bios>` (metadata only): image 4 MiB, ROMDIR table at ROM offset `0x2780`, **105 records**, `ROMVER = 0230AC20080220` (v02.30, region A = USA, C = console, 2008-02-20) — the BIOS PCSX2 reported as `USA v02.30(20/02/2008)` (`docs/PCSX2.md`). Entries in ROM order: `RESET 0x0 (0x2780)`, `ROMDIR`, `EXTINFO`, `SBIN`, `LOGO`, `IOPBTCONF`/`IOPBTCON2`, the IOP boot modules (`SYSMEM`, `LOADCORE`, `EXCEPMAN`, `INTRMANP/I`, `SSBUSC`, `TIMEMANP/I`, `DMACMAN`, `SYSCLIB`, `HEAPLIB`, `THREADMAN`, `VBLANK`, `IOMAN`, `MODLOAD`, `ROMDRV`, `ADDDRV`, `STDIO`, `SIFMAN`, `SIFINIT`), **`EENULL 0x40BE0 (0x40)`**, `EELOADCNF`, `LIBFI`, `PS1ID`/`PS1VER*`, `OSDVER`, `RDRAM`, `SIFCMD`, `REBOOT`, `LOADFILE`, `EESYNC`, `TZLIST`, `OSDCNF`, `IOPBOOT`, `TBIN`, `XLOADFILE`, `SECRMAN`, `SIO2MAN`, `EECONF`, `RMRESET`, `KROMG`, `KROM`, `ROMVER 0x7FF00`, `VERSTR`, `ROMGSCRT`, `NCDVDMAN`, `MCMAN`, `MCSERV`, `PADMAN`, `CDVDMAN`, `CDVDFSV`, `FILEIO`, `CLEARSPU`, `UDNL`, `IGREETING`, `TESTMODE`, **`EELOAD 0xD0FF0 (0xF190)`**, `TESTSPU`, `LIBSD`, `TSIO2MAN`, `TPADMAN`, `PS1DRV`, font/sound/texture/icon images, the `X*` module set, `OSDSND`, `PS2LOGO`, `XPARAM`, `OSDSYS 0x33A2F0 (0x5875C)`, **`KERNEL 0x392A50 (0x173E8)`**, padding, `DECKARD 0x3E0000 (0x20000)`. Full table (offsets, sizes, extinfo): `ida/logs/bios_romdir.json` (gitignored; regenerate with `--json`).

**EE kernel = `KERNEL`** (raw image, not ELF), **loaded at kseg0 `0x80000000`**, entry **`kernel_entry 0x80001000`** (obs):
* The ROM `RESET` code's EE path sets `$sp = 0x70003FF0` (scratchpad), calls a ROM routine, then `lui $t0,0x8000; ori $t0,0x1000; jr $t0` (ROM `0xBFC008E4–0xBFC008F4`); the `RESET` image contains the string `KERNEL` (ROM offset `0x1CA8`). That the routine copies `KERNEL` to `0x80000000` is inferred from the following self-consistency, not from reading the copy loop.
* The image is consistent only at that base: the R5900 vectors sit at image offsets `0x000/0x080/0x100/0x180/0x200`; `kvec_common 0x80000180` and `kvec_tlb_refill 0x80000000` index `kexc_code_table 0x80015900` by `Cause.ExcCode`, whose entries point at code in the image (`ksyscall_entry 0x80000280` for ExcCode 8, `kexc_default_handler 0x800146B8` for the rest); `kernel_entry`'s `jal`s land on function prologues (`0x80005C30`, `0x80002050`, `0x8000E0D0`, `0x80004EC0`, …).
* `kernel_entry` stores the RAM size RESET left at `0x70003FF0` into `g_kMemorySize 0x80017410` and ROM word `0xBFC001F8` into `g_kMachineType 0x80017400`; sets the kernel stack `0x80019440`; initialises TLB, interrupts (`kintr_init_all 0x80002050`), threads/semaphores (`kthread_init 0x80004EC0`), loads `Status`/`Config`; installs the interrupt-handler trampoline `0x81FE0` (`kSetIntrTrampoline 0x80001578`); `SetVSyncFlag(0, 0)`; creates thread **`EELOAD`** at `0x82000` with priority 0 (`kthread_create_from_rom 0x80005388`, which copies the named ROM file to the entry address) and launches it (`kthread_launch_first 0x80005140`, ending `di; eret`).
* `kthread_init` first creates the **idle thread (tid 0, priority 128)** from ROM file `EENULL`, copied to `0x81FC0`. `EENULL` is 16 words: an idle loop at `0x81FC0` and, at `0x81FE0`, the **user-mode interrupt-handler trampoline** (sets `$sp = 0x81FC0`, `jalr $v1`, then `syscall` with `$v1 = −5`).
* Not the EE kernel: `EELOAD` (EE loader; runs at `0x82000` as tid 1 and `ExecPS2`s the next program), `OSDSYS` (browser), `KROM`/`KROMG`/`DECKARD` (not examined; the names suggest PS1-mode firmware of this slim model — inf).

Kernel data lives past the image end (`kbss` segment `0x800173F0–0x80080000`).

## 1. Database and syscall table

`open_bios_kernel.py <bios> ida/work_bios_kernel.i64 [--rebuild]` loads `KERNEL` **in place** from the dump (no extraction), seeds the vectors and `kernel_entry`, recovers the four `sltiu`/`lw TBL`/`jr` switch tables IDA's MIPS module misses, splits fall-through entries, adds the runtime-installed entries (`kintc_dispatch_chain 0x80001630`, `kdmac_dispatch_chain 0x80001798`, `ksbus_dispatch 0x80001D58`, `kalarm_t3_dispatch 0x80002650`) and 87 unreached leaf stubs (e.g. the `GetCop0` stub table at `0x80002C58`), and applies 80 analyst names. Result: **428 functions; all 17,978 code words are inside functions** (log `ida/logs/bios_kernel_open.log`).

The syscall table is derived from the dispatcher, not guessed: `ksyscall_entry 0x80000280` does `sll $v1,$v1,2` then `lw $k0, 0x80015500($v1)` → **`ksyscall_table 0x80015500`, 256 slots** (`0x00–0xFF`). Every slot is named via `ps2_syscalls.py`; a slot serves both `+N` and `−N` (§7), so a slot whose only ps2sdk define is negative is named after it (`ksc_43_iSignalSema`, …). Listing: `ida/logs/bios_kernel_syscalls.txt`. Facts that matter (obs):
* Slots `0x00, 0x03, 0x08, 0x3F, 0x54–0x5B, 0x7C` → `ksc_unimplemented_stub 0x80001564` (prints `# Syscall: undefined (%d)`; `0x7C Deci2Call` is intercepted in `ksyscall_entry` before the table). Slots **`0x81–0xFF` are 0** (no handler) — including `0x83 FindAddress` and the alarm numbers `0xFC–0xFF`. `0x60–0x62` hold kseg1 aliases (`0xA0002C00`, …) of kseg0 code.
* `i*` pairs share one handler: `0x14/0x1A` … `0x17/0x1D`, `0x18/0x1E`, `0x19/0x1F`, `0x30/0x31`, `0x35/0x36`, `0x37/0x38`, `0x45/0x46`, `0x47/0x48`, `0x63/0x67`, `0x64/0x68`, `0x66/0x6A`. Where the positive call may block or switch, the positive slot is a thin wrapper (save context → `i*` worker → reschedule, §3) and the `i*` slot is the bare worker: positive `0x21/0x22/0x25/0x29/0x2B/0x2D/0x33/0x39/0x41/0x42` wrap `0x80003EF8/0x80003F68/0x80003DF8/0x80004280/0x80004380/0x800043C8/0x800046A8/0x800048B8/0x80004A40/0x80004BC0`.

## 2. Q-01 — INTC handler chain (**resolved from the dispatcher code**)

### 2.1 Interrupt entry/exit (obs)
`kvec_interrupt 0x80000200` saves `$sp/$ra/$at` (128-bit) at `kexc_save_sp_ra_at 0x800010C0`, takes the highest pending `Cause.IP` bit (`plzcw`) and jumps through `kint_ip_table 0x80015940`: IP2 → `kint_ip2_intc 0x80000380`, IP3 → `kint_ip3_dmac 0x800004C0`, IP7 → `kint_ip7_cop0_timer 0x80000600`. INTC path:
```
pending = INTC_STAT & INTC_MASK
if pending & (VU0|VU1) and VPU_STAT & 0x202: goto debug handler
Status &= ~(IE|EXL|KSU)          ; kernel mode, interrupts off      0x800003BC
sp = 0x80019440 (kernel stack); save EPC; kintr_save_gprs()         ; GPRs+HI/LO/HI1/LO1/SA -> 0x80001100, no FPRs
cause = index of highest set bit of pending                          0x800003E8
INTC_STAT = 1 << cause            ; acknowledged BEFORE dispatch     0x80000408
g_kNeedResched = 0
kintc_cause_dispatch_tbl[cause](cause)                               ; 0x80015980, filled by kintr_init_all
kintr_restore_gprs(); restore EPC, sp/ra/at
if g_kNeedResched: save context on the thread stack, pick, restore   ; 0x80000454 -> 0x8000363C
else: Status |= IE|EXL|KSU_user; eret
```
One cause per entry, **highest cause number first** (TIM3 12 > TIM2 11 > TIM0 9 > VBON 2); the remaining causes re-interrupt right after `eret`. DMAC (`0x800004C0`) is identical over `D_STAT[15:0] & (D_STAT[31:16] | 0x8000)`, ack `D_STAT = 1 << ch`, table `kdmac_chan_dispatch_tbl 0x800159C0`.

### 2.2 Handler lists (obs)
`kintr_init_all 0x80002050` installs `kintc_dispatch_chain 0x80001630` for causes 0–14 except 1 (`ksbus_dispatch`) and 12 (`kalarm_t3_dispatch`), and `kdmac_dispatch_chain` for channels 0–15. Each cause has a circular doubly-linked list with a sentinel `kintc_lists[c] = 0x80019458 + 12·c` `{L, R, count}`; forward order follows `R` (+4). Nodes come from one pool `khandler_nodes 0x800195D0` (24 bytes: `L, R, handler, gp, arg, mode`): **ids 1–128, shared by INTC and DMAC handlers**, FIFO free list `0x80019450`.

`AddIntcHandler(cause, handler, next, arg)` = `kintc_add_handler_core(…, mode=2) 0x800018B0`: `cause ≥ 15` or `cause == 1` → −1; no free node → −1; node `{handler, gp = caller's $gp, arg, mode 2}`; then `klist_insert_before(pos, node) 0x80005BA8` (links the node in front of `pos` in forward order) with

| `next` | `pos` | resulting position |
|---|---|---|
| `0` | current first node (`header.R`, load at `0x80001994`) | **head** — runs first |
| `−1` | the sentinel itself (`0x80001970`) | **tail** — runs last |
| `1..128` | node `next` (must be in use) | immediately **before** handler `next` |
| other | — | −1 |

then `count[cause]++` and the node id is returned. `RemoveIntcHandler(cause, id) 0x80001A70` validates only the id (1–128, in use), unlinks, frees, `count[cause]--`. `EnableIntcHandler/DisableIntcHandler(id) 0x80001FA0/0x80001FC8` set node mode 2 / 1 without validation. `AddDmacHandler` (`kdmac_add_handler_core 0x80001B10`, channels 0–15) is the same.

### 2.3 Dispatch and the return-value rule (obs)
```
kintc_dispatch_chain(cause):                                        ; 0x80001630
  if cause == 2 and g_kVSyncFlagPtr:                                ; SetVSyncFlag one-shot, BEFORE the handlers
      *g_kVSyncFlagPtr = 1; g_kVSyncFlagPtr = 0
      if g_kVSyncCsrPtr: *(u64*)g_kVSyncCsrPtr = GS_CSR; g_kVSyncCsrPtr = 0
  for node in list[cause] following R, count times:
      if node.mode == 2:                                            ; user handler
          gp = node.gp
          r = kcall_user_handler(node.handler, a0=cause, a1=node.arg, a2=EPC)   ; 0x80001704
          if r < 0: return                                          ; bgez at 0x8000170C: NEGATIVE STOPS the chain
      elif node.mode == 0: node.handler(cause)                      ; kernel-internal handler, result ignored
      ; mode 1 (DisableIntcHandler) is skipped
  if the list was empty: print "# INTC(%d) Handler does not exist." and KExit
```
`kcall_user_handler 0x80002840` saves the kernel `$ra/$sp` (`g_kIntrSavedRa/Sp 0x8001A7C0/0x8001A7D0`), sets `EPC = g_kIntrTrampoline` (`0x81FE0`), `$v1 = handler`, `Status |= EXL|KSU_user` with **IE still 0**, `eret`. The trampoline runs the handler **in user mode on the shared stack `0x81FC0`**, then `syscall −5` (`ResumeIntrDispatch 0x80002880`) returns into the dispatcher with `$v0` intact. Hence: **any negative return value stops the remaining handlers of that cause for this interrupt; 0 or positive continues.** Interrupts stay disabled for the whole chain (IE = 0); `ei`/`di` in a handler only change `Status.EIE` (legal in user mode because `kernel_entry` sets EDI) and cannot nest interrupts. DMAC handlers follow the same rule (`kdmac_dispatch_chain 0x80001798`, stop test at `0x80001824`).

### 2.4 Applied to the game's cause-2 list (der)
Installs (`10` §1.4, `12` §4.4): `_rwDMAVSYNCHandler` `next=0` → [RW]; `kwlnVsyncFieldGate` `next=0` → **[Gate, RW]**; `sceGsSyncVCallback(kwlnGsSyncVCallback)` `next=−1` → **[Gate, RW, Cb]**. Per VBLANK_START, the SetVSyncFlag work happens first (every vblank), then:
* `CSR.FIELD == 0`: Gate returns −1 → **RW and Cb do not run.**
* `CSR.FIELD == 1`: Gate returns 0 → RW (flip if one is pending; returns 0, `10` §2) → Cb (`ADXM_ExecVint`; returns 0).

So RW flips at most every second vblank: **≤ 30 flips/s at 60 vblanks/s, matching the observed FPS 30 / VPS 60** (`docs/PCSX2.md`). Side effect (der): the ADX vsync/fs threads are woken by `ADXPS2_ExecVint` only on odd fields (30 Hz), not every vblank as `12` §4.1 says. `10` §3.1's tentative reading ("0 terminates the chain, most-recent-first") is wrong; the K-04 caveat (RW must not be suppressed every vblank) holds — it is suppressed on even fields only.

## 3. Scheduler (obs unless marked)

**TCB** `ktcb 0x8001AC00`, 256 × 0x4C: `+0/+4` queue links, `+8` status (`0` free, `1` RUN, `2` READY, `4` WAIT, `8` SUSPEND, `0xC` WAITSUSPEND, `0x10` DORMANT), `+0xC` resume PC, `+0x10` saved-context pointer, `+0x14` gp, `+0x18/+0x1A` initial/current priority (s16), `+0x1C` wait type (1 sleep, 2 sema), `+0x20` wait id, `+0x24` wakeup count, `+0x30` entry, `+0x34` argc, `+0x38` arg, `+0x3C/+0x40` stack/size, `+0x44` return address for thread exit, `+0x48` heap end. Ready queues `kready_queues 0x8001A7F0`: **129 FIFO lists, priority 0 (highest) … 128 (idle only)**; `g_kTopReadyPrio 0x80015B70` caches the lowest non-empty index; `g_kCurrentTid 0x80015B6C`.

* **Ready insert** `kready_insert_tail 0x80005A58`: status READY, append at the **tail** of `queue[current priority]`, lower the cache if needed. The running thread **stays at the head of its queue** while it runs.
* **Pick** `ksched_preempt 0x8000394C(epc, ctx)`: store the outgoing thread's PC/context and mark it READY (it is still queued), scan from the cached priority to 128, take the **head** of the first non-empty queue, mark it RUN; **if its wait type is still set, clear it and force its saved `$v0 = −1`** (released waits, §4). Empty → `# <Thread> No active threads`, KExit.
* **Positive switching syscalls** (`0x21 0x22 0x25 0x29 0x2B 0x2D 0x33 0x39 0x41 0x42`) = `kctx_save_on_thread_stack 0x80003680` (full context incl. FPRs, FCSR and ACC at `sp − 0x280` on the **caller's own stack**) → worker → if the result is ≥ 0 **always pick** (immediate preemption or yield), else return the error in `$v0`. `SleepThread 0x800032C0` and `WaitSema 0x80003440` block through `ksched_block 0x80003A84` (leave the ready queue, status WAIT, wait type 1/2, pick).
* **Preemption after an interrupt**: `i*` workers set `g_kNeedResched 0x80015B74` when they ready a thread of strictly higher priority than `g_kTopReadyPrio`; the INTC/DMAC exits (`0x80000454`, `0x80000598`) then switch threads before `eret`. The flag is cleared at every interrupt entry (`0x80000410`), so an `i*` call made from **thread** context never preempts.

| Call | Kernel behaviour |
|---|---|
| `CreateThread(p) 0x80003C50` | TCB from the FIFO free list (none → −1); DORMANT; entry `p+4`, stack `p+8`, size `p+0xC`, gp `p+0x10`, priority `p+0x14` (**not range-checked**); context at `stack+size−0x2A0` with `sp = fp = stack+size−0x20`, `ra =` creator's `+0x44`; wakeup count 0; **heap end inherited** from the creator. Returns tid. |
| `StartThread(tid, arg) 0x80003F68` | tid 1–255, not self, DORMANT, else −1; `a0 = arg`; READY (tail); positive form picks immediately. Returns tid. |
| thread entry returns | jumps to `ra = +0x44` = `SetupThread`'s `root_func` (the game's `0x100220`, `ExitThread`), inherited by every thread. |
| `ExitThread 0x80003FF0` | leave the ready queue; `kthread_reset_dormant 0x80003BB8` (DORMANT, PC = entry, priority = initial, fresh context); pick. Restartable by `StartThread`. |
| `ExitDeleteThread 0x80004108` | as Exit, then the TCB is freed (appended to the free list). |
| `TerminateThread(tid) 0x80003DF8` | READY / WAIT / SUSPEND / WAITSUSPEND → removed (sema waiter count fixed) → DORMANT, returns tid; RUN (= self) → −1 (and sets the resched flag); DORMANT/free → −1. |
| `DeleteThread(tid) 0x80003EF8` | DORMANT and not self only, else −1. |
| `ChangeThreadPriority(tid, p) 0x80004280` | tid 0 = self; **p 0–127**, else −1; DORMANT → −1; READY/RUN → removed and re-appended at the **tail** of `p`; WAIT/SUSPEND → field only. Returns the **old** priority; positive form picks, so `ChangeThreadPriority(self, same)` **yields** to equal-priority peers and lowering below a ready thread switches at once. |
| `RotateThreadReadyQueue(p) 0x80004380` | p 0–127; head of `queue[p]` → tail (no-op if empty); returns p; positive form picks. The `i` form does **not** set the resched flag. |
| `SleepThread 0x800032C0` | wakeup count > 0 → count−1, return tid at once; else WAIT(1). A normal wake returns tid. |
| `WakeupThread(tid)` / `iWakeupThread 0x800046A8` | tid 0 = self; WAIT on sleep → READY (wait cleared); WAITSUSPEND on sleep → SUSPEND; READY, SUSPEND, or waiting on a semaphore → **count+1** (unbounded); **RUN → −1 and nothing is recorded** (an interrupt waking the thread it interrupted is lost; libkernel's `iWakeupThread 0x504028` defers exactly that case to `topThread`); DORMANT/free → −1. |
| `CancelWakeupThread(tid) 0x80004968` | returns the count and clears it (tid 0 = self). |
| `SuspendThread(tid) 0x80004800` (same slot as `i`) | tid 1–255; READY/RUN → removed from the queue, SUSPEND; WAIT → WAITSUSPEND; else −1. **No reschedule**: suspending self leaves the thread running while unqueued, and the next pick marks it READY outside any queue — must never happen. |
| `ResumeThread 0x800048B8` | not self; SUSPEND → READY (tail); WAITSUSPEND → WAIT; else −1; positive form picks. |
| `ReleaseWaitThread 0x800043C8` | WAIT → READY (sema waiter dequeued), WAITSUSPEND → SUSPEND; the wait type stays set, so the released call returns **−1**. |
| `ReferThreadStatus(tid, info) 0x80004550` | tid 0 = self; `info == NULL` → returns the status only; else fills `{status, PC (+0xC), stack, stack_size, gp, init_prio, cur_prio, attr (+0x28), option (+0x2C), waitType, waitId, wakeupCount}` and returns the status. |
| `GetThreadId 0x80004540` | `g_kCurrentTid`. |
| `Disable/EnableDispatchThread 0x80004220/0x80004250` | print "not supported in this version", return the current tid. |
| `SetupThread(gp, stack, size, args, root) 0x80005190` | `stack == −1` → `stack = MemSize − 0x1000 − size`; writes the caller's TCB (gp, stack, size, `+0x44 = root`), builds a context at `stack+size−0x2A0`, copies ExecPS2's argc/argv into `args` as `{argc, argv[16], strings}` (`kthread_copy_args 0x80004FA8`); **returns `stack+size−0x2A0`** (crt0's new `$sp`). |
| `SetupHeap(start, size) 0x80005298` / `EndOfHeap 0x800052D0` | `size ≥ 0` → end = start+size; **`size < 0` → end = the thread's stack base**; returns the end; EndOfHeap returns it (per TCB, inherited by CreateThread). |
| `ExecPS2` (`kExecPS2_core 0x800057E0`) | the caller keeps its tid and gets priority **0**, wakeups cancelled; every other thread except idle is terminated/deleted; semaphores and the INTC/DMAC lists (except SBUS) are reset. ⇒ the game's main thread starts at **priority 0**; it is tid 1 on the EELOAD path (inf). |

Ids: semaphores restart at **0** after ExecPS2 (deterministic). Thread ids come from a FIFO free list whose order depends on boot history (fast boot: first `CreateThread` = 2, inf) — the HLE must not depend on exact values.

## 4. Semaphores (obs)

`ksema 0x8001F800`, 256 × 32 bytes: `+0` free link, `+4` count (−1 = free/deleted), `+8` max, `+0xC` attr, `+0x10` option, `+0x14` waiter count, `+0x18` FIFO wait queue. `ksema_init 0x80004E60` (boot and every ExecPS2) frees all; the free list hands out ids **0, 1, 2, …**.
* `CreateSema(p) 0x800049B8`: none free or `init_count (p+8) < 0` → −1; count = init, max = `p+4` (**not validated, never enforced**), attr `p+0x10`, option `p+0x14`. Returns the id.
* `WaitSema(id)` (`kWaitSema_core 0x80004CF0`): invalid/deleted → −1; count > 0 → count−1, return id; else waiter count+1, append the caller to the **FIFO** queue (attr ignored — no priority ordering) and block. A normal wake returns **id**; a wake by DeleteSema or ReleaseWaitThread returns **−1**.
* `SignalSema/iSignalSema(id) 0x80004BC0`: invalid → −1; waiters present → pop the **first** waiter (count unchanged), WAIT → READY (+resched flag if higher priority), WAITSUSPEND → SUSPEND; no waiters → **count+1 with no clamp to max**. Returns the id.
* `PollSema/iPollSema 0x80004DC0`: count > 0 → count−1, return id; else −1.
* `DeleteSema/iDeleteSema 0x80004A40`: invalid → −1; release every waiter in FIFO order (they return −1); count = −1; back onto the free list. Returns the id.
* `ReferSemaStatus 0x80004DF8`: writes `{count, max, —, wait_threads, attr, option}` (`+8` untouched); returns the id.

## 5. Alarms and timers

* **Stock kernel alarms (obs)**: `_SetAlarm`/`_iSetAlarm` (slots 0x18/0x1E, `0x800022D8`) and `_ReleaseAlarm`/`_iReleaseAlarm` (0x19/0x1F, `0x80002570`) run on **Timer 3 counting H-blanks** (`T3_MODE = 0x183`: CLKS = HBLANK, CUE, CMPE). `SetAlarm(time, handler, arg)`: 64 slots (bitmap `kalarm_bitmap 0x8001A268`), 16-bit target = (T3_COUNT + time) mod 2^16, kept sorted; the earliest target goes into `T3_COMP`; returns the slot id or −1. `ReleaseAlarm(id)`: unknown → −1; clears CMPE when no alarm remains; returns the elapsed H-lines. INTC cause 12 → `kalarm_t3_dispatch 0x80002650`: re-arms the next target, pops due alarms and runs each handler through the user trampoline as `handler(id, target, arg)` with the setter's gp. Units: H-lines (NTSC ≈ 15.73 kHz). Slots 0xFC–0xFF are empty in this ROM.
* **The game's alarm patch (der)**: `T3_MODE.CMPE` is set only while a kernel alarm is pending, so `InitAlarm 0x50DB38` reads it clear and installs the patch — on real hardware as under PCSX2 (answers `PCSX2.md`'s "PCSX2 may not model CMPE" doubt; inf for real hardware). In behaviour terms the patch (a) fills the empty slots 0xFC/0xFD/0xFE/0xFF with libkernel's own `SetAlarm/iSetAlarm/ReleaseAlarm/iReleaseAlarm` (code copied to `0x80076000`); (b) its `SetSyscall(0x12C, X)` writes `ksyscall_table + 0x4B0 = 0x800159B0` = **`kintc_cause_dispatch_tbl[12]`**, replacing the kernel's T3 dispatcher with the patch's; (c) `SetSyscall(0x08, X)` fills the empty slot 8 (`ResumeT3IntrDispatch`), the return path of the 40-byte user stub at `0x82000` (same shape as the `EENULL` trampoline, inf from `12` §5). The payload internals were not analysed. No game code calls 0xFC–0xFF and T3 is never armed, so the patch never runs after install.
* The game's own timers are T0 (`kwlnT0OverflowHandler`, cause 9) and libkernel's T2 alarm engine (cause 11) — kernel-wise just two more INTC causes (§2).

## 6. GS, VSync, OSD config (obs)

* `SetGsCrt(interlace, mode, ffmd) 0x8000C3D0`: mode 0/1 resolve to NTSC (2) or PAL (3) from ROM region data; spins ~10k iterations; branches on the GS revision (`CSR[23:16]`); for NTSC writes `SMODE1 0x12000010` twice, then `0x12000020`, `0x12000030`, `0x12000040` (the interlace flag selects between two values of the last; `ffmd` is OR-ed into the SMODE1 words), then `SMODE1` twice more. Field-level decode of these privileged writes: **open** (not needed by the HLE; FIELD toggling is GS hardware).
* `GsGetIMR 0x80000D00` returns the kernel's cached copy `g_kGsIMR 0x80017408`, never the register; `GsPutIMR 0x80000D40` writes `0x12001010` and the cache and returns the value.
* `SetVSyncFlag(flag, csr) 0x80001588`: stores two pointers; consumed at the next VBON before any cause-2 handler (§2.3): `*flag = 1`, `*(u64*)csr = GS_CSR`; one-shot.
* `_GetGsDxDyOffset(mode, &dx1, &dy1, &dx2, &dy2) 0x8000D2C0`: GS revision `< 0x19` → all 0; else NTSC/PAL (and 20 other mode numbers) → `dx1 = −4`, the rest 0.
* `Get/SetOsdConfigParam 0x8000DA08/0x8000DAB8`: copy the whole 32-bit word to/from `g_kOsdConfigParam 0x80022B50` (bits 0, 1–2, 3, 4, 5–12, **13–15** field by field, then bits 16–31). Bits 13–15 round-trip, so `PatchIsNeeded 0x50D718` reads back what it wrote → the ExecPS2 patch is not installed (matches PCSX2).
* `MachineType 0x80000BC0` → `g_kMachineType` (ROM word `0xBFC001F8`, 0 in this dump); `PSMode 0x80000B80` ORs bit 15 into it; `GetMemorySize 0x80000C40` → the RAM size RESET measured.
* `FlushCache(mode) 0x80002A40`: 0 → D-cache writeback+invalidate, 1 → D-cache invalidate, 2 → I-cache invalidate, otherwise both.

## 7. Dispatch, SetSyscall and the libkernel patch hooks (obs)

```
ksyscall_entry:                                                     ; 0x80000280
  if (s32)v1 < 0: v1 = -v1                                          ; bltzl / negu
      ; NEGATIVE path 0x8000032C: Status untouched (EXL stays 1: kernel level, interrupts off),
      ; caller's own stack, EPC += 4, call table[v1], eret; no reschedule
  elif v1 == 0x7C: Deci2Call path
  else: save sp/ra/at; Status &= ~(IE|EXL|KSU); kernel stack 0x80019440; EPC += 4
        call table[v1](a0, a1, ...); Status |= IE|EXL|KSU_user; eret
```
* Negative numbers are the interrupt-context forms: same slot, executed at exception level on the current stack. A **positive** syscall from a user interrupt handler would reuse the kernel stack the dispatcher is running on — only `i*` (negative) calls are legal there.
* `SetSyscall(n, addr) 0x800006C0`: `ksyscall_table[n] = addr` — **no bounds check, no return value**. So `n ≥ 0x100` patches kernel data (0x12C → INTC cause-12 dispatcher) and a negative `n` patches kernel code (libkernel's `0xFFFFC402` → `0x80006508`, only when `PatchIsNeeded`).
* `Copy (0x5A)`, `GetEntryAddress (0x5B)`, `xlaunch (0x54)` and TLB `0x55–0x59` are **undefined in this ROM**; they exist only after libkernel's `SetSyscall` installs its own kernel-mode routines (`12` §5). The `FindAddress (0x83)` slot is **0** until libkernel installs `kFindAddress`. Inf: `12` §5's search range `0x80000000–0x80010000` does not contain this kernel's table (`0x80015500`), so libkernel's `GetSystemCallEntry` lookup finds nothing here (harmless: unused).
* Hazard (obs; consequence inf): the undefined-syscall stub falls through into `kSetIntrTrampoline 0x80001578` after its `printf`, storing whatever `$a0` the printf left into `g_kIntrTrampoline` — an undefined syscall can break every later user interrupt handler. libkernel always installs before calling, so the game never hits it.

## 8. HLE rules

| # | Rule | K-row |
|---|---|---|
| H-01 | Per-cause / per-channel ordered handler lists: `next = 0` → head, `−1` → tail, `id` → immediately before `id`; ids 1–128 from one pool shared by INTC and DMAC; `cause ≥ 15` or 1 → −1 | K-04, K-05 |
| H-02 | Dispatch walks head → tail; a handler returning **< 0 stops** the cause's remaining handlers, ≥ 0 continues; the handler gets `(cause or channel, arg, EPC)` and the registrant's `$gp` | K-04, K-05 |
| H-03 | The game's cause-2 order is [field gate, RW, GsSyncV callback]; RW and the ADX callback run only on `CSR.FIELD == 1` → 30 flips/s at 60 Hz (Q-01) | K-04, K-50 |
| H-04 | One cause per interrupt, highest cause/channel number first; ack the `INTC_STAT`/`D_STAT` bit **before** calling handlers; handlers run with interrupts disabled (`ei`/`di` only touch EIE; no nesting) | K-50, K-51, K-52 |
| H-05 | The real kernel does not preserve FPRs/FCSR across interrupts (only GPRs/HI/LO/SA); the HLE may save everything | K-50 |
| H-06 | `SetVSyncFlag`: at the next VBON, before the handlers and regardless of their results, `*flag = 1`, `*csr = GS_CSR` (u64), then forget both | K-09 |
| H-07 | `EnableIntc/Dmac` return 1 if the mask bit changed, 0 if already set; `Disable*` return 1 if it was set; mask writes toggle | K-06 |
| H-08 | Thread priorities 0 (highest) … 127 (128 = idle); FIFO per priority; the running thread stays at the head; pick = head of the lowest non-empty queue | K-07 |
| H-09 | Every successful positive call in the switching set reschedules immediately; `i*` forms only flag a reschedule (taken at interrupt exit, only for a strictly higher priority) and never preempt from thread context | K-07, K-08 |
| H-10 | `ChangeThreadPriority` re-appends READY/RUN threads at the tail (same priority = yield), returns the old priority, rejects DORMANT and p ≥ 128 | K-07 |
| H-11 | Wakeup counts: waking a READY/SUSPEND/sema-waiting thread increments (unbounded); `SleepThread` consumes one; **waking the RUN thread returns −1 and is lost** | K-07 |
| H-12 | Thread entry return → `root_func` from `SetupThread` (inherited) → `ExitThread` → DORMANT (restartable, priority reset) | K-07, K-15 |
| H-13 | `SetupThread` returns `stack+size−0x2A0`; `stack == −1` → top of RAM − 4 KiB; argv block `{argc, argv[16], strings}` | K-01 |
| H-14 | `SetupHeap(x, −1)` → `EndOfHeap` = the main thread's stack base; heap end inherited by created threads | K-01 |
| H-15 | The main thread starts at priority 0 (ExecPS2); semaphore ids start at 0 | K-07, K-08 |
| H-16 | Semaphores: init ≥ 0 required; **max never enforced** (Signal without waiters always count+1); waiters FIFO, attr ignored; Signal hands the unit to the first waiter; Wait returns the id, −1 if the sema is deleted or the wait released | K-08 |
| H-17 | `SuspendThread` never reschedules — trap self-suspension; `TerminateThread(self)` → −1 | K-07 |
| H-18 | `SetSyscall(n, a)` records into a 256-entry table without bounds checks: n = 0x12C replaces the INTC cause-12 dispatcher, negative n patches kernel code — accept and record; trap if INTC cause 12 is ever enabled/pending | K-11, K-48 |
| H-19 | `Copy`/`GetEntryAddress`/`xlaunch`/`FindAddress` exist only via libkernel's `SetSyscall`; slots 0x81–0xFF are empty and undefined numbers print-and-corrupt — trap any syscall whose slot was never installed | K-11, K-40, K-44 |
| H-20 | Alarm patch: installed (T3 CMPE is clear at boot), never executed; trap 0xFC–0xFF | K-48 |
| H-21 | `GsGetIMR` returns the last `GsPutIMR` value (a cached copy) | K-03 |
| H-22 | `Get/SetOsdConfigParam` store/return the 32-bit word verbatim (bits 13–15 round-trip) | K-12 |
| H-23 | `_GetGsDxDyOffset`: 0 offsets if the emulated GS revision is `< 0x19`, else NTSC `dx1 = −4`; choose the revision deliberately (Q-03) | K-13 |
| H-24 | `MachineType` → 0 (bit 15 set after `PSMode`); `GetMemorySize` → RAM size | K-23 |
| H-25 | `FlushCache`, any mode → no-op | K-10 |

## 9. Confidence and open items
* The Q-01 rule (insert positions, walk order, stop-on-negative), thread/semaphore semantics and the dispatch paths: **obs** (instructions read in `ida/work_bios_kernel.i64`). Game-level cadence (§2.4): **der** from `10`'s gate/RW return values; consistent with PCSX2's FPS 30 / VPS 60.
* Open: SetGsCrt field decode; libkernel alarm-payload internals; exact thread ids after an OSD boot; whether the kernel printf preserves `$a0` (§7 hazard); the GS revision PCSX2 reports (H-23).
