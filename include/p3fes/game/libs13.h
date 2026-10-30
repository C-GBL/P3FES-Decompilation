// Phase 5 slice libs13: CRI Sofdec's SFD core around the video decoder (0x590008-0x59C5E0). Register-ABI bodies
// started from p3fes_handgen (arguments in $a0.., the result in $v0; every statement, charge and check point is the
// generator's: game/include/p3fes/game/hg_cpu.h). Each declaration carries the function's role, read from the
// instructions (the error codes are the values the functions pass to the error reporter sub_58BE40). No CRI material
// was opened. The records below name the offsets the bodies use; tail1.h's sfd:: / mpv:: and libs5.h's sfdh:: hold
// the rest of the SFD handle.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs13 {
// The SFD handle (tail1::sfd): what this slice adds.
namespace sfd {
constexpr s32 kStat = 72;           // s32: status 0..6 (1 stopped, 2 preparing, 3 ready, 4 playing, 6 play end)
constexpr s32 kReq = 76;            // s32: the requested status (3 stop, 4 start)
constexpr s32 kApiMode = 88;        // s32: the API mode the handle was claimed for (sub_597DC8)
constexpr s32 kDecInfo = 2316;      // the decode-info record (sub_596F98)
constexpr s32 kCounters = 2384;     // the counters record: word 0 = decoded pictures (sub_597000)
constexpr s32 kParams = 2572;       // u32[100] by id (tail1::sfd::kParams); id n at + 4 n
constexpr s32 kTimeRec = 3376;      // the time record (sub_599810)
constexpr s32 kTcPic = 3404;        // the picture's time code (32 bytes)
constexpr s32 kTrefTab = 4576;      // 64 x {u16, u16}: the temporal-reference table (sub_5905F0)
constexpr s32 kStreams = 4880;      // 116-byte stream records
constexpr s32 kStreamStride = 116;
constexpr s32 kOutRecs = 5808;      // 136-byte output records, one per frame record
constexpr s32 kOutStride = 136;
constexpr s32 kTrnSlots = 7984;     // 68-byte transfer slots (9)
constexpr s32 kTrnStride = 68;
constexpr s32 kVdecWork = 8128;     // u32: the video-decoder work (vdec::), set to handle + kVdecArea by sub_5929B0
constexpr s32 kVdecArea = 9128;     // the video-decoder work area inside the handle
constexpr s32 kHdrObj = 14000;      // u32: the header object (tail1::sfd::kHdrBufObj)
constexpr s32 kProfile = 14016;     // the profile record (sub_597088)
constexpr s32 kMinWork = 0x37D0;    // the smallest work buffer sub_596CC0 accepts
}  // namespace sfd
// The video-decoder work (handle + sfd::kVdecWork)
namespace vdec {
constexpr s32 kMpv = 0;             // u32: the MPV handle
constexpr s32 kSkipMode = 116;      // s32: 3 skips B pictures, 2 P and B
constexpr s32 kEndMark = 124;       // s32
constexpr s32 kPrevRef = 352;       // u32: the older reference frame record
constexpr s32 kNextRef = 356;       // u32: the newer reference frame record
constexpr s32 kPending = 360;       // u32: the frame record held for the next picture
constexpr s32 kSkipB = 372;         // s32
constexpr s32 kFrameCount = 376;    // s32: frame records in use (<= 16)
constexpr s32 kFrames = 384;        // the frame records (frm::)
constexpr s32 kIpu = 4392;          // s32: decode through sceMpeg (the IPU) instead of MPV
constexpr s32 kIpuPending = 4404;   // s32: pictures fed and not yet decoded
constexpr s32 kMpeg = 4432;         // the sceMpeg record (72 bytes, saved at 0x9ACB70 across a recreate)
constexpr s32 kViBuf = 4504;        // the video-input ring (vibuf::)
}  // namespace vdec
// A frame record (vdec::kFrames + 240 i)
namespace frm {
constexpr s32 kSize = 240;
constexpr s32 kState = 0;           // 0 free, 1 taken, 2 decoded, 3 shown (was 4), 4 decoded reference
constexpr s32 kBuf = 8;             // u32: the frame buffer
constexpr s32 kTime = 56;           // s32: its time (sub_593FB0 orders by it)
constexpr s32 kShown = 88;          // s32: -1 while not shown
constexpr s32 kPicInfo = 92;        // the 32-byte picture info
}  // namespace frm
// The video-input ring of the IPU path (viBufCreate)
namespace vibuf {
constexpr s32 kBase = 0;            // u32: the data buffer
constexpr s32 kTags = 4;            // u32: the DMA tag area (uncached: | 0x20000000)
constexpr s32 kSectors = 8;         // s32: size in 2 KiB sectors
constexpr s32 kCount = 20;          // s32: bytes buffered
constexpr s32 kBytes = 24;          // s32: size in bytes
constexpr s32 kSema = 64;           // s32: the semaphore
constexpr s32 kTotal = 72;          // s64: bytes written in all
}  // namespace vibuf
}  // namespace libs13


// Video decoder, the picture-header step of an SFD handle: sets the MPV window, reads the next header from the input
//   chunk (sub_579450) and charges the bytes it took, reads the picture info (sub_579138; error -16773371); with flag
//   0x40, a sequence-size check and the param-95 callback may refuse the picture (*a4 = -2); sets the skip mark
//   work+372 by picture type and format, the temporal-reference change (+268 / +272), the param-77 / 78 user-data
//   callback; then the time stamp (sub_590360) and, when the flag mask matches, the time-code chain (sub_5905F0,
//   sub_590948, sub_590EF0, sub_590FD0, sub_591168).
void sub_590008(EEContext& ctx);  // 0x590008

// The picture's time stamp: both outs -1; with a chunk address, the stream's time stamp for it (sub_5980C8) and, when
//   one is found, its conversion (sub_590430).
void sub_590360(EEContext& ctx);  // 0x590360

// Resets a time-stamp record: words 0..2 and 6 = 0, the 64-bit word at +16 and word 7 = -1.
void sub_590408(EEContext& ctx);  // 0x590408

// The temporal-reference table (64 x {u16 count, u16 sum} at handle+4576): a new sequence clears it, otherwise the
//   slots skipped since the reference are cleared; stores the picture's field count and the running sum, and for a B
//   picture (type 3) patches the reference picture's sum and calls sub_590878.
void sub_5905F0(EEContext& ctx);  // 0x5905F0

// The time-code source: when param 52 is unset and the picture has no time stamp but a GOP time code (sub_590A28),
//   param 52 = 1; then, with param 52 = 1, builds the time code (sub_590AE8).
void sub_590948(EEContext& ctx);  // 0x590948

// Builds the picture's time code (handle+3404): from a time stamp, frames = PTS * 2 / rate (sub_57BC10) split into
//   h:m:s:f at the rate 0x7CA068[code], with the drop-frame tables 0x7CA090 (29.97) / 0x7CA0B0 (59.94); otherwise
//   from the GOP time code advanced by the field count (sub_590DF8), or the previous one copied, or zero.
void sub_590AE8(EEContext& ctx);  // 0x590AE8

// Advances a time code by its field count: frames + extra + 1 + fields / 2, carried into seconds, minutes and hours
//   at the rate 0x7CA068[code]; drop-frame: frame 0 / 1 of a minute not divisible by 10 becomes 2.
void sub_590DF8(EEContext& ctx);  // 0x590DF8

// Once (flag +3436): converts the picture's time code to a time (sub_59A870) and keeps it as the first time code
//   (+3440, time at +3472 / +3476).
void sub_590EF0(EEContext& ctx);  // 0x590EF0

// The latest time code: converts the picture's time code (sub_59A870) into the record at +3568 and, when its time is
//   at least the kept one (+3480 + 36), copies it there.
void sub_590FD0(EEContext& ctx);  // 0x590FD0

// Copies the GOP time-code fields of an MPV picture info (rate, drop flag, h, m, s, f, the byte at +84) into a time-
//   code record; field count 0.
void sub_591118(EEContext& ctx);  // 0x591118

// After a picture header: the sequence size (sub_579240; error -16773354), the rates (sub_5792A0), the decode-delay
//   limit work+276 (param 60: the smaller of the VBV delay and sub_589510, else 0); then the header object's video
//   record (sub_591298), the sequence record (sub_5913B8) and the frame pool (sub_5913F0).
void sub_591168(EEContext& ctx);  // 0x591168

// Fills the header object's video record once (its word 0 still 0): the VBV size capped at 512, the sequence block
//   (sub_575410), the bit rate x 50 or 0 for the variable-rate marker 0x3FFFF, the first time code.
void sub_591298(EEContext& ctx);  // 0x591298

// Stores the sequence record: width, height, the rate words, the byte count, the aspect.
void sub_5913B8(EEContext& ctx);  // 0x5913B8

// The frame pool: the picture must fit the configured maximum (errors -16773353 / -16773352); frame size =
//   macroblocks x 1,024 (format 2) or x 384, + 64; carves the frame buffers from work+36 into work+48.., the count to
//   work+376, and resets the frame records (sub_592DD0).
void sub_5913F0(EEContext& ctx);  // 0x5913F0

// Whether to decode the next picture: no when param 39 is set; the pending result when the skip byte (+228) is set;
//   otherwise the skip checks (sub_591808, sub_591858, sub_5918A8, sub_5916A0, sub_591988) and the decision's record
//   (sub_591700).
void sub_5915A8(EEContext& ctx);  // 0x5915A8

// Skip-mode check (work+116): mode 3 skips B pictures (type 3), mode 2 P and B (types 2..3).
void sub_5916A0(EEContext& ctx);  // 0x5916A0

// Whether the picture type's decoding is disabled: param 2 (I), 3 (P), 4 (B) zero; other types 1.
void sub_591858(EEContext& ctx);  // 0x591858

// Decodes one picture: a frame record and the output descriptor (sub_591F38), the reference sizes (sub_592240), the
//   user data (sub_592790), the display time code (sub_5922C8); decodes it (sub_595390) between two clock reads
//   (sub_59B3A8, profile sub_59B4B0), charges the bytes and errors (sub_58FF70 / sub_58FEC8); on success the frame's
//   user data, sizes and time, the pending-frame rotation (work+360), the frame state (2 or the reference state), and
//   the decode counter callback (sub_597100).
void sub_591C80(EEContext& ctx);  // 0x591C80

// Takes the pending or a free frame record (sub_593A18; none: busy mark, -1), copies the 32-byte picture info into it
//   and its time; format 3 rotates the reference frames (the oldest released by sub_593B10; work+352 / +356) and
//   computes the Y / C plane addresses of the output descriptor; other formats flip the double buffer at work+320.
void sub_591F38(EEContext& ctx);  // 0x591F38

// The reference frames' byte sizes for format 3: a P picture its forward frame's, a B picture both; else 0.
void sub_592240(EEContext& ctx);  // 0x592240

// Once (flag +3656): the display time code: the latest time code, its field count cleared unless the B type is
//   decoded, converted (sub_59A870), stored at +3660.
void sub_5922C8(EEContext& ctx);  // 0x5922C8

// The frame's user data: a reference picture keeps the work copy; the input's user-data block (sub_592618) of kind 3
//   is copied into the frame's buffer, otherwise the work copy is.
void sub_592570(EEContext& ctx);  // 0x592570

// Finds the user-data block of the input chunk through the reader's get / release callbacks (+24 / +28): start-code
//   searches (sub_578160 / sub_577FC8), the kind from the table 0x7CA0D0, a miss counted in 0x7B47A4.
void sub_592618(EEContext& ctx);  // 0x592618

// Copies one {ptr, size} buffer into another (memcpy) and its size.
void sub_592790(EEContext& ctx);  // 0x592790

// Adds the stream's consumed byte count (sub_5895F0 / sub_589D80) to the handle's 64-bit total (+2464).
void sub_592958(EEContext& ctx);  // 0x592958

// Creates the video decoder of an SFD handle (when it has video): the work at +9128 (sub_592B10), the sceMpeg path
//   (sub_594C38), an MPV handle (sub_57B440; error -16773366) with the header callback 0x592EF8 (error -16773365),
//   the MPV params from params 0 / 1 and the format; restores the saved state (0x9ACB60..) in recreate mode.
void sub_5929B0(EEContext& ctx);  // 0x5929B0

// Initialises the video work: validates and copies the saved configuration 0x9ACAF0.. (sub_592D08; error -16773355),
//   the defaults (+116 = 5, +120 = 192, ...), the 16 frame records (sub_592DD0), the decode-info and time-stamp
//   records.
void sub_592B10(EEContext& ctx);  // 0x592B10

// Validates the saved video configuration: frame count 1..16, the frame buffers, the pointer tables.
void sub_592D08(EEContext& ctx);  // 0x592D08

// Resets n frame records (240 bytes): state 0, the buffer from the table, the time records (sub_599A30, sub_592E80),
//   +88 = -1.
void sub_592DD0(EEContext& ctx);  // 0x592DD0

// Fills 32 words with -1 (sub_575880).
void sub_592E80(EEContext& ctx);  // 0x592E80

// Clears a record of 7 words and 16 word pairs.
void sub_592EA0(EEContext& ctx);  // 0x592EA0

// Destroys the video decoder: saves the configuration into 0x9ACAF0.. and 0x9ACB60.., releases the sceMpeg path
//   (sub_595060), the MPV handle (sub_5930C8; error -16773364).
void sub_592F38(EEContext& ctx);  // 0x592F38

// Destroys an MPV handle (sub_57B5C8).
void sub_5930C8(EEContext& ctx);  // 0x5930C8

// Fills a frame's output record for the application from the frame record: buffers, sizes, format, times and the
//   picture bytes.
void sub_593200(EEContext& ctx);  // 0x593200

// Releases a frame given by the application (by output record or by frame); errors -16773345 / -16773362 / -16773361.
void sub_593468(EEContext& ctx);  // 0x593468

// An output record's header: a1 - 8.
void sub_593590(EEContext& ctx);  // 0x593590

// The header object's video record (+2768) while no picture was decoded, else 0.
void sub_593700(EEContext& ctx);  // 0x593700

// The frame record (work+384 + 240 i) whose output record (handle+5816 + 136 i) is a1; 0 when none of 16.
void sub_593878(EEContext& ctx);  // 0x593878

// The output record (handle+5808 + 136 i) of frame record a1; 0 when none.
void sub_593900(EEContext& ctx);  // 0x593900

// work+124 (the end mark).
void sub_593958(EEContext& ctx);  // 0x593958

// work+128 = a1.
void sub_593968(EEContext& ctx);  // 0x593968

// Under the lock: the number of decoded frames (state 2 or 4) not yet shown (+88 = -1); -1 when none and the end mark
//   is 1.
void sub_593978(EEContext& ctx);  // 0x593978

// Under the lock: takes a free frame record (state 0 -> 1); 0 when all are in use.
void sub_593A18(EEContext& ctx);  // 0x593A18

// Marks a frame decoded (state 2).
void sub_593AB0(EEContext& ctx);  // 0x593AB0

// Marks a frame shown: state 4 -> 3, else 0; +88 = -1.
void sub_593AE0(EEContext& ctx);  // 0x593AE0

// Under the lock: the oldest (smallest time) decoded frame not yet shown.
void sub_593B38(EEContext& ctx);  // 0x593B38

// Get-frame entry: handle check (sub_58C060; error -16776829), then sub_593E08.
void sub_593DB0(EEContext& ctx);  // 0x593DB0

// Under the lock: while playing (status 4), the oldest decoded frame (sub_593EA0) when its time is due (param 15,
//   sub_59AEC0).
void sub_593E08(EEContext& ctx);  // 0x593E08

// The oldest and the second-oldest decoded frames not yet shown (0 when fewer).
void sub_593EA0(EEContext& ctx);  // 0x593EA0

// Whether frame b is older than frame a (time at +56); 1 when a is null.
void sub_593FB0(EEContext& ctx);  // 0x593FB0

// Video-input ring: the 2 KiB sector of an address, 0 at the end mark.
void sub_593FE8(EEContext& ctx);  // 0x593FE8

// Packs a DMA tag: (addr << 32) | (id << 28) | qwc.
void sub_594108(EEContext& ctx);  // 0x594108

// The video-input ring buffer for the IPU path: base, the uncached tag area, size in 2 KiB sectors, a semaphore, the
//   tag chain (sub_5941A8).
void viBufCreate(EEContext& ctx);  // 0x594130

// Video-input ring, under its semaphore: the free space as up to two pieces split at the wrap.
void sub_5942E8(EEContext& ctx);  // 0x5942E8

// Video-input ring, under its semaphore: adds n written bytes (count +20, 64-bit total +72).
void sub_5943D8(EEContext& ctx);  // 0x5943D8

// Video-input ring, under its semaphore: removes n consumed bytes; spins forever on an underflow, as the original.
void sub_594428(EEContext& ctx);  // 0x594428

// Sets the IPU-decode switch 0x7B47A8.
void sub_594B68(EEContext& ctx);  // 0x594B68

// Whether the handle decodes through sceMpeg (work+4392).
void sub_594B78(EEContext& ctx);  // 0x594B78

// With the IPU switch on: sceMpegInit and clears the saved sceMpeg record (72 bytes at 0x9ACB70).
void sub_594B88(EEContext& ctx);  // 0x594B88

// Sets up the sceMpeg path of a video work: the buffer sizes, sceMpegCreate and its four callbacks (or the saved
//   record, sub_595110), the input ring (viBufCreate: 256 sectors, 512 tags) and its DMA.
void sub_594C38(EEContext& ctx);  // 0x594C38

// Feeds a chunk to the input ring: the free pieces (sub_5942E8), the copy (sub_595260), the count (sub_5943D8).
void sub_594EC8(EEContext& ctx);  // 0x594EC8

// sceMpeg callback: restarts the input DMA (sub_5946A8); 1.
void sub_595010(EEContext& ctx);  // 0x595010

// sceMpeg callback: stops the input DMA (sub_5947A8); 1.
void sub_595038(EEContext& ctx);  // 0x595038

// Releases the sceMpeg path: stops the DMA (sub_594AC0); in recreate mode resets and saves the 72-byte sceMpeg record
//   into 0x9ACB70, else deletes it.
void sub_595060(EEContext& ctx);  // 0x595060

// Restores the 72-byte sceMpeg record from 0x9ACB70.
void sub_595110(EEContext& ctx);  // 0x595110

// On the sceMpeg path, feeds the input chunk to the ring (sub_594EC8); otherwise returns a2.
void sub_595138(EEContext& ctx);  // 0x595138

// On the sceMpeg path, takes n bytes from the ring (sub_594428); otherwise returns a1.
void sub_5951A8(EEContext& ctx);  // 0x5951A8

// Copies two source pieces into the two destination pieces of a ring when they fit; the total, or 0.
void sub_595260(EEContext& ctx);  // 0x595260

// Decodes a picture: through MPV (sub_579078), or on the sceMpeg path the input DMA stop / restart around
//   sceMpegGetPicture (format 2) / sceMpegGetPictureRAW8, one pending picture less (sub_595700), -3 on a sceMpeg
//   error.
void sub_595390(EEContext& ctx);  // 0x595390

// work+4440.
void sub_5954D8(EEContext& ctx);  // 0x5954D8

// sceMpeg path: counts the picture start codes of an input chunk, carrying the last 3 bytes across chunks; a non-
//   picture code or the sequence end (0xB7) completes the stream (sub_589FD0, sub_58A038, sub_595208).
void sub_5954E8(EEContext& ctx);  // 0x5954E8

// One pending picture less (work+4404).
void sub_595700(EEContext& ctx);  // 0x595700

// Whether the sceMpeg path has input enough: always without it; else at the end (+4424 = 1) or with 3 pictures
//   pending.
void sub_595718(EEContext& ctx);  // 0x595718

// Request (+76) = 3 (stop).
void sub_5959D0(EEContext& ctx);  // 0x5959D0

// Checks the work marker (sub_595B58) and clears the get-frame callback 0x7B47BC.
void sub_595B30(EEContext& ctx);  // 0x595B30

// The marker 0x7CA280 must be 0x5A5A5A5A (error -16776703).
void sub_595B58(EEContext& ctx);  // 0x595B58

// The status step of an SFD handle: when the time was updated (+68), runs the status's handler (1 sub_595E68, 2
//   sub_595E98, 3 sub_596230, 4 sub_5962D0, 6 sub_596340) between two clock reads (profile +14176).
void sub_595D10(EEContext& ctx);  // 0x595D10

// The pre-step of statuses 2..4: sub_595E50, then the header object's step (sub_598640).
void sub_595E28(EEContext& ctx);  // 0x595E28

// sub_59BB88(handle, 2).
void sub_595E50(EEContext& ctx);  // 0x595E50

// Status 1: to status 2 when the request is 2..4 or 6.
void sub_595E68(EEContext& ctx);  // 0x595E68

// Status 2 (preparing): when the inputs are ready (sub_595F58), the params (sub_596008); request 3 -> 3, 2 -> 2, 4 /
//   6 -> 4 when ready to start (sub_596348, sub_597340) else 3.
void sub_595E98(EEContext& ctx);  // 0x595E98

// Whether the audio (param 5) and video (param 6) inputs are ready (sub_59BC88 / sub_59BCB8).
void sub_595F58(EEContext& ctx);  // 0x595F58

// The stream params: sub_596038, sub_5960E0, sub_596168.
void sub_596008(EEContext& ctx);  // 0x596008

// The audio / video presence params (sub_589550 / sub_589530) and their copy into the header object (+3512 / +3516).
void sub_596038(EEContext& ctx);  // 0x596038

// Adjusts the sync param 15 from the video / audio presence (sub_599240).
void sub_5960E0(EEContext& ctx);  // 0x5960E0

// The sync-master param 25 from the video / audio presence (audio clock when there is one, sub_5A1B58, param 72).
void sub_596168(EEContext& ctx);  // 0x596168

// Status 3 (ready): request 2 -> 2, 3 -> 3, 4 / 6 -> 4 when ready to start (sub_596348, sub_597340).
void sub_596230(EEContext& ctx);  // 0x596230

// Status 4 (playing): the end checks (sub_596898) and the frame step (sub_5963B0); request 6 -> 6.
void sub_5962D0(EEContext& ctx);  // 0x5962D0

// Whether playback may start: 1 unless params 14 and 5 are set, +4064 is clear and +4092 is below param 45 (+2752);
//   then the input end (sub_596978).
void sub_596348(EEContext& ctx);  // 0x596348

// Under the lock: the frame step: shows the next frame when due (sub_596460) or releases the shown one (sub_5965E0),
//   sub_595868.
void sub_5963B0(EEContext& ctx);  // 0x5963B0

// Whether the next frame is due: playing, not paused, the inputs flowing (sub_5966C0, sub_589D30, sub_59BCD0,
//   sub_596760), the time (sub_59A168) against the frame time (sub_59A560).
void sub_596460(EEContext& ctx);  // 0x596460

// Whether an input has run dry: param 5 / 6 inputs (sub_59BCB8) or any of the 8 streams (sub_589D10).
void sub_5966C0(EEContext& ctx);  // 0x5966C0

// Play-end checks: the end time (sub_596908), the input end (sub_596978), the video end (sub_596A40), the audio end
//   (sub_596A98); any one ends it (sub_596B28).
void sub_596898(EEContext& ctx);  // 0x596898

// Whether the end time (params 20 / 21) is reached (sub_59A168, sub_56F4B8).
void sub_596908(EEContext& ctx);  // 0x596908

// The input end by the sync master (param 25): video, audio, both or either.
void sub_596978(EEContext& ctx);  // 0x596978

// The video end while playing (sub_599E08).
void sub_596A40(EEContext& ctx);  // 0x596A40

// The audio end while playing: the audio time (sub_59A028) against param 54 (sub_59A560).
void sub_596A98(EEContext& ctx);  // 0x596A98

// Creates an SFD handle: the creation params (sub_596CC0), a free table slot (sub_596D28; error -16776698), the
//   handle (sub_596D68), kept in the table 0x7B4774.
void sub_596C28(EEContext& ctx);  // 0x596C28

// Checks the creation params: a work buffer (+4; error -16776700) of at least 0x37D0 bytes (+64; error -16776699).
void sub_596CC0(EEContext& ctx);  // 0x596CC0

// The first free slot of the 8-handle table 0x7B4774; -1 when full.
void sub_596D28(EEContext& ctx);  // 0x596D28

// Builds an SFD handle in the 32-aligned work buffer: clears it, copies the 68-byte creation params, initialises its
//   parts (the header info, sub_596F98, sub_597000, sub_597088, the error record, the two 400-byte param tables from
//   0x7B4570, the time record, the streams sub_588740, the transfers sub_59B620, the header object, status 3); the
//   handle or 0.
void sub_596D68(EEContext& ctx);  // 0x596D68

// Resets the decode-info record (handle+2316).
void sub_596F98(EEContext& ctx);  // 0x596F98

// Resets the counters record (handle+2384) and its four 24-byte sub-records.
void sub_597000(EEContext& ctx);  // 0x597000

// Clears 24 bytes (three 64-bit words).
void sub_597078(EEContext& ctx);  // 0x597078

// Resets the profile record (handle+14016): six timing slots (sub_59B490) and the totals.
void sub_597088(EEContext& ctx);  // 0x597088

// Adds a1 to the decoded-picture count (handle+2384) and calls the counter callback (param) with (handle, a2,
//   counters).
void sub_597100(EEContext& ctx);  // 0x597100

// sub_59BB88(handle, 3).
void sub_5971D0(EEContext& ctx);  // 0x5971D0

// Destroys an SFD handle: handle check (error -16776911), stop (sub_5973C0), the header info (sub_58B158), the
//   streams (sub_588A10), reset (sub_597288), removed from the table 0x7B4774.
void sub_5971E8(EEContext& ctx);  // 0x5971E8

// Status and request 0, then sub_59BB88.
void sub_597288(EEContext& ctx);  // 0x597288

// Request (+76) = 4 (start).
void sub_597330(EEContext& ctx);  // 0x597330

// sub_59BC20(handle, 7, 6, 0, 0).
void sub_597340(EEContext& ctx);  // 0x597340

// Stops a handle: unless at status 1, stops the transfers (my_malloc_1) and rebuilds the handle in recreate mode
//   (0x7B476C, sub_5974A8).
void sub_5973C0(EEContext& ctx);  // 0x5973C0

// Sets the recreate switch 0x7B476C.
void sceInsockSetErrnoMode_1(EEContext& ctx);  // 0x597428

// Stops the transfers when playing (sub_59BC20); on success status and request 1.
void my_malloc_1(EEContext& ctx);  // 0x597448

// Rebuilds a stopped handle in place: saves the creation params and its settings, resets, re-creates it (sub_596D68;
//   error -16776702) and restores the param tables and the settings (sub_58E670, sub_597878 ..).
void sub_5974A8(EEContext& ctx);  // 0x5974A8

// Get-frame (transfer 6, command 11): handle check (error -16776906), API mode 1 (sub_597DC8); first frame's clock;
//   the callback 0x7B47BC.
void sub_597C28(EEContext& ctx);  // 0x597C28

// Release-frame (transfer 6, command 12): handle check (error -16776905), API mode 1, the released count.
void sub_597D20(EEContext& ctx);  // 0x597D20

// Claims the handle's API mode (+88): sets it when free; another mode is an error.
void sub_597DC8(EEContext& ctx);  // 0x597DC8

// Handle check (error -16776903), then sub_588D38.
void sub_597E20(EEContext& ctx);  // 0x597E20

// Clears a 20-byte record.
void sub_597E80(EEContext& ctx);  // 0x597E80

// The time of a stream position (stream record handle+4936 + 116 i, sub_598030; error -16776159).
void sub_597FA0(EEContext& ctx);  // 0x597FA0

// The time stamp of a stream address (sub_598140), relative to the stream's window.
void sub_5980C8(EEContext& ctx);  // 0x5980C8

// Whether a stream's time-stamp queue is full.
void sub_5982A0(EEContext& ctx);  // 0x5982A0

// Resets the header-object record: +8 = -3, +12 = 1.
void sub_5982E0(EEContext& ctx);  // 0x5982E0

// With a header object, its step (sub_598688, sub_598EE8).
void sub_598640(EEContext& ctx);  // 0x598640

// Resets the time record: the six time-source callbacks (0x59A298, 0x59A2E0, -, 0x59A340, -, 0x59A360), the time
//   windows (sub_599A30), counters and the defaults (1000, 100, -5, -1.0f ...).
void sub_599810(EEContext& ctx);  // 0x599810

// The audio time plus the pause offset (sub_59A150, sub_57BAF0).
void sub_59A028(EEContext& ctx);  // 0x59A028

// Time code to time: (h x 3600 + m x 60 + s) x rate + 1,000 x (f + extra) + 500 x field; the unit is a1.
void sub_59A910(EEContext& ctx);  // 0x59A910

// sub_59A910 at rate 30,000; then the unit word = a0.
void sub_59A9D8(EEContext& ctx);  // 0x59A9D8

// The frame rate of the handle's sequence (0x7CA2C0[code]); handle check (error -16776933).
void sub_59AD80(EEContext& ctx);  // 0x59AD80

// With a frame: whether its time is due (sub_59AEC0).
void sub_59AE88(EEContext& ctx);  // 0x59AE88

// Whether a time is due (sub_59B048), always unless param 14 is clear.
void sub_59AEC0(EEContext& ctx);  // 0x59AEC0

// Compares a time with the play clock (sub_59A168): at the stop clock -> due; otherwise scaled to 1/10000 units,
//   exact (param 15 = 1) or with tolerance (sub_59B210).
void sub_59B048(EEContext& ctx);  // 0x59B048

// The due decision with a tolerance window (+2756) and the 59.94 Hz frame-repeat rule.
void sub_59B210(EEContext& ctx);  // 0x59B210

// The current clock: the last handle's time source (+4100) or the vsync count x 1,000 at rate 0x7B4728; or the timer
//   (sub_5A1B80 / sub_5A1A30).
void sub_59B3A8(EEContext& ctx);  // 0x59B3A8

// Initialises the 9 transfer slots (68 bytes) from the creation's table and connects them (sub_59B720; error
//   -16776446).
void sub_59B620(EEContext& ctx);  // 0x59B620

// Resets a transfer slot.
void sub_59B6D8(EEContext& ctx);  // 0x59B6D8

// Connects the transfer graph for the streams present: system, video only, audio only or user data.
void sub_59B720(EEContext& ctx);  // 0x59B720

// The system-stream graph: the video and audio chains when present, the user-data link.
void sub_59B840(EEContext& ctx);  // 0x59B840

// The video chain: 1 -> 2 -> 3, then 3 -> 6 or 3 -> 4 -> 5 -> 6.
void sub_59B930(EEContext& ctx);  // 0x59B930

// The audio chain: 2 -> 3 -> 4, then 4 -> 7 or 4 -> 5 -> 6 -> 7.
void sub_59B9D0(EEContext& ctx);  // 0x59B9D0

// Link 7 -> 8 (sub_59BB50).
void sub_59BA70(EEContext& ctx);  // 0x59BA70

// A link variant (tail into the shared code at 0x59BB10).
void sub_59BA90(EEContext& ctx);  // 0x59BA90

// A link variant (tail into the shared code at 0x59BB10).
void sub_59BAB0(EEContext& ctx);  // 0x59BAB0

// A link variant (tail into the shared code at 0x59BB10).
void sub_59BAD0(EEContext& ctx);  // 0x59BAD0

// Links slot a1 to slot a2: the slot's input (handle+8000 + 68 a2) = a1, the stream's output (handle+4960 + 116 a1) =
//   a2.
void sub_59BB50(EEContext& ctx);  // 0x59BB50

// Pushes a sample into a ring-average record and stores the new average (+420, +424).
void sub_59C358(EEContext& ctx);  // 0x59C358

// The average of a ring-average record's samples.
void sub_59C418(EEContext& ctx);  // 0x59C418

// Profiler log: copies the column titles (0x7CA330) into the log buffer 0x7B47DC.
void sub_59C480(EEContext& ctx);  // 0x59C480

// Profiler log: one sprintf line of a handle's counters into the log buffer; wraps 1 KiB before its end.
void sub_59C5E0(EEContext& ctx);  // 0x59C5E0

}  // namespace p3fes::game
