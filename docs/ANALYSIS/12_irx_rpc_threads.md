# 12 — IOP modules, SIF RPC, threads/semaphores, interrupt handlers, kernel-patch payload

_Phase 2 topic 12. Database: `ida/work_irx_rpc_threads.i64` (copy of master). Every address is a VA. "observed" = read from instructions/Hex-Rays in this DB; "inferred" = conclusion drawn from it. Hex-Rays loses syscall numbers and some register args (see `04`); where an argument matters it was checked against the disassembly._

## 1. IRX loading — `kwlnInitPS2Systems 0x197030`

Called once from `main_loop_candidate 0x1984C0` (`0x1984C8`). Observed sequence (`0x197030–0x197348`):

| # | Call | Args | Notes |
|---|---|---|---|
| 1 | `sceSifInitRpc(0)` `0x19703C`; `sceSifInitIopHeap` `0x197044`; `sceCdInit(0)` `0x197050`; `sceCdMmode(2)` `0x19705C` | | pre-reboot init (binds heap RPC `0x80000003`, cdvd RPCs) |
| 2 | `sprintf(buf, "cdrom0:\LIB31\%s;1", "IOPRP310.IMG")` `0x197078` (strings `0x678510`, `0x678528`) → `sceSifRebootIop(buf)` `0x197084` | loop until return ≠ 0 (`0x197098`) | `sceSifRebootIop 0x50CA18` prefixes `"rom0:UDNL "` (`0x7BE000`) and calls `sceSifResetIop 0x50C848`: SIF command packet (104 bytes, cmd `0x80000003`, string at +24) via `sceSifSetDma`, then `sceSifSetReg(4 /*SMFLAG*/,0x40000)`, `(4,0x10000)`, `(4,0x20000)`, `(0x80000002,0)`, `(0x80000000,0)` |
| 3 | `sceSifSyncIop` `0x1970A0` loop until ≠ 0 (`0x1970B8`) | | |
| 4 | `sceSifInitRpc(0)`, `sceSifInitIopHeap`, `sceCdInit(0)`, `sceCdMmode(2)` again (`0x1970C4–0x1970E4`) | | post-reboot re-bind |
| 5 | `AddIntcHandler(9, kwlnT0OverflowHandler 0x196FE0, 0)` `0x1970FC`; `*(gp-0x4C58)=0` (64-bit tick); `T0_COUNT=0`, `T0_COMP=0`, `T0_HOLD=0`, `T0_MODE=0x281` (CLKS=1 BUSCLK/16, CUE, OVFE) `0x19711C`; `T1_COUNT=0` `0x197120`; `EnableIntc(9)` `0x197128` | | game time base (see §4.3) |
| 6 | 15 × `sceSifLoadModule(path, arglen, args)` `0x197148–0x197310`, each in a `bltz $v0 → retry` loop | see table | **a negative result retries forever**; the HLE must return ≥ 0 for every load, including the duplicate SKHSYNTH |
| 7 | `H_Pad_Init 0x103000` `0x197320`; `H_Memcard_Init 0x18F100` `0x197328`; `GetThreadId` → `*(gp-0x4C28)` `0x197338` | | main thread id saved |

Module order and arguments (observed):

| # | Path string (VA) | arglen | args |
|---|---|---|---|
| 1 | `cdrom0:\LIB31\SIO2MAN.IRX;1` `0x678540` | 0 | – |
| 2 | `SIO2D.IRX` `0x678560` | 0 | – |
| 3 | `PADMAN.IRX` `0x678580` | 0 | – |
| 4 | `DBCMAN.IRX` `0x6785A0` | 0 | – |
| 5 | `MC2_S1.IRX` `0x6785C0` | 0 | – |
| 6 | `LIBSD.IRX` `0x6785E0` | 0 | – |
| 7 | `CRI_ADXI.IRX` `0x678600` | 0x14 | `"sdinit=0 spucore=1"` `0x678620` |
| 8 | `SDRDRV.IRX` `0x678640` | 0 | – |
| 9 | `MODHSYN.IRX` `0x678660` | 0 | – |
| 10 | `MODMSIN.IRX` `0x678680` | 0 | – |
| 11 | `MODSESQ.IRX` `0x6786A0` | 0 | – |
| 12 | `SKSOUND.IRX` `0x6786C0` | 0 | – |
| 13 | `SKHSYNTH.IRX` `0x6786E0` | 0 | – |
| 14 | `SKHSYNTH.IRX` `0x6786E0` (second load, `0x1972DC`) | 0 | – |
| 15 | `SKSESQ.IRX` `0x678700` | 0x18 | `"maxtrack=16\0maxentry=16\0"` `0x678720`/`0x67872C` (two NUL-separated args) |

Not loaded although on disc: `MODMIDI.IRX`, `SKMIDI.IRX`, `SKMSIN.IRX` (no string references).

`sceSifLoadModule 0x50C4E8` → `_sceSifLoadModule 0x50C2C0`: `_lf_bind 0x50BAE8` binds loadfile RPC `0x80000006` then `sceSifCallRpc(cmd 0xFF, send 0, recv 4)` = version; the load is `sceSifCallRpc(cd 0x96A0C0, cmd 0 /*LF_F_MOD_LOAD*/, send 0x969EC0 512 bytes, recv 8)` with the ps2sdk `_lf_module_load_arg` layout: `+0 arglen/result`, `+4 modres`, `+8 path[252]` (`0x969EC8`), `+260 args[252]` (`0x969FC4`). Return = module id (`senddata` `0x969EC0`), `*modres = 0x969EC4`.

Failure handling: none — every step loops until success. Confidence: **high**.

## 2. SIF RPC inventory

### 2.1 IOP servers bound by the EE (`sceSifBindRpc 0x507050` sites)

| RPC id | IOP module | Bind site | Commands observed (cmd: send→recv bytes) |
|---|---|---|---|
| `0x80000001` | fileio (IOPRP) | `sceFsInit 0x508170` (`0x50822C`) | `sceOpen/Read/Close/...` via `sceFsSifCallRpc 0x507AD8` (retries with `DelayThread`). Game users: `H_Cdvd_RtFsHdd_* 0x102900+` (host/HDD dev paths), RenderWare `sub_4C08A0`, CRI `SRD_Sce* 0x558C98+`, **`checkModelVersion 0x4F90B8` reads `rom0:ROMVER`** (libgraph NTSC/PAL default) |
| `0x80000003` | heaplib/sysmem (IOPRP) | `sceSifInitIopHeap 0x50B598` (`0x50B5E4`) | `1` AllocIopHeap(size) 4→4 (`0x50B620`); `2` FreeSysMemory(addr) 4→4 (`0x50B710`); `3` LoadIopHeap(path,arg) (`0x50B7A8`); `4` AllocSysMemory(type,size,addr) 12→4 (`0x50B690`, buffer `0x969D80`, result `0x969D40`); `5` QueryMemSize 0→4 (`0x50B898`); 6–9 the remaining Query* (`0x50B908–0x50BA68`, numbers not individually checked). Game callers: `H_Sndcom_Update 0x10CDD0` (AllocSysMemory(0,size,0) ×6, FreeSysMemory), CRI `PS2RNA_Init 0x55FF70` (AllocIopHeap 2256 and `(max_voice<<10)+64`), `SJX_Init 0x564528`, `ps2rna_init_psj 0x55F748` |
| `0x80000006` | loadfile (IOPRP) | `_lf_bind 0x50BAE8` (`0x50BB1C`) | `0xFF` version 0→4; `0` MOD_LOAD 512→8 (§1). `sceSifLoadElf*`, `StopModule`, `Unload`, `SearchModule*` linked but unreferenced |
| `0x80000592` | cdvdfsv init | `sceCdInit 0x510460` (`0x51052C`) | `0` 4→16 |
| `0x80000593` | cdvdfsv S-cmd | `_sceCd_scmd_prechk 0x510258` (`0x510334`) | topic 11 |
| `0x80000595` | cdvdfsv N-cmd | `_sceCd_ncmd_prechk 0x50FF58` (`0x510034`) | `1` = `sceCdRead 0x510B80`: 24-byte `sceCd_ncmdsdata`, **async** (`mode 1`) with end-callback `sceCd_cd_read_intr` and 144-byte rdata; topic 11 |
| `0x80000597` | cdvdfsv searchfile | `sceCdLayerSearchFile 0x50FC38` (`0x50FD04`) | `0` 300→4 |
| `0x8000059A` | cdvdfsv diskready (old) | `sceCdDiskReady_old 0x510748` (`0x510834`) | `0` 4→4 |
| `0x8000059C` | cdvdfsv diskready | `sceCdDiskReady 0x510960` (`0x510A20`) | `0` 4→4 |
| `0x80000100` | PADMAN | `scePadInit 0x511138` (`0x51119C`, cd `0x96DCC0`) | every libpad call is **cmd 1, 128→128 bytes, buffer `0x96DF00`**, word0 = function: `16` Init2 (`0x5112D0`, word5=`0x782754`), `15` End (`0x5113C8`), `1` PortOpen(port,slot,dmabuf) (`0x511590`; returns word3 at `0x96DF0C`; word5 = IOP-side buffer addr saved for `_send_to_iop`), `14` PortClose (`0x511778`), `6` SetMainMode(port,slot,mode,lock) (`0x511FB8`), `8` SetActAlign (`0x512138`), `10` SetButtonInfo (`0x5122C0`), `11` SetVrefParam (`0x5124A0`), `12` GetPortMax (`0x512570`), `13` GetSlotMax (`0x5125D8`), `18` GetModVersion (`0x512640`; init checks major==4, `0x511164`), `20` SetWarningLevel (`0x5126A8`), `24` SetDmaCallback (`0x512710`) |
| `0x80000101` | PADMAN (2nd server) | `scePadInit 0x511138` (`0x5111F0`, cd `0x96DCE8`) | bound; **no `sceSifCallRpc` on it** (legacy) |
| `0x80000701` | SDRDRV (libsdr) | `sceSdRemoteInit 0x512868` (`0x51289C`, cd `0x96E040`) | `sceSdRemote 0x5129C0`: RPC cmd = libsd function code; args copied to 64-byte block `0x96E000` (word0 = block addr, words1–6 = args); default path sends the block (64) and receives 16 into it. Special cases `0x8130/0x81A0/0x81B0` (send 64 from arg2), `0x8140` (recv 64 into arg2), `0x81C0/0x81D0` (send `8*(n+1)` from arg1), `0x8160/0x8170` (local only). **Game uses only**: `0x8010` SetParam — `(0x800,4032)`,`(0x801,4044)` from `H_Sndcom_Init 0x10CAC0`; `(0x980,0x3FFF)`,`(0xA80,0x3FFF)`,`(0x981,0)`,`(0xA81,0)` from `sceSkSsInit 0x51DA50`; `0xE620` callback-init with six `0x780000` args (`sceSdRemoteCallbackInit 0x512D48`); `0x9100` SK extension — arg1 = EE address of a 64-byte command block, arg2 = 64 (§2.3) |
| `0x80001300` (earlier text: `0x80001400`; corrected 2026-10-18 from the bind site) | DBCMAN (libdbc) base | `sceDbcInit 0x51C3B8` (`0x51C44C`, cd `cd_base`) | all 144→144 on buffer `0x996840`: `0x80001401` CreateSocket (`0x51C770`), `0x80001402` DeleteSocket, `0x80001403` GetDepNumber, `0x80001404` SetWorkAddr(`sif_dma_buf`) (`0x51C700`, called from init), `0x80001405` GetIopDmabuff, `0x80001415` InitSocket, `0x80001416` ResetSocket, `0x80001417` GetDeviceStatus, `0x80001418` SRData, `0x80001419` SendData, `0x8000141A` ReceiveData, `0x8000141D` SearchPortSpecific (`0x51CDD8`, used by `sceMc2SearchSocket 0x513478`), `0x80001463` GetModVersion (init requires `ver>>4 == 50`, `0x51C480`) |
| `0x8000131C` (was `0x8000141C`; corrected 2026-10-18) | DBCMAN send_data2 | `sceDbcInit` (`0x51C4EC`) | `sceDbcSendData3 0x51D308`: cmd = seq, **async** (mode 1), 1168-byte buffer `0x996900`, end-callback = `sceMc2SifCallback 0x51AE38` (→ `iSignalSema(sceMc2_sema_subs)`). This is the memory-card page path: `_sceMcCoreReadPage2 0x51B708`, `WritePage 0x51B8F0`, `ReadPageFast 0x51BD10`, `WritePageFast 0x51BF40`, `BlockErase 0x51BBD8`, `GetCardSpec 0x51AFD8`, `CheckNewCard 0x51B1B0`, `Authentication 0x51B3B0`, `ReadClock 0x51B5F0`, `WriteBack 0x51B4A0`, `WriteSameData 0x51BA88`, `ClearNewCardFlag 0x51B2C0` |
| `0x8000131E`, `0x8000131F` (was `0x80001 41E/F`; corrected 2026-10-18) | DBCMAN send_data3[0..1] | `sceDbcInit` (`0x51C55C`, loop `v4<2`) | `sceDbcSendData2 0x51D158`: async 144→144 (no game caller) |
| `0x90000200` | CRI_ADXI (DTX) | `DTX_Init 0x559AA8` (`0x559AEC`, id `dtx_rpc_id 0x7A1144`, cd `unknown_libname_355`) | `dtx_create_rmt 0x559588` cmd 2 16→4; `dtx_destroy_rmt 0x5595F8` cmd 3 4→0; `DTX_CallUrpc 0x559C10` cmd = `urpc+1024`, send `4*nsend` words from `0x9979C0`, recv `4*nrecv` into `0x997AC0`. Urpc ids: `0` SJX_Create, `1` SJX_Destroy, `3` SJX_Init, `8` PS2RNA create, `9` destroy, `10` psm init, `11` restore IOP snd, `12` init IOP snd (sfreq, default 48000), `13` finish, `14/15` Dolby on/off, `16/17` start/stop PCM trans, `32–42` SJRMT (rbf/mem/uni create, destroy, uuid, reset, get/unget/put chunk, numdata, isgetchunk) |

Not an RPC: `sceSifGetOtherData 0x506D88` has no callers.

### 2.2 EE-side RPC servers (IOP → EE) and SIF command handlers

| Mechanism | id | Handler | Created by | Status |
|---|---|---|---|---|
| `sceSifRegisterRpc` | `0x80000704` | `_sdrCB 0x512FF0` on thread `_sdrCBThread 0x512F80` (queue `0x96F0C0`) | `sceSdRemoteCallbackInit 0x512D48` ← `sceSkSsInit(32)` ← `H_Sndcom_Init` | **live**; `_sdrCB` dispatches word0 bits `0x100/0x200` (trans intr core0/1) and `0x400` (SPU2 IRQ) to callbacks set by `sceSdRemote 0x8160/0x8170` — which the game never calls, so it never has work |
| `sceSifRegisterRpc` | `0x90000200` | `dtx_svr_proc 0x559508` | nobody (no xrefs) | dead |
| `sceSifAddCmdHandler` | `0x80000008/9/A/C` | `request_end 0x506BA8`, `request_bind 0x506F80`, `request_call 0x5071A0`, `request_rdata 0x506CB8` | `sceSifInitRpc 0x5068A8` | sifrpc core; `request_end` is how every `sceSifCallRpc`/`BindRpc` completes (`iSignalSema` or end-callback) |
| `sceSifAddCmdHandler` | `0x80000019` | `_pad_intr_hdr 0x511288` | `scePadInit2 0x5112D0` | calls the `scePadSetDmaCallback` user cb (never set) |
| sifcmd system | `0x80000000` change_addr, `0x80000001` set_sreg | `sceSifInitCmd 0x506148` | | handshake: `sceSifInitRpc` sends `0x80000002` and spins on `sceSifGetSreg(0)` |
| `sceSifSendCmd` | `0x80000019` | | `scePadEnd 0x51143C`, `cdvd_exit 0x50FAC0` | shutdown only |

DMAC ch5 (SIF0) handler `sceSifCmdIntrHdlr` installed by `sceSifInitCmd 0x506148` (`0x5062D0`); it is the only interrupt-driven RPC completion path.

### 2.3 Shared-memory / direct-SIF protocols

* **libpad DMA buffers (IOP → EE)**: `scePadPortOpen(port,slot,buf)` requires a 64-byte-aligned 256-byte EE buffer (`0x51159C`); PADMAN writes two 128-byte frames into it and `scePadGetDmaStr 0x511830` selects the frame whose frame counter (`+88` vs `+216`) is newer. Game buffers: `sPad0Port`, `sPad1Port` (`H_Pad_Init 0x103084/0x10309C`). Actuator commands go **EE → IOP** by direct `sceSifSetDma` (`_send_to_iop 0x511478`: 32-byte packet into the IOP buffer returned by PortOpen word5, double-buffered on frame parity).
* **libsifcmd `sceSifSetDma` (`0x506088`)** = the public API (`isceSifSetDma 0x506110`); both append a 16-byte "sync" packet via `sceSifSetDmaInternal 0x505FC0` (FLIRT had this as `sceSifInitCmd`; corrected, see §7). Direct users besides libpad: `H_Sndcom_CopyToIop 0x10CCE0` (request `{src,dst,size,0}` at `0x833640`, busy-waits `sceSifDmaStat`) and CRI `DTR_ExecHndl`/`DTR_ExecServer 0x559140`/`DTR_Stop 0x5593A8` (ADX stream data EE → IOP).
* **Sound bank upload** (`H_Sndcom_Update 0x10CDD0`, 6 slots × 17 words at `sSndcomWork 0x833710`, per-slot file triple `tbl_H_Sndcom_BankFiles 0x5D53A0[3*idx+{0,1,2}]`): header file → `sceSifAllocSysMemory` + `H_Sndcom_CopyToIop` (kept in IOP RAM, `+7/+8`); body file → IOP temp → `sceSkSsSOUND_Send(1, iop, spuaddr, n)` in ≤ 4096-byte (state 5) or ≤ 65536-byte (state 8) chunks → `sceSifFreeSysMemory`; sequence file → IOP RAM (`+11/+12`). SPU2 RAM is budgeted on the EE by `sceSpu2MemAllocate 0x51D6F8` (614400 + 716800 + 4×102400 bytes, `0x10CBB0–0x10CC2C`). Then `sceSkSsHSYNTH_Bind(3,-1,hd,hdsize,spu,bdsize)`→id, `HSYNTH_Bind(5,-1,id,0)`→id2, `SESQ_Bind(0,-1,sq,sqsize)`→id3, `SESQ_Bind(5,id2,id3)`→ctl (`0x10D2A8–0x10D3B4`). Playback: `SESQ_Control(ctl,0,10,seq)`→h (`H_Sndcom_PlayVoice 0x10DB60`), stop `SESQ_Status(ctl,1,10,h)`; `SESQ_Control(ctl,2,10,h)` (`H_Sndcom_StopVoice 0x10DA70`); unbind `SESQ_Unbind(5,x)`, `SESQ_Unbind(0,y)`, `HSYNTH_Unbind(5,z)`, `HSYNTH_Unbind(3,w)` (`H_Sndcom_UnbindSfx 0x10D950`). Init: `SOUND_Control(0,143,0)`, `(3,131,261)`, `(3,132,60)`, `(3,130,1)`, `(3,128,127)` (`0x10CAE0–0x10CB90`).
* **SK command block** (64 bytes, `sceSdRemote(1,0x90F0,blk,64)` (code **0x90F0** per the instruction at `0x51DB74`; corrected 2026-10-18 — earlier text said 0x9100)): word0 = module (`0` SOUND `0x782B80`, `0x1000000` HSYNTH `0x782BC0`, `0x4000000` SESQ `0x782C00`), word1 = function (SOUND: `2` Control, `10` Send; HSYNTH: `0` Bind, `1` Unbind; SESQ: `0` Bind, `1` Unbind, `2` Control, `3` Status), words2+ = arguments; result = first word of the 16-byte reply (`sceSdRemote` return). Observed at `0x51DB00–0x51E0DC`.

Confidence: **high** for ids/commands; **medium** for the SK/SDRDRV semantics (names come from promoted hints + argument shapes; the IOP side was not disassembled).

## 3. Pad, memory card, OSD params

* **Pad**: `scePadInit(0)` then `scePadPortOpen(0,0,sPad0Port)` and `(1,0,sPad1Port)` (`0x103084`, `0x10309C`) — two ports, slot 0, no multitap. Per frame `H_Pad_UpdateWorkPad 0x103110`: `scePadGetState`; state machine over `scePadSetMainMode(port,slot,mode 0/1)` (DUALSHOCK lock), `scePadInfoAct(-1)`, `scePadSetActAlign(gp-0x7A80)`, `scePadGetReqState`, `scePadRead(port,slot,&sRDataPort1)`, `scePadSetActDirect` (vibration, 6 bytes). Pressure mode is **not** used (`scePadEnterPressMode`/`InfoPressMode` have no callers). Button data consumed as `~byte[2..3]` (digital), bytes 4–7 analog, id byte `0x7E0701` must be `0x79` (DUALSHOCK2), `0x73` (DUALSHOCK) or `0x41` (digital).
* **Memory card**: `H_Memcard_Init 0x18F100`: `sceDbcInit`, `sceMc2Init(0)`, `sceMc2CreateSocket({2,2,0}, sMemcardMc2Socket)` → handle at `gp-0x4CCC`. libmc2 keeps the FAT on the EE (`basic_thread 0x5145F8` dispatches `sceMcFat*` by request code 2–15/32/33) and reaches the card only through DBC page RPCs (§2.1). Game sequence `H_Memcard_UpdateSeqMode 0x18F2C0` (states 0–13): `GetInfo` → `SearchFile("/BASLUS-21621Save%d/BASLUS-21621Save%d")` (`0x18F4FC`; variants `SaveG%d`, `BASLUS-21569`, `BASLUS-99998/99999` under `datGetFlag(5154)`, strings `0x5E4840–0x5E4B20`) → optional `Format` → `Mkdir("/BASLUS-21621Save%d")` (`0x18FAD4`) → `CreateFile` (`0x18FEB8`) → `WriteFile(icon.sys, 964 bytes from 0x846780)` (`0x1900A0`), `WriteFile(icon.ico, bytes of disc file "camp/icon.ico" 0x5E4B40)` (`0x1901CC`), `WriteFile(save, buf gp-0x4CC8, size gp-0x4CC0)` (`0x1904A4`); completion polled with `H_Memcard_Check 0x18F190` (`sceMc2CheckAsync`). Loads: `sub_190720`/`sub_190CD0`/`sub_191260`/`sub_191660` use `GetInfo`, `SearchFile`, `ReadFile`. **Recommended HLE boundary: the `sceMc2*Async` API (`0x513598–0x514510`) + `sceMc2CheckAsync 0x514900`, not the DBC RPC.**
* **OSD/Gs param syscalls**: `GetOsdConfigParam/SetOsdConfigParam` (`0x4B/0x4A`) are used only by `PatchIsNeeded 0x50D718` (§5). `GetGsHParam/VParam`, `SetGsHParam/VParam` (`0x4C–0x4F`) have **no callers**.

Confidence: **high**.

## 4. Threads, semaphores, timers, interrupt handlers

### 4.1 Thread table (every `CreateThread` site; `_sceCreateThread 0x502F60` xrefs)

| Entry | Creator (site) | Priority | Stack base | Size | Start arg / notes |
|---|---|---|---|---|---|
| main (crt0 `SetupThread`) | `start 0x100008` | kernel default → `ADXM_SetupThrd` sets **24** (`0x5406D4`, default `dword_788664`) | `0x1F60000–0x2000000` | | |
| `topThread 0x503E60` (libkernel) | `InitThread 0x503F38` ← `crt_init_runtime 0x50D658` | 0 | `mainThreadStack 0x965D00` | 1024 | arg `&mainThread`; waits `mainThreadSema`; services `iWakeupThread`/`iRotateThreadReadyQueue`/`iSuspendThread` deferred requests |
| `H_Resman_ThreadProc 0x10C7D0` | `H_ResrcMan_Init 0x10C050` (`0x10C140`; loop creates 1) | 28 | `sResrcManThreadStack 0x803640` | 0x20000 | arg = control block `gp-0x4DC0` {u16 go, ptr}; `SleepThread` until `H_ResrcMan_Update 0x10C5F0` sets go=1 and `WakeupThread` (`0x10C73C`); `ResumeThread` from `H_ResrcMan_MaybeResumeThread 0x10BFF0`; both called per frame from `kwlnRootUpdateShowRasterTask 0x199140`. Loads RW streams (`RpWorldStreamRead`, `RpClumpStreamRead`, `RwTexDictionaryStreamRead`, …) off the CDVD request queue |
| `adxm_safe_proc 0x53FB00` | `adxm_SetupSafeThrd 0x540178` | created at main prio, then **8** | `adxm_stack_safe 0x788770` | 2048 | suspended immediately |
| `adxm_vsync_proc 0x53FBF0` | `adxm_SetupVsyncThrd 0x5402D8` | **16** | `0x789F70` | 4096 | woken by `adxm_iWakeupThread` from `ADXPS2_ExecVint 0x540D80` (odd-field VBlanks only, 30 Hz: the callback sits behind `kwlnVsyncFieldGate` in the cause-2 chain and a negative return stops the chain — `15` §2.4; corrected 2026-10-18); runs `SVM_ExecSvrVsync`, `ADXPS2_WakeupMainThrd` |
| `adxm_fs_proc 0x53FCF8` | `adxm_SetupFsThrd 0x540360` | **18** | `0x78AF70` | 4096 | woken by `adxm_iWakeupThread(adxm_id_fs)` from `ADXPS2_ExecVint 0x540D80` (INTC 2, on odd-field VBlanks — 30 Hz, `15` §2.4 — when `dword_788690` is not already 1); runs `SVM_ExecSvrFs` — **this is the thread that issues the data-path `sceCdRead 0x510B80` (topic 11)**. The read is RPC `0x80000595` cmd 1 in async mode; completion arrives on DMAC 5 → `sceSifCmdIntrHdlr` → `request_end` → end-callback `_sceCd_cd_callback 0x50F698`, which must `iSignalSema(sceCd_ncmd_semid 0x780BA8)` and clear `sceCd_c_cb_sem 0x780BB4` (`0x50F6E4–0x50F72C`); the thread itself only sleeps on the next VBlank |
| `adxm_mwidle_proc 0x53FDE8` | `adxm_SetupMwIdleThrd 0x5403E8` | **25** | `0x78BF70` | 0x2000 | suspended at setup; resumed by `adxm_vsync_proc`/`ADXPS2_ResumeIdleThrd 0x540ED8` |
| `_sdrCBThread 0x512F80` | `sceSdRemoteCallbackInit 0x512D48` ← `sceSkSsInit(32) 0x51DA50` | **32** | `0x96E080` | 4096 | RPC server `0x80000704` (§2.2) |
| `basic_thread 0x5145F8` (libmc2) | `sceMc2Init 0x5130E8` (`0x5131FC`) | **1** | `0x96F680` | 0xC000 | `WaitSema(sceMc2_sema_start 0x96F664)` → run request `0x96F144` → `SignalSema(sceMc2_sema_end 0x96F668)` |
| `adxm_usrvsync/usridle_proc` | only `ADXM_SetupThrdEx 0x5411B0` | | | | **not created** (game calls `ADXM_SetupThrd(0)` at `0x198068`) |
| `sceCd_cbLoop` | `sceCdInitEeCB 0x50F808` | | | | **not created** (no callers) |
| `dtx_svr_proc` | – | | | | **not created** |

Order at boot: topThread (crt), then `kwlnInitPS2Systems 0x197030` (`jal` @`0x1984C8`, first call in `kwlnMain`) → `H_Memcard_Init 0x197328` → `basic_thread`; then `kwlnInitMain 0x198010` (`jal` @`0x1984D8`, after `kwlnInitRenderer` @`0x1984D0`): `H_Sndcom_Init` → `_sdrCBThread`; `ADXM_SetupThrd(0)` → safe/vsync/fs/mwidle; `H_ResrcMan_Init` → resman. Priorities are the final values after each setup's `ChangeThreadPriority`.

> **Correction 2026-10-18:** this paragraph previously placed `kwlnInitMain`'s threads before `kwlnInitPS2Systems` ("first frame of `main_loop_candidate`"). `kwlnMain 0x1984C0` is straight-line: `jal kwlnInitPS2Systems` @`0x1984C8` → `jal kwlnInitRenderer` @`0x1984D0` → `jal kwlnInitMain` @`0x1984D8` → `jal kwlnRootCreateTask` @`0x1984E0`, so `basic_thread` (libmc2) is created before the sound/ADX threads; `10` §1.1 and §1 above were right (resolved in RUNTIME_CONTRACT §8.2 item 2 / Q-12).

### 4.2 Semaphores (`_sceCreateSema 0x503160` xrefs; `{max, init}`)

Game/engine: `RwFsInit 0x4BFBB0` (`0x95FF30`, {1,1}, RenderWare file lock), `viBufCreate 0x594130` ({1,1} per Sofdec video buffer, +64). SDK persistent: `SceKernelLibc`×2 {1,1} (`supplement_crt0 0x50D408` → `0x77FBD0/0x77FBD4`), `SceKerneltopThread` {255,0} (`mainThreadSema`), `SceCdNcmdSema/ScmdSema/RcmdSema` {1,1}, `SceCdCallbackSema` {1,0} (`cmd_sem_init 0x50F960`), `sceMc2_sema_main` {127,1}, `_start` {127,0}, `_end` {127,0}, `_subs` {127,0} (`0x5130E8`, `0x51AE68`), `sceDbc_sema` {127,1} (`0x51C5A8`), `SceStdio*Sema` (fileio, `0x507960–0x50B4C8`). Transient (created/deleted per call): `SceSifrpcBind`/`SceSifrpcCall` {1,0} (`0x5070CC`, `0x507388`), `SceKernelDelayThread` {1,0} (`0x504220`).

Interrupt-context signals (`iSignalSema`): `request_end 0x506C48` (RPC completion), `_sceFs_Rcv_Intr 0x507FD4`, `_sceCd_cd_callback 0x50F6E4/0x50F70C`, `sceMc2SifCallback 0x51AE48`, `_DelayThreadHandler 0x504420`; `iWakeupThread` from `request_call 0x50721C` (server side).

### 4.3 Timers and alarms

* **T0** = game time base (`0x19710C–0x19711C`): CLKS=1 (BUSCLK/16), OVFE; `kwlnT0OverflowHandler 0x196FE0` on INTC 9 adds `0x10000` to the 64-bit counter `gp-0x4C58` when `T0_MODE.OVFF`. T1_COUNT is zeroed and otherwise unused here.
* **T2** = libkernel alarm engine: `InitTimer(2) 0x50DCB0` ← `crt_init_runtime`: `AddIntcHandler(11, cbTimerHandler 0x50E250)`, `T2_MODE = CLKS 2 (BUSCLK/256) | CMPE | OVFE` (+CUE on first start), 128 alarm slots `0x96D380`; `StartTimerSystemTime 0x50DEF0`. Clients: `DelayThread 0x5041D8` (`SetTimerAlarm 0x50F090` → `_DelayThreadHandler` → `iSignalSema`) used by `sceFsSifCallRpc` and `sceCdSync/SyncS 0x510148/0x5101E8`; sifrpc retry alarms `iSetTimerAlarm(2048, _alarm_bind/_alarm_rdata)` (`0x507030`, `0x506D70`).
* **T3**: only read by `InitAlarm 0x50DB38` (`T3_MODE & 0x100`) to decide whether to install the kernel alarm patch (§5).
* Kernel `SetAlarm/iSetAlarm/ReleaseAlarm` syscalls (`0xFC–0xFF` wrappers `0x502EE0–0x502F50`) have **no callers**.

### 4.4 Interrupt handlers

| Source | Handler | Installed by | Behaviour |
|---|---|---|---|
| INTC 2 VBLANK_START | `kwlnVBlankStartHandler 0x19D320` | `kwlnInstallVBlankStartHandler 0x19D360` ← `kwlnInitRenderer 0x197350` (`0x197B2C`); `EnableIntc(2)` | `sync; ei`; returns 0 when `GS_CSR.FIELD`=1 else −1 (field tracking only) |
| INTC 2 | `_rwDMAVSYNCHandler 0x4D47F0` (fes-pc-recomp "vblankStartHandler" confirmed) | `_rwDMAHook 0x4D6470` ← `_rwDMADmaOpen 0x4D67B0` | RenderWare sky: if a flip is pending, `sceGsPutDispEnv` of the back buffer, writes `DISPFB1/2` (`0x12000070/0x12000080`), kicks the deferred GIF packet on DMAC ch2 (`0x1000A030/A020/A000=0x104`) or calls `_rwDMAHandler(-1)` |
| INTC 2 | `kwlnGsSyncVCallback 0x197FE0` | `sceGsSyncVCallback 0x4FA4B8` ← `kwlnInitMain 0x1980CC` (`AddIntcHandler(2, cb, -1)`) | `ADXM_ExecVint → ADXPS2_ExecVint 0x540D80`: `adxm_iWakeupThread` of vsync/fs threads, `ADXMNG_CallVintServerFunctions` |
| INTC 9 TIM0 | `kwlnT0OverflowHandler 0x196FE0` | `kwlnInitPS2Systems` | §4.3 |
| INTC 11 TIM2 | `cbTimerHandler 0x50E250` | `InitTimer` | libkernel alarms (§4.3) |
| DMAC 1 VIF1, DMAC 2 GIF | `_rwDMAHandler 0x4D4350` | `_rwDMAHook` (`0x4D64B4`, `0x4D64D4`); the hook also sets `VIF0_ERR/VIF1_ERR` (`0x10003820`, `0x10003C20`) bit 1 (ME0) and clears `D_CTRL & 0x702` (`0x4D6550–0x4D6570`) | RenderWare DMA queue completion |
| DMAC 5 SIF0 | `sceSifCmdIntrHdlr` | `sceSifInitCmd 0x506148` (`0x5062D0`), `EnableDmac(5)` | SIF command dispatch → RPC completion |
| DMAC 3 IPU_FROM | `_ch3dmaCSC 0x5022D0` | `_doCSC2 0x501C38`, `_sceMpegCscStoreRefImage 0x501DF8` (transient) | libmpeg colour-space conversion (Sofdec video) |

> **Correction 2026-10-18:** the DMAC row previously named `0x10003820`/`0x10003C20` "VIF1_FBRST/GIF_CTRL"; on the EE those addresses are `VIF0_ERR`/`VIF1_ERR` (`VIF1_FBRST` is `0x10003C10`, `GIF_CTRL` is `0x10003000`). `_rwDMAHook 0x4D6470`: `lw $a2, 0x10003820; ori $a2, 2; sw $a2, 0x10003820` (`0x4D6548`–`0x4D655C`), `lw $a2, 0x10003820; ori $a2, 2; sw $a2, 0x10003C20` (`0x4D6560`–`0x4D6568`), then `D_CTRL 0x1000E000 &= 0xFFFFF8FD` (`0x4D656C`–`0x4D6578`), as `10` §2.14 says (resolved in RUNTIME_CONTRACT §8.2 item 4 / Q-13).

Polling paths that need INTC_STAT bits even with handlers disabled: `VSync 0x5035F0` (clears/polls `INTC_STAT & 4`), `VSync2 0x503680` (`SetVSyncFlag` syscall), both via `sceGsSyncV 0x4F9938`. `sceGsResetGraph 0x4F8EB0` and `_rwDMAUnhookPrimitive 0x4D6700` call `DisableIntc(2)`/`DisableDmac(1,2)`.

Confidence: **high** (threads/handlers), **medium** (semaphore purposes inside SDK code are inferred from names).

## 5. Kernel-patch payload (`crt_init_runtime 0x50D658`)

`crt_init_runtime`: `supplement_crt0 0x50D408` → `InitSystemCallTableAddress 0x50D548` → `InitAlarm 0x50DB38` → `InitTimer(2) 0x50DCB0` → `StartTimerSystemTime 0x50DEF0` → `InitThread 0x503F38` → `InitExecPS2 0x50D780` → `InitTLBFunctions 0x50CC78` → clears reboot buffers. This is the stock SCE SDK 3.1 libkernel `_InitSys` sequence, **not game-specific** (all functions carry agreeing snaku/tge-pr4 hints and no game code references them).

| Patch | Condition | Installs | Payload copy (`Copy` syscall 0x5A after `SetSyscall(0x5A, kCopy*)`) | Then |
|---|---|---|---|---|
| `InitSystemCallTableAddress` | always | `SetSyscall(0x83, kFindAddress 0x50D4C0)`, `SetSyscall(0x5A, kCopy_0 0x50D488)` (table `0x77FBC0`) | – | `FindAddress(0x80000000, 0x80010000, kFindAddress/kCopy_0)` locates the kernel syscall table (`dword_77FBB8` = match − 524 / − 360) for `GetSystemCallEntry 0x50D510` (unused) |
| `InitTLBFunctions` | always | `(0x5A, kCopy 0x50CC20)`, `(0x5B, 0x80075000)`, `(0x54, _kExitTLBHandler 0x50D180)` (table `0x77F8E8`) | `0x77F568` → `0x80075000`, 816 bytes (`kpayload_tlb`) | `SetSyscall(n, GetEntryAddress(n))` for n = 0x55..0x59 (TLB functions); `dword_77F8E0 = GetEntryAddress(3)` (kernel arg area used by `SetArg 0x50D880`) |
| `InitExecPS2` | `PatchIsNeeded 0x50D718` ≠ 0: sets OSD-config bits 13–15 to 1 and reads back; patch needed when they read 0 (old ROM) | `(0x5A, kCopy_1 0x50D6D0)`, `(0x5B, 0x80074000)` (table `0x780380`) | `0x77FBD8` → `0x80074000`, 1960 bytes (`kpayload_execps2`) | one entry: `SetSyscall(0xFFFFC402, GetEntryAddress(0xFFFFC402))` — a negative index, i.e. patches a kernel word at `table − 0xEFF8` (the kernel's `ExecPS2` path) |
| `InitAlarm` | `(T3_MODE & 0x100) == 0` (kernel without alarm support) | `(0x5A, kCopy_3 0x50DAF0)`, `(0x5B, 0x80076000)` (table `0x780B08`) | `0x7803A0` → `0x80076000`, 1856 bytes (`kpayload_alarm`); `0x780AE0` → `0x00082000`, 40 bytes (T3 interrupt stub: `lui $sp,8; jalr $v1; ...`) | `SetSyscall(n, GetEntryAddress(n))` for n = 0xFC, 0xFE, 0xFD, 0xFF, 0x12C, 0x08 |

The 9 "unreferenced functions" Ghidra found in `0x77F710–0x780A08` (`06`) are inside these three payload blobs; they execute in kernel mode at the kseg0 addresses above, never at their file VAs. The replacement `GetEntryAddress` (`0x7803A0`) looks up a 6-entry `{id, addr}` table at `0x80076710`.

**What Phase 3 must do (inferred):** emulate the **stock, modern kernel**: make `PatchIsNeeded` false (OSD config bits 13–15 round-trip), report `T3_MODE` bit 8 set, and implement `SetSyscall` (0x74), `Copy` (0x5A), `GetEntryAddress` (0x5B), `FindAddress` (0x83) and `FlushCache` as benign operations (kseg0 writes into the low 1 MiB must be accepted; `0x82000` too). After `_InitSys` the game never calls the patched syscalls: TLB syscalls 0x55–0x59 are only reached from `InitTLB 0x50CE00` ← `TerminateLibrary` (dead), `ExecPS2/LoadExecPS2/ExecOSD` have no callers (`Exit 0x50DA58` ← `_exit`/`kill`), and `SetAlarm` family has none. Trapping them with a diagnostic is sufficient. Confidence: **high**.

## 6. Runtime contract (what the HLE must answer)

1. **IRX loader**: `sceSifRebootIop`/`sceSifSyncIop` must succeed (SIF regs `0x80000000/2`, SMFLAG `4` semantics for `sceSifInitRpc` handshake: `GetReg(0x80000002)==0` → send cmd `0x80000002`, spin on `GetSreg(0)≠0`); 15 `LF_F_MOD_LOAD` calls returning ≥ 0 (duplicate SKHSYNTH included); fileio `0x80000001` must serve `rom0:ROMVER` for `checkModelVersion 0x4F90B8`.
2. **RPC servers**: `0x80000003` (heap: 1,2,4,5), `0x80000006` (0, 0xFF), cdvdfsv `0x80000592/593/595/597/59A/59C` (topic 11), PADMAN `0x80000100` cmd 1 functions {16,15,1,14,6,8,10,11,12,13,18,20,24} + two-frame 256-byte EE pad buffer per port + 32-byte actuator packets by direct SIF DMA, SDRDRV `0x80000701` functions {0x8010, 0xE620, 0x9100 → SK blocks §2.3}, DBCMAN `0x80001400` family + `0x8000141C` async page I/O (or HLE at `sceMc2*Async`), CRI DTX `0x90000200` cmds 2, 3 and `1024+urpc` for the ids in §2.1. EE server `0x80000704` exists but never needs to be called.
3. **Threads**: table §4.1 (9 threads incl. main/topThread); scheduler needs priorities 0,1,8,16,18,24,25,28,32, `SleepThread/WakeupThread/iWakeupThread`, `Suspend/ResumeThread`, `RotateThreadReadyQueue`, `ReferThreadStatus` (ADXM reads current priority), `ExitDeleteThread`.
4. **Semaphores**: §4.2; `iSignalSema` from the RPC-completion and DMA paths.
5. **Interrupts to fire**: INTC 2 (VBLANK_START) → three handlers (order of installation: RW sky `_rwDMAVSYNCHandler` with `next=0` @`0x4D648C`, game field gate `kwlnVsyncFieldGate` with `next=0` @`0x19D378`, `kwlnGsSyncVCallback` with `next=-1` @`0x4FA528`) and `INTC_STAT` bit for `VSync` polling; INTC 9 (T0 overflow, every 2^16 ticks at BUSCLK/16); INTC 11 (T2 compare/overflow at BUSCLK/256); DMAC 1, 2 completions (RW), DMAC 5 (SIF0, every IOP→EE command), DMAC 3 only during MPEG CSC. VBLANK_END is unused.
6. **Syscalls**: those in §5 plus `SetVSyncFlag` (0x73), `GsGetIMR/GsPutIMR`, `GetOsdConfigParam/Set` (0x4A/0x4B), `GetThreadId`, `ChangeThreadPriority`, `DIntr/EIntr` (inlined `di/ei`).

> **Correction 2026-10-18:** item 5 previously gave the install order as "game field handler, RW sky, GsSyncV callback". The call sequence is `kwlnInitRenderer`: `RwEngineStart` @`0x197B24` → `SkyStart` → `_rwDMADmaOpen` (`0x4E2710`) → `_rwDMAHook` (`0x4D67E0`) → `_sceAddIntcHandler(2, _rwDMAVSYNCHandler, 0)` @`0x4D648C` **first**; `kwlnInstallVsyncFieldGate` @`0x197B2C` → `_sceAddIntcHandler(2, kwlnVsyncFieldGate, 0)` @`0x19D378` **second**; `kwlnInitMain` @`0x1980CC` → `sceGsSyncVCallback 0x4FA4B8` → `_sceAddIntcHandler(2, cb, -1)` @`0x4FA528` **third**. The ELF only shows the `next` argument each site passes (0, 0, −1); the kernel's resulting chain position and return-value rule stay open as Q-01 (Phase 4). `10` §1.4 was right (resolved in RUNTIME_CONTRACT §8.2 item 3).

Confidence: **high** for the inventory (every item traces to a site above); the cdvdfsv command set is topic 11's, and IOP-side behaviour of SDRDRV/SK/DBC commands is inferred from the EE marshalling only.

## 7. Naming changes and conflicts

* FLIRT `sceSifInitCmd @0x505FC0` was wrong (it builds the DMA list + sync packet); renamed `sceSifSetDmaInternal` (tge-pr4 hint, verified) and `sceSifInitCmd_0 @0x506148` → `sceSifInitCmd` (installs DMAC 5 handler, cmd buffer). `sub_506088`/`sub_506110` → `sceSifSetDma`/`isceSifSetDma` (libsifcmd public API; the 16-byte syscall thunks keep their `_sce*` names).
* FLIRT `sceSkSsHSYNTH_Unbind*/sceSkSsSESQ_Unbind*` collisions replaced by the hint names verified from the command words: `HSYNTH_Bind 0x51DC70` (fn 0), `HSYNTH_Unbind 0x51DD48` (fn 1), `SESQ_Bind 0x51DDF0` (0), `SESQ_Unbind 0x51DEB0` (1), `SESQ_Control 0x51DF58` (2), `SESQ_Status 0x51E028` (3).
* Types (`symbols/types/irx_rpc_threads.h` + `.apply.txt`, 10 structs / 20 addresses): `KPatchEntry` (the four SetSyscall tables), `SceThreadParam` (`0x96DA18`), `SceSemaParam` (`0x95FF30`), `SceSifRpcClientData` (5 client descriptors), `SceSifDmaData` (`0x833640`, `0x96DFC0`), `LfModuleLoadArg` (`0x969EC0`), `PadRpcBuf` (`0x96DF00`), `SdrRemoteArgBlock` (`0x96E000`), `SkCmdBlock` (×3), `HSndcomSlot[6]` (`0x833710`).
* Promoted community hints (second pass, 47 rows): every `H_*`, `kwln*`, `adxm_*`, `_rwDMA*`, `DTX_*/DTR_*/PS2RNA_*` function cited above whose behaviour was read here (listed with `ev=` anchors in the delta).
* New: `kwlnT0OverflowHandler 0x196FE0` (promoted), `kwlnInstallVBlankStartHandler 0x19D360`, `kwlnVBlankStartHandler 0x19D320`, `H_ResrcMan_Update 0x10C5F0`, `H_Sndcom_CopyToIop 0x10CCE0`, patch tables/payloads (§5), RPC client/buffer globals (see `.sym`).

## 8. Open questions / blocked

* IOP-side semantics of SDRDRV function `0xE620` and the SK `SOUND_Control` parameter ids (143, 128–132) need the IRX disassembly (`LIB31/SDRDRV.IRX`, `SKSOUND.IRX`) — not done (EE-only scope).
* `0x80000003` commands 6–9 and loadfile `0xFF` meaning assumed from ps2sdk, not checked against `IOPRP310.IMG`.
* The save-data payload size (`gp-0x4CC0`) is set by the caller of `H_Memcard_UpdateSeqMode` (`sub_41D330 0x41D330`), not resolved here.
* Whether `kwlnVBlankStartHandler` returning −1 vs 0 affects the kernel's handler chain should be confirmed against PCSX2 (Phase 4).

> **Correction 2026-10-18 (PCSX2 observation, `docs/PCSX2.md` §save-state checks):** the title-screen save state shows the **alarm kernel-patch payload present** at `0x80076000` (1,856/1,856 bytes) with its `0x82000` stub (40/40), i.e. `InitAlarm`'s `T3_MODE & 0x100` gate evaluated **false** under PCSX2 and the patch was installed — the "gate true → skipped" reading above was wrong for this emulator (real hardware unverified). The ExecPS2 payload at `0x80074000` is absent (gate `PatchIsNeeded` false, as predicted) and the TLB payload at `0x80075000` is present (unconditional, as predicted). The runtime verdict is unchanged: no game code references the patched alarm syscalls `0xFC–0xFF`, so emulating the stock kernel remains correct; the runtime must simply not trap on `InitAlarm`'s `Copy`/`SetSyscall` sequence.
