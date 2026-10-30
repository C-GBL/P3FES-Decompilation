#include <doctest.h>

#include <cstring>
#include <new>

#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/syscalls.h"

using namespace p3fes;

namespace {

bool all_zero(const void* p, std::size_t n) {
    const unsigned char* b = static_cast<const unsigned char*>(p);
    for (std::size_t i = 0; i < n; ++i) {
        if (b[i] != 0) {
            return false;
        }
    }
    return true;
}

} // namespace

TEST_CASE("EEContext default-initialises every register to zero") {
    // Construct over dirty storage so default member initialisers, not luck,
    // are what makes the fields zero.
    alignas(EEContext) unsigned char storage[sizeof(EEContext)];
    std::memset(storage, 0xFF, sizeof(storage));
    EEContext* ctx = new (storage) EEContext;

    CHECK(all_zero(ctx->gpr, sizeof(ctx->gpr)));
    CHECK(all_zero(&ctx->hi, sizeof(ctx->hi)));
    CHECK(all_zero(&ctx->lo, sizeof(ctx->lo)));
    CHECK(ctx->pc == 0);
    CHECK(ctx->sa == 0);
    CHECK(all_zero(ctx->fpr, sizeof(ctx->fpr)));
    CHECK(ctx->acc == 0);
    CHECK(ctx->fcr0 == 0);
    CHECK(ctx->fcr31 == 0);
    CHECK(all_zero(ctx->cop0, sizeof(ctx->cop0)));
    // vf00 is the hardware constant (0, 0, 0, 1.0f); every other vf register is zero.
    CHECK(ctx->vu0.vf[0][0] == 0);
    CHECK(ctx->vu0.vf[0][1] == 0);
    CHECK(ctx->vu0.vf[0][2] == 0);
    CHECK(ctx->vu0.vf[0][3] == 0x3F800000u);
    CHECK(all_zero(ctx->vu0.vf[1], sizeof(ctx->vu0.vf) - sizeof(ctx->vu0.vf[0])));
    CHECK(all_zero(ctx->vu0.vi, sizeof(ctx->vu0.vi)));
    CHECK(all_zero(ctx->vu0.acc, sizeof(ctx->vu0.acc)));
    CHECK(ctx->vu0.q == 0);
    CHECK(ctx->vu0.p == 0);
    CHECK(ctx->vu0.i == 0);
    CHECK(ctx->vu0.r == 0);
    CHECK(ctx->vu0.status == 0);
    CHECK(ctx->vu0.mac == 0);
    CHECK(ctx->vu0.clip == 0);
    CHECK(ctx->vu0.tpc == 0);
    CHECK(ctx->vu0.cmsar0 == 0);
    CHECK(ctx->memory == nullptr);

    ctx->~EEContext();
}

TEST_CASE("EEContext layout matches the R5900 register model") {
    CHECK(sizeof(EEContext::gpr) == 32 * 16);
    CHECK(alignof(EEContext) >= 16);
    CHECK(sizeof(VU0State::vf) == 32 * 4 * sizeof(u32));
    CHECK(sizeof(EEContext::fpr) == 32 * sizeof(u32));
    CHECK(sizeof(VU0State::vi) == 16 * sizeof(u16));
    CHECK(GPR_RA == 31);
    CHECK(GPR_SP == 29);
}

TEST_CASE("SyscallTable starts empty and dispatches by raw number") {
    SyscallTable table;
    for (u32 i = 0; i < SyscallTable::kCount; ++i) {
        CHECK(table.get(static_cast<u8>(i)) == nullptr);
    }
    table.set(EESyscall::FlushCache, [](EEContext& ctx) { ctx.pc = 0x64; });
    CHECK(table.get(0x64) != nullptr);
    CHECK(table.get(0x63) == nullptr);

    EEContext ctx;
    table.get(0x64)(ctx);
    CHECK(ctx.pc == 0x64);
}
