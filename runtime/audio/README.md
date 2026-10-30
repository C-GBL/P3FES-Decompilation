# `runtime/audio/` — host audio (`p3fes_audio`)

Where the game's sound ends up on the host. The guest side is not here: SLUS_216.21 decodes ADX on
the EE (its own CRI library, recompiled) and streams 16-bit PCM to the IOP; the IOP HLE's model of
`CRI_ADXI.IRX` (`runtime/hle/sif/iop/srv_adxi.cpp`, `docs/ANALYSIS/16_iop_audio_modules.md`) mixes
that PCM as the module's PSM mixer would and pushes the result here. This library owns the sink
interfaces, the WAV / XAudio2 / null sinks, the `HostAudio` composition the host builds from its
command line, and a host-side ADX decoder for disc files.

| Header (`runtime/include/p3fes/audio/`) | Contents |
|---|---|
| `audio_sink.h` | `AudioSink` (48 kHz stereo s16, frames tagged with timeline positions), `StreamTap` (per-play-session PCM as the IOP consumed it), `NullSink` (counts + FNV-1a fingerprint), `TeeSink`/`TeeTap`, `TimelineCursor`, `frames_at_cycles` / `cycles_at_frame` |
| `wav.h` | `wav_image`, `WavWriter` (streaming PCM16, header patched on close), `WavSink` (timeline → one file, gaps as silence), `WavStreamDumper` (one file per stream) |
| `xaudio2_sink.h` | `XAudio2Sink`: one source voice, a ring of 1024-frame buffers, optional pacing |
| `host_audio.h` | `HostAudio` + `HostAudioOptions`, `default_dump_dir()` |
| `adx_decoder.h` | `adx_coefficients`, `adx_decode_frame`, `AdxDecoder` (mono/stereo, v4 loops), `decode_adx`, `decode_adx_to_wav` |
| `spu2_voice.h` | `Spu2Voices` (48 SPU2 voices over 2 MiB of voice RAM: ADPCM blocks, ADSR, pitch, L/R and master volume, KON/KOFF/ENDX, by libsd's parameter / switch / address codes), `adpcm_decode_block`, `Spu2Mixer` (sums the voices and the PSM stream into one 512-frame-pass stream for the `AudioSink`) — ADR-0014 milestone 2; ported shape from MIT `ps2-web-recomp` `spu2.cpp` (provenance line, `THIRD_PARTY_NOTICES.md`) |
| `spu2_backend.h` (`runtime/src/audio/`, in `p3fes_runtime`) | the original XAudio2 engine + mastering voice placeholder `main.cpp` creates; now exposes `engine()` so a sink can share it |

## Timing: audio from virtual time

* The timeline is integer frames at 48 kHz; one frame is exactly **6,144 EE cycles**
  (294,912,000 / 48,000), so `frames_at_cycles(c) = c / 6144`. The IOP's PSM model renders a
  **512-frame pass** (the half of PSMOUT's 4 KiB L/R AutoDMA buffer, `16` §6.3) whenever virtual
  time passes a pass boundary, and pushes it with its position. Silence is pushed while an output
  runs; while the IOP output is stopped (urpc 13/17, pause-all) nothing is pushed and the timeline
  has a gap.
* **SPU2 voices + PSM (`Spu2Mixer`, `IopConfig::sk_mode == Modules`, the default).** The interpreted
  SK modules key voices through the libsd HLE at the instants the IOP model acts (RPC calls, the 240 Hz
  SK tick), and `Spu2Mixer::advance_voices(frame)` renders the voices up to each such instant, so a
  key-on takes effect at its own frame. The PSM model keeps its own pass grid and consumption clock
  (nothing EE-visible changes) but pushes its passes into the mixer's `stream_sink()` instead of the
  host. The mixer emits passes `[g, g + 512)` on a grid anchored at frame 0 once virtual time passed
  `g + 1024` (by then the PSM model has delivered every stream frame below `g + 512`), summing voice
  output and stream, clipped to 16 bits; a pass with neither is skipped, so silence stays a timeline
  gap as before. `IopHle::flush_audio()` (the host's `flush_audio`) emits the last passes at exit.
  Consequence: pass positions, and with them the fingerprint, differ from `SkMode::Constants`
  (where the PSM model pushes directly, as in every run before SK increment 2).
* Nothing on the guest path reads the wall clock (ADR-0013 §4): a headless run's mix is a function
  of the run's inputs. `HostAudio` always feeds a `NullSink`, whose `hash()` / `frames()` are the
  determinism fingerprint (`describe()` prints them; `first_non_silent_frame()` marks the first
  audible frame, `capture.json` `audio.first_non_silent_frame`).
* `WavSink` writes gaps as silence relative to its first push. `XAudio2Sink` caps a gap's silence at
  its latency window (`max_queued_ms`, 120 ms) so the device never falls behind, drops (and counts)
  frames when its ring is full instead of blocking, and only with `pace` (windowed runs) blocks
  `push()` while more than `max_queued_ms` is queued — throttling a faster-than-real-time emulation
  to the audio clock. It never overwrites a queued buffer.

## Host wiring (the lead adds this; `main.cpp` belongs to the input agent)

```cpp
#include "p3fes/audio/host_audio.h"
// after the SifHle exists (GameHost owns it), with --dump-wav DIR parsed into dump_dir:
p3fes::audio::HostAudio audio({.xaudio2 = !headless, .pace = !headless, .dump_wav_dir = dump_dir,
                               .engine = spu2.is_initialised() ? spu2.engine() : nullptr});
sif.iop().set_audio_output(audio.mix_sink(), audio.stream_tap());
// ... run ...; at exit: audio.flush(); std::puts(audio.describe().c_str());
```

`--dump-wav DIR` (suggested default `default_dump_dir(repo root)` = gitignored
`extracted/_ours/wav/`): `DIR/mix_48k.wav` is the mix from the first pushed frame;
`DIR/stream_<id>_slot<rna>_<rate>hz_<ch>ch.wav` is every RNA play session's PCM exactly as the game
decoded and the IOP consumed it (before resampling and volume). For a disc file without running the
game: `decode_adx_to_wav(bytes, out, loops)`.

## ADX decoder

Encoding 3, 4-bit ADPCM, 18-byte frames, 1–2 channels, unencrypted. Hand-derived from the public
format description; every arithmetic detail checked against the game's own EE decoder
(`ADX_GetCoefficient 0x539858`, `ADX_DecodeMono4 0x53A410`, `16` §8): coefficients from the header's
high-pass cutoff in 12-bit fixed point with truncation (500 Hz → 48 kHz `(7400, −3342)`, 24 kHz
`(6687, −2729)`), effective scale `(scale & 0x1FFF) + 1`, prediction `(k0·h1 + k1·h2) >> 12`
(arithmetic), clamp to 16 bits, a scale word with bit 15 ends the stream. Stereo: one frame per
channel, interleaved, separate histories. Loops (v4 loop block): the loop region repeats bit-exactly
from the predictor state the first pass had at its start (inf — CRI's ADXT restart is not traced).

## SPU2 voice model (`spu2_voice.h`, ADR-0014 milestones 2-3)

The Standard Kit's sound effects: MODHSYN (interpreted in `runtime/hle/sif/iop`, README §9) keys
SPU2 voices through libsd — `SetAddr(SSA/LSAX)`, `SetParam(VOLL/VOLR/PITCH/ADSR1/ADSR2)`,
`SetSwitch(KON/KOFF)`, `GetSwitch(ENDX)`, `GetParam(ENVX)` — and the libsd HLE forwards them to
`Spu2Voices` by libsd's codes (`sd_code::*`, ps2sdk `libsd-common.h`). Per voice: a 16-byte ADPCM
block decoder (shift, the five filter pairs `{0,0} {60,0} {115,-52} {98,-55} {122,-60}`, clamp; flags
loop-start → LSAX unless written explicitly, loop-end → jump to LSAX, loop-end without repeat → the
sample ends when that block has played out and ENDX is set), a 16.12 position stepped by
`min(PITCH, 0x3FFF)` (0x1000 = one sample per 48 kHz frame), the SPU2 envelope (attack / decay /
sustain / release on the rate formula `shift = rate >> 2`, step `(7 - (rate & 3)) << max(0, 11 - shift)`
every `1 << max(0, shift - 11)` frames, exponential variants), fixed L/R gains and `SD_CORE_MUTE_ENABLE`.

* **Interpolation** (milestone 3): the hardware's 4-tap gaussian, from the public SPU description (nocash
  psx-spx "4-Point Gaussian Interpolation"; the SPU2 keeps the SPU's 512-entry table): with
  `i = (position >> 4) & 0xFF`, `out = g[0xFF-i]·s[-3] + g[0x1FF-i]·s[-2] + g[0x100+i]·s[-1] + g[i]·s[0]`,
  each product `>> 15` on its own. The voice buffer keeps the three samples before the current block
  as taps (zero after a key-on). Linear interpolation stays selectable (`--spu2-interp linear`,
  `IopConfig::spu2_gaussian`, `Spu2Voices::set_interpolation`) for A/B and for tests that check
  decoded samples exactly; `capture.json` `sk.interp` records which one ran.
* **Key-off and the end** (milestone 3): a key-off of a voice in attack/decay/sustain enters release at
  its current level with the rate counter restarted (`sk.key_offs_sounding` counts these; a key-off of
  an idle or already releasing voice changes nothing); release runs to level 0 and the voice goes Off.
  A loop-end block without repeat sets ENDX when it is shifted out and ends the voice at level 0 on
  that frame. `sk.voices_active` (at the snapshot), `sk.voices_active_max` and `sk.voice_longest_frames`
  (key-on to Off of the longest finished voice) are the stuck-voice accounting: a voice that never
  ends shows as `voices_active > 0` between sounds.
* **Init image** (milestone 3): `sceSdInit(flag)` → `Spu2Voices::reset(flag)`, the register image of
  ps2sdk libsd `freesd.c` (AFL-2.0, values only): KOFF to every voice, VMIX/VMIXE all on, MMIX
  `0xFF0` / `0xFFC`, AVOL core 0 = 0, core 1 = `0x7FFF`, BVOL 0, and with `flag & 1 == 0` MVOL 0 and
  EVOL 0. The power-on state is the same image without counted key-offs.
* **Volume law and the two-core chain** (milestone 3): core 1 is the output. Core 1's dry voice sum
  (MMIX1 bits 11/10) and its external input — core 0's output, `MVOL0 × (core-0 dry voices)`, through
  `AVOL1` and MMIX1 bits 3/2 — are scaled by `MVOL1`; each stage is a Q15 product. MVOL and the voice
  volumes are the sweep-capable kind: bit 15 selects sweep mode (not modelled: full scale, counted in
  `sk.volume_sweeps`, 0 on every route so far), else bits 0..14 are a signed level doubled to Q15
  (`0x3FFF → 0x7FFE`; bit 14 is the sign). AVOL/BVOL/EVOL are plain signed 16-bit gains.
  `SOUND_Control (3, 0x80, L, R)` (the game sends `(127, 127)` every frame from `sub_108BC0`) makes
  SKSOUND write **`MVOL1 = (value × 129) & 0x7FFF`** through libsd (measured through the interpreted
  modules, `tests/sif/test_sk_modules.cpp`: 127 → `0x3FFF`, 64 → `0x2040`, 1 → `0x81`, 0 → 0, 128 →
  `0x4080` = a phase-inverted level, 255 → `0x7F`); a write that leaves the value unchanged is not a
  `CORE` line, so the per-frame `(127, 127)` shows once. The game's own writes (dorm sound log `CORE`
  lines): `MVOL0 = 0x3FFF` at vblank 0, `MMIX0 = 0xFC0`, `MMIX1 = 0xFCC` (no memory-input wet bits:
  the stream is never sent to the effect), then `MVOL1 = 0x3FFF` from the first `SOUND_Control 0x80`.
* **The ADX stream** enters core 1 (CRI_ADXI `spucore=1`) as its memory input: `Spu2Mixer` scales each
  512-frame pass of it by `stream_gain_l/r()` = `MVOL1` through MMIX1 bits 7/6 (or the core-0 chain
  when the stream sits on core 0), sampled when the voices first advance into that pass. Its BVOL is
  CRI_ADXI's (an IRX the port models as a whole, never through this libsd; the SK stack never writes
  BVOL — no `CORE` line), so it is taken as full scale. Checked against PCSX2: the same ADX samples
  come out at **-0.09 dB** (least-squares gain 0.9894, waveform NCC 0.997; "A/B against PCSX2" below).

### Reverb (decision, milestone 3)

The game turns the SPU2 effect **on**: at vblank 0-1 of the dorm route the modules call
`sceSdSetEffectAttr` with mode `0x105` (mode 5 with the clear-work-area bit) and delay `0x3C` on both
cores, write `EVOL = 0x3C78` L/R on both cores and set core attribute 1 (effect enable); every SE
key-on then writes `VMIXEL/VMIXER` bits for its voices (the `CORE` lines `kind 2 code 0x19/0x1B`).
The model **stores** all of this (EVOL, ESA/EEA, VMIXE*, the effect attributes; `LibsdHle::effect_attr`,
`set_effect_attr` mirrors the depths into EVOL as libsd's `effect.c` does) and **renders the dry path
only** (`tests/audio` "Reverb decision": identical output whatever the effect registers hold).
Reason: the reverb is a 22-register IIR/comb network over a work area in voice RAM; the SPU's public
description (psx-spx "SPU Reverb Formula") covers the algorithm, but the per-mode register presets
live in libsd's `effect.c` and the SPU2's work-area addressing and 48 kHz/2 timing are not described
publicly, and the GPL PCSX2 source is off limits (ADR-0014 §3). The audible cost, measured: after the
first decide SE the title BGM fades out the same way on both sides (-47.6 / -47.0 dBFS 0.53-0.88 s
after the onset, -53.9 / -55.3 dBFS 0.88-1.08 s), then PCSX2 keeps a decorrelated (L/R NCC -0.2) residual
of -76.7 dBFS (1.08-1.58 s, peak 46) and -93.6 dBFS (1.58-2.18 s, peak 9) — consistent with the
effect's tail — where the port is digitally silent; inside the first 250 ms the floor-corrected SE
level differs by 0.25-0.31 dB and the SE-dominated octave bands by at most 0.1 dB. Rendering the reverb is a
milestone-4 item (with the battle bank), from the public algorithm and libsd's presets.

## A/B against PCSX2 (`tools/ours/pcsx2/audio_ab.py`, milestone 3)

Reference: a PCSX2 2.8.2 recording of the title screen and the memory-card prompt
(`tools/ours/pcsx2/audio_capture.py`, docs/PCSX2.md §12; 15.3 s, 48 kHz stereo), keys Cross, Cross,
Down, Cross 3 s apart — the same four presses as `to_dorm.txt` vblanks 1385/1557/1804/1819 (SEs
`(0, 1)` decide, `(0, 1)`, `(0, 0)` cursor, `(0, 1)` at vblanks 1387/1559/1805/1821). Ours: the dorm
replay's `--dump-wav DIR/mix_48k.wav` (index = timeline frame). Method: PCSX2 onsets from the RMS
detector, ours from the first KON line of each SE, the ours onset then moved by the lag (±40 ms) that
maximizes the NCC of the 1 ms floor-corrected envelopes; per SE window RMS / peak per channel, the
floor-corrected SE RMS (the 500 ms before subtracted in power), the envelope NCC, octave-band energies
of the first 250 ms (floor-corrected; bands where the SE dominates on both sides) and their
log-spectral distance; `bgm` aligns a stretch of the ADX stream between SEs by envelope then
waveform NCC and fits the gain. Numbers: `docs/INTEGRATION_LOG.md` "SK modules, increment 3".

## What is not modelled

* Reverb (decision above), Dolby Pro Logic II, digital out, voice volume sweeps (counted), noise,
  pitch modulation, voice IRQs, AutoDMA (the PSM stream enters through the mixer), the ADX stream's
  BVOL (full scale; CRI_ADXI's register).
* CRI's RCV rate converter (linear interpolation here) and PSMMIX's use of the side gains (gain/255
  here); the gains themselves follow the IRX's volume/pan tables (`16` §6.2).

## Tests

`tests/audio/` (`p3fes_audio_tests`): coefficients for five rates; frame vectors computed by an
independent oracle from the format description and the decoder's arithmetic (first samples
hand-checked in the comments): zero coefficients, history carry across frames, saturation, a
non-zero starting history, the end marker; whole files built in the test (mono stopping mid-frame,
stereo with separate histories, v4 loop repetition + tail, refusals); WAV header and writer, gap
filling, the per-stream dumper's interleave/padding; timeline math (exact 48 kHz, 44.1 kHz
floor/ceil round trip, 10 h without overflow); `NullSink` gaps/clips/fingerprint; `HostAudio`
headless. `test_spu2_voice.cpp`: hand-computed ADPCM vectors (filter 0 nibble values, filters 1–4
predictions, shifts 0/11/12, clamp, flags, history carry), the envelope formula (rates 0/4/48/50/124,
exponential increase above 0x6000, exponential decrease never sticking) and its phase transitions
through a voice, pitch 0x1000 reproducing a block one sample per frame and 0x800 interpolating,
ENDX / end-flag stop / loop repeat / explicit LSAX, L/R and master gains and MUTE, the mixer's grid,
two-pass latency, stream + voice sum, clipping and gaps. Milestone 3: the gaussian table (four weights
of every index sum to `0x7F7F..0x7F81`) and its taps at pitch 0x1000 and 0x800 across a block boundary,
the end block's ENDX/stop frame; release after a key-off while sounding (linear: exactly 4,096 frames
from full scale at rate 0x0B; exponential: never sticking) with the counters (`key_offs_sounding`,
`active_voices_max`, `longest_voice_frames`); the volume law (libsd's init image, `reset(1)` keeping
MVOL/EVOL, MVOL1 on core 1, the core-0 chain through AVOL1 and the MMIX bits, MUTE on core 1
silencing core 0, the stream gain, sweep counting); the stream scaled per pass with a master-volume
change taking effect from the next pass; the reverb decision (dry output identical with the effect
registers set). With `extracted/` present one more case
decodes `BGM/0501.ADX` to its header's sample count, and `COMSE.BD`'s first `Vagi` entry (489 blocks,
44.1 kHz) played through the voice model equals a direct decode of the same bytes sample for sample.
IOP-side behaviour (DTX, SJX, PSM consumption and mix, SK values; the routed H_Sndcom flow keying
voices through the real modules) is tested in `tests/sif/test_adxi.cpp` / `test_sk_modules.cpp`.
