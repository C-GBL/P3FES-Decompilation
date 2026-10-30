// The script band, third pass (slice script3; docs/ANALYSIS/18_script_vm.md): the script task layer of scrScriptProcess.c
// (scrStartScript, the three scrCreateTask* entry points, scrReleaseScript, the dds3 process wrappers), CodeFunc_Comm /
// CodeFunc_Run, the scrCommonCommand.c / scrComuCommand.c COMM handlers left by the earlier passes, and the mt_evt*
// helpers of 0x3902B8-0x3A0000 the event player and the custom events call. Every body is p3fes_handgen's register-ABI
// body (arguments in $a0.., the result in $v0) with the roles, named offsets and structure added on top
// (game/src/script/script3.cpp; docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). Names are symbols/functions.json's;
// a bracketed name is a proposal (symbols/deltas/script3.sym). COMM ids are sScrCommandTable 0x7B92B0 indices, read
// from the ELF (the scrComuCommand.c handlers sit in the same table: entries 123 / 125 / 181..183 / 207 / 221..223 / 495).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/script_vm.h"

#include <cstddef>

namespace p3fes::game {

namespace script3 {

// --- ScrTask (script_vm.h, 252 bytes) as the s32 immediates of the bodies ---------------------------------------------
constexpr s32 kTaskPc = 0x18, kTaskSp = 0x1C, kTaskTags = 0x20, kTaskValues = 0x3C, kTaskImage = 0xAC,
              kTaskSections = 0xB0, kTaskProcLabels = 0xB4, kTaskJumpLabels = 0xB8, kTaskInsn = 0xBC,
              kTaskMessages = 0xC0, kTaskStrings = 0xC4, kTaskStartProc = 0xC8, kTaskMessageId = 0xCC,
              kTaskFrames = 0xD0, kTaskCmdTimer = 0xD4, kTaskOwnedImage = 0xD8, kTaskLocalInts = 0xDC,
              kTaskLocalFloats = 0xE0, kTaskProcess = 0xE4, kTaskPrev = 0xE8, kTaskNext = 0xEC, kTaskUserData = 0xF0;
constexpr bool offset_is(s32 k, std::size_t off) { return static_cast<std::size_t>(k) == off; }
static_assert(offset_is(kTaskPc, offsetof(ScrTask, pc)) && offset_is(kTaskSp, offsetof(ScrTask, sp)) && offset_is(kTaskTags, offsetof(ScrTask, tags)) &&
              offset_is(kTaskValues, offsetof(ScrTask, values)) && offset_is(kTaskImage, offsetof(ScrTask, image)) &&
              offset_is(kTaskSections, offsetof(ScrTask, sections)) && offset_is(kTaskProcLabels, offsetof(ScrTask, proc_labels)) &&
              offset_is(kTaskJumpLabels, offsetof(ScrTask, jump_labels)) && offset_is(kTaskInsn, offsetof(ScrTask, insn)) &&
              offset_is(kTaskMessages, offsetof(ScrTask, message_data)) && offset_is(kTaskStrings, offsetof(ScrTask, strings)) &&
              offset_is(kTaskStartProc, offsetof(ScrTask, start_proc)) && offset_is(kTaskMessageId, offsetof(ScrTask, message_id)) &&
              offset_is(kTaskFrames, offsetof(ScrTask, frames)) && offset_is(kTaskCmdTimer, offsetof(ScrTask, cmd_timer)) &&
              offset_is(kTaskOwnedImage, offsetof(ScrTask, owned_image)) && offset_is(kTaskLocalInts, offsetof(ScrTask, local_ints)) &&
              offset_is(kTaskLocalFloats, offsetof(ScrTask, local_floats)) && offset_is(kTaskProcess, offsetof(ScrTask, process)) &&
              offset_is(kTaskPrev, offsetof(ScrTask, prev)) && offset_is(kTaskNext, offsetof(ScrTask, next)) &&
              offset_is(kTaskUserData, offsetof(ScrTask, user_data)));
constexpr s32 kLabelInsn = 0x18;         // BfLabel: first instruction of a procedure / jump label (32-byte records)
constexpr s32 kSectionCount = 8;         // BF section descriptor (16 bytes): element count
constexpr s32 kBfLocalIntCount = 0x14;   // BF header: s16 local int count (scrStartScript asserts < 256)
constexpr s32 kBfLocalFloatCount = 0x16; // BF header: s16 local float count (asserts < 128)
constexpr s32 kInsnOperand = 2;          // instruction word { u16 opcode; s16 operand }
constexpr s32 kKwlnPriority = 0x20;      // KwlnTask (task.h): priority -- SCR_RUN adds its arg1 to the caller's

// gp-relative globals ($gp = 0x7D2CF0)
constexpr s32 kGpScrTaskCount = -18292;     // 0x7CE57C g_scrTaskCount: running scripts
constexpr s32 kGpScrTaskListHead = -18288;  // 0x7CE580 g_scrTaskListHead
constexpr s32 kGpScrTaskListTail = -18284;  // 0x7CE584 g_scrTaskListTail
constexpr s32 kGpScrCurrentTask = -18248;   // 0x7CE5A8 g_scrCurrentTask (set by CodeFunc_Comm for the command)
constexpr s32 kGpComuState125 = -18244;     // 0x7CE5AC COMM 125's event-step state
constexpr s32 kGpComuState222 = -18240;     // 0x7CE5B0 COMM 222's event-step state
constexpr s32 kGpComuTodayId = -18236;      // 0x7CE5B4 COMM 223: today's invitation id
constexpr s32 kGpComuTodayRecord = -18232;  // 0x7CE5B8 COMM 223: its record (sub_3BEB10)
constexpr s32 kGpEvtModelWord = -18136;     // 0x7CE618 read by sub_39E6F0

// --- the event player's work (the parent task of "event Draw 3D/2D" and "FrameVar"; type_5 of types.json, >= 0x984) --
constexpr s32 kEvtFlags = 4;              // flag word: 0x80 cut started, 0x1000 fade set, 0x10000 camera reset; bit 3 kept
constexpr s32 kEvtData = 8;               // the event data (PM): +52 model rows (32 bytes) / +56 count, +96 cut table
constexpr s32 kEvtCamBase = 16, kEvtCamCur = 24, kEvtCamKey = 28;  // sub_393F30: cur = base, key = -1
constexpr s32 kEvtFlashOn = 1648, kEvtFlashA = 1652, kEvtFlashB = 1656;           // sub_395550
constexpr s32 kEvtRedraw = 1660;          // sub_395910 sets, the 3D draw calls sub_386E50 and clears
constexpr s32 kEvtRectOn = 1664, kEvtRectX = 1668, kEvtRectY = 1672, kEvtRectZ = 1676, kEvtRectScale = 1680;  // sub_396270
constexpr s32 kEvtQuadOn = 1684, kEvtQuad = 1696, kEvtQuadScale = 1760;           // sub_3957D0 / sub_395810
constexpr s32 kEvtWord1764On = 1764, kEvtWord1768 = 1768;                          // sub_396250
constexpr s32 kEvtLetterboxOn = 1772, kEvtLetterboxA = 1776, kEvtLetterboxB = 1788; // sub_395930
constexpr s32 kEvtAttachCount = 1932, kEvtAttachData = 1936, kEvtAttachId = 1976, kEvtAttachSize = 1996;  // 10 attach models
constexpr s32 kEvtPackData = 2040, kEvtPackId = 2060, kEvtPackSize = 2072;          // 5 pack models (table at 2036)
constexpr s32 kEvtCamBlock = 2272, kEvtCamCount = 2276, kEvtCam2328 = 2328;         // camera key block (sub_393F30)
constexpr s32 kEvtChildTask = 2356;       // destroyed by sub_393E30 unless flag 8
constexpr s32 kEvtCutBlock = 2400, kEvtCutMode = 2404, kEvtCut = 2416, kEvtCutWord = 2424;
constexpr s32 kEvtDataCuts = 96;          // event data: cut table
constexpr s32 kCutCount = 2, kCutRows = 4;  // cut table: u16 count, rows (140 bytes each)
constexpr s32 kCutRowBytes = 140;

// --- the effect registry (mt_evtEffect.c, 400 bytes) ------------------------------------------------------------------
constexpr s32 kRegState = 0, kRegCount = 4, kRegCursor = 8, kRegPending = 12;  // state 1 loading, 2 loaded
constexpr s32 kRegEntKind = 16, kRegEntName = 20, kRegEntData = 52, kRegEntHandle = 56;  // entry i at +44 * i
constexpr s32 kRegEntryBytes = 44;
constexpr s32 kRegResIds = 368;           // u16[16] scene resource ids

// --- "koma_Manager" panels (12 bytes each, 3) -------------------------------------------------------------------------
constexpr s32 kKomaState = 0, kKomaClose = 4, kKomaTask = 8;  // state 1 opening, 2 open, 3 closed

// --- the "evtPMFileReader" work (64 bytes) ----------------------------------------------------------------------------
constexpr s32 kPmrState = 0;              // 0..7, 7 = loaded
constexpr s32 kPmrDefaults = 4;           // 1: PM2 / PM3 are the built-in default blocks (no load)
constexpr s32 kPmrPakMode = 8;            // != 0: one PAK request instead of three files
constexpr s32 kPmrMajor = 12, kPmrMinor = 16, kPmrArg2 = 20;  // event e<major>_<minor>
constexpr s32 kPmrEventId = 24;           // u16 sub_3BD9A0(major, minor)
constexpr s32 kPmrCdvd1 = 28, kPmrCdvd2 = 32, kPmrCdvd3 = 36;          // H_Cdvd handles
constexpr s32 kPmrDefault1 = 40, kPmrDefault2 = 44, kPmrDefault3 = 48; // default blocks (event heap tags 4..6)
constexpr s32 kPmrPm1 = 52, kPmrPm2 = 56, kPmrPm3 = 60;                // the loaded PM1 / PM2 / PM3

// --- the message slot (mt_evtMessage.c, 32 bytes) ---------------------------------------------------------------------
constexpr s32 kMsgActive = 0;     // 1 while a handle is open
constexpr s32 kMsgKind = 4;       // 0 dialogue (state flag 0x200000), 1 centred y 2208, 2 centred y 1520
constexpr s32 kMsgHandle = 8;     // itfMesMng handle
constexpr s32 kMsgPhase = 12;     // MT_Msg_Update phase 0..5
constexpr s32 kMsgMessage = 16, kMsgSelection = 20, kMsgSelArg = 24, kMsgResult = 28;

}  // namespace script3

// --- scrScriptProcess.c / scrCommonCommand.c / scrTraceCode.c: the script task layer, COMM / RUN, the dds3 wrappers ------
void sub_35AC50(EEContext& ctx);  // 0x35AC50 [frFontFatal]
void nullsub_21(EEContext& ctx);  // 0x35AC80 an empty callback (the font layer's sub_3AFA40 calls it)
void sub_35AD80(EEContext& ctx);  // 0x35AD80 [dds3InitProcess]
void sub_35ADB0(EEContext& ctx);  // 0x35ADB0 [dds3KillProcess]
void nullsub_22(EEContext& ctx);  // 0x35AE50 an empty event-viewer callback (sub_36F000 calls it on teardown).
void nullsub_23(EEContext& ctx);  // 0x35AE60 an empty event-viewer callback (sub_36F000 calls it on teardown).
void nullsub_24(EEContext& ctx);  // 0x35AE70 an empty event-viewer callback (sub_36F000 calls it on teardown).
void nullsub_25(EEContext& ctx);  // 0x35AE80 an empty event-viewer callback (sub_36F000 calls it on teardown).
void sub_35AE90(EEContext& ctx);  // 0x35AE90 returns 0 (a stub query of the font layer, called by sub_3B0F50).
void sub_35AEA0(EEContext& ctx);  // 0x35AEA0 returns 0 (a stub query of the font layer, called by sub_3B18C0).
void scrCommand_PUT(EEContext& ctx);  // 0x35B090 COMM 16 (0x010, argc 1) PUT
void sub_35B0D0(EEContext& ctx);  // 0x35B0D0 [scrCommand_PUTSTR]
void scrCommand_SCR_RUN(EEContext& ctx);  // 0x35B280 COMM 23 (0x017, argc 2) SCR_RUN
void scrCommand_SCR_KILL(EEContext& ctx);  // 0x35B390 COMM 24 (0x018, argc 1) SCR_KILL
void scrStartScript(EEContext& ctx);  // 0x35B570 builds a script task record (ScrTask, 252 bytes, H_Malloc) from a BF i
void scrCreateTaskFromHeader(EEContext& ctx);  // 0x35BB40 scrCreateTaskFromHeader(priority, image, start_proc)
void scrCreateTaskFromScriptMemory(EEContext& ctx);  // 0x35BC00 scrCreateTaskFromScriptMemory(priority, bf, size, start_proc)
void scrCreateTask(EEContext& ctx);  // 0x35BD50 scrCreateTask(priority, image, sections, procs, jumps, insns, messages
void scrReleaseScript(EEContext& ctx);  // 0x35BE30 frees a script task record
void sub_35BFB0(EEContext& ctx);  // 0x35BFB0 [scrKillAllScripts]
void scrDestroyTask(EEContext& ctx);  // 0x35C200 the dds3 destructor of a script process (registered by the scrCreateTa
void CodeFunc_Comm(EEContext& ctx);  // 0x35CF20 opcode 8 COMM
void CodeFunc_Run(EEContext& ctx);  // 0x35D2C0 opcode 12 RUN

// --- scrComuCommand.c below 0x360020 (sScrCommandTable entries 123..495) -------------------------------------------------
void sub_35F170(EEContext& ctx);  // 0x35F170 COMM 123 (0x07B, argc 1)
void sub_35F4A0(EEContext& ctx);  // 0x35F4A0 [comuCmdRunEventStep]
void sub_35F5B0(EEContext& ctx);  // 0x35F5B0 COMM 125 (0x07D, argc 1) [comu event]
void sub_35F680(EEContext& ctx);  // 0x35F680 COMM 221 (0x0DD, argc 1)
void sub_35F730(EEContext& ctx);  // 0x35F730 COMM 222 (0x0DE, argc 0)
void sub_35F7A0(EEContext& ctx);  // 0x35F7A0 COMM 181 (0x0B5, argc 0)
void sub_35F880(EEContext& ctx);  // 0x35F880 COMM 207 (0x0CF, argc 2) [add social stat]
void sub_35FD00(EEContext& ctx);  // 0x35FD00 COMM 495 (0x1EF, argc 1)
void sub_35FDB0(EEContext& ctx);  // 0x35FDB0 COMM 223 (0x0DF, argc 0) [today's invitation into the message]

// --- mt_evtPolygonMovie.c: the event player cut / camera helpers, the PM file names and default blocks -------------------
void sub_393E30(EEContext& ctx);  // 0x393E30 [mtEvt_StartCut]
void sub_393F30(EEContext& ctx);  // 0x393F30 [mtEvt_ResetCamera]
void sub_394040(EEContext& ctx);  // 0x394040 [mtEvt_Lerp]
void sub_394070(EEContext& ctx);  // 0x394070 [mtEvt_LerpKey]
void sub_394270(EEContext& ctx);  // 0x394270 [mtEvtPM_AllocWork]
void sub_394C30(EEContext& ctx);  // 0x394C30 [mtEvtPM_FreeWork]
void sub_394CE0(EEContext& ctx);  // 0x394CE0 [mtEvtPM_DefaultPm1]
void sub_394D60(EEContext& ctx);  // 0x394D60 [mtEvtPM_DefaultPm2]
void sub_394DF0(EEContext& ctx);  // 0x394DF0 [mtEvtPM_DefaultPm3]
void sub_394E70(EEContext& ctx);  // 0x394E70 [mtEvtPM_HostPaths]
void sub_395000(EEContext& ctx);  // 0x395000 [mtEvtPM_DiscPaths]

// --- MT_Misc / event sound / the event draw and "FrameVar" tasks ---------------------------------------------------------
void sub_395200(EEContext& ctx);  // 0x395200 [MT_Misc_Rand]
void sub_395230(EEContext& ctx);  // 0x395230 [MT_Misc_Chance]
void sub_395270(EEContext& ctx);  // 0x395270 [MT_Misc_StopSe]
void nullsub_27(EEContext& ctx);  // 0x3952A0 an empty event command stub (sub_363030's table).
void sub_3952B0(EEContext& ctx);  // 0x3952B0 returns 0 (an event command stub of sub_363030).
void sub_3952C0(EEContext& ctx);  // 0x3952C0 returns 0 (an event command stub of sub_38D720).
void sub_3952D0(EEContext& ctx);  // 0x3952D0 [MT_Misc_PlayEventVoice]
void sub_395350(EEContext& ctx);  // 0x395350 [MT_Misc_StreamCtl]
void sub_3953B0(EEContext& ctx);  // 0x3953B0 the update of "FrameVar"
void sub_3953E0(EEContext& ctx);  // 0x3953E0 [mtEvt_CreateFrameVarTask]
void nullsub_28(EEContext& ctx);  // 0x395420 an empty event-viewer callback (sub_36F000).
void sub_395430(EEContext& ctx);  // 0x395430 [mtEvt_SetFade]
void sub_3954E0(EEContext& ctx);  // 0x3954E0 [mtEvt_FadeOut]
void sub_395550(EEContext& ctx);  // 0x395550 [mtEvt_SetFlash]
void sub_3957D0(EEContext& ctx);  // 0x3957D0 [mtEvt_SetFilterQuad]
void sub_395810(EEContext& ctx);  // 0x395810 [mtEvt_DrawFilterQuad]
void sub_395910(EEContext& ctx);  // 0x395910 [mtEvt_RequestRedraw]
void sub_395930(EEContext& ctx);  // 0x395930 [mtEvt_SetLetterbox]
void sub_396250(EEContext& ctx);  // 0x396250 [mtEvt_SetWord1768]
void sub_396270(EEContext& ctx);  // 0x396270 [mtEvt_SetScreenRect]
// sub_3962C0 (the update of "event Draw 3D") lives in render_game2
void sub_3963C0(EEContext& ctx);  // 0x3963C0 the update of "event Draw 2D"
void sub_396410(EEContext& ctx);  // 0x396410 [mtEvt_CreateDrawTasks]

// --- mt_evtEffect.c: the effect registry (400 bytes, kReg* below) --------------------------------------------------------
void sub_396480(EEContext& ctx);  // 0x396480 [MT_RegEff_AddMemory]
void sub_3964C0(EEContext& ctx);  // 0x3964C0 [MT_RegEff_Create]
void sub_396530(EEContext& ctx);  // 0x396530 [MT_RegEff_Destroy]
void sub_3965D0(EEContext& ctx);  // 0x3965D0 [MT_RegEff_StartLoad]
void sub_3965F0(EEContext& ctx);  // 0x3965F0 [MT_RegEff_Load]
void sub_396760(EEContext& ctx);  // 0x396760 [MT_RegEff_CreateResource]
void sub_3968A0(EEContext& ctx);  // 0x3968A0 [MT_RegEff_GetResource]
void sub_396910(EEContext& ctx);  // 0x396910 [MT_RegEff_Delete]
void sub_3969B0(EEContext& ctx);  // 0x3969B0 [MT_RegEff_DeleteAll]

// --- mt_evtCutin.c: "koma_Manager", 3 cut-in panels of 12 bytes (kKoma* below) -------------------------------------------
void sub_396A70(EEContext& ctx);  // 0x396A70 the update of "koma_Manager"
void sub_396BA0(EEContext& ctx);  // 0x396BA0 the destroy callback of "koma_Manager"
void sub_396BF0(EEContext& ctx);  // 0x396BF0 [koma_CreateManagerTask]
void sub_396C70(EEContext& ctx);  // 0x396C70 [koma_Open]
void sub_396E30(EEContext& ctx);  // 0x396E30 [koma_RequestClose]
void sub_396ED0(EEContext& ctx);  // 0x396ED0 [koma_GetState]
void sub_396F50(EEContext& ctx);  // 0x396F50 [koma_Close]
void sub_397030(EEContext& ctx);  // 0x397030 [koma_Destroy]
void sub_3970D0(EEContext& ctx);  // 0x3970D0 [koma_DestroyAll]
void sub_3971A0(EEContext& ctx);  // 0x3971A0 COMM 182 (0x0B6, argc 7) [CUTIN]
void sub_3973E0(EEContext& ctx);  // 0x3973E0 COMM 183 (0x0B7, argc 1) [CUTIN_END]

// --- the event data's cut table (event player +8 -> +96: u16 count at +2, 140-byte rows at +4) ---------------------------
void sub_397450(EEContext& ctx);  // 0x397450 [mtEvt_DeleteHaitiNpcs]
void sub_397500(EEContext& ctx);  // 0x397500 [mtEvt_GetCut]
void sub_397510(EEContext& ctx);  // 0x397510 [mtEvt_SetCut]
void sub_397520(EEContext& ctx);  // 0x397520 [mtEvt_GetCutCount]
void sub_397580(EEContext& ctx);  // 0x397580 [mtEvt_GetCutWord]
void sub_397630(EEContext& ctx);  // 0x397630 [mtEvt_GetCutByte22]
void sub_3976F0(EEContext& ctx);  // 0x3976F0 [mtEvt_GetCutPair]
void sub_3977C0(EEContext& ctx);  // 0x3977C0 [mtEvt_GetCutCamera]
void sub_397870(EEContext& ctx);  // 0x397870 [mtEvt_GetCutQuad]

// --- mt_evtPMFileReader.c: the "evtPMFileReader" process (64-byte work, kPmr* below) -------------------------------------
void sub_397950(EEContext& ctx);  // 0x397950 the update of "evtPMFileReader"
void sub_397D60(EEContext& ctx);  // 0x397D60 the destroy callback of "evtPMFileReader"
void sub_397EC0(EEContext& ctx);  // 0x397EC0 [mtEvtPMR_Create]
void sub_397F80(EEContext& ctx);  // 0x397F80 [mtEvtPMR_CreateFromViewer]
void sub_398060(EEContext& ctx);  // 0x398060 [mtEvtPMR_IsDone]
void sub_3980E0(EEContext& ctx);  // 0x3980E0 [mtEvtPMR_GetWork]
void sub_398140(EEContext& ctx);  // 0x398140 [mtEvtPMR_FindEntry0]
void sub_3982D0(EEContext& ctx);  // 0x3982D0 [mtEvtPMR_HasEvent]

// --- mt_evtCustomEvent.c helpers -----------------------------------------------------------------------------------------
void sub_398390(EEContext& ctx);  // 0x398390 [mtEvt_TimerSet]
void sub_3983A0(EEContext& ctx);  // 0x3983A0 [mtEvt_TimerTick]
void sub_3983E0(EEContext& ctx);  // 0x3983E0 [mtEvtCustom_MessageIndex]

// --- mt_evtModel: attach / pack models of the event player ---------------------------------------------------------------
void sub_39E6F0(EEContext& ctx);  // 0x39E6F0 returns the word 0x7CE618 (gp-18136), an event-model counter.
void sub_39E700(EEContext& ctx);  // 0x39E700 [mtEvtModel_RegistAttach]
void sub_39E7C0(EEContext& ctx);  // 0x39E7C0 [mtEvtModel_DetachAll]
void sub_39E820(EEContext& ctx);  // 0x39E820 [mtEvtModel_Detach3]
void sub_39E880(EEContext& ctx);  // 0x39E880 [mtEvtModel_Attach]
void sub_39EA20(EEContext& ctx);  // 0x39EA20 [mtEvtModel_DetachSlot]
void sub_39EAA0(EEContext& ctx);  // 0x39EAA0 [mtEvtModel_RegistPack]
void sub_39EB90(EEContext& ctx);  // 0x39EB90 [mtEvtModel_DeletePacks]
void sub_39EC10(EEContext& ctx);  // 0x39EC10 [mtEvtModel_GetPack]
void sub_39EC60(EEContext& ctx);  // 0x39EC60 [mtEvtModel_PackResId]

// --- mt_evtMessage.c: the 32-byte message slot (kMsg* below) -------------------------------------------------------------
void sub_39EC70(EEContext& ctx);  // 0x39EC70 [MT_Msg_Open]
void sub_39ED20(EEContext& ctx);  // 0x39ED20 [MT_Msg_OpenKind1]
void sub_39EDD0(EEContext& ctx);  // 0x39EDD0 [MT_Msg_OpenKind2]
void sub_39EE80(EEContext& ctx);  // 0x39EE80 [MT_Msg_Close]
void sub_39EEE0(EEContext& ctx);  // 0x39EEE0 [MT_Msg_IsOpen]
void sub_39EEF0(EEContext& ctx);  // 0x39EEF0 [MT_Msg_SetNumber]
void sub_39EF30(EEContext& ctx);  // 0x39EF30 [MT_Msg_SetString]
void sub_39EF70(EEContext& ctx);  // 0x39EF70 [MT_Msg_SetLinkName]
void sub_39EFD0(EEContext& ctx);  // 0x39EFD0 [MT_Msg_SetArcanaName]
void sub_39F050(EEContext& ctx);  // 0x39F050 [MT_Msg_SetPersonaLevel]
void sub_39F0C0(EEContext& ctx);  // 0x39F0C0 [MT_Msg_SetPartnerName]
void sub_39F120(EEContext& ctx);  // 0x39F120 [MT_Msg_SetString13BCB0]
void sub_39F190(EEContext& ctx);  // 0x39F190 [MT_Msg_SetArcanaText]
void sub_39F210(EEContext& ctx);  // 0x39F210 [MT_Msg_Request]
void sub_39F2A0(EEContext& ctx);  // 0x39F2A0 [MT_Msg_End]
void sub_39F350(EEContext& ctx);  // 0x39F350 [MT_Msg_EndIfActive]
void sub_39F410(EEContext& ctx);  // 0x39F410 [MT_Msg_Update]
void sub_39F6E0(EEContext& ctx);  // 0x39F6E0 [MT_Msg_IsIdle]
void sub_39F710(EEContext& ctx);  // 0x39F710 [MT_Msg_GetMessageCount]
void sub_39F750(EEContext& ctx);  // 0x39F750 [MT_Msg_GetMessageType]
void sub_39F7C0(EEContext& ctx);  // 0x39F7C0 [MT_Msg_SetChoiceMask]
void sub_39F800(EEContext& ctx);  // 0x39F800 [MT_Msg_GetResult]
}  // namespace p3fes::game
