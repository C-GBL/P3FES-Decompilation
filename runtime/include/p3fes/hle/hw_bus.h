// Hardware bus: the one place a guest access to the EE hardware-register windows is routed to a
// device model, and the shared virtual time base (ADR-0013).
//
// Ownership (ADR-0013 §3): the kernel/timing HLE (`runtime/hle/kernel/`) owns the bus instance,
// the INTC and timer registers, the DMAC register block and the virtual time base. Other device
// models register their ranges: GS privileged registers + VIF/GIF (`runtime/gs/`), SIF
// (`runtime/hle/sif/`). DMA channel transfers are delegated per channel through
// `DmaChannelHandler`; the DMAC register block itself (CHCR/MADR/QWC/TADR, D_STAT, D_PCR, ...)
// stays with the owner so that completion -> D_STAT bit -> DMAC handler chain is modelled once.
//
// Addresses are *physical* (`EEMemory::to_physical`): 0x10000000-0x1000FFFF (EE registers) and
// 0x12000000-0x12001FFF (GS privileged). Widths follow the guest access: the EE writes GS
// privileged registers as 64-bit, most EE registers as 32-bit, VIF FIFOs as 128-bit.
//
// Everything here is single-threaded (ADR-0013 §1): devices are called from the guest's host
// thread, never concurrently. A device that must raise an interrupt does so through `HwBus`
// (`raise_intc`, `dma_complete`); it never touches INTC_STAT/D_STAT storage directly.
#pragma once

#include "p3fes/ee_types.h"

#include <cstddef>

namespace p3fes::hle {

// Virtual time (ADR-0013 §2). `cycles` is advanced by the generated code (one `ctx.cycles +=
// N` per basic block, N = instruction count) and by the HLE for work it models (DMA, syscalls).
// `hlines` and `field` are derived from it by the owner: NTSC 262.5 H-lines per field at
// 59.94 fields/s; `field` toggles at each VBLANK_START and is what `GS CSR.FIELD` reports.
struct Timebase {
    u64 cycles = 0;       // EE cycles, 294,912,000 per second
    u64 hlines = 0;       // H-lines elapsed (NTSC: 15,734.26 per second)
    u32 field = 0;        // 0 = even, 1 = odd; toggles at every VBLANK_START
    u64 vblanks = 0;      // VBLANK_START count since reset
};

// A memory-mapped device. Default implementations report the access as unhandled (the owner
// counts and logs them; reads return 0). Implement only the widths the guest uses for the
// registers you own; the bus never splits or merges accesses.
class HwDevice {
public:
    virtual ~HwDevice() = default;
    virtual u32  read32(u32 pa)                 { (void)pa; return 0; }
    virtual void write32(u32 pa, u32 v)         { (void)pa; (void)v; }
    virtual u64  read64(u32 pa)                 { return read32(pa); }
    virtual void write64(u32 pa, u64 v)         { write32(pa, static_cast<u32>(v)); }
    virtual u128 read128(u32 pa)                { return u128::from_u64(read64(pa)); }
    virtual void write128(u32 pa, const u128& v) { write64(pa, v.lo()); }
    virtual u8   read8(u32 pa)                  { return static_cast<u8>(read32(pa & ~3u) >> ((pa & 3u) * 8u)); }
    virtual u16  read16(u32 pa)                 { return static_cast<u16>(read32(pa & ~3u) >> ((pa & 2u) * 8u)); }
    virtual void write8(u32 pa, u8 v)           { write32(pa, v); }
    virtual void write16(u32 pa, u16 v)         { write32(pa, v); }
};

// One DMAC channel's data path. The owner decodes CHCR/MADR/QWC/TADR (and the tag chain in
// chain mode) and hands each transfer here; `transfer` performs the copy from/to guest RAM via
// the pointers given, returns the number of quadwords consumed, and the owner completes the
// channel (D_STAT bit, DMAC handler chain) when QWC reaches 0 or the tag chain ends. A handler
// that needs to stall (GIF path arbitration, SIF waiting for the "IOP") returns fewer quadwords
// and is called again on the next `service()`.
class DmaChannelHandler {
public:
    virtual ~DmaChannelHandler() = default;
    // `data` points at `qwc` quadwords of guest RAM (direction per channel: to-device for
    // VIF0/VIF1/GIF/SIF1/toSPR, from-device for SIF0/fromSPR/IPU_out). `tag` is the DMAtag that
    // started this transfer in chain mode (0 in normal mode).
    virtual std::size_t transfer(u128* data, std::size_t qwc, u64 tag) = 0;
};

class HwBus {
public:
    virtual ~HwBus() = default;

    // Route [pa_begin, pa_end) to `dev`. Ranges must not overlap; the owner refuses otherwise.
    virtual void map(u32 pa_begin, u32 pa_end, HwDevice* dev) = 0;
    // Install the data path of DMAC channel `ch` (0 VIF0, 1 VIF1, 2 GIF, 3 fromIPU, 4 toIPU,
    // 5 SIF0, 6 SIF1, 7 SIF2, 8 fromSPR, 9 toSPR).
    virtual void set_dma_handler(unsigned ch, DmaChannelHandler* h) = 0;

    // Interrupt sources. `raise_intc(cause)` sets INTC_STAT bit `cause` (2 VBLANK_START, 3
    // VBLANK_END, 9 TIM0, 10 TIM1, 11 TIM2, 12 TIM3, ...); `dma_complete(ch)` sets D_STAT bit
    // `ch`. Delivery to handler chains happens at the next check point (ADR-0013 §2), never
    // inside the call.
    virtual void raise_intc(unsigned cause) = 0;
    virtual void dma_complete(unsigned ch) = 0;

    virtual const Timebase& time() const = 0;

    // Guest access entry points used by the rt adapter (physical address, width by name).
    virtual u32  read32(u32 pa) = 0;
    virtual void write32(u32 pa, u32 v) = 0;
    virtual u64  read64(u32 pa) = 0;
    virtual void write64(u32 pa, u64 v) = 0;
    virtual u128 read128(u32 pa) = 0;
    virtual void write128(u32 pa, const u128& v) = 0;
    virtual u8   read8(u32 pa) = 0;
    virtual u16  read16(u32 pa) = 0;
    virtual void write8(u32 pa, u8 v) = 0;
    virtual void write16(u32 pa, u16 v) = 0;
};

} // namespace p3fes::hle
