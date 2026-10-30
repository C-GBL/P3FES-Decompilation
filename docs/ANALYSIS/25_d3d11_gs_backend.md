# 25 — The D3D11 GS back end: what the game uses, how it maps to D3D11, and a first step that is bit-exact

_Phase 6 design (GOAL: ≥100 % speed on the recorded battle route, then a DirectX 11 renderer). Inputs: a dynamic
census of every GS feature on the battle route and the dorm route (new opt-in probe `p3fes --gs-census`), one-frame
GS command-stream recordings (`p3fes --gs-record`), and an experimental D3D11 back end that replays such a recording
(`p3fes_gsreplay`). Static references: `10_frame_loop_gs.md`, `14_vu1_gs_census.md`, `22_rendering.md` (the draw
path), `runtime/gs/README.md`, `RUNTIME_CONTRACT.md` §5. GPL sources (PCSX2's GS) were not opened (ADR-0010); the
design follows the GS User's Manual definitions as implemented in our own `runtime/gs` and public D3D11 knowledge.
Tags: **obs** measured on this machine, **der** derived from measurements, **inf** inferred._

## 0. Headline

* **The game uses a small, regular slice of the GS (obs, §1).** One screen format: PSMCT32 640×448 at FBP 0/140
  (FBW 10), **PSMZ16S** at ZBP 280; **only sprites, triangles, strips and fans** (no points, lines, AA1, FST/UV
  texturing); textures **PSMT8/PSMT4 with a PSMCT32 CLUT (CSM1, CSA 0, CLD 1)**, PSMCT32, and one PSMCT16S render
  target; **MODULATE** only; bilinear (MXL 0) almost everywhere, a little nearest, one trilinear MXL 2 effect worth
  18 k pixels; 11 ALPHA equations including **destination-alpha** ones (`0x52/0x54/0x58`) and FIX ones; a dozen
  TEST combinations including **DATE**, **AFAIL FB_ONLY/ZB_ONLY/RGB_ONLY** and "NEVER + FB_ONLY" as a Z-write mask;
  FBMSK all/partial; COLCLAMP 1, PABE/FBA/SCANMSK never, DTHE only on the 16-bit target; offscreen render targets
  (three 128×128 PSMCT32 at FBP 488/496/504 in the field, one 512×256 PSMCT16S at FBP 480 in battle) that are later
  sampled as textures; contexts 1 **and 2**.
* **The EE never reads GS memory on these routes (obs).** 0 local→host transfers, 0 local→local copies,
  0 SIGNAL/FINISH/LABEL; the only privileged-register read is **CSR** (≈1.5 per vblank, the FIELD bit). Uploads are
  host→local PSMCT32/PSMCT16 over PATH2 and PATH3. So nothing the EE can observe depends on rendered pixels: a GPU
  renderer cannot move the memory gates as long as register/transfer semantics stay the software model's.
* **Rasterisation is the biggest host cost (obs/der, §2).** It is 40–62 % of wall time in the battle segments,
  52 % in the field, 69 % at the title (probe timing per primitive; the draw-path agent's sampling profile agrees:
  55.1 % in battle, 57.7 % in the field). Taking it off the EE thread gives **≈2.1× in battle and ≈2.0× in the
  field** by itself (der); together with VU1 acceleration (34.5 % of battle) the GS work stops being the limit.
* **First step done and bit-exact (obs, §7).** `p3fes_gsreplay` replays a recorded frame through the software GS and
  through D3D11 with **GS local memory as one 4 MiB UAV** and the GS pixel pipeline in HLSL. With per-pixel exact
  attribute evaluation (`--exact`, doubles) and rasterizer-ordered views, the GPU result is **byte-identical to the
  software rasteriser over the whole 4 MiB on all seven recorded frames** (title, field ×2, battle ×2, results,
  dorm) — frame buffers, Z buffer, offscreen targets and the CRTC output. The cheaper interpolated mode gives
  43–67 dB PSNR with an identical Z buffer. GPU time on an RTX 3060: **0.7–5.6 ms** per frame interpolated,
  **3.8–21 ms** exact, against **52–311 ms** of software rasterisation for the same frames.
* **Built (§11):** windowed play renders on the GPU by default (`--gs-backend auto|d3d11|software`), interpolated
  attributes, with software fallback and bounded, message-pumping waits; a windowed d3d11 dorm replay leaves
  `eeMemory` byte-identical to the software reference.
* **Headless exact back end (§12):** `--headless --gs-backend d3d11 --gs-exact` renders on an offscreen device in
  exact mode; the gates' `-FastGs` mode. Snapshots (`frame.png`, `eeMemory.bin`, `gsMemory.bin`) are byte-identical
  to the software GS on all three gate routes. Software stays the headless default.
* **Architecture (§3):** keep `GsCore`'s register file, kick rules, transfers and CLUT logic on the EE fiber
  (that is what the EE observes); replace only `rasterize()` with an op list (draw batches, transfer scatters, CLUT
  loads) handed to a render thread that executes it on D3D11 against the VRAM UAV and composes the CRTC picture on
  the GPU. Headless gates keep the software rasteriser as the oracle; `p3fes_gsreplay` keeps the GPU path honest.

## 1. Dynamic census (obs)

**Method.** `--gs-census FILE --gs-census-marks V1,V2,…` installs a `gs::IGsDrawObserver` on the core. For every
kicked primitive it keys the *effective* state at draw time (PRIM attributes after PRMODECONT, the selected context's
FRAME/ZBUF/TEST/ALPHA/TEX0/TEX1/CLAMP/SCISSOR/XYOFFSET/FBA, TEXA, DTHE/COLCLAMP/PABE/SCANMSK; irrelevant fields
zeroed so e.g. ALPHA does not split keys when ABE = 0) and accumulates primitives, **pixels that reached the
frame/Z write stage** and nanoseconds spent rasterising; per vblank segment it also diffs the core/GIF/privileged
counters (uploads by PSM, local→host qwords, local copies, CLUT loads, SIGNAL/FINISH/LABEL, EE reads per privileged
register — a new `GsPrivStats::reads[]`) and tracks 8 KiB pages last written by a draw vs. by an upload (texture
footprints that hold draw output, uploads over drawn pages, readbacks of drawn pages). It never changes guest state;
without the option the host creates no probe and the core pays one pointer test per primitive. Routes: the battle
route (`to_battle.txt`, Tartarus card, 6,700 vblanks) and the dorm route (`to_dorm.txt`, new card, 4,900 vblanks).
Raw outputs (gitignored scratch): `census_battle.txt`, `census_dorm.txt`; the table below aggregates them.

Columns: **boot** = vblank 0–1064 (logo, opening movie), **UI** = title/menus 1064–2000 and the results screen
6150–6258, **field** = Tartarus 3000–4614 and 6258–6700 (+ load 2000–3000 folded in where noted), **battle** =
4614–6150 (encounter transition, battle, victory). "px" = pixels written, "pr" = primitives.

| Feature | Battle | Field | UI (title / results) | Notes for the back end |
|---|---|---|---|---|
| PRIM types | sprite 875 M px, trifan 849 M, tristrip 1016 M (ctx2 600 M), triangle 189 M | sprite 1195 M, trifan 1388 M, tristrip 446 M, triangle 137 M | title: trifan 1075 M, sprite 519 M, strips; results: sprite 62 M, trifan 46 M | **no point, line, line strip, AA1** on either route |
| Shading / texturing | Gouraud everywhere, flat sprites; **STQ only** (FST never), fog on strips | same, fog heavy (14 M fogged strip prims) | same | per-pixel `s/q`, `t/q`; fog per vertex |
| Context | ctx 1 and **ctx 2** (strips, 600 M px) | ctx 1 (ctx 2 11 M) | ctx 1 (title ctx 2 27 M) | both register sets |
| FRAME | CT32 FBP 0/140 FBW 10; **CT16S FBP 480 FBW 8** (512×256, DTHE 1, 6 prims) | CT32 FBP 0/140; **CT32 FBP 488/496/504 FBW 2** (128×128, 3.7 M prims of ~9 px) | CT32 FBP 0/140 (+FBP 504 on the title); boot clear FBP 0 FBW 16 | render-to-texture of small targets; RW clear = FBMSK=all sprites |
| FBMSK | 0, all (Z-only clears), partial (406 M px) | 0, all, partial (366 M px) | 0, all, partial | arbitrary masks |
| ZBUF / Z test | **Z16S ZBP 280** only; ALWAYS, GEQUAL; ZMSK common | same | same (boot clear ZBP 256) | 16-bit Z, GEQUAL |
| Alpha test | off, GEQUAL 7F FB_ONLY, **NEVER 80/00 FB_ONLY** (Z-write off), GEQUAL 5F, GREATER 0, RGB_ONLY ×3, NOTEQUAL 0 KEEP, GEQUAL 01/08 KEEP/RGB_ONLY | same family + **NEVER 0 ZB_ONLY** (Z-only), ALWAYS 80 KEEP | GEQUAL 7F, NEVER, ALWAYS | all four AFAIL modes appear except none missing |
| Destination alpha test | **DATE (pass Ad = 1)**: 3.9 M prims, 3.8 M px | DATE 5.8 k prims | DATE 1.8 k prims | needs the frame alpha bit |
| ALPHA (ABE 1) | 0x44 1394 M px, 0x48 371 M, 0x42 223 M, 0x58 52 M, 0x54 15 M, **0x64 FIX 0** 0.5 M prims, 0x24 FIX 0 (6) | 0x44 1322 M, 0x42 284 M, **0x52** 212 M, **0x54** 154 M, 0x48 | 0x44, 0x48 174 M, **0x6A FIX 0** 122 M, 0x58 69 M, 0x52/0x54, **0x68 FIX 0x80** | Cd and **Ad** as inputs, As up to 0x80+, FIX |
| COLCLAMP / PABE / FBA / DTHE / SCANMSK | 1 / 0 / 0 / 0 (1 on the CT16S target) / 0 | 1 / 0 / 0 / 0 / 0 | 1 (0 once in the boot clear) | dither only on the 16-bit target |
| SCISSOR | 0..639×0..447; 0..2047 (clear sprites, non-std XYOFFSET); 0..511×0..255 | + 0..127×0..127 | same | rectangle per draw |
| Texture PSM | **T8 + CT32 CLUT** 675 M px, **T4 + CT32 CLUT** 701 M, CT32 68 M, **CT16S** 9 M (the rendered target) | T8 847 M, T4 242 M, CT32 507 M | T8 788 M, T4 88 M, CT32 67 M | CSM1, CSA 0, **CLD 1 at every TEX0** (11 M CLUT loads in battle) |
| Texture size / TBW | 32²…1024×512, TBW 2–16 | same | same | |
| Filter | MMAG=MMIN=LINEAR MXL 0 (1444 M px), NEAREST (9 M) | LINEAR, NEAREST 166 M | + **LINEAR_MIPMAP_LINEAR MXL 2** (17 k px) | LOD only for one rare effect |
| Wrap | REPEAT, CLAMP, **REGION_CLAMP** | same | same | |
| TFX / TCC | MODULATE, TCC 1 (RGB-only TCC 0 for CT32) | same | same | |
| TEXA | TA0 0, AEM 0, TA1 0x80 (CT16S) | — | — | 16-bit expansion |
| Uploads (host→local) | CT32 1.9 M px, CT16 1.6 M px; PATH2 **and PATH3** | CT32 38.7 M, CT16 7.5 M | title CT32 109 M (backdrop), CT16 36 M | ~10⁵–10⁶ words per frame at worst |
| Local→host / local→local | **0 / 0** | 0 / 0 | 0 / 0 | no readback to keep coherent |
| SIGNAL / FINISH / LABEL | 0 | 0 | 0 | |
| EE reads of GS registers | **CSR only** (FIELD), ≈1.5/vblank | CSR | CSR | served by `GsPrivRegs`, independent of drawing |

Additional observations: textured draws whose texture footprint holds draw output (render-to-texture) occur in every
phase (field offscreen targets, battle CT16S target, menu effects); uploads into pages last written by a draw are
rare (≤ 452 pixels per segment — page-granular noise, e.g. a CLUT next to a target); textures never overlap the
frame buffer being drawn. The dorm route adds no feature outside this table (§1.1).

### 1.1 Dorm route

`census_dorm.txt` (segments 0–898 boot, 898–1898 title/menus, 1898–3000 and 3000–4000 opening movie/event,
4000–4900 dorm lobby event): **the only feature value not on the battle route is one texture size (64×256)**. Same
formats, PRIM types, blend/test combinations; 0 local→host, 0 local copies, 0 SIGNAL/FINISH/LABEL, CSR-only reads;
uploads up to 66.7 M qwords in the title segment (the streamed backdrop). Raster share of wall: boot 78 %, title
90 %, opening 92–94 %, dorm lobby 43 %.

## 2. Where the time goes, and the expected gain (obs/der)

Per segment of the battle-route census run (MSVC Release, this 8-core machine shared with three other agents, so
wall times are noisy; the *ratios* are what matter):

| Segment | vblanks | wall s | raster s | raster share | prims | pixels |
|---|---|---|---|---|---|---|
| boot (logo/movie) | 0–1064 | 11.6 | 9.6 | 83 % | 34 k | 553 M |
| title/menus | 1064–2000 | 83.5 | 57.9 | 69 % | 4.6 M | 1727 M |
| load + field | 2000–4614 | 256.7 | 140.2 | 55 % | 18.3 M | 4009 M |
| battle (transition → victory) | 4614–6150 | 187.3 | 102.6 | **55 %** | 11.3 M | 2933 M |
| results | 6150–6258 | 1.9 | 1.8 | 96 % | 9.6 k | 108 M |
| field | 6258–6700 | 44.0 | 21.2 | 48 % | 3.6 M | 652 M |

Independent sampling profile (draw-path agent, `22_rendering.md`, battle vblank 5750–6100): GS raster 55.1 %,
VU1 interpreter 34.5 %, soft-float 6.9 %, recompiled EE ~0.8 %; field 57.7 / 32.2 / 4.8 / ~1.3 %.

**Estimate.** With the D3D11 back end the EE thread keeps the GS front end (already in today's non-raster time) and
gains the op recording: measured at 7–10 ms per 16–19 k-primitive frame in `p3fes_gsreplay` (including a full
`GsCore` replay), i.e. ≈3–5 % of the rasterisation it replaces. The GPU work (≤ 21 ms exact, ≤ 6 ms interpolated
per 33 ms frame) runs on another thread and overlaps. So battle wall time goes from 1.0 to ≈ 0.45 + 0.55 × 0.04 ≈
**0.47 (≈2.1×)**, field ≈ **2.0×**, title ≈ 3×, results ≈ 10×. From the ~0.6× the lead measured on an idle machine
this alone reaches ≈1.2–1.3×; VU1 (34.5 %) is then the largest remaining cost — if the VU1 lane removes four fifths
of it, battle wall time falls to ≈ 0.19 of today (≈5×, i.e. ≈3× real time). The UI path (Im2D → VU1 programs
036–039, 100 % of the results screen, 24 % of battle batches per `22_rendering.md`) could additionally hand
screen-space quads straight to the back end's op list, skipping VU1 program 039.

## 3. Architecture (one page)

```
 EE fiber (guest timing, deterministic)                      Render thread (wall clock, may lag)
 ─────────────────────────────────────                      ───────────────────────────────────
 GIF PATH1/2/3 → GsCore (unchanged): registers, vertex
   queue + kick rules, TRXDIR/HWREG transfers into the
   CPU copy of local memory, CLUT logic, SIGNAL/FINISH/
   LABEL → GsPrivRegs (CSR, IMR, flip detection)
        │ IGsDrawObserver (new): on_draw / on_clut_load /
        │ on_transfer_pixel / on_local_copy / on_local_read
        ▼
 OpRecorder: draw batches (D3D vertices + PrimRec +           GpuGs: one 4 MiB RWByteAddressBuffer "VRAM"
   constant block, broken on state change), merged             (+ swizzle tables, CLUT buffer)
   transfer words, CLUT ops, copy ops                          for op in frame:
        │ frame = ops between two flips                            Draw   → VS + PS (GS pixel pipeline, ROV)
        └──── SPSC queue (double/triple buffered) ────────►        Scatter→ CS (masked word writes)
 flip event (DISPFB write) closes the frame                        Clut   → CS (reads VRAM)
                                                                   Copy   → CS in TRXPOS.DIR order
                                                               CRTC: PS composes DISPFB1/2 + PMODE from VRAM
                                                               → swap chain (present.h layout)
```

* **What stays on the EE fiber** is everything the guest can observe: register values, the GIF/VIF/DMAC timing,
  transfers into the CPU copy of local memory (so `read_image`, if it ever happens, is still served from CPU
  memory — see §5), CLUT buffer contents, privileged registers, flips. `GsCore::set_software_raster(false)` (new)
  turns off only the pixel writes; the core's CPU memory then holds uploads but not rendered pixels.
* **The render thread** owns D3D11 (immediate context, single thread). It consumes whole frames, never feeds
  anything back to the guest, and may drop frames when it falls behind (presentation only).
* **Batching.** Primitives with identical state go into one `Draw`. With ROVs (D3D11.3 `ROVsSupported`) overlapping
  pixels within a draw are serialised in primitive order, so a state run of a 16 k-primitive battle frame is ~200
  draws. Without ROVs a draw must not contain overlapping primitives: the 8×8-tile split gives ~14 k draws per
  battle frame and 60–125 ms GPU (obs) — not real time; such adapters fall back to the conventional render-target
  tier (§4 last row) or to the software path.
* **Presentation.** The CRTC (`gs::compose` today: two read circuits, PMODE ALP 0x80 flicker filter, DBY 1) becomes a
  full-screen pixel shader reading the VRAM UAV as an SRV, writing the swap-chain back buffer at any scale — the
  640×448 → window resample happens there. `HostDisplay`/`present.h` keep the letterbox policy.

## 4. Feature mapping

| GS feature (census) | D3D11 mapping in the UAV design | Exactness |
|---|---|---|
| Local memory, all PSM layouts | One raw 4 MiB buffer; frame/Z/texture/CLUT addresses computed in HLSL from `gs::swizzle_tables()` (uploaded once, 45,056 entries). Mid-page base pointers, aliasing (T8↔CT32, T4↔CT16), Z block XOR, 4 MiB wrap all fall out of the same arithmetic as `GsMemory` | exact (obs: 0 bytes) |
| Frame CT32 / CT24 / CT16(S), FBMSK | Store word (CT32) or masked atomic AND/OR (sub-word formats, FBMSK, RGB_ONLY), the same merges as `Raster::pixel` | exact |
| Z16S (and Z16/24/32) | Z read/test/write in the shader; 16-bit stores as masked atomics; Z interpolated from the GS vertices | exact with `--exact` (interpolated: identical on all frames too) |
| Coverage, pixel centres | Vertex = GS window coordinate (12.4, minus XYOFFSET) + ½ pixel, viewport (−4096, −4096) 8192², NDC = x / 4096: exact in float and on the rasterizer's 1/256 grid; D3D's top-left rule equals `Raster::triangle`'s; sprites as two triangles cover `[⌈x0⌉, ⌈x1⌉)` like `Raster::sprite`; scissor = D3D scissor rect | exact (obs: identical Z everywhere) |
| Gouraud / flat colour, fog, UV, Z, STQ | *Interpolated mode*: D3D `noperspective` attributes (flat = `nointerpolation`, the kicking vertex). *Exact mode*: per-pixel plane equations from the three GS vertices (`StructuredBuffer<PrimRec>[SV_PrimitiveID]`) with integer floor division in doubles, Z with the reciprocal area, STQ from the same double weights, `s/q` as a double division rounded to float (= IEEE float division) | interpolated: 43–67 dB; exact: bit-identical |
| Textures T8/T4 + CT32 CLUT (CSM1/CSM2, CSA), CT32/CT24/CT16(S), TEXA | Texel fetch = `read_px` + CLUT buffer lookup / 16-bit expansion in the shader; wrap modes REPEAT/CLAMP/REGION_CLAMP/REGION_REPEAT; bilinear with the GS's 1/16 integer weights; LOD/trilinear as `ref::sample` | exact |
| CLUT loads (CLD 0–5) | `GsCore::load_clut` decides *whether* to load (CBP0/CBP1 state stays on the EE thread); the load itself is a 256-thread compute shader reading VRAM, so a CLUT drawn by the GPU is still right | exact |
| Render-to-texture (offscreen FBP 480/488/496/504) | Nothing special: textures are read from the same buffer the draws write. D3D11 orders UAV accesses between draws | exact (obs: the three 128×128 targets identical) |
| TFX MODULATE (+DECAL/HIGHLIGHT/2), TCC | integer code | exact |
| Alpha test (8) + AFAIL (4), DATE/DATM | integer code; DATE reads the destination alpha bit of the frame word | exact |
| ALPHA A/B/C/D/FIX, As/Ad > 0x80, COLCLAMP, PABE, FBA | `(((A−B)·C) >> 7) + D` on integers with arithmetic shift, clamp or wrap, alpha write with FBA | exact |
| DTHE (16-bit target) | DIMX matrix in the constant block, added before the clamp | exact |
| Host→local transfers (PATH2/PATH3, CT32/CT16/…) | `GsCore` still unpacks the data (packing, RRW×RRH, HWREG); the observer turns each stored pixel into a (word, mask, value) and a compute shader applies the merged words before the next GPU op that could see them | exact |
| Local→local copies | Compute shader per copy in TRXPOS.DIR order (the tool round-trips through the CPU; 0 on these routes) | exact |
| Local→host (`sceGsExecStoreImage`, RW `SkyRasterLock`) | See §5: served from the CPU copy after a GPU→CPU sync of the source rectangle | exact if synced |
| Points, lines, AA1 | not used on either route; the front end counts them (`unsupported`); add as quads following `Raster::line/point` if a later census finds them | — |
| CRTC (PMODE/DISPFB/DISPLAY, flicker filter) | full-screen pixel shader over VRAM, `gs::compose` arithmetic | exact |
| Conventional tier (no ROV) | Render targets per frame-buffer layout (CT32 640×448 RGBA8, Z16S as R16_UINT), textures decoded from VRAM into SRVs with a page-hash cache, fixed blending where the equation allows (0x44/0x48/0x42 with As ≤ 0x80), shader blending with a copy of the target otherwise | approximate; only if a user's GPU lacks ROVs |

## 5. Coherence and the EE-visible behaviour that must stay byte-exact

* **Two copies of local memory.** The CPU copy (`GsCore::mem()`) receives every upload and nothing rendered; the
  GPU copy receives both. They agree everywhere except draw output. Because the EE never reads GS memory on these
  routes (0 local→host, §1) and no GS register value depends on pixels, the memory gates (`eeMemory.bin`) cannot
  see the difference.
* **If a readback happens** (RW's `SkyRasterLock` → `sceGsExecStoreImage`, the screenshot path in
  `kwlnRootUpdateShowRasterTask`, the camp-menu background capture if any): `on_local_read` is the sync point.
  The EE fiber blocks until the render thread has executed every op up to it, copies the source rectangle's pages
  GPU→CPU into `GsCore::mem()`, then the transfer proceeds from CPU memory as today. That stalls only that frame and
  keeps the bytes exact. The census probe reports any such event with its vblank.
* **Local→local copies whose source holds draw output** need the same order on the GPU (compute copy); the CPU copy
  is updated by `GsCore` from CPU memory as today (its result may differ in rendered areas, which nothing reads).
* **CLUTs loaded from rendered memory** (the probe saw CLUT blocks in pages last written by a draw: ≤ 12 k of 34 k
  loads per segment, page-granular) are loaded on the GPU from GPU memory, so they are right there; the CPU CLUT
  copy only matters for the software path.
* **Timing the guest can see:** FINISH/SIGNAL/LABEL are raised synchronously by `GsCore` from the register write,
  CSR.FIELD/VSINT come from the time base, GIF/VIF/DMAC stalls from the software model — none depends on the
  renderer, so guest timing is unchanged. (FINISH/SIGNAL are unused on these routes anyway.)
* **Determinism rule (ADR-0013 §4) holds:** the render thread reads only op lists; the guest never waits on the GPU
  except at a readback, where it waits for a *result* that is a pure function of the ops.

## 6. The software GS stays the oracle

* **Headless gates** (`--headless`, `--snapshot-at`, tracediff, the replay gates) run the software rasteriser by
  default; `--gs-backend d3d11 --gs-exact` (gate `-FastGs`, §12) is the opt-in exact GPU path, checked against the
  software references on every route. `frame.png` in headless snapshots is always the software CRTC (`gs::compose`)
  over GS memory.
* **Regression oracle for the GPU path:** `p3fes --gs-record FILE --gs-record-at V1,V2,…` records frames on any
  route (the file holds the core state + 4 MiB at both ends, so a replay is checked against itself first);
  `p3fes_gsreplay FILE --exact` must report `VRAM bytes differing 0`. Seven recorded frames do today. A ctest can
  replay a synthetic stream (`--synthetic`) without game data; game recordings stay gitignored.
* **Windowed play may use the interpolated mode** (faster, 43–67 dB vs the oracle, identical Z) or the exact mode
  (≤ 21 ms per frame here, still inside a 33 ms frame on a mid-range GPU).
* **Threading without changing guest timing:** the op list is recorded on the EE fiber during the frame; the flip
  event (DISPFB write in RW's vsync handler, `GsPrivRegs::dispfb_written`) closes it and pushes it to a lock-free
  single-producer/single-consumer queue; the render thread executes and presents. Back-pressure: at most two frames
  in flight; when the queue is full the EE fiber does *not* wait (that would make wall-clock timing visible) — the
  oldest queued frame's draws are kept but its present is skipped, or, simpler, the producer blocks only in windowed
  mode where pacing is wall-clock anyway (`Pacer`). Uploads inside a frame are copied into the op list's word array,
  so the producer never shares CPU memory with the renderer.

## 7. First step: replaying recorded frames on D3D11 (obs)

New pieces (all opt-in; the game host's default path is unchanged):

| Piece | What |
|---|---|
| `runtime/include/p3fes/gs/gs_core.h` | `IGsDrawObserver` (on_draw, on_clut_load, on_transfer_pixel, on_local_copy, on_local_read), `IGsStreamSink`, `GsCoreState` + `save_state/load_state`, `set_software_raster` |
| `runtime/{include/p3fes/gs,gs}/gs_stream.*` | `GsStreamRecorder` (start state + VRAM, every API call, end state + VRAM + display registers), `read_stream`, `replay_software` (self-check) |
| `runtime/app/gs_probe.*` | `--gs-census FILE [--gs-census-marks …]`, `--gs-record FILE --gs-record-at N[,N…]` |
| `runtime/gs/tools/gsreplay.cpp`, `gs_d3d11_shaders.h` | `p3fes_gsreplay`: software oracle, op recorder, D3D11 executor (ROV or split draws, interpolated or exact), comparison + PNGs |
| `tests/gs/test_gs_stream.cpp` | record → write → read → replay equals the live core (memory + state); observer changes nothing; raster-off draws nothing |

Results (RTX 3060, driver 32.0.16.1664; software timings on the shared machine; "differing" = whole 4 MiB):

| Frame (vblank) | Prims | Ops (draws / CLUT / scatters) | SW raster | GPU interp. | Interp. vs SW | GPU exact | Exact vs SW |
|---|---|---|---|---|---|---|---|
| title 1201 | 613 | 40 / 35 / 19 (806 k words) | 311 ms | 2.1 ms | FB 53.3 dB, Z =, CRTC 59.1 dB | 16.7 ms | **0 bytes** |
| field 3501 | 11,939 | 127 / 184 / 0 | 130 ms | 3.0 ms | 67.1 dB, Z = | 11.3 ms | **0 bytes** |
| battle 5001 | 19,841 | 200 / 242 / 12 | 131 ms | 4.9 ms | 53.9 dB, Z = | 13.7 ms | **0 bytes** |
| battle 5801 | 16,119 | 209 / 247 / 0 | 222 ms | 5.6 ms | 55.2 dB, Z =, CRTC 61.1 dB | 21.0 ms | **0 bytes** |
| results 6151 | 184 | 28 / 31 / 0 | 52 ms | 0.7 ms | 51.5 dB, Z = | 3.8 ms | **0 bytes** |
| field 6601 (+3 offscreen 128²) | 19,085 | 230 / 230 / 0 | 171 ms | 4.7 ms | 43.2 dB, 3 Z values ±2 | 15.6 ms | **0 bytes** |
| dorm 4851 (to_dorm) | 11,803 | 156 / 199 / 75 (313 k words) | 92 ms | 4.1 ms | 55.6 dB, 20 Z values differ (max \|d\| 65535: float interpolation crossing the Z clamp — not investigated, interpolated mode only), CRTC 61.8 dB | 10.4 ms | **0 bytes** |

* Front end (GsCore replay + op recording) 5–10 ms for the 12–20 k-primitive frames, 21–42 ms for the title frame
  with 806 k uploaded words (per-pixel transfer callbacks; a production path would scatter whole rows).
* Without ROVs (`--no-rov`) the same battle frame needs 14,444 draws: still exact, but 60 ms (interpolated) / 125 ms
  (exact) GPU. WARP supports ROVs but its exact-mode result differs (65 k bytes) — WARP is a functional fallback, not
  an oracle.
* Interpolated-mode differences are ±1 Gouraud/texture-coordinate rounding at near-integer plane values (diff
  images show triangle edges and text); max 8–17 per channel in the frame, 5–59 after the CRTC filter.
* Found while building it: refilling the same structured SRV buffers between two replays of a frame (UpdateSubresource
  into DEFAULT or Map(WRITE_DISCARD) of DYNAMIC) made the second replay read stale records/words on this driver,
  deterministically; fresh buffers per frame fix it. The production renderer should use a ring of buffers and be
  tested for repeatability the same way (`gsreplay` prints a warning when two runs differ).

## 8. The hard parts, ranked

1. **Throughput of the exact pipeline without ROVs.** ROV (D3D11.3, FL 11_0 + `ROVsSupported`; every NVIDIA
   Maxwell 2+, AMD RDNA, Intel Gen9+ driver exposes it) is what makes "VRAM as a UAV" real time. Without it the
   design degrades to many small draws (≈60–125 ms per battle frame) — needs the conventional tier or smarter
   batching (per-tile primitive lists). Risk: medium (depends on the user's GPU; RTX 3060 here is fine).
2. **Doubles for the exact mode.** Exact attribute evaluation uses `double` with the extended instructions (`ddiv`,
   `dtoi`): optional in D3D11 and slow on consumer GPUs (1/32–1/64 rate). 21 ms per battle frame on a 3060; weaker
   GPUs may need the interpolated mode. A 64-bit-integer emulation (two 32-bit words) could replace doubles. Risk:
   low for correctness, medium for speed on low-end GPUs.
3. **The render thread hand-off.** Op lists must be self-contained (upload words copied, vertex data owned), frames
   must be closed exactly at the flip, and back-pressure must never block the EE fiber in headless mode. Risk:
   medium (concurrency bugs), mitigated by `gsreplay`-style recordings of whole sessions.
4. **Upload volume.** The title backdrop streams ~806 k words per frame; per-pixel callbacks cost 20–40 ms on the
   EE thread. Needs a row/block-level transfer path in `GsCore` (memcpy of whole 32-bit rows, scatter only for
   swizzled sub-word formats). Risk: low.
5. **Readback sync** if a route ever uses `SkyRasterLock` (screenshot, camp capture): a GPU→CPU stall of one frame.
   Risk: low (not seen; the probe flags it).
6. **Features outside the census** (lines/points, PABE, FBA, SCANMSK, CSM2, MXL > 0 with LCM 0) are implemented in
   the shader from the reference but untested on game data; any new route must be re-censused (`--gs-census`).
7. **Interlace/CRTC** is already handled in `gs::compose`; on the GPU it is a straight port. Risk: low.

## 9. Plan

1. (done) census probe, stream recorder, `p3fes_gsreplay` with exact parity on recorded frames.
2. `GsCore` row-level transfer path and the op recorder as a library (`runtime/gs/gpu/`), with `IGsDrawObserver` as
   the boundary; unit test: synthetic stream replays exactly (ctest without game data, skips without a D3D11
   device).
3. Render thread + SPSC queue + CRTC pixel shader + `--renderer d3d11` in the windowed host; software stays default.
4. Session recordings (`--gs-record-at` many points) on both routes as the GPU regression set; parity report.
5. Conventional tier only if a target GPU lacks ROVs.
6. With the VU1 lane: an Im2D fast path that emits screen-space quads into the op list (skipping VU1 program 039).

## 11. As built: the windowed D3D11 renderer (2026-10-20, second step)

**GPU (this machine, obs):** NVIDIA GeForce RTX 3060, driver 32.0.16.1664, feature level 11_1, ROVsSupported yes,
DoublePrecisionFloatShaderOps yes, ExtendedDoublesShaderInstructions yes (`p3fes_gsreplay --synthetic --exact` prints
it; the host logs it at start).

**Mode.** Live play uses **interpolated attributes** (default): 0.7–5.6 ms of GPU per frame on the recorded frames,
43–67 dB against the software picture, Z identical. **Exact** (`--gs-exact`, doubles) is byte-identical to the
software rasteriser but 4–21 ms per frame and its render thread fell behind on the battle route (1,143 of 6,699 op
lists appended to a queued one, against 13 interpolated): it stays the regression mode (`p3fes_gsreplay --exact`,
`tests/gs/test_gs_gpu.cpp`).

**Architecture as built** (§3 made real):

| Piece | Where | What |
|---|---|---|
| Front end | `GsCore` (EE fiber) | unchanged registers/kick rules/transfers/CLUT logic; `set_software_raster(false)`; transfers report row spans (`on_transfer_span`, 32-bit data through a row loop) |
| Op recorder | `gs_ops.h` `GsOpRecorder` | draw batches per state run (triangles in GS window coordinates + per-triangle GS vertex records), transfer scatters (32-bit words with the bits uploaded, values from the CPU copy), **page records** for full-word (CT32/Z32) uploads (8 KiB page + 2048-bit "written" mask: the title's 730 k-word backdrop upload costs 9 ms instead of 42 ms on the EE side), CLUT loads, local copies |
| Hand-off | `GameHost::take_gpu_ops` → `GsD3D11Renderer::submit` | once per vblank slice of the host loop (between run slices, so no guest code runs concurrently), with the display registers of that moment; never waits: when 3 lists are queued the new one is appended to the last (`OpList::append`) |
| Render thread | `gs_d3d11.h` `GsD3D11Renderer` | owns its D3D11 device (hardware, FL 11_0, ROVs required), the window's flip-discard swap chain, a `GsD3D11Executor`: GS memory = one 4 MiB raw UAV, the pixel pipeline as a ROV pixel shader, transfer scatters / page uploads / CLUT loads as compute shaders, upload ring of 3 slots (DEFAULT buffers filled by a copy from per-slot staging buffers), the CRTC merge (`gs::compose`) as a compute pass into an RGBA8 texture, then a point/bilinear quad into the letterbox rectangle (`present.h` layout via `HostDisplay::on_layout`), `Present(vsync)`; when behind it skips presents but presents at least every 100 ms |
| Window | `HostDisplay` (`external_presenter`) | creates no device of its own; WM_SIZE → `set_view`; screenshots and snapshot `frame.png` / `--png` read the GPU picture back (`sync_frame`) |
| Shader cache | `%LOCALAPPDATA%\P3FES\shadercache` | compiled blobs keyed by source + entry + target + macros: first start 9 s (the ROV pixel shader), later starts 0.15 s |

**Fail-safes.** Every host-side wait on the render thread (start, `sync_vram`/`sync_frame`, stop) dispatches the
window's messages while it waits and has a timeout (60 s / 10 s / 3 s): the window never stops responding, and a
render thread stuck in the driver is detached instead of joined. No hardware device, no ROVs, a shader that does not
compile, or no successful `Present` within 5 s of the first submit → the log says why and the host switches to the
software rasteriser and its built-in presenter (`P3FES_D3D11_TEST_FAIL=start|present` exercises both paths; both
tested). Closing the window ends the process in ~2.6 s (measured with `CloseMainWindow`). `--gpu-debug` requests
the D3D11 debug device (Graphics Tools) in any build and prints its errors/warnings after every frame; it reported
none on the runs here.

**Cause of the frozen white window the user saw** (first windowed builds of this step; the freeze itself was not
reproduced here, the two defects below were found in the code and either one freezes the window): the host thread — which
owns the window — blocked on a plain condition-variable wait while the render thread created the device and the
window's swap chain (`start`), and again in `sync_frame` / `stop`. DXGI may send messages to the window during
swap-chain creation, so with the window thread not pumping, the two threads waited on each other: the window was
never painted (white) and showed "Not Responding". A second bug made it certain on some paths: after one
`sync_frame` (a screenshot, a snapshot's `frame.png`) the render thread waited for the host to "take" the result
on a predicate that a second request could never satisfy, so a second snapshot/`--png` hung the host thread forever.
Both are fixed (pumping, bounded waits; the sync request is served from the main wait predicate), and presents are
now guaranteed at least every 100 ms even while the renderer catches up.

**Driver note (obs, repeatable):** refilling a buffer that has a raw SRV with `Map(WRITE_DISCARD)` (DYNAMIC) or
`UpdateSubresource` (DEFAULT) made the GPU read stale/zero contents the next time the ring slot came round (no
debug-layer message); DEFAULT buffers filled with `CopySubresourceRegion` from a staging buffer are repeatable over
8 executions of the same list (gsreplay and `test_gs_gpu.cpp` check it). The vertex buffer (no view) is fine DYNAMIC.

**Determinism (obs).** A *windowed* d3d11 run of the dorm route (`--gs-backend d3d11 --unpaced --replay-input
config\inputs\to_dorm.txt --snapshot-at vblank:4900`) gives an `eeMemory.bin` with **0 differing bytes** against the
software gate reference (`tracediff snapshot … --dead-stack`), flips at the same vblanks (2,244 by vblank 4900); its
`frame.png` (the GPU picture, interpolated mode) is 56.5 dB from the software reference frame (max |d| 12).
Headless runs use the GPU only in the exact offscreen mode (§12).

**Speed (obs, battle route, windowed, `--unpaced`, MSVC Release; software and d3d11 run back to back on this
machine, which other agents share):**

| Segment (vblanks) | software | d3d11 (interpolated) | gain | fps software → d3d11 |
|---|---|---|---|---|
| title / menus 1100–2000 | 0.206× | 0.799× | 3.9× | 6.1 → 23.6 |
| field 3500–5300 | 0.170× | 0.412× | 2.4× | 5.0 → 12.3 |
| **battle 5300–6100** | **0.166×** | **0.394×** | **2.4×** | **4.9 → 11.8** |
| results + field 6200–6700 | 0.209× | 0.472× | 2.3× | 6.2 → 14.0 |
| whole route 0–6700 | 499 s (0.224×) | 189 s (0.592×) | 2.6× | |

Per battle vblank (zones): software GS raster 56.6 ms + VU1 36.5 ms + the rest ~6 ms; d3d11 GS (= op recording)
1.9 ms + VU1 35.1 ms + the rest ~5 ms. The VU1 interpreter is now ~83 % of a battle vblank; the GPU work (~1 ms
per vblank) runs on its own thread. An earlier pair of runs under heavier machine load gave 0.172× → 0.315× (exact
mode 0.292×) for the battle segment.

## 12. Headless exact back end: the gates' fast mode (2026-10-20, third step)

**What.** `p3fes --headless --gs-backend d3d11 --gs-exact` renders the GS on an **offscreen** `GsD3D11Renderer`
(`start(nullptr, …)`: hardware device, ROVs + doubles required, no swap chain, nothing presented) in exact mode.
Headless runs stay software by default (`auto` = software headless; `d3d11` without `--gs-exact` says why it stays
software); a device without ROVs/doubles, a shader that does not compile or `P3FES_D3D11_TEST_FAIL=start` → the log
says `gs-backend: software (d3d11 unavailable: …)` and the run continues on the software GS (tested).

**The EE side is the windowed one.** One run slice per vblank (`plan.every_vblank`, as windowed play has always run;
stop points and snapshot instants are unchanged because every stop is at VBLANK_START), the ops of the slice go to
the render thread with `submit` (never waits: up to 8 lists queue, later ones append), and the EE fiber waits for the
GPU only where its CPU copy of GS memory would matter:

| Sync point | What happens (all on the EE fiber; `GameHost::sync_gpu_memory`) |
|---|---|
| `--snapshot-at` / `--png` | take the open ops, submit, `sync_vram` (waits for every list, reads 4 MiB + the 512-entry CLUT buffer back, refuses a removed device), copy into `GsCore::mem()` + `set_clut`; then the **unchanged** snapshot code writes `gsMemory.bin` from the core and `frame.png` with the software CRTC (`gs::compose`) — so the picture is never the GPU's CRTC pass |
| local→host transfer (`GsOpRecorder::sync_hook`, `LocalRead`) | the same copy before `GsCore` serves the read from CPU memory (none on the routes; also active windowed) |
| point/line primitive (`Unsupported`) | headless only: the same copy, then `set_software_raster(true)` + observer off **from inside the hook**; `GsCore::draw_queue` then rasterises that primitive itself and the host stops the renderer after the slice ("software from vblank N on"). The CLUT readback matters here: the GPU loaded CLUTs from GPU memory, the CPU copy's CLUT may be stale (`test_gs_gpu.cpp` checks a CLUT loaded from drawn pixels). Windowed play keeps skipping such primitives |

After a sync the CPU copy equals GPU memory everywhere (it held the uploads; now also the draws), which is the state
the software GS would have had. A sync that fails (timeout 900 s headless, lost device) stops the run with exit 1
instead of writing a wrong snapshot.

**Byte identity (obs, MSVC Release fast build `--vu1 aot`, RTX 3060, driver 32.0.16.1664):** on all three gate
routes the fast run's `frame.png`, `eeMemory.bin` and `gsMemory.bin` are **byte-identical** to the software run's
(`cmp` of the raw files, not only `tracediff --dead-stack`) and to the references (dorm frame `EE0EB5DA…`, M1
`E3A93615…`, battle `CFAA5A61…`, 0 differing bytes; the references' `gsMemory.bin` also equal both). Run stats: dorm
4,900 lists (9 appended), battle 6,150 lists (1 appended), one GS memory sync per run (the snapshot).

**Speed (obs, routes one after the other, back to back on the shared machine, CPU load ~80 % from other agents):**

| Route | software | d3d11 exact | gain |
|---|---|---|---|
| dorm (vblank 4900) | 284.7 s (367.0 s in an earlier pair) | 44.0 s (46.8 s) | 6.5× (7.8×) |
| M1 (sky:11, vblank 380) | 2.4 s | 2.3 s | — (device start 0.35 s) |
| battle (vblank 6150) | 662.9 s (771.8 s) | 183.2 s (183.5 s) | 3.6× (4.2×) |

The fast battle route is ~30 ms per vblank of host time, now almost all VU1 + game code; the GPU work runs on the
render thread and never stalls the EE side (1 list appended in 6,150).

**What could make it diverge** (none seen): a GS feature outside the census that the HLSL implements but no route
has exercised (§8 item 6; the gates would show it as a frame/`gsMemory` difference, and `p3fes_gsreplay --exact`
on a `--gs-record` of that frame localises it); a driver change (the exact mode depends on IEEE double division and
ROV ordering — re-run `p3fes_gsreplay --exact` and the gates after a driver update); WARP or another adapter (WARP's
exact mode differs, §7: it is a functional fallback, not an oracle — the gate fails loudly rather than silently).
Local→local copies (none on the routes) go through a CPU round trip on the render thread; the write-back now uses
the staging buffer + `CopyResource` instead of `UpdateSubresource` (the §11 driver note), and `test_gs_gpu.cpp`
copies a drawn block and compares the whole 4 MiB.

**The gate script (`tools/ours/gate/gate.ps1`).** Besides `-FastGs`, three changes that cost nothing in exactness:
(1) the emitter (`recomp/src/emit_driver.cpp`) writes a generated unit only when its text changed and removes only
stale units — before, every gate run's emit rewrote all ~75 units and the MSVC build recompiled the whole program
(several minutes) even when nothing changed; (2) `p3fes_game_tests` ran twice per gate (inside ctest and again only
to print its counts): the counts now come from ctest's `LastTest.log`; (3) the three routes run as background
processes from the moment the MSVC build is done, overlapping the MSVC ctest (background) and the clang-cl
build + ctest (foreground); `-Serial` restores the old order. A failing suite now fails the gate (before, ctest's
exit code was ignored), each route also compares `gsMemory.bin` with the reference, and the bootstrap emitter is
the newest one (the first by name predated `--replace`). Whole-script wall time on a warm tree (no source change,
`-Jobs 3`, both compilers, back to back on the shared machine):

| Script | wall | where the time goes |
|---|---|---|
| before (a5e75de; emit rewrites every unit) | 1,708 s | full rebuild of the generated code, ctest MSVC, the game tests again, ctest clang-cl, three routes in series |
| after, software GS | 416 s | critical path: battle route 411 s (dorm 208 s, M1 2.5 s alongside); ctest MSVC 236 s, clang-cl 322 s overlapped |
| after, `-FastGs` | 253 s | critical path: clang-cl ctest 248 s (its Debug `p3fes_game_tests`); battle 137 s, dorm 35 s, M1 6 s |

The final pair on the committed code, under heavier load from other agents: software 441 s (battle 434 s), `-FastGs`
385 s (clang-cl ctest 381 s; battle 202 s, dorm 35 s). In that fast run the render thread fell behind on the dorm
route (2,838 of 4,900 lists appended to a queued one) and the snapshots were still byte-identical to the software
run's — list boundaries do not matter to the result.
With `-FastGs` the replay gates are no longer the critical path: the clang-cl Debug pair tests are (one test case,
`game(battle_calc): the unit / weapon / skill helpers…`, is 107 s of the 231 s MSVC run). Sharding the game tests
or a clang-cl Release suite tree would be the next cut; not done here (the tests are other slices' files).

**The suite cut (2026-10-20, fourth step; `tools/ours/gate/gate.ps1`, `tests/game`).** Three changes, no assertion
dropped (254 cases / 36,264,899 assertions before and after, on both compilers):
(1) *Where the time went:* not the bodies but the pair protocol around them. `battle_calc` / `battle_rest` /
`script_comm_a` copied a 2–4 MiB data window three times and compared it per pair (`script_comm_a` into fresh
vectors: soft page faults); `render_rw2`'s hardware pairs copied all 32 MiB of RAM five times and compared it
byte by byte; `render_game` restored and compared 32 MiB twice. `PairRange` (`tests/game/write_tracker.h`) does
the same snapshot / restore / first-difference on page-granular write tracking (the pages read-only, a vectored
exception handler keeps a page's bytes at its first write): exact, since a page nobody wrote holds the starting
bytes after both bodies; checked against the full-copy protocol on 3,000 random pairs (MSVC and clang-cl) and with planted
differences (every planted byte reported, at its address). `run_pair_hw` uses it for ranges of 1 MiB and more;
the byte walks of the other comparisons start with a `memcmp`. MSVC Release, one process: `battle_calc` 169 s →
~3–10 s, `render_rw2` 245 → 24 s, `script_comm_a` 41 → 2.4 s, `render_game` 50 → 23 s.
(2) `p3fes_game_tests` is one ctest entry per test file (`--source-file`, option `P3FES_GAME_TESTS_SHARDED`,
COST hints for a fresh tree); the gate adds up the doctest summaries and checks them against `--count`.
(3) The gate's clang-cl tree is Release (preset `clangcl-x64-release`): the second compiler's optimised codegen.
clang-cl numbers on the new code, `-j 3`: Debug cold build 172 s, suites 252 s wall (game-test entries 680 s
summed); Release cold build 207 s, suites 46 s wall (125 s summed); every suite passes on both.
Gate, same trees, `-FastGs -Jobs 3`, shared machine: before 1,902 s (cold, incl. 403 s MSVC + 172 s clang builds;
ctest MSVC 411 s, clang-cl Debug 1,270 s) and 2,343 s warm (ctest MSVC 674 s, clang-cl Debug 2,336 s, heavier
load); after 265 s with the one-time clang-cl Debug → Release rebuild (210 s; ctest MSVC 58 s, clang-cl 48 s) and
257 s warm (ctest MSVC 71 s and clang-cl 68 s, both overlapping the routes; battle route 252 s under that load).
The battle route is the critical path again; the suites finish in a quarter of its time.

## 10. Reproduce

```
p3fes --memcard …\tartarus.ps2 --replay-input config\inputs\to_battle.txt --headless --quiet --frames 6700 ^
      --gs-census census.txt --gs-census-marks 1064,2000,3000,3500,4000,4614,5000,5400,5800,6000,6150,6258,6400 ^
      --gs-record rec\frame.p3gs --gs-record-at 3500,5000,5800,6150,6600
p3fes_gsreplay rec\frame_v5800.p3gs [--exact] [--no-rov] [--warp] --out cmp_dir
p3fes_gsreplay --synthetic --exact
```

## 13. Fast front end (2026-10-25, graphics team track D)

The user's order (2026-10-25): a locked 30 fps everywhere, graphics ~10x cheaper. Track D is the CPU cost from GIF
packets to the GPU and the GPU cost of the GS emulation. Exactness rules unchanged: the headless exact path
(`--headless --gs-backend d3d11 --gs-exact`, the gates' `-FastGs`) stays byte-identical to the software GS; windowed
play (interpolated) is unchanged picture for picture by everything below (the interpolated output of every recorded
frame is identical to the one before the change, same pixel counts and PSNR against the exact picture).

### 13.1 The front end's input interface (for tracks B and C)

Everything the GS front end consumes enters through four `GsCore` calls, in GS order; nothing else is needed and
nothing is global:

| Call | Semantics |
|---|---|
| `write_reg(reg, value)` | A+D / REGLIST register write (64-bit value) |
| `write_packed(desc, qword)` | PACKED register write (GIF tag register descriptor 0x0-0xF) |
| `on_gif_tag()` | a GIF tag was read (resets the internal Q to 1.0) |
| `write_image(qwords)` / `write_hwreg(value)` | IMAGE data / HWREG for a host -> local transfer |

`Gif::feed` is only the tag walker over these: PACKED data now runs in one tight loop per tag (`gif.cpp`). A producer
that already knows the register sequence (track B's VU1 fast path emitting primitives without serialising GIF
packets) may call `write_packed` / `write_reg` directly with the same values in the same order; the result (GS state,
op lists, CPU copy of GS memory) is then identical by construction. It must still keep the GIF's own guest-visible
state (path ownership, `GifStats`, which feed capture.json) the way `Gif::feed` would.

Thread-agnostic: `GsCore`, `GsOpRecorder`, `OpList`, `Gif` and `Vif1` keep all state in their objects (the only
process-wide object they touch is the zone profiler, `p3fes/prof.h`, which track C makes per-thread). A consumer on
another thread owns the GsCore + recorder pair; the hand-off unit stays the `OpList` (self-contained, movable).

`GsCore::state_generation()` (new) changes on every register write except RGBAQ / ST / UV / FOG / XYZ* and on
reset / load_state / a machine-state load: an observer may keep anything it derived from the draw state while the
value is unchanged.

### 13.2 What changed on the CPU side

| Where | Before | Now |
|---|---|---|
| `GsOpRecorder::on_draw` | per primitive: `decode_draw_state` (full register decode, 7 mip levels), a 400-byte `GpuDrawCB` built and `memcmp`'d against the open draw, 3 x 52-byte vertices + a 128-byte `GpuPrimRec` per triangle | decode + constant block only when `state_generation()` changed; 3 x 40-byte vertices; `GpuPrimRec`s only in exact mode (only the exact pixel shader reads them) |
| `GpuVertex` | 13 floats/ints, 52 bytes | 40 bytes: colour RGBA8, UV 2 x u16, fog u32, CLUT version; the vertex shader widens to float (exact, all values < 2^24), so interpolation is unchanged |
| OpList storage | a fresh list every vblank: every array regrows from zero (memmove + VirtualAlloc/Free ~7 % of the game thread per T0's sampler) | `GsD3D11Renderer::recycle` returns executed lists; the recorder continues in their storage |
| CLUT loads | every load a GPU compute dispatch between draws (~250 per battle frame), each closing the draw | loads whose source cannot hold draw output are resolved on the CPU into CLUT versions (13.3); the draw continues |
| GS census observer | `std::string` keys built per state-register write | memoised per register (last value -> counter) |
| GIF PACKED | one outer-loop iteration per qword | one tight loop per tag |
| VIF1 UNPACK / MPG | payload words pushed one by one into a vector, then a generic bit-extracting unpack | the payload straight from the DMA stream when complete (else gathered in bulk); unmasked, non-filling byte-aligned formats in specialised loops (`vif_unpack`, generic path kept for masks, filling writes and V4-5) |

### 13.3 CLUT versions

`GsCore::load_clut` loads the CLUT buffer from the CPU copy of GS memory, which holds every upload but no draw
output. The recorder tracks, per 8 KiB page, the sequence number of the last draw that may have written it (frame and,
when written, Z rows of each draw's bounding box) and, per word, the sequence number of the last full-word upload.
A load is *clean* when every source word is in a page never drawn, or (32-bit CLUTs) was uploaded after the page's
last draw: then GsCore's CPU result is exactly what the GPU would load. Clean loads become CLUT versions
(`OpList::clut_tab`, 512 u32 per version: the slots written since the list started or since its last GPU load,
`kClutInherit` for the rest); the draw state block names the version its primitives read (`GpuDrawCB::clut_ver`,
`kClutLive` = the GPU CLUT buffer). A load that is not clean is a GPU load (`Clut` op) preceded by a `ClutResolve`
that writes the current version into the GPU CLUT buffer; later versions inherit from the buffer as that load leaves
it. A list that ends on a version ends with a `ClutResolve`, so the GPU CLUT buffer (read back by `sync_vram`) is
always the software model's. Draw marks use the pixel rows a primitive can write (pixel centres, the scissor), not
the bounding box margin: a full-screen draw no longer marks the page after its buffer (where this game keeps CLUTs). `P3FES_GS_GPU_CLUT=1` turns the CPU path off (diagnostics). `test_gs_gpu.cpp` covers both paths
(a clean upload-only CLUT and a CLUT drawn over by a sprite).

### 13.4 Merged draw calls (the GPU side)

D3D11 makes every draw call that writes a UAV wait for the previous one (an implicit UAV barrier), so a frame of
~200 state runs plus ~250 CLUT dispatches was ~450 serialised GPU steps. Inside one draw call the ROV already orders
every access to the same pixel in primitive order, so consecutive draws can share one call when that is all the
ordering they need:

* the recorder marks a Draw op `merge` when the op before it is a Draw with the same frame and Z buffers (FBP, FBW,
  PSM, ZBP, ZPSM: then all frame / Z traffic is same-pixel and ROV-ordered) and no texture of the run reads a page
  that a draw of the run writes (8 KiB page sets: frame / Z rows of each draw's pixel bounding box, texture extents
  of every mip level in use, region modes widened); a draw that samples what it draws starts no run;
* every vertex carries its draw state index (`GpuVertex::cbi`); the pixel shader reads the state from
  `cbuffer Draw { DrawCB dcb[128]; }` (the executor binds 128 consecutive 512-byte blocks of the list's one constant
  buffer at an offset, D3D11.1) and tests the draw's own scissor (the call's hardware scissor is the union);
* CLUT versions (13.3) put the CLUT into the state block, so a CLUT load no longer splits the run.

Without ROVs or constant-buffer offsets every Draw op stays its own call (the old behaviour). The exact mode's
`GpuPrimRec` index is `g_prim_base + SV_PrimitiveID` (the call's first record from `cbuffer Group`).

### 13.5 Numbers (2026-10-25, RTX 3060, machine shared with ~8 agents: CPU 100 % busy, GPU contended)

`p3fes_gsreplay` on recorded frames, best of 5-9, before (main 4709fee) / after; front end = GsCore + recorder CPU
per game frame (recycled list storage), GPU = timestamps, interpolated mode:

| Frame | front end ms | GPU ms | draw calls | CLUT GPU loads |
|---|---|---|---|---|
| battle 5800 (16 k prims) | 10.8 / 2.9 | 5.3 / 2.4 | 209 / 4 | 247 / 0 |
| field 3500 | 10.6 / 1.9-2.6 | 3.4 / 0.8 | 127 / 3 | 184 / 0 |
| field 6600 | 12.8 / 3.5 | 4.6 / 1.2 | 230 / 6 | 230 / 0 |
| title (730 k uploaded words) | 28.3 / 12.2 | 2.1 / 1.8 | 40 / 18 | 35 / 0 |
| dorm | 23.9 / 9.5 | 4.1 / 2.6 | 156 / 65 | 199 / 0 |

Exact mode GPU on the battle frame: 51 -> 15-19 ms (same load). Windowed battle route, same-load A/B (`--zones`):
gif + gs_raster + gs_upload + gs_submit per vblank battle 5.4 -> 1.5 ms, field 9.6 -> 3.3, title 16.0 -> 9.2;
VIF1 roughly 2.5x lower. Interpolated pictures are identical to before on all 10 recorded frames (title, dorm,
battle x5, fusion x2, shop: CRTC 49-72 dB vs the exact picture, unchanged); exact mode 0 bytes on all of them; the
gate's six routes byte-identical.

`GsD3D11Renderer::stop()` always joins the render thread now (it detached it after 3 s, and the detached thread used
the destroyed renderer: a use-after-free on a loaded machine); the window keeps pumping messages while it waits.
