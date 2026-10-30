// Phase 5 slice social_map: two small subsystems of docs/ANALYSIS/27_unmapped_bands.md section 8 that no wave-10 slice
// took --
//
//   (1) the social-link code 0x3C03F0-0x3C442C (comuTimerSequence.c, comuSasoi.c, comuEventExec.c, comuData.c; the nm*
//       helpers from 0x3C4430 on are the nm_message slice's), 54 functions, and
//   (2) the area map ("y_lmap proc", sequence 4 of the sequence table) in the Y band 0x421770-0x4281E4 (the Tartarus
//       mini-map / stratum / enemy code from 0x4281F0 on is the tartarus slice's; 23 of the band's COMM handlers were
//       replaced by the comm slices), 65 functions.
// Left out: Y_Misc_GetT0Count 0x4241D0 (reads the EE timer register T0_COUNT 0x10000000: hardware in its own body).
//
// No replay route reaches either subsystem. The social-link tables are loaded at boot and sit in every replay snapshot,
// so tests/game/test_social_map.cpp pairs the comu functions on the real tables of a snapshot for every day of the
// year, besides the random worlds.
//
// What the social-link code works on (read from the instructions; names in brackets are proposals, not imported):
//
//   [comu data]  the record at 0x95B070 (sub_3BD870 returns it), filled at boot; the tables used here (row counts in
//                every snapshot checked: dorm_replay_4900, b_5800, battle_ref_6150, v_m1):
//                 +0x628 / +0x62C  availability rows, 5 bytes {link, month, day, end month, end day}: end month 0xFF =
//                                  a rule handed to sub_3BF200 (month 0xFF too: every month) -- 819 rows
//                 +0x650 / +0x654  no-call days, 3 bytes {month, day, link or 0xFF for all} -- 57 rows
//                 +0x660 / +0x664  timer events by date, 12 bytes {month, day, -, -, +4 kind (0: after school, else
//                                  evening), +8 u16 event, +10 / +11 its two bytes} -- 69 rows
//                 +0x674 / +0x678  invitation rows, 12 bytes {link, lowest rank, highest rank, ...} -- 105 rows
//                the record at 0x95B6A8 (sub_3BDD50): +0 / +4 phone-call rows (24 bytes, link first; 104 rows), +8 / +12
//                days without calls (2 bytes {month, day}; 48 rows).
//   [comu timer process] "comuTimerProcess" (comu_CreateComuTimerProcessTask, from the calendar code; update
//                sub_3BF610) keeps the current state function in its work block. Each state is called with the task in
//                $a0 and returns 0 (stay), -1 (finished) or the next state function. The state's work words: +0 phase,
//                +4 frame counter, +8 frame limit (the phase-1 wait), +12..+20 cleared with them; sub_3C15D0 keeps a
//                56-byte copy of the current invitation at +0x20. A phase that starts an event fills a 28-byte sequence
//                parameter on its frame and calls adminiChangeSeq(sequence, param, 28, 0) -- sequence 3: an event by
//                number (+12 event, +16 / +20 its two words), sequence 2: the halfword form (+0 / +2 / +4 / +8) -- and
//                the next phase waits until the sequence manager is idle (current id 0 and no next id: sub_27C2B0 /
//                sub_27C330).
//   [invitations] comuSasoi.c: today's invitation list 0x95B7E0 (count, then 56-byte entries filled by sub_3BE8E0;
//                0x698 bytes) and the phone-call record 0x95B790 (+0 valid, +4 month, +8 day, +12 the call's data from
//                sub_3BE2A0).
//   [event exec] comuEventExec.c: sub_3C33C0 steps a social-link event (record: +0 link, +1 partner link, +2 event type
//                0..7, +8 step result, +12 phase 0..3, +0x24 / +0x2A / +0x30 condition words for sub_172750, +0x20
//                6-byte result rows).
//   [comu text]  comuData.c: the ELF's static tables -- 0x6A3590 the 42 place names ("Club", "Rooftop", ...), 0x6A36A0
//                the 30 partner names ("SEES", "Kenji", ...), 0x6A38E0 the 30 social-link titles ("SEES", "Classmate",
//                ...), 0x6A38E8 a table of 24-byte rows, 0x6A3A50 the weekday names, 0x6A3B40 six gift descriptions,
//                0x6A3BE0 "next Sunday" .. "next Saturday", "tomorrow", 0x6A3CA0 the 22 ultimate personas ("Susano-o"
//                ...), 0x6A3D70 the invitation kind per link (4-byte rows {s8 kind, -, u16 message}: kind 2 for links 1,
//                4, 6..14, 17..19, 23, 27, else 0), 0x6A3340 one signed byte per link (30 for all 30).
//
// What the area-map code works on: the "y_lmap proc" work (+0 phase word, +60 the current area byte, +64 the menu task,
// +92 the script task, +96 / +112 the two file nodes, +144 the model task), the shared record at gp-0x4648 (11 bytes:
// +6 the move target, +7 a menu-select flag, +8 the move-done flag, +9 / +10 a preselection), the menu record (+0 state
// byte, +142 entry count, +143.. entry ids, +149 a flag, +150 the selected entry, +204.. sprite handles, +396 / +400 the
// entry positions), the box-fill and tmx display records (task +60: +272.. four corner colours, +296 / +300 size, +304
// alpha (float), +308 / +312 position, +318 / +336 / +396 flag bytes, +321 the shape), the curve helpers (sinf / cosf
// easing between two ends, pi at gp-0x7DB8), the area models 0x95BEC0[6] and the path table of sub_425D50 (6 x 6
// nested jump tables 0x7BC280..0x7BC320).
//
// Every body keeps the original's registers, frame, spills, links, cycle charges and check points (p3fes_handgen,
// game/include/p3fes/game/hg_cpu.h); the names below are offsets for the bodies and the tests.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// --- the comu timer states' work block (task work: kwlnTaskGetWorkData) ---------------------------------------------
constexpr s32 kComuWorkPhase = 0;      // the state's phase
constexpr s32 kComuWorkWait = 4;       // frames waited in phase 1
constexpr s32 kComuWorkWaitLimit = 8;  // frames to wait (2)
constexpr s32 kComuWorkWord3 = 12;     // cleared with the others when the state hands over
constexpr s32 kComuWorkWord4 = 16;
constexpr s32 kComuWorkWord5 = 20;

// --- the event-exec record of sub_3C33C0 / sub_3C3E80 ------------------------------------------------------------------
constexpr s32 kExecLink = 0;     // u8: the social link
constexpr s32 kExecPartner = 1;  // u8: the partner's link (made active on some results)
constexpr s32 kExecType = 2;     // u8: the event type 0..7 (the three jump tables)
constexpr s32 kExecResult = 8;   // u8: the step result (1..4)
constexpr s32 kExecPhase = 12;   // word: 0 start, 1 decide, 2 checks, 3 finish

// --- a timer-event row (kComuEventRows, 12 bytes) ---------------------------------------------------------------------
constexpr s32 kEventMonth = 0;  // u8
constexpr s32 kEventDay = 1;    // u8
constexpr s32 kEventKind = 4;   // word: 0 after school (time slot 2), else evening (4)
constexpr s32 kEventId = 8;     // u16, then the bytes +10 / +11

// --- the comu data record (sub_3BD870) and its tables -----------------------------------------------------------------
constexpr u32 kComuData = 0x95B070u;
constexpr s32 kComuAvailRows = 0x628;   // 5-byte availability rows {link, month, day, end month, end day}
constexpr s32 kComuAvailCount = 0x62C;
constexpr s32 kComuBusyRows = 0x650;    // 3-byte no-call rows {month, day, link or 0xFF}
constexpr s32 kComuBusyCount = 0x654;
constexpr s32 kComuEventRows = 0x660;   // 12-byte timer-event rows {month, day, -, -, kind, u16 event, b, c}
constexpr s32 kComuEventCount = 0x664;
constexpr s32 kComuSasoiRows = 0x674;   // 12-byte invitation rows {link, lowest rank, highest rank, ...}
constexpr s32 kComuSasoiCount = 0x678;
constexpr u32 kComuData2 = 0x95B6A8u;   // (sub_3BDD50) +0 / +4 phone-call rows (24 bytes), +8 / +12 no-call days (2 bytes)

// --- the comu globals -----------------------------------------------------------------------------------------------
constexpr u32 kComuEventWord = 0x7CE670u;   // gp-0x4680
constexpr u32 kComuPending = 0x95B750u;     // sub_3C1430
constexpr u32 kComuCall = 0x95B790u;        // +0 valid, +4 month, +8 day, +12 data
constexpr u32 kComuSasoiList = 0x95B7E0u;   // count, then 56-byte entries (0x698 bytes)
constexpr u32 kComuSasoiOwner = 0x95BE74u;
constexpr u32 kComuNumLinks = 30;           // the loops over links run 0..29

// --- comuData.c's static tables (the ELF's .data) -------------------------------------------------------------------
constexpr u32 kComuPlaceNames = 0x6A3590u;      // 42 pointers
constexpr u32 kComuPartnerNames = 0x6A36A0u;    // 30 pointers
constexpr u32 kComuLinkTitles = 0x6A38E0u;      // 30 pointers
constexpr u32 kComuGrid = 0x6A38E8u;            // 24-byte rows
constexpr u32 kComuWeekdayNames = 0x6A3A50u;    // 7 pointers
constexpr u32 kComuGiftTexts = 0x6A3B40u;       // 6 pointers
constexpr u32 kComuWhenTexts = 0x6A3BE0u;       // "next Sunday" .. "next Saturday", "tomorrow"
constexpr u32 kComuUltimatePersonas = 0x6A3CA0u;  // 22 pointers
constexpr u32 kComuSasoiKinds = 0x6A3D70u;      // 4-byte rows {s8 kind, -, u16 message}
constexpr u32 kComuDayLimits = 0x6A3340u;       // one s8 per link

// --- the area map ---------------------------------------------------------------------------------------------------
constexpr u32 kLmapShared = 0x7CE6A8u;      // gp-0x4648: the 11-byte shared record
constexpr u32 kLmapStratumTask = 0x7CE6ACu; // gp-0x4644
constexpr u32 kLmapModelArea = 0x7CE6B4u;   // gp-0x463C: the model's current area (s8)
constexpr u32 kLmapMoveSlot = 0x7CE6B8u;    // gp-0x4638: the lmap_model_move task (sub_426090)
constexpr u32 kLmapModels = 0x95BEC0u;      // 6 area models
constexpr u32 kLmapPi = 0x7CAF38u;          // gp-0x7DB8: 3.14159274f
constexpr s32 kTaskWork = 0x3C;           // KwlnTask::work (task.h): the task record of the area-map tasks
constexpr s32 kBoxColors = 272;             // box-fill / tmx records: four RGBA corner colours
constexpr s32 kBoxSize = 296;               // +296 / +300
constexpr s32 kBoxAlpha = 304;              // float
constexpr s32 kBoxPos = 308;                // +308 / +312 (floats)

// --- the bodies (register ABI: arguments in $a0.., $f12.., the result in $v0 / $f0; src/ui/social_map.cpp) ----------
// The bracketed role is a proposal (not imported); the functions keep their symbols/functions.json names.

// [comu timer process] the states: task in $a0; 0 stay, -1 finished, else the next state function
void sub_3C03F0(EEContext& ctx);  // 0x3C03F0 [comuTimerStateEvent8C]
void sub_3C0570(EEContext& ctx);  // 0x3C0570 [comuTimerStateApril]
void sub_3C07C0(EEContext& ctx);  // 0x3C07C0 [comuTimerStateDaily]
void sub_3C09A0(EEContext& ctx);  // 0x3C09A0 [comuTimerStateEvent321]
void sub_3C0B30(EEContext& ctx);  // 0x3C0B30 [comuTimerStateCheckFlag]
void sub_3C0BD0(EEContext& ctx);  // 0x3C0BD0 [comuTimerStateKind1]
void sub_3C0C30(EEContext& ctx);  // 0x3C0C30 [comuTimerStateSeq2_7_1]
void sub_3C0D20(EEContext& ctx);  // 0x3C0D20 [comuTimerStateKind4]
void sub_3C0DB0(EEContext& ctx);  // 0x3C0DB0 [comuFindDateEvent]
void sub_3C0F20(EEContext& ctx);  // 0x3C0F20 [comuTimerStateDateEvent]
void sub_3C1150(EEContext& ctx);  // 0x3C1150 [comuTimerStateSasoi]
void sub_3C1300(EEContext& ctx);  // 0x3C1300 [comuTimerStateKind3]
void sub_3C1340(EEContext& ctx);  // 0x3C1340 [comuTimerStateSeq2_6_3]
void sub_3C1430(EEContext& ctx);  // 0x3C1430 [comuGetPendingRecord]
void sub_3C1440(EEContext& ctx);  // 0x3C1440 [comuTimerStateNight]
void sub_3C15D0(EEContext& ctx);  // 0x3C15D0 [comuTimerStateInvite]
void sub_3C1810(EEContext& ctx);  // 0x3C1810 [comuTimerStateKind5]
void sub_3C18C0(EEContext& ctx);  // 0x3C18C0 [comuTimerStateKind6]

// [comu timer process] creation / RevMailSeq
void sub_3C1A70(EEContext& ctx);  // 0x3C1A70 [comuTimerDestroy]
void comu_CreateComuTimerProcessTask(EEContext& ctx);  // 0x3C1AB0 
void comu_UpdateRevMailSeqTask(EEContext& ctx);  // 0x3C1D20 
void sub_3C22F0(EEContext& ctx);  // 0x3C22F0 [comuRevMailDestroy]
void comu_CreateRevMailSeqTask(EEContext& ctx);  // 0x3C2350 

// [invitations] comuSasoi.c
void sub_3C23F0(EEContext& ctx);  // 0x3C23F0 [comuIsUnavailable]
void sub_3C2570(EEContext& ctx);  // 0x3C2570 [comuSasoiTier]
void sub_3C2630(EEContext& ctx);  // 0x3C2630 [comuBuildSasoiList]
void sub_3C2770(EEContext& ctx);  // 0x3C2770 [comuGetSasoiList]
void sub_3C2780(EEContext& ctx);  // 0x3C2780 [comuFindSasoiRow]
void sub_3C28A0(EEContext& ctx);  // 0x3C28A0 [comuCollectSasoi]
void sub_3C2AB0(EEContext& ctx);  // 0x3C2AB0 [comuIsNoCallDay]
void sub_3C2B40(EEContext& ctx);  // 0x3C2B40 [comuNextCallDay]
void sub_3C2C50(EEContext& ctx);  // 0x3C2C50 [comuCanCall]
void sub_3C2DF0(EEContext& ctx);  // 0x3C2DF0 [comuIsBusyToday]
void sub_3C2EE0(EEContext& ctx);  // 0x3C2EE0 [comuMakeCall]
void sub_3C3050(EEContext& ctx);  // 0x3C3050 [comuMakeCallNow]
void sub_3C30B0(EEContext& ctx);  // 0x3C30B0 [comuAcceptCall]
void sub_3C3120(EEContext& ctx);  // 0x3C3120 [comuDeclineCall]
void sub_3C3190(EEContext& ctx);  // 0x3C3190 [comuPickRandomCall]
void sub_3C3390(EEContext& ctx);  // 0x3C3390 [comuGetCall]

// [event exec] comuEventExec.c
void sub_3C33C0(EEContext& ctx);  // 0x3C33C0 [comuEventExecStep]
void sub_3C3E80(EEContext& ctx);  // 0x3C3E80 [comuEventExecUpdate]

// [comu text] comuData.c
void sub_3C3F40(EEContext& ctx);  // 0x3C3F40 [comuGetPlaceName]
void sub_3C3F80(EEContext& ctx);  // 0x3C3F80 [comuGetLinkTitle]
void sub_3C3FE0(EEContext& ctx);  // 0x3C3FE0 [comuGetPartnerName]
void sub_3C4040(EEContext& ctx);  // 0x3C4040 [comuGetGridText]
void sub_3C40F0(EEContext& ctx);  // 0x3C40F0 [comuGetSasoiKind]
void sub_3C4110(EEContext& ctx);  // 0x3C4110 [comuGetSasoiMessage]
void sub_3C4130(EEContext& ctx);  // 0x3C4130 [comuGetWeekdayName]
void sub_3C4210(EEContext& ctx);  // 0x3C4210 [comuGetGiftText]
void sub_3C4270(EEContext& ctx);  // 0x3C4270 [comuGetWhenText]
void sub_3C4390(EEContext& ctx);  // 0x3C4390 [comuGetUltimatePersonaName]
void sub_3C43F0(EEContext& ctx);  // 0x3C43F0 [comuGetGpWord]
void sub_3C4400(EEContext& ctx);  // 0x3C4400 Returns 0 
void sub_3C4410(EEContext& ctx);  // 0x3C4410 Returns 0 
void sub_3C4420(EEContext& ctx);  // 0x3C4420 Returns 0 

// [area map] the y_lmap task, its records and helpers
void Y_LMap_UpdateLmapTask(EEContext& ctx);  // 0x421770 
void sub_421D70(EEContext& ctx);  // 0x421D70 [lmapDestroy]
void Y_LMap_CreateLmapTask(EEContext& ctx);  // 0x421DE0 
void sub_421EF0(EEContext& ctx);  // 0x421EF0 [lmapIsPhase15]
void sub_421F10(EEContext& ctx);  // 0x421F10 [lmapGetRecord112]
void sub_421F20(EEContext& ctx);  // 0x421F20 [lmapAllocShared]
void sub_421FB0(EEContext& ctx);  // 0x421FB0 [lmapFreeShared]
void sub_421FE0(EEContext& ctx);  // 0x421FE0 [lmapEase]
void sub_4221A0(EEContext& ctx);  // 0x4221A0 [lmapEaseF]
void sub_4222D0(EEContext& ctx);  // 0x4222D0 [lmapEase2]
void sub_4229A0(EEContext& ctx);  // 0x4229A0 [boxfillDestroy]
void Y_LMap_CreateBoxfillTasks(EEContext& ctx);  // 0x4229D0 
void sub_422C10(EEContext& ctx);  // 0x422C10 [boxfillSetAlpha]
void sub_422C30(EEContext& ctx);  // 0x422C30 [boxfillSetRect]
void sub_422C90(EEContext& ctx);  // 0x422C90 [boxfillSetColor]
void sub_422CD0(EEContext& ctx);  // 0x422CD0 [boxfillSetFlag]
void Y_LMap_UpdateLMapMenuTask(EEContext& ctx);  // 0x422CE0 
void sub_423790(EEContext& ctx);  // 0x423790 [lmapMenuDestroy]
void Y_LMap_CreateLMapMenuTask(EEContext& ctx);  // 0x4238B0 
void sub_423B50(EEContext& ctx);  // 0x423B50 [lmapMenuSelected]
void sub_423B70(EEContext& ctx);  // 0x423B70 [lmapMenuIsDone]
void sub_423BA0(EEContext& ctx);  // 0x423BA0 [lmapMenuClose]
void sub_423BF0(EEContext& ctx);  // 0x423BF0 [lmapMenuIsOpen]
void sub_423C10(EEContext& ctx);  // 0x423C10 [lmapMenuSelect]
void sub_423CD0(EEContext& ctx);  // 0x423CD0 [lmapMenuLayout]
void sub_423FC0(EEContext& ctx);  // 0x423FC0 [lmapMenuSetFlag149]
void sub_423FE0(EEContext& ctx);  // 0x423FE0 [lmapAlign]

// [area map] sequence 4 rows and the COMM handlers of the band
void sub_4241E0(EEContext& ctx);  // 0x4241E0 [seq4Create]
void sub_424230(EEContext& ctx);  // 0x424230 [seq4Destroy]
void sub_4242B0(EEContext& ctx);  // 0x4242B0 [seq4Poll]
void sub_424310(EEContext& ctx);  // 0x424310 COMM
void sub_424370(EEContext& ctx);  // 0x424370 COMM
void sub_424B60(EEContext& ctx);  // 0x424B60 COMM
void sub_424F80(EEContext& ctx);  // 0x424F80 COMM
void sub_425020(EEContext& ctx);  // 0x425020 COMM
void sub_425070(EEContext& ctx);  // 0x425070 COMM
void sub_4252D0(EEContext& ctx);  // 0x4252D0 COMM
void sub_425320(EEContext& ctx);  // 0x425320 COMM
void sub_425480(EEContext& ctx);  // 0x425480 COMM TIME_LIMIT

// [area map] the model, the model move, the tmx display
void sub_425690(EEContext& ctx);  // 0x425690 [lmapModelUpdate]
void sub_425BA0(EEContext& ctx);  // 0x425BA0 [lmapModelDestroy]
void Y_LMap_CreateLmapModelTask(EEContext& ctx);  // 0x425C60 
void sub_425D10(EEContext& ctx);  // 0x425D10 [lmapModelSetTarget]
void sub_425D30(EEContext& ctx);  // 0x425D30 [lmapModelSetPos]
void sub_425D50(EEContext& ctx);  // 0x425D50 [lmapPathStep]
void sub_426040(EEContext& ctx);  // 0x426040 [lmapModelSetByte3]
void sub_426050(EEContext& ctx);  // 0x426050 [lmapModelSetState3]
void sub_426070(EEContext& ctx);  // 0x426070 [lmapModelIsMoving]
void sub_426090(EEContext& ctx);  // 0x426090 [lmapGetModelMoveSlot]
void sub_4260A0(EEContext& ctx);  // 0x4260A0 [lmapModelMoveUpdate]
void sub_4264A0(EEContext& ctx);  // 0x4264A0 [lmapModelMoveDestroy]
void Y_LMap_CreateLmapModelMoveTask(EEContext& ctx);  // 0x4264D0 
void sub_426590(EEContext& ctx);  // 0x426590 [tmxDispUpdate]
void sub_427640(EEContext& ctx);  // 0x427640 [tmxDispDestroy]
void Y_LMap_CreateTmxDispTask(EEContext& ctx);  // 0x427670 
void sub_427830(EEContext& ctx);  // 0x427830 [tmxDispCreateEx3]
void sub_427A10(EEContext& ctx);  // 0x427A10 [tmxDispCreateEx]
void sub_427BF0(EEContext& ctx);  // 0x427BF0 [tmxDispCreateEx2]
void sub_427DB0(EEContext& ctx);  // 0x427DB0 [tmxDispSetPos]
void sub_427DE0(EEContext& ctx);  // 0x427DE0 [tmxDispSetColor]
void sub_427E20(EEContext& ctx);  // 0x427E20 [tmxDispSetSize]
void sub_427E50(EEContext& ctx);  // 0x427E50 [tmxDispSetHidden]
void sub_427E60(EEContext& ctx);  // 0x427E60 [tmxDispSetBlend]
void sub_427E70(EEContext& ctx);  // 0x427E70 [tmxDrawQuad]

}  // namespace p3fes::game
