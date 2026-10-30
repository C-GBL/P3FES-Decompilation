# 06 — Ghidra (EE extension) cross-check of IDA's function boundaries and of the MMI decompiler

_Observed_ = produced by the tools and files cited; _inferred_ = our reading of those observations;
_hypothesis_ = plausible, unverified. Nothing here changes authority: IDA (`symbols/p3fes.sym`) stays
the sole naming/boundary source (ADR-0004, ADR-0006 item 3). Ghidra names are quoted only to locate
things in the Ghidra project.

Tooling (all read-only against the existing headless project `ghidra/p3fes`, `-noanalysis -readOnly`):
`tools/ours/ghidra/ExportFunctions.java` -> `ghidra/functions_ghidra.json`;
`tools/ours/ghidra/diff_functions.py` -> `ghidra/logs/diff_report.md`, `diff.json`;
`tools/ours/ghidra/DecompileList.java` -> `ghidra/decomp/<addr>.c` (targets in `decomp_targets.txt`);
`tools/ours/ghidra/InspectBoundaries.java` and `MnemonicCensus.java` -> `ghidra/logs/inspect_boundaries*.txt`,
`mnemonic_census.txt`. Runner: `tools/ours/ghidra/run_export.ps1`. Scripts compiled on the fly without
incident (no PyGhidra fallback needed). Ghidra 12.1.4, extension `ghidra-emotionengine-reloaded`
(SLEIGH `r5900.slaspec` compiled at import, `ghidra/headless.log` line 13).

Snapshot note. The diff was first run against the 18:22 IDA export (14,040 functions) and re-run
against the 18:43 export (14,225 functions, after the FLIRT pass in `05`; `ghidra/logs/diff_report_14040.md`
keeps the first run). Numbers below are from the 14,225 run unless marked "18:22". The Ghidra side is
identical in both. The 185 functions FLIRT added are 151 stubs of <= 64 bytes (mostly 8-byte
`unknown_libname_*`), 105 of them in `0x500000..0x50ffff` (libkernel); Ghidra has 3 of them, and the other
182 were inspected separately (`inspect_boundaries4.txt`). FLIRT names are quoted only as labels.

## 1. Program metadata (observed, `functions_ghidra.json#program`)

| Field | Ghidra | IDA (00/01) |
|---|---|---|
| Executable SHA-256 | `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc` | same (01) |
| Language / processor | `r5900:LE:32:default` v1.4, `MIPS-R5900` | `r5900l` |
| Compiler spec / compiler | `default` / `unknown` | MW MIPS C 2.4.1 (ELF `.comment`, 00) |
| Image base | `0x100000` | `0x100000` |
| `_mips_gp0_value` | `0x7d2cf0` (import log) | `gp_base` `0x7d2cf0` |
| Functions | 13,406 | 14,225 (14,040 before the FLIRT pass) |
| Instructions / defined data items | 1,187,198 / 65,778 | — |
| Undefined bytes inside `main` block | 2,174,460 | IDA: 19,008 orphan code items, 0x12af0 bytes (00) |
| Total function bytes | 4,637,184 | 4,752,420 (4,738,136 at 18:22) |
| Calling convention assigned | `unknown` on 13,405 of 13,406 (`__stdcall` on 1); signatures are `undefined FUN_x()` | n/a |
| Named functions | 69 (`src: ANALYSIS`) + `entry`: EE-extension kernel labels such as `FlushCache`, `RFU116_SetSyscall`, `_LoadExecPS2`, `sceSifSetDma` | 80 non-auto names at 18:22; 1,424 FLIRT-derived (`05`) at 18:43 |

Memory blocks (observed):

| Block | Range | Bytes | Perms | Init | Type | Source |
|---|---|---|---|---|---|---|
| `main` | `0x100000..0x7cde7f` | 7,134,848 | rwx | yes | default | ELF loader |
| `segment_0.2` | `0x7cde80..0x9acc7f` | 1,961,472 | rw- | yes | default | ELF loader (= IDA `LOAD`/.bss) |
| `registers.io` | `0x10000000..0x1000ffff` | 65,536 | rw- | no | default | language |
| `vu0.code` / `vu0.data` | `0x11000000..0x11000fff` / `0x11004000..0x11004fff` | 4,096 each | rwx / rw- | no | default | language |
| `vu1.code` / `vu1.data` | `0x11008000..0x1100bfff` / `0x1100c000..0x1100ffff` | 16,384 each | rwx / rw- | no | default | language |
| `registers.gs` | `0x12000000..0x12001fff` | 8,192 | rw- | no | default | language |
| `iop_ram` | `0x1c000000..0x1dffffff` | 33,554,432 | rwx | no | default | language |
| `RAM(uncached)` | `0x20000000..0x21e847ff` | 32,000,000 | r-- | no | byte-mapped | language |
| `RAM(uncached_and_accelerated)` | `0x30100000..0x31f847ff` | 32,000,000 | r-- | no | byte-mapped | language |
| `scratchpad` | `0x70000000..0x70003fff` | 16,384 | rw- | no | default | language |
| `BIOS/rom09(cached)` / `BIOS/rom0b(uncached)` | `0x9fc00000..0x9fcfffff` / `0xbfc00000..0xbfcfffff` | 1,048,576 each | r-- | no | byte-mapped | language |
| `.comment`, `.reginfo`, `.shstrtab`, `_elf*` | overlays at `0x0` | 43 / 24 / 64 / 52 / 64 / 280 | --- | yes | overlay | ELF loader |

Import log notes (observed, `ghidra/headless.log` lines 55-60): zero-length PT_LOAD at `0x9acc80` skipped;
`.relmain` skipped (invalid offset `0x8ace9c`); empty `heap` section skipped; and
`Failed to add language defined memory block due to conflict: rom0: start_address=0x1FC00000, uninitialized, length=0x4000000`.

**The `rom0` conflict.** The extension's processor spec declares a 64 MiB `rom0` block at `0x1FC00000`,
which would run to `0x23BFFFFF` and overlap the `RAM(uncached)` mirror at `0x20000000`; Ghidra dropped
`rom0` and kept the mirror (inferred from the block list above: no `rom0`, mirror present; 64 MiB for
a 4 MiB BIOS is presumably a spec typo — hypothesis). Does it matter? No for this binary: a scan of the
`main` section finds **0** `lui` instructions with an upper half in `0x1FC0..0x1FFF` and only 4 literal
words in `0x1FC00000..0x1FFFFFFF`, all in the data band (`0x6afb2c`, `0x6afb6c`, `0x796fcc`, `0x7c01d8`;
observed via a stdlib scan of the ELF). The game reaches the BIOS only through syscalls and through
kseg0 kernel addresses (`0x8007xxxx`, 28,668 words in that range — mostly the SetSyscall patch table and
kernel pointers noted in 01), and the kseg0/kseg1 BIOS mirrors `rom09`/`rom0b` are still mapped. Nothing
in `main` references a dropped address, so no reference or decompilation was affected (inferred).

## 2. Boundary agreement: IDA `symbols/functions.json` vs Ghidra (observed unless marked)

| Metric | Count |
|---|---|
| IDA functions / Ghidra functions | 14,225 / 13,406 (18:22: 14,040 / 13,406) |
| Entries in both | 13,222 (92.9 % of IDA, 98.6 % of Ghidra; 18:22: 13,219 = 94.2 % of IDA) |
| ... agree on entry **and** size | **12,155** (91.9 % of common; 85.4 % of all IDA functions; 18:22: 12,152) |
| ... same entry, different size | 1,067 — IDA larger 1,052, Ghidra larger 15; 857 differ by <= 16 bytes (-4: 617, -8: 127, -12: 76, -16: 24, +8: 11, +16: 2) — identical in both runs |
| IDA-only entries | 1,003: 522 are <= 16 bytes, 82 are `nullsub_*`; 997 lie in Ghidra-undefined space, 6 inside a Ghidra body (18:22: 821, 41,728 bytes, 393 <= 16 B, 95 `nullsub_*`) |
| Ghidra-only entries | 184: 74 inside an IDA function body, 110 in IDA-undefined space (18:22: 187 / 74 / 113, 31,536 bytes) |
| Ghidra functions at/after `0x5a2000` | 9 (2,692 bytes); IDA has 11 there: `sub_77FFA0`, `0x7cc670`, and nine 8-byte FLIRT stubs `unknown_libname_631..639` at `0x77f598..0x7803ec` |
| Ghidra multi-range functions / thunks | 994 / 16 (IDA multi-chunk: 172 per 01; 169 provable from `functions.json` span overrun) |

### 2.1 Where the tools disagree (bands inferred from the `03` module map; counts observed)

| Band | IDA-only | ... Ghidra has no code there | Ghidra-only | ... IDA has no function there |
|---|---|---|---|---|
| `0x100000..0x103da0` crt0 + early SDK stubs | 4 | 4 | 0 | 0 |
| `0x103da0..0x1939d0` `h_*`/`_h_camp_*` | 2 | 2 | 0 | 0 |
| `0x1939d0..0x199440` `kwln*` | 1 | 1 | 0 | 0 |
| `0x199440..0x1e7f90` `k_*` | 2 | 2 | 0 | 0 |
| `0x1e7f90..0x28dbf0` `br_*`/`bp_*`/`sfl_*`/`op_*` | 46 | 46 | 1 | 1 |
| `0x28dbf0..0x30fc40` `btl*`/`dat*` | 76 | 76 | 0 | 0 |
| `0x30fc40..0x35aef0` unattributed | 88 | 88 | 0 | 0 |
| `0x35aef0..0x361350` `scr*` | 4 | 4 | 0 | 0 |
| `0x361350..0x3a2150` `mt_evt*` | 1 | 1 | 0 | 0 |
| `0x3a2150..0x3bdbd0` `itf*`/`fr*` | 38 | 38 | 5 | 0 |
| `0x3bdbd0..0x4176f0` `comu*`/`fcl*` | 20 | 20 | 0 | 0 |
| `0x4176f0..0x46c000` unattributed (`Y_StParts_UpdateStratumPartsTask`) | 10 | 10 | 5 | 5 |
| `0x46c000..0x4e7000` `G3_2D*` renderer (MMI band) | 72 | 72 | 8 | 8 |
| `0x4e7000..0x4f9000` renderer tail | 3 | 3 | 6 | 6 |
| `0x4f9000..0x51d460` SCE SDK libs | 174 (18:22: 33) | 173 | 11 | 11 |
| `0x51d460..0x5a2000` MW runtime + CRI | **452** (18:22: 428) | 447 | **140** | 71 |
| `0x5a2000..0x7cde80` data band | 10 (18:22: 1) | 10 | 8 | 8 |

Reading (inferred): game code written by Atlus (`0x100000..0x46c000`) agrees almost perfectly — the
one-sided entries there are overwhelmingly tiny IDA-only stubs. Disagreement concentrates in the
SDK and compiler-runtime bands `0x4f9000..0x5a2000` (777 of the 1,187 one-sided entries; 592 in the
MW/CRI band alone), where MW/CRI code uses shared epilogues, `j` tail-jumps and function-pointer tables
that the two tools attribute differently, and where the FLIRT pass added 141 stub entries that Ghidra
never created.

### 2.2 Why the sizes differ (observed with `InspectBoundaries.java`, `ghidra/logs/inspect_boundaries*.txt`)

* **Unreachable alignment words (857 cases, delta <= 16).** Every inspected small delta is a
  `0x00000000` word following an unconditional `b`/`j` and its delay slot, e.g. `0x5501fc` in
  `sub_550048` (IDA 496, Ghidra 492), `0x5841cc` in `sub_584190`, the 8 gaps of `sub_4E53E0`
  (`0x4e5cfc`, `0x4e632c`, ... each exactly 4 bytes) and the 18 gaps of `sub_4E6D60`. IDA keeps the
  padding `nop` inside the contiguous body; Ghidra's flow-based body excludes it. This also explains
  most of Ghidra's 994 multi-range functions. Harmless for the recompiler: the words are never executed.
* **Switch dispatch (`jr $v1`/`jr $v0`) ends the Ghidra function (the large deltas).** `sub_3E0C20`
  (IDA 20,184 bytes) is 92 bytes in Ghidra: range `0x3e0c20..0x3e0c5f` ends at `jr v1` and the only
  other range is the epilogue `0x3e5adc..0x3e5af7`; the switch body in between is left as code outside
  any function. Same shape at `0x12f6d0`, `0x3d06d0`, `0x163330`, `0x404750`, `0x2e1500`, `0x4d6b90`
  (`jr v0` four times) and `0x527b48` (`jr t5`). Ghidra's "Decompiler Switch Analysis" (40 s in the
  import log) did not recover these MW jump tables; IDA did. Inferred: IDA's boundary is the correct one,
  and Phase 3 must take jump-table targets from IDA (`jpt_*`) — Ghidra cannot serve as a check there.
* **`j` tail-jumps split differently.** `sub_526238` (IDA 5,588; FLIRT-named `vfprintf` at 18:43, consistent with the varargs reading in 01) ends in Ghidra after
  `j 0x5262b0; addiu sp,sp,0x20` (116 bytes); the target becomes `FUN_005262b0` (5,456 bytes), which is
  also `jal`-called directly from `sub_528920` at `0x528950`. IDA merged both into one function with a
  second entry inside the body. Same pattern: `sub_53AD00` -> `FUN_0053a9b8`/`FUN_0053a5f0`,
  `sub_5A0C00` -> `FUN_005a0cf0`, `sub_52EA30` -> `FUN_0052b548`, `sub_567C58` -> `FUN_00567d28`.
* **Ghidra larger (15 cases).** 11 are +8: Ghidra attaches a shared `jr ra; nop` epilogue that IDA made a
  separate 8-byte function (`sub_549088`/`0x5490d8`, `sub_543160`/`0x543178`, `sub_54D560`/`0x54d588`...).
  `start` is 520 in IDA vs 528 in Ghidra: **IDA's `start` ends at `0x100210`, so the exit path
  `0x100210..0x100217` (`j exit_candidate; move $a0,$v0`, listed in 01) belongs to no IDA function**
  (observed from `p3fes.sym`: `00100008 00000208 F start`, next record `00100218`). `main` 32 vs 48 and
  `sub_1939B0` 16 vs 32 are the same shape (trailing code after the last `jal` dropped by IDA).

### 2.3 The 40 largest size deltas (observed; negative = Ghidra smaller)

| Entry | IDA name | IDA | Ghidra | Delta | Ghidra ranges | Band |
|---|---|---|---|---|---|---|
| `0x3e0c20` | `sub_3E0C20` | 20184 | 92 | -20092 | 2 | comu*/fcl* |
| `0x12f6d0` | `sub_12F6D0` | 5988 | 144 | -5844 | 2 | h_* |
| `0x3d06d0` | `sub_3D06D0` | 5912 | 84 | -5828 | 2 | comu*/fcl* |
| `0x526238` | `sub_526238` | 5588 | 116 | -5472 | 1 | MW/CRI |
| `0x163330` | `sub_163330` | 5612 | 144 | -5468 | 2 | h_* |
| `0x161d90` | `sub_161D90` | 5532 | 128 | -5404 | 2 | h_* |
| `0x404750` | `sub_404750` | 4632 | 88 | -4544 | 2 | comu*/fcl* |
| `0x3d8850` | `sub_3D8850` | 4040 | 104 | -3936 | 2 | comu*/fcl* |
| `0x527b48` | `sub_527B48` | 3216 | 1032 | -2184 | 3 | MW/CRI |
| `0x53ad00` | `sub_53AD00` | 1916 | 108 | -1808 | 2 | MW/CRI |
| `0x2e1500` | `sub_2E1500` | 1776 | 96 | -1680 | 2 | btl*/dat* |
| `0x11e380` | `sub_11E380` | 1696 | 88 | -1608 | 2 | h_* |
| `0x37e460` | `sub_37E460` | 1644 | 140 | -1504 | 2 | mt_evt* |
| `0x154970` | `sub_154970` | 1532 | 120 | -1412 | 2 | h_* |
| `0x371790` | `sub_371790` | 1588 | 256 | -1332 | 2 | mt_evt* |
| `0x5a0c00` | `sub_5A0C00` | 1160 | 80 | -1080 | 1 | MW/CRI |
| `0x37f650` | `sub_37F650` | 1156 | 124 | -1032 | 2 | mt_evt* |
| `0x381c60` | `sub_381C60` | 1152 | 124 | -1028 | 2 | mt_evt* |
| `0x3d9820` | `sub_3D9820` | 1124 | 104 | -1020 | 2 | comu*/fcl* |
| `0x3722d0` | `sub_3722D0` | 1204 | 200 | -1004 | 2 | mt_evt* |
| `0x4d6b90` | `sub_4D6B90` | 3352 | 2360 | -992 | 6 | G3_2D* |
| `0x381540` | `sub_381540` | 1128 | 200 | -928 | 2 | mt_evt* |
| `0x53b8d0` | `sub_53B8D0` | 948 | 40 | -908 | 1 | MW/CRI |
| `0x567c58` | `sub_567C58` | 1084 | 204 | -880 | 2 | MW/CRI |
| `0x4e2b70` | `sub_4E2B70` | 904 | 88 | -816 | 3 | G3_2D* |
| `0x380380` | `sub_380380` | 872 | 124 | -748 | 2 | mt_evt* |
| `0x1345b0` | `sub_1345B0` | 836 | 104 | -732 | 2 | h_* |
| `0x52ea30` | `sub_52EA30` | 716 | 20 | -696 | 1 | MW/CRI |
| `0x375ab0` | `sub_375AB0` | 704 | 100 | -604 | 2 | mt_evt* |
| `0x1281e0` | `sub_1281E0` | 664 | 72 | -592 | 2 | h_* |
| `0x374d30` | `sub_374D30` | 708 | 128 | -580 | 2 | mt_evt* |
| `0x4f2430` | `sub_4F2430` | 728 | 176 | -552 | 4 | renderer tail |
| `0x590ae8` | `sub_590AE8` | 780 | 236 | -544 | 3 | MW/CRI |
| `0x54d080` | `sub_54D080` | 576 | 32 | -544 | 1 | MW/CRI |
| `0x595060` | `sub_595060` | 640 | 140 | -500 | 3 | MW/CRI |
| `0x122710` | `sub_122710` | 556 | 60 | -496 | 2 | h_* |
| `0x5a1518` | `sub_5A1518` | 604 | 116 | -488 | 3 | MW/CRI |
| `0x5a0830` | `sub_5A0830` | 716 | 240 | -476 | 2 | MW/CRI |
| `0x121de0` | `sub_121DE0` | 524 | 60 | -464 | 2 | h_* |
| `0x595110` | `sub_595110` | 504 | 40 | -464 | 1 | MW/CRI |

Pattern (inferred from 2.2): "2 ranges, tiny Ghidra size" = switch dispatch truncation in game code;
"1 range, tiny Ghidra size, MW/CRI band" = `j` tail-jump split. Neither is an IDA error.

### 2.4 One-sided entries, classified by Ghidra references (observed, `inspect_boundaries3.txt`)

IDA-only (821 at 18:22): 408 have **no reference at all** in Ghidra and 407 of those are undefined bytes there
(IDA found them by prologue/alignment scan; e.g. `sub_4A2790` 1,040 bytes, `pds2DObjectSetupA`, `sub_5411B0` —
dead code, inferred); 342 are referenced **only from data** (function-pointer tables, e.g. `sub_27CB40`
from `0x68f078`, `sub_2D86C0`/`sub_2D89E0` from `0x6978fc`/`0x69790c` — Ghidra disassembled them but
created no function); 58 are referenced as a `PARAM` (function pointers passed in registers, e.g.
`sub_100230` 828 bytes from `0x10063c`, `_sceExitThread` `0x100220` from `start`); 13 are reached only
by an unconditional jump. Ghidra created **no** function for any of these; IDA's extra entries are
plausible functions, not noise (inferred). The 182 entries added by the FLIRT pass behave the same
way (`inspect_boundaries4.txt`): 152 have no Ghidra reference, 146 are undefined bytes in Ghidra, 23 are
referenced only from data, 7 as `PARAM`, **0 are called**; 151 are <= 64 bytes. Inferred: signature
matches on library stubs and unreachable library code, which cost nothing to recompile.

Ghidra-only (187 at 18:22, 184 at 18:43): 146 are `jal` targets; 140 are called from inside an IDA function body.
* 54 of those lie **inside an IDA function body** — mid-body entry points reached by `jal` from other
  functions (`FUN_005262b0` in `sub_526238` from `sub_528920`; 39 distinct IDA hosts, most in
  `sub_53B8D0`, `sub_5A0C00`, `sub_54E7D8`, `sub_56DE28`, `sub_582838`, `sub_5830D0`). Total 13,356 bytes.
* 92 lie in IDA gaps. 78 are compatible with being **far tail chunks** of the calling IDA function
  (the caller's `functions.json` span overruns the next entry by at least the callee size; 11,156 far-chunk
  bytes provable overall). **14 were not explained** at 18:22 (7,952 bytes); the FLIRT export gave three
  of them IDA functions (`0x4fd968`, `0x51e150`, `0x522f98`), so **11 remain** and must be checked in IDA:
  `0x4501b0` (2,432 B, `jal` from `sub_44BEB0` at `0x44bf24`), `0x241910` (2,380 B, from `bpRoot_UpdateBattlePanelDrawTask`
  at `0x1fdb90`), `0x4fbf48` (540 B, from `sub_4FC3A8`/`sub_4FC168`), `0x46b8e0` (452 B, from
  `sub_472130`/`sub_472170`/`sub_4721B0`), `0x5244c0` (428 B, from `sub_53AE60`/`sub_53AFD8`/`sub_564BA0`),
  `0x5757b0`, `0x4c5960`, `0x54e888`, and three whose callers (`0x49bcd0`, `0x49bd20`, ...) are themselves
  outside every IDA function: `0x49ee70`, `0x49e830`, `0x4fda58`.
* 14 have **no references** (10,208 bytes): `FUN_004e9aa0` (4,436 B, proper `addiu sp,-0xa0 ... jr ra`
  frame), `0x4ed260`, `0x4ee180`, `0x4ee4b0`, `0x50af18`, and the data-band cluster below.
* 7 are referenced only from data or as `PARAM` (`0x4a6eb0` 1,884 B from `0x4a918c`, `0x4f02e0` 1,684 B,
  `0x46bfb0` 892 B, `0x4967a0` 804 B...). Same class as the 342 IDA-only data-referenced entries, with the
  roles reversed.

### 2.5 Ghidra functions in the data band (`>= 0x5a2000`)

Nine, 2,692 bytes, all in `0x77f710..0x780a08`: `0x77f710` (304), `0x77fdc0` (192), `0x77ffa0` (208, =
IDA `sub_77FFA0`), `0x780070` (484), `0x7803f8` (260), `0x780500` (316), `0x780640` (416), `0x7807e0`
(32), `0x780828` (480). Observed: each has a normal frame (`addiu sp,sp,-0x30/-0xb0 ... jr ra`),
single range, **zero references**, and Ghidra left the rest of the data band undefined (2,174,460
undefined bytes in `main` ~ the 2.27 MiB data band). So these are *not* mis-disassembled VU/GIF packet
data; they are unreferenced, well-formed code inside the data band, and they do not correspond to IDA's
19,008 orphan items (those are scattered `.word` runs, 00). Hypothesis: a position-dependent payload that
crt0 copies into kernel memory — 01 records the SetSyscall patch table at `0x780380` installing
`(0x5B, 0x80074000)`, and `0x780380` sits inside this cluster. The 18:43 FLIRT pass independently matched library signatures at
nine 8-byte spots in the same cluster (`unknown_libname_631..639`, `0x77f598..0x7803ec`), which supports
"library code" without identifying it. To be confirmed in Phase 2 by tracing `sub_50D780`. IDA's third data-band "function" `0x7cc670` is 3 bytes of a string referenced from
`0x69384c` (IDA artefact, as 00 said); Ghidra has data there.

## 3. MMI decompiler test (observed, `ghidra/decomp/*.c`, `ghidra/logs/mnemonic_census.txt`)

All nine targets decompiled (`decompileCompleted`, no errors): `0x4e53e0` 465 ms, `0x46d6f0` 536 ms,
`0x4e6d60` 342 ms, `0x472970` 416 ms, `0x46cd90` 344 ms, `start` 25 ms, `main` 4 ms, `sub_106FF0` 4 ms,
`sub_54F8C8` 16 ms. The only warning, verbatim, in `0x46cd90`, `0x46d6f0`, `0x472970`:
`/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */`. No
`Bad instruction`/`Truncating control flow`/`halt_baddata` markers anywhere.

### 3.1 How the SLEIGH lifts each instruction class (observed, p-code census over the nine bodies)

| Class | Mnemonics seen | Lifting | Decompiler rendering |
|---|---|---|---|
| 128-bit SIMD MMI | `paddw` 15, `pcpyld` 110, `ppacw` 24, `phmadh` 12, `psraw` 3, `pxor` 6, `qfsrv` 6 | **`CALLOTHER` on every one** (1 p-code op per instruction) | typed intrinsic call `_paddw(a,b)` over `undefined1 [16]` values |
| 128-bit load/store | `lq` 101, `sq` 195 | lifted (8 p-code ops each) | 16-byte array deref / four 32-bit stores |
| MMI-class integer multiply | `mult1` 54, `maddu` 70, `mult` 69, `divu` 3 | lifted (5-7 p-code ops) | plain C arithmetic (`iVar26 * 10`, `uVar14 * (uVar17 & 0xff)`) |
| Shift-amount register | `mtsah` 6 | lifted (6 ops) | folded into the following `_qfsrv` operands |
| COP0 / privileged | `mfc0 Status`, `di`, `ei`, `sync 0x10`, `syscall` | `mfc0` lifted; `di`/`ei`/`sync`/`syscall` are `CALLOTHER` | `Status & 0x10000`, `DI()`, `EI()`, `SYNC(0x10)`, `syscall(0x3c)` |
| COP2 / VU0 macro | none in these nine functions | — | **unverified** (3,589 COP2 ops live elsewhere, 01) |

A correction to 01 falls out of this (observed by decoding the raw words in the ELF): the "top MMI
users" `sub_4E53E0` (78) and `sub_4E6D60` (46) contain **no 128-bit SIMD at all** — their opcode-`0x1C`
words are `mult1` (36/18) and `maddu` (42/28), i.e. pipeline-1 integer multiplies in the same opcode
class. The raw census in 01 counts the MMI *opcode class*; the SIMD-heavy functions are `matfxBridgeBumpEnvMap`
(41 `pcpyld`, 8 `ppacw`), `matfxBridgeDualUvTransform`, `matfxBridgeEnvMap`, `sub_54F8C8` (42 SIMD ops). Phase 3's R5900
table must treat `mult1/madd/maddu/div1/mflo1/...` as ordinary 64-bit integer ops, separate from the
SIMD lane.

### 3.2 Excerpts (<= 15 lines each; Ghidra names, IDA names in the heading)

`start` `0x100008` (`ghidra/decomp/00100008.c`) — the `padduw` register clear is eliminated as dead code,
the `sq $zero` loop becomes four 32-bit stores whose upper halves are *unknown inputs*, and `syscall`
keeps its number but, as in Hex-Rays, its arguments are glued onto the next call:

```c
  for (; puVar1 != (undefined4 *)&DAT_009acc80; puVar1 = puVar1 + 4) {
    *puVar1 = in_zero_lo;
    puVar1[1] = in_zero_hi;
    puVar1[2] = in_zero_udw;
    puVar1[3] = in_register_0000000c;
  }
  syscall(0x3c);
  syscall(0x3d);
  FUN_0050d658(0,0,0,0,0,0,0,0,0x9acc80,0xffffffffffffffff,0xa0000,0x95c280,0x100220,0,0,0);
  FlushCache(0);
  EI();
  uVar2 = FUN_00193980(DAT_0095c280,0x95c284);
  FUN_0051f6a0(uVar2);
```

Hex-Rays (04): 29-line `__asm { padduw ... }` block, `__asm { syscall }` twice with the number dropped,
then `crt_init_runtime(10144896, -1, 655360, ...)`. Ghidra is better on the syscall number
(`0x3c`/`0x3d` = SetupThread/SetupHeap) and on `FlushCache`, equally wrong on argument attribution, and
treats the upper 96 bits of `$zero` as unknowns (`in_zero_hi`, `in_zero_udw`), which is a semantic
wart: the loop really stores zeros.

`sub_54F8C8` `0x54f8c8` (42 SIMD ops; Hex-Rays output in 04 is three opaque `__asm` blocks with
`_$A6`/`_$T4` register pseudo-variables):

```c
undefined8 FUN_0054f8c8(undefined1 (*param_1) [16],undefined1 (*param_2) [16],undefined8 param_3)
  ...
    auVar2 = _phmadh(*param_1,*pauVar6);
    auVar4 = _phmadh(param_1[1],pauVar6[1]);
    auVar2 = _paddw(auVar2,auVar4);
    ...
    _pxor(auVar2,auVar2);
    auVar2 = _qfsrv(auVar3,auVar3);
    auVar2 = _paddw(auVar3,auVar2);
    ...
    auVar2 = _psraw(auVar2,0xc);
    *psVar8 = auVar2._0_2_;
    *psVar9 = -1 - auVar2._0_2_;
```

Data flow is intact: the `lq` operands become typed 16-byte array elements, every intrinsic result
feeds the next, and the final `psraw` low half is stored (`auVar2._0_2_`), with the mirrored write
`-1 - x` recovered as C. What is **missing** is semantics: `_phmadh`/`_paddw` are opaque, so nothing
downstream is simplified, and `_pxor(auVar2,auVar2)` + `mtsah` (a zero-then-set-shift-amount idiom) is
rendered as a call whose result is unused.

`matfxBridgeBumpEnvMap` `0x46d6f0` (41 `pcpyld`, 8 `ppacw`; GIF-tag/packet assembly in the `G3_2D*` band):

```c
  auVar108._8_8_ = 0;
  auVar108._0_8_ = uVar40;
  auVar62._8_8_ = in_a0_udw;
  auVar62._0_8_ = 0x1000002b;
  auVar94 = _pcpyld(auVar108 << 0x40,auVar62);
  ...
  *DAT_007ce9f4 = auVar94._0_4_;
  puVar2[1] = auVar94._4_4_;
  puVar2[2] = auVar94._8_4_;
  puVar2[3] = auVar94._12_4_;
  auVar95 = _ppacw(auVar20 << 0x40,auVar21 << 0x40);
```

Readable as "build a 128-bit quadword from two 64-bit halves and `sq` it to the packet cursor
`DAT_007ce9f4`", but note `in_a0_udw`: the upper 64 bits of `$a0` at entry leak in as an undefined
input because `pcpyld` only uses the low halves and the lifter does not know that.

`matfxBridgeEnvMap` `0x46cd90`, COP0 idiom (also in `0x46d6f0`, `0x472970`):

```c
  do {
    DI();
    SYNC(0x10);
  } while ((Status & 0x10000) != 0);
  ...
  EI();
```

The EE `di; sync.p; mfc0 Status; ext bit 16 (EDI); loop` interrupt-disable idiom becomes legible C;
Hex-Rays renders `_ei()`/`_sync()` but leaves `mfc0` in `__asm` (04).

`sub_4E53E0` `0x4e53e0` (`mult1`/`maddu` user, 762 lines, 0 intrinsics, 0 128-bit temporaries):

```c
      iVar15 = iVar25 + iVar26 * 10;
      ...
                    iVar26 = ((int)(uVar4 & 0x7c00) >> 7) * iVar25;
                    uVar20 = (uVar4 & 0x1f) * 8 * iVar25;
                    *puVar10 = (short)(((uVar20 | (int)uVar20 >> 0x1f) + uVar14 * (uVar17 & 0xff) &
```

Pipeline-1 multiplies are indistinguishable from pipeline-0 ones in the output — correct, since the
result registers are what matter (inferred: RGB5A1 texel expansion, from the `0x7c00`/`0x1f` masks).

`sub_106FF0` `0x106ff0` (plain-integer leaf, the 04 control):

```c
bool FUN_00106ff0(short param_1)
{
  return *(short *)(&DAT_007e2680 + param_1 * 0x670) == 3;
}
```

Identical to Hex-Rays' `*(__int16 *)&byte_7E2680[1648 * a1] == 3` (0x670 = 1648).

`main` `0x193980`: `FUN_005225a8(&gp0xffff93f8); FUN_001939b0(0);` — the `$gp-0x6C08` string pointer
(`"jpx235\n"` at `0x7cc0e8`, 01) is **not** resolved despite `_mips_gp0_value=0x7d2cf0` being known at
import; Hex-Rays showed `$gp - 0x6C08` likewise. Neither decompiler resolves gp-relative data here.

### 3.3 Comparison with Hex-Rays (04) — summary

| Aspect | Hex-Rays `hexmips` (04) | Ghidra + EE extension (this doc) |
|---|---|---|
| 128-bit SIMD MMI | opaque `__asm` block; data flow broken (`_$A6`) | opaque **intrinsic** `_paddw(a,b)`; data flow intact, no semantics |
| `lq`/`sq` | `__asm` | lifted to typed 16-byte loads/stores |
| `mult1`/`maddu`/`div1` | not tested in 04 | lifted to plain arithmetic |
| `syscall` | `__asm { syscall }`, number dropped | `syscall(0x3c)`, number kept; args still misattributed |
| COP0 (`mfc0 Status`, `di`, `ei`, `sync`) | `_ei()`, `_sync()`, `mfc0` in `__asm` | `DI()`, `EI()`, `SYNC(0x10)`, `Status` variable |
| `padduw $r,$zero,$zero` clears | 29-line `__asm` | eliminated as dead stores (silently) |
| Upper 64 bits of GPRs | `_$Rn` pseudo-registers | `in_a0_udw`-style undefined inputs leak into output |
| COP2 / VU0 macro | untested | untested (no COP2 in the nine targets) — **open** |
| Plain integer leaf | clean | clean, identical |

## 4. Verdicts

**(a) Is IDA's boundary set safe for the recompiler (ADR-0004)?** Yes, with named exceptions. Ghidra
independently confirms 13,222 of 14,225 IDA entries (92.9 %; 94.2 % of the pre-FLIRT 14,040) and the
exact size of 12,155; every
inspected size disagreement is either an unreachable `nop` after `b`/`j` (857 cases, harmless), a
switch body that Ghidra failed to recover and IDA did (`sub_3E0C20` and the whole table in 2.3 —
IDA is right, and Phase 3 must consume IDA's jump tables because Ghidra offers no check there), or a
`j` tail-jump that IDA merged and Ghidra split (`sub_526238`/`0x5262b0`). The 1,003 IDA-only entries
are real code Ghidra never reached (at 18:22: 408 unreferenced, 342 reached only via data tables, 58 via
function pointers; the 182 FLIRT additions: 152 unreferenced, 0 called) and cost nothing to recompile.
Phase 3 **must double-check**: (1) the 54 mid-body
`jal` targets (2.4; e.g. `0x5262b0` inside `sub_526238`, called from `0x528950`) — a one-C++-function-per-
IDA-function emitter needs mid-body entry support or a split, otherwise those calls land nowhere;
(2) the 11 called addresses still without an IDA function (`0x4501b0`, `0x241910`, `0x4fbf48`, `0x46b8e0`,
`0x5244c0`, `0x5757b0`, `0x4c5960`, `0x54e888`, `0x49ee70`, `0x49e830`, `0x4fda58`) — open each in IDA;
if IDA has them as tails or nothing, the recompiler would emit no code for roughly 7.5 KiB that is
demonstrably called; (3) the exit path `0x100210..0x100217`
outside `start` and the trailing instructions after `main`'s last `jal` (2.2) — recompile by
instruction stream over the whole `main` block, not only inside IDA bodies, or extend those bodies;
(4) use IDA `Chunks()` for bodies — `functions.json` carries only the chunk sum, so `[a, a+s)` is wrong
for the 169-172 multi-chunk functions (11,156 far-chunk bytes) and would silently misattribute code;
(5) the unreferenced code islands (`FUN_004e9aa0` 4,436 B; the `0x77f710..0x780a08` cluster) — decide
whether they are dead or copied elsewhere (`0x80074000` hypothesis, 2.5) before dropping them.

**(b) Does the EE extension's decompiler earn its "second opinion" role for MMI code (ADR-0006 item 3)?**
Partly, and only as a reading aid. For 128-bit SIMD it is a genuine improvement over Hex-Rays — the
`__asm` wall becomes typed intrinsics with intact data flow (`sub_54F8C8`: `_phmadh` -> `_paddw` ->
`_qfsrv` -> `_psraw` -> 16-bit store), `lq`/`sq`, `mtsah`, COP0 idioms and the pipeline-1 multiplies are
lifted to real C, and `syscall` keeps its number — so a Phase 5 analyst can see *what flows where*
in `G3_2D*` packet builders (`matfxBridgeBumpEnvMap`) without reading raw MIPS. It is **not** a semantic oracle:
every SIMD op is `CALLOTHER`, so Ghidra cannot simplify or verify a single SIMD computation, it emits
undefined upper-half inputs (`in_a0_udw`, `in_zero_hi`) that would be wrong if read literally, it
silently drops the `padduw` clears, it misattributes `syscall` arguments exactly like Hex-Rays, it does
not resolve `$gp`-relative data, and its function boundaries are worse than IDA's wherever a MW switch
or tail-jump appears. COP2/VU0 macro-mode rendering is **unverified** — none of the nine targets
contains a COP2 op; that test (e.g. a function from the 3,589-op COP2 census) is the next thing to run
before relying on Ghidra for VU0 code. ADR-0004 and ADR-0006 stand as written: recompile from IDA's
instruction stream, read Ghidra for data flow, copy nothing back.
