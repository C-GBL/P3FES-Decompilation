#include <doctest.h>

#include "p3fes/ee_types.h"

using namespace p3fes;

TEST_CASE("u128 is one quadword, 16-byte aligned") {
    CHECK(sizeof(u128) == 16);
    CHECK(alignof(u128) == 16);
    CHECK(sizeof(u8) == 1);
    CHECK(sizeof(u16) == 2);
    CHECK(sizeof(u32) == 4);
    CHECK(sizeof(u64) == 8);
    CHECK(sizeof(f32) == 4);
}

TEST_CASE("u128 lanes alias little-endian") {
    u128 q = u128::from_u64(0x1122334455667788ull);
    CHECK(q.lo() == 0x1122334455667788ull);
    CHECK(q.hi() == 0);
    CHECK(q.u32[0] == 0x55667788u);
    CHECK(q.u32[1] == 0x11223344u);
    CHECK(q.u8[0] == 0x88);
    CHECK(q.u8[7] == 0x11);
    CHECK(q.u8[15] == 0x00);

    q.u64[1] = 0xFFFFFFFFFFFFFFFFull;
    CHECK(q.s32[3] == -1);
    CHECK(q.u16[7] == 0xFFFF);
}
