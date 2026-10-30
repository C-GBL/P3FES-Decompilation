// VU0 macro-mode vectors (runtime/include/p3fes/ee/vu0.h): dest masks, broadcast fields, ACC/Q/I, the
// Q-pipe ops, integer ops, COP2 transfers and the (macro-mode-inert) MAC/STATUS flag computation.
// Provenance:
//   (hand: EE Core User's Manual semantics)   - the manual defines the result (VU User's Manual for VU ops)
//   (upstream behaviour, hardware-unverified) - detail the manual does not pin down; we match ps2-web-recomp @ c0f476e
//   (PCSX2 2.8.2 observed: <id>)             - settled by tests/ee/vectors/pcsx2_vectors.json (tools/ours/eevec)
#include "ee_test_util.h"

#include "p3fes/ee/vu0.h"
#include "p3fes/ee_memory.h"

using namespace p3fes;
using namespace p3fes::ee;
using namespace p3fes::ee_test;

namespace {

void set4(VU0State& v, unsigned r, float x, float y, float z, float w) {
    vu0::set_vf(v, r, 0, f2u(x));
    vu0::set_vf(v, r, 1, f2u(y));
    vu0::set_vf(v, r, 2, f2u(z));
    vu0::set_vf(v, r, 3, f2u(w));
}

void set_acc4(VU0State& v, float x, float y, float z, float w) {
    vu0::set_acc(v, 0, f2u(x));
    vu0::set_acc(v, 1, f2u(y));
    vu0::set_acc(v, 2, f2u(z));
    vu0::set_acc(v, 3, f2u(w));
}

u128 vf4(const VU0State& v, unsigned r) {
    return qw(vu0::vf(v, r, 0), vu0::vf(v, r, 1), vu0::vf(v, r, 2), vu0::vf(v, r, 3));
}

u128 acc4(const VU0State& v) {
    return qw(vu0::acc(v, 0), vu0::acc(v, 1), vu0::acc(v, 2), vu0::acc(v, 3));
}

u128 f4(float x, float y, float z, float w) { return qw(f2u(x), f2u(y), f2u(z), f2u(w)); }

VU0State fresh() {
    VU0State v;
    vu0::reset(v);
    return v;
}

} // namespace

TEST_CASE("reset: vf00 = (0,0,0,1), everything else zero") {
    VU0State v;
    v.vi[3] = 7;
    set4(v, 5, 1, 2, 3, 4);
    vu0::reset(v);
    // (hand: manual) vf00 reads as (0, 0, 0, 1.0).
    CHECK(vf4(v, 0) == f4(0, 0, 0, 1.0f));
    CHECK(vf4(v, 5) == f4(0, 0, 0, 0));
    CHECK(v.vi[3] == 0);
    CHECK(v.status == 0);
}

TEST_CASE("dest mask: each field individually, all fields, and the read-only vf00") {
    VU0State v = fresh();
    set4(v, 1, 1, 2, 3, 4);
    set4(v, 2, 10, 20, 30, 40);
    // (hand: manual) dest bit 3 = x ... bit 0 = w; unselected lanes keep their value.
    const unsigned masks[4] = {vu0::kDestX, vu0::kDestY, vu0::kDestZ, vu0::kDestW};
    for (int lane = 0; lane < 4; ++lane) {
        set4(v, 3, -1, -1, -1, -1);
        vu0::add(v, masks[lane], 3, 1, 2);
        const float expect[4] = {11, 22, 33, 44};
        for (int i = 0; i < 4; ++i) {
            CHECK(vu0::vf(v, 3, i) == (i == lane ? f2u(expect[i]) : f2u(-1.0f)));
        }
    }
    set4(v, 3, -1, -1, -1, -1);
    vu0::add(v, vu0::kDestXYZW, 3, 1, 2);
    CHECK(vf4(v, 3) == f4(11, 22, 33, 44));
    set4(v, 3, -1, -1, -1, -1);
    vu0::add(v, vu0::kDestXYZ, 3, 1, 2);
    CHECK(vf4(v, 3) == f4(11, 22, 33, -1));
    set4(v, 3, -1, -1, -1, -1);
    vu0::add(v, 0u, 3, 1, 2); // empty dest writes nothing
    CHECK(vf4(v, 3) == f4(-1, -1, -1, -1));
    // (hand: manual) vf00 is never written.
    vu0::add(v, vu0::kDestXYZW, 0, 1, 2);
    CHECK(vf4(v, 0) == f4(0, 0, 0, 1.0f));
    CHECK(vu0::lane(vu0::kDestX, 0));
    CHECK_FALSE(vu0::lane(vu0::kDestX, 3));
    CHECK(vu0::lane(vu0::kDestW, 3));
}

TEST_CASE("vadd/vsub/vmul/vmadd/vmsub and vmax/vmini") {
    VU0State v = fresh();
    set4(v, 1, 5, 5, 5, 5);
    set4(v, 2, 1, 2, 3, 4);
    // (hand: manual)
    vu0::sub(v, vu0::kDestXYZW, 3, 1, 2);
    CHECK(vf4(v, 3) == f4(4, 3, 2, 1));
    vu0::mul(v, vu0::kDestXYZW, 3, 1, 2);
    CHECK(vf4(v, 3) == f4(5, 10, 15, 20));
    set_acc4(v, 1, 1, 1, 1);
    set4(v, 4, 2, 2, 2, 2);
    set4(v, 5, 3, 3, 3, 3);
    vu0::madd(v, vu0::kDestXYZW, 3, 4, 5);
    CHECK(vf4(v, 3) == f4(7, 7, 7, 7));
    vu0::msub(v, vu0::kDestXYZW, 3, 4, 5);
    CHECK(vf4(v, 3) == f4(-5, -5, -5, -5));
    CHECK(acc4(v) == f4(1, 1, 1, 1)); // VMADD/VMSUB leave ACC alone
    set4(v, 6, 1, -1, 0, 5);
    set4(v, 7, 0, -2, 0, 5);
    vu0::set_vf(v, 7, 2, 0x80000000u); // -0 in ft.z
    vu0::max(v, vu0::kDestXYZW, 3, 6, 7);
    CHECK(vf4(v, 3) == f4(1, -1, 0, 5));
    vu0::mini(v, vu0::kDestXYZW, 3, 6, 7);
    // (upstream behaviour, hardware-unverified) +0 vs -0 and equal values return the fs pattern.
    CHECK(vf4(v, 3) == f4(0, -2, 0, 5));
    // (hand: manual) overflow clamps to +/-0x7FFFFFFF, denormals flush.
    vu0::set_vf(v, 6, 0, 0x7F7FFFFFu);
    vu0::set_vf(v, 7, 0, 0x7F7FFFFFu);
    vu0::add(v, vu0::kDestX, 3, 6, 7);
    CHECK(vu0::vf(v, 3, 0) == 0x7FFFFFFFu);
    vu0::set_vf(v, 7, 0, 0x00000001u);
    vu0::mul(v, vu0::kDestX, 3, 6, 7);
    CHECK(vu0::vf(v, 3, 0) == 0u);
}

TEST_CASE("broadcast forms: each bc field, Q and I") {
    VU0State v = fresh();
    set4(v, 1, 1, 2, 3, 4);
    set4(v, 2, 10, 20, 30, 40);
    // (hand: manual) vmulx/y/z/w vf3, vf1, vf2{x|y|z|w}
    vu0::mul_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(10, 20, 30, 40));
    vu0::mul_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcY);
    CHECK(vf4(v, 3) == f4(20, 40, 60, 80));
    vu0::mul_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcZ);
    CHECK(vf4(v, 3) == f4(30, 60, 90, 120));
    vu0::mul_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcW);
    CHECK(vf4(v, 3) == f4(40, 80, 120, 160));
    // broadcast with a partial dest
    set4(v, 3, -1, -1, -1, -1);
    vu0::add_bc(v, vu0::kDestY | vu0::kDestW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(-1, 12, -1, 14));
    vu0::sub_bc(v, vu0::kDestXYZW, 3, 2, 1, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(9, 19, 29, 39));
    // (hand: manual) vmulq / vaddi / vmuli / vsubq / vmaddi / vmsubq / vmaxi / vminii
    vu0::set_q(v, f2u(2.0f));
    vu0::set_i(v, f2u(0.5f));
    vu0::mul_q(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(2, 4, 6, 8));
    vu0::add_i(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(1.5f, 2.5f, 3.5f, 4.5f));
    vu0::mul_i(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(0.5f, 1, 1.5f, 2));
    vu0::sub_q(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(-1, 0, 1, 2));
    set_acc4(v, 1, 1, 1, 1);
    vu0::madd_i(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(1.5f, 2, 2.5f, 3));
    vu0::msub_q(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(-1, -3, -5, -7));
    vu0::max_i(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(1, 2, 3, 4));
    vu0::mini_i(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == f4(0.5f, 0.5f, 0.5f, 0.5f));
    // madd_bc / msub_bc / max_bc / mini_bc
    set_acc4(v, 100, 100, 100, 100);
    vu0::madd_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(110, 120, 130, 140));
    vu0::msub_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(90, 80, 70, 60));
    vu0::max_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(10, 10, 10, 10));
    vu0::mini_bc(v, vu0::kDestXYZW, 3, 1, 2, vu0::kBcX);
    CHECK(vf4(v, 3) == f4(1, 2, 3, 4));
    // the broadcast operand is read before the destination lanes are written (fd == ft)
    set4(v, 4, 2, 3, 4, 5);
    vu0::mul_bc(v, vu0::kDestXYZW, 4, 4, 4, vu0::kBcX);
    CHECK(vf4(v, 4) == f4(4, 6, 8, 10));
}

TEST_CASE("ACC-writing forms with dest masks: vadda/vsuba/vmula/vmadda/vmsuba and broadcast/Q/I variants") {
    VU0State v = fresh();
    set4(v, 1, 1, 2, 3, 4);
    set4(v, 2, 1, 1, 1, 1);
    // (hand: manual)
    set_acc4(v, 9, 9, 9, 9);
    vu0::adda(v, vu0::kDestX | vu0::kDestY, 1, 2);
    CHECK(acc4(v) == f4(2, 3, 9, 9));
    vu0::suba(v, vu0::kDestXYZW, 1, 2);
    CHECK(acc4(v) == f4(0, 1, 2, 3));
    vu0::mula(v, vu0::kDestXYZW, 1, 1);
    CHECK(acc4(v) == f4(1, 4, 9, 16));
    vu0::madda(v, vu0::kDestXYZW, 1, 2);
    CHECK(acc4(v) == f4(2, 6, 12, 20));
    vu0::msuba(v, vu0::kDestXYZW, 1, 1);
    CHECK(acc4(v) == f4(1, 2, 3, 4));
    vu0::mula_bc(v, vu0::kDestXYZW, 1, 1, vu0::kBcW);
    CHECK(acc4(v) == f4(4, 8, 12, 16));
    vu0::adda_bc(v, vu0::kDestXYZW, 1, 1, vu0::kBcX);
    CHECK(acc4(v) == f4(2, 3, 4, 5));
    vu0::suba_bc(v, vu0::kDestXYZW, 1, 1, vu0::kBcY);
    CHECK(acc4(v) == f4(-1, 0, 1, 2));
    vu0::madda_bc(v, vu0::kDestXYZW, 1, 1, vu0::kBcX);
    CHECK(acc4(v) == f4(0, 2, 4, 6));
    vu0::msuba_bc(v, vu0::kDestXYZW, 1, 1, vu0::kBcX);
    CHECK(acc4(v) == f4(-1, 0, 1, 2));
    vu0::set_q(v, f2u(2.0f));
    vu0::set_i(v, f2u(3.0f));
    vu0::mula_q(v, vu0::kDestXYZW, 1);
    CHECK(acc4(v) == f4(2, 4, 6, 8));
    vu0::adda_i(v, vu0::kDestXYZW, 1);
    CHECK(acc4(v) == f4(4, 5, 6, 7));
    vu0::madda_q(v, vu0::kDestXYZW, 1);
    CHECK(acc4(v) == f4(6, 9, 12, 15));
    vu0::msuba_i(v, vu0::kDestXYZW, 1);
    CHECK(acc4(v) == f4(3, 3, 3, 3));
    vu0::suba_q(v, vu0::kDestXYZW, 1);
    CHECK(acc4(v) == f4(-1, 0, 1, 2));
    vu0::mula_i(v, vu0::kDestXYZW, 2);
    CHECK(acc4(v) == f4(3, 3, 3, 3));
    vu0::adda_q(v, vu0::kDestXYZW, 2);
    CHECK(acc4(v) == f4(3, 3, 3, 3));
    vu0::madda_i(v, vu0::kDestXYZW, 2);
    CHECK(acc4(v) == f4(6, 6, 6, 6));
    vu0::msuba_q(v, vu0::kDestXYZW, 2);
    CHECK(acc4(v) == f4(4, 4, 4, 4));
}

TEST_CASE("vopmula / vopmsub: outer product halves; the cross-product idiom swaps operands") {
    VU0State v = fresh();
    set4(v, 1, 1, 2, 3, 99);
    set4(v, 2, 4, 5, 6, 99);
    set_acc4(v, 0, 0, 0, 7);
    // (hand: manual) ACC.xyz = fs.yzx * ft.zxy; w untouched.
    vu0::opmula(v, 1, 2);
    CHECK(acc4(v) == f4(12, 12, 5, 7));
    // (hand: manual) fd.xyz = ACC - fs.yzx * ft.zxy with the operands swapped -> (1,2,3) x (4,5,6) = (-3, 6, -3).
    set4(v, 3, 0, 0, 0, 55);
    vu0::opmsub(v, 3, 2, 1);
    CHECK(vf4(v, 3) == f4(-3, 6, -3, 55));
    // same operands as opmula gives zero; vf00 is never written
    vu0::opmsub(v, 3, 1, 2);
    CHECK(vf4(v, 3) == f4(0, 0, 0, 55));
    vu0::opmsub(v, 0, 1, 2);
    CHECK(vf4(v, 0) == f4(0, 0, 0, 1.0f));
}

TEST_CASE("vabs / vmove / vmr32") {
    VU0State v = fresh();
    set4(v, 1, -1, 2, -3, 4);
    vu0::set_vf(v, 1, 1, 0x80000000u); // -0 in y
    // (hand: manual)
    vu0::abs(v, vu0::kDestXYZW, 2, 1);
    CHECK(vf4(v, 2) == f4(1, 0, 3, 4));
    vu0::move(v, vu0::kDestXYZW, 3, 1);
    CHECK(vf4(v, 3) == qw(f2u(-1.0f), 0x80000000u, f2u(-3.0f), f2u(4.0f)));
    set4(v, 4, 1, 2, 3, 4);
    vu0::mr32(v, vu0::kDestXYZW, 5, 4);
    CHECK(vf4(v, 5) == f4(2, 3, 4, 1));
    set4(v, 5, -1, -1, -1, -1);
    vu0::mr32(v, vu0::kDestX | vu0::kDestW, 5, 4);
    CHECK(vf4(v, 5) == f4(2, -1, -1, 1));
    vu0::mr32(v, vu0::kDestXYZW, 4, 4); // in place: the source is read before any lane is written
    CHECK(vf4(v, 4) == f4(2, 3, 4, 1));
}

TEST_CASE("vftoi0/4/12/15 and vitof0/4/12/15") {
    VU0State v = fresh();
    set4(v, 1, 2.5f, -2.5f, 1.0f, 0.5f);
    // (hand: manual) truncation; fixed-point scaling by 2^n.
    vu0::ftoi(v, vu0::kDestXYZW, 2, 1, 0);
    CHECK(vf4(v, 2) == qw(2u, static_cast<u32>(-2), 1u, 0u));
    vu0::ftoi(v, vu0::kDestXYZW, 2, 1, 4);
    CHECK(vf4(v, 2) == qw(40u, static_cast<u32>(-40), 16u, 8u));
    vu0::ftoi(v, vu0::kDestXYZW, 2, 1, 12);
    CHECK(vf4(v, 2) == qw(10240u, static_cast<u32>(-10240), 4096u, 2048u));
    vu0::ftoi(v, vu0::kDestXYZW, 2, 1, 15);
    CHECK(vf4(v, 2) == qw(81920u, static_cast<u32>(-81920), 32768u, 16384u));
    // (hand: manual) saturation: 2^27 * 2^4 = 2^31 saturates positive, -2^31 is representable.
    vu0::set_vf(v, 3, 0, 0x4D000000u);
    vu0::set_vf(v, 3, 1, 0xCD000000u);
    vu0::set_vf(v, 3, 2, 0x4F000000u);
    vu0::set_vf(v, 3, 3, 0x7FFFFFFFu);
    vu0::ftoi(v, vu0::kDestXYZW, 2, 3, 4);
    CHECK(vf4(v, 2) == qw(0x7FFFFFFFu, 0x80000000u, 0x7FFFFFFFu, 0x7FFFFFFFu));
    // itof
    vu0::set_vf(v, 4, 0, 2u);
    vu0::set_vf(v, 4, 1, 16u);
    vu0::set_vf(v, 4, 2, 4096u);
    vu0::set_vf(v, 4, 3, static_cast<u32>(-32768));
    vu0::itof(v, vu0::kDestX, 5, 4, 0);
    vu0::itof(v, vu0::kDestY, 5, 4, 4);
    vu0::itof(v, vu0::kDestZ, 5, 4, 12);
    vu0::itof(v, vu0::kDestW, 5, 4, 15);
    CHECK(vf4(v, 5) == f4(2, 1, 1, -1));
    vu0::set_vf(v, 4, 0, 0x7FFFFFFFu);
    vu0::itof(v, vu0::kDestX, 5, 4, 0);
    CHECK(vu0::vf(v, 5, 0) == 0x4EFFFFFFu); // truncated, not rounded up to 2^31
}

TEST_CASE("vdiv / vsqrt / vrsqrt with fsf/ftf selectors, Q and the STATUS I/D bits") {
    VU0State v = fresh();
    set4(v, 1, 1, 4, 9, 16);
    set4(v, 2, -4, 0, 2, 0);
    // (hand: manual) Q = vf1.x / vf1.y = 0.25
    vu0::div(v, 1, 0, 1, 1);
    CHECK(vu0::q(v) == f2u(0.25f));
    CHECK(v.status == 0u);
    // (hand: manual) x / 0 -> +/-max; (PCSX2 2.8.2 observed: vu0_3280) D (bit 5) + sticky DS (bit 11).
    vu0::div(v, 1, 3, 2, 1);
    CHECK(vu0::q(v) == 0x7FFFFFFFu);
    CHECK(v.status == (vu0::kStatusDivideByZero | vu0::kStatusDivideByZeroSticky));
    vu0::div(v, 2, 0, 2, 1);
    CHECK(vu0::q(v) == 0xFFFFFFFFu);
    // a following valid divide clears D, the sticky bit stays (PCSX2 2.8.2 observed: vu0_3380)
    vu0::div(v, 1, 0, 1, 1);
    CHECK(v.status == vu0::kStatusDivideByZeroSticky);
    // (hand: manual) sqrt(vf1.z) = 3; sqrt(-4) = 2 (|x|) with I + IS (PCSX2 2.8.2 observed: vu0_3294)
    vu0::sqrt(v, 1, 2);
    CHECK(vu0::q(v) == f2u(3.0f));
    CHECK(v.status == vu0::kStatusDivideByZeroSticky);
    vu0::sqrt(v, 2, 0);
    CHECK(vu0::q(v) == f2u(2.0f));
    CHECK(v.status == (vu0::kStatusDivideByZeroSticky | vu0::kStatusInvalid | vu0::kStatusInvalidSticky));
    // (hand: manual) rsqrt = vf1.w / sqrt(vf1.y) = 16 / 2 = 8; I cleared, both sticky bits stay
    vu0::rsqrt(v, 1, 3, 1, 1);
    CHECK(vu0::q(v) == f2u(8.0f));
    CHECK(v.status == (vu0::kStatusDivideByZeroSticky | vu0::kStatusInvalidSticky));
    // ft component zero -> clamp with sign of fs and D flag (PCSX2 2.8.2 observed: vu0_3281)
    vu0::rsqrt(v, 2, 0, 2, 1);
    CHECK(vu0::q(v) == 0xFFFFFFFFu);
    CHECK(v.status == (0xC00u | vu0::kStatusDivideByZero));
    // (PCSX2 2.8.2 observed: vu0_3279) negative ft uses |ft| and raises I: 16 / sqrt(|-4|) = 8
    vu0::rsqrt(v, 1, 3, 2, 0);
    CHECK(vu0::q(v) == f2u(8.0f));
    CHECK(v.status == (0xC00u | vu0::kStatusInvalid));
    // (PCSX2 2.8.2 observed: vu0_3318) 0 / 0 raises I, not D
    set4(v, 3, 0, 0, 0, 0);
    v.status = 0;
    vu0::div(v, 3, 0, 3, 1);
    CHECK(vu0::q(v) == 0x7FFFFFFFu);
    CHECK(v.status == (vu0::kStatusInvalid | vu0::kStatusInvalidSticky));
    // sticky bits 6..11 survive the D-bit update (PCSX2 2.8.2 observed: vu0_3379)
    v.status = 0xFC0u;
    vu0::div(v, 1, 3, 2, 1);
    CHECK(v.status == (0xFC0u | vu0::kStatusDivideByZero));
    // (upstream behaviour, hardware-unverified) vwaitq / vnop do nothing; PCSX2 showed the new Q before a VWAITQ too
    // (vu0_3378)
    const VU0State before = v;
    vu0::waitq(v);
    vu0::nop(v);
    CHECK(vu0::q(v) == vu0::q(before));
    CHECK(v.status == before.status);
}

TEST_CASE("integer ops: viadd/visub/viand/vior/viaddi, vi00 constant, 16-bit wrap") {
    VU0State v = fresh();
    v.vi[1] = 0xFFFF;
    v.vi[2] = 1;
    v.vi[3] = 0x0F0F;
    // (hand: manual)
    vu0::iadd(v, 4, 1, 2);
    CHECK(v.vi[4] == 0u);                 // 0xFFFF + 1 wraps to 0
    vu0::isub(v, 4, 2, 1);
    CHECK(v.vi[4] == 2u);                 // 1 - 0xFFFF = 2 mod 2^16
    vu0::iand(v, 4, 1, 3);
    CHECK(v.vi[4] == 0x0F0Fu);
    vu0::ior(v, 4, 2, 3);
    CHECK(v.vi[4] == 0x0F0Fu);
    vu0::iaddi(v, 4, 2, -1);
    CHECK(v.vi[4] == 0u);
    vu0::iaddi(v, 4, 4, -1);
    CHECK(v.vi[4] == 0xFFFFu);
    vu0::iaddi(v, 4, 3, 15);
    CHECK(v.vi[4] == 0x0F1Eu);
    vu0::iaddi(v, 4, 0, -16);
    CHECK(v.vi[4] == 0xFFF0u);
    // vi00 reads 0 and ignores writes
    vu0::iadd(v, 0, 1, 2);
    CHECK(v.vi[0] == 0u);
    vu0::set_vi(v, 0, 0x1234u);
    CHECK(v.vi[0] == 0u);
    vu0::iadd(v, 4, 0, 3);
    CHECK(v.vi[4] == 0x0F0Fu);
    // (hand: manual) vmfir sign-extends vi into the selected lanes
    v.vi[5] = 0x8000;
    vu0::mfir(v, vu0::kDestX | vu0::kDestZ, 6, 5);
    CHECK(vf4(v, 6) == qw(0xFFFF8000u, 0u, 0xFFFF8000u, 0u));
}

TEST_CASE("qmfc2 / qmtc2 move whole quadwords; the interlock bit is accepted and ignored") {
    VU0State v = fresh();
    const u128 q = qw(0x7FFFFFFFu, 0x80000000u, 0x00000001u, f2u(1.0f));
    // (hand: manual) bit patterns survive untouched (no flush on transfer).
    vu0::qmtc2(v, 7, q);
    CHECK(vf4(v, 7) == q);
    CHECK(vu0::qmfc2(v, 7) == q);
    vu0::qmtc2(v, 8, q, true);
    CHECK(vu0::qmfc2(v, 8, true) == q);
    // vf00 is never written
    vu0::qmtc2(v, 0, q);
    CHECK(vu0::qmfc2(v, 0) == f4(0, 0, 0, 1.0f));
}

TEST_CASE("cfc2 / ctc2: vi registers, STATUS/MAC/CLIP/I/Q, unbacked registers") {
    VU0State v = fresh();
    // (hand: manual) registers 0..15 are the integer file; vi00 ignores writes.
    vu0::ctc2(v, 5, 0x12345678u);
    CHECK(v.vi[5] == 0x5678u);
    CHECK(vu0::cfc2(v, 5) == 0x5678u);
    vu0::ctc2(v, 0, 0xFFFFu);
    CHECK(vu0::cfc2(v, 0) == 0u);
    // I ($21) and Q ($22) carry raw float patterns.
    vu0::ctc2(v, vu0::kCtrlI, f2u(2.0f));
    CHECK(vu0::i_reg(v) == f2u(2.0f));
    CHECK(vu0::cfc2(v, vu0::kCtrlI) == f2u(2.0f));
    vu0::ctc2(v, vu0::kCtrlQ, f2u(0.5f));
    CHECK(vu0::cfc2(v, vu0::kCtrlQ) == f2u(0.5f));
    // (upstream behaviour, hardware-unverified) STATUS keeps bits 0..5 and accepts only the sticky bits 6..11.
    v.status = 0x20u;
    vu0::ctc2(v, vu0::kCtrlStatus, 0xFFFFFFFFu);
    CHECK(vu0::cfc2(v, vu0::kCtrlStatus) == 0xFE0u);
    // (PCSX2 2.8.2 observed: vu0_3403) MAC is read-only
    v.mac = 0xFu;
    vu0::ctc2(v, vu0::kCtrlMac, 0xABCDu);
    CHECK(vu0::cfc2(v, vu0::kCtrlMac) == 0xFu);
    vu0::ctc2(v, vu0::kCtrlClip, 0xFFFFFFFFu);
    CHECK(vu0::cfc2(v, vu0::kCtrlClip) == 0xFFFFFFu);
    // (upstream behaviour, hardware-unverified) R is 23 bits, CMSAR0 16 bits; TPC is read-only.
    vu0::ctc2(v, vu0::kCtrlR, 0xFFFFFFFFu);
    CHECK(vu0::cfc2(v, vu0::kCtrlR) == 0x7FFFFFu);
    vu0::ctc2(v, vu0::kCtrlCmsar0, 0x12345678u);
    CHECK(vu0::cfc2(v, vu0::kCtrlCmsar0) == 0x5678u);
    vu0::ctc2(v, vu0::kCtrlTpc, 0x40u);
    CHECK(vu0::cfc2(v, vu0::kCtrlTpc) == 0u);
    v.tpc = 0x80u;
    CHECK(vu0::cfc2(v, vu0::kCtrlTpc) == 0x80u);
    // FBRST, VPU-STAT, CMSAR1 are not modelled: reads 0, writes dropped (as upstream)
    CHECK(vu0::cfc2(v, vu0::kCtrlVpuStat) == 0u);
    vu0::ctc2(v, vu0::kCtrlFbrst, 1u);
    vu0::ctc2(v, vu0::kCtrlCmsar1, 0x100u);
    CHECK(vu0::cfc2(v, vu0::kCtrlFbrst) == 0u);
    CHECK(vu0::cfc2(v, vu0::kCtrlCmsar1) == 0u);
}

TEST_CASE("lqc2 / sqc2 ignore the low four address bits; lqc2 into vf00 is discarded") {
    EEMemory mem;
    VU0State v = fresh();
    const u128 q = qseq(0x40);
    vu0::qmtc2(v, 9, q);
    // (hand: manual)
    vu0::sqc2(v, mem, 9, 0x20Cu);
    CHECK(mem.read<u32>(0x200u) == 0x43424140u);
    CHECK(mem.read<u32>(0x210u) == 0u);
    vu0::lqc2(v, mem, 10, 0x205u);
    CHECK(vf4(v, 10) == q);
    vu0::lqc2(v, mem, 0, 0x200u);
    CHECK(vf4(v, 0) == f4(0, 0, 0, 1.0f));
    CHECK(mem.unmapped_accesses() == 0u);
}

TEST_CASE("vclip: six judgement bits shift into the 24-bit CLIP register") {
    VU0State v = fresh();
    set4(v, 1, 2, -2, 0.5f, 0);
    set4(v, 2, 0, 0, 0, 1);
    // (hand: manual) x > +w -> bit 0; y < -w -> bit 3; z inside -> nothing.
    vu0::clip(v, 1, 2);
    CHECK(v.clip == 0x9u);
    vu0::clip(v, 1, 2);
    CHECK(v.clip == 0x249u);
    // |w| is used, so a negative w behaves like its magnitude
    set4(v, 2, 0, 0, 0, -1);
    vu0::clip(v, 1, 2);
    CHECK(v.clip == 0x9249u);
    // the register is 24 bits wide
    for (int i = 0; i < 8; ++i) vu0::clip(v, 1, 2);
    CHECK(v.clip == 0x249249u);
}

TEST_CASE("update_mac_flags: Z/S/O per lane with dest masking and sticky STATUS bits") {
    VU0State v = fresh();
    // (upstream behaviour, hardware-unverified) result (0, -1.0, 0x7FFFFFFF, 2.0) -> Z.x, S.y, O.z.
    const u32 r[4] = {0u, f2u(-1.0f), 0x7FFFFFFFu, f2u(2.0f)};
    vu0::update_mac_flags(v, r, vu0::kDestXYZW);
    CHECK(v.mac == 0x2048u);
    CHECK(v.status == 0x2CBu);
    // Only x selected: a fresh MAC with just Z.x; STATUS keeps the sticky bits from before and preserves I/D.
    v.status |= vu0::kStatusDivideByZero;
    vu0::update_mac_flags(v, r, vu0::kDestX);
    CHECK(v.mac == 0x8u);
    CHECK(v.status == (0x2C0u | 0x1u | vu0::kStatusDivideByZero));
    // (PCSX2 2.8.2 observed: vu0_3417, vu0_3422) macro-mode arithmetic updates the flags: (0,-1,2,3) + vf00 ->
    // (0, -1, 2, 4): Z.x and S.y, with their sticky copies.
    VU0State w = fresh();
    set4(w, 1, 0, -1, 2, 3);
    vu0::add(w, vu0::kDestXYZW, 2, 1, 0);
    CHECK(w.mac == 0x48u);
    CHECK(w.status == 0xC3u);
    // dest-masked lanes contribute nothing and read 0 in MAC
    vu0::add(w, vu0::kDestY, 2, 1, 0);
    CHECK(w.mac == 0x40u);
    CHECK(w.status == 0xC2u);
    // (PCSX2 2.8.2 observed: vu0_3030, vu0_3419) VMAX/VMINI and the moves leave MAC/STATUS alone
    vu0::max(w, vu0::kDestXYZW, 2, 1, 0);
    vu0::move(w, vu0::kDestXYZW, 3, 1);
    CHECK(w.mac == 0x40u);
    CHECK(w.status == 0xC2u);
}
