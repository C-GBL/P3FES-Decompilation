// GIF: GIF-tag decoding and the three paths into the GS (contract H-20..H-22; docs/ANALYSIS/10 §5.7, 14 §3).
//
//   PATH1  VU1 XGKICK (IGifSink, synchronous inside MSCAL/MSCNT)            highest priority
//   PATH2  VIF1 DIRECT/DIRECTHL                                             middle
//   PATH3  DMAC channel 2 (and the GIF FIFO 0x10006000)                     lowest
//
// Arbitration model (synchronous): a path owns the GIF from the first tag of a packet until the data of the tag
// with EOP=1 is consumed, and is never interrupted inside a packet. While a path owns the GIF, other paths stall:
// PATH2/PATH3 calls return fewer quadwords than offered (the VIF / DMAC owner re-offers the rest later), PATH1
// packets are copied into a queue and run as soon as the GIF is idle. At every packet boundary queued PATH1
// packets run first; PATH3 then yields to a stalled PATH2 and stops while masked (VIF1 MSKPATH3 = GIF_STAT.M3P,
// or GIF_MODE.M3R). Intermittent mode (IMT) is stored and reported but not modelled.
#pragma once

#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_pipe.h"
#include "p3fes/hle/hw_bus.h"

#include <deque>
#include <functional>
#include <span>
#include <vector>

namespace p3fes::gs {

struct GifTag {
    u32 nloop = 0;
    bool eop = false;
    bool pre = false;
    u32 prim = 0;
    u32 flg = 0;  // 0 PACKED, 1 REGLIST, 2 IMAGE, 3 disabled (= IMAGE)
    u32 nreg = 0; // 1..16
    u64 regs = 0;

    static GifTag decode(const u128& q) noexcept;
    // Quadwords of data that follow the tag.
    u32 data_qwords() const noexcept { return flg == 0 ? nloop * nreg : (flg == 1 ? (nloop * nreg + 1u) / 2u : nloop); }
    u32 reg(u32 i) const noexcept { return static_cast<u32>(regs >> (4u * i)) & 0xFu; }
};

struct GifStats {
    u64 tags[4][4] = {};        // [path][flg]
    u64 qwords[4] = {};         // per path
    u64 path1_queued = 0;       // XGKICK packets deferred behind PATH2/PATH3
    u64 path1_truncated = 0;    // XGKICK packets without EOP (closed by force)
    u64 path2_stalls = 0;
    u64 path3_mask_stalls = 0;
    u64 path3_yields = 0;
    u64 path3_window_stops = 0;  // PATH3 stopped after one EOP packet of an unmask window
    u64 resets = 0;
    u64 unhandled_reg_writes = 0;
};

class Gif {
public:
    explicit Gif(GsCore& core) : core_(core) {}

    // PATH entry points. Return the number of quadwords consumed (fewer than offered = stalled).
    std::size_t path2(std::span<const u128> q);
    std::size_t path3(std::span<const u128> q);
    void path1(std::span<const u128> q);

    // VIF1 MSKPATH3 (GIF_STAT.M3P). Unmasking with a stalled PATH3 calls the path3-ready callback.
    void set_m3p(bool masked);
    bool path3_masked() const noexcept { return m3p_ || m3r_; }
    // Set by the VIF while it waits for PATH2 (VIF1_STAT.VGW / GIF_STAT.P2Q).
    void set_path2_waiting(bool w) noexcept { p2_waiting_ = w; }
    bool path2_waiting() const noexcept { return p2_waiting_; }
    u32 active_path() const noexcept { return owner_; }
    bool idle() const noexcept { return owner_ == 0 && p1_queue_.empty(); }
    // What VIF1's FLUSHA waits for: "the end of the PATH3 transfer" (EE User's Manual, VIFcode FLUSHA) -- PATH3
    // owning the GIF mid-packet, PATH3 data stalled in the GIF (mask / yield), or DMAC channel 2 still running
    // (CHCR.STR, read through `set_path3_dma_busy`; the DMA's data phase and its completion delay both count).
    // Without this, PATH2 draw packets overtook the PATH3 texture uploads they depend on (the title screen bug).
    // While PATH3 is masked (MSKPATH3 / GIF_MODE.M3R) only the packet in flight counts: a masked PATH3 cannot
    // finish, and a VIF that waited for its own mask would never continue (PCSX2's FLUSHA has the same guard).
    bool path3_pending() const {
        if (owner_ == 3) return true;
        if (path3_masked()) return false;
        return p3_stalled_ || (path3_dma_busy_ && path3_dma_busy_());
    }

    void set_busdir_source(const u64* busdir) noexcept { busdir_ = busdir; }
    void set_path2_resume(std::function<void()> f) { path2_resume_ = std::move(f); }
    void set_path3_ready(std::function<void()> f) { path3_ready_ = std::move(f); }
    void set_path3_dma_busy(std::function<bool()> f) { path3_dma_busy_ = std::move(f); }

    // An unmask window (VIF1 `MSKPATH3 off`): while it is open, PATH3 transfers one GS packet (through its EOP)
    // and then stalls at the next packet boundary (GIF_STAT.P3Q) until the DMAC retries it. RenderWare's
    // texture sync packet -- `MSKPATH3 off`, ~96 NOPs, `MSKPATH3 on`, `FLUSHA`, TEX0 + draw -- is a timing window
    // in which the hardware lets exactly the next texture pair (texture, CLUT, EOP) through before the mask,
    // effective at the EOP boundary, stops PATH3 again; the following upload of the same chain may legally
    // overwrite VRAM that the draw just issued still reads, so letting the whole chain through here renders the
    // wrong textures (the title screen, docs/INTEGRATION_LOG.md "Title fix"). GsSystem opens the window around
    // its path3-ready callback.
    void begin_path3_window() noexcept { p3_window_ = true; p3_window_done_ = false; }
    void end_path3_window() noexcept { p3_window_ = p3_window_done_ = false; }

    void reset();

    // Threaded pipeline (gs_pipeline.h). With a pipe, PATH2/PATH3 GsCore calls become commands and PATH1 never reaches
    // this object: VU1 runs on a worker, whose kicks go straight to the GsCore when the GIF is idle at the run
    // (`active_path() == 0`) or into the worker's PATH1 queue otherwise (`note_p1_queued`); the queue is flushed by
    // a command at the point run_path1_queue would run it. nullptr = synchronous (default).
    void set_pipe(GsPipe* p) noexcept { fwd_ = p; }
    void note_p1_queued() noexcept { p1_pending_ = true; }
    bool p1_pending() const noexcept { return p1_pending_; }
    // Machine states with the pipeline on: the PATH1 queue and the last-tag registers as the synchronous GIF holds
    // them (GsPipeline exports its worker's queue / PATH1 tag into these before a save and takes them after a load).
    std::deque<std::vector<u128>>& p1_queue() noexcept { return p1_queue_; }
    void set_last_tag(const u32 tag[4], u32 path) noexcept {
        for (u32 w = 0; w < 4; ++w) last_tag_[w] = tag[w];
        last_tag_path_ = path;
    }
    void clear_p1_pending() noexcept { p1_pending_ = false; }
    u64 last_tag_seq() const noexcept { return last_tag_seq_; }
    GifStats& mutable_stats() noexcept { return stats_; }

    // GIF registers at 0x10003000 (offsets 0x00 CTRL .. 0xA0 P3TAG), 32-bit.
    u32 read_reg(u32 off) const;
    void write_reg(u32 off, u32 v);
    u32 stat() const;

    const GifStats& stats() const noexcept { return stats_; }

    void state(StateIo& io);  // machine state (gs_state.cpp)

private:
    struct Path {
        bool in_tag = false;  // tag read, data pending
        bool open = false;    // packet started, EOP tag not finished
        GifTag tag{};
        u32 loop = 0;
        u32 reg = 0;
    };

    std::size_t feed(u32 p, std::span<const u128> q);
    void run_path1_queue();
    void close_path1();

    GsCore& core_;
    GsPipe* fwd_ = nullptr;     // set_pipe
    bool p1_pending_ = false;   // pipeline: a VU1 run kicked (or may have kicked) into the worker's PATH1 queue
    u64 last_tag_seq_ = 0;      // pipeline: GsPipe::seq() at the last tag read here
    Path path_[4]{};
    u32 owner_ = 0;
    bool m3p_ = false, m3r_ = false, imt_ = false, pse_ = false;
    bool p2_waiting_ = false;
    bool p3_stalled_ = false;
    bool p3_window_ = false, p3_window_done_ = false;  // begin/end_path3_window
    std::size_t p3_stall_qwc_ = 0;
    std::deque<std::vector<u128>> p1_queue_;
    bool running_p1_queue_ = false;
    u32 last_tag_[4] = {};
    u32 last_tag_path_ = 0;
    u32 p3_last_tag_ = 0;
    const u64* busdir_ = nullptr;
    std::function<void()> path2_resume_;
    std::function<void()> path3_ready_;
    std::function<bool()> path3_dma_busy_;  // DMAC channel 2 CHCR.STR (GsSystem::attach)
    GifStats stats_{};
};

// GIF registers device (physical 0x10003000-0x100030B0).
class GifRegsDevice final : public hle::HwDevice {
public:
    static constexpr u32 kBase = 0x10003000u;
    static constexpr u32 kEnd = 0x100030B0u;
    explicit GifRegsDevice(Gif& gif) : gif_(gif) {}
    u32 read32(u32 pa) override { return gif_.read_reg(pa - kBase); }
    void write32(u32 pa, u32 v) override { gif_.write_reg(pa - kBase, v); }
    u64 read64(u32 pa) override { return read32(pa); }
    void write64(u32 pa, u64 v) override { write32(pa, static_cast<u32>(v)); }

private:
    Gif& gif_;
};

// GIF FIFO (physical 0x10006000-0x10006010): 128-bit stores feed PATH3 (0 sites in the game, accepted anyway).
class GifFifoDevice final : public hle::HwDevice {
public:
    static constexpr u32 kBase = 0x10006000u;
    static constexpr u32 kEnd = 0x10006010u;
    explicit GifFifoDevice(Gif& gif) : gif_(gif) {}
    void write128(u32 pa, const u128& v) override;
    u128 read128(u32) override { return u128{}; }
    // Retry buffered qwords (called when PATH3 is unmasked).
    void drain();
    std::size_t pending() const noexcept { return pending_.size(); }
    void state(StateIo& io);  // machine state (gs_state.cpp)

private:
    Gif& gif_;
    std::vector<u128> pending_;
};

// DMAC channel 2 data path (PATH3).
class GifDmaHandler final : public hle::DmaChannelHandler {
public:
    explicit GifDmaHandler(Gif& gif) : gif_(gif) {}
    std::size_t transfer(u128* data, std::size_t qwc, u64 tag) override {
        (void)tag;
        return gif_.path3(std::span<const u128>(data, qwc));
    }

private:
    Gif& gif_;
};

} // namespace p3fes::gs
