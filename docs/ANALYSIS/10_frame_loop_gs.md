# 10 — Frame loop, GS/DMA/VIF initialisation, display environment, double-buffering

_Phase 2 topic 10. Source: `ida/work_frame_loop_gs.i64` (copy of the master), full listing dump + Hex-Rays on the functions named below. Every address is a VA. **observed** = read from the instructions/decompilation; **inferred** = derived; **unverified** = needs the Phase 4 PCSX2 trace. Hint names (`HINT[tge-pr4]`) that this doc confirms are promoted in `symbols/deltas/frame_loop_gs.sym`._

## 0. Headline

* The renderer is **RenderWare 3.x with the PS2 "sky" driver**. The game never touches GS/DMAC/VIF registers itself: all of it happens inside `RwEngineStart` (`sub_4CA640`, renamed) → `_rwDeviceSystemRequest(rwDEVICESYSTEMSTART=2)` → **`SkyStart 0x4E1060`**, which calls libgraph/libdma (`sceGsResetGraph 0x4F8EB0`, `sceGsSetDefDispEnv 0x4F9168`, `sceGsSetDefDrawEnv 0x4F9668`/`…Env2 0x4FA558`, `sceGsSwapDBuffDc 0x4FA738` → `sceGsPutDispEnv 0x4F94E0` + `sceGsPutDrawEnv 0x4F9850`, `sceGsSyncPath 0x4F99D0`, `sceDmaSend/SendN 0x4FAC20/0x4FAC88`) and installs its own INTC/DMAC handlers (`_rwDMAHook 0x4D6470`).
* Display: **640×448, PSMCT32, NTSC, interlaced, SMODE2 = FIELD mode** (`sceGsResetGraph(0, 1, 2, 0)` @`0x4E1438`), two frame buffers at FBP 0 and FBP 140, one 16-bit Z (PSMZ16S) at ZBP 280, texture cache from page 350. RenderWare's "flicker-free interlace" mode (video mode 82, flags `0x203`) displays the same buffer on **both GS circuits** (PMODE `0x8003`, ALP=0x80, circuit 2 offset by one line, DBY=1).
* Frame pacing: no `sceGsSyncV` in the loop. `RwCameraShowRaster` queues a flip; the flip is executed by the **VBLANK_START INTC handler** `_rwDMAVSYNCHandler 0x4D47F0`; the next frame blocks in `SkyCameraBeginUpdate` → `_rwDMAWaitQueue` → `_rwDMAForceBufferSwap` until the previous frame's DMA queue drained. Atlus adds an INTC-2 handler **`kwlnVsyncFieldGate 0x19D320`** (`sub_19D320`, renamed) that returns -1 on even fields and 0 on odd fields → inferred **30 fps lock** (one flip per two vblanks). The two `T0_COUNT` reads at `0x1984F8`/`0x198508` seed the RNGs (`RpRandomSeed`, `RpRandomSeedMT`), not timing; the per-frame `T0_COUNT` reads in `kwlnUpdate`/`kwlnRootUpdateShowRasterTask` compute a CPU-load percentage against a **520 H-line (= 1/30 s) budget**.

## 1. Init sequence in execution order (observed unless marked)

### 1.1 `main 0x193980` → `initAndLoop 0x1939B0` → `kwlnMain 0x1984C0`
`main` prints `"jpx235\n"` (`0x19398C`), calls `initAndLoop(0)` (`0x198`, hint confirmed: it only calls `0x1984C0`), which calls `kwlnMain` (`main_loop_candidate`, hint `kwlnMain` confirmed by the `kwlnRoot.c`/`kwlnTask.c` strings and the task kernel it drives).

`kwlnMain` body: `kwlnInitPS2Systems 0x197030` @`0x1984C8` → `kwlnInitRenderer 0x197350` @`0x1984D0` → `kwlnInitMain 0x198010` @`0x1984D8` → loop (§3).

### 1.2 `kwlnInitPS2Systems 0x197030` (IOP reboot, timers, IRX) — size 0x31C
| VA | Call / write | Note |
|---|---|---|
| `0x19703C` | `sceSifInitRpc(0)` | |
| `0x197044` | `sceSifInitIopHeap` | |
| `0x197050` | `sceCdInit` ; `0x19705C` `sceCdMmode(2)` | |
| `0x197078` | `sprintf(buf, "cdrom0:\\LIB31\\%s;1", "IOPRP310.IMG")` | |
| `0x197084` | `sceSifRebootIop(buf)` retried until non-zero (`0x197098`) | |
| `0x1970A0` | `sceSifSyncIop` retried until non-zero (`0x1970B8`) | |
| `0x1970C4`–`0x1970E4` | `sceSifInitRpc`, `sceSifInitIopHeap`, `sceCdInit`, `sceCdMmode(2)` again | post-reboot |
| `0x1970FC` | `_sceAddIntcHandler(9 /*INTC_TIMER0*/, kwlnT0OverflowHandler 0x196FE0, 0)` | syscall 0x10 |
| `0x197104` | `sd $zero, g_kwlnT0Overflow64 (0x7CE098)` | 64-bit accumulated T0 |
| `0x19710C` | `T0_COUNT (0x10000000) = 0` | |
| `0x197110` | `T0_COMP (0x10000020) = 0` ; `0x197114` `T0_HOLD (0x10000030) = 0` | |
| `0x19711C` | **`T0_MODE (0x10000010) = 0x281`** | CLKS=1 (BUSCLK/16), CUE=1, OVFE=1 |
| `0x197120` | `T1_COUNT (0x10000800) = 0` | |
| `0x197128` | `EnableIntc(9)` | |
| `0x197148`…`0x197310` | 15× `sceSifLoadModule("cdrom0:\LIB31\*.IRX;1")`, each retried while `< 0` | SIO2MAN, SIO2D, PADMAN, DBCMAN, MC2_S1, LIBSD, CRI_ADXI (`"sdinit=0 spucore=1"`), SDRDRV, MODHSYN, MODMSIN, MODSESQ, SKSOUND, SKHSYNTH ×2, SKSESQ (`"maxtrack=16"`) — detail is topic 12 |
| `0x197320` / `0x197328` | `H_Pad_Init`, `H_Memcard_Init` | |
| `0x197330` | `_sceGetThreadId` → `g_kwlnMainThreadId 0x7CE0C8` | |

`kwlnT0OverflowHandler 0x196FE0` (hint confirmed, `sub_196FE0`): if cause==9 and `T0_MODE & 0x800` (OVF), write the bit back to acknowledge (`0x197008`) and add `0x10000` to `g_kwlnT0Overflow64` (`0x19700C`–`0x197018`); `sync; ei; return 0`.

### 1.3 `kwlnInitRenderer 0x197350` (RenderWare bring-up) — size 0xC24
| VA | Call | Note |
|---|---|---|
| `0x19736C` | `sub_4AC860(0x20, 0x20)` | RW freelist/alloc hint (unverified) |
| `0x197374`/`0x197388` | `RwEngineInit(H_Malloc_GetRwMemoryFunctions(), 0, 0x800000)` | 8 MiB RW resource arena request |
| `0x197394` | `RpPDSPluginAttach(7)` ; `0x1973C4`–`0x197ABC` 33× `RpPDSRegisterPipe 0x46A830` | pipeline ids 0x1001…0x1002B, 0x10019…0x10024 — topic 14 |
| `0x1974FC`,`0x19750C`,`0x197664`,`0x197674`,`0x197978` | `RpWorldPluginAttach`, `RpSplinePluginAttach`, `RtAnimInitialize`, `RpSkinPluginAttach`, `RpPTankPluginAttach` | |
| `0x197ADC` | **`RwEngineOpen(&{displayID=0})`** → `SkySystem 0x4E2B70` case 0 → `SkyOpen 0x4E01B0` | SkyOpen builds fog tables only; no hardware access (observed) |
| `0x197AE8` | `RpSkySelectDeepZBuffer(0)` | sets `g_skyZBufferDepth (0x7CDDD8) = 16` → PSMZ16S (`0x4D82A0`) |
| `0x197AF4` | **`RwEngineSetVideoMode(0x52)`** → `SkyUseMode 0x4DFF20` | `videoModes[82] @0x77EEC0` = {640, 448, 32, flags 0x203, 60 Hz, fmt 0x500} |
| `0x197B00` | `RwResourcesSetArenaSize(0x380000)` (`sub_4C4C00`, renamed) | 3.5 MiB resource arena |
| `0x197B08` | `sub_35ABA0` | not examined |
| `0x197B1C` | `_rwDMAPreAlloc(0x280000, 0x400, 0)` | RW DMA packet buffer 2.5 MiB (two halves) |
| `0x197B24` | **`RwEngineStart` (`sub_4CA640`, renamed)** → requests 2 (START → **`SkyStart`** §2), 3, 0x11 (`_rwSkyOverloadPipelines`) | |
| `0x197B2C` | `kwlnInstallVsyncFieldGate 0x19D360` (`sub_19D360`, renamed) | `_sceAddIntcHandler(2, kwlnVsyncFieldGate 0x19D320, 0)`, `EnableIntc(2)`; id → `0x7CC148` |
| `0x197B58`…`0x197D30` | `RpWorldCreate` (bbox ±150), 3× `RpLightCreate`/`RpWorldAddLight` | |
| `0x197D48`/`0x197D58` | `RwEngineGetCurrentVideoMode`, `RwEngineGetVideoModeInfo` | returns 640×448 |
| `0x197D6C` | `kwlnCreateMainCamera(640, 448, 1)` → `RwCameraCreate`, `RwRasterCreate(w,h,0,rwRASTERTYPECAMERA=2)`, `RwRasterCreate(w,h,0,rwRASTERTYPEZBUFFER=1)` (`0x195C80`) | camera → `g_kwlnMainCamera 0x7CE0C0` (`0x197DF4`) |
| `0x197D8C`/`0x197DA0` | far clip 25600.0, near clip 20.0 | |
| `0x197DE4` | `kwlnSetupMainCameraViewport(cam, {0,0,640,448}, 0.5)` | view window; recreates rasters if needed (`0x195980`) |
| `0x197E1C` | `printf("--->camera raster depth %d %d %d\n")` | |
| `0x197E28` | `Rt2dOpen(cam)` ; `0x197E94`/`0x197EBC` `RwHeapMalloc(0xC000)`, `RwHeapMalloc(0xA0000)` → `sub_1919C0` | |
| `0x197EE8`/`0x197F18` | image-format registration; `K_Abort("Cannot register image file format")` `0x197F50` | |

> **Correction 2026-10-18:** the pipe-registration count was given as "~30×"; counting the `jal RpPDSRegisterPipe` (`0x46A830`) sites in `kwlnInitRenderer` gives exactly **33** (first `0x1973C4`, last `0x197ABC`), as `14` §2 states (resolved in RUNTIME_CONTRACT §8.2 item 6).

### 1.4 `kwlnInitMain 0x198010` (CRI/ADX, vsync callback, ROFS) — size 0x390
`H_Cdvd_InitCd 0x198018`, `H_Cdvd_InitRtFS 0x198020`, `datInitHero`, `psStatusSpriteListInit`, `H_Sndcom_Init 0x198038`, `H_Snd_Init 0x198040`, `ADXPS2_SetupDvdFs 0x19807C`, `ADXM_SetupThrd(0) 0x198088`, `ADXPS2_SetupVoice(5,5) 0x198098`, `ADXT_Init`, `ADXCS_Init`, `ADXM_SetCbErr(kwlnAdxErrorCallback 0x197FB0)`, **`sceGsSyncVCallback(kwlnGsSyncVCallback 0x197FE0)` @`0x1980CC`** → `sceAddIntcHandler(2, cb, -1)` + `EnableIntc(2)` (`0x4FA4B8`); the callback is `ADXM_ExecVint(); sync; ei; return 0`. Then `ROFS_Init 0x198110`, `ROFS_SetCond`, `ADXF_SetupRofs`, 3× `ADXF_AddRofsVol` (`CDV:data.cvm`/`bgm`/`btl`, each retried while non-zero, `0x198148`/`0x198168`/`0x198188`), `ROFS_SetDir` ×3, `ADXF_SetDefDev` — topic 11 owns the rest.

**Three INTC-2 (VBLANK_START) handlers exist after init** (install order): `_rwDMAVSYNCHandler 0x4D47F0` (next=0, from `_rwDMAHook` @`0x4D648C`), `kwlnVsyncFieldGate 0x19D320` (next=0, @`0x19D378`), `kwlnGsSyncVCallback 0x197FE0` (next=-1, @`0x4FA528`).

> **Correction 2026-10-18:** install order confirmed from the call sequence (`RwEngineStart` @`0x197B24` → `SkyStart` → `_rwDMADmaOpen` `0x4E2710` → `_rwDMAHook` `0x4D67E0` → `jal _sceAddIntcHandler` @`0x4D648C` with `$a2=0`; `kwlnInstallVsyncFieldGate` @`0x197B2C` → `0x19D378` with `$a2=0`; `kwlnInitMain` `0x1980CC` → `sceGsSyncVCallback` → `0x4FA528` with `li $a2, -1` @`0x4FA52C`); the two `jal` VAs above were previously cited one instruction early (`0x4D6488`, `0x4FA50C`). `12` §6.5 corrected to this order; the kernel's `next` semantics remain Q-01 (resolved in RUNTIME_CONTRACT §8.2 item 3).

## 2. `SkyStart 0x4E1060` — the GS/DMA/VIF initialisation (observed from Hex-Rays; register values decoded by hand)

Execution order:

1. **`skyInitialClear 0x965770`** (13 qwords, built in `.bss`, `SyncDCache`): GIF tag `{NLOOP=1, EOP=1, PACKED, NREG=12, regs=0xEEEEEEEEEEEE (A+D)}` then `ALPHA_1(0x42)=0`, `FRAME_1(0x4C)=0x100000` (FBP 0, FBW 16 = 1024 px, PSMCT32), `SCISSOR_1(0x40)=0x03FF0000_03FF0000` (0..1023 × 0..1023), `PRMODECONT(0x1A)=1`, `TEST_1(0x47)=0x30000` (ZTE=1, ZTST=ALWAYS), `XYOFFSET_1(0x18)=0`, `ZBUF_1(0x4E)=0x1_0A00_0100` (ZBP 0x100, PSMZ16S, ZMSK=1), `PRIM(0x00)=6` (SPRITE), `RGBAQ(0x01)=0`, `XYZ2(0x05)=0`, `XYZ2(0x05)=0x3FFFFFFF` (x=4095.9, y=1023.9). Inferred: clears all 4 MiB of VRAM to black.
2. **`_rwSkyInitConfigSystem 0x4D6B10`**: `cfc2/ctc2 $vi28 (FBRST) |= 0x200` (VU1 force-break), `VIF1_FBRST (0x10003C10)=1`, `VIF0_FBRST (0x10003810)=1`, `GIF_CTRL (0x10003000)=1` (resets), `FBRST |= 2`; `sceGsResetPath 0x4F9050`: `VIF1_FBRST=1`, `VIF1_ERR (0x10003C20)=2` (ME0: mask DMAtag-mismatch error), `FBRST |= 0x200`, two `sq` of `xmmword_77F290`/`…2A0` to a VIF FIFO (target register lost by the decompiler — **unverified**, likely `VIF1_FIFO 0x10005000`), `GIF_CTRL=1`; `sceDmaReset(1) 0x4FA918`: zero the 10 libdma channel structs, `D_STAT (0x1000E010)=0`, `sceDmaPutEnv(zeros)` → `D_CTRL (0x1000E000)`, `D_PCR (0x1000E020)=0`, `D_SQWC (0x1000E030)=0`, `D_RBSR (0x1000E040)=0`, `D_RBOR (0x1000E050)=0`; then `D_CTRL |= 1` (DMAE).
3. **`sceGsSyncV(0)` @`0x4E13A4`** → no callback registered yet → `VSync 0x5035F0`: `INTC_STAT (0x1000F000) = 4`, spin `while (!(INTC_STAT & 4))`, clear again. First hard dependency on a vblank source.
4. `videoModes[82]` → `customMode 0x965730` = {640, 448, 32, 0x203, 60, 0x500}; since `flags & 0x100 == 0`: `byte_965760 = byte_965761 = 2` (two frame buffers), `byte_965763 = 1`. `skyCustomModeIsOk 0x4E0C10`: height 448 → `byte_965762 = 2` (SCE_GS_NTSC); VRAM budget check (`≤ 0x400000` bytes).
5. **`sceGsResetGraph(0, SCE_GS_INTERLACE=1, SCE_GS_NTSC=2, SCE_GS_FIELD=0)` @`0x4E1438`** (branch: `flags&4==0`, `flags&2!=0`, `flags&0x100==0`). Inside (`0x4F8EB0`): `GS_CSR (0x12001000) = 0x200` (RESET), GParam ← {interlace, mode, ffmd, CSR byte 2}, **`GsPutIMR(0xFF00)`** (syscall 0x71: mask all GS interrupts), if an old vsync handler exists `DisableIntc(2)`/`RemoveIntcHandler`, **`SetGsCrt(1, 2, 0)`** (syscall 0x02).
6. **`sceDmaSendN(sceDmaGetChan(2), &skyInitialClear, 13)` @`0x4E1458`** → GIF channel 2, normal mode: `D2_MADR = 0x965770`, `D2_QWC = 13`, `D2_CHCR = 0x101`. Then `while (sceGsSyncPath(1, 0))` @`0x4E1464` (polls `D1_CHCR.STR`, `D2_CHCR.STR`, `VIF1_STAT & 0x1F000003`, `VPU_STAT ($vi29) & 0x100`, `GIF_STAT (0x10003020) & 0xC00` until all clear; 0x1000000 iterations then prints and returns -1). `D_STAT = 4` (clear CIS2).
7. **`sceGsSetDefDispEnv(&disp[0] 0x964990, PSMCT32, 640, 448, 0, 0)` @`0x4E14CC`; `(&disp[1] 0x9649B8, …)` @`0x4E1518`.** Produced values (NTSC, interlace=1, ffmd=0, `checkModelVersion()`/`sce_GetGsDxDyOffset` offsets assumed 0 — unverified on late models):

| Register | Value | Fields |
|---|---|---|
| PMODE | `0x66` | EN2=1, CRTMD=1, MMOD=1, AMOD=1, ALP=0 |
| SMODE2 | `0x1` | INT=1, FFMD=0 (FIELD), DPMS=0 |
| DISPFB2 | `0x1400` (+FBP) | FBP=0 / 140, FBW=10 (640 px), PSM=0 |
| DISPLAY2 | DX=636, DY=50, MAGH=3, MAGV=0, DW=2559, DH=447 | `0x001BF9FF_0183227C` |
| BGCOLOR | `0` | |

> **Correction 2026-10-18:** the DISPLAY2 literal previously read `0x1BF_09FF_0193_227C`, which decodes to DH=1008/DY=306 (DH was shifted by 16 instead of 12 and the low word had `0x0193` for `0x0183`). The field list was right: `sceGsSetDefDispEnv 0x4F9168` (NTSC, interlace branch `0x4F9280`–`0x4F93BC`) builds DX = dxoff + 636 (`daddiu 0x27C` @`0x4F92A8`), DY = dyoff + 50 (`addiu 0x32` @`0x4F92A4`), MAGH = (640+0x9FF)/640 − 1 = 3 (`0x4F9290`, `0x4F92C0`), DW = 4·640 − 1 = 2559 (`0x4F92B8`, `0x4F92C8`), DH = 448 − 1 = 447 for FFMD=0 (`0x4F93A0`), and stores the 64-bit value with `sd $v0, 0x18($s3)` @`0x4F93BC` = `(447<<44)|(2559<<32)|(3<<23)|(50<<12)|636` = `0x001BF9FF_0183227C` (resolved in RUNTIME_CONTRACT §8.2 item 7 / Q-10).

8. **Draw environments**: `sceGsSetDefDrawEnv(&draw0 0x9649F0, 0, 640, 448, ztest=2, zpsm=0x3A)` @`0x4E1584`; `sceGsSetDefDrawEnv2(&draw02 0x964A70, …)` @`0x4E15F0`; `sceGsSetDefDrawEnv(&draw1 0x964B60, …)` @`0x4E165C`; `sceGsSetDefDrawEnv2(&draw12 0x964BE0, …)` @`0x4E16C8`. `zpsm = 0x3A (PSMZ16S)` because `g_skyZBufferDepth == 16`; `0x31 (PSMZ24)` otherwise. Each `sceGsDrawEnv1` is 8 A+D pairs (0x80 bytes, giftag kept separately at `0x9649E0`/`0x964B50` = `{NLOOP=16, EOP, NREG=1, A+D}`):

| Reg | Value | Fields |
|---|---|---|
| FRAME_1 (0x4C) | `FBW=10<<16, PSM=0<<24` + FBP | FBP 140 (draw0/draw02), 0 (draw1/draw12) |
| ZBUF_1 (0x4E) | `ZBP | 0xA<<24` | ZBP=280, PSMZ16S, ZMSK=0 |
| XYOFFSET_1 (0x18) | `OFX=(2048-320)<<4=0x6C00, OFY=(2048-224)<<4=0x7200` | |
| SCISSOR_1 (0x40) | `X1=639, Y1=447` | `0x01BF_0000_027F_0000` |
| PRMODECONT (0x1A) | 1 | |
| COLCLAMP (0x46) | 1 | |
| DTHE (0x45) | 0 | dither off for 32-bit |
| TEST_1 (0x47) | `0x50000` | ZTE=1, ZTST=2 (GEQUAL); clear packets later OR `0x140B` (ATE=1, ATST=5, AREF=0x40, AFAIL=1) |

9. **Buffer placement** (branch `byte_965763 != 0` @`0x4E17BC`, `0x4E17C8`–`0x4E1A2C`; FBP 140 stores `0x4E1864`/`0x4E1870`/`0x4E187C`, ZBP 280 stores `0x4E1A14`/`0x4E1A2C`…): `pages = ((640+63)&~63)·((448+31)&~31) / 2048 = 140` → `disp[1].DISPFB.FBP = 140`, `draw0/draw02 FBP = 140`, `draw1/draw12 FBP = 0`; `ZBP = 2·140 = 280` written into all four draw envs; 16-bit Z occupies 70 pages; `g_skyTexCacheStartWord (0x7CEA9C) = (280+70)<<11` → `skyTexCacheOpenCache(350 pages, rest)`.

| VRAM | Pages (8 KiB) | Bytes | Use |
|---|---|---|---|
| FB "1" (draw1/disp[0]) | 0–139 | `0x000000–0x117FFF` | 640×448×32 |
| FB "0" (draw0/disp[1]) | 140–279 | `0x118000–0x22FFFF` | 640×448×32 |
| Z | 280–349 | `0x230000–0x2BDFFF` | 640×448 PSMZ16S |
| Texture cache | 350–511 | `0x2BE000–0x3FFFFF` | RW sky tex cache |

10. **Flicker-free interlace** (`flags & 2 && flags & 0x200`, @`0x4E1A20`–`0x4E1AC0`): copies DISPFB/DISPLAY of both disp envs to the circuit-1 copies at `0x964CC0`/`0x964CC8` (disp[0]) and `0x964CD0`/`0x964CD8` (disp[1]); then on the originals (circuit 2): `DISPFB2.DBY = 1`, `DISPLAY2.DH -= 1`, `PMODE = (PMODE & 0xFFFF00FC) | 0x8003` (EN1=EN2=1, ALP=0x80). Both envs. Result: circuit 1 shows line n, circuit 2 line n+1, blended 50 % — RenderWare's vertical flicker filter.
11. **`sceDmaSend(sceDmaGetChan(1), gs_set_up 0x7B5080)` @`0x4E1AF8`** → VIF1 channel 1, **chain mode** (`D1_TADR=0x7B5080`, `D1_QWC=0`, `D1_CHCR=0x105`). Packet (observed bytes): tag `CNT qwc=1` + VIF `STCYCL(4,4)`, `STMASK` → `0`, `STMOD(0)`; tag `CNT qwc=4` + VIF `DIRECT 4` → GIF tag `{NLOOP=3, EOP, A+D}`: `TEST_1 = 0x5140B` (ATE=1, ATST=5 GEQUAL, AREF=0x40, AFAIL=1 FB_ONLY, ZTE=1, ZTST=2), `TEXA (0x3B) = 0x80<<32` (TA1=0x80), `ALPHA_1 (0x42) = 0x44` (Cs·As + Cd·(1−As)); tag `END`. A second chain at `0x7B5100` (`DIRECT 2`, giftag NLOOP=1 to register 0x7F = NOP) follows. `while (sceGsSyncPath(1,0))` @`0x4E1B04`; `D_STAT = 2`.
12. Clear-packet patching (`TEST |= 0x140B` at `0x964A60`/`0x964BD0`), unpacked copies at `0x964CE0`–`0x964D4C`, `SyncDCache`; `g_skyFrameCount (0x7CEA78) = 1`.
13. **`sceGsSwapDBuffDc(&rwDMAFlipData 0x964990, 0)` @`0x4E26C4`** → `sceGsPutDispEnv(disp[0])`: **GS privileged writes `PMODE 0x12000000`, `SMODE2 0x12000020`, `DISPFB2 0x12000090`, `DISPLAY2 0x120000A0`, `BGCOLOR 0x120000E0`** (`0x4F94E0`; the `GParam+6 == 1` branch writes `DISPFB1 0x12000070`/`DISPLAY1 0x12000080`/`EXTDATA 0x120000C0` instead — not taken here); then `sceGsPutDrawEnv(giftag0 0x9649E0)`: `D2_QWC = (NLOOP & 0x7FFF) + 1 = 17`, `D2_MADR = 0x9649E0` (SPR addresses would get bit 31), `D2_CHCR = 0x101` (`0x4F9850`; spins up to 0x1000000 on a busy channel). `while (sceGsSyncPath(1,0))`; `D_STAT = 4`. Net: display FB at FBP 0, draw to FBP 140.
14. **`_rwDMADmaOpen 0x4D67B0`**: `RwHeapMalloc(0x280000 + 128, 0x40411)`; the 128-aligned block is split into a 2 KiB header area (queue + tag templates) and two half-buffers of `((0x280000 − 2048 − 4·n) >> 1) & ~0x7F` bytes; writes DMA-tag templates (`0x11000000` = `CNT qwc=0` with IRQ, `0x30000021/22` = `REF` tags, …) at `0x964D60`–`0x964D90`; `g_rwDMASprBase (0x7CEA0C) = 0x70000000`; `SyncDCache`. **`_rwDMAHook 0x4D6470`**: `sceAddIntcHandler(2, _rwDMAVSYNCHandler 0x4D47F0, 0)` @`0x4D6488`, `sceAddDmacHandler(1, _rwDMAHandler 0x4D4350, 0)`, `sceAddDmacHandler(2, _rwDMAHandler, 0)`, `EnableIntc(2)`, `EnableDmac(1)`, `EnableDmac(2)`, `VIF0_ERR (0x10003820) |= 2`, `VIF1_ERR (0x10003C20) = VIF0_ERR | 2`, `D_CTRL &= 0xFFFFF8FD` (clear RELE, MFD, STS).
15. `setInitialRenderState 0x4DFDD0`: opens a VIF packet and `_rwSkySetRenderState(6,1)`, `(8,1)`. `SkyStart` returns 1; `RwEngineStart` then issues request 3 and `0x11` (`_rwSkyOverloadPipelines`).

**Syscalls on the init path** (numbers from `02`): `SetGsCrt 0x02`, `GsPutIMR 0x71`, `GsGetIMR 0x70` (StoreImage only), `AddIntcHandler 0x10`, `RemoveIntcHandler 0x11`, `AddDmacHandler 0x12`, `_EnableIntc 0x14`/`_EnableDmac 0x16` (behind libkernel `EnableIntc`/`EnableDmac`), `_DisableIntc 0x15`, `GetThreadId 0x2F`, `SetVSyncFlag 0x73` (only via `VSync2`, i.e. only when a vsync callback is registered), `SyncDCache 0x64`, `InvalidDCache 0x68`.

## 3. The frame loop (`0x1984E0`–`0x19853C`) — observed

```
loop:  g_kwlnRootTask (0x7CE0D0) = kwlnRootCreateTask()          ; 0x1984E0
       kwlnInitGameData()                                          ; 0x1984EC  (game state only, no HW)
       RpRandomSeed(T0_COUNT)   ; 0x1984F8/0x1984FC  LCG table (x*0x41C64E6D+0x3039), 0x136 warm-up draws
       RpRandomSeedMT(T0_COUNT) ; 0x198508/0x19850C  MT19937 state (624 words, mult 69069)
       while (kwlnTaskExists(g_kwlnRootTask)) kwlnUpdate();        ; 0x198524-0x198530 / 0x19851C
       goto loop                                                   ; 0x198538  (root task died -> soft reset)
```

`kwlnRootCreateTask 0x198940`: `RwHeapCalloc(1, 8)`, `kwlnTaskInit("rootProc", 0, kwlnRootUpdateTask 0x198650, kwlnRootDestroyTask 0x1988F0, ctx)`, `sub_109CA0(0,1)`, `sub_109CA0(1,2)`.

`kwlnUpdate 0x1983A0` (one iteration = one game frame):
* First call only (`g_kwlnFirstFrame 0x7CC134 != 0`): `T0_COUNT = 0` @`0x1983C8`, **`T0_MODE = 0x83`** @`0x1983D0` (CLKS=3 = H-BLANK, CUE=1; OVFE is dropped, so the overflow handler is effectively retired), return 1.
* Otherwise: `g_kwlnFrameStartT0 (0x7CE0FC) = T0_COUNT` @`0x1983DC`; `H_Cdvd_Update`, `H_Sndcom_Update`, `H_Snd_Update`, `H_Pad_Update` (`0x1983E8`–`0x198400`); screenshot combo check (`gPadFlags1/2`) → `K_VPad_MakeScreenshot`; else **`kwlnTaskMain 0x1949E0`** (runs the task tree; returns 0 when nothing is left → `kwlnUpdate` returns 0); `H_ResrcMan_MaybeSuspendThread`; `RwFrameSetChildUpdateFlag(1)`; `0x7CE10C++`, `0x7CE108++` (frame counters).

`kwlnRootUpdateTask 0x198650` state 0 creates the per-frame draw children in this order (`0x1986B4`–`0x1987C8`): `K_SceneDraw_CreateTasks`, `K_Spipe_Create3DDrawTask`, 2DDrawBegin, 2DDrawBeginPreEnd, 2DDrawEnd, 3DOn2DZClear, 3DOn2DDrawBegin, 3DOn2DDrawEnd, DrawBustupProc, EtcDrawBegin, EtcDraw, DrawEnd, **ShowRaster**. Subsystem view of the update functions:

| Task update fn | Does |
|---|---|
| `kwlnRootUpdate2DDrawBeginTask 0x1989E0` | `RwCameraClear(cam, kwlnGetClearColor(), flags)` @`0x198A0C`, `RwCameraBeginUpdate` @`0x198A20`, `RpSkyRenderStateSet` ×2, `sprFileManagerUpdate`, `sprSpriteDrawAll` |
| `…2DDrawEndTask 0x198B20` | `RwCameraEndUpdate` @`0x198B34` |
| `…3DOn2DZClearTask 0x198C10` | `RwCameraClear` (Z) @`0x198C3C` |
| `…3DOn2DDrawBeginTask 0x198C60` / `…EndTask 0x198D20` | `RwCameraBeginUpdate` / `RwCameraEndUpdate` around callbacks |
| `K_SPipe_Update3DDrwBeginTask 0x199520` / `…EndTask 0x1995F0` | same pattern for the 3-D scene pipeline |
| `…EtcDrawBeginTask 0x198E90`, `…EtcDrawTask 0x198F90` (`H_Fade_Main`, `H_Dbprt_*`), `…DrawEndTask 0x198FD0` | overlay pass |
| **`kwlnRootUpdateShowRasterTask 0x199140`** | screenshot path (`RwRasterLock/Unlock`, `RwImageAllocatePixels`) if armed; **`RwCameraShowRaster` @`0x199248`**; `g_kwlnFrameEndT0 (0x7CE100) = T0_COUNT` @`0x199250`; `g_kwlnFrameDeltaHsync (0x7CE14C) = float(end − start)`, `g_kwlnFrameEndHsync (0x7CE148)`; **`g_kwlnCpuLoadPct (0x7CE150) = delta / 520.0f · 100.0f`** (`0x1992DC`–`0x1992FC`); `T0_COUNT = 0` @`0x199304`; `RwFrameSetChildUpdateFlag(0)`, `H_ResrcMan_MaybeResumeThread`, `sub_10C5F0`, `mwPlySwitchToIdle`, `RpRandom` |

`RwCameraShowRaster 0x4C9ED0` → `RwRasterShowRaster` → **`SkyRasterShowRaster 0x4D9460`**: `skyTexCacheEndFrame()`, `frame = g_skyFrameCount++` (`0x7CEA78`), **`_rwDMAReqFlip(&rwDMAFlipData, frame & 1)` 0x4D5270**: opens a 24-qword VIF1 packet (`0x5000000211000000` tag + giftag `0x8001` + zeroed registers, 5 qwords ×4), `_rwDMAForceBufferSwap()` if a flip was already requested this buffer, queues entry **type 65 (flip to disp[1]) or 64 (flip to disp[0])** (`0x4D5370`), `di`, and if no DMA is in flight and no flip is pending, drives the queue inline with `_rwDMAHandler(-1)`.

### 3.1 How the frame reaches the GS and how vsync is awaited (observed in RW code; cadence inferred)
* **Queue model**: RW keeps a software queue of 8-byte entries `{type|flags, addr}` in the 2 KiB header (`g_rwDMAQueueRead` gp−17232 = `0x7CE99C`, write gp−17236). `_rwDMAHandler 0x4D4350` (DMAC ch1 **and** ch2 handler; also called inline with −1) pops entries while nothing is in flight (`g_rwDMABusyCount 0x7CE9B0 == 0`) and no flip is pending (`g_rwDMAFlipPending 0x7CE9AC`):
  * type 1 → **VIF1 ch1**: flags `& 0x300` → chain (`D1_TADR=addr`, `D1_QWC=0`, `D1_CHCR = ((hdr & 0x1300) >> 6) | 0x101` — TTE/ASP bits from the entry), else normal (`D1_MADR`, `D1_QWC=(hdr & 0xFFFF000)>>12`, `CHCR=0x101`); busy++.
  * type 2 → **GIF ch2 (PATH3)**: waits until PATH1/PATH2/VIF1/VU1 idle (same predicate as `sceGsSyncPath`), `GIF_MODE (0x10003010) = 0`, chain/normal as above with `CHCR 0x100/0x104`; busy++.
  * type 0x21 → simultaneous **VIF1 + GIF image upload**: waits idle, writes a `MSKPATH3` VIF code (`0x06008000`) to the VIF1 FIFO (`sq … 0x5000($a0)`), waits `GIF_STAT & 2`, `GIF_MODE = 4` (IMT), kicks `D2` chain (`CHCR 0x104`) then `D1` chain (`CHCR 0x145`, TTE), busy += 2.
  * type 64/65 → flip request: sets `g_rwDMAFlipPending=1`, `g_rwDMAFlipBuf (0x7CE9A8) = 0/1`, `g_rwDMAFlipData (0x7CE9A4) = addr`, stops the queue.
  * type 66 → decrement a counter at `addr` (used by `_rwDMAAddPURef` fences), 67 → nop, 79 → callback `addr(fromIrq)`, 127 → queue wrap (jump).
* **Flip**: `_rwDMAVSYNCHandler 0x4D47F0` on INTC cause 2 (VBLANK_START) with `g_rwDMAFlipPending`: reads `GS_CSR (0x12001000)` FIELD bit (13); `sceGsPutDispEnv(&disp[buf])` (`+848` FSAA variant unused); writes **`DISPFB1 (0x12000070)` / `DISPLAY1 (0x12000080)`** from the circuit-1 copies (`rwDMAFlipData + 816/824` for buf 0, `+832/840` for buf 1; `+928…952` for odd-field FSAA copies); if a per-buffer post-flip GIF chain exists at `rwDMAFlipData + 960 + 4·(buf|field)` (`0x964D50`–`0x964D5C`, all zero here) kicks `D2` (`TADR`, `QWC=0`, `CHCR=0x104`), else resumes the queue with `_rwDMAHandler(-1)`; `sync; ei; return 0`. A1 != 2 or no pending flip → only bumps a counter.
* **Throttle**: `SkyCameraBeginUpdate 0x4D84C0` → `_rwDMAWaitQueue 0x4D53F0` → `_rwDMAForceBufferSwap 0x4D4DF0`: closes the open packet (flushes it from SPR with **D8 fromSPR**: `D8_SADR 0x1000D080`, `D8_MADR 0x1000D010`, `D8_QWC 0x1000D020`, `D8_CHCR 0x1000D000 = 0x100`, after clearing `D_STAT = 0x100` and, if D8 is still busy, writing `D_PCR (0x1000E020) = 0x100` — semantics unverified), then **spins** `do { … } while (queue not drained || busy)` calling the optional wait callback `g_rwDMAWaitCallback (0x7CE95C)` (never set by this game; only zeroed at `0x4D6A74`), swaps the two half-buffers, `InvalidDCache`, `_rwDMAHandler(-1)`.
* **Cadence (inferred)**: a flip can only happen in the VBLANK_START handler, so ≤ 60 flips/s. `kwlnVsyncFieldGate 0x19D320` (installed on cause 2 **after** the RW handler, `0x19D378`) returns −1 when `CSR.FIELD == 0` and 0 when odd (`0x19D320`–`0x19D358`). Reading this as the kernel chain convention "0 terminates the chain" with handlers run most-recent-first, the RW flip executes on even fields only → **30 fps lock**, which is also what FIELD-mode interlacing of a 448-line buffer needs (both fields of a frame must come from the same buffer) and what the 520 H-line (= 525/30 Hz frame) CPU-budget metric assumes. **Corrected 2026-10-18 from the EE kernel (`15` §2, obs):** the convention is the opposite — `next = 0` puts a handler at the **head**, `−1` at the tail, the chain runs head → tail and a **negative** return stops it. The cause-2 list is therefore [`kwlnVsyncFieldGate`, `_rwDMAVSYNCHandler`, `kwlnGsSyncVCallback`]: on even fields the gate's −1 stops RW and the ADX callback, on odd fields all three run. The 30 fps lock stands; the mechanism above ("0 terminates, most-recent-first") was wrong. PCSX2 agrees: 30.012 flips/s at 59.94 Hz, 150/150 flips on callback vblanks (`docs/PCSX2.md` §9).

## 4. Other hardware touched outside RW/libgraph (from the listing scan, IDA-resolved absolute operands only)

| Register(s) | Writers | Note |
|---|---|---|
| `T0_COUNT/MODE/COMP/HOLD 0x10000000–30`, `T1_COUNT 0x10000800` | `kwlnInitPS2Systems`, `kwlnUpdate`, `kwlnRootUpdateShowRasterTask`, `Y_Misc_GetT0Count 0x4241D0` (returns `T0_COUNT`), `kwlnT0OverflowHandler` | game timer |
| `T2 0x10001000/10` | `cbTimerHandler 0x50E250` | libkernel alarm/`clock()` — topic 12 |
| `IPU 0x10002000/10`, `D3 (fromIPU) 0x1000B000/20` | `_sequenceHeader`, `_pictureCodingExtension`, `_sceMpegCscStoreRefImage`, `_ch3dmaCSC` | libmpeg (SFD video), later milestone |
| `D8 fromSPR 0x1000D000–80`, `D9 toSPR 0x1000D400–80`, `D_STAT`, `D_PCR` | `uttmxDMASPRCopy 0x10E630`, `_rptankscrMem* 0x476140+`, `rpPTankSkyIns* 0x47C240+`, `MWSPR_SaveSprByDma/Restore 0x580F10/0x580FE8` | scratchpad bulk copies |
| `GS_CSR 0x12001000` (read) | `kwlnVsyncFieldGate`, `_rwDMAVSYNCHandler`, `sceGsSyncV` | FIELD bit |

## 5. What the runtime must emulate before the first flip (Phase 3 checklist)

1. **EE kernel syscalls** used on this path with these semantics: `SetGsCrt(1,2,0)` (record mode; no other effect needed), `GsPutIMR`/`GsGetIMR`, `AddIntcHandler(cause, fn, next)` / `RemoveIntcHandler` with a per-cause **ordered handler list** (`next=0` append, `next=-1` prepend — verify) and the return-value chain rule (§3.1, verify), `AddDmacHandler(ch, fn, next)`, `_EnableIntc/_EnableDmac/_DisableIntc`, `GetThreadId`, `SyncDCache`/`InvalidDCache` (no-ops), `SetVSyncFlag` (only if a vsync callback is registered — it is, after `kwlnInitMain`).
2. **Handler calling convention**: handlers run with interrupts disabled and end with `sync; ei`; `_rwDMAHandler(cause)` receives the DMAC channel number (1 or 2) or −1 when called inline — the runtime must call DMAC handlers with the channel and INTC handlers with the cause (2 = VBLANK_START, 9 = TIMER0).
3. **INTC**: `INTC_STAT (0x1000F000)` bit 2 (VBLANK_S) set at every vblank (write-1-to-clear) so `VSync` returns; invoke the cause-2 handler chain each vblank; cause-9 (TIMER0 overflow) handler only if T0 overflow is modelled (OVFE set at `0x19711C`, retired at `0x1983D0`).
4. **Timers**: `T0_COUNT` free-running 16-bit counter; `T0_MODE` CLKS=1 (BUSCLK/16) before the first frame, CLKS=3 (H-BLANK, ~15.7 kHz) afterwards; OVF bit (0x800) write-1-to-clear. Only differences are used (CPU-load stat) — accuracy not critical, but monotonic, wrapping at 0x10000. `T1_COUNT` write must be accepted.
5. **DMAC**: channels **1 (VIF1)**, **2 (GIF)**, **8 (fromSPR)**; registers `CHCR/MADR/QWC/TADR` (+`SADR` for ch8) and `D_CTRL/D_STAT/D_PCR/D_SQWC/D_RBSR/D_RBOR`. Normal mode (MADR/QWC) and **source-chain mode** with tags `CNT (1)`, `REF (3)`, `END (7)` at least (RW templates use `0x11000000`, `0x30000021/22`, game packets use `0x10000001`, `0x70000000`); `STR` must clear on completion and the per-channel **DMAC interrupt** must fire (RW relies on it to advance its queue). `D_STAT` write-1-to-clear. Scratchpad addresses (`0x70000000` + bit 31 in MADR as libdma does at `0x4F9850`) must be understood.
6. **VIF1**: at minimum `STCYCL`, `STMASK`, `STMOD`, `DIRECT` (pass GIF data to PATH2), `NOP`, `MSKPATH3`, `FLUSH*`; `VIF1_STAT (0x10003C00)` must read 0 when idle (`sceGsSyncPath` masks `0x1F000003`); `VIF1_FBRST/VIF1_ERR/VIF0_FBRST/VIF0_ERR` writes accepted. The full `MPG`/`MSCAL`/`UNPACK` set is topic 14, needed before the first *rendered* frame but not for the first flip (`gs_set_up` uses only STCYCL/STMASK/STMOD/DIRECT).
7. **GIF**: PATH2 (from VIF1 DIRECT) and PATH3 (ch2); `GIF_CTRL (0x10003000)` reset, `GIF_MODE (0x10003010)` (0 / 4 IMT), `GIF_STAT (0x10003020)` with bits `0xC00` (P3Q/P2Q… queue) clear when idle and bit 1 (`PSE`/path-3 masked) readable; `VPU_STAT ($vi29)` bit 8 (VU1 busy) readable via `cfc2`.
8. **GS privileged registers** (`sd`/`ld` 64-bit): `PMODE 0x12000000`, `SMODE2 0x12000020`, `DISPFB1 0x12000070`, `DISPLAY1 0x12000080`, `DISPFB2 0x12000090`, `DISPLAY2 0x120000A0`, `EXTDATA 0x120000C0`, `BGCOLOR 0x120000E0`, `CSR 0x12001000` (RESET bit 9 write, **FIELD bit 13 must alternate every vblank**, byte 2 readable), `IMR 0x12001010` via syscall. The present scheme shows both circuits with ALP=0x80 — a host renderer may collapse this to "display FBP from DISPFB1 (circuit 1, DBY=0)".
9. **GS general registers via A+D** needed for the init packets: `PRIM, RGBAQ, XYZ2, XYOFFSET_1, PRMODECONT, TEXA, SCISSOR_1, ALPHA_1, DTHE, COLCLAMP, TEST_1, FRAME_1, ZBUF_1` (+ `_2` variants from `sceGsDrawEnv2`), register 0x7F ignored; a sprite clear of 1024×1024 scissored to the 1024-wide FBW=16 frame.
10. **VRAM**: 4 MiB, page/block addressing as above (FBP/ZBP in 8 KiB pages, FBW in 64-px units); layout in §2 table.
11. **Memory**: RW heap arena (8 MiB asked at `0x197388`, 3.5 MiB resource arena at `0x197B00`), 2.5 MiB DMA packet buffer, `.bss` tables `rwDMAFlipData 0x964990` (sceGsDBuffDc, ≈0x400 bytes), `customMode 0x965730`, `skyInitialClear 0x965770`; game globals at `0x7CC000`–`0x7CF000` via `$gp = 0x7D2CF0`.
12. **Interrupt-safe primitives**: `di`/`ei`, `sync`, `mfc0 Status` polling (`_rwDMAReqFlip` spins `while (Status & 0x10000 /*EDI*/)`), `cfc2/ctc2 $vi28/$vi29` (FBRST/VPU_STAT).
13. **Not required for the first flip**: VU0/VU1 execution, IPU, SIF beyond what topic 12 needs for `sceSifRebootIop`/`LoadModule` returns, CDVD beyond topic 11.

## 6. Confidence
* Init call order and VAs (§1): **high** (straight-line code, observed).
* `SkyStart` register values (§2): **high** for structure/registers, **medium** for the exact DISPLAY2/XYOFFSET constants (formula read from `sceGsSetDefDispEnv`/`DefDrawEnv`; model-dependent DX/DY offsets from `sce_GetGsDxDyOffset` not evaluated).
* Double-buffer scheme and VRAM map: **high** (page arithmetic observed, 140/280/350).
* Queue/handler model (§3.1): **high** on mechanism (decompiled), **medium** on tag-template meaning.
* 30 fps lock via `kwlnVsyncFieldGate`: **inferred, medium** — depends on kernel handler-chain semantics; Phase 4 check.
* Hardware-register inventory (§4): **partial** — only IDA-resolved absolute operands and decompiler `MEMORY[]` refs were scanned; base-register-relative accesses (e.g. libdma channel structs pointing at `0x10009000`/`0x1000A000`) are covered by the libdma analysis, others may be missed.

## 7. Open questions / blocked
1. Kernel INTC handler-chain order (`next` semantics) and return-value rule → settles the 30 vs 60 fps question. Also whether `kwlnGsSyncVCallback` returning 0 at the head would block RW's handler (it demonstrably does not in the real game, so the rule cannot be "0 stops" with head-first order).
2. Target register of the two `sq` writes in `sceGsResetPath` (`0x4F9050`, likely `VIF1_FIFO 0x10005000`) and of the `sq … 0x5000($a0)` in `_rwDMAHandler` type 0x21 — the decompiler lost the base; confirm from the instructions.
3. `sub_35ABA0` @`0x197B08` and `sub_4AC860` @`0x19736C` (RW/HAL set-up) not examined.
4. `D_PCR = 0x100` write while D8 busy (`_rwDMAClosePkt`/`_rwDMAOpenVIFPkt`) — exact intent (likely CPC8 priority/stall) unverified.
5. `sceGsSetDefDispEnv` model offsets (`checkModelVersion` reads `rom0:ROMVER`): the runtime should report an early model (offsets 0).
6. The 24 new `g_*` data labels at `$gp`-relative addresses are tails of large auto-sized items on the master (`bss_start` block `0x7CDE80`+800, `dword_7CE690`+1264, `0x7CC128`+88; `0x7CDDD8` lies inside the 24-byte hint-named `skySrcBlend 0x7CDDC8`, so either that hint is oversized or `g_skyZBufferDepth` is its third dword) — observed with `ida_bytes.get_item_head` on the copy; the lead must split those items before `set_name` succeeds (import result on the copy: 56 promotions, 6 new names, 32/32 comments, 24 data labels failed).
