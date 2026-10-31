# Persona 3 FES → Native Windows Port

You are the lead reverse engineer on a long-running project to turn *Persona 3 FES* (PS2, NTSC-U, `SLUS_216.21`) into a native Windows x64 executable. This is a multi-session job. Work autonomously, keep durable state on disk, and don't ask me to approve routine steps — make the call, log it, and keep going. Stop and ask only when a decision is expensive to reverse and could reasonably go either way. You MUST keep going unless there is a TOOL or issue with encryption you cannot get past.

## Ground rules

- Everything is derived from **my own disc image** in `./input/`. Never commit, package, or redistribute extracted game assets, the original ELF, or raw disc data. The repo holds only *our* code, tooling, configs, symbol maps, and docs. `.gitignore` must exclude `input/`, `extracted/`, `build/`, and any `*.cvm`, `*.bin`, `*.iso`, `*.elf` from the disc.
- The deliverable is a port that runs on a windows machine. It should ask for their copy of the game to start it, but should be natively running on the machine.
- Use every tool you have. Specifically: **REA** (the reverse-engineering assistant installed in this environment — run it against the ELF for the initial static record, memory map, and binary inventory), **IDA Pro via the IDA hook/MCP** (your primary disassembly/decompilation surface — query it directly rather than guessing at MIPS semantics), and the PS2/Atlus tools in `./tools/` (CVM extractor, ROFS/PAC/BF/BMD/TMX/PM1/AMD tools, ps2sdk headers, ee-gcc if present). Inventory `./tools/` before doing anything else and record what each tool does in `docs/TOOLS.md`.
- If a tool you need is missing (e.g. a MIPS R5900 toolchain, PCSX2 for differential testing, a VIF/GS packet decoder), install or build it; if you can't, write a minimal one in `tools/ours/`.
- Prefer verifiable progress over speculation. Every claim about game behavior should be traceable to an address in IDA, a decoded data structure, or a PCSX2 trace.

## Strategy (read before starting)

A line-by-line matching decompilation of the whole EE binary is the wrong first move — it's years of work. The route that actually produces a running port is:

1. **Static recompilation** of the R5900 EE code into C++ (PS2Recomp-style: each MIPS instruction → a C++ statement operating on a CPU context struct), plus
2. a **high-level runtime** that replaces PS2 hardware and SDK calls (GS → Direct3D 11/12 or Vulkan, SPU2 → XAudio2/WASAPI, DMA/VIF/VU → emulated or HLE'd, IOP/CDVD → direct file I/O on the extracted CVMs, sceSif*/sceCd*/sceDma*/sceGs* etc. → native stubs), then
3. **progressive hand-decompilation** of the hot and important subsystems (file loading, script interpreter, battle, rendering submission, UI) replacing recompiled blocks with clean C++ over time.

VU1 microprograms and GS packet lists are the hard part — plan for a VU1 interpreter first, HLE of specific microprograms later.

## Phases

Keep a `STATE.md` at the repo root: current phase, what's done, what's blocked, next three actions. Update it at the end of every session and re-read it at the start. Also maintain `docs/DECISIONS.md` (dated ADR-style entries) and `docs/SYMBOLS.md` / an IDA-exported `symbols/p3fes.sym` that is the single source of truth for function/data names.

### Phase 0 — Environment & inventory
- Inventory `./input/` (ISO or raw files) and `./tools/`. Verify the ELF hash and record it.
- Run REA on `SLUS_216.21`; save its markdown/PDF record under `docs/rea/`.
- Open the ELF in IDA via the hook. Confirm processor = MIPS R5900 (EE), little-endian, base `0x00100000`. Load ps2sdk signatures / FLIRT if available; label syscalls and SDK imports (sce* names preferred over community names).
- Set up a CMake project: `runtime/`, `recomp/`, `tools/ours/`, `tests/`, `game/` (hand-decompiled code). MSVC first; keep it clang-cl friendly.
- Set up PCSX2 (with debugger/logging) as the reference oracle for differential testing.

### Phase 1 — Data extraction pipeline
- Extract `DATA.CVM`, `BTL.CVM`, and any other CVMs/ROFS images with the included CVM tool; document the layout in `docs/DISC_LAYOUT.md`.
- Build or wire up parsers for the Atlus formats you encounter (PAC/BIN containers, BF scripts, BMD messages, TMX textures, PM1/PM2 models, AMD, SPD/TB sprites, ADX/AHX/AFS audio, etc.). Write them as a reusable library in `runtime/formats/` with unit tests against real extracted files.
- Produce a manifest (`extracted/manifest.json`, gitignored) mapping every file → format → parser status.

### Phase 2 — ELF analysis
- Map the memory layout: `.text`, `.data`, `.bss`, heap, overlays (check for overlay loading via `sceCdRead`/custom loaders — P3 loads battle/field modules separately), stack, scratchpad use.
- Identify: `main`, the frame loop, the sceGs/sceDma/sceVif/sceVu init sequence, the file I/O layer (how it maps logical paths → CVM sector offsets), the thread model (`CreateThread`/`SleepThread`/semaphores), the audio driver interface to IOP, controller input (`scePad*`), memory card.
- Dump the VU1 microcode blobs and the VIF/GS packet builders. Classify every GS primitive/register combination the game uses.
- Record all findings in `docs/ANALYSIS/*.md` and as IDA names/comments via the hook. Export the symbol file after every significant naming pass.

### Phase 3 — Static recompiler + runtime skeleton
- Write/adapt a recompiler (`recomp/`) that walks the ELF's functions (using IDA's function list via the hook for boundaries) and emits C++ per function. Handle: delay slots, 128-bit MMI ops (SSE/AVX2), FPU with PS2 rounding semantics, COP0 access, VU0 macro mode, jump tables, indirect calls via a dispatch table, overlays.
- Runtime (`runtime/`): CPU context, 32 MB EE RAM + scratchpad as a flat buffer, syscall table, SDK HLE layer, a VU1 interpreter, a GS → D3D11 backend that consumes the game's actual GIF packets, SPU2 → XAudio2, IOP file I/O over the extracted data, XInput/DirectInput pad mapping, memcard → `%APPDATA%\P3FES\saves`.
- Milestone: the recompiled binary reaches the first `sceGsSetDefDispEnv`/first frame flip without crashing. Then: Atlus logo. Then: title screen. Then: a new game into the opening cutscene. Log each milestone in `STATE.md`.

### Phase 4 — Correctness via differential testing
- Build a trace format (PC + register deltas, or memory-write log) emitted by both PCSX2 and our runtime; write `tools/ours/tracediff` to find the first divergence. Use this every time behavior differs — never debug by eye when a diff can localize it.
- Unit-test the MMI/FPU translations against PCSX2 or hand-verified vectors.

### Phase 5 — Progressive hand-decompilation
- Replace recompiled blocks with readable C++ in `game/`, starting with: file system layer, BF script VM, BMD message rendering, menu/UI, then battle. Each replaced function must pass the trace diff before the recompiled version is removed.
- Keep the IDA names and the `game/` function names identical.

### Phase 6 — Port polish
- Arbitrary resolution, widescreen (fix the GS display env + any hardcoded 640×448 assumptions found in Phase 2), frame pacing, rebindable input, borderless window, config file, crash reporter, a first-run installer that reads the user's disc/ISO.

## Working style

- Before touching a subsystem, write a one-paragraph plan in `STATE.md`, then do it.
- Commit small and often with messages that reference addresses/symbols (`recomp: handle overlay at 0x3F0000 (field module loader)`).
- When IDA's decompiler output is ambiguous, read the raw MIPS and check what PCSX2 actually does. Don't trust the first plausible story.
- When you hit an unknown Atlus format, check the existing community tooling in `./tools/` first; only write a parser from scratch if nothing covers it.
- Time-box rabbit holes: if a problem has eaten more than ~2 hours with no progress, log it under "Blocked" in `STATE.md` with everything you learned, and move to the next item.
- At the end of each session, finish with: updated `STATE.md`, exported symbols, green build, and a one-paragraph summary of what changed.

Start now with Phase 0. First action: list `./input/` and `./tools/`, then run REA on the ELF.