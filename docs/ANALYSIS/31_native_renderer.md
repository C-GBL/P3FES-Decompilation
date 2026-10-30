# 31 — The native renderer: RenderWare's g3 batches drawn without VU1, the GIF and the GS front end

_Graphics team track E (the user's order of 2026-10-25: "rebuild a better graphics layer that is 10X more performant
... a perfect 30 FPS at ALL times"; graphics measured at 43 ms of a 33.3 ms frame on the user's machine). Worktree
branch of `main` `4709fee`. Tags: **obs** measured in a run made for this document, **der** arithmetic on obs
numbers, **inf** inferred. Every run here shared the 8-core machine with ~8 other agents' builds and games: wall
times are 1.5-2.5x an idle machine's, so the tables give CPU ms per vblank by zone (`--zones`) and compare runs made
at the same time; the quiet-machine commands are in §8._

## 0. Headline

* **Where the frame goes today (obs, §1).** On the battle route in windowed D3D11 play (`--vu1 aot`), a battle
  vblank costs VU1 41 ms, VIF1 7.4, GIF 3.8, GS front end + op recording 7.1, game code 6.8 (loaded machine). The
  GPU itself is idle most of the frame (0.4-4 ms per list). Two VU1 programs, `g3_skin` (064) and `g3_generic` (042),
  are 90 % of the VU1 work; in the Tartarus field the parallel-projection skin program 063 (the characters' shadow
  textures) adds as much again, interpreted.
* **The seam (§2).** RenderWare's PS2 driver turns every atomic into VIF packets: a per-object block (transform rows,
  lights, GIF tag, material colour, flags) and per-mesh vertex clusters, each cluster one MSCNT batch of a g3 program.
  The native renderer keeps everything the EE side does — the RW driver, the packets, the DMAC and VIF1 with their
  timing and registers, the UNPACKs into VU1 memory — and replaces only what happens at the MSCAL/MSCNT: instead of
  running the microprogram, a **semantic model** (`runtime/native/g3_model.cpp`) computes the batch's vertices from
  VU1 memory in C++ and hands the triangles straight to the GPU op list. No VU1 program, no PATH1 packet, no GIF
  parse, no GS vertex queue.
* **Why there and not at RpAtomicRender (§2.2).** At the VU1 boundary the inputs are complete and unambiguous (the
  material block the bridge uploaded, the skinned bone palette, the morph target), the order of draws relative to the
  emulated ones (Im2D, sprites, PATH2/PATH3 uploads) is exactly the kick order, and every batch can fall back to the
  exact VU1 run on its own. The RW-level knowledge (pipelines, bridges, the light list `openVU1SetupPktNew` builds,
  the code arrays) is what the model is written from.
* **Composition (§3).** Native triangles go into the same op list, at the position of the kick, with the GS state
  the exact path would have had (GsCore's context registers set by the PATH2 A+D packets, PRIM from the batch's GIF
  tag). The D3D11 back end then draws them through the same ROV pixel pipeline into the same 4 MiB VRAM buffer:
  textures, CLUTs, Z buffer, blending, offscreen targets and the CRTC are shared by construction. There is no second
  render target and no reordering.
* **Exactness policy (§4).** The EE never observes VU1 work: DMAC completion time does not depend on it, VU1 memory
  is not guest-visible, PATH1 never stalls PATH2/PATH3 in the synchronous model (the hook falls back whenever the GIF
  is busy, so a queued PATH1 packet keeps its place). Native mode is play-only (`--renderer native`, windowed
  D3D11); headless runs and every gate keep the exact path and stay byte-identical.
* **Validation (§5).** `p3fes_native_check` (captured batches) and `--renderer native-diff` (every batch of a whole
  route, model vs the VU1's own packet): positions within 1/16 pixel, colours exact, STQ within 5e-7 relative; ADC
  (culling) identical except sliver triangles (0.06 % of vertices). Pictures: PSNR against the exact (software)
  frame equals the emulated D3D11 path's to 0.02 dB on every recorded frame (50-59 dB), 0 % of pixels off by more
  than 32.
* **Speed (§6).** Battle route, windowed, same build, runs at the same time (loaded machine): battle segment 67.9 →
  30.2 ms per vblank (VU1 41.1 → 13.5, GIF 3.8 → 1.3, GS front end 7.1 → 2.9), field 1F 50.5 → 30.1. What remains:
  the model + triangle submission on the EE thread (~6 ms per vblank under load), the programs not yet native
  (MatFX 061/093/097, skin MatFX 101/102, 046, clipped batches), VIF1 (track D's UNPACK fast path takes it from 5.9
  to ~1.4: measured with an equivalent change here, dropped from this commit in favour of D's).

## 1. Where the time goes (baseline)

_§6 has the tables; method: `p3fes --gs-backend d3d11 --unpaced --vu1 aot --zones FILE` on the recorded routes,
`tools/ours/perf/zones_report.py` with the route segments of docs/ANALYSIS/23 §1.3._

## 2. The g3 programs as a semantic model

### 2.1 Batch input (VU1 data memory at the MSCNT)

| Address | Content | Written by |
|---|---|---|
| TOP + 4k (+5k skin) | vertex k: position xyz, uv xy, prelit colour (int32 x4), normal (signed 8-bit unpack, int32 x4); skin: + bone weights (floats whose low 16 bits are the bone index x4) | the mesh's resEntry UNPACKs (V3-32, V2-32, V4-8, V3-8, V4-32) |
| TOP + 4N.. / 5N.. | morph target: N positions, then N normals | morph instancing |
| 0x2B8.. | skin bone palette, 4 qwords per bone | `sub_46B8E0` (palette upload) |
| 0x3D0-0x3D3 | lighting matrix (3x3 + translation; w lanes: scale) | `openVU1SetupPktNew` |
| 0x3D4.. | light list: per light the colour (type in w: 1 directional, 2 ambient, 0x80 point, 0x81 spot, 0x82 soft spot, 0 end), position / direction (+ radius), spot direction (+ cone) | `openVU1SetupPktNew` (`sub_49FF10`, `sub_4A06C0`) |
| 0x3F0-0x3F3 | camera x object transform rows | object setup |
| 0x3F6 | fog: z = scale, w = near | camera |
| 0x3F7 / 0x3F8 / 0x3F9 | screen scale, screen offset, offset 2 (xy) | camera (`sub_4EEC20`) |
| 0x3FA | GIF tag yzw: PRE + PRIM + FLG + NREG, REGS (STQ RGBAQ XYZF2/XYZ2) | bridge (template 0x9658A0) |
| 0x3FB | material colour (x 1/255 scaling built in) | bridge (`sub_49CAB0`) |
| 0x3FC | lighting factors: x ambient, z directional / point / spot, w morph factor | bridge (`sub_49CBD0`) |
| 0x3FD / 0x3FE | guard-band clip scales | bridge (clip vectors) |
| 0x3FF | x variant flags (bit 1 cull/clip, bit 3 full clipper, bit 2 triangle list, bit 0 fog), y continuation (written by the init), z cull mode | `RpAtomicPS2AllPrimTypeTransTypeSetupFunc` / bridge |

### 2.2 What one batch computes (042 / 064; 063 differs in §2.4)

1. **Skinning (064, pairs 0x4B-0xAD).** Blended matrix = Σ w_j · palette[index_j] (rows 0x2B8+idx .. 0x2BB+idx),
   applied to the position (with translation) and the normal; the result is written back as a 4-qword vertex.
2. **Morph (both).** When 0x3FC.w ≠ 0: position = p·(1−w) + p2·w, normal = (n·(1−w) + n2·w)/128.
3. **Lighting (0x82-0x185).** colour = itof(prelit) + Σ lights, then min(colour, 255) × material colour:
   ambient + L·k.x; directional + L·k.z·max(0, n·(M3·d·(−m3.w))); point + max(0, L·k.z·max(0, d·n)·(1/|d| − 1/(r·m0.w)))
   (d = M4·pos_L − p); spot the same with a cone test; soft spot the same scaled by max(0, (cone − cos)/(1 + cone)).
   No lights: colour = itof(prelit) × material colour.
4. **Transform (0x1B2 ...).** The init (MSCAL 0, pairs 0x00-0x32) turns 0x3F0-0x3F3 into screen rows vf28-vf31
   (z lanes cleared so that Z = offset.z + scale.z / w, xy recentred by half of w and scaled by 0x3F7). Per vertex
   c = vf31 + vf28·x + vf29·y + vf30·z; Q = 1/c.w (fog variants: Q = fs / (fs·w)); XYZ = vf02 + c·Q (12.4 by FTOI4);
   STQ = (u, v, 1)·Q; RGBA = FTOI0(colour); fog F = clamp(fs·w, fs·near, fs·near + 255) − fs·near.
5. **ADC (culling).** Per kicking vertex (strips: from the third on, lists: every third) the sign of the screen-space
   cross product of the triangle, with the strip's alternating operand order, against the cull mode 0x3FF.z; the
   guard-band variants also cull a triangle with any vertex outside the guard band (CLIPW against the scaled clip
   vector); the full clipper (0x3FF) skips a batch whose vertices are all outside one plane, takes a fast path when
   none is outside (homogeneous triple products for the ADC, the odd/even halves inverted by an extra + 0x8000),
   and clips otherwise (not modelled: those batches run on the VU1).

Details that the comparison against the interpreter pinned down (each was a mismatch first): the S flag of a −0
cross product counts as negative; the clipper's pair loop also judges the quadruple after the last vertex when N is
odd (whatever the buffer holds there); non-fog variants write the 16-bit ADC word sign-extended (0x7FE0 when drawn);
the fog variants put ADC and fog in one word ((fog + 2048.5)·16).

### 2.3 The init and the VU state a fallback needs

MSCAL 0 is emulated in C++ (`g3_init`, idempotent with the program's own init); after a native batch the hook leaves
what a later exact MSCNT reads: TPC (the pair after the E pair's delay slot), vi15 (the jump back to the batch
start), the swapped output buffers vi13/vi14. Every batch can therefore fall back to the exact program by itself.

### 2.4 vu1_prog_063_g3_skin (parallel projection)

g3_skin's code-array entry 3 (camera transType bit 3 = not perspective): the characters rendered into the 128x128
shadow textures of the field (FBP 488/496/504, docs/ANALYSIS/25 §1). Same batch layout, skinning and lighting code
(batch start 0x25, E at 0x625); its init keeps the transform rows whole (vf31.xy − 0.5, xyz scaled by 0x3F7), and
the output part has no division: XYZ = vf31 + vf02 + M·p, STQ = (u, v, 1), fog always (clamp(fs·(w − near))). No fog
variant bit; strip / list / guard band (judged against ±1) / full clipper. ADC: cross-product sign ≠ the cull mode.

## 3. Composition with the emulated draws

### 3.1 One op list, one VRAM

The D3D11 back end (docs/ANALYSIS/25 §11) executes, per vblank, an op list recorded in GS order: draw batches,
transfer scatters, CLUT loads, copies. Native batches append ordinary draw ops to the same list at the moment the
VU1 would have kicked their packet, so:

* **order** — a native mesh is drawn after the PATH2 A+D packet that set its TEST/TEX0/CLAMP/ALPHA, after the PATH3
  texture upload it samples, before the Im2D HUD drawn later in the frame; the full-screen passes and render-to-texture
  targets (shadow textures, the battle's 16-bit target) see exactly the pixels they would see;
* **state** — the draw constant block is decoded from GsCore's registers (the same `decode_draw_state` the emulated
  path uses) after the native batch writes the PRIM register its GIF tag would have written;
* **pixels** — the same ROV pixel shader: GS texture formats and CLUTs straight from the VRAM buffer, Z16S, the
  eleven blend equations, alpha/destination-alpha tests, fog, FBMSK, offscreen targets, the CRTC merge.

Nothing is drawn twice and nothing can be reordered, so no shared-depth-buffer or render-target plumbing is
needed: the emulated GS frame and the native draws are one stream. The cost of this choice is that native draws are
rasterised by the GS pixel pipeline in HLSL (ROV, 0.4-4 ms of GPU per frame on the RTX 3060) rather than by fixed
function; that is far below the frame budget and keeps every GS blend/test quirk exact.

### 3.2 GS state left behind

The exact path leaves, after a batch, PRIM (written: identical), RGBAQ / ST / Q / XYZ of the last vertex and the GS
vertex queue holding the last two vertices. Every g3 packet and every Im2D packet starts with a tag that has PRE = 1
(PRIM written, queue reset) and sets every attribute per vertex, so nothing later reads those leftovers; the GIF's
last-tag registers (readable only while paused) are not modelled.

### 3.3 Stages (the hook API other renderers and the pipelined host code against)

* `gs::IVuRunHook` (`p3fes/gs/vif1.h`): `bool run(const VuRunInfo&, VU1Interpreter&)` — called by whoever executes a
  VU1 run, after the VIF's own register update, with op / entry / TOP / ITOP / `gif_busy`; true = handled (the VU1
  does not run). `after_exact` follows every declined run. Today the caller is `Vif1::run_vu` on the EE fiber; on a
  pipelined host (track C) the call moves with the VU1 run onto the VU1 stage (`GsPipeline::set_vu_run_hook`,
  `VuRunInfo::queued` ≙ `gif_busy`), where VU1 memory is current.
* `NativeG3::run` is the VU1 stage: it reads VU1 memory, runs the model and builds a self-contained `GsWork` (PRIM,
  the vertex words, the triangle index triples; no pointer into VU1 memory). `apply_gs` is the GS stage: the PRIM
  write, the GS-register-dependent vertex fields (FOG for XYZ2, UV), `GsOpRecorder::on_native_triangles`. Without an
  emitter it runs at once; with `set_emitter(fn)` it travels as an in-order GS-stage command (`GsPipeline::emit_gs`).
* `GsOpRecorder::on_native_triangles(regs, GsVertex*, nv, u16* idx, ntri, prim_records)` (`p3fes/gs/gs_ops.h`): what
  any native producer (Im2D, MatFX, PTank, Rt2d) calls with triangles in GS window terms; it records exactly what
  `ntri` triangle `on_draw` calls would, with the state decoded once.

## 4. Determinism and the exactness policy

### 4.1 What the EE can observe

| Effect of a skipped VU1 run | Why the EE cannot see it |
|---|---|
| DMAC channel 1 completion time | `dma_base_cycles + qwc * dma_cycles_per_qword` (runtime/hle/kernel/dmac.cpp): independent of VU1 work |
| VIF1 registers (STAT, TOP/ITOP/TOPS/DBF, CYCLE, MASK, ROW/COL, CODE) | updated by the VIF before the hook, UNPACKs still executed |
| VU1 data / micro memory, VU1 registers | not mapped into the EE's address space (VU1 runs only from VIF1) |
| GIF_STAT (P1Q, APATH, OPH) | a PATH1 packet that would queue (GIF busy) falls back to the exact run; otherwise the packet runs and ends inside the kick, leaving the GIF idle exactly as now |
| GS privileged registers (CSR, IMR, SIGNAL/FINISH/LABEL) | g3 packets carry no such registers |

So guest state and guest timing are those of the exact path; the native renderer changes only what the GPU draws.
Headless runs never install the hook, so every gate (software or `-FastGs` exact D3D11) is byte-identical by
construction; the windowed native run's `eeMemory.bin` at a snapshot equals the exact reference (§5).

### 4.2 VU1 state a skipped run does not produce

A skipped run leaves VU1 registers and data memory as they were, except what `leave_like_exact` writes (TPC, vi15,
vi13/vi14) and what the emulated init writes (vf02, vf28-vf31, vi12-vi14, 0x3FF.y). `--renderer native-diff` measures
the rest on every batch of a route (the exact run's final state against the state the native path would leave); the
table is in §5. Everything in it is scratch the programs overwrite before reading: the batch's input buffer (lighting
and skinning rewrite it in place), the output double buffers, temporaries vf01/vf03-vf27, vi01-vi11, ACC, Q, P, the
flag registers. `--renderer native-verify` closes the loop: native rendering, but every 16th batch runs exactly on the
VU state left by the skipped runs before it, and its packet is compared with the model (§5). Programs other than the
g3 ones start with their own MSCAL init after their own MPG upload; they cannot rely on g3 registers either.

## 5. Validation

### 5.1 The model against the interpreter on captured batches (`p3fes_native_check`, obs)

11,564 batches sampled over the whole battle route (`--native-capture DIR 97 12000`) plus 895 from vblank 5800:

| Program / variant | batches | modelled | result |
|---|---|---|---|
| generic strip / strip_fog / list | 2,382 | all | X/Y within 1/16 px (1.2 % of vertices off by 1/16), Z rel ≤ 1.1e-4, colour exact, STQ rel ≤ 4.4e-7, ADC exact except 86 of 119,102 vertices (slivers) |
| skin strip / strip_fog | 7,255 | all | the same; ADC 9 of 286,876 |
| generic clip_strip | 1,727 | 1,124 (1,087 culled whole, 37 fast path) | 603 needed clipping (run on the VU1) |
| skin clip_strip | 179 | 157 (149 culled whole) | 22 needed clipping |
| generic clip_list | 21 | 0 | not modelled (VU1) |

The checker also reports the model's cost: 227 ns per vertex single-threaded (§6).

### 5.2 Whole routes, in the running game (obs)

* `--renderer native-diff` (every batch exact, the model compared with the VU1's packet), battle route 0-6300:
  **1,195,478 batches, 131 mismatched** (all `skin clip_strip`: the clipper's inside/outside decision on vertices
  near the guard band), 24,494 ADC flips in 45.1 M vertices (0.05 %, sliver triangles).
* VU state after each exact run against the state the native path would leave (same run): every run differs in
  scratch — vf01/vf03-vf27, vi01-vi11, ACC/Q/P/flags, the input and output buffers (blocks 0x000-0x3CF) — and in
  1-ulp init rounding of vf28-vf31 (≈ 10 %); vi12, the light block 0x3D0-0x3EF and the constants/flags 0x3F0-0x3FF
  never differ.
* `--renderer native-verify` (native rendering, every 16th batch run exactly on the VU state the skipped runs left,
  packet compared with the model), battle route 0-6300 with 063 native as well: **74,865 exact runs, 5 mismatched**
  (the same clipper decision as in diff mode), 1,582 ADC flips in 2.8 M vertices. So nothing a later run reads
  depends on the skipped runs' leftovers.

### 5.3 Pictures (obs)

`frame.png` of windowed runs (`--snapshot-at`, the GPU picture read back) against a headless exact run of the same
build (D3D11 exact = the software GS byte for byte), battle route, `tools/ours/perf/frame_psnr.py`:

| vblank | scene | emulated D3D11 (interpolated) | native | native + verify |
|---|---|---|---|---|
| 3000 | Thebel 1F, dialogue + bust-up | 58.95 dB | 58.95 dB | 58.95 dB |
| 4200 | Thebel 2F field | 50.28 dB | 50.26 dB | 50.26 dB |
| 5000 | battle, command menu | 54.00 dB | 53.98 dB | 53.98 dB |
| 5800 | battle, WEAK hit | 55.62 dB | 55.61 dB | 55.61 dB |
| 6150 | results | 52.81 dB | 52.81 dB | 52.81 dB |

Other routes (native with 063, against a headless exact run of the same build; emulated D3D11 in brackets):
dorm 2000 / 3500 identical (inf), 4900 56.53 (56.53) dB; M1 200 / 380 identical (no g3 batch yet); fusion 2000
67.93 (67.93), 4000 56.12 (56.12), 6300 70.47 (70.51); shop 2000 70.87 (71.86), 3000 60.12 (63.23; 0.001 % of pixels
off by more than 32, max 73: a few clipper / sliver pixels), 4100 56.01 (56.17) dB. Climb: pending.

SSIM ≥ 0.9997 and 0.000 % of pixels off by more than 32 everywhere except vblank 4200 (0.026 %, identical in the
emulated run: the interpolated rasteriser's own differences). The native renderer adds nothing measurable to the
interpolated back end's error.

## 6. Speed

Zones per vblank (ms, `--zones`, `--vu1 aot`, MSVC Release, loaded machine; emulated and native runs of the same
build made at the same time; battle route segments of docs/ANALYSIS/23 §1.3):

| Zone | battle emulated | battle native | field 1F emulated | field 1F native | Thebel 2F emulated | Thebel 2F native |
|---|---|---|---|---|---|---|
| VU1 (incl. the native model) | 41.12 | 13.53 | 25.27 | 8.94 | 61.76 | 38.39 |
| VIF1 | 7.40 | 5.91 | 4.70 | 4.83 | 8.39 | 7.40 |
| GIF | 3.75 | 1.31 | 5.71 | 4.03 | 6.09 | 3.01 |
| GS front end + recording | 7.11 | 2.90 | 4.50 | 2.83 | 10.32 | 5.89 |
| game code (ee) | 6.81 | 5.43 | 7.81 | 7.11 | 7.78 | 6.68 |
| **wall per vblank** | **67.87** | **30.22** | **50.48** | **30.10** | **95.59** | **62.56** |

(obs; Thebel 2F in this pair still runs 063 on the VU1 interpreter: 063 native is in the committed code, measured in
verify mode only so far.) The native model and the triangle submission cost 7.7 s + 12.4 s over the route's 39.6 M
native vertices (≈ 0.5 µs per vertex under load; 227 ns of it is the model, single-threaded, in
`p3fes_native_check`): the next step moves that work to the GPU (§7).

**Stage 2 (GPU vertex stage + clipping in the model), on main 06e4f8d with track C's threaded pipeline (VU1 and GS
workers), lighter machine load; windowed, wall ms per vblank, the same build in both modes:**

| Segment | emulated | native (GPU stage) |
|---|---|---|
| field 1F (2750-3850) | 5.31 | 5.01 |
| Thebel 2F (3950-4600) | 22.75 | 7.34 |
| battle (4600-6150) | 9.38 | 7.51 |

Worker CPU over the route: VU1 stage 47.6 → 29.8 s, GS stage 20.5 → 13.3 s; PATH1 packets 1.85 M → 0.72 M.
PSNR against the exact picture equal to the CPU-model native path on all five battle frames (57.6 / 50.3 / 54.0 /
55.6 / 52.8 dB).

Remaining VU1 work in the battle segment (per flip, emulated programs, loaded): 061 g3_matfx 6.4 ms, 101
g3_skin_matfx 4.3, 042 clipped batches 2.9, 093 g3_matfx 2.6, 046 g3_generic[0] 2.1, 039 Im2D 1.0.

## 7. What falls back, and next steps

* Falls back today: clip_list, any tag other than PACKED STQ/RGBAQ/XYZ(F)2, a busy GIF, every non-g3 program
  (2,450 of 1.26 M g3 batches on the battle route).
* **Clipping in the model (stage 2).** A full-clipper batch with vertices outside the guard band is clipped in
  homogeneous space against the six planes the VU1 tests, each triangle as a fan, culled by the clipped polygon's
  screen orientation under the clipper's rule; fallbacks on the battle route 59,047 → 2,450.
* **GPU vertex stage (stage 2, default with an interpolated D3D11 renderer; `--native-cpu` keeps the CPU model).**
  Every batch except the full clipper's is sent as a record (`g3_gpu_record`: header, vf28-vf31/vf02, VU1
  0x3D0-0x3FF, the vertex block; the bone palette separately, shared by consecutive batches of an object) into
  `OpList::nat_in` with a slot table `nat_tab`; `GsOpRecorder::on_native_gpu_batch` records a native draw op
  (`GpuOp::native`). Before a list's ops run, `cs_native` (`p3fes/gs/gs_native_hlsl.h`, the model in HLSL) computes one
  triangle per thread — morph, skinning (VU1 address wrap of the bone index), the light list, the transform, the
  ADC rule of the variant, each vertex's F from its own W word — into a vertex buffer the native draw ops read; a
  culled triangle is written with zero area. `p3fes_native_gpucheck` runs the records of captured batches through the
  recorder and the shader on the GPU and compares every vertex with the CPU model: 11,564 route-wide batches,
  759,507 vertices, position / Z / colour / STQ / fog 0 differences, 148 culling decisions differ (slivers).
* Next: the CPU side of the GPU stage (record build 0.5 µs per batch; the recorder call and the threaded
  hand-off's per-batch allocation are what remains), the MatFX / skin-MatFX programs, Im2D (other agents).
* Other agents (hook API of §3.3): Im2D / sprites / fonts (programs 036-039), RpMatFX (061/093/097) and skin MatFX
  (101/102) on top of the shared lighting / skinning / transform functions of g3_model, PTank (033/035), Rt2d (089).

## 8. The high-frame-rate mode (track H) on top of this renderer

The user's target moved to ≤ 15 ms per game frame and as high a display rate as possible, with interpolated
in-between frames. What the native path provides or will provide for that:

* **Stable batch identity.** A g3 batch is identified by (resident program, the VU1 entry, the DMA address of the
  mesh resEntry the VIF1 chain `call`s, the cluster index inside it). The resEntry address is stable for as long as
  the mesh stays instanced (RW re-instances only on geometry change), so it identifies the geometry across frames;
  the object block (0x3F0-0x3FF, the bone palette at 0x2B8) identifies the atomic's transform for the frame. To be
  added: the DMAC passes the resEntry address down with the VIF1 data (a `VuRunInfo` field).
* **Transform inputs per batch, kept for the previous frame.** Everything the vertex math needs is already gathered
  per batch by the model: the screen transform rows (vf28-vf31 after the init: camera x object), the screen offset /
  scale, fog, the light list in object space, the bone palette, the morph factor. Keeping last frame's copy keyed by
  batch identity costs one small record per batch (≈ 70 qwords + the palette per skinned object).
* **Re-issue without the game.** Native draws are pure functions of (batch input buffer, transform record, GS draw
  state). An in-between frame re-runs the model (or the GPU vertex shader, next step) with blended records: rows
  interpolated (or decomposed: the camera and object parts both come from the RW driver's per-object setup), bone
  matrices blended per bone, then the same `on_native_triangles` with the recorded draw state; emulated (non-native)
  draws of the frame are repeated unchanged (UI and 2D are not interpolated).
* **GPU vertex processing** (§7) becomes the main lever: vertex work per displayed frame doubles at 60 fps.

**As merged with tracks D and H (2026-10-28).** The batch tag is track H's (`NativeG3::batch_tag`: FNV-1a over the
first 8 input vertices, the last one, N and the program; rows 0x3F0-0x3F3), computed only while the recorder's side
table is on; fallback brackets carry it too. H's interpolator blends the converted vertices of the side table
(`OpList::nat_*`), which only the CPU model produces, so with the side table on (`--fps` above 30) every batch takes
the CPU model and the GPU stage is idle; at the game's own rate the GPU stage runs. The GPU stage writes track D's
40-byte `GpuVertex` (packed rgba / uv, integer fog, the draw state's `cbi` from record word 11, rebased by
`OpList::append`); a native op merges only with native ops (its vertices live in the stage's buffer), and since its
triangles' rows are not known on the CPU it counts as writing every row of its scissor for D's merge and CLUT-source
checks. Battle route, windowed (machine loaded by a gate run): PSNR against the exact picture 57.57 / 50.26 / 53.96 /
55.59 / 52.81 dB with the GPU stage and with `--fps 60` (CPU model), as before the merge; paced `--fps 60`: 2,023
in-between pictures, batches matched 99.0 %. Next: GPU-stage output into the side table (or blending on the GPU) so that
`--fps 60` keeps the GPU stage.

## 9. Reproduce

```
p3fes --gs-backend d3d11 --unpaced --renderer native|emulated|native-diff|native-verify --zones Z.tsv ^
      --memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt --frames 6300 ^
      --snapshot-at vblank:5800 DIR
p3fes --headless --gs-backend d3d11 --gs-exact <same route> --snapshot-at vblank:5800 REF      (the exact picture)
python -I tools\ours\perf\frame_psnr.py --trees REF_PARENT DIR_PARENT
python -I tools\ours\perf\zones_report.py Z.tsv --seg battle=4600:6150 --vu1 battle
p3fes ... --renderer native-diff --native-capture CAPDIR 97 12000    then    p3fes_native_check CAPDIR
```

Quiet-machine measurement for the user: the first command with `--renderer emulated` and `--renderer native`, one
after the other, nothing else running; compare the `battle` rows of `zones_report.py`.
