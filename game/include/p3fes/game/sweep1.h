// Phase 5 slice sweep1: a reach-first sweep of the game code no other slice owned -- the H_Cdvd RtFS pak layer and the
// boot / heap-check leftovers, the EE-side sound helpers (BGM, voice / AFS, the SFD movie tasks), g_data.c's leftovers,
// the effect classes 10 / 13 / 16 kinds and filter helpers left by fx2, the message / card-effect band 0x3A0000, and the
// facility band (persona fusion screens, the shop / facility list steps). Register-ABI bodies (arguments in $a0..,
// the result in $v0) made readable on top of p3fes_handgen's output; the named offsets below each equal the literal
// they replace (a check script compares every file with the generator's output statement for statement).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace sw1 {

// --- RenderWare RtFS devices of the H_Cdvd layer (group file) ---------------------------------------------------------
// The file-system record (92 bytes, RwCalloc) the installers H_Cdvd_InitRtFsPak / H_Cdvd_InitRtFsHdd fill, and the file
// objects of its array (272 bytes for "pak:", 144 for "hdd:"). A "pak:" file object holds a copy of the 148-byte
// sCdvdCache entry (hcdvd.h HCdvdCacheEntry) at +112, whose spare word +144 serves as the read position.
namespace rtfs {
inline constexpr s32 kFsFileCount = 4;       // s32 file objects in the array
inline constexpr s32 kFsGetFile = 20;        // callback (fs, index) -> file object
inline constexpr s32 kFsClose = 24;          // callback (fs): close the file system
inline constexpr s32 kFsOpen = 40;           // callback (fs, file, name, mode) -> 1 / 2
inline constexpr s32 kFsFClose = 44;         // callback (file)
inline constexpr s32 kFsRead = 48;           // callback (file, dst, n) -> n read
inline constexpr s32 kFsWrite = 52;          // callback (hdd only)
inline constexpr s32 kFsSeek = 56;           // callback (result*, file, offset, whence)
inline constexpr s32 kFsEof = 68;            // callback (file) -> -1 / 0
inline constexpr s32 kFsExists = 76;         // callback (fs, name) -> 1 / 0
inline constexpr s32 kFsFiles = 88;          // the file-object array
inline constexpr s32 kFsSize = 92;
inline constexpr s32 kFileFs = 80;           // file object: the owning file system
inline constexpr s32 kFileBuffer = 104;      // file object: its 2,048-byte buffer
inline constexpr s32 kFileBufferSize = 108;  // file object: the buffer's size
inline constexpr s32 kPakFileSize = 272;     // "pak:" file object size
inline constexpr s32 kHddFileSize = 144;     // "hdd:" file object size
inline constexpr s32 kPakEntry = 112;        // "pak:" file object: the sCdvdCache entry copy (148 bytes)
inline constexpr s32 kEntryData = 136;       // entry: guest address of the file bytes
inline constexpr s32 kEntrySize = 140;       // entry: the file size
inline constexpr s32 kEntryPos = 144;        // entry copy: the read position
inline constexpr s32 kPakSize = 252;         // kPakEntry + kEntrySize
inline constexpr s32 kPakPos = 256;          // kPakEntry + kEntryPos
}  // namespace rtfs

// --- the EE-side sound helpers of h_snd.c / h_sndcom.c (group sound) ----------------------------------------------------
// The ADX channel records (font2.h snd: 16 records of 77 words from 0x7E4430; channel 0 is the BGM): +0 active, +8 s16
// the id, +12 s16 started, +16 the ADXT stream, +20 s16 the start type, +22 the file name, +0x118 / +0x11C / +0x120 the
// memory-start arguments. The CRI thunks at 0x54D000-0x54D400 they call are ADXT entry points (FLIRT gave some of them
// libm names: atan2l_4 / cosl_4 / setenv / pvalloc ...); the 40-byte stream-creation parameters of each channel are at
// 0x7E42E0 + 40 * ch, its work buffers at 0x7E43F0 / 0x7E43D0 + 4 * ch.
namespace sndch {
inline constexpr s32 kRecordSize = 308;  // 77 words
inline constexpr s32 kStartType = 20;    // s16: 0 / 1 file, 2 / 4 and 3 the memory forms, 5 memory, 6 by name
}  // namespace sndch

// The SE-bank requests (six 40-byte records at 0x7E5770, stepped by sub_108BC0 through sub_108E80): +0 s16 state (0 new
// -> 1 idle, 2 requested -> 3 binding -> 1), +2 s16 the bank, +4 s16 the h_sndcom slot, +8 s32 bound, +12 s16 explicit
// buffers, +16..+36 the HD / SQ / BD addresses and sizes passed to sub_10D7B0.
namespace sebank {
inline constexpr s32 kState = 0;
inline constexpr s32 kBank = 2;
inline constexpr s32 kSlot = 4;
inline constexpr s32 kBound = 8;
inline constexpr s32 kExplicit = 12;
}  // namespace sebank

// The h_sndcom.c slots (0x833710, 68 bytes each; IDA's HSndcomSlot): +0 s16 state (1 idle, 2 load by id, 8 load from
// buffers), +8 s16 the bank id, +24 bound, +32 / +40 / +48 the HD / BD / SQ sizes, +52 / +56 / +60 their sources.
namespace sndslot {
inline constexpr u32 kSlots = 0x833710u;
inline constexpr s32 kSlotSize = 68;
}  // namespace sndslot

// The "H_SfdPlay" movie task's work (544 bytes, RwCalloc): +4 the MW player, +208 a render object, +216 the player is
// started, +480 / +512 buffers, +484 s16 state, +490 s16 the movie id, +494 s16, +500 owned by a caller (not the
// script's shared task in $gp 0x7CDF14), +508 the camera / render state must be restored, +516 / +520 / +524 cleared on a
// script request.
namespace sfd {
inline constexpr s32 kGpScriptTask = -19932;  // 0x7CDF14: the script's shared movie task (comm_b.h kFieldTask)
inline constexpr s32 kWorkSize = 544;
inline constexpr s32 kPriority = 7383;
inline constexpr s32 kState = 484;
inline constexpr s32 kMovieId = 490;
inline constexpr s32 kOwned = 500;
inline constexpr s32 kRestore = 508;
}  // namespace sfd

// --- g_data.c (group data) -------------------------------------------------------------------------------------------
// facility/ps_model.bin, loaded by sub_16C010 into one heap block whose 32-byte header the $gp slot below points at:
// two sets of {+0 s32 record count, +4 s32 sub-record count, +8 records (32 bytes each), +12 sub-records (16 bytes)},
// set 0 at +0 and set 1 at +16; the file is the two counts pairs {n0, n1, .., .., n2, n3} followed by the four arrays.
// A record: +0 / +2 / +4 / +6 s16, +8 f32, +18 s16 the index of its 16-byte sub-record.
namespace psmodel {
inline constexpr s32 kGpTable = -19776;  // 0x7CDFB0: the table header
inline constexpr s32 kSetSize = 16;      // one set in the header
inline constexpr s32 kRecords = 8;       // set: the 32-byte records
inline constexpr s32 kSubRecords = 12;   // set: the 16-byte sub-records
inline constexpr s32 kRecordSize = 32;
inline constexpr s32 kSubRecordSize = 16;
inline constexpr s32 kRecF32 = 8;        // record: f32
inline constexpr s32 kRecSubIndex = 18;  // record: s16 the sub-record's index
}  // namespace psmodel

// event/itemtbl.bin (ui2.h "event/itemtbl.bin"): its H_Cdvd node while sub_16C1D0 copies it, and the section slots
// sub_1715F0 reads (items 0..999 -> section 0, 1000..1999 -> 2, 2000..2999 -> 3; section 10 holds the 32-byte records
// whose byte +0 == 100 marks a valid entry and byte +1 its value).
namespace itemtbl {
inline constexpr s32 kGpNode = -19720;      // 0x7CDFE8: the H_Cdvd node of event/itemtbl.bin
inline constexpr s32 kGpSection0 = -19724;  // 0x7CDFE4: 40-byte records (+20 u16 the section-10 index)
inline constexpr s32 kGpSection2 = -19732;  // 0x7CDFDC: 32-byte records (+12 u16 the section-10 index)
inline constexpr s32 kGpSection3 = -19736;  // 0x7CDFD8: 32-byte records (+12 u16 the section-10 index)
inline constexpr s32 kGpSection10 = -19772; // 0x7CDFB4: 32-byte records
}  // namespace itemtbl

// The 64 request slots of g_data.c (sub_172E50 / sub_172F70 / sub_173040; the record of request i is sub_3BEB10(i)):
// s32 accepted[64] 0x8364F4, s32 done[64] 0x8365F4 (= accepted + 256), u8 extra[64] 0x8366F4.
namespace request {
inline constexpr u32 kAccepted = 0x8364F4u;
inline constexpr u32 kDone = 0x8365F4u;
inline constexpr u32 kExtra = 0x8366F4u;
inline constexpr s32 kCount = 64;
}  // namespace request

// --- itfMesManager.c's message handle (group msg; msg2.h has the layout) ------------------------------------------------
namespace mes {
inline constexpr s32 kSpeaker = 20;   // the speaker sub-record
inline constexpr s32 kText = 36;      // the text sub-record (+16 relative = the busy byte +52)
inline constexpr s32 kBusy = 52;      // s8: 0 idle, 1 shown, < 0 finished (the COMM handlers clear it)
inline constexpr s32 kPanel = 168;    // the panel sub-record
inline constexpr s32 kGpWindowSprites = -18076;  // 0x7CE654: the message-window sprite file
}  // namespace mes

// --- the facility sequences' step payload (shops.h kStepResult / kStepFlags / kStepPhase; group combine / shop) -------
namespace step {
inline constexpr s32 kResult = 0;  // what the step's poller returns when it ends
inline constexpr s32 kFlags = 4;   // 1 decided, 2 hidden / closing
inline constexpr s32 kPhase = 8;   // the step's state
}  // namespace step
// the fclCombine sequence steps' payload (the menu steps and the root: +0 the result, +4 the step's state)
namespace cstep {
inline constexpr s32 kResult = 0;
inline constexpr s32 kState = 4;
}  // namespace cstep

}  // namespace sw1

// -------------------------------------------------------------------------------------------------------------------
// group file (game/src/sweep/sweep1_file.cpp): exit thunks, the RtFS "pak:" / "hdd:" devices of the H_Cdvd layer,
// the CRI stream starts by name, h_chkmem.c's malloc / free.
// -------------------------------------------------------------------------------------------------------------------
// sub_100210 0x100210 [crt0_CallExit]:
//   crt0's tail after main returns: `j exit` with main's result still in $v0 as the exit code (IDA's "possibly
//   undefined v0": the value is the caller's).
void sub_100210(EEContext& ctx);
// sub_100218 0x100218 [crt0_ExitThunk]:
//   exit()'s final step: `j Exit` (the libkernel Exit syscall wrapper); never returns.
void sub_100218(EEContext& ctx);
// H_Cdvd_RtFsPak_FOpen 0x1016D0:
//   (fs, file, name) -> 1 opened / 2 failed. The "pak:" device's open callback (fs +40): the name pointer 1 (a
//   sentinel) fails; otherwise the name is built (H_Cdvd_BuildPathUppercase) and normalized, then compared with
//   the normalized name of every used sCdvdCache slot (256 x 148 bytes); on a match the slot is copied into the
//   file object at +112 (data +248, size +252, position +256 = 0), the 64-bit length +0 = the size, +16 / +32 /
//   +48 = 0, +56 = 2, +60 = 1.
void H_Cdvd_RtFsPak_FOpen(EEContext& ctx);
// sub_101800 0x101800 [H_Cdvd_RtFsPak_FClose]:
//   The "pak:" device's close callback (fs +44): nothing to release (the data belongs to the PAK's H_Cdvd node);
//   `jr $ra`.
void sub_101800(EEContext& ctx);
// H_Cdvd_RtFsPak_FRead 0x101810:
//   (file, dst, n) -> bytes read. The "pak:" device's read callback (fs +48): while the position (+256) is below
//   the size (+252), copies min(n, size - position) bytes from data + position (memcpy) and advances the
//   position; at the end returns 0.
void H_Cdvd_RtFsPak_FRead(EEContext& ctx);
// sub_1018A0 0x1018A0 [H_Cdvd_RtFsPak_FEof]:
//   (file) -> -1 at the end / 0. The "pak:" device's end-of-file callback (fs +68): position (+256) >= size
//   (+252), signed, as 0 / -1 (`slt` + `subu zero`).
void sub_1018A0(EEContext& ctx);
// sub_1018C0 0x1018C0 [H_Cdvd_RtFsPak_FSeek]:
//   (result*, file, offset, whence). The "pak:" device's seek callback (fs +56); the 128-bit result (the new
//   position as a 64-bit value) is stored through $a0 via a stack quadword (sd / lq / sq): whence 1 -> position
//   = min(position + offset, size); whence 2 -> position += min(offset, size); whence 3 -> position = size +
//   offset, or size.
void sub_1018C0(EEContext& ctx);
// H_Cdvd_RtFsPak_Get 0x1019A0:
//   (fs, index) -> file object / 0. The device's get-file-object callback (fs +20): index below the file count
//   (+4) -> the 272-byte object index of the array +88, else 0.
void H_Cdvd_RtFsPak_Get(EEContext& ctx);
// sub_1019E0 0x1019E0 [H_Cdvd_RtFsPak_FsClose]:
//   (fs). The "pak:" device's close-file-system callback (fs +24): frees the file-object array (+88) through the
//   RwFree slot 0x96017C.
void sub_1019E0(EEContext& ctx);
// sub_101A10 0x101A10 [H_Cdvd_RtFsPak_FExists]:
//   (fs, name) -> 1 / 0. The "pak:" device's exists callback (fs +76): the same name build / normalize and the
//   walk over the 256 sCdvdCache slots as the open callback, without opening.
void sub_101A10(EEContext& ctx);
// H_Cdvd_InitRtFsPak 0x101AD0:
//   (count, buffers, buffer size, device name, fs name) -> fs / 0. Installs the memory-backed "pak:" RtFS
//   device: unless sub_4BFD50 finds the name taken, allocates the 92-byte file-system record (the RwCalloc slot
//   0x960184: 1 x 92, hint 0x40000), sets its callbacks (+20 get, +24 fs close, +40 open, +44 close, +48 read,
//   +68 eof, +56 seek, +76 exists), allocates `count` 272-byte file objects (+88), gives each the fs
//   back-pointer (+80) and its buffer (+104 = buffers + i * size, +108 = size), and registers the device
//   (sub_4BF6E0); a failure prints "#### rtFSInitError = %d".
void H_Cdvd_InitRtFsPak(EEContext& ctx);
// H_Cdvd_InitRtFS 0x101C70:
//   (no args) kwlnInitMain's RtFS set-up: RwFsInit(-1); then the "hst:" host device (sub_4C0FD0: 5 buffers of
//   2,048 bytes at 0x7D4780) and, when that registered, the "pak:" device (H_Cdvd_InitRtFsPak: 5 x 2,048 at
//   0x7D1F80; made the default with sub_4C0230), 0x7CDF38 = 1, and the "hdd:" device (H_Cdvd_InitRtFsHdd: 5 x
//   2,048 at 0x7CF780).
void H_Cdvd_InitRtFS(EEContext& ctx);
// H_Cdvd_StartSfd 0x1023F0:
//   (handle, path, flag) The Sofdec movie start by name: the path is upper-cased into 0x7CEB80, split into file
//   0x7CEC80 and directory 0x7CED80 (H_Cdvd_SplitPath), the ROFS directory set (H_Cdvd_SetRofsDir), then the CRI
//   MW start of the file name: sub_584290 (flag != 0) or sub_580378.
void H_Cdvd_StartSfd(EEContext& ctx);
// H_Cdvd_StartADXTFileRange 0x102530:
//   (stream, path) The ADX stream start of BGM channel 0: the CRI stop (0x54D390) of the stream, the path
//   upper-cased into 0x7CF180 and split (file 0x7CF280, directory 0x7CF380), the ROFS directory set, then the
//   ADXT start of the file name (sub_54B2E8).
void H_Cdvd_StartADXTFileRange(EEContext& ctx);
// H_Cdvd_StartADXTFile 0x1025C0:
//   (stream, path) The same for the other channels: buffers 0x7CF480 / 0x7CF580 / 0x7CF680 and the ADXT start
//   0x54D0A0 (FLIRT's "pvalloc": a CRI ADXT thunk).
void H_Cdvd_StartADXTFile(EEContext& ctx);
// sub_1028D0 0x1028D0 [H_Cdvd_RtFsHdd_FEof]:
//   The "hdd:" device's end-of-file callback (fs +68): prints " HDD EOF " (scePrintf) and returns scePrintf's
//   result.
void sub_1028D0(EEContext& ctx);
// sub_102D90 0x102D90 [H_Cdvd_RtFsHdd_Get]:
//   (fs, index) -> file object / 0. The "hdd:" device's get-file-object callback (fs +20): prints a debug line,
//   then index below the file count (+4) -> the 144-byte object index of the array +88, else 0.
void sub_102D90(EEContext& ctx);
// sub_102E00 0x102E00 [H_Cdvd_RtFsHdd_FsClose]:
//   (fs). The "hdd:" device's close-file-system callback (fs +24): prints "HDD FSClose" and frees the
//   file-object array (+88) through the RwFree slot.
void sub_102E00(EEContext& ctx);
// H_Cdvd_InitRtFsHdd 0x102E50:
//   (count, buffers, buffer size, device name, fs name) -> fs / 0. Installs the "hdd:" RtFS device: the same
//   body as H_Cdvd_InitRtFsPak with the hdd callbacks (+20 get, +24 fs close, +40 open, +44 close, +48 read, +52
//   write, +68 eof, +56 seek, +76 exists: the pfs0: file I/O of 0x102900-0x102D10) and 144-byte file objects.
void H_Cdvd_InitRtFsHdd(EEContext& ctx);
// sub_103D00 0x103D00 [H_ChkMem_Free]:
//   (block) h_chkmem.c's free: for a non-null block, the 16-byte header before it gives the size (-16) and a
//   clear flag (-4); the running total 0x7CDEAC drops by the size, then inside DIntr / EIntr (EIntr only when
//   DIntr reported interrupts were on) the block is zero-filled when flagged (memset) and freed (newlib cfree).
void sub_103D00(EEContext& ctx);
// sub_103DA0 0x103DA0 [H_ChkMem_Malloc]:
//   (size) -> block / 0. h_chkmem.c's malloc: size 172 prints a marker; the running total 0x7CDEAC grows by the
//   size; newlib malloc(size + 16) inside DIntr / EIntr; a block at 0x14CCAC8 prints "CHECK !!"; the 16-byte
//   header gets the size (+0), a serial number (+8, the counter 0x7CDEB8 + 1) and the tag 0x7CDEBC (+12), and
//   the caller receives header + 16.
void sub_103DA0(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group sound (game/src/sweep/sweep1_sound.cpp): ADX set-up, SE-bank requests, ADX channel stop / in-memory play,
// the AFS voice loader, the H_SfdPlay movie task, h_sndcom.c slot requests.
// -------------------------------------------------------------------------------------------------------------------
// sub_108740 0x108740 [H_Snd_InitAdx]:
//   (no args) kwlnInitMain's sound set-up: the ADXM parameters {f32 0x7CAD28, 1, 1, 0} at 0x7E4410 to
//   sub_57F768, the CRI library starts (0x54CFE8, 0x54D468, sub_5497B0(30)); then four ADXT stream
//   configurations -- the 40-byte parameter records 0x7E42E0 (BGM: 3 / 2 channels, 48,000 Hz), 0x7E4330 (24,000
//   Hz, mono), 0x7E4358 and 0x7E4380 (24,000 Hz) --, each with its work size (0x54D080), an RwMalloc'd work
//   buffer (0x7E43F0.
void sub_108740(EEContext& ctx);
// sub_108E80 0x108E80 [H_Snd_StepSeBankRequest]:
//   (req) One step of an SE-bank request (40-byte records 0x7E5770, stepped by sub_108BC0): state 0 -> 1; state
//   2 -> the h_sndcom slot (+4) is asked to load the bank (+2): from explicit HD / SQ / BD buffers (+16..+36)
//   through sub_10D7B0 when +12 is set, else by id (sub_10D6F0); state 3; state 3 -> once the slot is idle again
//   (H_Sndcom_IsChannelPlaying), bound (+8) = 1 and state 1.
void sub_108E80(EEContext& ctx);
// sub_109070 0x109070 [H_Snd_StopChannel]:
//   (ch) -> 1. Stops ADX channel `ch` when it is active: the CRI stop (0x54D100) of its stream (+16), started
//   (+12) = 0, active = 0, id (+8) = -1. (The two paths for ch < 2 and ch >= 2 are the same.).
void sub_109070(EEContext& ctx);
// sub_109CA0 0x109CA0 [H_Snd_RequestSeBank]:
//   (slot, bank) -> 1. kwlnRootCreateTask's SE-bank request for request record `slot` (0x7E5770 + 40 slot): when
//   sub_109DF0() is non-zero and the record already holds this bank nothing changes; otherwise the record gets
//   state 2 (requested), the bank, the slot, bound = 0, explicit = 0 (with sub_109DF0() == 0, a record still
//   binding -- state 3 -- another bank K_Asserts first: h_snd.c, 843).
void sub_109CA0(EEContext& ctx);
// sub_109E30 0x109E30 [H_Snd_FadeStopChannel]:
//   (ch) For an active ADX channel: 0x54D220(stream, 10) and then the same stop as sub_109070 (CRI stop, started
//   = 0, active = 0, id = -1). K_Field_DestroyFieldRootTask's call.
void sub_109E30(EEContext& ctx);
// sub_10A2E0 0x10A2E0 [H_Snd_PlayMemoryAdx]:
//   (data, ch, id) -> 1. Plays an in-memory ADX on channel `ch`: active = 1, id (+8), the data address (+0x11C),
//   started = 0, start type 5, then H_Snd_StartChannel (sub_109180).
void sub_10A2E0(EEContext& ctx);
// sub_10A5A0 0x10A5A0 [H_Afs_UpdateTask]:
//   (task) -> 0. Update callback of "H_AfsSetProc" (work +60): state 0 -> time 0, the voice pack name
//   "sound/v%03d%03d.afs" (work +12, +16) loaded into the ADXF handle +4 (H_Cdvd_LoadAfsFile), state 1; state 1
//   -> time +1 per frame, the ADXF status (0x53C268): 4 -> state 0 (again), 3 -> the debug line "##### AFS
//   =[..]" and state 2 (loaded); state 2 stays.
void sub_10A5A0(EEContext& ctx);
// sub_10BB00 0x10BB00 [H_SfdPlay_DestroyTask]:
//   (task) Destroy callback of "H_SfdPlay" (work +60): the MW player (+4) is stopped (0x584338 when started,
//   +216) and destroyed (0x57DB58); the two buffers +480 / +512 are freed (RwFree; the second also clears $gp
//   0x7CDF10); the render object +208 is destroyed (sub_4CDE90); flag 5127 is cleared; a task not owned by a
//   caller (+500 = 0) clears the script's shared task slot $gp 0x7CDF14; with +508 the field camera's raster /
//   render state is restored (sub_198590 -> sub_4AA550, sub_4B6350, sub_4B7630(0x77E4E0)); the work is freed.
void sub_10BB00(EEContext& ctx);
// sub_10BCE0 0x10BCE0 [H_SfdPlay_CreateTask]:
//   (parent, movie) -> task / 0. Creates an "H_SfdPlay" task (priority 7383; update sub_10A860, destroy
//   sub_10BB00) on a 544-byte RwCalloc work: owned (+500) = 1, the movie id (+490), +508 = 0.
void sub_10BCE0(EEContext& ctx);
// sub_10BE60 0x10BE60:
//   (script) -> 1. A script COMM handler: plays movie scrGetIntPara(0) on the script's shared "H_SfdPlay" task
//   ($gp 0x7CDF14, created once with movie 7, not owned): the work's movie id (+490), +494 = 0, +516 / +520 /
//   +524 = 0, state (+484) = 2.
void sub_10BE60(EEContext& ctx);
// sub_10D6F0 0x10D6F0 [H_Sndcom_RequestBank]:
//   (slot, bank) An idle h_sndcom slot (0x833710 + 68 slot; state 1) drops its bound bank (H_Sndcom_UnbindSfx
//   when +24 is set), takes the bank id (+8) and state 2 (load by id).
void sub_10D6F0(EEContext& ctx);
// sub_10D7B0 0x10D7B0 [H_Sndcom_RequestBankFrom]:
//   (slot, bank, hd, hdSize, bd, bdSize, sq, sqSize) The same for a bank in memory: an idle slot unbinds, takes
//   the bank id, state 8, the three sources (+52 / +56 / +60) and sizes (+32 / +40 / +48); eight register
//   arguments ($a0..$t3).
void sub_10D7B0(EEContext& ctx);
// H_Sndcom_IsChannelPlaying 0x10D910:
//   (slot) -> 0 / 1. h_sndcom slot `slot` is idle: its s16 state (+0) == 1. (The name is IDA's; state 1 is the
//   state the request functions wait for.).
void H_Sndcom_IsChannelPlaying(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group data (game/src/sweep/sweep1_data.cpp): g_data.c -- ps_model.bin, the item table, flag words,
// comuFunction.c's 64 entries.
// -------------------------------------------------------------------------------------------------------------------
// sub_16BA00 0x16BA00 [datPsModelGetF32]:
//   (set, i) -> $f0. ps_model.bin record i of set `set` (u16 each): K_Assert(g_data.c, 134) when the table is
//   not loaded, then $f0 = the record's f32 +8 ($v0 is left holding the record's address).
void sub_16BA00(EEContext& ctx);
// sub_16BA80 0x16BA80 [datPsModelGetS16_0]:
//   (set, i) -> s16. ps_model.bin record i of set `set`: the s16 at +0 (K_Assert line 139 without the table).
void sub_16BA80(EEContext& ctx);
// sub_16BB00 0x16BB00 [datPsModelGetS16_2]:
//   (set, i) -> s16. The record's s16 at +2 (K_Assert line 144).
void sub_16BB00(EEContext& ctx);
// sub_16BB80 0x16BB80 [datPsModelGetS16_4]:
//   (set, i) -> s16. The record's s16 at +4 (K_Assert line 149).
void sub_16BB80(EEContext& ctx);
// sub_16BC00 0x16BC00 [datPsModelGetS16_6]:
//   (set, i) -> s16. The record's s16 at +6 (K_Assert line 154).
void sub_16BC00(EEContext& ctx);
// sub_16BEE0 0x16BEE0 [datPsModelCopySub]:
//   (set, i, dst) Copies the 16-byte sub-record that record i of set `set` names (its s16 +18) into dst (memcpy;
//   K_Assert line 184 without the table).
void sub_16BEE0(EEContext& ctx);
// sub_16BF80 0x16BF80 [datPsModelCopyRecord]:
//   (set, i, dst) Copies record i of set `set` (32 bytes) into dst (memcpy); K_Assert(g_data.c, 195) on a null
//   dst.
void sub_16BF80(EEContext& ctx);
// sub_16C010 0x16C010 [datPsModelLoad]:
//   (no args) Loads facility/ps_model.bin synchronously (H_Cdvd_Request / ReadSync), allocates one RwMalloc
//   block (slot 0x960178, hint 0x40000) of 32 + 32 (n0 + n2) + 16 (n1 + n3) bytes, stores it in the $gp slot
//   0x7CDFB0, fills the two sets' counts and array pointers (set 0: records right after the header, sub-records
//   after them; set 1 after those), copies the four arrays from the file (memcpy) and destroys the file node.
void sub_16C010(EEContext& ctx);
// sub_16C1D0 0x16C1D0 [datLoadMsgPakAndItemTable]:
//   (no args) A kwlnInitMain step: loads help/datMsg.pak (H_Cdvd_Request with the archive flag, ReadSync),
//   registers its eight message files -- their names copied from the table 0x5E31D0 to the stack -- with
//   sub_3C7D80(i, H_Cdvd_CacheFindFile(name)), loads ps_model.bin (sub_16C010), then event/itemtbl.bin (node in
//   $gp 0x7CDFE8): copied whole to 0x83BB30, the node destroyed, the section pointers set
//   (datItemTblSetSections).
void sub_16C1D0(EEContext& ctx);
// sub_16E190 0x16E190 [datPickComuTag]:
//   (kind) -> s16. Of the three {social link, value} pairs of row `kind` of the s16 table 0x5E3240 (copied to
//   the stack, 6 words), returns the value of the first pair whose social link (K_Assert < 30, line 1429) has a
//   rank above 0 (gGlobalWork's s8 ranks 0x836276); 0 when none.
void sub_16E190(EEContext& ctx);
// sub_16F320 0x16F320:
//   (no args) Sets the 7-bit field of bits 3..9 of the flag word 0x83A24C to 11 (& ~0x3F8 | 0x58), then
//   sub_1754A0(1). Called from the kwln boot sequence (sub_195DE0, sub_1967D0).
void sub_16F320(EEContext& ctx);
// sub_1715F0 0x1715F0 [datItemGetSection10Byte]:
//   (item) -> u8 / 0 / 255. The item table lookup of a byte value: items 3000..3999 and >= 4000 -> 0; items
//   0..999 take the u16 +20 of their 40-byte section-0 record, 1000..1999 / 2000..2999 the u16 +12 of their
//   32-byte section-2 / section-3 record; that index picks a 32-byte section-10 record, whose byte +1 is
//   returned when its byte +0 is 100, else 255.
void sub_1715F0(EEContext& ctx);
// sub_172750 0x172750:
//   (rec) -> 0 / 1. A 6-byte record is set: 0 for the empty pattern {u8 +0 = 255, u16 +2 = 0, u8 +4 = 0, u8 +5 =
//   0}, otherwise 1 when any of those four is non-zero (else 0). Called by sub_3C33C0.
void sub_172750(EEContext& ctx);
// sub_1727E0 0x1727E0:
//   (no args) Clears bits 7..11 of the flag word 0x83A34C (& 0xFFFFF07F).
void sub_1727E0(EEContext& ctx);
// sub_172860 0x172860:
//   (no args) -> 0 / 1. Bit 10 of the flag word 0x83A34C.
void sub_172860(EEContext& ctx);
// sub_172B80 0x172B80 [datSetEventB]:
//   (a, b, rec) Copies the 56-byte record `rec` into gGlobalWork's second event block 0x8364BC (cleared first),
//   sets its flag (sub_395170(0x983)) and passes the packed word {a, b, rec[0], rec[30]} (built in a stack word)
//   to sub_17AC60.
void sub_172B80(EEContext& ctx);
// sub_172E50 0x172E50 [comuAcceptEntry]:
//   (i, extra, cost) comuFunction.c entry i: money 0x83A6DC - cost (K_Assert line 3463 below 0); unless entry i
//   is already accepted, it is accepted (0x8364F4[i] = 1), not done (0x8365F4[i] = 0), its extra byte
//   0x8366F4[i] = `extra`, and the money is stored clamped to 9,999,999 (K_Assert line 1674 beyond).
void sub_172E50(EEContext& ctx);
// sub_172F70 0x172F70 [comuFindExpiredEntry]:
//   (out*) -> 1 / 0. The first comuFunction.c entry that is accepted and not done and whose date (record +2
//   month, +3 day; clndGetDaysSinceStartFromDate) is today or earlier (gGlobalWork's day count 0x83679C): *out =
//   its index, 1; none -> 0.
void sub_172F70(EEContext& ctx);
// sub_173040 0x173040 [comuCompleteEntry]:
//   (i) Completes comuFunction.c entry i (K_Assert: accepted, line 3516; not yet done, line 3519): done = 1; for
//   each of its extra-byte + 2 rewards (record +4 s16 ids, +12 u8 counts): an id below 4000 is built into an
//   equipment entry (sub_1828D0) and added `count` times into a free slot of the shared 20-entry table 0x833E80
//   (sub_1831E0(-1, slot, entry); K_Assert line 3554 when full); an id >= 4000 goes to sub_170860(-1).
void sub_173040(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group fx (game/src/sweep/sweep1_fx.cpp): particle type 11, class-10 kinds 3 / 7, class-16 kind 3, filter
// helpers, the effect-clump and EPL texture-particle draws.
// -------------------------------------------------------------------------------------------------------------------
// sub_331650 0x331650 [psysType11Update]:
//   (psys) The update of particle-system type 11 (fx2: the "track" rows 0x69C510): with the owning effect's
//   emission on (+184 of the parameters +32), the emission budget from the lifetime / rate (+36 / +40, the
//   fraction carried in +20), the burst flag (+189), new particles placed from the effect's matrix (sub_357E30,
//   VU0) and its spread (sinf), every live particle aged and moved (FPU accumulator), the dead ones replaced
//   from the free list (memcpy of the 0x69C500 template), the per-particle state written through sub_32A770 /
//   sub_32A890.
void sub_331650(EEContext& ctx);
// sub_33B0D0 0x33B0D0 [k10Streak3Init]:
//   (inst) Class-10 kind 3 slot 0: locks the mesh (geometryLock 2), clears its 12-byte vertices (memset, the
//   kind's vertex count), unlocks (sub_4933D0), sets the double-sided flag when the kind's flags bit 2 is set,
//   and frees every 44-byte record (word 0 = -1) of the parameters' count (+56).
void sub_33B0D0(EEContext& ctx);
// sub_33B1C0 0x33B1C0 [k10Streak3Create]:
//   (params) -> kind object. Class-10 kind 3 slot 1: one RwMalloc block of 16 + 44 * count bytes (records right
//   after the 16-byte head, +8 the block itself) and a 12 x 13 grid mesh (sub_3233A0 with the layout 0x69BD80,
//   stride 72).
void sub_33B1C0(EEContext& ctx);
// sub_33B250 0x33B250 [k10Streak3Destroy]:
//   (obj) Class-10 kind 3 slot 2: destroys the mesh (sub_3237C0) and frees the block (RwFree).
void sub_33B250(EEContext& ctx);
// sub_33B2A0 0x33B2A0 [k10Streak3Update]:
//   (inst) Class-10 kind 3 slot 4: emits / ages the streaks (the spark parameters' rate, life and random ranges
//   from +96) and rebuilds the grid vertices on VU0 (positions from the effect matrix, the streak's two ends,
//   the colour track; MMI packs for the vertex colours).
void sub_33B2A0(EEContext& ctx);
// sub_33BBE0 0x33BBE0 [k10Streak3Draw]:
//   (inst) Class-10 kind 3 slot 5: the mesh colour from the instance colour x the colour track on VU0 (scale
//   1/255, 0x7CAE4C; ppacb), placed at the effect's frame (sub_3238D0) and queued (sub_323860); sub_32A120 gives
//   the effect's colour.
void sub_33BBE0(EEContext& ctx);
// sub_33E700 0x33E700 [k10Streak7Init]:
//   (inst) Class-10 kind 7 slot 0: the same body as k10Streak3Init (clear the vertices, free every record).
void sub_33E700(EEContext& ctx);
// sub_33E7F0 0x33E7F0 [k10Streak7Create]:
//   (params) -> kind object. Class-10 kind 7 slot 1: the 16 + 44 * count block and a 3 x 5 grid mesh (layout
//   0x69BD60, stride 72).
void sub_33E7F0(EEContext& ctx);
// sub_33E890 0x33E890 [k10Streak7Destroy]:
//   (obj) Class-10 kind 7 slot 2: destroys the mesh and frees the block.
void sub_33E890(EEContext& ctx);
// sub_33E8E0 0x33E8E0 [k10Streak7Update]:
//   (inst) Class-10 kind 7 slot 4: emits / ages the streaks and rebuilds the 3 x 5 grid vertices on VU0 (the
//   kind-7 random ranges).
void sub_33E8E0(EEContext& ctx);
// sub_33F2E0 0x33F2E0 [k10Streak7Draw]:
//   (inst) Class-10 kind 7 slot 5: colour, place and queue the mesh (the same body as k10Streak3Draw).
void sub_33F2E0(EEContext& ctx);
// sub_344AA0 0x344AA0 [k16Streamer3Init]:
//   (inst) Class-16 kind 3 slot 0: every record of the parameters' count is freed (word 0 = -1) and its mesh
//   vertex colour (the triangle list +40) set from the global colour 0x7CE544..0x7CE547 (an alpha of 255 is
//   written as 254 and the global's alpha byte restored to 255).
void sub_344AA0(EEContext& ctx);
// sub_344B70 0x344B70 [k16Streamer3BuildMesh]:
//   (obj, params) The streamer mesh of class-16 kind 3: with a count (+56), locks the mesh (geometryLock 4088)
//   and fills its segments (+140 + 1 rows): the width taper from the start / end fractions (+120 / +124), the
//   length step +144 / 3, the texture coordinates and the vertex positions / colours, then unlocks (sub_4933D0).
void sub_344B70(EEContext& ctx);
// sub_345080 0x345080 [k16Streamer3Destroy]:
//   (inst) Class-16 kind 3 slot 2: destroys the mesh (sub_324310) and frees the block (RwFree).
void sub_345080(EEContext& ctx);
// sub_3450D0 0x3450D0 [k16Streamer3Update]:
//   (inst) Class-16 kind 3 slot 4: emits / ages the streamer points along the effect's path and rebuilds the
//   strip vertices (VU0).
void sub_3450D0(EEContext& ctx);
// sub_345970 0x345970 [k16Streamer3Draw]:
//   (inst) Class-16 kind 3 slot 5: the strip colour from the instance colour, the colour track and the global
//   colour 0x7CE544 on VU0, placed (sub_3244C0) and queued (sub_3243D0).
void sub_345970(EEContext& ctx);
// sub_348950 0x348950 [fltBuildRotQuad]:
//   (params, quad) A screen-filter quad builder (sub_34A800's): the four Im2D vertices (64 bytes each) of the
//   rectangle +24..+36 with the RGBA bytes +0..+3, rhw 1 / the camera's near plane (sub_198590 +128) and z
//   g_rwIm2DNearScreenZ, and texture coordinates turned by the angle +12 (sinf / cosf) over the screen size
//   0x957BAC / 0x957BB0.
void sub_348950(EEContext& ctx);
// sub_349090 0x349090 [fltPulseCellsA]:
//   (params, cells) The cell pulse of a screen-filter kind (sub_349FD0's): for each 52-byte cell: a delay counts
//   down with alpha 0; otherwise the phase +4 past the limit 0x7CAD58 respawns the cell (sub_348F30), the scale
//   +24 = 1 + amplitude x sinf (FPU accumulator), the alpha +15 = (1 - |..|) x max alpha in soft double (fptodp
//   / fabs / dpsub / dpmul / dptofp), the phase advances by the speed +8.
void sub_349090(EEContext& ctx);
// sub_349620 0x349620 [fltPulseCellsB]:
//   (params, cells) The cell pulse of another filter kind (sub_34A370's): a negative phase counts up; otherwise
//   scale +24 = 1 + amplitude x sinf x (1 - phase) (accumulator), colour +12, alpha +15 = max alpha x (1 -
//   phase), the cell rectangle +28..+48 = the centre +32 / +36 -+ size x phase, the phase advances by +28.
void sub_349620(EEContext& ctx);
// sub_34DC00 0x34DC00 [effDrawClump]:
//   (eff) The effect-clump draw (sub_321360's): the colour word +4 scaled to floats on VU0 (pextlb / pextlh, x
//   0x7CAE08); with a clump (+88 +8 / +16): its frame placed from the effect matrix (sub_3322F0 / sub_3322B0,
//   VU0) for kind 3 with the frame flag, or from the camera-facing matrix, the material colours / alpha set for
//   every atomic (sub_34D3A0 per material, sub_4C31B0 / sub_4C2F30 / sub_4C33D0 / sub_4C35D0), the clump drawn
//   (RpClumpRender) and the frame restored (sub_4CB7F0).
void sub_34DC00(EEContext& ctx);
// sub_34EAE0 0x34EAE0 [eplDrawTexParticle]:
//   (obj, pos, part, colour, ...) The EPL texture-particle draw (sub_34F910's): the particle colour x the
//   instance colour on VU0 (ppach / ppacb); visible (alpha > 0): the camera-facing quad from the camera matrix
//   (sub_4D81B0, sub_4C6BE0), rotated by the particle angle (sinf / cosf), texture set (sub_3210A0, the frame's
//   coordinates from sub_3294D0 / sub_329550 / sub_3295C0 / sub_329630), the blend render states and the Im2D
//   primitive through pfn_RwRenderStateSet / pfn_RwIm2DRenderPrimitive (jalr).
void sub_34EAE0(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group msg (game/src/sweep/sweep1_msg.cpp): the social-link card effect, message COMM handlers, the message
// manager's page / selection steps, window frame draws, message tag handlers.
// -------------------------------------------------------------------------------------------------------------------
// sub_3A0220 0x3A0220 [evtCardEff_Draw]:
//   (task) -> 0. Draw callback "CardEff DrawProc" of the card effect (work +60): the global wobble 0x7CE61C +=
//   0.5; while drawing is on (+184): the background quad in the colour {+176..+179} with alpha +160
//   (sub_386F70); unless +188 is set, the card face quad 320 - w / 2 wide by |cos| (angle +168 < 90: front
//   texture +104) or |sin| (back texture +108) of the angle (soft-double cos / sin) drawn by sub_388000 with
//   alpha +156; the glow counter +200 counts up to 56 (then restarts unless +208 is 1) and draws sub_39FFC0
//   while positive; with +188 set, sub_39FBD0 draws.
void sub_3A0220(EEContext& ctx);
// sub_3A05B0 0x3A05B0 [evtCardEff_PlaceCardModel]:
//   (work, n) Places card model n (scene model 250 + n, sub_3B64C0; kept in +236 + 2 n) when slot n is loaded
//   (+116 + 4 n): 800 units in front of the field camera (its frame matrix via sub_4CB2F0, sub_4C69F0; FPU
//   accumulator madd.s), moved back by 85 (n = 3) or 240 along the camera's up axis, oriented from the camera
//   matrix (sub_3B7AC0) and set (sub_3B78B0); model 6 also gets its colour alpha cleared (sub_350040 /
//   sub_34FF90); then shown (sub_3B9550).
void sub_3A05B0(EEContext& ctx);
// sub_3A0960 0x3A0960 [evtCardEff_PlaceUnitModel]:
//   (work, n, unit) Places card model n beside scene unit `unit` (sub_3B5D10): at the unit's bone 2 position
//   (sub_318ED0; for type-1 units after sub_318B60) or, when that fails, at the model's origin + 175 in y; set
//   (sub_3B78B0) and shown (sub_3B9550).
void sub_3A0960(EEContext& ctx);
// sub_3A0E90 0x3A0E90 [evtCardEff_Update]:
//   (task) -> 0 / -1. Update callback of the card effect (work +60, state +148, 36 states through the jump table
//   0x7BB0C0; the cases are labelled below).
void sub_3A0E90(EEContext& ctx);
// sub_3A1F30 0x3A1F30 [evtCardEff_Destroy]:
//   (task) Destroy callback: releases the +104.. textures (sub_4D0F00, +112 of them), the seven card models
//   (+236.., sub_3B7090), the file nodes +16 / +20 / +24 (with their textures +96 / +100, sub_133D30), the two
//   message records (+28 / +60, sub_39EE80), the model list +232 and the work (RwFree).
void sub_3A1F30(EEContext& ctx);
// scrCommand_MSG 0x3A2150:
//   (script) -> 0 / 1. COMM 0 (MSG): message scrGetIntPara(0) on the script's message slot: requested once
//   (window type 4, itfMesMngRequestMessage) and polled through the handle's busy byte +52 until it goes
//   negative, which is cleared; 1 = done (also for no slot or a failed request).
void scrCommand_MSG(EEContext& ctx);
// sub_3A2260 0x3A2260:
//   (script) -> 0 / 1. A message COMM handler: window type 6, state flag 0x200000, the request, sub_3C9570 and
//   sub_3A5210(slot, 0, 0, 32, 0); on the busy byte -1 the selection is reset (sub_3A2A30, sub_3A3420) and the
//   byte set to -2; on -2 once the phases +0 bits 8-9 are clear: window type 4, the speaker / text / panel
//   records re-initialised, flag 0x400000 cleared, busy 0, done.
void sub_3A2260(EEContext& ctx);
// sub_3A2440 0x3A2440:
//   (script) -> 0 / 1. A message COMM handler like scrCommand_MSG with window type 7, flag 0x200000, sub_3C9570
//   and sub_3A5210(slot, 1, 5, 32, 0).
void sub_3A2440(EEContext& ctx);
// itfMesMngCreateHandle 0x3A2EF0:
//   (bmd) -> handle. Checks the BMD magic (K_Assert line 1747), allocates the 488-byte handle (RwMalloc when
//   flag 5156 is set, else H_Malloc), binds the BMD, clears the state word, +4, +12, +18, +484 and initialises
//   the speaker (+20), text (+36), selection (+64), panel (+168), argument (+212) and window (+468) records.
void itfMesMngCreateHandle(EEContext& ctx);
// sub_3A7120 0x3A7120 [itfMesMngStepPage]:
//   (handle) The page step of a message being shown (busy +52 == 1, request state 4): counts frames (+476);
//   unless auto-advance (bit 23) is set the page ends (+468 = 1 without bit 20) and on the confirm buttons, a
//   held button after 5 frames, an empty page or an auto page whose text is done (bit 27, sub_3B1710) the next
//   page starts ("push kai page button!!", the window record reset, offset 568 / 395, page +60 + 1,
//   sub_109F60(2, 0)): the 32 message arguments go back to the font (frFontSetTagSlot), the page is laid out
//   (sub_3A5980) and, for window type 6, its line styled; past the last page the message ends.
void sub_3A7120(EEContext& ctx);
// sub_3A7490 0x3A7490 [itfMesMngStepSelection]:
//   (handle) The selection step (selection record +64, phase +84): 4 -> scroll in (sub_3A7940) while the text is
//   below y 2840, else phase -1; 3 -> slide (+100 -= 16) and phase 4; 2 -> once the input step (sub_3A7A40)
//   reports a choice, the cursor glyph is drawn at the chosen line, the window phase bits 10-11 advance, request
//   state 5 and phase 3; 1 -> by window type (2: scroll the text into place by 64 per frame; 4 and the others:
//   colour the lines) the request state 3 and phase 2.
void sub_3A7490(EEContext& ctx);
// sub_3A7A40 0x3A7A40 [itfMesMngSelectInput]:
//   (handle) -> 0 / 1. The selection's pad input: up / down (0x7E0952 / 0x7E095A with the repeat words) move the
//   cursor (sub_3A7CB0, wrapping only on a fresh press at the ends); confirm (0x40) picks the cursor's option
//   counting only enabled options of the mask +80 ("ok button push", sound sub_10A4E0(0, 0, 0, 1)); a pointer
//   pick (sub_3A7D60, when +102 > 0) moves the highlight (itfMesMngTextSetLineAlpha 0 / 6) with sound 2.
void sub_3A7A40(EEContext& ctx);
// sub_3AA720 0x3AA720:
//   (win) Message-window frame draw (a draw callback): eight sprites 0..7 of the window sprite file ($gp
//   0x7CE654) at the {x, y} pairs of 0x6A2060 (y offset by the window's +4 - 5), alpha 255 - the window's +12,
//   drawn one-shot (sub_1127D0, sub_115980).
void sub_3AA720(EEContext& ctx);
// sub_3AAAE0 0x3AAAE0:
//   (win) Message-window frame draw: sprites 20.. at the pairs of 0x6A2080 (+5 / +5), alpha 255 - +12, and the
//   rest of the frame's sprites in the same way.
void sub_3AAAE0(EEContext& ctx);
// sub_3AB320 0x3AB320:
//   (win) Message-window frame draw for the three phases of the window state +0 (1 opening, 2 open, 3 closing):
//   the frame pieces through sub_3C9000 at (-75, -57), (-75, 35), (-31, -16) with alphas from the phase counter
//   +8 (x 255 / 5) and the window alpha +12 (f32 scale 0x7CB08C / 0x7CB14C; sinf for the pulse).
void sub_3AB320(EEContext& ctx);
// sub_3ABB10 0x3ABB10:
//   (win) Message-window frame draw of the name-plate form: the two coordinate tables 0x6A20A0 / 0x6A20C0 copied
//   to the stack, the window's rectangle (+16..+28 >> 4 / >> 3), sprites 42.. by the phase +0 (sub_40D5B0,
//   sub_3A87D0 for the plate).
void sub_3ABB10(EEContext& ctx);
// sub_3ACBC0 0x3ACBC0:
//   (ctx, tag) -> 0. Message tag handler: plays a voice line when flag 388 is set -- the three 16-bit tag
//   arguments (event major / minor / line; each argument is two bytes, lo - 1 and hi - 1 with 255 meaning 0)
//   build "sound/voice_e%03d_%03d/%03d_%03d%05d.adx" (major <= 400) or "..._%04d.adx" (major 401..500, minor /
//   20 in the directory), played on channel 2 (sub_10A370).
void sub_3ACBC0(EEContext& ctx);
// sub_3ACE60 0x3ACE60:
//   (ctx, tag) -> 0. Message tag handler: with flag 388 set and bit 8 of 0x7CD500 clear, plays an in-memory ADX
//   on channel 2 (sub_10A2E0(arg0, 2, arg1)).
void sub_3ACE60(EEContext& ctx);
// sub_3ADB80 0x3ADB80:
//   (ctx, tag) -> 0. Message tag handler: sub_3CF160(arg2 | arg0 << 16 | arg1 << 8, arg3 == 0 ? 0x300 : 0x200)
//   from four 16-bit tag arguments.
void sub_3ADB80(EEContext& ctx);
// sub_3ADD40 0x3ADD40:
//   (ctx, tag) -> 0. Message tag handler: sub_3CF160(arg2 | arg0 << 16 | arg1 << 8, 0).
void sub_3ADD40(EEContext& ctx);
// sub_3AEA50 0x3AEA50:
//   (ctx, tag) -> 0. Message tag handler: sub_3B93C0 with five 16-bit tag arguments (the last as s16).
void sub_3AEA50(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group combine (game/src/sweep/sweep1_combine.cpp): fclCombine.c's set-up / sequence steps / root update,
// fclCombineList.c's list updates, the persona panels, the backdrop particles.
// -------------------------------------------------------------------------------------------------------------------
// sub_3D2740 0x3D2740 [fclCombine_SetupStep]:
//   (seq, step) -> next step. fclCombine.c's set-up step over the sequence's command table (0x6A4380, 8-byte
//   records {u16 op, ..., name}, the step's index +12): op 1 the persona-status tasks
//   (fclMisc_CreatePsStatusTasks), op 2 a facility element (sub_3EFED0(7), sub_40E300), op 3 the message file
//   "facility/msg/AGS_msg_combine.bmd" or the "facility/%s" name of the record (K_Assert lines 903 / 915) found
//   in the H_Cdvd cache, op 4 the scene (MT_Scene_Load), op 5 sub_3D5420(0), and the load / wait / camera ops
//   after them (H_Cdvd_Request / IsFileLoaded, sub_1A1150 / sub_1A1190 / sub_1A4580, sub_1A0040); a waiting op
//   returns nmSeqNullStep.
void sub_3D2740(EEContext& ctx);
// sub_3D2C10 0x3D2C10 [fclCombine_OpenMenuA]:
//   (owner) -> step. Adds menu step 1 to the fclCombine sequence ($gp 0x7CE684; nmSequenceAddStep with the
//   20-byte record copied from 0x6A46B0), stores it in owner +20, hides panel 4 and panel 10 (sub_3D06D0(..,
//   0)).
void sub_3D2C10(EEContext& ctx);
// sub_3D2CE0 0x3D2CE0 [fclCombine_WaitMenuA]:
//   (owner) -> result / -1. Waits for that step: once its object's flags (+20 +20) have bit 3 (done), panel 4 is
//   shown again, owner +20 cleared and the step's first payload word returned; otherwise -1.
void sub_3D2CE0(EEContext& ctx);
// sub_3D2E00 0x3D2E00 [fclCombine_MenuStep]:
//   (seq, step) -> 0 / nmSeqNullStep. A fclCombine menu step: finished (sub_3D3010) -> nmSeqNullStep; else the
//   decided row (sub_3D3050) - 1 goes to the step's payload with sub_3D3280 and panel 10 shown, or, with no
//   decision, a cancel (sub_3D3170) sets the payload to 6 and shows panel 10.
void sub_3D2E00(EEContext& ctx);
// sub_3D3050 0x3D3050 [fclCombine_DecidedRow]:
//   (menu) -> row id / -1 / 0. The decided row of a fclCombine command list: when the list (+8) has one and the
//   element (+16, sub_3DF010) is ready: the element closed (sub_3DEF80), panel 0 hidden unless the row is 7, the
//   menu refreshed (sub_3D3760(menu, 0, 1)), the row's word (+20 +12) stored in the root payload +16, the
//   confirm sound (sub_10A4E0(0, 0, 0, 1)), the row id returned; none -> -1; no menu -> 0.
void sub_3D3050(EEContext& ctx);
// sub_3D3D20 0x3D3D20 [fclCombine_RootUpdate]:
//   (seq, step) -> next step. The fclCombine root's main step (state +4 of the step payload, jump table
//   0x7BB620): hides / shows the field (sub_1A0040, sub_1A0150 3072..3074, the "fclCombine_FIELD_(IN)VISIBLE"
//   debug lines), opens the list menu of the fusion kind +8 (kinds 0 / 1: sub_3DA0C0, kinds 2..4: sub_3DE290)
//   and runs it (sub_3DA700 / sub_3DE470), then the fusion itself: the result (sub_3D4CD0, sub_3D8080), the
//   fusion effect tasks (fclCmbEff_CreateCmbEffCalcTasks), the messages (msgWinRequestMessage), the flags, the
//   persona compendium and the social-link checks, the fade / sound helpers (sub_108570 / sub_108670 /
//   sub_1086A0) and the cut-in.
void sub_3D3D20(EEContext& ctx);
// sub_3D4DE0 0x3D4DE0 [fclCombine_OpenMenuB]:
//   (owner) -> step. Adds menu step 4 (the record 0x6A48A0) to the fclCombine sequence, stores it in owner +32
//   and hides panel 7.
void sub_3D4DE0(EEContext& ctx);
// sub_3D4E90 0x3D4E90 [fclCombine_WaitMenuB]:
//   (owner) -> result / -1. Waits for that step (bit 3 of its object's flags): owner +32 cleared, panel 7 shown,
//   the payload's first word returned; otherwise -1.
void sub_3D4E90(EEContext& ctx);
// sub_3D4FF0 0x3D4FF0 [fclCombine_ListStep]:
//   (seq, step) -> 0 / nmSeqNullStep. A fclCombine list step: the cursor sounds (sub_10A4E0 0 on move down /
//   scroll, 5 on page / move up), then its states (jump table 0x7BB6C0): 1 hide the field and wait for the
//   element, 2 show it and panel 1, 3 the list held and decided rows (sub_40C650 / sub_40C5B0 / sub_40C6A0, a
//   message on a refusal), 4.
void sub_3D4FF0(EEContext& ctx);
// sub_3DA700 0x3DA700 [fclCombineList_Update2]:
//   (list) -> 0 / 1 / 2. The update of the two-persona list menu (fclCombineList.c): when the command list (+20)
//   reports closed, 1 (flag bit 4) or 2 with panel 5 shown; otherwise the cursor sounds and the phase +8 (jump
//   table 0x7BB840): 3 browse -- the decided persona checked (K_Assert lines 1125 / 1126; sub_3DA470 / the
//   selection rules), selected / unselected (sub_3DA570 / sub_3DA2A0), the panels (sub_3D8850), cancel / close;
//   then the result preview (sub_3DDB90 / sub_3DDD20, sub_3D6C90 .
void sub_3DA700(EEContext& ctx);
// sub_3DC2D0 0x3DC2D0 [fclCombinePanel_Single]:
//   (x, y, alpha, ..., entry, highlight, active) The persona panel of one list entry: the arcana frame
//   (sub_40E3C0 sprite 37, frame 2 (arcana - 1) + 1), the name (sub_3B32D0 from the name table $gp 0x7CE4E4, 17
//   bytes a persona, the colour by the highlight from 0x7CD79C) and the level (sprintf of 0x7CD798 drawn by
//   sub_40EB50); an inactive panel fades by 0x7CADD0.
void sub_3DC2D0(EEContext& ctx);
// sub_3DC700 0x3DC700 [fclCombinePanel_Multi]:
//   (x, y, alpha, list, entry, highlight) The panels of a multi-persona entry: for each selected persona its
//   arcana frame, name, level (as in fclCombinePanel_Single) and the slot mark (sprite 36), or an empty slot's
//   frame.
void sub_3DC700(EEContext& ctx);
// sub_3DCC90 0x3DCC90 [fclCombinePanel_Result]:
//   (x, y, alpha, ..., entry, highlight) The result panel: the result persona's arcana frame (sprite 57), name
//   and level, or for a persona built from an id (sub_176680) its frame and the eight skill / two marks (sprites
//   39 / 40) by the flags +100.
void sub_3DCC90(EEContext& ctx);
// sub_3DDB90 0x3DDB90 [fclCombineList_MakePreview]:
//   (src, out) Builds the 168-byte preview record of a fusion: cleared (memset), flags bit 0, the counts and the
//   persona (memcpy 84 + 52 bytes from the source), the stat deltas subtracted, the panel (+160) given its
//   flags, mode and position (sub_3C9D00 / sub_3C9E00 / sub_3C9E30 / sub_3C9B00); with a social link for the
//   result's arcana (sub_16DEB0 / sub_16DBA0), the link bonus (sub_3D58C0) in +164 and +104.
void sub_3DDB90(EEContext& ctx);
// sub_3DDD20 0x3DDD20 [fclCombineList_PreviewStep]:
//   (preview) -> 0 / 1 / 2. The preview's state machine (+4, jump table 0x7BB8B0): open, show, the yes / no
//   message (msgWinRequestMessage, msgWinLastSelection, sub_3C7850 / sub_3C7700), the skill choice (sub_3D8230,
//   sub_3D5DC0), the sounds; 1 = accepted, 2 = cancelled.
void sub_3DDD20(EEContext& ctx);
// sub_3DE470 0x3DE470 [fclCombineList_UpdateN]:
//   (list) -> 0 / 1 / 2. The update of the three-or-more-persona list menu: as fclCombineList_Update2 for its
//   recipes: the decided row's record (+20 +28) refused with sound 8 when flagged, else sound 1, the list
//   closed, the 84-byte result copied (memcpy), sub_3DEB20 / sub_3D6AE0 and the panels 7..22 shown; then the
//   preview steps.
void sub_3DE470(EEContext& ctx);
// sub_3E0B70 0x3E0B70 [fclShop_CloseSequence]:
//   (no args) Closes the shop's nm sequence ($gp 0x7CE688): when open, sub_3E0A10 and nmSequenceDestroy; the
//   slot is cleared either way.
void sub_3E0B70(EEContext& ctx);
// sub_3E5B00 0x3E5B00 [fclShopBg_EmitParticles]:
//   (bg, mode, base, n, alpha) Emits up to n particles into the 64 16-byte slots of the backdrop (a slot is free
//   when its life +22 is 0): life 30..49 (mode != 0) or 20..29, alpha range, the start position and speed from
//   RpRandom (sub_488F30 % 0xFFFF scaled; flag bit 1 picks the right-hand side), the colour byte 255, the angle
//   0..359; the live count +1036 grows.
void sub_3E5B00(EEContext& ctx);
// sub_3E5E20 0x3E5E20 [fclShopBg_StepParticle]:
//   (bg, p) One backdrop particle per frame: a delay counts down; otherwise it drifts (x by (speed + wobble) /
//   4, y by 2 or 4), the wobble re-rolled (RpRandom), the angle turned and wrapped to 0..360, the alpha faded in
//   over 25 frames from the backdrop's alpha (+5), drawn (sub_40E3F0 sprite 247) while visible, and the life
//   counted down (the live count -1 at 0).
void sub_3E5E20(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group shop (game/src/sweep/sweep1_shop.cpp): the shop steps' callbacks, the item / request / compendium lists
// and their drawers, the quantity selector, the facility sprite helper, the fcl and fclCombineEffect task updates.
// -------------------------------------------------------------------------------------------------------------------
// sub_3E9160 0x3E9160 [fclShopRoot_Fini]:
//   (seq, step) -> 0. The ROOT step's fini: for shop type 8 (the shop work record's word +0) the help element
//   (sub_40C9A0 of the step payload +16) closes and the root panel 1 is redrawn (sub_3E0C20(work, 1, 1)); every
//   other shop releases its list (sub_4003A0 of +12).
void sub_3E9160(EEContext& ctx);
// sub_3EAF90 0x3EAF90 [fclShopArmsCombine_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The ARMSCOMBINE (weapon fusion) step's update: hidden (flags bit 1) -> 0;
//   its list finished (sub_3FE5D0) -> nmSeqNullStep; a finished sub-list (+16, sub_3FE950) is destroyed; the
//   phases (+8, jump table 0x7BBC00): 0 decided; 1 / 2 the base-item list -- the decided row held, the persona
//   stock list (sub_3EFDE0 / sub_3FE850), the recipe (sub_401DE0, sub_402400), the yes / no and result messages
//   (msgWinRequestMessage, msgWinLastSelection, the item name through sprintf "%d" / sub_3C7BC0), the purchase
//   (sub_17C1C0 / sub_174B40), the cancel / close paths (nmCmdListCancelled / CloseNow, sub_3E0C20 panels).
void sub_3EAF90(EEContext& ctx);
// sub_3EBCB0 0x3EBCB0 [fclShopTrade_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The TRADE step's update: its list finished (sub_3FF570) -> nmSeqNullStep;
//   phase 1 releases the list; phase 2 the decided row (the payload +16): a tradable row (flag bit 4) with fewer
//   than 99 owned asks how many (sub_3FEE40), the confirmation message with the item name (sub_171110 / sprintf
//   / sub_3C7BC0), the trade (sub_3F1720); a refused row a message; cancel closes the list (jump table
//   0x7BBC50).
void sub_3EBCB0(EEContext& ctx);
// sub_3EC210 0x3EC210 [fclShopQuest_Init]:
//   (seq, step) -> 0. The QUEST step's init: the request list of the shop (sub_405AC0(shop, 0): the open
//   requests) into the payload +12, phase 1.
void sub_3EC210(EEContext& ctx);
// sub_3EC2C0 0x3EC2C0 [fclShopQuest_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The QUEST step's update (Elizabeth's requests): list finished (sub_405E30)
//   -> nmSeqNullStep; the decided request (payload +16): a taken / cleared one (flag bit 4) plays the refusal
//   sound 8 and its message; otherwise the request's text (sub_4032F0 / sub_403410 deadline), the yes / no
//   (msgWinLastSelection) and the acceptance (sub_405970 re-marks the row, sub_403800 / sub_403830 the
//   accessors, the count sub_17C700); cancel closes (jump table 0x7BBC70).
void sub_3EC2C0(EEContext& ctx);
// sub_3EC870 0x3EC870 [fclShopQuestCancel_Init]:
//   (seq, step) -> 0. The QUESTCANCEL step's init: the list of the accepted requests (sub_405AC0(shop, 1)) into
//   the payload +12, phase 1.
void sub_3EC870(EEContext& ctx);
// sub_3EC920 0x3EC920 [fclShopQuestCancel_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The QUESTCANCEL step's update: the decided accepted request (not flag bit
//   1): confirm sound, the cancel question with its name (sub_4038E0, sprintf / sub_3C7BC0), yes -> the request
//   dropped (sub_16E9B0 / sub_403340), its row removed (nmCmdListRemoveRow), the count (sub_17C700) and the
//   panel / list refresh (sub_40C170, sub_17D040, sub_3E0C20); cancel closes (jump table 0x7BBCA0).
void sub_3EC920(EEContext& ctx);
// sub_3ECEB0 0x3ECEB0 [fclShopBook_Init]:
//   (seq, step) -> 0. The BOOK (compendium summon) step's init: the compendium list (sub_409F50(shop, 0)) into
//   the payload +16, its panel object from the shop work record (+132) with the persona model (sub_3CDA60(work
//   +128), sub_3CDEE0(.., 1)) and the panel modes (sub_3C9F10 / sub_3C9F60, 5), phase 1.
void sub_3ECEB0(EEContext& ctx);
// sub_3ECFE0 0x3ECFE0 [fclShopBook_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The BOOK step's update: list finished (sub_40A2B0) -> nmSeqNullStep;
//   phases 1 / 2 the decided persona (confirm sound, payload +20, phase 3), 3 / 4 its detail panel (sub_40B840)
//   and the summon dialogue (sub_40B910), cancel closes the list and the root panel (sub_3E0C20).
void sub_3ECFE0(EEContext& ctx);
// sub_3ED4E0 0x3ED4E0 [fclShopBookRegist_Init]:
//   (seq, step) -> 0. The BOOKREGIST step's init: the registration list (sub_409F50(shop, 1): the stock) into
//   the payload +12, its panel object from the work record (+132) set to mode 2 / 0 and size 8 x 8 (sub_3C9E00 /
//   sub_3C9E30 / sub_3C9FB0), phase 1.
void sub_3ED4E0(EEContext& ctx);
// sub_3ED5E0 0x3ED5E0 [fclShopBookRegist_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The BOOKREGIST step's update (jump table 0x7BBCD0): list finished
//   (sub_40A490) -> nmSeqNullStep; the registration message (23) with the window flags, the decided persona's
//   panel (sub_3C9B00 / sub_3C9E70 / sub_3C9EE0), the yes / no (msgWinLastSelection), the registration
//   (sub_17C8C0 / sub_17C960) and the row removed, the panel modes (sub_3C9D00 16), cancel.
void sub_3ED5E0(EEContext& ctx);
// sub_3EDF20 0x3EDF20 [fclShopHelp_Init]:
//   (seq, step) -> 0. The HELP step's init: the help element (sub_40C6F0(1)) into the payload +8, state 2.
void sub_3EDF20(EEContext& ctx);
// sub_3EDF80 0x3EDF80 [fclShopHelp_Fini]:
//   (seq, step) -> 0. The HELP step's fini: the help element closes (sub_40C9A0 of the payload +8).
void sub_3EDF80(EEContext& ctx);
// sub_3EDFC0 0x3EDFC0 [fclShopHelp_Update]:
//   (seq, step) -> 0 / nmSeqNullStep. The HELP step's update: the facility state 3 (sub_40CA00) ->
//   nmSeqNullStep; the cursor sounds; states (jump table 0x7BBD10): 1 the root panel back, 2 / 3 once the
//   element is ready (sub_3DFF30) the panel off and the list released, then the decided topic (sub_40C650 /
//   sub_40C5B0 / sub_40C6A0, a message when refused), cancel / close.
void sub_3EDFC0(EEContext& ctx);
// sub_3EE2D0 0x3EE2D0 [fclShopHelp_Draw]:
//   (seq, step) -> 0. The HELP step's draw: the help element (sub_40CAD0 of the payload +8).
void sub_3EE2D0(EEContext& ctx);
// sub_3F2940 0x3F2940 [fclShopLineup_AddRows]:
//   (list, entries, n, flags) -> rows added. Adds the shop lineup's entries to a list: for each non-empty entry
//   id (s16, 12-byte entries) the item's kind and owner (sub_170ED0) filtered by the flags (0x400 new only,
//   0x800 equipment kinds 1..3, 0x1000 / 0x2000 / 0x4000 / bit 0), the stock / sold-out checks (sub_1712D0 ==
//   128, sub_3F1A10, sub_17D800 / datGetFlag / sub_17D060), the row (nmListFindByWord4 / nmCmdListAddRow) priced
//   by sub_3E6DC0 / sub_3F1BA0 / sub_3F2DC0, the record table 0x6ACC60.
void sub_3F2940(EEContext& ctx);
// sub_3F2F70 0x3F2F70 [fclShopLineup_Build]:
//   (list, shop, flags) -> 1 / 0. Builds a shop's lineup list: shop index <= 8 (K_Assert fclShopMisc.c 185); the
//   lineup record of 0x6AC9D0 (36 bytes; the second half when sub_17D800 -- The Answer -- is set), the list's
//   work +4 / +6 = shop; the dated lineup (sub_3F00D0) priced by sub_3F25E0, else the record's entry lists
//   through sub_3F2940 and the extras (sub_16C470, sub_3F03E0).
void sub_3F2F70(EEContext& ctx);
// sub_3F3FC0 0x3F3FC0 [fclShopList_DrawFrame0]:
//   (x, y, alpha, list) The list drawer of the drawer tables' entry 0: the window alpha by the list status
//   (nmCmdListStatus28: 1 / 12 full, 20 the given alpha), the frame quad (RpSkyRenderStateSet /
//   pfn_RwRenderStateSet blends, sub_40D610), sprites 35 / 36 at the work's offsets (+56.., sub_40E3C0 /
//   sub_40E3F0 with the scroll bar), the rows (sub_3F7730 / sub_3F5AB0 / sub_3F61D0) and the help line
//   (sub_3F7A80).
void sub_3F3FC0(EEContext& ctx);
// sub_3F4350 0x3F4350 [fclShopList_DrawFrame1]:
//   (x, y, alpha, list) The list drawer of entries 1 / 5..7: the frame sprite 34 and the scroll-bar sprites 36 /
//   37 (position = 104 x the scroll word / 0xFFFF) at the work's offsets, the rows (sub_3F7730, sub_3F5D10) and
//   the help line (sub_3F7A80).
void sub_3F4350(EEContext& ctx);
// sub_3F4870 0x3F4870 [fclShopList_DrawFrame3]:
//   (x, y, alpha, list) The list drawer of entry 3: frame sprite 22, scroll-bar sprites 24 / 25 (86 x scroll /
//   0xFFFF), the rows and the help line.
void sub_3F4870(EEContext& ctx);
// sub_3F7390 0x3F7390 [fclShopArmsCombine_DrawResult]:
//   (x, y, alpha, ..., row) The weapon-fusion result panel: sprites 219..228, for each of the two ingredients
//   its icon (sprite 27), name (sub_171110 -> sub_3B2CB0), count ("%d" through sub_40EB50) and owner checks
//   (sub_170ED0, sub_16F630 / sub_170760).
void sub_3F7390(EEContext& ctx);
// sub_3F7A80 0x3F7A80 [fclShopList_DrawHelp]:
//   (x, y, alpha, list, row) The help line of an item row through the item text drawer sub_3C7E20: a persona row
//   (work +6 == -1 with flag 0x1000) as kind 2; an equipment row (flag 0x1000) as kind 1 with the value of the
//   item table (sub_1715F0: 255 -> the row's own byte +13) in bits 16..; else kind 1 with the id.
void sub_3F7A80(EEContext& ctx);
// sub_3F7C60 0x3F7C60 [fclShopList_DrawHelp2]:
//   (x, y, alpha, list, row) The same help line without the item-table lookup (kind 0 for plain items).
void sub_3F7C60(EEContext& ctx);
// sub_3F7D50 0x3F7D50 [fclShopRow_DrawSlide]:
//   (x, y, alpha, list, row) A row drawer for the sliding list (status 12): the slide-in offset from the row's
//   distance to the cursor (5 steps of 30 / 5 pixels, div1), the fade-in after 4 frames, the cursor sprite 35
//   for the selected row, the row body by the list kind (work +6: -2 / -3 / -5 / other -> sub_3F55B0 /
//   sub_3F5830 with style 3 / 1 / 2).
void sub_3F7D50(EEContext& ctx);
// sub_3F7FE0 0x3F7FE0 [fclShopRow_DrawNormal]:
//   (x, y, alpha, list, row) The row drawer for status 20: the cursor sprite 35 on the selected row and the row
//   body by the list kind (sub_3F55B0 / sub_3F5830, style 3 / 1 selected, 2 otherwise).
void sub_3F7FE0(EEContext& ctx);
// sub_3F8180 0x3F8180 [fclShopRow_DrawOpen]:
//   (x, y, alpha, list, row) The row drawer for status 1 (open): on the selected row the frame sprites of the
//   table 0x6AEEE0 (6 x 4 by the list's +4: plain / flag 4 / flag 8 / end) and the row body (sub_3F55B0 /
//   sub_3F5830).
void sub_3F8180(EEContext& ctx);
// sub_3F85A0 0x3F85A0 [fclShopRow_Draw]:
//   (x, y, alpha, list, row) The row drawer of the drawer tables' entries 9..11: by the list status (1 open, 20
//   normal at the work's offsets +40 / +42, 12 sliding) one of the three above.
void sub_3F85A0(EEContext& ctx);
// sub_3F86A0 0x3F86A0 [fclShopRow_DrawAlt0]:
//   (x, y, alpha, list, row) A row drawer (table entry 8): status 1 the frame sprites of 0x6AEEE0 and the row
//   body (sub_3F55B0); 20 / 12 the same with the offsets / the slide.
void sub_3F86A0(EEContext& ctx);
// sub_3F8A00 0x3F8A00 [fclShopRow_DrawAlt1]:
//   (x, y, alpha, list, row) A row drawer (table entry 9): the frame sprites, the slide (div1) and the row body
//   (sub_3F55B0) by the list status.
void sub_3F8A00(EEContext& ctx);
// sub_3F9220 0x3F9220 [fclShopRow_DrawAlt3]:
//   (x, y, alpha, list, row) A row drawer (table entry 11): the slide and fade by the cursor distance for status
//   12, the cursor sprite and the row body (sub_3F55B0).
void sub_3F9220(EEContext& ctx);
// sub_3FB6B0 0x3FB6B0 [fclShopQuantity_Update]:
//   (sel) -> 0 / 1 / 2. The quantity selector's dialogue (jump table 0x7BBD80): open (flag bit 0) -> 3 the
//   slide-in (+42 alpha 255, +48 -500), the count changed by up / down (sub_3FB2F0 / sub_3FB530 with sounds),
//   the price line (sprintf / sub_3C7BC0, cosf for the blink), the confirmation (msgWinLastSelection); 1 = buy
//   (flag 0x400), 2 = cancel (flag 0x800); the closing clears the flags (sub_3EED10(0)).
void sub_3FB6B0(EEContext& ctx);
// sub_3FBE70 0x3FBE70 [fclShopQuantity_Init]:
//   (sel, row) Initialises the 152-byte quantity selector from a row: cleared, the equipped item of the row's
//   kind (datGetEquipmentIdx(1, kind) -> sub_3F1DC0 into +80), the 28-byte row record copied to +108, open flag,
//   state 1.
void sub_3FBE70(EEContext& ctx);
// sub_3FCAD0 0x3FCAD0 [fclShopEquip_DrawHelpA]:
//   (x, y, alpha, list) The help line of the equipment list's selected row at (293, 227) through sub_3C7E20
//   (persona kind 2 / equipment kind 1 with its byte +13 / item kind 0); the 0x7CD970 drawer set's list draw A.
void sub_3FCAD0(EEContext& ctx);
// sub_3FCDC0 0x3FCDC0 [fclShopEquip_DrawRow]:
//   (x, y, alpha, list, row) An equipment row: the slot frame (sprite 0, frame 2 kind + selected), the name
//   (sub_171110 -> sub_3B2CB0, style 6 on the cursor row), and the stat by the kind bits 8..11 (0: +20, 1: +24,
//   2: +26 as "%d" through sub_40EB50 in the colours of 0x7CD958).
void sub_3FCDC0(EEContext& ctx);
// sub_3FD010 0x3FD010 [fclShopEquip_DrawRowA]:
//   (x, y, alpha, list, row) The 0x7CD970 drawer set's row draw A: a tail call into sub_3FCDC0.
void sub_3FD010(EEContext& ctx);
// sub_3FD030 0x3FD030 [fclShopEquip_DrawHelpB]:
//   (x, y, alpha, list) The help line at (83, 250): the drawer set's list draw B (same body as A).
void sub_3FD030(EEContext& ctx);
// sub_3FD320 0x3FD320 [fclShopEquip_DrawRowB]:
//   (x, y, alpha, list, row) The drawer set's row draw B: sub_3FCDC0's body with the colours of 0x7CD960.
void sub_3FD320(EEContext& ctx);
// sub_3FD570 0x3FD570 [fclShopEquip_BuildMembers]:
//   (shop, list*) Builds the party list of the equipment screen: the hero (row 1) and every member of the 11
//   flags of 0x6AF140 that is set (member 343 only without flag 168, member 338 only with flag 82), each with
//   its equipment list (sub_3FE020) and element (sub_3DFEB0) in a 12-byte row (nmListAppendNew).
void sub_3FD570(EEContext& ctx);
// sub_3FD730 0x3FD730 [fclShopEquip_RefreshMember]:
//   (member, row) Refreshes the four equipment rows of a member: for slots 0..3 the equipped item
//   (datGetEquipmentIdx -> sub_3F1DC0) copied (28 bytes) into the row records.
void sub_3FD730(EEContext& ctx);
// sub_3FDCC0 0x3FDCC0 [fclShopEquip_Draw]:
//   (screen, view, list*) The equipment screen draw: with the view's alpha (+38), for mode 3 the frame (sprite
//   72) and every member row (sub_3FD140) at the list's position and row pitch, else the single member's panel
//   (sub_177790 / sub_3B32D0 / sub_3FCBE0) in the colours of 0x7CD968.
void sub_3FDCC0(EEContext& ctx);
// sub_3FE020 0x3FE020 [fclShopEquip_BuildList]:
//   (side, member) -> list. The four-slot equipment list of a member: an 88-byte list (sub_3C58F0(0, 88, 5,
//   36)), side < 2 (K_Assert fclShopMisc.c 5258) in its work +4, four rows with the equipped items
//   (datGetEquipmentIdx -> sub_3F1DC0, 28 bytes), the drawers of the set 0x7CD970 by side, the position of
//   0x6AF170 and the sizes 10 / 5.
void sub_3FE020(EEContext& ctx);
// sub_4026B0 0x4026B0 [fclShopGiveItems]:
//   (item, n, flags) -> 1 / 0. Gives n copies of an item if they fit: a kind-4 item (sub_171250) succeeds at
//   once; otherwise needs 300 - the owned count (sub_16F490(1)) >= n; each copy built (sub_1828D0, the random
//   roll sub_488F30 for flags bit 0, the level byte from the item's bits 16..23 unless bit 2) and stored
//   (sub_1830C0).
void sub_4026B0(EEContext& ctx);
// sub_402800 0x402800 [fclShopRequest_SetMessageArgs]:
//   (request) Fills message slot 8's arguments for a request (sub_3C7D60(8)): the reward text by the reward kind
//   (+10: 4 "oooooooo", 3 "%d", 1 / 2 the item format, 0 the item name sub_171110), the target (sub_3A4010 kinds
//   2 / 17), the client's name ($gp 0x7CE4E4 / 0x7CE4E8 tables), the deadline and state (sub_4038E0, sub_403800
//   / sub_403830 / sub_403740).
void sub_402800(EEContext& ctx);
// sub_402C80 0x402C80 [fclShopRequest_SetWindowArgs]:
//   (request) The same arguments for the message window (sub_3C7BC0 / sub_3C7C20 instead of the message slot).
void sub_402C80(EEContext& ctx);
// sub_4045D0 0x4045D0 [fclShopRequest_AddOpen]:
//   (list) Adds the open requests: for each of the request table's records (64 bytes, $gp 0x7CD8F0 / count
//   0x7CD8F4; request 55 only with sub_17D7B0) that has a reward (+58) and whose two gating flags (+4 / +6,
//   0xFFFF = none) are set or whose condition holds (sub_3F04F0(+8, 2)): a 12-byte row with its id and element,
//   marked by sub_405970.
void sub_4045D0(EEContext& ctx);
// sub_405970 0x405970 [fclShopRequest_MarkRow]:
//   (list, row) -> 0. Marks a request row: done (flag 4464 + id) -> 3; available (sub_3F04F0(+8, 0)) -> taken or
//   not (sub_17C610); else 2 (locked); a marked row gets flag bit 4 and the mark in +6; an unmarked one flag
//   0x100 unless flag 4351 + id is set (new).
void sub_405970(EEContext& ctx);
// sub_405AC0 0x405AC0 [fclShopRequest_BuildList]:
//   (shop, accepted) -> list. The request list: a 12-byte-row list (sub_3C58F0(0, 12, 5, 28)); accepted -> the
//   accepted requests (sub_17C700 / sub_17C670) with their states (sub_403380: 1..4), flag bit 1; else the open
//   ones (sub_4045D0); sorted (sub_405E00), its element, the row remove / draw / row draw callbacks sub_405A90 /
//   sub_407180 / sub_407210, the sizes 10 / 10, the panel set-up (sub_404750(list, 6, 0)).
void sub_405AC0(EEContext& ctx);
// sub_405F70 0x405F70 [fclShopRequest_DrawPanel]:
//   (x, y, alpha, list, ...) The request detail panel: the two coordinate tables 0x6AF5E0 / 0x6AF600, the
//   deadline in days ("%02d", datGetDaysSinceApr5 / clndGetDaysSinceStartFromDate) with a pulsing alpha (sinf),
//   the message arguments (sub_402800) and the reward line (sub_3C7E20), the panel sprites (sub_40E3C0), the
//   seen flag (datSetFlag).
void sub_405F70(EEContext& ctx);
// sub_4064E0 0x4064E0 [fclShopRequest_DrawReward]:
//   (x, y, alpha, list) The selected request's reward panel: sprites 81..88, the message arguments (sub_402800),
//   the reward's text (sub_3C7E20 kind 6 with the record's +50), its count ("%d" via sub_40EBC0) or item name
//   (sub_3F1BA0 / sub_171110 / sub_3B32D0).
void sub_4064E0(EEContext& ctx);
// sub_409F50 0x409F50 [fclShopBook_BuildList]:
//   (shop, regist) -> list. The compendium list: a 40-byte list (sub_3C58F0(0, 40, 8, 24)); regist -> the stock
//   personas that can be registered (sub_174A90 / sub_17CA10), work +4 = -9; else the registered compendium
//   sorted (sub_409C80, sub_40A6D0(list, 1)), work +4 = -8; the cursor (nmCmdListSelect), +36 the money
//   (sub_17CF00), the elements +28 / +32, the row remove / draw / row draw callbacks sub_409F20 / sub_40B630 /
//   sub_40B780, the layout (sub_4072D0).
void sub_409F50(EEContext& ctx);
// sub_40A2B0 0x40A2B0 [fclShopBook_UpdateList]:
//   (list) -> 1 closed / 0. The compendium list's per-frame step: its elements and the rows' elements stepped
//   (sub_3E0650), the list updated (nmCmdListUpdate == 3 -> closed), the cursor sounds, the layout element 2
//   (sub_4072D0); on closing the elements 14 and 15 (summon) / 16 (register) and 13.
void sub_40A2B0(EEContext& ctx);
// sub_40A490 0x40A490 [fclShopBookRegist_UpdateList]:
//   (list) -> 1 closed / 0. The registration list's per-frame step: the element and the rows' elements stepped,
//   the list updated, the cursor sounds, layout element 2.
void sub_40A490(EEContext& ctx);
// sub_40B840 0x40B840 [fclShopBook_OpenDetail]:
//   (list) The compendium's detail panel for the decided persona: work +24 = 0, +16 = 1, open flag; the panel
//   (+8) given the persona (sub_3C9B00), mode 8, size 3, side 2 (sub_3C9D00 / sub_3C9E00 / sub_3C9E30); the shop
//   root panel 13 (sub_3E0C20).
void sub_40B840(EEContext& ctx);
// sub_40B910 0x40B910 [fclShopBook_SummonStep]:
//   (list) -> 0 / 1 / 2. The compendium summon dialogue (work +16, jump table 0x7BBE60): states 1..4 wait for
//   the list (nmCmdListStatus & 5); 5 the checks -- already in the stock (sub_1749A0: message 21), the stock
//   full (sub_1756F0 / sub_175410), the price against the money (sub_16DD50, "%d" / sub_3C7BC0) --, the yes / no
//   (msgWinLastSelection), the purchase (sub_16E9B0, sub_174FB0), the list refresh (sub_3C5AF0,
//   nmCmdListCursorDown), the detail panel / model (sub_3CDBA0 / sub_3C9E70 / sub_3CDE00), the pad paging
//   (0x7E0952 / 0x7E095A).
void sub_40B910(EEContext& ctx);
// sub_40D540 0x40D540:
//   (script) -> 1. A script COMM handler (table index 44, no arguments): closes the open facility by the
//   facility kind $gp 0x7CDA00 (jump table 0x7BBF10): kinds 0..6 and 8 the shop sequence (sub_3E0B70), 7
//   sub_3D0560; any other sets it to -1.
void sub_40D540(EEContext& ctx);
// sub_40E420 0x40E420 [fclSprite_DrawBank]:
//   (x, y, alpha, sprite, frame, ...) Draws a sprite of the facility sprite bank ($gp 0x7CE6A0): sub_40E930 with
//   the bank as its sixth argument.
void sub_40E420(EEContext& ctx);
// sub_40E930 0x40E930 [fclSprite_DrawScaled]:
//   (x, y, alpha, sprite, frame, bank, ...) Draws one facility sprite: the bank's 8-byte sprite record (+12
//   table: {u8 file, s16 index, s16 dx, s16 dy}), a one-shot sprite handle (sprCreateHandle of the record's file
//   and index + frame) placed at x + dx x scale, y + dy x scale (FPU accumulator, $f13 / $f15), alpha 255 - a,
//   the colour words, drawn (sub_1127D0 / sub_115980).
void sub_40E930(EEContext& ctx);
// sub_413B70 0x413B70 [fclBank_UpdateDraw]:
//   (task, view, req) The draw step of two fcl tasks (descriptors 0x6B1900 / 0x6B1920, 156-byte work): the
//   coordinate tables 0x6B1190 / 0x6B1220 / 0x6B1340 / 0x6B1370 / 0x6B13A0 / 0x6B1400 / 0x6B1460 copied to the
//   stack, then by the view's state (jump table 0x7BC020) the panel's elements placed and faded (sub_3E0940 /
//   the shop root payload).
void sub_413B70(EEContext& ctx);
// sub_415DC0 0x415DC0 [fclTask_UpdateDraw]:
//   (task, view, req) The draw step of the fcl task of descriptor 0x6B19C8 (216-byte work): the coordinate table
//   0x6B1710 copied to the stack, the request's mode (+6: 1 -> +76 = 0, 4 -> +76 = 1, 2) and the panel elements
//   placed (sub_3E0940 / the root payload, the scale 0x7CDA4C).
void sub_415DC0(EEContext& ctx);
// fclCmbEff_UpdateCmbEffCalcTask 0x417410:
//   (task) -> 0 / -1. Update of the kwlnTask "fclCmbEffCalc": the work's phase +0: 0 -> set-up (sub_4177E0); 1
//   -> once loaded (sub_4178C0) flag bit 1 cleared; 2 -> once the effect is built (sub_41B530); 3 -> started
//   (sub_41B550), flags 4 | 1; 4 -> the effect stepped (sub_41B5C0 with +68) until it ends.
void fclCmbEff_UpdateCmbEffCalcTask(EEContext& ctx);
// fclCmbEff_UpdateCmbEffDrawTask 0x417540:
//   (task) -> 0. Update of the kwlnTask "fclCmbEffDraw": draws the fusion effect's 2D part (sub_41B810) while
//   the work's flag bit 0 is set.
void fclCmbEff_UpdateCmbEffDrawTask(EEContext& ctx);
// fclCmbEff_UpdateCmbEffDraw3DTask 0x417590:
//   (task) -> 0. Update of the kwlnTask "fclCmbEffDraw3D": draws the 3D part (sub_41B950) while flag bit 0 is
//   set.
void fclCmbEff_UpdateCmbEffDraw3DTask(EEContext& ctx);

}  // namespace p3fes::game
