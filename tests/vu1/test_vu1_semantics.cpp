// Hand-built semantic vectors for the VU1 interpreter. Each TEST_CASE name carries its provenance tag:
//   (hand: VU User's Manual)                  derived by hand from the manual's definition of the operation
//   (upstream behaviour, hardware-unverified) what ps2-web-recomp @ c0f476e does; no hardware/PCSX2 check yet
// Programs end with an E pair plus its delay pair unless the test is about control flow.
#include "vu1_test_util.h"

using namespace p3fes;
using namespace p3fes::vu1;
using namespace p3fes::vu1::test;

namespace {

std::vector<u8> bytes_of(const std::vector<Pair>& pairs) {
    std::vector<u8> out;
    for (const Pair& p : pairs) {
        u8 b[8];
        std::memcpy(b, &p.lo, 4);
        std::memcpy(b + 4, &p.hi, 4);
        out.insert(out.end(), b, b + 8);
    }
    return out;
}

// body + {E nop | nop} + {nop | nop}, loaded at micro address 0.
std::unique_ptr<VU1Interpreter> build(std::vector<Pair> body, IGifSink* sink = nullptr) {
    body.push_back({UNOP | E_BIT, LNOP});
    body.push_back({UNOP, LNOP});
    auto vu = std::make_unique<VU1Interpreter>(sink);
    vu->load_micro(0, bytes_of(body));
    return vu;
}

void ended(VU1Interpreter& vu) {
    const RunResult r = vu.mscal(0);
    REQUIRE(r.status == RunStatus::Ended);
}

void check_vf(const VU1State& s, u32 r, float x, float y, float z, float w) {
    CAPTURE(r);
    CHECK(s.vf[r][0] == f2u(x));
    CHECK(s.vf[r][1] == f2u(y));
    CHECK(s.vf[r][2] == f2u(z));
    CHECK(s.vf[r][3] == f2u(w));
}

constexpr u32 kMax = 0x7FFFFFFFu;

} // namespace

// ---- FMAC arithmetic, dest masks, broadcast, I/Q sources --------------------------------------------------------

TEST_CASE("ADD.xyzw adds lane-wise (hand: VU User's Manual)") {
    auto vu = build({{u_add(XYZW, 3, 1, 2), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 0.5f, 0.5f, 0.5f, 0.5f);
    ended(*vu);
    check_vf(vu->state(), 3, 1.5f, 2.5f, 3.5f, 4.5f);
}

TEST_CASE("dest mask .xz writes only x and z (hand: VU User's Manual)") {
    auto vu = build({{u_add(X | Z, 3, 1, 2), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 0.5f, 0.5f, 0.5f, 0.5f);
    set_vf(vu->state(), 3, 9, 9, 9, 9);
    ended(*vu);
    check_vf(vu->state(), 3, 1.5f, 9, 3.5f, 9);
}

TEST_CASE("ADDy broadcasts ft.y to every lane (hand: VU User's Manual)") {
    auto vu = build({{u_addbc(XYZW, 3, 1, 2, by), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 10, 20, 30, 40);
    ended(*vu);
    check_vf(vu->state(), 3, 21, 22, 23, 24);
}

TEST_CASE("MULx and SUBw broadcast forms (hand: VU User's Manual)") {
    auto vu = build({{u_mulbc(XYZW, 3, 1, 2, bx), LNOP}, {u_subbc(XYZW, 4, 1, 2, bw), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 10, 20, 30, 40);
    ended(*vu);
    check_vf(vu->state(), 3, 10, 20, 30, 40);
    check_vf(vu->state(), 4, -39, -38, -37, -36);
}

TEST_CASE("MULA then MADD accumulates ACC + fs*ft (hand: VU User's Manual)") {
    auto vu = build({{u_mula(XYZW, 1, 2), LNOP}, {u_madd(XYZW, 3, 1, 2), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 2, 2, 2, 2);
    ended(*vu);
    CHECK(vu->state().acc[0] == f2u(2));
    CHECK(vu->state().acc[3] == f2u(8));
    check_vf(vu->state(), 3, 4, 8, 12, 16);
}

TEST_CASE("MSUBx subtracts fs*ft.x from ACC (hand: VU User's Manual)") {
    auto vu = build({{u_mula(XYZW, 1, 2), LNOP}, {u_msubbc(XYZW, 4, 1, 2, bx), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 2, 5, 5, 5);
    ended(*vu);
    check_vf(vu->state(), 4, 0, 6, 9, 12); // ACC = (2, 10, 15, 20) minus vf1 * 2 = (2, 4, 6, 8)
}

TEST_CASE("LOI loads I; MULi in a later pair uses it (hand: VU User's Manual)") {
    auto vu = build({{UNOP | I_BIT, f2u(3.0f)}, {u_muli(XYZW, 3, 1), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    ended(*vu);
    CHECK(vu->state().i == f2u(3.0f));
    check_vf(vu->state(), 3, 3, 6, 9, 12);
}

TEST_CASE("an upper op in the LOI pair reads the previous I (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_muli(XYZW, 3, 1) | I_BIT, f2u(5.0f)}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    vu->state().i = f2u(2.0f);
    ended(*vu);
    check_vf(vu->state(), 3, 2, 4, 6, 8);
    CHECK(vu->state().i == f2u(5.0f));
}

TEST_CASE("ADDi adds I to every lane (hand: VU User's Manual)") {
    auto vu = build({{UNOP | I_BIT, f2u(0.5f)}, {u_addi(XYW, 3, 1), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    ended(*vu);
    check_vf(vu->state(), 3, 1.5f, 2.5f, 0, 4.5f);
}

TEST_CASE("vf00 stays (0, 0, 0, 1) when written (hand: VU User's Manual)") {
    auto vu = build({{u_add(XYZW, 0, 1, 2), l_move(XYZW, 0, 1)}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 1, 1, 1, 1);
    ended(*vu);
    check_vf(vu->state(), 0, 0, 0, 0, 1);
}

TEST_CASE("MAX and MINI pick per lane, sign-aware (hand: VU User's Manual)") {
    auto vu = build({{u_max(XYZW, 3, 1, 2), LNOP}, {u_mini(XYZW, 4, 1, 2), LNOP}});
    set_vf(vu->state(), 1, 1, -2, 3, -4);
    set_vf(vu->state(), 2, -1, 2, -3, 4);
    ended(*vu);
    check_vf(vu->state(), 3, 1, 2, 3, 4);
    check_vf(vu->state(), 4, -1, -2, -3, -4);
}

TEST_CASE("OPMULA + OPMSUB give the cross product, w untouched (hand: VU User's Manual)") {
    auto vu = build({{u_opmula(1, 2), LNOP}, {u_opmsub(3, 2, 1), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 0);
    set_vf(vu->state(), 2, 4, 5, 6, 0);
    set_vf(vu->state(), 3, 0, 0, 0, 7);
    ended(*vu);
    check_vf(vu->state(), 3, -3, 6, -3, 7);
}

// ---- conversions ----------------------------------------------------------------------------------------------

TEST_CASE("FTOI0 truncates toward zero (hand: VU User's Manual)") {
    auto vu = build({{u_ftoi(0, XYZW, 3, 1), LNOP}});
    set_vf(vu->state(), 1, 2.75f, -2.75f, 0.5f, -0.5f);
    ended(*vu);
    CHECK(vu->state().vf[3][0] == 2u);
    CHECK(vu->state().vf[3][1] == static_cast<u32>(-2));
    CHECK(vu->state().vf[3][2] == 0u);
    CHECK(vu->state().vf[3][3] == 0u);
}

TEST_CASE("FTOI4 scales by 16 before truncating (hand: VU User's Manual)") {
    auto vu = build({{u_ftoi(1, XYZW, 3, 1), LNOP}});
    set_vf(vu->state(), 1, 1.5f, -0.0625f, 100.25f, 0.0f);
    ended(*vu);
    CHECK(vu->state().vf[3][0] == 24u);
    CHECK(vu->state().vf[3][1] == 0xFFFFFFFFu);
    CHECK(vu->state().vf[3][2] == 1604u);
    CHECK(vu->state().vf[3][3] == 0u);
}

TEST_CASE("FTOI0 saturates out-of-range values (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_ftoi(0, XYZW, 3, 1), LNOP}});
    set_vf(vu->state(), 1, 3e9f, -3e9f, 2147483648.0f, -2147483648.0f);
    ended(*vu);
    CHECK(vu->state().vf[3][0] == 0x7FFFFFFFu);
    CHECK(vu->state().vf[3][1] == 0x80000000u);
    CHECK(vu->state().vf[3][2] == 0x7FFFFFFFu);
    CHECK(vu->state().vf[3][3] == 0x80000000u);
}

TEST_CASE("ITOF0 and ITOF4 convert fixed point to float (hand: VU User's Manual)") {
    auto vu = build({{u_itof(0, XYZW, 3, 1), LNOP}, {u_itof(1, X | Y, 4, 2), LNOP}});
    VU1State& s = vu->state();
    s.vf[1][0] = 7;
    s.vf[1][1] = static_cast<u32>(-3);
    s.vf[1][2] = 0;
    s.vf[1][3] = static_cast<u32>(-1);
    s.vf[2][0] = 24;
    s.vf[2][1] = static_cast<u32>(-16);
    ended(*vu);
    check_vf(s, 3, 7, -3, 0, -1);
    CHECK(s.vf[4][0] == f2u(1.5f));
    CHECK(s.vf[4][1] == f2u(-1.0f));
}

TEST_CASE("ITOF0 of 2^24+1 truncates to 2^24 (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_itof(0, X, 3, 1), LNOP}});
    vu->state().vf[1][0] = (1u << 24) + 1u;
    ended(*vu);
    CHECK(vu->state().vf[3][0] == f2u(16777216.0f));
}

// ---- CLIP and clip flags --------------------------------------------------------------------------------------

TEST_CASE("CLIP sets +x / -y judgement bits against |w| (hand: VU User's Manual)") {
    auto vu = build({{u_clip(1, 2), LNOP}});
    set_vf(vu->state(), 1, 2, -2, 0.5f, 0);
    set_vf(vu->state(), 2, 0, 0, 0, -1); // |w| = 1
    ended(*vu);
    CHECK(vu->state().clip == 0x09u); // bit 0: x > |w|, bit 3: y < -|w|
}

TEST_CASE("CLIP shifts the previous judgements up by 6 bits (hand: VU User's Manual)") {
    auto vu = build({{u_clip(1, 2), LNOP}, {u_clip(3, 2), LNOP}});
    set_vf(vu->state(), 1, 2, -2, 0.5f, 0);
    set_vf(vu->state(), 2, 0, 0, 0, 1);
    set_vf(vu->state(), 3, 0, 0, -5, 0);
    ended(*vu);
    CHECK(vu->state().clip == ((0x09u << 6) | 0x20u));
}

TEST_CASE("FCAND tests clip bits three pairs after CLIP (hand: VU User's Manual; latency upstream)") {
    auto vu = build({{u_clip(1, 2), LNOP},
                     {UNOP, LNOP},
                     {UNOP, LNOP},
                     {UNOP, l_fcand(0x000001)},
                     {UNOP, l_iaddiu(5, 1, 0)},
                     {UNOP, l_fcand(0x000002)}});
    set_vf(vu->state(), 1, 2, -2, 0.5f, 0);
    set_vf(vu->state(), 2, 0, 0, 0, 1);
    ended(*vu);
    CHECK(vu->state().vi[5] == 1);
    CHECK(vu->state().vi[1] == 0);
}

TEST_CASE("FCAND in the pair after CLIP still sees the old clip flags (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_clip(1, 2), LNOP}, {UNOP, l_fcand(0x000001)}});
    set_vf(vu->state(), 1, 2, 0, 0, 0);
    set_vf(vu->state(), 2, 0, 0, 0, 1);
    ended(*vu);
    CHECK(vu->state().vi[1] == 0);
    CHECK(vu->state().clip == 0x01u);
}

TEST_CASE("FCOR is 1 only when clip | imm covers all 24 bits (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_fcset(0xFFFFF0)}, {UNOP, l_fcor(0x00000F)}, {UNOP, l_iaddiu(5, 1, 0)},
                     {UNOP, l_fcor(0x000007)}});
    ended(*vu);
    CHECK(vu->state().vi[5] == 1);
    CHECK(vu->state().vi[1] == 0);
}

TEST_CASE("FCSET then FCGET returns the low 12 clip bits (hand: VU User's Manual; FCSET visibility upstream)") {
    auto vu = build({{UNOP, l_fcset(0xABCDEF)}, {UNOP, l_fcget(2)}});
    ended(*vu);
    CHECK(vu->state().clip == 0xABCDEFu);
    CHECK(vu->state().vi[2] == 0xDEF);
}

// ---- MAC flags ------------------------------------------------------------------------------------------------

TEST_CASE("MAC Z flags: a zero result sets bits 3..0 for its dest lanes (hand: VU User's Manual)") {
    auto vu = build({{u_sub(XYZW, 3, 1, 1), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    ended(*vu);
    CHECK(vu->state().mac == 0x000Fu);
    CHECK((vu->state().status & 1u) == 1u); // Z
}

TEST_CASE("MAC S flags: a negative x lane sets bit 7, flags only cover dest lanes (hand: VU User's Manual)") {
    auto vu = build({{u_sub(X | Y, 3, 0, 1), LNOP}});
    set_vf(vu->state(), 1, 1, -1, 0, 0);
    ended(*vu);
    CHECK(vu->state().mac == 0x0080u);
    auto vu2 = build({{u_sub(X, 3, 1, 1), LNOP}});
    set_vf(vu2->state(), 1, 1, 2, 3, 4);
    ended(*vu2);
    CHECK(vu2->state().mac == 0x0008u);
}

TEST_CASE("MAX/MINI/FTOI leave the MAC flags alone (hand: VU User's Manual)") {
    auto vu = build({{u_sub(XYZW, 3, 1, 1), LNOP}, {u_max(XYZW, 4, 1, 2), LNOP}, {u_ftoi(0, XYZW, 5, 1), LNOP}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, -1, -1, -1, -1);
    ended(*vu);
    CHECK(vu->state().mac == 0x000Fu);
}

TEST_CASE("FMAND reads the MAC flags four pairs after the producer (hand: VU User's Manual; latency upstream)") {
    auto vu = build({{u_sub(XYZW, 3, 1, 1), l_iaddiu(3, 0, 0x7FFF)},
                     {UNOP, l_fmand(4, 3)}, // too early: the run-start value (0)
                     {UNOP, LNOP},
                     {UNOP, LNOP},
                     {UNOP, l_fmand(2, 3)}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    ended(*vu);
    CHECK(vu->state().vi[4] == 0);
    CHECK(vu->state().vi[2] == 0x000F);
}

// ---- EFU: DIV / RSQRT / WAITQ / ERCPR / MFP -------------------------------------------------------------------

TEST_CASE("DIV + WAITQ + MULq uses the quotient (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, by)}, {UNOP, l_waitq()}, {u_mulq(XYZW, 3, 4), LNOP}});
    set_vf(vu->state(), 1, 1, 0, 0, 0);
    set_vf(vu->state(), 2, 0, 4, 0, 0);
    set_vf(vu->state(), 4, 4, 8, 12, 16);
    ended(*vu);
    CHECK(vu->state().q == f2u(0.25f));
    check_vf(vu->state(), 3, 1, 2, 3, 4);
}

TEST_CASE("DIV by zero gives +/-max and sets status D (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, bx)}, {UNOP, l_waitq()}, {UNOP, l_div(1, by, 2, bx)}});
    set_vf(vu->state(), 1, 1, -1, 0, 0);
    ended(*vu);
    CHECK(vu->state().q == (0x80000000u | kMax)); // -1 / 0 (the run end flushes Q)
    CHECK((vu->state().status & 0x20u) == 0x20u);
}

TEST_CASE("DIV 0/0 gives +max with status D, not I (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, bx)}});
    ended(*vu);
    CHECK(vu->state().q == kMax);
    CHECK((vu->state().status & 0x30u) == 0x20u);
}

TEST_CASE("DIV with a finite divisor clears status D (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, bx)}, {UNOP, l_waitq()}, {UNOP, l_div(1, bx, 1, bx)}});
    set_vf(vu->state(), 1, 3, 0, 0, 0);
    ended(*vu);
    CHECK(vu->state().q == f2u(1.0f));
    CHECK((vu->state().status & 0x30u) == 0u);
}

TEST_CASE("RSQRT computes fs / sqrt(ft) (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_rsqrt(1, bx, 2, bz)}});
    set_vf(vu->state(), 1, 1, 0, 0, 0);
    set_vf(vu->state(), 2, 0, 0, 4, 0);
    ended(*vu);
    CHECK(vu->state().q == f2u(0.5f));
}

TEST_CASE("RSQRT of a negative ft uses |ft| (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_rsqrt(1, bx, 2, bz)}});
    set_vf(vu->state(), 1, 1, 0, 0, 0);
    set_vf(vu->state(), 2, 0, 0, -4, 0);
    ended(*vu);
    CHECK(vu->state().q == f2u(0.5f));
}

TEST_CASE("RSQRT by sqrt(0) gives +max with status D (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_rsqrt(1, bx, 2, bx)}});
    set_vf(vu->state(), 1, 2, 0, 0, 0);
    ended(*vu);
    CHECK(vu->state().q == kMax);
    CHECK((vu->state().status & 0x20u) == 0x20u);
}

TEST_CASE("Q pipeline: MULq right after DIV sees the old Q (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, bx)}, {u_mulq(XYZW, 3, 4), LNOP}});
    VU1State& s = vu->state();
    set_vf(s, 1, 1, 0, 0, 0);
    set_vf(s, 2, 4, 0, 0, 0);
    set_vf(s, 4, 4, 8, 12, 16);
    s.q = f2u(2.0f);
    ended(*vu);
    check_vf(s, 3, 8, 16, 24, 32);
    CHECK(s.q == f2u(0.25f)); // the run end flushes the pending result
}

TEST_CASE("Q pipeline: MULq seven pairs after DIV sees the new Q (upstream behaviour, hardware-unverified)") {
    std::vector<Pair> body{{UNOP, l_div(1, bx, 2, bx)}};
    for (int k = 0; k < 7; ++k) body.push_back({UNOP, LNOP});
    body.push_back({u_mulq(XYZW, 3, 4), LNOP});
    auto vu = build(body);
    VU1State& s = vu->state();
    set_vf(s, 1, 1, 0, 0, 0);
    set_vf(s, 2, 4, 0, 0, 0);
    set_vf(s, 4, 4, 8, 12, 16);
    s.q = f2u(2.0f);
    ended(*vu);
    check_vf(s, 3, 1, 2, 3, 4);
}

TEST_CASE("Q pipeline: a stepped DIV leaves Q pending until WAITQ (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_div(1, bx, 2, bx)}, {UNOP, l_waitq()}});
    VU1State& s = vu->state();
    set_vf(s, 1, 1, 0, 0, 0);
    set_vf(s, 2, 2, 0, 0, 0);
    vu->start(0);
    REQUIRE(vu->step().status == RunStatus::Running);
    CHECK(s.pipe.q_pending);
    CHECK(s.q == 0u);
    REQUIRE(vu->step().status == RunStatus::Running);
    CHECK_FALSE(s.pipe.q_pending);
    CHECK(s.q == f2u(0.5f));
}

TEST_CASE("ERCPR + MFP write 1/x to the dest lanes (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_ercpr(1, bz)}, {UNOP, l_mfp(X | W, 3)}});
    set_vf(vu->state(), 1, 0, 0, 4, 0);
    set_vf(vu->state(), 3, 9, 9, 9, 9);
    ended(*vu);
    CHECK(vu->state().p == f2u(0.25f));
    check_vf(vu->state(), 3, 0.25f, 9, 9, 0.25f);
}

TEST_CASE("ERCPR of zero gives 3.4e38 (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_ercpr(1, bx)}});
    ended(*vu);
    CHECK(vu->state().p == f2u(3.4e38f));
}

// ---- integer unit ---------------------------------------------------------------------------------------------

TEST_CASE("integer registers wrap at 16 bits (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_isubiu(1, 0, 1)}, {UNOP, l_iaddiu(2, 1, 1)}, {UNOP, l_iadd(3, 1, 1)}});
    ended(*vu);
    CHECK(vu->state().vi[1] == 0xFFFF);
    CHECK(vu->state().vi[2] == 0x0000);
    CHECK(vu->state().vi[3] == 0xFFFE);
}

TEST_CASE("IADDIU/ISUBIU take a 15-bit unsigned immediate split across the word (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(3, 0, 0x7FFF)}, {UNOP, l_iaddiu(4, 0, 0x4321)}, {UNOP, l_isubiu(5, 4, 0x0321)}});
    ended(*vu);
    CHECK(vu->state().vi[3] == 0x7FFF);
    CHECK(vu->state().vi[4] == 0x4321);
    CHECK(vu->state().vi[5] == 0x4000);
}

TEST_CASE("IADD / ISUB / IADDI with a signed 5-bit immediate (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 5)},
                     {UNOP, l_iaddiu(2, 0, 7)},
                     {UNOP, l_iadd(3, 1, 2)},
                     {UNOP, l_isub(4, 1, 2)},
                     {UNOP, l_iaddi(5, 1, -1)},
                     {UNOP, l_iaddi(6, 1, 15)},
                     {UNOP, l_iaddi(7, 1, -16)}});
    ended(*vu);
    const VU1State& s = vu->state();
    CHECK(s.vi[3] == 12);
    CHECK(s.vi[4] == 0xFFFE);
    CHECK(s.vi[5] == 4);
    CHECK(s.vi[6] == 20);
    CHECK(s.vi[7] == 0xFFF5);
}

TEST_CASE("IAND / IOR (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 0x00F0)},
                     {UNOP, l_iaddiu(2, 0, 0x0FF0)},
                     {UNOP, l_iand(3, 1, 2)},
                     {UNOP, l_ior(4, 1, 2)}});
    ended(*vu);
    CHECK(vu->state().vi[3] == 0x00F0);
    CHECK(vu->state().vi[4] == 0x0FF0);
}

TEST_CASE("vi00 stays zero when written (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(0, 0, 5)}, {UNOP, l_iaddiu(1, 0, 0)}});
    ended(*vu);
    CHECK(vu->state().vi[0] == 0);
    CHECK(vu->state().vi[1] == 0);
}

TEST_CASE("MFIR sign-extends, MTIR truncates to 16 bits (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_isubiu(1, 0, 0x7FFF)}, {UNOP, l_mfir(X | W, 2, 1)}, {UNOP, l_mtir(3, 4, by)}});
    VU1State& s = vu->state();
    s.vf[4][1] = 0x12345678u;
    ended(*vu);
    CHECK(s.vi[1] == 0x8001);
    CHECK(s.vf[2][0] == 0xFFFF8001u);
    CHECK(s.vf[2][1] == 0u);
    CHECK(s.vf[2][3] == 0xFFFF8001u);
    CHECK(s.vi[3] == 0x5678);
}

TEST_CASE("XTOP / XITOP return the VIF double-buffer registers (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_xtop(1)}, {UNOP, l_xitop(2)}});
    vu->set_tops(0x123, 0x45);
    ended(*vu);
    CHECK(vu->state().vi[1] == 0x123);
    CHECK(vu->state().vi[2] == 0x45);
}

// ---- moves and memory -----------------------------------------------------------------------------------------

TEST_CASE("MOVE honours dest; MR32 rotates lanes (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_move(Y | W, 2, 1)}, {UNOP, l_mr32(XYZW, 3, 1)}});
    set_vf(vu->state(), 1, 1, 2, 3, 4);
    set_vf(vu->state(), 2, 9, 9, 9, 9);
    ended(*vu);
    check_vf(vu->state(), 2, 9, 2, 9, 4);
    check_vf(vu->state(), 3, 2, 3, 4, 1);
}

TEST_CASE("SQ/LQ with dest masks and a negative offset (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(2, 0, 10)}, {UNOP, l_sq(X | Z, 1, 2, -1)}, {UNOP, l_lq(Y | W, 3, 0, 9)}});
    VU1State& s = vu->state();
    set_vf(s, 1, 1, 2, 3, 4);
    set_qword(s, 9, 0xAAAAAAAAu, 0xBBBBBBBBu, 0xCCCCCCCCu, 0xDDDDDDDDu);
    for (int i = 0; i < 4; ++i) s.vf[3][i] = 0x11111111u;
    ended(*vu);
    CHECK(data_word(s, 9, 0) == f2u(1));
    CHECK(data_word(s, 9, 1) == 0xBBBBBBBBu);
    CHECK(data_word(s, 9, 2) == f2u(3));
    CHECK(data_word(s, 9, 3) == 0xDDDDDDDDu);
    CHECK(s.vf[3][0] == 0x11111111u);
    CHECK(s.vf[3][1] == 0xBBBBBBBBu);
    CHECK(s.vf[3][3] == 0xDDDDDDDDu);
}

TEST_CASE("SQI/LQI post-increment, SQD/LQD pre-decrement (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 20)},
                     {UNOP, l_iaddiu(2, 0, 20)},
                     {UNOP, l_iaddiu(3, 0, 21)},
                     {UNOP, l_iaddiu(4, 0, 31)},
                     {UNOP, l_sqi(XYZW, 1, 1)},
                     {UNOP, l_lqi(XYZW, 4, 2)},
                     {UNOP, l_lqd(X, 5, 3)},
                     {UNOP, l_sqd(W, 1, 4)}});
    VU1State& s = vu->state();
    set_vf(s, 1, 1, 2, 3, 4);
    ended(*vu);
    CHECK(s.vi[1] == 21);
    CHECK(s.vi[2] == 21);
    CHECK(s.vi[3] == 20);
    CHECK(s.vi[4] == 30);
    check_vf(s, 4, 1, 2, 3, 4);
    CHECK(s.vf[5][0] == f2u(1));
    CHECK(data_word(s, 30, 3) == f2u(4));
}

TEST_CASE("data-memory qword addresses wrap at 1024 (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1023)}, {UNOP, l_sq(XYZW, 2, 1, 2)}});
    set_vf(vu->state(), 2, 5, 6, 7, 8);
    ended(*vu);
    CHECK(data_word(vu->state(), 1, 0) == f2u(5));
}

TEST_CASE("ILW reads the first dest lane's low half; ISW writes vi to every dest lane (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_ilw(Y, 1, 0, 5)}, {UNOP, l_isw(X | W, 1, 0, 6)}, {UNOP, l_iaddiu(3, 0, 5)},
                     {UNOP, l_ilwr(Z, 2, 3)}, {UNOP, l_iaddiu(4, 0, 7)}, {UNOP, l_iswr(Y, 2, 4)}});
    VU1State& s = vu->state();
    set_qword(s, 5, 0x11112222u, 0x33334444u, 0x55556666u, 0x77778888u);
    set_qword(s, 6, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu);
    ended(*vu);
    CHECK(s.vi[1] == 0x4444);
    CHECK(data_word(s, 6, 0) == 0x00004444u);
    CHECK(data_word(s, 6, 1) == 0xFFFFFFFFu);
    CHECK(data_word(s, 6, 3) == 0x00004444u);
    CHECK(s.vi[2] == 0x6666);
    CHECK(data_word(s, 7, 1) == 0x00006666u);
}

// ---- pair ordering --------------------------------------------------------------------------------------------

TEST_CASE("the upper result wins over a lower write to the same vf (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_add(XYZW, 3, 1, 2), l_move(XYZW, 3, 4)}});
    set_vf(vu->state(), 1, 1, 1, 1, 1);
    set_vf(vu->state(), 2, 1, 1, 1, 1);
    set_vf(vu->state(), 4, 7, 7, 7, 7);
    ended(*vu);
    check_vf(vu->state(), 3, 2, 2, 2, 2);
}

TEST_CASE("a lower store in the same pair sees vf before the upper result (upstream behaviour, hardware-unverified)") {
    auto vu = build({{u_add(XYZW, 3, 1, 2), l_sq(XYZW, 3, 0, 40)}});
    set_vf(vu->state(), 1, 1, 1, 1, 1);
    set_vf(vu->state(), 2, 1, 1, 1, 1);
    set_vf(vu->state(), 3, 5, 5, 5, 5);
    ended(*vu);
    CHECK(data_word(vu->state(), 40, 0) == f2u(5));
    check_vf(vu->state(), 3, 2, 2, 2, 2);
}

// ---- control flow ---------------------------------------------------------------------------------------------

TEST_CASE("B executes its delay slot, then the target (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_b(2)},                // -> pair 3
                     {UNOP, l_iaddiu(1, 0, 1)},     // delay slot
                     {UNOP, l_iaddiu(2, 0, 2)},     // skipped
                     {UNOP, l_iaddiu(3, 0, 3)}});
    ended(*vu);
    CHECK(vu->state().vi[1] == 1);
    CHECK(vu->state().vi[2] == 0);
    CHECK(vu->state().vi[3] == 3);
}

TEST_CASE("IBNE / IBEQ taken and not taken (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 4)},
                     {UNOP, LNOP},
                     {UNOP, l_ibeq(1, 0, 2)},    // not taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(2, 0, 2)},  // runs
                     {UNOP, l_ibne(1, 0, 2)},    // taken -> pair 8
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(3, 0, 3)},  // skipped
                     {UNOP, l_iaddiu(4, 0, 4)}});
    ended(*vu);
    CHECK(vu->state().vi[2] == 2);
    CHECK(vu->state().vi[3] == 0);
    CHECK(vu->state().vi[4] == 4);
}

TEST_CASE("IBLTZ / IBGEZ / IBLEZ / IBGTZ treat vi as signed 16-bit (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 0x7FFF)},
                     {UNOP, l_iaddiu(1, 1, 1)},  // 0x8000 = -32768
                     {UNOP, LNOP},
                     {UNOP, l_ibgez(1, 2)},      // not taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(2, 0, 1)},
                     {UNOP, l_ibgtz(1, 2)},      // not taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(3, 0, 1)},
                     {UNOP, l_iblez(1, 2)},      // taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(4, 0, 1)},  // skipped
                     {UNOP, l_ibltz(1, 2)},      // taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(5, 0, 1)},  // skipped
                     {UNOP, l_iaddiu(6, 0, 1)}});
    ended(*vu);
    const VU1State& s = vu->state();
    CHECK(s.vi[2] == 1);
    CHECK(s.vi[3] == 1);
    CHECK(s.vi[4] == 0);
    CHECK(s.vi[5] == 0);
    CHECK(s.vi[6] == 1);
}

TEST_CASE("branch VI delay: a branch right after a vi write reads the old value (upstream behaviour, hardware-unverified)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1)},
                     {UNOP, LNOP},
                     {UNOP, l_isubiu(1, 1, 1)}, // vi1 = 0 ...
                     {UNOP, l_ibne(1, 0, 2)},   // ... but the branch still sees 1: taken -> pair 6
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(2, 0, 5)}, // skipped
                     {UNOP, l_iaddiu(3, 0, 7)}});
    ended(*vu);
    CHECK(vu->state().vi[1] == 0);
    CHECK(vu->state().vi[2] == 0);
    CHECK(vu->state().vi[3] == 7);
}

TEST_CASE("branch VI delay does not apply across an intervening pair (hand: VU User's Manual)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1)},
                     {UNOP, l_isubiu(1, 1, 1)},
                     {UNOP, LNOP},
                     {UNOP, l_ibne(1, 0, 2)}, // vi1 = 0: not taken
                     {UNOP, LNOP},
                     {UNOP, l_iaddiu(2, 0, 5)},
                     {UNOP, l_iaddiu(3, 0, 7)}});
    ended(*vu);
    CHECK(vu->state().vi[2] == 5);
    CHECK(vu->state().vi[3] == 7);
}

TEST_CASE("BAL links (pc + 16) / 8 and JR returns through it (hand: VU User's Manual)") {
    auto vu = std::make_unique<VU1Interpreter>();
    const std::vector<Pair> prog{
        {UNOP, l_bal(15, 3)},              // 0: -> pair 4, vi15 = 2
        {UNOP, LNOP},                      // 1: delay
        {UNOP | E_BIT, l_iaddiu(2, 0, 2)}, // 2: return point, E
        {UNOP, LNOP},                      // 3: E delay
        {UNOP, l_iaddiu(1, 0, 1)},         // 4: subroutine
        {UNOP, l_jr(15)},                  // 5: -> pair 2
        {UNOP, l_iaddiu(3, 0, 3)},         // 6: delay
    };
    vu->load_micro(0, bytes_of(prog));
    REQUIRE(vu->mscal(0).status == RunStatus::Ended);
    const VU1State& s = vu->state();
    CHECK(s.vi[15] == 2);
    CHECK(s.vi[1] == 1);
    CHECK(s.vi[2] == 2);
    CHECK(s.vi[3] == 3);
    CHECK(s.tpc == 32);
}

TEST_CASE("the PC wraps from 0x3FF8 to 0x0000, and so do branch targets (hand: VU User's Manual)") {
    auto vu = std::make_unique<VU1Interpreter>();
    const std::vector<Pair> tail{
        {UNOP, l_iaddiu(1, 0, 1)}, // 0x3FF0
        {UNOP, l_iaddiu(2, 0, 2)}, // 0x3FF8
        {UNOP | E_BIT, l_iaddiu(3, 0, 3)}, // 0x0000 (sequential wrap)
        {UNOP, LNOP},
    };
    vu->load_micro(0x3FF0, bytes_of(tail));
    vu->start(0x3FF0);
    REQUIRE(vu->run().status == RunStatus::Ended);
    CHECK(vu->state().vi[1] == 1);
    CHECK(vu->state().vi[2] == 2);
    CHECK(vu->state().vi[3] == 3);
    CHECK(vu->state().tpc == 0x10);

    auto vb = std::make_unique<VU1Interpreter>();
    const std::vector<Pair> wrap{
        {UNOP, l_b(2)},                    // 0x3FF0: raw target 0x4008 -> 0x0008
        {UNOP, LNOP},                      // 0x3FF8: delay
        {UNOP, l_iaddiu(2, 0, 1)},         // 0x0000: skipped
        {UNOP | E_BIT, l_iaddiu(1, 0, 9)}, // 0x0008
        {UNOP, LNOP},
    };
    vb->load_micro(0x3FF0, bytes_of(wrap));
    vb->start(0x3FF0);
    REQUIRE(vb->run().status == RunStatus::Ended);
    CHECK(vb->state().vi[1] == 9);
    CHECK(vb->state().vi[2] == 0);
    CHECK(vb->state().tpc == 0x18);
}

TEST_CASE("E stops after its delay pair; MSCNT resumes at the pair after it (hand: VU User's Manual)") {
    auto vu = std::make_unique<VU1Interpreter>();
    const std::vector<Pair> prog{
        {UNOP, l_iaddiu(1, 1, 1)}, // 0
        {UNOP | E_BIT, LNOP},      // 1
        {UNOP, LNOP},              // 2: delay of E
        {UNOP, l_iaddiu(2, 2, 1)}, // 3: MSCNT resume point
        {UNOP, l_b(-5)},           // 4: -> pair 0
        {UNOP, LNOP},              // 5
    };
    vu->load_micro(0, bytes_of(prog));
    RunResult r = vu->mscal(0);
    REQUIRE(r.status == RunStatus::Ended);
    CHECK(r.steps == 3);
    CHECK(vu->state().tpc == 24);
    CHECK_FALSE(vu->state().running);
    r = vu->mscnt();
    REQUIRE(r.status == RunStatus::Ended);
    CHECK(r.steps == 6);
    CHECK(vu->state().vi[1] == 2);
    CHECK(vu->state().vi[2] == 1);
    CHECK(vu->state().tpc == 24);
}

TEST_CASE("MSCAL starts at imm * 8; MSCALF behaves the same (hand: VIF User's Manual)") {
    auto vu = std::make_unique<VU1Interpreter>();
    const std::vector<Pair> prog{
        {UNOP, l_iaddiu(1, 0, 1)},
        {UNOP, LNOP},
        {UNOP | E_BIT, l_iaddiu(2, 2, 1)}, // pair 2
        {UNOP, LNOP},
    };
    vu->load_micro(0, bytes_of(prog));
    REQUIRE(vu->mscal(2).status == RunStatus::Ended);
    CHECK(vu->state().vi[1] == 0);
    CHECK(vu->state().vi[2] == 1);
    REQUIRE(vu->mscalf(2).status == RunStatus::Ended);
    CHECK(vu->state().vi[2] == 2);
}

TEST_CASE("a runaway loop stops at the step limit and can continue (our runtime contract)") {
    auto vu = std::make_unique<VU1Interpreter>();
    vu->load_micro(0, bytes_of({{UNOP, l_b(-1)}, {UNOP, LNOP}}));
    RunResult r = vu->mscal(0, 100);
    CHECK(r.status == RunStatus::StepLimit);
    CHECK(r.steps == 100);
    CHECK(vu->state().running);
    r = vu->run(10);
    CHECK(r.status == RunStatus::StepLimit);
    CHECK(vu->stats().pairs == 110);
}

// ---- XGKICK ---------------------------------------------------------------------------------------------------

namespace {
// GIF tag lanes: NLOOP 14..0 + EOP 15 in x; FLG 27..26 and NREG 31..28 in y (bits 58/60 of the low dword).
constexpr u32 tag_x(u32 nloop, bool eop) { return (nloop & 0x7FFFu) | (eop ? 0x8000u : 0u); }
constexpr u32 tag_y(u32 flg, u32 nreg) { return (flg << 26) | (nreg << 28); }
} // namespace

TEST_CASE("XGKICK hands a PACKED packet up to EOP to the sink (hand: GS User's Manual)") {
    CaptureSink sink;
    auto vu = build({{UNOP, l_iaddiu(1, 0, 100)}, {UNOP, l_xgkick(1)}}, &sink);
    VU1State& s = vu->state();
    set_qword(s, 100, tag_x(2, true), tag_y(0, 1), 0x0E, 0);
    set_qword(s, 101, 1, 2, 3, 4);
    set_qword(s, 102, 5, 6, 7, 8);
    set_qword(s, 103, 0xDEAD, 0, 0, 0); // not part of the packet
    ended(*vu);
    REQUIRE(sink.packets.size() == 1);
    REQUIRE(sink.packets[0].size() == 3);
    CHECK(sink.packets[0][1].u32[0] == 1);
    CHECK(sink.packets[0][2].u32[3] == 8);
    CHECK(vu->stats().kicks == 1);
    CHECK(vu->stats().kick_qwords == 3);
    CHECK(vu->stats().kicks_without_eop == 0);
}

TEST_CASE("XGKICK follows a tag chain: REGLIST rounds up, IMAGE counts nloop (hand: GS User's Manual)") {
    CaptureSink sink;
    auto vu = build({{UNOP, l_iaddiu(1, 0, 10)}, {UNOP, l_xgkick(1)}}, &sink);
    VU1State& s = vu->state();
    set_qword(s, 10, tag_x(3, false), tag_y(1, 1), 0, 0); // REGLIST 3 regs -> 2 qwords
    set_qword(s, 13, tag_x(4, true), tag_y(2, 0), 0, 0);  // IMAGE 4 qwords
    ended(*vu);
    REQUIRE(sink.packets.size() == 1);
    CHECK(sink.packets[0].size() == 1 + 2 + 1 + 4);
}

TEST_CASE("XGKICK: NREG 0 means 16 registers (hand: GS User's Manual)") {
    CaptureSink sink;
    auto vu = build({{UNOP, l_xgkick(0)}}, &sink);
    set_qword(vu->state(), 0, tag_x(1, true), tag_y(0, 0), 0, 0);
    ended(*vu);
    REQUIRE(sink.packets.size() == 1);
    CHECK(sink.packets[0].size() == 17);
}

TEST_CASE("XGKICK wraps at the end of data memory (upstream behaviour, hardware-unverified)") {
    CaptureSink sink;
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1023)}, {UNOP, l_xgkick(1)}}, &sink);
    VU1State& s = vu->state();
    set_qword(s, 1023, tag_x(2, true), tag_y(0, 1), 0, 0);
    set_qword(s, 0, 0x100, 0, 0, 0);
    set_qword(s, 1, 0x101, 0, 0, 0);
    ended(*vu);
    REQUIRE(sink.packets.size() == 1);
    REQUIRE(sink.packets[0].size() == 3);
    CHECK(sink.packets[0][1].u32[0] == 0x100);
    CHECK(sink.packets[0][2].u32[0] == 0x101);
}

TEST_CASE("XGKICK without EOP stops at 1024 qwords and is counted (our runtime contract)") {
    CaptureSink sink;
    auto vu = build({{UNOP, l_xgkick(0)}}, &sink); // all-zero memory: tags with NLOOP 0 and no EOP
    ended(*vu);
    REQUIRE(sink.packets.size() == 1);
    CHECK(sink.packets[0].size() == kDataQwords);
    CHECK(vu->stats().kicks_without_eop == 1);
}

// ---- traps ----------------------------------------------------------------------------------------------------

TEST_CASE("an undefined upper encoding traps with its pc and raw words, executing nothing (our runtime contract)") {
    const u32 bad = up(0x30, 1, 2, 3, XYZW);
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1)}, {UNOP, LNOP}, {bad, l_iaddiu(2, 0, 2)}});
    const RunResult r = vu->mscal(0);
    CHECK(r.status == RunStatus::Trapped);
    CHECK(r.steps == 2);
    CHECK(vu->trap().kind == TrapKind::UndefinedUpper);
    CHECK(vu->trap().pc == 16);
    CHECK(vu->trap().hi == bad);
    CHECK(vu->trap().lo == l_iaddiu(2, 0, 2));
    CHECK(vu->trap().upper == "UNKNOWN");
    CHECK(vu->state().vi[1] == 1);
    CHECK(vu->state().vi[2] == 0);
    CHECK_FALSE(vu->state().running);
    CHECK(vu->state().pc == 16);
}

TEST_CASE("defined ops outside the census set trap (our runtime contract, 09 §4)") {
    auto sq = build({{UNOP, l_sqrt(1, bx)}});
    CHECK(sq->mscal(0).status == RunStatus::Trapped);
    CHECK(sq->trap().kind == TrapKind::UncensusedLower);
    CHECK(sq->trap().lower == "SQRT");
    auto abs = build({{up_sp(0x1D, 1, 2, XYZW), LNOP}});
    CHECK(abs->mscal(0).status == RunStatus::Trapped);
    CHECK(abs->trap().kind == TrapKind::UncensusedUpper);
    CHECK(abs->trap().upper == "ABS");
    auto und = build({{UNOP, 0x02u << 25}});
    CHECK(und->mscal(0).status == RunStatus::Trapped);
    CHECK(und->trap().kind == TrapKind::UndefinedLower);
}

TEST_CASE("the M/D/T flags trap (our runtime contract, 09 §4: never set)") {
    auto vu = build({{UNOP | kFlagD, LNOP}});
    CHECK(vu->mscal(0).status == RunStatus::Trapped);
    CHECK(vu->trap().kind == TrapKind::DebugFlag);
    CHECK(to_string(vu->trap().kind) == "M/D/T flag set");
}

TEST_CASE("rewriting micro memory invalidates cached decodes (our runtime contract)") {
    auto vu = build({{UNOP, l_iaddiu(1, 0, 1)}});
    ended(*vu);
    CHECK(vu->state().vi[1] == 1);
    const std::vector<u8> patch = bytes_of({{UNOP, l_iaddiu(1, 0, 2)}});
    vu->load_micro(0, patch);
    ended(*vu);
    CHECK(vu->state().vi[1] == 2);
}
