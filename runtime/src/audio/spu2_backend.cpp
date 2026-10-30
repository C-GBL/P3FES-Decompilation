#include "p3fes/audio/spu2_backend.h"

#include <objbase.h>

namespace p3fes::audio {

XAudio2Backend::~XAudio2Backend() {
    shutdown();
}

bool XAudio2Backend::init() {
    shutdown();

    // XAudio2 2.9 (Windows 10+) does not strictly need COM initialised, but
    // some device enumeration paths do. Initialise if nobody else has.
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        com_initialised_ = true;
    } else if (hr != RPC_E_CHANGED_MODE) {
        last_hr_ = hr;
        return false;
    }

    hr = XAudio2Create(&engine_, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr)) {
        last_hr_ = hr;
        shutdown();
        return false;
    }

    // SPU2 output format: 48 kHz stereo. Let XAudio2 pick the device.
    hr = engine_->CreateMasteringVoice(&mastering_, 2, 48000);
    if (FAILED(hr)) {
        last_hr_ = hr;
        shutdown();
        return false;
    }

    last_hr_ = S_OK;
    return true;
}

void XAudio2Backend::shutdown() {
    if (mastering_) {
        mastering_->DestroyVoice();
        mastering_ = nullptr;
    }
    if (engine_) {
        engine_->Release();
        engine_ = nullptr;
    }
    if (com_initialised_) {
        CoUninitialize();
        com_initialised_ = false;
    }
}

} // namespace p3fes::audio
