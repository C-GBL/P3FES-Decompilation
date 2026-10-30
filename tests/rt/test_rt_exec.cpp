// First execution of recompiled code against the rt adapter (Phase 3 milestone).
//
// The build emits a subset of pure libc functions from the user's ELF (tests/rt/CMakeLists.txt:
// p3fes_recomp --out --only <subset>, cycles and check points on), compiles it with p3fes_rt and
// links it here. Each function is called through rt::lookup_func with its arguments in $a0..$a3
// on a guest machine set up like the game's (ELF image loaded at 0x100000, $gp = 0x7D2CF0 from
// crt0, $sp inside the main-thread stack 0x1F60000-0x2000000; docs/RUNTIME_CONTRACT.md §1.1 and
// H-46), and compared with the host C library on randomised inputs: the return value, and every
// byte of the guest scratch arena against a host mirror to which the host function was applied
// (so a stray store anywhere in the arena fails the test).
//
// Purity of the subset was checked on the emitted code (no rt::syscall, no calls, no
// rt::lookup_func, no hardware addresses; constants are byte masks) and is enforced at run time:
// the test hooks count syscalls, traps and bus accesses, and RtHooks::fatal throws.
// Skips (doctest MESSAGE) when the build had no ELF to emit from, or the ELF is absent now.
#include "fake_hooks.h"

#include "elf_image.h"
#include "p3fes/ee_memory.h"
#include "p3fes_recomp_rt.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_RT_EXEC_HAVE_GENERATED
#define P3FES_RT_EXEC_HAVE_GENERATED 0
#endif

using namespace p3fes;
using rt_test::FatalEvent;
using rt_test::HooksScope;
using rt_test::TestHooks;

REGISTER_EXCEPTION_TRANSLATOR(const p3fes::rt_test::FatalEvent& e) {
    return doctest::String(("RtHooks::fatal: " + e.what).c_str());
}

#if P3FES_RT_EXEC_HAVE_GENERATED

namespace {

// symbols/p3fes.sym (FLIRT names; bodies read in the emitted code).
constexpr u32 kMemcmp = 0x5211B8, kMemcpy = 0x521250, kMemmove = 0x521300, kMemset = 0x521408;
constexpr u32 kStrchr = 0x523F98, kStrcmp = 0x524128, kStrcpy = 0x524270, kStrlen = 0x524388;
constexpr u32 kStrncat = 0x5244C0, kStrncmp = 0x524670, kStrncpy = 0x524828;

constexpr u32 kGp = 0x007D2CF0u;     // crt0's $gp (RUNTIME_CONTRACT H-46)
constexpr u32 kSp = 0x01FFFF00u;     // inside the main-thread stack 0x1F60000-0x2000000
constexpr u32 kArena = 0x01800000u;  // guest scratch arena: free RAM far above .bss/heap start
constexpr u32 kArenaSize = 0x2000u;

u64 sx(u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); }

const char* elf_path() {
    const char* p = std::getenv("P3FES_ELF");
    return p ? p : P3FES_ELF_DEFAULT;
}

struct Machine {
    EEMemory mem;
    EEContext ctx;
    TestHooks hooks;
    HooksScope scope{&hooks};
    std::vector<u8> mirror = std::vector<u8>(kArenaSize);
    std::map<u32, int> calls;
    std::mt19937 rng{0x5EED1234u};

    Machine() {
        ctx.memory = &mem;
        rt::bind_context(&ctx);
    }

    // Load every PT_LOAD of the verified ELF into guest RAM (filesz bytes; .bss stays zero).
    const char* load_elf(const char* path) {
        recomp::ElfImage elf;
        const recomp::ElfImage::LoadResult r = elf.load(path);
        if (r.error) return r.error;
        for (const recomp::ElfSegment& s : elf.segments()) {
            if (s.vaddr + s.memsz > EEMemory::kMainRamSize) return "segment outside main RAM";
            if (s.filesz == 0) continue;  // memory-only segment: stays zero
            const u8* bytes = elf.bytes_at(s.vaddr, s.filesz);
            if (!bytes) return "segment bytes unavailable";
            std::memcpy(mem.main_ram() + s.vaddr, bytes, s.filesz);
        }
        return nullptr;
    }

    u8* arena() { return mem.main_ram() + kArena; }
    u8* host(u32 guest) { return mirror.data() + (guest - kArena); }

    void fill_arena() {
        for (u32 i = 0; i < kArenaSize; ++i) arena()[i] = static_cast<u8>(rng());
        std::memcpy(mirror.data(), arena(), kArenaSize);
    }
    // A random NUL-terminated string of `len` bytes (1..255) written to both copies at `at`.
    void put_string(u32 at, std::size_t len) {
        for (std::size_t i = 0; i < len; ++i) arena()[at - kArena + i] = static_cast<u8>(1 + rng() % 255);
        arena()[at - kArena + len] = 0;
        std::memcpy(host(at), arena() + (at - kArena), len + 1);
    }
    u32 rand_addr(u32 lo, u32 hi) { return kArena + lo + static_cast<u32>(rng() % (hi - lo)); }
    u32 rand_below(u32 n) { return n ? static_cast<u32>(rng() % n) : 0u; }

    u64 call(u32 fn, u64 a0, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0) {
        ctx.gpr[GPR_A0].u64[0] = a0;
        ctx.gpr[GPR_A1].u64[0] = a1;
        ctx.gpr[GPR_A2].u64[0] = a2;
        ctx.gpr[GPR_A3].u64[0] = a3;
        ctx.gpr[GPR_SP].u64[0] = sx(kSp);
        ctx.gpr[GPR_GP].u64[0] = sx(kGp);
        ctx.gpr[GPR_RA].u64[0] = 0;
        rt::lookup_func(fn)(ctx);
        ++calls[fn];
        return ctx.gpr[GPR_V0].u64[0];
    }
    // Compares the guest arena with the host mirror; on a difference reports the first differing
    // address and resynchronises the mirror so later checks are independent.
    bool arena_matches() {
        const u8* g = mem.main_ram() + kArena;
        for (u32 i = 0; i < kArenaSize; ++i) {
            if (g[i] != mirror[i]) {
                MESSAGE("first arena difference at 0x" << std::hex << (kArena + i) << ": guest 0x"
                        << static_cast<unsigned>(g[i]) << ", host 0x" << static_cast<unsigned>(mirror[i]) << std::dec);
                std::memcpy(mirror.data(), g, kArenaSize);
                return false;
            }
        }
        return true;
    }
};

int sign(long long v) { return v < 0 ? -1 : (v > 0 ? 1 : 0); }

constexpr int kIterations = 300;

} // namespace

TEST_CASE("exec: recompiled libc functions run on the rt adapter and match the host C library") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err) << " (set P3FES_ELF)");
        return;
    }
    // The ELF text really is there: strlen's first word (andi v0, a0, 7).
    REQUIRE(m.mem.read<u32>(kStrlen) == 0x30820007u);

    SUBCASE("strlen") {
        for (int i = 0; i < kIterations; ++i) {
            m.fill_arena();
            const u32 s = m.rand_addr(0, 0x1000);
            const std::size_t len = m.rand_below(400);
            m.put_string(s, len);
            const u64 v0 = m.call(kStrlen, sx(s));
            CHECK(v0 == std::strlen(reinterpret_cast<const char*>(m.host(s))));
            CHECK(m.arena_matches());
        }
    }
    SUBCASE("strcmp / strncmp / memcmp") {
        for (int i = 0; i < kIterations; ++i) {
            m.fill_arena();
            const u32 a = m.rand_addr(0, 0x0C00), b = m.rand_addr(0x0C00, 0x1800);
            const std::size_t len = m.rand_below(300);
            m.put_string(a, len);
            std::memcpy(m.arena() + (b - kArena), m.arena() + (a - kArena), len + 1);
            std::memcpy(m.host(b), m.host(a), len + 1);
            if (len && m.rand_below(4) != 0) {  // usually differ at one position (or end early)
                const std::size_t k = m.rand_below(static_cast<u32>(len));
                const u8 c = static_cast<u8>(m.rand_below(256));
                m.arena()[b - kArena + k] = c;
                *m.host(b + static_cast<u32>(k)) = c;
            }
            const char* ha = reinterpret_cast<const char*>(m.host(a));
            const char* hb = reinterpret_cast<const char*>(m.host(b));
            CHECK(sign(static_cast<s32>(m.call(kStrcmp, sx(a), sx(b)))) == sign(std::strcmp(ha, hb)));
            const u32 n = m.rand_below(320);
            CHECK(sign(static_cast<s32>(m.call(kStrncmp, sx(a), sx(b), sx(n)))) == sign(std::strncmp(ha, hb, n)));
            const u32 nm = m.rand_below(static_cast<u32>(len) + 2);
            CHECK(sign(static_cast<s32>(m.call(kMemcmp, sx(a), sx(b), sx(nm)))) == sign(std::memcmp(ha, hb, nm)));
            CHECK(m.arena_matches());
        }
    }
    SUBCASE("memcpy / memmove / memset") {
        for (int i = 0; i < kIterations; ++i) {
            m.fill_arena();
            // Disjoint ranges (memcpy's contract): src + n < 0x0C00 <= dst.
            const u32 src = m.rand_addr(0, 0x0600), dst = m.rand_addr(0x0C00, 0x1400);
            const u32 n = m.rand_below(0x0600);
            CHECK(static_cast<u32>(m.call(kMemcpy, sx(dst), sx(src), sx(n))) == dst);
            std::memcpy(m.host(dst), m.host(src), n);
            CHECK(m.arena_matches());

            // Overlapping move in either direction inside one window.
            const u32 w = m.rand_addr(0, 0x1000);
            const u32 s2 = w + m.rand_below(0x200), d2 = w + m.rand_below(0x200);
            const u32 n2 = m.rand_below(0x400);
            CHECK(static_cast<u32>(m.call(kMemmove, sx(d2), sx(s2), sx(n2))) == d2);
            std::memmove(m.host(d2), m.host(s2), n2);
            CHECK(m.arena_matches());

            const u32 d3 = m.rand_addr(0, 0x1000);
            const u32 n3 = m.rand_below(0x0C00);
            const u32 c = static_cast<u32>(m.rng());  // only the low byte counts
            CHECK(static_cast<u32>(m.call(kMemset, sx(d3), sx(c), sx(n3))) == d3);
            std::memset(m.host(d3), static_cast<int>(c & 0xFFu), n3);
            CHECK(m.arena_matches());
        }
    }
    SUBCASE("strcpy / strncpy / strncat / strchr") {
        for (int i = 0; i < kIterations; ++i) {
            m.fill_arena();
            const u32 src = m.rand_addr(0, 0x0800), dst = m.rand_addr(0x0C00, 0x1000);
            const std::size_t len = m.rand_below(250);
            m.put_string(src, len);
            CHECK(static_cast<u32>(m.call(kStrcpy, sx(dst), sx(src))) == dst);
            std::strcpy(reinterpret_cast<char*>(m.host(dst)), reinterpret_cast<const char*>(m.host(src)));
            CHECK(m.arena_matches());

            const u32 n = m.rand_below(300);
            CHECK(static_cast<u32>(m.call(kStrncpy, sx(dst), sx(src), sx(n))) == dst);
            std::strncpy(reinterpret_cast<char*>(m.host(dst)), reinterpret_cast<const char*>(m.host(src)), n);
            CHECK(m.arena_matches());

            const u32 d2 = m.rand_addr(0x1400, 0x1600);
            m.put_string(d2, m.rand_below(120));
            const u32 n2 = m.rand_below(300);
            CHECK(static_cast<u32>(m.call(kStrncat, sx(d2), sx(src), sx(n2))) == d2);
            std::strncat(reinterpret_cast<char*>(m.host(d2)), reinterpret_cast<const char*>(m.host(src)), n2);
            CHECK(m.arena_matches());

            // strchr: a byte from the string, a random byte, or NUL (pointer to the terminator).
            const u32 pick = m.rand_below(3);
            int c = 0;
            if (pick == 0 && len) c = *m.host(src + m.rand_below(static_cast<u32>(len)));
            else if (pick == 1) c = static_cast<int>(1 + m.rand_below(255));
            const char* hs = reinterpret_cast<const char*>(m.host(src));
            const char* hit = std::strchr(hs, c);
            const u32 want = hit ? src + static_cast<u32>(hit - hs) : 0u;
            CHECK(static_cast<u32>(m.call(kStrchr, sx(src), sx(static_cast<u32>(c)))) == want);
            CHECK(m.arena_matches());
        }
    }

    // Nothing but pure computation happened.
    CHECK(m.hooks.syscalls == 0);
    CHECK(m.hooks.traps == 0);
    CHECK(m.hooks.bus_.log.empty());
    CHECK(m.mem.unmapped_accesses() == 0);
    CHECK(m.hooks.checks > 0);
    int total = 0;
    std::string per;
    for (const auto& [fn, n] : m.calls) {
        total += n;
        char buf[48];
        std::snprintf(buf, sizeof buf, " 0x%06x:%d", fn, n);
        per += buf;
    }
    MESSAGE("calls " << total << " (" << per << " ), check points " << m.hooks.checks << ", cycles " << m.ctx.cycles);
}

TEST_CASE("exec: cycle accounting of one strlen(16 bytes) equals its executed instruction words") {
    Machine m;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err));
        return;
    }
    const u32 s = kArena + 0x100;  // 16-byte aligned: the lq path
    std::memcpy(m.arena() + 0x100, "0123456789abcdef", 17);
    const u64 c0 = m.ctx.cycles;
    const int k0 = m.hooks.checks;
    CHECK(m.call(kStrlen, sx(s)) == 16u);
    const u64 cycles = m.ctx.cycles - c0;
    // Executed words of strlen (0x524388) for an aligned 16-byte string, read from the --annotate
    // emission: andi/bne/slot 3 + andi, lui, 5 x ori/dsll, bne/slot 9 + lq ... bnel/slot 17 +
    // addiu 1 + one pass of the lq loop (lq ... beql/slot) 9 + b/slot 2 + lb, 4 load-delay nops
    // (0x5244a0..0x5244ac: dropped from the C++, counted in N), bnel/slot 7 + jr/slot 2 = 50.
    CHECK(cycles == 50u);
    // Only the entry check: the lq loop and the byte loop each exit on their first pass without
    // taking their back-edge.
    MESSAGE("strlen(16 bytes, aligned): " << cycles << " cycles, " << (m.hooks.checks - k0) << " check points");
    CHECK(m.hooks.checks - k0 == 1);
}

#else

TEST_CASE("exec: recompiled libc functions run on the rt adapter and match the host C library") {
    MESSAGE("SKIP: built without the ELF (extracted/disc/SLUS_216.21 absent at configure time); no recompiled "
            "subset to execute");
}

#endif
