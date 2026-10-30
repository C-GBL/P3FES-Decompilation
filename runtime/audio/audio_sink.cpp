#include "p3fes/audio/audio_sink.h"
#include "p3fes/state_io.h"

#include <algorithm>
#include <cstdlib>

namespace p3fes::audio {

TimelineCursor::Placement TimelineCursor::place(u64 first_frame, u64 frames) {
    Placement p;
    if (!started_) {
        started_ = true;
        origin_ = first_frame;
        next_ = first_frame;
    }
    if (first_frame >= next_) {
        p.silence = first_frame - next_;
    } else {
        p.skip = std::min<u64>(next_ - first_frame, frames);
    }
    next_ = std::max<u64>(next_, first_frame + frames);
    return p;
}

void NullSink::state(StateIo& io) {
    io.section("audio-fingerprint");
    io(frames_, end_, first_, gap_frames_, clipped_, non_silent_, first_non_silent_, hash_, peak_, any_);
}

void NullSink::push(u64 first_frame, std::span<const s16> interleaved) {
    const u64 n = interleaved.size() / kOutputChannels;
    if (!any_) {
        any_ = true;
        first_ = first_frame;
        end_ = first_frame;
    }
    u64 skip = 0;
    if (first_frame < end_) {
        skip = std::min<u64>(end_ - first_frame, n);
        clipped_ += skip;
    } else {
        gap_frames_ += first_frame - end_;
    }
    for (u64 f = skip; f < n; ++f) {
        const u64 pos = first_frame + f;
        bool silent = true;
        for (u32 c = 0; c < kOutputChannels; ++c) {
            const s16 s = interleaved[f * kOutputChannels + c];
            if (s != 0) silent = false;
            peak_ = std::max<s32>(peak_, std::abs(static_cast<s32>(s)));
            hash_ ^= static_cast<u16>(s);
            hash_ *= 0x100000001b3ull;
        }
        hash_ ^= pos;
        hash_ *= 0x100000001b3ull;
        if (!silent) {
            ++non_silent_;
            if (first_non_silent_ == ~0ull) first_non_silent_ = pos;
        }
    }
    frames_ += n - skip;
    end_ = std::max<u64>(end_, first_frame + n);
}

}  // namespace p3fes::audio
