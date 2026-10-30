# 07 — Community symbol hints: provenance, boundary comparison, coverage (ADR-0009)

_Written 2026-10-18. Implements ADR-0009 on a **copy** of the master database (`ida/work_hints.i64`, gitignored);
the master `ida/p3fes.i64` was not opened. Legend: **[obs]** observed in a file or IDA API result on this machine ·
**[der]** derived by our scripts from observed data · **[inf]** inference. Everything from the unlicensed sources
stays in gitignored files (`symbols/hints/`, `symbols/p3fes.hints.sym`, `ida/logs/hints_*`); this page quotes a
handful of names as examples only._

Tools: `tools/ours/ida/hints_convert.py` (conversion + boundary comparison, plain CPython `-I`),
`tools/ours/ida/hints_import.py` (apply as hints), `import_symbols.py` (owner of the hint/promotion semantics),
`export_symbols.py` (withholds unverified hint names from every committed output). See `tools/ours/ida/README.md`.

## 1. Provenance [obs]

| Source | Origin / commit | License | Content read | Rows total | Descriptive kept | Dropped | Hint file |
|---|---|---|---|---|---|---|---|
| `snaku` | `snaku/Persona3-FES-Decompilation` `main` @ `59d284ee21fe166bd46252e38e1a08874c4a1a66`, `config/SLUS_216.21/symbol_addrs.txt` | **none** (all rights reserved) -> hints only (§1 of ADR-0009) | 14,702 splat symbols: 14,567 `type:func`, 135 untyped data; 1 `size:` | 14,702 | **3,025** (F 2,899 + D 126) | 11,677 placeholders | `symbols/hints/snaku.sym` |
| `tge-pr4` | same repo, unmerged PR #4 (`tge-was-taken`), local branch `pr4` @ `c45ffa45d517582148b474631f1d1772d8b160ff` (fetched earlier; no network needed) | **none** -> hints only | 16,004 symbols: 14,708 `type:func`, 1,296 untyped data; 1 `size:` | 16,004 | **8,500** (F 7,422 + D 1,078; 207 second-name-at-same-address rows dropped) | 7,297 placeholders | `symbols/hints/tge-pr4.sym` |
| `fes-pc-recomp` | `Virtual-AK/fes-pc-recomp` @ `6b3a905a1e44a994c94682582d2c04cbf10c7c4e`, `docs/formats.md`, `docs/script-functions.md`, `tools/p3fes_bf.py` | **MIT** -> promotable (§2a), attributed in `symbols/README.md` | prose findings; curated into table `FES_PC_RECOMP` with `cite=file:line` | 27 | 27 (F 21, D 5, L 1) | 0 | `symbols/hints/fes-pc-recomp.sym` |

ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc` is recorded in every hint header;
snaku's `checksum.sha1` equals our ELF (`docs/COMMUNITY.md`). `p3fes-recompiled` (GPL-3, different ELF) was not used.

Placeholder rule [der]: `func_X`, `D_X`, `jpt_`, `lbl_`, `jtbl_`, and any name whose trailing hex token is its own
address (`h_cdvd_00101100`, `libadxe_adx_dcd_0043976x`, `gUnk_007cad7c`, `sNextId_7CC530`). This is slightly stricter
than the counts in `docs/COMMUNITY.md` (3,060 / 8,776), which kept address-suffixed descriptive stems.
Hint line format: `<addr8> <size8> <F|D|L> <name> source=<src> [module=<splat module>] [cite=<file:line>] [# note]`.
fes-pc-recomp names the project itself uses (`cvFsAddDev`, `cvFsOpen`, `cvFsReqRd`) are verbatim; roles we labelled
from its prose carry the project's `_candidate` suffix (e.g. `vblankStartHandler_candidate` at `0x4D47F0`).

## 2. Boundary comparison — third opinion on function starts [der]

Compared every community `type:func` start (placeholders included: their addresses are boundary facts even if their
names are not) with `symbols/functions.json` as committed at run time (**14,225** IDA functions, post-FLIRT export;
the pre-FLIRT baseline had 14,040). Splat carries one explicit `size:` per file, so community sizes are **derived**
as `next community start - start`; a derived size within <16 bytes of IDA's total chunk size counts as consistent
(alignment padding). Full tables: `ida/logs/hints_boundary.md`.

| Metric | snaku | tge-pr4 |
|---|---|---|
| community `type:func` starts (distinct) | 14,564 | 14,678 |
| same start address as an IDA function | **13,964** | **14,071** |
| same start, consistent size | 13,581 | 13,711 |
| same start, different size | 383 | 359 |
| ... IDA function longer (spans past the next community start: merge/split disagreement) | 295 | 302 |
| ... community gap longer by >=16 B (IDA ends earlier: IDA split, or unreached code/data in between) | 88 | 57 |
| community-only starts (no IDA function there) | 600 | 607 |
| IDA-only starts (no community function there) | 261 | 154 |

Disagreements by band (`docs/ANALYSIS/03_strings_of_interest.md` source-file bands; `tge-pr4` figures, snaku in parentheses where different):

| Band | community-only | IDA-only |
|---|---|---|
| crt0 / h_cursor / h_cdvd (pre-band) | 8 (7) | 0 |
| h_* camp/memory/fade/Sofdec/sound | 50 | 0 (1) |
| kwln* task kernel | 2 | 0 |
| k_* field/dungeon | 4 | 0 |
| br_/bp_/sfl_/gc_/op_ battle UI, shuffle, title | 16 | 0 |
| btl*/dat* battle core | 45 | 0 (2) |
| mt_evt*/mt_scene*/itf*/fr* event+UI | 10 | 0 |
| comu*/nm*/fcl* social, fusion, shops | 17 | 0 |
| 0x470E10..0x4F9168 engine/RenderWare (inferred) | 98 (94) | 8 (22) |
| SCE SDK libs (libgraph..libdbc) | 16 | 3 (11) |
| 0x51D460..0x5A0000 CRI/libc/other libs (inferred) | 261 (259) | 132 (213) |
| data (.data/.rodata/.bss, VU1 microcode) | 19 | 10 (11) |
| other game code (between bands) | 61 | 1 |

[inf] Game code agrees almost completely; the disagreement mass sits in the CRI/libc/RenderWare library region,
where IDA's auto-analysis and splat's hand-placed starts differ (library jump tables, `ee-gcc` padding, unreached
helpers). The 302 "IDA longer" cases are the ones that matter for the recompiler (a merged function hides a second
entry point) and belong on the Phase 3 boundary review list.

### 30 largest size deltas (tge-pr4 derived size vs IDA total chunk size) [der]

| Address | IDA name | IDA size | community size | delta |
|---|---|---|---|---|
| `0x43CA30` | `Y_StParts_UpdateStratumPartsTask` | 0xb09c | 0x8000 | 0x309c |
| `0x303130` | `sub_303130` | 0x2840 | 0x300 | 0x2540 |
| `0x526238` | `vfprintf` | 0x15d4 | 0x78 | 0x155c |
| `0x3407E0` | `sub_3407E0` | 0x13b8 | 0xc48 | 0x770 |
| `0x53AD00` | `sub_53AD00` | 0x77c | 0x70 | 0x70c |
| `0x52AFE8` | `__ieee754_asinf` | 0x398 | 0x818 | 0x480 |
| `0x53C2A0` | `sub_53C2A0` | 0x47c | 0x50 | 0x42c |
| `0x5A0C00` | `sub_5A0C00` | 0x488 | 0xa0 | 0x3e8 |
| `0x581BB0` | `sub_581BB0` | 0x54 | 0x3e0 | 0x38c |
| `0x53B8D0` | `sub_53B8D0` | 0x3b4 | 0xb0 | 0x304 |
| `0x5016C8` | `_dispRefImageField` | 0x420 | 0x168 | 0x2b8 |
| `0x52EA30` | `logf` | 0x2cc | 0x18 | 0x2b4 |
| `0x552BD0` | `sub_552BD0` | 0x134 | 0x3d0 | 0x29c |
| `0x566C20` | `sub_566C20` | 0x94 | 0x310 | 0x27c |
| `0x553310` | `sub_553310` | 0x44 | 0x2c0 | 0x27c |
| `0x54D080` | `valloc` | 0x240 | 0x20 | 0x220 |
| `0x581350` | `sub_581350` | 0xa4 | 0x280 | 0x1dc |
| `0x595110` | `sub_595110` | 0x1f8 | 0x28 | 0x1d0 |
| `0x595060` | `sub_595060` | 0x280 | 0xb0 | 0x1d0 |
| `0x52EA18` | `atan2f` | 0x1dc | 0x18 | 0x1c4 |
| `0x5611E0` | `sub_5611E0` | 0x48 | 0x200 | 0x1b8 |
| `0x59F3D8` | `sub_59F3D8` | 0x13c | 0x2f0 | 0x1b4 |
| `0x5613E0` | `sub_5613E0` | 0x44 | 0x1d0 | 0x18c |
| `0x5535D0` | `sub_5535D0` | 0x84 | 0x210 | 0x18c |
| `0x583CE8` | `sub_583CE8` | 0x6c | 0x1e8 | 0x17c |
| `0x5824B0` | `sub_5824B0` | 0xa4 | 0x220 | 0x17c |
| `0x59EE18` | `sub_59EE18` | 0x20 | 0x178 | 0x158 |
| `0x54F730` | `sub_54F730` | 0x70 | 0x198 | 0x128 |
| `0x242320` | `sub_242320` | 0x218 | 0xf0 | 0x128 |
| `0x575AA0` | `sub_575AA0` | 0xa8 | 0x1c8 | 0x120 |

[inf] `0x43CA30` (IDA 0xB09C bytes, community 0x8000): IDA has merged a very large function; splat places a start
inside it. `vfprintf`/`logf`/`valloc`/`atan2f` (FLIRT names) where IDA is *longer*: either FLIRT matched a prefix and
IDA ran on into following library functions, or splat split these — each needs a look at the actual `jr $ra`. The
"community longer" cases at `0x52AFE8`, `0x581BB0`, `0x566C20` are IDA ending early (unreached tail code or a
jump-table region) — candidates for `create_funcs`/boundary fixes. Not verified beyond the numbers.

## 3. Applying the hints to the copy [obs]

Snapshot: `copy ida\p3fes.i64 ida\work_hints.i64` taken 2026-10-18 18:50 (the master already carried the FLIRT
pass: 14,225 functions, 1,192 descriptive names, 528 `sce*`). Command:
`hints_import.py ida\work_hints.i64 --root .` with the default priority `fes-pc-recomp,tge-pr4,snaku`.
Rules: name set only where IDA had an auto name (`sub_*`, `nullsub_*`, IDA `j_*` thunk names); ours and FLIRT's names
win (`conflict`); every hint leaves a repeatable comment `HINT[<source>] <name>` (`agrees` when the name was already
there); no functions created, no data items split.

| Source | named | same (name already present) | alternate (lower-priority, different) | conflict | no_func | mid_item |
|---|---|---|---|---|---|---|
| fes-pc-recomp | 23 (17 F + 6 D/L) | 0 | 0 | 4 | 0 | 0 |
| tge-pr4 | 6,440 (5,953 F + 487 D/L) | 836 | 16 | 288 | 344 | 576 |
| snaku | 0 (tge-pr4 covers every snaku address first) | 2,638 | 95 | 94 | 103 | 95 |

* `same` for tge-pr4 = **836 functions where TGE's name equals the FLIRT name** — independent agreement between the
  signature pass and the decomp, recorded as `HINT[tge-pr4] <name> agrees`.
* `no_func` (344): community function starts with no IDA function at that address — the same set as the
  "community-only" rows in §2; comment only.
* `mid_item` (576 + 95): data hints at addresses inside an existing IDA item (e.g. `0x7CAD1C` lies inside a
  1,124-byte item at `0x7CAD00`; `0x5C9F30` inside the item at `0x5C977C`). Applying them needs the item split first.
* The copy is saved (`ida/work_hints.i64`); `symbols/p3fes.hints.sym` (gitignored, 11,552 rows) lists every hint with
  `applied=<status>`; `ida/logs/hints_coverage.json` holds the counters below.

### Coverage headline

| | pre-FLIRT committed baseline (`p3fes.sym` 18:22) | master snapshot after FLIRT (copy, 18:50) | after hints (copy) |
|---|---|---|---|
| functions | 14,040 | 14,225 | 14,225 |
| with a descriptive (non-auto) name | 80 | 1,192 | **7,160** |
| `sce*` (`^_?i?(sce\|Sce\|SCE)`) | 75 | 528 | 535 |
| `rw*` (`^_?(Rw\|Rp\|Rt\|rw\|rp\|rt\|RW\|RP\|RT)`) | 0 | 0 | **658** |
| `cri*` (`^_?(cri\|CRI\|ADX\|adx\|AIX\|AHX\|cv[A-Z]\|ROFS\|rofs\|mw[A-Z]\|sj[A-Z]\|SJ\|srd\|SRD\|DVCI\|HTCI\|svm\|SFD\|mpeg\|...)`) | 0 | 0 | **1,500** |
| named data items / labels | 3 D | 8 D + 519 L | + 521 (487 tge-pr4, 28 snaku, 6 fes-pc-recomp) |

Gain of 5,968 function names: 5,950 tge-pr4, 17 fes-pc-recomp, 1 IDA thunk auto-renamed to `j_<hint>`.
[inf] FLIRT already covered the Sony SDK (`sce*` +7 only); the hints' value is RenderWare (+658) and CRI (+1,500)
plus ~2,100 Atlus game functions.

By band (functions / descriptive before -> after / gained from fes-pc-recomp / from tge-pr4):

| Band | functions | before | after | fes-pc-recomp | tge-pr4 |
|---|---|---|---|---|---|
| crt0 / h_cursor / h_cdvd (pre-band) | 66 | 3 | 59 | 3 | 53 |
| h_* camp/memory/fade/Sofdec/sound | 1,014 | 0 | 396 | 0 | 396 |
| kwln* task kernel | 68 | 1 | 55 | 0 | 54 |
| k_* field/dungeon | 659 | 0 | 264 | 0 | 264 |
| br_/bp_/sfl_/gc_/op_ battle UI, shuffle, title | 1,217 | 0 | 73 | 0 | 73 |
| btl*/dat* battle core | 1,446 | 0 | 192 | 0 | 192 |
| scr* BF script VM | 85 | 0 | 71 | 0 | 71 |
| mt_evt*/mt_scene*/itf*/fr* event+UI | 907 | 0 | 134 | 0 | 134 |
| comu*/nm*/fcl* social, fusion, shops | 910 | 0 | 51 | 0 | 51 |
| G3_2D*_Node renderer | 8 | 0 | 8 | 0 | 8 |
| 0x470E10..0x4F9168 engine/RenderWare (inferred) | 1,343 | 18 | 937 | 6 | 912 |
| SCE SDK libs (libgraph..libdbc) | 797 | 753 | 792 | 0 | 39 |
| 0x51D460..0x5A0000 CRI/libc/other libs (inferred) | 3,693 | 414 | 3,379 | 6 | 2,959 |
| data (.data/.rodata/.bss, VU1 microcode) | 62 | 2 | 50 | 0 | 48 |
| other game code (between bands) | 1,950 | 1 | 699 | 2 | 696 |

[inf] Battle UI (`br_/bp_`, 73 of 1,217) and social/fusion (51 of 910) stay mostly unnamed even in PR #4 — those
remain Phase 5 hand-decompile work; the library bands are now almost fully labelled.

### Conflicts (existing non-auto name != hint) [obs/der]

386 rows at 300 distinct addresses (`ida/logs/hints_conflicts.tsv`), categorised by `hints_import` output:

| Category | Rows | Examples |
|---|---|---|
| genuinely different names (FLIRT vs community) | 251 | `0x100220` `_sceExitThread` (ours, syscall wrapper) vs `_root`; `0x48A3D0` `name__C9type_info` (FLIRT) vs `RpSkinGetNumBones` |
| same identity, different spelling | 126 | `0x100008` `start` vs `_start`; `0x4F9158` `_sce_GetGsDxDyOffset` vs `_GetGsDxDyOffset`; `0x502E40` `_sceAddIntcHandler` vs `AddIntcHandler` |
| one name contains the other | 4 | `0x5035F0` `VSync` (FLIRT) vs `vsyncPollWait0_candidate` (fes-pc-recomp); `0x51F6A0` `exit_candidate` vs `exit` |
| FLIRT `unknown_libname_N` vs a community name | 3 | `0x782600` `unknown_libname_351` vs `sceCd_rcmdrdata` |
| our analyst name vs community name | 2 | `0x1984C0` `main_loop_candidate` vs `kwlnMain` (both sources) — supports our inference |

The four fes-pc-recomp conflicts are all agreements in substance with FLIRT names: `0x4F94E0` `sceGsPutDispEnv` vs
`gsSetDisplayEnv_candidate`, `0x4F9938` `sceGsSyncV` vs `gsSyncVWait_candidate`, `0x5035F0`/`0x503680`
`VSync`/`VSync2` vs the polling-wait candidates. [inf] The 251 "genuinely different" rows are a ready-made QA list
for the FLIRT pass (a C++ RTTI name on a RenderWare skin function is unlikely to be right).

## 4. Round trip and leak check [obs]

* `export_symbols.py ida\work_hints.i64 <scratch root> --no-save` on the hinted copy: 17 F + 6 D/L rows exported with
  `source=fes-pc-recomp`; **6,454 unverified hint names withheld** (written as `sub_<ADDR>`; `ida/logs/export_hints_withheld.txt`).
  Scripted check: 0 hint-placed snaku/tge-pr4 names in the scratch `p3fes.sym`, `functions.json`, or any generated
  `docs/ANALYSIS/0x_*.md` block (listings/decompiler text are filtered at `write_doc`).
* `import_symbols.py ida\work_hints.i64 <scratch>\symbols\p3fes.sym --no-save`: `names_failed: 0`, `hints_same: 23`.
* `roundtrip_test.py` on the copy: `_sceExitThread`, `_sce_GetGsDxDyOffset`, `main` deleted and restored — `ROUNDTRIP OK`.
* Promotion probe (closed without save): applying `00100230 ... F H_Cursor_UpdateDrawTask source=tge-pr4 verified=yes`
  upgraded the comment to `HINT[tge-pr4] H_Cursor_UpdateDrawTask verified` (`hints_promoted: 1`); the exporter then
  treats the name as exportable with `source=tge-pr4`.

**Promotion workflow (implemented):** verify the function in IDA, write the evidence in `docs/ANALYSIS/`, then make the
one-line edit in `symbols/p3fes.hints.sym` (or the source hint file): append ` verified=yes` to that row and re-run
`import_symbols.py ida\p3fes.i64 symbols\p3fes.hints.sym`. Alternatively add `<addr> <name>` to
`tools/ours/ida/names_manual.txt` — the exporter treats manual-named addresses as verified too.

## 5. Applying to the master (after the FLIRT pass is saved and nothing holds `ida/p3fes.i64`)

```powershell
$PY = "C:\Users\Ash\.local\share\rea\ida-mcp\Scripts\python.exe"
# 1. regenerate hint files from the pinned commits (plain CPython, -I because the inputs are untrusted)
& C:\Python314\python.exe -I tools\ours\ida\hints_convert.py --root . --snaku tools\third_party\_community-eval\snaku --pr4-rev pr4 --fes-pc-recomp tools\third_party\_community-eval\fes-pc-recomp --compare symbols\functions.json
# 2. dry run: read ida\logs\hints_conflicts.tsv and ida\logs\hints_coverage.json
& $PY tools\ours\ida\hints_import.py ida\p3fes.i64 --root . --dry-run
# 3. apply (saves the master), then re-export; committed outputs gain only `source=fes-pc-recomp` rows
& $PY tools\ours\ida\hints_import.py ida\p3fes.i64 --root .
& $PY tools\ours\ida\export_symbols.py ida\p3fes.i64 . --apply-names tools\ours\ida\names_manual.txt
git diff --stat symbols docs      # expect 23 new source=fes-pc-recomp rows; ida\logs\export_hints_withheld.txt ~6.4k rows
```

## 6. Open decisions for the lead

1. **Priority order.** `fes-pc-recomp` first means its `_candidate` role names win the IDA display at 17 functions
   where TGE has the original Atlus name (e.g. `0x100D80` `fileRequestGet_candidate` vs `H_Cdvd_Request`). Swap to
   `--sources tge-pr4,snaku,fes-pc-recomp` if IDA readability matters more than having the committable name in place.
2. **`unknown_libname_N`.** Treated as FLIRT's (wins). Only 3 conflicts in this snapshot, but earlier FLIRT states had
   201 such names; a flag to let hints replace them is a one-line change in `import_symbols.has_user_name_at`.
3. **`mid_item` data hints (671).** Need `del_items` before naming; not done because it changes item layout.
4. **Boundary follow-up.** 302 "IDA longer" and 344 `no_func` starts from PR #4 are candidates for the `create_funcs`
   pass (`tools/ours/ida/create_funcs.py`, other owner) before the recompiler freezes boundaries.
5. **FLIRT QA.** 251 hard disagreements between FLIRT names and community names (§3) — decide whether community
   agreement/disagreement should feed `05_flirt.md`'s spot checks.
