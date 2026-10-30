# `recomp/` — the R5900 → C++ static recompiler

_Phase 3 (GOAL.md). Shape: N64Recomp-style per-function emission (ADR-0010 §1). Decoder: our own
census-scoped R5900 table (ADR-0011). Status 2026-10-18: decoder, ELF view, function scope and the
emitter are implemented. All 14,486 IDA functions are emitted with ADR-0013's virtual-time
accounting and check points; the output compiles with zero warnings at `/W4` and links against
the aborting adapter stubs and against the real adapter `p3fes_rt` (`runtime/rt/`) under cl.exe
and clang-cl, Debug and Release. Recompiled libc functions execute correctly on that adapter
(`tests/rt/`, `runtime/rt/README.md`)._

## What exists

| File | Role |
|---|---|
| `src/r5900_decode.{h,cpp}` | Field-oriented decoder. `enum class Op` = the 198 base mnemonics of `symbols/insn_census.json` + `Invalid` (199 values). `constexpr decode(word, pc) -> Insn` with `rs/rt/rd/sa/fs/ft/fd`, `imm`, `target`, VU0 `dest`/`bc`/`vu_bc`, `fmt` (pmfhl format, sync stype), `interlock`, and `is_branch/is_likely/is_jump/is_call/has_delay_slot`. `mnemonic(Op)` and `variant_mnemonic(Insn)` give census spellings for diagnostics only. Table layout after `ps2-web-recomp/recomp/r5900.cpp` (MIT, attributed in `THIRD_PARTY_NOTICES.md`). |
| `src/elf_image.{h,cpp}` | Loads `SLUS_216.21` from a caller-given path, refuses unless the SHA-256 equals the digest in `docs/INVENTORY.md`, parses the ELF32 program headers and serves `word_at(va)` / `bytes_at(va, n)`. |
| `src/function_list.{h,cpp}`, `src/json_lite.h` | The function scope: `symbols/functions.json` (start, total size, name) plus the chunk list `symbols/function_chunks.txt` (IDA chunk ranges and data items inside chunks). No exceptions; errors are returned. |
| `src/emit_program.{h,cpp}` | Whole-program view: `WordSource` (ELF or an in-memory vector for tests), `SwitchTables` (`symbols/jumptables.json`), chunk ownership (`owner_of`), and the interprocedural fixpoint for **mid-body entries** and **which roots can return** (`compute_entries_and_returns`). |
| `src/emit_analyze.{h,cpp}` | Per function: decode every chunk word (data items skipped by address), pair each branch/jump with its delay slot, classify every edge, walk reachability from the start and the entries, collect labels and counts. |
| `src/emit_cgen.{h,cpp}` | C++ text of one function from its analysis; `Op` → `rt::` name mapping. |
| `src/emit_driver.{h,cpp}` | Selection (`--only`, `--band`), grouping into translation units, `functions.h`, `dispatch.cpp`, `missing_stubs.cpp`, `manifest.json`. |
| `src/handgen*.{h,cpp}` | `p3fes_handgen`: the register-faithful C++ body of a function for Phase 5 (section "p3fes_handgen" below). |
| `src/main.cpp` | CLI: `--dump-decode` (oracle test) and `--out` (emitter). Both exit 1 on an `Invalid` word inside a function body (fail closed); `--out` also exits 1 on any structural problem (below) unless `--keep-going`. |
| `include/p3fes_recomp_rt.h` | The adapter API generated code calls (`namespace p3fes::rt`). 203 declarations (202 + `check_events`, ADR-0013). Implemented by `runtime/rt/` (`p3fes_rt`). |
| `rt_stubs/rt_stubs.cpp` | Aborting definitions of every `rt::` function except `lookup_func` (generated), for compile/link tests that must not depend on the runtime. |
| `linkcheck/linkcheck_main.cpp` | `main` for the whole-program link: prints `lookup_func(<va>)` (default `start`); a miss stops naming the VA. Linked against the stubs (default) or `p3fes_rt` (`-DP3FES_LINKCHECK_RT=rt`). |
| `CMakeLists.txt` targets | `p3fes_recomp_generated` (object library: the emitted units, compiled once), `p3fes_program` (static library: those objects + `p3fes_rt`; in-tree builds only), `p3fes_recomp_linkcheck`. All only with `-DP3FES_RECOMP_GENERATED=ON`. |
| `tests/decode_census_test.cpp` | doctest: static encoding/fail-closed checks and the census equivalence over the real ELF (skips with a message when the ELF is absent). |
| `tests/emit_flow_test.cpp` | doctest: emitter structure on synthetic word sequences (delay slots, likely branches, jump tables, entry form, data words, reachability, noreturn propagation, link writes, multi-chunk, operand fields) and ADR-0013's cycle counts and check-point placement (straight line, conditional and likely branches, backward branch / `j` / switch case, entry form, delay-slot target, each option off). Needs nothing from the disc. |
| `tests/compile_subset.cmake` | ctest `p3fes_recomp_emit_subset`: emits 15 reviewed real functions, compiles every unit with the configuration's compiler at `/W4 /WX`, links against the stubs, runs two dispatch lookups. Skips (77) without the ELF. |
| `tests/oracle_decode.py` | Oracles 2 and 3: rabbitizer 1.16.2 (`724a49a`) and ps2dev `objdump -d -z` over the same words, with the explicit alias list. |

`generated/` (gitignored, derived from the user's ELF: never commit or copy it elsewhere) holds the
output of a full `--out` run.

### Fail-closed policy

`Op` contains only what the census found. EE instructions the game never uses (`dadd`, `tge`,
`bltzal`, `pref`, `vcallms`, `bc2f`, `plzcw`, `pmthl`, TLB ops...) and generic-MIPS encodings the
EE lacks (`ll`/`sc`, `dmult`/`ddiv`, `ldc1`/`sdc1`, `add.d`...) all decode to `Op::Invalid`; table
slots carry the mnemonic they would have so that widening after a census re-run is a one-word
change. The CLI and the emitter stop on an `Invalid` word inside a function body, reached or not.

### Running the decoder gate

```bat
cmake --preset msvc-x64-debug && cmake --build --preset msvc-x64-debug && ctest --preset msvc-x64-debug
```

The census test reads `extracted/disc/SLUS_216.21` (override with `P3FES_ELF`), `symbols/functions.json`,
`symbols/insn_census.json` and `symbols/function_chunks.txt`. Oracles 2/3 (not in ctest:
they need the venv and the ps2dev toolchain):

```bat
py -3.14 -m venv build\rabbitizer-venv
build\rabbitizer-venv\Scripts\python -m pip install tools\third_party\_community-eval\rabbitizer   # needs cl.exe (VS dev shell)
build\rabbitizer-venv\Scripts\python -I recomp\tests\oracle_decode.py ^
    --recomp build\msvc-x64-debug\bin\p3fes_recomp.exe ^
    --objdump-exe tools\third_party\ps2dev\ps2dev\ee\bin\mips64r5900el-ps2-elf-objdump.exe
```

Alias list (the only tolerated disagreements): binutils pseudo-ops (`nop`, `move`, `li`, `b`, `beqz`,
`bnez`, `beqzl`, `bnezl`, `negu`, `neg`, `dnegu`, `not`), `sync`↔`sync.l`, binutils' raw `c2` for
`vsqrt`; rabbitizer's `qmfc2.ni`/`qmtc2.ni`/`cfc2.ni`/`ctc2.ni` for the interlock-clear forms,
`sync`↔`sync.l`, `nop` for word 0, and two gaps found by the test: rabbitizer prints COP1 funct 4 as
raw `c1` (ID `r5900_c1__sqrt_s`; 133 `sqrt.s` sites) and its `isValid()` rejects the EE's
three-operand `multu rd,rs,rt` (12 sites, `0x4d9f24`...), which binutils and our table accept.

## Inputs to the emitter

1. **Function set and boundaries**: `symbols/functions.json` (IDA, ADR-0004) plus the chunk list.
   Both now come from the same database state (14,486 functions, 173 multi-chunk, 1,550 data items;
   the census test checks that no start appears in only one of them). The chunk list is required:
   `functions.json` cannot locate tail chunks or data words.
2. **Jump tables**: `symbols/jumptables.json` `resolved[]` (553 `jr` sites with IDA `switch_info_t`,
   all 32-bit absolute, 5,131 distinct targets, all inside the owning function). `unresolved[]` and
   `jalr_sites[]` need no input: every `jr $rN` without a table and every `jalr` goes through
   `rt::lookup_func`.
3. **Bytes**: from the verified ELF. The recompiler never consumes IDA mnemonics, item sizes or
   `decode_insn` output (ADR-0011 §2).

## Pipeline

```
functions.json + chunks ─┐
jumptables.json ─────────┼─► Program ── compute_entries_and_returns (fixpoint over all functions)
ELF bytes ───────────────┘        │
                                  ▼  per selected function
          analyze_function: decode chunks → classify edges → apply callee returns → reachability walk
                                  │
                                  ▼
          generate_function (C++ text)  ──►  emit_program: units of 200, functions.h, dispatch.cpp,
                                                            missing_stubs.cpp, manifest.json
```

**Edges.** Every branch/jump target is classified once: inside this function (any chunk) → `Local`
(`goto`); a `jal` to a function start → direct call; a `jal` into a body (own or another
function's) → call of that function's entry form; `j`, a branch, or a chunk end falling to another
function's start or body → tail call (`f(ctx); return;`); `jr $ra` → `return;`; `jr` with a table →
`switch`; other `jr $rN` → `rt::lookup_func(t)(ctx); return;`; `jalr` → `rt::lookup_func(t)(ctx);`;
a chunk end that falls into no function → `rt::unreachable(pc)`. A static target in no function is
a fatal problem (none occur).

**Interprocedural facts** (`Program::compute_entries_and_returns`, least fixpoint, both sets only
grow; every function is analysed with the current facts and re-analysed when they change):
* *Mid-body entries*: addresses that live code calls or jumps to inside another function's body
  (or its own, by `jal`). Edges from unreached code create none. Result: 23 entries in 21
  functions (all in the libc/CRI band `0x526238..0x5a0c00`); the 54 of `docs/ANALYSIS/06` §2.4 were
  mostly split into functions by later IDA passes.
* *Returns*: a root (function start or entry) can return if some reached path from it ends in a
  `return;` (`jr $ra`, `eret`, a register tail jump, a switch default, or a tail call to a returning
  root). A `jal` to a root that cannot return ends the path; a tail call to one is emitted without
  `return;`. Result: 21 functions cannot return (endless main loops such as `kwlnMain`, and the
  chains above them: `initAndLoop`, `main`); 6 calls and 1 tail call to them. Without this, MSVC
  `/O2` inlining proves the code after `jal kwlnMain` dead and reports C4702.

**Reachability.** Only words a static path reaches from the start or an entry are emitted
(fall-through, local edges, switch targets, a branch into a delay slot, calls that return). Every
emitted statement is therefore reachable in the C++ as well, which is why no C4702 suppression is
needed. Unreached runs (alignment `nop`s after returns, IDA data words after terminators) become a
single comment line.

## Emitted code shape

Synthetic input (not game code): `F` has a branch whose delay slot is also the target of a later
likely branch, a `jal`, a `jalr`, and a padding word; `G` has a mid-body entry that `H` calls.

```cpp
// F @ 0x00010000 (size 56, chunks 1)
void fn_F_00010000(p3fes::EEContext& ctx) {
    rt::check_events(ctx);                // ADR-0013 check point, once per invocation
    ctx.cycles += 3;                      // addiu, sw, beq (beq's slot is a label: charged per path)
    rt::addiu(ctx, 29, 29, -16);
    rt::sw(ctx, 31, 29, 0);
    if (rt::cmp_eq(ctx, 4, 0)) {          // beq a0,zero: condition first, slot on the taken path
        ctx.cycles += 1;
        rt::addiu(ctx, 2, 0, 1);
        goto L_00010020;
    }
L_0001000c:                               // the slot again: it is the bnel's target
    ctx.cycles += 1;
    rt::addiu(ctx, 2, 0, 1);
    ctx.cycles += 4;                      // jal + slot, bnel + slot (a call does not end a block)
    rt::jal(ctx, 0x10010u);               // $ra = pc + 8, then the slot, then the host call
    rt::addiu(ctx, 4, 4, -1);
    fn_G_00010100(ctx);
    if (rt::cmp_ne(ctx, 2, 0)) {          // bnel: the likely slot runs only when taken
        rt::lw(ctx, 25, 5, 8);
        rt::check_events(ctx); goto L_0001000c;   // backward edge: check point
    }
L_00010020:
    ctx.cycles += 5;                      // jalr + slot (nop), lw, jr + slot
    {
        const std::uint32_t t = rt::reg32(ctx, 25);   // jalr t9: target read before the slot
        rt::jalr(ctx, 31, 0x10020u);
        rt::lookup_func(t)(ctx);
    }
    rt::lw(ctx, 31, 29, 0);
    rt::addiu(ctx, 29, 29, 16);           // jr ra's delay slot, then the host return
    return;
    // 0x00010034..0x00010038: not reached by any static path, not emitted (1 word)
}
void fn_G_00010100_entry(p3fes::EEContext& ctx, std::uint32_t entry_pc) {
    rt::check_events(ctx);                // before the entry dispatch: once per invocation
    switch (entry_pc) {
    case 0x10100u: goto L_00010100;
    case 0x10108u: goto L_00010108;
    default: rt::bad_entry(0x10100u, entry_pc);
    }
L_00010100:
    ctx.cycles += 2;
    return;
L_00010108:
    ctx.cycles += 3;
    rt::addiu(ctx, 2, 0, 2);
    return;
}
void fn_G_00010100(p3fes::EEContext& ctx) { fn_G_00010100_entry(ctx, 0x10100u); }
void fn_G_00010100_at_00010108(p3fes::EEContext& ctx) { fn_G_00010100_entry(ctx, 0x10108u); }
```

(`H`'s `jal 0x10108` becomes `rt::jal(ctx, 0x10200u); fn_G_00010100_entry(ctx, 0x10108u);`.
The code is the generator's output for these words; the inline comments are added here for the
reader; `--annotate` instead appends the address and census mnemonic of every instruction.
`--no-cycles` / `--no-check-events` remove the `ctx.cycles` / `rt::check_events` lines.)

Rules, all visible above or covered by `tests/emit_flow_test.cpp`:
* **Names**: `fn_<IDA name, non-identifier characters → _>_<addr8>`. Functions are in namespace
  `p3fes::recomp_gen`, signature `void(p3fes::EEContext&)`; memory is reached through
  `ctx.memory` inside the adapter.
* **Delay slots** are emitted with their branch: conditional branches evaluate the condition into
  the `if` first and duplicate the slot into both outcomes; likely branches put it on the taken
  path only; `jr`/`jalr` read the target register before the slot. A slot that is itself a branch
  target is emitted once more under its own label (followed by the instruction at slot + 4); a slot
  beyond the chunk end (1 site, `0x4c72d4`) is fetched by address.
* **Calls** are host calls and `jr $ra` is a host return; the link register is still written
  (`rt::jal` / `rt::jalr`) so stack contents and `$ra` match the EE for tracediff.
* **Switches**: `switch (t)` on the target address loaded by the game, one `case` per distinct
  table target (`goto` or, for a target in another function, a tail call), `default:` →
  `rt::lookup_func(t)(ctx); return;`.
* **Entry-dispatch form** (functions with mid-body entries): `fn_X_entry(ctx, entry_pc)` holds the
  body with a `switch` to the start or entry label and `rt::bad_entry` as default; `fn_X(ctx)` and
  one `fn_X_at_<pc8>(ctx)` per entry are one-line wrappers (the dispatch table points at them, and so
  does every `jal` / `j` into the entry: `fn_X_at_<pc8>(ctx)`, never `fn_X_entry` -- the same call whether
  the function is replaced or not). Register state at an entry is the caller's, as on hardware; no extra
  analysis is needed.
* **Semantics stay in the adapter**: every state-changing instruction is exactly one `rt::` call
  with register indices and immediates; the generated code does no arithmetic. `nop` (word 0) and
  pure ALU writes to `$zero` are dropped; loads into `$zero`, and multiplies (`mult`, `madd`,
  `phmadh`, ...) with `rd = 0`, are kept (memory access / HI-LO side effects).
* **Portability**: standard C++20, no GNU extensions, no `musttail`. The only silenced diagnostic
  is the unused-label warning (C4102 / `-Wunused-label`) in `gen_prelude.h`; in practice every
  emitted label is referenced.

## Cycle accounting and check points (ADR-0013)

Both are on by default; `--no-cycles` and `--no-check-events` turn each off (the manifest's
`selection` records the choice, its `counts` the statements emitted).

**Virtual time.** `ctx.cycles += N;` is emitted at the start of every basic block, the only place
the generated code touches `EEContext` directly. A block starts at (1) the function start, (2) every
emitted label (local branch / jump / switch targets, mid-body entries, chunk starts), (3) the
fall-through of a reached conditional branch, and (4) a delay slot that is itself a branch target
(its own label). It runs to the first conditional branch or terminator (`j`, `jr`, `b`/`beq r,r`,
`eret`, a call that cannot return) **including its delay slot**, or to the next leader. **N is the
number of instruction words**, delay slots and `nop`s included (a `nop` produces no C++ but is
counted). Rules for the edge cases, each chosen so that every executed word is charged exactly once
on every path:
* **Calls that return (`jal`, `jalr`) do not end a block**: the words after the delay slot are
  charged together with the words before the call (one add instead of two; the callee charges its
  own words). The time a callee observes at its entry check is therefore ahead by the caller's
  post-call words, which is deterministic.
* **Likely branches**: the delay slot is counted once, also on the not-taken path that skips it.
* **A delay slot that is a branch target** (1 site in the binary): the slot is charged under its
  own label (which the jump-in path and, for a non-likely branch, the not-taken path fall through)
  and inside the taken path (`ctx.cycles += 1;` in the `if`); the branch's block then charges the
  branch word only. For likely branches the block charges branch + slot as usual and the label
  charges the slot for jump-ins only.
* An IDA data word reached by fall-through (`rt::unreachable`) is not counted.

Statically, the sum of all N equals the number of reachable words, plus one word per delay-slot
label (the slot appears on two paths). Pinned by `tests/emit_flow_test.cpp` ("cycles:" cases) and,
on real code, by `tests/rt/test_rt_exec.cpp`: one `strlen` of a 16-byte aligned string charges
exactly its 50 executed words.

**Check points.** `rt::check_events(ctx);` is emitted
* **once per invocation**: as the first statement of every function body, before the entry
  dispatch of entry-form functions and ahead of any label, so a loop back to the function start
  does not check twice per iteration (the `_at_` wrappers carry none);
* **before every loop back-edge**: a local edge (`goto`) whose target address is `<=` the address
  of the branch or jump itself, for conditional and likely branches, `j`/`b`, and each switch
  `case` whose target lies at or below the `jr` (`case 0x...u: rt::check_events(ctx); goto L_...;`).
  A chunk's fall-through end edge is never backward. Tail calls, register jumps and calls reach
  the callee's entry check instead.

## Adapter API contract (`include/p3fes_recomp_rt.h`)

Generated code includes only `p3fes_recomp_rt.h` and `functions.h`. `p3fes_recomp_rt.h` includes
`p3fes/ee_context.h` and, at its end, `p3fes_recomp_rt_inline.h`, which *defines* the hot subset inline
for every translation unit (integer ALU, shifts, immediates, branch conditions, link writes, HI/LO moves,
aligned main-RAM/scratchpad loads and stores, `check_events`; it needs `p3fes/ee/core.h`, `ee/hilo.h` and
`p3fes/ee_memory.h` from `runtime/include`). `runtime/rt/` (library `p3fes_rt`, one translation unit per
area) defines everything else plus the inline set's out-of-line halves (`rt::detail::load_slow`,
`store_slow`, `check_events_slow`, `g_deadline`); `rt_stubs` stands in for link-only tests (it stubs the
slow halves, never the inline set). See `runtime/rt/README.md` "Inline fast paths".

* **Dispatch and stops** (19 functions incl. `check_events`; the first cut said 19 for its 18): `lookup_func` (defined in the generated `dispatch.cpp`),
  `[[noreturn]]` `lookup_miss`, `bad_entry`, `unreachable`, `missing_function`;
  `trap(ctx, pc, Trap::Break|Unsupported, code)` (`break`, and undecodable words under
  `--keep-going`; may return); `syscall(ctx, pc)` (the runtime reads `$v1`); `check_events(ctx)`
  (ADR-0013 check point, above); `jal(ctx, pc)` /
  `jalr(ctx, rd, pc)` (link writes); `reg32` (jump-register target); branch conditions `cmp_eq`,
  `cmp_ne`, `cmp_lez`, `cmp_gtz`, `cmp_ltz`, `cmp_gez`, `cop1_cond` (FCR31.C; negated for
  `bc1f*`), `cop0_cond` (`bc0f` branches when false).
* **One function per state-changing `Op`** (183, incl. 9 `_bc` broadcast variants of VU0 ops):
  name = census mnemonic with `.` → `_`, `_` appended for C++ alternative tokens (`and_`, `or_`,
  `xor_`); `_bc` for VU0 broadcast forms. Pure control flow (`j`, `jr`, branches) has no function.
  Operand order is the assembler's: `(rd, rs, rt)`, `(rt, rs, imm)`, shifts `(rd, rt, sa)` /
  `(rd, rt, rs)`, memory `(rt, base, imm)` (the adapter adds and masks), FPU `(fd, fs, ft)`,
  `sqrt_s(fd, ft)` (the EE reads `ft`), COP2 transfers `(rt, fs-field register, interlock)`, VU0
  `(dest, fd, fs, ft[, bc])`, `vsqrt(ft, ftf)`, `vrsqrt(fs, fsf, ft, ftf)`.
* **Values**: register operands are indices 0..31; `imm` is sign-extended, `uimm` (`andi`/`ori`/
  `xori`/`lui`) zero-extended. The adapter drops writes to GPR 0, sign-extends 32-bit results, and
  owns every EE rule (FPU clamping/RZ, MMI lanes, HI1/LO1, SA units, LQ/SQ alignment).
* `pc` is passed only where the runtime needs it (syscall, traps, link writes, stops); memory
  operations carry none (a memory fault reports the address and the host return address).

## Dispatch table (`dispatch.cpp`)

A sorted `{va, fn}` array over **every function start and every mid-body entry of the program**
(14,509 rows in the full run), independent of `--only`; `rt::lookup_func(va)` is a binary search;
a miss calls `rt::lookup_miss(va)`, which is a hard error naming the VA. In a subset run the
functions that were not emitted resolve to their `missing_stubs.cpp` definition, which fails with
`rt::missing_function(va)`. Duplicate rows are an emitter error.

## Data words, unreached words, and the headless word

* **IDA data items inside chunks** (1,550 words) are never decoded. A data word that a static path
  falls into is emitted as `rt::unreachable(pc);  // IDA data word reached by fall-through`
  (`[[noreturn]]`); the others are part of an unreached run (comment only). The manifest lists all
  1,550 with `reached`; **none is reached**. The two that were (`0x242000` `jalr $v0` + its delay
  slot `0x242004` in `sub_241910`; `0x4509bc` `subu` in `sub_4501B0`) were code IDA had misflagged
  and are now instructions on the master (`tools/ours/ida/code_manual.txt`, `fix_code_items.py`).
* **Unreached code** (489 words): mostly alignment `nop`s after returns; not emitted.
* **`sub_46BFB0` headless word**: `0x46c14c` (`nop` between `b 0x46c160; lh` and the branch target
  `0x46c150`). Confirmed in IDA: four unexplored bytes (no item head, no xrefs) inside
  `sub_46BFB0`'s only chunk, so the function owns it and no flow reaches it. It is decoded like any
  word, reached by nothing, and emitted as a comment.

## Output files and manifest

`gen_prelude.h` (includes, `rt` alias, the unused-label pragma), `functions.h` (declarations of all
functions and entry forms), `fn_NNNN_<lo>_<hi>.cpp` (200 functions each, ascending), `dispatch.cpp`,
`missing_stubs.cpp` (empty in a full run), `manifest.json`: selection, counts (below), mid-body
entries, every data word with `reached`, unsupported words, problems, targets in no function.
Problems (`invalid_word`, `branch_in_delay_slot`, `delay_slot_is_data`, `target_in_no_function`,
...) stop the run with nothing written unless `--keep-going`.

### Full run (2026-10-18, `symbols/` before the Milestone-1 integration)

_Re-run 2026-10-19 after the integration added 16 missed callbacks and extended 6 truncated functions on the
master (`tools/ours/ida/funcs_manual.txt`, `docs/INTEGRATION_LOG.md` #2/#3): 14,501 functions emitted, 0 with
problems; 1,196,674 words; 5,149 `jalr`; 5 chunk ends into no function (was 11); ADR-0013: 158,949 cycle adds
(1,196,175 words charged), 14,501 entry checks, 11,354 back-edge checks. The table below is the earlier run._

| | |
|---|---|
| functions emitted / skipped / with problems | 14,486 / 0 / 0 |
| instruction words / statements / `nop`s dropped | 1,195,263 / 1,035,713 / 232,283 |
| branches (likely) / direct calls / `jalr` | 106,485 (2,387) / 66,528 / 5,144 |
| switches (targets) / static tail calls / register tail jumps | 553 (5,131) / 1,511 / 16 |
| mid-body entries (functions) / calls into them | 23 (21) / 20 |
| `jr $ra` / `syscall` / `break` / `eret` | 13,773 / 168 / 2 / 6 |
| chunk ends into no function / noreturn functions | 11 / 21 |
| data words reached / unreached; unreached code words | 0 / 1,550; 489 |
| ADR-0013: `ctx.cycles` adds (words charged) / entry checks / back-edge checks | 158,801 (1,194,775) / 14,486 / 11,331 |
| output | 73 units + 4 files, 43,207,961 B (41.2 MiB); with `--no-cycles --no-check-events` 39,191,811 B (37.4 MiB) |

Words charged = the 1,194,774 reachable words (1,195,263 decoded − 489 unreached) + 1 for the single
delay slot that is a branch target (`sub_5067F8`, charged on two paths). 158,801 adds is one per
7.5 reachable words.

The 16 register tail jumps are the 16 RenderWare `lw $v0, <ptr>; jr $v0` sites of
`jumptables.json#unresolved` (`sub_4C0880` at `0x4c088c` included since the re-export from the
master snapshot).

Timings on this machine (12 logical CPUs, Ninja default parallelism, clean builds of the 77
objects + link of `p3fes_recomp_linkcheck` in the standalone `recomp/` project against the stubs;
other agents were building concurrently, so the CPU load sampled just before each build is given):

| | emit (`--out`, Debug build of the recompiler) | compile + link Debug | compile + link Release |
|---|---|---|---|
| cl.exe 19.44, before ADR-0013 (first cut, `8e567bc`) | 35 s | 10 s | 37 s |
| cl.exe, now, default (cycles + checks) | 28.4 s (load 3 %) | 10.3 s (22 %) | 38.6 s (12 %), 38.9 s (1 %), 39.0 s (0 %); one 43.5 s at 18 % |
| cl.exe, now, `--no-cycles --no-check-events` | 32.7 s | 9.5 s (14 %) | 31.0 s (8 %), 31.0 s (13 %) |
| clang-cl 22.1, before ADR-0013 | | 10 s | 17 s |
| clang-cl, now, default | | 9.2 s (12 %) | 16.7 s (2 %), 16.2 s (2 %) |
| clang-cl, now, `--no-cycles --no-check-events` | | 8.7 s (15 %) | 14.7 s (10 %), 14.3 s (2 %) |

Same session, same inputs: the ADR-0013 statements cost cl.exe Release about +8 s (+25 %), clang-cl
Release +2 s (+13 %), Debug under 1 s. The in-tree `p3fes_program` + `p3fes_recomp_linkcheck`
against `p3fes_rt` (cl Debug, `-DP3FES_LINKCHECK_RT=rt`) builds in 11 s.

Warnings at `/W4`: 0 in all configurations above (the subset test additionally uses `/WX`).

## Commands

All from a VS x64 developer shell (`BUILDING.md`), repository root. Use private build directories
when other work builds concurrently.

```bat
:: recompiler + tests (in-tree; or standalone: cmake -S recomp -B build\msvc-recomp -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=cl)
cmake --preset msvc-x64-debug -B build\msvc-recomp
cmake --build build\msvc-recomp --target p3fes_recomp p3fes_recomp_tests
ctest --test-dir build\msvc-recomp -R recomp          :: flow tests + subset emit/compile/link

:: full emission (writes recomp\generated, gitignored)
build\msvc-recomp\bin\p3fes_recomp.exe --elf extracted\disc\SLUS_216.21 --functions symbols\functions.json ^
    --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated ^
    --replace game\replaced.txt

:: full compile + link against the stubs (standalone recomp/ project; repeat with clang-cl / Release)
cmake -S recomp -B build\msvc-recomp-full -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=cl -DP3FES_RECOMP_GENERATED=ON
cmake --build build\msvc-recomp-full --target p3fes_recomp_linkcheck
build\msvc-recomp-full\bin\p3fes_recomp_linkcheck.exe 0x5262b0

:: the program against the real adapter (in-tree: p3fes_rt comes from runtime/rt)
cmake --preset msvc-x64-debug -B build\msvc-program -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt
cmake --build build\msvc-program --target p3fes_program p3fes_recomp_linkcheck
```

Emit options: `--only a,b,...`, `--band lo-hi`, `--group-size N` (default 200), `--stable-units`,
`--annotate`, `--keep-going`, `--no-cycles`, `--no-check-events`, `--replace game/replaced.txt`
(required for the in-tree program since Phase 5 began; see "Replacements").
`P3FES_RECOMP_GENERATED_DIR` points the generated build at another `--out` directory.
`--stable-units` (2026-10-21) groups by the whole program's bands of N functions (position in
`functions.json`) instead of by the selection, and names each unit after its band, so a subset's units
keep their names and text when the selection changes elsewhere; a full run writes the same units
either way. `tests/rt/emit_units.cmake` uses it for the tests' big subset (`p3fes_game_gen`: 16
bucket translation units `gen_units_NN.cpp`, each recompiled only when one of its units changed).
Build speed (2026-10-21): every file is written only when its text changes, and `functions.h` does not
depend on `--replace`, so a change of `game/replaced.txt` recompiles only the units holding a function
whose status changed (a 60-function slice: 1 of 75 units, was all 75). `-DP3FES_UNIT_CACHE=<dir>`
(`tools/ours/gate/unit_cache.py`, set by the gate) shares the compiled units between trees.

## Replacements (Phase 5, `--replace game/replaced.txt`)

GOAL.md Phase 5 replaces recompiled functions with readable C++ in `game/`, one at a time, each
gated by the trace diff. The emitter supports this without touching the call sites:

* `game/replaced.txt` lists `<hex start> <IDA name>` per line. With `--replace <file>` the emitter
  checks every entry against `functions.json` (unknown start, a name that no longer matches, a
  duplicate, or a mid-body entry list that is not the program's all stop the run), emits the recompiled body under
  `fn_<name>_<addr>__recomp` (declared in `replaced.h`, which no unit includes; `functions.h`
  declares the plain symbols only, the same text whatever `--replace` lists). **Mid-body entries** (since
  2026-10-29, slice finalD): a function with entries lists them on its row as `@0x<pc>` tokens
  (`0x526238 vfprintf @0x5262b0`; exactly the program's set, else the emitter names the expected list). Its
  `__recomp` emission keeps the entry form (`fn_X_entry__recomp` and the `fn_X__recomp` / `fn_X_at_<pc8>__recomp`
  wrappers); `game/` defines the plain `fn_X` and every `fn_X_at_<pc8>` (one forwarder each from the same row;
  p3fes_handgen writes one `game::<name>_at_<pc8>` per entry, with the regions the entry points share as static
  bodies). Every call or jump into an entry, replaced or not, goes through the `_at_<pc8>` wrapper (never
  `fn_X_entry`), so a function can change status without touching its callers; a replaced entry's call sites and
  dispatch row use `fn_X_at_<pc8>__sel`, which reads the function's own reference flag. The plain
  `fn_<name>_<addr>` comes from `game/`: a forwarder generated from `replaced.txt` (below, "Forwarders"), or for the
  functions `game/forwarders.txt` marks `-` a thin shim a source defines (arguments from `$a0..`, result into `$v0`,
  `game/include/p3fes/game/guest.h`). Since 2026-10-21 the dispatch row and every generated
  call site of a replaced function use `fn_<name>_<addr>__sel`, an inline selector the unit declares itself
  (`if (rt::g_reference_<addr8>) ..__recomp(ctx); else fn_<name>_<addr>(ctx);`; flags and
  `rt::set_reference_mode` in `dispatch.cpp`): `p3fes --reference-mode` runs the zero-replacement program from the
  same executable (runtime/STATE.md "Reference mode"). A unit's text therefore changes when a function it calls
  changes status, not only one it defines. `--no-selectors` emits plain calls (a cost baseline: no measurable
  difference on the battle route). `manifest.json` carries `"replaced"` (count and list).
* `p3fes_program` (and the link check) link `p3fes_game_forwarders` (the plain forwarders) and through it
  `p3fes_game`. An emission made **without** `--replace` while `game/` defines a function fails the link with a
  duplicate symbol, and one made with it but without the `game/` definition fails with an unresolved symbol: the
  two inputs cannot drift apart silently.
* **Forwarders** (since 2026-10-29). A replaced function's entry point is the one-line forwarder
  `void p3fes::recomp_gen::fn_<name>_<addr8>(p3fes::EEContext& ctx) { p3fes::game::<name>(ctx); }`. No source
  writes it: `game/forwarders.cmake` generates every row of `replaced.txt` at build time, except the rows
  `game/forwarders.txt` marks `0x<addr> <name> -` (1,825 older functions whose source defines a typed shim or a shim
  macro row) or gives another body name (`0x<addr> <name> <body>`, e.g. `<name>_regs`). It writes two units:
  `forwarders_game.cpp`, plain, is `p3fes_game_forwarders` (p3fes, the link check, the audit: the game's code is the
  same tail call as before, no branch, no global); `forwarders_test.cpp` is compiled into `p3fes_game_tests` instead,
  each forwarder starting with the check `tests/rt/emit_units.cmake` puts into a hooked generated body,
  `if (::p3fes::game_test::g_stand_ins_active && ::p3fes::game_test::stand_in_hook(ctx, 0x<addr8>u)) return;`.
  So **a replaced function can be stood in: the test build's forwarder asks the stand-ins first**, and a function
  some test stands in can be replaced without breaking that test. `p3fes_game` itself holds no plain forwarders, so
  each executable links exactly one definition of each. The pair runners (`pair_harness.h`, `handgen_pairs.h`) call
  the function under test past its own stand-in (`tests/game/stand_in_entry.h`: the first stand-in query of the run,
  the forwarder's own, is skipped), so a pair compares the real hand-written body even with a global set such as
  FakeCd installed. `p3fes_handgen` writes no entry points in the replacement flow (only with `--shim-suffix` /
  `--shim`); a branch made before this change still ends its sources with forwarders: after merging it run
  `python -I tools/ours/phase5/forwarders.py` (moves them out, idempotent; `--check` reports). Such a tree does not
  link until then (duplicate `fn_*` symbols).
* The recompiled body stays in the program under `__recomp` so `tests/game/` can run both on
  identical guest machines and require the same result, callee-saved registers, memory outside the
  dead stack, virtual cycles and number of check points (ADR-0013): a replacement is observationally
  the recompiled function, including interrupt delivery points. The whole-program gate is the
  deterministic dorm replay (`BUILDING.md`), byte-identical before and after.

## p3fes_handgen (register-faithful bodies for Phase 5)

`p3fes_handgen` (`src/handgen*.cpp`, target `p3fes_handgen`) writes the C++ body a Phase 5 slice starts from, so a
slice agent no longer transliterates frames, spills, links, register values, cycle charges, back-edge checks and jump
tables by hand (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen" is the agent's how-to).

```powershell
build\<tree>\bin\p3fes_handgen.exe --elf <ELF> --functions symbols\functions.json --chunks symbols\function_chunks.txt `
    --jumptables symbols\jumptables.json --sym symbols\p3fes.sym --only @my_slice.txt --slice my_slice `
    --header-include p3fes/game/my_slice.h --out-cpp game\src\<area>\my_slice.cpp `
    --out-h game\include\p3fes\game\my_slice.h --out-replaced my_slice.rows --out-test tests\game\test_my_slice.cpp
```

Output per function: `void p3fes::game::<name>(EEContext&)` (register ABI: arguments in `$a0..`, result in `$v0`), the
`p3fes::recomp_gen::fn_<name>_<addr8>` shim, a header declaration, a `game/replaced.txt` row, and one pair-test skeleton
for the whole list. `--body-suffix` / `--shim-suffix` rename the body / shim (a scratch substitution next to an existing
typed version; the self-tests pair `fn_X__hg` with the recompiled `fn_X`); `--replaced game/replaced.txt` tells the
skeleton which functions have a `__recomp` body in the build.

**Faithful by construction.** The CFG is built from the emitter's own `FunctionAnalysis` and mirrors
`generate_function` item for item (the same leaders, the same `block_words` charge per block, the same delay-slot-label
continuation, the same back-edge rule `target <= branch pc`), so every path executes the recompiled body's statements in
its order with its charges and check points. Every statement is one instruction on the register view
`game/include/p3fes/game/hg_cpu.h`: one proxy per GPR (`v0 = addiu(s0, 1)`: the `ee::core` rule `rt::addiu` itself
applies; volatile reads and writes), the FPU / MMI / HI-LO / COP0 / COP2 / VU0 macro instructions as the `rt::` op of
the same name, loads and stores as `rt::lw..sq` (the fast path, the bus slow path, the faults), `charge` / `enter` /
`backedge` through a volatile `ctx.cycles` (the wave-10 MSVC lesson), `jal(ctx, pc, gen::fn_*)` = `rt::jal` + the
callee's entry point (hand-written or recompiled), `jalr`, jump tables as `switch` on the loaded entry with the
generated `default` (the dispatch table). Delay slots: written before their call / branch when independent of it (no
link-register access, no memory access that could reach a check point while `$ra` differs, the branch operands
untouched); otherwise the link (`link(ctx, pc)`) or the test (`cc = ...`) or the jump target (`jt = ...`) comes first, as
on the hardware. Likely branches keep the slot on the taken path. A mid-body-entry function (the entry form) becomes one
`game::` function per entry point, `<name>` and `<name>_at_<pc8>`, each starting with its own entry check point: the
region an entry point reaches and that never flows back to another is its own; where a root flows into such an entry
it calls that entry's shared body (a `static` function, forward-declared, without a check point of its own) and
returns, so every path runs the recompiled body's statements, charges and check points in its order. A tail call to a
root that cannot return inside a branch edge is refused (none among the replaced functions).

**Structure.** Dominators, post-dominators (jump-table defaults not counted) and natural loops over that CFG; a
recursive emitter places each block once: loops as `for (;;)` (test-first or test-last as compiled; `continue` /
`break` where the edges allow), `if` / `else` at the post-dominator merge, a block that only one test reaches placed
after the other branch when that branch flows into it, the shorter of two terminating branches first (early returns),
`switch` bodies with `break` at the merge, small shared epilogues written out on each path (the same statements in the
same order: still faithful). Whatever stays shared or irreducible is a `goto L_<address8>` to a labelled block. Comments:
the original address per block, the frame summary (frame size, every callee-saved spill and its slot), data symbols of
`symbols/p3fes.sym` for absolute and `$gp`-relative accesses, string literals for `.rodata` addresses, the table indices
of every `case`.

**Tests.** `p3fes_handgen_selftest` (ctest; `tests/game/handgen_selftest.cmake`): regenerates the functions of
`tests/game/handgen_selftest.txt` at build time (`/WX`), and pairs each with its recompiled body on random worlds through
`tests/game/handgen_pairs.h` -- the whole register file and cycles at every check point and at the return / stop, all
32 MiB of RAM, the scratchpad, the BIOS window, the bus log. `-DP3FES_HANDGEN_DEEP=ON` (a tree with
`-DP3FES_RECOMP_GENERATED=ON`) adds `p3fes_handgen_deep`: the same against the whole recompiled program, so the runs go
past every call (`P3FES_HANDGEN_DEEP_LIST`; `P3FES_HG_SEEDS`, `P3FES_HG_ONLY`, `P3FES_HG_TRACE` in the environment).

## p3fes_types (whole-program struct-layout recovery)

`src/types*.cpp`, target `p3fes_types`: a forward dataflow per function over `emit_analyze`'s items (base pointers,
offsets, strides, spills, phis), then a field-sensitive union-find with layout, anchor and size vetoes; raw JSON for
`tools/ours/types/types_build.py`, which writes `tools/ours/types/types.json` and the proposed headers in
`game/include/p3fes/game/types/`. All 14,500 functions take 2.6 s. Method, numbers and limits are in
`docs/ANALYSIS/28_types.md`; how slices use it is in the brief, "Type recovery".

## Limits and open items

* **Host return for `jr $ra`**: control flow ignores the guest's `$ra`. Code that returns somewhere
  else (setjmp/longjmp, thread context switches, the libkernel patch payloads installed with
  `SetSyscall`, `docs/ANALYSIS/13`) needs HLE; `eret` is emitted as `rt::eret` + `return`.
* **Indirect targets** must be function starts or known entries; a `jalr`/`jr` to anything else
  stops in `lookup_miss` naming the VA (the fix is in `symbols/`).
* **Mid-body entries** are found only from static edges; a function pointer into a body would miss.
* **Reachability is static**: code reached only through such an unknown indirect edge is not
  emitted (it shows up as an unreached run in the source and as a `lookup_miss` at run time).
* **Performance** (first measurement, `runtime/rt/README.md`): the game's `memset` over 1 MiB runs
  229,405 guest instructions in 0.44 ms (cl.exe Release; about 520 M guest instructions/s, 1.8x the
  EE clock), with every `rt::` call still opaque (one call per instruction, no LTO). The ADR-0013
  statements cost +11 % (cl) / +9 % (clang-cl) in that loop, which checks every 7 instructions.
