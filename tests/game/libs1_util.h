// Shared pair runner and helpers of slice libs1's tests (tests/game/test_libs1_*.cpp; game/src/lib/libs1_*.cpp).
// Every pair runs the hand body and its recompiled body through tests/game/handgen_pairs.h (the whole register file and
// cycles at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log)
// with a fresh stand-in world around each body (tests/game/stand_ins.h); the two call logs must be equal, and so must
// any host-side state a stand-in keeps (the memory card image below).
//
// The memory card: a raw PS2 card image (528-byte pages: 512 data bytes + 16 ECC bytes, the layout of the route cards
// under extracted/_ours/cards) served at libmc2's core layer -- the page reads / writes / erases that go to the IOP on
// the console (_sceMcCoreReadPage2 / WritePage / ReadPageFast / WritePageFast / BlockErase / ReadClock /
// GetConnection; none of them is emitted in a test build). Each world gets its own copy, so writes are compared too.
#pragma once

#include "handgen_pairs.h"
#include "stand_ins.h"

#include <cstdio>
#include <cstring>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace p3fes::game_test::libs1 {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

using Setup = std::function<void(StandInWorld&)>;

// --- guest memory helpers -------------------------------------------------------------------------------------------
inline u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
inline u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2);
    return v;
}
inline u64 r64(const Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 8);
    return v;
}
inline u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
inline void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
inline void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
inline void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
inline void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
inline void wstr(Machine& m, u32 va, const std::string& s) {
    std::memcpy(m.at(va), s.data(), s.size());
    *m.at(va + static_cast<u32>(s.size())) = 0;
}
inline void wzero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
inline std::string gstr(const Machine& m, u32 va, u32 max = 512) { return m.str(va, max); }
inline u32 gu32(EEContext& ctx, u32 va) {
    u32 v;
    std::memcpy(&v, ctx.memory->main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
inline u8* gptr(EEContext& ctx, u32 va) { return ctx.memory->main_ram() + (va & 0x1FFFFFFu); }

// --- the pair runner ----------------------------------------------------------------------------------------------
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    Setup setup;
};
inline Tramp& tramp_state() {
    static Tramp t;
    return t;
}
template <int K>
void tramp(EEContext& c) {
    Tramp& t = tramp_state();
    t.world[K] = std::make_unique<StandInWorld>();
    if (t.setup) t.setup(*t.world[K]);
    StandInsScope scope(t.world[K]->si);
    t.fn[K](c);
}

struct Counts {
    int pairs = 0;
    int stops = 0;
};
inline Counts& counts() {
    static Counts c;
    return c;
}

// One pair of `c` from the machine's current state; afterwards the recompiled run's memory is in place.
inline hgp::Run pair(Machine& m, const Case& c, const Args& a, u32 seed, const std::string& what, const Setup& setup = {},
                     const HwCheck& hw = {}) {
    Tramp& t = tramp_state();
    t.fn[0] = c.hand;
    t.fn[1] = c.recomp;
    t.setup = setup;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what.c_str(), hw);
    if (t.world[0] && t.world[1]) expect_same_log(t.world[0]->si, t.world[1]->si, what.c_str());
    ++counts().pairs;
    if (r.stopped) ++counts().stops;
    if (std::getenv("P3FES_LIBS1_TRACE")) {  // debugging: the stop and the call log of every pair
        std::fprintf(stderr, "%s: %s%s\n", what.c_str(), r.stopped ? "stopped: " : "returned", r.stopped ? r.what.c_str() : "");
        if (t.world[1])
            for (const StandInCall& call : t.world[1]->si.log)
                std::fprintf(stderr, "    call %s a0=%llx a1=%llx a2=%llx -> %llx\n", t.world[1]->si.name_of(call.va).c_str(),
                             static_cast<unsigned long long>(call.args[0]), static_cast<unsigned long long>(call.args[1]),
                             static_cast<unsigned long long>(call.args[2]), static_cast<unsigned long long>(call.v0));
    }
    return r;
}
inline const StandIns& last_log() { return tramp_state().world[1]->si; }
// A HwCheck that only sets argument registers beyond $a3 ($t0..$t3) after the randomised context.
inline HwCheck hw_in(std::initializer_list<std::pair<const unsigned, u64>> regs) {
    HwCheck h;
    for (const auto& [r, v] : regs) h.gpr_in[r] = v;
    return h;
}
inline u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
inline s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }

inline const Case& by_name(const Case* cases, std::size_t n, const char* name) {
    for (std::size_t i = 0; i < n; ++i)
        if (std::string(cases[i].name) == name) return cases[i];
    FAIL("no case " << name);
    return cases[0];
}

// The random sweep every slice file starts with: `seeds` random worlds per function, on a fresh stand-in world with
// recorders for the callees the bodies reach (`setup`).
inline void random_sweep(Machine& m, const Case* cases, std::size_t n, u32 world, u32 world_size, u32 seeds_default,
                         const Setup& setup, bool bounded = false) {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : seeds_default;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (std::size_t i = 0; i < n; ++i) {
        const Case& c = cases[i];
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(m, world, world_size, rng);
            Args args{hgp::random_arg(rng, world, world_size), hgp::random_arg(rng, world, world_size),
                      hgp::random_arg(rng, world, world_size), hgp::random_arg(rng, world, world_size)};
            // bounded: wide values cut to 12 bits (counts and cluster numbers the card layer would loop over for hours)
            if (bounded)
                for (u64& a : args)
                    if (a < world || a >= world + world_size) a &= 0xFFF;
            stops += pair(m, c, args, seed, c.name, setup).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// --- the memory card --------------------------------------------------------------------------------------------
constexpr u32 kRawPage = 528;  // 512 data bytes + 16 ECC bytes per page in the image
constexpr u32 kMaxPages = 4096; // pages one stand-in request moves at most (the library asks for 128 at a time)
constexpr u32 kCoreTable = 0x985508u;  // libmc2 core: 2 sockets x 36 bytes (+8 page length, +12 ECC length, ...)
constexpr u32 kCoreStride = 36;
// The core-layer entry points the card stand-ins serve.
constexpr u32 kReadPage2 = 0x51B708u, kWritePage = 0x51B8F0u, kReadPageFast = 0x51BD10u, kWritePageFast = 0x51BF40u;
constexpr u32 kBlockErase = 0x51BBD8u, kReadClock = 0x51B5F0u, kGetConnection = 0x51C0C0u;
constexpr u32 kCheckNewCard = 0x51B1B0u, kClearNewCardFlag = 0x51B2C0u, kAuthentication = 0x51B3B0u;
constexpr u32 kWriteBack = 0x51B4A0u, kGetCardSpec = 0x51AFD8u;

struct Card {
    std::vector<u8> img;
    u32 pages_per_block = 16;
    std::vector<std::tuple<char, u32, u32>> ops;  // 'r' / 'w' / 'e', page, count: the requests in order
    u64 clock = 0x0007E70A0C0F1E00ull;            // the BCD-free clock record the stand-in returns (sec / min / hour / day...)
    u32 pages() const { return static_cast<u32>(img.size() / kRawPage); }
    bool operator==(const Card& o) const { return img == o.img && ops == o.ops; }
};
inline std::vector<u8> read_file(const std::string& path) {
    std::vector<u8> v;
    if (std::FILE* f = std::fopen(path.c_str(), "rb")) {
        std::fseek(f, 0, SEEK_END);
        const long n = std::ftell(f);
        std::fseek(f, 0, SEEK_SET);
        v.resize(static_cast<std::size_t>(n > 0 ? n : 0));
        if (!v.empty() && std::fread(v.data(), 1, v.size(), f) != v.size()) v.clear();
        std::fclose(f);
    }
    return v;
}
// A route card from the main tree (extracted/_ours/cards beside the ELF's tree); empty when absent.
inline std::vector<u8> route_card(const char* name) {
    std::string root = extracted_root();
    for (const std::string& p : {root + "/_ours/cards/" + name, root + "\\_ours\\cards\\" + name}) {
        std::vector<u8> v = read_file(p);
        if (v.size() == 8650752u) return v;
    }
    return {};
}

// Installs the core-layer stand-ins on `w`, serving `card` (owned by the world's lambdas). `connected` is what
// GetConnection answers; `new_card` what CheckNewCard answers.
inline void install_card(StandInWorld& w, std::shared_ptr<Card> card, u64 connected = 1, u64 new_card = 0) {
    auto page_len = [](EEContext& ctx, u32 port) { return gu32(ctx, kCoreTable + kCoreStride * port + 8); };
    auto read = [card, page_len](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 port = static_cast<u32>(c.args[0]) & 1, buf = static_cast<u32>(c.args[1]);
        const u32 page = static_cast<u32>(c.args[2]), n = static_cast<u32>(c.args[3]);
        const u32 len = page_len(ctx, port);
        card->ops.emplace_back('r', page, n);
        for (u32 i = 0; i < n && i < kMaxPages && len <= 512; ++i) {  // (a random world may ask for billions)
            const std::size_t off = static_cast<std::size_t>(page + i) * kRawPage;
            u8* dst = gptr(ctx, buf + i * len);
            if (off + len <= card->img.size()) std::memcpy(dst, card->img.data() + off, len);
            else std::memset(dst, 0xFF, len);
        }
        c.v0 = n;
    };
    auto write = [card, page_len](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 port = static_cast<u32>(c.args[0]) & 1, buf = static_cast<u32>(c.args[1]);
        const u32 page = static_cast<u32>(c.args[2]), n = static_cast<u32>(c.args[3]);
        const u32 len = page_len(ctx, port);
        card->ops.emplace_back('w', page, n);
        for (u32 i = 0; i < n && i < kMaxPages && len <= 512; ++i) {
            const std::size_t off = static_cast<std::size_t>(page + i) * kRawPage;
            if (off + len <= card->img.size()) std::memcpy(card->img.data() + off, gptr(ctx, buf + i * len), len);
        }
        c.v0 = n;
    };
    w.si.install(kReadPage2, "_sceMcCoreReadPage2", read);
    w.si.install(kReadPageFast, "_sceMcCoreReadPageFast", read);
    w.si.install(kWritePage, "_sceMcCoreWritePage", write);
    w.si.install(kWritePageFast, "_sceMcCoreWritePageFast", write);
    w.si.install(kBlockErase, "_sceMcCoreBlockErase", [card](EEContext&, StandIns&, StandInCall& c) {
        const u32 block = static_cast<u32>(c.args[1]);
        card->ops.emplace_back('e', block, 1);
        for (u32 p = 0; p < card->pages_per_block; ++p) {
            const std::size_t off = static_cast<std::size_t>(block * card->pages_per_block + p) * kRawPage;
            if (off + kRawPage <= card->img.size()) std::memset(card->img.data() + off, 0xFF, kRawPage);
        }
        c.v0 = 1;
    });
    w.si.install(kReadClock, "_sceMcCoreReadClock", [card](EEContext& ctx, StandIns&, StandInCall& c) {
        std::memcpy(gptr(ctx, static_cast<u32>(c.args[1])), &card->clock, 8);
        c.v0 = 1;
    });
    w.si.install_recorder(kGetConnection, "_sceMcCoreGetConnection", connected);
    w.si.install_recorder(kCheckNewCard, "_sceMcCoreCheckNewCard", new_card);
    w.si.install_recorder(kClearNewCardFlag, "_sceMcCoreClearNewCardFlag", 1);
    w.si.install_recorder(kAuthentication, "_sceMcCoreAuthentication", 1);
    w.si.install_recorder(kWriteBack, "_sceMcCoreWriteBack", 1);
    w.si.install_recorder(kGetCardSpec, "_sceMcCoreGetCardSpec", 1);
}

}  // namespace p3fes::game_test::libs1
