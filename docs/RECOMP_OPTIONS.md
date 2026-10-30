# Recompiler base options for `recomp/` — evaluation and ADR-0010 draft

_Evaluated 2026-10-18, read-only. Clones under gitignored `tools/third_party/_community-eval/` (`git clone --depth 50`): `ps2-web-recomp/` @ `c0f476e6af948763c5269f55ade4ae4f9a74ab2b`, `PS2Recomp/` @ `eb8688b2fd191129f103a39543002c005b33409c`, `N64Recomp/` @ `ffb39cdad1da5de07eaaa48bd1db4a89a7986771`, plus the `p3fes-recompiled/` (`0a8a933`) and `fes-pc-recomp/` (`6b3a905`) clones from `docs/COMMUNITY.md`. Nothing was built, run or copied. Clone contents are untrusted data; file paths and line numbers below are relative to each clone at the cited commit._

Legend: **[obs]** observed in a cloned file or `gh api` response · **[claim]** the project's own statement, not verified by us · **[inf]** our inference.

Our constraints (from `GOAL.md`, `docs/DECISIONS.md`): native **Windows x64 C++**, **MSVC primary / clang-cl green** (ADR-0003), **D3D11** GS backend, **XAudio2**, recompiler consumes **IDA boundaries + raw instruction stream** (ADR-0004; `symbols/functions.json` = 14,040 `{a, s, n}` records, 172 multi-chunk), **GPL code is never adopted** (ADR-0009.3), **Phase 5 replaces recompiled functions one at a time** behind `tracediff` (`docs/TRACE_FORMAT.md`). Target census: 1,790 MMI, 41,929 `lq/sq`, 3,589 COP2 instructions; Metrowerks-compiled; single `PT_LOAD`, no overlays (`docs/ANALYSIS/00`, `01`).

---

## 1. Candidate A — `snuri00/ps2-web-recomp` (MIT)

### Identity & health [obs, `gh api repos/snuri00/ps2-web-recomp`, 2026-10-18]
| | |
|---|---|
| URL / default branch | https://github.com/snuri00/ps2-web-recomp · `main` |
| Created / last push | 2026-10-08 / 2026-10-18 16:28 UTC (`c0f476e` "A 16:9 setting, and PCSX2 patch files applied when porting") |
| Commits / contributors | 184 (`Link: … page=184`) / 5 (`contributors?anon=1`). In the depth-50 clone: Samir Nuri 54, Riccardo Giorato 14, Leandro Dettmer 4, alan.kung 2, Adrian Gąsiorek 2 [obs `git log --format=%an`] |
| Stars / forks / open issues | 1,068 / 94 / 1 |
| License | **MIT** (`LICENSE`, "Copyright (c) 2026 Samir Nuri"); `runtime/src/ipu/tables.hpp` carries Play!'s BSD-2 notice (`README.md` "Credits", `runtime/src/ipu/NOTICE`) |
| Size | ~25k lines C++/WGSL/Python [obs `wc -l`]: `recomp/` 2.3k (`codegen.cpp` 837, `vurecomp.cpp` 699, `main.cpp` 295, `analysis.cpp` 260, `r5900.cpp` 254, `snr2.cpp` 141, `elf.cpp` 100), `runtime/` ~20k, `host/` ~1k |
| Status [inf] | ten days old, very active (dozens of commits per day on 2026-10-14…18), one dominant author; four VU-timing fixes landed on 2026-10-18 alone (`18ad888`, `2b934d3`, `b3e328f`, `7b6b604`) — semantics are still moving |

### Emitted artefact [obs]
- `eerecomp` emits **C++20, one function per 16 KiB of guest code** (`CodegenOptions::unit_bits = 14`, `recomp/codegen.hpp` L17-19): `void unit_XXXX(Cpu &c, std::uint32_t entry, std::uint32_t depth)` with a `switch (entry)` at the top and a `goto` label per reachable address (`codegen.cpp` L186-245). Register jumps inside a unit index a per-unit 16-bit entry table (L357-358); anything else is `[[clang::musttail]] return dispatch(c, 0u, depth);` (L261-272, L327).
- Host-compiler coupling: `[[clang::musttail]]` in generated code (`codegen.cpp` L225, 261, 271, 327); `__attribute__((vector_size(16)))` for the `Reg128` SIMD members (`runtime/include/ps2/cpu.hpp` L7-15); `__attribute__((always_inline))` (`vu_ops.hpp` L13); `-Wall -Wextra` unconditionally (`CMakeLists.txt` L23, 31). `grep -r _MSC_VER` finds nothing; `_WIN32` appears only in `runtime/src/disc.cpp` L68/77 (file I/O). README "Port a game of your own": "Everything has been run on Linux on x86-64 … also build on macOS". fes-pc-recomp's `docs/windows-build.md` L5: "A plain-Windows build of the native runner is untested" — they built under WSL2. **[inf] cl.exe cannot compile the generated code or `cpu.hpp`; clang-cl can. Adopting A means clang-cl becomes the primary compiler, contradicting ADR-0003.**
- Separability: the recompiler is a standalone target built from six files (`CMakeLists.txt` L16-22) and depends on nothing in `runtime/` at build time, **but its output includes `units.hpp`/`generated.hpp`** and calls `dispatch/call/syscall/mfc0/mtc0/ld32/st128/fp::add/mmi::paddw/vu::…` (`runtime/include/ps2/generated.hpp` L1-60) — the emitted code is a client of this runtime's ABI, not of ours. Native output exists (`ps2run`, `host/main.cpp`, SDL2 window `host/window.cpp` L5-6) but the GPU GS is **WebGPU compute shaders** (`runtime/src/gs/gpu/gs.wgsl` 1,144 lines, `gpu.cpp` 1,862) through `wgpu-native` on native builds (`CMakeLists.txt` L54-79); `runtime/src/gs/raster.cpp` (474 lines) is the software reference GS.

### CPU-model fidelity (R5900)
| Item | Verdict | Evidence [obs] |
|---|---|---|
| 128-bit GPRs, MMI (`paddw`, `pextlw`, `pcpyld`, `pcpyud`, `qfsrv`, `pmfhl/pmthl`, `plzcw`, `pinth`, …), `lq/sq` | **handled** | `recomp/r5900.cpp` L121 `decode_mmi`, `kPrimary` has `Lq, Sq, Lqc2, Sqc2` (L12-20); `runtime/include/ps2/mmi.hpp` 354 lines, 78 inline ops via `PS2_LANES` (L34-50) incl. saturating forms; codegen cases for each |
| Two HI/LO pairs, `mfhi1/mflo1/mthi1/mtlo1`, `mult1/madd1/div1/divu1` | **handled** | `codegen.cpp` L426-433 (`c.hi.d[1]`, `c.lo.d[1]`), L445-448 (`mmi::div(c, 1, …)`) |
| SA register (`mtsa/mtsab/mtsah/mfsa`, `qfsrv`) | **handled** | `codegen.cpp` L455-458 |
| FPU with PS2 semantics | **handled (bit-level)** | `runtime/include/ps2/fpu.hpp`: `flush()` denormals (L15), `add`/`mul` on raw mantissas with truncation and saturation to `0x7FFFFFFF` on overflow (`pack`, L18-22, L24-68), `div/sqrt/rsqrt` via double then `from_double` (L95-117), `cvt_w_s` truncate+saturate (L125-137), `max/min/c.eq/lt/le` on a signed key (L119-123); `MaddS/MsubS` use `c.facc` (codegen L140-146). Last-bit exactness vs hardware not verified by us; README admits VU "can differ … in its last bit" |
| COP0 Count/Compare/Status, `ei/di/eret` | **partial** | `runtime/src/kernel.cpp` L826-840: `mfc0` reg 9 → `now()` cycle counter, reg 12 → `c.cop0[12]`; `mtc0`; `Ei/Di → set_interrupts` (codegen L121-122), `eret` (L225). Compare/timer interrupt via COP0 not seen [inf: EE timers are in `hw.cpp`, which the game uses instead of COP0 Compare] |
| **VU0 macro mode** (`vadd…`, `qmfc2/qmtc2`, `cfc2/ctc2`, `vcallms`) | **handled** | codegen L156-194+: `Qmfc2/Qmtc2` (interlock bit → `vu0_wait`, which is a no-op: `runtime/src/cop.cpp` L58), `Cfc2/Ctc2` incl. `vi` writes, broadcast/Q/I forms, `Vcallms/Vcallmsr → vcallms()` → `vu::run(0, addr)` (interpreted VU0 micro, `vu_micro.cpp` L1121); `bc2f/bc2t → vu0_busy` (L299-300). VU0 state in `Vu0Regs` (`cpu.hpp` L36-50) incl. MAC/STATUS/CLIP flags |
| Delay slots incl. likely branches | **handled** | `Flow::BranchLikely` (`r5900.cpp` L231); `condition()` covers all `*l` forms incl. `bc0fl/bc1fl/bc2fl` (codegen L288-302); `Bltzall/Bgezall` put the slot inside the taken path (L333-335); a branch/syscall in a delay slot stops with "unsupported delay slot" (L306-308). Unit-boundary likely-slot bug was found and fixed with GoW II (README "A second game") |
| `sync`, `cache`, `pref` | **no-op** (appropriate for a flat-memory port) | codegen L425 |
| Jump tables / indirect calls | **handled, iterative** | `analysis.cpp` `computed_branches` (L150-187: `jr` fed by `addu` of a `lui/addiu` table constant, stride from `sll`, ≤64 slots), `address_constants`, `frame_starts`; unknown targets at run time → `bad_entry` → `port.sh` adds them to `--entries` and re-translates (README "Port a game of your own") |
| `syscall` dispatch | **handled** | codegen L422 `syscall(c, pc)`; `kernel.cpp` L462-475 reads `$v1`, negates the `i*` form, honours a guest `SetSyscall` table, ~70 numbers (L476-727), logs `[sys] unhandled syscall` (L729) |
| Overlays / code loaded at runtime | **handled** (not needed by P3FES) | `--overlays`, `--modules` (SNR2 relocatable modules, `snr2.cpp`), `ModuleInfo.fixed_base/checks` (`generated.hpp` L22-33), `scripts/windows.py` |
| Interrupt handlers (VBlank `0x4D47F0`), alarms | **handled** | `kernel.cpp` L479-495 (`AddIntcHandler/AddDmacHandler/SetAlarm`), `on_vblank_start` (L435), guest handlers re-entered on the host stack with `g_guest_calls` bookkeeping (L85, L188-195); `system.cpp` L153-168 schedules VBlank start/end on an hblank-derived clock |
| Thread model | **handled** | thread switch unwinds the host stack (`kUnwind` bit in `pc`, `dispatch.cpp` L146-191; `cpu.hpp` L71), cycle `budget` pre-emption (`system.cpp` L212-229) — no per-thread host stacks |

### Function-boundary input [obs]
Own control-flow explorer (`analysis.cpp` `Explorer`, L12-110) seeded from the ELF entry, `.symtab` symbols (`elf.cpp` — empty for our stripped ELF), `--entries <file>` (plain hex tokens, `module:hex` for module entries; `main.cpp` L28-42) and up to eight heuristic rounds. **Sizes/ends are not consumed**; code is marked per word. Our `functions.json` exports to `--entries` trivially (14,040 lines), which would remove the discovery rounds, but IDA's chunk/size knowledge is thrown away [inf].

### Runtime / HLE model [obs, line counts]
EE kernel HLE (`kernel.cpp` 888) · IOP: **R3000 interpreter** (`iop/cpu.cpp` 210) + reimplemented IOP kernel/libs (`iop/kernel.cpp` 814, `iop/libs.cpp` 1,291, thvpool `cb1d8a6`) running the game's own IRX · SIF (`sif.cpp` 867) · CDVD from the disc image (`iop/cdvd.cpp` 187, `cdvdfsv.cpp` 179, `disc.cpp`) · DMAC (472) · VIF (405; `MSKPATH3` → `gif::set_path3_masked`, `vif.cpp` L232, added in `a85a2b8` 2026-10-14 "Bring up Burnout 3") · GIF (219) · GS software (`gs.cpp` 1,153 + `raster.cpp`) and WebGPU · VU1 interpreter (`vu_micro.cpp` 1,144) + AOT compiler (`vurecomp.cpp`) + JIT (`vu_jit.cpp` 2,087) with pipeline/flag delays · IPU MPEG-2 (`ipu/ipu.cpp` 716) · SPU2 (`iop/spu2.cpp` 614) · SIO2 pads/memcards (439) · save states.

**What fes-pc-recomp had to patch for P3FES on this runtime** (`fes-pc-recomp/tools/*.py` docstrings [obs]): VIF1 `MSKPATH3` pulse semantics (`ps2run_fix_path3_mask.py`: textures landed before the draws that needed them → floor noise F1, dark rooms F2, menu corruption F3); VIF `UNPACK V2` lanes 3-4 zero-fill (`ps2run_vif_v2zero_patch.py`, cut-in panels); VU integer-branch reading the *old* register after `ISUBIU` (`ps2run_vubranch_patch.py`) — upstream addressed the branch delay on 2026-10-18 (`7b6b604`, `18ad888`, `b3e328f`) and a `MSKPATH3` model on 2026-10-14; whether these match fes-pc-recomp's patches is **unverified**; texel-centre sampling and flipped-tile alignment in the Tartarus minimap (`ps2run_tricenter_patch.py`, `ps2gpu_flipfix_patch.py`); `[sif] command 0x80000004 has no handler` ~2×/frame (`docs/playtest-plan.md` L30); **sound not implemented** (F4, L29). Sofdec/IPU needed no patch here [inf from absence].

### Testing & maturity [obs]
`scripts/test_vu_codegen.py` (VU codegen: native vs Wasm vs interpreter, no disc); commit `2751ff3` "compiled VU programs proven against the interpreter". No EE instruction tests, no CI directory, no differential tracer; debugging aids are `probe()` insertions (`codegen.cpp` L216), `PS2_TRACE_*` switches, a write watchpoint (`4594bc7`), save states and PPM frame dumps. Known-good titles: GT4 PAL and GoW II [claim; `docs/media/demo.webp`/`demo.mp4` exist for GT4], Burnout 3 to menus (`a85a2b8`), KH2 (PR #13 "KH2 VU correctness fixes"), P3FES via fes-pc-recomp [claim].

### The "dormitory 3D scenes, 0 unhandled syscalls" claim — claim vs evidence
- **[claim]** `fes-pc-recomp/docs/playtest-plan.md` L9-20: "0 unhandled system calls, 0 missing IOP functions and 0 new entry points in the last three runs (60,000 frames…)" → logo, movie, title, menu, New Game, name entry, second movie, dorm 3D scenes, cut to the street; L126: later scripted runs reached the school. `docs/phase1-summary.md` L25, L41 repeat it (3,600 → 16,000 → 60,000 frames).
- **[obs] evidence in the repo: none.** Policy L5: "Game pictures … stay on your own PC"; no screenshots, logs or state files are committed; all 31 commits are web uploads ("Add files via upload"). The upstream `ps2-web-recomp` repo does not mention P3FES. Status: **plausible but unverified**; reproducible by us under WSL2 per `docs/windows-build.md` if the lead wants a second oracle (see §7).

---

## 2. Candidate B — `ran-j/PS2Recomp` (GPL-3.0), the base of `poopoocacacacaca/p3fes-recompiled`

### Identity [obs]
- **Which "PS2Recomp":** `p3fes-recompiled` commit `eb552f8` "Import PS2Recomp at upstream commit 2c5fbb9"; `2c5fbb9` is in `ran-j/PS2Recomp` history (2026-10-05 "Dispatch syscalls 0x79/0x7A… (#274)"). It additionally merged `KIexster/god-of-war-recomp` (GPL-3.0, 120 ★, 550 commits, 5 contributors, pushed 2026-10-18) and PCSX2's GS/IPU (GPL-3.0). It is **not** `snuri00/ps2-web-recomp`, and GOAL.md's phrase "PS2Recomp-style" describes the per-instruction-to-C++ *style*, not this repository.
- https://github.com/ran-j/PS2Recomp · `main` · created 2025-04-12 · pushed 2026-10-14 (`eb8688b` "Emulate PS2 float semantics for EE FPU results and DIV.S/RSQRT.S (#272)") · 169 commits · 21 contributors (Ranieri 18 of the last 50) · 3,580 ★ / 194 forks / **162 open issues** · **GPL-3.0** (`LICENSE`). ~100k lines outside `third_party/` [obs `wc -l`]; modules `ps2xAnalyzer`, `ps2xRecomp`, `ps2xRuntime`, `ps2xIOP`, `ps2xStudio` (imgui GUI), `ps2xTest`, plus `android/`, `vita/`.

### Emitted artefact [obs]
C++ **per function**; `addiu $r4,$r4,0x20` → `ctx->r4 = ADD32(ctx->r4, 0X20);` (README); macros in `ps2xRuntime/include/ps2_runtime_macros.h` (1,031 lines; 176 `_mm_`/`__m128` SSE uses; `__declspec(noinline)` branch for MSVC L154) — **MSVC-portable**, CI has a `windows-msvc` matrix (`.github/workflows/build.yml` L41-59). Generated files include `ps2_runtime.h`, `ps2_syscalls.h`, `ps2_stubs.h` (`ps2_recompiler.cpp` L104-110) → coupled to its runtime API. Recompiler is a library (`ps2xRecomp/src/lib`) and separable in principle, but GPL.

### CPU-model fidelity
| Item | Verdict | Evidence [obs] |
|---|---|---|
| 128-bit GPRs, MMI, `lq/sq` | **handled, with a record of late bugs** | `instructions.h` (804 lines) enumerates MMI0-3, PMFHL sub-functions (L365-372), `LQ/SQ` (L87-88), `MTSA/B/H`; `mmi_translation_helpers.cpp` 608 lines. Upstream fixes: MMI2 `PMADDH/PHMADH/PMSUBH/PHMSBH` opcode mapping (`d87bff4`, 2026-08-01), SSE4.1 `PADDSW/PSUBSW` paths (`3a2e0d6`). **p3fes-recompiled had to fix `PMFHL/PMTHL` to use all four HI/LO words "(fixes libmpeg/Sofdec math)" and 64-bit compares for `BLEZ/BGTZ/BLTZ/BGEZ` and likely/link forms** (`56d6601`) — on their fork; not seen upstream as of `eb8688b` [inf] |
| HI1/LO1 | handled | `MMI_MFHI1/MFLO1/MULT1/DIV1` (`instructions.h` L237-244), `ctx->hi1/lo1` (fork commit above) |
| FPU semantics | **partial** | #272 (2026-10-14): clamp inputs/results, `x/0 → ±max`, `RSQRT` operand order; arithmetic itself is host `float` with clamping (`ps2_runtime_macros.h` L143-260, `ps2_vclamp` SSE L322-354) — not bit-exact rounding. p3fes-recompiled added "CVT.W.S truncates and saturates like the R5900 FPU" (`616ed77`) on its fork |
| COP0 | partial | `cop0_translator.cpp` maps every register to `ctx->cop0_*` (Count L47, Compare L51); `patch_cop0` TOML option |
| VU0 macro | handled | 50 `translateVU_*` emitters (`vu_translation_helpers.cpp` 886 lines) incl. `VCALLMS/VCALLMSR` (L150-167); runtime `Kernel/Stubs/VU.cpp` 1,103 lines; #183 HLE `sceVu0*` math library |
| Likely branches / delay slots | handled | `control_flow_emitter.cpp` L61-66, L464-500 |
| `sync/cache` | config-driven | `patch_cache` option (README) |
| Jump tables / indirect | **partial** | tables come from TOML (`setConfiguredJumpTables`, `code_generator.h` L54) → `switch (jumpTarget)` (`control_flow_emitter.cpp` L373); otherwise `runtime->lookupFunction(0x…)`. p3fes-recompiled README: "14 recovered jump tables, 453,264 indirect-jump fallback entries" |
| `syscall` | handled | encoded immediate first, then `$v1` (README "Current Behavior") |
| Overlays | partial | self-modifying code "flagged but requires manual review" (`ps2xAnalyzer/Readme.md` "Limitations") |
| Interrupts / threads | handled | `Kernel/EeScheduler.cpp` 2,146 lines (#184 "from guest threads to EE scheduler"), interrupt tests (`ps2_runtime_interrupt_tests.cpp` 751) |

### Function-boundary input [obs]
Preferred: Ghidra `ps2xRecomp/tools/ghidra/ExportPS2Functions.java` → TOML + CSV `Name,Start,End,Size` (L1070), loaded by `ElfParser::loadGhidraFunctionMap` (`elf_parser.cpp` L2115). Also DWARF, a JAL scanner, and an embedded 12 MB SCE symbol database (`ps2xAnalyzer/include/ps2recomp/sce_symbol_database_data.h`, "Generated from sce-symbol-scanner symboldb resources"; `Readme.md`: "built from PS2 games with debug information, primarily the Japanese set" — i.e. derived from commercial binaries [inf: provenance unclear]). Our `functions.json` would map 1:1 onto the CSV.

### Runtime / HLE model [obs]
Name/address-bound HLE stubs (`Kernel/Stubs/`: `MPEG.cpp` 2,573, `GS.cpp` 1,541, `MemoryCard.cpp` 1,532, `LibC.cpp` 1,195, `CD.cpp` 989, `Pad.cpp` 863, `SIF.cpp` 847, `Audio.cpp` 657, `Font.cpp` 667), `ps2xIOP` R3000A interpreter + virtual IOP kernel running IRX, VIF1 interpreter, VU1 interpreter (~3.1k lines), **GS: CPU backend only** (`gs_cpu_backend.cpp` 1,980; raylib window) — README "Limitations: Performance is very bad for VU and GS". **What p3fes-recompiled added for this game** (commit log [obs]): IPU + scratchpad DMA so FMVs play (`c1c9ae6`), SPU2 ADMA/BVOL (`a462f00`, `91b4d55`, `d4f1632`), memcards via SIO2 (`83fc57b`), thread-syscall return values and `ChangeThreadPriority` for CRI ADX (`616ed77`), `keep_guest` so `sceIpu*/sceMpeg*` stay guest code (`56d6601`), and finally **replaced the GS with PCSX2's as a shared library** (`f0ab0aa`, `e8a461e`) — i.e. the native GS was not good enough for the opening movie/menus.

### Testing & maturity [obs]
`ps2xTest/` MiniTest harness, 19 suites (decoder, codegen, recompiler, float semantics, VU, VU1, GS, kernel, interrupts, SIF, IOP; ~30k lines); CI ubuntu + windows-msvc. No fully playable title in README; GoW [claim, KIexster]; Killzone mentioned in #272; p3fes-recompiled reaches title/menu at 0.75× [claim, README "Status"; no screenshots — `p3fes/branding/` only; progress SVG is generated from hand-edited `status.toml`].

### Verdict
Technically the most complete per-function PS2 recompiler and MSVC-clean, but **GPL-3.0 (plus GPL god-of-war and PCSX2 pieces, plus a map derived from snaku's unlicensed symbols)** — excluded by ADR-0009.3 regardless of merit. Consult-only: its `stubs`/`keep_guest` list and the P3FES fork's bug commits are a checklist of pitfalls (PMFHL four-word semantics, 64-bit branch compares, CVT.W.S saturation, CRI ADX priority-0 threads, SPU2 ADMA pacing).

---

## 3. Candidate C — `Mr-Wiseguy/N64Recomp` (MIT) as the architectural model, R5900 semantics by us

### Identity [obs, `gh api`]
https://github.com/Mr-Wiseguy/N64Recomp · `main` · created 2022-11-16 · pushed 2026-05-27 (`ffb39cd` "dump symbols in deterministic order (#179)") · 110 commits · 14 contributors (Wiseguy 31 of 50) · 8,266 ★ / 460 forks / 58 open issues · **MIT** (`LICENSE`, "Copyright (c) 2024 Wiseguy"). ~14k lines (`src/` ~6.2k, `LiveRecomp/` 2.3k, `RSPRecomp/` 1.2k, mod tools). Submodules (`.gitmodules`): **rabbitizer** (decoder; MIT, 182 ★, README L51 "R5900 (PS2's Emotion Engine processor) decoding support" [obs via `gh api …/readme`]), ELFIO, fmt, tomlplusplus, sljit.

### Emitted artefact [obs]
**C, one function per guest function**: `RECOMP_FUNC void name(uint8_t* rdram, recomp_context* ctx)` (`src/cgenerator.cpp` L398); operations through macros (`ADD32`, `MEM_W`, `LOOKUP_FUNC(addr)(rdram, ctx)`, L25-61, L410-414); `functions_per_output_file` (`src/main.cpp` L618-657). `include/recomp.h` L10-35 has explicit `_MSC_VER`/clang/gcc branches (`_mul128` for MSVC) — README: "tested with msvc, gcc and clang"; CI matrix includes `windows-latest` (`.github/workflows/*.yml` L18). Runtime is a **separate repository** (N64ModernRuntime) by design. The emitter is behind a virtual `Generator` interface (`include/recompiler/generator.h` L28-70) with `CGenerator` and a `LiveGenerator` JIT — the cleanest separation of decode/semantics/emission among the three.

### CPU-model fidelity for R5900
| Item | Verdict | Evidence [obs] |
|---|---|---|
| 128-bit GPRs / MMI / `lq/sq` / HI1-LO1 / SA / COP2 | **missing** (N64 VR4300 target) | `include/recompiler/operations.h` enumerates MIPS III integer + IEEE single/double FPU only; `cgenerator.cpp` op table L25-61 |
| FPU | wrong model for EE | IEEE with `fenv` rounding (`recomp.h` L15-30), double precision, NaN checks (`emit_check_nan`) — the EE has none of these |
| COP0 | Status only | `src/recompilation.cpp` L418-444 ("Unhandled cop0 register") |
| Delay slots / likely branches | **handled** (reusable pattern) | slot duplication (`process_delay_slot`, L209-230); likely branches via `skip_N` labels (L823-859) |
| Jump tables | **handled** (reusable pattern) | `src/analysis.cpp` L104-235: `lui/addiu` + `sll` + `lw` + `addu` + `jr`, incl. PIC/GOT variant → `emit_switch` |
| Indirect calls / overlays | handled | `LOOKUP_FUNC`, relocatable sections (README "Overlays") |
| `syscall`/`break` | handled | `recompilation.cpp` L563-570 → `emit_syscall/emit_do_break` |
| `sync/cache` | not seen | no `cpu_cache`/`cpu_sync` cases in `recompilation.cpp` [obs grep]; handling unknown [inf: ignored by rabbitizer categorisation or treated as nop] |

### Function-boundary input [obs]
ELF with symbols, **or a TOML symbols file**: `[[section]] rom, vram, size, name, functions = [{ name, vram, size }]` (`src/config.cpp` L553-640), plus `manual_funcs`, `function_sizes`, `[patches] stubs/ignored/renamed/instruction/hook` (L22-258). Our `functions.json` `{a, s, n}` maps field-for-field. **Caveat [inf]:** functions are assumed contiguous (`words` read from `vram..vram+size`); our 172 multi-chunk functions need a chunk list or per-chunk pseudo-functions.

### Runtime / testing [obs]
Runtime not applicable (N64 hardware). Tests: `LiveRecomp/live_recompiler_test.cpp` (364 lines); CI five-OS matrix. Known-good: Zelda 64: Recompiled [README]. Maturity of the *architecture* is high (3.5 years, shipped ports, modding tool chain); nothing PS2-specific exists.

---

## 4. Candidate D — from scratch
What we already have [obs]: `runtime/include/p3fes/ee_context.h` (128-bit `gpr/hi/lo`, `sa`, `fpr/acc/fcr31`, `cop0[32]`, `VU0State` with MAC/STATUS/CLIP), `ee_memory.h` (32 MiB + scratchpad + mirrors), `syscalls.h` (ps2sdk numbering), `vu1_interp.h` placeholder, `recomp/src/main.cpp` CLI stub, doctest harness, D3D11/XAudio2 host. Everything else (decoder, emitter, 78 MMI ops, FPU model, COP2 macro, kernel HLE, IOP, DMAC/VIF/GIF/GS, VU1, IPU, SPU2, SIO2, CDVD) would be written without reference implementations — the only argument for D over C is avoiding the N64Recomp learning curve, which is small (6k lines).

---

## 5. Comparison matrix

| | A `ps2-web-recomp` | B `PS2Recomp` | C N64Recomp-shaped, R5900 by us | D scratch |
|---|---|---|---|---|
| License (SPDX) | MIT (+BSD-2 tables) | **GPL-3.0** (+GPL deps) | MIT (N64Recomp, rabbitizer) | ours |
| Output language | C++20, **clang-only** (`musttail`, `vector_size`) | C++20, MSVC-clean (SSE intrinsics) | C/C++ per function, MSVC/clang-cl | C++20 per function (we choose) |
| Separable core | recompiler builds alone, output bound to its runtime ABI | library, bound to its runtime headers | yes by design (`Generator` interface, separate runtime) | n/a |
| Granularity | **16 KiB units** + `switch(entry)` | per function | per function | per function |
| MMI (128-bit, HI1/LO1, SA) | handled (`mmi.hpp` 78 ops) | handled, late-found bugs (PMFHL, MMI2 map) | **to write** (~78 ops; can port A's `mmi.hpp` under MIT) | to write |
| VU0 macro | handled, interlock no-op, micro via interpreter | handled (50 emitters) | **to write** (can port A's `vu_ops.hpp`) | to write |
| FPU semantics | bit-level, no NaN/Inf/denormal, truncating | host float + clamp (partial) | **to write** (A's `fpu.hpp` is 142 lines) | to write |
| Overlays | handled (not needed) | flagged only | handled (not needed) | not needed |
| Boundary input | hex entry list; **sizes ignored**, own scan | Ghidra CSV `Name,Start,End,Size` | TOML `{name, vram, size}` ≙ our `functions.json` | ours |
| Runtime coupling | WebGPU GS, SDL2 host, Emscripten build scripts, HTTP-Range disc | raylib/imgui, CPU GS, ps2xIOP | none (runtime is ours) | none |
| Maturity | 10 days; GT4/GoW II playable [claim]; P3FES to 3D field [claim] | 18 months; 162 open issues; no playable title in README | 3.5 years; shipped N64 ports; zero PS2 code | 0 |
| Tests / tracing | VU codegen test only; probes, watchpoints, save states | 19 MiniTest suites, MSVC CI | live-recomp test, 5-OS CI | ours (`tracediff`, compiled vectors) |

### What each path leaves *us* to write (subsystems)
- **A (adopt wholesale):** switch primary compiler to clang-cl (ADR-0003 amendment) or rewrite `cpu.hpp`/codegen for cl.exe; GS backend WebGPU→D3D11 (port `gs.wgsl` compute to HLSL, or run wgpu-native on D3D12 against ADR-0003); SDL audio→XAudio2 and SDL input→XInput (or accept SDL2 as a dependency); a per-function interposition mechanism for Phase 5 (units have none; only `probe()`); per-instruction `trace_step` emission for `docs/TRACE_FORMAT.md` Level A; the IDA→`--entries` exporter; CVM sector mapping in `disc.cpp` (ADR-0008); P3FES sound (unimplemented on A per fes-pc-recomp F4); tracking a fast-moving upstream while diverging in all of the above.
- **B:** nothing adoptable (GPL). Even ignoring license: a GPU GS (its own is CPU-only), XAudio2, the P3FES fork's fixes.
- **C (recommended):** the emitter itself (modelled on N64Recomp's `recompilation.cpp`/`cgenerator.cpp` patterns: delay-slot duplication, likely skip labels, jump-table switch, `LOOKUP_FUNC`), a decoder (rabbitizer R5900 via submodule, or our own table — A's `r5900.cpp` is 254 lines), R5900 semantics headers against our `EEContext` (MMI, FPU, COP2 — port from A with attribution, verified by compiled vectors), and **the whole runtime**: kernel HLE, IOP interpreter + IOP libs, SIF, DMAC/VIF/GIF, GS→D3D11, VU1 interpreter, IPU, SPU2→XAudio2, SIO2, CDVD sector HLE. For each runtime subsystem A is an MIT reference (`iop/`, `ipu/`, `spu2.cpp`, `vif.cpp`, `dmac.cpp`, `kernel.cpp`, `vu_micro.cpp`, `raster.cpp`) that can be ported piecemeal onto our interfaces.
- **D:** everything in C plus the decoder and the emitter architecture, with no reference for any PS2 quirk.

---

## 6. Risks

1. **License contamination.** B and everything downstream (`god-of-war-recomp`, PCSX2 GS/IPU, `p3fes-recompiled`) is GPL-3.0; `p3fes-recompiled`'s map is 99 % snaku's unlicensed symbols (`docs/COMMUNITY.md` §2); B's SCE symbol DB is derived from commercial debug builds. Rule: nothing from B is opened in an editor next to `recomp/`; A's and N64Recomp's MIT notices go into `THIRD_PARTY_NOTICES` for any ported file; Play!'s BSD-2 notice travels with IPU tables if ported.
2. **Web-centric assumptions in A.** WebGPU compute GS, SharedArrayBuffer worker threading, Emscripten tail calls (`-mtail-call`), HTTP-Range disc streaming, 16 MB GPU upload cache tuned for Chrome (README "Lessons"). Porting semantics is safe; porting the GS/host layer is not.
3. **Compiler coupling in A.** `[[clang::musttail]]` and GNU vector extensions break cl.exe; adopting A silently flips ADR-0003.
4. **AI-generated provenance.** `p3fes-recompiled` self-describes as "AI-Powered" and merges from `/home/claude/p3fes-port` (`0ad3958`); `fes-pc-recomp` docs are written with Claude (`playtest-plan.md` L5); A's commit prose is uniform and the author's style is consistent with assisted authoring [inf, not evidence]. Consequence: every borrowed semantic must be validated by our compiled test vectors (ADR-0006.5) and PCSX2 traces, never trusted by reading.
5. **Churn and single-maintainer risk in A.** 54 of 76 recent commits by one author; four VU-timing fixes in one day; semantics may change under us. Pinning a commit and porting *facts* avoids this; forking the runtime does not.
6. **Boundary mismatch.** A discards IDA sizes and re-scans; a fork would fight ADR-0004. N64Recomp-style input consumes IDA exactly but assumes contiguous functions — our 172 multi-chunk functions need an explicit design (chunk lists or IDA-side splitting).
7. **Claims without artefacts.** Every "runs to X" statement for P3FES is text in a repo that forbids screenshots (fes-pc-recomp) or a hand-edited status table (p3fes-recompiled). Treat as a motivating prior, not as proof that A's runtime models are complete for this game (sound is explicitly missing; `[sif] 0x80000004` unhandled).
8. **FPU last-bit exactness.** A's `fpu.hpp` is bit-level but unverified against hardware; B clamps host floats; neither has published vectors. Our Phase 4 vectors are required either way.

---

## 7. Recommendation

**Choose C, with A as the MIT semantic reference and second oracle; never B.** Write `recomp/` ourselves in the N64Recomp shape — per-function C++ against our `EEContext`, `symbols/functions.json` as the only boundary authority, `LOOKUP_FUNC`-style dispatch for indirect calls, delay-slot duplication and likely-branch skip labels, jump-table recovery from IDA's switch-table analysis exported alongside `functions.json` [inf: IDA's MIPS module normally recovers `switch` tables, but we have not yet checked this on `p3fes.i64`] with an `addu/lw/jr` scan as a fallback — and port the R5900 *semantics* (MMI, FPU, COP2 macro) and, subsystem by subsystem, the runtime models (IOP kernel/libs, IPU, SPU2, VIF/DMAC/GIF, VU1 interpreter, kernel HLE) from `ps2-web-recomp` under MIT attribution, each landing only with compiled test vectors or a `tracediff` run. Separately, reproduce fes-pc-recomp's WSL2 build of A (`docs/windows-build.md`) to obtain a *second* running reference for Phase 4 that can be probed per instruction, which PCSX2 cannot without a patched build (`docs/TRACE_FORMAT.md` §6).

Why not A as the base: clang-only output and headers (ADR-0003), 16 KiB-unit granularity defeats Phase 5's function-at-a-time replacement, a GS and host layer we would discard, ten days of history with one dominant author, and a function-discovery model that discards IDA's work. Why not D: it gives up a proven emitter architecture (N64Recomp) and the only MIT-licensed, game-proven PS2 semantics (A) for no gain.

### Draft ADR-0010 · 2026-10-18 · `recomp/` is our own per-function recompiler in the N64Recomp shape; `ps2-web-recomp` (MIT) is the semantic reference and second oracle; GPL `PS2Recomp` is consult-only
**Context.** `docs/RECOMP_OPTIONS.md` evaluated four bases against ADR-0003 (MSVC primary, D3D11), ADR-0004 (IDA boundaries + raw instructions), ADR-0009.3 (no GPL) and Phase 5 (per-function replacement under `tracediff`). `snuri00/ps2-web-recomp` (MIT, 1,068 ★, created 2026-10-08) has complete R5900 semantics — 128-bit MMI (`runtime/include/ps2/mmi.hpp`), two HI/LO pairs, bit-level EE FPU (`fpu.hpp`), VU0 macro + micro, likely branches, `SetSyscall`-aware kernel, IOP R3000 interpreter running IRX, IPU, SPU2, VU1 with pipeline timing — and reportedly runs `SLUS_216.21` to the dormitory 3D scenes with 0 unhandled syscalls (fes-pc-recomp, text only, unverified). But it emits clang-only C++ (`[[clang::musttail]]`, GNU `vector_size`) in 16 KiB units with `switch(entry)` dispatch, re-discovers functions itself and ignores sizes, and its GS is WebGPU compute. `ran-j/PS2Recomp` (GPL-3.0; the base of `p3fes-recompiled` together with GPL `god-of-war-recomp` and PCSX2 GS) is per-function and MSVC-clean but license-incompatible, and its P3FES fork needed PMFHL/branch/CVT fixes. `Mr-Wiseguy/N64Recomp` (MIT, 8,266 ★) has the right architecture — per-function C through a `Generator` interface, TOML `{name, vram, size}` symbol input, delay-slot duplication, likely-branch skip labels, jump-table switches, `LOOKUP_FUNC` dispatch, MSVC/clang/gcc output, runtime in a separate repo — and no PS2 semantics at all.
**Decision.**
1. `recomp/p3fes_recomp` is written by us, modelled on N64Recomp's `recompilation.cpp`/`cgenerator.cpp`: one C++ function per IDA function (chunk-aware for the 172 multi-chunk functions), input = `symbols/functions.json` + the ELF, output against `runtime/include/p3fes/ee_context.h`. Decoder: rabbitizer's R5900 tables (MIT) if the submodule proves complete on our 1,790 MMI / 3,589 COP2 instructions in a census pass, otherwise our own table (`ps2-web-recomp/recomp/r5900.cpp` is the 254-line reference). No N64Recomp *code* is copied beyond patterns; if any is, MIT attribution is added.
2. R5900 semantics (MMI, FPU, COP2 macro, SA, HI1/LO1) and runtime models (kernel HLE, IOP kernel/libs, SIF, DMAC/VIF/GIF, VU1 interpreter, IPU, SPU2, SIO2, CDVD) are **ported from `ps2-web-recomp` @ `c0f476e` under MIT attribution** (`THIRD_PARTY_NOTICES.md`; Play! BSD-2 notice with IPU tables), adapted to our interfaces (`EEMemory`, D3D11 `gs_backend.h`, XAudio2 `spu2_backend.h`, sector-level CVM CDVD per ADR-0008). Each ported unit lands with compiled R5900 test vectors (ADR-0006.5) or a `tracediff` pass; nothing is trusted by reading.
3. `ps2-web-recomp` is additionally built unmodified under WSL2 (per `fes-pc-recomp/docs/windows-build.md`) as a **second oracle** for Phase 4, pinned to a recorded commit, in gitignored `tools/third_party/`. Divergences between it, PCSX2 and us are triaged in that order of authority (PCSX2 > ps2-web-recomp > us).
4. `ran-j/PS2Recomp`, `god-of-war-recomp`, `p3fes-recompiled` and PCSX2 sources are **never opened alongside `recomp/` or `runtime/`**; their commit logs and `stubs`/`keep_guest` lists are consulted as a pitfall checklist only (`docs/COMMUNITY.md` §2).
5. The compiler stance of ADR-0003 is unchanged: generated code and runtime compile under cl.exe and clang-cl; SIMD via `<immintrin.h>` intrinsics or portable lane loops, never GNU vector extensions or `musttail`.
**Why not alternatives.** Building on `ps2-web-recomp` would make clang-cl primary, lock Phase 5 to 16 KiB units, inherit a WebGPU/SDL host we must discard, and tie us to a ten-day-old single-maintainer codebase changing daily; forking it is more maintenance than porting its facts. `PS2Recomp` is GPL-3.0 and its P3FES derivative carries snaku's unlicensed map. From scratch forfeits a proven emitter architecture and the only MIT, game-proven PS2 semantics for no benefit.
**Consequences.** `recomp/` gains a decoder, a chunk-aware function walker, a `Generator`-style emitter and semantic headers; `runtime/` grows subsystem by subsystem with a provenance line per ported file. First measurable milestone: all 14,040 functions emitted and compiled under both compilers with `start`…`main` executing to `SetupThread` under `tracediff` against PCSX2. Phase 4 gets two oracles. Revisit this ADR if (a) ps2-web-recomp gains an MSVC/D3D path and per-function hooks, or (b) rabbitizer's R5900 coverage proves incomplete and the decoder cost dominates.
