// p3fes_native_movies_check: the offline checks of modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "Layer 4 status").
//
//   sweep --extracted DIR [--jobs N] [--file-timeout S] [--only NAME,...]
//       Every .SFD under DIR: demultiplexed, then its video decoded twice, picture for picture -- through the native
//       engine (DirectEngine: the host bit reader and the IPU core's functions, what `--native movies` runs) and
//       through the emulated IPU (IpuEngine: p3fes::ipu::IpuCore driven by FDEC / VDEC / BDEC / SETIQ / CSC as
//       libmpeg drives it) -- each shown picture's RGB32 hash compared. A file that runs past S seconds stops and is
//       reported TIMEOUT. One line per file, then the totals.
//   frames --sfd FILE [--count N] [--dump K --out FILE] [--trace K]
//       One movie's shown pictures (native engine): type, temporal reference, bits, RGB32 hash; diagnostics.
//   audio --extracted DIR --wav-dir RUN [--wav-dir RUN ...]
//       The ADX track of every .SFD decoded by our ADX decoder (runtime/audio) and matched against the stream_*.wav
//       files of runs' --dump-wav directories: per matched stream, the samples compared and the differences.
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "mpeg_video.h"
#include "p3fes/audio/adx_decoder.h"

namespace fs = std::filesystem;
using namespace p3fes;
using namespace p3fes::native::movies;

namespace {

std::vector<u8> read_file(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    f.seekg(0, std::ios::end);
    std::vector<u8> b(static_cast<std::size_t>(f.tellg()));
    f.seekg(0);
    f.read(reinterpret_cast<char*>(b.data()), static_cast<std::streamsize>(b.size()));
    return b;
}

std::vector<fs::path> find_sfds(const fs::path& root, const std::vector<std::string>& only) {
    std::vector<fs::path> out;
    for (const auto& e : fs::recursive_directory_iterator(root)) {
        if (!e.is_regular_file()) continue;
        std::string ext = e.path().extension().string();
        for (char& c : ext) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        if (ext != ".SFD") continue;
        if (!only.empty() && std::find(only.begin(), only.end(), e.path().filename().string()) == only.end()) continue;
        out.push_back(e.path());
    }
    std::sort(out.begin(), out.end());
    return out;
}

struct FileResult {
    std::string name;
    u64 bytes = 0, video = 0, audio = 0;
    u64 shown = 0, differ = 0, first_diff = ~u64{0};
    u64 types[4] = {};
    std::string end_native, end_ipu;
    double seconds = 0;
    bool timeout = false;
    unsigned w = 0, h = 0;
};

FileResult sweep_file(const fs::path& p, double timeout_s) {
    FileResult r;
    r.name = p.filename().string();
    const auto t0 = std::chrono::steady_clock::now();
    const std::vector<u8> file = read_file(p);
    r.bytes = file.size();
    SfdStreams st;
    demux_sfd(file.data(), file.size(), st);
    r.video = st.video.size();
    r.audio = st.audio.size();
    MpegDecoder dn, di;
    DirectEngine en(st.video.data(), st.video.size());
    IpuEngine ei(st.video.data(), st.video.size());
    std::vector<u8> on(64u * 64u * 1024u), oi(64u * 64u * 1024u);  // the largest picture the decoder accepts
    Status sn = Status::Shown, si = Status::Shown;
    for (;;) {
        sn = dn.decode(en, true, on.data(), on.size());
        si = di.decode(ei, true, oi.data(), oi.size());
        if (sn != Status::Shown || si != Status::Shown) break;
        const std::size_t n = dn.frame_bytes(true);
        if (n != di.frame_bytes(true) || std::memcmp(on.data(), oi.data(), n) != 0) {
            if (r.differ == 0) r.first_diff = r.shown;
            ++r.differ;
        }
        ++r.types[dn.last_shown_type() & 3];
        ++r.shown;
        if (std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count() > timeout_s) {
            r.timeout = true;
            break;
        }
    }
    r.end_native = to_string(sn);
    r.end_ipu = to_string(si);
    if (sn != si) ++r.differ;
    r.w = dn.width();
    r.h = dn.height();
    r.seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    return r;
}

int cmd_sweep(const fs::path& root, unsigned jobs, double timeout_s, const std::vector<std::string>& only) {
    const std::vector<fs::path> files = find_sfds(root, only);
    if (files.empty()) {
        std::fprintf(stderr, "sweep: no .SFD under %s\n", root.string().c_str());
        return 2;
    }
    std::vector<FileResult> res(files.size());
    std::atomic<std::size_t> next{0};
    std::mutex out_mu;
    auto worker = [&] {
        for (;;) {
            const std::size_t i = next++;
            if (i >= files.size()) return;
            res[i] = sweep_file(files[i], timeout_s);
            const FileResult& r = res[i];
            std::lock_guard<std::mutex> lk(out_mu);
            std::printf("%-20s %4ux%-4u pictures %6llu (I %llu P %llu B %llu) differ %llu%s end %s/%s %s %.1f s\n",
                        r.name.c_str(), r.w, r.h, static_cast<unsigned long long>(r.shown),
                        static_cast<unsigned long long>(r.types[1]), static_cast<unsigned long long>(r.types[2]),
                        static_cast<unsigned long long>(r.types[3]), static_cast<unsigned long long>(r.differ),
                        r.differ ? (" first " + std::to_string(r.first_diff)).c_str() : "", r.end_native.c_str(),
                        r.end_ipu.c_str(), r.timeout ? "TIMEOUT" : (r.differ ? "DIFFER" : "ok"), r.seconds);
            std::fflush(stdout);
        }
    };
    std::vector<std::thread> pool;
    for (unsigned j = 0; j < std::max(1u, jobs); ++j) pool.emplace_back(worker);
    for (auto& t : pool) t.join();
    u64 shown = 0, differ = 0, bytes = 0, video = 0, timeouts = 0, bad_end = 0, types[4] = {};
    for (const FileResult& r : res) {
        shown += r.shown;
        differ += r.differ;
        bytes += r.bytes;
        video += r.video;
        timeouts += r.timeout ? 1 : 0;
        bad_end += (r.end_native != "end" || r.end_ipu != "end") && !r.timeout ? 1 : 0;
        for (unsigned k = 0; k < 4; ++k) types[k] += r.types[k];
    }
    std::printf("sweep: %zu files, %llu bytes (video ES %llu), %llu pictures (I %llu P %llu B %llu), %llu differ, "
                "%llu timeouts, %llu files not ending at the sequence end\n",
                files.size(), static_cast<unsigned long long>(bytes), static_cast<unsigned long long>(video),
                static_cast<unsigned long long>(shown), static_cast<unsigned long long>(types[1]),
                static_cast<unsigned long long>(types[2]), static_cast<unsigned long long>(types[3]),
                static_cast<unsigned long long>(differ), static_cast<unsigned long long>(timeouts),
                static_cast<unsigned long long>(bad_end));
    return (differ || timeouts || bad_end) ? 1 : 0;
}

// ---- audio ---------------------------------------------------------------------------------------------------------

struct Wav {
    u32 channels = 0, rate = 0;
    std::vector<s16> pcm;
};
Wav read_wav(const fs::path& p) {
    Wav w;
    const std::vector<u8> b = read_file(p);
    if (b.size() < 44) return w;
    auto u16at = [&](std::size_t o) { return static_cast<u32>(b[o]) | static_cast<u32>(b[o + 1]) << 8; };
    auto u32at = [&](std::size_t o) { return u16at(o) | u16at(o + 2) << 16; };
    std::size_t o = 12, data = 0, len = 0;
    while (o + 8 <= b.size()) {
        const u32 id = u32at(o), sz = u32at(o + 4);
        if (id == 0x20746D66u) {
            w.channels = u16at(o + 10);
            w.rate = u32at(o + 12);
        } else if (id == 0x61746164u) {
            data = o + 8;
            len = std::min<std::size_t>(sz, b.size() - data);
            break;
        }
        o += 8 + sz + (sz & 1);
    }
    w.pcm.resize(len / 2);
    if (!w.pcm.empty()) std::memcpy(w.pcm.data(), b.data() + data, w.pcm.size() * 2);
    return w;
}

int cmd_audio(const fs::path& root, const std::vector<fs::path>& runs) {
    struct Track {
        std::string name;
        u32 channels = 0;
        std::vector<s16> pcm;
    };
    std::vector<Track> tracks;
    for (const fs::path& p : find_sfds(root, {})) {
        const std::vector<u8> file = read_file(p);
        SfdStreams st;
        demux_sfd(file.data(), file.size(), st);
        if (st.audio.empty()) continue;
        const auto bytes = std::as_bytes(std::span<const u8>(st.audio));
        auto d = audio::AdxDecoder::open(bytes);
        if (!d) continue;
        audio::AdxDecoder dec = std::move(d).value();
        Track t;
        t.name = p.filename().string();
        t.channels = dec.channels();
        std::vector<s16> buf(4096 * dec.channels());
        for (;;) {
            const std::size_t n = dec.decode(buf);
            if (n == 0) break;
            t.pcm.insert(t.pcm.end(), buf.begin(), buf.begin() + static_cast<std::ptrdiff_t>(n * dec.channels()));
        }
        tracks.push_back(std::move(t));
    }
    std::printf("audio: %zu movie ADX tracks decoded\n", tracks.size());
    u64 matched = 0, exact = 0, compared = 0, streams = 0;
    for (const fs::path& run : runs) {
        for (const auto& e : fs::directory_iterator(run)) {
            const std::string fn = e.path().filename().string();
            if (fn.rfind("stream_", 0) != 0 || e.path().extension() != ".wav") continue;
            ++streams;
            const Wav w = read_wav(e.path());
            if (w.pcm.empty()) continue;
            // the track whose decode the stream starts with: 4,096 frames from the stream's first sound (movies open
            // on silence) decide
            std::size_t first = 0;
            while (first < w.pcm.size() && w.pcm[first] == 0) ++first;
            const Track* best = nullptr;
            for (const Track& t : tracks) {
                if (t.channels != w.channels || first >= w.pcm.size()) continue;
                const std::size_t n = std::min<std::size_t>({t.pcm.size(), w.pcm.size(), first + std::size_t{4096} * t.channels});
                if (n <= first || std::memcmp(t.pcm.data(), w.pcm.data(), n * 2) != 0) continue;
                best = &t;
            }            if (!best) continue;
            ++matched;
            const std::size_t n = std::min(best->pcm.size(), w.pcm.size());
            u64 diff = 0;
            for (std::size_t i = 0; i < n; ++i) diff += best->pcm[i] != w.pcm[i] ? 1 : 0;
            compared += n / best->channels;
            if (diff == 0) ++exact;
            std::printf("  %s/%s = %s: %zu frames compared (stream %zu, track %zu), %llu samples differ\n",
                        run.filename().string().c_str(), fn.c_str(), best->name.c_str(), n / best->channels,
                        w.pcm.size() / w.channels, best->pcm.size() / best->channels,
                        static_cast<unsigned long long>(diff));
        }
    }
    std::printf("audio: %llu streams, %llu match a movie track, %llu bit-exact over the common length (%llu frames)\n",
                static_cast<unsigned long long>(streams), static_cast<unsigned long long>(matched),
                static_cast<unsigned long long>(exact), static_cast<unsigned long long>(compared));
    return matched == exact ? 0 : 1;
}

// frames: one line per shown picture of one .SFD (native engine): index, type, temporal reference, RGB32 hash; with
// --dump N, the picture N's RGB32 macroblocks into <out>; with --trace K, every macroblock of the picture decoded K-th
// (decode order): position, macroblock_type flags (| 0x100 skipped, | dir << 9), the vectors.
int cmd_frames(const fs::path& sfd, u64 count, u64 dump, const fs::path& out, u64 tr) {
    const std::vector<u8> file = read_file(sfd);
    SfdStreams st;
    demux_sfd(file.data(), file.size(), st);
    MpegDecoder d;
    DirectEngine e(st.video.data(), st.video.size());
    std::vector<u8> o(64u * 64u * 1024u);
    if (tr != ~u64{0})
        d.trace = [&](unsigned x, unsigned y, unsigned f, const int (&mv)[2][2]) {
            if (d.frames_decoded() == tr) std::printf("  mb %u,%u flags %03X fwd %d,%d bwd %d,%d\n", x, y, f, mv[0][0], mv[0][1], mv[1][0], mv[1][1]);
        };
    for (u64 i = 0; i < count; ++i) {
        const Status s = d.decode(e, true, o.data(), o.size());
        if (s != Status::Shown) {
            std::printf("%llu %s\n", static_cast<unsigned long long>(i), to_string(s));
            break;
        }
        const std::size_t n = d.frame_bytes(true);
        std::printf("%llu type %u tref %u bits %llu frame=%016llX\n", static_cast<unsigned long long>(i),
                    d.last_shown_type(), d.last_shown_tref(), static_cast<unsigned long long>(e.bitpos()),
                    static_cast<unsigned long long>(fnv1a64(o.data(), n)));
        if (i == dump && !out.empty()) {
            std::ofstream f(out, std::ios::binary);
            f.write(reinterpret_cast<const char*>(o.data()), static_cast<std::streamsize>(n));
        }
    }
    return 0;
}

int usage() {
    std::fprintf(stderr,
                 "usage: p3fes_native_movies_check sweep --extracted DIR [--jobs N] [--file-timeout S] [--only A,B]\n"
                 "       p3fes_native_movies_check audio --extracted DIR --wav-dir RUN [--wav-dir RUN ...]\n"
                 "       p3fes_native_movies_check frames --sfd FILE [--count N] [--dump K --out FILE] [--trace K]\n");
    return 2;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) return usage();
    const std::string cmd = argv[1];
    fs::path extracted;
    unsigned jobs = 4;
    double timeout_s = 600;
    std::vector<std::string> only;
    std::vector<fs::path> runs;
    fs::path sfd, out;
    u64 count = 10, dump = ~u64{0}, trace = ~u64{0};
    for (int i = 2; i < argc; ++i) {
        const std::string a = argv[i];
        const bool has1 = i + 1 < argc;
        if (a == "--extracted" && has1) extracted = argv[++i];
        else if (a == "--jobs" && has1) jobs = static_cast<unsigned>(std::atoi(argv[++i]));
        else if (a == "--file-timeout" && has1) timeout_s = std::atof(argv[++i]);
        else if (a == "--wav-dir" && has1) runs.emplace_back(argv[++i]);
        else if (a == "--sfd" && has1) sfd = argv[++i];
        else if (a == "--count" && has1) count = std::strtoull(argv[++i], nullptr, 10);
        else if (a == "--dump" && has1) dump = std::strtoull(argv[++i], nullptr, 10);
        else if (a == "--out" && has1) out = argv[++i];
        else if (a == "--trace" && has1) trace = std::strtoull(argv[++i], nullptr, 10);
        else if (a == "--only" && has1) {
            std::string s = argv[++i];
            for (std::size_t p = 0; p <= s.size();) {
                const std::size_t q = std::min(s.find(',', p), s.size());
                if (q > p) only.push_back(s.substr(p, q - p));
                p = q + 1;
            }
        } else return usage();
    }
    if (cmd == "frames") return cmd_frames(sfd, count, dump, out, trace);
    if (extracted.empty()) return usage();
    if (cmd == "sweep") return cmd_sweep(extracted, jobs, timeout_s, only);
    if (cmd == "audio") return cmd_audio(extracted, runs);
    return usage();
}
