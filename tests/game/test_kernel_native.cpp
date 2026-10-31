// Modernize layer 6, step 1 (docs/MODERNIZE_PLAN.md "Layer 6 status", ADR-0017): the game's kernel calls with the
// host's kernel service installed (p3fes/native/kernel_service.h, `--native kernel`):
//   - the libkernel stubs (_sceWaitSema, _sceGetThreadId, _sceiSignalSema, _sceFlushCache) hand the call to the service
//     with $v1 = their call number and their syscall address, and execute no `syscall`;
//   - CRI ADX's thread lock (sub_53F8B8: GetThreadId + ChangeThreadPriority + its ResumeThread helper) runs the same
//     path, with the same registers, guest memory, virtual time and check points as with the instruction, when the
//     service answers what the kernel answers;
//   - without the service every stub executes its faithful `syscall` (the pair tests of the stubs' files cover that).
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/native/kernel_service.h"

#include <cstring>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using namespace p3fes::game_test;
namespace nk = p3fes::native::kernel;

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
void fn__sceWaitSema_005031a0(EEContext&);
void fn__sceGetThreadId_00503050(EEContext&);
void fn__sceiSignalSema_00503190(EEContext&);
void fn__sceFlushCache_005033e0(EEContext&);
void fn_sub_53F8B8_0053f8b8(EEContext&);
}  // namespace p3fes::recomp_gen

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

namespace {

// Records each call and answers as rt_test::TestHooks::syscall does (so both paths see the same $v0).
struct FakeKernel final : nk::KernelService {
    struct Call {
        s64 v1;
        u32 pc;
        u64 a0;
    };
    std::vector<Call> calls;
    void call(EEContext& ctx, u32 pc) override {
        calls.push_back({static_cast<s64>(static_cast<s32>(ctx.gpr[GPR_V1].u32[0])), pc, ctx.gpr[GPR_A0].u64[0]});
        ctx.gpr[GPR_V0].u64[0] = 0x600DF00Du;
    }
};

struct ServiceScope {
    explicit ServiceScope(nk::KernelService* s) { nk::g_service = s; }
    ~ServiceScope() { nk::g_service = nullptr; }
};

constexpr u32 kAdxLo = 0x788600u, kAdxHi = 0x790000u;  // CRI ADX's thread-manager globals (0x788650.., 0x78FF70..)

}  // namespace

TEST_CASE("game(kernel_native): the libkernel stubs hand their call to the native kernel service, no syscall") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    struct Stub {
        Fn fn;
        s64 number;
        u32 pc;
    };
    const Stub stubs[] = {
        {&recomp_gen::fn__sceWaitSema_005031a0, 0x44, 0x5031A4u},
        {&recomp_gen::fn__sceGetThreadId_00503050, 0x2F, 0x503054u},
        {&recomp_gen::fn__sceiSignalSema_00503190, -0x43, 0x503194u},
        {&recomp_gen::fn__sceFlushCache_005033e0, 0x64, 0x5033E4u},
    };
    for (const Stub& s : stubs) {
        // Faithful: the instruction.
        const int sys0 = m.hooks.syscalls;
        const Outcome f = run(m, s.fn, {7, 0, 0, 0}, 11);
        CHECK(m.hooks.syscalls == sys0 + 1);
        CHECK(static_cast<s64>(static_cast<s32>(m.hooks.syscall_v1)) == s.number);
        CHECK(m.hooks.syscall_pc == s.pc);
        // Native: the service, with the same number, address and argument; the same result and time.
        FakeKernel fk;
        ServiceScope svc(&fk);
        const int sys1 = m.hooks.syscalls;
        const Outcome n = run(m, s.fn, {7, 0, 0, 0}, 11);
        CHECK(m.hooks.syscalls == sys1);  // no syscall reached the hooks
        REQUIRE(fk.calls.size() == 1);
        CHECK(fk.calls[0].v1 == s.number);
        CHECK(fk.calls[0].pc == s.pc);
        CHECK(fk.calls[0].a0 == 7);
        CHECK(n.v0 == f.v0);
        CHECK(n.cycles == f.cycles);
        CHECK(n.checks == f.checks);
        CHECK(m.ctx.gpr[GPR_V1].u64[0] == static_cast<u64>(s.number));  // $v1 as the stub set it
    }
}

TEST_CASE("game(kernel_native): CRI ADX's thread lock runs the same path through the service as through syscall") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::memset(m.at(kAdxLo), 0, kAdxHi - kAdxLo);
    const std::vector<u8> before = m.bytes(kAdxLo, kAdxHi - kAdxLo);
    const int sys0 = m.hooks.syscalls;
    const Outcome f = run(m, &recomp_gen::fn_sub_53F8B8_0053f8b8, {0, 0, 0, 0}, 5);
    const int faithful_calls = m.hooks.syscalls - sys0;
    const std::vector<u8> after_f = m.bytes(kAdxLo, kAdxHi - kAdxLo);
    CHECK(faithful_calls >= 2);  // GetThreadId + ChangeThreadPriority (+ the resume helper's)
    std::memcpy(m.at(kAdxLo), before.data(), before.size());

    FakeKernel fk;
    ServiceScope svc(&fk);
    const int sys1 = m.hooks.syscalls;
    const Outcome n = run(m, &recomp_gen::fn_sub_53F8B8_0053f8b8, {0, 0, 0, 0}, 5);
    CHECK(m.hooks.syscalls == sys1);
    CHECK(static_cast<int>(fk.calls.size()) == faithful_calls);
    REQUIRE(!fk.calls.empty());
    CHECK(fk.calls[0].v1 == 0x2F);  // GetThreadId first
    CHECK(n.v0 == f.v0);
    CHECK(std::memcmp(n.saved, f.saved, sizeof f.saved) == 0);
    CHECK(n.cycles == f.cycles);
    CHECK(n.checks == f.checks);
    CHECK(n.arena == f.arena);
    CHECK(m.bytes(kAdxLo, kAdxHi - kAdxLo) == after_f);
}

#else
TEST_CASE("game(kernel_native): skipped (no generated program)") { MESSAGE("SKIP: P3FES_GAME_HAVE_GENERATED=0"); }
#endif
