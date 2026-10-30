// Fixed-width scalar types for the Emotion Engine (R5900) model.
//
// The EE is a 64-bit MIPS core with 128-bit general-purpose registers (the
// upper 64 bits are only touched by the MMI instruction set and by LQ/SQ).
// Everything in the runtime that models guest state uses these aliases so the
// recompiler output reads like the original MIPS semantics.
#pragma once

#include <cstddef>
#include <cstdint>

namespace p3fes {

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using s8  = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using f32 = float;
using f64 = double;

// One 128-bit EE register / quadword. Little-endian lane order: lane 0 is the
// least significant. GPR `rN` as seen by ordinary 32/64-bit MIPS code is
// `.u64[0]` (sign-extended into the low 64 bits; bits 64..127 are untouched).
// Members are spelled with the std:: types on purpose: naming a member `u64`
// of type `u64` would change the meaning of the alias inside the union.
union alignas(16) u128 {
    std::uint64_t u64[2];
    std::uint32_t u32[4];
    std::uint16_t u16[8];
    std::uint8_t  u8[16];
    std::int64_t  s64[2];
    std::int32_t  s32[4];
    std::int16_t  s16[8];
    std::int8_t   s8[16];
    float         f32[4];

    // Value accessors used by recompiled scalar code.
    constexpr std::uint64_t lo() const noexcept { return u64[0]; }
    constexpr std::uint64_t hi() const noexcept { return u64[1]; }

    static constexpr u128 from_u64(std::uint64_t v) noexcept {
        u128 r{};
        r.u64[0] = v;
        r.u64[1] = 0;
        return r;
    }
};

static_assert(sizeof(u128) == 16, "u128 must be exactly one quadword");
static_assert(alignof(u128) == 16, "u128 must be quadword aligned (LQ/SQ require it)");

} // namespace p3fes
