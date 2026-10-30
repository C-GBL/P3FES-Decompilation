// rt adapter: COP2 in macro mode (recomp/include/p3fes_recomp_rt.h "COP2 transfers" and "COP2 VU0
// macro mode", except LQC2/SQC2 which are in rt_mem.cpp). Every operation is a call into
// runtime/include/p3fes/ee/vu0.h on EEContext::vu0: dest masks, broadcast / Q / I operand
// selection, vf00 read-only, the Q pipe without latency, CFC2/CTC2 register routing. The
// QMFC2/QMTC2/CFC2/CTC2 interlock bit is passed through and ignored there (no concurrent
// micro-program in macro mode).
#include "rt_internal.h"

#include "p3fes/ee/vu0.h"

namespace p3fes::rt {

namespace core = ::p3fes::ee::core;
namespace vu0 = ::p3fes::ee::vu0;

// ---------------------------------------------------------------------------------------------
// Transfers.

// CFC2 moves a 32-bit value: sign-extended into the GPR (vu0.h note on cfc2).
void cfc2(EEContext& ctx, Reg rt, Reg vi, bool) { core::set_gpr64(ctx, rt, core::sext32(vu0::cfc2(ctx.vu0, vi))); }
// CTC2 to vi28 (FBRST) also reaches the hooks: its VU1 reset / force-break bits belong to the VU1 owner
// (rt_hooks.h vu_control_write); the VU0 side keeps no FBRST state (vu0.h drops the write).
void ctc2(EEContext& ctx, Reg rt, Reg vi, bool) {
    const u32 value = core::gpr32(ctx, rt);
    vu0::ctc2(ctx.vu0, vi, value);
    if (vi == vu0::kCtrlFbrst) detail::hk().vu_control_write(ctx, vi, value);
}
void qmfc2(EEContext& ctx, Reg rt, Reg vf, bool interlock) { core::set_gpr128(ctx, rt, vu0::qmfc2(ctx.vu0, vf, interlock)); }
void qmtc2(EEContext& ctx, Reg rt, Reg vf, bool interlock) { vu0::qmtc2(ctx.vu0, vf, ctx.gpr[rt], interlock); }

// ---------------------------------------------------------------------------------------------
// Vector ALU.

#define P3FES_RT_V3(rtname, op)                                                                   \
    void rtname(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft) { vu0::op(ctx.vu0, dest, fd, fs, ft); }
#define P3FES_RT_V3BC(rtname, op)                                                                 \
    void rtname(EEContext& ctx, unsigned dest, Reg fd, Reg fs, Reg ft, unsigned bc) {             \
        vu0::op(ctx.vu0, dest, fd, fs, ft, bc);                                                   \
    }
#define P3FES_RT_V2ACC(rtname, op)                                                                \
    void rtname(EEContext& ctx, unsigned dest, Reg fs, Reg ft) { vu0::op(ctx.vu0, dest, fs, ft); }
#define P3FES_RT_V2ACCBC(rtname, op)                                                              \
    void rtname(EEContext& ctx, unsigned dest, Reg fs, Reg ft, unsigned bc) { vu0::op(ctx.vu0, dest, fs, ft, bc); }

P3FES_RT_V3(vadd, add)
P3FES_RT_V3BC(vadd_bc, add_bc)
P3FES_RT_V3(vsub, sub)
P3FES_RT_V3BC(vsub_bc, sub_bc)
P3FES_RT_V3(vmul, mul)
P3FES_RT_V3BC(vmul_bc, mul_bc)
P3FES_RT_V3(vmadd, madd)
P3FES_RT_V3BC(vmadd_bc, madd_bc)
P3FES_RT_V3(vmsub, msub)
P3FES_RT_V3BC(vmsub_bc, msub_bc)
P3FES_RT_V3(vmax, max)
P3FES_RT_V3(vmini, mini)

P3FES_RT_V2ACC(vadda, adda)
P3FES_RT_V2ACCBC(vadda_bc, adda_bc)
P3FES_RT_V2ACC(vmula, mula)
P3FES_RT_V2ACCBC(vmula_bc, mula_bc)
P3FES_RT_V2ACC(vmadda, madda)
P3FES_RT_V2ACCBC(vmadda_bc, madda_bc)
P3FES_RT_V2ACC(vmsuba, msuba)
P3FES_RT_V2ACCBC(vmsuba_bc, msuba_bc)

#undef P3FES_RT_V3
#undef P3FES_RT_V3BC
#undef P3FES_RT_V2ACC
#undef P3FES_RT_V2ACCBC

// I / Q operand forms: (dest, fd, fs).
void vaddi(EEContext& ctx, unsigned dest, Reg fd, Reg fs) { vu0::add_i(ctx.vu0, dest, fd, fs); }
void vmuli(EEContext& ctx, unsigned dest, Reg fd, Reg fs) { vu0::mul_i(ctx.vu0, dest, fd, fs); }
void vmulq(EEContext& ctx, unsigned dest, Reg fd, Reg fs) { vu0::mul_q(ctx.vu0, dest, fd, fs); }

// Unary forms write the ft field: (dest, ft, fs).
void vabs(EEContext& ctx, unsigned dest, Reg ft, Reg fs) { vu0::abs(ctx.vu0, dest, ft, fs); }
void vmove(EEContext& ctx, unsigned dest, Reg ft, Reg fs) { vu0::move(ctx.vu0, dest, ft, fs); }
void vftoi0(EEContext& ctx, unsigned dest, Reg ft, Reg fs) { vu0::ftoi(ctx.vu0, dest, ft, fs, 0); }
void vitof0(EEContext& ctx, unsigned dest, Reg ft, Reg fs) { vu0::itof(ctx.vu0, dest, ft, fs, 0); }

// Outer product: the encoding fixes dest to xyz (vu0.h), so the field is not consulted.
void vopmula(EEContext& ctx, unsigned, Reg fs, Reg ft) { vu0::opmula(ctx.vu0, fs, ft); }
void vopmsub(EEContext& ctx, unsigned, Reg fd, Reg fs, Reg ft) { vu0::opmsub(ctx.vu0, fd, fs, ft); }

// Q pipe.
void vsqrt(EEContext& ctx, Reg ft, unsigned ftf) { vu0::sqrt(ctx.vu0, ft, ftf); }
void vrsqrt(EEContext& ctx, Reg fs, unsigned fsf, Reg ft, unsigned ftf) { vu0::rsqrt(ctx.vu0, fs, fsf, ft, ftf); }
void vwaitq(EEContext& ctx) { vu0::waitq(ctx.vu0); }
void vnop(EEContext& ctx) { vu0::nop(ctx.vu0); }

} // namespace p3fes::rt
