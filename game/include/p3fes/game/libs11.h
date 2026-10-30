// Phase 5 slice libs11 (game/src/cri/libs11.cpp): the register-ABI bodies (arguments in $a0.., result in $v0) of the
// CRI middleware band 0x550808-0x55F670, and the record layouts their named offsets use. Every offset below is read
// from the instructions of the bodies that use it; a name with the offset in it (kWord448) is a field whose role the
// slice has not established.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs11 {

// The AIX player handle (the AIXP_* functions; the error strings 'E20030502xx' / 'E2003052xxx' name the API).
namespace aixp {
constexpr s32 kStat = 1;          // u8 status: 1..3 while a stream is attached / parsed / playing (the getters test it)
constexpr s32 kParser = 4;        // the AIX parser record (sub_554820's records)
constexpr s32 kSubPly = 12;       // the sub-player (sub_548AE8 / sub_548EB8 read it)
constexpr s32 kSource = 144;      // the data source object (vtable at +0; slot 36 = the sample count)
constexpr s32 kByte433 = 433;     // u8 set by sub_553408
constexpr s32 kWord448 = 448;     // set / read by sub_553438 / sub_553468
constexpr s32 kRangeStart = 452;  // start of the range set by sub_553498 ($a1)
constexpr s32 kRangeEnd = 456;    // its end ($a1 + $a2); sub_553510 gives back the start and the length
constexpr s32 kSrvState = 476;    // 3 after an attach (sub_552FA0)
constexpr s32 kFloat480 = 480;    // float stored by sub_553310
}  // namespace aixp

// The AIX parser records: 4 of 6492 bytes at 0x79A330 (sub_554820), cleared by sub_554778.
namespace aixparse {
constexpr u32 kRecords = 0x79A330u;
constexpr s32 kRecordSize = 6492;
constexpr s32 kRecordCount = 4;
constexpr s32 kUsed = 0;            // u8: 1 while in use
constexpr s32 kStat = 1;            // u8 parse status: 2 header read, 3 end chunk, 4 error
constexpr s32 kNumTrk = 2;          // u8 track count (the create argument)
constexpr s32 kNumPly = 3;          // u8 track players at +12..
constexpr s32 kMode = 4;            // u8
constexpr s32 kBytes = 8;           // bytes consumed from the source
constexpr s32 kSource = 28;         // the source object (vtable: 24 = get chunk, 28 = put back, 32 = consume, 36 = size)
constexpr s32 kTrkStream = 32;      // the track streams (u32 each)
constexpr s32 kHeader = 160;        // the parsed header (sub_554AE8; reset by sub_554EA0, 6328 bytes)
constexpr s32 kHdrNumTrk = 688;     // in the parser header area: the track count (word)
constexpr s32 kNumSong = 6452;      // the song count
}  // namespace aixparse

// The PL2 encoder handle (44 bytes in the work area given to sub_55EC38; PL2ENC Ver.1.01).
namespace pl2 {
constexpr s32 kSize = 44;
constexpr s32 kWork = 0;        // the work area as given
constexpr s32 kWorkSize = 4;    // its size (at least 1024)
constexpr s32 kDelay0 = 8;      // the first 384-byte delay line (s32 samples)
constexpr s32 kDelay1 = 12;     // the second one (kDelay0 + 384)
constexpr s32 kRate = 16;       // the sample rate (sub_55F308)
constexpr s32 kPos = 20;        // the delay-line position (wraps at kDelayLen)
constexpr s32 kDelayLen = 24;   // rate / 750 clamped to 1..96
constexpr s32 kGain0 = 28;      // the four gain indices into the table 0x7C5C60 (sub_55F218)
constexpr s32 kGain1 = 32;
constexpr s32 kGain2 = 36;
constexpr s32 kGain3 = 40;
constexpr u32 kGainTable = 0x7C5C60u;
}  // namespace pl2

// The PL2 words of an ADXT stereo channel record (sub_55F390 attaches the encoder there).
namespace adxt_pl2 {
constexpr s32 kPl2 = 232;   // the PL2 encoder handle
constexpr s32 kPos0 = 236;  // the two position arguments given to sub_55F1C8
constexpr s32 kPos1 = 240;
}  // namespace adxt_pl2

// The SRD read request (sub_557C70 queues one, sub_558320 serves it on the host).
namespace srd {
constexpr s32 kMode = 1;     // u8: 2 once a read is queued
constexpr s32 kStat = 2;     // u8: 0 idle, 1 queued, 2 reading, 3 done, 9 error
constexpr s32 kCancel = 4;   // 1 asks the server to drop the request
constexpr s32 kBuf = 24;     // the destination buffer
constexpr s32 kSize = 32;    // u64 bytes to read
constexpr s32 kOffset = 40;  // u64 sector offset (<< 11 for the seek)
constexpr s32 kFd = 48;      // the host descriptor
constexpr s32 kErr = 52;     // the negative result of a failed seek / read / ioctl
}  // namespace srd

// The sector file handle (13 of 48 bytes at 0x7A2C80; the 'E0092712:handl is null.' functions).
namespace fsh {
constexpr u32 kHandles = 0x7A2C80u;
constexpr s32 kHandleSize = 48;
constexpr s32 kStat = 2;     // u8: 0 idle, 1 read done, 2 reading, 3 error
constexpr s32 kSize = 8;     // u64 file size in bytes
constexpr s32 kNsct = 16;    // file size in sectors
constexpr s32 kWord20 = 20;  // cleared by a read request
constexpr s32 kFd = 24;      // the descriptor given to the SRD request
constexpr s32 kPos = 28;     // the sector position
constexpr s32 kBuf = 32;     // the read buffer
constexpr s32 kNreq = 36;    // sectors asked
constexpr s32 kNread = 40;   // sectors read
constexpr s32 kSrd = 44;     // the SRD request in flight
}  // namespace fsh

// The LSC (stream queue) handle: a ring of 16 stream entries of 32 bytes at +56.
namespace lsc {
constexpr s32 kStat = 1;     // u8: 1 at the queue end, 3 on a reader error
constexpr s32 kSvr = 2;      // u8: 1 while the head stream runs
constexpr s32 kLoop = 3;     // u8: 1 = re-queue each finished stream
constexpr s32 kWord20 = 20;
constexpr s32 kWord24 = 24;
constexpr s32 kHead = 32;    // the head slot of the ring
constexpr s32 kCount = 36;   // streams queued
constexpr s32 kFp = 40;      // the reader
constexpr s32 kPos = 44;     // the head stream's start position
constexpr s32 kQueue = 56;   // the ring
constexpr s32 kEntSize = 32;
constexpr s32 kEntries = 16;
namespace ent {
constexpr s32 kId = 0;       // the stream id
constexpr s32 kName = 4;     // the file name
constexpr s32 kSum = 8;      // the byte sum of the name (checked before the start)
constexpr s32 kOffset = 12;
constexpr s32 kSize = 16;
constexpr s32 kWord20 = 20;  // the start position
constexpr s32 kStat = 24;    // 1 running, 2 done
constexpr s32 kPos = 28;     // the reader position
}  // namespace ent
}  // namespace lsc

}  // namespace libs11

void sub_550808(EEContext& ctx);  // 0x550808 (register ABI: arguments in $a0.., the result in $v0)
void sub_5509F8(EEContext& ctx);  // 0x5509F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_550BE8(EEContext& ctx);  // 0x550BE8 (register ABI: arguments in $a0.., the result in $v0)
void sub_550DD8(EEContext& ctx);  // 0x550DD8 (register ABI: arguments in $a0.., the result in $v0)
void sub_550FC8(EEContext& ctx);  // 0x550FC8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5511B8(EEContext& ctx);  // 0x5511B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_551980(EEContext& ctx);  // 0x551980 (register ABI: arguments in $a0.., the result in $v0)
void sub_551988(EEContext& ctx);  // 0x551988 (register ABI: arguments in $a0.., the result in $v0)
void sub_552000(EEContext& ctx);  // 0x552000 (register ABI: arguments in $a0.., the result in $v0)
void sub_552010(EEContext& ctx);  // 0x552010 (register ABI: arguments in $a0.., the result in $v0)
void sub_552020(EEContext& ctx);  // 0x552020 (register ABI: arguments in $a0.., the result in $v0)
void sub_5523F8(EEContext& ctx);  // 0x5523F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_552478(EEContext& ctx);  // 0x552478 (register ABI: arguments in $a0.., the result in $v0)
void sub_552494(EEContext& ctx);  // 0x552494 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524A8(EEContext& ctx);  // 0x5524A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524B8(EEContext& ctx);  // 0x5524B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524C8(EEContext& ctx);  // 0x5524C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524D0(EEContext& ctx);  // 0x5524D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524D8(EEContext& ctx);  // 0x5524D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5524F0(EEContext& ctx);  // 0x5524F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_552538(EEContext& ctx);  // 0x552538 (register ABI: arguments in $a0.., the result in $v0)
void sub_552550(EEContext& ctx);  // 0x552550 (register ABI: arguments in $a0.., the result in $v0)
void sub_552558(EEContext& ctx);  // 0x552558 (register ABI: arguments in $a0.., the result in $v0)
void sub_552560(EEContext& ctx);  // 0x552560 (register ABI: arguments in $a0.., the result in $v0)
void sub_552568(EEContext& ctx);  // 0x552568 (register ABI: arguments in $a0.., the result in $v0)
void sub_552570(EEContext& ctx);  // 0x552570 (register ABI: arguments in $a0.., the result in $v0)
void sub_552578(EEContext& ctx);  // 0x552578 (register ABI: arguments in $a0.., the result in $v0)
void sub_552580(EEContext& ctx);  // 0x552580 (register ABI: arguments in $a0.., the result in $v0)
void sub_552588(EEContext& ctx);  // 0x552588 (register ABI: arguments in $a0.., the result in $v0)
void sub_5525A0(EEContext& ctx);  // 0x5525A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5525B8(EEContext& ctx);  // 0x5525B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5525D0(EEContext& ctx);  // 0x5525D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5525E8(EEContext& ctx);  // 0x5525E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_552688(EEContext& ctx);  // 0x552688 (register ABI: arguments in $a0.., the result in $v0)
void sub_552D08(EEContext& ctx);  // 0x552D08 (register ABI: arguments in $a0.., the result in $v0)
void sub_552FA0(EEContext& ctx);  // 0x552FA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5531B8(EEContext& ctx);  // 0x5531B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_553310(EEContext& ctx);  // 0x553310 (register ABI: arguments in $a0.., the result in $v0)
void sub_553358(EEContext& ctx);  // 0x553358 (register ABI: arguments in $a0.., the result in $v0)
void sub_553408(EEContext& ctx);  // 0x553408 (register ABI: arguments in $a0.., the result in $v0)
void sub_553438(EEContext& ctx);  // 0x553438 (register ABI: arguments in $a0.., the result in $v0)
void sub_553468(EEContext& ctx);  // 0x553468 (register ABI: arguments in $a0.., the result in $v0)
void sub_553498(EEContext& ctx);  // 0x553498 (register ABI: arguments in $a0.., the result in $v0)
void sub_553510(EEContext& ctx);  // 0x553510 (register ABI: arguments in $a0.., the result in $v0)
void sub_553560(EEContext& ctx);  // 0x553560 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_143(EEContext& ctx);  // 0x553688 (register ABI: arguments in $a0.., the result in $v0)
void sub_553690(EEContext& ctx);  // 0x553690 (register ABI: arguments in $a0.., the result in $v0)
void sub_553730(EEContext& ctx);  // 0x553730 (register ABI: arguments in $a0.., the result in $v0)
void sub_553788(EEContext& ctx);  // 0x553788 (register ABI: arguments in $a0.., the result in $v0)
void sub_5537E0(EEContext& ctx);  // 0x5537E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_554008(EEContext& ctx);  // 0x554008 (register ABI: arguments in $a0.., the result in $v0)
void sub_5545D8(EEContext& ctx);  // 0x5545D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_554678(EEContext& ctx);  // 0x554678 (register ABI: arguments in $a0.., the result in $v0)
void sub_554778(EEContext& ctx);  // 0x554778 (register ABI: arguments in $a0.., the result in $v0)
void sub_5547C8(EEContext& ctx);  // 0x5547C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_554820(EEContext& ctx);  // 0x554820 (register ABI: arguments in $a0.., the result in $v0)
void sub_5548D0(EEContext& ctx);  // 0x5548D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_554940(EEContext& ctx);  // 0x554940 (register ABI: arguments in $a0.., the result in $v0)
void sub_554950(EEContext& ctx);  // 0x554950 (register ABI: arguments in $a0.., the result in $v0)
void sub_554960(EEContext& ctx);  // 0x554960 (register ABI: arguments in $a0.., the result in $v0)
void sub_554970(EEContext& ctx);  // 0x554970 (register ABI: arguments in $a0.., the result in $v0)
void sub_554980(EEContext& ctx);  // 0x554980 (register ABI: arguments in $a0.., the result in $v0)
void sub_554EA0(EEContext& ctx);  // 0x554EA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_554EF0(EEContext& ctx);  // 0x554EF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_554FD0(EEContext& ctx);  // 0x554FD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_555120(EEContext& ctx);  // 0x555120 (register ABI: arguments in $a0.., the result in $v0)
void sub_555470(EEContext& ctx);  // 0x555470 (register ABI: arguments in $a0.., the result in $v0)
void sub_555738(EEContext& ctx);  // 0x555738 (register ABI: arguments in $a0.., the result in $v0)
void sub_555788(EEContext& ctx);  // 0x555788 (register ABI: arguments in $a0.., the result in $v0)
void sub_557C70(EEContext& ctx);  // 0x557C70 (register ABI: arguments in $a0.., the result in $v0)
void sub_558320(EEContext& ctx);  // 0x558320 (register ABI: arguments in $a0.., the result in $v0)
void sub_5587A8(EEContext& ctx);  // 0x5587A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_558848(EEContext& ctx);  // 0x558848 (register ABI: arguments in $a0.., the result in $v0)
void sub_5589B8(EEContext& ctx);  // 0x5589B8 (register ABI: arguments in $a0.., the result in $v0)
void __errno_6(EEContext& ctx);  // 0x5589F8 (register ABI: arguments in $a0.., the result in $v0)
void __errno_7(EEContext& ctx);  // 0x558A60 (register ABI: arguments in $a0.., the result in $v0)
void sub_559458(EEContext& ctx);  // 0x559458 (register ABI: arguments in $a0.., the result in $v0)
void sub_559648(EEContext& ctx);  // 0x559648 (register ABI: arguments in $a0.., the result in $v0)
void sub_559660(EEContext& ctx);  // 0x559660 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B480(EEContext& ctx);  // 0x55B480 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B5C8(EEContext& ctx);  // 0x55B5C8 (register ABI: arguments in $a0.., the result in $v0)
void atan2l_7(EEContext& ctx);  // 0x55B6E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B798(EEContext& ctx);  // 0x55B798 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B7F8(EEContext& ctx);  // 0x55B7F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B8B0(EEContext& ctx);  // 0x55B8B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55B910(EEContext& ctx);  // 0x55B910 (register ABI: arguments in $a0.., the result in $v0)
void sub_55BA68(EEContext& ctx);  // 0x55BA68 (register ABI: arguments in $a0.., the result in $v0)
void sub_55BCE8(EEContext& ctx);  // 0x55BCE8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55BD70(EEContext& ctx);  // 0x55BD70 (register ABI: arguments in $a0.., the result in $v0)
void sub_55BFE0(EEContext& ctx);  // 0x55BFE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C078(EEContext& ctx);  // 0x55C078 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C0B0(EEContext& ctx);  // 0x55C0B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C370(EEContext& ctx);  // 0x55C370 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C378(EEContext& ctx);  // 0x55C378 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C3E0(EEContext& ctx);  // 0x55C3E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C400(EEContext& ctx);  // 0x55C400 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C430(EEContext& ctx);  // 0x55C430 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C450(EEContext& ctx);  // 0x55C450 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C480(EEContext& ctx);  // 0x55C480 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C548(EEContext& ctx);  // 0x55C548 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C5B8(EEContext& ctx);  // 0x55C5B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C728(EEContext& ctx);  // 0x55C728 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C740(EEContext& ctx);  // 0x55C740 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C798(EEContext& ctx);  // 0x55C798 (register ABI: arguments in $a0.., the result in $v0)
void sub_55C830(EEContext& ctx);  // 0x55C830 (register ABI: arguments in $a0.., the result in $v0)
void sub_55CB30(EEContext& ctx);  // 0x55CB30 (register ABI: arguments in $a0.., the result in $v0)
void sub_55CCE8(EEContext& ctx);  // 0x55CCE8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55CE18(EEContext& ctx);  // 0x55CE18 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D108(EEContext& ctx);  // 0x55D108 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D198(EEContext& ctx);  // 0x55D198 (register ABI: arguments in $a0.., the result in $v0)
void WTLS_set_table(EEContext& ctx);  // 0x55D220 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D400(EEContext& ctx);  // 0x55D400 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D7F0(EEContext& ctx);  // 0x55D7F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D880(EEContext& ctx);  // 0x55D880 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D918(EEContext& ctx);  // 0x55D918 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D9B0(EEContext& ctx);  // 0x55D9B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55DAB0(EEContext& ctx);  // 0x55DAB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55DB20(EEContext& ctx);  // 0x55DB20 (register ABI: arguments in $a0.., the result in $v0)
void __env_unlock_7(EEContext& ctx);  // 0x55DC80 (register ABI: arguments in $a0.., the result in $v0)
void sub_55DDC8(EEContext& ctx);  // 0x55DDC8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55DEF0(EEContext& ctx);  // 0x55DEF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55DFB8(EEContext& ctx);  // 0x55DFB8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55E208(EEContext& ctx);  // 0x55E208 (register ABI: arguments in $a0.., the result in $v0)
void sub_55E318(EEContext& ctx);  // 0x55E318 (register ABI: arguments in $a0.., the result in $v0)
void sub_55E408(EEContext& ctx);  // 0x55E408 (register ABI: arguments in $a0.., the result in $v0)
void sub_55E800(EEContext& ctx);  // 0x55E800 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EAB0(EEContext& ctx);  // 0x55EAB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EAF0(EEContext& ctx);  // 0x55EAF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EB38(EEContext& ctx);  // 0x55EB38 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EB68(EEContext& ctx);  // 0x55EB68 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EBA8(EEContext& ctx);  // 0x55EBA8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EBD8(EEContext& ctx);  // 0x55EBD8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EBF0(EEContext& ctx);  // 0x55EBF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EC38(EEContext& ctx);  // 0x55EC38 (register ABI: arguments in $a0.., the result in $v0)
void sub_55ED38(EEContext& ctx);  // 0x55ED38 (register ABI: arguments in $a0.., the result in $v0)
void sub_55ED68(EEContext& ctx);  // 0x55ED68 (register ABI: arguments in $a0.., the result in $v0)
void sub_55ED88(EEContext& ctx);  // 0x55ED88 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EDF8(EEContext& ctx);  // 0x55EDF8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55EE58(EEContext& ctx);  // 0x55EE58 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F028(EEContext& ctx);  // 0x55F028 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F218(EEContext& ctx);  // 0x55F218 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F2C8(EEContext& ctx);  // 0x55F2C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F308(EEContext& ctx);  // 0x55F308 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F390(EEContext& ctx);  // 0x55F390 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F4C8(EEContext& ctx);  // 0x55F4C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F598(EEContext& ctx);  // 0x55F598 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F608(EEContext& ctx);  // 0x55F608 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F620(EEContext& ctx);  // 0x55F620 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F658(EEContext& ctx);  // 0x55F658 (register ABI: arguments in $a0.., the result in $v0)
void sub_55F670(EEContext& ctx);  // 0x55F670 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
