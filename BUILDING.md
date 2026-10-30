# Building the port

Windows x64 only. No package manager, no network at configure time
(doctest is vendored under `tests/vendor/`).

## Toolchain (verified 2026-10-18)

| Tool | Location |
|---|---|
| MSVC 14.44 (VS 2022 Build Tools 17.14) | `C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools` |
| clang-cl 22.1 | `C:\Program Files\LLVM\bin\clang-cl.exe` |
| CMake 4.3.1 | `C:\Program Files\CMake\bin` |
| Ninja 1.13 | `C:\ninja\ninja.exe` |
| Windows SDK 10.0.26100 | d3d11 / dxgi / xaudio2 / xinput headers and import libs |

`cl.exe` is **not** on `PATH`. Every preset (including clang-cl, which needs
the MSVC STL and the Windows SDK) must run inside a VS x64 developer shell
(`. .\tools\env.ps1` in PowerShell does this). The `clangcl-x64-debug` preset
takes `clang-cl` from `PATH`: on this machine that is the VS Build Tools
"C++ Clang tools for Windows" component (clang 19.1.5, Microsoft-signed), which
the developer shell puts on `PATH`; a standalone LLVM works the same way.

```bat
"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
set PATH=C:\ninja;C:\Program Files\CMake\bin;%PATH%
```

(PowerShell: `Import-Module` the `Microsoft.VisualStudio.DevShell.dll` under
`Common7\Tools\` and run `Enter-VsDevShell -Arch amd64 -HostArch amd64`, or
use `Launch-VsDevShell.ps1`.)

## Presets

All presets use the Ninja generator and build into `build/<preset>/`;
binaries land in `build/<preset>/bin/`.

| Preset | Compiler | Config |
|---|---|---|
| `msvc-x64-debug` | cl | Debug |
| `msvc-x64-release` | cl | Release |
| `clangcl-x64-debug` | clang-cl | Debug |
| `clangcl-x64-release` | clang-cl | Release (the gate's second-compiler suite tree) |

```bat
cmake --preset msvc-x64-debug
cmake --build --preset msvc-x64-debug
ctest --preset msvc-x64-debug
build\msvc-x64-debug\bin\p3fes.exe --smoke
```

`p3fes --smoke` creates the window, a D3D11 device + swap chain and an
XAudio2 engine, presents three frames and exits 0. `--selftest [--headless]`
draws the GS self-test scene.

## Running the recompiled game (Phase 3 integration)

Needs the emitted program (`p3fes_recomp --out recomp\generated --replace game\replaced.txt`,
`recomp/README.md` "Replacements": since Phase 5 the hand-decompiled functions in `game/` take the
place of their recompiled bodies, and an emission without `--replace` fails the link on purpose)
and a configure with `-DP3FES_RECOMP_GENERATED=ON`; then `p3fes` composes the runtime
(`runtime/app/game_host.h`), loads the SHA-checked ELF and runs `start`:

```bat
cmake --preset msvc-x64-release -B build\msvc-int-rel -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt
cmake --build build\msvc-int-rel --target p3fes tracediff p3fes_gscmp
:: windowed (presents on every GS flip, paced to the wall clock)
build\msvc-int-rel\bin\p3fes.exe
:: Milestone 1 snapshot, headless (PCSX2 first_flip point: g_skyFrameCount 11 at a VBLANK_START)
build\msvc-int-rel\bin\p3fes.exe --headless --quiet --snapshot-at sky:11 extracted\_ours\first_flip
build\msvc-int-rel\bin\tracediff.exe snapshot extracted\_pcsx2\first_flip\eeMemory.bin extracted\_ours\first_flip\eeMemory.bin
```

Options: `--iso PATH` / `--extracted DIR`, `--frames N` (vblanks), `--until-flip N`,
`--until-cycles N`, `--until-sky N`, `--snapshot-at flip:N|vblank:N|cycles:N|sky:N DIR`
(eeMemory.bin + frame.png + capture.json), `--png PATH`, and for triage
`--trace-syscalls N`, `--trace-hw N`, `--trace-sif`, `--watch-write VA[+LEN] N`.
Results and the issue log: `docs/INTEGRATION_LOG.md`.

## Targets

| Target | Kind | Source | Purpose |
|---|---|---|---|
| `p3fes_runtime` | static lib | `runtime/` | EE memory/context, syscall table, HLE, VU1, GS (D3D11), SPU2 (XAudio2) |
| `p3fes` | exe | `runtime/app/` | host executable |
| `p3fes_recomp` | exe | `recomp/` | static recompiler (CLI stub) |
| `p3fes_game` | static lib | `game/` | hand-decompiled game code (Phase 5; `game/replaced.txt`, `game/README.md`) |
| `tracediff` | exe | `tools/ours/tracediff/` | snapshot divergence finder (`docs/TRACE_FORMAT.md`) |
| `p3fes_tests` … | exe | `tests/` | doctest suites, registered with ctest (16, incl. `p3fes_game_tests`: Phase 5 replacements against their recompiled bodies) |

Compiler flags: C++20, `/W4 /permissive- /utf-8 /EHsc`. Warnings are not yet
errors; enable with `-DP3FES_WARNINGS_AS_ERRORS=ON`.

## Host executable options (input and presentation)

`p3fes` runs the recompiled game when built with `-DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt`. Beyond the headless/snapshot options documented in `runtime/app/game_host.h`: `--input-script "VBLANK:buttons[:frames],..."` (scripted presses, e.g. `560:left:4,580:cross:4`), `--record-input FILE` / `--replay-input FILE` (deterministic replays, ADR-0013 §4), `--fullscreen`, `--scale integer|smooth`, `--vsync on|off`, `--stats`, `--background-input`; keys: F12 screenshot to `extracted/_ours/screens/`, F11 or Alt+Enter full screen, F3 the frame-time overlay. Frame pacing and frame-time telemetry (`docs/ANALYSIS/31_frame_pacing.md`): `--pacing display|clock|legacy` (default display: one guest vblank per display refresh on 60/120 Hz, one timed Present per guest frame), `--present-delay-ms N`, `--frame-log FILE` (per-frame CSV; `tools/ours/perf/frame_report.py` folds it), `--frame-overlay`, `--frame-stats off`; the `p3fes: frame-time:` summary (interval percentiles, refreshes per frame, hitches with causes) is printed at exit of every windowed run. The keyboard/XInput map is `config/input.ini` (see `runtime/app/input.h`).

## Profiling

`p3fes --profile FILE [--profile-us N] [--profile-from VBLANK]` samples the host thread's instruction pointer
(default every 1000 µs; `--profile-from` starts at that vblank, e.g. after the boot) and prints the hottest
functions at exit, writing the full table to FILE (`runtime/app/host_profile.h`; after it, a "with callers" table
lists the samples as `function <- caller <- caller's caller`, so a memset or heap hit names the code that caused
it). Recompiled guest functions appear
under their generated names (`fn_<name>_<addr8>`), the adapter under `p3fes::rt::`, the GS under `p3fes::gs::`.
It needs a PDB; the Release preset has none, so configure a separate tree with debug info:

```powershell
cmake --preset msvc-x64-release -B build\prof -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt `
  -DCMAKE_CXX_FLAGS_RELEASE="/O2 /Ob2 /DNDEBUG /Zi /FS" `
  -DCMAKE_EXE_LINKER_FLAGS_RELEASE="/DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF"
cmake --build build\prof --target p3fes
build\prof\bin\p3fes.exe --headless --quiet --profile extracted\_ours\prof.txt --profile-from 6400 --snapshot-at sky:3315 extracted\_ours\prof_title
```

Inlined functions are attributed to their caller (the adapter's inline fast paths show up inside the generated
functions, runtime/rt/README.md "Inline fast paths").

`p3fes --zones FILE [--zones-every N]` is the other view: host wall time per **subsystem** (recompiled EE code,
kernel/scheduler, fiber switches, hardware registers + DMAC, VIF1, VU1, GIF, GS raster, GS uploads, IPU, IOP HLE,
R3000, audio, CDVD, present), measured at the subsystems' entry points with the TSC (`runtime/include/p3fes/prof.h`,
`runtime/app/host_zones.h`), plus workload counters (primitives by type, textured/bilinear pixels, upload qwords,
VU1 runs and pairs per uploaded program, GS SIGNAL/FINISH/LABEL per GIF path, R3000 instructions), one TSV row per
segment of N vblanks (default 50), written at exit. It needs no PDB and works in any build; off, it costs one
predictable branch per entry point and changes nothing the guest sees. Fold the rows into named ranges with
`tools/ours/perf/zones_report.py` (docs/ANALYSIS/23_performance_profile.md has the battle-route ranges):

```powershell
build\prof\bin\p3fes.exe --headless --quiet --memcard extracted\_ours\cards\tartarus.ps2 `
  --replay-input config\inputs\to_battle.txt --frames 6800 --zones extracted\_ours\zones_battle.tsv
python -I tools\ours\perf\zones_report.py extracted\_ours\zones_battle.tsv --seg field=3500:5300 `
  --seg battle=5300:6100 --vu1 battle
```

Each row also carries the host thread's and the process's CPU time (cycle counts at the TSC rate), the machine's busy
share, the D3D11 renderer's counters (lists, presents, render-thread busy time and CPU, GPU time from timestamp
queries) and the guest's running kwln task names; `FILE.frames.tsv` has one row per game frame. With the threaded
graphics pipeline (`--gs-threads`, default 2; docs/ANALYSIS/32) the EE thread's zones gain `gs_wait` (waiting for a
worker) and each row carries the workers' own zones (`w0_*` = the VU1 worker, `w1_*` = the GS worker: vif1, vu1, gif,
gs_raster, gs_upload, gs_submit, gs_wait, busy) and CPU time (`cpu_w0`, `cpu_w1`); the console table lists them per
thread. `--gs-threads off` measures the synchronous model.

**The performance harness** (`tools/ours/perf/bench.py`, docs/ANALYSIS/23 "Re-measure 2026-10-25") runs the six replay
routes with `--zones`, windowed (D3D11, `--unpaced`, a kill timeout) and headless (`--gs-backend d3d11 --gs-exact`),
cuts every route into segments by what is on screen (title, movie, load, menu, field, Tartarus, event, battle, result:
from the running task names) and prints per segment the game thread's CPU ms per frame, graphics CPU ms by subsystem,
render-thread CPU, GPU ms, x real time (wall and CPU) and frame-time percentiles, plus `report.json` / `report.csv`;
`compare` puts two runs side by side. The machine is shared: read the CPU columns, not the wall-clock ones.

```powershell
python -I tools\ours\perf\bench.py run --exe build\<tree>\bin\p3fes.exe --out <dir> [--routes battle,dorm] [--modes windowed,headless] [--repeat 2]
python -I tools\ours\perf\bench.py report <dir> [--timeline] [--vu1] [--tasks]
python -I tools\ours\perf\bench.py compare <dirA> <dirB>
```

## Scripted path into the game (`config/inputs/to_dorm.txt`)

A pad log recorded by the user on 2026-10-19 (fresh memory card, `--memcard new`): START through the Atlus/Sofdec
screens and the opening movie, cross through the title, the Journey/Answer screen and the main menu (New Game), cross
through the "played before" dialogue and the settings prompt, START through the three FMVs, then into the opening
event. Replayed headlessly it reaches the Iwatodai dorm lobby (`4/7 Tu Late Night`, Mitsuru's "My name is Mitsuru
Kirijo..." line) at vblank 4900, deterministically:

```powershell
build\<tree>\bin\p3fes.exe --headless --quiet --memcard new --replay-input config\inputs\to_dorm.txt `
  --snapshot-at vblank:4900 extracted\_ours\dorm
```

Use it as the fixed route for in-game comparisons and performance runs (5,200 vblanks = 86.8 virtual s; 319 s wall
on the VM at the 2026-10-19 software-GS speed).
