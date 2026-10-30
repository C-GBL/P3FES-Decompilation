// Emotion Engine CPU state operated on by recompiled code.
//
// Layout notes:
//  * GPRs are 128-bit (MMI). Ordinary MIPS integer ops read/write `.u64[0]`
//    and sign-extend 32-bit results into it; MMI ops touch the whole quadword.
//    r0 ($zero) is stored but must read as 0: the recompiler is expected to
//    never emit a write to gpr[0].
//  * HI/LO are 128-bit as well: MULT/DIV use the low 64 bits, the MMI
//    MULT1/DIV1/PMULT* family uses the upper 64 bits (HI1/LO1).
//  * `sa` is the Shift Amount register used by QFSRV.
//  * COP1 (FPU) is single precision only on the EE; `acc` is the MADD
//    accumulator. The EE FPU is not IEEE-754 compliant (no NaN/Inf, no
//    denormals, round-toward-zero only); the recompiler must honour this.
//  * COP2 (VU0 macro mode) state is kept here because VU0 macro instructions
//    execute in the EE pipeline. VU0 micro mode and VU1 live elsewhere.
#pragma once

#include "p3fes/ee_types.h"

namespace p3fes {

class EEMemory;

// VU0 register file as visible to COP2 macro-mode instructions
// (QMFC2/QMTC2/CFC2/CTC2 and the V* arithmetic ops).
// All floating-point state is stored as raw IEEE bit patterns (u32): the EE/VU
// datapath is defined on the bits (no NaN/Inf, flush-to-zero, RZ) and
// p3fes/ee/fpu.h + vu0.h only convert at the arithmetic boundary.
struct VU0State {
    alignas(16) u32 vf[32][4] = {{0u, 0u, 0u, 0x3F800000u}}; // vf00..vf31 (x,y,z,w); vf00 is constant (0,0,0,1.0f)
    u16 vi[16] = {};                  // vi00..vi15; vi00 is constant 0
    alignas(16) u32 acc[4] = {};      // ACC
    u32 q = 0;                        // Q (division result)
    u32 p = 0;                        // P (EFU result; VU1 only in hardware, kept for symmetry)
    u32 i = 0;                        // I (immediate)
    u32 r = 0;                        // R (random seed, 23 bits; vi20)
    u32 status = 0;                   // VU STATUS flag register (vi16)
    u32 mac = 0;                      // MAC flags (vi17)
    u32 clip = 0;                     // CLIP flags (vi18)
    u32 tpc = 0;                      // TPC (micro-program PC; vi26)
    u32 cmsar0 = 0;                   // CMSAR0 (VCALLMS start address; vi27)
};

struct alignas(16) EEContext {
    // Integer unit.
    u128 gpr[32] = {};
    u128 hi = {};
    u128 lo = {};
    u32  pc = 0;
    u32  sa = 0;

    // Virtual time (ADR-0013 §2): generated code adds each basic block's instruction count;
    // the kernel/timing HLE derives H-lines, fields and VBLANKs from it and delivers
    // interrupts at check points. Never compared against the wall clock.
    u64  cycles = 0;

    // COP1: floating point unit (raw IEEE bit patterns, see VU0State note).
    u32 fpr[32] = {};
    u32 acc = 0;
    u32 fcr0 = 0;
    u32 fcr31 = 0;

    // COP0: system control.
    u32 cop0[32] = {};

    // COP2: VU0 macro mode.
    VU0State vu0 = {};

    // Backing memory; not owned.
    EEMemory* memory = nullptr;
};

// R5900 GPR numbering for readability in recompiled output.
enum GprIndex : u8 {
    GPR_ZERO = 0, GPR_AT, GPR_V0, GPR_V1, GPR_A0, GPR_A1, GPR_A2, GPR_A3,
    GPR_T0, GPR_T1, GPR_T2, GPR_T3, GPR_T4, GPR_T5, GPR_T6, GPR_T7,
    GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7,
    GPR_T8, GPR_T9, GPR_K0, GPR_K1, GPR_GP, GPR_SP, GPR_FP, GPR_RA,
};

} // namespace p3fes
