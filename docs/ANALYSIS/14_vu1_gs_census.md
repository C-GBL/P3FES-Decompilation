# 14 — VU1 microcode inventory, VIF/GIF packet builders, GS register census, RenderWare pipelines

_Phase 2 topic 14. Legend: **[obs]** observed in the ELF bytes or an IDA/Hex-Rays/Ghidra result on this machine · **[der]** derived by our scripts from observed data · **[inf]** inference. All addresses are VAs (`VA = file_offset + 0xFFF80`, confirmed from the ELF program header [obs]). Scripts: `vu1_scan.py`, `gs_static_scan.py`, `vu1_ida*.py` (scratchpad copies; outputs under `ida/logs/vu1/`, gitignored). Database copy `ida/work_vu1_gs.i64`; the master was not opened._

## 0. Headline

- **114 VU1 microprograms, 114 distinct SHA-256, 984,760 bytes of microcode** (123,095 64-bit instructions) sit in the data band `0x5A1D80..0x77DD0C` as RenderWare DMA `ret` packets [obs]. Every one has the layout `DMAtag(ID=ret, QWC) | VIF NOP | VIF MPG` followed by 2048-byte MPG pieces separated by `MPG`+`NOP` codes; piece addresses are consecutive from VU1 micro address 0 [obs]. fes-pc-recomp's "181 programs / 172 distinct / 421 uploads" counted pieces heuristically; the packet view gives 114 programs from **539 `MPG` codes** (all 539 chain into the 114 packets; 0 orphans) [der].
- **86 programs are reachable from pointer tables** (RW PS2All "VU1 code arrays", §2); **28 programs (`0x5A1D80..0x5C7750`) have no pointer, no `lui/addiu` and no table reference anywhere in the image** [der] -> linked-but-unused library code [inf]. The Phase 3 interpreter must still load them if the game ever MPGs them, but no static path does.
- All transform work is RenderWare 3.7 **PS2All** pipelines registered through **RpPDS** (`kwlnInitRenderer 0x197350` registers 33 pipes [obs]). The game has no hand-written VIF/GIF builders outside RW: the only `MSCAL/MSCNT/MSCALF/DIRECT/UNPACK` constant sites outside `rw*/rp*/sky*` are the CRI Sofdec/IPU sequence header (`_sequenceHeader 0x4feee0`, 4 `DIRECT`) and five `sub_2C8xxx/0x2CCF60/0x306E80` sites (`MSCALF`/`MSCNT`) [obs, §3].
- GS state is set by two RW shadow-register funnels: `_rwSkySetRenderState 0x4d6b90` (RW render states -> TEST_1/TEX1_1/CLAMP_1/FOGCOL/ALPHA shadows, flushed as 1-register A+D packets via `_rwDMAOpenVIFPkt`) and `RpSkyRenderStateSet 0x4d7f60` (raw ALPHA_1, alpha-test half of TEST_1, DIMX, 2 globals) with **665 call sites** [obs]. ALPHA_1 census from the call sites: `0x44` (Cs-Cd)*As+Cd x219, `0x48` additive x75, `0x42` subtractive x5, `0x6A` Cd-only x5, `0x58` x5, `0x54`/`0x64`/`0x06`/`0x2024` x1 each; 19 sites take a register value [der, §4].
- Frame buffer: RW video mode **82 = 640x448x32, flags 0x203, 60 Hz, format 0x500 (8888)** (`RwEngineSetVideoMode(82)` at `0x197350`, table `videoModes 0x77e710` [obs]); `RpSkySelectDeepZBuffer(0)` [obs] → 16-bit Z (PSMZ16S); frame/Z placement (FBP 0/140, ZBP 280) is fixed by `SkyStart` for mode 82, texture `TBP/CBP` are dynamic (§5, corrected 2026-10-18).

Reconciliation with topic 13 (NOP-signature bands `0x5A2000–0x5CA000`, `0x6B6000–0x77A000`): the packet inventory extends both bands — `0x5A1D80` (first ret tag) to `0x5CDB1C` (PTank/null programs `0x5C9F30..0x5CDB10` lie above `0x5CA000`) and `0x6B5E90` to `0x77DD0C` (Rt2d `0x738D20..0x7437C0` inside, PTank transform programs `0x77CB40..0x77D910` above `0x77A000`); the NOP signature misses short programs with few `nop` pairs [der].

Static GIF-tag scan of the data band found **no A+D packets** (2,580 noisy REGLIST/IMAGE-shaped candidates, all inside microcode or float data) [der]: every GS register packet in this game is built at run time by code.

## 1. VU1 microprogram inventory [obs/der]

Packet = `ret` DMA tag at VA (QWC in qwords), VIF codes in the tag's upper 64 bits (`00000000 4Axx0000` = NOP, MPG num=xx addr=0). Dumps: `ida/logs/vu1/<code_va>.bin` (gitignored; the file is the concatenated microcode, named by the VA of the first `MPG` code = tag+12). Columns: units = 64-bit instructions; E = instructions with the E bit; XGK = `xgkick` count; family/index = membership in the code arrays of §2 (`-` = unreferenced).

Tag check: 114 of 114 packets have `ID=ret` and `QWC*16 == microcode + inter-piece codes (+8 pad)` [der].

| # | tag VA | QWC | units | bytes | pieces | E | XGK | br | SHA-256 (first 16) | family / array index | name |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 0 | `0x5a1d80` | 63 | 126 | 1008 | 1 | 1 | 1 | 9 | `68291e9e0988181e` | - | `vu1_prog_000_unreferenced` |
| 1 | `0x5a2180` | 75 | 150 | 1200 | 1 | 1 | 1 | 11 | `8844f69a9e06c18d` | - | `vu1_prog_001_unreferenced` |
| 2 | `0x5a2640` | 73 | 146 | 1168 | 1 | 1 | 1 | 10 | `d3ef18d641922ce6` | - | `vu1_prog_002_unreferenced` |
| 3 | `0x5a2ae0` | 83 | 166 | 1328 | 1 | 1 | 1 | 12 | `8f746e50acd77768` | - | `vu1_prog_003_unreferenced` |
| 4 | `0x5a3020` | 84 | 168 | 1344 | 1 | 1 | 1 | 7 | `05f1af3f3a6aa081` | - | `vu1_prog_004_unreferenced` |
| 5 | `0x5a3570` | 102 | 204 | 1632 | 1 | 1 | 1 | 9 | `bba8098050fc8dc3` | - | `vu1_prog_005_unreferenced` |
| 6 | `0x5a3be0` | 171 | 341 | 2728 | 2 | 1 | 1 | 13 | `8f1f72e1b6ac2d23` | - | `vu1_prog_006_unreferenced` |
| 7 | `0x5a46a0` | 126 | 252 | 2016 | 1 | 1 | 1 | 12 | `5bce40603c68b486` | - | `vu1_prog_007_unreferenced` |
| 8 | `0x5a4e90` | 87 | 174 | 1392 | 1 | 1 | 1 | 3 | `6bdf39389ad3d1ab` | - | `vu1_prog_008_unreferenced` |
| 9 | `0x5a5410` | 102 | 204 | 1632 | 1 | 1 | 1 | 5 | `0eae757bc44e1892` | - | `vu1_prog_009_unreferenced` |
| 10 | `0x5a5a80` | 115 | 230 | 1840 | 1 | 1 | 1 | 3 | `3d922d2ed32278ea` | - | `vu1_prog_010_unreferenced` |
| 11 | `0x5a61c0` | 151 | 301 | 2408 | 2 | 1 | 1 | 6 | `db53b5f71691b77c` | - | `vu1_prog_011_unreferenced` |
| 12 | `0x5a6b40` | 143 | 285 | 2280 | 2 | 1 | 1 | 3 | `e2372630da8784aa` | - | `vu1_prog_012_unreferenced` |
| 13 | `0x5a7440` | 153 | 305 | 2440 | 2 | 1 | 1 | 5 | `24aa4a8fc7c7d4de` | - | `vu1_prog_013_unreferenced` |
| 14 | `0x5a7de0` | 210 | 419 | 3352 | 2 | 1 | 1 | 4 | `4e2bd97520cdb555` | - | `vu1_prog_014_unreferenced` |
| 15 | `0x5a8b10` | 197 | 393 | 3144 | 2 | 1 | 1 | 5 | `4c9076eacaad427b` | - | `vu1_prog_015_unreferenced` |
| 16 | `0x5a9770` | 698 | 1391 | 11128 | 6 | 7 | 6 | 127 | `bf0218011e232d10` | - | `vu1_prog_016_unreferenced` |
| 17 | `0x5ac320` | 760 | 1515 | 12120 | 6 | 7 | 6 | 130 | `19c83193728cb8a7` | - | `vu1_prog_017_unreferenced` |
| 18 | `0x5af2b0` | 701 | 1397 | 11176 | 6 | 7 | 6 | 124 | `b91cccf9c37e5709` | - | `vu1_prog_018_unreferenced` |
| 19 | `0x5b1e90` | 717 | 1429 | 11432 | 6 | 7 | 6 | 126 | `0ce59150a491e0ec` | - | `vu1_prog_019_unreferenced` |
| 20 | `0x5b4b70` | 569 | 1134 | 9072 | 5 | 6 | 5 | 111 | `5fe5df59262f6744` | - | `vu1_prog_020_unreferenced` |
| 21 | `0x5b6f10` | 577 | 1150 | 9200 | 5 | 6 | 5 | 111 | `694f06e44cd5e61b` | - | `vu1_prog_021_unreferenced` |
| 22 | `0x5b9330` | 742 | 1479 | 11832 | 6 | 7 | 6 | 127 | `fc074f5757aae1d3` | - | `vu1_prog_022_unreferenced` |
| 23 | `0x5bc1a0` | 768 | 1531 | 12248 | 6 | 7 | 6 | 127 | `3600827ad7ae1500` | - | `vu1_prog_023_unreferenced` |
| 24 | `0x5bf1b0` | 745 | 1485 | 11880 | 6 | 7 | 6 | 124 | `d2cc5422ede18a4b` | - | `vu1_prog_024_unreferenced` |
| 25 | `0x5c2050` | 761 | 1517 | 12136 | 6 | 7 | 6 | 126 | `1585db1ede547f5d` | - | `vu1_prog_025_unreferenced` |
| 26 | `0x5c4ff0` | 629 | 1254 | 10032 | 5 | 6 | 5 | 113 | `e105b1e05b546be1` | - | `vu1_prog_026_unreferenced` |
| 27 | `0x5c7750` | 637 | 1270 | 10160 | 5 | 6 | 5 | 113 | `281fd2eebe98b778` | - | `vu1_prog_027_unreferenced` |
| 28 | `0x5c9f30` | 66 | 132 | 1056 | 1 | 2 | 2 | 8 | `41b4b303c68359b4` | ptank_spr2d[2] | `vu1_prog_028_ptank_spr2d` |
| 29 | `0x5ca360` | 59 | 118 | 944 | 1 | 2 | 2 | 7 | `70697b59792c4a43` | ptank_spr2d[3] | `vu1_prog_029_ptank_spr2d` |
| 30 | `0x5ca720` | 61 | 122 | 976 | 1 | 1 | 2 | 4 | `c96fdf7d0659d1d5` | ptank_spr2d[0] | `vu1_prog_030_ptank_spr2d` |
| 31 | `0x5cab00` | 53 | 106 | 848 | 1 | 1 | 2 | 3 | `faba806bf1a031f6` | ptank_spr2d[1] | `vu1_prog_031_ptank_spr2d` |
| 32 | `0x5cae60` | 167 | 333 | 2664 | 2 | 2 | 2 | 10 | `0e2ca11c32aeffd3` | ptank_spr3d[2] | `vu1_prog_032_ptank_spr3d` |
| 33 | `0x5cb8e0` | 138 | 275 | 2200 | 2 | 2 | 2 | 9 | `121f9cdeaa2580cf` | ptank_spr3d[3] | `vu1_prog_033_ptank_spr3d` |
| 34 | `0x5cc190` | 156 | 311 | 2488 | 2 | 1 | 2 | 6 | `a29a56afcc70baad` | ptank_spr3d[0] | `vu1_prog_034_ptank_spr3d` |
| 35 | `0x5ccb60` | 132 | 263 | 2104 | 2 | 1 | 2 | 5 | `acc6e8d83beb0a87` | ptank_spr3d[1] | `vu1_prog_035_ptank_spr3d` |
| 36 | `0x5cd3b0` | 31 | 62 | 496 | 1 | 1 | 1 | 3 | `16df7386d53e187e` | unknown_tbl4[4] | `vu1_prog_036_unknown_tbl4` |
| 37 | `0x5cd5b0` | 38 | 76 | 608 | 1 | 1 | 1 | 3 | `6a53e468ff1b8de1` | unknown_tbl4[5] | `vu1_prog_037_unknown_tbl4` |
| 38 | `0x5cd820` | 21 | 41 | 328 | 1 | 1 | 1 | 3 | `e681b489a6e20965` | unknown_tbl4[0] | `vu1_prog_038_unknown_tbl4` |
| 39 | `0x5cd980` | 24 | 47 | 376 | 1 | 1 | 1 | 3 | `be30f12b217e3700` | unknown_tbl4[1] | `vu1_prog_039_unknown_tbl4` |
| 40 | `0x5cdb10` | 2 | 4 | 32 | 1 | 1 | 0 | 1 | `e20db00a77d56d81` | null_transform[0], null_transform[1], null_transform[2], null_transform[3], null_transform[4], null_transform[5], null_transform[6], null_transform[7], null_transform[8], null_transform[9], null_transform[10], null_transform[11], null_transform[12], null_transform[13], null_transform[14], null_transform[15], null_transform[16], null_transform[17], null_transform[18], null_transform[19], null_transform[20], null_transform[21], null_transform[22], null_transform[23], null_transform[24], null_transform[25], null_transform[26], null_transform[27], null_transform[28], null_transform[29], null_transform[30], null_transform[31] | `vu1_prog_040_null_transform` |
| 41 | `0x6b5e90` | 746 | 1487 | 11896 | 6 | 1 | 8 | 217 | `b5da3704bd4ebbb3` | g3_generic[3], g3_matfx[3] | `vu1_prog_041_g3_generic` |
| 42 | `0x6b8d40` | 923 | 1839 | 14712 | 8 | 1 | 12 | 216 | `ffa410ad2dad1208` | g3_generic[1], g3_matfx[1] | `vu1_prog_042_g3_generic` |
| 43 | `0x6bc700` | 424 | 845 | 6760 | 4 | 1 | 5 | 117 | `866be57f8571c20d` | g3_generic[6], g3_generic[7] | `vu1_prog_043_g3_generic` |
| 44 | `0x6be190` | 468 | 933 | 7464 | 4 | 1 | 5 | 119 | `335a06de9929e826` | g3_generic[4], g3_generic[5] | `vu1_prog_044_g3_generic` |
| 45 | `0x6bfee0` | 677 | 1348 | 10784 | 6 | 1 | 7 | 198 | `1b14cb7c935a2368` | g3_generic[2], g3_matfx[2] | `vu1_prog_045_g3_generic` |
| 46 | `0x6c2940` | 686 | 1367 | 10936 | 6 | 1 | 8 | 194 | `6b0e71911b6ebd21` | g3_generic[0], g3_matfx[0] | `vu1_prog_046_g3_generic` |
| 47 | `0x6c5430` | 706 | 1406 | 11248 | 6 | 1 | 4 | 201 | `0b20783e9cd1036b` | g3_matfx[4] | `vu1_prog_047_g3_matfx` |
| 48 | `0x6c8060` | 671 | 1337 | 10696 | 6 | 1 | 4 | 199 | `8c18355ed0ccd81e` | g3_matfx[6] | `vu1_prog_048_g3_matfx` |
| 49 | `0x6caa60` | 955 | 1903 | 15224 | 8 | 1 | 4 | 241 | `a8f9f704e85284ca` | g3_matfx[5] | `vu1_prog_049_g3_matfx` |
| 50 | `0x6ce620` | 778 | 1550 | 12400 | 7 | 1 | 4 | 229 | `cc4527fbac17b161` | g3_matfx[7] | `vu1_prog_050_g3_matfx` |
| 51 | `0x6d16d0` | 698 | 1390 | 11120 | 6 | 1 | 4 | 202 | `08071ca9ac26610f` | g3_matfx[8] | `vu1_prog_051_g3_matfx` |
| 52 | `0x6d4280` | 663 | 1320 | 10560 | 6 | 1 | 4 | 198 | `3469d2db08451bcb` | g3_matfx[10] | `vu1_prog_052_g3_matfx` |
| 53 | `0x6d6c00` | 945 | 1882 | 15056 | 8 | 1 | 4 | 242 | `9cb8b7e6adb93d6e` | g3_matfx[9] | `vu1_prog_053_g3_matfx` |
| 54 | `0x6da720` | 770 | 1534 | 12272 | 6 | 1 | 4 | 229 | `5fc265af1ed7442b` | g3_matfx[11] | `vu1_prog_054_g3_matfx` |
| 55 | `0x6dd750` | 726 | 1447 | 11576 | 6 | 1 | 6 | 204 | `1fbf08fda38e1159` | g3_matfx[12] | `vu1_prog_055_g3_matfx` |
| 56 | `0x6e04c0` | 692 | 1378 | 11024 | 6 | 1 | 6 | 202 | `c9c71c055c087809` | g3_matfx[14] | `vu1_prog_056_g3_matfx` |
| 57 | `0x6e3010` | 976 | 1944 | 15552 | 8 | 1 | 6 | 244 | `fd563d910e8311b6` | g3_matfx[13] | `vu1_prog_057_g3_matfx` |
| 58 | `0x6e6d20` | 799 | 1591 | 12728 | 7 | 1 | 6 | 232 | `030cf0a1807cf66d` | g3_matfx[15] | `vu1_prog_058_g3_matfx` |
| 59 | `0x6e9f20` | 673 | 1340 | 10720 | 6 | 1 | 4 | 199 | `bbc4b6dacc111417` | g3_matfx[16] | `vu1_prog_059_g3_matfx` |
| 60 | `0x6ec940` | 638 | 1271 | 10168 | 5 | 1 | 4 | 197 | `39b189d2ff763ea6` | g3_matfx[18] | `vu1_prog_060_g3_matfx` |
| 61 | `0x6ef130` | 922 | 1837 | 14696 | 8 | 1 | 4 | 239 | `9574714cc2b7d215` | g3_matfx[17] | `vu1_prog_061_g3_matfx` |
| 62 | `0x6f2ae0` | 745 | 1484 | 11872 | 6 | 1 | 4 | 227 | `a8d0b58ddbd61a34` | g3_matfx[19] | `vu1_prog_062_g3_matfx` |
| 63 | `0x6f5980` | 792 | 1577 | 12616 | 7 | 1 | 8 | 216 | `09d10f7af023f740` | g3_skin[3], g3_skin_matfx[3] | `vu1_prog_063_g3_skin` |
| 64 | `0x6f8b10` | 968 | 1929 | 15432 | 8 | 1 | 12 | 215 | `930a758f0515baf3` | g3_skin[1], g3_skin_matfx[1] | `vu1_prog_064_g3_skin` |
| 65 | `0x6fc7a0` | 469 | 935 | 7480 | 4 | 1 | 5 | 116 | `5fbc81b4fb6981fa` | g3_skin[6], g3_skin[7] | `vu1_prog_065_g3_skin` |
| 66 | `0x6fe500` | 513 | 1023 | 8184 | 4 | 1 | 5 | 118 | `d1f5180e7627fefa` | g3_skin[4], g3_skin[5] | `vu1_prog_066_g3_skin` |
| 67 | `0x700520` | 722 | 1438 | 11504 | 6 | 1 | 7 | 197 | `3c542b56f3326efe` | g3_skin[2], g3_skin_matfx[2] | `vu1_prog_067_g3_skin` |
| 68 | `0x703250` | 731 | 1457 | 11656 | 6 | 1 | 8 | 193 | `d5ad7443c7b8cd89` | g3_skin[0], g3_skin_matfx[0] | `vu1_prog_068_g3_skin` |
| 69 | `0x706010` | 744 | 1482 | 11856 | 6 | 1 | 4 | 200 | `eefdcf408b01f3d6` | g3_skin_matfx[4], g3_skspt_a[0] | `vu1_prog_069_g3_skin_matfx` |
| 70 | `0x708ea0` | 709 | 1413 | 11304 | 6 | 1 | 4 | 198 | `245de4cc3538a167` | g3_skin_matfx[6], g3_skspt_a[2] | `vu1_prog_070_g3_skin_matfx` |
| 71 | `0x70bb00` | 993 | 1979 | 15832 | 8 | 1 | 4 | 240 | `0e8998ecdc5b9fb8` | g3_skin_matfx[5], g3_skspt_a[1] | `vu1_prog_071_g3_skin_matfx` |
| 72 | `0x70f920` | 816 | 1626 | 13008 | 7 | 1 | 4 | 228 | `1a6f300acc8b2feb` | g3_skin_matfx[7], g3_skspt_a[3] | `vu1_prog_072_g3_skin_matfx` |
| 73 | `0x712c30` | 736 | 1466 | 11728 | 6 | 1 | 4 | 201 | `60580395ae8c9f54` | g3_skin_matfx[8], g3_skspt_gem[0] | `vu1_prog_073_g3_skin_matfx` |
| 74 | `0x715a40` | 701 | 1396 | 11168 | 6 | 1 | 4 | 197 | `2f5e7306a5574f9a` | g3_skin_matfx[10], g3_skspt_gem[2] | `vu1_prog_074_g3_skin_matfx` |
| 75 | `0x718620` | 983 | 1958 | 15664 | 8 | 1 | 4 | 241 | `f4d052ba0ff6af82` | g3_skin_matfx[9], g3_skspt_gem[1] | `vu1_prog_075_g3_skin_matfx` |
| 76 | `0x71c3a0` | 808 | 1610 | 12880 | 7 | 1 | 4 | 228 | `43a9a0e219640630` | g3_skin_matfx[11], g3_skspt_gem[3] | `vu1_prog_076_g3_skin_matfx` |
| 77 | `0x71f630` | 764 | 1523 | 12184 | 6 | 1 | 6 | 203 | `7314d6f8a089c927` | g3_skin_matfx[12], g3_skspt_bem[0] | `vu1_prog_077_g3_skin_matfx` |
| 78 | `0x722600` | 730 | 1454 | 11632 | 6 | 1 | 6 | 201 | `b63efb2e489e2a90` | g3_skin_matfx[14], g3_skspt_bem[2] | `vu1_prog_078_g3_skin_matfx` |
| 79 | `0x7253b0` | 1014 | 2020 | 16160 | 8 | 1 | 6 | 243 | `7cf20975a85e189d` | g3_skin_matfx[13], g3_skspt_bem[1] | `vu1_prog_079_g3_skin_matfx` |
| 80 | `0x729320` | 837 | 1667 | 13336 | 7 | 1 | 6 | 231 | `1b5a370c5f57eabc` | g3_skin_matfx[15], g3_skspt_bem[3] | `vu1_prog_080_g3_skin_matfx` |
| 81 | `0x72c780` | 718 | 1430 | 11440 | 6 | 1 | 4 | 198 | `33339a53484b75cc` | g3_skin_matfx[16], g3_skspt_dup[0] | `vu1_prog_081_g3_skin_matfx` |
| 82 | `0x72f470` | 683 | 1361 | 10888 | 6 | 1 | 4 | 196 | `b951d7a14e0e349f` | g3_skin_matfx[18], g3_skspt_dup[2] | `vu1_prog_082_g3_skin_matfx` |
| 83 | `0x731f30` | 967 | 1927 | 15416 | 8 | 1 | 4 | 238 | `e33a44cdd397b7b0` | g3_skin_matfx[17], g3_skspt_dup[1] | `vu1_prog_083_g3_skin_matfx` |
| 84 | `0x735bb0` | 790 | 1574 | 12592 | 7 | 1 | 4 | 226 | `1056ebb9b336ef24` | g3_skin_matfx[19], g3_skspt_dup[3] | `vu1_prog_084_g3_skin_matfx` |
| 85 | `0x738d20` | 534 | 1063 | 8504 | 5 | 1 | 8 | 164 | `582acecede8e0db7` | rt2d_stroke[0] | `vu1_prog_085_rt2d_stroke` |
| 86 | `0x73ae90` | 524 | 1044 | 8352 | 5 | 1 | 7 | 168 | `5503461fa8489266` | rt2d_stroke[1] | `vu1_prog_086_rt2d_stroke` |
| 87 | `0x73cf60` | 556 | 1108 | 8864 | 5 | 1 | 8 | 164 | `de92a4a6bf1105d0` | rt2d_font[0] | `vu1_prog_087_rt2d_font` |
| 88 | `0x73f230` | 547 | 1089 | 8712 | 5 | 1 | 7 | 168 | `2a9530b9c979cbb6` | rt2d_font[1] | `vu1_prog_088_rt2d_font` |
| 89 | `0x741470` | 564 | 1123 | 8984 | 5 | 1 | 8 | 166 | `2556bdb10012eefa` | rt2d_fill[0] | `vu1_prog_089_rt2d_fill` |
| 90 | `0x7437c0` | 554 | 1104 | 8832 | 5 | 1 | 7 | 170 | `548a62f81d9f7c94` | rt2d_fill[1] | `vu1_prog_090_rt2d_fill` |
| 91 | `0x745a70` | 697 | 1388 | 11104 | 6 | 1 | 8 | 195 | `c407e5c8b60bad10` | g3_matfx[20] | `vu1_prog_091_g3_matfx` |
| 92 | `0x748610` | 687 | 1369 | 10952 | 6 | 1 | 7 | 199 | `b68a6e024de7f5f0` | g3_matfx[22] | `vu1_prog_092_g3_matfx` |
| 93 | `0x74b110` | 934 | 1860 | 14880 | 8 | 1 | 12 | 217 | `7931b3c700d48fe3` | g3_matfx[21] | `vu1_prog_093_g3_matfx` |
| 94 | `0x74eb80` | 757 | 1508 | 12064 | 6 | 1 | 8 | 218 | `a7ff6f7579dec4e3` | g3_matfx[23] | `vu1_prog_094_g3_matfx` |
| 95 | `0x751ae0` | 685 | 1365 | 10920 | 6 | 1 | 4 | 200 | `5389caa20e2b11b0` | g3_matfx[24] | `vu1_prog_095_g3_matfx` |
| 96 | `0x7545c0` | 651 | 1296 | 10368 | 6 | 1 | 4 | 198 | `3c1aaf61189e70e4` | g3_matfx[26] | `vu1_prog_096_g3_matfx` |
| 97 | `0x756e80` | 935 | 1862 | 14896 | 8 | 1 | 4 | 240 | `9e2dacc0dee79388` | g3_matfx[25] | `vu1_prog_097_g3_matfx` |
| 98 | `0x75a900` | 757 | 1509 | 12072 | 6 | 1 | 4 | 228 | `4e0c861d68167ecf` | g3_matfx[27] | `vu1_prog_098_g3_matfx` |
| 99 | `0x75d860` | 742 | 1478 | 11824 | 6 | 1 | 8 | 194 | `f7c256017974ed2c` | g3_skin_matfx[20], g3_skspt_uva[0] | `vu1_prog_099_g3_skin_matfx` |
| 100 | `0x7606d0` | 732 | 1459 | 11672 | 6 | 1 | 7 | 198 | `f49fbfe7ec201e43` | g3_skin_matfx[22], g3_skspt_uva[2] | `vu1_prog_100_g3_skin_matfx` |
| 101 | `0x7634a0` | 979 | 1950 | 15600 | 8 | 1 | 12 | 216 | `71e11ced88713a80` | g3_skin_matfx[21], g3_skspt_uva[1] | `vu1_prog_101_g3_skin_matfx` |
| 102 | `0x7671e0` | 802 | 1598 | 12784 | 7 | 1 | 8 | 217 | `95de82b856d0877d` | g3_skin_matfx[23], g3_skspt_uva[3] | `vu1_prog_102_g3_skin_matfx` |
| 103 | `0x76a410` | 524 | 1044 | 8352 | 5 | 1 | 5 | 119 | `4891a122347ee8db` | g3_skspt_uva[4], g3_skspt_uva[5] | `vu1_prog_103_g3_skspt_uva` |
| 104 | `0x76c4e0` | 480 | 956 | 7648 | 4 | 1 | 5 | 117 | `403387e0a37fb0c8` | g3_skspt_uva[6], g3_skspt_uva[7] | `vu1_prog_104_g3_skspt_uva` |
| 105 | `0x76e2f0` | 730 | 1455 | 11640 | 6 | 1 | 4 | 199 | `c7467b681414972a` | g3_skin_matfx[24], g3_skspt_dupuva[0] | `vu1_prog_105_g3_skin_matfx` |
| 106 | `0x7710a0` | 696 | 1386 | 11088 | 6 | 1 | 4 | 197 | `870a31f024e87cf4` | g3_skin_matfx[26], g3_skspt_dupuva[2] | `vu1_prog_106_g3_skin_matfx` |
| 107 | `0x773c30` | 980 | 1952 | 15616 | 8 | 1 | 4 | 239 | `7fbb6aea44183c96` | g3_skin_matfx[25], g3_skspt_dupuva[1] | `vu1_prog_107_g3_skin_matfx` |
| 108 | `0x777980` | 803 | 1599 | 12792 | 7 | 1 | 4 | 227 | `c9ccca005b897608` | g3_skin_matfx[27], g3_skspt_dupuva[3] | `vu1_prog_108_g3_skin_matfx` |
| 109 | `0x77cb40` | 57 | 113 | 904 | 1 | 3 | 2 | 13 | `9bf7abece5e48f2b` | ptank_xform[0] | `vu1_prog_109_ptank_xform` |
| 110 | `0x77cee0` | 49 | 98 | 784 | 1 | 2 | 1 | 9 | `7f301dc2d0bfde4c` | ptank_xform[0] | `vu1_prog_110_ptank_xform` |
| 111 | `0x77d200` | 56 | 112 | 896 | 1 | 2 | 1 | 9 | `cdcf02ffb54cfbaa` | ptank_xform[0] | `vu1_prog_111_ptank_xform` |
| 112 | `0x77d590` | 55 | 110 | 880 | 1 | 2 | 1 | 9 | `1935b8c5395c4a08` | ptank_xform[0] | `vu1_prog_112_ptank_xform` |
| 113 | `0x77d910` | 57 | 113 | 904 | 1 | 2 | 1 | 9 | `efe7c4df253ffaed` | ptank_xform[0] | `vu1_prog_113_ptank_xform` |

Observations on the bodies [der, instruction-class counts from the raw words]:
- `unreferenced`: 28 programs, 126–1531 units, xgkick 1–6, clip ops (`clipw`) 2–21, div/sqrt/rsqrt 2–54.
- `g3_matfx`: 24 programs, 1271–1944 units, xgkick 4–12, clip ops (`clipw`) 29–44, div/sqrt/rsqrt 24–84.
- `g3_skin_matfx`: 24 programs, 1361–2020 units, xgkick 4–12, clip ops (`clipw`) 29–44, div/sqrt/rsqrt 24–84.
- `g3_generic`: 6 programs, 845–1839 units, xgkick 5–12, clip ops (`clipw`) 11–40, div/sqrt/rsqrt 18–84.
- `g3_skin`: 6 programs, 935–1929 units, xgkick 5–12, clip ops (`clipw`) 11–40, div/sqrt/rsqrt 18–84.
- `ptank_xform`: 5 programs, 98–113 units, xgkick 1–2, clip ops (`clipw`) 2–4, div/sqrt/rsqrt 3–4.
- `ptank_spr2d`: 4 programs, 106–132 units, xgkick 2–2, clip ops (`clipw`) 2–2, div/sqrt/rsqrt 2–2.
- `ptank_spr3d`: 4 programs, 263–333 units, xgkick 2–2, clip ops (`clipw`) 12–12, div/sqrt/rsqrt 12–12.
- `unknown_tbl4`: 4 programs, 41–76 units, xgkick 1–1, clip ops (`clipw`) 0–0, div/sqrt/rsqrt 0–0.
- `rt2d_stroke`: 2 programs, 1044–1063 units, xgkick 7–8, clip ops (`clipw`) 30–38, div/sqrt/rsqrt 15–45.
- `rt2d_font`: 2 programs, 1089–1108 units, xgkick 7–8, clip ops (`clipw`) 30–38, div/sqrt/rsqrt 15–45.
- `rt2d_fill`: 2 programs, 1104–1123 units, xgkick 7–8, clip ops (`clipw`) 30–38, div/sqrt/rsqrt 14–44.
- `g3_skspt_uva`: 2 programs, 956–1044 units, xgkick 5–5, clip ops (`clipw`) 11–17, div/sqrt/rsqrt 18–39.
- `null_transform`: 1 programs, 4–4 units, xgkick 0–0, clip ops (`clipw`) 0–0, div/sqrt/rsqrt 0–0.
- The 12 large unreferenced programs `0x5A9770..0x5C7750` (1134–1531 units, 6 E-bits/5-6 xgkick each) are 6-piece programs with 111–130 branches: full RW transform programs of a stock pipeline whose code array is not linked [inf]. The 16 small unreferenced programs `0x5A1D80..0x5A8B10` (126–419 units, 1 xgkick) match the size class of the generic set [inf].
- `vu1_prog_*_null_transform` (`0x5CDB10`, 4 units, 0 xgkick) is `skyVU1NullTransforms` x32: the pipeline node default when no code array is set (`PS2AllMatPipelineNodeInit 0x4a3540`, `RxPipelineNodePS2AllMatSetVU1CodeArray 0x4a3db0` [obs]).
- Index semantics inside an 8/28-entry array: entries 4,5 and 6,7 of every 8-entry array are pairwise identical [obs], so the selecting bit field has one bit that only matters for entries 0-3. The index is formed in the bridge callback from the PS2All transform type (`RpAtomicPS2AllPrimTypeTransTypeSetupFunc 0x4a05d0`; stock bridge `RpMeshPS2AllBridgeCallBack 0x4a0e00` reads the clip mode from `gp-16876/gp-20232` and the prim flags from `mesh+40`) [obs]; the exact bit assignment (TL/TS clip x fog x prelit?) is **open** (§7).

## 2. Code arrays, pipe definitions and the RenderWare pipeline set [obs]

`RpPDSSkyMatPipeCreate 0x46ad80` builds a material pipeline from a 132-byte definition: `+0/+4` plugin ids, `+8..` up to 10 cluster pairs, `+88` RW prim type (1/2 line, 3/4/5 tri, 6 point), `+92/+96/+100` VU buffer sizes, `+104` VIF offset, `+108` -> `{vu1CodeArray*, count}` descriptor, `+112..+128` PS2All callbacks 1..5 (`RxPipelineNodePS2AllMatSetCallBack`) [obs, Hex-Rays]. `RxPipelineNodePS2AllMatSetVU1CodeArray` stores the pair at node-private `+24/+28` [obs]. Definitions found by scanning for `+108` descriptors in `0x7CDB28..0x7CDBB8` [der]:

| def VA | pipe id | prim | VU buf | VIF off | code array x n | instance CB | bridge CB |
|---|---|---|---|---|---|---|---|
| `0x6b4f20` | `0x1` | 4 | 4,69,23 | 276 | `0x6b4f00` x8 (`g3_generic`) | RpMeshPS2AllInstanceCallBack | RpMeshPS2AllBridgeCallBack |
| `0x6b4ff0` | `0x4` | 4 | 4,69,23 | 276 | `0x6b4f00` x8 (`g3_generic`) | RwIm3DPS2AllInstanceCallBack | RwIm3DPS2AllBridgeCallBack |
| `0x6b5080` | `0x5` | 1 | 4,69,34 | 276 | `0x6b4f00` x8 (`g3_generic`) | RwIm3DPS2AllInstanceCallBack | RwIm3DPS2AllBridgeCallBack |
| `0x6b51e0` | `0x1100b` | 4 | 4,56,18 | 224 | `0x6b5170` x28 (`g3_matfx`) | RpMeshPS2AllInstanceCallBack | RpPDS_G3_Matfx_PS2AllMatBridgeCallBack |
| `0x6b5270` | `0x1100c` | 4 | 4,56,18 | 224 | `0x6b5170` x28 (`g3_matfx`) | RpMeshPS2AllInstanceCallBack | RpPDS_G3_Matfx_PS2AllMatBridgeCallBack |
| `0x6b53a0` | `0x10001` | 4 | 5,43,14 | 215 | `0x6b5380` x8 (`g3_skin`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpMeshPS2AllBridgeCallBack |
| `0x6b5500` | `0x11011` | 4 | 5,36,12 | 180 | `0x6b5490` x28 (`g3_skin_matfx`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_Matfx_PS2AllMatBridgeCallBack |
| `0x6b5590` | `0x11012` | 4 | 5,36,12 | 180 | `0x6b5490` x28 (`g3_skin_matfx`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_Matfx_PS2AllMatBridgeCallBack |
| `0x6b56a0` | `0x10019` | 6 | 2,40,40 | 240 | `0x7cdb78` x2 (`rt2d_stroke`) | RpPDS_G3_2DStroke_PS2AllMatInstanceCallBack | RpPDS_G3_2DStroke_PS2AllBridgeCallBack |
| `0x6b57f0` | `0x1001b` | 6 | 2,12,12 | 228 | `0x7cdb88` x2 (`rt2d_font`) | RpPDS_G3_2DFont_PS2AllMatInstanceCallBack | RpPDS_G3_2DFont_PS2AllBridgeCallBack |
| `0x6b5940` | `0x1001d` | 4 | 2,80,26 | 240 | `0x7cdb98` x2 (`rt2d_fill`) | RpPDS_G3_2DFill_PS2AllMatInstanceCallBack | RpPDS_G3_2DFill_PS2AllBridgeCallBack |
| `0x6b5a50` | `0x10020` | 4 | 5,43,14 | 215 | `0x6b5380` x8 (`g3_skin`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_SkSpt_PS2AllBridgeCallBack |
| `0x6b5b00` | `0x10021` | 4 | 5,36,12 | 180 | `0x6b5450` x4 (`g3_skspt_a`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | sub_472170 |
| `0x6b5b90` | `0x10022` | 4 | 5,36,12 | 180 | `0x6b5460` x4 (`g3_skspt_gem`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_SkSptGem_PS2AllBridgeCallBack |
| `0x6b5c20` | `0x10023` | 4 | 5,36,12 | 180 | `0x6b5470` x4 (`g3_skspt_bem`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_SkSptBem_PS2AllMatBridgeCallBack |
| `0x6b5cb0` | `0x10024` | 4 | 5,36,12 | 180 | `0x6b5480` x4 (`g3_skspt_dup`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_SkSptDup_PS2AllMatBridgeCallBack |
| `0x6b5d70` | `0x1002a` | 4 | 5,43,14 | 215 | `0x6b5d40` x8 (`g3_skspt_uva`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | sub_473340 |
| `0x6b5e00` | `0x1002b` | 4 | 5,36,12 | 180 | `0x6b5d60` x4 (`g3_skspt_dupuva`) | RpPDS_G3d_Skin_PS2AllInstanceCallBack | RpPDS_G3_SkSptDupUva_PS2AllMatBridgeCallBack |

Code arrays (owner: the definitions above and two RW globals):

| array VA | n | family | note |
|---|---|---|---|
| `0x6b4f00` | 8 | `g3_generic` | RpMesh/RwIm3D generic (non-skinned) transform; descriptor 0x7cdb28; pipes 0x1001/0x1004/0x1005 (tri, Im3D tri, Im3D line) |
| `0x6b5170` | 28 | `g3_matfx` | RpPDS_G3_Matfx bridge; descriptor 0x7cdb40; pipes 0x1100b/0x1100c (entries 0-3 = generic set) |
| `0x6b5380` | 8 | `g3_skin` | RpPDS_G3d_Skin instance + stock bridge; descriptor 0x7cdb48; pipes 0x10001/0x10020 |
| `0x6b5490` | 28 | `g3_skin_matfx` | skin + RpPDS_G3_Matfx bridge; descriptor 0x7cdb70; pipes 0x11011/0x11012 |
| `0x6b5450` | 4 | `g3_skspt_a` | skin + bridge sub_472170 (unnamed; SkSpt variant); descriptor 0x7cdb50; pipe 0x10021 |
| `0x6b5460` | 4 | `g3_skspt_gem` | skin + RpPDS_G3_SkSptGem bridge; descriptor 0x7cdb58; pipe 0x10022 |
| `0x6b5470` | 4 | `g3_skspt_bem` | skin + RpPDS_G3_SkSptBem bridge; descriptor 0x7cdb60; pipe 0x10023 |
| `0x6b5480` | 4 | `g3_skspt_dup` | skin + RpPDS_G3_SkSptDup bridge; descriptor 0x7cdb68; pipe 0x10024 |
| `0x6b5d40` | 8 | `g3_skspt_uva` | skin + bridge sub_473340 (unnamed; Uva variant); descriptor 0x7cdba8; pipe 0x1002a |
| `0x6b5d60` | 4 | `g3_skspt_dupuva` | skin + RpPDS_G3_SkSptDupUva bridge; descriptor 0x7cdbb0; pipe 0x1002b |
| `0x7cdb78` | 2 | `rt2d_stroke` | RpPDS_G3_2DStroke (Rt2d stroke, point-list prim 6); pipe 0x10019 |
| `0x7cdb88` | 2 | `rt2d_font` | RpPDS_G3_2DFont (Rt2d font, point-list prim 6); pipe 0x1001b |
| `0x7cdb98` | 2 | `rt2d_fill` | RpPDS_G3_2DFill (Rt2d fill, tristrip); pipe 0x1001d |
| `0x77b1e0` | 4 | `ptank_spr2d` | rps2gPS2ALLVUCodeArray: RpPTank 2D sprite pipe (rpSpr2dGenCreatePS2AllMatPipe 0x478a70) |
| `0x77b1f0` | 4 | `ptank_spr3d` | rps3gPS2ALLVUCodeArray: RpPTank 3D sprite pipe (rpSpr3dGenCreatePS2AllMatPipe 0x479e50) |
| `0x7bcf74` | 6 | `unknown_tbl4` | pointer table 0x7bcf74..0x7bcf88 (4 program pointers + 2 other words) with no code/data xref found |
| `0x77ac5c` | 1 | `ptank_xform` | RpPTank TransformInfo 0x77ac40.. (rpSkyAlloc 0x475540): per-format instance programs at 0x77ac5c/0x77ac60/0x77acfc/0x77ad9c/0x77ae3c |
| `0x77f130` | 32 | `null_transform` | skyVU1NullTransforms: 32 x the 4-unit null program |

Pipeline registration [obs, Hex-Rays of `kwlnInitRenderer 0x197350`]: `RwEngineInit(H_Malloc_GetRwMemoryFunctions(), 0, 0x800000)`, `RpPDSPluginAttach(7)`, then 33 x `RpPDSRegisterPipe({def, parentId, id, kind, 0})` with ids `0x1001..0x1007`, `0x1100b/c`, `0x10001`, `0x11011/2`, `0x10019..0x1001e`, `0x10020..0x10024`, `0x1002a/b` (material pipes have kind 1, object pipes kind 2 and reference a material id); `RpWorldPluginAttach`, `RpSplinePluginAttach`, `RpSkinPluginAttach 0x48a1a0`, `RpPTankPluginAttach 0x473590`; `RwEngineOpen`, `RpSkySelectDeepZBuffer(0)`, `RwEngineSetVideoMode(82)`, `rwDMAPreAlloc(0x280000, 1024, 0)`, `RpWorldCreate`, 2 lights. Consumers: `RpPDSGetPipe 0x46a890` x29 (`mdlManagerSetMaterialMatFxPipeline` x7, `rt2dPS2PipeOpen 0x4b1100` x6 = ids 0x1001a/0x1001c/0x1001e, `_rwfastIm3DPipesOpen` x4, `_rpMatFXPipeline*Setup` x4, `mdlManagerSetClumpPipelines`, `_rpSkinPipelinesAttach`) [obs].

Which RW 3.7 components are present and used [obs via xrefs]: **rpWorld** (`RpWorldRender` x3 from `K_FldSrc_DrawFieldOpaque`), **rpSkin** (`RpSkinAtomicSetHAnimHierarchy` from `mdlManagerSetAtomicHAnim`), **rpMatFX** (`RpMatFXMaterialSetBumpMapTexture 0x469060`, `_rpMatFXPipeline*Setup`), **rpPDS** (all platform pipes), **rpPTank** (particles: `rpSpr2dGen/rpSpr3dGen` pipes, `_rpPTankSkyFillTags 0x474d30` emits `MSCAL`), **Rt2d** (`rt2dPS2PipeOpen`, font/stroke/fill pipes: menus & text), **rwIm3D** (`RwIm3DTransform` x23: `gcModelDraw` x16, `K_SPipe_DrawShadow`, `primLine3D`), **rwIm2D** through the device table (`SkyIm2DRenderPrimitive 0x4edba0` etc. have no direct callers [obs]; reached via `RwIm2D*` function pointers [inf]), **rpSpline**, **rpCollision** (`RpCollisionWorldForAllIntersections 0x464020`), **rpUserData**, **rpRandom**. `.RMD` streams: `RwStreamOpen` x18 (`sub_319970` x5, `K_Fldrc_InitRead` x3, `mdlManagerLoadRwStream`, `uttmxRwStreamOpen`), `RpClumpStreamRead 0x4920a0` x3 and `RwTexDictionaryStreamRead 0x4c8680` x4 from `H_Resman_ThreadProc`, `K_Fldrc_InitRead`, `sub_319970`, `sub_34D990` [obs]: a resource-manager thread reads clumps/texdicts (Atlus chunk `0xF0F000F0` wraps them, DISC_LAYOUT §4). Instancing is RW's: `RpAtomicPS2AllInstance 0x4a1430` / `RpMeshPS2AllInstanceCallBack 0x4a0dc0` generate the VIF `UNPACK` streams per mesh at first render (`RxPipelineNodePS2AllMatGenerateCluster 0x4a35c0` emits `UNPACK V4-8/V3-32/V2-32` cluster formats [obs]).

`G3_2D*` band (`0x46F400–0x470E10`): the hint names `RpPDS_G3_2DStroke/2DFont/2DFill_*` are RW PDS **Rt2d** pipelines, not Atlus code: point-list prims (2 code programs each, §1) expanded by VU1, bridge `RpPDS_G3_2DFont_PS2AllBridgeCallBack 0x4709e0` emits `STCYCL 0x01000404` + `UNPACK V4-32` to VU addresses `0x3FA/0x3FC/0x3FD` and a GIF tag through the standard VIF packet, no `DIRECT` [obs]. 2D sprites are therefore drawn **through VU1**, not via PATH2 `DIRECT`.

## 3. VIF packet builders and the `DIRECT` paths [obs]

Owner of every packet: `_rwDMAOpenVIFPkt 0x4d59d0` (69 callers: `_rwSkySetRenderState` x13, `RpSkyRenderStateSet` x3, every bridge callback x2) and `_rwDMAOpenGIFPkt 0x4d54e0` (10 callers, all texture upload: `skyPrepareUploadRaster`, `SkyUpLoadAlignedRectangle`, `skyTexCacheMemRasterToGs`, `SkyDdispatchUpLoadAlignedContiguousRectangle`), `_rwDMAOpenVIFPktInline 0x4d5e90` (PTank setup + `uttmxDMASPRCopy`) [obs].

Constant `lui` census over all code (unambiguous VIF commands only; `0x7FFF`-class float masks excluded) [obs]:

| VIFcode | sites | emitting functions |
|---|---|---|
| `DIRECT` | 83 | RpPDS_G3_Bem_PS2AllMatBridgeCallBack x6, RpPDS_G3_Dup_PS2AllMatBridgeCallBack x6, RpPDS_G3_DupUva_PS2AllMatBridgeCallBack x6, SkyRasterCreate x6, RpPDS_G3_Emb_PS2AllMatBridgeCallBack x5, RpPDS_G3_Gem_PS2AllMatBridgeCallBack x5, RpPDS_G3_Uva_PS2AllMatBridgeCallBack x4, RpMeshPS2AllBridgeCallBack x4, SkyUpLoadAlignedRectangle x4, _sequenceHeader x4 |
| `UNPACK_V4-32` | 75 | RpPDS_G3_Gem_PS2AllMatBridgeCallBack x5, RpPDS_G3_Dup_PS2AllMatBridgeCallBack x5, RpPDS_G3_Uva_PS2AllMatBridgeCallBack x5, RpPDS_G3_DupUva_PS2AllMatBridgeCallBack x5, RpPDS_G3_Emb_PS2AllMatBridgeCallBack x4, RpPDS_G3_Bem_PS2AllMatBridgeCallBack x4, RpPDS_G3_2DStroke_PS2AllBridgeCallBack x4, RpPDS_G3_2DFont_PS2AllBridgeCallBack x4, RpPDS_G3_2DFill_PS2AllBridgeCallBack x4, RpMeshPS2AllBridgeCallBack x4 |
| `UNPACK_V4-32m` | 11 | _strtod_r x3, addCopyVU1Line x1, addCopyVU1Triangle x1, addCopyVU1PrimPolyLine x1, addCopyVU1PrimTriStrip x1, addCopyVU1PrimTriFan x1, addCopyVU1IndPrimLineList x1, addCopyVU1IndPrimPolyLine x1, addCopyVU1IndPrimTriFan x1 |
| `UNPACK_S-32` | 10 | DMADataFillTags x2, _rpPTankSkyFillTags x1, PS2AllMatProcessInitData x1, _rwDMADmaOpen x1, RpSkyRenderStateSet x1, setInitialRenderState x1, initVu1DispatchStuff x1, skyFillInPktForUpLoadAlignedContiguousRectangle x1, sceIpuInit x1 |
| `MSCALF` | 8 | sub_2C84B0 x1, sub_2C9E90 x1, sub_2CAAE0 x1, sub_2CD0C0 x1, sub_306E80 x1, _rpPTankSkyFillTags x1, DMADataFillTags x1, initVu1DispatchStuff x1 |
| `UNPACK_V2-32` | 6 | sub_2170C0 x1, rpSpr2dGenCreatePS2AllMatPipe x1, rpSpr3dGenCreatePS2AllMatPipe x1, DMADataFillTags x1, PS2AllMatProcessInitData x1, RxPipelineNodePS2AllMatGenerateCluster x1 |
| `UNPACK_V3-32` | 5 | DMADataFillTags x2, _rwPS2AllRabinsConstructionTimeCode x1, PS2AllMatProcessInitData x1, RxPipelineNodePS2AllMatGenerateCluster x1 |
| `UNPACK_V4-8` | 5 | RxPipelineNodePS2AllMatGenerateCluster x2, _rwPS2AllRabinsConstructionTimeCode x1, DMADataFillTags x1, PS2AllMatProcessInitData x1 |
| `MSCNT` | 3 | sub_2CCF60 x1, DMADataFillTags x1, initVu1DispatchStuff x1 |
| `UNPACK_S-16m` | 3 | RpSkyRenderStateSet x1, setInitialRenderState x1, SkyOpen x1 |
| `UNPACK_V3-32m` | 2 | sub_203DE0 x1, SkyGSMipGenerate x1 |
| `UNPACK_V4-16` | 2 | DMADataFillTags x1, PS2AllMatProcessInitData x1 |
| `UNPACK_V2-16` | 2 | DMADataFillTags x1, PS2AllMatProcessInitData x1 |
| `MSCAL` | 1 | _rpPTankSkyFillTags x1 |

Stock material packet (`RpMeshPS2AllBridgeCallBack 0x4a0e00`, mirrored by every `RpPDS_G3_*` bridge) [obs]: `0x6C0103FC01000404` = `STCYCL cl=4 wl=4` + `UNPACK V4-32 x1 -> VU1 data 0x3FC` (material colour, `rxPS2AllMatColASMFunc`), `0x6C0303FD01000404` = `UNPACK V4-32 x3 -> 0x3FD` (surface props + clip vectors `skyClipVect1`/`skyCClipVect1`), Gem/Emb variants add `UNPACK x1 -> 0x3FA/0x3FB` and `0x6C0B03BC` (`x11 -> 0x3BC`, lighting/matrix block); a GIF tag (`gifTag128 0x9658a0`, PRIM field = `transType | mesh+41`), then an A+D block `0x1000000000008003` (3 regs: TEST_1, TEX0_1, CLAMP_1 shadows `gp-17072/-17040/-17048`) when textured, and the `MSCAL` of the selected code-array entry. The 2D/PTank/Im3D pipes use the same skeleton with `DIRECT` (`0x50000002/4/6`) A+D blocks for TEX0/TEX1/ALPHA/TEST [obs, Ghidra constant census of `0x46cd90`].

Texture upload (`skyFillInPktForUpLoadAlignedContiguousRectangle 0x4ef020`) [obs]: per 32750-qword slice `DMA cnt 1 | VIF NOP, DIRECT 1 | GIFtag IMAGE (0x0800000000000000|nloop)`, then `DMA ref qwc,addr | VIF NOP, DIRECT qwc`, and a trailer `DMA cnt 2 | DIRECT 2 | GIFtag A+D x1 | <TEXFLUSH prebuilt at 0x965A40>`; `BITBLTBUF/TRXPOS/TRXREG/TRXDIR` come from the caller (`skyPrepareUploadRaster 0x4ef1d0`) — all **PATH2 (VIF1 DIRECT)**, never PATH3/GIF FIFO (0 `lui 0x1000`+`0x6000` sites) [obs]. Palette upload: `skyTexCacheUploadPalette 0x4f0c70` -> `_rwDMAAddImageUpload 0x4d6250`.

## 4. GS register / state census [obs/der]

Privileged registers (`lui 0x1200`): only `sceGsPutDispEnv 0x4f94e0` (9), `sceGsExecStoreImage 0x4f9e28` (7, used by `SkyRasterLock` x4 = read-back of GS memory), `_rwDMAVSYNCHandler 0x4d47f0` (4: flips `DISPFB` at vblank), `sceGsResetGraph 0x4f8eb0` (3, from `SkyStart 0x4e1060` x5), `sub_2C8260` (1), `adxm_fs_proc` (1, FLIRT name doubtful) [obs]. Topic 10 owns the display-env values; cross-reference `10_frame_loop_gs.md`.

RW render-state funnel `_rwSkySetRenderState 0x4d6b90` (RW `rwRENDERSTATE*` -> GS shadows, each flush = `_rwDMAOpenVIFPkt(0x80000000,2)` + `GIFtag 0x1000000000008001` + one A+D qword) [obs, Hex-Rays]:

| RW state (case) | GS field | values seen in the switch |
|---|---|---|
| 29 ALPHATESTFUNCTION | TEST_1 bits 0-3 (ATE,ATST) | 1->`ATE=1,ATST=NEVER`, 2->LESS(5), 3->EQUAL(9) [ATST 4], 4->LEQUAL(7) [ATST 3] (labels corrected 2026-10-18; values unchanged), 5->GEQUAL(0xD), 6->GREATER(0xF), 7->NOTEQUAL(0xB), 8->ALWAYS(2) |
| 30 ALPHATESTFUNCTIONREF | TEST_1 AREF bits 4-11 | caller value |
| 9 TEXTUREFILTER | TEX1_1 MMAG/MMIN bits 5-8 | 1->0, 2->0x60, 3->0x80, 4->0x120, 5->0xC0, 6->0x160 (nearest, linear, mip-nearest, mip-linear, linear-mip-nearest, linear-mip-linear) |
| 10/11 TEXTUREADDRESS U/V | CLAMP_1 WMS/WMT (+ bit 39 flag) | 1 wrap, 2 mirror, 5 clamp, 6 border, 7, 8 |
| 15 FOGCOLOR | FOGCOL (RGB byte-swapped) | caller value |
| 8/12/13/14/16/20 | ZWRITE/ZTEST/FOG/SRC-DEST blend/CULL (shadows `gp-17072`, `gp-20272` flags) | see Hex-Rays `ida/logs/vu1/hx/004d6b90.c` (575 lines) |

Game-facing funnel `RpSkyRenderStateSet 0x4d7f60` (hint name; semantics verified) [obs]: case 1 dither -> `DIMX` (`0x6071243571603524` standard matrix, `0x1212303012123030` alternate, 0 off), case 2 -> `ALPHA_1` raw (`A/B/C/D` low byte, FIX from bits 24-31), case 3 -> low 16 bits of `TEST_1` (ATE/ATST/AREF/AFAIL/DATE/DATM; ZTE/ZTST kept), case 4/5 -> two `gp` globals (no packet). Call-site argument census over 665 sites [der, lui/li/ori walk-back]:

| state | value | sites | emitting functions (sample) |
|---|---|---|---|
| 2 | `0x44` | 219 | H_Maestro_UpdateCutInDrawTask, K_Clump_SetupRender, K_Draw_UpdateCircleDrawTask, K_FldFilter_Main, K_FldShadow_UpdateShadowMapTask, K_FldSrc_DrawFieldOpaque |
| 2 | `0x48` | 75 | H_Maestro_UpdateCutInDrawTask, Y_Misc_UpdateTmxDispProcTask, bsRootDraw, gcModelDraw, opMenuDraw, opMenuDraw2 |
| 2 | `<move>` | 9 | btlBossDrawScreenOverlay, mdlEffectDrawEffect, sub_2FE780 |
| 2 | `<lw>` | 6 | mdlEffectDraw2PassScreenEffect, mdlEffectScreenEffectType2Draw, sub_315C20, sub_317A20, sub_34B010, sub_34EAE0 |
| 2 | `0x42` | 5 | sprDrawSprite, sub_1A8140, sub_1A8B10, sub_224150, sub_34EAE0 |
| 2 | `0x6a` | 5 | bsRootDraw, gcModelDraw, opMenuDraw |
| 2 | `0x58` | 5 | bsRootDraw, gcModelDraw, opMenuDraw |
| 2 | `<ori>` | 4 | mdlEffectDraw2PassScreenEffect, mdlEffectScreenEffectType2Draw, sub_34B010, sub_34EAE0 |
| 2 | `0x6` | 1 | K_FldFilter_Main |
| 2 | `0x54` | 1 | opWaitDraw |
| 2 | `0x64` | 1 | sub_315C20 |
| 2 | `0x2024` | 1 | mdlEffectDrawCrossfadeWipe |
| 3 | `<ori>` | 317 | H_Maestro_UpdateCutInDrawTask, K_Clump_SetupRender, K_Draw_UpdateCircleDrawTask, K_FldFilter_Main, K_FldShadow_UpdateShadowMapTask, K_FldSrc_DrawFieldOpaque |
| 3 | `<move>` | 9 | btlBossDrawScreenOverlay, mdlEffectDrawEffect, sub_2FE780 |
| 3 | `<lw>` | 2 | sub_315C20, sub_317A20 |
| None | `0x44` | 2 | K_FldFilter_Main, sub_1A8B10 |
| None | `0x48` | 1 | K_FldFilter_Main |
| None | `0x42` | 1 | K_FldFilter_Main |
| None | `<ori>` | 1 | sub_229B40 |

Decoded `ALPHA_1` tuples (A,B,C,D): `0x44` -> (Cs-Cd)*As+Cd normal blend; `0x48` -> (Cs-0)*As+Cd additive; `0x42` -> (0-Cs)*As+Cd subtractive; `0x6A` -> (0-0)*FIX+Cd (colour write off / Z-only); `0x58` -> (Cs-0)*Ad+Cd; `0x54` -> (Cs-Cd)*Ad+Cd; `0x64` -> (Cs-Cd)*FIX+Cd; `0x06` -> (0-Cd)*As+Cs; `0x2024` -> (Cs-Cd)*FIX+Cs [der]. The alpha-test half (state 3, 317 sites) is built with `lui`+`ori` into a scratch register that the walk-back did not resolve: **values not yet tabulated** (§7). `PRIM` fields are not constants: the GIF tag PRIM is `transType | mesh prim flags` at run time (§3), so the primitive census is **tri-strip/tri-list/line/point via RW prim type (def `+88`) with `IIP/TME/FGE/ABE/FST` from the mesh/material flags** [obs]; `SPRITE` prims appear only in Im2D/PTank/Rt2d output [inf].

## 5. Frame buffer, textures, CLUT [obs/inf]

- `videoModes 0x77e710` entry 82 (24 bytes each): `640, 448, 32, flags 0x203, 60, format 0x500` [obs; table typed by topic 10 as `RwVideoMode[90]`, see `10_frame_loop_gs.md`]; `SkyUseMode 0x4dff20` copies it to `customMode 0x965730..` and selects frame mode (`flags & 0x100 == 0` -> `byte_965760 = 2`) [obs]. `SkyCreateFBRaster 0x4e3100` creates the camera raster with `RwRasterCreate(w,h,depth, format|rwRASTERTYPECAMERA)` and writes `FRAME`-style fields (`FBW` from `gp-17080>>16`, `PSM` from `>>24`, TW/TH log2) into the raster private data; `SkyCreateDBRaster 0x4e3320` builds the second (display) buffer likewise with the ZBUF-style bits from `qword_9649A0`; `RpSkySelectDeepZBuffer(0)` [obs] -> `g_skyZBufferDepth 0x7CDDD8 = 16` (`0x4D82D0`) -> ZBUF PSM `0xA` = **PSMZ16S** [obs]. Frame/Z placement is static for mode 82: `SkyStart` computes `pages = 140` (`0x4E17C8`–`0x4E1850`) and writes FBP 140 into `disp[1].DISPFB`/`draw0`/`draw02` (`0x4E1864`–`0x4E187C`) and ZBP 280 into the draw envs (`0x4E1A14`, `0x4E1A2C`, …), FBP 0 stays in `draw1`/`draw12` [obs]; only texture/CLUT `TBP/CBP` come from RW's run-time allocator (`_rwSkyRasterFinaliseStart 0x4e40b0`, `SkyRasterCreate 0x4db350`, texture cache `skyTexCacheOpenCache 0x4f0990` from page 350 = `g_skyTexCacheStartWord 0x7CEA9C`) — the backend must mirror that allocator or trace it at run time (Phase 3 item).
- Textures: `.TMX` -> `uttmxCreateRaster 0x10e880` maps the TMX PSM byte to RW formats: `20/44/36 (PSMT8/PSMT4HH/PSMT8H) -> PAL8 (0x4000)`, `19/27 (PSMT4/PSMT4HL) -> PAL4 (0x2000)`, `2/10 (PSMCT16/16S)`, `1 (PSMCT24)`, `0 (PSMCT32)`; raster created as `format | 0x504` (8888 | TEXTURE), pixels copied under `RwRasterLock`, palette under `RwRasterLockPalette` [obs]. RW texture dictionaries (`.RMD` chunk 0x16, 273 files) go through `RwTexDictionaryStreamRead` -> `SkyNativeTextureRead 0x4df9d0` [obs]. GS upload formats are therefore PSMCT32/24/16/16S, PSMT8/8H, PSMT4/4HL/4HH with CLUT in PSMCT32 (`skyTexCacheUploadPalette`) [obs for the TMX path; CLUT PSM inferred from RW defaults].
- Video (`H_SfdPlay_UpdateTask 0x10a860`): CRI Sofdec decodes into a locked RW raster (`RpSkyTexCacheRasterLock` x2, `sceDmaGetChan/sceDmaSync`) that is drawn as a texture; the IPU/`_sequenceHeader 0x4feee0` `DIRECT` sites belong to `_sceMpegNextHeader` [obs].

> **Correction 2026-10-18:** (a) the former "24-bit Z [inf]" inverted the flag: `RpSkySelectDeepZBuffer 0x4D82A0` stores depth **16** and zmax 65535.0 (`0x477FFF00`) when its argument is 0 (`0x4D82D0`–`0x4D82E4`), and 32 / 16777215.0 (24-bit) only when non-zero; `SkyStart` selects `zpsm = 0x3A` when `g_skyZBufferDepth == 16` (`0x4E1520`–`0x4E1534`, repeated at `0x4E158C`, `0x4E15F8`, `0x4E1664`) and `sceGsSetDefDrawEnv 0x4F9668` stores `ZBUF = sceGszbufaddr(…) | (zpsm & 0xF) << 24` (`sd $v0, 0x10($s0)` @`0x4F9740`; `sceGsSetDefDrawEnv2` @`0x4FA62C`) → PSM nibble `0xA` = PSMZ16S. (b) "no static GS memory map" over-generalised: FB/Z bases are constants of mode 82 (VAs above); only textures are dynamic. `10` §1.3 and §2.8–9 were right (resolved in RUNTIME_CONTRACT §8.2 items 1 and 5 / Q-11).

## 6. Runtime contract for Phase 3

1. **VU1**: interpret first; the 114 programs are RW code-generator output in 5 families (§1). HLE candidates in order of payoff: `g3_generic` (6 programs, every static mesh), `g3_skin` (6, every character), `g3_matfx`/`g3_skin_matfx` (48, env/bump variants), `rt2d_*` (6, all UI text/boxes), `ptank_*` (8, particles), `null_transform`. The 28 unreferenced programs need no HLE. Entry points: every program starts at VU1 address 0; the code arrays select a program, the bridge issues `MSCAL` with the entry offset (`RxPipelineNodePS2AllMatSetVIFOffset`, def `+104` = 180..276) [obs].
2. **VIF1**: `STCYCL (cl=wl=4)`, `UNPACK V4-32/V4-16/V4-8/V3-32/V2-32/V2-16/S-32/S-16m` (instance clusters), `MPG` (ret packets), `MSCAL/MSCNT/MSCALF`, `DIRECT` (GS A+D blocks and IMAGE uploads), `FLUSH*`, `STMASK/STROW` (mask-mode unpacks `V4-32m`, `V3-32m`, `S-16m` seen in `addCopyVU1*`/`RpSkyRenderStateSet`). PATH3 is unused for uploads (0 GIF-FIFO sites) [obs].
3. **GS**: registers written: PRIM (via GIF tag), RGBAQ/ST/UV/XYZ2/XYZF2 (from VU1 `xgkick` output, formats in the microcode), TEX0_1, TEX1_1, CLAMP_1, TEST_1, ALPHA_1, FOGCOL, DIMX (+DTHE), TEXFLUSH, BITBLTBUF/TRXPOS/TRXREG/TRXDIR + IMAGE data, FRAME/ZBUF/XYOFFSET/SCISSOR via `sceGsSetDefDrawEnv`/`SkyCameraBeginUpdate 0x4d84c0` (topic 10), privileged PMODE/DISPFB/DISPLAY/BGCOLOR via `sceGsPutDispEnv`. Context 2 registers were not seen in any constant [obs, limited to the decompiled set].
4. **Blend/test coverage** (§4): 9 ALPHA_1 equations; 8 alpha-test functions with 8-bit AREF; Z test/write from RW states 8/12; dither on/off with two matrices.

## 7. Open questions / blocked

- Transform-type bit layout that indexes the 8/28-entry code arrays (needs a read of `RpAtomicPS2AllPrimTypeTransTypeSetupFunc 0x4a05d0` and the matfx bridge).
- Alpha-test (`RpSkyRenderStateSet` state 3) value histogram: 317 sites, operands built in a scratch register — needs a data-flow walk rather than the immediate scan used here.
- Who references the 4-entry table `0x7bcf74` (programs `0x5CD3B0/0x5CD5B0/0x5CD820/0x5CD980`) and the 28 unreferenced programs; whether `_rpCreatePlatform*Pipelines 0x4a5210/0x4a52a0/0x4a5330` are PDS stubs (would confirm the dead-library hypothesis).
- The unnamed bridges `sub_472170` (pipe 0x10021) and `sub_473340` (pipe 0x1002a): by table position they are the `SkSpt` plain and `SkSptUva` material bridges [inf]; not named.
- Exact A+D register ids inside each bridge's `DIRECT` block (Hex-Rays loses the `pcpyld` register half; Ghidra keeps constants but not the pairing) — needs the Ghidra outputs in `ghidra/decomp_vu1/` read per bridge.
- Game-side GS writers outside RW: `sub_2C8260` (`lui 0x1200`), `sub_2C84B0/0x2C9E90/0x2CAAE0/0x2CD0C0/0x2CCF60` (`MSCALF/MSCNT`) in the `0x2C8000` band — probably the effect/particle (`eff*`) renderer; not read.

## Confidence

- VU1 inventory (count, VAs, sizes, hashes, table membership): **high** (byte-level, cross-checked by DMA tag QWC). Family purposes: **medium** (from the owning pipeline definition, not from reading the microcode). Unreferenced = dead: **low-medium**.
- Pipeline set / registration / RW components: **high** (Hex-Rays + xrefs).
- VIF code census: **high** for the unambiguous commands; **not covered**: `STCYCL/STMASK/STROW/FLUSH*` constants (ambiguous with addresses) beyond the ones seen in decompiled bodies.
- GS state funnel semantics: **high** for the switch mappings quoted; ALPHA census **high**; alpha-test census **not done**; per-bridge DIRECT register lists **low**.
- Frame buffer: mode/format **high**; GS memory map **not static** (stated).

> **Correction 2026-10-18 (from `09_vu1_micro_census.md`):** the `br` column of the program inventory (sum 15,378) counted `LOI` immediates as branches because the upper-instruction I bit was ignored; the decoded branch total is **14,751** (IBEQ 6,782, IBNE 4,333, B 2,613, BAL 280, JR 176, …), none leaving its program, 73 relying on the 16 KiB PC wrap. Units, `E` counts and `XGKICK` counts agree on all 114 rows.
