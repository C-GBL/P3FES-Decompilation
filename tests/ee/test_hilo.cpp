// HI/LO pipes, the 32-bit multiply/divide family and the SA register (runtime/include/p3fes/ee/hilo.h).
// Provenance of each expectation is stated inline:
//   (hand: EE Core User's Manual semantics)   - the manual defines the result
//   (upstream behaviour, hardware-unverified) - the manual leaves it undefined; we match ps2-web-recomp @ c0f476e
//   (PCSX2 2.8.2 observed: <id>)             - settled by tests/ee/vectors/pcsx2_vectors.json (tools/ours/eevec); all 656 hilo vectors agree
#include "ee_test_util.h"

#include "p3fes/ee/hilo.h"

using namespace p3fes;
using namespace p3fes::ee;

TEST_CASE("mult/mult1: signed 32x32 -> HI/LO of the selected pipe only") {
    EEContext c;
    // (hand: manual) -1 * 2 = -2: LO = sext32(0xFFFFFFFE), HI = sext32(0xFFFFFFFF).
    mult(c, kPipe0, 0xFFFFFFFFu, 2u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(c.hi.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.lo.u64[1] == 0);
    CHECK(c.hi.u64[1] == 0);
    CHECK(mflo(c) == 0xFFFFFFFFFFFFFFFEull);
    CHECK(mfhi(c) == 0xFFFFFFFFFFFFFFFFull);

    // (hand: manual) INT32_MIN * INT32_MIN = 2^62 -> LO1 = 0, HI1 = 0x40000000; pipe 0 untouched.
    mult1(c, 0x80000000u, 0x80000000u);
    CHECK(c.lo.u64[1] == 0);
    CHECK(c.hi.u64[1] == 0x40000000u);
    CHECK(mflo1(c) == 0);
    CHECK(mfhi1(c) == 0x40000000u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFEull);

    // (hand: manual) 0x7FFFFFFF * 2 = 0xFFFFFFFE: LO sign-extends the low word even though the product is positive.
    mult(c, kPipe0, 0x7FFFFFFFu, 2u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(c.hi.u64[0] == 0);
}

TEST_CASE("multu/multu1: unsigned 32x32") {
    EEContext c;
    // (hand: manual) 0xFFFFFFFF * 2 = 0x1_FFFFFFFE -> LO = sext32(0xFFFFFFFE), HI = 1.
    multu(c, kPipe0, 0xFFFFFFFFu, 2u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(c.hi.u64[0] == 1u);
    // (hand: manual) 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE_00000001 on pipe 1.
    multu1(c, 0xFFFFFFFFu, 0xFFFFFFFFu);
    CHECK(c.lo.u64[1] == 1u);
    CHECK(c.hi.u64[1] == 0xFFFFFFFFFFFFFFFEull);
}

TEST_CASE("madd/maddu: accumulate into {HI,LO} with carry across the word boundary") {
    EEContext c;
    // (hand: manual) 0x10000 * 0x10000 = 2^32 -> LO = 0, HI = 1; then + 3*4 -> LO = 12, HI = 1.
    mult(c, kPipe0, 0x10000u, 0x10000u);
    madd(c, kPipe0, 3u, 4u);
    CHECK(c.lo.u64[0] == 12u);
    CHECK(c.hi.u64[0] == 1u);
    // (hand: manual) 0xFFFFFFFF + 1*1 carries into HI: LO = 0, HI = 1.
    multu(c, kPipe0, 0xFFFFFFFFu, 1u);
    maddu(c, kPipe0, 1u, 1u);
    CHECK(c.lo.u64[0] == 0u);
    CHECK(c.hi.u64[0] == 1u);
    // (hand: manual) negative product: 0 + (-1 * 1) = -1 -> LO = HI = all ones.
    mult(c, kPipe0, 0u, 0u);
    madd(c, kPipe0, 0xFFFFFFFFu, 1u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.hi.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    // (hand: manual) madd1/maddu1 use pipe 1 and leave pipe 0 alone.
    madd1(c, 2u, 3u);
    maddu1(c, 1u, 1u);
    CHECK(c.lo.u64[1] == 7u);
    CHECK(c.hi.u64[1] == 0u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFFull);
}

TEST_CASE("div/div1: signed divide, truncation toward zero, special cases") {
    EEContext c;
    // (hand: manual) 7 / 2 = 3 rem 1.
    div(c, kPipe0, 7u, 2u);
    CHECK(c.lo.s64[0] == 3);
    CHECK(c.hi.s64[0] == 1);
    // (hand: manual) -7 / 2 = -3 rem -1 (remainder takes the dividend's sign).
    div(c, kPipe0, static_cast<u32>(-7), 2u);
    CHECK(c.lo.s64[0] == -3);
    CHECK(c.hi.s64[0] == -1);
    // (hand: manual) 7 / -2 = -3 rem 1.
    div(c, kPipe0, 7u, static_cast<u32>(-2));
    CHECK(c.lo.s64[0] == -3);
    CHECK(c.hi.s64[0] == 1);
    // (PCSX2 2.8.2 observed: hilo_0911, hilo_0912) divide by zero: LO = -1 for n >= 0, +1 for n < 0; HI = n.
    div1(c, 9u, 0u);
    CHECK(c.lo.s64[1] == -1);
    CHECK(c.hi.s64[1] == 9);
    div1(c, static_cast<u32>(-5), 0u);
    CHECK(c.lo.s64[1] == 1);
    CHECK(c.hi.s64[1] == -5);
    // (PCSX2 2.8.2 observed: hilo_0612) INT32_MIN / -1: LO = INT32_MIN (sign-extended), HI = 0.
    div(c, kPipe0, 0x80000000u, 0xFFFFFFFFu);
    CHECK(c.lo.u64[0] == 0xFFFFFFFF80000000ull);
    CHECK(c.hi.u64[0] == 0u);
}

TEST_CASE("divu/divu1: unsigned divide, results sign-extended as words") {
    EEContext c;
    // (hand: manual) 0xFFFFFFFF / 2 = 0x7FFFFFFF rem 1.
    divu(c, kPipe0, 0xFFFFFFFFu, 2u);
    CHECK(c.lo.u64[0] == 0x7FFFFFFFu);
    CHECK(c.hi.u64[0] == 1u);
    // (hand: manual) 0xFFFFFFFF / 1 = 0xFFFFFFFF, which sign-extends to all ones in the 64-bit LO.
    divu1(c, 0xFFFFFFFFu, 1u);
    CHECK(c.lo.u64[1] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.hi.u64[1] == 0u);
    // (PCSX2 2.8.2 observed: hilo_0636, hilo_0637) divide by zero: LO = -1, HI = sext32(dividend).
    divu(c, kPipe0, 0x80000000u, 0u);
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.hi.u64[0] == 0xFFFFFFFF80000000ull);
}

TEST_CASE("mthi/mtlo/mthi1/mtlo1 round-trip 64-bit values and stay in their pipe") {
    EEContext c;
    // (hand: manual) MTHI/MTLO copy the full 64-bit GPR.
    mthi(c, 0x1122334455667788ull);
    mtlo(c, 0x99AABBCCDDEEFF00ull);
    mthi1(c, 0x0102030405060708ull);
    mtlo1(c, 0x090A0B0C0D0E0F10ull);
    CHECK(mfhi(c) == 0x1122334455667788ull);
    CHECK(mflo(c) == 0x99AABBCCDDEEFF00ull);
    CHECK(mfhi1(c) == 0x0102030405060708ull);
    CHECK(mflo1(c) == 0x090A0B0C0D0E0F10ull);
    CHECK(hilo(c, kPipe0) == 0x55667788DDEEFF00ull); // {HI[31:0], LO[31:0]}
    CHECK(hilo(c, kPipe1) == 0x050607080D0E0F10ull);
}

TEST_CASE("SA register: mtsab/mtsah/mtsa/mfsa and the byte count QFSRV consumes") {
    EEContext c;
    // (hand: manual) MTSAB: SA = ((rs ^ imm) & 0xF) * 8 bits.
    mtsab(c, 0x5u, 0x3u);
    CHECK(mfsa(c) == 48u);
    CHECK(sa_bytes(c) == 6u);
    mtsab(c, 0x13u, 0u); // only the low four bits of rs count
    CHECK(mfsa(c) == 24u);
    CHECK(sa_bytes(c) == 3u);
    mtsab(c, 0u, 0u);
    CHECK(mfsa(c) == 0u);
    // (hand: manual) MTSAH: SA = ((rs ^ imm) & 0x7) * 16 bits.
    mtsah(c, 1u, 4u);
    CHECK(mfsa(c) == 80u);
    CHECK(sa_bytes(c) == 10u);
    mtsah(c, 8u, 0u); // bit 3 of rs is ignored
    CHECK(mfsa(c) == 0u);
    mtsah(c, 7u, 0u);
    CHECK(mfsa(c) == 112u);
    CHECK(sa_bytes(c) == 14u);
    // (hand: manual) MTSA copies rs; MFSA reads it back unchanged. The byte count is bits 6..3.
    mtsa(c, 0x12345678u);
    CHECK(mfsa(c) == 0x12345678u);
    CHECK(sa_bytes(c) == 15u);
    mtsa(c, 0x7u); // not a multiple of 8: undefined on hardware, the low bits are ignored here
    CHECK(sa_bytes(c) == 0u);
}
