// Font renderer leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md section 5.2-5.3):
// the .FNT Huffman glyph decoder of fmGslCont.c, the glyph-node constructor with the text-code -> glyph
// index rule, the proportional metrics and pair kerning, the line-node/row helpers that measure and move
// message lines, the raster-slot cache lookup and ageing, the ring buffers and GS-list entries, and the
// sFrTagTable scanner with the tag handlers that only change render state (parameters, wait counter).
//
// Names: the IDA names of symbols/functions.json (the symbols/deltas/font.sym names since IDA master
// update #4). The trailing comment gives the function's address.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace font {

// --- globals ($gp = 0x7D2CF0) -------------------------------------------------------------------------
inline constexpr u32 kTagFlags = 0x7CD4E8u;        // gp-0x5808 u32: bits set by the tag handlers (0x80 wait, 0x40 wait-if-flag 389), low 6 cleared per scan
inline constexpr u32 kLineSpacing = 0x7CD4F0u;     // gp-0x5800 s32: row step in 1/8 px units (default 25)
inline constexpr u32 kStyleSizes = 0x7CD4F8u;      // gp-0x57F8 s8[9]: glyph size per style (32 = 1:1)
inline constexpr u32 kDefaultGlyphFlags = 0x7CD500u;  // gp-0x57F0 s16: flags OR-ed into every new glyph node (+0x17)
inline constexpr u32 kScaleX = 0x7CE638u;          // gp-0x46B8 s32: x scale /128 (<= 0: off)
inline constexpr u32 kScaleY = 0x7CE63Cu;          // gp-0x46B4 s32: y scale /128 (<= 0: off)
inline constexpr u32 kRasterSlots = 0x7CE644u;     // gp-0x46AC: the raster-slot manager (+8 active list, +0xC its tail, +0x10/+0x14 free list head/tail)
inline constexpr u32 kLastDecodedBytes = 0x7CE650u;  // gp-0x46A0 s32: byte count of the last fmGslDecodeGlyph

inline constexpr u32 kTagParams = 0x95ABE0u;       // u32[4]: the two parameter pairs of tags 0x42 / 0x43 (frFontTagSetParams01 / frFontTagSetParams23)
inline constexpr u32 kTagSlotTable = 0x95AC70u;    // u32[]: frFontSetTagSlot stores here
inline constexpr u32 kStyles = 0x95ACF0u;          // FrFontStyle[9], 32 bytes each (frAddFontStyle)
inline constexpr u32 kStyleStride = 0x20u;
inline constexpr u32 kGlyphCreatedCount = 0x95AE14u;  // s32: frFontCreateGlyphNode calls
inline constexpr u32 kGlyphRing = 0x95AE1Cu;       // ring buffer of 0x2C-byte glyph nodes (rbInitRingBuf(0x2C, 1024))
inline constexpr u32 kGslFreeCount = 0x95AEB8u;    // s32: free GS-list entries
inline constexpr u32 kGslList = 0x95AEBCu;         // the GS-list container (+0x1C first entry)
inline constexpr u32 kTagHandlers = 0x6A2370u;     // sFrTagTable: handler per tag code & 0xFF

inline constexpr u32 kFrFontFile = 0x6A2730u;      // "frFont.c" (K_Assert / K_Abort file argument)
inline constexpr u32 kTextOverflowMsg = 0x6A2860u; // "FONT SYS : Text buffer overflow error."
inline constexpr u32 kGslContFile = 0x6A2A18u;     // "fmGslCont.c"

// Style record (kStyles + 32 * style), filled by frAddFontStyle from the .FNT header.
inline constexpr u32 kStyleFnt = 0x04;           // .FNT image
inline constexpr u32 kStyleWidthBytes = 0x08;    // u32 size1: bytes of the {left, right} table (2 per glyph)
inline constexpr u32 kStyleWidthTable = 0x10;    // s8[count][2] {left, right}
inline constexpr u32 kStyleHuffman = 0x1C;       // the Huffman block

// .FNT header fields read here.
inline constexpr u32 kFntGlyphCount = 0x0E;      // u16
inline constexpr u32 kFntGlyphWidth = 0x10;      // u16
inline constexpr u32 kFntGlyphHeight = 0x12;     // u16
inline constexpr u32 kFntHasWidths = 0x16;       // u8: 1 = the width table is present

// Glyph-index constants of frFontCreateGlyphNode.
inline constexpr u32 kGlyphSpace = 0x1F7;        // ' ' maps to the wide blank glyph 503
inline constexpr u32 kGlyphReplacement = 0x147;  // index >= glyph count -> glyph 327

}  // namespace font

// Glyph node (0x2C bytes, from kGlyphRing): +0 u16 text code, +2 u16, +4 s32 x offset (1/16 px), +8 s32
// y offset (16 for descenders), +0xC s32 advance, +0x10 u32 rgba, +0x14 u8 colour/raster set, +0x15 u8
// style, +0x16 u8 mode (2 = fading), +0x17 u8 flags (bit 0 proportional, bit 4 descender), +0x18/+0x19 u8
// scaled sizes, +0x1C the GS-list entry of its raster (frFontCacheGlyph), +0x20..+0x27, +0x28 next glyph.
// Line node (0x44 bytes, frFontInitLineNode): +0 u16 code, +2 u8 alpha, +3 s8 letter spacing, +4 x, +8 y,
// +0xC glyph count, +0x1C first glyph, +0x24 next line (walked by the setters), +0x28 next line of the chain
// (walked by the row helpers), +0x2C the chain's first line (a fresh node points at itself), +0x40 dirty flag.
// A row of a chain: the run of lines whose y is below the row's first line's y + 100 (20_menu_ui.md 5.4).

// --- fmGslCont.c: Huffman glyph decoder, GS list, ring buffers (game/src/ui/font.cpp) ------------------
void fmGslGetGlyphBlocks(EEContext& ctx);  // [register ABI] 0x3B4770: {dict, offsets, stream}
void fmGslDecodeGlyph(EEContext& ctx);  // [register ABI] 0x3B47B0: bytes written
void fmGslAllocEntry_regs(EEContext& ctx);  // [register ABI] 0x3B4520: unlink the first free entry
void fmGslReleaseEntry(EEContext& ctx);  // [register ABI] 0x3B4580: relink; $v0 = new free count
void rbAlloc(EEContext& ctx);  // [register ABI] 0x3B46B0: pop, payload = record + 8
void rbFree(EEContext& ctx);  // [register ABI] 0x3B46F0: push back, 1 = done

// --- frFont.c: glyph nodes ---------------------------------------------------------------------------
void frFontSetGlyphMetrics(EEContext& ctx);  // [register ABI] 0x3B01D0
void frFontInitLineNode(EEContext& ctx);  // [register ABI] 0x3B05C0
u32 frFontCreateGlyphNode(EEContext& ctx, u32 code, u32 style, u32 colour, u32 mode);  // 0x3B0620
void frFontKerningAdjust(EEContext& ctx);  // [register ABI] 0x3B0840
void frFontLineSetAlpha(EEContext& ctx);  // [register ABI] frFontLineSetAlpha
void frFontNodeSetCode(EEContext& ctx);  // [register ABI] frFontNodeSetCode
void frFontLineResetAlpha(EEContext& ctx);  // [register ABI] frFontLineResetAlpha
void frFontLineSetStyle(EEContext& ctx);  // [register ABI] frFontLineSetStyle
void frFontLineSetPos(EEContext& ctx);  // [register ABI] frFontLineSetPos
void frFontLineSetColourSet(EEContext& ctx);  // [register ABI] frFontLineSetColourSet
void frFontLineSetRgba(EEContext& ctx);  // [register ABI] frFontLineSetRgba
void frFontSetDefaultGlyphFlags(EEContext& ctx);  // [register ABI] frFontSetDefaultGlyphFlags (returns the old flags)
void frFontClearDefaultGlyphFlags(EEContext& ctx);  // [register ABI] frFontClearDefaultGlyphFlags
void frFontLineFadeStep(EEContext& ctx);  // [register ABI] frFontLineFadeStep: 1 when a glyph faded
void frFontLineChainJoin(EEContext& ctx);  // [register ABI] frFontLineChainJoin
void frFontLineGetWidth(EEContext& ctx);  // [register ABI] frFontLineGetWidth (1/16 px)
void frFontGetStyleGlyphWidth(EEContext& ctx);  // [register ABI] 0x3B1A10
void frFontGetStyleGlyphHeight(EEContext& ctx);  // [register ABI] 0x3B1A40
void frFontResetLineSpacing(EEContext& ctx);                                                // frFontResetLineSpacing (25)
void frFontSetLineSpacing(EEContext& ctx, u32 spacing);                                   // frFontSetLineSpacing
void frFontChainCountLines(EEContext& ctx);  // [register ABI] frFontChainCountLines
void frFontChainGetRowWidth(EEContext& ctx);  // [register ABI] frFontChainGetRowWidth (1/16 px << 4)
void frFontChainGetRowPos(EEContext& ctx);  // [register ABI] frFontChainGetRowPos
void frFontChainMoveTo(EEContext& ctx);  // [register ABI] frFontChainMoveTo
void frFontChainCentreAt(EEContext& ctx);  // [register ABI] frFontChainCentreAt

// --- frFontEx.c: tag scan and tag handlers -------------------------------------------------------------
void frFontLayoutNewRow(EEContext& ctx);  // [register ABI] frFontLayoutNewRow
u32 frFontTestTagFlags(EEContext& ctx, u32 mask);                                       // frFontTestTagFlags
void frFontSetTagSlot(EEContext& ctx);  // [register ABI] frFontSetTagSlot
void frFontProcessTagEx(EEContext& ctx);  // [register ABI] 0x3B2A30
void frFontProcessTag(EEContext& ctx);  // [register ABI] frFontProcessTag
u32 frFontTagGetParam0(EEContext& ctx);                                                 // frFontTagGetParam0
u32 frFontTagGetParam1(EEContext& ctx);                                                 // frFontTagGetParam1
u32 frFontTagGetParam2(EEContext& ctx);                                                 // frFontTagGetParam2
u32 frFontTagGetParam3(EEContext& ctx);                                                 // frFontTagGetParam3
void frFontTagSetParams01(EEContext& ctx);  // [register ABI] frFontTagSetParams01 (tag 0x42)
void frFontTagSetParams23(EEContext& ctx);  // [register ABI] frFontTagSetParams23 (tag 0x43)
void frFontTagWait(EEContext& ctx);  // [register ABI] frFontTagWait (tag 0x46)
void frFontTagWaitIfFlag389(EEContext& ctx);  // [register ABI] frFontTagWaitIfFlag389 (tag 0x47)

// --- frFontRaster.c: the raster-slot cache --------------------------------------------------------------
void frFontGetStyleSize(EEContext& ctx);  // [register ABI] frFontGetStyleSize
void frFontRasterAgeSlots(EEContext& ctx);                                      // 0x3B3770
void frFontRasterFind(EEContext& ctx);  // [register ABI] 0x3B3DD0
void frFontRasterLookup(EEContext& ctx);  // [register ABI] frFontRasterLookup

}  // namespace p3fes::game
