// p3fes_native_files_check: modernize layer 1, checks (a) and (b) (docs/MODERNIZE_PLAN.md §3).
//
//   p3fes_native_files_check reads --disc ISO_OR_DIR LOG...
//       (a) every read of faithful read logs (--read-log, cdvdfsv), served through the native API twice: by the
//       logged path and offset (FileService::find + read: what H_Cdvd's native load does) and by its container and
//       container offset (outer_at(LSN of the CVM) + read: what dvCi's native read does). Each must give the logged
//       hash over the logged number of bytes, and find() the logged file size. Reads with path "-" or err= are
//       counted apart (none in the six routes).
//   p3fes_native_files_check sweep --disc ISO_OR_DIR [--extracted DIR]
//       (b) every file of the disc (27 outer, 12,017 CVM members on the user's disc): its whole disc extent read by
//       path through the native API against the sector path (DiscSource::read_sectors at its LSN, what cdvdfsv
//       serves), and each member's bytes against its extracted copy (DIR\DATA\..., DIR\BTL\..., DIR\BGM\...).
// Exit 0 when everything matches, 1 on a mismatch, 2 on a usage or open error. One summary line per log / sweep.
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "native_files.h"
#include "p3fes/hle/read_log.h"

namespace {

using namespace p3fes;
using native::files::NativeFiles;
constexpr u32 S = hle::kSectorSize;

bool field(std::string_view line, std::string_view key, std::string& out) {
    const std::string k = " " + std::string(key) + "=";
    const auto at = line.find(k);
    if (at == std::string_view::npos) return false;
    const auto from = at + k.size();
    const auto end = line.find(' ', from);
    out = std::string(line.substr(from, end == std::string_view::npos ? std::string_view::npos : end - from));
    return true;
}

int check_reads(NativeFiles& nf, const std::vector<std::string>& logs) {
    bool bad = false;
    u64 all_reads = 0, all_ok = 0;
    for (const std::string& log : logs) {
        std::ifstream in(log);
        if (!in) {
            std::printf("reads %s: cannot open\n", log.c_str());
            return 2;
        }
        u64 reads = 0, ok = 0, skipped = 0, missing = 0, size_bad = 0, hash_bad = 0, cont_bad = 0, bytes = 0;
        std::string line, lsn_s, n_s, path, off_s, fsize_s, hash_s, err_s;
        std::vector<std::byte> buf;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') continue;
            ++reads;
            if (!field(line, "lsn", lsn_s) || !field(line, "n", n_s) || !field(line, "path", path) || !field(line, "off", off_s) ||
                !field(line, "fsize", fsize_s) || !field(line, "hash", hash_s) || field(line, "err", err_s) || path == "-") {
                ++skipped;
                continue;
            }
            const u32 lsn = static_cast<u32>(std::stoul(lsn_s)), n = static_cast<u32>(std::stoul(n_s));
            const u64 off = std::stoull(off_s), fsize = std::stoull(fsize_s), hash = std::stoull(hash_s, nullptr, 16);
            buf.assign(static_cast<std::size_t>(n) * S, std::byte{0});
            const auto f = nf.find(path);
            if (!f) {
                ++missing;
                if (missing <= 5) std::printf("  missing: %s\n", line.c_str());
                continue;
            }
            bool good = true;
            if (f->size != fsize) {
                ++size_bad;
                good = false;
            }
            if (!nf.read(*f, off, buf, 0) || hle::fnv1a64(buf) != hash) {
                ++hash_bad;
                good = false;
                if (hash_bad <= 5) std::printf("  by path differs: %s\n", line.c_str());
            }
            // The dvCi form: the container (the CVM, or the outer file itself) at the read's offset in it.
            const std::string outer = path.substr(0, path.find(':'));
            const auto c = nf.find(outer);
            std::fill(buf.begin(), buf.end(), std::byte{0});
            if (!c || lsn < c->lsn || !nf.read(*c, static_cast<u64>(lsn - c->lsn) * S, buf, 0) || hle::fnv1a64(buf) != hash) {
                ++cont_bad;
                good = false;
                if (cont_bad <= 5) std::printf("  by container differs: %s\n", line.c_str());
            }
            if (good) {
                ++ok;
                bytes += buf.size();
            }
        }
        std::printf("reads %s: %" PRIu64 " reads, %" PRIu64 " identical by path and by container (%" PRIu64
                    " bytes), %" PRIu64 " size mismatches, %" PRIu64 " by-path mismatches, %" PRIu64
                    " by-container mismatches, %" PRIu64 " not found, %" PRIu64 " skipped (path - / err)\n",
                    log.c_str(), reads, ok, bytes, size_bad, hash_bad, cont_bad, missing, skipped);
        if (ok + skipped != reads) bad = true;
        all_reads += reads;
        all_ok += ok;
    }
    std::printf("reads total: %" PRIu64 " reads in %zu logs, %" PRIu64 " identical: %s\n", all_reads, logs.size(), all_ok,
                bad ? "MISMATCH" : "OK");
    return bad ? 1 : 0;
}

int sweep(NativeFiles& nf, hle::DiscSource& disc, const std::string& extracted) {
    constexpr u32 kChunk = 4096;  // sectors per step (8 MiB)
    std::vector<std::byte> a(static_cast<std::size_t>(kChunk) * S), b(a.size()), x(a.size());
    u64 files = 0, outer = 0, members = 0, bytes = 0, bad = 0, ext_files = 0, ext_bad = 0, ext_missing = 0;
    nf.for_each_file([&](const std::string& path, u32 lsn, u64 size) {
        ++files;
        const bool member = path.find(':') != std::string::npos;
        member ? ++members : ++outer;
        const auto f = nf.find(path);
        if (!f || f->lsn != lsn || f->size != size) {
            ++bad;
            std::printf("  lookup differs: %s\n", path.c_str());
            return;
        }
        std::ifstream ext;
        bool ext_ok = true;
        if (member && !extracted.empty()) {
            // "DATA.CVM:\FIELD\X.PAC" -> DIR\DATA\FIELD\X.PAC
            const std::string vol = path.substr(0, path.find('.'));
            const std::string rel = path.substr(path.find(":\\") + 2);
            std::string host = extracted + "\\" + vol + "\\" + rel;
            ext.open(host, std::ios::binary);
            if (!ext && !host.empty() && host.back() == '.') {  // "LMAP_DAT." is stored without the dot
                host.pop_back();
                ext.open(host, std::ios::binary);
            }
            if (!ext) {
                ++ext_missing;
                if (ext_missing <= 5) std::printf("  no extracted copy: %s\n", host.c_str());
            } else {
                ++ext_files;
            }
        }
        const u32 sectors = static_cast<u32>((size + S - 1) / S);
        bool same = true;
        for (u32 done = 0; done < sectors; done += kChunk) {
            const u32 n = std::min(kChunk, sectors - done);
            const std::span<std::byte> sa(a.data(), static_cast<std::size_t>(n) * S), sb(b.data(), sa.size());
            if (!nf.read(*f, static_cast<u64>(done) * S, sa, 0) || !disc.read_sectors(lsn + done, n, sb).ok() ||
                std::memcmp(sa.data(), sb.data(), sa.size()) != 0)
                same = false;
            if (ext.is_open()) {
                const u64 at = static_cast<u64>(done) * S;
                const std::size_t want = static_cast<std::size_t>(std::min<u64>(sa.size(), size - at));
                ext.read(reinterpret_cast<char*>(x.data()), static_cast<std::streamsize>(want));
                if (static_cast<std::size_t>(ext.gcount()) != want || std::memcmp(x.data(), sa.data(), want) != 0) ext_ok = false;
            }
            bytes += sa.size();
        }
        if (ext.is_open()) {
            ext.peek();
            if (!ext.eof()) ext_ok = false;  // the extracted copy is longer than the disc file
            if (!ext_ok && ++ext_bad <= 5) std::printf("  extracted copy differs: %s\n", path.c_str());
        }
        if (!same && ++bad <= 5) std::printf("  native and sector reads differ: %s\n", path.c_str());
    });
    std::printf("sweep: %" PRIu64 " files (%" PRIu64 " outer, %" PRIu64 " CVM members), %" PRIu64
                " bytes by path vs by sector: %" PRIu64 " differ; extracted copies: %" PRIu64 " compared, %" PRIu64
                " differ, %" PRIu64 " missing: %s\n",
                files, outer, members, bytes, bad, ext_files, ext_bad, ext_missing, (bad || ext_bad) ? "MISMATCH" : "OK");
    return (bad || ext_bad) ? 1 : 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: p3fes_native_files_check reads --disc ISO_OR_DIR LOG... | sweep --disc ISO_OR_DIR [--extracted DIR]\n");
        return 2;
    }
    const std::string mode = argv[1];
    std::string disc_path, extracted;
    std::vector<std::string> logs;
    for (int i = 2; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--disc" && i + 1 < argc) disc_path = argv[++i];
        else if (a == "--extracted" && i + 1 < argc) extracted = argv[++i];
        else logs.push_back(a);
    }
    if (disc_path.empty() || (mode != "reads" && mode != "sweep") || (mode == "reads" && logs.empty())) {
        std::fprintf(stderr, "p3fes_native_files_check: bad arguments\n");
        return 2;
    }
    auto disc = hle::open_user_disc(disc_path);
    if (!disc) {
        std::fprintf(stderr, "disc %s: %s %s\n", disc_path.c_str(), std::string(formats::error_name(disc.code())).c_str(), std::string(disc.detail()).c_str());
        return 2;
    }
    auto nf = NativeFiles::open(*disc.value());
    if (!nf) {
        std::fprintf(stderr, "native files: %s\n", std::string(nf.detail()).c_str());
        return 2;
    }
    std::printf("native files: %zu outer files, %zu CVM members\n", nf.value()->outer_files(), nf.value()->members());
    return mode == "reads" ? check_reads(*nf.value(), logs) : sweep(*nf.value(), *disc.value(), extracted);
}
