# 11 — File I/O: path → `#DirLst#` lookup → sector reads, CVM volumes, read queue

_Phase 2 topic 11. Database: `ida/work_file_io.i64` (copy of the master). Every address is an EE virtual address; **observed** = read from IDA disassembly/Hex-Rays, **inferred** = derived. Logs: `ida/logs/file_io_*.txt`. Names promoted/assigned: `symbols/deltas/file_io.sym` (413 rows, 282 comments)._

## 0. Headline

* The game never parses ISO9660 directories at run time. Every file open is a **name search inside an in-ELF `#DirLst#` table** selected by directory string (`H_Cdvd_SetRofsDir 0x101520` → `ROFS_SetDir 0x566B08` → `RFMAI_SetDirG 0x569058`, which with `ROFS_SetCond(0,0,1)` (`kwlnInitMain 0x198010`) just **stores the table pointer** into the volume record — no copy, no disc read).
* **`#DirLst#` byte +13 resolved:** it is a lookup-acceleration hash, `search_id = ((218 + Σ toUpperFname(c)) >> 2) & 0xFF` with `toUpperFname` = ASCII uppercase and `'.' → 0` (`rfdir_getSearchID 0x56BC10`, `rfdir_toUpperFname 0x56BC78`). Verified equal on all 12,016 entries of the 149 tables (`ida/logs/file_io_tables.txt`, `sid_mismatch=0`). It is only consulted by the sequential search; CVM volumes use the binary search (§1).
* **Volume geometry (observed):** the CVMs are opened as *files on the disc's ISO9660* through CRI CVFS device `CDV:` (`dvCiOpen 0x55A1F0` → `sceCdLayerSearchFile 0x50FC38` for `\DATA.CVM;1` etc.), and ROFS adds the CVM header offset itself: `vol.lba_offset = 3` (u32 BE at CVM file offset 136, `cvmh_AnalyMainHdrCvm 0x56AE20`), applied in `dcfReqRdCda 0x56AA98`. Hence **disc LSN = LSN(x.CVM) + 3 + iso_lba** ⇔ CVM-file byte offset `0x1800 + lba·2048`. ADR-0008's math is confirmed.
* **Single data-path `sceCdRead` caller:** `srd_exec_dvd 0x558138` (`sceCdRead 0x510B80` at `0x558250`). Reads are asynchronous (`dvg_ci_rdmode 0x7A2A74 = 0`), one in flight (`srd_obj 0x7A08B0`), issued and polled from the **ADX file-system thread** (`adxm_fs_proc 0x53FCF8`, priority 18) — not from the main thread.
* The game-side API is `H_Cdvd_*` (`0x100800–0x102FFC`, Atlus `h_cdvd.c`): a FIFO of 868-byte request nodes pumped once per frame by `H_Cdvd_Update 0x100980` from `kwlnUpdate 0x1983A0`; whole files are loaded into 64-byte-aligned heap buffers; name-first PAKs are indexed on load into a 256-slot cache. 136 functions call `H_Cdvd_Request 0x100D80` (218 sites). `0x1934F0` is **not** the file layer (it is the disc-swap check task `H_FileSetup_UpdateTstDvdChkDrawTask`).

## 1. Lookup algorithm (`rofs_dir.c`, `rofs_mai.c`)

Mount-time binding (observed, `kwlnInitMain 0x198010`, `0x19813C–0x19819C`):
```
ROFS_Init(&cfg{6 handles,3 volumes,836 dir entries})   ; 0x567820
ROFS_SetCond(0,0,1)                                    ; "external directory records" mode
ADXF_SetupRofs(0)        -> cvFsAddDev("ROFS", ROCI_GetInterface)                 ; 0x53B250
ADXF_AddRofsVol("VOL","CDV:data.cvm",0) -> cvFsOpen("CDV:data.cvm") ; cvFsAddVolumeEx("ROFS","VOL",hn)  ; 0x53B318 -> 0x56CAB0 -> RFMAI_MountG 0x567C58
ADXF_AddRofsVol("BGM","CDV:bgm.cvm",0);  ADXF_AddRofsVol("BTL","CDV:btl.cvm",0)
ROFS_SetDir("VOL", g_rofs_dir_VOL 0x5E5150); ROFS_SetDir("BGM", 0x6418E0); ROFS_SetDir("BTL", 0x644330)
ADXF_SetDefDev("VOL")
```
Volume names live at `0x7CC128 "VOL"`, `0x7CC12C "BGM"`, `0x7CC130 "BTL"` (gp-relative, gp = `0x7D2CF0`).

Per-open path (observed):
1. Game path → `H_Cdvd_BuildPathUppercase 0x101010`: `"VOL:\" + path`, `/`→`\`, a–z uppercased. `H_Cdvd_BuildVolumePaths 0x101240` splits dir/file; if the normalized directory string equals an entry of `g_tbl_rofsDirNames_BTL 0x5CDD80` (25 strings: `\`, `\BATTLE\`, `\MODEL\…`, `\SKILL\`, `\SND_BENC\…`) the file becomes `"BTL:NAME"`, else `"VOL:NAME"` (`0x7CB1B8/0x7CB1C8` hold the `"VOL:"`/`"BTL:"` pointers). The brief's "route table" `0x7CB188–0x7CB268` is just these strings plus the rtFS device names `pak:`/`hst:`/`hdd:`/`pfs0:`; the real routing tables are:
   | table | VA | entries | parallel pointer table |
   |---|---|---|---|
   | `g_tbl_rofsDirNames_BTL` | `0x5CDD80` | 25 dir strings | `g_tbl_rofsDirLst_BTL 0x5CDDF0` → `#DirLst#` tables `0x644330–0x6783B0` |
   | `g_tbl_rofsDirNames_VOL` | `0x5CE590` | 123 dir strings | `g_tbl_rofsDirLst_VOL 0x5CE780` → `0x5E5150–0x641500` |
   | (BGM has one directory) | — | — | root table `0x6418E0`, set once at init |
   25 + 123 + 1 = 149 = every `#DirLst#` table in the ELF; the full map is in `ida/logs/file_io_tables.txt`.
2. `H_Cdvd_SetRofsDir 0x101520`: `strcmp` the directory (first 300 slots, stops at empty) against both tables and `ROFS_SetDir(volume, table)` (retry loop on error, `"rofs err %d"`). `RFMAI_SetDirG 0x569058` validates `+12 == "#DirLst#"` (`0x7C73B0`) or the volume name and, in cond-0 mode, writes the pointer into `RofsVolume.dir` (`+16`).
3. `ADXF_Open("VOL:NAME",0) 0x53C910` → ADXSTM → `cvFsOpen` → `ROCI_Open 0x56C900` → `ROFS_Open 0x5665D0` → `RFMAI_OpenG 0x568388`: `rfmai_divideFname 0x566F78` splits `VOL:` (uppercased, ≤ 8 chars; no colon → default volume), `rfmai_getVolume 0x5671F0`, then `RFDIR_SearchName(name, vol.dir, vol) 0x56C5B0`.
4. **Search:** `RFDIR_SearchName` picks `rfdir_nameBinarySearch 0x56C320` when `vol.lba_offset != 0` (true for all three CVMs, offset 3) else `rfdir_nameSequentialSearch 0x56C4B0`. Binary search: query uppercased (`RFMAI_ToUpperStr 0x569848`); a copy gets `"."` appended if it contains no period (this is why extension-less names are stored as `LMAP_DAT.`); `"."`→1, `".."`→2; per probe, directory entries (`flags & 2`) are `strcmp`'d against the raw uppercase query, files against the dotted one; `lo=2, hi=count`, 1-based result. **Case-insensitive, exact length, no wildcard, no `;1`** (the table stores names with `;1` already stripped: `rfdir_getOneDirEnt 0x56BCB0` copies `len-2` chars for files when building a record from an ISO directory record). Sequential search filters on `entry.search_id == getSearchID(query)` and then uses `rfdirStrcmpFileName 0x56BAC8` (a trailing period in either operand is optional).
5. Result: entry = `table + 24 + 48·(idx−1)`; `RFHN_CreateHnG 0x565A20` stores `start_lba = entry.lba (+8)`, `size = (u32 +4 ⟪32) | (u32 +0)` (`RFMAI_CnvU32plusU32toS64 0x569BD0` — the "u32 0" at +4 is the **high half of a 64-bit size**), `size_sct = (size+2047)>>11`. `ADXF_GetFsizeSct 0x53D968` returns that sector count to the game.

Record definitions (now IDA structs in the copy, delta documents them):
```
struct RofsDirLstHdr { u32 count; u32 count2; u32 dir_lba; char marker[8]="#DirLst#"; u32 zero; };     // 24 B
struct RofsDirLstEnt { u32 size_lo; u32 size_hi; u32 lba; u8 flags /*bit1 dir*/; u8 search_id; char name[34]; }; // 48 B
struct RofsVolume    { int img_hn; int lba_offset; int root_lba; int root_size; RofsDirLstHdr* dir; u16; char name[8]; u16; int; u8 key[8]; u8 cvm_id[8]; }; // 52 B, array at g_rofs_work+40
struct RofsHandle    { int size_lo, size_hi, rofs, dir_idx, start_lba, pos_sct, size_sct; RofsVolume* vol; int req_sct, rd_sct, rd_rem, sct_len; void* buf; s16 active, req_state, stat, err; }; // 60 B
```
Only flags 0x00 and 0x02 occur in the tables (census). `ROFS_ChangeDir/LoadDir` (ISO path-table walk `rfdir_searchPath 0x56C5F0`) are reachable only through `ROCI_ChangeDir` and are not used by the game.

**Confidence: high** (all steps read from instructions; hash verified exhaustively).

## 2. Volume mapping (CVM → disc LBA)

Observed in `RFMAI_MountG 0x567C58` / `rfmai_getCvmfInfo 0x5674C0` / `rfmai_readPvd 0x5676B0` / `RFHN_ReqRdG 0x565E10` / `dcfReqRdCda 0x56AA98` / `dvCiOpen 0x55A1F0` / `dvCiReqRd 0x55A490`:
1. `cvFsOpen("CDV:data.cvm")` → `dvCiOpen("data.cvm")`: `dvci_conv_fname 0x55A9B0` builds `"\DATA.CVM;1"` (root `"/"` from `ADXPS2_SetupDvdFs 0x547668`, params at `0x847F1C`), file cache miss → `dvCiCdSearchFile 0x559DD8` → `sceCdLayerSearchFile 0x50FC38` (SIF RPC `0x80000597`, `cdrdsf`) → handle `+32 = start LSN`, `+36 = size`, `+8 = size_sct`, `+12 = pos_sct`. **So the CVMs are located by ISO9660 search at boot — three RPC calls the HLE must answer** (`DATA.CVM`, `BGM.CVM`, `BTL.CVM`; the sectors of the disc's own PVD/directory are never read by the EE).
2. Mount reads, per volume, through the synchronous `RFMAI_ReadWG 0x569538`: CVM-file sector 0 (`CVMH` header, big-endian: zone count at file offset 128 = 1, zone select 132 = 0, **data LBA offset 136 = 3**, zone table at 256 → sector 1), sector 1 (`ZONE` header: sector length 2048 at +12/+16, data location 3 at +32), then the PVD at `zone.data_loc − lba_offset + 16 = 16` which `rfmai_checkMedia 0x566F30` checks for `CD001`. The root directory record read is skipped (cond 0). `rfmai_decipherSectors 0x569C00` (`RSU_Decipher`) is applied to these metadata sectors only; since the PVD is plain in the CVM and the check passes on hardware, the descramble is the identity for these discs (inferred). It is EE code and gets recompiled anyway.
3. Every read: `RFHN_ReqRdG` (`0x565F70–0x565F88`) calls `dcfReqRdCda(vol.lba_offset=3, vol.img_hn, start_lba + pos_sct, nsct, buf)` → `dcfReqRdBlk(img, lba+3, …) 0x56A860` → `rfpfs_parentSeek` → `pfsCvfsSeek`/`cvFsSeek` → `dvCiSeek 0x55A3C0` (`pos_sct = lba+3`, clamped) → `dcfReqRd` → `cvFsReqRd 0x5564E0` → `dvCiReqRd`: `SRD_ReqRdDvd(srd, lsn = file_start_lsn + pos_sct, nsct, buf, mode)`.

**Contract:** `sceCdRead(lsn, n, buf, mode)` with `lsn ∈ [LSN(x.CVM), LSN(x.CVM)+size_sct)` reads `n·2048` bytes at byte offset `(lsn − LSN(x.CVM))·2048` of that CVM file; the ISO LBA inside the CVM is `lsn − LSN(x.CVM) − 3`, and `extracted/manifest.json` (`lba` = in-CVM ISO LBA, `offset = 0x1800 + lba·2048`) maps it back to a path. `nsct` is clamped to the ROFS file end by `RFHN_ReqRdG`, so reads never cross a file boundary except through the ADX stream path's own ranges.

**Confidence: high** for the offset math and search-at-boot (instructions + CVM header bytes cross-checked against `extracted/disc/DATA.CVM`); **medium** for RSU identity.

## 3. Read path, threads, libcdvd surface

Layering (all EE code; each arrow is a direct call or vtable slot, observed):
`H_Cdvd_Update` → `ADXF_ReadNw 0x53D380` (buffer must be 64-byte aligned, error `E0120401`) → `adxf_ReadNw32 0x53D1F0` wraps the caller's buffer in an SJRBF ring of `nsct·2048` bytes → ADXSTM → `adxstmf_ExecRead 0x546788`: `cvFsSeek(hn, base+pos)` + `cvFsReqRd(hn, min(ring free/2048, remaining, max_req_sct(+44)))` per step → `ROCI_ReqRd 0x56C988` → `ROFS_ReqRd 0x566708` → `RFHN_ReqRdG` → … → `dvCiReqRd` → `SRD_ReqRdDvd 0x557B80` (single global slot `srd_obj 0x7A08B0`; `SRD_Create 0x557A58` returns 0 while busy, ROFS then reports −200/−204 and the stream retries). The default `max_req_sct` is set in the ADXSTM handle constructor and was **not** traced (`ADXF_SetReqRdSct 0x53DF50` is never called by the game) — so a whole-file `ADXF_ReadNw` is served as a sequence of `sceCdRead`s, not one call. Sofdec (`H_Cdvd_StartSfd 0x1023F0` → `mwPlyStartFname`) and ADX (`H_Cdvd_StartADXTFile* 0x102530/0x1025C0`, `H_Cdvd_LoadAfsFile 0x1024A0`) streams use the same ROFS/CVFS chain (`ADXSTMF_ExecHndl 0x546BB0` opens `VOL:name` via `cvFsOpen`) and bypass only the `H_Cdvd` buffers; the ADX stream path toggles `sceCdRMode.spindlctrl` (`0x7A092C`, `srd_exec_dvd 0x558218`).

Issue/poll (observed, `srd_exec_dvd 0x558138`): `stat 1 → sceCdRead(lsn, nsct, buf, &mode{trycount 0, spindlctrl 0, datapattern 0 (SCECdSecS2048)})` → `stat 2 → sceCdSync(1)==0 → srd_check_dvd_error 0x557FE8 (sceCdGetError 0x510EF0; 0x20 tolerated) → 3 ok / 9 error`; break: `sceCdBreak 0x510F88` + `sceCdSync(0)`. `dvCiReqRd` calls `InvalidDCache(buf, buf+n·2048−1)` before the request. Who runs it: `SRD_ExecServer 0x558500` ← `adxt_ExecFsSvr 0x53E0E0` ← `ADXT_UpdateFsStat 0x53E0B8` ← `SVM_ExecSvrFs 0x565420` ← **`adxm_fs_proc 0x53FCF8`**, the ADX fs thread (`adxm_SetupFsThrd 0x540360`: `sceCreateThread`, stack `adxm_stack_fs 0x78AF70` 4096 B, priority 18 after creation; defaults in `ADXM_SetupThrd 0x540588`: safe 8, vsync 16, fs 18, main 24, mwidle 25). The thread sleeps (`adxm_SleepThread`) and is woken by the ADX vsync/idle machinery (`adxm_WakeupThread 0x540048`) — topic 12 owns the thread/semaphore inventory; **file I/O makes no progress unless this thread runs**. ROFS completion is polled on the same server chain: `RFMAI_ExecServerG 0x568938` → `rfmai_updateHnStat 0x568710` (pfs `GetStat==1` and `GetNumTr == req<<11`). `RFHN_WaitCompleteReq 0x5658B8` (mount only) spins the servers itself with `RFTGT_Wait100MicroSec`.

libcdvd calls issued by the whole file layer (observed xrefs):
| sce call | VA | callers | RPC (topic 12 verifies ids) |
|---|---|---|---|
| `sceCdInit(0)` | `0x510460` | `H_Cdvd_InitCd 0x100800`, `kwlnInitPS2Systems 0x197030` | bind `0x80000592` |
| `sceCdMmode(2)` | `0x511040` | same | scmd `0x80000593` |
| `sceCdDiskReady(0)` | `0x510960` | `H_Cdvd_InitCd` | `0x8000059C` |
| `sceCdSearchFile`/`LayerSearchFile` | `0x50FF38`/`0x50FC38` | `dvCiCdSearchFile 0x559DD8` (3× at boot; also `dvCiIsExistFile/GetFileSize`) | `0x80000597` |
| `sceCdRead` | `0x510B80` | `srd_exec_dvd 0x558250`; (`dvci_load_flist 0x55AE28`, dead: `ADXPS2_LoadFcacheDvd` has no callers) | ncmd `0x80000595` fn 1, end-callback `_sceCd_cd_read_intr 0x50F8A8` |
| `sceCdSync(0/1)` | `0x510148` | SRD, DVCI (16 sites) | polls `sceCd_c_cb_sem 0x780BB4` + `sceSifCheckStatRpc` |
| `sceCdGetError` | `0x510EF0` | `srd_check_dvd_error`, `SRD_SetDvdSeekPos` | |
| `sceCdBreak` | `0x510F88` | `srd_exec_dvd` | |
| `sceCdSeek` | `0x510D60` | `SRD_SetDvdSeekPos 0x558AE0` | ncmd fn 5 |
| `sceCdGetDiskType2` | `0x510E30` | `0x1934F0` (disc check) | |
`sceCdCallback 0x50F630` has no callers (no user callback). No `sceSif*` call is made by the file layer itself; everything goes through libcdvd's RPC clients.

**Confidence: high** for the chain and callers; **medium** for scheduling (wake source not traced).

## 4. Consumers (game side)

API (observed): `H_Cdvd_Request(path, isArchive) 0x100D80` → node (dedup by uppercased path, refcount `+858`); `H_Cdvd_IsFileLoaded 0x1016B0` (`state==4`, 131 sites); `H_Cdvd_ReadSync 0x1023A0` (spins `H_Cdvd_Update`, 42 sites — blocking loads at init: `K_Data_LoadFldMainScript 0x1B7B10`, `sprFontInit 0x111F50`, `H_Fade_ReadPak 0x107020`…); `H_Cdvd_Destroy 0x100EC0` (197 sites); `H_Cdvd_CacheFindFile 0x1021C0` (66) and `H_Cdvd_ArchiveGetFile 0x102100` (159) to address entries; `H_Cdvd_FileExists 0x1008B0` (16, table-only probe). Callers by module (`ida/logs/file_io_callers.txt`): 56 unnamed `sub_*`, `H_Camp*` 16, `MT_EvtCustomEvent*` 13, `K_Fldrc*` 5, `K_Data*` 4, battle (`btl*`), `mdlStreamRequestCdvd 0x3198C0`, `op*`/`bp*` resource requests, `fr*` fonts.

Loading (observed, `H_Cdvd_Update`): the whole file is read into `RwHeapMalloc((sct<<11) + 64, 0x40000)` (archives: `+320`, and 256 zero bytes are appended after the data as a PAK terminator), aligned up to 64 bytes (`+272` aligned, `+276` raw). No decompression anywhere in this layer. **Name-first PAK** (`H_Cdvd_AddFile 0x101E30`, `H_Cdvd_ArchiveGetFile`): entry = 252-byte NUL-padded name + u32 LE size, data at +256, next entry at `+256 + align64(size)`, empty name terminates; every entry is registered in `sCdvdCache 0x7D6F80` (256 × 148 B: `used, owner, name[128], data, size, 0`) under `UPPER(dir + name)` with `/`→`\`. The same cache backs the RenderWare rtFS `pak:` device (`H_Cdvd_RtFsPak_* 0x1016D0+`, `H_Cdvd_InitRtFS 0x101C70`) so RW streams (`RwStreamOpen("pak:…")`) read from memory; `hdd:`/`hst:` are dev-only. Buffers are heap allocations (`0x9ACC80+`), not fixed addresses; the only fixed buffers are the path scratch areas `0x7CED80–0x7CF780` used by the stream starters.

**Confidence: high.**

## 5. What the runtime (Phase 3) must emulate

1. **Sector service.** `sceCdRead(lsn, n, buf, mode)`: locate the CVM whose disc extent contains `lsn` (from the disc ISO9660 — `manifest.json` has in-CVM LBAs and sizes but **not** the three CVM start LSNs on the disc; take them from `extracted/disc`'s ISO directory or the user's ISO at HLE init), copy `n·2048` bytes from byte offset `(lsn − LSN_cvm)·2048` of that CVM file. `mode.datapattern` is always 0 (2048-byte sectors); `trycount` 0; spindle control varies (ignore). Reads of CVM sectors 0, 1 and 16 happen at boot (mount) before any file read.
2. **`sceCdSearchFile` RPC** for `\DATA.CVM;1`, `\BGM.CVM;1`, `\BTL.CVM;1` → `{lsn, size, name}`; `sceCdDiskReady → 2`, `sceCdGetDiskType2 → 20 (PS2 DVD)`, `sceCdMmode/Init → 1`, `sceCdGetError → 0`.
3. **Async semantics that must be kept** (if hooking at `sceCdRead` rather than at the IOP RPC): `sceCdRead` returns 1 immediately; completion is observed only through `sceCdSync(1) == 0`, which requires `sceCd_c_cb_sem 0x780BB4 == 0` **and** `sceSifCheckStatRpc(ncmd client) == 0`; the real end-callback `_sceCd_cd_read_intr 0x50F8A8 → _sceCd_cd_callback 0x50F698` also **signals `sceCd_ncmd_semid 0x780BA8`**, which `_sceCd_ncmd_prechk 0x50FF58` polls before every N-command — if the HLE skips it, the second `sceCdRead` fails (`"Ncmd fail sema"`). Completing synchronously inside `sceCdRead` is behaviourally safe because every consumer polls; FIFO order is enforced by the game itself (`H_Cdvd_Update` keeps one request in flight; `srd_obj` is a single slot).
4. **Threads.** The issuer is the ADX fs thread (prio 18); the main thread only polls `ADXF_GetStat`. The kernel HLE must schedule it (and its wake-ups) or file loads hang in state 2.
5. **Alignment/DMA.** Destination buffers are 64-byte aligned (`ADXF_ReadNw` rejects others; `H_Cdvd_Update` aligns); `dvCiReqRd` invalidates the D-cache over the range, `sceCdRead` writes back the D-cache (`sceSifWriteBackDCache` over `n·2048` unless `sceCd_ee_read_mode & 2`). A memcpy into EE RAM is sufficient.
6. **Path-level hook (deferred, ADR-0008):** the right seam is `RFMAI_OpenG 0x568388` / `RFDIR_SearchName 0x56C5B0` plus the 149 tables (sizes are baked into `RofsDirLstEnt.size_lo/hi`); the lookup rules in §1 (uppercase, dot-append, `;1` stripped, dirs vs files compared differently) define exactly what a replacement table must contain.
7. **`manifest.json` can answer:** in-CVM LBA ↔ path ↔ size for every file (= the `#DirLst#` content). **Cannot answer:** disc-level LSNs of the CVM files, the CVM header/zone sectors, the per-request chunking (`max_req_sct`), or anything about `hst:`/`hdd:`.

## 6. Names: promotions and corrections

413 delta rows (`symbols/deltas/file_io.sym`; 263 functions/globals + 150 table rows): tge-pr4 hint names verified from the instructions and promoted (`source=tge-pr4 verified=yes`), our own names for CRI statics (`rfdir_*`, `rfmai_*`, `cvfs_*`, `dvci_*`, `adxstmf_*`) and tables (`g_tbl_rofsDirNames_{VOL,BTL}`, `g_tbl_rofsDirLst_{VOL,BTL}`, 146 `tbl_DirLst_<VOL>_<PATH>`; the three root tables keep the lead's `g_rofs_dir_*`). **FLIRT false positives replaced** (bundled-library collisions, record for `05_flirt.md`): `mem_free_0 0x56C900 → ROCI_Open`, `atan2l_8 0x565820 → pfsCvfsGetSctLen`, `cosl_8 0x565838 → pfsCvfsGetNumTr`, `sceLibgcc32GetErxEntries_10 0x5658A8 → PFSCVFS_GetPfsTbl`, `logl_0 0x53F9B0 → adxm_goto_svr_border`. Hint spelling fixed: `H_Cdvd_StartADXTFIle → H_Cdvd_StartADXTFile 0x1025C0`. The fes-pc-recomp labels `fileRequestGet_candidate 0x100D80` / `cvFsFindDevByName_candidate 0x555FA0` / `cvFsSplitDevicePath_candidate 0x5561E8` are confirmed as `H_Cdvd_Request` / `cvfs_variousProc` / `cvfs_getDevName`. Function comments are in the delta's `# comment` block — **note:** `import_symbols.py` currently ignores `#` lines, so the lead must merge comments separately.

## 7. Open questions / blocked

* `max_req_sct` default (ADXSTM handle `+44`): decides the `sceCdRead` chunk size of a whole-file load; needs `adxstm` constructor decompilation (~20 min).
* ADX fs-thread wake source (`adxm_WakeupThread 0x540048` callers are ADX vsync/idle procs) — topic 12.
* `RSU_Decipher` identity is inferred, not traced through `rsu_Encipher`.
* `0x1934F0`: the disc-check task looks for `SLPM_664.45`/`SLPM_666.89` on a swapped disc (`cdrom0:\` via `sceDopen/sceDread`, IOP fileio) — carry-over feature, needs IOP `fileio` HLE if supported.
