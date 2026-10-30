#include "p3fes/audio/wav.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <system_error>

namespace p3fes::audio {
namespace {

void put16(std::vector<u8>& v, std::size_t off, u16 x) {
    v[off] = static_cast<u8>(x);
    v[off + 1] = static_cast<u8>(x >> 8);
}
void put32(std::vector<u8>& v, std::size_t off, u32 x) {
    for (int i = 0; i < 4; ++i) v[off + i] = static_cast<u8>(x >> (8 * i));
}

// Canonical 44-byte PCM16 header for `data_bytes` of samples.
std::vector<u8> header(u32 rate, u16 channels, u32 data_bytes) {
    std::vector<u8> h(44, 0);
    std::memcpy(h.data() + 0, "RIFF", 4);
    put32(h, 4, 36u + data_bytes);
    std::memcpy(h.data() + 8, "WAVE", 4);
    std::memcpy(h.data() + 12, "fmt ", 4);
    put32(h, 16, 16);                          // fmt chunk size
    put16(h, 20, 1);                           // PCM
    put16(h, 22, channels);
    put32(h, 24, rate);
    put32(h, 28, rate * channels * 2u);        // byte rate
    put16(h, 32, static_cast<u16>(channels * 2u));  // block align
    put16(h, 34, 16);                          // bits per sample
    std::memcpy(h.data() + 36, "data", 4);
    put32(h, 40, data_bytes);
    return h;
}

std::FILE* open_file(const std::filesystem::path& p, const char* mode, const wchar_t* wmode) {
#ifdef _WIN32
    (void)mode;
    return _wfopen(p.c_str(), wmode);
#else
    (void)wmode;
    return std::fopen(p.string().c_str(), mode);
#endif
}

}  // namespace

std::vector<u8> wav_image(u32 sample_rate, u16 channels, std::span<const s16> interleaved) {
    const u32 bytes = static_cast<u32>(interleaved.size() * 2);
    std::vector<u8> v = header(sample_rate, channels, bytes);
    v.resize(44 + bytes);
    for (std::size_t i = 0; i < interleaved.size(); ++i) put16(v, 44 + 2 * i, static_cast<u16>(interleaved[i]));
    return v;
}

WavWriter::~WavWriter() { close(); }

bool WavWriter::open(const std::filesystem::path& path, u32 sample_rate, u16 channels) {
    close();
    std::error_code ec;
    if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path(), ec);
    f_ = open_file(path, "wb", L"wb");
    if (f_ == nullptr) return false;
    path_ = path;
    rate_ = sample_rate;
    channels_ = channels;
    frames_ = 0;
    failed_ = false;
    const std::vector<u8> h = header(rate_, channels_, 0);
    failed_ = std::fwrite(h.data(), 1, h.size(), f_) != h.size();
    return !failed_;
}

void WavWriter::write(std::span<const s16> interleaved) {
    if (f_ == nullptr || interleaved.empty()) return;
    // Host and WAV are both little-endian (x64).
    failed_ |= std::fwrite(interleaved.data(), sizeof(s16), interleaved.size(), f_) != interleaved.size();
    frames_ += interleaved.size() / std::max<u16>(channels_, 1);
}

void WavWriter::write_silence(u64 frames) {
    if (f_ == nullptr || frames == 0) return;
    static const std::array<s16, 2048> kZero{};
    u64 samples = frames * channels_;
    while (samples > 0) {
        const std::size_t n = static_cast<std::size_t>(std::min<u64>(samples, kZero.size()));
        failed_ |= std::fwrite(kZero.data(), sizeof(s16), n, f_) != n;
        samples -= n;
    }
    frames_ += frames;
}

bool WavWriter::close() {
    if (f_ == nullptr) return !failed_;
    const u64 data = frames_ * channels_ * 2ull;
    const u32 data32 = data > 0xFFFFFFD3ull ? 0xFFFFFFD3u : static_cast<u32>(data);  // RIFF is 32-bit
    const std::vector<u8> h = header(rate_, channels_, data32);
    if (std::fseek(f_, 0, SEEK_SET) == 0) failed_ |= std::fwrite(h.data(), 1, h.size(), f_) != h.size();
    else failed_ = true;
    failed_ |= std::fclose(f_) != 0;
    f_ = nullptr;
    return !failed_;
}

void WavSink::push(u64 first_frame, std::span<const s16> interleaved) {
    if (failed_ || closed_) return;
    if (!writer_.is_open()) {
        if (!writer_.open(path_, kOutputRate, kOutputChannels)) {
            failed_ = true;
            return;
        }
    }
    const u64 n = interleaved.size() / kOutputChannels;
    const TimelineCursor::Placement p = cursor_.place(first_frame, n);
    writer_.write_silence(p.silence);
    if (p.skip < n) writer_.write(interleaved.subspan(static_cast<std::size_t>(p.skip * kOutputChannels)));
}

WavStreamDumper::~WavStreamDumper() { close_all(); }

void WavStreamDumper::stream_begin(const StreamInfo& info) {
    stream_end(info.id);
    Open& o = open_[info.id];
    o.info = info;
    char name[96];
    std::snprintf(name, sizeof name, "stream_%04u_slot%02u_%uhz_%uch.wav", info.id, info.slot, info.sample_rate,
                  info.channels);
    const std::filesystem::path p = dir_ / name;
    if (o.writer.open(p, info.sample_rate ? info.sample_rate : kOutputRate,
                      static_cast<u16>(std::clamp<u32>(info.channels, 1, 2))))
        files_.push_back(p);
}

void WavStreamDumper::drain(Open& o, bool final) {
    const u32 ch = std::clamp<u32>(o.info.channels, 1, 2);
    if (ch == 1) {
        o.writer.write(o.pending[0]);
        o.pending[0].clear();
        return;
    }
    std::size_t n = std::min(o.pending[0].size(), o.pending[1].size());
    if (final) n = std::max(o.pending[0].size(), o.pending[1].size());
    if (n == 0) return;
    std::vector<s16> inter(n * 2);
    for (std::size_t i = 0; i < n; ++i) {
        inter[2 * i] = i < o.pending[0].size() ? o.pending[0][i] : 0;
        inter[2 * i + 1] = i < o.pending[1].size() ? o.pending[1][i] : 0;
    }
    o.writer.write(inter);
    for (auto& p : o.pending) p.erase(p.begin(), p.begin() + static_cast<std::ptrdiff_t>(std::min(n, p.size())));
}

void WavStreamDumper::stream_data(u32 id, u32 channel, std::span<const s16> samples) {
    auto it = open_.find(id);
    if (it == open_.end() || channel > 1) return;
    it->second.pending[channel].insert(it->second.pending[channel].end(), samples.begin(), samples.end());
    drain(it->second, false);
}

void WavStreamDumper::stream_end(u32 id) {
    auto it = open_.find(id);
    if (it == open_.end()) return;
    drain(it->second, true);
    it->second.writer.close();
    open_.erase(it);
}

void WavStreamDumper::close_all() {
    while (!open_.empty()) stream_end(open_.begin()->first);
}

}  // namespace p3fes::audio
