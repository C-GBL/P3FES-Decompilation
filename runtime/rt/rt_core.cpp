// rt adapter: the out-of-line part of the integer core -- COP0 condition, MULT/DIV (HI/LO pipe 0)
// and COP0 (recomp/include/p3fes_recomp_rt.h "Integer core", "COP0").
//
// The ALU, shifts, immediates, branch conditions, link writes and HI/LO moves are defined inline for
// every translation unit in recomp/include/p3fes_recomp_rt_inline.h (performance pass); they are not
// repeated here. Every rule comes from runtime/include/p3fes/ee/core.h, ee/hilo.h (MULT/DIV and HI/LO)
// and ee/cop0.h (Status, ERET, CPCOND0); this file only moves operands in and results out. Writes to
// $zero are dropped by core::set_gpr64.
#include "rt_internal.h"

#include "p3fes/ee/cop0.h"
#include "p3fes/ee/hilo.h"

namespace p3fes::rt {

namespace hl = ::p3fes::ee;  // hilo.h lives directly in p3fes::ee
namespace cop0 = ::p3fes::ee::cop0;

// BC0F/BC0T: CPCOND0 from the DMAC's D_PCR / D_STAT, read through the bus (their owner is the
// kernel HLE's DMAC model, ADR-0013 §3). No check point here: every BC0F wait in the binary is a
// loop whose back-edge is one.
bool cop0_cond(const EEContext&) {
    hle::HwBus& bus = detail::hk().bus();
    const u32 pcr = bus.read32(cop0::kDmacPcr);  // sequenced: bus accesses happen in a fixed order
    const u32 stat = bus.read32(cop0::kDmacStat);
    return cop0::cpcond0(pcr, stat);
}

// ---------------------------------------------------------------------------------------------
// HI/LO pipe 0 (pipe 1 is in rt_mmi.cpp). The EE's three-operand MULT/MULTU also write rd <- LO.

void mult(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::mult(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo(ctx));
}
void multu(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::multu(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo(ctx));
}
void div(EEContext& ctx, Reg rs, Reg rt) { hl::div(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt)); }
void divu(EEContext& ctx, Reg rs, Reg rt) { hl::divu(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt)); }

// ---------------------------------------------------------------------------------------------
// COP0.

// MFC0 moves a 32-bit register: sign-extended into the GPR like every MIPS word move.
void mfc0(EEContext& ctx, Reg rt, Reg rd) { core::set_gpr64(ctx, rt, core::sext32(cop0::mfc0(ctx, rd))); }
void mtc0(EEContext& ctx, Reg rt, Reg rd) { cop0::mtc0(ctx, rd, core::gpr32(ctx, rt)); }
// SYNC.L / SYNC.P and CACHE: no-ops (host memory is coherent; no cache model).
void sync(EEContext&, unsigned) {}
void cache(EEContext&, unsigned, Reg, std::int32_t) {}
void ei(EEContext& ctx) { cop0::ei(ctx); }
void di(EEContext& ctx) { cop0::di(ctx); }
// ERET: Status.ERL/EXL as on hardware; the resume address is not used (the generated code returns
// to its host caller right after this call).
void eret(EEContext& ctx, std::uint32_t) { (void)cop0::eret(ctx); }

} // namespace p3fes::rt
