// Modernize layer 1: the host's native files service (native_files.h).
#include "native_files.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

#include "p3fes/hle/read_log.h"

namespace p3fes::native::files {

namespace {

constexpr u32 S = hle::kSectorSize;

std::string upper(std::string_view s) {
    std::string r(s);
    for (char& c : r) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return r;
}

}  // namespace

std::string path_key(std::string_view path) {
    std::string out;
    std::string comp;
    auto flush = [&] {
        if (const auto semi = comp.find(';'); semi != std::string::npos) comp.resize(semi);
        while (!comp.empty() && comp.back() == '.') comp.pop_back();
        if (!comp.empty()) {
            if (!out.empty()) out += '\\';
            out += comp;
        }
        comp.clear();
    };
    for (char c : path) {
        if (c == '/' || c == '\\') flush();
        else comp += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    flush();
    return out;
}

NativeFiles::~NativeFiles() = default;

hle::Result<std::unique_ptr<NativeFiles>> NativeFiles::open(hle::DiscSource& disc) {
    std::unique_ptr<NativeFiles> nf(new NativeFiles(disc));
    const hle::DiscPathIndex ix = hle::DiscPathIndex::build(disc);
    ix.for_each_file([&](const std::string& path, u32 lsn, u32 sectors, u64 size, bool outer) {
        Entry e;
        e.path = path;
        e.lsn = lsn;
        e.sectors = sectors;
        e.disc_size = size;
        e.outer = outer;
        nf->entries_.push_back(std::move(e));
        if (outer) ++nf->outer_count_;
    });
    for (std::size_t i = 0; i < nf->entries_.size(); ++i) {
        Entry& e = nf->entries_[i];
        const u32 id = static_cast<u32>(i + 1);
        nf->by_key_.emplace(path_key(e.path), id);
        if (e.outer) {
            nf->outer_by_lsn_.emplace(e.lsn, id);
        } else if (const auto colon = e.path.find(':'); colon != std::string::npos) {
            if (auto it = nf->by_key_.find(path_key(e.path.substr(0, colon))); it != nf->by_key_.end()) e.container = it->second;
        }
    }
    if (nf->members() == 0)
        return hle::Error{hle::FormatError::Unsupported, "native files: the disc has no CVM member (not the user's disc?)"};
    return nf;
}

FileRef NativeFiles::ref(u32 id) const {
    const Entry& e = *entry(id);
    return FileRef{id, e.host.empty() ? e.disc_size : e.host_size, e.lsn};
}

std::optional<FileRef> NativeFiles::find(std::string_view path) {
    const auto it = by_key_.find(path_key(path));
    if (it == by_key_.end()) {
        if (miss_) miss_(path);
        return std::nullopt;
    }
    return ref(it->second);
}

std::optional<OuterFile> NativeFiles::search(std::string_view cd_path) {
    const auto it = by_key_.find(path_key(cd_path));
    if (it == by_key_.end() || !entry(it->second)->outer) {
        if (miss_) miss_(cd_path);
        return std::nullopt;
    }
    OuterFile o;
    o.file = ref(it->second);
    // The directory record itself (identifier as recorded, recording date): the host's own ISO9660 reader, the one
    // DiscPathIndex walked (for extracted volumes, kDiscLayout's rows).
    if (auto f = disc_.find_file(cd_path); f && f.value()) {
        o.identifier = f.value()->identifier;
        o.recorded = f.value()->recorded;
    } else {
        o.identifier = entry(it->second)->path + ";1";
    }
    return o;
}

std::optional<FileRef> NativeFiles::outer_at(u32 lsn) {
    const auto it = outer_by_lsn_.find(lsn);
    if (it == outer_by_lsn_.end()) return std::nullopt;
    return ref(it->second);
}

bool NativeFiles::read_disc(u64 byte_offset, std::span<std::byte> dst) {
    if (dst.empty()) return true;
    const u64 first = byte_offset / S;
    const u64 last = (byte_offset + dst.size() - 1) / S;
    if (last >= disc_.sector_count()) return false;
    if (byte_offset % S == 0 && dst.size() % S == 0)
        return disc_.read_sectors(static_cast<u32>(first), static_cast<u32>(last - first + 1), dst).ok();
    bounce_.resize(static_cast<std::size_t>(last - first + 1) * S);
    if (!disc_.read_sectors(static_cast<u32>(first), static_cast<u32>(last - first + 1), bounce_).ok()) return false;
    std::memcpy(dst.data(), bounce_.data() + (byte_offset - first * S), dst.size());
    return true;
}

bool NativeFiles::read_host(const Entry& e, u64 offset, std::span<std::byte> dst) {
    std::fill(dst.begin(), dst.end(), std::byte{0});
    if (offset >= e.host_size) return true;
    const std::size_t want = static_cast<std::size_t>(std::min<u64>(dst.size(), e.host_size - offset));
    std::FILE* f = nullptr;
#ifdef _WIN32
    if (_wfopen_s(&f, e.host.c_str(), L"rb") != 0) f = nullptr;
#else
    f = std::fopen(e.host.c_str(), "rb");
#endif
    if (!f) return false;
    bool ok = _fseeki64(f, static_cast<long long>(offset), SEEK_SET) == 0;
    // A file that shrank since the scan reads short: the rest stays zero, as past its end.
    if (ok) (void)std::fread(dst.data(), 1, want, f);
    std::fclose(f);
    return ok;
}

bool NativeFiles::read(const FileRef& f, u64 offset, std::span<std::byte> dst, u32 guest_dst) {
    const Entry* e = entry(f.id);
    if (!e) return false;
    bool ok;
    if (!e->host.empty()) {
        ok = read_host(*e, offset, dst);
    } else {
        ok = read_disc(static_cast<u64>(e->lsn) * S + offset, dst);
        if (ok && e->outer) {
            if (auto it = replaced_in_.find(f.id); it != replaced_in_.end()) {
                // A container read over replaced members (a stream through dvCi): their extents serve the mod files.
                const u64 lo = offset, hi = offset + dst.size();
                for (u32 mid : it->second) {
                    const Entry& m = *entry(mid);
                    const u64 m_lo = static_cast<u64>(m.lsn - e->lsn) * S, m_hi = m_lo + static_cast<u64>(m.sectors) * S;
                    const u64 a = std::max(lo, m_lo), b = std::min(hi, m_hi);
                    if (a < b) ok = read_host(m, a - m_lo, dst.subspan(static_cast<std::size_t>(a - lo), static_cast<std::size_t>(b - a))) && ok;
                }
            }
        }
    }
    if (ok && observer_)
        observer_(NativeRead{static_cast<u32>(e->lsn + offset / S), static_cast<u32>((dst.size() + S - 1) / S), guest_dst, dst});
    return ok;
}

std::size_t NativeFiles::set_overrides(const std::vector<hle::ModOverride>& overrides) {
    for (Entry& e : entries_) {
        e.host.clear();
        e.host_size = 0;
    }
    replaced_in_.clear();
    std::size_t applied = 0;
    for (const hle::ModOverride& o : overrides) {
        // "DATA\FIELD\X.PAC" -> "DATA.CVM:\FIELD\X.PAC" when DATA.CVM is a container; else an outer path.
        std::string key = path_key(o.disc_path);
        if (const auto sep = key.find('\\'); sep != std::string::npos) {
            const std::string cvm = key.substr(0, sep) + ".CVM";
            if (auto c = by_key_.find(cvm); c != by_key_.end() && entry(c->second)->outer)
                key = path_key(cvm + ":\\" + key.substr(sep + 1));
        }
        const auto it = by_key_.find(key);
        if (it == by_key_.end()) continue;
        Entry& e = entries_[it->second - 1];
        e.host = o.host_path;
        e.host_size = o.size;
        if (e.container) replaced_in_[e.container].push_back(it->second);
        ++applied;
    }
    return applied;
}

}  // namespace p3fes::native::files
