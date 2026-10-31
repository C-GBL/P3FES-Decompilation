// ModsOverlay (ADR-0016): the virtual disc over a synthetic ISO with a CVM (replaced / grown / shrunk files,
// directory records, untouched sectors), path rules, mod.json, load order, refusals, reload, the ROFS table patch,
// and an end-to-end read of a modified real data file through CdvdHle and the ELF's own ROFS tables (skipped
// without input/persona3fes.iso). Test mods are written to a temporary folder; no game data is committed.
#include <doctest.h>

#include <windows.h>

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "hle_fixtures.h"
#include "p3fes/hle/cdvd.h"
#include "p3fes/hle/mods_overlay.h"
#include "p3fes/hle/read_log.h"
#include "native_files.h"

using namespace p3fes;
using namespace p3fes::hle;

namespace {

constexpr u32 S = kSectorSize;

std::vector<std::byte> pattern(std::size_t n, u32 seed) {
    std::vector<std::byte> v(n);
    for (std::size_t i = 0; i < n; ++i) v[i] = static_cast<std::byte>((seed * 131u + i * 7u + (i >> 9)) & 0xFF);
    return v;
}

void put_be32(std::vector<std::byte>& b, std::size_t off, u32 v) {
    for (int i = 0; i < 4; ++i) b[off + i] = static_cast<std::byte>((v >> (8 * (3 - i))) & 0xFF);
}
void put_be64(std::vector<std::byte>& b, std::size_t off, u64 v) {
    for (int i = 0; i < 8; ++i) b[off + i] = static_cast<std::byte>((v >> (8 * (7 - i))) & 0xFF);
}
void put_le32(std::vector<std::byte>& b, std::size_t off, u32 v) {
    for (int i = 0; i < 4; ++i) b[off + i] = static_cast<std::byte>((v >> (8 * i)) & 0xFF);
}
u32 le32(const std::byte* p) {
    return std::to_integer<u32>(p[0]) | (std::to_integer<u32>(p[1]) << 8) | (std::to_integer<u32>(p[2]) << 16) |
           (std::to_integer<u32>(p[3]) << 24);
}
u32 be32(const std::byte* p) {
    return (std::to_integer<u32>(p[0]) << 24) | (std::to_integer<u32>(p[1]) << 16) | (std::to_integer<u32>(p[2]) << 8) |
           std::to_integer<u32>(p[3]);
}
u64 be64(const std::byte* p) {
    u64 v = 0;
    for (int i = 0; i < 8; ++i) v = (v << 8) | std::to_integer<u64>(p[i]);
    return v;
}

// ---- a tiny ISO9660 builder ---------------------------------------------------------------------
struct Node {
    std::string name;
    bool dir = false;
    std::vector<std::byte> data;
    std::vector<Node> kids;
    u32 lsn = 0, size = 0;
    const Node* kid(std::string_view n) const {
        for (const Node& k : kids)
            if (k.name == n) return &k;
        return nullptr;
    }
};

void assign_dirs(Node& d, u32& next) {
    d.lsn = next++;
    d.size = S;
    for (Node& k : d.kids)
        if (k.dir) assign_dirs(k, next);
}
void assign_files(Node& d, u32& next) {
    for (Node& k : d.kids) {
        if (k.dir) {
            assign_files(k, next);
        } else {
            k.lsn = next;
            k.size = static_cast<u32>(k.data.size());
            next += std::max<u32>(1, (k.size + S - 1) / S);
        }
    }
}
void write_dirs(std::vector<std::byte>& img, const Node& d, const Node& parent) {
    std::size_t r = static_cast<std::size_t>(d.lsn) * S;
    r = test::put_dir_record(img, r, std::string_view("\0", 1), d.lsn, S, 0x02);
    r = test::put_dir_record(img, r, std::string_view("\1", 1), parent.lsn, S, 0x02);
    for (const Node& k : d.kids) {
        const std::string id = k.dir ? k.name : k.name + ";1";
        r = test::put_dir_record(img, r, id, k.lsn, k.size, k.dir ? 0x02 : 0x00);
        REQUIRE(r < static_cast<std::size_t>(d.lsn + 1) * S);
    }
    for (const Node& k : d.kids)
        if (k.dir) write_dirs(img, k, d);
}
void write_files(std::vector<std::byte>& img, const Node& d) {
    for (const Node& k : d.kids) {
        if (k.dir) write_files(img, k);
        else if (!k.data.empty()) std::memcpy(img.data() + static_cast<std::size_t>(k.lsn) * S, k.data.data(), k.data.size());
    }
}
// Directories from LSN 18 (one sector each), then the files; the PVD at 16, the terminator at 17.
std::vector<std::byte> build_iso(Node& root) {
    u32 next = 18;
    assign_dirs(root, next);
    assign_files(root, next);
    const u32 total = next + 4;
    std::vector<std::byte> img(static_cast<std::size_t>(total) * S);
    const std::size_t p = 16 * S;
    img[p] = std::byte{1};
    std::memcpy(img.data() + p + 1, "CD001", 5);
    img[p + 6] = std::byte{1};
    test::put_u32_both(img, p + 80, total);
    test::put_u16_both(img, p + 120, 1);
    test::put_u16_both(img, p + 124, 1);
    test::put_u16_both(img, p + 128, static_cast<u16>(S));
    test::put_dir_record(img, p + 156, std::string_view("\0", 1), root.lsn, S, 0x02);
    img[17 * S] = std::byte{255};
    std::memcpy(img.data() + 17 * S + 1, "CD001", 5);
    img[17 * S + 6] = std::byte{1};
    write_dirs(img, root, root);
    write_files(img, root);
    return img;
}

// CVMH + ZONE + one spare header sector (data offset 3, as on the user's disc) + the inner ISO.
std::vector<std::byte> build_cvm(const std::vector<std::byte>& inner) {
    std::vector<std::byte> c(3 * S + inner.size());
    const u64 size = c.size();
    std::memcpy(c.data(), "CVMH", 4);
    put_be64(c, 0x1C, size);
    put_be32(c, 136, 3);
    std::memcpy(c.data() + S, "ZONE", 4);
    put_be64(c, S + 0x04, size - 0x80C);
    put_be64(c, S + 0x30, size - 3 * S);
    std::memcpy(c.data() + 3 * S, inner.data(), inner.size());
    return c;
}

// ROFS "#DirLst#" tables (docs/ANALYSIS/11 §1) for every directory of `root`, plus a decoy with the root's LBA
// whose listing differs (another CVM's directory at the same LBA, like BTL's root vs DATA's).
std::vector<std::byte> build_tables(const Node& root, std::map<std::string, std::size_t>& entry_at) {
    std::vector<std::byte> b(64);
    std::memcpy(b.data() + 20, "#DirLst#", 8);  // a stray marker that is no table
    auto table = [&](const Node& d, const Node& parent, const std::string& prefix, bool decoy) {
        while (b.size() % 16) b.push_back(std::byte{0});
        const std::size_t h = b.size();
        const u32 count = static_cast<u32>(2 + d.kids.size() + (decoy ? 1 : 0));
        b.resize(h + 24 + 48 * count);
        put_le32(b, h, count);
        put_le32(b, h + 4, count);
        put_le32(b, h + 8, d.lsn);
        std::memcpy(b.data() + h + 12, "#DirLst#", 8);
        auto ent = [&](u32 k, u32 size, u32 lba, u8 flags, std::string_view name) {
            const std::size_t e = h + 24 + 48 * k;
            put_le32(b, e, size);
            put_le32(b, e + 8, lba);
            b[e + 12] = std::byte{flags};
            std::memcpy(b.data() + e + 14, name.data(), name.size());
            if (!decoy) entry_at[prefix + std::string(name)] = e;
        };
        ent(0, d.size, d.lsn, 2, ".");
        ent(1, parent.size, parent.lsn, 2, "..");
        u32 k = 2;
        for (const Node& c : d.kids) ent(k++, c.size, c.lsn, c.dir ? 2 : 0, c.name);
        if (decoy) ent(k, 1, 1, 0, "ZZZ.BIN");
    };
    table(root, root, "\\", false);
    for (const Node& c : root.kids)
        if (c.dir) table(c, root, "\\" + c.name + "\\", false);
    table(root, root, "decoy", true);
    return b;
}

// The synthetic disc: SYSTEM.CNF, a fake SLUS_216.21, DATA.CVM {A.BIN, GROW.BIN, NOEXT., SUB/{SHRINK.BIN, KEEP.BIN}},
// LIB31/{TEST.IRX}.
struct Synth {
    Node inner, outer;
    std::vector<std::byte> iso, cvm, tables;
    std::map<std::string, std::size_t> entry_at;  // "\SUB\KEEP.BIN" -> offset in `tables`
    std::unique_ptr<test::TempFile> file;
    const Node& in(std::string_view a, std::string_view b = {}) const {
        const Node* n = inner.kid(a);
        REQUIRE(n);
        if (!b.empty()) n = n->kid(b);
        REQUIRE(n);
        return *n;
    }
    const Node& data_cvm() const { return *outer.kid("DATA.CVM"); }
};

Node file_node(std::string name, std::vector<std::byte> data) {
    Node n;
    n.name = std::move(name);
    n.data = std::move(data);
    return n;
}
Node dir_node(std::string name) {
    Node n;
    n.name = std::move(name);
    n.dir = true;
    return n;
}

Synth make_synth() {
    Synth s;
    s.inner.dir = true;
    s.inner.kids.push_back(file_node("A.BIN", pattern(5000, 1)));
    s.inner.kids.push_back(file_node("GROW.BIN", pattern(3000, 2)));
    s.inner.kids.push_back(file_node("NOEXT.", pattern(10, 6)));
    Node sub = dir_node("SUB");
    sub.kids.push_back(file_node("SHRINK.BIN", pattern(9000, 3)));
    sub.kids.push_back(file_node("KEEP.BIN", pattern(100, 4)));
    s.inner.kids.push_back(std::move(sub));
    auto inner_iso = build_iso(s.inner);
    s.cvm = build_cvm(inner_iso);
    const std::string cnf = "BOOT2 = cdrom0:\\SLUS_216.21;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n";
    s.outer.dir = true;
    s.outer.kids.push_back(file_node("DATA.CVM", s.cvm));
    Node lib = dir_node("LIB31");
    lib.kids.push_back(file_node("TEST.IRX", pattern(700, 5)));
    s.outer.kids.push_back(std::move(lib));
    s.outer.kids.push_back(file_node("SLUS_216.21", pattern(3000, 7)));
    s.outer.kids.push_back(file_node("SYSTEM.CNF", std::vector<std::byte>(reinterpret_cast<const std::byte*>(cnf.data()),
                                                                          reinterpret_cast<const std::byte*>(cnf.data()) + cnf.size())));
    s.iso = build_iso(s.outer);
    s.tables = build_tables(s.inner, s.entry_at);
    s.file = std::make_unique<test::TempFile>(s.iso);
    return s;
}

// A temporary folder tree, removed on destruction.
class TempDir {
public:
    TempDir() {
        static unsigned counter = 0;
        path_ = std::filesystem::temp_directory_path() /
                ("p3fes_mods_" + std::to_string(::GetCurrentProcessId()) + "_" + std::to_string(++counter));
        std::filesystem::remove_all(path_);
        std::filesystem::create_directories(path_);
    }
    ~TempDir() {
        std::error_code ec;
        std::filesystem::remove_all(path_, ec);
    }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;
    const std::filesystem::path& path() const { return path_; }
    std::filesystem::path write(const std::filesystem::path& rel, const std::vector<std::byte>& bytes) const {
        const auto p = path_ / rel;
        std::filesystem::create_directories(p.parent_path());
        std::ofstream f(p, std::ios::binary | std::ios::trunc);
        f.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        return p;
    }
    std::filesystem::path write(const std::filesystem::path& rel, std::string_view text) const {
        return write(rel, std::vector<std::byte>(reinterpret_cast<const std::byte*>(text.data()),
                                                 reinterpret_cast<const std::byte*>(text.data()) + text.size()));
    }

private:
    std::filesystem::path path_;
};

struct Logged {
    std::vector<std::string> lines;
    std::function<void(std::string_view)> sink() {
        return [this](std::string_view s) { lines.emplace_back(s); };
    }
    bool has(std::string_view needle) const {
        for (const auto& l : lines)
            if (l.find(needle) != std::string::npos) return true;
        return false;
    }
};

std::unique_ptr<ModsOverlay> open_overlay(const Synth& s, std::vector<std::filesystem::path> dirs, Logged* log = nullptr,
                                          u64 max_bytes = kModsMaxFileBytes, u32 window = kModsCvmWindowSectors) {
    auto base = IsoFileSource::open(s.file->path());
    REQUIRE(base.ok());
    ModsOptions o;
    o.dirs = std::move(dirs);
    o.max_file_bytes = max_bytes;
    o.cvm_window_sectors = window;
    if (log) o.log = log->sink();
    auto ov = ModsOverlay::open(std::move(base).value(), std::move(o));
    REQUIRE_MESSAGE(ov.ok(), formats::error_name(ov.code()) << ": " << ov.detail());
    return std::move(ov).value();
}

std::vector<std::byte> read(DiscSource& d, u32 lsn, u32 n) {
    std::vector<std::byte> b(static_cast<std::size_t>(n) * S, std::byte{0xCC});
    auto r = d.read_sectors(lsn, n, b);
    REQUIRE_MESSAGE(r.ok(), formats::error_name(r.code()) << ": " << r.detail());
    return b;
}

// Test oracle: directory records of the extent at `lsn` (byte offsets ignored), independent of runtime/hle/iso9660.
struct Rec {
    std::string id;
    u32 lsn = 0, size = 0;
    u8 flags = 0;
};
std::map<std::string, Rec> records(DiscSource& d, u32 lsn) {
    std::map<std::string, Rec> out;
    const auto b = read(d, lsn, 1);
    std::size_t off = 0;
    while (off < S) {
        const u8 len = std::to_integer<u8>(b[off]);
        if (len == 0) break;
        Rec r;
        r.lsn = le32(&b[off + 2]);
        CHECK(be32(&b[off + 6]) == r.lsn);  // both-endian fields stay consistent
        r.size = le32(&b[off + 10]);
        CHECK(be32(&b[off + 14]) == r.size);
        r.flags = std::to_integer<u8>(b[off + 25]);
        r.id.assign(reinterpret_cast<const char*>(&b[off + 33]), std::to_integer<u8>(b[off + 32]));
        out[r.id] = r;
        off += len;
    }
    return out;
}

const ModOverride* find_override(const ModsOverlay& ov, std::string_view path) {
    for (const ModOverride& o : ov.scan().overrides)
        if (o.disc_path == path) return &o;
    return nullptr;
}

std::vector<std::byte> extent_bytes(DiscSource& d, const ModOverride& o) {
    auto b = read(d, o.lsn, std::max<u32>(1, (o.size + S - 1) / S));
    CHECK(std::all_of(b.begin() + o.size, b.end(), [](std::byte x) { return x == std::byte{0}; }));  // zero tail
    b.resize(o.size);
    return b;
}

}  // namespace

TEST_CASE("mods: normalise_mod_path folds case and refuses paths that escape the mod root") {
    CHECK(normalise_mod_path("data/field/f005_001.pac").value() == "DATA\\FIELD\\F005_001.PAC");
    CHECK(normalise_mod_path("DATA\\Field\\X.BIN").value() == "DATA\\FIELD\\X.BIN");
    CHECK(normalise_mod_path("NOEXT.").value() == "NOEXT.");
    for (const char* bad : {"", "\\DATA\\X", "/DATA/X", "C:\\DATA\\X", "C:DATA", "DATA\\..\\X", "..\\X", "DATA\\.\\X",
                            "DATA\\\\X", "DATA\\X\\", "DATA\\X.BIN:stream", "DATA\\X;1", "DATA\\X*", "DATA\\\xC3\xA9.BIN",
                            "DATA\\\tX"}) {
        auto r = normalise_mod_path(bad);
        CHECK_MESSAGE(r.code() == FormatError::Unsupported, "accepted: " << bad);
    }
}

TEST_CASE("mods: mod.json -- fields, defaults, unknown and nested keys, BOM, malformed input") {
    auto full = parse_mod_json(R"({"name": "Better text", "description": "Line \"one\"\nLine two \u00e9", "load_order": -3,
                                   "authors": ["a", {"x": [1, 2.5e3, true, false, null]}], "version": 2})");
    REQUIRE_MESSAGE(full.ok(), full.detail());
    CHECK(full->name == "Better text");
    CHECK(full->description == "Line \"one\"\nLine two \xC3\xA9");
    CHECK(full->load_order == -3);
    CHECK(full->has_manifest);
    auto empty = parse_mod_json("\xEF\xBB\xBF  { }  ");
    REQUIRE(empty.ok());
    CHECK(empty->name.empty());
    CHECK(empty->load_order == 0);
    for (const char* bad : {"", "[]", "{\"name\": 3}", "{\"load_order\": 1.5}", "{\"load_order\": \"1\"}", "{\"a\":1,}",
                            "{\"a\" 1}", "{\"a\":1} x", "{\"name\": \"unterminated}", "{\"a\": tru}", "{\"a\": [1,}"}) {
        CHECK_MESSAGE(parse_mod_json(bad).code() == FormatError::BadHeader, "accepted: " << bad);
    }
}

TEST_CASE("mods: a replaced, a grown and a shrunk file -- records, LBAs, sizes, bytes, every untouched sector") {
    Synth s = make_synth();
    TempDir mods;
    auto a = s.in("A.BIN").data;
    a[1234] = static_cast<std::byte>(std::to_integer<u8>(a[1234]) ^ 0x5A);
    mods.write("DATA/A.BIN", a);
    const auto grow = pattern(7000, 20);
    mods.write("DATA/GROW.BIN", grow);
    const auto shrink = pattern(1000, 30);
    mods.write("DATA/SUB/SHRINK.BIN", shrink);
    Logged log;
    auto ov = open_overlay(s, {mods.path()}, &log);
    const ModsScan& sc = ov->scan();
    REQUIRE(sc.overrides.size() == 3);
    CHECK(sc.rejected.empty());
    CHECK(sc.mods.size() == 1);

    const Node& cvm = s.data_cvm();
    const u32 W = ov->cvm_lsn("DATA.CVM").value();
    CHECK(W == kModsFirstWindow);
    const u32 cvm_sectors = static_cast<u32>(s.cvm.size() / S);
    CHECK(ov->sector_count() == kModsFirstWindow + 2 * kModsWindowSectors);  // one CVM window + the outer window
    CHECK(ov->identity().kind == DiscSourceKind::IsoImage);

    // Extents: appended after the relocated CVM image, in path order, sector aligned.
    const ModOverride* oa = find_override(*ov, "DATA\\A.BIN");
    const ModOverride* og = find_override(*ov, "DATA\\GROW.BIN");
    const ModOverride* os = find_override(*ov, "DATA\\SUB\\SHRINK.BIN");
    REQUIRE(oa);
    REQUIRE(og);
    REQUIRE(os);
    CHECK(oa->lsn == W + cvm_sectors);
    CHECK(og->lsn == oa->lsn + 3);
    CHECK(os->lsn == og->lsn + 4);
    CHECK(oa->size == 5000);
    CHECK(og->size == 7000);
    CHECK(os->size == 1000);
    CHECK(oa->lba == oa->lsn - W - 3);
    CHECK(oa->original_size == 5000);
    CHECK(og->original_size == 3000);
    CHECK(oa->original_lsn == cvm.lsn + 3 + s.in("A.BIN").lsn);
    CHECK(extent_bytes(*ov, *oa) == a);
    CHECK(extent_bytes(*ov, *og) == grow);
    CHECK(extent_bytes(*ov, *os) == shrink);
    CHECK(log.has("DATA\\GROW.BIN <- "));
    CHECK(log.has("scan 0: 1 mod(s), 3 file(s) replaced, 0 refused"));

    // find_file: the CVM relocated with its window size; other files as on the disc.
    auto f = ov->find_file("\\data.cvm;1");
    REQUIRE(f.ok());
    REQUIRE(f->has_value());
    CHECK(f.value()->lsn == W);
    CHECK(f.value()->size == kModsCvmWindowSectors * S);
    auto lib = ov->find_file("\\LIB31\\TEST.IRX;1");
    REQUIRE(lib.ok());
    CHECK(lib.value()->lsn == s.outer.kid("LIB31")->kid("TEST.IRX")->lsn);

    // Outer directory records and PVD.
    auto pvd = read(*ov, 16, 1);
    CHECK(le32(&pvd[80]) == ov->sector_count());
    CHECK(be32(&pvd[84]) == ov->sector_count());
    auto root = records(*ov, s.outer.lsn);
    CHECK(root["DATA.CVM;1"].lsn == W);
    CHECK(root["DATA.CVM;1"].size == kModsCvmWindowSectors * S);
    CHECK(root["SYSTEM.CNF;1"].lsn == s.outer.kid("SYSTEM.CNF")->lsn);

    // CVM header sizes moved by the same amount; the inner PVD covers the window.
    const u64 vsize = static_cast<u64>(kModsCvmWindowSectors) * S, osize = s.cvm.size();
    auto hdr = read(*ov, W, 2);
    CHECK(std::memcmp(hdr.data(), "CVMH", 4) == 0);
    CHECK(be64(&hdr[0x1C]) == vsize);
    CHECK(be32(&hdr[136]) == 3);
    CHECK(be64(&hdr[S + 0x04]) == vsize - 0x80C);
    CHECK(be64(&hdr[S + 0x30]) == vsize - 3 * S);
    auto ipvd = read(*ov, W + 3 + 16, 1);
    CHECK(le32(&ipvd[80]) == kModsCvmWindowSectors - 3);
    (void)osize;

    // Inner directory records: the three point at their extents; the others are as on the disc.
    auto iroot = records(*ov, W + 3 + s.inner.lsn);
    CHECK(iroot["A.BIN;1"].lsn == oa->lba);
    CHECK(iroot["A.BIN;1"].size == 5000);
    CHECK(iroot["GROW.BIN;1"].lsn == og->lba);
    CHECK(iroot["GROW.BIN;1"].size == 7000);
    CHECK(iroot["NOEXT.;1"].lsn == s.in("NOEXT.").lsn);
    CHECK(iroot["SUB"].lsn == s.in("SUB").lsn);
    auto isub = records(*ov, W + 3 + s.in("SUB").lsn);
    CHECK(isub["SHRINK.BIN;1"].lsn == os->lba);
    CHECK(isub["SHRINK.BIN;1"].size == 1000);
    CHECK(isub["KEEP.BIN;1"].lsn == s.in("SUB", "KEEP.BIN").lsn);
    CHECK(isub["KEEP.BIN;1"].size == 100);
    // The byte through the directory record, as a reader of the inner ISO finds it.
    CHECK(read(*ov, W + 3 + iroot["A.BIN;1"].lsn, 1)[1234] == a[1234]);

    // Every sector that is not one of the patched ones equals the ISO's: the outer image in place and the
    // relocated CVM image byte for byte.
    auto iso = IsoFileSource::open(s.file->path());
    REQUIRE(iso.ok());
    const u32 iso_sectors = iso.value()->sector_count();
    std::size_t same = 0, patched = 0;
    for (u32 l = 0; l < iso_sectors; ++l) {
        const bool expect_patch = l == 16 || l == s.outer.lsn;
        const bool eq = read(*ov, l, 1) == read(*iso.value(), l, 1);
        CHECK_MESSAGE(eq != expect_patch, "outer LSN " << l);
        (eq ? same : patched) += 1;
    }
    for (u32 k = 0; k < cvm_sectors; ++k) {
        const bool expect_patch = k == 0 || k == 1 || k == 3 + 16 || k == 3 + s.inner.lsn || k == 3 + s.in("SUB").lsn;
        const bool eq = read(*ov, W + k, 1) == read(*iso.value(), cvm.lsn + k, 1);
        CHECK_MESSAGE(eq != expect_patch, "CVM sector " << k);
        (eq ? same : patched) += 1;
    }
    CHECK(patched == 7);
    CHECK(same == iso_sectors + cvm_sectors - 7);
    // Gaps of the virtual disc read as zeros; reads may span regions.
    auto gap = read(*ov, os->lsn + 1, 2);
    CHECK(std::all_of(gap.begin(), gap.end(), [](std::byte x) { return x == std::byte{0}; }));
    auto span = read(*ov, W + cvm_sectors - 1, 5);
    CHECK(std::memcmp(span.data() + S, a.data(), S) == 0);
    std::vector<std::byte> one(S);
    CHECK(ov->read_sectors(ov->sector_count() - 1, 2, one).code() == FormatError::Overrun);
}

TEST_CASE("mods: case-insensitive names, load order from mod.json, later --mods win, outer files") {
    Synth s = make_synth();
    TempDir root, extra;
    // A folder of mods: "zz_first" has load_order 1, "aa_second" load_order 2: aa_second is applied later and wins.
    root.write("zz_first/mod.json", R"({"name": "First", "load_order": 1})");
    root.write("zz_first/data/a.bin", pattern(4000, 40));
    root.write("zz_first/Data/Sub/Keep.Bin", pattern(50, 41));
    root.write("aa_second/mod.json", R"({"name": "Second", "description": "wins", "load_order": 2})");
    root.write("aa_second/DATA/A.bin", pattern(4100, 42));
    root.write("no_manifest/lib31/test.irx", pattern(800, 43));
    // A single mod given after the folder: it wins over both for KEEP.BIN.
    extra.write("DATA/SUB/KEEP.BIN", pattern(60, 44));
    auto ov = open_overlay(s, {root.path(), extra.path()});
    const ModsScan& sc = ov->scan();
    REQUIRE(sc.mods.size() == 4);
    CHECK(sc.mods[0].name == "no_manifest");  // load_order 0
    CHECK(sc.mods[1].name == "First");
    CHECK(sc.mods[2].name == "Second");
    CHECK(sc.mods[2].description == "wins");
    CHECK(sc.mods[3].name == extra.path().filename().string());
    REQUIRE(sc.overrides.size() == 3);
    const ModOverride* a = find_override(*ov, "DATA\\A.BIN");
    REQUIRE(a);
    CHECK(a->mod_name == "Second");
    CHECK(extent_bytes(*ov, *a) == pattern(4100, 42));
    const ModOverride* k = find_override(*ov, "DATA\\SUB\\KEEP.BIN");
    REQUIRE(k);
    CHECK(extent_bytes(*ov, *k) == pattern(60, 44));
    // The outer file: its own window, its record and find_file (what cdvdfsv answers) point at the extent.
    const ModOverride* irx = find_override(*ov, "LIB31\\TEST.IRX");
    REQUIRE(irx);
    CHECK(irx->lsn == kModsFirstWindow + kModsWindowSectors);
    auto f = ov->find_file("\\LIB31\\TEST.IRX;1");
    REQUIRE(f.ok());
    REQUIRE(f->has_value());
    CHECK(f.value()->lsn == irx->lsn);
    CHECK(f.value()->size == 800);
    CHECK(f.value()->identifier == "TEST.IRX;1");
    auto lib = records(*ov, s.outer.kid("LIB31")->lsn);
    CHECK(lib["TEST.IRX;1"].lsn == irx->lsn);
    CHECK(lib["TEST.IRX;1"].size == 800);
    CHECK(extent_bytes(*ov, *irx) == pattern(800, 43));
    // Through the CDVD HLE, as the IOP serves the game.
    CdvdHle cd(*ov);
    auto sr = cd.search_file("\\LIB31\\TEST.IRX;1");
    REQUIRE(sr.ok());
    REQUIRE(sr->file.has_value());
    CHECK(sr->file->lsn == irx->lsn);
}

TEST_CASE("mods: refusals -- escapes, reparse points, protected and absent files, size cap, full window") {
    Synth s = make_synth();
    TempDir mods;
    mods.write("DATA/NOPE.BIN", pattern(10, 1));          // not on the disc
    mods.write("DATA/SUB/KEEP.BIN/X", pattern(10, 1));    // under a disc *file*: not on the disc
    mods.write("SYSTEM.CNF", std::string_view("BOOT2 = cdrom0:\\X;1\r\n"));
    mods.write("SLUS_216.21", pattern(10, 2));
    mods.write("DATA.CVM", pattern(10, 3));
    mods.write("DATA/GROW.BIN", pattern(6000, 4));        // above the 5,096-byte cap below
    mods.write("DATA/X;1.BIN", pattern(10, 5));           // ';' in a name
    mods.write("DATA/A.BIN", pattern(5000, 6));           // fits
    mods.write("DATA/SUB/SHRINK.BIN", pattern(4000, 7));  // fits the cap, not the window
    TempDir outside;
    outside.write("DATA/NOEXT.", pattern(10, 8));
    std::error_code ec;
    // A directory junction (no privilege needed) and, where allowed, symlinks.
    const std::wstring junction = L"cmd /c mklink /J \"" + (mods.path() / "LINKED").wstring() + L"\" \"" +
                                  (outside.path() / "DATA").wstring() + L"\" >nul";
    const bool have_link = _wsystem(junction.c_str()) == 0 && std::filesystem::exists(mods.path() / "LINKED" / "NOEXT.");
    if (!have_link) MESSAGE("could not create a directory junction; reparse refusal not exercised");
    std::filesystem::create_directory_symlink(outside.path() / "DATA", mods.path() / "DATA" / "SUB" / "SLINK", ec);
    const bool have_dir_link = !ec;
    if (!have_dir_link) MESSAGE("directory symlinks not available here (" << ec.message() << ")");
    std::filesystem::create_symlink(outside.path() / "DATA" / "NOEXT.", mods.path() / "DATA" / "NOEXT.", ec);
    const bool have_file_link = !ec;

    Logged log;
    const u32 cvm_sectors = static_cast<u32>(s.cvm.size() / S);
    auto ov = open_overlay(s, {mods.path()}, &log, 4096 + 1000, cvm_sectors + 3);  // room for A.BIN's 3 sectors only
    const ModsScan& sc = ov->scan();
    REQUIRE(sc.overrides.size() == 1);
    CHECK(sc.overrides[0].disc_path == "DATA\\A.BIN");
    auto refused = [&](std::string_view what) {
        for (const auto& r : sc.rejected)
            if (r.find(what) != std::string::npos) return true;
        return false;
    };
    CHECK(refused("DATA\\NOPE.BIN"));
    CHECK(refused("not on the disc"));
    CHECK(refused("SYSTEM.CNF"));
    CHECK(refused("SLUS_216.21"));
    CHECK(refused("DATA.CVM"));
    CHECK(refused("protected disc file"));
    CHECK(refused("above the"));
    CHECK(refused("reserved character"));
    CHECK(refused("no room left in the DATA.CVM window"));
    if (have_link) CHECK(refused("LINKED: reparse point / symlink"));
    if (have_dir_link) CHECK(refused("SLINK: reparse point / symlink"));
    if (have_file_link) CHECK(refused("NOEXT.: reparse point / symlink"));
    CHECK(find_override(*ov, "DATA\\NOEXT.") == nullptr);  // the symlinked file is never served
    CHECK(log.has("mods: refused"));

    // A missing folder fails open (the user named it); so does a disc larger than the first window (not testable
    // here) -- and an extracted-volumes base refuses outer files (covered by the real-disc case).
    auto base = IsoFileSource::open(s.file->path());
    REQUIRE(base.ok());
    ModsOptions o;
    o.dirs = {mods.path() / "does_not_exist"};
    CHECK(ModsOverlay::open(std::move(base).value(), o).code() == FormatError::BadHeader);
}

TEST_CASE("mods: reload -- new extents for changed files, old extents keep their bytes, removed files restored") {
    Synth s = make_synth();
    TempDir mods;
    const auto a1 = pattern(5000, 50);
    mods.write("DATA/A.BIN", a1);
    mods.write("DATA/SUB/KEEP.BIN", pattern(100, 51));
    Logged log;
    auto ov = open_overlay(s, {mods.path()}, &log);
    const ModOverride a_old = *find_override(*ov, "DATA\\A.BIN");
    const ModOverride k_old = *find_override(*ov, "DATA\\SUB\\KEEP.BIN");
    CHECK(a_old.generation == 0);

    // The ROFS tables in a guest image (the ELF's copy) point at the extents.
    std::vector<std::byte> image = s.tables;
    auto p = ov->patch_rofs_tables(image, 0x100000);
    REQUIRE_MESSAGE(p.ok(), p.detail());
    CHECK(p.value() == 2);
    CHECK(ov->rofs_table_count() == 3);  // root, SUB and the decoy (the stray marker is no table)
    CHECK(le32(&image[s.entry_at["\\A.BIN"] + 8]) == a_old.lba);
    CHECK(le32(&image[s.entry_at["\\A.BIN"]]) == 5000);
    CHECK(le32(&image[s.entry_at["\\SUB\\KEEP.BIN"] + 8]) == k_old.lba);
    CHECK(ov->scan().overrides[0].rofs_entries == 1);
    // The decoy table (same directory LBA, another listing) is untouched.
    CHECK(std::equal(image.begin() + static_cast<std::ptrdiff_t>(s.entry_at["\\SUB\\KEEP.BIN"]) + 48, image.end(),
                     s.tables.begin() + static_cast<std::ptrdiff_t>(s.entry_at["\\SUB\\KEEP.BIN"]) + 48));
    const std::string fp0 = ov->fingerprint();

    // The editor saves a new A.BIN by writing a temporary file and renaming it over the old one; KEEP.BIN goes away;
    // GROW.BIN is added.
    const auto a2 = pattern(6000, 52);
    mods.write("DATA/A.tmp", a2);
    REQUIRE(::MoveFileExW((mods.path() / "DATA/A.tmp").c_str(), (mods.path() / "DATA/A.BIN").c_str(), MOVEFILE_REPLACE_EXISTING));
    std::filesystem::remove(mods.path() / "DATA/SUB/KEEP.BIN");
    mods.write("DATA/GROW.BIN", pattern(3000, 53));
    auto r = ov->reload();
    REQUIRE(r.ok());
    CHECK(r.value() == 2);
    REQUIRE(find_override(*ov, "DATA\\A.BIN"));
    const ModOverride a_copy = *find_override(*ov, "DATA\\A.BIN");  // scan() is replaced by every reload
    const ModOverride* a_new = &a_copy;
    CHECK(a_new->generation == 1);
    CHECK(a_new->lsn > a_old.lsn);  // never reused
    CHECK(a_new->size == 6000);
    CHECK(extent_bytes(*ov, *a_new) == a2);
    CHECK(extent_bytes(*ov, a_old) == a1);  // a handle the guest opened before the reload still reads the old file
    CHECK(find_override(*ov, "DATA\\SUB\\KEEP.BIN") == nullptr);
    CHECK(ov->fingerprint() != fp0);
    CHECK(log.has("scan 1: 1 mod(s), 2 file(s) replaced"));
    auto isub = records(*ov, ov->cvm_lsn("DATA.CVM").value() + 3 + s.in("SUB").lsn);
    CHECK(isub["KEEP.BIN;1"].lsn == s.in("SUB", "KEEP.BIN").lsn);  // the disc's record again
    CHECK(isub["KEEP.BIN;1"].size == 100);

    p = ov->patch_rofs_tables(image, 0x100000);
    REQUIRE(p.ok());
    CHECK(p.value() == 2);  // A.BIN, GROW.BIN
    CHECK(le32(&image[s.entry_at["\\A.BIN"] + 8]) == a_new->lba);
    CHECK(le32(&image[s.entry_at["\\A.BIN"]]) == 6000);
    CHECK(le32(&image[s.entry_at["\\GROW.BIN"]]) == 3000);
    CHECK(le32(&image[s.entry_at["\\GROW.BIN"] + 8]) == find_override(*ov, "DATA\\GROW.BIN")->lba);
    // KEEP.BIN's entry is back to the disc's bytes.
    CHECK(std::memcmp(&image[s.entry_at["\\SUB\\KEEP.BIN"]], &s.tables[s.entry_at["\\SUB\\KEEP.BIN"]], 48) == 0);
    CHECK(log.has("1 restored"));

    // An unchanged reload keeps every extent.
    const u32 lsn_before = a_new->lsn;
    REQUIRE(ov->reload().ok());
    CHECK(find_override(*ov, "DATA\\A.BIN")->lsn == lsn_before);
    CHECK(find_override(*ov, "DATA\\A.BIN")->generation == 1);
    // An in-place rewrite: the overlay holds no handle (the write succeeds), serves the scanned copy until the
    // reload, then a new extent.
    {
        std::fstream f(mods.path() / "DATA/A.BIN", std::ios::binary | std::ios::in | std::ios::out);
        REQUIRE(f.good());
        f.seekp(10);
        f.put('\x7E');
    }
    ::Sleep(20);  // a later write time than the scan saw, on file systems with coarse timestamps
    std::filesystem::last_write_time(mods.path() / "DATA/A.BIN", std::filesystem::file_time_type::clock::now());
    CHECK(extent_bytes(*ov, *find_override(*ov, "DATA\\A.BIN"))[10] == a2[10]);
    REQUIRE(ov->reload().ok());
    const ModOverride* a3 = find_override(*ov, "DATA\\A.BIN");
    CHECK(a3->lsn > lsn_before);
    CHECK(extent_bytes(*ov, *a3)[10] == std::byte{0x7E});
    CHECK(extent_bytes(*ov, *a_new) == a2);
    // A different image than the first call's is refused.
    std::vector<std::byte> other(16);
    CHECK(ov->patch_rofs_tables(other, 0x100000).code() == FormatError::Unsupported);
}

TEST_CASE("mods: files above the in-memory size are read from the host file at each read") {
    Synth s = make_synth();
    TempDir mods;
    const auto big = pattern(9000, 70);
    mods.write("DATA/SUB/SHRINK.BIN", big);
    auto base = IsoFileSource::open(s.file->path());
    REQUIRE(base.ok());
    ModsOptions o;
    o.dirs = {mods.path()};
    o.snapshot_max_file_bytes = 4096;
    auto ovr = ModsOverlay::open(std::move(base).value(), o);
    REQUIRE(ovr.ok());
    auto& ov = *ovr.value();
    const ModOverride sh = ov.scan().overrides.at(0);
    CHECK(extent_bytes(ov, sh) == big);
    // Replace by rename (the overlay holds no handle) with a shorter file: the extent reads it, zero-padded.
    const auto shorter = pattern(5000, 71);
    mods.write("DATA/SUB/S.tmp", shorter);
    REQUIRE(::MoveFileExW((mods.path() / "DATA/SUB/S.tmp").c_str(), (mods.path() / "DATA/SUB/SHRINK.BIN").c_str(),
                          MOVEFILE_REPLACE_EXISTING));
    auto now = extent_bytes(ov, sh);
    CHECK(std::equal(shorter.begin(), shorter.end(), now.begin()));
    CHECK(std::all_of(now.begin() + 5000, now.end(), [](std::byte x) { return x == std::byte{0}; }));
    // Gone: the read fails (the guest sees a read error) instead of serving stale bytes.
    std::filesystem::remove(mods.path() / "DATA/SUB/SHRINK.BIN");
    std::vector<std::byte> buf(S);
    CHECK_FALSE(ov.read_sectors(sh.lsn, 1, buf).ok());
}

TEST_CASE("mods: files read since the last reload, the stale list, enable / disable, folder list") {
    Synth s = make_synth();
    TempDir mods;
    mods.write("DATA/A.BIN", pattern(5000, 60));
    auto ov = open_overlay(s, {mods.path()});
    std::vector<std::string> seen;
    ov->set_read_observer([&](const std::string& p) { seen.push_back(p); });
    const u32 W = ov->cvm_lsn("DATA.CVM").value();
    CHECK(ov->files_read().empty());

    read(*ov, W, 2);                    // CVM header sectors: no file
    read(*ov, W + 3 + 16, 1);           // the inner PVD: no file
    read(*ov, W + 3 + s.inner.lsn, 1);  // a directory: no file
    CHECK(ov->files_read().empty());
    read(*ov, W + 3 + s.in("SUB", "KEEP.BIN").lsn, 1);  // an untouched member at its relocated LSN
    read(*ov, W + 3 + s.in("SUB", "KEEP.BIN").lsn, 1);  // twice: reported once
    const ModOverride a = *find_override(*ov, "DATA\\A.BIN");
    read(*ov, a.lsn + 1, 1);                           // the replaced file's extent
    read(*ov, s.outer.kid("LIB31")->kid("TEST.IRX")->lsn, 1);  // an outer file
    read(*ov, W + 3 + s.in("GROW.BIN").lsn + 1, 2);    // a span over the end of one file and the start of the next
    CHECK(s.in("NOEXT.").lsn == s.in("GROW.BIN").lsn + 2);
    CHECK(ov->files_read() == std::vector<std::string>{"DATA\\A.BIN", "DATA\\GROW.BIN", "DATA\\NOEXT.", "DATA\\SUB\\KEEP.BIN",
                                                       "LIB31\\TEST.IRX"} );
    CHECK(seen.size() == 5);
    CHECK(seen[0] == "DATA\\SUB\\KEEP.BIN");
    CHECK(ov->was_read("DATA\\A.BIN"));
    CHECK_FALSE(ov->was_read("DATA\\SUB\\SHRINK.BIN"));

    // A changes and SHRINK.BIN (never read) is added: only A needs a scene reload; the read list starts over.
    mods.write("DATA/A.BIN", pattern(5100, 61));
    mods.write("DATA/SUB/SHRINK.BIN", pattern(10, 62));
    REQUIRE(ov->reload().ok());
    CHECK(ov->stale_after_reload() == std::vector<std::string>{"DATA\\A.BIN"});
    CHECK(ov->files_read().empty());

    // Disabled: nothing replaced, the tables go back to the disc's values; A (read earlier) is listed as stale.
    std::vector<std::byte> image = s.tables;
    REQUIRE(ov->patch_rofs_tables(image, 0x200000).ok());
    CHECK(le32(&image[s.entry_at["\\A.BIN"]]) == 5100);
    ov->set_enabled(false);
    REQUIRE(ov->reload().ok());
    CHECK(ov->scan().overrides.empty());
    CHECK(ov->scan().mods.empty());
    CHECK(ov->stale_after_reload() == std::vector<std::string>{"DATA\\A.BIN"});
    REQUIRE(ov->patch_rofs_tables(image, 0x200000).ok());
    CHECK(image == s.tables);
    auto f = ov->find_file("\\DATA.CVM;1");
    REQUIRE(f.ok());
    CHECK(f.value()->lsn == W);  // the CVM stays relocated
    ov->set_enabled(true);
    REQUIRE(ov->reload().ok());
    CHECK(ov->scan().overrides.size() == 2);
    // Folder list: none -> nothing replaced; a missing folder -> the reload fails and the overrides stay.
    ov->set_dirs({});
    REQUIRE(ov->reload().ok());
    CHECK(ov->scan().overrides.empty());
    ov->set_dirs({mods.path(), mods.path() / "missing"});
    CHECK(ov->reload().code() == FormatError::BadHeader);
    CHECK(ov->scan().overrides.empty());
    ov->set_dirs({mods.path()});
    REQUIRE(ov->reload().ok());
    CHECK(ov->scan().overrides.size() == 2);
}

TEST_CASE("mods: an overlay with no folder serves the disc unchanged apart from the relocated CVMs") {
    Synth s = make_synth();
    auto ov = open_overlay(s, {});
    CHECK(ov->scan().overrides.empty());
    CHECK(ov->scan().mods.empty());
    auto iso = IsoFileSource::open(s.file->path());
    REQUIRE(iso.ok());
    const u32 W = ov->cvm_lsn("DATA.CVM").value();
    const Node& cvm = s.data_cvm();
    for (u32 k = 3 + 17; k < s.cvm.size() / S; ++k)  // past the header and the inner PVD: no directory is patched
        CHECK(read(*ov, W + k, 1) == read(*iso.value(), cvm.lsn + k, 1));
    std::vector<std::byte> image = s.tables;
    auto p = ov->patch_rofs_tables(image, 0x100000);
    REQUIRE(p.ok());
    CHECK(p.value() == 0);
    CHECK(image == s.tables);
}

// ---- the user's disc ------------------------------------------------------------------------------

namespace {

// The ELF's loaded bytes (first PT_LOAD segment) as the game sees them in RAM, read from the disc itself.
struct ElfImage {
    std::vector<std::byte> bytes;
    u32 va = 0;
};
ElfImage load_elf_from_disc(DiscSource& d) {
    auto f = d.find_file("\\SLUS_216.21;1");
    REQUIRE(f.ok());
    REQUIRE(f->has_value());
    auto all = read(d, f.value()->lsn, f.value()->sectors());
    all.resize(f.value()->size);
    const u32 phoff = le32(&all[28]);
    ElfImage img;
    img.va = le32(&all[phoff + 8]);
    const u32 off = le32(&all[phoff + 4]), filesz = le32(&all[phoff + 16]);
    img.bytes.assign(all.begin() + off, all.begin() + off + filesz);
    return img;
}

// The game's lookup (RFDIR_SearchName over vol.dir): the table whose directory LBA and listing are those of
// `dir_lba`, and its entry `name`. Returns the entry offset in the image or npos.
std::size_t rofs_entry(const ElfImage& img, u32 dir_lba, u32 dir_size, std::string_view name, u32 lba) {
    for (std::size_t pos = 12; pos + 8 <= img.bytes.size(); ++pos) {
        if (std::memcmp(&img.bytes[pos], "#DirLst#", 8) != 0) continue;
        const std::size_t h = pos - 12;
        const u32 count = le32(&img.bytes[h]);
        if (count != le32(&img.bytes[h + 4]) || le32(&img.bytes[h + 8]) != dir_lba || h + 24 + 48 * count > img.bytes.size()) continue;
        if (le32(&img.bytes[h + 24]) != dir_size) continue;
        for (u32 k = 2; k < count; ++k) {
            const std::size_t e = h + 24 + 48 * k;
            if (std::string_view(reinterpret_cast<const char*>(&img.bytes[e + 14])) == name &&
                (lba == 0 || le32(&img.bytes[e + 8]) == lba))
                return e;
        }
    }
    return std::string::npos;
}

}  // namespace

TEST_CASE("mods: the user's disc -- a real data file with one byte changed reaches the guest's read path") {
    auto iso = test::open_real_iso();
    P3FES_SKIP_UNLESS(iso, "input/persona3fes.iso");
    // Pick a small file from DATA.CVM's first subdirectory (test oracle walk, not the overlay's).
    const DiscLayoutEntry& data = *find_disc_layout("DATA.CVM");
    const u32 inner0 = data.lsn + kCvmHeaderSectors;
    auto ipvd = read(*iso, inner0 + 16, 1);
    const u32 root_lba = le32(&ipvd[156 + 2]);
    auto root = records(*iso, inner0 + root_lba);
    Rec dir, file;
    for (const auto& [id, r] : root) {
        if (!(r.flags & 2) || id.size() < 2) continue;
        for (const auto& [fid, fr] : records(*iso, inner0 + r.lsn))
            if (!(fr.flags & 2) && fr.size > 2048 && fr.size < 64 * 1024 && fid.size() > 2) {
                dir = r;
                file = fr;
                break;
            }
        if (file.size) break;
    }
    REQUIRE(file.size != 0);
    const std::string name = file.id.substr(0, file.id.find(';'));
    const std::string dir_name = dir.id;
    MESSAGE("modifying DATA\\" << dir_name << "\\" << name << " (" << file.size << " B, lba " << file.lsn << ")");
    auto original = read(*iso, inner0 + file.lsn, (file.size + S - 1) / S);
    original.resize(file.size);
    auto modded = original;
    const std::size_t at = file.size / 2;
    modded[at] = static_cast<std::byte>(std::to_integer<u8>(modded[at]) ^ 0xFF);
    TempDir mods;
    mods.write(std::filesystem::path("DATA") / dir_name / name, modded);

    // Unmodified ELF: the game's own entry for the file.
    const ElfImage pristine = load_elf_from_disc(*iso);
    const std::size_t e0 = rofs_entry(pristine, dir.lsn, dir.size, name, file.lsn);
    REQUIRE(e0 != std::string::npos);
    CHECK(le32(&pristine.bytes[e0]) == file.size);

    Logged log;
    ModsOptions o;
    o.dirs = {mods.path()};
    o.log = log.sink();
    auto ovr = ModsOverlay::open(std::move(iso), o);
    REQUIRE_MESSAGE(ovr.ok(), ovr.detail());
    auto& ov = *ovr.value();
    REQUIRE(ov.scan().overrides.size() == 1);
    CHECK(ov.scan().rejected.empty());
    ElfImage ram = pristine;
    auto p = ov.patch_rofs_tables(ram.bytes, ram.va);
    REQUIRE(p.ok());
    CHECK(ov.rofs_table_count() == 149);  // docs/ANALYSIS/11 §1
    CHECK(p.value() == 1);

    // The game's path, through the CDVD HLE: sceCdSearchFile("\DATA.CVM;1") -> the CVM's LSN; its CVMH says the
    // ISO data starts 3 sectors in; the ROFS entry gives lba and size; sceCdRead reads the sectors.
    CdvdHle cd(ov);
    auto sr = cd.search_file("\\DATA.CVM;1");
    REQUIRE(sr.ok());
    REQUIRE(sr->file.has_value());
    const u32 cvm_lsn = sr->file->lsn;
    CHECK(cvm_lsn == ov.cvm_lsn("DATA.CVM").value());
    CHECK(sr->file->size == 0xFFFFF800u);
    std::vector<std::byte> hdr(S);
    REQUIRE(cd.read(cvm_lsn, 1, hdr, ReadMode{}).ok());
    CHECK(cd.sync(SyncMode::Block) == 0);
    const u32 lba_offset = be32(&hdr[136]);
    CHECK(lba_offset == 3);
    const u32 size = le32(&ram.bytes[e0]), lba = le32(&ram.bytes[e0 + 8]);
    CHECK(size == file.size);
    CHECK(lba != file.lsn);
    // dvCiSeek clamps to (size + 2047) >> 11 of the CVM: the extent must lie below it.
    CHECK(lba_offset + lba + (size + S - 1) / S <= (sr->file->size + 2047u) >> 11);
    std::vector<std::byte> got(static_cast<std::size_t>((size + S - 1) / S) * S);
    REQUIRE(cd.read(cvm_lsn + lba_offset + lba, (size + S - 1) / S, got, ReadMode{}).ok());
    CHECK(cd.sync(SyncMode::Block) == 0);
    CHECK(cd.get_error() == cd::kErrNone);
    got.resize(size);
    CHECK(got[at] == modded[at]);
    CHECK(got[at] != original[at]);
    CHECK(got == modded);
    // Every other file of the CVM reads as before at its unpatched entry, relocated: e.g. the original extent.
    auto same = read(ov, cvm_lsn + lba_offset + file.lsn, (file.size + S - 1) / S);
    same.resize(file.size);
    CHECK(same == original);
    // The other two CVMs are relocated too, and the ELF's own tables still match the CVMs' directories.
    CHECK(ov.cvm_lsn("BTL.CVM").has_value());
    CHECK(ov.cvm_lsn("BGM.CVM").has_value());
    CHECK(log.has("ROFS tables: 149 in the ELF"));
}

TEST_CASE("mods: over extracted/disc -- CVM members work, outer files are refused") {
    auto ext = test::open_real_extracted();
    P3FES_SKIP_UNLESS(ext, "extracted/disc");
    const DiscLayoutEntry& data = *find_disc_layout("DATA.CVM");
    const u32 inner0 = data.lsn + kCvmHeaderSectors;
    auto ipvd = read(*ext, inner0 + 16, 1);
    auto root = records(*ext, inner0 + le32(&ipvd[156 + 2]));
    Rec file;
    std::string fname, dname;
    for (const auto& [id, r] : root) {
        if (!(r.flags & 2) || id.size() < 2) continue;
        for (const auto& [fid, fr] : records(*ext, inner0 + r.lsn))
            if (!(fr.flags & 2) && fr.size > 0 && fr.size < 1'000'000 && fid.size() > 2) {
                file = fr;
                fname = fid.substr(0, fid.find(';'));
                dname = id;
                break;
            }
        if (file.size) break;
    }
    REQUIRE(file.size != 0);
    TempDir mods;
    const auto bytes = pattern(file.size + 3000, 77);
    mods.write(std::filesystem::path("DATA") / dname / fname, bytes);
    mods.write("LIB31/PADMAN.IRX", pattern(10, 78));
    ModsOptions o;
    o.dirs = {mods.path()};
    auto ovr = ModsOverlay::open(std::move(ext), o);
    REQUIRE(ovr.ok());
    auto& ov = *ovr.value();
    CHECK(ov.identity().kind == DiscSourceKind::ExtractedVolumes);
    REQUIRE(ov.scan().overrides.size() == 1);
    CHECK(extent_bytes(ov, ov.scan().overrides[0]) == bytes);
    REQUIRE(ov.scan().rejected.size() == 1);
    CHECK(ov.scan().rejected[0].find("extracted-volumes source has no ISO directory") != std::string::npos);
    auto f = ov.find_file("\\DATA.CVM;1");
    REQUIRE(f.ok());
    CHECK(f.value()->lsn == ov.cvm_lsn("DATA.CVM").value());
}

// ---- the read log (p3fes/hle/read_log.h; docs/MODERNIZE_PLAN.md §3 stage 0) ---------------------------------------
// Kept here for the synthetic disc with a CVM above.

TEST_CASE("read log: FNV-1a 64 and the line format") {
    CHECK(fnv1a64({}) == kFnv1a64Basis);
    const std::string a = "a", foobar = "foobar";
    CHECK(fnv1a64(std::as_bytes(std::span(a.data(), a.size()))) == 0xAF63DC4C8601EC8Cull);
    CHECK(fnv1a64(std::as_bytes(std::span(foobar.data(), foobar.size()))) == 0x85944171F73967E8ull);
    ReadLogRecord r;
    r.vblank = 1595;
    r.lsn = 584'500;
    r.sectors = 3;
    r.dst = 0x01A2B340;
    r.file = ResolvedRead{"DATA.CVM:\\FIELD\\PACK\\F032_002.PAC", 8192, 70'000};
    r.hash = 0x0123456789ABCDEFull;
    CHECK(format_read_log_line(r) ==
          "1595 lsn=584500 n=3 bytes=6144 dst=01A2B340 path=DATA.CVM:\\FIELD\\PACK\\F032_002.PAC off=8192 fsize=70000 "
          "hash=0123456789ABCDEF");
    r.error = 0x30;
    r.file = ResolvedRead{};
    CHECK(format_read_log_line(r) == "1595 lsn=584500 n=3 bytes=6144 dst=01A2B340 path=- off=0 fsize=0 hash=- err=48");
    CHECK(kReadLogHeader.front() == '#');
}

TEST_CASE("read log: the path index of a synthetic disc -- CVM members, outer files, spans across files") {
    Synth s = make_synth();
    auto disc = IsoFileSource::open(s.file->path());
    REQUIRE(disc.ok());
    const DiscPathIndex ix = DiscPathIndex::build(*disc.value());
    CHECK(ix.members() == 5);
    CHECK(ix.outer_files() == 4);  // DATA.CVM, LIB31\TEST.IRX, SLUS_216.21, SYSTEM.CNF
    const u32 cvm = s.data_cvm().lsn, img = cvm + 3;
    const Node& a = s.in("A.BIN");
    ResolvedRead r = ix.resolve(img + a.lsn, 1);
    CHECK(r.path == "DATA.CVM:\\A.BIN");
    CHECK(r.offset == 0);
    CHECK(r.file_size == 5000);
    r = ix.resolve(img + a.lsn + 1, 2);  // the last two sectors, padding included
    CHECK(r.path == "DATA.CVM:\\A.BIN");
    CHECK(r.offset == S);
    r = ix.resolve(img + s.in("SUB", "KEEP.BIN").lsn, 1);
    CHECK(r.path == "DATA.CVM:\\SUB\\KEEP.BIN");
    CHECK(r.file_size == 100);
    CHECK(ix.resolve(img + s.in("NOEXT.").lsn, 1).path == "DATA.CVM:\\NOEXT.");
    r = ix.resolve(img + a.lsn, 4);  // runs into the next member: the CVM itself
    CHECK(r.path == "DATA.CVM");
    CHECK(r.offset == static_cast<u64>(3 + a.lsn) * S);
    CHECK(r.file_size == s.cvm.size());
    r = ix.resolve(cvm, 1);  // the CVMH header
    CHECK(r.path == "DATA.CVM");
    CHECK(r.offset == 0);
    r = ix.resolve(s.outer.kid("LIB31")->kid("TEST.IRX")->lsn, 1);
    CHECK(r.path == "LIB31\\TEST.IRX");
    CHECK(r.file_size == 700);
    CHECK(ix.resolve(s.outer.kid("SLUS_216.21")->lsn, 2).path == "SLUS_216.21");
    r = ix.resolve(16, 1);  // the PVD: no file
    CHECK(r.path == "-");
    CHECK(r.offset == 16u * S);
    CHECK(r.file_size == 0);
    CHECK(ix.resolve(s.outer.kid("SLUS_216.21")->lsn, 1000).path == "-");  // past the end of every file
}

TEST_CASE("read log: the path index over a mods overlay follows the relocated CVM") {
    Synth s = make_synth();
    auto ov = open_overlay(s, {});
    const DiscPathIndex ix = DiscPathIndex::build(*ov);
    CHECK(ix.members() == 5);
    const u32 img = ov->cvm_lsn("DATA.CVM").value() + 3;
    const ResolvedRead r = ix.resolve(img + s.in("GROW.BIN").lsn, 1);
    CHECK(r.path == "DATA.CVM:\\GROW.BIN");
    CHECK(r.file_size == 3000);
}

TEST_CASE("read log: the path index of the user's disc (ISO and extracted volumes agree)") {
    auto iso = test::open_real_iso();
    if (!iso) return;
    const DiscPathIndex ix = DiscPathIndex::build(*iso);
    MESSAGE("ISO: " << ix.outer_files() << " outer files, " << ix.members() << " CVM members");
    CHECK(ix.members() > 10'000);
    const DiscLayoutEntry& slus = *find_disc_layout("SLUS_216.21");
    ResolvedRead r = ix.resolve(slus.lsn, 2);
    CHECK(r.path == "SLUS_216.21");
    CHECK(r.offset == 0);
    CHECK(r.file_size == slus.size);
    const DiscLayoutEntry& data = *find_disc_layout("DATA.CVM");
    CHECK(ix.resolve(data.lsn, 1).path == "DATA.CVM");
    auto ext = test::open_real_extracted();
    if (!ext) return;
    const DiscPathIndex ex = DiscPathIndex::build(*ext);
    CHECK(ex.members() == ix.members());
    CHECK(ex.outer_files() == kDiscLayout.size());
    CHECK(ex.resolve(slus.lsn, 2).path == "SLUS_216.21");
}

// ---- modernize layer 1: the native files service (runtime/native/files/native_files.h) -------------------------

TEST_CASE("native files: path keys fold case, separators, versions and trailing dots") {
    using native::files::path_key;
    CHECK(path_key("DATA.CVM:\\FIELD\\X.PAC") == "DATA.CVM:\\FIELD\\X.PAC");
    CHECK(path_key("data.cvm:/field//x.pac;1") == "DATA.CVM:\\FIELD\\X.PAC");
    CHECK(path_key("\\DATA.CVM;1") == "DATA.CVM");
    CHECK(path_key("DATA.CVM:\\FIELD\\LMAP_DAT.") == path_key("DATA.CVM:\\FIELD\\LMAP_DAT"));
    CHECK(path_key("LIB31\\TEST.IRX;1") == "LIB31\\TEST.IRX");
}

TEST_CASE("native files: by path -- members, outer files, the disc's padding, container reads, search, the observer") {
    Synth s = make_synth();
    auto disc = IsoFileSource::open(s.file->path());
    REQUIRE(disc.ok());
    auto opened = native::files::NativeFiles::open(*disc.value());
    REQUIRE(opened.ok());
    native::files::NativeFiles& nf = *opened.value();
    CHECK(nf.members() == 5);
    CHECK(nf.outer_files() == 4);
    const u32 cvm = s.data_cvm().lsn, img = cvm + 3;
    const Node& a = s.in("A.BIN");

    const auto f = nf.find("DATA.CVM:\\A.BIN");
    REQUIRE(f);
    CHECK(f->size == 5000);
    CHECK(f->lsn == img + a.lsn);
    const auto f2 = nf.find("data.cvm:/a.bin;1");
    REQUIRE(f2);
    CHECK(f2->id == f->id);
    CHECK(nf.find("DATA.CVM:\\NOEXT"));   // ROFS's "NOEXT." and the bare name are the same file
    CHECK(nf.find("DATA.CVM:\\NOEXT."));
    CHECK(nf.find("DATA.CVM:\\SUB\\KEEP.BIN")->size == 100);
    CHECK_FALSE(nf.find("DATA.CVM:\\NONE.BIN"));
    CHECK_FALSE(nf.find("DATA.CVM:\\KEEP.BIN"));  // not in the root directory

    std::vector<native::files::NativeRead> seen;
    std::vector<std::vector<std::byte>> seen_bytes;
    nf.set_read_observer([&](const native::files::NativeRead& r) {
        seen.push_back(r);
        seen_bytes.emplace_back(r.data.begin(), r.data.end());
    });
    // Whole sectors, the last one's padding as the disc holds it (what a sector read delivers).
    std::vector<std::byte> got(3 * S);
    REQUIRE(nf.read(*f, 0, got, 0x01234000u));
    CHECK(got == read(*disc.value(), img + a.lsn, 3));
    REQUIRE(seen.size() == 1);
    CHECK(seen[0].lsn == img + a.lsn);
    CHECK(seen[0].sectors == 3);
    CHECK(seen[0].guest_dst == 0x01234000u);
    CHECK(seen_bytes[0] == got);
    // An unaligned range.
    std::vector<std::byte> part(50);
    REQUIRE(nf.read(*f, 100, part, 0));
    CHECK(std::equal(part.begin(), part.end(), a.data.begin() + 100));
    // The container by its LSN (dvCi), at the member's offset in it; the CVMH header sector.
    const auto c = nf.outer_at(cvm);
    REQUIRE(c);
    CHECK(c->size == s.cvm.size());
    CHECK_FALSE(nf.outer_at(cvm + 1));
    std::vector<std::byte> via(3 * S);
    REQUIRE(nf.read(*c, static_cast<u64>(3 + a.lsn) * S, via, 0));
    CHECK(via == got);
    std::vector<std::byte> hdr(S);
    REQUIRE(nf.read(*c, 0, hdr, 0));
    CHECK(std::memcmp(hdr.data(), "CVMH", 4) == 0);
    // Outer files and sceCdSearchFile's answer.
    const auto irx = nf.find("LIB31\\TEST.IRX");
    REQUIRE(irx);
    CHECK(irx->size == 700);
    const auto o = nf.search("\\DATA.CVM;1");
    REQUIRE(o);
    CHECK(o->identifier == "DATA.CVM;1");
    CHECK(o->file.lsn == cvm);
    CHECK(o->file.size == s.cvm.size());
    CHECK_FALSE(nf.search("\\NONE.CVM;1"));
    CHECK_FALSE(nf.search("DATA.CVM:\\A.BIN"));  // a member is not an outer file
    // Past the disc: an error, never a short read.
    std::vector<std::byte> beyond(S);
    CHECK_FALSE(nf.read(*c, static_cast<u64>(disc.value()->sector_count()) * S, beyond, 0));
}

TEST_CASE("native files: mods by path -- the mod file's bytes and size at the disc file's LSN, zeros after it, containers") {
    Synth s = make_synth();
    TempDir mods;
    const std::vector<std::byte> grown = pattern(7000, 40);
    mods.write("DATA\\GROW.BIN", grown);
    const std::vector<std::byte> irx = pattern(300, 41);
    mods.write("LIB31\\TEST.IRX", irx);
    auto ov = open_overlay(s, {mods.path()});
    REQUIRE(ov->scan().overrides.size() == 2);
    // Native mode reads the plain disc (the overlay's base): no relocated LSNs.
    auto opened = native::files::NativeFiles::open(ov->base());
    REQUIRE(opened.ok());
    native::files::NativeFiles& nf = *opened.value();
    const u32 cvm = s.data_cvm().lsn, img = cvm + 3;
    const Node& g = s.in("GROW.BIN");
    CHECK(nf.find("DATA.CVM:\\GROW.BIN")->size == 3000);
    CHECK(nf.set_overrides(ov->scan().overrides) == 2);
    const auto f = nf.find("DATA.CVM:\\GROW.BIN");
    REQUIRE(f);
    CHECK(f->size == 7000);
    CHECK(f->lsn == img + g.lsn);
    std::vector<std::byte> got(4 * S, std::byte{0xCC});
    REQUIRE(nf.read(*f, 0, got, 0));
    CHECK(std::equal(grown.begin(), grown.end(), got.begin()));
    CHECK(std::all_of(got.begin() + 7000, got.end(), [](std::byte b) { return b == std::byte{0}; }));
    CHECK(nf.find("LIB31\\TEST.IRX")->size == 300);
    // A container read over the replaced member (a stream through dvCi): the member's disc extent (2 sectors for
    // 3000 bytes) serves the mod file; the sectors around it stay the disc's.
    const auto c = nf.outer_at(cvm);
    REQUIRE(c);
    const u64 at = static_cast<u64>(3 + g.lsn) * S;
    std::vector<std::byte> span(4 * S);
    REQUIRE(nf.read(*c, at - S, span, 0));
    const std::vector<std::byte> disc_bytes = read(ov->base(), img + g.lsn - 1, 4);
    CHECK(std::equal(span.begin(), span.begin() + S, disc_bytes.begin()));
    CHECK(std::equal(span.begin() + S, span.begin() + 3 * S, grown.begin()));
    CHECK(std::equal(span.begin() + 3 * S, span.end(), disc_bytes.begin() + 3 * S));
    // Untouched members are the disc's.
    std::vector<std::byte> a(S);
    REQUIRE(nf.read(*nf.find("DATA.CVM:\\A.BIN"), 0, a, 0));
    CHECK(std::equal(a.begin(), a.end(), s.in("A.BIN").data.begin()));
    // Overrides off again: the disc's bytes and size.
    CHECK(nf.set_overrides({}) == 0);
    CHECK(nf.find("DATA.CVM:\\GROW.BIN")->size == 3000);
    REQUIRE(nf.read(*nf.find("DATA.CVM:\\GROW.BIN"), 0, got, 0));
    CHECK(std::equal(g.data.begin(), g.data.end(), got.begin()));
}

TEST_CASE("native files: the user's disc -- every container by LSN, sceCdSearchFile's records, ISO and extracted agree") {
    auto iso = test::open_real_iso();
    if (!iso) return;
    auto opened = native::files::NativeFiles::open(*iso);
    REQUIRE(opened.ok());
    native::files::NativeFiles& nf = *opened.value();
    MESSAGE("native files over the ISO: " << nf.outer_files() << " outer files, " << nf.members() << " CVM members");
    CHECK(nf.members() > 10'000);
    for (const DiscLayoutEntry& e : kDiscLayout) {
        const auto f = nf.outer_at(e.lsn);
        REQUIRE(f);
        CHECK(f->size == e.size);
        const auto o = nf.search("\\" + std::string(e.identifier));
        REQUIRE(o);
        CHECK(o->identifier == e.identifier);
        CHECK(o->recorded == e.recorded);
    }
    auto ext = test::open_real_extracted();
    if (!ext) return;
    auto opened_ext = native::files::NativeFiles::open(*ext);
    REQUIRE(opened_ext.ok());
    native::files::NativeFiles& nx = *opened_ext.value();
    CHECK(nx.members() == nf.members());
    // A sample of members, by path, from both host files.
    std::size_t i = 0, compared = 0;
    std::vector<std::byte> a(S), b(S);
    nf.for_each_file([&](const std::string& path, u32, u64 size) {
        if (i++ % 997 != 0 || path.find(':') == std::string::npos || size == 0) return;
        const auto fa = nf.find(path), fb = nx.find(path);
        REQUIRE(fa);
        REQUIRE(fb);
        CHECK(fa->lsn == fb->lsn);
        REQUIRE(nf.read(*fa, 0, a, 0));
        REQUIRE(nx.read(*fb, 0, b, 0));
        CHECK(a == b);
        ++compared;
    });
    CHECK(compared > 5);
}
