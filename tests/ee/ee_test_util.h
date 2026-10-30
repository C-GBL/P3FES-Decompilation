// Shared helpers for tests/ee/: quadword constructors, u128 equality and doctest printing.
#pragma once

#include <doctest.h>

#include <bit>
#include <cstdio>

#include "p3fes/ee_types.h"

namespace p3fes {

inline bool operator==(const u128& a, const u128& b) noexcept { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }
inline bool operator!=(const u128& a, const u128& b) noexcept { return !(a == b); }

} // namespace p3fes

namespace doctest {

template <>
struct StringMaker<p3fes::u128> {
    static String convert(const p3fes::u128& v) {
        char buf[64];
        std::snprintf(buf, sizeof buf, "{w3=%08X w2=%08X w1=%08X w0=%08X}", v.u32[3], v.u32[2], v.u32[1], v.u32[0]);
        return buf;
    }
};

} // namespace doctest

namespace p3fes::ee_test {

// Lane 0 first (little-endian), matching the `u128` member arrays.
inline u128 qw(u32 w0, u32 w1, u32 w2, u32 w3) noexcept {
    u128 r{};
    r.u32[0] = w0; r.u32[1] = w1; r.u32[2] = w2; r.u32[3] = w3;
    return r;
}

inline u128 qd(u64 lo, u64 hi) noexcept {
    u128 r{};
    r.u64[0] = lo; r.u64[1] = hi;
    return r;
}

inline u128 qh(u16 h0, u16 h1, u16 h2, u16 h3, u16 h4, u16 h5, u16 h6, u16 h7) noexcept {
    u128 r{};
    r.u16[0] = h0; r.u16[1] = h1; r.u16[2] = h2; r.u16[3] = h3;
    r.u16[4] = h4; r.u16[5] = h5; r.u16[6] = h6; r.u16[7] = h7;
    return r;
}

inline u128 qb(const u8 (&b)[16]) noexcept {
    u128 r{};
    for (int i = 0; i < 16; ++i) r.u8[i] = b[i];
    return r;
}

// Bytes 0..15 = base+0 .. base+15: handy for permutation tests.
inline u128 qseq(u8 base) noexcept {
    u128 r{};
    for (int i = 0; i < 16; ++i) r.u8[i] = static_cast<u8>(base + i);
    return r;
}

inline constexpr u32 f2u(float f) noexcept { return std::bit_cast<u32>(f); }

} // namespace p3fes::ee_test
