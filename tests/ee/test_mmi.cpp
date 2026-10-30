// MMI instruction vectors (runtime/include/p3fes/ee/mmi.h), one or more per instruction, run through the
// default path (SSE2 unless P3FES_EE_MMI_USE_SSE2=0). tests/ee/test_mmi_paths.cpp proves the scalar and SSE2
// paths agree on random inputs, so these hand vectors only need to pin the semantics once.
// Provenance:
//   (hand: EE Core User's Manual semantics)   - the manual defines the result
//   (upstream behaviour, hardware-unverified) - the manual leaves it undefined; we match ps2-web-recomp @ c0f476e
//   (PCSX2 2.8.2 observed: <id>)             - settled by tests/ee/vectors/pcsx2_vectors.json (tools/ours/eevec)
#include "ee_test_util.h"

#include "p3fes/ee/mmi.h"
#include "p3fes/ee_memory.h"

using namespace p3fes;
using namespace p3fes::ee;
using namespace p3fes::ee_test;

namespace {

u128 bin(void (*op)(u128&, const u128&, const u128&), const u128& s, const u128& t) {
    u128 d{};
    op(d, s, t);
    return d;
}
u128 un(void (*op)(u128&, const u128&), const u128& t) {
    u128 d{};
    op(d, t);
    return d;
}
u128 sh(void (*op)(u128&, const u128&, u32), const u128& t, u32 sa) {
    u128 d{};
    op(d, t, sa);
    return d;
}

} // namespace

// ------------------------------------------------------------------------------------------------
// Parallel add / subtract
// ------------------------------------------------------------------------------------------------
TEST_CASE("paddw/psubw: 32-bit lanes wrap, carries never cross lanes") {
    // (hand: manual)
    CHECK(bin(mmi::paddw, qw(0xFFFFFFFFu, 1u, 0x7FFFFFFFu, 0u), qw(1u, 1u, 1u, 0u)) == qw(0u, 2u, 0x80000000u, 0u));
    CHECK(bin(mmi::psubw, qw(0u, 5u, 0x80000000u, 1u), qw(1u, 3u, 1u, 1u)) == qw(0xFFFFFFFFu, 2u, 0x7FFFFFFFu, 0u));
}

TEST_CASE("paddh/psubh and paddb/psubb: 16- and 8-bit lanes wrap") {
    // (hand: manual)
    CHECK(bin(mmi::paddh, qh(0xFFFF, 1, 0x7FFF, 0, 0, 0, 0, 0x8000), qh(1, 1, 1, 0, 0, 0, 0, 0x8000)) ==
          qh(0, 2, 0x8000, 0, 0, 0, 0, 0));
    CHECK(bin(mmi::psubh, qh(0, 5, 0x8000, 0, 0, 0, 0, 0), qh(1, 3, 1, 0, 0, 0, 0, 0)) == qh(0xFFFF, 2, 0x7FFF, 0, 0, 0, 0, 0));
    const u8 a[16] = {0xFF, 1, 0x7F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10};
    const u8 b[16] = {1, 1, 1, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20};
    const u8 sum[16] = {0, 2, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30};
    const u8 diff[16] = {0xFE, 0, 0x7E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xF6};
    CHECK(bin(mmi::paddb, qb(a), qb(b)) == qb(sum));
    CHECK(bin(mmi::psubb, qb(a), qb(b)) == qb(diff));
}

TEST_CASE("paddsw/psubsw: signed 32-bit saturation at both bounds") {
    // (hand: manual)
    CHECK(bin(mmi::paddsw, qw(0x7FFFFFFFu, 0x80000000u, 5u, 0x80000000u), qw(1u, 0xFFFFFFFFu, static_cast<u32>(-3), 0x7FFFFFFFu)) ==
          qw(0x7FFFFFFFu, 0x80000000u, 2u, 0xFFFFFFFFu));
    CHECK(bin(mmi::psubsw, qw(0x80000000u, 0x7FFFFFFFu, 5u, 0u), qw(1u, 0xFFFFFFFFu, 7u, 0x80000000u)) ==
          qw(0x80000000u, 0x7FFFFFFFu, static_cast<u32>(-2), 0x7FFFFFFFu));
}

TEST_CASE("paddsh/psubsh and paddsb/psubsb: signed 16/8-bit saturation") {
    // (hand: manual)
    CHECK(bin(mmi::paddsh, qh(0x7FFF, 0x8000, 5, 0x7FFE, 0, 0, 0, 0), qh(1, 0xFFFF, 0xFFFD, 1, 0, 0, 0, 0)) ==
          qh(0x7FFF, 0x8000, 2, 0x7FFF, 0, 0, 0, 0));
    CHECK(bin(mmi::psubsh, qh(0x8000, 0x7FFF, 5, 0, 0, 0, 0, 0), qh(1, 0xFFFF, 7, 0x8000, 0, 0, 0, 0)) ==
          qh(0x8000, 0x7FFF, 0xFFFE, 0x7FFF, 0, 0, 0, 0));
    const u8 a[16] = {0x7F, 0x80, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7E};
    const u8 b[16] = {1, 0xFF, 0xFD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    const u8 sum[16] = {0x7F, 0x80, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7F};
    CHECK(bin(mmi::paddsb, qb(a), qb(b)) == qb(sum));
    const u8 c[16] = {0x80, 0x7F, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const u8 d[16] = {1, 0xFF, 7, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const u8 diff[16] = {0x80, 0x7F, 0xFE, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    CHECK(bin(mmi::psubsb, qb(c), qb(d)) == qb(diff));
}

TEST_CASE("padduw/psubuw/padduh/psubuh/paddub/psubub: unsigned saturation") {
    // (hand: manual)
    CHECK(bin(mmi::padduw, qw(0xFFFFFFFFu, 0x80000000u, 1u, 0xFFFFFFFEu), qw(1u, 0x80000000u, 2u, 1u)) ==
          qw(0xFFFFFFFFu, 0xFFFFFFFFu, 3u, 0xFFFFFFFFu));
    CHECK(bin(mmi::psubuw, qw(0u, 5u, 3u, 0x80000000u), qw(1u, 3u, 3u, 0x7FFFFFFFu)) == qw(0u, 2u, 0u, 1u));
    CHECK(bin(mmi::padduh, qh(0xFFFF, 0x8000, 1, 0, 0, 0, 0, 0xFFFE), qh(1, 0x8000, 2, 0, 0, 0, 0, 1)) ==
          qh(0xFFFF, 0xFFFF, 3, 0, 0, 0, 0, 0xFFFF));
    CHECK(bin(mmi::psubuh, qh(0, 5, 3, 0x8000, 0, 0, 0, 0), qh(1, 3, 3, 0x7FFF, 0, 0, 0, 0)) == qh(0, 2, 0, 1, 0, 0, 0, 0));
    const u8 a[16] = {0xFF, 0x80, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFE};
    const u8 b[16] = {1, 0x80, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    const u8 sum[16] = {0xFF, 0xFF, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF};
    CHECK(bin(mmi::paddub, qb(a), qb(b)) == qb(sum));
    const u8 c[16] = {0, 5, 3, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const u8 d[16] = {1, 3, 3, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const u8 diff[16] = {0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    CHECK(bin(mmi::psubub, qb(c), qb(d)) == qb(diff));
}

TEST_CASE("padsbh: lower four halfwords subtract, upper four add") {
    // (hand: manual)
    CHECK(bin(mmi::padsbh, qh(10, 10, 10, 10, 10, 10, 10, 10), qh(1, 2, 3, 4, 5, 6, 7, 8)) == qh(9, 8, 7, 6, 15, 16, 17, 18));
}

// ------------------------------------------------------------------------------------------------
// Compare, min/max, logical
// ------------------------------------------------------------------------------------------------
TEST_CASE("pcgtw/pcgth/pcgtb: signed greater-than produces all-ones masks") {
    // (hand: manual)
    CHECK(bin(mmi::pcgtw, qw(5u, 0xFFFFFFFFu, 0u, 0x80000000u), qw(4u, 0u, 0u, 0x7FFFFFFFu)) == qw(0xFFFFFFFFu, 0u, 0u, 0u));
    CHECK(bin(mmi::pcgth, qh(0x8000, 2, 0x7FFF, 0, 0, 0, 0, 1), qh(1, 1, 0x8000, 0, 0, 0, 0, 1)) ==
          qh(0, 0xFFFF, 0xFFFF, 0, 0, 0, 0, 0));
    const u8 a[16] = {0x80, 2, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    const u8 b[16] = {0x7F, 1, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    const u8 r[16] = {0, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    CHECK(bin(mmi::pcgtb, qb(a), qb(b)) == qb(r));
}

TEST_CASE("pceqw/pceqh/pceqb: equality masks") {
    // (hand: manual)
    CHECK(bin(mmi::pceqw, qw(1u, 2u, 0x80000000u, 0u), qw(1u, 3u, 0x80000000u, 1u)) == qw(0xFFFFFFFFu, 0u, 0xFFFFFFFFu, 0u));
    CHECK(bin(mmi::pceqh, qh(1, 2, 3, 4, 5, 6, 7, 8), qh(1, 0, 3, 0, 5, 0, 7, 0)) ==
          qh(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0));
    const u8 a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    const u8 b[16] = {1, 0, 3, 0, 5, 0, 7, 0, 9, 0, 11, 0, 13, 0, 15, 0};
    const u8 r[16] = {0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0};
    CHECK(bin(mmi::pceqb, qb(a), qb(b)) == qb(r));
}

TEST_CASE("pmaxw/pminw/pmaxh/pminh: signed selection") {
    // (hand: manual)
    const u128 s = qw(0x80000000u, 5u, 0u, 0xFFFFFFFFu), t = qw(0x7FFFFFFFu, static_cast<u32>(-5), 0u, 1u);
    CHECK(bin(mmi::pmaxw, s, t) == qw(0x7FFFFFFFu, 5u, 0u, 1u));
    CHECK(bin(mmi::pminw, s, t) == qw(0x80000000u, static_cast<u32>(-5), 0u, 0xFFFFFFFFu));
    const u128 sh_ = qh(0x8000, 5, 0, 0xFFFF, 1, 2, 3, 4), th = qh(0x7FFF, 0xFFFB, 0, 1, 1, 2, 3, 4);
    CHECK(bin(mmi::pmaxh, sh_, th) == qh(0x7FFF, 5, 0, 1, 1, 2, 3, 4));
    CHECK(bin(mmi::pminh, sh_, th) == qh(0x8000, 0xFFFB, 0, 0xFFFF, 1, 2, 3, 4));
}

TEST_CASE("pand/por/pxor/pnor") {
    // (hand: manual)
    const u128 s = qd(0xF0F0F0F0F0F0F0F0ull, 0x00000000FFFFFFFFull), t = qd(0xFF00FF00FF00FF00ull, 0x0F0F0F0F0F0F0F0Full);
    CHECK(bin(mmi::pand, s, t) == qd(0xF000F000F000F000ull, 0x000000000F0F0F0Full));
    CHECK(bin(mmi::por, s, t) == qd(0xFFF0FFF0FFF0FFF0ull, 0x0F0F0F0FFFFFFFFFull));
    CHECK(bin(mmi::pxor, s, t) == qd(0x0FF00FF00FF00FF0ull, 0x0F0F0F0FF0F0F0F0ull));
    CHECK(bin(mmi::pnor, s, t) == qd(0x000F000F000F000Full, 0xF0F0F0F000000000ull));
}

// ------------------------------------------------------------------------------------------------
// Pack / unpack / permute
// ------------------------------------------------------------------------------------------------
TEST_CASE("pextlw/pextuw: interleave the low / high words of rt (even lanes) and rs (odd lanes)") {
    // (hand: manual) PEXTLW rd = {rs.w1, rt.w1, rs.w0, rt.w0}; PEXTUW rd = {rs.w3, rt.w3, rs.w2, rt.w2}.
    const u128 s = qw(0x11u, 0x22u, 0x33u, 0x44u), t = qw(0xAAu, 0xBBu, 0xCCu, 0xDDu);
    CHECK(bin(mmi::pextlw, s, t) == qw(0xAAu, 0x11u, 0xBBu, 0x22u));
    CHECK(bin(mmi::pextuw, s, t) == qw(0xCCu, 0x33u, 0xDDu, 0x44u));
}

TEST_CASE("pextlh/pextuh and pextlb/pextub") {
    // (hand: manual) rs = 0x10.. bytes, rt = 0x00.. bytes.
    const u128 s = qseq(0x10), t = qseq(0x00);
    // halfwords: s.h[i] = 0x(11+2i)(10+2i), t.h[i] = 0x(01+2i)(00+2i)
    CHECK(bin(mmi::pextlh, s, t) == qh(0x0100, 0x1110, 0x0302, 0x1312, 0x0504, 0x1514, 0x0706, 0x1716));
    CHECK(bin(mmi::pextuh, s, t) == qh(0x0908, 0x1918, 0x0B0A, 0x1B1A, 0x0D0C, 0x1D1C, 0x0F0E, 0x1F1E));
    const u8 lb[16] = {0x00, 0x10, 0x01, 0x11, 0x02, 0x12, 0x03, 0x13, 0x04, 0x14, 0x05, 0x15, 0x06, 0x16, 0x07, 0x17};
    const u8 ub[16] = {0x08, 0x18, 0x09, 0x19, 0x0A, 0x1A, 0x0B, 0x1B, 0x0C, 0x1C, 0x0D, 0x1D, 0x0E, 0x1E, 0x0F, 0x1F};
    CHECK(bin(mmi::pextlb, s, t) == qb(lb));
    CHECK(bin(mmi::pextub, s, t) == qb(ub));
}

TEST_CASE("ppacw/ppach/ppacb: keep the low half of each lane, rt low, rs high") {
    // (hand: manual) PPACW rd = {rs.w2, rs.w0, rt.w2, rt.w0}.
    const u128 s = qw(0x11u, 0x22u, 0x33u, 0x44u), t = qw(0xAAu, 0xBBu, 0xCCu, 0xDDu);
    CHECK(bin(mmi::ppacw, s, t) == qw(0xAAu, 0xCCu, 0x11u, 0x33u));
    // PPACH: even halfwords of rt then of rs. Only the low 16 bits of each word survive (no saturation).
    const u128 s2 = qseq(0x10), t2 = qseq(0x00);
    CHECK(bin(mmi::ppach, s2, t2) == qh(0x0100, 0x0504, 0x0908, 0x0D0C, 0x1110, 0x1514, 0x1918, 0x1D1C));
    CHECK(bin(mmi::ppach, qw(0xFFFF8000u, 0x7FFF1234u, 0u, 0u), qw(0x12345678u, 0xABCD0000u, 0u, 0u)) ==
          qh(0x5678, 0x0000, 0, 0, 0x8000, 0x1234, 0, 0));
    // PPACB: even bytes of rt then of rs; a 0xFF low byte is kept, not saturated.
    const u8 pb[16] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E};
    CHECK(bin(mmi::ppacb, s2, t2) == qb(pb));
    const u8 hi_bytes[16] = {0xFF, 0x80, 0x7F, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    const u8 packed[16] = {0xFF, 0x7F, 0, 0, 0, 0, 0, 0, 0xFF, 0x7F, 0, 0, 0, 0, 0, 0};
    CHECK(bin(mmi::ppacb, qb(hi_bytes), qb(hi_bytes)) == qb(packed));
}

TEST_CASE("pinth/pinteh: halfword interleave") {
    // (hand: manual) PINTH rd = {rs.h7, rt.h3, rs.h6, rt.h2, rs.h5, rt.h1, rs.h4, rt.h0}.
    const u128 s = qh(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17), t = qh(0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27);
    CHECK(bin(mmi::pinth, s, t) == qh(0x20, 0x14, 0x21, 0x15, 0x22, 0x16, 0x23, 0x17));
    // PINTEH rd = {rs.h6, rt.h6, rs.h4, rt.h4, rs.h2, rt.h2, rs.h0, rt.h0}.
    CHECK(bin(mmi::pinteh, s, t) == qh(0x20, 0x10, 0x22, 0x12, 0x24, 0x14, 0x26, 0x16));
}

TEST_CASE("pcpyld/pcpyud: doubleword copies") {
    // (hand: manual) PCPYLD rd = {rs.lo, rt.lo}; PCPYUD rd = {rt.hi, rs.hi}.
    const u128 s = qd(0x1111111111111111ull, 0x2222222222222222ull), t = qd(0xAAAAAAAAAAAAAAAAull, 0xBBBBBBBBBBBBBBBBull);
    CHECK(bin(mmi::pcpyld, s, t) == qd(0xAAAAAAAAAAAAAAAAull, 0x1111111111111111ull));
    CHECK(bin(mmi::pcpyud, s, t) == qd(0x2222222222222222ull, 0xBBBBBBBBBBBBBBBBull));
}

TEST_CASE("pabsw/pabsh: absolute value saturates the minimum") {
    // (hand: manual)
    CHECK(un(mmi::pabsw, qw(0x80000000u, static_cast<u32>(-5), 7u, 0u)) == qw(0x7FFFFFFFu, 5u, 7u, 0u));
    CHECK(un(mmi::pabsh, qh(0x8000, 0xFFFB, 7, 0, 0x8001, 0x7FFF, 0xFFFF, 1)) == qh(0x7FFF, 5, 7, 0, 0x7FFF, 0x7FFF, 1, 1));
}

TEST_CASE("pcpyh/pexch/pexcw/pexeh/pexew/prevh/prot3w: fixed permutations") {
    // (hand: manual)
    const u128 h = qh(0, 1, 2, 3, 4, 5, 6, 7), w = qw(0, 1, 2, 3);
    CHECK(un(mmi::pcpyh, h) == qh(0, 0, 0, 0, 4, 4, 4, 4));
    CHECK(un(mmi::pexch, h) == qh(0, 2, 1, 3, 4, 6, 5, 7));  // exchange centre halfwords of each doubleword
    CHECK(un(mmi::pexcw, w) == qw(0, 2, 1, 3));              // exchange centre words
    CHECK(un(mmi::pexeh, h) == qh(2, 1, 0, 3, 6, 5, 4, 7));  // exchange even halfwords
    CHECK(un(mmi::pexew, w) == qw(2, 1, 0, 3));              // exchange even words
    CHECK(un(mmi::prevh, h) == qh(3, 2, 1, 0, 7, 6, 5, 4));  // reverse within each doubleword
    CHECK(un(mmi::prot3w, w) == qw(1, 2, 0, 3));             // rotate the low three words
}

TEST_CASE("pext5/ppac5: 1:5:5:5 <-> 8:8:8:8 colour expansion") {
    // (hand: manual) PEXT5: R -> bits 7..3, G -> 15..11, B -> 23..19, A -> 31; the upper 16 input bits are ignored.
    CHECK(un(mmi::pext5, qw(0xFFFFu, 0x0001u, 0x8000u, 0xFFFF0000u)) == qw(0x80F8F8F8u, 0x00000008u, 0x80000000u, 0u));
    // 0x1234 = R 20, G 17, B 4, A 0 -> (20 << 3) | (17 << 11) | (4 << 19) = 0x002088A0.
    CHECK(un(mmi::pext5, qw(0x001Fu, 0x03E0u, 0x7C00u, 0x1234u)) == qw(0x000000F8u, 0x0000F800u, 0x00F80000u, 0x002088A0u));
    // PPAC5 is the inverse; the low 3 bits of each component are dropped.
    CHECK(un(mmi::ppac5, qw(0x80F8F8F8u, 0xFFFFFFFFu, 0x00000008u, 0x00000007u)) == qw(0xFFFFu, 0xFFFFu, 0x0001u, 0u));
    CHECK(un(mmi::ppac5, qw(0x002088A0u, 0u, 0u, 0u)) == qw(0x1234u, 0u, 0u, 0u));
}

// ------------------------------------------------------------------------------------------------
// Shifts
// ------------------------------------------------------------------------------------------------
TEST_CASE("psllh/psrlh/psrah: halfword shifts by 0, 1, 15 and the sa[3:0] mask") {
    const u128 t = qh(0x8001, 0x0001, 0x8000, 0xFFFF, 0x7FFF, 0x4000, 0x0002, 0x0000);
    // (hand: manual)
    CHECK(sh(mmi::psllh, t, 0) == t);
    CHECK(sh(mmi::psllh, t, 1) == qh(0x0002, 0x0002, 0x0000, 0xFFFE, 0xFFFE, 0x8000, 0x0004, 0x0000));
    CHECK(sh(mmi::psllh, t, 15) == qh(0x8000, 0x8000, 0x0000, 0x8000, 0x8000, 0x0000, 0x0000, 0x0000));
    CHECK(sh(mmi::psrlh, t, 15) == qh(0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000));
    CHECK(sh(mmi::psrlh, t, 1) == qh(0x4000, 0x0000, 0x4000, 0x7FFF, 0x3FFF, 0x2000, 0x0001, 0x0000));
    CHECK(sh(mmi::psrah, t, 15) == qh(0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000));
    CHECK(sh(mmi::psrah, t, 1) == qh(0xC000, 0x0000, 0xC000, 0xFFFF, 0x3FFF, 0x2000, 0x0001, 0x0000));
    // (PCSX2 2.8.2 observed: mmi_1741, the sa = 16 and 31 shift vectors) only sa[3:0] is used, so 16 behaves like 0.
    CHECK(sh(mmi::psllh, t, 16) == t);
    CHECK(sh(mmi::psrah, t, 17) == sh(mmi::psrah, t, 1));
}

TEST_CASE("psllw/psrlw/psraw: word shifts by 0, 1 and 31") {
    const u128 t = qw(0x80000001u, 0x00000001u, 0x80000000u, 0x7FFFFFFFu);
    // (hand: manual)
    CHECK(sh(mmi::psllw, t, 0) == t);
    CHECK(sh(mmi::psllw, t, 31) == qw(0x80000000u, 0x80000000u, 0u, 0x80000000u));
    CHECK(sh(mmi::psllw, t, 1) == qw(0x00000002u, 0x00000002u, 0u, 0xFFFFFFFEu));
    CHECK(sh(mmi::psrlw, t, 31) == qw(1u, 0u, 1u, 0u));
    CHECK(sh(mmi::psraw, t, 31) == qw(0xFFFFFFFFu, 0u, 0xFFFFFFFFu, 0u));
    CHECK(sh(mmi::psraw, t, 1) == qw(0xC0000000u, 0u, 0xC0000000u, 0x3FFFFFFFu));
    CHECK(sh(mmi::psraw, t, 0) == t);
}

TEST_CASE("psllvw/psrlvw/psravw: lanes 0 and 2, shift count from rs, results sign-extended to 64 bits") {
    // (hand: manual) rs.w0 = 4, rs.w2 = 31; odd words of rs/rt are ignored.
    const u128 s = qw(4u, 0xDEADBEEFu, 31u, 0xDEADBEEFu);
    CHECK(bin(mmi::psllvw, s, qw(0x10000001u, 0xDEADBEEFu, 1u, 0xDEADBEEFu)) == qd(0x0000000000000010ull, 0xFFFFFFFF80000000ull));
    CHECK(bin(mmi::psrlvw, s, qw(0x80000000u, 0u, 0x80000000u, 0u)) == qd(0x0000000008000000ull, 0x0000000000000001ull));
    CHECK(bin(mmi::psravw, s, qw(0x80000000u, 0u, 0x80000000u, 0u)) == qd(0xFFFFFFFFF8000000ull, 0xFFFFFFFFFFFFFFFFull));
    // shift count 0 and the & 31 mask (32 behaves like 0): PSRLVW of 0x80000000 by 0 sign-extends the word.
    const u128 z = qw(0u, 0u, 32u, 0u);
    CHECK(bin(mmi::psrlvw, z, qw(0x80000000u, 0u, 0x80000000u, 0u)) == qd(0xFFFFFFFF80000000ull, 0xFFFFFFFF80000000ull));
    CHECK(bin(mmi::psravw, qw(30u, 0u, 0u, 0u), qw(0x40000000u, 0u, 7u, 0u)) == qd(1ull, 7ull));
}

TEST_CASE("plzcw: leading sign bits minus one, low two words only") {
    // (hand: manual) the count excludes the sign bit itself: 0 and -1 give 31; 1 gives 30; 0x80000000 and
    // 0x7FFFFFFF give 0; 0x00008000 (16 leading zeros) and 0xFFFF7FFF (16 leading ones) give 15.
    u128 d = qd(0ull, 0xCAFEBABECAFEBABEull);
    mmi::plzcw(d, qw(0u, 0xFFFFFFFFu, 0u, 0u));
    CHECK(d == qd(0x0000001F0000001Full, 0xCAFEBABECAFEBABEull)); // upper half untouched (PCSX2 2.8.2 observed: mmi_1882)
    mmi::plzcw(d, qw(1u, 0x80000000u, 0u, 0u));
    CHECK(d.u32[0] == 30u);
    CHECK(d.u32[1] == 0u);
    mmi::plzcw(d, qw(0x7FFFFFFFu, 0x00008000u, 0u, 0u));
    CHECK(d.u32[0] == 0u);
    CHECK(d.u32[1] == 15u);
    mmi::plzcw(d, qw(0xFFFF7FFFu, 0x00000002u, 0u, 0u));
    CHECK(d.u32[0] == 15u);
    CHECK(d.u32[1] == 29u);
}

TEST_CASE("qfsrv: funnel shift right of {rs:rt} by SA bytes") {
    // (hand: manual) rt occupies the low 16 bytes of the 32-byte window, rs the high 16.
    const u128 s = qseq(0x10), t = qseq(0x00);
    u128 d{};
    mmi::qfsrv(d, s, t, 0u);
    CHECK(d == t);
    mmi::qfsrv(d, s, t, 8u);
    CHECK(d == qd(t.u64[1], s.u64[0]));
    mmi::qfsrv(d, s, t, 15u);
    const u8 e15[16] = {0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
    CHECK(d == qb(e15));
    mmi::qfsrv(d, s, t, 1u);
    const u8 e1[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    CHECK(d == qb(e1));
    // Through the context: MTSAB rs=0, imm=8 -> SA = 64 bits -> 8 bytes.
    EEContext c;
    mtsab(c, 0u, 8u);
    mmi::qfsrv(c, d, s, t);
    CHECK(d == qd(t.u64[1], s.u64[0]));
    // MTSAH rs=0, imm=1 -> SA = 16 bits -> 2 bytes.
    mtsah(c, 0u, 1u);
    mmi::qfsrv(c, d, s, t);
    const u8 e2[16] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11};
    CHECK(d == qb(e2));
}

// ------------------------------------------------------------------------------------------------
// Multiply / divide through HI/LO
// ------------------------------------------------------------------------------------------------
TEST_CASE("pmultw/pmultuw: lanes 0 and 2 into rd and both HI/LO pipes") {
    EEContext c;
    u128 d{};
    // (hand: manual) -2 * 3 = -6 on pipe 0; 0x7FFFFFFF * 2 = 0xFFFFFFFE on pipe 1.
    mmi::pmultw(c, d, qw(static_cast<u32>(-2), 0xDEADBEEFu, 0x7FFFFFFFu, 0xDEADBEEFu), qw(3u, 0xDEADBEEFu, 2u, 0xDEADBEEFu));
    CHECK(d == qd(0xFFFFFFFFFFFFFFFAull, 0x00000000FFFFFFFEull));
    CHECK(c.lo.u64[0] == 0xFFFFFFFFFFFFFFFAull);
    CHECK(c.hi.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.lo.u64[1] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(c.hi.u64[1] == 0u);
    // (hand: manual) unsigned: 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE_00000001.
    mmi::pmultuw(c, d, qw(0xFFFFFFFFu, 0u, 2u, 0u), qw(0xFFFFFFFFu, 0u, 0x80000000u, 0u));
    CHECK(d == qd(0xFFFFFFFE00000001ull, 0x0000000100000000ull));
    CHECK(c.lo.u64[0] == 1u);
    CHECK(c.hi.u64[0] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(c.lo.u64[1] == 0u);
    CHECK(c.hi.u64[1] == 1u);
}

TEST_CASE("pmaddw/pmsubw/pmadduw: accumulate {HI,LO} per pipe") {
    EEContext c;
    u128 d{};
    // (hand: manual) start from pipe0 = -6, pipe1 = 0xFFFFFFFE (from pmultw above).
    mmi::pmultw(c, d, qw(static_cast<u32>(-2), 0u, 0x7FFFFFFFu, 0u), qw(3u, 0u, 2u, 0u));
    mmi::pmaddw(c, d, qw(2u, 0u, 1u, 0u), qw(3u, 0u, 1u, 0u));
    CHECK(d == qd(0ull, 0x00000000FFFFFFFFull));
    CHECK(c.lo.u64[0] == 0u);
    CHECK(c.hi.u64[0] == 0u);
    CHECK(c.lo.u64[1] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(c.hi.u64[1] == 0u);
    // (hand: manual) PMSUBW from zero: 0 - 2*3 = -6.
    EEContext z;
    mmi::pmsubw(z, d, qw(2u, 0u, 0u, 0u), qw(3u, 0u, 0u, 0u));
    CHECK(d.u64[0] == 0xFFFFFFFFFFFFFFFAull);
    CHECK(z.lo.u64[0] == 0xFFFFFFFFFFFFFFFAull);
    CHECK(z.hi.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    CHECK(d.u64[1] == 0u);
    // (hand: manual) PMADDUW from zero: 0xFFFFFFFF * 2 = 0x1_FFFFFFFE.
    EEContext u;
    mmi::pmadduw(u, d, qw(0xFFFFFFFFu, 0u, 0u, 0u), qw(2u, 0u, 0u, 0u));
    CHECK(d.u64[0] == 0x00000001FFFFFFFEull);
    CHECK(u.lo.u64[0] == 0xFFFFFFFFFFFFFFFEull);
    CHECK(u.hi.u64[0] == 1u);
}

TEST_CASE("pdivw/pdivuw: lanes 0 and 2 into pipes 0 and 1") {
    EEContext c;
    // (hand: manual) -7 / 2 on pipe 0; (PCSX2 2.8.2 observed: mmi_2009) 100 / 0 on pipe 1.
    mmi::pdivw(c, qw(static_cast<u32>(-7), 0u, 100u, 0u), qw(2u, 0u, 0u, 0u));
    CHECK(c.lo.s64[0] == -3);
    CHECK(c.hi.s64[0] == -1);
    CHECK(c.lo.s64[1] == -1);
    CHECK(c.hi.s64[1] == 100);
    // (hand: manual) 0xFFFFFFFF / 16; (PCSX2 2.8.2 observed: mmi_2017) 7 / 0.
    mmi::pdivuw(c, qw(0xFFFFFFFFu, 0u, 7u, 0u), qw(16u, 0u, 0u, 0u));
    CHECK(c.lo.u64[0] == 0x0FFFFFFFu);
    CHECK(c.hi.u64[0] == 0xFu);
    CHECK(c.lo.s64[1] == -1);
    CHECK(c.hi.s64[1] == 7);
}

TEST_CASE("pdivbw: four words divided by rt.h0") {
    EEContext c;
    // (hand: manual) divisor 3: quotients truncate toward zero, remainders carry the dividend's sign.
    mmi::pdivbw(c, qw(100u, static_cast<u32>(-100), 7u, 0x80000000u), qw(3u, 0u, 0u, 0u));
    CHECK(c.lo.s32[0] == 33);
    CHECK(c.lo.s32[1] == -33);
    CHECK(c.lo.s32[2] == 2);
    CHECK(c.lo.s32[3] == -715827882);
    CHECK(c.hi.s32[0] == 1);
    CHECK(c.hi.s32[1] == -1);
    CHECK(c.hi.s32[2] == 1);
    CHECK(c.hi.s32[3] == -2);
    // (PCSX2 2.8.2 observed: mmi_2026, mmi_2027) divisor 0 and INT32_MIN / -1.
    mmi::pdivbw(c, qw(5u, static_cast<u32>(-5), 0u, 0u), qw(0u, 0u, 0u, 0u));
    CHECK(c.lo.s32[0] == -1);
    CHECK(c.hi.s32[0] == 5);
    CHECK(c.lo.s32[1] == 1);
    CHECK(c.hi.s32[1] == -5);
    mmi::pdivbw(c, qw(0x80000000u, 0u, 0u, 0u), qw(0xFFFFu, 0u, 0u, 0u));
    CHECK(c.lo.s32[0] == INT32_MIN);
    CHECK(c.hi.s32[0] == 0);
}

TEST_CASE("pmulth/pmaddh/pmsubh: eight halfword products spread over HI/LO") {
    EEContext c;
    u128 d{};
    const u128 s = qh(1, 2, 3, 4, 5, 6, 7, 8), t = qh(2, 2, 2, 2, 2, 2, 2, 2);
    // (hand: manual) LO = {p0, p1, p4, p5}, HI = {p2, p3, p6, p7}, rd = {LO.w0, HI.w0, LO.w2, HI.w2}.
    mmi::pmulth(c, d, s, t);
    CHECK(c.lo == qw(2u, 4u, 10u, 12u));
    CHECK(c.hi == qw(6u, 8u, 14u, 16u));
    CHECK(d == qw(2u, 6u, 10u, 14u));
    mmi::pmaddh(c, d, s, t);
    CHECK(c.lo == qw(4u, 8u, 20u, 24u));
    CHECK(c.hi == qw(12u, 16u, 28u, 32u));
    CHECK(d == qw(4u, 12u, 20u, 28u));
    mmi::pmsubh(c, d, s, t);
    mmi::pmsubh(c, d, s, t);
    CHECK(c.lo == qw(0u, 0u, 0u, 0u));
    CHECK(c.hi == qw(0u, 0u, 0u, 0u));
    CHECK(d == qw(0u, 0u, 0u, 0u));
    // (hand: manual) INT16_MIN * INT16_MIN = 2^30 fits a word; -1 * 1 = -1.
    mmi::pmulth(c, d, qh(0x8000, 0xFFFF, 0, 0, 0, 0, 0, 0), qh(0x8000, 1, 0, 0, 0, 0, 0, 0));
    CHECK(c.lo.u32[0] == 0x40000000u);
    CHECK(c.lo.u32[1] == 0xFFFFFFFFu);
}

TEST_CASE("phmadh/phmsbh: horizontal pair sums into the even words of HI/LO") {
    EEContext c;
    c.lo = qw(0xDEADBEEFu, 0xDEADBEEFu, 0xDEADBEEFu, 0xDEADBEEFu);
    c.hi = c.lo;
    u128 d{};
    const u128 s = qh(1, 2, 3, 4, 5, 6, 7, 8), t = qh(1, 1, 1, 1, 1, 1, 1, 1);
    // (hand: manual) LO.w0 = p1+p0, HI.w0 = p3+p2, LO.w2 = p5+p4, HI.w2 = p7+p6.
    mmi::phmadh(c, d, s, t);
    CHECK(d == qw(3u, 7u, 11u, 15u));
    CHECK(c.lo.u32[0] == 3u);
    CHECK(c.hi.u32[0] == 7u);
    CHECK(c.lo.u32[2] == 11u);
    CHECK(c.hi.u32[2] == 15u);
    // (upstream behaviour, deliberate disagreement) the odd words are undefined in the manual and left unchanged here;
    // PCSX2 stores the odd products p1/p3/p5/p7 there (PHMSBH: their one's complements) -- tests/ee/vectors status
    // "disagree:phmadh-odd-words" (mmi_2056, mmi_2066).
    CHECK(c.lo.u32[1] == 0xDEADBEEFu);
    CHECK(c.hi.u32[3] == 0xDEADBEEFu);
    // (hand: manual) PHMSBH: p1-p0 ...
    mmi::phmsbh(c, d, s, t);
    CHECK(d == qw(1u, 1u, 1u, 1u));
    mmi::phmsbh(c, d, qh(0x8000, 0x7FFF, 0, 0, 0, 0, 0, 0), qh(0x7FFF, 0x8000, 0, 0, 0, 0, 0, 0));
    // p1 - p0 = (-32767*32768) - (-32768*32767) = 0
    CHECK(d.u32[0] == 0u);
}

TEST_CASE("pmfhl.lw/.uw/.slw/.lh/.sh: HI/LO rearrangements and saturation") {
    EEContext c;
    c.lo = qw(0x4C000000u, 0x4C111111u, 0x4C222222u, 0x4C333333u);
    c.hi = qw(0x48000000u, 0x48111111u, 0x48222222u, 0x48333333u);
    u128 d{};
    // (hand: manual) LW picks the even words, UW the odd words.
    mmi::pmfhl_lw(c, d);
    CHECK(d == qw(0x4C000000u, 0x48000000u, 0x4C222222u, 0x48222222u));
    mmi::pmfhl_uw(c, d);
    CHECK(d == qw(0x4C111111u, 0x48111111u, 0x4C333333u, 0x48333333u));
    mmi::pmfhl(c, d, 0u);
    CHECK(d == qw(0x4C000000u, 0x48000000u, 0x4C222222u, 0x48222222u));
    // (hand: manual) LH: {HI.h6, HI.h4, LO.h6, LO.h4, HI.h2, HI.h0, LO.h2, LO.h0}.
    c.lo = qh(0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17);
    c.hi = qh(0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27);
    mmi::pmfhl_lh(c, d);
    CHECK(d == qh(0x10, 0x12, 0x20, 0x22, 0x14, 0x16, 0x24, 0x26));
    // (hand: manual) SLW: {HI.w0:LO.w0} and {HI.w2:LO.w2} saturated to signed 32 bits, sign-extended.
    c.lo = qw(0x7FFFFFFFu, 0u, 0u, 0u);
    c.hi = qw(0u, 0u, 1u, 0u);
    mmi::pmfhl_slw(c, d);
    CHECK(d == qd(0x000000007FFFFFFFull, 0x000000007FFFFFFFull));
    c.lo = qw(0x80000000u, 0u, 0xFFFFFFFFu, 0u);
    c.hi = qw(0xFFFFFFFFu, 0u, 0xFFFFFFFEu, 0u);
    mmi::pmfhl_slw(c, d);
    CHECK(d == qd(0xFFFFFFFF80000000ull, 0xFFFFFFFF80000000ull));
    // (hand: manual) SH: each word saturated to a signed halfword.
    c.lo = qw(0x12345u, static_cast<u32>(-0x12345), 0x1234u, 0xFFFF8000u);
    c.hi = qw(0x8000u, 0x7FFFu, 0xFFFFFFFFu, 0u);
    mmi::pmfhl_sh(c, d);
    CHECK(d == qh(0x7FFF, 0x8000, 0x7FFF, 0x7FFF, 0x1234, 0x8000, 0xFFFF, 0));
    // (upstream behaviour, deliberate disagreement) reserved formats behave like SH here; PCSX2's recompiler leaves rd
    // unchanged (mmi_3440..3442, "disagree:pmfhl-reserved"; its interpreter trapped before reaching them). The decoder
    // never accepts these formats (census: pmfhl.lw only).
    u128 d2{};
    mmi::pmfhl(c, d2, 5u);
    CHECK(d2 == d);
}

TEST_CASE("pmthl.lw: words of rs into the even words of LO/HI, odd words untouched") {
    EEContext c;
    c.lo = qw(0xDEADBEEFu, 0xDEADBEEFu, 0xDEADBEEFu, 0xDEADBEEFu);
    c.hi = c.lo;
    // (hand: manual)
    mmi::pmthl(c, qw(0xA0u, 0xB0u, 0xC0u, 0xD0u));
    CHECK(c.lo == qw(0xA0u, 0xDEADBEEFu, 0xC0u, 0xDEADBEEFu));
    CHECK(c.hi == qw(0xB0u, 0xDEADBEEFu, 0xD0u, 0xDEADBEEFu));
    // PMFHL.LW undoes it.
    u128 d{};
    mmi::pmfhl_lw(c, d);
    CHECK(d == qw(0xA0u, 0xB0u, 0xC0u, 0xD0u));
}

TEST_CASE("pmfhi/pmflo/pmthi/pmtlo: whole-register moves") {
    EEContext c;
    const u128 a = qd(0x0123456789ABCDEFull, 0xFEDCBA9876543210ull), b = qd(0x1111111111111111ull, 0x2222222222222222ull);
    // (hand: manual)
    mmi::pmthi(c, a);
    mmi::pmtlo(c, b);
    CHECK(c.hi == a);
    CHECK(c.lo == b);
    u128 d{};
    mmi::pmfhi(c, d);
    CHECK(d == a);
    mmi::pmflo(c, d);
    CHECK(d == b);
}

// ------------------------------------------------------------------------------------------------
// LQ / SQ
// ------------------------------------------------------------------------------------------------
TEST_CASE("lq/sq ignore the low four address bits") {
    EEMemory mem;
    const u128 v = qseq(0xA0);
    // (hand: manual) SQ to 0x10F lands on the quadword at 0x100; the neighbours stay zero.
    mmi::sq(mem, 0x10Fu, v);
    CHECK(mem.read<u32>(0x100u) == 0xA3A2A1A0u);
    CHECK(mem.read<u32>(0x10Cu) == 0xAFAEADACu);
    CHECK(mem.read<u32>(0x0FCu) == 0u);
    CHECK(mem.read<u32>(0x110u) == 0u);
    // LQ from any address inside the quadword returns the whole quadword.
    CHECK(mmi::lq(mem, 0x100u) == v);
    CHECK(mmi::lq(mem, 0x107u) == v);
    CHECK(mmi::lq(mem, 0x10Fu) == v);
    CHECK(mmi::lq(mem, 0x110u) == qd(0ull, 0ull));
    // Scratchpad is reachable too.
    mmi::sq(mem, EEMemory::kScratchpadBase + 0x21u, v);
    CHECK(mmi::lq(mem, EEMemory::kScratchpadBase + 0x2Fu) == v);
    CHECK(mem.unmapped_accesses() == 0u);
}
