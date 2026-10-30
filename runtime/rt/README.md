# `runtime/rt/` — the rt adapter (`p3fes_rt`)

The implementation of `p3fes::rt` (`recomp/include/p3fes_recomp_rt.h`): what every statement of the
recompiled program calls. ADR-0013 §3 fixes its scope: **register semantics and guest RAM access, no
device models**. Everything that is "the system" — syscalls, check points (interrupt delivery,
thread switches), hardware-register windows, traps and fatal stops — goes to the `RtHooks` instance
installed with `p3fes::set_hooks()` (`runtime/include/p3fes/rt_hooks.h`), which the kernel HLE
(`runtime/hle/kernel/`) implements.

No R5900 rule is derived here. Every operation is a call into `runtime/include/p3fes/ee/*.h`:
`core.h` (integer ALU, shifts, extension, GPR write rule, addressing, unaligned merges, branch
conditions; added with this adapter), `cop0.h` (Status, ERET, CPCOND0; added with this adapter),
`hilo.h`, `mmi.h`, `fpu.h`, `vu0.h` (ported earlier). The adapter only moves operands in and results
out, and resolves memory.

## Setup contract

Before the first recompiled function runs, the host must

1. set `EEContext::memory` to the guest `EEMemory` (a null pointer makes every memory access fatal),
2. install its hooks with `p3fes::set_hooks(&hooks)` — until then (and after `set_hooks(nullptr)`)
   an aborting default is installed that names the hook that was reached and exits with code 3,
   without the Debug CRT's modal `abort()` dialog,
3. call `p3fes::rt::bind_context(&ctx)` (`include/p3fes/rt/rt_adapter.h`) so that the four stops
   that receive no context report the live CPU state to `RtHooks::fatal` (unbound: a zeroed
   placeholder `EEContext` is passed instead).

`lookup_func` is not here: the generated `dispatch.cpp` defines it (`p3fes_program`, or a test's own
emitted subset). `RtHooks::trap`'s `kind` is the value of `rt::Trap` (`kTrapBreak` 0,
`kTrapUnsupported` 1, `rt_adapter.h`).

## What maps to what (202 of the 203 declarations; `lookup_func` is generated)

| File | Declarations | Semantics from | Notes |
|---|---|---|---|
| `rt_hooks.cpp` | 7: `syscall`, `check_events`, `trap`, `lookup_miss`, `bad_entry`, `unreachable`, `missing_function` (+ `set_hooks`/`hooks`, `bind_context`/`bound_context`) | — | `syscall` → `hooks().syscall(ctx, pc)`; `check_events` → `hooks().check_events(ctx)` (reads the hooks pointer directly: one indirect call); `trap` → `hooks().trap(ctx, pc, kind, code)` (may return); the stops → `hooks().fatal(ctx, pc, message)` with the VA in the message, never return |
| `rt_core.cpp` | 62: `jal`, `jalr`, `reg32`, `cmp_*` ×6, `cop0_cond`; 45 integer ALU / shift / HI-LO pipe-0 ops; 7 COP0 (`mfc0`, `mtc0`, `sync`, `ei`, `di`, `cache`, `eret`) | `core.h`, `hilo.h`, `cop0.h` | `cop0_cond` (BC0F) reads D_PCR then D_STAT (fixed order) through `hooks().bus()` and applies `cop0::cpcond0`; no check point there (every BC0F wait is a loop with a back-edge check) |
| `rt_mem.cpp` | 25: `lb` `lbu` `lh` `lhu` `lw` `lwu` `ld` `sb` `sh` `sw` `sd`, `lwl` `lwr` `ldl` `ldr` `swl` `swr` `sdl` `sdr`, `lq` `sq`, `lwc1` `swc1`, `lqc2` `sqc2` (the aligned forms: slow halves of the inline fast paths) | `core.h` (extension, alignment, merges), `mmi.h`/`vu0.h` (`kQuadwordMask`), `fpu.h` (`fpr`/`set_fpr`), `vu0.h` (`qmtc2`/`qmfc2`) | resolution order below |
| `rt_mmi.cpp` | 47: 33 lane ops (`paddh` … `qfsrv`, `phmadh`, `pmfhl`), 10 pipe-1 / three-operand multiply ops (`div1`, `madd`, `maddu`, `maddu1`, `mult1`, `multu1`, `mfhi1`, `mflo1`, `mthi1`, `mtlo1`), 4 SA ops | `mmi.h` (SSE2 or scalar per `P3FES_EE_MMI_USE_SSE2`), `hilo.h` | MMI results are whole quadwords |
| `rt_fpu.cpp` | 24: 6 three-operand, 13 two-operand (ACC forms, compares, unary), `sqrt_s`, `mfc1`, `mtc1`, `ctc1`, `cop1_cond` | `fpu.h` | FPRs stay `u32` bit patterns; no host float operation touches a register |
| `rt_vu0.cpp` | 37: `cfc2`, `ctc2`, `qmfc2`, `qmtc2`; 33 macro ops (base, `_bc`, I/Q forms, `vftoi0`/`vitof0`, outer product, `vsqrt`/`vrsqrt`/`vwaitq`, `vnop`) | `vu0.h` | interlock bits passed through and ignored there; `vopmula`/`vopmsub` ignore `dest` (fixed xyz by the encoding) |

`tests/rt/test_rt_coverage.cpp` takes the address of all 202 (so the test only links if each is
defined) and parses the header to require that the table names exactly the declared functions.

## Rules

* **GPR writes**: through `core::set_gpr64` / `set_gpr128`: writes to `$zero` are dropped; ordinary
  instructions write bits 0..63 and leave 64..127 unchanged; MMI results, `lq` and `qmfc2` write all
  128 bits. Loads into `$zero` still perform the read (it may be a register with side effects).
* **32-bit results are sign-extended** (`core::sext32` inside the `core.h` operations; `mfc0`,
  `cfc2` and `mfc1` sign-extend the moved word). 32-bit operations read the low word of their
  sources. Three-operand `mult`/`multu`/`madd`/`maddu`/`mult1`/`multu1`/`maddu1` also write
  `rd <- LO` of their pipe.
* **Link writes**: `jal` writes `$ra`, `jalr` writes `rd`, both `sext32(pc + 8)`.
* **Memory**: effective address = low 32 bits of `base + sext(imm)`. Natural alignment is required
  for halfword/word/doubleword accesses (`lh`/`lhu`/`sh`, `lw`/`lwu`/`sw`/`lwc1`/`swc1`, `ld`/`sd`); a
  misaligned one is the EE's Address Error and is fatal here. `lq`/`sq`/`lqc2`/`sqc2` drop the low
  four address bits. `lwl`/`lwr`/`ldl`/`ldr` read the containing aligned word/doubleword and merge;
  `swl`/`swr`/`sdl`/`sdr` read, merge and write it back (`core.h`; `lwr` at offsets 1..3 keeps bits
  32..63 of rt — the EE choice, hardware-unverified).
* **Resolution order** for an access of n bytes at virtual address va:
  1. `EEMemory::resolve(va, n)` — main RAM and its KSEG0/KSEG1/0x2/0x3 mirrors, the 16 KiB
     scratchpad at 0x70000000, the BIOS window (RAM accesses are not check points);
  2. `EEMemory::is_hw(va)` — physical 0x10000000–0x1000FFFF and 0x12000000–0x12001FFF, reached
     through the identity range or KSEG0/KSEG1 (ADR-0013 consequence; `is_hw` changed with this
     adapter, `tests/test_ee_memory.cpp`) → `hooks().bus()` at `EEMemory::to_physical(va)` with the
     guest's width (`read8/16/32/64/128`, `write8/16/32/64/128`; the unaligned forms use 32/64), then
     **a check point** `hooks().check_events(ctx)` after the destination register is written;
  3. anything else → `hooks().fatal` naming the instruction, size, direction, virtual and physical
     address and the host return address into the generated function.
* **Fatal paths never return**: `RtHooks::fatal` is `[[noreturn]]`; a test sink throws.
* **COP0**: `ei`/`di` set/clear Status.EIE (bit 16, which the kernel HLE reads to decide whether a
  check point may deliver an interrupt); `eret` clears ERL, else EXL (control returns to the host
  caller, as emitted); `mfc0`/`mtc0` are plain storage; `sync` and `cache` are no-ops.

## Not modelled / stubbed, and known limits

* **No pc for memory faults.** Memory operations carry no guest pc in the API; a fault reports
  `ctx.pc` (which generated code does not maintain) plus the host return address, which a debugger
  resolves to the generated function and line (exact with `--annotate`). Open question below.
* **Exceptions**: Address Error → fatal; `add`/`addi`/`sub` overflow wraps (no Integer Overflow
  trap); TLB refill/invalid never happen (no TLB: the retail identity map is assumed).
* **COP2 control**: `ctc2` to vi28 (FBRST) is also forwarded to `RtHooks::vu_control_write` (VU1 reset/force-break
  belong to the VU1 owner, `runtime/gs`); `cfc2` of vi28/vi29 reads 0 (VPU_STAT busy bits clear: VU1 never runs
  concurrently).
* **Status mode bits**: `di`/`ei` act regardless of KSU/EDI. **Count** (COP0 $9) does not tick —
  the binary never reads or writes it (generated-code census: `mfc0` of $8, $12, $13, $14, $23, $28;
  `mtc0` of $6, $12, $14, $30).
* **BIOS window writes** go to the `EEMemory` BIOS storage (EEMemory resolves it for writes); the ROM
  would ignore them.
* **Segments**: hardware registers only through 0x00000000–0x1FFFFFFF and KSEG0/KSEG1; other
  segments' folds (e.g. 0x70004000 → 0x10004000) are fatal, not hardware.
* **`swl`/`swr`/`sdl`/`sdr` on a register** perform a read before the write (read-modify-write);
  none is known to target hardware.
* **Hot path**: every instruction is an opaque call (no LTO, no inlining across the adapter);
  `check_events` is two indirect jumps (adapter → hooks).

## Tests (`tests/rt/`, `tests/ee/test_core.cpp`, `tests/ee/test_cop0.cpp`)

| Executable | Cases / assertions | What |
|---|---|---|
| `p3fes_rt_tests` | 26 / 1,167 | memory: every width and extension, little-endian stores, the RAM mirrors / scratchpad / BIOS, `lwl`/`lwr`/`ldl`/`ldr` and `swl`/`swr`/`sdl`/`sdr` pairs at every byte offset with neighbours untouched, `lq`/`sq`/`lqc2`/`sqc2` masking, `lwc1`/`swc1`; hardware windows routed by width at the physical address (KSEG1 and identity), read values and extension through the bus, FIFO transfers, read-modify-write of the unaligned forms, one check point per access, `$zero` loads still reading; fatal on misalignment, unmapped addresses (named), null `EEMemory`. Core: `$zero` drop for every writer class, sign extension and the untouched upper half, 64-bit ops, link writes, 64-bit branch conditions, HI/LO, COP0, BC0F from the bus. MMI/FPU/VU0 plumbing. Hooks: install/restore, syscall/check_events/trap forwarding, the four stops reaching `fatal` with pc, message and bound context. Coverage (202). |
| `p3fes_ee_core_tests` | 10 / 132 | `core.h` (hand-derived vectors; the unaligned merges also against a byte-wise reference at every offset) and `cop0.h` |
| `p3fes_rt_exec_tests` | 2 / 6,027 | first execution, below |

All three pass with exit code 0 under cl.exe and clang-cl, Debug and Release (run 2026-10-18).

## First execution of recompiled code

`p3fes_rt_exec_tests` emits **11 libc functions** from the ELF at build time
(`emit_units.cmake`, cycles and check points on): `memcmp 0x5211B8`, `memcpy 0x521250`,
`memmove 0x521300`, `memset 0x521408`, `strchr 0x523F98`, `strcmp 0x524128`, `strcpy 0x524270`,
`strlen 0x524388`, `strncat 0x5244C0`, `strncmp 0x524670`, `strncpy 0x524828` (FLIRT names from
`symbols/p3fes.sym`). Purity was read from the emitted code (no `rt::syscall`, no calls, no
`rt::lookup_func`, constants are byte masks; ops used: integer ALU, `lb/lbu/ld/sd/sb`, `lq/sq`,
`pand/pnor/psubb/psubw/pxor/pcpyld/pcpyud/pcpyh`, `movz`) and is enforced at run time (hooks count
syscalls, traps and bus accesses: all 0). The guest is set up like the game's: the ELF's PT_LOAD
copied to 0x100000, `$gp = 0x7D2CF0`, `$sp = 0x01FFFF00` (main-thread stack band). Each function is
called through `rt::lookup_func` with arguments in `$a0..$a3` on random inputs (fixed seed, random
alignments 0..15, byte values 1..255, lengths up to 0xC00), and compared with the host CRT: the
return value (sign for the compares, guest pointer for `strchr` and the copy functions) and **every
byte of an 8 KiB guest arena** against a host mirror the host function was applied to.

Result: **3,300 calls (300 per function), all equal**; check points reached 1,061,514 times (entry +
back-edge) and `ctx.cycles` advanced by 7,766,100 over the four groups (strlen 53,509 / 377,973;
compares 70,283 / 652,409; copy/fill 790,650 / 5,548,269; string copy/search 147,072 / 1,187,449).
Those counters are identical in all four builds (cl.exe and clang-cl, Debug and Release): virtual
time does not depend on the host compiler or optimisation level. MWCC's compare functions finish with `lbu` differences, so the host
CRT's sign is a valid oracle for all byte values. One `strlen` of a 16-byte, 16-aligned string adds
**exactly 50** to `ctx.cycles` — its executed instruction words, read from the `--annotate` emission
(3 + 9 + 17 + 1 + 9 + 2 + 7 + 2, including four load-delay `nop`s at 0x5244a0–0x5244ac that produce no
C++) — and passes one check point (the entry; neither loop takes its back-edge).

## Performance (ADR-0013 hot-path cost)

`p3fes_rt_perf` / `p3fes_rt_perf_off` (`-DP3FES_RT_PERF=ON`, `tests/rt/perf_main.cpp`): the game's
`memset` over 1 MiB of guest RAM (229,405 guest instructions per call: a 7-instruction loop of two
`sq`, 32,768 iterations, one back-edge check each). `_off` is the same function emitted with
`--no-cycles --no-check-events`. Hooks: `check_events` is one compare against a far deadline (the
"one compare when nothing is due" of ADR-0013). Wall time per call, 5 runs, machine otherwise idle
(CPU load 1 % sampled before the runs; 12 logical CPUs):

| Build | default (cycles + checks) | `--no-cycles --no-check-events` | cost |
|---|---|---|---|
| cl.exe Debug (4 calls/run) | 3.314 3.060 2.790 2.783 2.806 ms (median 2.806) | 2.640 2.664 2.662 2.640 2.628 ms (median 2.640) | +6.3 % |
| clang-cl Debug (4 calls/run) | 3.089 3.083 3.061 3.063 3.068 ms (median 3.068) | 2.999 2.976 2.965 2.973 2.972 ms (median 2.973) | +3.2 % |
| cl.exe Release (20 calls/run) | 0.450 0.437 0.443 0.437 0.442 ms (median 0.442) | 0.397 0.401 0.396 0.401 0.397 ms (median 0.397) | +11.3 % |
| clang-cl Release (20 calls/run) | 0.432 0.429 0.445 0.429 0.434 ms (median 0.432) | 0.397 0.410 0.398 0.402 0.396 ms (median 0.398) | +8.5 % |

Release: about 1.0–1.4 ns per loop iteration for one `ctx.cycles` add plus one check; the program
runs this loop at ~520 M guest instructions/s (1.8x the EE's 294.912 MHz) with every instruction an
out-of-line call. This loop is a worst case (a check point every 7 instructions; the whole program
averages one cycle add per 7.5 reachable words and has 11,331 back-edge sites).

## Open questions for the lead

1. **pc for memory faults**: add a `pc` argument to the 25 memory declarations (one more immediate
   per call), have the emitter store a block pc (`ctx.pc = ...` per block, a second store next to
   the cycle add), or keep the host return address? The brief asked for "pc and address"; today the
   message has the address and host location only.
2. **CPCOND0 owner**: `cop0_cond` reads D_PCR/D_STAT through the bus and applies the manual's rule;
   the kernel HLE's DMAC model must serve those two registers (upstream simply returns true).
3. **`check_events` cost**: two indirect calls per check. If the title-screen measurement shows it
   matters, a deadline mirror the adapter compares inline (`if (ctx.cycles < next) return;`) would
   make the common case a compare without changing `RtHooks`.
4. **Fold `p3fes_ee_core_tests` into `p3fes_tests`** (two source lines in `tests/CMakeLists.txt`);
   kept separate only because this change was limited to one line there.

## Inline fast paths (performance pass, 2026-10-19)

The hot subset of the API is defined `inline` for every translation unit in
`recomp/include/p3fes_recomp_rt_inline.h` (included by `p3fes_recomp_rt.h` itself): the integer ALU,
shifts, immediates, branch conditions, link writes, HI/LO moves, the naturally aligned main-RAM /
scratchpad loads and stores (`lb..ld`, `lq`, `sb..sd`, `sq`) and `check_events`. The generated code
open-codes them; the out-of-line halves stay here: `rt::detail::load_slow` / `store_slow`
(`rt_mem.cpp`: BIOS window, hardware windows through `RtHooks::bus` + check point, unaligned and
unmapped faults — their own return address is the call site in the generated function) and
`rt::detail::check_events_slow` (`rt_hooks.cpp`). `set_hooks()` points `rt::detail::g_deadline` at
`RtHooks::deadline_ptr()` (the kernel HLE returns `&next_deadline_`) or at a zero, so a check point is
one compare in the generated code and hooks without a deadline pointer behave as before. `EEMemory::fast_ptr`
is the inline RAM/scratchpad resolver (alignment + `phys < 32 MiB`, the same folding as `resolve()`).
`rt_stubs` stubs only the slow halves. Semantics are unchanged: every rule still comes from `ee/core.h` and
`ee/hilo.h`; all rt/ee/exec suites pass and the M1/M2 `eeMemory.bin` images are byte-identical.

Second pass (2026-10-25, graphics track B, from IP-sampler profiles with caller frames): the memory fast paths
are `__forceinline` (MSVC left out-of-line copies of `rt::lw`/`ld`/`fast_ptr` inside the large hand-written
`game/` functions), `lwc1`/`swc1`/`lqc2`/`sqc2` have inline RAM fast paths too (the FPR and VU0 vf files are
plain bit patterns; the slow halves `rt::detail::lwc1_slow` ... `sqc2_slow` stay in `rt_mem.cpp`, stubbed in
`rt_stubs`), `EEMemory::read`/`write` (behind `guest::load`/`store`) inline the main-RAM branch of `resolve()`,
and the generated `rt::lookup_func` keeps a direct-mapped 4096-entry cache in front of its binary search.

Measured on the game (MSVC 14.44 Release, headless, PCSX2's card, this machine, each run once right after the
other):

| Build | boot → first RW flip (vblank 365) | boot → Atlus logo `sky:154` (vblank 676) |
|---|---:|---:|
| out-of-line adapter (`afa8903`) | 3.06 s wall (1.99× real time) | 9.27 s |
| `-DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON` alone | 1.55 s (3.9×) | 7.89 s |
| inline fast paths (this change) | **0.94 s (6.5×)** | **7.20 s** |

The logo phase is GS/VU1-bound (RenderWare's 2D path through the software rasteriser and the VU1
interpreter), so the adapter change barely moves it; that is the next profile target. LTO on top of the inline
header is measured separately (`build/r4-inl-lto`).
