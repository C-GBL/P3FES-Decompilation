# VU1 (`p3fes_vu1`)

Decoder and interpreter for the VU1 micro-programs the game uploads with VIF1 `MPG` and starts with
`MSCAL`/`MSCNT`/`MSCALF`. Sources: `runtime/vu1/`; headers: this directory; tests: `tests/vu1/`. Scope and
instruction set come from [`docs/ANALYSIS/09_vu1_micro_census.md`](../../../../docs/ANALYSIS/09_vu1_micro_census.md)
(resolves `RUNTIME_CONTRACT.md` V-07).

## What is implemented

| Piece | File | Notes |
|---|---|---|
| Decoder | `vu1_decode.h`, `runtime/vu1/vu1_decode.cpp` | All defined encodings (59 upper and 71 lower mnemonics, counting `NOP` and `LOI` as the census does), raw fields always extracted. Tables mirror `tools/ours/vu1/vu1_decode.py` entry by entry; `tests/vu1/test_vu1_census.cpp` reproduces `symbols/vu1_micro_census.json` exactly on all 114 dumps (123,095 pairs, per-program and aggregate histograms, 0 unknown). Keep both decoders in agreement: a table change lands in both, and the census test must stay green. |
| Interpreter | `vu1_interp.h`, `runtime/vu1/vu1_interp.cpp` | Executes exactly the census set: 43 upper + 45 lower mnemonics, the I flag (`LOI`) and the E flag. Every other encoding traps before any part of the pair executes, with the pair's byte PC, raw words and decoded mnemonics (`TrapKind`: undefined upper/lower, defined-but-uncensused upper/lower, M/D/T flag). |
| Q timing model | `runtime/vu1/vu1_qtiming.{h,cpp}` (private) | Port of upstream's static interlock model (see below). |
| State | `VU1State` | 32 `vf` as raw `u32[4]` (vf00 = 0,0,0,1.0), 16 `vi` (`u16`), ACC, Q, P, I, R, MAC, status (+ sticky, unused), 24-bit clip, PC/next PC/TPC, TOP/ITOP, flag/Q pipe, running/ending, the branch-VI-delay snapshot, 16 KiB micro memory (`MicroMemory`, write-only through `write`, generation-counted) and 16 KiB data memory (persists across runs, 09 §2.5). |
| Entry points | `VU1Interpreter` | `mscal(imm)` starts at `imm * 8`; `mscnt()` resumes at TPC = the pair after the E pair's delay slot (09 §2.4); `mscalf` = `mscal` (nothing in flight to flush in a synchronous model); `start`/`step`/`run(limit)` for fine control; `set_tops(top, itop)` feeds `XTOP`/`XITOP`. Default step limit 1,000,000 pairs (upstream's runaway guard) returns `StepLimit` and leaves the unit running. |

Branches have one delay slot; every PC, branch target and `JR` target is masked with `0x3FFF` (73 branches in the
corpus depend on the wrap). Data-memory qword addresses wrap at 1024.

## Upstream model ported, and its limits

Semantics are ported from `snuri00/ps2-web-recomp` @ `c0f476e` (MIT; provenance in [THIRD_PARTY.md](THIRD_PARTY.md)):
`runtime/src/vu_micro.cpp` `run()` (the `PS2_VU_EXACT` path, whose upper ops are `upper()` on the bit-level
`fpu.hpp` datapath), `lower()`, `xgkick()`, `set_flags()`, `BranchView`; `runtime/include/ps2/vu_ops.hpp`
`FlagPipe`, `clip_value`, `vf_use`/`issue`/`retire`/`q_delay`/`q_read_kind`. The float datapath is our existing port
`p3fes/ee/fpu.h` (flush-to-zero, no NaN/Inf, ±0x7FFFFFFF clamp, truncating), not a second copy. Upstream's default
fast path (`run_fast`) uses host floats instead; we deliberately took the exact path. Decision for the lead: if
`tracediff` shows PCSX2 matching host-float rounding better, switch the five FMAC kinds in `compute_upper`.

Pair semantics: the upper op reads registers before the lower op runs and commits after it (the upper result wins
a same-register race; a lower store sees the pre-upper value); `LOI` writes I in the lower slot, so an upper op in the
same pair reads the old I; vf00/vi00 are re-forced after every pair.

**Hardware-unverified behaviour (tests tag these "(upstream behaviour, hardware-unverified)")**

* **Q pipe.** `DIV` (7) / `RSQRT` (13) results are held pending. A Q-reading upper op sees the new Q when a static
  walk of its predecessors (≤ 15 pairs, FMAC operand interlocks at +4 cycles, loaded vi at +4) proves the latency
  elapsed on every path, the old Q when it never did, and otherwise compares the run's pair counter with the
  straight-line delay. `WAITQ`, a new Q producer and the end of a run flush it. Upstream quirk kept: the walk only
  checks "both outcomes seen" after expanding a node.
* **P pipe.** `ERCPR` writes P immediately (no 12-cycle latency); `MFP` reads it at once. Host-float `1/x` with
  inputs flushed/clamped; `1/0 = 3.4e38f`. (`WAITP` is outside the census and traps.)
* **MAC/clip timing.** A flag read sees the newest MAC value at least 4 pairs old and the newest clip value at
  least 3 pairs old; `FCSET` is visible immediately. MAC has Z/S/O bits only (no underflow); status keeps Z S U O
  + sticky, `DIV`/`RSQRT` set D (bit 5) for x/0 **and** 0/0 (the manual says I for 0/0).
* **Branch VI delay.** A conditional branch reads the vi values from before the previous pair's lower op unless that
  op was a flag read, `BAL` or `JALR`, or the pair was `LOI` (PCSX2 documents the same effect). `JR` reads vi
  directly.
* **Conversions.** `FTOI*` saturate to 0x7FFFFFFF / 0x80000000; `ITOF*` truncate. `RSQRT` uses |ft|.
* **Address wrap.** Data memory at 1024 qwords, `XGKICK` reads likewise.
* **Not modelled.** Cycle timing, VIF/GIF stalls, PATH arbitration, the D/T interrupt mechanism (trapped instead),
  `MSCALF`'s wait for GIF PATH1/2 idle.

## XGKICK / GIF contract for the GS backend

`IGifSink::kick(std::span<const u128>)` is called **synchronously** while the `XGKICK` pair executes, once per kick
(1–12 per run in the corpus). The span holds one complete PATH1 GIF packet copied out of VU1 data memory: GIF tag,
its data (PACKED `nloop*nreg`, REGLIST `ceil(nloop*nreg/2)`, IMAGE/disabled `nloop` qwords; `nreg 0 = 16`), then the
next tag, until the first tag with EOP has had its data copied. Addresses wrap at 1024 qwords; a chain with no EOP
within 1024 qwords is delivered truncated and counted in `VU1Stats::kicks_without_eop`. The span is valid only for
the call: the backend must consume or copy it before returning. Copying at kick time is safe for the game's
programs because they alternate two output buffers (09 §2.3: `iadd vi15,vi13; iadd vi13,vi14; xgkick vi14; iadd
vi14,vi15`); a program that kicked a buffer and kept writing it would diverge from hardware. Ordering relative to
VIF1 `DIRECT` (PATH2) packets is the VIF stream order, because the interpreter runs to `E` inside the `MSCAL`/`MSCNT`
call. The interpreter never interprets GIF registers itself.

## Ahead-of-time compiled programs (`vu1_aot.h`)

Measured on the battle route, the interpreter costs 44–68 ns per pair and VU1 is 28–41 % of the host's wall time
(`docs/ANALYSIS/24_vu1_acceleration.md`). The programs are static data with a closed instruction set, so
`p3fes_vu1_aotgen` (`runtime/vu1/aotgen/`) translates all 114 into C++ at build time, one function per program:

| Piece | File | Notes |
|---|---|---|
| Generator | `runtime/vu1/aotgen/vu1_aotgen.cpp` | Reads the dumps (`tools/ours/vu1/vu1_dump.py --elf <ELF>` writes `ida/logs/vu1/<code_va>.bin`) and the census JSON; writes `vu1_aot_<code_va>.cpp` + `vu1_aot_programs.cpp` into the build tree (they embed game code: never committed). |
| Shared semantics | `runtime/vu1/vu1_semantics.h` | The upper-op table, FMAC datapath, MAC/status/clip rules and flag pipe, moved verbatim out of `vu1_interp.cpp`: both engines run the same code. |
| Helpers | `runtime/vu1/vu1_aot_rt.h` | SSE4.1 kernels (round 3): host float ops under round toward zero + FTZ/DAZ (`CsrScope`, MXCSR restored around XGKICK, RSQRT and ERCPR) equal `fp::` except for exponent-255 operands and overflow, which show as a result lane >= 0x7F7FFFFF and are redone lane by lane with `fp::`; fp::add's alignment reproduced exactly in floats; DIV by DIVSS with the same guard; ITOF/FTOI/MAX/MINI/CLIP exact by construction; `bail()`/`finish()` hand the state over exactly as `step()` leaves it. |
| Resident check | `runtime/vu1/vu1_aot.cpp` (`AotIndex`) | Image match from micro address 0, once per micro generation; branches outside the image into pairs the Q analysis enumerated trigger a re-classification of the affected Q reads with the interpreter's own analysis (cached by the outside bytes); any change rejects the program for that generation. |
| Modes | `VU1Interpreter::set_mode` | `Interp` (the oracle; the class default), `Aot`, `Diff` (both engines on every run, everything compared, the interpreter's outcome kept). App: `p3fes --vu1` interp / aot / diff, default aot in builds with compiled programs. |

Round 3 (24 §8): vf / ACC are SSE locals and vi / clip integer locals for a whole block, written back at its exits;
a branch to the block's own label loops inside the block function. The MAC and clip rings get only the entries
some reader can see (a least-fixpoint liveness over the pair graph, across blocks; JR, traps and pairs outside the
program count as reading everything, the end of a run as nothing); a reader whose entry was written earlier in the
same block reads a local. The status register (sticky bits included) and the MAC register are folded exactly at
block exits. Diff mode does not compare the rings (they are dead after a run and every value read from them lands
in a vi register).

Per pair the compiled code is exactly `step()`: pair counter, Q read with the precomputed `q_read_kind`, upper op into
locals, branch condition on the branch-VI view (tracked as "register written by the previous lower op + old value +
live flag"), lower op, upper commit, MAC/clip pipe, E handling; DIV/RSQRT latencies are the precomputed `q_delay`.
Branches become returns to the driver (or a loop inside the block) after their delay slot, `JR` a switch over the
labels (entry, branch targets, fall-throughs, MSCNT resume points, every `iaddiu viN, vi00, imm`). A branch in a delay slot, an encoding outside the census, a `JR`
to a non-label pc, the step limit or a non-canonical vf00/vi00 bail out to the interpreter at that pair boundary.
Build: `-DP3FES_VU1_AOT=ON` (`P3FES_VU1_AOT_DUMPS`, `P3FES_VU1_AOT_ONLY=<va,...>`); without it the table is empty
and `Aot` runs the interpreter.

Workload accounting: `p3fes --vu1-stats FILE --vu1-stats-at V1,V2,...` writes runs, pairs, kicks, VU1 time and the
time spent inside `IGifSink::kick` (the GS drawing synchronously) per (program, start pc) and interval
(`vu1_profile.h`, zero cost when off: one null test per run); `--vu1-capture DIR N` saves run inputs for the
differential tests (`P3FES_VU1_CAPTURES`).

## Per-family HLE hook plan (superseded by the AOT path, kept for reference)

Every run is one batch: `XTOP`/`XITOP` input, the material block `0x3BC–0x3FF`, 1–12 GIF packets out, persistent
state only in data memory (the `0x3FF.y` continuation). The planned hook, not implemented (24 §3 compares it with
the AOT path):

1. Identify the resident program by the uploaded image (hash of micro memory over the program extent, recorded per
   `MicroMemory::generation()`), mapped to the `vu1_prog_*` rows of `symbols/p3fes.sym` / the census JSON.
2. At `mscal`/`mscnt`, look up `(program, start pc)` in a table of HLE functions
   `void (VU1State&, IGifSink&)` that read TOP/ITOP and the material block and emit the same packets.
3. Differential mode: run the interpreter on a copy of the state and compare kicked packets and final data memory
   packet by packet; promote a family only after it matches across recorded batches.
4. Order (`14` §6 / RUNTIME_CONTRACT V-F1..F7): `g3_generic`, `g3_skin`, `g3_matfx`/`g3_skin_matfx`, `rt2d_*`
   (first needed at M2), `ptank_*`, `null_transform` (trivial). `unknown_tbl4` and the 28 unreferenced programs stay
   interpreted.

## Tests

`build/<dir>/bin/p3fes_vu1_tests` (ctest `p3fes_vu1_tests`): decoder vectors mirroring `vu1_decode.py --selftest`;
the census reproduction and a 64-pair trap-free smoke run of all 114 programs (both skip without the gitignored
dumps; `P3FES_VU1_DUMPS` overrides the directory); hand-derived semantic vectors, each tagged `(hand: VU User's
Manual)` or `(upstream behaviour, hardware-unverified)`; batch runs of `null_transform` (`0x5cdb10`) and `rt2d_fill`
`vu1_prog_089` (`0x741470`) on synthetic input, checked for `E` termination, packet sizes and bit-identical repeat
runs; `test_vu1_aot.cpp`: the compiled table against the dumps, the resident check, randomised states for every
compiled program (MSCAL 0 + the MSCNT chain + every resume point; `P3FES_VU1_AOT_ITERATIONS`), step limits, captured
battle-route inputs (`P3FES_VU1_CAPTURES`) and `Mode::Diff`, all compared field by field against the interpreter.
