// Modernize layer 4: the native movie service (native_movies.h).
#include "native_movies.h"

#include <algorithm>
#include <chrono>
#include <cstring>

#include "p3fes/state_io.h"

namespace p3fes::native::movies {

void NativeMovies::ring_reset(u64, u32 vibuf) {
    rings_[vibuf] = Ring{};
    ++st_.ring_resets;
}

void NativeMovies::ring_close(u64, u32 vibuf) { rings_.erase(vibuf); }

u64 NativeMovies::ring_cursor(u32 vibuf) const {
    const auto it = rings_.find(vibuf);
    return it == rings_.end() ? 0 : it->second.cursor;
}

u64 NativeMovies::ring_queue_end(u32 vibuf) const {
    const auto it = rings_.find(vibuf);
    return it == rings_.end() ? 0 : it->second.queue_end;
}

void NativeMovies::ring_set_queue_end(u32 vibuf, u64 end) { rings_[vibuf].queue_end = end; }

void NativeMovies::mpeg_create(u64, u32 mpeg, u32 vibuf) {
    Dec& d = decs_[mpeg];
    d.vibuf = vibuf;
    d.d = std::make_unique<MpegDecoder>();
    ++st_.creates;
}

void NativeMovies::mpeg_reset(u64, u32 mpeg) {
    const auto it = decs_.find(mpeg);
    if (it != decs_.end()) it->second.d->reset();
    ++st_.resets;
}

void NativeMovies::mpeg_delete(u64, u32 mpeg) {
    decs_.erase(mpeg);
    ++st_.deletes;
}

const MpegDecoder* NativeMovies::decoder(u32 mpeg) const {
    const auto it = decs_.find(mpeg);
    return it == decs_.end() ? nullptr : it->second.d.get();
}

u32 NativeMovies::decoder_ring(u32 mpeg) const {
    const auto it = decs_.find(mpeg);
    return it == decs_.end() ? 0u : it->second.vibuf;
}

const u8* NativeMovies::gather(const Ring& r, const u8* ring, u32 size, u64 n) {
    n = std::min<u64>(n, size);
    scratch_.resize(static_cast<std::size_t>(n) + 16u);
    const u64 at = (r.cursor / 8u) % size;
    const u64 first = std::min<u64>(n, size - at);
    std::memcpy(scratch_.data(), ring + at, static_cast<std::size_t>(first));
    if (n > first) std::memcpy(scratch_.data() + first, ring, static_cast<std::size_t>(n - first));
    std::memset(scratch_.data() + n, 0, 16);
    return scratch_.data();
}

MoviePlan NativeMovies::mpeg_plan(u32 mpeg, const u8* ring, u32 size, u64 avail) {
    MoviePlan p;
    const auto it = decs_.find(mpeg);
    if (it == decs_.end() || size == 0) return p;
    const Ring& r = rings_[it->second.vibuf];
    const u64 n = std::min<u64>(avail, size);
    const u8* b = gather(r, ring, size, n);
    const Plan q = it->second.d->plan(b, static_cast<std::size_t>(n), static_cast<unsigned>(r.cursor & 7u));
    p.kind = q.status == Status::Shown ? MoviePlan::Shown : q.status == Status::End ? MoviePlan::End : MoviePlan::NeedData;
    p.needed = q.needed;
    if (p.kind == MoviePlan::NeedData) ++st_.short_plans;
    return p;
}

MovieDecode NativeMovies::mpeg_decode(u64, u32 mpeg, const u8* ring, u32 size, u64 avail, bool rgb32, u8* out,
                                      u32 out_size) {
    MovieDecode r;
    ++st_.calls;
    const auto it = decs_.find(mpeg);
    if (it == decs_.end() || size == 0) {
        r.kind = MovieDecode::Error;
        ++st_.errors;
        return r;
    }
    const auto t0 = std::chrono::steady_clock::now();
    Ring& ring_state = rings_[it->second.vibuf];
    MpegDecoder& d = *it->second.d;
    const u64 n = std::min<u64>(avail, size);
    const u8* b = gather(ring_state, ring, size, n);
    const unsigned bit0 = static_cast<unsigned>(ring_state.cursor & 7u);
    DirectEngine e(b, static_cast<std::size_t>(n), bit0);
    const DecoderStats before = d.stats();
    const Status s = d.decode(e, rgb32, out, out_size);
    const DecoderStats& after = d.stats();
    const u64 terms[kTerms] = {after.pictures[1] - before.pictures[1], after.pictures[2] - before.pictures[2],
                               after.pictures[3] - before.pictures[3], after.shown - before.shown,
                               after.mb_intra - before.mb_intra, after.mb_fwd - before.mb_fwd,
                               after.mb_bwd - before.mb_bwd, after.mb_bi - before.mb_bi,
                               after.mb_nomc - before.mb_nomc, after.skipped_mbs - before.skipped_mbs,
                               after.blocks - before.blocks, e.bitpos() - bit0};
    std::memcpy(last_, terms, sizeof last_);
    // The faithful call's guest time for this work: per call plus per macroblock by kind (least squares over the 90
    // picture calls of the dorm / battle / fusion / shop routes, faithful cycles against these terms: mean error
    // 3.4 %, at most 17.5 %; docs/MODERNIZE_PLAN.md "Layer 4 status"). Bidirectional macroblocks cost most (two
    // fetches and the average on the EE), intra least (no motion compensation).
    // A call that only shows (the sequence end's held reference: no macroblock decoded) still converts the picture
    // (libmpeg's CSC of every macroblock, which the per-macroblock terms carry otherwise): kCostFlush, the opening
    // movie's last call (188,023 cycles faithful).
    constexpr u64 kCostCall = 21387, kCostIntra = 1323, kCostFwd = 2909, kCostBwd = 2833, kCostBi = 4160,
                  kCostNoMc = 2306, kCostSkip = 1499, kCostFlush = 166636;
    const bool show_only = terms[3] != 0 && terms[0] + terms[1] + terms[2] == 0;
    // The fit is of the faithful call's span, which includes what other threads ran meanwhile; charged with check
    // points that time comes on top again, so the charge is the span x 0.91 (unscaled, the native calls measured
    // 1.10 x the faithful span on the four routes).
    r.cycles = (kCostCall + (show_only ? kCostFlush : 0) + kCostIntra * terms[4] + kCostFwd * terms[5] +
                kCostBwd * terms[6] + kCostBi * terms[7] + kCostNoMc * terms[8] + kCostSkip * terms[9]) *
               91u / 100u;
    if (instant_) r.cycles = 0;  // layer 6 (b), --native-kernel-timing host: the decode costs the guest no time
    r.bits = e.bitpos() - bit0;
    ring_state.cursor += r.bits;
    st_.bits += r.bits;
    r.kind = s == Status::Shown ? MovieDecode::Shown : s == Status::End ? MovieDecode::End : MovieDecode::Error;
    if (s == Status::Shown) ++st_.shown;
    else if (s == Status::End) ++st_.ends;
    else ++st_.errors;
    r.width = d.width();
    r.height = d.height();
    r.decoded = d.frames_decoded();
    r.shown = d.frames_shown();
    r.type = d.last_shown_type();
    r.tref = d.last_shown_tref();
    for (unsigned k = 1; k < 4; ++k) st_.pictures[k] += terms[k - 1];
    st_.host_seconds += std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    return r;
}

void NativeMovies::state(StateIo& io) {
    io(rings_);
    u32 n = static_cast<u32>(decs_.size());
    io(n);
    if (io.loading()) {
        decs_.clear();
        for (u32 i = 0; i < n; ++i) {
            u32 key = 0, vibuf = 0;
            io(key, vibuf);
            Dec& d = decs_[key];
            d.vibuf = vibuf;
            d.d = std::make_unique<MpegDecoder>();
            d.d->state(io);
        }
    } else {
        for (auto& [key, d] : decs_) {
            u32 k = key, v = d.vibuf;
            io(k, v);
            d.d->state(io);
        }
    }
    io(st_.ring_resets, st_.creates, st_.resets, st_.deletes, st_.calls, st_.shown, st_.ends, st_.errors,
       st_.short_plans, st_.pictures, st_.bits);
}

}  // namespace p3fes::native::movies
