// Fixtures for the CDVD HLE tests: a synthetic ISO9660 builder (no game data), locators for the
// user's ISO / extracted/disc (tests skip cleanly when absent), and a minimal reader for the
// path/container/size/lba fields of extracted/manifest.json.
#pragma once

#include <doctest.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "../formats/fixtures.h"  // test::extracted_dir(): P3FES_EXTRACTED override, else the build-time path
#include "p3fes/hle/disc_source.h"

namespace p3fes::test {

// ---- real data ------------------------------------------------------------------------------

inline std::filesystem::path iso_path() {
    if (const char* env = std::getenv("P3FES_ISO"); env && *env) return env;
#ifdef P3FES_INPUT_DIR
    return std::filesystem::path(P3FES_INPUT_DIR) / "persona3fes.iso";
#else
    return std::filesystem::path("input") / "persona3fes.iso";
#endif
}

inline std::filesystem::path extracted_disc_dir() { return extracted_dir() / "disc"; }

// nullptr when the ISO is absent (caller skips). A present ISO that fails to open is a failure.
inline std::unique_ptr<hle::IsoFileSource> open_real_iso() {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(iso_path(), ec)) return nullptr;
    auto r = hle::IsoFileSource::open(iso_path());
    if (!r) {
        FAIL_CHECK("user ISO present but refused: " << formats::error_name(r.code()) << ": " << r.detail());
        return nullptr;
    }
    return std::move(r).value();
}

inline std::unique_ptr<hle::ExtractedVolumesSource> open_real_extracted() {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(extracted_disc_dir() / "DATA.CVM", ec)) return nullptr;
    auto r = hle::ExtractedVolumesSource::open(extracted_disc_dir());
    if (!r) {
        FAIL_CHECK("extracted/disc present but refused: " << formats::error_name(r.code()) << ": " << r.detail());
        return nullptr;
    }
    return std::move(r).value();
}

inline std::optional<std::vector<std::byte>> read_host_file(const std::filesystem::path& p) {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    std::ifstream f(p, std::ios::binary);
    std::vector<std::byte> data(static_cast<std::size_t>(std::filesystem::file_size(p, ec)));
    if (!f || (!data.empty() && !f.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(data.size()))))
        return std::nullopt;
    return data;
}

// ---- manifest.json --------------------------------------------------------------------------

struct ManifestEntry {
    std::string path;       // relative to extracted/, e.g. "DATA/BUSTUP/BUST_DUMMY.BIN"
    std::string container;  // "DATA.CVM" / "BTL.CVM" / "BGM.CVM"
    u64 size = 0;
    u32 lba = 0;            // ISO LBA inside the CVM
};

// Minimal JSON walker: enough grammar to skip any value and to read the scalar fields of the
// objects in the top-level "entries" array. nullopt on malformed input.
class ManifestReader {
public:
    explicit ManifestReader(std::string_view text) : s_(text) {}

    std::optional<std::vector<ManifestEntry>> entries() {
        std::vector<ManifestEntry> out;
        if (!expect('{')) return std::nullopt;
        while (true) {
            ws();
            if (peek() == '}') return out;
            auto key = string();
            if (!key || !expect(':')) return std::nullopt;
            if (*key == "entries") {
                if (!expect('[')) return std::nullopt;
                while (true) {
                    ws();
                    if (peek() == ']') { ++p_; break; }
                    auto e = entry();
                    if (!e) return std::nullopt;
                    out.push_back(std::move(*e));
                    ws();
                    if (peek() == ',') ++p_;
                }
            } else if (!skip_value()) {
                return std::nullopt;
            }
            ws();
            if (peek() == ',') ++p_;
        }
    }

private:
    char peek() const { return p_ < s_.size() ? s_[p_] : '\0'; }
    void ws() { while (p_ < s_.size() && (s_[p_] == ' ' || s_[p_] == '\n' || s_[p_] == '\r' || s_[p_] == '\t')) ++p_; }
    bool expect(char c) { ws(); if (peek() != c) return false; ++p_; return true; }

    std::optional<std::string> string() {
        ws();
        if (peek() != '"') return std::nullopt;
        ++p_;
        std::string out;
        while (p_ < s_.size() && s_[p_] != '"') {
            if (s_[p_] == '\\') {
                if (++p_ >= s_.size()) return std::nullopt;
                const char e = s_[p_];
                if (e == 'u') { p_ += 4; out.push_back('?'); }   // not needed for the fields read here
                else out.push_back(e == 'n' ? '\n' : e == 't' ? '\t' : e);
                ++p_;
                continue;
            }
            out.push_back(s_[p_++]);
        }
        if (p_ >= s_.size()) return std::nullopt;
        ++p_;
        return out;
    }

    std::optional<std::string_view> scalar() {
        ws();
        const std::size_t b = p_;
        while (p_ < s_.size() && s_[p_] != ',' && s_[p_] != '}' && s_[p_] != ']' && s_[p_] != ' ' && s_[p_] != '\n' &&
               s_[p_] != '\r')
            ++p_;
        if (p_ == b) return std::nullopt;
        return s_.substr(b, p_ - b);
    }

    bool skip_value() {
        ws();
        const char c = peek();
        if (c == '"') return string().has_value();
        if (c == '{' || c == '[') {
            const char close = c == '{' ? '}' : ']';
            ++p_;
            while (true) {
                ws();
                if (peek() == close) { ++p_; return true; }
                if (c == '{') {
                    if (!string() || !expect(':')) return false;
                }
                if (!skip_value()) return false;
                ws();
                if (peek() == ',') ++p_;
            }
        }
        return scalar().has_value();
    }

    std::optional<ManifestEntry> entry() {
        if (!expect('{')) return std::nullopt;
        ManifestEntry e;
        while (true) {
            ws();
            if (peek() == '}') { ++p_; return e; }
            auto key = string();
            if (!key || !expect(':')) return std::nullopt;
            ws();
            if (*key == "path" || *key == "container") {
                auto v = string();
                if (!v) return std::nullopt;
                (*key == "path" ? e.path : e.container) = std::move(*v);
            } else if (*key == "size" || *key == "lba") {
                auto v = scalar();
                if (!v) return std::nullopt;
                const u64 n = std::strtoull(std::string(*v).c_str(), nullptr, 10);
                if (*key == "size") e.size = n; else e.lba = static_cast<u32>(n);
            } else if (!skip_value()) {
                return std::nullopt;
            }
            ws();
            if (peek() == ',') ++p_;
        }
    }

    std::string_view s_;
    std::size_t p_ = 0;
};

inline std::optional<std::vector<ManifestEntry>> load_manifest() {
    auto bytes = read_host_file(extracted_dir() / "manifest.json");
    if (!bytes) return std::nullopt;
    ManifestReader rd(std::string_view(reinterpret_cast<const char*>(bytes->data()), bytes->size()));
    return rd.entries();
}

// ---- synthetic ISO9660 image (our own bytes; no game data) ----------------------------------

inline constexpr u32 kSynthSectors = 512;  // 1 MiB
inline constexpr u32 kSynthDataLsn = 24;   // DATA.BIN extent
inline constexpr u32 kSynthDataSize = 40'000;

inline std::byte synth_data_byte(u32 lsn, u32 i) { return static_cast<std::byte>((lsn * 31u + i * 7u + 3u) & 0xFFu); }

struct SynthOptions {
    std::string system_cnf = "BOOT2 = cdrom0:\\SLUS_216.21;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n";
    bool with_system_cnf = true;
    bool with_pvd = true;
    u32 extra_bytes = 0;  // appended after the last sector (non-2048-multiple images)
};

inline void put_u16_both(std::vector<std::byte>& b, std::size_t off, u16 v) {
    b[off] = std::byte(v & 0xFF); b[off + 1] = std::byte(v >> 8);
    b[off + 2] = std::byte(v >> 8); b[off + 3] = std::byte(v & 0xFF);
}
inline void put_u32_both(std::vector<std::byte>& b, std::size_t off, u32 v) {
    for (int i = 0; i < 4; ++i) b[off + i] = std::byte((v >> (8 * i)) & 0xFF);
    for (int i = 0; i < 4; ++i) b[off + 4 + i] = std::byte((v >> (8 * (3 - i))) & 0xFF);
}

// Appends one directory record at `off`; returns the next offset.
inline std::size_t put_dir_record(std::vector<std::byte>& b, std::size_t off, std::string_view id, u32 lsn, u32 size,
                                  u8 flags) {
    const std::size_t len = 33 + id.size() + ((id.size() % 2 == 0) ? 1 : 0);  // pad to even length
    b[off] = std::byte(static_cast<u8>(len));
    put_u32_both(b, off + 2, lsn);
    put_u32_both(b, off + 10, size);
    b[off + 25] = std::byte(flags);
    put_u16_both(b, off + 28, 1);  // volume sequence number
    b[off + 32] = std::byte(static_cast<u8>(id.size()));
    std::memcpy(b.data() + off + 33, id.data(), id.size());
    return off + len;
}

// Layout: 16 PVD, 17 terminator, 18 root {DATA.BIN;1 @24, SUB/ @19, SYSTEM.CNF;1 @20},
// 19 SUB {INNER.TXT;1 @21}, 20 SYSTEM.CNF, 21 "HELLO", 24.. DATA.BIN pattern.
inline std::vector<std::byte> make_synthetic_iso(const SynthOptions& o = {}) {
    constexpr std::size_t S = hle::kSectorSize;
    std::vector<std::byte> b(static_cast<std::size_t>(kSynthSectors) * S + o.extra_bytes, std::byte{0});
    auto at = [&](u32 lsn) { return static_cast<std::size_t>(lsn) * S; };
    if (o.with_pvd) {
        const std::size_t p = at(16);
        b[p] = std::byte{1};
        std::memcpy(b.data() + p + 1, "CD001", 5);
        b[p + 6] = std::byte{1};
        put_u32_both(b, p + 80, kSynthSectors);
        put_u16_both(b, p + 120, 1);
        put_u16_both(b, p + 124, 1);
        put_u16_both(b, p + 128, static_cast<u16>(S));
        put_dir_record(b, p + 156, std::string_view("\0", 1), 18, static_cast<u32>(S), 0x02);
        const std::size_t t = at(17);
        b[t] = std::byte{255};
        std::memcpy(b.data() + t + 1, "CD001", 5);
        b[t + 6] = std::byte{1};
    }
    std::size_t r = at(18);
    r = put_dir_record(b, r, std::string_view("\0", 1), 18, static_cast<u32>(S), 0x02);
    r = put_dir_record(b, r, std::string_view("\1", 1), 18, static_cast<u32>(S), 0x02);
    r = put_dir_record(b, r, "DATA.BIN;1", kSynthDataLsn, kSynthDataSize, 0);
    r = put_dir_record(b, r, "SUB", 19, static_cast<u32>(S), 0x02);
    if (o.with_system_cnf)
        put_dir_record(b, r, "SYSTEM.CNF;1", 20, static_cast<u32>(o.system_cnf.size()), 0);
    std::size_t d = at(19);
    d = put_dir_record(b, d, std::string_view("\0", 1), 19, static_cast<u32>(S), 0x02);
    d = put_dir_record(b, d, std::string_view("\1", 1), 18, static_cast<u32>(S), 0x02);
    put_dir_record(b, d, "INNER.TXT;1", 21, 5, 0);
    std::memcpy(b.data() + at(20), o.system_cnf.data(), o.system_cnf.size());
    std::memcpy(b.data() + at(21), "HELLO", 5);
    for (u32 i = 0; i < kSynthDataSize; ++i) {
        const u32 lsn = kSynthDataLsn + i / static_cast<u32>(S);
        b[at(kSynthDataLsn) + i] = synth_data_byte(lsn, i % static_cast<u32>(S));
    }
    return b;
}

// A uniquely named file in the temp directory, removed on destruction.
class TempFile {
public:
    explicit TempFile(const std::vector<std::byte>& bytes, std::string_view ext = ".iso") {
        static unsigned counter = 0;
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        path_ = std::filesystem::temp_directory_path() /
                ("p3fes_hle_" + std::to_string(stamp) + "_" + std::to_string(++counter) + std::string(ext));
        std::ofstream f(path_, std::ios::binary);
        f.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    }
    ~TempFile() {
        std::error_code ec;
        std::filesystem::remove_all(path_, ec);
    }
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;
    const std::filesystem::path& path() const { return path_; }

private:
    std::filesystem::path path_;
};

inline std::unique_ptr<hle::IsoFileSource> open_synthetic(const TempFile& f) {
    auto r = hle::IsoFileSource::open(f.path());
    REQUIRE_MESSAGE(r.ok(), formats::error_name(r.code()) << ": " << r.detail());
    return std::move(r).value();
}

}  // namespace p3fes::test

// Skips the current test case (doctest MESSAGE + return) when `ptr` is null.
#define P3FES_SKIP_UNLESS(ptr, what)                         \
    if (!(ptr)) {                                            \
        MESSAGE("skipped: " << what << " not present");      \
        return;                                              \
    }
