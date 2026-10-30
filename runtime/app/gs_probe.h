// Opt-in GS diagnostics for the D3D11 back-end design (docs/ANALYSIS/25_d3d11_gs_backend.md): a per-draw feature
// census bucketed by vblank segments (`--gs-census FILE [--gs-census-marks V1,V2,...]`) and a one-frame GS
// command-stream recording (`--gs-record FILE --gs-record-at N`). Both observe the GS core through
// gs::IGsDrawObserver / gs::IGsStreamSink and never change guest-visible state; with neither option the host does
// not create a probe and the GS core pays one pointer test per primitive.
#pragma once

#include "p3fes/gs/gs_stream.h"
#include "p3fes/gs/gs_system.h"
#include "p3fes/hle/hw_bus.h"

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace p3fes::app {

struct GsProbeConfig {
    std::filesystem::path census;              // --gs-census FILE (empty = off)
    std::vector<std::uint64_t> marks;          // segment starts in vblanks (0 is implicit)
    std::filesystem::path record;              // --gs-record FILE (empty = off)
    // --gs-record-at N[,N2,...]: the first flip at vblank >= N starts a recording, the next flip ends it; with
    // several points the files are FILE's stem + "_v<N>" + extension.
    std::vector<std::uint64_t> record_at;
    bool enabled() const { return !census.empty() || !record.empty(); }
};

class GsProbe final : public gs::IGsDrawObserver {
public:
    GsProbe(const GsProbeConfig& cfg, gs::GsSystem& gs, const hle::Timebase& time);
    ~GsProbe() override;

    // The host's flip callback forwards every flip event here (drives the recording window).
    void on_flip(const gs::FlipEvent& e);
    // TRXDIR / BITBLTBUF / TRXPOS / TRXREG are seen through on_local_* and on_transfer_span; nothing else needed.
    // Writes the census file (and a pending recording); idempotent.
    void finish();

    // gs::IGsDrawObserver
    void on_draw(const gs::GsRegs& r, const gs::GsVertex* v, u32 count, u64 pixels, u64 ns) override;
    void on_clut_load(u64 tex0, u64 texclut) override;
    void on_transfer_span(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 n) override;
    void on_local_copy(u64 bitbltbuf, u64 trxpos, u64 trxreg) override;
    void on_local_read(u64 bitbltbuf, u64 trxpos, u64 trxreg) override;

    struct Key {
        std::uint64_t k[4] = {};
        bool operator==(const Key& o) const { return k[0] == o.k[0] && k[1] == o.k[1] && k[2] == o.k[2] && k[3] == o.k[3]; }
    };
    struct KeyHash {
        std::size_t operator()(const Key& x) const noexcept {
            std::uint64_t h = 0x9E3779B97F4A7C15ull;
            for (std::uint64_t v : x.k) h = (h ^ v) * 0x100000001B3ull + (h >> 29);
            return static_cast<std::size_t>(h);
        }
    };
    struct Agg {
        std::uint64_t prims = 0, pixels = 0, ns = 0;
    };
    struct Counters {  // GS/GIF/privileged counters, diffed per segment
        gs::GsCoreStats core{};
        gs::GifStats gif{};
        gs::GsPrivStats priv{};
    };
    struct Segment {
        std::uint64_t from_vblank = 0, to_vblank = 0;  // [from, to)
        double wall_s = 0;
        std::uint64_t raster_ns = 0, prims = 0, pixels = 0;
        std::unordered_map<Key, Agg, KeyHash> keys;
        Counters at_open{}, at_close{};
        std::uint64_t upload_pixels_by_psm[64] = {};
        std::uint64_t uploads_over_rendered = 0, upload_pixels_over_rendered = 0;
        std::uint64_t tex_draws_rendered_src = 0, tex_pixels_rendered_src = 0;   // texture footprint holds draw output
        std::uint64_t tex_draws_self_feedback = 0;                              // texture overlaps the draw's own FRAME
        std::uint64_t rendered_src_by_area[4] = {};                             // FB0/FB1/Z/other (draws)
        std::uint64_t clut_loads = 0, clut_loads_rendered = 0;
        std::uint64_t local_copies = 0, local_copies_rendered_src = 0;
        std::uint64_t local_reads = 0, local_reads_rendered = 0, local_read_pixels = 0;
        std::vector<std::string> events;  // first few readbacks / copies, with vblank
        std::uint64_t offscreen_draws = 0, offscreen_pixels = 0;               // FRAME not at FBP 0/140
    };

private:
    void roll_segment();
    std::size_t segment_index(std::uint64_t vblank) const;
    Counters counters() const;
    void mark_pages(std::uint32_t bp_blocks, std::uint32_t bw, std::uint32_t psm, int x0, int y0, int x1, int y1,
                    std::uint64_t serial, bool upload);
    bool any_rendered(std::uint32_t bp_blocks, std::uint32_t bw, std::uint32_t psm, int x0, int y0, int x1, int y1,
                      int* area = nullptr) const;
    void write_census() const;

    GsProbeConfig cfg_;
    gs::GsSystem& gs_;
    const hle::Timebase& time_;
    std::vector<Segment> segs_;
    std::size_t cur_ = SIZE_MAX;
    std::chrono::steady_clock::time_point seg_t0_{};
    std::uint64_t serial_ = 0;
    std::array<std::uint64_t, 512> page_draw_{};    // serial of the last draw that wrote the page (FRAME or ZBUF)
    std::array<std::uint64_t, 512> page_upload_{};  // serial of the last host->local transfer into the page
    std::uint64_t xfer_serial_ = 0;                 // serial of the current transfer (for per-transfer counting)
    bool xfer_over_rendered_counted_ = false;
    gs::GsStreamRecorder rec_;
    std::size_t rec_next_ = 0;
    std::filesystem::path record_path(std::size_t i) const;
    bool finished_ = false;
};

} // namespace p3fes::app
