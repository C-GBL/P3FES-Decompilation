// GS privileged registers (GS User's Manual §8; values the game writes: docs/ANALYSIS/10 §2.5-2.13, §3.1).
#include "p3fes/gs/gs_priv.h"
#include "p3fes/prof.h"

namespace p3fes::gs {

namespace {
constexpr u64 kCsrSignal = 1u << 0, kCsrFinish = 1u << 1, kCsrHsint = 1u << 2, kCsrVsint = 1u << 3,
              kCsrEdwint = 1u << 4, kCsrReset = 1u << 9;
constexpr u64 kCsrFifoEmpty = 1u << 14;
} // namespace

u64 GsPrivRegs::read64(u32 pa) {
    const u32 off = pa - kBase;
    if ((off & 0xFu) != 0) {
        ++stats_.unhandled_reads;
        return 0;
    }
    if (off < 0x100u) ++stats_.reads[off >> 4];
    else if (off >= 0x1000u && off < 0x1100u) ++stats_.reads[16u + ((off - 0x1000u) >> 4)];
    // Threaded pipeline: the SIGNAL / FINISH / LABEL writes of PATH1 packets in flight must have landed.
    if (pipe_ && (off == priv::CSR || off == priv::SIGLBLID))
        pipe_->sync_vu(off == priv::CSR ? SyncWhy::CsrRead : SyncWhy::SiglblidRead);
    const hle::Timebase* t = time();
    switch (off) {
    case priv::PMODE: return disp_.pmode;
    case priv::SMODE1: return disp_.smode1;
    case priv::SMODE2: return disp_.smode2;
    case priv::SRFSH: return srfsh_;
    case priv::SYNCH1: return synch1_;
    case priv::SYNCH2: return synch2_;
    case priv::SYNCV: return syncv_;
    case priv::DISPFB1: return disp_.dispfb[0];
    case priv::DISPLAY1: return disp_.display[0];
    case priv::DISPFB2: return disp_.dispfb[1];
    case priv::DISPLAY2: return disp_.display[1];
    case priv::EXTBUF: return extbuf_;
    case priv::EXTDATA: return extdata_;
    case priv::EXTWRITE: return extwrite_;
    case priv::BGCOLOR: return disp_.bgcolor;
    case priv::CSR: {
        u64 v = csr_flags_ & (kCsrSignal | kCsrFinish | kCsrEdwint);
        if (t && t->hlines > hsint_ack_) v |= kCsrHsint;
        if (t && t->vblanks > vsint_ack_) v |= kCsrVsint;
        const u64 field = t ? (t->field & 1u) : 0u;
        v |= field << 13;  // FIELD
        v |= field << 12;  // NFIELD (modelled equal to FIELD; unverified)
        v |= kCsrFifoEmpty; // the synchronous GIF never holds data in the GS FIFO
        v |= static_cast<u64>(kGsRevision) << 16;
        v |= static_cast<u64>(kGsId) << 24;
        return v;
    }
    case priv::IMR: return imr_;
    case priv::BUSDIR: return busdir_;
    case priv::SIGLBLID: return siglblid_;
    default: ++stats_.unhandled_reads; return 0;
    }
}

void GsPrivRegs::write64(u32 pa, u64 v) {
    const u32 off = pa - kBase;
    if ((off & 0xFu) != 0) {
        ++stats_.unhandled_writes;
        return;
    }
    if (pipe_ && (off == priv::CSR || off == priv::IMR || off == priv::SIGLBLID)) {
        // CSR.RESET: core_.reset() below touches the GS stage's state, so every stage must be idle.
        if (off == priv::CSR && (v & kCsrReset)) pipe_->drain(SyncWhy::CsrReset);
        else pipe_->sync_vu(SyncWhy::PrivWrite);
    }
    switch (off) {
    case priv::PMODE: disp_.pmode = v; break;
    case priv::SMODE1: disp_.smode1 = v; break;
    case priv::SMODE2:
        disp_.smode2 = v;
        smode2_armed_ = true;
        break;
    case priv::SRFSH: srfsh_ = v; break;
    case priv::SYNCH1: synch1_ = v; break;
    case priv::SYNCH2: synch2_ = v; break;
    case priv::SYNCV: syncv_ = v; break;
    case priv::DISPFB1: dispfb_written(0, v); break;
    case priv::DISPLAY1: disp_.display[0] = v; break;
    case priv::DISPFB2: dispfb_written(1, v); break;
    case priv::DISPLAY2: disp_.display[1] = v; break;
    case priv::EXTBUF: extbuf_ = v; break;
    case priv::EXTDATA: extdata_ = v; break;
    case priv::EXTWRITE: extwrite_ = v; break;
    case priv::BGCOLOR: disp_.bgcolor = v; break;
    case priv::CSR: {
        csr_flags_ &= ~(v & (kCsrSignal | kCsrFinish | kCsrEdwint));
        if (const hle::Timebase* t = time()) {
            if (v & kCsrHsint) hsint_ack_ = t->hlines;
            if (v & kCsrVsint) vsint_ack_ = t->vblanks;
        }
        if (v & kCsrReset) {
            ++stats_.resets;
            core_.reset();
            csr_flags_ = 0;
        }
        break; // FLUSH (bit 8): nothing is buffered
    }
    case priv::IMR:
        imr_ = v & 0x7F00u;
        for (u32 bit = 0; bit < 5; ++bit) {
            if ((csr_flags_ >> bit) & 1u) raise_if_unmasked(bit);
        }
        break;
    case priv::BUSDIR: busdir_ = v & 1u; break;
    case priv::SIGLBLID: siglblid_ = v; break;
    default: ++stats_.unhandled_writes; break;
    }
}

u32 GsPrivRegs::read32(u32 pa) {
    const u64 v = read64(pa & ~7u);
    return static_cast<u32>((pa & 4u) ? v >> 32 : v);
}

void GsPrivRegs::write32(u32 pa, u32 v) {
    const u32 base = pa & ~7u;
    const u32 off = base - kBase;
    if (off == priv::CSR) {
        // CSR's low half carries the W1C flags, FLUSH and RESET; its high half is read-only (REV/ID).
        if (!(pa & 4u)) write64(base, v);
        return;
    }
    const u64 old = read64(base);
    write64(base, (pa & 4u) ? ((old & 0xFFFFFFFFull) | (static_cast<u64>(v) << 32)) : ((old & ~0xFFFFFFFFull) | v));
}

void GsPrivRegs::raise_if_unmasked(u32 flag_bit) {
    if (!((imr_ >> (8u + flag_bit)) & 1u) && bus_) bus_->raise_intc(0); // INTC cause 0 = GS
}

void GsPrivRegs::on_signal(u32 id, u32 mask) {
    ++stats_.signals;
    prof::gs_event(0);
    siglblid_ = (siglblid_ & ~static_cast<u64>(mask)) | (id & mask);
    csr_flags_ |= kCsrSignal;
    raise_if_unmasked(0);
}

void GsPrivRegs::on_finish() {
    ++stats_.finishes;
    prof::gs_event(1);
    csr_flags_ |= kCsrFinish;
    raise_if_unmasked(1);
}

void GsPrivRegs::on_label(u32 id, u32 mask) {
    ++stats_.labels;
    prof::gs_event(2);
    const u64 lbl = ((siglblid_ >> 32) & ~static_cast<u64>(mask)) | (id & mask);
    siglblid_ = (siglblid_ & 0xFFFFFFFFull) | (lbl << 32);
}

void GsPrivRegs::dispfb_written(u32 circuit, u64 v) {
    ++stats_.dispfb_writes;
    const u32 old_fbp = bits(disp_.dispfb[circuit], 0, 9);
    disp_.dispfb[circuit] = v;
    const u32 fbp = bits(v, 0, 9);
    const bool event = smode2_armed_ || fbp != old_fbp;
    smode2_armed_ = false;
    if (!event) return;
    const hle::Timebase* t = time();
    const u64 vb = t ? t->vblanks : 0;
    if (t && vb == last_flip_vblank_) return; // same vblank interval: already counted
    last_flip_vblank_ = vb;
    ++flips_;
    last_flip_ = FlipEvent{flips_, circuit, fbp, vb};
    if (flip_cb_) flip_cb_(last_flip_);
}

} // namespace p3fes::gs
