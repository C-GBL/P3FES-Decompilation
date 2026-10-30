// SifHle: SIF registers, the SIF syscalls, the SIF1 copy into IOP RAM and the SIF0 delivery loop.
#include "p3fes/hle/sif/sif.h"

#include <algorithm>
#include <string>
#include <vector>

#include "iop/iop_core.h"
#include "p3fes/prof.h"
#include "p3fes/state_io.h"

namespace p3fes::hle::sif {
namespace detail {

// 0x1000F200-0x1000F26F. The game reaches these only through the kernel's sceSifSetReg/GetReg (which
// this module implements), so the MMIO view exists for completeness and for a kernel/BIOS that pokes
// them. Semantics (inf, SIF protocol as ps2sdk's sifman documents who writes what): MSCOM EE-written;
// SMCOM read-only for the EE (the IOP's sifcmd buffer); MSFLG: an EE write sets bits; SMFLG: an EE
// write clears bits (the IOP sets them) -- what sceSifResetIop's SetReg(4, BOOTEND / SIFINIT /
// CMDINIT) relies on (obs 0x50C92C..0x50C95C); CTRL and BD6 store and read back the written value.
class SifRegsDevice final : public HwDevice {
public:
    explicit SifRegsDevice(SifHle& s) : s_(s) {}
    u32 read32(u32 pa) override {
        switch (pa) {
        case kRegMscom: return s_.get_reg(reg::kMainAddr);
        case kRegSmcom: return s_.get_reg(reg::kSubAddr);
        case kRegMsflg: return s_.get_reg(reg::kMsFlag);
        case kRegSmflg: return s_.get_reg(reg::kSmFlag);
        case kRegCtrl: return s_.core().regs().ctrl;
        case kRegBd6: return s_.core().regs().bd6;
        default: ++s_.stats_.unhandled_reg_accesses; return 0;
        }
    }
    void write32(u32 pa, u32 v) override {
        switch (pa) {
        case kRegMscom: s_.set_reg(reg::kMainAddr, v); break;
        case kRegSmcom: s_.set_reg(reg::kSubAddr, v); break;
        case kRegMsflg: s_.set_reg(reg::kMsFlag, v); break;
        case kRegSmflg: s_.set_reg(reg::kSmFlag, v); break;
        case kRegCtrl: s_.core().regs().ctrl = v; break;
        case kRegBd6: s_.core().regs().bd6 = v; break;
        default: ++s_.stats_.unhandled_reg_accesses; break;
        }
    }
    u64 read64(u32 pa) override { return read32(pa); }
    void write64(u32 pa, u64 v) override { write32(pa, static_cast<u32>(v)); }

private:
    SifHle& s_;
};

// DMAC channels 5/6 as register-started transfers. The game drives SIF DMA only through the
// syscalls (`12` §2.3), so a register-started transfer is unexpected: it is counted, consumed and
// otherwise ignored (SIF0's destination comes from IOP-side tags, not from MADR).
class SifChannel final : public DmaChannelHandler {
public:
    SifChannel(SifHle& s, unsigned ch) : s_(s), ch_(ch) {}
    std::size_t transfer(u128* /*data*/, std::size_t qwc, u64 /*tag*/) override {
        if (++s_.stats_.unexpected_channel_transfers == 1)
            s_.core().log("[sif] DMAC channel " + std::to_string(ch_) + " started by register writes (consumed, ignored)");
        return qwc;
    }

private:
    SifHle& s_;
    unsigned ch_;
};

}  // namespace detail

// inf: the kernel's SIF DMA queue depth. libsifcmd never sends more than 32 entries (31 + its sync
// packet, sceSifSetDmaInternal 0x505FD8).
static constexpr s32 kMaxDmaTransfers = 32;

SifHle::SifHle(EEMemory& mem, HwBus& bus, IopConfig config, DiscSource* disc)
    : mem_(mem),
      bus_(bus),
      iop_(std::make_unique<detail::IopCore>(mem, bus, std::move(config), disc)),
      regs_dev_(std::make_unique<detail::SifRegsDevice>(*this)),
      ch5_(std::make_unique<detail::SifChannel>(*this, 5)),
      ch6_(std::make_unique<detail::SifChannel>(*this, 6)) {}

SifHle::~SifHle() = default;

detail::IopCore& SifHle::core() { return *iop_.core_; }

void SifHle::attach() {
    bus_.map(kRegBase, kRegEnd, regs_dev_.get());
    bus_.set_dma_handler(5, ch5_.get());
    bus_.set_dma_handler(6, ch6_.get());
}

HwDevice& SifHle::registers() { return *regs_dev_; }
DmaChannelHandler& SifHle::sif0_channel() { return *ch5_; }
DmaChannelHandler& SifHle::sif1_channel() { return *ch6_; }
IopHle& SifHle::iop() { return iop_; }
const SifStats& SifHle::stats() const { return stats_; }
bool SifHle::sif0_started() const { return sif0_started_; }

void SifHle::service() {
    const prof::Scope prof_zone(prof::Zone::Iop);
    detail::IopCore& c = core();
    c.tick();
    c.flush_sif0(sif0_started_);
}

u64 SifHle::next_event_cycles() const { return iop_.core_->next_event_cycles(sif0_started_); }

void SifHle::state(StateIo& io) {
    io.section("sif");
    io(stats_, next_dma_id_, sif0_started_, deci2_protocols_);
    core().state(io);
}

u32 SifHle::get_reg(u32 r) {
    ++stats_.reg_reads;
    detail::SifRegisterFile& f = core().regs();
    switch (r) {
    case reg::kMainAddr: return f.mscom;
    case reg::kSubAddr: return f.smcom;
    case reg::kMsFlag: return f.msflg;
    case reg::kSmFlag: return f.smflg;
    default: break;
    }
    if ((r & reg::kSystem) != 0 && (r & ~reg::kSystem) < reg::kSystemCount) return f.sys[r & ~reg::kSystem];
    ++stats_.unhandled_reg_accesses;
    return 0;
}

u32 SifHle::set_reg(u32 r, u32 v) {
    ++stats_.reg_writes;
    detail::SifRegisterFile& f = core().regs();
    u32 old = 0;
    switch (r) {
    case reg::kMainAddr: old = f.mscom; f.mscom = v; return old;
    case reg::kSubAddr: ++stats_.unhandled_reg_accesses; return f.smcom;  // IOP-owned
    case reg::kMsFlag: old = f.msflg; f.msflg |= v; return old;
    case reg::kSmFlag: old = f.smflg; f.smflg &= ~v; return old;
    default: break;
    }
    if ((r & reg::kSystem) != 0 && (r & ~reg::kSystem) < reg::kSystemCount) {
        old = f.sys[r & ~reg::kSystem];
        f.sys[r & ~reg::kSystem] = v;
        return old;
    }
    ++stats_.unhandled_reg_accesses;
    return 0;
}

u64 SifHle::set_dma(EEContext& ctx) {
    ++stats_.set_dma_calls;
    const u32 list = static_cast<u32>(ctx.gpr[GPR_A0].u64[0]);
    const s32 count = static_cast<s32>(ctx.gpr[GPR_A1].u64[0]);
    if (count <= 0 || count > kMaxDmaTransfers) {
        ++stats_.set_dma_rejected;
        return 0;
    }
    const u8* d = mem_.resolve(list, static_cast<u32>(count) * kDmaTransferSize);
    if (d == nullptr) {
        ++stats_.set_dma_rejected;
        core().log("[sif] sceSifSetDma: transfer list " + detail::hex32(list) + " is not in EE memory");
        return 0;
    }
    std::vector<DmaTransfer> ts;
    ts.reserve(static_cast<std::size_t>(count));
    for (s32 i = 0; i < count; ++i)
        ts.push_back(decode_dma_transfer(std::span<const u8>(d + static_cast<std::size_t>(i) * kDmaTransferSize, kDmaTransferSize)));
    for (const DmaTransfer& t : ts) {
        // The SIF moves whole quadwords (inf: the kernel builds the chain with qwc = (size + 15) / 16).
        const u32 n = (t.size + 15u) & ~15u;
        if (n == 0) continue;
        if (n > detail::kIopRamSize) {
            core().log("[sif] sceSifSetDma: transfer of " + std::to_string(t.size) + " bytes exceeds IOP RAM (dropped)");
            continue;
        }
        const u8* src = mem_.resolve(t.src, n);
        u32 len = n;
        if (src == nullptr) {  // the rounding may cross the end of EE RAM: take the exact size
            src = mem_.resolve(t.src, t.size);
            len = t.size;
        }
        if (src == nullptr) {
            core().note_unknown(UnknownEvent::Kind::Dma, t.src, t.size, "sceSifSetDma source not in EE memory (dropped)");
            continue;
        }
        core().sif1_receive(t.dest, std::span<const u8>(src, len), t.attr);
    }
    const u32 id = next_dma_id_++;
    if (next_dma_id_ == 0) next_dma_id_ = 1;
    return id;
}

// Deci2Call (K-30): a DECI2 manager with no host attached. The game's only client is libkernel's TTY
// (sceTtyInit 0x504B00 opens protocol 0x210; sceTtyWrite 0x5048B8 = ReqSend, then Poll until its handler
// clears the busy word). Observed in the PCSX2 first_flip state (BIOS v02.30 kernel): the TTY block
// 0x966650 holds socket -3 (a second Open after sceResetttyinit, DECI2_ERR_ALREADYUSE), wlen 0x14 unsent
// and the busy word 0, i.e. the first write ended without sending anything. Modelled (inf, the BIOS deci2
// code is not traced): Open succeeds once per protocol, re-opening it is ALREADYUSE; every send
// (ReqSend/ExReqSend/ExSend/ExRecv) fails with DECI2_ERR_NOROUTE (-10), which the TTY client handles by
// clearing its busy word itself (0x5049AC); Poll/Lock/Unlock/Close succeed; kputs (0x10) is logged.
// Error values from ps2sdk ee/kernel/include/deci2.h.
s32 SifHle::deci2_call(EEContext& ctx) {
    constexpr s32 kErrInvalSock = -2, kErrAlreadyUse = -3, kErrNoRoute = -10;
    const u32 fn = static_cast<u32>(ctx.gpr[GPR_A0].u64[0]);
    const u32 blk = static_cast<u32>(ctx.gpr[GPR_A1].u64[0]);
    const auto valid = [this](s32 s) { return s >= 0 && static_cast<std::size_t>(s) < deci2_protocols_.size() && deci2_protocols_[static_cast<std::size_t>(s)] != 0; };
    switch (fn) {
    case 1: {  // Open {u16 protocol, opt, handler, work}
        const u16 proto = mem_.read<u16>(blk);
        for (u16 p : deci2_protocols_)
            if (p == proto) return kErrAlreadyUse;
        deci2_protocols_.push_back(proto);
        return static_cast<s32>(deci2_protocols_.size() - 1);
    }
    case 2: {  // Close {socket}
        const s32 s = static_cast<s32>(mem_.read<u32>(blk));
        if (!valid(s)) return kErrInvalSock;
        deci2_protocols_[static_cast<std::size_t>(s)] = 0;
        return 0;
    }
    case 3: case 5: case 6: case 7:  // ReqSend, ExRecv, ExSend, ExReqSend: no route to a host
        return valid(static_cast<s32>(mem_.read<u32>(blk))) ? kErrNoRoute : kErrInvalSock;
    case 4: case 8: case 9:  // Poll, ExLock, ExUnLock
        return valid(static_cast<s32>(mem_.read<u32>(blk))) ? 0 : kErrInvalSock;
    case 0x10: {  // kputs {char*}
        std::string s;
        for (u32 p = mem_.read<u32>(blk); s.size() < 512; ++p) {
            const u8 c = mem_.read<u8>(p);
            if (!c) break;
            s.push_back(static_cast<char>(c));
        }
        core().log("[deci2] kputs: " + s);
        return 0;
    }
    default:
        core().log("[deci2] Deci2Call function " + std::to_string(fn) + " not modelled; returning DECI2_ERR_INVALID");
        return -1;
    }
}

u64 SifHle::syscall(EEContext& ctx, int number) {
    const prof::Scope prof_zone(prof::Zone::Iop);
    const int n = number < 0 ? -number : number;
    service();  // due IOP work first (a reboot that completed, deferred results)
    u64 ret = 0;
    auto sext = [](u32 v) { return static_cast<u64>(static_cast<s64>(static_cast<s32>(v))); };
    switch (n) {
    case syscall_no::kSifSetDma:
        ret = set_dma(ctx);
        break;
    case syscall_no::kSifDmaStat:
        // Every transfer completed inside sceSifSetDma (ADR-0013 §3: DMA runs synchronously), so any id
        // reports "done" (< 0). Both pollers (H_Sndcom_CopyToIop 0x10CCE0, _send_to_iop 0x511478)
        // only wait for that.
        ret = sext(static_cast<u32>(-1));
        break;
    case syscall_no::kSifSetDChain:
        ++stats_.dchain_calls;
        sif0_started_ = true;
        break;
    case syscall_no::kSifStopDma:
        ++stats_.stop_dma_calls;
        sif0_started_ = false;
        break;
    case syscall_no::kSifSetReg:
        ret = sext(set_reg(static_cast<u32>(ctx.gpr[GPR_A0].u64[0]), static_cast<u32>(ctx.gpr[GPR_A1].u64[0])));
        break;
    case syscall_no::kSifGetReg:
        ret = sext(get_reg(static_cast<u32>(ctx.gpr[GPR_A0].u64[0])));
        break;
    case syscall_no::kDeci2Call:
        ret = sext(static_cast<u32>(deci2_call(ctx)));
        break;
    default:
        core().log("[sif] syscall " + std::to_string(number) + " routed to the SIF module but not one of its slots");
        break;
    }
    service();  // deliver what this syscall produced (RPC ends, a re-armed SIF0)
    return ret;
}

}  // namespace p3fes::hle::sif
