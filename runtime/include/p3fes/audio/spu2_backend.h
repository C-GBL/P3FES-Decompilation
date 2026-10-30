// SPU2 replacement: XAudio2 output.
//
// Scope: create the XAudio2 engine and a mastering voice; tear them down. The game's audio is
// produced by the IOP HLE (CRI_ADXI PSM model) into a p3fes::audio::AudioSink; to play it on this
// engine, build an XAudio2Sink (p3fes/audio/xaudio2_sink.h) or HostAudio (host_audio.h) on
// engine(). SPU2 voice playback (SK sound banks) is not modelled yet (runtime/audio/README.md).
#pragma once

#include <xaudio2.h>

namespace p3fes::audio {

class XAudio2Backend {
public:
    XAudio2Backend() = default;
    ~XAudio2Backend();

    XAudio2Backend(const XAudio2Backend&) = delete;
    XAudio2Backend& operator=(const XAudio2Backend&) = delete;

    // Returns false on failure; `last_hresult()` holds the reason.
    bool init();
    void shutdown();

    bool    is_initialised() const noexcept { return engine_ != nullptr; }
    // The engine (nullptr before init); borrowed by XAudio2Sink / HostAudio.
    IXAudio2* engine() const noexcept { return engine_; }
    HRESULT last_hresult() const noexcept { return last_hr_; }

private:
    IXAudio2*               engine_ = nullptr;
    IXAudio2MasteringVoice* mastering_ = nullptr;
    HRESULT                 last_hr_ = S_OK;
    bool                    com_initialised_ = false;
};

} // namespace p3fes::audio
