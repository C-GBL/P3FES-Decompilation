<p align="center">
  <img src="https://p3fmmo.com/p3fesdecompheader.png" alt="Persona 3 FES Decompilation" height="480">
</p>

# Persona 3 FES Decompilation

<p align="center">
  <a href="https://github.com/C-GBL/P3FES-Decompilation/releases/latest"><img src="https://img.shields.io/github/v/release/C-GBL/P3FES-Decompilation?include_prereleases&label=release" alt="Latest release"></a>
  <a href="https://github.com/C-GBL/P3FES-Decompilation/releases"><img src="https://img.shields.io/github/downloads/C-GBL/P3FES-Decompilation/total" alt="Downloads"></a>
  <a href="https://github.com/C-GBL/P3FES-Decompilation/commits/main"><img src="https://img.shields.io/github/last-commit/C-GBL/P3FES-Decompilation/main" alt="Last commit"></a>
  <a href="https://github.com/C-GBL/P3FES-Decompilation/stargazers"><img src="https://img.shields.io/github/stars/C-GBL/P3FES-Decompilation?style=flat" alt="Stars"></a>
  <a href="https://github.com/C-GBL/P3FES-Decompilation/issues"><img src="https://img.shields.io/github/issues/C-GBL/P3FES-Decompilation" alt="Open issues"></a>
  <br>
  <img src="https://img.shields.io/badge/platform-Windows%20x64-0078D4" alt="Platform: Windows x64">
  <img src="https://img.shields.io/badge/C%2B%2B-20-00599C" alt="C++20">
  <img src="https://img.shields.io/badge/renderer-Direct3D%2011-76B900" alt="Direct3D 11">
  <img src="https://img.shields.io/badge/functions%20recompiled-14%2C500%20%2F%2014%2C500-brightgreen" alt="14,500 of 14,500 functions recompiled">
  <img src="https://img.shields.io/badge/target-SLUS__216.21%20(USA)-8A2BE2" alt="Target: SLUS_216.21 USA">
</p>

A native Windows x64 port of Persona 3 FES (`SLUS_216.21`, the USA release), built by statically recompiling the PS2 executable into C++ and running it on a runtime written for this game. The port renders through Direct3D 11, compiles the game's VU1 microprograms ahead of time, and plays from start to finish.

This is not a finished product. Read [What is native and what is still emulated](#what-is-native-and-what-is-still-emulated) before you expect a clean rewrite. It also needs your own legally obtained copy of the game. See [Releases](#releases).

## Releases

Prebuilt executables are on the [Releases page](https://github.com/C-GBL/P3FES-Decompilation/releases).

This version does not contain a full handwritten source code, and is currently emulating certain PS2 core features such as IO, Sound, ADX Playback and more. It does however contain a D3D11 backend that runs natively, and it also features ahead-of-time VU1 compilation. The game is completely playable, but it is NOT the finished product.

This executable requires a LEGALLY obtained copy of the game (it needs to be the USA copy of P3FES) and will not launch without the .iso or the extracted game files. The recompiler checks the ELF's SHA-256 against the known USA digest, so other regions and modified images are refused.

Set up the directory like this:

```
extracted
  disc
    (extracted iso files here)
input
  persona3fes.iso
p3fes.exe
```

Launch it with these flags:

```
p3fes.exe --iso input\persona3fes.iso --renderer native --fps 120 --quiet --scale smooth
```

Verify the hash of the file before you run it. Do NOT download this executable from anywhere else, as it will most likely be malware.

```
7dcd3e485e89b22d91ceefcd2bec86159bba4f71dc2484690241d8a3d4183a93
```

Saves go to `%APPDATA%\P3FES\saves` as a standard PS2 memory card image (`Mcd001.ps2`). The keyboard and XInput map is `config/input.ini`. F12 takes a screenshot, F11 or Alt+Enter toggles full screen, F3 shows the frame-time overlay.

### Changelog

| Version | Notes |
|---|---|
| v0.1.0 | Initial commit, with all recompiled functions (14,500) |

## How the port works

The PS2 build of Persona 3 FES is a 9 MB MIPS R5900 ELF. Rather than interpret it, `p3fes_recomp` translates every one of its 14,500 functions into a C++ function, one translation unit per group, with a dispatch table for indirect calls, thread entries and interrupt handlers. The output compiles at `/W4` under both MSVC and clang-cl. Generated code calls a small adapter API (`namespace p3fes::rt`, 203 functions) for memory access, FPU and MMI semantics, VU0 macro instructions and syscalls; the runtime implements that adapter and everything the game expects from the machine around it.

Every one of those functions has since been moved into `game/` under its IDA name as register-faithful C++ (this is the `journey-100` state), still taking `EEContext&` and still charging the same virtual cycles, so the whole program stays byte-identical to the pure recompiled build. Several bands (boot, file system, BF script VM, BMD messages, menu/UI, battle) have been reworked further into structured code with named fields and no gotos. The lift into natural C++ comes after the PS2 platform is removed from under it (see below).

The recompiler consumes IDA disassembly and raw instruction words, never Hex-Rays pseudocode, and decodes with its own R5900 table scoped to the 198 mnemonics the game uses. Anything outside that census decodes to `Invalid` and stops the emitter, so an unexpected instruction can't silently become wrong code. rabbitizer, binutils and `ps2-web-recomp` serve as decode oracles in the test suite.

Execution follows one host thread with a fiber per guest thread. Time is virtual, computed from cycle counts the emitter writes into each basic block; interrupts and thread switches happen at check points, not at arbitrary host instants. The result is deterministic. The same inputs produce byte-identical guest memory on every run, which is what the whole validation story below depends on.

### The runtime

| Part | Where | What it does |
|---|---|---|
| EE memory and context | `runtime/rt/`, `runtime/src/` | 32 MB main RAM, scratchpad, 128-bit GPRs, FPU, COP0, VU0 registers, MMI |
| Kernel | `runtime/hle/kernel/` | threads on fibers, semaphores, INTC, DMAC, timers, VSync, syscalls |
| CDVD and files | `runtime/hle/` | `sceCdRead` served by sector from the ISO or extracted CVM volumes; ISO9660 reader; a mods overlay (`--mods DIR`) that swaps whole disc files for host files |
| IOP | `runtime/hle/sif/iop/` | SIF RPC, fileio, PADMAN, memory card (MC2), CRI ADX streaming, and the game's own SK/libsd sound modules running on a small R3000 interpreter |
| GS, GIF, VIF1 | `runtime/gs/` | a software rasteriser into 4 MiB of swizzled local memory, all 54 GS registers, PATH1/2/3 arbitration, CRTC composition |
| VU1 | `runtime/vu1/` | a bit-exact interpreter, plus `p3fes_vu1_aotgen`, which compiles all 114 of the game's microprograms to C++ ahead of time |
| D3D11 back end | `runtime/src/gs/`, `runtime/hfr/` | GPU rasterisation through a rasteriser-ordered-view pixel pipeline into the same 4 MiB VRAM image, frame pacing, in-between frame interpolation |
| Native renderer | `runtime/native/` | RenderWare g3 batches drawn from a C++ model of the VU1 programs, skipping the microprogram, the GIF parse and the GS vertex queue |
| IPU | `runtime/ipu/` | MPEG-2 decoding for the Sofdec movies |
| Audio | `runtime/audio/` | 48 SPU2 voices with ADPCM and ADSR, the PSM stream mixer, an ADX decoder, XAudio2 and WAV sinks |

### Graphics

Three rendering paths exist, and they share one VRAM image and one op list.

The software GS is the oracle. Every gate in the project compares against it, and it never changed when the faster paths were added.

The D3D11 back end (`--gs-backend d3d11`) replays the same GS operations on the GPU. In `--gs-exact` mode its frames are byte-identical to the software rasteriser on every recorded route.

The native renderer (`--renderer native`) replaces the VU1 run itself. RenderWare's PS2 driver turns every atomic into VIF packets and kicks a g3 microprogram per vertex cluster; two programs, `g3_skin` and `g3_generic`, are 90% of the VU1 work in battle. In native mode a semantic model of those programs computes the batch's vertices in C++ from VU1 memory and hands triangles straight to the GPU. Everything the EE side does stays as it was: the RW driver, the DMAC, VIF1 timing, the UNPACKs into VU1 memory. Any batch the model doesn't recognise falls back to the exact VU1 run. Measured against the exact output, positions land within 1/16 pixel and colours match exactly.

`--fps 60`, `--fps 120`, `--fps monitor` and `--fps unlimited` show interpolated pictures between the game's 30 fps frames. The render thread keeps each game frame's lists and VRAM state, matches native batches between consecutive frames by a hash of their vertex block, and blends vertices in clip space. Game logic, guest memory and every gate are untouched by this; `--fps 30` is the plain behaviour.

Ahead-of-time VU1 (`--vu1 aot`, built with `-DP3FES_VU1_AOT=ON`) compiles each microprogram's label blocks to C++ with host SSE/AVX float under round-toward-zero and an exact per-lane fallback. On captured battle batches it runs 14 to 24 times faster than the interpreter, and a differential mode (`--vu1 diff`) has compared it over 30 billion instruction pairs with zero mismatches.

### Sound

The game decodes ADX on the EE with its own CRI library, which is recompiled like everything else, and streams PCM to the IOP. The IOP side models `CRI_ADXI.IRX`'s PSM mixer. Sound effects and sequenced music go through the game's real `SK*`/`libsd` IRX modules, interpreted on an R3000 core inside the IOP HLE, driving a host SPU2 voice model. Menu sound effects measure within 0.5 dB of PCSX2.

## What is native and what is still emulated

| Native on the host | Still a model of PS2 hardware |
|---|---|
| Game code: all 14,500 functions as C++ under `game/`, register-faithful (the `EEContext` calling convention), with the boot, file system, script VM, message, menu and battle bands reworked into structured code | CDVD, cdvdfsv and the CVM/ROFS sector reads |
| Window, input (keyboard, XInput), memory card storage | IOP, SIF RPC, PADMAN, MC2, the IRX sound modules on an R3000 interpreter |
| D3D11 rasterisation and presentation, frame pacing, interpolation | GS register model, GIF, VIF1, DMAC, INTC, timers |
| VU1 g3 batches in `--renderer native` | VU1 for everything else (AOT-compiled, still a microprogram) |
| MPEG-2 decode core | IPU command and FIFO timing around it |
| XAudio2 output, ADX decode | SPU2 voice model, the IOP's PSM stream mixer |

The plan for removing the right-hand column is ADR-0017 in `docs/DECISIONS.md` and `docs/MODERNIZE_PLAN.md`: one layer at a time (files, input, sound, movies, graphics, kernel and timing), each behind its own switch, each with a stated check against the faithful path before it becomes the default. Files come first, because everything streams through them and the check is exact. After that pass, the hand-written lift starts on code that calls host services only.

## Validation

The project treats PCSX2 as a state oracle, never as a source. `tracediff` compares a snapshot of guest memory at a given vblank against a capture from a clean PCSX2 2.8.2 run. At every milestone (first flip, the Atlus logo, the title, a dorm save) the code band differs by 0 bytes. 3,443 compiled EE semantics vectors were run in PCSX2 to pin down instruction behaviour; 0 are unexplained.

Six recorded input routes (first flip, dorm, battle, fusion, shop, Tartarus climb) replay deterministically from a fresh memory card. Every merge re-runs them headless and compares `eeMemory.bin`, `gsMemory.bin` and `frame.png` against stored references. Each function moved into `game/` also runs a pair test against its own recompiled body on randomised inputs (same result, same callee-saved registers, same memory, same cycle count) before the recompiled version is retired. The suite is 16 doctest executables, run under both MSVC and clang-cl.

## Building from source

Windows x64 only. MSVC 14.44 (VS 2022 Build Tools 17.14) is the primary compiler; clang-cl must also build. CMake 3.25+, Ninja, Windows SDK 10.0.26100 for the D3D11, XAudio2 and XInput headers. Nothing is downloaded at configure time; doctest is vendored under `tests/vendor/`.

You need your own disc image at `input/persona3fes.iso` and an extracted copy of it at `extracted/disc/` (`python -I tools\ours\cvm\cvm_extract.py` unpacks the three CVM containers, 12,019 files). Generated code is derived from that ELF and is never committed.

```powershell
. .\tools\env.ps1
cmake --preset msvc-x64-release -B build\int -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt
cmake --build build\int --target p3fes_recomp
build\int\bin\p3fes_recomp.exe --elf extracted\disc\SLUS_216.21 --functions symbols\functions.json `
  --chunks symbols\function_chunks.txt --jumptables symbols\jumptables.json --out recomp\generated --replace game\replaced.txt
cmake --build build\int
ctest --test-dir build\int
build\int\bin\p3fes.exe
```

`BUILDING.md` has the full set of presets, the profiling and zone-timing tools, and the headless snapshot options used for gating.

## Repository layout

| Path | Contents |
|---|---|
| `recomp/` | the R5900 to C++ static recompiler, its decoder and emitter, the hand-code generator |
| `runtime/` | the host runtime: EE, kernel, HLE, GS, VU1, D3D11, native renderer, IPU, audio, the `p3fes` executable |
| `game/` | hand-decompiled game code, organised by subsystem (battle, field, script, msg, ui, calendar, ...) |
| `symbols/` | function list, chunk ranges, jump tables, instruction and VU1 microprogram censuses, verified names |
| `tests/` | doctest suites for every runtime component and the game pair tests |
| `tools/ours/` | CVM extractor, tracediff, IDA and Ghidra scripts, PCSX2 oracle setup, perf harness |
| `config/` | input map and the six recorded replay routes |
| `docs/` | ADRs, the runtime contract, format notes, 30+ analysis documents, the integration log |

## AI Disclosure
I've used Claude a lot on this and will keep using it. A project this big on the timeline I wanted wasn't happening otherwise. Everything it writes has to pass the same tests as anything I write by hand. PRs are welcome, AI-assisted ones too.

## Legal

This repository contains no game data, no BIOS, no Sony SDK code and no generated code. The disc image, the ELF, the extracted files and the recompiled C++ all come from your own copy and stay on your machine. Community symbol maps were used as private reading hints; the committed names are only those verified in our own analysis or permissively licensed.

Third-party code used under its license, with the notices in `licenses/` and the `THIRD_PARTY.md` files next to each ported part:

- `ps2-web-recomp` (MIT, Samir Nuri): R5900 decode table layout, SPU2 voice model shape, VU1 reference semantics
- Play! (BSD, Jean-Philip Desjardins): MPEG-2 VLC tables in the IPU

GPL projects (PCSX2 source, PS2Recomp, p3fes-recompiled) were used as behavioural oracles only; their source was never opened for this code base.

Persona 3 FES is the property of ATLUS / SEGA. This project is not affiliated with or endorsed by them.
