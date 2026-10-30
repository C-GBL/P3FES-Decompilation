// The IPU as one object on the EE bus: the register and FIFO windows (HwDevice), the DMAC channel 3 (fromIPU) and
// 4 (toIPU) data paths (DmaChannelHandler), the INTC cause-8 line and a device service for timed completion.
// `attach(bus)` is the whole integration with the kernel/timing owner (runtime/ipu/README.md "Integration").
#pragma once

#include "p3fes/hle/hw_bus.h"
#include "p3fes/ipu/ipu_core.h"

#include <functional>

namespace p3fes::ipu {

class IpuSystem {
public:
    explicit IpuSystem(IpuCosts costs = {});
    IpuSystem(const IpuSystem&) = delete;
    IpuSystem& operator=(const IpuSystem&) = delete;

    // Maps 0x10002000-0x10002040 (IPU_CMD/CTRL/BP/TOP) and 0x10007000-0x10007020 (out/in FIFO), installs the
    // DMAC channel 3 and 4 handlers, and takes the time base and INTC line (cause 8) from `bus`.
    void attach(hle::HwBus& bus);

    // Kernel::add_device_service body: completes a command whose completion cycle has passed and returns the next
    // completion cycle (UINT64_MAX when none). Completion is also evaluated at every IPU register access and DMA
    // transfer, so BUSY polling never waits for a service call; the service makes INTC 8 timely when the CPU is
    // not touching the IPU.
    u64 service();

    IpuCore& core() noexcept { return core_; }
    hle::HwDevice& regs_device() noexcept { return regs_; }
    hle::HwDevice& fifo_device() noexcept { return fifo_; }
    hle::DmaChannelHandler& dma_from_ipu() noexcept { return from_; }  // channel 3
    hle::DmaChannelHandler& dma_to_ipu() noexcept { return to_; }      // channel 4

    // Fail-closed reports (IpuTrap). Default: one line on stderr. The host routes this to RtHooks::fatal.
    void set_trap_handler(std::function<void(const IpuTrap&)> h);

    void state(StateIo& io) { core_.state(io); }  // machine state: the core's (the rest is wiring)

private:
    u64 now() const { return bus_ ? bus_->time().cycles : 0; }
    void bad_access(u32 pa, u32 width, bool write, u64 value);

    class Regs final : public hle::HwDevice {
    public:
        explicit Regs(IpuSystem& s) : s_(s) {}
        u32 read32(u32 pa) override;
        void write32(u32 pa, u32 v) override;
        u64 read64(u32 pa) override;
        void write64(u32 pa, u64 v) override;
        u128 read128(u32 pa) override { return u128::from_u64(read64(pa)); }
        void write128(u32 pa, const u128& v) override { write64(pa, v.lo()); }
        void write8(u32 pa, u8 v) override { s_.bad_access(pa, 8, true, v); }
        void write16(u32 pa, u16 v) override { s_.bad_access(pa, 16, true, v); }

    private:
        IpuSystem& s_;
    };
    class Fifo final : public hle::HwDevice {
    public:
        explicit Fifo(IpuSystem& s) : s_(s) {}
        u128 read128(u32 pa) override;
        void write128(u32 pa, const u128& v) override;
        u32 read32(u32 pa) override { s_.bad_access(pa, 32, false, 0); return 0; }
        void write32(u32 pa, u32 v) override { s_.bad_access(pa, 32, true, v); }
        u64 read64(u32 pa) override { s_.bad_access(pa, 64, false, 0); return 0; }
        void write64(u32 pa, u64 v) override { s_.bad_access(pa, 64, true, v); }
        u8 read8(u32 pa) override { s_.bad_access(pa, 8, false, 0); return 0; }
        u16 read16(u32 pa) override { s_.bad_access(pa, 16, false, 0); return 0; }
        void write8(u32 pa, u8 v) override { s_.bad_access(pa, 8, true, v); }
        void write16(u32 pa, u16 v) override { s_.bad_access(pa, 16, true, v); }

    private:
        IpuSystem& s_;
    };
    class FromIpu final : public hle::DmaChannelHandler {
    public:
        explicit FromIpu(IpuSystem& s) : s_(s) {}
        std::size_t transfer(u128* data, std::size_t qwc, u64 tag) override;

    private:
        IpuSystem& s_;
    };
    class ToIpu final : public hle::DmaChannelHandler {
    public:
        explicit ToIpu(IpuSystem& s) : s_(s) {}
        std::size_t transfer(u128* data, std::size_t qwc, u64 tag) override;

    private:
        IpuSystem& s_;
    };

    IpuCore core_;
    hle::HwBus* bus_ = nullptr;
    Regs regs_{*this};
    Fifo fifo_{*this};
    FromIpu from_{*this};
    ToIpu to_{*this};
    std::function<void(const IpuTrap&)> trap_;
};

} // namespace p3fes::ipu
