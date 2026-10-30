// Integer core semantics (runtime/include/p3fes/ee/core.h). Provenance of each expectation:
//   (hand: manual)  - MIPS III / EE Core Instruction Set Manual semantics, computed by hand
//   (EE, hardware-unverified) - the manual says implementation-dependent; the EE choice in core.h
// The unaligned merges are also checked against a byte-wise reference model of the little-endian
// LWL/LWR/... definitions at every byte offset (the reference is written from the manual's byte
// diagrams, independently of core.h's mask formulation).
#include "ee_test_util.h"

#include "p3fes/ee/core.h"

#include <cstring>

using namespace p3fes;
namespace core = p3fes::ee::core;

TEST_CASE("core: GPR writes drop $zero and keep bits 64..127 for 64-bit writes") {
    EEContext c;
    c.gpr[5].u64[1] = 0x1111222233334444ull;
    core::set_gpr64(c, 5, 0xAAAAull);
    CHECK(c.gpr[5].u64[0] == 0xAAAAull);
    CHECK(c.gpr[5].u64[1] == 0x1111222233334444ull);  // (hand: manual) non-MMI writes leave the upper half
    core::set_gpr64(c, 0, 0x1234u);
    CHECK(c.gpr[0].u64[0] == 0);
    core::set_gpr128(c, 0, ee_test::qd(1, 2));
    CHECK(c.gpr[0].u64[1] == 0);
    core::set_gpr128(c, 6, ee_test::qd(1, 2));
    CHECK(c.gpr[6].u64[0] == 1);
    CHECK(c.gpr[6].u64[1] == 2);
    CHECK(core::gpr32(c, 5) == 0xAAAAu);
}

TEST_CASE("core: 32-bit ALU results are sign-extended; sources use their low word") {
    // (hand: manual)
    CHECK(core::add32(0x7FFFFFFFu, 1u) == 0xFFFFFFFF80000000ull);
    CHECK(core::add32(0xFFFFFFFF00000001ull, 0x1u) == 2u);            // upper source bits ignored
    CHECK(core::sub32(0u, 1u) == 0xFFFFFFFFFFFFFFFFull);
    CHECK(core::add32i(0x7FFFFFF0u, 0x10) == 0xFFFFFFFF80000000ull);
    CHECK(core::add32i(5u, -6) == 0xFFFFFFFFFFFFFFFFull);
    CHECK(core::lui(0x8000u) == 0xFFFFFFFF80000000ull);
    CHECK(core::lui(0x7FFFu) == 0x7FFF0000ull);
    CHECK(core::lui(0x12345u) == 0x23450000ull);                       // only the 16-bit field
}

TEST_CASE("core: 64-bit ALU, logical immediates zero-extend, compares") {
    // (hand: manual)
    CHECK(core::add64(0xFFFFFFFFFFFFFFFFull, 2u) == 1u);
    CHECK(core::sub64(0u, 1u) == 0xFFFFFFFFFFFFFFFFull);
    CHECK(core::add64i(0x100000000ull, -1) == 0xFFFFFFFFull);
    CHECK(core::andi(0xFFFFFFFFFFFFFFFFull, 0x8001u) == 0x8001u);
    CHECK(core::ori(0xFFFFFFFF00000000ull, 0x8000u) == 0xFFFFFFFF00008000ull);
    CHECK(core::xori(0xFFFFull, 0xFFFFu) == 0u);
    CHECK(core::nor64(0u, 0xF0u) == 0xFFFFFFFFFFFFFF0Full);
    CHECK(core::slt(0xFFFFFFFFFFFFFFFFull, 0u) == 1u);   // -1 < 0
    CHECK(core::sltu(0xFFFFFFFFFFFFFFFFull, 0u) == 0u);
    CHECK(core::slti(0x8000000000000000ull, 0) == 1u);
    CHECK(core::sltiu(5u, -1) == 1u);                    // 5 < 0xFFFF...FFFF unsigned
    CHECK(core::sltiu(0xFFFFFFFFFFFFFFFFull, -1) == 0u);
    CHECK(core::movn_taken(0x100000000ull));             // 64-bit test: only the upper word set
    CHECK_FALSE(core::movz_taken(0x100000000ull));
}

TEST_CASE("core: shifts") {
    // (hand: manual)
    CHECK(core::sll(1u, 31) == 0xFFFFFFFF80000000ull);
    CHECK(core::srl(0xFFFFFFFF80000000ull, 1) == 0x40000000ull);
    CHECK(core::srl(0xFFFFFFFFFFFFFFFFull, 0) == 0xFFFFFFFFFFFFFFFFull);  // srl 0 re-sign-extends the word
    CHECK(core::sra(0x80000000u, 4) == 0xFFFFFFFFF8000000ull);
    CHECK(core::sllv(1u, 33u) == 2u);                                     // rs[4:0]
    CHECK(core::srav(0x80000000u, 0xFFFFFFE1u) == 0xFFFFFFFFC0000000ull); // rs = ...E1 -> shift 1
    CHECK(core::dsll(1u, 63) == 0x8000000000000000ull);
    CHECK(core::dsrl(0x8000000000000000ull, 63) == 1u);
    CHECK(core::dsra(0x8000000000000000ull, 4) == 0xF800000000000000ull);
    CHECK(core::dsll32(1u, 0) == 0x100000000ull);
    CHECK(core::dsll32(1u, 31) == 0x8000000000000000ull);
    CHECK(core::dsrl32(0xFFFFFFFF00000000ull, 0) == 0xFFFFFFFFull);
    CHECK(core::dsra32(0x8000000000000000ull, 0) == 0xFFFFFFFF80000000ull);
    CHECK(core::dsllv(1u, 64u + 3u) == 8u);                                // rs[5:0]
    CHECK(core::dsrlv(0x80u, 0xC7u) == 1u);                                // 0xC7 & 63 = 7
}

TEST_CASE("core: branch conditions, link value, addressing, load extension") {
    // (hand: manual)
    CHECK(core::beq(0x100000000ull, 0x100000000ull));
    CHECK_FALSE(core::beq(0x100000000ull, 0u));          // differs only in the upper word
    CHECK(core::blez(0u));
    CHECK(core::blez(0x8000000000000000ull));
    CHECK_FALSE(core::blez(0x80000000u));                // positive as a 64-bit value
    CHECK(core::bgtz(1u));
    CHECK(core::bltz(0xFFFFFFFFFFFFFFFFull));
    CHECK(core::bgez(0u));
    CHECK(core::link_value(0x100010u) == 0x100018u);
    CHECK(core::link_value(0x7FFFFFF8u) == 0xFFFFFFFF80000000ull);
    CHECK(core::effective_address(0x00100000u, -4) == 0x000FFFFCu);
    CHECK(core::effective_address(0xFFFFFFFF80001000ull, 0x10) == 0x80001010u);
    CHECK(core::is_aligned(0x1000u, 8));
    CHECK_FALSE(core::is_aligned(0x1004u, 8));
    CHECK(core::lb(0x80u) == 0xFFFFFFFFFFFFFF80ull);
    CHECK(core::lbu(0x80u) == 0x80u);
    CHECK(core::lh(0x8001u) == 0xFFFFFFFFFFFF8001ull);
    CHECK(core::lhu(0x8001u) == 0x8001u);
    CHECK(core::lw(0x80000000u) == 0xFFFFFFFF80000000ull);
    CHECK(core::lwu(0x80000000u) == 0x80000000u);
}

namespace {

// Byte-wise little-endian reference (manual byte diagrams): memory unit bytes m[0..n), register
// bytes r[0..8). LWL at offset b loads m[0..b] into the top b+1 bytes of the word; LWR loads
// m[b..n) into the low bytes; SWL stores the top b+1 bytes of the word into m[0..b]; SWR stores the
// low n-b bytes into m[b..n).
template <int N>
void ref_left_load(u8 (&r)[8], const u8 (&m)[N], int b) {
    for (int i = 0; i <= b; ++i) r[N - 1 - b + i] = m[i];
}
template <int N>
void ref_right_load(u8 (&r)[8], const u8 (&m)[N], int b) {
    for (int i = b; i < N; ++i) r[i - b] = m[i];
}
template <int N>
void ref_left_store(u8 (&m)[N], const u8 (&r)[8], int b) {
    for (int i = 0; i <= b; ++i) m[i] = r[N - 1 - b + i];
}
template <int N>
void ref_right_store(u8 (&m)[N], const u8 (&r)[8], int b) {
    for (int i = b; i < N; ++i) m[i] = r[i - b];
}

u64 bytes_to_u64(const u8 (&r)[8]) { u64 v; std::memcpy(&v, r, 8); return v; }
void u64_to_bytes(u8 (&r)[8], u64 v) { std::memcpy(r, &v, 8); }

} // namespace

TEST_CASE("core: LWL/LWR/SWL/SWR match the byte-wise reference at every offset") {
    const u32 mem = 0x44332211u;              // bytes 11 22 33 44
    const u64 rt = 0xA1A2A3A4B5B6B7B8ull;
    u8 m[4];
    std::memcpy(m, &mem, 4);
    for (u32 b = 0; b < 4; ++b) {
        CAPTURE(b);
        u8 r[8];
        // LWL: merge into the word, then sign-extend (the word's bit 31 always comes from memory).
        u64_to_bytes(r, rt);
        ref_left_load<4>(r, m, static_cast<int>(b));
        const u32 lwl_word = static_cast<u32>(bytes_to_u64(r));
        CHECK(core::lwl(rt, mem, 0x1000u + b) == core::sext32(lwl_word));
        // LWR: merge into the word; b == 0 is a full load (sign-extended), otherwise the upper half stays.
        u64_to_bytes(r, rt);
        ref_right_load<4>(r, m, static_cast<int>(b));
        const u32 lwr_word = static_cast<u32>(bytes_to_u64(r));
        const u64 lwr_expect = b == 0 ? core::sext32(lwr_word) : ((rt & 0xFFFFFFFF00000000ull) | lwr_word);
        CHECK(core::lwr(rt, mem, 0x1000u + b) == lwr_expect);  // (PCSX2 2.8.2 interpreter observed: core_0015..0023 keep the
                                                                // upper half; the recompiler zeroes it for b != 0)
        // SWL / SWR.
        u8 mm[4];
        std::memcpy(mm, m, 4);
        u64_to_bytes(r, rt);
        ref_left_store<4>(mm, r, static_cast<int>(b));
        u32 expect;
        std::memcpy(&expect, mm, 4);
        CHECK(core::swl(mem, rt, 0x1000u + b) == expect);
        std::memcpy(mm, m, 4);
        ref_right_store<4>(mm, r, static_cast<int>(b));
        std::memcpy(&expect, mm, 4);
        CHECK(core::swr(mem, rt, 0x1000u + b) == expect);
    }
    // (hand: manual) the classic pair reads an unaligned word: lwr 0(a) ; lwl 3(a) at a = 0x1001
    // over the doubleword 11 22 33 44 55 66 77 88 gives 0x55443322.
    const u32 lo = 0x44332211u, hi = 0x88776655u;
    u64 v = core::lwr(0, lo, 0x1001u);
    v = core::lwl(v, hi, 0x1004u);
    CHECK(v == 0x55443322u);
    // (hand: manual) LWR at offset 3 keeps the top three bytes and the upper word.
    CHECK(core::lwr(0xFFFFFFFF12345678ull, 0xAABBCCDDu, 0x1003u) == 0xFFFFFFFF123456AAull);
    // (hand: manual) LWL at offset 0 puts byte 0 at the top and sign-extends.
    CHECK(core::lwl(0x0000000012345678ull, 0x000000F0u, 0x1000u) == 0xFFFFFFFFF0345678ull);
}

TEST_CASE("core: LDL/LDR/SDL/SDR match the byte-wise reference at every offset") {
    const u64 mem = 0x8877665544332211ull;
    const u64 rt = 0xA1A2A3A4B5B6B7B8ull;
    u8 m[8];
    std::memcpy(m, &mem, 8);
    for (u32 b = 0; b < 8; ++b) {
        CAPTURE(b);
        u8 r[8];
        u64_to_bytes(r, rt);
        ref_left_load<8>(r, m, static_cast<int>(b));
        CHECK(core::ldl(rt, mem, 0x2000u + b) == bytes_to_u64(r));
        u64_to_bytes(r, rt);
        ref_right_load<8>(r, m, static_cast<int>(b));
        CHECK(core::ldr(rt, mem, 0x2000u + b) == bytes_to_u64(r));
        u8 mm[8];
        std::memcpy(mm, m, 8);
        u64_to_bytes(r, rt);
        ref_left_store<8>(mm, r, static_cast<int>(b));
        u64 expect;
        std::memcpy(&expect, mm, 8);
        CHECK(core::sdl(mem, rt, 0x2000u + b) == expect);
        std::memcpy(mm, m, 8);
        ref_right_store<8>(mm, r, static_cast<int>(b));
        std::memcpy(&expect, mm, 8);
        CHECK(core::sdr(mem, rt, 0x2000u + b) == expect);
    }
    // (hand: manual) ldr 0(a) ; ldl 7(a) at a = 0x2003 over 16 sequential bytes 00..0F = bytes 03..0A.
    u8 seq[16];
    for (int i = 0; i < 16; ++i) seq[i] = static_cast<u8>(i);
    u64 d0, d1;
    std::memcpy(&d0, seq, 8);
    std::memcpy(&d1, seq + 8, 8);
    u64 v = core::ldr(0, d0, 0x2003u);
    v = core::ldl(v, d1, 0x200Au);
    CHECK(v == 0x0A09080706050403ull);
}
