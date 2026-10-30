// VU1 micro-instruction decoder. Tables mirror tools/ours/vu1/vu1_decode.py (_UPPER_FUNCT, _UPPER_SPECIAL,
// _LOWER_OPCODE, _LOWER_INT, _LOWER_SPECIAL) entry by entry; field layout cross-checked against
// snuri00/ps2-web-recomp @ c0f476e, runtime/src/vu_micro.cpp (MIT, see runtime/include/p3fes/vu1/THIRD_PARTY.md).
#include "p3fes/vu1/vu1_decode.h"

#include <array>
#include <cstddef>

namespace p3fes::vu1 {
namespace {

using U = UpperOp;
using L = LowerOp;

constexpr std::array<UpperOp, 0x3C> make_upper_funct() {
    std::array<UpperOp, 0x3C> t{};
    for (auto& e : t) e = U::Unknown;
    const UpperOp bc[7] = {U::ADDbc, U::SUBbc, U::MADDbc, U::MSUBbc, U::MAXbc, U::MINIbc, U::MULbc};
    for (unsigned g = 0; g < 7; ++g)
        for (unsigned k = 0; k < 4; ++k) t[g * 4 + k] = bc[g];
    const UpperOp rest[0x14] = {U::MULq, U::MAXi, U::MULi,  U::MINIi, U::ADDq, U::MADDq, U::ADDi,
                                U::MADDi, U::SUBq, U::MSUBq, U::SUBi, U::MSUBi, U::ADD,  U::MADD,
                                U::MUL,  U::MAX,  U::SUB,   U::MSUB, U::OPMSUB, U::MINI};
    for (unsigned k = 0; k < 0x14; ++k) t[0x1C + k] = rest[k];
    return t; // 0x30..0x3B stay Unknown
}

constexpr std::array<UpperOp, 128> make_upper_special() {
    std::array<UpperOp, 128> t{};
    for (auto& e : t) e = U::Unknown;
    const UpperOp bc[4] = {U::ADDAbc, U::SUBAbc, U::MADDAbc, U::MSUBAbc};
    for (unsigned g = 0; g < 4; ++g)
        for (unsigned k = 0; k < 4; ++k) t[g * 4 + k] = bc[g];
    const UpperOp conv[8] = {U::ITOF0, U::ITOF4, U::ITOF12, U::ITOF15, U::FTOI0, U::FTOI4, U::FTOI12, U::FTOI15};
    for (unsigned k = 0; k < 8; ++k) t[0x10 + k] = conv[k];
    for (unsigned k = 0; k < 4; ++k) t[0x18 + k] = U::MULAbc;
    t[0x1C] = U::MULAq;  t[0x1D] = U::ABS;    t[0x1E] = U::MULAi;  t[0x1F] = U::CLIP;
    t[0x20] = U::ADDAq;  t[0x21] = U::MADDAq; t[0x22] = U::ADDAi;  t[0x23] = U::MADDAi;
    t[0x24] = U::SUBAq;  t[0x25] = U::MSUBAq; t[0x26] = U::SUBAi;  t[0x27] = U::MSUBAi;
    t[0x28] = U::ADDA;   t[0x29] = U::MADDA;  t[0x2A] = U::MULA;   // 0x2B undefined
    t[0x2C] = U::SUBA;   t[0x2D] = U::MSUBA;  t[0x2E] = U::OPMULA; t[0x2F] = U::NOP;
    return t; // 0x30.. undefined
}

constexpr std::array<LowerOp, 128> make_lower_opcode() {
    std::array<LowerOp, 128> t{};
    for (auto& e : t) e = L::Unknown;
    t[0x00] = L::LQ;    t[0x01] = L::SQ;    t[0x04] = L::ILW;   t[0x05] = L::ISW;
    t[0x08] = L::IADDIU; t[0x09] = L::ISUBIU;
    t[0x10] = L::FCEQ;  t[0x11] = L::FCSET; t[0x12] = L::FCAND; t[0x13] = L::FCOR;
    t[0x14] = L::FSEQ;  t[0x15] = L::FSSET; t[0x16] = L::FSAND; t[0x17] = L::FSOR;
    t[0x18] = L::FMEQ;  t[0x1A] = L::FMAND; t[0x1B] = L::FMOR;  t[0x1C] = L::FCGET;
    t[0x20] = L::B;     t[0x21] = L::BAL;   t[0x24] = L::JR;    t[0x25] = L::JALR;
    t[0x28] = L::IBEQ;  t[0x29] = L::IBNE;
    t[0x2C] = L::IBLTZ; t[0x2D] = L::IBGTZ; t[0x2E] = L::IBLEZ; t[0x2F] = L::IBGEZ;
    return t; // 0x40 is decoded separately
}

constexpr std::array<LowerOp, 0x3C> make_lower_int() {
    std::array<LowerOp, 0x3C> t{};
    for (auto& e : t) e = L::Unknown;
    t[0x30] = L::IADD; t[0x31] = L::ISUB; t[0x32] = L::IADDI; t[0x34] = L::IAND; t[0x35] = L::IOR;
    return t;
}

constexpr std::array<LowerOp, 128> make_lower_special() {
    std::array<LowerOp, 128> t{};
    for (auto& e : t) e = L::Unknown;
    t[0x30] = L::MOVE;  t[0x31] = L::MR32;
    t[0x34] = L::LQI;   t[0x35] = L::SQI;   t[0x36] = L::LQD;   t[0x37] = L::SQD;
    t[0x38] = L::DIV;   t[0x39] = L::SQRT;  t[0x3A] = L::RSQRT; t[0x3B] = L::WAITQ;
    t[0x3C] = L::MTIR;  t[0x3D] = L::MFIR;  t[0x3E] = L::ILWR;  t[0x3F] = L::ISWR;
    t[0x40] = L::RNEXT; t[0x41] = L::RGET;  t[0x42] = L::RINIT; t[0x43] = L::RXOR;
    t[0x64] = L::MFP;
    t[0x68] = L::XTOP;  t[0x69] = L::XITOP; t[0x6C] = L::XGKICK;
    t[0x70] = L::ESADD; t[0x71] = L::ERSADD; t[0x72] = L::ELENG; t[0x73] = L::ERLENG;
    t[0x74] = L::EATANxy; t[0x75] = L::EATANxz; t[0x76] = L::ESUM;
    t[0x78] = L::ESQRT; t[0x79] = L::ERSQRT; t[0x7A] = L::ERCPR; t[0x7B] = L::WAITP;
    t[0x7C] = L::ESIN;  t[0x7D] = L::EATAN; t[0x7E] = L::EEXP;
    return t;
}

constexpr auto kUpperFunct = make_upper_funct();
constexpr auto kUpperSpecial = make_upper_special();
constexpr auto kLowerOpcode = make_lower_opcode();
constexpr auto kLowerInt = make_lower_int();
constexpr auto kLowerSpecial = make_lower_special();

constexpr std::array<std::string_view, static_cast<std::size_t>(UpperOp::Count)> kUpperNames = {
    "UNKNOWN",
    "ADDbc", "SUBbc", "MADDbc", "MSUBbc", "MAXbc", "MINIbc", "MULbc",
    "MULq", "MAXi", "MULi", "MINIi", "ADDq", "MADDq", "ADDi", "MADDi", "SUBq", "MSUBq", "SUBi", "MSUBi",
    "ADD", "MADD", "MUL", "MAX", "SUB", "MSUB", "OPMSUB", "MINI",
    "ADDAbc", "SUBAbc", "MADDAbc", "MSUBAbc",
    "ITOF0", "ITOF4", "ITOF12", "ITOF15", "FTOI0", "FTOI4", "FTOI12", "FTOI15",
    "MULAbc", "MULAq", "ABS", "MULAi", "CLIP",
    "ADDAq", "MADDAq", "ADDAi", "MADDAi", "SUBAq", "MSUBAq", "SUBAi", "MSUBAi",
    "ADDA", "MADDA", "MULA", "SUBA", "MSUBA", "OPMULA", "NOP",
};

constexpr std::array<std::string_view, static_cast<std::size_t>(LowerOp::Count)> kLowerNames = {
    "UNKNOWN", "NOP", "LOI",
    "LQ", "SQ", "ILW", "ISW", "IADDIU", "ISUBIU",
    "FCEQ", "FCSET", "FCAND", "FCOR", "FSEQ", "FSSET", "FSAND", "FSOR", "FMEQ", "FMAND", "FMOR", "FCGET",
    "B", "BAL", "JR", "JALR", "IBEQ", "IBNE", "IBLTZ", "IBGTZ", "IBLEZ", "IBGEZ",
    "IADD", "ISUB", "IADDI", "IAND", "IOR",
    "MOVE", "MR32", "LQI", "SQI", "LQD", "SQD", "DIV", "SQRT", "RSQRT", "WAITQ", "MTIR", "MFIR", "ILWR", "ISWR",
    "RNEXT", "RGET", "RINIT", "RXOR", "MFP", "XTOP", "XITOP", "XGKICK",
    "ESADD", "ERSADD", "ELENG", "ERLENG", "EATANxy", "EATANxz", "ESUM", "ESQRT", "ERSQRT", "ERCPR", "WAITP",
    "ESIN", "EATAN", "EEXP",
};

// docs/ANALYSIS/09_vu1_micro_census.md §4 (b) / symbols/vu1_micro_census.json aggregate.upper / .lower.
constexpr std::array<bool, static_cast<std::size_t>(UpperOp::Count)> make_upper_census() {
    std::array<bool, static_cast<std::size_t>(UpperOp::Count)> t{};
    const UpperOp ops[] = {
        U::NOP,    U::MADDbc, U::ADDbc, U::MADDAbc, U::MULAbc, U::MUL,    U::MULq,   U::ADDAbc, U::SUB,
        U::SUBbc,  U::MULbc,  U::MSUBbc, U::CLIP,   U::MAX,    U::ITOF0,  U::FTOI0,  U::FTOI4,  U::ADDA,
        U::MINIi,  U::ADD,    U::MAXbc, U::MADDq,   U::MINI,   U::MULi,   U::OPMULA, U::OPMSUB, U::SUBq,
        U::MSUB,   U::MADD,   U::SUBi,  U::MSUBAbc, U::MULAi,  U::ADDi,   U::MULA,   U::MINIbc, U::ITOF4,
        U::SUBAbc, U::MSUBi,  U::ADDAi, U::MADDi,   U::ADDq,   U::MULAq,  U::MSUBq,
    };
    static_assert(sizeof(ops) / sizeof(ops[0]) == 43, "09 §4: 43 upper mnemonics");
    for (const UpperOp op : ops) t[static_cast<std::size_t>(op)] = true;
    return t;
}

constexpr std::array<bool, static_cast<std::size_t>(LowerOp::Count)> make_lower_census() {
    std::array<bool, static_cast<std::size_t>(LowerOp::Count)> t{};
    const LowerOp ops[] = {
        L::LQ,    L::NOP,   L::IADDIU, L::SQ,    L::SQI,   L::IBEQ,   L::IBNE,  L::IADD,  L::LQI,
        L::DIV,   L::B,     L::FCAND,  L::MOVE,  L::FMAND, L::ILW,    L::MR32,  L::IAND,  L::IOR,
        L::ISUBIU, L::LOI,  L::XTOP,   L::ISW,   L::FCOR,  L::RSQRT,  L::MTIR,  L::LQD,   L::MFIR,
        L::XGKICK, L::FCGET, L::ISUB,  L::XITOP, L::BAL,   L::WAITQ,  L::IBLTZ, L::IBGEZ, L::JR,
        L::SQD,   L::IBLEZ, L::FCSET,  L::ERCPR, L::ILWR,  L::MFP,    L::IBGTZ, L::IADDI, L::ISWR,
    };
    static_assert(sizeof(ops) / sizeof(ops[0]) == 45, "09 §4: 45 lower mnemonics");
    for (const LowerOp op : ops) t[static_cast<std::size_t>(op)] = true;
    return t;
}

constexpr auto kUpperCensus = make_upper_census();
constexpr auto kLowerCensus = make_lower_census();

constexpr s32 sext(u32 value, unsigned bits) noexcept {
    const u32 m = 1u << (bits - 1u);
    value &= (1u << bits) - 1u;
    return static_cast<s32>((value ^ m) - m);
}

} // namespace

UpperInsn decode_upper(u32 hi) noexcept {
    UpperInsn u;
    u.dest = static_cast<u8>((hi >> 21) & 0xFu);
    u.ft = static_cast<u8>((hi >> 16) & 0x1Fu);
    u.fs = static_cast<u8>((hi >> 11) & 0x1Fu);
    u.fd = static_cast<u8>((hi >> 6) & 0x1Fu);
    u.funct = static_cast<u8>(hi & 0x3Fu);
    u.bc = static_cast<u8>(hi & 3u);
    u.index = static_cast<u8>(u.fd * 4u + (u.funct & 3u));
    u.op = u.funct < 0x3C ? kUpperFunct[u.funct] : kUpperSpecial[u.index];
    return u;
}

LowerInsn decode_lower(u32 lo, bool i_flag) noexcept {
    LowerInsn l;
    l.raw = lo;
    l.opcode = static_cast<u8>(lo >> 25);
    l.dest = static_cast<u8>((lo >> 21) & 0xFu);
    l.it = static_cast<u8>((lo >> 16) & 0x1Fu);
    l.is = static_cast<u8>((lo >> 11) & 0x1Fu);
    l.id = static_cast<u8>((lo >> 6) & 0x1Fu);
    l.funct = static_cast<u8>(lo & 0x3Fu);
    l.index = static_cast<u8>(l.id * 4u + (l.funct & 3u));
    l.fsf = static_cast<u8>((lo >> 21) & 3u);
    l.ftf = static_cast<u8>((lo >> 23) & 3u);
    l.imm5 = static_cast<s8>(sext(l.id, 5));
    l.imm11 = static_cast<s16>(sext(lo & 0x7FFu, 11));
    l.imm12 = static_cast<u16>(((lo >> 10) & 0x800u) | (lo & 0x7FFu));
    l.imm15 = static_cast<u16>(((lo >> 10) & 0x7800u) | (lo & 0x7FFu));
    l.imm24 = lo & 0xFFFFFFu;
    if (i_flag) {
        l.op = L::LOI;
    } else if (lo == kLowerNopWord) {
        l.op = L::NOP;
    } else if (l.opcode == 0x40) {
        l.op = l.funct < 0x3C ? kLowerInt[l.funct] : kLowerSpecial[l.index];
    } else {
        l.op = kLowerOpcode[l.opcode];
    }
    return l;
}

DecodedPair decode_pair(u32 lo, u32 hi) noexcept {
    DecodedPair d;
    d.lo = lo;
    d.hi = hi;
    d.i = (hi & kFlagI) != 0;
    d.e = (hi & kFlagE) != 0;
    d.m = (hi & kFlagM) != 0;
    d.d = (hi & kFlagD) != 0;
    d.t = (hi & kFlagT) != 0;
    d.upper = decode_upper(hi);
    d.lower = decode_lower(lo, d.i);
    return d;
}

std::string_view mnemonic(UpperOp op) noexcept {
    const auto k = static_cast<std::size_t>(op);
    return k < kUpperNames.size() ? kUpperNames[k] : "UNKNOWN";
}

std::string_view mnemonic(LowerOp op) noexcept {
    const auto k = static_cast<std::size_t>(op);
    return k < kLowerNames.size() ? kLowerNames[k] : "UNKNOWN";
}

bool in_census(UpperOp op) noexcept {
    const auto k = static_cast<std::size_t>(op);
    return k < kUpperCensus.size() && kUpperCensus[k];
}

bool in_census(LowerOp op) noexcept {
    const auto k = static_cast<std::size_t>(op);
    return k < kLowerCensus.size() && kLowerCensus[k];
}

bool is_branch(LowerOp op) noexcept {
    switch (op) {
    case L::B: case L::BAL: case L::JR: case L::JALR:
    case L::IBEQ: case L::IBNE: case L::IBLTZ: case L::IBGTZ: case L::IBLEZ: case L::IBGEZ:
        return true;
    default:
        return false;
    }
}

bool is_jump_register(LowerOp op) noexcept { return op == L::JR || op == L::JALR; }
bool is_unconditional(LowerOp op) noexcept { return op == L::B || op == L::BAL; }
bool links(LowerOp op) noexcept { return op == L::BAL || op == L::JALR; }

} // namespace p3fes::vu1
