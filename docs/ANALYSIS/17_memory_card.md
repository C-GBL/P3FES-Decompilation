# 17 — Memory card: libmc2 → libdbc → DBCMAN/MC2_S1 → card, and the HLE behind it

Scope: what the game's memory-card stack sends over the SIF, what the two IOP modules on the disc do with it, the
card model that answers, and the validation against the PCSX2 `atlus_logo` state. Tags: **obs** read from the
game's instructions (EE: ps2dev objdump of `SLUS_216.21`, VAs; IOP: ps2dev objdump of `LIB31/DBCMAN.IRX` and
`LIB31/MC2_S1.IRX` from the disc, `.text`/`.data` offsets with the module at 0), from PCSX2 save-state memory
(`extracted/_pcsx2/atlus_logo/{eeMemory,iopMemory}.bin`) or from the user's card image; **der** derived from obs;
**inf** inferred, unverified. IDA was not used (another agent held it). Card format sources: Ross Ridge,
"PlayStation 2 Memory Card File System" (layout, FAT, ECC description); ps2sdk @ `329e2bb` (AFL-2.0)
`mcman-internal.h` / `libmc-common.h` for field names and offsets. No GPL source was opened.

**Corrections to the brief and earlier docs (obs):**

* **The PCSX2 card is not formatted.** `tools/third_party/pcsx2/memcards/Mcd001.ps2` (the `PCSX2.ini` slot-1 card:
  `[Folders] MemoryCards = memcards`, `[MemoryCards] Slot1_Filename = Mcd001.ps2`) is 8,650,752 bytes and **every
  byte is 0xFF** (sha256 `47ebe237…8358`; `Mcd002.ps2` is identical). PCSX2 boots with an *erased, unformatted*
  card present; the game's boot check accepts that silently (`_sceMcFatGetInfo` answers `0x8101002F`, no dialog).
* The DBC work area is **`0x996F40`** (`sceDbcInit 0x51C5FC–0x51C618`: `lui 0x99; addiu 0x6F40` →
  `sceDbcSetWorkAddr`), not `0x997140` (SIF README §3).
* An erase block is 16 pages × 512 data bytes = **8 KiB** (+ 256 spare bytes), not 16 KiB.
* MC2_S1 serves **DBC port 2 only** (its setup loop `.text 0x170–0x1D8` runs once): a card in slot 2 is never seen.
* MC2_S1 **never checks ECC on read** (`.text 0x2C78` is `li v0,1; jr ra`) and its command 11 (`WriteSameData`)
  is a no-op returning 1 (jump table entry → exit, `.text 0x2B90`).
* `12` §3 / contract L-40 recommend HLE at `sceMc2*Async`. This implementation sits one level lower, at the DBC RPC,
  so libmc2's own FAT code runs unmodified and its buffers end up byte-identical to PCSX2's (§7).

## 1. The stack

```
H_Memcard_* 0x18F100..          sceMc2*Async 0x513598..  ──► basic_thread 0x5145F8 (prio 1)
  _sceMcFat* 0x5153A0..0x51A0BC (FAT on the EE)  ──► _sceMcp* 0x51A140..  ──► _sceMcCore* 0x51AE68..0x51C35C
  ──► libdbc sceDbc* 0x51C360..0x51D584  ──SIF RPC──►  DBCMAN.IRX (sockets, devices)  ──► MC2_S1.IRX (driver)
  ──► SIO2MAN/SIO2D ──► card            (our HLE: srv_dbcman.cpp + mc_mc2s1.cpp + hle::memcard::Card)
```

## 2. libdbc ↔ DBCMAN (obs)

Servers bound by `sceDbcInit 0x51C3B8` (init flag `0x782B00`): `0x80001300` (client data `0x996740`), `0x8000131C`
(`0x996790`), `0x8000131E/F` (`0x9967B8`, `0x9967E0`); semaphore `sceDbc_sema` id at `0x997000`. DBCMAN registers the
same ids (`.text 0x1DEC`, `0x1E88`, `0x1F2C`), version word `0x0320` (`.data 0x2714`; `sceDbcInit` needs
`ver >> 4 == 50`, `0x51C478`).

**Base server**: every wrapper sends and receives the 144-byte buffer `0x996840` (blocking, mode 0); DBCMAN's
dispatcher (`.text 0x1C88`, table `.rodata 0x2560`, index `fno − 0x80001301`) answers in the same buffer:

| fno | EE wrapper | request | reply word | DBCMAN |
|---|---|---|---|---|
| `0x80001301` | `sceDbcCreateSocket 0x51C770` | `+0` flags, `+4` type, `+8` port, `+12` slot, `+16` field, `+20` name[16], `+40` EE buffer 0, `+44` EE buffer 1 | `+36` socket index, −21 if none free | `.text 0x1940` → `0x54C`; links the first attached device matching the flags (bit 0 type, bit 1 port+slot, bit 2 field, bit 3 name; `0xC00`) |
| `0x80001302` | `sceDbcDeleteSocket 0x51C8A0` | `+0` socket | `+4` 1 / −22 | `.text 0x5A4`: unlink, table word 0, DMA |
| `0x80001303` | `sceDbcGetDepNumber 0x51C960` | `+0` socket | `+4` device index / −12 | `.text 0x5F4` (EE side first requires `work[socket] == 1`, else −12) |
| `0x80001304` | `sceDbcSetWorkAddr 0x51C700` | `+4` EE address | `+0` 1 | `.text 0x8D0`: stores it and DMAs the table (below) |
| `0x80001315/16` | `sceDbcInit/ResetSocket 0x51CBC8/0x51CC78` | `+0` socket | `+4` 1 / −22 / −23 | driver entries 0/1 |
| `0x80001317` | `sceDbcGetDeviceStatus 0x51CD28` | `+0` socket | `+4` 0 | prints "status function is not support" |
| `0x80001319` | `sceDbcSendData 0x51D028` | `+0` socket, `+4` cmd, `+8` size, `+12` data | `+140` result | driver entry 5 (the MC2 command path, §3) |
| `0x8000131A` | `sceDbcReceiveData 0x51D460` | `+0` socket, `+4`, `+8` size | `+140` 1 | driver entry 3 (`MC2_S1 .text 0x1F04` → 1) |
| `0x8000131D` | `sceDbcSearchPortSpecific 0x51CDD8` | `+8` := 2, `+16` port, `+20` slot | `+4` linked socket / −22 / −12 | `.text 0x624` |
| `0x80001363` | `sceDbcGetModVersion 0x51C360` | — | `+0` `0x0320` | `.text 0x8F8` |
| others (`0x1305` GetIopDmabuff, `0x1318` SRData, …) | | | buffer back unchanged | table default; SRData's result word is at `+272`, outside the 144-byte reply |

The game calls GetModVersion, SetWorkAddr and CreateSocket only (`H_Memcard_Init 0x18F100` → `sceMc2CreateSocket`
→ `_sceMcCoreCreateSocket 0x51C130`: flags `param[0] | 1` = 3, type 2, port 2, slot 0, name `"MC2SOCKET"`
`0x7BE690`, buffers `0x9855C0` / `0x985640`).

**Connection state is pushed, never asked for.** DBCMAN keeps one word per socket (`.bss 0x2778`, 16 words; 1 =
linked to a device) and `.text 0xA4` DMAs **128 bytes** from it to the work address — the table, 8 zero bytes,
device record 0 (40 bytes: state, type, field, driver-table pointer, port, slot, name[16]) and 16 bytes of record 1
— whenever SetWorkAddr, a link or an unlink happens (CreateSocket links before its RPC returns). `sceDbcGetConnection
0x51CAD0` copies 64 bytes of the work area under `DIntr` and reports 1 if `work[socket] == 1`, else 3;
`_sceMcCoreGetConnection 0x51C0C0` = `!= 3`. Device record 0 is MC2_S1's: registered at module start (`MC2_S1 .text
0x1C80` → `dbcman_4` = `DBCMAN .text 0x978`: state 1, type 2, port/slot −1), attached when the card is detected
(`.text 0x334` → `dbcman_6` = `0x1BC`: state 2, port 2, slot 0), linked (3) with the socket. PCSX2's EE at
`0x996F40`: `01 00 00 00` … `0x996F88: 03 00 00 00 02 00 00 00 00 00 00 00 30 2E 06 00 02 00 00 00` (obs) — the
driver table `0x00062E30` is an IOP address (MC2_S1 loaded at `0x5DF30`, table at `+0x4F00`, obs in `iopMemory.bin`).

**send_data3** (`sceDbcSendData3 0x51D308`): refuses while `sceSifCheckStatRpc(0x996790)` is busy; builds `{+0 socket,
+4 cmd, +8 size (≤ 1152), +12 data}` in `0x996900` and calls `0x8000131C` **NOWAIT (mode 1)**, 1168 bytes each way,
end function `sceMc2SifCallback 0x51AE38` (→ `iSignalSema(*0x985500)`). DBCMAN (`.text 0x1BCC`, ≤ 1168 bytes) runs
driver entry 5 with (`cmd`, `&size`, `data`) and stores the result at **`+1164`**; the reply is the received buffer
with that word and the size word (48). send_data2 (`0x131E/F`, `sceDbcSendData2 0x51D158`, buffers `0x996DC0 +
192·i`) is the same with 144 bytes and the result at `+140` — no game caller.

## 3. The MC2 command protocol (obs: `_sceMcCore*` senders, MC2_S1 `.text 0x2024`)

Every `_sceMcCore*` function: `sceDbcGetConnection` (3 → fail), fill the **48-byte request block `0x985580`**,
`memset(0x9855C0, 0, 256)` + `SyncDCache`, store the command number in `0x782AEC`, loop `sceDbcSendData3(socket,
cmd, &48, 0x985580, sceMc2SifCallback)` until it returns 1, then wait: `SyncDma 0x51AD10` (picks whichever of
`0x9855C0` / `0x985640` has the larger sequence word, remembers it in `0x782AE8`; neither → status cleared) or
`SyncDmaForRead 0x51ADE0` (buffer 0 only).

Request block: `+0` page, `+4` count, `+8` page size, `+12` pages per block, `+16` card pages, `+20` backup block
1, `+24` backup block 2, `+28` source block, `+32` block, `+36` ECC flag, `+40` EE data address, `+44` EE scratch.
Response block (MC2_S1 `.bss 0x4F48`, 128 bytes, DMA'd by DBCMAN to the socket's EE buffers): `+0` sequence counter
(+1 per command), `+4` device, `+8` **status**, `+12…` payload. Normal path (`.text 0x20BC–0x2178`): clear `+12…`,
size word 48, status 1, counter + 1, ECC size = `page_size/128·3` if `+36` ≠ 0 or command 8 else 0; then the
response goes to EE buffer `toggle` (`dbcman_8`, `.text 0x1E8C`, toggle flips) — except reads, whose page data
goes to buffer 0 + 128 (+ page size per page) and whose response goes to buffer 0 + 0 (`dbcman_9`). Commands 1, 2,
5, 6, 8, 11 first check `card_pages ≥ page + count` and `≥ (backup+1)·ppb` for both backup blocks (`.text
0x217C–0x2214`). **While the new-card flag is set** (`.bss 0x4E08`, set at module start, `.text 0x188`) every command
but 4 and 13 returns 2 and DMAs the *previous* response block with status 2 (`.text 0x2084–0x20B8`).

| cmd | EE sender | IOP | semantics → status |
|---|---|---|---|
| 1 | `_sceMcCoreReadPage2 0x51B708` (`_sceMcCoreReadPage 0x51B8D0` passes the socket's ECC flag) | `0x230C` | per page: read page (+ ECC bytes if `+36`), DMA `page_size` bytes; status 1 (0 on a failed read) |
| 2 | `_sceMcCoreWritePage 0x51B8F0` (`+20` = backup block 1 1023, `+24` = backup block 2 1022 once a superblock was read; `+40` = data) | `0x2460` | per erase block touched: **backup** (if block ∉ {b1, b2} and b2 ≠ 0): block number → page 0 of b2, whole block → b1 (verified copy, `.text 0x2EF0`), number → page 1 of b2; erase the block; program each requested page from EE memory (`sceSifGetOtherData`) with its ECC, read it back; restore the block's other pages from b1 (verified; a mismatch only sets status 0); erase b2. Without backup the block's other pages are left **erased** |
| 3 | `_sceMcCoreGetCardSpec 0x51AFD8` (sends the block zeroed) | `0x29EC` | 1; `+12` u16 page size 512, `+14` u16 pages/block 16, `+16` u32 pages 16,384 (EE stores them + status as the socket's ECC flag) |
| 4 | `_sceMcCoreCheckNewCard 0x51B1B0` | `0x2A2C` | card present → new flag ? **2** : 1; absent → 0 |
| 5 | — | `0x2AC0` | write-back probe (`.text 0x2C88`): b2 page 0 word = −1 → 1; else page 1 repeats it → 2 and `+12` = block; else erase b2 → 1 |
| 6 | `_sceMcCoreWriteBack 0x51B4A0` | `0x2AA8` | probe; on 2 copy b1 → block, erase b2 → 2 (0 on failure) |
| 7 | — | `0x2AE8` | copy block `+28` → `+32` |
| 8 | — | `0x230C` | one page + ECC bytes, DMA `((page+ecc+127)/128+1)·128` bytes from the IOP page buffer |
| 9 | `_sceMcCoreBlockErase 0x51BBD8` (sceMc2Unformat only) | `0x2B14` | erase block `+32` |
| 10 | `_sceMcCoreReadClock 0x51B5F0` | `0x2B4C` | `sceCdReadClock` (cdvdman 24) → 1, `+12` 8 bytes sceCdCLOCK (BCD) |
| 11 | `_sceMcCoreWriteSameData 0x51BA88` (no caller) | `0x2B90` | nothing → 1 |
| 12 | `_sceMcCoreAuthentication 0x51B3B0` (sceMc2Unformat only) | `0x2B78` → `0x6A0` | secrman card authentication → 1 / 2 / 0 |
| 13 | `_sceMcCoreClearNewCardFlag 0x51B2C0` | `0x2A84` | new flag := 0 → 1 |
| 16 / 17 | `_sceMcCoreWritePageFast 0x51BF40` / `ReadPageFast 0x51BD10` (*FastFile only, no game caller) | `0x4820` / `0x4790` | SIO2 DMA straight to/from EE `+40` |
| 14, 15, 0, > 17 | — | `0x2B90` | nothing → 1 |

ECC (`.text 0x2BDC`, generator only): 3 bytes per 128 — column parity over the bit groups `0x55 0x33 0x0F 0xAA 0xCC
0xF0` (stored `~cp & 0x77`), line parities over the indices of odd-parity bytes, `~i` and `i` (stored `& 0x7F`) —
the scheme in Ross Ridge's description. Programs write page + 12 ECC bytes (524); spare bytes 524–527 stay erased.

## 4. What the title screen issues (obs + der)

`_sceMcFatGetInfo 0x515D80` (slot data `0x97B788 + 2200·slot`: `+2184` new-card flag, `+2188` formatted; superblock
cache `0x7827E0 + 388·slot`): no connection → **`0x81010013`**; `_sceMcpCheckNewCard` 0 → `0x81010013`, 2 →
`ClearNewCardFlag` + `+2184 = 1`; if `+2184`: `GetCardSpec` (fail → `0x8101006F`), `_sceMcpReadSysInfo 0x51A1E0`
(`ReadPage2(page 0, count 1, ECC 0)` into `0x984D00`, 388 bytes to the cache; fail → `0x8101006F`); info = {2, …};
magic `"Sony PS2 Memory Card Format"` (27 chars, `0x7BE610`) differs → **`0x8101002F`** (unformatted); version
digits `sb[28]·10 + sb[30] − 528 < 11` → `0x81010086`; then `SetWriteBackHole(sb+68, sb+64)`, `WriteBack`, the
bad-cluster scan, root `"."`/`".."` (`_GetEntryByPos`), `+2188 = 1`, free clusters (reads every FAT cluster);
finally **`0x81019003`** if `+2184` was set (cleared), else 0.

PCSX2 with its erased card (obs, `atlus_logo` state): MC2 counter 4, last command 1 (page 0, count 1, ECC 0), PCSX2
`0x9855C0 = {4, 0, 1}`, `0x985640..0x98583F` = 0xFF, `0x984D00` 512 × 0xFF, `0x7827E0` 388 × 0xFF, `0x782AE8 = 3`,
`0x782AEC = 1`, slot `+2184 = 1`, `+2188 = 0`, send_data3 reply `+1164 = 1` ⇒ the sequence was **CheckNewCard (2) →
ClearNewCardFlag → GetCardSpec → ReadPage(0)** and GetInfo returned `0x8101002F`. The game then shows the Atlus logo
— no dialog for an unformatted card at boot. Our model reproduces exactly these 4 commands (§7).

## 5. The card model (`runtime/hle/memcard/`, library `p3fes_memcard`)

| Part | What | Source / tag |
|---|---|---|
| `card.h` `Card` | 16,384 raw pages × 528 B (8,650,752 B); read/program from byte 0 of a page (≤ 528); **program = AND** (NAND: a bit only goes 1→0, conflicts counted); erase = the 16 pages of one block → 0xFF; dirty-page tracking + `flush` to a backing | Ross Ridge; erased 0xFF obs (PCSX2 card); AND rule = flash physics (inf for PCSX2's emulation — MC2_S1 always erases first, so it is never exercised by the game) |
| `ecc.h` | `ecc_chunk`/`ecc_compute`, `ecc_check_chunk` with single-bit data correction and code-bit detection | Ross Ridge; equal to MC2_S1's generator (obs) |
| `fs.h` | superblock parse, 512-byte directory entries, FAT via the indirect FAT, chains, free count, **formatter** | Ross Ridge, ps2sdk names; formatter values = libmc2's `_sceMcFatFormat 0x516118` (obs, `fs.h` header): magic + `" 1.2.0.0"`, 512/2/16/0xFF00, 8192 clusters, IFC 8, FAT 9–40, alloc offset 41, alloc end 8135, backup blocks 1023/1022, type 2, flags 0x2B, root `"."` 0x8427 len 2 / `".."` 0xA426, libmc2's extension words at +340…+384 |
| `source.h` | `open_memcard(spec)`: `""`/`pcsx2` (PCSX2.ini slot 1), PATH, `new`, `blank`, `none`; **copy-on-write**: the source is opened read-only; the first change writes a full copy to `extracted/_ours/memcards/<name>`, later changes rewrite only dirty pages (flushed after every MC2 command that changed the card); an existing copy is preferred (earlier saves win; delete it to re-seed); a path inside that directory is ours and written in place; folder cards / other sizes fail | — |
| `iop_slot.h` `IopSlotConfig` | what `IopConfig::memcard` points at: slot-1 card, per-command latency (default 1 cycle), RTC for command 10 (fixed 2026-01-01 12:00:00 BCD, deterministic) | — |

Server side (`runtime/hle/sif/iop/`): `srv_dbcman.cpp` — DBCMAN (socket/device tables, matching, connection-table
DMA, base functions, send_data2/3 deferred by the configured latency and completed through `IopCore::complete` at a
later `service()`, the cdvdfsv pattern); `mc_mc2s1.{h,cpp}` — MC2_S1 commands 1–13 as in §3, its persistent
response block / toggle / page buffers, the new-card gate.

**Implemented vs stubbed.** DBCMAN: all functions in its table (SRData answered as the table default, logged).
MC2: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13 modelled from the IRX; 11/14/15 = the IRX's no-op; 12 answers 1 (the secrman
exchange is not modelled, inf); **16/17 not modelled** (status 0, logged as unknown — no game caller).

## 6. Host wiring (`runtime/app/`, not edited here)

```cpp
// main.cpp option table:
} else if (std::strcmp(a, "--memcard") == 0 && has1) { game.cfg.memcard = argv[++i]; }
// game_host.h HostConfig:  std::string memcard;  // "" = PCSX2's slot-1 card if PCSX2.ini exists, else none
// game_host.cpp, after `ic.log = ...;`:
if (auto mr = hle::memcard::open_memcard(cfg_.memcard); mr.ok) {
    log("[host] memory card: " + mr.description);
    if (mr.card) ic.memcard = std::make_shared<hle::memcard::IopSlotConfig>(hle::memcard::IopSlotConfig{mr.card});
} else { error = "memcard: " + mr.error; return false; }   // (or log and fall back to none for the default "")
```

## 7. Validation (MSVC Release, private snapshot of the tree with the wiring above as `P3FES_MEMCARD`)

Runs: `p3fes --iso input/persona3fes.iso --headless --quiet --until-sky 154 --snapshot-at sky:154
extracted/_ours/atlus_logo_mc`, no pad script.

| | `pcsx2` card (erased) | `new` (our formatter) | `none` |
|---|---|---|---|
| boot check | vblank 470 "Checking memory card (8MB) (for PlayStation®2)…", 495 black, 530 ATLUS logo | same screens | vblank 530: "No memory card (for PS2) inserted in MEMORY CARD slot 1 … Start the game anyway? Yes / **No**" (waits, as before) |
| MC2 commands | 4 (4→2, 13, 3, 1 page 0) — PCSX2's counter is 4 too | 73 = two GetInfo calls: 4→2, 13, 3, 1 (superblock), 6→1, 1 ×2 page 82 (root `.`/`..`), 1 ×33 pages 16–80 (IFC + 32 FAT clusters, free count) → `0x81019003`; then 4→1, 1 ×32 pages 18–80 → 0. No writes | 0 (GetConnection = 3, so no DBC page call) |
| sky 154 at | vblank 676, cycle 3,325,997,876 | vblank 676, cycle 3,325,997,876 | vblank 666 |
| libmc2 result | `0x8101002F` (unformatted), `+2184 = 1` | formatted (`+2188 = 1`, `+2184` cleared) | `0x81010013` |
| IOP unknown events | 0 | 0 | 0 |

**`tracediff snapshot` vs PCSX2 `atlus_logo`** (default kernel mask): **5,966 B / 1,329 runs** (was 90,578 / 37,456
with the pad script). Per band: kernel 0, **code 0**, data 780, bss 4,127, heap 680, stack 379. First divergence
**`0x780B48`** (data, 1 byte): libkernel's T2 overflow count, PCSX2 `0x95` (149 × 0.114 s) vs ours `0x63` (99 ×
0.114 s = our 11.28 virtual s) — timing. With `first_flip_timing.txt`: 3,333 B / 1,306 runs (data 772, bss 1,626,
heap 556, stack 379), first divergence `0x780C05` (stale IOP words in libcdvd's reply buffer, M1 IOP-identity class).

| Bytes | Runs | Class (address ranges) | M2 (pad script) |
|---:|---:|---|---:|
| 2,633 | 23 | timing (the M1 mask ranges: MT19937, RpRandomSeed table, T2/vsync counters, `g_kwln*`) | 2,632 |
| 185 | 93 | RW DMA ring `[0x9B0A00, 0xC2F200)`: this frame's packets only (the heap pointer `0x139A5D8` vs `0x139A5A8`, a few qwords of one packet) | **71,970** |
| **0** | 0 | **libmc2/DBC buffers** `0x7827E0`/388, `0x782AE0`/16, `0x97B788`/4,400, `0x984D00`/2,048, `0x985500–0x985A40`, `0x996840–0x996FFF` | 1,436 |
| 8 | 5 | heap objects that held the M2 dialog's font (`0x1150000–0x1162000`, `0x11E0000`, `0x1218000`, `0x11FA000`) | 7,852 |
| 29 | 12 | DBC RPC client structs `0x996740` (IOP `sd`/buffer addresses: IOP identity) | 39 |
| 277 | 69 | heap layout `0x130A000–0x139B000` (M1 class) | 278 |
| 82 | 8 | PADMAN frames `0x7E0740/0x7E07C0` (IOP identity) | 82 |
| 379 | 111 | stack band | 384 |
| 2,373 | 1,008 | other: dead thread-stack words in `.bss` (`0x8001AD84`, `-1` kernel frame words), CRI/ADX handle slots, stale IOP words in RPC buffers, `sCdvdCache` names — the M1/M2 classes | 5,905 |

Every libmc2/DBC byte now equals PCSX2's: the superblock cache and SysInfo buffer (0xFF), the request block
`{0, 1, 512, 16, 16384, …}`, both response buffers (counter 4, status 1, page 0xFF), `0x782AE8 = 3`, `0x782AEC = 1`,
the send_data3 reply, the work area incl. the device record and the `0x62E30` driver pointer. Screenshot vs PCSX2:
`p3fes_gscmp … --tolerance 8` **MATCH**, PSNR 44.28 dB, 0.807 % over tolerance (the M2 numbers; the frame PNG is
byte-identical to M2's, sha256 `dc098334…`). **Determinism**: two runs give identical `eeMemory.bin` (sha256
`81d9636d…a3e7`), `frame.png` and `capture.json`. The PCSX2 card file's sha256 is unchanged after all runs and no
copy-on-write file was created (the boot path writes nothing).

Tests (`tests/sif/test_dbcman.cpp`, 9 cases; with the existing DBC case 10 cases / 11,402 assertions, MSVC and
clang-cl Debug): hand-derived ECC vectors, all 1,024 single-bit corrections, code-bit and double-bit cases; NAND
rules; the formatter's file system; copy-on-write (source bytes and mtime unchanged, copy complete, re-open uses the
copy) and the PCSX2.ini lookup; the boot sequence on an erased card (PCSX2's bytes), reads with ECC, the write
protocol with backup blocks, write-back restore, erase, clock, the new-card gate, no-card answers (−23/−22/−12),
send_data2, the deferred completion.

## 8. Open questions

1. **Per-command latency.** The model completes each MC2 command one cycle after the call; the real driver spends
   milliseconds per page on SIO2. The title path is insensitive (the sky:154 point lands on the same vblank and
   cycle with and without card I/O), but a save (≈ hundreds of commands) would take ~0 virtual time. Check: time
   `Checking memory card` → logo and a save in PCSX2 frames and set `IopSlotConfig::command_latency_cycles`.
2. **Command 12 (authentication) and the fast transfers 16/17** are not modelled (no game caller on the paths seen).
3. The **AND-on-program** rule and erase-to-0xFF are what flash does; whether PCSX2 emulates the AND is unknown
   (it cannot matter for MC2_S1's erase-then-program sequences).
4. **Saving was not exercised end to end** (no input path to the save menu in a headless run yet): the write protocol
   is covered by unit tests only. Check: save in PCSX2 and in our build from the same state and compare the card
   files (our copy under `extracted/_ours/memcards/`).
5. The formatter's output has not been compared with a card the game itself formatted (none available); its fields
   follow `_sceMcFatFormat` (§5).
6. Card hot-plug (MC2_S1's 30-vblank poll, `.text 0x450`) and the slot-2 card are not modelled (slot 2 is
   unreachable for this game).
