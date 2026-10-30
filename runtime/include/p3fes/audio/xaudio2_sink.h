// XAudio2 output for the mixed 48 kHz stereo stream (windowed runs).
//
// The sink queues fixed-size buffers on one source voice. It never feeds anything back into the
// guest: the producer (the IOP HLE) runs on virtual time, so what the guest observes is independent
// of the host device. With `pace` set, push() blocks while more than `max_queued_ms` of audio is
// queued -- the only place the wall clock is consulted -- which throttles a faster-than-real-time
// emulation to the audio clock. Headless runs use NullSink/WavSink instead and never pace.
//
// Rate control (frame pacing, docs/ANALYSIS/31 §5): the host paces video to its own clock (QPC, or the display's
// refresh), which drifts against the audio device's crystal by up to ~0.1 %. With `rate_control` the sink keeps
// the queue near `target_queued_ms` by playing the source voice up to +-0.5 % fast or slow
// (IXAudio2SourceVoice::SetFrequencyRatio, an inaudible pitch change), so the queue neither underruns (crackle) nor
// grows into the back-pressure limit (which would stall the guest thread mid-frame).
#pragma once

#include <memory>
#include <span>

#include "p3fes/audio/audio_sink.h"

struct IXAudio2;  // xaudio2.h

namespace p3fes::audio {

class XAudio2Sink final : public AudioSink {
public:
    struct Options {
        bool pace = false;          // block push() while the queue is longer than max_queued_ms
        u32 max_queued_ms = 120;
        u32 buffer_frames = 1024;   // frames per submitted buffer (21.3 ms)
        u32 buffers = 48;           // ring size (<= XAUDIO2_MAX_QUEUED_BUFFERS = 64)
        bool rate_control = false;  // steer the queue to target_queued_ms with the voice's frequency ratio
        u32 target_queued_ms = 80;
        double max_ratio_dev = 0.005;
    };
    struct Stats {
        u64 frames_submitted = 0;
        u64 buffers_submitted = 0;
        u64 frames_dropped = 0;     // queue full while not pacing
        u64 pace_waits = 0;         // push() calls that blocked
        u64 silence_frames = 0;     // gap fill
        double pace_wait_ms = 0.0;  // wall time push() spent blocked
        u64 underruns = 0;          // buffers submitted to a voice that had run dry
        double ratio = 1.0;         // the voice's frequency ratio now (rate control)
        double queued_ms = 0.0;     // smoothed queue length (rate control), else the last measured
    };

    XAudio2Sink();
    ~XAudio2Sink() override;
    XAudio2Sink(const XAudio2Sink&) = delete;
    XAudio2Sink& operator=(const XAudio2Sink&) = delete;

    // Creates the source voice on `engine` (borrowed; e.g. XAudio2Backend::engine()) or, when
    // nullptr, on an engine + mastering voice of its own. false on failure (last_hresult()).
    bool init(const Options& opt, IXAudio2* engine = nullptr);
    void shutdown();
    bool ready() const;
    long last_hresult() const;  // HRESULT

    void push(u64 first_frame, std::span<const s16> interleaved) override;
    void flush() override;      // submit the partial buffer
    u64 queued_frames() const;  // frames submitted and not yet played
    const Stats& stats() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace p3fes::audio
