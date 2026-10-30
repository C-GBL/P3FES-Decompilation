// Slice font2: the font renderer (frFont.c / frFontEx.c / frFontRaster.c / fmGslCont.c, 0x3AE000-0x3B4FC0) and the
// still-recompiled sprite / cursor band 0x100000-0x11FFFF (game/src/ui/font2.cpp; docs/ANALYSIS/20_menu_ui.md 4-5).
// Every function keeps the name symbols/functions.json gives it; a proposed name is given in [brackets] (and in
// symbols/deltas/font2.sym). Register ABI throughout: arguments in $a0.. ($f12.. for floats), the result in $v0.
//
// The font pipeline (obs from the instructions; 20_menu_ui.md 5.2-5.4 has the .FNT format):
//
//   text --(sub_3B2430 layout loop / sub_3B1D90 / sub_3B2020 inserted strings; the immediate draw sub_3B2F90)-->
//   frFontBuildGlyphList: one glyph node per character from the glyph ring, chained on a line node from the line ring
//     --> frFontCreateGlyphNode --> frFontCacheGlyph: (glyph, colour set) looked up in the raster slots;
//         hit  = the slot's cache record gains a reference;
//         miss = Huffman-decode the glyph (fmGslDecodeGlyph, 512 bytes, 4 bpp 32 x 32), take a slot from the free list
//                (frFontRasterAllocSlot: swizzle into its raster, load the colour set's CLUT -- frFontRasterCreate2),
//                and register a GS-list entry + cache record (frFontRegisterGlyphRaster) linked both ways with it.
//   frFontDraw walks the nodes (sub_3B0F50 reveals one glyph per call), sub_3B0030 releases a chain: a cache record
//   whose references drop to 0 frees its GS entry and clears the slot's in-use bit; frFontRasterAgeSlots (every frame)
//   returns aged, unused slots to the free list -- so a glyph drawn again soon is still a hit.
//
// Records (offsets in the namespaces below): line node 0x44 B, glyph node 0x2C B, glyph cache record 16 B (a GS-list
// entry's work), raster slot 28 B + its 512-byte buffer, the slot pool header 24 B, GS-list entry 32 B, style 32 B,
// layout record 48 B (ui4.h), sprite handle 0x34 B (ui4.h). Task callbacks get their kwlnTask in $a0 (work at +0x3C).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace font2 {
// the font system (frFont.c / frFontRaster.c / fmGslCont.c): lo parts of 0x960000 and gp offsets ($gp = 0x7D2CF0)
namespace fnt {
inline constexpr s32 kLoCluts = 8496;  // 0x6A2130: the 16-entry CLUT per colour set (64 bytes each)
inline constexpr s32 kLoTagTable = 9072;  // 0x6A2370: sFrTagTable: the text-tag handlers by code & 0xFF
inline constexpr s32 kLoVoiceThresholds = 9792;  // 0x6A2640: sub_3AE000: three thresholds
inline constexpr s32 kLoVoiceThresholds1 = 9796;  // 0x6A2644: sub_3AE000: threshold 2
inline constexpr s32 kLoVoiceThresholds2 = 9800;  // 0x6A2648: sub_3AE000: threshold 3
inline constexpr s32 kLoVoiceIds = 9808;  // 0x6A2650: sub_3AE000: three sound ids
inline constexpr s32 kLoVoiceIds1 = 9812;  // 0x6A2654: sub_3AE000: sound id 2
inline constexpr s32 kLoVoiceIds2 = 9816;  // 0x6A2658: sub_3AE000: sound id 3
inline constexpr s32 kLoCondBanks = 9824;  // 0x6A2660: sub_3AEE20: the five flag-bank bases
inline constexpr s32 kLoSetBanks = 9856;  // 0x6A2680: sub_3AF110: the five flag-bank bases
inline constexpr s32 kLoSwizzle = 10480;  // 0x6A28F0: the PSMT4 32 x 32 swizzle table (256 bytes)
inline constexpr s32 kLoPlateUv0 = 10792;  // 0x6A2A28: name-plate frame UVs, left cap
inline constexpr s32 kLoPlateUv1 = 10796;  // 0x6A2A2C: middle
inline constexpr s32 kLoPlateUv2 = 10800;  // 0x6A2A30: right cap
inline constexpr s32 kLoJptCondition = -20000;  // 0x7BB1E0: jump table of sub_3AEE20
inline constexpr s32 kGpTagFlags = -22536;  // 0x7CD4E8: u32: the tag flags (0x80 wait, 0x40 wait-if-flag, 0x20 condition true; low byte cleared per layout)
inline constexpr s32 kGpLetterSpacing = -22532;  // 0x7CD4EC: s32: letter spacing given to every new line (+3)
inline constexpr s32 kGpLineSpacing = -22528;  // 0x7CD4F0: s32: the row step (1/8 px; 25 by default)
inline constexpr s32 kGpStyleSizes = -22520;  // 0x7CD4F8: s8[9]: glyph size per style (32 = 1:1)
inline constexpr s32 kGpGlyphFlags = -22512;  // 0x7CD500: u16: default glyph flags (low two bits: 1 while a layout runs, 2 after; bit 2 newline rows; bit 7 tag writes allowed)
inline constexpr s32 kGpEmptyText = -22472;  // 0x7CD528: the empty string a new line node is started from
inline constexpr s32 kGpPlateRaster = -22468;  // 0x7CD52C: the name-plate frame raster word (sub_3B4D10)
inline constexpr s32 kGpScaleX = -18104;  // 0x7CE638: s32: glyph x scale / 128 (<= 0 off)
inline constexpr s32 kGpScaleY = -18100;  // 0x7CE63C: s32: glyph y scale / 128 (<= 0 off)
inline constexpr s32 kGpCurStyle = -18096;  // 0x7CE640: u8: the current style (frFontBuildGlyphList)
inline constexpr s32 kGpRasterSlots = -18092;  // 0x7CE644: the raster-slot pool header (frFontRasterCreate)
inline constexpr s32 kGpGsWidth = -18088;  // 0x7CE648: s32: GS width of the font area (16 * (width / 16))
inline constexpr s32 kGpGslReady = -18084;  // 0x7CE64C: u8: the GS-list container is set up
inline constexpr s32 kLoTagSlots = -21392;  // 0x95AC70: u32[32]: the strings of the inserted-text tags (frFontSetTagSlot)
inline constexpr s32 kLoStyles = -21264;  // 0x95ACF0: sFrFontStyles: the nine 32-byte style records
inline constexpr s32 kLoStyleHuffman = -21236;  // 0x95AD0C: style 0 +0x1C: the Huffman block word of sFrFontStyles (+32 * style; non-zero = the style has a font)
inline constexpr s32 kLoStyle1 = -21232;  // 0x95AD10: sFrFontStyles[1] (frLoadFontData copies style 0 here and to styles 2..5)
inline constexpr s32 kLoStyle2 = -21200;  // 0x95AD30: sFrFontStyles[2]
inline constexpr s32 kLoStyle3 = -21168;  // 0x95AD50: sFrFontStyles[3]
inline constexpr s32 kLoStyle4 = -21136;  // 0x95AD70: sFrFontStyles[4]
inline constexpr s32 kLoStyle5 = -21104;  // 0x95AD90: sFrFontStyles[5]
inline constexpr s32 kLoCachedGlyphs = -20976;  // 0x95AE10: s32: glyphs with a registered GS entry (frFontCacheGlyph +1, the chain release -1)
inline constexpr s32 kLoGlyphNodes = -20972;  // 0x95AE14: s32: glyph nodes taken from the glyph ring
inline constexpr s32 kLoLineNodes = -20968;  // 0x95AE18: s32: line nodes taken from the line ring
inline constexpr s32 kLoGlyphRing = -20964;  // 0x95AE1C: the glyph-node ring buffer (0x2C-byte nodes)
inline constexpr s32 kLoLineRing = -20960;  // 0x95AE20: the line-node ring buffer (0x44-byte nodes)
inline constexpr s32 kLoGlyphBytes = -20948;  // 0x95AE2C: s32: bytes of one decoded glyph (512)
inline constexpr s32 kLoGlyphBytesLog2 = -20944;  // 0x95AE30: s32: log2 of it (9)
inline constexpr s32 kLoGsRowPow2 = -20940;  // 0x95AE34: s32: 32 * (GS width / 16) rounded up to a power of two
inline constexpr s32 kLoGsRowLog2 = -20936;  // 0x95AE38: s32: log2 of it
inline constexpr s32 kLoGslArg0 = -20932;  // 0x95AE3C: the word handed to sub_3B41A0 as $a0 (not read there)
inline constexpr s32 kLoGlyphQwords64 = -20928;  // 0x95AE40: s32: glyph bytes / 64 (8)
inline constexpr s32 kLoStyleCdNodes = -20876;  // 0x95AE74: H_Cdvd request per style (style 0: font/font0.fnt), u32[9]
inline constexpr s32 kLoGslBlock0 = -20832;  // 0x95AEA0: GS-list block 0: the entries
inline constexpr s32 kLoGslBlock1 = -20828;  // 0x95AEA4: GS-list block 1: the per-entry work
inline constexpr s32 kLoGslEntryW = -20824;  // 0x95AEA8: s32: entry width (32)
inline constexpr s32 kLoGslEntryH = -20820;  // 0x95AEAC: s32: entry height (32)
inline constexpr s32 kLoGslEntryBytes = -20816;  // 0x95AEB0: s32: w * h / 2 (4-bit texels)
inline constexpr s32 kLoGslEntryCount = -20812;  // 0x95AEB4: s32: entries (cols * rows)
inline constexpr s32 kLoGslFreeCount = -20808;  // 0x95AEB8: s32: free entries
inline constexpr s32 kLoGslList = -20804;  // 0x95AEBC: the GS-list container (circular list of 32-byte entries)
}  // namespace fnt

// the RenderWare engine slots (lo parts of 0x960000)
namespace rw {
inline constexpr s32 kIm2DNearZ = 136;  // 0x960088: g_rwIm2DNearScreenZ: f32 the Im2D near screen z
inline constexpr s32 kIm2DFarZ = 140;  // 0x96008C: f32: the Im2D far screen z
inline constexpr s32 kRenderStateSet = 144;  // 0x960090: pfn_RwRenderStateSet: the RwRenderStateSet slot
inline constexpr s32 kMalloc = 376;  // 0x960178: the RwMalloc slot (RwEngineInstance memory functions)
inline constexpr s32 kFree = 380;  // 0x96017C: the RwFree slot
inline constexpr s32 kCalloc = 388;  // 0x960184: the RwCalloc slot
}  // namespace rw

// the pad layer (h_pad.c): gp offsets and lo parts of 0x7E0000
namespace pad {
inline constexpr s32 kGpVibState = -20064;  // 0x7CDE90: s16: vibration state (0 reset, 1 off, 2 pulsing)
inline constexpr s32 kGpVibValue = -20060;  // 0x7CDE94: u8: actuator value while on
inline constexpr s32 kGpVibOn = -20056;  // 0x7CDE98: s16: the pulse phase (1 on)
inline constexpr s32 kGpVibOffFrames = -20052;  // 0x7CDE9C: s16: frames off per pulse
inline constexpr s32 kGpVibOnFrames = -20048;  // 0x7CDEA0: s16: frames on per pulse
inline constexpr s32 kGpVibCounter = -20044;  // 0x7CDEA4: s16: frames left in the phase
inline constexpr s32 kGpVibPulses = -20040;  // 0x7CDEA8: s16: phases left
inline constexpr s32 kLoWorkBase = 2480;  // 0x7E09B0: the pad work pointer (54 bytes per port)
inline constexpr s32 kLoHeld = 2492;  // 0x7E09BC: pad record +0: u16 held buttons (port records 54 bytes apart)
inline constexpr s32 kLoPressed = 2494;  // 0x7E09BE: +2: u16 pressed this frame
inline constexpr s32 kLoPrevHeld = 2496;  // 0x7E09C0: +4: u16 held last frame
inline constexpr s32 kLoRepeat = 2498;  // 0x7E09C2: +6: u16 pressed or auto-repeated
inline constexpr s32 kLoStick = 2502;  // 0x7E09C6: +0xA: u16 held with the left stick as d-pad
inline constexpr s32 kLoStickPressed = 2504;  // 0x7E09C8: +0xC: u16 pressed (stick word)
inline constexpr s32 kLoStickRepeat = 2506;  // 0x7E09CA: +0xE: u16 pressed or auto-repeated (stick word)
inline constexpr s32 kLoStickPrev = 2508;  // 0x7E09CC: +0x10: u16 stick word last frame
inline constexpr s32 kLoStickX = 2510;  // 0x7E09CE: +0x12: u8 left stick x
inline constexpr s32 kLoStickY = 2511;  // 0x7E09CF: +0x13: u8 left stick y
inline constexpr s32 kLoRepeatCounters = 2514;  // 0x7E09D2: +0x16: u8[12] auto-repeat counters
inline constexpr s32 kLoActuator0 = 2526;  // 0x7E09DE: u16: small motor value
inline constexpr s32 kLoActuator1 = 2528;  // 0x7E09E0: u16: large motor value
inline constexpr s32 kLoEdge0 = 2546;  // 0x7E09F2: u16 frame-edge word cleared every frame
inline constexpr s32 kLoEdge1 = 2548;  // 0x7E09F4: u16 frame-edge word
inline constexpr s32 kLoEdge2 = 2552;  // 0x7E09F8: u16 frame-edge word
inline constexpr s32 kLoEdge3 = 2556;  // 0x7E09FC: u16 frame-edge word
inline constexpr s32 kLoEdge4 = 2558;  // 0x7E09FE: u16 frame-edge word
inline constexpr s32 kLoAnalog0 = 2564;  // 0x7E0A04: u8 analogue value, centred to 0x80 every frame
inline constexpr s32 kLoAnalog1 = 2565;  // 0x7E0A05: u8
inline constexpr s32 kLoAnalog2 = 2566;  // 0x7E0A06: u8
inline constexpr s32 kLoAnalog3 = 2567;  // 0x7E0A07: u8
}  // namespace pad

// the debug print layer and the memory checker hooks
namespace dbg {
inline constexpr s32 kGpPrintList = -20008;  // 0x7CDEC8: the queued debug strings (280-byte nodes linked by +0)
inline constexpr s32 kGpFontImage = -20004;  // 0x7CDECC: the debug font RW image while it is converted
inline constexpr s32 kGpFontRaster = -20000;  // 0x7CDED0: the debug font raster
inline constexpr s32 kLoMemHooks = 2592;  // 0x7E0A20: the memory checker hook table (four function pointers)
inline constexpr s32 kLoMemHookFree = 2596;  // 0x7E0A24: hook 1
inline constexpr s32 kLoMemHookCopy = 2600;  // 0x7E0A28: hook 2
inline constexpr s32 kLoMemHookClear = 2604;  // 0x7E0A2C: hook 3
inline constexpr s32 kLoScreen = 7728;  // 0x7E1E30: the 2,120-byte debug character screen
}  // namespace dbg

// the bust-up portraits (h_chrdsp.c): lo parts of 0x7E0000 (records 1,648 bytes apart)
namespace bust {
inline constexpr s32 kLoNameTable = 13136;  // 0x5D3350: off_5D3350: the bust-up file name table
inline constexpr s32 kLoRecords = 9856;  // 0x7E2680: the three 1,648-byte bust-up records
inline constexpr s32 kLoPose = 9858;  // 0x7E2682: record +2: s16 pose
inline constexpr s32 kLoChar = 9860;  // 0x7E2684: record +4: s16 character
inline constexpr s32 kLoCostume = 9864;  // 0x7E2688: record +8: s16 costume / pose argument
inline constexpr s32 kLoFace = 9866;  // 0x7E268A: record +0xA: s16 expression
inline constexpr s32 kLoPos = 9868;  // 0x7E268C: record +0xC: the 64-bit position
inline constexpr s32 kLoR = 11168;  // 0x7E2BA0: record +0x520: u8 r
inline constexpr s32 kLoG = 11169;  // 0x7E2BA1: record +0x521: u8 g
inline constexpr s32 kLoB = 11170;  // 0x7E2BA2: record +0x522: u8 b
inline constexpr s32 kLoA = 11171;  // 0x7E2BA3: record +0x523: u8 alpha
inline constexpr s32 kLoCdNode = 11176;  // 0x7E2BA8: record +0x528: the file request
inline constexpr s32 kLoScaleX = 11180;  // 0x7E2BAC: record +0x52C: f32 x scale
inline constexpr s32 kLoScaleY = 11184;  // 0x7E2BB0: record +0x530: f32 y scale
inline constexpr s32 kLoResReq = 11208;  // 0x7E2BC8: record +0x548: the resource-manager request
inline constexpr s32 kLoWord54C = 11212;  // 0x7E2BCC: record +0x54C
inline constexpr s32 kLoFade = 11216;  // 0x7E2BD0: record +0x550: the fade word
inline constexpr s32 kLoFlip = 11220;  // 0x7E2BD4: record +0x554
inline constexpr s32 kLoFadeOn = 11224;  // 0x7E2BD8: record +0x558
inline constexpr s32 kLoFadeStep = 11228;  // 0x7E2BDC: record +0x55C
inline constexpr s32 kLoFadeFrame = 11232;  // 0x7E2BE0: record +0x560
inline constexpr s32 kLoWord564 = 11236;  // 0x7E2BE4: record +0x564
}  // namespace bust

// the fade layer (h_fade.c)
namespace fade {
inline constexpr s32 kLoDrawTable = 20928;  // 0x7B51C0: jump table of sub_107060
inline constexpr s32 kGpActive = -19996;  // 0x7CDED4: s32: a fade is running
inline constexpr s32 kGpB = -19968;  // 0x7CDEF0: u8: fade colour b
inline constexpr s32 kGpG = -19964;  // 0x7CDEF4: u8: fade colour g
inline constexpr s32 kGpR = -19960;  // 0x7CDEF8: u8: fade colour r
inline constexpr s32 kGpType = -19944;  // 0x7CDF08: s16: fade type (the draw table 0x7B51C0)
}  // namespace fade

// the sound channel records (h_snd.c)
namespace snd {
inline constexpr s32 kLoChannels = 17456;  // 0x7E4430: the sound channel records (77 words each; +0 active)
inline constexpr s32 kLoBgmId = 17464;  // 0x7E4438: channel 0 +8: s16 the BGM id
inline constexpr s32 kLoChannelStream = 17472;  // 0x7E4440: channel +0x10: the ADX stream
}  // namespace snd

// the sprite layer
namespace spr {
inline constexpr s32 kGpHandleList = -19892;  // 0x7CDF3C: gp-0x4DB4: the persistent sprite handle list
inline constexpr s32 kLoFontFiles = 14912;  // 0x833A40: sSprFontFiles[3]: the three sprite fonts
inline constexpr s32 kLoFontFile1 = 14916;  // 0x833A44: sSprFontFiles[1] (0x833A40 + 4)
inline constexpr s32 kLoFontFile2 = 14920;  // 0x833A48: sSprFontFiles[2]
// sprite draw handle (0x34 bytes, sprCreateHandle; ui4.h SprHandle)
inline constexpr s32 kNext = 0;  // next handle
inline constexpr s32 kPrev = 4;  // previous handle (0: the list head gp-0x4DB4)
inline constexpr s32 kX = 16;  // f32 x
inline constexpr s32 kY = 20;  // f32 y
inline constexpr s32 kFlags = 24;  // u8 flags
inline constexpr s32 kXOffset = 32;  // f32 x offset
inline constexpr s32 kW = 36;  // s16 width override
inline constexpr s32 kH = 38;  // s16 height override
inline constexpr s32 kScaleX = 40;  // s16 12.4 x scale
inline constexpr s32 kScaleY = 42;  // s16 12.4 y scale
inline constexpr s32 kZ = 44;  // f32 z
inline constexpr s32 kR = 48;  // u8 r
inline constexpr s32 kG = 49;  // u8 g
inline constexpr s32 kB = 50;  // u8 b
}  // namespace spr

// the cut-ins and the persona effects (h_cutin.c, h_perefect*.c)
namespace fx {
inline constexpr s32 kLoCutInVoices = 21472;  // 0x5D53E0: 6-byte records {ids[4], voice[2]} of the cut-in voices
inline constexpr s32 kLoJptCutInPlayer = 21264;  // 0x7B5310: jump table of sub_1107D0
inline constexpr s32 kLoJptPerEfect0 = 21344;  // 0x7B5360: jump table of sub_115F00
inline constexpr s32 kLoJptPerEfect1c = 21376;  // 0x7B5380: jump table of sub_1167F0
inline constexpr s32 kLoJptPerEfect1b = 21424;  // 0x7B53B0: jump table of sub_1167F0
inline constexpr s32 kLoJptPerEfect1a = 21472;  // 0x7B53E0: jump table of sub_1167F0
inline constexpr s32 kLoJptPerEfect2 = 21504;  // 0x7B5400: jump table of sub_117540
inline constexpr s32 kGpPerEfect2Float = -32184;  // 0x7CAF38: f32 constant of sub_117540
inline constexpr s32 kGpCutInFloat0 = -31996;  // 0x7CAFF4: f32 constant of the cut-in draws
inline constexpr s32 kGpCutInFloat1 = -31992;  // 0x7CAFF8: f32 constant of the cut-in draws
inline constexpr s32 kGpCutInFmt = -30600;  // 0x7CB568: the printf format of the cut-in texture request
}  // namespace fx

// kwlnTask (the fields these bodies read)
namespace task {
inline constexpr s32 kWork = 60;  // +0x3C: the task's work block
}  // namespace task

// frFont line node (0x44 bytes, the line ring; frFontInitLineNode). Note: font.h calls +0xC the glyph count;
// frFontBuildGlyphList adds each advance there (the width, 1/16 px) and counts glyphs in +0x18
namespace line {
inline constexpr s32 kCode = 0;  // u16: the line code (layout +0x1E)
inline constexpr s32 kAlpha = 2;  // u8: alpha
inline constexpr s32 kSpacing = 3;  // s8: letter spacing added to every advance
inline constexpr s32 kX = 4;  // s32: x (1/16 px)
inline constexpr s32 kY = 8;  // s32: y (1/8 px)
inline constexpr s32 kWidth = 12;  // s32: summed advances (1/16 px)
inline constexpr s32 kSizeW = 16;  // u16: the last glyph's scaled width
inline constexpr s32 kSizeH = 18;  // u16: the last glyph's scaled height
inline constexpr s32 kZ = 20;  // the z word (f32 in sub_3B2F90; layout +8 >> 4 in sub_3B2430)
inline constexpr s32 kCount = 24;  // s32: glyph count
inline constexpr s32 kFirstGlyph = 28;  // the first glyph node
inline constexpr s32 kLastGlyph = 32;  // the last glyph node
inline constexpr s32 kNext = 36;  // the next line (the setters' walk)
inline constexpr s32 kChainNext = 40;  // the next line of the chain (the row helpers' walk)
inline constexpr s32 kChainHead = 44;  // the chain's first line
inline constexpr s32 kWaitCode = 48;  // the wait tag's code (F214 / F215 / F246 / F247)
inline constexpr s32 kWaitArmed = 52;  // a pending window tag code (F117)
inline constexpr s32 kWaitFlag = 56;  // set when a wait arrives while one is armed
inline constexpr s32 kWaitTicks = 60;  // s32: ticks to wait (-1: until the voice ends; 0xFFFF in the F117 form)
inline constexpr s32 kDirty = 64;  // non-zero: skip the wait checks
}  // namespace line

// frFont glyph node (0x2C bytes, the glyph ring; frFontCreateGlyphNode)
namespace glyph {
inline constexpr s32 kCode = 0;  // u16: text code
inline constexpr s32 kCode2 = 2;  // u16: second code word (the mode-1 jitter seed)
inline constexpr s32 kXOff = 4;  // s32: x offset (1/16 px)
inline constexpr s32 kYOff = 8;  // s32: y offset (16 for descenders)
inline constexpr s32 kAdvance = 12;  // s32: advance (1/16 px)
inline constexpr s32 kRgba = 16;  // u32: colour, alpha in the low byte
inline constexpr s32 kColourSet = 20;  // u8: colour set (the raster slot key with the glyph index)
inline constexpr s32 kStyle = 21;  // u8: style
inline constexpr s32 kMode = 22;  // u8: mode (1 jitter, 2 fading)
inline constexpr s32 kFlags = 23;  // u8: flags (bit 0 proportional, bit 4 descender)
inline constexpr s32 kSizeW = 24;  // u8: scaled width
inline constexpr s32 kSizeH = 25;  // u8: scaled height
inline constexpr s32 kCache = 28;  // the glyph cache record (what frFontCacheGlyph returns)
inline constexpr s32 kNoCache = 32;  // non-zero: the glyph holds no cache reference
inline constexpr s32 kPrev = 36;  // the previous glyph
inline constexpr s32 kNext = 40;  // the next glyph
}  // namespace glyph

// glyph cache record (a GS-list entry's 16-byte work, frFontRegisterGlyphRaster)
namespace cache {
inline constexpr s32 kGlyph = 0;  // u16: the glyph index
inline constexpr s32 kRefs = 4;  // u16: glyph nodes using it
inline constexpr s32 kEntry = 8;  // its GS-list entry
inline constexpr s32 kSlot = 12;  // its raster slot
}  // namespace cache

// raster slot (28 bytes + the 512-byte glyph buffer; frFontRasterCreate)
namespace slot {
inline constexpr s32 kFlags = 0;  // u32: bit 0 in use
inline constexpr s32 kGlyph = 4;  // the glyph index
inline constexpr s32 kColourSet = 8;  // s16: colour set of the palette loaded
inline constexpr s32 kTicks = 10;  // s16: age ticks
inline constexpr s32 kBuffer = 12;  // the 512-byte glyph buffer (right behind the slot)
inline constexpr s32 kCache = 16;  // the glyph cache record using it (0: none)
inline constexpr s32 kRaster = 20;  // its 32 x 32 4-bit RwRaster
inline constexpr s32 kNext = 24;  // next slot (active or free list)
}  // namespace slot

// raster-slot pool header (24 bytes at gp-0x46AC)
namespace pool {
inline constexpr s32 kCount = 0;  // s32: slots
inline constexpr s32 kSlots = 4;  // the first slot (header + 24)
inline constexpr s32 kActiveHead = 8;  // active list head
inline constexpr s32 kActiveTail = 12;  // active list tail
inline constexpr s32 kFreeHead = 16;  // free list head
inline constexpr s32 kFreeTail = 20;  // free list tail
}  // namespace pool

// GS-list entry (32 bytes; fmGslCont.c)
namespace gsl {
inline constexpr s32 kIndex = 0;  // s32: entry index
inline constexpr s32 kX0 = 4;  // s32: GS x0 (1/16 px)
inline constexpr s32 kY0 = 8;  // s32: GS y0
inline constexpr s32 kX1 = 12;  // s32: GS x1
inline constexpr s32 kY1 = 16;  // s32: GS y1
inline constexpr s32 kWork = 20;  // its work record (the glyph cache record)
inline constexpr s32 kPrev = 24;  // previous entry
inline constexpr s32 kNext = 28;  // next entry
}  // namespace gsl

// font style record (32 bytes, sFrFontStyles 0x95ACF0 + 32 * style; frAddFontStyle)
namespace style {
inline constexpr s32 kOwner = 0;  // the file data the style owns (frAddFontStyle's third argument; 0 for an image bound by pointer)
inline constexpr s32 kFnt = 4;  // the .FNT image
inline constexpr s32 kWidthBytes = 8;  // bytes of the width table
inline constexpr s32 kBlock2Bytes = 12;  // bytes of block 2
inline constexpr s32 kWidths = 16;  // s8[count][2] {left, right}
inline constexpr s32 kBlock2 = 20;  // block 2
inline constexpr s32 kGlyphTable = 24;  // u32[count] (zeros in the files)
inline constexpr s32 kHuffman = 28;  // the Huffman block (non-zero = bound)
}  // namespace style

// .FNT header fields read here (docs/ANALYSIS/20_menu_ui.md 5.3)
namespace fnthdr {
inline constexpr s32 kHeaderSize = 0;  // u32: header size (0x20)
inline constexpr s32 kClutBlocks = 10;  // u8: CLUT blocks of 64 bytes
inline constexpr s32 kGlyphCount = 14;  // u16: glyph count
inline constexpr s32 kHasTables = 22;  // u8: 1 = the width table and block 2 follow the CLUT
}  // namespace fnthdr

// text layout record (48 bytes on sub_3B2990's frame; ui4.h FrTextLayout)
namespace lay {
inline constexpr s32 kX = 0;  // s32: x
inline constexpr s32 kY = 4;  // s32: y
inline constexpr s32 kZ16 = 8;  // 16 x the z word given to each line (ui4 lay::kColour)
inline constexpr s32 kStyle = 12;  // s8: style
inline constexpr s32 kColourSet = 13;  // s8: colour set
inline constexpr s32 kMode = 14;  // s8: glyph mode
inline constexpr s32 kAlpha = 15;  // u8: alpha
inline constexpr s32 kText = 16;  // the text
inline constexpr s32 kLine = 20;  // the current line node
inline constexpr s32 kPos = 24;  // read position
inline constexpr s32 kNewLine = 28;  // u8: start a new line before the next glyph
inline constexpr s32 kPosPending = 29;  // u8: the next line takes (x, y)
inline constexpr s32 kLineCode = 30;  // u16: code of each new line
}  // namespace lay

}  // namespace font2


// --- H_Cursor and the pad layer (h_cursor.c, h_pad.c) ---------------------------------------------------
// 0x100580 H_Cursor_DestroyDrawTask: Destroy callback of the "H CURSOR Draw" task: frees the task's 0x150-byte work
//   block (task +0x3C) through the RwFree slot 0x96017C. Returns RwFree's $v0.
void H_Cursor_DestroyDrawTask(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1007F0 nullsub_1: [dbgPrintFontLoaded] Empty in retail (a `jr $ra`): sub_1042E0 calls it right after the debug
//   font raster is built.
void nullsub_1(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x103580 sub_103580: [H_Pad_UpdateAll] The per-frame pad update (kwlnUpdate, kwlnRootUpdateTask): for both ports
//   H_Pad_UpdateWorkPad(pad work + 54 * port) and the derived button words (sub_103650); then clears the five
//   frame-edge words of the shared pad block (0x7E09F2..0x7E09FE), sets the four analogue bytes 0x7E0A04..0x7E0A07 to
//   the centre 0x80 and steps the vibration (sub_103B10).
void sub_103580(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x103650 sub_103650: [H_Pad_UpdateButtonWords] Derives one port's button words (54-byte pad record at 0x7E09BC + 54
//   * port): the stick word (+10) from the held word's d-pad nibble plus the left stick's bytes (+0x12 x, +0x13 y: >=
//   0xC1 right / down 0x2000 / 0x4000, < 0x40 left / up 0x8000 / 0x1000), the pressed edges (+2 = held & (held ^
//   previous), +0xC for the stick word), copies into the repeat words (+6, +0xE), then the auto-repeat of the four
//   directions (sub_103990) and of eight buttons (sub_1038D0; counter slots 4..11).
void sub_103650(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1038D0 sub_1038D0: [H_Pad_RepeatButton] Auto-repeat of one button of a port: a fresh press arms the counter byte
//   (pad record +0x16 + slot) with 7; while held it counts down and at 0 ORs the bit into the repeat word (+6) and
//   re-arms with 3.
void sub_1038D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x103990 sub_103990: [H_Pad_RepeatDirection] Auto-repeat of one direction: as sub_1038D0 for the held word (repeat
//   word +6), then the same rule again for the stick word (+0xC edges, +0xA held, repeat word +0xE) on the same
//   counter byte.
void sub_103990(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x103B10 sub_103B10: [H_Pad_UpdateVibration] The vibration state machine (0x7CDE90 s16 state): state 2 pulses the
//   two actuator words 0x7E09DE / 0x7E09E0 on and off (on value 0x7CDE94, phase flag 0x7CDE98, off / on frame counts
//   0x7CDE9C / 0x7CDEA0, the frame counter 0x7CDEA4, the pulse count 0x7CDEA8) until the pulses run out (state 1);
//   state 1 keeps the actuators off; state 0 resets everything and goes to 1.
void sub_103B10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x103CF0 sub_103CF0: Empty in retail (a `jr $ra`; the movie player sub_10A860 calls it).
void sub_103CF0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the debug print layer (h_dbgprt.c: dbgPrint*) ----------------------------------------------------------
// 0x1040F0 sub_1040F0: [H_ChkMem_GetHooks] Fills the four-entry hook table at 0x7E0A20 with sub_104140 / sub_104280 /
//   sub_103F50 / sub_104040 (the memory checker's allocate / free / copy / clear hooks) and returns its address
//   (kwlnInitRenderer).
void sub_1040F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1042E0 sub_1042E0: [dbgPrintInit] Loads the debug font "font/size12/f11_001.tmx" synchronously (H_Cdvd_Request +
//   ReadSync), reads it into an RW image (sub_4CCAC0), creates a 4-bit raster of its size (RwRasterCreate sub_4CE0F0,
//   format 0x4504), copies the image in (sub_4CDCE0), destroys the image and the request; then clears the 2,120-byte
//   character screen 0x7E1E30 to spaces and the queued-string list (0x7CDEC8).
void sub_1042E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1043B0 sub_1043B0: [dbgPrintClear] Per-frame reset of the debug print: the character screen to spaces, then frees
//   every queued string node of the list (0x7CDEC8, linked by +0) through RwFree.
void sub_1043B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x104EB0 sub_104EB0: [dbgPrintColourF] Queues a formatted debug string with a colour: RwCalloc(1, 280) a node,
//   vsprintf the format and the variadic arguments into +16, x (+4) and the f32 y (+8) from the first argument pair,
//   colour bytes +276..+279 from $a1, appended at the tail of the list 0x7CDEC8.
void sub_104EB0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x104FD0 sub_104FD0: [dbgPrintF] As sub_104EB0 with the colour white (0xFF in the four bytes +276..+279).
void sub_104FD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x105210 sub_105210: [dbgPrintScreenZ] Screen z for a debug quad: from the main camera's near / far planes (+0x84 /
//   +0x80 of g_kwlnMainCamera) and the Im2D z range (0x960088 near, 0x96008C far) interpolates $f12 into $f0 (an
//   R5900 ACC multiply-add).
void sub_105210(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the bust-up portraits (h_chrdsp.c) and the fade layer (h_fade.c) -----------------------------------------
// 0x105800 sub_105800: [H_ChrDsp_Init] Clears the three 1,648-byte bust-up records at 0x7E2680 (state, the request
//   and work words +0x550 / +0x554, the three raster words +20..+28).
void sub_105800(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1058A0 sub_1058A0: [H_ChrDsp_DrawAll] Draw task body (kwlnRootUpdateDrawBustupProcTask): the Im2D render states
//   (6,1) (7,2) (8,1) (11,6) (10,5) (9,1) (12,1) (2,4) through the RwRenderStateSet slot 0x960090, then the bust-up
//   draw sub_1059B0 on each of the three records.
void sub_1058A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106730 sub_106730: [H_ChrDsp_Release] Releases bust-up record `id`: prints "!!! RELEASE CHAR %d", drops its
//   resource request (sub_133D30 when +0x548 is set, else H_Cdvd_Destroy of +0x528), destroys its three rasters
//   (RwRasterDestroy sub_4D0F00) and clears the state.
void sub_106730(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106860 sub_106860: [H_ChrDsp_Request] Requests bust-up `id` (character, pose, expression): stores them, releases
//   the old one, builds "i_bust_%02d_%x%1d[a|b].tmx" (the summer / winter suffix from clndIsDateInRange(6/1..9/30),
//   the 29 file for character 9 when sub_17D800), looks it up in the name table off_5D3350 and turns it into
//   "bustup/i_b_..bin" (or the dummy), requests the file (H_Cdvd_Request) and resets colour 0xFFFFFFFF and the two
//   scales 1.0.
void sub_106860(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106E90 sub_106E90: [H_ChrDsp_SetAlpha] Bust-up record `id`: alpha byte (+0x523) = $a1.
void sub_106E90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106EC0 sub_106EC0: [H_ChrDsp_SetFade] Bust-up record `id`: the fade word (+0x550) = $a1; a non-zero value also
//   starts the fade (+0x558 = 1, +0x560 = 0, +0x55C = 2).
void sub_106EC0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106F30 sub_106F30: [H_ChrDsp_SetFlip] Bust-up record `id`: +0x554 = $a1.
void sub_106F30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106F60 sub_106F60: [H_ChrDsp_SetPose] Bust-up record `id`: a loaded record (state 3) goes to state 4; the pose
//   word (+2) = $a1.
void sub_106F60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106FB0 sub_106FB0: [H_ChrDsp_SetPos] Bust-up record `id`: the 64-bit position word (+0xC: x, y) = $a1.
void sub_106FB0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x106FF0 sub_106FF0: [H_ChrDsp_IsReady] Bust-up record `id` is loaded (state == 3).
void sub_106FF0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x107060 sub_107060: [H_Fade_DrawTask] The fade draw (kwlnRootUpdateEtcDrawTask): the Im2D render states, then
//   while a fade is active (0x7CDED4) the draw of its type (0x7CDF08, jump table 0x7B51C0: 0-2 / 4 sub_1071F0, 3 / 5
//   H_Fade_DrawBlue, 6 H_Fade_DrawWhite, 7 sub_107B20, 8 H_Fade_DrawColour).
void sub_107060(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x108680 sub_108680: [H_Fade_SetColour] The fade colour bytes: r 0x7CDEF8, g 0x7CDEF4, b 0x7CDEF0 = $a0, $a1, $a2.
void sub_108680(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the sound state leaves (h_snd.c) ------------------------------------------------------------------------
// 0x108E50 sub_108E50: [H_Snd_GetBgmId] The playing BGM: the s16 id 0x7E4438 while the BGM channel record 0x7E4430 is
//   active, else -1.
void sub_108E50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x109040 sub_109040: [H_Snd_PlayBgmFade] sub_1099D0(bgm, 1) (the BGM request with a fade); returns 1.
void sub_109040(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x109170 sub_109170: Returns 0 (K_Field_DestroyFieldRootTask; a stripped sound query).
void sub_109170(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1099A0 sub_1099A0: [H_Snd_GetBgmId2] Same body as sub_108E50: the s16 BGM id while channel 0 is active, else -1.
void sub_1099A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10A500 sub_10A500: [H_Snd_IsChannelBusy] Is sound channel `ch` (77-word records from 0x7E4430) still playing:
//   channels 0, 1 and 5 never; otherwise an active record whose ADX stream (+0x10) is not in state 3 (ADXT_GetStat,
//   expl_4 in the database). frFontDraw and the text-wait helpers poll channel 2 (the voice).
void sub_10A500(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10A6D0 sub_10A6D0: [H_Afs_DestroyTask] Destroy callback of "H_AfsSetProc": drops the work's file request (+0x20,
//   H_Cdvd_Destroy) and frees the work.
void sub_10A6D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the TMX texture loader (uttmx.c) ------------------------------------------------------------------------
// 0x10DD10 sub_10DD10: [uttmxCopyPixels32] TMX PSMCT32 pixels into a locked RW image (+4 width, +8 height, +0x10
//   stride, +0x14 pixels): RGB copied, alpha < 0x7F scaled by 255 / 128, else 0xFF.
void sub_10DD10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10DDC0 sub_10DDC0: [uttmxCopyPixels24] TMX PSMCT24 pixels: RGB copied, alpha 0xFF.
void sub_10DDC0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10DE40 sub_10DE40: [uttmxCopyPixels16] TMX PSMCT16 / 16S pixels: each 5-bit channel << 3, alpha 0xFF.
void sub_10DE40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10DEE0 sub_10DEE0: [uttmxCopyPixels4] TMX PSMT4 pixels: each byte split into two 4-bit indices, one byte each.
void sub_10DEE0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10DF60 sub_10DF60: [uttmxCopyPalette32] A TMX PSMCT32 palette into the image palette (+0x18, 1 << depth entries):
//   RGB copied, alpha < 0x7F scaled by 255 / 128 (rounded toward zero), else 0xFF.
void sub_10DF60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10E010 sub_10E010: [uttmxUnswizzlePalette8] For an 8-bit image swaps entries 8..15 and 16..23 of every 32-entry
//   block of the 256-entry palette (the PS2 CSM1 palette order).
void sub_10E010(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10E0D0 sub_10E0D0: [uttmxImageFromTmx] Builds an RW image from a TMX file in memory (header checked: 2, 0,
//   "TMX0"): depth from the pixel format (+0x16: 0x14 / 0x24 / 0x2C 4-bit, 0x13 / 0x1B 8-bit, 2 / 0xA 16, 1 24, 0 32;
//   16 and more become 32), RwImageCreate (sub_4CBE00) + allocate (sub_4CBF20), the palette (16-bit or 32-bit,
//   sub_10DF60, then sub_10E010) and the pixels through the copiers above. Returns the image or 0.
void sub_10E0D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10E500 sub_10E500: [uttmxImageRead] RW image reader callback: opens the file (RwStreamOpen sub_4C58A0), reads the
//   64-byte header and the rest into a RwMalloc'd buffer, sub_10E0D0, frees the buffer and closes the stream
//   (sub_4C5780).
void sub_10E500(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10E5F0 sub_10E5F0: [uttmxImageReadHeader] RW image header callback: opens the stream and returns $a0 (the stream
//   is not closed).
void sub_10E5F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the cut-in player (h_cutin.c: "H_CutInPlayer", "H_CutInDraw") ---------------------------------------------
// 0x10EC50 sub_10EC50: [H_CutInDraw_DrawDirect] Immediate draw of a cut-in's draw work (sub_1115E0): camera and world
//   set-up (RwCameraBeginUpdate-style calls sub_4AA390 / sub_4AA3D0 / sub_4A9F20 / sub_4AA410), z test / blend states
//   per +0x4E4, and in state 3 the per-layer keyframe draw of the 18-byte key records (colour clamps, the sprite /
//   mesh calls sub_4AC5F0 / sub_4AB1B0 / sub_4A62E0 ...).
void sub_10EC50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x10F6C0 sub_10F6C0: [H_CutInDraw_Update] Update of the "H_CutInDraw" task: the same camera / render-state set-up
//   and keyframe walk as sub_10EC50, run every frame unless +0x4E8 (pause) is set; advances the per-layer key
//   indices.
void sub_10F6C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1102E0 sub_1102E0: [H_CutInDraw_Destroy] Destroy callback of "H_CutInDraw": destroys the layer clumps (+0xA8..,
//   sub_4AC390) and atomics (+0x148.., sub_4A5540) of the +0x4E0 layers (" destroy error" on a failure), then frees
//   the work.
void sub_1102E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1103E0 sub_1103E0: [H_CutInDraw_Create] Creates the "H_CutInDraw" task under `parent` (priority $a1): RwCalloc(1,
//   0x4EC) work, kwlnTaskCreate(update sub_10F6C0, destroy sub_1102E0); key data +4 = $a2, layer count +0x4E0 = $a3.
void sub_1103E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1104B0 sub_1104B0: [H_CutInDraw_IsLoaded] The draw task's state >= 2.
void sub_1104B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1104D0 sub_1104D0: [H_CutInDraw_Start] State 2 (ready) -> 3 (playing); returns 1, else 0.
void sub_1104D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x110510 sub_110510: [H_CutInDraw_StepKeys] While playing (state 3): per layer advances the key index (+0x1E8 + 4 *
//   layer) past the -1 terminator (counting finished layers in +0x3E8); returns 0 at a -2 (wait) key, 1 when every
//   layer is through.
void sub_110510(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1105D0 sub_1105D0: [H_CutInDraw_SetRaster] Raster slot `i` (< 40) of the draw work (+0x328) = $a2; a non-null
//   raster gets its +0x50 low byte set to 2.
void sub_1105D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x110620 sub_110620: [H_CutInDraw_SetLayerColour] Layer `i` colour offsets: s16 r +0x3F0, g +0x440, b +0x490 (two
//   bytes per layer).
void sub_110620(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x110650 sub_110650: [H_CutInDraw_MapUv] Maps layer b's screen rectangle onto layer a's raster: reads both frames'
//   bounds (sub_4AC120), computes the four UVs from the raster size (448-line screen) and sets them (sub_4A6200).
void sub_110650(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1107D0 sub_1107D0: [H_CutInPlayer_Update] Update of "H_CutInPlayer" (jump table 0x7B5310): 0 request the .cpk
//   (when +0x310), 1 wait, 2 per archive entry either a texture through the resource manager (sub_10C1A0, "h_cutin.c"
//   1286) or the key file (42-byte header to +0xCC, key count by -1 / -2 markers), 4 collect the texture
//   (sub_10C3A0), 6 create the draw task (H_CutInDraw inline, priority +0x30C or 5286) and hand it rasters / colours,
//   7 start it and fire the cut-in voice of the table 0x5D53E0 (sub_10A4E0), 8 count frames until +0xB8; returns -1
//   when done.
void sub_1107D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x110E70 sub_110E70: [H_CutInPlayer_Destroy] Destroy callback of "H_CutInPlayer": drops the pending texture
//   (sub_133D30) or the .cpk request, destroys the 40 rasters, prints "*** CUTIN RELEASE %s" and frees the work.
void sub_110E70(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111150 sub_111150: [H_CutInPlayer_CreateFromFile] Creates "H_CutInPlayer" (RwCalloc 0x314,
//   kwlnTaskCreateWithAutoPriority 4207): the four s16 ids of the 64-bit $a1 to +0xA8..+0xAE, the path
//   "battle/cutin/c%02d_%d%x%02d.cpk" (+0xFC), the directory "battle/cutin/" (+0x1FC), load-from-file +0x310 = 1.
void sub_111150(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111260 sub_111260: [H_CutInPlayer_CreateFromArchive] As sub_111150 with the archive request $a2 (+0xC8) and
//   +0x310 = 0 (the data is already loaded).
void sub_111260(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111380 sub_111380: [H_CutInPlayer_CreateWithPriority] As sub_111260 under kwlnTaskCreate with priority $a1
//   (+0x30C, +0x308 = 1).
void sub_111380(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111520 sub_111520: [H_CutInPlayer_SetEndFrame] The player's end frame (s16 +0xD2) = $a1.
void sub_111520(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111570 sub_111570: [H_CutInPlayer_SetBlend] The player's blend mode (+0x304) = $a1 (handed to the draw task's
//   +0x4E4).
void sub_111570(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1115B0 sub_1115B0: [H_CutInPlayer_Pause] Pauses the player's draw task (+0x4E8 = 1) when it exists.
void sub_1115B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1115E0 sub_1115E0: [H_CutInPlayer_DrawDirect] Draws the player's draw task immediately (sub_10EC50) when it
//   exists.
void sub_1115E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x111D60 sub_111D60: [H_DrawMaestro_Destroy] Destroy callback of "H_DrawMaestro": drops the file request (+4) and
//   the clump (+0xC, sub_4B4410), frees the work.
void sub_111D60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the sprite fonts and the sprite draw helpers (spr*) -----------------------------------------------------------
// 0x111F50 sprFontInit: Loads the three sprite fonts synchronously (kwlnInitMain): requests
//   "camp/font/i_font01a.spr", "i_font02a.spr", "i_font02b.spr", waits for each (H_Cdvd_ReadSync), registers them
//   (sprAddFile) into sSprFontFiles[3] 0x833A40, runs the file list (sub_1120C0) until all three reach state 5, then
//   drops the requests.
void sprFontInit(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x115CD0 sub_115CD0: [sprDrawSpriteBasic4] One-shot sprite draw: sprCreateHandle(0, file, sprite), x / y / z from
//   $f12 / $f13 / $f14, flags $a3, rgb $t0..$t2, sprDrawSprite(handle, 0) (sub_1127D0), unlink from the handle list
//   (gp-0x4DB4) and RwFree.
void sub_115CD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the persona effects (h_perefect0/1/2.c: "H_PerEfect0Draw" .. "H_sMark2SprDraw") ------------------------------
// 0x115F00 sub_115F00: [H_PerEfect0_Update] Update of "H_PerEfect0Draw" (jump table 0x7B5360): 0 request
//   "battle/cutin/per_efc0_%02X_00.bin" (AGS variants), 1 register its three archives (H_Cdvd_CacheAddArchive), start
//   three cut-in players (sub_111260) with the persona's frame set and blend 1, load the two effect models
//   (sub_34FCD0), 2 wait for the players, 4 start them, 5 run until the players end; returns -1 when finished.
void sub_115F00(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1165C0 sub_1165C0: [H_PerEfect0_Destroy] Destroy callback of "H_PerEfect0Draw": removes the three archives, drops
//   the request, frees the two effect models (sub_34FCF0) and the work.
void sub_1165C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1166A0 sub_1166A0: [H_PerEfect0_Create] Creates "H_PerEfect0Draw" (RwCalloc 0xAB4, auto priority 4207, sub_115F00
//   / sub_1165C0); persona +4 = $a1, +8 = $a2.
void sub_1166A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116760 sub_116760: [H_PerEfect0_IsReady] Effect 0 work state == 3.
void sub_116760(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116780 sub_116780: [H_PerEfect0_Start] Effect 0 work state = 4.
void sub_116780(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1167A0 sub_1167A0: [H_PerEfect0_End] Effect 0 work +0x78 = 1 (end requested).
void sub_1167A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1167C0 sub_1167C0: [H_PerEfect0_GetFrame] Frame value i of effect 0 (+0x68 + 4 * i); 51 for i == 0.
void sub_1167C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1167F0 sub_1167F0: [H_PerEfect1_Update] Update of "H_PerEfect1Draw" (jump tables 0x7B53E0 / 0x7B53B0 / 0x7B5380):
//   0 request "battle/cutin/per_efc1_%02d.bin" by persona, 1 register two archives, start a cut-in player and build
//   the mark sprite file (sprCreateHandleFromData), 2 wait, end frame 50, 4 start and create the "H_sMarkSprDraw"
//   task, 5 count to 50 and stop the player; returns -1 when the player is gone.
void sub_1167F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116CF0 sub_116CF0: [H_PerEfect1_Destroy] Destroy callback of "H_PerEfect1Draw": frees the sprite file
//   (sub_1124B0), removes the archives, drops the requests, destroys the two rasters and frees the work.
void sub_116CF0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116E20 sub_116E20: [H_PerEfect1_Create] Creates "H_PerEfect1Draw" (RwCalloc 0x73C, auto priority 4207); persona
//   +4 = $a1.
void sub_116E20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116ED0 sub_116ED0: [H_PerEfect1_IsReady] Effect 1 work state == 3.
void sub_116ED0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116EF0 sub_116EF0: [H_PerEfect1_Start] Effect 1 work state = 4.
void sub_116EF0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116F10 sub_116F10: [H_PerEfect1_GetLength] Returns 63 (effect 1's length in frames).
void sub_116F10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116F20 sub_116F20: [H_PerEfect1_GetFrame] Effect 1 frame counter (+0x64).
void sub_116F20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116F30 sub_116F30: [H_PerEfect1_IsPastHit] Effect 1 frame counter >= 50.
void sub_116F30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116F50 sub_116F50: [H_PerEfect1_End] Effect 1: +0x6C = 1 and ends its mark sprite (sub_117470).
void sub_116F50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x116F80 sub_116F80: [H_sMarkSpr_Update] Update of "H_sMarkSprDraw": a four-phase slide of the mark sprite on the
//   eased path sub_18BC10 / sub_18B700 (phase 0 start from x 666, 1 slide in with a shrinking x offset and a debug
//   printf of the end / current x, 2 a 6-frame bounce, 3 wait for the end request, 4 slide out); each frame one
//   sprite handle drawn and freed. Returns -1 at the end.
void sub_116F80(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x117440 sub_117440: [H_sMarkSpr_Destroy] Destroy callback of "H_sMarkSprDraw": frees the work.
void sub_117440(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x117470 sub_117470: [H_sMarkSpr_End] Mark sprite work +0xC = 1 (end requested).
void sub_117470(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x117490 sub_117490: [H_sMarkSpr_Create] Creates "H_sMarkSprDraw" (RwCalloc 0x58, priority 6325, sub_116F80 /
//   sub_117440); sprite file +0x10 = $a1.
void sub_117490(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x117540 sub_117540: [H_PerEfect2_Update] Update of "H_PerEfect2Draw" (jump table 0x7B5400): 0 request the one to
//   three persona textures "battle/cutin/c71_c80_L_L_1/[AGS_]a_%03X.tmx" and the per_efc2 archive, 1 build the cut-in
//   draw tasks (sub_1103E0, layer colours sub_110620) and the texture requests through the resource manager, then the
//   later states map the textures, drive the layers (sin / cos motion) and the "H_sMark2SprDraw" task; returns -1
//   when done.
void sub_117540(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1191C0 sub_1191C0: [H_PerEfect2_Destroy] Destroy callback of "H_PerEfect2Draw": removes the archive, frees the
//   sprite file, drops the nine requests, destroys the six rasters and frees the work.
void sub_1191C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1192B0 sub_1192B0: [H_PerEfect2_Create] Creates "H_PerEfect2Draw" (RwCalloc 0x834, priority 6335); the three
//   persona ids from $a1[0..2] to +8..+0x10.
void sub_1192B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x119380 sub_119380: [H_PerEfect2_IsReady] Effect 2 work state == 3.
void sub_119380(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1193A0 sub_1193A0: [H_PerEfect2_Start] Effect 2 work state = 4.
void sub_1193A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1193C0 sub_1193C0: [H_PerEfect2_GetLength] Returns 40.
void sub_1193C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x1193D0 sub_1193D0: [H_sMark2Spr_Update] Update of "H_sMark2SprDraw": the second mark sprite's zoom-in (12.4 scale
//   13516 -> 4096 on the eased path), a 3-frame and a 2-frame bounce, then the hold and the slide out; one handle
//   drawn and freed per frame. Returns -1 at the end.
void sub_1193D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x119930 sub_119930: [H_sMark2Spr_Destroy] Destroy callback of "H_sMark2SprDraw": frees the work.
void sub_119930(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x119960 sub_119960: [H_sMark2Spr_Create] Creates "H_sMark2SprDraw" (RwCalloc 0x58, priority 6337); +4 = $a1,
//   sprite file +0x54 = $a2.
void sub_119960(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frTagTable.c: four more text-tag handlers ----------------------------------------------------------------
// 0x3AE000 sub_3AE000: [frTagPlayVoiceByWeekday] Tag handler (code, layout): parameter p0; records it for today's
//   weekday (sub_16E2B0 on the sub_16DD40 record) and, for p0 != 0, plays the sound sub_10A4E0(0, 0, 4, id) whose id
//   is picked from the three thresholds 0x6A2640.. / ids 0x6A2650.. by p0. Returns 0.
void sub_3AE000(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AE420 sub_3AE420: [frTagSetCommuRank] Tag handler: parameters (p0 < 8, p1 < 4; K_Assert frTagTable.c 721 / 722)
//   -> sub_17C7F0(p0, p1). Returns 0.
void sub_3AE420(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AEE20 sub_3AEE20: [frTagTestCondition] Tag handler (jump table 0x7BB1E0): tests condition p0 against value p1 --
//   0..2 the three social stats (sub_16C6F0 / 0x16C740 / 0x16C790) < p1, 3..7 a stat of sub_1738D0 < p1, 8 / 9
//   sub_16C920 ==/!= p1, 10 / 11 sub_172C50 none / some, 12..16 flag bank[p0 - 12] + p1 set, 17..21 flag bank[p0 -
//   17] + p1 clear (the five bank bases copied from 0x6A2660); a true condition sets tag flag 0x20. Returns 0.
void sub_3AEE20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AF110 sub_3AF110: [frTagSetValue] Tag handler, only while the layout runs (default glyph flags bit 7):
//   parameters (kind, bank, index, value): 0 datSetFlag(bank base 0x6A2680[bank] + index, value), 1 sub_171C40, 2 / 3
//   the weekday record (sub_16E2B0); kind 6 does nothing. Returns 0.
void sub_3AF110(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frFont.c: the font table and the styles -----------------------------------------------------------------
// 0x3AF7A0 frInitFontTable: Starts the font system (frFontSystemStart: $a0 = GS width in pixels, $a1 = glyph
//   rasters): clears the counters and the nine styles' Huffman words, the glyph-size words (512 bytes, log2 9, the GS
//   row of 32 * width / 16 rounded to a power of two and its log2, 512 / 64), the GS-list container (sub_3B41A0: 16 x
//   width/16 entries of 32 x 32), the glyph ring (sub_3B45F0(0x2C, 4 * n)) and the line ring (0x44, n), loads
//   font0.fnt as style 0 (frLoadFontData), prints the CLUT, clears the 32 tag slots, prints "clear texarea", sets the
//   GS width (gp-0x46A8) and creates the raster-slot pool (frFontRasterCreate(n)).
void frInitFontTable(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFAD0 frAddFontStyle: Binds style `s` (< 9, else "Illegal style no error") to a .FNT image: record 0x95ACF0 + 32
//   * s = {owner (the file argument $a2), fnt, width-table bytes, block-2 bytes, width table, block 2, glyph table,
//   Huffman block} from the header (CLUT blocks +0xA * 64, the two length-prefixed tables when +0x16, then glyph
//   count * 4 bytes); a null fnt takes the file argument (K_Assert 1023 when both are 0); prints "font trans
//   ADDR=...".
void frAddFontStyle(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFC70 frLoadFontData: Loads "font/font0.fnt" once (H_Cdvd_Request + ReadSync, kept in 0x95AE74) and binds it as
//   style 0 ("abort2!! ... have been allocated" when style 0 is set); copies style 0's first 32 bytes to styles 1..5
//   and clears the two scale words (gp-0x46B8 / gp-0x46B4).
void frLoadFontData(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3AFE30 frFreeFontStyles: For every bound style (Huffman word set): drops its file request (0x95AE74 + 4 * s,
//   "font cdvd free StyleNo=%d") and clears its owner and Huffman words; the glyph-table word always.
void frFreeFontStyles(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frFont.c: glyph lists, the glyph cache, the draw-time helpers ------------------------------------------------
// 0x3B0030 sub_3B0030: [frFontLineChainRelease] Releases a line chain: for every line (+0x24) every glyph node
//   (+0x28) -- a glyph whose cache entry (+0x1C) drops to refcount 0 frees its raster slot (in-use bit and GS entry
//   cleared) and its GS-list entry (fmGslReleaseEntry), cached-glyph count -1 -- goes back to the glyph ring, then
//   the line to the line ring (the two node counters follow). Returns 0.
void sub_3B0030(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B0430 frFontCacheGlyph: The glyph cache (frFontCreateGlyphNode, frFontRasterDrawGlyph): looks up (glyph, colour
//   set) in the raster slots (frFontRasterFind); a slot with a GS entry is a hit (entry refcount +1). A miss decodes
//   the glyph from its style's Huffman block into a RwMalloc'd 512-byte buffer (fmGslGetGlyphBlocks /
//   fmGslDecodeGlyph), takes a slot (frFontRasterFindOrAlloc; K_Assert 1730), frees the buffer, then registers a GS
//   entry of the style's glyph size (frFontRegisterGlyphRaster) linked both ways with the slot; cached-glyph count
//   +1. Returns the GS entry.
void frFontCacheGlyph(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B0970 frFontBuildGlyphList: Appends text to a line node (or a fresh one from the line ring when $t0 is 0;
//   K_Assert 2010): style $a1 (>= 0 sets the current style gp-0x46B0), colour set $a2, mode $a3; returns 0 when the
//   style has no font. Each character (two bytes from 0x80) becomes a glyph node (frFontCreateGlyphNode; K_Assert
//   2031) linked at the tail (+0x28 / +0x24), the line's width (+0xC) and glyph count (+0x18) grow, pair kerning
//   (frFontKerningAdjust) is taken off the previous glyph and the width; the last glyph's scaled sizes go to the line
//   (+0x10 / +0x12). Returns the line.
void frFontBuildGlyphList(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B0F50 sub_3B0F50: [frFontGlyphRevealStep] One glyph of the typewriter reveal (frFontDraw): the glyph becomes
//   visible (its alpha +0x10 low byte raised by 32 * speed / (advance + spacing), clamped at 255) once the previous
//   glyph is past the threshold `skip` (+20 for ASCII), honouring the window's wait tags (F247 / F215: until the
//   voice ends or the ticks run out; F214: ticks), and the tag F117 window wait; returns the y jitter of a mode-1
//   glyph that is not fully shown (-16 * (2 * code2 % 5 - 2)).
void sub_3B0F50(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B1710 sub_3B1710: [frFontChainWaitDone] Sums the glyph counts (+0x18) of a chain (+0x2C, +0x28) and checks the
//   last line's wait tag: F247 / F215 wait for the voice (H_Snd channel 2) and ticks, F246 counts ticks down, F214
//   ticks; returns the count when no wait is pending, else 0.
void sub_3B1710(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B1D90 sub_3B1D90: [frFontLayoutTagSlot] Lays out tag slot `n` (0x95AC70[n]) into the layout record $a1 character
//   by character: a style change since the previous character starts a new line node (an empty line from "" joined to
//   the chain, alpha from the record) ; each character through frFontBuildGlyphList with the record's style / colour
//   set / mode, letter spacing gp-0x5804, the line width recomputed (K_Assert 2072 / 2120).
void sub_3B1D90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2020 sub_3B2020: [frFontLayoutString] As sub_3B1D90 for a string argument (the inserted-string tag handlers:
//   names, dates, weekdays).
void sub_3B2020(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B22A0 sub_3B22A0: [frFontLayoutFlushLine] Applies a layout record's pending state: a new-line request (+0x1C,
//   dropped when the current line is still empty) starts a new line node with the record's alpha and line code
//   (K_Assert 2072 / 2092); a pending position (+0x1D) moves the current line to (x, y) (K_Assert 2188).
void sub_3B22A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B2430 sub_3B2430: [frFontLayoutText] The text layout loop (sub_3B2990): skips a 4-byte header when the second
//   byte is 8, clears the tag flags, marks the layout phase (default glyph flags low bits 1); per byte: 0 ends, 0xFn
//   + next byte runs sFrTagTable[code & 0xFF] (code 2..0x4C; K_Assert 3577 / 3578) and skips 2 * (n - 1) parameter
//   bytes (a non-zero result stops), '\n' with flag 4 steps a row; any other character flushes pending lines (as
//   sub_3B22A0, alpha through frFontLineSetAlpha), maps a two-byte code >= 0xC080 to style 8 (- 0x4000) and ' ' to
//   the wide blank 0x83F7, appends it (frFontBuildGlyphList), sets letter spacing -2 * size / 32, the width and the
//   line's z (layout +8 >> 4; K_Assert 2213). Ends the phase (bits 2) and returns the current line.
void sub_3B2430(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- frFontRaster.c and fmGslCont.c: the raster-slot pool and the GS list ----------------------------------------
// 0x3B35E0 frFontRasterCreate: Creates the raster-slot pool (frInitFontTable; K_Assert 36 when one exists):
//   RwMalloc(540 * n + 24), header {n, slots, active head, tail, free head, tail} at gp-0x46AC, n slots of 28 bytes
//   each followed by its 512-byte glyph buffer (+0xC) chained on the free list (+0x18), then a 32 x 32 4-bit raster
//   per slot (RwRasterCreate, format 0x4504; "raster create false" retries).
void frFontRasterCreate(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B3E60 frFontRasterAllocSlot: Takes the free list's head slot (K_Assert 291 on a null glyph buffer), appends it
//   to the active list, swizzles the glyph into its raster (frFontRasterCreate2), stores glyph / ticks 1 / in-use,
//   copies the 512 bytes into the slot's buffer and clears the GS entry. Returns the slot or 0.
void frFontRasterAllocSlot(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B3F90 frFontRasterCreate2: Writes a decoded 4-bit 32 x 32 glyph into the slot's raster: copies the 256-byte
//   swizzle table 0x6A28F0 to its frame, locks the raster (sub_4CE200, mode 9) and stores each texel at its PSMT4
//   block address (the low / high nibble by the table's bit 0), unlocks, locks the palette and copies colour set `c`
//   (16 entries from 0x6A2130 + 64 * c), unlocks; the slot's colour set (+8) = c. No data prints "font data none"
//   (K_Assert 377).
void frFontRasterCreate2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B41A0 sub_3B41A0: [fmGslInit] Initialises the GS-list container once (gp-0x46A4 flag): entry size w x h, w * h /
//   2 bytes, cols * rows entries (also the free count), RwMalloc(32 * n) entries (K_Assert 81) and an optional n *
//   $t1 work block (K_Assert 87); a circular doubly linked list (+0x1C next, +0x18 prev) with each entry's index, GS
//   rectangle (x0, y0, x1, y1 in 1/16 px) and work pointer. Returns 1 (0 when already set up or on a null entry,
//   after sub_3B44A0).
void sub_3B41A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x3B4D10 sub_3B4D10: [itfPnlDrawFrame3] The name-plate frame of a panel (draw type 6): three slices of the
//   rectangle $a0 (left cap of width $a3, the stretched middle, the right cap) through sub_3B4B40 with the UV sets
//   0x6A2A28 / 0x6A2A2C / 0x6A2A30 of the plate raster gp-0x57C4 and the colour $a1.
void sub_3B4D10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
