# Community reverse-engineering projects for Persona 3 FES — evaluation

_Evaluated 2026-10-18. Read-only review of three GitHub projects (plus the upstreams they credit). Clones live under the gitignored `tools/third_party/_community-eval/` (`git clone --depth 50`); nothing from them has been copied into any other path. No scripts, build systems, or binaries from these repos were run. Adoption of any asset is the lead's decision and must respect each license._

Our target: `SLUS_216.21`, SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`, SHA-1 `3929cd7c02be944f25ec6b924e5f1eab9bc5e9cb` (`docs/INVENTORY.md`). Our route: static recompilation + HLE runtime, IDA as disassembly surface (`GOAL.md` "Strategy").

Legend: **[obs]** observed in a cloned file / API response (path or hash cited) · **[claim]** the project's own statement, not verified by us · **[inf]** our inference.

---

## 1. `snaku/Persona3-FES-Decompilation` — matching decompilation (splat + MWCCPS2/ee-gcc)

Clone: `tools/third_party/_community-eval/snaku/` at `59d284ee21fe166bd46252e38e1a08874c4a1a66`.

### Identity & health [obs, `gh api repos/snaku/Persona3-FES-Decompilation`, 2026-10-18]
| | |
|---|---|
| Default branch | `main` |
| Created / last push | 2025-12-13 / 2026-09-04 (`59d284e`, "Implement 'btlUnitLookAtUpdateAll'") |
| Commits | 923 (GitHub `Link: … page=923` on `commits?per_page=1`) |
| Contributors | `snaku` 913, `tge-was-taken` (TGE) 10 |
| Stars / forks | 68 / 3 |
| Issues / PRs | 4 total: #1 closed (Discord pointer), #2 open ("Very great!", noise), #3 merged 2026-07-29 (TGE: splat/objdiff/ninja build system), **#4 open since 2026-10-16** (TGE: "Lots of symbols, IDA & Ghidra helper scripts and structs", +12,805/−4,684, 23 files, head `c45ffa45d517582148b474631f1d1772d8b160ff` on `tge-was-taken/Persona3-FES-Decompilation`) |
| Status | **[inf] stalled on the maintainer side** (no push in 6 weeks, an unreviewed 12k-line PR), but with an active, high-quality contributor (TGE = author of Amicitia / Atlus-Script-Tools). Not archived. |

### License
**No license file anywhere in the tree [obs: `ls` of repo root; `gh api … .license` = `null`]. All rights reserved by default.** The TGE fork is likewise unlicensed. Treat all code *and* the symbol file as not reusable; reading facts is fine, copying text is not.

### Target binary
- `config/SLUS_216.21/checksum.sha1` [obs]: `3929cd7c02be944f25ec6b924e5f1eab9bc5e9cb  SLUS_216.21` → **exactly our ELF's SHA-1** (`docs/INVENTORY.md`).
- `config/SLUS_216.21/splat.yaml` [obs]: `sha1: a3289987032d81209ac0246f58c2bf19e23d5a89` on `target_path: main.bin` — that is the extracted loadable segment, not the ELF [inf]; `vram: 0x100000`, `gp_value: 0x7D2CF0`, `bss_size: 0x1DEE00`, `.data` at file 0x4A9D3C (vram 0x5A9D3C), `.rodata` at 0x6B5180, segment end 0x6CDE80.

### Approach & progress
- splat-based matching decomp with objdiff + ninja (`configure.py`, PR #3). Compilers [obs `configure.py` L90-116]: game code **MWCCPS2 3.0-011126 `-O2 -gccincludes`**; RenderWare 3.7 archives `mwcps2-3.0.1b119-040914 -O4,p`; Sony SDK libs `ee-gcc2.9-991111 -O2 -G0`; libgcc/libhttps/CRI `ee-gcc2.96`. (Same compiler family the Persona 4 decomp uses — see §4.)
- Progress [obs]: 126 `.c` files under `src/`, ~1,196 function-definition-shaped lines (rough grep); their own count via p3fes-recompiled's `status.toml` is 986 C functions at `59d284e`. `INCLUDE_ASM` count = 0 (splat is configured `create_c_files: false`; unimplemented functions stay as `asm` segments). ≈ 7 % of 14.5k functions. The game is not "built and booting" from source in the decomp sense; this is a per-function matching project.
- `docs/prefixes.md` [obs]: maps Atlus developer prefixes (`k_` Kosaka field, `h_` Tohyama chief dev, `mt` Takano event, `d_` Yajima, `nm` Miwa, `y_` Miyashita) and functional prefixes (`btl`, `dat`, `scr`, `mdl`, `fcl`, `op_`, `ed_`…) to original source file names recovered from the binary.

### Symbol / knowledge assets
| Asset | Path | Size | Content | Naming quality | License |
|---|---|---|---|---|---|
| **Symbol map** | `config/SLUS_216.21/symbol_addrs.txt` | 730,893 B, 15,850 lines | **14,702 symbols** (14,567 `type:func`, 135 data), range 0x00100008–0x0095B658, grouped under 574 `// module` comments | 3,060 fully descriptive names (`H_Cdvd_Read`, `datGetPartyId`, `btlActionInitStateEndure`, `sceGsSyncV`); 11,642 are module-prefixed placeholders with an address suffix (`h_cdvd_00101100`, `libadxe_adx_dcd_0043976x`). 398 `sce*`, 162 RenderWare `Rw/Rp/Rt*`. Original Atlus names where strings leak them; sce/Rw/CRI names are canonical library names. | none (all rights reserved) |
| **PR #4 symbol map** (TGE, unmerged) | `pr4:config/SLUS_216.21/symbol_addrs.txt` (fetched as local branch `pr4` in the clone) | 17,151 lines | **16,004 symbols** (14,708 funcs); **8,776 descriptive vs 7,228 placeholders** — nearly triples the named count | plus `include/lib/rw/rw.h` (4,393 lines, RenderWare 3.7 structs), `include/sce/sce.h` (633 lines), `scripts/ida/export_from_ida.py` / `import_to_ida.py`, `scripts/ghidra/ImportP3FESDecompSymbols.py` | none |
| **Segment map** | `config/SLUS_216.21/splat.yaml` (604 lines) | — | ~250 translation units with file offsets: game TUs by developer, then `lib/rw/*` (librwcore, librpworld, librpcollis, librphanim, librpmatfx, librpmorph, librptoon, librpspline, librt2d, librtanim, p2* PS2 pipelines), `lib/sce/*` (libgraph, libdma, libmpeg, libipu, libkernl, libcdvd, libpad, libsdr, libmc2, libdbc, libspu2m, libsk, libc, libm), `lib/gcc/*`, `lib/sce/libhttps`, `lib/cri/libadxe`, `lib/cri/librofs`, `lib/cri/libmwsfde` (Sofdec) | file names are the SDK/RW/CRI object names | none |
| **Struct headers** | `include/**` (≈100 files) | small | `sce/eekernel.h`, `libcdvd.h`, `libmc2.h`, `libpad.h`, `sifrpc.h`; game structs (`datCalendar.h`, `g_flags.h`, `itfMesManager.h`, `Kosaka/*.h`, `Battle/*.h`) | Atlus-style | none |
| Misc | `BGM.txt` | 1.5 KB | BGM.CVM track listing | — | none |
| IDA/Ghidra DBs | **none** in repo [obs] | | | | |
| Format specs (BF/BMD/PAC/TMX…) | **none** in repo [obs]; TGE's Amicitia covers these separately | | | | |

### Reusability verdict
- (a) **Consult: yes, high value.** Function boundaries and addresses, module→developer attribution, library layout, and the compiler identification are facts about *our exact binary*. We re-derive and name in IDA ourselves (our `symbols/p3fes.sym` already has 14,040 functions; theirs has 14,567 — the ~500 delta is worth cross-checking in IDA).
- (b) **Adopt code/text: no** — unlicensed.
- Strategy-relevant facts: no overlays; game code is **Metrowerks CodeWarrior**, not ee-gcc (affects any FLIRT/signature plan and calling-convention assumptions); engine is **RenderWare 3.7** (VU1 microcode is largely RenderWare's PS2 pipelines — `p2allim3d`, `p2altmdl`, `p2dep`…); CRI Sofdec drives the IPU directly.

---

## 2. `poopoocacacacaca/p3fes-recompiled` — PS2Recomp-based static recomp (GPL-3.0)

Clone: `tools/third_party/_community-eval/p3fes-recompiled/` at `0a8a9333d1e89cf947e2c099843a2b16cd8fb5e2`.

### Identity & health [obs, `gh api`]
| | |
|---|---|
| Default branch | `main` |
| Created / last push | 2026-10-14 15:35 UTC / 2026-10-14 16:09 UTC — **all 35 commits within ~14 hours of one day** (first `83fc57b` 03:50 +0200, last `0a8a933` 18:09 +0200) |
| Contributors | one (`poopoocacacacaca`; one commit as `poo`) |
| Stars / forks / issues | 2 / 0 / 0 (one self-merged PR #1) |
| Status | **[inf] a one-day code drop; too new to call active or stalled.** README describes itself as "AI-Powered"; commit `0ad3958` merges from `/home/claude/p3fes-port` [obs `git log`]. |

### License
`LICENSE` = **GPL-3.0** (GitHub SPDX `GPL-3.0`; file header "GNU General Public License Version 3"). Inherited from PS2Recomp (GPL-3.0), PCSX2 subset in `third_party/pcsx2/` (`COPYING.GPLv3`), god-of-war-recomp (GPL-3.0). `p3fes/README.md` L34-35 acknowledges copyleft obligations. 12 MB `ps2xAnalyzer/include/ps2recomp/sce_symbol_database_data.h` ("Generated from sce-symbol-scanner symboldb resources") embeds hashes/relocations of Sony SDK objects — provenance/licensing of that data is unclear [inf].

### Target binary
- README L22-26 [obs]: NTSC-U `SLUS-21621`, Redump disc 4125, **`SLUS_216.21` SHA-1 `7ca061aac239e53e86bcd4c0ce8e19e987d8a75f`** — **does not match our SHA-1 `3929cd7c…`**, nor snaku's `checksum.sha1` (which matches ours).
- However their function map is byte-for-byte derived from snaku's symbols: `p3fes/scripts/make_map.py` L1-3 ("from the P3 FES decomp's symbol_addrs.txt plus JAL-target scanning"), `TEXT_END = 0x100000 + 0x4A9D3C` (= snaku's `.data` offset), and **14,532 of 14,628 rows in `p3fes/p3fes_map.csv` are identical name+address pairs with snaku's `symbol_addrs.txt`** [obs, `comm -12`]. The remaining ~100 are JAL-scan additions (e.g. `libiberty_cplus_dem_00558108`).
- [inf] Either their README hash is for a different pressing/patched ELF with identical code layout, or it is simply wrong. fes-pc-recomp independently notes a circulating "deinterlaced" image whose executable differs from the Redump dump in ~830 bytes (`fes-pc-recomp/docs/findings.md` L10) — a plausible source of a second SHA-1. **Unresolved**: redump.org refused connections during this evaluation; the lead should check disc 4125's ELF SHA-1 directly. Our own hash is the authority regardless.

### Approach & progress
- Engine: **PS2Recomp** (ran-j, imported at upstream `2c5fbb9`, commit `eb552f8`) + runtime work merged from **KIexster/god-of-war-recomp** (SPU2, SIO2, IOP interpreter, VU1) + PCSX2's GS as a shared library (`third_party/pcsx2-gs`, "WIP") + PCSX2's IPU. R3000A interpreter runs the game's **original IRX modules**. ~94k lines of C++ outside `third_party/` [obs `wc -l`].
- Config [obs `p3fes/p3fes.toml`]: 14,628-function map, `keep_guest` for `sceIpu*/sceMpeg*` (Sofdec drives the IPU itself), `stubs` binding ~205 `sceGs*/sceDma*/sceCd*/pad/mc` functions to HLE at explicit addresses (e.g. `sceGsSetDefDispEnv@0x004F9168`, `sceGsSyncV@0x004F9938`, `sceDmaSend@0x004FAC20`). `p3fes/status/status.toml` [obs]: `functions = 14628`, `recompiled = 14423`, `hle = 205`; README: "3,910 functions / 453,264 indirect-jump fallback entries, 14 recovered jump tables".
- Progress **[claim, README "Status"]**: boots from CVMs, memcard + pad detected, opening movie with sound via PCSX2 GS, title screen, Journey/Answer menu (background corrupted), ~0.75× speed on a 2-core VM. Field/Tartarus/battle not reached. **No screenshots or recordings in the repo** (only `p3fes/branding/logo-*.png`); the status SVG is generated from hand-edited `status.toml`. Not verified by us.
- `p3fes/names/p4_names.csv` + `scripts/p4_names.py`: names transferred from the Persona 4 decomp by aligning runs of identical function sizes ("309 anchored", commit `137cdaa`) — an interesting technique [inf: useful idea, moderate confidence names].

### Symbol / knowledge assets
| Asset | Path | Size | Content | Quality | License |
|---|---|---|---|---|---|
| Function map | `p3fes/p3fes_map.csv` | 692,500 B, 14,628 rows (`Name,Start,End,Size`) | derived from snaku + JAL scan + P4 overlay | same as snaku (unlicensed origin!) + 67 `func_`-style rows | **GPL-3.0 repo, but content is a derivative of snaku's unlicensed symbol file** [inf] — doubly encumbered |
| HLE binding list | `p3fes/p3fes.toml` `stubs`/`keep_guest` | 80 KB | address-anchored list of SDK functions PS2Recomp stubs | canonical `sce*` | GPL-3.0 |
| Extra entry points | `p3fes/extra_starts.txt` | 1.1 KB | code/data starts the analyzer missed | — | GPL-3.0 |
| P4→P3 name transfer | `p3fes/names/p4_names.csv`, `scripts/p4_names.py` | 39 KB | 309 anchored names | medium | GPL-3.0 (P4 source unlicensed) |
| SDK symbol DB | `ps2xAnalyzer/include/ps2recomp/sce_symbol_database_data.h` | 12 MB | per-SDK-version function hashes + relocations for `crt0`, libs… | — | unclear |
| IDA/Ghidra DBs, format specs | none | | | | |

### Reusability verdict
- (a) **Consult: yes** for the HLE stub list (which `sce*` entry points at which addresses a PS2Recomp port needed to bind — directly maps onto our Phase 3 syscall/SDK HLE table), the `keep_guest` lesson (Sofdec+libmpeg must stay guest code on an emulated IPU), and the runtime env-var/debug surface as a design reference.
- (b) **Adopt code: no** for an MIT/Apache from-scratch port — GPL-3.0 (and the map inherits snaku's no-license). If the lead ever relaxes to GPL, this is the closest existing runtime to our design.
- (c) Its map adds nothing over snaku except JAL-scan stragglers.

---

## 3. `Virtual-AK/fes-pc-recomp` — data-format tooling + ps2-web-recomp experiments (MIT)

Clone: `tools/third_party/_community-eval/fes-pc-recomp/` at `6b3a905a1e44a994c94682582d2c04cbf10c7c4e`.

### Identity & health [obs]
| | |
|---|---|
| Default branch | `main` |
| Created / last push | 2026-10-15 00:48 UTC (first commit `f6dcc42` 2026-10-14 −0700) / 2026-10-18 21:21 UTC |
| Commits | 31, **all "Add files via upload"** via the GitHub web UI (one "Delete ps2-native-tools directory", one "Create README.md") |
| Contributors | one (`VirtualAK`) |
| Stars / forks / issues | 1 / 0 / 0 |
| Status | **active this week**; README names itself `ps2-native-tools`; LICENSE copyright "ps2-native-tools contributors". Docs reference the maintainer working with Claude in chat (`docs/playtest-plan.md` L5) [obs]. |

### License
`LICENSE` = **MIT** (SPDX `MIT`) [obs]. Covers the Python tools and docs. **No game-code recompilation lives in this repo**; the recompiler they use is `snuri00/ps2-web-recomp` (MIT, 1,068 ★, 94 forks, created 2026-10-08, pushed 2026-10-18 [obs `gh api`]).

### Target binary
- NTSC-U `SLUS-21621`/`SLUS_216.21` throughout (`docs/findings.md` L1, L8; `docs/formats.md`; `tools/p3fes_bf.py` L7-14). **No ELF hash is published** [obs: grep for 40/64-hex strings finds none; `tools/p3fes_inspect.py` computes SHA-1/MD5 at run time, L190-371]. States it matches "the Redump entry" [claim]. Reports the ELF as one loadable segment 0x00100000–0x009ACC80, 9,096,320 B, entry 0x00100008, stripped (`docs/findings.md` L9-10) — consistent with our 9,096,860-byte ELF [inf].
- Noteworthy [obs `docs/findings.md` L10]: "The community 'deinterlaced' image differs from the plain dump in about 830 bytes of the executable plus 42 re-encoded .SFD videos" — see §2's hash discrepancy.

### Approach & progress
- Phase 0 = **pure-Python format tooling** (Python ≥ 3.8, no deps): `tools/p3fes_{cvm,unpack,tmx,audio,bed,text,bmd,bf,rmd,gltf,field,fx,formats,vu,iop,iopimg,pacing,filecalls,exe_scan,patch}.py` (~40 tools, ~800 KB) + 115 tests (`tests/`). Also ~25 `ps2run_*/ps2web_*/ps2gpu_*_patch.py` scripts that **patch the ps2-web-recomp runtime source** (traces, VIF V2 unpack fix, VU branch-delay fix, MSKPATH3/PATH3 arbitration fix, texel-centre fixes) [obs README L92-120].
- Phase 1 **[claim, `docs/phase1-summary.md`, `docs/playtest-plan.md`]**: ps2-web-recomp's `eerecomp` translated `SLUS_216.21` in 1.7 s (1,187,301 instructions, 9,446 functions, 297 units, 0 rejected); built under WSL2; headless runs of 60,000 frames reached **publisher logo → opening video → title → main menu → New Game flow → name entry → second movie → first 3D dormitory scenes (dialogue, walking, camera, next morning) → cut to the city street**, with 0 unhandled syscalls, 0 missing IOP functions, all 14 IRX loaded on the R3000 interpreter. Faults F1-F3 (floor noise, dark rooms, menu corruption) attributed to the runtime ignoring **VIF1 `MSKPATH3`** and fixed by `tools/ps2run_fix_path3_mask.py`; **sound not implemented**; speed never measured. No screenshots in repo (policy: pictures stay local). Not verified by us.

### Symbol / knowledge assets (all MIT)
| Asset | Path | Size | Content | Quality |
|---|---|---|---|---|
| **Format spec** | `docs/formats.md` | 160 KB | CVM/ROFS layout; PAC/PAK/BIN/CPK containers (256-byte name+size records); TMX header; BMD `MSG1`; AFS; ADX; SFD (MPEG-2, 640×368/640×448/512×448); **RMD (RenderWare clump) geometry, PS2 native textures, skeleton/skin/animation**; `.SE` Sony sound banks (`.sq`/`.hd`); `.BED4` effect trees; `.BF` `FLW0` sections/opcodes; field `.FBN/.HBN/.RWS` tables; plus the ELF scans below | careful, evidence-tagged ("verified"/"partly known"/"not understood yet") |
| **ELF facts** | `docs/formats.md` ~L545-620, `docs/phase1-*.md` | — | VU0 macro mode: 5,938 COP2 instrs in 716 sites; **VU1 microcode as data at 0x5A0000–0x77xxxx: 383 blocks, 421 VIF MPG uploads → 181 programs (172 distinct), 676,888 B**, many 2 KiB pieces loaded at VU addresses 0x000–0x500; file layer: central request fn `0x00100D80` (218 callers, logs `REQ CDVD %s`, 868-byte entries, list head 0x7E0380) over CRI `cvFs*` at 0x555B10–0x5577B8 (device vtable: open +16, read-req +32; 40-handle table at 0x997518); VBlank handler `0x004D47F0` registered at `0x004D6470`, DMA-end handlers `0x004D4350`; sync wait `0x005035F0/0x00503680` used only by `sceGsSyncV@0x004F9938`; 129 syscall numbers used; 14 IRX by name; `IOPRP310.IMG` = 17 Sony modules, needs intrman/dmacman/heaplib/secrman/vblank from ROM | address-level, checkable in IDA |
| **Script function table** | `docs/script-functions.md`, `tools/script_names.txt` | 10 KB + 5.6 KB | BF `COMM n` table: **502 × 8-byte records at 0x7B92B0**, 213 used, grouped by Atlus source file; guessed roles marked `?` | medium; hypotheses marked |
| Text codes | `docs/text-codes.md` | 2.7 KB | BMD control codes | |
| IDA/Ghidra DBs, symbol maps | **none** (they have 9,446 function starts inside the recompiler output, not published) | | | |

### Reusability verdict
- (a) **Consult: yes** — the VU1 microcode inventory, file-layer addresses, frame-pacing findings and the COMM table address are exactly our Phase 2 questions, pre-answered with addresses we can verify in IDA.
- (b) **Adopt code: yes, license-compatible (MIT).** Candidates: `tools/p3fes_formats.py`/`p3fes_tmx.py`/`p3fes_bmd.py`/`p3fes_bf.py`/`p3fes_rmd.py` as a reference or port into `runtime/formats/` (Phase 1), with attribution. Quality caveat [inf]: single-author, web-uploaded, Python-only; verify against our extracted files before trusting any parser.
- Their runtime patches target ps2-web-recomp's source and are not directly applicable to our C++/D3D11 runtime, but each one documents a real PS2 behaviour the game depends on (MSKPATH3 arbitration, VIF V2 unpack zero-fill, VU integer-branch delay reading the *old* register) — port the *facts*, not the patches.

---

## 4. Other finds (not cloned)

| Resource | What | License | Why it matters |
|---|---|---|---|
| [snuri00/ps2-web-recomp](https://github.com/snuri00/ps2-web-recomp) | Static recomp → C++/WASM + native `ps2run` (SDL2 + wgpu-native/Vulkan); HLE EE kernel, R3000 interpreter for IRX, VU1 compiled with pipeline/flag timing, GS in WebGPU compute shaders, SPU2, IPU. Claims GT4 and GoW II playable; fes-pc-recomp reports P3FES reaching 3D field scenes on it (§3) [claim]. 1,068 ★, created 2026-10-08. | **MIT** (Play! MPEG VLC tables BSD-2) | **The only MIT-licensed PS2 recompiler+runtime that reportedly runs our game.** Directly adoptable as a reference implementation or a base. |
| [ran-j/PS2Recomp](https://github.com/ran-j/PS2Recomp) | Recompiler + runtime + ps2xIOP; 3,580 ★ | GPL-3.0 | Base of §2; license-incompatible with MIT/Apache. |
| [KIexster/god-of-war-recomp](https://github.com/KIexster/god-of-war-recomp) | PS2Recomp port with SPU2/SIO2/IOP/VU1 work | GPL-3.0 | Same. |
| [Raikaru/Persona4-Decompilation](https://github.com/Raikaru/Persona4-Decompilation) | Matching decomp of P4 `SLUS_217.82` (MWCCPS2 3.0.1 b210 game / b119 RenderWare); `config/symbol_addrs.txt` 542 KB, `symbol_data_addrs.txt` 131 KB, `sdk_symbol_provenance.txt`; 43 ★, pushed 2026-10-17 | **none** | Same engine generation and link order as P3FES; names transferable by size-run alignment (§2 technique). Consult only. |
| [tge-was-taken/Amicitia](https://github.com/tge-was-taken/Amicitia) (= TGEnigma) | Editor for Atlus formats (PAC/TMX/SPR/RMD/BF/BMD…), last push 2024-03 | **none** | Already in `tools/third_party/Amicitia`; format knowledge, no license for code reuse. |
| [Amicitia wiki — TMX](https://amicitia.miraheze.org/wiki/TMX), [SPR](https://amicitia.miraheze.org/wiki/SPR) | Struct-level TMX/SPR specs | wiki text | Cross-check for `runtime/formats/`. |
| [Data Crystal — P3/P4 TMX](https://datacrystal.tcrf.net/wiki/Persona_3_and_4:TMX), [BMD](https://datacrystal.tcrf.net/wiki/Persona_3_and_4:BMD_(File_Format)), [ROM map](https://datacrystal.tcrf.net/wiki/Persona_3_and_4:ROM_map) | Format tables + ROM map | wiki (CC) | Secondary source. |
| [ShrineFox — AtlusScriptCompiler decompile docs](https://docs.shrinefox.com/flowscript/atlusscriptcompiler/run-via-commandline/decompile) | P3FES library/encoding for BF decompilation; notes function-signature offsets are RE'd from the ELF | docs | Pairs with the COMM table at 0x7B92B0 (§3). Tool already in `tools/third_party/Atlus-Script-Tools`. |
| GitHub search `SLUS_216.21` / "Persona 3 FES decomp" | Only snaku surfaced; **no splat project for original P3 `SLUS_213.39` found**, no published IDA/Ghidra DB | — | [obs `gh api search/repositories`] |

---

## 5. Comparison

| | snaku/Persona3-FES-Decompilation | poopoocacacacaca/p3fes-recompiled | Virtual-AK/fes-pc-recomp |
|---|---|---|---|
| **License** | none (all rights reserved) | GPL-3.0 (map derived from unlicensed snaku data) | MIT |
| **Target** | `SLUS_216.21`, SHA-1 **matches ours** | `SLUS_216.21`, published SHA-1 **differs** (`7ca061aa…`); layout identical | `SLUS_216.21`, no hash published |
| **Approach** | matching decomp (splat, MWCCPS2 + ee-gcc, objdiff) | static recomp: PS2Recomp + GoW-recomp runtime + PCSX2 GS/IPU, IRX on R3000 interpreter | data tooling (Python) + experiments on ps2-web-recomp (MIT recompiler) |
| **Progress** | ~1k of 14.5k functions matched; no runnable output by design | [claim] boots, FMV with sound, title, menu (corrupt bg), 0.75× speed | [claim] on ps2-web-recomp: boots → New Game → dorm 3D scenes, no sound; formats ~85 % documented |
| **Symbol assets** | 14,702 syms (3,060 named); PR #4 → 16,004 (8,776 named) + RW/SCE headers + IDA/Ghidra scripts | 14,628-row map (= snaku + JAL scan + 309 P4 names); 205 HLE stub bindings | no symbol map; address-level findings (VU1 inventory, file layer, pacing, COMM table); 160 KB format spec |
| **Verdict** | (a) consult heavily; (b) no | (a) consult stub list / keep_guest; (b) no (GPL) | (a) consult; (b) **adoptable (MIT)** with verification |

## 6. Strategy impact

Nothing here invalidates `GOAL.md`'s route; two things sharpen it. First, **the route is now demonstrated on this exact game by two independent efforts [claim]**: a GPL PS2Recomp build reaches the title/menu, and an MIT ps2-web-recomp build reportedly reaches the dormitory 3D scenes — both running the original IRX modules on an R3000 interpreter and treating VU1 microcode as data to be compiled/interpreted, which matches our plan (VU1 interpreter first). We should expect the same first obstacles they hit: Sofdec must keep driving a real IPU model (`keep_guest`), VIF1 `MSKPATH3` arbitration must be honoured, VU integer-branch delay semantics matter, and sound is the long pole (9 IOP sound modules; running them needs intrman/dmacman/heaplib/secrman/vblank + an SPU2 model). Second, the binary facts converge: no overlays or compressed/encrypted code (one loadable segment, CVMs are plain ISO — consistent with `docs/INVENTORY.md`), game code built with **Metrowerks CodeWarrior for PS2 3.0** (not ee-gcc, so EE-gcc FLIRT signatures will only hit SDK/CRI libs), and the engine is **RenderWare 3.7** — ~170 distinct VU1 programs, many variants of a few RenderWare pipeline templates, which makes later HLE of specific microprograms more tractable than a bespoke engine would. The remaining decision is less "can it work" than "how much of ps2-web-recomp (MIT) to build on versus write ourselves", and whether to submit cross-checks to snaku's PR #4 rather than duplicate 8.7k names of naming work we may legally only *consult*.

## 7. Lead decisions

1. **Resolve the ELF hash discrepancy**: fetch Redump disc 4125's `SLUS_216.21` SHA-1 and record which of `3929cd7c…` (ours = snaku) / `7ca061aa…` (p3fes-recompiled) is Redump; note fes-pc-recomp's "~830-byte deinterlaced ELF variant". Our hash stays the authority either way.
2. **ps2-web-recomp (MIT)**: decide between (i) reference-only, (ii) borrow specific components (VU1 compiler/timing model, GS rasterization rules, IPU) with attribution, or (iii) build our runtime on it. This is the single largest schedule lever. Requires reading its code (not done here) before deciding.
3. **snaku symbols**: consult-only policy confirmed (no license). Decide whether to (a) cross-check our IDA function list against their 14,567 starts and PR #4's 16,004 and record disagreements as `docs/ANALYSIS` items, and (b) contact snaku/TGE about licensing or contributing — their PR #4 IDA export/import scripts solve the same symbol round-trip problem as `tools/ours/ida/export_symbols.py`.
4. **fes-pc-recomp (MIT)**: approve consulting its format spec and ELF findings now; decide per-parser whether to port its Python into `runtime/formats/` or use only as a test oracle. Verify each claim at the cited address in IDA before it enters `docs/ANALYSIS`.
5. **Persona 4 decomp**: consult-only; consider reproducing the size-run name-transfer technique in `tools/ours/` against our own IDA export (facts only, no text copied).
6. **Toolchain note for Phase 2/3**: plan FLIRT/signature work for MWCCPS2-compiled game code and ee-gcc-compiled libs separately; prioritise RenderWare 3.7 PS2 pipeline knowledge for the VU1 plan.
