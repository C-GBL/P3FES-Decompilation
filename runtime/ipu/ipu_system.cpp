// IpuSystem: the IPU on the EE bus (register/FIFO windows, DMAC channels 3/4, INTC cause 8, device service).
// Written for p3fes-port against runtime/include/p3fes/hle/hw_bus.h.
#include "p3fes/ipu/ipu_system.h"
#include "p3fes/prof.h"

#include <cstdio>

namespace p3fes::ipu {

IpuSystem::IpuSystem(IpuCosts costs) : core_(costs) {
    core_.set_completion_handler([this] {
        if (bus_) bus_->raise_intc(kIntcIpu);
    });
    core_.set_trap_handler([this](const IpuTrap& t) {
        if (trap_) trap_(t);
        else std::fprintf(stderr, "[ipu] trap: %s\n", t.message.c_str());
    });
}

void IpuSystem::attach(hle::HwBus& bus) {
    bus_ = &bus;
    bus.map(kRegBase, kRegEnd, &regs_);
    bus.map(kFifoBase, kFifoEnd, &fifo_);
    bus.set_dma_handler(kDmaFromIpu, &from_);
    bus.set_dma_handler(kDmaToIpu, &to_);
}

u64 IpuSystem::service() {
    const prof::Scope prof_zone(prof::Zone::Ipu);
    return core_.update(now());
}

void IpuSystem::set_trap_handler(std::function<void(const IpuTrap&)> h) { trap_ = std::move(h); }

void IpuSystem::bad_access(u32 pa, u32 width, bool write, u64 value) {
    char buf[160];
    std::snprintf(buf, sizeof buf, "unmodelled IPU access: %u-bit %s 0x%08X%s", width, write ? "write to" : "read of", pa,
                  write ? "" : " (reads 0)");
    std::string msg = buf;
    if (write) {
        std::snprintf(buf, sizeof buf, " value 0x%llX", static_cast<unsigned long long>(value));
        msg += buf;
    }
    IpuTrap t;
    t.kind = IpuTrap::Kind::ReservedRegister;
    t.pa = pa;
    t.value = value;
    t.message = std::move(msg);
    if (trap_) trap_(t);
    else std::fprintf(stderr, "[ipu] trap: %s\n", t.message.c_str());
}

// ---- registers: IPU_CMD / IPU_TOP are 64-bit (BUSY in bit 63, i.e. bit 31 of the upper word), CTRL / BP 32-bit.

u32 IpuSystem::Regs::read32(u32 pa) {
    const u64 t = s_.now();
    switch (pa) {
    case kIpuCmd: return static_cast<u32>(s_.core_.read_cmd(t));
    case kIpuCmd + 4: return static_cast<u32>(s_.core_.read_cmd(t) >> 32);
    case kIpuCtrl: return s_.core_.read_ctrl(t);
    case kIpuBp: return s_.core_.read_bp(t);
    case kIpuTop: return static_cast<u32>(s_.core_.read_top(t));
    case kIpuTop + 4: return static_cast<u32>(s_.core_.read_top(t) >> 32);
    default: break;
    }
    s_.bad_access(pa, 32, false, 0);
    return 0;
}

void IpuSystem::Regs::write32(u32 pa, u32 v) {
    const prof::Scope prof_zone(prof::Zone::Ipu);
    const u64 t = s_.now();
    switch (pa) {
    case kIpuCmd: s_.core_.write_cmd(v, t); return;
    case kIpuCtrl: s_.core_.write_ctrl(v, t); return;
    default: break;
    }
    s_.bad_access(pa, 32, true, v);
}

u64 IpuSystem::Regs::read64(u32 pa) {
    const u64 t = s_.now();
    switch (pa) {
    case kIpuCmd: return s_.core_.read_cmd(t);
    case kIpuCtrl: return s_.core_.read_ctrl(t);
    case kIpuBp: return s_.core_.read_bp(t);
    case kIpuTop: return s_.core_.read_top(t);
    default: break;
    }
    s_.bad_access(pa, 64, false, 0);
    return 0;
}

void IpuSystem::Regs::write64(u32 pa, u64 v) {
    switch (pa) {
    case kIpuCmd:
    case kIpuCtrl: write32(pa, static_cast<u32>(v)); return;
    default: break;
    }
    s_.bad_access(pa, 64, true, v);
}

// ---- FIFOs ----

u128 IpuSystem::Fifo::read128(u32 pa) {
    if (pa == kOutFifo) {
        u128 q{};
        s_.core_.read_out_fifo(q, s_.now());
        return q;
    }
    s_.bad_access(pa, 128, false, 0);
    return u128{};
}

void IpuSystem::Fifo::write128(u32 pa, const u128& v) {
    const prof::Scope prof_zone(prof::Zone::Ipu);
    if (pa == kInFifo) {
        s_.core_.write_in_fifo(v, s_.now());
        return;
    }
    s_.bad_access(pa, 128, true, v.lo());
}

// ---- DMAC data paths (hw_bus.h contract: return the qwords consumed/produced; fewer = stalled, retried later) --

std::size_t IpuSystem::FromIpu::transfer(u128* data, std::size_t qwc, u64) {
    return s_.core_.pop_output(data, qwc, s_.now());
}

std::size_t IpuSystem::ToIpu::transfer(u128* data, std::size_t qwc, u64) {
    return s_.core_.push_input(data, qwc, s_.now());
}

} // namespace p3fes::ipu
