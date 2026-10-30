# Phase 5 quick brief (slice agents)

_Read this, `CLAUDE.md` and your `packet.md`; nothing else at the start. The packet already did the discovery: which
functions, their callees, what to reuse, the test set. `docs/PHASE5_AGENT_BRIEF.md` is the long reference: open one
of its sections only when this page points you there._

## Ground rules

- One pass: work, commit once, report, end. No sub-agents, forks or workflows.
- Commands go through `tools\ours\phase5\slice.ps1`. It prints at most ~12 lines and keeps the full logs in
  `build\slice-logs\<cmd>.log`. Never print a big file or log; read line ranges (Read with offset / limit, or
  `Select-String` with a pattern).
- PowerShell 5.1: never `2>&1` on a native command; quote hex lists (`'0x1,0x2'`), or PowerShell turns them into
  numbers. Python is always `python -I`. Gitignored inputs (ELF, ISO, `extracted/`, `ida/`) live only in the main tree
  `F:\P3FES-PORT\p3fes-port`: point at them, never copy or commit them.
- Take only the packet's functions. Its `claims.txt` is yours; another packet's claims are not.

## Steps

`$s = '<slice>'; $env:P3FES_SLICE = $s; $p5 = 'tools\ours\phase5\slice.ps1'` in your worktree, then:

1. `powershell -File $p5 build`: configures `build\<slice>-gate`, emits `recomp\generated` with `--replace`, builds
   with MSVC (a fresh tree takes 2-7 min with the shared unit cache). Rerun it after every change to `replaced.txt`,
   your sources or the test lists.
2. `powershell -File $p5 gen`: runs p3fes_handgen on the packet's gen list. It writes the faithful bodies, the header
   and the pair-test skeleton to the packet's `Write:` paths. It then appends the rows and files to the shared lists
   (`wire.py`). Then run `build` and `test`: the skeleton passes as generated. A function with mid-body entries gets
   one `<name>_at_<pc8>` function per entry (its row carries `@0x<pc>`; each entry is its own pair and forwarder).
3. `powershell -File $p5 pseudo`: writes `<scratch>\<slice>.pseudo.c` (IDA's C for each function followed by its
   handgen body, with a table at the top). Read it by line ranges. It is a reading hint, not a source (below).
4. Readability pass on your `.cpp` / `.h` (rules below). Use `types_query.py` for pointers (step 6).
5. Tests: replace the skeleton's random worlds with real structures (rules below).
6. Types: `python -I tools\ours\types\types_query.py --addr <start|name>` (also `--type T --off 0x3C`,
   `--global 0x7CE3EC`) names what `$a0..$t3` / `$v0` point to. Take offsets from `game/include/p3fes/game/types/*.h`
   (do not include those headers). Confirm `low` / `poly` / "beyond the documented size" fields from the
   instructions. Confirmed names go into `tools/ours/types/deltas/<slice>.json` (`seeds.json` format; `how` = `param`
   + `index`, `ret`, `gslot`, `gobj`; give `size` when known). Then run
   `cmake --build build\<slice>-gate --target p3fes_types` once (after `. F:\P3FES-PORT\p3fes-port\tools\env.ps1`), then
   `python -I tools\ours\types\types_build.py --exe build\<slice>-gate\bin\p3fes_types.exe --out-json <scratch>\types.json --headers <scratch>\types --report <scratch>\types_report.txt`
   (always all three into your scratch: the defaults rewrite the shared `types.json` and type headers, which slices
   never commit) and check that your record's found / conflicts line improved. Name fields only from your own evidence.
7. Iterate with `powershell -File $p5 step` (build + test + audit). `test` and `audit` alone also work.
   `audit` builds `p3fes_audit_faithful` in the same tree the first time (~3.5 min) and must say every function is
   faithful. To fix a differing function, regenerate it (full brief, "The faithfulness audit" step 2).
8. Docs: one row in `game/README.md`'s module table:
   ``| `<slice>.h` / `src/<area>/<slice>*.cpp` | what it is (N; slice `<slice>`; how it is made readable; tests) | `docs/INTEGRATION_LOG.md` (<slice>) |``.
   One section at the end of `docs/INTEGRATION_LOG.md`:
   `## Phase 5 slice <slice>: <summary> (<N> functions, <date>)`, then `**What.**`, `**How chosen.**` (the packet),
   `**Tests.**`, `**Audit.**`, `**Gate.**`. Use numbers from your own runs only.
9. `powershell -File $p5 final`: `sync` (merges main, keeps your uncommitted work, and drops rows main now replaces;
   exit 3 = delete those definitions and test rows, then rerun), then `build`, `test`, `clang` (clang-cl build plus
   your tests), and the gate (`gate.ps1 -Slice -FastGs`, all six routes, including the ~21 min climb). Every route
   must show its expected frame, `eeMemory 0 bytes`, `gsMemory identical`, and the last line must be `GATE: PASSED`.
10. Commit (below), then `powershell -File $p5 report` prints the counts block for your report.

For a **continue** packet (paused work): start with `sync`, then `build` and `test`. The packet lists what is done (the
rows, files and tests in the worktree), what is missing, and the rows you must drop. `gen` writes the remaining
functions to new `_rest` files.

## Readability: make it readable without changing what runs

The handgen body is one statement per instruction on `hg_cpu.h`'s register view. It is the faithful source of truth:
it already equals the recompiled body (frame, spills, `$ra` links, cycle charges, check points). Your job is the
names, structure, comments and typed views on top of it.

- **Safe:**
  - comments and names: a role comment per function, `// [proposed name]`, block roles;
  - named offsets (`constexpr s32 kNext = 24; lw(v0, s1, kNext);`) and struct layouts in your header;
  - host copies for reading (`const u32 node = s1.u();`): every guest register write stays;
  - structure: `goto L_x` into `if (a || b)` / `while` / `for`, epilogue copies merged into one, as long as each path
    keeps the same statements, charges and check points in the same order;
  - inside one block (between two `charge` lines), moving pure register statements when nothing in between reads or
    writes what they touch.
- **Not safe:**
  - `lw`/`sw` replaced by `guest::load`/`store` (faults and the bus path are part of the behaviour; use the `rt::`
    ops);
  - anything moved across a load, store, call or check point;
  - dropping a frame, spill, `link`, `charge` or `backedge`;
  - calling a callee directly instead of through `jal(ctx, pc, gen::...)`;
  - reordering the delay-slot statements written after `link(...)` / `cc = ...`.
- Leave every register (GPRs, HI/LO, FPRs, ACC, FCR31) as the original does at every check point, call and return. A
  preemption saves the whole register file to the guest stack, so a "dead" scratch register still reaches memory.
  Reproduce `$v0` of void functions and `$f20`-style floats that callers can see.
- Pseudocode (`*.pseudo.c`) is a hint for structure, field offsets, strides, switch shapes and roles. Never copy its
  statements; check every reading against the instructions. Never commit it.
- Names in code are exactly `symbols/functions.json`'s (often `sub_XXXXXX`). Put a proposal in a comment and in
  `symbols/deltas/<slice>.sym` with evidence (importer format: `tools/ours/ida/README.md`).
- Your header holds local helpers; never edit `guest.h` or another slice's files. A typed C++ wrapper is fine when
  hand-written callers need one (they give `$ra` with `rt::jal` at the original call site).

## Pair tests: must-haves

- Your own file `tests/game/test_<slice>*.cpp`, built on `pair_harness.h` / `handgen_pairs.h` and `stand_ins.h`. Each
  pair runs the hand body against `__recomp` on identical machines and compares:
  - the whole register file and cycles at every check point and at the return / stop;
  - all 32 MiB of RAM, the dead stack included;
  - the scratchpad, the BIOS window and the bus log.
  `run_pair_si(m, hand, recomp, args, seed, what, hw)` with `kAllGprs`, `compare_checkpoint_regs`,
  `compare_dead_stack` and a whole-RAM range. Restore worlds with `BaseRange` / `PairRange` (`write_tracker.h`), not
  32 MiB copies.
- Worlds: real structures from the snapshots (`read_snapshot("b_5800")`, `copy_from_snapshot`, `h_malloc_blocks`),
  the edge cases each branch tests, and a few documented-rule checks. Skip cleanly when game data is absent.
  `P3FES_HG_SEEDS` / `P3FES_HG_ONLY` / `P3FES_HG_TRACE=1` tune the runs.
- Calls through `jalr` need a **non-leaf** callee that spills `$ra` below the `$sp` it receives, with the dead stack
  compared. Test whole 64-bit registers where the original uses `daddu` / 64-bit compares. Read loop bounds and jump
  tables from the instructions.
- A callee your paths need but the test build does not emit: stand it in **inside your test**
  (`w.si.install_recorder(va, name, v0)` or `w.si.install(va, name, fn)`; the heap, printf / sprintf and the H_Cdvd
  layer come from `install_standard`). Do not add it to `_callees`. Never add printf (0x5225A8), file loading, the
  sound driver, kernel wrappers or the `sub_1FDD40` tree to `_callees`. If your additions break another slice's test,
  trim yours.
- A replaced function can be stood in: the test build's forwarder asks the stand-ins first. Every replaced function's
  entry point `fn_<name>_<addr8>` is a forwarder generated from `game/replaced.txt` (recomp/README.md "Forwarders"); in
  `p3fes_game_tests` it starts with the same check as a hooked generated body, so a stand-in you install serves the
  callee whether it is recompiled or hand-written, and a function you take keeps meeting the stand-ins other tests
  install for it. The pair runners call your function under test past its own stand-in (`stand_in_entry.h`), so a
  pair always compares your real body. Your source defines no `recomp_gen` entry point (`gen` writes none).
- What you stand in no longer blocks other slices; `standins.py` still indexes it, and the packet of the slice that
  takes it lists your test under "Tests that stand them in". Stand in only what you need.
- If the original faults on a random world, compare the two faults with `fault_of` and skip the value checks.
- MSVC only: cycles off by a small helper's cost means `/O2` kept `ctx.cycles` in a register across the call. Use
  core3.cpp's volatile Cpu-view pattern.

## The relaxed callee rule

A body may call functions that stay recompiled, through their `gen::` entry points (`jal(ctx, pc, gen::fn_...)`).
You do not wait for callees to be hand-written: take a function whatever its callees' state. The packet's callee
codes show what a pair meets:
- `R`: hand-written;
- `E`: recompiled and emitted in the test build; it runs;
- `G`: recompiled and not emitted; the pair stops there unless you stand it in;
- `S`: stood in by another slice's test (there a stand-in serves it, recompiled or replaced).

The packet's "Tests that stand them in" names the tests that stand in, name (a `stop_pc` / not-emitted check) or had
served (an absent-run recorder) one of your functions. Run them besides your own after `build`: a stand-in keeps
serving the function, but a `stop_pc` check or an absent recorder (installed on a missing-function stop, which your
replaced function no longer gives) can change. Fix such a test by standing the function in explicitly in it.

## Skip rules (the packet has applied them; recheck what you add)

Skip a function, and give the reason in the report, when it has:
- (no longer: a mid-body entry -- since slice finalD the emitter, p3fes_handgen, the forwarders and the pairs handle
  them: the row carries `@0x<pc>` per entry, `gen` writes one `<name>_at_<pc8>` function per entry);
- a hardware-register access, a `syscall` or a COP0 instruction in its own body;
- a direct call into SIF / IOP RPC, the sound driver below `H_Snd*` (`sceSd*` / `sceSk*` / `sceSpu2*`), or ADXF /
  ROFS / `sceCd` (not through H_Cdvd), unless your prompt allows it.

Not skip reasons: heap use, printf / sprintf, H_Cdvd file loading and `jalr` calls. Pair them on the stand-ins.

## Shared files (append only; the lead merges them as unions)

`gen` writes these entries, and `sync` keeps them across merges. Format for hand edits:
- `game/replaced.txt`: a block `# Phase 5 slice <slice>: <summary> (game/src/<area>/<slice>*.cpp)`, then
  `0x<start> <name>` rows.
- `tests/game/CMakeLists.txt`:
  - your test file in the `p3fes_game_tests` list;
  - a block `    # <slice> slice (...)` ... `    # end <slice>` just before `p3fes_rt_emitted_lib(p3fes_game_gen`,
    holding `string(APPEND _replaced ",0x..,...")` lines (12 per line, equal to your replaced.txt rows) and any new
    `_callees` lines.
- `game/CMakeLists.txt`: your header and sources in the `p3fes_game` list.
- No forwarder lines: the `recomp_gen` entry points come from `game/replaced.txt` (game/forwarders.cmake). A typed shim
  you write yourself needs a `0x<start> <name> -` row in `game/forwarders.txt`.
- `game/README.md`: one row. `docs/INTEGRATION_LOG.md`: one section at the end.

## Commit

Commit once on your worktree branch with explicit pathspecs; never `git add -A`. Commit your sources, header, tests,
the shared files, your `tools/ours/types/deltas/<slice>.json` and `symbols/deltas/<slice>.sym`. Never commit anything
under `extracted/`, `build/`, `recomp/generated`, `ida/`, `*.i64` or `*.pseudo.c`. Write the message as
`game(<area>): <slice> -- <what>` and end it with `Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`. The merge
commit `sync` makes is not yours to squash.

## Licences and sources (ADRs)

- ADR-0009: names in code and docs are only `symbols/` names. Community maps (`symbols/hints/`) are hints; a name
  inferred from them, or from anything else, goes into a comment or a delta, with evidence.
- RenderWare: no RW source. RW 3.7 / SCE struct headers from community PR #4 are consult-only. Our headers come from
  public SDK knowledge, ps2sdk and our own type recovery.
- No GPL: PCSX2, PS2Recomp and p3fes-recompiled sources are never opened (ADR-0010). GPL code never enters the repo.
- IDA: never open the master (`ida/p3fes.i64`). The pseudocode export already exists, so you do not need IDA.

## When to open the full brief (`docs/PHASE5_AGENT_BRIEF.md`, by section)

| Section | Open it when |
|---|---|
| "Using p3fes_handgen" | handgen limits (shared-block `goto`s, irreducible CFGs), typed wrappers for hand-written callers |
| "The pseudocode reference" | a Hex-Rays reading looks odd (unknown prototypes, `__asm`, merged jump tables) |
| "Lessons from wave 6" | a pair test or a gate differs and you look for the known bug classes |
| "The faithfulness audit" | `audit` reports a difference: regenerate it with `regen_faithful.py`, `rm_defs.py`, `carry_docs.py` |
| "Stand-ins" | stand-in API details: heap arena, FakeCd, `_stand_in_hooks`, the limits |
| "Type recovery" | the `types_query` / delta format beyond step 6 |
| "Machine states" | a route differs: find the first differing vblank, save a state, bisect with `--reference-mode` |
| "Build and gates" | slice.ps1 fails in a way its log does not explain (the manual recipe) |
