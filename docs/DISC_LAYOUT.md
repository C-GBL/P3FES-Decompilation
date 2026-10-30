# Disc layout — CVM containers (Phase 1)

_Observed 2026-10-18 from the user's own disc (`extracted/disc/*.CVM`, see `docs/INVENTORY.md`).
Tool: `tools/ours/cvm/cvm_extract.py` (pure Python 3, `probe` / `list` / `extract`).
Logs and raw evidence: `extracted/_logs/` (gitignored). Nothing here is committed game data._

Legend used below: **observed** = read from bytes; **derived** = arithmetic on observed values;
**inferred** = best explanation, not proven; **unknown** = no evidence.

## 1. CVM container format

Each `.CVM` is a **0x1800-byte (6 x 2048) CRI header followed by a plain, unencrypted ISO9660
image** (observed on all three: PVD `\x01CD001` at file offset 0x9800 = 0x1800 + 16 x 2048;
derived: PVD `volume_space_size` x 2048 == file size - 0x1800 for all three). The extractor does not
assume 0x1800: it scans the first 64 KiB for `CD001` on 2048-byte boundaries and derives the header
size from the PVD position.

Header fields (all three containers have identical layout; multi-byte header fields are **big-endian**,
established by fitting the values; everything not listed is zero):

| Offset | Size | DATA / BTL / BGM value | Status | Meaning |
|---:|---:|---|---|---|
| 0x000 | 4 | `CVMH` | observed | chunk tag |
| 0x004 | 4 | 0 | unknown | |
| 0x008 | 4 | `0x000007F4` | derived | chunk payload length = 0x800 - 0xC -> CVMH chunk is [0x000, 0x800) |
| 0x020 | 4 | `0xC8B6E000` / `0x37D31000` / `0x0F6E8000` | derived | == total .CVM file size in bytes (3,367,428,096 / 936,579,072 / 258,899,968) |
| 0x024 | 7 | `6A 0B 01 0D 25 04 24` | derived | ISO9660 7-byte date: 2006-11-01 13:37:04 UTC+9 (tz byte 0x24 = 36 x 15 min). Same string appears in the PVD creation date `2006110113370400$` at 0x9800+813. Identical in all three. |
| 0x02C | 4 | `0x01010000` | unknown | |
| 0x034 | 4 | `ROFS` | observed | format tag |
| 0x038 | .. | `ROFSBLD Ver.1.52 2003-06-09` | observed | builder tool and version (ASCII, NUL padded) |
| 0x078 | 8 | `01 1F 00 00 03 00 00 00` | unknown | |
| 0x080 | 16 | `00 00 00 01 00 00 00 00 00 00 00 03 00 ..` | unknown | small ints 1, 0, 3 |
| 0x100 | 4 | `0x00000001` | unknown | |
| 0x800 | 4 | `ZONE` | observed | chunk tag |
| 0x804 | 4 | 0 | unknown | |
| 0x808 | 4 | `0xC8B6D7F4` / `0x37D307F4` / `0x0F6E77F4` | derived | chunk payload length = file size - 0x80C (e.g. 0xC8B6E000 - 0xC8B6D7F4 = 0x80C), i.e. the ZONE chunk runs to EOF and the ISO image is its payload |
| 0x80C | 4 | 3 | unknown | |
| 0x810 | 4 | `0x410` | unknown | |
| 0x818, 0x81C, 0x828 | 4 each | `0x800` | inferred | sector size 2048 (value only) |
| 0x820 / 0x82C | 4 | 2 / 3 | unknown | |
| 0x834 | 4 | `0xC8B6C800` / `0x37D2F800` / `0x0F6E6800` | derived | == file size - 0x1800 == ISO image bytes == PVD volume_space_size x 2048 |
| 0x1000 | 32 | `41 00 00 02 00..`, `41 01 00 02 00..`, `41 01 01 02 00 00 02 00`, `41 AA 01 02 xx xx xx xx` | unknown | four 8-byte records; only the last differs per container (DATA `00 A9 25 24`, BTL `00 A1 39 36`, BGM `00 28 07 38`). Not the PVD sector count. |
| 0x1800 | | | observed | ISO9660 logical sector 0 |

Nothing in the CRI header is needed to read files; the ISO9660 structures are self-sufficient.

## 2. ISO9660 parameters (from `probe`, `extracted/_logs/probe_*.txt`)

| | DATA.CVM | BTL.CVM | BGM.CVM |
|---|---:|---:|---:|
| system id / volume id / publisher | `CRI ROFS` / `SAMPLE_GAME_TITLE` / `PUBLISHER_NAME` (placeholders left by ROFSBLD) | same | same |
| logical block size | 2048 | 2048 | 2048 |
| volume_space_size (sectors) | 1,644,249 | 457,311 | 126,413 |
| path table size / L / M LBA | 1562 / 18 / 19 | 370 / 18 / 19 | 10 / 18 / 19 |
| root directory LBA / size | 20 / 2048 | 20 / 2048 | 20 / 10240 (5 sectors, flat volume) |
| other descriptors | sector 17 = 0xFF terminator (no Joliet) | same | same |
| creation / modification | `2006110113370400$` (+9h) | same | same |
| files / dirs / bytes | 7,441 / 122 / 3,358,900,515 | 4,355 / 24 / 931,949,374 | 223 / 0 / 258,730,054 |

Directory records: plain ISO9660 Level 1 style `NAME.EXT;1`, flags 0x00 (file) / 0x02 (dir), no
interleave, no multi-extent records, no extended attributes, volume sequence 1. Extension-less files
are stored as `NAME.;1` (e.g. `LMAP_DAT.;1`); the extractor strips the `;1` **and** the trailing dot
(so they appear as `DATA/LMAP/LMAP_DAT`, `DATA/STRATUM/STRATUM_DAT`, `BTL/MODEL/NPC/N02155BRMD`).
Record dates span `2005-07-19` to `2008-01-04` (preserved as file mtimes; `iso_date` in the manifest).

File-offset formula: `cvm_offset = 0x1800 + lba * 2048`; a file is contiguous (`size` bytes).

### Cross-validation
* `BGM.CVM` minus 0x1800 bytes written to `extracted/_tmp/bgm_stripped.iso`; `7z l -slt` lists 223
  files whose names and sizes match `cvm_extract.py list` exactly; `7z x` output is **byte-identical**
  (`filecmp`) to `extracted/BGM/` for all 223 files (`extracted/_logs/7z_crosscheck_BGM.txt`).
* Same listing comparison for `BTL.CVM` (24 directories, exercises the directory walk): 4,355/4,355
  names and sizes match (`extracted/_logs/7z_crosscheck_BTL.txt`).
* `extract --verify` re-read size + first 16 bytes of every written file from the source: 0 failures
  on all 12,019 files. `_tmp/` contents deleted afterwards.

## 3. Directory trees (file counts are direct files; bytes recursive unless noted)

### DATA.CVM (3,358,900,515 B; no root-level files)
| Directory | Files (direct) | Bytes (recursive) | Content by extension / notes |
|---|---:|---:|---|
| `SFD/` | 41 | 2,052,458,496 | `.SFD` Sofdec MPEG videos — **61% of the disc**; `STAFF_ROLL_A/B/F.SFD` 195/194/192 MB |
| `SOUND/` (+`SPU/` 10, `VOICE/` 30) | 373 | 462,399,270 | 366 `.AFS` voice archives (`V4xxxxx.AFS`), `BBGM03/FBGM03/FBGM04.ADX`, Sony `.HD/.BD/.SQ` banks in `SPU/` |
| `FIELD/` (+`PACK/` 834, `RMD/` 813, `MAP/` 54, `SCRIPT/` 36, `TABLE/` 7, `GRMD/`, `EFFECT/`, `BTL_EFFECT/`, `ICON/`) | 3 | 430,727,442 | `PACK/*.FPC` field packs (322 MB), `RMD/M###_###.RMD` field models, `SCRIPT/*.BF` flow scripts, `TABLE/*.BIN` |
| `BUSTUP/` | 587 | 172,441,336 | `I_B_####A/B.BIN` bust-up packs (name-first PAK), `BUST_DUMMY.BIN`, `LIST.TXT` |
| `CAMP/` (+`PERSONA/` 189, `COMMU/TIM2_*` 88, `FONT/`, `COMU/`, `STATUS/`) | 38 | 62,927,138 | menu `.PAK`s, `.SPR` sprites, `PERSONA/*.TMX` |
| `SOUND2/` (`BATTLE/` 50, `EVENT/` 295) | 0 | 51,522,008 | `.ADX` |
| `EVENT/` (73 `E###/` subdirs, 3,148 files + `SYS/` 39 + 5 direct) | 5 | 43,897,592 | per-event `E###_###.PM1/.PM2/.PM3` triplets (1,042 each), `AEGIS_ITEMTBL.BIN`, `COMUPACK.PAK` |
| `CUTIN/SHAPE/` | 299 | 42,989,504 | `C##_####.CPK` (name-first PAK, **not** CRI CPK) |
| `CARD/` (`PERSONA/` 188, `SARCANA/` 56, `MISC/` 2) | 2 | 14,906,008 | `.TMX` |
| `FACILITY/` | 63 | 14,358,973 | shop `.PAK`s + their `.SEQ` build lists, `PAK.BAT`, `TEST.BMD`, `TEST2.BMD` |
| `OPED/` | 5 | 4,284,544 | |
| `FONT/` (+`SIZE12/`) | 7 | 2,582,417 | `ADVFONTALL.FNT`, `SYSFONTALL.FNT`, `FONT0-3.FNT`, `FSU_00.TMX` |
| `IRX_NEW/` | 21 | 800,024 | IOP modules incl. `IOPRP300.IMG`, `KWLNSND.IRX`, `MCMAN/MCSERV.IRX` (not loaded by the `cdrom0:\LIB31\...` strings in the ELF — dev leftover, inferred) |
| `STRATUM/` | 18 | 719,680 | `STRATUM_DAT` (name-first PAK) |
| `LMAP/` | 1 | 456,256 | `LMAP_DAT` (name-first PAK) |
| `FTP_IRX/` | 10 | 434,354 | `PS2FTPD.IRX`, `HDD.IRX`, `DEV9.IRX`, `SMAP.IRX`, `PFS.IRX`… — **dev-kit networking/HDD leftovers** |
| `ICON/` 25 · `SMAP/` 55 (+`SYMBOL/` 1) · `EFFECT/` 2 · `HELP/` 5 · `SCRIPT/EVENT/` 3 | | 275 KB · 266 KB · 222 KB · 219 KB · 13 KB | `HELP/*.BMD`, `EFFECT/EFFPACK.BIN` |

### BTL.CVM (931,949,374 B; no root-level files)
| Directory | Files | Bytes | Notes |
|---|---:|---:|---|
| `MODEL/NPC/` | 1,072 | 323,051,022 | `N#####[A/B].RMD` |
| `MODEL/PACK/` | 530 | 299,706,944 | `BC###*.PAC` (party), `EM###.PAC` (enemies) |
| `MODEL/PERSONA/` | 256 | 77,804,343 | `PS###.RMD` |
| `MODEL/FACILITYP/` | 256 | 62,531,570 | |
| `MODEL/WEAPON/` | 769 | 16,098,767 | `WP###*.RMD` |
| `MODEL/SYMBOL/` 31 · `MODEL/FIELD/` 21 | | 6.2 MB · 5.5 MB | |
| `SKILL/` | 976 | 54,764,848 | `###.BED` (581, tag `BED4`) + `###.SE` (465, name-first PAK) |
| `BATTLE/` | 13 | 78,757,230 (rec.) | 13 `.TBL` game tables (see §5), `CUTIN/` 311 files 72 MB (`C##_####.CPK`, `.CIN`, `.TMX`), `RESULT/`, `SHUFFLE/`, `PANEL/`, `EFFECT/` (71 small files) |
| `SND_BENC/` (+`BOSS/` 22, `PANEL/` 3) | 4 | 7,586,768 | `BSV###.BVP`, `E1A#.PAK`, `BP_ALL.BIN` |

### BGM.CVM (258,730,054 B; flat, 223 files, no directories)
159 `NN.ADX` (01–~160), 31 `FBGM##.ADX`, 27 `ENV_###.ADX`, `BBGM03.ADX`, `COMBINE.ADX`, `KINPAKU.ADX`,
`THEME.ADX`, 2 `MAP*.ADX`. All ADX (`80 00` header).

## 4. Extension histogram (all containers; `extracted/manifest_summary.json` has per-container splits)

| Ext | Files | Bytes | Observed identification |
|---|---:|---:|---|
| `.RMD` | 3,234 | 571,954,440 | RenderWare binary streams: 2,961 start with chunk id `0xF0F000F0` (Atlus RMD scene), 273 with `0x16` (TexDictionary); libraryID `0x1C020037` (259) / `0x1C02002D` (14) |
| `.PM2` / `.PM1` / `.PM3` | 1,058 / 1,048 / 1,042 | 5.9 MB / 36.5 MB / 149 KB | tag `PMD2` / `PMD1` / `PMD3` at +8 (event cutscene data, one triplet per event) |
| `.PAC` | 964 | 324,391,808 | name-first PAK (252-byte name + u32 LE size, then payload; e.g. `BTL/MODEL/PACK/BC003.PAC` → `bc003.RMD`, size 0x7983B at +0xFC) |
| `.BIN` | 853 | 249,203,980 | 833 name-first PAK; 20 raw tables (`FIELD/TABLE/*.BIN`, `EVENT/*TBL.BIN`); 2 are **zero bytes** (`BUSTUP/I_B_07CA.BIN`, `I_B_08C8.BIN`) |
| `.TMX` | 645 | 72,018,304 | `TMX0` at +8 |
| `.ADX` | 601 | 327,771,380 | CRI ADX (`80 00`) |
| `.BED` | 581 | 33,653,984 | tag `BED4` (BTL/SKILL; semantics unknown) |
| `.SE` | 465 | 22,353,856 | name-first PAK (BTL/SKILL) |
| `.FPC` | 401 | 322,890,432 | name-first PAK (field packs) |
| `.AFS` | 366 | 426,444,800 | CRI AFS (`AFS\0`) |
| `.CPK` | 344 | 48,850,752 | name-first PAK (cut-in), **not CRI CPK** |
| `.PAK` | 89 | 25,905,472 | name-first PAK |
| `.SFD` | 42 | 2,068,389,888 | MPEG-PS (`00 00 01 BA`), CRI Sofdec |
| `.MAP` 54 · `.EPL` 41 · `.BF` 40 (`FLW0`@8) · `.SPR` 31 (`SPR0`@8) · `.IRX` 30 (ELF) · `.SEQ` 16 · `.TBL` 13 · `.BMD` 11 (`MSG1`@8) · `.CIN` 10 (`CIN\0`) · `.TXT` 7 · `.FNT` 6 · `.HD`/`.SQ` 4+4 (`IECS`) · `.BD` 4 · `.INI` 3 · `.BAT` 3 · no-ext 3 · `.BVP` 3 · `.FLD` 1 · `.IMG` 1 (`RESET` romdir) · `.ANM` 1 | | | |

The 25 largest files are all `DATA/SFD/*.SFD` except `DATA/SOUND/V452001.AFS` (38.2 MB, #21) and
`V450001.AFS` (26.6 MB, #23); full list in `manifest_summary.json#largest_25`.

## 5. Notable / odd findings

* **Build-time leftovers shipped on disc** (all paths observed):
  `DATA/FACILITY/PAK.BAT` (calls `pakfile *.seq *.pak`, `copy msg\...bmd`), 16 `.SEQ` files that are
  the input lists for those PAKs (e.g. `FACILITY/AGS_FCL_COMBINE.SEQ` lists `..\battle\result\brp_base.bin`,
  `effect\GAT01_01.EPL`…), `BTL/BATTLE/EFFECT/BTLEFF.BAT` (`..\..\..\persona3\program\tools\pakfile.exe`),
  `BTL/BATTLE/CUTIN/CONVERT.BAT`, `BUSTUP/LIST.TXT`, `CAMP/NAMEDIC_DAT.TXT` (= `NotUse`), `*/BGCOL.INI`,
  `BTL/BATTLE/CUTIN/*/ID.TXT`, `FACILITY/TEST.BMD`, `TEST2.BMD`, `SOUND/SPU/TEST.{HD,BD,SQ}`,
  `BUSTUP/BUST_DUMMY.BIN`, `BTL/MODEL/NPC/N_DUMMY.RMD`, `FIELD/EDITOR.RMD`, `FIELD/BASE.RMD`,
  `DATA/FTP_IRX/*` (PS2 dev-kit FTP/HDD modules), `DATA/IRX_NEW/*` (a second, older IRX set incl.
  `IOPRP300.IMG`). The ELF also keeps `test/*.RMD`, `work/VIEWER.RMD`, `hdd:`/`hst:` device strings
  (VA 0x69ABE0–0x69ADF0 (file 0x59AC60–0x59AE70), 0x7CB240–0x7CB268 (file 0x6CB2C0–0x6CB2E8)) — a host/HDD development loader path.
* **`AGS_` prefix** (FES additions, inferred from name pairing): 2 `CAMP/AGS_CAMP_FR0#.PAK`,
  `FACILITY/AGS_FCL_*.PAK/.SEQ`, `BTL/BATTLE/CUTIN/AGS_PER_*.BIN`, `BTL/SND_BENC/PANEL/AGS_BP_ALL.BIN`,
  `AGS2_BP_ALL.BIN`. Many FES variants exist side-by-side with originals (`*_F.TBL`, `*_AEGIS.BF`,
  `DUNGEONFES.BIN`).
* **Duplicates** (SHA-1, `extracted/_logs/analysis.txt`): 400 identical-content groups, 214,272,532
  redundant bytes. 39 groups span containers: `DATA/SOUND/{B,F}BGM0#.ADX` == `BGM/…`; 23
  `DATA/SOUND2/EVENT/EVE_###.ADX` == `BGM/ENV_###.ADX`/`109.ADX`/`110.ADX`/`COMBINE.ADX`; 13
  `DATA/CUTIN/SHAPE/C4#_####.CPK` == `BTL/BATTLE/CUTIN/…`. Within DATA, `FIELD/PACK/F02#_000.FPC` ==
  `F05#_00#.FPC` and `F04#_000.FPC` == `F07#_00#.FPC` (Tartarus block floors share one pack);
  `BGM/02.ADX`–`18.ADX`, `41.ADX`, `42.ADX`, `63.ADX` (20 files) are one identical 540,058-byte stream
  (placeholder track, inferred).
* **Game data tables** (`BTL/BATTLE/*.TBL`, 13 files, 1.6 MB; `AICALC.TBL` = 524,240 B): headers like
  `40 09 00 00` (`MODEL.TBL`) and `00 70 00 00` (`ENCOUNT.TBL`) are section-size prefixes
  (inferred) — these are gameplay tables, **not** file TOCs (no LBA values). `DATA/FIELD/MAP/*.MAP`
  are fixed 4,608 B.
* No file is encrypted or compressed at the ISO level; every file is a contiguous extent.

## 6. How files are addressed (for the Phase 2 file-I/O layer)

**Observed in `SLUS_216.21`** (addresses are EE virtual addresses; the ELF has one PT_LOAD with `p_offset=0x80`, `p_vaddr=0x100000`, so `VA = file_offset + 0xFFF80`; file offsets are given in parentheses, and the `extracted/_logs/elf_*` files and `manifest_summary.json#elf_directory_tables` use **file offsets**):
1. Volume strings `CDV:data.cvm`, `CDV:bgm.cvm`, `CDV:btl.cvm` at 0x678798 / 0x6787A8 / 0x6787B8 (file 0x578838), and the
   CRI ROFS API (`ROFS_AddVolume`, `ROFS_SetDefVolume`, `ROFS_Open`, `ROFS_OpenRange`, `ROFS_Seek`,
   `ROFS_Tell`, `ROFS_GetNumTr`, `ROFS_SetPfsFuncTbl` at 0x7C6FF8–0x7C70F0 (file 0x6C7078–0x6C7170); source names
   `../../rofs_{hn,if,mai,pfs,dir}.c` at 0x7C6FE8–0x7C7718 (file 0x6C7068–0x6C7798); `rofs err %d` at 0x5CE988 (file 0x4CEA08)). ADX file-system
   layer `ADXF/PS2EE Ver.7.30` (0x7C1A89, file 0x6C1B09) and `ADXT/PS2EE Ver.9.44` (0x7C2269, file 0x6C22E9) for AFS/ADX streaming.
2. A device-prefix / route table at 0x7CB188–0x7CB268 (file 0x6CB208–0x6CB2E8): `\MODEL\`, `\SKILL\`, `VOL:\`, `VOL:`, `BTL:`,
   `\CAMP\`, `\CARD\`, `\CUTIN\`, `\EVENT\`, `\FIELD\`, `\FONT\`, `\HELP\`, `\ICON\`, `\LMAP\`, `\OPED\`,
   `\SFD\`, `\SMAP\`, `\SOUND\`, `pak:`, `hst:`, `hdd:`, `pfs0:`; plus `BGM:%s` at 0x7CB538 (file 0x6CB5B8) next to the
   BGM file-name table (`105.ADX`… at 0x7CB4E0 (file 0x6CB560)). **Inferred:** game code opens files by *path*; the
   top-level directory selects the volume (`BTL:` for `MODEL\`/`SKILL\`, default `VOL:` = DATA, `BGM:`
   for music), and `pak:`/`hst:`/`hdd:` are alternative dev sources.
3. ~9,000 path-like strings and 86 printf templates, e.g. `field/script/everyday.bf` (0x679040, file 0x5790C0),
   `sound/voice_e%03d_%03d/%03d_%03d%05d.adx` (0x6A25E0, file 0x5A2660), `%splayer/bc%03X_wp%X_c0.RMD` (0x69B2F0, file 0x59B370),
   `%senemy/em%03X.RMD`, `bustup/i_b_%02d%x%1da.bin`, `persona3_data/event/e%03d/E%03d_%03d.PM1`
   (0x6A0D70, file 0x5A0DF0). 609 extracted relative paths occur verbatim in the ELF; the rest are generated by
   `sprintf`. (Note `%splayer/bc003.RMD` names do not exist on disc — the matching files are
   `BTL/MODEL/PACK/BC003*.PAC` whose first entry is `bc003.RMD`; so the `%s` prefix likely resolves to a
   `pak:`-style route into the PAC — inferred, verify in IDA.)
4. **The complete directory structure of all three volumes is linked into the ELF** as 149 CRI ROFS
   directory tables, marker `#DirLst#`, contiguous at **VA 0x5E5150–0x6784B8 (file 0x4E51D0–0x578538), 601,800 B**: DATA
   0x5E5150–0x6418D8 (file 0x4E51D0–0x541958) (123 dirs), BGM 0x6418E0–0x644328 (file 0x541960–0x5443A8) (1 dir), BTL 0x6444E8–0x6784B8 (file 0x544568–0x578538) (25 dirs) — same
   order as the `CDV:` strings. Layout (observed, `extracted/_logs/elf_dirlst_tables.txt`):
   ```
   struct DirLst { u32 count; u32 count_again; u32 dir_lba; char marker[8] = "#DirLst#"; u32 zero;
                   struct { u32 size; u32 zero; u32 lba; u8 flags /*0x02=dir*/; u8 unk; char name[34]; } e[count]; }
   ```
   Entries include `.` and `..`, are **sorted by name**, keep the ISO form of extension-less names
   (`LMAP_DAT.`), and match the manifest's `(lba, size, name)` for 12,016 of 12,019 files (the other 3
   are the trailing-dot names). `unk` (byte +13) is **not** a sum/xor/length of the name — unknown; likely
   a lookup-acceleration hash, resolve in `rofs_dir.c` code. The marker constant also sits in the ROFS
   library's rodata at 0x7C73B0 (file 0x6C7430), next to `../../rofs_dir.c` — this is the 150th `#DirLst#` occurrence in the
   file (149 real tables + this constant; the bytes before it do not parse as a table header), so the
   library itself validates/consumes this table format (ROFSBLD "directory record" output — inferred).

**Conclusion (inferred from 1–4):** the game addresses files **by path**, but resolves them **without
reading ISO directories at runtime**: path → in-ELF `#DirLst#` lookup → `(lba, size)` → raw sector reads
from the CVM (`0x1800 + lba*2048`, via `sceCdRead`/CDVD; `DVCI: sceCdSearchFile` strings at 0x7C4C78 (file 0x6C4CF8)
belong to the LIB31 IRX loader, not to data loading). Consequently, for the port the file-I/O HLE
should: (a) intercept `ROFS_Open`-level calls (or the `sceCdRead` LBA reads underneath, which the
manifest maps back to paths), (b) serve bytes from the user's CVM at `0x1800 + lba*2048` or from
`extracted/`, and (c) treat `extracted/manifest.json` as the authoritative path↔LBA↔size map — it is
exactly the data the ELF carries. Any modding/replacement layer must patch or shadow the in-ELF table
(sizes are baked in), not just the ISO.

## 7. Outputs
* `extracted/DATA/`, `extracted/BTL/`, `extracted/BGM/` — 12,019 files, 4,549,579,943 B (gitignored).
* `extracted/manifest.json` — one entry per file: `path, container, size, lba, magic16, ext,
  format_guess, parser_status ("unknown"), iso_date, dir_record_offset, verified` (4.2 MB).
* `extracted/manifest_summary.json` — per-container totals, extension/format histograms, 2-level tree,
  25 largest, duplicate summary, dev leftovers, ELF directory-table facts (28 KB).
* `extracted/_logs/` — probe/list outputs, 7-Zip cross-checks, `analysis.txt`, `elf_dirlst_records.json`
  (the parsed in-ELF table, 12,314 records with ELF **file** offsets; add 0xFFF80 for VA).

## 7. Disc LSNs of the container files (for the sector-level CDVD HLE, ADR-0008)

Observed 2026-10-18 with `tools/ours/cvm/cvm_extract.py list input/persona3fes.iso` (the outer ISO is plain ISO9660, header offset 0; PS2 disc LSN == image LBA, 2048-byte sectors). Topic 11 (`docs/ANALYSIS/11_file_io.md`) established that the game locates the CVMs with `sceCdLayerSearchFile` at boot and that ROFS adds `lba_offset = 3` for the CVM header, so **disc LSN of a file inside a volume = LSN(volume) + 3 + iso_lba**, i.e. byte offset `0x1800 + iso_lba·2048` inside the extracted `.CVM`.

| Disc file | Size (B) | Disc LSN (dec) | Disc LSN (hex) |
|---|---:|---:|---:|
| `BTL.CVM` | 936,579,072 | 633 | `0x279` |
| `BGM.CVM` | 258,899,968 | 457,947 | `0x6FCDB` |
| `DATA.CVM` | 3,367,428,096 | 584,363 | `0x8EAAB` |
| `SLUS_216.21` | 9,096,860 | 2,228,615 | `0x220187` |
| `SYSTEM.CNF` | 51 | 2,233,057 | `0x2212E1` |

The HLE maps a requested disc LSN to `(volume, iso_lba)` by range: `BTL` `[633, 633+457,314)`, `BGM` `[457,947, 457,947+126,416)`, `DATA` `[584,363, 584,363+1,644,252)` (sizes in sectors = file size / 2048 incl. the 3 header sectors). Reads of `SLUS_216.21`/`SYSTEM.CNF` LSNs never occur at runtime (topic 13); serve them from `extracted/disc/` if they do.
