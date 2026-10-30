// GS drawing core: the general-purpose register file, the vertex queue and kick rules, image transfers
// (BITBLTBUF/TRXPOS/TRXREG/TRXDIR + HWREG) and the software rasteriser into GsMemory (contract H-31..H-34).
//
// Inputs arrive from the GIF (runtime/include/p3fes/gs/gif.h) as A+D / REGLIST writes (`write_reg`), PACKED writes
// (`write_packed`) and IMAGE data (`write_image`). Everything is synchronous: a vertex kick rasterises the primitive
// before `write_reg` returns. SIGNAL/FINISH/LABEL are reported to an IGsEvents receiver (the privileged-register
// device owns CSR and SIGLBLID).
#pragma once

#include "p3fes/gs/gs_mem.h"

#include <array>
#include <cstddef>
#include <functional>
#include <span>

namespace p3fes {
class StateIo;  // p3fes/state_io.h (machine states)
}

namespace p3fes::gs {

class IGsEvents {
public:
    virtual ~IGsEvents() = default;
    virtual void on_signal(u32 id, u32 mask) = 0;
    virtual void on_finish() = 0;
    virtual void on_label(u32 id, u32 mask) = 0;
};

// Per-context registers (suffix _1 / _2).
struct GsContextRegs {
    u64 tex0 = 0, clamp = 0, tex1 = 0, xyoffset = 0, miptbp1 = 0, miptbp2 = 0, scissor = 0, alpha = 0, test = 0,
        fba = 0, frame = 0, zbuf = 0;
};

struct GsRegs {
    u64 prim = 0, rgbaq = 0, st = 0, uv = 0, fog = 0, prmodecont = 1, prmode = 0, texclut = 0, scanmsk = 0, texa = 0,
        fogcol = 0, dimx = 0, dthe = 0, colclamp = 0, pabe = 0, bitbltbuf = 0, trxpos = 0, trxreg = 0, trxdir = 0;
    std::array<GsContextRegs, 2> ctx{};
    u32 q_internal = 0x3F800000u; // PACKED ST writes Q here; PACKED RGBAQ takes it; each GIF tag resets it to 1.0
};

// One queued vertex as the GS latched it at the XYZ write.
struct GsVertex {
    u32 x = 0, y = 0; // 12.4 fixed-point primitive coordinates (before XYOFFSET)
    u32 z = 0;
    u8 r = 0, g = 0, b = 0, a = 0;
    u32 q = 0x3F800000u, s = 0, t = 0; // float bit patterns
    u32 u = 0, v = 0;                  // 10.4 fixed point (UV register)
    u8 f = 0;                          // fog coefficient
};

struct GsCoreStats {
    u64 reg_writes = 0;
    u64 unknown_reg_writes = 0;   // addresses with no register (0x0B, 0x0E..0x13 in A+D, 0x1D.., > 0x62 except 0x7F)
    u64 primitives = 0;           // primitives rasterised (after kick)
    u64 prohibited_prims = 0;     // PRIM type 7
    u64 pixels_written = 0;       // pixels that reached the frame/Z write stage
    u64 image_qwords_in = 0;      // host -> local data accepted
    u64 image_qwords_ignored = 0; // IMAGE data with no active host -> local transfer
    u64 image_qwords_out = 0;     // local -> host data produced
    u64 local_copies = 0;
    u64 clut_loads = 0;
    u64 invalid_psm = 0;          // an undefined PSM value reached the rasteriser / a transfer
};

// Draw-level observer (diagnostics and alternative back ends; docs/ANALYSIS/25_d3d11_gs_backend.md §5). Every
// callback runs synchronously inside the GsCore call that caused it and must not touch the guest. Unset (default):
// one pointer test per primitive / CLUT load / transfer pixel.
class IGsDrawObserver {
public:
    virtual ~IGsDrawObserver() = default;
    // A primitive was kicked (not PRIM type 7): the register file and the `count` queued vertices as the kick rule
    // delivered them (last = kicking vertex). `pixels` = pixels that reached the frame/Z write stage and `ns` =
    // host nanoseconds spent rasterising it (both 0 when software rasterisation is off).
    virtual void on_draw(const GsRegs& regs, const GsVertex* v, u32 count, u64 pixels, u64 ns) = 0;
    // The CLUT buffer was (re)loaded from local memory for this TEX0 (after a TEX2 merge) and TEXCLUT.
    virtual void on_clut_load(u64 /*tex0*/, u64 /*texclut*/) {}
    // Host -> local transfer pixels (x .. x+n-1, y) of the buffer {psm, bp, bw} were stored into local memory (one
    // call per contiguous run of a row inside one write_image / HWREG call; the values are in GsCore::mem()).
    virtual void on_transfer_span(u32 /*psm*/, u32 /*bp*/, u32 /*bw*/, u32 /*x*/, u32 /*y*/, u32 /*n*/) {}
    // A local -> local copy (TRXDIR 2) is about to run with these BITBLTBUF/TRXPOS/TRXREG values.
    virtual void on_local_copy(u64 /*bitbltbuf*/, u64 /*trxpos*/, u64 /*trxreg*/) {}
    // A local -> host transfer (TRXDIR 1) was started (the EE will read GS memory back).
    virtual void on_local_read(u64 /*bitbltbuf*/, u64 /*trxpos*/, u64 /*trxreg*/) {}
};

// The GsCore API calls in the order they happened (runtime/gs/gs_stream.h records them into a replayable file).
// Calls GsCore makes to itself (PACKED -> register, HWREG register -> write_hwreg) are not reported again.
class IGsStreamSink {
public:
    virtual ~IGsStreamSink() = default;
    virtual void on_reg(u32 reg, u64 value) = 0;
    virtual void on_packed(u32 desc, const u128& q) = 0;
    virtual void on_gif_tag() = 0;
    virtual void on_image(std::span<const u128> qwords) = 0;
    virtual void on_hwreg(u64 value) = 0;
    virtual void on_read_image(std::size_t qwords) = 0;
    virtual void on_reset() = 0;
};

// Everything GsCore holds besides local memory, by value (a stream recording starts from one).
struct GsCoreState {
    GsRegs regs{};
    std::array<GsVertex, 3> queue{};
    u32 queued = 0;
    std::array<u16, 512> clut{};
    u32 cbp0 = 0xFFFFFFFFu, cbp1 = 0xFFFFFFFFu;
    u32 xfer_active = 0, xfer_dir = 3, xfer_x = 0, xfer_y = 0;
    u64 xfer_bitbuf = 0;
    u32 xfer_bitcount = 0;
};

class GsCore {
public:
    GsCore();
    ~GsCore();
    GsCore(const GsCore&) = delete;
    GsCore& operator=(const GsCore&) = delete;

    GsMemory& mem() noexcept { return mem_; }
    const GsMemory& mem() const noexcept { return mem_; }
    const GsRegs& regs() const noexcept { return r_; }
    const GsCoreStats& stats() const noexcept { return stats_; }
    void set_events(IGsEvents* ev) noexcept { events_ = ev; }
    // Diagnostics: called for every write to a *state* register (PRIM and everything from TEX0_1 up, except the
    // per-vertex FOG/XYZF3/XYZ3), A+D/REGLIST or PACKED, before it takes effect. Not called for RGBAQ/ST/UV/XYZ*.
    // Empty (default): no cost beyond one test per state write.
    void set_reg_observer(std::function<void(u32 reg, u64 value)> f) { reg_observer_ = std::move(f); }
    // Draw-level observer (above); nullptr = off. Never changes what the core computes.
    void set_draw_observer(IGsDrawObserver* o) noexcept { draw_observer_ = o; }
    // API-call recorder; nullptr = off.
    void set_stream_sink(IGsStreamSink* s) noexcept { sink_ = s; }
    // false: primitives are reported to the draw observer only and local memory receives no pixels (a GPU back
    // end draws them). Transfers, CLUT loads and every register keep their software semantics. Default true; the
    // game's host clears it only for the D3D11 back end (windowed play, or headless --gs-backend d3d11 --gs-exact).
    // An observer may set it back to true from inside on_draw: the core then rasterises that primitive itself
    // (a GPU back end that cannot draw it, after syncing local memory and the CLUT buffer back into the core).
    void set_software_raster(bool on) noexcept { software_raster_ = on; }
    bool software_raster() const noexcept { return software_raster_; }
    // Changes whenever a register that the draw state is decoded from may have changed (every register write except
    // RGBAQ / ST / UV / FOG / XYZ*, and reset / load_state / a machine-state load): a draw observer may keep its
    // decoded state while the value is unchanged (docs/ANALYSIS/25 "Fast front end"). Never 0.
    u64 state_generation() const noexcept { return state_gen_; }

    GsCoreState save_state() const;
    void load_state(const GsCoreState& s);
    // Machine state (p3fes/state_io.h, gs_state.cpp): local memory, registers, queue, CLUT, transfer, stats --
    // not the host's choices (observers, sinks, software_raster).
    void state(StateIo& io);

    // CSR.RESET: registers, vertex queue, transfer and CLUT state to power-on values; local memory is kept.
    void reset();

    // A+D / REGLIST semantics: the 64-bit register value.
    void write_reg(u32 reg, u64 value) {
        if (sink_) sink_->on_reg(reg, value);
        write_reg_impl(reg, value);
    }
    // PACKED semantics for register descriptor `desc` (0x0..0xF): the 128-bit qword.
    void write_packed(u32 desc, const u128& q);
    // A GIF tag was read (any path): resets the internal Q to 1.0 (GS User's Manual, PACKED RGBAQ/ST).
    void on_gif_tag() {
        if (sink_) sink_->on_gif_tag();
        r_.q_internal = 0x3F800000u;
    }

    // IMAGE / HWREG data for a host -> local transfer (TRXDIR 0). Data beyond RRW*RRH pixels is dropped and counted.
    void write_image(std::span<const u128> qwords);
    void write_hwreg(u64 value) {
        if (sink_) sink_->on_hwreg(value);
        write_hwreg_impl(value);
    }
    // Local -> host (TRXDIR 1): fill `out` with the next qwords of the transfer (zeros once it is complete).
    void read_image(std::span<u128> out);
    bool host_to_local_active() const noexcept { return xfer_.active && xfer_.dir == 0; }
    bool local_to_host_active() const noexcept { return xfer_.active && xfer_.dir == 1; }

    // CLUT buffer (GS internal, 512 halfwords: 16-bit entries, or the low/high halves of 32-bit entries at +0/+256).
    const std::array<u16, 512>& clut() const noexcept { return clut_; }
    // A GPU back end hands its CLUT buffer back (loaded on the GPU from GPU memory) before software takes over.
    void set_clut(const std::array<u16, 512>& c) noexcept { clut_ = c; }

private:
    void write_reg_impl(u32 reg, u64 value);
    void write_hwreg_impl(u64 value);
    struct Transfer {
        bool active = false;
        u32 dir = 3;
        u32 x = 0, y = 0;          // next pixel inside the RRW x RRH rectangle
        u64 bitbuf = 0;            // pending bits of a partially consumed byte stream (24/4-bit packing)
        u32 bitcount = 0;
    };

    void vertex(u32 xy, u32 z, u8 f, bool kick);
    void draw_queue();
    void load_clut(u64 tex0);
    void start_transfer(u64 trxdir);
    void local_copy();
    void transfer_pixel_in(u32 value);
    void flush_span();
    void image32(std::span<const u128> qwords);
    void image16(std::span<const u128> qwords);
    bool transfer_pixel_out(u32& value);

    GsMemory mem_;
    GsRegs r_{};
    std::array<GsVertex, 3> queue_{};
    u32 queued_ = 0;
    std::array<u16, 512> clut_{};
    u32 cbp0_ = 0xFFFFFFFFu, cbp1_ = 0xFFFFFFFFu;
    Transfer xfer_{};
    IGsEvents* events_ = nullptr;
    std::function<void(u32, u64)> reg_observer_;
    IGsDrawObserver* draw_observer_ = nullptr;
    u32 span_x_ = 0, span_y_ = 0, span_n_ = 0;  // pending on_transfer_span run
    IGsStreamSink* sink_ = nullptr;
    bool software_raster_ = true;
    u64 state_gen_ = 1;
    GsCoreStats stats_{};
};

} // namespace p3fes::gs
