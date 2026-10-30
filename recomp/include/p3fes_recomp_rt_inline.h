// p3fes::rt -- header-inline fast paths for the hot subset of the adapter API (p3fes_recomp_rt.h).
//
// p3fes_recomp_rt.h includes this file at its end, so every translation unit that sees one of these
// declarations also sees the inline definition ([dcl.inline]: an inline function is inline everywhere).
// Generated code therefore open-codes the integer ALU, shifts, immediates, branch conditions, link
// writes, HI/LO moves, the naturally aligned RAM/scratchpad loads and stores (LB..LD, LQ, SB..SD, SQ,
// LWC1/SWC1, LQC2/SQC2)
// and the check-point compare instead of calling the adapter library for each one (Phase 3
// performance pass; numbers in runtime/rt/README.md "Inline fast paths"). The semantics are untouched:
// every rule still comes from runtime/include/p3fes/ee/core.h and ee/hilo.h, and this header moves
// operands in and results out exactly as runtime/rt/rt_core.cpp and rt_mem.cpp did (ADR-0010 §2).
//
// Out of line (runtime/rt/rt_mem.cpp and rt_hooks.cpp; aborting stand-ins in recomp/rt_stubs/):
//   * rt::detail::load_slow / store_slow -- any access that is not a naturally aligned main-RAM or
//     scratchpad access: the BIOS window, the hardware-register windows (RtHooks::bus + check point),
//     unaligned (fatal) and unmapped (fatal). They take the effective address and finish the
//     instruction (register write, check point) themselves; their own return address is the call
//     site inside the generated function, which is what the fault message reports.
//   * rt::detail::check_events_slow -- the installed hooks' check point, reached when
//     ctx.cycles >= *g_deadline. set_hooks() points g_deadline at RtHooks::deadline_ptr() when the
//     hooks provide one (the kernel HLE's next event deadline) and at a zero otherwise, which makes
//     every check point take the slow path -- the behaviour before this header existed.
//   * everything else declared in p3fes_recomp_rt.h (MULT/DIV, COP0, FPU, MMI, COP2, the unaligned
//     LWL/LWR/LDL/LDR/SWL/SWR/SDL/SDR merges, the slow halves of LWC1/SWC1/LQC2/SQC2, traps and stops).
//
// Compiles under cl.exe and clang-cl at /W4 with C++20 (ADR-0003); _ReturnAddress is not needed here
// (see load_slow above). Do not include this file directly: include p3fes_recomp_rt.h.
#pragma once

#include "p3fes_recomp_rt.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/ee_memory.h"

#include <cstdint>
#include <cstring>

// The memory fast paths are force-inlined: hand-written game code (game/) calls them from very large functions where
// MSVC's heuristics otherwise left out-of-line copies on the hot path.
#if defined(_MSC_VER) && !defined(__clang__)
#define P3FES_RT_HOT __forceinline
#else
#define P3FES_RT_HOT inline __attribute__((always_inline))
#endif

namespace p3fes::rt {

namespace core = ::p3fes::ee::core;

namespace detail {

// Hot-path state and the out-of-line halves.
extern const u64* g_deadline;  // never null; *g_deadline == 0 forces the slow path on every check point
void check_events_slow(EEContext& ctx);

enum class LoadKind : unsigned { lb, lbu, lh, lhu, lw, lwu, ld, lq };
enum class StoreKind : unsigned { sb, sh, sw, sd, sq };
// `va` is the effective address (LQ/SQ: already masked to the quadword). Writes the destination GPR as
// the fast path would and runs the check point after a hardware-window access.
void load_slow(EEContext& ctx, Reg rt, std::uint32_t va, LoadKind kind);
// `v` is the whole source GPR; the stored width comes from `kind`.
void store_slow(EEContext& ctx, std::uint32_t va, const u128& v, StoreKind kind);
// LWC1/SWC1 (FPR) and LQC2/SQC2 (VU0 vf; `va` already masked to the quadword) outside RAM / the scratchpad: as
// load_slow / store_slow (the hardware windows with a check point, everything else fatal).
void lwc1_slow(EEContext& ctx, Reg ft, std::uint32_t va);
void swc1_slow(EEContext& ctx, Reg ft, std::uint32_t va);
void lqc2_slow(EEContext& ctx, Reg vf, std::uint32_t va);
void sqc2_slow(EEContext& ctx, Reg vf, std::uint32_t va);

// LQ/SQ ignore the low four bits (ee/mmi.h kQuadwordMask; rt_mem.cpp static_asserts the equality).
inline constexpr std::uint32_t kQuadwordMask = ~15u;

P3FES_RT_HOT std::uint32_t ea(const EEContext& ctx, Reg base, std::int32_t imm) noexcept {
    return core::effective_address(core::gpr64(ctx, base), imm);
}
// Host pointer for a naturally aligned access in main RAM (any mirror) or the scratchpad, else nullptr.
P3FES_RT_HOT u8* fast_ptr(const EEContext& ctx, std::uint32_t va, std::uint32_t len) noexcept {
    EEMemory* m = ctx.memory;
    return m ? m->fast_ptr(va, len) : nullptr;
}

} // namespace detail

// ---------------------------------------------------------------------------------------------
// Check point (ADR-0013 §2): one compare on the hot path.

inline void check_events(EEContext& ctx) {
    if (ctx.cycles < *detail::g_deadline) return;
    detail::check_events_slow(ctx);
}

// ---------------------------------------------------------------------------------------------
// Link writes, register reads and branch conditions.

inline void jal(EEContext& ctx, std::uint32_t pc) { core::set_gpr64(ctx, GPR_RA, core::link_value(pc)); }
inline void jalr(EEContext& ctx, Reg rd, std::uint32_t pc) { core::set_gpr64(ctx, rd, core::link_value(pc)); }

inline std::uint32_t reg32(const EEContext& ctx, Reg r) { return core::gpr32(ctx, r); }

inline bool cmp_eq(const EEContext& ctx, Reg rs, Reg rt) { return core::beq(core::gpr64(ctx, rs), core::gpr64(ctx, rt)); }
inline bool cmp_ne(const EEContext& ctx, Reg rs, Reg rt) { return core::bne(core::gpr64(ctx, rs), core::gpr64(ctx, rt)); }
inline bool cmp_lez(const EEContext& ctx, Reg rs) { return core::blez(core::gpr64(ctx, rs)); }
inline bool cmp_gtz(const EEContext& ctx, Reg rs) { return core::bgtz(core::gpr64(ctx, rs)); }
inline bool cmp_ltz(const EEContext& ctx, Reg rs) { return core::bltz(core::gpr64(ctx, rs)); }
inline bool cmp_gez(const EEContext& ctx, Reg rs) { return core::bgez(core::gpr64(ctx, rs)); }

// ---------------------------------------------------------------------------------------------
// Integer ALU, shifts and immediates (core.h rules; writes to $zero dropped by core::set_gpr64).

#define P3FES_RT_INLINE_RRR(name, expr)                                                           \
    inline void name(EEContext& ctx, Reg rd, Reg rs, Reg rt) {                                    \
        const u64 s = core::gpr64(ctx, rs);                                                       \
        const u64 t = core::gpr64(ctx, rt);                                                       \
        core::set_gpr64(ctx, rd, (expr));                                                         \
    }
P3FES_RT_INLINE_RRR(add, core::add32(s, t))
P3FES_RT_INLINE_RRR(addu, core::add32(s, t))
P3FES_RT_INLINE_RRR(sub, core::sub32(s, t))
P3FES_RT_INLINE_RRR(subu, core::sub32(s, t))
P3FES_RT_INLINE_RRR(and_, core::and64(s, t))
P3FES_RT_INLINE_RRR(or_, core::or64(s, t))
P3FES_RT_INLINE_RRR(xor_, core::xor64(s, t))
P3FES_RT_INLINE_RRR(nor, core::nor64(s, t))
P3FES_RT_INLINE_RRR(slt, core::slt(s, t))
P3FES_RT_INLINE_RRR(sltu, core::sltu(s, t))
P3FES_RT_INLINE_RRR(daddu, core::add64(s, t))
P3FES_RT_INLINE_RRR(dsubu, core::sub64(s, t))
#undef P3FES_RT_INLINE_RRR

inline void movn(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    if (core::movn_taken(core::gpr64(ctx, rt))) core::set_gpr64(ctx, rd, core::gpr64(ctx, rs));
}
inline void movz(EEContext& ctx, Reg rd, Reg rs, Reg rt) {
    if (core::movz_taken(core::gpr64(ctx, rt))) core::set_gpr64(ctx, rd, core::gpr64(ctx, rs));
}

#define P3FES_RT_INLINE_SHIFTV(name)                                                              \
    inline void name(EEContext& ctx, Reg rd, Reg rt, Reg rs) {                                    \
        core::set_gpr64(ctx, rd, core::name(core::gpr64(ctx, rt), core::gpr64(ctx, rs)));         \
    }
P3FES_RT_INLINE_SHIFTV(sllv)
P3FES_RT_INLINE_SHIFTV(srlv)
P3FES_RT_INLINE_SHIFTV(srav)
P3FES_RT_INLINE_SHIFTV(dsllv)
P3FES_RT_INLINE_SHIFTV(dsrlv)
#undef P3FES_RT_INLINE_SHIFTV

#define P3FES_RT_INLINE_SHIFTI(name)                                                              \
    inline void name(EEContext& ctx, Reg rd, Reg rt, unsigned sa) {                               \
        core::set_gpr64(ctx, rd, core::name(core::gpr64(ctx, rt), sa));                           \
    }
P3FES_RT_INLINE_SHIFTI(sll)
P3FES_RT_INLINE_SHIFTI(srl)
P3FES_RT_INLINE_SHIFTI(sra)
P3FES_RT_INLINE_SHIFTI(dsll)
P3FES_RT_INLINE_SHIFTI(dsrl)
P3FES_RT_INLINE_SHIFTI(dsra)
P3FES_RT_INLINE_SHIFTI(dsll32)
P3FES_RT_INLINE_SHIFTI(dsrl32)
P3FES_RT_INLINE_SHIFTI(dsra32)
#undef P3FES_RT_INLINE_SHIFTI

inline void addi(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm) { core::set_gpr64(ctx, rt, core::add32i(core::gpr64(ctx, rs), imm)); }
inline void addiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm) { core::set_gpr64(ctx, rt, core::add32i(core::gpr64(ctx, rs), imm)); }
inline void daddiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm) { core::set_gpr64(ctx, rt, core::add64i(core::gpr64(ctx, rs), imm)); }
inline void slti(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm) { core::set_gpr64(ctx, rt, core::slti(core::gpr64(ctx, rs), imm)); }
inline void sltiu(EEContext& ctx, Reg rt, Reg rs, std::int32_t imm) { core::set_gpr64(ctx, rt, core::sltiu(core::gpr64(ctx, rs), imm)); }
inline void andi(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm) { core::set_gpr64(ctx, rt, core::andi(core::gpr64(ctx, rs), uimm)); }
inline void ori(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm) { core::set_gpr64(ctx, rt, core::ori(core::gpr64(ctx, rs), uimm)); }
inline void xori(EEContext& ctx, Reg rt, Reg rs, std::uint32_t uimm) { core::set_gpr64(ctx, rt, core::xori(core::gpr64(ctx, rs), uimm)); }
inline void lui(EEContext& ctx, Reg rt, std::uint32_t uimm) { core::set_gpr64(ctx, rt, core::lui(uimm)); }

// HI/LO pipe 0 moves (hilo.h); MULT/DIV stay in rt_core.cpp.
inline void mfhi(EEContext& ctx, Reg rd) { core::set_gpr64(ctx, rd, ::p3fes::ee::mfhi(ctx)); }
inline void mflo(EEContext& ctx, Reg rd) { core::set_gpr64(ctx, rd, ::p3fes::ee::mflo(ctx)); }
inline void mthi(EEContext& ctx, Reg rs) { ::p3fes::ee::mthi(ctx, core::gpr64(ctx, rs)); }
inline void mtlo(EEContext& ctx, Reg rs) { ::p3fes::ee::mtlo(ctx, core::gpr64(ctx, rs)); }

// ---------------------------------------------------------------------------------------------
// Naturally aligned loads and stores: RAM / scratchpad inline, everything else through the slow path.

#define P3FES_RT_INLINE_LOAD(name, T)                                                             \
    P3FES_RT_HOT void name(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {                        \
        const std::uint32_t va = detail::ea(ctx, base, imm);                                      \
        if (const u8* p = detail::fast_ptr(ctx, va, sizeof(T))) {                                 \
            T v;                                                                                  \
            std::memcpy(&v, p, sizeof(T));                                                        \
            core::set_gpr64(ctx, rt, core::name(v));                                              \
            return;                                                                               \
        }                                                                                         \
        detail::load_slow(ctx, rt, va, detail::LoadKind::name);                                   \
    }
P3FES_RT_INLINE_LOAD(lb, u8)
P3FES_RT_INLINE_LOAD(lbu, u8)
P3FES_RT_INLINE_LOAD(lh, u16)
P3FES_RT_INLINE_LOAD(lhu, u16)
P3FES_RT_INLINE_LOAD(lw, u32)
P3FES_RT_INLINE_LOAD(lwu, u32)
#undef P3FES_RT_INLINE_LOAD

P3FES_RT_HOT void ld(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm);
    if (const u8* p = detail::fast_ptr(ctx, va, 8)) {
        u64 v;
        std::memcpy(&v, p, 8);
        core::set_gpr64(ctx, rt, v);
        return;
    }
    detail::load_slow(ctx, rt, va, detail::LoadKind::ld);
}

P3FES_RT_HOT void lq(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm) & detail::kQuadwordMask;
    if (const u8* p = detail::fast_ptr(ctx, va, 16)) {
        u128 v;
        std::memcpy(&v, p, 16);
        core::set_gpr128(ctx, rt, v);
        return;
    }
    detail::load_slow(ctx, rt, va, detail::LoadKind::lq);
}

#define P3FES_RT_INLINE_STORE(name, T)                                                            \
    P3FES_RT_HOT void name(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {                        \
        const std::uint32_t va = detail::ea(ctx, base, imm);                                      \
        if (u8* p = detail::fast_ptr(ctx, va, sizeof(T))) {                                       \
            const T v = static_cast<T>(core::gpr64(ctx, rt));                                     \
            std::memcpy(p, &v, sizeof(T));                                                        \
            return;                                                                               \
        }                                                                                         \
        detail::store_slow(ctx, va, ctx.gpr[rt], detail::StoreKind::name);                        \
    }
P3FES_RT_INLINE_STORE(sb, u8)
P3FES_RT_INLINE_STORE(sh, u16)
P3FES_RT_INLINE_STORE(sw, u32)
P3FES_RT_INLINE_STORE(sd, u64)
#undef P3FES_RT_INLINE_STORE

P3FES_RT_HOT void sq(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm) & detail::kQuadwordMask;
    if (u8* p = detail::fast_ptr(ctx, va, 16)) {
        std::memcpy(p, &ctx.gpr[rt], 16);
        return;
    }
    detail::store_slow(ctx, va, ctx.gpr[rt], detail::StoreKind::sq);
}

// Coprocessor loads and stores: the FPR file and the VU0 vf file are plain bit patterns in EEContext
// (fpu.h set_fpr / fpr, vu0.h qmtc2 / qmfc2: vf00 is never written), so the RAM fast path moves the bytes directly.
P3FES_RT_HOT void lwc1(EEContext& ctx, Reg ft, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm);
    if (const u8* p = detail::fast_ptr(ctx, va, 4)) {
        std::memcpy(&ctx.fpr[ft], p, 4);
        return;
    }
    detail::lwc1_slow(ctx, ft, va);
}
P3FES_RT_HOT void swc1(EEContext& ctx, Reg ft, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm);
    if (u8* p = detail::fast_ptr(ctx, va, 4)) {
        std::memcpy(p, &ctx.fpr[ft], 4);
        return;
    }
    detail::swc1_slow(ctx, ft, va);
}
P3FES_RT_HOT void lqc2(EEContext& ctx, Reg vf, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm) & detail::kQuadwordMask;
    if (const u8* p = detail::fast_ptr(ctx, va, 16)) {
        if (vf) std::memcpy(ctx.vu0.vf[vf], p, 16);  // the read happens, a write to vf00 is dropped
        return;
    }
    detail::lqc2_slow(ctx, vf, va);
}
P3FES_RT_HOT void sqc2(EEContext& ctx, Reg vf, Reg base, std::int32_t imm) {
    const std::uint32_t va = detail::ea(ctx, base, imm) & detail::kQuadwordMask;
    if (u8* p = detail::fast_ptr(ctx, va, 16)) {
        std::memcpy(p, ctx.vu0.vf[vf], 16);
        return;
    }
    detail::sqc2_slow(ctx, vf, va);
}

} // namespace p3fes::rt
