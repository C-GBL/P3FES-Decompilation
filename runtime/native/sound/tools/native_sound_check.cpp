// p3fes_native_sound_check: modernize layer 3, check 1 (docs/MODERNIZE_PLAN.md §3): the ADX PCM the game decoded (its
// own CRI decoder, the `--dump-wav` stream files of a run, faithful or `--native sound`) against our decoder
// (runtime/audio/adx_decoder) on the files the run read, a whole-disc decode sweep, and vgmstream-cli as a second
// opinion. No game data is written anywhere but the given temporary directory.
//
//   p3fes_native_sound_check streams --extracted DIR RUN...   RUN = a run directory with reads.txt (--read-log) and
//                                                             wav/stream_*.wav (--dump-wav)
//   p3fes_native_sound_check sweep --extracted DIR            every .ADX file and every ADX member of every .AFS
//   p3fes_native_sound_check vgm --extracted DIR --vgmstream EXE --tmp DIR [--count N]
//   p3fes_native_sound_check mixcmp FAITHFUL.wav NATIVE.wav   check 3's metric: per-channel RMS level (dB, native vs
//                                                             faithful) and 0.5 s windows aligned by the lag (+-1,024
//                                                             frames) that minimises the squared difference: bit-exact
//                                                             windows, residual RMS(f - n) / RMS(f) in dB
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "p3fes/audio/adx_decoder.h"
#include "p3fes/formats/adx.h"
#include "p3fes/formats/afs.h"

namespace fs = std::filesystem;
using namespace p3fes;

namespace {

std::vector<std::byte> read_file(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    f.seekg(0, std::ios::end);
    std::vector<std::byte> b(static_cast<std::size_t>(f.tellg()));
    f.seekg(0);
    f.read(reinterpret_cast<char*>(b.data()), static_cast<std::streamsize>(b.size()));
    return b;
}

// A 16-bit PCM WAV's samples (interleaved) and channel count; empty on a bad file.
struct Wav {
    u32 channels = 0, rate = 0;
    std::vector<s16> pcm;
};
Wav read_wav(const fs::path& p) {
    Wav w;
    const std::vector<std::byte> b = read_file(p);
    if (b.size() < 44) return w;
    auto u16at = [&](std::size_t o) { return static_cast<u32>(b[o]) | static_cast<u32>(b[o + 1]) << 8; };
    auto u32at = [&](std::size_t o) { return u16at(o) | u16at(o + 2) << 16; };
    std::size_t o = 12;
    std::size_t data = 0, len = 0;
    while (o + 8 <= b.size()) {
        const u32 id = u32at(o), sz = u32at(o + 4);
        if (id == 0x20746D66u) {  // "fmt "
            w.channels = u16at(o + 10);
            w.rate = u32at(o + 12);
        } else if (id == 0x61746164u) {  // "data"
            data = o + 8;
            len = std::min<std::size_t>(sz, b.size() - data);
            break;
        }
        o += 8 + sz + (sz & 1);
    }
    w.pcm.resize(len / 2);
    std::memcpy(w.pcm.data(), b.data() + data, w.pcm.size() * 2);
    return w;
}

// "DATA.CVM:\SOUND\X.AFS" -> <extracted>/DATA/SOUND/X.AFS; "BGM.CVM:\01.ADX" -> <extracted>/BGM/01.ADX.
fs::path host_path(const fs::path& extracted, const std::string& disc) {
    const std::size_t colon = disc.find(":\\");
    std::string rel = disc;
    fs::path root = extracted / "disc";
    if (colon != std::string::npos) {
        std::string vol = disc.substr(0, colon);
        if (vol.size() > 4) vol.resize(vol.size() - 4);  // "DATA.CVM" -> "DATA"
        root = extracted / vol;
        rel = disc.substr(colon + 2);
    }
    std::replace(rel.begin(), rel.end(), '\\', '/');
    return root / rel;
}

// A decodable ADX: a whole file or one member of an AFS.
struct Source {
    std::string name;
    std::vector<std::byte> bytes;
};

// Decodes `src` into interleaved PCM, at least `frames` frames when the file loops (else the file once).
std::vector<s16> decode(const Source& src, u64 frames) {
    auto d = audio::AdxDecoder::open(src.bytes);
    if (!d) return {};
    audio::AdxDecoder dec = std::move(d).value();
    if (dec.has_loop()) dec.set_loops(-1);
    std::vector<s16> out;
    std::vector<s16> buf(4096 * dec.channels());
    while (out.size() / dec.channels() < frames + 64) {
        const std::size_t n = dec.decode(buf);
        if (n == 0) break;
        out.insert(out.end(), buf.begin(), buf.begin() + static_cast<std::ptrdiff_t>(n * dec.channels()));
    }
    return out;
}

void for_each_adx(const fs::path& extracted, const std::function<void(const Source&)>& f);

int cmd_streams(const fs::path& extracted, const std::vector<fs::path>& runs) {
    u64 streams = 0, matched = 0, exact = 0, samples = 0, movie = 0, unmatched = 0, from_disc = 0, ranged = 0;
    for (const fs::path& run : runs) {
        // the ADX sources the run read: whole .ADX files, and the AFS members its reads touched
        std::map<std::string, Source> sources;
        std::ifstream log(run / "reads.txt");
        std::string line;
        std::map<std::string, std::vector<std::byte>> afs_cache;
        while (std::getline(log, line)) {
            const std::size_t p = line.find(" path="), q = line.find(" off=");
            if (p == std::string::npos || q == std::string::npos) continue;
            const std::string path = line.substr(p + 6, q - p - 6);
            const u64 off = std::strtoull(line.c_str() + q + 5, nullptr, 10);
            std::string up = path;
            for (char& c : up) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            if (up.size() > 4 && up.substr(up.size() - 4) == ".ADX") {
                if (!sources.count(path)) sources[path] = Source{path, read_file(host_path(extracted, path))};
            } else if (up.size() > 4 && up.substr(up.size() - 4) == ".AFS") {
                auto& bytes = afs_cache[path];
                if (bytes.empty()) bytes = read_file(host_path(extracted, path));
                auto v = formats::AfsView::parse(bytes);
                if (!v) continue;
                for (const formats::AfsEntry& e : v.value().entries()) {
                    if (off < e.offset || off >= u64{e.offset} + e.size || !formats::is_adx(e.data)) continue;
                    const std::string key = path + "#" + std::to_string(e.offset);
                    if (!sources.count(key)) sources[key] = Source{key, std::vector<std::byte>(e.data.begin(), e.data.end())};
                }
            }
        }
        for (const auto& entry : fs::directory_iterator(run / "wav")) {
            const std::string fname = entry.path().filename().string();
            if (fname.rfind("stream_", 0) != 0) continue;
            ++streams;
            const Wav w = read_wav(entry.path());
            if (w.channels == 0 || w.pcm.empty()) continue;
            const u64 frames = w.pcm.size() / w.channels;
            const Source* best = nullptr;
            std::vector<s16> best_pcm;
            for (const auto& [key, src] : sources) {
                auto info = formats::parse_adx(src.bytes);
                if (!info || info.value().header.channels != w.channels || info.value().header.sample_rate != w.rate) continue;
                std::vector<s16> d = decode(src, std::min<u64>(frames, 64));
                const std::size_t n = std::min<std::size_t>({d.size(), w.pcm.size(), std::size_t{64} * w.channels});
                if (n == 0 || !std::equal(d.begin(), d.begin() + static_cast<std::ptrdiff_t>(n), w.pcm.begin())) continue;
                best = &src;
                best_pcm = decode(src, frames);
                break;
            }
            std::size_t start = 0;  // the stream's first frame in the source (a range start: H_Cdvd_StartADXTFileRange)
            if (!best && w.rate != 48000 && frames >= 64) {
                for (const auto& [key, src] : sources) {
                    auto info = formats::parse_adx(src.bytes);
                    if (!info || info.value().header.channels != w.channels || info.value().header.sample_rate != w.rate) continue;
                    const std::vector<s16> d = decode(src, info.value().header.sample_count + frames);
                    const std::size_t win = std::size_t{64} * w.channels;
                    for (std::size_t i = 0; i + win <= d.size(); i += w.channels)
                        if (d[i] == w.pcm[0] && std::equal(d.begin() + static_cast<std::ptrdiff_t>(i),
                                                           d.begin() + static_cast<std::ptrdiff_t>(i + win), w.pcm.begin())) {
                            best = &src;
                            best_pcm.assign(d.begin() + static_cast<std::ptrdiff_t>(i), d.end());
                            start = i / w.channels;
                            break;
                        }
                    if (best) {
                        ++ranged;
                        break;
                    }
                }
            }
            if (best && start != 0)
                std::printf("  %s/%s: from frame %zu of %s\n", run.filename().string().c_str(), fname.c_str(), start,
                            best->name.c_str());
            if (!best && w.rate != 48000) {
                // not among the run's reads (a file the run loaded whole earlier, played from memory): every ADX
                // on the BGM and DATA volumes
                static std::vector<Source> all;
                if (all.empty())
                    for (const char* vol : {"BGM", "DATA"})
                        for_each_adx(extracted / vol, [&](const Source& s) { all.push_back(s); });
                for (const Source& src : all) {
                    auto info = formats::parse_adx(src.bytes);
                    if (!info || info.value().header.channels != w.channels || info.value().header.sample_rate != w.rate) continue;
                    std::vector<s16> d = decode(src, std::min<u64>(frames, 64));
                    const std::size_t n = std::min<std::size_t>({d.size(), w.pcm.size(), std::size_t{64} * w.channels});
                    if (n == 0 || !std::equal(d.begin(), d.begin() + static_cast<std::ptrdiff_t>(n), w.pcm.begin())) continue;
                    best = &src;
                    best_pcm = decode(src, frames);
                    ++from_disc;
                    break;
                }
            }
            if (!best) {
                if (w.rate == 48000) ++movie;  // Sofdec audio: inside the .SFD mux, not a file of its own
                else ++unmatched;
                std::printf("  %s/%s: %llu frames, %u Hz %u ch: no source among the run's reads%s\n",
                            run.filename().string().c_str(), fname.c_str(), static_cast<unsigned long long>(frames),
                            w.rate, w.channels, w.rate == 48000 ? " (a movie's audio)" : "");
                continue;
            }
            ++matched;
            const std::size_t n = std::min(best_pcm.size(), w.pcm.size());
            std::size_t first = n;
            for (std::size_t i = 0; i < n; ++i)
                if (best_pcm[i] != w.pcm[i]) {
                    first = i;
                    break;
                }
            // past the file's end (no loop) ADXT pads silence
            bool tail_silent = true;
            for (std::size_t i = n; i < w.pcm.size(); ++i) tail_silent &= w.pcm[i] == 0;
            const bool ok = first == n && tail_silent;
            exact += ok;
            samples += n;
            if (!ok)
                std::printf("  %s/%s vs %s: DIFFER at sample %zu of %zu%s\n", run.filename().string().c_str(),
                            fname.c_str(), best->name.c_str(), first, n, tail_silent ? "" : " (non-silent tail)");
        }
    }
    std::printf("streams %llu: matched to a file %llu (%llu from a later start, %llu not among the run's reads), "
                "bit-exact %llu (%llu samples compared); movie audio %llu, unmatched %llu\n",
                static_cast<unsigned long long>(streams), static_cast<unsigned long long>(matched),
                static_cast<unsigned long long>(ranged), static_cast<unsigned long long>(from_disc),
                static_cast<unsigned long long>(exact),
                static_cast<unsigned long long>(samples),
                static_cast<unsigned long long>(movie), static_cast<unsigned long long>(unmatched));
    return matched == exact && unmatched == 0 ? 0 : 1;
}

void for_each_adx(const fs::path& extracted, const std::function<void(const Source&)>& f) {
    for (const auto& e : fs::recursive_directory_iterator(extracted)) {
        if (!e.is_regular_file()) continue;
        std::string ext = e.path().extension().string();
        for (char& c : ext) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        if (ext == ".ADX") {
            f(Source{e.path().string(), read_file(e.path())});
        } else if (ext == ".AFS") {
            const std::vector<std::byte> b = read_file(e.path());
            auto v = formats::AfsView::parse(b);
            if (!v) continue;
            for (const formats::AfsEntry& m : v.value().entries())
                if (formats::is_adx(m.data))
                    f(Source{e.path().string() + "#" + std::to_string(m.offset), std::vector<std::byte>(m.data.begin(), m.data.end())});
        }
    }
}

int cmd_sweep(const fs::path& extracted) {
    u64 files = 0, ok = 0, frames = 0, loops = 0;
    for_each_adx(extracted, [&](const Source& s) {
        ++files;
        auto d = audio::AdxDecoder::open(s.bytes);
        if (!d) {
            std::printf("  %s: refused\n", s.name.c_str());
            return;
        }
        audio::AdxDecoder dec = std::move(d).value();
        loops += dec.has_loop();
        std::vector<s16> buf(8192 * dec.channels());
        u64 n = 0;
        for (std::size_t k; (k = dec.decode(buf)) != 0;) n += k;
        frames += n;
        if (n == dec.header().sample_count) ++ok;
        else std::printf("  %s: %llu frames, header %u\n", s.name.c_str(), static_cast<unsigned long long>(n), dec.header().sample_count);
    });
    std::printf("sweep: %llu ADX (files and AFS members), %llu decoded to their header's sample count, %llu frames, "
                "%llu with a loop\n",
                static_cast<unsigned long long>(files), static_cast<unsigned long long>(ok),
                static_cast<unsigned long long>(frames), static_cast<unsigned long long>(loops));
    return files == ok ? 0 : 1;
}

int cmd_vgm(const fs::path& extracted, const fs::path& vgm, const fs::path& tmp, u64 count) {
    std::vector<Source> pick;
    u64 seen = 0;
    for_each_adx(extracted, [&](const Source& s) {
        // spread the sample over the disc: every 37th ADX
        if (seen++ % 37 == 0 && pick.size() < count) pick.push_back(s);
    });
    fs::create_directories(tmp);
    u64 exact = 0, samples = 0;
    for (std::size_t i = 0; i < pick.size(); ++i) {
        const fs::path in = tmp / ("in" + std::to_string(i) + ".adx"), out = tmp / ("out" + std::to_string(i) + ".wav");
        {
            std::ofstream f(in, std::ios::binary);
            f.write(reinterpret_cast<const char*>(pick[i].bytes.data()), static_cast<std::streamsize>(pick[i].bytes.size()));
        }
        const std::string cmd = "\"\"" + vgm.string() + "\" -i -o \"" + out.string() + "\" \"" + in.string() + "\" >NUL 2>&1\"";
        if (std::system(cmd.c_str()) != 0) {
            std::printf("  %s: vgmstream-cli failed\n", pick[i].name.c_str());
            continue;
        }
        const Wav w = read_wav(out);
        auto ours = audio::decode_adx(pick[i].bytes, 0);
        fs::remove(in);
        fs::remove(out);
        if (!ours) continue;
        const std::vector<s16>& a = ours.value();
        const bool same = a == w.pcm;
        exact += same;
        samples += a.size();
        if (!same) {
            std::size_t diff = 0, first = ~std::size_t{0};
            int maxd = 0;
            for (std::size_t k = 0; k < std::min(a.size(), w.pcm.size()); ++k)
                if (a[k] != w.pcm[k]) {
                    ++diff;
                    first = std::min(first, k);
                    maxd = std::max(maxd, std::abs(int{a[k]} - int{w.pcm[k]}));
                }
            std::printf("  %s: ours %zu samples, vgmstream %zu; %zu differ (first %zu, max |d| %d)\n", pick[i].name.c_str(),
                        a.size(), w.pcm.size(), diff, first, maxd);
        }
    }
    std::printf("vgmstream-cli -i: %llu / %zu ADX identical sample for sample (%llu samples)\n",
                static_cast<unsigned long long>(exact), pick.size(), static_cast<unsigned long long>(samples));
    return exact == pick.size() ? 0 : 1;
}

// Check 3 of layer 3: the whole mix's per-channel RMS level, then each 0.5 s window of the faithful mix that is not
// silent against the native mix shifted by the lag in [-1024, 1024] frames with the smallest squared difference.
int cmd_mixcmp(const fs::path& fa, const fs::path& na) {
    const Wav f = read_wav(fa), n = read_wav(na);
    if (f.channels != 2 || n.channels != 2) {
        std::fprintf(stderr, "mixcmp: both files must be 16-bit stereo WAVs\n");
        return 2;
    }
    const std::size_t ff = f.pcm.size() / 2, nf = n.pcm.size() / 2;
    auto level = [](const Wav& w, int ch) {
        double e = 0;
        const std::size_t frames = w.pcm.size() / 2;
        for (std::size_t i = 0; i < frames; ++i) e += static_cast<double>(w.pcm[2 * i + ch]) * w.pcm[2 * i + ch];
        return frames ? 10.0 * std::log10(std::max(e / static_cast<double>(frames), 1e-12)) : -240.0;
    };
    std::printf("frames %zu / %zu; level native - faithful: L %+.3f dB, R %+.3f dB\n", ff, nf, level(n, 0) - level(f, 0), level(n, 1) - level(f, 1));
    constexpr std::size_t kWin = 24000;
    constexpr long kLag = 1024;
    std::vector<double> residual;
    std::size_t windows = 0, exact = 0, exact_lag0 = 0;
    for (std::size_t w0 = 0; w0 + kWin <= ff; w0 += kWin) {
        double ef = 0;
        for (std::size_t i = w0; i < w0 + kWin; ++i) ef += static_cast<double>(f.pcm[2 * i]) * f.pcm[2 * i] + static_cast<double>(f.pcm[2 * i + 1]) * f.pcm[2 * i + 1];
        if (ef == 0) continue;
        ++windows;
        double best = -1;
        long best_lag = 0;
        for (long k = 0; k <= 2 * kLag; ++k) {
            const long lag = (k & 1) ? (k + 1) / 2 : -(k / 2);  // 0, +1, -1, +2, -2, ...
            double sse = 0;
            for (std::size_t i = w0; i < w0 + kWin; ++i) {
                const long j = static_cast<long>(i) + lag;
                const double nl = (j >= 0 && static_cast<std::size_t>(j) < nf) ? n.pcm[2 * static_cast<std::size_t>(j)] : 0.0;
                const double nr = (j >= 0 && static_cast<std::size_t>(j) < nf) ? n.pcm[2 * static_cast<std::size_t>(j) + 1] : 0.0;
                const double dl = f.pcm[2 * i] - nl, dr = f.pcm[2 * i + 1] - nr;
                sse += dl * dl + dr * dr;
                if (best >= 0 && sse >= best) break;
            }
            if (best < 0 || sse < best) {
                best = sse;
                best_lag = lag;
            }
            if (best == 0) break;
        }
        if (best == 0) {
            ++exact;
            if (best_lag == 0) ++exact_lag0;
        } else {
            residual.push_back(10.0 * std::log10(best / ef));
        }
    }
    std::sort(residual.begin(), residual.end());
    auto pct = [&](double q) {
        if (residual.empty()) return std::string("exact");
        // over all windows: the bit-exact ones count as the lowest residuals
        const double pos = q * static_cast<double>(windows - 1);
        const std::size_t idx = static_cast<std::size_t>(pos + 0.5);
        if (idx < exact) return std::string("exact");
        char b[32];
        std::snprintf(b, sizeof b, "%.1f dB", residual[std::min(idx - exact, residual.size() - 1)]);
        return std::string(b);
    };
    std::printf("windows %zu (non-silent, 0.5 s): %zu bit-exact after the lag (%zu at lag 0); residual median %s, 90th percentile %s\n", windows, exact,
                exact_lag0, pct(0.5).c_str(), pct(0.9).c_str());
    return 0;
}
}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: p3fes_native_sound_check streams|sweep|vgm --extracted DIR ...\n");
        return 2;
    }
    const std::string cmd = argv[1];
    if (cmd == "mixcmp" && argc == 4) return cmd_mixcmp(argv[2], argv[3]);
    fs::path extracted, vgm, tmp;
    u64 count = 20;
    std::vector<fs::path> runs;
    for (int i = 2; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--extracted" && i + 1 < argc) extracted = argv[++i];
        else if (a == "--vgmstream" && i + 1 < argc) vgm = argv[++i];
        else if (a == "--tmp" && i + 1 < argc) tmp = argv[++i];
        else if (a == "--count" && i + 1 < argc) count = std::strtoull(argv[++i], nullptr, 10);
        else runs.emplace_back(a);
    }
    if (extracted.empty()) {
        std::fprintf(stderr, "--extracted DIR is required\n");
        return 2;
    }
    if (cmd == "streams") return cmd_streams(extracted, runs);
    if (cmd == "sweep") return cmd_sweep(extracted);
    if (cmd == "vgm" && !vgm.empty() && !tmp.empty()) return cmd_vgm(extracted, vgm, tmp, count);
    std::fprintf(stderr, "unknown command or missing argument\n");
    return 2;
}
