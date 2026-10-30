// Aborting stand-ins for the p3fes::rt adapter API (recomp/include/p3fes_recomp_rt.h).
//
// Purpose: let generated code be *linked* for compile tests before the runtime implements the
// adapter over its semantics headers. Every function aborts after printing its name; nothing
// here models the R5900. The runtime's real adapter replaces this translation unit wholesale.
// lookup_func() is not defined here: it lives in the generated dispatch.cpp.
#include "p3fes_recomp_rt.h"

#include <cstdio>
#include <cstdlib>

namespace p3fes::rt {

namespace {
[[noreturn]] void die(const char* what) {
    std::fprintf(stderr, "p3fes rt_stubs: %s called; the adapter is not implemented\n", what);
    std::abort();
}
[[noreturn]] void die_va(const char* what, std::uint32_t va) {
    std::fprintf(stderr, "p3fes rt_stubs: %s(0x%08x)\n", what, va);
    std::abort();
}
}  // namespace

void lookup_miss(std::uint32_t va) { die_va("lookup_miss", va); }
void bad_entry(std::uint32_t fn_start, std::uint32_t entry_pc) {
    std::fprintf(stderr, "p3fes rt_stubs: bad_entry(fn 0x%08x, entry 0x%08x)\n", fn_start, entry_pc);
    std::abort();
}
void unreachable(std::uint32_t pc) { die_va("unreachable", pc); }
void missing_function(std::uint32_t va) { die_va("missing_function", va); }
void trap(EEContext&, std::uint32_t pc, Trap, std::uint32_t) { die_va("trap", pc); }
void syscall(EEContext&, std::uint32_t pc) { die_va("syscall", pc); }

// The hot subset (ALU, shifts, immediates, branch conditions, link writes, HI/LO moves, aligned RAM
// loads/stores, check_events) is inline in p3fes_recomp_rt_inline.h; only its out-of-line halves
// are stubbed here.
namespace detail {
const u64 g_zero_deadline = 0;
const u64* g_deadline = &g_zero_deadline;  // every check point takes the slow path -> die
void check_events_slow(EEContext&) { die("check_events"); }
void load_slow(EEContext&, Reg, std::uint32_t va, LoadKind) { die_va("load (lb/lbu/lh/lhu/lw/lwu/ld/lq outside RAM)", va); }
void store_slow(EEContext&, std::uint32_t va, const u128&, StoreKind) { die_va("store (sb/sh/sw/sd/sq outside RAM)", va); }
void lwc1_slow(EEContext&, Reg, std::uint32_t va) { die_va("lwc1 outside RAM", va); }
void swc1_slow(EEContext&, Reg, std::uint32_t va) { die_va("swc1 outside RAM", va); }
void lqc2_slow(EEContext&, Reg, std::uint32_t va) { die_va("lqc2 outside RAM", va); }
void sqc2_slow(EEContext&, Reg, std::uint32_t va) { die_va("sqc2 outside RAM", va); }
}  // namespace detail

bool cop1_cond(const EEContext&) { die("cop1_cond"); }
bool cop0_cond(const EEContext&) { die("cop0_cond"); }

#define P3FES_STUB3(name) void name(EEContext&, Reg, Reg, Reg) { die(#name); }
#define P3FES_STUB2(name) void name(EEContext&, Reg, Reg) { die(#name); }
#define P3FES_STUB1(name) void name(EEContext&, Reg) { die(#name); }
#define P3FES_STUB_RRI(name) void name(EEContext&, Reg, Reg, std::int32_t) { die(#name); }
#define P3FES_STUB_RRU(name) void name(EEContext&, Reg, Reg, std::uint32_t) { die(#name); }
#define P3FES_STUB_RRS(name) void name(EEContext&, Reg, Reg, unsigned) { die(#name); }

P3FES_STUB3(mult) P3FES_STUB3(multu)
P3FES_STUB2(div) P3FES_STUB2(divu)
P3FES_STUB_RRI(lwl) P3FES_STUB_RRI(lwr) P3FES_STUB_RRI(ldl) P3FES_STUB_RRI(ldr)
P3FES_STUB_RRI(swl) P3FES_STUB_RRI(swr) P3FES_STUB_RRI(sdl) P3FES_STUB_RRI(sdr)

P3FES_STUB2(mfc0) P3FES_STUB2(mtc0)
void sync(EEContext&, unsigned) { die("sync"); }
void ei(EEContext&) { die("ei"); }
void di(EEContext&) { die("di"); }
void cache(EEContext&, unsigned, Reg, std::int32_t) { die("cache"); }
void eret(EEContext&, std::uint32_t pc) { die_va("eret", pc); }

P3FES_STUB2(abs_s) P3FES_STUB3(add_s) P3FES_STUB2(adda_s) P3FES_STUB2(c_eq_s) P3FES_STUB2(c_le_s) P3FES_STUB2(c_lt_s)
P3FES_STUB2(ctc1) P3FES_STUB2(cvt_s_w) P3FES_STUB2(cvt_w_s) P3FES_STUB3(div_s) P3FES_STUB3(madd_s)
P3FES_STUB2(madda_s) P3FES_STUB2(mfc1) P3FES_STUB2(mov_s) P3FES_STUB3(msub_s) P3FES_STUB2(msuba_s) P3FES_STUB2(mtc1)
P3FES_STUB3(mul_s) P3FES_STUB2(mula_s) P3FES_STUB2(neg_s) P3FES_STUB2(sqrt_s) P3FES_STUB3(sub_s) P3FES_STUB2(suba_s)


P3FES_STUB2(div1) P3FES_STUB3(madd) P3FES_STUB3(maddu) P3FES_STUB3(maddu1) P3FES_STUB1(mfhi1)
P3FES_STUB1(mflo1) P3FES_STUB1(mfsa) P3FES_STUB1(mthi1) P3FES_STUB1(mtlo1) P3FES_STUB1(mtsa)
void mtsab(EEContext&, Reg, std::int32_t) { die("mtsab"); }
void mtsah(EEContext&, Reg, std::int32_t) { die("mtsah"); }
P3FES_STUB3(mult1) P3FES_STUB3(multu1) P3FES_STUB3(paddh) P3FES_STUB3(paddub) P3FES_STUB3(padduw) P3FES_STUB3(paddw)
P3FES_STUB3(pand) P3FES_STUB3(pcgth) P3FES_STUB2(pcpyh) P3FES_STUB3(pcpyld) P3FES_STUB3(pcpyud) P3FES_STUB2(pexew)
P3FES_STUB3(pextlb) P3FES_STUB3(pextlh) P3FES_STUB3(pextlw) P3FES_STUB3(pextub) P3FES_STUB3(pextuw) P3FES_STUB3(phmadh)
P3FES_STUB3(pmaxh)
void pmfhl(EEContext&, Reg, unsigned) { die("pmfhl"); }
P3FES_STUB3(pminh) P3FES_STUB3(pnor) P3FES_STUB3(por) P3FES_STUB3(ppacb) P3FES_STUB3(ppach) P3FES_STUB3(ppacw)
P3FES_STUB2(prot3w) P3FES_STUB_RRS(psllh) P3FES_STUB_RRS(psrah) P3FES_STUB_RRS(psraw) P3FES_STUB_RRS(psrlh)
P3FES_STUB3(psubb) P3FES_STUB3(psubw) P3FES_STUB3(pxor) P3FES_STUB3(qfsrv)

void cfc2(EEContext&, Reg, Reg, bool) { die("cfc2"); }
void ctc2(EEContext&, Reg, Reg, bool) { die("ctc2"); }

void qmfc2(EEContext&, Reg, Reg, bool) { die("qmfc2"); }
void qmtc2(EEContext&, Reg, Reg, bool) { die("qmtc2"); }


#define P3FES_STUB_V3(name) void name(EEContext&, unsigned, Reg, Reg, Reg) { die(#name); }
#define P3FES_STUB_V3BC(name) void name(EEContext&, unsigned, Reg, Reg, Reg, unsigned) { die(#name); }
#define P3FES_STUB_V2(name) void name(EEContext&, unsigned, Reg, Reg) { die(#name); }
#define P3FES_STUB_V2BC(name) void name(EEContext&, unsigned, Reg, Reg, unsigned) { die(#name); }

P3FES_STUB_V2(vabs) P3FES_STUB_V3(vadd) P3FES_STUB_V3BC(vadd_bc) P3FES_STUB_V2(vadda) P3FES_STUB_V2BC(vadda_bc)
P3FES_STUB_V2(vaddi) P3FES_STUB_V2(vftoi0) P3FES_STUB_V2(vitof0) P3FES_STUB_V3(vmadd) P3FES_STUB_V3BC(vmadd_bc)
P3FES_STUB_V2(vmadda) P3FES_STUB_V2BC(vmadda_bc) P3FES_STUB_V3(vmax) P3FES_STUB_V3(vmini) P3FES_STUB_V2(vmove)
P3FES_STUB_V3(vmsub) P3FES_STUB_V3BC(vmsub_bc) P3FES_STUB_V2(vmsuba) P3FES_STUB_V2BC(vmsuba_bc) P3FES_STUB_V3(vmul)
P3FES_STUB_V3BC(vmul_bc) P3FES_STUB_V2(vmula) P3FES_STUB_V2BC(vmula_bc) P3FES_STUB_V2(vmuli) P3FES_STUB_V2(vmulq)
void vnop(EEContext&) { die("vnop"); }
P3FES_STUB_V3(vopmsub) P3FES_STUB_V2(vopmula)
void vrsqrt(EEContext&, Reg, unsigned, Reg, unsigned) { die("vrsqrt"); }
void vsqrt(EEContext&, Reg, unsigned) { die("vsqrt"); }
P3FES_STUB_V3(vsub) P3FES_STUB_V3BC(vsub_bc)
void vwaitq(EEContext&) { die("vwaitq"); }

}  // namespace p3fes::rt
