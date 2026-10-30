#include "p3fes/audio/xaudio2_sink.h"

#include <windows.h>
#include <objbase.h>
#include <xaudio2.h>

#include <algorithm>
#include <cmath>
#include <vector>

namespace p3fes::audio {

struct XAudio2Sink::Impl {
    Options opt{};
    Stats stats{};
    IXAudio2* engine = nullptr;
    bool own_engine = false;
    bool com = false;
    IXAudio2MasteringVoice* master = nullptr;
    IXAudio2SourceVoice* voice = nullptr;
    HRESULT hr = S_OK;
    std::vector<std::vector<s16>> ring;
    std::size_t cur = 0;        // ring slot being filled
    std::size_t fill = 0;       // frames in ring[cur]
    TimelineCursor cursor;
    u64 frames_queued_total = 0;  // frames handed to the voice (rate control: queue = this - SamplesPlayed)
    double ema_ms = -1.0;         // smoothed queue length
    LARGE_INTEGER last_qpc{};
    std::vector<s16> preroll;     // silence queued in front after running dry (rate control; stays valid while queued)
    bool gap = false;  // a timeline gap (the IOP stopped its output) since the last submit: running dry is no underrun

    u32 queued_buffers() const {
        if (voice == nullptr) return 0;
        XAUDIO2_VOICE_STATE st{};
        voice->GetState(&st, XAUDIO2_VOICE_NOSAMPLESPLAYED);
        return st.BuffersQueued;
    }
    // Rate control: the exact queue (frames handed over minus frames played), smoothed over ~1 s, steers the
    // frequency ratio proportionally: +-max_ratio_dev at +-50 % of the target.
    void steer() {
        XAUDIO2_VOICE_STATE st{};
        voice->GetState(&st, 0);
        const double queued = static_cast<double>(frames_queued_total) - static_cast<double>(st.SamplesPlayed);
        const double ms = std::max(0.0, queued) * 1000.0 / kOutputRate;
        LARGE_INTEGER now, f;
        QueryPerformanceCounter(&now);
        QueryPerformanceFrequency(&f);
        const double dt = last_qpc.QuadPart ? static_cast<double>(now.QuadPart - last_qpc.QuadPart) / static_cast<double>(f.QuadPart) : 0.0;
        last_qpc = now;
        const double a = std::clamp(dt / 1.0, 0.0, 1.0);
        ema_ms = ema_ms < 0.0 ? ms : ema_ms + a * (ms - ema_ms);
        stats.queued_ms = ema_ms;
        const double target = static_cast<double>(opt.target_queued_ms);
        const double err = (ema_ms - target) / (0.5 * target);
        const double r = 1.0 + std::clamp(err, -1.0, 1.0) * opt.max_ratio_dev;
        if (std::fabs(r - stats.ratio) >= 2e-5) {
            if (SUCCEEDED(voice->SetFrequencyRatio(static_cast<float>(r)))) stats.ratio = r;
        }
    }
    void submit() {
        if (fill == 0 || voice == nullptr) return;
        const u32 limit_ms = opt.rate_control ? std::max(opt.max_queued_ms, 3 * opt.target_queued_ms) : opt.max_queued_ms;
        const u64 max_frames = static_cast<u64>(limit_ms) * kOutputRate / 1000;
        if (opt.pace) {
            // Back-pressure: wait (bounded) for the device to play down to the latency target.
            bool waited = false;
            LARGE_INTEGER t0{};
            for (int spins = 0; spins < 2000 && static_cast<u64>(queued_buffers()) * opt.buffer_frames > max_frames; ++spins) {
                if (!waited) QueryPerformanceCounter(&t0);
                waited = true;
                Sleep(1);
            }
            if (waited) {
                ++stats.pace_waits;
                LARGE_INTEGER t1, f;
                QueryPerformanceCounter(&t1);
                QueryPerformanceFrequency(&f);
                stats.pace_wait_ms += static_cast<double>(t1.QuadPart - t0.QuadPart) * 1000.0 / static_cast<double>(f.QuadPart);
            }
        }
        const bool dry = queued_buffers() == 0;
        if (stats.buffers_submitted && !gap && dry) ++stats.underruns;  // ran dry mid-stream
        gap = false;
        if (dry && opt.rate_control) {
            // Start (or restart after running dry) with the target queue of silence in front, so the first heavy
            // frames do not underrun while rate control would still be filling the queue at 0.5 %.
            preroll.assign(static_cast<std::size_t>(opt.target_queued_ms) * kOutputRate / 1000 * kOutputChannels, 0);
            XAUDIO2_BUFFER z{};
            z.AudioBytes = static_cast<UINT32>(preroll.size() * sizeof(s16));
            z.pAudioData = reinterpret_cast<const BYTE*>(preroll.data());
            if (!preroll.empty() && SUCCEEDED(voice->SubmitSourceBuffer(&z))) {
                frames_queued_total += preroll.size() / kOutputChannels;
                stats.silence_frames += preroll.size() / kOutputChannels;
            }
        }
        if (queued_buffers() >= ring.size() || queued_buffers() >= XAUDIO2_MAX_QUEUED_BUFFERS) {
            stats.frames_dropped += fill;  // device not draining and not pacing: drop, never block
            fill = 0;
            return;
        }
        XAUDIO2_BUFFER b{};
        b.AudioBytes = static_cast<UINT32>(fill * kOutputChannels * sizeof(s16));
        b.pAudioData = reinterpret_cast<const BYTE*>(ring[cur].data());
        hr = voice->SubmitSourceBuffer(&b);
        if (SUCCEEDED(hr)) {
            stats.frames_submitted += fill;
            frames_queued_total += fill;
            ++stats.buffers_submitted;
            if (opt.rate_control) steer();
        } else {
            stats.frames_dropped += fill;
        }
        cur = (cur + 1) % ring.size();
        fill = 0;
    }
    // The slot about to be filled is still owned by the device only when every slot is queued.
    bool slot_free() {
        if (fill > 0) return true;
        if (opt.pace)
            for (int spins = 0; spins < 2000 && queued_buffers() >= ring.size(); ++spins) Sleep(1);
        return queued_buffers() < ring.size();
    }
    void append(const s16* data, u64 frames) {  // data == nullptr: silence
        while (frames > 0) {
            if (!slot_free()) {
                stats.frames_dropped += frames;  // never overwrite a queued buffer
                return;
            }
            const std::size_t room = opt.buffer_frames - fill;
            const std::size_t n = static_cast<std::size_t>(std::min<u64>(room, frames));
            s16* dst = ring[cur].data() + fill * kOutputChannels;
            if (data) {
                std::copy(data, data + n * kOutputChannels, dst);
                data += n * kOutputChannels;
            } else {
                std::fill(dst, dst + n * kOutputChannels, static_cast<s16>(0));
            }
            fill += n;
            frames -= n;
            if (fill == opt.buffer_frames) submit();
        }
    }
};

XAudio2Sink::XAudio2Sink() : impl_(std::make_unique<Impl>()) {}
XAudio2Sink::~XAudio2Sink() { shutdown(); }

bool XAudio2Sink::init(const Options& opt, IXAudio2* engine) {
    shutdown();
    Impl& m = *impl_;
    m.opt = opt;
    m.opt.buffers = std::clamp<u32>(m.opt.buffers, 2, XAUDIO2_MAX_QUEUED_BUFFERS);
    m.opt.buffer_frames = std::max<u32>(m.opt.buffer_frames, 64);
    m.ring.assign(m.opt.buffers, std::vector<s16>(static_cast<std::size_t>(m.opt.buffer_frames) * kOutputChannels));
    if (engine == nullptr) {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if (SUCCEEDED(hr)) m.com = true;
        hr = XAudio2Create(&m.engine, 0, XAUDIO2_DEFAULT_PROCESSOR);
        if (FAILED(hr)) {
            m.hr = hr;
            shutdown();
            return false;
        }
        m.own_engine = true;
        hr = m.engine->CreateMasteringVoice(&m.master, kOutputChannels, kOutputRate);
        if (FAILED(hr)) {
            m.hr = hr;
            shutdown();
            return false;
        }
    } else {
        m.engine = engine;
    }
    WAVEFORMATEX fmt{};
    fmt.wFormatTag = WAVE_FORMAT_PCM;
    fmt.nChannels = kOutputChannels;
    fmt.nSamplesPerSec = kOutputRate;
    fmt.wBitsPerSample = 16;
    fmt.nBlockAlign = static_cast<WORD>(kOutputChannels * 2);
    fmt.nAvgBytesPerSec = kOutputRate * fmt.nBlockAlign;
    HRESULT hr = m.engine->CreateSourceVoice(&m.voice, &fmt);
    if (FAILED(hr)) {
        m.hr = hr;
        shutdown();
        return false;
    }
    hr = m.voice->Start(0);
    m.hr = hr;
    if (FAILED(hr)) {
        shutdown();
        return false;
    }
    return true;
}

void XAudio2Sink::shutdown() {
    Impl& m = *impl_;
    if (m.voice) {
        m.voice->Stop(0);
        m.voice->FlushSourceBuffers();
        m.voice->DestroyVoice();
        m.voice = nullptr;
    }
    if (m.master) {
        m.master->DestroyVoice();
        m.master = nullptr;
    }
    if (m.engine && m.own_engine) m.engine->Release();
    m.engine = nullptr;
    m.own_engine = false;
    if (m.com) {
        CoUninitialize();
        m.com = false;
    }
    m.fill = 0;
    m.cur = 0;
}

bool XAudio2Sink::ready() const { return impl_->voice != nullptr; }
long XAudio2Sink::last_hresult() const { return impl_->hr; }
const XAudio2Sink::Stats& XAudio2Sink::stats() const { return impl_->stats; }

u64 XAudio2Sink::queued_frames() const {
    return static_cast<u64>(impl_->queued_buffers()) * impl_->opt.buffer_frames + impl_->fill;
}

void XAudio2Sink::push(u64 first_frame, std::span<const s16> interleaved) {
    Impl& m = *impl_;
    if (m.voice == nullptr) return;
    const u64 n = interleaved.size() / kOutputChannels;
    const TimelineCursor::Placement p = m.cursor.place(first_frame, n);
    // A long gap (the IOP's output was stopped) is not replayed as seconds of silence: cap it at one
    // latency window so the device does not fall behind the emulation.
    const u64 cap = static_cast<u64>(m.opt.max_queued_ms) * kOutputRate / 1000;
    const u64 silence = std::min<u64>(p.silence, cap);
    if (p.silence) m.gap = true;
    m.stats.silence_frames += silence;
    m.append(nullptr, silence);
    if (p.skip < n) m.append(interleaved.data() + p.skip * kOutputChannels, n - p.skip);
}

void XAudio2Sink::flush() { impl_->submit(); }

}  // namespace p3fes::audio
