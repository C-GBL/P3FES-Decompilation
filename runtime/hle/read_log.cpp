// The read log's path index and line format (p3fes/hle/read_log.h).
#include "p3fes/hle/read_log.h"

#include <algorithm>
#include <cctype>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <functional>

#include "iso9660.h"

namespace p3fes::hle {

namespace {

constexpr u32 S = kSectorSize;
constexpr int kMaxDepth = 16;

// A window onto `count` sectors of another source from `first` (a CVM's inner ISO9660 image).
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

std::string display_name(std::string_view identifier) {
    std::string s(identifier.substr(0, identifier.find(';')));
    for (char& c : s) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}

bool ends_with_cvm(const std::string& name) { return name.size() > 4 && name.compare(name.size() - 4, 4, ".CVM") == 0; }

u32 be32(const std::byte* p) {
    return (std::to_integer<u32>(p[0]) << 24) | (std::to_integer<u32>(p[1]) << 16) | (std::to_integer<u32>(p[2]) << 8) |
           std::to_integer<u32>(p[3]);
}

// Header sectors of a CRI CVM (CVMH +136, big-endian; 3 on the user's disc), 0 if `f` is not a CVM.
u32 cvm_header_sectors(DiscSource& disc, u32 lsn, u32 sectors) {
    if (sectors < 2 || static_cast<u64>(lsn) + 1 > disc.sector_count()) return 0;
    std::vector<std::byte> hdr(S);
    if (!disc.read_sectors(lsn, 1, hdr)) return 0;
    if (std::memcmp(hdr.data(), "CVMH", 4) != 0) return 0;
    const u32 h = be32(hdr.data() + 136);
    return (h != 0 && h + 17 <= sectors) ? h : 0;
}

void walk(DiscSource& disc, const iso9660::Volume& vol, const iso9660::Record& dir, const std::string& prefix, u32 first,
          int depth, const std::function<void(const iso9660::Record&, const std::string&, u32)>& emit) {
    if (depth > kMaxDepth) return;
    auto entries = iso9660::read_directory(disc, vol, dir);
    if (!entries) return;
    for (const iso9660::Record& r : entries.value()) {
        const std::string name = prefix + display_name(r.identifier);
        if (r.is_directory()) walk(disc, vol, r, name + "\\", first, depth + 1, emit);
        else emit(r, name, first + r.lsn);
    }
}

}  // namespace

u64 fnv1a64(std::span<const std::byte> bytes, u64 h) {
    for (std::byte b : bytes) {
        h ^= std::to_integer<u64>(b);
        h *= 0x100000001B3ull;
    }
    return h;
}

DiscPathIndex DiscPathIndex::build(DiscSource& disc) {
    DiscPathIndex ix;
    auto add_cvm_members = [&](const std::string& cvm, u32 lsn, u32 sectors) {
        const u32 h = cvm_header_sectors(disc, lsn, sectors);
        if (h == 0) return;
        OffsetView inner(disc, lsn + h, sectors - h);
        auto iv = iso9660::read_volume(inner);
        if (!iv) return;
        walk(inner, iv.value(), iv->root, cvm + ":\\", lsn + h, 0, [&](const iso9660::Record& r, const std::string& p, u32 at) {
            const u32 n = (r.size + S - 1) / S;
            if (n) ix.members_.push_back(Span{at, n, r.size, p});
        });
    };
    auto add_outer = [&](const std::string& name, u32 lsn, u64 size) {
        const u32 n = static_cast<u32>((size + S - 1) / S);
        if (n == 0) return;
        ix.outer_.push_back(Span{lsn, n, size, name});
        if (ends_with_cvm(name)) add_cvm_members(name, lsn, n);
    };
    if (auto vol = iso9660::read_volume(disc); vol) {
        walk(disc, vol.value(), vol->root, "", 0, 0,
             [&](const iso9660::Record& r, const std::string& p, u32 at) { add_outer(p, at, r.size); });
    } else {
        // Extracted volumes: no outer directories; the fixed layout places the five root files (LIB31 is not served).
        for (const DiscLayoutEntry& e : kDiscLayout) add_outer(std::string(e.host_name), e.lsn, e.size);
    }
    auto by_lsn = [](const Span& a, const Span& b) { return a.lsn < b.lsn; };
    std::sort(ix.outer_.begin(), ix.outer_.end(), by_lsn);
    std::sort(ix.members_.begin(), ix.members_.end(), by_lsn);
    return ix;
}

const DiscPathIndex::Span* DiscPathIndex::find(const std::vector<Span>& v, u32 lsn, u32 sectors) {
    auto it = std::upper_bound(v.begin(), v.end(), lsn, [](u32 l, const Span& s) { return l < s.lsn; });
    if (it == v.begin()) return nullptr;
    const Span& s = *(it - 1);
    const u64 end = static_cast<u64>(s.lsn) + s.sectors;
    if (lsn >= end || static_cast<u64>(lsn) + std::max<u32>(sectors, 1) > end) return nullptr;
    return &s;
}

ResolvedRead DiscPathIndex::resolve(u32 lsn, u32 sectors) const {
    const Span* s = find(members_, lsn, sectors);
    if (!s) s = find(outer_, lsn, sectors);
    if (!s) return ResolvedRead{"-", static_cast<u64>(lsn) * S, 0};
    return ResolvedRead{s->path, static_cast<u64>(lsn - s->lsn) * S, s->size};
}

std::string format_read_log_line(const ReadLogRecord& r) {
    char head[160];
    std::snprintf(head, sizeof head, "%" PRIu64 " lsn=%u n=%u bytes=%" PRIu64 " dst=%08X path=", r.vblank, r.lsn,
                  r.sectors, static_cast<u64>(r.sectors) * S, r.dst);
    char tail[96];
    if (r.error == 0)
        std::snprintf(tail, sizeof tail, " off=%" PRIu64 " fsize=%" PRIu64 " hash=%016" PRIX64, r.file.offset,
                      r.file.file_size, r.hash);
    else
        std::snprintf(tail, sizeof tail, " off=%" PRIu64 " fsize=%" PRIu64 " hash=- err=%d", r.file.offset,
                      r.file.file_size, r.error);
    return std::string(head) + (r.file.path.empty() ? std::string("-") : r.file.path) + tail;
}

}  // namespace p3fes::hle
