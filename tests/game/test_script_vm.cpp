// Phase 5 pair tests for the script-VM replacements (game/src/script/script_vm.cpp, script_ops.cpp),
// modelled on test_replacements.cpp: the hand-written function and the recompiled body it replaces run
// on two identical guest machines and must agree on the result ($v0), every callee-saved register, guest
// memory outside the dead stack (here: the whole scratch arena, which the functions write, plus the
// VM's .bss words -- scrOperation's scratch and g_scrCurrentTask), the virtual cycles and the number of
// check points (ADR-0013). Each case also checks the documented rule (docs/ANALYSIS/18_script_vm.md)
// independently of the recompiled body.
//
// K_Assert (sub_19D3F0) and K_Abort (sub_19D400) are `jr $ra` in this build, so every "bad input" path
// (sp outside 0..27, unknown tags, division by zero, out-of-range label index) returns and is compared
// here like any other.
#include "fake_hooks.h"

#include "elf_image.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee_memory.h"
#include "p3fes/game/script_vm.h"
#include "p3fes_recomp_rt.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using rt_test::HooksScope;
using rt_test::TestHooks;

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_CodeFunc_Proc_0035cf00)
P3FES_DECL_PAIR(fn_CodeFunc_Jmp_0035d1d0)
P3FES_DECL_PAIR(fn_CodeFunc_Goto_0035d310)
P3FES_DECL_PAIR(fn_ApplyRelocTable_0035ac90)
P3FES_DECL_PAIR(fn_CodeFunc_PushI_0035c300)
P3FES_DECL_PAIR(fn_CodeFunc_PushS_0035c3b0)
P3FES_DECL_PAIR(fn_CodeFunc_PushF_0035c450)
P3FES_DECL_PAIR(fn_CodeFunc_PushIX_0035c500)
P3FES_DECL_PAIR(fn_CodeFunc_PushIF_0035c5b0)
P3FES_DECL_PAIR(fn_CodeFunc_PushLIX_0035c660)
P3FES_DECL_PAIR(fn_CodeFunc_PushLFX_0035c710)
P3FES_DECL_PAIR(fn_CodeFunc_PushSTR_0035c7c0)
P3FES_DECL_PAIR(fn_CodeFunc_PushREG_0035c870)
P3FES_DECL_PAIR(fn_CodeFunc_PopIX_0035c900)
P3FES_DECL_PAIR(fn_CodeFunc_PopFX_0035ca70)
P3FES_DECL_PAIR(fn_CodeFunc_PopLIX_0035cc00)
P3FES_DECL_PAIR(fn_CodeFunc_PopLFX_0035cd70)
P3FES_DECL_PAIR(fn_CodeFunc_End_0035d040)
P3FES_DECL_PAIR(fn_CodeFunc_Call_0035d210)
P3FES_DECL_PAIR(fn_scrOperation_0035d350)
P3FES_DECL_PAIR(fn_CodeFunc_Add_0035dfe0)
P3FES_DECL_PAIR(fn_CodeFunc_Sub_0035e020)
P3FES_DECL_PAIR(fn_CodeFunc_Mul_0035e060)
P3FES_DECL_PAIR(fn_CodeFunc_Div_0035e0a0)
P3FES_DECL_PAIR(fn_CodeFunc_Minus_0035e0e0)
P3FES_DECL_PAIR(fn_CodeFunc_Not_0035e250)
P3FES_DECL_PAIR(fn_CodeFunc_Or_0035e650)
P3FES_DECL_PAIR(fn_CodeFunc_And_0035e690)
P3FES_DECL_PAIR(fn_CodeFunc_Eq_0035e6d0)
P3FES_DECL_PAIR(fn_CodeFunc_Neq_0035e710)
P3FES_DECL_PAIR(fn_CodeFunc_S_0035e750)
P3FES_DECL_PAIR(fn_CodeFunc_L_0035e790)
P3FES_DECL_PAIR(fn_CodeFunc_SE_0035e7d0)
P3FES_DECL_PAIR(fn_CodeFunc_LE_0035e810)
P3FES_DECL_PAIR(fn_CodeFunc_IF_0035e850)
P3FES_DECL_PAIR(fn_scrGetIntPara_0035ed20)
P3FES_DECL_PAIR(fn_scrGetFloatPara_0035ee60)
P3FES_DECL_PAIR(fn_scrGetStrPara_0035efa0)
P3FES_DECL_PAIR(fn_scrSetIntReturnVal_0035f060)
P3FES_DECL_PAIR(fn_scrSetFloatReturnVal_0035f080)
P3FES_DECL_PAIR(fn_scrGetLabelAddr_0035f0a0)
P3FES_DECL_PAIR(fn_scrSetPC_0035f120)
P3FES_DECL_PAIR(fn_scrGetCmdTimer_0035f130)
P3FES_DECL_PAIR(fn_scrGetMessageID_0035f140)
P3FES_DECL_PAIR(fn_scrGetCurrent_0035f150)
P3FES_DECL_PAIR(fn_scrGetUserData_0035f160)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

constexpr u32 kGp = 0x007D2CF0u;     // crt0's $gp
constexpr u32 kSp = 0x01FFFF00u;     // inside the main-thread stack 0x1F60000-0x2000000
constexpr u32 kArena = 0x01800000u;  // scratch arena: free RAM far above .bss/heap start
constexpr u32 kArenaSize = 0x2000u;
constexpr u32 kDeadStack = 0x400u;

// The VM's .bss words outside the arena that the handlers read or write: scrOperation's scratch
// (0x7CE588..0x7CE5A4) and g_scrCurrentTask 0x7CE5A8. Seeded per run so both runs of a pair start alike
// and compared afterwards.
constexpr u32 kVmBss = 0x7CE580u;
constexpr u32 kVmBssSize = 0x30u;

u64 sx(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

const char* elf_path() {
    const char* p = std::getenv("P3FES_ELF");
    return p ? p : P3FES_ELF_DEFAULT;
}

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
    u8* arena() { return mem.main_ram() + kArena; }
    u8* at(u32 va) { return mem.main_ram() + va; }
    void fresh_context(const u64 args[4], std::mt19937& rng) {
        ctx = EEContext{};
        ctx.memory = &mem;
        for (unsigned r = 1; r < 32; ++r) {
            ctx.gpr[r].u64[0] = (static_cast<u64>(rng()) << 32) | rng();
            ctx.gpr[r].u64[1] = rng();
        }
        ctx.gpr[GPR_ZERO].u64[0] = ctx.gpr[GPR_ZERO].u64[1] = 0;
        for (unsigned i = 0; i < 4; ++i) ctx.gpr[GPR_A0 + i].u64[0] = args[i];
        ctx.gpr[GPR_SP].u64[0] = sx(kSp);
        ctx.gpr[GPR_GP].u64[0] = sx(kGp);
        ctx.gpr[GPR_RA].u64[0] = sx(0x00100008u);
        for (unsigned f = 0; f < 32; ++f) ctx.fpr[f] = rng();  // $f12 carries scrSetFloatReturnVal's argument
        ctx.cycles = 1000;
    }
};

struct Outcome {
    u64 v0 = 0;
    u64 saved[12] = {};
    u64 cycles = 0;
    int checks = 0;
    u32 f0 = 0;      // $f0 after the run (scrGetFloatPara's result)
    u32 f12_in = 0;  // $f12 before the run (scrSetFloatReturnVal's argument)
    std::vector<u8> arena;
    std::vector<u8> live_stack;
    std::vector<u8> vm_bss;
};

// The seeded contents of the VM's .bss words before a run (scrOperation's stale result words are
// observable when `op` >= 12, so the rule checks need to know them).
u32 bss_pattern(u32 seed, u32 off) { return (seed * 0x9E3779B9u) ^ (off * 0x85EBCA6Bu) ^ 0x5CA1AB1Eu; }

// Runs `fn` on the arena image `image` (restored first) and returns what the caller can observe.
// g_scrGlobals (0x7CCA5C) points at arena + globals_off, g_scrCurrentTask at arena + task_off.
Outcome run(Machine& m, void (*fn)(EEContext&), const std::vector<u8>& image, const u64 args[4], u32 seed,
            u32 globals_off = 0x1800, u32 task_off = 0) {
    std::memcpy(m.arena(), image.data(), image.size());
    for (u32 off = 0; off < kVmBssSize; off += 4) {
        const u32 w = bss_pattern(seed, off);
        std::memcpy(m.at(kVmBss + off), &w, 4);
    }
    const u32 globals = kArena + globals_off, task = kArena + task_off;
    std::memcpy(m.at(game::scr::kGlobalsPtr), &globals, 4);
    std::memcpy(m.at(game::scr::kCurrentTask), &task, 4);
    HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    const u32 f12_in = m.ctx.fpr[12];
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    fn(m.ctx);
    Outcome o;
    o.f12_in = f12_in;
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    const unsigned regs[12] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
    for (int i = 0; i < 12; ++i) o.saved[i] = m.ctx.gpr[regs[i]].u64[0];
    o.cycles = m.ctx.cycles - c0;
    o.checks = m.hooks.checks - k0;
    o.f0 = m.ctx.fpr[0];
    o.arena.assign(m.arena(), m.arena() + kArenaSize);
    o.live_stack.assign(m.mem.main_ram() + kSp, m.mem.main_ram() + kSp + 0x100);
    o.vm_bss.assign(m.at(kVmBss), m.at(kVmBss) + kVmBssSize);
    std::memset(m.mem.main_ram() + kSp - kDeadStack, 0, kDeadStack);
    return o;
}

void expect_same(const Outcome& hand, const Outcome& recomp, const char* what, bool compare_v0 = true) {
    INFO(what);
    if (compare_v0) CHECK(hand.v0 == recomp.v0);
    for (int i = 0; i < 12; ++i) CHECK(hand.saved[i] == recomp.saved[i]);
    CHECK(hand.cycles == recomp.cycles);
    CHECK(hand.checks == recomp.checks);
    CHECK(hand.arena == recomp.arena);
    CHECK(hand.live_stack == recomp.live_stack);
    CHECK(hand.vm_bss == recomp.vm_bss);
}

u32 rd32(const std::vector<u8>& v, u32 off) {
    u32 x;
    std::memcpy(&x, v.data() + off, 4);
    return x;
}
void wr32(std::vector<u8>& v, u32 off, u32 x) { std::memcpy(v.data() + off, &x, 4); }
s8 rds8(const std::vector<u8>& v, u32 off) { return static_cast<s8>(v[off]); }

// Arena layout for the opcode handlers: task record at +0, instruction words at +0x100 (512 words),
// procedure labels at +0xA00 and jump labels at +0x1200 (64 records of 32 bytes each).
constexpr u32 kTask = 0x000, kInsn = 0x100, kInsnWords = 512, kProc = 0xA00, kJump = 0x1200, kLabels = 64;

std::vector<u8> task_image(std::mt19937& rng, s32 pc, s16 operand) {
    std::vector<u8> img(kArenaSize);
    for (u8& b : img) b = static_cast<u8>(rng());
    wr32(img, kTask + game::scr::kPc, static_cast<u32>(pc));
    wr32(img, kTask + game::scr::kInsn, kArena + kInsn);
    wr32(img, kTask + game::scr::kProcLabels, kArena + kProc);
    wr32(img, kTask + game::scr::kJumpLabels, kArena + kJump);
    if (pc >= 0 && static_cast<u32>(pc) < kInsnWords) {
        const u32 at = kInsn + static_cast<u32>(pc) * 4;
        img[at + 2] = static_cast<u8>(operand);
        img[at + 3] = static_cast<u8>(operand >> 8);
    }
    return img;
}

bool load_or_skip(Machine& m) {
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err) << " (set P3FES_ELF)");
        return false;
    }
    return true;
}

}  // namespace

TEST_CASE("game: CodeFunc_Proc (PROC) equals its recompiled body and advances the pc by one") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x9C0C0DE5u};
    const s32 pcs[] = {0, 1, 7, 511, -1, 0x7FFFFFFF, static_cast<s32>(0x80000000u)};
    int cases = 0;
    for (int i = 0; i < 200; ++i) {
        const s32 pc = i < 7 ? pcs[i] : static_cast<s32>(rng());
        const std::vector<u8> img = task_image(rng, pc, 0);
        const u64 args[4] = {sx(kArena + kTask), rng(), rng(), rng()};
        const u32 seed = rng();
        const Outcome h = run(m, &recomp_gen::fn_CodeFunc_Proc_0035cf00, img, args, seed);
        const Outcome r = run(m, &recomp_gen::fn_CodeFunc_Proc_0035cf00__recomp, img, args, seed);
        expect_same(h, r, "CodeFunc_Proc");
        CHECK(h.v0 == 1);
        CHECK(static_cast<s32>(rd32(h.arena, kTask + game::scr::kPc)) == static_cast<s32>(static_cast<u32>(pc) + 1u));
        ++cases;
    }
    MESSAGE("CodeFunc_Proc: " << cases << " cases compared");
}

TEST_CASE("game: CodeFunc_Jmp (JUMP) and CodeFunc_Goto (GOTO) equal their recompiled bodies and load the label's instruction index") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x3D1D03D3u};
    struct Variant {
        const char* name;
        void (*hand)(EEContext&);
        void (*recomp)(EEContext&);
        u32 table;
    };
    const Variant variants[] = {
        {"CodeFunc_Jmp", &recomp_gen::fn_CodeFunc_Jmp_0035d1d0, &recomp_gen::fn_CodeFunc_Jmp_0035d1d0__recomp, kProc},
        {"CodeFunc_Goto", &recomp_gen::fn_CodeFunc_Goto_0035d310, &recomp_gen::fn_CodeFunc_Goto_0035d310__recomp, kJump},
    };
    for (const Variant& v : variants) {
        int cases = 0;
        for (int i = 0; i < 300; ++i) {
            const s32 pc = static_cast<s32>(rng() % kInsnWords);
            // Labels 0..63 are in the table; a few negative operands exercise the sign-extended read
            // (the record then lies in the previous area of the arena, still inside it).
            const s16 operand = (i % 10 == 9) ? static_cast<s16>(-1 - static_cast<int>(rng() % 8)) : static_cast<s16>(rng() % kLabels);
            const std::vector<u8> img = task_image(rng, pc, operand);
            const u64 args[4] = {sx(kArena + kTask), rng(), rng(), rng()};
            const u32 seed = rng();
            const Outcome h = run(m, v.hand, img, args, seed);
            const Outcome r = run(m, v.recomp, img, args, seed);
            expect_same(h, r, v.name);
            CHECK(h.v0 == 1);
            const u32 record = v.table + static_cast<u32>(static_cast<s32>(operand)) * 32u;
            CHECK(rd32(h.arena, kTask + game::scr::kPc) == rd32(img, record + game::scr::kLabelInsn));
            ++cases;
        }
        MESSAGE(std::string(v.name) << ": " << cases << " cases compared");
    }
}

TEST_CASE("game: ApplyRelocTable (BMD relocation) equals its recompiled body on every encoding and matches the documented rule") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0xB3D5E10Cu};
    // Words at +0x0 (1024 words), relocation stream at +0x1000.
    constexpr u32 kWords = 0x000, kWordCount = 1024, kReloc = 0x1000;
    int cases = 0, fixups_total = 0;
    for (int i = 0; i < 300; ++i) {
        std::vector<u8> img(kArenaSize);
        for (u8& b : img) b = static_cast<u8>(rng());
        // Build a stream whose fix-ups stay inside the word area; remember the expected positions.
        std::vector<u8> stream;
        std::vector<u32> expected;  // word indices that must receive `add`
        u32 cursor = 0;             // the function starts at word 0 and fixes after each advance
        const int steps = static_cast<int>(rng() % 12);
        for (int s = 0; s < steps; ++s) {
            const unsigned form = rng() % 4;
            if (form == 3) {
                const u32 n = rng() % 32;  // run of n + 2 consecutive words after the cursor
                if (cursor + n + 2 >= kWordCount) break;
                stream.push_back(static_cast<u8>((n << 3) | 7));
                for (u32 k = 1; k <= n + 2; ++k) expected.push_back(cursor + k);
                cursor += n + 2;
                continue;
            }
            u32 adv;
            if (form == 0) adv = rng() % 128;                 // 1 byte: adv < 2^7
            else if (form == 1) adv = 128 + rng() % 256;      // 2 bytes: adv < 2^14 (kept small)
            else adv = 300 + rng() % 400;                     // 3 bytes: adv < 2^21 (kept small)
            if (cursor + adv >= kWordCount) break;
            if (form == 0) {
                stream.push_back(static_cast<u8>(adv << 1));
            } else if (form == 1) {
                const u32 v = (adv << 2) | 1;
                stream.push_back(static_cast<u8>(v));
                stream.push_back(static_cast<u8>(v >> 8));
            } else {
                const u32 v = (adv << 3) | 3;
                stream.push_back(static_cast<u8>(v));
                stream.push_back(static_cast<u8>(v >> 8));
                stream.push_back(static_cast<u8>(v >> 16));
            }
            cursor += adv;
            expected.push_back(cursor);
        }
        std::memcpy(img.data() + kReloc, stream.data(), stream.size());
        const u32 add = rng();
        const u64 args[4] = {sx(kArena + kWords), sx(add), sx(kArena + kReloc), sx(static_cast<u32>(stream.size()))};
        const u32 seed = rng();
        const Outcome h = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90, img, args, seed);
        const Outcome r = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90__recomp, img, args, seed);
        expect_same(h, r, "ApplyRelocTable", /*compare_v0=*/false);  // void; $v0 is untouched by both
        // Documented rule: exactly the expected words gained `add`, everything else is unchanged.
        std::vector<u8> want = img;
        for (u32 w : expected) wr32(want, kWords + w * 4, rd32(want, kWords + w * 4) + add);  // a word may be hit twice
        CHECK(h.arena == want);
        fixups_total += static_cast<int>(expected.size());
        ++cases;
    }
    // The table of DATA/HELP/DATTUTORIAL.BMD (docs/FORMATS.md section 3): bytes 07 16 relocate the
    // words at +0x24, +0x28 (run of two after word 0) and +0x54 (advance 11 words).
    {
        std::vector<u8> img(kArenaSize, 0);
        img[kReloc] = 0x07;
        img[kReloc + 1] = 0x16;
        const u64 args[4] = {sx(kArena + 0x20), sx(0x1000), sx(kArena + kReloc), sx(2)};
        const Outcome h = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90, img, args, 1);
        const Outcome r = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90__recomp, img, args, 1);
        expect_same(h, r, "ApplyRelocTable DATTUTORIAL", false);
        CHECK(rd32(h.arena, 0x24) == 0x1000);
        CHECK(rd32(h.arena, 0x28) == 0x1000);
        CHECK(rd32(h.arena, 0x54) == 0x1000);
        CHECK(rd32(h.arena, 0x20) == 0);
        CHECK(rd32(h.arena, 0x2C) == 0);
        CHECK(rd32(h.arena, 0x50) == 0);
        CHECK(rd32(h.arena, 0x58) == 0);
    }
    // An empty table does nothing (the loop test runs first).
    {
        std::vector<u8> img(kArenaSize);
        for (u8& b : img) b = static_cast<u8>(rng());
        const u64 args[4] = {sx(kArena), sx(0x12345678), sx(kArena + kReloc), sx(0)};
        const Outcome h = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90, img, args, 2);
        const Outcome r = run(m, &recomp_gen::fn_ApplyRelocTable_0035ac90__recomp, img, args, 2);
        expect_same(h, r, "ApplyRelocTable empty", false);
        CHECK(h.arena == img);
    }
    MESSAGE("ApplyRelocTable: " << cases << " random tables compared, " << fixups_total << " fix-ups");
}

// ===== the operand-stack handlers, scrOperation and the COMM accessors (script_ops.cpp) =====================

namespace {

using namespace game::scr;

// Arena layout for the stack handlers (all pointers of the task record point into it; the globals block
// at +0x1800 stands in for 0x957C00, g_scrGlobals is pointed at it by run()).
constexpr u32 kVmTask = 0x000;
constexpr u32 kVmInsn = 0x100, kVmInsnWords = 512;   // -> 0x900
constexpr u32 kVmStrings = 0x900;                    // 256 bytes
constexpr u32 kVmProc = 0xA00, kVmJump = 0xE00, kVmLabels = 32;
constexpr u32 kVmLocalInts = 0x1200, kVmLocalFloats = 0x1300, kVmLocals = 64;
constexpr u32 kVmSections = 0x1400;                  // 5 descriptors of 16 bytes
constexpr u32 kVmGlobals = 0x1800, kVmGlobalCount = 256;  // ints at +0x1800, floats at +0x1C00

using Fn = void (*)(EEContext&);
struct Handler {
    const char* name;
    Fn hand;
    Fn recomp;
};
#define P3FES_PAIR(name, sym) Handler{name, &recomp_gen::sym, &recomp_gen::sym##__recomp}

// Stack contents: a tag distribution covering every path and values that index the globals block for
// tags 2 and 3.
s8 pick_tag(std::mt19937& rng) {
    const unsigned r = rng() % 100;
    if (r < 30) return kTagInt;
    if (r < 55) return kTagFloat;
    if (r < 65) return kTagGlobalInt;
    if (r < 75) return kTagGlobalFloat;
    if (r < 83) return kTagReturnAddress;
    if (r < 90) return kTagString;
    s8 t = static_cast<s8>(rng());
    return (t >= 0 && t <= 5) ? static_cast<s8>(t + 6) : t;
}
u32 pick_value(std::mt19937& rng) {
    static const u32 kFloats[] = {0x00000000u, 0x80000000u, 0x3F800000u, 0xBF800000u, 0x40200000u, 0x00000001u,
                                  0x7F7FFFFFu, 0xFF7FFFFFu, 0x4B000000u, 0x4F000000u, 0xCF000000u, 0x7F800000u};
    const unsigned r = rng() % 100;
    if (r < 45) return rng();
    if (r < 70) return static_cast<u32>(static_cast<s32>(rng() % 201) - 100);
    if (r < 90) return kFloats[rng() % (sizeof(kFloats) / sizeof(kFloats[0]))];
    return 0;
}
u32 value_for(std::mt19937& rng, s8 tag) {
    return (tag == kTagGlobalInt || tag == kTagGlobalFloat) ? rng() % kVmGlobalCount : pick_value(rng);
}
// sp: mostly a usable count (1..26), one time in five anywhere in [lo, hi] -- empty, full, past the end
// or negative; every check is a no-op. Each family sets the range the pair can still compare: a push at
// slot -1 lands its tag byte in the top byte of `sp` (+0x1F) and the recompiled value store then goes
// through an address outside RAM, which the rt adapter reports as fatal while guest::store drops it;
// likewise slot 28's "value" is the `image` word, so a pop there with tag 2/3 dereferences garbage.
s32 pick_sp(std::mt19937& rng, s32 lo, s32 hi) {
    if (rng() % 5 != 0) {
        const s32 a = std::max(lo, 1), b = std::min(hi, 26);
        return a + static_cast<s32>(rng() % static_cast<u32>(b - a + 1));
    }
    return lo + static_cast<s32>(rng() % static_cast<u32>(hi - lo + 1));
}

struct VmImage {
    std::vector<u8> bytes;
    s32 pc, sp;
    s16 operand;
};

VmImage vm_image(std::mt19937& rng, s32 sp, s16 operand) {
    VmImage v;
    v.bytes.assign(kArenaSize, 0);
    for (u8& b : v.bytes) b = static_cast<u8>(rng());
    v.pc = static_cast<s32>(rng() % (kVmInsnWords - 1));  // PUSHI/PUSHF read the next word too
    v.sp = sp;
    v.operand = operand;
    std::vector<u8>& img = v.bytes;
    wr32(img, kVmTask + kPc, static_cast<u32>(v.pc));
    wr32(img, kVmTask + game::scr::kSp, static_cast<u32>(v.sp));    // qualified: the file's kSp is the guest $sp
    wr32(img, kVmTask + game::scr::kInsn, kArena + kVmInsn);  // and its kInsn the arena offset above
    wr32(img, kVmTask + kStrings, kArena + kVmStrings);
    wr32(img, kVmTask + kProcLabels, kArena + kVmProc);
    wr32(img, kVmTask + kJumpLabels, kArena + kVmJump);
    wr32(img, kVmTask + kLocalInts, kArena + kVmLocalInts);
    wr32(img, kVmTask + kLocalFloats, kArena + kVmLocalFloats);
    wr32(img, kVmTask + kSections, kArena + kVmSections);
    wr32(img, kVmSections + 16 + kSectionCount, rng() % (kVmLabels + 1));  // section 1's element count
    const u32 at = kVmInsn + static_cast<u32>(v.pc) * 4;
    img[at + 2] = static_cast<u8>(operand);
    img[at + 3] = static_cast<u8>(operand >> 8);
    for (u32 i = 0; i < 28; ++i) {
        const s8 tag = pick_tag(rng);
        img[kVmTask + kTags + i] = static_cast<u8>(tag);
        wr32(img, kVmTask + kValues + i * 4, value_for(rng, tag));
    }
    // The globals block holds the same value mix.
    for (u32 i = 0; i < 2 * kVmGlobalCount; ++i) wr32(img, kVmGlobals + i * 4, pick_value(rng));
    for (u32 i = 0; i < kVmLocals; ++i) {
        wr32(img, kVmLocalInts + i * 4, pick_value(rng));
        wr32(img, kVmLocalFloats + i * 4, pick_value(rng));
    }
    return v;
}

// Host restatement of the slot conversions (18_script_vm.md section 2.3; the globals through the image).
s32 slot_as_int(const std::vector<u8>& img, s32 slot) {
    const s8 tag = rds8(img, kVmTask + kTags + static_cast<u32>(slot));
    const u32 value = rd32(img, kVmTask + kValues + static_cast<u32>(slot) * 4);
    switch (tag) {
    case kTagInt:
    case kTagReturnAddress: return static_cast<s32>(value);
    case kTagFloat: return static_cast<s32>(ee::fpu::cvt_w_s(value));
    case kTagGlobalInt: return static_cast<s32>(rd32(img, kVmGlobals + value * 4));
    case kTagGlobalFloat: return static_cast<s32>(ee::fpu::cvt_w_s(rd32(img, kVmGlobals + kGlobalFloats + value * 4)));
    default: return 0;
    }
}
u32 slot_as_float(const std::vector<u8>& img, s32 slot, bool return_address_as_int) {
    const s8 tag = rds8(img, kVmTask + kTags + static_cast<u32>(slot));
    const u32 value = rd32(img, kVmTask + kValues + static_cast<u32>(slot) * 4);
    switch (tag) {
    case kTagInt: return ee::fpu::cvt_s_w(value);
    case kTagFloat: return value;
    case kTagGlobalInt: return ee::fpu::cvt_s_w(rd32(img, kVmGlobals + value * 4));
    case kTagGlobalFloat: return rd32(img, kVmGlobals + kGlobalFloats + value * 4);
    case kTagReturnAddress: return return_address_as_int ? ee::fpu::cvt_s_w(value) : 0u;
    default: return 0;
    }
}
bool is_int_tag(s8 tag) { return tag == kTagInt || tag == kTagGlobalInt; }
bool is_float_tag(s8 tag) { return tag == kTagFloat || tag == kTagGlobalFloat; }
s8 tag_at(const std::vector<u8>& img, s32 slot) { return rds8(img, kVmTask + kTags + static_cast<u32>(slot)); }
u32 value_at(const std::vector<u8>& img, s32 slot) { return rd32(img, kVmTask + kValues + static_cast<u32>(slot) * 4); }
s32 pc_of(const std::vector<u8>& img) { return static_cast<s32>(rd32(img, kVmTask + kPc)); }
s32 sp_of(const std::vector<u8>& img) { return static_cast<s32>(rd32(img, kVmTask + game::scr::kSp)); }
// A pop stores sp - 1 before it reads the slot's tag, so for sp <= 0 (slots -1..-4 overlap the bytes of
// `sp` itself) the tag it sees is a byte of the decremented count: the rule is stated on this image.
std::vector<u8> after_pop(const std::vector<u8>& img, s32 sp) {
    std::vector<u8> popped = img;
    wr32(popped, kVmTask + game::scr::kSp, static_cast<u32>(sp - 1));
    return popped;
}
u32 insn_word(const std::vector<u8>& img, s32 pc) { return rd32(img, kVmInsn + static_cast<u32>(pc) * 4); }
u32 label_insn_of(const std::vector<u8>& img, u32 table, s32 index) {
    return rd32(img, table + static_cast<u32>(index) * 32 + kLabelInsn);
}

struct PairResult {
    Outcome hand, recomp;
};
PairResult run_pair(Machine& m, const Handler& h, const VmImage& v, std::mt19937& rng, u64 a0 = sx(kArena + kVmTask), u64 a1 = 0) {
    const u64 args[4] = {a0, a1, rng(), rng()};
    const u32 seed = rng();
    PairResult p;
    p.hand = run(m, h.hand, v.bytes, args, seed);
    p.recomp = run(m, h.recomp, v.bytes, args, seed);
    expect_same(p.hand, p.recomp, h.name);
    return p;
}

}  // namespace

TEST_CASE("game: the PUSH handlers and CALL equal their recompiled bodies and push the documented tag and value") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x5075C4EDu};
    enum Kind { kPushI, kPushS, kPushF, kPushIX, kPushIF, kPushLIX, kPushLFX, kPushSTR, kPushREG, kCall };
    struct Case {
        Handler h;
        Kind kind;
    };
    const Case cases[] = {
        {P3FES_PAIR("CodeFunc_PushI", fn_CodeFunc_PushI_0035c300), kPushI},
        {P3FES_PAIR("CodeFunc_PushS", fn_CodeFunc_PushS_0035c3b0), kPushS},
        {P3FES_PAIR("CodeFunc_PushF", fn_CodeFunc_PushF_0035c450), kPushF},
        {P3FES_PAIR("CodeFunc_PushIX", fn_CodeFunc_PushIX_0035c500), kPushIX},
        {P3FES_PAIR("CodeFunc_PushIF", fn_CodeFunc_PushIF_0035c5b0), kPushIF},
        {P3FES_PAIR("CodeFunc_PushLIX", fn_CodeFunc_PushLIX_0035c660), kPushLIX},
        {P3FES_PAIR("CodeFunc_PushLFX", fn_CodeFunc_PushLFX_0035c710), kPushLFX},
        {P3FES_PAIR("CodeFunc_PushSTR", fn_CodeFunc_PushSTR_0035c7c0), kPushSTR},
        {P3FES_PAIR("CodeFunc_PushREG", fn_CodeFunc_PushREG_0035c870), kPushREG},
        {P3FES_PAIR("CodeFunc_Call", fn_CodeFunc_Call_0035d210), kCall},
    };
    int total = 0, overflow = 0;
    for (const Case& c : cases) {
        for (int i = 0; i < 300; ++i) {
            const s32 sp = pick_sp(rng, 0, 29);
            s16 operand;
            switch (c.kind) {
            case kPushIX: case kPushIF: operand = static_cast<s16>(static_cast<int>(rng() % (kVmGlobalCount + 8)) - 8); break;
            case kPushLIX: case kPushLFX: operand = static_cast<s16>(static_cast<int>(rng() % (kVmLocals + 8)) - 8); break;
            case kPushSTR: operand = static_cast<s16>(rng() % 256); break;
            case kCall: operand = static_cast<s16>(static_cast<int>(rng() % (kVmLabels + 4)) - 4); break;
            default: operand = static_cast<s16>(rng()); break;
            }
            const VmImage v = vm_image(rng, sp, operand);
            const std::vector<u8>& img = v.bytes;
            const PairResult p = run_pair(m, c.h, v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            // Rule: tag and value at slot sp, sp + 1, pc advanced (by two for the opcodes with an operand word).
            s8 want_tag = kTagInt;
            u32 want_value = 0;
            s32 want_pc = v.pc + 1;
            switch (c.kind) {
            case kPushI: want_value = insn_word(img, v.pc + 1); want_pc = v.pc + 2; break;
            case kPushS: want_value = static_cast<u32>(static_cast<s32>(operand)); break;
            case kPushF: want_tag = kTagFloat; want_value = insn_word(img, v.pc + 1); want_pc = v.pc + 2; break;
            case kPushIX: want_value = rd32(img, kVmGlobals + static_cast<u32>(static_cast<s32>(operand)) * 4); break;
            case kPushIF: want_tag = kTagFloat; want_value = rd32(img, kVmGlobals + kGlobalFloats + static_cast<u32>(static_cast<s32>(operand)) * 4); break;
            case kPushLIX: want_value = rd32(img, kVmLocalInts + static_cast<u32>(static_cast<s32>(operand)) * 4); break;
            case kPushLFX: want_tag = kTagFloat; want_value = rd32(img, kVmLocalFloats + static_cast<u32>(static_cast<s32>(operand)) * 4); break;
            case kPushSTR: want_tag = kTagString; want_value = kArena + kVmStrings + static_cast<u32>(static_cast<s32>(operand)); break;
            case kPushREG: want_tag = tag_at(img, kReturnSlot); want_value = value_at(img, kReturnSlot); break;
            case kCall:
                want_tag = kTagReturnAddress;
                want_value = static_cast<u32>(v.pc);
                want_pc = static_cast<s32>(label_insn_of(img, kVmProc, operand));
                break;
            }
            CHECK(tag_at(out, sp) == want_tag);
            CHECK(value_at(out, sp) == want_value);
            CHECK(sp_of(out) == sp + 1);
            CHECK(pc_of(out) == want_pc);
            if (sp >= kStackSlots) ++overflow;
            ++total;
        }
    }
    MESSAGE("PUSH/CALL: " << total << " cases compared (" << overflow << " with sp >= 27, the no-op assertion)");
}

TEST_CASE("game: the POP handlers equal their recompiled bodies and convert by tag") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x90901E55u};
    enum Kind { kPopIX, kPopFX, kPopLIX, kPopLFX };
    struct Case {
        Handler h;
        Kind kind;
    };
    const Case cases[] = {
        {P3FES_PAIR("CodeFunc_PopIX", fn_CodeFunc_PopIX_0035c900), kPopIX},
        {P3FES_PAIR("CodeFunc_PopFX", fn_CodeFunc_PopFX_0035ca70), kPopFX},
        {P3FES_PAIR("CodeFunc_PopLIX", fn_CodeFunc_PopLIX_0035cc00), kPopLIX},
        {P3FES_PAIR("CodeFunc_PopLFX", fn_CodeFunc_PopLFX_0035cd70), kPopLFX},
    };
    int total = 0, by_tag[8] = {};
    for (const Case& c : cases) {
        for (int i = 0; i < 400; ++i) {
            const s32 sp = pick_sp(rng, -2, 28);
            const bool local = c.kind == kPopLIX || c.kind == kPopLFX;
            const s16 operand = static_cast<s16>(static_cast<int>(rng() % ((local ? kVmLocals : kVmGlobalCount) + 8)) - 8);
            const VmImage v = vm_image(rng, sp, operand);
            const std::vector<u8>& img = v.bytes;
            const PairResult p = run_pair(m, c.h, v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            const s32 top = sp - 1;
            const s8 tag = tag_at(img, top);
            const std::vector<u8> popped = after_pop(img, sp);
            u32 dest;
            u32 want;
            switch (c.kind) {
            case kPopIX: dest = kVmGlobals; want = static_cast<u32>(slot_as_int(popped, top)); break;
            case kPopFX: dest = kVmGlobals + kGlobalFloats; want = slot_as_float(popped, top, false); break;
            case kPopLIX: dest = kVmLocalInts; want = static_cast<u32>(slot_as_int(popped, top)); break;
            default: dest = kVmLocalFloats; want = slot_as_float(popped, top, false); break;
            }
            dest += static_cast<u32>(static_cast<s32>(operand)) * 4;
            // A tag-2/3 slot whose index is the destination itself reads before it writes: the rule holds on the input image.
            CHECK(rd32(out, dest) == want);
            CHECK(sp_of(out) == top);
            CHECK(pc_of(out) == v.pc + 1);
            ++by_tag[(tag >= 0 && tag <= 5) ? tag : 6 + (tag < 0)];
            ++total;
        }
    }
    MESSAGE("POP: " << total << " cases compared; top tags int " << by_tag[0] << " float " << by_tag[1] << " gint " << by_tag[2]
                    << " gfloat " << by_tag[3] << " ret " << by_tag[4] << " str " << by_tag[5] << " other " << by_tag[6] + by_tag[7]);
}

TEST_CASE("game: CodeFunc_End equals its recompiled body: an empty stack ends the script, otherwise the pc returns past the CALL") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0xE4DE4DE4u};
    const Handler h = P3FES_PAIR("CodeFunc_End", fn_CodeFunc_End_0035d040);
    int total = 0, ended = 0, returned = 0;
    for (int i = 0; i < 500; ++i) {
        const s32 sp = (i % 10 == 0) ? 0 : pick_sp(rng, -2, 28);  // one in ten: the empty call stack
        VmImage v = vm_image(rng, sp, static_cast<s16>(rng()));
        // Most call stacks hold a return address on top; the rest exercise the (no-op) assertion.
        if (sp > 0 && rng() % 4 != 0) v.bytes[kVmTask + kTags + static_cast<u32>(sp - 1)] = static_cast<u8>(kTagReturnAddress);
        const std::vector<u8>& img = v.bytes;
        const PairResult p = run_pair(m, h, v, rng);
        const std::vector<u8>& out = p.hand.arena;
        if (sp == 0) {
            CHECK(p.hand.v0 == 0);
            CHECK(out == img);
            ++ended;
        } else {
            CHECK(p.hand.v0 == 1);
            CHECK(sp_of(out) == sp - 1);
            CHECK(pc_of(out) == static_cast<s32>(static_cast<u32>(slot_as_int(after_pop(img, sp), sp - 1)) + 1u));
            ++returned;
        }
        ++total;
    }
    MESSAGE("CodeFunc_End: " << total << " cases compared (" << ended << " ended, " << returned << " returned)");
}

TEST_CASE("game: CodeFunc_Minus, CodeFunc_Not and CodeFunc_IF equal their recompiled bodies and follow the tag rules") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x14F11F14u};
    const Handler minus = P3FES_PAIR("CodeFunc_Minus", fn_CodeFunc_Minus_0035e0e0);
    const Handler nott = P3FES_PAIR("CodeFunc_Not", fn_CodeFunc_Not_0035e250);
    const Handler iff = P3FES_PAIR("CodeFunc_IF", fn_CodeFunc_IF_0035e850);
    int n_minus = 0, n_not = 0, n_if = 0, if_taken = 0;
    for (int i = 0; i < 500; ++i) {
        const s32 sp = pick_sp(rng, -2, 28);
        const s32 top = sp - 1;
        const s16 operand = static_cast<s16>(static_cast<int>(rng() % (kVmLabels + 4)) - 4);
        const VmImage v = vm_image(rng, sp, operand);
        const std::vector<u8>& img = v.bytes;
        const s8 tag = tag_at(img, top);
        const u32 value = value_at(img, top);
        {
            const PairResult p = run_pair(m, minus, v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            CHECK(sp_of(out) == sp);
            CHECK(pc_of(out) == v.pc + 1);
            std::vector<u8> want = img;
            wr32(want, kVmTask + kPc, static_cast<u32>(v.pc + 1));
            switch (tag) {
            case kTagInt: wr32(want, kVmTask + kValues + static_cast<u32>(top) * 4, 0u - value); break;
            case kTagFloat: wr32(want, kVmTask + kValues + static_cast<u32>(top) * 4, value ^ ee::fpu::kSign); break;
            case kTagGlobalInt: wr32(want, kVmGlobals + value * 4, 0u - rd32(img, kVmGlobals + value * 4)); break;
            case kTagGlobalFloat:
                wr32(want, kVmGlobals + kGlobalFloats + value * 4, rd32(img, kVmGlobals + kGlobalFloats + value * 4) ^ ee::fpu::kSign);
                break;
            default: break;  // a return address or an unknown tag: K_Abort (no-op), nothing changes
            }
            CHECK(out == want);
            ++n_minus;
        }
        if (sp >= 1) {  // a NOT at sp <= 0 pushes at slot -1 (see pick_sp)
            const PairResult p = run_pair(m, nott, v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            CHECK(pc_of(out) == v.pc + 1);
            if (is_int_tag(tag) || is_float_tag(tag)) {
                const std::vector<u8> popped = after_pop(img, sp);
                const u32 want = is_int_tag(tag) ? (slot_as_int(popped, top) == 0 ? 1u : 0u)
                                                 : (ee::fpu::key(slot_as_float(popped, top, false)) == 0 ? 1u : 0u);
                CHECK(sp_of(out) == sp);  // popped and pushed
                CHECK(tag_at(out, top) == kTagInt);
                CHECK(value_at(out, top) == want);
            } else {
                CHECK(sp_of(out) == sp);  // nothing popped
                CHECK(tag_at(out, top) == tag);
                CHECK(value_at(out, top) == value);
            }
            ++n_not;
        }
        {
            const PairResult p = run_pair(m, iff, v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            bool taken = false;
            if (is_int_tag(tag)) taken = slot_as_int(after_pop(img, sp), top) != 0;
            else if (is_float_tag(tag)) taken = ee::fpu::key(slot_as_float(after_pop(img, sp), top, false)) != 0;
            CHECK(sp_of(out) == ((is_int_tag(tag) || is_float_tag(tag)) ? top : sp));
            CHECK(pc_of(out) == (taken ? v.pc + 1 : static_cast<s32>(label_insn_of(img, kVmJump, operand))));
            if (taken) ++if_taken;
            ++n_if;
        }
    }
    MESSAGE("CodeFunc_Minus " << n_minus << ", CodeFunc_Not " << n_not << ", CodeFunc_IF " << n_if << " (" << if_taken << " taken) cases compared");
}

namespace {

// Host restatement of scrOperation (18_script_vm.md section 2.3 and the generated body): the top slot is
// the left operand; integers when both tags are 0/2, floats otherwise (ints promoted with cvt.s.w,
// other tags 0.0); integer MUL is the low product word, integer DIV follows the EE's div (LO = lhs < 0 ?
// 1 : -1 on a zero divisor, INT_MIN / -1 = INT_MIN); float DIV is div.s; comparisons push an int.
struct OpResult {
    s8 tag;
    u32 value;
};
OpResult expect_operation(const std::vector<u8>& img, s32 sp, u32 op) {
    const s8 lt = tag_at(img, sp - 1), rt = tag_at(img, sp - 2);
    if (is_int_tag(lt) && is_int_tag(rt)) {
        const s32 a = slot_as_int(img, sp - 1), b = slot_as_int(img, sp - 2);
        const u32 ua = static_cast<u32>(a), ub = static_cast<u32>(b);
        u32 r = 0;
        switch (op) {
        case kOpAdd: r = ua + ub; break;
        case kOpSub: r = ua - ub; break;
        case kOpMul: r = static_cast<u32>(static_cast<s64>(a) * static_cast<s64>(b)); break;
        case kOpDiv:
            if (b == 0) r = static_cast<u32>(a < 0 ? 1 : -1);
            else if (a == INT32_MIN && b == -1) r = 0x80000000u;
            else r = static_cast<u32>(a / b);
            break;
        case kOpOr: r = (a != 0 || b != 0) ? 1 : 0; break;
        case kOpAnd: r = (a != 0 && b != 0) ? 1 : 0; break;
        case kOpEq: r = a == b; break;
        case kOpNeq: r = a != b; break;
        case kOpLess: r = a < b; break;
        case kOpGreater: r = a > b; break;
        case kOpLessEqual: r = a <= b; break;
        case kOpGreaterEqual: r = a >= b; break;
        }
        return {kTagInt, r};
    }
    const u32 fa = slot_as_float(img, sp - 1, false), fb = slot_as_float(img, sp - 2, false);
    const s32 ka = ee::fpu::key(fa), kb = ee::fpu::key(fb);
    switch (op) {
    case kOpAdd: return {kTagFloat, ee::fpu::add(fa, fb)};
    case kOpSub: return {kTagFloat, ee::fpu::sub(fa, fb)};
    case kOpMul: return {kTagFloat, ee::fpu::mul(fa, fb)};
    case kOpDiv: return {kTagFloat, ee::fpu::div_nearest(fa, fb).value};
    case kOpOr: return {kTagInt, (ka != 0 || kb != 0) ? 1u : 0u};
    case kOpAnd: return {kTagInt, (ka != 0 && kb != 0) ? 1u : 0u};
    case kOpEq: return {kTagInt, ka == kb ? 1u : 0u};
    case kOpNeq: return {kTagInt, ka != kb ? 1u : 0u};
    case kOpLess: return {kTagInt, ka < kb ? 1u : 0u};
    case kOpGreater: return {kTagInt, ka > kb ? 1u : 0u};
    case kOpLessEqual: return {kTagInt, ka <= kb ? 1u : 0u};
    default: return {kTagInt, ka >= kb ? 1u : 0u};
    }
}

// Operand pairs that make the interesting paths likely: equal values, zeros, the overflow corner.
void shape_operands(std::mt19937& rng, VmImage& v) {
    if (v.sp < 2) return;
    const u32 l = kVmTask + kValues + static_cast<u32>(v.sp - 1) * 4, r = l - 4;
    const unsigned pick = rng() % 10;
    if (pick == 0) wr32(v.bytes, r, rd32(v.bytes, l));                      // equal operands
    else if (pick == 1) wr32(v.bytes, r, 0);                                 // zero divisor / right operand
    else if (pick == 2) wr32(v.bytes, r, 0x80000000u);                       // -0.0 or INT_MIN
    else if (pick == 3) {                                                    // INT_MIN / -1
        wr32(v.bytes, l, 0x80000000u);
        wr32(v.bytes, r, 0xFFFFFFFFu);
    }
    if (pick <= 3) {  // keep the shaped values meaningful: direct int/float tags on both slots
        v.bytes[kVmTask + kTags + static_cast<u32>(v.sp - 1)] = static_cast<u8>(rng() % 2 ? kTagInt : kTagFloat);
        v.bytes[kVmTask + kTags + static_cast<u32>(v.sp - 2)] = static_cast<u8>(rng() % 2 ? kTagInt : kTagFloat);
    }
}

}  // namespace

TEST_CASE("game: the twelve arithmetic/comparison opcodes (scrOperation) equal their recompiled bodies and follow the int/float rules") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0xA12173E7u};
    const Handler ops[12] = {
        P3FES_PAIR("CodeFunc_Add", fn_CodeFunc_Add_0035dfe0), P3FES_PAIR("CodeFunc_Sub", fn_CodeFunc_Sub_0035e020),
        P3FES_PAIR("CodeFunc_Mul", fn_CodeFunc_Mul_0035e060), P3FES_PAIR("CodeFunc_Div", fn_CodeFunc_Div_0035e0a0),
        P3FES_PAIR("CodeFunc_Or", fn_CodeFunc_Or_0035e650),   P3FES_PAIR("CodeFunc_And", fn_CodeFunc_And_0035e690),
        P3FES_PAIR("CodeFunc_Eq", fn_CodeFunc_Eq_0035e6d0),   P3FES_PAIR("CodeFunc_Neq", fn_CodeFunc_Neq_0035e710),
        P3FES_PAIR("CodeFunc_S", fn_CodeFunc_S_0035e750),     P3FES_PAIR("CodeFunc_L", fn_CodeFunc_L_0035e790),
        P3FES_PAIR("CodeFunc_SE", fn_CodeFunc_SE_0035e7d0),   P3FES_PAIR("CodeFunc_LE", fn_CodeFunc_LE_0035e810),
    };
    int total = 0, ints = 0, floats = 0, zero_div = 0;
    for (u32 op = 0; op < 12; ++op) {
        for (int i = 0; i < 400; ++i) {
            // sp >= 2 only: with sp <= 1 the second pop reads slot -1 and the push then writes the top byte
            // of sp (see pick_sp), so the `sp < 2` assertion path cannot be compared.
            const s32 sp = pick_sp(rng, 2, 28);
            VmImage v = vm_image(rng, sp, static_cast<s16>(rng()));
            shape_operands(rng, v);
            const std::vector<u8>& img = v.bytes;
            const PairResult p = run_pair(m, ops[op], v, rng);
            const std::vector<u8>& out = p.hand.arena;
            CHECK(p.hand.v0 == 1);
            CHECK(sp_of(out) == sp - 1);
            CHECK(pc_of(out) == v.pc + 1);
            const OpResult want = expect_operation(img, sp, op);
            CHECK(tag_at(out, sp - 2) == want.tag);
            CHECK(value_at(out, sp - 2) == want.value);
            // scrOperation itself on the same image (the __recomp wrappers above call the hand-written
            // scrOperation -- every generated call site uses the plain symbol -- so its body is compared
            // here): `op` in $a1, the pc untouched, $v0 left alone by both.
            {
                const Handler direct = P3FES_PAIR("scrOperation", fn_scrOperation_0035d350);
                const u64 args[4] = {sx(kArena + kVmTask), sx(op), rng(), rng()};
                const u32 seed = rng();
                const Outcome dh = run(m, direct.hand, img, args, seed);
                const Outcome dr = run(m, direct.recomp, img, args, seed);
                expect_same(dh, dr, "scrOperation");
                CHECK(sp_of(dh.arena) == sp - 1);
                CHECK(pc_of(dh.arena) == v.pc);
                CHECK(tag_at(dh.arena, sp - 2) == want.tag);
                CHECK(value_at(dh.arena, sp - 2) == want.value);
            }
            const bool integer = is_int_tag(tag_at(img, sp - 1)) && is_int_tag(tag_at(img, sp - 2));
            integer ? ++ints : ++floats;
            if (op == kOpDiv && (integer ? slot_as_int(img, sp - 2) == 0 : ee::fpu::key(slot_as_float(img, sp - 2, false)) == 0)) ++zero_div;
            ++total;
        }
    }
    // Documented examples: 7 + 5 = 12 as ints; 7 - 5.0 promotes to 2.0f; 1 / 0 (int) = -1 and -1 / 0 = 1;
    // 1.0f / 0.0f saturates to the largest EE float; 3 < 4.0f is int 1.
    struct Example {
        u32 op;
        s8 lt;
        u32 lv;
        s8 rt;
        u32 rv;
        s8 want_tag;
        u32 want_value;
    };
    const Example examples[] = {
        {kOpAdd, kTagInt, 7, kTagInt, 5, kTagInt, 12},
        {kOpSub, kTagInt, 7, kTagFloat, 0x40A00000u, kTagFloat, 0x40000000u},
        {kOpDiv, kTagInt, 1, kTagInt, 0, kTagInt, 0xFFFFFFFFu},
        {kOpDiv, kTagInt, static_cast<u32>(-1), kTagInt, 0, kTagInt, 1},
        {kOpDiv, kTagFloat, 0x3F800000u, kTagFloat, 0, kTagFloat, 0x7FFFFFFFu},
        {kOpLess, kTagInt, 3, kTagFloat, 0x40800000u, kTagInt, 1},
        {kOpMul, kTagInt, 0x10000u, kTagInt, 0x10000u, kTagInt, 0},
    };
    for (const Example& e : examples) {
        VmImage v = vm_image(rng, 5, 0);
        v.bytes[kVmTask + kTags + 4] = static_cast<u8>(e.lt);
        wr32(v.bytes, kVmTask + kValues + 16, e.lv);
        v.bytes[kVmTask + kTags + 3] = static_cast<u8>(e.rt);
        wr32(v.bytes, kVmTask + kValues + 12, e.rv);
        const PairResult p = run_pair(m, ops[e.op], v, rng);
        CHECK(tag_at(p.hand.arena, 3) == e.want_tag);
        CHECK(value_at(p.hand.arena, 3) == e.want_value);
        CHECK(sp_of(p.hand.arena) == 4);
    }
    // scrOperation itself with an operation number outside 0..11: nothing is computed and the stale
    // scratch word (seeded by run()) is pushed -- tag 0 from the int path, tag 1 from the float path.
    {
        const Handler direct = P3FES_PAIR("scrOperation", fn_scrOperation_0035d350);
        int stale = 0;
        for (int i = 0; i < 100; ++i) {
            const s32 sp = 2 + static_cast<s32>(rng() % 24);
            const VmImage v = vm_image(rng, sp, 0);
            const u32 op = 12 + rng() % 0x100;
            const u64 args[4] = {sx(kArena + kVmTask), sx(op), rng(), rng()};
            const u32 seed = rng();
            const Outcome h = run(m, direct.hand, v.bytes, args, seed);
            const Outcome r = run(m, direct.recomp, v.bytes, args, seed);
            expect_same(h, r, "scrOperation op >= 12");
            const bool integer = is_int_tag(tag_at(v.bytes, sp - 1)) && is_int_tag(tag_at(v.bytes, sp - 2));
            CHECK(tag_at(h.arena, sp - 2) == (integer ? kTagInt : kTagFloat));
            CHECK(value_at(h.arena, sp - 2) == bss_pattern(seed, (integer ? kOpResultInt : kOpResultFloat) - kVmBss));
            CHECK(sp_of(h.arena) == sp - 1);
            ++stale;
        }
        MESSAGE("scrOperation: " << stale << " out-of-range operations compared");
    }
    MESSAGE("ADD..LE: " << total << " cases compared (" << ints << " integer, " << floats << " float, " << zero_div << " zero divisors)");
}

TEST_CASE("game: the COMM-side accessors equal their recompiled bodies on g_scrCurrentTask") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0xC0333A5Cu};
    int total = 0;
    // scrSetIntReturnVal / scrSetFloatReturnVal write slot 27; scrSetPC the pc; the getters read fields.
    {
        const Handler set_int = P3FES_PAIR("scrSetIntReturnVal", fn_scrSetIntReturnVal_0035f060);
        const Handler set_float = P3FES_PAIR("scrSetFloatReturnVal", fn_scrSetFloatReturnVal_0035f080);
        const Handler set_pc = P3FES_PAIR("scrSetPC", fn_scrSetPC_0035f120);
        for (int i = 0; i < 200; ++i) {
            const VmImage v = vm_image(rng, pick_sp(rng, -2, 28), 0);
            const u32 value = pick_value(rng);
            {
                const PairResult p = run_pair(m, set_int, v, rng, sx(value));
                CHECK(tag_at(p.hand.arena, kReturnSlot) == kTagInt);
                CHECK(value_at(p.hand.arena, kReturnSlot) == value);
            }
            {
                // The argument travels in $f12 (fresh_context seeds every FPR; run() records the input value).
                const PairResult p = run_pair(m, set_float, v, rng, rng());
                CHECK(tag_at(p.hand.arena, kReturnSlot) == kTagFloat);
                CHECK(value_at(p.hand.arena, kReturnSlot) == p.hand.f12_in);
            }
            {
                const PairResult p = run_pair(m, set_pc, v, rng, sx(value));
                CHECK(pc_of(p.hand.arena) == static_cast<s32>(value));
            }
            total += 3;
        }
    }
    {
        struct Getter {
            Handler h;
            u32 field;  // 0: the task address itself
        };
        const Getter getters[] = {
            {P3FES_PAIR("scrGetCmdTimer", fn_scrGetCmdTimer_0035f130), kCmdTimer},
            {P3FES_PAIR("scrGetMessageID", fn_scrGetMessageID_0035f140), kMessageId},
            {P3FES_PAIR("scrGetCurrent", fn_scrGetCurrent_0035f150), 0},
            {P3FES_PAIR("scrGetUserData", fn_scrGetUserData_0035f160), kUserData},
        };
        for (const Getter& g : getters) {
            for (int i = 0; i < 100; ++i) {
                const VmImage v = vm_image(rng, pick_sp(rng, -2, 28), 0);
                const PairResult p = run_pair(m, g.h, v, rng, rng());
                const u32 want = g.field ? rd32(v.bytes, kVmTask + g.field) : kArena + kVmTask;
                CHECK(p.hand.v0 == sx(want));
                CHECK(p.hand.arena == v.bytes);
                ++total;
            }
        }
    }
    // scrGetLabelAddr: jump_labels[index].insn; the range assertions are no-ops, so out-of-range indices
    // (negative, >= section 1's count) still read the record.
    {
        const Handler h = P3FES_PAIR("scrGetLabelAddr", fn_scrGetLabelAddr_0035f0a0);
        int in_range = 0;
        for (int i = 0; i < 300; ++i) {
            const VmImage v = vm_image(rng, pick_sp(rng, -2, 28), 0);
            const s32 index = static_cast<s32>(rng() % (kVmLabels + 6)) - 3;
            const PairResult p = run_pair(m, h, v, rng, sx(static_cast<u32>(index)));
            CHECK(p.hand.v0 == sx(label_insn_of(v.bytes, kVmJump, index)));
            CHECK(p.hand.arena == v.bytes);
            if (index >= 0 && index < static_cast<s32>(rd32(v.bytes, kVmSections + 16 + kSectionCount))) ++in_range;
            ++total;
        }
        MESSAGE("scrGetLabelAddr: " << in_range << " of 300 indices inside section 1's count");
    }
    MESSAGE("accessors: " << total << " cases compared");
}

TEST_CASE("game: scrGetIntPara / scrGetFloatPara / scrGetStrPara equal their recompiled bodies and read argument i by tag") {
    Machine m;
    if (!load_or_skip(m)) return;
    std::mt19937 rng{0x6E79A4A5u};
    const Handler get_int = P3FES_PAIR("scrGetIntPara", fn_scrGetIntPara_0035ed20);
    const Handler get_float = P3FES_PAIR("scrGetFloatPara", fn_scrGetFloatPara_0035ee60);
    const Handler get_str = P3FES_PAIR("scrGetStrPara", fn_scrGetStrPara_0035efa0);
    int total = 0, beyond = 0, strings = 0;
    for (int i = 0; i < 500; ++i) {
        const s32 sp = pick_sp(rng, -2, 28);
        const s32 arg = static_cast<s32>(rng() % 10) - 1;  // -1 and i >= sp exercise the no-op assertion
        const VmImage v = vm_image(rng, sp, 0);
        const std::vector<u8>& img = v.bytes;
        const s32 slot = sp - 1 - arg;
        // Slots -3..-1 read the bytes of `sp` as their tag (0 or 0xFF: no dereference); slot 28's value is
        // the `image` word (see pick_sp), so the comparable slots are -3..27.
        if (slot < -3 || slot > 27) continue;
        {
            const PairResult p = run_pair(m, get_int, v, rng, sx(static_cast<u32>(arg)));
            CHECK(p.hand.v0 == sx(static_cast<u32>(slot_as_int(img, slot))));
            CHECK(p.hand.arena == img);
        }
        {
            // Returns in $f0; the recompiled body leaves a slot address (or the last tag constant) in the
            // dead $v0, which the shim does not reproduce, so $v0 is left out of this comparison.
            const u64 args[4] = {sx(static_cast<u32>(arg)), rng(), rng(), rng()};
            const u32 seed = rng();
            const Outcome h = run(m, get_float.hand, img, args, seed);
            const Outcome r = run(m, get_float.recomp, img, args, seed);
            expect_same(h, r, get_float.name, /*compare_v0=*/false);
            CHECK(h.f0 == r.f0);
            CHECK(h.f0 == slot_as_float(img, slot, /*return_address_as_int=*/true));
            CHECK(h.arena == img);
        }
        {
            const PairResult p = run_pair(m, get_str, v, rng, sx(static_cast<u32>(arg)));
            const bool is_string = tag_at(img, slot) == kTagString;
            CHECK(p.hand.v0 == sx(is_string ? value_at(img, slot) : 0u));
            CHECK(p.hand.arena == img);
            if (is_string) ++strings;
        }
        if (arg < 0 || arg >= sp) ++beyond;
        total += 3;
    }
    MESSAGE("scrGet*Para: " << total << " cases compared (" << beyond << " arguments beyond the stack, " << strings << " strings)");
}

#else

TEST_CASE("game: script VM replacements (skipped: built without the recompiled bodies)") {
    MESSAGE("SKIP: tests/game needs the ELF at configure time (P3FES_RT_EXEC_ELF)");
}

#endif
