// Phase 5 slice script4, the 0x3A0000 band (game/src/script/script4_msg.cpp): the message manager internals the
// earlier UI passes (ui2 / ui3 / ui4, msg2) left -- itfMesManager.c's handle release / free, line builders, argument
// strings, panel set-ups and per-frame panel step, the message draw; itfPanel.c's create / move / Im2D draw and six
// draw types; the frTagTable.c tags 0x0C (the hero's name) and 0x1A (an item name with its icon); the card effect's
// load steps sub_3A1C00; the event-message sequence step sub_3A0B50; plus sub_3CF630, the event-busy test the panel
// step waits on. scrCommand_MSG (COMM 0) and the request / initialize path stay recompiled:
// other slices' tests stand them in (docs/INTEGRATION_LOG.md, ui4 and script4). Every body is p3fes_handgen's
// register-ABI body with roles, named offsets and comments added; names are symbols/functions.json's, bracketed names
// proposals (symbols/deltas/script4.sym).
//
// The message handle (ItfMesHandle, H_Malloc'd; layouts as in ui4.h, confirmed from these bodies):
//   +0   state word: bits 0..2 text phase (>= 3 drawing, 4 finished), bits 3..5 selection phase (3 appearing, 4 live),
//        bits 8..9 window panel phase (1 opening, 2 open, 3 closing), bits 10..11 third panel phase, bits 12..13 speaker
//        plate fade (1 in, 2 shown, 3 out), bit 16 tag flag 2 of the text, bit 17 text hidden, bit 18 selection hidden,
//        bit 21 tight line spacing (window type 4), bit 22 keep the glyph nodes, bit 25 do not wait for the event
//        (sub_3CF630), bits 26 / 27 tag flags 0x80 / 0xC0.
//   +12 z, +18 s16 window type, +20 speaker record {x, y, line chain +28, u16 index +32}, +36 text record {x, y, record
//   +44, line chain +48, u8 flags +53, colours +54..+57, s16 last line +58, s16 line +60}, +64 selection record (line
//   chain +76, +80, s16 +84 / chosen +86 / +88 / +90), +168 panel record {plate +168, window +172, third +176, the
//   window rectangle offsets +180..+192, rgb +196..+204, alpha +208}, +212 the 32 message-argument words (+340 their
//   heap blocks), +468 window animation (u8 flags: 1 prompt, 2 sprite), +476, +484 a text callback.
// The manager slots: 0x959EE0 + 52 * id (slot +12 = the current handle, +20 four {handle, handle} entries); the handle
// count 0x959EC0, the slot list 0x959ED0 (ui4.h kLo*).
// The panel (itfPnl, 80 bytes H_Malloc'd by sub_3A8B00): +0 itself, +4 / +8 work buffer (size per type, 0x6A1D10), +12
// z, +16..+28 rectangle, +32 / +36 type words, +44..+56 rgba, +56 alpha step, +60 u8 type, +64..+76 the animation
// callbacks (clear, open, close; itfPnlRunPhase0..3 call them).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace s4msg {

// --- globals: lo halves under 0x960000 / 0x6A0000 / 0x7C0000, gp-relative under $gp = 0x7D2CF0 --------------------
constexpr s32 kLoHandleCount = -24896;  // 0x959EC0: handles in use (ui4.h kLoHandleCount)
constexpr s32 kLoPanelArg = -24892;     // 0x959EC4: the word every panel create receives
constexpr s32 kLoMgrFlags = -24884;     // 0x959ECC u16: bit 0 reset nodes, bit 1 a window panel drawn this frame
constexpr s32 kLoSlotList = -24880;     // 0x959ED0: sItfMesManagerMsgHead (slots in use)
constexpr s32 kLoSlotBase = -24896;     // 0x959EC0 + 52 * id + 32 = slot id (the bodies index from the count word)
constexpr s32 kLoSlotHandle = -24852;   // 0x959EEC = slot 0 +12: the current handle of slot id (+ 52 * id)
constexpr s32 kSlotBytes = 52;
constexpr s32 kSlotRecord = 32;         // from 0x959EC0 + 52 * id to the slot itself
constexpr s32 kSlotHandleInRow = 44;    // 0x959EC0 + 52 * id + 44 = slot +12
constexpr s32 kGpLineSpacing = -18100;  // 0x7CE63C s32: tight line spacing in force (116 while set)
constexpr s32 kGpWinAlphaScale = -32604; // 0x7CAD94 f32 0.85: window type 10's alpha scale
constexpr s32 kGpEvtBusy = -18032;      // 0x7CE680: the event work sub_3CF630 reads
constexpr s32 kMemHintUi = 0x40000;

// --- ItfMesHandle (ui4.h) ---------------------------------------------------------------------------------------
constexpr s32 kHState = 0, kHZ = 12, kHWinType = 18;
constexpr s32 kHSpeaker = 20, kHSpeakerLine = 28;
constexpr s32 kHText = 36, kHRecord = 44, kHTextLine = 48, kHLineIdx = 60;
constexpr s32 kHSel = 64, kHSelLine = 76, kHSelWord84 = 84, kHSelChosen = 86, kHSelWord90 = 90;
constexpr s32 kHPanels = 168, kHPlate = 168, kHWindow = 172, kHThird = 176;
constexpr s32 kHArgs = 212, kHArgBlocks = 128;  // argument words; their heap blocks 32 words further
constexpr s32 kHAnim = 468, kHAnim476 = 476, kHTextHook = 484;
constexpr s32 kRecLineCount = 24, kRecLines = 28;  // dialogue record: s16 line count, line pointers
// text record (handle +36): x, y, the record, the line chain, flags, colours, last line, line index
constexpr s32 kTxX = 0, kTxY = 4, kTxRecord = 8, kTxLine = 12, kTxFlags = 17, kTxColour = 18, kTxLastLine = 22,
              kTxLineIdx = 24;
// selection record (handle +64)
constexpr s32 kSlLine = 12, kSlWord80 = 16, kSlWord84 = 20, kSlChosen = 22, kSlRow = 24, kSlCount = 26;
// panel record (handle +168): plate, window, third panel, window rectangle offsets, rgb, alpha
constexpr s32 kPrPlate = 0, kPrWindow = 4, kPrThird = 8, kPrX0 = 12, kPrY0 = 16, kPrX1 = 20, kPrY1 = 24, kPrR = 28,
              kPrG = 32, kPrB = 36, kPrA = 40;

// --- the state word's fields ----------------------------------------------------------------------------------------
constexpr u32 kStTextPhase = 0x7, kStSelPhase = 0x38, kStWindowPhase = 0x300, kStThirdPhase = 0xC00,
              kStPlatePhase = 0x3000, kStTagFlag2 = 0x10000, kStTextHidden = 0x20000, kStSelHidden = 0x40000,
              kStTightSpacing = 0x200000, kStKeepNodes = 0x400000, kStNoEventWait = 0x2000000;

// --- itfPnl ---------------------------------------------------------------------------------------------------------
constexpr s32 kPnSelf = 0, kPnWork = 4, kPnCursor = 8, kPnZ = 12, kPnX0 = 16, kPnY0 = 20, kPnX1 = 24, kPnY1 = 28,
              kPnWord32 = 32, kPnWord36 = 36, kPnAlpha = 56, kPnType = 60, kPnAnimClear = 64, kPnAnimOpen = 68,
              kPnAnimClose = 72, kPnAnim76 = 76, kPnBytes = 80;

// --- frTagTable.c layout record ($a1 of a tag handler) ---------------------------------------------------------------
constexpr s32 kLayData = 16, kLayPos = 24;  // the tag's parameter bytes are at data + pos

}  // namespace s4msg

void sub_3A0B50(EEContext& ctx);  // 0x3A0B50 [evtMsgSequenceStep] (work) -> 1 when the message sequence of work +192 is done
void sub_3A1C00(EEContext& ctx);  // 0x3A1C00 [ceCardEffLoadStep] (task) the card effect's load steps -> 0, -1 when done
void sub_3A3530(EEContext& ctx);  // 0x3A3530 [itfMesMngOpenSelPanel9] the type-9 selection panel around the option rows
void sub_3A3680(EEContext& ctx);  // 0x3A3680 [itfMesMngOpenSelPanel11] the type-11 selection panel
void sub_3A4A70(EEContext& ctx);  // 0x3A4A70 [itfMesMngSetTagParam] (slot, key, value) -> 1 when stored
void sub_3A4DD0(EEContext& ctx);  // 0x3A4DD0 [itfMesMngReleaseSlot] (slot id)
void sub_3A4EF0(EEContext& ctx);  // 0x3A4EF0 [itfMesMngFreeHandle] (handle)
void sub_3A53B0(EEContext& ctx);  // 0x3A53B0 [itfMesMngBuildLine] (x, y, rgba, style, colour set, flags, slot, line) -> line chain
void sub_3A5570(EEContext& ctx);  // 0x3A5570 [itfMesMngDrawLine] one dialogue line drawn once
void sub_3A56F0(EEContext& ctx);  // 0x3A56F0 [itfMesMngDrawLine2] one or two dialogue lines drawn once
void sub_3A5980(EEContext& ctx);  // 0x3A5980 [itfMesMngBuildText] the current line of the handle's record
void sub_3A5CA0(EEContext& ctx);  // 0x3A5CA0 [itfMesMngSetArgString] (handle, index, data, size)
void sub_3A5EA0(EEContext& ctx);  // 0x3A5EA0 [itfMesMngSetArgWord] (handle, index, word)
void sub_3A6140(EEContext& ctx);  // 0x3A6140 [itfMesMngBuildOptions] the selection's option lines
void sub_3A6520(EEContext& ctx);  // 0x3A6520 [itfMesMngOpenWindow] the window panel of the handle's window type
void sub_3A67E0(EEContext& ctx);  // 0x3A67E0 [itfMesMngOpenPlate] the speaker name plate
void sub_3A6CA0(EEContext& ctx);  // 0x3A6CA0 [itfMesMngSetWindowLayout] (panel record, window type, alpha)
void sub_3A6E30(EEContext& ctx);  // 0x3A6E30 [itfMesMngStepPanels] per frame: the three panels' phases
void itfMesManagerDrawMsg(EEContext& ctx);  // 0x3A7E90 the per-frame draw of one handle
void sub_3A87D0(EEContext& ctx);  // 0x3A87D0 [itfPnlDrawIm2D] (x, y, points, count, rgba, keep state, $f12 z)
void sub_3A8B00(EEContext& ctx);  // 0x3A8B00 [itfPnlRegist2] (type, arg) -> panel (named by its debug print)
void sub_3A8EA0(EEContext& ctx);  // 0x3A8EA0 [itfPnlSetPositionOffset] (panel, dx0, dy0, dx1, dy1, dz) (named by its debug print)
void sub_3A9ED0(EEContext& ctx);  // 0x3A9ED0 [itfPnlDrawType1] (panel, arg)
void sub_3AA000(EEContext& ctx);  // 0x3AA000 [itfPnlDrawType2]
void sub_3AA130(EEContext& ctx);  // 0x3AA130 [itfPnlDrawType3]
void sub_3AC240(EEContext& ctx);  // 0x3AC240 [itfPnlDrawType7]
void sub_3AC350(EEContext& ctx);  // 0x3AC350 [itfPnlDrawType8]
void sub_3AA370(EEContext& ctx);  // 0x3AA370 [itfPnlDrawType6] the name-plate panel
void sub_3AC900(EEContext& ctx);  // 0x3AC900 [frTagHeroName] tag 0x0C: character 1's names into the text
void sub_3AD400(EEContext& ctx);  // 0x3AD400 [frTagItemNameWithIcon] (item, column, tag, layout): icon glyph + item name
void sub_3AD740(EEContext& ctx);  // 0x3AD740 [frTagItemName] tag 0x1A: the item / column from two message arguments
void sub_3CF630(EEContext& ctx);  // 0x3CF630 [evtIsBusy] -> 1 while the event's step or one of its 3 panels runs

}  // namespace p3fes::game
