// Phase 5 slice cri1: the CRI middleware's pure parts (game/src/cri/cri1_*.cpp, tests/game/test_cri1.cpp) -- what only
// computes or moves memory in the ADX / Sofdec libraries linked into the ELF:
//   * ADXB: the ADX header parsers (main header, version, cutoff, histories, loop record, AINF), the AHX / SPSD / WAV
//     tests, the prediction coefficients, the two ADPCM block decoders and the 16 decoder objects that run them;
//   * the stream joints (SJ): SJMEM (a fixed memory block), SJRBF (a ring buffer) and SJUNI (chunk lists over a node
//     pool), each a handle pool, a 12-entry vtable and its locked wrappers;
//   * the SVM lock / unlock (through the callbacks the ADX setup installs) and error-callback helpers;
//   * the cvFs pieces that touch no device: init, upper-casing, the DEV:file split, the default-device copy, the
//     error helpers (the device registration / lookup calls newlib strncmp, which test_models stands in: left).
// Every function is a p3fes_handgen body on the register ABI (arguments in $a0..$t3, more on the caller's stack from
// $sp + 0 in 8-byte slots, the result in $v0) with its recompiled entry point fn_<name>_<addr8> as the shim. Names are
// symbols/functions.json's (ADR-0009); each declaration says the function's role, with a proposed name in [brackets]
// (our own, from the instructions; not imported). Worked from the binary only (the CRI SDK is proprietary and was not
// consulted); the ADX block format is the public one (18-byte frames: a big-endian scale stored minus one, then 32
// signed 4-bit samples, high nibble first; 4.12 fixed-point prediction from the last two samples).
//
// Not taken (driver level, for the native-port phase): docs/INTEGRATION_LOG.md, section "cri1".
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace cri1 {

// --- ADX file header (big-endian; public format) --------------------------------------------------------------------
namespace adx {
constexpr u16 kMagic = 0x8000;      // +0: u16 magic; +2: u16 header size (data at header size + 4, "(c)CRI" just before)
constexpr s32 kHeaderSize = 0x02;   // u16
constexpr s32 kEncoding = 0x04;     // u8: 3 = ADX ADPCM (every file of the disc)
constexpr s32 kBlockSize = 0x05;    // u8: 18
constexpr s32 kBits = 0x06;         // u8: 4
constexpr s32 kChannels = 0x07;     // u8: 1 / 2
constexpr s32 kRate = 0x08;         // u32
constexpr s32 kSamples = 0x0C;      // u32: samples per channel
constexpr s32 kCutoff = 0x10;       // u16: the high-pass cutoff the coefficients come from (500 on the disc)
constexpr s32 kVersion = 0x12;      // u8: 3 / 4
constexpr s32 kFlags = 0x13;        // u8: 0 (no encryption on the disc)
constexpr s32 kHistory = 0x18;      // version 4: 2 x {hist1, hist2} s16 (sub_539CD8)
constexpr s32 kLoopV3 = 0x14;       // the loop record: version 3 at +20, version 4 at +32 (sub_539ED8)
constexpr s32 kLoopV4 = 0x20;       //   {u16 alignment samples, u16 loop count, u32 loop flag (its low half is read), u32 start sample, u32 start byte,
                                    //    u32 end sample, u32 end byte}
constexpr u32 kAinf = 0x41494E46u;  // "AINF": the extension after the loop record (sub_53A138)
constexpr u16 kAhxMagic = 0x8001;   // AHX (MPEG-like) streams: the same header-size field
constexpr s32 kFrame = 18;          // ADX frame: u16 scale (stored minus one; bit 15 set = end block) + 16 bytes of nibbles
constexpr s32 kFrameSamples = 32;
}  // namespace adx

// --- the ADPCM decoder objects (16 x 60 bytes at 0x793B80; created by sub_54CBC8) -----------------------------------
namespace adxpd {
constexpr u32 kPool = 0x793B80u;   // 16 objects
constexpr u32 kCount = 16;
constexpr u32 kSize = 60;
constexpr u32 kErrorFlag = 0x793B78u;  // set by sub_54CE80 when a stereo job decoded an odd number of blocks
constexpr u32 kImplFlag = 0x784948u;   // sub_53AD00: non-zero = downmix, both outputs (L + R) * 7 / 10
constexpr u32 kNibbleTable = 0x7C1A40u;  // s32[16]: the signed value of a low nibble (0..7, -8..-1)
constexpr s32 kUsed = 0x00;      // 1 while taken
constexpr s32 kId = 0x04;        // slot index
constexpr s32 kMode = 0x08;      // sub_54CD78
constexpr s32 kState = 0x0C;     // 0 idle, 1 started, 2 decoding, 3 done
constexpr s32 kDecoded = 0x10;   // blocks the last job decoded (the decoder's result)
constexpr s32 kKind = 0x14;      // 1 mono (sub_53A410), 2 stereo (sub_53AD00)
constexpr s32 kSrc = 0x18;       // ADX blocks
constexpr s32 kBlocks = 0x1C;    // blocks to decode (stereo: both channels' blocks)
constexpr s32 kDstL = 0x20;      // s16 PCM out (left / mono)
constexpr s32 kDstR = 0x24;      // s16 PCM out (right)
constexpr s32 kHistL = 0x28;     // s16 hist1, hist2 (left / mono)
constexpr s32 kHistR = 0x2C;     // s16 hist1, hist2 (right)
constexpr s32 kCoef1 = 0x30;     // s16, 4.12 fixed point
constexpr s32 kCoef2 = 0x32;     // s16
constexpr s32 kKey = 0x34;       // u16 running key (0 on the disc: the XOR is the identity)
constexpr s32 kKeyMul = 0x36;    // s16
constexpr s32 kKeyAdd = 0x38;    // s16
}  // namespace adxpd

// --- the stream joints ---------------------------------------------------------------------------------------------
// Every SJ handle starts with {vtable, used, uuid}; the vtables (12 words: three unused, then destroy, get uuid,
// reset, get chunk, unget chunk, put chunk, get num data, is get chunk, entry error function) live at 0x7AC780
// (SJMEM), 0x7ACC68 (SJRBF) and 0x7B0CA0 (SJUNI). A chunk is {u32 data, s32 size} (8 bytes). Lines: 0 = free space,
// 1 = data (SJUNI: four lines). A bad line calls the handle's error callback (fn, obj) with -3.
namespace sj {
constexpr s32 kVtbl = 0x00;
constexpr s32 kUsed = 0x04;   // SJUNI: u8
constexpr s32 kUuid = 0x08;   // pointer to the type's 16-byte uuid (0x7C67F0 / 0x7C6950 / 0x7C6AA8)
constexpr s32 kChunkData = 0x00;
constexpr s32 kChunkSize = 0x04;
}  // namespace sj
namespace sjmem {  // 32 x 36 bytes at 0x7AC7B8
constexpr u32 kPool = 0x7AC7B8u;
constexpr u32 kCount = 32;
constexpr u32 kSize = 36;
constexpr u32 kVtable = 0x7AC780u;
constexpr s32 kLeft = 0x0C;     // data bytes not yet got
constexpr s32 kOffset = 0x10;   // read offset into the buffer
constexpr s32 kBuf = 0x14;
constexpr s32 kBufSize = 0x18;
constexpr s32 kErrFn = 0x1C;
constexpr s32 kErrObj = 0x20;
}  // namespace sjmem
namespace sjrbf {  // 256 x 64 bytes at 0x7ACCA0
constexpr u32 kPool = 0x7ACCA0u;
constexpr u32 kCount = 256;
constexpr u32 kSize = 64;
constexpr u32 kVtable = 0x7ACC68u;
constexpr s32 kData = 0x0C;      // line 1: bytes of data
constexpr s32 kFree = 0x10;      // line 0: bytes free
constexpr s32 kPos0 = 0x14;      // line 0 (write) position
constexpr s32 kPos1 = 0x18;      // line 1 (read) position
constexpr s32 kBuf = 0x1C;
constexpr s32 kBufSize = 0x20;
constexpr s32 kXtrSize = 0x24;   // the extra area after the buffer a chunk may run into (mirrored on put)
constexpr s32 kGot0 = 0x28;      // running totals: bytes got from line 0 / put to line 0 ... (diagnostics)
constexpr s32 kPut0 = 0x2C;
constexpr s32 kGot1 = 0x30;
constexpr s32 kPut1 = 0x34;
constexpr s32 kErrFn = 0x38;
constexpr s32 kErrObj = 0x3C;
}  // namespace sjrbf
namespace sjuni {  // 64 x 48 bytes at 0x7B0CD8
constexpr u32 kPool = 0x7B0CD8u;
constexpr u32 kCount = 64;
constexpr u32 kSize = 48;
constexpr u32 kVtable = 0x7B0CA0u;
constexpr s32 kMerge = 0x05;     // u8: 1 = contiguous chunks are merged / split
constexpr s32 kWork = 0x0C;      // node work area: 16-byte nodes {next, unused, data, size}
constexpr s32 kNodes = 0x10;     // node count (work size / 16)
constexpr s32 kFreeList = 0x14;  // first free node
constexpr s32 kLines = 0x18;     // 4 line heads
constexpr s32 kErrFn = 0x28;
constexpr s32 kErrObj = 0x2C;
}  // namespace sjuni

// --- SVM -------------------------------------------------------------------------------------------------------------
namespace svm {
constexpr u32 kLockFn = 0x99A0A0u;    // lock callback / its object 0x99A0A4
constexpr u32 kUnlockFn = 0x99A0A8u;  // unlock callback / its object 0x99A0AC
constexpr u32 kErrFn = 0x99A0B0u;     // error callback / its object 0x99A0B4
constexpr u32 kLockDepth = 0x7B2630u;
constexpr u32 kLockType = 0x7B2634u;  // the outermost lock's type
constexpr u32 kErrText = 0x7B2678u;   // 128-byte error text
}  // namespace svm

// --- cvFs -----------------------------------------------------------------------------------------------------------
namespace cvfs {
constexpr u32 kDevices = 0x997658u;   // 32 x 16 bytes: {u32 interface (vtable), char name[12]} (names at 0x99765C)
constexpr u32 kDeviceCount = 32;
constexpr u32 kDeviceSize = 16;
constexpr u32 kHandles = 0x997518u;   // cvFsHandleTable: 40 x {interface, device handle}
constexpr u32 kDefDev = 0x997858u;    // the default device name (9 bytes)
constexpr u32 kInitCount = 0x7A08ACu;
constexpr u32 kErrFn = 0x7A08A4u;     // error callback / its object 0x7A08A8
constexpr s32 kIfSetErrFn = 0x04;     // device interface entries the slice calls: set the error callback
constexpr s32 kIfOption = 0x60;       //   and the option request (100: does the device want its name in paths)
}  // namespace cvfs

}  // namespace cri1

// --- ADXB: header parsers, coefficients, decoders ---------------------------------------------------------------------
// is the buffer an SPSD header ("SPSD" at +0)? 1 / 0. [spsd_IsHeader]
void sub_538EF0(EEContext& ctx);  // 0x538EF0
// parse a RIFF / WAVE header: the "fmt " chunk (4-byte aligned; format tag below 2, channels, rate, block align,
//   bits) and the "data" chunk (data offset, sample count = size / block align); 16-bit, 8-bit and 4-bit kinds (the
//   tag pointers at 0x784930 / 0x784934). [wav_DecodeHeader]
void sub_538F18(EEContext& ctx);  // 0x538F18
// fill a decoder record (+12 ... +156) from a WAV header (sub_538F18) and reset its counters; returns the data
//   offset. [wav_SetupDecoder]
void sub_539148(EEContext& ctx);  // 0x539148
// is the buffer a RIFF / WAVE header ("RIFF" at +0, "WAVE" at +8)? 1 / 0. [wav_IsHeader]
void sub_5396F8(EEContext& ctx);  // 0x5396F8
// ADXB lock counter: +1 (the first lock clears 0x784938). [adxb_Lock]
void sub_5397B8(EEContext& ctx);  // 0x5397B8
// ADXB lock counter: -1 (the last unlock clears 0x784938). [adxb_Unlock]
void sub_5397E8(EEContext& ctx);  // 0x5397E8
// the empty lock stub of the ADX libraries (100 callers; `jr $ra`). [adx_EnterCs (stub)]
void sub_539848(EEContext& ctx);  // 0x539848
// the empty unlock stub of the ADX libraries (100 callers; `jr $ra`). [adx_LeaveCs (stub)]
void sub_539850(EEContext& ctx);  // 0x539850
// the ADX prediction coefficients from a high-pass cutoff and a sample rate (floats: sqrtf, cosf): a = sqrt2 - cos(2
//   pi cutoff / rate), b = sqrt2 - 1, c = (a - sqrt((a + b)(a - b))) / b; coef1 = (s16)(2c * 4096), coef2 =
//   (s16)(-c^2 * 4096). [adx_CalcCoefficients]
void sub_539858(EEContext& ctx);  // 0x539858
// find the first big-endian 0x0080 halfword (an AHX frame sync) in a buffer, 2-byte steps: offset or -1.
//   [ahx_FindSync]
void sub_5399B8(EEContext& ctx);  // 0x5399B8
// is the buffer an ADX file start? 0x8000 magic, at least 0x8000 bytes, "(c)CRI" just before the data offset; also
//   returns the data offset (header size + 4). [adx_IsHeader]
void sub_539A38(EEContext& ctx);  // 0x539A38
// decode an ADX main header: data offset, encoding, block size, bits per sample, channels, sample rate, total
//   samples, samples per block (8 * block size - 16) / bits). [adx_DecodeHeader]
void sub_539AE0(EEContext& ctx);  // 0x539AE0
// the high-pass cutoff of an ADX header (u16 BE at +16; header at least 18 bytes). [adx_GetCutoff]
void sub_539BE0(EEContext& ctx);  // 0x539BE0
// the version and flags bytes of an ADX header (+18 / +19). [adx_GetVersion]
void sub_539C60(EEContext& ctx);  // 0x539C60
// the two channels' initial histories of a version-4 ADX header (+24 ... +30; zeros before version 4).
//   [adx_GetHistory]
void sub_539CD8(EEContext& ctx);  // 0x539CD8
// the loop of an ADX header: the loop flag (0 unless the record says 1) and the loop start / end samples less the
//   alignment samples modulo 2048. [adx_GetLoopInfo]
void sub_539E10(EEContext& ctx);  // 0x539E10
// decode an ADX loop record (version 3 at +20, version 4 at +32): alignment samples, loop flag, start / end sample,
//   start / end byte. [adx_DecodeLoop]
void sub_539ED8(EEContext& ctx);  // 0x539ED8
// decode the "AINF" extension of an ADX header (after the loop record): size, 16-byte id, volume, pan pair.
//   [adx_DecodeAinf]
void sub_53A138(EEContext& ctx);  // 0x53A138
// is the buffer an AHX header (0x8001 magic)? returns the data offset (header size + 4). [ahx_DecodeHeader]
void _get_peer_or_sock_name_3(EEContext& ctx);  // 0x53A358
// (position + header + block size + 57 (a0 != 0) or 33) rounded down to whole blocks, less the header.
void sub_53A3B8(EEContext& ctx);  // 0x53A3B8
// decode N mono ADX blocks (18 bytes: BE scale, 32 nibbles) to 16-bit PCM; the scale is XORed with the running key
//   (key = (key * mult + add) & 0x7FFF per block); stops before an 0x8000 end block. [adxpd_DecodeMono]
void sub_53A410(EEContext& ctx);  // 0x53A410
// decode N interleaved stereo ADX blocks (left, right, ...) to two PCM buffers; with 0x784948 non-zero both outputs
//   get the downmix (L + R) * 7 / 10 (histories stay per channel); same key rule as the mono decoder; an end block
//   returns early without writing the histories back (both decoders). [adxpd_DecodeStereo]
void sub_53AD00(EEContext& ctx);  // 0x53AD00

// --- ADXB: the decoder objects (adxpd) --------------------------------------------------------------------------------
// clear the 16 decoder objects (init). [ADXPD_Init]
void sub_54CB78(EEContext& ctx);  // 0x54CB78
// clear the 16 decoder objects (finish). [ADXPD_Finish]
void sub_54CBA0(EEContext& ctx);  // 0x54CBA0
// take a free decoder object: used = 1, id, state 0, coefficients for 500 Hz / 44100 Hz, histories 0. [ADXPD_Create]
void sub_54CBC8(EEContext& ctx);  // 0x54CBC8
// set a decoder object's coefficients from cutoff and rate. [ADXPD_SetCoef]
void sub_54CC98(EEContext& ctx);  // 0x54CC98
// set a decoder object's two histories (+40 ... +46). [ADXPD_SetDly]
void sub_54CCC0(EEContext& ctx);  // 0x54CCC0
// get a decoder object's two histories. [ADXPD_GetDly]
void sub_54CCE8(EEContext& ctx);  // 0x54CCE8
// set a decoder object's key (+52 start, +54 multiplier, +56 increment). [ADXPD_SetExtPrm]
void sub_54CD10(EEContext& ctx);  // 0x54CD10
// release a decoder object (zero its 60 bytes). [ADXPD_Destroy]
void sub_54CD40(EEContext& ctx);  // 0x54CD40
// set a decoder object's word +8. [ADXPD_SetMode]
void sub_54CD78(EEContext& ctx);  // 0x54CD78
// a decoder object's state (+12: 0 idle, 1 started, 2 decoding, 3 done). [ADXPD_GetStat]
void sub_54CD80(EEContext& ctx);  // 0x54CD80
// start a mono job (kind 1): source, block count, output; refused (0) unless idle. [ADXPD_EntryMono]
void sub_54CD88(EEContext& ctx);  // 0x54CD88
// start a stereo job (kind 2): source, block count, left / right outputs; refused unless idle. [ADXPD_EntrySte]
void sub_54CDB8(EEContext& ctx);  // 0x54CDB8
// start a mono job (kind 1) with a second output word (+36); refused unless idle. [ADXPD_EntryPl2]
void sub_54CDE8(EEContext& ctx);  // 0x54CDE8
// stop a decoder object: state 0, histories cleared. [ADXPD_Stop]
void sub_54CE38(EEContext& ctx);  // 0x54CE38
// a decoder object's state; a finished job (3) goes back to idle (0). [ADXPD_Reset]
void sub_54CE60(EEContext& ctx);  // 0x54CE60
// the blocks the last job decoded (+16). [ADXPD_GetNumBlk]
void sub_54CE78(EEContext& ctx);  // 0x54CE78
// flag an odd stereo block count (0x793B78 = 1). [adxpd_SetError]
void sub_54CE80(EEContext& ctx);  // 0x54CE80
// run one decoder object: started -> decoding -> the mono or stereo decoder -> done (an odd stereo result sets the
//   error flag). [ADXPD_ExecHndl]
void sub_54CE90(EEContext& ctx);  // 0x54CE90
// run every used decoder object. [ADXPD_ExecServer]
void sub_54CF88(EEContext& ctx);  // 0x54CF88

// --- SJMEM ------------------------------------------------------------------------------------------------------------
// SJ library init counter (the first init clears 0x7AC770). [sj_Init]
void sub_561758(EEContext& ctx);  // 0x561758
// SJ lock: SVM lock of type 1. [sj_Lock]
void sub_5617C0(EEContext& ctx);  // 0x5617C0
// SJ unlock: SVM unlock of type 1. [sj_Unlock]
void sub_5617D8(EEContext& ctx);  // 0x5617D8
// report an SJ error text through the SVM error callback. [sj_Error]
void sub_5617F0(EEContext& ctx);  // 0x5617F0
// the SJMEM handles' default error callback ("SJMEM Error"). [sjmem_DefaultErrFn]
void sub_561808(EEContext& ctx);  // 0x561808
// SJMEM error: code + message joined in a 64-byte stack buffer, then reported. [sjmem_Error]
void sub_561828(EEContext& ctx);  // 0x561828
// SJMEM init (locked): the SJ counter and the handle pool. [SJMEM_Init]
void sub_561870(EEContext& ctx);  // 0x561870
// SJMEM pool init: the first call clears the 32 handles. [sjmem_InitPool]
void sub_5618A0(EEContext& ctx);  // 0x5618A0
// SJMEM finish (locked). [SJMEM_Finish]
void sub_5618F0(EEContext& ctx);  // 0x5618F0
// SJMEM pool finish: the last call clears the 32 handles. [sjmem_FinishPool]
void sub_561920(EEContext& ctx);  // 0x561920
// create an SJMEM handle (locked): buffer, size. [SJMEM_Create]
void sub_561970(EEContext& ctx);  // 0x561970
// take a free SJMEM handle, fill vtable / uuid / buffer / size / error callback, reset it. [sjmem_Create]
void sub_5619B8(EEContext& ctx);  // 0x5619B8
// destroy an SJMEM handle (locked). [SJMEM_Destroy]
void sub_561A80(EEContext& ctx);  // 0x561A80
// destroy: zero the 36 bytes. [sjmem_Destroy]
void sub_561AB0(EEContext& ctx);  // 0x561AB0
// the uuid of an SJMEM handle (locked). [SJMEM_GetUuid]
void sub_561B38(EEContext& ctx);  // 0x561B38
// the uuid pointer (+8). [sjmem_GetUuid]
void sub_561B70(EEContext& ctx);  // 0x561B70
// set an SJMEM handle's error callback (locked). [SJMEM_EntryErrFunc]
void sub_561BC8(EEContext& ctx);  // 0x561BC8
// store the error callback and its object (+28 / +32). [sjmem_EntryErrFunc]
void sub_561C18(EEContext& ctx);  // 0x561C18
// reset an SJMEM handle (locked). [SJMEM_Reset]
void sub_561C78(EEContext& ctx);  // 0x561C78
// reset: data = size, read offset = 0. [sjmem_Reset]
void sub_561CA8(EEContext& ctx);  // 0x561CA8
// bytes on a line: line 1 = the data left, line 0 = none; another line calls the error callback (-3).
//   [SJMEM_GetNumData]
void sub_561D10(EEContext& ctx);  // 0x561D10
// get a chunk (locked). [SJMEM_GetChunk]
void sub_561D58(EEContext& ctx);  // 0x561D58
// get a chunk: line 1 gives min(n, data left) bytes at buffer + offset and advances; line 0 gives an empty chunk.
//   [sjmem_GetChunk]
void sub_561DB8(EEContext& ctx);  // 0x561DB8
// put a chunk (locked). [SJMEM_PutChunk]
void sub_561E98(EEContext& ctx);  // 0x561E98
// put a chunk: lines 0 / 1 accept and drop it; another line clears it and calls the error callback. [sjmem_PutChunk]
void sub_561EE8(EEContext& ctx);  // 0x561EE8
// unget a chunk (locked). [SJMEM_UngetChunk]
void sub_561F88(EEContext& ctx);  // 0x561F88
// unget a chunk on line 1: step the read offset back (an out-of-order chunk calls the error callback).
//   [sjmem_UngetChunk]
void sub_561FD8(EEContext& ctx);  // 0x561FD8
// is a chunk of n bytes available (locked). [SJMEM_IsGetChunk]
void sub_5620D8(EEContext& ctx);  // 0x5620D8
// is a chunk of n bytes available: the size that can be got and whether it is n. [sjmem_IsGetChunk]
void sub_562140(EEContext& ctx);  // 0x562140

// --- SJRBF (and five stream-record accessors 0x562DE0..0x562E10) ------------------------------------------------------
// an SJRBF handle's line-0 position (+20). [SJRBF_GetWritePos]
void _ZNKSt15basic_streambufIcSt11char_traitsIcEE5ebackEv_3(EEContext& ctx);  // 0x562210
// an SJRBF handle's line-1 position (+24). [SJRBF_GetReadPos]
void width__CQ24_STL8ios_base_0(EEContext& ctx);  // 0x562218
// the SJRBF handles' default error callback ("SJRBF Error"). [sjrbf_DefaultErrFn]
void sub_562220(EEContext& ctx);  // 0x562220
// SJRBF error: code + message joined, then reported. [sjrbf_Error]
void sub_562240(EEContext& ctx);  // 0x562240
// SJRBF init (locked). [SJRBF_Init]
void sub_562288(EEContext& ctx);  // 0x562288
// SJRBF pool init: the first call clears the 256 handles. [sjrbf_InitPool]
void sub_5622B8(EEContext& ctx);  // 0x5622B8
// SJRBF finish (locked). [SJRBF_Finish]
void sub_562308(EEContext& ctx);  // 0x562308
// SJRBF pool finish: the last call clears the 256 handles. [sjrbf_FinishPool]
void sub_562338(EEContext& ctx);  // 0x562338
// create an SJRBF handle (locked): buffer, size, extra (mirror) size. [SJRBF_Create]
void sub_562388(EEContext& ctx);  // 0x562388
// take a free SJRBF handle, fill it and reset it. [sjrbf_Create]
void sub_5623E0(EEContext& ctx);  // 0x5623E0
// destroy an SJRBF handle (locked). [SJRBF_Destroy]
void sub_5624B0(EEContext& ctx);  // 0x5624B0
// destroy: zero the 64 bytes. [sjrbf_Destroy]
void sub_5624E0(EEContext& ctx);  // 0x5624E0
// the uuid pointer (+8). [SJRBF_GetUuid]
void sub_562568(EEContext& ctx);  // 0x562568
// store the error callback and its object (+56 / +60). [SJRBF_EntryErrFunc]
void sub_562570(EEContext& ctx);  // 0x562570
// reset an SJRBF handle (locked). [SJRBF_Reset]
void sub_562580(EEContext& ctx);  // 0x562580
// reset: free = size, data = 0, both positions and the three counters 0. [sjrbf_Reset]
void sub_5625B0(EEContext& ctx);  // 0x5625B0
// bytes on a line: line 0 = free space, line 1 = data; another line calls the error callback. [SJRBF_GetNumData]
void sub_562630(EEContext& ctx);  // 0x562630
// get a chunk (locked). [SJRBF_GetChunk]
void sub_562680(EEContext& ctx);  // 0x562680
// get a chunk from line 0 (free) or 1 (data): min(n, line bytes, bytes to the end + extra) at buffer + position; the
//   position advances modulo the size. [sjrbf_GetChunk]
void sub_5626E0(EEContext& ctx);  // 0x5626E0
// put a chunk (locked). [SJRBF_PutChunk]
void sub_562880(EEContext& ctx);  // 0x562880
// put a chunk on line 0 (free += n) or 1 (data += n); a chunk on line 1 that ran into the extra area or the buffer
//   start is mirrored (memcpy) to the other side. [sjrbf_PutChunk]
void sub_5628D0(EEContext& ctx);  // 0x5628D0
// unget a chunk (locked). [SJRBF_UngetChunk]
void sub_562A50(EEContext& ctx);  // 0x562A50
// unget a chunk: the line's position steps back by n (modulo the size) when the chunk was the last one got.
//   [sjrbf_UngetChunk]
void sub_562AA0(EEContext& ctx);  // 0x562AA0
// is a chunk of n bytes available (locked). [SJRBF_IsGetChunk]
void sub_562C80(EEContext& ctx);  // 0x562C80
// is a chunk of n bytes available: min(line bytes, bytes to the end + extra, n) and whether it is n.
//   [sjrbf_IsGetChunk]
void sub_562CE8(EEContext& ctx);  // 0x562CE8
// word +28 of a stream record (callers 0x541E28 / 0x542438).
void sub_562DE0(EEContext& ctx);  // 0x562DE0
// word +32 of a stream record.
void sub_562DE8(EEContext& ctx);  // 0x562DE8
// word +36 of a stream record.
void sub_562DF0(EEContext& ctx);  // 0x562DF0
// store a word of the 2-column table at +40 of a stream record ([2 * row + column]).
void sub_562DF8(EEContext& ctx);  // 0x562DF8
// read a word of the 2-column table at +40 of a stream record.
void sub_562E10(EEContext& ctx);  // 0x562E10

// --- SJUNI and the chunk split ----------------------------------------------------------------------------------------
// the SJUNI handles' default error callback ("SJUNI Error"). [sjuni_DefaultErrFn]
void sub_562E28(EEContext& ctx);  // 0x562E28
// SJUNI error: code + message joined, then reported. [sjuni_Error]
void sub_562E48(EEContext& ctx);  // 0x562E48
// SJUNI init (locked). [SJUNI_Init]
void sub_562E90(EEContext& ctx);  // 0x562E90
// SJUNI pool init: the first call clears the 64 handles. [sjuni_InitPool]
void sub_562EC0(EEContext& ctx);  // 0x562EC0
// SJUNI finish (locked). [SJUNI_Finish]
void sub_562F10(EEContext& ctx);  // 0x562F10
// SJUNI pool finish: the last call clears the 64 handles. [sjuni_FinishPool]
void sub_562F40(EEContext& ctx);  // 0x562F40
// create an SJUNI handle (locked): merge mode, node work area, work size. [SJUNI_Create]
void sub_562F90(EEContext& ctx);  // 0x562F90
// take a free SJUNI handle: mode, work area, node count = size / 16, reset it. [sjuni_Create]
void sub_562FE8(EEContext& ctx);  // 0x562FE8
// destroy an SJUNI handle (locked). [SJUNI_Destroy]
void sub_5630D0(EEContext& ctx);  // 0x5630D0
// destroy: zero the 48 bytes. [sjuni_Destroy]
void sub_563100(EEContext& ctx);  // 0x563100
// the uuid of an SJUNI handle (locked). [SJUNI_GetUuid]
void sub_563188(EEContext& ctx);  // 0x563188
// the uuid pointer (+8). [sjuni_GetUuid]
void sub_5631C0(EEContext& ctx);  // 0x5631C0
// set an SJUNI handle's error callback (locked). [SJUNI_EntryErrFunc]
void sub_563218(EEContext& ctx);  // 0x563218
// store the error callback and its object (+40 / +44). [sjuni_EntryErrFunc]
void sub_563268(EEContext& ctx);  // 0x563268
// reset an SJUNI handle (locked). [SJUNI_Reset]
void sub_5632C8(EEContext& ctx);  // 0x5632C8
// reset: chain every 16-byte node into the free list, empty the four lines. [sjuni_Reset]
void sub_5632F8(EEContext& ctx);  // 0x5632F8
// bytes on a line (locked). [SJUNI_GetNumData]
void sub_5633D0(EEContext& ctx);  // 0x5633D0
// bytes on a line: the sum of its chunks' sizes (lines 0..3). [sjuni_GetNumData]
void sub_563418(EEContext& ctx);  // 0x563418
// get a chunk (locked). [SJUNI_GetChunk]
void sub_5634D0(EEContext& ctx);  // 0x5634D0
// get a chunk from a line: its first node whole when it fits n (the node goes back to the free list), else in merge
//   mode the first n bytes (sub_563C28 splits it), else an empty chunk. [sjuni_GetChunk]
void sub_563530(EEContext& ctx);  // 0x563530
// put a chunk (locked). [SJUNI_PutChunk]
void sub_563680(EEContext& ctx);  // 0x563680
// put a chunk at a line's tail (merge mode: grown into the last node when contiguous); a free node is taken, none
//   left calls the error callback. [sjuni_PutChunk]
void sub_5636D0(EEContext& ctx);  // 0x5636D0
// unget a chunk (locked). [SJUNI_UngetChunk]
void sub_5637F8(EEContext& ctx);  // 0x5637F8
// unget a chunk at a line's head (merge mode: joined to the first node when contiguous). [sjuni_UngetChunk]
void sub_563848(EEContext& ctx);  // 0x563848
// is a chunk of n bytes available (locked). [SJUNI_IsGetChunk]
void sub_563968(EEContext& ctx);  // 0x563968
// is a chunk of n bytes available: the first node's size; merge mode: size >= n, else size == n. [sjuni_IsGetChunk]
void sub_5639D0(EEContext& ctx);  // 0x5639D0
// chunks on a line (locked). [SJUNI_GetNumChunk]
void sub_563A98(EEContext& ctx);  // 0x563A98
// chunks on a line: its node count. [sjuni_GetNumChunk]
void sub_563AE0(EEContext& ctx);  // 0x563AE0
// free nodes (locked). [SJUNI_GetNumChainPool]
void sub_563B70(EEContext& ctx);  // 0x563B70
// free nodes: the free list's length. [sjuni_GetNumChainPool]
void sub_563BA8(EEContext& ctx);  // 0x563BA8
// split a chunk {data, size} at n: the first part (size min(n, size)) and the rest (data + n, or {0, 0}).
//   [SJ_SplitChunk]
void sub_563C28(EEContext& ctx);  // 0x563C28

// --- SVM --------------------------------------------------------------------------------------------------------------
// SVM lock: call the lock callback (0x99A0A0 / its object 0x99A0A4); the outermost lock records its type. [SVM_Lock]
void sub_564888(EEContext& ctx);  // 0x564888
// SVM unlock: the outermost unlock checks the type (a mismatch is reported), then the unlock callback (0x99A0A8 /
//   0x99A0AC). [SVM_Unlock]
void sub_5648E8(EEContext& ctx);  // 0x5648E8
// SVM lock, type 1. [SVM_LockVar]
void sub_564978(EEContext& ctx);  // 0x564978
// SVM unlock, type 1. [SVM_UnlockVar]
void sub_564990(EEContext& ctx);  // 0x564990
// SVM lock, type 2. [SVM_LockRsc]
void sub_5649A8(EEContext& ctx);  // 0x5649A8
// SVM lock, type 3.
void sub_5649C0(EEContext& ctx);  // 0x5649C0
// SVM lock, type 4.
void sub_5649D8(EEContext& ctx);  // 0x5649D8
// SVM lock, type 5.
void sub_5649F0(EEContext& ctx);  // 0x5649F0
// SVM unlock, type 2. [SVM_UnlockRsc]
void sub_564A20(EEContext& ctx);  // 0x564A20
// SVM unlock, type 3.
void sub_564A38(EEContext& ctx);  // 0x564A38
// SVM unlock, type 4.
void sub_564A50(EEContext& ctx);  // 0x564A50
// SVM unlock, type 5.
void sub_564A68(EEContext& ctx);  // 0x564A68
// SVM error with a format: the 128-byte text buffer 0x7B2678 cleared, vsprintf into it, then the error callback
//   (0x99A0B0 / 0x99A0B4). [SVM_CallErr]
void sub_564AA8(EEContext& ctx);  // 0x564AA8
// SVM error with a text: strncpy (127) into 0x7B2678, then the error callback. [SVM_CallErr1]
void sub_564B50(EEContext& ctx);  // 0x564B50

// --- cvFs -------------------------------------------------------------------------------------------------------------
// call the cvFs error callback (0x7A08A4) with its object (0x7A08A8). [cvfs_callErrFunc]
void sub_5558E8(EEContext& ctx);  // 0x5558E8
// cvFs error: the message through the error callback. [cvfs_Error]
void sub_555918(EEContext& ctx);  // 0x555918
// cvFs init: the first call clears the 40 handles, the 32 device names and the default device name.
void cvFsInit(EEContext& ctx);  // 0x555940
// upper-case a string in place (a-z only). [cvfs_ToUpperStr]
void sub_555D10(EEContext& ctx);  // 0x555D10
// split "DEV:file" into an upper-case device name and the file name (no colon: no device; one-letter device names
//   are drive letters and stay in the file name).
void cvfs_getDevName(EEContext& ctx);  // 0x5561E8
// copy the default device name (empty when none).
void cvfs_getDefDev(EEContext& ctx);  // 0x556330

}  // namespace p3fes::game
