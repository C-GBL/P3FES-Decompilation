# IPU — MPEG macroblock decoder + colour-space converter (`p3fes_ipu`)

The PS2 Image Processing Unit as an EE-bus device: its four registers, the input FIFO + bit-stream buffer, the
output FIFO, the ten commands (BCLR, IDEC, BDEC, VDEC, FDEC, SETIQ, SETVQ, CSC, PACK, SETTH), the DMAC channel 3
(fromIPU) and 4 (toIPU) data paths and the INTC cause-8 line. The game's Sony libmpeg/libipu (SDK 3.1, FLIRT-named
at `0x4FB168–0x502D40`) and CRI's Sofdec wrapper are recompiled guest code; this module is the hardware they drive
for the Sofdec FMVs (`docs/RUNTIME_CONTRACT.md` L-35, H-06, H-47). Sources: `runtime/ipu/`; headers:
`runtime/include/p3fes/ipu/`; tests: `tests/ipu/`; provenance: `runtime/include/p3fes/ipu/THIRD_PARTY.md`.

Tags: **obs** read from the game's instructions (`recomp/generated/`, the M2 `--trace-hw` sequence in
`docs/INTEGRATION_LOG.md`) or a cited header; **der** derived from obs; **std** defined by ISO/IEC 13818-2 (MPEG-2)
or 11172-2 (MPEG-1); **inf** inferred — a choice, hardware-unverified (Phase 4 checks). No IPU manual was available
locally; no GPL source (PCSX2, PS2Recomp, libmpeg2, ffmpeg) was opened.

## Files

| File | Concern |
|---|---|
| `include/p3fes/ipu/ipu_regs.h` | addresses, field layout, command codes, the command words the game issues |
| `include/p3fes/ipu/mpeg2.h`, `mpeg2.cpp` | pure functions: scans, inverse quantisation, IDCT, RAW16 assembly, CSC, PACK |
| `vlc_tables.cpp` | Annex B code tables (ported rows) and their decoders (NeedBits / Invalid on short input) |
| `include/p3fes/ipu/ipu_core.h`, `ipu_core.cpp` | `IpuCore`: registers, FIFOs, bit reader, the command engine, timing |
| `include/p3fes/ipu/ipu_system.h`, `ipu_system.cpp` | `IpuSystem`: `HwDevice`s, `DmaChannelHandler`s, INTC 8, the device service |
| `NOTICE` | Play!'s BSD-2 notice (verbatim; it covers the ported VLC rows) |

## Registers (physical, `IpuSystem::attach` maps `0x10002000–0x10002040` and `0x10007000–0x10007020`)

| Register | Access | Model |
|---|---|---|
| `IPU_CMD 0x10002000` | write 32 (64 = low word): command; read 64: `DATA[31:0]` \| `BUSY` bit 63; read 32 at `+0` DATA, at `+4` BUSY in bit 31 | DATA = last VDEC/FDEC result (der: `_sceMpegWaitIpuIdle64 0x4FD4D8` `ld`s it and tests bit 63) |
| `IPU_CTRL 0x10002010` | read/write 32 | `IFC[3:0]` `OFC[7:4]` `CBP[13:8]` `ECD 14` `SCD 15` `IDP[17:16]` `AS 20` `IVF 21` `QST 22` `MP1 23` `PCT[26:24]` `RST 30` (write) `BUSY 31`. A write stores only IDP/AS/IVF/QST/MP1/PCT (the game writes CTRL read-modify-write, `_decMB0 0x4FCCA0`, `_pictureCodingExtension 0x4FF5C0`) |
| `IPU_BP 0x10002020` | read 32 | `BP[6:0]` `IFC[11:8]` `FP[17:16]` |
| `IPU_TOP 0x10002030` | read 64 (32 at `+0`/`+4`) | `BSTOP[31:0]` = the next 32 stream bits; `BUSY` bit 63 while the decoder still consumes bits or < 32 bits are buffered |
| out FIFO `0x10007000` | read 128 | one qword (CPU path; DMAC ch3 is the normal path) |
| in FIFO `0x10007010` | write 128 | one qword (`sceIpuInit 0x502B08` writes 8 + 2 qwords with `sq`) |

Any other offset, width or direction calls the trap handler (`IpuTrap::ReservedRegister`) and reads 0.

## Commands

| Code | Command | Fields | Implemented | Used by the game (obs) | Exactness |
|---|---|---|---|---|---|
| 0 | BCLR | BP[6:0] | input FIFO + FP emptied, BP set | `sceIpuInit`, `sceIpuRestartDMA 0x5028D8` (BCLR(BP)), `_sequenceHeader 0x4FEEE0`, `_sceMpegCscStoreRefImage 0x501DF8` | der |
| 1 | IDEC | FB, QSC, DTD, SGN, DTE, OFM | per MB: MB type (B.2), dct_type if DTD, quantiser_scale_code if quant, 6 intra blocks, CSC; then start code (8 zero bits) → byte-align, scan for `000001`, SCD; else MB address increment (stuffing/escape looped) | no | std decode; CSC inf; **SGN = 1 traps** (`Unsupported`, semantics unknown) |
| 2 | BDEC | FB, QSC, DT, DCR, MBI | CBP (B.9) unless MBI; DCR resets DC predictors to `128 << IDP`; intra DC (B.12/B.13), first non-intra coefficient `1s`, AC (B.14/B.15 by IVF), escapes (MPEG-2 12-bit, MPEG-1 8/16-bit), IQ, IDCT, RAW16 768 bytes | yes: `_decMB0` `0x20000000 \| MBI<<27 \| DCR<<26 \| DT<<25 \| QSC<<16` | std (IDCT: see below) |
| 3 | VDEC | FB, TBL | DATA = `length << 16 \| value[15:0]`; TBL 0 B.1 (stuffing `0x22` only with MP1, escape `0x23`), 1 MB type by PCT (1 I, 2 P, 3 B, 4 D), 2 B.10, 3 B.11 | yes: `0x30000000/34/38/3C000000` | table values std; result format der |
| 4 | FDEC | FB | skip FB, then DATA = next 32 bits (not consumed) | yes: `0x40000000 \| n` (`_sceMpegNextBit 0x4FD658`, `_sceMpegPeepBit 0x4FD740`, `_sceMpegFlushBuf 0x4FD7D0`, the M2 start-code scan) | der |
| 5 | SETIQ | FB, IQM | 64 bytes in zigzag order → intra (IQM 0) / non-intra (IQM 1) matrix | yes: `0x50000000`, `0x58000000` (from the FIFO in `sceIpuInit`, from the stream or a 4-qword DMA in `_sequenceHeader`) | der (the SDK's default tables at ELF `0x77F340/0x77F410` are zigzag-ordered) |
| 6 | SETVQ | (FB honoured) | 16 × u16 little-endian → VQ CLUT | yes: `0x60000000` (`sceIpuInit`, CLUT at ELF `0x77F460`) | der (the CLUT words only make sense little-endian) |
| 7 | CSC | MBC, DTE, OFM | MBC × RAW8 (384 bytes) → RGB32 (1024) / RGB16 (512) | yes: `0x70000000 \| n` RGB32, no dither (`_sceMpegCscStoreRefImage`, `_doCSC2 0x501C38` + `_ch3dmaCSC 0x5022D0` for n ≥ 1024) | conversion inf |
| 8 | PACK | MBC, DTE, OFM | MBC × RGB32 → RGB16 (OFM 1) / INDX4 via the VQ CLUT (OFM 0) | no | inf |
| 9 | SETTH | TH0[8:0], TH1[24:16] | thresholds for the CSC/IDEC alpha | yes: `0x90000000` (0, 0) | der |
| A–F | — | — | trap `ReservedCommand`, not started | no | — |

A command written while BUSY traps (`CommandWhileBusy`) and is ignored (the game always waits for idle; its
`_ch3dmaCSC` issues the next CSC from the D3 completion handler, which the timing rule below keeps legal).

## Data path

* **Input side** (der: `sceIpuStopDMA 0x5027F0` / `sceIpuRestartDMA` and CRI's ring-aware copies `sub_5946A8` /
  `sub_5947A8` rewind D4 by `FP + IFC` qwords and re-issue `BCLR(BP)`): up to 10 qwords — the 8-qword FIFO (IFC) plus
  the 2-qword bit-stream buffer (FP) — of which none is fully consumed; `FP = min(2, n)`, `IFC = n − FP`, BP = bits
  consumed of the first. A qword retires as soon as BP passes 128. `(IFC + FP) × 128 − BP` is exactly the number of
  buffered bits, the quantity `_sceMpegWaitIpuIdle 0x4FD370` computes. Tested end to end through the kernel DMAC
  (stop, reuse the IPU, rewind, the stream continues bit-exact).
* **Bit order:** bytes in FIFO (memory) order, bits MSB first — the MPEG byte stream (std). SETVQ/CSC/PACK read
  bytes in memory order.
* **Decoding is eager and element-atomic:** on every input push, output pop or command write the engine runs as far
  as the buffered bits and the output FIFO allow, one syntax element (≤ 32 bits: a VLC with its sign/escape payload,
  a DC size + differential, an IDEC MB header, a byte of SETIQ) at a time. An element that does not fit is not
  consumed; decoding resumes when data arrives, so a 10-qword buffer never deadlocks a macroblock of any size. The
  FB skip is its own element: an FDEC/VDEC/BDEC whose skip fits but whose code does not leaves BP advanced with
  < 32 bits buffered — the state the game's wait loop recognises as "ask the stream for more data" (der).
* **Output side:** 8-qword FIFO (OFC); the macroblock being emitted waits in a staging buffer (≤ 64 qwords) and moves
  into the FIFO as it drains. A CSC/PACK may load the next macroblock's input while the previous one drains; BDEC and
  IDEC stage one macroblock at a time.
* **Short input:** VLC decoding uses only the bits present; with fewer bits than the longest code it distinguishes
  "a code may still follow" (stall) from "no code can start with these bits" (invalid → ECD) through a prefix trie.
* **Errors:** an invalid code (or a run past coefficient 63, or no MB-type table for the PCT) sets ECD and ends the
  command; the offending bits stay unconsumed, already complete IDEC macroblocks are still delivered, VDEC DATA = 0.
  ECD/SCD clear when the next command is written (inf). SCD is set only by IDEC's start-code stop (inf).
* **RST** (CTRL bit 30) empties both FIFOs and the staging buffer, clears BP/ECD/SCD/CBP and aborts the command
  without a completion interrupt; the quantiser matrices, VQ CLUT, thresholds and DC predictors survive (der:
  `sceIpuInit` loads the matrices before its final RST).

## Timing (ADR-0013 §2)

A command completes at `max(issue + cost, the cycle its data flow ended)` — data flow = all input it needs consumed
and its last output qword in the output FIFO. BUSY (CMD bit 63 = CTRL bit 31) is set until then; completion raises
**INTC cause 8** once (ps2sdk `INTC_IPU`; the game never enables it — its interrupt census has no INTC 8 handler,
`docs/ANALYSIS/12` §4.4, and none is registered at the movie start, M2 log). The
completion check runs at every IPU access and DMA transfer (lazy, so a polling loop sees BUSY clear at exactly the
completion cycle) and in `IpuSystem::service()`. IPU_TOP becomes valid when the data flow ends, even while BUSY
waits out the cost (`_slice0 0x4FC3A8` reads TOP as soon as D3_QWC reaches 0 after BDEC).

| Command | BCLR | IDEC | BDEC | VDEC | FDEC | SETIQ | SETVQ | CSC | PACK | SETTH |
|---|---|---|---|---|---|---|---|---|---|---|
| cost (EE cycles, inf, `IpuCosts`) | 8 | 64 | 64 | 16 | 16 | 32 | 16 | 64 | 64 | 8 |

These are placeholders like the kernel's DMA `64 + 2/qword`. Streaming commands are dominated by the DMAC (its
stall retry every 64 cycles), which makes the IPU finish before the fromIPU channel's completion event — the
precondition of `_ch3dmaCSC` (tested). The game's "stuck" fallbacks (5000 / 500 polls in `_sceMpegWaitIpuIdle` /
`64`) are far above these costs.

## Exact vs approximate

**Exact to the standard (std) and tested:** every Annex B table used (rows cross-checked against hand vectors from the
printed tables, prefix-freeness, Kraft sums), escapes, the non-intra first-coefficient rule, intra DC prediction with
`intra_dc_precision`, zigzag/alternate scans, inverse quantisation for MPEG-2 (`(2·QF + k)·W·qs / 32` truncating,
saturation, mismatch control) and MPEG-1 (×8 DC, oddification, no mismatch control), linear/non-linear quantiser
scale, frame/field DCT luma placement, RAW16/RAW8 layouts.

**IDCT:** the double-precision IEEE 1180 reference form (direct 2-D sum, fixed `cos(kπ/16)` literals, the four
basis functions with u, v ∈ {0, 4} pinned to ±1/8 so DC-only blocks are exact), round half up, saturate to
[−256, 255], no FMA contraction — bit-identical on MSVC and clang-cl. Against an independent `std::cos` separable
reference on 6,000 IEEE 1180 random blocks (384,000 samples): **0 differences** (peak 0, MSE 0); tolerance stated in
the test: exact except within 1e-9 of a .5 tie (none occurred). The IPU's hardware IDCT is an unknown fixed-point
implementation; ±1 differences against hardware are possible (unverified).

**Derived from the game (der):** VDEC result format and the MPEG-2 stuffing rule, FDEC's non-consuming 32-bit
window and FB-first consumption, the FP/IFC/BP accounting, SETIQ zigzag order, SETVQ byte order, the RST survivors.

**Inferred (inf, Phase 4 checks):** CSC coefficients `149, 204, 50, 104, 258` with `+64 >> 7` and `Y − 16 ≥ 0`
(BT.601 × 128, agrees with ps2-web-recomp); 4:2:0 chroma by replication; alpha 0x00/0x40/0x80 by TH0/TH1 (`<`) and
the RGB16 A bit = alpha bit 7; the 4×4 dither matrix (the GS DIMX sample pattern, transposition unverified); PACK's
VQ metric (squared 5-bit distance, lowest index on ties) and INDX4 nibble order (even pixel low); IDEC SGN (trapped);
ECD/SCD clearing; the costs; FP = min(2, n); the D-picture table; VDEC decoding with exactly the bits it needs.
None of the inferred parts is on the game's path except the CSC conversion itself (RGB32, TH 0, no dither).

## Game usage (Sofdec over SDK 3.1 libmpeg; obs unless tagged)

1. Boot, `sceMpegInit 0x500A20 → sceIpuInit 0x502B08`: RST; BCLR; 8 qwords into the in-FIFO (default intra matrix
   zigzag-ordered from `0x77F410`, 4 qwords of 16); SETIQ `0x50000000`; SETIQ `0x58000000`; 2 qwords (VQ CLUT
   `0x77F460`); SETVQ; SETTH(0, 0); RST; BCLR — every step polled on CTRL.BUSY (the 26 accesses unhandled at M1).
2. Movie start, `_clearOnce 0x4FFDA8` / `sceMpegReset 0x500BB8`: CTRL MP1 on, D3/D4 cleared, RST; CRI
   `viBufCreate 0x594130 → sub_5941A8`: D4 MADR/TADR, `CHCR = 5` (M2 log). First decode, `sub_5947A8`: BCLR,
   CTRL = 0, `D4_CHCR = 0x30000105` — a source chain of 128-qword REF tags over the video ring buffer (M2 log).
3. Header parsing: `_sceMpegNextHeader 0x4FF9D8` / `flushByteBoundary 0x4FFB38` / `_sceMpegNextBit` scan for start
   codes with FDEC 0 / FDEC 8 and 64-bit IPU_CMD reads (M2 log); `_sequenceHeader 0x4FEEE0` loads quantiser matrices
   with SETIQ from the stream, or (default matrix) stops the stream DMA (callback 2), BCLR, sends 4 qwords from
   `0x77F340`/`0x77F380` with D4 normal mode, SETIQ, restarts the stream (callback 3). **Correction for
   `docs/ANALYSIS/14` §0/§5:** the "4 × `DIRECT`" constants at `_sequenceHeader` are the SETIQ words `0x50000000` /
   `0x58000000`, not VIF codes. `_pictureCodingExtension`: IDP, QST, IVF, AS into CTRL; `_decMB0`: PCT.
4. Macroblocks, `_slice0 0x4FC3A8` → `_sceMpegMbAddressIncrement 0x4FD1F8` (VDEC MBAI: 34 stuffing → again, 35 →
   +33, 0 → with MPEG-2 peek 11 bits == 15 → skip them), `_decMB0` (VDEC MB type; `_motionVector 0x4FC6D8` VDEC
   motion code + FDEC residual, VDEC DMV; `receiveDataFromIPU 0x4FE988` = D3 48 qwords; BDEC), then waits
   `D3_QWC == 0`, reads IPU_BP + IPU_TOP; motion compensation on the EE (`_doMC 0x4FBF48`, `_rix_*`).
5. Picture out, `_sceMpegCscStoreRefImage 0x501DF8`: stop stream DMA, RST if ECD, BCLR, D4 normal 24 qw/MB, D3
   64 qw/MB, CSC `0x70000000 | n` (n < 1024) or `_doCSC2` (CSC 1023 per round, re-armed by `_ch3dmaCSC` from the
   DMAC ch3 handler; `_ch4dma 0x502418` splits inputs > 0xFFFF qwords), restart stream DMA.
6. Error/abort paths: `_sceMpegErrorBdec 0x5025A0`, `_sceMpegStopIpuDma 0x502500`: RST + channel stops.

Not seen in the 42 functions that address the IPU or DMAC channels 3/4 with constant addresses (30 of them touch IPU
registers; scan of `recomp/generated/`, register-indirect accesses not covered): IDEC, PACK, CSC with RGB16/dither, a non-zero SETTH, CPU reads of the out
FIFO.

## Native movies (modernize layer 4, `--native movies`; `docs/MODERNIZE_PLAN.md` §3)

With `--native movies` the movie player's video never reaches this device: CRI's SFD video decoder, on its
"sceMpeg path" (`game/src/cri/libs13.cpp` 0x5941A8-0x595718), decodes each picture with a host decoder instead of
Sony's libmpeg driving the IPU (`runtime/native/movies/mpeg_video.h`, service `native_movies.h`, seam
`p3fes/native/movies_service.h`, game side `game/src/cri/sfd_native.cpp` / `p3fes/game/movies_native.h`). No IPU
command, no DMAC channel 3 / 4 transfer, no sceMpegInit / sceIpuInit at boot.

* **Swap point**: the SFD player's own glue to the platform pair, at the calls it makes: sceMpegInit (sub_594B88),
  sceMpegCreate + its four callbacks (sub_594C38), sceMpegReset / Delete (sub_595060), sceMpegGetPicture / RAW8
  (sub_595390: the player's picture call), and its five DMA helpers over the video-input ring (sub_5941A8 reset,
  sub_5944A8 flush, sub_5946A8 / sub_5947A8 stop / restart around a picture, sub_594AC0 destroy). Everything else
  of Sofdec -- the demux, the feed into the ring (sub_594EC8) and its free-space query, the start-code counter, the
  frame pool, the time codes, the display, the movie's ADX audio -- runs its faithful body. One level higher (the
  MPV / SFD decode step) would re-implement CRI's frame pool and timing; one lower is the IPU's registers.
* **The decoder** is libmpeg's picture loop on the host (sequence / GOP / picture headers and extensions, slices,
  macroblock headers, motion vectors, the reference rotation and display order: a reference is shown when the next
  is decoded, B pictures at once, the held reference at the sequence end; frameCount = the shown picture's number)
  over an `Engine`, the macroblock layer the IPU implements. `DirectEngine` reads bits on the host and calls this
  module's `mpeg2::` functions (the same VLC tables, the BDEC coefficient loop of `ipu_core.cpp`, IQ, IDCT, RAW16,
  CSC); `IpuEngine` drives an `IpuCore` with FDEC / VDEC / BDEC / SETIQ / CSC as libmpeg does (the stream fed as
  qwords, CSC after a BCLR with the stream stopped, the BCLR(BP) rewind). Motion compensation is libmpeg's
  (`_getRef0`, the `_rix_*` / `_ri0_*` kernels), including one quirk: the averaged luma kernel with both half-pel
  bits (`_rix_111`, the backward half of a bidirectional macroblock) reuses its rounding register after the first
  row, so rows 1..15 round with +1 instead of +2 (found by the in-game comparison: all 162 differing macroblocks of
  the first B picture were that case).
* **Output**: the shown picture as macroblocks in column-major order (macroblock (c, r) at c * mbh + r: the game
  uploads 16-pixel columns), RGB32 through the IPU's CSC (TH0 = TH1 = 0) or RAW8.
* **The ring**: 256 sectors of 2 KiB; the PS2's DMA chain covers the queued sectors (+16 from the head +12) and the
  flush adds the whole sectors written since (+20) and frees the ones the DMA has passed. Natively the "DMA
  position" is the decoder's read position plus the 10 qwords the DMA runs ahead into the IPU's FIFOs, never past the
  queued end, and the record's words evolve by the faithful arithmetic: with that model the ring record after every
  picture call equals the faithful one on the dorm, battle, fusion and shop routes (90 of 90 calls). A picture call
  that would read past the queued sectors takes CRI's starvation callback's path (sub_594F68): the 16-byte end code
  after the written data, the abort mark, the call returns -3 (tests/game/test_movies_native.cpp drives it at a
  movie's end).
* **Timing**: the call charges the guest the cycles the faithful call takes for the same work, modelled per call and
  per macroblock kind (least squares over 90 faithful calls; `native_movies.cpp` kCost*), with check points, so the
  player gets ready, decodes ahead and finishes at the faithful vblanks.
* **Scope**: MPEG-1, and MPEG-2 4:2:0 progressive frame pictures with frame_pred_frame_dct (every MPEG-2 movie of the
  disc: P3CTOP, P3FCT003, STAFF_ROLL_F); field pictures, field / dual-prime prediction, concealment vectors and D
  pictures report Unsupported (none on the disc).

## Integration (for the lead / `runtime/app`)

```cpp
#include "p3fes/ipu/ipu_system.h"
ipu_ = std::make_unique<ipu::IpuSystem>();
ipu_->attach(kernel_->bus());                       // maps 0x10002000-40, 0x10007000-20; DMAC ch3 + ch4 handlers
ipu_->set_trap_handler([&](const ipu::IpuTrap& t) { /* route to RtHooks::fatal (fail closed) */ });
kernel_->add_device_service([this] { return ipu_->service(); });  // before Kernel::start
```

Link `p3fes_ipu` into the host. Nothing else is needed: no syscall, no VU/GS coupling. Unattached, the first
`sceIpuInit` access is unhandled and the movie's first `D4_CHCR` write is a kernel fatal (M2 log).

## Performance (measured: MSVC 14.44 `/O2`, this host, scratch benchmark, 2 runs)

| Workload | Time |
|---|---|
| BDEC, dense intra MB (126 coefficients, 2,908 bits) | 7.1–7.2 µs/MB (8 ms for a 1,120-MB 640×448 frame) |
| CSC RGB32 | 2.9 µs/MB (3.2 ms per frame) |
| FDEC 8 with refill and completion | 0.05 µs per command |

The IDCT cost is proportional to the non-zero coefficients (64 multiply-adds each); typical Sofdec macroblocks are far
sparser than the dense case. CSC conversion is per pixel in scalar code; both are obvious SIMD candidates if M4 needs it.

## Tests (`tests/ipu/`, `p3fes_ipu_tests`)

`test_vlc` (structure + hand vectors of B.1–B.4, B.9–B.15, short-input NeedBits/Invalid), `test_idct_iq` (scans,
quantiser scale, MPEG-2/MPEG-1 IQ hand vectors, IDCT exact cases and the IEEE 1180 statistics), `test_csc_pack`
(hand-computed YCbCr→RGB, thresholds, 4:2:0 replication, RGB16, dither, PACK RGB16/INDX4), `test_core` (sceIpuInit
sequence, a sequence header with SETIQ at bit 95, BP/FP/IFC/TOP/FDEC, BCLR, every VDEC table, BDEC intra/non-intra/escapes/IVF/alternate scan/field DCT/
predictors/FB, errors, IDEC with SCD, CSC, PACK, dribbled-input equivalence, output back-pressure, TOP validity,
timing + INTC, RST, traps), `test_system` (`IpuSystem` on a fake bus; through the real kernel DMAC: REF-tag chain →
BDEC → RAM, CSC with D_STAT ordering, the Stop/RestartDMA rewind, the boot sequence, an MPEG-1 I-slice driven
like `_slice0`/`_decMB0`). All streams are hand-built; no
game data. 2026-10-19, msvc-x64-debug and clangcl-x64-debug, both from a HEAD snapshot + this module (`build/msvc-ipu`,
`build/clangcl-ipu`) and from the shared tree (`build/msvc-ipu-tree`, `build/clangcl-ipu-tree`): 44 cases / 47,464
assertions, exit 0, `/W4` 0 warnings, ~0.35 s.

## Open questions

1. The task brief named INTC cause 4 for the IPU; cause 4 is VIF0. ps2sdk `INTC_IPU` = 8, used here.
2. `HwBus` has no way for a device to ask for a service call at a new deadline, so INTC 8 is raised at the first IPU
   access / DMA transfer / service call at or after completion (deterministic; exact timing irrelevant while the game
   never unmasks cause 8). A `HwBus::schedule_service(u64)` would make it exact.
3. Hardware facts to settle in Phase 4 (PCSX2 state captures around a decoded frame): CSC rounding, the IDCT's bit
   pattern, VDEC's DATA[31:16], ECD/SCD behaviour, command latencies.
4. **Kernel DMAC restart window (for `runtime/hle/kernel`, not fixed here).** The kernel keeps `CHCR.STR` set until
   a completion event `64 + 2 x qwc` cycles after a transfer's data ended (160 cycles for BDEC's 48 qwords); a
   `CHCR = 0x100` written in that window is taken as a write to a running channel (`dmac_write`: `c.active &&
   now_set`) and the new transfer never starts (its MADR/QWC stay loaded, STR clears at the old event). The game's
   `_slice0` waits only for `D3_QWC == 0` before `_decMB0 → receiveDataFromIPU` re-arms D3 for the next macroblock,
   one MB-address VDEC and one MB-type VDEC later — plausibly inside 160 cycles (a first version of the in-repo
   slice test, which also restarted D3 right after `D3_QWC == 0`, lost the second macroblock's transfer this way;
   whether the game's own gap is shorter is unmeasured: it depends on the EE work in between). On hardware STR
   clears when the transfer ends. Suggested fix in the DMAC owner: a STR write while the channel's data phase is
   done but its completion event pending completes that event at once (D_STAT CIS, STR clear) and then starts the
   new transfer. `tests/ipu` waits for STR to clear to stay independent of this.
