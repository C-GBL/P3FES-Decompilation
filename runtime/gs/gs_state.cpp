// Machine state of the GS side (runtime/STATE.md): GS core + local memory, privileged registers, GIF and its
// FIFO, VIF1, the VIF0 stub and VU1. Wiring (bus, callbacks, observers, sinks) and the host's choices
// (software rasterisation on/off, the VU1 engine) are not part of it.
#include "p3fes/gs/gs_system.h"
#include "p3fes/state_io.h"

namespace p3fes::gs {

void GsCore::state(StateIo& io) {
    io.section("gs-core");
    ++state_gen_;  // a load replaces the registers (not part of the state: a host-side cache key)
    io.raw(mem_.data(), kVramBytes);
    io(r_, queue_, queued_, clut_, cbp0_, cbp1_);
    io(xfer_.active, xfer_.dir, xfer_.x, xfer_.y, xfer_.bitbuf, xfer_.bitcount);
    io(span_x_, span_y_, span_n_, stats_);
}

void GsPrivRegs::state(StateIo& io) {
    io.section("gs-priv");
    io(disp_, srfsh_, synch1_, synch2_, syncv_, extbuf_, extdata_, extwrite_);
    io(csr_flags_, imr_, busdir_, siglblid_, vsint_ack_, hsint_ack_, smode2_armed_);
    io(flips_, last_flip_vblank_, last_flip_, stats_);
}

void Gif::state(StateIo& io) {
    io.section("gif");
    for (Path& p : path_) io(p.in_tag, p.open, p.tag, p.loop, p.reg);
    io(owner_, m3p_, m3r_, imt_, pse_, p2_waiting_, p3_stalled_, p3_window_, p3_window_done_);
    std::uint64_t qwc = p3_stall_qwc_;
    io(qwc);
    p3_stall_qwc_ = static_cast<std::size_t>(qwc);
    io(p1_queue_, running_p1_queue_, last_tag_, last_tag_path_, p3_last_tag_, stats_);
}

void GifFifoDevice::state(StateIo& io) {
    io.section("gif-fifo");
    io(pending_);
}

void Vif1::state(StateIo& io) {
    io.section("vif1");
    io(err_, mark_, cycle_, mode_, num_, mask_, code_, itops_, base_, ofst_, tops_, itop_, top_, row_, col_);
    io(dbf_, mrk_, stall_flags_, gif_wait_, state_, cmd_, skip_, need_, buf_, direct_part_, direct_part_n_, word_pos_);
    io(backlog_, stats_);
    if (io.loading()) mpg_src_ = nullptr;  // profiling attribution only
}

void Vif0StubDevice::state(StateIo& io) {
    io.section("vif0");
    io(err_, mark_, data_traps_);
}

void GsSystem::state(StateIo& io) {
    io.section("gs-system");
    // Threaded pipeline: every stage idle, and the GIF holding the PATH1 queue / last tag the VU1 and GS stages have
    // (the synchronous model's state); a loaded queue goes back to the VU1 stage.
    GsPipeline* pipe = pipeline();
    if (pipe) pipe->export_to_gif();
    core_.state(io);
    priv_.state(io);
    gif_.state(io);
    if (pipe) {
        if (io.loading()) pipe->import_from_gif();
        else gif_.p1_queue().clear();
    }
    gif_fifo_.state(io);
    vif1_.state(io);
    vif0_.state(io);
    vu1_->state(io);
}

} // namespace p3fes::gs
