// Host audio output (runtime/audio/README.md).
//
// Audio is produced by the IOP HLE (CRI_ADXI's PSM mixer model, runtime/hle/sif/iop/srv_adxi.cpp)
// from *virtual* time: the sink receives frames tagged with their position on a timeline that is a
// pure function of EE cycles (ADR-0013 Timebase), never of the wall clock. Headless runs therefore
// produce byte-identical audio for identical inputs; only the XAudio2 sink looks at the host clock,
// and only to pace (block) the producer in windowed mode.
//
// Two interfaces:
//   * AudioSink: the mixed 48 kHz stereo s16 stream (what SPU2 core 0 would play).
//   * StreamTap: the per-stream PCM the IOP consumed (the game's own ADX decoder output, one stream
//     per CRI RNA play session) -- used by --dump-wav.
// Single-threaded, like the rest of the runtime (ADR-0013 §1).
#pragma once

#include <array>
#include <cstddef>
#include <span>
#include <string>
#include <vector>

#include "p3fes/ee_types.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h (machine states)
}

namespace p3fes::audio {

inline constexpr u64 kEeClockHz = 294'912'000;  // EE cycles per virtual second (ADR-0013 §2)
inline constexpr u32 kOutputRate = 48'000;      // SPU2 output rate (CRI PSM output, IRX 0x5864)
inline constexpr u32 kOutputChannels = 2;
inline constexpr u64 kCyclesPerOutputFrame = kEeClockHz / kOutputRate;  // 6144, exact
static_assert(kEeClockHz % kOutputRate == 0);

// Timeline <-> virtual time. frames_at_cycles(c) = floor(c * rate / kEeClockHz) without overflow;
// cycles_at_frame(f) = the first cycle c with frames_at_cycles(c) >= f.
constexpr u64 frames_at_cycles(u64 cycles, u32 rate = kOutputRate) {
    return (cycles / kEeClockHz) * rate + ((cycles % kEeClockHz) * rate) / kEeClockHz;
}
constexpr u64 cycles_at_frame(u64 frame, u32 rate = kOutputRate) {
    const u64 q = frame / rate, r = frame % rate;
    return q * kEeClockHz + (r * kEeClockHz + rate - 1) / rate;
}

// The mixed output stream: 48 kHz, 2 channels, interleaved s16 (L, R).
class AudioSink {
public:
    virtual ~AudioSink() = default;
    // `interleaved.size()` must be a multiple of kOutputChannels. `first_frame` is the timeline
    // position of the first frame; positions never go backwards (a push that overlaps the previous
    // one is clipped by the sink). A gap between pushes is silence.
    virtual void push(u64 first_frame, std::span<const s16> interleaved) = 0;
    // End of stream (process exit, IOP reboot): sinks finalise files / drain queues.
    virtual void flush() {}
};

// One CRI RNA play session as the IOP consumed it (before resampling/mixing).
struct StreamInfo {
    u32 id = 0;           // sequential per IopHle, from 1
    u32 slot = 0;         // IOP RNA slot (0..15)
    u32 channels = 0;     // 1 or 2
    u32 sample_rate = 0;  // the RNA's input sfreq (RNA command 4)
};
class StreamTap {
public:
    virtual ~StreamTap() = default;
    virtual void stream_begin(const StreamInfo& info) = 0;
    // Planar: the samples of one channel, in consumption order.
    virtual void stream_data(u32 id, u32 channel, std::span<const s16> samples) = 0;
    virtual void stream_end(u32 id) = 0;
};

// Discards audio but keeps a determinism fingerprint (headless runs, tests).
class NullSink final : public AudioSink {
public:
    void push(u64 first_frame, std::span<const s16> interleaved) override;
    u64 frames() const { return frames_; }            // frames received
    u64 end_frame() const { return end_; }            // timeline position after the last frame
    u64 first_frame() const { return first_; }        // position of the first frame ever pushed
    u64 gap_frames() const { return gap_frames_; }    // silence implied by gaps
    u64 clipped_frames() const { return clipped_; }   // overlapping frames dropped
    u64 non_silent_frames() const { return non_silent_; }
    u64 first_non_silent_frame() const { return first_non_silent_; }  // ~0 while every frame was silent
    u64 hash() const { return hash_; }                // FNV-1a over (position, samples)
    s32 peak() const { return peak_; }                // max |sample|
    void state(StateIo& io);                          // machine state (audio_sink.cpp)
private:
    u64 frames_ = 0, end_ = 0, first_ = 0, gap_frames_ = 0, clipped_ = 0, non_silent_ = 0, first_non_silent_ = ~0ull;
    u64 hash_ = 0xcbf29ce484222325ull;
    s32 peak_ = 0;
    bool any_ = false;
};

// Fans one stream out to several sinks / taps (nullptrs are skipped).
class TeeSink final : public AudioSink {
public:
    void add(AudioSink* s) { if (s) sinks_.push_back(s); }
    void push(u64 first_frame, std::span<const s16> interleaved) override {
        for (AudioSink* s : sinks_) s->push(first_frame, interleaved);
    }
    void flush() override {
        for (AudioSink* s : sinks_) s->flush();
    }
    bool empty() const { return sinks_.empty(); }
private:
    std::vector<AudioSink*> sinks_;
};
class TeeTap final : public StreamTap {
public:
    void add(StreamTap* t) { if (t) taps_.push_back(t); }
    void stream_begin(const StreamInfo& i) override { for (auto* t : taps_) t->stream_begin(i); }
    void stream_data(u32 id, u32 ch, std::span<const s16> s) override { for (auto* t : taps_) t->stream_data(id, ch, s); }
    void stream_end(u32 id) override { for (auto* t : taps_) t->stream_end(id); }
    bool empty() const { return taps_.empty(); }
private:
    std::vector<StreamTap*> taps_;
};

// Turns pushes with gaps/overlaps into a contiguous stream: `place` returns how many silent frames
// must be emitted before the data and how many leading frames of the data to skip. Shared by the
// WAV and XAudio2 sinks; the first push defines the origin.
class TimelineCursor {
public:
    struct Placement {
        u64 silence = 0;     // frames of silence to emit first
        u64 skip = 0;        // leading frames of the push already covered (overlap)
    };
    Placement place(u64 first_frame, u64 frames);
    bool started() const { return started_; }
    u64 origin() const { return origin_; }
    u64 next() const { return next_; }
private:
    bool started_ = false;
    u64 origin_ = 0, next_ = 0;
};

}  // namespace p3fes::audio
