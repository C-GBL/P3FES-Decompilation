// Slice libs20 (Phase 5): 100 small CRI middleware and SDK functions (game/src/cri/libs20.cpp), register ABI
// (arguments in $a0.., the result in $v0). Each declaration carries the function's role; names in [brackets] are
// proposals (symbols/deltas/libs20.sym holds the ones the binary's own strings give).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace l20 {
// An ADXT player handle (200 bytes; 16 at 0x787570): the fields the error check sub_54C670 reads.
namespace adxt {
inline constexpr s32 kStat = 1;        // s8: 0 stop, 1 decoding the header, 2 preparing, 3 playing, ...
inline constexpr s32 kSjd = 4;         // u32: the ADXSJD decoder (sub_542008 its state: 3 ended)
inline constexpr s32 kStm = 8;         // u32: the streamer (sub_546368 its state: 4 error), 0 for memory input
inline constexpr s32 kSji = 20;        // u32: the input joint (an SJ object: +0 its function table, +36 its data count)
inline constexpr s32 kChkUnit = 56;    // s32: the error check's unit (limits 5 x and 20 x this many calls)
inline constexpr s32 kErrCode = 96;    // s16: 0, -1 a starved input, -2 a stuck decoder (adxt_GetErrCode)
inline constexpr s32 kLastSmpl = 100;  // s32: the decoded sample count at the last check
inline constexpr s32 kStallCnt = 104;  // s16: checks with the same sample count
inline constexpr s32 kStarveCnt = 106; // s16: checks with under 64 input bytes
inline constexpr s32 kRecover = 109;   // u8: the recovery mode: 0 none, 1 stop, 2 restart from the input
inline constexpr s32 kPause = 114;     // s8: paused (adxt_GetStatPause)
}  // namespace adxt
// A host CI file handle (48 bytes; 13 at 0x7A2C80, sub_55BD70).
namespace htci {
inline constexpr s32 kUsed = 0;        // u8
inline constexpr s32 kCached = 1;      // s8: 1 = served from the file cache (no sceClose)
inline constexpr s32 kTrState = 2;     // u8: >= 2 while a transfer runs
inline constexpr s32 kSize = 8;        // s64: the file size in bytes
inline constexpr s32 kNumSct = 16;     // s32: (size + 2047) >> 11
inline constexpr s32 kIoStat = 20;     // s32: sceIoctl(fd, 1)'s output: 1 while executing
inline constexpr s32 kFd = 24;         // s32: the sceOpen descriptor (the cache offset when cached)
}  // namespace htci
// A memory-file (mfCi) handle (56 bytes; 40 at 0x7A7A18, sub_55E3B0): the file is the memory named "address.size".
namespace mfci {
inline constexpr s32 kUsed = 0;        // s8: 1 in use
inline constexpr s32 kStat = 1;        // s8: 1 complete, 2 transferring
inline constexpr s32 kSctLen = 4;      // s32: the sector length (2048 at open)
inline constexpr s32 kSize = 8;        // s32: the file size in bytes
inline constexpr s32 kNumSct = 12;     // s32: sectors in the file
inline constexpr s32 kPos = 16;        // s32: the position in sectors
inline constexpr s32 kTrBytes = 20;    // s32: the bytes the last read moved
inline constexpr s32 kReqSct = 24;     // s32: the sectors of the last read
inline constexpr s32 kName = 28;       // char[]: the "address.size" name
inline constexpr s32 kRdOfs = 48;      // s32: the read's byte offset
inline constexpr s32 kRdLen = 52;      // s32: the read's byte length
}  // namespace mfci
}  // namespace l20

// ---- ADXT: the locked public entry points (the ADX lock stubs around the adxt_* body) and the error check -----------
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AA80(handle), the decoded sample count of the
// handle's decoder (null: E02080818, -1); returns it. [proposed ADXT_GetDecNumSmpl]
void sub_54AA48(EEContext& ctx);  // 0x54AA48
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AAF0(handle), the decoded input bytes of the
// handle's decoder (null: E04041901, -1); returns it. [proposed ADXT_GetDecDtLen]
void sub_54AAB8(EEContext& ctx);  // 0x54AAB8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AB78(handle, $a1, $a2): sub_542F70 on the
// handle's decoder (null: E04041902). The unlock is a tail call.
void sub_54AB28(EEContext& ctx);  // 0x54AB28
// Stores $a0 in the global word 0x787560, then for each of the 16 ADXT handles (200 bytes at 0x787570) in use (byte +0
// == 1) re-applies every channel's pan (sub_5491B0(h, ch, sub_549310(h, ch)) for ch < +3 channels) and the output
// volume (sub_549390(h, sub_549450(h))): a global output mode that takes effect on the playing handles. [proposed
// ADXT_SetOutputMono]
void sub_54AE80(EEContext& ctx);  // 0x54AE80
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54AFD8(handle), a tail call of sub_542FC0. The
// unlock is a tail call.
void sub_54AFA8(EEContext& ctx);  // 0x54AFA8
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B028(handle), the handle's output object (+12);
// returns it.
void sub_54AFF0(EEContext& ctx);  // 0x54AFF0
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B070(handle, $a1): sub_543020 on the handle's
// decoder (+4). The unlock is a tail call.
void sub_54B030(EEContext& ctx);  // 0x54B030
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B230(handle, fname, $a2, $a3),
// adxt_StartFnameRange: copy the name, request the open. The unlock is a tail call. [proposed ADXT_StartFnameRange]
void sub_54B1D0(EEContext& ctx);  // 0x54B1D0
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54B388(handle, $a1): sub_54B3F0(handle, $a1,
// 0x40000000). The unlock is a tail call. (A FLIRT name.)
void sceInsockAbortGethostbyaddr_2(EEContext& ctx);  // 0x54B348
// set_new_handler: stores the new handler in 0x793B68 and returns the previous one.
void set_new_handler__FPFv_v(EEContext& ctx);  // 0x54C0E8
// The ADXT error check of one handle, run by the server. While playing (stat +1 == 3, not paused +114, decoder not
// ended): the same decoded sample count (+100) for more than 5 x (+56) calls sets the error code (+96) to -2 (a stuck
// decoder); while preparing or playing (stat 1..3), input under 64 bytes (the input joint +20, its +36 entry with lane
// 1) for more than 5 x (+56) calls (20 x when not yet playing) sets -1 (a starved input). Counters reset when their
// condition breaks. With an error code the recovery mode (+109) acts: after the stall check mode 1 or 2 stops the
// handle (sub_548678); after the input check mode 1 stops it and mode 2 restarts it from its input (sub_54C580); when
// the mode is set the error code and that counter are then cleared. A streamer (+8) in state 4 (error) runs the
// input-check recovery. [proposed adxt_ExecErrChk]
void sub_54C670(EEContext& ctx);  // 0x54C670
// Under the ADX lock (the empty stubs sub_539848 / sub_539850): sub_54CB08(handle): the handle's streamer (+8, else the
// play list's) passed to sub_547558; returns it.
void sub_54CAD0(EEContext& ctx);  // 0x54CAD0

// ---- ACS sound-server thunks (the server pointer 0x793F44); AHX init counter, bit mask, sync search -----------------
// ACSSVR_Finish on the sound server (*0x793F44), a tail call.
void sub_54D010(EEContext& ctx);  // 0x54D010
// The ducking lowering frames of the server's ducking object: ACSVHL_GetDownTime(ACSSVR_GetVhl(*0x793F44)), a tail
// call.
void sub_54D560(EEContext& ctx);  // 0x54D560
// The ducking restoring frames: ACSVHL_GetUpTime(ACSSVR_GetVhl(*0x793F44)), a tail call.
void sub_54D588(EEContext& ctx);  // 0x54D588
// The ducking depth (dB x 10): ACSVHL_GetDepth(ACSSVR_GetVhl(*0x793F44)), a tail call. (A FLIRT name.)
void sqrtl_5(EEContext& ctx);  // 0x54D5B0
// One server frame: ACSSVR_ExecServer(*0x793F44), a tail call. (sub_535050)
void sub_54D5D8(EEContext& ctx);  // 0x54D5D8
// One sound's frame: acssvr_ExecSnd(*0x793F44, $a0), a tail call. (sub_5350D0; a FLIRT name.)
void valloc_0(EEContext& ctx);  // 0x54D5F8
// The AHX init counter 0x796F50 (beside the bit reader's call count 0x796F54 and mask table 0x796F58): the first call
// clears the 704-byte work 0x796FE0; returns the new count. (A FLIRT name.)
void pvalloc_0(EEContext& ctx);  // 0x54D618
// The matching AHX finish: decrements 0x796F50 and clears the 704-byte work 0x796FE0 when it reaches 0.
void sub_54D668(EEContext& ctx);  // 0x54D668
// A mask of the $a0 low bits: $a0 / 8 bytes of 0xFF shifted in, then $a0 % 8 single bits (signed division by 8); passed
// as $a1 to sub_54D88C, which returns it (a tail call).
void sub_54D818(EEContext& ctx);  // 0x54D818
// AHX sync search on the bit reader $a0: mask = 0x796F58[$a2] ($a2 bits); skips to the byte boundary (the bits
// consumed, sub_54DBE8, & 7; sub_54DB38 takes the rest), takes $a2 bits, then while (bits & mask) != $a1 and the reader
// has data (sub_54DBF0) shifts in 8 more bits. Returns 1 when found (data left), else 0.
void sub_54DC48(EEContext& ctx);  // 0x54DC48
// Returns 0 (a stub).
void sub_54DDF8(EEContext& ctx);  // 0x54DDF8
// Calls the registered callback *0x7973A4 (when set) with its object *0x7973A8 and $a0 (jalr); returns 0.
void sub_54DE18(EEContext& ctx);  // 0x54DE18
// Calls the return stub at 0x54E808 (the tail of sub_54E7D8) and returns its $v0 x 12.
void sub_54E810(EEContext& ctx);  // 0x54E810

// ---- AIX header info ------------------------------------------------------------------------------------------------
// Reads track $a1's two words of the AIX info $a0 (16-byte records: +700 and +704) into *$a2 / *$a3 (each when not
// null).
void sub_554998(EEContext& ctx);  // 0x554998
// Reads segment $a1's four u16 of the AIX info $a0 (8-byte records at +6456: +0, +2, +4, +6) into *$a2, *$a3, *$a4,
// *$a5 (each when not null).
void sub_554A00(EEContext& ctx);  // 0x554A00
// Checks the arguments of the AIX header parse (buffer, size > 0, out): a bad one reports "E2003080101 : Illegal
// parameter is specified." (sub_552630) and returns -1; else sub_554AE8 (tail call) parses the header.
void sub_554AA0(EEContext& ctx);  // 0x554AA0

// ---- CRI CFG (version text, a 16-entry name table) and the CVFS finish ----------------------------------------------
// CRI CFG init: points 0x997408 at the version text "CRI CFG/PS2EE Ver.1.002 ...", clears the 256 bytes at 0x997418 and
// makes them a table of 16-byte entries (base 0x99740C = the word-aligned 0x99741B, count 0x997410 = 16).
void sub_5556A0(EEContext& ctx);  // 0x5556A0
// CRI CFG finish: clears the entry table base (0x99740C) and count (0x997410).
void sub_555720(EEContext& ctx);  // 0x555720
// CRI CFG: adds an entry {name (12 chars, strncpy), $a1}: 0 when stored, -1 when CFG is not initialised (base 0), -2
// when the table is full (sub_555738 finds no free entry).
void sub_555820(EEContext& ctx);  // 0x555820
// CVFS finish: decrements the init count 0x7A08AC; at 0, for each of the 40 open-handle records {device interface,
// device handle} at 0x997518 calls the interface's +20 entry with the handle (jalr) when set and clears the record,
// clears the first byte of 32 16-byte device records (0x99765C..0x99784C), then the 9 bytes at 0x997858. [proposed
// cvFsFinish]
void sub_555A08(EEContext& ctx);  // 0x555A08

// ---- SRD (the stream read driver): settings and status words around srd_obj 0x7A08B0 --------------------------------
// SRD_WaitComplete(&srd_obj 0x7A08B0), a tail call.
void sub_557F60(EEContext& ctx);  // 0x557F60
// SRD: stores the byte 0x7A092C = $a0.
void sub_5580F8(EEContext& ctx);  // 0x5580F8
// SRD: stores the word 0x7A0928 = $a0.
void sub_558108(EEContext& ctx);  // 0x558108
// SRD: the byte 0x7A092C (sub_5580F8's).
void sub_558118(EEContext& ctx);  // 0x558118
// SRD: the word 0x7A0928 (sub_558108's). (A FLIRT name.)
void __errno_3(EEContext& ctx);  // 0x558128
// SRD: srd_obj's device type byte (0x7A08B1: 1 DVD, 2 host).
void sub_5585F0(EEContext& ctx);  // 0x5585F0
// SRD: the word 0x7A08E4. (A FLIRT name.)
void __errno_5(EEContext& ctx);  // 0x558600
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F0; returns its address.
void sub_558678(EEContext& ctx);  // 0x558678
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F4; returns its address.
void sub_5586B0(EEContext& ctx);  // 0x5586B0
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08F8; returns its address.
void sub_5586E8(EEContext& ctx);  // 0x5586E8
// SRD: waits for the server (sub_558610), stores the sign-extended byte $a0 in 0x7A08FC; returns its address.
void sub_558720(EEContext& ctx);  // 0x558720
// SRD: srd_obj.stat (0x7A08B2) = 9; returns 9.
void sub_558758(EEContext& ctx);  // 0x558758
// SRD info dump (scePrintf): "SRD: SRD Info.", srd_enter_fg (0x7A08EC), srd_debug_geterror (0x7A0904), srd_obj.stat,
// the device type (DVD / HOST lines), the read status (sub_558848); returns 0.
void sub_558898(EEContext& ctx);  // 0x558898
// SRD: the word 0x7A090C.
void sub_558968(EEContext& ctx);  // 0x558968
// SRD: the word 0x7A0908.
void sub_558978(EEContext& ctx);  // 0x558978
// SRD: the word 0x7A091C.
void sub_5589A8(EEContext& ctx);  // 0x5589A8

// ---- HTCI, the host file system device (host:), with its SRD / host settings ----------------------------------------
// The address of the 0x7A2A80 block. (A FLIRT name.)
void sceLibgcc32GetErxEntries_6(EEContext& ctx);  // 0x55B6D8
// sub_5589B8($a0): the 64-bit host filesystem flag (a tail call). (A FLIRT name.)
void cosl_7(EEContext& ctx);  // 0x55B700
// __errno_6 (0x5589F8), a tail call. (A FLIRT name.)
void coshl_7(EEContext& ctx);  // 0x55B718
// Stores the sign-extended byte $a0 in 0x7A08F4 and 0x7A0924 and prints "SRD: Enable HostLock" (scePrintf, a tail call)
// when $a0 == 1. Three chunks: an empty frame at 0x55B730, then the body at 0x558A08. (A FLIRT name.)
void expl_7(EEContext& ctx);  // 0x55B730
// __errno_7 (0x558A60), a tail call. (A FLIRT name.)
void hypotf_7(EEContext& ctx);  // 0x55B748
// Host CI setup: clears the root directory (sub_55D108(0)) and resets the device prefix (sub_55D198(0): "host:");
// returns the address of the function table 0x7A2C18 ($v1 keeps the word 0x7A2C08). [proposed htCiGetInterface]
void sub_55B760(EEContext& ctx);  // 0x55B760
// Whether a host CI handle's transfer has ended: sceIoctl(fd +24, 1, &h+20) with the SRD trace codes 0x4000 / 0x4001
// around it; 1 when the call succeeded and +20 != 1 (not executing), else 0.
void sub_55B848(EEContext& ctx);  // 0x55B848
// The host CI error callback: function 0x7A2C0C = $a0, object 0x7A2C10 = $a1. [proposed htCiEntryErrFunc]
void sub_55BA50(EEContext& ctx);  // 0x55BA50
// The host file's size (sub_55BB30) as a sign-extended 32-bit value. [proposed htCiGetFileSize]
void sub_55BB08(EEContext& ctx);  // 0x55BB08
// Opens a host file for reading: null name, a write mode or no free handle (sub_55BD70) report E0092708 / 09 / 10 and
// return 0. A file-cache hit (sub_55CF08) takes the cached offset and size (cached +1 = 1); else builds the full path
// (0x7A2EF0), prints "HTCI: File cache was not hit.", takes the size (sub_55BB30; 0 fails) and sceOpen's it with mode
// 0x7A3030 (trace 0x4900 / 0x4901; a failure reports E0092711 and frees the handle). Then the sector count (size +
// 2047) >> 11, the counters cleared, used = 1. [named by its own text: htCiOpen]
void sub_55BDC8(EEContext& ctx);  // 0x55BDC8
// Closes a host CI handle: stops a running transfer (state +2 >= 2: sub_55C240), sceClose's an uncached one (trace
// 0x5000 / 0x5001; "HTCI: Failed sceClose" on error), marks it free and clears it (sub_55BDA8, a tail call). [proposed
// htCiClose]
void sub_55BF40(EEContext& ctx);  // 0x55BF40
// Loads the host file list $a0 into the buffer $a1 ($a2 bytes, $a3 = the name length): clears the 4 KiB read buffer
// 0x998BC0, the cache descriptor once (sub_55CEE0) and the open files (sub_55CCE8); a null buffer or size prints "HTCI:
// Invalidate filelist ..." and returns 0; reads the file (sub_55C9D0; failure: "HTCI: Can't read filelist file." and
// E0111501) and parses it into $a2 / ($a3 + 9) entries (sub_55C830, sub_55CB30). Returns 8 x ($a2 / ($a3 + 9)) + n x
// ($a3 + 1), n from sub_55CB30. [named by its own text: htCiLoadDirInfo]
void sub_55CF58(EEContext& ctx);  // 0x55CF58
// Whether $a0 is in the host file cache (sub_55CF08 into a stack record; its size word +4 != 0).
void sub_55D0B0(EEContext& ctx);  // 0x55D0B0
// The host open mode 0x7A3030: 1 (SCE_RDONLY) when $a0 == 1, else 0x8001 (SCE_RDONLY | SCE_NOWAIT).
void sub_55D0D8(EEContext& ctx);  // 0x55D0D8
// The address of the root directory 0x7A3038. (A FLIRT name.)
void sceLibgcc32GetErxEntries_7(EEContext& ctx);  // 0x55D188
// The address of the device prefix 0x7A3140. (A FLIRT name.)
void sceLibgcc32GetErxEntries_8(EEContext& ctx);  // 0x55D200
// The host open mode 0x7A3030 (sub_55D0D8's). (A FLIRT name.)
void WTLS_get_table(EEContext& ctx);  // 0x55D210
// The word 0x7A3034. (A FLIRT name.)
void __errno_9(EEContext& ctx);  // 0x55D230

// ---- LSC settings, mfCi (memory files named "address.size") and the PL2 encoder lock --------------------------------
// LSC: the flag byte +4 of the stream queue $a0 = ($a1 == 1); returns 1. A null queue reports "E2005012808: Illigal
// parameter lsc=NULL" (sub_55DBE8, a tail call).
void sub_55D6F0(EEContext& ctx);  // 0x55D6F0
// The LSC error callback: function, object and a third word (0x7A3168 / 0x7A316C / 0x7A3170) = $a0..$a2, all 0 when $a0
// is null.
void sub_55DAE0(EEContext& ctx);  // 0x55DAE0
// Opens a memory file whose name is "address.size" in hex: null name, a write mode or no free handle (sub_55E3B0)
// report E01100301 / 02 / 03 and return 0; else copies the name (+28) and opens it (sub_55E428). [named by its own
// text: mfCiOpen]
void sub_55E498(EEContext& ctx);  // 0x55E498
// Closes a memory-file handle: clears its status (sub_55E800); a used one (+0 == 1) is marked free and cleared
// (sub_55E408). [proposed mfCiClose]
void sub_55E538(EEContext& ctx);  // 0x55E538
// Seeks a memory-file handle in sectors, inside the lock: whence $a2 = 0 from the start, 1 from the position, 2 from
// the end; clamped to 0..sectors (+12); returns the new position (+16). A null handle reports E01100305 and returns 0.
// [proposed mfCiSeek]
void sub_55E580(EEContext& ctx);  // 0x55E580
// The position (+16, sectors) of a memory-file handle; null: E01100306, 0. [proposed mfCiTell]
void sub_55E640(EEContext& ctx);  // 0x55E640
// Reads $a1 sectors of a memory file into $a2 (a memcpy from its address, the tail past the file end zeroed): a null
// handle / buffer or a negative count report E01100307 / 08 / 09 and return 0; 0 sectors completes at once; a busy
// handle (+1 == 2) returns 0. Clamps to the sectors left, advances the position, records the bytes moved (+20) and
// completes (+1 = 1); returns the sectors read. [proposed mfCiReqRd]
void sub_55E678(EEContext& ctx);  // 0x55E678
// The status byte (+1) of a memory-file handle; null: E0092912, 0. [proposed mfCiGetStat]
void sub_55E850(EEContext& ctx);  // 0x55E850
// The sector length (+4) of a memory-file handle; null: E0040301, 0. [proposed mfCiGetSctLen]
void sub_55E888(EEContext& ctx);  // 0x55E888
// Sets the sector length of a memory-file handle and rescales by it: sectors = (size + len - 1) / len, position =
// position x old len / len, bytes moved = request x len. Null: E0040302. [proposed mfCiSetSctLen]
void sub_55E8C0(EEContext& ctx);  // 0x55E8C0
// The PL2 encoder (sub_55F028) inside the CRI critical section.
void sub_55EFC8(EEContext& ctx);  // 0x55EFC8
// sub_55F1C8 on the object at $a0 + 232 (a tail call).
void sub_55F640(EEContext& ctx);  // 0x55F640

// ---- PS2RNA "not implemented" stubs ---------------------------------------------------------------------------------
// Prints "PS2RNA_ClearBuf: not implemented" (sub_541760, a tail call) unless the mode word 0x7A93F8 is 1 with no count
// (0x7A93F0 <= 0). [named by its own text: PS2RNA_ClearBuf]
void sub_560DE8(EEContext& ctx);  // 0x560DE8
// Prints "PS2RNA_SetPcmType: not implemented" unless the mode word 0x7A93F8 is 1 with no count (0x7A93F0 <= 0). [named
// by its own text: PS2RNA_SetPcmType]
void sub_560E30(EEContext& ctx);  // 0x560E30
// Prints "PS2RNA_GetStartSmpl: not implemented" unless the mode word 0x7A93F8 is 1 with no count; returns 0. [named by
// its own text: PS2RNA_GetStartSmpl]
void sub_5613E0(EEContext& ctx);  // 0x5613E0
// Prints "PS2RNA_IsOverflow: not implemented" unless the mode word 0x7A93F8 is 1 with no count; returns 0. [named by
// its own text: PS2RNA_IsOverflow]
void sub_561518(EEContext& ctx);  // 0x561518
// Prints "PS2RNA_ClearOverflow: not implemented" unless the mode word 0x7A93F8 is 1 with no count. [named by its own
// text: PS2RNA_ClearOverflow]
void sub_561560(EEContext& ctx);  // 0x561560
// An empty function.
void nullsub_144(EEContext& ctx);  // 0x5615A8
// Prints "PS2RNA_SetTotalNumSmpl: not implemented" unless the mode word 0x7A93F8 is 1 with no count. [named by its own
// text: PS2RNA_SetTotalNumSmpl]
void sub_5615F8(EEContext& ctx);  // 0x5615F8
// Clears the word 0x7AC768.
void sub_561708(EEContext& ctx);  // 0x561708
// Clears the word 0x7AC768 (a twin of sub_561708).
void sub_561718(EEContext& ctx);  // 0x561718

// ---- DTR / DTX: records and the IOP URPC commands (DTX_CallUrpc; arguments 0x999C00, reply 0x999D00) ----------------
// Prints "DTR_Init: in (count)" (sub_541760), clears the 2048 bytes at 0x7A0938 on the first call, increments the init
// count 0x7A0934, prints "DTR_Init: out" (tail call). [named by its own text: DTR_Init]
void sub_559200(EEContext& ctx);  // 0x559200
// DTX record $a0 of the 16 68-byte records at 0x7A1160 (unsigned $a0 < 16), else 0.
void sub_5596D0(EEContext& ctx);  // 0x5596D0
// Clears a DTX record's send and receive callbacks: the words +32, +36 (send function, object), +40, +44 (receive
// function, object).
void sub_559700(EEContext& ctx);  // 0x559700
// Whether any of the 40 DVD CI handles (72 bytes at 0x7A1DF0) is in use (byte +0 == 1) and transferring (status +2 ==
// 2): 1, else 0.
void sub_559E30(EEContext& ctx);  // 0x559E30
// Writes a 16-byte block header into the buffer {ptr, size} at $a0: clears the buffer, the tag $a1 (7 chars, strncpy)
// at +0 and (size - 16) as 7 lower-case hex digits at +8. Two chunks (0x563C88 and 0x563DD0).
void sub_563DD0(EEContext& ctx);  // 0x563DD0
// DTX URPC command 32 with three words ($a0..$a2 into 0x999C00..): DTX_CallUrpc(32, 0x999C00, 3, 0x999D00, 1); returns
// the reply word.
void sub_563F38(EEContext& ctx);  // 0x563F38
// DTX URPC command 33 with two words: DTX_CallUrpc(33, 0x999C00, 2, 0x999D00, 1); returns the reply word.
void sub_563F90(EEContext& ctx);  // 0x563F90
// DTX URPC command 36 with one word, four reply words copied to 0x999BC0; returns that address.
void sub_564068(EEContext& ctx);  // 0x564068
// DTX URPC command 37 with one word and no reply (a tail call).
void sub_5640D8(EEContext& ctx);  // 0x5640D8
// DTX URPC command 38 with three words; the two reply words go to $a3[0], $a3[1].
void sub_564108(EEContext& ctx);  // 0x564108
// DTX URPC command 39 with $a0, $a1 and the two words at $a2; no reply (a tail call).
void sub_564178(EEContext& ctx);  // 0x564178
// DTX URPC command 40 with $a0, $a1 and the two words at $a2; no reply (a tail call).
void sub_5641C8(EEContext& ctx);  // 0x5641C8
// DTX URPC command 42 with three words; the second reply word goes to *$a3, the first is returned.
void sub_564268(EEContext& ctx);  // 0x564268

}  // namespace p3fes::game
