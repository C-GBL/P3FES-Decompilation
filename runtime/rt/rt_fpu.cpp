// rt adapter: COP1 (recomp/include/p3fes_recomp_rt.h "COP1 FPU", except LWC1/SWC1 which are in
// rt_mem.cpp). Every operation is the per-instruction form of runtime/include/p3fes/ee/fpu.h (EE
// single precision: flush-to-zero, round toward zero, +/-0x7FFFFFFF clamp, FCR31.C); FPRs stay
// u32 bit patterns and no host floating-point operation touches a register here.
#include "rt_internal.h"

#include "p3fes/ee/fpu.h"

namespace p3fes::rt {

namespace core = ::p3fes::ee::core;
namespace fpu = ::p3fes::ee::fpu;

#define P3FES_RT_F3(name)                                                                         \
    void name(EEContext& ctx, Reg fd, Reg fs, Reg ft) { fpu::name(ctx, fd, fs, ft); }
P3FES_RT_F3(add_s)
P3FES_RT_F3(sub_s)
P3FES_RT_F3(mul_s)
P3FES_RT_F3(div_s)
P3FES_RT_F3(madd_s)
P3FES_RT_F3(msub_s)
#undef P3FES_RT_F3

#define P3FES_RT_F2(name)                                                                         \
    void name(EEContext& ctx, Reg a, Reg b) { fpu::name(ctx, a, b); }
// ACC forms and compares: (fs, ft).
P3FES_RT_F2(adda_s)
P3FES_RT_F2(suba_s)
P3FES_RT_F2(mula_s)
P3FES_RT_F2(madda_s)
P3FES_RT_F2(msuba_s)
P3FES_RT_F2(c_eq_s)
P3FES_RT_F2(c_le_s)
P3FES_RT_F2(c_lt_s)
// Unary forms: (fd, fs).
P3FES_RT_F2(abs_s)
P3FES_RT_F2(mov_s)
P3FES_RT_F2(neg_s)
P3FES_RT_F2(cvt_s_w)
P3FES_RT_F2(cvt_w_s)
#undef P3FES_RT_F2

// SQRT.S fd, ft: the EE reads the ft field.
void sqrt_s(EEContext& ctx, Reg fd, Reg ft) { fpu::sqrt_s(ctx, fd, ft); }

// GPR <-> FPU moves: MFC1 sign-extends the pattern into the GPR (fpu::mfc1); MTC1/CTC1 take the
// low word of rt.
void mfc1(EEContext& ctx, Reg rt, Reg fs) { core::set_gpr64(ctx, rt, fpu::mfc1(ctx, fs)); }
void mtc1(EEContext& ctx, Reg rt, Reg fs) { fpu::mtc1(ctx, fs, core::gpr32(ctx, rt)); }
void ctc1(EEContext& ctx, Reg rt, Reg fs) { fpu::ctc1(ctx, fs, core::gpr32(ctx, rt)); }

bool cop1_cond(const EEContext& ctx) { return fpu::condition(ctx); }

} // namespace p3fes::rt
