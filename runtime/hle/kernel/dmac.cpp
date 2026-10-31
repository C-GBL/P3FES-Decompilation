// Provenance: chain-walk shape (tag decode, ASR stack, TTE low-half zeroing, SPR dest chain, RAM masking) ported from snuri00/ps2-web-recomp @ c0f476e runtime/src/dmac.cpp (MIT); see THIRD_PARTY.md.
// DMAC register block (0x10008000-0x1000EFFF; D_ENABLER 0x1000F520 / D_ENABLEW 0x1000F590), the
// transfer engine (normal mode, source chain with the DMAtag set refe/cnt/next/ref/refs/call/ret/end,
// ASR stack, TTE, TIE), the SPR channels 8/9, stall/resume and completion -> D_STAT -> handler chain.
// Tag decode follows the EE User's Manual DMAC chapter; the shape of the chain walk was cross-checked
// against snuri00/ps2-web-recomp @ c0f476e runtime/src/dmac.cpp (MIT, see THIRD_PARTY.md).
//
// Channels: 0 VIF0, 1 VIF1, 2 GIF, 3 fromIPU, 4 toIPU, 5 SIF0, 6 SIF1, 7 SIF2, 8 fromSPR, 9 toSPR.
// Data paths 0-7 are DmaChannelHandlers installed by their owners (ADR-0013 §3); 8/9 are performed here.
// The whole transfer runs synchronously when CHCR.STR is set (or when a stalled data path is retried);
// completion (STR clear, D_STAT.CIS) is an event `dma_base_cycles + qwords * dma_cycles_per_qword` later.
#include "kernel_core.h"

#include <algorithm>
#include <cstring>

namespace p3fes::hle {

using namespace kc;

namespace {

constexpr u32 kChanBase[10] = {0x10008000u, 0x10009000u, 0x1000A000u, 0x1000B000u, 0x1000B400u,
                               0x1000C000u, 0x1000C400u, 0x1000C800u, 0x1000D000u, 0x1000D400u};
constexpr const char* kChanName[10] = {"VIF0", "VIF1", "GIF", "fromIPU", "toIPU", "SIF0", "SIF1", "SIF2", "fromSPR", "toSPR"};
constexpr u32 kDCtrl = 0x1000E000u, kDStat = 0x1000E010u, kDPcr = 0x1000E020u, kDSqwc = 0x1000E030u,
              kDRbsr = 0x1000E040u, kDRbor = 0x1000E050u, kDStadr = 0x1000E060u;
constexpr u32 kDEnableR = 0x1000F520u, kDEnableW = 0x1000F590u;
constexpr u32 kChcrStr = 0x100u, kChcrTte = 0x40u, kChcrTie = 0x80u;
constexpr u32 kSprMask = EEMemory::kScratchpadSize - 16u;

int channel_of(u32 pa) {
    const u32 block = pa & ~0x3FFu;
    for (int ch = 0; ch < 10; ++ch)
        if (kChanBase[ch] == block) return ch;
    return -1;
}

class DmacDev final : public HwDevice {
public:
    explicit DmacDev(KernelHooks& k) : k_(k) {}
    u32 read32(u32 pa) override { return k_.dmac_read(pa); }
    void write32(u32 pa, u32 v) override { k_.dmac_write(pa, v); }

private:
    KernelHooks& k_;
};

class DEnableDev final : public HwDevice {
public:
    explicit DEnableDev(KernelHooks& k) : k_(k) {}
    u32 read32(u32 pa) override { return k_.denable_read(pa); }
    void write32(u32 pa, u32 v) override { k_.denable_write(pa, v); }

private:
    KernelHooks& k_;
};

} // namespace

std::unique_ptr<HwDevice> kc::make_dmac_device(KernelHooks& k) { return std::make_unique<DmacDev>(k); }
std::unique_ptr<HwDevice> kc::make_denable_device(KernelHooks& k) { return std::make_unique<DEnableDev>(k); }

// ---- registers -------------------------------------------------------------------------------------

u32 KernelHooks::dmac_read(u32 pa) {
    if (census_) {
        const int c = channel_of(pa);
        if (c < 0) ++census_->dmac_ctrl_regs.reads;
        else if ((pa & 0x3FFu) == 0 && dch_[static_cast<unsigned>(c)].active) ++census_->dma_busy_polls[static_cast<unsigned>(c)];
    }
    switch (pa) {
    case kDCtrl: return d_ctrl_;
    case kDStat: return d_stat_;
    case kDPcr: return d_pcr_;
    case kDSqwc: return d_sqwc_;
    case kDRbsr: return d_rbsr_;
    case kDRbor: return d_rbor_;
    case kDStadr: return d_stadr_;
    default: break;
    }
    const int ch = channel_of(pa);
    if (ch >= 0) {
        const DmaChan& c = dch_[static_cast<unsigned>(ch)];
        switch (pa & 0x3FFu) {
        case 0x00: return c.chcr;
        case 0x10: return c.madr;
        case 0x20: return c.qwc;
        case 0x30: return c.tadr;
        case 0x40: return c.asr0;
        case 0x50: return c.asr1;
        case 0x80: return c.sadr;
        default: break;
        }
    }
    report_unhandled(pa, 32, false, 0);
    return 0;
}

void KernelHooks::dmac_write(u32 pa, u32 v) {
    if (census_ && channel_of(pa) < 0) ++census_->dmac_ctrl_regs.writes;
    switch (pa) {
    case kDCtrl:
        d_ctrl_ = v;
        dma_release_held();
        return;
    case kDStat:
        // CIS/SIS/MEIS/BEIS (bits 0-15) write-1-to-clear; the mask bits (16-31) toggle on a 1 (`15` §2.1).
        d_stat_ = (d_stat_ & ~(v & 0xFFFFu)) ^ (v & 0xFFFF0000u);
        force_check();
        return;
    case kDPcr: d_pcr_ = v; return;  // CPC/CDE/PCE: storage (Q-04); CPCOND0 is computed by the adapter from it
    case kDSqwc: d_sqwc_ = v; return;
    case kDRbsr: d_rbsr_ = v; return;
    case kDRbor: d_rbor_ = v; return;
    case kDStadr: d_stadr_ = v; return;
    default: break;
    }
    const int ch = channel_of(pa);
    if (ch < 0) {
        report_unhandled(pa, 32, true, v);
        return;
    }
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    switch (pa & 0x3FFu) {
    case 0x00: {
        if (c.active && !c.device_driven && c.phase == DmaChan::Phase::Done) {
            // Re-arm window: the data phase has ended and only the completion event (STR clear, D_STAT.CIS,
            // `dma_base_cycles + qwc * dma_cycles_per_qword` later) is pending. On hardware STR clears when
            // the transfer ends, so a CHCR write here addresses an idle channel: complete the pending
            // transfer now (CIS set; its handler chain runs at the next check point, as for a timely event),
            // then take the write — STR=1 starts the new transfer. (`_slice0 0x4FC3A8` re-arms D3 as soon as
            // D3_QWC reads 0; runtime/ipu/README.md open question 4.)
            if (census_) ++census_->dma_rearms[static_cast<unsigned>(ch)];
            dma_complete_event(ch);
        }
        const bool was = (c.chcr & kChcrStr) != 0;
        const bool now_set = (v & kChcrStr) != 0;
        if (c.active && now_set) {  // write while running: keep the engine, take the non-STR bits
            c.chcr = (v & ~0xFFFF0000u) | (c.chcr & 0xFFFF0000u) | kChcrStr;
            return;
        }
        c.chcr = v;
        if (!now_set) {
            // STR cleared by the CPU: the channel stops where it is (suspend); registers keep their state.
            c.active = c.stalled = c.held = c.device_driven = false;
            c.phase = DmaChan::Phase::Done;
            deadline_[static_cast<unsigned>(kEvDma0 + ch)] = kNever;
            return;
        }
        if (!was || !c.active) dma_start(ch);
        return;
    }
    case 0x10: c.madr = v; return;
    case 0x20: c.qwc = v & 0xFFFFu; return;
    case 0x30: c.tadr = v; return;
    case 0x40: c.asr0 = v; return;
    case 0x50: c.asr1 = v; return;
    case 0x80: c.sadr = v & kSprMask; return;
    default: break;
    }
    report_unhandled(pa, 32, true, v);
}

u32 KernelHooks::denable_read(u32 pa) {
    if (pa == kDEnableR || pa == kDEnableW) return d_enable_;
    report_unhandled(pa, 32, false, 0);
    return 0;
}

void KernelHooks::denable_write(u32 pa, u32 v) {
    if (pa != kDEnableW) {
        report_unhandled(pa, 32, true, v);
        return;
    }
    d_enable_ = v;
    dma_release_held();
}

void KernelHooks::dma_release_held() {
    if (!(d_ctrl_ & 1u) || (d_enable_ & 0x10000u)) return;
    for (int ch = 0; ch < 10; ++ch) {
        DmaChan& c = dch_[static_cast<unsigned>(ch)];
        if (c.held) {
            c.held = false;
            dma_start(ch);
        }
    }
}

// ---- engine ------------------------------------------------------------------------------------------

bool KernelHooks::dma_channel_routed(int ch) const {
    return ch == 8 || ch == 9 || dma_handlers_[static_cast<unsigned>(ch)] != nullptr;
}

u8* KernelHooks::dma_resolve(u32 addr, std::size_t& max_qw) {
    // inf (matches upstream): bit 31 selects the scratchpad (libdma ORs it into SPR addresses); other
    // addresses are physical RAM, masked to 32 MiB (so the 0x2/0x3 uncached mirrors land on RAM).
    if (addr & 0x80000000u) {
        const u32 off = addr & kSprMask;
        max_qw = (EEMemory::kScratchpadSize - off) / 16u;
        return mem_.scratchpad() + off;
    }
    const u32 off = addr & (EEMemory::kMainRamSize - 16u);
    max_qw = (EEMemory::kMainRamSize - off) / 16u;
    return mem_.main_ram() + off;
}

// Zone of a channel's data path (p3fes/prof.h).
static prof::Zone dma_zone(int ch) {
    switch (ch) {
    case 1: return prof::Zone::Vif1;
    case 2: return prof::Zone::Gif;
    case 3: case 4: return prof::Zone::Ipu;
    case 5: case 6: case 7: return prof::Zone::Iop;
    default: return prof::Zone::Hw;
    }
}

std::size_t KernelHooks::dma_sink(int ch, u128* data, std::size_t qwc, u64 tag) {
    const prof::Scope prof_zone(dma_zone(ch));
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    u8* spr = mem_.scratchpad();
    if (ch == 9) {  // toSPR: RAM -> SPR at SADR (wraps in 16 KiB)
        for (std::size_t i = 0; i < qwc; ++i) {
            std::memcpy(spr + c.sadr, data + i, 16);
            c.sadr = (c.sadr + 16u) & kSprMask;
        }
        return qwc;
    }
    if (ch == 8) {  // fromSPR normal mode: SPR at SADR -> RAM
        for (std::size_t i = 0; i < qwc; ++i) {
            std::memcpy(data + i, spr + c.sadr, 16);
            c.sadr = (c.sadr + 16u) & kSprMask;
        }
        return qwc;
    }
    return dma_handlers_[static_cast<unsigned>(ch)]->transfer(data, qwc, tag);
}

void KernelHooks::dma_start(int ch) {
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    if (!(d_ctrl_ & 1u) || (d_enable_ & 0x10000u)) {  // DMAE clear or all channels held (D_ENABLEW.CPND)
        c.held = true;
        return;
    }
    const u32 mode = (c.chcr >> 2) & 3u;
    if (d_ctrl_ & 0xFCu)
        die("DMAC ch%d (%s) started with D_CTRL 0x%08X: MFIFO/stall control (MFD/STS/STD) is not modelled", ch,
            kChanName[ch], d_ctrl_);
    if (mode >= 2)
        die("DMAC ch%d (%s) started in %s mode (CHCR 0x%08X): not modelled", ch, kChanName[ch],
            mode == 2 ? "interleave" : "reserved", c.chcr);
    if (!dma_channel_routed(ch))
        die("DMAC ch%d (%s) started (CHCR 0x%08X MADR 0x%08X QWC %u TADR 0x%08X) with no data path installed", ch,
            kChanName[ch], c.chcr, c.madr, c.qwc, c.tadr);
    if (mode == 1 && ch == 3) die("DMAC ch3 (fromIPU) started in chain mode: not modelled");
    if (census_) {
        ++census_->dma_starts[static_cast<unsigned>(ch)];
        if (mode == 1) ++census_->dma_chain_starts[static_cast<unsigned>(ch)];
    }
    c.active = true;
    c.stalled = false;
    c.device_driven = false;
    c.qw_total = 0;
    c.tag = 0;
    if (mode == 0) {
        c.phase = DmaChan::Phase::Data;
        c.end_after = true;
    } else if (ch == 5) {
        // SIF0 is a destination chain fed by the IOP: tags arrive with the data, so the SIF module drives
        // the transfer and ends it with dma_complete(5) (README "DMAC").
        c.device_driven = true;
        return;
    } else if (ch == 8) {
        dma_spr_chain(ch);
        return;
    } else if (c.qwc) {
        // Resume of a suspended chain: finish the current block, then end if its tag ended the chain.
        const u32 id = (c.chcr >> 28) & 7u;
        c.phase = DmaChan::Phase::Data;
        c.end_after = id == 0 || id == 7 || ((c.chcr & kChcrTie) && (c.chcr & 0x80000000u));
        c.tag = static_cast<u64>(c.chcr & 0xFFFF0000u);
    } else {
        c.phase = DmaChan::Phase::NeedTag;
    }
    if (mode == 1 && ch == 9 && (c.chcr & kChcrTte)) die("DMAC ch9 (toSPR) chain with TTE: not modelled");
    dma_pump(ch);
}

void KernelHooks::dma_pump(int ch) {
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    if (c.in_pump) return;  // a data path re-entering its own channel: the outer pump continues
    const prof::Scope prof_zone(prof::Zone::Hw);
    c.in_pump = true;
    c.stalled = false;
    for (;;) {
        if (c.phase == DmaChan::Phase::NeedTag) {
            std::size_t room = 0;
            const u8* tp = dma_resolve(c.tadr, room);
            u64 tag = 0;
            std::memcpy(&tag, tp, 8);
            const u32 qwc = static_cast<u32>(tag & 0xFFFFu);
            const u32 id = static_cast<u32>(tag >> 28) & 7u;
            const bool irq = (tag >> 31) & 1u;
            const u32 addr = (static_cast<u32>(tag >> 32) & 0x7FFFFFF0u) | (static_cast<u32>(tag >> 63) << 31);
            if (c.chcr & kChcrTte) {  // tag qword delivered first, its DMAtag half zeroed (two VIF NOPs)
                std::memcpy(&c.tagqw, tp, 16);
                c.tagqw.u64[0] = 0;
            }
            c.chcr = (c.chcr & 0xFFFFu) | (static_cast<u32>(tag) & 0xFFFF0000u);
            c.qwc = qwc;
            c.tag = tag;
            const u32 data_after_tag = c.tadr + 16u;
            const u32 asp = (c.chcr >> 4) & 3u;
            c.end_after = false;
            switch (id) {
            case 0:  // refe: data at ADDR, then end
                c.madr = addr;
                c.tadr += 16u;
                c.end_after = true;
                break;
            case 1:  // cnt: data follows the tag, next tag follows the data
                c.madr = data_after_tag;
                c.tadr = data_after_tag + qwc * 16u;
                break;
            case 2:  // next: data follows the tag, next tag at ADDR
                c.madr = data_after_tag;
                c.tadr = addr;
                break;
            case 3:  // ref
            case 4:  // refs (stall control not modelled: D_CTRL.STS/STD trap at start)
                c.madr = addr;
                c.tadr += 16u;
                break;
            case 5:  // call: push the address after the data, next tag at ADDR
                if (asp >= 2) die("DMAC ch%d (%s): call tag at 0x%08X with ASR stack full", ch, kChanName[ch], c.tadr);
                c.madr = data_after_tag;
                (asp == 0 ? c.asr0 : c.asr1) = data_after_tag + qwc * 16u;
                c.chcr = (c.chcr & ~0x30u) | ((asp + 1u) << 4);
                c.tadr = addr;
                break;
            case 6:  // ret: pop, or end when the stack is empty
                c.madr = data_after_tag;
                if (asp > 0) {
                    c.tadr = (asp == 2 ? c.asr1 : c.asr0);
                    c.chcr = (c.chcr & ~0x30u) | ((asp - 1u) << 4);
                } else {
                    c.tadr = data_after_tag + qwc * 16u;
                    c.end_after = true;
                }
                break;
            default:  // 7 end: data follows the tag, then end
                c.madr = data_after_tag;
                c.tadr = data_after_tag + qwc * 16u;
                c.end_after = true;
                break;
            }
            if ((c.chcr & kChcrTie) && irq) c.end_after = true;
            c.phase = (c.chcr & kChcrTte) ? DmaChan::Phase::TagQw : DmaChan::Phase::Data;
            continue;
        }
        if (c.phase == DmaChan::Phase::TagQw) {
            const std::size_t got = dma_sink(ch, &c.tagqw, 1, c.tag);
            if (got > 1) die("DMAC ch%d (%s): data path consumed %zu of 1 qword", ch, kChanName[ch], got);
            if (got == 0) break;  // stalled on the tag qword
            ++c.qw_total;
            c.phase = DmaChan::Phase::Data;
            continue;
        }
        if (c.phase == DmaChan::Phase::Data) {
            bool stalled = false;
            while (c.qwc) {
                std::size_t room = 0;
                u8* p = dma_resolve(c.madr, room);
                const std::size_t n = std::min<std::size_t>(c.qwc, room);
                const std::size_t got = dma_sink(ch, reinterpret_cast<u128*>(p), n, c.tag);
                if (got > n) die("DMAC ch%d (%s): data path consumed %zu of %zu qwords", ch, kChanName[ch], got, n);
                c.madr += static_cast<u32>(got * 16u);
                c.qwc -= static_cast<u32>(got);
                c.qw_total += got;
                if (got < n) {
                    stalled = true;
                    break;
                }
            }
            if (stalled) break;
            if (c.end_after || ((c.chcr >> 2) & 3u) == 0) {
                dma_finish(ch);
                break;
            }
            c.phase = DmaChan::Phase::NeedTag;
            continue;
        }
        break;  // Done
    }
    c.in_pump = false;
    if (c.active && c.phase != DmaChan::Phase::Done) {
        c.stalled = true;
        if (census_) ++census_->dma_stalls[static_cast<unsigned>(ch)];
        dma_schedule_retry();
    }
}

// fromSPR destination chain: tags are read from the scratchpad stream at SADR (cnts 0 / cnt 1 / end 7),
// each giving the RAM destination (ADDR) of the QWC qwords that follow it.
void KernelHooks::dma_spr_chain(int ch) {
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    u8* spr = mem_.scratchpad();
    bool end = false;
    if (c.qwc) {  // resume: finish the current block first; its tag (CHCR.TAG) decides whether it ends
        const u32 id = (c.chcr >> 28) & 7u;
        end = id == 7 || ((c.chcr & kChcrTie) && (c.chcr & 0x80000000u));
    }
    for (int guard = 0; guard < 0x100000; ++guard) {
        if (c.qwc == 0 && !end) {
            u64 tag = 0;
            std::memcpy(&tag, spr + c.sadr, 8);
            c.sadr = (c.sadr + 16u) & kSprMask;
            const u32 id = static_cast<u32>(tag >> 28) & 7u;
            if (id != 0 && id != 1 && id != 7)
                die("DMAC ch8 (fromSPR) destination chain: tag id %u at SPR 0x%04X not modelled", id,
                    (c.sadr - 16u) & kSprMask);
            c.chcr = (c.chcr & 0xFFFFu) | (static_cast<u32>(tag) & 0xFFFF0000u);
            c.qwc = static_cast<u32>(tag & 0xFFFFu);
            c.madr = static_cast<u32>(tag >> 32) & 0x7FFFFFF0u;
            end = id == 7 || ((c.chcr & kChcrTie) && ((tag >> 31) & 1u));
        }
        while (c.qwc) {
            std::size_t room = 0;
            u8* dst = dma_resolve(c.madr, room);
            std::memcpy(dst, spr + c.sadr, 16);
            c.sadr = (c.sadr + 16u) & kSprMask;
            c.madr += 16u;
            --c.qwc;
            ++c.qw_total;
        }
        if (end) {
            dma_finish(ch);
            return;
        }
    }
    die("DMAC ch8 (fromSPR) destination chain did not end within 0x100000 tags");
}

void KernelHooks::dma_finish(int ch) {
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    c.phase = DmaChan::Phase::Done;
    c.stalled = false;
    if (census_) census_->dma_qwords[static_cast<unsigned>(ch)] += c.qw_total;
    schedule(kEvDma0 + ch, now() + opts_.dma_base_cycles + c.qw_total * opts_.dma_cycles_per_qword);
}

void KernelHooks::dma_complete_event(int ch) {
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    deadline_[static_cast<unsigned>(kEvDma0 + ch)] = kNever;
    if (!c.active) return;
    c.active = false;
    c.chcr &= ~kChcrStr;
    d_stat_ |= 1u << static_cast<unsigned>(ch);  // CIS; delivered when CIM is set (`15` §2.1)
    force_check();
}

void KernelHooks::dma_schedule_retry() {
    schedule(kEvDmaRetry, now() + std::max<u64>(1, opts_.dma_stall_retry_cycles));
}

// A data path that just became able to accept data (the GIF after VIF1's `MSKPATH3 off`) asks for the
// channel's transfer to proceed inside the window the guest opened, instead of at the next retry event.
void KernelHooks::retry_dma_now(int ch) {
    if (ch < 0 || ch >= 10) return;
    DmaChan& c = dch_[static_cast<unsigned>(ch)];
    if (c.active && c.stalled && !c.device_driven) dma_pump(ch);
}

void KernelHooks::dma_retry_event() {
    deadline_[kEvDmaRetry] = kNever;
    for (int ch = 0; ch < 10; ++ch) {
        DmaChan& c = dch_[static_cast<unsigned>(ch)];
        if (c.active && c.stalled) dma_pump(ch);
    }
}

} // namespace p3fes::hle
