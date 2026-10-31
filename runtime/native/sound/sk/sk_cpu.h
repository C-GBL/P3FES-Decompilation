// The register file and memory view the generated SK code runs on (sk_gen_*.cpp, tools/ours/modernize/skgen.py;
// README.md). Modernize layer 3, steps 2-3 (docs/MODERNIZE_PLAN.md section 3): the six Standard Kit IOP modules as
// native C++ instead of on the R3000 interpreter (runtime/hle/sif/iop/r3000.cpp), with the interpreter's semantics:
// the MIPS I integer set, 32-bit wrapping arithmetic, no overflow traps, div / divu by zero as the interpreter
// leaves HI / LO, loads and stores over the 2 MiB of IOP RAM (kuseg / kseg0 / kseg1 fold onto it; a misaligned
// access or one outside RAM is a fault, as the interpreter traps), LWL / LWR / SWL / SWR by its merge formulas.
#pragma once

#include <cstdint>
#include <cstring>

namespace p3fes::native::sound::sk {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

inline constexpr u32 kRamSize = 0x200000u;        // IOP RAM
inline constexpr u32 kExitSentinel = 0xBFC00000u; // what a thread entry / interrupt handler returns to

class NativeSk;

struct Cpu {
    u32 r[32]{};
    u32 hi = 0, lo = 0;
    u8* ram = nullptr;        // IOP RAM, kRamSize bytes (borrowed)
    NativeSk* host = nullptr;
    // A blocking import parked the running thread: every caller returns at once up to its runner.
    bool parked = false;
    // The runner resumes a woken thread by calling its entry with `resume` = the instruction after the blocking call
    // (the entry jumps there; the registers are the thread's) and `resume_ra0` = the $ra the entry was started with.
    u32 resume = 0, resume_ra0 = 0;

    // ---- memory (the interpreter's checks: R3000::check_addr) ---------------------------------------------------
    static bool bad(u32 a, u32 size) { return (a & (size - 1u)) != 0 || (a & 0x1FFFFFFFu) >= kRamSize; }
    static u32 off(u32 a) { return a & (kRamSize - 1u); }
    u32 raw32(u32 a) const {
        u32 v;
        std::memcpy(&v, ram + off(a & ~3u), 4);
        return v;
    }
    void put32(u32 a, u32 v) { std::memcpy(ram + off(a & ~3u), &v, 4); }
    u32 lw(u32 a) {
        if (bad(a, 4)) return fault_load(a);
        return raw32(a);
    }
    u32 lhu(u32 a) {
        if (bad(a, 2)) return fault_load(a);
        u16 v;
        std::memcpy(&v, ram + off(a), 2);
        return v;
    }
    u32 lh(u32 a) { return static_cast<u32>(static_cast<s32>(static_cast<s16>(lhu(a)))); }
    u32 lbu(u32 a) {
        if (bad(a, 1)) return fault_load(a);
        return ram[off(a)];
    }
    u32 lb(u32 a) { return static_cast<u32>(static_cast<s32>(static_cast<s8>(lbu(a)))); }
    void sw(u32 a, u32 v) {
        if (bad(a, 4)) return fault_store(a);
        put32(a, v);
    }
    void sh(u32 a, u32 v) {
        if (bad(a, 2)) return fault_store(a);
        const u16 h = static_cast<u16>(v);
        std::memcpy(ram + off(a), &h, 2);
    }
    void sb(u32 a, u32 v) {
        if (bad(a, 1)) return fault_store(a);
        ram[off(a)] = static_cast<u8>(v);
    }
    u32 lwl(u32 a, u32 old) {
        if (bad(a, 1)) return fault_load(a);
        const u32 shift = (3u - (a & 3u)) * 8u, mem = raw32(a);
        return (mem << shift) | (shift ? (old & ((1u << shift) - 1u)) : 0u);
    }
    u32 lwr(u32 a, u32 old) {
        if (bad(a, 1)) return fault_load(a);
        const u32 shift = (a & 3u) * 8u, mem = raw32(a);
        return (mem >> shift) | (shift ? (old & ~(0xFFFFFFFFu >> shift)) : 0u);
    }
    void swl(u32 a, u32 v) {
        if (bad(a, 1)) return fault_store(a);
        const u32 shift = (3u - (a & 3u)) * 8u, mem = raw32(a);
        put32(a, (v >> shift) | (shift ? (mem & ~(0xFFFFFFFFu >> shift)) : 0u));
    }
    void swr(u32 a, u32 v) {
        if (bad(a, 1)) return fault_store(a);
        const u32 shift = (a & 3u) * 8u, mem = raw32(a);
        put32(a, (v << shift) | (shift ? (mem & ((1u << shift) - 1u)) : 0u));
    }
    // Call argument i of an import (a0..a3, then the caller's stack from sp + 16), as R3000::arg.
    u32 arg(unsigned i) const { return i < 4 ? r[4 + i] : raw32(r[29] + 4u * i); }

    // ---- faults (sk_host.cpp: the first one is kept and logged; the native stack then stops answering) ----------
    u32 fault_load(u32 a);
    void fault_store(u32 a);
    void trap(u32 pc, const char* what);
    void bad_return(u32 fn, u32 ra);
    void bad_jump(u32 at, u32 target);
    void fell_off(u32 fn);
};

using Fn = void (*)(Cpu&);

inline void mult(Cpu& c, u32 a, u32 b) {
    const s64 p = static_cast<s64>(static_cast<s32>(a)) * static_cast<s32>(b);
    c.lo = static_cast<u32>(static_cast<u64>(p));
    c.hi = static_cast<u32>(static_cast<u64>(p) >> 32);
}
inline void multu(Cpu& c, u32 a, u32 b) {
    const u64 p = static_cast<u64>(a) * b;
    c.lo = static_cast<u32>(p);
    c.hi = static_cast<u32>(p >> 32);
}
inline void div(Cpu& c, u32 a, u32 b) {
    const s32 n = static_cast<s32>(a), d = static_cast<s32>(b);
    if (d == 0) {
        c.lo = n < 0 ? 1u : 0xFFFFFFFFu;
        c.hi = static_cast<u32>(n);
    } else if (n == INT32_MIN && d == -1) {
        c.lo = static_cast<u32>(INT32_MIN);
        c.hi = 0;
    } else {
        c.lo = static_cast<u32>(n / d);
        c.hi = static_cast<u32>(n % d);
    }
}
inline void divu(Cpu& c, u32 a, u32 b) {
    if (b == 0) {
        c.lo = 0xFFFFFFFFu;
        c.hi = a;
    } else {
        c.lo = a / b;
        c.hi = a % b;
    }
}

// jalr / an indirect jump: the generated function at IOP address `addr` (sk_gen.h kFunctions); anything else is a
// fault. Defined in sk_host.cpp.
void call_address(Cpu& c, u32 addr);
// The function that starts at `addr`, nullptr when none.
Fn function_at(u32 addr);

}  // namespace p3fes::native::sound::sk
