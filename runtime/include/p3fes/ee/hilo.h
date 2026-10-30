// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/mmi.hpp (set_hilo, hilo, mult, multu,
// madd, maddu, div, divu) and recomp/codegen.cpp (mfhi/mflo/mthi/mtlo[1], mfsa/mtsa/mtsab/mtsah emit rules),
// MIT; adapted for p3fes-port (p3fes::ee namespace, EEContext/u128 instead of Cpu/Reg128, SA register held in
// hardware bit units rather than upstream's byte units, named *1 wrappers for the second pipe).
//
// The EE has two HI/LO pairs: pipe 0 (HI/LO, written by MULT/MULTU/DIV/DIVU/MADD/MADDU and the low halves of
// the PMULT*/PMADD*/PDIV* family) and pipe 1 (HI1/LO1, written by MULT1/MULTU1/DIV1/DIVU1/MADD1/MADDU1 and the
// upper halves of the parallel multiply family). `EEContext::hi`/`lo` are 128-bit: `.u64[0]` is pipe 0 and
// `.u64[1]` is pipe 1 (ee_context.h). The binary never uses DMULT/DMULTU/DDIV/DDIVU (docs/ANALYSIS/08), so no
// 64x64 multiply or 64-bit divide is modelled here.
//
// Provenance of each rule: "manual" = EE Core User's Manual / EE Core Instruction Set Manual wording that the
// upstream code reproduces; "upstream" = behaviour the hardware manual leaves undefined and upstream chose,
// kept bit-exact here and listed as hardware-unverified in tests/ee/vectors/README.md.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::ee {

inline constexpr int kPipe0 = 0; // HI / LO
inline constexpr int kPipe1 = 1; // HI1 / LO1

inline constexpr s64 sext32(u32 v) noexcept { return static_cast<s32>(v); }

// Store a 64-bit product into one pipe: LO <- sext32(low word), HI <- sext32(high word). (manual)
inline void set_hilo(EEContext& c, int pipe, u64 value) noexcept {
    c.lo.s64[pipe] = sext32(static_cast<u32>(value));
    c.hi.s64[pipe] = sext32(static_cast<u32>(value >> 32));
}

// Read {HI[31:0], LO[31:0]} of one pipe as an unsigned 64-bit accumulator (used by MADD/MADDU/PMADD*). (manual)
inline u64 hilo(const EEContext& c, int pipe) noexcept {
    return (static_cast<u64>(c.hi.u32[pipe * 2]) << 32) | c.lo.u32[pipe * 2];
}

// MULT / MULT1: signed 32x32 -> 64. (manual)
inline void mult(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    set_hilo(c, pipe, static_cast<u64>(static_cast<s64>(static_cast<s32>(s)) * static_cast<s32>(t)));
}

// MULTU / MULTU1: unsigned 32x32 -> 64. (manual)
inline void multu(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    set_hilo(c, pipe, static_cast<u64>(s) * t);
}

// MADD / MADD1: {HI,LO} += signed product. (manual)
inline void madd(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    set_hilo(c, pipe, hilo(c, pipe) + static_cast<u64>(static_cast<s64>(static_cast<s32>(s)) * static_cast<s32>(t)));
}

// MADDU / MADDU1: {HI,LO} += unsigned product. (manual)
inline void maddu(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    set_hilo(c, pipe, hilo(c, pipe) + static_cast<u64>(s) * t);
}

// DIV / DIV1: signed 32-bit divide. Divide by zero and INT32_MIN / -1 are undefined on hardware (manual);
// upstream uses the MIPS convention LO = (n < 0 ? 1 : -1), HI = n for /0 and LO = INT32_MIN, HI = 0 for the
// overflow case. (upstream, hardware-unverified)
inline void div(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    const s32 n = static_cast<s32>(s);
    const s32 m = static_cast<s32>(t);
    if (m == 0) {
        c.lo.s64[pipe] = n < 0 ? 1 : -1;
        c.hi.s64[pipe] = n;
    } else if (n == INT32_MIN && m == -1) {
        c.lo.s64[pipe] = INT32_MIN;
        c.hi.s64[pipe] = 0;
    } else {
        c.lo.s64[pipe] = n / m;
        c.hi.s64[pipe] = n % m;
    }
}

// DIVU / DIVU1: unsigned 32-bit divide; results are sign-extended into the 64-bit HI/LO. Divide by zero is
// undefined on hardware (manual); upstream yields LO = -1, HI = sext32(s). (upstream, hardware-unverified)
inline void divu(EEContext& c, int pipe, u32 s, u32 t) noexcept {
    if (t == 0) {
        c.lo.s64[pipe] = -1;
        c.hi.s64[pipe] = sext32(s);
    } else {
        c.lo.s64[pipe] = sext32(s / t);
        c.hi.s64[pipe] = sext32(s % t);
    }
}

// Named forms for the second pipe, so recompiled code reads like the disassembly.
inline void mult1(EEContext& c, u32 s, u32 t) noexcept { mult(c, kPipe1, s, t); }
inline void multu1(EEContext& c, u32 s, u32 t) noexcept { multu(c, kPipe1, s, t); }
inline void madd1(EEContext& c, u32 s, u32 t) noexcept { madd(c, kPipe1, s, t); }
inline void maddu1(EEContext& c, u32 s, u32 t) noexcept { maddu(c, kPipe1, s, t); }
inline void div1(EEContext& c, u32 s, u32 t) noexcept { div(c, kPipe1, s, t); }
inline void divu1(EEContext& c, u32 s, u32 t) noexcept { divu(c, kPipe1, s, t); }

// The three-operand forms (MULT rd, rs, rt; MADD rd, rs, rt ...) also write rd <- LO of the pipe. (manual)
inline u64 mflo(const EEContext& c) noexcept { return c.lo.u64[kPipe0]; }
inline u64 mfhi(const EEContext& c) noexcept { return c.hi.u64[kPipe0]; }
inline u64 mflo1(const EEContext& c) noexcept { return c.lo.u64[kPipe1]; }
inline u64 mfhi1(const EEContext& c) noexcept { return c.hi.u64[kPipe1]; }
inline void mtlo(EEContext& c, u64 v) noexcept { c.lo.u64[kPipe0] = v; }
inline void mthi(EEContext& c, u64 v) noexcept { c.hi.u64[kPipe0] = v; }
inline void mtlo1(EEContext& c, u64 v) noexcept { c.lo.u64[kPipe1] = v; }
inline void mthi1(EEContext& c, u64 v) noexcept { c.hi.u64[kPipe1] = v; }

// ---------------------------------------------------------------------------------------------------------
// SA (shift amount) register, consumed by QFSRV.
//
// `EEContext::sa` holds the hardware value in BITS: MTSAB sets ((rs ^ imm) & 0xF) * 8, MTSAH sets
// ((rs ^ imm) & 0x7) * 16, MTSA copies rs, MFSA reads it back (manual). Upstream stores the byte count
// instead (`c.sa = (rs ^ imm) & 15`, `c.sa = ((rs ^ imm) & 7) * 2`, `c.sa = rs & 15`); QFSRV results are
// identical, only the value observed through MFSA differs. The binary's two MFSA / one MTSA are the SDK
// exception handler's context save/restore (0x50d0ec, 0x50d1dc, 0x50d32c), so either representation is
// self-consistent there; the hardware one is kept so PCSX2 register traces (Phase 4) compare directly.
// ---------------------------------------------------------------------------------------------------------
inline u32 mfsa(const EEContext& c) noexcept { return c.sa; }
inline void mtsa(EEContext& c, u32 rs) noexcept { c.sa = rs; }
inline void mtsab(EEContext& c, u32 rs, u32 imm) noexcept { c.sa = ((rs ^ imm) & 15u) << 3; }
inline void mtsah(EEContext& c, u32 rs, u32 imm) noexcept { c.sa = ((rs ^ imm) & 7u) << 4; }

// Byte shift QFSRV applies: SA / 8, modulo one quadword. SA values that are not a multiple of 8 are
// undefined on hardware (manual); the low three bits are ignored here, matching upstream's byte model.
inline u32 sa_bytes(const EEContext& c) noexcept { return (c.sa >> 3) & 15u; }

} // namespace p3fes::ee
