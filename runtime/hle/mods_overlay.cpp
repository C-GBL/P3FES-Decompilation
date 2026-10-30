// ModsOverlay: the virtual disc of ADR-0016. See p3fes/hle/mods_overlay.h for the design and the guest's view.
#include "p3fes/hle/mods_overlay.h"

#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <system_error>

#include "host_file.h"
#include "iso9660.h"

namespace p3fes::hle {

namespace {

constexpr u32 S = kSectorSize;

char up(char c) { return (c >= 'a' && c <= 'z') ? static_cast<char>(c - 'a' + 'A') : c; }
std::string upper(std::string_view s) {
    std::string o(s);
    for (char& c : o) c = up(c);
    return o;
}
bool iequal(std::string_view a, std::string_view b) { return upper(a) == upper(b); }
std::string_view strip_version(std::string_view s) {
    const std::size_t semi = s.find(';');
    return semi == std::string_view::npos ? s : s.substr(0, semi);
}
std::string u8str(const std::filesystem::path& p) {
    const std::u8string s = p.u8string();
    return std::string(reinterpret_cast<const char*>(s.data()), s.size());
}
std::string hex32(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%X", v);
    return b;
}

void put_both32(std::byte* p, u32 v) {
    for (int i = 0; i < 4; ++i) p[i] = static_cast<std::byte>((v >> (8 * i)) & 0xFF);
    for (int i = 0; i < 4; ++i) p[4 + i] = static_cast<std::byte>((v >> (8 * (3 - i))) & 0xFF);
}
u64 ld_be64(const std::byte* p) {
    u64 v = 0;
    for (int i = 0; i < 8; ++i) v = (v << 8) | std::to_integer<u64>(p[i]);
    return v;
}
void st_be64(std::byte* p, u64 v) {
    for (int i = 0; i < 8; ++i) p[i] = static_cast<std::byte>((v >> (8 * (7 - i))) & 0xFF);
}
u32 ld_be32(const std::byte* p) {
    return (std::to_integer<u32>(p[0]) << 24) | (std::to_integer<u32>(p[1]) << 16) | (std::to_integer<u32>(p[2]) << 8) |
           std::to_integer<u32>(p[3]);
}
u32 ld_le32(const std::byte* p) {
    return std::to_integer<u32>(p[0]) | (std::to_integer<u32>(p[1]) << 8) | (std::to_integer<u32>(p[2]) << 16) |
           (std::to_integer<u32>(p[3]) << 24);
}
void st_le32(std::byte* p, u32 v) {
    for (int i = 0; i < 4; ++i) p[i] = static_cast<std::byte>((v >> (8 * i)) & 0xFF);
}

// A window onto `count` sectors of another source starting at `first` (a CVM's inner ISO9660 image).
class OffsetView final : public DiscSource {
public:
    OffsetView(DiscSource& base, u32 first, u32 count) : base_(base), first_(first) { id_.sectors = count; }
    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override {
        auto bytes = check_read(lsn, count, dst);
        if (!bytes) return bytes.error();
        return base_.read_sectors(first_ + lsn, count, dst);
    }
    u32 sector_count() const override { return id_.sectors; }
    const DiscIdentity& identity() const override { return id_; }

private:
    DiscSource& base_;
    u32 first_;
    DiscIdentity id_;
};

// Normalised form of a disc query ("\DATA.CVM;1" -> "DATA.CVM").
std::string normalise_query(std::string_view path) {
    std::string out;
    for (std::string_view c : iso9660::split_path(path)) {
        if (!out.empty()) out += '\\';
        out += upper(strip_version(c));
    }
    return out;
}

std::vector<std::string> split_norm(std::string_view norm) {
    std::vector<std::string> out;
    for (std::string_view c : iso9660::split_path(norm)) out.emplace_back(c);
    return out;
}

// A file located through directory records: its record and the directory holding it.
struct Located {
    iso9660::Record rec;
    iso9660::Record parent;
};

Result<std::optional<Located>> locate(DiscSource& disc, const iso9660::Volume& vol, const std::vector<std::string>& comps,
                                      std::size_t first) {
    iso9660::Record dir = vol.root;
    for (std::size_t i = first; i < comps.size(); ++i) {
        auto entries = iso9660::read_directory(disc, vol, dir);
        if (!entries) return entries.error();
        const iso9660::Record* hit = nullptr;
        for (const iso9660::Record& r : entries.value())
            if (iso9660::component_matches(r.identifier, comps[i])) {
                hit = &r;
                break;
            }
        if (hit == nullptr) return std::optional<Located>{};
        if (i + 1 == comps.size()) return std::optional<Located>{Located{*hit, dir}};
        if (!hit->is_directory()) return std::optional<Located>{};
        dir = *hit;
    }
    return std::optional<Located>{};
}

// Every file under `dir` (recursively, bounded depth): emit(first sector + record LBA, sectors, "PREFIX\NAME").
void walk_files(DiscSource& disc, const iso9660::Volume& vol, const iso9660::Record& dir, const std::string& prefix,
                u32 first, int depth, const std::function<bool(const iso9660::Record&)>& skip,
                const std::function<void(u32, u32, std::string)>& emit) {
    if (depth > 16) return;
    auto entries = iso9660::read_directory(disc, vol, dir);
    if (!entries) return;
    for (const iso9660::Record& r : entries.value()) {
        if (skip && skip(r)) continue;
        const std::string name = prefix + upper(strip_version(r.identifier));
        if (r.is_directory()) walk_files(disc, vol, r, name + "\\", first, depth + 1, skip, emit);
        else emit(first + r.lsn, (r.size + S - 1) / S, name);
    }
}

bool is_reparse(const std::filesystem::path& p) {
    const DWORD a = ::GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
}

// ---- a small JSON reader for mod.json ---------------------------------------------------------
class Json {
public:
    explicit Json(std::string_view s) : s_(s) {}
    Result<ModInfo> top() {
        ModInfo info;
        info.has_manifest = true;
        ws();
        if (peek() != '{') return bad("mod.json: the top level is not an object");
        ++p_;
        ws();
        if (peek() == '}') {
            ++p_;
            return finish(info);
        }
        while (true) {
            ws();
            std::string key;
            if (!string(key)) return bad("mod.json: expected a string key");
            ws();
            if (peek() != ':') return bad("mod.json: expected ':'");
            ++p_;
            ws();
            if (key == "name" || key == "description") {
                std::string v;
                if (!string(v)) return bad("mod.json: \"name\" / \"description\" is not a string");
                (key == "name" ? info.name : info.description) = std::move(v);
            } else if (key == "load_order") {
                double d = 0;
                if (!number(d)) return bad("mod.json: \"load_order\" is not a number");
                if (d != static_cast<double>(static_cast<long long>(d)) || d > 1e15 || d < -1e15)
                    return bad("mod.json: \"load_order\" is not an integer");
                info.load_order = static_cast<long long>(d);
            } else if (!skip(0)) {
                return bad("mod.json: malformed value");
            }
            ws();
            if (peek() == ',') {
                ++p_;
                continue;
            }
            if (peek() == '}') {
                ++p_;
                return finish(info);
            }
            return bad("mod.json: expected ',' or '}'");
        }
    }

private:
    Result<ModInfo> finish(ModInfo& info) {
        ws();
        if (p_ != s_.size()) return bad("mod.json: text after the object");
        return info;
    }
    static Error bad(const char* m) { return Error{FormatError::BadHeader, m}; }
    char peek() const { return p_ < s_.size() ? s_[p_] : '\0'; }
    void ws() {
        while (p_ < s_.size() && (s_[p_] == ' ' || s_[p_] == '\t' || s_[p_] == '\r' || s_[p_] == '\n')) ++p_;
    }
    static int hexv(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;
    }
    bool string(std::string& out) {
        if (peek() != '"') return false;
        ++p_;
        while (p_ < s_.size()) {
            const char c = s_[p_++];
            if (c == '"') return true;
            if (static_cast<unsigned char>(c) < 0x20) return false;
            if (c != '\\') {
                out += c;
                continue;
            }
            if (p_ >= s_.size()) return false;
            const char e = s_[p_++];
            switch (e) {
                case '"': out += '"'; break;
                case '\\': out += '\\'; break;
                case '/': out += '/'; break;
                case 'b': out += '\b'; break;
                case 'f': out += '\f'; break;
                case 'n': out += '\n'; break;
                case 'r': out += '\r'; break;
                case 't': out += '\t'; break;
                case 'u': {
                    if (p_ + 4 > s_.size()) return false;
                    unsigned v = 0;
                    for (int i = 0; i < 4; ++i) {
                        const int h = hexv(s_[p_++]);
                        if (h < 0) return false;
                        v = (v << 4) | static_cast<unsigned>(h);
                    }
                    if (v >= 0xD800 && v <= 0xDFFF) v = '?';  // surrogate halves: not needed for names
                    if (v < 0x80) {
                        out += static_cast<char>(v);
                    } else if (v < 0x800) {
                        out += static_cast<char>(0xC0 | (v >> 6));
                        out += static_cast<char>(0x80 | (v & 0x3F));
                    } else {
                        out += static_cast<char>(0xE0 | (v >> 12));
                        out += static_cast<char>(0x80 | ((v >> 6) & 0x3F));
                        out += static_cast<char>(0x80 | (v & 0x3F));
                    }
                    break;
                }
                default: return false;
            }
        }
        return false;
    }
    bool number(double& out) {
        const std::size_t b = p_;
        if (peek() == '-') ++p_;
        if (!(peek() >= '0' && peek() <= '9')) return false;
        while (peek() >= '0' && peek() <= '9') ++p_;
        if (peek() == '.') {
            ++p_;
            if (!(peek() >= '0' && peek() <= '9')) return false;
            while (peek() >= '0' && peek() <= '9') ++p_;
        }
        if (peek() == 'e' || peek() == 'E') {
            ++p_;
            if (peek() == '+' || peek() == '-') ++p_;
            if (!(peek() >= '0' && peek() <= '9')) return false;
            while (peek() >= '0' && peek() <= '9') ++p_;
        }
        out = std::strtod(std::string(s_.substr(b, p_ - b)).c_str(), nullptr);
        return true;
    }
    bool literal(std::string_view w) {
        if (s_.substr(p_, w.size()) != w) return false;
        p_ += w.size();
        return true;
    }
    bool skip(int depth) {
        if (depth > 64) return false;
        ws();
        const char c = peek();
        if (c == '"') {
            std::string t;
            return string(t);
        }
        if (c == '{' || c == '[') {
            const char close = c == '{' ? '}' : ']';
            ++p_;
            ws();
            if (peek() == close) {
                ++p_;
                return true;
            }
            while (true) {
                ws();
                if (c == '{') {
                    std::string k;
                    if (!string(k)) return false;
                    ws();
                    if (peek() != ':') return false;
                    ++p_;
                }
                if (!skip(depth + 1)) return false;
                ws();
                if (peek() == ',') {
                    ++p_;
                    continue;
                }
                if (peek() == close) {
                    ++p_;
                    return true;
                }
                return false;
            }
        }
        if (c == 't') return literal("true");
        if (c == 'f') return literal("false");
        if (c == 'n') return literal("null");
        double d;
        return number(d);
    }

    std::string_view s_;
    std::size_t p_ = 0;
};

}  // namespace

// ---- free functions ----------------------------------------------------------------------------

Result<ModInfo> parse_mod_json(std::string_view text) {
    if (text.size() >= 3 && static_cast<unsigned char>(text[0]) == 0xEF && static_cast<unsigned char>(text[1]) == 0xBB &&
        static_cast<unsigned char>(text[2]) == 0xBF)
        text.remove_prefix(3);  // UTF-8 BOM (Notepad)
    return Json(text).top();
}

Result<std::string> normalise_mod_path(std::string_view rel) {
    auto no = [](const char* m) { return Error{FormatError::Unsupported, m}; };
    if (rel.empty()) return no("empty path");
    if (rel.front() == '\\' || rel.front() == '/') return no("absolute path");
    if (rel.size() >= 2 && rel[1] == ':') return no("drive path");
    std::string out;
    std::size_t i = 0;
    while (i <= rel.size()) {
        std::size_t j = i;
        while (j < rel.size() && rel[j] != '\\' && rel[j] != '/') ++j;
        const std::string_view c = rel.substr(i, j - i);
        if (c.empty()) return no("empty path component");
        if (c == "." || c == "..") return no("'.' or '..' component (escapes the mod root)");
        for (const char ch : c) {
            const auto u = static_cast<unsigned char>(ch);
            if (u < 0x20 || u >= 0x7F) return no("non-ASCII or control character (disc names are ASCII)");
            if (std::strchr(":;*?\"<>|", ch) != nullptr) return no("reserved character (: ; * ? \" < > |) in a component");
        }
        if (!out.empty()) out += '\\';
        out += upper(c);
        if (j >= rel.size()) break;
        i = j + 1;
    }
    return out;
}

// ---- internals ----------------------------------------------------------------------------------

struct ModsOverlay::Cvm {
    std::string identifier;  // as recorded, "DATA.CVM;1"
    std::string host_name;   // "DATA.CVM"
    std::string base_name;   // "DATA"
    DiscFile file;           // the base extent
    u32 header_sectors = kCvmHeaderSectors;
    u32 window = 0, cursor = 0, window_end = 0;
    std::unique_ptr<OffsetView> inner_view;  // the inner ISO9660 image, read from the base
    iso9660::Volume inner;
    bool outer_record = false;               // its root record was found (ISO base)
    u32 outer_record_lsn = 0;
    std::size_t outer_record_off = 0;
};

struct ModsOverlay::Extent {
    std::string disc_path, mod_name, identifier;
    std::filesystem::path host_path;
    std::filesystem::file_time_type mtime{};
    std::shared_ptr<const std::vector<std::byte>> snap;  // the bytes at scan time; null: read the host file per read
    std::array<u8, 7> recorded{};
    int cvm = -1;  // -1: an outer file
    u32 lsn = 0, sectors = 0, size = 0, lba = 0, generation = 0;
    u32 original_lsn = 0, original_size = 0, original_lba = 0;
    iso9660::Record parent;  // the directory holding the record (inner LBAs for CVM members)
    std::size_t record_off = 0;
};

struct ModsOverlay::Region {
    u32 start = 0, count = 0;
    u32 base_lsn = 0;           // Base
    const Extent* ext = nullptr;  // non-null: an extent
};

struct ModsOverlay::Table {
    std::size_t offset = 0;  // header offset in the image
    u32 count = 0, dir_lba = 0, dir_size = 0;
    std::vector<std::byte> original;           // 48 * count entry bytes as loaded
    std::map<int, bool> belongs;               // cvm index -> its directory at dir_lba is this table
    std::vector<bool> written;                 // entries currently patched
};

struct ModsOverlay::Pending {
    std::string disc_path, mod_name;
    std::filesystem::path host_path;
    std::filesystem::file_time_type mtime{};
    u64 size = 0;
};

ModsOverlay::ModsOverlay(std::unique_ptr<DiscSource> base, ModsOptions options)
    : base_(std::move(base)), opt_(std::move(options)) {}
ModsOverlay::~ModsOverlay() = default;

void ModsOverlay::log(std::string_view s) const {
    if (opt_.log) opt_.log(s);
}

Result<std::unique_ptr<ModsOverlay>> ModsOverlay::open(std::unique_ptr<DiscSource> base, ModsOptions options) {
    if (!base) return Error{FormatError::Unsupported, "mods overlay without a disc"};
    if (base->sector_count() > kModsFirstWindow)
        return Error{FormatError::Unsupported, "disc larger than the first mods window"};
    std::unique_ptr<ModsOverlay> o(new ModsOverlay(std::move(base), std::move(options)));
    auto lay = o->init_layout();
    if (!lay) return lay.error();
    auto sc = o->rescan();
    if (!sc) return sc.error();
    return o;
}

Result<std::size_t> ModsOverlay::init_layout() {
    identity_ = base_->identity();
    // Candidate root names: the ISO root listing, or the fixed table of the extracted volumes.
    std::vector<std::pair<std::string, std::optional<iso9660::Record>>> roots;
    if (auto vol = iso9660::read_volume(*base_); vol) {
        auto root = iso9660::read_directory(*base_, vol.value(), vol->root);
        if (!root) return root.error();
        base_has_iso_ = true;
        for (const iso9660::Record& r : root.value()) roots.emplace_back(r.identifier, r);
    } else {
        for (const DiscLayoutEntry& e : kDiscLayout) roots.emplace_back(std::string(e.identifier), std::nullopt);
    }
    u32 next = kModsFirstWindow;
    for (const auto& [ident, rec] : roots) {
        const std::string name = upper(strip_version(ident));
        if (name.size() < 5 || name.substr(name.size() - 4) != ".CVM") continue;
        if (rec && rec->is_directory()) continue;
        auto f = base_->find_file("\\" + ident);
        if (!f || !f->has_value()) continue;
        const DiscFile file = *f.value();
        std::vector<std::byte> hdr(S);
        if (file.sectors() < 2 || !base_->read_sectors(file.lsn, 1, hdr)) continue;
        if (std::memcmp(hdr.data(), "CVMH", 4) != 0) {
            log("mods: " + name + " has no CVMH header; not treated as a CVM");
            continue;
        }
        Cvm c;
        c.identifier = ident;
        c.host_name = name;
        c.base_name = name.substr(0, name.size() - 4);
        c.file = file;
        c.header_sectors = ld_be32(hdr.data() + 136);
        if (c.header_sectors == 0 || c.header_sectors + 17 > file.sectors()) {
            log("mods: " + name + " has an unexpected CVM data offset; not treated as a CVM");
            continue;
        }
        if (opt_.cvm_window_sectors < file.sectors() || opt_.cvm_window_sectors > kModsCvmWindowSectors)
            return Error{FormatError::Unsupported, "a CVM is larger than the mods CVM window"};
        c.inner_view = std::make_unique<OffsetView>(*base_, file.lsn + c.header_sectors, file.sectors() - c.header_sectors);
        auto iv = iso9660::read_volume(*c.inner_view);
        if (!iv) {
            log("mods: " + name + " holds no readable ISO9660 image; not treated as a CVM");
            continue;
        }
        c.inner = iv.value();
        c.window = next;
        c.cursor = next + file.sectors();
        c.window_end = next + opt_.cvm_window_sectors;
        next += kModsWindowSectors;
        cvms_.push_back(std::move(c));
    }
    // The outer root records of the CVMs (to patch their LSN / size).
    if (base_has_iso_) {
        auto vol = iso9660::read_volume(*base_);
        auto root = iso9660::read_directory(*base_, vol.value(), vol->root);
        for (Cvm& c : cvms_)
            for (const iso9660::Record& r : root.value())
                if (r.identifier == c.identifier) {
                    c.outer_record = true;
                    c.outer_record_lsn = vol->root.lsn + static_cast<u32>(r.dir_offset / S);
                    c.outer_record_off = r.dir_offset % S;
                }
    }
    outer_window_ = next;
    outer_cursor_ = next;
    identity_.sectors = next + kModsWindowSectors;
    // The read index: CVM members at their relocated LSNs, outer files (ISO base) at theirs.
    auto emit = [this](u32 start, u32 count, std::string path) { files_.push_back(FileSpan{start, count, std::move(path)}); };
    for (const Cvm& c : cvms_)
        walk_files(*c.inner_view, c.inner, c.inner.root, c.base_name + "\\", c.window + c.header_sectors, 0, nullptr, emit);
    if (base_has_iso_) {
        auto vol = iso9660::read_volume(*base_);
        auto is_cvm = [this](const iso9660::Record& r) {
            for (const Cvm& c : cvms_)
                if (r.identifier == c.identifier) return true;
            return false;
        };
        walk_files(*base_, vol.value(), vol->root, "", 0, 0, is_cvm, emit);
    }
    std::sort(files_.begin(), files_.end(), [](const FileSpan& a, const FileSpan& b) { return a.start < b.start; });
    for (const Cvm& c : cvms_)
        log("mods: " + c.host_name + " (LSN " + std::to_string(c.file.lsn) + ", " + std::to_string(c.file.size) +
            " B) relocated to LSN " + std::to_string(c.window) + ", reported size " +
            std::to_string(static_cast<u64>(opt_.cvm_window_sectors) * S) + " B");
    return cvms_.size();
}

Result<std::vector<std::byte>*> ModsOverlay::patch_sector(u32 vlsn) {
    auto it = patched_.find(vlsn);
    if (it != patched_.end()) return &it->second;
    std::vector<std::byte> s(S);
    auto rd = read_unpatched(vlsn, 1, s);  // patched_ does not hold vlsn yet
    if (!rd) return rd.error();
    return &patched_.emplace(vlsn, std::move(s)).first->second;
}

void ModsOverlay::rebuild_regions() {
    regions_.clear();
    regions_.push_back(Region{0, base_->sector_count(), 0, nullptr});
    for (const Cvm& c : cvms_) regions_.push_back(Region{c.window, c.file.sectors(), c.file.lsn, nullptr});
    for (const auto& e : extents_)
        if (e->sectors) regions_.push_back(Region{e->lsn, e->sectors, 0, e.get()});
    std::sort(regions_.begin(), regions_.end(), [](const Region& a, const Region& b) { return a.start < b.start; });
}

Result<std::size_t> ModsOverlay::read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) {
    auto bytes = check_read(lsn, count, dst);
    if (!bytes) return bytes.error();
    auto rd = read_unpatched(lsn, count, dst);
    if (!rd) return rd.error();
    for (auto p = patched_.lower_bound(lsn); p != patched_.end() && p->first < lsn + count; ++p)
        std::memcpy(dst.data() + static_cast<std::size_t>(p->first - lsn) * S, p->second.data(), S);
    note_read(lsn, count);
    return bytes.value();
}

void ModsOverlay::note_file(const std::string& path) {
    if (!reads_.insert(path).second) return;
    reads_ever_.insert(path);
    reads_list_.insert(std::lower_bound(reads_list_.begin(), reads_list_.end(), path), path);
    if (read_observer_) read_observer_(path);
}

void ModsOverlay::note_read(u32 lsn, u32 count) {
    const u64 end = static_cast<u64>(lsn) + count;
    auto overlaps = [&](u32 start, u32 n) { return start < end && static_cast<u64>(start) + std::max<u32>(n, 1) > lsn; };
    auto f = std::upper_bound(files_.begin(), files_.end(), lsn, [](u32 v, const FileSpan& s) { return v < s.start; });
    if (f != files_.begin()) --f;
    for (; f != files_.end() && f->start < end; ++f)
        if (overlaps(f->start, f->count)) note_file(f->path);
    auto r = std::upper_bound(regions_.begin(), regions_.end(), lsn, [](u32 v, const Region& g) { return v < g.start; });
    if (r != regions_.begin()) --r;
    for (; r != regions_.end() && r->start < end; ++r)
        if (r->ext != nullptr && overlaps(r->start, r->count)) note_file(r->ext->disc_path);
}

std::size_t ModsOverlay::rofs_table_count() const { return tables_.size(); }

void ModsOverlay::clear_reads() {
    reads_.clear();
    reads_list_.clear();
}

Result<std::size_t> ModsOverlay::read_unpatched(u32 lsn, u32 count, std::span<std::byte> dst) {
    auto bytes = check_read(lsn, count, dst);
    if (!bytes) return bytes.error();
    u32 cur = lsn;
    std::size_t at = 0;
    while (cur < lsn + count) {
        const u32 rem = lsn + count - cur;
        auto it = std::upper_bound(regions_.begin(), regions_.end(), cur,
                                   [](u32 v, const Region& r) { return v < r.start; });
        const Region* hit = nullptr;
        if (it != regions_.begin()) {
            const Region& r = *(it - 1);
            if (cur < r.start + r.count) hit = &r;
        }
        if (hit == nullptr) {
            const u32 gap_end = it != regions_.end() ? it->start : sector_count();
            const u32 n = std::min(rem, gap_end - cur);
            std::memset(dst.data() + at, 0, static_cast<std::size_t>(n) * S);
            cur += n;
            at += static_cast<std::size_t>(n) * S;
            continue;
        }
        const u32 n = std::min(rem, hit->start + hit->count - cur);
        const std::span<std::byte> part = dst.subspan(at, static_cast<std::size_t>(n) * S);
        if (hit->ext == nullptr) {
            auto rd = base_->read_sectors(hit->base_lsn + (cur - hit->start), n, part);
            if (!rd) return rd.error();
        } else {
            const Extent& e = *hit->ext;
            const u64 off = static_cast<u64>(cur - e.lsn) * S;
            const u64 valid = off >= e.size ? 0 : std::min<u64>(e.size - off, part.size());
            if (valid && e.snap) {
                std::memcpy(part.data(), e.snap->data() + off, static_cast<std::size_t>(valid));
            } else if (valid) {  // not kept in memory: the host file as it is now (opened per read, so never locked)
                auto f = HostFile::open_shared(e.host_path);
                if (!f) return f.error();
                auto rd = f.value()->read_zero_fill(off, part.first(static_cast<std::size_t>(valid)));
                if (!rd) return rd.error();
            }
            if (valid < part.size()) std::memset(part.data() + valid, 0, part.size() - static_cast<std::size_t>(valid));
        }
        cur += n;
        at += part.size();
    }
    return bytes.value();
}

Result<std::optional<DiscFile>> ModsOverlay::find_file(std::string_view path) {
    const std::string norm = normalise_query(path);
    for (const Cvm& c : cvms_)
        if (norm == c.host_name) {
            auto r = base_->find_file(path);
            if (!r || !r->has_value()) return r;
            DiscFile f = *r.value();
            f.lsn = c.window;
            f.size = opt_.cvm_window_sectors * S;
            return std::optional<DiscFile>{f};
        }
    if (auto it = live_.find(norm); it != live_.end() && it->second->cvm < 0) {
        const Extent& e = *it->second;
        return std::optional<DiscFile>{DiscFile{e.lsn, e.size, e.identifier, e.recorded}};
    }
    return base_->find_file(path);
}

std::optional<u32> ModsOverlay::cvm_lsn(std::string_view host_name) const {
    for (const Cvm& c : cvms_)
        if (iequal(c.host_name, host_name)) return c.window;
    return std::nullopt;
}

std::string ModsOverlay::fingerprint() const {
    u64 h = 0xcbf29ce484222325ull;
    auto mix = [&](const void* p, std::size_t n) {
        const auto* b = static_cast<const unsigned char*>(p);
        for (std::size_t i = 0; i < n; ++i) h = (h ^ b[i]) * 0x100000001b3ull;
    };
    for (const auto& [path, e] : live_) {
        mix(path.data(), path.size());
        mix(&e->lsn, sizeof e->lsn);
        mix(&e->size, sizeof e->size);
        const auto t = e->mtime.time_since_epoch().count();
        mix(&t, sizeof t);
    }
    char b[24];
    std::snprintf(b, sizeof b, "%016llx", static_cast<unsigned long long>(h));
    return b;
}

Result<std::size_t> ModsOverlay::reload() {
    auto r = rescan();
    if (!r) log("mods: reload failed: " + std::string(formats::error_name(r.code())) + " " + r.detail());
    return r;
}

Result<std::size_t> ModsOverlay::rescan() {
    const std::vector<std::filesystem::path> none;
    const std::vector<std::filesystem::path>& dirs = opt_.enabled ? opt_.dirs : none;
    for (const auto& d : dirs) {
        std::error_code ec;
        if (!std::filesystem::is_directory(d, ec)) {
            log("mods: " + u8str(d) + " is not a directory");
            return Error{FormatError::BadHeader, "a --mods folder is not a directory"};
        }
    }
    ModsScan next;
    next.generation = scans_++;
    auto reject = [&](std::string line) {
        log("mods: refused " + line);
        next.rejected.push_back(std::move(line));
    };

    // Root names: what makes a folder a single mod rather than a folder of mods.
    std::vector<std::string> root_names;
    for (const Cvm& c : cvms_) root_names.push_back(c.base_name);
    if (base_has_iso_) {
        if (auto vol = iso9660::read_volume(*base_); vol)
            if (auto root = iso9660::read_directory(*base_, vol.value(), vol->root); root)
                for (const iso9660::Record& r : root.value()) root_names.push_back(upper(strip_version(r.identifier)));
    } else {
        for (const DiscLayoutEntry& e : kDiscLayout) root_names.push_back(upper(strip_version(e.identifier)));
        for (std::string_view d : kDiscRootDirectories) root_names.push_back(upper(d));
    }
    auto read_manifest = [&](const std::filesystem::path& root) {
        ModInfo info;
        info.root = root;
        info.name = u8str(root.filename());
        const std::filesystem::path mj = root / "mod.json";
        std::error_code ec;
        if (!std::filesystem::is_regular_file(mj, ec)) return info;
        if (is_reparse(mj)) {
            reject(u8str(mj) + ": reparse point / symlink");
            return info;
        }
        auto f = HostFile::open_shared(mj);
        if (!f || f.value()->size() > 1u << 20) {
            reject(u8str(mj) + ": unreadable or larger than 1 MiB (defaults used)");
            return info;
        }
        std::string text(static_cast<std::size_t>(f.value()->size()), '\0');
        if (!f.value()->read_at(0, std::as_writable_bytes(std::span(text)))) {
            reject(u8str(mj) + ": unreadable (defaults used)");
            return info;
        }
        auto parsed = parse_mod_json(text);
        if (!parsed) {
            reject(u8str(mj) + ": " + parsed.detail() + " (defaults used)");
            return info;
        }
        ModInfo m = std::move(parsed).value();
        m.root = root;
        if (m.name.empty()) m.name = info.name;
        return m;
    };
    for (const auto& dir : dirs) {
        std::error_code ec;
        bool single = std::filesystem::is_regular_file(dir / "mod.json", ec);
        for (const auto& e : std::filesystem::directory_iterator(dir, ec))
            for (const std::string& n : root_names)
                if (upper(u8str(e.path().filename())) == n) single = true;
        if (single) {
            next.mods.push_back(read_manifest(dir));
            continue;
        }
        std::vector<ModInfo> group;
        for (const auto& e : std::filesystem::directory_iterator(dir, ec)) {
            std::error_code ec2;
            if (!e.is_directory(ec2)) continue;
            if (is_reparse(e.path()) || e.is_symlink(ec2)) {
                reject(u8str(e.path()) + ": reparse point / symlink");
                continue;
            }
            group.push_back(read_manifest(e.path()));
        }
        std::sort(group.begin(), group.end(), [](const ModInfo& a, const ModInfo& b) {
            if (a.load_order != b.load_order) return a.load_order < b.load_order;
            return upper(u8str(a.root.filename())) < upper(u8str(b.root.filename()));
        });
        for (auto& m : group) next.mods.push_back(std::move(m));
    }

    // Files, later mods winning.
    std::map<std::string, Pending> winners;
    for (const ModInfo& m : next.mods) {
        std::error_code ec;
        std::filesystem::recursive_directory_iterator it(m.root, std::filesystem::directory_options::none, ec), end;
        if (ec) {
            reject(u8str(m.root) + ": cannot list (" + ec.message() + ")");
            continue;
        }
        for (; it != end; it.increment(ec)) {
            if (ec) {
                reject(u8str(m.root) + ": listing stopped (" + ec.message() + ")");
                break;
            }
            const std::filesystem::path& p = it->path();
            std::error_code ec2;
            if (is_reparse(p) || it->is_symlink(ec2)) {
                reject(u8str(p) + ": reparse point / symlink");
                if (it->is_directory(ec2)) it.disable_recursion_pending();
                continue;
            }
            if (it->is_directory(ec2)) continue;
            if (!it->is_regular_file(ec2)) continue;
            const std::filesystem::path rel = p.lexically_relative(m.root);
            if (rel.empty() || rel.is_absolute() || *rel.begin() == "..") {
                reject(u8str(p) + ": outside the mod root");
                continue;
            }
            if (it.depth() == 0 && iequal(u8str(rel), "mod.json")) continue;
            auto norm = normalise_mod_path(u8str(rel.generic_u8string()));
            if (!norm) {
                reject(u8str(p) + ": " + norm.detail());
                continue;
            }
            const u64 size = it->file_size(ec2);
            if (ec2) {
                reject(u8str(p) + ": cannot read its size");
                continue;
            }
            if (size > opt_.max_file_bytes || size > 0xFFFFF800ull) {
                reject(u8str(p) + ": " + std::to_string(size) + " B is above the " + std::to_string(opt_.max_file_bytes) +
                       " B cap");
                continue;
            }
            Pending pd{norm.value(), m.name, p, it->last_write_time(ec2), size};
            winners[norm.value()] = std::move(pd);
        }
    }

    // Resolve against the disc and allocate.
    const std::string boot = [&] {
        std::string b = identity_.system_cnf.boot2;
        if (const std::size_t c = b.find(":\\"); c != std::string::npos) b = b.substr(c + 2);
        return upper(strip_version(b));
    }();
    std::map<std::string, std::shared_ptr<Extent>> live;
    std::vector<std::shared_ptr<Extent>> added;
    for (const auto& [path, pd] : winners) {
        const std::vector<std::string> comps = split_norm(path);
        const Cvm* cvm = nullptr;
        int cvm_index = -1;
        for (std::size_t i = 0; i < cvms_.size(); ++i)
            if (comps.size() >= 2 && comps[0] == cvms_[i].base_name) {
                cvm = &cvms_[i];
                cvm_index = static_cast<int>(i);
            }
        if (comps.size() == 1) {
            bool is_cvm = false;
            for (const Cvm& c : cvms_) is_cvm = is_cvm || comps[0] == c.host_name;
            if (is_cvm || comps[0] == "SYSTEM.CNF" || comps[0] == boot) {
                reject(path + " (" + u8str(pd.host_path) + "): protected disc file (SYSTEM.CNF, the boot ELF, a whole CVM)");
                continue;
            }
        }
        std::optional<Located> loc;
        if (cvm) {
            auto r = locate(*cvm->inner_view, cvm->inner, comps, 1);
            if (!r) {
                reject(path + ": " + std::string(formats::error_name(r.code())) + " " + r.detail());
                continue;
            }
            loc = r.value();
        } else {
            if (!base_has_iso_) {
                reject(path + ": outside the CVMs, and the extracted-volumes source has no ISO directory");
                continue;
            }
            auto vol = iso9660::read_volume(*base_);
            if (!vol) return vol.error();
            auto r = locate(*base_, vol.value(), comps, 0);
            if (!r) {
                reject(path + ": " + std::string(formats::error_name(r.code())) + " " + r.detail());
                continue;
            }
            loc = r.value();
        }
        if (!loc) {
            reject(path + " (" + u8str(pd.host_path) + "): not on the disc (only existing files can be replaced)");
            continue;
        }
        if (loc->rec.is_directory()) {
            reject(path + ": a directory on the disc");
            continue;
        }
        // Unchanged since the last scan: keep its extent.
        if (auto old = live_.find(path); old != live_.end() && old->second->host_path == pd.host_path &&
                                         old->second->size == pd.size && old->second->mtime == pd.mtime &&
                                         old->second->mod_name == pd.mod_name) {
            live.emplace(path, old->second);
            continue;
        }
        const u32 sectors = static_cast<u32>((pd.size + S - 1) / S);
        u32& cursor = cvm ? cvms_[cvm_index].cursor : outer_cursor_;
        const u32 end = cvm ? cvm->window_end : outer_window_ + kModsWindowSectors;
        if (static_cast<u64>(cursor) + sectors > end) {
            reject(path + " (" + u8str(pd.host_path) + "): no room left in the " +
                   (cvm ? cvm->host_name : std::string("outer")) + " window (restart to compact)");
            continue;
        }
        auto f = HostFile::open_shared(pd.host_path);
        if (!f) {
            reject(path + " (" + u8str(pd.host_path) + "): cannot open");
            continue;
        }
        std::shared_ptr<std::vector<std::byte>> snap;
        if (pd.size <= opt_.snapshot_max_file_bytes) {  // kept in memory: old extents keep exactly these bytes
            snap = std::make_shared<std::vector<std::byte>>(static_cast<std::size_t>(pd.size));
            if (!f.value()->read_zero_fill(0, *snap)) {
                reject(path + " (" + u8str(pd.host_path) + "): cannot read");
                continue;
            }
        }
        f.value().reset();  // never hold the file open: the editor must be able to replace it
        auto e = std::make_shared<Extent>();
        e->snap = std::move(snap);
        e->disc_path = path;
        e->mod_name = pd.mod_name;
        e->identifier = loc->rec.identifier;
        e->recorded = loc->rec.recorded;
        e->host_path = pd.host_path;
        e->mtime = pd.mtime;
        e->cvm = cvm_index;
        e->lsn = cursor;
        e->sectors = sectors;
        e->size = static_cast<u32>(pd.size);
        e->generation = next.generation;
        e->original_size = loc->rec.size;
        e->original_lba = loc->rec.lsn;
        e->parent = loc->parent;
        e->record_off = loc->rec.dir_offset;
        if (cvm) {
            e->lba = cursor - cvm->window - cvm->header_sectors;
            e->original_lsn = cvm->file.lsn + cvm->header_sectors + loc->rec.lsn;
        } else {
            e->lba = cursor;
            e->original_lsn = loc->rec.lsn;
        }
        cursor += sectors;
        added.push_back(e);
        live.emplace(path, std::move(e));
    }

    // Commit.
    std::set<std::string> changed;
    for (const auto& e : added) changed.insert(e->disc_path);
    for (const auto& [path, e] : live_)
        if (!live.count(path)) changed.insert(path);
    stale_.clear();
    for (const std::string& p : changed)
        if (reads_ever_.count(p)) stale_.push_back(p);
    for (auto& e : added) extents_.push_back(e);
    live_ = std::move(live);
    // Memory bound: past the budget, superseded extents (oldest first) drop their copy and read the host file.
    u64 kept = 0;
    for (const auto& e : extents_)
        if (e->snap) kept += e->snap->size();
    for (auto& e : extents_) {
        if (kept <= opt_.snapshot_total_bytes) break;
        const auto lv = live_.find(e->disc_path);
        if (!e->snap || (lv != live_.end() && lv->second == e)) continue;
        kept -= e->snap->size();
        e->snap.reset();
    }
    rebuild_regions();
    patched_.clear();
    if (base_has_iso_) {
        auto pvd = patch_sector(iso9660::kPvdLsn);
        if (!pvd) return pvd.error();
        put_both32(pvd.value()->data() + 80, sector_count());
        for (const Cvm& c : cvms_) {
            if (!c.outer_record) continue;
            auto s = patch_sector(c.outer_record_lsn);
            if (!s) return s.error();
            put_both32(s.value()->data() + c.outer_record_off + 2, c.window);
            put_both32(s.value()->data() + c.outer_record_off + 10, opt_.cvm_window_sectors * S);
        }
    }
    for (const Cvm& c : cvms_) {
        const u64 old_size = c.file.size, new_size = static_cast<u64>(opt_.cvm_window_sectors) * S;
        const u64 delta = new_size - old_size;
        // CVMH: u64 BE CVM size at +0x1C; ZONE: u64 BE at +0x04 (size - 0x80C) and +0x30 (size - header bytes).
        // Moved only where they hold the values this disc's headers hold.
        auto h = patch_sector(c.window);
        if (!h) return h.error();
        if (ld_be64(h.value()->data() + 0x1C) == old_size) st_be64(h.value()->data() + 0x1C, new_size);
        auto z = patch_sector(c.window + 1);
        if (!z) return z.error();
        if (std::memcmp(z.value()->data(), "ZONE", 4) == 0) {
            if (ld_be64(z.value()->data() + 0x04) == old_size - 0x80C) st_be64(z.value()->data() + 0x04, old_size - 0x80C + delta);
            if (ld_be64(z.value()->data() + 0x30) == old_size - static_cast<u64>(c.header_sectors) * S)
                st_be64(z.value()->data() + 0x30, old_size - static_cast<u64>(c.header_sectors) * S + delta);
        }
        auto ip = patch_sector(c.window + c.header_sectors + iso9660::kPvdLsn);
        if (!ip) return ip.error();
        if (std::memcmp(ip.value()->data() + 1, "CD001", 5) == 0)
            put_both32(ip.value()->data() + 80, opt_.cvm_window_sectors - c.header_sectors);
    }
    for (const auto& [path, e] : live_) {
        const u32 dir_first = e->cvm >= 0 ? cvms_[e->cvm].window + cvms_[e->cvm].header_sectors : 0;
        auto s = patch_sector(dir_first + e->parent.lsn + static_cast<u32>(e->record_off / S));
        if (!s) return s.error();
        put_both32(s.value()->data() + e->record_off % S + 2, e->lba);
        put_both32(s.value()->data() + e->record_off % S + 10, e->size);
    }

    for (const auto& [path, e] : live_) {
        ModOverride o;
        o.disc_path = path;
        o.host_path = e->host_path;
        o.mod_name = e->mod_name;
        o.lsn = e->lsn;
        o.size = e->size;
        o.lba = e->lba;
        o.original_lsn = e->original_lsn;
        o.original_size = e->original_size;
        o.generation = e->generation;
        next.overrides.push_back(std::move(o));
        log("mods: " + path + " <- " + u8str(e->host_path) + " [" + e->mod_name + "] " + std::to_string(e->size) +
            " B (disc " + std::to_string(e->original_size) + " B at LSN " + std::to_string(e->original_lsn) + ") at LSN " +
            std::to_string(e->lsn) + (e->cvm >= 0 ? ", ROFS lba " + std::to_string(e->lba) : std::string()) +
            (e->generation != next.generation ? " (unchanged)" : ""));
    }
    log("mods: scan " + std::to_string(next.generation) + ": " + std::to_string(next.mods.size()) + " mod(s), " +
        std::to_string(next.overrides.size()) + " file(s) replaced, " + std::to_string(next.rejected.size()) + " refused" +
        (opt_.enabled ? "" : " (mods disabled)"));
    scan_ = std::move(next);
    clear_reads();
    return scan_.overrides.size();
}

Result<std::size_t> ModsOverlay::patch_rofs_tables(std::span<std::byte> image, u32 image_va) {
    constexpr std::size_t kHdr = 24, kEnt = 48;
    if (!tables_scanned_) {
        static constexpr char kMarker[] = "#DirLst#";
        for (std::size_t pos = 12; pos + 8 <= image.size(); ++pos) {
            if (std::memcmp(image.data() + pos, kMarker, 8) != 0) continue;
            const std::size_t h = pos - 12;
            const u32 count = ld_le32(image.data() + h), count2 = ld_le32(image.data() + h + 4);
            if (count != count2 || count < 2 || count > 65536 || h + kHdr + kEnt * count > image.size()) continue;
            if (ld_le32(image.data() + h + 20) != 0) continue;
            const std::byte* e0 = image.data() + h + kHdr;
            if (std::to_integer<char>(e0[14]) != '.' || std::to_integer<char>(e0[15]) != 0) continue;
            Table t;
            t.offset = h;
            t.count = count;
            t.dir_lba = ld_le32(image.data() + h + 8);
            t.dir_size = ld_le32(e0);
            t.original.assign(e0, e0 + kEnt * count);
            t.written.assign(count, false);
            tables_.push_back(std::move(t));
        }
        tables_scanned_ = true;
        image_va_ = image_va;
        image_size_ = image.size();
    } else if (image_va != image_va_ || image.size() != image_size_) {
        return Error{FormatError::Unsupported, "patch_rofs_tables: a different guest image than the first call's"};
    }

    auto entry_name = [](const std::byte* e) {
        const char* n = reinterpret_cast<const char*>(e + 14);
        std::size_t len = 0;
        while (len < 34 && n[len] != 0) ++len;
        return std::string(n, len);
    };
    auto belongs = [&](Table& t, int ci) {
        if (auto it = t.belongs.find(ci); it != t.belongs.end()) return it->second;
        Cvm& c = cvms_[static_cast<std::size_t>(ci)];
        iso9660::Record dir;
        dir.lsn = t.dir_lba;
        dir.size = t.dir_size;
        dir.flags = 0x02;
        bool ok = false;
        if (auto recs = iso9660::read_directory(*c.inner_view, c.inner, dir); recs && recs->size() + 2 == t.count) {
            ok = true;
            for (u32 k = 2; k < t.count && ok; ++k) {
                const std::byte* e = t.original.data() + kEnt * k;
                const std::string n = entry_name(e);
                const bool is_dir = (std::to_integer<u8>(e[12]) & 0x02) != 0;
                bool found = false;
                for (const iso9660::Record& r : recs.value())
                    if (r.is_directory() == is_dir && r.lsn == ld_le32(e + 8) &&
                        (is_dir || (r.size == ld_le32(e) && ld_le32(e + 4) == 0)) &&
                        iso9660::component_matches(r.identifier, n))
                        found = true;
                ok = found;
            }
        }
        t.belongs.emplace(ci, ok);
        return ok;
    };

    std::vector<std::vector<bool>> want(tables_.size());
    for (std::size_t ti = 0; ti < tables_.size(); ++ti) want[ti].assign(tables_[ti].count, false);
    std::size_t written = 0;
    for (ModOverride& o : scan_.overrides) {
        o.rofs_entries = 0;
        const auto it = live_.find(o.disc_path);
        if (it == live_.end() || it->second->cvm < 0) continue;
        const Extent& e = *it->second;
        for (std::size_t ti = 0; ti < tables_.size(); ++ti) {
            Table& t = tables_[ti];
            if (t.dir_lba != e.parent.lsn || t.dir_size != e.parent.size || !belongs(t, e.cvm)) continue;
            for (u32 k = 2; k < t.count; ++k) {
                const std::byte* oe = t.original.data() + kEnt * k;
                if ((std::to_integer<u8>(oe[12]) & 0x02) != 0 || ld_le32(oe + 8) != e.original_lba ||
                    ld_le32(oe) != e.original_size || !iso9660::component_matches(e.identifier, entry_name(oe)))
                    continue;
                std::byte* dst = image.data() + t.offset + kHdr + kEnt * k;
                st_le32(dst, e.size);
                st_le32(dst + 4, 0);
                st_le32(dst + 8, e.lba);
                want[ti][k] = true;
                t.written[k] = true;
                ++o.rofs_entries;
                ++written;
            }
        }
        if (o.rofs_entries == 0)
            log("mods: " + o.disc_path + ": no ROFS table entry in the ELF names it; the game will not see the change");
    }
    // Entries patched before whose override is gone: back to the disc's values.
    std::size_t restored = 0;
    for (std::size_t ti = 0; ti < tables_.size(); ++ti) {
        Table& t = tables_[ti];
        for (u32 k = 0; k < t.count; ++k)
            if (t.written[k] && !want[ti][k]) {
                std::memcpy(image.data() + t.offset + kHdr + kEnt * k, t.original.data() + kEnt * k, 12);
                t.written[k] = false;
                ++restored;
            }
    }
    log("mods: ROFS tables: " + std::to_string(tables_.size()) + " in the ELF at " + hex32(image_va) + ", " +
        std::to_string(written) + " entries patched" + (restored ? ", " + std::to_string(restored) + " restored" : ""));
    return written;
}

}  // namespace p3fes::hle
