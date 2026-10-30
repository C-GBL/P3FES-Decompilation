# 01 — Functions summary

_Observed_ = IDA shows it at the cited address; _inferred_ = our conclusion from those observations.

## Strip status and naming

* The ELF carries no `.symtab`/`.strtab` (see 00). Every one of the 14,040 functions started life as `sub_*`/`nullsub_*`. All non-auto names in the database were assigned by us: `start` (IDA entry), 75 `_sce*` syscall wrappers (02), and the handful in `tools/ours/ida/names_manual.txt` (`main`, `kwlnMain` (our session-1 placeholder was `kwlnMain`; renamed after topics 10/12 verified it, see `10_frame_loop_gs.md`), `exit`, `crt_init_runtime`, `bss_start`, `gp_base`, `crt0_args`).
* 177 `nullsub_*` are bare `jr $ra; nop` stubs (observed), consistent with debug/trace hooks compiled out in the retail build (inferred).
* Compiler is Metrowerks CodeWarrior MIPS 2.4.1 (ELF `.comment`), so Phase 3 must follow the SCE EE ABI as emitted by MW: 128-bit GPR saves with `sq/sd`, arguments in `$a0..$a3,$t0..$t3` (IDA shows them as `$a4..$a7`), 16-byte stack alignment (all observed in `start`, `sub_50D658`, `sub_5225A8`).

## Entry chain: `start` -> crt0 -> `main` (observed unless marked)

| Address | What is there | Reading |
|---|---|---|
| `0x100008..0x100118` | `padduw $r,$zero,$zero` for every GPR, `mthi/mtlo/mthi1/mtlo1/mtsah`, `mtc1 $zero,$f0..$f31`, `adda.s`, `sync`, `ctc1 $zero,FCSR` | register/FPU reset; the padduw idiom clears all 128 bits of each GPR |
| `0x10011c..0x100194` | byte loop then `sq $zero` loop from `0x7CDE80` to `0x9ACC80` | `.bss` zero-fill (bss_start.._end) |
| `0x1001a4..0x1001c8` | `$a0=0x7D2CF0 $a1=0x1F60000 $a2=0xA0000 $a3=0x95C280 $a4=0x100220; move $gp,$a0; li $v1,0x3C; syscall` | `SetupThread(gp, stack, stack_size, args, root_func)` — argument shape matches ps2sdk crt0 exactly; root func `0x100220` is `li $v1,0x23; syscall` = `ExitThread` (named `_sceExitThread`) |
| `0x1001cc` | `move $sp,$v0` | kernel-returned stack pointer |
| `0x1001d8..0x1001e4` | `$a0=0x9ACC80 $a1=-1; li $v1,0x3D; syscall` | `SetupHeap(_end, -1)` |
| `0x1001e8` | `jal 0x50D658` (`crt_init_runtime`) | eight `jal`s: `0x50D408` creates semaphores named `SceKernelLibc`/`SceKernelLibcEh` (strings `0x7be0b0`, `0x7be0c0`), `0x503F38` touches `SceKerneltopThread` (`0x7bda88`), `0x50D780` installs kernel patches via `SetSyscall` (table at `0x780380`: `(0x5A, 0x50D6D0)`, `(0x5B, 0x80074000)`), `0x50CC78` writes `0x8007xxxx` (kernel) addresses. Inferred: SCE libkernel `_InitSys` + MW runtime init. Tail-jumps to `0x50F3D0` -> `sub_521408(0x96D7C8, 0, 0x200)` (memset-like). |
| `0x1001f0` | `jal 0x5033E0` with `$a0=0` | `FlushCache(0)` (`_sceFlushCache`) — same as ps2sdk crt0 |
| `0x1001f8` | `ei` | interrupts on |
| `0x1001fc..0x10020c` | `lw $a0,0($v0=0x95C280)`; `addiu $a1,$v0,4`; `jal 0x193980` | **`main(argc, argv)`**: `0x95C280` is the `args` block handed to `SetupThread`, whose first word is argc and the following words argv — the standard SCE crt0 convention. Inferred name `main` (high confidence). |
| `0x100210` | `j 0x51F6A0` with `$a0=$v0` | `exit(main_return)` — inferred, named `exit` |
| `0x100218` | `j 0x50DA58` | unreachable from `start` (no fall-through into it); separate stub |

## `main` (`0x193980`, 32 bytes) and the frame loop

* `main` calls `0x5225A8` with `$a0 = $gp - 0x6C08 = 0x7CC0E8`, which holds the C string `"jpx235\n"` (observed in the file). `0x5225A8` spills `$a1..$a7` to the stack and calls `0x526238(stream, fmt, va)` with the stream from `off_782F30` — a `printf`-style varargs function (inferred). So `main` begins by printing the build tag `jpx235` (inferred: an internal build/CL number).
* `main` then calls `0x1939B0(0)`, which calls **`0x1984C0` (`kwlnMain`)**: `0x197030` (references every `cdrom0:\LIB31\*.IRX;1` string at `0x678510..0x678700` -> IOP module loader), `0x197350`, `0x198010`, then an unconditional loop `0x1984E0..0x19853C` (`b loc_1984E0` at `0x198538`): `0x198940` -> `gp-0x4C20`, `0x195DE0`, two reads of `0x10000000` (EE Timer0 `T0_COUNT`) feeding `0x488DD0`/`0x488C70`, `0x195460(gp-0x4C20)` polled until non-zero. Inferred: this is the game's top-level frame loop; the `kwlnTask.c`/`kwlnRoot.c` strings (`0x5e4e98`, `0x6787d8`) referenced from `0x1939D0`/`0x1989E0` next to it suggest the Atlus "kwln" task kernel lives here.
* `exit` (`0x51F6A0`) and `crt_init_runtime` remain to be confirmed by a PCSX2 trace (Phase 4).

## Size profile

See the generated tables: median function is 64–256 bytes; five functions exceed 16 KiB (largest `sub_53AD00`-class CRI/SDK routines and game logic). 172 functions have multiple chunks — relevant for the recompiler's boundary handling. The MMI census (1,790 MMI, 41,929 `lq/sq`, 3,589 COP2 instructions across 307 MMI-using functions) sizes the R5900-specific work for Phase 3; the heaviest MMI users (`sub_4E53E0`, `matfxBridgeBumpEnvMap`, `sub_4E6D60`, `matfxBridgeDualUvTransform`, …) sit in the `0x46c000..0x4e7000` band, which the source-path strings (`G3_2D*_Node.c` at `0x6b5770..0x6b5a10` referenced from `0x46F400`, `0x470200`, `0x470E10`) place in the renderer.

## Generated data

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-21 06:38:58 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

| Metric | Value |
|---|---|
| Functions (IDA `Functions()`) | 14500 |
| ... with auto names (`sub_`/`nullsub_`/`j_`) | 7028 |
| ... with non-auto names | 7472 |
| ... `nullsub_*` (empty `jr $ra`) | 72 |
| ... multi-chunk functions | 173 |
| Total function bytes | 0x49224c (4.57 MiB) |
| ELF symbols (`.symtab`) | none — stripped |
| MMI (opcode 0x1C) instructions / functions containing them | 2138 / 346 |
| `lq`/`sq` instructions | 42386 |
| COP2 (VU0 macro) instructions | 3627 |

### Size histogram (bytes, all chunks)

| Range | Count |
|---|---|
| 0 – 16 | 876 |
| 16 – 64 | 3271 |
| 64 – 256 | 6223 |
| 256 – 1024 | 3180 |
| 1024 – 4096 | 847 |
| 4096 – 16384 | 98 |
| 16384 – inf | 5 |

### 30 largest functions

| Address | Size | Chunks | Name |
|---|---|---|---|
| `0x0043ca30` | 0xb09c (45212) | 1 | `Y_StParts_UpdateStratumPartsTask` |
| `0x0014f7d0` | 0x4f9c (20380) | 1 | `sub_14F7D0` |
| `0x001c8620` | 0x4f48 (20296) | 1 | `K_FldEvent_UpdateFldEventTask` |
| `0x003e0c20` | 0x4ed8 (20184) | 1 | `sub_3E0C20` |
| `0x00290be0` | 0x412c (16684) | 1 | `btlActionUpdateStateSkill` |
| `0x003760a0` | 0x3708 (14088) | 1 | `sub_3760A0` |
| `0x0022fa80` | 0x3420 (13344) | 1 | `sub_22FA80` |
| `0x00210d90` | 0x30e4 (12516) | 1 | `sub_210D90` |
| `0x00571088` | 0x2fe0 (12256) | 1 | `sub_571088` |
| `0x003912f0` | 0x2b38 (11064) | 1 | `sub_3912F0` |
| `0x004072d0` | 0x29ac (10668) | 1 | `sub_4072D0` |
| `0x00156f80` | 0x2978 (10616) | 1 | `sub_156F80` |
| `0x00303130` | 0x2840 (10304) | 1 | `datCalcDamage` |
| `0x0014c5c0` | 0x2758 (10072) | 1 | `sub_14C5C0` |
| `0x0021f410` | 0x2744 (10052) | 1 | `sub_21F410` |
| `0x001da020` | 0x26d0 (9936) | 1 | `sub_1DA020` |
| `0x002392d0` | 0x26b8 (9912) | 1 | `sub_2392D0` |
| `0x00245ea0` | 0x25f0 (9712) | 1 | `sub_245EA0` |
| `0x00236390` | 0x25e8 (9704) | 1 | `sub_236390` |
| `0x0026a2c0` | 0x2450 (9296) | 1 | `sub_26A2C0` |
| `0x00369a20` | 0x23e4 (9188) | 1 | `sub_369A20` |
| `0x0023f540` | 0x23c8 (9160) | 1 | `sub_23F540` |
| `0x0026eed0` | 0x2360 (9056) | 1 | `sub_26EED0` |
| `0x00435c00` | 0x21f4 (8692) | 1 | `sub_435C00` |
| `0x00164920` | 0x2084 (8324) | 1 | `sub_164920` |
| `0x0028eb50` | 0x207c (8316) | 1 | `btlActionUpdateStateAttack` |
| `0x001311d0` | 0x1fac (8108) | 1 | `sub_1311D0` |
| `0x001f7210` | 0x1eec (7916) | 1 | `sub_1F7210` |
| `0x001e9af0` | 0x1e28 (7720) | 1 | `sub_1E9AF0` |
| `0x00117540` | 0x1c80 (7296) | 1 | `sub_117540` |

### Top MMI-using functions (raw opcode census)

| Address | Name | Size | MMI ops |
|---|---|---|---|
| `0x004e53e0` | `sub_4E53E0` | 0x1978 | 78 |
| `0x0046d6f0` | `matfxBridgeBumpEnvMap` | 0xa78 | 49 |
| `0x004e6d60` | `sub_4E6D60` | 0x18a8 | 46 |
| `0x00472970` | `matfxBridgeDualUvTransform` | 0x9cc | 43 |
| `0x0046cd90` | `matfxBridgeEnvMap` | 0x95c | 42 |
| `0x0054f8c8` | `sub_54F8C8` | 0x1b0 | 42 |
| `0x0046e170` | `matfxBridgeDual` | 0x908 | 40 |
| `0x004fe750` | `_rix_111` | 0x120 | 37 |
| `0x0046c5b0` | `matfxBridgeBumpMap` | 0x7dc | 32 |
| `0x00100008` | `start` | 0x208 | 31 |
| `0x004fe098` | `_rix_011` | 0xf8 | 29 |
| `0x004d9bc0` | `sub_4D9BC0` | 0x1640 | 28 |
| `0x004fd968` | `_copyAddRefImage` | 0xec | 28 |
| `0x004d6b90` | `_rwSkySetRenderState` | 0xd18 | 27 |
| `0x004db350` | `sub_4DB350` | 0x1b50 | 26 |

### Entry function listing (`start` `0x00100008`..`0x00100210`), tail from `0x100198`

```
00100198  lui     $a0, 0x7D  # '}'
0010019c  lui     $a1, 0x1F6
001001a0  lui     $a2, 0xA
001001a4  lui     $a3, 0x96
001001a8  lui     $a4, 0x10
001001ac  li      $a0, gp_base
001001b0  li      $a1, 0x1F60000
001001b4  li      $a2, 0xA0000
001001b8  li      $a3, crt0_args # HINT[tge-pr4] argc
001001bc  li      $a4, _sceExitThread
001001c0  move    $gp, $a0
001001c4  li      $v1, 0x3C  # '<'
001001c8  syscall
001001cc  move    $sp, $v0
001001d0  lui     $a0, 0x9B
001001d4  lui     $a1, 0
001001d8  li      $a0, 0x9ACC80
001001dc  li      $a1, 0xFFFFFFFF
001001e0  li      $v1, 0x3D  # '='
001001e4  syscall
001001e8  jal     crt_init_runtime
001001ec  nop
001001f0  jal     _sceFlushCache
001001f4  move    $a0, $zero
001001f8  ei
001001fc  li      $v0, crt0_args # HINT[tge-pr4] argc
00100204  lw      $a0, (crt0_args - 0x95C280)($v0) # argc
00100208  jal     main
0010020c  addiu   $a1, $v0, (data_95C284 - 0x95C280) # data_95C284
00100210  j       exit
00100214  move    $a0, $v0
00100218  j       Exit # HINT[tge-pr4] sub_100218
0010021c  nop
00100220  li      $v1, 0x23  # '#' # HINT[tge-pr4] _root
```

### `main` at `0x00193980`

```
00193980  addiu   $sp, -0x10 # HINT[tge-pr4] main agrees
00193984  sd      $ra, var_s0($sp)
00193988  addiu   $a0, $gp, -0x6C08
0019398c  jal     printf
00193990  nop
00193994  move    $a0, $zero
00193998  jal     initAndLoop
0019399c  nop
001939a0  ld      $ra, 0($sp)
001939a4  addiu   $sp, 0x10
001939a8  jr      $ra
001939ac  nop
```

### `kwlnMain` at `0x001984C0` (called from `sub_1939B0`)

```
001984c0  addiu   $sp, -0x10 # HINT[tge-pr4] kwlnMain verified
001984c4  sd      $ra, var_s0($sp)
001984c8  jal     kwlnInitPS2Systems
001984cc  nop
001984d0  jal     kwlnInitRenderer
001984d4  nop
001984d8  jal     kwlnInitMain
001984dc  nop
001984e0  jal     kwlnRootCreateTask
001984e4  nop
001984e8  sw      $v0, -0x4C20($gp)
001984ec  jal     sub_195DE0
001984f0  nop
001984f4  lui     $v0, 0x1000
001984f8  lw      $a0, 0x10000000
001984fc  jal     RpRandomSeed
00198500  nop
00198504  lui     $v0, 0x1000
00198508  lw      $a0, 0x10000000
0019850c  jal     RpRandomSeedMT
00198510  nop
00198514  b       loc_198524
00198518  nop
0019851c  jal     kwlnUpdate
00198520  nop
00198524  lw      $a0, -0x4C20($gp)
00198528  jal     kwlnTaskExists
0019852c  nop
00198530  bnez    $v0, loc_19851C
00198534  nop
00198538  b       loc_1984E0
0019853c  nop
```
<!-- GENERATED:END -->
