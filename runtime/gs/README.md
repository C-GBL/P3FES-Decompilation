# GS, GIF, VIF1 (`p3fes_gs`)

The Graphics Synthesizer as a software rasteriser into 4 MiB of local memory, its privileged registers, the GIF
with PATH1/2/3, VIF1 (PATH2 + VU1 micro-program upload and start), the DMAC channel 1/2 data paths, and the CRTC
composition of the displayed picture. D3D11 only presents the composed frame
(`runtime/src/gs/d3d11_backend.cpp`). Sources: `runtime/gs/`; headers: `runtime/include/p3fes/gs/`; tests:
`tests/gs/`. Game-side facts come from `docs/ANALYSIS/10_frame_loop_gs.md` and `14_vu1_gs_census.md`; register
definitions from the GS / EE User's Manuals. Provenance of ported parts: `runtime/include/p3fes/gs/THIRD_PARTY.md`.
Tags below: **obs** observed, **der** derived, **inf** inferred.

## Architecture

```
 VU1 XGKICK ──PATH1──┐                                       ┌─ GsMemory (4 MiB, swizzled)
 VIF1 DIRECT ─PATH2──┼─> Gif (tags, arbitration) ──> GsCore ─┤   registers, vertex queue, CLUT buffer,
 DMAC ch2 ────PATH3──┘        GIF_* registers                └─ transfers; rasteriser (gs_raster.cpp)
 DMAC ch1 / VIF1 FIFO ──> Vif1 (VIFcodes, UNPACK, MPG, MSCAL ──> VU1Interpreter (runtime/vu1))
 0x12000000.. ──> GsPrivRegs (PMODE..BGCOLOR, CSR, IMR, BUSDIR, SIGLBLID, flip counter) ──> compose() ──> Frame
```

| File | Owns |
|---|---|
| `gs_mem.{h,cpp}` | `GsMemory`: 4 MiB, page/block/column address mapping for the 13 PSMs, raw pixel read/write |
| `gs_core.{h,cpp}` | `GsCore`: all 54 general-purpose registers (A+D/REGLIST and PACKED forms), vertex queue and kick rules, CLUT buffer + CLD logic, host↔local and local↔local transfers, SIGNAL/FINISH/LABEL events |
| `gs_raster.{h,cpp}` | decoded per-primitive state and the pixel pipeline (private header); the fast implementation |
| `gs_raster_ref.cpp` | the reference pixel pipeline (`detail::ref`): one generic operation per pixel, the pre-optimisation code kept as the oracle of the fast paths and their fallback for unspecialised texture states |
| `gs_priv.{h,cpp}` | `GsPrivRegs` (`HwDevice` on `0x12000000–0x12001FFF`): 19 privileged registers, CSR from the time base, GS interrupt, flip detection |
| `gif.{h,cpp}` | `Gif` (tags, PATH1/2/3, arbitration, `GIF_*` registers), `GifRegsDevice`, `GifFifoDevice`, `GifDmaHandler` (ch2) |
| `vif1.{h,cpp}` | `Vif1` (VIFcode stream machine), `Vif1RegsDevice`, `Vif1FifoDevice`, `Vif1DmaHandler` (ch1), `Vif0StubDevice` + `Vif0DmaTrap` |
| `gs_output.{h,cpp}` | `compose()` (CRTC), PNG writer, `frame_hash`, `resample_bilinear`, `diff_frames` |
| `gs_system.{h,cpp}` | `GsSystem`: owns everything above + the `VU1Interpreter`; `attach(HwBus&)` |
| `gif_builder.h`, `gs_selftest.{h,cpp}` | packet builder for tests; the synthetic scene `p3fes --smoke/--headless` draw |
| `tools/gscmp.cpp` | `p3fes_gscmp`: PNG vs reference screenshot (WIC decoding), tolerance report |

Everything is synchronous and single-threaded (ADR-0013 §1/§3): a vertex kick rasterises before the register
write returns, `MSCAL` runs VU1 to `E` inside the VIF call, a DMA transfer handed to a handler is consumed (or
refused) before it returns. No wall clock is read; output is a pure function of the inputs.

## Integration for the lead (kernel/DMAC owner and host)

* **Bus.** `GsSystem::attach(bus)` maps (physical, [begin, end)): GIF registers `0x10003000–0x100030B0`; VIF0
  registers `0x10003800–0x10003980` (accepted: the game resets VIF0 and ORs `VIF0_ERR`, B-42/B-55); VIF1
  registers `0x10003C00–0x10003D80` (the brief said `…3C70`; the block includes R0–R3/C0–C3 at `+0x100…+0x170`);
  VIF0 FIFO `0x10004000–0x10004010` (traps); VIF1 FIFO `0x10005000–0x10005010` (128-bit; Q-02's `sq` target is
  served either way); GIF FIFO `0x10006000–0x10006010`; GS privileged `0x12000000–0x12002000` (64-bit native,
  32-bit halves supported). It installs DMA handlers 0 (trap), 1 (`Vif1DmaHandler`), 2 (`GifDmaHandler`).
* **DMAC channel 1.** `transfer(data, qwc, tag)` consumes VIF stream qwords; fewer than `qwc` = stalled (GIF busy
  for PATH2, interrupt bit, FBRST STP/FBK); re-offer the rest at the next `service()`. Words of a partly consumed
  qword are kept inside the VIF, so returned counts are always whole qwords. **TTE**: when `CHCR.TTE = 1`, pass
  the tag qword first as a one-qword transfer with its lower 64 bits zeroed (two VIF NOPs; the upper half carries
  the VIFcodes, e.g. RW's `ret` packets `tag | NOP | MPG` and texture `ref` tags `NOP | DIRECT`). **Direction**:
  with GS `BUSDIR = 1` (`sceGsExecStoreImage`, D1 `CHCR.DIR = 0`) the handler *fills* `data` from the GS
  (local → host) and returns `qwc`.
* **DMAC channel 2 (PATH3).** Returns 0 while PATH3 is masked at a packet boundary (VIF `MSKPATH3` or
  `GIF_MODE.M3R`), while another path owns the GIF mid-packet, or when it yields to a waiting PATH2. Re-offer later;
  `GsSystem::set_path3_ready_callback` fires when a mask clears with channel 2 stalled (the RW queue type 0x21
  flow: FIFO `MSKPATH3 on` → D2 kicked and stalled → D1 image upload ending in `MSKPATH3 off` → D2 runs).
* **Interrupts.** `raise_intc(0)` for SIGNAL/FINISH when `IMR` unmasks them (the game masks all: `GsPutIMR(0xFF00)`);
  `raise_intc(5)` for a VIFcode with the interrupt bit (not used by the game per `14` §3). VSINT/HSINT are flags only.
* **Time.** `CSR.FIELD = bus.time().field` (bit 13; `kwlnVsyncFieldGate` and `_rwDMAVSYNCHandler` read it);
  `NFIELD` is modelled equal (unverified); `VSINT`/`HSINT` are set when `time().vblanks`/`hlines` advanced since
  their last W1C.
* **Flip counter** (ADR-0013 §4): `GsSystem::flip_count()`, `GsPrivRegs::last_flip()`, `set_flip_callback()`.
  A DISPFB1/2 write that changes that circuit's FBP, or the first DISPFB write after an SMODE2 write, is an event;
  events in the same `time().vblanks` interval coalesce. For this game: flip 1 = `SkyStart`'s
  `sceGsSwapDBuffDc → sceGsPutDispEnv` (FBP 0, B-54); every executed RW flip in `_rwDMAVSYNCHandler` (B-64) is
  one more. PCSX2's `first_flip` capture point ("first executed flip after `g_skyFrameCount ≥ 2`") therefore
  corresponds to flip ≥ 2 here; hook the count the harness wants.
* **Host.** `compose_output()` gives the woven 640×448 RGBA frame; `write_png()`; `p3fes --headless --png f.png`;
  `p3fes_gscmp ours.png extracted\_pcsx2\<point>\Screenshot.png --tolerance N --diff d.png` (resamples 640×448 to
  PCSX2's 640×480).
* **Not mine, needed by the game:** `VPU_STAT ($vi29)` bit 8 (VU1 busy) must read 0 (VU1 never runs concurrently);
  `ctc2 $vi28` (FBRST) bit 9 (VU1 reset, `FBRST |= 0x200` in B-42/B-43) should call `GsSystem::vu1().reset()` —
  both are COP2 control registers on the rt/VU0 side. Wired (integration): `cfc2 $vi29` reads 0 in the adapter;
  `ctc2 $vi28` reaches `RtHooks::vu_control_write` → `Kernel::set_vu_control_handler` → the host resets VU1 on
  bit 9 (runtime/app/game_host.cpp); VIF/VU traps go to `RtHooks::fatal`.
* **Diagnostics.** `GsCore::set_reg_observer(fn(reg, value))` sees every PRIM and state-register write (TEX0 and up,
  not RGBAQ/ST/UV/XYZ/FOG) before it takes effect; the host's GS census (`capture.json` `gs_census`) is built on it.
* **Draw observer, stream recorder, GPU experiments** (`docs/ANALYSIS/25_d3d11_gs_backend.md`).
  `GsCore::set_draw_observer(IGsDrawObserver*)` reports every kicked primitive (register file + queued vertices,
  pixels written, raster nanoseconds), CLUT loads, transfer spans (one call per contiguous run of a row; 32-bit
  data goes through a row loop, `image32`), local copies and local→host starts;
  `set_stream_sink(IGsStreamSink*)` sees the API calls (`gs_stream.h`: `GsStreamRecorder` writes a replayable
  one-frame file with the core state and 4 MiB at both ends, `replay_software` checks it); `set_software_raster(false)`
  leaves only the observer to draw. All default off (one pointer test per call). Host options `--gs-census` and
  `--gs-record` (`runtime/app/gs_probe.*`); `p3fes_gsreplay` replays a recording through this core and through the
  D3D11 back end and compares the memories (bit-identical with `--exact`). `GsPrivStats::reads[]` counts EE reads
  per privileged register.
* **D3D11 back end (windowed play).** `gs_ops.h`: `GsOpRecorder` (an observer) turns the core's work with
  rasterisation off into `OpList`s (draw batches + GS vertex records, transfer scatters with the bits written,
  CLUT loads, local copies); `gs_d3d11.h` (library `p3fes_gs_d3d11`): `GsD3D11Executor` runs them with GS local
  memory as one 4 MiB GPU buffer (pixel pipeline in `gs_d3d11_hlsl.h`, CRTC merge as a compute pass) and
  `GsD3D11Renderer` is the render thread with the window's swap chain. The host submits one list per vblank slice
  (`p3fes --gs-backend d3d11|auto`). Headless runs use it only when asked for `--gs-backend d3d11 --gs-exact`:
  the renderer then runs offscreen (no window, no swap chain; `start(nullptr, …)`), the EE side is the windowed
  one, and snapshots sync GPU memory and the CLUT buffer back into the core (`GameHost::sync_gpu_memory`), so
  `gsMemory.bin` and `frame.png` (the software CRTC over that memory) are byte-identical to the software GS — the
  gates' `-FastGs` mode. The recorder's `sync_hook` makes the core exact at the two places its CPU copy would
  matter: a local→host transfer (memory synced first) and a primitive the GPU path cannot draw (points/lines: memory
  + CLUT synced, `set_software_raster(true)` from inside the hook, the core draws it and everything after). Design
  and measurements: `docs/ANALYSIS/25_d3d11_gs_backend.md` §11, §12.
* **Traps (fail closed).** `GsSystem::set_trap_handler` receives `VifTrap` {invalid VIFcode, invalid UNPACK
  format, VU1 trap (with the interpreter's `vu1::Trap`), VU1 step limit, VIF0 data}. Default: one line on stderr.
  Route it to `rt::trap`.
* **Threaded pipeline** (`p3fes/gs/gs_pipeline.h`, `GsSystem::start_pipeline`, `p3fes --gs-threads 2|1|0|off`,
  default 2). VIF1 hands UNPACK / MPG / MSCAL-MSCNT to a VU1 worker and the GIF hands its PATH2/PATH3 GsCore calls
  to a GS worker (through the VU1 worker, in order); the EE keeps VIF1/GIF arbitration, the registers and the
  DMAC. CSR / SIGLBLID / IMR accesses wait for the VU1 worker; local -> host reads, CSR.RESET and the host
  (`GsSystem::quiesce`) wait for both. Results are the synchronous model's (`tests/gs/test_gs_pipeline.cpp`, the
  gates). With the pipeline on, touch `core()`, `vu1()` and GS memory from the host only after `quiesce()`; the
  D3D11 op lists go out at vblank markers (`GameHost::end_vblank_slice`). Design, sync rules, measurements:
  `docs/ANALYSIS/32_threaded_graphics.md`.

## Revision (contract Q-03 / H-23)

`CSR.ID = 0x55`, `CSR.REV = 0x1B` (`kGsId`, `kGsRevision` in `gs_priv.h`). **obs:** `sceGsResetGraph 0x4F8EB0`
stores `CSR[23:16]` with `sh v0,6(s0)` @`0x4F8F58` into GParam (`0x77F280`, from `sceGsGetGParam 0x4F9040`), and
PCSX2 2.8.2's `first_flip` `eeMemory.bin` holds `0x001B` at `0x77F286` — the revision PCSX2 reports. Choosing the
same value keeps GParam byte-identical for `tracediff`.

**Consequence for Q-03 / H-23 / B-49: none for this game's mode.** The same PCSX2 states hold
`DISPLAY2 = 0x001BE9FF0183227C` / `DISPLAY1 = 0x001BF9FF0183227C` in both display envs (`0x964990+0x18`,
`0x9649B8+0x18`, circuit-1 copies `0x964CC8/0x964CD8`; first_flip, atlus_logo and title_runA identical) — DX 636,
a zero offset — and the code explains why (obs, disassembly of `sceGsSetDefDispEnv 0x4F9168`): it loads the GParam
mode (`lhu a0,2(s1)` @`0x4F91C0`), and for mode 2 or 3 (NTSC/PAL; `addiu -2; sltiu 2` @`0x4F91C4–C8`) the
`bnezl` @`0x4F91CC` goes straight to zeroing the four offsets (`0x4F9204–0x4F9210`); `checkModelVersion 0x4F90B8`
and `_GetGsDxDyOffset` (syscall 0x80 via `0x4F9158`, call @`0x4F91F0`) are reached only for other modes. So the
revision does not reach DX/DY here and B-49's "report an early model" is not needed for NTSC; topic 15 §6's
revision rule (`0x8000D2C0`) only matters for non-NTSC/PAL modes.

## Paths (arbitration model)

A path owns the GIF from the first tag of a packet to the end of the data of its EOP tag and is never interrupted
inside it. While owned: PATH2/PATH3 calls consume nothing (VIF sets `VGW`/`GIF_STAT.P2Q`; channel 2 `P3Q`, `FQC`
= min(16, offered) — **inf**), PATH1 packets (complete, copied by the VU1 interpreter up to EOP) are queued
(`P1Q`). At every packet boundary (a GS packet = through its EOP tag): queued PATH1 packets run first; PATH3 stops if
masked (`M3P`/`M3R`) and yields to a waiting PATH2 (after asking the VIF to retry its FIFO backlog). **Unmask window**
(2026-10-19): when VIF1's `MSKPATH3 off` clears the mask with channel 2 stalled, `GsSystem` opens a window around its
path3-ready callback (the host calls `Kernel::retry_dma_now(2)` there) in which PATH3 transfers exactly one GS packet
and then stalls (`P3Q`, `GifStats::path3_window_stops`) until the DMAC retries it. That is what the hardware does with
RenderWare's texture sync packet (`MSKPATH3 off`, ~96 NOPs, `MSKPATH3 on`, `FLUSHA`, TEX0 + draw): the next texture
pair goes through, the mask takes effect at its EOP, and the draw that follows samples it — while the *next* upload of
the same chain may already reuse that VRAM (`docs/INTEGRATION_LOG.md` "Title fix"). `GIF_STAT.APATH`/`OPH` report the owner — 0
when idle, which is what `sceGsSyncPath` (`GIF_STAT & 0xC00`) and RW (`GIF_STAT & 2` = M3P) poll (obs, `10` §2.6,
§3.1). `FLUSHE`/`FLUSH` have nothing to wait for (VU1 finished inside MSCAL; PATH1 output is complete or queued);
`FLUSHA` waits for the end of the PATH3 transfer (`Gif::path3_pending`: PATH3 owns the GIF mid-packet, PATH3 data
is stalled in the GIF by a mask or a yield, or DMAC channel 2 is still running — `D2_CHCR.STR`, read through the
bus, stays set from the kick to the DMAC's completion event). Before 2026-10-19 it waited only for the mid-packet
case, which let PATH2 draw packets overtake the PATH3 texture uploads they depend on: the title screen drew with
CLUTs and T4 atlases that the *next* upload had already overwritten (`docs/INTEGRATION_LOG.md` "Title fix").
`MSCALF` = `MSCAL`; `DIRECTHL` = `DIRECT` (no PATH3 IMAGE interruption exists to wait for). IMT (intermittent PATH3) is stored and reported, not modelled. Every GIF
tag resets the internal Q to 1.0; PRE applies to PACKED tags only.

## Coverage against the census

| Set | Census (contract §5, `14` §3–4) | Implemented |
|---|---|---|
| GS general registers | 31 named (H-31: PRIM, RGBAQ, XYZ2, XYOFFSET_1, PRMODECONT, TEXA, SCISSOR_1, ALPHA_1, DTHE, COLCLAMP, TEST_1, FRAME_1, ZBUF_1 + FRAME/ZBUF/XYOFFSET/SCISSOR/TEST `_2`; H-32: TEX0_1, TEX1_1, CLAMP_1, FOGCOL, DIMX, TEXFLUSH, BITBLTBUF, TRXPOS, TRXREG, TRXDIR, ST, UV, XYZF2) + NOP 0x7F | all **54** defined registers + 0x7F (adds XYZF3/XYZ3, FOG, TEX2, PRMODE, TEXCLUT, SCANMSK, MIPTBP1/2, PABE, FBA, HWREG, SIGNAL, FINISH, LABEL, all `_2`); undefined ids counted (`unknown_reg_writes`) |
| PACKED descriptors | A+D, PRIM-via-tag, RGBAQ/ST/UV/XYZF2/XYZ2 from xgkick | all 15 (0x0–0xA, 0xC–0xF; 0xB reserved → counted) |
| Privileged registers | 10 (PMODE, SMODE2, DISPFB1/2, DISPLAY1/2, EXTDATA, BGCOLOR, CSR, IMR) | all **19** |
| PSMs | 13 (CT32/24/16/16S, T8/8H, T4/4HL/4HH, Z32/24/16/16S) | **13/13** (+ PS-GPU24 `0x12` as a display format) |
| ALPHA equations | 9 (`0x44 0x48 0x42 0x6A 0x58 0x54 0x64 0x06 0x2024`) | any A/B/C/D/FIX; all 9 tested with hand values |
| TEST | ATST 8 functions, AREF, AFAIL, Z GEQUAL (+ ALWAYS in the clear) | ATE/ATST/AREF/AFAIL (4 modes), DATE/DATM, ZTE/ZTST (4) |
| VIFcodes | 15 kinds (NOP, STCYCL, STMASK, STMOD, STROW, DIRECT, MSKPATH3, FLUSHE/FLUSH/FLUSHA, MPG, MSCAL, MSCALF, MSCNT, UNPACK) | all **21** defined (adds OFFSET, BASE, ITOP, MARK, STCOL, DIRECTHL); undefined → trap |
| UNPACK formats | 10 (V4-32, V4-32m, S-32, V2-32, V3-32, V4-8, S-16m, V3-32m, V4-16, V2-16) | all **15 × {plain, masked} = 30**, USN, FLG, CL/WL skip and fill, MODE 0/1/2 |
| DMAC channels | 1 (VIF1), 2 (GIF) | 1, 2 + 0 (trap) |

## Exact vs approximate vs unimplemented

**Exact to the manual's definitions (and tested):** swizzle of all 13 PSMs incl. aliasing between formats, the
Z block XOR, mid-page base pointers and 4 MiB wrap; host↔local transfers with 32/24/16/8/4-bit packing, HWREG,
local↔local with TRXPOS.DIR order; GIF tag forms; kick rules (point, line, strip, triangle, strip, fan, sprite,
XYZ3/ADC, PRIM resets the queue); sprite and triangle coverage on pixel sample points with the top-left rule;
flat shading from the kicking vertex; TFX (4 functions) and TCC; TEXA expansion for 24/16-bit; CLUT CSM1 (both
layouts, CSA for 4-bit), CSM2, CLD 0–5 with CBP0/CBP1; wrap modes (4); the blend equation with arithmetic shift,
COLCLAMP, PABE, FBA; alpha test (8) and AFAIL (4); DATE/DATM; Z test with 32/24/16/16S buffers and ZMSK; FBMSK on
32- and 16-bit frames; DIMX dithering on 16-bit frames; fog; VIF UNPACK formats, masks, modes, write cycles,
double buffering (TOPS/TOP/DBF), MPG, MSCAL/MSCNT; CRTC placement from DISPLAY/DISPFB.

**Approximate (documented choices):** colour/F/UV interpolation is an exact-integer plane equation with floor and
Z a double one (not the GS's DDA bit pattern); STQ interpolated in float; bilinear weights in 1/16 steps,
truncating; LOD from `log2(1/|Q|)` in double, `*_MIPMAP_NEAREST` rounds `lod + 0.5`, trilinear blends two levels;
MTBA automatic mip addresses (inf); lines are a DDA without the diamond rule, points round up; Z above the format
maximum is **clamped** (unverified: hardware may wrap); a CLUT loads when TEX0/TEX2 is written (not at first use)
and only for indexed PSMs (inf); CSA is ignored for 8-bit textures; a 24-bit frame's destination alpha reads
0x80 (inf); the PCRTC merge uses ALP/255 (0xFF = 1.0, inf) with circuit 2 or BGCOLOR underneath, and a circuit
outside its rectangle contributes nothing (the last line of RW's flicker filter blends with BGCOLOR); FRAME-mode
interlace doubles lines; V2/V3 "indeterminate" lanes and unmasked fill writes follow ps2-web-recomp (`x,y,x,y`,
`w = 0`, row register); WL = 0 writes consecutively; `NFIELD = FIELD`.

**Unimplemented:** AA1 antialiasing and PRIM.FIX; a texture cache (TEXFLUSH is a no-op: every sample reads local
memory, i.e. a perfectly coherent cache — a game relying on stale cache contents would differ); GS FIFO timing,
the GS stall on a second SIGNAL, FINISH latency (immediate); IMT intermittent PATH3; EXTBUF/EXTWRITE feedback
write (accepted, stored); HSYNC/VSYNC interrupt generation (flags only); VIF0 (traps); VIF/VU cycle timing.

## Output

`compose()` returns one pixel per read-circuit pixel (MAGH/MAGV divided out): the game's mode gives 640×448. The
game's flicker-free setup (PMODE `0x8067`: both circuits, ALP 0x80; circuit 2 with DBY 1 and DH 446) composes
`out(y) = (buf(y)·128 + buf(y+1)·127 + 127) / 255`, which is a vertical [1,1]/2 filter. PCSX2's `Screenshot.png`
is 640×480 (obs: all four captures), so comparisons resample (`p3fes_gscmp`, bilinear) and must explain residual
differences: the 448→480 scaling filter, the merge rounding above, Gouraud/bilinear rounding, dithering (only on
16-bit frames; this game draws 32-bit, `DTHE 0` in the draw env, `10` §2.8).

## Performance

Measured on the game (MSVC 14.44 Release `/O2`, this host: a 4-vCPU VM; `p3fes --headless --quiet`, the wall times
the host prints at its markers). The title phase is vblank 6374 (movie flag cleared) to 7032 (`--snapshot-at
sky:3315`): 179,142 primitives, 10.5 M triangle rows and 1.136 G covered pixels in 658 vblanks (1.7 M pixels per
vblank, about twelve full-screen layers of blended, bilinear PSMT8/PSMT4 trifans per 640×448 frame). The logo phase
is vblank 365 (first RW flip) to 676 (`--input-script 560:left:4,580:cross:4 --snapshot-at sky:154`), flat sprites
and a few trifans. Profiles with `--profile` (BUILDING.md "Profiling"), samples by function:

| Step | Title phase | ns / pixel | Logo phase | Boot → title | Hottest functions (title samples) |
|---|---|---|---|---|---|
| Baseline (`2b33c18`) | 103.4 s | 91 | 6.35 s | 242.5 s | `Raster::pixel` 18 %, `Raster::triangle` 15 %, `fetch` 14 %, CRT `log2` 13 %, `GsMemory::read` 10 %, `sample_level` 7 %, CRT `floor` 6 %, `wrap_coord` 5 %, `GsMemory::write` 4 %, `sample` 4 % |
| 1: per-primitive texel/plane setup, no per-pixel LOD, span walking, incremental divisions | 56.8 s | 50 | 4.6 s | 169.8 s | `pixel` 32 %, `triangle` 18 %, `texel<T8>` 14 %, `floor_exact` 8 %, `Plane::read` 8 %, `Plane::write` 5 %, `sample_fast` 4 % (MSVC did not inline the helpers) |
| 2: force-inlined helpers, pixel loop instantiated per sampler, shared bilinear wraps, straight-line `a0 b1 c0 d1` blend | 47.4 s | 42 | 3.45 s | 139.8 s | `triangle<T8 bilinear>` 76 %, `triangle<T4 bilinear>` 10 %, `sprite<flat>` 8 %, `triangle<flat>` 3 %; nothing outside the GS above 0.5 % |
| 3: depth test before sampling, no colour stepping for uniform vertex colours, branchless wrap/carry, hoisted scissor/SCANMSK, fog stepping only with FGE | 45.1 s | 40 | 2.93 s | 132.0 s | `triangle<T8 bilinear>` 78 %, `triangle<T4 bilinear>` 9 %, `sprite<flat>` 7 %, `triangle<flat>` 2 % |

Method (`gs_raster.cpp`, all of it provably output-identical to `gs_raster_ref.cpp`; `tests/gs/test_gs_fast.cpp`
draws random primitives through both and requires the two 4 MiB memories equal, `P3FES_GS_FAST_ITERATIONS=20` for a
stress run):

* **Texture.** With `TEX1.MXL = 0` the per-pixel LOD (`log2(1/|Q|)`, the CRT call that cost 13 %) selects nothing
  but the filter, and when MMAG and MMIN agree not even that, so it is skipped; with `LCM = 1` the filter is
  decided once per primitive. Everything else (MXL > 0, MMAG ≠ MMIN with LCM 0) still goes through `ref::sample`.
  The texel fetch is a template per PSM over level 0 with the wrap mode, the buffer base and the swizzle table
  resolved once per primitive and the CLUT folded into a 256-entry palette; the bilinear path wraps its four
  coordinates once and blends two channels per multiply (a channel sum is below 2^16). The pixel loop is
  instantiated per sampler, so for the census's PSMT8/PSMT4/PSMCT32 the fetch is inlined and no call remains in
  the loop; other formats call through a per-primitive pointer.
* **Frame and Z.** Per-primitive `Plane`s address the two buffers inline (page × table) with the 24-bit / T8H /
  T4HL / T4HH merges as read/write masks; PSMT8/PSMT4 frames and undefined PSMs keep the generic `GsMemory` path
  (a separate instantiation). The depth test runs before texture sampling: nothing it depends on is computed
  there and a rejected pixel writes nothing either way, so with twelve layers of overdraw most samples are never
  taken.
* **Triangles.** The three edge functions are linear in x, so each row's pixel span is three divisions instead of
  three products per pixel, and the floor-divided attribute planes (RGBA, F, UV) step as quotient + remainder
  with an exact carry instead of up to seven 64-bit divisions per pixel. Three equal vertex colours skip the
  stepping (floor(0 / area) = 0). Z and STQ keep the reference's per-pixel double/float expressions, evaluated
  from the stepped integer weights (the same values). `std::floor` became a truncating conversion plus one
  compare where its result feeds an integer conversion.
* **Not done.** Per-span page-local frame/Z stepping (the inline address is already a table lookup), caching the
  decoded `DrawState` between kicks, a texture page cache, and a template per TEST/ALPHA combination (the
  remaining per-pixel branches are predictable; the one data-dependent blend equation is special-cased). The
  remaining cost is the pixel pipeline itself at 40 ns per covered pixel on this VM.

Reference route after round 3 (Release, `--headless --quiet --memcard new --replay-input config\inputs\to_dorm.txt
--snapshot-at vblank:4900`): 4900 vblanks (81.7 virtual s) in 140.0 s wall, of which the title/menu segment
(vblank 898–1898) is 75.6 s; frame SHA-256 `ee0eb5da4042b042…` (first measurement, no earlier figure).

The scratch benchmarks of the first version (flat sprite 640×448 8.3 ms, PSMT8 bilinear blended sprite 36.5 ms,
10,000 8×8 Gouraud triangles 27 ms, `compose()` 5.3 ms) predate the fast paths. The debug test suite runs in ~1.4 s.

## Tests

`build/<dir>/bin/p3fes_gs_tests` (ctest `p3fes_gs_tests`): swizzle against the manual's literal column tables,
block order and bijection per page, PSMT8↔PSMCT32 and PSMT4↔PSMCT16 aliasing, page/BW/BP/wrap arithmetic, raw
read/write and transfer round trips for all 13 PSMs, HWREG, local copies; GIF tags, PACKED/REGLIST/A+D/PRE/NLOOP 0,
path arbitration and GIF registers; sprite/triangle coverage, XYOFFSET/scissor, the `skyInitialClear` 4 MiB clear,
kick rules, shading, the 9 ALPHA equations, COLCLAMP/PABE/FBA, alpha test + AFAIL, DATE, Z16S depth, FBMSK,
dithering, fog; textures (CT32/24/16, T8 + CSM1 CLUT, T4 + CSA with 32/16-bit CLUTs, T8H, CLD 0–5, TEX2, CSM2,
wrap modes, bilinear, STQ, mipmaps); VIF1 (stock material packet `0x6C0103FC01000404`/`0x6C0303FD01000404`, all
UNPACK formats, skip/fill, mask/mode, double buffering, MPG + MSCAL with a synthetic XGKICK program, MSCNT, VU
trap, DIRECT incl. split transfers and TTE tags, MSKPATH3 with a stalled channel 2, interrupt bit, traps, FLUSHA,
local→host); privileged registers (CSR revision/FIELD/VSINT, SIGNAL/FINISH/LABEL and IMR, RESET, halves, flip
detection); CRTC compose (one circuit, RW's two circuits, MMOD/SLBG, 16-bit, FRAME mode, union), PNG, the
self-test scene; the fast rasteriser against the reference one (random states and primitives, identical memory).
No game data.
