// Slice ui4: the message / menu / font band 0x3A0000-0x3C4430, fourth UI pass, and three functions of the spr*
// layer 0x1120C0-0x1126AC (game/src/ui/ui4.cpp; docs/ANALYSIS/20_menu_ui.md 4.3 and 5, 18_script_vm.md 5). Hand-decompiled from
// SLUS_216.21 on p3fes_handgen bodies. Every function keeps the name symbols/functions.json gives it; a proposed name is
// given in [brackets] (and in symbols/deltas/ui4.sym). Register ABI throughout: arguments in $a0.. ($f12.. for floats),
// the result in $v0.
//
// Records (obs from the instructions unless marked inf; the offsets are the ui4:: constants below):
//
// * SprFile (0x1C0 bytes, RwCalloc; the list at gp-0x4DB0): +0 u16 kind, +2 path, +0x104 rasters[32], +0x184 sprite
//   records, +0x188 H_Cdvd request, +0x18C in-memory data, +0x1B8 next, +0x1BC prev. sprFileHandleUpdate loads it.
// * SprHandle (0x34 bytes, RwCalloc; the persistent list at gp-0x4DB4): +0 next, +4 prev, +8 file, +0xC sprite index,
//   +0x10 / +0x14 f32 x / y, +0x18 flags, +0x19 inverse alpha, +0x2C f32 z, +0x30..+0x32 rgb.
// * ItfMesHandle (bmd_msg.h; msg2.h lists the sub-records): +0 state (bits 0-2 request state 2 opening / 3 open, bits 8-9
//   and 12-13 window phases 1 opening .. 3 closing, bit 17, bit 19 hide panels, 0x200000 open the window on the next
//   request, bit 24 shown), +12 z, +18 window type, +20 speaker sub-record, +36 text sub-record (+48 its line chain, +52
//   busy), +44 record, +60 / +62 request argument / line count, +64 selection sub-record (+76 option lines, +84 state,
//   +86 chosen, +88 cursor row, +90 count, +92 / +96 widest row), +168 panels (+168 speaker plate, +172 window, +176 third;
//   +208 the window-type argument), +212 32 message-argument words and (+340) their heap blocks, +468 window sub-record
//   (+468 active, +470 phase, +472 frame, +474 pop-in y offset, +480 / +482 window x / y).
// * Manager slot (52 bytes from 0x959EE0, bmd_msg.h ItfMesSlotLinks): +4 next, +8 id, +12 current handle, +20 entries.
// * itfPnl (msg2.h): +0 its heap block, +4 the work buffer's block, +8 work buffer, +12 z, +16..+28 x0 y0 x1 y1,
//   +44..+56 rgba, +60 type; drawn through itfMesManagerDrawTypeTbl 0x6A1C90 (15 types).
// * FrTextLayout (48 bytes on sub_3B2990's frame; the record every text-tag handler gets in $a1): +0 x, +4 y, +8 16 x colour
//   word, +12 style, +13 colour set, +14 glyph mode, +15 alpha, +16 text, +20 the line node being built, +24 read position,
//   +28 new-line, +29 position-pending, +30 u16 line code. sub_3B2430 walks the text; a byte 0xFn starts a tag
//   (code = byte << 8 | next byte, n - 1 = the parameter pairs), handler sFrTagTable[code & 0xFF](code, layout), a non-zero
//   result stops. A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8 (no byte is 0).
// * frFont line node (font.h): +8 y, +0x14 z, +0x24 next, +0x30 wait code, +0x34 wait armed, +0x38 wait flag, +0x3C ticks.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace ui4 {
namespace spr {
inline constexpr s32 kTaskWork = 60;  // kwlnTask +0x3C: the task's work block
inline constexpr s32 kGpFileList = -19888;  // gp-0x4DB0 = 0x7CDF40: head of the .SPR file handle list
inline constexpr s32 kGpHandleList = -19892;  // gp-0x4DB4 = 0x7CDF3C: head of the persistent sprite draw handle list
inline constexpr s32 kFileKind = 0;  // SprFile u16: 0 = loaded from a path (sprAddFile), 1 = built around data in memory
inline constexpr s32 kFileName = 2;  // SprFile: the path (strcpy)
inline constexpr s32 kFileRasters = 260;  // SprFile +0x104: RwRaster*[32], one per texture
inline constexpr s32 kFileRecords = 388;  // SprFile +0x184: the RwCalloc'd sprite records (0x80 bytes each)
inline constexpr s32 kFileCdNode = 392;  // SprFile +0x188: the H_Cdvd request of the file
inline constexpr s32 kFileData = 396;  // SprFile +0x18C: the in-memory file (sprCreateHandleFromData)
inline constexpr s32 kFileNext = 440;  // SprFile +0x1B8: next file handle
inline constexpr s32 kFilePrev = 444;  // SprFile +0x1BC: previous file handle
inline constexpr s32 kFileSize = 448;  // sizeof(SprFile) = 0x1C0
inline constexpr s32 kHandleNext = 0;  // SprHandle: next draw handle
inline constexpr s32 kHandlePrev = 4;  // SprHandle: previous draw handle (or the owning list word)
inline constexpr s32 kHandleFile = 8;  // SprHandle: the SprFile
inline constexpr s32 kHandleSprite = 12;  // SprHandle: sprite index in the file
inline constexpr s32 kHandleX = 16;  // SprHandle f32 x
inline constexpr s32 kHandleY = 20;  // SprHandle f32 y
inline constexpr s32 kHandleFlags = 24;  // SprHandle u8 flags
inline constexpr s32 kHandleInvAlpha = 25;  // SprHandle u8: 255 - alpha
inline constexpr s32 kHandleZ = 44;  // SprHandle f32 z
inline constexpr s32 kHandleR = 48;  // SprHandle u8 r (g +49, b +50; 0xFF on creation)
inline constexpr s32 kHandleG = 49;  // SprHandle u8 g
inline constexpr s32 kHandleB = 50;  // SprHandle u8 b
inline constexpr s32 kHandleSize = 52;  // sizeof(SprHandle) = 0x34
}  // namespace spr
namespace rw {
inline constexpr s32 kMalloc = 376;  // 0x960178 (lo of 0x960000 +): the RwMalloc slot
inline constexpr s32 kFree = 380;  // 0x96017C: the RwFree slot
inline constexpr s32 kCalloc = 388;  // 0x960184: the RwCalloc slot
inline constexpr s32 kHintUi = 0x40000;  // the memory hint every UI allocation passes
}  // namespace rw
namespace mes {
inline constexpr s32 kLoHandleCount = -24896;  // 0x959EC0 (0x960000 - 0x6140): handles created (itfMesMngInitialize ++)
inline constexpr s32 kLoDestroyed = -24892;  // 0x959EC4: cleared by the manager's destroy callback
inline constexpr s32 kLoDrawFrames = -24888;  // 0x959EC8: frames drawn by "DrawMsgMng"
inline constexpr s32 kLoFlags = -24884;  // 0x959ECC u16: manager flags (bit 1: a window panel was drawn this frame)
inline constexpr s32 kLoSlotList = -24880;  // 0x959ED0: sItfMesManagerMsgHead, the slots in use (bmd_msg.h ItfMesSlotList)
inline constexpr s32 kLoSlotFree = -24872;  // 0x959ED8: the free-slot list head
inline constexpr s32 kLoCursorOwner = -29720;  // 0x958BE8: a record whose +12 names the handle the cursor marker belongs to (inf)
inline constexpr s32 kSlotNext = 4;  // manager slot: next slot in use
inline constexpr s32 kSlotId = 8;  // manager slot: its index = the slot id scripts hold
inline constexpr s32 kSlotHandle = 12;  // manager slot: the current message handle
inline constexpr s32 kSlotEntries = 20;  // manager slot: four {handle, handle} entries
inline constexpr s32 kSlotEntryCopy = 24;  // manager slot entry 0, second word
inline constexpr s32 kState = 0;  // ItfMesHandle state word
inline constexpr s32 kSpeakerWord2 = 8;  // ItfMesHandle: the speaker block's third word ("MSG1" files)
inline constexpr s32 kZ = 12;  // ItfMesHandle: the text z handed to every line (frFont line +0x14)
inline constexpr s32 kWindowType = 18;  // ItfMesHandle s16 window type
inline constexpr s32 kSpeaker = 20;  // ItfMesHandle: speaker sub-record (+0 x, +4 y, +8 name line, +12 u16 speaker index)
inline constexpr s32 kSpeakerY = 24;  // ItfMesHandle: speaker y
inline constexpr s32 kSpeakerLine = 28;  // ItfMesHandle: the speaker name line chain
inline constexpr s32 kSpeakerIndex = 32;  // ItfMesHandle u16: speaker index (0xFFFF none, bit 15: name from message argument)
inline constexpr s32 kText = 36;  // ItfMesHandle: text sub-record (+0 x, +4 y, +12 line chain, +16 busy)
inline constexpr s32 kTextY = 40;  // ItfMesHandle: text y
inline constexpr s32 kRecord = 44;  // ItfMesHandle: the current dialogue record
inline constexpr s32 kTextLines = 48;  // ItfMesHandle: the text line chain
inline constexpr s32 kRequestArg = 60;  // ItfMesHandle s16: the third argument of itfMesMngRequestMessage
inline constexpr s32 kLineCount = 62;  // ItfMesHandle s16: the record's line count
inline constexpr s32 kSelectWord84 = 84;  // ItfMesHandle s16 +84 (selection state: 0 idle, < 0 chosen)
inline constexpr s32 kSelection = 86;  // ItfMesHandle s16: the chosen option
inline constexpr s32 kSelectRow = 88;  // ItfMesHandle s16: the cursor row (-1 none)
inline constexpr s32 kPanel0 = 168;  // ItfMesHandle: panel sub-record, first itfPnl (the speaker plate)
inline constexpr s32 kPanel1 = 172;  // ItfMesHandle: the window panel
inline constexpr s32 kPanel2 = 176;  // ItfMesHandle: the third panel
inline constexpr s32 kPanelArg = 40;  // panel sub-record +40 (= handle +208): the window-type argument
inline constexpr s32 kArgs = 212;  // ItfMesHandle: 32 message-argument words, then (+340) their 32 heap blocks
inline constexpr s32 kArgBlocks = 128;  // argument table: the heap block of word i is 32 words further
inline constexpr s32 kWindowAnim = 468;  // ItfMesHandle: window sub-record (+0 u8 active, +2 s16 phase, +4 s16 frame, +6 s16 y offset)
inline constexpr s32 kWindowFrame = 472;  // ItfMesHandle s16: the window animation frame
inline constexpr s32 kWindowYOffset = 474;  // ItfMesHandle s16: the window pop-in y offset
inline constexpr s32 kWindowX = 480;  // ItfMesHandle s16: window x (itfMesMngSetWindowOffset)
inline constexpr s32 kWindowY = 482;  // ItfMesHandle s16: window y
inline constexpr s32 kRecLineCount = 24;  // dialogue record u16 line count
inline constexpr s32 kRecSpeaker = 26;  // dialogue record u16 speaker
inline constexpr s32 kSubX = 0;  // speaker / text sub-record x
inline constexpr s32 kSubY = 4;  // speaker / text sub-record y
inline constexpr s32 kSubLine = 8;  // speaker sub-record: its line chain
inline constexpr s32 kSubIndex = 12;  // speaker sub-record u16 index; text sub-record: its line chain
inline constexpr s32 kSubTextLines = 12;  // text sub-record: its line chain (= handle +48)
inline constexpr s32 kSubBusy = 16;  // text sub-record s8 busy (= handle +52)
inline constexpr s32 kSelLines = 12;  // selection sub-record (handle +64): the option line chain (+76)
inline constexpr s32 kSelWord84 = 20;  // selection sub-record: +84
inline constexpr s32 kSelChosen = 22;  // selection sub-record: +86 the chosen option / cursor
inline constexpr s32 kSelCursor2 = 24;  // selection sub-record: +88
inline constexpr s32 kSelCount = 26;  // selection sub-record: +90 option count
inline constexpr s32 kSelWidestPos = 28;  // selection sub-record: +92 x of the widest row
inline constexpr s32 kSelWidest = 32;  // selection sub-record: +96 width of the widest row
inline constexpr s32 kSelKeyCount = 38;  // key-map record s16 count; entries {s16 pad bit, s16 value} from +40
inline constexpr s32 kSelKeys = 40;  // key-map record: first {pad bit, value}
inline constexpr s32 kWinActive = 0;  // window sub-record u8 active
inline constexpr s32 kWinPhase = 2;  // window sub-record s16 phase (0 popping in, 1 done)
inline constexpr s32 kWinFrame = 4;  // window sub-record s16 frame
inline constexpr s32 kWinYOffset = 6;  // window sub-record s16 y offset
inline constexpr s32 kPnlRecNext = 4;  // panel sub-record: second panel (= handle +172)
inline constexpr s32 kPnlRecThird = 8;  // panel sub-record: third panel (= handle +176)
inline constexpr s32 kLineNext = 36;  // frFont line node +0x24: next line
inline constexpr s32 kLineY = 8;  // frFont line node: y (1/16 px)
}  // namespace mes
namespace pnl {
inline constexpr s32 kBlock = 0;  // itfPnl: the heap block holding the panel
inline constexpr s32 kWorkBlock = 4;  // itfPnl: the heap block of the work buffer
inline constexpr s32 kWork = 8;  // itfPnl: the per-type work buffer (vertices, colours)
inline constexpr s32 kZ = 12;  // itfPnl z
inline constexpr s32 kX0 = 16;  // itfPnl x0
inline constexpr s32 kY0 = 20;  // itfPnl y0
inline constexpr s32 kX1 = 24;  // itfPnl x1
inline constexpr s32 kY1 = 28;  // itfPnl y1
inline constexpr s32 kR = 44;  // itfPnl colour r
inline constexpr s32 kG = 48;  // itfPnl colour g
inline constexpr s32 kB = 52;  // itfPnl colour b
inline constexpr s32 kA = 56;  // itfPnl colour alpha
inline constexpr s32 kType = 60;  // itfPnl u8 type (0..14)
inline constexpr s32 kType0Alpha = 92;  // type-0 work buffer: alpha of its colour table
inline constexpr s32 kType0Colours = 64;  // type-0 work buffer: its colour table
inline constexpr s32 kType4Alpha = 44;  // type-4 work buffer: alpha of its colour table
inline constexpr s32 kType4Colours = 32;  // type-4 work buffer: its colour table
inline constexpr s32 kType5Alpha = 76;  // type-5 work buffer: alpha of its colour table
inline constexpr s32 kType5Colours = 48;  // type-5 work buffer: its colour table
inline constexpr s32 kType12Value = 4;  // type-12 work buffer word +4
inline constexpr s32 kType9Alpha = 0x212C;  // 0x6A212C (0x6A0000 +): the type-9 colour's alpha
inline constexpr s32 kShadeR = 0;  // shade table entry (16 bytes): r factor (16.16)
inline constexpr s32 kShadeG = 4;  // shade table entry: g factor
inline constexpr s32 kShadeB = 8;  // shade table entry: b factor
inline constexpr s32 kOutA = 12;  // shaded colour (16 bytes): alpha
}  // namespace pnl
namespace lay {
inline constexpr s32 kX = 0;  // FrTextLayout x
inline constexpr s32 kY = 4;  // FrTextLayout y
inline constexpr s32 kColour = 8;  // FrTextLayout: 16 x the colour word (the line's +0x14 gets it >> 4)
inline constexpr s32 kStyle = 12;  // FrTextLayout s8 font style (tag 0x06)
inline constexpr s32 kColourSet = 13;  // FrTextLayout s8 colour set (tag 0x02; 3 while an inserted string is laid out)
inline constexpr s32 kMode = 14;  // FrTextLayout s8 glyph mode (tag 0x09)
inline constexpr s32 kAlpha = 15;  // FrTextLayout u8 alpha (tags 0x07, 0x12, 0x3F)
inline constexpr s32 kText = 16;  // FrTextLayout: the text
inline constexpr s32 kLine = 20;  // FrTextLayout: the line node being built (draw-time scans: the window)
inline constexpr s32 kPos = 24;  // FrTextLayout: read position (at a handler: the first parameter byte)
inline constexpr s32 kNewLine = 28;  // FrTextLayout u8: start a new line node before the next glyph
inline constexpr s32 kPosPending = 29;  // FrTextLayout u8: the next line takes (x, y)
inline constexpr s32 kLineCode = 30;  // FrTextLayout u16: the code stored in each new line node (tags 0x12, 0x3F)
inline constexpr s32 kGpTagFlags = -22536;  // gp-0x5808 = 0x7CD4E8: the tag-flag word (font.h kTagFlags)
inline constexpr s32 kGpGlyphFlags = -22512;  // gp-0x57F0 = 0x7CD500: the default glyph flags (font.h kDefaultGlyphFlags)
inline constexpr s32 kGpTag16A = -18120;  // gp-0x46C8 = 0x7CE628: tag 0x16's first parameter
inline constexpr s32 kGpTag16B = -18116;  // gp-0x46C4 = 0x7CE62C: tag 0x16's second parameter
inline constexpr s32 kGpDrawMode = -18112;  // gp-0x46C0 = 0x7CE630: the third argument of every frFontDraw
inline constexpr s32 kGpTag18 = -18108;  // gp-0x46BC = 0x7CE634: set to 20 by tag 0x18 with parameter 0
inline constexpr s32 kWaitCode = 48;  // frFont line node +0x30: the wait tag's code
inline constexpr s32 kWaitArmed = 52;  // frFont line node +0x34: a wait is armed (tag 0x17 stores its code here)
inline constexpr s32 kWaitFlag = 56;  // frFont line node +0x38: 1 when a wait arrives while one is armed
inline constexpr s32 kWaitTicks = 60;  // frFont line node +0x3C: ticks to wait
}  // namespace lay
namespace fnt {
inline constexpr s32 kGpMesWinSpr = -18076;  // gp-0x469C = 0x7CE654: the SprFile of facility/i_mes_win01.spr
inline constexpr s32 kGpRasterSlots = -18092;  // gp-0x46AC = 0x7CE644: the raster-slot manager (font.h kRasterSlots)
inline constexpr s32 kLoReleaseList0 = -20896;  // 0x95AE60 (0x960000 -): deferred line release list 0
inline constexpr s32 kLoReleaseList1 = -20892;  // 0x95AE64: deferred line release list 1
inline constexpr s32 kLoGlyphRing = -20964;  // 0x95AE1C: the glyph-node ring buffer (font.h kGlyphRing)
inline constexpr s32 kLoLineRing = -20960;  // 0x95AE20: the line-node ring buffer
inline constexpr s32 kLoBuffer24 = -20956;  // 0x95AE24: a font buffer handed to nullsub_21 at teardown
inline constexpr s32 kLoBuffer28 = -20952;  // 0x95AE28: a second one
inline constexpr s32 kLoGslList = -20804;  // 0x95AEBC: the GS-list container (font.h kGslList)
inline constexpr s32 kLoGslBlock0 = -20832;  // 0x95AEA0: GS-list block 0
inline constexpr s32 kLoGslBlock1 = -20828;  // 0x95AEA4: GS-list block 1
inline constexpr s32 kSlotGlyph = 4;  // raster slot +4 (u16 here: 1 = registered)
inline constexpr s32 kSlotEntry = 8;  // raster slot +8: its GS-list entry
inline constexpr s32 kEntrySlot = 20;  // GS-list entry +0x14: its raster slot
inline constexpr s32 kLineZ = 20;  // frFont line node +0x14: z (f32)
}  // namespace fnt
}  // namespace ui4


// --- the spr* layer: the .SPR file list and the persistent sprite draw (0x1120C0-0x1126AC) -------------------------
// 0x1120C0 sub_1120C0: [sprUpdateFiles] Runs sprFileHandleUpdate on every .SPR file handle of the list (gp-0x4DB0), from the
//   head along +0x1B8 (sprFontInit, kwlnRootUpdate2DDrawBeginTask, the PAK screens).
void sub_1120C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x112370 sprAddFile: Registers a .SPR file by path: RwCalloc(1, 0x1C0, 0x40000) a file handle, kind 0, the path copied to +2,
//   appended at the tail of the file list (the loading itself is sprFileHandleUpdate's, frame by frame).
//   Returns the handle.
void sprAddFile(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1125D0 sprSpriteDrawAll: Draws the persistent sprite handles (kwlnRootUpdate2DDrawBeginTask): the Im2D render states (6,1) (7,2) (8,1)
//   (9,1) (12,1) (11,6) (10,5) through RwRenderStateSet (0x960090), then sprDrawSprite (sub_1127D0) on every
//   handle of the list at gp-0x4DB4.
void sprSpriteDrawAll(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfMesManager.c: the COMM handlers next to scrCommand_MSG, handles, requests, slots ---------------------------
// 0x3A2660 sub_3A2660: [scrCommand_MSG_SEL] Script COMM handler of a selection: with no message slot returns 1. Otherwise (K_Assert
//   line 937 on a null handle) reads integer parameter 0; while +84 is 0 it (re)issues the selection request
//   (sub_3A37C0(slot, p)) and returns 0 (call again); once +84 went negative it clears it, returns the chosen
//   option (+86) to the script, resets the selection and returns 1. A positive +84 returns 0.
void sub_3A2660(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A2900 sub_3A2900: [scrCommand_MSG_WINDOW] COMM handler: switches the script's message window to type 4 (arg 0) and sets state
//   bit 0x200000 (open on the next request). Returns 1.
void sub_3A2900(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A2970 sub_3A2970: [scrCommand_MSG_CLOSE] COMM handler: with no slot returns 1. Otherwise (K_Assert line 1227) while the window
//   phase (state bits 8-9) is 1 or 2 it starts the close (sub_3A2A30); returns 1 once the phase is 0 (closed),
//   else 0.
void sub_3A2970(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A2B30 sub_3A2B30: [scrCommand_SET_MSG_VAR] COMM handler SET_MSG_VAR(index, value, type): prints the call (debug printf), then
//   sub_3A4010(slot, index, value, type), the three parameters read again. Returns 1.
void sub_3A2B30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3470 sub_3A3470: [itfMesMngClearText] Releases the handle's text lines and resets the text sub-record (itfMesMngInitTextRecord,
//   keep 0), clears the request state (bits 0-2) and bit 17; with `also_speaker` the speaker name line too
//   (itfMesMngInitSpeakerRecord, keep 0).
void sub_3A3470(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A4220 sub_3A4220: [itfMesMngSetMessageArgStringBySlot] sub_3A5CA0(handle of slot, i, text, 0): message argument i of the slot
//   becomes a copy of `text` (18 callers: the battle, facility and event texts).
void sub_3A4220(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfMesManager.c: the manager tasks, text and panel helpers, the selection cursor, the window draws ------------
// 0x3A4CE0 sub_3A4CE0: [itfMesMngSystemInit] The message manager's start (frFontSystemStart): counters and flags cleared, the 64-slot
//   list built over 0x959EE0 (sub_3B4920, 52-byte slots) with every free slot's handle cleared, the process
//   "CalcMsgMng" (dds3InitProcess sub_35AD80: priority 4207, update sub_3A8440, destroy sub_3A8530) and the task
//   "DrawMsgMng" (kwlnTaskInit: 7359, sub_3A84C0, sub_3A8530) created, then "[%s] init mes manage" printed.
void sub_3A4CE0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A5210 sub_3A5210: [itfMesMngSetTextStyleBySlot] On the slot's text line chain: alpha, line code, style, colour set
//   (frFontLineSetAlpha / frFontNodeSetCode / frFontLineSetStyle / frFontLineSetColourSet).
void sub_3A5210(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A52C0 sub_3A52C0: [itfMesMngLayoutLineBySlot] Pushes the message arguments of the slot in $t2 to the font, lays out a dialogue line
//   through sub_3A53B0 (its sixth argument 0) and sets the result's style to $a3. Returns the line chain
//   (sub_248580, sub_25BE60: battle texts).
void sub_3A52C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A5540 sub_3A5540: [itfMesMngLayoutLine] sub_3A53B0 with the arguments from the sixth on moved one register up and 0 as the
//   sixth (5 callers in the battle UI).
void sub_3A5540(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6060 sub_3A6060: [itfMesMngSetSpeakerText] Replaces the handle's speaker name line by a layout of `text` at the speaker
//   position (style 0, colour set 1, alpha 255) and marks the speaker index 0xFFFF (sub_3A5980). K_Assert line
//   4406 on a null handle.
void sub_3A6060(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6B00 sub_3A6B00: [itfMesMngReleasePanels] Releases the three panels of the handle (+168, +172, +176) and clears state bits 8-11.
void sub_3A6B00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6B90 sub_3A6B90: [itfMesMngFreeArgStrings] For the 32 message-argument words at `table`: a non-zero word has its heap block
//   (32 words further) H_Freed and is cleared.
void sub_3A6B90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A7940 sub_3A7940: [itfMesMngMoveWindowY] Moves a handle's window down by `dy`: text y and every text line's y, panels 1 and 0
//   (sub_3A8EA0, the panel move), and when a speaker name exists the speaker y and its lines.
void sub_3A7940(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A7CB0 sub_3A7CB0: [itfMesMngMoveSelection] Moves the selection cursor of a selection sub-record one option by the sign of $a1
//   (wrapping at both ends): the old row back to alpha 0, the new one to 6 (itfMesMngTextSetLineAlpha), +86 and
//   +88 = the new row, then the cursor sound (sub_10A4E0(0, 0, 0, 0)).
void sub_3A7CB0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A7D60 sub_3A7D60: [itfMesMngKeyToValue] Returns the value of the first {pad bit, value} pair (from +40, count at +38) whose bit
//   is held in gPadFlags (0x7E094E); -1 when none.
void sub_3A7D60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A7DD0 sub_3A7DD0: [itfMesMngWindowPopStep] One frame of the window pop-in: while the window sub-record (+468) is active and in
//   phase 0 the frame advances and the y offset takes the curve value {0, -32, -12, 6, -4, 0}[frame] (0x6A1BD0,
//   copied to the frame first); at frame 5 the phase becomes 1 (done).
void sub_3A7DD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8080 sub_3A8080: [itfMesManagerDrawPanels] Draws a handle's window panels unless state bit 19 is set: with a window phase >= 1
//   panel 1 (not for window type 3) through sub_3A9080, manager flag bit 1 set, and panel 2 when present; then,
//   when the record at 0x958BE8 names this handle, the cursor corners of panel 1 (sub_3A8590).
void sub_3A8080(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8170 itfMesManagerDrawSprite: Draws the selection cursor bar of a handle (when a cursor row is set and an option line exists): y =
//   1928 + 200 * row for 4 options, else 1928 + 8 * (int)(75.0 / count) * row + 8 * ((int)(75.0 / count) >> 1);
//   then sprites 0x12 at x 225 and 0x13 at x 561 of facility/i_mes_win01.spr at (y >> 3) + 2, alpha 255
//   (itfMesManagerDrawSpriteEx). (20_menu_ui.md 4.3 calls these the window frame; the instructions draw them
//   at the cursor row.)
void itfMesManagerDrawSprite(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8260 sub_3A8260: [itfMesMngMeasureCursor] Debug "drawCursolVist": for a handle with a cursor row, finds the widest row of the
//   option lines (its position into +92, its width into +96) and the cursor row's position (into a dead local).
void sub_3A8260(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8350 sub_3A8350: [itfMesMngDrawPrompt] Draws sprite 0x10 of i_mes_win01.spr at the window position (+480, +482 - 5 + the pop-in
//   y offset) with alpha 255 * frame / 5 (the float -> u8 conversion with its >= 2^31 path).
void sub_3A8350(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8440 sub_3A8440: [itfMesManagerCalcProc] The "CalcMsgMng" update: per slot in use, on its current handle sub_3A6E30, sub_3A7120,
//   sub_3A7490 and the pop-in step sub_3A7DD0. Returns 0.
void sub_3A8440(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A84C0 sub_3A84C0: [itfMesManagerUpdateDrawTask] The "DrawMsgMng" update: itfMesManagerDrawMsg on every slot's handle, then the
//   frame counter. Returns 0.
void sub_3A84C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8530 sub_3A8530: [itfMesManagerDestroyProc] Destroy callback of both manager tasks: sub_3A4DD0 on every slot id in use (the next
//   slot read first), then 0x959EC4 = 0.
void sub_3A8530(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8590 sub_3A8590: [itfPnlCursorCorners] Copies the four corners {x0,y0} {x1,y0} {x1,y1} {x0,y1} of a panel into a 32-byte local
//   that nothing reads (the stripped cursor draw); the zeroing loop before it runs only on a non-null frame address.
void sub_3A8590(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8600 sub_3A8600: [itfMesMngSetPanelValueBySlot] sub_3AB2A0(panel 1 of the slot's handle, value).
void sub_3A8600(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8650 sub_3A8650: [itfMesMngSetPanelRectBySlot] itfPnlSetPosition(panel 1 of the slot's handle, x0, y0, x1, y1, z) from
//   (slot, x0, y0, z, x1, y1); K_Assert line 7477 on a null handle.
void sub_3A8650(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8710 itfMesManagerDrawSpriteEx: Draws sprite `id` of facility/i_mes_win01.spr (gp-0x469C) once at (x, y) with z $f12 and alpha `alpha`
//   (inverse alpha 255 - alpha): sprCreateHandle(0, file, id), sprDrawSprite, sprDestroyHandle. Returns 0.
void itfMesManagerDrawSpriteEx(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfPanel.c: release, rectangle, colour, the draw-type dispatch and draw types 0 / 4 / 5 / 9 / 14 --------------
// 0x3A8D60 itfPnlRelease: Frees a panel (debug print first): the work buffer's heap block when the panel has a work buffer, then the
//   panel's own block. A null panel only prints.
void itfPnlRelease(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8DC0 itfPnlSetPosition: Sets a panel's rectangle and z (K_Assert line 590; debug print) and rebuilds its vertices through the
//   per-type table 0x6A1C10 (itfPnlSetVertexType*: work buffer, x0, y0, x1, y1) when the type has one.
void itfPnlSetPosition(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A8FB0 itfPnlSetColor: Sets a panel's colour (K_Assert line 660; debug print) and its per-type colours through the table 0x6A1C50
//   (itfPnlSetColorType*: work buffer, r, g, b, a) when the type has one.
void itfPnlSetColor(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9080 sub_3A9080: [itfPnlDraw] Draws a panel: sub_3AC590 (an empty hook) and sub_3A90C0(panel, 0).
void sub_3A9080(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A90C0 sub_3A90C0: [itfPnlDrawByType] K_Assert line 726 on a null panel, then the panel's draw routine from
//   itfMesManagerDrawTypeTbl 0x6A1C90[type] (panel, arg).
void sub_3A90C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9E20 sub_3A9E20: [itfMesManagerDrawType0] Draw type 0: the panel alpha into the work buffer's colour table, then three gouraud
//   quads (sub_3B4B40: points, colours, the index lists 0x6A1EE0 + 4i / 0x6A1EF0 + 4i, z, arg).
void sub_3A9E20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AA280 sub_3AA280: [itfMesManagerDrawType4] Draw type 4: the alpha into the colour table, one gouraud quad (index lists 0x7CD4D0,
//   0x7CE624).
void sub_3AA280(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AA2D0 sub_3AA2D0: [itfMesManagerDrawType5] Draw type 5: the alpha into the colour table; the rest calls the empty hooks
//   nullsub_118 / nullsub_116 (a stripped six-point draw over 0x7CD4D8 / 0x7CD4E0).
void sub_3AA2D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AB2A0 sub_3AB2A0: [itfPnlSetType12Value] K_Assert a non-null type-12 panel (lines 2059 / 2060), then work +4 = value.
void sub_3AB2A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC230 sub_3AC230: [itfMesManagerDrawType14] Draw type 14: nothing.
void sub_3AC230(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC500 sub_3AC500: [itfMesManagerDrawType9] Draw type 9: the colour alpha at 0x6A212C = 103 * panel alpha / 128 (toward zero), the
//   rectangle copied to a local, then sub_3B4D10(rect, colour 0x6A2120, z, 576, arg).
void sub_3AC500(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC590 sub_3AC590: [itfPnlDrawHook] An empty hook (sub_3A9080 calls it before every panel).
void sub_3AC590(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frTagTable.c: the BMD text-tag handlers of sFrTagTable 0x6A2370 ($a0 = tag code, $a1 = FrTextLayout) ----------
// 0x3AC5A0 sub_3AC5A0: tag 0x02 (sFrTagTable 0x6A2370 [0x02]): colour set = b0 - 1. Returns 0.
void sub_3AC5A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC600 sub_3AC600: tag 0x03 (sFrTagTable 0x6A2370 [0x03]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; when message argument p (kTagSlotTable 0x95AC70) is set, the pending run is
//   closed (sub_3B22A0) and argument p & 0xFF laid out (sub_3B1D90). Returns 0.
void sub_3AC600(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC6C0 sub_3AC6C0: tag 0x04 (sFrTagTable 0x6A2370 [0x04]): tag flags |= 1; returns 1 (stops the layout).
void sub_3AC6C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC6E0 sub_3AC6E0: tag 0x05 (sFrTagTable 0x6A2370 [0x05]): nothing; returns 0.
void sub_3AC6E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC6F0 sub_3AC6F0: tag 0x06 (sFrTagTable 0x6A2370 [0x06]): font style = b0 - 1. Returns 0.
void sub_3AC6F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC750 sub_3AC750: tag 0x07 (sFrTagTable 0x6A2370 [0x07]): alpha = b0 - 1. Returns 0.
void sub_3AC750(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC7B0 sub_3AC7B0: tag 0x08 (sFrTagTable 0x6A2370 [0x08]): nothing; returns 0.
void sub_3AC7B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC7C0 sub_3AC7C0: tag 0x09 (sFrTagTable 0x6A2370 [0x09]): glyph mode = b0 - 1. Returns 0.
void sub_3AC7C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC820 sub_3AC820: tag 0x0A (sFrTagTable 0x6A2370 [0x0A]): lays out sprintf("%s", sub_177670(1)) -- a name string from the buffer at 0x833BB0 (inf: the
//   hero's family name). Returns 0.
void sub_3AC820(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AC890 sub_3AC890: tag 0x0B (sFrTagTable 0x6A2370 [0x0B]): the same with sub_177790(1) (the buffer at 0x833BD0; inf: the given name). Returns 0.
void sub_3AC890(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACA30 sub_3ACA30: tag 0x0D (sFrTagTable 0x6A2370 [0x0D]): nothing; returns 0.
void sub_3ACA30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACA40 sub_3ACA40: tag 0x0E (sFrTagTable 0x6A2370 [0x0E]): nothing; returns 0.
void sub_3ACA40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACA50 sub_3ACA50: tag 0x0F (sFrTagTable 0x6A2370 [0x0F]): a new row (frFontLayoutNewRow) unless default glyph flag 4 is set. Returns 0.
void sub_3ACA50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACA90 sub_3ACA90: tag 0x10 (sFrTagTable 0x6A2370 [0x10]): tag flags |= 2; returns 0.
void sub_3ACA90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACAB0 sub_3ACAB0: tag 0x11 (sFrTagTable 0x6A2370 [0x11]): with default glyph flag 8: tag flags |= 1 and returns 1 (stop); else a new row when flag 0x20
//   is set; returns 0.
void sub_3ACAB0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACB10 sub_3ACB10: tag 0x12 (sFrTagTable 0x6A2370 [0x12]): alpha = b0 - 1, line code = parameter 1 (bytes 2, 3). Returns 0.
void sub_3ACB10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACDA0 sub_3ACDA0: tag 0x48 (sFrTagTable 0x6A2370 [0x48]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; with flag 388 set and default glyph flag 0x100 clear, sub_10A2E0(2, 2, p) (a sound
//   request; inf: a voice line). Returns 0.
void sub_3ACDA0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ACF80 sub_3ACF80: tag 0x4A (sFrTagTable 0x6A2370 [0x4A]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; with flag 388 set, sub_10A2E0(2, 2, p). Returns 0.
void sub_3ACF80(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD030 sub_3AD030: tag 0x4B (sFrTagTable 0x6A2370 [0x4B]): parameters p0, p1; with flag 388 set, sub_10A2E0(p0, 2, p1). Returns 0.
void sub_3AD030(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD130 sub_3AD130: tag 0x14 (sFrTagTable 0x6A2370 [0x14]): a wait on the current line: +0x38 = 1 when a wait is armed (+0x34), +0x30 = the tag code,
//   +0x3C = parameter 0 ticks. Returns 0.
void sub_3AD130(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD1B0 sub_3AD1B0: tag 0x15 (sFrTagTable 0x6A2370 [0x15]): the same wait, ticks = (s16) parameter 0 with flag 388 set, else 35; clamped at 0.
void sub_3AD1B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD2A0 sub_3AD2A0: tag 0x16 (sFrTagTable 0x6A2370 [0x16]): parameters p0 / p1 to 0x7CE628 / 0x7CE62C, tag flags |= 8. Returns 0.
void sub_3AD2A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD360 sub_3AD360: tag 0x17 (sFrTagTable 0x6A2370 [0x17]): arms a wait on the current line (+0x34 = the tag code). Returns 0.
void sub_3AD360(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD380 sub_3AD380: tag 0x18 (sFrTagTable 0x6A2370 [0x18]): with parameter 0 equal to 0, 0x7CE634 = 20. Returns 0.
void sub_3AD380(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD640 sub_3AD640: tag 0x19 (sFrTagTable 0x6A2370 [0x19]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; when message argument p is set: with colour set 3, the glyph 0x83D5 then argument p
//   & 0xFF laid out; the colour set restored. Returns 0.
void sub_3AD640(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD860 sub_3AD860: tag 0x1B (sFrTagTable 0x6A2370 [0x1B]): when message argument p is set, argument p & 0xFF laid out with colour set 3. Returns 0.
void sub_3AD860(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AD930 sub_3AD930: tag 0x1C (sFrTagTable 0x6A2370 [0x1C]): the same as tag 0x1B. Returns 0.
void sub_3AD930(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADA00 sub_3ADA00: tag 0x1D (sFrTagTable 0x6A2370 [0x1D]): with colour set 3: the glyph 0x83D5, then the name sub_171110((s16) p, 0) returns (a table
//   lookup over 0x5DABF0.. of g_data.c); the colour set restored. Returns 0.
void sub_3ADA00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADB00 sub_3ADB00: tag 0x1E (sFrTagTable 0x6A2370 [0x1E]): sub_3AD400((u16) p, 2, code, layout). Returns 0.
void sub_3ADB00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADD00 sub_3ADD00: tag 0x20 (sFrTagTable 0x6A2370 [0x20]): sub_3CF520() (a flag-389 / 0x7CE680 check of the facility layer). Returns 0.
void sub_3ADD00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADD30 sub_3ADD30: tag 0x21 (sFrTagTable 0x6A2370 [0x21]): nothing; returns 0.
void sub_3ADD30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADE60 sub_3ADE60: tag 0x23 (sFrTagTable 0x6A2370 [0x23]): nothing; returns 0.
void sub_3ADE60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADE70 sub_3ADE70: tag 0x24 (sFrTagTable 0x6A2370 [0x24]): sub_3BB060(p0, p1) (the scene layer, mt_sceneFunc.c). Returns 0.
void sub_3ADE70(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADF40 sub_3ADF40: tag 0x25 (sFrTagTable 0x6A2370 [0x25]): nothing; returns 0.
void sub_3ADF40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADF50 sub_3ADF50: tag 0x26 (sFrTagTable 0x6A2370 [0x26]): nothing; returns 0.
void sub_3ADF50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADF60 sub_3ADF60: tag 0x27 (sFrTagTable 0x6A2370 [0x27]): nothing; returns 0.
void sub_3ADF60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3ADF70 sub_3ADF70: tag 0x28 (sFrTagTable 0x6A2370 [0x28]): clndGetCurrentWeekDay() (result unused), then sub_16E2B0(sub_16DD40(), p) (g_data.c). Returns 0.
void sub_3ADF70(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE140 sub_3AE140: tag 0x2A (sFrTagTable 0x6A2370 [0x2A]): nothing; returns 0.
void sub_3AE140(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE150 sub_3AE150: tag 0x2B (sFrTagTable 0x6A2370 [0x2B]): nothing; returns 0.
void sub_3AE150(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE160 sub_3AE160: tag 0x32 (sFrTagTable 0x6A2370 [0x32]): datSetFlag({0, 0x400, 0xC00, 0x1000, 0x1400}[p0] + p1, 1): sets a flag of bank p0 (the table
//   0x6A2680 copied to the frame). Returns 0.
void sub_3AE160(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE260 sub_3AE260: tag 0x33 (sFrTagTable 0x6A2370 [0x33]): the same with datSetFlag(..., 0): clears the flag. Returns 0.
void sub_3AE260(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE360 sub_3AE360: tag 0x2C (sFrTagTable 0x6A2370 [0x2C]): lays out string sub_17C860(p) of row p of the phrase table 0x6A24D0 (four pointers a row:
//   "Sayonara", "Mata na", "Ja ne", "Hasta la vista", ...). Returns 0.
void sub_3AE360(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE560 sub_3AE560: tag 0x2E (sFrTagTable 0x6A2370 [0x2E]): lays out club name sub_16E190(p) of the table 0x6A25C0 ("Go-home", "Track Team", ...,
//   "Music Club"; K_Assert line 747 when above 6). Returns 0.
void sub_3AE560(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE650 sub_3AE650: tag 0x2F (sFrTagTable 0x6A2370 [0x2F]): copies the text from the read position up to the next 10 (two-byte glyphs and tag parameters
//   skipped whole) into the zeroed buffer 0x95ABF0, NUL-terminated; tag flags |= 0x10; the read position moves past
//   it. Returns 0.
void sub_3AE650(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE750 sub_3AE750: tag 0x30 (sFrTagTable 0x6A2370 [0x30]): sub_170C00(1, p0, p1) (g_data.c). Returns 0.
void sub_3AE750(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE820 sub_3AE820: tag 0x31 (sFrTagTable 0x6A2370 [0x31]): tag flags |= 3; returns 1 (stops the layout).
void sub_3AE820(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE840 sub_3AE840: tag 0x34 (sFrTagTable 0x6A2370 [0x34]): nothing; returns 0.
void sub_3AE840(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE850 sub_3AE850: tag 0x35 (sFrTagTable 0x6A2370 [0x35]): nothing; returns 0.
void sub_3AE850(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE860 sub_3AE860: tag 0x36 (sFrTagTable 0x6A2370 [0x36]): nothing; returns 0.
void sub_3AE860(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE870 sub_3AE870: tag 0x37 (sFrTagTable 0x6A2370 [0x37]): lays out the current month, sprintf("%d", clndGetCurrentMonth()). Returns 0.
void sub_3AE870(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE8D0 sub_3AE8D0: tag 0x38 (sFrTagTable 0x6A2370 [0x38]): lays out the current day of the month (clndGetCurrentDay). Returns 0.
void sub_3AE8D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE930 sub_3AE930: tag 0x39 (sFrTagTable 0x6A2370 [0x39]): sub_171C40(sub_16DD40(), 1) (g_data.c). Returns 0.
void sub_3AE930(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE970 sub_3AE970: tag 0x3A (sFrTagTable 0x6A2370 [0x3A]): sub_171C40(sub_16DD40(), 0). Returns 0.
void sub_3AE970(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE9B0 sub_3AE9B0: tag 0x3B (sFrTagTable 0x6A2370 [0x3B]): lays out the weekday glyph of clndGetCurrentWeekDay() from the 7 x 8-byte table 0x6A26B0
//   (copied to the frame). Returns 0.
void sub_3AE9B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AEC20 sub_3AEC20: tag 0x3D (sFrTagTable 0x6A2370 [0x3D]): lays out the element icon of skill p: the glyph 0x8D, table0x6A26F0[datCalcGetSkillElement(0, p)]
//   - 90 (the 19-byte table copied to the frame). Returns 0.
void sub_3AEC20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AED10 sub_3AED10: tag 0x3E (sFrTagTable 0x6A2370 [0x3E]): lays out sub_3C3F80 [comuGetLinkTitle] of p, or of sub_16DD40() when p is 0 (K_Assert line
//   908 when that is 0 too). Returns 0.
void sub_3AED10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AEE00 sub_3AEE00: tag 0x3F (sFrTagTable 0x6A2370 [0x3F]): alpha = 20, line code = 32. Returns 0.
void sub_3AEE00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AF520 sub_3AF520: tag 0x44 (sFrTagTable 0x6A2370 [0x44]): sub_172200(sub_16DD40(), 1) (g_data.c). Returns 0.
void sub_3AF520(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AF560 sub_3AF560: tag 0x45 (sFrTagTable 0x6A2370 [0x45]): sub_172200(sub_16DD40(), 0). Returns 0.
void sub_3AF560(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frFont.c / frFontEx.c / frFontRaster.c / fmGslCont.c: styles, line release, layout entry points, start / end ---
// 0x3AF770 frLoadFontData_Ptr: frAddFontStyle(style, 0, fnt): adds a font style from a .FNT already in memory (sub_27ACE0).
void frLoadFontData_Ptr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFA40 sub_3AFA40: [frFontSystemEnd] Destroy callback of the task "fontMan": frees the font styles, releases both deferred line
//   lists, destroys the glyph and line ring buffers (sub_3B4740), the GS list (sub_3B44A0), hands the buffers
//   0x95AE24 / 0x95AE28 to nullsub_21 and frees the raster-slot manager (sub_3B3740).
void sub_3AFA40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFC30 sub_3AFC30: [frFreeFontStyleBlock] RwFree of the first word of font style `style` (sFrFontStyles 0x95ACF0, 32 bytes a
//   style; sub_27AFD0).
void sub_3AFC30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFF50 frFontPrintClutData: Debug: six times an empty 16-step loop and printf("load clut data for font :%s\n", "frFont.c").
void frFontPrintClutData(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFFD0 sub_3AFFD0: [frFontLineReleaseFaded2] A copy of sub_3B0170 (sub_3A7490 calls this one).
void sub_3AFFD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B0170 sub_3B0170: [frFontLineReleaseFaded] Steps a line chain's fade (frFontLineFadeStep); once nothing changed any more the
//   chain's nodes go back to the ring buffers (sub_3B0030). Returns the chain or sub_3B0030's result.
void sub_3B0170(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B03A0 frFontRegisterGlyphRaster: Takes a GS-list entry (fmGslAllocEntry; K_Abort "FONT SYS : GS buffer over flow." line 1599 when none) and
//   its raster slot (+0x14; K_Assert line 1604), marks the slot (+4 = 1) and links it back to the entry (+8).
//   Returns the slot.
void frFontRegisterGlyphRaster(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B1300 sub_3B1300: [itfMesManagerFontDraw] sub_3B1330(line, 0) (itfMesManagerDrawMsg).
void sub_3B1300(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B1330 sub_3B1330: [itfMesManagerFontDraw2] frFontDraw(line, skip, the word at 0x7CE630).
void sub_3B1330(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B18C0 sub_3B18C0: [frFontManUpdate] The task "fontMan"'s update: releases deferred line list sub_35AEA0() (0x95AE60 + 4i;
//   sub_35AEA0 returns 0) through sub_3B0030 and stores the result back, then ages the raster slots
//   (frFontRasterAgeSlots). Returns 0.
void sub_3B18C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B19A0 frSetMessageFontStyle: frAddFontStyle(8, fnt, 0): binds a message's own font as style 8 (itfMesMngRequestMessage for "MSG1").
void frSetMessageFontStyle(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2900 sub_3B2900: [frFontLayoutTextSimple] sub_3B2990(x, y, 0, 0, 0, 0, 255, text, chain): a text layout with style 0, colour
//   set 0, mode 0, alpha 255 (sub_3A4B90).
void sub_3B2900(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2940 sub_3B2940: [frFontLayoutTextAt] sub_3B2990(x, y, 0, style, colour set, mode, alpha, text, chain): the layout with colour
//   word 0 (the message manager's name and text lines).
void sub_3B2940(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2990 sub_3B2990: [frFontLayoutText] Builds the 48-byte FrTextLayout record on its frame -- x, y, 16 * colour, style, colour
//   set, mode, alpha, text, chain, position 0, new-line 1, position-pending 1, line code 32 -- and runs the
//   layout (sub_3B2430). Returns the line chain.
void sub_3B2990(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2C60 sub_3B2C60: [frFontLineSetZ] K_Assert(line) ("frFontEx.c" line 19), then the line's z (+0x14) = $f12. 18 callers.
void sub_3B2C60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B3740 sub_3B3740: [frFontRasterSlotsFree] RwFree of the raster-slot manager (gp-0x46AC), which is then cleared.
void sub_3B3740(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B3D60 frFontRasterFindOrAlloc: The raster slot of (glyph, colour): frFontRasterLookup, else frFontRasterAllocSlot; 0 when both fail.
void frFontRasterFindOrAlloc(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B44A0 sub_3B44A0: [fmGslFree] When the GS list exists (0x95AEBC), RwFrees its two blocks (0x95AEA0, 0x95AEA4), clears it and returns
//   1; else 0.
void sub_3B44A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B45F0 sub_3B45F0: [rbInitRingBuf] A ring buffer of `count` records of `size` bytes: RwMalloc((size + 8) * (count + 1) + 4,
//   0x40000), the block's own address in its first word, then count + 1 headers {index, next} chained (each
//   record 8 + size bytes), the last {count, first}. Returns the first record (block + 4).
void sub_3B45F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4740 sub_3B4740: [rbDestroy] RwFree of the block in front of a ring buffer (its word -4). Returns 1.
void sub_3B4740(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4A90 sub_3B4A90: [itfPnlShadeColours] For `n` 16-byte entries of a 16.16 shade table: dst = {min(r * t.r, 0xFF0000) >> 16,
//   the same for g (MMI mult1) and b, alpha}; dst advances 16 bytes. itfPnlSetColorType1..3 call it.
void sub_3B4A90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4E90 nullsub_119: An empty hook of the panel draws (sub_3AA370, sub_3AC240, sub_3AC350).
void nullsub_119(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4EA0 nullsub_121: An empty hook (sub_3AC240).
void nullsub_121(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4EB0 nullsub_116: An empty hook: the stripped point draw of draw types 1, 2, 5.
void nullsub_116(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4EC0 nullsub_117: An empty hook (draw types 1, 2, 3).
void nullsub_117(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4ED0 nullsub_118: An empty hook: the stripped render-state set of draw type 5.
void nullsub_118(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4EE0 frFontSystemStart: The font / message system start (kwlnInitMain): msgWinReset, the task "fclBank" (kwlnTaskInitEx: 6320,
//   fclBank_UpdateTask) stored into sub_3CF120's record, frInitFontTable(256, 256), the task "fontMan" (4196,
//   update sub_3B18C0, destroy sub_3AFA40), the message manager (sub_3A4CE0), fclMisc_CreateMsgAssistTask, then
//   facility/i_mes_win01.spr read synchronously (H_Cdvd_Request + H_Cdvd_ReadSync) and registered with
//   sprAddFile into gp-0x469C.
void frFontSystemStart(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
