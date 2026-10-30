// Phase 5 slice savedata: the save system -- the save packing and unpacking of g_data.c (0x177DB0-0x17AC60), the rest of
// g_data.c (0x17C2F0-0x17D7C0: the persona compendium and the small tables the save carries), four datPersona.c
// persona functions, the H_Memcard request helpers, the memory-card save / load screens ("mcProc" / "mcWNDProc",
// 0x41BE50-0x42176C) and the name entry ("M_NameEntry", 0x45A3B0-0x45EBF8, with the field-event helpers that share the
// band). The bodies (game/src/data/savedata.cpp) are p3fes_handgen's: register for register and block for block as the
// recompiled bodies (frame, spills, $ra links, cycle charges, check points); their roles, the record offsets and the
// branch meanings are named on top (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). The card driver itself (libmc2
// sceMc2*, libdbc, the H_Memcard sequencers that call them) stays recompiled.
//
// Names: the functions keep their symbols/functions.json names (sub_XXXXXX); a proposed name is given in brackets
// (ADR-0009: from the instructions, the callers, the strings and the snapshots; not imported). Every address below is
// the ELF's (.bss / .data), the same in every run.
//
// =====================================================================================================================
// THE SAVE FORMAT (for the multiplayer server: every player carries one of these). Read from sub_177DB0 (the packer),
// sub_179030 / sub_179360 / sub_17A430 (the unpackers), sub_1791D0 (the verifier) and checked byte for byte against
// the save the game itself wrote on extracted/_ours/cards/tartarus.ps2 (tests/game/test_savedata.cpp).
// =====================================================================================================================
//
// The card file (the sequencers' sprintf in sub_190720 / H_Memcard_UpdateSeqMode): /BASLUS-21621Save<N>/BASLUS-21621Save<N>
// for The Journey, /BASLUS-21621SaveG<N>/... in The Answer (sub_17D800), /BASLUS-99998Save<N> / -99999 with the debug
// flag 5154, and /BASLUS-21569Save<N> -- Persona 3's own save (SLUS-21569) -- for a carry-over load; beside icon.sys
// and icon.ico. The file IS the packed buffer, all little-endian, no padding or alignment anywhere (the blocks run on at
// odd offsets: block 9 begins at file offset 8,150):
//
//   +0      u32   version: 3 (sub_177DB0's first argument; sub_41CC70 / sub_41DB20 pass 3). The unpackers skip the
//                 header only for version >= 2 and check the checksum only for version >= 3.
//   +4      52    the HEADER -- the slot list's summary (sub_41F370 / sub_41F940 draw it), kSaveHeader* below:
//                 +0 u16 day (days since April 5, gGlobalWork +0x59C), +2 u16 time slot (+0x59E), +4 s32 play time
//                 in 1/30 s (0x83A598; drawn as t / 108,000 hours and t / 1,800 % 60 minutes), +8 u8 the hero's level
//                 (from his exp and the table 0x5DC050, as datGetLevelForExp), +9 u8 the clear mark (2 if flag
//                 0x1319, else 1 if flag 0x1311, else 0: flag word 0x83A47C bits 25 / 17), +10 u8 *0x83AA98
//                 (sub_17D7B0), +11 u8 unused, +12 18 bytes the hero's first name (gGlobalWork +0x00), +30 18 bytes
//                 his surname (+0x12), +48 u8 / +49 u8 the current field (major, minor: the field task's first two
//                 words), +50 u16 = the byte sum of header bytes +0..+49, mod 256 (never checked on load).
//   +56     the BLOCKS, until the terminator: { s32 id; u32 size; u8 data[size]; } ... -- 158 blocks in this order:
//             1..36 the gGlobalWork pieces (kGlobalBlocks; 32 is not written),
//             0x100 * (k + 1) + 0 .. 11 for the ten party records k = 0..9 (twelve pieces each, kRecordPieces),
//             0x1000 the 20-entry equipment table 0x833E80 (400), 0x1001 the item count table 0x833C20 (600),
//             0x2000 the checksum: size 1, one u8 = the byte sum (mod 256) of every byte from file offset 56 up to
//                    this block's id (all the other blocks, headers included),
//   then    s32 -1 (0xFFFFFFFF), the terminator.
//   Size: 36,182 bytes (35,153 bytes of headers and data + 1,029: the 0x1000 / 0x1001 / 0x2000 blocks and the end).
//
// A loader (sub_179030) walks the blocks until id -1 or 0x2000 and copies each one whose id AND size it knows to its
// place (sub_179360); an unknown id or a size mismatch is skipped, so the format can grow. Then it rebuilds the
// display copies of the hero's name (0x833BB0 / 0x833BD0 / 0x833BF0, as sub_1774E0). The verifier (sub_1791D0) wants
// a buffer of at least 4,096 bytes, walks the blocks (a zero size, an id -1 before 0x2000, or running past the end
// fails) and compares the sum. A carry-over load (*0x7CE00C != 0: the card file is Persona 3's BASLUS-21569 save, the
// same block format) instead copies only blocks 2 (the hero's unit), 16 (the compendium), 17 (the flags) and 24 into
// the buffers *0x7CE050 / *0x7CE054 / *0x7CE058 / *0x7CE05C (sub_17A430).
//
// What the blocks hold (the gGlobalWork 0x836200 range 0x836200..0x83AA9C is saved whole, except the two pointers at
// +0x594 / +0x598 -- their targets are saved instead -- and two pad bytes; gamedata.h and calendar.h name the fields):
//   id  address    size   what
//    1  0x836200     36   the hero's first name (+0x00, 18) and surname (+0x12, 18)
//    2  0x836224     80   the hero's DatUnit (60), social stats s16[3], exp, condition (gamedata.h +0x24..+0x74)
//    3  0x836274   1288   the social-link block (ranks, points, day stamps, ... gamedata.h +0x74)
//    4  0x83677C     16   +0x57C..+0x58C (the comu month / day rows end at +0x570; u8 counter8[8] at +0x573)
//    5  0x83678C      8   the hero's equipment indices s16[4]
//    6  *0x836794  6000   the hero's equipment stock: 300 x EquipEntry (20), through the pointer at +0x594
//    7  *0x836798   600   the hero's item counts: 300 x u16, through the pointer at +0x598
//    8  0x83679C      2   the date (s16 days since April 5)
//    9  0x83679E      1   the time slot
//   10  0x8367A0      4   time skip active
//   11  0x8367A4      2   time skip target day
//   12  0x8367A6      1   time skip target slot
//   13  0x8367A7   1024   +0x5A7..+0x9A7
//   14  0x836BA8      2   the hero's current persona slot
//   15  0x836BAC    624   the hero's persona stock: 12 x Persona (52)
//   16  0x836E1C  13312   the persona compendium: 256 x Persona, one per persona id (flag bit 0 = registered)
//   17  0x83A21C    704   the flag bit array (176 words; datGetFlag / datSetFlag)
//   25  0x83A4DC    512   the counters s32[128]
//   18  0x83A6DC      4   money
//   19  0x83A6E0      8   the party s16[4]
//   20  0x83A6E8      4   +0x44E8 (sub_17B160 / sub_17B170 / sub_17B180)
//   21  0x83A6EC      4   the field to return to, major  } re-read by the packer from the field task and
//   22  0x83A6F0      4   the field to return to, minor  } K_FldDungeon_GetCurrentFloor() before packing
//   23  0x83A6F4      4   the dungeon floor to return to }
//   36  0x83A6F8      4   The Answer's day sequence index
//   26  0x83A6FC     28   +0x44FC..+0x4518
//   27  0x83A718     16   kBlock27: 4 x {s16 id (-1 = free), s16 counter} (sub_17C350..sub_17C750)
//   28  0x83A728      8   u8[8] (sub_17C7F0 / sub_17C860)
//   29  0x83A730      4   s32 counter (sub_17D030 / sub_17D040)
//   30  0x83A734    256   kBlock30: 32 x {u16 a, u16 b, u16 key, u16 value} (sub_17D060 / sub_17D1A0 / sub_17D250)
//   31  0x83A834    144   kBlock31: 9 x {8 bytes current, 8 bytes previous} (sub_17D3C0..sub_17D700)
//   24  0x83A8C4     44   +0x46C4..+0x46F0
//   33  0x83A8F0    424   +0x46F0..+0x4898
//   34  0x83679E      1   the time slot again
//   35  0x83AA98      4   s32 (sub_17D7B0; header +10)
//   The party records (gamedata.h PartyRecord, 868 bytes at 0x834010 + 868 * k, k = 0..9 = pc 2..11) are saved whole
//   in twelve pieces, block id 0x100 * (k + 1) + piece: piece 0 +0x000 (4), 1 +0x004 (80: the DatUnit, stats, exp,
//   condition), 2 +0x054 (8: equipment indices), 3 +0x05C (80: equipment[4]), 4 +0x0AC (48: the pairs), 5 +0x0DC (52:
//   the persona), 6 +0x110 (16), 7 +0x120 (16), 8 +0x130 (80), 9 +0x180 (400: equipment2[4] and 320 more), 10 +0x310
//   (80: the pouch), 11 +0x360 (4).
//
// The memory-card process (Y_McProc_CreateMcProcDrawTask: tasks "mcProc" sub_41E830 + "mcProcDraw", and the message
// window tasks "mcWNDProc" / "mcWNDProcDraw"): its work (956 bytes, kMcWork* below) runs a mode -- 0 check the card,
// 1 check the free space, 2 save, 3 load (sub_41CC70 starts one, sub_41CEA0 / sub_41D120 / sub_41D330 / sub_41DB20
// step it) -- over a 16-row slot list whose rows show the 52-byte headers read from the card. A save packs the state
// (sub_177DB0), copies it into a heap block {u32 size, u32 data -> +8, data} and hands it to H_Memcard_UpdateSeqMode
// through sub_18F170; a load reads the file into such a block (sub_190700), verifies it (sub_1791D0) and unpacks it
// (sub_179030), then sets *0x7CDFFC = 1. The H_Memcard request words are kMc* below (0x7CE00C..0x7CE03C).
// =====================================================================================================================
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

namespace savedata {

// --- the file ---------------------------------------------------------------------------------------------------------
inline constexpr u32 kSaveVersion = 3;
inline constexpr u32 kSaveHeaderOffset = 4;     // the 52-byte header
inline constexpr u32 kSaveHeaderSize = 52;
inline constexpr u32 kSaveBlocksOffset = 56;    // the first block
inline constexpr u32 kSaveFileSize = 36182;     // what sub_177DB0 produces (the card file's length)
inline constexpr u32 kSaveMinVerifySize = 4096; // sub_1791D0: a smaller buffer fails
inline constexpr s32 kBlockEnd = -1;            // the terminator
inline constexpr s32 kBlockChecksum = 0x2000;   // size 1: the u8 byte sum of [56, this block)
inline constexpr s32 kBlockEquipTable = 0x1000; // 0x833E80, 400
inline constexpr s32 kBlockItemTable = 0x1001;  // 0x833C20, 600
inline constexpr u32 kSaveBlockCount = 158;     // without the terminator

// The header (offsets inside the 52 bytes)
inline constexpr s32 kHdrDay = 0, kHdrSlot = 2, kHdrPlayTime = 4, kHdrLevel = 8, kHdrClearMark = 9, kHdrAnswer = 10,
                     kHdrFirstName = 12, kHdrSurname = 30, kHdrFieldMajor = 48, kHdrFieldMinor = 49, kHdrSum = 50;
inline constexpr u32 kNameSize = 18;
inline constexpr u32 kPlayTimePerHour = 108000;  // 1/30 s units (sub_41F370 / sub_41F940)
inline constexpr u32 kPlayTimePerMinute = 1800;

// --- what the packer reads -------------------------------------------------------------------------------------------
inline constexpr u32 kGlobalWork = 0x836200u;
inline constexpr u32 kHeroExp = 0x836268u;            // gGlobalWork +0x68 (the header's level)
inline constexpr u32 kHeroEquipmentStockPtr = 0x836794u;  // EquipEntry* (block 6 saves 6000 bytes of its target)
inline constexpr u32 kHeroItemNumPtr = 0x836798u;         // u16* (block 7 saves 600 bytes of its target)
inline constexpr u32 kPlayTime = 0x83A598u;           // s32, 1/30 s (header +4): counter 47 of 0x83A4DC
inline constexpr u32 kClearFlagWord = 0x83A47Cu;      // flag word 152: bit 17 = flag 0x1311, bit 25 = flag 0x1319
inline constexpr u32 kClearMarkA = 0x20000u, kClearMarkB = 0x2000000u;
inline constexpr u32 kHeroExpTable = 0x5DC050u;       // s32[99]
inline constexpr u32 kAnswerWord = 0x83AA98u;         // block 35, header +10 (sub_17D7B0)
inline constexpr u32 kReturnFieldMajor = 0x83A6ECu, kReturnFieldMinor = 0x83A6F0u, kReturnFloor = 0x83A6F4u;
inline constexpr s32 kGpFieldWork = -22448;           // $gp slot 0x7CD540: the field work (+0 major, +4 minor)
inline constexpr u32 kPartyRecords = 0x834010u;       // + 868 * k, k = 0..9
inline constexpr u32 kPartyRecordSize = 868;
inline constexpr s32 kPartyRecordsSaved = 10;
inline constexpr u32 kEquipTable = 0x833E80u;         // block 0x1000
inline constexpr u32 kItemTable = 0x833C20u;          // block 0x1001
inline constexpr u32 kNameCopyFirst = 0x833BB0u, kNameCopySurname = 0x833BD0u, kNameFull = 0x833BF0u;

// The gGlobalWork blocks in the packer's order: {id, address, size, through a pointer}.
struct GlobalBlock {
    s32 id;
    u32 addr;
    u32 size;
    bool via_pointer;  // addr is a pointer slot; the block holds `size` bytes of its target
};
inline constexpr GlobalBlock kGlobalBlocks[] = {
    {1, 0x836200u, 36, false},     {2, 0x836224u, 80, false},    {3, 0x836274u, 1288, false},
    {4, 0x83677Cu, 16, false},     {5, 0x83678Cu, 8, false},     {6, 0x836794u, 6000, true},
    {7, 0x836798u, 600, true},     {8, 0x83679Cu, 2, false},     {9, 0x83679Eu, 1, false},
    {10, 0x8367A0u, 4, false},     {11, 0x8367A4u, 2, false},    {12, 0x8367A6u, 1, false},
    {13, 0x8367A7u, 1024, false},  {14, 0x836BA8u, 2, false},    {15, 0x836BACu, 624, false},
    {16, 0x836E1Cu, 13312, false}, {17, 0x83A21Cu, 704, false},  {18, 0x83A6DCu, 4, false},
    {19, 0x83A6E0u, 8, false},     {20, 0x83A6E8u, 4, false},    {21, 0x83A6ECu, 4, false},
    {22, 0x83A6F0u, 4, false},     {23, 0x83A6F4u, 4, false},    {24, 0x83A8C4u, 44, false},
    {25, 0x83A4DCu, 512, false},   {26, 0x83A6FCu, 28, false},   {27, 0x83A718u, 16, false},
    {28, 0x83A728u, 8, false},     {29, 0x83A730u, 4, false},    {30, 0x83A734u, 256, false},
    {31, 0x83A834u, 144, false},   {33, 0x83A8F0u, 424, false},  {34, 0x83679Eu, 1, false},
    {35, 0x83AA98u, 4, false},     {36, 0x83A6F8u, 4, false},
};
inline constexpr s32 kGlobalBlockCount = 35;

// The twelve pieces of a party record: block id 0x100 * (k + 1) + piece.
struct RecordPiece {
    u32 offset;
    u32 size;
};
inline constexpr RecordPiece kRecordPieces[12] = {
    {0x000, 4}, {0x004, 80}, {0x054, 8}, {0x05C, 80}, {0x0AC, 48}, {0x0DC, 52},
    {0x110, 16}, {0x120, 16}, {0x130, 80}, {0x180, 400}, {0x310, 80}, {0x360, 4},
};
constexpr s32 record_block_id(s32 k, s32 piece) { return 0x100 * (k + 1) + piece; }

// The blocks a carry-over load keeps (sub_17A430): id -> the $gp slot holding the destination.
inline constexpr u32 kCarryOverMode = 0x7CE00Cu;      // non-zero: a carry-over load of a P3 save (sub_17A430)
inline constexpr u32 kCarryUnit = 0x7CE050u;          // block 2 (80)
inline constexpr u32 kCarryCompendium = 0x7CE054u;    // block 16 (13312)
inline constexpr u32 kCarryFlags = 0x7CE058u;         // block 17 (704)
inline constexpr u32 kCarryBlock24 = 0x7CE05Cu;       // block 24 (44)

// --- the tables of g_data.c 0x17C2F0-0x17D7C0 ------------------------------------------------------------------------
inline constexpr u32 kCompendium = 0x836E1Cu;         // 256 x 52 (Persona), index = persona id
inline constexpr u32 kPersonaSize = 52;
inline constexpr s32 kPersonaIds = 256;
inline constexpr u32 kPersonaTableSlot = 0x7CE420u;   // *: 14-byte persona records; u16 +0 flags: 0x08 / 0x20 not
                                                      // registrable (sub_17CD30, sub_17CF00)
inline constexpr u32 kBlock27 = 0x83A718u;            // 4 x {s16 id, s16 counter}; slots 0..2 used
inline constexpr s32 kBlock27Slots = 3, kBlock27CounterMax = 32001;
inline constexpr u32 kBlock28 = 0x83A728u;            // u8[8]
inline constexpr u32 kBlock29 = 0x83A730u;            // s32
inline constexpr u32 kBlock30 = 0x83A734u;            // 32 x {u16 a, u16 b, u16 key, u16 value}
inline constexpr s32 kBlock30Rows = 32;
inline constexpr u32 kBlock31 = 0x83A834u;            // 9 x {u8[8] current, u8[8] previous}; 5 used
inline constexpr s32 kBlock31Rows = 9, kBlock31Used = 5;
inline constexpr u32 kBlock31Init = 0x5E38C0u;        // f32[4], copied into every row (sub_17D3C0)
inline constexpr u32 kSkillElementMap = 0x5E38A0u;    // s8[19] (sub_17D2E0)

// --- H_Memcard's request words (dword_7CDF54[i] = 0x7CDF54 + 4 i) ----------------------------------------------------
inline constexpr u32 kMcLoadedFlag = 0x7CDFFCu;       // [42]: 1 after a load (MEMCARD_LOAD OK)
inline constexpr u32 kMcCancel = 0x7CE01Cu;           // [50]: sub_190580 sets 1 (the sequencers' reset / cancel)
inline constexpr u32 kMcList = 0x7CE020u;             // [51]: the slot-list buffer (sub_190CB0)
inline constexpr u32 kMcData = 0x7CE028u;             // [53]: the data to write / the read buffer
inline constexpr u32 kMcReadBlock = 0x7CE02Cu;        // [54]: the load's {size, data} block (sub_190700)
inline constexpr u32 kMcSize = 0x7CE030u;             // [55]: the size to write (sub_18F170)
inline constexpr u32 kMcSlot = 0x7CE034u;             // [56]: the slot (0-based)
inline constexpr u32 kMcSubStep = 0x7CE038u;          // [57]
inline constexpr u32 kMcSeqMode = 0x7CE03Cu;          // [58]: 0 start, 4 format confirmed, 9 overwrite confirmed
inline constexpr u32 kSeqList = 0x7CE040u;            // [59..62] a 500-entry list of 8-byte words (sub_1919C0)

// --- the memory-card process work (956 bytes; Y_McProc_CreateMcProcDrawTask) -----------------------------------------
inline constexpr s32 kMcWorkState = 0;       // u16: the task's load state 0..10 (sub_41E830)
inline constexpr s32 kMcWorkMenu = 2;        // u16: the slot-list state 0..13 (sub_41E010)
inline constexpr s32 kMcWorkFlags = 4;       // bit 0 ready to draw, 1 save screen (load otherwise), 2 drawing pass,
                                             // 3 done (sub_4204F0), 10 fade in, 11 fade out
inline constexpr s32 kMcWorkMode = 8;        // 0 check, 1 area check, 2 save, 3 load
inline constexpr s32 kMcWorkStep = 12;       // the mode's step
inline constexpr s32 kMcWorkStepFlags = 16;  // bit 0: the card needs formatting (save)
inline constexpr s32 kMcWorkSlotUsed = 20;   // s32[16]: a save in that slot
inline constexpr s32 kMcWorkHeaders = 84;    // 16 x 52: the slots' headers
inline constexpr s32 kMcWorkSlots = 16;
inline constexpr s32 kMcWorkDrawTask = 916;  // "mcProcDraw"
inline constexpr s32 kMcWorkWindow = 920;    // the "mcWNDProc" task
inline constexpr s32 kMcWorkList = 924;      // the nmCmdList of the 16 rows
inline constexpr s32 kMcWorkBuffer = 928;    // the heap block {u32 size, u32 data, data...}
inline constexpr s32 kMcWorkElemA = 932, kMcWorkFade = 936, kMcWorkAlpha = 938, kMcWorkElemB = 940;
inline constexpr s32 kMcWorkIconFile = 944, kMcWorkPakFile = 948, kMcWorkTimer = 952;
inline constexpr s32 kMcModeCheck = 0, kMcModeArea = 1, kMcModeSave = 2, kMcModeLoad = 3;
inline constexpr u32 kMcBufferAlloc = 131080;  // 0x20008: {size, data} + 128 KiB
// H_Memcard sequencer results the steps test
inline constexpr s32 kMcOk = 100, kMcNoCard = -2, kMcCancelled = 3;

// --- the name entry -------------------------------------------------------------------------------------------------
inline constexpr u32 kNameFirstBuf = 0x95C240u;  // 18 bytes: 8 two-byte characters + NUL
inline constexpr u32 kNameSurnameBuf = 0x95C220u;
inline constexpr u32 kNameBlank = 0x7CDB14u;     // the two-byte blank character
inline constexpr s32 kNameChars = 8;
inline constexpr s32 kNameEntryFlag = 5127;      // set while the name entry runs (0x1407)
inline constexpr u32 kNameWork = 0x7CE6A0u;      // dword_7CE6A0[22] field-event task, [24] the dialog answer,
                                                 // [26] the "M_NameEntry" task, [27..29] the cursor, [30] the sprites

#pragma pack(push, 1)
struct SaveHeader {
    u16 day;
    u16 slot;
    s32 play_time;
    u8 level;
    u8 clear_mark;
    u8 answer;
    u8 pad11;
    u8 first_name[18];
    u8 surname[18];
    u8 field_major;
    u8 field_minor;
    u16 sum;
};
static_assert(sizeof(SaveHeader) == kSaveHeaderSize && offsetof(SaveHeader, first_name) == kHdrFirstName &&
              offsetof(SaveHeader, field_major) == kHdrFieldMajor && offsetof(SaveHeader, sum) == kHdrSum);
#pragma pack(pop)

}  // namespace savedata

// --- the register-ABI bodies (arguments in $a0.., the result in $v0; game/src/data/savedata.cpp) ---------------------
// Each: its address, (arguments) -> result and [the proposed name]; the role is in the .cpp.
// datPersona.c
void sub_173C60(EEContext& ctx);  // 0x173C60 (persona, stat) -> s8 [datPersonaGetEquipStatBonus]
void sub_174C10(EEContext& ctx);  // 0x174C10 (slot) -> 1 / 0 [datPersonaRemoveSlot]
void sub_175820(EEContext& ctx);  // 0x175820 (pc, id) -> 1 [datPersonaGive]
void sub_175CE0(EEContext& ctx);  // 0x175CE0 (persona, out40) [datPersonaCalcLevelUp]
// g_data.c: the save
void sub_177DB0(EEContext& ctx);  // 0x177DB0 (version, u32* size) -> buffer [datSavePack]
void sub_179030(EEContext& ctx);  // 0x179030 (version, data, size) [datSaveUnpack]
void sub_1791D0(EEContext& ctx);  // 0x1791D0 (version, data, size) -> 1 ok / 0 [datSaveVerify]
void sub_179360(EEContext& ctx);  // 0x179360 (version, id, size, src) [datSaveUnpackBlock]
void sub_17A430(EEContext& ctx);  // 0x17A430 (version, id, size, src) [datSaveUnpackCarryOverBlock]
// g_data.c: the tables the save carries
void sub_17C2F0(EEContext& ctx);  // 0x17C2F0 (s16** a, s16** b) -> key(a) - key(b) [datBlock27Compare]
void sub_17C350(EEContext& ctx);  // 0x17C350 () [datBlock27Sort]
void sub_17C4E0(EEContext& ctx);  // 0x17C4E0 (id) -> 1 / 0 [datBlock27Add]
void sub_17C590(EEContext& ctx);  // 0x17C590 (id) [datBlock27Remove]
void sub_17C610(EEContext& ctx);  // 0x17C610 (id) -> entry / 0 [datBlock27Find]
void sub_17C670(EEContext& ctx);  // 0x17C670 (i) -> entry / 0 [datBlock27Get]
void sub_17C6C0(EEContext& ctx);  // 0x17C6C0 () -> sub_403130()
void sub_17C6E0(EEContext& ctx);  // 0x17C6E0 () -> sub_403220()
void sub_17C700(EEContext& ctx);  // 0x17C700 () -> count [datBlock27Count]
void sub_17C750(EEContext& ctx);  // 0x17C750 (arg) [datBlock27Tick]
void sub_17C7F0(EEContext& ctx);  // 0x17C7F0 (i, value) [datBlock28Set]
void sub_17C860(EEContext& ctx);  // 0x17C860 (i) -> u8 [datBlock28Get]
void sub_17C8C0(EEContext& ctx);  // 0x17C8C0 (id) -> Persona* / 0 [datCompendiumGet]
void sub_17C960(EEContext& ctx);  // 0x17C960 (persona) [datCompendiumStore]
void sub_17CA10(EEContext& ctx);  // 0x17CA10 (persona) -> -1 / 1 / 0 [datCompendiumCompare]
void sub_17CD30(EEContext& ctx);  // 0x17CD30 (persona) -> persona / entry / 0 [datCompendiumRegister]
void sub_17CF00(EEContext& ctx);  // 0x17CF00 () -> percent [datCompendiumPercent]
void sub_17D030(EEContext& ctx);  // 0x17D030 () -> s32 [datBlock29Get]
void sub_17D040(EEContext& ctx);  // 0x17D040 () [datBlock29Increment]
void sub_17D060(EEContext& ctx);  // 0x17D060 (ab, key, value) -> row [datBlock30Set]
void sub_17D1A0(EEContext& ctx);  // 0x17D1A0 (a, key, delta) -> value / -1 [datBlock30Subtract]
void sub_17D250(EEContext& ctx);  // 0x17D250 (a, key) -> value / -1 [datBlock30Get]
void sub_17D2E0(EEContext& ctx);  // 0x17D2E0 (skill) -> s8 [datSkillElementClass]
void sub_17D3C0(EEContext& ctx);  // 0x17D3C0 () [datBlock31Init]
void sub_17D450(EEContext& ctx);  // 0x17D450 (i, rec8) -> 1 / 0 [datBlock31Update]
void sub_17D610(EEContext& ctx);  // 0x17D610 (i) -> 1 / 0 [datBlock31Refresh]
void sub_17D6D0(EEContext& ctx);  // 0x17D6D0 (i, out8) [datBlock31GetPrevious]
void sub_17D700(EEContext& ctx);  // 0x17D700 (i, which, out8) [datBlock31Get]
void sub_17D790(EEContext& ctx);  // 0x17D790 () -> sub_3D74B0()
void sub_17D7B0(EEContext& ctx);  // 0x17D7B0 () -> *0x83AA98 [datGetBlock35]
// H_Memcard requests
void sub_18F170(EEContext& ctx);  // 0x18F170 (slot, data, size) [H_Memcard_RequestSave]
void sub_18F2A0(EEContext& ctx);  // 0x18F2A0 () [H_Memcard_ConfirmOverwrite]
void sub_18F2B0(EEContext& ctx);  // 0x18F2B0 () [H_Memcard_ConfirmFormat]
void sub_190580(EEContext& ctx);  // 0x190580 () [H_Memcard_Cancel]
void sub_190700(EEContext& ctx);  // 0x190700 (slot, data, block) [H_Memcard_RequestLoad]
void sub_190CB0(EEContext& ctx);  // 0x190CB0 (list) [H_Memcard_RequestList]
void sub_191640(EEContext& ctx);  // 0x191640 (slot) [H_Memcard_RequestAreaCheck]
void sub_1919C0(EEContext& ctx);  // 0x1919C0 (base, size) [the 500-word list init]
// the memory-card screens
void sub_41BE50(EEContext& ctx);  // 0x41BE50 (h) -> h+12 [a handle release]
void sub_41BEB0(EEContext& ctx);  // 0x41BEB0 (h) -> sub_4C35D0(h+16)
void sub_41BEE0(EEContext& ctx);  // 0x41BEE0 (h) -> sub_4C3760(h+16)
void sub_41BF10(EEContext& ctx);  // 0x41BF10 (list, rgba) [set every entry's colour]
void sub_41C140(EEContext& ctx);  // 0x41C140 (x, y, alpha, which) [mcDrawDigit]
void sub_41C180(EEContext& ctx);  // 0x41C180 (work, element, out) [mcProcSetElementAnim]
void sub_41CC70(EEContext& ctx);  // 0x41CC70 (work, mode) [mcProcBeginMode]
void sub_41CEA0(EEContext& ctx);  // 0x41CEA0 (work) -> 0 / 1 / 3 / 4 [mcProcCheckStep]
void sub_41D120(EEContext& ctx);  // 0x41D120 (work) -> 0 / 1 / 4 [mcProcAreaStep]
void sub_41D330(EEContext& ctx);  // 0x41D330 (work) -> 0 / 1 / 2 / 4 [mcProcSaveStep]
void sub_41DB20(EEContext& ctx);  // 0x41DB20 (work) -> 0 / 1 / 2 / 4 [mcProcLoadStep]
void sub_41E010(EEContext& ctx);  // 0x41E010 (work) -> 1 done [mcProcUpdateMenu]
void sub_41E830(EEContext& ctx);  // 0x41E830 (task) -> 0 / -1 [mcProcUpdateTask]
void sub_41EAF0(EEContext& ctx);  // 0x41EAF0 (task) [mcProcDestroyTask]
void Y_McProc_UpdateMcProcDrawTask(EEContext& ctx);  // 0x41EB50 (task)
void sub_41EC30(EEContext& ctx);  // 0x41EC30 (list) [mcProcListUpdate]
void nullsub_59(EEContext& ctx);  // 0x41EC60 [mcProcListDraw]
void sub_41EC70(EEContext& ctx);  // 0x41EC70 (work) -> slot used [mcProcSelectedSlotUsed]
void sub_41ECA0(EEContext& ctx);  // 0x41ECA0 (x, y, alpha, ...) [mcDrawCursor]
void sub_41EF40(EEContext& ctx);  // 0x41EF40 (x, y, alpha, ...) [mcDrawCursorFrame]
void sub_41F370(EEContext& ctx);  // 0x41F370 (x, y, alpha, list, row, ...) [mcDrawSlotRow]
void sub_41F940(EEContext& ctx);  // 0x41F940 (x, y, alpha, list, row, ...) [mcDrawSlotRowAnswer]
void sub_41FD90(EEContext& ctx);  // 0x41FD90 (x, y, alpha, list, row) [mcProcRowDraw]
void sub_41FF50(EEContext& ctx);  // 0x41FF50 (x, y, alpha, work) [mcProcFrameDraw]
void sub_4202E0(EEContext& ctx);  // 0x4202E0 (work) [mcProcFree]
void Y_McProc_CreateMcProcDrawTask(EEContext& ctx);  // 0x420340 (parent, save) -> task
void sub_4204F0(EEContext& ctx);  // 0x4204F0 (task) -> done [mcProcIsDone]
void sub_420520(EEContext& ctx);  // 0x420520 (window, element, out) [mcWndSetElementAnim]
void sub_420A20(EEContext& ctx);  // 0x420A20 (x, y, alpha, window) [mcWndDrawText]
void sub_420DA0(EEContext& ctx);  // 0x420DA0 (x, y, alpha, work) [mcWndDraw]
void sub_420F60(EEContext& ctx);  // 0x420F60 (list, node) -> 0 [mcWndFreeNode]
void sub_420F90(EEContext& ctx);  // 0x420F90 (task) [mcWndDestroyTask]
void sub_420FE0(EEContext& ctx);  // 0x420FE0 (work, window) -> 1 closed [mcWndUpdateWindow]
void Y_Misc_UpdateMcWNDProcTask(EEContext& ctx);  // 0x421330 (task)
void sub_421460(EEContext& ctx);  // 0x421460 (task) [mcWndDrawTask]
void Y_Misc_CreateMCWNDProcTasks(EEContext& ctx);  // 0x4214E0 (parent, arg) -> draw task
void sub_4215B0(EEContext& ctx);  // 0x4215B0 (task, message) [mcWndOpen]
void sub_421650(EEContext& ctx);  // 0x421650 (task) [mcWndClose]
void sub_421700(EEContext& ctx);  // 0x421700 (task) -> 1 none / 0 open / 1 + answer [mcWndGetResult]
void sub_421760(EEContext& ctx);  // 0x421760 () -> 0x7CE6A4
// the field-event helpers on the task in 0x7CE6F8, and the name entry
void sub_45A3B0(EEContext& ctx);  // 0x45A3B0 () -> state >= 2 [fldEvtIsShown]
void sub_45A3E0(EEContext& ctx);  // 0x45A3E0 () [fldEvtRequestClose]
void sub_45A400(EEContext& ctx);  // 0x45A400 () [fldEvtHide]
void sub_45A430(EEContext& ctx);  // 0x45A430 (pause) [fldEvtPauseTimer]
void sub_45A490(EEContext& ctx);  // 0x45A490 (task, ...) [nameDrawKeyboard]
void sub_45ACE0(EEContext& ctx);  // 0x45ACE0 (task, ...) [nameDrawCursor]
void sub_45AF40(EEContext& ctx);  // 0x45AF40 () -> s32 / -1 [fldEvtGetValue]
void sub_45AF70(EEContext& ctx);  // 0x45AF70 (value) [fldEvtSetByte93]
void sub_45AF90(EEContext& ctx);  // 0x45AF90 (track) -> 1 null / 0 [animTrackReset]
void sub_45AFD0(EEContext& ctx);  // 0x45AFD0 (track, x0, y0, x1, y1, delay, hold, frames; f12 rate) [animTrackAddKey]
void sub_45B190(EEContext& ctx);  // 0x45B190 (track) [animTrackStep]
void sub_45B420(EEContext& ctx);  // 0x45B420 (track, out xy) -> 0 / 1 / 2 [animTrackGetPos]
void sub_45B480(EEContext& ctx);  // 0x45B480 (track) -> running [animTrackIsRunning]
void sub_45B4B0(EEContext& ctx);  // 0x45B4B0 (track) -> idle [animTrackIsIdle]
void sub_45B4E0(EEContext& ctx);  // 0x45B4E0 (track) -> f0 0..1 [animTrackProgress]
void sub_45B620(EEContext& ctx);  // 0x45B620 (task, ...) [nameDrawFrame]
void sub_45B830(EEContext& ctx);  // 0x45B830 (task, row) [nameMoveRowCursor]
void sub_45B8F0(EEContext& ctx);  // 0x45B8F0 (task) [nameMoveKeyCursor]
void sub_45BCB0(EEContext& ctx);  // 0x45BCB0 (task, char2) [nameTypeChar]
void sub_45BD90(EEContext& ctx);  // 0x45BD90 (task) [nameInput]
void sub_45C530(EEContext& ctx);  // 0x45C530 (task) [nameDrawNames]
void sub_45C8C0(EEContext& ctx);  // 0x45C8C0 (task, ...) [nameDrawPanel]
void sub_45CDD0(EEContext& ctx);  // 0x45CDD0 (task, ...) [nameDrawPanels]
void sub_45CE90(EEContext& ctx);  // 0x45CE90 (task) [nameDraw]
void sub_45D990(EEContext& ctx);  // 0x45D990 (task, step) [nameDrawIntro]
void sub_45DF00(EEContext& ctx);  // 0x45DF00 (task) -> -1 / answer [nameConfirm]
void sub_45E010(EEContext& ctx);  // 0x45E010 (task) -> 1 done [nameIntroStep0]
void sub_45E0C0(EEContext& ctx);  // 0x45E0C0 (task) -> 1 done [nameIntroStep1]
void sub_45E170(EEContext& ctx);  // 0x45E170 (task) -> 1 done [nameIntroStep2]
void M_Name_UpdateNameKeyProcTask(EEContext& ctx);  // 0x45E3E0 (task)
void sub_45E7B0(EEContext& ctx);  // 0x45E7B0 (task) [nameKeyProcDestroy]
void sub_45E7E0(EEContext& ctx);  // 0x45E7E0 () [nameInitBuffers]
void M_Name_UpdateNameEntryTask(EEContext& ctx);  // 0x45E8C0 (task)
void sub_45EA80(EEContext& ctx);  // 0x45EA80 (task) [nameEntryDestroy]
void M_Name_CreateNameEntryTask(EEContext& ctx);  // 0x45EAF0 () -> 1 (COMM 0x1BF)
void sub_45EBA0(EEContext& ctx);  // 0x45EBA0 () -> 1 finished [nameEntryWait] (COMM 0x1C0)

}  // namespace p3fes::game
