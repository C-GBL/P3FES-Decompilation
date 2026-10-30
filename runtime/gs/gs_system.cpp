// GsSystem: wiring of GS core, privileged registers, GIF, VIF1/VU1 and the DMAC channel handlers.
#include "p3fes/gs/gs_system.h"

namespace p3fes::gs {

GsSystem::GsSystem()
    : priv_(core_),
      gif_(core_),
      vu1_(std::make_unique<vu1::VU1Interpreter>(this)),
      vif1_(gif_, core_, *vu1_),
      gif_regs_(gif_),
      gif_fifo_(gif_),
      gif_dma_(gif_),
      vif1_regs_(vif1_),
      vif1_fifo_(vif1_),
      vif1_dma_(vif1_, priv_.busdir_source()),
      vif0_(&trap_),
      vif0_dma_(vif0_) {
    core_.set_events(&priv_);
    gif_.set_busdir_source(priv_.busdir_source());
    vif1_.set_busdir_source(priv_.busdir_source());
    gif_.set_path2_resume([this] { vif1_.resume(); });
    gif_.set_path3_ready([this] {
        gif_fifo_.drain();
        // The host retries DMAC channel 2 inside this callback; the GIF lets one GS packet through (gif.h
        // begin_path3_window) -- the texture pair RenderWare's sync packet opened the window for.
        gif_.begin_path3_window();
        if (path3_ready_cb_) path3_ready_cb_();
        gif_.end_path3_window();
    });
}

GsSystem::~GsSystem() { stop_pipeline(); }

void GsSystem::start_pipeline(const GsPipelineOptions& o) {
    if (!pipe_) pipe_ = std::make_unique<GsPipeline>(*vu1_, core_, gif_, vif1_, priv_, *this);
    pipe_->start(o);
}

void GsSystem::stop_pipeline() {
    if (pipe_) pipe_->stop();
}

void GsSystem::quiesce() {
    if (pipe_ && pipe_->running() && !GsPipeline::on_worker()) pipe_->drain(SyncWhy::Host);
}

void GsSystem::vu1_reset() {
    if (pipe_ && pipe_->running()) pipe_->vu_reset();
    else vu1_->reset();
}

void GsSystem::set_trap_handler(std::function<void(const VifTrap&)> h) {
    trap_ = h;
    vif1_.set_trap_handler(std::move(h));
}

void GsSystem::attach(hle::HwBus& bus) {
    priv_.set_bus(&bus);
    vif1_.set_bus(&bus);
    bus.map(GsBusRanges::kGifRegs[0], GsBusRanges::kGifRegs[1], &gif_regs_);
    bus.map(GsBusRanges::kVif0Regs[0], GsBusRanges::kVif0Regs[1], &vif0_);
    bus.map(GsBusRanges::kVif1Regs[0], GsBusRanges::kVif1Regs[1], &vif1_regs_);
    bus.map(GsBusRanges::kVif0Fifo[0], GsBusRanges::kVif0Fifo[1], &vif0_);
    bus.map(GsBusRanges::kVif1Fifo[0], GsBusRanges::kVif1Fifo[1], &vif1_fifo_);
    bus.map(GsBusRanges::kGifFifo[0], GsBusRanges::kGifFifo[1], &gif_fifo_);
    bus.map(GsBusRanges::kGsPriv[0], GsBusRanges::kGsPriv[1], &priv_);
    bus.set_dma_handler(0, &vif0_dma_);
    bus.set_dma_handler(1, &vif1_dma_);
    bus.set_dma_handler(2, &gif_dma_);
    // FLUSHA (VIF1) waits for the end of the PATH3 transfer: channel 2's CHCR.STR stays set from the kick until
    // the DMAC's completion event, which is what "transfer end" means to the game (runtime/hle/kernel/dmac.cpp).
    gif_.set_path3_dma_busy([&bus] { return (bus.read32(0x1000A000u) & 0x100u) != 0; });
}

} // namespace p3fes::gs
