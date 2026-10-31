// Modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "4. Movies", ADR-0017): the host side of `--native movies`
// (p3fes/native/movies_service.h). Each SFD video work's ring has a read position (the bits its decoder consumed)
// and a queued end (the sectors the PS2's DMA chain would cover); each sceMpeg record has an MpegDecoder
// (mpeg_video.h) that decodes straight from the ring's bytes in guest RAM into the frame buffer.
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "mpeg_video.h"
#include "p3fes/native/movies_service.h"

namespace p3fes {
class StateIo;
}

namespace p3fes::native::movies {

struct NativeMoviesStats {
    u64 ring_resets = 0, creates = 0, resets = 0, deletes = 0;
    u64 calls = 0, shown = 0, ends = 0, errors = 0, short_plans = 0;
    u64 pictures[4] = {};  // decoded by type
    u64 bits = 0;          // stream bits consumed
    double host_seconds = 0;
};

class NativeMovies final : public MoviesService {
public:
    void ring_reset(u64 cycles, u32 vibuf) override;
    void ring_close(u64 cycles, u32 vibuf) override;
    u64 ring_cursor(u32 vibuf) const override;
    u64 ring_queue_end(u32 vibuf) const override;
    void ring_set_queue_end(u32 vibuf, u64 end) override;
    void mpeg_create(u64 cycles, u32 mpeg, u32 vibuf) override;
    void mpeg_reset(u64 cycles, u32 mpeg) override;
    void mpeg_delete(u64 cycles, u32 mpeg) override;
    MoviePlan mpeg_plan(u32 mpeg, const u8* ring, u32 ring_size, u64 avail) override;
    MovieDecode mpeg_decode(u64 cycles, u32 mpeg, const u8* ring, u32 ring_size, u64 avail, bool rgb32, u8* out,
                            u32 out_size) override;

    const NativeMoviesStats& stats() const { return st_; }
    // Layer 6 (b) set (--native-kernel-timing host): the picture call charges the guest 0 cycles instead of the faithful
    // call's modelled cost (an instant decode; the movie timing moves, docs/MODERNIZE_PLAN.md "Layer 6 status").
    void set_instant(bool on) { instant_ = on; }
    // The last picture call's work (the guest-time model's terms): pictures decoded I / P / B, pictures shown,
    // macroblocks intra / forward / backward / bidirectional / no-MC / skipped, coded blocks, stream bits.
    static constexpr unsigned kTerms = 12;
    const u64* last_terms() const { return last_; }
    // The decoder of a record (nullptr when none): the movie log reads its counters.
    const MpegDecoder* decoder(u32 mpeg) const;
    u32 decoder_ring(u32 mpeg) const;
    void state(StateIo& io);

private:
    struct Ring {
        u64 cursor = 0;     // bits
        u64 queue_end = 0;  // bytes
    };
    struct Dec {
        u32 vibuf = 0;
        std::unique_ptr<MpegDecoder> d;
    };
    // `n` bytes of the ring from the read position, linear (the ring wraps at `size`).
    const u8* gather(const Ring& r, const u8* ring, u32 size, u64 n);
    std::map<u32, Ring> rings_;
    std::map<u32, Dec> decs_;
    std::vector<u8> scratch_;
    NativeMoviesStats st_;
    u64 last_[kTerms] = {};
    bool instant_ = false;
};

}  // namespace p3fes::native::movies
