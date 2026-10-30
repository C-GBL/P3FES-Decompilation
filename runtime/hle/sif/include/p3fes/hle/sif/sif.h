// SIF HLE (ADR-0013 §3: runtime/hle/sif/ owns the SIF registers, DMAC channels 5-6 and the IOP RPC
// servers). The EE side -- libsifcmd, libsifrpc, libcdvd, libpad, libmc2/libdbc, the sound and CRI
// clients -- is the game's own recompiled code; this module is everything it talks to:
//
//   * the SIF register block 0x1000F200-0x1000F26F (HwDevice, map it with attach());
//   * the SIF syscalls (K-14/K-29/K-30): 0x6B sceSifStopDma, 0x76 sceSifDmaStat, 0x77 sceSifSetDma,
//     0x78 sceSifSetDChain, 0x79 sceSifSetReg, 0x7A sceSifGetReg, 0x7C Deci2Call, positive and
//     negative (i*) forms alike;
//   * the SIF1 (EE -> IOP) data path: sceSifSetDma copies into IOP RAM at once and the IOP consumes
//     command packets immediately;
//   * the SIF0 (IOP -> EE) path: answers are queued and delivered by service(): data into EE RAM,
//     then the packet into the EE's receive buffer and HwBus::dma_complete(5), one packet per
//     re-arm (sceSifSetDChain) exactly like the hardware chain the EE re-starts in its handler;
//   * the IOP itself (iop.h).
//
// Who calls what (runtime/hle/sif/README.md §2):
//   * the kernel installs the syscalls (install_sif_syscalls) and calls service() at its check
//     points -- at least whenever Timebase::cycles >= next_event_cycles() and after every
//     VBLANK_START (PADMAN frames). service() returns at once when nothing is due;
//   * every SIF syscall also runs service() itself, so RPC traffic flows from syscalls alone.
//
// Single-threaded (ADR-0013 §1).
#pragma once

#include <array>
#include <memory>
#include <vector>

#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/hle/sif/iop.h"

namespace p3fes {
class StateIo;  // p3fes/state_io.h
}

namespace p3fes::hle::sif {

namespace detail {
class SifRegsDevice;
class SifChannel;
}  // namespace detail

// Syscall numbers this module implements (ps2sdk ee/kernel/include/syscallnr.h @ 329e2bb; obs as the
// `li v1,N` of the wrappers at 0x503430 and 0x503500-0x503590). Negative forms share the slot.
namespace syscall_no {
inline constexpr int kSifStopDma = 0x6B;
inline constexpr int kSifDmaStat = 0x76;
inline constexpr int kSifSetDma = 0x77;
inline constexpr int kSifSetDChain = 0x78;
inline constexpr int kSifSetReg = 0x79;
inline constexpr int kSifGetReg = 0x7A;
inline constexpr int kDeci2Call = 0x7C;
}  // namespace syscall_no
inline constexpr std::array<int, 7> kSifSyscalls = {
    syscall_no::kSifStopDma, syscall_no::kSifDmaStat, syscall_no::kSifSetDma, syscall_no::kSifSetDChain,
    syscall_no::kSifSetReg,  syscall_no::kSifGetReg,  syscall_no::kDeci2Call,
};

// The signature the kernel calls an installed syscall with (runtime/include/p3fes/hle/kernel.h,
// uncommitted at the time of writing: `std::function<u64(EEContext&, int number)>`; the return value
// goes to $v0). Spelled here so this module does not depend on the kernel's header.
using SifSyscallFn = u64 (*)(EEContext& ctx, int number);

struct SifStats {
    u64 set_dma_calls = 0;
    u64 set_dma_rejected = 0;  // count <= 0, too many entries, or the list is not in EE memory
    u64 dchain_calls = 0;
    u64 stop_dma_calls = 0;
    u64 reg_reads = 0;
    u64 reg_writes = 0;
    u64 unhandled_reg_accesses = 0;
    u64 unexpected_channel_transfers = 0;  // DMAC ch5/ch6 started by register writes (not by syscalls)
};

class SifHle {
public:
    // `disc` (optional) feeds cdvdfsv through a CdvdHle; it must outlive this object. Without it the
    // CDVD servers still answer (reads fail with SCECdErREAD, searches find nothing).
    SifHle(EEMemory& mem, HwBus& bus, IopConfig config = {}, DiscSource* disc = nullptr);
    ~SifHle();
    SifHle(const SifHle&) = delete;
    SifHle& operator=(const SifHle&) = delete;

    // Maps the register block on the bus and installs the DMAC channel 5/6 handlers.
    void attach();
    HwDevice& registers();
    DmaChannelHandler& sif0_channel();
    DmaChannelHandler& sif1_channel();

    // One SIF syscall; `number` is $v1 (either sign). Returns the $v0 value. Arguments in $a0/$a1.
    u64 syscall(EEContext& ctx, int number);

    // Delivers due IOP -> EE traffic and advances IOP timers (reboot, CDVD latency, PADMAN frames).
    void service();
    // Earliest Timebase::cycles at which service() has work: <= now if something is deliverable now,
    // UINT64_MAX if idle or waiting on the EE (re-arm / buffer consumption) or on the next vblank.
    u64 next_event_cycles() const;

    // SIF0 receive armed (what DMAC D5_CHCR.STR should report): set by sceSifSetDChain, cleared by
    // each delivered packet and by sceSifStopDma. Initially set (inf: the boot loader leaves it so).
    bool sif0_started() const;

    IopHle& iop();
    const SifStats& stats() const;

    // Machine state of the SIF + IOP side (sif.cpp, iop_state.cpp).
    void state(StateIo& io);

private:
    EEMemory& mem_;
    HwBus& bus_;
    IopHle iop_;
    SifStats stats_{};
    u32 next_dma_id_ = 1;
    bool sif0_started_ = true;
    std::unique_ptr<detail::SifRegsDevice> regs_dev_;
    std::unique_ptr<detail::SifChannel> ch5_;
    std::unique_ptr<detail::SifChannel> ch6_;

    detail::IopCore& core();
    u64 set_dma(EEContext& ctx);
    u32 get_reg(u32 r);
    u32 set_reg(u32 r, u32 v);
    s32 deci2_call(EEContext& ctx);  // Deci2Call (K-30): DECI2 manager without a host (sif.cpp)
    std::vector<u16> deci2_protocols_;  // socket id -> protocol (0 = closed)
    friend class detail::SifRegsDevice;
    friend class detail::SifChannel;
};

// Installs kSifSyscalls on a kernel exposing `install_syscall(int, F)` where F is constructible from
// a `u64(EEContext&, int)` callable (runtime/include/p3fes/hle/kernel.h). `sif` must outlive `kernel`'s
// use of the slots. Returns the number of slots the kernel accepted.
template <class Kernel>
int install_sif_syscalls(Kernel& kernel, SifHle& sif) {
    int accepted = 0;
    for (int n : kSifSyscalls) {
        if (kernel.install_syscall(n, [&sif](EEContext& ctx, int number) -> u64 { return sif.syscall(ctx, number); }))
            ++accepted;
    }
    return accepted;
}

}  // namespace p3fes::hle::sif
