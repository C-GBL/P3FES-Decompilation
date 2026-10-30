// BMD message manager, second slice (Atlus itfMesManager.c, itfPanel.c): the per-slot handle accessors,
// the current-handle switch, the choice-mask helpers, the speaker-name lookup, the sub-record
// initialisers of itfMesMngCreateHandle, the text-line list helpers of the layout, and the pure panel
// routines (the per-type vertex/colour tables at 0x6A1C10 / 0x6A1C50 and the open/close animation
// steps that itfPnlRegist2 0x3A8B00 installs). Hand-decompiled from SLUS_216.21; docs/ANALYSIS/
// 18_script_vm.md section 5 and 20_menu_ui.md section 4.3 describe the system. Every function bears
// the name symbols/functions.json gives it: the names proposed from the instructions in
// symbols/deltas/msg2.sym, imported into the IDA master (update #4).
//
// Layouts read from the instructions (obs) unless marked inf:
//
// * Manager slots. sItfMesManagerMsgHead 0x959ED0 (bmd_msg.h ItfMesSlotList) is followed by the slot
//   array at 0x959EE0, 52 bytes a slot; the word at slot + 12 is the slot's current message handle,
//   so "the handle of slot id h" is *(0x959EEC + 52*h) -- every accessor below computes exactly that
//   (no bounds check; a null handle is K_Assert'ed and then used anyway). slot + 16 mirrors +12;
//   slot + 20 + 8*i (i < 4) are the slot's four {handle, handle} entries (itfMesMngInitialize).
//
// * The message handle (bmd_msg.h ItfMesHandle, 488 bytes), fields touched here:
//     +0   state word: bits 0-2 request state, 3-5 cleared by the selection reset, 8-9 / 12-13 two-bit
//          window phases, 10-11, bit 18, bits 16-31 settable through itfMesMngSetStateFlags / itfMesMngClearStateFlags
//     +20  speaker sub-record (itfMesMngInitSpeakerRecord): +20 x, +24 y, +28 name text node, +32 u16 speaker index
//     +36  text sub-record (itfMesMngInitTextRecord): +36 x, +40 y, +48 text node list, +52 u8 busy, ...
//     +64  selection sub-record (itfMesMngInitSelectRecord): +76 text node, +80 u32 choice mask (bit set = option
//          disabled, inf), +84 s16, +86 s16 cursor / chosen option, +88 s16, +90 s16 option count
//     +168 panel sub-record (itfMesMngInitPanelRecord): three itfPnl pointers
//     +212 32 words (itfMesMngClearMessageArgs), the per-message argument table handed to the font (itfMesMngPushMessageArgs)
//     +468 16-byte sub-record (itfMesMngInitWindowRecord); +480 / +482 two s16 set by itfMesMngSetWindowOffset
//
// * Text line nodes (built by the font layout, frFont.c; inf beyond the offsets): +2 u8 alpha, +4 s32 x,
//   +8 s32 y (nodes of one line share it), +12 s32 advance, +20 u32, +28 first glyph record, +32 style
//   record, +36 next node; glyph records: +16 u32 colour word (low byte kept separately), +20 u8,
//   +40 next.
//
// * itfPnl panels (80 bytes, itfPnlRegist2): +8 per-type work buffer, +12 z, +16..+28 x0 y0 x1 y1,
//   +44..+56 colour, +60 u8 type, +64/+68/+72/+76 phase callbacks (types 10-13). The animation work
//   record of types 10-13 is 16 bytes: +0 phase (1 opening, 2 open, 3 closing, 0 closed), +4 s32,
//   +8 s32 frame counter, +12 s32 alpha.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

inline constexpr u32 kItfMesSlotArray = 0x959EE0u;       // 52-byte manager slots
inline constexpr u32 kItfMesSlotStride = 52u;
inline constexpr u32 kItfMesSlotCurrentHandle = 0x959EECu;  // kItfMesSlotArray + 12
inline constexpr u32 kFrMessageArgTable = 0x95AC70u;     // 32 words written by frFontSetTagSlot (frFont.c)
inline constexpr u32 kItfPnlVertexStepTable = 0x6A1DE8u;  // {0, 8, 48}: itfPnlSetVertexType1's row offsets

// Arguments typed s64/u64 are compared as the whole 64-bit register, as the recompiled body does before
// any 32-bit operation touches them (callers pass sign-extended 32-bit values; the type keeps that exact).

// --- per-slot handle accessors (the slot id is the value scrGetMessageID returns) ------------------

// 0x3A2580 [itfMesMngGetBusy]: the s8 at handle+52 (scrCommand_MSG polls it).
void itfMesMngGetBusy(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A25F0 [itfMesMngSetBusy]: handle+52 = value (low byte).
void itfMesMngSetBusy(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A2750 [itfMesMngGetSelectWord84]: the s16 at handle+84.
void itfMesMngGetSelectWord84(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A27C0 [itfMesMngSetSelectWord84]: handle+84 = value (low half).
void itfMesMngSetSelectWord84(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A2830 [itfMesMngGetSelection]: the s16 at handle+86 (assert line 1107).
void itfMesMngGetSelection(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3F20 [itfMesMngGetSelection2]: the same s16 at handle+86 (assert line 2729; a second copy).
void itfMesMngGetSelection2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3DA0 [itfMesMngGetState]: the state word handle+0.
void itfMesMngGetState(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3E10 [itfMesMngSetStateFlags]: state |= flags & 0xFFFF0000.
void itfMesMngSetStateFlags(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3E90 [itfMesMngClearStateFlags]: state &= ~(flags & 0xFFFF0000).
void itfMesMngClearStateFlags(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3BA0 [itfMesMngSetChoiceMask]: handle+80 = mask.
void itfMesMngSetChoiceMask(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3C10 [itfMesMngSetSelection]: maps option `option` to its index among the enabled options: walks
// bits 0..option of the choice mask (at least bit 0; the bound is the caller's whole 64-bit $a1),
// counting the clear (enabled) ones; when bit `option` itself is set the result is 0, else count - 1;
// stored to handle+86 (cursor) and +88.
void itfMesMngSetSelection(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3CE0 [itfMesMngSetTextPosition]: moves the text sub-record to (x, y): when either delta is
// non-zero, offsets every node of the text list (itfMesMngTextOffsetNodes) and stores x/y at handle+36/+40.
void itfMesMngSetTextPosition(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3F90 [itfMesMngGetMessageArg]: word i of the handle's 32-word table at +212 (no bounds check).
void itfMesMngGetMessageArg(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A5120 [itfMesMngGetMessageType]: the type word of BMD entry i of the slot's handle.
void itfMesMngGetMessageType(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A51A0 [itfMesMngGetMessageCount]: the BMD message count of the slot's handle.
void itfMesMngGetMessageCount(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6A80 [itfMesMngSetWindowOffset]: handle+480 = a, handle+482 = b (s16 each).
void itfMesMngSetWindowOffset(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3AB0 [itfMesMngResetSelectionBySlot]: itfMesMngResetSelection on the slot's handle. Leaves the slot entry's
// address in $v0 (its scratch register) unless the callee's font release writes $v0.
void itfMesMngResetSelectionBySlot(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A3B00 [itfMesMngResetSelection]: releases the selection text node (+76, through the still-
// recompiled sub_3B0170) and clears the selection sub-record: +84 = 0, +90 = 0, +86 = -1, +80 = 0;
// state &= ~0x38, then &= ~0x40000. K_Assert on a null handle (line 2354).
void itfMesMngResetSelection(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A2C90 [itfMesMngSwitchCurrentHandle]: makes entry i (0..3, K_Assert otherwise) of `slot_va` the
// slot's current handle. 0 when the entry is empty. Otherwise, when a handle was current, its 488 bytes
// are first copied to a buffer on the guest stack (a 560-byte frame, buffer at +64) and afterwards the
// new handle takes the old state word and the old +168 panel sub-record (44 bytes) from that copy;
// slot+12 and slot+16 both get the new handle. Returns the entry's address (slot + 20 + 8*i).
void itfMesMngSwitchCurrentHandle(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A3010 [itfMesMngGetBmdMessageCount]: K_Assert(itfMesMngCheckBmdMagic(bmd)) (line 1788), then the
// header's message count.
void itfMesMngGetBmdMessageCount(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- message records and handle sub-records ----------------------------------------------------------

// 0x3A5940 [itfMesMngGetDialogueLine]: the text pointer of line i of a dialogue record (u16 count at
// +24, pointers from +28); 0 when i is out of range.
void itfMesMngGetDialogueLine(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6030 [itfMesMngGetSpeakerName]: the speaker name pointer of the handle: speaker table of the
// bound BMD (bmd_msg.h BmdSpeakerBlock::table) at the u16 index handle+32. No range check.
void itfMesMngGetSpeakerName(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6100 [itfMesMngCountClearBits]: the number of clear bits among the low `n` bits of `mask`.
void itfMesMngCountClearBits(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A5FD0 [itfMesMngPushMessageArgs]: hands the 32 words at `table_va` to the font, word i through
// frFontSetTagSlot(i, word) (frFont.c: kFrMessageArgTable[i] = word). Leaves table_va + 124 in $v0.
void itfMesMngPushMessageArgs(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6900 [itfMesMngInitSpeakerRecord]: with `defaults`, x = 656 and y = 2632; always text node = 0,
// speaker index = 0xFFFF.
void itfMesMngInitSpeakerRecord(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6930 [itfMesMngInitTextRecord]: with `defaults`, x = 864 and y = 2840; then clears the record and
// sets the byte at +21 to 255.
void itfMesMngInitTextRecord(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6980 [itfMesMngInitSelectRecord]: x = 3824, y = 3904, cleared, +22/+24 = -1.
void itfMesMngInitSelectRecord(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A69D0 [itfMesMngInitPanelRecord]: three null panel pointers, then sub_3A6CA0(rec, 0, 0).
void itfMesMngInitPanelRecord(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6A10 [itfMesMngClearMessageArgs]: zeroes 32 words.
void itfMesMngClearMessageArgs(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6A40 [itfMesMngInitWindowRecord]: the byte at +0 cleared unless `keep`; +2..+11 cleared,
// +12 = 568, +14 = 395 (s16).
void itfMesMngInitWindowRecord(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6C10 [itfMesMngFormatNumber]: writes the decimal digits of n (at most 10, most significant first)
// as two-byte glyph codes ((d + 16) << 8) + 0x8080 at out, then a 0 halfword; returns the address of
// that terminator. The digits come from repeated div by 10 (a non-positive quotient stops the loop).
void itfMesMngFormatNumber(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- text line-node lists (frFont layout) -----------------------------------------------------------

// 0x3A6280 [itfMesMngTextGetLastNode]: the last node of the list.
void itfMesMngTextGetLastNode(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A62B0 [itfMesMngTextCopyNodeStyle]: dst+21 = src[+2] >> 1; dst+18/19/20 = style[+21], [+20], [+22] of the
// style record src+32 points to.
void itfMesMngTextCopyNodeStyle(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A62E0 [itfMesMngTextGetLineIndex]: ((b.y - a.y) >> 3) / b.s16[+18] + 1 (EE div: HI/LO as the original).
void itfMesMngTextGetLineIndex(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6310 [itfMesMngTextOffsetNodes]: every node's x += dx, y += dy.
void itfMesMngTextOffsetNodes(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6350 [itfMesMngTextSetNodesWord20]: every node's +20 word = value.
void itfMesMngTextSetNodesWord20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6380 [itfMesMngTextSetLineAlpha]: skips (last - first - 1) line changes (nodes with a new y), then sets
// the +20 byte of every glyph record of the nodes of the line it reached to `alpha`.
void itfMesMngTextSetLineAlpha(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6410 [itfMesMngTextSetGlyphColour]: every glyph record of every node: colour = (colour & ~0xFF) | value.
void itfMesMngTextSetGlyphColour(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A6460 [itfMesMngTextGetMaxLineWidth]: the largest sum of +12 advances over the nodes of one line, x16.
void itfMesMngTextGetMaxLineWidth(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A64C0 [itfMesMngTextResetNodes]: frFontLineResetAlpha on every node whose first glyph record has a zero +22 byte.
void itfMesMngTextResetNodes(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfPnl per-type vertex tables (off_6A1C10) -------------------------------------------------------
// Each writes the panel's vertex list for the rectangle (x0, y0)-(x1, y1) into `buf` (the panel's +8
// buffer); coordinates are 12.4 fixed point (inf: 512 = 32 px).

// 0x3A96F0 [itfPnlSetVertexType0]: four columns {x0, x0+512, x1-512, x1} (the middle two meet at the
// centre when the panel is narrower than 1024), one {x, y0, x, y1} quad edge each.
void itfPnlSetVertexType0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9780 [itfPnlSetVertexType1]: a 4x4 grid {x0-256, x0+512, x1-512, x1+256} x {y0-128, y0+128,
// y1-128, y1+128}, then 3 rows at y0 + {0, 8, 48} and 3 rows at y1 - {0, 8, 48} over
// {x0-256, x0+1024, x1-1024, x1+256}.
void itfPnlSetVertexType1(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9930 [itfPnlSetVertexType2]: the same 4x4 grid, then 2 rows at y0 + {0, 8} and 2 at y1 - {0, 8}.
void itfPnlSetVertexType2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9AC0 [itfPnlSetVertexType3] (types 3 and 4): {a,b}, {c,b}, {c,d}, {a,d}.
void itfPnlSetVertexType3(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9AF0 [itfPnlSetVertexType5]: 2 rows {y0, y1} x 3 columns {x0, x1-1440, x1}.
void itfPnlSetVertexType5(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9B80 [itfPnlSetVertexType8]: fixed columns {416, 1152, 7024, 7760}, rows y0+352 / y1-320, written
// from buf+4.
void itfPnlSetVertexType8(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfPnl per-type colour tables (off_6A1C50) -------------------------------------------------------
// 0x3A9C00 [itfPnlSetColorType0]: +64.. = {r, g, b, 0, r, g, b, a}.
void itfPnlSetColorType0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9C30 [itfPnlSetColorType1]: +320.. = {r, g, b, 1, r, g, b, a}, then the 6 shaded colours from
// the table 0x6A1E00 into +352 (still-recompiled sub_3B4A90). Leaves 1 in $v0.
void itfPnlSetColorType1(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9C90 [itfPnlSetColorType2]: the same at +256 with 4 colours from 0x6A1E60. Leaves 1 in $v0.
void itfPnlSetColorType2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9CF0 [itfPnlSetColorType3]: +32.. = {r, g, b, a}; one shaded colour from 0x6A1EA0 into +48, two
// from 0x6A1EB0 (alpha 128) into +64.
void itfPnlSetColorType3(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9D90 [itfPnlSetColorType4]: +32.. = {r, g, b, a}.
void itfPnlSetColorType4(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9DB0 [itfPnlSetColorType5]: +48.. = {r, g, b, 0, r, g, b, a}.
void itfPnlSetColorType5(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9DE0 [itfPnlSetColorType8]: fixed {115, 135, 255, 0} twice at +68 (the arguments are ignored).
void itfPnlSetColorType8(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- itfPnl phase callbacks of types 10-13 (installed by itfPnlRegist2) and their dispatchers ---------
// Each takes the panel; the work record is the panel's +8 word. "Done" functions return 1 on the
// frame the phase finishes, else 0.

// 0x3A9140 / 0x3A92A0 / 0x3A94E0 [itfPnlAnimClear10 / 11 / 13]: memset(work, 0, 16), returns 0 (types 10, 11, 13).
void itfPnlAnimClear10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void itfPnlAnimClear11(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void itfPnlAnimClear13(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9170 [itfPnlAnimOpenType10]: 6 frames; +4 = 100 - 100*n/6, +12 = 255*n/6 from frame 2.
void itfPnlAnimOpenType10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9230 / 0x3A9580 [itfPnlAnimCloseFade10 / itfPnlAnimCloseFade13]: 10 frames of alpha 255 - 255*n/10 (types 10, 13).
void itfPnlAnimCloseFade10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void itfPnlAnimCloseFade13(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A92D0 [itfPnlAnimOpenType11]: 10 frames; +4 = 100 - (100n)/4 for n < 4, +12 = 255*n/10.
void itfPnlAnimOpenType11(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A93A0 [itfPnlAnimCloseType11]: one frame (alpha 255*(1-n)).
void itfPnlAnimCloseType11(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9400 [itfPnlAnimOpenFade15]: 15 frames of alpha 255*n/15 (type 12).
void itfPnlAnimOpenFade15(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9470 [itfPnlAnimCloseFade5]: 5 frames of alpha 255 - 255*n/5 (type 12).
void itfPnlAnimCloseFade5(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A9510 [itfPnlAnimOpenFade6]: 6 frames of alpha 255*n/6 (type 13).
void itfPnlAnimOpenFade6(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3A95F0 / 0x3A9630 / 0x3A9670 / 0x3A96B0 [itfPnlRunPhase0..3]: calls the panel's +64 / +68 / +72 /
// +76 callback (the panel stays in $a0) and returns its $v0; 1 when the slot is null.
void itfPnlRunPhase0(EEContext& ctx);
void itfPnlRunPhase1(EEContext& ctx);
void itfPnlRunPhase2(EEContext& ctx);
void itfPnlRunPhase3(EEContext& ctx);

}  // namespace p3fes::game
