// R5900 COP0 semantics the recompiled code reaches: MFC0/MTC0 register storage, EI/DI (Status.EIE), ERET
// (Status.ERL/EXL), and the CPCOND0 signal tested by BC0F. Written for p3fes-port from the EE Core User's
// Manual (COP0 chapter) and the EE User's Manual (DMAC D_PCR / D_STAT); the EI/DI/ERET bit rules agree with
// snuri00/ps2-web-recomp @ c0f476e runtime/src/kernel.cpp (MIT, see THIRD_PARTY.md), which instead models
// CPCOND0 as constantly true.
//
// What the binary uses (generated code census, docs/ANALYSIS/08): MFC0 of Status (99 sites: the DI/EI retry
// idiom and interrupt-state save), Cause, EPC, BadVAddr, $23 and TagLo; MTC0 of Status, EPC, ErrorEPC and
// $6; EI/DI 167; BC0F 201 (DMA completion waits); ERET 6 (exception handlers the HLE never enters); SYNC and
// CACHE are no-ops on the host (coherent memory). Count ($9) is never read or written, so it is plain
// storage here (it does not tick).
//
// Ownership: the registers live in EEContext::cop0; the kernel HLE reads Status.EIE to decide whether a check
// point may deliver an interrupt (ADR-0013 §2) and owns the D_PCR/D_STAT registers that CPCOND0 is computed
// from (the adapter reads them through the HwBus).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::ee::cop0 {

inline constexpr unsigned kBadVAddr = 8, kCount = 9, kStatus = 12, kCause = 13, kEpc = 14, kPrid = 15,
                          kTagLo = 28, kErrorEpc = 30;

// Status bits. (manual)
inline constexpr u32 kStatusIe = 1u << 0;
inline constexpr u32 kStatusExl = 1u << 1;
inline constexpr u32 kStatusErl = 1u << 2;
inline constexpr u32 kStatusEie = 1u << 16;  // master interrupt enable toggled by EI / DI
inline constexpr u32 kStatusEdi = 1u << 17;

// MFC0 / MTC0: plain register storage (see the header note on Count). (manual layout)
inline u32 mfc0(const EEContext& c, unsigned reg) noexcept { return c.cop0[reg & 31u]; }
inline void mtc0(EEContext& c, unsigned reg, u32 value) noexcept { c.cop0[reg & 31u] = value; }

// EI sets Status.EIE, DI clears it. On hardware DI/EI take effect in kernel mode or with Status.EDI = 1; the
// privilege mode is not modelled (the game's DI() idiom re-reads Status until EIE is clear, which this
// satisfies at once). (manual; mode check: not modelled)
inline void ei(EEContext& c) noexcept { c.cop0[kStatus] |= kStatusEie; }
inline void di(EEContext& c) noexcept { c.cop0[kStatus] &= ~kStatusEie; }
inline bool interrupts_enabled(const EEContext& c) noexcept { return (c.cop0[kStatus] & kStatusEie) != 0; }

// ERET: clears Status.ERL if set (return to ErrorEPC), otherwise Status.EXL (return to EPC). Returns the
// address hardware would resume at; recompiled code returns to its host caller instead. (manual)
inline u32 eret(EEContext& c) noexcept {
    u32& status = c.cop0[kStatus];
    if (status & kStatusErl) {
        status &= ~kStatusErl;
        return c.cop0[kErrorEpc];
    }
    status &= ~kStatusExl;
    return c.cop0[kEpc];
}

// CPCOND0 (BC0F/BC0T): asserted when every DMAC channel selected in D_PCR.CPC[9:0] has its D_STAT.CIS bit
// set, i.e. (~CPC | CIS) over the ten channels is all ones. With no channel selected it is asserted.
// (manual: EE User's Manual, DMAC "D_PCR" CPC field)
inline constexpr u32 kDmacPcr = 0x1000E020u;   // physical address of D_PCR
inline constexpr u32 kDmacStat = 0x1000E010u;  // physical address of D_STAT
inline constexpr bool cpcond0(u32 d_pcr, u32 d_stat) noexcept {
    return ((~d_pcr | d_stat) & 0x3FFu) == 0x3FFu;
}

} // namespace p3fes::ee::cop0
