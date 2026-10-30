// Phase 5 slice libs23: the leftover CRI Sofdec entry points 0x58C138-0x5A1518 that nothing in the game calls (no
// callers, no data references): the SFD API's stubs and "unsupported" raisers, the per-handle getters / setters
// behind the SFD handle check (sub_58C060, errors through sub_58BE40), the frame-lock counters, the header-object
// queries, the transfer-slot 8 entry setter, the 23.976 drop-frame time-code conversions, the frame-buffer layout
// helpers, the SFD server sweep, and the "<SUDPS_>" tag helpers. Register-ABI bodies started from p3fes_handgen
// (arguments in $a0.., the result in $v0; every statement, charge and check point is the generator's:
// game/include/p3fes/game/hg_cpu.h). Each declaration carries the function's role, read from the instructions; the
// error codes are the values passed to sub_58BE40. No CRI material was opened. The offsets come from tail1.h's sfd::
// / sfdinfo::, libs5.h's sfdh:: and libs13.h's sfd:: / vdec:: / vibuf::; this slice adds the few below.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/libs13.h"
#include "p3fes/game/libs5.h"
#include "p3fes/game/tail1.h"

namespace p3fes::game {

namespace libs23 {
// SFD handle words this slice adds (the handle is tail1::sfd's 0x37B0-byte record)
namespace sfd {
constexpr s32 kFrameLocks = 2432;   // s32: frame locks held in all (sub_593730 adds one, sub_5937D0 takes one)
constexpr s32 kTimeTick = 676;      // s32, in the time record (libs5::sfdh::kTimeRec): sub_59A4A8 counts it
constexpr s32 kTimeSet = 688;       // s32, in the time record: sub_59AEF8 counts it and stores the pair below
constexpr s32 kTimeSetA = 692;      // s32: its first value
constexpr s32 kTimeSetB = 696;      // s32: its second value
constexpr s32 kTimeUnit = 684;      // s32, in the time record: the unit sub_59ADF8 scales by (criMulDiv x 1000)
constexpr s32 kTimeSrc = 2336;      // s32: the time-source index (sub_59ADF8 reads the rate table 0x7CA2C0 by it)
constexpr s32 kParaClock = 56;      // in the parameter table (libs5::sfdh::kPara): param 14's word (sub_59AF80)
constexpr s32 kParaClockArg = 180;  // param 45's word, passed to sub_59B048 in $t0
constexpr s32 kRec3544 = 3544;      // the stride of the records sub_598300 initialises
}  // namespace sfd
// The header object (handle + libs13::sfd::kHdrObj)
namespace hdr {
constexpr s32 kNoParam5 = 3512;     // s32: 0 = parameter 5 is cleared by sub_598C28
constexpr s32 kNoParam6 = 3516;     // s32: 0 = parameter 6 is cleared by sub_598C28
constexpr s32 kUserWord = 3520;     // s32: set by sub_5984C8
}  // namespace hdr
// The handle's 12-byte record that sub_598C28 copies in (handle + 14004..14015)
constexpr s32 kStartRec = 14004;
constexpr s32 kStartRecW2 = 14012;
// A frame record (libs13::frm): its lock count
constexpr s32 kFrmLocks = 4;
// The 36-byte frame-buffer configuration (sub_58E260 copies one to 0x9ACAF0; sub_58E400 lays its planes out)
namespace fbcfg {
constexpr u32 kGlobal = 0x9ACAF0u;  // the copy
constexpr u32 kClear8 = 0x9ACB18u;  // 8 bytes cleared with it
constexpr u32 kClear64 = 0x9ACB20u; // 64 bytes cleared with it
constexpr s32 kWidth = 0;           // s32: pixels
constexpr s32 kHeight = 4;          // s32: pixels
constexpr s32 kSize16 = 16;         // s32: rounded up to 64 by sub_58E260
constexpr s32 kBase = 32;           // u32: the buffer base, rounded up to 64 by sub_58E260
}  // namespace fbcfg
// The three-plane record of sub_5A0050 / sub_5A00D8: Y, Cb, Cr at +4 / +20 / +36, 16 bytes each, size word +8
namespace planes {
constexpr s32 kY = 4;
constexpr s32 kCb = 20;
constexpr s32 kCr = 36;
constexpr s32 kYPitch = 12;
constexpr s32 kCbPitch = 28;
constexpr s32 kCrPitch = 44;
}  // namespace planes
// The stepping record of sub_59EAA8 / sub_59EAD0: {u32 pointer, ?, s32 count, s32 step}
namespace step {
constexpr s32 kPtr = 0;
constexpr s32 kCount = 8;
constexpr s32 kStep = 12;
}  // namespace step
// Globals
constexpr u32 kErrno = 0x7B491Cu;   // u32: WTLS_set_table_2 sets it, __errno_14 returns it
constexpr u32 kPairA = 0x7B47DCu;   // u32: sub_59C468's first argument
constexpr u32 kPairB = 0x7B47D8u;   // u32: its second
constexpr u32 kRateTable = 0x7CA2C0u;  // s32[]: by time-source index (sub_59ADF8)
// The "<SUDPS_>" tag strings
constexpr u32 kStrTag = 0x7CABA8u;   // "<SUDPS_>"
constexpr u32 kStrHex = 0x7CABB8u;   // "<%06X>"
constexpr u32 kStr02 = 0x7CABC0u;    // "02"
constexpr u32 kStrNl = 0x7CABC8u;    // "\n"
constexpr u32 kStrA = 0x7CABD0u;     // "A"
constexpr u32 kStrP = 0x7CAC00u;     // "P"
constexpr u32 kStrI = 0x7CAC08u;     // "I"
}  // namespace libs23

// Five SFD stubs: return 0.
void sub_58C138(EEContext& ctx);  // 0x58C138
void sub_58C178(EEContext& ctx);  // 0x58C178
void sub_58C180(EEContext& ctx);  // 0x58C180
void sub_58C188(EEContext& ctx);  // 0x58C188
void sub_58C190(EEContext& ctx);  // 0x58C190
// Copies a 36-byte frame-buffer configuration ($a0) to 0x9ACAF0, rounds its words +16 and +32 up to 64, then clears
//   8 bytes at 0x9ACB18 and 64 bytes at 0x9ACB20 (memset; the second as a tail call).
void sub_58E260(EEContext& ctx);  // 0x58E260
// Lays out a frame buffer from a configuration ($a0: width +0, height +4, base +32) into $a1: macroblocks rounded up
//   (16 pixels); the Y pitch (16 x columns) and C pitch (8 x columns) rounded up to 64 as u16 at +14 / +12; +8 = base;
//   +0 = base + 1,024 x (Y pitch / 64) x rows; +4 = that + 512 x (C pitch / 64) x rows.
void sub_58E400(EEContext& ctx);  // 0x58E400
// Handle check (error 0xFF000184), then sub_5793E8 on the MPV handle of the handle's video decoder with $a1..$t0;
//   returns 0.
void sub_58E758(EEContext& ctx);  // 0x58E758
// mpvFinish (sub_57B418); returns 0.
void r_lock_def_free_7(EEContext& ctx);  // 0x58EA40
// Four SFD stubs: return 0.
void sub_5930E0(EEContext& ctx);  // 0x5930E0
void sub_5930E8(EEContext& ctx);  // 0x5930E8
void sub_5930F0(EEContext& ctx);  // 0x5930F0
void sub_5930F8(EEContext& ctx);  // 0x5930F8
// "Unsupported": reports 0xFF000F0D for the handle in $a0 (sub_58BE40, a tail call).
void sub_593100(EEContext& ctx);  // 0x593100
void sub_593120(EEContext& ctx);  // 0x593120
// Video decoder setup step: sub_593608(handle, its video-decoder work, a stack word); its non-zero result is
//   returned; otherwise the skip mode (vdec +116) = 2 and vdec +120 = 200 when the stack word and parameter 48 are
//   set, else 192; returns 0.
void sub_593598(EEContext& ctx);  // 0x593598
// Locks the frame whose output record is $a1 (sub_593878): handle check (0xFF000188); its lock count +4 goes up, or
//   0xFF000F30 when none; the handle's lock total (+2432) goes up either way and is returned.
void sub_593730(EEContext& ctx);  // 0x593730
// Unlocks the frame whose output record is $a1: handle check (0xFF000189); its lock count +4 goes down (not below
//   0), or 0xFF000F31 when none; the handle's lock total (+2432) goes down either way and is returned.
void sub_5937D0(EEContext& ctx);  // 0x5937D0
// The video-input ring's positions (vdec +4504): *$a1 = its size in bytes (+24); *$a3 = sector word +12 x 2,048;
//   *$a2 = ((+12 + +16) x 2,048 + bytes buffered +20) mod size (break 7 for a zero size); *$t0 = +16 x 2,048 + +20.
void sub_594BD0(EEContext& ctx);  // 0x594BD0
// The sceMpeg record of the handle's video decoder (vdec +4432).
void sub_595770(EEContext& ctx);  // 0x595770
// Its size: 72.
void sub_595780(EEContext& ctx);  // 0x595780
// Empty.
void nullsub_177(EEContext& ctx);  // 0x595BB8
// The SFD server sweep: the status step (sub_595D10) of every valid handle in the 8-handle table 0x7B4774 (sub_58C060
//   accepts it), then sub_596B68 (a tail call).
void sub_595CB8(EEContext& ctx);  // 0x595CB8
// 1 when transfer slot 0's stream (+8004) has ended (sub_589D10), else 0.
void sub_5979F8(EEContext& ctx);  // 0x5979F8
// Initialises $a1 records of 3,544 bytes from $a0 (sub_598348 on each); nothing for $a1 <= 0.
void sub_598300(EEContext& ctx);  // 0x598300
// Handle check (0xFF000152); the header object's word +3520 = $a1.
void sub_5984C8(EEContext& ctx);  // 0x5984C8
// Handle check (0xFF000153); parameter 47 = 1 (sub_599240), then the stop request (sub_5959D0, a tail call).
void sub_598528(EEContext& ctx);  // 0x598528
// *$a1 = 0; handle check (0xFF000154); sub_5985F8(header object, $a1); returns 0.
void sub_598588(EEContext& ctx);  // 0x598588
// *$a1 = 0; handle check (0xFF000155); sub_598980(header object, $a1); returns 0.
void sub_598910(EEContext& ctx);  // 0x598910
// *$a3 = 0; handle check (0xFF000156); when the header object holds a record (sub_598980 into a stack word),
//   sub_598A90(header object, $a1, $a2, $a3); returns 0.
void sub_5989F0(EEContext& ctx);  // 0x5989F0
// *$a2 = 0, *$a3 = 1; handle check (0xFF000157); when the header object holds a record (sub_598980),
//   sub_598B90(header object, $a1, $a2, $a3); returns 0.
void sub_598AE8(EEContext& ctx);  // 0x598AE8
// Handle check (0xFF000158); with a header object: stops the handle (sub_5973C0; its non-zero result is returned),
//   parameter 47 = 0, parameters 5 / 6 = 0 when the header object's +3512 / +3516 are 0, copies the 12 bytes at $a1
//   to handle +14004, then method 13 of every transfer slot (sub_59BB88, a tail call).
void sub_598C28(EEContext& ctx);  // 0x598C28
// Handle check (0xFF00011C); the header-sector copy: when a header was parsed (+120), *$a1 = the copy (+268) and
//   *$a2 = its size (+264), else both 0; returns 0.
void sub_599760(EEContext& ctx);  // 0x599760
// Handle check (0xFF000127), then the time (sub_59A150, a tail call).
void sub_59A0D8(EEContext& ctx);  // 0x59A0D8
// Handle check (0xFF000128), then the time through the time source (sub_59A200, a tail call).
void sub_59A188(EEContext& ctx);  // 0x59A188
// Handle check (0xFF000122); counts the time record's word +676 and marks the time updated (+68 = 1).
void sub_59A4A8(EEContext& ctx);  // 0x59A4A8
// Time code to time (sub_59A910) with $a0 = 24,000; *$a3 = the caller's $a0.
void sub_59A9A0(EEContext& ctx);  // 0x59A9A0
// 23.976 drop-frame time code ($a1: hours +8, minutes +12, seconds +16, frames +20, extra +24, s16 fields +30) to
//   time: (86,292 h + 1,438 m + 2 (m / 10) + 24 s + frames + extra) x 1,000 + 500 x fields into *$a2; *$a3 = $a0.
void sub_59AA48(EEContext& ctx);  // 0x59AA48
// *$a1 = -1; handle check (0xFF000118); with a time source (+2336): *$a1 = criMulDiv(rate 0x7CA2C0[source], the time
//   record's +684, 1,000) and returns 0.
void sub_59ADF8(EEContext& ctx);  // 0x59ADF8
// Handle check (0xFF000125); counts the time record's +688, stores $a1 / $a2 at +692 / +696, marks the time updated.
void sub_59AEF8(EEContext& ctx);  // 0x59AEF8
// *$a3 = 0; handle check (0xFF000126); without parameter 14: *$a3 = 1; else with start requested (+76 = 4) the clock comparison
//   sub_59B048($a0..$a3, $t0 = parameter 45) and 0; otherwise *$a3 = 0.
void sub_59AF80(EEContext& ctx);  // 0x59AF80
// 0x7B47DC = $a0, 0x7B47D8 = $a1.
void sub_59C468(EEContext& ctx);  // 0x59C468
// Transfer slot 8's entry $a1: handle check (0xFF000192); error 0xFF000602 when its stream (+8544) is 8; else
//   sfdSetEntry(work +8536 + 16 $a1 + 4, $a2, 0, $a3, $t0) and sub_588F48(handle, stream, $a1, the entry); returns 0.
void sub_59C7B8(EEContext& ctx);  // 0x59C7B8
// Seven SFD stubs: return 0.
void sub_59C9F8(EEContext& ctx);  // 0x59C9F8
void sub_59CC50(EEContext& ctx);  // 0x59CC50
void sub_59CD00(EEContext& ctx);  // 0x59CD00
void sub_59CEC8(EEContext& ctx);  // 0x59CEC8
void sub_59CED0(EEContext& ctx);  // 0x59CED0
void sub_59CED8(EEContext& ctx);  // 0x59CED8
void sub_59CEE0(EEContext& ctx);  // 0x59CEE0
// "Unsupported": reports 0xFF000701 for the handle in $a0 (sub_58BE40, a tail call).
void sub_59CEE8(EEContext& ctx);  // 0x59CEE8
void sub_59CF08(EEContext& ctx);  // 0x59CF08
// Reverses a stepping record: pointer +0 += step +12 x (count +8 - 1), step = -step (returned).
void sub_59EAA8(EEContext& ctx);  // 0x59EAA8
void sub_59EAD0(EEContext& ctx);  // 0x59EAD0
// 0x7B491C = $a0.
void WTLS_set_table_2(EEContext& ctx);  // 0x59FD70
// The word 0x7B491C.
void __errno_14(EEContext& ctx);  // 0x59FD80
// The record at $a0 +36: its word +72 = $a1.
void sub_59FDA0(EEContext& ctx);  // 0x59FDA0
// The word $a0 +52.
void sub_59FE58(EEContext& ctx);  // 0x59FE58
// Three planes ($a0 +4 / +20 / +36) by sub_5A00B0: the Y plane with $a1 rounded down to even, Cb and Cr with half.
void sub_5A0050(EEContext& ctx);  // 0x5A0050
// The three plane pitches: +12 = $a1 rounded down to even, +28 and +44 = half of it.
void sub_5A00D8(EEContext& ctx);  // 0x5A00D8
// When the word $a0 +8 is 1: *$a1 = +12, *$a2 = +16; else both 0.
void sub_5A04C0(EEContext& ctx);  // 0x5A04C0
// The word +4 of the record at $a0 +36.
void sub_5A10F8(EEContext& ctx);  // 0x5A10F8
// Writes a "<SUDPS_>" tag at $a0: the 8 tag bytes (strncpy), "<000013>" appended (sprintf "<%06X>" of 19, strcat);
//   at $a0 +16: the number "02" (strncpy 2), the three index characters (sub_5A1218 with $a2), then "\n" appended.
void sub_5A1188(EEContext& ctx);  // 0x5A1188
// For a SUD tag ($a0 non-null, $a1 >= 0) whose number (+16, sub_5A12F8) is non-zero: 1 when byte +20 is 'I'; else 0.
void sub_5A13C0(EEContext& ctx);  // 0x5A13C0
// For a SUD tag whose number (+16, sub_5A12F8) is at least 2: byte +21 'P' gives 1, 'I' 2, others 0; else 0.
void sub_5A1420(EEContext& ctx);  // 0x5A1420
// For a SUD tag whose number (+16, sub_5A12F8) is at least 2: 1 when byte +22 is not 'A'; else 0.
void sub_5A14B0(EEContext& ctx);  // 0x5A14B0
// For a SUD tag whose number (+16, sub_5A12F8) is at least 2: the three characters at +23 read as hexadecimal
//   (sub_5A1778 with base 16 on a stack copy), sign-extended; else 0.
void sub_5A1518(EEContext& ctx);  // 0x5A1518

}  // namespace p3fes::game
