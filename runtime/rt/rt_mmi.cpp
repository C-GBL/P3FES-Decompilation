// rt adapter: MMI (recomp/include/p3fes_recomp_rt.h "MMI", except LQ/SQ which are in rt_mem.cpp):
// the 128-bit lane operations over runtime/include/p3fes/ee/mmi.h (SSE2 or scalar path, selected by
// P3FES_EE_MMI_USE_SSE2), HI1/LO1 and the second-pipe multiply/divide over ee/hilo.h, and the SA
// register. MMI results are whole quadwords (core::set_gpr128); scalar results use set_gpr64.
#include "rt_internal.h"

#include "p3fes/ee/hilo.h"
#include "p3fes/ee/mmi.h"

namespace p3fes::rt {

namespace core = ::p3fes::ee::core;
namespace hl = ::p3fes::ee;
namespace mmi = ::p3fes::ee::mmi;

// ---------------------------------------------------------------------------------------------
// Lane operations.

#define P3FES_RT_MMI3(name)                                                                       \
    void name(EEContext& ctx, Reg rd, Reg rs, Reg rt) {                                           \
        u128 d;                                                                                   \
        mmi::name(d, ctx.gpr[rs], ctx.gpr[rt]);                                                   \
        core::set_gpr128(ctx, rd, d);                                                             \
    }
P3FES_RT_MMI3(paddh)
P3FES_RT_MMI3(paddub)
P3FES_RT_MMI3(padduw)
P3FES_RT_MMI3(paddw)
P3FES_RT_MMI3(pand)
P3FES_RT_MMI3(pcgth)
P3FES_RT_MMI3(pcpyld)
P3FES_RT_MMI3(pcpyud)
P3FES_RT_MMI3(pextlb)
P3FES_RT_MMI3(pextlh)
P3FES_RT_MMI3(pextlw)
P3FES_RT_MMI3(pextub)
P3FES_RT_MMI3(pextuw)
P3FES_RT_MMI3(pmaxh)
P3FES_RT_MMI3(pminh)
P3FES_RT_MMI3(pnor)
P3FES_RT_MMI3(por)
P3FES_RT_MMI3(ppacb)
P3FES_RT_MMI3(ppach)
P3FES_RT_MMI3(ppacw)
P3FES_RT_MMI3(psubb)
P3FES_RT_MMI3(psubw)
P3FES_RT_MMI3(pxor)
#undef P3FES_RT_MMI3

#define P3FES_RT_MMI2(name)                                                                       \
    void name(EEContext& ctx, Reg rd, Reg rt) {                                                   \
        u128 d;                                                                                   \
        mmi::name(d, ctx.gpr[rt]);                                                                \
        core::set_gpr128(ctx, rd, d);                                                             \
    }
P3FES_RT_MMI2(pcpyh)
P3FES_RT_MMI2(pexew)
P3FES_RT_MMI2(prot3w)
#undef P3FES_RT_MMI2

#define P3FES_RT_MMI_SHIFT(name)                                                                  \
    void name(EEContext& ctx, Reg rd, Reg rt, unsigned sa) {                                      \
        u128 d;                                                                                   \
        mmi::name(d, ctx.gpr[rt], sa);                                                            \
        core::set_gpr128(ctx, rd, d);                                                             \
    }
P3FES_RT_MMI_SHIFT(psllh)
P3FES_RT_MMI_SHIFT(psrah)
P3FES_RT_MMI_SHIFT(psraw)
P3FES_RT_MMI_SHIFT(psrlh)
#undef P3FES_RT_MMI_SHIFT

// QFSRV uses the SA register (hilo.h holds it in hardware bit units).
void qfsrv(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    u128 d;
    mmi::qfsrv(ctx, d, ctx.gpr[rs], ctx.gpr[rt]);
    core::set_gpr128(ctx, rd, d);
}

// PHMADH writes HI/LO and rd; with rd = 0 only the HI/LO write remains.
void phmadh(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    u128 d;
    mmi::phmadh(ctx, d, ctx.gpr[rs], ctx.gpr[rt]);
    core::set_gpr128(ctx, rd, d);
}

void pmfhl(EEContext& ctx, Reg rd, unsigned fmt) {
    u128 d = ctx.gpr[rd];
    mmi::pmfhl(ctx, d, fmt);
    core::set_gpr128(ctx, rd, d);
}

// ---------------------------------------------------------------------------------------------
// Pipe 1 (HI1/LO1) and the three-operand MADD/MADDU forms (rd <- LO of the pipe).

void div1(EEContext& ctx, Reg rs, Reg rt) { hl::div1(ctx, core::gpr32(ctx, rs), core::gpr32(ctx, rt)); }
void madd(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::madd(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo(ctx));
}
void maddu(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::maddu(ctx, hl::kPipe0, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo(ctx));
}
void maddu1(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::maddu1(ctx, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo1(ctx));
}
void mult1(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::mult1(ctx, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo1(ctx));
}
void multu1(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    hl::multu1(ctx, core::gpr32(ctx, rs), core::gpr32(ctx, rt));
    core::set_gpr64(ctx, rd, hl::mflo1(ctx));
}
void mfhi1(EEContext& ctx, Reg rd) { core::set_gpr64(ctx, rd, hl::mfhi1(ctx)); }
void mflo1(EEContext& ctx, Reg rd) { core::set_gpr64(ctx, rd, hl::mflo1(ctx)); }
void mthi1(EEContext& ctx, Reg rs) { hl::mthi1(ctx, core::gpr64(ctx, rs)); }
void mtlo1(EEContext& ctx, Reg rs) { hl::mtlo1(ctx, core::gpr64(ctx, rs)); }

// ---------------------------------------------------------------------------------------------
// SA register.

void mfsa(EEContext& ctx, Reg rd) { core::set_gpr64(ctx, rd, hl::mfsa(ctx)); }
void mtsa(EEContext& ctx, Reg rs) { hl::mtsa(ctx, core::gpr32(ctx, rs)); }
void mtsab(EEContext& ctx, Reg rs, std::int32_t imm) { hl::mtsab(ctx, core::gpr32(ctx, rs), static_cast<u32>(imm)); }
void mtsah(EEContext& ctx, Reg rs, std::int32_t imm) { hl::mtsah(ctx, core::gpr32(ctx, rs), static_cast<u32>(imm)); }

} // namespace p3fes::rt
