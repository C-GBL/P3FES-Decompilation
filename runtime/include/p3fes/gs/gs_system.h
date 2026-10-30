// The GS subsystem as one object: GS core + privileged registers, GIF, VIF1 (+ the VIF0 stub), the VU1
// interpreter whose XGKICKs feed PATH1, and the DMAC channel 1/2 data paths (ADR-0013 §3: runtime/gs owns the GS
// privileged registers, GIF, VIF1 and DMAC channels 1-2). `attach(bus)` is the whole integration with the
// kernel/timing owner (runtime/gs/README.md "Integration").
#pragma once

#include "p3fes/gs/gif.h"
#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_output.h"
#include "p3fes/gs/gs_pipeline.h"
#include "p3fes/gs/gs_priv.h"
#include "p3fes/gs/vif1.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/vu1/vu1_interp.h"

#include <functional>
#include <memory>

namespace p3fes::gs {

// Physical ranges `attach` maps (all [begin, end)).
struct GsBusRanges {
    static constexpr u32 kGifRegs[2] = {GifRegsDevice::kBase, GifRegsDevice::kEnd};      // 0x10003000-0x100030B0
    static constexpr u32 kVif0Regs[2] = {Vif0StubDevice::kBase, Vif0StubDevice::kEnd};    // 0x10003800-0x10003980
    static constexpr u32 kVif1Regs[2] = {Vif1RegsDevice::kBase, Vif1RegsDevice::kEnd};    // 0x10003C00-0x10003D80
    static constexpr u32 kVif0Fifo[2] = {Vif0StubDevice::kFifoBase, Vif0StubDevice::kFifoEnd}; // 0x10004000-0x10004010
    static constexpr u32 kVif1Fifo[2] = {Vif1FifoDevice::kBase, Vif1FifoDevice::kEnd};    // 0x10005000-0x10005010
    static constexpr u32 kGifFifo[2] = {GifFifoDevice::kBase, GifFifoDevice::kEnd};       // 0x10006000-0x10006010
    static constexpr u32 kGsPriv[2] = {GsPrivRegs::kBase, GsPrivRegs::kEnd};              // 0x12000000-0x12002000
};

class GsSystem : public vu1::IGifSink {
public:
    GsSystem();
    ~GsSystem() override;
    GsSystem(const GsSystem&) = delete;
    GsSystem& operator=(const GsSystem&) = delete;

    // Map the device ranges above, install DMAC handlers for channels 0 (trap), 1 (VIF1) and 2 (GIF PATH3), and
    // take the time base (CSR.FIELD) and interrupt lines (GS = cause 0, VIF1 = cause 5) from `bus`.
    void attach(hle::HwBus& bus);

    GsCore& core() noexcept { return core_; }
    GsMemory& mem() noexcept { return core_.mem(); }
    GsPrivRegs& priv() noexcept { return priv_; }
    Gif& gif() noexcept { return gif_; }
    Vif1& vif1() noexcept { return vif1_; }
    vu1::VU1Interpreter& vu1() noexcept { return *vu1_; }
    hle::DmaChannelHandler& dma_vif1() noexcept { return vif1_dma_; }
    hle::DmaChannelHandler& dma_gif() noexcept { return gif_dma_; }

    // VIF/VU traps (fail closed). Default: a line on stderr. The lead routes this to rt::trap.
    void set_trap_handler(std::function<void(const VifTrap&)> h);
    // Called when PATH3 becomes unmasked while a channel-2 transfer was stalled (the DMAC owner may service
    // channel 2 at once instead of at the next check point).
    void set_path3_ready_callback(std::function<void()> cb) { path3_ready_cb_ = std::move(cb); }

    // The CRTC picture from the current display registers.
    Frame compose_output() const { return compose(core_.mem(), priv_.display()); }
    u64 flip_count() const noexcept { return priv_.flip_count(); }

    // Machine state of the whole GS side (gs_state.cpp): core + local memory, privileged registers, GIF + its
    // FIFO, VIF1, the VIF0 stub, VU1. Host wiring and choices are not part of it.
    void state(StateIo& io);

    // IGifSink: VU1 XGKICK -> PATH1.
    void kick(std::span<const u128> qwords) override { gif_.path1(qwords); }

    // Threaded graphics pipeline (gs_pipeline.h): VU1 work and the GS front end on worker threads. Off by default.
    void start_pipeline(const GsPipelineOptions& o);
    void stop_pipeline();
    GsPipeline* pipeline() noexcept { return pipe_ && pipe_->running() ? pipe_.get() : nullptr; }
    // Waits until every stage is idle (no-op without the pipeline, or on a pipeline worker): call before touching
    // the GS core, VU1 or the GIF from the host.
    void quiesce();
    // CTC2 vi28 FBRST.RS1: the VU1 reset, in order with the VU1 work in flight.
    void vu1_reset();

private:
    GsCore core_;
    GsPrivRegs priv_;
    Gif gif_;
    std::unique_ptr<vu1::VU1Interpreter> vu1_;
    Vif1 vif1_;
    GifRegsDevice gif_regs_;
    GifFifoDevice gif_fifo_;
    GifDmaHandler gif_dma_;
    Vif1RegsDevice vif1_regs_;
    Vif1FifoDevice vif1_fifo_;
    Vif1DmaHandler vif1_dma_;
    std::function<void(const VifTrap&)> trap_;
    Vif0StubDevice vif0_;
    Vif0DmaTrap vif0_dma_;
    std::function<void()> path3_ready_cb_;
    std::unique_ptr<GsPipeline> pipe_;  // last: destroyed (stopped) first
};

} // namespace p3fes::gs
