// Phase 5 slice boot: the boot and file-setup band 0x191D10-0x1997A0 -- the boot sequence's game side (main, the kwln
// root task and its draw passes, the new-game data), the boot data-file set-up tasks (H_FileSetup_*: the scenario
// choice, the item-table reads, the carry-over data), the GS upload packet builders, the task-tree debug dump. The
// party / area panels and the cut-ins of 0x18A3F0-0x18F0E0 are in boot_panels.h, the scene-draw and shadow tasks of
// 0x199C60-0x19FF10 in boot_scene.h.
//
// The bodies (game/src/boot/boot.cpp) are p3fes_handgen's: register for register and block for block as the
// recompiled bodies (frame, spills, $ra links, cycle charges, check points); their roles, the record offsets and the
// branch meanings are named on top (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). Names: the functions keep their
// symbols/functions.json names; a proposed name is given in brackets (ADR-0009: from the instructions, the callers,
// the strings and the ELF's tables; not imported). Every address is the ELF's (the same in every run).
//
// =====================================================================================================================
// THE BOOT SEQUENCE (for the engine and the server: what the game does from power-on to the first playable frame).
// Read from main / kwlnMain / kwlnInitMain / kwlnRootUpdateTask and the set-up tasks; docs/ANALYSIS/10_frame_loop_gs.md
// sections 1 and 3 has the hardware side. "(recompiled)" = not replaced here (hardware, IOP, ADX / ROFS in the body).
// =====================================================================================================================
//
// 1. start (crt0) -> main 0x193980: printf("jpx235\n") (the build tag) -> initAndLoop 0x1939B0 -> kwlnMain 0x1984C0
//    (recompiled: it reads T0_COUNT itself).
// 2. kwlnInitPS2Systems 0x197030 (recompiled): SIF / IOP heap / CD init, IOP reboot with cdrom0:\LIB31\IOPRP310.IMG,
//    the T0 time base, then 15 IOP modules from cdrom0:\LIB31\ in this order: SIO2MAN, SIO2D, PADMAN, DBCMAN, MC2_S1,
//    LIBSD, CRI_ADXI ("sdinit=0 spucore=1"), SDRDRV, MODHSYN, MODMSIN, MODSESQ, SKSOUND, SKHSYNTH (twice), SKSESQ
//    ("maxtrack=16"); H_Pad_Init, H_Memcard_Init.
// 3. kwlnInitRenderer 0x197350 (here): RenderWare -- the 8 MiB engine arena, the 33 PDS pipelines, the plugins,
//    video mode 82 (640 x 448 x 32 interlaced, 16-bit Z), the GS start, the vsync field gate, the world, three lights,
//    the 640 x 448 main camera (far 25600, near 20), Rt2d, the image formats.
// 4. kwlnInitMain 0x198010 (recompiled: ADX / ROFS / sceGsSyncVCallback in its body), in call order: H_Cdvd_InitCd,
//    H_Cdvd_InitRtFS, sub_177D40, sub_119A20, H_Sndcom_Init, sub_108740; ADX (DVD file system, threads, voices 5 / 5,
//    the error callback kwlnAdxErrorCallback); sceGsSyncVCallback(kwlnGsSyncVCallback); ROFS with the three CVM
//    volumes "CDV:data.cvm", "CDV:bgm.cvm", "CDV:btl.cvm" (each retried until it mounts) and their directories; the
//    second ADX error callback sub_197F80; kwlnSetFlags(0x80000000, 1); then the game modules: sub_27C8F0,
//    sub_31B470, sub_1042E0 (the debug printer, font/size12/f11_001.tmx), sub_105800, sub_196770 (the RW render
//    states saved), sub_4D8300(1), sub_4D8310(1), H_ResrcMan_Init, effMng_CreateEffectProgramTasks, btlTableInit (the
//    battle .TBLs: battle/SKILL.TBL, UNIT, MSG, PERSONA, ENCOUNT, EFFECT, MODEL, AICALC), sub_3BD130,
//    frFontSystemStart, sub_396BF0(0), sub_3BD280, sub_1D4560, sub_1DCA10, sub_1B7D00, K_Data_LoadFldMainScript (the
//    field's main script), sub_1B7C40(0), sub_1D7260, sub_1B7BB0, sub_1B7DC0, sub_1D4290, sub_1B8B40, sub_1B8C40,
//    sub_107020 (camp/fade_pak.pak), sprFontInit, sub_18E4A0 (camp/areapnl.pak, read synchronously), sub_18BC80
//    (camp/ptypnl.pak, read synchronously), effAfter_CreateAfterEffectRenderTask, counter 63 = 0, sub_17C280,
//    sub_16C1D0, sub_20C8D0, sub_4302B0, sub_267260.
// 5. The main loop (kwlnMain): forever { g_kwlnRootTask = kwlnRootCreateTask(); kwlnInitGameData (sub_195DE0: the
//    new-game state, below); RpRandomSeed / RpRandomSeedMT from T0_COUNT; while (kwlnTaskExists(root)) kwlnUpdate();
//    } -- the root dying is a soft reset. kwlnUpdate (recompiled) is one frame: H_Cdvd_Update (one file-read step),
//    the sound and pad updates, kwlnTaskMain (every task's update callback in priority order), the frame counters.
// 6. kwlnRootUpdateTask ("rootProc"), first frames: state 0 waits for sub_109DF0(0), then creates the frame's draw
//    tasks (below) as its children; state 1; state 2 creates the game root (gmRoot_CreateGameRootTask: the title /
//    the opening; recompiled) and state 3 watches it (a dead game root is made again). The debug path state 5 / 6
//    runs the scenario prompt "ChoiceDataFileSetup" (HONPEN / GOJITUDAN) and then kwlnInitGameData.
// 7. Starting a game (from the title, sub_265030): the scenario's file set-up task -- "HonpenFileSetup" (The Journey,
//    sub_1928D0, scenario word 0) or "GojitudanFileSetup" (The Answer, sub_192AA0, scenario 1) -- runs its three
//    loaders one after the other, each a task that is waited for until it ends:
//      The Journey: "HonpenItemTblDataRead" -> event/itemtbl.bin copied whole to 0x83BB30 (kItemTbl), then
//                   datItemTblSetSections (13 counted sections + 35 32-byte records: ui2.h);
//                   sub_27E270 "btlTableReload" (the battle tables of the scenario);
//                   sub_1B8030 the startup data dungeonAT.bin.
//      The Answer:  "GojitudanItemTblDataRead" -> event/AEGIS_itemtbl.bin to 0x83BB30 and event/AEGIS_seq.bin to
//                   0x83AB30 (4,096 bytes before it), then datItemTblSetSections;
//                   sub_27E2C0 "btlTableReload"; sub_1B80C0 the startup data dungeonFES.bin.
//    The title also starts "H_TstDvdChkDraw" (sub_1938E0; its update calls sceCd* itself and stays recompiled).
// 8. A new game's "played Persona 3 before?" step (the script commands sub_1933D0 / sub_193460): "HikitugiDataProc"
//    allocates the four carry-over buffers (80 / 13,312 / 704 / 44 bytes at 0x7CE050..0x7CE05C), opens the card
//    browser in carry-over mode (0x7CE00C = 1: the loader takes Persona 3's BASLUS-21569 save, savedata.h), and when a
//    save was loaded (0x7CDFFC) applies it (sub_192E70): the hero's three social stats, 39 flags of the list
//    0x5E4D80, the compendium's registered personas.
//
// The frame's task order (kwln priorities, ascending = earlier in the frame; the draw tasks of rootProc, the scene and
// the 3-D pipeline): shadow map camera 2068 / shadow node(camera all clear) 2069 / draw opac field 2070 / draw opac
// field object 2071 / draw character model 2084 / draw trans field obj preChar 2095 / 3D Draw Begin 2098 / 3D Draw End
// 4167 / draw persona model 4168 / draw trans field object 4172 / draw trans field 4173 / draw trans field(sort),
// draw trans NPC(sort) 4183 / 2D Draw Begin 4196 / 2D Draw Pre End 5231 / 2D Draw End 5241 / 3D on 2D Zclear 5243 /
// 3D on 2D Draw Begin 5245 / drawBustupProc 5276 / 3D on 2D Draw End 6320 / etc Draw Begin 6323 = the party panel /
// its member panels and the area panel 6324 / etc Draw 6335 = the mix-raid cut-in / its words 6336 / etc Draw End
// 7379 / <<< show raster >>> 7396 (the flip). The set-up tasks are created through kwlnTaskCreateWithAutoPriority with
// 0x106F (4207).
//
// The new-game state (kwlnInitGameData, sub_195DE0; read from its instructions, the function itself stays
// recompiled: test_title's windowed worlds run through it once it is emitted), for the server's character creation: ten party records reset;
// unit 1 is the hero (11,210 exp in The Answer); every unit gets its first persona from the u16 table 0x5E4F20 (The
// Journey: 1, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xCA, 0xCC, 0xCE, 0xCF for units 1..10) or 0x5E4F40 (The Answer: 0xC3,
// 0xC1, 0xC2, 0xC5, 0xC7, 0xC9, 0xCB, 0xCD, 0xD3, 0xCF), full HP / SP; all flags cleared; the date is day 2 (April 7)
// in The Journey, day 360 (March 31) in The Answer; the persona stock gets four personas (ids 32, 1001, 2001, 3128 /
// 203, 1073, 2073, 3132 through sub_182C50 + sub_1830C0); then the field, calendar and social systems reset.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace boot {
namespace task {  // the kwln task record (task.h)
inline constexpr s32 kWork = 60;  // +0x3C: the work block
}  // namespace task
namespace rw {  // the RenderWare memory slots (absolute: 0x960000 + slot)
inline constexpr s32 kFreeSlot = 380;    // 0x96017C: RwFree(ptr)
inline constexpr s32 kCallocSlot = 388;  // 0x960184: RwCalloc(n, size, hint 0x40000)
}  // namespace rw
namespace node {  // the H_Cdvd request node (hcdvd.h HCdvdRequest)
inline constexpr s32 kData = 272;  // +0x110: the file's bytes (64-byte aligned)
inline constexpr s32 kSize = 280;  // +0x118: the byte count the readers take
}  // namespace node
namespace fs {  // the file set-up tasks' 12-byte works
inline constexpr s32 kStep = 0;      // the step / phase
inline constexpr s32 kNode = 4;      // item-table read: the first file node; file setup: the step index
inline constexpr s32 kNode2 = 8;     // the second file node (The Answer) / the running sub-task / the choice's task
inline constexpr s32 kChoice = 4;    // ChoiceDataFileSetup: 0 The Journey, 1 The Answer
inline constexpr s32 kStepIndex = 4;
inline constexpr s32 kSubTask = 8;
inline constexpr s32 kResult = 4;    // HikitugiDataProc: 1 loaded, -1 none
inline constexpr s32 kCardTask = 8;  // HikitugiDataProc: the card browser
inline constexpr u32 kTaskPriority = 0x106F;  // 4207: every set-up task
}  // namespace fs
inline constexpr u32 kItemTbl = 0x83BB30u;        // event/itemtbl.bin / AEGIS_itemtbl.bin, copied whole
inline constexpr u32 kAegisSeq = 0x83AB30u;       // event/AEGIS_seq.bin (The Answer)
inline constexpr u32 kFileSetupStepsJourney = 0x5E4D00u;  // {sub_1924D0, sub_27E270, sub_1B8030, 0}
inline constexpr u32 kFileSetupStepsAnswer = 0x5E4D20u;   // {sub_192710, sub_27E2C0, sub_1B80C0, 0}
inline constexpr u32 kChoiceNames = 0x7CC0D8u;    // {"HONPEN" 0x7CC0D0, "GOJITUDAN" 0x5E4D48}
inline constexpr u32 kHikitugiFlagList = 0x5E4D80u;  // 0-terminated flag ids (39) the carry-over copies
inline constexpr u32 kJourneyPersonas = 0x5E4F20u;   // u16[10]: each unit's first persona, The Journey
inline constexpr u32 kAnswerPersonas = 0x5E4F40u;    // u16[10]: The Answer
inline constexpr u32 kNewCycleFlagList = 0x5E4F60u;  // 0-terminated flag ids kept by the new-cycle reset
// $gp words (gp = 0x7D2CF0)
inline constexpr u32 kHikitugiLoaded = 0x7CDFFCu;  // a carry-over save was loaded
inline constexpr u32 kHikitugiMode = 0x7CE00Cu;    // the card loader takes Persona 3's save
inline constexpr u32 kHikitugiBufs = 0x7CE050u;    // u32[4]: hero record 80, compendium 13,312, flags 704, block 24 44
inline constexpr u32 kHikitugiTask = 0x7CE060u;    // the running HikitugiDataProc
inline constexpr u32 kKeepFlagsWord = 0x7CDF78u;   // set: kwlnInitGameData keeps flags 387..393
inline constexpr u32 kWorlds = 0x7CE0A0u;          // u32[]: the RW worlds; [*0x7CE0CC] the current one
inline constexpr u32 kLights = 0x7CE0A8u;          // u32[3]: the three lights
inline constexpr u32 kMainCamera = 0x7CE0C0u;      // g_kwlnMainCamera
inline constexpr u32 kClearColor = 0x7CE128u;      // u8[4] RGBA (scaled)
inline constexpr u32 kBaseClearColor = 0x7CE124u;  // u8[4] RGBA (unscaled)
inline constexpr u32 kUploadPacket = 0x846F00u;    // the GS upload DMA packet buffer
}  // namespace boot

void sub_191D10(EEContext& ctx);  // 0x191D10 (n, size) -> block [H_Calloc]
void sub_191D70(EEContext& ctx);  // 0x191D70 (raster, data, qwc, rows) [kwlnRasterUpload]
void sub_191E60(EEContext& ctx);  // 0x191E60 (gsbase, packet, data, ...) [kwlnBuildUploadPacketFixed]
void sub_191EC0(EEContext& ctx);  // 0x191EC0 (gsbase, packet, data, bufw, rects, rect_bufw, height, slices) [kwlnBuildUploadPacket]
void sub_192160(EEContext& ctx);  // 0x192160 (dst, spr, addr, irq, id, pce, qwc) [kwlnSetDmaTag]
void sub_1921D0(EEContext& ctx);  // 0x1921D0 (dst, regs, nreg, flg, prim, pre, eop, nloop) [kwlnSetGifTag]
void sub_192230(EEContext& ctx);  // 0x192230 (dst, dbp, dbw, dpsm) [kwlnSetBitBltBuf]
void sub_1922A0(EEContext& ctx);  // 0x1922A0 (dst, dir, dsax, dsay) [kwlnSetTrxPos]
void sub_192310(EEContext& ctx);  // 0x192310 (dst, rrw, rrh) [kwlnSetTrxReg]
void sub_192370(EEContext& ctx);  // 0x192370 (dst, xdir) [kwlnSetTrxDir]
void H_FileSetup_UpdateHonpenItemTblDataReadTask(EEContext& ctx);  // 0x1923B0 (task) -> 0 / -1
void sub_192480(EEContext& ctx);  // 0x192480 (task)
void sub_1924D0(EEContext& ctx);  // 0x1924D0 (parent) -> task / 0 [H_FileSetup_CreateHonpenItemTblReadTask]
void sub_192570(EEContext& ctx);  // 0x192570 (task) -> 0 / -1 [H_FileSetup_UpdateGojitudanItemTblDataReadTask]
void sub_1926A0(EEContext& ctx);  // 0x1926A0 (task) [H_FileSetup_DestroyGojitudanItemTblReadTask]
void sub_192710(EEContext& ctx);  // 0x192710 (parent) -> task / 0 [H_FileSetup_CreateGojitudanItemTblReadTask]
void sub_1927B0(EEContext& ctx);  // 0x1927B0 (task) -> 0 / -1 [H_FileSetup_UpdateHonpenFileSetupTask]
void sub_1928A0(EEContext& ctx);  // 0x1928A0 (task) [H_FileSetup_DestroyFileSetupTask]
void sub_1928D0(EEContext& ctx);  // 0x1928D0 () -> task / 0 [H_FileSetup_CreateHonpenFileSetupTask]
void sub_192980(EEContext& ctx);  // 0x192980 (task) -> 0 / -1 [H_FileSetup_UpdateGojitudanFileSetupTask]
void sub_192A70(EEContext& ctx);  // 0x192A70 (task) [H_FileSetup_DestroyFileSetupTask2]
void sub_192AA0(EEContext& ctx);  // 0x192AA0 () -> task / 0 [H_FileSetup_CreateGojitudanFileSetupTask]
void H_FileSetup_UpdateChoiceDataFileSetupTask(EEContext& ctx);  // 0x192B50 (task) -> 0 / -1
void sub_192DB0(EEContext& ctx);  // 0x192DB0 (task) [H_FileSetup_DestroyChoiceDataFileSetupTask]
void sub_192DE0(EEContext& ctx);  // 0x192DE0 () -> task / 0 [H_FileSetup_CreateChoiceDataFileSetupTask]
void sub_192E70(EEContext& ctx);  // 0x192E70 () [H_FileSetup_ApplyHikitugiData]
void H_FileSetup_UpdateHikitugiDataProcTask(EEContext& ctx);  // 0x193020 (task) -> 0 / -1
void sub_193320(EEContext& ctx);  // 0x193320 (task) [H_FileSetup_DestroyHikitugiDataProcTask]
void sub_1933D0(EEContext& ctx);  // 0x1933D0 () -> 1 [H_FileSetup_StartHikitugiDataProc]
void sub_193460(EEContext& ctx);  // 0x193460 () -> 1 / 0 [H_FileSetup_WaitHikitugiDataProc]
void sub_1938B0(EEContext& ctx);  // 0x1938B0 (task) [H_FileSetup_DestroyTstDvdChkDrawTask]
void sub_1938E0(EEContext& ctx);  // 0x1938E0 (parent) -> task / 0 [H_FileSetup_CreateTstDvdChkDrawTask]
void main(EEContext& ctx);  // 0x193980 (argc, argv) -> never returns
void initAndLoop(EEContext& ctx);  // 0x1939B0 () -> never returns
void sub_194750(EEContext& ctx);  // 0x194750 (task, depth) [kwlnTaskPrintTree]
void sub_1948B0(EEContext& ctx);  // 0x1948B0 () [kwlnTaskPrintAll]
void kwlnSetupMainCameraViewport(EEContext& ctx);  // 0x195980 (camera, rect*, view_scale) [kwlnSetupMainCameraViewport]
void kwlnCreateMainCamera(EEContext& ctx);  // 0x195C80 (width, height, zbuffer) -> camera / 0 [kwlnCreateMainCamera]
void sub_196770(EEContext& ctx);  // 0x196770 () [kwlnSaveRenderStates]
void sub_1967D0(EEContext& ctx);  // 0x1967D0 () [kwlnInitGameDataNewCycle]
void kwlnInitRenderer(EEContext& ctx);  // 0x197350 () [kwlnInitRenderer]
void sub_197F80(EEContext& ctx);  // 0x197F80 (unused, text) [kwlnAdxErrorPrint]
void sub_198540(EEContext& ctx);  // 0x198540 (index) -> world [kwlnGetWorld]
void sub_198560(EEContext& ctx);  // 0x198560 () -> light [kwlnGetLight0]
void sub_198570(EEContext& ctx);  // 0x198570 () -> light [kwlnGetLight1]
void sub_198580(EEContext& ctx);  // 0x198580 () -> light [kwlnGetLight2]
void sub_198590(EEContext& ctx);  // 0x198590 () -> camera [kwlnGetMainCamera]
void sub_1985A0(EEContext& ctx);  // 0x1985A0 () -> rgba* [kwlnGetClearColor]
void sub_1985B0(EEContext& ctx);  // 0x1985B0 (r, g, b, a) [kwlnSetClearColor]
void sub_1985D0(EEContext& ctx);  // 0x1985D0 () -> rgba* [kwlnGetBaseClearColor]
void sub_1985E0(EEContext& ctx);  // 0x1985E0 (r, g, b, a) [kwlnSetBaseClearColor]
void kwlnRootUpdateTask(EEContext& ctx);  // 0x198650 (task) -> 0 / -1
void sub_1988F0(EEContext& ctx);  // 0x1988F0 (task) [kwlnRootDestroyTask]
void kwlnRootCreateTask(EEContext& ctx);  // 0x198940 () -> task / 0 [kwlnRootCreateTask]
void kwlnRootUpdate2DDrawPreEndTask(EEContext& ctx);  // 0x198B10 (task) -> 0
void sub_198B50(EEContext& ctx);  // 0x198B50 () -> task [kwlnRootCreate2DDrawBeginTask]
void sub_198B90(EEContext& ctx);  // 0x198B90 () -> task [kwlnRootCreate2DDrawPreEndTask]
void sub_198BD0(EEContext& ctx);  // 0x198BD0 () -> task [kwlnRootCreate2DDrawEndTask]
void sub_198DD0(EEContext& ctx);  // 0x198DD0 () -> task [kwlnRootCreate3DOn2DZClearTask]
void sub_198E10(EEContext& ctx);  // 0x198E10 () -> task [kwlnRootCreate3DOn2DDrawBeginTask]
void sub_198E50(EEContext& ctx);  // 0x198E50 () -> task [kwlnRootCreate3DOn2DDrawEndTask]
void kwlnRootUpdateEtcDrawTask(EEContext& ctx);  // 0x198F90 (task) -> 0
void sub_199080(EEContext& ctx);  // 0x199080 () -> task [kwlnRootCreateEtcDrawBeginTask]
void sub_1990C0(EEContext& ctx);  // 0x1990C0 () -> task [kwlnRootCreateEtcDrawTask]
void sub_199100(EEContext& ctx);  // 0x199100 () -> task [kwlnRootCreateEtcDrawEndTask]
void kwlnRootCreateShowRasterTask(EEContext& ctx);  // 0x199360 () -> task
void kwlnRootUpdateDrawBustupProcTask(EEContext& ctx);  // 0x1993A0 (task) -> 0
void sub_1993D0(EEContext& ctx);  // 0x1993D0 () -> task [kwlnRootCreateDrawBustupProcTask]
void sub_199410(EEContext& ctx);  // 0x199410 (task) [K_SPipe_DestroyTask]
void sub_199440(EEContext& ctx);  // 0x199440 (parent) -> task / 0 [K_SPipe_CreateTask]
void sub_1996C0(EEContext& ctx);  // 0x1996C0 (parent) -> task [K_SPipe_Create3DDrawBeginTask]
void sub_199700(EEContext& ctx);  // 0x199700 (parent) -> task [K_SPipe_Create3DDrawEndTask]
void sub_1997A0(EEContext& ctx);  // 0x1997A0 (parent) -> task [K_SPipe_CreateShadowNodeTask]

}  // namespace p3fes::game
