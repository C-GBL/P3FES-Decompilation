# PCSX2 2.8.2 as the Phase 4 reference oracle

_Status: brought up 2026-10-18 on Windows 11 (PowerShell 5.1, Python 3.14). Everything marked **observed** was read from `tools/third_party/pcsx2/logs/emulog.txt`, PINE replies, or the extracted save state of that session; **inferred** is our reading of it. Logs of the runs are kept (gitignored) under `extracted/_pcsx2/logs/`. BIOS files are referred to by file name only; nothing under `tools/third_party/pcsx2/` or `extracted/` is ever committed._

## 1. Layout and what we own

| Path | Role | Git |
|---|---|---|
| `tools/third_party/pcsx2/pcsx2-qt.exe` | PCSX2 v2.8.2 Qt x64 portable (see `docs/TOOLS.md`) | ignored |
| `tools/third_party/pcsx2/portable.txt` | empty marker: PCSX2 keeps `inis/ bios/ logs/ sstates/ memcards/ snaps/ dumps/ cache/` next to the exe | ignored |
| `tools/third_party/pcsx2/bios/` | the user's own BIOS dump (we use `ps2-0230a-20080220.bin`; PCSX2 created the sidecars `ps2-0230a-20080220.nvm` / `.mec` next to it on first boot) | ignored |
| `tools/third_party/pcsx2/inis/PCSX2.ini` | the configuration below; `PCSX2.ini.default.bak` = pristine `-testconfig` output, `PCSX2.ini.<stamp>.bak` = one backup per `configure_ini.py` write | ignored |
| `tools/third_party/pcsx2/logs/emulog.txt` | the run log (PCSX2 truncates it on every start; it is flushed lazily, so read it after the run or copy it late) | ignored |
| `tools/third_party/pcsx2/sstates/SLUS-21621 (94A82AAA).NN.p2s` | save states (slot NN); contain game + BIOS data | ignored |
| `tools/ours/pcsx2/configure_ini.py` | idempotent ini editor (backs up first) | ours |
| `tools/ours/pcsx2/run_pcsx2.ps1` | boot with timeout + clean stop + log capture | ours |
| `tools/ours/pcsx2/pine.py` | stdlib PINE client (reads/writes/save/load state/metadata) | ours |
| `tools/ours/pcsx2/extract_savestate.py` | `.p2s` extractor + ELF-vs-RAM verification | ours |
| `extracted/_pcsx2/title/` | extracted title-screen state (`eeMemory.bin` …, `verify.json`) | ignored |

## 2. How to run (exact commands, from the repo root)

```powershell
# one-time: generate the default ini, then apply our settings (fast boot on, state compression zstd)
tools\third_party\pcsx2\pcsx2-qt.exe -portable -testconfig
C:\Python314\python.exe tools\ours\pcsx2\configure_ini.py --fastboot on --statecomp 2

# boot the ISO for 120 s, stop cleanly, copy the log to extracted\_pcsx2\logs\emulog_<stamp>.txt
powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -TimeoutSec 120 -FastBoot
#   -SlowBoot forces the BIOS -> OSDSYS -> PS2LOGO -> SLUS_216.21 path, -NoGui hides the window,
#   -ExtraArgs passes further pcsx2-qt flags, -LogCopy <path> picks the log destination.

# leave it running for PINE, then stop it later (WM_CLOSE first, Stop-Process after 15 s)
powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -KeepRunning -FastBoot
C:\Python314\python.exe tools\ours\pcsx2\pine.py status
powershell -ExecutionPolicy Bypass -File tools\ours\pcsx2\run_pcsx2.ps1 -StopPid <pid>

# save state slot 0 over PINE, extract and verify it against the ELF
C:\Python314\python.exe tools\ours\pcsx2\pine.py savestate 0
C:\Python314\python.exe tools\ours\pcsx2\extract_savestate.py "tools\third_party\pcsx2\sstates\SLUS-21621 (94A82AAA).00.p2s" extracted\_pcsx2\title --verify-elf extracted\disc\SLUS_216.21
```

Timing (observed, log timestamps are seconds since process start): slow boot reaches `ELF cdrom0:\SLUS_216.21;1 ... is executing` at 126.6 s (the OSD sits ~2 min on the fresh-NVM path: `ExecutePs2GameDisk` at 118 s), the opening FMV starts at 149.9 s and ends at 239.2 s, i.e. the title screen is up ~4 min after launch. Fast boot executes the ELF at 3.6 s and loads the first IRX at 4.8 s.

### CLI flags of this build (observed: `-help` prints nothing to a pipe because the exe is a GUI-subsystem app; the list below is the help text recovered from the binary's strings and exercised where noted)

`-help`, `-version`, `-batch` (exit after the VM shuts down; **used**), `-nogui` (hide main window, implies batch), `-fullscreen`, `-nofullscreen`, `-bigpicture`, `-slowboot` / `-fastboot` (override `EnableFastBoot` for this boot; **both used**), `-bios` (boot the OSD), `-disc <path>`, `-elf <file>` (override boot ELF), `-state <index>`, `-statefile <file>`, `-gameargs "<args>"`, `-debugger` (open debugger, break at entry), `-logfile <path>`, `-earlyconsolelog` (**used**), `-raintegration`, `-portable` (**used**), `-datapath <path>`, `-setupwizard`, `-testconfig` (**used**), `-turbo`, `-unlimited`, `--` (end of options; **used**, the ISO path follows).

## 3. ini keys changed (`configure_ini.py` baseline; everything else is the 2.8.2 default)

| Section / key | Value | Why |
|---|---|---|
| `[UI] SetupWizardIncomplete` | `false` | default `true` pops the first-run wizard on every launch |
| `[UI] ConfirmShutdown` | `false` | so WM_CLOSE from `run_pcsx2.ps1` stops the VM without a modal prompt |
| `[UI] StartFullscreen` / `PauseOnFocusLoss` / `StartPaused` | `false` | already default; pinned |
| `[Folders] Bios` | `bios` | default (relative to the portable dir); pinned |
| `[Filenames] BIOS` | `ps2-0230a-20080220.bin` | USA v2.30 dump from the user's `bios/` folder, matching the SLUS disc. **PCSX2 2.8.2 has no "region auto" setting**: the region is whatever the BIOS is; an empty value makes PCSX2 refuse to boot, so it must be named. Chosen over the `SCPH-90001_BIOS_V18_USA_230.ROM0` set so PCSX2 writes its mutable `.nvm`/`.mec` sidecars next to a plain file instead of modifying the user's genuine `.NVM`/`.MEC` dumps |
| `[EmuCore] EnablePINE` / `PINESlot` | `true` / `28011` | PINE server on TCP 127.0.0.1:28011 |
| `[EmuCore] EnableFastBoot` | `false` for the first run (observed BIOS path), **`true` now** | `--fastboot on|off` |
| `[EmuCore] EnableFastBootFastForward` | `false` | default; pinned |
| `[EmuCore] SaveStateOnShutdown` / `BackupSavestate` | `false` / `false` | exactly one `.p2s` per slot, nothing written on close |
| `[EmuCore] SavestateCompressionType` | `2` (Zstandard; 0 = Uncompressed, 1 = Deflate64, 3 = LZMA2) | default kept, our extractor handles 0 and 2; `--statecomp 0` if a tool without zstd needs to read states |
| `[EmuCore/GS] Renderer` | `13` (software) | default `-1` = auto (D3D12 here); software for deterministic frames |
| `[EmuCore/GS] upscale_multiplier` | `1` | native 640x448 |
| `[EmuCore/Speedhacks] vuThread` | **`false`** (MTVU off; added 2026-10-18 for reference captures) | PCSX2 warns save states may be unstable with MTVU; ADR-0012 §3 |
| `[SPU2/Output] Backend` | **`Null`** (added 2026-10-18) | host audio output only (guest SPU2 is still emulated). With `Cubeb`, 5/5 boots crashed (`0xC0000005`, fault in an unregistered low-memory region, offset `…5E42`) ~10 s into the opening FMV — fast and slow boot, MTVU on and off, with and without PINE polling; with `Null` 4/4 boots ran through the FMV to the title, but one of them later crashed the same way at the title (§9). Not a full fix |
| `[Logging] EnableFileLogging` / `EnableTimestamps` | `true` | `logs/emulog.txt` with `[ seconds]` stamps |
| `[Logging] EnableEEConsole` / `EnableIOPConsole` | `true` | EE `printf`/`sceSif` text and the IOP tty (`loadmodule:` lines) |
| `[Logging] EnableVerbose` | `true` | extra PCSX2 messages (`cdvdLoadElf`, CRTC lines) |
| `[Logging] EnableSystemConsole` | `false` | no console window |
| `[EmuCore/TraceLog] Enabled, EE.bios, EE.memory, EE.r5900, EE.cop0, EE.knownhw, MISC.sif` | toggled by `--tracelog on|off`; **off now** | §7 |
| `[EmuCore/CPU/Recompiler] EnableEE` | toggled via `--set` for the §7 test; **`true` (recompiler) now** | |

Not changed but relevant to determinism (open, see §8): `[EmuCore/Speedhacks] vuThread=true` (MTVU; PCSX2 warned `MTVU speedhack is enabled, saved states may not be stable` when saving), `IntcStat`, `WaitLoop`, `EECycleRate=0`, `[EmuCore/GS] extrathreads=3` (software-renderer worker threads), `SkipDuplicateFrames=true`, audio `[SPU2/Output] Backend=Cubeb`. Game patches: PCSX2 found 3 patch groups in its bundled `SLUS-21621_94A82AAA.pnach` (`[Widescreen 16:9]`, `[Mode 480p]`, `[Controllable Party Members]` by TGE); all are opt-in sections and none is enabled (`EnableWideScreenPatches=false`, no `gamesettings/94A82AAA.ini`), and the code-band check in §6 confirms no patched word.

## 4. Boot smoke test (slow boot, observed, `extracted/_pcsx2/logs/emulog_slowboot_title_20261018.txt`)

- BIOS: `[0.5074] BIOS Found: USA     v02.30(20/02/2008)  Console 20080220-175343` (followed by `BIOS rom1 module not found, skipping` and the creation of a default NVM/MEC: `Failed to open or read NVRAM at ps2-0230a-20080220.nvm ... creating default`). The OSD later printed `REGION PARAMS = Oceania AAengAU` from that default NVM (harmless for an NTSC-U disc; open question in §8).
- Disc/ELF: `[0.5111] (SYSTEM.CNF) Detected PS2 Disc = cdrom0:\SLUS_216.21;1`, `Disc region type = NTSC`, `Serial: SLUS-21621 ... CRC: 94A82AAA`; after the OSD: `[124.6570] ELF Loading: cdrom0:\SLUS_216.21;1, Game CRC = 94A82AAA, EntryPoint = 0x00100008`, `[126.6273] ELF cdrom0:\SLUS_216.21;1 with entry point at 0x00100008 is executing.` (`loadelf` printed `0 00100000 008acc80` = one PT_LOAD, as in `docs/ANALYSIS/00_elf_layout.md`).
- IOP reboot: `IOP Realtime Kernel Ver. 2.2` at 127.14 s after `Get Reboot Request From EE` (the `IOPRP310.IMG` reboot of topic 12 step 2).
- IRX loads (IOP tty drops the backslashes), **exactly the 15 loads in topic 12's order**:
  `[127.1783] loadmodule: fname cdrom0:LIB31SIO2MAN.IRX;1 args 0 arg` → `id 25, ret 0`; `SIO2D` 26/0; `PADMAN` 27/0; `DBCMAN` 28/0; `MC2_S1` 29/2; `LIBSD` 30/0; `CRI_ADXI.IRX;1 args 20 arg sdinit=0 spucore=1` 31/2 (driver banner `CRI ADX Driver Ver.9.44(Feb 28 2005 ...)`, `SPU CORE Number = 0`); `SDRDRV` 32/2; `MODHSYN` 33/0; `MODMSIN` 34/0; `MODSESQ` 35/0; `SKSOUND` 36/0; `SKHSYNTH` 37/0; `SKHSYNTH` again `id 38, ret 1` (already resident, still ≥ 0 as topic 12 requires); `SKSESQ.IRX;1 args 24 arg maxtrack=16` 39/0 (`[127.8292]`). No `sceSif`/RPC error lines anywhere in the log.
- GS mode: `[127.8450] Set GS CRTC configuration. NTSC 640x448 @ 59.940 (59.82) Interlaced (FIELD)` — matches topic 10 (640x448 NTSC interlaced, SMODE2 FIELD). (The OSD and PS2LOGO before it used `Interlaced (FRAME)`.)
- First game frames: `[127.8631] SDR callback thread created`, `PS2RNA: sceSifAllocIopHeap(266304) ret=0x000bdd00`, `[127.9061] DVCI: File cache was not hit. "DATA.CVM;1"` then `BGM.CVM;1`, `BTL.CVM;1` (the `sceCdLayerSearchFile` volume lookups of topic 11); `[138.4055] microVU1: Cached Prog = [000]` = first VU1 program; `[149.8939] FMV started` (opening movie), `[239.2427] FMV ended`.
- Title: the save state taken at 262.3 s (`OSD [SaveStateSlot0]: Saving state to slot 0...`) embeds `Screenshot.png` showing "PRESS ANY BUTTON", the P3F / PERSONA3 FES logo and "© 2006-2008 ATLUS" (file `extracted/_pcsx2/title/Screenshot.png`); the window status bar read `Software 640x448 (1x) ... FPS: 30 VPS: 60` — consistent with topic 10's inferred 30 fps lock. Harmless noise: `cdvdLoadElf(): Unknown device in ELF path 'rom0:PS2LOGO'` (PCSX2 only resolves disc ELFs) and recompiler `Possible old value used in COP2 code` notes at `0x273000` (OSD-era code, before the game ELF).
- Stop: `run_pcsx2.ps1 -StopPid` → WM_CLOSE shut the VM down cleanly (`Add 403 seconds play time`, `NVRAM saved to ps2-0230a-20080220.nvm`, `Releasing host memory`), no `Stop-Process` needed.

## 5. PINE usage (`tools/ours/pcsx2/pine.py`)

Protocol as implemented and exercised against this build: TCP `127.0.0.1:28011`; request `u32 size (incl. itself) | u8 opcode | payload`, reply `u32 size | u8 result (0 ok, 0xFF fail) | payload`; opcodes `MsgRead8..64 = 0..3`, `MsgWrite8..64 = 4..7`, `MsgVersion 8`, `MsgSaveState 9 (u8 slot)`, `MsgLoadState 10`, `MsgTitle 11`, `MsgID 12`, `MsgUUID 13`, `MsgGameVersion 14`, `MsgStatus 15` (u32: 0 running, 1 paused, 2 shutdown); strings are `u32 len | bytes` with the NUL counted. (PCSX2's own spec lives in `pcsx2/PINE.h` of the upstream repo, which is not cloned here; the opcode table was taken from the task brief and confirmed by the replies below.) The server logs each connection (`PINE: New client with FD n connected.` / `Client disconnected.`).

Observed replies: `status` → `0 (Running)`, `version` → `PCSX2 v2.8.2`, `title` → `Shin Megami Tensei - Persona 3 FES`, `id` → `SLUS-21621`, `uuid` → `94a82aaa`, `gameversion` → `1.00`; `savestate 0` → ok and the `.p2s` appeared ~0.3 s later.

**Proof read while the game ran** (`pine.py dump 5E5150 64`):
```
005E5150  17 00 00 00 17 00 00 00 14 00 00 00 23 44 69 72  ............#Dir
005E5160  4c 73 74 23 00 00 00 00 00 08 00 00 00 00 00 00  Lst#............
005E5170  14 00 00 00 02 36 2e 00 00 00 00 00 00 00 00 00  .....6..........
```
= `{count=0x17, count=0x17, dir_lba=0x14, "#DirLst#"}` followed by the `.` entry, byte-identical to ELF file offset `0x4E51D0` (`docs/DISC_LAYOUT.md` §6). Frame counters moved between polls (`0x7CE10C`: `0x1ACD` → `0x1B19` two seconds later; `g_skyFrameCount 0x7CEA78`: `0x2C1` → `0x30D`), `g_kwlnFirstFrame 0x7CC134 = 0`, `g_kwlnRootTask 0x7CE0D0 = 0x01023040` — the topic 10 loop is running. Before the game ELF was loaded (OSD still running at 90 s) the same addresses read as OSDSYS bytes / zeros, so a PINE poll of `0x5E5150 == 0x17` is a cheap "game ELF is in RAM" check.

Addressing (observed): PINE resolves **EE virtual addresses through the guest TLB**. Game VAs in kuseg read directly; the kernel area must be read through kseg0: `read32 80075000` → `0x3C028007` (the TLB-patch payload) while `read32 75000` → `0`, because the EE leaves kuseg `0x0–0x7FFFF` unmapped; `read32 82000` → `0x3C1D0008` (the alarm stub). Reads past 32 MiB (`0x02000000`) return `0`, not an error. The extracted `eeMemory.bin` on the other hand is **physical** (offset = VA & 0x1FFFFFFF).

## 6. Save-state format and the title-screen state

Format (observed, `SLUS-21621 (94A82AAA).00.p2s`, 9,438,380 B): a plain ZIP (`PK\x03\x04`) whose entries are stored (method 0) or **Zstandard-compressed (method 93, one raw zstd frame per entry)**; `PCSX2 Savestate Version.id` reports `Savestate version: 0x9a590000`. Entries: `PCSX2 Internal Structures.dat` (2,275,706 B: CPU/COP0/VU registers, DMAC, counters … opaque to us), `eeMemory.bin` 33,554,432 B, `iopMemory.bin` 2,097,152 B, `eeHwRegs.bin` 65,536, `iopHwRegs.bin` 65,536, `Scratchpad.bin` 16,384, `vu0Memory.bin` 4,096, `vu1Memory.bin` 16,384, `vu0MicroMem.bin` 4,096, `vu1MicroMem.bin` 16,384, `SPU2.bin` 2,178,992, `USB.bin` 8,491, `PAD.bin` 228, `GS.bin` 4,194,813 (GS registers + 4 MiB VRAM), `Screenshot.png` 378,027 (stored). Python has no zstd in the stdlib and the `zstandard` module is not installed, so `extract_savestate.py` reads the raw entry bytes and decompresses them through PCSX2's own `zstd.dll` (1.5.7) via `ctypes`, checking each entry's CRC32 (all 16 `crc ok`). If that is unwanted, set `--statecomp 0` and plain `zipfile` suffices; 7-Zip (`C:\Program Files\7-Zip\7z.exe`) is also present.

Verification of `extracted/_pcsx2/title/eeMemory.bin` against `extracted/disc/SLUS_216.21` (SHA-256 `d1b163eb…57bc`, PT_LOAD VA `0x100000`, 9,096,320 B; `verify.json` holds the numbers):

| Check | Result (observed) |
|---|---|
| (a) code band `0x100000–0x5A1400` (4,854,784 B) | **0 differing bytes** — no self-modifying code, no overlay or patch write into the band (independent confirmation of topic 13 and of "no pnach applied") |
| (a′) rest of the initialised image `0x5A1400–0x7CDE80` (2,280,064 B) | 6,066 differing bytes in 1,937 runs (829 of them 3-byte, 690 single-byte); samples: `0x6A3E50` eight words `-1` → `0..7`, `0x6B4FC0/4FE0/5120` zero words → heap pointers `0x00C427F0`/`0x00C42824` — ordinary writes to writable globals living in the single `main` section (the ELF has no .data/.rodata split) |
| (a″) `.bss` `0x7CDE80–0x9ACC80` (1,961,472 B) | 448,766 bytes non-zero — the game's live state |
| (b) 149 `#DirLst#` tables `0x5E5150–0x6784B8` (602,984 B) | **0 differing bytes; 149 markers in RAM at the same 149 positions as in the ELF; 0 tables differ** |
| (c) kernel-patch payloads (topic 12 §5) | `0x80074000` ExecPS2 patch (1,960 B from `0x77FBD8`): **absent**, destination all zero → `PatchIsNeeded` was false on this BIOS (as topic 12 expected). `0x80075000` TLB payload (816 B from `0x77F568`): **present**, 816/816 bytes equal (installed unconditionally, as documented). `0x80076000` alarm payload (1,856 B from `0x7803A0`): **present**, 1856/1856, and its 40-byte T3 stub at `0x00082000` (from `0x780AE0`): **present**, 40/40 |

Inferred from (c): the `InitAlarm` gate `(T3_MODE & 0x100) == 0` was **true** at runtime under PCSX2 + BIOS v2.30, so the libkernel alarm patch *is* installed, contrary to topic 12's "make `T3_MODE` bit 8 read as set so the patch is skipped" plan; the HLE must either accept the `Copy`/`SetSyscall(0xFC..0xFF, 0x12C, 0x08)` sequence as benign writes (topic 12 already says the patched syscalls have no later callers) or mimic the real kernel's T3 state. Whether a real console with this ROM behaves the same is **unverified** (PCSX2 may simply not model the kernel's T3 CMPE bit). Flag for topic 12 / `RUNTIME_CONTRACT.md`.

## 7. Trace capability — verdict for `TRACE_FORMAT.md` §6

**Observed:** with `[EmuCore/TraceLog] Enabled=true` and `EE.bios`, `EE.memory`, `EE.r5900`, `EE.cop0`, `EE.knownhw`, `MISC.sif` all `true`, a 15 s fast-boot run (ELF executing at 3.6 s, IRX loads at 4.8 s) produced an `emulog.txt` of 22,423 B / 417 lines containing **no per-instruction, syscall, or hardware-access line at all** (`extracted/_pcsx2/logs/emulog_fastboot_tracelog_test.txt`). Repeating with the EE interpreter (`[EmuCore/CPU/Recompiler] EnableEE=false`) gave 22,806 B / 419 lines, again nothing (`emulog_fastboot_tracelog_interp_test.txt`). The binary does contain the key names (`EmuCore/TraceLog`, `EE.r5900`, …), i.e. the settings are parsed but the sinks are compiled out of this release build. **Verdict: option (a) is unavailable in PCSX2 2.8.2 release.** No sample line exists to quote.

GS dumps **do** exist in this build: menu actions `Save Single Frame GS Dump` / `Save Multi Frame GS Dump` (Debug menu once advanced settings are shown), hotkeys `[Hotkeys] GSDumpSingleFrame = Shift+F8`, `GSDumpMultiFrame = Ctrl+Shift+F8`, output `.gs.zst` (`[EmuCore/GS] GSDumpCompression=2`), and the same exe replays `*.gs`/`*.gs.xz`/`*.gs.zst` as a "game" (built-in `GSDumpReplayer`). Not fired in this session (needs a focused window keystroke).

**Recommendation (for the lead to record as the §6 ADR):** keep PCSX2 2.8.2 as the *state* oracle, not the *instruction* oracle. (1) Level B/C now, cheaply, through what works today: PINE reads at `SYNC` points (`EVENT`/syscall markers our runtime emits) and save-state diffs — two `eeMemory.bin` images diffed give the net memory-write set between two sync points, which is exactly the Phase 5 "replace a block, keep the write log identical" check at coarse granularity, and `GS.bin` + GS dumps give the GIF-packet ground truth for the renderer. (2) For Level A (per-instruction `.p3tr`), follow the document's default plan, **(c) a patched PCSX2 build with an emitter hook in the EE interpreter** (`R5900::Interpreter`, `EnableEE=false`): option (a) would at best require a self-built dev build whose text trace still has to be converted, so hooking the interpreter directly to write `P3TR` is the smaller total effort and gives the register-delta records the format wants. The fork stays outside this repo (GPL-3.0; build recipe + patch only). (3) Do not spend time on (d) the Qt debugger beyond spot checks (`-debugger` exists and breaks at the entry point).

## 8. Open questions

1. Determinism knobs: `vuThread` (MTVU) is now pinned `false` and host audio `Null` (§3, §9); `extrathreads` for the software renderer and `SkipDuplicateFrames` do not change guest state but should be fixed before GS-dump diffs; interpreter vs recompiler should be chosen per trace level (TRACE_FORMAT §4.1 timing masks still apply either way).
2. Default NVM: PCSX2 generated `ps2-0230a-20080220.nvm` with OSD region params reported as `Oceania AAengAU` for a USA ROM. It did not affect the NTSC-U boot; if OSD language/clock defaults ever matter, use the user's genuine `SCPH-90001_BIOS_V18_USA_230.NVM` set (read-only copy question: PCSX2 writes back to the sidecar on exit).
3. Topic 12 §5: the alarm patch *is* installed at runtime (§6(c)); needs a decision on whether the HLE mimics kernel T3 state or just tolerates the patch writes.
4. The slow-boot OSD path takes ~2 min on this BIOS before `ExecutePs2GameDisk`; unknown why (first-boot NVM? PS2LOGO decode?). Fast boot is the default from now on; slow boot only when the BIOS→ELF handover itself is under study.
5. `-help`/`-version` write nothing to a redirected pipe; `-earlyconsolelog` only affects a real console. If a CLI usage dump is wanted, run from a `cmd` with `start /wait` or read the strings as done here.
6. PINE has no "shutdown" opcode; clean stop is WM_CLOSE via `run_pcsx2.ps1 -StopPid`. A `-batch` run with the game still running never exits on its own (the VM only shuts down when the game or the user stops it), so the timeout path is the normal path.

## 9. Reference captures (2026-10-18, ADR-0012)

_Observed unless marked; all files below are gitignored (`extracted/_pcsx2/`, PCSX2's own `sstates/ snaps/ logs/`)._

**Tools.** `capture.py run` boots PCSX2 under the oracle ini, detects each point over PINE (one batched message per poll, `pine.Pine.read_many`), fires one Shift+F8 GS dump, then `MsgSaveState`, extracts the state and writes `<point>/capture.json` (seconds since launch, globals at the request **and read back from the state's own `eeMemory.bin`** = the exact frame, PCSX2 version, CRC `94a82aaa`, ini hashes, detection method/uncertainty, GS-dump record, screenshot pixel stats). `measure_flips.py` (or `capture.py run --measure-flips N`) samples the flip/vsync globals at 2 ms. Commands:
```powershell
C:\Python314\python.exe tools\ours\pcsx2\configure_ini.py --fastboot on
C:\Python314\python.exe tools\ours\pcsx2\capture.py run --tag A --title-name title_runA --measure-flips 2500
C:\Python314\python.exe tools\ours\pcsx2\capture.py run --tag B --points title --title-name title_runB --slot-base 4 --measure-flips 2500
build\msvc-tracediff\bin\tracediff.exe snapshot-mask extracted\_pcsx2\title_runA\eeMemory.bin extracted\_pcsx2\title_runB\eeMemory.bin --out extracted\_pcsx2\masks\title.txt
build\msvc-tracediff\bin\tracediff.exe snapshot extracted\_pcsx2\first_flip\eeMemory.bin extracted\_pcsx2\title_runA\eeMemory.bin --json extracted\_pcsx2\masks\first_flip_vs_title_runA.json
```

**Oracle ini.** Fast boot on, PINE on, software renderer, MTVU off, host audio `Null` (§3). PCSX2 rewrites `HeaderState` (in `[GameListTableView]`) and `[UI] MainWindowGeometry/State` on every exit, so the raw file hash changes per run; the oracle id is the hash without those keys: **`ini_sha256_normalized = 2630dac3…2a59`** for all four captures (the value first recorded by the tool dropped only `[UI]` keys and is kept as `…_as_recorded`).

**Stability (open).** With host audio `Cubeb`, 5/5 boots crashed ~10 s into the opening FMV (fast and slow boot, MTVU on and off, with and without PINE). Every crash in this session is the same `0xC0000005` at a fixed non-module address (`0x02455E42` twice, else `0x0…5E42` at a 64 KiB-aligned base). With `Null`, 4 sessions reached the title; one (run A) crashed the same way ~20 s after the title state had been saved, during PINE flip sampling. The captured states are complete (CRC-checked). Root cause unknown. `capture.py` reports `pcsx2_exited_by_itself`.

**What PINE can and cannot see.** GS privileged registers (`0x12000070 DISPFB1`, `0x12001000 CSR`) and EE hardware registers read back as 0, so there is no direct VBlank/FIELD counter. Disassembly (our own decoder over the ELF): `_rwDMAVSYNCHandler 0x4D47F0` keeps **no monotonic counter**. Byte `0x7CE988` counts vblanks since the last flip up to the byte `0x7CE960`, which is **0 at runtime**, so RW itself never holds a flip back. The flip path clears `g_rwDMAFlipPending` first (`0x4D486C`), and every path returns 0. `adxt_vsync_cnt 0x787568` is incremented unconditionally on entry of `ADXPS2_ExecVint 0x540D80` (`0x540DA8`), whose only caller is `kwlnGsSyncVCallback 0x197FE0`. The vblank time base is therefore `g_kwlnFrameEndHsync 0x7CE148` (T0 in H-BLANK mode between two ShowRaster calls; 262.5 lines per field).

| Point | Detection | State frame (`g_skyFrameCount` / kwln) | s since launch | Screenshot | GS dump |
|---|---|---|---|---|---|
| `first_flip` | first executed flip after `g_skyFrameCount ≥ 2` (`g_rwDMAFlipPending` 1→0 at sky 3), ~1 ms batched polling | 11 / 6170: **8 flips after the first one**; ~0.23 s went to re-foregrounding the window for the dump (a run that saved first landed at sky 4, but its dump came 20 frames later) | 16.6 | memory-card check screen | ok, keystroke at sky 10 (25 KB) |
| `atlus_logo` | sky ≥ first-flip + 150 (5 s at 30 fps). Heuristic: in 4 probe runs the logo was fully shown +3.8…+6.2 s after the first flip | 154 / 6313 | 21.5 | pixel test `atlus_logo_likely = true` (red T + blue letters on black) | ok, sky 153 (24 KB) |
| `title_runA` | emulog `FMV ended` (polled 0.25 s, flushed ~1 s late), then sky + 240 | 3279 / 9438 | 143.9 | title (PRESS ANY BUTTON) | ok, sky 3278 (2.8 MB) |
| `title_runB` | same, independent boot | 3274 / 9433 | 149.8 | title | ok, sky 3273 (2.9 MB) |

**GS dumps.** PINE has no dump opcode. `SendInput` Shift+F8 is sent only after `GetForegroundWindow()` confirms PCSX2 has focus, and no other key is ever sent. It worked on 5/5 attempts: `snaps/<title>_SLUS-21621_<stamp>.gs.zst` plus a `.png`, copied to `<point>/gsdump.*`. The keystroke steals focus from the user's desktop for about 0.2 s per run.

**Noise mask (title A vs B, 5 frames apart).** 42,156 bytes in 15,133 runs: data 131 B / 91, bss 5,920 B / 1,951, heap 36,083 B / 13,081, stack 22 B / 10, code 0, kernel masked. Written to `masks/title.txt` (15,133 ranges, pad 0). Masked A vs B gives 0 by construction.

**`first_flip` vs `title_runA`** (default kernel mask): 6,325,509 differing bytes in 134,732 runs. First divergence `0x0077E4F1` (data, 3 bytes). Per band: code 0, data 2,116 / 730, bss 18,454 / 4,330, heap 6,301,877 / 129,435, stack 3,062 / 237. Largest runs are 160–190 KiB heap blocks. With the title mask: 6,286,789 / 133,742. The code band stays byte-identical at both points (cf. §6).

**Flip rate at the title** (2 runs × 2,500 samples at 2.0 ms, 5.0 s, max gap 3.0 ms, `flips/flip_rate_*.json`):
- Requests, executed flips (139–140 pending edges plus 10–11 back-to-back buffer toggles = 150), game frames and `kwlnGsSyncVCallback` invocations all run at **30.012/s, ratio 0.5007 to 59.94 Hz**.
- Every frame spans **525 H-lines (521–531) = 2.0 fields**, while the frame's CPU work is 47 lines (load ~9%), so without gating the game could flip every vblank.
- **150/150 flips fall in the same vblank (±2 ms) as a callback invocation; 0 do not.**

This is consistent with topic 15 §2 (derived from the dispatcher code): `next=0` puts a handler at the head and `-1` at the tail, and a **negative** return stops the chain. The resulting chain is [field gate, RW, ADX callback]: on FIELD=0 the gate's −1 stops it; on FIELD=1 all three run. It is **not** consistent with topic 10 §3.1's reading that a 0 return terminates the chain, since RW returns 0 and the callback still runs on the same vblanks. This corroborates the rule but does not prove it: only the outcome of the kernel's dispatch is observed, on PCSX2's model of CSR.FIELD.

## 10. In-game reference state (Milestone 4, user-driven)

The route into the game needs button presses, which `capture.py` does not send (it sends only Shift+F8, §9).
The in-game comparison point is therefore produced by hand, once, and extracted with the existing tool:

1. `python -I tools\ours\pcsx2\configure_ini.py --fastboot on` (oracle ini, §3), and make sure slot 1 holds a
   **fresh, formatted** card (PCSX2 → Settings → Memory Cards; the port's route `config/inputs/to_dorm.txt` was
   recorded with `--memcard new`, so the first in-game save prompt and the card contents match).
2. Boot the ISO, skip the logos/movies with START, cross through the title and New Game, answer the
   "played before" / dialogue-speed prompts as the recording does (cross through, default choices), START through
   the three FMVs, and stop on the first dorm lobby line, Mitsuru's **"My name is Mitsuru Kirijo..."** (`4/7 Tu Late
   Night`), *before* advancing it.
3. Save a state in an unused slot (F1 saves the current slot; Shift+F2/F2 change it; or System → Save State).
4. Extract it: `python -I tools\ours\pcsx2\capture.py extract <slot> dorm --tag M4` → `extracted/_pcsx2/dorm/`.
5. Compare with the port's snapshot at the same line (`BUILDING.md` "Scripted path into the game",
   `extracted/_ours/dorm_replay_4900`):
   `tracediff snapshot extracted\_pcsx2\dorm\eeMemory.bin extracted\_ours\dorm_replay_4900\eeMemory.bin --json extracted\_ours\tracediff\m4.json`
   and `p3fes_gscmp` on the two frames. Expected classes (as at M1–M3): code band 0; timing counters, RNG state,
   IOP identity values, dead stack. The kernel area is masked by default.

## 11. EE semantics vectors (PCSX2 observed)

_2026-10-19, PCSX2 2.8.2 release binary as a black box (ADR-0010/0012). Tools in `tools/ours/eevec/` (README there),
data in `tests/ee/vectors/pcsx2_vectors.json`, test `tests/ee/test_pcsx2_vectors.cpp` (part of `p3fes_tests`)._

**What.** The EE semantics headers `runtime/include/p3fes/ee/{hilo,mmi,fpu,vu0,core}.h` are checked against PCSX2
with compiled test vectors (GOAL.md Phase 4, ADR-0006 item 5): `gen_vectors.py` holds the vector tables and emits a
freestanding R5900 program (entry `0x100000`, no libc, built with the ps2dev `mips64r5900el-ps2-elf-as`/`ld` from
`tools/env.ps1`) that loads each operand set, runs the instruction and stores rd / HI / LO / FCR31 / VU0
STATUS-MAC-CLIP-Q (before and after) / an ACC probe into a 96-byte slot of a results table at `0x01000000`, bumps a
progress word, writes a magic word after the last safe vector and a tail marker after the vectors that may trap on
hardware. `run_pcsx2.py` boots the ELF, polls the markers over PINE, reads the table (batched 64-bit reads, twice,
identical) and writes the JSON; the doctest replays every vector through our headers (MMI lane ops on both the
scalar and the SSE2 path) and compares each observed field.

**Launch (observed to work).** PCSX2 2.8.2 boots a bare ELF given as the file argument, no disc needed:
`tools\ours\pcsx2\run_pcsx2.ps1 -Iso build\eevec-msvc\eevec\eevec.elf -KeepRunning -FastBoot`, i.e.
`pcsx2-qt.exe -portable -earlyconsolelog -fastboot -- <path>\eevec.elf`; emulog: `ELF Loading: host:eevec.elf, Game CRC
= ..., EntryPoint = 0x00100000`, `loadelf: fname host:eevec.elf secname all`. The BIOS hands the program COP1 and COP2
enabled (Status read back `0x70030C11`), FCR0 reads `0x2E30`. The magic word appears 1-4 s after launch; the whole
run including the read-back takes about 20 s per engine. The ini stays the oracle ini (`check_ini` gate; normalized hash
`2630dac3...2a59` before and after); the interpreter pass sets `[EmuCore/CPU/Recompiler] EnableEE=false` through
`configure_ini.py --set` for its run and restores it.

**Regenerate** (also in `tools/ours/eevec/README.md`):
```powershell
& $env:P3FES_PYTHON -I tools\ours\eevec\gen_vectors.py --out build\eevec-msvc\eevec --build
& $env:P3FES_PYTHON -I tools\ours\eevec\run_pcsx2.py --elf build\eevec-msvc\eevec\eevec.elf --layout build\eevec-msvc\eevec\layout.json --out tests\ee\vectors\pcsx2_vectors.json --ee-mode rec
& $env:P3FES_PYTHON -I tools\ours\eevec\run_pcsx2.py --elf ... --layout ... --out tests\ee\vectors\pcsx2_vectors.json --merge tests\ee\vectors\pcsx2_vectors.json --ee-mode int
$env:P3FES_EEVEC_REPORT = "$PWD\build\eevec-msvc\eevec\report.jsonl"; .\build\eevec-msvc\bin\p3fes_tests.exe -tc="pcsx2 vectors*"
& $env:P3FES_PYTHON -I tools\ours\eevec\annotate.py --report build\eevec-msvc\eevec\report.jsonl
```

**Two engines, one oracle.** Every vector was run under the EE recompiler (the oracle ini used for all captures,
`obs`) and under the EE interpreter (`obs_int`, stored where it differs). They disagree on **1,122 of 3,443
vectors**; the interpreter is PCSX2's reference model and is treated as the oracle where they differ (lead decision),
the recompiler's value is accepted as `agree-rec:<class>` where it is the one that follows the manual. The classes
(observed, by field):

| Class | Vectors (field) |
|---|---|
| FCR31 fixed bits: the recompiler reads `0x01000001` (FS, RM=01) and masks CTC1 to `0x0083C078`; the interpreter stores CTC1 raw from reset value 0 (ours: raw from 0) | 736, every FPU vector (`fcr31`, `fcr31_pre`) |
| FCR0: recompiler `0x2E30`, interpreter `0x2E00` (ours `0x2E30`) | 736 (`fcr0`; compared only on `cfc1.fcr0`) |
| FCR31 cause bits: the recompiler clears I/D on every DIV/SQRT/RSQRT, the interpreter clears O/U on ADD/SUB/MUL/MADD; neither sets O/U (ours: set-only) | within the 736 |
| Exact round-toward-zero ADD/SUB: the interpreter and the VU path are exact (`1.0 - 2^-26 = 0x3F7FFFFF`, `2^31 + -1.0 = 0x4EFFFFFF`); the FPU recompiler returns the larger operand when they are more than 24 binades apart | part of `fd` 69 |
| Exponent-255 operands/results: the recompiler clamps everything to IEEE `+/-0x7F7FFFFF`; the interpreter keeps some EE-range results (`0x7FFFFFFF / 0x7FFFFFFF = 1.0`, `2^128 x 0.5 = 2^127`) | `fd`/`acc` 69 + 10 |
| DIV.S rounding: recompiler round-to-nearest (`FPUDiv.Roundmode=0`), interpreter truncation (`1/3 = 0x3EAAAAAA`) | 35 |
| MAX.S/MIN.S ties: recompiler returns flushed ft, interpreter orders -0 below +0 without flushing | 5 |
| `sqrt.s`: the recompiler rounds to nearest (`sqrt(10) = 0x404A62C2`), the interpreter truncates (`...C1`, ours) | 2 |
| LWR with a non-zero byte offset: recompiler zero-extends the merged word, interpreter leaves bits 63..32 (ours) | `core` 6 |
| PMADDW/PMSUBW: the interpreter drops the carry from LO into HI; the recompiler (and ours) keep the 64-bit sum | `mmi` 7 |
| MTSA: the recompiler masks the value to 4 bits (bytes), the interpreter stores it raw and QFSRV then shifts by a garbage amount | `mmi` 7 |
| CTC2 STATUS ($16): the recompiler writes only the sticky bits 6..11 (ours), the interpreter writes all 32 | `vu0` `status`/`status_pre` 334 |
| CTC2 vi1: the interpreter keeps 32 bits (`0x12345678`), the recompiler 16 (ours) | 1 |
| VRSQRT with ft = +/-0: the interpreter gives the clamp the sign of ft and, for fs = 0 too, raises I **and** D with Q = +/-0 | `q` 14 |
| ADD/SUB/ADDI/DADD overflow: the interpreter raises Integer Overflow (the run stops at the first such vector, like hardware), the recompiler wraps (ours wraps) | 8 (no `obs_int`) |

**Results** (`meta.summary` of the JSON; `agree` = equals the oracle; `agree-rec` = equals the recompiler where the
interpreter takes a shortcut; `disagree` = documented deliberate difference from both engines; mismatch = 0):

| Family | Ops | Vectors | agree | agree-rec | disagree (classes) |
|---|---|---|---|---|---|
| core | 58 | 552 | 552 | 0 | 0 |
| hilo | 16 | 656 | 656 | 0 | 0 |
| mmi | 94 | 890 | 827 | 8 | 55: `sa-units` 32, `phmadh-odd-words` 20, `pmfhl-reserved` 3 |
| fpu | 26 | 736 | 590 | 32 | 114: `ee-range-input` 47, `ee-range-clamp` 52 (7 with `fcr31-cause-clear`, 2 with `rsqrt-zero-sign`), `fcr31-cause-clear` 10, `maxmin-zero-order` 5 |
| vu0 | 108 | 609 | 461 | 11 | 137: `ee-range-input` 85, `ee-range-clamp` 20 (2 with `rsqrt-negative-zero-sign`), `add-alignment` 18, `maxmin-zero-order` 6, `rsqrt-zero-operands` 6, `ctc2-width` 2 |
| **total** | | **3,443** | **3,086** | **51** | **306** |

**Header changes driven by the vectors** (interpreter and manual agree against the ported upstream rule; flag and
status semantics only, no arithmetic result changes):

| Header | Rule before | Rule now | Vectors |
|---|---|---|---|
| `fpu.h` `div`/`div_nearest`/`rsqrt`/`sqrt_flags`, `div_s`/`sqrt_s`/`rsqrt_s` | x/0 and rsqrt(x, 0) set FCR31 `0x30000`; 0/0 the same; sqrt/rsqrt of a negative raised nothing | x/0 and rsqrt(x, 0) (any fs) set D + SD (`0x10020`); 0/0, sqrt(-x), rsqrt(x, -y) set I + SI (`0x20040`); bits are OR-ed, never cleared; a flushed negative denormal is -0 (no I) | `fpu_2216`, `fpu_2219`, `fpu_2259`, `fpu_2280`, `fpu_2283`, `fpu_2289`, `fpu_2273`, `fpu_2781` |
| `vu0.h` `add`...`msub` (+bc/q/i), `adda`...`msuba`, `opmula`, `opmsub` | macro-mode arithmetic left MAC/STATUS alone | MAC/STATUS updated from the written lanes (`update_mac_flags`), sticky copies kept, I/D preserved; VMAX/VMINI, VABS/VMOVE/VMR32, VFTOI/VITOF, VCLIP, the integer ops and the transfers still do not | `vu0_3417` (MAC `0x49`, STATUS `0xC3`), `vu0_3422` (dest x only), `vu0_2838` (-0 sets S and Z), `vu0_3030`, `vu0_3419` |
| `vu0.h` `div`/`sqrt`/`rsqrt` (`set_q_result`) | D (bit 5) only, no sticky bit, cleared by the next op; sqrt raised nothing | I and D cleared, then x/0 -> D + DS (bit 11); 0/0, sqrt(-x), rsqrt(x, -y) -> I + IS (bit 10); the sticky bits stay | `vu0_3280` (`0x821`), `vu0_3318` (`0x411`), `vu0_3279`, `vu0_3294`, `vu0_3380`, `vu0_3379` |
| `vu0.h` `ctc2` | wrote MAC ($17) | MAC is read-only | `vu0_3403` |

**Kept as deliberate disagreements** (both engines differ from ours; the test class predicts the PCSX2 value):

- `add-alignment` (18 VU0 vectors; the 16 FPU ones are `agree-rec:int-exact-rz-or-ee-range`): `fpu::add`/`sub` keep
  upstream's 25-binade alignment, which is exactly what PCSX2's EE recompiler computes for ADD.S/SUB.S (`fpu_2129`:
  1 - 2^-26 = 1.0, `fpu_2174`: 2^31 + -1.0 = 2^31), while the interpreter and both engines' VU path are exact
  round-toward-zero (`0x3F7FFFFF`, `0x4EFFFFFF`; `vu0_2839`, `vu0_2873`, `vu0_2994`). **Lead decision 2026-10-19:**
  ADR-0012 makes PCSX2 the *state* oracle and every capture (first_flip, atlus_logo, title C/D, the future dorm state)
  runs the recompiler, so for arithmetic rounding classes the port follows the recompiler, exactly as integration
  decision 1 did for DIV.S. Hardware truth for ADD/SUB is unknown; both observations stay in the JSON. (An exact-RZ
  `add` was tried: it moved the M1 image 70 B further from the `first_flip` capture, 50 words of 1-ULP floats.)

- `ee-range-input` / `ee-range-clamp` (130 + 65): the EE has no Inf/NaN: exponent 255 is a normal binade and the
  overflow / divide-by-zero value is +/-`0x7FFFFFFF` (manual Fmax). PCSX2 computes on host floats: such operands are
  Inf/NaN to it, results are clamped to +/-`0x7F7FFFFF`, compares see `Inf == FLT_MAX`, and the intermediate product of
  MADD/MSUB is clamped before the add. Game-visible only after an x/0 or an overflow; the difference stays within the
  magnitude's last binade.
- DIV.S rounding: DIV.S rounds to nearest here by integration decision 1 (the recompiler's game state at M1), so these
  35 vectors count as `agree-rec`; **the interpreter truncates DIV.S like every other FPU op, as the manual says** --
  a decision for the lead (`fpu_2213`: 1/3 = `0x3EAAAAAB` vs `0x3EAAAAAA`).
- `fcr31-cause-clear` (17): we only set the cause bits; the engines clear different ones. The binary never reads FCR31.
- `sa-units` (32): SA is held in bits (manual: MTSAB x8, MTSAH x16); both engines hold bytes (MFSA after `mtsab 1`
  reads 1, we read 8). QFSRV results agree for every MTSAB/MTSAH vector; the binary's MFSA/MTSA only save and restore
  the register in the exception handler.
- `phmadh-odd-words` (20): the manual leaves HI/LO words 1 and 3 undefined and we leave them unchanged; both engines
  store the odd halfword products there (PHMADH: p1, p3, p5, p7; PHMSBH: their one's complements), plausibly the
  hardware's subtractor latch -- a candidate for adoption if a trace ever depends on it.
- `pmfhl-reserved` (3): reserved formats behave as `.SH` here, the recompiler leaves rd unchanged; the decoder never
  accepts them (census: `pmfhl.lw` only).
- `maxmin-zero-order` (11): PCSX2 orders -0 below +0 and does not flush in MAX/MIN/VMAX/VMINI; we flush and return fs
  on ties. Only the sign of a zero can differ.
- `rsqrt-zero-operands` (6), `rsqrt-*-sign` (4): RSQRT with ft = +/-0 / fs = 0, see the engine table.
- `ctc2-width` (2): CLIP and CMSAR0 masked to 24 / 16 bits here, 32 in PCSX2.
- Observed but not a standing class: PCSX2 rounds sqrt(ft) to single precision inside VRSQRT (`vu0_3369`:
  `0x40000000` vs our `0x3FFFFFFF` from one double-precision expression); covered by `rsqrt-intermediate-rounding`.

Everything the game uses (`docs/ANALYSIS/08` census) lies in the `agree` set except the EE-range clamps and the
VRSQRT intermediate rounding.

**Game gate after the header changes** (`build/eevec-msvc`, Release, generated code; changes 2-5 only, `add` reverted
to the recompiler's rule; `tracediff snapshot --dead-stack <ours>/capture.json`):

| Point | Reference | After | Result |
|---|---|---|---|
| M1 `--snapshot-at sky:11` (`extracted/_ours/v_m1` -> `eevec_m1`) | frame `e3a93615...b672`, memory `5bc34218...e89f` | frame `e3a93615...b672` (identical), memory `74c2c292...220f` | 0 differing bytes with the dead-stack mask (the two images differ only below `sp`) |
| dorm `to_dorm.txt` `vblank:4900` (`dorm_replay_4900` -> `eevec_dorm`) | frame `ee0eb5da...5d85`, memory `0db8edec...a7b5` | frame `ee0eb5da...5d85` (identical), memory `5894655f...7223` | 1 differing byte: stack `0x01FFF9D4`, a saved FCR31 word `0x00830000` (C, I, D) -> `0x00830060`: the sticky SD/SI bits of change 2, stored there by the kernel HLE thread-context save (`runtime/hle/kernel/scheduler.cpp:273`, `mem_.write<u32>(f + 4u, c.fcr31)`); the game itself never executes CFC1; code 0, data 0, bss 0, heap 0 |

An exact-RZ `add` (tried before the lead decision) had moved both images: M1 by 50 one-ULP float words (and 70 B
further from the recompiler's `first_flip` capture), the dorm by 27,579 words of propagated animation/skinning state
with the frame still at PSNR 69.85 dB; that is why rounding classes follow the recompiler.

**Done 2026-10-20:** the user's state (`extracted/_ours/savestate.p2s`) sits at Mitsuru's *first* line, one line before the
route's vblank-4900 snapshot; the port's matching point is vblank 4762 (`extracted/_ours/dorm_m4_4762`). Results in
`docs/INTEGRATION_LOG.md` "Milestone 4 vs PCSX2": code 0, frame PSNR 31.0 dB, data/bss in the known classes, heap
layout identical.

## 12. Audio capture (ADR-0014 milestone 3, `tools/ours/pcsx2/audio_capture.py`)

PCSX2 2.8.2 has no PINE opcode for its media capture and the oracle ini outputs audio to the `Null` backend; the
capture records the game audio all the same (observed). The only non-interactive
path is the `ToggleVideoCapture` hotkey (unbound by default) with `[EmuCore/GS] EnableVideoCapture = false`,
`EnableAudioCapture = true`, `CaptureContainer = wav` (an audio-only 48 kHz stereo 16-bit PCM WAV in
`tools/third_party/pcsx2/videos/`). The tool treats PCSX2 as a black box:

```powershell
. .\tools\env.ps1
& $env:P3FES_PYTHON -I tools\ours\pcsx2\audio_capture.py run --name title_prompt   # --settle 8 --gap 3 (defaults)
& $env:P3FES_PYTHON -I tools\ours\pcsx2\audio_capture.py restore                    # only if a run was interrupted
```

1. `capture.check_ini()` must accept the ini as the oracle configuration; a byte copy is kept in
   `extracted/_pcsx2/audio/PCSX2.ini.before_audio_capture`.
2. The four keys above are set with `configure_ini.py`'s editor (`Hotkeys/ToggleVideoCapture = Keyboard/F7`).
3. Fast boot through `run_pcsx2.ps1 -KeepRunning`; wait for "FMV ended" in the emulog (the title, ~121 s) plus 8 s.
4. The window is foregrounded as for GS dumps; F7 starts the capture; Cross (`Keyboard/K`), Cross, Down, Cross go
   out 3 s apart (each timed against the capture start, with the game's frame counters read over PINE); F7 stops it.
5. PCSX2 is stopped, the new WAV copied to `extracted/_pcsx2/audio/<name>.wav` with `<name>.json` (key times, ini
   hashes, version, file SHA-256), and the ini restored byte for byte; its normalized hash must equal the oracle id
   (`ini_restored_equals_before`).

Run of 2026-10-19 (`title_prompt`): 15.31 s, 2,937,422 bytes, SHA-256 `13a57232…1b200`; keys at +3.063 / +6.125 /
+9.188 / +12.250 s (`g_skyFrameCount` 3345 / 3437 / 3529 / 3621); normalized ini hash before and after
**`2630dac3…782a59`** = `capture_run_D.json`'s. Re-checked 2026-10-20 before the analysis: no PCSX2 process, ini hash
unchanged. The SE onsets the RMS detector finds (`audio_ab.py onsets`) sit 40-77 ms before the key times (capture
start latency): 3.023 / 6.061 / 9.111 / 12.200 s.

Comparison with the port: `audio_ab.py compare <pcsx2.wav> <ours mix_48k.wav> --pcsx2-onsets … --ours-onsets …
--window-ms 250` and `audio_ab.py bgm …` (method in `runtime/audio/README.md` "A/B against PCSX2", numbers in
`INTEGRATION_LOG.md` "SK modules, increment 3"). The WAVs hold game audio and stay under gitignored `extracted/`.
