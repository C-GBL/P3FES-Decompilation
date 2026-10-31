// Modernize layer 3, steps 2-3: the native SK stack (runtime/native/sound/sk, the six SK modules as the C++
// tools/ours/modernize/skgen.py made) against its oracle, the same modules interpreted by the IOP HLE (IopKernel on
// the R3000 interpreter). Both get the same requests at the same virtual instants over their own IOP RAM and libsd
// model, at the Pcsx2 placement the game uses; every reply, every libsd event (KON / KOFF / core writes, with its
// instant) and the modules' memory at the end must be identical. Needs the user's extracted/disc/LIB31 and
// extracted/DATA/SOUND/SPU (P3FES_EXTRACTED overrides); skipped with a message when absent.
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "doctest.h"
#include "iop_kernel_hle.h"
#include "libsd_hle.h"
#include "sk_gen.h"
#include "sk_host.h"
#include "srv_sdr.h"

namespace {

using namespace p3fes;
using namespace p3fes::hle::sif;
using namespace p3fes::hle::sif::iop;
namespace nsk = p3fes::native::sound::sk;

std::filesystem::path extracted_dir() {
    if (const char* env = std::getenv("P3FES_EXTRACTED"); env && *env) return env;
    return P3FES_EXTRACTED_DIR;
}

std::optional<std::vector<u8>> read_file(const std::filesystem::path& p) {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    std::ifstream f(p, std::ios::binary);
    std::vector<u8> d(static_cast<std::size_t>(std::filesystem::file_size(p, ec)));
    if (!d.empty() && !f.read(reinterpret_cast<char*>(d.data()), static_cast<std::streamsize>(d.size()))) return std::nullopt;
    return d;
}
std::optional<std::vector<u8>> lib31(std::string_view name) { return read_file(extracted_dir() / "disc" / "LIB31" / std::string(name)); }

// One libsd event, as the --sound-log lines carry it.
struct Event {
    u64 at = 0;
    u32 kind = 0;  // 1 KON, 2 KOFF, 3 core write
    std::array<u32, 8> args{};
    bool operator==(const Event&) const = default;
};
std::string str(const Event& e) {
    std::ostringstream o;
    o << e.at << " " << e.kind << " |";
    for (u32 a : e.args) o << " " << std::hex << a;
    return o.str();
}

void hook(LibsdHle& sd, std::vector<Event>& out, const u64& now) {
    sd.on_key_on = [&out, &now](const audio::Spu2KeyOn& k) {
        out.push_back({now, 1, {k.core, k.voice, k.ssa, k.lsax, k.pitch, k.adsr1, k.adsr2, (static_cast<u32>(k.voll) << 16) | k.volr}});
    };
    sd.on_key_off = [&out, &now](u32 c, u32 v) { out.push_back({now, 2, {c, v}}); };
    sd.on_core_write = [&out, &now](u32 c, u32 kind, u32 code, u32 value, u32 old) { out.push_back({now, 3, {c, kind, code, value, old}}); };
}

constexpr const char* kFiles[] = {"SDRDRV.IRX", "MODHSYN.IRX", "MODMSIN.IRX", "MODSESQ.IRX", "SKSOUND.IRX", "SKHSYNTH.IRX", "SKHSYNTH.IRX", "SKSESQ.IRX"};
std::string_view args_of(const char* f) {
    return std::strcmp(f, "SKSESQ.IRX") == 0 ? std::string_view("maxtrack=16\0maxentry=16\0", 24) : std::string_view();
}

// The oracle: the interpreter's kernel with the faithful path's placement (SdrdrvServer::ensure_kernel).
struct Interp {
    detail::IopRam ram;
    LibsdHle sd;
    std::vector<Event> ev;
    u64 now = 0;
    IopKernel k{ram, sd};
    std::string error;
    Interp() {
        ram.set_heap(detail::kIopHeapBeginPcsx2, detail::kIopHeapEndPcsx2);
        std::vector<std::pair<u32, u32>> ranges(std::begin(detail::kKernelRangesPcsx2), std::end(detail::kKernelRangesPcsx2));
        k.set_alloc_ranges(ranges);
        for (const detail::SkModulePlacement& p : detail::kSkModulesPcsx2) k.set_fixed_base(p.file, p.base);
        k.set_time_hook([this](u64 t) { now = t; });
        hook(sd, ev, now);
    }
    void load(u64 t, const char* f) {
        if (std::strcmp(f, "MODMSIN.IRX") == 0) return;  // an HLE-only entry on the faithful path
        k.advance_to(t);
        const auto file = lib31(f);
        REQUIRE(file);
        REQUIRE_MESSAGE(k.load_module(*file, std::string("cdrom0:\\LIB31\\") + f + ";1", args_of(f), error), error);
    }
    std::vector<u8> call(u64 t, u32 fno, std::span<const u8> send) {
        k.advance_to(t);
        const RpcServerRecord* s = k.rpc_server(0x80000701u);
        REQUIRE(s);
        std::memcpy(ram.at(s->buf, static_cast<u32>(send.size())), send.data(), send.size());
        const auto r = k.rpc_dispatch(0x80000701u, fno, s->buf, static_cast<u32>(send.size()), error);
        REQUIRE_MESSAGE(r, error);
        std::vector<u8> reply(16);
        std::memcpy(reply.data(), ram.at(*r, 16), 16);
        return reply;
    }
};

// The native stack over its own RAM and libsd.
struct Native final : nsk::SkPort {
    detail::IopRam mem;
    LibsdHle sd;
    std::vector<Event> ev;
    u64 now = 0;
    std::vector<std::string> logs;
    nsk::NativeSk sk{*this};
    Native() {
        mem.set_heap(detail::kIopHeapBeginPcsx2, detail::kIopHeapEndPcsx2);
        hook(sd, ev, now);
        std::string err;
        REQUIRE_MESSAGE(sk.install(lib31, err), err);
    }
    u8* ram() override { return mem.at(0, detail::kIopRamSize); }
    u32 alloc_at(u32 addr, u32 size) override { return mem.alloc(size, 2, addr); }
    u32 alloc(u32 size, u32 mode) override { return mem.alloc(size, mode, 0); }
    u32 alloc_in(u32 lo, u32 hi, u32 size) override { return mem.alloc_in(lo, hi, size); }
    bool free(u32 addr) override { return mem.free(addr); }
    u32 libsd(u32 o, const u32 (&a)[5]) override { return libsd_call(sd, mem, o, a); }
    void at_time(u64 t) override { now = t; }
    void log(std::string_view l) override { logs.emplace_back(l); }
    void record(u32, std::span<const u8>, s32, u64) override {}
    void load(u64 t, const char* f) { sk.load_module(t, std::string("cdrom0:\\LIB31\\") + f + ";1", args_of(f)); }
    std::vector<u8> call(u64 t, u32 fno, std::span<const u8> send) {
        const auto r = sk.rpc(t, fno, send, 16);
        REQUIRE_MESSAGE(r, sk.stats().fault);
        return *r;
    }
};

std::vector<u8> sd_block(u32 a1, u32 a2) {  // sceSdRemote's 64-byte argument block (word 0 = its EE address)
    std::vector<u8> b(64, 0);
    const u32 w[3] = {0x0096E000u, a1, a2};
    std::memcpy(b.data(), w, sizeof w);
    return b;
}
std::vector<u8> sk_block(u32 module, u32 fn, std::initializer_list<u32> args) {  // the sceSkSs* 64-byte block
    std::vector<u8> b(64, 0);
    std::vector<u32> w{module, fn};
    w.insert(w.end(), args);
    std::memcpy(b.data(), w.data(), w.size() * 4);
    return b;
}

struct Pair {
    Interp f;
    Native n;
    u64 t = 1'000'000;
    int calls = 0;
    std::vector<u8> call(u32 fno, const std::vector<u8>& send) {
        const auto a = f.call(t, fno, send), b = n.call(t, fno, send);
        ++calls;
        CHECK_MESSAGE(a == b, "reply " << calls << " (fno " << std::hex << fno << ") differs");
        return a;
    }
    s32 sk(u32 module, u32 fn, std::initializer_list<u32> args) {
        const auto r = call(0x90F0u, sk_block(module, fn, args));
        s32 v;
        std::memcpy(&v, r.data(), 4);
        return v;
    }
    void dma(u32 addr, std::span<const u8> bytes) {
        std::memcpy(f.ram.at(addr, static_cast<u32>(bytes.size())), bytes.data(), bytes.size());
        std::memcpy(n.mem.at(addr, static_cast<u32>(bytes.size())), bytes.data(), bytes.size());
    }
    u32 alloc(u32 size) {
        const u32 a = f.ram.alloc(size, 0, 0), b = n.mem.alloc(size, 0, 0);
        REQUIRE(a == b);
        return a;
    }
    void advance(u64 dt) {
        t += dt;
        f.k.advance_to(t);
        n.sk.advance(t);
    }
};

bool have_data() {
    if (!nsk::kGenerated) return false;  // no LIB31 when the build was configured
    std::error_code ec;
    return std::filesystem::is_regular_file(extracted_dir() / "disc" / "LIB31" / "SKSOUND.IRX", ec) &&
           std::filesystem::is_regular_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.HD", ec) &&
           std::filesystem::is_regular_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "BSE.SQ", ec);
}

struct Bank {
    u32 hd = 0, hd_size = 0, sq = 0, sq_size = 0, spu = 0, bd_size = 0;
    s32 port = -1;
};

// H_Sndcom's bring-up and two bank loads (COMSE on port 0, BSE on port 1), as the game's sound log has them.
void bring_up(Pair& p, Bank (&banks)[2]) {
    for (const char* f : kFiles) {
        p.f.load(p.t, f);
        p.n.load(p.t, f);
        p.t += 120'000;
    }
    REQUIRE(p.f.k.fault().empty());
    REQUIRE_MESSAGE(p.n.sk.stats().fault.empty(), p.n.sk.stats().fault);
    p.call(0xE620u, sd_block(0x780000u, 0x780000u));
    for (const auto& [reg, val] : {std::pair<u32, u32>{0x980, 0x3FFF}, {0xA80, 0x3FFF}, {0x981, 0}, {0xA81, 0}}) p.call(0x8010u, sd_block(reg, val));
    CHECK(p.sk(0, 2, {0, 0x8F, 0}) == 0);
    CHECK(p.sk(0, 2, {3, 0x83, 0x105, 0x3C}) == 0);
    CHECK(p.sk(0, 2, {3, 0x84, 0x3C, 0x3C}) == 0);
    CHECK(p.sk(0, 2, {3, 0x82, 1, 0x40}) == 0);
    p.call(0x8010u, sd_block(0x800, 0xFC0));
    p.call(0x8010u, sd_block(0x801, 0xFCC));
    CHECK(p.sk(0, 2, {3, 0x80, 0x7F, 0x7F}) == 0);
    const char* names[2] = {"COMSE", "BSE"};
    u32 spu = 0x5010;
    const u32 tmp = p.alloc(4096);
    for (int b = 0; b < 2; ++b) {
        const auto dir = extracted_dir() / "DATA" / "SOUND" / "SPU";
        const auto hd = read_file(dir / (std::string(names[b]) + ".HD"));
        const auto bd = read_file(dir / (std::string(names[b]) + ".BD"));
        const auto sq = read_file(dir / (std::string(names[b]) + ".SQ"));
        REQUIRE((hd && bd && sq));
        Bank& k = banks[b];
        k.hd_size = static_cast<u32>(hd->size());
        k.sq_size = static_cast<u32>(sq->size());
        k.bd_size = static_cast<u32>(bd->size());
        k.hd = p.alloc(k.hd_size);
        k.sq = p.alloc(k.sq_size);
        p.dma(k.hd, *hd);
        p.dma(k.sq, *sq);
        k.spu = spu;
        for (std::size_t off = 0; off < bd->size(); off += 4096) {
            const u32 n = static_cast<u32>(std::min<std::size_t>(4096, bd->size() - off));
            p.dma(tmp, std::span<const u8>(bd->data() + off, n));
            REQUIRE(p.sk(0, 10, {1, tmp, spu, n}) == static_cast<s32>(n));
            spu += n;
            p.t += 3'000;
        }
        spu = (spu + 0xFFF) & ~0xFFFu;
        const s32 entry = p.sk(0x1000000, 0, {3, 0xFFFFFFFFu, k.hd, k.hd_size, k.spu, k.bd_size});
        REQUIRE(entry >= 0);
        k.port = p.sk(0x1000000, 0, {5, 0xFFFFFFFFu, static_cast<u32>(entry), 0});
        REQUIRE(k.port >= 0);
        const s32 seq = p.sk(0x4000000, 0, {0, 0xFFFFFFFFu, k.sq, k.sq_size});
        REQUIRE(seq >= 0);
        CHECK(p.sk(0x4000000, 0, {5, static_cast<u32>(k.port), static_cast<u32>(seq)}) == k.port);
    }
}

void compare_end(Pair& p) {
    // the libsd event streams, instant for instant
    const auto& a = p.f.ev;
    const auto& b = p.n.ev;
    std::size_t first = 0;
    while (first < a.size() && first < b.size() && a[first] == b[first]) ++first;
    CHECK_MESSAGE(a.size() == b.size(), "events " << a.size() << " interpreted, " << b.size() << " native");
    CHECK_MESSAGE(first == std::min(a.size(), b.size()),
                  "first differing event " << first << ": " << (first < a.size() ? str(a[first]) : "-") << " vs " << (first < b.size() ? str(b[first]) : "-"));
    // memory: the six modules' data and bss, then every block both IOP heaps hold (work areas, thread stacks, argv,
    // the banks) byte for byte -- the image blocks' text areas excepted (the interpreter holds the code there, the
    // native stack leaves them zero)
    std::size_t differ = 0;
    u32 first_addr = 0;
    // The game's second SKHSYNTH: the interpreter loads its image into a block it frees again (start result 1), the
    // native stack only takes and frees the same block -- what the interpreter left there (the module's bytes) is not
    // compared where a later block reuses it.
    u32 dup_lo = 0, dup_hi = 0;
    for (const LoadedIrx& m : p.f.k.modules())
        if (!m.resident) dup_lo = m.block, dup_hi = m.info.base + m.info.image_size;
    CHECK(dup_hi > dup_lo);
    std::size_t residue = 0;
    // and the RPC-return trampoline: the interpreter's host-call word, an address only for the native stack
    const u32 tramp = p.n.sk.rpc_return_address();
    auto cmp = [&](u32 lo, u32 hi) {
        for (u32 x = lo; x < hi; ++x)
            if (x >= tramp && x < tramp + 16u) {
                continue;
            } else if (x >= dup_lo && x < dup_hi) {
                residue += *p.f.ram.at(x, 1) != *p.n.mem.at(x, 1);
            } else if (*p.f.ram.at(x, 1) != *p.n.mem.at(x, 1)) {
                if (!differ) first_addr = x;
                ++differ;
            }
    };
    for (const nsk::ModuleImage& m : nsk::kModules) cmp(m.base + m.text, m.base + m.text + m.data + m.bss);
    CHECK_MESSAGE(p.f.ram.blocks() == p.n.mem.blocks(), "the heaps' block maps differ (" << p.f.ram.blocks().size() << " / " << p.n.mem.blocks().size() << " blocks)");
    for (const auto& [addr, size] : p.n.mem.blocks()) {
        bool image = false;
        for (const nsk::ModuleImage& m : nsk::kModules) image |= addr == m.base - 0x30u;
        if (!image) cmp(addr, addr + size);
    }
    CHECK_MESSAGE(differ == 0, differ << " bytes of module / block memory differ, first at " << first_addr);
    MESSAGE("the second SKHSYNTH's freed image block [" << dup_lo << ", " << dup_hi << "): " << residue << " bytes of its residue inside later blocks");    CHECK(p.f.k.fault().empty());
    CHECK_MESSAGE(p.n.sk.stats().fault.empty(), p.n.sk.stats().fault);
    MESSAGE(p.calls << " requests, " << a.size() << " libsd events, " << p.n.sk.stats().tick_runs << " ticks (interpreter " << p.f.k.timer_handler_runs()
                    << "), " << p.f.k.instructions() << " instructions interpreted");
}

}  // namespace

TEST_CASE("Native SK: the generated code matches the IRX files it was made from") {
    if (!have_data()) {
        MESSAGE("skipped: extracted/disc/LIB31 or extracted/DATA/SOUND/SPU not present");
        return;
    }
    detail::IopRam ram;
    struct Port final : nsk::SkPort {
        detail::IopRam* r;
        u8* ram() override { return r->at(0, detail::kIopRamSize); }
        u32 alloc_at(u32, u32) override { return 0; }
        u32 alloc(u32, u32) override { return 0; }
        u32 alloc_in(u32, u32, u32) override { return 0; }
        bool free(u32) override { return false; }
        u32 libsd(u32, const u32 (&)[5]) override { return 0; }
        void at_time(u64) override {}
        void log(std::string_view) override {}
        void record(u32, std::span<const u8>, s32, u64) override {}
    } port;
    port.r = &ram;
    nsk::NativeSk sk(port);
    std::string err;
    CHECK_MESSAGE(sk.install(lib31, err), err);
    // a module whose text is not the one generated from is refused
    nsk::NativeSk other(port);
    CHECK_FALSE(other.install([](std::string_view f) -> std::optional<std::vector<u8>> {
        auto d = lib31(f);
        if (d && f == "MODSESQ.IRX") (*d)[0x200] ^= 1u;  // one bit of its code
        return d;
    }, err));
    CHECK(err.find("MODSESQ.IRX") != std::string::npos);
    // every generated function is found by its address (call_address / the thread entries)
    for (const nsk::FnEntry& e : nsk::kFunctions) CHECK(nsk::function_at(e.addr) == e.fn);
    CHECK(nsk::function_at(0x12345678u) == nullptr);
}

TEST_CASE("Native SK vs the interpreter: bring-up, both banks, the menu SEs (replies, libsd events, memory)") {
    if (!have_data()) {
        MESSAGE("skipped: extracted/disc/LIB31 or extracted/DATA/SOUND/SPU not present");
        return;
    }
    Pair p;
    Bank banks[2];
    bring_up(p, banks);
    // the memory-card prompt's SEs, then a few seconds of ticks
    for (int i = 0; i < 4; ++i) {
        const s32 tr = p.sk(0x4000000, 2, {static_cast<u32>(banks[0].port), 0, 10, 0, static_cast<u32>(i & 1)});
        CHECK(tr >= 0);
        p.sk(0x4000000, 3, {static_cast<u32>(banks[0].port), 1, 10, static_cast<u32>(tr)});
        p.advance(30'000'000);  // ~100 ms
    }
    p.advance(600'000'000);
    compare_end(p);
}

TEST_CASE("Native SK vs the interpreter: a storm of plays, stops, status and volume on both ports at random instants") {
    if (!have_data()) {
        MESSAGE("skipped: extracted/disc/LIB31 or extracted/DATA/SOUND/SPU not present");
        return;
    }
    Pair p;
    Bank banks[2];
    bring_up(p, banks);
    u32 seed = 0x5EED1234u;
    auto rnd = [&seed](u32 n) {
        seed = seed * 1664525u + 1013904223u;
        return (seed >> 8) % n;
    };
    std::vector<std::pair<u32, s32>> tracks;
    for (int step = 0; step < 1500; ++step) {
        p.t += rnd(2'000'000);  // 0 .. 6.8 ms between requests (ticks land between and on them)
        const u32 op = rnd(10);
        const Bank& b = banks[rnd(2)];
        const u32 port = static_cast<u32>(b.port);
        if (op < 5) {
            const s32 tr = p.sk(0x4000000, 2, {port, rnd(4) == 0 ? 7u : 0u, 10, rnd(8), rnd(16)});
            if (tr >= 0) tracks.push_back({port, tr});
        } else if (op < 7 && !tracks.empty()) {
            const auto [pp, tr] = tracks[rnd(static_cast<u32>(tracks.size()))];
            p.sk(0x4000000, 3, {pp, 1, 10, static_cast<u32>(tr)});
            p.sk(0x4000000, 2, {pp, 2, 10, static_cast<u32>(tr)});
        } else if (op < 9) {
            p.sk(0, 2, {3, 0x80, rnd(128), rnd(128)});
        } else {
            p.sk(0x4000000, 3, {port, 1, 10, rnd(32)});
        }
        if (p.calls % 200 == 0) {
            REQUIRE_MESSAGE(p.n.sk.stats().fault.empty(), p.n.sk.stats().fault);
        }
    }
    p.advance(300'000'000);
    compare_end(p);
}
