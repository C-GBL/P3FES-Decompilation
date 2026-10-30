// R5900 integer core semantics: GPR write rules, 32/64-bit ALU, shifts, set-on-less-than, conditional
// moves, branch conditions, link values, effective addresses, load extension, natural alignment and the
// unaligned load/store merges (LWL/LWR/LDL/LDR/SWL/SWR/SDL/SDR). Written for p3fes-port from the MIPS III /
// EE Core Instruction Set Manual; the unaligned-merge formulation and the LWR partial-load rule were
// cross-checked against snuri00/ps2-web-recomp @ c0f476e runtime/include/ps2/memory.hpp (MIT, see THIRD_PARTY.md).
//
// Everything is a pure value function (no memory, no EEContext side effects except the explicit GPR writers),
// so the rt adapter (runtime/rt/) only moves operands in and results out and never re-derives a rule.
//
// Register model (ee_types.h): a GPR is 128 bits; ordinary MIPS instructions read and write the low 64 bits
// (`u64[0]`) and leave bits 64..127 untouched; MMI and LQ write the whole quadword. GPR 0 reads as zero and
// every write to it is dropped (the emitter still emits loads into $zero for their memory side effect).
//
// Provenance tags: (manual) = the instruction-set manual defines it; (EE) = the manual leaves it
// implementation-dependent and the EE behaviour is stated (hardware-unverified unless noted).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::ee::core {

// ---------------------------------------------------------------------------------------------------------
// GPR access.
// ---------------------------------------------------------------------------------------------------------
inline u64 gpr64(const EEContext& c, unsigned r) noexcept { return c.gpr[r].u64[0]; }
inline u32 gpr32(const EEContext& c, unsigned r) noexcept { return c.gpr[r].u32[0]; }
// 64-bit write: bits 64..127 unchanged; $zero dropped. (manual + ee_types.h register model)
inline void set_gpr64(EEContext& c, unsigned r, u64 v) noexcept {
    if (r != 0) c.gpr[r].u64[0] = v;
}
// 128-bit write (MMI results, LQ, QMFC2); $zero dropped. (manual)
inline void set_gpr128(EEContext& c, unsigned r, const u128& v) noexcept {
    if (r != 0) c.gpr[r] = v;
}

// 32-bit results are sign-extended into the 64-bit register. (manual)
inline constexpr u64 sext32(u32 v) noexcept { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }
inline constexpr u64 sext16(u16 v) noexcept { return static_cast<u64>(static_cast<s64>(static_cast<s16>(v))); }
inline constexpr u64 sext8(u8 v) noexcept { return static_cast<u64>(static_cast<s64>(static_cast<s8>(v))); }

// ---------------------------------------------------------------------------------------------------------
// ALU. 32-bit operations use the low word of their sources (EE: no check that the sources are sign-extended
// 32-bit values; MIPS III calls other inputs UNPREDICTABLE). ADD/ADDI/SUB raise Integer Overflow on hardware;
// a game that overflowed would crash in the kernel, so the trap is not modelled and the wrapped result is
// returned like ADDU/ADDIU/SUBU (EE: as ps2-web-recomp; hardware-unverified for the overflow case).
// ---------------------------------------------------------------------------------------------------------
inline constexpr u64 add32(u64 s, u64 t) noexcept { return sext32(static_cast<u32>(s) + static_cast<u32>(t)); }
inline constexpr u64 sub32(u64 s, u64 t) noexcept { return sext32(static_cast<u32>(s) - static_cast<u32>(t)); }
inline constexpr u64 add32i(u64 s, s32 imm) noexcept { return sext32(static_cast<u32>(s) + static_cast<u32>(imm)); }
inline constexpr u64 add64(u64 s, u64 t) noexcept { return s + t; }                                  // DADDU
inline constexpr u64 sub64(u64 s, u64 t) noexcept { return s - t; }                                  // DSUBU
inline constexpr u64 add64i(u64 s, s32 imm) noexcept { return s + static_cast<u64>(static_cast<s64>(imm)); } // DADDIU

inline constexpr u64 and64(u64 s, u64 t) noexcept { return s & t; }
inline constexpr u64 or64(u64 s, u64 t) noexcept { return s | t; }
inline constexpr u64 xor64(u64 s, u64 t) noexcept { return s ^ t; }
inline constexpr u64 nor64(u64 s, u64 t) noexcept { return ~(s | t); }
// ANDI/ORI/XORI take the zero-extended 16-bit immediate. (manual)
inline constexpr u64 andi(u64 s, u32 uimm) noexcept { return s & static_cast<u64>(uimm & 0xFFFFu); }
inline constexpr u64 ori(u64 s, u32 uimm) noexcept { return s | static_cast<u64>(uimm & 0xFFFFu); }
inline constexpr u64 xori(u64 s, u32 uimm) noexcept { return s ^ static_cast<u64>(uimm & 0xFFFFu); }
// LUI: imm << 16, sign-extended. (manual)
inline constexpr u64 lui(u32 uimm) noexcept { return sext32((uimm & 0xFFFFu) << 16); }

// Set on less than: signed / unsigned 64-bit compares; SLTIU compares against the sign-extended immediate
// as an unsigned value. (manual)
inline constexpr u64 slt(u64 s, u64 t) noexcept { return static_cast<s64>(s) < static_cast<s64>(t) ? 1u : 0u; }
inline constexpr u64 sltu(u64 s, u64 t) noexcept { return s < t ? 1u : 0u; }
inline constexpr u64 slti(u64 s, s32 imm) noexcept { return static_cast<s64>(s) < static_cast<s64>(imm) ? 1u : 0u; }
inline constexpr u64 sltiu(u64 s, s32 imm) noexcept { return s < static_cast<u64>(static_cast<s64>(imm)) ? 1u : 0u; }

// MOVN/MOVZ: move the 64-bit rs when the 64-bit rt is non-zero / zero. (manual)
inline constexpr bool movn_taken(u64 t) noexcept { return t != 0; }
inline constexpr bool movz_taken(u64 t) noexcept { return t == 0; }

// ---------------------------------------------------------------------------------------------------------
// Shifts. Word shifts use the low word of rt and sign-extend the 32-bit result; variable shifts take the
// amount from rs[4:0] (word) or rs[5:0] (doubleword); DSLL32/DSRL32/DSRA32 shift by sa + 32. (manual)
// ---------------------------------------------------------------------------------------------------------
inline constexpr u64 sll(u64 t, unsigned sa) noexcept { return sext32(static_cast<u32>(t) << (sa & 31u)); }
inline constexpr u64 srl(u64 t, unsigned sa) noexcept { return sext32(static_cast<u32>(t) >> (sa & 31u)); }
inline constexpr u64 sra(u64 t, unsigned sa) noexcept {
    return sext32(static_cast<u32>(static_cast<s32>(static_cast<u32>(t)) >> (sa & 31u)));
}
inline constexpr u64 sllv(u64 t, u64 s) noexcept { return sll(t, static_cast<unsigned>(s) & 31u); }
inline constexpr u64 srlv(u64 t, u64 s) noexcept { return srl(t, static_cast<unsigned>(s) & 31u); }
inline constexpr u64 srav(u64 t, u64 s) noexcept { return sra(t, static_cast<unsigned>(s) & 31u); }
inline constexpr u64 dsll(u64 t, unsigned sa) noexcept { return t << (sa & 63u); }
inline constexpr u64 dsrl(u64 t, unsigned sa) noexcept { return t >> (sa & 63u); }
inline constexpr u64 dsra(u64 t, unsigned sa) noexcept { return static_cast<u64>(static_cast<s64>(t) >> (sa & 63u)); }
inline constexpr u64 dsll32(u64 t, unsigned sa) noexcept { return dsll(t, (sa & 31u) + 32u); }
inline constexpr u64 dsrl32(u64 t, unsigned sa) noexcept { return dsrl(t, (sa & 31u) + 32u); }
inline constexpr u64 dsra32(u64 t, unsigned sa) noexcept { return dsra(t, (sa & 31u) + 32u); }
inline constexpr u64 dsllv(u64 t, u64 s) noexcept { return dsll(t, static_cast<unsigned>(s) & 63u); }
inline constexpr u64 dsrlv(u64 t, u64 s) noexcept { return dsrl(t, static_cast<unsigned>(s) & 63u); }

// ---------------------------------------------------------------------------------------------------------
// Branch conditions on the 64-bit register values; link value of JAL/JALR (= pc + 8, sign-extended as a
// 32-bit address). (manual)
// ---------------------------------------------------------------------------------------------------------
inline constexpr bool beq(u64 s, u64 t) noexcept { return s == t; }
inline constexpr bool bne(u64 s, u64 t) noexcept { return s != t; }
inline constexpr bool blez(u64 s) noexcept { return static_cast<s64>(s) <= 0; }
inline constexpr bool bgtz(u64 s) noexcept { return static_cast<s64>(s) > 0; }
inline constexpr bool bltz(u64 s) noexcept { return static_cast<s64>(s) < 0; }
inline constexpr bool bgez(u64 s) noexcept { return static_cast<s64>(s) >= 0; }
inline constexpr u64 link_value(u32 pc) noexcept { return sext32(pc + 8u); }

// ---------------------------------------------------------------------------------------------------------
// Memory addressing. The EE has a 32-bit address space: the effective address is the low word of
// base + sign-extended offset. Natural alignment is required for LH/LHU/SH (2), LW/LWU/SW/LWC1/SWC1 (4) and
// LD/SD (8); a misaligned access raises Address Error on hardware (the kernel's handler stops the game), so
// the adapter treats it as fatal. LQ/SQ/LQC2/SQC2 ignore the low four bits instead (mmi.h, vu0.h), and the
// unaligned forms below access the containing aligned word/doubleword. (manual)
// ---------------------------------------------------------------------------------------------------------
inline constexpr u32 effective_address(u64 base, s32 imm) noexcept {
    return static_cast<u32>(base) + static_cast<u32>(imm);
}
inline constexpr bool is_aligned(u32 vaddr, u32 size) noexcept { return (vaddr & (size - 1u)) == 0; }
inline constexpr u32 kWordMask = ~3u;
inline constexpr u32 kDwordMask = ~7u;

// Load extension. (manual)
inline constexpr u64 lb(u8 v) noexcept { return sext8(v); }
inline constexpr u64 lbu(u8 v) noexcept { return v; }
inline constexpr u64 lh(u16 v) noexcept { return sext16(v); }
inline constexpr u64 lhu(u16 v) noexcept { return v; }
inline constexpr u64 lw(u32 v) noexcept { return sext32(v); }
inline constexpr u64 lwu(u32 v) noexcept { return v; }

// ---------------------------------------------------------------------------------------------------------
// Unaligned loads/stores, little-endian. `vaddr` is the instruction's effective address; `mem` is the
// aligned word (vaddr & ~3) / doubleword (vaddr & ~7) read from memory; `rt` is the register's current
// 64-bit value. With b = the byte offset inside the aligned unit:
//   LWL: memory bytes [0, b] become the high bytes of the word; the result is sign-extended. (manual)
//   LWR: memory bytes [b, 3] become the low bytes. b == 0 loads the whole word, which is sign-extended;
//        otherwise bits 32..63 keep their old value. (manual: implementation-dependent for b != 0 —
//        "unchanged or a copy of bit 31"; EE: unchanged, as ps2-web-recomp; hardware-unverified)
//   LDL/LDR: the same on doublewords (no extension).
//   SWL/SWR/SDL/SDR: the inverse merges; the returned value is the new aligned unit to store.
// ---------------------------------------------------------------------------------------------------------
inline constexpr u64 lwl(u64 rt, u32 mem, u32 vaddr) noexcept {
    const u32 b = vaddr & 3u;
    const u32 keep = 0x00FFFFFFu >> (b * 8u);
    return sext32((static_cast<u32>(rt) & keep) | (mem << ((3u - b) * 8u)));
}
inline constexpr u64 lwr(u64 rt, u32 mem, u32 vaddr) noexcept {
    const u32 b = vaddr & 3u;
    if (b == 0) return sext32(mem);
    const u32 keep = 0xFFFFFF00u << ((3u - b) * 8u);
    const u32 lo = (static_cast<u32>(rt) & keep) | (mem >> (b * 8u));
    return (rt & 0xFFFFFFFF00000000ull) | lo;
}
inline constexpr u64 ldl(u64 rt, u64 mem, u32 vaddr) noexcept {
    const u32 b = vaddr & 7u;
    const u64 keep = 0x00FFFFFFFFFFFFFFull >> (b * 8u);
    return (rt & keep) | (mem << ((7u - b) * 8u));
}
inline constexpr u64 ldr(u64 rt, u64 mem, u32 vaddr) noexcept {
    const u32 b = vaddr & 7u;
    const u64 keep = 0xFFFFFFFFFFFFFF00ull << ((7u - b) * 8u);
    return (rt & keep) | (mem >> (b * 8u));
}
inline constexpr u32 swl(u32 mem, u64 rt, u32 vaddr) noexcept {
    const u32 b = vaddr & 3u;
    const u32 keep = 0xFFFFFF00u << (b * 8u);
    return (mem & keep) | (static_cast<u32>(rt) >> ((3u - b) * 8u));
}
inline constexpr u32 swr(u32 mem, u64 rt, u32 vaddr) noexcept {
    const u32 b = vaddr & 3u;
    const u32 keep = 0x00FFFFFFu >> ((3u - b) * 8u);
    return (mem & keep) | (static_cast<u32>(rt) << (b * 8u));
}
inline constexpr u64 sdl(u64 mem, u64 rt, u32 vaddr) noexcept {
    const u32 b = vaddr & 7u;
    const u64 keep = 0xFFFFFFFFFFFFFF00ull << (b * 8u);
    return (mem & keep) | (rt >> ((7u - b) * 8u));
}
inline constexpr u64 sdr(u64 mem, u64 rt, u32 vaddr) noexcept {
    const u32 b = vaddr & 7u;
    const u64 keep = 0x00FFFFFFFFFFFFFFull >> ((7u - b) * 8u);
    return (mem & keep) | (rt << (b * 8u));
}

} // namespace p3fes::ee::core
