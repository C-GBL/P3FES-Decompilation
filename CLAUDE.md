# P3FES port — session setup

Read `STATE.md` first, then `docs/HANDOFF.md` (this machine replaced one infected with Win32/Expiro on 2026-10-18).
Phase 5 slice agents read `docs/PHASE5_QUICK.md` plus their `packet.md` instead of STATE.md / HANDOFF / the full brief.

## Environment: run this first in every PowerShell session

```powershell
. .\tools\env.ps1
```

It enters the VS 2022 x64 dev shell and puts everything below on PATH, then prints where each tool resolved. Nothing is on PATH without it. `cl`, `cmake`, `ninja` and `msbuild` come from VS Build Tools 17.14 (MSVC 14.44, SDK 10.0.26100), never from loose copies (there is no `C:\ninja`).

| Need | Location | Notes |
|---|---|---|
| Python 3.14 | `%LOCALAPPDATA%\Programs\Python\Python314\python.exe` (`$env:P3FES_PYTHON`) | **Not** `C:\Python314` as older docs say. Run tool scripts with `-I`. |
| rabbitizer 1.16.2 (decode oracle) | venv `deps\venv\rabbitizer` (`$env:P3FES_RABBITIZER_PY`) | Interpreter for `recomp/tests/oracle_decode.py`. `build\rabbitizer-venv` is from the old machine: don't use it. |
| EE toolchain: gcc 15.2.0, binutils 2.45.1 | `tools\third_party\ps2dev\ps2dev\ee\bin` (`$env:PS2DEV`) | No gdb (skipped on purpose). Needs the 8 bundled MinGW DLLs beside the exes. |
| PCSX2 2.8.2 (portable) + BIOS v2.30 | `tools\third_party\pcsx2\` (`$env:P3FES_PCSX2`), BIOS in `bios\ps2-0230a-20080220.bin` | Byte-identical to the official release. BIOS SHA-256 `f609ed1ca62437519828cdd824b5ea79417fd756e71a4178443483e3781fedd2`. |
| cvm_tool | `tools\bin\cvm_tool.exe` | Built with `cl /FImalloc.h /D__builtin_alloca=_alloca`. |
| vgmstream-cli r2117 | `tools\bin\vgmstream\vgmstream-cli.exe` | Built with every external codec off (no `ext_libs` DLLs). |
| Atlus-Script-Tools, PersonaEditor, AtlusFileSystemLibrary/PAKPack, Amicitia, ps2sdk | `tools\third_party\<name>` | Pinned commits as in `docs/TOOLS.md`. .NET builds are in each repo's `bin`/`Build` dir. |
| ps2-web-recomp, rabbitizer source | `tools\third_party\_community-eval\` | Read-only references. |
| IDA Pro 9.3 (licensed) | `C:\Program Files\IDA Professional 9.3` (`$env:P3FES_IDA_DIR`) | idalib venv `deps\venv\idalib\Scripts\python.exe` (created 2026-10-19 from IDA's `idalib\python` wheel + `py-activate-idalib.py`); every `tools/ours/ida` script runs under it. |
| Ghidra 12.1.4 + EE extension v2.1.38 | `C:\ghidra` (`$env:GHIDRA_INSTALL_DIR`) | Extension built from source; no prebuilt `stdump.exe`. |
| JDK 21, Gradle 9.7.1 | `C:\Program Files\Java\jdk-21.0.12.1`, `deps\tools\gradle-9.7.1` | Gradle zip hash-checked; don't use Ghidra's unpinned wrapper. |
| .NET SDK 8, Git, MSYS2 | system installs; MSYS2 at `C:\msys64` (MINGW64) | MSYS2 is only for rebuilding the EE toolchain. |

Disc image: `input/persona3fes.iso` (SHA-256 in `docs/INVENTORY.md`, verified). `extracted/` was regenerated 2026-10-19 (12,019 files, 0 verify failures, ELF hash matches).

**IDA master:** `ida/p3fes.i64` is the old machine's master database, kept on the user's decision (it is a data file, not a PE; its export equals `symbols/` byte for byte apart from timestamps). The other old databases are in `ida/_old_machine/`. A from-text rebuild (`ida/p3fes.fresh-rebuild.i64`) is **lossy** — `tools/ours/ida/README.md` "Round-trip gaps" — so never replace the master with one.

## Builds

- Configure into your **own fresh** dir: `cmake --preset msvc-x64-debug -B build/<name>`. The ~66 old dirs in `build/` came from the infected machine (their executables were deleted): never reuse them. Clean trees on this machine: `build/clean-msvc-x64-debug` (Debug, no game data), `build/r6-phase5` (Release + `-DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt`, runs the game; the integration tree since 2026-10-20), `build/r6-clang` (clang-cl Debug); 16/16 suites. **Since Phase 5, emit with `--replace game\replaced.txt`** (`recomp/README.md` "Replacements"); older game trees (`r1-msvc-int-rel`, `r3-inl`) no longer link against the current `recomp/generated` (duplicate symbols, by design).
- clang-cl 19.1.5 is installed as the VS Build Tools "C++ Clang tools for Windows" component (`VC\Tools\Llvm\x64\bin`, Microsoft-signed; installed by the user through the Visual Studio Installer on 2026-10-19). The old machine had LLVM 22; the `clangcl-x64-debug` preset works with this one. Keep every suite green on both compilers.

## Security rules (from the Expiro incident)

- Never run a downloaded executable until its hash or signature matches the vendor's published value. Prefer building from pinned source.
- `tools/fetch_tools.ps1` and `docs/TOOLS.md` still describe the **old prebuilt** downloads: don't run that script as-is.
- After building third-party code, check new PE files for the Expiro marker (appended W+X last section) and scan with Defender.
- Defender is active (real-time on). Don't put malware-indicator keywords (e.g. `DownloadString`, `EncodedCommand`) on a command line: its ML engine flags the command itself. Put such patterns in a file.
- Local, uncommitted edits to third-party clones: `pcsx2/.github/workflows/scripts/windows/build-dependencies.bat` (`vswhere -products *`, HarfBuzz `CLAUDE.md` symlink excluded). The `pcsx2` folder now holds the release, not source.

## EE toolchain pins (all were floating branches; resolved 2026-10-19)

ps2toolchain `v2.0.0` → ps2toolchain-ee `v2.0.0` (`3fe7fd71`) with binutils-gdb `616e51fa6ed9`, gcc `df77d03bc1bd`, newlib `8881dc4b138f`, pthread-embedded `b1746fd2b52d`. Rebuild recipe: run the `ps2toolchain-ee/scripts/00*.sh` steps under MSYS2 MINGW64 with `PS2DEV_CONFIG_OVERRIDE` setting those SHAs as the refs; sources in `deps/build/ps2toolchain-ee-src`.
