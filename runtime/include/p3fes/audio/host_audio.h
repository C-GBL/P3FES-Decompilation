// The host's audio composition: one object the host constructs from its command line and hands to
// the IOP HLE (runtime/audio/README.md "Host wiring"):
//
//     p3fes::audio::HostAudio audio({.xaudio2 = !headless, .pace = !headless, .dump_wav_dir = dir});
//     sif.iop().set_audio_output(audio.mix_sink(), audio.stream_tap());
//
// * xaudio2: play the mix through XAudio2 (falls back to silence, logged, when the device fails);
// * dump_wav_dir (--dump-wav DIR): write the mix to DIR/mix_48k.wav and every RNA play session the
//   IOP consumed (the game's decoded ADX PCM) to DIR/stream_*.wav. Suggested default: the gitignored
//   extracted/_ours/wav/ (default_dump_dir()).
// Headless without --dump-wav: a NullSink keeps a determinism fingerprint (stats()).
#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "p3fes/audio/audio_sink.h"

struct IXAudio2;

namespace p3fes::audio {

class WavSink;
class WavStreamDumper;
class XAudio2Sink;

struct HostAudioOptions {
    bool xaudio2 = false;
    bool pace = false;                   // XAudio2 back-pressure (windowed only)
    bool rate_control = false;           // XAudio2 queue steered by the voice's frequency ratio (frame pacing)
    unsigned target_queued_ms = 60;      // ... to this length
    std::filesystem::path dump_wav_dir;  // empty = no WAV dumps
    IXAudio2* engine = nullptr;          // borrow an engine (XAudio2Backend::engine()); else own one
};

// <repo root>/extracted/_ours/wav
std::filesystem::path default_dump_dir(const std::filesystem::path& repo_root);

class HostAudio {
public:
    explicit HostAudio(HostAudioOptions opt);
    ~HostAudio();
    HostAudio(const HostAudio&) = delete;
    HostAudio& operator=(const HostAudio&) = delete;

    AudioSink* mix_sink() { return &tee_; }
    StreamTap* stream_tap() { return tap_.empty() ? nullptr : &tap_; }
    void flush();

    bool xaudio2_active() const;
    const XAudio2Sink* xaudio2() const { return xa_.get(); }  // nullptr when inactive (telemetry)
    const NullSink& fingerprint() const { return null_; }  // always fed
    // Machine state: the fingerprint only (XAudio2 / WAV outputs are host outputs; a loaded run starts them anew).
    void state(StateIo& io) { null_.state(io); }
    std::string describe() const;                          // one line for the host log

private:
    HostAudioOptions opt_;
    NullSink null_;
    TeeSink tee_;
    TeeTap tap_;
    std::unique_ptr<XAudio2Sink> xa_;
    std::unique_ptr<WavSink> wav_;
    std::unique_ptr<WavStreamDumper> dumper_;
};

}  // namespace p3fes::audio
