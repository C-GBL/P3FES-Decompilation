# 19 — SPU2 sequenced sound (SDRDRV / Standard Kit / MODSESQ / MODHSYN): design study for Phase 6

_Read-only study, 2026-10-19. Sources: the EE binary (`extracted/disc/SLUS_216.21`, ps2dev objdump, VAs),
the LIB31 IRX modules disassembled into **new** gitignored databases `ida/work_irx_{sdrdrv,sksound,skhsynth,
sksesq,modsesq,modhsyn,libsd}.i64` with `tools/ours/ida/open_irx.py` (listings `ida/logs/irx/<MODULE>.asm`;
IRX addresses are **module offsets**), the game's bank files under `extracted/DATA/SOUND/`, our M4 snapshot
`extracted/_ours/dorm_m4_4762/eeMemory.bin`, and PCSX2's `extracted/_pcsx2/{dorm,title_runC}/{eeMemory,SPU2}.bin`.
The master `ida/p3fes.i64` was not opened; no game was run; no GPL source was read (ADR-0010 §4).
Tags: **obs** read from instructions/bytes; **obs-P** read from a PCSX2 save state; **der** derived; **inf** inferred._

## 0. Headline

* **The SK stack is the game's SFX path only.** BGM and voice are CRI ADX (`16`); the Standard Kit plays
  **SE banks**: the EE uploads two banks on every route (`sound/spu/comse.{hd,bd,sq}` = common SE,
  `sound/spu/bse.*` = battle SE) and triggers sounds with `SESQ_Control(port, 0, 10, group, entry)` from one
  game API (`sub_10A4E0 → H_Sndcom_PlayVoice 0x10DB60`) that has **512 call sites** (obs). The third bank
  triple in the table (`sound/BSE.*`, a `Prog/Sset/Smpl/Midi` MIDI bank) is **never requested** (obs/obs-P
  §1.3) and the MIDI modules are never loaded (B-20): there is no sequenced BGM in this game.
* **What the EE sends is thin; the behaviour is on the IOP.** The RPC carries bank pointers and (group, entry)
  pairs. Everything audible — a 35-opcode SE sequencer (MODSESQ `0xC9C`), a hardware-synth module that keys
  SPU2 voices through libsd (MODHSYN, 226 functions, 48.7 KB of code), a 240 Hz tick (SKSOUND hard timer,
  4,167 µs) — lives in six IRX modules totalling **80,592 bytes of text** that nothing in the port executes.
* **Recommendation: run those six modules on a small R3000 interpreter inside the existing IOP HLE, with the
  IOP kernel imports and the libsd layer HLE'd, libsd driving a host SPU2 voice model** (option B-lite, §3).
  It is the cheapest route to bit-faithful sequencing (the game's own IRX bytes, loaded from `extracted/` at
  run time like the ELF), it stays on virtual time, and it later gives Phase 5 an oracle to pair-test any
  hand-decompiled replacement against. Estimate 3–4 weeks; options A/C 5–10 weeks with lower fidelity or no
  oracle; a full IOP emulator 8–12 weeks and it would re-do `runtime/hle/sif` wholesale.

## 1. What the EE sends

### 1.1 Command set actually used (obs, EE)

| Call (EE) | RPC `0x80000701` code / SK block | Payload (words) | Callers | HLE today (`srv_sdr.cpp`) |
|---|---|---|---|---|
| `sceSdRemote(0x8010)` SetParam | `0x8010` | `{reg, val}`: `(0x800,4032)`, `(0x801,4044)` from `H_Sndcom_Init 0x10CAC0`; `(0x980,0x3FFF)`, `(0xA80,0x3FFF)`, `(0x981,0)`, `(0xA81,0)` from `sceSkSsInit 0x51DA50` | boot | register shadow → 0 |
| `sceSdRemoteCallbackInit 0x512D48` | `0xE620` | six `0x780000` | boot | 0 (thread not modelled; binds EE `0x80000704` on hardware, `16` §9.5) |
| `sceSkSsSOUND_Control 0x51DB00` | `0x90F0`, module 0 fn 2 | `{port, cmd, a, b}`: init `(0,143,0) (3,131,261,60) (3,132,60,60) (3,130,1) (3,128,127,127)`; **`(3,128,127,127)` every `kwlnUpdate`** (`sub_108BC0 0x108BF0`, called at `0x1983F8`) | boot + per frame | `0x80`→master volume shadow, `0x81/82/84/8F`→0, `0x83`→0 |
| `sceSkSsSOUND_Send 0x51DBC0` | module 0 fn 10 | `{1, iop_src, spu_dst, n}` chunks ≤ 4096 B (`H_Sndcom_Update 0x10D0F4`) or ≤ 65536 B (`0x10D53C`) | bank load | memcpy into a 2 MiB SPU-RAM shadow, returns `n` |
| `sceSkSsHSYNTH_Bind 0x51DC70` | module 1 fn 0 | `(3, -1, hd, hdsize, spu, bdsize)` → entry; `(5, -1, entry, 0)` → port (`0x10D2A8`, `0x10D304`; state-8 path `0x10D620/0x10D640`) | bank load | 0-based entry / port |
| `sceSkSsSESQ_Bind 0x51DDF0` | module 4 fn 0 | `(0, -1, sq, sqsize)` → entry; `(5, port, entry)` → **port** (`0x10D360`, `0x10D3B4`) | bank load | entry / port |
| `sceSkSsSESQ_Control 0x51DF58` | module 4 fn 2 | play `(port, 0, 10, group, entry)` → track (`H_Sndcom_PlayVoice 0x10DCC0`); stop `(port, 2, 10, track)` (`0x10DC60`, `H_Sndcom_StopVoice 0x10DB38`) | SFX | round-robin 0-based track / 0 |
| `sceSkSsSESQ_Status 0x51E028` | module 4 fn 3 | `(port, 1, 10, track)` before every stop (`0x10DC48`, `0x10DB20`); result ignored | SFX | 0 |
| `…_Unbind` ×2 | module 1/4 fn 1 | from `H_Sndcom_UnbindSfx 0x10D950` only (bank unload) | never on the dorm route | frees slot, 0 |

Block layout: 64 bytes at `sk_{sound,hsynth,sesq}_cmdblk 0x782B80/BC0/C00`, word0 = module << 24, word1 =
function, words 2+ = args; reply 16 bytes, result = word0 (L-30/L-31; code is `0x90F0`, `sif/README` §6).

### 1.2 The EE-side objects (obs)

| Object | Address | Layout |
|---|---|---|
| Bank slots `sSndcomWork` | `0x833710`, 6 × 68 B | `+0 h state` (1 loaded, 2 requested, 3…8 loading), `+2 h file idx` (×3 into `tbl_H_Sndcom_BankFiles 0x5D53A0`), `+0x18 hd iop`, `+0x1C hdsize`, `+0x20 spu addr`, `+0x24 bdsize`, `+0x28 sq iop`, `+0x2C sqsize`, `+0x40 SESQ port` (`0x10D3BC`) |
| SE channels | `0x833650`, 16 × 12 B | `+0 playing`, `+4 h slot`, `+8 track handle` (`H_Sndcom_PlayVoice 0x10DC8C–0x10DCD4`) |
| Bank requests | `0x7E5770`, 6 × 40 B | `+0 h state`, `+2 h file idx`, `+12 h mode` (0 → `sub_10D6F0` file load, else `sub_10D7B0` pointers already in EE RAM) — driven by `sub_108E80` |
| Bank file table | `0x5D53A0` | idx 0 `sound/BSE.{hd,bd,sq}` (`0x5D52A8…`), idx 1 `sound/spu/comse.*` (`0x5D52E0…`), idx 2 `sound/spu/bse.*` (`0x5D5340…`) |
| SPU budget | `sceSpu2MemAllocate 0x51D6F8` | 614,400 + 716,800 + 4 × 102,400 B (`0x10CBB0–0x10CC2C`, L-32) |

### 1.3 What the dorm route exercises (obs: our M4 snapshot; obs-P: PCSX2 dorm and title states)

| Fact | Ours (vblank 4,762) | PCSX2 dorm / title |
|---|---|---|
| Requests `0x7E5770` | `{1, idx 1}`, `{1, idx 2}`, four idle | identical |
| Slot 0 = COMSE | hd `0xC6400`/`0x2860` (= 10,336 = `COMSE.HD`), spu **`0x5010`**, bd `0x8C180` (= 573,824 = `COMSE.BD`), sq `0xD3500`/`0xF40`, port 0 | hd `0x103800`, same sizes, spu `0x5010`, port 0 |
| Slot 1 = BSE (SPU) | hd `0xC8D00`/`0xA7C0` (42,944), spu **`0x9B010`**, bd `0xAAC90` (699,536), sq `0x2DE0`, port 1 | hd `0x106100`, same, port 1 |
| SE channels in use | ch0 `{1, slot 0, track 0}`, ch1 `{1, slot 0, track 1}` | dorm: tracks **`0x15`, `0x1A`**; title: none playing |
| SPU RAM | shadow only | `SPU2.bin`: `COMSE.BD` body at file offset `0x15014`, `BSE.BD` at `0xAB014` = `0x10004` + spu addr (der: 0x10004-byte state header) |
| Sound requests counted | **8,142** (`capture.json`; ≈ 47 are DTX: 45 urpcs + 2 creates) | — |

Both banks are uploaded during boot (slot states 1 already at M2, `chk_m2`); the dorm event plays only COMSE
sounds; the request count is dominated by the per-frame `SOUND_Control(3,128,127,127)` (one per `kwlnUpdate`)
plus 312 `SOUND_Send` chunks (573,824/4096 + 699,536/4096 = 141 + 171) and the SE triggers (inf: the
remainder, ≈ 3,000, are `SESQ_Control/Status` calls; the HLE's `sound_log()` keeps only the newest 256, so a
full dump is the first implementation task).

### 1.4 The M1–M4 diff classes this explains

* **SK ids / "sound-command rings"** (`sk_sesq_cmdblk+`, `g_sndcomSifDmaReq+`, channel handles): PCSX2's
  track handles are `0x15`/`0x1A` because MODSESQ allocates tracks **round-robin from the last one + 1 over a
  32-bit mask** (`0x2248–0x22A4`, `dword_2B60`), whereas the HLE hands out the first free index (obs vs
  `srv_sdr.cpp` `sk_sesq`). Running the IRX removes this class; a hand model must copy the allocator.
* **"SK sound-bank heap shift"** (`INTEGRATION_LOG` "Remaining divergences" 4): the only SK replies the EE
  stores are the Bind ids (slot `+0x40`), the `SOUND_Send` return and the track handles; none sizes an EE
  allocation in `H_Sndcom_Update` (obs: the allocations there are `sceSifAllocSysMemory`, IOP side). inf: the
  0x30 B shift is downstream of the IOP-heap addresses (`0xC6400` vs `0x103800`) copied into EE structures,
  i.e. the IOP-identity class, not an SK reply — to confirm with `--watch-write` when the heap is modelled.

## 2. What the IOP does with them

### 2.1 Modules and layering (obs: import/export tables in the listings)

| Module | text / fns | Role | Imports it needs |
|---|---|---|---|
| `SDRDRV` | 4,912 B / 65 | RPC `0x80000701`; libsd codes `0x8000…0x81D0` → libsd; `0x90F0` → user slot (`0x588` switch, `16` §9.1) | libsd (26 fns), sifcmd, thbase, intrman |
| `SKSOUND` | 5,616 B / 71 | registers `0x90F0` (`sceSdrSetUserCommandFunction`, `0xDD4`); module dispatch `0xD30`; **tick**: `AllocHardTimer(1, 0x20, 1)` + `SetTimerHandler(sub_1140)` + `SetupHardTimer(t, 1, 0, 1)` at `USec2SysClock(dword_17B0)`, default **`0x1047` = 4,167 µs ≈ 240 Hz** (`0x14–0x18`; "tickresolution=" arg not given by the game); handler `iWakeupThread`s the SK thread `sub_EE0`, which calls up to 11 registered callbacks (`dword_17C0` mask, `dword_17C4` table, export 6 registers) under `CpuSuspendIntr` | libsd (7), thbase, thsemap, timrman, sysmem, intrman |
| `SKHSYNTH` | 5,632 B / 50 | Bind `0x820`: type 3 → `modhsyn_6` (SetBank: hd/bd pointers, `0xC08`), type 5 → port; tick callback `sub_1B0` → **`modhsyn_5`** (MODHSYN tick) | modhsyn (15 fns), sksound, libsd Get* (2) |
| `SKSESQ` | 5,136 B / 46 | Bind `0x770`: type 0 → `modsesq_6` (bind sequence data to a slot, `0xA0C`), stores `skhsynth_4(port)` (the HSYNTH **port struct**, `0x1780 + 1032·port`) in the SESQ port (`0x9E4`); Control `0xCFC`: `modsesq_7(ctx, port, group & 0xFF, entry & 0xFF)` → track, then `modsesq_9(ctx, port, track, cmd 7 ? 1 : 0x101)`; cmd 2 → `modsesq_9(…, stop)`; tick callback `sub_230` → **`modsesq_5`** | modsesq (9 fns), skhsynth (2), sksound |
| `MODSESQ` | 10,592 B / 38 | the SE sequencer: `sub_440` (export 6) binds data to a port slot and resets its track records (defaults vol `0x7F`, pan `0x40`, tempo `0x3E8`); `sub_21F8` (export 7) resolves **(group, entry)** through the two-level offset table (§2.3) and allocates a track; `sub_730` (export 5) tick → `sub_1AEC` per track → **`sub_C9C`: a 35-case opcode switch (`0xE74`)** | sysclib/stdio/intrman only — **no modhsyn import, no `jalr`** (obs) |
| `MODHSYN` | 48,704 B / 226 | the hardware synth: `sub_39C` (export 6) validates the HD chunks by name (`"SCEI"`, `"Vers"`, `"Head"`, `"Prog"`, `"Sset"`, `"Smpl"`, `"Vagi"`, `"Setb"`, strings `0xBE60–0xBE98`, `0x4F4–0x62C`); tick `sub_1890` (export 5) reads voice end flags (`sceSdGetSwitch` ×4 via `sub_A68C`, `0x195C–0x19B0`) and runs `sub_3DDC`/`sub_5428`/`sub_572C`; every libsd call goes through one trampoline each (`sub_A528` SetParam 16 callers, `sub_A614` SetSwitch 12, `sub_A5A4` GetParam 3, `sub_A6FC` SetAddr 2, `sub_A7E4` SetCoreAttr 3, `sub_AD48/ADC4` Set/GetEffectAttr 3 + 2, `sub_AAD0` VoiceTrans 1, `sub_AC30` VoiceTransStatus 2, `sub_A860` Note2Pitch 1 — **ProcBatch/ProcBatchEx, BlockTrans, GetAddr trampolines have 0 callers**); reads `GetSystemTime` at `0x4990`, `0x5FF8`, `0x62E8` | libsd (19 fns), thbase (2), intrman |
| `LIBSD` | 19,376 B / 80 | the register driver (SPU2 at `0x1F900000`, SPU DMA, SPU2 interrupt) | intrman, sifman, thevent |

inf (from the three obs above): MODSESQ drives MODHSYN **through the HSYNTH port struct** it is handed — it
writes note/control messages into the port's buffer and MODHSYN's tick consumes them (Sony's SK design:
sequencer modules produce messages, the synth module keys voices). The exact message format is the first
thing an implementation must read (`sub_C9C` cases 0–7, 10–18, 32–34 vs MODHSYN `sub_62E0`).

### 2.2 Data formats on the disc (obs: bytes under `extracted/DATA/SOUND/`)

| File | Chunks (`"IECS"` + reversed tag + size) | Notes |
|---|---|---|
| `SPU/COMSE.HD` 10,336 B | `Vers` 0x10 · `Head` 0x40 (offsets: Prog/Sset/Smpl −1, **Vagi `0x50`**, **Setb `0x2E0`**) · `Vagi` 0x290 (53 entries × 8 B `{u32 bd_offset, u16 rate 44100, u8 loop 0, u8 0xFF}`) · `Setb` 0x2580 | the SE-table bank form (`Setb`); MODHSYN `sub_39C` accepts it with Prog/Sset/Smpl absent |
| `SPU/COMSE.BD` 573,824 B | raw SPU2 ADPCM (16-byte blocks, 4-bit, flags byte) | body = SPU RAM `0x5010…` |
| `SPU/COMSE.SQ` 3,904 B | `Vers` · `Sequ` 0x20 · **`Sesq`** 0xF10: header `{6, 0x10, vol 0x7F, pan 0x40, tempo 0x3E8, …}`, 7 group offsets (`0x3C, 0x250, 0x720, 0x9F0, 0xA4C, 0xAEC, 0xE7C`), each group `{count 12, …, entry offsets 0x80, 0xA0, …}` → entry = opcode stream | matches `sub_21F8`: group table at data+0x10, entry table at group+4, `−1` = empty |
| `SPU/BSE.{HD,BD,SQ}` 42,944 / 699,536 / 11,744 B | same shapes (`Setb` 0xA4E0, `Sesq` 0x2DB0) | battle SE |
| `SPU/BSE.SE` 755,328 B, `TEST.*` | not referenced by the table | dev leftovers |
| `sound/BSE.{HD,BD,SQ}` | `Prog/Sset/Smpl/Vagi` + `Midi` 0x370 | MIDI form; needs MODMIDI (never loaded) |

ps2sdk (`tools/third_party/ps2sdk/iop/sound/sdhd/include/sdhd.h`, AFL-2.0) documents the `Prog/Sset/Smpl/Vagi`
records (`SceSdHdSampleADSR`, `SceSdHdVAGInfoParam`, …) but **not `Setb` or `Sesq`**; those two must be read
from MODHSYN/MODSESQ. The SE opcode set has 35 cases of which the listing groups 0/1, 2, 3/4, 5/32/33,
6/10/11, 7, 12/13, 14/15, 16/17, 18/34 and leaves 8, 9, 19–31 to the default (obs `0xE5C–0x10DC`).

### 2.3 From RPC to SPU2 voice (der from §2.1)

```
EE SESQ_Control(port,0,10,g,e) ─► SDRDRV 0x588 ─► SKSOUND 0xD30 ─► SKSESQ 0xCFC ─► MODSESQ 0x21F8 (track)
                                                                          └─► 0x1E20 (start, flag 1/0x101)
SKSOUND hard timer 4,167 µs ─► thread 0xEE0 ─► SKSESQ 0x230 → MODSESQ tick 0x730 → 0x1AEC → 0xC9C (opcodes)
                                           └─► SKHSYNTH 0x1B0 → MODHSYN tick 0x1890: messages → voices →
                                                 libsd SetAddr(SSA/LSAX) · SetParam(VOLL/VOLR/PITCH/ADSR1/2)
                                                 · SetSwitch(KON/KOFF) · GetSwitch(ENDX) · SetCoreAttr/EffectAttr
EE SOUND_Send(1, iop, spu, n) ─► SKSOUND 0xA00 ─► sceSdVoiceTrans(ch 0, mode 0, iop, spu, n) + wait ─► SPU RAM
```

SPU2 features the stack touches (obs: the trampolines' callers; semantics inf from libsd's public API,
`ps2sdk/iop/sound/libsd/include/libsd.h`): per-voice volume L/R, pitch, ADSR1/ADSR2, start/loop address, key
on/off, end-flag polling; core attributes and effect (reverb) attributes/depth (`SOUND_Control 0x83/0x84` at
init only); master volume via `SetParam 0x981/0xA81` (the per-frame call). No pitch-modulation/noise switches
are set by MODHSYN's callers (inf: not seen among the 12 SetSwitch sites' constants — to confirm). PSM's ADX
stream enters the same SPU2 core 0 by AutoDMA (`16` §6.3), so the host mix is `voices + PSM`.

## 3. Options

Common to all: a host **SPU2 voice model** (48 voices: ADPCM block decoder with the 5 filter pairs and
loop flags, 4-phase ADSR, pitch step ≤ 0x3FFF, L/R volume, output at 48 kHz in the same 512-frame passes as
the PSM model, pushed to the existing `AudioSink`); reverb optional (can stay unmodelled first). The MIT
reference `ps2-web-recomp/runtime/src/iop/spu2.cpp` (614 lines; voices, ADSR, IRQ, no reverb, obs) is a
permitted port source with provenance lines (ADR-0010 §2; done before for hilo/MMI/FPU/VU0).

| | A — HLE at the RPC boundary with a host sequencer | B — full IOP emulator | **B-lite — interpret the 6 SK modules inside the IOP HLE** | C — hand-decompile MODSESQ+MODHSYN to host C++ |
|---|---|---|---|---|
| What runs | our own sequencer/synth written from §2.2 formats and from reading `0xC9C`/MODHSYN | IOPRP310 kernel + all 15 LIB31 modules on an R3000 + SPU2/DMAC/INTC/SIF hardware | SDRDRV·SKSOUND·SKHSYNTH·SKSESQ·MODSESQ·MODHSYN bytes (80,592 B text, ~20k words) loaded from `extracted/disc/LIB31/` and relocated into the 2 MiB IOP RAM model; imports bound to host functions | C++ ports of MODSESQ (2,648 words) and MODHSYN (12,176 words) + SK glue, on an HLE libsd |
| Code to write (inf, from sizes) | sequencer ≈ 1.5–2 k lines after reading ~8 k words of IRX; voice model ≈ 0.8 k | R3000 + COP0/exceptions, IOP DMAC/INTC/timers/SIF registers, SPU2 incl. AutoDMA, re-host every server now in `runtime/hle/sif/iop` (3,441 lines) | R3000 interpreter ≈ 300 lines (reference `cpu.cpp` 210 lines, 57 opcode cases), IRX REL loader + import binder ≈ 300, kernel HLE for the ~40 imports used (thbase, thsemap, timrman, intrman, sysmem, loadcore, sysclib, stdio; reference `libs.cpp` 1,291 lines covers these libraries) ≈ 600, libsd HLE (20 functions → voice model) ≈ 400, voice model ≈ 800, tests | voice model + libsd HLE as B-lite, plus ≈ 15 k words of IOP code to decompile by hand with no oracle to pair-test against (Phase 5's pace: 13 functions / 2,400 B in two sessions, `INTEGRATION_LOG` "Phase 5") |
| Effort | 5–6 weeks | 8–12 weeks, then performance work (runtime is at 0.35× real time in the movie already) | **3–4 weeks** | 6–10 weeks |
| Fidelity | approximate: voice stealing, envelopes, opcode corner cases re-derived | exact | exact sequencer/synth (the game's code); voice model is the only approximation | exact only where the decompile is right |
| Runtime files | `runtime/hle/sif/iop/srv_sdr.cpp` (sequencer), new `runtime/audio/spu2_voice.*`, `game_host.cpp` | everything under `runtime/hle/sif/`, `runtime/hle/cdvd`, memcard, pad | new `runtime/hle/sif/iop/{r3000,irx_loader,iop_kernel_hle,libsd_hle}.*`; `srv_sdr.cpp` routes `0x90F0` and the libsd codes into the loaded modules / libsd HLE; `iop_core.h` gains an IOP clock (EE cycles / 8) and a tick deadline; new `runtime/audio/spu2_voice.*`; `game_host.cpp` `--sound-log`; READMEs | `game/src/sk/` replacements + the B-lite voice/libsd layer |
| Contract rows | I-11, L-30…L-32 rewritten as model rows; new row for the SK tick | all I-/K-14/29/30 rows re-derived | I-11 ("answered by the IRX code"), L-31 (ids come from the modules), L-32 (SPU RAM is the voice model's), new I-11a (SK tick 4,167 µs on virtual time), audio row for `voices + PSM` | as B-lite |
| Determinism / tracediff | pure function of RPC stream + virtual time | IOP cycle model needed | interpreter runs only at RPC calls and at tick deadlines on the virtual timeline; `GetSystemTime` served from EE cycles / 8; output is a pure function of inputs (fingerprint stays in `capture.json`); SK ids now match MODSESQ's allocator (the M4 "sound-command rings" class shrinks) | same as A |
| Unit tests on extracted data | opcode decoder on `COMSE.SQ`; ADPCM on `COMSE.BD` | — | load the 6 IRXs (skip without disc, as other suites do), re-enact `H_Sndcom` (`tests/sif/test_adxi.cpp`, the case at line 435, already re-enacts the flow): Bind/Control replies == today's values (regression); after `SOUND_Send`, voice RAM at `0x5010`/`0x9B010` == `COMSE.BD`/`BSE.BD` bodies and == PCSX2 `SPU2.bin` at `0x15014`/`0xAB014`; 240 ticks per virtual second; first key-on produces non-zero samples | pair tests against B-lite |
| Risks | wrong-sounding SFX never provably right; RE cost is the whole of C anyway | scope, speed, re-validating M1–M4 | §3.1 | no oracle until B-lite exists |

### 3.1 Why B-lite, and its risks

The command stream at the RPC boundary is three verbs; the behaviour that makes a sound is in 20k words of
Sony code that we hold byte-exact on the disc and may load at run time exactly as we load the ELF (GOAL
ground rules: nothing copied into the repo). An interpreter for this subset is small because the modules use
plain MIPS I (no FPU, no COP2), their kernel surface is ~40 imports, their only threads are SKSOUND's tick
thread and SDRDRV's callback thread (which never has work, `16` §9.5), and their only timing source is one
hard timer plus `GetSystemTime`. Option C is best done **afterwards** as Phase-5-style replacement with the
interpreter as the pair-test oracle. Risks:

1. **IRX relocation and kernel semantics** (`.rel` sections with `R_MIPS_26/HI16/LO16/32`; `CpuSuspendIntr`
   nesting; `SleepThread/iWakeupThread` counts; the hard timer's prescale) — a wrong loader shows up as a
   crash in the first `Bind`, so it is caught in unit tests, but it costs the first week. Mitigation: the MIT
   reference loader/kernel (`kernel.cpp` 814 lines), and `open_irx.py`'s already-written `.iopmod`/import parsing.
2. **Voice-model fidelity** (ADSR rates, pitch interpolation, the volume law, reverb absent): audible but not
   provably right. Mitigation: unit vectors from the public SPU2 description; A/B against a PCSX2 WAV capture
   of the memory-card prompt (manual, obs-P), the `--dump-wav` path.
3. **Hidden EE coupling**: the M4 snapshot classes `sk_sesq_cmdblk+`, `sdr_rpc_cd+`, the heap shift (§1.4) and
   the tracediff masks move; the per-frame `SOUND_Control` and the SE triggers interleave with ADXI's SIF0
   queue. Mitigation: milestone 1 requires frame/`eeMemory` identity except the SK-id class.
4. Performance: 240 ticks/s × (MODSESQ per-track step + MODHSYN 48-voice housekeeping) ≈ low tens of
   thousands of interpreted instructions per tick (inf) — negligible beside the EE; measure in milestone 1.

## 4. Phased plan for B-lite (each milestone on the recorded dorm route)

| Phase | Work | Milestone (measurable) | Tests |
|---|---|---|---|
| 0 — instrument (2 days) | `--sound-log FILE` dumps every `SoundRequest` (full, not newest 256); counters for SK verbs in `capture.json` | the M4 replay's 8,142 requests broken down by verb; the first `SESQ_Control` play on the route located (expected at the memory-card prompt, vblank 1,200–1,822) | existing suites green; log format test |
| 1 — the SK stack runs (1.5 weeks) | R3000 interpreter, IRX loader, kernel HLE for the imports of §2.1, libsd HLE into a **silent** voice model (RAM + registers only); `srv_sdr.cpp` routes `0x90F0` into SDRDRV's user slot and `0x8000…0x8080` into libsd HLE; tick deadline every 4,167 µs of virtual time | M1/M2/M4 replays: **code 0, frame identical, `eeMemory` differs only in the SK-id class** (`classify_runs.py`); Bind replies unchanged; voice RAM at `0x5010`/`0x9B010` equals the `.BD` bodies; interpreter instructions per tick logged | `tests/sif/test_sk_modules.cpp`: loader (every import resolved, `.iopmod` entry runs, `RegisterLibraryEntries` order SDRDRV→SKSOUND→…), the `H_Sndcom` re-enactment, bank bytes vs `extracted/`, 240 ticks per virtual second, two runs identical |
| 2 — first sound (1 week) | ADPCM decode, ADSR, pitch, L/R volume in the voice model; 512-frame passes summed with the PSM output into the `AudioSink` | **first key-on produces a non-silent mix**: `--dump-wav` shows the memory-card-prompt cursor SE before any ADX stream starts; `audio.non_silent_frames > 0` before `rna_playing` | `tests/audio/test_spu2_voice.cpp`: ADPCM vectors (hand-computed, incl. filters 1–4 and loop flags), ADSR phase transitions, pitch 0x1000 = 1:1, clipping; key-on from the loaded COMSE bank yields samples equal to decoding the `Vagi` entry's bytes directly |
| 3 — menus and the event (1 week) | key-off/release, end-flag polling back to MODHSYN, master volume (`0x981/0xA81`), voice stealing as MODHSYN issues it, `--sound-log` cross-check of track handles | **menu cursor/decide SFX audible** in windowed mode at the title and on every text advance of the dorm event; no stuck voices (active-voice count returns to 0 between sounds); M4 fingerprint identical across two runs | replay with `--dump-wav`; count key-ons == `SESQ_Control` plays; stress: 16 channels of `H_Sndcom_PlayVoice` in a test harness |
| 4 — battle and polish (1 week) | BSE bank in the first battle (user play, off the recorded route); core attributes; reverb (optional, `0x83/0x84` depth) ; perf budget | battle SFX audible; voices + ADX BGM balanced as on PCSX2 (manual A/B); tick cost < 1 % of frame time | regression suite on both compilers; contract rows I-11/I-11a/L-31/L-32 and `16` §9–§10, `sif/README` §3, `audio/README` updated |

Not planned: "sequenced BGM at the title" — the title BGM is ADX (`INTEGRATION_LOG` "Snapshot diff at the
title") and the game has no SK music path (§0).

## 5. Open questions and corrections

* The SE opcode semantics (35 cases) and MODSESQ→MODHSYN message format: not needed for B-lite, needed for
  any later replacement (C); record them while writing the loader tests.
* `SOUND_Send`'s real return value: SKSOUND `0xA00` returns `sceSdVoiceTrans`'s result after waiting (`16`
  §9.2, inf = size); B-lite's libsd HLE must return what libsd does (ps2sdk `voice.c` returns the size, AFL).
* `12` §2.3 / L-31 call `H_Sndcom_PlayVoice`'s arguments `seq`; they are **(group, entry)** bytes into the
  `Sesq` two-level table (`0x21F8`); `maxtrack=16` is SKSESQ's argument while MODSESQ's per-port mask has 32
  tracks (`0x2244`) — the `kSesqTracks = 16` constant in `srv_sdr.cpp` is the wrong number for the allocator.
* `16` §9.3: SKHSYNTH's port record is 1,032 bytes (`skhsynth_export_4`, `sll 7 + add, sll 3`).
* The claim "every SK result is stored or dropped" (`16` §9.4) stands: the EE never branches on a track
  handle beyond `≥ 0`, which is why the silent HLE has not blocked any milestone.
