#include "p3fes/audio/host_audio.h"

#include <cstdio>

#include "p3fes/audio/wav.h"
#include "p3fes/audio/xaudio2_sink.h"

namespace p3fes::audio {

std::filesystem::path default_dump_dir(const std::filesystem::path& repo_root) {
    return repo_root / "extracted" / "_ours" / "wav";
}

HostAudio::HostAudio(HostAudioOptions opt) : opt_(std::move(opt)) {
    tee_.add(&null_);
    if (opt_.xaudio2) {
        xa_ = std::make_unique<XAudio2Sink>();
        XAudio2Sink::Options o;
        o.pace = opt_.pace;
        o.rate_control = opt_.rate_control;
        o.target_queued_ms = opt_.target_queued_ms;
        if (xa_->init(o, opt_.engine)) {
            tee_.add(xa_.get());
        } else {
            std::fprintf(stderr, "[audio] XAudio2 sink unavailable (hr=0x%08lX); continuing silent\n",
                         static_cast<unsigned long>(xa_->last_hresult()));
            xa_.reset();
        }
    }
    if (!opt_.dump_wav_dir.empty()) {
        wav_ = std::make_unique<WavSink>(opt_.dump_wav_dir / "mix_48k.wav");
        dumper_ = std::make_unique<WavStreamDumper>(opt_.dump_wav_dir);
        tee_.add(wav_.get());
        tap_.add(dumper_.get());
    }
}

HostAudio::~HostAudio() { flush(); }

void HostAudio::flush() {
    tee_.flush();
    if (dumper_) dumper_->close_all();
}

bool HostAudio::xaudio2_active() const { return xa_ && xa_->ready(); }

std::string HostAudio::describe() const {
    char b[256];
    std::snprintf(b, sizeof b, "audio: %s%s%s; mixed %llu frames (%llu audible), hash %016llx",
                  xaudio2_active() ? "XAudio2" : "no device", opt_.pace && xaudio2_active() ? " (paced)" : "",
                  opt_.dump_wav_dir.empty() ? "" : (", WAV dumps in " + opt_.dump_wav_dir.string()).c_str(),
                  static_cast<unsigned long long>(null_.frames()), static_cast<unsigned long long>(null_.non_silent_frames()),
                  static_cast<unsigned long long>(null_.hash()));
    return b;
}

}  // namespace p3fes::audio
