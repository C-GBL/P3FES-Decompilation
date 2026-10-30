# 05 — FLIRT signature pass

_Narrative (which packs, verdict on match quality) is hand-written below the generated block._

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-18 18:43:05 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

Signature directory: `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips`; files applied this run (in order): `PS2SDK_3.0.3.sig`, `PS2SDK_3.0.2.sig`, `PS2SDK_3.0.0.sig`, `PS2SDK_2.4.2.sig`, `PS2SDK_1.0.0.sig`, `libsn.sig`, `MetrowerksCodewarrior.sig`.

### Signatures known to the database (`ida_funcs.get_idasgn_qty/get_idasgn_desc`)

| # | Signature | Declared library | Matches |
|---|---|---|---|
| 0 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\PS2SDK_3.0.3.sig` |  | 1750 |
| 1 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\PS2SDK_3.0.2.sig` |  | 96 |
| 2 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\PS2SDK_3.0.0.sig` |  | 217 |
| 3 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\PS2SDK_2.4.2.sig` |  | 12 |
| 4 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\PS2SDK_1.0.0.sig` |  | 2 |
| 5 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\libsn.sig` |  | 168 |
| 6 | `C:\Users\Ash\AppData\Roaming\Hex-Rays\IDA Pro\sig\mips\MetrowerksCodewarrior.sig` |  | 139 |

Functions newly named by this run's signature pass: **1348**; functions carrying FUNC_LIB (any run): **1424**. These names are *derived* and tagged `flirt` in `symbols/p3fes.sym`; manual names (`names_manual.txt`) were applied before the signatures and win on conflict.

### Spot check (first 12 FLIRT-named functions with independent evidence)

| Address | FLIRT name | Evidence |
|---|---|---|
| `0x00198010` | `SSL_library_init` | string 0x678798 `CDV:data.cvm`; string 0x6787a8 `CDV:bgm.cvm` |
| `0x0049ff00` | `sceLibgcc32GetErxEntries` | string 0x77de80 `h` |
| `0x004c72e0` | `_dispRefImageField_0` | string 0x523ac8 ```; string 0x524270 `-8` |
| `0x004f8eb0` | `sceGsResetGraph` | syscall(s): `SetGsCrt` |
| `0x004f90b8` | `checkModelVersion` | string 0x7bd070 `rom0:ROMVER` |
| `0x004f9168` | `sceGsSetDefDispEnv` | string 0x7bd080 `sceGsDefDispEnv:Not support displaymode for 0x%x!! ` |
| `0x004f9850` | `sceGsPutDrawEnv` | string 0x7bd0b8 `sceGsPutDrawEnv: DMA Ch.2 does not terminate  ` |
| `0x004f99d0` | `sceGsSyncPath` | string 0x7bd0e8 `sceGsSyncPath: DMA Ch.1 does not terminate  `; string 0x7bd1c8 `sceGsSyncPath: DMA Ch.2 does not terminate  ` |
| `0x004f9e28` | `sceGsExecStoreImage` | string 0x7bd280 `sceGsExecStoreImage: DMA Ch.1 does not terminate  `; string 0x7bd2b8 `sceGsExecStoreImage: GS does not terminate  ` |
| `0x004fa798` | `WaitDma` | string 0x7bd450 `libdma: sync timeout ` |
| `0x004fa808` | `WatchDma` | string 0x7bd450 `libdma: sync timeout ` |
| `0x004fb168` | `_getAllRefs` | string 0x7bd4c0 `(a) invalid motion_type(%d)-0`; string 0x7bd4e0 `(b) invalid motion_type(%d)-1` |
<!-- GENERATED:END -->

## Narrative and verdict (hand-written, 2026-10-18)

**Pack.** Amorri40/pool7 community set (ASSEMBLERgames 2018, recovered from Wayback raw captures; provenance in `docs/TOOLS.md`, authorisation in ADR-0007). Applied in order: `PS2SDK_3.0.3`, `3.0.2`, `3.0.0`, `2.4.2`, `1.0.0`, `libsn`, `MetrowerksCodewarrior`. Withheld: `PS2SDK_2.0.0` (74 % x86 host-toolchain patterns). Not applied: IDA's PS1 `psyq.sig` (137 matches in a dry run, but PS1-era names on PS2 code are more likely to mislead than help).

**Raw result (generated block above).** 1,348 functions newly named, 1,424 carrying `FUNC_LIB`; functions 14,040 → 14,225 because signature application defined 185 new functions. `SDK 3.0.3` alone matched 1,750 patterns — the game's SDK 3.1.0 libraries are close enough to 3.0.3 for the stable surface (libkernel, libgraph, libdma, libpad, libmc2, libcdvd, libsif*).

**Audit (`tools/ours/ida/flirt_audit.py`, logs `ida/logs/flirt_audit*.json`).** The pack bundles x86 host libraries (OpenSSL, bfd, Tcl/Tk…) whose tiny getters collide with unrelated R5900 code. Stripped, with the rule that caught each:
| Rule | Count | Examples |
|---|---:|---|
| `host-lib` (OpenSSL/bfd/Tcl/Tk/… prefixes) | 35 functions + 3 labels | `SSL_library_init` @ `0x198010` (actually the game's IRX-loader neighbour referencing `CDV:data.cvm`), `X509_STORE_CTX_get_depth` ×3, `EVP_CIPHER_iv_length` ×3 |
| `unknown_libname` (nameless match placeholders) | 201 | `unknown_libname_502…526` across the G3 renderer band; 9 of them were pseudo-functions FLIRT created in the data band (renamed back to `sub_*`; the bogus function objects remain until Phase 2 defines that data) |
| `gcc-mangled` below the SDK band | 3 | `_ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv` @ `0x4AE8F0`, `basic_streambuf::eback` ×2 — libstdc++ getters in a Metrowerks binary whose GCC-built parts (CRI) are C |

**Final state.** `symbols/p3fes.sym`: 14,749 records (F 14,225 · D 8 · L 516); **1,184 FLIRT-derived names** (tagged `flirt`), **682 `sce*`/`_sce*` symbols** including our 159 syscall wrappers. By band: SDK `0x4F9000–0x51E000` 773 · MW runtime/libc/CRI `0x51E000–0x5A1400` 400 · transition `0x4E7000–0x4F9000` 1 · game code 10 · data 0. The 10 game-band survivors are Metrowerks C++ runtime (`name__C9type_info` ×3, `HandleUnexpected__FP12ThrowContext…`), four `sceLibgcc32GetErxEntries` ERX stubs and two `_dispRefImage*` — kept as low-confidence derived names, not verified.

**Spot check** (generated table above): `sceGsResetGraph` carries the `SetGsCrt` syscall; `sceGsSetDefDispEnv`, `sceGsPutDrawEnv`, `sceGsSyncPath`, `sceGsExecStoreImage` each reference their own libgraph error string; `WaitDma`/`WatchDma` reference `libdma: sync timeout`. No contradiction found among sampled SDK-band names.

**Verdict for ADR-0007 — better: yes.** 1,184 library names in ~15 s with string- and syscall-confirmed anchors versus weeks of manual prologue matching; the false-positive classes are mechanical and now stripped by a committed, re-runnable script. FLIRT names stay *derived* (`flirt` tag); ELF symbols (none exist) and manual names win on conflict; promotion to verified happens per function in Phase 2/5 with evidence. `ida/p3fes.pre-flirt.i64` is the pre-pass backup (gitignored) until the hint import lands.
