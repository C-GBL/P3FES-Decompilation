// BMD message manager (Atlus itfMesManager.c) and the manager slot list (docs/ANALYSIS/18_script_vm.md
// section 5), hand-decompiled from SLUS_216.21. Names are the IDA names in symbols/p3fes.sym (the
// 2026-10-20 master re-export); the three list helpers have no name yet and keep their sub_* names.
//
// A BMD ("MSG0"/"MSG1", docs/FORMATS.md section 3, runtime/include/p3fes/formats/bmd.h) is used in
// place: itfMesMngRelocateBmdOnce turns its +0x20-relative pointers into guest addresses the first
// time a handle binds it (flag byte +0x1C), and the message handle (488 bytes, itfMesMngCreateHandle)
// keeps the BMD's address at +4.
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

// --- the BMD image -----------------------------------------------------------------------------------
namespace bmd {
inline constexpr u32 kMagicMsg0 = 0x3047534Du;  // "MSG0"
inline constexpr u32 kMagicMsg1 = 0x3147534Du;  // "MSG1"
inline constexpr u32 kPointerBase = 0x20;       // stored pointers are relative to header + 0x20
}  // namespace bmd

struct BmdHeader {  // 32 bytes
    u32 type;           // +0x00 7
    u32 size;           // +0x04 file size
    u32 magic;          // +0x08 "MSG0" / "MSG1"
    u32 zero;           // +0x0C
    u32 reloc_offset;   // +0x10 relocation table, from the header
    s32 reloc_size;     // +0x14 its length in bytes
    u32 message_count;  // +0x18
    u8 relocated;       // +0x1C 0 on disc (the low byte of the 0x00020000 version word); 1 once relocated in place
    u8 pad_1d;          // +0x1D
    u16 version;        // +0x1E 0x0002
};
static_assert(sizeof(BmdHeader) == 32);
static_assert(offsetof(BmdHeader, relocated) == 0x1C && offsetof(BmdHeader, message_count) == 0x18);

struct BmdMessageEntry {  // 8 bytes, message_count of them at +0x20
    u32 type;  // 0 dialogue, 1 selection
    u32 ptr;   // the record (relative to +0x20 on disc; a guest address once relocated)
};
static_assert(sizeof(BmdMessageEntry) == 8);

struct BmdSpeakerBlock {  // 16 bytes right after the entries: itfMesMngGetSpeakerBlock's result
    u32 table;  // speaker name pointer table
    u32 count;  // speaker names
    u32 word2;  // kept by the handle (+8) for "MSG1" files; 0 in every BMD on the disc
    u32 word3;
};
static_assert(sizeof(BmdSpeakerBlock) == 16);

// --- the message handle (488 bytes; H_Malloc / RwHeapMalloc in itfMesMngCreateHandle 0x3A2EF0) -----
// Fields named here are the ones the hand-written functions and 18_script_vm.md section 5 use; the
// `unknown_*` runs are bytes whose meaning was not read. Sub-records at +20, +36, +64, +168, +212 and
// +468 are initialised by itfMesMngInitSpeakerRecord .. itfMesMngInitWindowRecord.
struct ItfMesHandle {
    u32 state;           // +0   low 3 bits: request state (2 open request, 3 ...), bit 24 set while a message is up
    u32 bmd;             // +4   guest address of the bound BMD (itfMesMngBindBmd)
    u32 speaker_word2;   // +8   BmdSpeakerBlock::word2 of an "MSG1" file, else 0 (itfMesMngBindBmd)
    u32 word_c;          // +12  zeroed by itfMesMngCreateHandle
    u8 unknown_10[2];    // +16
    s16 window_type;     // +18  printed by itfMesMngInitialize ("type=%d"); set to 4 for script handles
    u8 unknown_14[24];   // +20  sub-record (itfMesMngInitSpeakerRecord)
    u32 record;          // +44  the current dialogue record (itfMesMngRequestMessage)
    u8 unknown_30[4];    // +48
    s8 busy;             // +52  0 idle; polled by scrCommand_MSG, negative once the window closed
    u8 unknown_35[33];   // +53
    s16 selection;       // +86  the chosen option of a selection message
    u8 unknown_58[80];   // +88
    u8 unknown_a8[44];   // +168 sub-record copied by itfMesMngSwitchCurrentHandle when the current handle changes
    u8 unknown_d4[256];  // +212 sub-record (itfMesMngClearMessageArgs)
    u8 unknown_1d4[16];  // +468 sub-record (itfMesMngInitWindowRecord)
    u32 word_1e4;        // +484 zeroed by itfMesMngCreateHandle
};
static_assert(sizeof(ItfMesHandle) == 488);
static_assert(offsetof(ItfMesHandle, bmd) == 4 && offsetof(ItfMesHandle, speaker_word2) == 8 &&
              offsetof(ItfMesHandle, window_type) == 18 && offsetof(ItfMesHandle, record) == 44 &&
              offsetof(ItfMesHandle, busy) == 52 && offsetof(ItfMesHandle, selection) == 86 &&
              offsetof(ItfMesHandle, unknown_a8) == 168 && offsetof(ItfMesHandle, word_1e4) == 484);
constexpr u32 kItfMesHandleSize = 488;

// --- the manager slot list (sItfMesManagerMsgHead 0x959ED0; sub_3B4920 / sub_3B49A0 / sub_3B4A20) --
// Two doubly linked lists over one array of slots: the slots in use (head/tail) and the free ones
// (free_head/free_tail). Every slot starts with its links and its index in the array; the message
// manager's slot continues with the current handle (+12/+16) and four {handle, handle} entries at +20.
struct ItfMesSlotList {  // 16 bytes
    u32 head;       // +0  first slot in use, 0 when none
    u32 tail;       // +4  last slot in use
    u32 free_head;  // +8  first free slot (sub_3B49A0 takes it)
    u32 free_tail;  // +12 last free slot (sub_3B4A20 appends there)
};
static_assert(sizeof(ItfMesSlotList) == 16);

struct ItfMesSlotLinks {  // the first 12 bytes of every slot
    u32 prev;
    u32 next;
    s32 id;  // the slot's index, written by sub_3B4920 as a sign-extended byte
};
static_assert(sizeof(ItfMesSlotLinks) == 12);
constexpr u32 kItfMesManagerMsgHead = 0x959ED0u;

// 0x3A5090 itfMesMngCheckBmdMagic: 1 when the word at bmd+8 is "MSG0" or "MSG1", else 0.
void itfMesMngCheckBmdMagic(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A50E0 itfMesMngGetMessageEntry: the guest address of entry `index` of the handle's BMD,
// handle->bmd + 0x20 + 8 * index (32-bit arithmetic, no bounds check).
void itfMesMngGetMessageEntry(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A5100 itfMesMngGetSpeakerBlock: bmd + 0x20 + 8 * message_count, the BmdSpeakerBlock.
void itfMesMngGetSpeakerBlock(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A5030 itfMesMngRelocateBmdOnce: when the flag byte at +0x1C is 0, applies the relocation table
// (ApplyRelocTable(bmd+0x20, bmd+0x20, bmd + reloc_offset, reloc_size)) and sets the flag to 1; a
// relocated image is left alone.
void itfMesMngRelocateBmdOnce(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3A42C0 itfMesMngBindBmd: handle->bmd = bmd (K_Assert "itfMesManager.c" 3085 on a null handle),
// relocates the BMD once, and keeps the speaker block's third word at handle+8 for an "MSG1" file
// (0 otherwise). Returns the BMD the handle held before.
void itfMesMngBindBmd(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3B4920 sub_3B4920: builds the free list over `count` slots of `stride` bytes starting at
// `slots_va` (prev/next links, id = index as a signed byte) and resets `list_va`: nothing in use, every
// slot free. The body runs once and then while the remaining count is >= 2, so the last slot written
// is slot max(count, 2) - 1.
void sub_3B4920(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3B49A0 sub_3B49A0: pops the first free slot and appends it to the slots in use; 0 when none is free.
void sub_3B49A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// 0x3B4A20 sub_3B4A20: unlinks `slot_va` from the slots in use and appends it to the free list.
void sub_3B4A20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
