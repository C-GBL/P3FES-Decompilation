# 31 — Frame pacing and hitches: every guest frame on time, once, on a steady cadence

_Graphics team, track F (2026-10-25). The user's order: "a perfect 30 FPS at ALL times", since raised to "each
frame 15 ms at max ... 60 fps ... as HIGH AS POSSIBLE". The other tracks make each frame cheaper. This track makes
every frame arrive on time, decouples the display rate from the game rate (for track H's interpolated frames) and
measures it all. Tags as in `23`: **obs** = printed by a run made for this document, **der** = arithmetic on obs
numbers, **inf** = inferred._

## 0. Headline

* **Every windowed run now measures itself**: per guest frame the host work, the guest thread's CPU time, the zone
  split, the present-to-present interval and, from DXGI frame statistics, how many display refreshes the frame
  stayed on screen. It also lists hitches with a cause, has an F3 overlay showing both rates (game and display) and
  the 15 ms line, and writes a per-frame CSV (`--frame-log`). The summary is printed at exit.
* **The new pacing (`--pacing display`, the default)** presents each guest frame **once**, at a **timed** moment.
  One guest vblank is locked to one display refresh, and the presents are phase-locked to the middle of a refresh
  interval. On frames the host can afford, the cadence is exact:
  * M1 boot route: interval p99 **33.5 ms**, **544 of 546** frames held exactly 2 refreshes (obs, v6).
  * Dorm route's first 4,000 vblanks: p95 58.8 → **33.4 ms**, p99 124.4 → **50.0 ms**, hitches 348 → **29**;
    **1,720 of 1,742** frames held exactly 2 refreshes (obs, v5 A/B).
* **Under load the new loop keeps running; the old one stalls.** On this shared 8-core machine the old loop was
  descheduled in 70–4,785 frames per route. With the guest thread above normal priority, the new loop has 0–10 such
  frames (§5). The old audio back-pressure stalled the guest thread 1.3–15.5 s per route; rate control removes all
  of those stalls.
* **What still makes frames late is host cost, not pacing.** In over-budget frames the dominant zone is VU1 (tracks
  A/B), then GS uploads (scene and floor loads: up to 151 ms in one frame), then IPU movie decoding (M1's FMV: 43 %
  of its frames over 15 ms). Disc reads (`cdvd`) are about 0: synchronous loads are not a hitch source.
* **Display rate decoupled from game rate** (`--display-rate refresh|HZ|uncapped`). The render thread runs its own
  display clock: 60 presents/s at 60 Hz (obs: 1,650 presents, interval p50 16.7 ms, p99 17.1). Uncapped gives
  ~900/s. Guest frames still advance on the 30 fps field gate, and track H's interpolated frames plug in through
  `GsD3D11Renderer::set_display_hook`.
* **Against the 15 ms target** (obs, loaded machine, v5 display runs): host work per frame p50 / p99 by route is
  m1 2.6 / 39.5, dorm 5.0 / 103.5, fusion 13.7 / 136.7, shop 55.2 / 119.5, battle 69.6 / 143.4, climb 103.0 / 149.0 ms.
  The share of frames over 15 ms is 34–82 %. Those are other tracks' costs measured on a busy machine; the
  quiet-machine command is in §6.

## 1. What "30 fps" means here

* The guest is field-gated (`10` §4). `kwlnVsyncFieldGate` lets the RW flip run on odd fields only, so the game
  flips at most once per two VBLANK_STARTs: 29.97 frames/s, a 33.37 ms budget per frame. A frame that takes the game
  itself longer (its own CPU/DMA budget in virtual cycles) flips after 3 or 4 vblanks. That slowdown is the game's
  own, deterministic and the same on every host; the telemetry counts it apart as "guest".
* The host runs the guest in **vblank slices** (`GameHost::run` with `every_vblank`) and hands each slice's GS op
  list to the D3D11 render thread (`25` §11). Before this track the render thread **presented after every list**,
  as soon as the list arrived: 60 presents/s, half of them repeats. The time at which a new picture reached the swap
  chain therefore depended on how the guest's work split between the frame's two slices. The host clock (QPC at
  59.94 Hz) also beat against the display's (60.000 Hz on the user's monitor). Frames were held for 1, 2 or 3
  refreshes in an irregular pattern even when the average was 30 fps.
* "Perfect" therefore has three parts, all measured (§2): (a) one **Present per guest frame**; (b) each frame shown
  for exactly **two refreshes** on a 60 Hz display (DXGI frame statistics); (c) no frame later than its slot, and
  the remaining hitches explained.

## 2. Telemetry (`runtime/app/frame_telemetry.{h,cpp}`, `frame_overlay.{h,cpp}`)

Always on in windowed runs (`--frame-stats off` disables it). Printed at exit as `p3fes: frame-time: ...` lines:

| Measure | Source |
|---|---|
| host **work** per guest frame (wall time of its slices minus the pacing waits) | QPC around each slice |
| guest-thread **CPU** time per frame | `QueryThreadCycleTime`: work much larger than cpu means the thread was descheduled by machine load, not slow |
| **zones** per frame (ee, vu1, vif1, gif, gs_upload, gs_submit, ipu, iop, audio, cdvd, ...) | the zone profiler (`p3fes/prof.h`), turned on without a `--zones` recorder; read through one accessor (`zone_state()`) so a per-thread profiler (track C) is a one-line change |
| **new-frame interval** as displayed (DXGI `SyncQPCTime`) or, failing that, as presented | `gs::PresentRecord` from the render thread |
| **refreshes per frame** on screen | `IDXGISwapChain::GetFrameStatistics` (`SyncRefreshCount` per present; works for the windowed flip-model swap chain, obs) |
| **display rate**: every present's interval, presents in the last second | the same records (decoupled display rates present more often than the game flips) |
| render-side timing of each frame: queue wait, execute + compose, the `Present` call, lateness against its timed target | `PresentRecord` (`submit_qpc`, `dequeue_qpc`, `ready_qpc`, `present_qpc`, `return_qpc`) |
| guest cadence (vblanks per flip), render-queue merges, audio queue / ratio / underruns / back-pressure waits, pacer re-anchors, frames over 15 ms | host counters per frame |

Percentiles p50 / p95 / p99 / max come from a 0.1 ms histogram (`FrameTimeHistogram`). A **hitch** is a new-frame
interval above 34.0 ms. The 20 worst are listed with their frame's work, CPU, top zones and events, and a cause:
* **guest**: the game itself took more than 2 vblanks.
* **pacing**: a re-anchor.
* **load**: work over budget, but the thread was descheduled (work − cpu > 30 % of work and > 5 ms).
* **host**: work over budget; the zones say where.
* **present**: the host was on time, the picture was late on the render side.
* **display**: both were on time (DWM/DXGI, or GPU contention).

`--frame-log FILE` writes one CSV row per guest frame (a 256 KiB buffer, written as frames complete).
`tools/ours/perf/frame_report.py` folds the CSVs into the tables of §5. Its `fit_p99` / `fit_hitch` columns cover only
frames that, like the frame before them, fit the budget: that is what the pacing alone delivers.

`--frame-overlay` (or **F3** at any time) shows a translucent, click-through window over the top-left of the game:
* the game fps and display fps over the last second, and the worst interval;
* frame interval p50/p99 and host work p50/p95 over the last ~5 s;
* hitches, late presents, the audio queue / ratio / underruns, the pacing mode;
* a bar graph of the last 240 frame intervals, with host work as dim bars, against the 33.4 ms, 50 ms and 15 ms lines.

The overlay is GDI in its own layered window, redrawn four times a second, so it costs nothing on the render thread
or in the swap chain.

Cost: a few QPC/TSC reads and one `QueryThreadCycleTime` per slice, `GetFrameStatistics` per present, and the zone
profiler, measured at 0.3 % of wall time in `23` §1.4. It was not measured separately again on this loaded machine.

## 3. The pacing policy (`runtime/app/frame_pacing.{h,cpp}`, main.cpp's windowed loop)

1. **Virtual → wall mapping** `wall(v) = offset + v·scale` (`FramePacer`). Before running the guest past virtual
   time v the host waits until wall(v); it never runs ahead. Up to **two vblanks** of debt (being behind) is caught
   up by later light slices; the two slices of a frame are uneven. A host further behind **re-anchors to exactly
   two vblanks behind**. A slow stretch therefore never idles, and the first version's idling is gone: re-anchoring
   to zero made the next light slice wait a full vblank while the game was already below full speed. A recovery
   catches up at most 33 ms. The old pacer let the debt reach 0.25 s, then re-anchored to zero and ran flat out to
   catch up.
2. **Display lock** (`--pacing display`, the default). DWM's composition timing (`DwmGetCompositionTimingInfo`,
   re-read twice a second) gives the refresh period P. When one guest vblank is within 0.5 % of k refreshes
   (60 / 59.94 Hz: k = 1; 120 Hz: 2; 240 Hz: 4), scale = k·P / (1001/60000 s): the guest runs at the display's rate
   (on a 60.000 Hz monitor that is 100.1 % of NTSC speed) and the frame grid never slips against the refresh grid.
   With no such k (75, 144, 165 Hz) it falls back to `clock` (scale 1, real time). Frames then alternate between
   neighbouring refresh counts, which only a VRR display (G-SYNC / FreeSync in windowed mode) removes.
3. **One Present per guest frame** (`PresentGate`). A slice presents when the guest flipped or the display
   registers changed. While the guest does not flip (static screens, front-buffer drawing), every second vblank
   presents. Other slices are submitted with `PresentPlan::Skip`: executed, not presented.
4. **Timed presents** (`PresentPlan::At`). The frame that flipped in the slice ending at virtual time v is presented
   at **wall(v) + D**. The render thread executes the list and draws the picture into the back buffer at once. It
   presents at that moment (high-resolution timer, the last 0.5 ms spun; obs precision p99 0.5–0.6 ms) and keeps
   executing later lists meanwhile; they change GS memory, never the back buffer.
   * D = one vblank is the minimum: a frame is two slices [a, b], and if a + b ≤ 33.37 ms the flip slice ends no
     later than wall(v) + 16.7 ms whatever the split. `tests/app/test_frame_pacing.cpp` simulates 22,000 random and
     adversarial splits: 0 late, every interval exactly 33.37 ms.
   * D adapts on top of that (`PresentDelayController`): one vblank plus the p90 of the render thread's recent
     submit → picture-ready time, capped at two vblanks. It rises at once and falls after 300 presents. The reason
     is the title's 12-layer backdrop, whose list takes ~11 ms on the render thread (obs). `--present-delay-ms N`
     fixes D.
   * The cost is latency: D is 17–33 ms.
5. **Phase lock**: in display lock each timed present is steered (10 % of the error per frame) to the middle of a
   refresh interval, the point farthest from both vblanks. Half a refresh of timer or DWM jitter then cannot move a
   frame to the neighbouring refresh.
6. **Catch-up**: a list that arrives after its time presents at once (counted as "late"). Presents are never closer
   together than their guest vblanks, minus 0.1 ms (`FramePacer::schedule_present`): while a debt is caught up the
   frames keep their cadence instead of bunching, and drift back onto the timed grid over a few seconds.
7. **Decoupled display rate** (`--display-rate refresh|HZ|uncapped`; `gs_d3d11.h` `DisplayRate`, `PresentPlan::Latch`,
   `DisplayHook`).
   * The host submits each new guest frame as `Latch`, with the same timed due time.
   * The render thread composes it into a 4-slot ring (`Gpu::Latched`) and presents on its own display clock:
     * `refresh`: mid-refresh ticks from DWM's timing, `Present(1)`;
     * `HZ`: that many ticks a second, `Present(0)`;
     * `uncapped`: at most one tick per millisecond.
   * Each tick shows frame A, the newest due at or before the tick. If a `DisplayHook` is installed, it draws the
     picture between A and the next frame B, with alpha = (tick − due_A) / (due_B − due_A). The ring holds B D ahead
     of time: the look-ahead an interpolator needs.
   * In this mode the phase lock puts the due times on the vblanks, half a refresh away from every tick, so no tick
     is ambiguous.
   * The game logic is untouched: guest frames still come at 30 fps from the field gate.
8. **Audio follows video** (`XAudio2Sink` rate control, `runtime/include/p3fes/audio/xaudio2_sink.h`). The video
   clock (QPC or the display) drifts against the audio device's crystal, and the display lock runs the guest 0.1 %
   fast on 60.000 Hz.
   * The sink measures its exact queue (frames handed over − `SamplesPlayed`), smooths it over ~1 s and sets the
     source voice's frequency ratio within ±0.5 % to hold it at 60 ms. It pre-rolls 60 ms of silence when it starts
     or runs dry.
   * The old back-pressure (`Sleep(1)` loops in the guest thread while more than 120 ms was queued, at 15.6 ms
     `Sleep` granularity) remains only as a safety net at 180 ms.
   * obs: legacy runs spent 1.3–15.5 s blocked there per route (§5); display runs 0.
9. **Scheduling**:
   * `timeBeginPeriod(1)` for the process;
   * the guest thread at `THREAD_PRIORITY_ABOVE_NORMAL`;
   * the render thread at `THREAD_PRIORITY_HIGHEST` (its work per frame is short and its presents are timed);
   * `IDXGIDevice1::SetMaximumFrameLatency(2)`;
   * no core affinity (the scheduler does better on a shared 8-core machine than a fixed mask).
10. **`--unpaced`** stays uncapped: no waits, untimed presents, still one per guest frame. **`--pacing legacy`** is
    the loop of before in full (presents after every list, 0.25 s catch-up, back-pressure audio, no timer or
    priority changes), kept for A/B measurements. Headless runs are untouched.

**Determinism.** None of this reaches the guest. The host decides only when the next slice runs and when and what
the render thread presents. The guest sees the same VBLANK_START sequence, and replays are vblank-indexed. The merge
gate (headless, six routes byte-identical) is unaffected by construction and passes (report / commit message).

## 4. Hitches found (obs, the telemetry's causes)

| Source | Finding | Status |
|---|---|---|
| Presenting every vblank, untimed (legacy) | Frames held 1 / 2 / 3 refreshes depending on how the work split; QPC against the display clock | **fixed** (§3.3–3.5) |
| Pacer catch-up | 0.25 s of debt run flat out (fast-forward bursts); after a re-anchor, light slices idled while the game was below full speed | **fixed** (§3.1, §3.6) |
| Audio back-pressure | `Sleep(1)` loops on the guest thread while the queue exceeded 120 ms: 205 waits / 5.9 s on dorm, 190 / 15.5 s on battle (legacy, obs) | **fixed** (rate control, §3.8); display runs 0 |
| Machine load / priorities | legacy frames descheduled (work − cpu > 30 %) in 70 (m1) to 4,785 (climb) frames; display runs 0–10 (obs) | **fixed** (§3.9) |
| Timer resolution | `Sleep` at 15.6 ms granularity (no `timeBeginPeriod`) in the audio waits | **fixed** |
| Render thread, heavy lists | The title's backdrop: ~11 ms execute + compose per frame on the render thread (obs `render_ms`), making the picture ready late | **mitigated** (adaptive D); the cost itself is track D's |
| Render thread blocked by a timed present | the first version waited inside the present and stalled later lists, a feedback loop that pushed D to its cap | **fixed** (draw now, present later) |
| GS uploads on the guest thread | second cause of over-budget frames (dorm 105, shop 98, fusion 61 frames), one-off spikes up to 151 ms (floor and scene loads) | **open**: track D (GS front end) |
| IPU movie decode on the guest thread | M1's FMV: 58 of its 85 over-budget frames dominated by `ipu` (12 ms mean) | **open**: an IPU-on-a-thread or faster MPEG decode track |
| VU1 | dominant zone in 2,091 of 2,116 over-budget battle frames (58.7 ms mean under load) | **open**: tracks A / B |
| Disc / file reads | `cdvd` zone about 0 in every hitch; mods overlay reads go through the same disc source | **not a hitch source** |
| Shader compilation | everything compiles at renderer start (cache: 9 s first run, 0.15 s after), none in play; the first lists queue behind the driver's first use during boot (75 merged lists before the first frame, obs) | **no in-play hitch** |
| "display" hitches | frames presented on time but shown 3 refreshes: on this machine the GPU is shared with other agents' headless d3d11 gates | **inf**: GPU contention; re-measure on a quiet machine |
| Window drag / resize | the Win32 modal loop stops the guest thread; the pacer re-anchors | **known**; would need the guest off the window thread |
| Logging on the hot path | windowed stdout is unbuffered, but nothing prints per frame without `--stats` | **none found** |

## 5. Before / after (obs; windowed, paced, as a player runs it)

Machine: the shared Ryzen 7 5800X / RTX 3060 with about eight agents building and gating, plus this track's own
gate during the v5 campaign. Wall time was very noisy (one legacy battle run took 1,800 s against 270 s for the
display run in the same window).

Load noise is separated three ways:
1. the `load` column: frames whose wall work exceeds the guest thread's own CPU time by > 30 %;
2. `fit_p99` / `fit_hitch`: only frames that, like the frame before them, fit the budget; that is the pacing alone,
   independent of how expensive the scene is;
3. A/B pairs run back to back in random order (`campaign.ps1`).

Same binary (v5), `--pacing legacy` = the old loop, `--pacing display` = the new one. Climb limited to 15,000 vblanks.
"refresh2" = frames shown exactly 2 refreshes / frames with DXGI statistics (legacy presents 60/s, so its statistics
cover only a few frames).

| run | frames | p50 | p95 | p99 | max | hitches | refresh2 | work p50 | work p95 | fit | load | fit p99 | fit hitches |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| m1 legacy | 563 | 33.3 | 58.5 | 80.0 | 6063 | 181 | 260/262 | 2.6 | 57.1 | 402 | 70 | 57.1 | 23 |
| m1 display | 563 | 33.3 | 33.4 | 50.0 | 6083 | **10** | 535/544 | 2.6 | 36.0 | 478 | 2 | **33.5** | 2 |
| dorm legacy | 2243 | 33.3 | 541.0 | 787.5 | 6066 | 674 | 763/786 | 6.0 | 413.4 | 1726 | 427 | 64.0 | 160 |
| dorm display | 2243 | 33.3 | 83.4 | 100.1 | 6050 | **276** | 1923/2189 | 5.0 | 89.5 | 1874 | 0 | **33.4** | 4 |
| shop legacy | 1836 | 70.4 | 142.7 | 514.6 | 8626 | 1277 | 279/285 | 65.7 | 131.0 | 590 | 296 | 57.1 | 40 |
| shop display | 1836 | 50.0 | 116.6 | 133.3 | 6085 | **993** | 796/1777 | 55.3 | 105.8 | 755 | 6 | **33.5** | 1 |
| fusion legacy | 2938 | 33.6 | 143.0 | 177.4 | 6067 | 1359 | 605/617 | 14.4 | 135.4 | 1960 | 240 | 56.9 | 380 |
| fusion display | 2938 | 33.3 | 116.6 | 133.4 | 6083 | **815** | 1863/2667 | 13.7 | 109.0 | 2105 | 10 | **50.0** | 35 |
| battle legacy | 2859 | 612.1 | 1196 | 1409 | 15158 | 2523 | 8/33 | 435.2 | 982.3 | 418 | 2361 | 216.3 | 19 |
| battle display | 2859 | 66.7 | 133.4 | 150.1 | 6083 | **2060** | 757/2802 | 69.6 | 134.5 | 620 | 4 | **33.7** | 3 |
| climb legacy (15k vb) | 7267 | 319.3 | 841.2 | 1028 | 10189 | 6020 | 97/132 | 222.6 | 699.2 | 1324 | 4785 | 169.0 | 62 |
| climb display (15k vb) | 7267 | 100.0 | 133.4 | 150.1 | 9633 | **5150** | 2056/7182 | 103.0 | 137.1 | 1956 | 10 | **33.5** | 7 |

Segments (`--seg`) where the scene fits the budget show the pacing best:
* dorm 0–4000: p95 58.8 → 33.4, p99 124.4 → 50.0, hitches 348 → 29, refresh2 1,720/1,742.
* battle title 1100–1600 (v4 pair): p95 58.1 → 33.4, hitches 105 → 4, refresh2 232/235.
* M1 with the final build (v6, `--display-rate game`): p99 33.5, max 67 apart from boot, 544/546 frames at exactly
  2 refreshes; again on the merged build (v7, during the merge gate): p99 33.6, 554/556.

Over-budget frames (work > 33.4 ms, or > 15 ms for the new target) stay late in both modes: that is scene cost
(§4), and the new loop's job there is not to make it worse. It runs them without idling and presents them once.

**Against 15 ms** (v5 display runs, host work per frame; loaded machine):

| route | work p50 | p95 | p99 | > 15 ms | > 33.4 ms |
|---|---|---|---|---|---|
| m1 | 2.6 | 35.6 | 39.5 | 42.8 % | 15.2 % |
| dorm | 5.0 | 89.4 | 103.5 | 34.0 % | 16.5 % |
| fusion | 13.7 | 108.1 | 136.7 | 46.4 % | 28.3 % |
| shop | 55.2 | 105.6 | 119.5 | 76.1 % | 59.0 % |
| battle | 69.6 | 134.5 | 143.4 | 82.1 % | 78.4 % |
| climb (15k vb) | 103.0 | 136.9 | 149.0 | 77.8 % | 73.1 % |

Decoupled display (v6, m1):
* `refresh`: 1,650 presents, interval p50 16.7 / p99 17.1 ms; game frames 548/561 at 2 refreshes.
* `uncapped`: 28,407 presents in 33 s (~900/s); game-frame p95 35.1 ms.
* `game`: 748 presents, game p99 33.5.
* Caveat: rerun on the merged build while the merge gate's six exact-mode GPU routes shared the RTX 3060 (v7),
  `refresh` held 433 of 533 game frames at 2 refreshes. 91 frames were shown for 3: their latched picture was ready
  after its due time (413 late latches), so they appeared one tick later. Game mode in the same window held 554/556,
  because its delay had grown to the 33.4 ms cap. The decoupled path's quality under GPU contention needs a
  quiet-machine run before it becomes a default.

## 6. Reproduce

Windowed route runs (the A/B scripts are in the track's scratch folder; the commands are those of
`tools/ours/gate/gate.ps1` without `--headless`, plus pacing flags):

```powershell
$M = 'F:\P3FES-PORT\p3fes-port'
build\<tree>\bin\p3fes.exe --elf $M\extracted\disc\SLUS_216.21 --iso $M\input\persona3fes.iso --vu1 aot --quiet `
  --memcard $M\extracted\_ours\cards\tartarus.ps2 --replay-input $M\config\inputs\to_battle.txt --frames 6150 `
  --pacing display --frame-log battle_display.csv          # and --pacing legacy for the old loop; F3 = overlay
python -I tools\ours\perf\frame_report.py battle_legacy.csv battle_display.csv --seg title=1100:1600 --seg battle=4600:6150
```

Other routes: `--memcard new --replay-input to_dorm.txt --frames 4900`; `--frames 1500` (m1);
`fusion.ps2 + fusion.txt --frames 6300`; `shop_buy.ps2 + shop.txt --frames 4100`;
`full_battle.ps2 + full_battle.txt --frames 39820`. Display-rate variants: add `--display-rate refresh|120|uncapped`.
On a quiet machine the `load` column should read 0 in both modes, and the legacy / display difference that remains
is the pacing itself.
