// GS privileged registers (physical 0x12000000-0x12001FFF, 64-bit accesses; contract H-30, docs/ANALYSIS/10 §2.5,
// §2.7, §2.10, §3.1). Owns CSR/IMR/BUSDIR/SIGLBLID, the display registers the CRTC reads, and the flip counter
// the host loop and the snapshot harness use (ADR-0013 §4).
//
// CSR.FIELD is the time base's field (`HwBus::time().field`, toggled by the kernel/timing owner at VBLANK_START);
// VSINT/HSINT are derived from the time base's vblank / H-line counts (set when the count advanced since the
// last write-1-to-clear). SIGNAL/FINISH raise INTC cause 0 when IMR leaves them unmasked.
//
// Revision: CSR.ID = 0x55, CSR.REV = 0x1B — the value PCSX2 2.8.2 reports to this game (observed: the game stores
// CSR[23:16] at GParam+6 = 0x77F286 in sceGsResetGraph 0x4F8F58; PCSX2's first_flip eeMemory.bin holds 0x001B
// there). Contract Q-03/H-23 consequence: see runtime/gs/README.md "Revision".
#pragma once

#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_pipe.h"
#include "p3fes/hle/hw_bus.h"

#include <functional>

namespace p3fes::gs {

inline constexpr u8 kGsId = 0x55;
inline constexpr u8 kGsRevision = 0x1B;

// The registers the CRTC composes from (GS User's Manual §8), captured by value.
struct DisplayRegs {
    u64 pmode = 0, smode1 = 0, smode2 = 0, dispfb[2] = {0, 0}, display[2] = {0, 0}, bgcolor = 0;
};

struct FlipEvent {
    u64 count = 0;       // flip_count() after this event
    u32 circuit = 0;     // 0 = DISPFB1, 1 = DISPFB2 (the write that triggered the event)
    u32 fbp = 0;         // FBP (2048-word pages) written
    u64 vblank = 0;      // Timebase::vblanks at the event
};

struct GsPrivStats {
    u64 unhandled_reads = 0;
    u64 unhandled_writes = 0;
    u64 resets = 0;
    u64 signals = 0;
    u64 finishes = 0;
    u64 labels = 0;
    u64 dispfb_writes = 0;
    // EE reads per register (diagnostics; docs/ANALYSIS/25 census): index = offset >> 4 for 0x000-0x0F0
    // (PMODE..BGCOLOR), 16 + ((offset - 0x1000) >> 4) for CSR (16), IMR (17), BUSDIR (20), SIGLBLID (24).
    u64 reads[32] = {};
};

class GsPrivRegs final : public hle::HwDevice, public IGsEvents {
public:
    static constexpr u32 kBase = 0x12000000u;
    static constexpr u32 kEnd = 0x12002000u;

    explicit GsPrivRegs(GsCore& core, hle::HwBus* bus = nullptr) : core_(core), bus_(bus) {}

    void set_bus(hle::HwBus* bus) noexcept { bus_ = bus; }
    // Threaded pipeline (gs_pipeline.h): CSR, SIGLBLID and IMR are where the EE can observe GS events, so every access
    // to them waits for the VU1 stage (GsPipe::sync_vu; a CSR.RESET write waits for every stage). nullptr = off.
    void set_pipe(GsPipe* p) noexcept { pipe_ = p; }

    // HwDevice: 64-bit is the native width; 32-bit accesses read/modify one half.
    u64 read64(u32 pa) override;
    void write64(u32 pa, u64 v) override;
    u32 read32(u32 pa) override;
    void write32(u32 pa, u32 v) override;

    // IGsEvents (GsCore SIGNAL / FINISH / LABEL register writes).
    void on_signal(u32 id, u32 mask) override;
    void on_finish() override;
    void on_label(u32 id, u32 mask) override;

    DisplayRegs display() const noexcept { return disp_; }
    u64 csr_flags() const noexcept { return csr_flags_; }
    u64 imr() const noexcept { return imr_; }
    u64 busdir() const noexcept { return busdir_; }
    // BUSDIR as the GIF (GIF_STAT.DIR) and VIF1 (VIF1_STAT.FDR, channel-1 direction) read it.
    const u64* busdir_source() const noexcept { return &busdir_; }
    u64 siglblid() const noexcept { return siglblid_; }

    // Flip detection: a DISPFB1/DISPFB2 write whose FBP differs from that circuit's previous FBP, or the first
    // DISPFB write after an SMODE2 write, is a flip event. Events within one vblank interval (same
    // Timebase::vblanks) coalesce into one, because the CRTC can show at most one new buffer per field and RW's
    // handler writes both circuits back to back (docs/ANALYSIS/10 §3.1).
    u64 flip_count() const noexcept { return flips_; }
    const FlipEvent& last_flip() const noexcept { return last_flip_; }
    void set_flip_callback(std::function<void(const FlipEvent&)> cb) { flip_cb_ = std::move(cb); }

    const GsPrivStats& stats() const noexcept { return stats_; }

    void state(StateIo& io);  // machine state (gs_state.cpp)

private:
    const hle::Timebase* time() const noexcept { return bus_ ? &bus_->time() : nullptr; }
    void raise_if_unmasked(u32 flag_bit);
    void dispfb_written(u32 circuit, u64 v);

    GsCore& core_;
    hle::HwBus* bus_;
    GsPipe* pipe_ = nullptr;
    DisplayRegs disp_{};
    u64 srfsh_ = 0, synch1_ = 0, synch2_ = 0, syncv_ = 0, extbuf_ = 0, extdata_ = 0, extwrite_ = 0;
    u64 csr_flags_ = 0;  // SIGNAL(0) FINISH(1) EDWINT(4); HSINT/VSINT are derived
    u64 imr_ = 0x7F00u;  // all GS interrupts masked after reset
    u64 busdir_ = 0;
    u64 siglblid_ = 0;
    u64 vsint_ack_ = 0;  // Timebase::vblanks at the last VSINT clear
    u64 hsint_ack_ = 0;  // Timebase::hlines at the last HSINT clear
    bool smode2_armed_ = false;
    u64 flips_ = 0;
    u64 last_flip_vblank_ = ~0ull;
    FlipEvent last_flip_{};
    std::function<void(const FlipEvent&)> flip_cb_;
    GsPrivStats stats_{};
};

} // namespace p3fes::gs
