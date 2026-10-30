# REA static record — `SLUS_216.21`

Run 2026-10-18 through the `rea` MCP server (rea-agents 6.7.0, protocol 2025-11-25, client claude-code 2.1.301) on Windows 11 x64 with Ghidra 12.1.4, IDA Pro 9.3 (headless) and JADX configured. Raw payloads are the numbered JSON files beside this README; nothing here is paraphrased beyond the tables.

## What REA established
| Call | Outcome | Evidence |
|---|---|---|
| `open_binary` | **accepted** — `format: elf`, `kind: executable`, `architecture: mips`, `sha256 d1b163eb…` (matches `docs/INVENTORY.md`) | `02_open_binary.json` |
| `binary_session` | target bound as a MIPS ELF; everything REA recorded about the target, minus generic server/capability blocks | `03_binary_session_target.json` |
| `inspect_binary_layout` (summary) | **refused** — `pwntools-elf` provider: *"initial real-verified pwntools artifact profile supports Linux x64 only"* | `01_inspect_binary_layout.json` |
| `binary_overview` (any analysis op) | **refused by every provider** — see below | `04_binary_overview_rejections.json` |
| `inspect_artifact` on the ISO (CLI, earlier in session 1) | refused — `unsupported binary format` | STATE.md session-1 notes |

### Provider verdicts on this exact target (from `04_…`)
| Provider | Code | REA's stated reason |
|---|---|---|
| ghidra | `target_format_unsupported` | Windows Ghidra P0 accepts native PE and explicitly selected raw 6502 targets only |
| ida | `architecture_unsupported` | REA's IDA adapter has no verified MIPS lane |
| hopper | `unsupported_host` / `architecture_unsupported` | not on win32; adapter does not admit MIPS |
| kuna | `not_configured` / `architecture_unsupported` | mips is not admitted yet |

## Conclusion
On this host REA can **identify** the executable (format, architecture, digest) and nothing further: no memory map, inventory, strings or disassembly for a MIPS ELF. This is REA failing closed by design, not a misconfiguration — the same engines are verified working on PE targets (session-1 notes). GOAL.md's expectation that REA supplies "the initial static record, memory map, and binary inventory" is therefore met only for *identity*; the memory map and inventory come from IDA Pro directly (`docs/ANALYSIS/`), per **ADR-0002**.

Re-run `open_binary` + `binary_overview` after any REA upgrade whose changelog mentions a MIPS lane; if either succeeds, supersede ADR-0002.
