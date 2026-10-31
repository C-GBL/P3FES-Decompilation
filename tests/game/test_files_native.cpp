// Modernize layer 1 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of the game's CD wrappers
// (game/src/hcdvd/hcdvd_native.cpp, game/include/p3fes/game/files_native.h) against a fake files service.
//   - dvCiReqRd's and dvCiCdSearchFile's native halves on a bare guest machine (they call no guest code);
//   - H_Cdvd_Update with the service installed: every queued request loads by path in one pump, with the faithful
//     buffer rule, the PAK terminator and the sCdvdCache registration; a missing file stops the walk;
//   - without the service the same bodies take the faithful path (the pair tests of test_sweep5a / test_sweep5c /
//     test_libs24 cover that byte for byte).
#include "pair_harness.h"
#include "stand_ins.h"

#include "p3fes/game/files_native.h"
#include "p3fes/game/hcdvd.h"

#include <cstring>
#include <optional>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using namespace p3fes::game_test;
namespace nf = p3fes::native::files;

namespace {

// A files service over host byte vectors. Bytes past a file's end read as 0xEE (the "disc's padding").
class FakeFiles final : public nf::FileService {
public:
    struct File {
        std::string key;
        std::vector<std::byte> bytes;
        u32 lsn = 0;
        bool outer = false;
    };
    std::vector<File> files;
    std::vector<std::string> finds;
    struct Read {
        u32 id;
        u64 offset, len;
        u32 dst;
    };
    std::vector<Read> reads;
    bool fail_reads = false;

    static std::string key(std::string_view p) {
        std::string k;
        for (char c : p) {
            if (c == '/') c = '\\';
            if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 32);
            if (c == '\\' && (k.empty() || k.back() == '\\')) continue;  // no leading or doubled separators
            k += c;
        }
        return k;
    }
    void add(std::string path, std::vector<std::byte> bytes, u32 lsn, bool outer = false) {
        files.push_back(File{key(path), std::move(bytes), lsn, outer});
    }
    nf::FileRef ref(std::size_t i) const { return nf::FileRef{static_cast<u32>(i + 1), files[i].bytes.size(), files[i].lsn}; }
    std::optional<nf::FileRef> find(std::string_view path) override {
        finds.emplace_back(path);
        for (std::size_t i = 0; i < files.size(); ++i)
            if (files[i].key == key(path)) return ref(i);
        return std::nullopt;
    }
    std::optional<nf::OuterFile> search(std::string_view cd_path) override {
        std::string k = key(cd_path);
        if (const auto semi = k.find(';'); semi != std::string::npos) k.resize(semi);
        for (std::size_t i = 0; i < files.size(); ++i)
            if (files[i].outer && files[i].key == k) return nf::OuterFile{ref(i), files[i].key + ";1", {108, 1, 4, 14, 55, 42, 36}};
        return std::nullopt;
    }
    std::optional<nf::FileRef> outer_at(u32 lsn) override {
        for (std::size_t i = 0; i < files.size(); ++i)
            if (files[i].outer && files[i].lsn == lsn) return ref(i);
        return std::nullopt;
    }
    bool read(const nf::FileRef& f, u64 offset, std::span<std::byte> dst, u32 guest_dst) override {
        if (fail_reads || f.id == 0 || f.id > files.size()) return false;
        const auto& b = files[f.id - 1].bytes;
        for (std::size_t i = 0; i < dst.size(); ++i) dst[i] = offset + i < b.size() ? b[offset + i] : std::byte{0xEE};
        reads.push_back(Read{f.id, offset, dst.size(), guest_dst});
        return true;
    }
};

std::vector<std::byte> bytes_of(std::size_t n, u32 seed) {
    std::vector<std::byte> v(n);
    u32 x = seed * 2654435761u + 1;
    for (auto& b : v) {
        x = x * 1664525u + 1013904223u;
        b = static_cast<std::byte>(x >> 24);
    }
    return v;
}

u32 ld32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + va, 4);
    return v;
}
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

// The service is installed for one scope only.
struct ServiceScope {
    explicit ServiceScope(nf::FileService* s) { nf::g_service = s; }
    ~ServiceScope() { nf::g_service = nullptr; }
};

}  // namespace

TEST_CASE("game(files_native): dvCi's native read -- the faithful clamp, the bytes at once, a complete handle, errors") {
    Machine m;
    m.ctx.memory = &m.mem;
    FakeFiles fs;
    const std::vector<std::byte> cvm = bytes_of(12 * 2048, 7);
    fs.add("DATA.CVM", cvm, 584363, true);
    constexpr u32 h = 0x7A1DF0u, buf = 0x01800000u;
    std::memset(m.at(h), 0x5A, 72);
    st32(m, h + 8, 10);       // size in sectors
    st32(m, h + 12, 8);       // position
    st32(m, h + 32, 584363);  // the sceCdlFILE's LSN
    m.at(0x7A2A70)[0] = 1, m.at(0x7A2A70)[1] = 2, m.at(0x7A2A70)[2] = 3;
    std::memset(m.at(buf), 0, 5 * 2048);

    CHECK(game::dvci_native_read(m.ctx, fs, h, 5, buf) == 2);  // clamped to the file end
    CHECK(ld32(m, h + 16) == 2);
    CHECK(ld32(m, h + 20) == 2);
    CHECK(ld32(m, h + 12) == 10);
    CHECK(ld32(m, h + 24) == buf);
    CHECK(ld32(m, h + 28) == 0);  // no SRD
    CHECK(m.at(h)[2] == 1);       // complete (dvCiExecHndl's state for a finished read)
    CHECK(m.at(h)[68] == 1);
    CHECK(m.at(h)[69] == 2);
    CHECK(m.at(h)[70] == 3);
    CHECK(std::memcmp(m.at(buf), cvm.data() + 8 * 2048, 2 * 2048) == 0);
    CHECK(m.at(buf)[2 * 2048] == 0);  // nothing past the clamp
    REQUIRE(fs.reads.size() == 1);
    CHECK(fs.reads[0].offset == 8u * 2048);
    CHECK(fs.reads[0].dst == buf);

    CHECK(game::dvci_native_read(m.ctx, fs, h, 4, buf) == 0);  // at the end: nothing more, still complete
    CHECK(m.at(h)[2] == 1);
    CHECK(fs.reads.size() == 1);

    st32(m, h + 12, 0);
    fs.fail_reads = true;
    CHECK(game::dvci_native_read(m.ctx, fs, h, 1, buf) == 1);
    CHECK(m.at(h)[2] == 3);  // dvCiExecHndl's error state
    fs.fail_reads = false;
    st32(m, h + 32, 1234);  // a handle on no known file
    CHECK(game::dvci_native_read(m.ctx, fs, h, 1, buf) == 1);
    CHECK(m.at(h)[2] == 3);
}

TEST_CASE("game(files_native): dvCi's native search -- the sceCdlFILE as cdvdfsv writes it") {
    Machine m;
    m.ctx.memory = &m.mem;
    FakeFiles fs;
    fs.add("DATA.CVM", bytes_of(4096, 1), 584363, true);
    fs.add("DATA.CVM:\\A.BIN", bytes_of(100, 2), 600000);
    constexpr u32 fp = 0x01800000u, name = 0x01800100u;
    std::memset(m.at(fp), 0x77, 36);
    m.put(name, "\\DATA.CVM;1");
    CHECK(game::dvci_native_search(m.ctx, fs, fp, name) == 1);
    CHECK(ld32(m, fp + 0) == 584363);
    CHECK(ld32(m, fp + 4) == 4096);
    CHECK(m.str(fp + 8) == "DATA.CVM;1");
    const u8 date[8] = {0, 42, 55, 14, 4, 1, 2008 & 0xFF, 2008 >> 8};
    CHECK(std::memcmp(m.at(fp + 24), date, 8) == 0);
    CHECK(ld32(m, fp + 32) == 0);
    std::memset(m.at(fp), 0x77, 36);
    m.put(name, "\\NONE.CVM;1");
    CHECK(game::dvci_native_search(m.ctx, fs, fp, name) == 0);
    CHECK(m.at(fp)[0] == 0x77);  // untouched
}

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Update_00100980(EEContext&);
}  // namespace p3fes::recomp_gen

namespace {

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

constexpr u32 kSetRofsDir = 0x101520u;
constexpr u32 kListFirst = game::kHCdvdListHead + 4;

// A state-0 request node with the retail layout (hcdvd.h), linked after `prev`.
u32 add_node(Machine& m, GuestHeap& heap, u32 prev, const std::string& vol_file, const std::string& dir, bool archive) {
    const u32 n = heap.alloc(868);
    std::memset(m.at(n), 0, 868);
    st32(m, n + 0, prev);
    st32(m, prev + 4, n);
    m.put(n + 16, dir + vol_file.substr(vol_file.find(':') + 1));
    st32(m, n + 336, archive ? 1 : 0);
    m.put(n + 344, vol_file);
    m.put(n + 600, dir);
    const s16 one = 1;
    std::memcpy(m.at(n + 858), &one, 2);
    return n;
}

// A one-entry name-first PAK: 252-byte name + u32 size, the data at +256 (H_Cdvd_AddFile's rule).
std::vector<std::byte> one_entry_pak(const std::string& name, const std::vector<std::byte>& data) {
    std::vector<std::byte> p(256 + data.size());
    std::memcpy(p.data(), name.data(), name.size());
    const u32 n = static_cast<u32>(data.size());
    std::memcpy(p.data() + 252, &n, 4);
    std::memcpy(p.data() + 256, data.data(), data.size());
    return p;
}

}  // namespace

TEST_CASE("game(files_native): H_Cdvd_Update with --native files loads every queued request by path in one pump") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StandInWorld w;
    w.heap.install_rw(w.si);
    write_rw_slots(m);
    w.si.install_recorder(kSetRofsDir, "H_Cdvd_SetRofsDir");
    StandInsScope scope(w.si);
    std::memset(m.at(game::kHCdvdCache), 0, game::kHCdvdCacheSlots * sizeof(game::HCdvdCacheEntry));
    st32(m, kListFirst, 0);

    FakeFiles fs;
    const std::vector<std::byte> plain = bytes_of(5000, 3);
    const std::vector<std::byte> pak = one_entry_pak("X.BIN", bytes_of(10, 4));
    fs.add("DATA.CVM:\\FIELD\\A.BIN", plain, 700000);
    fs.add("BTL.CVM:\\BATTLE\\P.PAK", pak, 800);
    const u32 n1 = add_node(m, w.heap, game::kHCdvdListHead, "VOL:A.BIN", "VOL:\\FIELD\\", false);
    const u32 n2 = add_node(m, w.heap, n1, "BTL:P.PAK", "VOL:\\BATTLE\\", true);
    const std::size_t blocks0 = w.heap.live().size();
    {
        ServiceScope svc(&fs);
        run(m, &recomp_gen::fn_H_Cdvd_Update_00100980, {}, 1);
    }
    // Both in one call, in list order, each through H_Cdvd_SetRofsDir first (the faithful prologue of state 0).
    CHECK(w.si.calls_to(kSetRofsDir) == 2);
    REQUIRE(fs.reads.size() == 2);
    CHECK(fs.finds.size() == 2);
    for (const u32 n : {n1, n2}) {
        INFO("node 0x" << std::hex << n);
        CHECK(ld32(m, n + game::kHCdvdNodeState) == game::kHCdvdStateLoaded);
        CHECK(ld32(m, n + 340) == 0);  // no ADXF handle
        const u32 data = ld32(m, n + 272), raw = ld32(m, n + 276);
        CHECK(data % 64 == 0);
        CHECK(data >= raw);
        CHECK(data - raw < 64);
    }
    CHECK(ld32(m, n1 + 292) == 5000);
    CHECK(ld32(m, n1 + 280) == 5000);
    CHECK(ld32(m, n2 + 292) == pak.size());
    // Buffers: (sectors << 11) + 64, archives + 320 (the faithful rule); every sector read, padding included.
    CHECK(w.heap.live().size() == blocks0 + 2);
    CHECK(w.heap.size_of(ld32(m, n1 + 276)) >= (3u << 11) + 64);
    CHECK(w.heap.size_of(ld32(m, n2 + 276)) >= (1u << 11) + 320);
    CHECK(fs.reads[0].len == 3u * 2048);
    CHECK(fs.reads[0].dst == ld32(m, n1 + 272));
    const u32 d1 = ld32(m, n1 + 272), d2 = ld32(m, n2 + 272);
    CHECK(std::memcmp(m.at(d1), plain.data(), plain.size()) == 0);
    CHECK(m.at(d1)[5000] == 0xEE);  // the service's bytes past the end, as a sector read delivers the disc's
    CHECK(std::memcmp(m.at(d2), pak.data(), pak.size()) == 0);
    std::vector<u8> zeros(256, 0);
    CHECK(std::memcmp(m.at(d2 + static_cast<u32>(pak.size())), zeros.data(), 256) == 0);  // the PAK terminator
    // sCdvdCache: the plain file once, the PAK's entry at its data (+256).
    bool plain_slot = false, entry_slot = false;
    for (u32 i = 0; i < game::kHCdvdCacheSlots; ++i) {
        const u32 slot = game::kHCdvdCache + i * static_cast<u32>(sizeof(game::HCdvdCacheEntry));
        if (!ld32(m, slot)) continue;
        const u32 d = ld32(m, slot + offsetof(game::HCdvdCacheEntry, data));
        plain_slot |= d == d1;
        entry_slot |= d == d2 + 256;
    }
    CHECK(plain_slot);
    CHECK(entry_slot);
}

TEST_CASE("game(files_native): H_Cdvd_Update with --native files stops at a file the service does not have") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    StandInWorld w;
    w.heap.install_rw(w.si);
    write_rw_slots(m);
    w.si.install_recorder(kSetRofsDir, "H_Cdvd_SetRofsDir");
    StandInsScope scope(w.si);
    std::memset(m.at(game::kHCdvdCache), 0, game::kHCdvdCacheSlots * sizeof(game::HCdvdCacheEntry));
    st32(m, kListFirst, 0);
    FakeFiles fs;
    fs.add("DATA.CVM:\\FIELD\\B.BIN", bytes_of(100, 5), 700100);
    const u32 n1 = add_node(m, w.heap, game::kHCdvdListHead, "VOL:NONE.BIN", "VOL:\\FIELD\\", false);
    const u32 n2 = add_node(m, w.heap, n1, "VOL:B.BIN", "VOL:\\FIELD\\", false);
    const std::size_t blocks0 = w.heap.live().size();
    {
        ServiceScope svc(&fs);
        run(m, &recomp_gen::fn_H_Cdvd_Update_00100980, {}, 2);
    }
    CHECK(ld32(m, n1 + game::kHCdvdNodeState) == 0);  // stays, as a failed ADXF_Open (retried next frame)
    CHECK(ld32(m, n2 + game::kHCdvdNodeState) == 0);  // FIFO: not reached
    CHECK(fs.reads.empty());
    CHECK(w.heap.live().size() == blocks0);
    CHECK(w.si.calls_to(kSetRofsDir) == 1);
}

#endif  // P3FES_GAME_HAVE_GENERATED
