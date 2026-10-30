# 03 — Strings of interest

The generated tables below are grouped by category (a string may appear in several). "Referenced from" is the first two IDA xrefs with the containing function; `-` means IDA found no reference (often MIPS `lui/addiu` pairs IDA did not resolve, or data-table references). Observed facts cite addresses; groupings are inferred.

## Toolchain and middleware identity

* Game code: `MW MIPS C Compiler (2.4.1.01)` (ELF `.comment`, see 00). No `GCC:`/`ee-gcc`/`SN Systems`/`ProDG` banner exists for the game code itself.
* SCE SDK: `PsIIlibdma  3100` at `0x77f2c0` → libdma from **SDK 3.1.0**, matching the disc's `LIB31/IOPRP310.IMG`. Library-internal strings place the SDK objects: libgraph (`sceGsDefDispEnv/PutDrawEnv/SyncPath/ExecStoreImage` messages, `0x7bd080..0x7bd328`, code `0x4F9168..0x4F9E28`), libdma (`0x7bd450`, code `0x4FA798`), libmpeg/libipu (`0x7bd650..0x7bd930`, code `0x4FEA28..0x500278`), libkernel (`SceKernelLibc`, `SceKerneltopThread`, `SceKernelDelayThread` `0x7bda88..0x7be0c0`, code `0x503E60..0x50D418`), sifrpc (`SceSifrpcGod/Bind/Call` `0x7bdd10..0x7bdd30`, code `0x506D88..0x507230`), fileio/stdio (`SceStdio*Sema` `0x7bdd40..0x7bdfd8`, code `0x507960..0x50B3B8`), libcdvd (`0x7be0d8..0x7be2b8`, code `0x50F738..0x510960`), libpad (`0x7be358..0x7be3f8`, code `0x511138..0x511590`), libsdr (`0x7be488`, `0x512868`), libmc2 (`sceMc2_*` `0x7be4f0..0x7be668`, code `0x5130E8..0x51AE68`), libdbc (`0x7be6a0..0x7be928`, code `0x51C3B8..0x51D460`). These address bands are the first cut of the SDK HLE map for Phase 3.
* CRI middleware (all `Ver.x.xx Build:Feb 28 2005 / Mar 1-2 2005`, each followed by `Append: GCC2096 SCE3020` = built with ee-gcc 2.96 against SCE SDK 3.0.2): ADX family (ADXT 9.44 `0x7c2268`, ADXF 7.30 `0x7c1a88`, ADXRT 3020 `0x793ad8`, ADXCS, ADXENC, AHX 1.44, AIXP 2.21), file system (CVFS 2.39 `0x7c3958`, ROFS 1.77 `0x7c7200`, ROCI, RSU, DVCI 2.71 `0x7c4be0`, HTCI 2.69 `0x7c4ff0`, SRD 2.22, LSC, MFCI), Sofdec video (MWSFD 3.50 `0x7c8490`, CRI SFD/SFH/SFX/SUD/M2V/MPS/MPV `0x7c7918..0x7cab70`, `mwPly*` error strings `0x7c85f0..0x7c99e0`), PS2RNA 1.32, SJ 6.31 / SJX / SJRMT / SVM. The audio HLE must cover both this ADX stack and the Sony `MOD*/SK*` sequencer stack (IRX list below).

## IOP modules and device paths (observed)

* `0x197030` (first call of `main_loop_candidate`) references every `cdrom0:\LIB31\<name>.IRX;1` string at `0x678540..0x678700`: SIO2MAN, SIO2D, PADMAN, DBCMAN, MC2_S1, LIBSD, CRI_ADXI, SDRDRV, MODHSYN, MODMSIN, MODSESQ, SKSOUND, SKHSYNTH (twice), SKSESQ, plus the template `cdrom0:\LIB31\%s;1` (`0x678510`). This is the IOP module loader and the canonical list of IRX dependencies the runtime must HLE.
* `rom0:UDNL ` (`0x7be000`, from `0x50CA18`) = IOP reboot with an IOPRP image (libcdvd/sif path); `rom0:ROMVER` (`0x7bd070`, `0x4F90B8`) = libgraph reading the ROM version to pick NTSC/PAL defaults; `host:` (`0x7c5500`, CRI HTCI host-file cache — dev path); `pfs0:` (`0x7cb268`); `cdrom0:\` (`0x5e4e38`, game file layer `0x1934F0`).

## Leaked source file names (182) — module map

All are bare file names (the MW build strips directories) except CRI's relative paths `../../rofs_hn.c, rofs_if.c, rofs_mai.c, rofs_pfs.c, rofs_dir.c, pfs_cvfs.c` (`0x7c6fc0..0x7c7718`). Each is referenced by one or two functions — the per-file error/assert reporter — which lets us attribute code regions to Atlus source files:

| Prefix | Files (examples) | Code band | Likely subsystem (inferred) |
|---|---|---|---|
| `kwln*` | `kwlnTask.c` (`0x5e4e98`), `kwlnRoot.c` | `0x1939D0..0x198C60` | Atlus task kernel ("kwln"), hosts `main_loop_candidate` |
| `h_*`, `_h_camp_*` | `h_chkmem.c`, `h_fade.c`, `h_sfdply.c`, `h_sndcom.c`, `h_camp.c`, `_h_camp_status/persona/comu/system/fr_status.c`, `h_malloc.c` | `0x103DA0..0x191AF0` | high-level game: camp (pause) menu, memory, fade, Sofdec playback, sound |
| `k_*` | `k_field.c`, `k_dungeon.c`, `k_event.c`, `k_unit.c`, `k_fldCamera.c`, `k_encount.c`, `k_battle.c`, `k_sceneDraw.c`, `k_shadow.c`, `k_clump.c`, `k_epl.c` | `0x199440..0x1D9860` | field/dungeon engine |
| `btl*`, `dat*` | `btlAction.c`, `btlFormation.c`, `btlAICommand.c`, `btlAIScript.c`, `btlEfficacy.c`, `btlBossElizabeth.c`, `datUnit.c`, `datCalc.c`, `datScript.c`, `datPersona.c` | `0x28DBF0..0x30FC40` | battle core and data tables |
| `br_*`, `bp_*`, `bpp_*`, `bcm_*`, `bai_*`, `brp_*`, `sfl_*`, `gc_*`, `baus_*` | `br_root.c`, `bp_main.c`, `sfl_root.c`, `sfl_card.c`, `gc_model.c`, … | `0x1EF7F0..0x27BBA0` | battle UI/result/panels, shuffle time |
| `scr*` | `scrScriptProcess.c`, `scrCommonCommand.c`, `scrComuCommand.c`, `scrTraceCode.c` | `0x35AEF0..0x35F680` | BF script VM (`>>>SCRIPT TRACE <0x%X>` at `0x69d470`) |
| `mt_evt*`, `mt_scene*` | `mt_evtMain.c`, `mt_evtMenu.c`, `mt_evtLoadSave.c`, `mt_evtPolygonMovie.c`, `mt_evtPMFileReader.c`, `mt_evtMessage.c`, `mt_scene.c` | `0x361350..0x3BAC40` | event system, PM1/PM2 model files, save/load |
| `itf*`, `fr*`, `fm*`, `resrc*` | `itfPanel.c`, `itfMesManager.c`, `frFont.c`, `frFontRaster.c`, `frTagTable.c`, `fmGslCont.c`, `resrcManager.c` | `0x3A2150..0x3B50D0` | UI panels, BMD message/font rendering, resources |
| `comu*`, `nm*`, `fcl*` | `comuFunction.c`, `comuEventExec.c`, `fclCombine*.c`, `fclShop*.c`, `fclBankManager.c` | `0x3BDBD0..0x4176F0` | social links, Velvet Room fusion, shops |
| `op_*`, `gm_*`, `ed_*`, `admini.c`, `y_stparts.c` | `op_title.c`, `op_logo.c`, `op_menu.c`, `ed_scroll.c` | `0x265030..0x27C080`, `0x43CA30` | title/opening/ending |
| `G3_2D*_Node.c` | `G3_2DStroke_Node.c`, `G3_2DFont_Node.c`, `G3_2DFill_Node.c` | `0x46F400..0x470E10` | "G3" 2D renderer nodes (`%s(%d): DMA memory failure`) — in the MMI-heavy band |
| `uttmx.c`, `k_epl.c`, `ed_sr.c`, `h_snd.c` | `0x7cb548..0x7cc4f0` | unreferenced | TMX texture utils, EPL effects |

## Asset paths and format strings

* 1,528 strings carry asset extensions (first 400 in the table; full list in `ida/logs/strings_all.txt`). Two path styles coexist: lowercase forward-slash (`battle/effect/OVERHEAT.BED` `0x696a80`) and uppercase backslash roots (`\FIELD\SCRIPT\`, `\SCRIPT\EVENT\` `0x5ce4a8..0x5ce508`) — inferred: two file APIs (CRI ROFS vs the game's own CVM path layer); to be resolved in Phase 2's file-I/O analysis.
* Debug/assert format strings with file:line survive only as generic `[%s:%d]` (`0x7bb730`, `0x7bb790`, `0x7cd6f8..0x7cd7c0`, used by `0x3D3D20`/`0x3D4FF0`) and `(%d)%s[%s]#%s:%d` in CRI ROFS (`0x7c7518`). `ASSERT!! Comp flag Invalid Value!!` (`0x69d550`), `CAUTION!! READ OLD VER … DATA` (`0x678ff0`, `0x684090`, `0x684450`) and `Process stat Invalid!!`/`kwlnTask.c` (`0x193a0c`) show assertion reporting is still compiled in and routes through `nullsub_9` (a stubbed-out printf) — i.e. the retail build silenced output rather than removing the checks.

## Generated data

<!-- GENERATED:BEGIN (export_symbols.py) -->
_Generated 2026-10-21 06:38:58 by `tools/ours/ida/export_symbols.py` from `ida/p3fes.i64` (ELF SHA-256 `d1b163eb20cb72d8764d2b94a8751abfc9e82fce7ae9e692dfaf97d64e3957bc`). Do not edit inside the markers._

Total strings in IDA string list: 6887; strings containing `%`: 633. Full list: `ida/logs/strings_all.txt` (gitignored).

### Source paths (`*.c/*.cpp/*.h/*.s`) — 182 hits

| Address | String | Referenced from |
|---|---|---|
| `0x005ceb30` | `h_chkmem.c` | 0x103ee8 (sub_103DA0) |
| `0x005d3c98` | `h_chrdsp.c` | 0x105af4 (sub_1059B0) |
| `0x005d3ff0` | `h_fade.c` | 0x107dfc (sub_107B20) |
| `0x005d5250` | `h_sfdply.c` | 0x10a9d8 (sub_10A860) |
| `0x005d53c8` | `h_sndcom.c` | 0x10cd54 (H_Sndcom_CopyToIop), 0x10cf18 (H_Sndcom_Update) |
| `0x005d58a8` | `h_cutin.c` | 0x1108f4 (sub_1107D0) |
| `0x005d6f80` | `h_perefect2.c` | 0x117d58 (sub_117540), 0x117da0 (sub_117540) |
| `0x005dacd0` | `h_camp.c` | 0x11b164 (sub_11B0B0) |
| `0x005db080` | `_h_camp_status.c` | 0x126a0c (sub_1269A0), 0x126a60 (sub_1269A0) |
| `0x005db170` | `_h_camp_persona.c` | 0x13384c (sub_133780) |
| `0x005dba38` | `_h_camp_comu.c` | 0x134be4 (sub_134A10), 0x135db8 (sub_1355C0) |
| `0x005dbc80` | `_h_camp_system.c` | 0x14f854 (sub_14F7D0), 0x14f8a8 (sub_14F7D0) |
| `0x005dbe30` | `_h_camp_fr_status.c` | 0x164a48 (sub_164920) |
| `0x005e3098` | `g_data.c` | 0x16ba24 (sub_16BA00), 0x16baa4 (sub_16BA80) |
| `0x005e3278` | `datPersona.c` | 0x173240 (sub_173220), 0x1732a0 (sub_173280) |
| `0x005e4418` | `h_permixefc.c` | 0x18ad58 (sub_18A9F0), 0x18ada4 (sub_18A9F0) |
| `0x005e4c48` | `h_malloc.c` | 0x191c78 (sub_191AF0), 0x191cc8 (sub_191AF0) |
| `0x005e4e98` | `kwlnTask.c` | 0x193a14 (kwlnTaskRemoveFromList), 0x193c10 (kwlnTaskAddToList) |
| `0x006787d8` | `kwlnRoot.c` | 0x198ad4 (kwlnRootUpdate2DDrawBeginTask), 0x198ce4 (kwlnRootUpdate3DOn2DDrawBeginTask) |
| `0x006788c8` | `k_spipe.c` | 0x199460 (sub_199440), 0x1995ac (K_SPipe_Update3DDrwBeginTask) |
| `0x00678948` | `k_shadow.c` | 0x19c04c (sub_19BEB0), 0x19c258 (sub_19BEB0) |
| `0x00678988` | `k_sceneDraw.c` | 0x19d9ac (K_SceneDraw_UpdateDrwOpcFldObjTask), 0x19dd98 (sub_19DB10) |
| `0x00678b08` | `k_lbox.c` | 0x1a3f6c (sub_1A3F20) |
| `0x00678c78` | `k_clump.c` | 0x1a8948 (sub_1A8920) |
| `0x00678df8` | `k_fldrc.c` | 0x1b1f58 (sub_1B10F0), 0x1b20b4 (sub_1B10F0) |
| `0x00679060` | `k_sequence.c` | 0x1b77cc (K_Seq_CallField), 0x1b791c (K_Seq_CallFieldEvent) |
| `0x0067f440` | `k_data.c` | 0x1b7cb4 (sub_1B7C40), 0x1b7f44 (sub_1B7E60) |
| `0x0067f578` | `k_field.c` | 0x1b9510 (K_Field_UpdateFieldRootTask), 0x1b9590 (K_Field_UpdateFieldRootTask) |
| `0x006833a0` | `k_dungeon.c` | 0x1bb0e8 (sub_1BB090), 0x1bb118 (sub_1BB090) |
| `0x00683660` | `k_command.c` | 0x1c2b38 (sub_1C2900), 0x1c2c54 (sub_1C2B80) |
| `0x00683730` | `k_event.c` | 0x1c8584 (sub_1C8120), 0x1c9d3c (K_FldEvent_UpdateFldEventTask) |
| `0x00683940` | `k_unit.c` | 0x1cfaf0 (sub_1CF940), 0x1d0814 (sub_1D0720) |
| `0x00683a78` | `k_fldCamera.c` | 0x1d5bb0 (K_FldCamera_CreateFieldCameraControlerTask), 0x1d64b0 (sub_1D6270) |
| `0x00683b28` | `k_encount.c` | 0x1d7aa0 (K_Encount_PickEncounter) |
| `0x00683b68` | `k_battle.c` | 0x1d8be8 (K_Battle_CreateBattleTask) |
| `0x00683b98` | `k_support.c` | 0x1d9934 (sub_1D9860), 0x1d9a0c (sub_1D9860) |
| `0x006844f8` | `eff_after.c` | 0x1e82cc (sub_1E7F90), 0x1e83a0 (sub_1E8360) |
| `0x00684508` | `eff_afpack.c` | 0x1ee380 (sub_1EE2E0), 0x1ee3c0 (sub_1EE2E0) |
| `0x00684578` | `br_root.c` | 0x1efcbc (brRoot_UpdateBattleResultTask), 0x1effc8 (brRoot_UpdateBattleResultTask) |
| `0x00684620` | `sfl_root.c` | 0x1f3520 (sub_1F3270), 0x1f362c (sub_1F3270) |
| `0x00684a28` | `sfl_result.c` | 0x1f590c (sub_1F58F0), 0x1f5968 (sub_1F5950) |
| `0x00684ba8` | `br_friend.c` | 0x1f9e64 (sub_1F9D70), 0x1f9ebc (sub_1F9E90) |
| `0x00684c28` | `br_data.c` | 0x1fb370 (sub_1FB1F0), 0x1fba20 (sub_1FB560) |
| `0x00684d60` | `pb_main.c` | 0x1fc76c (sub_1FC720), 0x1fcd0c (sub_1FCCC0) |
| `0x00684e38` | `bp_root.c` | 0x1fdc2c (sub_1FDC00), 0x1fde2c (sub_1FDDF0) |
| `0x00684e48` | `bp_misc.c` | 0x1ff450 (sub_1FF430), 0x1ff4c8 (sub_1FF430) |
| `0x00684f48` | `bcm_main.c` | 0x1ff8a8 (sub_1FF890), 0x1ffc80 (sub_1FFC60) |
| `0x006850a8` | `baus_main.c` | 0x208aec (sub_208AD0), 0x208b60 (sub_208B30) |
| `0x0068e080` | `sfl_data.c` | 0x209d94 (sub_209D40) |
| `0x0068e0a0` | `gc_model.c` | 0x20b28c (sub_20B250), 0x20c5b4 (sub_20C590) |
| `0x0068e118` | `sfl_res.c` | 0x20d7ec (sub_20D7D0), 0x20d844 (sub_20D820) |
| `0x0068e208` | `bpp_main.c` | 0x20ed84 (sub_20ED70), 0x20ee10 (sub_20EDF0) |
| `0x0068e218` | `bsa_main.c` | 0x20fea4 (sub_20FE30), 0x2101f0 (sub_20FE30) |
| `0x0068e228` | `sfl_psel.c` | 0x215a6c (sub_215A50), 0x215ab4 (sub_215AA0) |
| `0x0068e238` | `gc_res.c` | 0x219cac (sub_219C90), 0x219db0 (sub_219D90) |
| `0x0068e2d0` | `bse_main.c` | 0x21b690 (sub_21B670), 0x21b704 (sub_21B6F0) |
| `0x0068e2e0` | `bp_res.c` | 0x21b95c (sub_21B940), 0x21bac4 (sub_21BAB0) |
| `0x0068e370` | `bp_tex.c` | 0x21ed20 (sub_21EC40), 0x21edf8 (sub_21EC40) |
| `0x0068e380` | `bcm_panel.c` | 0x21f0dc (sub_21F0C0), 0x21f178 (sub_21F150) |
| `0x0068e690` | `bpp_panel.c` | 0x22c870 (sub_22C850), 0x22c8e4 (sub_22C8A0) |
| `0x0068e6a0` | `br_res.c` | 0x23398c (sub_233970), 0x2339e8 (sub_2339D0) |
| `0x0068e790` | `br_panel.c` | 0x23497c (sub_234960), 0x234a34 (sub_234A00) |
| `0x0068e7a0` | `bp_ifont.c` | 0x2389d0 (bpIfontDrawNumber), 0x238ac0 (sub_238A50) |
| `0x0068e7b0` | `sfl_ground.c` | 0x23918c (sub_239170), 0x239294 (sub_239280) |
| `0x0068e860` | `sfl_panel.c` | 0x23d7c4 (sub_23D7B0), 0x23d808 (sub_23D7F0) |
| `0x0068e870` | `bi_main.c` | 0x23f49c (sub_23F480), 0x23f514 (sub_23F500) |
| `0x0068e880` | `bpc_main.c` | 0x242c74 (sub_242C60), 0x242ce4 (sub_242CC0) |
| `0x0068e890` | `bpm_main.c` | 0x2484b4 (sub_2484A0), 0x24851c (sub_248500) |
| `0x0068e8a0` | `bpe_main.c` | 0x249264 (sub_249250), 0x2492cc (sub_2492B0) |
| `0x0068e8c8` | `bp_list.c` | 0x24a284 (sub_24A260) |
| `0x0068e8d8` | `bas_main.c` | 0x24a700 (sub_24A6E0), 0x24a764 (sub_24A750) |
| `0x0068e8e8` | `brp_birth.c` | 0x24a890 (sub_24A870), 0x24aaa8 (sub_24AA90) |
| `0x0068e928` | `brp_res.c` | 0x24ba6c (sub_24BA50), 0x24bb50 (sub_24BB30) |
| `0x0068e980` | `bai_main.c` | 0x24c134 (sub_24C110), 0x24ccc0 (sub_24CCA0) |
| `0x0068e990` | `sfl_camera.c` | 0x24d12c (sub_24D110), 0x24d174 (sub_24D160) |
| `0x0068e9a0` | `gc_pose.c` | 0x24da34 (sub_24DA20), 0x24da7c (sub_24DA60) |
| `0x0068e9c0` | `bp_tut.c` | 0x251074 (sub_251060), 0x2510a0 (sub_251060) |
| `0x0068e9d0` | `bp_tuta.c` | 0x251a98 (sub_251A80), 0x251e28 (sub_251E10) |
| `0x0068e9e0` | `bpo_main.c` | 0x251f64 (sub_251F40), 0x252074 (sub_252060) |
| `0x0068e9f0` | `bpd_main.c` | 0x252ea4 (sub_252E90), 0x252ef4 (sub_252EE0) |
| `0x0068ea00` | `sfl_card.c` | 0x25357c (sub_253560), 0x2536dc (sub_2536B0) |
| `0x0068eb18` | `sfl_script.c` | 0x259654 (sub_259640), 0x2596b4 (sub_259690) |
| `0x0068ebb8` | `sfl_cursor.c` | 0x25a144 (sub_25A130), 0x25a468 (sub_25A440) |
| `0x0068ebc8` | `sfl_count.c` | 0x25b4c4 (sub_25B4B0), 0x25b510 (sub_25B4F0) |
| `0x0068ebd8` | `bp_dialog.c` | 0x25be14 (sub_25BE00), 0x25be98 (sub_25BE60) |
| `0x0068ebe8` | `bp_rush.c` | 0x25cf40 (sub_25CF20), 0x25d034 (sub_25D020) |
| `0x0068ebf8` | `br_item.c` | 0x25d8c0 (sub_25D8A0), 0x25d9f4 (sub_25D9E0) |
| `0x0068ec18` | `sfl_psel2.c` | 0x260a24 (sub_260A10), 0x260a6c (sub_260A50) |
| `0x0068ec28` | `br_hero.c` | 0x2626fc (sub_2626E0), 0x262744 (sub_262730) |
| `0x0068ec38` | `br_persona.c` | 0x264d9c (sub_264D80), 0x264de4 (sub_264DD0) |
| `0x0068ec48` | `op_root.c` | 0x26504c (sub_265030), 0x265b48 (sub_265B30) |
| `0x0068ec58` | `gm_root.c` | 0x266158 (sub_266140), 0x2662fc (sub_266140) |
| `0x0068ec78` | `op_res.c` | 0x2666a8 (sub_266690), 0x26672c (sub_266710) |
| `0x0068ecc8` | `bp_persona.c` | 0x266ecc (sub_266EB0), 0x266f14 (sub_266F00) |
| `0x0068ed00` | `op_title.c` | 0x2673bc (sub_2673A0), 0x267404 (sub_2673F0) |
| `0x0068ed10` | `op_logo.c` | 0x269cdc (sub_269CC0), 0x269d24 (sub_269D10) |
| `0x0068ed20` | `op_menu.c` | 0x26a24c (opMenuSetWork), 0x26a294 (sub_26A280) |
| `0x0068ed30` | `op_wait.c` | 0x26dd2c (sub_26DD10), 0x26dd74 (sub_26DD60) |
| `0x0068ed40` | `op_fade.c` | 0x271d84 (sub_271D70), 0x271dc4 (sub_271DB0) |
| `0x0068ed88` | `brp_seq.c` | 0x27234c (sub_272330), 0x272394 (sub_272380) |
| `0x0068eea8` | `brp_root.c` | 0x275538 (sub_275520), 0x2755f0 (sub_2755D0) |
| `0x0068ef10` | `br_lvpnl.c` | 0x275aac (sub_275A90), 0x275bd4 (sub_275BC0) |
| `0x0068ef20` | `brp_persona.c` | 0x276948 (sub_276930), 0x2769e8 (sub_2769C0) |
| `0x0068ef30` | `brp_param.c` | 0x276d44 (sub_276D30), 0x276db8 (sub_276D90) |
| `0x0068ef40` | `ed_scroll.c` | 0x279c0c (sub_279BF0), 0x279ca8 (sub_279C90) |
| `0x0068ef80` | `ed_res.c` | 0x27ac94 (sub_27AC80), 0x27ad04 (sub_27ACE0) |
| `0x0068efc8` | `bp_select.c` | 0x27b5e4 (sub_27B5D0), 0x27b624 (sub_27B610) |
| `0x0068efd8` | `sfl_persona.c` | 0x27bb6c (sub_27BB50), 0x27bbb4 (sub_27BBA0) |
| `0x0068efe8` | `admini.c` | 0x27c0c4 (adminiChangeSeq), 0x27c0f0 (adminiChangeSeq) |
| `0x00693318` | `btlAction.c` | 0x28de88 (sub_28DBF0), 0x296454 (sub_296320) |
| `0x00696430` | `btlFormation.c` | 0x2b7120 (sub_2B7060), 0x2b72c8 (sub_2B71E0) |
| `0x00696f88` | `btlAICommand.c` | 0x2c2b44 (sub_2C2B20), 0x2c2de0 (sub_2C2D00) |
| `0x00697720` | `btlAIScript.c` | 0x2d0a88 (sub_2D0A30) |
| `0x006978e0` | `btlEfficacy.c` | 0x2d75ac (sub_2D7560) |
| `0x00697b18` | `btlSupport.c` | 0x2dbb88 (sub_2DBB00) |
| `0x0069a4b0` | `btlBossElizabeth.c` | 0x2f8f30 (sub_2F8EB0) |
| `0x0069aa70` | `datUnit.c` | 0x2ff570 (datUnitEcAddEnemy), 0x2ff594 (datUnitEcAddEnemy) |
| `0x0069aa80` | `datCalc.c` | 0x2ffbd8 (datCalcRand), 0x2ffd10 (datCalcGetLevel) |
| `0x0069ab78` | `datScript.c` | 0x30fca8 (datScriptCalc), 0x30fd04 (datScriptCalc) |
| `0x0069abc8` | `mdlManager.c` | 0x319b6c (sub_319970), 0x319dd4 (sub_319970) |
| `0x0069b1c0` | `mdlFile.c` | 0x31c054 (sub_31C000), 0x31c10c (sub_31C000) |
| `0x0069cee0` | `scrCommonCommand.c` | 0x35af18 (scrCommand_BIT_ON), 0x35af78 (scrCommand_BIT_OFF) |
| `0x0069cfb0` | `scrScriptProcess.c` | 0x35b5e4 (scrStartScript), 0x35b624 (scrStartScript) |
| `0x0069d1e8` | `scrTraceCode.c` | 0x35c340 (CodeFunc_PushI), 0x35c3e8 (CodeFunc_PushS) |
| `0x0069d530` | `scrComuCommand.c` | 0x35f61c (sub_35F5B0), 0x35f6b8 (sub_35F680) |
| `0x0069d580` | `mt_evtMain.c` | 0x3613c8 (sub_361350), 0x361418 (sub_361350) |
| `0x0069e408` | `mt_evtMenu.c` | 0x36f51c (sub_36F500), 0x372c68 (sub_372C40) |
| `0x006a0a10` | `mt_evtMisc.c` | 0x386b24 (sub_386AE0), 0x388e30 (sub_388DF0) |
| `0x006a0b00` | `mt_evtLoadSave.c` | 0x38db1c (sub_38DAD0), 0x38e5b8 (sub_38DAD0) |
| `0x006a0c40` | `mt_evtPolygonMovie.c` | 0x3940a8 (sub_394070), 0x394298 (sub_394270) |
| `0x006a0f70` | `mt_evtEffect.c` | 0x3964e8 (sub_3964C0) |
| `0x006a1040` | `mt_evtCutin.c` | 0x397270 (sub_3971A0), 0x397320 (sub_3971A0) |
| `0x006a1090` | `mt_evtPMFileReader.c` | 0x397ba0 (sub_397950), 0x397c64 (sub_397950) |
| `0x006a1200` | `mt_evtCustomEvent.c` | 0x3984f8 (sub_3983E0), 0x398750 (sub_398530) |
| `0x006a1840` | `mt_evtMessage.c` | 0x39ec9c (sub_39EC70), 0x39ece4 (sub_39EC70) |
| `0x006a1900` | `mt_evtCardEffect.c` | 0x3a0f64 (sub_3A0E90), 0x3a1054 (sub_3A0E90) |
| `0x006a1a70` | `itfMesManager.c` | 0x3a21b0 (scrCommand_MSG), 0x3a22c4 (sub_3A2260) |
| `0x006a1bf8` | `itfPanel.c` | 0x3a882c (sub_3A87D0), 0x3a8b44 (sub_3A8B00) |
| `0x006a2698` | `frTagTable.c` | 0x3ae4e4 (sub_3AE420), 0x3ae514 (sub_3AE420) |
| `0x006a2730` | `frFont.c` | 0x3afa00 (frInitFontTable), 0x3afb0c (frAddFontStyle) |
| `0x006a2888` | `frFontEx.c` | 0x3b2c80 (sub_3B2C60), 0x3b2ec4 (sub_3B2CB0) |
| `0x006a2898` | `frFontRaster.c` | 0x3b3618 (frFontRasterCreate), 0x3b3a9c (frFontRasterDrawGlyph) |
| `0x006a2a18` | `fmGslCont.c` | 0x3b427c (sub_3B41A0), 0x3b42c8 (sub_3B41A0) |
| `0x006a2ab0` | `resrcManager.c` | 0x3b5124 (sub_3B50D0), 0x3b52a0 (sub_3B50D0) |
| `0x006a2be8` | `mt_scene.c` | 0x3b5f3c (sub_3B5E90), 0x3b7b88 (sub_3B7AC0) |
| `0x006a2dd8` | `mt_sceneFunc.c` | 0x3b895c (sub_3B88C0), 0x3bad04 (sub_3BAC40) |
| `0x006a3280` | `comuFunction.c` | 0x3bdc44 (sub_3BDBD0), 0x3bdfe8 (sub_3BDFC0) |
| `0x006a3290` | `comuTimerSequence.c` | 0x3bf898 (sub_3BF720), 0x3bfea4 (sub_3BFDB0) |
| `0x006a3318` | `comuSasoi.c` | 0x3c25ac (sub_3C2570), 0x3c2718 (sub_3C2630) |
| `0x006a3330` | `comuEventExec.c` | 0x3c3610 (sub_3C33C0), 0x3c3894 (sub_3C33C0) |
| `0x006a3d58` | `comuData.c` | 0x3c4070 (sub_3C4040), 0x3c409c (sub_3C4040) |
| `0x006a3de8` | `nmlist.c` | 0x3c4470 (sub_3C4430), 0x3c4528 (sub_3C44D0) |
| `0x006a3df8` | `nmSequence.c` | 0x3c5280 (nmSequenceAddStep), 0x3c529c (nmSequenceAddStep) |
| `0x006a3e08` | `nmCmdList.c` | 0x3c5e40 (nmCmdListSetDrawFunc), 0x3c5ea0 (nmCmdListSetUpdateFunc) |
| `0x006a3e18` | `fclMisc.c` | 0x3c77bc (sub_3C77A0), 0x3c8424 (sub_3C8400) |
| `0x006a4270` | `fclBankManager.c` | 0x3cf188 (sub_3CF160), 0x3cf268 (sub_3CF240) |
| `0x006a4648` | `fclCombine.c` | 0x3d2830 (sub_3D2740), 0x3d28a4 (sub_3D2740) |
| `0x006a5f70` | `fclCombineMisc.c` | 0x3d5550 (sub_3D5510), 0x3d5760 (sub_3D5730) |
| `0x006a6020` | `fclCombineList.c` | 0x3da114 (sub_3DA0C0), 0x3da400 (sub_3DA3E0) |
| `0x006a6af8` | `fclShop.c` | 0x3e09b8 (sub_3E0950), 0x3e6dd4 (sub_3E6DC0) |
| `0x006aede8` | `fclShopMisc.c` | 0x3f0014 (sub_3EFFF0), 0x3f0268 (sub_3F0240) |
| `0x006af950` | `fclDrawSprite.c` | 0x40ed88 (sub_40EC50), 0x40edac (sub_40EC50) |
| `0x006afbe0` | `fclShopBGManager.c` | 0x410f74 (sub_410E70) |
| `0x006b2ad0` | `fclCombineEffect.c` | 0x417198 (fclCmbEff_CreateCmbEffCalcTasks), 0x417750 (sub_4176F0) |
| `0x006b4878` | `y_stparts.c` | 0x43ce6c (Y_StParts_UpdateStratumPartsTask), 0x43ceb8 (Y_StParts_UpdateStratumPartsTask) |
| `0x006b5770` | `G3_2DStroke_Node.c` | 0x46fb50 (sub_46F400) |
| `0x006b58c0` | `G3_2DFont_Node.c` | 0x470744 (sub_470200) |
| `0x006b5a10` | `G3_2DFill_Node.c` | 0x4711e8 (sub_470E10) |
| `0x007b69e8` | `h_malloc.c` | 0x191c30 (sub_191AF0) |
| `0x007bb4d8` | `nmlist.h` | 0x3c84ec (sub_3C8400) |
| `0x007bb720` | `fclCombine.h` | 0x3d3dcc (sub_3D3D20), 0x3d51e8 (sub_3D4FF0) |
| `0x007bb780` | `fclCombine.h` | 0x3d3f1c (sub_3D3D20), 0x3d5144 (sub_3D4FF0) |
| `0x007c6fc0` | `../../pfs_cvfs.c` | 0x56575c (pfsCvfsSeek) |
| `0x007c6fe8` | `../../rofs_hn.c` | 0x565c48 (ROFS_Seek), 0x565c84 (ROFS_Seek) |
| `0x007c7068` | `../../rofs_if.c` | 0x5663cc (ROFS_SetPfsFuncTbl), 0x566464 (ROFS_AddVolume) |
| `0x007c72a8` | `../../rofs_mai.c` | 0x567c00 (sub_567BE0), 0x567c9c (RFMAI_MountG) |
| `0x007c7608` | `../../rofs_pfs.c` | 0x56a584 (dcfSeek), 0x56a5e4 (dcfTell) |
| `0x007c7718` | `../../rofs_dir.c` | 0x56be1c (rfdir_getDirEnt), 0x56c0a0 (rfdir_getDirEnt) |
| `0x007cb548` | `h_snd.c` | - |
| `0x007cb560` | `uttmx.c` | - |
| `0x007cc210` | `k_epl.c` | - |
| `0x007cc4f0` | `ed_sr.c` | - |

### Assertion / debug format strings mentioning file or line — 26 hits

| Address | String | Referenced from |
|---|---|---|
| `0x005e3260` | `no exist comu %s %d` | 0x16e710 (sub_16E670) |
| `0x005e4be0` | `file = %s  data_985588 = %d\n` | 0x190f94 (sub_190CD0) |
| `0x005e4ec8` | `%s+-%s [%d]` | 0x19476c (sub_194750) |
| `0x0069d550` | `ASSERT!! Comp flag Invalid Value!! objtype =%d\n` | 0x361000 (sub_360ED0) |
| `0x0069ef80` | `D(%d-%d)%s %d %d` | 0x377db8 (sub_3760A0) |
| `0x0069ef98` | `R(%d)%s %d %d` | 0x377e1c (sub_3760A0) |
| `0x0069efd8` | `L%d A%d %s` | 0x37843c (sub_3760A0) |
| `0x0069faf0` | `%s ch%d %d %d` | 0x37ca34 (sub_37C350) |
| `0x006a0fb0` | `reg effect [no %d]= %s  from file\n` | 0x3966ec (sub_3965F0) |
| `0x006a3200` | `error!! comuTableBinFile Version Invalid  SupportVersion=%d (%d)` | 0x3bd2f0 (sub_3BD280) |
| `0x006a3250` | `comuTableBinFile Load version=%d tableno=%d\n` | 0x3bd38c (sub_3BD280) |
| `0x006b5750` | `%s(%d): DMA memory failure\n` | 0x46fb4c (sub_46F400) |
| `0x006b58a0` | `%s(%d): DMA memory failure\n` | 0x470740 (sub_470200) |
| `0x006b59f0` | `%s(%d): DMA memory failure\n` | 0x4711e4 (sub_470E10) |
| `0x0077e380` | `lineto %f %f\n` | 0x4a8cfc (sub_4A8980) |
| `0x007bb730` | `[%s:%d]` | 0x3d3dc4 (sub_3D3D20), 0x3d51e0 (sub_3D4FF0) |
| `0x007bb790` | `[%s:%d]` | 0x3d3f14 (sub_3D3D20), 0x3d513c (sub_3D4FF0) |
| `0x007c4c78` | `DVCI: sceCdSearchFile failed. "%s"\n` | 0x55a14c (dvCiGetFileSize), 0x55a860 (sub_55A800) |
| `0x007c4d50` | `DVCI: File cache was not hit. "%s"\n` | 0x55a2a0 (dvCiOpen) |
| `0x007c5248` | `HTCI: File cache was not hit. "%s"\n` | 0x55be68 (sub_55BDC8) |
| `0x007c7518` | `(%d)%s[%s]#%s:%d` | 0x569790 (sub_569730) |
| `0x007c7530` | `(%d)%s#%s:%d` | 0x5697c0 (sub_569730) |
| `0x007cd6f8` | `[%s:%d]` | - |
| `0x007cd728` | `[%s:%d]` | - |
| `0x007cd758` | `[%s:%d]` | - |
| `0x007cd7c0` | `[%s:%d]` | - |

### SCE SDK / Sony library identifiers (`sce`, `SCE`) — 116 hits

| Address | String | Referenced from |
|---|---|---|
| `0x00678998` | `scene draw CTL` | 0x19f740 (K_SceneDraw_CreateTasks) |
| `0x0069df70` | `[evtEventViewerProcessSceneRead] data create!\n` | 0x36dd10 (sub_36DB20) |
| `0x0069dfa0` | `[evtEventViewerProcessSceneRead] scene read\n` | 0x36dd4c (sub_36DB20) |
| `0x006a2b60` | `Scene data cashe hit!! major=%d minor=%d\n` | 0x3b57b4 (MT_Scene_Load) |
| `0x006a2b90` | `Scene data load...\n` | 0x3b588c (MT_Scene_Load) |
| `0x006a2f60` | `SceneManager Task` | 0x3bd0c0 (sub_3BD0B0) |
| `0x006a2f80` | `SceneManager Draw` | 0x3bd0f0 (sub_3BD0B0) |
| `0x007bd080` | `sceGsDefDispEnv:Not support displaymode for 0x%x!!\n` | 0x4f94ac (sceGsSetDefDispEnv) |
| `0x007bd0b8` | `sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n` | 0x4f98f8 (sceGsPutDrawEnv) |
| `0x007bd0e8` | `sceGsSyncPath: DMA Ch.1 does not terminate\r\n` | 0x4f9b34 (sceGsSyncPath) |
| `0x007bd1c8` | `sceGsSyncPath: DMA Ch.2 does not terminate\r\n` | 0x4f9b40 (sceGsSyncPath) |
| `0x007bd1f8` | `sceGsSyncPath: VIF1 does not terminate\r\n` | 0x4f9b4c (sceGsSyncPath) |
| `0x007bd228` | `sceGsSyncPath: VU1 does not terminate\r\n` | 0x4f9b58 (sceGsSyncPath) |
| `0x007bd250` | `sceGsSyncPath: GIF does not terminate\r\n` | 0x4f9b5c (sceGsSyncPath) |
| `0x007bd280` | `sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n` | 0x4fa1d8 (sceGsExecStoreImage) |
| `0x007bd2b8` | `sceGsExecStoreImage: GS does not terminate\r\n` | 0x4fa1ec (sceGsExecStoreImage) |
| `0x007bd2e8` | `sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n` | 0x4fa21c (sceGsExecStoreImage) |
| `0x007bd328` | `sceGsExecStoreImage: Enough data does not reach VIF1\n` | 0x4fa220 (sceGsExecStoreImage) |
| `0x007bd650` | `_sceMpegSliceA0(): error happens` | 0x4feb50 (_sceMpegSliceA0) |
| `0x007bd8f0` | `Need to re-setup libipu since sceMpegGetPicture was aborted\n` | 0x5002d8 (_getpic) |
| `0x007bd930` | `sceMpegGetPicture is aborted\n` | 0x5002e8 (_getpic) |
| `0x007bda88` | `SceKerneltopThread` | 0x503f60 (InitThread) |
| `0x007bdaa0` | `SceKernelDelayThread` | 0x504210 (DelayThread) |
| `0x007bdd10` | `SceSifrpcGod` | 0x506e04 (sceSifGetOtherData) |
| `0x007bdd20` | `SceSifrpcBind` | 0x5070bc (sceSifBindRpc) |
| `0x007bdd30` | `SceSifrpcCall` | 0x507378 (sceSifCallRpc) |
| `0x007bdd40` | `SceStdioIobSema` | 0x507988 (_sceFsIobSemaMK) |
| `0x007bdd50` | `SceStdioQueSema` | 0x5079a8 (_sceFsIobSemaMK) |
| `0x007bddc8` | `SceStdioFioSema` | 0x508018 (_sceFsSemInit) |
| `0x007bdde0` | `SceStdioOpenSema` | 0x5087c0 (sceOpen) |
| `0x007bddf8` | `SceStdioCloseSema` | 0x508980 (sceClose) |
| `0x007bde10` | `SceStdioLseekSema` | 0x508b10 (sceLseek) |
| `0x007bde28` | `SceStdioReadSema` | 0x508d50 (sceRead) |
| `0x007bde40` | `SceStdioWriteSema` | 0x508fc0 (sceWrite) |
| `0x007bde58` | `SceStdioIoctlSema` | 0x509434 (sceIoctl), 0x509480 (sceIoctl) |
| `0x007bde70` | `SceStdioIoctl2Sema` | 0x509648 (sceIoctl2) |
| `0x007bde88` | `SceStdioCCodeSema` | 0x50981c (_sceCallCode) |
| `0x007bdea0` | `SceStdioMkdirSema` | 0x5099fc (sceMkdir) |
| `0x007bdeb8` | `SceStdioFormatSema` | 0x509c8c (sceFormat) |
| `0x007bded0` | `SceStdioAddDrvSema` | 0x509dd0 (sceAddDrv) |
| `0x007bdee8` | `SceStdioDcloseSema` | 0x50a000 (sceDclose) |
| `0x007bdf00` | `SceStdioDreadSema` | 0x50a170 (sceDread) |
| `0x007bdf18` | `SceStdioGetstatSema` | 0x50a328 (sceGetstat) |
| `0x007bdf30` | `SceStdioChstatSema` | 0x50a4d8 (sceChstat) |
| `0x007bdf48` | `SceStdioRenameSema` | 0x50a778 (sceRename) |
| `0x007bdf60` | `SceStdioSyncSema` | 0x50a954 (sceSync) |
| `0x007bdf78` | `SceStdioMountSema` | 0x50abbc (sceMount) |
| `0x007bdf90` | `SceStdioLseek64Sema` | 0x50ad70 (sceLseek64) |
| `0x007bdfa8` | `SceStdioDevctlSema` | 0x50b084 (sceDevctl) |
| `0x007bdfc0` | `SceStdioSymlinkSema` | 0x50b2d8 (sceSymlink) |
| `0x007bdfd8` | `SceStdioReadlinkSema` | 0x50b4b4 (sceReadlink) |
| `0x007be0b0` | `SceKernelLibc` | 0x50d418 (supplement_crt0) |
| `0x007be0c0` | `SceKernelLibcEh` | 0x50d41c (supplement_crt0) |
| `0x007be0d8` | `data_96DA00= %d sceCdCbfunc_num= %d\n` | 0x50f7c0 (_sceCd_cbLoop) |
| `0x007be100` | `SceCdCallbackThread` | 0x50f844 (sceCdInitEeCB) |
| `0x007be118` | `SceCdNcmdSema` | 0x50f9b8 (cmd_sem_init) |
| `0x007be128` | `SceCdScmdSema` | 0x50f9d8 (cmd_sem_init) |
| `0x007be138` | `SceCdRcmdSema` | 0x50f9f0 (cmd_sem_init) |
| `0x007be148` | `SceCdCallbackSema` | 0x50fa08 (cmd_sem_init) |
| `0x007be330` | `sceCdChgSys: Illegal_function_call\n` | 0x511120 (sceCdChgSys) |
| `0x007be3a8` | `libpad: sceSifSetDma faild\n` | 0x51155c (_send_to_iop) |
| `0x007be488` | `sceSdRemoteInit() RPC data_77F558 error!\n` | 0x5128b0 (sceSdRemoteInit) |
| `0x007be4b0` | `SceSdrCallbackThread` | 0x512dd4 (sceSdRemoteCallbackInit) |
| `0x007be4f0` | `sceMc2_sema_main` | 0x513130 (sceMc2Init) |
| `0x007be508` | `sceMc2_sema_start` | 0x513178 (sceMc2Init) |
| `0x007be520` | `sceMc2_sema_end` | 0x51319c (sceMc2Init) |
| `0x007be530` | `sceMc2_basic_thread` | 0x5131d4 (sceMc2Init) |
| `0x007be668` | `sceMc2_sema_subs` | 0x51ae74 (_sceMcCoreInit) |
| `0x007be710` | `sceDbc_sema` | 0x51c594 (sceDbcInit) |
| `0x007be740` | `sceDbcSetWorkAddr: rpc error\n` | 0x51c754 (sceDbcSetWorkAddr) |
| `0x007be760` | `sceDbcCreateSocket: rpc error\n` | 0x51c860 (sceDbcCreateSocket) |
| `0x007be780` | `sceDbcDeleteSocket: rpc error\n` | 0x51c924 (sceDbcDeleteSocket) |
| `0x007be7a0` | `sceDbcGetDepNumber: rpc error\n` | 0x51ca94 (sceDbcGetDepNumber) |
| `0x007be7c0` | `sceDbcInitSocket: rpc error\n` | 0x51cc3c (sceDbcInitSocket) |
| `0x007be7e0` | `sceDbcResetSocket: rpc error\n` | 0x51ccec (sceDbcResetSocket) |
| `0x007be800` | `sceDbcGetDeviceStatus: rpc error\n` | 0x51cd9c (sceDbcGetDeviceStatus), 0x51ce60 (sceDbcSearchPortSpecific) |
| `0x007be828` | `sceDbcSRData: rpc error\n` | 0x51cf88 (sceDbcSRData) |
| `0x007be848` | `sceDbcSendData: rpc error\n` | 0x51d100 (sceDbcSendData) |
| `0x007be8b8` | `sceDbcSendData2: rpc error\n` | 0x51d2b8 (sceDbcSendData2) |
| `0x007be928` | `sceDbcReceiveData: rpc error\n` | 0x51d4f4 (sceDbcReceiveData) |
| `0x007c1ab9` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c2299` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c393d` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c46f8` | `SRD: Drive Error (sceCdGetError = 0x%x)\r\n` | 0x5580cc (srd_check_dvd_error) |
| `0x007c4728` | `SRD: sceCdBreak is fail. %d\n` | 0x5581b4 (srd_exec_dvd) |
| `0x007c48e0` | `SRD: sceLseek64 error = %d\r\n` | 0x558bbc (sub_558B68) |
| `0x007c4900` | `SRD: sceLseek error = %d\r\n` | 0x558be8 (sub_558B68) |
| `0x007c4920` | `SRD: sceIoctl error = %d\r\n` | 0x558c5c (sub_558C20) |
| `0x007c4940` | `SRD: sceOpen error = %d\r\n` | 0x558cc8 (sub_558C98) |
| `0x007c4960` | `SRD: sceClose error = %d\r\n` | 0x558d24 (sub_558D00) |
| `0x007c4980` | `SRD: sceRead error = %d\r\n` | 0x558d94 (sub_558D58) |
| `0x007c4c78` | `DVCI: sceCdSearchFile failed. "%s"\n` | 0x55a14c (dvCiGetFileSize), 0x55a860 (sub_55A800) |
| `0x007c4d78` | `E0092911:sceCdSearchFile fail.(dvCiOpen)` | 0x55a2dc (dvCiOpen) |
| `0x007c5088` | `HTCI: sceOpen failed. "%s"\n` | 0x55bbb4 (sub_55BB30) |
| `0x007c50a8` | `E0092705:sceOpen fail.(sub_55BB08)` | 0x55bbb8 (sub_55BB30) |
| `0x007c50d0` | `HTCI: sceOpen failed. IOP Module version is invalid.\n` | 0x55bbdc (sub_55BB30) |
| `0x007c5108` | `E0082101:sceOpen fail.(sub_55BB08)` | 0x55bbe0 (sub_55BB30), 0x55bc04 (sub_55BB30) |
| `0x007c5130` | `HTCI: sceOpen failed. file desc is insufficient.\n` | 0x55bc00 (sub_55BB30) |
| `0x007c5168` | `E0092706:sceLseek fail.(sub_55BB08)` | 0x55bc6c (sub_55BB30) |
| `0x007c5198` | `E0092707:sceClose fail.(sub_55BB08)` | 0x55bcbc (sub_55BB30) |
| `0x007c5270` | `E0092711:sceOpen fail.(sub_55BDC8)` | 0x55becc (sub_55BDC8) |
| `0x007c5298` | `HTCI: Failed sceClose\n` | 0x55bfa0 (sub_55BF40) |
| `0x007c5358` | `HTCI: "%s" can'data_77DD78 Open.(sceOpen)\n` | 0x55cc10 (sub_55CB30) |
| `0x007c5380` | `HTCI: "%s" Opened.(sceOpen)\n` | 0x55cc38 (sub_55CB30) |
| `0x007c53e8` | `HTCI: "%s" can'data_77DD78 Close.(sceClose)\n` | 0x55cdac (sub_55CCE8) |
| `0x007c5410` | `HTCI: "%s" Closed.(sceClose)\n` | 0x55cda4 (sub_55CCE8) |
| `0x007c6338` | `PS2RNA: E01112903: Failed, sceSifAllocIopHeap(%d) in sub_55F748\n` | 0x55f7d8 (sub_55F748) |
| `0x007c6380` | `PS2RNA: sceSifAllocIopHeap(%d) ret=0x%08x\n` | 0x55f814 (sub_55F748), 0x560084 (PS2RNA_Init) |
| `0x007c64b8` | `PS2RNA: E01112902: Failed, sceSifAllocIopHeap(%d) in PS2RNA_Init.` | 0x560054 (PS2RNA_Init) |
| `0x007c6528` | `E02041101: Failed, sceSifAllocIopHeap(%d) in PS2RNA_Init.` | 0x560178 (PS2RNA_Init) |
| `0x007c780c` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c794d` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c79ed` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c7a55` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c84c2` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c9f95` | `Append: GCC2096 SCE3020\n` | - |

### Library / module names (`lib`, `.IRX`) — 43 hits

| Address | String | Referenced from |
|---|---|---|
| `0x005dd560` | `Excalibur` | 0x5de194, 0x5de198 |
| `0x00678510` | `cdrom0:\LIB31\%s;1` | 0x197068 (kwlnInitPS2Systems) |
| `0x00678540` | `cdrom0:\LIB31\SIO2MAN.IRX;1` | 0x197138 (kwlnInitPS2Systems) |
| `0x00678560` | `cdrom0:\LIB31\SIO2D.IRX;1` | 0x197158 (kwlnInitPS2Systems) |
| `0x00678580` | `cdrom0:\LIB31\PADMAN.IRX;1` | 0x197178 (kwlnInitPS2Systems) |
| `0x006785a0` | `cdrom0:\LIB31\DBCMAN.IRX;1` | 0x197198 (kwlnInitPS2Systems) |
| `0x006785c0` | `cdrom0:\LIB31\MC2_S1.IRX;1` | 0x1971b8 (kwlnInitPS2Systems) |
| `0x006785e0` | `cdrom0:\LIB31\LIBSD.IRX;1` | 0x1971d8 (kwlnInitPS2Systems) |
| `0x00678600` | `cdrom0:\LIB31\CRI_ADXI.IRX;1` | 0x1971f8 (kwlnInitPS2Systems) |
| `0x00678640` | `cdrom0:\LIB31\SDRDRV.IRX;1` | 0x19721c (kwlnInitPS2Systems) |
| `0x00678660` | `cdrom0:\LIB31\MODHSYN.IRX;1` | 0x19723c (kwlnInitPS2Systems) |
| `0x00678680` | `cdrom0:\LIB31\MODMSIN.IRX;1` | 0x19725c (kwlnInitPS2Systems) |
| `0x006786a0` | `cdrom0:\LIB31\MODSESQ.IRX;1` | 0x19727c (kwlnInitPS2Systems) |
| `0x006786c0` | `cdrom0:\LIB31\SKSOUND.IRX;1` | 0x19729c (kwlnInitPS2Systems) |
| `0x006786e0` | `cdrom0:\LIB31\SKHSYNTH.IRX;1` | 0x1972bc (kwlnInitPS2Systems), 0x1972dc (kwlnInitPS2Systems) |
| `0x00678700` | `cdrom0:\LIB31\SKSESQ.IRX;1` | 0x1972fc (kwlnInitPS2Systems) |
| `0x006794b4` | `Library` | - |
| `0x0077f2c0` | `PsIIlibdma  3100` | - |
| `0x007bd450` | `libdma: sync timeout\n` | 0x4fa7d4 (WaitDma), 0x4fa854 (WatchDma) |
| `0x007bd8f0` | `Need to re-setup libipu since sceMpegGetPicture was aborted\n` | 0x5002d8 (_getpic) |
| `0x007bda60` | `## internel error in libkernl.a!\n` | 0x503ed4 (topThread) |
| `0x007be0b0` | `SceKernelLibc` | 0x50d418 (supplement_crt0) |
| `0x007be0c0` | `SceKernelLibcEh` | 0x50d41c (supplement_crt0) |
| `0x007be160` | `Libcdvd data_77F558 err CdSearchFile\n` | 0x50fd28 (sceCdLayerSearchFile) |
| `0x007be1f8` | `Libcdvd data_77F558 err N CMD\n` | 0x51005c (_sceCd_ncmd_prechk) |
| `0x007be258` | `Libcdvd data_77F558 err S cmd\n` | 0x51035c (_sceCd_scmd_prechk) |
| `0x007be270` | `Libcdvd data_77F558 err %d CD_Init %d\n` | 0x510550 (sceCdInit) |
| `0x007be290` | `Libcdvd Exit\n` | 0x5106c4 (sceCdInit) |
| `0x007be2b8` | `Libcdvd data_77F558 err CdDiskReady\n` | 0x510858 (sceCdDiskReady_old), 0x510a44 (sceCdDiskReady) |
| `0x007be358` | `libpad: Module version mismatch ` | 0x511230 (scePadInit) |
| `0x007be380` | `[libpad.a = %d.%d, padman.irx = %d.%d]\n` | 0x51123c (scePadInit) |
| `0x007be3a8` | `libpad: sceSifSetDma faild\n` | 0x51155c (_send_to_iop) |
| `0x007be3c8` | `libpad: buffer addr is not 64 byte align. %08x\n` | 0x5115e8 (scePadPortOpen) |
| `0x007be3f8` | `libpad: pad port is already open [%d][%d]\n` | 0x511638 (scePadPortOpen) |
| `0x007be548` | `libmc2: TerminateTread faild\n` | 0x5132f4 (sceMc2End) |
| `0x007be640` | `libmc2: Fatal Error [%08x]\n` | 0x51674c (_sceMcFatFormat) |
| `0x007be6a0` | `libdbc: data_77F558 failed\n` | 0x51c5c4 (sceDbcInit) |
| `0x007be6b8` | `libdbc: Module version mismatch ` | 0x51c488 (sceDbcInit) |
| `0x007be6e0` | `[libdbc.a = %d.%02x, dbcman.irx = %d.%02x]\n` | 0x51c494 (sceDbcInit) |
| `0x007be720` | `libdbc: SifDmaAddr %08x\n` | 0x51c608 (sceDbcInit) |
| `0x007be868` | `libdbc: SendData2 data length too long [%d]\n` | 0x51d1a4 (sceDbcSendData2) |
| `0x007be8d8` | `libdbc: SendData3 data length too long [%d]\n` | 0x51d358 (sceDbcSendData3) |
| `0x007cd588` | `Library` | 0x6a35a4 |

### Device / path prefixes (`cdrom0:`, `host0:`, `mc0:`, `rom0:`) — 20 hits

| Address | String | Referenced from |
|---|---|---|
| `0x005e4e38` | `cdrom0:\` | 0x1935cc (H_FileSetup_UpdateTstDvdChkDrawTask), 0x19375c (H_FileSetup_UpdateTstDvdChkDrawTask) |
| `0x00678510` | `cdrom0:\LIB31\%s;1` | 0x197068 (kwlnInitPS2Systems) |
| `0x00678540` | `cdrom0:\LIB31\SIO2MAN.IRX;1` | 0x197138 (kwlnInitPS2Systems) |
| `0x00678560` | `cdrom0:\LIB31\SIO2D.IRX;1` | 0x197158 (kwlnInitPS2Systems) |
| `0x00678580` | `cdrom0:\LIB31\PADMAN.IRX;1` | 0x197178 (kwlnInitPS2Systems) |
| `0x006785a0` | `cdrom0:\LIB31\DBCMAN.IRX;1` | 0x197198 (kwlnInitPS2Systems) |
| `0x006785c0` | `cdrom0:\LIB31\MC2_S1.IRX;1` | 0x1971b8 (kwlnInitPS2Systems) |
| `0x006785e0` | `cdrom0:\LIB31\LIBSD.IRX;1` | 0x1971d8 (kwlnInitPS2Systems) |
| `0x00678600` | `cdrom0:\LIB31\CRI_ADXI.IRX;1` | 0x1971f8 (kwlnInitPS2Systems) |
| `0x00678640` | `cdrom0:\LIB31\SDRDRV.IRX;1` | 0x19721c (kwlnInitPS2Systems) |
| `0x00678660` | `cdrom0:\LIB31\MODHSYN.IRX;1` | 0x19723c (kwlnInitPS2Systems) |
| `0x00678680` | `cdrom0:\LIB31\MODMSIN.IRX;1` | 0x19725c (kwlnInitPS2Systems) |
| `0x006786a0` | `cdrom0:\LIB31\MODSESQ.IRX;1` | 0x19727c (kwlnInitPS2Systems) |
| `0x006786c0` | `cdrom0:\LIB31\SKSOUND.IRX;1` | 0x19729c (kwlnInitPS2Systems) |
| `0x006786e0` | `cdrom0:\LIB31\SKHSYNTH.IRX;1` | 0x1972bc (kwlnInitPS2Systems), 0x1972dc (kwlnInitPS2Systems) |
| `0x00678700` | `cdrom0:\LIB31\SKSESQ.IRX;1` | 0x1972fc (kwlnInitPS2Systems) |
| `0x007bd070` | `rom0:ROMVER` | 0x4f90cc (checkModelVersion) |
| `0x007be000` | `rom0:UDNL ` | 0x50ca38 (sceSifRebootIop), 0x50ca9c (sceSifRebootIop) |
| `0x007c5500` | `host:` | 0x55d1b0 (sub_55D198), 0x55d1b8 (sub_55D198) |
| `0x007cb268` | `pfs0:` | - |

### Atlus asset extensions (.CVM .PAC .BF .BMD .TMX .PM1 .AMD .ADX ...) — 1245 hits (first 400 shown)

| Address | String | Referenced from |
|---|---|---|
| `0x005ceb50` | `font/size12/f11_001.tmx` | 0x1042ec (sub_1042E0), 0x104310 (sub_1042E0) |
| `0x005ceb70` | `i_bust_01_11a.tmx` | 0x5d3350 |
| `0x005ceb90` | `i_bust_01_11b.tmx` | 0x5d3354 |
| `0x005cebb0` | `i_bust_01_21a.tmx` | 0x5d3358 |
| `0x005cebd0` | `i_bust_01_21b.tmx` | 0x5d335c |
| `0x005cebf0` | `i_bust_01_31.tmx` | 0x5d3360 |
| `0x005cec10` | `i_bust_01_61.tmx` | 0x5d3364 |
| `0x005cec30` | `i_bust_01_81.tmx` | 0x5d3368 |
| `0x005cec50` | `i_bust_01_91.tmx` | 0x5d336c |
| `0x005cec70` | `i_bust_01_a1.tmx` | 0x5d3370 |
| `0x005cec90` | `i_bust_01_c1.tmx` | 0x5d3374 |
| `0x005cecb0` | `i_bust_02_11a.tmx` | 0x5d3378 |
| `0x005cecd0` | `i_bust_02_11b.tmx` | 0x5d337c |
| `0x005cecf0` | `i_bust_02_12a.tmx` | 0x5d3380 |
| `0x005ced10` | `i_bust_02_12b.tmx` | 0x5d3384 |
| `0x005ced30` | `i_bust_02_13a.tmx` | 0x5d3388 |
| `0x005ced50` | `i_bust_02_13b.tmx` | 0x5d338c |
| `0x005ced70` | `i_bust_02_14a.tmx` | 0x5d3390 |
| `0x005ced90` | `i_bust_02_14b.tmx` | 0x5d3394 |
| `0x005cedb0` | `i_bust_02_15a.tmx` | 0x5d3398 |
| `0x005cedd0` | `i_bust_02_15b.tmx` | 0x5d339c |
| `0x005cedf0` | `i_bust_02_17a.tmx` | 0x5d33a0 |
| `0x005cee10` | `i_bust_02_17b.tmx` | 0x5d33a4 |
| `0x005cee30` | `i_bust_02_18a.tmx` | 0x5d33a8 |
| `0x005cee50` | `i_bust_02_18b.tmx` | 0x5d33ac |
| `0x005cee70` | `i_bust_02_21a.tmx` | 0x5d33b0 |
| `0x005cee90` | `i_bust_02_21b.tmx` | 0x5d33b4 |
| `0x005ceeb0` | `i_bust_02_22a.tmx` | 0x5d33b8 |
| `0x005ceed0` | `i_bust_02_22b.tmx` | 0x5d33bc |
| `0x005ceef0` | `i_bust_02_23a.tmx` | 0x5d33c0 |
| `0x005cef10` | `i_bust_02_23b.tmx` | 0x5d33c4 |
| `0x005cef30` | `i_bust_02_24a.tmx` | 0x5d33c8 |
| `0x005cef50` | `i_bust_02_24b.tmx` | 0x5d33cc |
| `0x005cef70` | `i_bust_02_25a.tmx` | 0x5d33d0 |
| `0x005cef90` | `i_bust_02_25b.tmx` | 0x5d33d4 |
| `0x005cefb0` | `i_bust_02_26a.tmx` | 0x5d33d8 |
| `0x005cefd0` | `i_bust_02_26b.tmx` | 0x5d33dc |
| `0x005ceff0` | `i_bust_02_27a.tmx` | 0x5d33e0 |
| `0x005cf010` | `i_bust_02_27b.tmx` | 0x5d33e4 |
| `0x005cf030` | `i_bust_02_31.tmx` | 0x5d33e8 |
| `0x005cf050` | `i_bust_02_32.tmx` | 0x5d33ec |
| `0x005cf070` | `i_bust_02_33.tmx` | 0x5d33f0 |
| `0x005cf090` | `i_bust_02_34.tmx` | 0x5d33f4 |
| `0x005cf0b0` | `i_bust_02_37.tmx` | 0x5d33f8 |
| `0x005cf0d0` | `i_bust_02_41.tmx` | 0x5d33fc |
| `0x005cf0f0` | `i_bust_02_42.tmx` | 0x5d3400 |
| `0x005cf110` | `i_bust_02_43.tmx` | 0x5d3404 |
| `0x005cf130` | `i_bust_02_44.tmx` | 0x5d3408 |
| `0x005cf150` | `i_bust_02_47.tmx` | 0x5d340c |
| `0x005cf170` | `i_bust_02_51.tmx` | 0x5d3410 |
| `0x005cf190` | `i_bust_02_52.tmx` | 0x5d3414 |
| `0x005cf1b0` | `i_bust_02_53.tmx` | 0x5d3418 |
| `0x005cf1d0` | `i_bust_02_54.tmx` | 0x5d341c |
| `0x005cf1f0` | `i_bust_02_57.tmx` | 0x5d3420 |
| `0x005cf210` | `i_bust_02_61.tmx` | 0x5d3424 |
| `0x005cf230` | `i_bust_02_62.tmx` | 0x5d3428 |
| `0x005cf250` | `i_bust_02_63.tmx` | 0x5d342c |
| `0x005cf270` | `i_bust_02_64.tmx` | 0x5d3430 |
| `0x005cf290` | `i_bust_02_67.tmx` | 0x5d3434 |
| `0x005cf2b0` | `i_bust_02_91.tmx` | 0x5d3438 |
| `0x005cf2d0` | `i_bust_02_92.tmx` | 0x5d343c |
| `0x005cf2f0` | `i_bust_02_93.tmx` | 0x5d3440 |
| `0x005cf310` | `i_bust_02_94.tmx` | 0x5d3444 |
| `0x005cf330` | `i_bust_02_97.tmx` | 0x5d3448 |
| `0x005cf350` | `i_bust_02_c1.tmx` | 0x5d344c |
| `0x005cf370` | `i_bust_02_c2.tmx` | 0x5d3450 |
| `0x005cf390` | `i_bust_02_c3.tmx` | 0x5d3454 |
| `0x005cf3b0` | `i_bust_02_c4.tmx` | 0x5d3458 |
| `0x005cf3d0` | `i_bust_02_c5.tmx` | 0x5d345c |
| `0x005cf3f0` | `i_bust_02_c7.tmx` | 0x5d3460 |
| `0x005cf410` | `i_bust_02_c8.tmx` | 0x5d3464 |
| `0x005cf430` | `i_bust_03_11a.tmx` | 0x5d3468 |
| `0x005cf450` | `i_bust_03_11b.tmx` | 0x5d346c |
| `0x005cf470` | `i_bust_03_12a.tmx` | 0x5d3470 |
| `0x005cf490` | `i_bust_03_12b.tmx` | 0x5d3474 |
| `0x005cf4b0` | `i_bust_03_13a.tmx` | 0x5d3478 |
| `0x005cf4d0` | `i_bust_03_13b.tmx` | 0x5d347c |
| `0x005cf4f0` | `i_bust_03_14a.tmx` | 0x5d3480 |
| `0x005cf510` | `i_bust_03_14b.tmx` | 0x5d3484 |
| `0x005cf530` | `i_bust_03_31.tmx` | 0x5d3488 |
| `0x005cf550` | `i_bust_03_32.tmx` | 0x5d348c |
| `0x005cf570` | `i_bust_03_33.tmx` | 0x5d3490 |
| `0x005cf590` | `i_bust_03_34.tmx` | 0x5d3494 |
| `0x005cf5b0` | `i_bust_03_41.tmx` | 0x5d3498 |
| `0x005cf5d0` | `i_bust_03_42.tmx` | 0x5d349c |
| `0x005cf5f0` | `i_bust_03_43.tmx` | 0x5d34a0 |
| `0x005cf610` | `i_bust_03_44.tmx` | 0x5d34a4 |
| `0x005cf630` | `i_bust_03_51.tmx` | 0x5d34a8 |
| `0x005cf650` | `i_bust_03_52.tmx` | 0x5d34ac |
| `0x005cf670` | `i_bust_03_53.tmx` | 0x5d34b0 |
| `0x005cf690` | `i_bust_03_54.tmx` | 0x5d34b4 |
| `0x005cf6b0` | `i_bust_03_61.tmx` | 0x5d34b8 |
| `0x005cf6d0` | `i_bust_03_62.tmx` | 0x5d34bc |
| `0x005cf6f0` | `i_bust_03_63.tmx` | 0x5d34c0 |
| `0x005cf710` | `i_bust_03_64.tmx` | 0x5d34c4 |
| `0x005cf730` | `i_bust_03_a1.tmx` | 0x5d34c8 |
| `0x005cf750` | `i_bust_03_a2.tmx` | 0x5d34cc |
| `0x005cf770` | `i_bust_03_a3.tmx` | 0x5d34d0 |
| `0x005cf790` | `i_bust_03_a4.tmx` | 0x5d34d4 |
| `0x005cf7b0` | `i_bust_03_a8.tmx` | 0x5d34d8 |
| `0x005cf7d0` | `i_bust_03_b1.tmx` | 0x5d34dc |
| `0x005cf7f0` | `i_bust_03_b2.tmx` | 0x5d34e0 |
| `0x005cf810` | `i_bust_03_b3.tmx` | 0x5d34e4 |
| `0x005cf830` | `i_bust_03_b4.tmx` | 0x5d34e8 |
| `0x005cf850` | `i_bust_03_c1.tmx` | 0x5d34ec |
| `0x005cf870` | `i_bust_03_c2.tmx` | 0x5d34f0 |
| `0x005cf890` | `i_bust_03_c3.tmx` | 0x5d34f4 |
| `0x005cf8b0` | `i_bust_03_c4.tmx` | 0x5d34f8 |
| `0x005cf8d0` | `i_bust_03_c8.tmx` | 0x5d34fc |
| `0x005cf8f0` | `i_bust_04_11a.tmx` | 0x5d3500 |
| `0x005cf910` | `i_bust_04_11b.tmx` | 0x5d3504 |
| `0x005cf930` | `i_bust_04_12a.tmx` | 0x5d3508 |
| `0x005cf950` | `i_bust_04_12b.tmx` | 0x5d350c |
| `0x005cf970` | `i_bust_04_13a.tmx` | 0x5d3510 |
| `0x005cf990` | `i_bust_04_13b.tmx` | 0x5d3514 |
| `0x005cf9b0` | `i_bust_04_14a.tmx` | 0x5d3518 |
| `0x005cf9d0` | `i_bust_04_14b.tmx` | 0x5d351c |
| `0x005cf9f0` | `i_bust_04_17a.tmx` | 0x5d3520 |
| `0x005cfa10` | `i_bust_04_17b.tmx` | 0x5d3524 |
| `0x005cfa30` | `i_bust_04_21a.tmx` | 0x5d3528 |
| `0x005cfa50` | `i_bust_04_21b.tmx` | 0x5d352c |
| `0x005cfa70` | `i_bust_04_22a.tmx` | 0x5d3530 |
| `0x005cfa90` | `i_bust_04_22b.tmx` | 0x5d3534 |
| `0x005cfab0` | `i_bust_04_23a.tmx` | 0x5d3538 |
| `0x005cfad0` | `i_bust_04_23b.tmx` | 0x5d353c |
| `0x005cfaf0` | `i_bust_04_24a.tmx` | 0x5d3540 |
| `0x005cfb10` | `i_bust_04_24b.tmx` | 0x5d3544 |
| `0x005cfb30` | `i_bust_04_27a.tmx` | 0x5d3548 |
| `0x005cfb50` | `i_bust_04_27b.tmx` | 0x5d354c |
| `0x005cfb70` | `i_bust_04_31.tmx` | 0x5d3550 |
| `0x005cfb90` | `i_bust_04_32.tmx` | 0x5d3554 |
| `0x005cfbb0` | `i_bust_04_33.tmx` | 0x5d3558 |
| `0x005cfbd0` | `i_bust_04_34.tmx` | 0x5d355c |
| `0x005cfbf0` | `i_bust_04_37.tmx` | 0x5d3560 |
| `0x005cfc10` | `i_bust_04_41.tmx` | 0x5d3564 |
| `0x005cfc30` | `i_bust_04_42.tmx` | 0x5d3568 |
| `0x005cfc50` | `i_bust_04_43.tmx` | 0x5d356c |
| `0x005cfc70` | `i_bust_04_44.tmx` | 0x5d3570 |
| `0x005cfc90` | `i_bust_04_47.tmx` | 0x5d3574 |
| `0x005cfcb0` | `i_bust_04_51.tmx` | 0x5d3578 |
| `0x005cfcd0` | `i_bust_04_52.tmx` | 0x5d357c |
| `0x005cfcf0` | `i_bust_04_53.tmx` | 0x5d3580 |
| `0x005cfd10` | `i_bust_04_54.tmx` | 0x5d3584 |
| `0x005cfd30` | `i_bust_04_57.tmx` | 0x5d3588 |
| `0x005cfd50` | `i_bust_04_61.tmx` | 0x5d358c |
| `0x005cfd70` | `i_bust_04_62.tmx` | 0x5d3590 |
| `0x005cfd90` | `i_bust_04_63.tmx` | 0x5d3594 |
| `0x005cfdb0` | `i_bust_04_64.tmx` | 0x5d3598 |
| `0x005cfdd0` | `i_bust_04_67.tmx` | 0x5d359c |
| `0x005cfdf0` | `i_bust_04_91.tmx` | 0x5d35a0 |
| `0x005cfe10` | `i_bust_04_92.tmx` | 0x5d35a4 |
| `0x005cfe30` | `i_bust_04_93.tmx` | 0x5d35a8 |
| `0x005cfe50` | `i_bust_04_94.tmx` | 0x5d35ac |
| `0x005cfe70` | `i_bust_04_97.tmx` | 0x5d35b0 |
| `0x005cfe90` | `i_bust_04_c1.tmx` | 0x5d35b4 |
| `0x005cfeb0` | `i_bust_04_c2.tmx` | 0x5d35b8 |
| `0x005cfed0` | `i_bust_04_c3.tmx` | 0x5d35bc |
| `0x005cfef0` | `i_bust_04_c4.tmx` | 0x5d35c0 |
| `0x005cff10` | `i_bust_04_c7.tmx` | 0x5d35c4 |
| `0x005cff30` | `i_bust_05_10a.tmx` | 0x5d35c8 |
| `0x005cff50` | `i_bust_05_10b.tmx` | 0x5d35cc |
| `0x005cff70` | `i_bust_05_11a.tmx` | 0x5d35d0 |
| `0x005cff90` | `i_bust_05_11b.tmx` | 0x5d35d4 |
| `0x005cffb0` | `i_bust_05_12a.tmx` | 0x5d35d8 |
| `0x005cffd0` | `i_bust_05_12b.tmx` | 0x5d35dc |
| `0x005cfff0` | `i_bust_05_13a.tmx` | 0x5d35e0 |
| `0x005d0010` | `i_bust_05_13b.tmx` | 0x5d35e4 |
| `0x005d0030` | `i_bust_05_14a.tmx` | 0x5d35e8 |
| `0x005d0050` | `i_bust_05_14b.tmx` | 0x5d35ec |
| `0x005d0070` | `i_bust_05_15a.tmx` | 0x5d35f0 |
| `0x005d0090` | `i_bust_05_15b.tmx` | 0x5d35f4 |
| `0x005d00b0` | `i_bust_05_16a.tmx` | 0x5d35f8 |
| `0x005d00d0` | `i_bust_05_16b.tmx` | 0x5d35fc |
| `0x005d00f0` | `i_bust_05_17a.tmx` | 0x5d3600 |
| `0x005d0110` | `i_bust_05_17b.tmx` | 0x5d3604 |
| `0x005d0130` | `i_bust_05_18a.tmx` | 0x5d3608 |
| `0x005d0150` | `i_bust_05_18b.tmx` | 0x5d360c |
| `0x005d0170` | `i_bust_05_19a.tmx` | 0x5d3610 |
| `0x005d0190` | `i_bust_05_19b.tmx` | 0x5d3614 |
| `0x005d01b0` | `i_bust_05_21a.tmx` | 0x5d3618 |
| `0x005d01d0` | `i_bust_05_21b.tmx` | 0x5d361c |
| `0x005d01f0` | `i_bust_05_22a.tmx` | 0x5d3620 |
| `0x005d0210` | `i_bust_05_22b.tmx` | 0x5d3624 |
| `0x005d0230` | `i_bust_05_23a.tmx` | 0x5d3628 |
| `0x005d0250` | `i_bust_05_23b.tmx` | 0x5d362c |
| `0x005d0270` | `i_bust_05_24a.tmx` | 0x5d3630 |
| `0x005d0290` | `i_bust_05_24b.tmx` | 0x5d3634 |
| `0x005d02b0` | `i_bust_05_25a.tmx` | 0x5d3638 |
| `0x005d02d0` | `i_bust_05_25b.tmx` | 0x5d363c |
| `0x005d02f0` | `i_bust_05_26a.tmx` | 0x5d3640 |
| `0x005d0310` | `i_bust_05_26b.tmx` | 0x5d3644 |
| `0x005d0330` | `i_bust_05_27a.tmx` | 0x5d3648 |
| `0x005d0350` | `i_bust_05_27b.tmx` | 0x5d364c |
| `0x005d0370` | `i_bust_05_31.tmx` | 0x5d3650 |
| `0x005d0390` | `i_bust_05_32.tmx` | 0x5d3654 |
| `0x005d03b0` | `i_bust_05_33.tmx` | 0x5d3658 |
| `0x005d03d0` | `i_bust_05_34.tmx` | 0x5d365c |
| `0x005d03f0` | `i_bust_05_35.tmx` | 0x5d3660 |
| `0x005d0410` | `i_bust_05_37.tmx` | 0x5d3664 |
| `0x005d0430` | `i_bust_05_61.tmx` | 0x5d3668 |
| `0x005d0450` | `i_bust_05_62.tmx` | 0x5d366c |
| `0x005d0470` | `i_bust_05_63.tmx` | 0x5d3670 |
| `0x005d0490` | `i_bust_05_64.tmx` | 0x5d3674 |
| `0x005d04b0` | `i_bust_05_65.tmx` | 0x5d3678 |
| `0x005d04d0` | `i_bust_05_67.tmx` | 0x5d367c |
| `0x005d04f0` | `i_bust_05_c0.tmx` | 0x5d3680 |
| `0x005d0510` | `i_bust_05_c1.tmx` | 0x5d3684 |
| `0x005d0530` | `i_bust_05_c2.tmx` | 0x5d3688 |
| `0x005d0550` | `i_bust_05_c3.tmx` | 0x5d368c |
| `0x005d0570` | `i_bust_05_c4.tmx` | 0x5d3690 |
| `0x005d0590` | `i_bust_05_c5.tmx` | 0x5d3694 |
| `0x005d05b0` | `i_bust_05_c6.tmx` | 0x5d3698 |
| `0x005d05d0` | `i_bust_05_c7.tmx` | 0x5d369c |
| `0x005d05f0` | `i_bust_05_c8.tmx` | 0x5d36a0 |
| `0x005d0610` | `i_bust_05_c9.tmx` | 0x5d36a4 |
| `0x005d0630` | `i_bust_06_11a.tmx` | 0x5d36a8 |
| `0x005d0650` | `i_bust_06_11b.tmx` | 0x5d36ac |
| `0x005d0670` | `i_bust_06_12a.tmx` | 0x5d36b0 |
| `0x005d0690` | `i_bust_06_12b.tmx` | 0x5d36b4 |
| `0x005d06b0` | `i_bust_06_13a.tmx` | 0x5d36b8 |
| `0x005d06d0` | `i_bust_06_13b.tmx` | 0x5d36bc |
| `0x005d06f0` | `i_bust_06_14a.tmx` | 0x5d36c0 |
| `0x005d0710` | `i_bust_06_14b.tmx` | 0x5d36c4 |
| `0x005d0730` | `i_bust_06_15a.tmx` | 0x5d36c8 |
| `0x005d0750` | `i_bust_06_15b.tmx` | 0x5d36cc |
| `0x005d0770` | `i_bust_06_17a.tmx` | 0x5d36d0 |
| `0x005d0790` | `i_bust_06_17b.tmx` | 0x5d36d4 |
| `0x005d07b0` | `i_bust_06_18a.tmx` | 0x5d36d8 |
| `0x005d07d0` | `i_bust_06_18b.tmx` | 0x5d36dc |
| `0x005d07f0` | `i_bust_06_21a.tmx` | 0x5d36e0 |
| `0x005d0810` | `i_bust_06_21b.tmx` | 0x5d36e4 |
| `0x005d0830` | `i_bust_06_22a.tmx` | 0x5d36e8 |
| `0x005d0850` | `i_bust_06_22b.tmx` | 0x5d36ec |
| `0x005d0870` | `i_bust_06_24a.tmx` | 0x5d36f0 |
| `0x005d0890` | `i_bust_06_24b.tmx` | 0x5d36f4 |
| `0x005d08b0` | `i_bust_06_25a.tmx` | 0x5d36f8 |
| `0x005d08d0` | `i_bust_06_25b.tmx` | 0x5d36fc |
| `0x005d08f0` | `i_bust_06_27a.tmx` | 0x5d3700 |
| `0x005d0910` | `i_bust_06_27b.tmx` | 0x5d3704 |
| `0x005d0930` | `i_bust_06_28a.tmx` | 0x5d3708 |
| `0x005d0950` | `i_bust_06_28b.tmx` | 0x5d370c |
| `0x005d0970` | `i_bust_06_31.tmx` | 0x5d3710 |
| `0x005d0990` | `i_bust_06_32.tmx` | 0x5d3714 |
| `0x005d09b0` | `i_bust_06_34.tmx` | 0x5d3718 |
| `0x005d09d0` | `i_bust_06_35.tmx` | 0x5d371c |
| `0x005d09f0` | `i_bust_06_37.tmx` | 0x5d3720 |
| `0x005d0a10` | `i_bust_06_41.tmx` | 0x5d3724 |
| `0x005d0a30` | `i_bust_06_42.tmx` | 0x5d3728 |
| `0x005d0a50` | `i_bust_06_44.tmx` | 0x5d372c |
| `0x005d0a70` | `i_bust_06_45.tmx` | 0x5d3730 |
| `0x005d0a90` | `i_bust_06_47.tmx` | 0x5d3734 |
| `0x005d0ab0` | `i_bust_06_51.tmx` | 0x5d3738 |
| `0x005d0ad0` | `i_bust_06_52.tmx` | 0x5d373c |
| `0x005d0af0` | `i_bust_06_54.tmx` | 0x5d3740 |
| `0x005d0b10` | `i_bust_06_55.tmx` | 0x5d3744 |
| `0x005d0b30` | `i_bust_06_57.tmx` | 0x5d3748 |
| `0x005d0b50` | `i_bust_06_61.tmx` | 0x5d374c |
| `0x005d0b70` | `i_bust_06_62.tmx` | 0x5d3750 |
| `0x005d0b90` | `i_bust_06_64.tmx` | 0x5d3754 |
| `0x005d0bb0` | `i_bust_06_65.tmx` | 0x5d3758 |
| `0x005d0bd0` | `i_bust_06_67.tmx` | 0x5d375c |
| `0x005d0bf0` | `i_bust_06_91.tmx` | 0x5d3760 |
| `0x005d0c10` | `i_bust_06_92.tmx` | 0x5d3764 |
| `0x005d0c30` | `i_bust_06_94.tmx` | 0x5d3768 |
| `0x005d0c50` | `i_bust_06_95.tmx` | 0x5d376c |
| `0x005d0c70` | `i_bust_06_97.tmx` | 0x5d3770 |
| `0x005d0c90` | `i_bust_06_c1.tmx` | 0x5d3774 |
| `0x005d0cb0` | `i_bust_06_c2.tmx` | 0x5d3778 |
| `0x005d0cd0` | `i_bust_06_c3.tmx` | 0x5d377c |
| `0x005d0cf0` | `i_bust_06_c4.tmx` | 0x5d3780 |
| `0x005d0d10` | `i_bust_06_c5.tmx` | 0x5d3784 |
| `0x005d0d30` | `i_bust_06_c7.tmx` | 0x5d3788 |
| `0x005d0d50` | `i_bust_06_c8.tmx` | 0x5d378c |
| `0x005d0d70` | `i_bust_06_d1.tmx` | 0x5d3790 |
| `0x005d0d90` | `i_bust_06_d2.tmx` | 0x5d3794 |
| `0x005d0db0` | `i_bust_06_d3.tmx` | 0x5d3798 |
| `0x005d0dd0` | `i_bust_06_d4.tmx` | 0x5d379c |
| `0x005d0df0` | `i_bust_06_d5.tmx` | 0x5d37a0 |
| `0x005d0e10` | `i_bust_07_10a.tmx` | 0x5d37a4 |
| `0x005d0e30` | `i_bust_07_10b.tmx` | 0x5d37a8 |
| `0x005d0e50` | `i_bust_07_11a.tmx` | 0x5d37ac |
| `0x005d0e70` | `i_bust_07_11b.tmx` | 0x5d37b0 |
| `0x005d0e90` | `i_bust_07_12a.tmx` | 0x5d37b4 |
| `0x005d0eb0` | `i_bust_07_12b.tmx` | 0x5d37b8 |
| `0x005d0ed0` | `i_bust_07_13a.tmx` | 0x5d37bc |
| `0x005d0ef0` | `i_bust_07_13b.tmx` | 0x5d37c0 |
| `0x005d0f10` | `i_bust_07_14a.tmx` | 0x5d37c4 |
| `0x005d0f30` | `i_bust_07_14b.tmx` | 0x5d37c8 |
| `0x005d0f50` | `i_bust_07_15a.tmx` | 0x5d37cc |
| `0x005d0f70` | `i_bust_07_15b.tmx` | 0x5d37d0 |
| `0x005d0f90` | `i_bust_07_18a.tmx` | 0x5d37d4 |
| `0x005d0fb0` | `i_bust_07_18b.tmx` | 0x5d37d8 |
| `0x005d0fd0` | `i_bust_07_21a.tmx` | 0x5d37dc |
| `0x005d0ff0` | `i_bust_07_21b.tmx` | 0x5d37e0 |
| `0x005d1010` | `i_bust_07_22a.tmx` | 0x5d37e4 |
| `0x005d1030` | `i_bust_07_22b.tmx` | 0x5d37e8 |
| `0x005d1050` | `i_bust_07_23a.tmx` | 0x5d37ec |
| `0x005d1070` | `i_bust_07_23b.tmx` | 0x5d37f0 |
| `0x005d1090` | `i_bust_07_24a.tmx` | 0x5d37f4 |
| `0x005d10b0` | `i_bust_07_24b.tmx` | 0x5d37f8 |
| `0x005d10d0` | `i_bust_07_28a.tmx` | 0x5d37fc |
| `0x005d10f0` | `i_bust_07_28b.tmx` | 0x5d3800 |
| `0x005d1110` | `i_bust_07_31.tmx` | 0x5d3804 |
| `0x005d1130` | `i_bust_07_32.tmx` | 0x5d3808 |
| `0x005d1150` | `i_bust_07_33.tmx` | 0x5d380c |
| `0x005d1170` | `i_bust_07_34.tmx` | 0x5d3810 |
| `0x005d1190` | `i_bust_07_61.tmx` | 0x5d3814 |
| `0x005d11b0` | `i_bust_07_62.tmx` | 0x5d3818 |
| `0x005d11d0` | `i_bust_07_63.tmx` | 0x5d381c |
| `0x005d11f0` | `i_bust_07_64.tmx` | 0x5d3820 |
| `0x005d1210` | `i_bust_07_69.tmx` | 0x5d3824 |
| `0x005d1230` | `i_bust_07_71.tmx` | 0x5d3828 |
| `0x005d1250` | `i_bust_07_72.tmx` | 0x5d382c |
| `0x005d1270` | `i_bust_07_73.tmx` | 0x5d3830 |
| `0x005d1290` | `i_bust_07_74.tmx` | 0x5d3834 |
| `0x005d12b0` | `i_bust_07_75.tmx` | 0x5d3838 |
| `0x005d12d0` | `i_bust_07_c0.tmx` | 0x5d383c |
| `0x005d12f0` | `i_bust_07_c1.tmx` | 0x5d3840 |
| `0x005d1310` | `i_bust_07_c2.tmx` | 0x5d3844 |
| `0x005d1330` | `i_bust_07_c3.tmx` | 0x5d3848 |
| `0x005d1350` | `i_bust_07_c4.tmx` | 0x5d384c |
| `0x005d1370` | `i_bust_07_c5.tmx` | 0x5d3850 |
| `0x005d1390` | `i_bust_07_c8.tmx` | 0x5d3854 |
| `0x005d13b0` | `i_bust_08_11a.tmx` | 0x5d3858 |
| `0x005d13d0` | `i_bust_08_11b.tmx` | 0x5d385c |
| `0x005d13f0` | `i_bust_08_12a.tmx` | 0x5d3860 |
| `0x005d1410` | `i_bust_08_12b.tmx` | 0x5d3864 |
| `0x005d1430` | `i_bust_08_13a.tmx` | 0x5d3868 |
| `0x005d1450` | `i_bust_08_13b.tmx` | 0x5d386c |
| `0x005d1470` | `i_bust_08_14a.tmx` | 0x5d3870 |
| `0x005d1490` | `i_bust_08_14b.tmx` | 0x5d3874 |
| `0x005d14b0` | `i_bust_08_21a.tmx` | 0x5d3878 |
| `0x005d14d0` | `i_bust_08_21b.tmx` | 0x5d387c |
| `0x005d14f0` | `i_bust_08_22a.tmx` | 0x5d3880 |
| `0x005d1510` | `i_bust_08_22b.tmx` | 0x5d3884 |
| `0x005d1530` | `i_bust_08_23a.tmx` | 0x5d3888 |
| `0x005d1550` | `i_bust_08_23b.tmx` | 0x5d388c |
| `0x005d1570` | `i_bust_08_24a.tmx` | 0x5d3890 |
| `0x005d1590` | `i_bust_08_24b.tmx` | 0x5d3894 |
| `0x005d15b0` | `i_bust_08_c1.tmx` | 0x5d3898 |
| `0x005d15d0` | `i_bust_08_c2.tmx` | 0x5d389c |
| `0x005d15f0` | `i_bust_08_c3.tmx` | 0x5d38a0 |
| `0x005d1610` | `i_bust_08_c4.tmx` | 0x5d38a4 |
| `0x005d1630` | `i_bust_09_11a.tmx` | 0x5d38a8 |
| `0x005d1650` | `i_bust_09_a1.tmx` | 0x5d38ac |
| `0x005d1670` | `i_bust_09_a3.tmx` | 0x5d38b0 |
| `0x005d1690` | `i_bust_09_a6.tmx` | 0x5d38b4 |
| `0x005d16b0` | `i_bust_09_c1.tmx` | 0x5d38b8 |
| `0x005d16d0` | `i_bust_09_c3.tmx` | 0x5d38bc |
| `0x005d16f0` | `i_bust_09_c6.tmx` | 0x5d38c0 |
| `0x005d1710` | `i_bust_10_a1.tmx` | 0x5d38c4 |
| `0x005d1730` | `i_bust_10_a2.tmx` | 0x5d38c8 |
| `0x005d1750` | `i_bust_10_a3.tmx` | 0x5d38cc |
| `0x005d1770` | `i_bust_10_a4.tmx` | 0x5d38d0 |
| `0x005d1790` | `i_bust_10_c1.tmx` | 0x5d38d4 |
| `0x005d17b0` | `i_bust_10_c2.tmx` | 0x5d38d8 |
| `0x005d17d0` | `i_bust_10_c3.tmx` | 0x5d38dc |
| `0x005d17f0` | `i_bust_10_c4.tmx` | 0x5d38e0 |
| `0x005d1810` | `i_bust_11_a1.tmx` | 0x5d38e4 |
| `0x005d1830` | `i_bust_11_a2.tmx` | 0x5d38e8 |
| `0x005d1850` | `i_bust_11_a3.tmx` | 0x5d38ec |
| `0x005d1870` | `i_bust_11_a4.tmx` | 0x5d38f0 |
| `0x005d1890` | `i_bust_11_a7.tmx` | 0x5d38f4 |
| `0x005d18b0` | `i_bust_11_a8.tmx` | 0x5d38f8 |
| `0x005d18d0` | `i_bust_12_a1.tmx` | 0x5d38fc |
| `0x005d18f0` | `i_bust_12_a2.tmx` | 0x5d3900 |
| `0x005d1910` | `i_bust_12_a4.tmx` | 0x5d3904 |
| `0x005d1930` | `i_bust_13_31.tmx` | 0x5d3908 |
| `0x005d1950` | `i_bust_13_32.tmx` | 0x5d390c |
| `0x005d1970` | `i_bust_13_33.tmx` | 0x5d3910 |
| `0x005d1990` | `i_bust_13_34.tmx` | 0x5d3914 |
| `0x005d19b0` | `i_bust_13_41.tmx` | 0x5d3918 |
| `0x005d19d0` | `i_bust_13_42.tmx` | 0x5d391c |
| `0x005d19f0` | `i_bust_13_43.tmx` | 0x5d3920 |
| `0x005d1a10` | `i_bust_13_44.tmx` | 0x5d3924 |
| `0x005d1a30` | `i_bust_13_a1.tmx` | 0x5d3928 |
| `0x005d1a50` | `i_bust_13_a2.tmx` | 0x5d392c |
| `0x005d1a70` | `i_bust_13_a4.tmx` | 0x5d3930 |
| `0x005d1a90` | `i_bust_13_a7.tmx` | 0x5d3934 |
| `0x005d1ab0` | `i_bust_14_a1.tmx` | 0x5d3938 |
| `0x005d1ad0` | `i_bust_15_a1.tmx` | 0x5d393c |
| `0x005d1af0` | `i_bust_16_a1.tmx` | 0x5d3940 |
| `0x005d1b10` | `i_bust_17_a1.tmx` | 0x5d3944 |
| `0x005d1b30` | `i_bust_17_a2.tmx` | 0x5d3948 |
| `0x005d1b50` | `i_bust_17_a3.tmx` | 0x5d394c |
| `0x005d1b70` | `i_bust_17_a5.tmx` | 0x5d3950 |
| `0x005d1b90` | `i_bust_18_a1.tmx` | 0x5d3954 |
| `0x005d1bb0` | `i_bust_18_a3.tmx` | 0x5d3958 |
| `0x005d1bd0` | `i_bust_18_a4.tmx` | 0x5d395c |
| `0x005d1bf0` | `i_bust_19_a1.tmx` | 0x5d3960 |
| `0x005d1c10` | `i_bust_19_a2.tmx` | 0x5d3964 |
| `0x005d1c30` | `i_bust_19_a3.tmx` | 0x5d3968 |
| `0x005d1c50` | `i_bust_19_a4.tmx` | 0x5d396c |
| `0x005d1c70` | `i_bust_19_a5.tmx` | 0x5d3970 |
| `0x005d1c90` | `i_bust_19_b1.tmx` | 0x5d3974 |
| `0x005d1cb0` | `i_bust_19_b2.tmx` | 0x5d3978 |
| `0x005d1cd0` | `i_bust_19_b3.tmx` | 0x5d397c |
| `0x005d1cf0` | `i_bust_19_b4.tmx` | 0x5d3980 |
| `0x005d1d10` | `i_bust_20_a1.tmx` | 0x5d3984 |
| `0x005d1d30` | `i_bust_20_a3.tmx` | 0x5d3988 |

### Version / SDK / compiler banners — 69 hits

| Address | String | Referenced from |
|---|---|---|
| `0x005ce4a8` | `\FIELD\SCRIPT\` | - |
| `0x005ce4f8` | `\SCRIPT\` | - |
| `0x005ce508` | `\SCRIPT\EVENT\` | - |
| `0x00678600` | `cdrom0:\LIB31\CRI_ADXI.IRX;1` | 0x1971f8 (kwlnInitPS2Systems) |
| `0x0069d470` | `>>>SCRIPT TRACE <0x%X>\n` | 0x35ec78 (scrTraceCode) |
| `0x006a3200` | `error!! comuTableBinFile Version Invalid  SupportVersion=%d (%d)` | 0x3bd2f0 (sub_3BD280) |
| `0x0077f2c0` | `PsIIlibdma  3100` | - |
| `0x00793ad8` | `\nADXRT  Ver.3020 Build:Feb 28 2005 19:25:21\n` | 0x547670 (ADXPS2_SetupDvdFs) |
| `0x007a8408` | `\nPL2ENC Ver.1.01 Build:Feb 28 2005 19:25:06\n` | 0x55eb74 (sub_55EB68), 0x55ec40 (sub_55EC38) |
| `0x007acc38` | `\nSJ/PS2EE Ver.6.31 Build:Feb 28 2005 19:25:09\n` | - |
| `0x007be630` | ` 1.2.0.0` | 0x516298 (_sceMcFatFormat) |
| `0x007c1188` | `\nSKG/PS2EE Ver.0.64 Build:Feb 28 2005 19:25:15\n` | - |
| `0x007c19b8` | `CRI-MW` | 0x537724 (sub_5376E0) |
| `0x007c1a38` | `(c)CRI` | 0x539ab0 (sub_539A38) |
| `0x007c1a88` | `\nADXF/PS2EE Ver.7.30 Build:Feb 28 2005 19:25:12\n` | 0x53b0a0 (sub_53B080) |
| `0x007c1ab9` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c21b0` | `(c)CRI` | 0x53e6f4 (sub_53E6D8) |
| `0x007c2268` | `\nADXT/PS2EE Ver.9.44 Build:Feb 28 2005 19:25:20\n` | 0x53e9c0 (sceLibgcc32GetErxEntries_3), 0x53eab0 (sub_53EA90) |
| `0x007c2299` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c24c0` | `\nADXPS2 Ver.2.60 Build:Feb 28 2005 19:25:21\n` | 0x788640 |
| `0x007c2648` | `CRI-MW` | 0x54366c (sub_543628) |
| `0x007c2650` | `\nADXENC/PS2EE Ver.1.10 Build:Feb 28 2005 19:25:16\n` | 0x790a24 |
| `0x007c2688` | `ADXENC.DLL Ver.1.10 Feb 28 2005` | 0x5436c8 (sceLibgcc32GetErxEntries_4) |
| `0x007c26b8` | `(c)CRI` | 0x790a30 |
| `0x007c3100` | `\nADXCS/PS2EE Ver.1.11 Build:Feb 28 2005 19:25:09\n` | 0x793f40 |
| `0x007c3138` | `CRI-MW` | 0x54e08c (sub_54E048) |
| `0x007c3170` | `\nAHX/PS2EE Ver.1.44 Build:Feb 28 2005 19:25:26\n` | 0x7986ec |
| `0x007c31a0` | `\nAIXP/PS2EE Ver.2.21 Build:Feb 28 2005 19:25:27\n` | 0x799960 |
| `0x007c3828` | `(c)CRI` | 0x554af4 (sub_554AE8) |
| `0x007c3908` | `\nCRI CFG/PS2EE Ver.1.002 Build:Feb 28 2005 19:25:35\n` | 0x5556b4 (sub_5556A0) |
| `0x007c393d` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c3958` | `\nCVFS/PS2EE Ver.2.39 Build:Feb 28 2005 19:25:29\n` | 0x7a08a0 |
| `0x007c4610` | `\nSRD/PS2EE Ver.2.22 Build:Feb 28 2005 19:25:34\n` | 0x7a08e8 |
| `0x007c49a0` | `\nDTR Ver.1.08 Build:Feb 28 2005 19:25:30\n` | 0x7a0930 |
| `0x007c4ad8` | `\nDTX Ver.1.10 Build:Feb 28 2005 19:25:30\n` | 0x7a1140 |
| `0x007c4be0` | `\nDVCI/PS2EE Ver.2.71 Build:Feb 28 2005 19:25:31\n` | 0x7a1d70 |
| `0x007c4ff0` | `\nHTCI/PS2EE Ver.2.69 Build:Feb 28 2005 19:25:31\n` | 0x7a2c08 |
| `0x007c5920` | `\nLSC/PS2EE Ver.2.22 Build:Feb 28 2005 19:25:33\n` | 0x7a3280 |
| `0x007c59a8` | `\nMFCI/PS2EE Ver.1.10 Build:Feb 28 2005 19:25:33\n` | 0x7a79a0 |
| `0x007c6268` | `\nPS2RNA Ver.1.32 Build:Feb 28 2005 19:25:33\n` | 0x7a8448 |
| `0x007c6c68` | `\nSJRMT Ver.1.03 Build:Feb 28 2005 19:25:10\n` | 0x7b1ab0 |
| `0x007c6c98` | `\nSJX Ver.1.09 Build:Feb 28 2005 19:25:11\n` | 0x7b1ab8 |
| `0x007c6d48` | `\nSVM/PS2EE Ver.1.58 Build:Feb 28 2005 19:25:09\n` | 0x7b2628 |
| `0x007c7200` | `\nROFS Ver.1.77 Build:Mar  2 2005 11:30:59\n` | 0x567818 (sceLibgcc32GetErxEntries_11) |
| `0x007c7708` | `CRI CD CRAFT` | 0x56b5d0 (sub_56B528), 0x56b5d4 (sub_56B528) |
| `0x007c7768` | `\nROCI Ver.1.15 Build:Mar  2 2005 11:31:01\n` | 0x56c880 (sub_56C878) |
| `0x007c77a0` | `CRI-MW` | 0x56d084 (sub_56D040) |
| `0x007c77a8` | `\nRSU Ver.1.10 Build:Mar  2 2005 11:31:01\n` | 0x56d6e0 (sceLibgcc32GetErxEntries_14) |
| `0x007c77d8` | `\nCRI CFT/PS2EE Ver.1.72 Build:Mar  1 2005 10:54:09\n` | 0x56de3c (sub_56DE28) |
| `0x007c780c` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c7918` | `\nCRI M2V/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:05\n` | 0x574e58 (sceLibgcc32GetErxEntries_16), 0x574f64 (sub_574F10) |
| `0x007c794d` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c79b8` | `\nCRI MPS/PS2EE Ver.1.924 Build:Mar  1 2005 10:53:57\n` | 0x577a30 (sceLibgcc32GetErxEntries_17), 0x577a54 (sub_577A38) |
| `0x007c79ed` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c7a20` | `\nCRI MPV/PS2EE Ver.1.958 Build:Mar  1 2005 10:54:00\n` | 0x57af00 (sceLibgcc32GetErxEntries_18), 0x57afb0 (sub_57AFA0) |
| `0x007c7a55` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c7ad0` | `CRI-MW` | 0x57bf4c (sub_57BF08) |
| `0x007c8490` | `\nMWSFD/PS2EE Ver.3.50 Build:Mar  1 2005 10:54:15\n` | 0x57f738 (__gthread_get_ee_key_value), 0x57f7b4 (sub_57F768) |
| `0x007c84c2` | `Append: GCC2096 SCE3020\n` | - |
| `0x007c85f0` | `E011081 sub_57FCB0: Not compatible SFD Version.` | 0x57fcf8 (sub_57FCB0) |
| `0x007c9670` | `CRITAGS` | 0x583634 (sub_5835F0) |
| `0x007c9678` | `CRITAGE` | 0x583638 (sub_5835F0) |
| `0x007c9dc8` | `(c)CRI` | 0x58666c (sub_586628) |
| `0x007c9f60` | `\nCRI SFD/PS2EE Ver.1.958 Build:Mar  1 2005 10:53:48\n` | 0x58bc18 (sceLibgcc32GetErxEntries_20), 0x58bc40 (sub_58BC30) |
| `0x007c9f95` | `Append: GCC2096 SCE3020\n` | - |
| `0x007ca550` | ` SFH Version 1.19SFH_VER_DATE` | - |
| `0x007ca590` | `\nCRI SFH/PS2EE Ver.1.19 Build:Mar  1 2005 10:54:03\n` | 0x59cfa8 (sceLibgcc32GetErxEntries_21) |
| `0x007ca968` | `\nCRI SFX/PS2EE Ver.2.29 Build:Mar  1 2005 10:54:12\n` | 0x59f9e8 (sceLibgcc32GetErxEntries_22) |
| `0x007cab70` | `\nCRI SUD/PS2EE Ver.0.05 Build:Mar  1 2005 10:54:11\n` | 0x5a1160 (sceLibgcc32GetErxEntries_23) |
<!-- GENERATED:END -->
