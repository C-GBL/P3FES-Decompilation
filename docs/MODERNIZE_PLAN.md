# Modernize pass: plan

Agreed with the user on 2026-10-30 (ADR-0017). It follows The Journey, the faithful decomp of all 14,500 functions,
and comes before the hand-written lift.

**Goal.** Remove the PS2 platform from under the game, one layer at a time: the game logic calls host services
directly, and nothing emulates PS2 hardware (CDVD, IOP, SIF, SPU2, IPU, GS, VU1, DMAC, INTC, timers). The game
functions keep their faithful, register-shaped form, and `EEContext` stays as their calling convention. Turning that
into natural C++ is the lift pass, which then starts from code that has no PS2 parts left.

## 1. Rules for every layer

1. **One switch per layer.** Each layer has a faithful and a native mode: `HostConfig::native` plus
   `--native files,input,...`. Each layer starts **off**, and the default changes only once its checks are green. With
   every switch off, the game runs exactly as at the baseline tag: the six recorded routes (dorm, m1, battle, fusion,
   shop, climb) keep gating that configuration byte-exactly (frames, eeMemory, gsMemory) for as long as the faithful
   path exists.
2. **The swap point is the game's own wrapper.** A layer swaps where the game calls into the platform: its CD
   wrapper, its sound command layer, its pad wrapper, its movie player, its draw submission. It never swaps at the
   hardware register. The faithful mode stays the code that is there now; the native mode is new code under
   `runtime/native/<layer>/`, called from the same game function.
3. **Each layer has a behavioural check.** Byte-identical replays end once a layer changes timing or memory layout,
   so each layer names its check (§3) before its code is written. The faithful path is the oracle for it.
4. **Re-recorded routes.** Native layers change timing (instant loading, first of all), which desyncs the old input
   recordings. **The user re-records the routes** with the native layers on (offered 2026-10-30). The new recordings
   become the gates of the native configuration, and their expected frames are re-baselined after each layer, by
   the user's decision only. The old six stay with the faithful configuration.
5. **Removal comes last.** The emulated device is deleted only when no switch can reach it any more, the native
   configuration has been the default for at least one layer after it, and the user agrees. Until then both paths
   build, and the lead gate runs both configurations.
6. **The usual rules still apply.** No GPL sources (ADR-0010); our own decoders and mixer; no game data in the repo;
   one agent per layer; no nested agents.

## 2. Order

| # | Layer | Native replacement | Why at this point |
|---|---|---|---|
| 0 | Baseline | the `journey-100` tag; the switch plumbing; a read / sound / frame logging harness | every later check compares against it |
| 1 | Disc and files | CDVD, cdvdfsv, ROFS / dvCi / ADXF sector reads → host file reads by path, finished at once | everything loads through it, and sound and movies stream through it; small; its check is exact (same bytes) |
| 2 | Input | pad, libpad / SIO2 → XInput + keyboard into the game's pad work area | tiny, visible to the player |
| 3 | Sound | SIF RPC to SDRDRV / SK / MOD on the R3000 interpreter (ADR-0014), SPU2 voices, CRI ADX / AHX streaming → native sound commands, mixer and decoders | the largest IOP user; needs layer 1 for streaming |
| 4 | Movies | Sofdec `.SFD` through IPU emulation → the same MPEG-2 core (`runtime/ipu`) called directly, plus a native audio track | needs layers 1 and 3 |
| 5 | Graphics | GS / GIF / VU1 / the RenderWare PS2 driver → the D3D11 renderer; RW Im2D / G3 draws go to native draw calls | the biggest layer and the speed win; can run alongside 1–4, since that work already exists |
| 6 | Kernel and timing | threads (fibers, ADR-0013), semaphores, interrupts, DMAC, timers, VSync → host scheduling and frame pacing | last: removable only when nothing above uses them |

## 3. The check for each layer

**0. Baseline.** Tag the commit that reaches 14,500 / 14,500 with a green lead gate. Add the `native` switch set,
all off (the lead gate shows that all-off is the old build). Add the logging hooks that layers 1–5 compare with:
- the read log: path, offset, size, byte hash, destination;
- the sound command log: the existing `--sound-log`;
- the frame dumps: the existing GS probe.

**1. Disc and files.** Native: the game's CD wrapper (`H_Cdvd` request / pump / sync, dvCi, ROFS / ADXF reads)
resolves the path through the in-ELF `#DirLst#` tables, reads the host file (ISO or extracted volumes) and completes
**at once**, as the user chose on 2026-10-30. The mods overlay becomes a lookup by path in native mode: a replaced
file is just a different host file, with no relocated LSNs. Checks:
- **(a) Identical reads.** Replay the six old routes in faithful mode with the read log on. Serve every logged read
  through the native API and compare: same bytes and same size for every read.
- **(b) Whole-disc sweep.** Read all 12,019 files through both paths: identical bytes.
- **(c) Re-recorded routes.** They run to their end with the native files layer on, and give the same scene
  sequence and the same read log (in the same order, ignoring frame numbers) as the faithful run of the same scene
  path.
- **(d) The game is the same.** Game state at matching scene points matches the faithful run, apart from the CD
  layer's own state: dvCi handles, RPC buffers and timing counters, listed in an exclusion mask that the layer
  documents.

**2. Input.** The pad work area (`H_Pad_UpdateWorkPad`'s output) is identical for the same inputs in both modes, on
every frame of every route. Plus a check by hand: you play.

**3. Sound.**
- ADX / AHX decode: PCM bit-exact against our faithful decoder, and vgmstream-cli as the second opinion.
- Each sound command (SK / libsd verb) produces the same voice parameters (pitch, volume, ADSR, loop) as the
  faithful SPU2 model.
- The final mix stays within a stated tolerance of the faithful SPU2 mix (resampling and reverb may differ), measured
  per route.
- The sound command log is identical.

**4. Movies.** Every `.SFD` decodes to frames bit-exact with the IPU path (it is the same MPEG-2 core). Its audio
track decodes bit-exact against the ADX check. A/V sync stays within one frame.

**5. Graphics.**
- While the D3D11 path is exact (640×448, no enhancements), its frames are byte-identical to the software GS on every
  route (`p3fes_gsreplay --exact`, extended to live runs).
- The EE-visible GS behaviour stays identical: CSR, FINISH, SIGNAL and readbacks.
- After that, enhancements (upscaling, the texture pack, only after asking the user) are compared within a stated
  tolerance against the exact output.

**6. Kernel and timing.** It needs no check of its own beyond the earlier ones: the re-recorded routes and all suites
stay green with the emulated devices removed, and the frame pacing holds the game's own frame rate (the
frame-telemetry log).

## 4. After this pass

The hand-written lift starts on code that calls host services only. The pilot subsystem
is field and actors, since it serves the editor and then the server (the readiness gate for multiplayer is
unchanged).
