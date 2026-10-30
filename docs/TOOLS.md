# Tools inventory

_Owner: tooling agent. Reproduce everything below with `tools/fetch_tools.ps1`
(PowerShell 5.1). `tools/third_party/`, `tools/downloads/` and `tools/bin/` are
gitignored; the script plus this file are the record. Nothing in `tools/` is
derived from the disc. Last verified: 2026-10-18._

Conventions: **Observed** = we ran it on this machine and saw the result.
**Source-derived** = read from the upstream repository, not executed.
**Not attempted** = exactly that.

| Tool | Pinned | Built here? | Phase |
|---|---|---|---|
| cvm_tool (JayFoxRox/roxfan) | `33d937a5` | yes, clang-cl -> `tools/bin/cvm_tool.exe` | 1 |
| Atlus-Script-Tools (AtlusScriptCompiler) | `1c557a09` + release zip | yes, dotnet (net8.0) + prebuilt | 1, 5 |
| PersonaEditor / PersonaEditorLib | `5305355d` | yes, dotnet (net8.0) | 1, 5 |
| AtlusFileSystemLibrary + PAKPack | `d70da989` | yes, dotnet (.NET Fw 4.8 override) | 1 |
| Amicitia (reference source) | `6b6312af` | no (unlicensed; net47 chain) | 1 (reading only) |
| ps2sdk source | `329e2bb4` | headers only | 2, 3 |
| ps2dev v2.0.0 Windows toolchain (EE gcc 15.2.0) | `v2.0.0` tarball | prebuilt; runtime DLLs added | 2, 3, 4 (optional) |
| PCSX2 v2.8.2 Qt x64 | `v2.8.2` 7z | prebuilt | 0, 4 |
| vgmstream r2117 win64 | `r2117` zip | prebuilt | 1 |
| ghidra-emotionengine-reloaded v2.1.38 | zip for Ghidra 12.1.4 | prebuilt extension | 2 (secondary) |

---

## CVM / ROFS container extractor: `cvm_tool`

- **Purpose here:** read the CRI ROFS header of `DATA.CVM`, `BTL.CVM`, `BGM.CVM`
  and split off the embedded ISO 9660 image so ordinary ISO tooling (7-Zip,
  or our own parser in `runtime/formats/`) can list and extract files. `info`
  also tells us whether a volume is encrypted (ROFS supports a password-derived
  sector cipher; the tool implements roxfan's decryptor).
- **Upstream:** https://github.com/JayFoxRox/cvm_tool (roxfan's original ROFS
  tool, CMake-ified by JayFoxRox). Commit `33d937a5059d1a06e3e0ab60cd372794ccbdf456`
  (2020-04-04).
- **License:** mixed and **not clean**. README: JayFoxRox's contributions CC0;
  roxfan's original code has *no* stated license ("assume All Rights
  Reserved"). Use as a local tool only; do not vendor its source into
  `runtime/`. (Lead decision: acceptable for Phase 1 extraction? Our own
  ROFS/ISO reader in `tools/ours/` would remove the dependency; the format is
  small: 0x800-byte `CVMH` chunk, `ZONE` chunk, ISO 9660 from sector 3.)
- **Build (observed):** upstream `CMakeLists.txt` has no `cmake_minimum_required`
  and injects POSIX shims (`-D_fseeki64=fseek`, `-D__int64=off_t`) that break
  MSVC CRTs, so the script compiles the four .cpp files directly:
  `clang-cl /O2 /EHsc /D_FILE_OFFSET_BITS=64 ... /link /OUT:tools/bin/cvm_tool.exe`.
  Result: **built**, 188 KB, 12 warnings, 0 errors.
- **Invoke:** `tools\bin\cvm_tool.exe info <file.cvm>` ·
  `tools\bin\cvm_tool.exe split <file.cvm> <out.iso> [<out.hdr>]` ·
  `-p <password>` for encrypted volumes.
- **Observed on the real files (read-only `info`, nothing written):** all three
  CVMs report `FS id: ROFS`, `maker id: 'ROFSBLD Ver.1.52 2003-06-09'`,
  `ISO start sector: 3`, 2048-byte sectors, and `info` walked the directory
  tree (`BUSTUP/`, `*.BIN;1` entries) **without any password**, which is
  consistent with the volumes being unencrypted. `info` exits non-zero
  (`-1`) after dumping the directory on `DATA.CVM`; cause not investigated
  (Phase 1 item). `split` was **not** run.
- **Alternatives evaluated:** TGE's *AtlusFileSystemLibrary* has **no** CVM
  code (only PAK/ACX/APAK/DDS3/LB/SMT1). TGE's *Amicitia* has
  `AmicitiaLibrary/FileSystems/CVM` + `ISO` (C#) but no license (see below).
  Community guides note a CVM is an ISO with a 0x1800-byte prefix, so 7-Zip
  can often open the `.iso` produced by `split` directly.

## Atlus script toolchain: `Atlus-Script-Tools` (AtlusScriptCompiler)

- **Purpose here:** disassemble/decompile **BF** flow scripts and **BMD**
  message scripts from the extracted data (Phase 1 manifest; Phase 5 BF VM
  reimplementation reference). `AtlusScriptLibrary.dll` (net8.0) is callable
  from our .NET 9 tooling; it carries the P3FES function library
  (`Libraries/Persona3FES/*.json`) and the `P3` charset table.
- **Upstream:** https://github.com/tge-was-taken/Atlus-Script-Tools (the
  repository formerly known as AtlusScriptToolchain; the old URL 404s).
  Commit `1c557a092dd7610829b7215be0f0f5101acf1d72` (2026-05-17); release
  `v1.0-1c557a09…` zip, SHA-256
  `fb73bfb4976e48406ebd36991f23335728b212775507cb73b5b8bec8a1e9575d` (publisher digest).
- **License:** GPL-3.0 (`LICENSE.txt`). Fine as a tool; do not link it into the
  shipped port.
- **Build (observed):** `dotnet build Source/AtlusScriptCompiler/AtlusScriptCompiler.csproj -c Release`
  with .NET SDK 9.0.304 -> **built**, 54 warnings, 0 errors. Output goes to
  `tools/third_party/Atlus-Script-Tools/Build/Release/net8.0/` (repo-level
  `Directory.Build.props`). Runs on the installed 8.0.19 runtime (observed:
  prints `AtlusScriptCompiler 1.0-1c557a0`). Prebuilt release copy in
  `tools/bin/AtlusScriptCompiler/`.
- **Invoke (P3FES):**
  `tools\bin\AtlusScriptCompiler\AtlusScriptCompiler.exe -Decompile -In X.bf -Library p3f -Encoding P3`
  (library short name `p3f`, from `Libraries/Persona3FES.json`; `-Disassemble`
  for raw opcodes; `-OutFormat V1` is the P3/P4 binary format). Also ships
  `AtlusFlowScriptExtractor`, `AtlusMessageScriptExtractor`, `DumpProcedureIds`,
  `DumpMessageIds`.

## Persona format library: `PersonaEditor` / `PersonaEditorLib`

- **Purpose here:** MIT-licensed, **net8.0** parsers we can reference from
  .NET 9 or port to C++: `FileContainer/{BIN,PM1,BF,BVP,TBL}.cs` (PAC/BIN
  containers, PM1 model/event containers, TBL tables),
  `Sprite/TMX*.cs` (TMX textures incl. PS2 pixel formats / swizzle),
  `SpriteContainer/{SPR,SPD}.cs`, `Text/{BMD,PTP}.cs`, `Other/FNT*.cs`
  (font), `PersonaEncoding.cs` (P3 text encoding tables).
- **Upstream:** https://github.com/Meloman19/PersonaEditor, commit
  `5305355d159ee7d74eb830b325dd7a5f9a777961` (2024-12-27, release 1.6.7).
- **License:** MIT.
- **Build (observed):** `dotnet build PersonaEditorLib/PersonaEditorLib.csproj -c Release`
  -> **built**, 7 warnings, 0 errors: `tools/third_party/PersonaEditor/PersonaEditorLib/bin/Release/net8.0/PersonaEditorLib.dll`
  (+ `AuxiliaryLibraries.dll`). The WPF GUI (`PersonaEditor.csproj`) was not built.
- **Invoke:** library only (`GameFormatHelper.OpenFile(...)`, format classes
  above). No CLI.

## PAC/PAK container tools: `AtlusFileSystemLibrary` + `PAKPack`

- **Purpose here:** reference implementation + CLI for the several PAK/PAC/BIN
  pack layouts Atlus used (auto-detects variant), used to cross-check our own
  container parser in Phase 1.
- **Upstream:** https://github.com/tge-was-taken/AtlusFileSystemLibrary, commit
  `d70da989be2d82179b58b81c104b46778f409c91` (2020-07-09, "release-6").
- **License:** GPL-2.0.
- **Build (observed):** old-style csproj targeting .NET Framework **4.7**, whose
  targeting pack is absent here (`MSB3644`). 4.8 reference assemblies exist, so
  `dotnet build ... -p:TargetFrameworkVersion=v4.8` -> **built**
  (`Source/PackTools/PAKPack/bin/Release/PAKPack.exe`, runs on the OS's .NET
  Framework 4.8). Warning: `MoreLinq` reference unresolved (packages.config not
  restored) — build still succeeded; untested at runtime.
- **Invoke:** `PAKPack.exe unpack <file.pac> [outdir]` / `pack` / `list` /
  `replace` (see `Source/PackTools/PAKPack/Program.cs`).

## Amicitia (reference only)

- **Purpose here:** source reference for formats nothing else covers:
  `AmicitiaLibrary/FileSystems/{CVM,ISO,AMD,BVP}`, `Graphics/RenderWare`
  (RMD/RWS models, which is what P3FES PM1 files wrap), `Field`, TMX, SPR, PAK.
- **Upstream:** https://github.com/tge-was-taken/Amicitia, commit
  `6b6312af992d27cc8b45122480d5bb1b23aa4202` (2024-03-11, v1.9.6), submodules
  AtlusFileSystemLibrary `d70da989`, NvTriStrip.Net `0d06b041`.
- **License:** **none in the repository** (no LICENSE file, no header grants).
  Treat as all-rights-reserved: read to understand formats, re-implement
  independently, copy nothing.
- **Build (observed):** `AmicitiaLibrary` is netstandard2.0 but references the
  net47 `NvTriStripDotNet` and old OpenTK/SharpFileSystem binaries; `dotnet
  build` fails with `MSB3644` (no 4.7 pack) and `NETSDK1045` when overridden.
  **Not built**; the GUI is WinForms/.NET Framework anyway.

## ps2sdk headers (source checkout)

- **Purpose here:** authoritative struct/constant definitions for GIF tags,
  VIF codes, GS registers, DMA tags, SIF RPC, kernel syscalls — the vocabulary
  for Phase 2 (labelling SDK-like code in IDA) and Phase 3 (HLE layer).
  Note the game links Sony's proprietary `libsce*`, not ps2sdk; names and
  ABI differ, but hardware register/packet layouts are identical.
- **Upstream:** https://github.com/ps2dev/ps2sdk, commit
  `329e2bb43287e16af16c4dde1c614e2662c24468` (2026-10-13), shallow clone.
- **License:** Academic Free License 2.0 (`LICENSE`).
- **Where things are:** `ee/kernel/include/` (kernel.h, syscalls, sifdma.h),
  `common/include/` (`gif_tags.h`, `gif_registers.h`, `gs_gp.h`, `gs_privileged.h`,
  `gs_psm.h`, `vif_codes.h`, `vif_registers.h`, `tamtypes.h`),
  `ee/dma/include/` (`dma_tags.h`, `dma_registers.h`), `ee/packet2/include/`,
  `ee/rpc/*/include/` (cdvd, pad, memorycard, audsrv…), `iop/**/include`.
  Installed (preprocessed) copies live in the ps2dev tarball at
  `tools/third_party/ps2dev/ps2dev/ps2sdk/{ee,common,iop}/include/`. **libc
  headers** (newlib) are in
  `tools/third_party/ps2dev/ps2dev/ee/mips64r5900el-ps2-elf/include/`.
- **Build:** headers only; not attempted.

## EE toolchain: ps2dev v2.0.0 prebuilt (`mips64r5900el-ps2-elf-gcc` 15.2.0)

- **Purpose here:** optional. Assemble/compile test snippets to check our
  recompiler's understanding of R5900 encodings, build tiny PS2 ELFs to run in
  PCSX2 as differential-test vectors (Phase 4), `objdump -d` as a second
  disassembler opinion, `readelf` on the game ELF.
- **Upstream:** https://github.com/ps2dev/ps2dev release `v2.0.0`
  (2026-05-17, tag commit `69d11750`), asset `ps2dev-windows-latest.tar.gz`
  (272 MB), SHA-256
  `bab98ee210c62aa3bd98d9bdda2af3f92a628e6e3d63e4b52f243ae56e3eb4ce`
  (publisher digest). Built by ps2dev CI under **MSYS2 MINGW32** (32-bit
  binaries). Contains `ee/`, `iop/`, `dvp/` toolchains, `ps2sdk/`, `gsKit/`.
- **Licenses:** GCC/binutils/gdb GPL-3.0 (libgcc runtime exception),
  newlib (BSD-style, per-file), ps2sdk + gsKit AFL-2.0. MSYS2 runtime DLLs:
  libiconv LGPL, libwinpthread MIT/BSD, zstd BSD/GPL dual, gmp LGPL-3/GPL-2
  dual, isl MIT, mpc/mpfr LGPL-3, gcc-libs GPL-3+exception, expat MIT, xz
  (liblzma) 0BSD, termcap GPL-2.
- **Fix-up (observed):** the executables import MINGW32 DLLs ps2dev does not
  bundle (`libiconv-2`, `libwinpthread-1`, `libzstd`, `libgmp-10`, `libisl-23`,
  `libmpc-3`, `libmpfr-6`, `libgcc_s_dw2-1`, `libstdc++-6`, and for gdb
  `libexpat-1`, `liblzma-5`, `libtermcap-0`); without them gcc died with
  `STATUS_DLL_NOT_FOUND` and `cc1` failed silently. The script fetches the
  exact MSYS2 packages (11 packages, versions + recorded SHA-256 in
  `fetch_tools.ps1`; MSYS2 only publishes GPG signatures) and copies the 17
  DLLs into the three executable directories the Windows loader searches
  independently: `ps2dev/ee/bin/` (driver, binutils),
  `ps2dev/ee/libexec/gcc/mips64r5900el-ps2-elf/15.2.0/` (cc1, collect2, lto1)
  and `ps2dev/ee/mips64r5900el-ps2-elf/bin/` (the `as`/`ld` the driver really
  invokes). No PATH changes. The local `C:\msys64\mingw32\bin` is empty, so it
  could not be reused.
- **Smoke test (observed):** compile + link of a `kernel.h`/`gif_tags.h`
  snippet succeeded; exact commands and `readelf` output are in the log at the
  end of this file. `gdb` does not start (exit 127); everything else tried
  (`gcc`, `cc1`, `as`, `ld`, `objdump`, `readelf`) works.
- **Invoke:** `tools\third_party\ps2dev\ps2dev\ee\bin\mips64r5900el-ps2-elf-gcc.exe -D_EE -G0 -I<ps2dev>\ps2sdk\ee\include -I<ps2dev>\ps2sdk\common\include …`
  (`-D_EE` is required by `tamtypes.h`; `-G0` matches ps2sdk's defaults);
  link with `-L<ps2dev>\ps2sdk\ee\lib -T <ps2dev>\ps2sdk\ee\startup\linkfile … -lkernel`;
  `mips64r5900el-ps2-elf-objdump.exe -d`, `mips64r5900el-ps2-elf-readelf.exe -h`.
  The `ps2sdk/ee/lib/` directory holds `libkernel.a`, `libdma.a`, `libgraph.a`,
  `libgs.a`, `libdraw.a`, `libpacket*.a`, `libpad.a`, `libcdvd.a`, `libmc.a`… —
  homebrew analogues of the `libsce*` the game uses, handy as behavioural
  references for the HLE layer (AFL-2.0, so reading them is fine).
- **Not built from source.** The build route, if ever needed:
  `ps2dev/ps2toolchain-ee` scripts under MSYS2 MINGW32/UCRT64 (hours).

## PCSX2 v2.8.2 (reference oracle)

- **Purpose here:** Phase 0 reference run; Phase 2 live inspection (debugger,
  memory, GS dumps); Phase 4 differential tracing against our runtime.
- **Upstream:** https://github.com/PCSX2/pcsx2 release `v2.8.2` (2026-09-04),
  asset `pcsx2-v2.8.2-windows-x64-Qt.7z` (portable archive, not the installer),
  SHA-256 `7dfc829ca1994cc1045ac49f05e39b6cf968b72e6a374c40e05c2a2b4ac200b4`
  (publisher digest). Extracted to `tools/third_party/pcsx2/` (`pcsx2-qt.exe`).
- **License:** GPL-3.0 (`docs/GPL.html`, `docs/ThirdPartyLicenses.html`).
- **BIOS:** PCSX2 **requires a PS2 BIOS image dumped from the user's own
  console**. It is not included, not downloaded and must never be fetched by
  any script. Place the dump in `tools/third_party/pcsx2/bios/` (created
  empty). The script also creates `portable.txt`, which PCSX2 reads as
  "portable mode" so `inis/`, `bios/`, `memcards/`, `dumps/`, `logs/` stay
  under `tools/third_party/pcsx2/` instead of `%USERPROFILE%\Documents\PCSX2`.
- **Debugger / logging (source-derived from v2.8.2, not yet exercised):**
  - `Tools > Show Advanced Settings`, then `Debug > Open Debugger` (EE/IOP
    disassembly, breakpoints incl. memory breakpoints, register/memory views,
    thread list, function list, save/load symbol maps, "Dump" functions).
  - `Debug` menu: `Enable EE Console Logging`, `Enable IOP Console Logging`,
    `Enable CDVD Read Logging`, `Enable File Logging`, `Enable Verbose Logging`,
    `Save Single Frame GS Dump` (and multi-frame dumps from the debugger) —
    GS dumps are complete GIF-packet captures of what reached the GS, i.e. our
    Phase 2 "which GS primitives/registers does the game use" dataset.
    `Save CDVD Block Dump` logs sector reads (useful to map logical file ->
    CVM sector in Phase 2).
  - **Trace logging** (per-instruction/per-event text trace) is driven from
    `inis/PCSX2.ini` section `[EmuCore/TraceLog]` with keys
    `Enabled`, `EE.bios`, `EE.memory`, `EE.giftag`, `EE.vifcode`, `EE.mskpath3`,
    `EE.r5900`, `EE.cop0`, `EE.cop1`, `EE.cop2`, `EE.cache`, `EE.knownhw`,
    `EE.unknownhw`, `EE.dmahw`, `EE.ipu`, `EE.dmac`, `EE.counters`, `EE.spr`,
    `EE.vif`, `EE.gif`, `IOP.*`, `MISC.sif`. These require a build with trace
    logging compiled in (release builds may compile them out) — verify on
    first use. For register-level tracing, plan on the EE **interpreter**
    (`[EmuCore/CPU/Recompiler] EnableEE=false`) plus `EE.r5900`, or on the
    PINE IPC socket / a custom pcsx2 build (cf. TGE's `pcsx2-hook`,
    chaoticgd's `vutrace` for VU1 state dumps).
- **Invoke:** `tools\third_party\pcsx2\pcsx2-qt.exe [-portable] [-batch] <path\to\persona3fes.iso>`
  (`-portable` forces portable mode; `-batch` exits with the game).

## vgmstream r2117 (audio inspection)

- **Purpose here:** identify and decode **ADX/AHX** streams (CRI) from
  `BGM.CVM`/`DATA.CVM` for the Phase 1 manifest (`vgmstream-cli -m` prints
  codec, sample rate, channels, loop points, encryption-key hits). AFS
  containers: vgmstream has no dedicated `afs` meta (checked `src/meta/` at
  r2117) — plan to split AFS ourselves (trivial TOC: `"AFS\0"`, count, offset/size
  pairs) and feed the ADX members to vgmstream.
- **Upstream:** https://github.com/vgmstream/vgmstream release `r2117`
  (2026-05-19), asset `vgmstream-win64.zip`, SHA-256
  `6c4a8a3813864fefed081bbd337dbc0ad93bf88e0b92f5db98d7ab258b22dc6c`
  (publisher digest). Extracted to `tools/bin/vgmstream/`.
- **License:** ISC-style (`COPYING`), bundled decoders have their own
  (ffmpeg LGPL, libvorbis BSD, mpg123 LGPL…).
- **Observed:** `vgmstream-cli.exe -V` prints `r2117` and lists `adx`, `ahx`,
  `ads`, `afs2`, `aix` among supported extensions.
- **Invoke:** `tools\bin\vgmstream\vgmstream-cli.exe -m <file.adx>` (metadata)
  · `-o out.wav <file.adx>` (decode).
- **Not acquired:** VGMToolbox (SourceForge, .NET Framework GUI, unmaintained) —
  vgmstream + our own AFS splitter cover the need.

## ghidra-emotionengine-reloaded v2.1.38 (secondary analysis surface)

- **Purpose here:** adds a proper **R5900 + VU0 macro + VU1 micro** SLEIGH
  language to the Ghidra 12.1.4 already installed, giving a second
  disassembler/decompiler opinion where IDA's `hexmips` has no MMI/COP2
  awareness (ADR-0004). Ghidra also supports FunctionID/BSim, which could
  substitute for missing FLIRT sigs if we ever get SDK libraries.
- **Upstream:** https://github.com/chaoticgd/ghidra-emotionengine-reloaded
  release `v2.1.38` (2026-10-04), asset
  `ghidra_12.1.4_PUBLIC_20261004_ghidra-emotionengine-reloaded.zip`, SHA-256
  `e389ff3e921d9f7d4db2ece9906f808545ce4ff519d9e25a019b72ea509f240b`
  (publisher digest). Extracted to `tools/third_party/ghidra-emotionengine-reloaded/`
  (`extension.properties` says version `12.1.4`; original author beardypig).
- **License:** Apache-2.0.
- **Install (not yet done; touches Ghidra's user dir, lead's call):** Ghidra ->
  `File > Install Extensions… > +` -> pick the zip in `tools/downloads/`,
  restart Ghidra; import `SLUS_216.21` as language `r5900:LE:32:default`.
  Alternatively unzip into `<Ghidra>/Extensions/Ghidra/`.

---

## Host toolchain (already present; recorded, not installed by us)

| Component | Version / location | Notes |
|---|---|---|
| MSVC | 14.44.35207, VS 2022 Build Tools 17.14, `C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools` | primary compiler for `runtime/`, `recomp/` |
| clang-cl | LLVM 22.1, `C:\Program Files\LLVM\bin` | used for `cvm_tool`; also `llvm-readobj`, `llvm-objdump` |
| CMake | 4.3.1 | VS 17 2022 generator works |
| Ninja | `C:\ninja` | |
| Windows SDK | 10.0.26100 | d3d11, xaudio2 present |
| .NET SDK | 9.0.304; runtimes 8.0.19 / 9.0.8 / 10.0.9 (+ WindowsDesktop) | net8.0 tools run without roll-forward |
| .NET Framework ref assemblies | v4.0 … v4.7.2, **v4.8** (no 4.7) | why AFSL needed the 4.8 override |
| Rust | 1.94.1, `~/.cargo/bin` | |
| 7-Zip | 26, `C:\Program Files\7-Zip\7z.exe` (not on PATH) | used for .7z and .zst |
| bsdtar | `C:\Windows\System32\tar.exe` | used for the ps2dev tarball; cannot create symlinks |
| MSYS2 | `C:\msys64` — ucrt64 gcc present; `mingw32/`, `mingw64/` dirs exist but are empty; no `make` | not used |
| Python | 3.14, `C:\Python314` | |
| Git | 2.53.0; `gh` CLI authenticated | pins/digests gathered via `gh api` |
| IDA Pro | 9.3, `C:\Program Files\IDA Professional 9.3`, `procs/mips.dll` (r5900l/r5900b); ships only PS1 FLIRT sigs | primary RE surface |
| Ghidra | 12.1.4, `C:\Users\Ash\Downloads\ghidra_12.1.4_PUBLIC` | + EE extension above |
| Java | `C:\Program Files\Java\jdk-25.0.4` | for Ghidra |

## Not available

- **PS2 SDK (`libsce*`) FLIRT signatures for IDA.** _**Superseded 2026-10-18:** the pack was recovered from Wayback captures and installed under ADR-0007 — see the section "PS2 SDK FLIRT signatures (user-authorised, unlicensed, private use only)" below. The text that follows records the search as it stood before that._ No GitHub repository
  publishes them (`gh search` for `r5900`/`libgraph`/`ps2sdk` `.sig`/`.pat`,
  and the community FLIRT collections Maktm/FLIRTDB, push0ebp/sig-database,
  PlatyPew/ida-flirtdb contain none). The only known set is a 2018
  ASSEMBLERgames thread (“PS2 Signature Files for IDA Pro”, user Amorri40:
  official SDK 1.0.0/2.0.0/2.4.2/3.0.0/3.0.2/3.0.3, libsn, CodeWarrior, DNAS),
  hosted as forum attachments on the archive site, **no license stated**, and
  derived from Sony's proprietary libraries. Not downloaded. Lead decision
  needed: (a) obtain them manually for private use (`sig/mips/` in IDA 9.3,
  `File > Load file > FLIRT signature file`), (b) rely on manual
  pattern-matching of `sce*` idioms + the ps2sdk headers, or (c) if an SDK
  library set is lawfully at hand, generate our own with IDA's `makesig`/FLAIR
  into `tools/third_party/ida-sigs/` (directory not created yet).
  `ifarbod/renderware3-flirt` exists but is x86/D3D9-only — irrelevant to the
  MIPS RenderWare the game links.
- **Standalone GIF/VIF packet decoder.** Nothing credible and maintained
  exists as a library. Plan: PCSX2 GS dumps as ground truth, `ps2sdk`
  `gif_tags.h`/`vif_codes.h` as the spec, and a small decoder in
  `tools/ours/` (Phase 2).
- **Native Windows ps2toolchain built from source** — not attempted; the
  prebuilt v2.0.0 tarball covers the need.
- **TGE's `AtlusLibSharp`** — repository no longer exists (404).
- **Amicitia binaries** — not built (see above).

## Build and smoke-test log (observed 2026-10-18)

| Step | Command (abridged) | Result |
|---|---|---|
| cvm_tool | `clang-cl /O2 … /link /OUT:tools\bin\cvm_tool.exe` | OK, prints usage |
| cvm_tool on game data | `cvm_tool info extracted\disc\{DATA,BTL,BGM}.CVM` (read-only) | header + directory parsed with no password; exit −1 after listing |
| AtlusScriptCompiler | `dotnet build …AtlusScriptCompiler.csproj -c Release` | OK (54 warnings) |
| PersonaEditorLib | `dotnet build …PersonaEditorLib.csproj -c Release` | OK (7 warnings) |
| PAKPack | `dotnet build …PAKPack.csproj -c Release -p:TargetFrameworkVersion=v4.8` | OK (MoreLinq unresolved warning) |
| AmicitiaLibrary | `dotnet build …AmicitiaLibrary.csproj` | FAIL MSB3644 / NETSDK1045 |
| ps2dev gcc | `mips64r5900el-ps2-elf-gcc --version` | `(GCC) 15.2.0` after DLL fix-up |
| ps2dev compile/link | `-D_EE -G0 -I… -c t.c`; link with `-T linkfile … -lkernel` | OK, R5900 ELF produced (details below) |
| ps2dev gdb | `mips64r5900el-ps2-elf-gdb --version` | FAIL exit 127 (not needed) |
| vgmstream | `vgmstream-cli -V` | `r2117` |
| PCSX2 | extracted, `portable.txt` + `bios/` created | **not launched** (no BIOS; lead to supply) |

EE smoke-test note (observed, scratchpad only, nothing from the disc involved):

```
mips64r5900el-ps2-elf-gcc -D_EE -O2 -G0 -I<ps2dev>\ps2sdk\ee\include -I<ps2dev>\ps2sdk\common\include -c t.c -o t.o
  -> exit 0; objdump -d shows R5900 code (li/lui/dsll32/addiu/sd/jal), i.e. -march=r5900 -mabi=n32 defaults applied
mips64r5900el-ps2-elf-gcc -D_EE -O2 -G0 -I… -L<ps2dev>\ps2sdk\ee\lib -T <ps2dev>\ps2sdk\ee\startup\linkfile t.c -o t.elf -lkernel
  -> exit 0; readelf -h: ELF32, Machine MIPS R3000 (generic), Flags 0x20920025 "noreorder, cpic, abi2, 5900, mips3",
     entry 0x100b20, 1.3 MB (newlib + libkernel statically linked)
```
`t.c` includes `<stdio.h>`, `<kernel.h>`, `<gif_tags.h>` and calls `GIF_SET_TAG`,
`printf`, `SleepThread`. Modern ps2sdk no longer ships `ps2sdk/ee/startup/crt0.o`;
gcc links `ee/mips64r5900el-ps2-elf/lib/crt0.o` by default (ps2sdk's own
`Rules.make` uses `-nostartfiles` + its build-tree `crt0.o`; `-mno-crt0` to opt out).
The ELF was **not** run (no PCSX2 BIOS yet). `mips64r5900el-ps2-elf-gdb.exe`
still exits 127 after the DLL fix-up (some further dependency; not investigated,
gdb is not needed for this project).

The second, idempotent `fetch_tools.ps1` run (2026-10-18) reported every
download `cached`, every clone at its pinned commit, re-extracted the small
archives, re-installed the 17 runtime DLLs, rebuilt `cvm_tool.exe`, and exited 0.

## PS2 SDK FLIRT signatures (user-authorised, unlicensed, private use only)

_Supersedes the first bullet of "Not available" above (left in place for
history). Authority: `docs/DECISIONS.md` ADR-0007 (user override, 2026-10-18).
Reproduce with `tools/fetch_tools.ps1 -IncludeUnlicensedSigs` (opt-in switch;
a default run never touches this step). Nothing from the pack is tracked by git._

- **What it is:** community-made IDA FLIRT `.sig` files for Sony's official
  PS2 SDK libraries (`libsce*`: libkernl, libgraph, libdma, libpkt, libpad,
  libmc, libcdvd, libsdr, libspu2, libeenet, libc/libm, ...), plus SN Systems
  `libsn` (SN ProDG runtime: libc/libm/libstl/libsn/libsniop) and Metrowerks
  CodeWarrior for PS2 runtimes (`ANSICPP_PS2.LIB`, `MSLGCC_PS2.LIB`). Built
  with FLAIR `sigmake` by **Amorri40** (Alasdair Morrison, RetroReversing)
  "thanks to pool7" from the SDK `.a` archives.
- **Provenance chain (observed 2026-10-18):**
  1. Original: ASSEMBLERgames.com thread "[Reverse Engineering] PS2 Signature
     Files for IDA Pro", first post by Amorri40 on **2018-02-11**, attachment
     IDs 30719-30728; second attachment set (2018-09-28, IDs 33679-33687,
     "converted the libraries to .yara source files") carries byte-identical
     `.sig` files plus 92 `.yara` rules. ASSEMBLERgames.com is offline; no
     Wayback capture of the thread *page* exists under
     `assemblergames.com/threads/*` (CDX queries returned nothing).
  2. Thread text: read-only archive copy at
     <https://assemblergames.org/viewtopic.php?t=39373> (phpBB re-post stamped
     2019-06-27, "posted by Amorri40 on Feb 11, 2018"). Its attachment links
     (`/attachments/<id>/<name>.zip`) all return **HTTP 404** (10 KB HTML
     stubs), so the mirror provides text only.
  3. **Files used:** Wayback Machine raw captures (`id_` form) of the original
     `assemblergames.com/attachments/<slug>.<id>/` URLs; capture timestamps
     2018-04-01 07:58 UTC for the SDK zips (`20180401075841`...`075849`) and
     2019-11-09 10:03 UTC for libsn/CodeWarrior (`20191109100353`/`100357`).
     Exact URL + SHA-256 per archive are pinned in `fetch_tools.ps1` step 11
     and in the installed `MANIFEST.txt`. Archive digests were recorded by us
     (no publisher digest exists). The 2018-09 duplicates (`*_2018-09/`) were
     fetched for comparison only (`cmp`: identical `.sig`s) and are not
     installed; their `.zip.v2` archives stay in `tools/downloads/ida-sigs-amorri40/wayback/`.
- **License:** **none.** Neither the thread nor the archives state a license,
  so the author's work is all-rights-reserved by default, and the patterns
  themselves are derived from Sony's proprietary libraries (and SN/Metrowerks
  runtimes). Private use on this machine only; never commit, package or copy
  into `docs/`, `symbols/` or the port. Names *we* assign in IDA after
  verifying behaviour remain our own facts about the binary (ADR-0007).
- **Where:** downloads `tools/downloads/ida-sigs-amorri40/wayback/` (plus
  `../SHA256SUMS.txt`); extracted, one fresh directory per archive, in
  `tools/third_party/ida-sigs/<set>/generated/<Name>/{<Name>.sig,<Name>.exc,patternfiles/*.pat}`;
  installed `.sig`s + `MANIFEST.txt` in
  **`C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\`** (created).
  Program Files was not touched. `IDAUSR` is **not set** at User, Machine or
  Process scope (observed), so IDA 9.3 uses its documented default
  `%APPDATA%/Hex-Rays/IDA Pro` and searches `%IDAUSR%\sig\<arch-name>`
  (Hex-Rays docs, "Environment variables"); the sigs should therefore appear
  in the Signatures window / `File > Load file > FLIRT signature file` of an
  `r5900l` database without further configuration. **Not yet exercised in
  IDA** (another agent holds the session).
- **Header verification (Python, scratchpad parser; all 11 extracted `.sig`
  files; magic `IDASGN`, FLIRT format version 7, `features=0` i.e.
  uncompressed, `old_n_functions=0`, `n_functions` from the v6+ field):**

  | file (= library name in header) | size | n_functions | processor id | installed |
  |---|---|---|---|---|
  | `PS2SDK_3.0.3.sig` | 430,977 | 3,937 | 0x00 | yes (primary) |
  | `PS2SDK_3.0.2.sig` | 89,968 | 513 | 0x00 | yes |
  | `PS2SDK_3.0.0.sig` | 247,261 | 1,774 | 0x00 | yes |
  | `PS2SDK_2.4.2.sig` | 42,544 | 276 | 0x00 | yes |
  | `PS2SDK_2.0.0.sig` | 149,321 | 433 | 0x00 | **no** - see below |
  | `PS2SDK_1.0.0.sig` | 12,944 | 134 | 0x00 | yes |
  | `libsn.sig` | 194,598 | 1,706 | 0x00 | yes |
  | `MetrowerksCodewarrior.sig` | 22,683 | 274 | 0x00 | yes |

  SHA-256 of each archive and `.sig`: `MANIFEST.txt` in the install dir and
  `tools/fetch_tools.ps1` step 11. **Processor-id deviation:** every file
  reports processor id **0x00**, not MIPS (0x0C). The same is true of
  Hex-Rays' own bundled `sig/mips/psx.sig`, `sig/mips/pe.sig`,
  `sig/arm/elf.sig` and `sig/arm/android_arm.sig` (observed, read-only), so
  the byte is not a reliable architecture marker and the literal
  "reject if not MIPS" rule was replaced by a **content check**: the leading
  32 pattern bytes of every `.pat` line were decoded as little-endian MIPS
  words and classified by major opcode (lw/sw/sd/sq/addiu/lui/jal/jr/lqc2/
  cop2...). Result: the Sony/SN/Metrowerks libraries decode as EE code at
  95-100 % (top opcodes `sd`, `sq`, `addiu`, `lw`; `libvu0` is `lqc2`+COP2),
  **but the author also fed the SDK's x86 host-toolchain libraries into
  sigmake**: `libbfd`, `libopcodes`, `libiberty`, `libtcl8.0`, `libtk8.0`,
  `libtix`, `libitcl`, `libitk`, `libexpect`, `libreadline`, `libhistory`,
  `libfl`, `libmmalloc` start with `55 89 E5` (`push ebp; mov ebp,esp`).
  Share of x86 patterns: 3.0.3 = 265/4,789 (10 libs), 3.0.0 = 267/1,888
  (11 libs), 3.0.2 / 2.4.2 / 1.0.0 / libsn / CodeWarrior = 0, **2.0.0 =
  349/470 (74 %; its only EE content is `libgcc`+`libstdc++`, no Sony
  library)** - hence `PS2SDK_2.0.0.sig` is verified and kept in
  `tools/third_party/ida-sigs/ps2sdk_2-0-0/` but **not installed**. The x86
  patterns in 3.0.3/3.0.0 are inert in practice (FLIRT requires the 32-byte
  prefix, the CRC16 of the tail and the tail bytes to match), but a false
  positive would be named like `bfd_*`/`Tcl_*`/`Tk_*` and should be treated
  as such. A clean EE-only regeneration from the shipped `.pat` files needs
  FLAIR `sigmake`, which is **not installed** here (IDA 9.3 ships only the
  in-database `makesig` plugin; FLAIR is a separate Hex-Rays portal download).
- **Collisions:** the author's script resolved `.exc` collisions by taking the
  first candidate and prefixing it `collision_`; when IDA names a function
  `collision_*`, consult the matching `.exc` under `tools/third_party/ida-sigs/`
  for the alternatives (e.g. `sceVif0PkAddCode` / `sceVif0PkAddData` /
  `sceVif1PkAddCode` share one pattern).
- **Applicability to `SLUS_216.21` (SDK 3.1.x) - inference, not yet measured:**
  3.0.3 (2004) is the closest set; 3.1.0 (2005) was a minor bump, so expect
  **partial** matching: functions untouched between 3.0.3 and 3.1.x match
  exactly, recompiled-but-unchanged functions usually still match (FLIRT
  masks relocations), and anything refactored or built with changed compiler
  flags will not. Most likely stable: libkernl (syscall stubs are fixed
  trampolines), libc/libm (newlib-derived, rarely touched), libgraph, libdma,
  libpkt, libvu0, libpad (not libpad2's newer paths), libmc, libsdr, libcdvd,
  libsif*/libmrpc, libmtap, libspu2/libsnd2. Least likely: libeenet /
  network, libmc2, libhttp(s), anything rewritten for the 3.x libsk/USB
  stack. Apply 3.0.3 first, then 3.0.2 -> 3.0.0 -> 2.4.2 -> 1.0.0 for
  stragglers, then `libsn` / `MetrowerksCodewarrior` only if the
  compiler-fingerprint pass (`docs/ANALYSIS/`) points at SN ProDG or
  CodeWarrior rather than Sony's ee-gcc; record per-sig match counts in
  `docs/ANALYSIS/05_flirt.md` as ADR-0007 requires.
- **Other PS2 FLIRT material found (not acquired, out of ADR-0007 scope):**
  same thread, `gcc2-9.zip` (Wayback `20180401075843id_/.../gcc2-9-zip.30727/`,
  1.1 MB) - sigs for the ee-gcc 2.9 runtime (libgcc/libstdc++), potentially
  useful if the game's CRT is gcc 2.9x; `dnassdk30usa.zip`
  (`.../dnassdk30usa-zip.30728/`, 670 KB) - Sony DNAS 3.0 network-auth
  library, irrelevant to this game; the 2018-09 `.yara` conversions (RetDec
  format). No other PS2 FLIRT sets exist on GitHub (`gh search code/repos`
  for `PS2SDK_3.0.3.sig`, `libsn.sig`, `ps2 flirt`, `ps2 ida signatures`,
  `r5900 flirt`: zero hits); Maktm/FLIRTDB, Shiselster/FLIRTDB,
  push0ebp/sig-database, PlatyPew/ida-flirtdb and Hex-Rays' FLIRT bundle
  contain nothing PS2-specific; `oct0xor/ida-emotionengine` is a COP2
  disassembly plugin, not signatures. Open-source ps2sdk/gsKit `.a` files
  could be turned into sigs with FLAIR (AFL-2.0, clean), but the game links
  Sony's libraries, not ps2sdk, so that would only help for newlib `libc`.
