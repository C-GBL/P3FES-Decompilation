// VU1 micro-instruction decoder: one 64-bit pair = upper word (FMAC ops + I/E/M/D/T flags) and lower word
// (load/store, integer, EFU, branch, flag ops; a float immediate when the I flag is set).
//
// The tables mirror our verified Python decoder `tools/ours/vu1/vu1_decode.py` entry by entry (same field layout,
// same mnemonic strings, same UNKNOWN cases, same `NOP` rule for the lower word); `tests/vu1/test_vu1_census.cpp`
// proves the two agree on all 123,095 pairs of the 114 dumped programs (`symbols/vu1_micro_census.json`). Encoding
// source: the VU User's Manual field layout, cross-checked against `ps2-web-recomp` @ c0f476e
// `runtime/src/vu_micro.cpp` (`decode_upper`, `lower`); see THIRD_PARTY.md. No text was copied.
//
// The decoder is the single owner of field interpretation: the interpreter and the Q-pipeline timing model read the
// fields below and never re-parse raw words.
#pragma once

#include "p3fes/ee_types.h"

#include <string_view>

namespace p3fes::vu1 {

// VU1 micro memory: 16 KiB = 2048 pairs; the PC wraps inside it (09 §2.4: 73 branches rely on this).
inline constexpr u32 kMicroBytes = 0x4000u;
inline constexpr u32 kMicroMask = kMicroBytes - 1u;
inline constexpr u32 kMicroPairs = kMicroBytes / 8u;
// VU1 data memory: 16 KiB = 1024 qwords; qword addresses wrap inside it (upstream behaviour).
inline constexpr u32 kDataBytes = 0x4000u;
inline constexpr u32 kDataQwords = kDataBytes / 16u;

inline constexpr u32 kUpperNopWord = 0x000002FFu; // special index 0x2F with all other fields zero
inline constexpr u32 kLowerNopWord = 0x8000033Cu; // `move vf00, vf00` with dest 0: the conventional lower nop

// Upper-word flag bits (VU User's Manual).
inline constexpr u32 kFlagI = 1u << 31; // lower word is a float immediate for the I register (LOI)
inline constexpr u32 kFlagE = 1u << 30; // end: stop after the next pair
inline constexpr u32 kFlagM = 1u << 29; // VU0 only
inline constexpr u32 kFlagD = 1u << 28; // debug break
inline constexpr u32 kFlagT = 1u << 27; // debug halt

// Form-qualified upper mnemonics, in table order (funct table, then the funct >= 0x3C special table).
enum class UpperOp : u8 {
    Unknown,
    // funct < 0x3C
    ADDbc, SUBbc, MADDbc, MSUBbc, MAXbc, MINIbc, MULbc,
    MULq, MAXi, MULi, MINIi, ADDq, MADDq, ADDi, MADDi, SUBq, MSUBq, SUBi, MSUBi,
    ADD, MADD, MUL, MAX, SUB, MSUB, OPMSUB, MINI,
    // funct >= 0x3C, index = fd * 4 + (funct & 3)
    ADDAbc, SUBAbc, MADDAbc, MSUBAbc,
    ITOF0, ITOF4, ITOF12, ITOF15, FTOI0, FTOI4, FTOI12, FTOI15,
    MULAbc, MULAq, ABS, MULAi, CLIP,
    ADDAq, MADDAq, ADDAi, MADDAi, SUBAq, MSUBAq, SUBAi, MSUBAi,
    ADDA, MADDA, MULA, SUBA, MSUBA, OPMULA, NOP,
    Count
};

enum class LowerOp : u8 {
    Unknown,
    NOP, // exactly kLowerNopWord (any other `move` encoding is MOVE)
    LOI, // I flag set: the word is the immediate
    // opcode (bits 31..25) != 0x40
    LQ, SQ, ILW, ISW, IADDIU, ISUBIU,
    FCEQ, FCSET, FCAND, FCOR, FSEQ, FSSET, FSAND, FSOR, FMEQ, FMAND, FMOR, FCGET,
    B, BAL, JR, JALR, IBEQ, IBNE, IBLTZ, IBGTZ, IBLEZ, IBGEZ,
    // opcode 0x40, funct < 0x3C
    IADD, ISUB, IADDI, IAND, IOR,
    // opcode 0x40, funct >= 0x3C, index = id * 4 + (funct & 3)
    MOVE, MR32, LQI, SQI, LQD, SQD, DIV, SQRT, RSQRT, WAITQ, MTIR, MFIR, ILWR, ISWR,
    RNEXT, RGET, RINIT, RXOR, MFP, XTOP, XITOP, XGKICK,
    ESADD, ERSADD, ELENG, ERLENG, EATANxy, EATANxz, ESUM, ESQRT, ERSQRT, ERCPR, WAITP, ESIN, EATAN, EEXP,
    Count
};

// Raw fields are always extracted (whatever the op) so timing models can use them without re-parsing.
struct UpperInsn {
    UpperOp op = UpperOp::Unknown;
    u8 dest = 0;   // bits 24..21: bit 3 = x .. bit 0 = w
    u8 ft = 0;     // bits 20..16
    u8 fs = 0;     // bits 15..11
    u8 fd = 0;     // bits 10..6
    u8 bc = 0;     // bits 1..0: broadcast lane of ft
    u8 funct = 0;  // bits 5..0
    u8 index = 0;  // fd * 4 + (funct & 3): the special-table index (meaningful when funct >= 0x3C)
};

struct LowerInsn {
    LowerOp op = LowerOp::Unknown;
    u8 opcode = 0; // bits 31..25
    u8 dest = 0;   // bits 24..21
    u8 it = 0;     // bits 20..16 (vf ft / vi it; vi uses the low 4 bits)
    u8 is = 0;     // bits 15..11 (vf fs / vi is)
    u8 id = 0;     // bits 10..6
    u8 funct = 0;  // bits 5..0
    u8 index = 0;  // id * 4 + (funct & 3): special-table index of opcode 0x40 (meaningful when funct >= 0x3C)
    u8 fsf = 0;    // bits 22..21: lane of fs for DIV/RSQRT/MTIR/EFU
    u8 ftf = 0;    // bits 24..23: lane of ft for DIV/RSQRT/SQRT
    s8 imm5 = 0;   // IADDI: sign-extended id field
    s16 imm11 = 0; // bits 10..0 sign-extended: load/store offset (qwords), branch offset (pairs)
    u16 imm12 = 0; // FS*: ((w >> 10) & 0x800) | (w & 0x7FF)
    u16 imm15 = 0; // IADDIU/ISUBIU: ((w >> 10) & 0x7800) | (w & 0x7FF)
    u32 imm24 = 0; // FC*: w & 0xFFFFFF
    u32 raw = 0;   // the whole lower word (= the LOI immediate when op == LOI)
};

struct DecodedPair {
    u32 lo = kLowerNopWord;
    u32 hi = kUpperNopWord;
    UpperInsn upper{};
    LowerInsn lower{};
    bool i = false, e = false, m = false, d = false, t = false;
};

UpperInsn decode_upper(u32 hi) noexcept;
LowerInsn decode_lower(u32 lo, bool i_flag) noexcept;
// A dump/micro-memory unit is little-endian: bytes 0..3 = lower word, bytes 4..7 = upper word.
DecodedPair decode_pair(u32 lo, u32 hi) noexcept;

// Mnemonic strings exactly as vu1_decode.py prints them ("ADDbc", "MULq", "NOP", "LOI", "UNKNOWN", ...).
std::string_view mnemonic(UpperOp op) noexcept;
std::string_view mnemonic(LowerOp op) noexcept;

// The instruction set of the 114 programs (docs/ANALYSIS/09_vu1_micro_census.md §4 (b): 43 upper, 45 lower). The
// interpreter executes exactly this set and traps on every other encoding, defined or not.
bool in_census(UpperOp op) noexcept;
bool in_census(LowerOp op) noexcept;

// Branch classification of the lower op (LOI is never a branch).
bool is_branch(LowerOp op) noexcept;          // B BAL JR JALR IB*
bool is_jump_register(LowerOp op) noexcept;   // JR JALR
bool is_unconditional(LowerOp op) noexcept;   // B BAL (relative)
bool links(LowerOp op) noexcept;              // BAL JALR
// pc + 8 + imm11 * 8, wrapped into micro memory (pc is the byte address of the branch pair).
inline u32 branch_target(const LowerInsn& l, u32 pc) noexcept {
    return (pc + 8u + static_cast<u32>(static_cast<s32>(l.imm11)) * 8u) & kMicroMask;
}

} // namespace p3fes::vu1
