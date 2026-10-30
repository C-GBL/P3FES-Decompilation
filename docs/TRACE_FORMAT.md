# Execution trace format (Phase 4 — differential testing)

**Status:** draft v0, 2026-10-18. Our runtime's emitter and `tools/ours/tracediff` are fully specified here; the PCSX2 emitter is **TBD** until the tools inventory confirms which PCSX2 build and hooks we have (see §6). Nothing in this document is a claim about game behaviour.

## 1. Purpose
Two producers — PCSX2 (reference) and our recompiled runtime — emit the same stream describing EE execution. `tracediff` finds the **first divergence** and localises it to a PC, so we never debug by eye. The format must be:
- cheap enough to emit per instruction for a few seconds of game time (tens of millions of records);
- robust to the things that legitimately differ between an emulator and a port (timing, uninitialised memory, host pointers) — see §4;
- replayable: a trace is useful without the producer that made it.

## 2. File layout
Little-endian binary. One file = one run.

```
Header (64 bytes)
  magic        u8[4]   "P3TR"
  version      u16     1
  flags        u16     bit0 = has GPR deltas, bit1 = has FPR deltas, bit2 = has memory writes,
                       bit3 = per-instruction (else per-basic-block), bit4 = has instruction words
  producer     u8[8]   "pcsx2\0\0\0" | "p3fes\0\0\0"
  elf_sha256   u8[32]  must equal docs/INVENTORY.md (refuse to diff mismatched binaries)
  start_pc     u32     first PC recorded
  reserved     u32
Records (variable, tag-prefixed), terminated by END
```

### Record tags
| Tag | Name | Payload | Notes |
|---|---|---|---|
| `0x01` | `STEP` | `pc:u32` [, `insn:u32` if flag bit4] | one per retired instruction (bit3) or per basic-block entry |
| `0x02` | `GPR` | `reg:u8, lo:u64, hi:u64` | new 128-bit value of `reg` after the preceding `STEP` |
| `0x03` | `HILO` | `which:u8 (0=lo,1=hi,2=lo1,3=hi1), v:u64` | R5900 has two HI/LO pairs (MMI) |
| `0x04` | `FPR` | `reg:u8 (0..31, 32=ACC), v:u32` | raw IEEE bits, never a converted float |
| `0x05` | `FCR` | `which:u8 (0 or 31), v:u32` | |
| `0x06` | `COP0` | `reg:u8, v:u32` | only when written by the guest (mtc0) |
| `0x07` | `MEMW` | `addr:u32, size:u8 (1,2,4,8,16), data:u8[size]` | **virtual** EE address as the guest issued it; producers do not translate |
| `0x08` | `SYSCALL` | `num:s16` | the `$v1` value at the `syscall`; negative numbers preserved |
| `0x09` | `EVENT` | `kind:u8, arg:u32` | 0 frame-flip (`sceGsSyncV`/vsync), 1 thread switch (`arg` = thread id), 2 DMA kick (`arg` = channel), 3 overlay load (`arg` = base), 4 user marker |
| `0x0A` | `SYNC` | `seq:u32` | monotonic; emitted at every `SYSCALL`/`EVENT` so the differ can re-align after a timing-only divergence |
| `0xFF` | `END` | `records:u64` | count for integrity |

Register deltas are emitted **only for registers the instruction wrote** (the emitter compares before/after). A `STEP` with no following deltas means "no architectural state changed" (e.g. a taken branch, a NOP, a store — stores appear as `MEMW`).

## 3. Granularity
- **Level A — per instruction, no memory:** `STEP`+`GPR`/`FPR`. First thing to diff; localises an ALU/MMI/FPU translation bug to the exact PC.
- **Level B — memory-write log only:** `MEMW` + `SYNC`. Cheap, long-running; catches wrong stores, wrong addresses, DMA/VIF HLE divergences. Mandatory for Phase 5 (replacing a recompiled block must keep the write log identical).
- **Level C — basic-block PCs + syscalls/events:** control-flow only. For "where did it go wrong at all" over minutes of play.
A producer may emit any combination; `tracediff` requires both inputs to share the flag bits it is asked to compare.

## 4. What must be masked (producer or differ side)
These differ between PCSX2 and a port even when the port is correct; a naive diff would stop immediately.
1. **Timing-derived values:** COP0 `Count`, timer registers (`T0_COUNT`…), `cpu_ticks`-style reads, `sceGsSyncV` wait counts, `ReferThreadStatus` ordering. Differ: mask `MEMW`/`GPR` whose *source* is a `mfc0 Count` or a load from `0x1000_0000–0x1000_1FFF` (timers). Producers tag such loads via `EVENT kind=4` markers until a cleaner mechanism exists.
2. **Uninitialised memory:** reads of never-written RAM. PCSX2 zeroes RAM at boot; our runtime will too, and the differ treats matching zeros as equal, so this only bites via BIOS-left state — see 3.
3. **BIOS/kernel leftovers:** the EE kernel area (`0x8000_0000` kseg0 mirror of `0x0000_0000–0x0007_FFFF`) differs. Differ: ignore `MEMW` below `0x0010_0000` unless a run opts in.
4. **Host pointers / randomness:** none expected in guest state; if the game seeds RNG from timers it is case 1.
5. **Thread interleaving:** the EE kernel's scheduler decides at `SleepThread`/`WakeupThread`/semaphores. Our HLE scheduler must make the **same** decisions; until it does, diff at Level B/C between `SYNC` points per thread (`EVENT kind=1` carries the thread id). This is the known hard part; log any interleaving divergence under STATE.md "Blocked" with the two `SYNC` seqs.

## 5. `tracediff` (tools/ours/tracediff)
```
tracediff <ref.p3tr> <ours.p3tr> [--level A|B|C] [--mask timers,kernel,thread] [--context N] [--resync]
```
- Validates headers (version, `elf_sha256`, compatible flags).
- Streams both files; stops at the **first** differing record after masking, printing: record index, `SYNC` seq, PC of the enclosing `STEP`, the two payloads, and `N` preceding `STEP` PCs from each side (default 16) so the divergence can be read in IDA (`symbols/p3fes.sym` turns PCs into names).
- `--resync`: after a divergence, skip forward in both streams to the next common `SYNC` seq and continue, reporting a list — used to measure *how many* independent bugs remain, not to hide the first one.
- Exit code 0 identical, 1 divergence found, 2 usage/format error. Output is plain text first; JSON (`--json`) for the test harness.
- Unit tests: hand-written traces exercising each mask, the resync path, and a mismatched-ELF refusal.

The stream mode above is not implemented yet (the executable says so and exits 2). **Snapshot mode** (ADR-0012) is:
```
tracediff snapshot <ref/eeMemory.bin> <ours/eeMemory.bin> [--mask FILE]... [--dead-stack capture.json]... [--no-default-mask]
                   [--context N] [--top N] [--json OUT]
tracediff snapshot-mask <t0/eeMemory.bin> <t1/eeMemory.bin> --out MASK [--pad N] [--merge-gap N] [--mask FILE]...
```
- Inputs are 32 MiB EE RAM images in the **physical** layout of PCSX2's `eeMemory.bin` (offset = VA & `0x1FFFFFFF`); any other size is refused (exit 2). Our runtime must dump the same layout at the same sync point.
- `--dead-stack capture.json` (Phase 5 gate): from a p3fes snapshot's `capture.json` (`threads[]` with `stack`, `stack_size`, `frame`; `current_thread` + `sp`), also masks each thread's stack below its saved context frame, or below the live `sp` for the running thread — the bytes a hand-decompiled function legitimately leaves different from its recompiled body (callee spills below `$sp`).
- Masks: the §4.3 kernel area `0x00000000–0x000FFFFF` is masked by default (`--no-default-mask` opts in). A mask file has one range per line — `0xBEGIN-0xEND` (inclusive), `0xBEGIN+LEN`, or `0xADDR` (one 4-byte word) — with `#` comments; kseg0/kseg1 VAs are reduced to physical, ranges are merged and clipped. Masked bytes compare equal and a run never spans a masked range.
- Output: masked byte count, differing bytes and runs, the first run (VA, band, `--context` bytes from each side, default 16), the `--top` largest runs (default 20), and a per-band table — `kernel`, `code` `0x100000–0x5A1400`, `data` `0x5A2000–0x7CDE04`, `bss` `0x7CDE80–0x9ACC80`, `heap` `…–0x1F60000`, `stack` `…–0x2000000`, `other` (the ELF gaps) — where a run counts once in the band of its first byte and its bytes are split exactly at band edges. `--json` writes the same summary without byte contents.
- `snapshot-mask`: bytes that differ between two **reference** captures taken at the same sync point are timing noise; each run is widened by `--pad` bytes, runs closer than `--merge-gap` are merged, and the result is written as a mask file whose header names its inputs (the default kernel mask is excluded from the comparison and not repeated in the output). Exit 0 when the mask was written.
- Exit codes as above: 0 identical after masking, 1 divergence, 2 usage/format error.
- Unit tests: `tracediff_tests` (doctest, ctest name `tracediff_tests`) on synthetic images only; no game data is read.
- Reference captures, the first noise mask and example output: `docs/PCSX2.md` §9.

## 6. PCSX2 emitter — TBD, decision pending tools inventory
Candidates, to be chosen once `docs/TOOLS.md` records the PCSX2 build we have and whether it exposes these:
| Option | Granularity | Cost | Notes |
|---|---|---|---|
| a. PCSX2 built-in EE trace logging (dev/debug builds; `EE Trace` / `Log` options) | per instruction (text) | low if present | text → convert to `.p3tr` with a small tool; check which registers it prints |
| b. PINE / IPC protocol | memory peeks only, not per instruction | low | enough for Level B snapshots at `SYNC` points; not for Level A |
| c. Patched PCSX2 fork with an emitter hook in the EE interpreter (`R5900::Interpreter`) | any | high (C++ build of PCSX2) | most control; interpreter mode only (recompiler would need block-level hooks) |
| d. Qt debugger stepping | per instruction | impractical at volume | manual confirmation only |
Default plan if (a) is absent: **(c) at Level B first**, because the memory-write log is what Phase 5 needs continuously. Record the choice as an ADR.

**Decided 2026-10-18 (ADR-0012, evidence in `docs/PCSX2.md`):** option (a) is **absent** — PCSX2 2.8.2's release build parses `[EmuCore/TraceLog]` but emits no per-instruction, syscall or hardware lines. PCSX2 therefore serves as the **Level B/C oracle via snapshots**: PINE (`tools/ours/pcsx2/pine.py`) reads/saves at `SYNC` points, `extract_savestate.py` yields `eeMemory.bin`, and `tracediff` gains a snapshot mode (two memory images + the §4 masks) before its stream mode. GS dumps (`.gs.zst`) are the reference for the GS backend. Level A comes from a second runtime (`ps2-web-recomp` under WSL2 first; an out-of-repo PCSX2 interpreter-hook fork second). Rows (a)–(d) above are kept for the record.

## 7. Our runtime emitter
`runtime/trace/` — compiled out in release (`P3FES_TRACE=OFF`). When on, the recompiler emits a `trace_step(pc)` call at every instruction (Level A) or block entry (Level C) and the `EEMemory::write<T>` path emits `MEMW`. Register deltas are computed by snapshotting the `EEContext` before/after each `trace_step` (cheap: 32×16 B + FPU). Syscall and event hooks live in the HLE layer. Buffered 1 MiB, written with a background writer so tracing changes timing as little as possible — and timing must not matter, per §4.

## Open questions (carry into STATE.md when they become actionable)
- Does the game use both HI/LO pairs (`mult1`/`madd1`)? IDA scan in Phase 2 decides whether `HILO which=2,3` is ever emitted.
- VU0 macro-mode state (`vf00–vf31`, `vi`, `ACC`, `Q`, `P`, `I`) is not in the record set. Add a `VU0` tag (`0x0B`) once Phase 2 shows COP2 use; VU1 state is never diffed at this level (its outputs appear as GIF packets, diffed separately in Phase 3).
