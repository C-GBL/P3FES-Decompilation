# 08 - Instruction census (Phase 3 recompiler input)

_Written 2026-10-18 from `ida/work_phase3prep.i64` (a byte-identical copy of `ida/p3fes.i64`, opened read-only) by
`tools/ours/ida/insn_census.py` and `tools/ours/ida/export_jumptables.py`. Machine output: `symbols/insn_census.json`,
`symbols/jumptables.json`. Logs: `ida/logs/phase3prep_*.log`. **Observed** = counted from the database / listing;
**inferred** = our reading of those counts. The decoder decision this feeds is `docs/DECODER.md` (draft ADR-0011)._

> **Correction (2026-10-18, after `recomp/` implemented the decoder):** the distinct base-mnemonic count is **198** (per `symbols/insn_census.json#units`), not 199 as stated below; the oracle run over all function words also surfaced two rabbitizer gaps (`sqrt.s` rendered as raw `c1`; 3-operand `multu` rejected) — see `docs/DECODER.md` "Corrections after implementation".

## 1. Headline (observed)

* **14,420 IDA functions**, walked chunk by chunk (`idautils.Chunks`; 173 are multi-chunk), contain **1,194,277
  instruction words** (4,777,108 bytes). Every word decodes with our R5900 table — **0 invalid words**.
* IDA presents the same bytes as **1,177,887 items**: 16,389 words are hidden inside macro items (`li` 12,713 x 8 B,
  `lw`/`lhu`/`lwc1`/`ld`... fused with their `lui` at 8-12 B, `uld`/`usd`/`ulw`/`usw` = `ldl+ldr` etc., `dli` 24 B,
  `li.s` = `lui+mtc1`). One function (`sub_46BFB0`, `0x46bfb0..0x46c330`) has one word that no IDA item covers
  (224 words vs 223 items+macro words); cause not investigated.
* Per unit (words, share): integer core 821,769 (68.8%), COP1 FPU 130,315 (10.9%), branches 101,291 (8.5%,
  incl. 201 `bc0f`), jumps 87,776 (`jal` 66,580, `jr` 14,295, `jalr` 5,143, `j` 1,758), **MMI 44,438 (3.7%)**,
  likely branches 2,374 (0.2%), **COP2 VU0 macro 2,960**, COP2 transfers 1,954 (`lqc2` 662, `sqc2` 618, `qmtc2` 481,
  `qmfc2` 93, `ctc2` 83, `cfc2` 17), COP0 1,049 (`sync` 733 = `sync.p` 380 + `sync.l` 353, `mfc0` 110, `ei` 92,
  `di` 75, `cache` 17, `mtc0` 16, `eret` 6), traps 351 (`break` 183, `syscall` 168).
* Of the 44,438 MMI words, **42,231 are `lq`/`sq`** (128-bit load/store); only 2,207 words are MMI ALU operations
  (`pcpyld` 678, `mult1` 283, `pextlb` 167, `pextlh` 131, `ppacb` 81, `paddh` 80, `ppach` 73, `maddu` 71 ...; 49
  distinct MMI mnemonics in total, 5 `pmfhl`, all `pmfhl.lw`). Inferred: the recompiler's 128-bit path is dominated
  by quadword moves, and the exotic MMI ALU set is small enough to test exhaustively.
* VU0 macro mode uses **24 base mnemonics** (`vmul` 722, `vadd` 382, `vsub` 272, `vmula` 216, `vmadda` 210,
  `vmadd` 202, `vnop` 160, `vmove` 156, `vitof0` 131, `vadda` 77, `vftoi0` 73, `vaddi` 72, `vmsub` 63, `vwaitq` 48,
  `vrsqrt` 39, `vmulq` 39, `vabs`/`vmini`/`vmax` 15, `vmuli` 14, `vopmula`/`vopmsub` 13, `vsqrt` 8, `vmsuba` 5) in
  47 broadcast forms and the dest fields listed in `insn_census.json#variants`. **No** `vcallms`/`vcallmsr`, `vlqi`/
  `vsqi`/`vlqd`/`vsqd`, `vilwr`/`viswr`, `vclip`, `vdiv`, `vmtir`/`vmfir`, `vrnext`/`vrget`/`vrinit`/`vrxor`, integer
  `vi*` ops, or `bc2*` branches occur: VU0 is used purely as a vector ALU from the EE, never with micro-programs
  (observed absence; inferred reading).
* FPU: 29 mnemonics incl. the EE-only `adda.s` 2,264, `madd.s` 2,510, `msub.s` 695, `mula.s` 941, `madda.s` 361,
  `msuba.s` 3, `suba.s` 2; compares are only `c.le.s`/`c.lt.s`/`c.eq.s` (no `c.f.s`); `bc1fl`/`bc1tl` 13 total;
  `ctc1` once, `cfc1` never; no `rsqrt.s`, `max.s`, `min.s`.
* Likely branches: 6 integer forms (`bnel` 1,181, `beql` 938, `bgezl` 112, `blezl` 64, `bltzl` 40, `bgtzl` 39) +
  13 `bc1fl/tl`; `bltzall`/`bgezall` never. 1,966 of the 2,374 words are in the MW runtime + CRI band and 397 in the
  SCE SDK band; Atlus game code (`0x100000..0x46c000`) contains **none**. Inferred: likely-branch handling is only
  exercised by library code, so its tests can target `0x4f9000..0x5a2000` functions.

## 2. Three decoders on the same words (observed)

| Decoder | Result over the 1,194,277 words |
|---|---|
| Our table (`insn_census.py`, layout mirrors `ps2-web-recomp/recomp/r5900.cpp`) | 0 invalid |
| ps2dev binutils 2.45.1 `mips64r5900el-ps2-elf-objdump -d` | agrees on 1,194,269; the 8 disagreements are `vsqrt` words (`0x3262ec`, `0x329cf0`, `0x32f000`...) that binutils prints as a raw `c2` word (binutils gap) |
| IDA 9.3 `r5900l` | names 201 `bc0f` words `mfthc1 $ra,$f0` (`0x10e6d4` and others, a misrendering: op 0x10, rs 8), names MMI2 fmt 0x1E `pexow` (manual, rabbitizer, binutils: `pexew`, 9 words), prints every VU0 macro word as opaque `cop2 <imm>` (2,960), and fuses 15,xxx multi-word macro items |

Inferred consequence (already ADR-0004's direction, now sharpened): the recompiler must decode **bytes**, not IDA items
or `ida_ua.decode_insn` output; IDA supplies boundaries, names, switch tables and nothing else about instruction identity.

## 3. Indirect control flow (observed; `symbols/jumptables.json`)

* `jr $ra` 13,727. **`jr $rN` (N != ra): 568 sites in 431 functions — 553 carry IDA `switch_info_t`, 15 do not.**
* The 553 resolved switches (416 functions; 72 have more than one, `sub_2DEFE0` and `sub_2E1500` have 11 each) are
  uniform: 32-bit absolute target tables (`SWI_J32|SWI_SIGNED`), element size 4, shift 0, every one with a default,
  510 with `lowcase` 0; 6,787 cases resolve to 5,131 distinct targets. Re-reading every table from its bytes
  reproduces IDA's target set at all 553 sites. **Sanity: 0 targets outside the owning function, 0 defaults outside
  it, 0 targets outside any function.** Largest: `__svfscanf_r` 121 (`0x527c58`), `sfxcnv_MakeTable` 101,
  `_sceSnprintf` 89, `vfprintf` 89 (`0x526488`), `sub_3E6E80` 81. `sub_3E0C20` (the Ghidra truncation case in `06`):
  one switch at `0x3e0c58`, table `0x7bb900`, 18 cases, default `0x3e5adc`. By band: `btl*/dat*` 111, `h_*` 109,
  `br_*/bp_*` 73, `mt_evt*` 69, `comu*/fcl*` 56.
* The 15 unresolved `jr` are all in the RenderWare band (`0x45edc8`..`0x4ca38c`), all `lw $v0, <pointer>; jr $v0;
  nop` in tail position: calls through `RwFree`, `RwHeapMalloc`, `pfnRwFreeListFree/Alloc`, camera begin/end-update
  callbacks and object vtable slots (`0x68($v0)`, `0x44($v0)`...). Inferred: none is a jump table; all are
  tail-calls through function pointers and belong to the `LOOKUP_FUNC` dispatch path, not to manual tables. The
  `sll/addu/lw/jr` idiom without switch info does **not** occur.
* `jalr`: 5,143 sites in 1,958 functions (`$v0` 4,849, `$v1` 183) — the size of the indirect-call dispatch problem.
* Not covered here: the 54 mid-body `jal` targets and the 11 called-but-unowned addresses from `06` §2.4.

## 4. Test-matrix sizing (observed counts of functions containing the feature)

| Feature | Functions | Feature | Functions |
|---|---|---|---|
| any `ld`/`sd` | 11,249 | any likely branch | 1,132 |
| any 64-bit integer ALU/shift (`daddu`, `dsll32`...) | 10,707 | any `jr $rN` (N != ra) | 431 |
| any MMI (incl. `lq`/`sq`) | 6,180 | any `syscall`/`break` | 267 |
| any MMI or COP2 | 6,197 | multi-chunk | 173 |
| any FPU | 2,393 | any COP2 (transfer or VU0) | 148 |
| any `jalr` | 1,958 | any VU0 macro op | 111 |
| contains data items inside its chunks | 932 | any COP0 | 93 |

Where the hard units live (observed): COP2 is concentrated in `0x30fc40..0x35aef0` (2,880 words, 123 functions —
the unattributed band between `btl*` and `scr*`; inferred: Atlus math/skinning helpers) and the `G3_2D*` renderer
band (1,844 words, 18 functions, the `RpPDS_G3_*_PS2AllMatBridgeCallBack` family); MMI ALU density peaks in the
RenderWare `rpPTankSkyInsPos*` particle renderers (`0x47cfd0..0x481860`, 219-336 MMI words each) and
`_rpSkinMatrixUpdating`. The top-20 table is in the generated block.

## 5. What is excluded (observed)

* **Orphan code outside every function: 39,848 bytes** (9,946 IDA items in `main`, `0x1939a0..0x7cdaac`). Its
  mnemonic mix (`nop` 1,331, `break` 1,230, `tge` 365, `beql` 557) is not plausible code; inferred: VU micro-code /
  GIF packets that IDA marked as code (the `syscall`-scan gotcha in `tools/ours/ida/README.md`). Not in any table.
* Data items inside function chunks (alignment words, inline constants) are counted but not decoded; see the
  generated block for the count and how many of those words would also decode as valid instructions.

<!-- GENERATED:BEGIN (insn_census.py) -->
_Generated 2026-10-21 06:40:17 by `tools/ours/ida/insn_census.py` from `ida/work_master_update5.i64 (copy of ida/p3fes.i64)`. Do not edit inside the markers. Word counts are observed (our decoder over IDA's function-chunk bytes); unit grouping and macro expansion are ours._

### Headline

| Metric | Value |
|---|---|
| IDA functions walked (all chunks) | 14,500 |
| Instruction words inside functions (word-level, ours) | 1,196,677 |
| IDA code items (macro-fused view) | 1,180,278 (+16,398 words hidden in macro items; sum matches words: False) |
| Code bytes inside functions | 4,786,708 |
| Data items inside function chunks (not decoded) | 1,550 items, 6,200 bytes (1,550 words would decode as valid instructions) |
| Orphan code outside every function (excluded) | 13,936 bytes in 1 segment(s) |
| &nbsp;&nbsp;orphan in `main` | 3,474 items, 13,936 bytes, `0x1939a0`..`0x7cdaac`; top: `nop` 463, `sll` 294, `add` 293, `mfhi` 264, `dsll` 249, `tge` 243 |
| Words our decoder rejects (`invalid`) | 0 (first 200 listed in JSON) |

### Per-unit totals (word level)

| Unit | Words | Share | Distinct base mnemonics |
|---|---|---|---|
| integer core | 823,376 | 68.81% | 64 |
| COP1 FPU | 130,643 | 10.92% | 29 |
| branch | 101,468 | 8.48% | 7 |
| jump | 87,887 | 7.34% | 4 |
| MMI | 44,615 | 3.73% | 49 |
| COP2 VU0 macro | 2,960 | 0.25% | 24 |
| branch (likely) | 2,374 | 0.20% | 6 |
| COP2 transfer | 1,954 | 0.16% | 6 |
| COP0 | 1,049 | 0.09% | 7 |
| trap | 351 | 0.03% | 2 |

### Mnemonic table by unit (VU0 dest `.xyzw` / broadcast `x|y|z|w` and `pmfhl.*` fold into the base; variants in `symbols/insn_census.json#variants`)

**MMI** (44,615): `sq` 21,399, `lq` 21,000, `pcpyld` 687, `mult1` 283, `pextlb` 167, `pextlh` 131, `ppacb` 81, `paddh` 80, `ppach` 73, `maddu` 71, `ppacw` 58, `mflo1` 53, `div1` 51, `psrlh` 50, `qfsrv` 48, `paddub` 35, `mtsab` 32, `pnor` 30, `pand` 30, `padduw` 29, `pcpyud` 25, `pextub` 18, `pminh` 16, `pmaxh` 16, `psubb` 15, `paddw` 15, `pextlw` 13, `por` 13, `phmadh` 12, `pexew` 9, `pxor` 9, `mtsah` 7, `mfhi1` 7, `pextuw` 6, `pcgth` 6, `madd` 6, `pmfhl` 5, `psrah` 4, `psllh` 4, `psubw` 4, `multu1` 3, `psraw` 3, `mthi1` 2, `mtlo1` 2, `mfsa` 2, `pcpyh` 2, `prot3w` 1, `maddu1` 1, `mtsa` 1

**integer core** (823,376): `sll` 199,843, `addiu` 156,233, `daddu` 90,142, `lw` 79,005, `lui` 46,522, `sw` 46,307, `addu` 27,082, `ld` 25,283, `sd` 23,399, `andi` 18,162, `sb` 9,819, `sh` 9,516, `lbu` 9,207, `ori` 7,340, `lhu` 7,313, `or` 6,410, `dsll32` 6,368, `slti` 5,903, `lh` 5,885, `subu` 5,394, `dsra32` 4,908, `slt` 4,253, `lb` 4,031, `and` 3,290, `srl` 3,229, `sltu` 2,578, `sra` 2,112, `sltiu` 1,928, `mult` 1,665, `div` 1,056, `mflo` 1,015, `dsrl32` 811, `xori` 618, `mfhi` 616, `sllv` 554, `ldr` 506, `ldl` 506, `movn` 473, `sdl` 460, `sdr` 460, `daddiu` 427, `nor` 423, `dsll` 421, `divu` 401, `movz` 299, `srlv` 258, `xor` 222, `lwu` 145, `dsrl` 123, `dsubu` 107, `srav` 72, `multu` 52, `lwr` 38, `lwl` 38, `addi` 29, `swl` 28, `swr` 28, `dsra` 20, `dsllv` 16, `add` 12, `mtlo` 7, `dsrlv` 5, `mthi` 2, `sub` 1

**COP1 FPU** (130,643): `lwc1` 30,864, `swc1` 24,370, `mtc1` 22,211, `add.s` 8,192, `cvt.s.w` 7,774, `mul.s` 7,287, `sub.s` 5,343, `mov.s` 3,918, `div.s` 2,679, `mfc1` 2,661, `madd.s` 2,519, `cvt.w.s` 2,378, `adda.s` 2,272, `bc1t` 1,659, `c.le.s` 1,486, `c.lt.s` 1,090, `bc1f` 1,076, `mula.s` 945, `msub.s` 698, `neg.s` 488, `madda.s` 362, `c.eq.s` 172, `sqrt.s` 133, `abs.s` 47, `bc1fl` 8, `bc1tl` 5, `msuba.s` 3, `suba.s` 2, `ctc1` 1

**COP0** (1,049): `sync` 733, `mfc0` 110, `ei` 92, `di` 75, `cache` 17, `mtc0` 16, `eret` 6

**branch** (101,468): `beq` 68,971, `bne` 27,066, `bltz` 1,872, `bgez` 1,276, `blez` 1,095, `bgtz` 987, `bc0f` 201

**jump** (87,887): `jal` 66,599, `jr` 14,378, `jalr` 5,149, `j` 1,761

**trap** (351): `break` 183, `syscall` 168

**COP2 transfer** (1,954): `lqc2` 662, `sqc2` 618, `qmtc2` 481, `qmfc2` 93, `ctc2` 83, `cfc2` 17

**COP2 VU0 macro** (2,960): `vmul` 722, `vadd` 382, `vsub` 272, `vmula` 216, `vmadda` 210, `vmadd` 202, `vnop` 160, `vmove` 156, `vitof0` 131, `vadda` 77, `vftoi0` 73, `vaddi` 72, `vmsub` 63, `vwaitq` 48, `vrsqrt` 39, `vmulq` 39, `vabs` 15, `vmini` 15, `vmax` 15, `vmuli` 14, `vopmula` 13, `vopmsub` 13, `vsqrt` 8, `vmsuba` 5

**branch (likely)** (2,374): `bnel` 1,181, `beql` 938, `bgezl` 112, `blezl` 64, `bltzl` 40, `bgtzl` 39

### Third decoder: ps2dev binutils `objdump -d` over the same words (observed)

_not run_

Word accounting (IDA items + macro words vs chunk words): 1 function(s) differ: `sub_46BFB0` `0x46bfb0` items+macro=223 words=224.

### How IDA renders the same stream (cross-check)

| IDA rendering | Items | Meaning |
|---|---|---|
| `cop2` | 2,960 | opaque: IDA does not name the VU0 macro op (the word-level table above does) |
| `li` | 12,721 | macro item, sizes {8: 12721}; expands to lui+ori/addiu (32-bit immediate) |
| `lw` | 1,950 | macro item, sizes {8: 1889, 12: 61}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lbu` | 57 | macro item, sizes {8: 55, 12: 2}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lh` | 25 | macro item, sizes {8: 23, 12: 2}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lhu` | 313 | macro item, sizes {8: 313}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lb` | 3 | macro item, sizes {8: 2, 12: 1}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lwc1` | 68 | macro item, sizes {8: 68}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `ld` | 22 | macro item, sizes {8: 22}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `swc1` | 13 | macro item, sizes {8: 13}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `lq` | 9 | macro item, sizes {8: 9}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `uld` | 460 | macro item, sizes {8: 460}; expands to ldl+ldr |
| `usd` | 451 | macro item, sizes {8: 451}; expands to sdl+sdr |
| `sw` | 16 | macro item, sizes {8: 10, 12: 6}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `ulw` | 28 | macro item, sizes {8: 28}; expands to lwl+lwr |
| `usw` | 23 | macro item, sizes {8: 23}; expands to swl+swr |
| `sd` | 10 | macro item, sizes {8: 10}; expands to lui-fused %hi/%lo address (8 B) or lui+addu+op (12 B); the op itself is the last word |
| `dli` | 27 | macro item, sizes {24: 27}; expands to lui/ori/dsll32/or 64-bit immediate sequence |
| `li.s` | 22 | macro item, sizes {8: 22}; expands to lui+mtc1 (float immediate) |

### Indirect jumps and calls

| Site kind | Count |
|---|---|
| `jr $ra` (returns) | 13,809 |
| `jr $rN`, N != ra (indirect jumps) | 569 in 432 functions |
| &nbsp;&nbsp;with IDA switch info | 553 |
| &nbsp;&nbsp;without switch info (unresolved) | 16 |
| `jalr` (indirect calls) | 5,149 in 1,962 functions |

`jr $rN` by register: `$v0` 355, `$v1` 180, `$a0` 11, `$t5` 7, `$a1` 4, `$t4` 2, `$s1` 2, `$s6` 2, `$a2` 2, `$a3` 1, `$a5` 1, `$a4` 1, `$s4` 1.  
`jalr` by target register: `$v0` 4855, `$v1` 183, `$s7` 27, `$s0` 13, `$s3` 11, `$a1` 10, `$a3` 9, `$a2` 7, `$s2` 6, `$s4` 6, `$at` 5, `$s1` 3, `$s6` 3, `$t7` 3, `$a4` 3, `$a0` 2, `$fp` 1, `$s5` 1, `$t4` 1.

### Functions by feature (recompiler test-matrix sizing)

| Feature present in function | Functions |
|---|---|
| any_ld_sd_or_unaligned_64 | 11,264 |
| any_ld_sd | 11,256 |
| any_64bit_int_alu_shift | 10,749 |
| any_mmi_or_cop2 | 6,202 |
| any_mmi | 6,185 |
| any_fpu | 2,399 |
| any_jalr | 1,962 |
| any_likely_branch | 1,132 |
| contains_data_items | 930 |
| any_jr_non_ra | 432 |
| any_trap_or_syscall | 267 |
| multi_chunk | 173 |
| any_cop2 | 148 |
| any_vu0_macro | 111 |
| any_cop0 | 93 |

### Distribution across the band map (`03`, bands as in `06` §2.1)

| Band | Functions | Words | MMI | fn w/ MMI | COP2 | fn w/ COP2 | FPU | likely | fn w/ likely |
|---|---|---|---|---|---|---|---|---|---|
| `0x100000..0x103da0 crt0 + early SDK stubs` | 68 | 3,846 | 247 | 41 | 0 | 0 | 131 | 0 | 0 |
| `0x103da0..0x1939d0 h_* / _h_camp_*` | 1,051 | 145,691 | 4,486 | 638 | 0 | 0 | 18,516 | 0 | 0 |
| `0x1939d0..0x199440 kwln*` | 85 | 5,679 | 148 | 32 | 0 | 0 | 61 | 0 | 0 |
| `0x199440..0x1e7f90 k_*` | 749 | 79,534 | 2,705 | 457 | 0 | 0 | 9,718 | 0 | 0 |
| `0x1e7f90..0x28dbf0 br_*/bp_*/sfl_*/op_*` | 1,536 | 167,518 | 5,320 | 945 | 34 | 1 | 25,182 | 0 | 0 |
| `0x28dbf0..0x30fc40 btl*/dat*` | 1,464 | 130,854 | 4,661 | 805 | 27 | 2 | 18,923 | 0 | 0 |
| `0x30fc40..0x35aef0 unattributed` | 861 | 75,720 | 4,536 | 539 | 2,880 | 123 | 16,289 | 0 | 0 |
| `0x35aef0..0x361350 scr*` | 122 | 6,269 | 318 | 83 | 0 | 0 | 185 | 0 | 0 |
| `0x361350..0x3a2150 mt_evt*` | 497 | 65,766 | 2,607 | 374 | 0 | 0 | 4,140 | 0 | 0 |
| `0x3a2150..0x3bdbd0 itf*/fr*` | 465 | 27,651 | 1,523 | 253 | 0 | 0 | 2,265 | 0 | 0 |
| `0x3bdbd0..0x4176f0 comu*/fcl*` | 916 | 90,485 | 4,405 | 654 | 0 | 0 | 5,073 | 0 | 0 |
| `0x4176f0..0x46c000 unattributed (Y_StParts_UpdateStratumPartsTask)` | 586 | 85,844 | 2,908 | 348 | 117 | 1 | 14,436 | 0 | 0 |
| `0x46c000..0x4e7000 G3_2D* renderer` | 1,313 | 125,151 | 8,407 | 824 | 1,844 | 18 | 13,092 | 5 | 1 |
| `0x4e7000..0x4f9000 renderer tail` | 131 | 16,841 | 1,342 | 81 | 0 | 0 | 1,025 | 6 | 2 |
| `0x4f9000..0x51d460 SCE SDK libs` | 807 | 36,825 | 696 | 57 | 5 | 2 | 10 | 397 | 205 |
| `0x51d460..0x5a2000 MW runtime + CRI` | 3,838 | 132,932 | 306 | 54 | 7 | 1 | 1,597 | 1,966 | 924 |
| `0x5a2000..0x7cde80 data band` | 11 | 71 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

### Top 20 functions by MMI + COP2 word count

| Function | VA | Size (B) | Chunks | Words | MMI | COP2 | FPU | Likely | Band |
|---|---|---|---|---|---|---|---|---|---|
| `sub_47FB10` | `0x47fb10` | 4,376 | 1 | 1,094 | 21 | 336 | 133 | 0 | G3_2D* renderer |
| `sub_481860` | `0x481860` | 4,592 | 1 | 1,148 | 31 | 324 | 109 | 0 | G3_2D* renderer |
| `sub_47E9E0` | `0x47e9e0` | 4,392 | 1 | 1,098 | 31 | 300 | 93 | 0 | G3_2D* renderer |
| `sub_47CFD0` | `0x47cfd0` | 3,668 | 1 | 917 | 21 | 219 | 141 | 0 | G3_2D* renderer |
| `sub_336E80` | `0x336e80` | 2,412 | 1 | 603 | 22 | 190 | 158 | 0 | unattributed |
| `sub_480C30` | `0x480c30` | 3,120 | 1 | 780 | 21 | 188 | 32 | 0 | G3_2D* renderer |
| `sub_47DE30` | `0x47de30` | 2,984 | 1 | 746 | 18 | 170 | 24 | 0 | G3_2D* renderer |
| `matfxBridgeBumpEnvMap` | `0x46d6f0` | 2,680 | 1 | 670 | 133 | 0 | 19 | 0 | G3_2D* renderer |
| `_rpSkinMatrixUpdating` | `0x46b510` | 968 | 1 | 242 | 12 | 117 | 0 | 0 | unattributed (Y_StParts_UpdateStratumPartsTask) |
| `sub_32EB40` | `0x32eb40` | 3,428 | 1 | 857 | 31 | 93 | 396 | 0 | unattributed |
| `sub_3407E0` | `0x3407e0` | 5,048 | 1 | 1,262 | 44 | 78 | 592 | 0 | unattributed |
| `sub_3275D0` | `0x3275d0` | 3,340 | 1 | 835 | 38 | 83 | 161 | 0 | unattributed |
| `sub_333970` | `0x333970` | 2,120 | 1 | 530 | 14 | 100 | 202 | 0 | unattributed |
| `matfxBridgeDualUvTransform` | `0x472970` | 2,508 | 1 | 627 | 112 | 0 | 3 | 0 | G3_2D* renderer |
| `sub_335A70` | `0x335a70` | 2,996 | 1 | 749 | 20 | 90 | 323 | 0 | unattributed |
| `matfxBridgeEnvMap` | `0x46cd90` | 2,396 | 1 | 599 | 110 | 0 | 5 | 0 | G3_2D* renderer |
| `sub_3520A0` | `0x3520a0` | 1,876 | 1 | 469 | 34 | 72 | 130 | 0 | unattributed |
| `sub_3399A0` | `0x3399a0` | 2,164 | 1 | 541 | 37 | 68 | 156 | 0 | unattributed |
| `sub_33B2A0` | `0x33b2a0` | 2,360 | 1 | 590 | 37 | 68 | 179 | 0 | unattributed |
| `sub_33C1A0` | `0x33c1a0` | 1,976 | 1 | 494 | 41 | 62 | 148 | 0 | unattributed |

### Operand-format samples as IDA prints them (first 3 sites each; VAs)

| IDA mnemonic | IDA items | Sample sites |
|---|---|---|
| `adda.s` | 2,272 | `0x100110` `adda.s  $f0, $f1`; `0x105274` `adda.s  $f1, $f22`; `0x112d80` `adda.s  $f2, $f0` |
| `bc1f` | 1,076 | `0x1047fc` `bc1f    loc_104A78`; `0x104dc8` `bc1f    loc_104E8C`; `0x104de0` `bc1f    loc_104E8C` |
| `bc1fl` | 8 | `0x52c44c` `bc1fl   loc_52C460`; `0x531f5c` `bc1fl   loc_531F64`; `0x531f6c` `bc1fl   loc_531F74` |
| `bc1t` | 1,659 | `0x1047b0` `bc1t    loc_1047C4`; `0x1119dc` `bc1t    loc_111A10`; `0x112cd0` `bc1t    loc_112EBC` |
| `bc1tl` | 5 | `0x52dc38` `bc1tl   loc_52D658`; `0x539938` `bc1tl   loc_53994C`; `0x5532a4` `bc1tl   loc_5532E8` |
| `beqzl` | 776 | `0x4f1e88` `beqzl   $at, loc_4F1EBC`; `0x4f1e9c` `beqzl   $at, loc_4F1EBC`; `0x4f1eb0` `beqzl   $at, loc_4F1EBC` |
| `bnezl` | 757 | `0x4f91cc` `bnezl   $v0, loc_4F9208`; `0x4faa40` `bnezl   $a0, loc_4FAA50`; `0x4faa54` `bnezl   $v0, loc_4FAA64` |
| `c.eq.s` | 172 | `0x1047ac` `c.eq.s  $f0, $f12`; `0x1047f8` `c.eq.s  $f0, $f1`; `0x112ccc` `c.eq.s  $f0, $f3` |
| `c.le.s` | 1,486 | `0x1119d8` `c.le.s  $f21, $f0`; `0x111d0c` `c.le.s  $f20, $f0`; `0x112cf8` `c.le.s  $f3, $f2` |
| `c.lt.s` | 1,090 | `0x104dc4` `c.lt.s  $f1, $f0`; `0x104ddc` `c.lt.s  $f20, $f0`; `0x10527c` `c.lt.s  $f0, $f1` |
| `cache` | 17 | `0x5039c4` `cache   0x10, 0($a2)`; `0x5039f4` `cache   0x14, 0($a2)`; `0x503a00` `cache   0x10, 1($a2)` |
| `cfc2` | 17 | `0x3262f4` `cfc2    $v0, $22`; `0x329cf8` `cfc2    $v0, $22`; `0x32f008` `cfc2    $v0, $22` |
| `cop2` | 2,960 | `0x285a8c` `cop2    0x1EB593C`; `0x285a9c` `cop2    0x1E25AD8`; `0x285abc` `cop2    0x1EA513C` |
| `ctc2` | 83 | `0x47d170` `ctc2    $a0, $21`; `0x47d190` `ctc2    $a0, $21`; `0x47d1b0` `ctc2    $a0, $21` |
| `cvt.s.w` | 7,774 | `0x10039c` `cvt.s.w $f0, $f0`; `0x1003bc` `cvt.s.w $f0, $f0`; `0x1003dc` `cvt.s.w $f0, $f0` |
| `cvt.w.s` | 2,378 | `0x104d94` `cvt.w.s $f0, $f0`; `0x104d9c` `cvt.w.s $f0, $f20`; `0x10812c` `cvt.w.s $f0, $f0` |
| `di` | 75 | `0x46cbd0` `di`; `0x46d348` `di`; `0x46dd10` `di` |
| `div` | 1,056 | `0x10779c` `div     $v1, $v0`; `0x107a18` `div     $v1, $v0`; `0x107ce8` `div     $v1, $v0` |
| `div.s` | 2,679 | `0x100344` `div.s   $f2, $f1, $f0`; `0x104450` `div.s   $f20, $f1, $f0`; `0x10473c` `div.s   $f21, $f1, $f0` |
| `div1` | 51 | `0x118f20` `div1    $v0, $a0`; `0x11cb84` `div1    $v0, $a0`; `0x1225d4` `div1    $v0, $v1` |
| `divu` | 401 | `0x12879c` `divu    $s4, $v1`; `0x128824` `divu    $s4, $v1`; `0x12889c` `divu    $s4, $v1` |
| `dli` | 27 | `0x5210f4` `dli     $v0, 0x101010101010101`; `0x521110` `dli     $v1, 0x8080808080808080`; `0x523e84` `dli     $v1, 0x101010101010101` |
| `dnegu` | 23 | `0x504d28` `dnegu   $a2, $a2`; `0x505354` `dnegu   $v1, $s0`; `0x520aac` `dnegu   $a7, $t7` |
| `ei` | 92 | `0x1001f8` `ei`; `0x197020` `ei`; `0x197ff4` `ei` |
| `eret` | 6 | `0x50d13c` `eret`; `0x50d270` `eret`; `0x50d378` `eret` |
| `ldl` | 46 | `0x148a94` `ldl     $a0, 0x3F($s1)`; `0x14c4a4` `ldl     $a0, 0x3F($s1)`; `0x15fd30` `ldl     $a0, 0x3F($s1)` |
| `ldr` | 46 | `0x148a90` `ldr     $a0, 0x38($s1)`; `0x14c4a0` `ldr     $a0, 0x38($s1)`; `0x15fd2c` `ldr     $a0, 0x38($s1)` |
| `li.s` | 22 | `0x531f50` `li.s    $f1, -960.0`; `0x531fd8` `li.s    $f12, 200.0`; `0x539860` `li.s    $f22, 2.0` |
| `lq` | 21,000 | `0x100558` `lq      $s1, 0x20+var_10($sp)`; `0x10055c` `lq      $s0, 0x20+var_20($sp)`; `0x1006f8` `lq      $s1, 0x60+var_40($sp)` |
| `lqc2` | 662 | `0x2b981c` `lqc2    $10, 0($v1)`; `0x2b9880` `lqc2    $11, 0($v1)`; `0x2b98a0` `lqc2    $11, 0($v1)` |
| `lwu` | 145 | `0x46c74c` `lwu     $a3, -0x51BC($gp)`; `0x46c774` `lwu     $a1, -0x51C0($gp)`; `0x46c78c` `lwu     $v1, 0x90+var_4($sp)` |
| `madd` | 6 | `0x5013c8` `madd    $zero, $v0, $v1`; `0x52ea98` `madd    $a0, $a1`; `0x53a6c0` `madd    $a0, $v1, $a2` |
| `madd.s` | 2,519 | `0x105278` `madd.s  $f0, $f2`; `0x112d84` `madd.s  $f1, $f20`; `0x112d90` `madd.s  $f1, $f20, $f1` |
| `madda.s` | 362 | `0x199dd0` `madda.s $f3, $f2`; `0x19a4e4` `madda.s $f3, $f2`; `0x1aae48` `madda.s $f1, $f8` |
| `maddu` | 71 | `0x3640a8` `maddu   $v1, $a2`; `0x4e5834` `maddu   $t7, $a0`; `0x4e5844` `maddu   $t7, $a2, $a2` |
| `maddu1` | 1 | `0x3640d4` `maddu1  $v1, $a2` |
| `mfc0` | 110 | `0x46cbd8` `mfc0    $v1, SR`; `0x46d350` `mfc0    $v1, SR`; `0x46dd18` `mfc0    $v1, SR` |
| `mfhi1` | 7 | `0x4db020` `mfhi1   $v0`; `0x50d0c8` `mfhi1   $v0`; `0x50d308` `mfhi1   $v0` |
| `mflo1` | 53 | `0x118f24` `mflo1   $v0`; `0x11cb88` `mflo1   $v1`; `0x1225d8` `mflo1   $a5` |
| `mfsa` | 2 | `0x50d0ec` `mfsa    $v0`; `0x50d32c` `mfsa    $v0` |
| `mfthc1` | 201 | `0x10e6d4` `mfthc1  $ra, $f0`; `0x10e754` `mfthc1  $ra, $f0`; `0x10e7d0` `mfthc1  $ra, $f0` |
| `movn` | 473 | `0x4685e8` `movn    $v0, $v1, $a0`; `0x468718` `movn    $v0, $v1, $a0`; `0x49de48` `movn    $a1, $zero, $s1` |
| `movz` | 299 | `0x45f76c` `movz    $s1, $zero, $v0`; `0x467558` `movz    $s6, $s1, $v1`; `0x469b84` `movz    $a1, $v1, $a2` |
| `msub.s` | 698 | `0x112dcc` `msub.s  $f0, $f20, $f1`; `0x157dfc` `msub.s  $f1, $f2, $f3`; `0x157ef0` `msub.s  $f1, $f2, $f3` |
| `msuba.s` | 3 | `0x28e1f4` `msuba.s $f3, $f2`; `0x4bc8ac` `msuba.s $f5, $f6`; `0x4bc8b4` `msuba.s $f1, $f4` |
| `mtc0` | 16 | `0x4e01d0` `mtc0    $v1, SR`; `0x50ce90` `mtc0    $zero, Wired`; `0x50cf68` `mtc0    $t9, Wired` |
| `mtsa` | 1 | `0x50d1dc` `mtsa    $v0` |
| `mtsab` | 32 | `0x4fdcb0` `mtsab   $a4, 0`; `0x4fdd28` `mtsab   $t4, 0`; `0x4fddd4` `mtsab   $t5, 0` |
| `mtsah` | 7 | `0x10008c` `mtsah   $zero, 0`; `0x54f924` `mtsah   $a4, 4`; `0x54f93c` `mtsah   $a5, 2` |
| `mula.s` | 945 | `0x112dc8` `mula.s  $f0, $f20`; `0x1878a4` `mula.s  $f0, $f20`; `0x187a88` `mula.s  $f0, $f3` |
| `mult1` | 283 | `0x1130f4` `mult1   $t4, $t7`; `0x113114` `mult1   $a7, $t7`; `0x191fe4` `mult1   $v0, $s5, $v0` |
| `pexow` | 9 | `0x339e38` `pexow   $v0, $v0`; `0x33ab10` `pexow   $v0, $v0`; `0x33b7d8` `pexow   $v0, $v0` |
| `pmfhl.lw` | 5 | `0x52ea9c` `pmfhl.lw $at`; `0x53136c` `pmfhl.lw $at`; `0x531378` `pmfhl.lw $at` |
| `qfsrv` | 48 | `0x4fdcd0` `qfsrv   $a6, $a5, $a4`; `0x4fdd44` `qfsrv   $a5, $a4, $a4`; `0x4fddd8` `qfsrv   $a6, $a5, $a4` |
| `qmfc2` | 93 | `0x285b14` `qmfc2   $v0, $10`; `0x285c44` `qmfc2   $v0, $10`; `0x3260dc` `qmfc2   $v1, $10` |
| `qmtc2` | 481 | `0x285a88` `qmtc2   $v0, $11`; `0x285a98` `qmtc2   $v0, $2`; `0x285ab8` `qmtc2   $v0, $10` |
| `sdl` | 9 | `0x545778` `sdl     $v1, 0xF($s0)`; `0x54e890` `sdl     $v0, 0xA27($a0)`; `0x563654` `sdl     $a2, 7($s2)` |
| `sdr` | 9 | `0x545780` `sdr     $v1, 8($s0)`; `0x54e898` `sdr     $v0, 0xA20($a0)`; `0x56365c` `sdr     $a2, 0($s2)` |
| `sq` | 21,399 | `0x100160` `sq      $zero, 0($v0)`; `0x100238` `sq      $s1, 0x20+var_10($sp)`; `0x10023c` `sq      $s0, 0x20+var_20($sp)` |
| `sqc2` | 618 | `0x2b9898` `sqc2    $11, 0($v1)`; `0x2b98dc` `sqc2    $10, 0($s1)`; `0x2ba194` `sqc2    $10, 0($s0)` |
| `sqrt.s` | 133 | `0x1b067c` `sqrt.s  $f0, $f0`; `0x1d51d0` `sqrt.s  $f0, $f0`; `0x1d5458` `sqrt.s  $f2, $f0` |
| `suba.s` | 2 | `0x52be98` `suba.s  $f11, $f2`; `0x52dd28` `suba.s  $f0, $f13` |
| `sync` | 733 | `0x100114` `sync    0x10`; `0x10e6b8` `sync`; `0x10e6bc` `sync    0x10` |
| `uld` | 460 | `0x4faba0` `uld     $v0, 0($a5)`; `0x4faba8` `uld     $a0, 8($a5)`; `0x4fabd8` `uld     $a1, (qword_965AC8 - 0x965AC8)($a4)` |
| `ulw` | 28 | `0x507c7c` `ulw     $v0, 0($s0)`; `0x507c8c` `ulw     $a2, 4($s0)`; `0x507c9c` `ulw     $v1, 8($s0)` |
| `usd` | 451 | `0x4fabb4` `usd     $v0, (qword_965AC8 - 0x965AC8)($a2)`; `0x4fabbc` `usd     $a0, (qword_965AD0 - 0x965AC8)($a2)`; `0x4fabec` `usd     $a1, 0($a0)` |
| `usw` | 23 | `0x507c84` `usw     $v0, 0x30+var_30($sp)`; `0x507c94` `usw     $a2, 0x30+var_2C($sp)`; `0x507ca4` `usw     $v1, 0x30+var_28($sp)` |
<!-- GENERATED:END -->
