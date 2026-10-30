// Phase 5 slice libs12: the CRI Sofdec library band 0x580588-0x58FF70 -- MWSFD's player calls (mwPlyStartSj,
// the loop / seamless play calls, the statistics getters), the SFD library init, the stream records of an SFD handle
// (layout, SJ attach, the locked accessors), the system-stream demux server and the video decode server with their
// start-code searches. Register-ABI bodies started from p3fes_handgen (every statement, charge and check point is the
// generator's: game/include/p3fes/game/hg_cpu.h): arguments in $a0.., the result in $v0. Each declaration carries the
// function's role and, in brackets, a proposed name taken from the binary's own error / banner text (ADR-0009:
// proposals only, in symbols/deltas/libs12.sym). No CRI material was opened. The records below name the offsets the
// bodies use (each constant equals the literal it replaces); the MWSFD player's are libs5::ply's.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/libs5.h"

namespace p3fes::game {

namespace libs12 {
// MWSFD player words beyond libs5::ply: the SJ start record (mwPlyStartSj sets them)
namespace plyx {
constexpr s32 kSjStat = 464;              // 2 after mwPlyStartSj
constexpr s32 kSjW0 = 468;                // cleared by mwPlyStartSj
constexpr s32 kSjW1 = 472;
constexpr s32 kSjW2 = 476;
}  // namespace plyx
// SFD handle stream records: 116 bytes each from +4880 (libs5::sfdh::kStream, 4884, is their word +4)
namespace stm {
constexpr s32 kBase = 4880;
constexpr s32 kStride = 116;
constexpr s32 kType = 0;                  // 1 / 2 / 3 fixed buffers, 4 waits for an SJ, 5 owns its memory SJ
constexpr s32 kFlag = 4;                  // set with the chunk descriptor
constexpr s32 kInEnd = 8;                 // input end flag (sub_589CD0 / sub_589CB0)
constexpr s32 kOutEnd = 12;               // end flag (sub_589D10 reads it, sub_589CF0 sets it)
constexpr s32 kDesc = 16;                 // 24-byte chunk descriptor {kind, SJ, address, size, offset, 0}
constexpr s32 kSj = 20;                   // the SJ (descriptor word 1)
constexpr s32 kBufSize = 28;              // descriptor word 3 (sub_589510)
constexpr s32 kPos = 40;                  // two words read / written under the lock (sub_589438 / sub_5894A8)
constexpr s32 kAvail = 48;                // available amount (sub_589550)
constexpr s32 kCount = 52;                // consumed count, -1 = not counting (sub_589650 / sub_589530)
}  // namespace stm
// SFD handle transfer slots (libs5::sfdh::kTrn, 68 bytes each): slot 1 is the system-stream demux, slot 2 the video
// decoder; each holds its work pointer at +8, its input stream at +16 and its output streams after it
namespace trn {
constexpr s32 kDemux = 8052;              // slot 1
constexpr s32 kDemuxWork = 8060;          // the demux record (handle +8600, sub_58DE40)
constexpr s32 kDemuxIn = 8068;            // input stream index
constexpr s32 kDemuxOut2 = 8080;          // the third output stream (+8072 / +8076 are the other two)
constexpr s32 kVideo = 8120;              // slot 2
constexpr s32 kVideoWork = 8128;          // the video decoder record
constexpr s32 kVideoIn = 8136;            // input stream index
constexpr s32 kVideoOut = 8140;           // output stream index
}  // namespace trn
}  // namespace libs12

// Starts a player on an input SJ: handle check (E1122609), resets the player (sub_580628), stores the SJ (+444),
// status word +464 = 2, clears +468..+476, then sub_580270 and the play start sub_57C730 (tail call).
void sub_580588(EEContext& ctx);  // 0x580588 [mwPlyStartSj]
// Asks ADXF_GetFnameRangeEx (sub_53DD10) for the range of the player's file name (+420) into three stack words; on
// success marks a pending file start (+428 = 1) with the three words at +432..+440, else reports E211151.
void sub_580A98(EEContext& ctx);  // 0x580A98
// Thunk: sub_588270 on the player's SFD handle (+60), as a tail call.
void sub_580C20(EEContext& ctx);  // 0x580C20
// Thunk: sub_5882F0 on the player's SFD handle (+60), as a tail call.
void sub_580C38(EEContext& ctx);  // 0x580C38
// Thunk: sub_588168 on the player's SFD handle (+60), as a tail call.
void sub_580C50(EEContext& ctx);  // 0x580C50
// Thunk: sub_5881F8 on the player's SFD handle (+60), as a tail call.
void sub_580C68(EEContext& ctx);  // 0x580C68
// Resets the four MWSFD words 0x7B4528..0x7B4534 to 1, 0, 0, 0.
void sub_580C98(EEContext& ctx);  // 0x580C98
// Handle check (E202232, result 0); the dropped-frame count: the skipped decodes (sub_5812D8) plus sub_57F058's count.
void sub_581270(EEContext& ctx);  // 0x581270 [mwPlyGetNumDropFrm]
// Handle check (E1122619, result 0); with the player's SFD handle (sub_5811D0) reads its statistics (sub_5994F0) to
// the stack and returns word 1 - word 4, else 0.
void sub_5812D8(EEContext& ctx);  // 0x5812D8 [mwPlyGetNumSkipDec]
// The player's SFD statistics: sub_5994F0(SFD handle, out) when the player has one (+60), else memset(out, 0, 168).
void sub_581628(EEContext& ctx);  // 0x581628
// sub_599418 on the player's SFD handle (+60) when it has one.
void sub_581660(EEContext& ctx);  // 0x581660
// Returns the player's word +64 (its ADXT player).
void _M_numpunct_facet__CQ24_STL8ios_base(EEContext& ctx);  // 0x5816E0
// Handle check (E1122623, result 0); reads the statistics (sub_581628) to the stack and returns word 4.
void sub_582040(EEContext& ctx);  // 0x582040 [mwPlyGetNumSkipEmptyB]
// Handle check (E1122624); returns the file input's SJ (+448).
void sub_582118(EEContext& ctx);  // 0x582118 [mwPlyGetInputSj]
// Thunk: sub_59FA38.
void sub_5827D8(EEContext& ctx);  // 0x5827D8
// Creation-parameter check: sub_5829B8 on the parameter's word 12 compared with 1, then, when word 34 is set,
// sub_5A1380(word 34, word 35) compared with 1.
void sub_582968(EEContext& ctx);  // 0x582968
// Entry (n mod 8, truncating division) of the 20-byte table at $a0 + 192: its word 2 when its word 0 is 1, else 0.
void sub_5829B8(EEContext& ctx);  // 0x5829B8
// Maps an MwsfdBufFmt value to 1, 2 or 3; any other value reports E201184.
void sub_582A58(EEContext& ctx);  // 0x582A58
// Fills a frame description: words +68 / +72 from the source's words 3 / 4; format 3 splits the buffer in three planes
// (sub_57EC00) and stores Y, Cb, Cr plane records (+4, +20, +36; the chroma ones at half size), other formats one
// plane record.
void sub_582AB8(EEContext& ctx);  // 0x582AB8
// Copies the source's word +52 to the destination's word +76.
void sub_582B88(EEContext& ctx);  // 0x582B88
// Stores a three-word plane record {a1, a2, a3} at $a0.
void sub_582B98(EEContext& ctx);  // 0x582B98
// Reads two values of the SFX handle (+168) with sub_59FEF8 into the output's words 20 / 21 and clears words 22 / 23.
void sub_582BA8(EEContext& ctx);  // 0x582BA8
// Handle check (E2011915, result 0); the SFX composition mode of the player (sub_59FDB8 on sub_582828's handle), with
// 81 and 97 both reported as 65.
void sub_583058(EEContext& ctx);  // 0x583058 [mwPlyFxGetCompoMode]
// Handle check (E1122634); links the stream (sub_584830 1), starts on the file SJ (sub_580588 with +448), sub_580900,
// sub_55D600 on the LSC (+72), calls the input SJ's vtable +20 when there is one, the play start (sub_57C730) and
// clears +680.
void sub_584190(EEContext& ctx);  // 0x584190 [mwPlyStartSeamless]
// Handle check (E1122641); sets the loop flag $a1 on the player's LSC (+72) with sub_55DB58.
void sub_584230(EEContext& ctx);  // 0x584230 [mwPlySetLpFlg]
// Handle check (E1122630) and file name check (E10915A); sets the file name (sub_5809B0), resets the LSC (sub_55D668),
// enters the name (sub_5840D0 with +420), loop flag 1 (sub_584230) and the seamless start (sub_584190).
void sub_584290(EEContext& ctx);  // 0x584290 [mwPlyStartFnameLp]
// Handle check (E1122631); loop flag 0 (sub_584230), then a second handle check (E1122635) and the stream unlink
// (sub_584830 0).
void sub_584338(EEContext& ctx);  // 0x584338 [mwPlyReleaseLp]
// Handle check (E1122642); sets the link byte (+112) to $a1. Unlinking a linked player requests termination (+113 =
// 1); linking an unlinked one calls sub_589F70 on the SFD handle and reports E99072101 when it fails.
void sub_584830(EEContext& ctx);  // 0x584830 [mwPlyLinkStm]
// MWSFD's fixed buffer sizes: 149,988 / 40,000 / 2,048 into the three outputs; returns their sum.
void sub_5849A0(EEContext& ctx);  // 0x5849A0
// Returns 0x7B4538, the address of the audio-slave interface pointer.
void sceLibgcc32GetErxEntries_19(EEContext& ctx);  // 0x5851A0
// Thunk: sub_547558.
void sub_586490(EEContext& ctx);  // 0x586490
// Data-referenced transfer callback (needs at least 288 bytes): sub_54ABA8 over the data; when that is 0 and
// sub_58BBB0 < 108, the length sub_586FE0 accepts; stores the count to *$a3, sub_586C10 into the work's (+8196)
// callback +60 and adds the count to the 64-bit total +2504.
void sub_586F20(EEContext& ctx);  // 0x586F20
// Words +12 / +16 of sub_588138's record into the two outputs; 0, or -1 when there is no record.
void sub_587218(EEContext& ctx);  // 0x587218
// Thunk: sub_589E38 (the SJ class uuids).
void sub_588720(EEContext& ctx);  // 0x588720
// Lays out an SFD handle's streams from its creation record: the eight buffer offsets (sub_588878), streams 0..2
// (sub_5888B8: residue of the first size, 2048, 0), stream 3 (sub_588AB8), then sub_588B70 / sub_588C98; stops at the
// first error.
void sub_588740(EEContext& ctx);  // 0x588740
// Running offsets: out[i] = base + the sum of the first i of eight sizes.
void sub_588878(EEContext& ctx);  // 0x588878
// Sets up stream n (116-byte record): with a size, a memory SJ over its buffer (sub_588978), the chunk descriptor
// (sub_588E98, flag 1) and the header as type 5 (owns its SJ); without, the header as type 4 (waits for an SJ).
void sub_5888B8(EEContext& ctx);  // 0x5888B8
// Memory SJ over a buffer: record {0, sj, addr, size - offset, offset, 0}; the SJ from sub_562388; error -16776180 (no
// room) or -16776182 (no SJ) through sub_58BE40.
void sub_588978(EEContext& ctx);  // 0x588978
// Destroys the SJs of streams 0, 1, 2 (sub_588A50).
void sub_588A10(EEContext& ctx);  // 0x588A10
// Stream n of type 5: destroys its SJ (vtable +12) and clears the pointer.
void sub_588A50(EEContext& ctx);  // 0x588A50
// Sets up stream n as a ring of type 1 over the handle's buffers (+5808, +7848): the record, then fifteen 16-byte
// descriptors.
void sub_588AB8(EEContext& ctx);  // 0x588AB8
// Sets up stream n as type 2: the record, its address / size and cleared counters.
void sub_588B70(EEContext& ctx);  // 0x588B70
// Sets up stream n as type 3: the record and two cleared 16-byte descriptors.
void sub_588C98(EEContext& ctx);  // 0x588C98
// Stream record header: type, flag, words 2 / 3 cleared, words 19 / 20 = 9.
void sub_588CE8(EEContext& ctx);  // 0x588CE8
// Attaches an input SJ to an SFD handle: checks the parameter (sub_588DE0, error -16776184); picks stream 0, 1 or 2 by
// the handle's kind (sub_59BCD0 1 / 2 / 3); the stream must be type 4 (error -16776183); then its chunk (sub_588E98).
void sub_588D38(EEContext& ctx);  // 0x588D38
// Validates an SJ attach parameter: 0 when word 1 is set and either word 0 is set, or word 2 is set with word 3 > 0
// and word 5 <= 0; -1 otherwise.
void sub_588DE0(EEContext& ctx);  // 0x588DE0
// Under the SFD lock (sub_58C100 / sub_58C118): sets the flag word, copies the 24-byte source descriptor, clears the
// pair at +24 and the words +32 / +36, and sub_597E80 on +40.
void sub_588E98(EEContext& ctx);  // 0x588E98
// Clears two words.
void sub_588F38(EEContext& ctx);  // 0x588F38
// Copies the 16-byte descriptor j of stream n (+4896 + 116n + 16j) to the output.
void sub_588F90(EEContext& ctx);  // 0x588F90
// Chunk read with lane 0: $a3 = 0, then sub_589018 entered past its prologue (0x589030).
void sub_589000(EEContext& ctx);  // 0x589000
// Chunk release with lane 0: $a3 = 0, then sub_5890F0 entered past its prologue (0x589108).
void sub_5890D8(EEContext& ctx);  // 0x5890D8
// Moves the data of an SJ into two chunks: reads the free amount (vtable +36), takes a chunk (+24); when it is short,
// takes a second one and puts it back (+28); puts the first back (+28).
void sub_5892E8(EEContext& ctx);  // 0x5892E8
// Takes a chunk from an SJ lane (+24) and puts it to the other lane (+32).
void sub_5893E0(EEContext& ctx);  // 0x5893E0
// Reads stream n's two words +40 / +44 (4920) under the SFD lock.
void sub_589438(EEContext& ctx);  // 0x589438
// Writes stream n's two words +40 / +44 (4920) under the SFD lock.
void sub_5894A8(EEContext& ctx);  // 0x5894A8
// Stream n's word +28 (4908).
void sub_589510(EEContext& ctx);  // 0x589510
// Stream n's word +52 (4932).
void sub_589530(EEContext& ctx);  // 0x589530
// Stream n's available amount under the SFD lock: word +48, or when it is 0 and +52 is set, +52 plus the SJ's amount
// (vtable +36, lane 1); a negative sum gives 0x7FFFFFFF.
void sub_589550(EEContext& ctx);  // 0x589550
// Adds $a2 to stream n's counter +52 when it is not negative.
void sub_589650(EEContext& ctx);  // 0x589650
// Sets stream n's word +12 (4892, the end flag).
void sub_589CF0(EEContext& ctx);  // 0x589CF0
// Chunk of stream n (sub_589018): returns its end, word 1 + word 3.
void sub_589D30(EEContext& ctx);  // 0x589D30
// Records the class uuids of the memory SJ (sub_562388) and the ring SJ (sub_561970): builds one of each on the stack,
// reads its uuid (vtable +16) to 0x9A6EF0 / 0x9A6EF4 and destroys it (+12).
void sub_589E38(EEContext& ctx);  // 0x589E38
// 1 when an SJ's uuid (vtable +16) equals the memory SJ's (0x9A6EF0).
void sub_589EC8(EEContext& ctx);  // 0x589EC8
// 1 when the SFD parameter 49 is set (sub_599408).
void sub_589FD0(EEContext& ctx);  // 0x589FD0
// 1 when the SFD parameter 49 or 56 is set.
void sub_589FF0(EEContext& ctx);  // 0x589FF0
// 1 when the SFD parameter 49 or 57 is set.
void sub_58A038(EEContext& ctx);  // 0x58A038
// Finds a 32-bit code (sub_5776B0 at each byte) in a buffer of n bytes; its address, or 0 when fewer than 4 bytes
// remain.
void sub_58AA20(EEContext& ctx);  // 0x58AA20
// 1 when sub_58ABA0 matches at any of the offsets 0, 2, 1, 3 of the buffer.
void sub_58AB08(EEContext& ctx);  // 0x58AB08
// Reads an audio frame header (sub_58AE50) to the stack; when found, stores its rate and mode from the tables 0x7C9E30
// / 0x7C9E40 to the output (+40 / +44), clears +12 and keeps the header in 0x7B4558..0x7B4563.
void sub_58ADA8(EEContext& ctx);  // 0x58ADA8
// Scans a buffer (at least 4 bytes) for an audio sync word 0xFF Fx, decoding each candidate (sub_58AF20) until a valid
// header is found.
void sub_58AE50(EEContext& ctx);  // 0x58AE50
// Walks the 0x40 markers of a buffer (sub_578160), reading each marker's mode nibbles, and records what it finds in
// the output; 1 when the buffer is used up.
void sub_58AFA0(EEContext& ctx);  // 0x58AFA0
// Private-stream packet: for type 2 checks the header (sub_58B220) and skips it, then hands the payload to sub_58B2D0;
// the flag output tells the caller to skip the 18-byte header.
void sub_58B168(EEContext& ctx);  // 0x58B168
// Calls the user callback of parameter 75 with parameter 76 and the data, then copies up to 2048 bytes to the handle's
// record (+268, memcpy) with its length (+264) and sub_58B560.
void sub_58B2D0(EEContext& ctx);  // 0x58B2D0
// SFD library init: banner text pointer (0x9A8198), the work size 14,256 (0x7B4794), the per-module init chain
// (atan2l_12, sub_58BC98, coshl_12, __env_lock_12).
void sub_58BC30(EEContext& ctx);  // 0x58BC30 [SFD_Init]
// Clears and fills the SFD library work (0x7B4570: memset 137 words, memcpy 400 bytes from 0x7CA100), keeps the init
// arguments, the sub-inits (sub_58BE10, sub_5997F8, sub_588720, sub_58BD58) and clears the eight handle slots.
void sub_58BC98(EEContext& ctx);  // 0x58BC98
// Thunk: sub_562288.
void atan2l_12(EEContext& ctx);  // 0x58C088
// sub_595B30, then sub_58B108.
void coshl_12(EEContext& ctx);  // 0x58C0B8
// Does nothing.
void __env_lock_12(EEContext& ctx);  // 0x58C0F0
// Transfer module init: spins when sub_58C378 reports (never), registers the module with sub_577A38(8, 0x9A81A0),
// error -16773887; clears 0x7B4798.
void sub_58C308(EEContext& ctx);  // 0x58C308
// Returns nothing (an empty check the caller tests).
void sub_58C378(EEContext& ctx);  // 0x58C378
// Per-handle demux server: returns 0 when every output stream has ended (sub_58D578); else reads the input
// (sub_58C430), demuxes it (sub_58C490) and with status 2 (+72) runs the header steps (sub_58D800).
void r_lock_def_get_free_item_6(EEContext& ctx);  // 0x58C3A0
// Feeds the demux object (*(+8060)) with the parameters 85 / 86 (sub_5759B0).
void sub_58C430(EEContext& ctx);  // 0x58C430
// Demux loop: takes the input chunk (sub_58C588), splits it into packets (sub_58C6B0), releases what was used
// (sub_58C648) and counts the bytes (sub_58DDC0), until no data or an error.
void sub_58C490(EEContext& ctx);  // 0x58C490
// Input chunk of the demux (sub_589018 on the input stream +8068): its address, length and end; data shorter than 2048
// bytes waits unless the input ended.
void sub_58C588(EEContext& ctx);  // 0x58C588
// Releases n bytes of the input stream (sub_5890F0) and adds them to the input total +14248.
void sub_58C648(EEContext& ctx);  // 0x58C648
// Demuxes one packet of the input: the start code (sub_5776B0), the pack / system headers (sub_58D600), the packet
// search (sub_58C980 / sub_58CB28) and the hand-over to the outputs.
void sub_58C6B0(EEContext& ctx);  // 0x58C6B0
// Finds the next pack start in the input: at the expected position (sub_58CA60) or by a byte scan (sub_58CAA0);
// returns the position.
void sub_58C980(EEContext& ctx);  // 0x58C980
// Address of the demux input stream's record: $a0 + 4896 + 116 * (+8068).
void sub_58CB00(EEContext& ctx);  // 0x58CB00
// Parses one packet with the demux object (sub_5779A8, errors -16773882 / -16773874) and hands its payload to its
// output (sub_58CCA0).
void sub_58CB28(EEContext& ctx);  // 0x58CB28
// Data-referenced audio packet handler: needs parameter 6; keeps the first time stamps, the parameters 30 / 55 and the
// chunk write (sub_58D378).
void sub_58CD10(EEContext& ctx);  // 0x58CD10
// Data-referenced video packet handler: needs parameter 5; keeps the first time stamps (sub_58D058), the parameters 29
// / ... and the chunk write (sub_58D378).
void sub_58CE80(EEContext& ctx);  // 0x58CE80
// Video time base by parameter 59: mode 2 uses the stream's picture counts (sub_58DB08); other modes keep $a1.
void sub_58D058(EEContext& ctx);  // 0x58D058
// Data-referenced private-stream handler: a private packet (sub_58B168) is consumed (sub_58E158) with the rest written
// after its 18-byte header; other data goes to sub_58D180.
void sub_58D0E0(EEContext& ctx);  // 0x58D0E0
// Writes packet data to the output stream +8080 (unless it is 8): its descriptor (sub_588F90), the SJ write
// (sub_58D258), then the vtable put calls.
void sub_58D180(EEContext& ctx);  // 0x58D180
// Writes n bytes into an SJ when it has room (vtable +36): sub_58D300 for the first part and the wrap; a short second
// write counts in 0x7B4798; 1 when written.
void sub_58D258(EEContext& ctx);  // 0x58D258
// Returns nothing (data-referenced no-op handler).
void sub_58D370(EEContext& ctx);  // 0x58D370
// Writes a packet into a stream chunk (sub_589000) by mode: 1 / 2 with the time stamp checks, copies through memcpy
// (sub_575410) and the release (sub_5890D8).
void sub_58D378(EEContext& ctx);  // 0x58D378
// Marks the three output streams (+8076, +8072, +8080) ended (sub_589CF0 1) and calls sub_595208.
void sub_58D508(EEContext& ctx);  // 0x58D508
// 1 when all three output streams have ended (sub_589D10 ANDed).
void sub_58D578(EEContext& ctx);  // 0x58D578
// Pack / end code handling of the demux: the code (sub_5776B0); 0x1BA keeps the input position (sub_589530); the end
// code ends the outputs (sub_58D508 / sub_58D798) when allowed (sub_58D748).
void sub_58D600(EEContext& ctx);  // 0x58D600
// 1 when the code is the end code (0x80000) and neither parameter 49 (sub_589FD0) nor 49 / 56 (sub_589FF0) is set.
void sub_58D748(EEContext& ctx);  // 0x58D748
// When the input stream ended (sub_589D10), ends the outputs (sub_58D508 with the demux's word +60) and reports 1
// through the optional output.
void sub_58D798(EEContext& ctx);  // 0x58D798
// The status-2 steps of the demux: picture counts (sub_58DB08), the start check (sub_58D858), the header (sub_58DBB8),
// the end check (sub_58DA10), the time (sub_58DC50) and sub_58DD00.
void sub_58D800(EEContext& ctx);  // 0x58D800
// Unless an output already reports input end (sub_58D8E0), when the input stream has its end flag and enough data is
// buffered (sub_58D9B0), marks the outputs (sub_58D950 1).
void sub_58D858(EEContext& ctx);  // 0x58D858
// 1 when any of the three output streams has its input end flag (sub_589CD0 ORed).
void sub_58D8E0(EEContext& ctx);  // 0x58D8E0
// Sets the input end flag of the three output streams to $a1 (sub_589CB0).
void sub_58D950(EEContext& ctx);  // 0x58D950
// Enough buffered: the target (+8, else the stream's +12, else the parameter +2660) capped by +2660, against stream
// 0's available amount (sub_589550).
void sub_58D9B0(EEContext& ctx);  // 0x58D9B0
// End handling of the prepare step: with parameters 79 / 80, a drained stream 2 (sub_589550) and no demux data, sets
// parameter 6 off (sub_599240) when sub_59BC88(6); then the video side.
void sub_58DA10(EEContext& ctx);  // 0x58DA10
// Largest values over the demux object's streams (sub_577860 for each): the two maxima into the outputs.
void sub_58DB08(EEContext& ctx);  // 0x58DB08
// Copies the demux object's header values (sub_5777F8, sub_577860 1) into the handle's header record (+2316) where
// they are known (> 0 / not -1).
void sub_58DBB8(EEContext& ctx);  // 0x58DBB8
// Time of the header object (sub_58E200): when the demux has a time (+24 of its object), the 64-bit offset (+3720) and
// the start-time words.
void sub_58DC50(EEContext& ctx);  // 0x58DC50
// Does nothing.
void sub_58DD00(EEContext& ctx);  // 0x58DD00
// Copies up to 176 bytes of the packet's private data (sub_577910) into the header object's record (sub_58E200 + 48)
// when it is free.
void sub_58DD08(EEContext& ctx);  // 0x58DD08
// When the handle has an input SJ (+4900), adds its chunk sizes (sub_589D80 / sub_589F38) to the 64-bit totals +2440 /
// +2448 / +2456.
void sub_58DDC0(EEContext& ctx);  // 0x58DDC0
// Data-referenced demux create: the demux record at +8600 (+8060 points to it), cleared (sub_58DF08); the demux object
// (sub_577DD8, error -16773880) with the packet callback sub_58DF90 (sub_577C68, error -16773879 after the destroy).
void sub_58DE40(EEContext& ctx);  // 0x58DE40
// Clears a demux record: the time words to INT_MAX / INT64_MAX, the stamp words to -1, 67 output slots cleared.
void sub_58DF08(EEContext& ctx);  // 0x58DF08
// Data-referenced demux destroy: sub_58DFF8 on the demux object; error -16773878.
void sub_58DFA8(EEContext& ctx);  // 0x58DFA8
// Thunk: sub_577F78.
void sub_58DFF8(EEContext& ctx);  // 0x58DFF8
// Does nothing.
void sub_58E158(EEContext& ctx);  // 0x58E158
// The header object's record (+14000, record at +2208) when there is one and sub_58E250 is not positive; else 0.
void sub_58E200(EEContext& ctx);  // 0x58E200
// Keeps a 32-byte configuration at 0x9ACAF0 (clearing 0x9ACB10 and its word +16), the two buffer addresses of $a1
// rounded up to 64 bytes at 0x9ACB18, and the first n (configuration word +28) of $a2 rounded up to 64 at 0x9ACB20,
// zeros after.
void sub_58E310(EEContext& ctx);  // 0x58E310
// Sets a video decoder option: optional handle check (sub_58C060, error -16776831), decoder of the handle (*(+8128))
// or 0, value $a2 (none for option 5) through sub_57B648; error -16773358.
void sub_58E530(EEContext& ctx);  // 0x58E530
// Sets up to 16 words of the video decoder's table (sub_57B648 per word) when the handle has a decoder.
void sub_58E5E8(EEContext& ctx);  // 0x58E5E8
// Sets n option values from an array on the video decoder (sub_57B648 per value) when there is one.
void sub_58E670(EEContext& ctx);  // 0x58E670
// Video module init: sub_594B88, spins when sub_58EA38 reports (never), registers with sub_57AFA0(8, 0x9A89B0) (error
// -16773357 or -16773375).
void sub_58E958(EEContext& ctx);  // 0x58E958
// Returns nothing (an empty check the caller tests).
void sub_58EA38(EEContext& ctx);  // 0x58EA38
// Per-handle video decode server: with parameter 5, unless the output ended (sub_58EC20): the options (sub_58EB10),
// the header step (sub_58EB80 with status 2, +72), the decode loop (sub_58EFD8), the end check (sub_58EC38) and
// sub_58EEC0.
void r_lock_def_get_free_item_7(EEContext& ctx);  // 0x58EA60
// With parameter 28: the video decoder option 5 from sub_58BBE8's sign (sub_58E530).
void sub_58EB10(EEContext& ctx);  // 0x58EB10
// Status 2: with the parameters 93 / 94 and a sequence-header record of 192 (+120 of the decoder), reads the header
// (sub_5796D0) into the handle.
void sub_58EB80(EEContext& ctx);  // 0x58EB80
// The video output stream's end flag (sub_589D10 on +8140).
void sub_58EC20(EEContext& ctx);  // 0x58EC20
// When the input stream ended (sub_589CD0 +8136) and decoding is done (sub_58ECE8), sets the output's input end
// (sub_589CB0 1) and the end time.
void sub_58EC38(EEContext& ctx);  // 0x58EC38
// Decoding done: sub_593958, or the frame check (sub_58ED48) and the buffer check (R_LOCK_DEF_w_lock_7).
void sub_58ECE8(EEContext& ctx);  // 0x58ECE8
// Enough pictures decoded: the target (+2664, else +44, capped by +44) against sub_593978 (plus +2408 in mode 2).
void sub_58ED48(EEContext& ctx);  // 0x58ED48
// Buffer check of the video input: input end (sub_58FF58), decoder state (+120 / +244), the stream amounts (sub_589510
// / sub_589550).
void R_LOCK_DEF_w_lock_7(EEContext& ctx);  // 0x58EDB0
// Pictures done (sub_593978, sub_58EF48): sets the end state (sub_58EFB8 1) and, without +2384, parameter 5 off
// (sub_599240).
void sub_58EEC0(EEContext& ctx);  // 0x58EEC0
// Decode finished: sub_593958, and in mode 1 the picture counter +2412 below +2408.
void sub_58EF48(EEContext& ctx);  // 0x58EF48
// Decode loop: the next picture (sub_58F058) and its decode (sub_58F808) until an error or nothing more, then
// sub_592958.
void sub_58EFD8(EEContext& ctx);  // 0x58EFD8
// Finds the next picture in the video input chunk (sub_589018): start codes (sub_58F548 206 etc.), the picture header
// (sub_58F298), the GOP / sequence codes and the position fix-ups (sub_589438 / sub_5894A8 / sub_58F458 / sub_58F4C0).
void sub_58F058(EEContext& ctx);  // 0x58F058
// Moves the video input position to a found code across the two parts of the chunk.
void sub_58F298(EEContext& ctx);  // 0x58F298
// Offset of an address inside the two-part chunk {addr0, len0, addr1, len1}: from the first part, or len0 + the offset
// in the second; 0 when outside.
void sub_58F458(EEContext& ctx);  // 0x58F458
// The video input's free amount (sub_589510 - sub_589D30) against the minimum (+40): error -16773348 when below.
void sub_58F4C0(EEContext& ctx);  // 0x58F4C0
// Searches a start code across the two-part chunk (sub_578160 on each part and on the 3-byte seam); its address and
// the part through *$a2.
void sub_58F548(EEContext& ctx);  // 0x58F548
// Searches backwards for a start code across the two-part chunk (sub_578060).
void sub_58F6A0(EEContext& ctx);  // 0x58F6A0
// Decodes one picture: skips when sub_595718; with the input ended (sub_58FF58) ends (sub_593948); else the picture
// header, the decode calls (sub_58FB28 / sub_58FBE0 / sub_590008 / ...) and the input release.
void sub_58F808(EEContext& ctx);  // 0x58F808
// The video input chunk (sub_589018 on +8136): its first two words into the output, zeros on an error.
void sub_58FAD8(EEContext& ctx);  // 0x58FAD8
// Skips start-code words of an SJ: reads 4 bytes (vtable +24); while the code is 0x80 (sub_577FC8) puts them back used
// (+32) and counts them (sub_58FEC8); otherwise returns the chunk (+28).
void sub_58FE08(EEContext& ctx);  // 0x58FE08
// Counts n consumed bytes: the video input stream's counter (sub_589650 on +8136) and the 64-bit total +2472.
void sub_58FEC8(EEContext& ctx);  // 0x58FEC8
// Continue check of the decode loop: 1 for the code 128, or for a small result (< 5) unless the input ended
// (sub_58FF58); else 0.
void sub_58FF10(EEContext& ctx);  // 0x58FF10
// The video input stream's end flag (sub_589D10 on +8136).
void sub_58FF58(EEContext& ctx);  // 0x58FF58
// Maps a decoder result to an SFD error (sub_58BE40): -2 is fine with data left, 0 is fine, -1 / -3 and others report.
void sub_58FF70(EEContext& ctx);  // 0x58FF70

}  // namespace p3fes::game
