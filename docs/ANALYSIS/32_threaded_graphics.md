# 32 — The threaded graphics pipeline: VU1 and the GS front end off the game thread, exactly

_Graphics team track C (2026-10-25). The user's orders: graphics ≈ 4 ms of CPU per frame on the game thread, then
(same day) **every game frame ≤ 15 ms of host time at the 99th percentile, frame rate as high as possible**. This is
the design, the sync rules, how often the EE waits, the determinism evidence and the measurements of
`p3fes/gs/gs_pipeline.h` (`--gs-threads`). Tags as in doc 23: **obs** = printed by a run, **der** = arithmetic on obs
numbers, **inf** = a design statement. **Load caveat:** every run here shared the 8-core machine with ~8 other agents
(GetSystemTimes busy share 0.99-1.00 in most segments): wall times are inflated and noisy (descheduled threads show
up as multi-second "frames"); CPU times (`QueryThreadCycleTime`) are the trustworthy numbers. §8 has the commands
for a quiet machine._

## 0. Headline

* **What moved.** VU1 (UNPACK / MPG into VU1 memory, every MSCAL / MSCALF / MSCNT run, its XGKICKs, the native
  renderer's VU1 hook) runs on a **VU1 worker**; the GsCore front end (PATH1/2/3 register writes, transfers, CLUT
  loads, the D3D11 op recorder or the software rasteriser, the native renderer's triangles) runs on a **GS worker**;
  the EE (game) thread keeps guest code, the DMAC, VIF1's codes, registers, stalls and interrupts, GIF arbitration
  and the GS privileged registers, and hands the rest over as an ordered command stream. Default `--gs-threads 2`
  (`1` = one worker, `0` = the stream on the EE thread, `off` = the synchronous model).
* **Exact and deterministic.** Each worker executes its commands in stream order on the objects the synchronous model
  uses, and the EE waits wherever it could observe a worker's result (§3): guest memory, GS memory and the pictures
  are the synchronous model's whatever the threads' timing (obs, §5: the six gate routes byte-identical with 2
  workers, 1 worker and inline, repeated; windowed d3d11 runs, interpolated and `--renderer native`, give eeMemory.bin
  0 differing bytes and the same GPU pictures as `--gs-threads off`).
* **Game-thread CPU** (obs, battle 4600–6150, main at 11712ad: full VU1 AOT round 3, paired runs under the same load,
  CPU time of the EE thread): headless d3d11 exact **21.2 → 7.4 ms per vblank**; windowed `--renderer native`
  **17.4 → 7.3 ms per vblank, 37.7 → 15.3 ms per game frame (p50), 58.0 → 23.0 ms (p99)**. What is left on the EE
  thread is the game's own code (the `ee` zone) plus ~2–4 ms per vblank of VIF1 decoding / payload copies (track D
  is cutting the copies through `unpack_reserve` / `mpg_reserve`, §2) and GIF PATH2/3 walking.
* **Workers** (obs, same runs): VU1 worker 6.4–7.4 ms, GS worker 4.6–6.7 ms of CPU per vblank in battle. Since round 3
  of the AOT, no stage is far above the others: the EE thread (game code) is now the longest one.
* **Against 15 ms per game frame (p99):** not there yet on this machine under load — EE-thread CPU per battle frame is
  15.3 ms p50 / 23.0 ms p99 (windowed native), field 16.8 / 24.5, title 5.1 / 9.3. With the pipeline the frame time
  is the slowest stage (plus the CSR tail, §3); the EE thread's game code is now that stage, outside this track.

## 1. Where the time was (obs, gate build, battle route, d3d11 exact, `--zones`)
| ms / vblank | title 1100–1600 | field 3500–4600 | battle 4600–6150 |
|---|---|---|---|
| ee (game code) | 1.9 | 6.1 | 4.2 |
| vif1 | 0.5 | — | 5.1 |
| vu1 | 0.7 | 38.3 | 26.7 |
| gif | 0.8 | — | 2.2 |
| gs_raster (= op recording with d3d11) | 0.2 | — | 3.5 |
| gs_upload | 8.0 | — | 0.2 |
| total | 13.0 | 62.7 | 42.2 |

(The first, unpaired baseline run; field VU1 is high because the gate build compiles only `g3_skin` and
`g3_generic` ahead of time and the Thebel field also runs `g3_skin` 063.)

## 2. Design

```
EE thread ──commands──▶ VU1 worker ──GS commands + PATH1 packets──▶ GS worker ──op list at each vblank──▶ render thread
```

* **Command stream** (`gs_pipe.h`, `gs_pipeline.cpp`): 16-byte headers + payloads in 32 KiB batches; the EE hands a
  batch over when it is full, at every sync point and at every vblank marker. Commands: `Unpack` (the VIFcode and the
  VIF registers it reads, plus the data words; the EE keeps mode-2 ROW updates itself), `Mpg`, `VuRun` (op, imm,
  TOP, ITOP, `queued`), `VuReset` (CTC2 FBRST), the PATH2/PATH3 GsCore calls (`GsTag`, `GsReg`, `GsPacked`,
  `GsImage`), `P1Flush` / `P1Clear` (the GIF's PATH1 queue), `GsFn` (a closure for the GS stage: the vblank
  op-list hand-off, the native renderer's GS work). The VU1 worker forwards GS commands and its PATH1 packets (`P1Packet`) to the GS worker in order.
* **Bounded queues** with back pressure: at most 1024 batches in flight (≈ 32 MiB) before the EE waits. Workers spin
  ~20 µs before sleeping on a condition variable.
* **PATH1 and the GIF.** In the synchronous model a VU1 kick feeds the GIF at once when it is idle and queues
  otherwise; the queue runs at the next PATH2/PATH3 packet boundary. PATH1 never changes the GIF's arbitration state
  (a PATH1 packet is always closed after its kick), so the EE-side GIF keeps arbitrating PATH2/PATH3 alone: a run
  made while it is busy is flagged `queued` (its kicks wait on the VU1 worker) and the point where `run_path1_queue`
  would run them becomes a `P1Flush` command. 0 such runs on the routes (obs).
* **Zero-copy payloads.** `unpack_reserve` / `mpg_reserve` queue the command with room for the payload and return
  where VIF1 writes the words (track D memcpys DMA runs straight there); `reserve_done` may hand the batch over.
* **The native renderer** (track E, doc 31): its `IVuRunHook` (`Vif1::set_run_hook`) is consulted by the VU1 worker
  before each run, with the run's inputs (`gif_busy` = the run was `queued`); its GS-side work (PRIM write, recorder
  call) comes back as a closure through `GsPipeline::emit_gs` and runs on the GS worker at that point of the stream.
  The native diff / verify modes tee VU1 kicks on the EE side and keep the pipeline off.
* **The vblank op-list hand-off** (`GameHost::end_vblank_slice(submit)`, `GsPipeline::call_on_gs`) is a `GsFn`
  command queued at the end of every vblank slice: the GS worker takes the op list when it reaches it and calls the
  host's submit closure with the display registers the EE captured, so every op list holds exactly what it held
  without threads. The closure carries what the host decided at the vblank (track F's `PresentPlan`: present now /
  at a time / skip; `submit_qpc` is stamped when the GS worker actually submits).

## 3. Sync rules (what the EE can observe of the workers, and the wait there)

| Observation | Rule | Why it is enough |
|---|---|---|
| GS CSR / SIGLBLID read; CSR / IMR / SIGLBLID write | wait for the VU1 worker (`sync_vu`), apply the SIGNAL / FINISH / LABEL writes its PATH1 packets made visible, in order | only A+D writes in PATH1 packets reach SIGNAL / FINISH / LABEL; the VU1 worker scans every packet when it becomes visible (direct kick or `P1Flush`) |
| PATH2 / PATH3 SIGNAL / FINISH / LABEL write | `sync_vu`, then applied by the EE at its place in the stream | keeps the order against pending PATH1 events |
| a VU1 run while IMR lets SIGNAL or FINISH interrupt | `sync_vu` after the run | the interrupt is raised where the synchronous model raises it (the game masks all: `GsPutIMR(0xFF00)`) |
| GIF_STAT while a run kicked into the PATH1 queue | `sync_vu`, P1Q from the worker's queue | |
| GIF TAG0–3 / CNT | drain, the newer of the EE's PATH2/3 tag and the GS worker's PATH1 tag | |
| local → host data (VIF1 FIFO / channel 1 with BUSDIR), CSR.RESET | drain, then the EE thread does the access on the GsCore | |
| VU1 traps (fail closed) | reported at the next `sync_vu` (the next vblank at the latest) | |
| host: snapshots, machine states, CRTC compose, op hand-off outside a vblank, stop | drain | |

Never waited for: VIF1 registers, stalls, interrupts, FLUSHA, MSKPATH3 windows, DMAC completion timing (EE side,
PATH2/PATH3 arbitration only), VPU_STAT (reads 0), the GS worker for CSR (it cannot change CSR).

**How often the EE waits** (obs, battle route with 2 workers): 9,009 CSR reads in 6,150 vblanks (the VBLANK_START
handlers `kwlnVsyncFieldGate` and `_rwDMAVSYNCHandler` read FIELD), 5,204 of them found the VU1 worker behind
(116 s of waiting in a 172 s run under load); 1 IMR write, 1 CSR.RESET, 0 GIF_STAT-with-queue, 0 TAG reads, 0 local
→ host reads, 0 PATH1 events. Dorm 7,143 CSR reads (4,704 waits), fusion 9,238 (5,784), shop 5,936 (3,585), M1 388.

**Where the wait comes from** (obs, `--zones-every 1`, battle 5000–5024, synchronous): the game does a whole frame
— game code and every DMA kick — in the vblank interval that starts at the odd VBLANK_START; the even interval is
idle (0.0 ms). The CSR read at the end of the busy interval therefore needs that frame's VU1 work done: with the exact
rule the VU1 work of a frame must fit in what is left of one busy interval after the EE's own work.

**`--gs-speculate` (opt-in, not exact by default):** CSR reads do not wait; the run stops (fail closed) the first time
the VU1 worker meets a PATH1 SIGNAL / FINISH / LABEL write (none on any route). Measured: no gain while the VU1
worker is the bottleneck (battle 42.5 vs 43.0 ms per vblank, paired; the waits move to back pressure). It matters
once VU1 is faster than the frame, so it stays as an option.

## 4. Threads, profiling

The zone profiler is per thread now (`prof::cur()`, `g_prof_threads`): the EE thread's zones as before plus
`gs_wait` (waiting for a worker), and per worker `w0_*` / `w1_*` columns (vif1, vu1, gif, gs_raster, gs_upload,
gs_submit, gs_wait, busy) and the CPU time of the three threads (`cpu_ee`, `cpu_w0`, `cpu_w1`, from
`QueryThreadCycleTime`: CPU time, not wall time, so they hold under load). The run summary prints every sync point's
count, waits and wait time (`p3fes: gs-threads: sync …`).

## 5. Determinism

* **Unit test** `tests/gs/test_gs_pipeline.cpp` (p3fes_gs_tests): one scripted stream — MPG + UNPACK + MSCAL drawing
  through PATH1 (double-buffered), PATH2 DIRECT, PATH3, a run whose kick queues behind an open PATH3 packet
  (GIF_STAT.P1Q, then the flush), SIGNAL / FINISH / LABEL written by PATH1 and by PATH3, CSR / SIGLBLID / GIF_STAT /
  GIF TAG reads, IMR unmasking SIGNAL (INTC 0 raised at the run), a local → host read, a VU1 reset, a VU1 trap —
  synchronous vs inline vs one worker vs two workers (4 repetitions each); every value the EE read, the interrupt
  log, the traps, GS memory, VU1 data memory and registers must be identical. Plus: a PATH1 SIGNAL visible exactly
  at the next CSR read, and a VU1 run hook drawing through `emit_gs` (the native renderer's shape) at its place in the
  stream. Both compilers.
* **Game stretch test** `p3fes_gs_threads_route` (ctest, needs the ELF and disc, skips without): the M1 route
  (boot → title, software GS) with `--gs-threads off`, `2`, `0`, `2`, `0`; eeMemory.bin, gsMemory.bin, frame.png
  byte-identical across all five.
* **Routes** (obs, d3d11 exact, compared with the zero-replacement references: frame.png SHA-256, eeMemory.bin via
  tracediff --dead-stack, gsMemory.bin SHA-256): every run below was identical.

| Route | threaded runs (all byte-identical) |
|---|---|
| dorm 4900 | 2 workers ×4 (incl. three gates), 1 worker ×1, inline ×1, windowed d3d11 ×1 (eeMemory) |
| M1 sky:11 | 2 workers ×5 (incl. gates, software and d3d11), inline ×2 (ctest) |
| battle 6150 | 2 workers ×8 (incl. gates; `--gs-speculate` ×1), windowed `--renderer native` ×3 (eeMemory 0 bytes; GPU pictures at 5800 and 6150 equal to `--gs-threads off`) |
| fusion 6300 | 2 workers ×3 |
| shop 4100 | 2 workers ×3 |
| climb 39820 | 2 workers ×2 (gates: 15.9 M VU1 runs, 0 PATH1 events, 0 queued runs) |

## 6. Measurements

**Where the EE waited** (obs, battle route, 2 workers): with the gate's two AOT programs 5,204 of 9,009 CSR reads
waited (116 s in a 172 s run); with full AOT round 3 5,925 waited but only **4.3 s in total (0.7 ms per vblank)**.
Back pressure (the EE > 1024 batches ahead of the GS worker) happens only in the title's backdrop uploads (3–18
times per route).

**Paired runs** (same binary, `--gs-threads off` and `2` started together; ms per vblank; CPU columns from
`QueryThreadCycleTime`):

| run | segment | wall off → t2 | EE CPU off → t2 | VU1 worker CPU | GS worker CPU |
|---|---|---|---|---|---|
| headless, 2 AOT programs (main 4709fee) | battle | 48.4 → 29.7 | 40.1 → 6.4 | 27.1 | 5.4 |
| | field (3500–4600) | 47.6 → 40.9 | 43.6 → 7.4 | 30.6 | 8.6 |
| | title | 24.0 → 10.0 | 12.3 → 2.6 | 1.0 | 8.3 |
| headless, full AOT round 3 (11712ad) | battle | (load 1.00) | 21.2 → 7.4 | 7.4 | 6.7 |
| windowed `--renderer native` (11712ad) | battle | 36.2 → 16.4 | 17.4 → 7.3 | 6.4 | 4.6 |
| | field | 38.8 → 17.5 | 19.3 → 7.7 | 6.3 | 5.8 |

Per game frame (FILE.frames.tsv, windowed native, EE-thread CPU per frame): battle p50 37.7 → 15.3 ms, p99 58.0 → 23.0;
field 42.7 → 16.8, 64.7 → 24.5; title 31.8 → 5.1, 48.3 → 9.3. Wall-time frame percentiles from the same runs are
dominated by the machine's load (p99 of 190–2,300 ms in both modes) and are not reported as results.

**`--gs-speculate`** (opt-in): no gain while one worker dominated (battle 43.0 vs 42.5 ms per vblank, paired, 2 AOT
programs). It lets the VU1 stage of frame N overlap the EE's game code of frame N+1 (the game does a whole frame in
one vblank interval, §3), which matters exactly when the stages are balanced, as they are since AOT round 3; it
stays opt-in because it is fail-closed rather than exact by construction.

## 7. Next steps

* **The EE thread is the longest stage now.** Graphics left on it: VIF1 decode + payload copies (track D:
  memcpy runs straight into the batch via `unpack_reserve` / `mpg_reserve`), the GIF's PATH2/3 walk, hand-offs
  (~30 batches per vblank; `--gs-batch-kb` tunes). The rest is the game's code (ee zone), outside graphics.
* **The CSR tail.** The game's vblank handlers read CSR at the end of the interval that did the frame's work, so
  in exact mode the VU1 work of a frame must finish by then: frame ≈ EE + max(0, VU1 − EE work after the frame's
  first kick). Exact ways to remove it: (a) parallel VU1 runs (below); (b) a proof that the pending runs cannot
  write SIGNAL / FINISH: only PACKED A+D descriptors in a PATH1 packet can, so a per-program certificate from the
  AOT compiler (track A) that the kicked tags' REGS come from input data the EE side can check would make the CSR
  read exact without waiting. `--gs-speculate` measures the upper bound meanwhile.
* **Parallel VU1 runs.** MSCALs of one frame are independent when their VU1 memory/register footprints do not
  overlap (RenderWare's double-buffered input/output), but proving it needs each program's live-in registers and
  data-memory read/write ranges as functions of TOP/ITOP — knowledge the AOT generator has (track A). With that, the
  VU1 stage can fan runs out to N workers on copy-on-write VU1 memory and merge in order; until then runs stay in
  order on one worker (the AOT runtime's diagnostic globals `g_aot_slow_ops` / `g_aot_cur_va` also assume one
  executing thread).
* **High-frame-rate mode (track H).** The GS worker hands op lists to the render thread at vblank markers and never
  waits for presents; the render thread may present more often than the game produces frames (interpolated
  in-between frames) without anything in the pipeline changing.

## 8. Reproduce

```
:: exactness: any route, compare with --gs-threads off (or the gate references)
build\<tree>\bin\p3fes.exe --headless --quiet --gs-backend d3d11 --gs-exact --gs-threads 2 ^
    --memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt --snapshot-at vblank:6150 out_t2
:: measurement (quiet machine: close other builds and games first), paired off / 2, per-thread CPU columns
build\<tree>\bin\p3fes.exe --quiet --gs-backend d3d11 --unpaced --renderer native --gs-threads 2 --zones z_t2.tsv ^
    --memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt --frames 6151
build\<tree>\bin\p3fes.exe <same> --gs-threads off --zones z_off.tsv
:: frame-time percentiles: z_*.tsv.frames.tsv (one row per game frame), or T0's tools\ours\perf\bench.py
```
The run prints every sync point (`p3fes: gs-threads: sync csr-read N times, waited M times, S s`) and the workers'
CPU time; `--zones` rows carry `w0_*` / `w1_*` (VU1 worker / GS worker zones) and `cpu_w0` / `cpu_w1`.
