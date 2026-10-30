// RIFF/WAVE PCM16 output: a streaming writer, a timeline sink for the mixed stream and a per-stream
// dumper for the IOP's consumed PCM. Output goes wherever the caller says; the host's --dump-wav
// default is the gitignored extracted/_ours/wav/ (HostAudio, host_audio.h).
#pragma once

#include <cstdio>
#include <filesystem>
#include <map>
#include <span>
#include <string>
#include <vector>

#include "p3fes/audio/audio_sink.h"

namespace p3fes::audio {

// Builds a complete WAV image in memory (canonical 44-byte header, PCM16 little-endian).
std::vector<u8> wav_image(u32 sample_rate, u16 channels, std::span<const s16> interleaved);

class WavWriter {
public:
    WavWriter() = default;
    ~WavWriter();
    WavWriter(const WavWriter&) = delete;
    WavWriter& operator=(const WavWriter&) = delete;

    // Creates the file (and its parent directories). false on failure.
    bool open(const std::filesystem::path& path, u32 sample_rate, u16 channels);
    void write(std::span<const s16> interleaved);
    void write_silence(u64 frames);
    // Patches the RIFF/data sizes and closes. Also called by the destructor.
    bool close();
    bool is_open() const { return f_ != nullptr; }
    u64 frames() const { return frames_; }
    u16 channels() const { return channels_; }
    const std::filesystem::path& path() const { return path_; }

private:
    std::FILE* f_ = nullptr;
    std::filesystem::path path_;
    u32 rate_ = 0;
    u16 channels_ = 0;
    u64 frames_ = 0;
    bool failed_ = false;
};

// The mixed 48 kHz stereo stream into one file; gaps become silence, the first push is t = 0
// (`origin_frame()` records where that was on the virtual timeline).
class WavSink final : public AudioSink {
public:
    explicit WavSink(std::filesystem::path path) : path_(std::move(path)) {}
    void push(u64 first_frame, std::span<const s16> interleaved) override;
    void flush() override {  // final: later pushes are ignored (the file is never reopened/truncated)
        writer_.close();
        closed_ = true;
    }
    u64 origin_frame() const { return cursor_.origin(); }
    u64 frames() const { return writer_.frames(); }
    bool ok() const { return !failed_; }
    const std::filesystem::path& path() const { return path_; }
private:
    std::filesystem::path path_;
    WavWriter writer_;
    TimelineCursor cursor_;
    bool failed_ = false;
    bool closed_ = false;
};

// One WAV per stream: <dir>/stream_<id:04>_slot<slot:02>_<rate>hz_<ch>ch.wav. Channels are
// interleaved as they arrive (a channel that runs ahead is buffered; at stream end the shorter
// channel is padded with zeros).
class WavStreamDumper final : public StreamTap {
public:
    explicit WavStreamDumper(std::filesystem::path dir) : dir_(std::move(dir)) {}
    ~WavStreamDumper() override;
    void stream_begin(const StreamInfo& info) override;
    void stream_data(u32 id, u32 channel, std::span<const s16> samples) override;
    void stream_end(u32 id) override;
    void close_all();
    std::vector<std::filesystem::path> files() const { return files_; }
private:
    struct Open {
        StreamInfo info;
        WavWriter writer;
        std::array<std::vector<s16>, 2> pending;
    };
    std::filesystem::path dir_;
    std::map<u32, Open> open_;
    std::vector<std::filesystem::path> files_;
    void drain(Open& o, bool final);
};

}  // namespace p3fes::audio
