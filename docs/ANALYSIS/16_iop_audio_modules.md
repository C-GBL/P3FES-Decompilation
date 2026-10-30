# 16 — IOP audio modules: CRI_ADXI (DTX · SJX · SJRMT · IOPRNA · PSM), SDRDRV, Standard Kit

_Phase 3 wave 3. Databases (gitignored): `ida/work_cri_adxi.i64` (CRI_ADXI.IRX) and
`ida/work_irx_{sdrdrv,sksound,skhsynth,sksesq}.i64`, built by `tools/ours/ida/open_irx.py`
(processor `mipsl`, IRX loaded at its link addresses, so every IRX address below is a **module
offset**). Listings: `ida/logs/irx/<MODULE>.{asm,data}`. EE side: SLUS_216.21 VAs, read with the
ps2dev objdump. PCSX2: the `extracted/_pcsx2/title/` save state (`eeMemory.bin`, `iopMemory.bin`;
CRI_ADXI sits at IOP `0x6D030` there, located by matching its `.text`)._

Tags: **obs** read from the instructions (IRX offset or EE VA given); **obs-P** a value in the
PCSX2 title save state, i.e. an observation of PCSX2 running the real IRX (not of hardware);
**der** derived from obs; **inf** inferred, unverified.

## 0. Headline

* **The EE decodes ADX; the IOP is a PCM mixer.** `CRI_ADXI.IRX` ("CRI ADX Driver Ver.9.44",
  Feb 28 2005) holds no ADX decoder: it receives 16-bit PCM in IOP RAM, mixes up to 16 streams
  (PSM) and AutoDMAs the mix to SPU2 (obs: strings `0xC10C…0xD0E4`, imports `sceSdBlockTrans`;
  the EE decoder is `ADX_DecodeMono4 0x53A410` / `ADX_DecodeSte4 0x53AD00`).
* **DTX is a ping-pong of whole buffers with a counter in the last word.** Each side owns a
  `wklen`-byte buffer whose last 64 bytes are a control block; the word at `wklen − 4` is the sender's
  count. The EE sends odd counts, the IOP answers with EE count + 1 and DMAs its **entire** buffer
  back into the EE buffer (obs EE `0x559938`, IOP `0xB24`/`0xC68`). The EE accepts a block only when
  that word exceeds its own count — the "counter written back" of the open question. PCSX2 title
  state: EE count 8027 (waiting), the EE buffer's word already 8028, IOP count 8028 (obs-P).
* **Cadence:** the IOP side runs once per IOP vblank-end in CRI_ADXI's main thread
  (`0x88`: `WaitVblankEnd 0x17C` → `0x6F4` → `0x1234` → DTX server `0xE14`), 60 Hz; the EE side
  completes **one exchange per ADX vsync (30 Hz)** — the count grows by 2 per exchange and equals
  2 · `adxt_vsync_cnt` − 27 in all three PCSX2 captures (first_flip 615 / 321, atlus_logo 913 / 470,
  title 8027 / 4027) (obs-P, der).
* **Two DTX ports carry everything after init:** id 0 = SJX (descriptors of PCM chunks in IOP RAM go
  to the IOP, consumed chunks come back), id 1 = IOPRNA (play/stop/rate/volume/pan commands; the IOP
  replies with 0 entries). PCM bytes themselves go EE → IOP by `DTR` SIF DMA, not through DTX.
* **Without the counter write-back** the first SJX block is never answered: no chunk ever returns
  to the EE, so DTR stops after the first 16 KiB per channel and no play command after the first
  block reaches the IOP; `ADXRNA_GetNumData` never falls to 0 and ADXT cannot reach PLAYEND (der).
* `"sdinit=0 spucore=1"` reaches CRI_ADXI as **one** argument (loadfile passes NUL-separated
  strings), so only `sdinit=0` parses: the SPU core stays **0** (obs `0x18C` parser, obs-P
  `0xD7D4 = 0`, `0xD410 = 0`, EE `0x7A9438 = 0`).
* HLE (runtime/hle/sif/iop/srv_adxi.cpp): the full DTX/SJX/SJRMT/IOPRNA protocol, a PSM model that
  consumes PCM from IOP RAM at the RNA's rate on virtual time and mixes it (§10); SDRDRV + SK answer
  with the IRXs' slot values (srv_sdr.cpp).

## 1. Modules

### 1.1 What was read

| Module | Size | `.iopmod` name / version | Role here | Read |
|---|---|---|---|---|
| `LIB31/CRI_ADXI.IRX` | 75,173 | `CRI_ADX_Driver` 0x92C; components ADXI 9.44, DTX 1.10, IOPRNA 1.32, PSM 1.10, SJRMT 1.03, SJX 1.09, RCV/PS2IOP 1.12 (`.rodata` strings) | DTX RPC `0x90000200`, PCM mixer | DTX, SJX, SJRMT, IOPRNA, PSM API, PSMOUT start/stop; **not**: RCV converter internals (`0x9DBC`, `0xA044`), mixer body (`0x30A4`, 7.5 KB) |
| `LIB31/SDRDRV.IRX` | 9,161 | `sdr_driver` 0x401 | RPC `0x80000701`, libsd remote | dispatcher `0x588`, user-command export, callback thread |
| `LIB31/SKSOUND.IRX` | 9,717 | `StandardKit/Sound/Foundation` 0x203 | SK `0x90F0` dispatch, SOUND | `0xD30`, `0xE20`, Control `0xA64`, Send `0xA00` |
| `LIB31/SKHSYNTH.IRX` | 9,601 | `…/HardwareSynthesizer` 0x103 | HSYNTH Bind/Unbind | `0x1310`, Bind `0x820`, args `0x0` |
| `LIB31/SKSESQ.IRX` | 10,337 | `…/SE_Seq_Player` 0x101 | SESQ Bind/Control | Bind `0x770`, Control `0xCFC` |

Imports were named from ps2sdk's `DECLARE_IMPORT` ordinals (numbering only). CRI_ADXI imports libsd
(`sceSdInit`, `SetParam`, `GetParam`, `SetCoreAttr`, `VoiceTrans`, `BlockTrans`, `…Status`,
`SetTransIntrHandler`, `GetTransIntrHandlerArgument`), sifcmd (`InitRpc`, `CallRpc`,
`RegisterRpc`, `SetRpcQueue`, `RpcLoop`, `RemoveRpc*`), sifman (`sceSifInit`, **`sceSifSetDma`**,
`CheckInit`), thbase, thsemap, intrman, vblank (`WaitVblankEnd`), loadcore `FlushDcache`; no exports
(obs).

### 1.2 Load arguments (`kwlnInitPS2Systems 0x197030`, `12` §1)

`sceSifLoadModule("…CRI_ADXI.IRX;1", 0x14, "sdinit=0 spucore=1")`: 20 bytes = one string with a
space. The module's parser (`0x18C`) walks `argv[1..]` and compares each **whole argument** with
`thpri=`, `spucore=`, `sdinit=`, `pthpri=`, `dthpri=`, `debug=` (`strncmp` at the start, obs
`0x218–0x440`), so only `sdinit=0` matches → `0xD7D8 = 0` (CRI does not call `sceSdInit`); `spucore`
keeps its default `0xD7D4 = 0` (obs `0x1F4`). PCSX2: `0xD7D4 = 0`, `0xD7D8 = 0`, thread priorities
`0xD7DC = 39` (main), `0xD7D0 = 39` (PSM), `0xD7E4 = 48` (DTX) (obs-P). SKSESQ's args are passed
NUL-separated (`"maxtrack=16\0maxentry=16\0"`), so the game's other module parses both (der).

## 2. Data path

```
EE (recompiled)                                         IOP (CRI_ADXI)
ADXT ─ ADXSJD/ADXB decode (0x53A410) ─► EE SJ (PCM, per channel)
DTR_ExecHndl 0x558DD0: GetChunk(EE SJ, data) + GetChunk(local SJUNI, free)
   ─ sceSifSetDma(EE PCM → IOP RAM chunk, 64-byte units) ─────────────────► IOP RAM (16 KiB / channel)
   PutChunk(local SJUNI, data) ; PutChunk(EE SJ, free)
sjx_sndcbf 0x564400: local SJUNI data chunks ─► DTX 0 block ─► 0x8F60: PutChunk(IOP SJUNI, data)
                                                               PSM slot ─ RCV ─ PSMMIX ─ PSMOUT
                                                               ─ sceSdBlockTrans(core 0) ─► SPU2
sjx_rcvcbf 0x564360: PutChunk(local SJUNI, free) ◄─ DTX 0 reply ◄─ 0x900C: GetChunk(IOP SJUNI, free)
ps2rna_sndcbf 0x55FC00: parameter commands ─► DTX 1 block ─► 0xEA0: PSM start/stop/rate/vol/pan
ps2rna_rcvcbf 0x55FBA0 (ignores entries)  ◄─ DTX 1 reply (0 entries, 0x10F8)
```

* The 16 KiB PCM buffers live in IOP RAM: `ps2rna_init_psj 0x55F748` allocates
  `16 × (256 + 16384)` = `0x41000` bytes (+64) with `AllocIopHeap` and, per channel ("psj"),
  creates a **remote** SJUNI on the IOP (urpc 34, 256-byte chain pool), a **local** EE SJUNI
  (`SJUNI_Create 0x562F90`) whose free line starts as one chunk `{iop buffer, 16384}`, and an SJX
  pairing the two (urpc 0) (obs). The EE therefore accounts for IOP buffer space itself.
* PCSX2 title, channel 0 (obs-P): IOP SJUNI `0x81680` data line `{0xBDE40, 12288}`, free line
  `{0xC1A40, 1024}`; DTR 0 in flight `{0xC0E40, 1536}`; the EE SJX buffer holds the IOP's reply
  returning `{0xC1440, 1536}`; local SJUNI empty — 12288 + 1024 + 1536 + 1536 = 16384 (der).

## 3. DTX

### 3.1 Objects (obs)

| Field | EE `0x7A1160 + 68·id` (DTX_Create `0x559718`) | IOP `0xE290 + 68·id` (`0x9D0`) |
|---|---|---|
| +0/+1/+2 | used / **stat** (1 = waiting for the peer) / enable | same; created with stat **1** |
| +4 | remote handle (fn 2 reply) | — |
| +8 | **count** | **count** |
| +12, +16 | own buffer, data length = wklen − 64 | IOP buffer, wklen − 64 |
| +20 | control block = (buf + wklen − 64) \| `0x20000000` (uncached) | IOP buf + wklen − 64 |
| +24, +28 | IOP buffer, wklen | EE buffer, wklen |
| +32/+36, +40/+44 | receive / send callback + arg | receive / send callback + arg |
| +48…+60 | `SifDmaTransfer_t {buf & 0x0FFFFFFF, iopbuf, wklen, 0}` | `{iopbuf, eebuf, wklen, 0}` |
| +64 | DMA id | DMA id |

Both callbacks are optional (`if (cb)`, IOP `0xB80`/`0xC10`). The control block's word +60 (= buffer
offset `wklen − 4`) is the counter; the other 60 bytes are never written by either side (obs).

### 3.2 RPC `0x90000200` (server `0x7D4`: `sceSifRegisterRpc(sid 0xD2D4 = 0x90000200, 0x720, buf 0xE190)`)

The RPC function `0x720` returns the receive buffer itself, so **every reply is the request buffer
modified in place** (obs `0x7C0`). fn < 2 and fn ≥ 1088: no action.

| fn | EE client | Args → reply | IOP |
|---|---|---|---|
| 2 | `dtx_create_rmt 0x559588` (send 16 → recv 4) | `{id, eewk, iopwk, wklen}` → object or 0 | `0x9D0`: refuses eewk % 64, iopwk % 32, wklen % 64, id ≥ 16, used; else stat 1, count 0, **memset(iopwk, 0, wklen)** |
| 3 | `dtx_destroy_rmt 0x5595F8` (4 → 0) | `{object}` | `0xAE8`: memset(obj, 0, 68) — clears the callbacks |
| 1024+u | `DTX_CallUrpc 0x559C10` (4·n → 4·m) | §4 | `0x78C`: handler `0xE090[u]` (arg `0xDF90[u]`), skipped when 0 |

Callbacks for ports 0 and 1 are bound at module start (`0x1614` calls urpc-10's handler `0x1408`
with zeros; `0x929C` calls urpc-3's `0x9228`), before any create, and `0x9D0` leaves them alone
(obs). EE users (obs): `SJX_Init 0x564528` → `DTX_Create(0, eebuf, iopbuf, 2176)` + urpc 3;
`PS2RNA_Init 0x55FF70` → `DTX_Create(1, eebuf, iopbuf, 2176)` + urpc 10. Both IOP buffers come
from `AllocIopHeap(2256)` aligned up to 64. PCSX2: EE buffers `0x7B1D80` / `0x7ABEC0`, IOP buffers
`0xBD440` / `0xFEE40`, wklen 2176 (obs-P).

### 3.3 The exchange (obs; EE `DTX_ExecHndl 0x559938`, IOP `0xB24`)

| Step | EE | IOP |
|---|---|---|
| receive | if stat == 1 and `count < ctrl[+60]` (signed): `InvalidDCache 0x503B98`, rcv(buf, wklen−64), count = ctrl, stat = 0 (`0x55996C–0x5599BC`) | if stat == 1 and `count < ctrl[+60]`: rcv(iopwk, wklen−64), stat = 0, count = ctrl (`0xB48–0xBAC`) |
| send | if `(word0 & 0x00FFFF00) == 0x00010000` (stat 0, enable 1) **and** `0x7A114C == 1` (set by the ADX init `0x53ECEC`): snd(buf, wklen−64); count += 1; `ctrl[+60] = count` (uncached store `0x559A1C`); `SyncDCache 0x503A58`; `sceSifSetDma({buf, iopbuf, wklen, 0})` retried until non-zero (`0x559A7C`); stat = 1 | if stat == 0: snd; count += 1; `ctrl[+60] = count` (`0xC3C`); `sceSifSetDma({iopwk, eewk, wklen, 0})` under CpuSuspendIntr, retried (`0xC68`); stat = 1 |

So with both counts starting at 0 the EE sends 1, the IOP accepts it (0 < 1), takes count 1, sends
2; the EE accepts 2, sends 3; … **The value written back is EE count + 1, at EE buffer offset
`wklen − 4`, as part of a whole-buffer DMA** whose other bytes are the IOP's buffer: the EE's own
last block (it was DMA'd there) with the IOP's send callback's edits (§5, §6) (der). The EE reads
the counter through the uncached alias, so the DMA'd value is seen without a cache flush (obs
`0x559974`). `DTX_Destroy 0x5598B0` spins `DTX_ExecServer` while its stat is 1, i.e. until the IOP
has answered (obs `0x5598D8`).

### 3.4 Cadence

* IOP: thread `0x88` (priority `0xD7DC` = 39) loops `0x6F4` → `0x1234` (RNA discard `0x1140` for
  each of 16 RNAs, then `0x912C` → DTX server `0xE14`: every used object in index order) →
  `WaitVblankEnd` (obs). One pass per IOP vblank-end.
* EE: `adxt_ExecServer 0x549EC8` calls `ADXRNA_ExecServer 0x541B28` (→ `PS2RNA_ExecServer
  0x561138` → RNA exec ×16, `DTR_ExecServer 0x559140`, `SJX_ExecServer` → `DTX_ExecServer
  0x559D18`) once, and a second time while a counter `0x793B20` is < 51 (obs `0x549F70`,
  `0x549F8C`).
* PCSX2 title (obs-P): IOP `0xD2EC = 16109` = 2 ports × 8054.5 passes (60 Hz, ~134 s);
  `adxt_vsync_cnt 0x787568 = 4027` (30 Hz, ~134 s); EE count 8027 = 4013 exchanges + 1 ⇒ **one
  exchange per ADX vsync**; EE `DTX_ExecHndl` calls `0x7A1158 = 32112` = 4.0 per port per ADX vsync,
  so the EE polls a port four times per exchange and every reply arrives before the EE's next ADX
  vsync (der).
* This runtime (MSVC Release, the ISO, headless, `p3fes --snapshot-at`, run 2026-10-19): EE count =
  2 · `adxt_vsync_cnt` + 1 at sky:11 (379 / 189, vblank 380), sky:154 (665 / 332, vblank 666) and
  vblank 1200 (1199 / 599); `0x7A1158` = 4.0 per port per ADX vsync (4800 at vblank 1200) — the
  same steady-state cadence as PCSX2; PCSX2 starts its exchanges 13.5 ADX vsyncs later (−27 vs +1:
  boot-timing difference, not analysed). RNA 0 is created and not playing at those points, as in
  PCSX2's first_flip and atlus_logo states (obs). To vblank 4800 (80 virtual s, the game waiting at
  the "no memory card" prompt): 4799 / 2399, IOP unknown events 0. With "Yes" pressed the Sofdec
  logo shows and the opening movie starts at vblank ~1822, where the run stops in libmpeg
  (`unreachable` at `0x4FDB00`, recompiler/IDA item issue, not audio) — **no ADX playback has been
  observed in this runtime yet**; SJX/PSM consumption and mixing are verified by tests only.

### 3.5 PCSX2 title state (obs-P)

| | EE port 0 (SJX) | EE port 1 (RNA) | IOP port 0 | IOP port 1 |
|---|---|---|---|---|
| object | `0x7A1160` | `0x7A11A4` | `0x7B2C0` (= base + `0xE290`) | `0x7B304` |
| stat / count | 1 / 8027 | 1 / 8027 | 1 / 8028 | 1 / 8028 |
| counter word | EE `0x7B25FC` = **8028** | EE `0x7AC73C` = **8028** | IOP `0xBDCBC` = 8028 | IOP `0xFF6BC` = 8028 |
| buffer word0 | 2 (two returned chunks) | 0 (zero entries) | 2 | 0 |

The EE buffers equal the IOP buffers entry for entry (e.g. port 0: `{0, 0x7B1AD0, 0xC1440, 0x600}`,
`{0, 0x7B1AE4, 0xC5540, 0x600}`) — the whole-buffer write-back (obs-P).

### 3.6 Correction to the wave-2 note

`runtime/hle/sif/README.md` §7 read the EE side correctly ("waits until that word has become
larger"); the IOP writes it at its next vblank-end pass, by DMA of the whole buffer, with EE count
+ 1. "Acknowledging at once" would have been wrong in two ways: the reply must carry the IOP's
buffer (returned chunks), and it comes one IOP pass later.

## 4. urpc table (`DTX_CallUrpc 0x559C10`: send `4·nsend` words from `0x9979C0`, receive `4·nrecv` into `0x997AC0`; result = first word)

| u | IOP handler | Args → reply | EE caller |
|---|---|---|---|
| 0 | `0x914C` SJX_Create | `{ee_sj, iop_sj, mode, ee_sjx}` → IOP SJX (32 × 20 B at `0x15190`); line = mode == 1 ? 0 : 1 | `SJX_Create 0x564738` (mode 1) |
| 1 | `0x920C` SJX_Destroy | `{sjx}` | `SJX_Destroy 0x564830` |
| 2 | `0x9218` SJX id | `{sjx, id}` | — |
| 3 | `0x9228` SJX_Init | binds DTX port 0 | `SJX_Init 0x564684` |
| 8 | `0x12B8` IOPRNA create | `{nch, core, sj0, sj1}` → RNA (16 × 28 B at `0xE770`) or 0; PSM_Create(core, nch, sjs) `0x2350`, nch, sfreq `0xD7F4` | `PS2RNA_Create 0x5608D8` (`{nch, 0, psj0->rmt, psj1->rmt}`) |
| 9 | `0x13D0` IOPRNA destroy | `{rna}` | `PS2RNA_Destroy 0x560AF8` (site `0x560B84`; also `PS2RNA_Create`'s error path `0x560998`) |
| 10 | `0x1408` PSM init | `{voices, work, size}`; binds DTX port 1 | `PS2RNA_Init 0x5601F8` (`{16, work, 0x4040}` in PCSX2) |
| 11 | `0x1494` restore IOP sound | `{core}`: core (≤ 2), finish, init | `PS2RNA_RestoreIopSnd 0x560280` |
| 12 | `0x14C8` init IOP sound | `{sfreq}` → **core** (`0xD410`); init (counted, `0xD40C`) starts PSMOUT on that core | `PS2RNA_InitIopSnd 0x560304` (sfreq 48000 unless a config string overrides, `0x5602CC`); the EE stores the reply at `0x7A9438` and enables PCM trans for that core |
| 13 | `0x150C` finish | counted; the last one stops both outputs | `PS2RNA_FinishIopSnd 0x5603B0` |
| 14 / 15 | `0x152C` / `0x154C` Dolby PL II on/off | core 0: prints "You use CORE0 now…" and does nothing | `0x560428` / `0x560494` |
| 16 / 17 | `0x156C` / `0x1590` PCM trans start/stop | `{core}` → PSMOUT start/stop | `PS2RNA_StartPcmTrans 0x5605C4` / `Stop 0x560650` (no game callers of the ADXPS2 wrappers) |
| 32 / 33 / 34 | `0x8AE0` / `0x8B20` / `0x8B5C` SJRBF / SJMEM / **SJUNI** CreateRmt | 34: `{mode, pool, size}` → SJUNI (48-byte objects, `0x81680 + 0x30·i` in PCSX2 = module `0x14650`) | 34 only: `ps2rna_init_psj 0x55F8CC` (`{1, iop pool, 256}`) |
| 35…42 | `0x8B9C…0x8DB8` → SJ vtable +0x0C destroy, +0x10 uuid, +0x14 reset, +0x18 GetChunk `{sj, line, max}` → `{ptr, len}`, +0x1C Unget, +0x20 Put, +0x24 GetNumData `{sj, line}` → n, +0x28 IsGetChunk | SJRMT client `0x564038…0x564268` | 35 from `0x55FA78`; **41 has no live caller** (`ADXPS2_GetNum*Sjiop 0x541878/0x5418B0` are unreferenced) |

## 5. SJX and SJUNI

* **Entry** (16 bytes after a count word at +0; ≤ 128 per block): `{u8 flag (0 = valid), u8 line,
  u16 id, u32 sjx, u32 ptr, u32 len}` (obs EE `0x564400`, `0x564360`; IOP `0x8F60`, `0x900C`).
* EE → IOP (`sjx_sndcbf`): for each of 32 EE SJX objects, every chunk of the local SJUNI's line
  `obj+12` (= 1, data) with `sjx` = the IOP SJX handle. IOP `0x8F60`: `PutChunk(IOP SJUNI, **1**,
  chunk)` (the line is hard-coded, `0x8FAC`).
* IOP → EE (`0x900C`): for each IOP SJX, every chunk of the IOP SJUNI's line `obj+12` (= 0, free)
  with `sjx` = the EE SJX object; EE `sjx_rcvcbf`: `PutChunk(local SJUNI, entry.line, chunk)`.
* **SJUNI semantics** (EE copy of the same library, obs): object 48 bytes (`+4` used, `+5` mode,
  `+12` pool, `+16` pool size / 16 = chain nodes, `+20` free nodes, `+24…+36` line heads);
  `PutChunk 0x5636D0` ignores empty chunks, **merges** (mode 1) a chunk that continues the line's
  tail, else takes a node (none left → error callback −3); `GetChunk 0x563530` returns the head chunk
  when `len ≤ max`, else (mode 1) splits it (`SJ_SplitChunk 0x563C28`); `GetNumData 0x563418` sums a
  line. The IOP objects have the same layout (obs-P: `0x81680` = `{vtable 0x7A560, 0x101, …, pool
  0xBDD40, 16 nodes, …}`).

## 6. IOPRNA / PSM

### 6.1 RNA commands (EE `ps2rna_sndcbf 0x55FC00` → IOP `0xEA0`; entry `{s16 cmd, _, rna, v8, v12}`)

The EE emits a command only when a field changed (new/old pairs in its 100-byte RNA object
`0x7AB850 + 100·i`). IOP switch (14 cases, obs):

| cmd | EE source | IOP effect |
|---|---|---|
| 0 / 1 | — | PSM start (`0x265C`: stop, restart each slot's RCV `0x6234`, playing = 1) / stop (`0x26DC`) |
| 2 | play switch (+80/+81, `SetPlaySw`) | v8 == 1 → start, else stop |
| 3 | channels (+82/+83) | rna+8 = v8; PSM nch only while stopped and ≤ max (`0x2DC4`) |
| 4 | sfreq (+48/+52) | every slot's input rate (`0x2768` → `0x62D4`), psm+0x34 |
| 5 | volume (+56/+60 via table `0x7A8450`) | rna+0x18 = v12; every channel volume = clamp(v12, 0, 255) (`0x2998`) |
| 8 | discard (+90/+91, `SetDiscardSw`) | rna+1 = v8; the server pass moves all data chunks to the free line (`0x1140`) |
| 9 | per-channel pan (+64/+72) | pan[v8] = clamp(v12, −15, 15) (`0x2A24`) |
| 10 | +84/+85 | rna+2; output core 0 if v8 == 1 else 1 (`0x2C38`) |
| 11 | global `0x7A9424/28` (`PauseAll`) | v8 == 1 stops both PSMOUTs, else starts them (`0x21C8`) |
| 12 | core (+86/+87 = `0x7A9438`) | rna+3; psm core = v8 |
| 13 | +92/+96 | output pan: −128 re-applies, else clamp(−15, 15) (`0x2ACC`) |
| 6, 7 | — | none |

PCSX2 title, the playing RNA (obs-P): EE `nch 2, sfreq 24000, vol −30 (→ 181), pans −15/+15,
play 1/1, core 0`; IOP RNA `0x7B7A0` `{used 1, maxnch 2, nch 2, psm 0x7DC40, sj 0x81680/0x816B0}`,
PSM `{used, playing 1, maxnch 2, nch 2, sfreq 24000, vol 181/181, pan −15/15, out pan 0, core 0}`.

### 6.2 Volume law (`0x27E4`, obs)

Side gain = round(vol · P[15 ± pan] · O[15 ± mpan] / 65025) (the instructions: `q = (10x ·
0x81018203) >> 47`, result `q / 10` rounded half up; left uses `+pan/+mpan`, right `−pan/−mpan`)
with P = `.data 0xD310` (255 … 180 at the centre … 0, a −3 dB centre) and O = `0xD38C` (255 for
−15…0, then 238 → 0). Gains feed PSMMIX (`0x5274`); how PSMMIX scales samples by them is not traced
(inf: gain/255).

### 6.3 Output and consumption

* PSMOUT (`0x5864`): a 4 KiB buffer per core in 512-byte L/R blocks, `sceSdBlockTrans(core, 0x10,
  buf, 4096)` (`0x5B90`), transfer interrupt → `iSignalSema` → the PSM thread (`0x5A30`) (obs) ⇒ one
  mix per half buffer = **512 frames at 48 kHz (10.67 ms)** (der).
* Consumption per pass = 512 · sfreq / 48000 samples per channel (der). PCSX2: the returned and free
  chunks of a 24 kHz stream are 1536 and 1024 bytes — multiples of 512 bytes = 256 samples (obs-P).
* RCV (`0x9380+`: rate conversion to 48 kHz) and the mixer body are not traced: the HLE interpolates
  linearly (inf).

## 7. What the EE polls

| EE function | Reads | Needs from the IOP |
|---|---|---|
| `ADXRNA_GetNumData 0x541AC0` → `PS2RNA_GetNumData 0x560EB0` | `(16384 − local SJUNI free bytes) / 2` | chunks returned via SJX (local accounting, no RPC) |
| `ADXRNA_GetNumRoom 0x541AD8` → `0x560F18` | local free bytes / 2 | same |
| `ADXRNA_GetTime 0x541AA8` → `PS2RNA_GetTime 0x560E78` | constant `{0, 48000}` | nothing |
| `adxt_stat_prep 0x54C100` | `GetNumData ≥ min(2 · ADXT[+72], 16384)` → `SetPlaySw(1)`, ADXT stat 3 | DTR progress only (local) |
| `adxt_stat_decend 0x54C370` (→ PLAYEND) | `GetNumData` falling as the IOP consumes | the PSM model + SJX returns |
| `PS2RNA_ExecHndl 0x560F78` (stop/flush) | `GetNumData(free) == 16384` per channel | every chunk returned |
| `DTR_GetStat 0x559138`, `DTX_ExecHndl` | own object bytes | the counter write-back (§3.3) |

There is no `DTX_GetStat`; DTX status is the object's stat byte. `ADXT_GetStat` is EE-local state
driven by the above (der).

## 8. The game's ADX decoder (reference for the host decoder)

`ADX_GetCoefficient 0x539858` (float): a = √2 − cos(2π·cutoff/rate), b = √2 − 1,
c = (a − √((a+b)(a−b)))/b; k0 = cvt.w.s(2c·4096), k1 = cvt.w.s(−c²·4096) (truncation). ADXPD objects
(60 B) keep k0/k1 at +48/+50 and a key state at +52/+54/+56 (zero unless set). `ADX_DecodeMono4
0x53A410`: big-endian scale word; bit 15 set → stop (end marker `0x8001`); effective scale =
((scale ^ key) & 0x1FFF) + 1; per byte, high nibble first (low nibble via the sign table
`0x7C1A40` = 0…7, −8…−1); sample = clamp16(((k0·h1 + k1·h2) >> 12) + nibble·scale) (obs). For the
500 Hz cutoff: 48 kHz (7400, −3342), 24 kHz (6687, −2729), 44.1 kHz (7334, −3283) — fractional parts
≥ 0.07 from an integer, so float vs double cannot change them (der). `runtime/audio/adx_decoder.cpp`
implements exactly this.

## 9. SDRDRV and the Standard Kit

### 9.1 SDRDRV dispatch (`0x588`, obs)

`dword_14E0 = 0` on entry; switch on `fno & 0xFFF0`; the reply is 16 bytes from `&dword_14E0`
(`0xDAC`; `0x8140` / `0x81C0`/`0x81D0` use other buffers). `0x8000` sceSdInit → result,
`0x8010` SetParam (void → **0**), `0x8020` GetParam, `0x8030/40` Set/GetSwitch, `0x8050/60`
Set/GetAddr, `0x8070/80` Set/GetCoreAttr, `0x8090/A0` Note2Pitch/Pitch2Note, `0x80B0/C0` ProcBatch,
`0x80D0…0x8100` transfers, `0x8130/40/50` effects, `0x8160/70/80` interrupt handlers, `0x8190`
effect clean, `0x8F10` thread priorities, **`0xE620` callback thread create (result 0)**, `0xE630`
delete, `0x9000…0x90F0` user commands: slot `(fno & 0xF0) >> 4` of `dword_14F0`, unregistered → 0;
others print "unknown command" and answer 0.

### 9.2 SK dispatch and SOUND

SKSOUND registers `0x90F0` (`0xDD4`, `sceSdrSetUserCommandFunction`); its handler `0xD30`
dispatches on block word0 >> 24 & 0x7F to the module table `0x1750` (SOUND 0 = `0xE20`, HSYNTH 1,
SESQ 4); an empty slot → **−310** (`0xFFFFFECA`). SOUND (`0xE20`): function 0/1 → 0; 2 Control
(`0xA64`): `0x80` master volume (SetParam `0x981/0xA81`, v·129), `0x81` core attr 6/7, `0x82` core
attr 2/3, `0x83` effect attr both cores (result of sceSdSetEffectAttr), `0x84` effect depth, `0x8F`
core attr `0xA`, others −310; 3 → `arg1 ? −310 : 0x17F8`; 10 Send (`0xA00`) →
`sceSdVoiceTrans(ch, 0, iop, spu, size)` + wait → its result (inf: the size, as ps2sdk's libsd
returns). The game's init (`H_Sndcom_Init 0x10CAC0`: `(0,143,0) (3,131,261,60) (3,132,60,60)
(3,130,1) (3,128,127,127)`) ignores every result (obs).

### 9.3 HSYNTH (`0x1310`)

0 Bind (`0x820`): types 1–3 take the first bank entry with `flags & 3 == 0` among `maxentry`
(default **8**, set at `0x14`; an invalid argument falls back to 8 at `0xD0`) or the given id → the **0-based index**; type 5 takes the first port whose
SKSOUND state `& 3 == 0` (or the given one), requires the entry's flags `== 3` (else −201) → the
port index, ORing port state 2; no slot → −101. 1 Unbind, 2, 3 (`0x119C`) not traced further.
SKHSYNTH is loaded twice by the game (`12` §1); the second instance's `RegisterLibraryEntries` fails
(`KE_LIBRARY_FOUND`), its `_start` returns 1 (`MODULE_NO_RESIDENT_END`) after 36 instructions and loadcore
frees the image (obs: the modules run in place, `runtime/hle/sif/README.md` §9). The port record is
1,032 bytes (`skhsynth_export_4`: `sll 7 + add, sll 3`; `19` §5), allocated at start together with four
other work areas (`0x1D8–0x2CC`: entries × 20, `maxport << 4`, `maxport × 1032`, `maxport × 1368`); a
failed allocation frees them and the module returns 1.

### 9.4 SESQ

Bind (`0x770`): type 0/10 → first free sequence entry (12-byte entries, `maxentry=16`) → index;
type 5 `(port, entry)` → port already holding a sequence (state bit 0) → −202, entry not bound →
−201, else **returns the port** (`0xA88`) and ORs state 1. Control (`0xCFC`): commands 0/7 with type
10 → a MODSESQ track (`modsesq_7`, ≥ 0; inf: 0-based, 16 tracks), 2 with type 10 → stop → 0; type
≠ 10 → 0. Status → result ignored by the game (`H_Sndcom_StopVoice 0x10DA70`). The EE checks only
`HSYNTH_Bind ≥ 0` and `SESQ_Bind ≥ 0` (`0x10D2B4`, `0x10D310`, `0x10D36C`) and `AllocSysMemory ≠ 0`
(obs); every other SK result is stored or dropped.

Corrections from running the IRX in place (ADR-0014 increment 2, obs): Control checks the port's SKSOUND
state `& 3 == 3` (−201), its type `== 10` (−102) and, for stop, the port's "playing" bit `0x80000` (−102);
the track handle is MODSESQ's, from its round-robin allocator over a **32-track** mask (`0x2248–0x22A4`:
0, 1, 2 … across the dorm route's 27 plays, not the first free index; `maxtrack=16` is SKSESQ's argument);
play flags the start with `0x101` (cmd 0) or `1` (cmd 7) to `modsesq_9`; on the dorm route every
`SESQ_Status(port, 1, 10, track)` answers **−299** and every following `SESQ_Control(port, 2, 10, track)`
**−304** (the one-shot SE has finished by then; the constant model's 0 was wrong, the game drops both).

### 9.5 The callback thread binds the EE

`0xE620` creates SDRDRV's callback thread (`0xCB8`), which **binds the EE's RPC server
`0x80000704`** in a retry loop (`0xFF0`/`0x1014`) and then sleeps until a transfer / SPU2 interrupt
handler sets `0x1530` (installed only by codes `0x8170/0x8180/0x8160`, which the game never sends)
(obs). So the IOP binds but never calls `_sdrCB 0x512FF0` (I-20/L-34 stay correct for calls). The HLE
does not send that bind (its only EE effect is sifrpc answering it).

## 10. HLE mapping (`runtime/hle/sif/iop/srv_adxi.cpp`, `srv_sdr.cpp`)

| Behaviour | Status |
|---|---|
| DTX fn 2/3 (checks, memset, handles), in-place replies, module-start callback bindings | **implemented** (obs) |
| Exchange state machine, counter EE + 1 at `wklen − 4`, whole-buffer write-back on the SIF0 queue, one pass per vblank-end (`IopConfig::adxi_tick_delay_cycles` after VBLANK_START, default 22 H-lines, inf) | **implemented** |
| urpc 0–3, 8–13, 16/17, 34/35/37–42 | **implemented**; 14/15 (Dolby), 32/33/36 logged as unknown (no game use) |
| SJX entries both ways, SJUNI lines with merge/split/node limit | **implemented** |
| RNA commands 0–13; PSM objects (vol 255, pan 0, out pan 0, core `0xD410`) | **implemented** |
| PSMOUT start/stop (init/finish counting, urpc 16/17, pause-all), 512-frame passes on the virtual-time timeline, consumption at sfreq/48000 from IOP RAM, free-line returns | **implemented** (pass size der; RCV interpolation inf) |
| Mix to the host AudioSink with the §6.2 gains (gain/255 inf); per-stream PCM tap | **implemented** |
| SPU2 core volumes, effects, Dolby, digital out, RCV filter shape | not modelled |
| SDRDRV libsd codes, `0xE620`/`0xE630`/`0x8F10`, `0x90F0` → SK | **the IRX code answers** (ADR-0014 increment 2, `IopConfig::sk_mode = Modules`): SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN loaded from the disc at the loadfile requests and interpreted (`runtime/hle/sif/README.md` §9); libsd is the HLE over the SPU2 voice model (`runtime/audio/README.md`); `SkMode::Constants` keeps the register-shadow model of increment 1 |
| SK SOUND Control/Send results; HSYNTH/SESQ slot allocation; Send into SPU RAM; MODSESQ sequencing and MODHSYN voice keying | **implemented**: the modules' own replies and 240 Hz tick; voices **played** by the host SPU2 voice model, mixed with the ADX stream (milestone 2: the memory-card prompt's SE is the first audible SFX; milestone 3 items in `runtime/audio/README.md`) |
| SDRDRV's bind of EE `0x80000704` | not sent (the callback thread's retry loop ends on a marked client, `iop_kernel_hle.cpp` `sceSifBindRpc`) |

IOP addresses of the HLE's objects (handles) are chosen in the IOP server arena and differ from
PCSX2's (CRI_ADXI's module base `0x6D030`): the IOP-identity difference of `INTEGRATION_LOG`
"Remaining divergences" 3. Since SK increment 2 (`IopLayout::Pcsx2`, the default) the SK module images
sit at PCSX2's addresses (SDRDRV `0x83230`, MODHSYN `0x84F30`, MODSESQ `0x95A30`, SKSOUND `0x98630`,
SKHSYNTH `0x9A030`, SKSESQ `0xB0730`; obs-P, the ModuleInfo chain of the dorm `iopMemory.bin`) and the
game's heap allocations start at `0xBD400`, PCSX2's first game allocation, so `sSndcomWork`'s and the
CRI file table's IOP addresses equal PCSX2's.

## 11. Open questions

* In-game playback: the first ADX stream (inf: the opening movie's audio, Sofdec plays through ADXT)
  is not reached yet (§3.4); the PSM consumption cadence and the returned-chunk sizes should be
  compared with PCSX2's title state (§2, §6.3) once the title BGM plays here.
* RCV's conversion filter (`0x9DBC`, `0xA044`) and PSMMIX's use of the side gains (`0x30A4`); PSM
  pre-fetch into each slot's 1 KiB SJRBF (`0x2408`) — up to 512 samples earlier returns than
  modelled.
* The exact IOP vblank-end offset (22 H-lines assumed) — EE-visible only through when the reply
  lands inside a field.
* `ADXT` loop restart behaviour (decoder history at the loop point) — matters for the host decoder's
  `--dump-wav` of disc files only.
* SPU2 voice playback for the SK banks: resolved by ADR-0014 increments 1–2 (the modules run in place
  over the host voice model); open are the milestone-3 items (`runtime/audio/README.md` "What is not
  modelled") and an A/B of the mix against a PCSX2 capture.
* What `PS2RNA_InitIopSnd`'s config probe (`0x555898`, string `0x7C6568`) can return (sfreq
  override); the game uses 48000 in PCSX2 (obs-P `0xD7F4`).

## 12. Corrections to other documents

* `runtime/hle/sif/README.md` §7 / §5 "DTX never acknowledges stream blocks": superseded by §3.
* `12` §2.1 / RUNTIME_CONTRACT L-33: urpc 12 returns the SPU core (0 here, §1.2); SJRMT GetNumData
  (41) has no live caller; the EE's buffer accounting is local (§7).
* RUNTIME_CONTRACT L-34 / `12` §2.2: SDRDRV's callback thread binds `0x80000704` (§9.5).
* The SK Bind values are 0-based slot indices and `SESQ_Bind(5, port, entry)` returns the port; the
  wave-2 stub's "ids from 1" is replaced (§9.3–9.4).
