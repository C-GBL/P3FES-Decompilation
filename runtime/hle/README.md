# `runtime/hle/` — sector-level CDVD HLE (`p3fes_cdvd`)

Implements ADR-0008 §1: the game's `sceCdRead(lsn, n, buf, mode)` is served straight from the
user's own disc, by sector, with no path parsing. Contract rows: `docs/RUNTIME_CONTRACT.md` §2.1
(L-01…L-06) and §4.1 (I-04…I-08); evidence: `docs/ANALYSIS/11_file_io.md`, `docs/DISC_LAYOUT.md` §7.

| File | Role |
|---|---|
| `include/p3fes/hle/disc_source.h` | `DiscSource`, `IsoFileSource`, `ExtractedVolumesSource`, `kDiscLayout`, SYSTEM.CNF identity, `open_user_disc` |
| `include/p3fes/hle/cdvd.h` | `CdvdHle` (cdvdfsv command surface), `CompletionHooks`, `guest_read_buffer` |
| `iso9660.{h,cpp}` | the one ISO9660 reader (PVD, directory records, path search) — private |
| `host_file.{h,cpp}` | read-only Win32 positioned reads — private |
| `include/p3fes/hle/mods_overlay.h`, `mods_overlay.cpp` | the mods overlay (ADR-0016, §6) |
| `disc_source.cpp`, `iso_file_source.cpp`, `extracted_volumes_source.cpp`, `cdvd.cpp` | implementations |

Errors are `formats::Result<T>` (no exceptions cross the API); the code mapping is at the top of
`disc_source.h`. Guest-visible outcomes (busy, libcdvd error codes) are values, not errors.

## 1. LSN math

The outer disc is plain ISO9660; PS2 disc LSN == image LBA, 2048-byte sectors. Each CVM is a
6-sector (0x1800-byte) CRI header followed by its own ISO9660 image, and ROFS adds that offset
itself (`vol.lba_offset = 3`, `cvmh_AnalyMainHdrCvm 0x56AE20`, applied in `dcfReqRdCda 0x56AA98`;
`11` §2). Hence

```
disc LSN of a file inside a CVM = LSN(x.CVM) + 3 + iso_lba        (cvm_file_lsn())
byte offset inside the .CVM     = (disc LSN − LSN(x.CVM)) · 2048 = 0x1800 + iso_lba · 2048
```

`kDiscLayout` (DISC_LAYOUT §7, observed from the user's ISO root directory):

| Disc file | Size (B) | Disc LSN | Sectors | Extent |
|---|---:|---:|---:|---|
| `BTL.CVM;1` | 936,579,072 | 633 | 457,314 | `[633, 457,947)` |
| `BGM.CVM;1` | 258,899,968 | 457,947 | 126,416 | `[457,947, 584,363)` |
| `DATA.CVM;1` | 3,367,428,096 | 584,363 | 1,644,252 | `[584,363, 2,228,615)` |
| `SLUS_216.21;1` | 9,096,860 | 2,228,615 | 4,442 | `[2,228,615, 2,233,057)` |
| `SYSTEM.CNF;1` | 51 | 2,233,057 | 1 | `[2,233,057, 2,233,058)` |

Disc size `kDiscSectors` = 2,243,312 (4,594,302,976 B / 2048, `docs/INVENTORY.md`). The root also
holds the directory `LIB31` (IRX modules; loaded through IOP fileio, not `sceCdRead`). Derived:
the five extents are packed back to back from LSN 633. DISC_LAYOUT §7 prints SYSTEM.CNF's hex
LSN as `0x2112E1`; the decimal 2,233,057 (= `0x2212E1`) is what the ISO directory records.

Each row also carries the root directory record's recording date (`DiscLayoutEntry::recorded`, e.g. BTL.CVM
2008-01-04 14:59:58 GMT+9; `verify_disc_layout` compares it with the ISO); `DiscFile::recorded` hands it to
cdvdfsv, whose `sceCdlFILE` replies then match the PCSX2 state (`docs/INTEGRATION_LOG.md` #7).

`ExtractedVolumesSource` serves `extracted/disc/` by this table; every other sector (system area,
outer PVD and directories, LIB31, the tail after SYSTEM.CNF) reads as zeros, as does the tail of a
file's last sector. `verify_disc_layout(iso)` re-checks the table, the root listing and the disc
size against an `IsoFileSource` whenever the ISO is present (the tests run it).

## 2. Async contract (`11` §3, §5.3; L-02/L-03)

The only data-path caller is `srd_exec_dvd 0x558138` on the ADX fs thread (`adxm_fs_proc
0x53FCF8`, prio 18): `sceCdRead(lsn, n, buf, {0,0,0})`, then `sceCdSync(1)` polling until 0, then
`sceCdGetError` (0x20 tolerated). One request is in flight (`srd_obj 0x7A08B0`); whole files are
loaded as a sequence of such reads (chunk size `max_req_sct` not yet traced, Q-06).

`CdvdHle` reproduces libcdvd's single N-command slot:

* `read()` / `seek()` → `Issue::Accepted` takes the slot (libcdvd: `_sceCd_ncmd_prechk 0x50FF58`
  takes `sceCd_ncmd_semid`; `sceCdRead 0x510B80` sets `sceCdCbfunc_num = 1`, `sceCd_c_cb_sem = 1`).
  While the slot is taken every N-command and `search_file` returns `Issue::Busy` — what the game
  sees as `"Ncmd fail sema"` and a 0 return. Nothing is written to the destination yet.
* `service()` is one IOP step: after `set_latency(n)` steps (default 0) the request completes —
  data is copied into the destination span, the drive error is set, and the hooks run **once**.
  `sync(Poll)` = `service()` then 1 if still busy else 0; `sync(Block)` completes immediately.
* Completion order follows `_sceCd_cd_callback 0x50F698` (callback number ≠ 11, no EE callback
  thread because `sceCdInitEeCB` is never called):
  1. `hooks.signal_ncmd_sema` → kernel HLE does `iSignalSema(sceCd_ncmd_semid 0x780BA8)`;
  2. `hooks.clear_cb_sem` → kernel HLE writes 0 to `sceCd_c_cb_sem 0x780BB4`.

  With both done, recompiled `sceCdSync(1) 0x510148` returns 0 (it also needs
  `sceSifCheckStatRpc(ncmd client) == 0`, i.e. the RPC end packet `request_end 0x506BA8` delivered
  on DMAC ch5 — that is the SIF/RPC HLE's job, I-22/I-41), and the next prechk finds the semaphore.
* `break_ncmd()` (sceCdBreak) aborts: the request completes on the next step with `SCECdErABRT` and
  no data. A host read failure completes with `SCECdErREAD`; `last_host_error()` keeps the cause.

Two ways to bind it: an HLE that intercepts `sceCdRead`/`sceCdSync` uses the return values
directly; an HLE at the RPC layer leaves libcdvd recompiled, calls `service()` from its scheduler
(e.g. per vblank, matching L-04's fs-thread wake-up) and maps the hooks onto the guest objects
above. `guest_read_buffer(mem, buf, n)` resolves the guest buffer through `EEMemory::resolve`
(KSEG0/KSEG1/uncached mirrors); the destination is written only at completion. No threads here.

## 3. Command surface: implemented vs stubbed

| cdvdfsv | Call | Status |
|---|---|---|
| `0x80000595` fn 1 | `sceCdRead` → `read()` | **implemented** (L-01, L-02, L-03); `datapattern` 1/2 (2328/2340-byte sectors) and 0-sector reads → `Unsupported`; out-of-disc range / short destination → `Overrun`; `trycount`/`spindlctrl` recorded only |
| `0x80000595` fn 5 | `sceCdSeek` → `seek()` | **implemented** as a data-less N-command (L-06) |
| `0x80000593` | `sceCdBreak` → `break_ncmd()` | implemented (abort → `SCECdErABRT`) |
| `0x80000593` | `sceCdGetError` → `get_error()` | implemented (0 / ABRT / READ) |
| `0x80000593` | `sceCdGetDiskType(2)` | constant `SCECdPS2DVD` (0x14) (L-06) |
| `0x80000593` | `sceCdMmode` | records CD(1)/DVD(2), returns 1; other values 0 (I-05) |
| `0x80000593` | `sceCdStatus` → `status()` | Read 0x06 / Seek 0x12 while busy, Pause 0x0A idle — **inferred** from ps2sdk enum meanings, no game caller |
| `0x80000593` | `sceCdGetToc` → `read_toc()` | **stub**: `Unsupported` (no caller in the ELF; DVD TOC bytes unobserved) |
| `0x80000592` | `sceCdInit` → `init()` | returns 1, clears the error (I-04) |
| `0x8000059A/0x8000059C` | `sceCdDiskReady` | constant `SCECdComplete` (2) (I-08) |
| `0x80000597` | `sceCd(Layer)SearchFile` → `search_file()` | **implemented** (I-07): ISO9660 walk on `IsoFileSource`; `kDiscLayout` on `ExtractedVolumesSource` (root files only; LIB31 paths → `Unsupported`, i.e. unknown, not absent). Returns `{lsn, size, identifier}`; packing the 36-byte `sceCdlFILE` reply (incl. date bytes) is left to the RPC HLE |

Not covered here: L-04 (scheduling the ADX fs thread), L-05 (chunking is the game's), L-07/L-08
(recompiled EE code), L-09 (IOP fileio: `rom0:ROMVER`, `cdrom0:\` listings, LIB31 module loads),
the SIF RPC transport and its ch5 completion (I-22, I-41).

## 4. Asking for the player's copy (API only)

GOAL.md: the port asks for the user's own copy and never ships disc data. The shipped port will:

1. On first run (or when the configured path stops opening), show a file picker for the ISO.
2. Call `open_user_disc(path)`: a regular file → `IsoFileSource::open`, which requires a plain
   2048-byte-sector image, an ISO9660 PVD, and a root `SYSTEM.CNF` whose `BOOT2` is exactly
   `cdrom0:\SLUS_216.21;1`; anything else is refused (`BadHeader` for raw 2352-byte BIN dumps,
   `BadMagic` for another disc). A directory → `ExtractedVolumesSource` (developer setups).
3. On error, show `formats::error_name(code)` + `detail` and ask again; on success, persist only
   the path in the config and construct `CdvdHle(*source, hooks)`.

Nothing is copied, cached, or written: reads go from the user's file into guest memory.

## 5. Tests

`tests/hle/` (`p3fes_hle_tests`, own ctest entry). Synthetic 1 MiB ISO9660 images built in the
test cover acceptance/refusal, directory search, and the async contract without game data.
Real-disc cases read `input/persona3fes.iso` (`P3FES_ISO` overrides) and `extracted/`
(`P3FES_EXTRACTED` overrides) and skip with a `MESSAGE` when absent: both sources agree on 50
random LSNs per CVM plus header/PVD/last sectors, SLUS_216.21 and boundary-spanning reads;
`verify_disc_layout`; the three boot-time CVM searches; 20 `manifest.json` files (8 DATA, 7 BTL,
5 BGM) loaded through `CdvdHle` at `LSN(container)+3+lba` in 32-sector chunks equal the extracted
files byte for byte, on each available source.
`test_mods_overlay.cpp` covers the mods overlay (§6).

## 6. Mods overlay (ADR-0016)

`include/p3fes/hle/mods_overlay.h` / `mods_overlay.cpp`: `ModsOverlay`, a `DiscSource` over the user's disc that
serves whole disc files from host folders (`p3fes --mods DIR`, repeatable; `HostConfig::mods` /
`mods_overlay` for the editor). Off unless asked for: without it nothing in this directory changes behaviour.
The header comment is the reference: folder layout and refusals, every place the guest learns a file's LBA and
size and how each is patched (relocated CVMs, directory records, CVM header sizes, the ELF's ROFS `#DirLst#`
tables in guest RAM), and what the guest sees after a reload. `GameHost` exposes reload / enable / folder list /
the active overrides / the files the guest read since the last reload (`runtime/app/game_host.h`).

## 7. Read log (modernize pass, stage 0; `docs/MODERNIZE_PLAN.md` §3)

`include/p3fes/hle/read_log.h` / `read_log.cpp`: `DiscPathIndex` (LSN → file by path, from the disc's own ISO9660
directories and every CVM's inner image; `kDiscLayout` for the extracted volumes; a mods overlay's relocated extents
are followed), FNV-1a 64 and the line format of `p3fes --read-log FILE`. The events come from cdvdfsv
(`IopConfig::cd_read_sink`, `sif/iop/srv_cdvdfsv.cpp`): one per `sceCdRead`, completed (the bytes delivered, from the
staging copy or guest RAM) or refused (`err=48`). The sink only reads. Line:
`<vblank> lsn= n= bytes= dst= path= off= fsize= hash= [err=]`, `path` = `DATA.CVM:\FIELD\X.PAC` (a CVM member),
`SLUS_216.21` / `LIB31\X.IRX` / `DATA.CVM` (an outer file, or a CVM when the read is not inside one member) or `-`.
Compare two logs with `tools/ours/modernize/logcmp.py reads A B [--by-path]`. Tests: `tests/hle/test_mods_overlay.cpp`
("read log: ..."), `tests/sif/test_cdvdfsv.cpp` (the sink).

## 8. Native files (modernize layer 1, `--native files`; `docs/MODERNIZE_PLAN.md` §3)

With `--native files` the game's own CD wrappers read host files by path and complete at once; the emulated CDVD,
cdvdfsv, SIF RPC, libcdvd and CRI's SRD are not used for any game read. Without `files` nothing changes: the native
branches are behind `native::files::service()`, which is `nullptr` (the six-route gate is byte-exact on that build).

- **Seam** (`runtime/include/p3fes/native/files_service.h`): the `FileService` interface and the inline pointer
  `g_service`, installed by `GameHost` while `--native files` is on. Host side: `runtime/native/files/native_files.h`
  (`NativeFiles`, library `p3fes_native_files`): a by-path table of every outer file and every CVM member built from
  the same walk as the read log (`DiscPathIndex::for_each_file`, so the path strings are the read log's), read straight
  from the host file (the ISO, or `extracted/disc`'s CVMs) through the DiscSource's host reader.
- **Swap points** (game side: `game/src/hcdvd/hcdvd_native.cpp`, `game/include/p3fes/game/files_native.h`):
  1. `H_Cdvd_Update 0x100980` (the game's loader), state 0 after `H_Cdvd_SetRofsDir`: `"<CVM>:<dir><name>"` from the
     node (+344 `VOL:` / `BTL:` / `BGM:` → `DATA.CVM` / `BTL.CVM` / `BGM.CVM`, +600 the directory), the buffer through
     the same heap hook with the same size (`(sectors << 11) + 64`, archives `+ 320`), every sector of the file, the
     256-byte PAK terminator, `H_Cdvd_AddFile`, state 4 — in the same pump, so **every queued request completes in one
     `H_Cdvd_Update` call** (faithful: one request in flight, chunks of 512 sectors through ADXF / ADXSTM / ROFS / CVFS /
     dvCi / SRD / sceCdRead over several frames). A file that is not found leaves the node in state 0 and stops the
     walk, as a failed `ADXF_Open` does (and is printed once per path, up to 16).
  2. `dvCiReqRd 0x55A490` (CRI's `CDV:` device, the CVM containers): the faithful clamp, the sectors copied at once,
     the handle left complete (`+2 = 1`, `+20 = n`, `+12 += n`, no SRD at +28). This serves every read that is not a
     whole-file load: the ROFS mount (CVMH header sectors 0 / 1 and the inner PVD at sector 19 of each CVM, by
     container offset) and the ADX / AFS / Sofdec streams.
  3. `dvCiCdSearchFile 0x559DD8`: `sceCdLayerSearchFile` answered from the host's directory (the sceCdlFILE as
     cdvdfsv writes it), no RPC.
  This is the highest point that serves every read: H_Cdvd sees only whole-file loads; streams and the mount go
  through CRI's file system to `dvCi`, which sees all of them by container offset.
- **Streams** go through point 2, chunk by chunk as ADXSTM asks: each chunk completes at once, but the chunking is
  still the stream's own (its ring buffer frees space only as the decoder consumes), so a stream stays paced by
  playback rather than by the disc. Loading a whole stream at once would need the sound / movie layers' own buffers
  (layers 3 and 4).
- **Reads past the end**: whole sectors, as faithful: the rest of a disc file's last sector is the disc's bytes; a mod
  file is zero-padded.
- **Mods** (ADR-0016) in native mode are a lookup by path (`NativeFiles::set_overrides`, from
  `GameHost::patch_mods_tables`, also after every reload): the mod file's bytes and size, at the disc file's own LSN; no
  relocated extents and the ELF's ROFS tables are not patched. Left: (1) a *streamed* replacement (ADX / Sofdec,
  through dvCi) is served inside the disc file's extent, because CRI ROFS still takes the stream's size from the
  ELF's `#DirLst#` table, so one longer than the disc file is cut there; (2) native reads bypass the overlay, so
  `ModsOverlay::files_read()` / `stale_after_reload()` (the editor's "needs a scene reload" list) do not see them;
  (3) the IOP's module loads (`LIB31\*.IRX`, read by the IOP itself, not through cdvdfsv) still read the overlay's
  sectors: layer 3 owns them.
- **Read log** in native mode: the same format; a whole-file load is logged as the 512-sector records ADXF_ReadNw
  makes of it on the faithful path, so `logcmp.py reads --by-path` compares like with like.
- **Checks** (2026-10-30): `p3fes_native_files_check reads --disc ISO LOG...` (check (a): every read of a faithful
  read log served by path and by container offset) and `p3fes_native_files_check sweep --disc ISO --extracted DIR`
  (check (b)); `tools/ours/modernize/layer1_cd_mask.txt` (check (d), the CD layer's own state). Tests:
  `tests/hle/test_mods_overlay.cpp` ("native files: ..."), `tests/game/test_files_native.cpp`,
  `tests/app/test_modernize.cpp`.