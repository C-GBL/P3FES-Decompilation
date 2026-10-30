# 32 — High frame rate: in-between frames over the 30 fps game, and what true 60 Hz logic would take

_Graphics team, track H (2026-10-25). The user's order: "I want each frame to be 15ms at max, the goal is to be
running at 60fps not 30. We should be getting the frame rate as HIGH AS POSSIBLE." Tags as in `23`/`31`:
**obs** = printed by a run made for this document, **der** = arithmetic on obs numbers, **inf** = inferred,
**code** = read from the decompiled / recompiled program (addresses are VAs). Every run shared the 8-core machine
with ~8 other agents: wall times and fps are 1.5-2.5x an idle machine's; the tables give render-thread CPU and GPU
milliseconds per picture and frame-time percentiles, and §11 has the quiet-machine commands._

## 0. Headline

* **`--fps 60 | 120 | monitor | unlimited`** (windowed play, D3D11, F's pacing) shows **interpolated pictures
  between the game's 30 fps frames**; `--fps 30` (default) is exactly today's behaviour; the game logic, the gates
  and the exact path are untouched (§1, §10.1). Display rates met on every route: 16.7 ms (60), 8.4 ms (120),
  ~1.1 ms (uncapped) p50 between presents (§9.3).
* **How (§3-§7):** every native g3 batch gets an identity (a hash of its input vertex block + N + program) and its
  transform rows; the recorder keeps its converted vertices in the op list's side table; the render thread keeps
  per game frame the GS memory at its start and its lists, and an in-between picture is frame B's lists replayed
  into a scratch GS memory bank with each matched batch's vertices blended in clip space (perspective-correct)
  between frames A and B. 2-D, UI, fallback VU1 batches and transfers are B's, in B's order. Camera cuts and frames
  without native batches show the 30 fps picture.
* **Exactness (§9.1-9.2):** a replayed frame equals the latched exact picture byte for byte on every frame checked;
  guest memory with interpolation on = off = the gate reference (0 bytes).
* **Cost (§9.3):** per in-between picture 2.7-6.7 ms on the render thread and 2.7-9 ms of GPU (one more execution
  of the frame's list); a GPU budget lowers the steps when 120 Hz would cost too much. Latency +~18 ms in the
  default mode, a low-latency mode extrapolates instead.
* **Limit:** the interpolator needs the game to hold real time. On the loaded machine the game ran at 38-44 ms per
  game frame on the heavy routes, so most ticks had no next frame to blend towards (1-10 % in-between instead of
  ~50 % at 60 Hz) — quiet-machine commands in §11.
* **Part 2 (§10):** true 60 Hz logic is feasible only as a months-long rewrite of ~1,000-2,000 per-frame functions
  with no oracle; it breaks replays, the gates and the multiplayer tick. **Recommendation: keep 30 Hz logic +
  interpolated display (this track).**

## 1. The constraint: the game is a 30 fps program

* `kwlnVsyncFieldGate 0x19D320` sits at the head of the INTC-2 chain and stops it on even fields (`10` §3.1,
  `RUNTIME_CONTRACT` Q-01): RenderWare's flip and the ADX vsync server run on odd fields only, so the game flips at
  most once per two VBLANK_STARTs, 29.97 frames/s; one `kwlnUpdate 0x1983A0` = one game frame.
* Everything the game simulates counts those frames (Part 2, §10): the task kernel's start / end delays and per-task
  timers (`kwlnTaskMain 0x1949E0`, task +36/+40/+44/+48), the script VM's `WAIT n` (`scrCommand_WAIT 0x35B030`:
  `scrGetCmdTimer() >= n`, frames), animation (`RtAnimInterpolatorAddAnimTime 0x4B7240` advanced by
  `speed x 1/30 s`, the constant at `0x7CADD4`), movement, fades, camera moves, menus' key repeat, one `RpRandom`
  draw per frame in `kwlnRootUpdateShowRasterTask 0x199140`. Running the loop at 60 Hz plays the game at double
  speed.
* So the logic stays exactly as it is — 30 fps, the gates and the exact path unchanged — and the **display** runs
  faster: the renderer shows pictures **between** game frames N-1 and N, made from the two frames' geometry. This is
  what PC ports of fixed-step console games do (frame interpolation of transforms); the price is up to one game frame
  of display latency (§8).

## 2. The pieces and who owns them

| Piece | Where | Owner |
|---|---|---|
| Native batches: the g3 VU1 programs computed in C++, their triangles straight into the op list | `runtime/native` (`31`) | E |
| The batch identity + transform record of every native batch (`NativeBatchTag`: key, rows 0x3F0-0x3F3, program), computed only while the side table is on | `NativeG3::run` → `GsWork::tag` → `GsOpRecorder::on_native_triangles(…, tag)` | H wrote it (lead's call); E refines the key in place (resEntry address) |
| The op list's **side table** (`OpList::nat_batches / nat_verts / nat_src`, `GsOpRecorder::set_native_side_table`, `note_native_batch`) | `runtime/include/p3fes/gs/gs_ops.h`, `runtime/gs/gs_ops.cpp` | H |
| Display rate decoupled from the game rate: `--display-rate game|refresh|HZ|uncapped`, latched guest frames each due at its time, the render thread's display clock, `DisplayTick {prev, next, alpha}` | `runtime/gs/d3d11/gs_d3d11.cpp`, `runtime/app/frame_pacing.*` (`31_frame_pacing`) | F |
| GS memory banks in the executor (`create_banks / save_bank / copy_bank / swap_bank`) and the interpolator hook (`IFrameInterpolator`: `before_execute / on_reset / draw`) | `gs_d3d11.{h,cpp}` (additive) | H |
| Matching, cut detection, clip-space vertex blending, transform blending | `runtime/hfr/hfr_interp.*` (pure C++, tested in `tests/gs/test_frame_interp.cpp`) | H |
| The render-thread interpolator (per-frame records, replay into a scratch bank, draw) | `runtime/hfr/hfr_d3d11.*` | H |
| Switches `--fps 30|60|120|unlimited|monitor`, `--hfr-latency normal|low` | `runtime/app/main.cpp` (no timing change) | H |

## 3. Which batch is which: RenderWare atomics → VU1 batches → keys

**How a model reaches the VU1 (code, `game/src/render/mesh.cpp`, `render_rw4/5.cpp`, `bridges.cpp`).** RenderWare
renders each *atomic* (one geometry under one frame of a clump: a body part, a weapon, a prop, a map piece) and each
*world sector* through the PS2All pipeline:

1. the object set-up callback (`sub_4A09D0` stock, `sub_46EB90` skinned, `skinSplitObjectSetupCB` partitioned skins)
   runs the **instance test** (`sub_4A0480`: `objIdentifier` = vertex count | flags | morph count; a different one
   re-instances), builds the **camera x object matrix** (the atomic's LTM times the camera's view matrix,
   `cameraBuildPerspViewMatrix 0x4C9270`: the frame's inverse scaled by 1 / view window) and the light list, and
   `openVU1SetupPktNew 0x4EC2B0` UNPACKs the rows to VU1 **0x3F0-0x3F3** (as {x, y, z, z}) and the lights to
   0x3D0..; a skinned atomic also uploads its **bone palette** (`_rpSkinMatrixUpdating 0x46B510`, the whole palette
   as 4 x bones quadwords to VU1 0x2BC; `sub_46B8E0` per mesh for partitioned skins);
2. per mesh the material **bridge** (`RpMeshPS2AllBridgeCallBack`, the MatFX bridges) sends the GIF tag template,
   the material colour, the lighting factors and the clip vectors (0x3FA-0x3FF), and the mesh's instanced vertex
   data — the atomic's **resEntry** in the RW resource arena (`resEntryAllocate 0x4C4930`), built once and reused
   every frame while resident — goes to the VU1 as REF-tagged DMA, cluster by cluster: each cluster is one
   **MSCNT batch** of the g3 program (`31` §2.1).

So one native batch = (atomic or sector, mesh, cluster). Its **input vertex block** (object-space positions, uv,
prelit colour, normals, skin weights) is the same bytes every frame as long as the resEntry is resident; what changes
per frame is the transform record (rows 0x3F0-0x3F3, palette, lights, morph factor).

**The key.** `NativeG3::run` hashes (FNV-1a) the first 8 input vertices of the batch, its last vertex, N and the
program — at most 9 x 5 quadwords per batch, nothing measurable — only while the side table is on; E may later switch
it to the resEntry's DMA address from a new `VuRunInfo` field. Either is opaque here: equal keys = the same geometry
cluster (or an identical copy of it). Consequences, all handled by `match_frames`:

| Case | What happens |
|---|---|
| The same cluster in both frames | matched; blended unless held (§5) |
| Several instances of one cluster (two Shadows of one model, a repeated prop, the party's shared weapon meshes) | the candidates of frame N-1 with that key and the same N are paired greedily with the **nearest origin** (row 3 of the rows = the object's origin in camera space); a pair farther apart than `instance_rel` (0.5) x its distance from the camera is not the same object |
| A cluster appears (spawn, LOD switch, a re-instance after resEntry eviction, a new model) | unmatched: drawn as in frame N |
| A cluster disappears | not drawn (the in-between picture is built from frame N's list) |
| Morph targets / vertex-animated meshes | positions come out of the batch's model, so blending the output vertices blends the morph too |
| Skinned meshes (064 / 063) | the output vertices already contain the skinning, so stage 1 blends skinned positions; stage 2 blends the palette (§4.2) |

The other identities a renderer could use, and why not: a sequence number per frame breaks on any change in draw
order (the RW world-sector order follows the camera); the RW atomic pointer is not visible at the VU1 hook (it would
need the EE-side RW pipeline instrumented, `31` §2.2 chose the VU1 seam); the rows alone change every frame.

## 4. Blending

### 4.1 Stage 1 (today): the native renderer's converted vertices, blended in clip space

For each matched batch the recorder keeps **all N source vertices** as converted `GpuVertex` (window x / y in 12.4,
Z, colour, STQ, fog), including vertices that only belong to culled triangles (a vertex drawn in frame N may have
been culled in N-1), plus the source index of every emitted vertex. The in-between triangle list is frame N's (its
triangles, its culling, its flat/smooth flag), with each vertex replaced by the blend of its two source vertices:

* **Position, perspective-correct.** The g3 transform is c = rows · p (clip), X = off + c.x / c.w (`31` §2.2 step 4).
  If the transform moves linearly between the frames, c moves linearly: c(t) = (1-t) c₀ + t c₁. With w = 1/q (Q is
  in every native vertex's STQ) that gives X(t) = ((1-t) w₀ X₀ + t w₁ X₁) / w(t), w(t) = (1-t) w₀ + t w₁ — the screen
  offset cancels out exactly (the derivation: X(t) - off = ((1-t) w₀ (X₀ - off) + t w₁ (X₁ - off)) / w(t), and the
  `off` terms sum to off · w(t) / w(t)), so no camera constant is needed. A plain screen-space lerp would be wrong
  for anything moving in depth (`test_frame_interp`: "perspective-correct", > 1 pixel off at the midpoint of a vertex
  going from 100 to 400 units).
* **Z.** The programs compute Z = offset.z + scale.z · q (z lanes cleared, `31` §2.2), affine in q: Z is taken at
  the blended q (β = (q(t) - q₀) / (q₁ - q₀), α when q hardly changes).
* **STQ.** s/q and t/q are the vertex's texture coordinates (constant per vertex; frame N's are used, so scrolling
  UVs step at 30 fps), times the blended q.
* **Colour and fog.** Lerped (the lighting moves with the object); flat batches give each triangle its third
  vertex's blended colour, as the GS would.
* **Refusals.** A vertex with q ≤ 0 or a blended w ≤ 0 keeps frame N's values (`blend_vertex` returns false).

Interpolating the converted vertices instead of the transform inputs is exactly a linear blend of the full
(camera x object x bone) matrices, at no model cost (no re-run of the batch). Its one difference from a rigid blend is
**rotation shortening**: a point rotating by θ in one game frame is drawn on the chord, r(1 - cos(θ/2)) short at the
midpoint: 0.4 % of r for 10° per game frame (300°/s), 3.4 % for 30°. For the camera and for bones at 30 fps that is
far below a pixel except for the fastest swings; above `max_turn_rad` (0.8 rad per game frame) the batch is held (§5).

### 4.2 Stage 2 (with E's GPU vertex stage): blended transform records

When E moves the per-vertex work to a compute shader (`31` stage 2), converted vertices no longer exist on the CPU
and the side record becomes {key, input range, output range, transform record}. An in-between picture then re-runs
the batch's compute dispatch with a **blended transform record**: rows by `blend_affine` (polar decomposition
M = R·S, rotation by quaternion slerp, stretch and translation lerped: lengths are kept, no shortening), each bone of
the palette the same way, light colours / directions lerped, the morph factor lerped. `match_frames` (keys, rows,
cuts) is shared by both stages; only the blend step differs (`hfr_interp.h`: `blend_vertices` vs `blend_affine`).

## 5. Holds and camera cuts

Per matched batch, `match_frames` holds it (draws frame N's version) when its origin jumps by more than
`max_jump_rel` (0.6) of its distance from the camera, when its rotation changes by more than `max_turn_rad` (0.8 rad,
46°), or when any vertex moves more than `max_move_px` (160 pixels) on screen. A **cut** is declared for the whole
frame pair — no blending at all, the previous frame stays until the next one is due, i.e. today's 30 fps picture —
when more than `cut_held_share` (40 %) of the matched vertices were held, or fewer than `min_matched_share` (30 %) of
frame N's native vertices found a partner (a scene change), or frame N has no native batch (menus, movies). Camera
cuts in events, battle camera switches, the field ↔ battle transition and loading screens are all of these kinds.

(An alternative is to read the main camera, `g_kwlnMainCamera 0x7CE0C0`, from guest memory at each flip and compare
its view matrices; the statistical test needs no guest structure and also catches cuts made by switching cameras.)

## 6. What is not blended, and how it is composed

The in-between picture is **frame N's op list replayed in its own order** from frame N's starting GS memory, with
only the matched native batches' vertices changed. Hence:

| Draw | In an in-between picture |
|---|---|
| Native g3 batches (`042` generic, `064` / `063` skin) | blended |
| Unmatched / held native batches | frame N's |
| 2-D: sprites (`sprSpriteDrawAll`), Im2D UI, fonts, message windows, the date HUD, menus, `H_Fade_Main`, bust-ups (`DrawBustupProc`) | frame N's — they come after the 3-D passes in the root task's draw order (`10` §3), so they are on top as in the game; their 30 fps animation (scrolling, fades) steps at 30 fps |
| VU1 batches that fall back to the exact program (clipped near-plane batches, a busy GIF, other programs: PTank particles, MatFX env/bump passes, Im3D) | frame N's — **they lead the blended geometry by (1-α) of a game frame**; E's clipper (fewer fallbacks) and the fallback bracket (E: begin / end recorder calls with the same key + rows, so their output can be blended when the topology matches) close this |
| Texture uploads, CLUT loads, render-to-texture (the 063 shadow textures, offscreen effects) | replayed as in frame N; the shadow textures are themselves native 063 batches, so they are blended too |
| Effects that read the previous frame's picture (blur, the battle transition) | read frame N-1's final picture from the bank, as the game did |
| Movies (IPU → GS uploads) | no native batch → a cut: 30 fps (the SFDs are 29.97 fps anyway) |

## 7. The render thread: banks, records, replay

* **Records** (`hfr_d3d11.cpp`). The host submits each slice's list; the one in which a flip happened goes as
  `PresentPlan::Latch` tagged with the new flip count (F). That flip ran at the slice's first check point — the
  kernel takes a stop requested at VBLANK_START before delivering the cause-2 handlers (`bus_timebase.cpp`
  `slow_check`), and RenderWare's DMA queue is stalled on the flip — so the Latch list holds only the **next**
  frame's GS work. `before_execute` therefore closes the open record at a Latch list (it is the frame of
  `plan.tag`, shown by this list's display registers), saves GS memory + the CLUT into the next record's bank
  (`save_bank`, a GPU `CopyResource` of 4 MiB + 1 KiB) and starts the next record with this list. Six records (the
  renderer latches four frames).
* **Replay.** For a tick between A and B with 0 < α < 1: copy B's starting bank into the scratch bank, swap it in as
  the executor's GS memory, execute B's list with the blended vertices, compose with B's display registers, swap the
  real memory back, draw the composed picture into the back buffer. α = 1 draws B's latched picture (exact), α = 0
  lets the renderer draw A. The real GS memory is never touched by a replay: local→host transfers, snapshots and
  the next frame see exactly what the exact path computed.
* **Quantised α.** F places display ticks half a refresh away from due times. When the display rate is an integer
  multiple k of the game rate (60 Hz: k = 2, 120 Hz: k = 4, detected from the tick interval within 4 %), α is rounded
  up to a multiple of 1/k, so the pictures are evenly spaced and every k-th one is the exact game frame
  (`quantise_alpha`); other rates (uncapped, 144 Hz) use the raw α.
* **GPU budget.** With automatic steps, the in-between pictures of one game frame may take at most `gpu_budget`
  (0.5) of the frame in GPU time, from the measured ms per replay (timestamp queries, read a few ticks late, no
  stall): k is lowered to 1 + floor(0.5 · T / gpu_ms) — 120 Hz with 9 ms replays shows in-betweens at 60 Hz spacing,
  uncapped is quantised to what the GPU affords — instead of letting replays delay the real frames' execution.
* **GPU cost.** A replay is one more execution of frame B's list through the GS pixel pipeline: GPU work scales with
  the number of in-between pictures (k-1 per game frame: 1 at 60 Hz, 3 at 120 Hz). §9 has the timestamp-query
  numbers per tick (copy of the 4 MiB bank + execute + CRTC compose + the present draw). Ways to cut it, in order of
  payoff:
  1. **D's non-ROV fast path** for ordinary opaque draws: the replay runs the same pixel shader as the exact
     execution, so whatever D saves there is saved per in-between picture too.
  2. **Replay from the first native draw.** Most of a frame's GPU time before its first native batch is clears,
     the texture-cache uploads (`Pages`/`Scatter` ops: re-uploaded by every replay), the sky / backdrop and 2-D
     under the 3-D. Saving a second bank during the real execution right before B's first native draw op and
     starting the replay there skips all of it (needs a "bank at op index i" hook in `before_execute` / the
     executor; the record keeps the op index).
  3. **Upload once per frame pair.** `execute` re-uploads every array of the list each time (vertices, records,
     scatter words, page records); only the vertices change between ticks. An executor entry that re-issues the ops
     of the last uploaded list with a new vertex buffer saves the upload (CPU `issue` time and PCIe), most of the
     in-between CPU cost (§9).
  4. **Stage 2 (E's GPU vertex stage).** Blending becomes a re-dispatch of the vertex compute shader with blended
     transform records: no CPU blend, no vertex upload.
  (A replay of a list recorded with `split_overlaps` keeps the original split, computed for frame N's positions; a
  blended triangle may then overlap one in the same draw by a sub-tile amount — only the non-ROV path cares.)

## 8. Latency and the presenter

F's pacer makes frame N due at D after the end of the slice in which it flipped (the Latch slice), D = one vblank +
the render p90 by default (`frame_pacing.h`). Frame N is latched about one render time after that slice ends. A tick
at α between due(N-1) and due(N) needs N already latched, i.e. D ≥ (1 - α_first)·T + render, where α_first is the
first tick's position (60 Hz: ticks sit half a refresh from due times, α = 0.25 → quantised up to 0.5: D ≥ ~25 ms +
render; 120 Hz: α = 0.125 → ~29 ms + render). So `--fps` above 30 with `--hfr-latency normal` sets the base delay to
**one game frame** (33.4 ms, + the adaptive render p90 on top): +~17 ms over `--fps 30`'s delay, measured in §9.4.
Within that delay the in-between pictures show the motion of frame N *earlier* than the exact frame (α of it at
due(N-1) + α·T). `--hfr-latency low` keeps F's short delay and, when a tick finds no next frame, extrapolates from
the two latest frames (α > 1, at most +0.5 frame): no added latency, overshoot on sudden stops / turns.
`--present-delay-ms N` still overrides both.

## 9. Results

All runs: windowed, `--renderer native --vu1 aot`, F's display pacing (60.00 Hz monitor, display lock x1), the
replayed routes to their gate end points (climb to vblank 14,000), `--fps 60 / 120 / unlimited`, two runs at a time
on the shared 8-core machine with ~8 other agents' builds and games (2026-10-25, 18:47-19:30). **obs** throughout.

### 9.1 Correctness

* **Replay is exact (obs).** On every dumped frame of every route (52 frames: battle 12+15+6, shop 12, climb 12,
  dorm 2, fusion 2, m1 6 with `--hfr-test-replay`), frame B replayed from its saved GS memory with its own lists is
  byte-identical to the picture the renderer latched on the exact path (`hfr_dump_check.py`: `replay equal`). The
  record boundaries (§7), the bank copies and the swap are therefore right, and an in-between picture differs from
  frame B only where blended native vertices moved.
* **Blending (obs).** Stray pixels (A and B agree, the in-between differs from both by > 48) ≤ 0.04 % on battle /
  climb / fusion / dorm, 0.13 % on one shop frame (the shop's blue sprite transition, drawn as B's — 2-D is not
  blended); pixels that differ from B lie between A and B per channel for 43-100 % (moving edges and the
  transparent effects account for the rest). Screenshots looked at: the battle (Agi cast, the All-Out-Attack
  cut-in, Yukari's attack, the field before the fight), the Tartarus lobby, the shop menu over the 3-D shop, the
  climb's Tartarus floors — no misplaced geometry, cracks or wrong instances seen; the UI is B's in every picture.
* **Matching (obs).** 98.6-100 % of native vertices found their partner in the previous frame on every route;
  held batches (moved too far / turned too much) 1-3 % of matched; new batches (spawns, LOD, re-instancing) < 3 %.
  Cuts: almost all are frame pairs without any native batch (title, movies, menus, loading, the field transition
  screens), the rest camera cuts.
* **Unit tests:** 12 cases / 208 assertions (`p3fes_gs_tests -tc="hfr*"`): perspective-correct blending against a
  hand projection, refusals, matching (order changes, instances by origin, appear / vanish), cuts and holds, flat
  shading, culled-only vertices, `OpList::append` rebasing, the recorder's side table, transform blending (slerp
  keeps lengths, ends exact, reflections, singular), alpha steps, the executor's memory banks on the GPU.

### 9.2 Determinism (obs)

Battle route, windowed, `--renderer native`, snapshot at vblank 6150: `--fps 60` (interpolation on) and `--fps 30`
give the same `eeMemory.bin` (SHA-256 `E5CCF60D…3A51` both), and both equal the gate's zero-replacement reference
`battle_ref_6150` (`tracediff snapshot`: 0 differing bytes, dead stack excluded). The interpolator only reads op
lists on the render thread; nothing reaches the guest.

### 9.3 Frame times and cost per route

Per run: display ticks, how each tick was drawn (in-between / B exact / A as is — of which "late" = the next game
frame was not latched yet), frame pairs and cuts, matched vertices, the render thread's CPU ms per in-between
picture (copy of B's list once per pair, the blend, issuing the replay), the GPU ms per in-between (timestamp
queries: bank copy + replay + compose + draw), the display-rate frame times (present-to-present, every present),
and the game thread's CPU ms per game frame (F's telemetry).

| run | ticks | in-between | exact B | A as is (late) | cuts / pairs | verts matched | CPU ms per in-between (copy / blend / issue) | GPU ms per in-between (max) | display interval ms p50 / p95 / p99 | game-thread CPU ms per frame p50 / p95 / p99 |
|---|---|---|---|---|---|---|---|---|---|---|
| battle 60 | 9717 | 516 (5 %) | 1205 | 7566 (6945) | 608 / 1123 | 98.7 % | 4.06 (0.82 / 1.28 / 1.28) | 3.72 (12.2) | 16.7 / 17.8 / 24.2 | 37.9 / 70.9 / 78.4 |
| battle 120 | 20706 | 1912 (9 %) | 1697 | 16196 (14070) | 747 / 2147 | 99.3 % | 4.16 (0.64 / 1.53 / 1.68) | 5.41 (37.0) | 8.4 / 11.7 / 23.3 | 42.8 / 79.4 / 90.5 |
| battle unlimited | 121180 | 4823 (4 %) | 1144 | 108690 (87733) | 753 / 2525 | 99.0 % | 2.66 (0.64 / 1.24 / 0.96) | 4.52 (24.5) | 1.1 / 4.1 / 9.3 | 37.1 / 69.6 / 79.6 |
| dorm 60 | 6296 | 54 (1 %) | 1999 | 3822 (1838) | 1981 / 2035 | 100 % | 3.84 (0.78 / 1.08 / 1.45) | 6.97 (17.1) | 16.7 / 17.1 / 18.0 | 3.4 / 42.4 / 48.8 |
| dorm 120 | 12915 | 87 (1 %) | 1978 | 9994 (4281) | 1981 / 2068 | 100 % | 4.68 (0.94 / 1.13 / 2.06) | 7.93 (39.1) | 8.4 / 8.8 / 10.6 | 3.5 / 46.1 / 49.9 |
| dorm unlimited | 92016 | 460 (0 %) | 1256 | 83427 (25880) | 1994 / 2211 | 99.5 % | 2.98 (0.87 / 1.04 / 1.29) | 6.71 (30.7) | 1.1 / 1.7 / 5.7 | 3.6 / 44.0 / 49.5 |
| fusion 60 | 8820 | 207 (2 %) | 2235 | 5962 (3970) | 1975 / 2182 | 99.6 % | 4.28 (1.01 / 1.23 / 1.36) | 4.27 (25.0) | 16.7 / 17.1 / 21.7 | 12.0 / 60.7 / 75.0 |
| fusion 120 | 15742 | 370 (2 %) | 1801 | 12591 (6683) | 2011 / 2306 | 98.6 % | 4.87 (0.67 / 1.30 / 2.63) | 23.2 (84.3) | 8.4 / 16.7 / 44.3 | 12.2 / 62.2 / 79.6 |
| fusion unlimited | 97622 | 1389 (1 %) | 1891 | 87762 (43472) | 2150 / 2732 | 99.2 % | 2.74 (0.70 / 1.16 / 1.07) | 9.33 (48.6) | 1.1 / 4.4 / 13.5 | 10.9 / 59.7 / 86.2 |
| shop 60 | 5503 | 557 (10 %) | 1216 | 3283 (2449) | 825 / 1363 | 99.8 % | 6.69 (1.33 / 2.76 / 1.63) | 5.69 (26.0) | 16.7 / 23.4 / 27.9 | 27.0 / 49.0 / 54.3 |
| shop 120 | 11081 | 937 (8 %) | 1347 | 7958 (5632) | 842 / 1415 | 99.3 % | 4.76 (1.07 / 2.24 / 1.34) | 3.15 (29.8) | 8.4 / 10.4 / 18.5 | 26.7 / 51.4 / 56.9 |
| shop unlimited | 74758 | 2913 (4 %) | 800 | 64287 (40337) | 849 / 1773 | 99.4 % | 3.86 (1.27 / 1.89 / 1.24) | 2.71 (10.0) | 1.1 / 3.5 / 12.0 | 28.1 / 53.7 / 59.7 |
| climb 60 (to vblank 14,000) | 22945 | 1064 (5 %) | 2663 | 18769 (16887) | 1867 / 2930 | 98.9 % | 4.83 (0.89 / 1.73 / 1.36) | 4.41 (28.8) | 16.7 / 17.5 / 23.6 | 43.9 / 67.7 / 76.6 |
| m1 60 (boot, 1500 vblanks) | 1795 | 0 | 558 | 858 (356) | 501 / 501 | — | — | — | 16.7 / 17.0 / 17.2 | 2.1 / 32.7 / 35.6 |

What the table says:

* **The display rate is met:** 60 Hz ticks at 16.7 ms p50 (p99 18-28 ms), 120 Hz at 8.4 ms (p99 10.6-44 ms, the
  worst on fusion, §9.4), uncapped at 1.1 ms p50 (~900 presents/s) on every route.
* **On this machine the game itself ran below real time** (game-thread CPU p50 38-44 ms per game frame on battle /
  climb against a 33.4 ms frame), so at most ticks the next game frame was not there yet ("late") and the picture
  was A as is; the in-between share is therefore 1-10 % here instead of the ~50 % (60 Hz) / ~75 % (120 Hz) a
  machine that holds real time shows. Where both frames were there, every tick was drawn (in-between or exact B).
  The interpolator cannot make the game run faster; it needs the game at ≥ 1.0x real time — the other tracks' job,
  and the quiet-machine runs (§11) are the ones to judge smoothness by.
* **Render-thread CPU per in-between: 2.7-6.7 ms** (copy of B's list 0.6-1.3 ms once per game frame, blend 1.0-2.8,
  issue 1.0-2.6). It is on the render thread, not the game thread (the game thread's CPU is unchanged: same columns
  as `--fps 30`, §9.5).
* **GPU per in-between: 2.7-9.3 ms average** (fusion at 120 Hz 23 ms, with the GPU shared by other agents' games),
  i.e. about one more execution of the frame's list. At 60 Hz that is one replay per game frame — affordable; at
  120 Hz three replays per frame need ≤ ~5 ms each to stay under half a frame. The GPU budget (`HfrOptions::
  gpu_budget`, default 0.5 of a game frame, measured per replay) now lowers the steps automatically when the replays
  cost more (120 Hz then shows in-betweens at 60 Hz spacing instead of stalling the real frames); §7 lists the
  savings that make 120 Hz affordable (D's non-ROV path, replay from the first native draw, one upload per pair,
  E's GPU vertex stage).

### 9.4 Latency

With `--hfr-latency normal` (default) the presenter's delay is one game frame + the render p90 (measured 39.4 ms on
battle at 60 Hz) instead of F's one vblank + p90 for `--fps 30` (~20 ms): **+~17-19 ms** from input to the exact
frame N on screen; the in-between pictures show part of N's motion half a game frame earlier than that (§8). With
`--hfr-latency low` the delay stays F's and a tick that finds no next frame extrapolates from the last two (up to
half a frame); motion then overshoots on sudden stops / turns.

### 9.5 With track C's threaded pipeline (main 06e4f8d)

The interpolator works unchanged on the threaded pipeline (the vblank op list travels as a GS-stage closure with
F's PresentPlan, so a Latch list still starts at the flip). Battle route to vblank 2600, `--fps 60` (obs, quieter
machine): 3132 ticks, **463 in-between and 985 exact-B pictures** (of 1448 ticks where the next frame was there,
32 % / 68 %), 692 late, 99.1 % of vertices matched, CPU 3.56 ms per in-between (copy 0.77 per pair, blend 1.22, issue
1.09), display interval p50 16.7 / p95 20.1 / p99 21.9 ms; replay byte-identical on the 4 dumped frames; the one
frame flagged by the checker (0.85 % stray, a camera pan in the Tartarus lobby) shows the clipped near-plane floor /
stair batches that still run on the VU1 a step ahead of the blended geometry (§6) — E's clipper in the model removes
those. The game-thread CPU per frame does not change with `--fps` (the interpolator runs on the render thread), so
`tools/ours/perf/bench.py`'s unpaced capacity numbers are those of track E / C and are not repeated here.

## 10. Part 2 — true 60 Hz game logic: feasibility

_A report, nothing implemented. Sources: the decompiled bodies in `game/`, the Hex-Rays reference
`ida/pseudocode/` (14,500 functions; a read-only hint), the recompiled program `recomp/generated/` (every load of a
constant), the ELF's data. Scripts: `tools/ours/hfr/census_*.py` (§11)._

### 10.1 What the field gate controls — and what it does not

* **It controls the flip cadence and nothing else.** `kwlnVsyncFieldGate 0x19D320` returns -1 on even fields, which
  stops the INTC-2 chain before `_rwDMAVSYNCHandler` (the RW flip) and `kwlnGsSyncVCallback` (`ADXM_ExecVint`, the
  ADX server tick). The game loop itself has **no timer**: `kwlnUpdate` runs once per loop iteration, and the
  iteration blocks in `SkyCameraBeginUpdate → _rwDMAWaitQueue` until the previous frame's flip drained RW's queue.
  Remove the gate (return 0) and the loop runs at 60 iterations per second whenever a frame's work fits one field —
  every frame-counted quantity below then runs **twice as fast**.
* **The game never measures time.** The only clocks it reads are T0 (H-blank counter): `kwlnUpdate` /
  `kwlnRootUpdateShowRasterTask` compute `g_kwlnCpuLoadPct 0x7CE150` (frame delta / 520 lines) and nothing reads it
  back (code: the global's only writer and reader is `0x199140`); the two `T0_COUNT` reads in `kwlnMain` seed the
  RNGs. There is **no variable-timestep path anywhere** — a slow frame is simply a longer frame (the game slows
  down, as on the PS2).
* The frame counters `g_kwlnFrameCounterA/B 0x7CE10C/0x7CE108` (incremented per `kwlnUpdate`) are read by 6
  functions; the per-task counters are inside the task structs.

### 10.2 Census of frame-counted logic

**Central mechanisms (code, exact).** These count game frames for everything built on them:

| Mechanism | Where | What counts frames |
|---|---|---|
| Task kernel | `kwlnTaskMain 0x1949E0` | per-task start delay (+44) and end delay (+48) decremented per frame; per-task frame timers (+36 / +40, read by `kwlnTaskGetTimer 0x195520` and inlined field reads); **~224 task creation sites** (`kwlnTaskCreate` 114 callers, `…WithAutoPriority` 83, `kwlnTaskInitEx` 11, `kwlnTaskInit` 16) = ~200 per-frame state machines |
| Script VM | `scrTraceCode` / `CodeFunc_Comm` (`18` §2) | `task->cmd_timer` (+0xD4) and `task->frames` (+0xD0) per frame; `WAIT n` = `scrGetCmdTimer() >= n` frames (`0x35B030`); `SYNC`; `SCR_GET_TIMER` (`0x35B4A0` → `sub_35ADF0`); 15 functions read the command timer (events, the dorm/field scripts, battle AI waits) |
| Animation | 11 functions (`0x111610`, `0x111CB0`, `0x1EDBE0`, `0x20AC90`, `0x313090`, `0x313490`, `0x314D30`, `0x318770`-`0x318990`) | `RtAnimInterpolatorAddAnimTime 0x4B7240` / `sub_4B74C0` advanced by `speed x 1/30 s` — the **only** load of the 1/30 constant in the program (`0x7CADD4`, `lwc1 $f1, -0x7F1C($gp)`); no 1/60 is loaded anywhere; 30.0f is loaded by one function, 60.0f only by two MatFX bridges (not timing) |
| Per-frame RNG | `kwlnRootUpdateShowRasterTask` | one `RpRandom` draw per frame, so every later random result depends on the frame count; 127 functions call an RNG (encounters `K_Encount_PickEncounter`, the battle camera, battle actions and AI, Shuffle Time, facilities), several of them per frame (random idle motions, effects) |
| Fades | `H_Fade_*` (`0x1075B0`-`0x1081E0`), `nmCmdListStartFade`, `frFontLineFadeStep`, `itfPnlAnim*Fade*` | colour / alpha steps per frame |
| Pad | `H_Pad_Update` (`sub_103580` in `kwlnUpdate`) | key repeat delays / rates in frames (menus, message advance) |
| ADX server | `kwlnGsSyncVCallback` → `ADXM_ExecVint` on odd fields | the ADX stream server's tick (BGM itself is real time on the IOP; the tick only refills) |

**Distributed per-frame logic (heuristic, lower bounds over the Hex-Rays text).** In the ~200 task update
functions and their callees, the per-frame steps are ordinary code — `x += speed`, `if (++t >= 30)`, `a += 8` —
not calls to a time function. A scan for "a memory field incremented / decremented and compared with an integer
literal 2..7200" finds **292** functions, "a float literal added to a memory field" **67**, RNG callers **127**;
**495** functions match at least one class, spread over every band (field 95+34, battle 93+74, battle camera / fx /
script 62, facilities / Tartarus / UI 57, RenderWare 43 — RW's own counters are mostly caches, not timing). The scan
misses steps written through registers, struct copies and table-driven motion (Hex-Rays text only), so the real
number of functions whose result depends on the step is larger: in practice every task update function and the
movement / collision / camera / effect / UI code under them — **on the order of 1,000-2,000 functions** of the
~9,500 game functions (inf).

Examples of the kinds (code): the field camera (`K_FldCamera_UpdateFieldCameraControlerTask 0x1D5220`) follows the
player by per-frame position constraints; the battle camera (`K_FldCamera_UpdateBattleKosakaTask 0x1D7D40`) mixes
per-frame moves with RNG picks; battle states count frames for each phase (`btlSupportTickTimers 0x2DCC40`); panels
open and close by per-frame steps (`itfPnlAnimOpenType10 0x3A9170`, …); message text appears so many characters per
frame; Tartarus enemies move per frame (`ene think proc`).

### 10.3 What a 60 Hz mode would have to do

1. Let the flip run every field (gate off) — trivial.
2. **Halve every per-frame quantity**, or run the logic at 30 Hz and only some of it at 60 Hz:
   * central counters (task delays/timers, script `cmd_timer` / `frames`, `WAIT`): count every second 60 Hz tick
     (~10 sites) — easy;
   * the animation step: 1/30 → 1/60 at `0x7CADD4` (one constant, 11 users) — easy, exact;
   * the per-frame RNG draw and every per-frame random test: only on every second tick, or the probabilities and the
     sequence change (per-frame chances double at 60 Hz: random encounters, idle motions) — moderate, ~127 sites to
     classify;
   * the distributed steps (velocities, angle steps, fades, panel animations, camera constraints, effect timelines,
     text speed, key repeat): each one rewritten with a step factor in hand-written C++ (`game/`) — integer steps
     that are odd (`+= 3` per frame) become fractional (fixed-point changes ripple into the data they touch), and
     exponential smoothing (`x += (y - x) * k`) needs k' = 1 - sqrt(1 - k) — **1,000-2,000 functions to audit and
     change, many of them still recompiled (no hand body yet)**;
   * collision / movement: a half step changes contact results (sliding, corner cases) and therefore positions.
3. Event and battle timelines authored in frames (BF scripts' `WAIT n`, EPL / effect key frames, motion files
   sampled per frame) stay in frames: they would play at the right speed only through the central counters, and
   per-frame interpolation of key frames would still be at 30 Hz unless each player is changed.

### 10.4 What would break

* **Determinism against the original:** a 60 Hz run is no longer the PS2 program. The gates (six routes byte-identical
  to the zero-replacement program), the pair tests (hand body vs recompiled original, same inputs → same memory), the
  segment checks and the PCSX2 oracle all compare at game frames; none of them can validate a 60 Hz mode, and none
  exists for it (the original never ran at 60). Every bug would have to be found by playing.
* **Replays / recorded routes:** input is recorded per vblank against 30 fps logic (`config/inputs/*.txt`); a 60 Hz
  mode desyncs them at the first random draw or movement step.
* **Saves:** compatible (the data does not record the rate), but the play-time counter (if frame-based) would run
  at double speed unless it is one of the central counters.
* **The future multiplayer server (`end-goal` memo, ADR on the server, gated):** an authoritative server needs one
  fixed tick that every client agrees on; the natural tick is the game's own 30 Hz frame (the PS2 logic, already
  deterministic, with replays and the gates as its test bed). A 60 Hz logic mode would either force the server to
  60 Hz (twice the simulation and bandwidth, and a second, untested simulation) or create two incompatible client
  kinds. Display interpolation (Part 1) is exactly what networked games do on top of a fixed tick.

### 10.5 Estimate

| Option | Work | Risk |
|---|---|---|
| A. Full 60 Hz logic (everything above) | central counters + animation + RNG: ~1-2 weeks; the distributed per-frame code: every per-frame function decompiled to readable C++ first (the decompilation waves are at ~9,500 of 14,040 functions, register-faithful bodies, not yet step-parameterised), then audited and changed: **several months** of agent time, then play-testing every system (battle, events, facilities, Tartarus, social links) without an oracle | high: subtle speed / timing / probability bugs, no automatic check; breaks replays and the server's tick |
| B. 30 Hz logic + interpolated display (Part 1) | done here (stage 1), stage 2 with E's GPU vertex stage | low: the logic and its gates are untouched; artefacts are visual only and can be held per batch |
| C. Hybrid: 30 Hz logic, but render-only extras at 60 Hz (camera, skeletal animation sampled at the half step) | the camera / animation would have to be evaluated twice per game frame on a copy of the state (guest code run in a sandbox or re-implemented in C++) | medium; gains over B only for fast rotations (B blends linearly) |

**Recommendation: B.** Keep the game logic at its native 30 Hz (exact, deterministic, gated, the server's tick) and
make the display as fast as the machine allows with interpolated in-between frames — 60 / 120 / the monitor's rate /
uncapped — which is what this track delivers. Revisit A only as an opt-in "experimental 60 Hz" mode after the
whole program is decompiled into readable C++, and never for multiplayer.

## 11. Reproduce

Build: any tree configured from `CMakePresets.json` (the gate's fast tree: MSVC Release, `-DP3FES_VU1_AOT=ON`). The
switches only act in windowed D3D11 play with F's pacing (`--pacing display|clock`, the default).

```powershell
$M = 'F:\P3FES-PORT\p3fes-port'; $exe = 'build\<tree>\bin\p3fes.exe'
$game = "--elf $M\extracted\disc\SLUS_216.21 --iso $M\input\persona3fes.iso --vu1 aot --renderer native"
# Play at 60 / 120 / the monitor's rate / uncapped (30 = exactly as before)
& $exe $game.Split(' ') --fps 60            # or 120, monitor, unlimited; --hfr-latency low; --hfr off
# A route with interpolated-picture dumps, the frame log and the end-of-run summaries ("p3fes: hfr: ..." and
# "p3fes: frame-time: ..."):
& $exe $game.Split(' ') --memcard $M\extracted\_ours\cards\tartarus.ps2 --replay-input $M\config\inputs\to_battle.txt `
    --fps 60 --hfr-dump dump --hfr-dump-every 41 --hfr-dump-max 12 --frame-log frames.csv --frames 6150
python -I tools\ours\hfr\hfr_dump_check.py dump        # replay exactness, motion, stray pixels per dumped frame
# Determinism: the same route at --fps 60 and --fps 30, snapshot at vblank 6150, against the gate's reference
& $exe $game.Split(' ') --memcard <copy of tartarus.ps2> --replay-input $M\config\inputs\to_battle.txt --fps 60 `
    --snapshot-at vblank:6150 snap60          # (windowed: close the window after the snapshot line)
build\<tree>\bin\tracediff.exe snapshot $M\extracted\_ours\battle_ref_6150\eeMemory.bin snap60\eeMemory.bin --dead-stack snap60\capture.json
# Unit tests (matching, blending, transform blending, alpha steps, the recorder side table, executor banks)
build\<tree>\bin\p3fes_gs_tests.exe -tc="hfr*"
# Part 2's census
python -I tools\ours\hfr\census_time_constants.py $M\extracted\disc\SLUS_216.21 $M\recomp\generated
python -I tools\ours\hfr\census_frame_logic.py $M\ida\pseudocode
```

**Quiet machine (for the user):** close other builds and games, then run the route lines above once per rate
(`--fps 60`, `--fps 120`, `--fps unlimited`) and read the `p3fes: hfr:` line (in-between share, CPU and GPU ms per
in-between picture) and the `frame-time: display (every present ...)` line (the display-rate frame times). On a
loaded machine most ticks show "next frame not latched yet": the game itself runs below real time, so there is no
next frame to blend towards (§9).
