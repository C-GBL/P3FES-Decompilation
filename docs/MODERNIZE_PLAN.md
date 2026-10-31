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
| 0 | Baseline (**done** 2026-10-30) | the `journey-100` tag; the switch plumbing; a read / sound / frame logging harness | every later check compares against it |
| 1 | Disc and files (**implemented** 2026-10-30, `--native files`, default off) | CDVD, cdvdfsv, ROFS / dvCi / ADXF sector reads → host file reads by path, finished at once | everything loads through it, and sound and movies stream through it; small; its check is exact (same bytes) |
| 2 | Input (**done** 2026-10-30, `--native input`, default off) | pad, libpad / SIO2 → XInput + keyboard into the game's pad work area | tiny, visible to the player |
| 3 | Sound (**steps 1-3** 2026-10-30, `--native sound`, default off: the ADX output, the SK sound effects, libsd) | SIF RPC to SDRDRV / SK / MOD on the R3000 interpreter (ADR-0014), SPU2 voices, CRI ADX / AHX streaming → native sound commands, mixer and decoders | the largest IOP user; needs layer 1 for streaming |
| 4 | Movies (**done** 2026-10-31, `--native movies`, default off) | Sofdec `.SFD` through IPU emulation → the same MPEG-2 core (`runtime/ipu`) called directly, plus a native audio track | needs layers 1 and 3 |
| 5 | Graphics (**steps 1-3** 2026-10-31, `--native graphics`, default off: RW Im2D; its packets without the GIF walk; the g3 pipelines at the PS2All bridge seam) | GS / GIF / VU1 / the RenderWare PS2 driver → the D3D11 renderer; RW Im2D / G3 draws go to native draw calls | the biggest layer and the speed win; can run alongside 1–4, since that work already exists |
| 6 | Kernel and timing (**step 1** 2026-10-31, `--native kernel`, default off: the inventory, the game's kernel calls as direct host calls; the (b) set behind `--native-kernel-timing host`) | threads (fibers, ADR-0013), semaphores, interrupts, DMAC, timers, VSync → host scheduling and frame pacing | last: removable only when nothing above uses them |

## 3. The check for each layer

**0. Baseline. Done (2026-10-30).** The tag `journey-100` (2265e36) is the commit that reaches 14,500 / 14,500 with a
green lead gate. The plumbing:
- **`--native LIST`** (`HostConfig::native`, `runtime/app/modernize.h`): `files`, `input`, `sound`, `movies`,
  `graphics`, `kernel`, comma separated, or `all` / `none` (the default); an unknown name is refused (exit 2). No
  layer has a native implementation yet: each switched-on layer prints `layer X has no native implementation yet;
  running faithful` at start and changes nothing else. Machine states (`state_config()`) and `capture.json` record a
  non-empty set as ` native=files,...` (absent when empty, so the baseline's strings are unchanged), the way they
  record `mods=`. A layer adds its own `if (cfg.native.files)` branch at the game's wrapper and flips its entry in
  `native_layer_implemented`. The empty set is the old build: the six-route gate on the stage-0 commit is green with
  eeMemory 0 bytes and gsMemory identical.
- **`--read-log FILE`** (`p3fes/hle/read_log.h`, `IopConfig::cd_read_sink`): one line per `sceCdRead` the game makes
  through cdvdfsv, completed or refused: vblank, LSN, sectors, bytes, guest destination, the file by path
  (`DATA.CVM:\FIELD\X.PAC` for a CVM member, `SLUS_216.21` / `LIB31\X.IRX` / `DATA.CVM` for an outer file, `-`
  for none), the byte offset in it, the file's size, and FNV-1a 64 of the bytes delivered. The path index
  (`DiscPathIndex`) walks the disc's own ISO9660 directories and each CVM's inner image (or `kDiscLayout` for the
  extracted volumes) and follows a mods overlay's relocated extents.
- **`--scene-log FILE`** (`runtime/app/modernize.h`): one line per change of (field major, minor, entry, kind,
  event id), sampled at VBLANK_START from MT_Scene's record (`*(0x7CD540)` = 0x95AFC0), the field root's work
  (`sField 0x869F60` → task +60: +20 entry, +12 event id, +60 event viewer), `gBtl` (`0x7CE3EC`) and the movie task's
  Sofdec player (`0x7CDF10`); kind = battle, else movie, else event, else field, else none.
- **`tools/ours/modernize/logcmp.py`** (run with `-I`; `--selftest`): `reads A B` (same reads in the same order,
  vblank ignored) or `reads A B --by-path` (same multiset of path, offset, size, hash); `scenes A B` (same lines in
  order, vblank ignored) or `scenes A B --coarse` (the order of distinct major / minor / kind / event only).

Both logs only read (the read log hashes the bytes cdvdfsv delivered; the scene sampler reads main RAM through
`EEMemory::ram_ptr`, not `read<>`, so not even the unmapped-access counter moves); a unit test shows guest memory
identical with and without the read sink. Which existing option each later check uses:

| Layer check | Uses |
|---|---|
| 1 (a), (b) identical reads, whole-disc sweep | `--read-log` of the faithful runs, replayed by path; `logcmp.py reads --by-path` |
| 1 (c) re-recorded routes | `--read-log` + `logcmp.py reads` (order), `--scene-log` + `logcmp.py scenes` (`--coarse` once timing differs) |
| 1 (d) the game is the same | `--snapshot-at` (eeMemory.bin, capture.json) + `tracediff snapshot` with the layer's exclusion mask |
| 2 input | `--snapshot-at` / `--watch-write` on the pad work area; `--record-input` / `--replay-input` |
| 3 sound | `--sound-log` (the command log), `--dump-wav DIR` (the mix and every ADX stream), the NullSink fingerprint in the run summary |
| 4 movies | `--dump-wav` for the audio track; the movie markers (`MarkerEdge`) and `--snapshot-at` frames |
| 5 graphics | the GS probe (`--gs-record`, `--gs-census`), `--snapshot-at` frame.png / gsMemory.bin, `p3fes_gsreplay --exact` |
| 6 kernel and timing | the replay gates, the frame-telemetry log, `--kernel-census` (the inventory) |

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

What the stage-0 logs show for this layer (dorm and battle routes, docs/INTEGRATION_LOG.md "Modernize stage 0"):
every read is a whole-sector `sceCdRead` to a 64-byte-aligned buffer, up to 512 sectors; 9 per route are not
inside one member but read a CVM itself by container offset (the CVMH header sectors 0 / 1 and the inner PVD at
sector 19 of DATA, BGM and BTL, ROFS at boot), so the native path must serve container offsets as well as members;
reads may run into the last sector's padding past the file size (`fsize`); and the ADX / SFD streams (74 of 223
reads on the dorm route, 82 of 319 on the battle route) go through the same cdvdfsv path in chunks interleaved with file loads, so their order and chunking
follow timing: check (c) compares them by path (`--by-path`) rather than in order.

**Layer 1 status (2026-10-30): implemented, `--native files` (default still off).** Where it swaps and why, streams,
mods and what is left: runtime/hle/README.md §8. The checks, every number from runs on that day:
- **(a)** `p3fes_native_files_check reads --disc input\persona3fes.iso <six read logs>`: the faithful read logs of
  the six old routes (dorm 223, m1 101, battle 319, fusion 232, shop 197, climb 1,070 reads) served through the native
  API by path and again by container offset: **2,142 / 2,142 identical** (bytes and size; 0 not found, 0 skipped).
- **(b)** `p3fes_native_files_check sweep --disc input\persona3fes.iso --extracted extracted`: **12,044 files** (27
  outer, 12,017 CVM members; 9,134,690,304 bytes) by path against the sector path, 0 differ; the 12,017 members
  against their extracted copies, 0 differ, 0 missing.
- **(c)** the old routes under `--native files` (input desync expected; same vblank caps as the gate): **m1** (no
  input) reaches `sky:11` at vblank 83 instead of 379 with the same 101 reads in the same order and the same scene
  log; **shop** passes all 12 coarse scenes and its 135 file loads are identical by path (streams differ in chunking
  and length); **dorm** 12 of 19 coarse scenes (desyncs in the dorm events), **battle** 8 of 14 (stays in event 139 at
  51/1), **fusion** 5 of 7 (stays at 32/2), **climb** 9 of 32 (stays in Tartarus 21/0). The new recordings make (c)
  a real check: guide below.
- **(d)** m1 at `sky:11`, faithful against native (`tracediff snapshot`): 6,769 bytes in 1,391 runs differ;
  `tools/ours/modernize/layer1_cd_mask.txt` (libcdvd's client, the ADX fs-thread stack, SRD, the dvCi handle table,
  CRI's ADXF / ROFS handle work, sCdvdCache's slot order, H_Cdvd's request ring) removes 919 bytes / 321 runs. The
  5,850 bytes left are timing, not files: the run reaches the point 296 vblanks earlier (kwln frame counters 0x7CE09A
  / 0x7CE108, the SK sound sequencer 0x782F50..0x7886BA, the pad work 0x822DD0..0x823425, 0x849018, the bss block
  0x95D410 (2,496 B), stacks and heap). At matching scene points of re-recorded routes the same split applies.

**Recording the native routes (for the user).** Play each route in a window (keyboard or gamepad) with the native
files layer on and the pad recorded; the memory card is the one the old route starts from:

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native files ^
        --memcard <card> --record-input config\inputs\native\<route>.txt --scene-log config\inputs\native\<route>.scenes.txt

| route | `--memcard` | must pass through (field major/minor, kind; from the faithful run) |
|---|---|---|
| dorm | `new` | title (0/0) → opening movie → 15/6 field and its three events → two movies → the dorm 7/2 field → its event |
| m1 | — | no recording needed: it has no input (`--snapshot-at sky:11` already runs natively) |
| battle | `extracted\_ours\cards\tartarus.ps2` | title → movie → 32/2 → 0/2 → 51/1 field and event → a battle (251/1) |
| fusion | `extracted\_ours\cards\fusion.ps2` | title → movie → 32/2 → 0/2 → the Velvet Room 8/3 (a fusion) |
| shop | `extracted\_ours\cards\shop_buy.ps2` | title → movie → 7/2 → 7/9 → 1/1 → 8/1 → 8/4 (a purchase) |
| climb | `extracted\_ours\cards\full_battle.ps2` | title → movie → 7/2 → 32/2 → Tartarus 21/0 with three battles (221/1) → 51/4 with a battle → 51/4 |

Save each `<route>.txt` (and its `.scenes.txt`) in `config\inputs\native\` and note the vblank where the route should
end (the last scene's line in the scene log); the lead then adds the six as the native configuration's gate
(`--native files --replay-input config\inputs\native\<route>.txt --snapshot-at vblank:<end>`), the old six stay the
faithful gate.
**2. Input.** The pad work area (`H_Pad_UpdateWorkPad`'s output) is identical for the same inputs in both modes, on
every frame of every route. Plus a check by hand: you play.

**Layer 2 status (2026-10-30): done, `--native input` (default still off).** The game's pad wrapper asks the host's pad
(`runtime/native/input`, `p3fes/native/input_service.h`) instead of libpad: no SIF RPC to PADMAN, no DMA'd pad frame,
no SIO2. Swap points `H_Pad_Init` 0x103000 and `H_Pad_UpdateWorkPad` 0x103110, the game's only libpad callers; what the
game uses (analog sticks, no pressure, vibration through `scePadSetActDirect` -> XInput rumble) and why there:
runtime/hle/sif/README.md §10. The pad work is 0x7E0700..0x7E0A3F (read buffer, records 0x7E09B0 + 54 x port, shared
block) and the vibration state 0x7CDE90..0x7CDEAB; layer 1's "pad work 0x822DD0..0x823425" is unnamed bss that only
follows `gPadFlags` in the symbol order. The checks, every number from runs on that day (`--vblank-dump` of those ranges
at every VBLANK_START, `logcmp.py dumps`; the gate's end points, `--gs-backend d3d11 --gs-exact`):
- **(1) Pad work, faithful vs `--native input`** (files faithful, the same replays): identical on every vblank from
  vblank 362 on in all six routes -- m1 380, dorm 4,900, battle 6,150, fusion 6,300, shop 4,100, climb 39,820 vblanks.
  Before the first frame (the first RW flip is at vblank 365) the boot loop is not vblank-paced and runs more
  iterations natively (the native answers cost fewer guest cycles): 3 vblanks differ in five routes (349, 352, 359:
  only the scratch byte 0x7E0700, which `H_Pad_UpdateWorkPad` sets to 0xFF before its read, sampled inside the
  faithful `scePadRead`), 5 in shop (351, 359, 361 the same byte; 346 / 347 an auto-repeat counter, 0x7E09DD and its
  copy 0x7E096D, one step ahead, under the recording's first press).
  The routes stay exact for the player: the scene logs are byte-identical with their vblanks (1 / 23 / 16 / 8 / 17 /
  40 lines), and frame.png and gsMemory are identical at all six end points. eeMemory differs by 319 / 407 / 380 / 358
  / 408 / 480 bytes (m1, dorm, battle, fusion, shop, climb); the mask (2) takes 190 of them in every route, the rest
  (129 / 217 / 190 / 168 / 218 / 290) is the boot loop's iteration count: kwln_frame is 9,104 higher in five routes
  (shop 9,097; m1 5,520 vs 14,624), and the RPC packet ids of the libcdvd / SRD / heap / SDR clients, CRI's time stamps, the CPU
  load meter and stack residue follow it.
- **(2) Mask** `tools/ours/modernize/layer2_pad_mask.txt` (4 ranges, 190 bytes differ in them on every route): the two
  DMA buffers 0x7E0740..0x7E093F, libpad's init flag 0x782748, the SIF command handler slot scePadInit2 installs
  (0x966BA8..0x966BB7: `_pad_intr_hdr`, $gp) and libpad's EE client 0x96DCC0..0x96DF7F (the two RPC clients, the
  port records, the state words, the request buffer). (Layer 1's mask range 0x7E0700..0x7E09FF is this pad state, not
  H_Cdvd's: its comment is corrected.)
- **(3) Both layers**: `--native files,input` runs m1 to `sky:11` at vblank 82 (files alone: 82) and dorm to vblank
  4,900 (54 s wall each way); the pad work is identical to `--native files` alone on all 82 / 4,900 vblanks, the dorm
  scene log is the same 15 lines, and it keeps the first 12 of the faithful run's 19 coarse scenes, as files alone
  did (the old recording desyncs under instant loading).
- **(4) Tests**, MSVC and clang-cl, `ctest --timeout 1200`: `p3fes_app_tests` 58 cases (8 new in
  `test_native_input.cpp`: answers and latency, buttons, sticks, keyboard / XInput into a report, mode change,
  actuators and rumble, unplugging, two ports, state round trip; 1 in `test_modernize.cpp`: `--vblank-dump`), `p3fes_game_tests`
  input_native 2 (H_Pad_Init / H_Pad_UpdateAll / H_Pad_UpdateWorkPad on the service), field8_sys 9, font2 10,
  sweep5a 3 (the faithful pair tests), `p3fes_sif_tests` 71: all pass. Machine state: m1 under `--native input` saved
  at vblank 300 and resumed reaches `sky:11` with eeMemory and gsMemory identical to the straight run.
- **(5) Faithful configuration**: `gate.ps1 -Slice -NoSuites -FastGs -Jobs 3 -Routes 'dorm,m1,battle,fusion,shop,climb'`
  on the layer's code: GATE: PASSED, eeMemory 0 bytes and gsMemory identical on all six.
- Vibration is used: the battle route sends 3 actuator packets, one with a motor on (the other routes 1, at start).
  Port 2 is opened and read but `H_Pad_UpdateAll` clears its words every frame: only port 1 reaches the game.

**Try it (for the user): a controller and the keyboard with the native pad.** Plug in an XInput pad (or use the keys of
`config\input.ini`: arrows, I / L / K / J = Triangle / Circle / Cross / Square, ENTER = Start, W A S D = left stick):

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native input

(your usual memory card; `--memcard new` for a fresh one). Add `--native files,input` for instant loading too, `--input-config FILE` for another key map, `--record-input F` /
`--replay-input F` as usual; vibration (battles, some events) should rumble the pad.

**3. Sound.**
- ADX / AHX decode: PCM bit-exact against our faithful decoder, and vgmstream-cli as the second opinion.
- Each sound command (SK / libsd verb) produces the same voice parameters (pitch, volume, ADSR, loop) as the
  faithful SPU2 model.
- The final mix stays within a stated tolerance of the faithful SPU2 mix (resampling and reverb may differ), measured
  per route.
- The sound command log is identical.

**Layer 3 status (2026-10-30): steps 1-3 done (the ADX output; the SK sound effects and libsd), `--native sound`
(default still off).** Step 1 below; steps 2 and 3 after its checks. BGM, voices
and the movies' audio -- everything CRI's ADX players (ADXT, Sofdec's audio, AHX / AIX) produce -- play on the host:
`runtime/native/sound` (`NativeSound`, library `p3fes_native_sound`), seam `p3fes/native/sound_service.h`, game side
`game/src/cri/rna_native.cpp` (`p3fes/game/sound_native.h`); design in runtime/audio/README.md "Native sound". No SIF
RPC reaches CRI_ADXI (kwlnInitPS2Systems no longer loads it: 14 IOP modules instead of 15), no DTR SIF DMA, no DTX /
SJX exchange, no PSM model. Steps 2 and 3 (the SK sound effects and the libsd remote calls, below "Steps 2 and 3") put
the SK stack on native code as well. The native ADX mix enters the SPU2 mixer's stream input where the PSM model's
passes did, so the host output is unchanged (XAudio2 windowed, NullSink / `--dump-wav` headless).
- **Swap point**: CRI's PS2 output layer PS2RNA, under the ADXRNA interface every CRI player writes its decoded PCM
  into: its eight functions that touch the IOP (Init 0x55FF70, Finish 0x560698, Create 0x560758, Destroy 0x560AF8, the
  transfer switch 0x560C88, GetNumData 0x560EB0, GetNumRoom 0x560F18, ExecServer 0x561138). Why there: one point serves
  every ADX producer (the game's BGM manager through ACSS, its direct ADXT calls, the movie player, AIX), every
  ADXT / ACSS answer the game reads stays CRI's own code, and below it is only PS2 glue (SIF DMA, DTX RPC, the IOP
  mixer). One level higher (ADXT) would re-implement the players and their state machine, and the movie player's
  stream-joint input; the decode is CRI's EE decoder, game code with no PS2 part, kept unchanged.
- **Streams**: the ADX / SFD reads stay where layer 1 puts them (ADXF / dvCi; native with `--native files`); the
  native output takes the decoded PCM from the players' output joints.
- **Timing**: the native output keeps the faithful device's cadence (runtime/audio/README.md): one pass per vblank
  after the vblank-end, DTX's one block in flight, DTR's one-chunk transfers, the 16 KiB buffers' SJUNI chunk lists.
  That is what keeps the scene logs identical below; a version without it (consumption at once) moved scenes by 2
  vblanks and desynced the battle recording.

The checks, every number from runs on that day (the gate's old routes and end points, `--gs-backend d3d11 --gs-exact`;
faithful vs `--native sound`):
- **(1) ADX decode.** The stream PCM the output consumed (`--dump-wav` `stream_*`) is identical between the modes on
  every stream of m1, dorm, battle, fusion and shop (3,069,440 / 0 / 4,181,248 / 3,767,808 / 1,929,216 samples over the
  common length; 52 streams). Against our decoder (`p3fes_native_sound_check streams`): 37 of the 52 streams match a
  file the run read (BGM.CVM ADX, voice AFS members) and all 37 are bit-exact (8,044,436 samples faithful, 8,042,388
  native); 6 are movie audio (inside the SFD mux) and 9 match no file from its start (not resolved: in-memory or
  processed sources). Whole-disc sweep: 12,797 ADX (223 BGM files, 12,574 in DATA incl. AFS members) decode to their
  headers' sample counts. vgmstream-cli `-i` on a sample of 27: 22 identical sample for sample; 5 differ in 219 to 760
  samples each (max |d| 9 to 20,210), where our decoder is the one that matches the game's.
- **(2) Output parameters.** The `RNA start` / `RNA stop` lines (slot, sfreq, channels, core, volume L / R, stream)
  are identical with their vblanks on m1 / dorm / battle / fusion / shop (0 / 16 / 61 / 11 / 11 events); the
  output's timeline frames are 0..5 frames earlier (the output's pass grid starts 4 frames earlier: the native init
  makes no IOP round trips). The SK / libsd lines (the effects, still faithful) are identical from the first frame on
  in dorm and m1 but for the KON / CORE frame column (-1); in battle / fusion / shop 32 / 22 / 48 of 3,510 / 3,342 /
  2,295 lines differ: a key-on that lands in the neighbouring 240 Hz SK tick takes another voice.
- **(3) Mix.** Metric (`mixcmp`): per-channel RMS level of the whole `mix_48k.wav` in dB, and 0.5 s windows aligned
  by the lag (+-1,024 frames) minimising the squared difference, residual = RMS(f - n) / RMS(f) in dB. Levels: dorm
  -0.011 / -0.011, battle +0.006 / +0.005, fusion -0.003 / -0.001, shop -0.001 / 0.000 dB; m1 silent in both
  (identical files). Windows bit-exact after the lag: dorm 82 / 119, battle 68 / 158, fusion 105 / 161, shop 39 / 91;
  median residual exact / -30.2 / exact / -23.3 dB, 90th percentile -11.4 / -8.1 / -10.2 / -9.1 dB. The rest is the
  ADX stream sitting 4 frames (0.08 ms) earlier against the SK voices plus the moved key-ons of (2). ADX alone
  (`--sk constants`, dorm): 117 / 120 windows bit-exact at lag 0, -0.011 dB; the 3 others are the ends of three
  movies, one 512-frame pass shorter (the native destroy comes ~29,000 cycles earlier, without the RPC round trip).
- **(4) The game's view.** Scene logs identical with their vblanks on m1, dorm, battle, fusion and shop (1 / 23 / 16 /
  8 / 17 lines), frame.png identical at all five end points. eeMemory differs by 4,649 / 8,585 / 4,938 / 75,904 /
  4,870 bytes; the mask `tools/ours/modernize/layer3_sound_mask.txt` (DTR / DTX / SJX / SJUNI / PSJ objects and their
  EE buffers, the PS2RNA records' PSJ / DTR / IOP fields, the urpc buffers, the IOP addresses of the SK banks) takes
  1,681 / 1,864 / 1,956 / 1,887 / 1,847 of the differing bytes in 0x770000..0x9A0000; what is left there is timing as
  in layers 1 / 2 (the bss block 0x95D410, 2,486 B; the RPC packet ids of every SIF client; the SK track ring;
  kwln_frame is 10 higher), and the rest of RAM is stacks and heap contents. **Climb**: the old recording desyncs. The
  ADXT / PS2RNA state is identical every vblank to 4,239 (`--vblank-dump` of the ADXT pool and the PS2RNA table; one
  old / new byte differs at 2,718-2,719), then the game starts the field BGM's player 2 vblanks later (vblank 4,242
  instead of 4,240; RNA start 4,255 instead of 4,253), an EE-side decision taken before any sound answer differs; the
  replay then leaves the route at 4,728 (13 of the 40 scene lines). The EE heap already differs at vblank 3,975 (a
  battle model loaded at 0x181D400 instead of 0x181D340). Taking CRI's four IOP heap blocks anyway (SK bank addresses
  as faithful) moves the BGM start back but desyncs the battle route instead, so it is not done; the climb needs the
  user's native recording (rule 4). (Climb runs crash at their end point when several run in parallel, faithful too:
  the faithful climb process reaches ~15 GB; alone they finish.)
- **(5) Combined** `--native files,input,sound`: m1 reaches `sky:11` at vblank 82 as with `files,input`, silent in
  both, frame.png identical. The user's native dorm recording (`--memcard new`, to vblank 4,226, 28 s wall): the 19
  scene lines identical to `--native files,input` with their vblanks, frame.png identical, the same 22 RNA events,
  audio present (2,572,927 audible frames of 3,382,784; `files,input`: 2,573,455), 14 IOP modules, no DTX request.
- **(6) Tests**, MSVC and clang-cl (Release), `ctest --timeout 2400`: `p3fes_app_tests` (5 new cases in
  `test_native_sound.cpp`: the PSM volume law over all 492,032 inputs, one block in flight and the answer, the mixer's
  rate conversion / gains / clip / silence / pause gaps / discard / tap sessions / events, the transfer switch and
  restart rule, the state round trip; `test_modernize.cpp` updated), `p3fes_game_tests` sound_native (PS2RNA Init /
  Create / transfer / ExecServer / GetNumData / GetNumRoom / Destroy on the ELF's code with the service) and the
  faithful pair tests of the hooked files libs14 / libs24 / libs25 / libs26 plus field8_sys / sweep5a,
  `p3fes_audio_tests`, `p3fes_sif_tests`, `p3fes_hle_tests`: 11 / 11 entries pass on both compilers.
- **(7) Faithful configuration**: `gate.ps1 -Slice -NoSuites -FastGs -Jobs 3 -Routes 'dorm,m1,battle,fusion,shop,climb'`
  on the layer's code: dorm, m1, battle, fusion and shop pass (expected frames, eeMemory 0 bytes, gsMemory
  identical); the climb process crashes at its end point (vblank 39,820, access violation in memmove while the
  snapshot is written), so GATE: FAILED. Main's own build (`build\lead-w3`, bb3b1ba's lead gate) crashes the same way
  on the same machine run alone (exit 0xC0000409 after 913 s, peak working set 2.0 GB; this build 0xC0000005 after
  1,056 s, 2.0 GB): an existing climb-end problem, not this layer's (its faithful path only adds null-service checks).

**Steps 2 and 3 (2026-10-30): the SK sound effects and the libsd remote calls on native code.** The six Standard Kit
modules (SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN: the 35-opcode SE sequencer, the hardware synth, the 240 Hz
tick, SDRDRV's libsd remote dispatch) run as native C++ instead of on the R3000 interpreter: `runtime/native/sound/sk`
(README there), `NativeSk` with the 71 imports they call. Their code (301 functions, one statement per instruction) is
generated **at build time** by `tools/ours/modernize/skgen.py` from the user's LIB31 files (CMake `P3FES_LIB31_DIR`;
derived from game data, so never committed, like `recomp/generated`); the IRX files are read for their initialised data
only, nothing of them is loaded as code or interpreted. libsd stays the IOP model's LibsdHle over the SPU2 voice model
(called by ordinal, `iop/libsd_hle.h libsd_call`), so the voices go into the same mixer step 1's ADX output uses.
- **Swap point**: SDRDRV's RPC boundary (0x80000701) and loadfile's module loads, reached by the game's own libsdr
  unchanged (`--native-sk sif`, the default): kwlnInitPS2Systems' loads of the six modules start the native modules at
  the instants the interpreter would load them (`srv_sdr.cpp on_module_load`), and every `sceSdRemote` request -- the
  libsd codes 0x8010 SetParam, 0xE620 CallbackInit and every SK block 0x90F0 (SOUND_Control / Send, HSYNTH / SESQ Bind,
  SESQ_Control / Status), all of the game's sound commands -- goes to SDRDRV's native handler on its RPC thread, at the
  instant the interpreted one would run. Why not at the game's wrapper (`sceSdRemote` itself, `--native-sk direct`,
  implemented: the module loads and sceSdRemote's three sceSifCallRpc calls go to the service, no SIF): every
  `sceSdRemote` is a blocking sceSifCallRpc (the per-frame SOUND_Control(3, 0x80) from kwlnUpdate included), and while
  the calling thread waits for the RPC end the EE's other threads run; without that wait the battle recording desyncs
  (below, (12)). Step 1's lesson again: the native layer must keep the faithful cadence; here the cadence is the RPC
  itself, which is the game's own code.
- **What still runs on the IOP model, and why**: the SIF RPC transport (sceSifCallRpc's packets, SDRDRV's binding,
  loadfile's answers) -- the game's thread timing depends on it, as said; the IOP RAM -- the game's H_Sndcom uploads the
  HD / SQ banks there itself (sceSifAllocSysMemory + SIF DMA) and passes their IOP addresses in the binds, and the
  native modules keep their data and work areas at the faithful addresses; libsd, the SPU2 voice model and the mixer
  (`LibsdHle` / `Spu2Voices` / `Spu2Mixer`, host models owned by the IOP core, the mixer step 1 feeds). Reverb is
  rendered in neither mode (the effect registers are stored, the dry path played: runtime/audio/README.md "Reverb"), so
  step 3 has no reverb work that the faithful path does. All three go with layer 6 (kernel and timing), when the EE's
  threads stop depending on the RPC wait and the routes are re-recorded (rule 4).

The checks, every number from runs on that day (the gate's old routes and end points, `--gs-backend d3d11 --gs-exact`;
the native SK vs the interpreted one = `--native sound` vs `--native sound --native-sk off`, and vs all-faithful):
- **(8) Oracle pair test** (`tests/sif/test_sk_native.cpp`): the native stack and the interpreted modules side by side,
  each on its own IOP RAM and libsd, at the Pcsx2 placement: the H_Sndcom bring-up with both banks (COMSE on port 0,
  BSE on port 1: 340 requests, 65 libsd events, 587 ticks) and a storm of 1,500 random plays / stops / status / volume
  changes on both ports at random instants (2,098 requests, 3,084 libsd events, 1,423 ticks; 33.9 M instructions on the
  interpreter side): every reply, every libsd event (KON / KOFF / core write) with its instant, the heaps' block maps
  and every block's bytes identical. Not compared: the interpreter's RPC-return trampoline word and the 290 bytes the
  game's second SKHSYNTH leaves in its freed image block (the interpreter loads its image there; natively the same
  block is only taken and freed).
- **(9) SK command lines** (requests: args + vblanks + results): the native stack against the interpreted one, the whole
  `--sound-log` is byte-identical with every cycle on m1 / dorm / battle / fusion / shop (5,880 / 8,433 / 9,444 / 9,226
  / 8,178 lines: 5,862 / 8,174 / 8,975 / 8,885 / 7,830 requests, 17 / 242 / 407 / 329 / 336 libsd events, 0 / 73 / 156
  / 106 / 108 key-ons). Against all-faithful, the requests after the boot loop (vblank 400; the boot loop's count of
  per-iteration SOUND_Control lines follows step 1's EE speed) are identical with their vblanks and results but for
  4 / 4 / 10 / 4 / 4 bind lines that carry step 1's IOP bank addresses (0xBD400 / 0xCA500 instead of 0x103800 /
  0x110900, the heap class of (4)) or stale argument words; the voice events are identical in content on m1, dorm and
  battle (the frame column is step 1's -1 / -2) and differ in 9 / 20 lines on fusion / shop, step 1's
  neighbouring-tick class (2).
- **(10) Mix**: `mix_48k.wav` byte-identical to the interpreted SK's on all five routes; against all-faithful
  (`p3fes_native_sound_check mixcmp`, the metric of (3)): levels dorm -0.011 / -0.011, battle +0.006 / +0.005, fusion
  -0.003 / -0.001, shop -0.001 / 0.000 dB; non-silent 0.5 s windows bit-exact after the lag dorm 86 / 122, battle 70 /
  161, fusion 106 / 162, shop 40 / 93, median residual exact / -46.2 / exact / -41.1 dB, 90th percentile -13.4 / -8.8 /
  -10.8 / -10.3 dB -- all of it step 1's (the ADX stream's offset against the voices).
- **(11) The game's view**: scene logs identical with their vblanks and frame.png identical at all five end points
  (against all-faithful and against the interpreted SK); eeMemory and gsMemory byte-identical to the interpreted SK's
  on all five, so step 1's mask `tools/ours/modernize/layer3_sound_mask.txt` is the whole difference to all-faithful:
  steps 2-3 add no entry.
- **(12) `--native-sk direct`** (no SIF): m1, dorm, fusion and shop keep their scene logs and frames; the battle
  recording desyncs -- every request is identical to the interpreted run's (vblanks, payload, results) up to vblank
  1,461, where the game issues an SE (SESQ_Status, stop, play) 8 vblanks later, and the battle starts at vblank 5,054
  instead of 4,604. Kept as an option for the re-recorded routes and layer 6.
- **(13) Combined** `--native files,input,sound`: m1 reaches `sky:11` at vblank 82; the user's native dorm recording
  (`--memcard new`, to vblank 4,226): sound log, mix, frame, gsMemory and scene log byte-identical to `--native-sk off`,
  audio present (2,572,927 audible frames of 3,382,784), no hang, no fault; 0 instructions interpreted, 16,918 native SK
  ticks, 2,484 SDRDRV requests answered natively.
- **(14) Tests**: `p3fes_sif_tests` (the pair tests of (8) and the generated code's own check: every function found by
  its address, a module whose text changed by one bit is refused), `p3fes_game_tests` sound_native (the direct branch of
  sceSdRemote on the ELF's code: libsd and SK requests reach the service with the bytes sceSifCallRpc would send, the
  reply lands in the receive buffer) and the pair tests of the hooked files (libs24, sweep5a, sweep5b). Every suite,
  `ctest --timeout 2400` with the user's data: MSVC Release 209 / 209, clang-cl Release 208 / 208 entries pass. Machine
  state: dorm under `--native sound` saved at vblank 3,500 and resumed reaches vblank 4,900 with eeMemory, gsMemory and
  frame.png identical to the straight run.
- **(15) Faithful configuration**: `gate.ps1 -Slice -NoSuites -FastGs` on dorm, m1, battle, fusion, shop: GATE: PASSED
  (expected frames, eeMemory 0 bytes, gsMemory identical; the climb runs in the lead's gate).

**Try it (for the user): the game's music, voices, movie sound and sound effects on native code.**

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native sound

(your usual memory card; the build must have been configured with your `extracted\disc\LIB31`, which a tree in the
main checkout finds by itself: the log says "the SK sound effects ... run on native code"). Everything should sound
exactly as before -- the effects now come from the native SK stack, with no IOP module interpreted. Add
`--native files,input,sound` for the native layers so far, `--dump-wav DIR` to keep the mix and every ADX stream,
`--sound-log FILE` for every sound command and voice event; `--native-sk off` gives the interpreted SK for comparison.

**4. Movies.** Every `.SFD` decodes to frames bit-exact with the IPU path (it is the same MPEG-2 core). Its audio
track decodes bit-exact against the ADX check. A/V sync stays within one frame.

**Layer 4 status (2026-10-31): done, `--native movies` (default still off).** The movie player's video decodes on the
host: CRI's SFD video decoder, on its sceMpeg path, calls a native MPEG decoder (`runtime/native/movies`, library
`p3fes_native_movies`; seam `p3fes/native/movies_service.h`; game side `game/src/cri/sfd_native.cpp`,
`p3fes/game/movies_native.h`) instead of Sony's libmpeg driving the IPU. No IPU command, no DMAC channel 3 / 4
transfer, no sceMpegInit / sceIpuInit at boot. Design (the decoder, the ring, the timing model, the scope):
runtime/ipu/README.md "Native movies".
- **Swap point**: the Sofdec player's own glue to libmpeg + the IPU, at the calls it makes: sceMpegInit (sub_594B88),
  sceMpegCreate and its four callbacks (sub_594C38), sceMpegReset / Delete (sub_595060), sceMpegGetPicture / RAW8
  in its picture call (sub_595390), and its five DMA helpers over the video-input ring (sub_5941A8 reset, sub_5944A8
  flush, sub_5946A8 / sub_5947A8 stop / restart, sub_594AC0 destroy). Why there: one level below is the IPU's and
  the DMAC's registers (rule 2); one above (the SFD decode step) would re-implement CRI's frame pool, skip rules and
  timing. Everything else of Sofdec runs its faithful body: the demux, the feed into the ring and its free space, the
  start-code counter, the frame pool, the time codes, the display.
- **The decoder** is libmpeg's picture loop (headers, slices, macroblocks, motion compensation, the display order)
  over the IPU core's own functions (`p3fes/ipu/mpeg2.h`: VLC tables, the BDEC coefficient loop, IQ, IDCT, CSC). The
  same decoder drives the emulated IPU (`IpuEngine`: IpuCore with FDEC / VDEC / BDEC / SETIQ / CSC, as libmpeg drives
  it) for check (1). libmpeg's motion compensation has one rounding quirk (`_rix_111`, kept): found by the in-game
  comparison, it was all 162 differing macroblocks of the first B picture (bidirectional, the backward vector
  half-pel in x and y) before.
- **Audio**: the movie's ADX track is not this layer's: CRI's own ADX player decodes it on the EE and plays it through
  PS2RNA, faithful or layer 3's native output (`--native sound`). It works with and without `sound` (check 3).
- **Timing**: the picture call charges the guest the cycles the faithful call takes for the same work (a per-call +
  per-macroblock-kind model, least squares over the 90 faithful calls of the dorm / battle / fusion / shop routes:
  mean error 3.4 %, at most 17.5 %; x 0.91 because the faithful span includes other threads), with check points.
  Without it (an instant decode) the player was ready 2 vblanks early (the 0x7CDF10 marker at 850 instead of 852,
  4280 instead of 4282 on dorm) and decoded 3 more pictures ahead.

The checks, every number from runs on 2026-10-30 / 31 (the gate's old routes and end points, `--gs-backend d3d11
--gs-exact`; `op` = a boot without input or card to the opening movie, `--memcard none --input-script
560:left:4,580:cross:4`, snapshot at vblank 3000 mid-movie and 6600 at the title; faithful vs `--native movies`):
- **(1) Every .SFD, native vs the IPU path.** `p3fes_native_movies_check sweep --extracted extracted --jobs 3
  --file-timeout 1800`: **42 files** (41 in DATA\SFD, DATA\SOUND\P3CT003.SFD; 39 MPEG-1, 3 MPEG-2), 2,068,389,888
  bytes (video ES 1,844,332,662), **107,893 pictures (I 7,701 / P 29,612 / B 70,580), 0 differ**, 0 timeouts, every
  file ends at its sequence end (slowest file 230 s; 2,542 s CPU in all). And against the game's own libmpeg + IPU
  (`--movie-log`: one line per picture call, the frame's FNV-1a 64): every picture call's frame identical in order --
  dorm 55, battle 20, fusion 10, shop 5, m1 0 (no movie), op to vblank 3000 945, op to 6600 **all 2,670 pictures of
  P3CTOP2** and its end (all MPEG-1). MPEG-2 in the game: op to 3000 with a mods overlay that puts P3CTOP.SFD (MPEG-2,
  640 x 368) in P3CTOP2's place (`--mods`, the user's own disc bytes, scratch only): 946 picture calls identical in
  order, markers, scene log, frame.png and gsMemory identical.
- **(2) The game is the same.** Movie markers (`MarkerEdge`: flag 5127 and the player object, with vblank and cycles)
  identical on dorm (18 edges), battle, fusion, shop, m1, op 3000 and op 6600. Scene logs identical with their
  vblanks (24 / 17 / 9 / 18 / 2 / 4 / 5 lines). frame.png identical at all seven end points; gsMemory identical on
  dorm, battle, shop, m1, op 3000, and differs on fusion (152 8-KiB pages of the texture area: RenderWare's texture
  ring placed differently -- fusion is layer 3's timing outlier too) and op 6600 (2 pages at the top of VRAM: the
  title's texture ring head, skyTexCache 0x77F204, 3 entries on). The ring record (head / queued / count / abort)
  after every picture call is the faithful one on dorm / battle / fusion / shop (90 of 90 calls), 2,621 of 2,670 on
  op 6600; the calls land within +-1 vblank (0 on the four routes); the SFD frame pool (`--vblank-dump` of its 16
  records) differs on 93 of 6,600 vblanks of op 6600 in 35 bytes, all decode-side fields (the shown field never).
  eeMemory (tracediff, dead stacks excluded): dorm 13,509 / battle 10,107 / fusion 80,908 / shop 9,752 / op 6600
  18,818 bytes; the mask `tools/ours/modernize/layer4_movies_mask.txt` (MWSFD's two scratchpad swap images, which
  hold libmpeg's macroblock work; the saved sceMpeg record and the error callback's words) leaves 3,792 / 3,276 /
  69,885 / 3,057 / 5,732: timing as in layers 1-3 (the bss block 0x95D410, 2,487 B on every route; the ADX fs
  stack; sCdvdCache's slots; RenderWare's DMA pointers) and dead heap of the movie's work. Mid-movie (op 3000)
  1,310,521 bytes differ, 1,298,681 of them the layer's own: libmpeg's work area (its decoder state and three RAW8
  reference frames, 1,290,498), the ring's DMA tags (1,540), the saved D4 / D3 / IPU registers (21), the sceMpeg
  record's libmpeg words (6: its flags word and work pointer), the swap images (6,616). The IPU sees nothing natively (capture.json `ipu`, op 3000:
  0 commands, 0 qwords; faithful: BDEC 815,646, VDEC 3,255,586, FDEC 1,198,078, CSC 1,890, 26.5 M qwords in), and the
  run's audio fingerprint (NullSink hash 0x83615E491DBA2575, 1,546,246 non-silent frames) is the faithful one.
- **(3) Audio track.** `--native movies,sound --dump-wav`, op to 3000: the movie's ADX stream (stream_0001, 48 kHz
  stereo) is byte-identical to the faithful run's, and both are bit-exact against our ADX decoder on P3CTOP2's 0xC0
  track (`p3fes_native_movies_check audio`: 1,509,888 frames, 0 samples differ; 41 movies have an ADX track, all
  decode). Pictures, markers, scene log, frame.png and gsMemory as in (2).
- **(4) Combined** `--native files,input,sound,movies`: m1 identical to `files,input,sound` (sky:11, no movie). The
  user's native dorm recording (`--memcard new`, to vblank 4226, 90 s wall, no hang): against `files,input,sound`
  the 27 picture calls identical, the 20 scene lines identical with their vblanks, frame.png and gsMemory identical,
  markers identical; audio present (2,572,927 audible frames of 3,382,784, as layer 3's), the movie's stream
  bit-exact against P3CTOP2's track (39,424 frames); 14 IOP modules.
- **Machine state**: op under `--native movies` saved mid-movie at vblank 2000 and resumed reaches vblank 3000 with
  eeMemory, gsMemory and frame.png identical to the straight run (the decoder's references and the ring's read
  position are in the state's `native-movies` section).
- **(5) Tests**, MSVC and clang-cl (Release), `ctest --timeout 2400`: `p3fes_app_tests` (4 new cases in
  `test_native_movies.cpp`: MPEG-1 and MPEG-2 streams built in the test through both engines, picture for picture;
  libmpeg's display order; the I picture's pixels, column-major order and the CSC; plan()'s byte counts suffice;
  the service over a ring, its state round trip; `test_modernize.cpp` updated), `p3fes_game_tests` movies_native (the
  ELF's viBufCreate / feed / flush / restart / stop / destroy with the service and the native picture call through a
  whole movie, P3FCT007's 270 pictures, against the decoder on the elementary stream, the end-code path at its end,
  no IPU / DMAC access; 3,469 assertions) and every other suite: MSVC 210 / 210 ctest entries pass (4,228 s),
  clang-cl 209 / 209 (3,464 s; `p3fes_recomp_emit_subset` skips by design on both); `p3fes_app_tests` 67 cases.
- **(6) Faithful configuration**: `gate.ps1 -Slice -NoSuites -FastGs -Jobs 3` on the layer's code (routes dorm, m1,
  battle, fusion, shop): GATE: PASSED, expected frames, eeMemory 0 bytes and gsMemory identical on all five. The
  climb was not run (the lead's merge gate runs it; layer 3 found its end-point crash on this machine, faithful too).
  The faithful path only adds null-service checks and the movie log's read-only hook.

**Try it (for the user): the movies on the host's decoder.**

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native movies

(your usual memory card). The opening movie and every event movie should look and sound exactly as before; add
`--native files,input,sound,movies` for all the native layers so far, `--movie-log FILE` for one line per decoded
picture.

**5. Graphics.**
- While the D3D11 path is exact (640×448, no enhancements), its frames are byte-identical to the software GS on every
  route (`p3fes_gsreplay --exact`, extended to live runs).
- The EE-visible GS behaviour stays identical: CSR, FINISH, SIGNAL and readbacks.
- After that, enhancements (upscaling, the texture pack, only after asking the user) are compared within a stated
  tolerance against the exact output.

**Layer 5 status (2026-10-31): steps 1-3 done (RenderWare Im2D; the host's packets without the GIF walk; the g3 pipelines at the PS2All bridge seam -- steps 2 and 3 below the step 1 checks), `--native graphics` (default still off).** Every Im2D
draw of the game -- sprites, glyphs, windows, fades, the HUD, the movie quad -- is drawn by the host instead of VU1
program 039: `runtime/native/graphics` (`NativeIm2D`, library `p3fes_native_graphics`), seam
`p3fes/native/graphics_service.h`, game side `game/src/render/render_im2d.cpp`; design in `native_im2d.h`.

*The draw map* (how the game's draws reach the GS; docs/ANALYSIS/22_rendering.md §1-§6 for the functions). Draw tasks
(`kwlnTaskMain`, ascending priority) → 3-D: model draw `sub_317A20` / world `RpWorldRender` → `AtomicDefaultRenderCallBack`
/ `_rpSectorDefaultRenderCallBack` → `RxPipelineExecute` → `PS2AllNodeBody` (object setup, per-mesh instance + material
bridge `RpMeshPS2AllBridgeCallBack` / the PDS bridges) → one VIF1 chain per frame → VU1 g3 programs; 2-D: the Im2D
device slots (100 game functions: `sprDrawSprite`, `frFontRasterDrawGlyph`, the cursor, fades, the movie player) →
`SkyIm2DRender*` → the 12 `addCopyVU1*` builders → `open2DVU1Pkt` / `closeAndDispatchVU1Packet` → VU1 039; plus Rt2d
(the Maestro HUD, program 089), PTank effects (033 / 035) and Im3D (041 / 046). The VU1 runs per route, faithful, from
`--vu1-stats` (the gate's end points; families of symbols/vu1_micro_census.json):

| route (vblanks) | VU1 runs | g3_skin (064, 063) | g3_generic (042, 046, 041) | Im2D 039 | g3_matfx (093, 097, 061, 053) | g3_skin_matfx (101, 102) | others |
|---|---|---|---|---|---|---|---|
| m1 (380) | 55 | 0 | 0 | 55 (100 % of runs) | 0 | 0 | 0 |
| dorm (4,900) | 316,061 | 76,195 | 81,652 | 152,579 (48.3 %; 3.3 % of pairs) | 4,165 | 1,470 | 0 |
| battle (6,150) | 1,754,344 | 858,016 | 414,718 | 370,909 (21.1 %; 0.9 %) | 81,466 | 23,809 | rt2d_fill 089 3,464; ptank_spr3d 1,962 |
| fusion (6,300) | 1,121,155 | 215,587 | 373,071 | 490,481 (43.7 %; 2.3 %) | 25,461 | 453 | ptank_spr3d 16,102 |
| shop (4,100) | 900,684 | 145,115 | 542,033 | 200,358 (22.2 %; 1.2 %) | 13,172 | 6 | 0 |

By VU1 work (pairs) g3_skin + g3_generic are 90-97 % on every route (battle 64.9 + 25.6 %), Im2D 0.9-3.3 %, though Im2D
is 21-48 % of the runs and 5-24 % of the PATH1 qwords (dorm 4.6 M of 18.9 M). The Im2D programs 036 / 037 (fog) and
038 (lines) never run on these routes: every Im2D draw is a 039 triangle batch. Per route the game side reported dorm
142,664 Im2D packets / 152,740 batches / 445,503 triangles, battle 360,309 / 370,989 / 841,354, fusion 481,619 /
490,551 / 1,115,077, shop 191,792 / 200,482 / 528,228, m1 104 / 104 / 208.

*Why Im2D first.* It is the one route into VU1 whose submission is already typed: the vertices are `RwIm2DVertex`
records in screen space (x, y, z, 1/z, u, v, colour), the program is 47 pairs with no clipping, and every 2-D element
of the game passes through two functions. The g3 pipelines carry 90 % of the VU1 work but need the PS2All bridge
seam and an exact model of the g3 programs (step 3).

*Swap point.* The RW sky driver's Im2D packet functions `open2DVU1Pkt` 0x4EC100 (notes the packet head and its
program) and `closeAndDispatchVU1Packet` 0x4EC4C0 (reports the closed packet: program, the three head quadwords that go
to VU1 0x3F9..0x3FB -- the screen offset, the GIF tag with PRIM, the colour scale -- and per batch of at most 16
triangles the vertex records as the VU1 receives them). Those are the two functions every one of the 12 builders goes
through, and the report is host-only: no guest register, memory word or cycle changes. The packet is still built and
queued as before, so the DMA bytes, the DMA / VIF timing and everything the EE observes stay the faithful ones (rule 1:
the timing is layer 6's). The host stands in for the VU1 where the program would run on a batch: `NativeIm2D` is the
VIF1's VU1 run hook (on the pipeline's VU1 stage), takes the queued record whose triangle count and words equal the
lanes program 039 reads from VU1 memory, and computes the program's whole effect from it -- the PATH1 packet, every VU1
register, flag and data word it writes, TPC -- then hands the packet to the VU1's own GIF sink, where every XGKICK goes
(GIF, GS registers, the D3D11 op recorder or the software rasteriser). A run with no matching record (none on the
routes) is the VU1's. With `--renderer native` (NativeG3, play mode) the hook passes every other program to it.

*What step 1 removes / keeps.* Removed for every Im2D batch: the VU1 program execution (the AOT or the interpreter).
Kept for step 2: the packet build, the DMA and VIF1 UNPACK of the vertices, the GIF tag walk and the GS register model.

The checks, every number from runs on that day (the gate's old routes and end points, `--gs-backend d3d11 --gs-exact`
at 640×448, faithful vs `--native graphics`):
- **(1) Frames.** `gate.ps1 -Slice -NoSuites -FastGs -NoBuild -ExtraArgs '--native graphics --native-graphics-check 16'`
  (the faithful references): dorm, m1, battle, fusion and shop GATE: PASSED -- frame.png the expected SHA-256 (dorm
  EE0EB5DA..., m1 E3A93615..., battle CFAA5A61..., fusion 9B5B5374..., shop 1165B3E0...), eeMemory 0 bytes, gsMemory
  identical. Every 039 run was native: 152,579 / 55 / 370,909 / 490,481 / 200,358 runs (445,181 / 110 / 841,250 /
  1,114,937 / 527,980 triangles), 0 fallbacks, 0 records dropped. Check mode (every 16th native run also run exactly on a
  scratch VU1 from the same state; registers, flags, data memory, TPC, branch view and kicked packet compared): 9,537 /
  4 / 23,182 / 30,656 / 12,523 runs compared, 0 differ. **Climb** (39,820 vblanks, run alone, 322 s wall): frame
  F3440652... as expected, eeMemory 0 bytes (`tracediff snapshot`, the gate's dead-stack rule), gsMemory identical;
  3,231,190 / 3,231,190 runs native (5,471,897 triangles), check every 64th: 50,488 compared, 0 differ.
- **(2) EE-visible GS behaviour.** eeMemory.bin byte-identical at all five end points (so the mask
  `tools/ours/modernize/layer5_graphics_mask.txt` has no range), and the scene logs byte-identical with their vblanks
  (dorm 24 lines, battle 17). The GS command stream itself: `--gs-record` of the battle frames at vblank 5800 and 6100
  (software GS) is byte-identical in both modes (10,024,695 and 8,912,772 bytes: every GIF tag, PACKED register write
  and image transfer in the same order), and so are that run's eeMemory, gsMemory and frame. CSR, FINISH, SIGNAL and readbacks are unchanged by construction: the native path writes no
  privileged register, its PATH1 packets are the program's (ST / RGBAQ / XYZF2 under one tag per triangle, an EOP tag
  with NLOOP 0: no SIGNAL / FINISH / LABEL), and local -> host transfers never pass through it.
- **(3) Speed.** Step 1 is the seam, not the speed win, and the numbers say so. Battle route headless (6,150
  vblanks = 102.6 virtual s, `--gs-backend d3d11 --gs-exact`, uncapped, runs one after the other on the shared
  machine): faithful 37.9 / 35.8 s, native 36.5 / 36.4 s (2.8x real time either way; earlier pairs under heavier load
  ranged 43-201 s, the same in both modes within the noise). The host's own work for the 370,909 Im2D runs is 353-367
  ms on the VU1 stage (0.97 us per run: matching the record, the SSE datapath, the packet) plus 57 ms handing the
  packets to the GIF; program 039 itself is only 0.9 % of the route's VU1 pairs. In isolation (`p3fes_app_tests`
  "cost per batch", two-triangle batches with the input placement both sides pay) the compiled program took 561 / 1,485 ns and
  the native run 644 / 368 ns per batch in two runs on the loaded machine: the same order. So the VU1 time moves, it does not shrink: the AOT already runs 039 at ~5 ns a pair.
  The remaining Im2D cost is the UNPACK, the GIF walk and the GS front end, which step 2 removes, and 90-97 % of the
  VU1 work is the g3 programs (step 3). A first fp::-only version was 2.5 us per run (the float datapath now uses the
  compiled programs' kernels, `vu1_aot_rt.h`; `g_im2d_fast = false` keeps the lane-by-lane fp:: path, both checked).
  The user's goal (battle at >= 100 % speed) holds in both modes: 2.8x headless.
- **(4) Combined** `--native files,input,sound,graphics`: m1 reaches `sky:11` at vblank 82 (as with `files,input,sound`),
  the user's native dorm recording (`--memcard new`, `config\inputs\native\dorm.txt`, to vblank 4,226) runs to its end
  with no hang: frame.png, eeMemory, gsMemory, the 20 scene lines and the 2,776 sound-log lines byte-identical to
  `--native files,input,sound` (frame C2249F19...), the `--dump-wav` mix too; 143,745 / 143,745 Im2D runs native, the
  SK stack native as well (0 instructions interpreted, 16,918 ticks); 26 s wall.
- **(5) Tests.** `p3fes_app_tests` `test_native_graphics.cpp` (4 cases; the game's program 039 from
  `ida/logs/vu1/005cd98c.bin`, `P3FES_VU1_DUMPS` overrides, skipped without it): 3,000 random batches of 0-16 triangles
  with game-shaped and adversarial floats, both TOP buffers, MSCAL 0 and MSCNT, both float paths -- the native run
  equals the VU1 interpreter in every register, MAC / status / clip flag, data word, TPC / PC, the branch view and the
  kicked packet; the lanes `im2d_inputs_match` reads (only the program's); the hook (matching, dropped stale records,
  the entry / count / no-record fallbacks, the next hook, the check mode); a cost case (MESSAGE only).
  `p3fes_game_tests` `test_render_im2d.cpp` (+1 case): 60 strip / fan packets and 30 line packets built by the hand
  builders with a recording service installed -- the reported program, head quadwords and per-batch vertex records
  equal the packet in the scratchpad and the source vertices, lines are declined, and the pair (hand with the report,
  recompiled without) still compares equal in every register, cycle, check point and guest byte. `test_modernize.cpp`:
  graphics is implemented. Every suite, `ctest --timeout 2400` with the user's data (`gate.ps1 -FastGs -ClangTree`):
  MSVC Release 209 / 209, clang-cl Release 208 / 208 entries pass (1,239 pair-test cases each); the oracle cases also
  run with the dumps on both trees: 4 / 4.
- **(6) Faithful configuration.** The same full gate's faithful routes (dorm, m1, battle, fusion, shop): GATE: PASSED
  (expected frames, eeMemory 0 bytes, gsMemory identical); `gate.ps1 -Slice -NoSuites -FastGs`: GATE: PASSED on the final code (dorm 50 s, m1 4 s, battle 80 s, fusion 66 s, shop 59 s). The gate
  learned `-ExtraArgs` (appended to every route, references unchanged) for check (1).

**Step 2 (2026-10-31): the host's packets without the GIF walk, the vertex UNPACK without the VIF decode.** Commit
9f88f55 (its `GsCore::packed_triangles` became step 3's `packed_run`). The VU1 stand-in of step 1 hands every PATH1 packet it computes to the VU1's sink as a *host packet*
(`vu1::IGifSink::kick_host`; GsSystem in the synchronous model, the pipeline's VU1-stage sink otherwise, which carries
a host flag on its PATH1 packet command to the GS stage). When the GIF is idle -- the case in which `path1` runs a
packet at once -- `gs::Gif::path1_host` applies it exactly as `path1` would: the GIF statistics, the last-tag registers
(TAG0-3 hold the closing tag), and every GsCore effect through `GsCore::packed_run`: PRIM by the tags' PRE, Q, ST,
RGBAQ, the vertex queue and its kicks, every draw (the d3d11 op recorder's `on_draw`, or the software rasteriser), the
counters and the register observer's PRIM calls (the GS census). What it skips is the per-qword dispatch of
`Gif::feed` / `write_packed`, and one thing more: the packet's equal per-triangle PRIM writes change
`state_generation()` once (at the first PRIM write and where the value changes), so the op recorder decodes the draw
state once per packet instead of once per triangle. A busy GIF (the packet must queue), any other form and a stream
recording (`--gs-record`: the calls are made one by one) take the packet path. The builders' vertex UNPACK (STCYCL 4,4,
STMASK 0xC000C000, UNPACK V4-32 masked, MODE 0 -- the form render_im2d.cpp reports) is written by the host as an image
(`IVuRunHook::unpack`, on the stage that writes VU1 memory) instead of `vif_unpack`'s generic masked decode; VIF1's
registers, its qword accounting and the DMA timing are untouched (the EE side still copies the payload: comparing it
with the record would cost what the copy costs). The GS register model therefore ends each packet in the state the
packet path leaves -- the faithful path is still the oracle (`--native-graphics-gs packets` keeps step 1's kicks and
`vif_unpack`). Why not `GsOpRecorder::on_native_triangles` (the plan): driving the recorder's own `on_draw` per kick
keeps the op lists identical by construction, and the per-triangle state decode -- the recorder's real per-triangle
cost on these packets -- goes away anyway.

Checks (the gate's routes, `--gs-backend d3d11 --gs-exact` at 640x448):
- **(1) Frames.** `gate.ps1 -Slice -NoSuites -FastGs -ExtraArgs '--native graphics --native-graphics-check 16'`: GATE:
  PASSED on dorm, m1, battle, fusion, shop -- the expected frames (EE0EB5DA / E3A93615 / CFAA5A61 / 9B5B5374 /
  1165B3E0...), eeMemory 0 bytes, gsMemory identical. All 152,579 / 55 / 370,909 / 490,481 / 200,358 program-039 runs
  native and every one of their packets applied as a host packet (0 through `path1`: the GIF was never busy at a
  native run); the vertex UNPACKs written by the host: 152,579 / 55 / 370,909 / 490,481 / 200,358 (5.34 M / 1,320 /
  10.1 M / 13.4 M / 6.34 M qwords), 0 by `vif_unpack`. Check mode: 9,537 / 4 / 23,182 / 30,656 / 12,523 runs compared,
  0 differ. The plain gate (faithful): GATE: PASSED, eeMemory 0 bytes, gsMemory identical.
- **(2)** eeMemory 0 bytes and gsMemory identical at the five end points (as above); scene logs: see step 3 (the same
  runs, both steps on).
- **(3) Speed.** The work removed is small in the route's terms: the GIF walk and the per-triangle draw-state decode of the Im2D packets (5-24 %
  of the PATH1 qwords) and the masked UNPACK of 10 M qwords on battle. Headless wall time does not move
  (below); in the inline pipeline (`--gs-threads 0`, every stage on one thread, zones) the `gif` zone of battle went
  0.68 -> 0.56 ms per vblank with steps 2-3 together.
- **(5) Tests** (`p3fes_app_tests`): host packets against the GIF walk on a d3d11 op recorder and on the software GS --
  600 / 120 random packets in program 039's form (every PRIM type including sprites and lines, ADC bits, XYZF2 /
  XYZ2, leftover closing tags with PRE and any FLG, malformed forms) between random A+D state writes including CLUT
  loads: GsCore registers / queue / counters / local memory, GIF TAG0-3 / STAT / statistics, the register observer's
  calls and the recorder's op lists byte for byte; a busy GIF refused, a stream sink sees the packet path's calls; the
  UNPACK image against `vif_unpack` over 2,000 random UNPACKs (the form and near misses).

**Step 3 (2026-10-31): the g3 pipelines at the PS2All bridge seam.** Commits 952a95e, c181681. Code:
`runtime/native/graphics/native_g3.{h,cpp}` (`NativeG3Seam`), the seam's records in `p3fes/native/graphics_service.h`
(`G3Service`, `G3ObjectRecord`, `G3MeshRecord`), game side `game/src/render/mesh.cpp` (`mesh::report_native_mesh`, the
object record in `openVU1SetupPktNew`) and `bridges.cpp` (the MatFX / skin bridges).
- *The seam.* With `--native graphics` the RW sky driver's object node and material bridges report, once the draw's
  guest state is complete, per object the camera x object matrix and the light block size, and per mesh the three
  quadwords the bridge sends to VU1 0x3FA..0x3FC (the GIF tag after the PRIM patch, the material colour, the surface
  properties), the GS register shadows of its A+D block (TEX0 after the cache placement, TEX1, CLAMP, TEST), the
  program (code-array entry), the resEntry's DMA address and whether a MatFX bridge drew it. Host-side reads only.
- *The hook.* `NativeG3Seam` is the next VIF1 run hook after `NativeIm2D` (it, in turn, hands everything to the
  play-mode `NativeG3` when `--renderer native` is on). For a run of a g3_generic, g3_skin, g3_matfx or g3_skin_matfx
  program (identified by image from the compiled table, `vu1::aot_programs()`) it finds the mesh record whose block VU1
  memory holds (all clusters of a mesh are runs with one block; the records before the match -- draws that never
  reached VU1 -- are dropped), lets the program run, and hands the run's XGKICKs to the VU1's sink as host packets in
  the order the program kicked them; `Gif::path1_host` now takes any packet of PACKED STQ / RGBAQ / XYZF2|XYZ2 tags
  (program 039's per-triangle tags, the g3 strips and lists) through `GsCore::packed_run`.
- *The model.* What a g3 batch draws is what the game's program computes, and that program already runs as exact
  native code: its ahead-of-time translation (`runtime/vu1/vu1_aot.h`: each pair's semantics, the VU float datapath with
  round toward zero / FTZ / DAZ and the slow-path lanes, MAC / status / clip flags, Q / P timing, checked against the
  interpreter by `--vu1 diff`). The hook keeps it as the model rather than a hand-written one, for a measured reason:
  the compiled g3 programs run at ~5.4 ns a pair on the VU1 worker (3.19 G pairs on battle in 17 s of worker CPU), and
  that worker is not on the critical path (below), so an exact re-implementation -- these programs are 845-1,929 pairs
  each, software-pipelined over the vertices, with clipping, five light types, skinning and morphing, and their VU
  state is compared in full -- would buy no wall time. NativeG3's float model (docs/ANALYSIS/31) stays the play-mode
  renderer.
- *Check mode* (`--native-graphics-check N`): every N-th g3 run also runs from the same state on a scratch VU1 in the
  interpreter; every register, flag, data word, TPC / PC, the branch view and every kicked packet are compared.

Checks (same configuration as step 2):
- **(1) Frames.** The slice gate with `-ExtraArgs '--native graphics --native-graphics-check 16'`: GATE: PASSED on the
  five routes (expected frames, eeMemory 0 bytes, gsMemory identical); the plain gate: GATE: PASSED. g3 runs per route
  (generic / skin / matfx / skin_matfx): dorm 163,482 (81,652 / 76,195 / 4,165 / 1,470), battle 1,378,009 (414,718 /
  858,016 / 81,466 / 23,809), fusion 614,572 (373,071 / 215,587 / 25,461 / 453), shop 700,326 (542,033 / 145,115 /
  13,172 / 6), m1 0. Their kicks as host packets applied without the GIF walk: dorm 128,857 of 128,877, battle
  1,326,432 of 1,471,134, fusion 539,579 of 577,121, shop 674,217 of 676,065; the rest are g3_matfx's 3-qword A+D
  packets (the second pass's state), not of the host form, so they take `path1` (0 for a busy GIF). Check mode:
  10,218 / 86,126 / 38,411 / 43,771 g3 runs compared, 0 differ (and the 039 runs as in step 2). Matched to a reported
  mesh record (the final matcher): dorm 163,482 / 163,482, battle 1,374,798 / 1,378,009, fusion 614,460 / 614,572,
  shop 700,005 / 700,326 (the first matcher's 64-record window: 52 % on dorm, 74 % on shop).
  **Climb** (39,820 vblanks, run alone, check every 64th run, 260 s wall): frame F3440652... as expected, eeMemory 0
  bytes, gsMemory identical; 12,660,306 g3 runs (3,231,286 / 8,823,183 / 370,809 / 235,028), 12,572,408 matched to a
  record; 14,769,795 of 15,449,203 host packets applied without the GIF walk (679,408 MatFX A+D through `path1`);
  all 3,231,190 program-039 runs native; check mode 197,818 g3 and 50,488 Im2D runs compared, 0 differ.
- **(2) EE-visible state.** eeMemory.bin 0 bytes and gsMemory identical at the five end points (the gate's
  `tracediff snapshot`, dead stack excluded); the scene logs byte-identical with their vblanks, faithful vs `--native
  graphics` (dorm 24 lines, battle 17), and so are eeMemory / gsMemory of those runs. CSR, FINISH, SIGNAL and
  readbacks: the host packets carry no privileged register (the form has none; the A+D packets go through `path1` and
  the pipeline's event scan as before), and the GIF's TAG0-3 / STAT and statistics after a host packet are those after
  `path1` (tests).
- **(3) Speed.** Headless, `--gs-backend d3d11 --gs-exact`, uncapped, faithful / native back to back (loaded machine;
  wall s, GS worker CPU s): dorm 15.4 / 15.7 (10.2 / 10.3), m1 2.6 / 2.5, battle 35.8 / 36.4 (24.6 / 25.4), fusion
  29.0 / 29.3 (23.2 / 20.4), shop 20.9 / 20.1 (17.5 / 16.7) -- the same within the noise (a second series, run while
  other agents' test suites started, ranged up to 3x for both modes). Windowed (the user's play: interpolated d3d11,
  vsync, `--unpaced --frames 6150`, battle): faithful 23.5 s, native 25.8 s for the route's 102.6 virtual s (4.4x /
  4.0x real time; the native run presented 2,163 frames against 1,854, frame interval p50 10 / 10 ms, p95 30 / 30,
  mean 14.6 / 12.9). Where the time goes (battle, faithful zones of the threaded pipeline): the EE thread is the
  critical path -- game code 67.5 %, VIF1 (the EE side: VIFcodes, copying UNPACK payloads into the pipeline) 9.8 %,
  waiting for the pipeline 11.0 %, GIF PATH2 / PATH3 2.4 % -- while the VU1 worker (17-18 s CPU) and the GS worker
  (22-25 s) run beside it. With every stage on one thread (`--gs-threads 0`, ms per vblank, faithful / native): EE
  code 3.56 / 3.79, VU1 2.15 / 2.23, VIF1 0.92 / 1.04, GS front end + op recording 0.92 / 0.90, GIF 0.68 / 0.56.
  `--vu1-stats` of the battle segment (vblanks 4600-6150, synchronous model, `--native graphics`, 16.2 s wall): g3_skin
  064 2.83 s (3.2-3.8 ns a pair), g3_generic 042 1.05 s, g3_matfx 061 0.30 s, g3_skin_matfx 101 0.10 s, g3_matfx 093
  0.07 s -- 27 % of the segment's wall time in that model, all of it compiled code.
  So the layer's remaining cost is the VU1 programs themselves (already compiled), the VIF1 front end on the EE thread
  and the op recording -- which only step 5 (no packets) removes; the speed goal (battle >= 100 %) holds by 2.9-4.4x
  in both modes.
- **(4) Combined** `--native files,input,sound,movies,graphics`: m1 identical to `files,input,sound,movies` (frame
  E3A93615..., eeMemory, gsMemory, scene log; sky:11 at vblank 82). The user's native dorm recording (`--memcard
  new`, `config\inputs\native\dorm.txt`, to vblank 4,226) against `files,input,sound,movies`: frame C2249F19... in
  both, eeMemory, gsMemory, the 20 scene lines and the 2,776 sound-log lines byte-identical; 143,757 / 143,757 Im2D
  runs native, 213,092 g3 runs through the seam (all matched), 311,685 of 311,701 packets applied as host packets
  (16 MatFX A+D); 14.4 s wall.
- **(5) Tests** (`p3fes_app_tests`, `test_native_graphics.cpp`, 9 cases; the program dumps from `ida/logs/vu1`,
  `P3FES_VU1_DUMPS` overrides, skipped without them): the game's g3 programs (042 g3_generic 006b8d4c, 064 g3_skin
  006f8b1c, 063 g3_skin 006f598c) on 120 random game-shaped batches each (N vertices, bone palette, light block,
  transform rows, constants, flag variants) through the seam on a VU1 running the compiled program -- every
  register, flag, data word and kicked packet equal to an interpreter running the same program from the same state,
  check mode 0 differ, every kick a host packet; the record matching (a mesh's clusters, passed-over records,
  unmatched runs), the forwarding to the next hook, `direct` off; host packets against the GIF walk now with g3-form
  packets (1-3 tags, strips / lists, PRE on later tags, closing tags) and CLUT loads.
  Every suite, `ctest --timeout 2400` (Release, the user's data, the two trees side by side): MSVC 210 / 210 entries
  pass (2,326 s), clang-cl 209 / 209 (2,223 s; `p3fes_recomp_emit_subset` skips by design on both); after the last
  seam change `p3fes_app_tests` again on both compilers, 76 / 76 cases with the dumps (67,713 assertions; the compiled
  g3 programs on MSVC, the interpreter on clang-cl) and without them (44,675).
- **(6) Faithful configuration.** The plain slice gate on the final code:`gate.ps1 -Slice -NoSuites -FastGs` with its build: GATE: PASSED --
  expected frames, eeMemory 0 bytes, gsMemory identical on dorm, m1, battle, fusion, shop (46 / 3 / 74 / 62 / 65 s);
  the same gate with `-ExtraArgs '--native graphics --native-graphics-check 16'`: GATE: PASSED (41 / 2 / 73 / 65 / 59 s),
  every check 0 differ. The faithful path runs the code it ran: the new entry points (`Gif::path1_host`,
  `GsCore::packed_run`, `IVuRunHook::unpack`, `kick_host`, the bridges' `g_g3` report) are reached only with
  `--native graphics`; otherwise each costs a null test.

**Steps 4-5 (the plan).** (Steps 2 and 3 as planned here before: see above for what was built and where it differs.)
1. **Step 4, the rest of the packet path.**
   - Rt2d 089 (the Maestro HUD), PTank 033 / 035, Im3D 041 / 046 and the never-seen Im2D 036-038: each program at its
     own submission seam (records reported as in steps 1 and 3), its kicks as host packets. Program 039's triangle
     packets and the g3 strips / lists already use the host form; Rt2d / PTank kick other forms (sprites, A+D).
   - The host form for A+D register lists (g3_matfx's 3-qword second-pass packets: 144,702 on battle, 679,408 on the
     climb), SIGNAL / FINISH / LABEL excluded so the pipeline's event scan is unchanged.
   - The seam's unmatched g3 runs (battle 3,211, fusion 112, shop 321, climb 87,898: runs whose 0x3FA..0x3FC block no reported
     record holds; find the bridge that does not report -- the PDS bridges of sky.cpp, 22_rendering.md §8.2 -- or the
     block it sends).
   - A hand-written exact model of the g3 programs only once the VU1 work is on the critical path (after step 5 has
     taken the EE side's VIF / DMA work away; today the compiled programs run beside the EE thread at ~3-5 ns a pair).
     It would be exact the way 039 is: the AOT float kernels, flags, the full VU state compared by the check mode.
2. **Step 5, no packets.** When every program the routes run goes through a seam and layer 6 owns the timing (DMA
   completion = the frame pacing), the game's draw submission calls the renderer directly: no DMA chain, no VIF1 /
   GIF. The step-3 records are what a draw is built from (per mesh the object, the material block, the GS register
   shadows and the resEntry's clusters, whose vertices the compiled program -- the model -- transforms on the host's
   own buffers instead of VU1 memory). Then the GS register model behind it: draws carry decoded state from the RW
   render-state funnel (`_rwSkySetRenderState`, `RpSkyRenderStateSet`) and the texture cache
   (`RpSkyTexCacheAccessRaster`: host textures instead of GS-memory uploads, CLUTs as data), the D3D11 renderer draws
   them; the software GS and the GS register path stay as the oracle until rule 5 removes them.

**Try it (for the user): the native graphics layer so far.** Your usual memory card; everything should look exactly as
before:

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native graphics

Add `--native files,input,sound,movies,graphics` for every native layer so far. At exit three log lines report the
layer: `p3fes: native graphics: Im2D packets ...` (the Im2D batches drawn by the host), `... g3 seam: ...` (the g3
runs, the meshes the bridges reported and how many runs matched one) and `... direct: ...` (the packets that reached
the GS without the GIF walk). `--native-graphics-check 64` also runs every 64th Im2D batch and every 64th g3 run on a
scratch VU1 and prints any difference (expect `0 differ` twice); `--native-graphics-gs packets` turns steps 2-3's
GS-side path off (the step 1 behaviour, for comparison).

**6. Kernel and timing.** It needs no check of its own beyond the earlier ones: the re-recorded routes and all suites
stay green with the emulated devices removed, and the frame pacing holds the game's own frame rate (the
frame-telemetry log).

**Layer 6 status (2026-10-31): step 1 done -- the inventory, the (a) / (b) split, the (a) set behind `--native kernel`
(default still off), the cheap part of the (b) set behind `--native-kernel-timing host`.** Code:
`runtime/native/kernel` (`NativeKernel`, library `p3fes_native_kernel`), seam `p3fes/native/kernel_service.h`, game side
`hg::syscall` (game/include/p3fes/game/hg_cpu.h), kernel side `Kernel::direct_call` and `KernelCensus`
(runtime/hle/kernel/README.md "Modernize layer 6"), the inventory tool `--kernel-census FILE` (runtime/app/kernel_census.h).

*What ADR-0013 already did.* The kernel is a host scheduler since Phase 3: one host thread, a fiber per guest thread,
virtual time from the emitted cycle counts, interrupts delivered at check points. So "threads → host scheduling" is
mostly there; what is still PS2-shaped is the call path (the `syscall` instruction and its `$v1` dispatch), the BIOS
context frames in guest memory, the INTC / DMAC / timer register model and the cost model of virtual time (DMA latency,
the SIF round trip, the movie decode's charge, the 1 cycle per instruction estimate). The game's per-vblank behaviour is
a function of that cost model, which is what decides the split below.

*The inventory* (`--kernel-census`, faithful, the gate's end points; per route dorm / m1 / battle / fusion / shop =
4,900 / 380 / 6,150 / 6,300 / 4,100 vblanks; "who" = the game functions behind the counts, by `$ra`):

| mechanism | count per route | who |
|---|---|---|
| threads | 8 created, 7 started (all at boot) | libkernel topThread, H_Resman, _sdrCBThread (SDR RPC server), libmc2 basic_thread, ADXM safe / vsync / fs / mwidle |
| fiber switches | 9,626 / 583 / 12,311 / 12,766 / 8,283 (~2 / vblank), 211 / 180 / 227 / 214 / 219 of them interrupt-exit preemptions | the ADX vsync / fs threads woken at 30 Hz, the RPC waits |
| idle (no thread ready) | 85 / 5 / 76 / 81 / 79 % of virtual time, 11,743 / 56 / 12,946 / 13,270 / 8,692 idle jumps | the game waits for the next VBLANK_START |
| ChangeThreadPriority + GetThreadId | 175 k + 180 k / 24 k + 24 k / 219 k + 225 k / 179 k + 185 k / 123 k + 127 k (36 / vblank each) | CRI ADXM's lock / unlock (sub_53F8B8 / sub_53F940) |
| ReferThreadStatus, Suspend / ResumeThread | 192 k, 92 k / 92 k (dorm; 39 and 19 / vblank) | ADXM's mwidle control (sub_540118 / sub_5400B0), H_Resman (sub_10BF70) |
| SleepThread / WakeupThread / iWakeupThread | 9,403 / 4,499 / 4,898 (dorm) | adxm_vsync_proc / adxm_fs_proc (woken from kwlnGsSyncVCallback), H_Resman |
| semaphores | Create / Delete 8,748 / 8,735, WaitSema 11,991, iSignalSema 9,023, SignalSema 3,645, PollSema 678 (dorm) | one sema per sceSifCallRpc (8,706), the RPC end (_request_end), viBuf (Sofdec), libcdvd (sceCdNcmdDiskReady, _sceCd_*_prechk), the RW file lock |
| SIF calls (layer 3's transport) | SifSetDma 18,287, SifSetDChain (i*) 9,027, SifDmaStat 4,671, SifGetReg 12,830 (all at boot: sceSifSyncIop's poll) | sceSifCallRpc / sceSifSetDmaInternal, H_Sndcom_CopyToIop |
| FlushCache, EndOfHeap, Deci2Call | 924-2,085, 349-503, 40-1,742 | sceTtyInit, H_Sndcom_CopyToIop, libmpeg CSC; sbrk; kputs |
| INTC 2 VBLANK_START | every vblank (4,898 ...) | kwlnVsyncFieldGate; on odd fields _rwDMAVSYNCHandler (the flip) + kwlnGsSyncVCallback (ADX vint) |
| INTC 9 T0 / INTC 11 T2 | 801 (boot only) / 719 / 56 / 902 / 924 / 602 | kwlnT0OverflowHandler; libkernel's alarm engine cbTimerHandler (DelayThread in sceCdSync / sceFsSifCallRpc, sifrpc retries) |
| DMAC 1 / 2 handler chains | 2,532 + 1,178 (dorm) | _rwDMAHandler (RW's DMA queue) |
| DMAC 3 / 5 handler chains | 80 / 9,025 (dorm) | _ch3dmaCSC (libmpeg, faithful movies only); the SIF command handler (sub_5066B0) |
| DMA ch1 VIF1 / ch2 GIF | 2,533 / 1,180 starts, 37.7 M / 87.3 M qw; GIF 26,225 stalls (PATH3), 190,976 busy CHCR reads (dorm; battle 272 M VIF1 qw) | RW's packet DMA, texture uploads |
| DMA ch3 / ch4 IPU | 44,644 / 216 starts, 1.47 M toIPU stalls (dorm) | libmpeg (faithful movies) |
| DMA ch8 / ch9 SPR | 157,852 / 48,721 starts, 19.1 M / 10.3 M qw, 594 k / 590 k busy CHCR reads (dorm; battle 525 k / 17 k starts) | my_malloc_0's sceDmaSync loop, uttmxDMASPRCopy (sub_10E630), RpSkyTexCacheAccessRaster, MWSPR save / restore |
| timers | T0 11-13 k reads (kwlnUpdate's frame-start count, the raster bar), T2 5-6 k reads / 2-3 k writes, T1 unused, T3 read once | kwlnUpdate / Y_Misc_GetT0Count, cbTimerHandler, InitAlarm |
| polled registers | INTC_STAT 462,671 reads (VSync()'s boot loop, every route), GS CSR once per vblank, D_STAT / D_PCR / D8-D9_CHCR (SPR copies) | VSync 0x5035F0, kwlnVsyncFieldGate |
| check points | 2.07 M / 17 k / 1.70 M / 1.21 M / 0.64 M slow check points (420 / vblank on dorm), 1,839 masked re-tests | ADR-0013's check points |

The earlier native layers (`--native files,input,sound,movies,graphics`, the user's native dorm recording, 4,226
vblanks): the same threads and the same ADXM traffic (122 k ChangeThreadPriority, 132 k ReferThreadStatus); SIF RPCs
down from 8,748 to 2,554 semaphores (files and sound native); T2 alarms 620; no DMAC 3 / 4 (movies native); VIF1 / GIF
DMA unchanged (2,262 / 1,133 starts: layer 5 still builds the packets); SPR unchanged (155,734 fromSPR starts).

*The split.* (a) = native with the game's per-vblank behaviour unchanged: the same results at the same virtual cycle
and the same guest memory, so the old recordings stay valid. (b) = changes what the game observes per vblank: the old
recordings desync, the user re-records.

| mechanism | class | why | step 1 |
|---|---|---|---|
| the call path of every kernel call (all ~160 stubs: threads, semaphores, sleep / wakeup, priorities, handlers, Enable / Disable, heap, cache, SIF) | (a) | the results do not depend on how the call arrives | **done**: the stubs call the host kernel directly (`--native kernel`) |
| host frame pacing (wall clock) | (a) | the guest never sees wall time | exists (FramePacer, docs/ANALYSIS/31); measured below |
| VSync()'s boot poll, sceSifSyncIop's SifGetReg poll, the SPR / GIF CHCR busy loops | (a) | a spin whose exit is fixed by the event schedule can be fast-forwarded to the same exit cycle | not done: 462 k + 12.8 k boot iterations and ~1.2 M SPR polls per route are well under 1 % of the host time |
| T0 frame-start count (Y_Misc_GetT0Count) | (a) | a pure function of virtual time | not done: the host answer would be the same timer model |
| the BIOS context frames (sp - 0x280 of a waiting thread, a new thread's stack top) | **(b)** | the game reads them back: uninitialised stack slots of its functions are copied whole into its records (the first: sCdvdCache 0x7D6F80's +104 word, from vblank 20 on m1) | behind `--native-kernel-timing host` |
| DMA completion latency (64 + 2 / qw cycles) | (b) | RW's DMA handler, the CHCR polls of the SPR copies and the GIF stalls observe it | `--native-kernel-timing host`: complete at the end of the data phase |
| the movie decode's per-call cycle charge (layer 4) | (b) | the movie task's pacing follows it (2 vblanks early without it) | `--native-kernel-timing host`: instant |
| the SIF RPC transport (layer 3) | (b) | the calling thread's RPC wait lets the other threads run | `--native-kernel-timing host` sets `--native-sk direct` (with `--native sound`) |
| T2 alarms (DelayThread), the 64-cycle masked re-test, VBLANK / T0 from the wall clock, ADR-0013's 1 cycle / instruction | (b) | the game's timing model itself; a wall-clock game is no longer deterministic | not done: needs the re-recorded routes and a new determinism rule (the replay gates) first |
| DMAC completions for native layers' transfers nothing observes mid-flight | (a) when such a transfer exists | today every remaining transfer is observed (RW handler, CHCR polls, SIF handler); layer 5 step 5 removes the VIF1 / GIF packets | none to swap yet |

*Swap points.* (a): `hg::syscall`, the game library's `syscall` -- every kernel call of the 14,500 hand-written
functions (the libkernel stubs and the inline sites; `$v1` is the number the stub set) -- hands the call to
`native::kernel::service()` when it is installed; `NativeKernel::call` serves it through `Kernel::direct_call`, the
instruction's own service (result, BIOS wrapper result rules, reschedule, the closing check point). (b):
`native::kernel::configure` (KernelOptions: `context_frames`, `dma_base_cycles`, `dma_cycles_per_qword`),
`NativeMovies::set_instant`, `--native-sk direct`. Without frames the kernel still applies every result rule of the
BIOS wrappers (the frame's `$v0`, the released wait's low word, the start registers from the fresh frame's bytes) --
only the bytes are not written; `capture.json` reports the saved sp as such a thread's dead-stack bound.

*Checks* (every number from runs on 2026-10-31, MSVC Release, `--vu1 aot`, `--gs-backend d3d11 --gs-exact`):
- **(1) The old routes with the (a) set** (the gate, `-ExtraArgs '--native kernel'`): dorm, m1, battle, fusion,
  shop **and the climb**: expected frames exact, eeMemory 0 bytes differ (dead stack excluded, as always), gsMemory
  identical -- no mask needed. With `'--native kernel,graphics --native-graphics-check 16'`: the five routes again
  exact (0 bytes, gsMemory identical), and the graphics check `0 differ` on every route (dorm 9,537 Im2D + 10,218 g3
  runs compared; battle 23,182 + 86,126; fusion 30,656 + 38,411; shop 12,523 + 43,771; m1 4). `native kernel: ...
  served directly` per route: 844 k (dorm), 156 k (m1), 1.05 M (battle), 908 k (fusion), 637 k (shop) kernel calls.
- **(2) The native configuration.** `gate.ps1 -NoBuild -NoSuites -FastGs -Native -NativeLayers 'files,input'`
  against the existing baselines: **passed**, all six routes (dorm, m1, battle, fusion, shop, climb: 0 bytes,
  gsMemory identical). `--native files,input,sound,movies,graphics,kernel` against the same without `kernel`: m1
  (`sky:11`) and the user's native dorm recording (to vblank 4,226): no hang; frame.png, gsMemory, eeMemory (0 bytes)
  and the scene log byte-identical with their vblanks (1 and 19 lines). 572 k kernel calls served directly on dorm.
- **(3) The (b) set** (`--native kernel --native-kernel-timing host`, the gate's five old routes): frames still equal
  and gsMemory identical at all five end points, but eeMemory differs: dorm 7,483 bytes, m1 3,556, battle 9,044,
  fusion 3,392, shop 7,967 -- the frame bytes the game copies out of dead stack (sCdvdCache and its neighbours, the
  0x95D410 block) plus what the DMA latency moves. Without the frames alone (before the SetupThread words were kept,
  see below) the battle route desynced (6.6 MB, another frame) and fusion's gsMemory differed. On the native dorm
  recording with every layer: the same 19 scenes in the same order, one of them 2 vblanks earlier (436 -> 434: the SK
  sounds without SIF), eeMemory 38,605 bytes differ; m1 the same frame, 2,702 bytes. The semaphores of the run drop
  from 18,047 to 8,413 (no SIF RPC for the sound commands). So the (b) set does not desync these routes yet, but it is
  not byte-exact, and the gates cannot vouch for it: it stays out of `--native kernel`.
- **One trap found on the way**: SetupThread's frame is the main thread's *live* stack (crt0 runs on from the sp it
  returns), so its four words are written in both modes; without them the main thread's stack differed above its sp.
- **Tests**: `tests/kernel/test_native_kernel.cpp` (one scenario of threads, semaphores, sleep / wakeup, priorities,
  a released wait, an invalid WaitSema and an iWakeupThread from a VBLANK handler, run faithful / (a) / host-only
  contexts: (a) = faithful in results, virtual time and memory; host-only contexts = faithful in results and time, no
  byte written below any stack top; the census counters; configure() and the timing names), `test_scheduler.cpp`'s
  frames-off case updated (the BIOS restore's start registers), `tests/game/test_kernel_native.cpp` (the stubs
  `_sceWaitSema`, `_sceGetThreadId`, `_sceiSignalSema`, `_sceFlushCache` hand their call to the service with their
  number, address and argument and execute no `syscall`; CRI ADXM's lock sub_53F8B8 runs the same path, registers,
  memory, cycles and check points through the service as through the instruction), `test_modernize.cpp` (every layer
  has a native implementation now).
- **(4) Frame pacing, windowed** (`--frame-log`, the default `--pacing display`, quiet machine; this host's display runs
  at 100.087 Hz, no multiple of 59.94, so the pacer is on the clock and a 33.37 ms frame is shown for 3 or 4 refreshes:
  p50 30.0 / p95 40.0 are that quantisation, not lateness). From vblank 400 on (after the boot):

  | run | frames | interval mean | p99 | game fps | work p50 / p95 / p99 ms | frames within budget | held > 2 vblanks by the game | late presents |
  |---|---|---|---|---|---|---|---|---|
  | dorm faithful | 2,225 | 33.74 | 40.0 | 29.64 | 1.0 / 4.1 / 12.4 | 2,225 / 2,225 | 4 | 0 / 2,445 |
  | dorm `--native kernel` | 2,225 | 33.74 | 40.0 | 29.64 | 1.0 / 4.1 / 12.4 | 2,225 / 2,225 | 4 | 0 / 2,445 |
  | battle faithful | 2,841 | 33.76 | 40.0 | 29.62 | 5.0 / 7.3 / 10.4 | 2,841 / 2,841 | 11 | 0 / 3,063 |
  | battle `--native kernel` | 2,841 | 33.77 | 40.0 | 29.62 | 5.0 / 7.3 / 10.0 | 2,841 / 2,841 | 11 | 0 / 3,063 |
  | native dorm, layers 1-5 | 1,891 | 33.76 | 40.0 | 29.62 | 1.3 / 4.1 / 6.8 | 1,891 / 1,891 | 5 | 0 / 2,106 |
  | native dorm, layers 1-6 | 1,891 | 33.75 | 40.0 | 29.63 | 1.4 / 4.2 / 7.1 | 1,891 / 1,891 | 5 | 0 / 2,106 |

  The windowed game holds its own frame rate under `--native kernel`: every guest frame's host work fits its budget
  (p99 at most 12.4 ms against 33.37), no present is late, and the rate is the game's own 29.62-29.64 fps (29.97
  minus the frames the game itself holds for 3+ vblanks, as on the PS2; the telemetry's worst-hitch causes are "guest"
  and "display", never "host", "pacing" or "load"). Nothing in the kernel layer had to change for that: the pacing
  already never reaches the guest (FramePacer maps virtual to wall time at the slice ends, docs/ANALYSIS/31), and the
  host cost that once broke it (42-49 ms per heavy frame on 2026-10-25) is gone with the VU1 AOT and layers 1-5. The
  kernel's own share is small: its zone never shows among a gameplay frame's top zones (at boot it is 16.5 of the
  1,228 ms the first frame takes, on battle), so the (a) set neither costs nor saves frame time. On a 60 / 120 Hz
  display the pacer locks to the refresh (`--pacing display`, 2 refreshes per frame).
- **(5) Speed, headless** (`--gs-backend d3d11 --gs-exact`, one process at a time, the routes' end points; mean of 3
  runs in alternating order where given): dorm 14.4 s faithful / 14.6 s `--native kernel`, m1 1.5 / 1.5, battle 25.6 /
  24.4, fusion 20.3 / 19.7, shop 21.8 / 21.2 (one run each): the same within the run-to-run noise (+-10 %). With every
  native layer: the native dorm recording (4,226 vblanks) 13.4 s with layers 1-5, 13.8 s with layers 1-6; m1 0.5 s
  either way (it reaches `sky:11` at vblank 82 instead of 380). The kernel layer is no speed lever: the routes run
  4-6x real time headless already, and the kernel's work per vblank is ~2 fiber switches, ~170 kernel calls and ~400
  slow check points (the inventory).

**Try it (for the user): the native kernel.** Your usual memory card; the game should play exactly as before:

    build\<tree>\bin\p3fes.exe --elf extracted\disc\SLUS_216.21 --iso input\persona3fes.iso --native kernel

At exit `p3fes: native kernel: N kernel calls served directly (...)` reports the layer. With every native layer:
`--native files,input,sound,movies,graphics,kernel` (or `--native all`). `--kernel-census FILE` writes what the run asked
of the kernel (the inventory above). `--native-kernel-timing host` is the (b) set: it plays, but the game's timing moves,
so it is not for the old recordings.

**What the user would need to re-record**: nothing for `--native kernel` (the (a) set keeps every old and native
recording valid; the gates prove it). Only if the (b) set (`--native-kernel-timing host`) is to become a gated
configuration: the old routes keep their frames under it (the five run; the climb was not), but their eeMemory is no longer byte-exact, so the faithful
configuration's gate cannot check it; the native recordings (`config\inputs\native\*.txt`) would need new baselines of
`native-...+kernel` with host timing -- by the user's decision only (rule 4) -- and, once the remaining (b) items
(T2 alarms, the wall clock) land, new recordings made with `--native all --native-kernel-timing host`, since those move
the game's frames.

## 4. After this pass

The hand-written lift starts on code that calls host services only. The pilot subsystem
is field and actors, since it serves the editor and then the server (the readiness gate for multiplayer is
unchanged).
