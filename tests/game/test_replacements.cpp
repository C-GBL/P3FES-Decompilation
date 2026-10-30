// Phase 5 gate at function level (GOAL.md: "Each replaced function must pass the trace diff before the
// recompiled version is removed"): the hand-written function and the recompiled body it replaces run
// on two identical guest machines and must agree on
//   * the result ($v0, 64-bit as the caller sees it),
//   * every callee-saved register ($s0..$s7, $gp, $sp, $fp, $ra) -- caller-saved temporaries are free,
//   * guest memory outside the dead stack (the recompiled body spills below $sp; the hand version does not),
//   * virtual time: the same `ctx.cycles` delta (ADR-0013 §2),
//   * check points: the same number of rt::check_events calls (interrupts are delivered at the same places).
// The whole-program gate is the deterministic dorm replay (BUILDING.md), byte-identical before and after.
#include "fake_hooks.h"

#include "elf_image.h"
#include "p3fes/ee_memory.h"
#include "p3fes/game/cri_rofs.h"
#include "p3fes_recomp_rt.h"

#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using rt_test::FatalEvent;
using rt_test::HooksScope;
using rt_test::TestHooks;

REGISTER_EXCEPTION_TRANSLATOR(const p3fes::rt_test::FatalEvent& e) {
    return doctest::String(("RtHooks::fatal: " + e.what).c_str());
}

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
// Declared here rather than through the generated functions.h so the test names exactly the pairs it checks.
void fn_rfdir_toUpperFname_0056bc78(EEContext&);
void fn_rfdir_toUpperFname_0056bc78__recomp(EEContext&);
void fn_rfdir_getSearchID_0056bc10(EEContext&);
void fn_rfdir_getSearchID_0056bc10__recomp(EEContext&);
void fn_RFMAI_ToUpperStr_00569848(EEContext&);
void fn_RFMAI_ToUpperStr_00569848__recomp(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

constexpr u32 kGp = 0x007D2CF0u;     // crt0's $gp (RUNTIME_CONTRACT H-46)
constexpr u32 kSp = 0x01FFFF00u;     // inside the main-thread stack 0x1F60000-0x2000000
constexpr u32 kArena = 0x01800000u;  // scratch arena for arguments: free RAM far above .bss/heap start
constexpr u32 kArenaSize = 0x2000u;
constexpr u32 kDeadStack = 0x400u;   // bytes below $sp the recompiled body may spill into

u64 sx(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

const char* elf_path() {
    const char* p = std::getenv("P3FES_ELF");
    return p ? p : P3FES_ELF_DEFAULT;
}

// One guest machine: the ELF image in RAM, a fresh context per call.
struct Machine {
    EEMemory mem;
    EEContext ctx;
    TestHooks hooks;

    const char* load_elf(const char* path) {
        recomp::ElfImage elf;
        const recomp::ElfImage::LoadResult r = elf.load(path);
        if (r.error) return r.error;
        for (const recomp::ElfSegment& s : elf.segments()) {
            if (s.vaddr + s.memsz > EEMemory::kMainRamSize) return "segment outside main RAM";
            if (s.filesz == 0) continue;
            const u8* bytes = elf.bytes_at(s.vaddr, s.filesz);
            if (!bytes) return "segment bytes unavailable";
            std::memcpy(mem.main_ram() + s.vaddr, bytes, s.filesz);
        }
        return nullptr;
    }
    void fresh_context(u64 a0, u64 a1, std::mt19937& rng) {
        ctx = EEContext{};
        ctx.memory = &mem;
        for (unsigned r = 1; r < 32; ++r) {  // callee-saved registers carry random values the callee must keep
            ctx.gpr[r].u64[0] = (static_cast<u64>(rng()) << 32) | rng();
            ctx.gpr[r].u64[1] = rng();
        }
        ctx.gpr[GPR_ZERO].u64[0] = ctx.gpr[GPR_ZERO].u64[1] = 0;
        ctx.gpr[GPR_A0].u64[0] = a0;
        ctx.gpr[GPR_A1].u64[0] = a1;
        ctx.gpr[GPR_SP].u64[0] = sx(kSp);
        ctx.gpr[GPR_GP].u64[0] = sx(kGp);
        ctx.gpr[GPR_RA].u64[0] = sx(0x00100008u);
        ctx.cycles = 1000;
    }
};

struct Outcome {
    u64 v0 = 0;
    u64 saved[12] = {};  // s0..s7, gp, sp, fp, ra
    u64 cycles = 0;
    int checks = 0;
    std::vector<u8> arena;
    std::vector<u8> live_stack;  // [sp, sp + 0x100): the caller's frame, must not change
};

Outcome run(Machine& m, void (*fn)(EEContext&), u64 a0, u64 a1, std::mt19937 rng_seed_copy) {
    HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    m.fresh_context(a0, a1, rng_seed_copy);
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Outcome o;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.arena.assign(m.mem.main_ram() + kArena, m.mem.main_ram() + kArena + kArenaSize);
    o.live_stack.assign(m.mem.main_ram() + kSp, m.mem.main_ram() + kSp + 0x100);
    // Scrub the dead stack so the next run starts from the same bytes.
    std::memset(m.mem.main_ram() + kSp - kDeadStack, 0, kDeadStack);
    return o;
}

void expect_same(const Outcome& hand, const Outcome& recomp, const char* what) {
    INFO(what);
    CHECK(hand.v0 == recomp.v0);
    for (int i = 0; i < 12; ++i) CHECK(hand.saved[i] == recomp.saved[i]);
    CHECK(hand.cycles == recomp.cycles);
    CHECK(hand.checks == recomp.checks);
    CHECK(hand.arena == recomp.arena);
    CHECK(hand.live_stack == recomp.live_stack);
}

}  // namespace

TEST_CASE("game: rfdir_toUpperFname equals its recompiled body on every byte") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err) << " (set P3FES_ELF)");
        return;
    }
    std::mt19937 rng{0xC0FFEEu};
    for (unsigned c = 0; c < 256; ++c) {
        // The caller passes the byte sign-extended (lb) or zero-extended (lbu); the body shifts it to a byte either way.
        for (u64 a0 : {sx(static_cast<u32>(static_cast<s8>(c))), static_cast<u64>(c), 0xDEADBEEF00ull | c}) {
            const u32 seed = rng();
            const Outcome h = run(m, &recomp_gen::fn_rfdir_toUpperFname_0056bc78, a0, 0, std::mt19937{seed});
            const Outcome r = run(m, &recomp_gen::fn_rfdir_toUpperFname_0056bc78__recomp, a0, 0, std::mt19937{seed});
            expect_same(h, r, "rfdir_toUpperFname");
        }
    }
    // The documented rule (docs/ANALYSIS/11 §1), independently of the recompiled body.
    HooksScope scope{&m.hooks};  // the hand-written functions reach rt::check_events too
    rt::bind_context(&m.ctx);
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, 'a')) == 'A');
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, 'z')) == 'Z');
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, 'A')) == 'A');
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, '.')) == 0);
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, '_')) == '_');
    CHECK(static_cast<u8>(game::rfdir_toUpperFname(m.ctx, static_cast<char>(0xE9))) == 0xE9);
}

TEST_CASE("game: rfdir_getSearchID equals its recompiled body on random and table names") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err) << " (set P3FES_ELF)");
        return;
    }
    std::mt19937 rng{0x5EA4C41Du};
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.";
    int cases = 0;
    for (int i = 0; i < 400; ++i) {
        const u32 at = kArena + 16 + rng() % (kArenaSize - 0x400);
        const std::size_t len = (i < 8) ? static_cast<std::size_t>(i) : rng() % 300;
        u8* p = m.mem.main_ram() + at;
        for (std::size_t k = 0; k < len; ++k) {
            const unsigned pick = rng() % 10;
            p[k] = pick < 8 ? static_cast<u8>(alphabet[rng() % alphabet.size()]) : static_cast<u8>(1 + rng() % 255);
        }
        p[len] = 0;
        const u32 seed = rng();
        const Outcome h = run(m, &recomp_gen::fn_rfdir_getSearchID_0056bc10, sx(at), 0, std::mt19937{seed});
        const Outcome r = run(m, &recomp_gen::fn_rfdir_getSearchID_0056bc10__recomp, sx(at), 0, std::mt19937{seed});
        expect_same(h, r, "rfdir_getSearchID");
        CHECK(h.v0 <= 0xFF);
        ++cases;
    }
    // Known values: the empty name (218 >> 2 = 54) and the formula on a real entry name.
    HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    CHECK(game::rfdir_getSearchID(m.ctx, "") == 54);
    CHECK(game::rfdir_getSearchID(m.ctx, "slus_216.21") == game::rfdir_getSearchID(m.ctx, "SLUS_216.21"));
    CHECK(game::rfdir_getSearchID(m.ctx, "NAME") == game::rfdir_getSearchID(m.ctx, "NAME."));
    MESSAGE("rfdir_getSearchID: " << cases << " random names compared");
}

TEST_CASE("game: RFMAI_ToUpperStr 0x569848 equals its recompiled body: in-place uppercase, null pointer, strlen kept recompiled") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err) << " (set P3FES_ELF)");
        return;
    }
    std::mt19937 rng{0x7E57A11Eu};
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.@{}[]";
    for (int i = 0; i < 400; ++i) {
        const u32 at = kArena + 16 + rng() % (kArenaSize - 0x400);
        const std::size_t len = (i < 8) ? static_cast<std::size_t>(i) : rng() % 300;
        std::vector<u8> text(len + 1, 0);
        for (std::size_t k = 0; k < len; ++k) {
            const unsigned pick = rng() % 10;
            text[k] = pick < 8 ? static_cast<u8>(alphabet[rng() % alphabet.size()]) : static_cast<u8>(1 + rng() % 255);
        }
        const u32 seed = rng();
        // The function writes the string: each run starts from the same bytes.
        std::memcpy(m.mem.main_ram() + at, text.data(), text.size());
        const Outcome h = run(m, &recomp_gen::fn_RFMAI_ToUpperStr_00569848, sx(at), 0, std::mt19937{seed});
        std::vector<u8> after_hand(m.mem.main_ram() + at, m.mem.main_ram() + at + text.size());
        std::memcpy(m.mem.main_ram() + at, text.data(), text.size());
        const Outcome r = run(m, &recomp_gen::fn_RFMAI_ToUpperStr_00569848__recomp, sx(at), 0, std::mt19937{seed});
        std::vector<u8> after_recomp(m.mem.main_ram() + at, m.mem.main_ram() + at + text.size());
        INFO("RFMAI_ToUpperStr");
        for (int k = 0; k < 12; ++k) CHECK(h.saved[k] == r.saved[k]);
        CHECK(h.cycles == r.cycles);
        CHECK(h.checks == r.checks);
        CHECK(h.arena == r.arena);
        CHECK(h.live_stack == r.live_stack);
        CHECK(after_hand == after_recomp);
        // And the documented effect: a-z uppercased, everything else untouched, NUL in place.
        for (std::size_t k = 0; k < len; ++k) {
            const u8 c = text[k];
            CHECK(after_hand[k] == ((c >= 'a' && c <= 'z') ? static_cast<u8>(c - 32) : c));
        }
        CHECK(after_hand[len] == 0);
    }
    // Null pointer: both return at once, nothing written, same cost.
    const u32 seed = rng();
    const Outcome h0 = run(m, &recomp_gen::fn_RFMAI_ToUpperStr_00569848, 0, 0, std::mt19937{seed});
    const Outcome r0 = run(m, &recomp_gen::fn_RFMAI_ToUpperStr_00569848__recomp, 0, 0, std::mt19937{seed});
    CHECK(h0.cycles == r0.cycles);
    CHECK(h0.checks == r0.checks);
    CHECK(h0.arena == r0.arena);
}

#else

TEST_CASE("game: replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game needs the ELF at configure time (P3FES_RT_EXEC_ELF)");
}

#endif
