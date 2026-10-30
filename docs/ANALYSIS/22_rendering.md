# 22 — Rendering: the draw path from the game's draw tasks to the GS, its classification, and the rewrite queue

_Phase 5 analysis (the rendering phase: readable C++ for the draw path, then speed). Database `ida/work_rendering.i64` (a copy of the master, opened headless with idalib; call graph + census dump `tools/ours/ida/rendering_dump.py` → `ida/logs/rendering/`, gitignored). Dynamic evidence from the recorded battle route (`--memcard extracted\_ours\cards\tartarus.ps2 --replay-input config\inputs\to_battle.txt`): the lead's snapshots `extracted/_ours/b_{3500,5800,6150,6300,6700,7200}` and the dorm gate snapshot `dorm_replay_4900`, walked with **`tools/ours/rw_dma_census.py`** (new: decodes RW's DMA queue, the DMA source chains and the VIF1 code stream of one frame); two host profiles and two `--trace-gs` windows run by this analysis (§4.4, §7.4). Every address is an EE virtual address. Tags: **obs** = read from the instructions, the decompiler or a snapshot byte; **der** = derived by a script from obs data; **inf** = inferred. Names: the exported name (`symbols/functions.json`); a name that is `sub_*` there and appears here was verified in this document and is proposed in `symbols/deltas/rendering.sym` (59 rows, not imported); other functions are given as `sub_XXXXXX` with their role. The earlier topics this builds on: `10_frame_loop_gs.md` (init, flip, DMA queue model), `14_vu1_gs_census.md` (114 VU1 programs, code arrays, the 33 PDS pipes), `09_vu1_micro_census.md`, `20_menu_ui.md` (UI = Im2D)._

## 0. Headline

* **The path, top to bottom (obs).** `kwlnTaskMain 0x1949E0` runs the draw tasks in ascending priority (§1): field `K_SceneDraw_*` (2070–4183), battle `btlUpdateDraw3DTask 0x27CCF0` / `…3DFrontTask 0x27CD70` / `…2DTask 0x27CDA0` (2081/4169/4207), the root 2D / 3D-on-2D / etc passes (4196–7379) and `kwlnRootUpdateShowRasterTask 0x199140` (7396). Each pass brackets itself with `RwCameraBeginUpdate 0x4C9D10` → `CameraBeginUpdate 0x4C9BA0` → **`SkyCameraBeginUpdate 0x4D84C0`** (draw-environment packet; the first one per frame blocks in `_rwDMAWaitQueue 0x4D53F0`). 3-D objects go **model draw `sub_317A20`** (18 callers, field and battle) → atomic lists `sub_1A7B50`/`sub_1A8140` (frustum test, `atomic->renderCallBack` at +0x48) → **`AtomicDefaultRenderCallBack 0x490860`** → **`RxPipelineExecute 0x4F2E70`** → **`PS2AllNodeBody 0x49F5D0`** (object setup → `openVU1SetupPktNew 0x4EC2B0`; per mesh: instance if stale → material **bridge callback**, e.g. `RpMeshPS2AllBridgeCallBack 0x4A0E00`) → **`_rwDMAOpenVIFPkt 0x4D59D0`** (packets are written into a 2×8 KiB **scratchpad** double buffer and flushed to the RW DMA buffer by **D8 fromSPR**) → one **VIF1 source chain per frame** queued for `_rwDMAHandler 0x4D4350` → VIF1 → VU1 (`MSCAL/MSCNT` of one of the 114 programs) → `xgkick` → GS; the flip is `_rwDMAVSYNCHandler 0x4D47F0`. The field world goes `K_FldSrc_DrawFieldOpaque 0x1B3E50` → `RpWorldRender 0x49A250` → `WorldSectorRender 0x499320` → `_rpSectorDefaultRenderCallBack 0x499B90` → the same `RxPipelineExecute`. The UI goes the **Im2D device pointers** (100 game functions) → **`SkyIm2DRenderPrimitive 0x4EDBA0`** & co → `addCopyVU1Prim* 0x4ECD40…0x4EE810` → `open2DVU1Pkt 0x4EC100` → VU1 programs **036–039** (until now "unknown_tbl4": they are RW's Im2D dispatch programs, §6).
* **Which pipelines run (der, §4).** Battle frame (vblank 5800): **1,068 VU1 batches** = g3_skin 495, g3_generic 267, **Im2D 256**, g3_matfx 23, PTank 3-D sprites 22, g3_skin_matfx 5; 126 mesh instances; 180,020 qw of UNPACK output; **36,557 qw of microcode re-uploaded** (47 program switches). Field (3500): 662 batches (skin 310, generic 209, Im2D 121, matfx 10, **Rt2d fill 9**, skin_matfx 3). Results screen (6150/6300): Im2D only (80/70). Dorm (4900): 824 batches + one **PATH3 texture upload of 78,358 qw**. The frame is **one VIF1 chain** (1 type-1 queue entry + ~100 resource fences).
* **Host cost (der, §7.4).** In the profiled battle segment the host time is **GS rasteriser 55 %, VU1 interpreter 35 %, soft-float helpers 7 % (shared by VU1 / VU0 macro / COP1), recompiled EE code ≤ 1 %**; the field segment is 58 / 32 / 5 / ≤ 1.3 %. The game's own frame meter says the EE side uses 19 % (battle) to 34 % (field) of the 1/30 s budget in virtual time. **Rewriting the EE draw path in C++ does not by itself buy speed**: speed comes from not interpreting VU1 for the g3_* and Im2D batches (≈95 % of batches) and from the GPU GS. The C++ rewrite is the **seam** that makes that bypass possible: it has the matrices, the material state and the vertex streams in typed form before they become VIF packets.
* **Classification (der, §7).** 543 functions on the path: the RW closure (356, band `0x460000–0x4FB100`) and the game draw layer (187). **(a) pure builders 514** (18 of them also use `di`/`ei`/`Status`), **(b) hardware-touching 29** (8 DMA packet/queue, 2 interrupt handlers, 16 PTank scratchpad-DMA streamers, 2 libgraph, 1 game timer read), **(c) hot 122** (overlaid on a/b). 243 (a)-functions reach a (b) callee (in practice `_rwDMAOpenVIFPkt`), so their pair tests must compare the RecordingBus log and the scratchpad — the test bus already records every access (`tests/rt/fake_hooks.h`).
* **First slice (§8.1):** the **Im2D submission path**, 18 functions / 9,440 bytes, leaf-first in `queue_rendering.txt`: it is self-contained (its only callees are the DMA-packet functions), its input is a typed `RwIm2DVertex` array, and its C++ form is the natural place for a later host fast path that skips VU1 program 039 entirely. Every UI element except the Rt2d (Maestro) animations uses it.

## 1. Frame order: the draw tasks (obs)

The kwln task kernel inserts a task before the first task with a strictly greater priority and walks the list front to back (`game/README.md`, kwln task kernel row), so a frame runs in ascending priority. The root tasks are created by `kwlnRootUpdateTask 0x198650` state 0 (topic 10 §3); the priorities below are the `$a1` of each `kwlnTaskInit`/`kwlnTaskCreate` call (the root ones at `0x198B60`, `0x198BA0`, … `0x199370`; field ones in `K_SceneDraw_CreateTasks 0x19F730`; battle ones in `btlStart 0x27D1D0`; 3-D pipe ones in `sub_1996C0`/`sub_199700`/`sub_1997A0`).

| prio | task (name string) | update function | does | scene |
|---|---|---|---|---|
| 2069 | "Shadow Node Camera" | `kwlnRootUpdateShadowNodeCameraTask` | shadow camera clear (`RwCameraClear`) | all |
| 2070 | "draw opaque field" | `K_SceneDraw_UpdateDrwOpcFldTask 0x19D410` | per field resource with flag 2: `K_FldSrc_DrawFieldOpaque(main camera, res+352)` | field |
| 2071 | "draw opaque field obj" | `K_SceneDraw_UpdateDrwOpcFldObjTask 0x19D780` | lights, `RwCameraBeginUpdate`, model draw `sub_317A20` per object (and its second clump), `K_FldSrc_DrawFieldTrans`, `RwCameraEndUpdate` | field |
| 2081 | "battle draw 3d" | `btlUpdateDraw3DTask 0x27CCF0` | `RwCameraBeginUpdate`, effect pass `sub_321120(2)`, battle draw list `sub_27F160(2)`, effects + models `sub_2BB3A0`, `RwCameraEndUpdate` | battle |
| 2084 | "draw character model" | `sub_19E330` | per character `sub_317A20` | field |
| 2095 | "draw trans field obj PC" | `sub_19E1B0` | translucent objects | field |
| 2098 | "3D Draw Begin" | `K_SPipe_Update3DDrwBeginTask 0x199520` | `RwCameraBeginUpdate`, render states 6/8 | all |
| 4167 | "3D Draw End" | `K_SPipe_Update3DDrwEndTask 0x1995F0` | fog states 14/15/16, `RwCameraEndUpdate` | all |
| 4168 | "draw persona model" | `sub_19F470` | `sub_317A20` | field |
| 4169 | "battle draw 3d front" | `btlUpdateDraw3DFrontTask 0x27CD70` | `sub_321120(3)` + front pass `sub_2891E0` (units via `sub_317A20`, mask packets, screen effect `sub_358460`) | battle |
| 4172 / 4173 / 4183 | trans field obj / trans field / trans field sort, trans NPC sort | `sub_19DE40`, `sub_19D4A0`, `sub_19D530`, `sub_19EF80` | translucent passes, distance sort | field |
| 4196 | "2D Draw Begin" | `kwlnRootUpdate2DDrawBeginTask 0x1989E0` | `RwCameraClear(cam, colour, 2 = Z only)`, BeginUpdate, sprite file manager `sub_1120C0`, `sprSpriteDrawAll 0x1125D0` | all |
| 4207 | "battle draw 2d" | `btlUpdateDraw2DTask 0x27CDA0` | `sub_321120(5)`, `sub_27F160(3)`, battle HUD `sub_29E4B0` | battle |
| 5231 / 5241 | "2D Draw Pre End" / "2D Draw End" | `kwlnRootUpdate2DDrawPreEndTask 0x198B10` / `kwlnRootUpdate2DDrawEndTask 0x198B20` | — / `RwCameraEndUpdate` | all |
| 5243 / 5245 | "3D on 2D Zclear" / "3D on 2D Draw Begin" | `kwlnRootUpdate3DOn2DZClearTask 0x198C10` / `kwlnRootUpdate3DOn2DDrawBeginTask 0x198C60` | Z clear / BeginUpdate | all |
| 5276 | "drawBustupProc" | `kwlnRootUpdateDrawBustupProcTask 0x1993A0` | bust-up banks `sub_1058A0` | events |
| 6320 | "3D on 2D Draw End" | `kwlnRootUpdate3DOn2DDrawEndTask 0x198D20` | EndUpdate | all |
| 6323 / 6335 | "etc Draw Begin" / "etc Draw" | `kwlnRootUpdateEtcDrawBeginTask 0x198E90` / `kwlnRootUpdateEtcDrawTask 0x198F90` | Z clear + BeginUpdate / fade `sub_107060`, debug print | all |
| 7379 | Draw End | `kwlnRootUpdateDrawEndTask 0x198FD0` | EndUpdate | all |
| 7396 | "<<< show raster >>>" | `kwlnRootUpdateShowRasterTask 0x199140` | `RwCameraShowRaster` → flip request; T0 CPU-load statistic | all |

UI screens are their own kwln tasks at their own priorities inside these bands (e.g. the cursor "H CURSOR Draw" at 0x18BF = 6335, topic 20 §3); they draw through Im2D between a Begin/End pair that a root task opened.

## 2. Game draw layer → RenderWare object render (obs)

### 2.1 What the game calls
The game-side layer is the 187 game functions that call the RW render API directly (`ida/logs/rendering`, der): **Im2D device pointers 100** (`0x9600A0` RwIm2DRenderPrimitive: 50 functions — sprites `sub_1127D0` (193 callers), glyphs `frFontRasterDrawGlyph 0x3B38F0`, cursor `H_Cursor_UpdateDrawTask 0x100230`, fades, the movie player `sub_10A860`, screen effects; `0x96009C` RenderTriangle: 44 functions, 955 references, the battle/opening panels `sub_2xxxxx`; `0x9600A4` indexed: 10), **`RpSkyRenderStateSet` 112** (665 call sites, topic 14 §4), **camera Begin/End 45**, **`RwIm3D*` 8** (`sub_20B250` (model draw through Im3D, 16 transform calls to `sub_4F1ED0`), shadow `sub_19AB80`/`sub_199D90`/`sub_19A420`, line primitives `sub_359110`, `sub_395950`, `sub_41BF80`, `sub_20D500`), **Rt2d 3** (`sub_10EC50` and the two Maestro (Rt2d animation) draw tasks `sub_111610`, `sub_10F6C0`), **PTank lock 3** (battle effects `sub_2496E0`, `sub_249C10`, `sub_3275D0`), **raw VIF packets 4** (`sub_3294D0`, `sub_329550`, `sub_3295C0`, `sub_329630`: alpha-mask / frame-mask / clamp packets built by the game itself with `_rwDMAOpenVIFPkt` — the only game code that writes VIF data), `RpWorldRender` 1 (`K_FldSrc_DrawFieldOpaque`), `RpClumpRender 0x491630` 1 (`sub_34DC00`, an effect).

### 2.2 Models (field and battle)
**`sub_317A20`** (2,220 B) is the model draw: 18 callers — the field object/character/persona/NPC tasks of §1, the battle front pass `sub_2891E0`, battle effects `sub_2BB3A0`, the shadow-map tasks `0x19B2B0`/`0x19C4B0`, and `sub_41B810`, `sub_425690`, `sub_4260A0`. It sets the model colour, walks the clump (`sub_4916D0`), and hands the model's four atomic lists to **`sub_1A7B50`** (opaque) and **`sub_1A8140`** (translucent): for every atomic `atomicGetWorldBoundingSphere` (world bounding sphere) + `sub_4C9DF0` (frustum sphere test), render state 14 (Z write) around it, then **`(*(atomic + 0x48))(atomic)`** — RW's atomic render callback (18 and 21 `jalr` sites in the two functions). The callback is **`AtomicDefaultRenderCallBack 0x490860`** for every atomic (installed by the atomic constructor `sub_491880`; also by the PTank atomic creator `sub_474260`): pipeline = `atomic+0x6C`, or the global default → `RxPipelineExecute(pipe, atomic, 1)`. `RpClumpRender 0x491630` does the same walk for whole clumps (render flag bit 2 at atomic+2, `sub_4CB2F0` frame LTM, callback +0x48) but only one effect uses it.

### 2.3 The field world
`K_FldSrc_DrawFieldOpaque 0x1B3E50` (2,244 B): ambient + directional light set-up (`sub_4944B0`), moves the main camera into the field world or one of its two sub-worlds (resource +8/+12/+16 chosen by flag bits 30/31), `RwCameraBeginUpdate`, render states 6/8 and fog 14/15/16, then **`RpWorldRender 0x49A250`** = `sub_49C330(camera, WorldSectorRender, world)` (frustum sector walk) → **`WorldSectorRender 0x499320`**: the sector's own render (`worldSectorRenderDispatch` calls the world's sector callback at world+104 = **`_rpSectorDefaultRenderCallBack 0x499B90`**: sector pipe +124, world default +108, else global → `RxPipelineExecute`) and, for every atomic linked to the sector (+56) not yet drawn this frame (render-frame stamp at atomic+96 vs `word_960078`), the frustum test and its render callback. Field objects then go `sub_1A7B50`. `K_FldSrc_DrawFieldTrans 0x1B4720` is the translucent pass over `sub_1A8140`.

### 2.4 Camera and present
`RwCameraBeginUpdate 0x4C9D10` / `RwCameraEndUpdate 0x4C9D00` call camera+24/+28 = `CameraBeginUpdate 0x4C9BA0` (current camera, frame sync, device begin `dword_9600BC`, `sub_4F28E0`) / `CameraEndUpdate 0x4C9B40` (device end `dword_9600E0`) → `SkyCameraBeginUpdate 0x4D84C0` (FRAME/ZBUF/XYOFFSET/SCISSOR packet, topic 14 §6; first call per frame throttles in `_rwDMAWaitQueue`) / `sub_4D8E80`. `RwCameraClear 0x4C9E90` → device clear → `sub_4D8F40`. `RwCameraShowRaster 0x4C9ED0` → `RwRasterShowRaster 0x4CDFE0` (resource purge + device show) → `SkyRasterShowRaster 0x4D9460` → `_rwDMAReqFlip 0x4D5270` (topic 10 §3).

## 3. RenderWare object → PS2All pipeline → packets (obs)

### 3.1 `RxPipelineExecute 0x4F2E70` and the PS2All object node
`RxPipelineExecute` stores the pipeline, object and heap in the execution-context globals and calls the first node's body (`node->definition` at +8, body at +4). For every atomic/sector pipeline that body is **`PS2AllNodeBody 0x49F5D0`** (1,220 B; node definition `0x77DE84`):

1. object setup callback at node-private +16 (the object-setup callbacks on the path are `sub_4A09D0`, `sub_46EB90`, `skinSplitObjectSetupCB`, `ps2AllSectorObjectSetup`) — transform type, lights, instancing test, matrix palette (skin: **`_rpSkinMatrixUpdating 0x46B510`**: per bone `LTM × skin-to-bone` and `× inverse(atomic LTM)` on VU0 macro (`lqc2`, COP2 macro operations, `sqc2`));
2. **`openVU1SetupPktNew 0x4EC2B0`** — per-object VIF packet (matrix and light block UNPACK; light buffer `gp-17516`);
3. per mesh (mesh header +4 = count, 12-byte mesh records): material pipeline = object default (node +24), else the mesh's material pipe (material +8), else the global default; its PS2AllMat callbacks array (pipe +8 → node +20): if the mesh has no or a stale resEntry, **`PS2AllNodeInstance 0x49FAA0`** (size recalculation `ps2AllInstanceSizes`, tag fill `ps2AllInstanceDmaChain`, instance callback: **`RpMeshPS2AllInstanceCallBack 0x4A0DC0`** = sector `ps2AllSectorInstance` / atomic `ps2AllAtomicInstance`, or **`RpPDS_G3d_Skin_PS2AllInstanceCallBack 0x46EB10`** = atomic instance + skin weights `skinInstanceWeights`), the resEntry is relinked at the head of the resource list (RW globals +36), then **bridge callback [3]**, then post-mesh callback [4];
4. the object's post callback (node-private +20).

Instancing (vertex data → VIF UNPACK clusters in the resource arena) therefore happens once per mesh (first render, morph/geometry change); every later frame only re-runs setup + bridge and `call`s the cached resEntry (§4: 98–141 distinct resEntries per frame, no instancing in a steady frame).

### 3.2 The material bridge
`RpMeshPS2AllBridgeCallBack 0x4A0E00` (1,572 B; the PDS bridges at `0x46C5B0…0x472970` (six full bridges and five 60-byte wrappers) have the same skeleton with extra UNPACKs, topic 14 §3): texture → `sub_4F0F30` (speculative cache access) and **`RpSkyTexCacheAccessRaster 0x4F1020`** when the raster changed (§5.3); texture filter / clamp shadows (`sub_49CA50`); `_rwDMAOpenVIFPkt(0, 18)`; GIF tag from the template at `0x9658A0` with PRIM = the shading flags `gp-20272` (the bridge sets bit 0x10 when textured and 0x40 when alpha or a texture with alpha is used) | the mesh prim (mesh +41); material colour (`sub_49CAB0`) → `UNPACK V4-32 ×1 → 0x3FC`; surface properties (`sub_49CBD0`) + clip vectors → `UNPACK ×3 → 0x3FD`; TEST/TEX0/CLAMP A+D (textured) or TEST only; then the **VU1 code array entry**: index (mesh +43) = **`((tt & 0x20) >> 5) | ((tt & 0x18) >> 2)`** with `tt` = mesh +40, and when the entry differs from the resident program (`gp-16888`) a **DMA `call` (0x50000000 | addr << 32) to the program's `ret` packet**; finally a `call` to the mesh's resEntry DMA data (the instanced UNPACK clusters, which carry their own `MSCAL`/`MSCNT` kicks: 457 `MSCNT` for the skin program in a battle frame, §4). `tt` comes from **`RpAtomicPS2AllPrimTypeTransTypeSetupFunc 0x4A05D0`**: the camera global `gp-16892` (set by `sub_4EEC20`, the per-camera VU constants: bit 3 = the camera is not perspective, i.e. parallel projection; bit 0 = fog, inf — it is also what picks the second Im2D descriptor, §6), then from the geometry flags bit 2 = list (tri-list or line-list), bit 4 = line primitives, and bit 1 when the frustum test result is not "inside" (clip); prim (mesh +41) 1 line list, 2 polyline, 3 tri-list, 4 tri-strip. So code-array entries 4–7 are the line programs and 2/3 the parallel-projection ones; bit 5 (entries 1/3/5/7 vs 0/2/4/6) is set in every observed perspective tri-strip frame (programs 042/064 = entry 1) and its source flag is open (§9).

### 3.3 Which pipeline an object gets (static)
| object | assigned by | PDS id (`RpPDSGetPipe 0x46A890`) |
|---|---|---|
| default material / atomic / world sector | `sub_4A5210` / `sub_4A5330` / `sub_4A52A0` at plugin open | 0x1001 / 0x1002 / 0x1003 |
| skinned atomic (RpSkin) | `sub_48AC10` (from `sub_489350` and the skin-type setter `sub_48A3F0`) | 0x11002, or 0x11013/0x11014 when MatFX is attached (geometry flag 0x80 picks the second) |
| MatFX atomic / MatFX world sector | `matfxSetAtomicPipeline` / `matfxSetSectorPipeline` | 0x1100D/0x1100E / 0x1100F/0x11010 (geometry/world flag 0x80) |
| big-skeleton character (skin with ≥ 0x41 bones) | **`mdlManagerSetClumpPipelines 0x312F90`** (per atomic from `sub_316970`, the model set-up) | atomic 0x1001F; materials by **`mdlManagerSetMaterialMatFxPipeline 0x312E80`**: MatFX effect 1–6 → 0x10021, 0x10022, 0x10023, 0x10024, 0x1002A, 0x1002B, none → 0x10020 |
| Im3D (`sub_20B250`, shadows, debug lines) | `sub_49C8C0` | 4 (transform), 5, 6, 7 (render, by prim type) |
| Rt2d (Maestro UI) | `rt2dPS2PipeOpen 0x4B1100` | 0x1001A font, 0x1001C fill, 0x1001E stroke |
| PTank particles | `sub_478A70`/`sub_479E50` (rpSpr2dGen/rpSpr3dGen material pipes) | own PS2All pipes (programs 028–035) |
| Im2D | not a pipeline: device functions (§6) | VU1 programs 036–039 |

The PDS definitions behind these ids, their code arrays and bridges are topic 14 §2. The 33 registrations are `kwlnInitRenderer 0x197350`.

## 4. Dynamic evidence: what each scene actually sends (der)

### 4.1 Method
`tools/ours/rw_dma_census.py <snapshot>` reads RW's DMA globals from `eeMemory.bin` (`$gp` = 0x7D2CF0: `gp-17304` buffer base, `gp-17160`/`gp-17156` half-buffers, `gp-17164` half size, `gp-17192` queue write pointer — §5.1), walks each half-buffer's queue ({u32 type|flags, u32 addr} entries; type 127 = jump), follows every VIF1 source chain tag by tag (cnt/next/ref/refs/call/ret/end, with the two VIF codes each tag carries) and decodes the VIF1 code stream (UNPACK sizes, MPG, MSCAL/MSCALF/MSCNT, DIRECT + the GIF tags inside). A `call` to one of the 114 program packets of topic 14 sets the "resident program"; MSCAL/MSCNT are counted against it; a `call` to anything else is a mesh resEntry. In every snapshot both halves are complete frames (the snapshot falls between a frame's build and its flip) and give the same counts within 1 %. The frame images were checked (`b_3500` Tartarus corridor with three party members and the "Dark Hour" HUD; `b_5800` battle with a fire hit on the harp enemy; `b_6150`/`b_6300` results screens).

### 4.2 Per scene
| snapshot (vblank) | scene | VU1 batches by family (MSCAL+MSCALF+MSCNT) | programs uploaded this frame (`call`s) | meshes (`call`s to resEntries / distinct) | UNPACK out qw | microcode qw | DIRECT qw (A+D regs) |
|---|---|---|---|---|---|---|---|
| 3500 | field | skin 310, generic 209, **Im2D 121**, matfx 10, **rt2d_fill 9**, skin_matfx 3 = **662** | 042 ×9, 064 ×5, 097 ×4, 039 ×2, 101, 089 | 176 / 111 | 118,331 | 18,406 | 14,201 (8,708) |
| 5800 | battle | skin 495, generic 267, **Im2D 256**, matfx 23, **ptank_spr3d 22**, skin_matfx 5 = **1,068** | 042 ×17, 064 ×9, 061 ×7, 033 ×5, 039 ×4, 046 ×4, 035 ×3, 093, 101 | 126 / 98 | 180,020 | 36,557 | 3,682 (2,633) |
| 6100 | battle | skin 180, Im2D 153, generic 86, matfx 17, skin_matfx 5 = 441 | 042 ×7, 061 ×3, 064 ×3, 039 ×2, 093, 101 | 50 / 39 | 66,398 | 14,038 | 2,167 |
| 6150, 6300 | results | Im2D only: 80, 70 (program resident from the previous frame) | — | 0 | 1,488 / 1,890 | 0 | 1,234 / 1,044 |
| 6700 (7200 equal) | field | skin 593, generic 233, Im2D 180, skin_matfx 30, matfx 14 = 1,050 | 042 ×8, 064 ×7, 063 ×6, 039 ×4, 102 ×3, 097 ×3, 101 ×3, 041 ×2, 046 | 205 / 115 | 197,509 | 29,218 | 8,139 |
| 4900 (dorm gate) | event | generic 329, skin 311, Im2D 161, matfx 17, skin_matfx 6 = 824 | 042 ×7, 064 ×5, 097 ×3, 101 ×2, 093, 039 | 141 / 141 | 153,294 | 16,956 | 3,757 + **PATH3 IMAGE 78,358** |

UNPACK formats per battle frame: V4-32 1,551, V3-32 790, V3-8 790, V4-8 812, V2-32 689 (the instanced clusters: position, normal, colour, UV) and **V4-32m 256** (Im2D vertices; equal to the Im2D batch count in every snapshot).

### 4.3 Program → pipeline
042 = g3_generic[1], 046 = [0], 041 = [3] (array 0x6B4F00: default material pipe 0x1001 and the Im3D pipes); 064 = g3_skin[1], 063 = [3] (array 0x6B5380: skin pipe 0x10001, SkSpt 0x10020); 061/093/097 = g3_matfx[17]/[21]/[25] (array 0x6B5170, pipes 0x1100B/0x1100C; 17/21/25 = 4k+1 with k = 4, 5, 6 — the MatFX bridge adds a per-effect group of 4, inf); 101/102 = g3_skin_matfx[21]/[23] (= g3_skspt_uva[1]/[3], the same program bytes); 033/035 = ptank_spr3d[3]/[1]; 089 = rt2d_fill[0]; **039 = Im2D triangles, descriptor 0x7BCF70** (§6). Never seen in these frames: rt2d_font/stroke, ptank_spr2d/xform, g3_skin entries other than 1/3, the Im2D programs 036/037 of the second descriptor, the 28 unreferenced programs.

**Field**: world sectors and objects on g3_generic/g3_matfx, characters on g3_skin (+ skin_matfx), HUD on Im2D + one Rt2d fill (the Maestro HUD). **Battle**: the same plus PTank 3-D sprites (the hit effect) and more generic/matfx (enemy, arena); one program switch per mesh group → 47 microcode uploads (36.6k qw) per frame. **UI/results**: Im2D only.

### 4.4 GS register trace (`--trace-gs`, placement registers per frame, obs)
| window | TEX0_1 PATH2 / PATH1 | FRAME_1 | ZBUF_1 | FRAME_2 / ZBUF_2 | BITBLTBUF+TRXDIR (PATH3) |
|---|---|---|---|---|---|
| field vblank 3641 / 3643 (r6-prof build) | 186 / 4 | 146 | **1,029** | 96 / 7 | 46+66 / 16+20 |
| battle vblank 5797 / 5799 (f-int build) | 180–184 / 22–24 | 50–54 | 95 | 22 / 11 (+10 on PATH1) | 4 / 0 |

Every texture placement goes through PATH3 (`sub_4D6250`, §5.3); the field frame changes ZBUF ~1,000 times (Z-write toggles from render state 14 around every atomic, `sub_1A7B50`).

## 5. The bottom: packet buffers, DMA queue, texture cache (obs)

### 5.1 Scratchpad packets and the DMA buffer
`_rwDMADmaOpen 0x4D67B0` allocates 0x280000 + 128 bytes (`gp-17292` raw, `gp-17304` = 128-aligned base): a 2 KiB header and two half-buffers of `gp-17164` bytes (`gp-17160` = base + 2048, `gp-17156` = half 1; in the snapshots base 0x9B0200, halves 0x9B0A00 / 0xAEFE00, size 0x13F400). The **queue lives inside each half**: a 15-entry block at the half's start (`gp-17192` write pointer, `gp-17188` limit), extended by type-127 jump entries into blocks carved from the packet space (`gp-17184` allocation pointer, `gp-17180` half end). `_rwDMAOpenVIFPkt 0x4D59D0` opens or extends the current packet: data are written to the **scratchpad** (`gp-17124` = 0x70000000 ^ 0x2000 double buffer, write pointer `gp-17148`) and copied to the DMA buffer (`gp-17128`) by a **D8 fromSPR** transfer each time 8 KiB fill or the packet type changes: `D_STAT = 0x100`, `D8_SADR/MADR/QWC`, `D8_CHCR = 0x100`, and `D_PCR = 0x100` + `sync` when D8 is still busy (0x4D5A90 region; the same sequence in `_rwDMAClosePkt 0x4D4A60`, `_rwDMAOpenGIFPkt 0x4D54E0`, `sub_4D5FE0`, `sub_4D5E90`). The packet type word (`gp-17212`: 0x1101 VIF chain + TTE, 0x102 GIF, bit 31 = an open `cnt` tag) becomes the queue entry when the packet closes (`_rwDMAClosePkt` writes the previous entry; image uploads add the pair 0x1121/0x122). `_rwDMAAddPURef 0x4D51C0` keeps a ring of resource references (`gp-17268`/`gp-17264`); `sub_4D4280` (reference flush) emits type-66 fences, which is the ~100 type-66 entries per frame of §4.

### 5.2 Kick and flip
Topic 10 §3.1 is unchanged: `_rwDMAHandler 0x4D4350` (DMAC ch1/ch2 handler and inline driver) pops entries while nothing is in flight: type 1 → `D1_TADR/QWC/CHCR`, type 0x21/0x22 → `MSKPATH3` to the VIF1 FIFO + `GIF_MODE`, D2 chain then D1 chain, flips 64/65 → stop until `_rwDMAVSYNCHandler 0x4D47F0` writes DISPFB/DISPLAY and resumes. Observed here: a steady frame is **a single VIF1 chain** (battle: 3,061 `cnt`, 566 `ref` (22,541 qw), 177 `call`/`ret`, 1 `end`), plus the PATH3 chain when textures are uploaded.

### 5.3 Texture cache
Bridge → **`RpSkyTexCacheAccessRaster 0x4F1020`** (1,304 B): if the raster is not resident, the cache's upload callback (`dword_77F220`; allocator `sub_4EFA00`, 2,268 B, 14 loops) places it in GS memory from page 350 up (topic 10 §2) and queues the upload (`sub_4D6250` → queue type 0x21/0x22: VIF1 chain + GIF chain with `BITBLTBUF/TRXPOS/TRXREG/TRXDIR` + IMAGE); then the raster's TEX0 TBP/CBP fields are patched from the cache slot (`+8`/`+12`, 14-bit block addresses; the frame-buffer raster special case uses `draw0/draw1.frame1`) and a TEX0 (+TEX1) A+D packet is emitted through `_rwDMAOpenVIFPkt`. Per frame: field 46–66 uploads (§4.4), battle 4, dorm one 78k-qw image (a bust-up or the movie texture).

### 5.4 Render state
`RpSkyRenderStateSet 0x4D7F60` (game-facing: ALPHA/TEST/DIMX) and `_rwSkySetRenderState 0x4D6B90` (RW states → GS shadows) each emit a one-register A+D packet per change (topic 14 §4): ~1,000 per field frame (§4.4). A redundancy filter would cut GS state traffic but changes the DMA stream (not allowed in a faithful rewrite; a later "fast mode" option).

## 6. The Im2D path (UI) (obs, der)

* `_rwSkyOverloadPipelines 0x4EEBC0` (RW device request 0x11 from `RwEngineStart`) writes the four Im2D device slots: `0x960098` = **`SkyIm2DRenderLine 0x4ECA60`**, `0x96009C` = **`SkyIm2DRenderTriangle 0x4ECCE0`**, `0x9600A0` = **`SkyIm2DRenderPrimitive 0x4EDBA0`**, `0x9600A4` = **`SkyIm2DRenderIndexedPrimitive 0x4EEB50`**, then calls the VU1 dispatch init `sub_4EC510`. The game calls these pointers directly (§2.1).
* `SkyIm2DRenderPrimitive(prim, verts, n)`: prim 1–5 indexes the array at **0x77F1B0** = {—, **`addCopyVU1PrimLineList 0x4ECD40`**, **`addCopyVU1PrimPolyLine 0x4ECFD0`**, **`addCopyVU1PrimTriList 0x4ED260`**, **`addCopyVU1PrimTriStrip 0x4ED570`**, **`addCopyVU1PrimTriFan 0x4ED890`**} (RW's rwPRIMTYPE order); the indexed variant uses **0x77F1D0** = {—, `addCopyVU1IndPrimLineList 0x4EDC20`, `addCopyVU1IndPrimPolyLine 0x4EDED0`, `addCopyVU1IndPrimTriList 0x4EE180`, `addCopyVU1IndPrimTriStrip 0x4EE4B0`, `addCopyVU1IndPrimTriFan 0x4EE810`}; Line/Triangle go to `addCopyVU1Line 0x4EC8A0` / `addCopyVU1Triangle 0x4ECAC0`. The first argument is a **dispatch descriptor** chosen by bit 0 of `gp-16892` (fog, inf): **0x7BCF70 (bit clear) = {`open2DVU1Pkt 0x4EC100`, program 038 `0x5CD820`, program 039 `0x5CD980`, 0}** and **0x7BCF80 (bit set) = {`open2DVU1Pkt`, 036 `0x5CD3B0`, 037 `0x5CD5B0`, 0}** (read from the ELF). Topic 14's "unknown_tbl4" table (`0x7BCF74`) is the middle of the no-fog descriptor; the four programs are RW's Im2D programs.
* A builder (`addCopyVU1PrimTriStrip`, 800 B) expands the strip into triangles and emits them in batches of ≤ 16: the descriptor's open callback (`open2DVU1Pkt(3, 12, n, 5, descriptor+8 = the triangle program, …)`: `_rwDMAOpenVIFPkt`, program `call` when it changes, GIF tag), a `cnt` tag of 12·n+2 qw with the `STCYCL`/`UNPACK V4-32m` header, then 3 vertices × 4 qw per triangle (64-byte `RwIm2DVertex`, alternating winding), and `closeAndDispatchVU1Packet 0x4EC4C0` (64-byte trailer with the MSCALF). Descriptor +4 (038/036) is the line program, +8 (039/037) the triangle program. One Im2D call = one or more VU1 batches; the battle frame has 256, a results frame 70–80.
* For a host renderer this is the easiest seam in the whole path: the vertices are already in screen space (`x, y, z, rhw, colour, u, v`), the raster and blend come from the preceding `RwRenderStateSet` calls, and the VU1 program is a short transform/clip (programs 036–039 are 41–76 instructions, topic 14 §1).

## 7. Classification for Phase 5 (der)

### 7.1 Counts
Path = RW closure (356 functions reached from the render entry points, the PS2All/PDS/PTank/Rt2d/Im2D callbacks and the data-table callbacks, minus creation/stream/plugin functions) + game draw layer (187, §2.1). Hardware access = a `lui 0x1000|0x1001|0x1100|0x1200` whose register is then the base of a load/store, `cfc2`/`ctc2` of VU control registers (vi26–29, 31), or `syscall` (field `hwregs` of `tools/ours/ida/rendering_dump.py`, cross-checked by an independent scan of the ELF bytes: the same 49 functions image-wide; constants that only build DMA/GIF tags are not counted — a plain `lui 0x1000` count would also flag every bridge and Im2D builder, which only build `0x10000000`-style tag constants). The closure, the depth order and the class/flag columns of the queue were computed from that dump (scratch scripts, not committed; the rules are the ones stated here and in the queue header).

| | RW closure | game layer | total |
|---|---|---|---|
| (a) pure builder | 310 | 186 | 496 |
| (a0) builder + `di`/`ei`/`mfc0 Status` only | 18 | 0 | 18 |
| (b) hardware-touching | 28 | 1 | 29 |
| of which (c) hot | 118 | 4 | 122 |
| (a/a0) that reach a (b) callee | 99 | 144 | 243 |

### 7.2 The (b) functions and what a pair test needs
| group | functions | registers |
|---|---|---|
| DMA packet / queue (8) | `_rwDMAOpenVIFPkt`, `_rwDMAClosePkt`, `_rwDMAOpenGIFPkt`, `_rwDMAAddPkt`, `_rwDMAForceBufferSwap`, `sub_4D5FE0`, `sub_4D5E90`, `sub_4D6250` | D8 fromSPR `0x1000D000/10/20/80`, `D_STAT 0x1000E010`, `D_PCR 0x1000E020` |
| interrupt handlers (2) | `_rwDMAHandler`, `_rwDMAVSYNCHandler` | `GIF_STAT 0x10003020`, D1 `0x10009000–30`, D2 `0x1000A000–30`, VIF1 FIFO, `cfc2 vi29`; `DISPFB1/DISPLAY1 0x12000070/80`, `GS_CSR 0x12001000` |
| PTank particle streamers (16) | `sub_476140`, `sub_476490`, `sub_476720`, `sub_476980` (scratchpad fills), `sub_47C240` … `sub_485750` (12 per-format instance writers) | D9 toSPR `0x1000D400/20`, D8 `0x1000D000/80`, `D_STAT`, `D_PCR`; they stream particle arrays through the scratchpad |
| libgraph (2) | `sceGsSyncPath 0x4F99D0`, `sceGsPutDispEnv 0x4F94E0` | `cfc2 vi29`; GS privileged |
| game (1) | `kwlnRootUpdateShowRasterTask 0x199140` | `T0_COUNT` |

The test machine already has what these need: `tests/rt/fake_hooks.h` `RecordingBus` logs every hardware access (direction, width, physical address, value) and serves reads from a register map (default pattern), and `TestHooks` records syscalls and VU control writes. `tests/game/pair_harness.h` does not compare that log yet: a rendering pair test adds (1) the bus log to `Outcome` and compares it, (2) primes the reads (e.g. `D8_CHCR` idle / busy to take both paths), (3) compares the scratchpad and the DMA half-buffer, not only the 8 KiB arena, and (4) for the PTank streamers, either pre-fills the scratchpad or adds a fake DMAC that performs D8/D9 copies (the recording bus performs no transfer, so both runs would compute on the same stale scratchpad). The 243 builders that only reach a (b) callee run that callee recompiled in both runs, so (1) + (3) suffice. The 18 (a0) functions mask interrupts around queue updates; `di`/`ei`/`Status` live in the `EEContext`, nothing to record.

### 7.3 Hot loops (c), ranked by likely EE cost
1. **c1 particles** — PTank instance writers (`sub_47C240`… 16 functions, up to 6 KiB each, 10–31 loops): per particle per frame, with scratchpad DMA; live in battle effects (22 batches).
2. **c2 skin palette** — `_rpSkinMatrixUpdating 0x46B510` (two VU0 4×4 products per bone), `sub_46B8E0` (palette upload), skin object setup `sub_46EB90` (18 loops) / `skinSplitObjectSetupCB`: per skinned atomic per frame, every character.
3. **c3 Im2D** — the 13 `addCopyVU1*` builders: 4 qw copied per vertex, 70–256 batches per frame; and the game side `sub_1127D0` (sprite) / `frFontRasterDrawGlyph` per sprite/glyph.
4. **c4 per mesh / per atomic** — `PS2AllNodeBody`, the bridges (`RpMeshPS2AllBridgeCallBack` + 6 PDS bridges, 9–11 loops), `openVU1SetupPktNew`, light set-up `sub_49FF10`/`sub_4A06C0`: 126–205 meshes per frame.
5. **c5 texture cache** — `RpSkyTexCacheAccessRaster`, allocator `sub_4EFA00`, upload builders `sub_4D6250`/`sub_4EF540`/`skyFillInPktForUpLoadAlignedContiguousRectangle`/`sub_4E4E90`: per material change, per miss (field 46–66 per frame).
6. **c6 render state** — `_rwSkySetRenderState`, `RpSkyRenderStateSet`: ~1,000 calls per field frame.
7. **c7 culling** — `WorldSectorRender`, `sub_49C330`, `sub_4C9DF0`, `atomicGetWorldBoundingSphere`, `sub_1A7B50`, `sub_1A8140`, `sub_317A20`: per sector / atomic.
8. **c8 instancing** — `ps2AllAtomicInstance` (4,196 B, 28 loops), `ps2AllSectorInstance`, `ps2AllInstanceDmaChain`, `ps2AllInstanceSizes`, `sub_4A35C0`, skin weights `skinInstanceWeights`: per vertex, but only when a mesh is (re)instanced (load time; 0 in a steady frame).
9. **c9 raster lock / blit** — `sub_4DE0A0` (3,132 B, 26 loops: CPU swizzle of a locked raster, every frame while a movie or a captured texture is shown), `sub_4E53E0`/`sub_4E6D60`/`sub_4E8610` (raster blits).

### 7.4 What the host actually spends (der)
Two `--profile` runs of the battle route with the PDB-carrying `build/r6-prof` (Release + `/Zi`, built 2026-10-19; its battle frame at vblank 5800 hashes the same as the lead's `f-int` snapshot, `993a1cb4…`), symbolised with `llvm-symbolizer`:

| segment | samples | GS raster (`p3fes::gs::`) | VU1 interpreter (`p3fes::vu1::`) | soft-float (`p3fes::ee::fpu`) | VU0 macro | recompiled EE (`fn_*`) | rt adapter |
|---|---|---|---|---|---|---|---|
| battle, vblank 5750–6100 | 2,213 | 1,220 (55.1 %) | 764 (34.5 %) | 153 (6.9 %) | 4 | 5 (0.2 %) | 13 (0.6 %) |
| field, vblank 3450–3650 | 977 | 564 (57.7 %) | 315 (32.2 %) | 47 (4.8 %) | 1 | 5 (0.5 %) | 8 (0.8 %) |

Top entries: `Raster::triangle<StaticSampler<19,1>>` 15.7 %, `vu1::compute_upper` 10.7 %, `VU1Interpreter::step` 10.1 %, `Raster::triangle<NoSampler>` 9.0 %, `Raster::sprite<NoSampler>` 6.9 %, `Raster::pixel` 6.2 %, `vu1::set_flags` 4.3 %, `ee::fpu::add` 3.3 %, `Vif1::exec_unpack` 1.1 %. The soft-float helpers are shared by the VU1 interpreter (`vu1_interp.cpp` uses `ee/fpu.h`), VU0 macro instructions and COP1, so the EE share is between 1 % and 8 %. The game's own meter (`g_kwlnCpuLoadPct 0x7CE150`, H-lines of virtual time from frame start to show-raster ÷ 520) reads field 33.5 % (174 H-lines), battle 18.8 % (98), dorm 13.5 %, results 2.3 % — the EE side never limits the frame rate in virtual time.

Consequences for the phase goal: (1) a faithful C++ rewrite of EE functions moves ≤ 1 % of host time; (2) the levers are the VU1 batches (g3_skin + g3_generic = 71–78 % of batches, Im2D 18–25 %) and the GS; (3) **microcode is re-uploaded on every program switch** (36.6k qw in a battle frame, 47 switches) — the VU1 lane should key decoded programs by packet address / hash (114 known packets) instead of re-decoding MPG data; (4) UNPACK volume is 118k–198k qw per frame; (5) the EE-side seam that lets a renderer skip VU1 is the bridge level (§3.2, §6), which is why the queue starts there.

## 8. Rewrite queue and the recommended first slice

`docs/ANALYSIS/queue_rendering.txt`: 543 rows, leaf-first by call depth on the strongly-connected-component condensation (the DMA-packet functions form one cycle: `_rwDMAClosePkt` ↔ `sub_4D4280` ↔ `_rwDMAAddPkt` ↔ `_rwDMAForceBufferSwap`), with size, class, flags (`c`, `callsB`, `vu0`, `spr`) and notes; the two slices first, then the RW closure, then the game layer.

### 8.1 First slice: the Im2D submission path (18 functions, 9,440 B)
`open2DVU1Pkt 0x4EC100` (420), `addCopyVU1Triangle 0x4ECAC0` (544), `addCopyVU1Line 0x4EC8A0` (436), the five `addCopyVU1Prim*` (652–800) and five `addCopyVU1IndPrim*` (688–864), `SkyIm2DRenderTriangle/Line/Primitive/IndexedPrimitive` (88–116), `closeAndDispatchVU1Packet 0x4EC4C0` (72). All class (a); 17 reach `_rwDMAOpenVIFPkt` (b).
* **Readable C++**: every sprite, glyph, window, fade and HUD element of the game except the Rt2d (Maestro) animations goes through these 18 functions; the hand versions turn MMI `lq`/`sq` copy loops into a typed `RwIm2DVertex` batcher (strips and fans expanded into triangles, ≤ 16 primitives per VU1 batch, descriptor/program selection by bit 0 of `gp-16892`).
* **Pair tests**: inputs = random vertex arrays in the arena, prim types 1–5, counts 0–100 (crossing the 16-vertex batch and the 8 KiB scratchpad half), fog bit on/off, resident program equal/different; compare the scratchpad, the DMA half-buffer region, the RW packet globals (`gp-17212…-17124`), the bus log (D8/D_STAT/D_PCR), cycles and check points. No callee besides the DMA-packet functions, which stay recompiled.
* **Speed seam**: with the batcher in C++, the D3D11 / VU1 lanes can add a host path at `SkyIm2DRender*` (screen-space quads straight to the GS backend, skipping VIF V4-32m, program 039 and the PATH1 kick) behind a switch, and validate it against the faithful path frame by frame. On the results screens that is 100 % of the VU1 work, in battle 24 % of the batches.

### 8.2 Second slice: the PS2All mesh seam (21 functions, 12,380 B)
Leaves `sub_49CA50`/`sub_49CAB0`/`sub_49CBD0` (filter, material colour, surface properties), `sub_4F1E20`/`sub_4F1E40` (TEX0/TEX1 from a raster), `RpAtomicPS2AllPrimTypeTransTypeSetupFunc`, the instance test `sub_4A0480`, lights `sub_4A06C0`/`sub_49FF10`/`sub_4A0430`, atomic setup `sub_4A09D0`, skin `_rpSkinMatrixUpdating`/`sub_46B8E0`/`sub_46EB90`, `openVU1SetupPktNew`, the texture cache entry `sub_4F0F30`/`RpSkyTexCacheAccessRaster`, `RpMeshPS2AllBridgeCallBack`, `sub_46EA80` (MatFX bridge dispatcher), `PS2AllNodeBody`, `AtomicDefaultRenderCallBack`. This is where a mesh draw exists as data — object matrix, light block, bone palette, material colour, TEX0/TEX1/CLAMP/TEST, VU1 code-array entry, resEntry address — just before it is serialised. A C++ version that records that tuple per mesh is what a VU1-bypass renderer for g3_generic/g3_skin consumes (decode each resEntry's clusters once, keyed by address + instance generation; draw with the recorded matrices). Harder than slice 1: MMI/VU0-heavy, 2 KiB bodies, and the bridges' A+D register pairing (topic 14 §7) must be read from the instructions.

### 8.3 After
Texture cache (c5) and render-state funnel (c6) next (they are what the D3D11 GS backend must mirror: TBP/CBP placement and the GS state per draw); then the game layer from the leaves (`sub_1A7B50`, `sub_1A8140`, `sub_317A20`, the field/battle tasks); PTank (c1, class b, needs the fake DMAC) and the DMA queue/handlers last (they are the runtime contract, topic 10).

## 9. Corrections to earlier topics, open questions, confidence

**Corrections (obs):**
1. `14` §7 "who references the 4-entry table `0x7bcf74`": it is inside RW's **Im2D dispatch descriptors** `0x7BCF70` (`open2DVU1Pkt`, programs 038/039) and `0x7BCF80` (036/037, selected by the fog bit, inf), used by the four `SkyIm2DRender*` functions; family "unknown_tbl4" = Im2D, and 039 runs in every frame with UI (§4, §6).
2. `14` §3 "texture upload … all PATH2, never PATH3": texture-cache uploads go through `sub_4D6250` (image-upload queue entry) → queue type 0x21/0x22 → a GIF (PATH3) chain; the GS trace shows BITBLTBUF/TRXPOS/TRXREG/TRXDIR on PATH3 in both field and battle (§4.4), and the dorm frame carries a 78,358-qw PATH3 IMAGE chain. `skyFillInPktForUpLoadAlignedContiguousRectangle` (the PATH2 `DIRECT` variant) is the raster-upload path outside the cache.
3. `14` §7 code-array index: index = `((tt & 0x20) >> 5) | ((tt & 0x18) >> 2)` (`RpMeshPS2AllBridgeCallBack`, §3.2); bit 4 = line primitives explains the identical entry pairs 4/5 and 6/7 only if bit 5 is ignored by the line programs (inf).

**Open:**
1. Source of transType bit 5 (`0x20`, entries 1/3 vs 0/2): set in every observed frame; the clipper selectors (`sub_4D8300`/`sub_4D8310` store `gp-16876`/`gp-20232`, read by the bridges for the clip-vector choice) are not it.
2. Per-function guest-cycle cost: the flat host profile cannot attribute EE time below 1 %; ranking §7.3 is static (loops × per-frame call counts from §4).
3. The ZBUF churn (§4.4) — confirm which state change emits it (render state 14 around every atomic in `sub_1A7B50` is the candidate).
4. PTank streamers were classified (b) by their D8/D9 scratchpad DMA; their pair tests need a DMAC fake (§7.2).

**Confidence:** draw-task order and the object → pipeline → bridge chain: high (decompiled, call graph). Pipeline assignment per object type: high (the `RpPDSGetPipe` ids are constants). Dynamic per-scene census: high for the frames sampled (complete queue walk, both halves agree); scenes not sampled (events, menus beyond the results screen, SFD) may use other programs. Hardware classification: high for (b) (each listed register access checked), medium for the boundary (a constant built with `lui 0x1000` and used as a store base would be counted). Host profile: medium (one build from 2026-10-19, ~1 ms sampling, shared machine), but the EE share is small in both segments.
