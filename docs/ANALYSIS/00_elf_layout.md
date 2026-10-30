# 00 — ELF layout as IDA sees it

_Observed_ = IDA/raw-ELF shows it at the cited address. _Inferred_ = our reading of those observations.

## Summary (observed)

* Processor `r5900l` (Emotion Engine, little-endian), image base `0x00100000`, entry `0x00100008`, image end `0x009acc80`. The ELF has **two PT_LOAD headers but only one with bytes**: PT_LOAD[0] covers `0x00100000..0x009acc80` with `filesz == memsz == 0x8acc80` and flags RWX; PT_LOAD[1] at `0x009acc80` is empty (`heap` marker).
* The section table is minimal: one `main` PROGBITS section (`0x00100000`, `0x6cde80` bytes), an empty `heap` section at `0x009acc80`, `.comment`, `.reginfo`, `.shstrtab`, and an empty `.relmain`. There is **no `.text/.data/.rodata/.bss/.sbss` split and no `.symtab`/`.strtab`** — the binary is fully stripped.
* IDA therefore creates two segments: `main` (`0x00100000..0x007cde80`, the ELF section) and `LOAD` (`0x007cde80..0x009acc80`, the part of PT_LOAD[0] no section covers). Both are class CODE / rwx only because the single ELF segment is RWX; the split below is derived from IDA's analysis, not from headers.
* `.comment` = `MW MIPS C Compiler (2.4.1.01)` / `PlayStation2`: the game code was built with **Metrowerks CodeWarrior for PS2**, not ee-gcc. (CRI middleware objects inside it carry `Append: GCC2096 SCE3020` banners, e.g. `0x007c1ab9`, so those libraries were prebuilt with ee-gcc 2.96 against SCE SDK 3.0.2 — inferred from the banner text.)
* `.reginfo` gp = `0x007d2cf0`; the same value is loaded into `$gp` by crt0 at `0x1001ac`/`0x1001c0`.

## Derived memory map (inferred from IDA analysis + crt0)

| Range | Role | Evidence |
|---|---|---|
| `0x00100000 – ~0x005a1400` | code (14,040 functions, 4.52 MiB of function bytes) | function density per 64 KiB is ~1.0 up to `0x5a0000` then drops to 0.10; last substantive functions are CRI SUD/SFX at `0x5a1158`/`0x59f9e0` (banner xrefs in 03). Three 4-byte "functions" at `0x7cc670` are IDA artefacts inside data. |
| `~0x005a2000 – 0x007cde04` | initialised data / rodata (strings from `0x5ce4a8`, SDK tables, CRI banners up to `0x7cd7c0`) | string list; byte accounting shows 4.09 MiB `is_data` |
| `0x007cde04 – 0x007cde80` | zero padding | file bytes |
| `0x007cde80 – 0x009acc80` | **.bss** (1.87 MiB, zero in file) | crt0 zero-fills exactly `[0x7CDE80, 0x9ACC80)` at `0x100124..0x100194` (byte loop to 16-alignment, then `sq $zero`); named `bss_start` |
| `0x009acc80 – …` | heap | `SetupHeap(0x9ACC80, -1)` at `0x1001d8..0x1001e4` (-1 = "to the stack") |
| `0x01f60000 – 0x02000000` | main thread stack (640 KiB) | `SetupThread(gp, stack=0x1F60000, size=0xA0000, args=0x95C280, root=0x100220)` at `0x1001a4..0x1001c8`, `$sp = $v0` at `0x1001cc` |
| `0x70000000` scratchpad | not referenced by crt0; usage is a Phase 2 question | — |

## Gaps / overlays / stray code

* No overlay mechanism is visible at the ELF level (single static image, no `.relmain` content). Overlays, if any, would be loaded by the game's own file layer (CRI ROFS: `../../rofs_*.c` strings at `0x7c6fe8..0x7c7718`, `cdrom0:\` at `0x5e4e38`) — to be checked in Phase 2, not established here.
* Auto-analysis found **no functions outside the `main` segment** (0), but it did flag 19,008 code items (`0x12af0` bytes) that belong to no function. Spot checks show these are mis-disassembled data (VU microcode / GIF packets rendered as `.word` runs with the occasional decoded instruction, e.g. `syscall 0x400` at `0x5e3240`, `syscall 0x17BE` at `0x5f93b0` — see `ida/logs/syscall_sites.txt` junk list). Treat `is_code` outside functions as untrusted.
* The `LOAD` segment (bss) contains no code or data items of interest; IDA's `is_data` total includes it.

## Generated data

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-21 06:38:58 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

| Item | Value (observed in IDA) |
|---|---|
| Processor module | `r5900l` (IDA `inf_get_procname`) |
| Endianness | little (`inf_is_be`=False) |
| Entry point | `0x00100008` (`inf_get_start_ea`; ELF `e_entry`=0x100008) |
| Image range | `0x00100000` .. `0x009acc80` (`inf_get_min_ea`/`max_ea`) |
| Image base / first PT_LOAD vaddr | `0x00100000` |
| ELF type / machine / flags | 2 (ET_EXEC) / 8 (EM_MIPS) / 0x20924000 |
| ELF file data_985588 | 9096860 bytes |
| `.comment` | `MW MIPS C Compiler (2.4.1.01) | PlayStation2 | ` |
| `.reginfo` | gprmask=0xf7fffffe cprmask=[0x0, 0xffffffff, 0x0, 0x0] **gp=0x7d2cf0** |
| `.symtab` present | False (fully stripped, no ELF symbols) |

### IDA segments (`ida_segment`)

| Name | Start | End | Size | Perm | Class | Bitness |
|---|---|---|---|---|---|---|
| `main` | `0x00100000` | `0x007cde80` | 0x6cde80 (6.80 MiB) | rwx | CODE | 32 |
| `LOAD` | `0x007cde80` | `0x009acc80` | 0x1dee00 (1.87 MiB) | rwx | CODE | 32 |

### ELF program headers (raw file parse)

| # | Type | Offset | Vaddr | Filesz | Memsz | Flags | Align |
|---|---|---|---|---|---|---|---|
| 0 | LOAD | 0x80 | 0x00100000 | 0x8acc80 | 0x8acc80 | 0x7 | 0x80 |
| 1 | LOAD | 0x8acd00 | 0x009acc80 | 0x0 | 0x0 | 0x6 | 0x10 |

### ELF section headers (raw file parse)

| # | Name | Type | Flags | Addr | Offset | Size | Align |
|---|---|---|---|---|---|---|---|
| 0 | `` | NULL | 0x0 | 0x00000000 | 0x0 | 0x0 | 0 |
| 1 | `main` | PROGBITS | 0x7 | 0x00100000 | 0x80 | 0x6cde80 | 128 |
| 2 | `.relmain` | REL | 0x0 | 0x00000000 | 0x8ace9c | 0x0 | 4 |
| 3 | `heap` | PROGBITS | 0x3 | 0x009acc80 | 0x8acd00 | 0x0 | 16 |
| 4 | `.comment` | PROGBITS | 0x0 | 0x00000000 | 0x8acd00 | 0x2b | 1 |
| 5 | `.reginfo` | MIPS_REGINFO | 0x0 | 0x00000000 | 0x8acd2c | 0x18 | 4 |
| 6 | `.shstrtab` | STRTAB | 0x0 | 0x00000000 | 0x8acd44 | 0x40 | 1 |

### Byte accounting over `0x00100000`..`0x009acc80` (IDA item flags)

| Kind | Bytes | MiB |
|---|---|---|
| code (is_code) | 0x493390 | 4.58 |
|   of which code outside any function | 0x3670 | 0.01 |
| data (is_data) | 0x3fb1e2 | 3.98 |
| align | 0x0 | 0.00 |
| unknown/unexplored | 0x0 | 0.00 |
| sum of function sizes (all chunks) | 0x49224c | 4.57 |

Zero-initialised tail: every byte from `0x007cde04` to `0x009acc80` is zero in the file (0x1dee7c bytes = 1.87 MiB); PT_LOAD[0] has filesz == memsz, so `.bss` was emitted as file bytes rather than NOBITS.

Functions outside the first segment (`main`): 0. Code items outside any function: 3474 items / 0x3670 bytes.
<!-- GENERATED:END -->
