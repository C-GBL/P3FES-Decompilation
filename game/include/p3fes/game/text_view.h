// Named views for the register-level text and UI bodies (p3fes_handgen, game/include/p3fes/game/hg_cpu.h): the guest
// addresses and record offsets that msg2.cpp (the message manager and the itfPnl panels), font.cpp (the font renderer)
// and ui2.cpp (the calendar, flag, camp-cursor and itemtbl helpers) read, so a body says
// `lw(v0, s0, mes_handle::kState)` instead of `lw(v0, s0, 0)`. Written by the read_text readability pass (2026-10-21);
// header only. Nothing here changes what a body runs: the constants are the values the instructions hold, and the
// helpers (la, k_assert) run exactly the statements, in order, that they stand for.
//
// Every offset comes from the instructions of the functions that use it, cross-checked against the layouts documented
// in msg2.h, bmd_msg.h, font.h, ui2.h and nm_message.h and against the proposed layouts of the type recovery
// (tools/ours/types/types_query.py; docs/ANALYSIS/28_types.md). Names are ours (ADR-0009); the confirmed ones are fed
// back through tools/ours/types/deltas/read_text.json. The battle pass's battle_view.h has the same addressing helpers
// in its own namespace; they are repeated here so the text bodies do not pull in the battle headers.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes/game/bmd_msg.h"  // the BMD image, ItfMesHandle, the manager slot list
#include "p3fes/game/font.h"     // font:: globals, style and .FNT offsets
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/msg2.h"     // kItfMesSlotCurrentHandle, kFrMessageArgTable, kItfPnlVertexStepTable
#include "p3fes/game/ui2.h"      // ui2:: g_data / calendar / pad / itemtbl globals

#include <bit>

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
}  // namespace p3fes::recomp_gen

namespace p3fes::game::tview {

// --- addressing: spell the address a `lui`/`addiu` pair or a `$gp` offset forms ------------------------------------
inline constexpr u32 kGp = 0x7D2CF0u;  // $gp of the whole program (crt0)
// `lw rt, gp_off(va)(gp)`: the signed 16-bit offset of `va` from $gp.
constexpr s32 gp_off(u32 va) noexcept { return static_cast<s32>(va - kGp); }
// `lui rt, hi(va)` + `addiu/lw rt, lo(va)(rt)`: the carry-adjusted upper half (as lui writes it: sign-extended) and the
// signed lower half. hi(0x959EEC) = 0x960000, lo(0x959EEC) = -24852.
constexpr u64 hi(u32 va) noexcept { return ee::core::lui((va + 0x8000u) >> 16); }
constexpr s32 lo(u32 va) noexcept { return static_cast<s16>(static_cast<u16>(va & 0xFFFFu)); }
static_assert(hi(0x959EECu) == 0x960000u && lo(0x959EECu) == -24852);
static_assert(gp_off(font::kRasterSlots) == -18092);
// `lui rt, hi16` of an EE single literal (lui + mtc1 builds every such float): the register value lui writes for `f`.
constexpr u64 flt(float f) noexcept { return ee::core::sext32(std::bit_cast<u32>(f)); }
static_assert(flt(1.0f) == 0x3F800000u);

// `la r, va`: the adjacent `lui r, hi(va); addiu r, r, lo(va)` pair that loads an address (same block, same order).
inline void la(hg::Gpr r, u32 va) {
    r = hi(va);
    r = hg::addiu(r, lo(va));
}

// K_Assert(file, line) called at `pc`: the original's `lui a0, hi(file); addiu a0, a0, lo(file); addiu a1, $zero, line;
// jal K_Assert` -- the same statements in the same order, one block (its `charge` stays at the call site). K_Assert is
// `jr $ra` in retail, so a failed check continues on the path after it with the same registers.
inline void k_assert(hg::Gpr a0, hg::Gpr a1, u32 pc, u32 file, s32 line) {
    a0 = hi(file);
    a0 = hg::addiu(a0, lo(file));
    a1 = hg::si(line);
    hg::jal(a0.c, pc, ::p3fes::recomp_gen::fn_sub_19D3F0_0019d3f0);
}

// --- K_Assert file arguments (the "<file>.c" strings) ---------------------------------------------------------------
inline constexpr u32 kItfMesManagerFile = 0x6A1A70u;      // "itfMesManager.c"
using font::kFrFontFile;                                  // 0x6A2730 "frFont.c"
using font::kGslContFile;                                 // 0x6A2A18 "fmGslCont.c"
inline constexpr u32 kGDataFile = ui2::kGDataSourceFile;  // 0x5E3098 "g_data.c"

// =====================================================================================================================
// itfMesManager.c (msg2.cpp): manager slots, the message handle and its sub-records, BMD records
// =====================================================================================================================

// --- a manager slot (52 bytes from kItfMesSlotArray; bmd_msg.h ItfMesSlotLinks for the first 12) ---------------------
// The script commands name a slot by its id; "the handle of slot id" is the word at kItfMesSlotCurrentHandle + 52 * id
// (the accessors compute 52 * id as ((id * 3) * 4 + id) * 4 and never check the id).
namespace mes_slot {
inline constexpr s32 kHandle = 12;        // u32: the current message handle (ItfMesHandle*), 0 when none
inline constexpr s32 kHandleMirror = 16;  // u32: a copy of +12 (itfMesMngSwitchCurrentHandle writes both)
inline constexpr s32 kEntries = 20;       // {u32 handle, u32}[4]: the slot's handles, entry i at +20 + 8 * i
inline constexpr s32 kEntrySize = 8;
inline constexpr s32 kEntryCount = 4;
inline constexpr u32 kSize = kItfMesSlotStride;  // 52
static_assert(kItfMesSlotCurrentHandle == kItfMesSlotArray + kHandle);
}  // namespace mes_slot

// --- the message handle (488 bytes; bmd_msg.h ItfMesHandle, msg2.h) --------------------------------------------------
namespace mes_handle {
inline constexpr s32 kState = 0;     // u32: bits 0-2 request state, 3-5 selection state, bit 18 a selection is up,
                                     // bits 16-31 the caller's flags (itfMesMngSetStateFlags / ClearStateFlags)
inline constexpr s32 kBmd = 4;       // u32: the bound BMD image (bmd_msg.h BmdHeader)
inline constexpr s32 kSpeaker = 20;  // the speaker sub-record (speaker_rec::)
inline constexpr s32 kText = 36;     // the text sub-record (text_rec::)
inline constexpr s32 kSelect = 64;   // the selection sub-record (select_rec::)
inline constexpr s32 kPanel = 168;   // the panel sub-record: three itfPnl pointers and the panel state, 44 bytes
inline constexpr s32 kPanelSize = 44;
inline constexpr s32 kArgs = 212;    // u32[32]: the per-message argument table handed to the font (frFontSetTagSlot)
inline constexpr s32 kArgCount = 32;
inline constexpr s32 kWindow = 468;  // the window sub-record (window_rec::), 16 bytes
inline constexpr s32 kWindowOffsetA = 480;  // s16: window_rec::kOffsetA (itfMesMngSetWindowOffset)
inline constexpr s32 kWindowOffsetB = 482;  // s16: window_rec::kOffsetB
inline constexpr u32 kSize = kItfMesHandleSize;  // 488
inline constexpr u32 kStateFlagsMask = 0xFFFF0000u;  // the bits the Set/ClearStateFlags accessors may touch
inline constexpr u32 kStateSelectBits = 0x38u;       // cleared by itfMesMngResetSelection
inline constexpr u32 kStateBit18 = 0x40000u;         // cleared by itfMesMngResetSelection
}  // namespace mes_handle

// --- the speaker sub-record (handle +20; itfMesMngInitSpeakerRecord) -------------------------------------------------
namespace speaker_rec {
inline constexpr s32 kX = 0;          // s32: 656 by default (12.4 fixed point)
inline constexpr s32 kY = 4;          // s32: 2632 by default
inline constexpr s32 kNameNode = 8;   // u32: the name's text line node
inline constexpr s32 kIndex = 12;     // u16: the speaker index into the BMD speaker table, 0xFFFF none
inline constexpr s32 kDefaultX = 656, kDefaultY = 2632;
inline constexpr s32 kNoSpeaker = 0xFFFF;
}  // namespace speaker_rec

// --- the text sub-record (handle +36; itfMesMngInitTextRecord; sub_3A5980 lays the text out from it) -----------------
namespace text_rec {
inline constexpr s32 kX = 0;            // s32: 864 by default
inline constexpr s32 kY = 4;            // s32: 2840 by default
inline constexpr s32 kRecord = 8;       // u32: the dialogue record being shown (dialogue_rec::); handle +44
inline constexpr s32 kNodes = 12;       // u32: the first text line node of the laid-out page; handle +48
inline constexpr s32 kBusy = 16;        // s8: handle +52, polled by scrCommand_MSG
inline constexpr s32 kTagFlags = 17;    // u8: frFontTestTagFlags(3) after the layout
inline constexpr s32 kStyle = 18;       // u8: the font style the layout starts with
inline constexpr s32 kColourSet = 19;   // u8: its colour set
inline constexpr s32 kMode = 20;        // u8: its glyph mode
inline constexpr s32 kAlpha = 21;       // u8: its alpha (255 by default)
inline constexpr s32 kLastLine = 22;    // s16: the line index of the page's last node (itfMesMngTextGetLineIndex)
inline constexpr s32 kLine = 24;        // s16: the dialogue record's line (page) shown
inline constexpr s32 kWord26 = 26;      // s16: cleared by the initialiser
inline constexpr s32 kDefaultX = 864, kDefaultY = 2840;
inline constexpr s32 kOpaque = 255;
}  // namespace text_rec

// --- the selection sub-record (handle +64; itfMesMngInitSelectRecord, itfMesMngResetSelection) -----------------------
namespace select_rec {
inline constexpr s32 kX = 0;           // s32: 3824
inline constexpr s32 kY = 4;           // s32: 3904
inline constexpr s32 kNode = 12;       // u32: the options' text line node (handle +76)
inline constexpr s32 kChoiceMask = 16; // u32: bit i set = option i disabled (handle +80)
inline constexpr s32 kWord84 = 20;     // s16 (handle +84; itfMesMngGet/SetSelectWord84)
inline constexpr s32 kCursor = 22;     // s16: the cursor / chosen option, -1 none (handle +86; itfMesMngGetSelection)
inline constexpr s32 kCursor2 = 24;    // s16: a second copy (handle +88), -1 none
inline constexpr s32 kOptionCount = 26;  // s16 (handle +90)
inline constexpr s32 kWord28 = 28, kWord32 = 32, kHalf36 = 36, kHalf38 = 38;  // cleared by the initialiser
inline constexpr s32 kDefaultX = 3824, kDefaultY = 3904;
inline constexpr s32 kNone = -1;
}  // namespace select_rec

// --- the window sub-record (handle +468; itfMesMngInitWindowRecord) --------------------------------------------------
namespace window_rec {
inline constexpr s32 kByte0 = 0;   // u8: cleared unless the caller keeps it
inline constexpr s32 kHalf2 = 2, kHalf4 = 4, kHalf6 = 6, kWord8 = 8;  // cleared
inline constexpr s32 kOffsetA = 12;  // s16: the window offset a, 568 by default (itfMesMngSetWindowOffset: handle +480)
inline constexpr s32 kOffsetB = 14;  // s16: the window offset b, 395 by default (handle +482)
inline constexpr s32 kDefaultOffsetA = 568, kDefaultOffsetB = 395;
}  // namespace window_rec
static_assert(mes_handle::kWindowOffsetA == mes_handle::kWindow + window_rec::kOffsetA &&
              mes_handle::kWindowOffsetB == mes_handle::kWindow + window_rec::kOffsetB);

// --- the BMD image (bmd_msg.h BmdHeader / BmdMessageEntry / BmdSpeakerBlock), relocated in place --------------------
namespace bmd_img {
inline constexpr s32 kMessageCount = 0x18;  // u32 BmdHeader::message_count
inline constexpr s32 kEntries = 0x20;       // BmdMessageEntry[message_count] {u32 type, u32 record}
inline constexpr s32 kEntrySize = 8;
inline constexpr s32 kEntryType = 0;        // 0 dialogue, 1 selection
inline constexpr s32 kEntryRecord = 4;
inline constexpr s32 kSpeakerTable = 0;     // BmdSpeakerBlock::table (the block follows the entries)
}  // namespace bmd_img

// --- a dialogue record (a BMD message of type 0) ---------------------------------------------------------------------
namespace dialogue_rec {
inline constexpr s32 kLineCount = 24;  // s16: its lines (pages)
inline constexpr s32 kLines = 28;      // u32[count]: the text of each line
}  // namespace dialogue_rec

// --- text line nodes and their glyph nodes (frFont.c; font.h "Line node" / "Glyph node") ----------------------------
namespace line_node {
inline constexpr s32 kCode = 0x00;        // u16
inline constexpr s32 kAlpha = 0x02;       // u8
inline constexpr s32 kSpacing = 0x03;     // s8: letter spacing, added per glyph to the line width
inline constexpr s32 kX = 0x04;           // s32 (1/16 px)
inline constexpr s32 kY = 0x08;           // s32 (1/16 px); the nodes of one line share it
inline constexpr s32 kGlyphCount = 0x0C;  // s32
inline constexpr s32 kLineStep = 0x12;    // s16: the line step of the layout (itfMesMngTextGetLineIndex divides by it)
inline constexpr s32 kWord20 = 0x14;      // u32 (itfMesMngTextSetNodesWord20; a float to frFontDraw)
inline constexpr s32 kGlyphs = 0x1C;      // u32: the first glyph node
inline constexpr s32 kStyleGlyph = 0x20;  // u32: the glyph node whose style the line ends in (itfMesMngTextCopyNodeStyle)
inline constexpr s32 kNext = 0x24;        // u32: the next line node of the page / list
inline constexpr s32 kChainNext = 0x28;   // u32: the next line of the chain (the row helpers walk it)
inline constexpr s32 kChainFirst = 0x2C;  // u32: the chain's first line (a fresh node points at itself)
inline constexpr s32 kDirty = 0x40;       // u32
inline constexpr u32 kSize = 0x44;
inline constexpr s32 kRowSpan = 100;      // a row of a chain: the lines whose y is below the row's first y + 100
inline constexpr s32 kBlankCode = 0x20;   // frFontInitLineNode's code
inline constexpr s32 kOpaque = 255;
}  // namespace line_node

namespace glyph_node {
inline constexpr s32 kCode = 0x00;       // u16: the text code
inline constexpr s32 kOffsetX = 0x04;    // s32 (1/16 px)
inline constexpr s32 kOffsetY = 0x08;    // s32 (16 for descenders)
inline constexpr s32 kAdvance = 0x0C;    // s32
inline constexpr s32 kRgba = 0x10;       // u32: the colour word; the low byte is the alpha the text code set
inline constexpr s32 kColourSet = 0x14;  // u8: colour / raster set (itfMesMngTextSetLineAlpha writes it)
inline constexpr s32 kStyle = 0x15;      // u8
inline constexpr s32 kMode = 0x16;       // u8: 2 = fading
inline constexpr s32 kFlags = 0x17;      // u8: bit 0 proportional, bit 4 descender
inline constexpr s32 kNext = 0x28;       // u32
inline constexpr u32 kSize = 0x2C;
}  // namespace glyph_node

// =====================================================================================================================
// itfPanel.c (msg2.cpp): the panels, their per-type work buffers and the open / close animations
// =====================================================================================================================

// --- an itfPnl panel (80 bytes, itfPnlRegist2) -----------------------------------------------------------------------
namespace pnl {
inline constexpr s32 kWork = 8;     // u32: the per-type work buffer (vertices, then colours; pnl_anim:: for 10-13)
inline constexpr s32 kZ = 12;
inline constexpr s32 kX0 = 16, kY0 = 20, kX1 = 24, kY1 = 28;  // s32, 12.4 fixed point
inline constexpr s32 kType = 60;    // u8
inline constexpr s32 kPhase0 = 64;  // u32: the phase callbacks 0..3 (types 10-13; itfPnlRunPhase0..3)
inline constexpr s32 kPhase1 = 68;
inline constexpr s32 kPhase2 = 72;
inline constexpr s32 kPhase3 = 76;
inline constexpr u32 kSize = 80;
}  // namespace pnl

// --- the animation work record of panel types 10-13 (16 bytes at pnl::kWork) ----------------------------------------
namespace pnl_anim {
inline constexpr s32 kPhase = 0;   // s32: 0 closed, 1 opening, 2 open, 3 closing
inline constexpr s32 kScale = 4;   // s32: 100 -> 0 while opening (types 10, 11) [proposed: the zoom-in percentage]
inline constexpr s32 kFrame = 8;   // s32: frames into the phase
inline constexpr s32 kAlpha = 12;  // s32: 0..255
inline constexpr s32 kClosed = 0, kOpening = 1, kOpen = 2, kClosing = 3;
inline constexpr s32 kOpaque = 255;
inline constexpr s32 kFullScale = 100;
}  // namespace pnl_anim

// --- the per-type work buffers the vertex / colour setters fill (msg2.h; off_6A1C10 / off_6A1C50) --------------------
// Vertices are {s32 x, s32 y} pairs (12.4 fixed point: 512 = 32 px) from +0 (type 8: from +4); the colour block follows
// the last vertex. Colours are {r, g, b, a} words; the shaded ones come from sub_3B4A90(dst, r, g, b, a, factors, n).
namespace pnl_buf {
inline constexpr s32 kVertexSize = 8;     // {x, y}
inline constexpr s32 kQuadEdgeSize = 16;  // {x, y0, x, y1}: one column of a type 0 / 8 panel
inline constexpr s32 kGridSize = 4;       // types 1 and 2: a 4 x 4 grid of vertices
inline constexpr s32 kCorner = 512;       // the corner size of types 0 / 1 / 2 (32 px)
inline constexpr s32 kOuterX = 256, kOuterY = 128;  // types 1 / 2: the grid sticks out this far past the rectangle
inline constexpr s32 kBandX = 1024;       // types 1 / 2: the inset of the top and bottom bands
inline constexpr s32 kType5Notch = 1440;  // type 5: the third column, x1 - 1440
inline constexpr s32 kType2BandStep = 8;  // type 2: band rows 8 apart
inline constexpr s32 kType0Colour = 64;   // {r, g, b, 0} {r, g, b, a}
inline constexpr s32 kType1Colour = 320;  // {r, g, b, 1} {r, g, b, a}, then 6 shaded colours
inline constexpr s32 kType2Colour = 256;  // {r, g, b, 1} {r, g, b, a}, then 4 shaded colours
inline constexpr s32 kType3Colour = 32;   // {r, g, b, a}, one shaded colour, two shaded colours at alpha 128
inline constexpr s32 kType4Colour = 32;   // {r, g, b, a}
inline constexpr s32 kType5Colour = 48;   // {r, g, b, 0} {r, g, b, a}
inline constexpr s32 kType8Vertices = 4;
inline constexpr s32 kType8Colour = 68;   // {115, 135, 255, 0} twice
inline constexpr s32 kShadesAfter = 32;   // the shaded colours start 32 bytes after the colour block (types 1 / 2)
inline constexpr u32 kType1Shades = 0x6A1E00u;   // sub_3B4A90 factor tables: 6 colours
inline constexpr u32 kType2Shades = 0x6A1E60u;   // 4 colours
inline constexpr u32 kType3ShadeA = 0x6A1EA0u;   // 1 colour
inline constexpr u32 kType3ShadeB = 0x6A1EB0u;   // 2 colours (alpha 128)
inline constexpr s32 kType3ShadeAlpha = 128;
inline constexpr s32 kType8R = 115, kType8G = 135, kType8B = 255;
inline constexpr s32 kType8Columns[4] = {416, 1152, 7024, 7760};
inline constexpr s32 kType8Top = 352, kType8Bottom = 320;  // rows y0 + 352 and y1 - 320
}  // namespace pnl_buf

// =====================================================================================================================
// frFont.c / frFontEx.c / frFontRaster.c / fmGslCont.c (font.cpp)
// =====================================================================================================================

// --- a font style (32 bytes at font::kStyles + 32 * style; font.h kStyle*) and its .FNT header -----------------------
namespace fnt_style {
inline constexpr s32 kFnt = 0x04;         // u32: the .FNT image
inline constexpr s32 kWidthBytes = 0x08;  // u32: bytes of the {left, right} width table (2 per glyph)
inline constexpr s32 kWidthTable = 0x10;  // u32: s8[count][2] {left, right}
inline constexpr s32 kHuffman = 0x1C;     // the Huffman block
inline constexpr u32 kSize = font::kStyleStride;  // 32
}  // namespace fnt_style
namespace fnt_hdr {
inline constexpr s32 kGlyphCount = 0x0E;   // u16
inline constexpr s32 kGlyphWidth = 0x10;   // u16
inline constexpr s32 kGlyphHeight = 0x12;  // u16
inline constexpr s32 kHasWidths = 0x16;    // u8: 1 = the width table is present
}  // namespace fnt_hdr

// --- the text codes the metrics and kerning rules test ----------------------------------------------------------------
namespace text_code {
inline constexpr s32 kNewline = 10;
inline constexpr s32 kSpace = 0x20;
inline constexpr s32 kExclam = 33;   // '!': drawn 4 wider, shifted 2 px left (frFontSetGlyphMetrics)
inline constexpr s32 kOne = 49;      // '1': likewise
inline constexpr s32 kTwoByte = 0x80;  // codes >= 0x80 are two-byte glyphs (lead byte, then one more)
inline constexpr s32 kTagLead = 0xF0;  // a lead byte 0xFn starts a tag: n - 1 parameter words follow its second byte
// kerning: a / e / o / u (or their two-byte forms 80C1 / 80C5 / 80CF / 80D5) before T / 80B4 or Y / 80B9
inline constexpr s32 kA = 97, kE = 101, kO = 111, kU = 117;
inline constexpr s32 kA2 = 0x80C1, kE2 = 0x80C5, kO2 = 0x80CF, kU2 = 0x80D5;
inline constexpr s32 kT = 84, kT2 = 0x80B4, kY = 89, kY2 = 0x80B9;
// tags that end a scan (frFontProcessTagEx)
inline constexpr s32 kTagEnd31 = 0xF131, kTagEnd10 = 0xF110, kTagEnd04 = 0xF104;
}  // namespace text_code

// --- fmGslCont.c: the glyph block header, the GS-list entries -------------------------------------------------------
namespace gsl_blocks {
inline constexpr s32 kDictOffset = 0;    // u32[8] header: [0] dictionary offset
inline constexpr s32 kDictBytes = 4;     // [1] dictionary bytes
inline constexpr s32 kOffsetsBytes = 24; // [6] offsets-block bytes
inline constexpr s32 kOutDict = 0, kOutOffsets = 4, kOutStream = 8;  // fmGslGetGlyphBlocks' {dict, offsets, stream}
inline constexpr s32 kNodeSize = 6;      // dictionary node {u16, u16 child0, u16 child1}; child0 == 0: a leaf
inline constexpr s32 kNodeChild0 = 2;    // the leaf's symbol is the byte at +4
inline constexpr u32 kSentinel = 0x10000u;  // the stream register's sentinel bit above a 16-bit word
}  // namespace gsl_blocks
namespace gsl_entry {
inline constexpr s32 kWord0 = 0x00;  // non-zero for a real entry (the container's own +0 is 0)
inline constexpr s32 kPrev = 0x18;   // circular, doubly linked through the container
inline constexpr s32 kNext = 0x1C;
}  // namespace gsl_entry

// --- the ring buffers (rbInitRingBuf): records {u32, u32 next, payload} ---------------------------------------------
namespace ring {
inline constexpr s32 kHead = 4;     // the ring's free head (a record)
inline constexpr s32 kWord0 = 0;    // a record's +0: non-zero for a real record (the ring's end has 0)
inline constexpr s32 kNext = 4;     // a record's link; 0 while it is handed out
inline constexpr s32 kPayload = 8;  // rbAlloc returns record + 8
}  // namespace ring

// --- the raster-slot cache (manager at *font::kRasterSlots; frFontRaster.c) -----------------------------------------
namespace raster_mgr {
inline constexpr s32 kActive = 0x08;      // u32: the first slot in use
inline constexpr s32 kActiveTail = 0x0C;  // u32
inline constexpr s32 kFree = 0x10;        // u32: the free list's head
inline constexpr s32 kFreeTail = 0x14;    // u32
}  // namespace raster_mgr
namespace raster_slot {
inline constexpr s32 kFlags = 0x00;      // u32: bit 0 used this frame
inline constexpr s32 kGlyph = 0x04;      // u32: the glyph index it holds
inline constexpr s32 kColourSet = 0x08;  // s16
inline constexpr s32 kTicks = 0x0A;      // s16: frames left; negative -> back to the free list
inline constexpr s32 kGsEntry = 0x10;    // u32: its GS-list entry
inline constexpr s32 kNext = 0x18;       // u32
inline constexpr u32 kFlagUsed = 0x1u;
}  // namespace raster_slot

// --- the tag scan / layout record (32 bytes; frFontProcessTag builds one in its frame) -------------------------------
namespace tag_scan {
inline constexpr s32 kX = 0x00;        // s32 (cleared)
inline constexpr s32 kY = 0x04;        // s32: frFontLayoutNewRow adds the line spacing * 8
inline constexpr s32 kText = 0x10;     // u32: the text being scanned
inline constexpr s32 kWindow = 0x14;   // u32: the window the tags act on (tag_window::)
inline constexpr s32 kOffset = 0x18;   // u32: the scan position in the text
inline constexpr s32 kNewRowA = 0x1C;  // u8: 1 after a new row (and initially)
inline constexpr s32 kNewRowB = 0x1D;  // u8: likewise
inline constexpr s32 kHalf1E = 0x1E;   // s16: 32 initially
inline constexpr u32 kSize = 32;
}  // namespace tag_scan
namespace tag_window {
inline constexpr s32 kWaitTag = 48;  // u32: the code of the tag that set the wait
inline constexpr s32 kWord52 = 52;   // u32: when non-zero a wait tag also sets +56
inline constexpr s32 kWord56 = 56;   // u32: = 1
inline constexpr s32 kWait = 60;     // s32: the wait in ticks (a negative parameter clamps to 0)
}  // namespace tag_window
namespace tag_flags {
inline constexpr u32 kWaitIfFlag = 0x40u;  // frFontTagWaitIfFlag389 (tag 0x47)
inline constexpr u32 kWait = 0x80u;        // frFontTagWait (tag 0x46)
inline constexpr s32 kScanClear = -64;     // ~0x3F: the low 6 bits are cleared per scan
inline constexpr s32 kFlag389 = 389;       // the global flag tag 0x47 tests (datGetFlag)
}  // namespace tag_flags

// --- g_data.c -------------------------------------------------------------------------------------------------------
inline constexpr u32 kGlobalWork = 0x836200u;  // gGlobalWork: the g_data.c record (ui2:: names the fields read here)
// The offset of a g_data.c field from gGlobalWork, as the loops that index from kGlobalWork write it.
constexpr s32 gw_off(u32 va) noexcept { return static_cast<s32>(va - kGlobalWork); }
static_assert(gw_off(ui2::kCounters) == 17116 && gw_off(ui2::kFlagWords) == 16412);
// The three social stats, s16 each, of a character record (ui2::kProtagonistStats for character 1, the protagonist;
// ui2::kCharacterStats + 868 * character for the others).
namespace social {
inline constexpr s32 kAcademic = 0;
inline constexpr s32 kCharm = 2;
inline constexpr s32 kCourage = 4;
inline constexpr s32 kPointLimit = 1000;  // the setters K_Assert 0 <= points < 1000 (and store anyway)
}  // namespace social

// --- event/itemtbl.bin (ui2.h kItemTbl*; 20_menu_ui.md section 6) ---------------------------------------------------
namespace itemtbl {
inline constexpr s32 kCount = 0;           // u32: a section header's record count (the header is 16 bytes)
inline constexpr s32 kHeaderSize = 16;
inline constexpr s32 kTailRecordSize = 32; // the 35 records after the 14th header
}  // namespace itemtbl

// --- the calendar ---------------------------------------------------------------------------------------------------
inline constexpr u32 kWeekdayJumpTable = 0x7B6460u;  // datSetDaysSinceApr5's switch on the weekday (0 = Sunday .. 6)

}  // namespace p3fes::game::tview
