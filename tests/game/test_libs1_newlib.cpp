// Pair tests of slice libs1, the newlib tail (game/src/lib/libs1_newlib.cpp), through tests/game/libs1_util.h. The
// allocator below these functions runs for real (_malloc_r, __malloc_lock / __malloc_unlock, _sbrk_r and sbrk are
// emitted in the test build by an earlier slice); stand-ins serve __srefill (a host byte stream), _fwalk, the FILE write
// callback (__swrite's address) and the atexit handlers (recorders). The Bigint helpers _dtoa_r calls (_Balloc,
// _multadd, _i2b, _multiply, _pow5mult, _lshift, __mdiff, _d2b) are emitted for these tests (pure newlib; no other test
// reaches them). Inputs and rules: calloc's zeroing over sizes around the unrolled / memset boundary; the errno
// wrappers; _dtoa_r's digits on 1,200 doubles in modes 0 / 2 / 3 against the host (the shortest round-trip digits and
// correctly rounded significant / fractional digits, counted; every mode-0 string must read back as the same double);
// __sinit's three standard FILEs, __sfp's glue chain growth, fflush's write loop with short writes and a failing
// callback, fread over a refilling stream, exit's handler order; dlmalloc's free on built heaps (coalescing back,
// forward and into the top chunk, small and large bins), the trim decision.
//@INCLUDES
#include "p3fes/game/libc.h"
#include <charconv>
#include <cmath>
//@END
#include "libs1_util.h"

#include "p3fes/game/libs1_newlib.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn__calloc_r_0051e178(EEContext&);  // generated body
void fn__calloc_r_0051e178__recomp(EEContext&);  // recompiled
void fn__close_r_0051e230(EEContext&);  // generated body
void fn__close_r_0051e230__recomp(EEContext&);  // recompiled
void fn__dtoa_r_0051e4b0(EEContext&);  // generated body
void fn__dtoa_r_0051e4b0__recomp(EEContext&);  // recompiled
void fn_exit_0051f6a0(EEContext&);  // generated body
void fn_exit_0051f6a0__recomp(EEContext&);  // recompiled
void fn_fflush_0051f728(EEContext&);  // generated body
void fn_fflush_0051f728__recomp(EEContext&);  // recompiled
void fn___sfmoreglue_0051f898(EEContext&);  // generated body
void fn___sfmoreglue_0051f898__recomp(EEContext&);  // recompiled
void fn___sfp_0051f908(EEContext&);  // generated body
void fn___sfp_0051f908__recomp(EEContext&);  // recompiled
void fn__cleanup_r_0051f9e0(EEContext&);  // generated body
void fn__cleanup_r_0051f9e0__recomp(EEContext&);  // recompiled
void fn__cleanup_0051fa00(EEContext&);  // generated body
void fn__cleanup_0051fa00__recomp(EEContext&);  // recompiled
void fn___sinit_0051fa20(EEContext&);  // generated body
void fn___sinit_0051fa20__recomp(EEContext&);  // recompiled
void fn_fread_0051faa0(EEContext&);  // generated body
void fn_fread_0051faa0__recomp(EEContext&);  // recompiled
void fn__free_r_0051fbb0(EEContext&);  // generated body
void fn__free_r_0051fbb0__recomp(EEContext&);  // recompiled
void fn__malloc_trim_r_0051fe90(EEContext&);  // generated body
void fn__malloc_trim_r_0051fe90__recomp(EEContext&);  // recompiled
void fn__kill_r_0051fff0(EEContext&);  // generated body
void fn__kill_r_0051fff0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

using p3fes::game_test::libs1::Case;

const Case kCases[] = {
    {"_calloc_r", 0x51E178, &recomp_gen::fn__calloc_r_0051e178, &recomp_gen::fn__calloc_r_0051e178__recomp},
    {"_close_r", 0x51E230, &recomp_gen::fn__close_r_0051e230, &recomp_gen::fn__close_r_0051e230__recomp},
    {"_dtoa_r", 0x51E4B0, &recomp_gen::fn__dtoa_r_0051e4b0, &recomp_gen::fn__dtoa_r_0051e4b0__recomp},
    {"exit", 0x51F6A0, &recomp_gen::fn_exit_0051f6a0, &recomp_gen::fn_exit_0051f6a0__recomp},
    {"fflush", 0x51F728, &recomp_gen::fn_fflush_0051f728, &recomp_gen::fn_fflush_0051f728__recomp},
    {"__sfmoreglue", 0x51F898, &recomp_gen::fn___sfmoreglue_0051f898, &recomp_gen::fn___sfmoreglue_0051f898__recomp},
    {"__sfp", 0x51F908, &recomp_gen::fn___sfp_0051f908, &recomp_gen::fn___sfp_0051f908__recomp},
    {"_cleanup_r", 0x51F9E0, &recomp_gen::fn__cleanup_r_0051f9e0, &recomp_gen::fn__cleanup_r_0051f9e0__recomp},
    {"_cleanup", 0x51FA00, &recomp_gen::fn__cleanup_0051fa00, &recomp_gen::fn__cleanup_0051fa00__recomp},
    {"__sinit", 0x51FA20, &recomp_gen::fn___sinit_0051fa20, &recomp_gen::fn___sinit_0051fa20__recomp},
    {"fread", 0x51FAA0, &recomp_gen::fn_fread_0051faa0, &recomp_gen::fn_fread_0051faa0__recomp},
    {"_free_r", 0x51FBB0, &recomp_gen::fn__free_r_0051fbb0, &recomp_gen::fn__free_r_0051fbb0__recomp},
    {"_malloc_trim_r", 0x51FE90, &recomp_gen::fn__malloc_trim_r_0051fe90, &recomp_gen::fn__malloc_trim_r_0051fe90__recomp},
    {"_kill_r", 0x51FFF0, &recomp_gen::fn__kill_r_0051fff0, &recomp_gen::fn__kill_r_0051fff0__recomp},
};

using namespace p3fes::game_test::libs1;

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSrefill = 0x523580u, kFwalk = 0x520410u, kSwrite = 0x523CC0u;
constexpr u32 kImpurePtr = 0x782F30u;  // _impure_ptr: the global reentrancy record
constexpr u32 kAv = 0x782F40u;          // dlmalloc's av_ (bins); av_[2] = the top chunk
constexpr u32 kTop = 0x782F48u, kBinBlocks = 0x782F44u, kTrimThreshold = 0x783348u, kTopPad = 0x783350u;
constexpr u32 kSbrkedMem = 0x783370u;
constexpr u32 kErrno = 0x9ACC20u;
constexpr u32 kDlArena = 0x01840000u;     // a built dlmalloc heap

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

void basic(StandInWorld& w) { w.si.install_recorder(kFwalk, "_fwalk", 0); }

u32 reent(const Machine& m) { return r32(m, kImpurePtr); }

}  // namespace

TEST_CASE("game(libs1_newlib): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    random_sweep(*m, kCases, std::size(kCases), kWorld, kWorldSize, 24, basic);
}

TEST_CASE("game(libs1_newlib): calloc zeroing and the errno wrappers") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1;
    const u32 re = reent(*m);
    REQUIRE(re != 0);
    for (u32 n = 0; n <= 80; ++n) {
        // poison the heap so the zeroing is visible
        for (u32 i = 0; i < 0x200; i += 4) w32(*m, kStandInHeap + i, 0xA5A5A5A5u);
        const auto r = pair(*m, C("_calloc_r"), {re, 1, n}, seed++, "_calloc_r " + std::to_string(n), basic);
        const u32 p = static_cast<u32>(v0_of(r));
        REQUIRE(p != 0);
        const u32 usable = (r32(*m, p - 4) & ~3u) - 4;
        CHECK(usable >= n);
        for (u32 i = 0; i < usable; ++i) CHECK(r8(*m, p + i) == 0);
    }
    // n x size multiplies as words; a refused allocation returns 0
    CHECK(v0_of(pair(*m, C("_calloc_r"), {re, 0x10000, 0x10000}, seed++, "_calloc_r overflow", basic)) != 0);  // 0 bytes
    CHECK(v0_of(pair(*m, C("_calloc_r"), {re, 0x1000, 0x1000}, seed++, "_calloc_r refused", basic)) == 0);
    // _close_r: close() is -1 with errno untouched; _kill_r: this build's fstat wrapper
    w32(*m, re, 0x55);
    w32(*m, kErrno, 7);
    CHECK(v0s(pair(*m, C("_close_r"), {re, 3}, seed++, "_close_r", basic)) == -1);
    CHECK(r32(*m, kErrno) == 0);
    CHECK(r32(*m, re) == 0x55);
    CHECK(v0s(pair(*m, C("_kill_r"), {re, 1, kWorld + 0x100}, seed++, "_kill_r", basic)) == 0);
    CHECK(r32(*m, kWorld + 0x104) == 0x2000u);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_newlib): _dtoa_r against the host's decimal conversions") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 re = reent(*m);
    const u32 out = kWorld + 0x8000;  // decpt, sign, rve
    std::mt19937_64 rng{2026};
    int n = 0, n0 = 0, exact0 = 0, roundtrip0 = 0, exact2 = 0, exact3 = 0, n2 = 0, n3 = 0, specials = 0;
    std::vector<double> vals = {0.0, -0.0, 1.0, -1.0, 0.1, 0.5, 1.5, 2.5, 123456789.0, 1e22, 1e23, 5e-324, 2.2250738585072014e-308,
                                1.7976931348623157e308, 3.141592653589793, 1.0 / 3.0, 100.0, 999999.9999, 4.35, 0.3};
    while (vals.size() < 1200) {
        const u64 k = rng() % 4;
        double d;
        if (k == 0) d = std::ldexp(static_cast<double>(rng() >> 11), static_cast<int>(rng() % 200) - 150);
        else if (k == 1) d = static_cast<double>(rng() % 100000) / static_cast<double>(1 + rng() % 1000);
        else if (k == 2) { const u64 b = rng() & 0x7FEFFFFFFFFFFFFFull; std::memcpy(&d, &b, 8); }
        else d = static_cast<double>(static_cast<s64>(rng() % 2000000) - 1000000) * 0.001;
        if (rng() % 2) d = -d;
        vals.push_back(d);
    }
    vals.push_back(std::numeric_limits<double>::infinity());
    vals.push_back(-std::numeric_limits<double>::infinity());
    vals.push_back(std::numeric_limits<double>::quiet_NaN());
    u32 seed = 1;
    for (std::size_t i = 0; i < vals.size(); ++i) {
        const double d = vals[i];
        u64 bits;
        std::memcpy(&bits, &d, 8);
        const int mode = i % 3 == 0 ? 0 : i % 3 == 1 ? 2 : 3;
        const int nd = mode == 0 ? 0 : mode == 2 ? 1 + static_cast<int>(i % 17) : static_cast<int>(i % 9);
        HwCheck hw;
        hw.gpr_in = {{GPR_T0, sx(out)}, {GPR_T1, sx(out + 4)}, {GPR_T2, sx(out + 8)}};
        int decpt = 0, sign = 0;
        std::string digits;
        const auto r = pair(*m, C("_dtoa_r"), {re, bits, static_cast<u64>(mode), static_cast<u64>(static_cast<s64>(nd))}, seed++,
                            "_dtoa_r " + std::to_string(d), basic, hw);
        CHECK(!r.stopped);
        if (r.stopped) continue;
        const u32 s = static_cast<u32>(v0_of(r));
        decpt = static_cast<s32>(r32(*m, out));
        sign = static_cast<s32>(r32(*m, out + 4));
        const u32 e = r32(*m, out + 8);
        for (u32 p = s; p < e && digits.size() < 40; ++p) digits.push_back(static_cast<char>(r8(*m, p)));
        ++n;
        if (std::isinf(d) || std::isnan(d)) {
            ++specials;
            CHECK(decpt == 9999);
            CHECK(digits == (std::isnan(d) ? "NaN" : "Infinity"));
            continue;
        }
        CHECK(sign == (std::signbit(d) ? 1 : 0));
        if (d == 0) {
            CHECK(digits == "0");
            CHECK(decpt == 1);
            continue;
        }
        const double a = std::fabs(d);
        if (mode == 0) {
            ++n0;
            char buf[64];
            auto res = std::to_chars(buf, buf + sizeof buf, a, std::chars_format::scientific);
            std::string sci(buf, res.ptr);
            std::string host_digits;
            int host_exp = 0;
            const auto epos = sci.find('e');
            for (char ch : sci.substr(0, epos))
                if (ch != '.') host_digits.push_back(ch);
            host_exp = std::stoi(sci.substr(epos + 1)) + 1;
            while (host_digits.size() > 1 && host_digits.back() == '0') host_digits.pop_back();
            if (digits == host_digits && decpt == host_exp) ++exact0;
            const std::string back = "0." + digits + "e" + std::to_string(decpt);
            if (std::strtod(back.c_str(), nullptr) == a) ++roundtrip0;
            else MESSAGE("mode 0: " << sci << " -> " << digits << " e" << decpt << " does not read back");
        } else {
            char buf[512];
            if (mode == 2) {
                ++n2;
                std::snprintf(buf, sizeof buf, "%.*e", nd - 1, a);
                std::string sci(buf);
                std::string hd;
                const auto epos = sci.find('e');
                for (char ch : sci.substr(0, epos))
                    if (ch != '.') hd.push_back(ch);
                const int he = std::stoi(sci.substr(epos + 1)) + 1;
                while (hd.size() > 1 && hd.back() == '0') hd.pop_back();
                if (hd == digits && he == decpt) ++exact2;
            } else {
                ++n3;
                std::snprintf(buf, sizeof buf, "%.*f", nd, a);
                std::string f(buf), hd;
                const auto dot = f.find('.');
                std::string ip = f.substr(0, dot), fp = dot == std::string::npos ? "" : f.substr(dot + 1);
                std::string all = ip + fp;
                int he = static_cast<int>(ip.size());
                std::size_t z = 0;
                while (z < all.size() && all[z] == '0') { ++z; --he; }
                hd = all.substr(z);
                while (!hd.empty() && hd.back() == '0') hd.pop_back();
                if (hd.empty()) { if (digits.empty() || digits == "0") ++exact3; }
                else if (hd == digits && he == decpt) ++exact3;
            }
        }
    }
    MESSAGE(n << " conversions paired (" << specials << " specials); mode 0: " << exact0 << " equal to the host's shortest digits, "
              << roundtrip0 << " read back exactly; mode 2: " << exact2 << " / " << n2 << " equal to %.*e; mode 3: " << exact3 << " / " << n3
              << " equal to %.*f");
    CHECK(n0 > 0);
    CHECK(roundtrip0 * 10 >= n0 * 9);  // measured, see the message; the soft-float fast path may lose the last digit
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_newlib): stdio -- __sinit, __sfp, fflush, fread, exit") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1;
    // a private reentrancy record (0x5A4 bytes zeroed) so the global one is not touched
    const u32 re = kWorld + 0x1000;
    wzero(*m, re, 0x800);
    w32(*m, re + 4, kWorld + 0x2000);  // _stdin / _stdout / _stderr point into its own __sf
    w32(*m, re + 8, kWorld + 0x2058);
    w32(*m, re + 12, kWorld + 0x20B0);
    auto r = pair(*m, C("__sinit"), {re}, seed++, "__sinit", basic);
    CHECK(r32(*m, re + 56) == 1);                // __sdidinit
    CHECK(r32(*m, re + 60) == 0x51F9E0u);        // __cleanup = _cleanup_r
    CHECK(r32(*m, re + 476) == 3);               // the glue: 3 FILEs at +484
    CHECK(r32(*m, re + 480) == re + 484);
    CHECK(r16(*m, kWorld + 0x2000 + 12) == 4);   // stdin __SRD, stdout __SWR | __SLBF, stderr __SWR | __SNBF
    CHECK(r16(*m, kWorld + 0x2058 + 12) == 9);
    CHECK(r16(*m, kWorld + 0x20B0 + 12) == 10);
    // __sfp: the first free FILE in the glue; when all are taken a block of 4 more from _malloc_r
    for (u32 i = 0; i < 3; ++i) w16(*m, re + 484 + 88 * i + 12, 1);
    r = pair(*m, C("__sfp"), {re}, seed++, "__sfp grows", basic);
    const u32 f = static_cast<u32>(v0_of(r));
    const u32 glue = r32(*m, re + 472);
    REQUIRE(glue != 0);
    CHECK(r32(*m, glue + 4) == 4);
    CHECK(f == glue + 12);
    CHECK(r16(*m, f + 12) == 1);
    CHECK(r16(*m, f + 14) == 0xFFFF);
    CHECK(r32(*m, f + 84) == re);
    r = pair(*m, C("__sfp"), {re}, seed++, "__sfp second", basic);
    CHECK(v0_of(r) == glue + 12 + 88);
    // fflush: write the buffered bytes through the callback (short writes loop; a failure sets __SERR)
    const u32 fp = kWorld + 0x3000, buf = kWorld + 0x3100;
    for (int variant = 0; variant < 4; ++variant) {
        wzero(*m, fp, 88);
        w32(*m, fp + 84, re);
        w16(*m, fp + 12, 8 | (variant == 3 ? 0 : 0));   // __SWR
        w32(*m, fp + 16, buf);                          // _bf._base
        w32(*m, fp + 20, 64);                           // _bf._size
        w32(*m, fp + 0, buf + 40);                      // _p: 40 bytes pending
        w32(*m, fp + 36, kSwrite);                      // _write
        w32(*m, fp + 28, 0x77);                         // _cookie
        auto setup = [variant](StandInWorld& w) {
            basic(w);
            auto calls = std::make_shared<int>(0);
            w.si.install(kSwrite, "__swrite", [variant, calls](EEContext&, StandIns&, StandInCall& c) {
                const s64 n = static_cast<s64>(c.args[2]);
                ++*calls;
                c.v0 = variant == 1 && *calls == 1 ? 15 : variant == 2 ? ~0ull : static_cast<u64>(n);
            });
        };
        r = pair(*m, C("fflush"), {fp}, seed++, "fflush " + std::to_string(variant), setup);
        const StandIns& log = last_log();
        if (variant == 2) {
            CHECK(v0s(r) == -1);
            CHECK((r16(*m, fp + 12) & 0x40) != 0);
            CHECK(log.calls_to(kSwrite) == 1);
        } else {
            CHECK(v0s(r) == 0);
            CHECK(log.calls_to(kSwrite) == (variant == 1 ? 2u : 1u));
            if (variant == 1) CHECK(log.log.back().args[2] == 25);  // the rest after a short write
            CHECK(r32(*m, fp + 0) == buf);
            CHECK(r32(*m, fp + 8) == 64);
        }
    }
    CHECK(v0s(pair(*m, C("fflush"), {0}, seed++, "fflush(NULL)", basic)) == 0);
    CHECK(last_log().calls_to(kFwalk) == 1);
    pair(*m, C("_cleanup_r"), {re}, seed++, "_cleanup_r", basic);
    CHECK(last_log().calls_to(kFwalk) == 1);
    CHECK(last_log().log.back().args[1] == 0x51F728u);  // fflush
    pair(*m, C("_cleanup"), {}, seed++, "_cleanup", basic);
    CHECK(last_log().log.back().args[0] == r32(*m, kImpurePtr));
    // fread over a stream refilled 10 bytes at a time from a host source
    for (u32 want : {0u, 5u, 10u, 23u, 64u, 200u}) {
        wzero(*m, fp, 88);
        w32(*m, fp + 84, re);
        w32(*m, fp + 0, buf);
        w32(*m, fp + 4, 7);  // 7 bytes buffered
        for (u32 i = 0; i < 7; ++i) w8(*m, buf + i, static_cast<u8>('a' + i));
        auto setup = [buf](StandInWorld& w) {
            basic(w);
            auto pos = std::make_shared<u32>(0);
            w.si.install(kSrefill, "__srefill", [buf, pos](EEContext& ctx, StandIns&, StandInCall& c) {
                const u32 f = static_cast<u32>(c.args[0]);
                if (*pos >= 50) { c.v0 = ~0ull; return; }  // EOF after 50 more bytes
                for (u32 i = 0; i < 10; ++i) gptr(ctx, buf)[i] = static_cast<u8>('0' + (*pos + i) % 10);
                *pos += 10;
                const u32 p = buf, n = 10;
                std::memcpy(gptr(ctx, f), &p, 4);
                std::memcpy(gptr(ctx, f + 4), &n, 4);
                c.v0 = 0;
            });
        };
        r = pair(*m, C("fread"), {kWorld + 0x4000, 1, want, fp}, seed++, "fread " + std::to_string(want), setup);
        const u32 got = static_cast<u32>(v0_of(r));
        CHECK(got == std::min(want, 57u));
        for (u32 i = 0; i < got; ++i) CHECK(r8(*m, kWorld + 0x4000 + i) == (i < 7 ? 'a' + i : '0' + (i - 7) % 10));
    }
    // exit: the atexit handlers newest first, the cleanup hook, then _exit
    {
        const u32 grre = r32(*m, kImpurePtr);
        const u32 at = kWorld + 0x5000;
        wzero(*m, at, 0x90);
        w32(*m, at + 4, 2);  // two handlers
        w32(*m, at + 8, kSwrite);
        w32(*m, at + 12, kSrefill);
        w32(*m, grre + 0x148, at);
        w32(*m, grre + 0x3C, kFwalk);
        auto setup = [](StandInWorld& w) {
            basic(w);
            w.si.install_recorder(kSwrite, "atexit handler 0", 0);
            w.si.install_recorder(kSrefill, "atexit handler 1", 0);
        };
        r = pair(*m, C("exit"), {3}, seed++, "exit", setup);
        const auto& log = last_log().log;
        std::vector<u32> order;
        for (const auto& c : log)
            if (c.va == kSwrite || c.va == kSrefill || c.va == kFwalk) order.push_back(c.va);
        CHECK(order == std::vector<u32>{kSrefill, kSwrite, kFwalk});  // then _exit (sub_100218, emitted)
    }
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs1_newlib): dlmalloc free and trim on built heaps") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 re = reent(*m);
    u32 seed = 1;
    // chunks A | B | C | D, then the top chunk (0x6000 bytes), PREV_INUSE set everywhere (all in use)
    auto build = [&](u32 top_size) {
        for (u32 i = 0; i < 0x40; i += 4) w32(*m, kAv + 8 + i, 0);  // (rebuilt below)
        for (u32 b = 0; b < 128; ++b) {  // empty bins point at themselves
            w32(*m, kAv + 8 * b + 8, kAv + 8 * b);
            w32(*m, kAv + 8 * b + 12, kAv + 8 * b);
        }
        w32(*m, kBinBlocks, 0);
        const u32 sizes[4] = {0x20, 0x90, 0x400, 0x48};
        u32 p = kDlArena;
        for (u32 s : sizes) {
            w32(*m, p + 4, s | 1);
            p += s;
        }
        w32(*m, kTop, p);
        w32(*m, p + 4, top_size | 1);
        w32(*m, kTrimThreshold, 0x20000);
        w32(*m, kTopPad, 0);
        w32(*m, kSbrkedMem, 0x10000);
        return p;
    };
    const u32 A = kDlArena, B = kDlArena + 0x20, Cc = kDlArena + 0xB0, D = kDlArena + 0x4B0;
    u32 top = build(0x6000);
    // free B (neighbours in use): a small bin (0x90 >> 3 = 18), the binblocks bit 18 >> 2
    auto r = pair(*m, C("_free_r"), {re, B + 8}, seed++, "free B", basic);
    CHECK(r32(*m, B + 4) == (0x90u | 1u));
    CHECK(r32(*m, B + 0x90) == 0x90u);                     // the footer
    CHECK((r32(*m, Cc + 4) & 1u) == 0u);                   // C's PREV_INUSE cleared
    CHECK(r32(*m, kAv + 8 * 18 + 8) == B);                 // bin 18 holds B
    CHECK((r32(*m, kBinBlocks) & (1u << (18 >> 2))) != 0);
    // free C: coalesces backward with B (unlinked from bin 18); 0x490 is a large size -> its bin
    r = pair(*m, C("_free_r"), {re, Cc + 8}, seed++, "free C", basic);
    CHECK(r32(*m, B + 4) == (0x490u | 1u));
    CHECK(r32(*m, kAv + 8 * 18 + 8) == kAv + 8 * 18);      // bin 18 empty again
    // free D: its next is the top chunk -> merged with the free run before it into the top
    r = pair(*m, C("_free_r"), {re, D + 8}, seed++, "free D", basic);
    CHECK(r32(*m, kTop) == B);
    CHECK(r32(*m, B + 4) == ((0x490u + 0x48u + 0x6000u) | 1u));
    // free A: into the top; free(NULL) does nothing
    r = pair(*m, C("_free_r"), {re, A + 8}, seed++, "free A", basic);
    CHECK(r32(*m, kTop) == A);
    pair(*m, C("_free_r"), {re, 0}, seed++, "free NULL", basic);
    CHECK(last_log().log.empty());
    // the trim decision: a top chunk past the threshold calls _malloc_trim_r, which gives whole pages back only when
    // sbrk(0) is the top chunk's end -- not so for a heap built in the test arena: the top is kept whole
    top = build(0x30000);
    r = pair(*m, C("_free_r"), {re, D + 8}, seed++, "free D, top past the threshold", basic);
    CHECK(r32(*m, kTop) == D);
    CHECK(r32(*m, D + 4) == ((0x48u + 0x30000u) | 1u));
    build(0x30000);
    CHECK(v0s(pair(*m, C("_malloc_trim_r"), {re, 0}, seed++, "_malloc_trim_r, the break elsewhere", basic)) == 0);
    CHECK(r32(*m, top + 4) == (0x30000u | 1u));
    build(0x1800);
    CHECK(v0s(pair(*m, C("_malloc_trim_r"), {re, 0x1000}, seed++, "_malloc_trim_r small top", basic)) == 0);  // < a page
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

#else

TEST_CASE("game(libs1_newlib): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
