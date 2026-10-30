// libmpeg's handle layer (0x500AD0-0x5024F0): the sceMpeg accessors and setters over the decoder state that the
// sceMpeg handle's word +64 points at (the record cri2 named, game/include/p3fes/game/cri2.h `cri2::mpeg`), the callback
// dispatchers, the work-area allocator, the field-picture display hand-off and the default error report. Library API
// names are the FLIRT names of symbols/functions.json (ADR-0009); no SDK material was used.
//
// Register ABI (arguments in $a0.., the result in $v0); one role line per function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs1::mpeg {
// The sceMpeg decoder state beyond cri2::mpeg's names (game/include/p3fes/game/cri2.h): the handle's word +64 points at it.
constexpr s32 kCbTable = 12;     // 12-byte callback slots by type: function, data, the installer's $gp
constexpr s32 kCbNodata = 24;    // the NODATA (type 1) slot's function
constexpr s32 kPtsGapSet = 140;  // default PTS gap valid / the gap (u64)
constexpr s32 kPtsGap = 144;
constexpr s32 kOutCsc = 196;     // output format: 1 RGB32 (colour-space converted), 0 raw 8-bit macroblocks
constexpr s32 kDispWidth = 224;  // display size
constexpr s32 kDispHeight = 228;
constexpr s32 kOutX = 240;       // raw output: x / y (pixels) and the size of the caller's buffer
constexpr s32 kOutY = 244;
constexpr s32 kOutSize = 248;
constexpr s32 kPtm = 256;        // presentation time (u64) / its flag
constexpr s32 kPtmSet = 264;
namespace alalc {  // the work-area allocator record
constexpr s32 kBase = 0, kSize = 4, kCursor = 8, kMark = 12;
}  // namespace alalc
}  // namespace libs1::mpeg


// Delete a decoder: nothing to release in this build; returns 1.
void sceMpegDelete(EEContext& ctx);  // 0x500AD0 (register ABI: arguments in $a0.., the result in $v0)
// Feed a bitstream chunk to the IPU: rounds (size + 19) / 16 down to whole quadwords (towards zero for negative sums)
// and hands the state, the data and that length to _sendDataToIPU; returns 1.
void sceMpegAddBs(EEContext& ctx);  // 0x500AD8 (register ABI: arguments in $a0.., the result in $v0)
// Decode the next picture as RGB32: output format 1 (colour-space converted), the image buffer as an uncached
// (0x20000000) address, the buffer size, no x / y offsets; tail-calls _getpic.
void sceMpegGetPicture(EEContext& ctx);  // 0x500B18 (register ABI: arguments in $a0.., the result in $v0)
// Decode the next picture as raw 8-bit YCbCr macroblocks: the image buffer (uncached, written as a doubleword: +240
// is cleared with it), the buffer size, output format 0, y offset 0; tail-calls _getpic.
void sceMpegGetPictureRAW8(EEContext& ctx);  // 0x500B60 (register ABI: arguments in $a0.., the result in $v0)
// Ask the running _getpic to stop (the abort flag +2168); returns 1.
void sceMpegGetPictureAbort(EEContext& ctx);  // 0x500BA8 (register ABI: arguments in $a0.., the result in $v0)
// The end-of-stream flag (state +0).
void sceMpegIsEnd(EEContext& ctx);  // 0x500C38 (register ABI: arguments in $a0.., the result in $v0)
// 1 when no reference picture is held (state +4 == 0).
void sceMpegIsRefBuffEmpty(EEContext& ctx);  // 0x500C48 (register ABI: arguments in $a0.., the result in $v0)
// Set the decode-or-skip limits for I / P / B pictures (state +168 / +172 / +176); returns the state pointer.
void sceMpegSetDecodeMode(EEContext& ctx);  // 0x500C58 (register ABI: arguments in $a0.., the result in $v0)
// Read the three decode-or-skip limits into *a1 / *a2 / *a3; returns the B limit.
void sceMpegGetDecodeMode(EEContext& ctx);  // 0x500C70 (register ABI: arguments in $a0.., the result in $v0)
// Install the callback of a type (12-byte slots from state +12: function, data, the caller's $gp); returns the old
// function.
void sceMpegAddCallback(EEContext& ctx);  // 0x500C90 (register ABI: arguments in $a0.., the result in $v0)
// Set the reference buffers' address space (0 uncached, 1 cached; state +2172) and re-clear them through _clearOnce;
// -1 for any other type, else 1.
void sceMpegSetBuffType(EEContext& ctx);  // 0x500CC8 (register ABI: arguments in $a0.., the result in $v0)
// The reference buffers' address space (state +2172).
void sceMpegGetBuffType(EEContext& ctx);  // 0x500D00 (register ABI: arguments in $a0.., the result in $v0)
// Call the callback installed for the record's type (the record's first word) with (handle, record, its data); 0 when
// the handle, its state or the slot is empty, else the callback's result (a jalr: the frame and $ra as the original).
void _sceMpegDispatchMpegCallback(EEContext& ctx);  // 0x500D10 (register ABI: arguments in $a0.., the result in $v0)
// Call the NODATA callback (type 1) with a stack record {1} when one is installed; returns 1 either way.
void _sceMpegDispatchMpegCbNodata(EEContext& ctx);  // 0x500D88 (register ABI: arguments in $a0.., the result in $v0)
// Mark the six reference-picture descriptors (forward / backward, frame and both fields: state +456.. +492) as not
// complete (their word +40 = 0); returns 1.
void sceMpegClearRefBuff(EEContext& ctx);  // 0x500E48 (register ABI: arguments in $a0.., the result in $v0)
// Decode the next picture as raw macroblocks into a buffer of a2 x a3 macroblocks: x / y in pixels (16 x), the
// macroblock count, output format 0; tail-calls _getpic.
void sceMpegGetPictureRAW8xy(EEContext& ctx);  // 0x500EA0 (register ABI: arguments in $a0.., the result in $v0)
// Set the default PTS gap (u64 at state +144) and its valid flag (+140); returns 1.
void sceMpegSetDefaultPtsGap(EEContext& ctx);  // 0x500EF0 (register ABI: arguments in $a0.., the result in $v0)
// Clear the default PTS gap and its flag; returns 1.
void sceMpegResetDefaultPtsGap(EEContext& ctx);  // 0x500F08 (register ABI: arguments in $a0.., the result in $v0)
// Set the image buffer (state +236); returns 1.
void sceMpegSetImageBuff(EEContext& ctx);  // 0x500F20 (register ABI: arguments in $a0.., the result in $v0)
// The display width (state +224).
void sceMpegDispWidth(EEContext& ctx);  // 0x500F30 (register ABI: arguments in $a0.., the result in $v0)
// The display height (state +228).
void sceMpegDispHeight(EEContext& ctx);  // 0x500F40 (register ABI: arguments in $a0.., the result in $v0)
// The address of the display-centre record (state + 200). (Both the X and the Y accessor return this same address in
// this build.)
void sceMpegDispCenterOffX(EEContext& ctx);  // 0x500F50 (register ABI: arguments in $a0.., the result in $v0)
// The address of the display-centre record (state + 200), as sceMpegDispCenterOffX.
void sceMpegDispCenterOffY(EEContext& ctx);  // 0x500F60 (register ABI: arguments in $a0.., the result in $v0)
// Set the pending broken-link flag (state +252); returns the old one.
void _sceMpegSetBrokenLink(EEContext& ctx);  // 0x500F70 (register ABI: arguments in $a0.., the result in $v0)
// Set the presentation time (u64 at state +256) and its flag (+264); returns 1.
void _sceMpegSetPtm(EEContext& ctx);  // 0x500F80 (register ABI: arguments in $a0.., the result in $v0)
// Initialise a work-area allocator {base, size, cursor, dynamic mark}: cursor and mark at the base.
void _sceMpegAlalcInit(EEContext& ctx);  // 0x501068 (register ABI: arguments in $a0.., the result in $v0)
// Remember the cursor as the dynamic mark (what _sceMpegAlalcFree rewinds to).
void _sceMpegAlalcSetDynamic(EEContext& ctx);  // 0x501080 (register ABI: arguments in $a0.., the result in $v0)
// Bytes left in the allocator: base + size - cursor.
void _sceMpegAlalcReset(EEContext& ctx);  // 0x501110 (register ABI: arguments in $a0.., the result in $v0)
// Hand a decoded field pair to the display (a0 = the decoder state, a1 / a2 = the two field descriptors, top first
// unless the picture structure +388 is 2): fills the output-info record (+2152) with each field's PTS (its own, else
// extrapolated from the default PTS gap, or a pending PTM) and DTS and its coded flags, sets the display size (+224 /
// +228) and centre (+200 / +204), checks the image buffer is large enough ("Too small buffer ... for %dx%d picture"
// through sceSnprintf and _sceMpegError otherwise), then converts with _sceMpegCscStoreRefImage (RGB32) or copies
// with _cpr8 (raw), by the output format.
void _dispRefImageField(EEContext& ctx);  // 0x5016C8 (register ABI: arguments in $a0.., the result in $v0)
// The default error report: scePrintf("[MPEG ERROR]%s\n", text) (a tail call).
void _ErrMessage(EEContext& ctx);  // 0x5024F0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
