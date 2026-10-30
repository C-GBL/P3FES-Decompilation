# Phase 2 — shared brief for topic agents

_Read this before any Phase 2 analysis. It is the contract between the lead and each topic agent; the topic-specific ask is appended by the lead when the agent is launched._

## Ground truth you start from
- Target: `extracted/disc/SLUS_216.21`, SHA-256 `d1b163eb…57bc`; `r5900l`, LE, base `0x00100000`, entry `0x00100008`. Compiler **Metrowerks MW MIPS C 2.4.1.01**; SDK **3.1.0**; CRI libs ee-gcc 2.96. Fully stripped. Layout: code `0x100000–0x5A1400`, data `0x5A2000–0x7CDE04`, `.bss` `0x7CDE80–0x9ACC80`, heap from `0x9ACC80`, stack `0x1F60000–0x2000000`, gp `0x7D2CF0`. (`docs/ANALYSIS/00`, `01`)
- Anchors: `start 0x100008` → `main 0x193980` → `main_loop_candidate 0x1984C0`; IRX loader `0x197030`; `crt_init_runtime 0x50D658`; `exit_candidate 0x51F6A0`. Source-file → address-band map in `03` (`kwln*`, `h_*`, `k_*`, `btl*`/`dat*`, `scr*`, `mt_evt*`, `itf*`/`fr*`, `comu*`/`fcl*`, `op_*`, `G3_2D*`). Syscall table in `02` (168 sites, 159 wrappers `_sce*`). FLIRT-derived library names (`05`): 1,184, tagged `flirt`. Community hints (`07`, if present): tagged `source=…`.
- Disc: `docs/DISC_LAYOUT.md` — the ELF embeds the ROFS directory tree (`#DirLst#` tables VA `0x5E5150–0x6784B8`), volume strings `CDV:*.cvm` `0x678798+`, route table `0x7CB188–0x7CB268`, `ROFS_*` `0x7C6FF8+`, `sceCdSearchFile` `0x7C4C78`. `extracted/manifest.json` = path ↔ LBA ↔ size for every file. CDVD HLE will be sector-level (ADR-0008).
- Decisions that bind you: ADR-0004 (recompiler consumes disassembly), ADR-0008 (I/O), ADR-0009 (hint vs verified names), ADR-0010 (recompiler architecture; what Phase 3 needs from you).

## Address convention
**Virtual addresses only**, 0x-prefixed, 6+ hex digits. If you ever read the raw file: `VA = file_offset + 0xFFF80`. Every claim cites a VA; observed (IDA shows X) vs inferred (therefore Y) is marked.

## Database protocol — one process per database, never the master
1. `copy ida\p3fes.i64 ida\work_<topic>.i64` (gitignored). Open **only your copy** with idalib (`import idapro` first; `idapro.open_database(path, False)`), save to it, close it. The master `ida/p3fes.i64` is the lead's; you never open it.
2. Ghidra second opinion (read-only): `tools/ours/ghidra/run_export.ps1` shows the headless invocation; `DecompileList.java` decompiles a list of addresses into `ghidra/decomp/` — use it for MMI/`lq`/`mult1` code where Hex-Rays emits `__asm`. Not an oracle: SIMD ops are opaque intrinsics; syscall args are misattributed by both decompilers.
3. Set `$env:JAVA_HOME = 'C:\Program Files\Java\jdk-25.0.4'` before any Ghidra call. idalib venv python: `C:\Users\Ash\.local\share\rea\ida-mcp\Scripts\python.exe`.

## Naming rules
- Name what you **verified** (behaviour read from the instructions, string/syscall/xref evidence recorded). Style: Atlus source-file prefixes where `03` gives one (`kwlnTaskCreate`, `k_fieldLoad…`), `sce*` for SDK functions, `cri*`/`ROFS_*`/`ADX*` for CRI. Globals: `g_<thing>`; tables: `tbl_<thing>`; strings keep IDA's `a*` names.
- Never overwrite a `flirt`-tagged or `source=`-tagged name unless your evidence contradicts it — then rename and record the conflict in your doc.
- Comments: a function comment stating what it does and the evidence; `HINT[...]` comments are from the hint import, leave them.

## Deliverables (per topic)
1. `docs/ANALYSIS/1x_<topic>.md` — findings with a VA on every line that asserts something; tables for inventories (e.g. every GS register written, every IRX RPC id, every CreateThread site with entry/priority/stack); a "what the runtime must emulate" section written for the Phase 3 implementer; a "confidence" line per subsystem; open questions.
2. `symbols/deltas/<topic>.sym` — your names and function comments in the `.sym` line format (`<addr8> <size8> <F|D|L> <name> source=phase2-<topic> ev=<doc anchor>`), plus a `# comments` block the importer understands (see `tools/ours/ida/import_symbols.py --help`). The lead merges deltas into the master with `import_symbols.py` and re-exports `symbols/p3fes.sym`; **your copy is discarded**, so everything must be in the delta.
3. `docs/ANALYSIS/queue_<topic>.txt` — functions you are confident enough about for Phase 5's hand-decompile queue (`addr name one-line purpose`).
3b. **Types** — a `.sym` cannot carry structures. If you defined structs/enums in your copy, export them as a C header `symbols/types/<topic>.h` (IDA: `File → Produce file → C header`, or `ida_typeinf.print_decls` over your local types; our own type recovery, committable) **and** an apply list `symbols/types/<topic>.apply.txt` with lines `<addr8> <TypeName>[<count>]` for every address you applied a type to (arrays as `Type[149]`). The lead imports the header with `ida_typeinf.parse_decls` and applies the list on the master.
4. A final report under 400 words: headline findings with VAs, counts, what Phase 3 must emulate, blockers.

## Rules
- Never execute the ELF or any game file; never copy game bytes into docs (short disassembly excerpts ≤ 12 lines are fine).
- Keep stdout short; log to `ida/logs/<topic>_*.log`. Time-box ~2 h per topic; log rabbit holes under "Blocked" in your doc after ~25 min without progress.
- Do not `git commit`. Do not touch `STATE.md`, `docs/DECISIONS.md`, other agents' `1x_*.md`, `symbols/p3fes.sym`, or the master DB.

## Topics (one agent each; the lead appends the specific ask)
| # | Topic | Doc | Primary anchors |
|---|---|---|---|
| 10 | Frame loop, GS/DMA/VIF init, display env, double-buffering | `10_frame_loop_gs.md` | `0x1984C0`, `sceGsSetDefDispEnv 0x4F9168`, `sceGsPutDrawEnv 0x4F9850`, `sceGsSyncPath 0x4F99D0`, `WaitDma 0x4FA798`, T0_COUNT reads at `0x10000000` |
| 11 | File I/O: path → `#DirLst#` lookup → sector reads; CVM mount; read queue/threads | `11_file_io.md` | `#DirLst#` `0x5E5150+`, `CDV:` `0x678798`, route table `0x7CB188`, `ROFS_*`, `sceCdSearchFile 0x7C4C78`, game file layer `0x1934F0`, `cvFs*` (fes-pc-recomp: `0x555B10+`, `0x100D80`) |
| 12 | IOP modules, SIF RPC ids, threads/semaphores, kernel patch payload | `12_irx_rpc_threads.md` | IRX loader `0x197030`, `sceSifBindRpc`, CreateThread/CreateSema wrappers (`02`), data-band code `0x77F710–0x780A08` (SetSyscall 0x5B hypothesis) |
| 13 | Overlays / dynamically loaded code, self-modifying code, `FlushCache` sites | `13_overlays.md` | `FlushCache` wrappers, any `sceCdRead` whose buffer lands in `0x100000–0x5A1400`, `jr` into buffers, `.bss` code hints |
| 14 | VU1 microcode & GS primitive census; VIF `MPG`/`UNPACK` builders; RenderWare pipelines | `14_vu1_gs_census.md` | VU1 blobs `0x5A0000–0x77xxxx` (181 programs per fes-pc-recomp — verify), `G3_2D*` band `0x46C000–0x4E7000`, `rw*` names from FLIRT/hints, GIF-tag builders |
