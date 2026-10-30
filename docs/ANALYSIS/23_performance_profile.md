# 23 — Performance profile of the battle route: where the host time goes, and what buys 1.0x

_Phase 6 prerequisite (the user's goal: at least 100 % speed on the recorded battle route before decompilation
continues, then a DirectX 11 renderer). Every number below comes from a run made for this document on 2026-10-20
(the run logs and TSV files are listed in §9). Tags: **obs** = printed by a run, **der** = arithmetic on obs numbers,
**inf** = inferred (a design statement, not measured)._

_Superseded for current numbers by §10 "Re-measure 2026-10-25" (all six routes, windowed D3D11 + full VU1 AOT, the harness `tools/ours/perf/bench.py`, the 15 ms target)._

## 0. Headline

* **The battle route runs at 0.14–0.16x real time** (obs: 103–117 ms of host time per vblank against a 16.68 ms
  budget), the field around it at 0.14–0.15x. Reaching 1.0x needs **6.2x** on the battle segment (der).
* **Two subsystems are 94 % of it** (obs, battle segment, four runs under different loads):
  **GS rasterisation 53–56 %** and the **VU1 interpreter 37–41 %**. Everything else together is 6 %: VIF1 2.4 %,
  recompiled EE code + rt adapter **2.0 %**, GIF 1.0 %, kernel + fibers + hardware registers/DMAC 0.1 %,
  IOP + R3000 + audio + CDVD 0.1 %. The independent IP sampler (`--profile`) gives the same split
  (raster 55.0 %, VU1 39.5 %, VIF1 2.2 %, EE + adapter 1.2 %).
* **The EE side is not the problem.** Recompiled code, adapter, kernel, scheduler and fiber switches together cost
  2.2 ms per vblank in battle (der); making them free would buy 1.02x.
* **The GS is a pure sink on this route** (obs): 0 SIGNAL / FINISH / LABEL events, 0 local→host transfers,
  0 local→local copies in 6,800 vblanks. Nothing the rasteriser writes is ever read back by guest code, so
  rasterisation can leave the guest thread (GPU or worker thread) without any guest-visible synchronisation.
* **Ranked levers** (§8, der): (1) GS rasterisation off the CPU thread — 0.16x → 0.36x alone; (2) VU1 ≥ 3.8x faster
  on the battle (≥ 5.2x if the D3D11 backend costs 3 ms/vblank of CPU; ≥ 6.3x for the Thebel 2F field) — together
  with (1) that is 1.0x, and a 10x VU1 gives ~1.7x (battle) / ~1.2x (field); (3) VU1 on its own host thread lowers
  the VU1 requirement to ≥ 2.6x (battle) / ≥ 3.4x (field); (4) EE/adapter/scheduler: ≤ 2 %.

## 1. Method

### 1.1 Tools

| Tool | What it measures | Where |
|---|---|---|
| `p3fes --zones FILE [--zones-every N]` (new) | Host wall time per subsystem, measured at the subsystems' entry points with the TSC (invariant TSC on this CPU, 3,792,881,182 ticks/s calibrated against QPC); workload counters; one TSV row per N vblanks | `runtime/include/p3fes/prof.h`, `runtime/app/host_zones.{h,cpp}`, BUILDING.md "Profiling" |
| `tools/ours/perf/zones_report.py` (new) | Folds the rows into named vblank ranges: speed, zone shares, workload per vblank and per flip, raster time by primitive type, VU1 programs | this document's tables |
| `p3fes --profile FILE --profile-from N` (existing) | IP samples of the host thread from a second thread (SuspendThread + GetThreadContext), symbolised with the PDB | `runtime/app/host_profile.h` |
| WPR / WPA | **not usable here**: `wpr -start CPU` fails with `0xc5585011` ("Failed to enable the policy to profile system performance") because the session is not elevated; WPA and xperf are installed (`C:\Program Files (x86)\Windows Kits\10\Windows Performance Toolkit`). The in-process sampler is the external cross-check instead. | — |

**Zones** (`prof::Zone`): `ee` (recompiled EE code and `game/`, with the adapter's inline paths), `kernel` (syscalls,
check-point slow path, interrupt dispatch, scheduler), `fiber` (SwitchToFiber), `hw_dmac` (hardware-register
accesses from guest code via the rt slow path, the DMAC chain walk), `vif1` (VIF1 decode, UNPACK, MPG), `vu1` (VU1
interpreter), `gif` (GIF tag walk + GS register file), `gs_raster` (`GsCore::draw_queue`), `gs_upload` (image
transfers, CLUT loads), `gs_crtc` / `present` (windowed only), `ipu`, `iop` (SIF, RPC servers, IOP kernel HLE, R3000
host calls), `iop_cpu` (R3000 interpreter), `audio` (SPU2 voices, ADXI PSM mix, mixer passes), `cdvd` (disc sector
reads), `host`. Nested entries restore the outer zone, so a VU1 run inside a VIF1 transfer inside a DMA kick is
charged to `vu1` and its XGKICK's GIF/raster work to `gif`/`gs_raster` (the VU1 per-program times exclude it). The
zone total equals the wall time of the run (obs: 103.33 ms/vblank both ways in §3).

### 1.2 Build, machine, route

* Tree `build/prof` (MSVC 14.44 Release, `/O2 /Ob2 /DNDEBUG /Zi /FS`, `/DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF`,
  `-DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt`), emitted with `--replace game\replaced.txt` from `47da0fd`
  (501 replaced functions). Optimisation flags are the Release preset's; `/Zi` + `/DEBUG` only add the PDB.
* AMD Ryzen 7 5800X (8 cores / 16 threads, 3.8 GHz base), Windows 10 19045, power plan High performance. **The
  machine is shared with three other agents**; their builds and game runs change the wall time of a run by up to 2x
  (§2.2). Zone *shares* are stable across loads (§3); absolute times are given for the least loaded runs.
* Route: `--memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt --headless
  --quiet --frames 6800` with the main tree's ELF and ISO. Every run ends at cycle 33,456,783,360 with 3,183 flips
  (obs, 9 runs).

### 1.3 Segments of the route (obs: `--snapshot-at` frames every few hundred vblanks, the host's movie-flag marker)

| Range (vblanks) | What is on screen | Evidence |
|---|---|---|
| 0–1100 | boot, logos, opening movie (skipped by START at 1055) | movie flag 5127 set 1004, cleared 1064 |
| 1100–1600 | title "PRESS ANY BUTTON" (1150), Continue, the DATA load screen (1500), fade-in (1580) | frames |
| 1600–2250 | Tartarus entrance lobby, "1F, Entrance" (1800) | frame |
| 2250–2650 | "TARTARUS block 1" floor selection | frame 2400 |
| 2650–2750, 3850–3960 | black floor transitions | frames 2680, 3880, 3960 |
| 2750–3850 | Thebel 1F: Yukari's line (3000), Mitsuru on the radio (3500) | frames |
| 3960–4614 | Thebel 2F exploration (4200); the hero strikes a shadow (4600) | frames |
| **4614–6150** | **battle**: command menu (5000), Agi cast (5100, 5650), the WEAK hit (5800), "A complete victory" (6000) | movie flag 5127 set at 4614, cleared at 6258 (the battle sequence uses the same flag) |
| 6150–6300 | RESULT screen (6150), fade to field (6280) | frames |
| 6300–6800 | Thebel 2F again (6500) | frame |

The brief's rough ranges ("field ~3500–5300, battle ~5300–6100") straddle the battle start: the battle begins at
vblank 4614. Both are reported; the recommendation uses 4600–6150.

### 1.4 Cost of the profiler and determinism

| Run pair (run concurrently, same load) | Wall s | Difference |
|---|---|---|
| zone build, `--zones` on vs off (5 processes on the host) | 586.1 vs 587.9 | −0.3 % (noise) |
| zone build `--zones` off vs baseline `47da0fd` (same flags, 7+ processes) | 636.0 vs 646.7 | −1.7 % (noise) |
| baseline alone-ish, earlier | 619.5 | — |

**Off**, every entry point is one load of `g_prof.on` and one predictable branch (inf: ~85 M entries × ~1 ns ≈ 0.1 s
per run, below the ±5 % run-to-run noise above). **On**, 84.8 M zone entries per run (obs, the TSV header) × 2 TSC
reads ≈ 1.7 s of a 586 s run, 0.3 % (der). No measurable difference either way (obs).

**Guest state is untouched** (obs, MSVC `build/prof`): dorm replay `--snapshot-at vblank:4900` frame `EE0EB5DA…`
and `tracediff … --dead-stack` **differing bytes: 0**, with and without `--zones`; M1 `--snapshot-at sky:11` frame
`E3A93615…`, **0 bytes**, with and without `--zones`. All battle-route runs end at the same cycle and flip count.
ctest 16/16 on MSVC Release (`build/prof`) and clang-cl 22.1 Debug (`build/prof-clang`); the one "Skipped" suite is
`p3fes_recomp_emit_subset`, which looks for the ELF inside the worktree.

## 2. Speed per segment

### 2.1 The two least loaded runs (`--zones`, 50-vblank segments; v1 = 5 processes on the host, v4 = none of the
other agents' game runs, builds possible)

| Segment | vblanks | v1 wall s | v1 x real time | v4 wall s | v4 x real time | best ms / vblank |
|---|---|---|---|---|---|---|
| boot → title (0–1100) | 1100 | 12.04 | **1.53** | 19.63 | 0.94 | 10.9 |
| title → load (1100–1600) | 500 | 43.01 | 0.19 | 58.70 | 0.14 | 86.0 |
| field: lobby (1600–2250) | 650 | 74.61 | 0.15 | 79.55 | 0.14 | 114.8 |
| floor menu (2250–2650) | 400 | 32.52 | 0.21 | 54.66 | 0.12 | 81.3 |
| field: Thebel 1F (2750–3850) | 1100 | 106.31 | 0.17 | 182.41 | 0.10 | 96.6 |
| **field: Thebel 2F (3950–4600)** | 650 | 74.99 | **0.145** | 75.65 | 0.143 | 115.4 |
| **battle (4600–6150)** | 1550 | 180.82 | 0.143 | 160.17 | **0.161** | 103.3 |
| results (6150–6300) | 150 | 2.13 | 1.17 | 1.80 | **1.39** | 12.0 |
| field after (6300–6800) | 500 | 55.17 | 0.151 | 56.09 | 0.149 | 110.4 |
| brief's "field" (3500–5300) | 1800 | 198.32 | 0.151 | 202.89 | 0.148 | 110.2 |
| brief's "battle" (5300–6100) | 800 | 92.05 | 0.145 | 81.85 | 0.163 | 102.3 |
| whole route (0–6800) | 6800 | 586.14 | 0.194 | 697.64 | 0.163 | — |

(obs; "best" = the lower of the two.) The battle segment needs 103.3 / 16.68 = **6.2x** (der). The only segments
at or above real time are the boot/logo phase and the RESULT screen (2D, < 200 primitives per flip).

### 2.2 Load sensitivity

The same binary and route took 586 s (v1), 698 s (v4), 893 s (v2, 2-vblank segments, 7+ other game processes) and
1,150 s (v3, heavy load) (obs). The battle segment ranged 103–220 ms/vblank; its zone shares stayed within
raster 53–56 % / VU1 37–41 % (obs, v1–v4). Speed claims for this phase should be measured on an otherwise idle
machine.

## 3. Subsystem breakdown (ms per vblank, share of the segment)

| Zone | battle 4600–6150, v4 | battle, v1 | field Thebel 2F 3950–4600, v4 | field, v1 |
|---|---|---|---|---|
| gs_raster | **56.31 (54.5 %)** | 64.39 (55.2 %) | **57.51 (49.4 %)** | 57.56 (49.9 %) |
| vu1 | **41.14 (39.8 %)** | 45.69 (39.2 %) | **50.14 (43.1 %)** | 49.10 (42.6 %) |
| vif1 | 2.51 (2.4 %) | 2.84 (2.4 %) | 3.49 (3.0 %) | 3.39 (2.9 %) |
| ee (recompiled code + adapter) | 2.08 (2.0 %) | 2.29 (2.0 %) | 2.93 (2.5 %) | 3.06 (2.7 %) |
| gif | 1.02 (1.0 %) | 1.13 (1.0 %) | 1.99 (1.7 %) | 1.92 (1.7 %) |
| hw_dmac | 0.08 | 0.09 | 0.13 | 0.13 |
| gs_upload | 0.06 | 0.07 | 0.08 | 0.08 |
| iop_cpu (R3000) | 0.05 | 0.06 | 0.04 | 0.04 |
| audio | 0.04 | 0.04 | 0.03 | 0.03 |
| kernel | 0.03 | 0.03 | 0.04 | 0.04 |
| iop (HLE) | 0.02 | 0.02 | 0.02 | 0.02 |
| fiber, ipu, cdvd, host | < 0.01 | < 0.01 | < 0.01 | < 0.01 |
| **total = wall** | **103.33** | 116.66 | **116.39** | 115.37 |

(obs.) Over the whole route (v4): raster 58.0 %, VU1 34.7 %, EE 2.7 %, VIF1 2.3 %, GIF 1.7 %, upload 0.4 %;
the title phase is 95 % raster (its known twelve-layer backdrop, `runtime/gs/README.md` "Performance"). For
comparison, the dorm route (`to_dorm.txt`, 0–4900, under load): raster 80.3 %, VU1 13.5 %; its opening event
(4000–4900) is already battle-like: raster 44.5 %, VU1 47.3 %.

**Cross-check with the IP sampler** (obs: `--profile` from vblank 4650 to 6150, 17,068 samples; the 1 ms request is
quantised by the system timer: 17,068 samples over the ~300 s window, one per ~17.8 ms): functions grouped by subsystem —
raster 54.96 %, VU1 (interpreter + `fpu.h` datapath) 39.51 %, VIF1 2.20 %, EE + adapter 1.22 %, GIF/GS registers
0.63 %, kernel/HLE 0.15 %, IOP/audio 0.02 %, CRT/heap/census strings ~1.3 %. Zones and samples agree within 2 points.

### 3.1 Top 20 functions of the battle segment (sampler, obs)

| # | % | Function | Subsystem |
|---|---|---|---|
| 1 | 18.68 | `gs::detail::Raster::triangle<StaticSampler<0x13 PSMT8, bilinear>>` | raster |
| 2 | 17.90 | `Raster::triangle<StaticSampler<0x14 PSMT4, bilinear>>` | raster |
| 3 | 11.45 | `vu1::compute_upper` | VU1 |
| 4 | 10.53 | `vu1::VU1Interpreter::step` | VU1 |
| 5 | 9.05 | `Raster::triangle<NoSampler>` (untextured) | raster |
| 6 | 5.67 | `Raster::sprite<NoSampler>` | raster |
| 7 | 3.62 | `vu1::set_flags` | VU1 |
| 8 | 3.22 | `VU1Interpreter::lower` | VU1 |
| 9 | 3.01 | `ee::fpu::add` (VU1's exact float datapath) | VU1 |
| 10 | 2.41 | `ee::fpu::mul` | VU1 |
| 11 | 1.32 | `gs::detail::init_tex` (per-primitive texture context) | raster |
| 12 | 1.29 | `Raster::triangle<StaticSampler<0x00 PSMCT32, bilinear>>` | raster |
| 13 | 1.23 | `gs::Vif1::exec_unpack` | VIF1 |
| 14 | 1.17 | `vu1::describe` (per executed upper op) | VU1 |
| 15 | 1.09 | `vu1::in_census` (per executed pair, trap check) | VU1 |
| 16 | 1.02 | `VU1Interpreter::sync_caches` (full re-decode after an MPG) | VU1 |
| 17 | 0.55 | `VU1Interpreter::run` | VU1 |
| 18 | 0.48 | `gs::Vif1::run_words` | VIF1 |
| 19 | 0.39 | `std::vector<u32>::push_back` (VIF1 word buffer) | VIF1 |
| 20 | 0.36 | `gs::GsCore::vertex` | GIF |

The first recompiled guest function, `fn_sub_3197C0_003197c0`, is at 0.08 %.

## 4. GS rasterisation by primitive type (v4 battle and field, per vblank; obs)

| Type | battle ms (share) | battle px / prim | battle ns / px | battle µs / prim | field ms (share) | field px / prim | field ns / px |
|---|---|---|---|---|---|---|---|
| triangle strip | **31.11 (55.3 %)** | 93 | 47 | 4.40 | 18.16 (31.6 %) | 28 | 67 |
| triangle fan | 13.87 (24.6 %) | 4,030 | 25 | 101 | **26.51 (46.1 %)** | 4,197 | 40 |
| sprite | 6.05 (10.7 %) | 14,332 | 11 | 152 | 7.67 (13.3 %) | 13,094 | 13 |
| triangle | 5.28 (9.4 %) | 1,394 | 43 | 60 | 5.17 (9.0 %) | 6,657 | 48 |

(obs; whole segment 29.6 ns per written pixel in battle, 35.2 in the field.) The battle's ~14,300 strip triangles
per flip (the skinned characters) are small and setup-bound: 4.4 µs ≈ 16,700 cycles per 93-pixel triangle (der).
The 80 sprites per flip write exactly 1,146,880 pixels = 4 × 640 × 448 (obs/der): four full-screen passes per frame,
cheap per pixel (11 ns). The fans are large screen-space layers (~4,000 px each).

## 5. VU1 by program (battle 4600–6150, v4; obs)

| Program (`symbols/p3fes.sym`) | runs | pairs | vu1 ms | share of vu1 time | ns / pair |
|---|---|---|---|---|---|
| `vu1_prog_064_g3_skin` `0x6F8B10` | 342,933 | 870.1 M | 44,486 | **69.8 %** | 51.1 |
| `vu1_prog_042_g3_generic` `0x6B8D40` | 137,281 | 271.5 M | 13,209 | **20.7 %** | 48.7 |
| `vu1_prog_061_g3_matfx` `0x6EF130` | 13,347 | 43.5 M | 2,238 | 3.5 % | 51.4 |
| `vu1_prog_101_g3_skin_matfx` `0x7634A0` | 12,415 | 27.5 M | 1,546 | 2.4 % | 56.2 |
| `vu1_prog_093_g3_matfx` `0x74B110` | 2,980 | 17.9 M | 925 | 1.5 % | 51.8 |
| `vu1_prog_046_g3_generic` `0x6C2940` | 8,863 | 13.0 M | 691 | 1.1 % | 53.3 |
| `vu1_prog_039_unknown_tbl4` `0x5CD980` | 139,616 | 8.3 M | 378 | 0.6 % | 45.8 |
| `vu1_prog_033/035_ptank_spr3d`, `089_rt2d_fill`, `063_g3_skin`, 3 more | 3,474 | 3.8 M | 293 | 0.5 % | 52–137 |

14 programs ran in the battle, 11 in the Thebel 2F field (`064` 45.5 %, `063_g3_skin` 27.6 %, `042` 21.4 % of the
pairs there). Every run was attributed (`vu1_unattributed` = 0 over the route). **Two programs carry 90 % of the
battle's VU1 time** (der) — the per-family HLE plan in `runtime/include/p3fes/vu1/README.md` gets most of its value
from `g3_skin` + `g3_generic` alone. Average cost: **50.8 ns ≈ 193 cycles per pair** in battle (der, 41.14 ms /
810,021 pairs per vblank).

Sampler detail of that cost (obs, % of battle samples): `compute_upper` 11.45 + `step` 10.53 + `set_flags` 3.62 +
`lower` 3.22 + `fpu::add/mul` 5.42 (exact datapath) + per-pair `describe`/`in_census` checks 2.26 + decode-cache
refills after MPG uploads (`sync_caches` 1.02, `decode_pair`/`decode_lower` 0.45, `q_read_kind` 0.09,
`MicroMemory::write` 0.09) 1.65. The game re-uploads its programs constantly (66,045 MPG pairs per flip, obs §6),
and each upload invalidates the whole 2,048-pair decode cache (`sync_caches` keys on `MicroMemory::generation()`).

## 6. Workload of one frame (2-vblank rows of run v2; counts do not depend on load)

| Counter | battle frame (vblank 5800, the WEAK hit) | field frame (vblank 4200, Thebel 2F) | battle average per flip (4614–6150) |
|---|---|---|---|
| GS primitives | 16,119: 664 tri, 14,957 strip, 418 fan, 80 sprite | 20,961: 8 tri, 20,503 strip, 358 fan, 92 sprite | 14,851 |
| pixels written | 4,921,162 (strip 1.45 M, fan 2.14 M, sprite 1.15 M, tri 0.19 M) | 3,548,239 (strip 0.72 M, fan 1.41 M, sprite 1.20 M, tri 0.23 M) | 3,844,509 |
| textured pixels (bilinear) | 2,467,540 (2,467,540) | 1,995,352 (1,991,487) | 1,905,075 (1,893,050) |
| raster ms (v2, loaded) | strip 143.1, fan 121.4, sprite 26.8, tri 10.2 | strip 62.6, fan 76.4, sprite 23.1, tri 14.0 | — |
| texture upload | 0 qwords; 247 CLUT loads | 0 qwords; 263 CLUT loads | 904 qwords (14.5 KB); 174 CLUT loads |
| GS register writes | 91,106 | 109,562 | 78,001 |
| GIF qwords PATH1 / 2 / 3 | 88,689 / 3,682 / 0 | 104,628 / 7,735 / 0 | 75,762 / 3,118 / 1,069 |
| VU1 runs / pairs | 1,068 / 1,870,367 | 1,033 / 1,783,453 | 863 / 1,639,864 |
| VU1 XGKICKs / MPG pairs | 977 / 73,113 | 1,045 / 64,471 | 832 / 66,045 |
| VU1 programs (runs, pairs) | `064` 495 / 1.28 M, `042` 222 / 423 k, `061` 19 / 61 k, `046` 45 / 41 k, `093` 4 / 24 k, `039` 256 / 16 k, `033` 18 / 13 k, `101` 5 / 11 k, `035` 4 / 3 k | `064` 298 / 764 k, `063` 295 / 511 k, `042` 210 / 406 k, `101` 15 / 34 k, `097` 13 / 26 k, `102` 15 / 24 k, `039` 179 / 13 k, `041` 8 / 6 k | — |
| R3000 instructions | 21,867 | 7,922 | 16,078 |

(obs.) A 640×448 frame is 286,720 pixels: the battle frame writes **17 layers** of it (der), half of them textured,
all of those bilinear. 110–116 VU1 pairs feed each primitive (der).

## 7. What threading can do while staying deterministic

* **GS raster and uploads** — obs: SIGNAL/FINISH/LABEL 0, local→host 0, local→local 0 over the whole route, so the
  GS core's output (local memory) is read only by the host's CRTC compose and snapshots. inf: a worker thread (or the
  GPU) that consumes the GS register/IMAGE stream in order produces the same memory; the guest thread never waits,
  except at compose/snapshot (drain the queue). CSR, IMR, DISPFB and the flip counter live in `GsPrivRegs`, not in the
  rasteriser, and stay on the guest thread. If a later scene uses FINISH/SIGNAL or local→host transfers, the
  `gs_events` / `image_qw_out` columns of `--zones` show it; those writes are parsed by the GIF (guest thread), so
  they can still be answered synchronously there.
* **VU1** — inf (from `vif1.cpp`/`gs_system.h`): the VU1's only outputs are XGKICK packets into PATH1; guest code
  cannot read VU1 memory (not in the rt adapter's hardware windows); TOP/ITOP/DBF are VIF bookkeeping computed before
  the run. In this synchronous model a PATH1 packet never holds the GIF past its own kick, so the guest-visible GIF
  state (ownership, PATH3 masking, FLUSHA) depends only on PATH2/PATH3 parsing. A pipeline "guest thread: EE + VIF1
  decode + a PATH2/3 arbiter → VU1 thread (UNPACK/MPG writes, runs, kicks, in stream order) → GS consumer" is
  deterministic; it needs the UNPACK/MPG data copied into the queue (2.5 ms/vblank of VIF1 time today stays on the
  guest thread).
* **Raster in bands** — inf: splitting the screen into N horizontal bands, each thread drawing every primitive in
  submission order inside its band, is output-identical per pixel; a primitive that samples a texture written by an
  earlier primitive of the same frame (post-processing passes; the 80 full-screen sprites are candidates) needs a
  barrier across bands.
* **IOP/audio** — 0.1 ms/vblank: nothing to gain.

## 8. Ranked recommendation (battle 4600–6150, v4 = 103.33 ms/vblank; target 16.68)

| # | Change | Battle ms / vblank after | x real time | Speed-up | Basis |
|---|---|---|---|---|---|
| 1 | **GS rasterisation + uploads on the GPU (D3D11)**, CPU cost of submission taken as 0 | 103.33 − 56.37 = **46.96** | 0.36 | 2.2x | der |
| 1b | same, CPU rasteriser on one worker thread | max(46.96, 56.37) = 56.37 | 0.30 | 1.8x | der/inf |
| 1c | same, worker with 4 raster bands | max(46.96, ≈ 14.1) = 46.96 | 0.36 | 2.2x | der/inf |
| 2 | **VU1 10x faster** (JIT, or HLE of `g3_skin` + `g3_generic` = 90 % of VU1 time), CPU raster unchanged | 103.33 − 37.03 = 66.30 | 0.25 | 1.6x | der |
| 2b | VU1 decode cache that survives re-uploads (key on program content, not generation) + hoist `describe`/`in_census` into decode | ≈ 103.33 − 4.0 | 0.168 | 1.04x | der (samples: 1.65 % + 2.26 % of battle time) |
| **1 + 2** | GPU raster + VU1 10x | 46.96 − 37.03 = **9.93** | **1.68** | 10.4x | der |
| 1 + 2, break-even | GPU raster + VU1 sped up just enough | VU1 ≤ 16.68 − 5.82 = 10.86 ms | 1.0 | VU1 ≥ **3.8x** (≥ 5.2x if the D3D11 path costs 3 ms of CPU per vblank, inf) | der |
| 3 | GPU raster + **VU1 + GIF on their own thread** (pipeline of §7) | max(4.80, 42.16) = 42.16 | 0.40 | 2.5x | der/inf |
| 3, break-even | as 3, VU1 sped up | VU1 ≤ 16.68 − 1.02 = 15.66 ms | 1.0 | VU1 ≥ **2.6x** | der |
| 4 | EE code + adapter + kernel + fibers + DMAC made free | 103.33 − 2.19 = 101.14 | 0.165 | 1.02x | der |
| 5 | IOP + R3000 + audio + CDVD made free | 103.33 − 0.11 | 0.161 | 1.00x | der |

Reading: **neither the GPU renderer nor a faster VU1 reaches 1.0x alone**; the GPU renderer is the larger single
step (it also covers the title phase, 95 % raster) and the VU1 work decides whether the combination clears 1.0x.
The field segment has the same structure (Thebel 2F v4: raster + upload 57.59, VU1 50.14, rest 8.66 ms; GPU raster +
VU1 10x → 8.66 + 5.01 = 13.67 ms → 1.22x, der), with more VU1 weight, so the VU1 target should be set on the field,
not only the battle: break-even there is VU1 ≥ 50.14 / (16.68 − 8.66) = **6.3x** without a VU1 thread (der), ≥ 3.4x
with one (50.14 / (16.68 − 1.99), der).

Cheap side levers seen on the way (each ≤ 1 %, obs from samples): the GS state-register census observer
(`GameHost::observe_gs_reg` building `std::string` map keys per state write: `wcstol`, `std::_Tree`, `fmt`,
`basic_string` ≈ 0.4 %), the VIF1 word buffer `std::vector<u32>::push_back` 0.39 %.

## 9. Reproduce

```powershell
build\prof\bin\p3fes.exe --headless --quiet --memcard extracted\_ours\cards\tartarus.ps2 `
  --replay-input config\inputs\to_battle.txt --frames 6800 --zones extracted\_ours\zones_battle.tsv
python -I tools\ours\perf\zones_report.py extracted\_ours\zones_battle.tsv --seg boot=0:1100 --seg title=1100:1600 `
  --seg field2F=3950:4600 --seg battle=4600:6150 --seg results=6150:6300 --seg field_after=6300:6800 `
  --vu1 battle --vu1 field2F
# hot functions (needs the PDB of a /Zi tree):
build\prof\bin\p3fes.exe <same route> --frames 6150 --profile extracted\_ours\prof_battle.txt --profile-from 4650
```

`--zones-every 2` gives one row per frame (§6). Runs used here (TSV + logs kept in the session scratchpad, not in
the repo): v1 `--zones` 586.1 s and its `--zones`-off twin 587.9 s; v2 `--zones-every 2` 893.2 s; v3 1,149.7 s;
v4 697.6 s; baseline `47da0fd` 619.5 s and 646.7 s, zone build off 636.0 s; sampler 4650–6150; the dorm and M1
gates with and without `--zones`; the 24-frame snapshot run of §1.3.

## 10. Re-measure 2026-10-25: all six routes, windowed D3D11 + VU1 AOT, against 15 ms per game frame

_Measured on main `3f4d39f` (the T0 harness `4465367`, VU1 AOT round 3b, native renderer stage 1, frame telemetry) +
this section's zone fixes. Same tags as
above (obs / der / inf). Everything in §1–§9 predates the D3D11 renderer (`9773972`), VU1 AOT (`6cd7a73`, round 2 in
`b9719d5`) and the ~9,500 replaced functions; this section replaces their numbers. The target changed twice on
2026-10-25: first 30 fps "at all times" (33.4 ms of host time per game frame), then **at most 15 ms of host time
per game frame at the 99th percentile in every scene** (so the host can show 60 fps and more; game logic stays at
30 fps, track H interpolates the in-between frames)._

### 10.1 The harness: `tools/ours/perf/bench.py`

```powershell
python -I tools\ours\perf\bench.py run --exe build\<tree>\bin\p3fes.exe --out <dir> `
    [--routes dorm,m1,battle,fusion,shop,climb] [--modes windowed,headless,software] [--repeat 2] [--jobs 1]
python -I tools\ours\perf\bench.py report <dir> [--timeline] [--vu1] [--tasks] [--json F] [--csv F] [--budget 15]
python -I tools\ours\perf\bench.py compare <dirA|A.json> <dirB|B.json>
```

* **Runs.** The gate's six routes (cards, input logs, end vblanks as in `tools/ours/gate/gate.ps1`; m1 with a fresh
  in-memory card instead of the user's own save, which the gate's m1 opens in place), each process in its own
  working directory (private copy-on-write cards), one at a time by default. Modes: `windowed` = what the player runs
  (window, D3D11 GS with interpolated attributes, `--unpaced` so it runs as fast as it can, `--quiet`, a kill timeout
  of 15× the route's real-time length + 120 s); `headless` = the gates' fast mode (`--gs-backend d3d11 --gs-exact`);
  `software` = the oracle. Every run gets `--vu1 aot` and `--zones … --zones-every 10`. `run.json` records the
  command line, exit code, wall time and the machine load during each run (busy share sampled by a thread of bench.py) and before / after it (the build / game
  processes of other agents); a run whose D3D11 device did not come up (software fallback) is flagged and skipped.
* **What `--zones` now records** (`runtime/app/host_zones.{h,cpp}`, `game_host.cpp`): besides the zone wall times
  and workload counters of §1.1, every row (10 vblanks) has the game thread's CPU time (`QueryThreadCycleTime`, at the
  TSC rate) and the process's (`QueryProcessCycleTime`; "other threads" = the difference: render thread, driver,
  audio), the D3D11 renderer's counters (lists submitted /
  appended / executed, presents, render-thread busy time and CPU cycles, the game thread's waits on the render thread,
  **GPU time from timestamp queries** around
  each executed list, read back a few lists later without waiting, only with `--zones`), whether a Sofdec movie is
  playing (the player pointer `0x7CDF10`) and the names of the guest's running kwln tasks (list head `0x7CE07C`,
  read-only). `FILE.frames.tsv` has one row per game frame (flip): wall, game-thread CPU and zone times. Guest state
  is untouched: the six gate routes stay byte-identical with these hooks in the build (§10.7).
* **Segments** come from the running task names, first match wins: `result` (battle_result), `battle` ("battle",
  "battle_*"), `movie` (the player pointer), `load` (NOW_LOADING), `menu` (fclShop*, fclCombine* / fclCmbEff*,
  mcProc, y_StratumParts_proc = the floor select, y_lmap* = the town map, Camp* / cmp*, M_Name*), `event` (the event
  viewer "(ZikkiPlayMode)EventVie", event_Draw_3D, or a script task eNNN_*), `tartarus` (automatic_dungeon_),
  `field` (field_root), `title` (op / op_draw), `boot` (anything else). `report --tasks` prints a run's task sets.
  (The movie flag 5127 is no use: the battle and the shop / fusion menus set it too; H_SfdPlay stays running after a
  movie.)
* **Columns** (per game frame = 2 vblanks): x real time on the wall clock and **as if the game thread had a core to
  itself** (its CPU time); the game thread's CPU ms; graphics on the game thread (VU1 + VIF1 + GIF + GS front end +
  uploads + CRTC + submit) and its parts; game code (EE + kernel + IOP + audio + …); render-thread CPU; GPU ms; other
  threads' CPU; the game thread's CPU ms per frame at p50 / p95 / p99 / max, the share of frames over the budget and
  **PASS / FAIL of the p99 against 15 ms**; the frame rate the host could reach uncapped (1000 / mean and 1000 / p99
  CPU ms); graphics p99; wall-clock p99; machine busy. Zone times are wall times, so on a loaded machine they include
  preemption: the CPU columns scale each row's zones by that row's CPU / wall ratio (an approximation: it assumes
  preemption hits every subsystem alike). JSON and CSV carry every number, including the raw wall-time zones.
  Per-thread zone columns ("thread.zone", once track C's graphics thread lands) are summed per thread.
* **The IP sampler** (`--profile`) now unwinds up to 7 callers per sample from the x64 unwind tables while the
  thread is suspended and adds an inclusive table and the callers of the 30 hottest functions to its report. A
  relink with `/DEBUG /OPT:REF /OPT:ICF` (public symbols, no recompilation) is enough. Caveat: static functions
  have no public symbol and show under the nearest public one; in particular the VU1 AOT block functions appear as
  `vu1::aot::vmul_avx2` (the AVX2 kernel itself is off by default).

### 10.2 Machine and load

AMD Ryzen 7 5800X, 32 GB, RTX 3060, Windows 10 19045. **The machine was saturated for the whole session**: 90–100 %
CPU busy (all 16 logical CPUs) from about ten other agents' builds, ctest runs and replay gates, several of them
D3D11 exact-mode gates on the same GPU. Consequences, measured here:

* Wall-clock speed varies 2–6× between runs of the same binary (dorm windowed 81.8 s in one run, 631 s killed in
  the next; battle headless 267–482 s).
* Even the game thread's CPU time is inflated, by SMT: a thread sharing a core with another busy thread runs slower
  per cycle. Expect quiet-machine CPU times ~1.3–1.7× lower than the tables (inf: typical SMT throughput sharing; not
  measurable here).
* GPU timestamps include time the GPU spent on other processes' work between our two timestamps; under this load
  GPU ms per frame tracks the wall time and is **not usable** (on a quiet machine it measures our lists).
* **A measurement artefact of the first version of this harness, fixed:** the zone recorder called `GetSystemTimes`
  at every row (10 vblanks) for the machine's busy share. On this host the call took from ~1 ms up to **4.6 s**
  (obs: 5 calls averaged 4,605 ms in a Python loop at 100 % load; `QueryProcessCycleTime` 2.3 µs,
  `QueryThreadCycleTime` 1.2 µs), and the wait was charged to the zone current at VBLANK_START — the kernel's (the
  host service runs inside the kernel's check-point). That was the "game thread blocked in the kernel zone, wall ≫
  CPU" pattern of the first baseline runs (kernel up to 29 % of wall on the battle route) and the 2.5–15 %
  `ZwQuerySystemInformation` track B's sampler saw. The recorder no longer samples the machine; `bench.py` does, from
  a thread of its own process. All numbers in §10.3 onward were measured after the fix.
* Two sampler runs that looked like 76–88 % `NtWriteFile` were the end-of-run flip dump (2,860 lines through the
  unbuffered windowed stdout on a saturated disk) inside the sampling window, not the frame loop; the harness passes
  `--quiet`. A guest log write does block the game thread when the output handle is slow (stderr is unbuffered).
* Overhead of `--zones` itself: two TSC reads per zone switch (`prof::switch_to`, 1–5 % of samples in light
  scenes: ~85 M switches on the battle route), a row mark per 10 vblanks (~5 µs: two cycle-count queries, the
  renderer's stats under its lock, the task-list walk) and a frame record per flip (~1.5 µs). The profiler's own
  cost is part of the game-thread CPU in the tables (~1–5 %, most in light scenes, where many short zones run).
* Waits of the game thread on the D3D11 render thread (start-up: device and shaders; readbacks; stop) are now
  counted (`Stats::host_wait_ms`, column "render wait"). Headless exact menus showed 23 % of samples in that
  condition variable for track B; in these runs it is the renderer's start-up and the final stop (a few seconds per
  run), spread over short routes.

So: read the CPU columns and the per-frame CPU percentiles, compare runs only with `compare` and the busy column, and
re-measure the final numbers on a quiet machine (§10.8).

### 10.3 Baseline: windowed D3D11, all six routes (main `3f4d39f`: full VU1 AOT round 3b)

`bench.py run --modes windowed,headless --repeat 1 --jobs 2` with the build of `3f4d39f` + the fixes of this section
(MSVC Release, `P3FES_VU1_AOT` with all 114 programs, round 3b's AVX2 build). Per **game frame** (2 vblanks); CPU =
the game thread's CPU time; gfx and its parts are CPU-scaled zone times (§10.1); "fps" = 1000 / mean CPU ms (the frame
rate the host could reach uncapped on this loaded machine). The machine was 100 % busy throughout (obs): divide by
~1.3–1.7 for a quiet machine (inf), and re-run §10.8 there before quoting absolute numbers.

| route | segment | vblanks | x real wall | x real CPU | game CPU ms | gfx | VU1 | VIF1 | GIF | GS fe | upload | game code | render thr CPU | p50 | p95 | p99 | max | 15 ms | fps |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| dorm | boot | 570 | 1.83 | 4.23 | 7.9 | 0.3 | 0.0 | 0.0 | 0.0 | 0.0 | 0.2 | 7.3 | 1.6 | 1.4 | 35.6 | 40.0 | 71 | FAIL | 217 |
| dorm | title | 1,330 | 0.81 | 1.64 | 20.4 | 16.5 | 0.3 | 0.4 | 0.4 | 0.4 | 15.0 | 3.3 | 1.9 | 22.3 | 38.5 | 41.6 | 61 | FAIL | 48 |
| dorm | movie | 100 | 0.63 | 1.18 | 28.4 | 5.6 | 0.0 | 0.0 | 0.1 | 1.8 | 3.6 | 22.2 | 1.7 | 29.5 | 37.4 | 46.8 | 47 | FAIL | 37 |
| dorm | load | 110 | 1.20 | 2.79 | 12.0 | 6.4 | 1.3 | 1.3 | 0.5 | 1.6 | 1.7 | 4.7 | 2.3 | 2.4 | 48.6 | 55.5 | 76 | FAIL | 89 |
| dorm | menu | 530 | 3.60 | 9.81 | 3.4 | 0.8 | 0.0 | 0.4 | 0.1 | 0.2 | 0.0 | 2.4 | 0.4 | 3.6 | 5.2 | 6.2 | 8 | PASS | 295 |
| dorm | event | 2,260 | 0.98 | 2.90 | 11.5 | 8.1 | 1.6 | 1.7 | 0.6 | 1.7 | 2.5 | 3.2 | 1.0 | 2.3 | 51.2 | 55.4 | 62 | FAIL | 87 |
| dorm | **whole** | 4,900 | 1.05 | 2.57 | 13.0 | 8.6 | 0.8 | 0.9 | 0.4 | 1.0 | 5.3 | 4.0 | 1.3 | 3.0 | 48.7 | 55.1 | 76 | FAIL | 75 |
| m1 | boot | 400 | 1.40 | 3.38 | 9.9 | 0.1 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 9.4 | 2.2 | 1.7 | 10.3 | 70.6 | 71 | FAIL | 164 |
| m1 | **whole** | 400 | 1.40 | 3.38 | 9.9 | 0.1 | 0.0 | 0.0 | 0.0 | 0.0 | 0.0 | 9.4 | 2.2 | 1.7 | 10.3 | 70.6 | 71 | FAIL | 171 |
| battle | boot | 530 | 1.79 | 3.82 | 8.7 | 0.7 | 0.1 | 0.1 | 0.1 | 0.2 | 0.1 | 7.7 | 1.6 | 1.4 | 34.4 | 40.3 | 67 | FAIL | 182 |
| battle | title | 830 | 2.00 | 3.50 | 9.5 | 7.1 | 0.0 | 0.2 | 0.1 | 0.1 | 6.7 | 2.2 | 0.9 | 0.7 | 31.4 | 35.2 | 53 | FAIL | 104 |
| battle | movie | 40 | 0.72 | 1.20 | 27.9 | 5.8 | 0.0 | 0.0 | 0.1 | 1.0 | 4.6 | 21.9 | 1.7 | 29.8 | 33.9 | 34.6 | 35 | FAIL | 36 |
| battle | load | 380 | 1.25 | 1.94 | 17.2 | 11.4 | 2.4 | 2.5 | 1.0 | 4.6 | 0.8 | 5.6 | 1.4 | 5.2 | 50.6 | 53.5 | 95 | FAIL | 60 |
| battle | menu | 530 | 0.97 | 1.42 | 23.5 | 15.9 | 2.2 | 3.1 | 1.1 | 3.3 | 6.0 | 7.4 | 1.3 | 23.6 | 32.2 | 36.8 | 39 | FAIL | 42 |
| battle | field | 40 | 1.11 | 1.43 | 23.3 | 16.1 | 4.4 | 5.0 | 1.8 | 4.6 | 0.3 | 7.1 | 1.5 | 20.8 | 34.3 | 36.7 | 37 | FAIL | 43 |
| battle | tartarus | 1,160 | 0.48 | 0.73 | 45.9 | 34.3 | 6.8 | 8.6 | 2.5 | 15.7 | 0.5 | 11.3 | 2.9 | 49.4 | 56.0 | 61.1 | 69 | FAIL | 22 |
| battle | event | 1,090 | 0.80 | 0.97 | 34.3 | 22.3 | 5.3 | 5.8 | 1.7 | 6.6 | 2.6 | 11.9 | 2.2 | 33.5 | 43.1 | 45.2 | 48 | FAIL | 29 |
| battle | battle | 1,290 | 0.30 | 0.79 | 42.4 | 30.0 | 7.9 | 9.1 | 2.1 | 10.3 | 0.5 | 11.8 | 3.4 | 45.6 | 58.7 | 63.8 | 72 | FAIL | 24 |
| battle | result | 260 | 0.49 | 1.61 | 20.7 | 13.3 | 3.1 | 5.1 | 1.3 | 3.4 | 0.2 | 7.3 | 1.3 | 18.3 | 39.9 | 41.0 | 44 | FAIL | 48 |
| battle | **whole** | 6,150 | 0.60 | 1.11 | 30.0 | 20.5 | 4.4 | 5.3 | 1.5 | 7.1 | 2.2 | 9.2 | 2.2 | 33.4 | 54.3 | 61.0 | 95 | FAIL | 32 |
| fusion | boot | 530 | 1.37 | 3.65 | 9.1 | 1.2 | 0.1 | 0.2 | 0.0 | 0.5 | 0.2 | 7.7 | 2.0 | 1.4 | 42.6 | 45.4 | 87 | FAIL | 147 |
| fusion | title | 860 | 1.18 | 2.44 | 13.7 | 10.7 | 0.1 | 0.2 | 0.2 | 0.3 | 9.8 | 2.5 | 1.5 | 1.2 | 37.8 | 40.8 | 61 | FAIL | 72 |
| fusion | movie | 20 | 0.81 | 1.45 | 23.1 | 2.5 | 0.0 | 0.0 | 0.1 | 0.4 | 2.0 | 20.5 | 2.7 | 25.6 | 35.0 | 35.0 | 35 | FAIL | 50 |
| fusion | load | 190 | 0.23 | 1.24 | 26.9 | 20.6 | 6.2 | 4.4 | 1.7 | 8.0 | 0.2 | 6.1 | 3.0 | 35.8 | 50.6 | 54.4 | 55 | FAIL | 38 |
| fusion | menu | 4,150 | 0.48 | 1.91 | 17.5 | 11.4 | 1.8 | 2.3 | 0.7 | 2.3 | 4.2 | 5.8 | 1.2 | 9.1 | 44.7 | 49.0 | 63 | FAIL | 57 |
| fusion | field | 350 | 0.17 | 0.68 | 49.0 | 37.1 | 8.7 | 7.9 | 3.3 | 13.0 | 4.1 | 11.6 | 3.9 | 49.1 | 58.8 | 61.2 | 62 | FAIL | 20 |
| fusion | tartarus | 200 | 0.16 | 0.81 | 41.1 | 31.0 | 8.2 | 6.9 | 2.2 | 13.3 | 0.4 | 9.6 | 3.0 | 44.8 | 49.9 | 53.2 | 56 | FAIL | 24 |
| fusion | **whole** | 6,300 | 0.45 | 1.75 | 19.1 | 12.7 | 2.1 | 2.3 | 0.8 | 3.0 | 4.4 | 6.0 | 1.6 | 10.4 | 48.7 | 56.2 | 87 | FAIL | 51 |
| shop | boot | 530 | 1.10 | 3.74 | 8.9 | 0.9 | 0.4 | 0.3 | 0.0 | 0.2 | 0.0 | 7.6 | 1.7 | 1.5 | 31.5 | 34.5 | 72 | FAIL | 160 |
| shop | title | 990 | 0.45 | 2.34 | 14.3 | 11.6 | 0.0 | 0.2 | 0.2 | 0.2 | 10.9 | 2.3 | 1.4 | 1.4 | 37.1 | 39.5 | 58 | FAIL | 69 |
| shop | movie | 10 | 0.28 | 1.59 | 20.9 | 1.1 | 0.0 | 0.0 | 0.0 | 0.2 | 0.8 | 19.8 | 3.0 | 25.0 | 33.1 | 33.1 | 33 | FAIL | 51 |
| shop | load | 210 | 0.51 | 1.93 | 17.3 | 10.2 | 2.0 | 3.5 | 0.3 | 3.8 | 0.5 | 7.1 | 1.6 | 10.2 | 41.4 | 45.5 | 51 | FAIL | 61 |
| shop | menu | 1,780 | 0.22 | 0.75 | 44.6 | 37.4 | 4.4 | 6.2 | 2.2 | 17.7 | 6.6 | 6.7 | 4.6 | 44.3 | 66.6 | 69.6 | 86 | FAIL | 22 |
| shop | field | 580 | 0.30 | 1.05 | 31.7 | 21.9 | 5.5 | 5.9 | 1.4 | 7.6 | 1.4 | 9.6 | 2.4 | 32.6 | 39.6 | 42.3 | 48 | FAIL | 31 |
| shop | **whole** | 4,100 | 0.31 | 1.14 | 29.4 | 22.8 | 2.8 | 3.8 | 1.2 | 9.0 | 5.7 | 6.2 | 3.0 | 33.4 | 64.1 | 69.0 | 86 | FAIL | 32 |
| climb | boot | 590 | 1.69 | 3.90 | 8.6 | 1.2 | 0.2 | 0.2 | 0.1 | 0.3 | 0.4 | 7.1 | 1.6 | 1.4 | 52.2 | 56.9 | 70 | FAIL | 151 |
| climb | title | 1,050 | 1.30 | 2.73 | 12.2 | 9.5 | 0.1 | 0.2 | 0.1 | 0.2 | 8.8 | 2.2 | 1.1 | 1.4 | 29.9 | 33.5 | 52 | FAIL | 81 |
| climb | movie | 130 | 0.38 | 1.20 | 27.8 | 5.8 | 0.0 | 0.0 | 0.1 | 0.4 | 3.4 | 21.4 | 1.0 | 28.3 | 32.1 | 32.1 | 34 | FAIL | 37 |
| climb | load | 1,510 | 0.48 | 1.04 | 32.2 | 23.4 | 5.0 | 5.8 | 2.2 | 9.7 | 0.3 | 8.5 | 2.1 | 40.8 | 52.0 | 56.9 | 89 | FAIL | 31 |
| climb | menu | 570 | 0.47 | 1.14 | 29.2 | 20.8 | 2.0 | 3.6 | 1.0 | 4.3 | 9.8 | 7.9 | 2.0 | 29.4 | 40.6 | 45.3 | 49 | FAIL | 34 |
| climb | field | 430 | 0.30 | 0.68 | 49.0 | 38.4 | 7.8 | 7.9 | 2.4 | 10.0 | 9.9 | 10.5 | 3.6 | 53.9 | 62.1 | 65.2 | 67 | FAIL | 20 |
| climb | tartarus | 6,420 | 0.26 | 0.78 | 42.8 | 30.8 | 7.4 | 8.9 | 2.4 | 11.4 | 0.4 | 11.9 | 3.1 | 43.3 | 56.5 | 62.4 | 69 | FAIL | 23 |
| climb | battle | 22,680 | 0.19 | 0.76 | 44.2 | 32.9 | 8.7 | 10.1 | 2.2 | 11.3 | 0.4 | 10.9 | 4.0 | 44.5 | 63.9 | 71.3 | 95 | FAIL | 23 |
| climb | result | 6,440 | 1.06 | 6.45 | 5.2 | 2.2 | 0.4 | 0.9 | 0.2 | 0.6 | 0.1 | 2.7 | 0.5 | 3.4 | 18.3 | 35.1 | 45 | FAIL | 194 |
| climb | **whole** | 39,820 | 0.25 | 0.94 | 35.6 | 26.0 | 6.5 | 7.7 | 1.8 | 8.9 | 0.8 | 9.4 | 3.1 | 40.5 | 61.4 | 68.8 | 95 | FAIL | 28 |

Headless (`--gs-backend d3d11 --gs-exact`, same build, run alongside) gives the same game-thread costs within a few percent (e.g. battle-route Tartarus 47.3 ms / p99 62.6, battle 40.9 / 59.1, climb Tartarus 43.7 / 60.7, shop menu 46.6 / 73.4): the D3D11 back end in either mode is off the game thread. The full headless table and both JSON reports are in the run directory, not in the repo.

Reading it (obs unless marked):

* **No segment meets 15 ms at p99 except the dorm's light menu (6.2 ms).** Heavy 3D — Tartarus floors, battles,
  the field — costs **42–49 ms per frame** of game-thread CPU (p99 61–71 ms); events 34 ms; the shop menu 45 ms;
  title 9–20 ms; movies 21–28 ms; boot, light menus and the result screen 3–9 ms.
* **Graphics is ~70–75 % of a heavy frame** (30–38 ms of 42–49), but no longer mostly VU1. The split of a heavy
  frame: **GS front end 10–16 ms** (`gs_raster` with D3D11 = GsCore register writes, vertex assembly, the op
  recorder), **VIF1 8–10 ms** (UNPACK / MPG), **VU1 7–9 ms** (full AOT), GIF 2–3 ms, uploads ~0.5 ms; game code
  (EE + kernel + IOP + audio) 10–12 ms; the D3D11 render thread 3–4 ms on its own thread.
* The shop menu is GS-front-end bound (17.7 ms) plus uploads (6.6 ms); the title is uploads (7–15 ms: the twelve-layer
  backdrop's page uploads, §3); movies are the IPU's MPEG decode (counted in "game code", 20–22 ms).
* p50 / p95 / p99 are the per-flip CPU times scaled to 2 vblanks; boot and title have a low p50 with a high p95
  (one expensive frame among cheap ones: loading).

### 10.4 Where "graphics takes 43 ms of frame time" came from, and what round 3 changed

The user's 43 ms is the editor profiler's **Graphics** category (`editor/core/profiler.cpp`: vif1 + vu1 + gif +
gs_raster + gs_upload + gs_crtc + gs_submit) for a frame of a heavy scene — the same sum as the gfx column here. On
`4709fee` (the morning's main: VU1 AOT round 2 with **two** compiled programs in the gate build, and a plain
`p3fes.exe` that defaulted to `--vu1 interp`) it was dominated by VU1:

| battle route, windowed, game-thread CPU ms / frame (same harness, same load) | round 2, 2 programs (`4465367`) | round 2, all 114 (gate `-FullAot`) | **round 3b, all 114 (`3f4d39f`)** |
|---|---|---|---|
| Tartarus floor: game CPU / gfx / VU1 | 106.8 / 88.8 / 63.7 | 81.1 / 66.0 / 35.0 | **45.9 / 34.3 / 6.8** |
| battle: game CPU / gfx / VU1 | 83.4 / 67.0 / 47.1 | 80.2 / 63.4 / 37.1 | **42.4 / 30.0 / 7.9** |
| menu (floor select): game CPU / VU1 | 51.3 / 23.5 | 38.2 / 9.9 | **23.5 / 2.2** |
| whole route: game CPU / gfx | 59.6 / 43.6 | 52.5 / 39.9 | **30.0 / 20.5** |

(obs; the first two columns were measured before the `GetSystemTimes` fix of §10.2, which did not touch the CPU
totals but blurred their zone split.) With only two programs compiled, the VU1 programs that ran interpreted —
`vu1_prog_063_g3_skin` (the Tartarus floors' skinning, 37–53 % of the floor's VU1 time), the matfx family `053` /
`061` / `093` / `097`, `101` / `102_g3_skin_matfx`, `046_g3_generic` — cost 100–250 ns per pair against 25–45 ns for
the compiled two (`bench.py report --vu1`), i.e. **~60 % of the floors' VU1 time and ~25 % of the battle's**. A plain
`p3fes.exe` without `--vu1 aot` ran *every* program interpreted (doc 24 §2: ~33 ms per battle vblank). Both are gone
on main: `--vu1 aot` is the default (`4465367`) and all 114 programs are compiled by default (track A, `4109078`).

### 10.5 Hot functions with call stacks (IP sampler, battle 4650–5400, headless exact, round 2 / 2 programs)

Measured before round 3 (so VU1 is over-represented against §10.3), kept for the non-VU1 paths, which round 3 did
not change. Inclusive = on the stack within 8 frames (obs):

| Inclusive | Function (callers) |
|---|---|
| 62 % | VU1 (`VU1Interpreter::aot_run` / `exec_run`): AOT `g3_skin` 37 %, `g3_generic` 10 %, interpreter (programs not compiled) 15 % |
| 13 % | `Gif::feed` (PATH1 95 %) → `GsCore::write_packed` → `vertex` → `draw_queue` → `GsOpRecorder::on_draw` 11 % |
| 7 % | memory copies under the op recorder: `memchr`-attributed 4.3 % (49 % from `on_draw`, 44 % from `vector<GpuVertex>::_Insert_counted_range`) + `memmove` 2.4 % (82 % from the `GpuVertex` insert) |
| 7 % | `Vif1::exec_unpack` (self), plus `vector<u32>::push_back` 2.1 % from `Vif1::run_words` |
| 1.3 % | `gs::detail::decode_draw_state` (from `on_draw`) |
| 0.3 % | the GS census after the fix (`unordered_map` emplace from `observe_gs_reg`) |

The recorder's per-vblank op list regrowth (memmove 3.5 % + `ZwFreeVirtualMemory` 3.3 % in an earlier sample) and
the VIF1 word buffer went to track D (owner of `runtime/gs`). Note on symbols: a `/DEBUG` relink has public symbols
only; the VU1 AOT block functions are static and show under the nearest public symbol, `vu1::aot::vmul_avx2`.

### 10.6 What T0 changed (all exact; gates in §10.7)

| Change | Effect (obs) |
|---|---|
| GS state-register census without per-write strings (`GameHost::observe_gs_reg`: counts per (register, census bits), strings built when read) | GIF zone on the battle 3.4 → 1.4 ms / frame (CPU-scaled), dorm 0.57 → 0.17; dorm `capture.json` byte-identical before / after |
| `--vu1 aot` by default (`4465367`; main kept the equivalent form) | a plain `p3fes.exe` no longer runs every VU1 program interpreted |
| `--zones`: CPU time, renderer counters, GPU timestamps, task names, per-frame file; no `GetSystemTimes` | the harness of §10.1; the recorder's own wait is gone (§10.2) |
| IP sampler with call stacks, inclusive table, callers | §10.5 |
| `Stats::host_wait_ms` (render-thread waits) | "render wait" column |

### 10.7 Gates

`tools\ours\gate\gate.ps1 -Repo <worktree> -Tree build\perf-gate -ClangTree build\perf-clang -Jobs 2 -FastGs`, both
compilers, all suites, six routes: **GATE: PASSED** (main `3f4d39f` + this section's code): ctest MSVC 160/160 and clang-cl 160/160 (`p3fes_game_tests` 1,007 cases, 56.8 M assertions on each compiler); dorm `EE0EB5DA…`, M1 `E3A93615…`, battle `CFAA5A61…`, fusion `9B5B5374…`, shop `1165B3E0…`, climb `F3440652…`, 0 differing bytes, gsMemory identical. The first commit (`4465367`) passed the same gate on `4709fee` except the then-known `field8_sys` case, which failed identically on main's own build.

### 10.8 Re-measuring on a quiet machine (for the user)

Close other heavy programs, then from the repo root:

```powershell
. .\tools\env.ps1
powershell -File tools\ours\gate\gate.ps1 -Tree build\bench -BuildOnly -Jobs 8      # the fast build (full VU1 AOT)
python -I tools\ours\perf\bench.py run --exe build\bench\bin\p3fes.exe --out extracted\_ours\bench_quiet `
    --modes windowed --repeat 2
python -I tools\ours\perf\bench.py report extracted\_ours\bench_quiet --vu1 --json extracted\_ours\bench_quiet\report.json
```

The windowed runs open a window for each route (about 25 minutes in all at ~1× real time; the climb is 11 minutes of
it). On a quiet machine the "on CPU" column should be near 100 % and the wall and CPU x real time should agree; the
GPU column is then meaningful too. `compare` against this section's `report.json` shows the machine difference.

### 10.9 Against 15 ms per frame: what is left (der from §10.3, heavy 3D frame ≈ 45 ms CPU here, ≈ 27–35 ms quiet, inf)

| Lever (owner) | Heavy-frame CPU now | Bound if removed from the game thread |
|---|---|---|
| GS front end: register writes, vertex assembly, the op recorder and its copies (D; E's native renderer bypasses VIF/VU1/GIF for the g3 batches) | 10–16 ms | −10–16 ms |
| VIF1 UNPACK / MPG (D) | 8–10 ms | −8–10 ms |
| VU1 (A; E bypasses it for native batches) | 7–9 ms | −7–9 ms |
| graphics on its own thread (C): moves gfx (30–38 ms) off the game thread; the game thread keeps game code + submit | 30–38 ms | game thread ≈ 11–12 ms ⇒ **under 15 ms only with the graphics thread**; the graphics thread itself then needs gfx ≤ 15 ms (≈ 2–2.5× less than now) |
| game code: EE, kernel, IOP, audio (decomp / not a graphics lever) | 10–12 ms | the floor of the game thread |
| uploads (title), IPU decode (movies) | 7–15 / 20 ms | title and movie frames |

Reading: with everything on one thread, 15 ms needs the heavy frame ~3× cheaper; with C's graphics thread the game
thread is already ≈ 11–12 ms (game code) and the target becomes "graphics ≤ 15 ms on its own thread", which D + E
(front end, VIF1, native g3) and A (VU1) between them have to deliver. Movies (IPU decode ~20 ms) and the title
(uploads) need their own fixes.
