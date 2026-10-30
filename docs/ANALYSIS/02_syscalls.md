# 02 — EE kernel syscall sites

## Provenance of the numbering

* Kernel names come from **ps2sdk `ee/kernel/include/syscallnr.h`** (`tools/third_party/ps2sdk/`, commit `329e2bb4`, 2026-10-12), parsed by `tools/ours/ida/ps2_syscalls.py` at export time; nothing is hand-typed into the table. The brief's original example numbers (0x3C CreateThread, 0x3E StartThread, 0x3F ExitThread, 0x0A ResetEE, 0x18 Exit) were wrong and were **not** used; the header puts CreateThread/StartThread/ExitThread at 0x20/0x22/0x23, ResetEE at 0x01, KExit at 0x04.
* The "PCSX2/ps2tek name if different" column shows naming disagreements only — no *numeric* disagreement exists between the two sources for any number this binary uses (both have `FlushCache=0x64`, `SetSyscall=0x74`, `SetVSyncFlag=0x73`, `SetPgifHandler=0x72`, `_print=0x75`).
* Sign: `li $v1,-N` is recorded in the `neg form` column, never dropped. ps2sdk defines the interrupt-context variants as negative numbers (`__NR_iSignalSema (-0x43)`), and the kernel dispatches on the magnitude.

## Empirical checks against the ELF (observed)

| Check | Where | Result |
|---|---|---|
| `SetupThread` = 0x3C | `0x1001a4..0x1001c8` loads `(gp, stack, stack_size, args, root_func)` then `li $v1,0x3C; syscall; move $sp,$v0` | argument shape and `$sp` result match ps2sdk `crt0.s`; 0x3C is not CreateThread |
| `SetupHeap` = 0x3D | `0x1001d8..0x1001e4`: `(0x9ACC80 = _end, -1)` | matches crt0 |
| `FlushCache` = 0x64 | `0x1001f0` calls `0x5033E0` (`li $v1,0x64`) with `$a0 = 0` | matches crt0 `FlushCache(0)`; 0x64 is not KSeg0 |
| `SetSyscall` = 0x74 (not 0x73) | wrapper `0x50D6B0` (`li $v1,0x74`) is called from `0x50D780` with `$a0 = *0x780380 = 0x5A`, `$a1 = *0x780384 = 0x50D6D0`; next table entry `(0x5B, 0x80074000)` | `(syscall_number, handler)` argument pair; `0x50D6D0` is a word-copy loop, which is exactly what the header names syscall 0x5A (`Copy`); `0x5B` = `GetEntryAddress` gets a kernel-space handler. Behaviour confirms 0x74 = SetSyscall and 0x5A/0x5B naming. Inferred: this is libkernel `_InitSys` patching the kernel. |
| negative = `i*` variant | `0x503400/0x503410/0x503420` = `-0x67/-0x68/-0x6A`, sitting between the `0x66` and `0x6B` wrappers | header defines exactly `iGetCop0 (-0x67)`, `iFlushCache (-0x68)`, `iCpuConfig (-0x6a)` |
| `ExitThread` = 0x23 | `0x100220` = `li $v1,0x23; syscall; nop; nop`, passed as crt0 `root_func` | thread root returns -> ExitThread, as in crt0 |

## Wrapper pattern and naming

* Thin wrapper = a 16-byte function `li $v1,N ; syscall ; jr $ra ; nop` (74 instances) or `li ; syscall ; nop ; nop` (1: the crt0 root `0x100220`). 75 wrappers were named `_sce<KernelName>`; names already starting with `sce`/`isce` get only the underscore (`_sceSifSetDma`, `_isceSifSetDma`). Negative-number wrappers take the header's negative define (`_sceiSignalSema`, `_sce_iWakeupThread`) or `i` + name when only the positive define exists (source `ps2sdk+i`). Duplicates get IDA's `_0.._3` suffix (e.g. four `_sceCopy_*`, four `_sceSetSyscall_*` — repeated libkernel shim objects).
* The remaining sites are `syscall`s inlined in larger functions (crt0's two, intc/dmac handler code around `0x4f9xxx`–`0x51xxxx`, the `_InitSys` family). They are listed individually in the generated table with their containing function.
* Coverage is unusual: essentially every table entry 0x00–0x83 appears once, i.e. the **entire SCE libkernel syscall surface was linked** (the MW linker did not drop unused objects). Only a fraction will ever execute; which ones is a Phase 4 trace question.
* 0xFD is used in positive form (`li $v1,0xFD`) while ps2sdk only defines `-0xfd` (`iSetAlarm`); 0xFC/`-0xFE`/`-0xFF` are the alarm family. Reported as `unknown_syscall_FD` with the hint, not guessed.
* Hex-Rays renders every `syscall` as `__asm { syscall }` and loses `$v1` (see 04). **The recompiler/runtime must take syscall numbers from this scan (the preceding `li $v1`), never from pseudocode.**

## Reconciliation with `runtime/include/p3fes/syscalls.h` (for the lead; file is owned by the runtime agent)

* Numbers agree wherever both define a name. Naming differences: runtime `InitMainThread/InitHeap` vs header `RFU060/RFU061` (= `SetupThread/SetupHeap`); runtime `Exit` (0x04) vs header `KExit`; runtime `iWakeupThread = 0x34` vs header `_iWakeupThread (-0x34)` — the ELF uses the **negative** form at its wrapper.
* The ELF uses many numbers the runtime header lacks: 0x00, 0x03, 0x05, 0x08–0x0F, 0x1A–0x1D (neg), 0x26–0x28, 0x2A, 0x2C, 0x2E, 0x31, 0x36, 0x38, 0x3A, 0x3B, 0x3F, 0x46, 0x48–0x4F, 0x50–0x5B (event flags, TLB, `Copy`, `GetEntryAddress`), 0x5C–0x63, 0x66–0x6F, 0x72, 0x75, 0x7B, 0x7D, 0x80, 0x82, 0x83, 0xFC–0xFF. Presence does not imply use; the runtime should at least trap them with a named diagnostic rather than silently fall through.

## Generated data

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-21 06:38:58 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

Syscall sites (code `syscall` opcode with a `li $v1,N` within 6 preceding instructions, or inside a function): **168**. Thin wrappers (`li $v1,N ; syscall ; jr $ra ; nop` or `li ; syscall ; nop ; nop`, exactly 16 bytes): **159**, renamed this run: 0. Code-flagged `syscall` opcodes outside any function with no `li $v1` (mis-disassembled data): 5 (listed in `ida/logs/syscall_sites.txt`).

Name authority: ps2sdk syscallnr.h (F:\P3FES-PORT\p3fes-port\tools\third_party\ps2sdk\ee\kernel\include\syscallnr.h). Source column: `ps2sdk` = exact `__NR_` define incl. sign; `ps2sdk+i` = positive define exists, negative form inferred as its interrupt-context variant; `pcsx2` = fallback table only. Sites using the negative form: 41.

### Distinct syscall numbers used

| N (hex) | neg form | Kernel name | Source | PCSX2/ps2tek name if different | Sites |
|---|---|---|---|---|---|
| 0x00 |  | `RFU000_FullReset` | pcsx2 |  | 1 |
| 0x01 |  | `ResetEE` | ps2sdk |  | 1 |
| 0x02 |  | `loc_502D60` | ps2sdk |  | 1 |
| 0x03 |  | `RFU003` | pcsx2 |  | 1 |
| 0x04 |  | `KExit` | ps2sdk | `Exit` | 1 |
| 0x05 |  | `ResumeIntrDispatch` | ps2sdk | `RFU005` | 1 |
| 0x06 |  | `loc_502DA0` | ps2sdk |  | 1 |
| 0x07 |  | `_ExecPS2` | ps2sdk |  | 1 |
| 0x08 |  | `ResumeT3IntrDispatch` | ps2sdk | `RFU008` | 1 |
| 0x09 |  | `RFU009` | ps2sdk |  | 1 |
| 0x0a |  | `AddSbusIntcHandler` | ps2sdk |  | 1 |
| 0x0b |  | `RemoveSbusIntcHandler` | ps2sdk |  | 1 |
| 0x0c |  | `Interrupt2Iop` | ps2sdk |  | 1 |
| 0x0d |  | `SetVTLBRefillHandler` | ps2sdk |  | 1 |
| 0x0e |  | `SetVCommonHandler` | ps2sdk |  | 1 |
| 0x0f |  | `SetVInterruptHandler` | ps2sdk |  | 1 |
| 0x10 |  | `AddIntcHandler` | ps2sdk |  | 2 |
| 0x11 |  | `RemoveIntcHandler` | ps2sdk |  | 1 |
| 0x12 |  | `AddDmacHandler` | ps2sdk |  | 2 |
| 0x13 |  | `RemoveDmacHandler` | ps2sdk |  | 1 |
| 0x14 |  | `_EnableIntc` | ps2sdk |  | 1 |
| 0x15 |  | `_DisableIntc` | ps2sdk |  | 1 |
| 0x16 |  | `_EnableDmac` | ps2sdk |  | 1 |
| 0x17 |  | `_DisableDmac` | ps2sdk |  | 1 |
| 0x1a | yes | `_iEnableIntc` | ps2sdk |  | 1 |
| 0x1b | yes | `_iDisableIntc` | ps2sdk |  | 1 |
| 0x1c | yes | `_iEnableDmac` | ps2sdk |  | 1 |
| 0x1d | yes | `_iDisableDmac` | ps2sdk |  | 1 |
| 0x20 |  | `CreateThread` | ps2sdk |  | 1 |
| 0x21 |  | `DeleteThread` | ps2sdk |  | 1 |
| 0x22 |  | `StartThread` | ps2sdk |  | 1 |
| 0x23 |  | `ExitThread` | ps2sdk |  | 2 |
| 0x24 |  | `ExitDeleteThread` | ps2sdk |  | 1 |
| 0x25 |  | `TerminateThread` | ps2sdk |  | 1 |
| 0x26 | yes | `iTerminateThread` | ps2sdk |  | 1 |
| 0x27 |  | `DisableDispatchThread` | ps2sdk |  | 1 |
| 0x28 |  | `EnableDispatchThread` | ps2sdk |  | 1 |
| 0x29 |  | `ChangeThreadPriority` | ps2sdk |  | 1 |
| 0x2a | yes | `iChangeThreadPriority` | ps2sdk |  | 1 |
| 0x2b |  | `RotateThreadReadyQueue` | ps2sdk |  | 1 |
| 0x2c | yes | `_iRotateThreadReadyQueue` | ps2sdk | `iRotateThreadReadyQueue` | 1 |
| 0x2d |  | `ReleaseWaitThread` | ps2sdk |  | 1 |
| 0x2e | yes | `iReleaseWaitThread` | ps2sdk |  | 1 |
| 0x2f |  | `GetThreadId` | ps2sdk |  | 1 |
| 0x2f | yes | `_iGetThreadId` | ps2sdk |  | 2 |
| 0x30 |  | `ReferThreadStatus` | ps2sdk |  | 1 |
| 0x31 | yes | `iReferThreadStatus` | ps2sdk |  | 1 |
| 0x32 |  | `SleepThread` | ps2sdk |  | 1 |
| 0x33 |  | `WakeupThread` | ps2sdk |  | 1 |
| 0x34 | yes | `_iWakeupThread` | ps2sdk |  | 1 |
| 0x35 |  | `CancelWakeupThread` | ps2sdk |  | 1 |
| 0x36 | yes | `iCancelWakeupThread` | ps2sdk |  | 1 |
| 0x37 |  | `SuspendThread` | ps2sdk |  | 1 |
| 0x38 | yes | `_iSuspendThread` | ps2sdk |  | 1 |
| 0x39 |  | `ResumeThread` | ps2sdk |  | 1 |
| 0x3a | yes | `iResumeThread` | ps2sdk |  | 1 |
| 0x3b |  | `RFU059` | ps2sdk | `JoinThread` | 1 |
| 0x3c |  | `RFU060` | ps2sdk | `RFU060_SetupThread` | 2 |
| 0x3d |  | `RFU061` | ps2sdk | `RFU061_SetupHeap` | 2 |
| 0x3e |  | `EndOfHeap` | ps2sdk |  | 1 |
| 0x3f |  | `RFU063` | pcsx2 |  | 1 |
| 0x40 |  | `CreateSema` | ps2sdk |  | 1 |
| 0x41 |  | `DeleteSema` | ps2sdk |  | 1 |
| 0x42 |  | `SignalSema` | ps2sdk |  | 1 |
| 0x43 | yes | `iSignalSema` | ps2sdk |  | 1 |
| 0x44 |  | `WaitSema` | ps2sdk |  | 1 |
| 0x45 |  | `PollSema` | ps2sdk |  | 1 |
| 0x46 | yes | `iPollSema` | ps2sdk |  | 1 |
| 0x47 |  | `ReferSemaStatus` | ps2sdk |  | 1 |
| 0x48 | yes | `iReferSemaStatus` | ps2sdk |  | 1 |
| 0x49 |  | `unknown_syscall_49` | unknown (ps2sdk defines only -0x49 = iDeleteSema) | `RFU073_iDeleteSema` | 1 |
| 0x4a |  | `SetOsdConfigParam` | ps2sdk |  | 1 |
| 0x4b |  | `GetOsdConfigParam` | ps2sdk |  | 1 |
| 0x4c |  | `GetGsHParam` | ps2sdk |  | 1 |
| 0x4d |  | `GetGsVParam` | ps2sdk |  | 1 |
| 0x4e |  | `SetGsHParam` | ps2sdk |  | 1 |
| 0x4f |  | `SetGsVParam` | ps2sdk |  | 1 |
| 0x50 |  | `CreateEventFlag` | ps2sdk |  | 1 |
| 0x51 |  | `DeleteEventFlag` | ps2sdk |  | 1 |
| 0x52 |  | `SetEventFlag` | ps2sdk |  | 1 |
| 0x53 | yes | `iSetEventFlag` | ps2sdk | `RFU083_iSetEventFlag` | 1 |
| 0x54 |  | `xlaunch` | ps2sdk | `RFU084_ClearEventFlag` | 1 |
| 0x54 | yes | `ixlaunch` | ps2sdk+i | `RFU084_ClearEventFlag` | 1 |
| 0x55 |  | `PutTLBEntry` | ps2sdk | `RFU085_iClearEventFlag` | 1 |
| 0x55 | yes | `iPutTLBEntry` | ps2sdk | `RFU085_iClearEventFlag` | 2 |
| 0x56 |  | `_SetTLBEntry` | ps2sdk | `RFU086_WaitEventFlag` | 2 |
| 0x56 | yes | `iSetTLBEntry` | ps2sdk | `RFU086_WaitEventFlag` | 1 |
| 0x57 |  | `GetTLBEntry` | ps2sdk | `RFU087_PollEventFlag` | 2 |
| 0x57 | yes | `iGetTLBEntry` | ps2sdk | `RFU087_PollEventFlag` | 1 |
| 0x58 |  | `ProbeTLBEntry` | ps2sdk | `RFU088_iPollEventFlag` | 1 |
| 0x58 | yes | `iProbeTLBEntry` | ps2sdk | `RFU088_iPollEventFlag` | 2 |
| 0x59 |  | `ExpandScratchPad` | ps2sdk | `RFU089_ReferEventFlagStatus` | 2 |
| 0x5a |  | `Copy` | ps2sdk | `RFU090_iReferEventFlagStatus` | 5 |
| 0x5a | yes | `iCopy` | ps2sdk+i | `RFU090_iReferEventFlagStatus` | 1 |
| 0x5b |  | `GetEntryAddress` | ps2sdk | `RFU091` | 4 |
| 0x5c |  | `EnableIntcHandler` | ps2sdk |  | 1 |
| 0x5c | yes | `iEnableIntcHandler` | ps2sdk |  | 1 |
| 0x5d |  | `DisableIntcHandler` | ps2sdk |  | 1 |
| 0x5d | yes | `iDisableIntcHandler` | ps2sdk |  | 1 |
| 0x5e |  | `EnableDmacHandler` | ps2sdk |  | 1 |
| 0x5e | yes | `iEnableDmacHandler` | ps2sdk |  | 1 |
| 0x5f |  | `DisableDmacHandler` | ps2sdk |  | 1 |
| 0x5f | yes | `iDisableDmacHandler` | ps2sdk |  | 1 |
| 0x60 |  | `KSeg0` | ps2sdk |  | 1 |
| 0x61 |  | `EnableCache` | ps2sdk |  | 1 |
| 0x62 |  | `DisableCache` | ps2sdk |  | 1 |
| 0x63 |  | `GetCop0` | ps2sdk |  | 1 |
| 0x64 |  | `FlushCache` | ps2sdk |  | 1 |
| 0x66 |  | `CpuConfig` | ps2sdk |  | 1 |
| 0x67 | yes | `iGetCop0` | ps2sdk |  | 1 |
| 0x68 | yes | `iFlushCache` | ps2sdk |  | 1 |
| 0x6a | yes | `iCpuConfig` | ps2sdk |  | 1 |
| 0x6b |  | `sceSifStopDma` | ps2sdk |  | 1 |
| 0x6c |  | `SetCPUTimerHandler` | ps2sdk |  | 1 |
| 0x6d |  | `SetCPUTimer` | ps2sdk |  | 1 |
| 0x6e |  | `SetOsdConfigParam2` | ps2sdk |  | 1 |
| 0x6f |  | `GetOsdConfigParam2` | ps2sdk |  | 1 |
| 0x70 |  | `GsGetIMR` | ps2sdk |  | 1 |
| 0x70 | yes | `iGsGetIMR` | ps2sdk |  | 1 |
| 0x71 |  | `GsPutIMR` | ps2sdk |  | 1 |
| 0x71 | yes | `iGsPutIMR` | ps2sdk |  | 1 |
| 0x72 |  | `SetPgifHandler` | ps2sdk |  | 1 |
| 0x73 |  | `SetVSyncFlag` | ps2sdk |  | 1 |
| 0x74 |  | `SetSyscall` | ps2sdk |  | 6 |
| 0x75 |  | `_print` | ps2sdk |  | 1 |
| 0x76 |  | `sceSifDmaStat` | ps2sdk |  | 1 |
| 0x76 | yes | `isceSifDmaStat` | ps2sdk |  | 1 |
| 0x77 |  | `sceSifSetDma` | ps2sdk |  | 1 |
| 0x77 | yes | `isceSifSetDma` | ps2sdk |  | 1 |
| 0x78 |  | `sceSifSetDChain` | ps2sdk |  | 1 |
| 0x78 | yes | `isceSifSetDChain` | ps2sdk |  | 1 |
| 0x79 |  | `sceSifSetReg` | ps2sdk |  | 1 |
| 0x7a |  | `sceSifGetReg` | ps2sdk |  | 1 |
| 0x7b |  | `loc_503580` | ps2sdk |  | 1 |
| 0x7c |  | `Deci2Call` | ps2sdk |  | 1 |
| 0x7d |  | `PSMode` | ps2sdk |  | 1 |
| 0x7e |  | `MachineType` | ps2sdk |  | 1 |
| 0x7f |  | `GetMemorySize` | ps2sdk |  | 1 |
| 0x80 |  | `_GetGsDxDyOffset` | ps2sdk |  | 1 |
| 0x82 |  | `_InitTLB` | ps2sdk |  | 1 |
| 0x83 |  | `FindAddress` | ps2sdk |  | 1 |
| 0xfc |  | `SetAlarm` | ps2sdk |  | 1 |
| 0xfd |  | `unknown_syscall_FD` | unknown (ps2sdk defines only -0xfd = iSetAlarm) |  | 1 |
| 0xfe | yes | `iReleaseAlarm` | ps2sdk+i |  | 1 |
| 0xff | yes | `iReleaseAlarm` | ps2sdk |  | 1 |

### All sites

| Site | Function | N | Kernel name | Source | Thin wrapper |
|---|---|---|---|---|---|
| `0x001001c8` | `start` @ `0x00100008` | 0x3c | `RFU060` | ps2sdk |  |
| `0x001001e4` | `start` @ `0x00100008` | 0x3d | `RFU061` | ps2sdk |  |
| `0x00100224` | `_sceExitThread` @ `0x00100220` | 0x23 | `ExitThread` | ps2sdk | yes |
| `0x004f915c` | `_sce_GetGsDxDyOffset` @ `0x004f9158` | 0x80 | `_GetGsDxDyOffset` | ps2sdk | yes |
| `0x00502d44` | `RFU000_FullReset` @ `0x00502d40` | 0x0 | `RFU000_FullReset` | pcsx2 | yes |
| `0x00502d54` | `ResetEE` @ `0x00502d50` | 0x1 | `ResetEE` | ps2sdk | yes |
| `0x00502d64` | `sceGsResetGraph` @ `0x004f8eb0` | 0x2 | `loc_502D60` | ps2sdk |  |
| `0x00502d74` | `RFU003` @ `0x00502d70` | 0x3 | `RFU003` | pcsx2 | yes |
| `0x00502d84` | `Exit` @ `0x0050da58` | 0x4 | `KExit` | ps2sdk |  |
| `0x00502d94` | `RFU005` @ `0x00502d90` | 0x5 | `ResumeIntrDispatch` | ps2sdk | yes |
| `0x00502da4` | `LoadExecPS2` @ `0x0050da10` | 0x6 | `loc_502DA0` | ps2sdk |  |
| `0x00502db4` | `_sce_ExecPS2` @ `0x00502db0` | 0x7 | `_ExecPS2` | ps2sdk | yes |
| `0x00502dc4` | `RFU008` @ `0x00502dc0` | 0x8 | `ResumeT3IntrDispatch` | ps2sdk | yes |
| `0x00502dd4` | `RFU009` @ `0x00502dd0` | 0x9 | `RFU009` | ps2sdk | yes |
| `0x00502de4` | `AddSbusIntcHandler` @ `0x00502de0` | 0xa | `AddSbusIntcHandler` | ps2sdk | yes |
| `0x00502df4` | `RemoveSbusIntcHandler` @ `0x00502df0` | 0xb | `RemoveSbusIntcHandler` | ps2sdk | yes |
| `0x00502e04` | `Interrupt2Iop` @ `0x00502e00` | 0xc | `Interrupt2Iop` | ps2sdk | yes |
| `0x00502e14` | `_sceSetVTLBRefillHandler` @ `0x00502e10` | 0xd | `SetVTLBRefillHandler` | ps2sdk | yes |
| `0x00502e24` | `_sceSetVCommonHandler` @ `0x00502e20` | 0xe | `SetVCommonHandler` | ps2sdk | yes |
| `0x00502e34` | `SetVInterruptHandler` @ `0x00502e30` | 0xf | `SetVInterruptHandler` | ps2sdk | yes |
| `0x00502e44` | `_sceAddIntcHandler` @ `0x00502e40` | 0x10 | `AddIntcHandler` | ps2sdk | yes |
| `0x00502e54` | `_sceAddIntcHandler_0` @ `0x00502e50` | 0x10 | `AddIntcHandler` | ps2sdk | yes |
| `0x00502e64` | `_sceRemoveIntcHandler` @ `0x00502e60` | 0x11 | `RemoveIntcHandler` | ps2sdk | yes |
| `0x00502e74` | `_sceAddDmacHandler` @ `0x00502e70` | 0x12 | `AddDmacHandler` | ps2sdk | yes |
| `0x00502e84` | `_sceAddDmacHandler_0` @ `0x00502e80` | 0x12 | `AddDmacHandler` | ps2sdk | yes |
| `0x00502e94` | `_sceRemoveDmacHandler` @ `0x00502e90` | 0x13 | `RemoveDmacHandler` | ps2sdk | yes |
| `0x00502ea4` | `_sce_EnableIntc` @ `0x00502ea0` | 0x14 | `_EnableIntc` | ps2sdk | yes |
| `0x00502eb4` | `_sce_DisableIntc` @ `0x00502eb0` | 0x15 | `_DisableIntc` | ps2sdk | yes |
| `0x00502ec4` | `_sce_EnableDmac` @ `0x00502ec0` | 0x16 | `_EnableDmac` | ps2sdk | yes |
| `0x00502ed4` | `_sce_DisableDmac` @ `0x00502ed0` | 0x17 | `_DisableDmac` | ps2sdk | yes |
| `0x00502ee4` | `SetAlarm` @ `0x00502ee0` | 0xfc | `SetAlarm` | ps2sdk | yes |
| `0x00502ef4` | `ReleaseAlarm` @ `0x00502ef0` | 0xfd | `unknown_syscall_FD` | unknown (ps2sdk defines only -0xfd = iSetAlarm) | yes |
| `0x00502f04` | `_sce_iEnableIntc` @ `0x00502f00` | -0x1a | `_iEnableIntc` | ps2sdk | yes |
| `0x00502f14` | `_sce_iDisableIntc` @ `0x00502f10` | -0x1b | `_iDisableIntc` | ps2sdk | yes |
| `0x00502f24` | `_sce_iEnableDmac` @ `0x00502f20` | -0x1c | `_iEnableDmac` | ps2sdk | yes |
| `0x00502f34` | `_sce_iDisableDmac` @ `0x00502f30` | -0x1d | `_iDisableDmac` | ps2sdk | yes |
| `0x00502f44` | `iSetAlarm` @ `0x00502f40` | -0xfe | `iReleaseAlarm` | ps2sdk+i | yes |
| `0x00502f54` | `iReleaseAlarm` @ `0x00502f50` | -0xff | `iReleaseAlarm` | ps2sdk | yes |
| `0x00502f64` | `_sceCreateThread` @ `0x00502f60` | 0x20 | `CreateThread` | ps2sdk | yes |
| `0x00502f74` | `_sceDeleteThread` @ `0x00502f70` | 0x21 | `DeleteThread` | ps2sdk | yes |
| `0x00502f84` | `_sceStartThread` @ `0x00502f80` | 0x22 | `StartThread` | ps2sdk | yes |
| `0x00502f94` | `ExitThread` @ `0x00502f90` | 0x23 | `ExitThread` | ps2sdk | yes |
| `0x00502fa4` | `_sceExitDeleteThread` @ `0x00502fa0` | 0x24 | `ExitDeleteThread` | ps2sdk | yes |
| `0x00502fb4` | `_sceTerminateThread` @ `0x00502fb0` | 0x25 | `TerminateThread` | ps2sdk | yes |
| `0x00502fc4` | `iTerminateThread` @ `0x00502fc0` | -0x26 | `iTerminateThread` | ps2sdk | yes |
| `0x00502fd4` | `DisableDispatchThread` @ `0x00502fd0` | 0x27 | `DisableDispatchThread` | ps2sdk | yes |
| `0x00502fe4` | `EnableDispatchThread` @ `0x00502fe0` | 0x28 | `EnableDispatchThread` | ps2sdk | yes |
| `0x00502ff4` | `_sceChangeThreadPriority` @ `0x00502ff0` | 0x29 | `ChangeThreadPriority` | ps2sdk | yes |
| `0x00503004` | `_sceiChangeThreadPriority` @ `0x00503000` | -0x2a | `iChangeThreadPriority` | ps2sdk | yes |
| `0x00503014` | `_sceRotateThreadReadyQueue` @ `0x00503010` | 0x2b | `RotateThreadReadyQueue` | ps2sdk | yes |
| `0x00503024` | `_iRotateThreadReadyQueue` @ `0x00503020` | -0x2c | `_iRotateThreadReadyQueue` | ps2sdk | yes |
| `0x00503034` | `ReleaseWaitThread` @ `0x00503030` | 0x2d | `ReleaseWaitThread` | ps2sdk | yes |
| `0x00503044` | `iReleaseWaitThread` @ `0x00503040` | -0x2e | `iReleaseWaitThread` | ps2sdk | yes |
| `0x00503054` | `_sceGetThreadId` @ `0x00503050` | 0x2f | `GetThreadId` | ps2sdk | yes |
| `0x00503064` | `_sceReferThreadStatus` @ `0x00503060` | 0x30 | `ReferThreadStatus` | ps2sdk | yes |
| `0x00503074` | `_sceiReferThreadStatus` @ `0x00503070` | -0x31 | `iReferThreadStatus` | ps2sdk | yes |
| `0x00503084` | `_sceSleepThread` @ `0x00503080` | 0x32 | `SleepThread` | ps2sdk | yes |
| `0x00503094` | `_sceWakeupThread` @ `0x00503090` | 0x33 | `WakeupThread` | ps2sdk | yes |
| `0x005030a4` | `_sce_iWakeupThread` @ `0x005030a0` | -0x34 | `_iWakeupThread` | ps2sdk | yes |
| `0x005030b4` | `CancelWakeupThread` @ `0x005030b0` | 0x35 | `CancelWakeupThread` | ps2sdk | yes |
| `0x005030c4` | `iCancelWakeupThread` @ `0x005030c0` | -0x36 | `iCancelWakeupThread` | ps2sdk | yes |
| `0x005030d4` | `_sceSuspendThread` @ `0x005030d0` | 0x37 | `SuspendThread` | ps2sdk | yes |
| `0x005030e4` | `_sce_iSuspendThread` @ `0x005030e0` | -0x38 | `_iSuspendThread` | ps2sdk | yes |
| `0x005030f4` | `_sceResumeThread` @ `0x005030f0` | 0x39 | `ResumeThread` | ps2sdk | yes |
| `0x00503104` | `iResumeThread` @ `0x00503100` | -0x3a | `iResumeThread` | ps2sdk | yes |
| `0x00503114` | `JoinThread` @ `0x00503110` | 0x3b | `RFU059` | ps2sdk | yes |
| `0x00503124` | `RFU060` @ `0x00503120` | 0x3c | `RFU060` | ps2sdk | yes |
| `0x00503134` | `RFU061` @ `0x00503130` | 0x3d | `RFU061` | ps2sdk | yes |
| `0x00503144` | `_sceEndOfHeap` @ `0x00503140` | 0x3e | `EndOfHeap` | ps2sdk | yes |
| `0x00503154` | `RFU063` @ `0x00503150` | 0x3f | `RFU063` | pcsx2 | yes |
| `0x00503164` | `_sceCreateSema` @ `0x00503160` | 0x40 | `CreateSema` | ps2sdk | yes |
| `0x00503174` | `_sceDeleteSema` @ `0x00503170` | 0x41 | `DeleteSema` | ps2sdk | yes |
| `0x00503184` | `_sceSignalSema` @ `0x00503180` | 0x42 | `SignalSema` | ps2sdk | yes |
| `0x00503194` | `_sceiSignalSema` @ `0x00503190` | -0x43 | `iSignalSema` | ps2sdk | yes |
| `0x005031a4` | `_sceWaitSema` @ `0x005031a0` | 0x44 | `WaitSema` | ps2sdk | yes |
| `0x005031b4` | `_scePollSema` @ `0x005031b0` | 0x45 | `PollSema` | ps2sdk | yes |
| `0x005031c4` | `iPollSema` @ `0x005031c0` | -0x46 | `iPollSema` | ps2sdk | yes |
| `0x005031d4` | `ReferSemaStatus` @ `0x005031d0` | 0x47 | `ReferSemaStatus` | ps2sdk | yes |
| `0x005031e4` | `iReferSemaStatus` @ `0x005031e0` | -0x48 | `iReferSemaStatus` | ps2sdk | yes |
| `0x005031f4` | `RFU073` @ `0x005031f0` | 0x49 | `unknown_syscall_49` | unknown (ps2sdk defines only -0x49 = iDeleteSema) | yes |
| `0x00503204` | `_sceSetOsdConfigParam` @ `0x00503200` | 0x4a | `SetOsdConfigParam` | ps2sdk | yes |
| `0x00503214` | `_sceGetOsdConfigParam` @ `0x00503210` | 0x4b | `GetOsdConfigParam` | ps2sdk | yes |
| `0x00503224` | `GetGsHParam` @ `0x00503220` | 0x4c | `GetGsHParam` | ps2sdk | yes |
| `0x00503234` | `GetGsVParam` @ `0x00503230` | 0x4d | `GetGsVParam` | ps2sdk | yes |
| `0x00503244` | `SetGsHParam` @ `0x00503240` | 0x4e | `SetGsHParam` | ps2sdk | yes |
| `0x00503254` | `SetGsVParam` @ `0x00503250` | 0x4f | `SetGsVParam` | ps2sdk | yes |
| `0x00503264` | `RFU080_CreateEventFlag` @ `0x00503260` | 0x50 | `CreateEventFlag` | ps2sdk | yes |
| `0x00503274` | `RFU081_DeleteEventFlag` @ `0x00503270` | 0x51 | `DeleteEventFlag` | ps2sdk | yes |
| `0x00503284` | `RFU082_SetEventFlag` @ `0x00503280` | 0x52 | `SetEventFlag` | ps2sdk | yes |
| `0x00503294` | `RFU083_iSetEventFlag` @ `0x00503290` | -0x53 | `iSetEventFlag` | ps2sdk | yes |
| `0x005032a4` | `RFU084_ClearEventFlag` @ `0x005032a0` | 0x54 | `xlaunch` | ps2sdk | yes |
| `0x005032b4` | `RFU085_iClearEventFlag` @ `0x005032b0` | -0x55 | `iPutTLBEntry` | ps2sdk | yes |
| `0x005032c4` | `RFU086_WaitEvnetFlag` @ `0x005032c0` | 0x56 | `_SetTLBEntry` | ps2sdk | yes |
| `0x005032d4` | `RFU087_PollEvnetFlag` @ `0x005032d0` | 0x57 | `GetTLBEntry` | ps2sdk | yes |
| `0x005032e4` | `RFU088_iPollEvnetFlag` @ `0x005032e0` | -0x58 | `iProbeTLBEntry` | ps2sdk | yes |
| `0x005032f4` | `RFU089_ReferEventFlagStatus` @ `0x005032f0` | 0x59 | `ExpandScratchPad` | ps2sdk | yes |
| `0x00503304` | `RFU090_iReferEventFlagStatus` @ `0x00503300` | -0x5a | `iCopy` | ps2sdk+i | yes |
| `0x00503314` | `RFU091` @ `0x00503310` | 0x5b | `GetEntryAddress` | ps2sdk | yes |
| `0x00503324` | `EnableIntcHandler` @ `0x00503320` | 0x5c | `EnableIntcHandler` | ps2sdk | yes |
| `0x00503334` | `iEnableIntcHandler` @ `0x00503330` | -0x5c | `iEnableIntcHandler` | ps2sdk | yes |
| `0x00503344` | `DisableIntcHandler` @ `0x00503340` | 0x5d | `DisableIntcHandler` | ps2sdk | yes |
| `0x00503354` | `iDisableIntcHandler` @ `0x00503350` | -0x5d | `iDisableIntcHandler` | ps2sdk | yes |
| `0x00503364` | `EnableDmacHandler` @ `0x00503360` | 0x5e | `EnableDmacHandler` | ps2sdk | yes |
| `0x00503374` | `iEnableDmacHandler` @ `0x00503370` | -0x5e | `iEnableDmacHandler` | ps2sdk | yes |
| `0x00503384` | `DisableDmacHandler` @ `0x00503380` | 0x5f | `DisableDmacHandler` | ps2sdk | yes |
| `0x00503394` | `iDisableDmacHandler` @ `0x00503390` | -0x5f | `iDisableDmacHandler` | ps2sdk | yes |
| `0x005033a4` | `KSeg0` @ `0x005033a0` | 0x60 | `KSeg0` | ps2sdk | yes |
| `0x005033b4` | `EnableCache` @ `0x005033b0` | 0x61 | `EnableCache` | ps2sdk | yes |
| `0x005033c4` | `DisableCache` @ `0x005033c0` | 0x62 | `DisableCache` | ps2sdk | yes |
| `0x005033d4` | `GetCop0` @ `0x005033d0` | 0x63 | `GetCop0` | ps2sdk | yes |
| `0x005033e4` | `_sceFlushCache` @ `0x005033e0` | 0x64 | `FlushCache` | ps2sdk | yes |
| `0x005033f4` | `CpuConfig` @ `0x005033f0` | 0x66 | `CpuConfig` | ps2sdk | yes |
| `0x00503404` | `iGetCop0` @ `0x00503400` | -0x67 | `iGetCop0` | ps2sdk | yes |
| `0x00503414` | `iFlushCache` @ `0x00503410` | -0x68 | `iFlushCache` | ps2sdk | yes |
| `0x00503424` | `iCpuConfig` @ `0x00503420` | -0x6a | `iCpuConfig` | ps2sdk | yes |
| `0x00503434` | `_sceSifStopDma` @ `0x00503430` | 0x6b | `sceSifStopDma` | ps2sdk | yes |
| `0x00503444` | `SetCPUTimerHandler` @ `0x00503440` | 0x6c | `SetCPUTimerHandler` | ps2sdk | yes |
| `0x00503454` | `SetCPUTimer` @ `0x00503450` | 0x6d | `SetCPUTimer` | ps2sdk | yes |
| `0x00503464` | `SetOsdConfigParam2` @ `0x00503460` | 0x6e | `SetOsdConfigParam2` | ps2sdk | yes |
| `0x00503474` | `GetOsdConfigParam2` @ `0x00503470` | 0x6f | `GetOsdConfigParam2` | ps2sdk | yes |
| `0x00503484` | `_sceGsGetIMR` @ `0x00503480` | 0x70 | `GsGetIMR` | ps2sdk | yes |
| `0x00503494` | `iGsGetIMR` @ `0x00503490` | -0x70 | `iGsGetIMR` | ps2sdk | yes |
| `0x005034a4` | `_sceGsPutIMR` @ `0x005034a0` | 0x71 | `GsPutIMR` | ps2sdk | yes |
| `0x005034b4` | `iGsPutIMR` @ `0x005034b0` | -0x71 | `iGsPutIMR` | ps2sdk | yes |
| `0x005034c4` | `SetPgifHandler` @ `0x005034c0` | 0x72 | `SetPgifHandler` | ps2sdk | yes |
| `0x005034d4` | `_sceSetVSyncFlag` @ `0x005034d0` | 0x73 | `SetVSyncFlag` | ps2sdk | yes |
| `0x005034e4` | `RFU116` @ `0x005034e0` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x005034f4` | `_print` @ `0x005034f0` | 0x75 | `_print` | ps2sdk | yes |
| `0x00503504` | `_sceSifDmaStat` @ `0x00503500` | 0x76 | `sceSifDmaStat` | ps2sdk | yes |
| `0x00503514` | `isceSifDmaStat` @ `0x00503510` | -0x76 | `isceSifDmaStat` | ps2sdk | yes |
| `0x00503524` | `_sceSifSetDma` @ `0x00503520` | 0x77 | `sceSifSetDma` | ps2sdk | yes |
| `0x00503534` | `_isceSifSetDma` @ `0x00503530` | -0x77 | `isceSifSetDma` | ps2sdk | yes |
| `0x00503544` | `_sceSifSetDChain` @ `0x00503540` | 0x78 | `sceSifSetDChain` | ps2sdk | yes |
| `0x00503554` | `_isceSifSetDChain` @ `0x00503550` | -0x78 | `isceSifSetDChain` | ps2sdk | yes |
| `0x00503564` | `_sceSifSetReg` @ `0x00503560` | 0x79 | `sceSifSetReg` | ps2sdk | yes |
| `0x00503574` | `_sceSifGetReg` @ `0x00503570` | 0x7a | `sceSifGetReg` | ps2sdk | yes |
| `0x00503584` | `ExecOSD` @ `0x0050da80` | 0x7b | `loc_503580` | ps2sdk |  |
| `0x00503594` | `_sceDeci2Call` @ `0x00503590` | 0x7c | `Deci2Call` | ps2sdk | yes |
| `0x005035a4` | `PSMode` @ `0x005035a0` | 0x7d | `PSMode` | ps2sdk | yes |
| `0x005035b4` | `MachineType` @ `0x005035b0` | 0x7e | `MachineType` | ps2sdk | yes |
| `0x005035c4` | `_sceGetMemorySize` @ `0x005035c0` | 0x7f | `GetMemorySize` | ps2sdk | yes |
| `0x005035d4` | `_sce_InitTLB` @ `0x005035d0` | 0x82 | `_InitTLB` | ps2sdk | yes |
| `0x00504038` | `iWakeupThread` @ `0x00504028` | -0x2f | `_iGetThreadId` | ps2sdk |  |
| `0x00504150` | `iSuspendThread` @ `0x00504140` | -0x2f | `_iGetThreadId` | ps2sdk |  |
| `0x0050cc14` | `_sceCopy` @ `0x0050cc10` | 0x5a | `Copy` | ps2sdk | yes |
| `0x0050cc5c` | `_sceGetEntryAddress` @ `0x0050cc58` | 0x5b | `GetEntryAddress` | ps2sdk | yes |
| `0x0050cc6c` | `_sceSetSyscall` @ `0x0050cc68` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x0050cd44` | `PutTLBEntry` @ `0x0050cd40` | 0x55 | `PutTLBEntry` | ps2sdk | yes |
| `0x0050cd54` | `iPutTLBEntry` @ `0x0050cd50` | -0x55 | `iPutTLBEntry` | ps2sdk | yes |
| `0x0050cd64` | `_sce_SetTLBEntry` @ `0x0050cd60` | 0x56 | `_SetTLBEntry` | ps2sdk | yes |
| `0x0050cda4` | `iSetTLBEntry` @ `0x0050cda0` | -0x56 | `iSetTLBEntry` | ps2sdk | yes |
| `0x0050cdb4` | `GetTLBEntry` @ `0x0050cdb0` | 0x57 | `GetTLBEntry` | ps2sdk | yes |
| `0x0050cdc4` | `iGetTLBEntry` @ `0x0050cdc0` | -0x57 | `iGetTLBEntry` | ps2sdk | yes |
| `0x0050cdd4` | `ProbeTLBEntry` @ `0x0050cdd0` | 0x58 | `ProbeTLBEntry` | ps2sdk | yes |
| `0x0050cde4` | `iProbeTLBEntry` @ `0x0050cde0` | -0x58 | `iProbeTLBEntry` | ps2sdk | yes |
| `0x0050cdf4` | `ExpandScratchPad` @ `0x0050cdf0` | 0x59 | `ExpandScratchPad` | ps2sdk | yes |
| `0x0050d158` | `_xlaunch` @ `0x0050d140` | -0x54 | `ixlaunch` | ps2sdk+i |  |
| `0x0050d47c` | `_sceCopy_0` @ `0x0050d478` | 0x5a | `Copy` | ps2sdk | yes |
| `0x0050d504` | `_sceFindAddress` @ `0x0050d500` | 0x83 | `FindAddress` | ps2sdk | yes |
| `0x0050d64c` | `_sceSetSyscall_0` @ `0x0050d648` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x0050d6b4` | `_sceSetSyscall_1` @ `0x0050d6b0` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x0050d6c4` | `_sceCopy_1` @ `0x0050d6c0` | 0x5a | `Copy` | ps2sdk | yes |
| `0x0050d70c` | `_sceGetEntryAddress_0` @ `0x0050d708` | 0x5b | `GetEntryAddress` | ps2sdk | yes |
| `0x0050d834` | `_sceCopy_2` @ `0x0050d830` | 0x5a | `Copy` | ps2sdk | yes |
| `0x0050d874` | `_sceSetSyscall_2` @ `0x0050d870` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x0050dad4` | `_sceSetSyscall_3` @ `0x0050dad0` | 0x74 | `SetSyscall` | ps2sdk | yes |
| `0x0050dae4` | `_sceCopy_3` @ `0x0050dae0` | 0x5a | `Copy` | ps2sdk | yes |
| `0x0050db2c` | `_sceGetEntryAddress_1` @ `0x0050db28` | 0x5b | `GetEntryAddress` | ps2sdk | yes |
<!-- GENERATED:END -->
