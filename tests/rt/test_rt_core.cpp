// rt adapter integer core, branch conditions, link writes, HI/LO and COP0 (runtime/rt/rt_core.cpp).
// The arithmetic rules are tested in tests/ee/test_core.cpp / test_hilo.cpp / test_cop0.cpp; these
// cases check the plumbing: operand order, $zero drop, sign extension into the GPR, the upper GPR
// half, and the bus read behind BC0F.
#include "fake_hooks.h"

#include "p3fes_recomp_rt.h"

#include <cstring>

using namespace p3fes;
using rt_test::HooksScope;
using rt_test::TestHooks;

namespace {
struct CoreFixture {
    EEContext ctx;
    TestHooks hooks;
    HooksScope scope{&hooks};
    void set(unsigned r, u64 v) { ctx.gpr[r].u64[0] = v; }
    u64 g(unsigned r) const { return ctx.gpr[r].u64[0]; }
};
} // namespace

TEST_CASE("rt core: writes to $zero are dropped by every writer class") {
    CoreFixture f;
    f.set(4, 0x12345678u);
    f.set(5, 0x9u);
    rt::addu(f.ctx, 0, 4, 5);
    rt::addiu(f.ctx, 0, 4, 1);
    rt::lui(f.ctx, 0, 0x1234u);
    rt::sll(f.ctx, 0, 4, 4);
    rt::sllv(f.ctx, 0, 4, 5);
    rt::movz(f.ctx, 0, 4, 0);
    rt::mfhi(f.ctx, 0);
    rt::mult(f.ctx, 0, 4, 5);       // HI/LO still written
    rt::jalr(f.ctx, 0, 0x100000u);
    rt::mfc0(f.ctx, 0, 12);
    rt::mfc1(f.ctx, 0, 1);
    rt::cfc2(f.ctx, 0, 22, false);
    rt::qmfc2(f.ctx, 0, 0, false);
    rt::pcpyld(f.ctx, 0, 4, 5);
    rt::pmfhl(f.ctx, 0, 0);
    rt::mfsa(f.ctx, 0);
    CHECK(f.ctx.gpr[0].u64[0] == 0u);
    CHECK(f.ctx.gpr[0].u64[1] == 0u);
    CHECK(f.ctx.lo.u64[0] == 0xFFFFFFFFA3D70A38ull);  // the multiply happened: sext32(0x12345678 * 9)
}

TEST_CASE("rt core: 32-bit results are sign-extended; non-MMI writes keep bits 64..127") {
    CoreFixture f;
    f.ctx.gpr[2].u64[1] = 0x5555555555555555ull;
    f.set(4, 0x7FFFFFFFu);
    f.set(5, 1u);
    rt::addu(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 0xFFFFFFFF80000000ull);
    CHECK(f.ctx.gpr[2].u64[1] == 0x5555555555555555ull);
    rt::add(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 0xFFFFFFFF80000000ull);
    rt::subu(f.ctx, 2, 0, 5);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFFull);
    rt::sub(f.ctx, 2, 5, 4);
    CHECK(f.g(2) == 0xFFFFFFFF80000002ull);
    rt::addi(f.ctx, 2, 4, 1);
    CHECK(f.g(2) == 0xFFFFFFFF80000000ull);
    rt::addiu(f.ctx, 2, 0, -2);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFEull);
    rt::sll(f.ctx, 2, 5, 31);
    CHECK(f.g(2) == 0xFFFFFFFF80000000ull);
    f.set(6, 0xFFFFFFFF80000000ull);
    rt::srl(f.ctx, 2, 6, 1);
    CHECK(f.g(2) == 0x40000000u);
    rt::sra(f.ctx, 2, 6, 1);
    CHECK(f.g(2) == 0xFFFFFFFFC0000000ull);
    f.set(7, 33u);
    rt::srlv(f.ctx, 2, 6, 7);  // (rd, rt, rs): shift rt by rs & 31 = 1
    CHECK(f.g(2) == 0x40000000u);
    rt::srav(f.ctx, 2, 6, 7);
    CHECK(f.g(2) == 0xFFFFFFFFC0000000ull);
    rt::sllv(f.ctx, 2, 5, 7);
    CHECK(f.g(2) == 2u);
    rt::lui(f.ctx, 2, 0x8000u);
    CHECK(f.g(2) == 0xFFFFFFFF80000000ull);
    CHECK(f.ctx.gpr[2].u64[1] == 0x5555555555555555ull);
}

TEST_CASE("rt core: 64-bit ALU, immediates and compares") {
    CoreFixture f;
    f.set(4, 0xFFFFFFFFFFFFFFFFull);
    f.set(5, 2u);
    rt::daddu(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 1u);
    rt::dsubu(f.ctx, 2, 0, 5);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFEull);
    rt::daddiu(f.ctx, 2, 5, -3);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFFull);
    rt::and_(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 2u);
    rt::or_(f.ctx, 2, 0, 5);
    CHECK(f.g(2) == 2u);
    rt::xor_(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFDull);
    rt::nor(f.ctx, 2, 0, 0);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFFull);
    rt::andi(f.ctx, 2, 4, 0xFFFFu);
    CHECK(f.g(2) == 0xFFFFu);
    rt::ori(f.ctx, 2, 0, 0x8000u);
    CHECK(f.g(2) == 0x8000u);
    rt::xori(f.ctx, 2, 4, 0x00FFu);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFF00ull);
    rt::slt(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 1u);
    rt::sltu(f.ctx, 2, 4, 5);
    CHECK(f.g(2) == 0u);
    rt::slti(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 1u);
    rt::sltiu(f.ctx, 2, 5, -1);
    CHECK(f.g(2) == 1u);
    rt::dsll(f.ctx, 2, 5, 62);
    CHECK(f.g(2) == 0x8000000000000000ull);
    rt::dsrl(f.ctx, 3, 2, 63);
    CHECK(f.g(3) == 1u);
    rt::dsra(f.ctx, 3, 2, 60);
    CHECK(f.g(3) == 0xFFFFFFFFFFFFFFF8ull);
    rt::dsll32(f.ctx, 2, 5, 0);
    CHECK(f.g(2) == 0x200000000ull);
    rt::dsrl32(f.ctx, 3, 2, 1);  // 2^33 >> 33
    CHECK(f.g(3) == 1u);
    rt::dsra32(f.ctx, 3, 4, 31);
    CHECK(f.g(3) == 0xFFFFFFFFFFFFFFFFull);
    f.set(7, 66u);
    rt::dsllv(f.ctx, 2, 5, 7);  // 66 & 63 = 2
    CHECK(f.g(2) == 8u);
    rt::dsrlv(f.ctx, 2, 4, 7);
    CHECK(f.g(2) == 0x3FFFFFFFFFFFFFFFull);
    f.set(8, 0x100000000ull);  // non-zero only in the upper word
    f.set(2, 7u);
    rt::movn(f.ctx, 2, 5, 8);
    CHECK(f.g(2) == 2u);
    rt::movz(f.ctx, 2, 4, 8);
    CHECK(f.g(2) == 2u);
    rt::movz(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFFFFull);
}

TEST_CASE("rt core: link writes and register reads for control flow") {
    CoreFixture f;
    rt::jal(f.ctx, 0x00100010u);
    CHECK(f.g(31) == 0x00100018u);
    rt::jalr(f.ctx, 5, 0x00123450u);
    CHECK(f.g(5) == 0x00123458u);
    f.set(9, 0xFFFFFFFF80401000ull);
    CHECK(rt::reg32(f.ctx, 9) == 0x80401000u);
    f.set(4, 0x100000000ull);
    f.set(5, 0u);
    CHECK_FALSE(rt::cmp_eq(f.ctx, 4, 5));  // 64-bit compare
    CHECK(rt::cmp_ne(f.ctx, 4, 5));
    CHECK(rt::cmp_eq(f.ctx, 5, 0));
    f.set(6, 0x80000000u);                 // positive 64-bit value
    CHECK(rt::cmp_gtz(f.ctx, 6));
    CHECK_FALSE(rt::cmp_lez(f.ctx, 6));
    CHECK(rt::cmp_gez(f.ctx, 6));
    f.set(6, 0xFFFFFFFF80000000ull);
    CHECK(rt::cmp_ltz(f.ctx, 6));
    CHECK(rt::cmp_lez(f.ctx, 6));
    CHECK(rt::cmp_lez(f.ctx, 0));
    CHECK(rt::cmp_gez(f.ctx, 0));
}

TEST_CASE("rt core: multiply/divide on pipe 0, three-operand rd, HI/LO moves") {
    CoreFixture f;
    f.set(4, 0xFFFFFFFFu);  // -1
    f.set(5, 2u);
    rt::mult(f.ctx, 3, 4, 5);
    CHECK(f.g(3) == 0xFFFFFFFFFFFFFFFEull);  // rd <- LO
    CHECK(f.ctx.hi.u64[0] == 0xFFFFFFFFFFFFFFFFull);
    rt::multu(f.ctx, 3, 4, 5);
    CHECK(f.g(3) == 0xFFFFFFFFFFFFFFFEull);
    CHECK(f.ctx.hi.u64[0] == 1u);
    f.set(6, 7u);
    rt::div(f.ctx, 6, 5);
    rt::mflo(f.ctx, 2);
    rt::mfhi(f.ctx, 3);
    CHECK(f.g(2) == 3u);
    CHECK(f.g(3) == 1u);
    rt::divu(f.ctx, 4, 5);
    rt::mflo(f.ctx, 2);
    CHECK(f.g(2) == 0x7FFFFFFFu);
    f.set(7, 0x1122334455667788ull);
    rt::mthi(f.ctx, 7);
    rt::mtlo(f.ctx, 0);
    CHECK(f.ctx.hi.u64[0] == 0x1122334455667788ull);
    CHECK(f.ctx.lo.u64[0] == 0u);
    CHECK(f.ctx.lo.u64[1] == 0u);  // pipe 1 untouched by pipe-0 ops
}

TEST_CASE("rt core: COP0 status, moves, ERET; SYNC and CACHE are no-ops") {
    CoreFixture f;
    rt::ei(f.ctx);
    rt::mfc0(f.ctx, 2, 12);
    CHECK(f.g(2) == 0x10000u);
    rt::di(f.ctx);
    rt::mfc0(f.ctx, 2, 12);
    CHECK(f.g(2) == 0u);
    f.set(4, 0x80001234u);
    rt::mtc0(f.ctx, 4, 14);  // EPC
    rt::mfc0(f.ctx, 3, 14);
    CHECK(f.g(3) == 0xFFFFFFFF80001234ull);  // MFC0 sign-extends
    f.ctx.cop0[12] = 0x2u;  // EXL
    rt::eret(f.ctx, 0x50d0f0u);
    CHECK(f.ctx.cop0[12] == 0u);
    const EEContext before = f.ctx;
    rt::sync(f.ctx, 0x10);
    rt::sync(f.ctx, 0);
    rt::cache(f.ctx, 0x18, 4, 0);
    CHECK(std::memcmp(before.gpr, f.ctx.gpr, sizeof before.gpr) == 0);
    CHECK(std::memcmp(before.cop0, f.ctx.cop0, sizeof before.cop0) == 0);
    CHECK(before.cycles == f.ctx.cycles);
}

TEST_CASE("rt core: BC0F reads CPCOND0 from D_PCR / D_STAT through the bus") {
    CoreFixture f;
    rt_test::RecordingBus& bus = f.hooks.bus_;
    bus.regs[0x1000E020u] = 0u;  // D_PCR: no channel selected
    bus.regs[0x1000E010u] = 0u;
    CHECK(rt::cop0_cond(f.ctx));
    REQUIRE(bus.log.size() == 2);
    CHECK(bus.log[0].pa == 0x1000E020u);
    CHECK(bus.log[1].pa == 0x1000E010u);
    CHECK(bus.log[0].bits == 32);
    bus.regs[0x1000E020u] = 0x4u;  // channel 2 (GIF) selected
    CHECK_FALSE(rt::cop0_cond(f.ctx));
    bus.regs[0x1000E010u] = 0x4u;  // GIF CIS set
    CHECK(rt::cop0_cond(f.ctx));
}
