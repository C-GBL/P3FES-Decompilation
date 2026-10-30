# 24 — VU1 acceleration: workload on the battle route, options, ahead-of-time compiled microprograms

_Written 2026-10-20 (F: machine, worktree branch of `main` `47da0fd`). Legend: **[obs]** measured in a run I did on
this machine (command in §6) · **[der]** arithmetic on observed numbers · **[inf]** inference / estimate. The
interpreter (`runtime/vu1/vu1_interp.cpp`) is the oracle throughout; "exact" means bit-identical registers, flags,
pipes, data memory, kicked GIF packets, run status and step counts against it._

## 0. Headline

* **Round 3 (§8, 2026-10-25) [obs].** Host SSE/AVX float under round-toward-zero + FTZ/DAZ with an exact per-lane
  fallback, vf/vi in registers per block, loops in place, flag-ring liveness across blocks, all 114 programs compiled
  by default (~4-6 min at -j 2). **Captured battle batches: 14-24x the interpreter** (g3_skin 17-23x, g3_generic
  13-15x; round 2: 3.4x), ~5.5 ns/pair on the heavily loaded machine (round 2: 17.7 quiet). Exact: `--vu1 diff` over
  all six routes 0 mismatches (climb: 15.9 M runs, 30.4 G pairs), gates byte-identical.

* **Round 2 (§7, rebased on `9773972`) [obs].** 4-lane soft-float helpers per dest mask (scalar kernel default; the
  AVX2 kernel is exact but measured slower), MAC/status liveness, longer blocks. **VU1 3.4× faster than the
  interpreter** in windowed D3D11 runs; **battle (vblanks 4600–6150) 0.416× → 1.032× real time, 12.4 → 30.7 fps**;
  field 0.51× → 1.14×. Still exact: `--vu1 diff` over the whole route 0 mismatches; dorm, M1 and battle gates 0
  differing bytes in both modes; ctest 16/16 on MSVC and clang-cl. The round-1 numbers below are kept as measured.

* **Workload [obs].** On the battle route the VU1 interpreter costs **36–41 % of host wall time** (field 3400–3500:
  38.0 %, battle 5700–5800: 36.2 %, results: 41.1 %), the GS drawing kicked packets another 45–55 %. Per battle
  vblank: 476 MSCAL/MSCNT runs, **0.93 M pairs**, 53.5 ms of pure VU1 time at 57 ns/pair; > 90 % of it in two
  programs, `vu1_prog_064_g3_skin` (62 %) and `vu1_prog_042_g3_generic` (24 %). Decode-cache refills after the
  game's MPG re-uploads: 2.8 % of VU1 time.
* **Options.** (A) faster interpreter: 1.5–2.5× [inf]; (B) ahead-of-time recompilation of the 114 programs:
  prototyped; (C) per-family native HLE: no higher ceiling than B under bit-exactness, weeks per family and high
  exactness risk. **Recommendation: B**, then 4-lane soft-float and flag liveness inside it (§5).
* **Prototype [obs].** `p3fes_vu1_aotgen` compiles **all 114 programs** (123,095 pairs) to one C++ function per
  label block, behind `-DP3FES_VU1_AOT=ON` + `--vu1 aot|diff`; the interpreter stays default and oracle. **Exact:**
  `--vu1 diff` over the whole route compared 1,754,344 runs (3.19 G pairs) field by field — **0 mismatches, 0
  bail-outs**; random states for every program, 425 captured battle batches, 50 M soft-float operand pairs: 0
  mismatches; dorm and M1 gates identical in both modes; ctest 16/16 on MSVC and clang-cl. **Speed:** VU1 time
  **1.8–2.3× lower** on the route intervals (battle 4,077 → 2,280 ms per 100 vblanks; `g3_skin` 1.69×,
  `g3_generic` 2.16×), **2.64×** on the captured batches with warm caches; whole route 551.6 → 470.5 s (1.17×).
* **Gap to the phase target [der].** The lead's bar (battle 1.0× with the GPU rasteriser) is ≥ 3.8× (≥ 2.6× with
  VU1 on its own thread). Measured headroom in the compiled code: soft-float ≈ 45 %, MAC-flag bookkeeping ≈ 20 % of
  its time; both are removable exactly (§5), projecting ≈ 4–5× over the interpreter [inf].

## 1. Method

* **Builds.** `build/vu1-msvc`: `msvc-x64-release` + `-DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt`, with
  `/Zi` + `/DEBUG` for the sampling profiler (same codegen as the Release preset), `-DP3FES_VU1_AOT=ON` for §4.
  Executables were copied out of the tree before each measured run so rebuilds could not touch them.
* **Route.** `--memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt --headless
  --quiet` (absolute paths in §6): field (Tartarus) around vblank 3500, battle at 5800, results at 6150. Intervals:
  field = vblanks 3400–3500, battle = 5700–5800, results = 5800–6100.
* **VU1 accounting (new, opt-in).** `p3fes --vu1-stats FILE --vu1-stats-at V1,V2,...` (`vu1_profile.h`): per
  (resident program, start pc) and interval: runs, pairs, kicks, kicked qwords, wall time inside MSCAL/MSCNT **minus**
  the time inside `IGifSink::kick` (the GS rasterises kicked packets synchronously inside the VU run; reported
  separately as "GS in kick"), cold runs, decode-cache rebuilds and the static Q analysis time. Programs are named by
  matching micro memory against the 114 dumps (`tools/ours/vu1/vu1_dump.py` re-creates them from the ELF: 114 of 114
  match the census SHA-256). Off = one null test per run.
* **Sampling profile.** `p3fes --profile` (1 ms) over vblanks 3300–3500 and 5600–5800 on the unmodified build,
  symbolised with `llvm-symbolizer` (the in-process DbgHelp pass could not open the copied PDB).
* **Load caveat [obs].** The machine was shared with other agents (10 `p3fes.exe` processes at one point), so
  absolute wall times are slower than an idle machine and vary run to run; every comparison below is between runs
  started at the same time on the same binary with only the `--vu1` mode changed.

## 2. The VU1 workload on the battle route

### 2.1 Share of host time (interpreter, run `vu1stats_2`, before the AOT work) [obs]

| Interval | vblanks | wall s | ms / vblank | real-time factor | VU1 (pure) | GS inside kicks | rest |
|---|---|---|---|---|---|---|---|
| boot → field (0–3400) | 3400 | 221.6 | 65.2 | 0.26× | 63.4 s (28.6 %) | 121.6 s (54.9 %) | 16.5 % |
| **field** 3400–3500 | 100 | 8.76 | 87.6 | 0.19× | 3.33 s (**38.0 %**) | 4.08 s (46.5 %) | 15.5 % |
| field → battle 3500–5700 | 2200 | 257.5 | 117.0 | 0.14× | 102.9 s (40.0 %) | 123.6 s (48.0 %) | 12.0 % |
| **battle** 5700–5800 | 100 | 14.80 | 148.0 | 0.11× | 5.35 s (**36.2 %**) | 8.09 s (54.7 %) | 9.1 % |
| results 5800–6100 | 300 | 24.45 | 81.5 | 0.20× | 10.05 s (41.1 %) | 10.96 s (44.8 %) | 14.1 % |

Real-time factor = 16.68 ms / (ms per vblank) [der]. Cross-checks from the parallel agents: the profiler
(23_performance_profile) measures 0.14–0.16× for the battle, VU1 39.8 % (41.1 ms/vblank) in the battle and 43.1 % in
the field, 1.87 M pairs and 1,068 runs per battle *frame* (two vblanks: our 0.93 M pairs and 476 runs per vblank);
the draw-path agent (22_rendering) 1,068 batches per battle frame, 47 program switches with 36.6k qw of microcode
re-uploaded per frame. The sampling profile agrees on the split (interpreter + fpu:
40.4 % of samples in the field window, 25.6 % in the battle window, GS raster the rest but a few %) [obs]; the lead's
draw-path profile (22_rendering.md) has 34.5 % VU1 / 55.1 % GS raster for battle 5750–6100.

### 2.2 Per vblank, interpreter [obs, der]

| Interval | runs / vblank | pairs / vblank | ns / pair (pure VU1) | VU1 ms / vblank | decode rebuilds / vblank | rebuild + Q-analysis ms / vblank |
|---|---|---|---|---|---|---|
| field 3400–3500 | 345 | 635,000 | 52.4 | 33.3 | 10.8 | 0.85 |
| battle 5700–5800 | 476 | 932,245 | 57.4 | 53.5 | 20.4 | 1.50 |
| results 5800–6100 | 327 | 573,910 | 58.4 | 33.5 | 14.2 | 1.05 |

The budget for real time is 16.68 ms per vblank for everything [der]: the interpreter alone needs 3.2× that in the
battle window.

**MPG re-uploads (the lead's question).** RenderWare re-uploads the microcode on every pipeline switch (22_rendering:
47 switches / 36.6k qw per battle frame). The interpreter keys its decode cache on `MicroMemory::generation()`, which
every `MPG` bumps: it re-decodes all 2048 pairs and rebuilds the jump list on the first fetch after a switch, and
re-derives the static Q classification lazily per pc. Measured cost: 2,040 rebuilds = 100 ms + 50 ms of Q analysis
per 100 battle vblanks, i.e. **2.8 % of VU1 time** [obs, der] — real, but not the problem. The AOT path below
replaces it with an image `memcmp` + an outside-branch scan per generation and keeps the decode cache only for the
rare Q re-verification (measured: 2,040 rebuilds → 0 per 100 battle vblanks, §4.4). Keying by content rather than
by the RW packet address keeps it independent of how the bytes arrived (any MPG sequence that leaves the same image
at address 0 hits the same compiled program).

### 2.3 Per program, battle 5700–5800 [obs]

| Program (census) | start pc | runs | pairs | VU1 ms | share | ns / pair | GS-in-kick ms |
|---|---|---|---|---|---|---|---|
| `vu1_prog_064_g3_skin` (`0x6f8b1c`) | 0x3c38 (MSCNT) | 22,593 | 57,490,580 | 3,325.8 | 62.1 % | 57.9 | 407.8 |
| `vu1_prog_042_g3_generic` (`0x6b8d4c`) | 0x3968 (MSCNT) | 9,261 | 18,231,218 | 924.8 | 17.3 % | 50.7 | 230.3 |
| `vu1_prog_042_g3_generic` | 0x0000 (MSCAL) | 2,842 | 5,329,322 | 335.6 | 6.3 % | 63.0 | 391.9 |
| `vu1_prog_064_g3_skin` | 0x0000 | 1,893 | 5,061,497 | 322.8 | 6.0 % | 63.8 | 30.8 |
| `0x6ef13c` (g3_matfx family) | 0x0000 + 0x36f0 | 950 | 3,049,233 | 179.5 | 3.4 % | 58.9 | 677.2 |
| `vu1_prog_093_g3_matfx` (`0x74b11c`) | both | 200 | 1,188,766 | 72.6 | 1.4 % | 61.1 | 398.1 |
| `0x6c294c` | both | 821 | 1,214,444 | 77.6 | 1.5 % | 63.9 | 982.0 |
| `vu1_prog_101_g3_skin_matfx` (`0x7634ac`) | both | 475 | 1,014,810 | 65.7 | 1.2 % | 64.8 | 2.9 |
| `vu1_prog_039_unknown_tbl4` (`0x5cd98c`, Im2D) | 0x0000 | 8,287 | 483,696 | 24.7 | 0.5 % | 51.1 | 2,431.4 |
| 6 more rows | | 273 | 160,901 | 23.7 | 0.4 % | | 2,534.9 |

Field 3400–3500: the same two programs dominate (`064` 63.9 %, `042` 19.0 % + 13.1 % = 32.0 % of VU1 time) [obs]. The g3
skin and generic families are > 90 % of VU1 time everywhere on the route; the Im2D sprite program `039` is cheap
on VU1 but its kicks carry 30 % of the GS-in-kick time (full-screen 2D).

## 3. Options

Common facts the estimates rest on [obs, §2, §4]: 0.93 M pairs per battle vblank; > 90 % of them in two programs
(`064` g3_skin, `042` g3_generic); the interpreter spends ~50–60 ns per pair (pure VU1); the host-profile split of
interpreter time in the field window is dispatch/decode/descriptor (`step` 29 %, `compute_upper` 26 % incl. inlined
FMAC, `lower` 9 %, `describe` 5 %, trap/census checks 2 %), flags (`set_flags` 8 %), soft-float calls that were not
inlined (`fpu::add` 8 %, `fpu::mul` 7 %), decode-cache rebuilds 4 % (of 427 VU1 samples). The real-time budget is
16.7 ms per vblank for the whole host.

| | (A) Faster interpreter | (B) AOT recompilation (prototyped) | (C) Per-family native HLE |
|---|---|---|---|
| What | Pre-decoded micro-op stream per program (op handler pointer + resolved operands), precomputed `UpperDesc`, no per-pair trap check (validate once per generation), decode cache keyed by image instead of generation, forced-inline soft-float, 4-lane FMAC | C++ generated per program (one function per label block, every field a constant), Q/flag pipes exactly as in the interpreter (§4) | Readable C++ per family (generic, skin, matfx, rt2d, ptank) producing the same packets |
| Expected VU1 speed-up on §2's workload | **[inf] 1.5–2.5×**: removes most of the dispatch/descriptor share but keeps an indirect call + operand loads per pair | **[obs] 1.8–2.3×** on the route intervals, **2.64×** on captured batches; [inf] 4–5× with §5 steps 1–2 | [inf] same ceiling as B with B's optimisations: bit-exactness forces the same soft-float operations, MAC/clip/Q pipe bookkeeping wherever an observer exists; the only extra freedom is hand-skipping state no consumer reads, which B can do by static liveness |
| Exactness risk | Low (same code paths, re-ordered) | Low and *measured*: every pair runs the interpreter's semantics from a shared header; Diff mode over the whole route, random states for all 114 programs and 425 captured batches: 0 mismatches (§4.3) | High: each family is ~1,500–1,950 pairs of RW-generated code with data-dependent paths (lighting, fog, clipping, strip restarts, continuations through `0x3FF.y`), Q-pipe and MAC-flag timing leaking into results; every divergence is a hand-debugging session |
| Effort | ~3–5 days | Prototype done in this session (generator ~600 lines, glue ~300, tests ~400); SIMD soft-float + flag liveness ~3–5 days more | Weeks per family; 5 families + the Im2D/unknown_tbl4 sprite programs |
| Gating | Interpreter tests + Diff against the old interpreter | `--vu1` interp / aot / diff, build option `P3FES_VU1_AOT`, Diff mode, `test_vu1_aot.cpp`, replay gates in both modes | Per-family switch + Diff against the interpreter; promote per family after recorded batches match |
| Coverage | All 114 programs, any code | All 114 programs (any other image falls back to the interpreter) | Only the families written; the rest interpreted |

Combinations: A is subsumed by B (B removes the same overheads statically). C on top of B buys nothing B's
optimiser cannot express (it is the same arithmetic, written by hand). The remaining lever after B is the
soft-float cost itself (§5), which is the same for all three.

## 4. Prototype: ahead-of-time compiled microprograms (option B)

### 4.1 Design

* **Generator** `p3fes_vu1_aotgen` (`runtime/vu1/aotgen/vu1_aotgen.cpp`, built and run by CMake with
  `-DP3FES_VU1_AOT=ON`): reads the 114 dumps + census names, writes `vu1_aot_<code_va>.cpp` per program and the
  table `vu1_aot_programs.cpp` into the build tree (they embed game code: build output, never committed). All 114
  programs, 123,095 pairs, 20,194 labels, 1.0 s [obs].
* **Per pair** the generated statements are `VU1Interpreter::step()` for that pair with every decoded field a
  constant: `++t` (pair counter), the Q read with the interpreter's own static classification (`detail::q_read_kind`,
  run at generation time), the upper op into locals, the branch condition on the branch-VI view, the lower op (one
  inline helper per `lower()` case, `vu1_aot_rt.h`), the upper commit, MAC flags + flag pipe, CLIP + clip pipe, E
  handling; DIV/RSQRT latencies are the precomputed `detail::q_delay`. The upper-op table, FMAC datapath and flag
  rules live in `vu1_semantics.h`, moved verbatim out of the interpreter so both engines share them.
* **Branch-VI delay** without the interpreter's 32-byte snapshot per pair: each pair records which vi register its
  lower op wrote, the old value and whether the snapshot is live (`pw/pv/pl`); a conditional branch reads
  `(pl && pw == r) ? pv : vi[r]`. In straight-line code these fold to constants or one load.
* **Control flow.** Labels = entry 0, branch targets, fall-throughs after delay slots, MSCNT resume points and every
  `iaddiu viN, vi00, imm` whose register some `JR` jumps through or some `ISW/ISWR` stores (the JR targets and
  `0x3FF.y` continuations the programs build; a JR anywhere else bails out, which never happened on the route). One C++ function per label block returning the next
  label; a per-program driver switches on it. (A first version emitted one function per program with gotos: MSVC
  stops inlining inside ~2,000-pair functions — 4,050 `std::array::operator[]` calls remained in `vu1_prog_064` — and
  with forced inlining the code got slower than the interpreter (89 vs 43 ns/pair in the benchmark) [obs].)
* **Bail-out.** Anything the compiled code does not handle hands the state to the interpreter at a pair boundary,
  exactly as `step()` would leave it (pc/npc, pair counter, branch-VI snapshot, ending flag): a branch or E in a delay
  slot, an encoding outside the census (the interpreter then traps identically), a JR to a non-label pc, the step
  limit (checked per block against the block's maximum length), a non-canonical vf00/vi00 at entry. On the route:
  **0 bail-outs in 1,754,344 runs** [obs].
* **Resident check** (`AotIndex`, once per micro generation): image `memcmp` from address 0; the Q analysis read no
  pair outside any image (0 of 114 programs) [obs]; code left over in micro memory from a larger program can branch
  into pairs whose predecessors a Q classification enumerated — then the affected readers are re-classified with
  the interpreter's own analysis on the real memory and the program runs only if every kind is unchanged; the
  verdict is cached by the bytes outside the image. Without this, `0x6ef13c` and `0x74b11c` were rejected on every
  captured battle run (0/48 each) [obs]; with it all 425 captured runs execute compiled code and match.
* **Exact fast soft-float** (`fmul`/`fadd`/`fsub` in `vu1_aot_rt.h`): for operands with exponent field 1..254 the
  48-bit product and the aligned sum (≤ 26 bits after `fp::add`'s truncating alignment) are exact in a host double,
  so the host rounding mode never applies (exact cancellation returns +0 explicitly, as `fp::add` does); narrowing
  truncates like `fp::from_double`; everything else calls `fp::` itself. 4,000,000 biased random operand pairs per
  test run (alignments ±30 binades, near and exact cancellation, overflow/underflow exponents), 50,000,000 once:
  0 mismatches in mul, add, sub [obs].
* **Modes.** `VU1Interpreter::set_mode(Interp | Aot | Diff)`, app `--vu1 interp|aot|diff` (default interp; exit code
  5 when Diff found a mismatch). Diff runs the interpreter and the AOT path from the same state on every run and
  compares vf/vi/ACC/Q/P/I/R, MAC/status/clip, the flag and Q pipes, pc/npc/tpc, running/ending, the branch-VI
  snapshot, all 16 KiB of data memory, every kicked packet, status, steps, trap and statistics; the interpreter's
  outcome is kept.

### 4.2 Gating

Default stays the interpreter. `-DP3FES_VU1_AOT=ON` builds the table (all 114 programs: generator 1.0 s, MSVC
`/O2` compile of the 114 files ≈ 17–21 min at `-j 4` on the loaded machine, clang-cl Debug for a 4-program subset
in the 7.4-min test build) [obs]; `--vu1 aot` selects it at run time, `--vu1 diff` checks it. Without the build
option `--vu1 aot` runs the interpreter (empty table).

### 4.3 Exactness [obs]

| Check | Inputs | Result |
|---|---|---|
| `--vu1 diff`, whole battle route 0–6150 (final build) | 1,754,344 runs, 3,187,514,104 compiled pairs, every run compared field by field | **0 mismatches**, 0 bail-outs, 0 interpreted runs; frame at 6150 identical in interp / aot / diff (`CFAA5A61…`) |
| `test_vu1_aot.cpp` randomised | 114 programs × 6 random states × (MSCAL 0 + MSCNT chain of 4 batches + every resume point): 3,415 runs, 2,263 entering compiled code | 0 mismatches |
| captured battle inputs (`--vu1-capture`, vblanks 5700–5800, 24 per program/pc) | 425 runs of 9 programs | 425 compiled, 0 bail-outs, 0 mismatches |
| step limits 1, 2, 3, 7, 50, 333 | `vu1_prog_113` | equal pc/state/status at the limit |
| fast soft-float | 50,000,000 biased operand pairs (+ 4 M in every ctest run) | 0 mismatches in mul / add / sub |
| dorm gate (`to_dorm.txt`, vblank 4900) | interp and aot | frame `EE0EB5DA…` both, `differing bytes: 0` both |
| M1 gate (`sky:11`) | interp and aot | frame `E3A93615…` both, `differing bytes: 0` both |
| battle gate (`to_battle.txt`, vblank 6150; the lead's new third gate) | interp and aot | frame `CFAA5A61…` = `battle_ref_6150` in both; interp vs aot snapshots: **0 differing bytes**; both vs `battle_ref_6150`: 23 bytes in 9 heap runs at `0xFFCDE0–0xFFCE1A`, identical in both modes, so not VU1 (this branch is `47da0fd`; the reference was taken 15:03 from the lead's newer tree) |
| ctest | MSVC Release (`build/vu1-msvc`, AOT on) / clang-cl Debug (`build/vu1-clang`, AOT on, 4 programs) | 16/16 / 16/16 (`p3fes_recomp_emit_subset` skipped as on main) |

Bugs the differential tests caught in the generator during the session (all fixed): `npc` after the E delay slot
one pair short; the branch-VI snapshot live flag after `LOI`/exempt ops; the `BAL` link stored before the snapshot
of the old register; the resident check rejecting `0x6ef13c`/`0x74b11c` on every real battle run (leftover code
branching into analysed pcs) — now re-verified instead.

### 4.4 Speed [obs]

Same binary, `--vu1 interp` and `--vu1 aot` started at the same moment on the same machine (§1 load caveat),
`--vu1-stats` intervals; "VU1" excludes the GS work inside kicks.

| Interval | interp VU1 ms | aot VU1 ms | **VU1 speed-up** | interp ns / pair | aot ns / pair | wall interp → aot |
|---|---|---|---|---|---|---|
| boot → field 0–3400 | 75,108 | 33,037 | **2.27×** | 68.2 | 30.0 | 264.9 → 227.7 s |
| field 3400–3500 | 3,702 | 1,827 | **2.03×** | 58.3 | 28.8 | 9.41 → 8.51 s |
| field → battle 3500–5700 | 96,177 | 45,325 | **2.12×** | 55.1 | 26.0 | 244.2 → 202.6 s |
| battle 5700–5800 | 4,077 | 2,280 | **1.79×** | 43.7 | 24.5 | 11.54 → 11.59 s (GS-in-kick 6.45 → 7.95 s: load noise) |
| results 5800–6100 | 7,866 | 4,061 | **1.94×** | 45.7 | 23.6 | 19.47 → 18.12 s |
| whole route 0–6150 | | | | | | **551.6 → 470.5 s (1.17×)** |

Per program, battle 5700–5800: `vu1_prog_064_g3_skin` resume (pc `0x3c38`) 2,513 → 1,484 ms (1.69×, 43.7 → 25.8
ns/pair); `vu1_prog_042_g3_generic` resume (`0x3968`) 715 → 331 ms (2.16×, 39.2 → 18.2 ns/pair) [obs]. Decode-cache
rebuilds: 2,040 (81 ms) → 0 per 100 battle vblanks; Q analysis 37 ms → 0 [obs].

Benchmark (`P3FES_VU1_BENCH=20`, the 425 captured battle runs, warm caches): interpreter 78.7 ns/pair, AOT
29.8 ns/pair = **2.64×** [obs]. Bounds measured with deliberately wrong builds (2 programs): soft-float replaced by
integer stand-ins → 14–16 ns/pair; MAC-flag writes removed → 18–23 ns/pair; against 22–29 ns/pair for the real
code in the same runs [obs] → soft-float ≈ 45 %, MAC/status/pipe bookkeeping ≈ 20 % of the compiled code's time
[der]. Earlier code-shape variants: one function per program calling `fp::` (no forced inlining): 1.50–1.55× on
the route; the same with forced inlining: 0.5× in the benchmark (MSVC gave up on the 2,000-pair functions); one
function per label block: 2.1–2.75× in repeated benchmark runs [obs].

**Against the lead's targets** (23_performance_profile: battle 1.0× with the GPU rasteriser needs VU1 ≥ 3.8× faster,
≥ 2.6× with VU1 on its own thread): the prototype reaches 1.8–2.6× today; §5 lists the measured headroom.

## 5. Recommendation and next steps

**Recommendation: (B), the AOT path, as the VU1 engine — promote it from opt-in to default after the gates have run
green in both modes on main for a few days; keep the interpreter as the oracle (Diff mode, tests) and as the
fallback for any image that is not one of the 114.** It is already exact on everything we can throw at it, covers
all programs, and costs ≈ 17–21 min of `-j 4` build for all 114 on the loaded machine (hot-family subset via
`P3FES_VU1_AOT_ONLY=006f8b1c,006b8d4c` for quick iteration: < 1 min).

What it does *not* do is make VU1 free. Measured bounds on the benchmark (§4.4): with the soft-float removed the
compiled code would run at ~14–16 ns/pair, with the MAC-flag bookkeeping removed at ~18–23 ns/pair, against
22–29 ns/pair now. Real time needs the whole host in 16.7 ms per vblank; at 0.93 M pairs per battle vblank that is
≤ 3 ns/pair if VU1 were to take a fifth of it [der]. Next steps, in order of value per effort [inf]:

1. **4-lane soft-float** in the generated code: one helper call per upper op instead of 4–8 scalar calls, AVX2
   (`cvtps_pd` → `mul_pd`/`add_pd` → integer narrowing) with a per-lane fallback mask to `fp::`, CPU-dispatched; the
   double-precision identity is already proven exact (§4.1, 0 mismatches). Expected: soft-float share (≈ 45 %) cut
   ~3× → ~1.4×.
2. **MAC/clip-flag liveness** in the generator: a MAC write is observable only through an `FMAND` ≥ 4 pairs later
   before it is superseded, the run-end `mac`/`status`, or a bail-out; skip the computation where none can see it
   (bail sites become rematerialisation points). Expected ≈ 15–20 % [inf from the no-MAC bound].
3. **Register caching per block** (vf/vi in locals across a block, written back at block exits) once 1–2 land.
4. Then re-measure: the GS rasteriser (46–55 % of wall, larger than VU1 everywhere) is the bigger lever for the
   phase goal and belongs to the D3D11 lane; with the GS on the GPU, VU1 (even after steps 1–2) becomes the
   dominant CPU cost, and moving VU1 + GIF to their own deterministic thread (the profiler's 2.6× bar) is the next
   structural step.

The per-family HLE (C) is not recommended: it cannot beat B's ceiling under the bit-exactness rule and carries
weeks of exactness debugging per family. The interpreter optimisation (A) is subsumed by B.

## 6. Reproduction

```powershell
. F:\P3FES-PORT\p3fes-port\tools\env.ps1
# 1. dumps (gitignored; 114 of 114 must match the census)
python -I tools\ours\vu1\vu1_dump.py --elf F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21
# 2. emit the EE code and configure (the /Zi flags only for --profile)
cmake --preset msvc-x64-release -B build\vu1-msvc -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt `
  -DP3FES_RT_EXEC_ELF=F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21 -DP3FES_VU1_AOT=ON `
  "-DCMAKE_CXX_FLAGS_RELEASE=/O2 /Ob2 /DNDEBUG /Zi /FS" "-DCMAKE_EXE_LINKER_FLAGS_RELEASE=/DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF"
cmake --build build\vu1-msvc -j 4
# 3. workload + comparison (run the modes side by side; same binary)
$route = "--memcard F:\P3FES-PORT\p3fes-port\extracted\_ours\cards\tartarus.ps2 --replay-input F:\P3FES-PORT\p3fes-port\config\inputs\to_battle.txt --elf F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21 --iso F:\P3FES-PORT\p3fes-port\input\persona3fes.iso --headless --quiet"
p3fes.exe $route --vu1 interp --vu1-stats st_interp.txt --vu1-stats-at 3400,3500,5700,5800,6100,6150 --frames 6150 --png interp.png
p3fes.exe $route --vu1 aot    --vu1-stats st_aot.txt    --vu1-stats-at 3400,3500,5700,5800,6100,6150 --frames 6150 --png aot.png
p3fes.exe $route --vu1 diff   --frames 6150 --png diff.png      # prints "diff mismatches N"; exit code 5 when N > 0
# 4. captures for the differential test (game data: keep them out of the repo)
p3fes.exe $route --vu1-stats st.txt --vu1-stats-at 3400,3500,5700,5800 --vu1-capture <dir> 24 --frames 5800
$env:P3FES_VU1_CAPTURES="<dir>"; build\vu1-msvc\bin\p3fes_vu1_tests.exe -tc=*aot*
$env:P3FES_VU1_BENCH="3"; build\vu1-msvc\bin\p3fes_vu1_tests.exe -tc=*benchmark*
```

## 7. Round 2 (rebased on `9773972`): 4-lane soft-float, MAC liveness, longer blocks

### 7.1 What changed (all exact; every check of §4.3 re-run)

* **4-lane FMAC helpers.** ADD/SUB/MUL/MADD/MSUB in all forms are one call per upper op (`vadd<D>`, `vmul_s<D>`,
  `vmadd<D>` ... in `vu1_aot_rt.h`), instantiated per dest mask `D` so only committed lanes are computed. Two
  kernels: the scalar double-precision fast paths of §4.1 (now also handling zero/denormal operands inline, as
  `fp::mul/add` define them) and an AVX2 kernel (`cvtps_pd` → `mul_pd`/`add_pd` → narrowing on 64-bit lanes, per-lane
  fallback to `fp::`), chosen by a CPU check at start-up (`aot_avx2()`, CPUID AVX2 + OS YMM state). **Measured: the
  AVX2 kernel is the slower one on this Ryzen 7 5800X with MSVC 14.44** (captured battle batches: 24.7 vs 17.7
  ns/pair; also 22 vs 16.5 with the generated files compiled `/arch:AVX2`, and when out of line) [obs] — the scalar
  lanes are four short independent chains, the AVX2 kernel one long one (convert, permute, two blends, 64-bit
  compares). So the scalar kernel is the default on every CPU and AVX2 is opt-in (`P3FES_VU1_AVX2=1`); both are
  tested on every run of `p3fes_vu1_tests` (12.5 M vectors × 5 ops each, 0 lane mismatches; the 425 captured runs on
  the non-default kernel, 0 mismatches) [obs].
* **MAC/status liveness.** Per block, a MAC write followed by another write `b` is skipped (no MAC register store, no
  pipe entry) when no `FMAND` lies in `[a + 4, b + 4)` and that window ends before the block can be left (the next
  conditional exit or the block end); blocks that can hand over to the interpreter mid-block keep every write. The
  status register keeps its exact value: `sem::set_flags` composed over a block is `(status & 0xFF0) | low(last) |
  (OR of low(all)) << 6`, folded at every block exit from two locals, with MAC computed by SSE2 compares. The MAC pipe
  is compared by what an FMAND can still read (`same_mac_view`, next five pair times), and `FlagPipe::status_v` is not
  maintained (no op reads it). Statically 55–60 % of the MAC writes of the g3 programs are dead (`vu1_prog_064`: 830
  dead / 520 live) [obs].
* **Longer blocks.** No label after a conditional branch any more: the not-taken path continues in the same block
  function (labels 20,194 → 10,461 for the 114 programs); blocks are capped at 48 pairs because MSVC `/O2` did not
  finish one 309-pair straight-line block of `vu1_prog_006` in 40 minutes [obs]. `/GS` cookies are off for block
  functions (`__declspec(safebuffers)`; their arrays are fixed 4-lane temporaries).

### 7.2 Exactness [obs]

| Check | Result |
|---|---|
| `--vu1 diff`, battle route 0–6150 | 1,754,344 runs, 3,187,514,104 compiled pairs, **0 mismatches**, 0 bail-outs; frame `CFAA5A61…` |
| randomised states, 114 programs | 3,415 runs, 0 mismatches |
| captured battle inputs, both soft-float kernels | 425 + 425 runs, 0 mismatches, 0 bail-outs |
| fast soft-float | 50 M scalar operand pairs + 12.5 M 4-lane vectors × 5 ops per kernel: 0 mismatches |
| dorm gate | interp and aot: frame `EE0EB5DA…`, `differing bytes: 0` |
| M1 gate | interp and aot: frame `E3A93615…`, `differing bytes: 0` |
| battle gate (vs `battle_ref_6150`, with `bcbb841` on main) | interp and aot: frame `CFAA5A61…`, **`differing bytes: 0`** |
| ctest | MSVC Release (AOT on, 114 programs) 16/16; clang-cl Debug (AOT on, 4 programs) 16/16 |

### 7.3 Speed [obs]

**Windowed, D3D11 GS** (`--gs-backend d3d11 --unpaced --zones`, battle route to vblank 6200, the two modes run one
after the other with a 15-min kill timeout; `tools/ours/perf/zones_report.py`). Battle = vblanks 4600–6150 (the
profiler's range); the game flips every second vblank (0.497 flips per vblank), so fps = x real time × 29.8.

| Range | VU1 ms / vblank interp → aot | **VU1 speed-up** | x real time interp → aot | fps interp → aot |
|---|---|---|---|---|
| field 3400–3500 | 25.87 → 7.58 | **3.41×** | 0.512 → **1.143** | 15.3 → 34.0 |
| battle 4600–6150 | 33.64 → 9.84 | **3.42×** | 0.416 → **1.032** | 12.4 → 30.7 |
| battle 5700–5800 | 38.64 → 11.36 | **3.40×** | 0.363 → **0.902** | 10.8 → 26.9 |
| whole run 0–6200 | | | wall 164.1 → 71.5 s | |

With D3D11 the remaining battle time per vblank (aot) is VU1 9.84 ms, VIF1 2.02, EE 1.70, GS raster (now the D3D11
submission path) 1.54, GIF 0.81 [obs]. Run side by side instead (both processes at once, more contention), two pairs
measured 2.57× / 2.77× on VU1 and 0.85× / 0.87× real time for the battle range.

**Headless, software GS** (`--vu1-stats`, nine runs in parallel on the shared machine, so noisier): VU1 time
3,965 → 1,407 ms per 100 battle vblanks (**2.82×**, 42.5 → 15.1 ns/pair), boot→field 3.31×, field 2.78×,
field→battle 3.19×, results 2.74×; whole route 493.5 → 398.7 s (the software GS is 64–74 % of the AOT run's wall).

**Benchmark** (425 captured battle batches, warm caches, same process): interpreter 60.3 ns/pair, AOT scalar kernel
17.7 ns/pair = **3.40×**, AVX2 kernel 24.7 ns/pair [obs].

**Against the targets:** VU1 is **3.4× faster** than the interpreter in the windowed D3D11 runs — above the 2.6× bar
for a VU1 thread, short of the 3.8× bar the profiler set — and the battle range already runs at **1.03× real time
(30.7 fps)** windowed with D3D11 on this machine (5700–5800, the heaviest 100 vblanks: 0.90×). Remaining measured
headroom in the compiled code (benchmark, deliberately wrong builds before the last two changes): soft-float ≈ 32 %,
MAC bookkeeping ≈ 19 % of its time; the next exact steps are register caching per block and a cheaper scalar mul
path (integer, no double round trip), then moving VU1 + GIF to their own thread (§5).

## 8. Round 3 (2026-10-25, on `main` `4709fee` / `4109078`): exact host float, registers per block, flag liveness across blocks

The user's order (2026-10-25): graphics at about a tenth of its cost, then at most 15 ms of host time per game frame
at p99. This round keeps the bit-exact contract of §4 (the interpreter is the oracle) and removes most of what §7
left: soft-float, flag bookkeeping, memory round trips for the registers, and the interpreted programs.

### 8.1 What changed

* **Exact host float** (`runtime/vu1/vu1_aot_rt.h`). A compiled run sets MXCSR to round toward zero + FTZ + DAZ
  (`CsrScope`; the host mode comes back around XGKICK, where the GS runs, and around RSQRT and ERCPR, whose double /
  float roundings depend on the mode). Under that mode:
  * `MULPS` is `fp::mul` for every operand pair except exponent-255 operands (Inf/NaN to the host) and overflow (the
    host gives `0x7F7FFFFF`; the EE has a whole extra binade and clamps at `0x7FFFFFFF`). Both show as a result lane of
    magnitude `>= 0x7F7FFFFF`, so a three-instruction guard per op sends exactly those lanes to `fp::` (the "slow
    path"; the other lanes keep the host result, lanes are independent). Underflow: FTZ gives the signed zero
    `fp::mul` packs (round toward zero never crosses 2^-126 upwards); DAZ gives `fp::mul`'s signed zero for a
    zero / denormal operand.
  * `fp::add` is *not* IEEE round toward zero: it aligns the smaller operand with one guard bit and drops the bits
    below it (§4.1, ADR-0012). The kernel reproduces the alignment in floats: for an exponent difference >= 2 the
    smaller operand `s` becomes `(s + C) - C` with `C = copysign(2^(E_big - 1), s)` (round toward zero truncates `s` to
    a multiple of ulp(big) / 2, both steps are exact, and at a difference >= 25 it becomes 0 as in `fp::add`), then the
    host adds with round toward zero. Exact cancellation is +0 in that mode, as `fp::add` returns.
  * DIV by `DIVSS` with the same guard: `fp::div` = `from_double(RN_double(a / b))` truncated, and a quotient of two
    24-bit significands is never within 2^-47 of a 24-bit boundary unless it is one, so the double rounding cannot
    cross it and the result is the truncated exact quotient.
  * ITOF (`CVTDQ2PS` rounds toward zero, the power-of-two scale is exact), FTOI (`CVTTPS2DQ`, saturation fixed up),
    MAX / MINI / CLIP (integer keys), MAC flags (compares): exact by construction. vf00-lane peepholes: MUL by 1.0 =
    flush, MUL by +0 = signed zero, ADD / SUB of +0, MADD / MSUB by 1.0 = ADD / SUB (`fp::add` flushes its operands).
  * MSVC never folds or rewrites SSE float intrinsics (checked: constant operands, `x * 1.0`, `x + -0`); clang would,
    so clang builds of these files use `/fp:strict`.
* **Registers per block** (`vu1_aotgen.cpp`). vf / ACC are `__m128i` locals and vi / clip integer locals for a whole
  block function, loaded once and written back at each exit (what the block wrote so far; everything it writes when
  it loops). A branch to the block's own label is a loop inside the function (the vertex loops), the step limit
  checked per iteration. Blocks up to 96 pairs (48 before; the round-2 code took MSVC > 40 min on a 309-pair block;
  this code compiles all 114 programs in ~4 min at -j 2). The generated files are built `/arch:AVX2` (VEX three-operand
  forms, ~10 % faster in the benchmark); `aot_cpu_ok()` checks AVX2 and OS YMM state, else the interpreter runs
  (`P3FES_VU1_AOT_ARCH=SSE41` builds for SSE4.1-only hosts).
* **Flag rings across blocks.** An FMAND at time q reads the newest MAC entry inserted with ts <= q - 4; FCAND / FCOR
  / FCGET the newest clip entry with ts <= q - 3 (FCSET inserts with ts = q - 4: visible from the next pair). A reader
  is *static* when that entry is inserted earlier in the same block: it reads a local. A ring entry is kept only if
  some other reader on some path can read it before it is superseded: a least fixpoint over the pair graph (nodes =
  pair x {normal, delay slot, after E}; state = the window of relative times in which the entry is still readable).
  JR, traps, pairs outside the program and delay slots the compiled code does not run count as reading everything,
  the end of a run as nothing (`start()` rebuilds the pipe from mac / status / clip). A bail-out at the step limit hands
  over at a label and the interpreter follows the same graph, so it needs no special case (test: runs stopped at 5,
  40, 300 and 1200 pairs and continued agree). Result: **634 of 81,499 MAC ring entries and 1,306 of 3,163 clip entries
  kept** (round 2 kept ~40 % of the MAC writes). The MAC register is folded at exits from the last write. The status
  register's sticky ZS / SS bits are only ever set (no FSSET in the census; a VU1 reset clears them), so a compiled run
  starts only once both are set and needs no sticky bookkeeping; the interpreter takes the others (0.3-7.6 % of the
  runs, 0.02-0.8 % of the pairs on the routes: a per-write sticky update under a block-level test would compile them
  too, at ~3 % in the benchmark); OS is set by the slow path, the
  only place an overflow lane appears. Diff mode no longer compares the rings: they are dead after a run and every
  value a reader takes from them lands in a vi register, which is compared.
* **Coverage.** All 114 programs compiled by default (`gate.ps1`; `-HotAot` builds the old pair); `--vu1 aot` is the
  default in AOT builds. Interpreted runs on the six routes: 0, except `006b5e9c` (98 runs on fusion, 2,850 on the
  climb, ~12 k and ~350 k pairs: negligible): leftover code outside its image branches into pcs its Q analysis
  enumerated and the exact re-classification (§4.1 resident check) changes a Q kind, so the compiled program would
  read Q at the wrong pair. Compiling it exactly would need run-time Q kinds in the hot code; not worth ~0.001 % of
  the pairs.
* **Upload caching.** `MicroMemory::write` bumps the generation only when a byte changes (RenderWare re-uploads the
  resident program on every pipeline switch: 86,982 MPG writes on the fusion route; track D's suggestion); the
  residency verdict is looked up by the bytes outside the image first.
* **Slow path.** Vectorised for the common case (an exponent-255 lane of an unused bone-matrix row times a zero
  weight in `g3_skin`'s skinning: `fp::mul` gives the signed zero, then the host add is exact again); remaining lanes
  go through `fp::`. Frequency: one slow op per ~700 pairs on the captured battle batches, ~250 on the dorm route,
  ~120 in the climb's battles. `P3FES_VU1_SLOW_SITES=1` prints the hottest sites (battle route: `g3_skin` pairs
  0x5A-0x60, the bone-matrix transform, then 0xF1, 0xFE, 0x2BE, 0x2CD).

### 8.2 Exactness [obs]

| Check | Result |
|---|---|
| `--vu1 diff`, six routes | 0 mismatches on every route (final build): dorm 316,061 runs, m1 55, battle 1,754,344 (3.19 G pairs), fusion 1,121,155, shop 900,684, climb 15,943,858 (30.4 G pairs); "bails" = runs started before ZS / SS were set, taken by the interpreter (dorm 23,931, battle 5,361, climb 9,426, fusion 6,658, shop 6,964, m1 all 55) |
| merge gate (`gate.ps1 -FastGs`, MSVC + clang-cl) | six routes byte-identical to the references; suites green except the known `field8_sys` case on main |
| randomised states, 114 programs | 3,480 runs, 0 mismatches (one state in four without ZS / SS: the interpreter) |
| captured battle inputs | 425 runs, all compiled, 0 mismatches |
| kernels vs `fp::` / `sem::` | 5 M biased vectors x 26 checks (mul, add, sub, madd, msub, max, min, FTOI / ITOF 0 / 4 / 12 / 15, MAC, CLIP, DIV, the vf00 forms, the OS bit): 0 mismatches |
| step-limit hand-over | 456 runs stopped at 5 / 40 / 300 / 1200 pairs and continued: 0 mismatches |

### 8.3 Speed [obs; ~8 agents' builds and games kept the machine at 100 % CPU throughout: absolute numbers are inflated and noisy]

Captured battle batches (305 runs of compiled programs; the two engines alternate per round in one process):

| Program | interpreter ns/pair | round 3 ns/pair | speed-up |
|---|---|---|---|
| all | 87-110 | 6.3-6.7 (best of six processes 5.5) | 14.5-16.3x |
| `vu1_prog_064_g3_skin` | 94-104 | 4.8-5.5 | 17-23x |
| `vu1_prog_042_g3_generic` | 87-104 | 6.7-7.0 | 13-15x |
| `vu1_prog_101_g3_skin_matfx` | 102-112 | 5.1-5.5 | 20x |
| `vu1_prog_033 / 035_ptank_spr3d` | 95 | 8.5-11 | 9-11x |
| `vu1_prog_039_unknown_tbl4` (Im2D, 59 pairs per run) | 69-154 | 11-21 | 6-7x |

Routes (`tools/ours/perf/bench.py`, headless exact, run side by side so both see the same load; `before` = main
`4465367`'s build: round 2 for `g3_skin` / `g3_generic`, the interpreter for every other program):

| dorm segment (per game frame) | VU1 CPU ms before -> after | graphics CPU ms | game-thread CPU p99 ms |
|---|---|---|---|
| event (the opening scene) | 2.1 -> 0.4 | 3.5 -> 1.3 | 90.3 -> 57.5 |
| load | 2.5 -> 0.3 | 3.6 -> 1.3 | 90.9 -> 54.4 |
| whole route | 0.7 -> 0.1 | 2.4 -> 1.6 | 88.8 -> 55.5 |

The battle, fusion and shop runs of both builds were killed by bench.py's timeout (route time x 1.2 + 120 s) on the
saturated machine. The zone profiler on the battle route (`--zones`, vblanks 4600-6150, two runs at different times of
the same saturated day, so only indicative): VU1 35.0 -> 14.4 ms per vblank; `g3_skin` 35.4 -> 15.4 ns/pair,
`g3_generic` 33.1 -> 18.5, the formerly interpreted `0x6EF130` / `0x7634A0` / `0x74B110` / `0x6C2940` / Im2D `0x5CD980`
115-143 / 96 -> 20-51 ns/pair (zone time includes the per-run overhead; the captured-batch benchmark above is the
clean comparison).

On a quiet machine: `python -I tools\ours\perf\bench.py run --exe <before> --out A --modes headless` and the same for
`<after>`, then `bench.py compare A B`; the VU1 microbenchmark: `$env:P3FES_VU1_CAPTURES=<dir>;
$env:P3FES_VU1_BENCH=10; p3fes_vu1_tests -tc=*benchmark*` (captures: `p3fes ... --vu1-stats F --vu1-stats-at 5700,5800
--vu1-capture <dir> 24`).

**Against 15 ms per game frame:** the battle runs ~1.6 M VU1 pairs per game frame (0.81 M per vblank), so the exact VU1
costs ~9 ms per frame at the loaded machine's ~5.5 ns/pair, an estimated 4-5 ms quiet (round 2: 17.7 ns/pair quiet,
~28 ms per frame). That is still a third of the budget on the exact path; the play path's HLE (track B) and VU1 off
the game thread (track C) take it below. Remaining exact headroom in the compiled code (the `g3_skin` vertex loop,
~24 instructions per pair): register spills (25 vf registers live in 16 XMM), data-memory address arithmetic, the
per-op guard (a per-site range proof could drop guards where operands are provably finite).
