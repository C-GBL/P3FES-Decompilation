# Handoff — continuing the P3FES port on another machine

> **Status 2026-10-20 (session 4, `F:\P3FES-PORT\p3fes-port`):** the move is done. The tree was copied as a
> working tree (nothing regenerated); §2's ten WIP slices and §3's IDA master #3 are **finished and merged**
> (501 functions replaced, 16/16 both compilers, gates 0 bytes) — see `STATE.md` "Wave 6". §4–§5 are history
> now; machine specifics are in `STATE.md`'s machine note and `CLAUDE.md` (VS 2022 Community via vswhere,
> clang-cl from standalone LLVM 22.1.0). Integration trees: `build/f-int` (MSVC Release), `build/f-clang`.

_Rewritten 2026-10-20 for the second machine move. This machine is **clean** (it replaced the Expiro-infected
one on 2026-10-19; every tool on it was built from pinned source or hash-verified, Defender real-time on, no
detections). The move is voluntary. §8 keeps the first move's incident record as history._

## 1. Where the work stands (main @ the commit that adds this file; read `STATE.md` next)

| Phase | State |
|---|---|
| 0–2 | done |
| 3 recompiler + runtime | **done.** All 14,500 functions emitted; the game boots, plays through the opening and into the dorm (Milestone 4); the user played almost every segment without a visible bug. |
| 4 differential testing | **done.** `tracediff` snapshot oracle against clean PCSX2 2.8.2 captures at M1/M2/M3 and the user's dorm save state (M4): code band 0 bytes everywhere; 3,443 compiled EE semantics vectors run in PCSX2, 0 unexplained. |
| 5 hand-decompilation | **active, the priority.** 112 functions replaced by readable C++ in `game/` across all five GOAL.md areas (file system, BF script VM, BMD messages, menu/UI, battle); analyses `docs/ANALYSIS/18` (script VM), `20` (menu/UI), `21` (battle) with leaf-first queues; pair tests 52 cases / 4,095,035 assertions; whole-program gates byte-identical. |
| 6 polish | **paused by the user** (Phase 5 first). Done so far: memory card in `%APPDATA%\P3FES\saves`; sound effects (ADR-0014: the game's own SK/libsd IOP modules on an R3000 interpreter + an SPU2 voice model; menu SE within 0.5 dB of PCSX2). Open: reverb, battle sound bank, widescreen, pacing, config, installer. |

Last verified state of main (lead re-run, `build/r6-phase5` MSVC 14.44 Release + `build/r6-clang` clang-cl 19.1.5):
16/16 suites on both compilers; dorm replay `frame.png` `EE0EB5DA…5D85`, M1 `frame.png` `E3A93615…B672`, both
0 differing bytes outside the dead stack against the references `extracted/_ours/dorm_replay_4900` and
`extracted/_ours/v_m1`.

## 2. Unfinished work saved on branches (stopped by the user mid-task on 2026-10-20)

Ten Opus agents were working on Phase 5 slices in parallel worktrees under the shared brief
`docs/PHASE5_AGENT_BRIEF.md`. They were stopped before finishing; each slice was saved as one **WIP commit on its
branch** (on top of main `4b7ec1f`). None of them is reviewed, fully built or gated. Resume a slice by checking
out its branch, reading the brief and the diff, finishing it (pair tests on both compilers, the two replay gates)
and merging it to main the usual way.

| Branch (`worktree-agent-…`) | WIP commit | Slice | Where it stopped |
|---|---|---|---|
| `a677bffe7ed9a13ec` | `5241025` | **IDA master #3**: battle delta imported, `symbols/` re-exported, the 16 battle functions renamed | before its replay gates — see §3, do this one first |
| `a87c9427575398c77` | `619c955` | battle hit/damage/affinity `[0x302000, 0x30B600)` | code + tests written, `replaced.txt` being edited |
| `ad09ead66c1951bbd` | `4ae9874` | battle AICALC formulas + `datScriptGetValue` `[0x30B600, 0x310000)` | code written, CMake lists being edited; no test file yet |
| `a617c46a49bf8c9d1` | `d6637a5` | battle data / table readers (rest of `queue_battle.txt`) | code + header only; not in the lists yet |
| `ac56eae6da78eeda4` | `7e5beef` | script VM layer 2 (task lifecycle, `scrTraceCode`, section resolvers) | code written; test file not yet |
| `af33c0997db471401` | `e57e127` | BMD message manager layer 2 `[0x3A0000, 0x3AF000)` | code + tests; header being written |
| `a55cca573b67b075c` | `833c0ab` | font renderer (glyph index, Huffman decoder, measuring) `[0x3AF000, 0x3B6000)` | code + tests; header being written |
| `a88b0651535ba9d7c` | `ced8f82` | menu/calendar/camp layer 2 | code + lists; test file not yet |
| `aa0ddedb785c44d12` | `3686adc` | kwln task system | code + header only |
| `a4373dc6d9730fd2d` | `12235ce` | file system layer 3 (ROFS names, `H_Cdvd_Request/Destroy`) | code + tests + lists; fixes in progress |

Merging rule: the shared lists (`game/replaced.txt`, `game/CMakeLists.txt`, `tests/game/CMakeLists.txt`,
`game/README.md`, `docs/INTEGRATION_LOG.md`) conflict between slices; resolve as unions. The battle slices use
`sub_*` names; once the master #3 branch is merged, rename them to the new `symbols/functions.json` names (the
emitter's `--replace` check refuses a mismatch and says which).

## 3. The IDA master is one step ahead of main — read before touching `ida/`

`ida/p3fes.i64` already contains the battle delta (`symbols/deltas/battle.sym`, 138 names) imported by the
master #3 agent; main's `symbols/` does **not** contain the matching re-export yet. The re-export and the renames
are the WIP commit `5241025` on branch `worktree-agent-a677bffe7ed9a13ec`. Two ways to make them agree again:
(a) **finish that branch** — rebuild, run the pair tests and both replay gates, merge (recommended); or
(b) restore the master from `ida/p3fes.pre-wave5-20261020.i64` (the copy taken before the import) and re-import
later. Backups of every earlier master state: `p3fes.pre-wave2-20261020.i64`, `p3fes.pre-wave4-20261020.i64`,
`p3fes.i64.bak-20261018`. `tools/ours/ida/README.md` "Full rebuild from nothing" rebuilds a master from `symbols/`
alone (the round trip is equal since `7b80687`), so the master can also be recreated on the new machine.

## 4. What to move (this machine is clean, so data files may be copied; executables are rebuilt)

1. **The repository as a git bundle** (text only, every branch including the ten WIP branches):
   `git bundle create p3fes-port.bundle --all` → `git bundle verify p3fes-port.bundle` → on the new machine
   `git clone p3fes-port.bundle p3fes-port` and `git checkout main`. `extracted/_ours/p3fes-port.bundle` is an
   older bundle from the first move; the new one replaces it.
2. **Data you own, never in git** (copy as files; hash the ISO against `docs/INVENTORY.md` after copying):
   `input/persona3fes.iso`; the BIOS `tools/third_party/pcsx2/bios/ps2-0230a-20080220.bin` (SHA-256 in `CLAUDE.md`);
   `ida/p3fes.i64` and its backups (§3); the PCSX2 reference captures `extracted/_pcsx2/` (first_flip, atlus_logo,
   title_runC/D, the user's dorm state `dorm/`, the audio reference `audio/title_prompt.wav`) — they cannot be
   regenerated without replaying in PCSX2; the gate references `extracted/_ours/dorm_replay_4900` and
   `extracted/_ours/v_m1` (regenerable with the commands in §6, but copying saves a run); memory cards
   (`extracted/_ours/memcards/`, `%APPDATA%\P3FES\saves\Mcd001.ps2`).
3. **Not moved:** `build/`, `recomp/generated/`, `.claude/worktrees/`, the rest of `extracted/` (regenerated from the
   ISO, §5), `deps/venv/` (recreate), `tools/bin/` and `tools/third_party/` (rebuild or re-fetch with hash checks).

## 5. Setting up the new machine

`CLAUDE.md` is the environment guide (tool table, pins, security rules). In order:
1. VS 2022 Build Tools 17.14 (MSVC 14.44, SDK 10.0.26100) with the "C++ Clang tools for Windows" component
   (clang-cl 19.1.5); its bundled CMake + Ninja. `tools/env.ps1` enters the dev shell and reports every tool.
2. Python 3.14 (user install); venvs `deps/venv/rabbitizer` (rabbitizer 1.16.2) and `deps/venv/idalib` (from IDA's
   `idalib\python` wheel + `py-activate-idalib.py`).
3. IDA Pro 9.3 (licensed). PCSX2 2.8.2 portable under `tools/third_party/pcsx2/` with the BIOS; apply the oracle ini
   with `python -I tools\ours\pcsx2\configure_ini.py --fastboot on` (normalized hash `2630dac3…2a59`).
4. EE toolchain (gcc 15.2 / binutils 2.45.1) only if you will regenerate the EE semantics vectors
   (`tools/ours/eevec/`); recipe and pins in `CLAUDE.md`. Ghidra, .NET and the Atlus tools are optional now.
5. Extract the disc: `python -I tools\ours\cvm\cvm_extract.py` per `docs/DISC_LAYOUT.md` (12,019 files,
   `--verify` 0 failures; the ELF hash is checked by the recompiler).
6. Never run a downloaded executable until its hash matches the vendor's; check new PE files for an appended W+X
   last section (the Expiro marker).

## 6. Build, run and the gates (the commands every merge uses)

```powershell
. .\tools\env.ps1
cmake --preset msvc-x64-release -B build\int -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt
cmake --build build\int --target p3fes_recomp
build\int\bin\p3fes_recomp.exe --elf extracted\disc\SLUS_216.21 --functions symbols\functions.json `
  --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated --replace game\replaced.txt
cmake --build build\int ; ctest --test-dir build\int          # 16/16
cmake --preset clangcl-x64-debug -B build\clang ; cmake --build build\clang ; ctest --test-dir build\clang
# replay gates
build\int\bin\p3fes.exe --headless --quiet --memcard new --replay-input config\inputs\to_dorm.txt --snapshot-at vblank:4900 extracted\_ours\g_dorm
build\int\bin\tracediff.exe snapshot extracted\_ours\dorm_replay_4900\eeMemory.bin extracted\_ours\g_dorm\eeMemory.bin --dead-stack extracted\_ours\g_dorm\capture.json
build\int\bin\p3fes.exe --headless --quiet --snapshot-at sky:11 extracted\_ours\g_m1
build\int\bin\tracediff.exe snapshot extracted\_ours\v_m1\eeMemory.bin extracted\_ours\g_m1\eeMemory.bin --dead-stack extracted\_ours\g_m1\capture.json
# play (windowed; saves in %APPDATA%\P3FES\saves)
build\int\bin\p3fes.exe
```

Expected: `frame.png` hashes `EE0EB5DA4042B0429B6E04A6C41641DE6AE07DABE028884E5B07AB88FE795D85` (dorm) and
`E3A93615056A12B632B697AAE5A1DF59C1CB67AB119ACFC787AE44869602B672` (M1); `differing bytes: 0` in both diffs. If the
references were not copied, generate them once from a build of `main` and keep them. On a faster host the dorm
route (5,200 vblanks) took 140 s on this VM.

## 7. Next actions (in order)

1. Finish and merge the **IDA master #3** branch (§3), so `symbols/` matches the master again.
2. Finish the nine Phase 5 WIP slices (§2) — or relaunch them as agents with `docs/PHASE5_AGENT_BRIEF.md` and the
   slice line from the table; the user wants Opus 5.5 for every agent.
3. Continue the queues (`docs/ANALYSIS/queue_*.txt`), leaf-first; import each slice's names delta into the master
   (one agent at a time owns the master).
4. Phase 6 stays paused until the user resumes it (reverb, battle sound bank, widescreen, pacing, installer).
5. Small items: doc corrections (contract L-33/34/40, I-12…I-14, `12` §2.1/2.2, `14` SETIQ words, PATH3 wording);
   the old branch `wip/wave4-wiring` is fully merged and can be deleted (user's call).

## 8. Rules that carried the project (keep them)

- Decisions are ADRs in `docs/DECISIONS.md` (0001–0014, append-only). The shaping ones: ADR-0002 (IDA via idalib),
  ADR-0004/0011 (recompile raw words, own decode table), ADR-0009 (unverified community names never committed),
  ADR-0010 (own recompiler; MIT `ps2-web-recomp` as the only code source; GPL `PS2Recomp`/`p3fes-recompiled`/PCSX2
  source never opened), ADR-0012 (PCSX2 as state oracle), ADR-0013 (one host thread, fibers, virtual time),
  ADR-0014 (sound effects through the game's own IOP modules).
- Never commit game data, BIOS, memory-card images, save states, generated code, IDA databases, or anything under
  `tools/third_party` / `tools/bin`.
- Every replaced function passes its pair test and the whole-program replay gates before it lands; every claim is
  tagged obs/der/inf; never report a run you did not do.
- Agents: one worktree and one build directory each; the IDA master has exactly one owner at a time.

### History: the first move (2026-10-18/19)

The first machine carried an active PE file infector (Win32/Expiro): Defender quarantined freshly built
`p3fes.exe`/`tracediff.exe` and `C:\ninja\ninja.exe`, and PE-header reads confirmed the appended W+X `.reloc`
section on many third-party tools and every build output. Only git objects moved; every tool was rebuilt from
pinned source on this machine, `extracted/` was regenerated, the PCSX2 captures were retaken, and the old IDA
master (a data file) was kept on the user's decision after its export proved equal to `symbols/`.
