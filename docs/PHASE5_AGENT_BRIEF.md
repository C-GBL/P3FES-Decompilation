# Phase 5 agent brief (shared by every hand-decompilation agent)

_Read this whole file first. Your own prompt only names your slice of functions and your files._

## Environment

- Read `CLAUDE.md`. Every PowerShell session starts with `. .\tools\env.ps1`. PowerShell 5.1: never `2>&1` on a
  native command; use `cmd /c "... > log 2>&1"`. Python with `-I`.
- This machine (since 2026-10-20): the main tree is `F:\P3FES-PORT\p3fes-port`; 8 cores / 16 threads shared by
  every agent, so build with `cmake --build <dir> -j 4`. Dot-source the **main tree's** env script
  (`. F:\P3FES-PORT\p3fes-port\tools\env.ps1`): tools, venvs and third-party code are gitignored and exist only
  there. Python 3.14 + idalib work (venv `F:\P3FES-PORT\p3fes-port\deps\venv\idalib`). The old WIP branches are still registered to stale worktrees, so `git checkout <branch>` refuses them: bring a
  WIP commit into your own worktree with `git cherry-pick <sha>` (or `git merge`).
- No backslash escapes in Bash heredocs (they get collapsed): write edit scripts to files or use the Edit tool.
- Gitignored inputs live only in the main tree; point at them, never copy or commit them:
  ELF `F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21`,
  ISO `F:\P3FES-PORT\p3fes-port\input\persona3fes.iso`, extracted data `F:\P3FES-PORT\p3fes-port\extracted\`.
- IDA: only on your own copy of the master (`ida/work_<slice>.i64` inside your worktree; take the copy once at the
  start, from `F:\P3FES-PORT\p3fes-port\ida\p3fes.i64`), headless through
  `F:\P3FES-PORT\p3fes-port\deps\venv\idalib\Scripts\python.exe` (`import idapro` first). Never open or
  write the master itself unless your prompt says you are the master agent.
- GPL sources (PCSX2, PS2Recomp, p3fes-recompiled) are never opened (ADR-0010). Unverified community names never
  enter the repo (ADR-0009); `symbols/hints/` may be read as hints only.

## The procedure (game/README.md is the reference; follow it exactly)

1. Read the recompiled body in `recomp/generated/fn_*.cpp` (emit it in your worktree first, below) and the IDA
   disassembly; read the topic doc for your area (`docs/ANALYSIS/1x/2x_*.md`) and its queue file.
2. Write the readable function in `namespace p3fes::game` under the name `symbols/functions.json` gives it **now**
   (often `sub_XXXXXX`; keep it, put a proposed name in a comment and in your delta file). **Since 2026-10-21 you
   start from `p3fes_handgen`'s output** (section "Using p3fes_handgen" below): it writes steps 2-4 faithful by
   construction plus the step-6 test skeleton; your work is everything that makes it readable.
3. Mirror the ADR-0013 cycle model exactly: `guest::enter` (entry check point + first block), `guest::charge` per
   executed block (the `ctx.cycles += N` lines of the generated body), `guest::backedge` where the recompiled loop
   has its back-edge check (loops whose test block comes first check before every iteration). A `jr` switch
   becomes a C++ switch with the per-case block costs. Still-recompiled callees go through `guest::call`
   (K_Assert/K_Abort `0x19D3F0`/`0x19D400` are `jr $ra` in retail: bad-input paths continue and store; mirror them).
   Guest stack buffers handed to callees go through `guest::StackFrame`. Reproduce what a void function leaves
   in `$v0` if callers could observe it.
4. The entry point `p3fes::recomp_gen::fn_<name>_<addr8>` is generated from `game/replaced.txt` (recomp/README.md
   "Forwarders"; since 2026-10-29). Only a typed shim of your own goes into your file, with a `0x<start> <name> -` row
   in `game/forwarders.txt`.
5. Append `<0xstart> <name>` to `game/replaced.txt` under a comment header naming your slice; add the start
   addresses (and any new still-recompiled callees) to the two lists in `tests/game/CMakeLists.txt`; add your
   source/header files to `game/CMakeLists.txt` and your test file to `tests/game/CMakeLists.txt`.
6. Pair tests in **your own new file** `tests/game/test_<slice>.cpp` using `tests/game/pair_harness.h`:
   randomised inputs plus edge cases, hand-written vs `__recomp` on identical guest machines (result, callee-saved
   registers, memory -- the dead stack too: a frame can stay live on a waiting thread's stack --, cycles, check-point
   count; then the faithfulness audit below for the whole register file), plus a few documented-rule checks; real
   game data where convenient (skip cleanly when absent).
7. Functions with mid-body entries (23 entries in 21 functions) are taken since slice finalD: the row lists the
   entries (`@0x<pc>`), p3fes_handgen writes one function per entry point. Skip anything that touches hardware
   registers, makes a syscall itself or talks to the IOP (SIF RPC, the sound driver) unless your prompt says
   otherwise; say so. **Since 2026-10-21 heap, printf / sprintf and H_Cdvd file loading are NOT skip reasons**: pair
   such functions on the test stand-ins (section "Stand-ins" below).

## Using p3fes_handgen (the faithful starting point; since 2026-10-21)

The mechanical half of a slice is generated: the original's frame and spills, `$ra` at every `jal`/`jalr`, every
register value at every check point, call and return, the per-block cycle charges and back-edge checks, jump tables as
switches with the generated fallback. You start from a body that already equals the recompiled one (it passes the pair
tests and the gates as it is); **your job is the naming, structure, comments, typed views and meaningful tests on top
of it.** (The missing frames and spills fixed in `f794284` -- RFMAI_ToUpperStr, frFontCreateGlyphNode -- cannot
happen in a generated body.)

1. **Generate.** Any configured tree builds the tool (`cmake --build build\<slice>-msvc --target p3fes_handgen`):
   ```
   build\<slice>-msvc\bin\p3fes_handgen.exe --elf F:\P3FES-PORT\p3fes-port\extracted\disc\SLUS_216.21 `
       --functions symbols\functions.json --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json `
       --sym symbols\p3fes.sym --only @<slice>.txt --slice <slice> --header-include p3fes/game/<slice>.h `
       --out-cpp game\src\<area>\<slice>.cpp --out-h game\include\p3fes\game\<slice>.h `
       --out-replaced <slice>.rows --out-test tests\game\test_<slice>.cpp
   ```
   `<slice>.txt`: one hex start per line (`#` comments). ~2 s for any number of functions. A function with mid-body
   entries (the recompiled entry form) becomes one `game::` function per entry point (`<name>_at_<pc8>` behind
   `fn_<name>_<addr8>_at_<pc8>`), the regions the entry points share as static bodies called where the flow enters
   them; its row carries `@0x<pc>` per entry and each entry is its own pair. Each function becomes `void p3fes::game::<name>(EEContext&)`
   (register ABI: arguments in `$a0..`, result in `$v0`); its `recomp_gen::fn_<name>_<addr8>` entry point is generated
   from `game/replaced.txt` (recomp/README.md "Forwarders"). Callees are called through their `recomp_gen` entry
   points, so hand-written and recompiled callees both work.
2. **Wire it up** as in step 5 of the procedure (the rows of `<slice>.rows` into `game/replaced.txt`, the sources into
   `game/CMakeLists.txt`, the test file and the starts into `tests/game/CMakeLists.txt`), emit, build, and run your
   test file: the skeleton pairs every body with its `__recomp` body on random worlds through
   `tests/game/handgen_pairs.h` (the whole register file and cycles at every check point and at the return / stop, all
   32 MiB of RAM, the scratchpad, the BIOS window, the bus log) and passes as generated.
3. **Make it readable without changing what runs.** The body is one statement per instruction on the register view
   `game/include/p3fes/game/hg_cpu.h` (`v0 = addiu(s0, 1)`, `lw(v0, s1, 24)`, `jal(ctx, pc, gen::fn_*)`,
   `charge(ctx, N)`, `backedge(ctx)`), and every path runs the recompiled body's statements in its order. Safe:
   * comments and names: block roles, `// [proposed name]`, named offsets (`constexpr s32 kNext = 24;
     lw(v0, s1, kNext);`), struct layouts in your header, host copies for reading (`const u32 node = s1.u();`) --
     every guest register write stays;
   * structure: the remaining `goto L_<address>` into conditions (`if (a || b)`), `for (;;)` into `while` / `for`,
     the epilogue copies into one -- as long as each path keeps the same statements, charges and check points in the
     same order;
   * inside one block (between two `charge` lines) pure register statements may move when nothing between reads or
     writes what they touch.
   Not safe: replacing `lw(...)`/`sw(...)` by `guest::load`/`store` (the faults and the bus slow path are part of the
   behaviour), moving anything across a load / store / call / check point, dropping a frame, spill, `link`, `charge`
   or `backedge`, calling a callee directly instead of through `jal(ctx, pc, gen::...)`. Delay slots that depend on
   the link or the test are already written after `link(...)` / `cc = ...`: keep that order.
4. **Tests.** Replace the skeleton's random world by the function's real structures (real game data, the snapshots),
   add the edge cases its branches test, put the callees its paths need into `_callees` (without them the runs stop,
   identically, at the first call), add documented-rule checks. `P3FES_HG_SEEDS=<n>`, `P3FES_HG_ONLY=<name>` and
   `P3FES_HG_TRACE=1` in the environment set the pairs per function, pick one function and trace every pair.
5. **Gate** as usual.

Measured (2026-10-21): all 2,321 functions of `game/replaced.txt` generate (0 refused; 1.6 s for all of them) and
compile warning-free at `/W4` under MSVC and clang-cl. Against the whole recompiled program on 32 random worlds each
(`p3fes_handgen_deep`), 2,319 equal their recompiled bodies (74,208 pairs, 742,134 assertions; 22,232 pairs end at the
same stop in both bodies); the other 2 cannot be tested that way (the recompiled body itself hits `std::terminate` in a
hand-written RenderWare callee). 44 hand-written functions swapped for their generated bodies in a scratch build kept
every existing pair test green on both compilers and all five replay routes byte-identical. Ten fresh functions
(0x3D2C10..0x3D38B0): from the address list to a passing pair test in 13.7 s.

Limits: the output is register-level C++ (no C types or locals: naming and typing are yours); a `goto` remains where a
block is shared or the CFG is irreducible; refused: a no-return tail call inside a branch edge (none
among the 2,321 replaced functions); the skeleton's world is generic; the `game::` function takes `EEContext&` only --
add a typed wrapper if hand-written callers need one (and give them the original's `link` at the call site).

## The pseudocode reference: IDA's C for every function, as a reading hint (since 2026-10-21)

`F:\P3FES-PORT\p3fes-port\ida\pseudocode\` holds Hex-Rays pseudocode for all 14,500 functions of
`symbols/functions.json` (`fn/<addr8>_<name>.c`, `index.tsv`), made by `tools/ours/ida/pseudo_export.py` from a prepped
copy of the master (`$gp` set so gp-relative globals show as `dword_7CE298`-style names; exactly the repo's names --
no withheld community hints, ADR-0009; K_Assert / K_Abort typed `(file, line)` as normal calls). Each file starts with
what the database knows: callers, callees, globals, strings, Hex-Rays warnings, the `__asm` the decompiler could not
lift (MMI, VU0 macro, `syscall`, R5900 FPU ACC ops); 128-bit `sq`/`lq` register saves are folded into one comment.

- **What it is**: a read-only hint for step 3 of "Using p3fes_handgen" (the readability pass). **p3fes_handgen's body
  stays the faithful source of truth**: never copy pseudocode statements into a body (it drops the frame, the spills,
  the cycle charges, 64-bit register state, `$v0` of void functions, delay-slot order; its argument counts, types,
  signedness and local names are IDA's guesses -- `__int64` everywhere, `_$S5` for a register read from the caller).
  Names: only `symbols/functions.json` names are used in code (ADR-0009); a name you read in the pseudocode is the
  repo's own name, and any name you infer from it goes into a comment / your delta file with evidence, as before.
- **Use it for**: the structure (which `goto`s are a `while`, a `for`, an `if (a || b)`; a `switch` and its cases),
  the typed views (offsets that are fields: `*(_WORD *)(unk_7CE3EC + 2900)`, array strides: `byte_7E2680[1648 * a1]`
  is a 1,648-byte record), the role of a function (its strings, callers and callees), and naming locals. Check every
  such reading against the instructions (the handgen body is one statement per instruction).
- **Collect your slice** (plain Python, no IDA, any worktree):
  ```
  python -I tools\ours\ida\pseudo.py --only @<slice>.txt --handgen game\src\<area>\<slice>.cpp --out <scratch>\<slice>.pseudo.c
  ```
  One file, each function's pseudocode followed by its p3fes_handgen body, plus a table (status, lines, `__asm`,
  JUMPOUT, warnings). `--facts-only` prints only the headers (callers / callees / globals / strings): the summary to
  read for a function the decompiler could not handle. A `STALE` mark means the master was renamed after the export.
- **Never commit it** (it is derived from the game binary, like `recomp/generated`): `/ida/` and `*.pseudo.c` are
  gitignored; keep the collection in your scratch area. Do not open IDA for this: one idalib process at a time on this
  machine, and the reference already exists. After a master update the lead (or the master owner) refreshes it:
  copy `ida\p3fes.i64` to `ida\work_pseudocode.i64`, run `pseudo_export.py` (incremental: only changed functions).
- Read with care: Hex-Rays assumes library prototypes it does not know (`strlen()` printed without its argument),
  gives an unexplored global as an offset into the nearest named array (`dword_7CE298[85]` is `0x7CE3EC`, which the
  handgen comment names correctly), lifts no 128-bit / MMI / VU0 instruction (`__asm` blocks; `cop2 ...` and
  `mfthc1` are IDA's decoding of VU0 / R5900 words), and turns a jump table whose cases share a target into an `if`
  (scrGetStrPara's 6-entry table is `== 5`).
- Measured 2026-10-21 (Hex-Rays 9.3, `$gp` set): 14,500 functions -- 13,253 `ok` (91.4 %; no `__asm` beyond the
  folded register saves), 1,246 `ok_partial` (functions per class, overlapping: R5900 FPU ACC ops 505, other
  `lq`/`sq` 404, MMI 348, `syscall` 167, VU0 macro 148, COP0/sync 6, other 28 -- mostly `mfthc1`; JUMPOUT 21), **1 failed** (`sub_4C72A0`, `MERR_BADRANGES`: its last
  instruction runs into the next function). Of the 2,343 replaced functions 2,155 are `ok`, 188 `ok_partial`. A full
  export takes 4 min 48 s (one idalib process), a no-change re-run 29 s (keys only), 58 MB on disk (25.8 MB of text).
  `pseudo.py` for a slice: 0.2 s.

## Lessons from wave 6 (real bugs the gates or pair tests caught — check for each in your own code)

- **Calls through function pointers (`jalr`) must reproduce the original's frame and link.** If the original opens a
  stack frame and sets `$ra` (and any register the callee can see, e.g. `$v1` = the table offset) before a `jalr`, the
  hand version must do the same (`guest::StackFrame`, set `$ra` to the generated link value) — otherwise every callee
  runs with `$sp` off and stale stack leaks into memory (`btlMainUpdateState`, fixed in `bcbb841`). In pair tests,
  install at least one **non-leaf** callee that spills `$ra` below the `$sp` it receives, and compare the dead stack.
- **Scratch registers callers can read**: leave `$at/$v0/$v1/$a0–$a3/$t0–$t9` as the original does when a caller
  could observe them (a 2-byte M1 diff traced to `kwlnTaskExists`); compare all GPRs in pair tests when unsure.
- **64-bit registers**: test whole registers where the original uses `daddu`/64-bit compares (several fixes).
- **Loop bounds and jump tables**: read them from the instructions, never from intuition (`itfMesMngSetSelection`,
  `scrFindPrcdIdxByName`, `datCalcCheckHit` row swap).
- **Do not take a function another slice already replaced**: before you start, check main's `game/replaced.txt` and
  stay inside the address list/range your prompt gives you (two slices replaced `sub_170E40` and three kwln accessors).
- **Floats seen by callees** (`$f20` returned by `datScriptGetValue` on assert paths) and **`$v0` of void functions**.
- **(wave 7) Every register reaches memory at a preemption.** When a check point preempts the thread or it makes a
  switching syscall, the kernel saves the WHOLE register file to the guest stack at `$sp - 0x280`
  (`KernelOptions::context_frames`). So a leftover scratch register (`$t2`…) that "no caller reads" still lands in
  memory and the gates see it (render_im2d's first version: pair tests green, gate 17–35 stack bytes off). Leave
  every register — GPRs, HI/LO, FPRs, ACC, FCR31 — as the original does at every check point, call and return, and
  compare all of them in pair tests (`run_pair_hw` / `HwCheck` in `pair_harness.h` can compare the full register
  file at every check point, the bus log, the scratchpad and chosen ranges — see `game/README.md`).
- **(wave 7) Calls through function pointers are doable**, not a skip reason: reproduce the frame and `$ra` (above).
- **(wave 9) The tests' `_callees` list is shared by every test file**: emitting a callee makes every other slice's
  pairs run deeper into it. Never add printf (0x5225A8), file loading, the sound driver, kernel wrappers or the
  `sub_1FDD40` tree (`test_ui2` and `test_battle_task` failed when one slice did); if your additions make another
  slice's test fail, trim yours rather than editing theirs. (2026-10-21: a callee you need served rather than run --
  printf, the H_Cdvd requests, anything not emitted -- is a per-test stand-in now, not a `_callees` entry; below.)
- **(wave 10) MSVC /O2 can keep `ctx.cycles` in a host register across a call to a small non-inlined helper that
  charges cycles** (render_core3: the helper's 3–7 cycles were lost; confirmed in the disassembly, caught by the pair
  tests). If pair tests show cycle counts off by a helper's cost on MSVC only, look at the disassembly; core3.cpp's
  Cpu view reads GPRs and updates cycles through volatile accesses as a barrier (copy that pattern into your header).
- **(wave 10) Route guest loads and stores through the runtime's own ops** (`rt::lw` … `rt::sq`, base `$zero`, the
  address as the offset), not `guest::load`/`guest::store`: the latter don't check alignment or mapping, so on a
  random world the recompiled body stops with an address error while the hand body carries on (nm_message,
  battle_result, title all hit this in pair tests).

## The faithfulness audit: is every hand-written function register- and frame-faithful? (since 2026-10-21)

`p3fes_audit_faithful` (tests/game/test_audit_faithful.cpp, opt-in, not in the gate) pairs EVERY function of
`game/replaced.txt` -- the hand-written `fn_X` against `fn_X__recomp` inside the whole recompiled program, so every
callee is there -- on random worlds and the replay snapshots, and compares what no slice test masks: the whole register
file and cycles at every check point and at the return / stop, all 32 MiB of RAM **including the dead stack** (frames
that stay live on a waiting thread's stack are memory the replay gates compare), the scratchpad, the BIOS window, the
bus log. One verdict per function, with classes (own frame / callee frames / memory / stop / check-point count / `$ra`
/ `$v0` / scratch / upper 64 bits / HI/LO / FPU / VU0 / cycles). Its first run (2026-10-21) found **975 of 2,343**
replaced functions unfaithful (347 missing frames or spills, 77 callee frames, 77 `$v0`, 137 scratch GPRs, 286 that only
differ on inputs the original faults on, 48 that terminated the host); all were regenerated (below) and the audit now
reports 2,343 faithful.

1. **Run it before you finish a slice** (your functions only, ~seconds):
   ```
   cmake --preset msvc-x64-release -B build\<slice>-audit -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt `
       -DP3FES_RT_EXEC_ELF=<literal ELF path> -DP3FES_AUDIT_FAITHFUL=ON     # after emitting recomp\generated with --replace
   cmake --build build\<slice>-audit --target p3fes_audit_faithful -j 4   # ~3.5 min fresh (the whole program)
   python -I tools\ours\audit\audit_faithful.py --exe build\<slice>-audit\bin\p3fes_audit_faithful.exe `
       --out build\<slice>-audit.tsv --only <name>,<name> --seeds 96 --snapshots dorm_replay_4900,b_5800,climb_ref_17000 `
       --snapshot-seeds 16 --objdir build\<slice>-audit\game
   ```
   Every row must say `faithful`. All 2,343 functions: drop `--only`, `--jobs 4`: 316 s. One function by hand:
   `P3FES_AUDIT_ONLY=<name> P3FES_AUDIT_SEEDS=96 build\...\p3fes_audit_faithful.exe` (`P3FES_AUDIT_TRACE=1` names the
   body and pair before each run: which one crashes). The TSV has the first instance of each class (register, check
   point, stack offset relative to the entry `$sp`, RAM address).
2. **Fix a differing function by regenerating it** (`tools/ours/audit/regen_faithful.py --handgen <p3fes_handgen.exe>
   --plan <file\taddr\tnote rows>`): the p3fes_handgen body replaces the old definition of the same name, the old
   comments move above it, the typed C++ API stays as a thin wrapper when other code still calls it (`$a0..`/`$f12..`
   as the original's caller sets them, `$v0`/`$f0` returned; a faithful caller still gives `$ra` with `rt::jal` at its
   original call site), the shim and the callee declarations are rewritten. Then build with clang-cl and remove what
   became dead (`rm_defs.py --warnings <log>`), carry docs that sat on register-view members (`carry_docs.py`), rerun.
3. **Lessons** (each was found by the audit): a check point inside a `noexcept` helper terminates the host when it
   raises (eight register views had `enter` / `backedge` noexcept; fixed); `guest::load` / `guest::store` skip the
   runtime's alignment, mapping and bus paths, so a hand version reads through a pointer the original faults on (286
   functions); a pair test whose random world the original itself faults on (now visible, since every callee is
   faithful) compares the two faults with `fault_of` (pair_harness.h) and skips its value checks.

## Stand-ins: pairing heap users, printf users and file loaders (since 2026-10-21)

`tests/game/stand_ins.h` (details in `game/README.md` "Pair tests with stand-ins"; examples in
`tests/game/test_standins_demo.cpp`, self-tests in `test_stand_ins.cpp`). Both bodies of a pair call the SAME
deterministic stand-in; the pair compares its call log and everything else exactly.

- **Use it**: `run_pair_si(m, hand, recomp, args, seed, what, hw)` instead of `run_pair_hw` (same `HwCheck`; take
  `kAllGprs`, `compare_checkpoint_regs`, `compare_dead_stack`, and a whole-RAM range `{0, 32 MiB}` -- write-tracked, so
  cheap). Default world (`install_standard`): the heap, printf, sprintf / vsprintf, the H_Cdvd layer. Pass your own
  `WorldSetup` lambda to choose (e.g. leave `install_sprintf` out to run the recompiled sprintf), to pre-allocate
  blocks (`w.heap.alloc`), to toggle file loading (`w.cd.load`), or to stand in any other callee.
- **Heap** (`GuestHeap`, arena 0x1C00000-0x1F00000, zero in every replay snapshot): H_Malloc 0x191AF0 / H_Free 0x191A10,
  the RW memory functions the slots 0x960178..0x96018C point at (RwMalloc / RwFree / RwRealloc / RwCalloc, the
  free-list alloc / free), newlib malloc / free / calloc / realloc. 16-byte first fit, same calls -> same addresses,
  no guest header. Call `write_rw_slots(m)` once on your machine (the ELF's .bss has zeros in the slots). Task creation
  (kwlnTaskCreate*, dds3InitProcess) works through it: the hand-written kwln kernel allocates with H_Malloc. Real heap
  data: `read_snapshot("b_5800")`, `copy_from_snapshot`, `h_malloc_blocks` (live blocks of H_Malloc's table),
  `GuestHeap::reserve`.
- **printf / sprintf**: `guest_format` follows this newlib (checked against the recompiled sprintf on 3,000 formats:
  `l` is 64-bit, `hh` = `h`, `%p` prints the 64-bit slot). printf logs the text (`StandInCall::text`) and returns its
  length; sprintf writes the text + NUL into the guest buffer. printf stays un-emitted (test_ui2): the stand-in is
  opt-in per test.
- **Files** (`FakeCd`): H_Cdvd_Request / Update / ReadSync / Destroy on guest memory with the retail node layout, list
  and sCdvdCache registration (the hand-written H_Cdvd_AddFile); files come from `extracted/` (DATA, BTL, BGM), whole,
  64-byte aligned in heap blocks; a missing file (or `load = false`) leaves the node pending, identically in both runs.
- **Any other not-emitted callee**: `w.si.install_recorder(va, name, v0)` logs the call and returns `v0`, so the pair
  continues past what used to be a missing-function stop; `w.si.install(va, name, fn)` for a custom one. A stand-in
  runs the callee's entry check point, then overwrites `$at/$v1/$a0-$a3/$t0-$t9` with a per-call pattern.
- **Limits**: a replaced function can be stood in (since 2026-10-29: the test build's forwarder asks the stand-ins
  first, recomp/README.md "Forwarders"; the pair runners call the function under test past its own stand-in); an
  emitted, still-recompiled callee can only if it is in `_stand_in_hooks` (tests/game/CMakeLists.txt); a fatal stop inside a pair propagates (build worlds that run to the
  end, as with `run_pair_hw`); the fake file layer completes a read in one Update (retail takes frames).
- **Still true skip reasons**: hardware registers, syscalls in the function's own body,
  the IOP / SIF RPC and the sound driver below `H_Snd*`, ADXF / ROFS / sceCd called directly (not through H_Cdvd:
  stand them in with recorders if the function is worth it).

## Type recovery: proposed struct layouts for your readability pass (since 2026-10-21)

`p3fes_types` (`docs/ANALYSIS/28_types.md`) proposes struct layouts for the whole program in about 3 s. It recovers
which offsets each pointer is accessed at, with width, kind and accessor functions, unified across calls, returns,
pointer fields and callbacks. It then checks them against the project's headers and the replay snapshots. Against the
headers, 983 of 1,336 documented fields were found and 13 conflict. On the snapshots, 98 % of the pointer and float
checks pass.

1. **Before you name anything, ask what your function's pointers point to:**
   ```
   python -I tools\ours\types\types_query.py --addr <start or name>     # $a0..$t3 / $v0 -> type + fields + accessors
   python -I tools\ours\types\types_query.py --type KwlnTask --off 0x3C # one field: width, accessors, pointee
   python -I tools\ours\types\types_query.py --global 0x7CE3EC          # what a global holds / which record lives there
   ```
   Each field line shows the offset, widths, type (`u16`, `f32`, `ptr`, `fnptr`, ...), confidence (high/medium/low),
   the number of accessor functions and the first three, the pointee type, snapshot checks, and the documented name
   when a header has one. `type_<id>` is an unnamed recovered type: use `unk_XX` for its fields.
2. **Typed views on top of the faithful body.** The `hg_cpu` body stays as generated. A typed view only names what it
   already does:
   * Take the offsets from the proposed headers in `game/include/p3fes/game/types/*.h`: units, battle state, tasks,
     field objects, Tartarus floors, effect nodes, script/event, models, calendar. They are byte-packed, carry
     `static_assert` sizes and give accessor evidence per field.
   * Copy the fields you use into your own header as named offsets (`constexpr s32 kHp = 0x8; lhu(v0, a0, kHp);`), or
     as a struct for comments and host-side reading.
   * Do not include the proposed headers from game code yet: they are regenerated.
   * A field marked `low`, `poly` (polymorphic pointee) or listed "beyond the documented size" is a guess. Confirm it
     from your function's instructions before you name it.
3. **Feed confirmed names back as a delta**, never by editing `seeds.json` or the generated headers. Write
   `tools/ours/types/deltas/<slice>.json` in the `seeds.json` format:
   ```
   {"records": [{"name": "FldUnit", "anchors": [{"how": "param", "fn": "0x1C65E0", "index": 0}],
                 "fields": [{"off": 48, "width": 4, "type": "f32", "name": "pos_x"}]}]}
   ```
   * `how` is one of `param` (with `index` 0..7 = `$a0..$t3`), `ret`, `gslot` (a global holding the pointer) or `gobj`
     (the record's address).
   * A delta field replaces the seed field at the same offset. A new record name adds a record; give `size` when you
     know it, because sizes are what stop merges.
   * Name fields only from your own evidence (ADR-0009).
   * Then rerun:
     ```
     python -I tools\ours\types\types_build.py --exe <tree>\bin\p3fes_types.exe --headers game\include\p3fes\game\types
     ```
     It takes 4 s. Check that your record's "found / conflicts" line in the report improved, and commit the delta with
     your slice. A conflict the report lists against an existing header is either a header error or a merge: say which
     in your slice notes.

## Files: avoid collisions with the other agents running at the same time

- Your code goes in **new files** named after your slice: `game/src/<area>/<slice>.cpp`,
  `game/include/p3fes/game/<slice>.h` (you may include existing headers; do not edit another slice's files, and do
  not edit `guest.h` — put local helpers in your own header).
- Shared files you may only **append** to: `game/replaced.txt`, `game/CMakeLists.txt` (source list),
  `tests/game/CMakeLists.txt` (test list, the `_replaced` list, the `_callees` list), `game/README.md` (one table
  row), `docs/INTEGRATION_LOG.md` (one section at the end). The lead merges these as unions.
- Names delta (optional, for proposed names): `symbols/deltas/<slice>.sym` in the importer format
  (`tools/ours/ida/README.md`; evidence per row; tge-pr4 promotions need `verified=yes ev=`). Not imported by you.

## Build and gates (keep CPU use modest: several agents share this machine)

**Since 2026-10-21 a slice uses ONE tree, built by the gate script, MSVC only** (the lead's merge gate builds
clang-cl and runs every suite on both compilers):

1. Build (configure + emit with `--replace` + build) — at the start, and again after every change of `replaced.txt`,
   your sources or the test lists:
   `powershell -File F:\P3FES-PORT\p3fes-port\tools\ours\gate\gate.ps1 -Repo <your worktree> -Tree build\<slice>-gate -Slice -BuildOnly -Jobs 3`
   It builds `p3fes`, `tracediff` and `p3fes_game_tests` only. Generated units, runtime/ and game/ objects come from
   the shared object cache (`F:\P3FES-PORT\p3fes-port\build\_unit_cache`, `tools/ours/gate/unit_cache.py`) when any
   tree compiled the same text (measured: a fresh tree 96 s with a warm cache, 430 s with an empty one), and a
   60-function replacement change rebuilds one program unit, one or two test buckets and your files (12 s; 222 s
   before, when every one of the 75 units recompiled). No separate `-recomp`/`-msvc`/`-clang` trees, no manual
   emission. `-NoUnitCache` compiles everything locally.
2. Pair tests from that tree: `build\<slice>-gate\bin\p3fes_game_tests.exe -sf=*test_<slice>.cpp` (or
   `ctest --test-dir build\<slice>-gate -R p3fes_game_tests.<slice>`). clang-cl is not required of a slice; build it
   only when you suspect compiler-specific code (`-ClangTree build\<slice>-clang` without `-Slice`).
   Worlds restored before every pair: use `BaseRange` (`tests/game/write_tracker.h`: restores only the pages written,
   exact `PairRange` protocol on the same tracker) instead of a 32 MiB `memcpy`, and a whole-RAM `PairRange` instead of
   copying windows (field_big 222 s → 23 s, battle_cmd_menu 107 s → 31 s, battle_actions 118 s → 13 s; exact, and
   whole RAM on every pair: mutations outside the old windows are now caught).
3. Once, at the end: `powershell -File F:\P3FES-PORT\p3fes-port\tools\ours\gate\gate.ps1 -Repo <your worktree> -Tree build\<slice>-gate -Slice -FastGs -Jobs 3`
   (the same tree: no rebuild; the pair-test entries + every replay gate; report its output verbatim). Measured
   2026-10-21: 277 s / 1,340 CPU-s, bounded by the battle route; the old slice gate (fresh MSVC tree, clang-cl tree,
   every suite on both compilers) took 1,201 s / 6,768 CPU-s on the same machine. (Both with five routes: the sixth,
   the full Tartarus climb, takes ~21 min on its own. **`-Slice` skips the climb** -- dorm, m1, battle, fusion and
   shop run; the lead's merge gate runs all six. `-Routes a,b,...` picks routes explicitly, e.g. `-Routes climb` when
   your slice touches Tartarus code and you want the climb's verdict before the merge.)
   The lead merges with `gate.ps1 -Tree build\<name> -ClangTree build\<name>-clang -FastGs` (no `-Slice`).

The older recipe below still works (the gate without `-Slice` is the full one).

1. Emit once per `replaced.txt` change: build `p3fes_recomp` in `build\<slice>-recomp`, then
   `build\<slice>-recomp\bin\p3fes_recomp.exe --elf <ELF> --functions symbols\functions.json --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated --replace game\replaced.txt`.
2. Pair tests on both compilers (these compile only the listed functions, so they are cheap):
   `cmake --preset msvc-x64-release -B build\<slice>-msvc -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt -DP3FES_RT_EXEC_ELF=<literal ELF path>`
   and `cmake --preset clangcl-x64-release -B build\<slice>-clang -DP3FES_RT_EXEC_ELF=<literal ELF path>`
   (pass the literal path, not a `$variable`; Release since 2026-10-20, the build type the gate's clang-cl run uses,
   so the gate reuses this tree instead of re-configuring and rebuilding it; `clangcl-x64-debug` stays for
   debugging); build `p3fes_game_tests` and run it directly on both: report its case/assertion counts. (Or
   `ctest --test-dir build\<slice>-msvc -R p3fes_game_tests -j 3`: one ctest entry per test file, in parallel.)
   Pair tests that restore and compare a big guest window per pair use `PairRange` (`tests/game/write_tracker.h`:
   only the pages written are copied; copying 2–32 MiB per pair was most of the suite's time) — use it for any
   window of a MiB or more.
3. **Once, at the end: the gate script** (since 2026-10-20 — three replay gates, the fast build, uncapped runs):
   `powershell -File F:\P3FES-PORT\p3fes-port\tools\ours\gate\gate.ps1 -Repo <your worktree> -Tree build\<slice>-gate -ClangTree build\<slice>-clang -FastGs`
   (`-FastGs` is the standard since wave 7: the user's "fastest version" rule; drop it only to compare with software)
   Run the MAIN tree's copy with `-Repo` (fixes reach you at once). It builds MSVC Release with VU1 compiled ahead of
   time for the two hot programs, emits with `--replace`, runs ctest + `p3fes_game_tests` on MSVC and clang-cl, then
   the dorm, M1 and **battle** gates with `--vu1 aot` against the main tree's references and prints `GATE: PASSED`
   or `GATE: FAILED` (expected frames dorm `EE0EB5DA…`, M1 `E3A93615…`, battle `CFAA5A61…`, all `differing bytes: 0`).
   Report its output verbatim. Add `-FastGs` to rasterise the three replay gates on the GPU (offscreen D3D11, exact
   mode: byte-identical to the software GS, also `gsMemory.bin`; dorm ~7×, battle ~4× faster); the routes run in
   parallel with the suites (`-Serial` for the old order), so a warm gate takes ~4 min instead of ~28.
   Suites (since 2026-10-20): `p3fes_game_tests` is one ctest entry per test file (`ctest -j`; the gate prints the
   summed case/assertion counts and fails unless they equal the binary's own `--count`), and the clang-cl tree is
   **Release** (an existing Debug `-ClangTree` is re-configured once, a full rebuild). `-ClangDebug` and
   `-WholeGameTests` restore the old arrangement; `-TestJobs N` sets `ctest -j` (default `-Jobs`). The suites now
   take ~1 min per compiler (were 7–39 min), so a warm gate is as long as the battle route (~3–4 min).
   The battle gate (Tartarus save → a fight → result screen) is the only one that runs
   battle code; the reference is a build with **no** replacements, so any byte is a real behavioural difference.
   Every game run is uncapped: headless runs are never paced; if you open a window, add `--unpaced` and give the run a
   kill timeout (Start-Process + WaitForExit(ms) + Stop-Process). The manual commands below are the fallback only.
   Old manual recipe (two routes) —
   dorm `build\<slice>-msvc\bin\p3fes.exe --elf <ELF> --iso <ISO> --headless --quiet --memcard new --replay-input config\inputs\to_dorm.txt --snapshot-at vblank:4900 extracted\_ours\<slice>_dorm`
   → `frame.png` SHA-256 `EE0EB5DA4042B0429B6E04A6C41641DE6AE07DABE028884E5B07AB88FE795D85` and
   `build\<slice>-msvc\bin\tracediff.exe snapshot F:\P3FES-PORT\p3fes-port\extracted\_ours\dorm_replay_4900\eeMemory.bin extracted\_ours\<slice>_dorm\eeMemory.bin --dead-stack extracted\_ours\<slice>_dorm\capture.json`
   → `differing bytes: 0`; M1 `--snapshot-at sky:11 extracted\_ours\<slice>_m1` vs
   `F:\P3FES-PORT\p3fes-port\extracted\_ours\v_m1` (frame
   `E3A93615056A12B632B697AAE5A1DF59C1CB67AB119ACFC787AE44869602B672`, 0 bytes). Anything else is a slip to find.
   The clang tree only needs the test suites.

## Machine states: resume a run near where it matters (since 2026-10-21; `runtime/STATE.md`)

- `p3fes.exe <route args> --save-state-at vblank:N s.p3st` writes the whole machine at a vblank boundary (~30 MiB,
  < 1 s); `p3fes.exe <route args> --load-state s.p3st --snapshot-at vblank:M DIR` resumes it in a fresh process and
  is exact: eeMemory.bin, gsMemory.bin, frame.png and capture.json equal a straight run to M byte for byte (checked
  on all five routes and the full climb with `--gs-backend d3d11 --gs-exact`, on dorm and battle with the software
  GS, and across the two). Keep the route's
  `--memcard` (any copy of its card: the state replaces the image) and its `--vu1`/GS flags; the state carries the
  pad replay position, so `--replay-input` is optional on load. `flip:N`, `sky:N`, `cycles:N` work like
  `--snapshot-at`.
- **Same `p3fes.exe` only.** A state holds the host stacks of the suspended guest threads (recompiled call chains),
  so it loads only into the executable that wrote it (checked: file hash, image base, ELF, `--sk`/`--iop-layout`/
  `--spu2-interp`); rebuilding invalidates your states. Not with `--trace-syscalls`/`--trace-hw`.
- **Dev-only build option.** States need a tree configured with `-DP3FES_MACHINE_STATES=ON` (the gate configures
  its tree so; add it to a slice tree you want states in). ON means `p3fes.exe` has no ASLR (`/DYNAMICBASE:NO`) and,
  when loading, adopts the /GS cookie stored in the state: a state file is raw host stacks and return addresses,
  so **loading one is equivalent to running its author's code -- never load a state from someone else, never ship
  an ON build.** OFF (the default; play builds, later the multiplayer client and server) is a normal ASLR build and
  `--save-state-at`/`--load-state` refuse. These trade-offs are for this local dev build only.
- **Reference mode** (`--reference-mode`): every function in `game/replaced.txt` runs as its recompiled original
  (`__recomp`, kept in every build; generated call sites and dispatch rows go through `fn_*__sel` selectors), so
  your own build *is* the zero-replacement program -- checked equal to the norep references on all six routes
  (eeMemory, gsMemory, frame). Use it instead of a separate norep build: e.g. run a route with and without
  `--reference-mode` to the same `--snapshot-at` and tracediff the two; to bisect a divergence, save a state in
  reference mode before it and resume it in hand mode (no flag) with more snapshot points. The selectors cost
  nothing measurable (battle route, median user CPU 91.4 s with and without).
- Slice-agent use: when a route differs, find the first differing vblank (`--snapshot-at` points, tracediff), save
  a state a few hundred vblanks before it once, then iterate diagnostics from the state in seconds instead of
  re-booting each time: `--load-state s.p3st --watch-write VA+LEN 16 --snapshot-at vblank:K DIR`, `--trace-gs A-B`,
  `--sound-log`, more `--snapshot-at` points. A code change means a rebuild and a new state (one run to the point).
- Gate: `-StateCheck` adds a round trip to every route (save mid-way, resume in a fresh process, compare with the
  route; ~+6 s); `tools/ours/state/state_roundtrip.ps1` checks chosen points of one route;
  `tools/ours/state/state_segments.ps1` re-runs a route's stretches in parallel from one build's states. A component
  that gains machine state needs a `state(StateIo&)` (the round trip finds what is missing).
- **Segment mode** (`gate.ps1 ... -FastGs -Segments [-Routes climb] [-SegmentJobs 8]`): your executable runs each
  route in reference mode from boot, saving a state + snapshot at each mark (`$segmentMarks`; the climb in six);
  every segment [S, E) then runs in **hand mode** from the reference state at S and must equal the reference
  snapshot at E. Frames suspended at S finish as originals and every new call goes to hand code, so each segment
  tests exactly the hand code running inside it: a difference is reported in the segment that causes it, and later
  segments start clean. The reference runs' ends are also checked against the norep references. It does not make a
  fresh build's gate shorter (each build makes its own reference states from boot; the segments overlap that run),
  it localises. Segments compare more points than the from-boot gate: before the audit merge, dorm 0-2500 showed 6
  heap bytes and climb 6500-13000 597 (transient: the from-boot gate's end points did not see them); at 2ccab12 all
  17 segments are clean, and a planted one-segment difference was reported in that segment only. The from-boot
  routes against the norep references stay the authoritative merge gate.

## Finish

Commit **once** on your worktree branch with explicit pathspecs (never `git add -A`; nothing under `extracted/`,
`build/`, `recomp/generated`, no `.i64`), message starting `game(<area>): ...` and ending with the line
`Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`. Report: branch + commit, functions replaced (name,
address, size, role), skipped with the exact reason, non-obvious cycle-model notes, pair-test counts on both
compilers, suite and gate results. Every number from a run you did.
