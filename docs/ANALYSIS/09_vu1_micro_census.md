# 09 - VU1 micro-instruction census (Phase 3 interpreter input)

_Written 2026-10-18 from the 114 microcode dumps `ida/logs/vu1/<code_va>.bin` (gitignored game data; produced by
topic `14`'s packet scan, named by the VA of the first `MPG` code = ret-tag VA + 0xC) by `tools/ours/vu1/vu1_decode.py`
(decoder) and `tools/ours/vu1/vu1_census.py` (census). Machine output: `symbols/vu1_micro_census.json`. Inventory
(VAs, families) comes from the `vu1_prog_*` rows of `symbols/p3fes.sym`, i.e. from `14` §1. No IDA database was
opened. This resolves `RUNTIME_CONTRACT.md` V-07 ("VU1 micro instruction coverage unmeasured"). Legend as in `14`:
**[obs]** counted from the dump bytes, **[der]** derived from the decoded stream by static reading (branch targets,
loops, reachability), **[inf]** our inference._

## 0. Headline

* **123,095 64-bit instructions (984,760 bytes) in 114 programs decode with 0 `UNKNOWN` halves** [obs]. Units, E-bit
  and `xgkick` counts agree with `14` §1 on all 114 rows [obs].
* The whole corpus uses **43 upper mnemonics** (form-qualified: `ADD`, `ADDbc`, `ADDi`, `ADDq` count separately; 20 base
  ops) and **45 lower mnemonics** [obs]. Not used anywhere: the **M, D and T flags** (0 of 123,095), every **R op**
  (`RINIT/RGET/RNEXT/RXOR`), **`JALR`**, the **status-flag ops** `FSEQ/FSSET/FSAND/FSOR`, `FMEQ/FMOR`, `FCEQ`, `SQRT`,
  `WAITP`, and 11 of the 13 **EFU P-pipe** producers (`EATAN/EATANxy/EATANxz`, `EEXP`, `ELENG`, `ERLENG`, `ERSADD`,
  `ERSQRT`, `ESADD`, `ESIN`, `ESQRT`, `ESUM`; only **`ERCPR`+`MFP`**, 62 each, occur), plus the upper ops `ABS`,
  `MAXi`, `ITOF12/ITOF15/FTOI12/FTOI15`, vector `SUBA`/`MADDA`/`MSUBA`, `SUBAi/SUBAq`, `MSUBAi/MSUBAq`,
  `MADDAi/MADDAq`, `ADDAq` [obs].
* **Q-pipe**: `DIV` 2,667, `RSQRT` 704, `WAITQ` 258; no `SQRT` [obs]. **Clipping**: `clipw` 2,558 with `FCAND` 2,073,
  `FCOR` 816, `FCGET` 426, `FCSET` 80; **MAC flags**: `FMAND` 1,710 [obs].
* **Branches**: 14,751 (`IBEQ` 6,782, `IBNE` 4,333, `B` 2,613, `BAL` 280, `IBLTZ` 249, `IBGEZ` 205, `JR` 176, `IBLEZ` 92,
  `IBGTZ` 21) [obs]. **73 branches in 73 places wrap around the 16 KiB micro memory** (raw targets `0x812`, `-0xd8` ...)
  and land inside their program after `& 0x3FFF`; **0 targets leave the owning program** [der]. `14`'s `br` column
  (sum 15,378) over-counted: it classified raw lower words with opcode `0x20-0x2F` without honouring the I bit, so
  `loi 255.0` (`0x437F0000`, opcode `0x21`) and `loi 2048.5` counted as branches; e.g. `vu1_prog_000` has 2 branches, not 9
  [obs for the counts, inf for the cause].
* **`xgkick`**: 501, up to **12 per program and 12 per `E`-bounded run**; 145 sit inside backward-branch loops; 76
  programs kick more than once per run [der]. Every program (except `null_transform`) reads **`xitop`** and loops over
  that count; **no program loops forever** - each `MSCAL`/`MSCNT` processes one batch and ends with `E` [der, §2].
* **Interpreter scope** (§4): the boot/first-rendered-frame families (`rt2d_*`, `ptank_*`, `null_transform`,
  `g3_generic`) already need **41 of the 43 upper and 43 of the 45 lower mnemonics**; the full game adds only `ADDAi`,
  `MADDi` (both only in the 28 unreferenced programs), `BAL` (matfx families) and `ISWR` (`unknown_tbl4`). There is no
  useful "small subset first" - implement the 43+45 set once. The **first flip needs no VU1 at all** (`10` §5.13).

## 1. Method and verification

* `vu1_decode.py` decodes the 64-bit pair (lower word = bytes 0-3, upper = bytes 4-7 of each little-endian 8-byte unit,
  confirmed by the null program: `0x400002FF/0x8000033C` = `E nop | nop`). Upper: flags I/E/M/D/T = bits 31..27, `dest`
  bits 24-21, `ft/fs/fd` 20-16/15-11/10-6, `funct` 5-0; `funct < 0x3C` is the direct table, otherwise the index
  `fd*4 + (funct & 3)` selects the ACC/special table (`NOP` = index `0x2F`, i.e. `0x2FF`). Lower: opcode bits 31-25;
  `0x40` with `funct < 0x3C` = integer ALU, `0x40` with `funct >= 0x3C` = index `id*4 + (funct & 3)` special table
  (`MOVE 0x30` ... `EEXP 0x7E`), other opcodes = load/store, `IADDIU/ISUBIU` (15-bit immediate
  `((w>>10)&0x7800)|(w&0x7FF)`), flag ops (`FC*` 24-bit, `FS*` 12-bit), branches (`imm11*8` relative to `pc+8`). When the I flag is set the lower word is a float immediate (`LOI`). Undefined encodings
  (upper `funct 0x30-0x3B`, special indices `0x2B`, `0x3x-0x3F`; lower opcodes `0x02/0x03/0x06/0x07/0x0A-0x0F/0x19/0x1D-0x1F/0x22/0x23/0x26/0x27/0x2A/0x2B/0x41+`,
  int functs other than `0x30/31/32/34/35`, unassigned special indices) return `UNKNOWN` with the raw word; the decoder
  never raises (exhaustive opcode/funct/fd sweep in the self-test).
* **Cross-check against `ps2-web-recomp`** (MIT, read-only clone `tools/third_party/_community-eval/ps2-web-recomp`):
  `runtime/src/vu_micro.cpp` functions `decode_upper` (upper funct and special index tables), `lower` (opcode `0x40`
  integer/special index tables and the `w >> 25` opcode switch, 15-bit `IADDIU` immediate split, 12-bit `FS*` split,
  flag/clip immediates, branch target arithmetic `pc + 8 + imm11*8`, `BAL` link = `(pc+16)/8`, `JR` target
  `vi*8`, PC masking with the unit's code mask) and `scan_flags` (I-bit test on the upper word before classifying
  branches). Every table entry we assign matches that source; the only difference is cosmetic (we name the upper
  special index `0x2F` `NOP` explicitly). No text was copied.
* **Self-test**: `python tools/ours/vu1/vu1_decode.py --selftest` - 147 checks (every mnemonic class from a hand-built
  word, flag bits, `LOI`, immediates, wrap-around targets, the 4-unit null program) [obs].
* **Census**: `python tools/ours/vu1/vu1_census.py` (1.8 s) writes the JSON and the GENERATED block below. Branch
  targets are wrapped into the 16 KiB micro memory by the decoder (`vu1_decode.VU1_MICRO_BYTES`), which is what the
  hardware PC does and what `vu_micro.cpp` does with its code mask [obs for our reading of that source].

## 2. Program structure [der]

All 113 non-null programs share one shape (checked on `g3_generic[0] 0x6c2940`, `rt2d_font[0] 0x73cf60`,
`ptank_spr2d[0] 0x5ca720`, `unknown_tbl4[0] 0x5cd820`, `unreferenced 0x5a9770`; the per-program table below gives every
program's `E` positions and resume targets):

1. **Setup at address 0** (`MSCAL 0`): constants from the material block (`lq ... 0x3C0-0x3FF(vi00)`, `loi 255.0`,
   `0.5`, `2048.5`, `1/128`, `1/127`), then it **falls into the batch entry**.
2. **Batch entry** = `xtop viN` (input buffer base, the VIF double-buffer `TOP`) + `xitop viM` (vertex count, `ITOP`).
   The count is scaled by the cluster stride with `iadd` chains, output pointers are set up, and a **vertex loop**
   (`ibne vi06, vi10, ...`) transforms, clips (`clipw.xyz` + `fcand/fcor`), perspective-divides (`div Q, vf00w, vfNNw` +
   `mulq`/`waitq`), converts (`ftoi4` XYZ, `ftoi0` RGBA/ST) and stores GIF-packet qwords. Data-dependent paths (lighting,
   fog, prelit, strip restarts) are chosen by `ibeq/ibne` on flags loaded from VU memory (`ilw.w vi03, 980(vi00)`,
   `fmand` of MAC flags), not by separate programs.
3. **`xgkick`** is issued whenever an output buffer fills, with **two output buffers alternated** (`iadd vi15,vi13;
   iadd vi13,vi14; xgkick vi14; iadd vi14,vi15`), so a run kicks 1-12 packets and keeps writing the other buffer while
   the GIF drains the kicked one. An interpreter that copies the kicked packet out synchronously at `xgkick` is
   therefore safe; one that lets the program overwrite a buffer the GIF has not consumed is not.
4. **End**: one `E` instruction per program in all 86 referenced programs except `ptank_*` (2-3) and the 28 unreferenced
   ones (1-7). The pair after the `E` pair is the **`MSCNT` resume point**: `iaddiu vi15, vi00, <entry>; nop; jr vi15`
   (g3/rt2d families) or a plain `b <entry>` (ptank, `unknown_tbl4`, unreferenced), where `<entry>` is the batch entry
   of step 2 (e.g. `0x27`). In 73 places that `b` is encoded with a raw target outside the program (`b 0x812` -> `0x12`,
   `b -0xd8` -> `0x728`) and relies on the **PC wrapping at 16 KiB** - the interpreter must mask the PC.
5. **Continuations through VU memory**: `g3_*` and `rt2d_*` programs store a return address in data qword `0x3FF.y`
   (`iaddiu vi12, vi00, 0x1a6; isw.y vi12, 1023(vi00)`), reload it (`ilw.y vi12, 1023`) and `jr vi12` after the
   shared vertex-loop subroutine; `g3_matfx`/`g3_skin_matfx` additionally use `bal viN`/`jr viN` (280/68+68)
   subroutines. Because the material UNPACK (`14` V-02: `UNPACK V4-32 x3 -> 0x3FD..0x3FF`) covers `0x3FF`, the EE can
   in principle select that continuation; **VU1 data memory must persist across `MSCAL`/`MSCNT` calls** in the
   interpreter.
6. **Static reachability** from entry 0 plus the resume points, following `jr` through every visible `iaddiu viN,
   vi00, imm` constant and `bal` link, covers 100 % of `rt2d_*`, `ptank_xform`, `unknown_tbl4` and `null_transform`,
   >= 99 % of `ptank_spr*` and the unreferenced set, **93-97 % of the `g3_*` programs and 70-75 % of three of them**
   (`vu1_prog_044`, `066`, `103`). The unreached `g3` ranges (e.g. `0x2c9-0x39b` in `044`) are branched into only from
   inside themselves: dead code of the RW generator, or an alternative loop entered through a continuation value the
   EE writes into `0x3FF` - **unresolved statically** (§5); 0 `jr` lack a visible source.

**Registers**: 76 programs touch all 15 integer registers, every program family except `unknown_tbl4` (9) and
`ptank_spr2d` (12) uses all 15; `vf01-vf31` are all used (max 31 per program). **Immediates**: 1,045 `loi` (255.0 x531,
0.5 x109, 2048.5 x106, 1/128 x74, 2048.0 x68 ...). Dest masks: `xyzw` 28,788, `xyz` 19,638, `w` 9,410, `x` 8,190,
`xyw` 7,019; 16 upper ops have an empty mask (flag-only side effects) [obs].

## 3. Corrections and additions to topic 14 [obs/der]

* `14` §1 `br` column: see §0; use the `branches` field of the JSON instead (14,751 total).
* **Unreferenced programs are not copies of referenced ones.** Nearest referenced program by normalised L1 histogram
  distance is >= 0.47 for all 28 (table below); the 16 small ones (126-419 units) sit nearest `ptank_spr2d`/`spr3d`,
  the 12 large ones (1134-1531 units, 6-7 `E` bits, 5-6 `xgkick`) nearest `g3_generic[4..7]`. They use the older RW
  codegen conventions (`b`-wrap resume instead of `jr`, 244 of the 258 `waitq`, the only `ADDAi`/`MADDi`), consistent
  with `14`'s "linked-but-unused library" reading [inf]. They add no instruction the referenced set lacks except
  `ADDAi`/`MADDi`.
* `unknown_tbl4` (`0x7bcf74`, 4 programs of 41-76 units): single-kick 2D sprite expanders (`xtop/xitop`, per-sprite
  7-qword output, `ftoi4`, GIF EOP via `iswr`), the only users of `ISWR` [obs]; owner still unknown (`14` §7).
* `ptank_xform` programs have 2-3 `E` bits and 1-2 `xgkick`: two entry/resume pairs per program (per-format instance
  code), consistent with `14` §2's TransformInfo reading [der].

## 4. VU1 interpreter scope (Phase 3)

**(a) First flip (M1)**: no VU1 execution (`10` §5.13, `RUNTIME_CONTRACT` B-61: the clear/sprite passes need `MSCAL`
only when a sprite is live). **First rendered frame / Atlus logo (M2) and title (M3)** [inf, from `14` §2 and
`RUNTIME_CONTRACT` L-20 - which families the logo actually `MSCAL`s is unmeasured, Q-21]: `rt2d_stroke/font/fill`
(all UI text/boxes, 6 programs), `ptank_spr2d/spr3d/xform` (particles/sprites, 13), `null_transform` (default node, 1),
and `g3_generic` (6) for any 3-D title scene. That subset needs **41 upper + 43 lower mnemonics** - everything in the
table below except `ADDAi`, `MADDi`, `BAL`, `ISWR`.

**(b) Full game** adds `g3_skin` (6), `g3_matfx`/`g3_skin_matfx`/`g3_skspt_*` (50) and `unknown_tbl4` (4): **43 upper
+ 45 lower**, i.e. the instruction set the interpreter must implement is exactly:

| Class | Must implement | May stub / never occurs in the 114 programs |
|---|---|---|
| Upper FMAC | `ADD/SUB/MUL/MADD/MSUB` in all four forms (vector, `bc`, `i`, `q`); `MAX`, `MAXbc`; `MINI`, `MINIbc`, `MINIi`; `ADDA`, `ADDAbc`, `ADDAi`; `SUBAbc`; `MULA`, `MULAbc`, `MULAi`, `MULAq`; `MADDAbc`; `MSUBAbc`; `OPMULA`, `OPMSUB`, `CLIP`, `ITOF0`, `ITOF4`, `FTOI0`, `FTOI4`, `NOP` (43) | `ABS`, `MAXi`, `ITOF12/15`, `FTOI12/15`, vector `SUBA`/`MADDA`/`MSUBA`, `SUBAi/q`, `MSUBAi/q`, `MADDAi/q`, `ADDAq` (0 uses) |
| Flags | **I** (1,045 `loi`), **E** (192) | **M, D, T** never set: no `MSCALF`-style D/T interrupt handling, no `M` flag (VU0-only anyway) |
| MAC/status/clip flags | MAC flags for `FMAND` (zero/sign per lane); clip flags: `CLIP` producing the 6-bit x3 history read by `FCAND`, `FCOR`, `FCGET`, written by `FCSET` | Status-flag register and sticky bits (`FSEQ/FSSET/FSAND/FSOR` 0 uses), `FMEQ/FMOR/FCEQ` (0) |
| Lower load/store | `LQ`, `SQ`, `LQI`, `SQI`, `LQD`, `SQD`, `ILW`, `ISW`, `ILWR`, `ISWR` (with dest-field lane select for `ILW*/ISW*`) | - |
| Integer | `IADD`, `ISUB`, `IADDI` (4 uses), `IADDIU`, `ISUBIU`, `IAND`, `IOR`, 16-bit `vi` wrap | - |
| Moves | `MOVE`, `MR32`, `MFIR`, `MTIR` | - |
| EFU | **Q pipe**: `DIV`, `RSQRT`, `WAITQ` (and implicit Q reads by `MULq/ADDq/SUBq/MADDq/MSUBq/MULAq`); **P pipe**: `ERCPR` + `MFP` only (g3 families, 62 each) | `SQRT`, `ESADD/ERSADD/ELENG/ERLENG/EATAN*/ESUM/ESQRT/ERSQRT/WAITP/ESIN/EEXP` |
| Branches | `B`, `BAL`, `JR`, `IBEQ`, `IBNE`, `IBLTZ`, `IBGTZ`, `IBLEZ`, `IBGEZ`; one delay slot; **PC & 0x3FFF** on every target | `JALR` (0) |
| VIF interface | `XTOP`, `XITOP` (every program), `XGKICK` with **multiple kicks per run** (up to 12) and **double-buffered output** (§2.3) | `RINIT/RGET/RNEXT/RXOR` (0) |
| Control | `MSCAL addr` (= 0 for the first batch), **`MSCNT` resuming at the pair after the `E` pair**, `E` stopping after one more pair, persistent 16 KiB data memory, `TOP`/`ITOP` from the VIF double-buffer registers (`BASE/OFFSET/TOPS`) | `MSCALF` only as `MSCAL` + flush semantics (its 8 EE sites are PTank/Atlus effect code, `14` §3) |

**Semantics to decide, not just decode** [inf, for Phase 3/4]: (1) Q-pipe latency - RW code places `waitq` or 7+
instructions between `div` and the `mulq` in most places but not all (258 explicit `waitq` vs 3,371 Q producers);
`vu_micro.cpp` models the pipeline with delays (7 for `DIV/SQRT`, 13 for `RSQRT`) and a `begin_q/end_q` pair - the
first interpreter should port that pipeline rather than complete Q immediately, and `tracediff` against PCSX2 decides
whether an immediate-Q simplification is observable. (2) MAC-flag timing for `fmand` after `clipw`/`sub` (the reference
keeps a 4-stage pipe; `g_flags_used` scan). (3) Branch-delay reads of `vi` registers written in the previous slot
(the reference's `branch_vi` snapshot). (4) `xgkick` of a packet whose buffer the program is still filling cannot
happen with RW's double buffering, so a synchronous copy at kick time is correct for these 114 programs.

**HLE outlook**: because every run is "one batch: `xitop` vertices in, 1-12 GIF packets out" with no persistent loop
state beyond the `0x3FF` continuation, per-family HLE of `g3_generic`/`g3_skin`/`rt2d_*` (the `14` §6 order) can be
written as a function of (input buffer, material block `0x3BC-0x3FF`, count) and validated against the interpreter
output packet by packet.

## 5. Open questions

* Which families the logo/title path actually `MSCAL`s (Q-21; PCSX2 `MPG`/`MSCAL` log) - the subset verdict above is
  by family membership, not by trace.
* The statically unreached 3-30 % of each `g3_*` program (§2.6): dead generator output or EE-selected continuation
  through `0x3FF.y`? Needs a PCSX2 VU1 PC trace or a read of the bridge's `0x3FD..0x3FF` UNPACK payload.
* The code-array index bit layout (`14` §7, Q-15) - unchanged.
* Q/P-pipe and MAC-flag timing sensitivity (§4) - Phase 4 `tracediff`.

## Confidence

Instruction totals, mnemonic sets, flag/EFU/branch counts: **high** (byte-level, decoder cross-checked against the
reference source and self-tested; 0 `UNKNOWN`). Program structure (§2): **medium-high** (read on 5 programs, consistent
with the per-program `E`/resume table for all 114). Reachability and dead-code claims: **medium** (static, `jr` targets
over-approximated from visible constants). Boot-path family selection: **inferred** (Q-21). Unreferenced = older
library code: **low-medium**.

<!-- GENERATED:BEGIN (vu1_census.py) -->
_Generated 2026-10-18 20:43:37 by `tools/ours/vu1/vu1_census.py` with `tools/ours/vu1/vu1_decode.py` over `ida/logs/vu1/<code_va>.bin` (114 gitignored dumps named by code VA = tag VA + 0xC, inventory from `symbols/p3fes.sym` rows `vu1_prog_*`). Do not edit inside the markers. Counts are observed (decoder over the dump bytes); E-segments, loops and reachability are static readings._

### Headline

| Metric | Value |
|---|---|
| Programs decoded | 114 |
| 64-bit instructions | 123,095 (984,760 bytes) |
| `UNKNOWN` halves | **0** |
| Distinct upper mnemonics (form-qualified) | 43 |
| Distinct lower mnemonics | 45 |
| Flag bits I / E / M / D / T | 1,045 / 192 / 0 / 0 / 0 |
| `xgkick` | 501 (in a backward-branch loop body: 145; programs with >1 per linear E-segment: 76) |
| Branches | 14,751 (`IBEQ` 6,782, `IBNE` 4,333, `B` 2,613, `BAL` 280, `IBLTZ` 249, `IBGEZ` 205, `JR` 176, `IBLEZ` 92, `IBGTZ` 21); `jr`/`jalr` 176; targets outside the owning program after 16 KiB wrap: **0**; branches whose raw target wraps around micro memory: 73 in 26 programs |
| Static reachability from entry 0 + post-`E` resume points | min coverage 71%; programs fully covered: 44; `jr` with no visible constant/`bal` source: 0 |
| Topic-14-style branch count (opcode 0x20-0x2F, I bit ignored) | 15,573 (over-counts `loi` floats) |
| `clipw` | 2,558 |
| EFU Q-pipe | `DIV` 2,667, `RSQRT` 704, `WAITQ` 258 |
| EFU P-pipe | `ERCPR` 62, `MFP` 62 |
| Flag-register ops | `FCAND` 2,073, `FMAND` 1,710, `FCOR` 816, `FCGET` 426, `FCSET` 80 |
| R ops | - |
| `xtop` / `xitop` | 1,009 / 331 (programs with `xitop`: 113) |
| Programs with backward branches | 114 |
| Integer registers touched (any program) | vi01, vi02, vi03, vi04, vi05, vi06, vi07, vi08, vi09, vi10, vi11, vi12, vi13, vi14, vi15 |

### Upper mnemonics (all programs)

`NOP` 34,156, `MADDbc` 11,915, `ADDbc` 10,050, `MADDAbc` 9,270, `MULAbc` 8,950, `MUL` 6,727, `MULq` 4,045, `ADDAbc` 3,969, `SUB` 3,410, `SUBbc` 3,294, `MULbc` 3,114, `MSUBbc` 2,851, `CLIP` 2,558, `MAX` 2,031, `ITOF0` 1,862, `FTOI0` 1,820, `FTOI4` 1,781, `ADDA` 1,609, `MINIi` 1,552, `ADD` 1,536, `MAXbc` 1,460, `MADDq` 1,233, `MINI` 904, `MULi` 792, `OPMULA` 454, `OPMSUB` 430, `SUBq` 258, `MSUB` 181, `MADD` 161, `SUBi` 120, `MSUBAbc` 114, `MULAi` 100, `ADDi` 98, `MULA` 67, `MINIbc` 55, `ITOF4` 48, `SUBAbc` 24, `MSUBi` 20, `ADDAi` 19, `MADDi` 19, `ADDq` 18, `MULAq` 15, `MSUBq` 5

Forms: `bc` 55,066, `` 16,626, `q` 5,574, `i` 2,720 (`bc` broadcast, `i`/`q` register, empty = vector). Dest masks: `xyzw` 28,788, `xyz` 19,638, `w` 9,410, `x` 8,190, `xyw` 7,019, `z` 6,610, `y` 4,370, `xy` 3,679, `yzw` 550, `zw` 347, `xzw` 124, `yw` 124.

### Lower mnemonics (all programs)

`LQ` 25,724, `NOP` 19,662, `IADDIU` 16,601, `SQ` 9,124, `SQI` 7,483, `IBEQ` 6,782, `IBNE` 4,333, `IADD` 3,165, `LQI` 2,683, `DIV` 2,667, `B` 2,613, `FCAND` 2,073, `MOVE` 1,895, `FMAND` 1,710, `ILW` 1,615, `MR32` 1,513, `IAND` 1,418, `IOR` 1,387, `ISUBIU` 1,283, `LOI` 1,045, `XTOP` 1,009, `ISW` 846, `FCOR` 816, `RSQRT` 704, `MTIR` 542, `LQD` 540, `MFIR` 531, `XGKICK` 501, `FCGET` 426, `ISUB` 422, `XITOP` 331, `BAL` 280, `WAITQ` 258, `IBLTZ` 249, `IBGEZ` 205, `JR` 176, `SQD` 96, `IBLEZ` 92, `FCSET` 80, `ERCPR` 62, `ILWR` 62, `MFP` 62, `IBGTZ` 21, `IADDI` 4, `ISWR` 4

### Per family

| Family | Progs | Units (min-max) | Upper distinct | Lower distinct | E | XGK | br | clipw | EFU Q | EFU P | flag ops | `xitop` | vi regs | UNK |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `g3_generic` | 6 | 7,819 (845-1839) | 37 | 39 | 1-1 | 5-12 | 113-209 | 11-40 | `DIV` 195, `RSQRT` 54, `WAITQ` 2 | `ERCPR` 6, `MFP` 6 | `FMAND` 108, `FCAND` 121, `FCGET` 36, `FCOR` 48, `FCSET` 2 | 6 | 15 | 0 |
| `g3_matfx` | 24 | 36,771 (1271-1944) | 37 | 41 | 1-1 | 4-12 | 190-232 | 29-44 | `DIV` 756, `RSQRT` 216, `WAITQ` 1 | `ERCPR` 24, `MFP` 24 | `FMAND` 533, `FCAND` 683, `FCSET` 6, `FCGET` 136, `FCOR` 288 | 104 | 15 | 0 |
| `g3_skin` | 6 | 8,359 (935-1929) | 37 | 39 | 1-1 | 5-12 | 112-208 | 11-40 | `DIV` 195, `RSQRT` 54, `WAITQ` 2 | `ERCPR` 6, `MFP` 6 | `FMAND` 108, `FCAND` 121, `FCGET` 36, `FCOR` 48, `FCSET` 2 | 18 | 15 | 0 |
| `g3_skin_matfx` | 24 | 38,763 (1361-2020) | 37 | 41 | 1-1 | 4-12 | 189-231 | 29-44 | `DIV` 756, `RSQRT` 216, `WAITQ` 1 | `ERCPR` 24, `MFP` 24 | `FMAND` 533, `FCAND` 683, `FCSET` 6, `FCGET` 136, `FCOR` 288 | 140 | 15 | 0 |
| `g3_skspt_uva` | 2 | 2,000 (956-1044) | 33 | 32 | 1-1 | 5-5 | 113-115 | 11-17 | `DIV` 39, `RSQRT` 18, `WAITQ` 1 | `ERCPR` 2, `MFP` 2 | `FMAND` 20, `FCAND` 8, `FCSET` 1, `FCGET` 10 | 6 | 15 | 0 |
| `null_transform` | 1 | 4 (4-4) | 1 | 2 | 1-1 | 0-0 | 1-1 | 0-0 | - | - | - | 0 | 0 | 0 |
| `ptank_spr2d` | 4 | 478 (106-132) | 21 | 24 | 1-2 | 2-2 | 3-7 | 2-2 | `DIV` 8 | - | `FCSET` 4, `FCAND` 8 | 4 | 12 | 0 |
| `ptank_spr3d` | 4 | 1,182 (263-333) | 20 | 24 | 1-2 | 2-2 | 5-9 | 12-12 | `DIV` 48 | - | `FCSET` 4, `FCAND` 15 | 4 | 15 | 0 |
| `ptank_xform` | 5 | 546 (98-113) | 24 | 25 | 2-3 | 1-2 | 7-11 | 2-4 | `DIV` 18 | - | `FCAND` 5 | 5 | 15 | 0 |
| `rt2d_fill` | 2 | 2,227 (1104-1123) | 29 | 35 | 1-1 | 7-8 | 162-166 | 30-38 | `DIV` 58, `WAITQ` 1 | - | `FCAND` 56, `FCSET` 1, `FCGET` 12, `FCOR` 24, `FMAND` 24 | 4 | 15 | 0 |
| `rt2d_font` | 2 | 2,197 (1089-1108) | 29 | 36 | 1-1 | 7-8 | 160-164 | 30-38 | `DIV` 60, `WAITQ` 3 | - | `FCAND` 56, `FCSET` 1, `FCGET` 12, `FCOR` 24, `FMAND` 24 | 4 | 15 | 0 |
| `rt2d_stroke` | 2 | 2,107 (1044-1063) | 30 | 36 | 1-1 | 7-8 | 160-164 | 30-38 | `DIV` 60, `WAITQ` 3 | - | `FCAND` 56, `FCSET` 1, `FCGET` 12, `FCOR` 24, `FMAND` 24 | 4 | 15 | 0 |
| `unknown_tbl4` | 4 | 226 (41-76) | 8 | 18 | 1-1 | 1-1 | 3-3 | 0-0 | - | - | - | 4 | 9 | 0 |
| `unreferenced` | 28 | 20,416 (126-1531) | 32 | 34 | 1-7 | 1-6 | 2-129 | 2-21 | `DIV` 474, `RSQRT` 146, `WAITQ` 244 | - | `FCSET` 52, `FCAND` 261, `FMAND` 336, `FCGET` 36, `FCOR` 72 | 28 | 15 | 0 |

### Rare mnemonics (used by at most 40 of the 114 programs)

| Mnemonic | Programs | Total | Families |
|---|---|---|---|
| `L:IADDI` | 1 | 4 | `ptank_spr3d` |
| `L:ISWR` | 4 | 4 | `unknown_tbl4` |
| `L:SQD` | 4 | 96 | `rt2d_font`, `rt2d_stroke` |
| `U:MSUBq` | 5 | 5 | `ptank_xform` |
| `U:SUBAbc` | 6 | 24 | `g3_generic`, `g3_skin`, `g3_skspt_uva` |
| `U:ADDAi` | 8 | 19 | `unreferenced` |
| `U:ITOF4` | 8 | 48 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx` |
| `U:MADDi` | 8 | 19 | `unreferenced` |
| `U:ADDq` | 10 | 18 | `rt2d_stroke`, `unreferenced` |
| `U:MULAq` | 11 | 15 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `rt2d_fill`, `rt2d_font`, `rt2d_stroke` |
| `L:IBGTZ` | 17 | 21 | `ptank_spr2d`, `ptank_spr3d`, `ptank_xform`, `unknown_tbl4` |
| `U:MSUB` | 17 | 181 | `ptank_xform`, `unreferenced` |
| `U:MSUBi` | 20 | 20 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `g3_skspt_uva`, `rt2d_fill`, `rt2d_font`, `rt2d_stroke` |
| `U:MINIbc` | 31 | 55 | `g3_matfx`, `g3_skin_matfx`, `ptank_xform`, `unreferenced` |
| `U:OPMSUB` | 34 | 430 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `unreferenced` |
| `U:OPMULA` | 34 | 454 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `unreferenced` |
| `L:WAITQ` | 35 | 258 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `g3_skspt_uva`, `rt2d_fill`, `rt2d_font`, `rt2d_stroke`, `unreferenced` |
| `U:MULAi` | 38 | 100 | `g3_generic`, `g3_matfx`, `g3_skin`, `g3_skin_matfx`, `g3_skspt_uva`, `ptank_spr2d`, `ptank_spr3d`, `rt2d_fill`, `rt2d_font`, `rt2d_stroke` |
| `L:BAL` | 40 | 280 | `g3_matfx`, `g3_skin_matfx` |

### Boot-path subset vs full game

Families taken as the boot path (inferred, see narrative): `rt2d_stroke`, `rt2d_font`, `rt2d_fill`, `g3_generic`, `null_transform`, `ptank_spr2d`, `ptank_spr3d`, `ptank_xform`. They use 41 upper and 43 lower mnemonics. Mnemonics that appear only outside that subset: upper `ADDAi`, `MADDi`; lower `BAL`, `ISWR`.

### Largest / most complex programs

| Program | Family | Units | Upper distinct | Lower distinct | br | back-br | `bal`/`jr` | XGK | E | clipw | EFU | static reach |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `vu1_prog_079_g3_skin_matfx` `0x7253b0` | `g3_skin_matfx` | 2,020 | 34 | 39 | 231 | 46 | 7/3 | 6 | 1 | 44 | 71 | 96% |
| `vu1_prog_071_g3_skin_matfx` `0x70bb00` | `g3_skin_matfx` | 1,979 | 34 | 39 | 229 | 45 | 7/3 | 4 | 1 | 44 | 71 | 96% |
| `vu1_prog_075_g3_skin_matfx` `0x718620` | `g3_skin_matfx` | 1,958 | 33 | 39 | 229 | 45 | 7/3 | 4 | 1 | 44 | 71 | 96% |
| `vu1_prog_107_g3_skin_matfx` `0x773c30` | `g3_skin_matfx` | 1,952 | 33 | 39 | 228 | 46 | 7/3 | 4 | 1 | 44 | 71 | 96% |
| `vu1_prog_101_g3_skin_matfx` `0x7634a0` | `g3_skin_matfx` | 1,950 | 34 | 37 | 209 | 46 | 0/2 | 12 | 1 | 40 | 86 | 97% |
| `vu1_prog_057_g3_matfx` `0x6e3010` | `g3_matfx` | 1,944 | 34 | 39 | 232 | 46 | 7/3 | 6 | 1 | 44 | 71 | 95% |
| `vu1_prog_064_g3_skin` `0x6f8b10` | `g3_skin` | 1,929 | 34 | 37 | 208 | 45 | 0/2 | 12 | 1 | 40 | 86 | 97% |
| `vu1_prog_083_g3_skin_matfx` `0x731f30` | `g3_skin_matfx` | 1,927 | 33 | 39 | 227 | 45 | 7/3 | 4 | 1 | 44 | 71 | 96% |
| `vu1_prog_049_g3_matfx` `0x6caa60` | `g3_matfx` | 1,903 | 34 | 39 | 230 | 45 | 7/3 | 4 | 1 | 44 | 71 | 95% |
| `vu1_prog_053_g3_matfx` `0x6d6c00` | `g3_matfx` | 1,882 | 33 | 39 | 230 | 45 | 7/3 | 4 | 1 | 44 | 71 | 95% |
| `vu1_prog_097_g3_matfx` `0x756e80` | `g3_matfx` | 1,862 | 33 | 39 | 229 | 46 | 7/3 | 4 | 1 | 44 | 71 | 96% |
| `vu1_prog_093_g3_matfx` `0x74b110` | `g3_matfx` | 1,860 | 34 | 37 | 210 | 46 | 0/2 | 12 | 1 | 40 | 86 | 97% |

### Unreferenced programs: nearest referenced program by mnemonic histogram

Distance = L1 of the combined upper+lower histograms / larger instruction count (0 = identical multiset).

| Unreferenced | Units | Nearest referenced | Units | Distance | Mnemonics only in the unreferenced one |
|---|---|---|---|---|---|
| `vu1_prog_000_unreferenced` | 126 | `vu1_prog_031_ptank_spr2d` | 106 | 0.611 | `ADDAbc`, `ADDAi`, `MADDi`, `MAX`, `MINIi`, `MULbc`, `MULq`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:SQI` |
| `vu1_prog_001_unreferenced` | 150 | `vu1_prog_031_ptank_spr2d` | 106 | 0.513 | `ADDAbc`, `ADDAi`, `MADDi`, `MAX`, `MINIi`, `MSUBbc`, `MULbc`, `MULq`, `L:FMAND`, `L:IBNE`, `L:ILW`, `L:LQI`, `L:MFIR`, `L:SQI` |
| `vu1_prog_002_unreferenced` | 146 | `vu1_prog_031_ptank_spr2d` | 106 | 0.514 | `ADDAbc`, `ADDAi`, `MADDi`, `MAX`, `MAXbc`, `MINIi`, `MULbc`, `MULq`, `SUBq`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_003_unreferenced` | 166 | `vu1_prog_029_ptank_spr2d` | 118 | 0.470 | `ADDAbc`, `ADDAi`, `MADDi`, `MAX`, `MAXbc`, `MINIi`, `MSUBbc`, `MULbc`, `MULq`, `SUBq`, `L:FMAND`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_004_unreferenced` | 168 | `vu1_prog_034_ptank_spr3d` | 311 | 0.659 | `ADDAbc`, `ADDAi`, `MADDi`, `MADDq`, `MINIi`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:SQI` |
| `vu1_prog_005_unreferenced` | 204 | `vu1_prog_034_ptank_spr3d` | 311 | 0.605 | `ADDAbc`, `ADDAi`, `MADDi`, `MADDq`, `MINIi`, `MSUBbc`, `L:FMAND`, `L:IBNE`, `L:ILW`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:SQI` |
| `vu1_prog_006_unreferenced` | 341 | `vu1_prog_033_ptank_spr3d` | 275 | 0.674 | `ADDAbc`, `ADDAi`, `MADDi`, `MADDq`, `MAX`, `MAXbc`, `MINIi`, `MULbc`, `SUBq`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:MTIR`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_007_unreferenced` | 252 | `vu1_prog_032_ptank_spr3d` | 333 | 0.586 | `ADDAbc`, `ADDAi`, `MADDi`, `MADDq`, `MAXbc`, `MINIi`, `MSUBbc`, `SUBq`, `L:FMAND`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI` |
| `vu1_prog_008_unreferenced` | 174 | `vu1_prog_035_ptank_spr3d` | 263 | 0.688 | `ADDAbc`, `MADD`, `MADDq`, `MAX`, `MAXbc`, `MINI`, `MINIi`, `MULbc`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_009_unreferenced` | 204 | `vu1_prog_030_ptank_spr2d` | 122 | 0.574 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `MSUBbc`, `L:FMAND`, `L:IBNE`, `L:ILW`, `L:LQI`, `L:MFIR`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_010_unreferenced` | 230 | `vu1_prog_032_ptank_spr3d` | 333 | 0.628 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `SUBq`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_011_unreferenced` | 301 | `vu1_prog_028_ptank_spr2d` | 132 | 0.651 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `MSUBbc`, `SUBq`, `L:FMAND`, `L:IBEQ`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_012_unreferenced` | 285 | `vu1_prog_032_ptank_spr3d` | 333 | 0.589 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_013_unreferenced` | 305 | `vu1_prog_032_ptank_spr3d` | 333 | 0.577 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `MSUBbc`, `L:FMAND`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_014_unreferenced` | 419 | `vu1_prog_032_ptank_spr3d` | 333 | 0.623 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `SUBq`, `L:IBEQ`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_015_unreferenced` | 393 | `vu1_prog_032_ptank_spr3d` | 333 | 0.606 | `ADDAbc`, `MADD`, `MADDq`, `MAXbc`, `MINIi`, `MSUBbc`, `SUBq`, `L:FMAND`, `L:IBNE`, `L:LQI`, `L:MFIR`, `L:MOVE`, `L:RSQRT`, `L:SQI`, `L:WAITQ` |
| `vu1_prog_016_unreferenced` | 1391 | `vu1_prog_044_g3_generic` | 933 | 0.531 | `ADDq`, `MINIbc`, `MSUB`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_017_unreferenced` | 1515 | `vu1_prog_044_g3_generic` | 933 | 0.539 | `ADDq`, `MINIbc`, `MSUB`, `OPMSUB`, `OPMULA`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_018_unreferenced` | 1397 | `vu1_prog_044_g3_generic` | 933 | 0.538 | `ADDq`, `MINIbc`, `MSUB`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_019_unreferenced` | 1429 | `vu1_prog_044_g3_generic` | 933 | 0.537 | `ADDq`, `MINIbc`, `MSUB`, `OPMSUB`, `OPMULA`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_020_unreferenced` | 1134 | `vu1_prog_081_g3_skin_matfx` | 1430 | 0.644 | `MINIbc`, `MSUB`, `L:MTIR`, `L:WAITQ` |
| `vu1_prog_021_unreferenced` | 1150 | `vu1_prog_093_g3_matfx` | 1860 | 0.660 | `MSUB`, `L:FCSET`, `L:WAITQ` |
| `vu1_prog_022_unreferenced` | 1479 | `vu1_prog_103_g3_skspt_uva` | 1044 | 0.517 | `ADDq`, `MINIbc`, `MSUB`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_023_unreferenced` | 1531 | `vu1_prog_103_g3_skspt_uva` | 1044 | 0.515 | `ADDq`, `MINIbc`, `MSUB`, `OPMSUB`, `OPMULA`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_024_unreferenced` | 1485 | `vu1_prog_103_g3_skspt_uva` | 1044 | 0.514 | `ADDq`, `MINIbc`, `MSUB`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_025_unreferenced` | 1517 | `vu1_prog_103_g3_skspt_uva` | 1044 | 0.514 | `ADDq`, `MINIbc`, `MSUB`, `OPMSUB`, `OPMULA`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_026_unreferenced` | 1254 | `vu1_prog_044_g3_generic` | 933 | 0.616 | `MINIbc`, `MSUB`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUB`, `L:ISUBIU`, `L:MTIR` |
| `vu1_prog_027_unreferenced` | 1270 | `vu1_prog_044_g3_generic` | 933 | 0.623 | `MSUB`, `OPMSUB`, `OPMULA`, `L:FCOR`, `L:IBGEZ`, `L:IBLTZ`, `L:ISUB`, `L:ISUBIU`, `L:MTIR` |

### Per program

E pcs / resume: instruction index of each E bit and where the post-E resume code jumps (the batch entry). XGK/E-seg: `xgkick` count per linear E-segment.

| # | tag VA | family | units | E pcs -> resume | I(loi) | XGK | XGK/E-seg | br (back) | bal | jr | wrap | out | clipw | EFU Q | EFU P | flag ops | xtop/xitop | vi | reach | UNK |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 0 | `0x5a1d80` | `unreferenced` | 126 | 0x7a -> 0x1a | 9 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 3 | 3 | 0 | 4 | 1/1 | 7 | 100% | 0 |
| 1 | `0x5a2180` | `unreferenced` | 150 | 0x92 -> 0x26 | 9 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 3 | 3 | 0 | 7 | 1/1 | 10 | 100% | 0 |
| 2 | `0x5a2640` | `unreferenced` | 146 | 0x8e -> 0x20 | 10 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 2 | 7 | 0 | 3 | 1/1 | 10 | 100% | 0 |
| 3 | `0x5a2ae0` | `unreferenced` | 166 | 0xa2 -> 0x2d | 10 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 2 | 6 | 0 | 5 | 1/1 | 12 | 100% | 0 |
| 4 | `0x5a3020` | `unreferenced` | 168 | 0xa4 -> 0x1a | 7 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 3 | 1/1 | 10 | 100% | 0 |
| 5 | `0x5a3570` | `unreferenced` | 204 | 0xc8 -> 0x26 | 7 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 5 | 1/1 | 13 | 100% | 0 |
| 6 | `0x5a3be0` | `unreferenced` | 341 | 0x151 -> 0x20 | 13 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 3 | 8 | 0 | 4 | 1/1 | 12 | 100% | 0 |
| 7 | `0x5a46a0` | `unreferenced` | 252 | 0xf7 -> 0x2d | 10 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 2 | 5 | 0 | 5 | 1/1 | 14 | 100% | 0 |
| 8 | `0x5a4e90` | `unreferenced` | 174 | 0xa9 -> 0x25 | 5 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 3 | 13 | 0 | 4 | 1/1 | 7 | 99% | 0 |
| 9 | `0x5a5410` | `unreferenced` | 204 | 0xc8 -> 0x33 | 5 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 3 | 11 | 0 | 7 | 1/1 | 9 | 100% | 0 |
| 10 | `0x5a5a80` | `unreferenced` | 230 | 0xe2 -> 0x27 | 5 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 3 | 16 | 0 | 4 | 1/1 | 7 | 100% | 0 |
| 11 | `0x5a61c0` | `unreferenced` | 301 | 0x129 -> 0x35 | 5 | 1 | 1/0 | 5 (2) | 0 | 0 | 0 | 0 | 4 | 19 | 0 | 9 | 1/1 | 9 | 100% | 0 |
| 12 | `0x5a6b40` | `unreferenced` | 285 | 0x119 -> 0x25 | 5 | 1 | 1/0 | 2 (2) | 0 | 0 | 0 | 0 | 3 | 10 | 0 | 4 | 1/1 | 9 | 100% | 0 |
| 13 | `0x5a7440` | `unreferenced` | 305 | 0x12d -> 0x33 | 5 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 3 | 13 | 0 | 7 | 1/1 | 11 | 100% | 0 |
| 14 | `0x5a7de0` | `unreferenced` | 419 | 0x19e -> 0x27 | 5 | 1 | 1/0 | 3 (2) | 0 | 0 | 0 | 0 | 4 | 20 | 0 | 5 | 1/1 | 9 | 100% | 0 |
| 15 | `0x5a8b10` | `unreferenced` | 393 | 0x184 -> 0x35 | 5 | 1 | 1/0 | 4 (2) | 0 | 0 | 0 | 0 | 4 | 20 | 0 | 7 | 1/1 | 11 | 100% | 0 |
| 16 | `0x5a9770` | `unreferenced` | 1391 | 0x19e,0x1ed,0x22c,0x26a,0x2c7,0x33e,0x56a -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 126 (47) | 0 | 0 | 1 | 0 | 19 | 69 | 0 | 49 | 1/1 | 13 | 100% | 0 |
| 17 | `0x5ac320` | `unreferenced` | 1515 | 0x1f4,0x244,0x28f,0x2cd,0x343,0x3ba,0x5e6 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 129 (47) | 0 | 0 | 1 | 0 | 19 | 77 | 0 | 64 | 1/1 | 14 | 100% | 0 |
| 18 | `0x5af2b0` | `unreferenced` | 1397 | 0x1bf,0x206,0x252,0x28e,0x303,0x39a,0x570 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 123 (48) | 0 | 0 | 1 | 0 | 19 | 58 | 0 | 49 | 1/1 | 13 | 100% | 0 |
| 19 | `0x5b1e90` | `unreferenced` | 1429 | 0x1b4,0x20f,0x24e,0x299,0x323,0x3ba,0x590 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 125 (48) | 0 | 0 | 1 | 0 | 17 | 59 | 0 | 60 | 1/1 | 15 | 100% | 0 |
| 20 | `0x5b4b70` | `unreferenced` | 1134 | 0xca,0x113,0x160,0x19b,0x242,0x46a -> 0x17 | 2 | 5 | 1/1/1/1/1/0/0 | 110 (37) | 0 | 0 | 1 | 0 | 21 | 50 | 0 | 51 | 1/1 | 15 | 100% | 0 |
| 21 | `0x5b6f10` | `unreferenced` | 1150 | 0xc3,0x10e,0x15d,0x196,0x252,0x47a -> 0x17 | 2 | 5 | 1/1/1/1/1/0/0 | 110 (37) | 0 | 0 | 1 | 0 | 19 | 46 | 0 | 64 | 1/1 | 15 | 100% | 0 |
| 22 | `0x5b9330` | `unreferenced` | 1479 | 0x1f6,0x245,0x284,0x2c2,0x31f,0x396,0x5c2 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 126 (47) | 0 | 0 | 1 | 0 | 19 | 69 | 0 | 49 | 1/1 | 13 | 100% | 0 |
| 23 | `0x5bc1a0` | `unreferenced` | 1531 | 0x205,0x255,0x2a0,0x2de,0x354,0x3cb,0x5f7 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 126 (47) | 0 | 0 | 1 | 0 | 19 | 65 | 0 | 64 | 1/1 | 14 | 100% | 0 |
| 24 | `0x5bf1b0` | `unreferenced` | 1485 | 0x217,0x25e,0x2aa,0x2e6,0x35b,0x3f2,0x5c8 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 123 (48) | 0 | 0 | 1 | 0 | 19 | 58 | 0 | 49 | 1/1 | 13 | 100% | 0 |
| 25 | `0x5c2050` | `unreferenced` | 1517 | 0x20c,0x267,0x2a6,0x2f1,0x37b,0x412,0x5e8 -> 0x12 | 5 | 6 | 1/1/1/1/1/1/0/0 | 125 (48) | 0 | 0 | 2 | 0 | 17 | 59 | 0 | 60 | 1/1 | 15 | 100% | 0 |
| 26 | `0x5c4ff0` | `unreferenced` | 1254 | 0x141,0x18a,0x1d7,0x212,0x2b9,0x4e1 -> 0x15 | 2 | 5 | 1/1/1/1/1/0/0 | 112 (38) | 0 | 0 | 1 | 0 | 21 | 50 | 0 | 51 | 1/1 | 15 | 100% | 0 |
| 27 | `0x5c7750` | `unreferenced` | 1270 | 0x13a,0x185,0x1d5,0x20e,0x2ca,0x4f2 -> 0x15 | 2 | 5 | 1/1/1/1/1/0/0 | 112 (38) | 0 | 0 | 1 | 0 | 19 | 46 | 0 | 64 | 1/1 | 15 | 100% | 0 |
| 28 | `0x5c9f30` | `ptank_spr2d` | 132 | 0x7b,0x7f -> 0x25,0x7f | 2 | 2 | 2/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 3 | 1/1 | 12 | 99% | 0 |
| 29 | `0x5ca360` | `ptank_spr2d` | 118 | 0x6d,0x71 -> 0x20,0x71 | 1 | 2 | 2/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 3 | 1/1 | 11 | 99% | 0 |
| 30 | `0x5ca720` | `ptank_spr2d` | 122 | 0x75 -> 0x25 | 2 | 2 | 2/0 | 3 (2) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 3 | 1/1 | 11 | 99% | 0 |
| 31 | `0x5cab00` | `ptank_spr2d` | 106 | 0x66 -> 0x1f | 1 | 2 | 2/0 | 3 (2) | 0 | 0 | 0 | 0 | 2 | 2 | 0 | 3 | 1/1 | 9 | 100% | 0 |
| 32 | `0x5cae60` | `ptank_spr3d` | 333 | 0x145,0x149 -> 0x25,0x149 | 2 | 2 | 2/0/0 | 9 (3) | 0 | 0 | 0 | 0 | 12 | 12 | 0 | 4 | 1/1 | 15 | 100% | 0 |
| 33 | `0x5cb8e0` | `ptank_spr3d` | 275 | 0x10a,0x10e -> 0x21,0x10e | 1 | 2 | 2/0/0 | 9 (3) | 0 | 0 | 0 | 0 | 12 | 12 | 0 | 5 | 1/1 | 12 | 100% | 0 |
| 34 | `0x5cc190` | `ptank_spr3d` | 311 | 0x133 -> 0x25 | 2 | 2 | 2/0 | 5 (2) | 0 | 0 | 0 | 0 | 12 | 12 | 0 | 5 | 1/1 | 13 | 100% | 0 |
| 35 | `0x5ccb60` | `ptank_spr3d` | 263 | 0x103 -> 0x20 | 1 | 2 | 2/0 | 5 (2) | 0 | 0 | 0 | 0 | 12 | 12 | 0 | 5 | 1/1 | 10 | 100% | 0 |
| 36 | `0x5cd3b0` | `unknown_tbl4` | 62 | 0x3a -> 0x6 | 0 | 1 | 1/0 | 3 (2) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1/1 | 8 | 100% | 0 |
| 37 | `0x5cd5b0` | `unknown_tbl4` | 76 | 0x48 -> 0x6 | 0 | 1 | 1/0 | 3 (2) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1/1 | 9 | 100% | 0 |
| 38 | `0x5cd820` | `unknown_tbl4` | 41 | 0x25 -> 0x1 | 0 | 1 | 1/0 | 3 (2) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1/1 | 6 | 100% | 0 |
| 39 | `0x5cd980` | `unknown_tbl4` | 47 | 0x2b -> 0x1 | 0 | 1 | 1/0 | 3 (2) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1/1 | 6 | 100% | 0 |
| 40 | `0x5cdb10` | `null_transform` | 4 | 0x0 -> 0x0 | 0 | 0 | 0/0 | 1 (1) | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0/0 | 0 | 100% | 0 |
| 41 | `0x6b5e90` | `g3_generic` | 1487 | 0x5cb -> 0x20,0x25 | 14 | 8 | 8/0 | 209 (41) | 0 | 2 | 0 | 0 | 35 | 26 | 2 | 71 | 9/1 | 15 | 96% | 0 |
| 42 | `0x6b8d40` | `g3_generic` | 1839 | 0x72b -> 0x33 | 11 | 12 | 12/0 | 209 (45) | 0 | 2 | 5 | 0 | 40 | 84 | 2 | 80 | 10/1 | 15 | 97% | 0 |
| 43 | `0x6bc700` | `g3_generic` | 845 | 0x349 -> 0x1,0x3,0x7,0xf,0x1f,0x22,0x3f | 7 | 5 | 5/0 | 113 (21) | 0 | 2 | 0 | 0 | 17 | 18 | 2 | 18 | 8/1 | 15 | 92% | 0 |
| 44 | `0x6be190` | `g3_generic` | 933 | 0x3a1 -> 0x1,0x3,0x7,0xf,0x1f,0x27,0x3f | 7 | 5 | 5/0 | 115 (22) | 0 | 2 | 0 | 0 | 11 | 40 | 2 | 21 | 9/1 | 15 | 71% | 0 |
| 45 | `0x6bfee0` | `g3_generic` | 1348 | 0x540 -> 0x22 | 8 | 7 | 7/0 | 193 (40) | 0 | 2 | 0 | 0 | 38 | 26 | 2 | 64 | 10/1 | 15 | 95% | 0 |
| 46 | `0x6c2940` | `g3_generic` | 1367 | 0x553 -> 0x27 | 8 | 8 | 8/0 | 189 (41) | 0 | 2 | 0 | 0 | 30 | 57 | 2 | 61 | 11/1 | 15 | 95% | 0 |
| 47 | `0x6c5430` | `g3_matfx` | 1406 | 0x514 -> 0x28,0x1bc,0x1e6,0x218,0x247,0x287,0x3cb | 11 | 4 | 0/4 | 194 (41) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 13/5 | 15 | 93% | 0 |
| 48 | `0x6c8060` | `g3_matfx` | 1337 | 0x4cf -> 0x25,0x1b9,0x1e2,0x210,0x247,0x388 | 11 | 4 | 0/4 | 192 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 12/5 | 15 | 93% | 0 |
| 49 | `0x6caa60` | `g3_matfx` | 1903 | 0x705 -> 0x20,0x36,0x1ca,0x211,0x24a,0x2a4,0x2e9,0x343,0x37f,0x3e9,0x437,0x5a4 | 17 | 4 | 0/4 | 230 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 12/5 | 15 | 95% | 0 |
| 50 | `0x6ce620` | `g3_matfx` | 1550 | 0x5a4 -> 0x20,0x28,0x1bc,0x208,0x243,0x29d,0x2e5,0x44b | 19 | 4 | 0/4 | 217 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 11/5 | 15 | 94% | 0 |
| 51 | `0x6d16d0` | `g3_matfx` | 1390 | 0x513 -> 0x28,0x1bc,0x1e4,0x216,0x245,0x286,0x3ca | 12 | 4 | 0/4 | 194 (41) | 7 | 3 | 0 | 0 | 29 | 39 | 2 | 61 | 13/5 | 15 | 93% | 0 |
| 52 | `0x6d4280` | `g3_matfx` | 1320 | 0x4cd -> 0x25,0x1b9,0x1e2,0x20e,0x245,0x386 | 12 | 4 | 0/4 | 190 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 12/5 | 15 | 93% | 0 |
| 53 | `0x6d6c00` | `g3_matfx` | 1882 | 0x6ff -> 0x20,0x36,0x1ca,0x20e,0x245,0x29e,0x2e3,0x33d,0x379,0x3e3,0x431,0x59e | 18 | 4 | 0/4 | 230 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 12/5 | 15 | 95% | 0 |
| 54 | `0x6da720` | `g3_matfx` | 1534 | 0x5a3 -> 0x20,0x28,0x1bc,0x208,0x242,0x29c,0x2e4,0x44a | 20 | 4 | 0/4 | 216 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 11/5 | 15 | 94% | 0 |
| 55 | `0x6dd750` | `g3_matfx` | 1447 | 0x514 -> 0x28,0x1bc,0x1e6,0x218,0x247,0x287,0x3cb | 12 | 6 | 0/6 | 196 (42) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 13/5 | 15 | 93% | 0 |
| 56 | `0x6e04c0` | `g3_matfx` | 1378 | 0x4cf -> 0x25,0x1b9,0x1e2,0x210,0x247,0x388 | 12 | 6 | 0/6 | 194 (41) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 12/5 | 15 | 93% | 0 |
| 57 | `0x6e3010` | `g3_matfx` | 1944 | 0x705 -> 0x20,0x36,0x1ca,0x211,0x24a,0x2a4,0x2e9,0x343,0x37f,0x3e9,0x437,0x5a4 | 18 | 6 | 0/6 | 232 (46) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 12/5 | 15 | 95% | 0 |
| 58 | `0x6e6d20` | `g3_matfx` | 1591 | 0x5a4 -> 0x20,0x28,0x1bc,0x208,0x243,0x29d,0x2e5,0x44b | 20 | 6 | 0/6 | 219 (42) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 11/5 | 15 | 94% | 0 |
| 59 | `0x6e9f20` | `g3_matfx` | 1340 | 0x4eb -> 0x28,0x1a7,0x1d1,0x203,0x232,0x272,0x3af | 11 | 4 | 0/4 | 192 (41) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 13/5 | 15 | 94% | 0 |
| 60 | `0x6ec940` | `g3_matfx` | 1271 | 0x4a6 -> 0x25,0x1a4,0x1cd,0x1fb,0x232,0x36c | 11 | 4 | 0/4 | 190 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 12/5 | 15 | 94% | 0 |
| 61 | `0x6ef130` | `g3_matfx` | 1837 | 0x6dc -> 0x20,0x36,0x1b5,0x1fc,0x235,0x28f,0x2d4,0x32e,0x36a,0x3d4,0x422,0x588 | 17 | 4 | 0/4 | 228 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 12/5 | 15 | 96% | 0 |
| 62 | `0x6f2ae0` | `g3_matfx` | 1484 | 0x57b -> 0x20,0x28,0x1a7,0x1f3,0x22e,0x288,0x2d0,0x42f | 19 | 4 | 0/4 | 215 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 11/5 | 15 | 95% | 0 |
| 63 | `0x6f5980` | `g3_skin` | 1577 | 0x625 -> 0x20,0x25 | 14 | 8 | 8/0 | 208 (41) | 0 | 2 | 0 | 0 | 35 | 26 | 2 | 71 | 15/3 | 15 | 97% | 0 |
| 64 | `0x6f8b10` | `g3_skin` | 1929 | 0x785 -> 0x33 | 11 | 12 | 12/0 | 208 (45) | 0 | 2 | 5 | 0 | 40 | 84 | 2 | 80 | 16/3 | 15 | 97% | 0 |
| 65 | `0x6fc7a0` | `g3_skin` | 935 | 0x3a3 -> 0x1,0x3,0x7,0xf,0x1f,0x22,0x3f | 7 | 5 | 5/0 | 112 (21) | 0 | 2 | 0 | 0 | 17 | 18 | 2 | 18 | 14/3 | 15 | 94% | 0 |
| 66 | `0x6fe500` | `g3_skin` | 1023 | 0x3fb -> 0x1,0x3,0x7,0xf,0x1f,0x27,0x3f | 7 | 5 | 5/0 | 114 (22) | 0 | 2 | 0 | 0 | 11 | 40 | 2 | 21 | 15/3 | 15 | 74% | 0 |
| 67 | `0x700520` | `g3_skin` | 1438 | 0x59a -> 0x22 | 8 | 7 | 7/0 | 192 (40) | 0 | 2 | 0 | 0 | 38 | 26 | 2 | 64 | 16/3 | 15 | 96% | 0 |
| 68 | `0x703250` | `g3_skin` | 1457 | 0x5ad -> 0x27 | 8 | 8 | 8/0 | 188 (41) | 0 | 2 | 0 | 0 | 30 | 57 | 2 | 61 | 17/3 | 15 | 96% | 0 |
| 69 | `0x706010` | `g3_skin_matfx` | 1482 | 0x560 -> 0x28,0x208,0x232,0x264,0x293,0x2d3,0x417 | 12 | 4 | 0/4 | 193 (41) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 19/6 | 15 | 95% | 0 |
| 70 | `0x708ea0` | `g3_skin_matfx` | 1413 | 0x51b -> 0x25,0x205,0x22e,0x25c,0x293,0x3d4 | 12 | 4 | 0/4 | 191 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 18/6 | 15 | 94% | 0 |
| 71 | `0x70bb00` | `g3_skin_matfx` | 1979 | 0x751 -> 0x20,0x36,0x216,0x25d,0x296,0x2f0,0x335,0x38f,0x3cb,0x435,0x483,0x5f0 | 18 | 4 | 0/4 | 229 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 18/6 | 15 | 96% | 0 |
| 72 | `0x70f920` | `g3_skin_matfx` | 1626 | 0x5f0 -> 0x20,0x28,0x208,0x254,0x28f,0x2e9,0x331,0x497 | 20 | 4 | 0/4 | 216 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 17/6 | 15 | 95% | 0 |
| 73 | `0x712c30` | `g3_skin_matfx` | 1466 | 0x55f -> 0x28,0x208,0x230,0x262,0x291,0x2d2,0x416 | 13 | 4 | 0/4 | 193 (41) | 7 | 3 | 0 | 0 | 29 | 39 | 2 | 61 | 19/6 | 15 | 95% | 0 |
| 74 | `0x715a40` | `g3_skin_matfx` | 1396 | 0x519 -> 0x25,0x205,0x22e,0x25a,0x291,0x3d2 | 13 | 4 | 0/4 | 189 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 18/6 | 15 | 94% | 0 |
| 75 | `0x718620` | `g3_skin_matfx` | 1958 | 0x74b -> 0x20,0x36,0x216,0x25a,0x291,0x2ea,0x32f,0x389,0x3c5,0x42f,0x47d,0x5ea | 19 | 4 | 0/4 | 229 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 18/6 | 15 | 96% | 0 |
| 76 | `0x71c3a0` | `g3_skin_matfx` | 1610 | 0x5ef -> 0x20,0x28,0x208,0x254,0x28e,0x2e8,0x330,0x496 | 21 | 4 | 0/4 | 215 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 17/6 | 15 | 95% | 0 |
| 77 | `0x71f630` | `g3_skin_matfx` | 1523 | 0x560 -> 0x28,0x208,0x232,0x264,0x293,0x2d3,0x417 | 13 | 6 | 0/6 | 195 (42) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 19/6 | 15 | 95% | 0 |
| 78 | `0x722600` | `g3_skin_matfx` | 1454 | 0x51b -> 0x25,0x205,0x22e,0x25c,0x293,0x3d4 | 13 | 6 | 0/6 | 193 (41) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 18/6 | 15 | 94% | 0 |
| 79 | `0x7253b0` | `g3_skin_matfx` | 2020 | 0x751 -> 0x20,0x36,0x216,0x25d,0x296,0x2f0,0x335,0x38f,0x3cb,0x435,0x483,0x5f0 | 19 | 6 | 0/6 | 231 (46) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 18/6 | 15 | 96% | 0 |
| 80 | `0x729320` | `g3_skin_matfx` | 1667 | 0x5f0 -> 0x20,0x28,0x208,0x254,0x28f,0x2e9,0x331,0x497 | 21 | 6 | 0/6 | 218 (42) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 17/6 | 15 | 95% | 0 |
| 81 | `0x72c780` | `g3_skin_matfx` | 1430 | 0x545 -> 0x28,0x201,0x22b,0x25d,0x28c,0x2cc,0x409 | 11 | 4 | 0/4 | 191 (41) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 19/7 | 15 | 95% | 0 |
| 82 | `0x72f470` | `g3_skin_matfx` | 1361 | 0x500 -> 0x25,0x1fe,0x227,0x255,0x28c,0x3c6 | 11 | 4 | 0/4 | 189 (40) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 18/7 | 15 | 95% | 0 |
| 83 | `0x731f30` | `g3_skin_matfx` | 1927 | 0x736 -> 0x20,0x36,0x20f,0x256,0x28f,0x2e9,0x32e,0x388,0x3c4,0x42e,0x47c,0x5e2 | 17 | 4 | 0/4 | 227 (45) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 18/7 | 15 | 96% | 0 |
| 84 | `0x735bb0` | `g3_skin_matfx` | 1574 | 0x5d5 -> 0x20,0x28,0x201,0x24d,0x288,0x2e2,0x32a,0x489 | 19 | 4 | 0/4 | 214 (41) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 17/7 | 15 | 96% | 0 |
| 85 | `0x738d20` | `rt2d_stroke` | 1063 | 0x423 -> 0x27 | 6 | 8 | 8/0 | 160 (27) | 0 | 2 | 0 | 0 | 30 | 47 | 0 | 57 | 11/2 | 15 | 100% | 0 |
| 86 | `0x73ae90` | `rt2d_stroke` | 1044 | 0x410 -> 0x22 | 6 | 7 | 7/0 | 164 (26) | 0 | 2 | 0 | 0 | 38 | 16 | 0 | 60 | 10/2 | 15 | 100% | 0 |
| 87 | `0x73cf60` | `rt2d_font` | 1108 | 0x450 -> 0x27 | 6 | 8 | 8/0 | 160 (27) | 0 | 2 | 0 | 0 | 30 | 47 | 0 | 57 | 11/2 | 15 | 100% | 0 |
| 88 | `0x73f230` | `rt2d_font` | 1089 | 0x43d -> 0x22 | 6 | 7 | 7/0 | 164 (26) | 0 | 2 | 0 | 0 | 38 | 16 | 0 | 60 | 10/2 | 15 | 100% | 0 |
| 89 | `0x741470` | `rt2d_fill` | 1123 | 0x45f -> 0x27 | 6 | 8 | 8/0 | 162 (27) | 0 | 2 | 0 | 0 | 30 | 45 | 0 | 57 | 11/2 | 15 | 100% | 0 |
| 90 | `0x7437c0` | `rt2d_fill` | 1104 | 0x44c -> 0x22 | 6 | 7 | 7/0 | 166 (26) | 0 | 2 | 0 | 0 | 38 | 14 | 0 | 60 | 10/2 | 15 | 100% | 0 |
| 91 | `0x745a70` | `g3_matfx` | 1388 | 0x568 -> 0x27 | 8 | 8 | 8/0 | 190 (42) | 0 | 2 | 0 | 0 | 30 | 57 | 2 | 61 | 12/1 | 15 | 95% | 0 |
| 92 | `0x748610` | `g3_matfx` | 1369 | 0x555 -> 0x22 | 8 | 7 | 7/0 | 194 (41) | 0 | 2 | 0 | 0 | 38 | 26 | 2 | 64 | 11/1 | 15 | 95% | 0 |
| 93 | `0x74b110` | `g3_matfx` | 1860 | 0x740 -> 0x33 | 11 | 12 | 12/0 | 210 (46) | 0 | 2 | 5 | 0 | 40 | 84 | 2 | 80 | 11/1 | 15 | 97% | 0 |
| 94 | `0x74eb80` | `g3_matfx` | 1508 | 0x5e0 -> 0x20,0x25 | 14 | 8 | 8/0 | 210 (42) | 0 | 2 | 0 | 0 | 35 | 26 | 2 | 71 | 10/1 | 15 | 96% | 0 |
| 95 | `0x751ae0` | `g3_matfx` | 1365 | 0x500 -> 0x28,0x1bc,0x1e6,0x218,0x247,0x287,0x3c4 | 11 | 4 | 0/4 | 193 (42) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 14/5 | 15 | 94% | 0 |
| 96 | `0x7545c0` | `g3_matfx` | 1296 | 0x4bb -> 0x25,0x1b9,0x1e2,0x210,0x247,0x381 | 11 | 4 | 0/4 | 191 (41) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 13/5 | 15 | 94% | 0 |
| 97 | `0x756e80` | `g3_matfx` | 1862 | 0x6f1 -> 0x20,0x36,0x1ca,0x211,0x24a,0x2a4,0x2e9,0x343,0x37f,0x3e9,0x437,0x59d | 17 | 4 | 0/4 | 229 (46) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 13/5 | 15 | 96% | 0 |
| 98 | `0x75a900` | `g3_matfx` | 1509 | 0x590 -> 0x20,0x28,0x1bc,0x208,0x243,0x29d,0x2e5,0x444 | 19 | 4 | 0/4 | 216 (42) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 12/5 | 15 | 95% | 0 |
| 99 | `0x75d860` | `g3_skin_matfx` | 1478 | 0x5c2 -> 0x27 | 8 | 8 | 8/0 | 189 (42) | 0 | 2 | 0 | 0 | 30 | 57 | 2 | 61 | 18/3 | 15 | 96% | 0 |
| 100 | `0x7606d0` | `g3_skin_matfx` | 1459 | 0x5af -> 0x22 | 8 | 7 | 7/0 | 193 (41) | 0 | 2 | 0 | 0 | 38 | 26 | 2 | 64 | 17/3 | 15 | 96% | 0 |
| 101 | `0x7634a0` | `g3_skin_matfx` | 1950 | 0x79a -> 0x33 | 11 | 12 | 12/0 | 209 (46) | 0 | 2 | 5 | 0 | 40 | 84 | 2 | 80 | 17/3 | 15 | 97% | 0 |
| 102 | `0x7671e0` | `g3_skin_matfx` | 1598 | 0x63a -> 0x20,0x25 | 14 | 8 | 8/0 | 209 (42) | 0 | 2 | 0 | 0 | 35 | 26 | 2 | 71 | 16/3 | 15 | 97% | 0 |
| 103 | `0x76a410` | `g3_skspt_uva` | 1044 | 0x410 -> 0x1,0x3,0x7,0xf,0x1f,0x27,0x3f | 7 | 5 | 5/0 | 115 (23) | 0 | 2 | 0 | 0 | 11 | 40 | 2 | 21 | 16/3 | 15 | 75% | 0 |
| 104 | `0x76c4e0` | `g3_skspt_uva` | 956 | 0x3b8 -> 0x1,0x3,0x7,0xf,0x1f,0x22,0x3f | 7 | 5 | 5/0 | 113 (22) | 0 | 2 | 0 | 0 | 17 | 18 | 2 | 18 | 15/3 | 15 | 94% | 0 |
| 105 | `0x76e2f0` | `g3_skin_matfx` | 1455 | 0x55a -> 0x28,0x216,0x240,0x272,0x2a1,0x2e1,0x41e | 11 | 4 | 0/4 | 192 (42) | 7 | 3 | 0 | 0 | 32 | 39 | 2 | 61 | 20/7 | 15 | 95% | 0 |
| 106 | `0x7710a0` | `g3_skin_matfx` | 1386 | 0x515 -> 0x25,0x213,0x23c,0x26a,0x2a1,0x3db | 11 | 4 | 0/4 | 190 (41) | 7 | 3 | 0 | 0 | 29 | 24 | 2 | 60 | 19/7 | 15 | 95% | 0 |
| 107 | `0x773c30` | `g3_skin_matfx` | 1952 | 0x74b -> 0x20,0x36,0x224,0x26b,0x2a4,0x2fe,0x343,0x39d,0x3d9,0x443,0x491,0x5f7 | 17 | 4 | 0/4 | 228 (46) | 7 | 3 | 4 | 0 | 44 | 69 | 2 | 81 | 19/7 | 15 | 96% | 0 |
| 108 | `0x777980` | `g3_skin_matfx` | 1599 | 0x5ea -> 0x20,0x28,0x216,0x262,0x29d,0x2f7,0x33f,0x49e | 19 | 4 | 0/4 | 215 (42) | 7 | 3 | 0 | 0 | 31 | 24 | 2 | 72 | 18/7 | 15 | 96% | 0 |
| 109 | `0x77cb40` | `ptank_xform` | 113 | 0x5c,0x61,0x6d -> 0x6d | 4 | 2 | 1/0/1/0 | 11 (4) | 0 | 0 | 0 | 0 | 4 | 4 | 0 | 1 | 1/1 | 15 | 100% | 0 |
| 110 | `0x77cee0` | `ptank_xform` | 98 | 0x59,0x5e -> 0x5e | 4 | 1 | 1/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 4 | 4 | 0 | 1 | 1/1 | 13 | 100% | 0 |
| 111 | `0x77d200` | `ptank_xform` | 112 | 0x67,0x6c -> 0x6c | 4 | 1 | 1/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 2 | 3 | 0 | 1 | 1/1 | 13 | 100% | 0 |
| 112 | `0x77d590` | `ptank_xform` | 110 | 0x65,0x6a -> 0x6a | 4 | 1 | 1/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 2 | 4 | 0 | 1 | 1/1 | 13 | 100% | 0 |
| 113 | `0x77d910` | `ptank_xform` | 113 | 0x68,0x6d -> 0x6d | 4 | 1 | 1/0/0 | 7 (3) | 0 | 0 | 0 | 0 | 2 | 3 | 0 | 1 | 1/1 | 13 | 100% | 0 |

<!-- GENERATED:END -->
