# 13 — Overlays, dynamically loaded and self-modifying EE code

_Phase 2 topic 13. Database: `ida/work_overlays.i64` (copy of the master, discarded after merge). Logs: `ida/logs/overlays_census.log`, `overlays_ctx.log`, `overlays_pass3.log`, `overlays_pass4.log`, `overlays_pass5.log`, `overlays_filescan.tsv`, `overlays_newfuncs.txt`. **Observed** = IDA/raw bytes show it at the cited VA; **inferred** = our reading._

## Question and verdict

**Does the EE ever execute code that is not in the ELF image as loaded?** **No, with one scoped exception that is kernel-mode, not game code:** libkernel copies three position-dependent patch payloads out of the data band into kernel memory (`0x80074000`, `0x80075000`, `0x80076000`, `0x82000`) at startup and installs them with `SetSyscall`. Nothing writes into `0x100000–0x5A1400`, no file on the disc contains an EE ELF or EE code, no loader API that targets EE memory has a caller, and every `FlushCache(2)` site is one of those three kernel-patch installs. The static image is complete for the recompiler; the residual risks are indirect control flow (§3, §7) and 70 functions IDA had not carved out (§3a).

_Name caveat: `load_flist`, `srd_exec_dvd`, `kwlnInitPS2Systems` `0x197030`, `itfPnlRegist2` `0x3A8B00`, `btlUnit*`, `H_Cdvd_*`, `H_Malloc_*` and the RenderWare `rp*/Rw*` names are tge-pr4 hints (`07`), used here as labels; only `load_flist` and `srd_exec_dvd` were read end-to-end and are promoted in the delta. libkernel names (`InitExecPS2`, `InitTLBFunctions`, `InitAlarm`, `InitSystemCallTableAddress`, `SetArg`, `PatchIsNeeded`, `kCopy_1`) are FLIRT names confirmed by reading._

## 1. Reads and copies into the code band `0x100000–0x5A1400` [obs]

| Source | Call sites | Destination evidence | Code-band hit? |
|---|---|---|---|
| `sceCdRead` `0x510B80` | 2: `load_flist` `0x55AE28`, `srd_exec_dvd` (CRI SRD/DVCI) | `load_flist` reads into its `$a1` argument (`0x55AD2C` → `0x55AE24`), a CRI ROFS work buffer; `srd_exec_dvd` serves CRI stream requests whose buffers come from the caller's handle | none constant; see §1b |
| `sceCdReadIOPm`, `sceCdReadChain`, `sceCdStRead` | no such functions in the image (FLIRT + name search) | — | — |
| `memcpy` `0x521250` | 828 sites / 324 functions | all destinations are register-carried; IDA resolved **0 write xrefs** (`dr_W`) into the code band | none |
| `memset` `0x521408` | 661 sites / 534 functions | same census: 0 `dr_W` into code band | none |
| `_sceSifSetDma` `0x503520` | 4 sites, all SDK (`_sceSifSendCmd_0`, `sceSifInitCmd`, `sceSifResetIop`, `sub_506088`) | EE→IOP direction only | n/a |
| `sceSifLoadElf` `0x50C650`, `sceSifLoadElfPart` `0x50C630`, `LoadExecPS2` `0x50DA10`, `ExecPS2` `0x50D9A0` | **0 callers** each (`_sceSifLoadElfPart` is called only by the two wrappers) | the only SDK paths that load code into EE memory are dead | none |
| `sceSifLoadModuleBuffer` / `sceSifLoadStartModuleBuffer` | 0 callers | no IRX is loaded from an EE buffer | n/a |
| `sceSifLoadModule` `0x50C4E8` | 15 sites, all in `kwlnInitPS2Systems` (the `0x197030` IRX loader) | loads `cdrom0:\LIB31\*.IRX` on the IOP | IOP code, not EE |

**1b. Why a computed destination cannot land in the code band (inferred).** Over all 14,419 functions, IDA resolved 1,900 code→code-band offset references to function starts, 85 into function bodies and 85 to non-function code (§3a); the read/write data references into the band are exactly two `lq` loads of the libmpeg constant `_maxval` `0x4FDB00` (from `0x4FD974`, `0x4FDA64`). No `lui 0x0010..0x005A` constant is used as a store base. Game buffers come from the MW heap (`SetupHeap(0x9ACC80)` at `0x1001D8`, `sbrk` `0x503860`) and `.bss` pools (`H_Malloc_GetRwMemoryFunctions` `0x1040F0` → `0x7E0A20`; `H_Memcard_Init` → `0x846B80`), all above `0x7CDE80`. A read into the code band would therefore need a pointer-arithmetic bug, not a design feature.

## 2. Cache maintenance [obs]

`_sceFlushCache` `0x5033E0` (syscall 0x64) has **31 call sites**; `iFlushCache` `0x503410` has **0**. Argument semantics per ps2sdk `kernel.h`: 0 = `WRITEBACK_DCACHE`, 1 = `INVALIDATE_DCACHE`, 2 = `INVALIDATE_ICACHE`, 3 = both.

| `$a0` | Sites | Where | Reading |
|---|---|---|---|
| 0 | 28 | `start` `0x1001F0` (crt0); `sub_10CCE0` `0x10CD2C` (`h_sndcom.c`); 18 RenderWare PTank/Sky sites `0x476178–0x485800`; `_sendDataToIPU` `0x50014C`; `_sceMpegCscStoreRefImage` `0x501ED0`; `sceTtyInit` `0x504B14`; `sceSifInitCmd_0` `0x50627C`; `sceSdRemoteInit` `0x5128F4`; and the three paired sites below | data-cache writeback before DMA/SIF — no code involvement |
| 2 | 3 | `InitTLBFunctions` `0x50CCC8`, `InitExecPS2` `0x50D7D8`, `InitAlarm` `0x50DBB8` — each immediately after a `_sceCopy*` into kernel memory and a `FlushCache(0)` | the classic "copy code then invalidate I-cache" signature, **only** in libkernel's kernel-patch installers (§5) |
| 1, 3 | 0 | — | — |

No `sync.l`/`sync.p` + store-to-code pattern exists outside those installers (the `dr_W` census in §1 is empty). Game code never flushes the instruction cache.

## 3. Computed control flow [obs]

Census over all code-band functions (`overlays_census.log` §5): `jr $ra` 13,700; `jr` with IDA switch info 553 (**all 553 jump tables lie in the file-backed data band `0x5A2000–0x7CDE04`**, none in `.bss`); `jalr` 5,136 in 1,957 functions (`$v0` 4,848, `$v1` 177, saved registers 71, others 40); `jr <reg≠$ra>` without switch info **15**.

* The 15 non-switch `jr` are RenderWare tail calls through a global or vtable slot: `lw $v0, RwFree; jr $v0` at `0x45EDC8` (`_rpCollTreeDestroy`), `lw $v0, RwHeapMalloc; jr $v0` `0x4959D0`, `lw $v0, 0x1C($a0); jr $v0` `0x4C9D04` (`RwCameraEndUpdate`), `0x4C9D14`, `0x49923C`, `0x49ACBC`, `0x49ACE4`, `0x4A9A74`, `0x4A9BE8`, `0x4ADC84`, `0x4ADCB8`, `0x4B6EB8`, `0x4C06B8`, `0x4C5FF8`, `0x4CA38C`. **Recompiler rule:** `jr reg` without switch info is an indirect *tail call* through the dispatch table, never a return.
* `jalr` targets are struct/global function pointers set by game code: the census found 331 stores of a function-start constant (`H_Cdvd_InitRtFsPak` `0x101B54–0x101BA8` fills a file-system vtable; `kwlnTaskUpdate` `0x19405C` calls task entries; `btlCameraSetState` `0x2A3A54`) and 2,799 data-band dwords equal to function starts (pointer tables; dense in `0x690000–0x6BFFFF`: 1,674, `0x7B0000–0x7CFFFF`: 766, `0x770000`: 147). The largest dispatchers are battle-UI task functions (`sub_213E80` 147 `jalr`, `sub_263DB0` 86, `sub_2350F0` 79).
* `_xlaunch` `0x50D14C` `jalr $at` with `$at = dword_77F898` is libkernel's thread-launch trampoline (entry stored by `CreateThread`); topic 12 covers it.
* `SetSyscall` (0x74) has 13 call sites, all in libkernel init: `InitTLBFunctions` ×4 (`0x50CCA0`, `0x50CCD4`, `0x50CCE0`, `0x50CD00`), `InitSystemCallTableAddress` ×2 (`0x50D580`, `0x50D58C`), `InitExecPS2` ×3 (`0x50D7B0`, `0x50D7E4`, `0x50D800`), `SetArg` ×1 (`0x50D8CC`), `InitAlarm` ×3 (`0x50DB78`, `0x50DBC4`, `0x50DBE0`). No game code installs syscalls. Semantics → `12_irx_rpc_threads.md`.

### 3a. Reached code that was not in IDA's function list [obs] <a id="missed-callbacks"></a>

85 `li reg, <code-band address>` references point at code-band bytes that are **not function starts**. 71 targets lie outside any function; the rest are IDA constant mis-resolutions (`0x3FFFFF`, `0x400004`, `0x1CC471` odd, `cop2` immediates rendered as `loc_2201BC` etc.) except `0x56F8F8` (`addiu $sp,-0x20` inside `m2v_SetErrFunc`, referenced from `M2V_Setup` `0x574D80` — a merged function boundary; flagged for the lead, not changed). Of the 71, 66 were callbacks stored into packet/panel/vtable slots (e.g. `btlUnitCreatePosRotColPacket` `0x27FED4` stores `0x27FD90` into slot `0x6C`; `itfPnlRegist2` `0x3A8C20..0x3A8C9C` stores `0x3A9230/0x3A93A0/0x3A9400/0x3A9470/0x3A9580`; `sub_4C0FD0` stores six `0x4BF9E0..0x4C0FC0`), four were still `.word` data (`0x45F490`, `0x45F530`, `0x48EA90`, `0x46A0F0` = `addiu $sp,-0xB0` prologue, `0x4A6EB0` = `addiu $sp,-0x140`, 1,900 bytes — Ghidra's data-referenced `FUN_004a6eb0` in `06`), one (`0x4FDB00` `_maxval`) is data. All 70 were created as functions in the copy (`overlays_newfuncs.txt`; sizes 8–1,900 bytes; `0x46A0F0` 320 B, `0x4A6EB0` 1,900 B, `0x3F3280` 332 B, `0x3F9CB0` 376 B, `0x35AA10` 392 B) and are in `symbols/deltas/overlays.sym` as F rows for `import_symbols.py --create-funcs`. **Without them the recompiler would emit no code for 70 reachable callbacks.** The two `.word`-rendered bodies show IDA's "code outside functions" census undercounts: bytes that were never disassembled do not appear in it.

## 4. Code in files [obs]

`extracted/BTL`, `extracted/DATA`, `extracted/BGM`, `extracted/disc/LIB31` — 12,042 files, 4.55 GB — scanned read-only for `7F 45 4C 46`, MIPS prologues (`addiu $sp,$sp,-N`) and `jr $ra` encodings (`overlays_filescan.tsv`).

| Class | Files | Finding |
|---|---|---|
| EE ELF / EE code | **0** | no `.PAC`, `.BIN`, `.FPC`, `.BF`, `.TBL`, `.PAK` file contains an ELF header or a run of MIPS prologues; the 401 `DATA/FIELD/PACK/*.FPC` and all of `BTL/BATTLE/*` are data (`.TBL` tables, `CUTIN`, `EFFECT`, `PANEL`) |
| IOP modules (R3000, IOP side) | 30 `.IRX` under `DATA/IRX_NEW/`, 10 under `DATA/FTP_IRX/` (dev-only FTP/HDD stack), `LIB31/*.IRX` on the disc root; `IOPRP310.IMG` (16 embedded ELFs, 278,353 B) and `DATA/IRX_NEW/IOPRP300.IMG` | IOP code only; loaded by `kwlnInitPS2Systems` via `sceSifLoadModule` and `sceSifRebootIop` (`rom0:UDNL`) — topic 12 |
| False positives | `DATA/SFD/P3CT023.SFD`, `STAFF_ROLL_B.SFD`, `STAFF_ROLL_F.SFD` (100–195 MB video) | 47–62 prologue-like byte patterns in 100+ MB of MPEG data = noise |

GOAL.md's "P3 loads battle/field modules separately" is **not borne out**: battle (`btl*`/`dat*` `0x28DBF0–0x30FC40`) and field (`k_*` `0x199440–0x1D9860`) code is statically linked (`03`); the files that are loaded per battle/field are data (`.PAC`/`.FPC`/`.BF` script bytecode for the `scr*` VM at `0x35AEF0`).

## 5. The data band and the `0x77F710–0x780A08` code cluster [obs unless marked]

Per-16 KiB classification (`overlays_census.log` §6) and VU-nop signature counts (`pass3.log` §4):

| Range | Content | Evidence |
|---|---|---|
| `0x5A2000–0x5CA000` | VU1 microcode | 8,451 upper-NOP (`0x000002FF`) / 7,501 lower-NOP (`0x8000033C`) words; IDA `data`, 36 function pointers (program tables) → topic 14 |
| `0x5CA000–0x5E6000` | strings, `#DirLst#` tables (`0x5E5150+`), pointer tables | `string`/`ptr_other` dominate |
| `0x5E6000–0x690000` | packed game tables; the "orphan code" here (≤ 2.8 KB per 16 KiB bucket, e.g. `0x5FA000–0x60E000`) is IDA mis-decoding table words | 0 xrefs to any orphan item; no VU signatures; same class as `00`'s `syscall 0x400` junk |
| `0x690000–0x6B6000` | string + function-pointer tables (1,674 function starts) | script/menu command tables (inferred) |
| `0x6B6000–0x77A000` | VU1 microcode (181-program band of `14`) | 27,428 upper / 11,212 lower NOP words, 4–12 pointers per bucket = per-program headers |
| `0x77A000–0x77F568` | SDK tables (libgraph `sceGs*` params `0x77F280+`, libipu `0x77F410+`, RW Sky `0x77F010+`) | xrefs from `sceGsGetGParam`, `sceIpuInit`, `SkySystem` |
| **`0x77F568–0x780B48`** | **libkernel kernel-patch payloads and their `SetSyscall` tables (1,908 bytes of code items)** | below |
| `0x780B48–0x7CDE04` | `.sdata`-style globals (gp = `0x7D2CF0`), SDK strings, CRI banners | `data_zero`/`ptr_other`/`string` |

**The cluster is kernel-mode code copied out of the image, not EE user code [obs]:**

| Installer | Copy (`_sceCopy*`, syscall 0x5A) | Then | Table |
|---|---|---|---|
| `InitTLBFunctions` `0x50CC78` | `0x80075000 ← 0x77F568`, `0x330` B (`0x50CCB4–0x50CCBC`) | `FlushCache(0)`, `FlushCache(2)` `0x50CCC0/0x50CCC8`; `SetSyscall` ×4 from `tbl 0x77F8E8` (`(0x5A,0x50CC20)`, `(0x5B,0x80075000)`, `(0x54,0x50D180)`, loop over `0x55..0x59` via `GetEntryAddress`) | `0x77F8E8–0x77F928` |
| `InitExecPS2` `0x50D780` (if `PatchIsNeeded` `0x50D718`) | `0x80074000 ← 0x77FBD8`, `0x7A8` B (`0x50D7B8–0x50D7CC`) | `FlushCache(0/2)` `0x50D7D0/0x50D7D8`; `SetSyscall(0x5A, kCopy_1 0x50D6D0)`, `(0x5B, 0x80074000)`, one `GetEntryAddress` entry (`0x780390`) | `0x780380–0x780398` |
| `InitAlarm` `0x50DB38` (if `T3_MODE 0x10001810` bit 8 clear) | `0x80076000 ← 0x7803A0`, `0x740` B (`0x50DB88–0x50DB94`); `0x82000 ← 0x780AE0`, `0x28` B (`0x50DBA0–0x50DBAC`) | `FlushCache(0/2)` `0x50DBB0/0x50DBB8`; `SetSyscall(0x5A, 0x50DAF0)`, `(0x5B, 0x80076000)`, loop over `0xFC/0xFE/0xFD…` | `0x780B08–0x780B48` |
| `InitSystemCallTableAddress` `0x50D548` | none (scans `0x80000000–0x80080000` with `_sceFindAddress` for `kFindAddress`/`kCopy_0` byte patterns, stores result at `0x77FBB8`) | `SetSyscall(0x83, 0x50D4C0)`, `(0x5A, 0x50D488)` | `0x77FBC0–0x77FBD8` |
| `SetArg` `0x50D880` | `_sceCopy_2` of argv words into kernel arg area at `*0x77F8E0 + 0x40` | `SetSyscall(0x5A, 0x50D840)` (`tbl 0x780398`) | — |

> **Correction 2026-10-18:** `0x10001810` was labelled "INTC_MASK" in this table, in the consequences paragraph below and in "What the runtime must emulate" item 2; on the EE it is **`T3_MODE`** (timer 3 mode register; `INTC_MASK` is `0x1000F010`). `InitAlarm 0x50DB38`: `li $v0, 0x10001810` @`0x50DB44`, `lw $v1, 0($v0)` @`0x50DB54`, `andi $v1, 0x100`, `bnez $v1` @`0x50DB5C` skips the alarm patch when bit 8 is set — agrees with `12` §4.3 and RUNTIME_CONTRACT B-07 (resolved in RUNTIME_CONTRACT §8.2 item 4 / Q-13).

Payload internals confirm kernel linkage: `0x7803A0` = `lui $v0,0x8007; addiu $v1,$v0,0x6710` (absolute kseg0 references), the payload at `0x77FBD8` begins `addiu $sp,-0x20; li $a1,0x26`; the data band holds 42 kseg0 words in `0x77F000–0x780C00`. Ghidra's nine functions (`0x77F710` … `0x780828`, `06` §2.5) all lie inside these three payload ranges (inferred from the ranges above), which is why they have zero references and normal frames. The `0x77F8E0` word is the kernel's syscall-table base found at runtime (`SetArg` reads it).

**Consequences for the recompiler:** do **not** emit `0x77F568–0x780B48` as game functions (they execute at kernel addresses, in kernel mode, after relocation by copy); the kernel HLE must instead provide the semantics of the patched syscalls (`Copy 0x5A`, `GetEntryAddress 0x5B`, `0x54–0x59` TLB functions, alarm `0xFC–0xFE`, `0x83`) — topic 12 owns those semantics. `PatchIsNeeded` and the `T3_MODE` test decide whether the patches run at all; the HLE can simply return "not needed"/"already set" and skip the copies if it implements the syscalls natively.

## 6. Verdict and evidence table

**Static image is complete: YES** (for EE user code).

| Check | Result | Anchor |
|---|---|---|
| Writes into code band | 0 `dr_W`; 2 `dr_R` (constants) | §1 |
| EE loader APIs with callers | 0 (`sceSifLoadElf*`, `LoadExecPS2`, `ExecPS2`, `*ModuleBuffer`) | §1 |
| `FlushCache(2)` outside libkernel installers | 0 of 31 sites | §2 |
| `jr` switch tables in `.bss` | 0 of 553 | §3 |
| EE ELF/code in 12,042 game files | 0 | §4 |
| Code copied out of the image | 3 kernel payloads, 0 user payloads | §5 |
| Code reached but not in IDA's list | 70 functions, now in `overlays.sym` | §3a |

**Residual risks and how `tracediff` catches a miss (inferred):** (a) function-pointer values that come from *files* (e.g. a `.BF` script header carrying an EE address) would make the recompiler's `LOOKUP_FUNC` fail on a target that is in the image but was never carved — the dispatch table must log/trap unknown targets, and the §3a list shows this class exists at ~0.5 % of functions; (b) the 4,848 `jalr $v0` sites are fine as long as every target is a function start — a PCSX2 trace of `jalr` targets compared with `symbols/functions.json` at the first run of each scene is the cheapest completeness check; (c) `jr reg` (15 sites) must be emitted as tail calls (§3).

## What the runtime must emulate

1. `FlushCache(0)` → no-op (host memory is coherent); `FlushCache(2)` → no-op once (c) below holds; `iFlushCache` never called.
2. `Copy`/`SetSyscall`/`GetEntryAddress`/`_sceFindAddress` kernel-patch sequence in `crt_init_runtime` `0x50D658`: either implement the patched syscalls natively and make `PatchIsNeeded` return 0 and `T3_MODE 0x10001810` bit 8 read as set, or let the copies write into an emulated kernel region (`0x80074000–0x80076740`, `0x82000`) that is never fetched as code by the recompiled program. Either way nothing in `0x100000–0x5A1400` changes at runtime.
3. Indirect dispatch (`jalr`/`jr reg`) through the function table only; unknown targets are a hard error with the VA logged.

## Confidence

* §1 reads/copies: **high** (xref census is exhaustive over IDA's resolution; the computed-pointer argument is inferred).
* §2 cache sites: **high** (31 sites, all arguments constant and read).
* §3 control flow: **high** for the census, **medium** for "all `jalr` targets are function starts" (not provable statically).
* §4 files: **high** for ELF magic; **medium** for "no raw EE code" (a heuristic on prologue density; a compressed payload would evade it — no compression format with EE code is known in this title).
* §5 data band: **high** for the kernel-patch cluster; **medium** for the table/VU labelling of `0x5E6000–0x690000` (hand-off to topic 14 for VU ranges).

## Open questions / hand-offs

* Topic 12: semantics of the patched syscalls and the `_xlaunch` trampoline (`0x50D140`); this doc only inventories the EE-side copies.
* Topic 14: confirm the two VU1 bands `0x5A2000–0x5CA000` and `0x6B6000–0x77A000` from the signature counts above.
* Lead: `0x56F8F8` is a function start merged into `m2v_SetErrFunc` (referenced from `M2V_Setup` `0x574D80`); split before Phase 3. Ghidra's data-referenced `FUN_004a6eb0` is now `sub_4A6EB0` (1,900 B) — 06's remaining "code islands" should get the same `.word`-to-function check.

## Blocked

Nothing blocked; the pass took ~80 minutes.
