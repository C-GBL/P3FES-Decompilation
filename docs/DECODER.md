# Decoder coverage decision for the Phase 3 recompiler

_2026-10-18. Resolves the deferred clause of ADR-0010 §1 ("rabbitizer's R5900 tables (MIT) if a census pass proves
them complete on our MMI/COP2 instructions, otherwise our own table"). Evidence: `docs/ANALYSIS/08_instruction_census.md`,
`symbols/insn_census.json`. Observed facts are labelled; everything under "Recommendation" is inferred._

## 1. What the binary needs decoded (observed)

The 1,194,277 instruction words inside the 14,420 IDA functions use **199 base mnemonics** (VU0 dest/broadcast
suffixes and `pmfhl.*` folded): 64 integer core, 49 MMI (incl. `lq`/`sq`, `mfsa`/`mtsa`/`mtsab`/`mtsah`, `mult1`/
`div1`/`mfhi1`/`mflo1`/`mthi1`/`mtlo1`/`madd`/`maddu`/`maddu1`, one `pmfhl` form: `pmfhl.lw`), 29 COP1, 7 COP0
(`sync.l`/`sync.p`, `mfc0`, `mtc0`, `cache`, `ei`, `di`, `eret`), 6 COP2 transfers, 24 VU0 macro bases in 47
broadcast forms, 7 branches (incl. `bc0f`), 6 likely branches, 4 jumps, 2 traps. Absent: every `vcallms*`, `vlqi`/
`vsqi`/`vlqd`/`vsqd`, `vilwr`/`viswr`, `vclip`, `vdiv`, `vmtir`/`vmfir`, VU random ops, VU integer ops, `bc2*`,
`bc0t/fl/tl`, TLB ops, `pref`, `pmthl`, `pmfhl.uw/.slw/.lh/.sh`, `rsqrt.s`, `max.s`/`min.s`, `c.f.s`, `bltzall`/
`bgezall`, `ll`/`sc`, `dmult`/`ddiv`, any double-precision FPU op. Full tables: `08` §1 and the generated block.

## 2. Candidates checked (observed)

### 2.1 `Decompollaborate/rabbitizer` — clone `tools/third_party/_community-eval/rabbitizer/` (gitignored)

Commit `724a49a5b4dbfb99f1a9e6992e63964fd29c90c8` (2026-05-29), version 1.16.2, **MIT** (c) 2022 Decompollaborate.
C11 library (32 `.c` files, 8,641 lines, `Makefile`, `-std=c11`, no CMake, one `_MSC_VER` branch in
`include/common/Utils.h`, 9 `__attribute__` uses) with a C++17 wrapper (`cplusplus/`), Rust crate and Python
extension. Instruction identity is table-driven: `tables/tables/instr_id/cpu/*.inc` (generic MIPS) plus
`tables/tables/instr_id/r5900/*.inc` (18 files: `normal`, `special`, `regimm`, `mmi`, `mmi_0..3`, `mmi_pmfhl`,
`mmi_pmthl`, `cop0_tlb`, `cop1_fpu_s`, `cop2_ni`, `cop2_i`, `cop2_bc2`, `cop2_special1`, `cop2_special2`,
`cop2_viwr`). `RabbitizerInstructionR5900_processUniqueId*` consults the R5900 table first and **falls back to the
generic `cpu` tables** for every opcode the R5900 file does not override (`src/instructions/RabbitizerInstructionR5900/
RabbitizerInstructionR5900_ProcessUniqueId.c`). Combined set: 610 instruction IDs.

Diff against the census (`scratchpad rab_diff.py`, result reproduced here):

| Census mnemonics | rabbitizer | Note |
|---|---|---|
| 196 of 199 | present under the same name (88 from `r5900/`, 108 from `cpu/`) | incl. `pmfhl.lw` (own ID), `sync.p` (own ID), `pexew`, `mtsab`/`mtsah`, `madd1`, all 24 VU0 bases, all 47 broadcast forms (`vaddx`, `vmadday`, `vmsubaz`...), `vsqrt`, `ei`/`di`, `cache`, `bc0f` |
| `qmfc2` (93), `qmtc2` (481) | only as `qmfc2.ni`/`qmfc2.i`, `qmtc2.ni`/`qmtc2.i` | the interlock bit (bit 0) is part of the ID; our 574 words all have it clear (`.ni`); `cfc2`/`ctc2` exist both plain (cpu) and `.i` |
| `sync.l` (353) | as plain `sync` (cpu table); `sync.p` is the R5900 override | naming only |
| **missing: 0** | | |

Operand-format differences that matter to an emitter (observed from the `.inc` files and
`include/instructions/RabbitizerInstructionR5900.h`): the VU0 **dest field is an operand type**
(`RAB_OPERAND_r5900_vfdxyzw`) with the suffix `RABINSTRSUFFIX_R5900_xyzw`, while the **broadcast field is in the
mnemonic** (`vaddx`...); `pmfhl.*` variants are five separate IDs; `vilwr`/`viswr` are 16 dest-specific IDs
(`cop2_viwr.inc`); field accessors exist for `vfs/vft/vfd`, `xyzw_x..w`, `fhi_flo`, `cop2_highlowbit`. Mis-categorisation
risk: the `cpu` fallback **accepts words the EE does not implement** (`ll`, `sc`, `lld`, `scd`, `dmult`, `dmultu`,
`ddiv`, `ddivu`, `ldc1`, `sdc1`, `lwc2`, `swc2`, `add.d`, `cvt.d.s`, `tlbp`...); none occurs in our 1,194,277 words,
but a decoder built on it would not flag them.

### 2.2 `ps2-web-recomp/recomp/r5900.cpp` (MIT, `tools/third_party/_community-eval/ps2-web-recomp`, @ `c0f476e`)

254 lines; pure `constexpr std::array<Op, N>` lookup by major opcode / `funct` / `rs` / `sa` and four `kVectorX`
sub-tables; `Op` is an enum (`R5900_OPS` X-macro in `r5900.hpp`) with `Insn` field accessors (`rs/rt/rd/sa/fd/dest/bc/imm5/imm15`).
Coverage of our 199: **all present**; `Pmfhl` is one op (the `sa` field selects `.lw/.uw/.slw/.lh/.sh`), `Sync`
is one op (no `.l`/`.p` split), `Qmfc2`/`Qmtc2`/`Cfc2`/`Ctc2` are one op each (interlock bit read from the word),
VU dest/bc are fields (`dest()`, `bc()`), broadcast ops are `Vaddbc`-style single IDs. It rejects every non-EE word
(`Invalid`). No disassembly text, no register tracking — exactly the shape an emitter consumes.

### 2.3 Our table (`tools/ours/ida/insn_census.py` `decode()`)

The census decoder: ~70 lines of tables in the same layout as 2.2 (so the two can be diffed row by row) plus a 60-line
`decode()`. Validated on the whole binary: 0 invalid words; **1,194,269 / 1,194,277 words agree with ps2dev binutils
2.45.1 `objdump -d`** after binutils pseudo-op aliases; the 8 disagreements are `vsqrt` words (`0x3262ec`, `0x329cf0`,
`0x32f000`...) that binutils cannot name (prints a raw `c2` word) while rabbitizer and 2.2 agree with us; and every
name agrees with rabbitizer's except the three naming conventions above.

### 2.4 Not candidates (observed)

* **IDA 9.3 `r5900l`**: renders all 2,960 VU0 macro words as `cop2 <imm>`, misnames 201 `bc0f` as `mfthc1 $ra,$f0`
  and 9 `pexew` as `pexow`, and fuses 16,389 words into 8-24 byte macro items (`li`, `uld`, `dli`, `%hi/%lo` `lw`...).
  It stays the authority for boundaries, names and switch tables (ADR-0004) but cannot be the instruction decoder.
* **binutils (ps2dev)**: a text disassembler, GPL, and misses `vsqrt`; kept as the third oracle in tests.

## 3. Recommendation (inferred)

**Write our own R5900 decode table in `recomp/` (the ADR-0010 §1 "otherwise" branch), in the `ps2-web-recomp`
layout, and keep rabbitizer only as a test oracle.** The census shows rabbitizer *is* complete for our instruction
set (0 missing mnemonics), so completeness is not what decides it. What decides it:

1. The emitter needs **fields, not strings**: opcode class, `rs/rt/rd/sa/fd/dest/bc/imm`, delay-slot and likely flags.
   2.2's enum+accessor shape gives that in ~250 lines; rabbitizer's descriptor model (610 IDs, operand type enums,
   suffix enums, disassembly machinery, register tracker) adds a C11 dependency with a Makefile-only build, a single
   `_MSC_VER` branch and `__attribute__` uses, against ADR-0003's cl.exe-first stance, for information we would
   immediately map back into fields.
2. **Fail-closed on the EE**: our table rejects every non-EE opcode as `invalid`; rabbitizer's `cpu` fallback accepts
   `ll`/`sc`/`dmult`/`ldc1`... as valid. A recompiler must stop on those, not emit them.
3. **Verifiability is already in hand**: the table is validated word-for-word against two independent decoders over
   the entire binary (binutils: 8 explained disagreements; rabbitizer: 3 naming conventions). That is a stronger
   acceptance test than a submodule's upstream CI, and it can be re-run on every table change (`insn_census.py
   --from-cache --objdump`).
4. **Licensing stays trivial**: the table is the ISA encoding; the layout is borrowed from MIT `r5900.cpp` and gets a
   `THIRD_PARTY_NOTICES.md` line (ADR-0010 §2 already covers porting from that repository). No submodule, no vendored
   `.inc` macro machinery.

Rabbitizer's Python binding (`pip install` from the clone, or `rabbitizer==1.16.2`) becomes the **third oracle** next
to binutils and `ps2-web-recomp`: a Phase 3 test decodes every function word with all three and fails on any
non-aliased disagreement — the same check the census performed by hand.

### Draft ADR-0011 · 2026-10-18 · The recompiler decodes raw words with our own R5900 table; rabbitizer, binutils and `ps2-web-recomp` are decode oracles, not dependencies

**Context.** ADR-0004 fixed IDA as the boundary/name authority and ADR-0010 §1 deferred the decoder choice to an
instruction census. The census (`docs/ANALYSIS/08_instruction_census.md`) decoded all 1,194,277 words inside the
14,420 IDA functions: 199 base mnemonics, 0 invalid, VU0 used only as a vector ALU (no `vcallms`, no VU memory ops,
no `bc2*`), likely branches only in SDK/MW/CRI library code. IDA's own decoder is unusable for instruction identity
(opaque `cop2`, `mfthc1`/`pexow` misnamings, macro fusion). rabbitizer @ `724a49a` (MIT) names every one of the 199
(3 naming-only differences) but is a 610-ID multi-ISA C11 library whose R5900 mode inherits non-EE opcodes from its
generic tables; `ps2-web-recomp/recomp/r5900.cpp` (MIT) is a 254-line field-oriented table that rejects non-EE words.
A table of that shape in `insn_census.py` already matches binutils on all but 8 explained words.

**Decision.**
1. `recomp/` gets `r5900_decode.{h,cpp}`: an `enum class Op`, `constexpr` lookup arrays by major opcode / `funct` /
   `rs` / `sa`, and an `Insn` with field accessors, in the layout of `ps2-web-recomp/recomp/r5900.cpp` (attributed in
   `THIRD_PARTY_NOTICES.md`). Every word outside the EE's set decodes to `Invalid` and the recompiler stops on it
   inside a function body (fail closed); `pmfhl` and `sync` are single ops with the format read from the field;
   `qmfc2`/`qmtc2`/`cfc2`/`ctc2` carry the interlock bit as a field.
2. The recompiler reads instruction **bytes** from the ELF at IDA's chunk ranges (`functions.json` + chunk list);
   it never consumes `ida_ua.decode_insn`, IDA mnemonics or item sizes. IDA's data items inside chunks (1,553 words, 6,212 bytes;
   every one of them would also decode as a valid instruction, so their nature — alignment, constants or misflagged
   code — must be settled per site before they are skipped) are handled by address, not by re-decoding.
3. Decode acceptance test (Phase 3 CI, local): every function word is decoded by our table, by rabbitizer (Python,
   pinned 1.16.2 / `724a49a`) and by ps2dev `objdump -d`; the test fails on any disagreement not in the explicit
   alias list (`move`/`li`/`nop`/`b`/`beqz`..., `qmfc2`↔`qmfc2.ni`, `sync`↔`sync.l`, binutils' `vsqrt` gap).
   `insn_census.py --from-cache --objdump` is the prototype of that test.
4. Jump tables come from `symbols/jumptables.json` (IDA `switch_info_t`, 553 sites, all 32-bit absolute, verified
   against the table bytes); the 15 unresolved `jr $v0` tail-calls and all 5,143 `jalr` go through `LOOKUP_FUNC`.

**Why not alternatives.** rabbitizer as a submodule: complete but shaped for disassembly and m2c-style analysis, not
emission; C11/Makefile build with minimal MSVC provisions (ADR-0003); accepts non-EE opcodes; its benefit (names) is
reproduced by a 70-line table that we can prove equivalent on the whole binary. Vendoring its `.inc` tables: drags in
the `RABBITIZER_DEF_INSTR_ID` descriptor machinery for the same fields we can write directly. Using IDA's decoder: ruled
out by §2.4. Porting `r5900.cpp` verbatim: acceptable too, but it is 254 lines that we would re-type into our `Op`
enum anyway; we take the layout and the attribution, and own the text.

**Consequences.** `recomp/` owns one more small, fully tested file; the three-oracle test becomes part of
`check:fast`-equivalent local gating for `recomp/`; MMI/FPU/VU0 *semantics* remain ported from `ps2-web-recomp`
(ADR-0010 §2) and are tested separately against PCSX2 (Phase 4). Revisit if the port ever needs instructions outside
the 199 (overlays or IOP code would show up in a re-run of the census first), or if rabbitizer gains an MSVC/CMake
build and an emitter-oriented API.

## Corrections after implementation (2026-10-18, `recomp/src/r5900_decode.*`, `recomp/tests/oracle_decode.py`)
- **198, not 199.** `symbols/insn_census.json#units` holds 198 distinct base mnemonics; the "199" in §1 and in `08` counted one twice. `Op` = 198 + `Invalid`, `static_assert`ed against the JSON.
- **Two rabbitizer gaps** the §2.1 diff missed, found by the full-binary oracle run (1,195,310 words): R5900 mode prints COP1 funct 4 (`sqrt.s`, 133 sites) as a raw `c1` word (ID `r5900_c1__sqrt_s`), and its `isValid()` rejects the EE's 3-operand `multu rd,rs,rt` (12 sites, e.g. `0x4D9F24`). binutils and our table accept both; both are recorded as explicit aliases in the oracle script. Final tally: objdump 1,195,310/1,195,310 agree, rabbitizer 1,195,310/1,195,310 agree after aliases, 0 `Invalid` inside functions.
- **Scope decision made explicit in ADR-0011 §1:** the `Op` set is census-scoped and fail-closed; unused EE instructions decode to `Invalid` until a census re-run justifies widening.
- The chunk + data-item list the census depends on (173 multi-chunk functions, 1,553 data words) must be a committed `symbols/` artefact regenerated from the master database, not the test fixture `recomp/tests/fixtures/function_chunks.txt` captured from the prep database (14,420 functions; the master has 14,486).
