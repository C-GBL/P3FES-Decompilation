// Original to p3fes-port; structure resembles snuri00/ps2-web-recomp @ c0f476e runtime/include/ps2/memory.hpp (MIT, read only; see THIRD_PARTY.md).
// rt adapter: every guest memory access of the generated code (loads/stores, the unaligned
// LWL/LWR/LDL/LDR/SWL/SWR/SDL/SDR merges, LQ/SQ, LWC1/SWC1, LQC2/SQC2).
//
// Resolution order for an access of `n` bytes at virtual address va:
//   1. EEMemory::resolve(va, n): main RAM and its mirrors, the scratchpad, the BIOS window;
//   2. EEMemory::is_hw(va) (ADR-0013): the EE register window 0x10000000-0x1000FFFF and the GS
//      privileged window 0x12000000-0x12001FFF -> RtHooks::bus() at the physical address with the
//      guest's width (8/16/32/64/128 bits), followed by a check point (rt_hooks.h);
//   3. anything else -> RtHooks::fatal naming the instruction, the address and the base/offset.
// Natural alignment is required (core::is_aligned; the EE raises Address Error otherwise, which the
// adapter reports as fatal). LQ/SQ/LQC2/SQC2 drop the low four bits (mmi.h / vu0.h), the unaligned
// forms access the containing word/doubleword (core.h).
//
// Memory operations carry no guest pc (p3fes_recomp_rt.h); a fault reports ctx.pc (whatever the
// runtime last stored there) and the host return address into the generated function, which a
// debugger resolves to the generated source line.
#include "rt_internal.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/ee/mmi.h"
#include "p3fes/ee/vu0.h"
#include "p3fes/ee_memory.h"
#include "p3fes/prof.h"

#include <cstring>
#include <intrin.h>

#define P3FES_RT_RA() _ReturnAddress()

namespace p3fes::rt {

namespace core = ::p3fes::ee::core;

namespace {

[[noreturn]] void mem_fault(EEContext& ctx, const char* op, u32 va, u32 size, bool write, const char* why,
                            const void* host_ra) {
    detail::fatalf(ctx, ctx.pc,
                   "%s: %s %u-byte %s at virtual 0x%08x (physical 0x%08x); host return address %p",
                   op, why, size, write ? "store" : "load", va, EEMemory::to_physical(va), host_ra);
}

// Host pointer for a naturally aligned access that lies in RAM / scratchpad / BIOS, else nullptr.
template <class T>
inline u8* fast_ptr(EEContext& ctx, u32 va) noexcept {
    if (!core::is_aligned(va, sizeof(T))) return nullptr;
    EEMemory* m = ctx.memory;
    return m ? m->resolve(va, static_cast<u32>(sizeof(T))) : nullptr;
}

template <class T>
T bus_read(hle::HwBus& bus, u32 pa) {
    if constexpr (sizeof(T) == 1) return bus.read8(pa);
    else if constexpr (sizeof(T) == 2) return bus.read16(pa);
    else if constexpr (sizeof(T) == 4) return bus.read32(pa);
    else if constexpr (sizeof(T) == 8) return bus.read64(pa);
    else return bus.read128(pa);
}

template <class T>
void bus_write(hle::HwBus& bus, u32 pa, const T& v) {
    if constexpr (sizeof(T) == 1) bus.write8(pa, v);
    else if constexpr (sizeof(T) == 2) bus.write16(pa, v);
    else if constexpr (sizeof(T) == 4) bus.write32(pa, v);
    else if constexpr (sizeof(T) == 8) bus.write64(pa, v);
    else bus.write128(pa, v);
}

// Not RAM: a hardware window (returns the value) or a fatal stop.
template <class T>
__declspec(noinline) T slow_load(EEContext& ctx, u32 va, const char* op, const void* ra) {
    constexpr u32 n = static_cast<u32>(sizeof(T));
    if (!ctx.memory) mem_fault(ctx, op, va, n, false, "no EEMemory bound (ctx.memory is null) for", ra);
    if (!core::is_aligned(va, n)) mem_fault(ctx, op, va, n, false, "address error: unaligned", ra);
    if (!EEMemory::is_hw(va)) mem_fault(ctx, op, va, n, false, "unmapped", ra);
    const prof::Scope prof_zone(prof::Zone::Hw);
    return bus_read<T>(detail::hk().bus(), EEMemory::to_physical(va));
}

template <class T>
__declspec(noinline) void slow_store(EEContext& ctx, u32 va, const T& v, const char* op, const void* ra) {
    constexpr u32 n = static_cast<u32>(sizeof(T));
    if (!ctx.memory) mem_fault(ctx, op, va, n, true, "no EEMemory bound (ctx.memory is null) for", ra);
    if (!core::is_aligned(va, n)) mem_fault(ctx, op, va, n, true, "address error: unaligned", ra);
    if (!EEMemory::is_hw(va)) mem_fault(ctx, op, va, n, true, "unmapped", ra);
    const prof::Scope prof_zone(prof::Zone::Hw);
    bus_write<T>(detail::hk().bus(), EEMemory::to_physical(va), v);
}

// Returns true when the access went to a hardware window (the caller then runs the check point
// after it has written its destination register).
template <class T>
inline bool load(EEContext& ctx, u32 va, T& out, const char* op, const void* ra) {
    if (const u8* p = fast_ptr<T>(ctx, va)) {
        std::memcpy(&out, p, sizeof(T));
        return false;
    }
    out = slow_load<T>(ctx, va, op, ra);
    return true;
}

template <class T>
inline bool store(EEContext& ctx, u32 va, const T& v, const char* op, const void* ra) {
    if (u8* p = fast_ptr<T>(ctx, va)) {
        std::memcpy(p, &v, sizeof(T));
        return false;
    }
    slow_store<T>(ctx, va, v, op, ra);
    return true;
}

inline u32 ea(const EEContext& ctx, Reg base, std::int32_t imm) noexcept {
    return core::effective_address(core::gpr64(ctx, base), imm);
}

} // namespace

// ---------------------------------------------------------------------------------------------
// Naturally aligned loads and stores: the RAM / scratchpad fast paths are inline in
// p3fes_recomp_rt_inline.h; everything that is not one lands here with the effective address. These
// two finish the instruction (destination register, check point after a hardware-window access) and
// report faults with their own return address = the call site inside the generated function.

static_assert(detail::kQuadwordMask == ee::mmi::kQuadwordMask, "LQ/SQ mask must match ee/mmi.h");
static_assert(detail::kQuadwordMask == ee::vu0::kQuadwordMask, "LQC2/SQC2 mask must match ee/vu0.h");

namespace detail {

__declspec(noinline) void load_slow(EEContext& ctx, Reg rt, u32 va, LoadKind kind) {
    const void* ra = P3FES_RT_RA();
    bool hw = false;
    switch (kind) {
    case LoadKind::lb: { u8 v; hw = load<u8>(ctx, va, v, "lb", ra); core::set_gpr64(ctx, rt, core::lb(v)); break; }
    case LoadKind::lbu: { u8 v; hw = load<u8>(ctx, va, v, "lbu", ra); core::set_gpr64(ctx, rt, core::lbu(v)); break; }
    case LoadKind::lh: { u16 v; hw = load<u16>(ctx, va, v, "lh", ra); core::set_gpr64(ctx, rt, core::lh(v)); break; }
    case LoadKind::lhu: { u16 v; hw = load<u16>(ctx, va, v, "lhu", ra); core::set_gpr64(ctx, rt, core::lhu(v)); break; }
    case LoadKind::lw: { u32 v; hw = load<u32>(ctx, va, v, "lw", ra); core::set_gpr64(ctx, rt, core::lw(v)); break; }
    case LoadKind::lwu: { u32 v; hw = load<u32>(ctx, va, v, "lwu", ra); core::set_gpr64(ctx, rt, core::lwu(v)); break; }
    case LoadKind::ld: { u64 v; hw = load<u64>(ctx, va, v, "ld", ra); core::set_gpr64(ctx, rt, v); break; }
    case LoadKind::lq: { u128 v; hw = load<u128>(ctx, va, v, "lq", ra); core::set_gpr128(ctx, rt, v); break; }
    }
    if (hw) after_hw(ctx);
}

__declspec(noinline) void store_slow(EEContext& ctx, u32 va, const u128& v, StoreKind kind) {
    const void* ra = P3FES_RT_RA();
    bool hw = false;
    switch (kind) {
    case StoreKind::sb: hw = store<u8>(ctx, va, static_cast<u8>(v.u64[0]), "sb", ra); break;
    case StoreKind::sh: hw = store<u16>(ctx, va, static_cast<u16>(v.u64[0]), "sh", ra); break;
    case StoreKind::sw: hw = store<u32>(ctx, va, static_cast<u32>(v.u64[0]), "sw", ra); break;
    case StoreKind::sd: hw = store<u64>(ctx, va, v.u64[0], "sd", ra); break;
    case StoreKind::sq: hw = store<u128>(ctx, va, v, "sq", ra); break;
    }
    if (hw) after_hw(ctx);
}

} // namespace detail

// ---------------------------------------------------------------------------------------------
// Unaligned forms: read the containing aligned unit, merge (core.h), write the register / unit.

#define P3FES_RT_LOAD_MERGE(name, T, mask)                                                        \
    void name(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {                               \
        const u32 va = ea(ctx, base, imm);                                                        \
        T mem;                                                                                    \
        const bool hw = load<T>(ctx, va & (mask), mem, #name, P3FES_RT_RA());                     \
        core::set_gpr64(ctx, rt, core::name(core::gpr64(ctx, rt), mem, va));                      \
        if (hw) detail::after_hw(ctx);                                                            \
    }
P3FES_RT_LOAD_MERGE(lwl, u32, core::kWordMask)
P3FES_RT_LOAD_MERGE(lwr, u32, core::kWordMask)
P3FES_RT_LOAD_MERGE(ldl, u64, core::kDwordMask)
P3FES_RT_LOAD_MERGE(ldr, u64, core::kDwordMask)
#undef P3FES_RT_LOAD_MERGE

#define P3FES_RT_STORE_MERGE(name, T, mask)                                                       \
    void name(EEContext& ctx, Reg rt, Reg base, std::int32_t imm) {                               \
        const u32 va = ea(ctx, base, imm);                                                        \
        const u32 unit = va & (mask);                                                             \
        T mem;                                                                                    \
        bool hw = load<T>(ctx, unit, mem, #name, P3FES_RT_RA());                                  \
        hw |= store<T>(ctx, unit, core::name(mem, core::gpr64(ctx, rt), va), #name, P3FES_RT_RA()); \
        if (hw) detail::after_hw(ctx);                                                            \
    }
P3FES_RT_STORE_MERGE(swl, u32, core::kWordMask)
P3FES_RT_STORE_MERGE(swr, u32, core::kWordMask)
P3FES_RT_STORE_MERGE(sdl, u64, core::kDwordMask)
P3FES_RT_STORE_MERGE(sdr, u64, core::kDwordMask)
#undef P3FES_RT_STORE_MERGE

// ---------------------------------------------------------------------------------------------
// Coprocessor transfers: inline fast paths in p3fes_recomp_rt_inline.h, the slow halves here.

namespace detail {

// The slow halves of the inline LWC1/SWC1/LQC2/SQC2 (p3fes_recomp_rt_inline.h): `va` is the effective address
// (LQC2/SQC2: masked to the quadword).
__declspec(noinline) void lwc1_slow(EEContext& ctx, Reg ft, u32 va) {
    u32 v;
    const bool hw = load<u32>(ctx, va, v, "lwc1", P3FES_RT_RA());
    ee::fpu::set_fpr(ctx, ft, v);
    if (hw) after_hw(ctx);
}
__declspec(noinline) void swc1_slow(EEContext& ctx, Reg ft, u32 va) {
    if (store<u32>(ctx, va, ee::fpu::fpr(ctx, ft), "swc1", P3FES_RT_RA())) after_hw(ctx);
}
__declspec(noinline) void lqc2_slow(EEContext& ctx, Reg vf, u32 va) {
    u128 v;
    const bool hw = load<u128>(ctx, va, v, "lqc2", P3FES_RT_RA());
    ee::vu0::qmtc2(ctx.vu0, vf, v);  // vf00 stays (0,0,0,1): the read happens, the write is dropped
    if (hw) after_hw(ctx);
}
__declspec(noinline) void sqc2_slow(EEContext& ctx, Reg vf, u32 va) {
    if (store<u128>(ctx, va, ee::vu0::qmfc2(ctx.vu0, vf), "sqc2", P3FES_RT_RA())) after_hw(ctx);
}

} // namespace detail

} // namespace p3fes::rt
