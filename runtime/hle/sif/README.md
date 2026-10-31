# `runtime/hle/sif/` — SIF + "IOP" HLE (`p3fes_sif`)

ADR-0013 §3: this module owns the SIF registers, DMAC channels 5–6 and the IOP RPC servers. The EE
side — libsifcmd, libsifrpc, libcdvd, libpad, libmc2/libdbc, libsdr/SK, CRI DTX, fileio — is the
game's own recompiled code and runs unmodified; everything it talks to across the SIF is here.
Contract rows: K-14, K-29, K-30, I-01…I-42 (`docs/RUNTIME_CONTRACT.md` §3–§4). Evidence: the game's
instructions (ps2dev objdump of `SLUS_216.21`, VAs below), `docs/ANALYSIS/12_irx_rpc_threads.md`,
`11_file_io.md`. Packet layouts follow ps2sdk @ `329e2bb` (AFL-2.0; field names/offsets only, cited
per header). Nothing of the SIF/RPC model is ported from `ps2-web-recomp` (its `runtime/src/iop/sif.cpp` was read
for comparison only); the R3000 interpreter under `iop/` (§9) follows its `iop/cpu.cpp` and carries a
provenance line (`THIRD_PARTY_NOTICES.md`). Tags: **obs** read from the game, **der** derived,
**inf** inferred.

| File | Role |
|---|---|
| `include/p3fes/hle/sif/protocol.h` | register numbers, flag bits, command ids, `SifDmaTransfer_t`, sifcmd header, bind/call/end/rdata packets (encode/decode) |
| `include/p3fes/hle/sif/sif.h` | `SifHle`: register device, syscalls, SIF1 copy, SIF0 delivery, `install_sif_syscalls` |
| `include/p3fes/hle/sif/iop.h` | `IopHle` inspection/host input, `IopConfig`, `PadInput`, sound/unknown logs |
| `sif.cpp` | `SifHle` |
| `iop/iop_core.{h,cpp}` | IOP RAM + heap, sifcmd system commands, sifrpc bind/call/rdata, SIF0 queue, reboot |
| `iop/srv_system.cpp` | loadfile, heaplib, fileio |
| `iop/srv_cdvdfsv.{h,cpp}` | cdvdfsv over `CdvdHle` (`runtime/hle/cdvd.h`) |
| `iop/srv_padman.{h,cpp}` | PADMAN |
| `iop/srv_dbcman.cpp` | DBCMAN (the memory-card transport) |
| `iop/mc_mc2s1.{h,cpp}` | MC2_S1, the card driver behind DBCMAN, over `runtime/hle/memcard` (`17`) |
| `iop/srv_sdr.{h,cpp}` | SDRDRV (libsd remote) + the Standard Kit modules behind `0x90F0` (SOUND, HSYNTH, SESQ) |
| `iop/srv_adxi.{h,cpp}` | CRI_ADXI: DTX `0x90000200` (ports, urpcs), SJX, SJRMT/SJUNI, IOPRNA, the PSM mixer model feeding the host `AudioSink` (`docs/ANALYSIS/16_iop_audio_modules.md`) |
| `iop/r3000.{h,cpp}` | R3000 (MIPS I) interpreter the SK/libsd IRX modules run on (ADR-0014; §9) |
| `iop/irx_loader.{h,cpp}` | IRX ELF loader: `.iopmod`, REL relocations, import stubs / export tables |
| `iop/iop_kernel_hle.{h,cpp}` | IOP kernel HLE for the modules' imports (thbase, thsemap, timrman, intrman, sysmem, loadcore, sysclib, stdio, sifcmd): threads, semaphores, hard timers on virtual time |
| `iop/libsd_hle.{h,cpp}` | libsd HLE: 2 MiB SPU RAM + register state, silent (no voice rendered yet) |

## 1. Model

```
EE (recompiled)                         this module                                  
sceSifSendCmd ─► syscall 0x77 ─► SifHle::set_dma: copy each SifDmaTransfer_t (qword-rounded)
                                  into 2 MiB IOP RAM; a transfer to the IOP sifcmd buffer with
                                  INT_O is a command ─► IopCore::on_command ─► server
                                                                                 │ reply
sceSifCmdIntrHdlr ◄─ DMAC ch5 ◄─ HwBus::dma_complete(5) ◄─ SifHle::service ◄─ SIF0 queue:
 (0x5066B0)            (kernel, next check point)          data into EE RAM, then the
   copies the packet, clears psize,                        packet into the EE receive
   isceSifSetDChain ─► syscall −0x78 ─► SIF0 re-armed ─►   buffer (0x966980); one packet
   dispatches: _request_end / set_sreg / _sceFs_Rcv_Intr   per arming, never over an
                                                           unconsumed one
```

* **SIF1 (EE→IOP) is synchronous**: `sceSifSetDma` copies at once (ADR-0013 §3) and the IOP consumes
  each command packet immediately; `sceSifDmaStat` therefore reports every id as done (−1). Both
  pollers (`H_Sndcom_CopyToIop 0x10CCE0`, `_send_to_iop 0x511478`) only wait for `< 0` (obs).
  libsifcmd appends a 16-byte packet `{psize 16, cid 0x80000004}` (bytes at `0x7BDD00`, obs) to every
  public `sceSifSetDma`; it is counted and ignored.
* **SIF0 (IOP→EE) is queued**: an RPC end, a `SET_SREG`, a fileio result are delivered by
  `service()`, in FIFO order, only while SIF0 is armed (`sceSifSetDChain`) and the EE buffer's
  `psize` byte is 0 — exactly the hardware chain the EE re-starts in its handler (obs `0x5066F8`,
  `0x506724`). Data writes without an interrupt (rmode-0 "rend", PADMAN frames) need no arming.
* **RPC semantics** (obs, `sceSifBindRpc 0x507050`, `sceSifCallRpc 0x507230`, `_request_end
  0x506BA8`): bind → END `{cid BIND, sd, buf}` (non-zero `sd` ends every client's bind loop); call →
  server → END `{cid CALL}` with the reply as extra data to `recvbuf`; `rmode 0` (NOWAIT, no end
  function) → no END, the reply plus a 64-byte rend with `rpc_id = rec_id = 0` over the EE's packet,
  which is what `sceSifCheckStatRpc 0x507430` tests.
* **Handshakes** (obs): `sceSifInitCmd 0x506148` either sends `CHANGE_SADDR` (kernel reg
  `0x80000000` set) or waits for SMFLAG `CMDINIT`, reads SMCOM, sets `0x80000000/1` and sends
  `INIT_CMD(opt 0, buf 0x966980)`; `sceSifInitRpc 0x5068A8` sends `INIT_CMD(opt 1)` when reg
  `0x80000002` is 0 and spins on `sceSifGetSreg(0)`: the IOP answers `SET_SREG(0, 1)`.
* **Reboot** (`sceSifRebootIop 0x50CA18` → `sceSifResetIop 0x50C848`, obs order): StopDma;
  SetReg(SMFLAG, BOOTEND) **before** the 104-byte reset DMA; then SetReg(SMFLAG, SIFINIT),
  (SMFLAG, CMDINIT), (0x80000002, 0), (0x80000000, 0). EE writes to SMFLAG clear bits, so the IOP
  must raise them only afterwards: the reset packet starts a reboot that completes
  `IopConfig::reboot_cycles` (default 1 ms, ≥ 1) of virtual time later — SMCOM = sifcmd buffer,
  SMFLAG |= SIFINIT|CMDINIT|BOOTEND, heap/modules/EE-buffer forgotten. `sceSifSyncIop 0x50C9C8` polls
  BOOTEND; the post-reboot `sceSifInitRpc` takes the CMDINIT path again (B-15…B-17).
* Power-on state (inf: the IOP was booted by EELOAD): SMFLAG = `0x70000`, SMCOM = IOP buffer,
  kernel registers 0, SIF0 armed.

## 2. Integration — what the lead must wire

| Item | How |
|---|---|
| Construction | `SifHle sif(mem, kernel.bus(), IopConfig{}, disc /* open_user_disc(...) or nullptr */);` then `sif.attach()` (maps `0x1000F200–0x1000F26F`, installs ch5/ch6 handlers). |
| Syscalls | `install_sif_syscalls(kernel, sif)` → slots `0x6B 0x76 0x77 0x78 0x79 0x7A 0x7C`, both signs (template: needs `install_syscall(int, F)` with `F` constructible from `u64(EEContext&, int)` — the kernel header's current `SyscallFn = std::function<u64(EEContext&, int)>`, uncommitted, not included here). |
| `service()` caller | The kernel, at check points: whenever `Timebase::cycles >= sif.next_event_cycles()` (CDVD latency, reboot, queued packets) and after every VBLANK_START (PADMAN writes one frame per vblank). Calling it at every check point is fine (it returns at once when idle). Every SIF syscall also calls it on entry and exit, so RPC traffic flows from syscalls alone. Wired as `kernel.add_device_service([&]{ sif.service(); return sif.next_event_cycles(); })` (runtime/app/game_host.cpp). |
| D5_CHCR.STR | If the kernel's DMAC block reports channel 5 STR (read by `sceSifInitCmd 0x5062A8`), report `sif.sif0_started()`. If it reports 0, the EE simply calls `sceSifSetDChain` — also correct. |
| DMAC ch5 handler chain | Nothing to add: `dma_complete(5)` → D_STAT bit 5 → the game's `sceSifCmdIntrHdlr`. |
| Pad input | `sif.iop().set_pad_input(port, PadInput{...})` (pressed mask in libpad bit order, sticks 0x80 centred). Port 0 connected, port 1 empty by default. |
| Audio output | `sif.iop().set_audio_output(mix, tap)` with an `audio::AudioSink` (48 kHz stereo, positions from virtual time) and an optional `audio::StreamTap`; `audio::HostAudio` builds both from the host's options (`runtime/audio/README.md`). Without it the mixer still runs (consumption is EE-visible), output is discarded. |

## 3. Servers (`12` §2.1, contract §4.1)

Status: **impl** = modelled from the client's code; **stub** = answered with fixed success values;
**unk** = not modelled, answered with zeros, counted + logged once (`IopHle::unknown_events`).

| sid | Module | Row | Functions (obs client) | Status |
|---|---|---|---|---|
| `0x80000006` | loadfile | I-03, B-19/20 | `0xFF` → `"3100"` (`_lf_bind 0x50BAE8`; `0x50BBE8` rejects other versions); `0` MOD_LOAD (512 B `{arglen, modres, path[252], args[252]}`) → `{id, 0}`, ids sequential from 1 per boot, path+args recorded (`IopHle::modules`) | impl; other fns unk |
| `0x80000003` | heaplib | I-02 | 1 AllocIopHeap, 2 Free, 4 AllocSysMemory `{size, type, addr}` (first/last/at), 5 QueryMemSize = 2 MiB, 6/7 max/total free, 8/9 block queries; heap `0x80000–0x1F0000`, 256-B blocks; exhaustion → 0 (logged) | impl (6–9 numbering inf, Q-14); 3 LoadIopHeap → −1 (no caller) |
| `0x80000001` | fileio | I-01, B-49 | `0xFF` init `{EE result buf, +1088}` → `{"3100" (checked by _fs_version 0x508378), 1}`; ops accept with word0 = 1 and answer by **SIF cmd `0x80000011`** whose extra data is the result block at the EE buffer (`_sceFs_Rcv_Intr 0x507C38`): 0 open (`rom0:ROMVER` only), 1 close, 2 read (head/tail block), 3 write (fd 1/2 → log), 4 lseek | impl for those; other ops → −ENODEV (unk); other paths → −ENOENT (unk) |
| `0x80000592` | cdvdfsv init | I-04 | 0 → `{CdvdHle::init, 0x0310, 0x0310, 0}` (versions inf; `sceCdInit 0x510460` only needs major ≥ 2) | impl |
| `0x80000593` | cdvdfsv S | I-05 | 3 disk type → 0x14, 4 error, 12 status, 22 break, 34 mmode (fn/sizes from the table at `0x782728`) | impl; other fns unk |
| `0x80000595` | cdvdfsv N | I-06, L-01…L-03 | 1 read (24 B `{lsn, n, buf, rmode, remain*, readpos*}`, NOWAIT + end callback, recv 0), 5 seek, 14 N-diskready → 2 | impl; 4 gettoc etc. unk |
| `0x80000597` | cdvdfsv search | I-07 | 0, 300 B `{fp, attr, path[256] @36, eedest @292, layer @296}` → word0 found; 36 B `sceCdlFILE`+flags DMA'd to eedest | impl (date/flags inf, §5) |
| `0x8000059A/C` | cdvdfsv diskready | I-08 | 0 → 2 | impl |
| `0x80000100` | PADMAN | I-09, L-14/15 | fn 1 × {16 Init2, 15 End, 1 PortOpen, 14 PortClose, 6 SetMainMode, 8 SetActAlign, 10 SetButtonInfo, 11 SetVrefParam, 12 GetPortMax, 13 GetSlotMax, 18 GetModVersion (0x0400), 20 SetWarningLevel, 24 SetDmaCallback}; result words per wrapper (srv_padman.h); frames per vblank | impl |
| `0x80000101` | PADMAN 2nd | I-10 | bind only | impl |
| `0x80001300` | DBCMAN | I-12, L-40 | DBCMAN.IRX's table (`17` §2): `…1301` CreateSocket → +36 (links MC2_S1's device when a card is in slot 1), `…1302` Delete, `…1303` GetDepNumber, `…1304` SetWorkAddr, `…1315/1316` Init/Reset, `…1317` → 0, `…1319` SendData, `…131A` ReceiveData, `…131D` SearchPortSpecific, `…1363` 0x320; the connection table is DMA'd to the work area (`0x996F40`) on SetWorkAddr / link / unlink; others: buffer back unchanged, as DBCMAN | **impl** (`17`) |
| `0x8000131C/E/F` | DBCMAN send_data3 / send_data2 | I-13/14 | MC2_S1 commands 1–13 over the card in `IopConfig::memcard` (`p3fes_memcard`): response blocks + page data DMA'd to the socket's EE buffers, result at +1164 / +140, completed at a later `service()`; 16/17 (fast transfers, no game caller) status 0 + logged | **impl** (`17` §3) |
| `0x80000701` | SDRDRV | I-11, L-30/31 | **Modules** (default, `IopConfig::sk_mode`): every request -- the libsd codes `0x8000`–`0x8080`, `0x8F10`, `0xE620`/`0xE630` and the `0x90F0` SK blocks -- goes to the game's own `SDRDRV.IRX` handler (`+0x588`) interpreted on the kernel HLE (§9); the reply is the 16 bytes at the pointer it returns; libsd is the HLE over the SPU2 voice model (`runtime/audio/README.md`). **Constants** (increment 1, A/B): IRX `0x588`: result cleared, reply `{result, 0, 0, 0}`; libsd `0x8000`–`0x8080` with a register shadow (`0x8010` SetParam → 0), `0x8F10`/`0xE620`/`0xE630` → 0, `0x9000`–`0x90E0` unregistered → 0; `0x90F0` → SK (`16` §9): SOUND 0/1 → 0, 2 Control (`0x80`–`0x84`, `0x8F` → 0, else −310), 3, 10 Send → size (bytes kept in an SPU2-RAM shadow); HSYNTH 0 Bind → 0-based bank entry / port (−101, −201), 1 Unbind; SESQ 0 Bind → entry / the port (−202, −201), 1 Unbind, 2 Control play → track (first free), stop → 0, 3 → 0; unknown module → −310 | **impl**: the IRX answers (modules); SFX audible (voice model, milestone 2); all logged (`sound_log`) |
| `0x90000200` | CRI_ADXI | I-15, L-33 | fn 2 create (alignment/id checks, IOP buffer zeroed) → object, 3 destroy, `1024+u` urpcs 0–3, 8–13, 16/17, 34–42 (`16` §4); replies are the request buffer modified in place; DTX ports exchanged at every IOP vblank-end (`16` §3): counter EE + 1 at `wklen − 4`, whole buffer DMA'd back; SJX chunks, RNA commands, PSM consumption + mix | **impl** (`16` §10; Dolby, SJRBF/SJMEM remotes logged) |
| any other | — | — | bound with a synthetic server (non-zero `sd`, so bind loops end) | unk |

Counts: the game has **16 bind sites for 17 server ids, all answered** — 17 implemented (fileio,
heaplib, loadfile, cdvdfsv ×6, PADMAN ×2 from the client code; SDRDRV and CRI_ADXI from their
IRXs, `16`; DBCMAN ×4 with MC2_S1 behind it from their IRXs, `17`), 0 unknown. Function level: 41
modelled from the clients (loadfile 2, heaplib 8, fileio 6, cdvdfsv 12, PADMAN 13; plus the fileio
result command); from the IRXs SDRDRV 12 codes and 13 SK functions, CRI_ADXI fn 2/3 + 21 urpcs + the
two DTX ports' four callbacks, DBCMAN's 10 table functions and MC2_S1 commands 1–15 (`17` §5); 3
stubbed (heaplib LoadIopHeap, fileio 2 tuning calls); everything else answered as unknown and
logged once.

**mcserv `0x80000400` is not used by this game** (no bind site, obs: the 16 `jal sceSifBindRpc`
sites); the card path is libmc2 → DBCMAN → MC2_S1. `sceDbcGetConnection 0x51CAD0` reports connected
only if `work[socket] == 1` in the work area registered by SetWorkAddr (`0x996F40`, obs; earlier text
said `0x997140`), which only DBCMAN's DMA writes; `_sceMcFatGetInfo 0x515D80` returns `0x81010013`
when not connected. Without `IopConfig::memcard` the device stays unattached and slot 1 reads as
empty, as before. Details, validation against PCSX2 and the host's `--memcard` wiring: `17`.

**EE-side servers / handlers** (I-20…I-25): the IOP never calls them — `_sdrCB 0x80000704`
(callbacks never set, L-34), `dtx_svr_proc` (never registered), cmd `0x80000012` (cdvd power-off),
`0x80000013` (fileio power-off), `0x80000019` (pad DMA callback, never set) are never sent. The only
IOP→EE command besides RPC ends and `SET_SREG` is fileio's `0x80000011` result.

## 4. Timing

* RPC answers: queued when the call arrives, deliverable at once (the EE handler runs at the next
  kernel check point after `dma_complete(5)`).
* CDVD N-commands: `max(1, cd_fixed_latency_cycles + cd_cycles_per_sector·n)` cycles (defaults 0/0
  → the first `service()` after virtual time moves past the issuing syscall). One request in flight
  (`CdvdHle`); a refused N-command still gets its RPC end, and `sceCdGetError` reports `0x30`.
  64-byte-aligned buffers are read straight into guest RAM at completion; others via a staging
  buffer and the 144-byte head/tail block that `_sceCd_cd_read_intr 0x50F8A8` copies.
* Reboot: `reboot_cycles` (default 294,912 = 1 ms).
* PADMAN: one frame per vblank (`Timebase::vblanks` change), halves alternating, counter at +88.
* CRI_ADXI: its server pass (RNA discard, every DTX exchange) runs `IopConfig::adxi_tick_delay_cycles`
  (default 412,352 = 22 H-lines, inf) after the first `service()` that sees a new VBLANK_START — the
  IOP's vblank-end — and is the server's `next_deadline()`. The PSM mixer renders 512-frame passes
  (3,145,728 cycles each) up to "now" at every pass and every DTX RPC; DTX write-backs are SIF0 data
  items (no packet) behind whatever is queued.

## 5. Inferred (inf) — to verify in Phase 4 or from the IRX

* Register semantics: EE write to MSFLG sets, to SMFLG clears, SMCOM not EE-writable, CTRL/BD6
  store-and-read (the game never touches `0x1000F2x0` directly — 0 accesses, obs; only via syscalls).
* SIF DMA moves whole quadwords; kernel queue depth 32; `sceSifSetReg` returns the old value.
* IOP memory map (buffer addresses, heap bounds, 256-B granularity), module ids from 1, version
  words (cdvdfsv 0x0310, PADMAN 0x0400, DBCMAN 0x320 — only the checked fields are obs).
* `sceCdlFILE` reply: name = identifier as recorded (`DATA.CVM;1`, with `;1`), NUL-terminated, ≤ 15
  chars, zero padded; the **date** is the ISO directory record's (`DiscFile::recorded`) in cdvdman's mapping
  (`cdl_date_from_iso`: date[1] s … [5] month, [6..7] year LE, [0] untouched) and **flags 0** — both as the
  PCSX2 first_flip state holds them for the three CVMs (obs). Not modelled: the stale bytes the real cdvdfsv
  leaves after the name's NUL (`DATA.CVM;1` NUL `G;1`). Not-found returns the request's own first 36 bytes (as
  cdvdfsv DMAs its copy).
* PADMAN frame fields beyond what libpad reads (actuator table, model 3, bytes 8–31 = 0); a DS2
  without pressure mode reports `0x73` in analog (the brief's `0x79` is pressure mode, which the game
  never enters: `scePadEnterPressMode` has no callers); first frame lands in the second half.
* ROMVER: the user's BIOS file content `0230AC20080220\n\0` (16 B, ROMDIR, `15` §0) — a "new" model,
  so `checkModelVersion` makes the game call `_GetGsDxDyOffset` (kernel-owned offsets, `15` H-23);
  the contract's "early model" (B-49) predates `15`. Configurable (`IopConfig::romver`).
* CRI_ADXI / SK object handles (IOP addresses in the server arena, not PCSX2's `0x6D030` module or
  `0xBD400…` heap), the IOP vblank-end offset, RCV's interpolation, PSMMIX's gain scale, SESQ track
  numbering and `SOUND_Send`'s return value (`16` §10).

### Deci2Call (K-30)

`Deci2Call` (0x7C) is a DECI2 manager **without a host** (`SifHle::deci2_call`): Open (1) succeeds once per protocol
and a re-open returns `DECI2_ERR_ALREADYUSE` (−3); ReqSend/ExRecv/ExSend/ExReqSend (3/5/6/7) return
`DECI2_ERR_NOROUTE` (−10); Poll/Lock/Unlock (4/8/9) and Close (2) succeed; kputs (0x10) is logged; unknown sockets
give `DECI2_ERR_INVALSOCK`. The only client is libkernel's TTY (`sceTtyInit 0x504B00`, `sceTtyWrite 0x5048B8`, which
polls until its handler clears a busy word): returning 0 for everything (the first cut) hung `printf("jpx235")`.
The PCSX2 first_flip state's TTY block (`0x966650`: socket −3, wlen 0x14 unsent, busy 0) is what this model
produces (obs); the BIOS's own DECI2 code (`0x8000F2C0`) is not traced (inf). Error values: ps2sdk `deci2.h`.

## 6. Corrections to the analysis docs (obs, this pass)

* SK commands use libsd code **`0x90F0`** (immediate at `0x51DB74`), not `0x9100` (`12` §2.1/§2.3, L-30).
* DBCMAN server ids are **`0x80001300`, `0x8000131C`, `0x8000131E/F`** with function numbers
  `0x800013xx` (`0x51C448`, `0x51C4E8`, `0x51C514`), not `0x800014xx`.
* `sceSifResetIop` clears SMFLAG BOOTEND **before** the reset DMA (`0x50C92C` → `0x50C93C`), then
  SIFINIT, CMDINIT, `0x80000002`, `0x80000000` (`12` §1 lists the DMA first).
* `sceCdRead`'s RPC has **recv size 0**; the 144-byte block is the end-callback parameter the IOP
  DMAs into (`0x510CDC–0x510CFC`), and an N-command disk-ready (fn 14) precedes reads (`0x5100B0`).
* fileio results come back as SIF command `0x80000011` (handler added by `sceFsInit 0x5081C4`).
* loadfile and fileio both require the version string `"3100"`.

## 7. Open questions

* ~~DTX block acknowledgement~~ — resolved from `CRI_ADXI.IRX` (`16` §3): the IOP answers at its
  vblank-end pass with EE count + 1 in the word at `wklen − 4`, DMAing its whole buffer back; this
  runtime now matches PCSX2's cadence (one exchange per ADX vsync).
* SDRDRV `0xE620` / SK semantics: resolved (`16` §9); `0xE620`'s callback thread binds the EE's
  `0x80000704` on real hardware — not sent here (`16` §9.5). SPU2 voice playback for SK banks is
  not modelled (SFX silent).
* IOP-side identity values the HLE invents (server/heap/DTX addresses, SK ids, PADMAN frame fields beyond libpad's
  reads) differ from the PCSX2 state (`docs/INTEGRATION_LOG.md` "Remaining divergences" 3).
* Real cdvdfsv/cdvdman, PADMAN and DBCMAN version words, the IOP memory layout, PADMAN's exact
  power-on mode and its per-command latency in frames.

## 8. Tests

`tests/sif/` (`p3fes_sif_tests`): a fake `HwBus` and `EeSide`, a C++ re-enactment of the game's EE
side at its own addresses (`sceSifInitCmd`, `sceSifInitRpc`, `_sceSifSendCmd` + sync packet,
`sceSifCmdIntrHdlr`, `_request_end`, bind/call/check-stat, `_sceFs_Rcv_Intr`, `_sceCd_cd_read_intr`).
Covered: ps2sdk layout offsets and packet round trips; register rules; DMA ids/status/stop/dchain;
the init handshake; the reboot sequence in both orders; one packet per re-arm; rmode-0 calls;
unknown-id logging; loadfile's 15 IRX loads in order; heap; fileio `rom0:ROMVER` read byte by byte;
PADMAN frames and mode change; DBC no-card; `test_dbcman.cpp`: the memory card (ECC, NAND rules,
file system, copy-on-write, the DBC/MC2 protocol on in-test cards, `17` §7); SK/DTX ids and the sound log; `test_adxi.cpp`: the DTX
counter protocol against an EE re-enactment of `DTX_ExecHndl` (block out → nothing before the IOP's
vblank-end pass → EE count + 1 → next block), whole-buffer replies, create checks / destroy / urpc
echo, SJX chunk flow with 512-byte-per-pass consumption at 24 kHz and ordered merged returns, the
PSM volume law, mixed output values, determinism, SJUNI urpcs, pause-all, the SDRDRV/SK values of
the `H_Sndcom` flow; cdvdfsv init/mmode/disk
type/ready, aligned and unaligned reads, break, seek, refused reads, search (synthetic disc); and,
when `input/persona3fes.iso` exists, the three boot-time CVM searches against `kDiscLayout` plus 9
`manifest.json` files (3 per CVM) read through the RPC path and compared byte for byte with
`extracted/`. No game data in the repo.

## 9. SK modules in place (ADR-0014 "B-lite", increments 1–2)

The sound-effect path (`docs/ANALYSIS/19_spu2_sequenced_sound.md`) is six IRX modules the EE talks to
through SDRDRV's RPC `0x80000701`: SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN (80,592 bytes of
MIPS I text). Increment 1 made them loadable and runnable inside this module; **increment 2 routes the
live RPC traffic into them and plays what they key through a host SPU2 voice model** (`IopConfig::sk_mode
= Modules`, the default; `Constants` keeps the increment-1 replies of §3 for A/B, byte- and
fingerprint-identical to every earlier run). `docs/INTEGRATION_LOG.md` "SK modules, increment 2" has the
gate numbers.

### 9.1 Pieces

* **`iop/r3000.{h,cpp}`** -- the integer MIPS I set (SPECIAL/REGIMM/J/branches/immediates/loads/stores
  incl. LWL/LWR/SWL/SWR; no FPU/COP0/COP2: the six modules' `.text` has none, checked with ps2dev objdump),
  branch delay slots via pc/npc, no load-delay model. Runs against `IopRam` (the same 2 MiB the SIF HLE
  copies into). Stops at a return sentinel (`kExitSentinel`, what a thread entry returns to), on a trap
  (reserved word, misaligned or out-of-RAM access, `syscall`/`break`) or when the step budget is spent.
  Host calls: a stub rewritten to opcode `0x3F | id` invokes a registered `std::function`, which reads
  `a0..a3` + stack words and sets `v0`; a host call may `request_stop()` (thread switch).
* **`iop/irx_loader.{h,cpp}`** -- `.iopmod` (name, version, entry, gp, text/data/bss), one PT_LOAD copied
  to a 16-byte-aligned base, REL sections with `R_MIPS_32/26/HI16/LO16` (HI16 pairs with the following
  LO16; every HI16 in the six files is followed by exactly one LO16), import tables `0x41E00000` + stubs
  `jr ra; li $0, n`, export tables `0x41C00000` (read after relocation: MODHSYN/MODSESQ export `_start`
  at offset 0). `bind_imports` patches each stub to `j <guest export>` or a host-call word and lists what
  stayed unresolved (trapped if ever called).
* **`iop/iop_kernel_hle.{h,cpp}`** -- `IopKernel`: `load_module` (image 0x30 bytes into its block after a
  ModuleInfo record, as loadcore places it; argv block; module-start thread at priority 8 run to its
  return and then deleted; a `NO_RESIDENT_END` image is freed), a thread table with a strict-priority FIFO
  scheduler (run-to-block coroutines; StartThread/WakeupThread/SignalSema preempt a lower-priority
  runner; `i*` forms from the interrupt context do not), semaphores, hard timers (handler on an
  interrupt context at `start + compare` IOP clocks, re-armed by the handler's return value), DelayThread
  deadlines, `GetSystemTime` = EE cycles / 8, `USec2SysClock` = µs × 36,864 / 1,000, sysmem,
  `RegisterLibraryEntries` (guest libraries resolve later imports; a second registration returns
  `KE_LIBRARY_FOUND` so the game's duplicate SKHSYNTH load answers 1 as on hardware), sysclib
  string/memory functions, `printf`/`Kprintf` to the log, and sifcmd's `RegisterRpc/SetRpcQueue/RpcLoop`
  plus **`rpc_dispatch`**: the thread blocked in `sceSifRpcLoop` is handed the handler frame (`a0` fno,
  `a1` buffer, `a2` size, `ra` a host-call trampoline), runs until the handler returns and is put back
  into its wait; a handler that blocks leaves the call pending (`rpc_poll` later; never happened).
  `sceSifBindRpc` marks the client bound (`cd->server` at +36) -- SDRDRV's callback thread
  (`0x1004–0x1054`) re-binds the EE's `0x80000704` with a 10,000-iteration busy wait until that word is
  non-zero, then sleeps. `advance_to(ee_cycles)` fires what is due in deadline order and calls the time
  hook (the voice model renders up to each instant) before anything runs there. Placement:
  `set_alloc_ranges` (the modules' `AllocSysMemory` first fit in order; stacks/argv/interrupt stack from
  the last range) and `set_fixed_base` (image addresses).
* **`iop/libsd_hle.{h,cpp}`** -- the 26 libsd ordinals the modules import, now over the SPU2 voice model
  (`p3fes/audio/spu2_voice.h`): `SetParam`/`GetParam` (voice VOLL/VOLR/PITCH/ADSR1/ADSR2/ENVX, core
  MMIX/MVOLL/MVOLR…), `SetSwitch`/`GetSwitch` (KON/KOFF act, ENDX is the voices' end flags, a write
  clears it; PMON/NON/VMIX stored), `SetAddr`/`GetAddr` (SSA/LSAX/NAX; ESA/EEA/TSA stored),
  `SetCoreAttr` (MUTE honoured), `VoiceTrans`/`BlockTrans` into the model's 2 MiB of voice RAM (return
  the size), `ProcBatch` over the 8-byte records, effect attributes stored; `on_key_on`/`on_key_off`
  report every voice keyed (the `KON`/`KOFF` lines of `--sound-log`).
* **`iop/srv_sdr.{h,cpp}`** -- `SdrdrvServer`: at each loadfile request for one of the six files
  (`IopCore::load_sk_module` from `srv_system.cpp`; `MODMSIN` stays an HLE-only entry) the file is read
  (`IopConfig::module_source`, else the disc: `cdrom0:\LIB31\<name>;1` through the `DiscSource`, the
  extracted-volumes source reading `extracted/disc/LIB31/<name>`) and loaded at virtual `now`; once
  SDRDRV's thread registered `0x80000701` the binding is re-pointed (`IopCore::rebind_server`) at the
  module's `SifRpcServerData_t` (`+0x15E0`) and buffer (`+0x1C30`), so the EE's send data lands in the
  module's own buffer. `call()`: `advance_to(now)` (ticks due first), `rpc_dispatch`, reply = the 16
  bytes at the returned pointer. `tick()` (every SIF check point) advances the kernel to `now`; nothing
  adds a check point (`next_deadline` stays never): the modules consume no EE time. Any load failure or
  kernel fault falls back to the constant model, logged once.
* **`audio::Spu2Mixer`** (owned by `IopCore` in Modules mode): the PSM model's passes go into the mixer's
  stream sink instead of the host; the voices are rendered up to every IOP instant; passes
  `[g, g + 512)` on a grid anchored at frame 0 are emitted once the clock passed `g + 2,560` (the PSM
  model renders at its once-per-vblank pass, so its frontier trails the clock by up to ~1,380 frames;
  `mix_stream_late` counts frames that would still arrive late: 0), summed and clipped; silent passes stay
  gaps. `IopHle::flush_audio()` emits the last passes at exit. `runtime/audio/README.md`.

### 9.2 Memory map (`IopConfig::iop_layout`)

`Pcsx2` (default): the module images at the addresses PCSX2's dorm state has them (the ModuleInfo chain of
`extracted/_pcsx2/dorm/iopMemory.bin`, obs-P): SDRDRV `0x83230`, MODHSYN `0x84F30`, (MODMSIN `0x95530`),
MODSESQ `0x95A30`, SKSOUND `0x98630`, SKHSYNTH `0x9A030`, SKSESQ `0xB0730`, each 0x30 after its 256-byte
block; the modules' work areas in `[0x9B900, 0xB0700)`, `[0xB2200, 0xBD400)`, kernel stacks from
`[0x1F0000, 0x1FF000)`; the game's heap RPC allocations from **`0xBD400`** (`IopRam::set_heap`), which is
where PCSX2's first game allocation lands -- so the IOP addresses the EE stores (`sSndcomWork` hd/sq
`0x103800/0x110900`, `0x106100/0x111900`; `sdr_rpc_cd` server/buffer `0x84810/0x84E60`; the CRI file
table's buffers) equal PCSX2's, the "IOP identity" class of `19` §1.4. `Legacy`: the map of every snapshot
before increment 2 (heap from `0x80000`); the modules then live in `[0x1A0000, 0x1F0000)`, above the
game's allocations, and the only EE-visible change is the SK-id class (20 bytes on the dorm route).

### 9.3 What the modules needed (measured, `tests/sif/test_sk_modules.cpp`)

Load order of `12` §1 -- SDRDRV, MODHSYN, MODSESQ, SKSOUND, SKHSYNTH, SKSESQ: relocations 7/157/112/112,
243/693/278/278, 55/110/32/32, 31/128/107/107, 12/127/111/111, 10/129/118/118 (`R_MIPS_32/26/HI16/LO16`);
imports 52/24/9/34/33/33 over 7/4/4/9/7/8 libraries, all resolved (guest: sdrdrv, modhsyn, modsesq,
sksound, skhsynth; host: libsd, thbase, thsemap, timrman, intrman, sysmem, loadcore, sysclib, stdio,
sifcmd); `_start` returns 2/0/0/0/0/0 after 233/20/39/640/12,562/19,581 interpreted instructions and
registers the six libraries in that order; the duplicate SKHSYNTH returns 1 after 36 and is freed.
SDRDRV's RPC thread registers `0x80000701` (handler `+0x588`, buffer `+0x1C30`) and blocks in
`sceSifRpcLoop`; SKSOUND's start thread creates the tick thread (entry `+0xEE0`, stack 0x800, one
priority above it), `AllocHardTimer(1, 32, 1)`, `SetTimerHandler(t, 153612, +0x1140, ctx)`,
`SetupHardTimer(t, 1, 0, 1)`, `StartHardTimer` and waits on its shutdown semaphore; the handler fires
every 1,228,896 EE cycles (4,167 µs: 239 times in the first virtual second, 240 in the next, 14,398 in
a minute) and each run wakes the tick thread (~957 instructions per tick with no callbacks bound). SKHSYNTH's
start allocates five work areas (`0x1D8–0x2CC`: entries × 20, `maxport << 4`, `maxport × 1032`,
`maxport × 1368`, …) and returns 1 if one fails -- the first symptom of a too-small kernel range.

The routed `H_Sndcom` flow (same test file, through the SIF harness with the modules loaded by loadfile
requests): the bind reports `0x84810`/`0x84E60`, the first heap allocation is `0xBD400`; 141 `SOUND_Send`
chunks answer their size; `HSYNTH_Bind 3/5` → 0/0, `SESQ_Bind 0/5` → 0/0 (the port), a second
`SESQ_Bind 5` → −202, entry 7 → −201, module slot 2 → −310; `SESQ_Control(0, 0, 10, 0, 1)` → track 0,
after 100 ms (23 ticks, 132,139 instructions) 2 voices keyed (core 1, SSA inside the COMSE body at
`0x5010`) and the mix is non-silent from frame 233 (peak 10,492); a second play → track 1; stop → −302
(the one-shot had finished); every SDRDRV request went to the handler; two runs identical (requests,
cycles, key-ons, fingerprint). The legacy layout keeps the first game allocation at `0x80000` with the
modules above `0x1A0000`; without module files (no disc, a reader returning nothing) the constant replies
stay in place.

### 9.4 Host instrumentation

`--sound-log FILE` writes every `SoundRequest` (vblank, cycles, server, function, verb, payload words,
reply) through `IopConfig::sound_sink`, plus the voice model's `KON` lines (sid 0, fno 1: core, voice,
SSA, LSAX, pitch, ADSR1, ADSR2, VOLL<<16|VOLR; the result column is the timeline frame) and `KOFF` (fno
2), and the ADX model's `RNA start`/`RNA stop` (sid `0x90000200`, fno `0x8000`/`0x8001`: slot, sfreq,
channels, core; frame in the result column) -- events, not counted in `sound_requests()`. `capture.json`
carries `iop_sound_census` (requests and events by verb), `sk` (`IopHle::sk_stats`: modules on, loaded,
RPC routed/pending, tick runs, instructions, key-ons/offs, voices active, voice frames and the first voice
frame, mixer passes, late stream frames, fault) and `audio.first_non_silent_frame`. `--sk constants|modules`
and `--iop-layout legacy|pcsx2` select the model and the map.

## 10. Native input (modernize layer 2, `--native input`; `docs/MODERNIZE_PLAN.md` §3)

With `--native input` the game's own pad wrapper asks the host's pad instead of libpad: no SIF RPC reaches PADMAN
(not even the bind and the port opens), no pad frame is DMA'd into the game's buffers, and nothing models SIO2.
Without `input` nothing changes: the native branches sit behind `native::input::service()`, which is `nullptr` (the
six-route gate is byte-exact on that build).

- **Seam** (`runtime/include/p3fes/native/input_service.h`): the `PadService` interface (libpad's eight answers the
  game uses) and the inline pointer `g_service`, installed by `GameHost` while `--native input` is on. Host side:
  `runtime/native/input/native_pad.h` (`NativePad`, library `p3fes_native_input`, pure C++): per port a DUALSHOCK 2
  (digital 0x41 until the game asks for analog, then 0x73; request BUSY for one report after SetMainMode /
  SetActAlign; the actuator map) and two report slots written alternately at each VBLANK_START, the newer one
  answering -- the same answers with the same latency as PADMAN's frames in the two halves of the game's buffer, so
  the game's pad work is the same in both modes. Opening a port prepares both slots as `scePadPortOpen` prepares its
  buffer (state 5, BUSY, no data), so the first report answers at the second VBLANK_START after the open.
- **Swap points** (game side: `game/include/p3fes/game/input_native.h`, `game/src/hpad/hpad_native.cpp`):
  1. `H_Pad_Init 0x103000` (`field8_sys.cpp`): `scePadInit(0)` and the two `scePadPortOpen` -> `open(0, 0)`,
     `open(1, 0)`.
  2. `H_Pad_UpdateWorkPad 0x103110` (`sweep5a.cpp`): each of its nine libpad calls (`scePadGetState`,
     `scePadGetReqState`, `scePadInfoAct`, `scePadSetActAlign`, three `scePadSetMainMode`, `scePadRead` into
     0x7E0700, `scePadSetActDirect`) -> the service; its own state machine (record +2: 0 -> 1 -> 3 -> 4 -> 5) and
     every store to the work record are the faithful code.
  These two are the game's only libpad callers (the libpad entry points have no other caller in game/src), and
  `H_Pad_UpdateAll 0x103580` runs `H_Pad_UpdateWorkPad` for both ports every frame; everything else reads the work
  records it fills (0x7E09B0, 54 bytes per port): so this is the highest point that serves every pad read. One
  level higher (H_Pad_UpdateAll) would have to re-implement the state machine and the button-word derivations;
  one lower (libpad itself) is the platform library, not the game's wrapper.
- **What the game uses** (from the code): the DUALSHOCK's analog sticks (it asks for analog mode, locked, at
  start; the records keep lx / ly / rx / ry, `sub_103650` turns the left stick into d-pad bits, the field reads
  the stick heading); **no pressure** (`scePadEnterPressMode` has no caller, `H_Pad_UpdateWorkPad` reads bytes 0..7
  only; 0x79 is accepted but never appears); **vibration**: `sub_103B10` steps the game's pulse pattern into the
  record's actuator words +46 (small motor, on / off) and +48 (large, 0..255), and `H_Pad_UpdateWorkPad` sends
  them with `scePadSetActDirect` when they change, through the `SetActAlign` map (0x7CB270). Native: the values
  go to `NativePad`'s rumble sink; the windowed host drives the XInput pad's motors with them (small -> right,
  high-frequency motor full on; large -> left motor x 257), stopped on exit and on unplugging. **Two ports**: the
  game opens both and reads port 2 too, but `H_Pad_UpdateAll` clears port 2's held word and centres its sticks after
  every update (its record's +12 and +30..33 are the shared block's frame-edge words 0x7E09F2.. and analogue bytes
  0x7E0A04..), so only port 1 reaches the game; `NativePad` keeps port 2 unplugged, as PADMAN does.
- **Input path**: the pad feed (`runtime/app/input.h`: keyboard + XInput sampling, `--input-config`,
  `--input-script` / `--press`, `--record-input`, `--replay-input`) is unchanged and sits above both modes:
  `GameHost::host_service` takes the native report for the vblank and then latches the feed into `NativePad`
  (faithful: `feed_pad_input` into PADMAN after its frame), so a recording made in either mode replays in either.
  Port 1 is a controller, port 2 is unplugged, as PADMAN's default.
- **Machine states**: a `native-input` section (the pad model) when the layer is on; `state_config()` records
  ` native=input` so a state loads only into a run with the same set.
- **Checks**: `--vblank-dump FILE RANGES` (the guest ranges at every VBLANK_START) and
  `tools/ours/modernize/logcmp.py dumps A B [--mask=FILE]`; `tools/ours/modernize/layer2_pad_mask.txt` (the pad
  layer's own state). Tests: `tests/app/test_native_input.cpp` (the model: answers and latency, buttons, sticks, the
  keyboard / XInput mapping into a report, mode change, actuators and rumble, unplugging, two ports, state round
  trip), `tests/game/test_input_native.cpp` (H_Pad_Init / H_Pad_UpdateAll / H_Pad_UpdateWorkPad on the service),
  `tests/app/test_modernize.cpp`.

## 11. Native sound (modernize layer 3, `--native sound`; `docs/MODERNIZE_PLAN.md` §3)

With `--native sound` the game does not load `CRI_ADXI.IRX` (kwlnInitPS2Systems 0x197030) and nothing reaches its DTX
server `0x90000200`: CRI's PS2 output layer (PS2RNA) plays on the host (`runtime/native/sound`, seam
`p3fes/native/sound_service.h`, game side `game/src/cri/rna_native.cpp`; design: `runtime/audio/README.md` "Native
sound"). The `RNA start` / `RNA stop` lines of `--sound-log` then come from the native output (the same arguments).
`IopHle::adx_input()` is where its 48 kHz passes enter (the SPU2 mixer's stream input in Modules mode).

Steps 2-3 (the SK sound effects and libsd remote calls, `runtime/native/sound/sk`): the six SK modules run as native
code. With `--native-sk sif` (the default) the game's RPC traffic stays as it is and `SdrdrvServer` hands it to the
native stack (`IopHle::set_native_sk`, `SkNativeBackend`): loadfile's requests for the six modules start them at the
instant the interpreter would load them (nothing is loaded into the interpreter, `sk_stats().instructions` stays 0),
the binding points at SDRDRV's native server buffer as in §9, and `call()` / `tick()` go to the native handler and the
native SK tick. The native stack uses this model's RAM, its heap placement and libsd over the voice model through the
`native_sk_*` calls of `IopHle` (`iop/libsd_hle.h libsd_call` is the one libsd implementation both paths call; the
interpreter's host calls go through it too). With `--native-sk direct` nothing reaches SDRDRV at all (the game calls
the stack itself); `--native-sk off` keeps §9.
