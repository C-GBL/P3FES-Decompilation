// Provenance: VBLANK_END = VBLANK_START + 22 H-lines taken from snuri00/ps2-web-recomp @ c0f476e runtime/src/hw.cpp vblank_start (MIT); see THIRD_PARTY.md.
// HwBus implementation (range map, width-exact dispatch, unhandled-access log) and the virtual time
// base / event loop (ADR-0013 §2). The `check_events` fast path is inline in kernel_core.h.
#include "kernel_core.h"

#include <algorithm>

namespace p3fes::hle {

using namespace kc;

namespace {
constexpr u32 kEeBase = EEMemory::kHwRegBase, kEeSize = EEMemory::kHwRegSize;
constexpr u32 kGsBase = EEMemory::kGsPrivBase, kGsSize = EEMemory::kGsPrivSize;
} // namespace

// ---- range map ---------------------------------------------------------------------------------

bool KernelHooks::try_map(u32 b, u32 e, HwDevice* dev) {
    if (!dev || b >= e || (b & 15u) || (e & 15u)) return false;
    HwDevice** slots = nullptr;
    u32 base = 0;
    if (b - kEeBase < kEeSize && e - kEeBase <= kEeSize) {
        slots = ee_slots_.data();
        base = kEeBase;
    } else if (b - kGsBase < kGsSize && e - kGsBase <= kGsSize) {
        slots = gs_slots_.data();
        base = kGsBase;
    } else {
        return false;
    }
    for (u32 a = b; a < e; a += 16)
        if (slots[(a - base) >> 4]) return false;  // overlap: refuse, change nothing
    for (u32 a = b; a < e; a += 16) slots[(a - base) >> 4] = dev;
    return true;
}

void KernelHooks::map(u32 b, u32 e, HwDevice* dev) {
    if (!try_map(b, e, dev))
        die("HwBus::map(0x%08X, 0x%08X) refused: misaligned, outside the EE/GS register windows, or overlapping",
            b, e);
}

HwDevice* KernelHooks::device_at(u32 pa) const {
    if (pa - kEeBase < kEeSize) return ee_slots_[(pa - kEeBase) >> 4];
    if (pa - kGsBase < kGsSize) return gs_slots_[(pa - kGsBase) >> 4];
    return nullptr;
}

void KernelHooks::report_unhandled(u32 pa, u32 width, bool write, u64 value) {
    UnhandledAccess& a = unhandled_.e[unhandled_.total % unhandled_.e.size()];
    a.pa = pa;
    a.width = width;
    a.write = write;
    a.value = value;
    a.pc = ctx_.pc;
    ++unhandled_.total;
}

std::vector<UnhandledAccess> KernelHooks::unhandled_log() const {
    std::vector<UnhandledAccess> out;
    const u64 n = std::min<u64>(unhandled_.total, unhandled_.e.size());
    out.reserve(static_cast<std::size_t>(n));
    for (u64 i = unhandled_.total - n; i < unhandled_.total; ++i) out.push_back(unhandled_.e[i % unhandled_.e.size()]);
    return out;
}

void KernelHooks::set_dma_handler(unsigned ch, DmaChannelHandler* h) {
    if (ch >= 10) die("set_dma_handler: channel %u out of range", ch);
    if (ch == 8 || ch == 9) die("set_dma_handler: channel %u (SPR) is performed by the kernel", ch);
    dma_handlers_[ch] = h;
}

// ---- width-exact dispatch (the bus never splits or merges an access) ---------------------------

u32 KernelHooks::read32(u32 pa) {
    if (census_) census_bus(pa, false);
    if (HwDevice* d = device_at(pa)) return d->read32(pa);
    report_unhandled(pa, 32, false, 0);
    return 0;
}
void KernelHooks::write32(u32 pa, u32 v) {
    if (census_) census_bus(pa, true);
    if (HwDevice* d = device_at(pa)) return d->write32(pa, v);
    report_unhandled(pa, 32, true, v);
}
u64 KernelHooks::read64(u32 pa) {
    if (census_) census_bus(pa, false);
    if (HwDevice* d = device_at(pa)) return d->read64(pa);
    report_unhandled(pa, 64, false, 0);
    return 0;
}
void KernelHooks::write64(u32 pa, u64 v) {
    if (census_) census_bus(pa, true);
    if (HwDevice* d = device_at(pa)) return d->write64(pa, v);
    report_unhandled(pa, 64, true, v);
}
u128 KernelHooks::read128(u32 pa) {
    if (census_) census_bus(pa, false);
    if (HwDevice* d = device_at(pa)) return d->read128(pa);
    report_unhandled(pa, 128, false, 0);
    return u128{};
}
void KernelHooks::write128(u32 pa, const u128& v) {
    if (census_) census_bus(pa, true);
    if (HwDevice* d = device_at(pa)) return d->write128(pa, v);
    report_unhandled(pa, 128, true, v.lo());
}
u8 KernelHooks::read8(u32 pa) {
    if (census_) census_bus(pa, false);
    if (HwDevice* d = device_at(pa)) return d->read8(pa);
    report_unhandled(pa, 8, false, 0);
    return 0;
}
u16 KernelHooks::read16(u32 pa) {
    if (census_) census_bus(pa, false);
    if (HwDevice* d = device_at(pa)) return d->read16(pa);
    report_unhandled(pa, 16, false, 0);
    return 0;
}
void KernelHooks::write8(u32 pa, u8 v) {
    if (census_) census_bus(pa, true);
    if (HwDevice* d = device_at(pa)) return d->write8(pa, v);
    report_unhandled(pa, 8, true, v);
}
void KernelHooks::write16(u32 pa, u16 v) {
    if (census_) census_bus(pa, true);
    if (HwDevice* d = device_at(pa)) return d->write16(pa, v);
    report_unhandled(pa, 16, true, v);
}

// ---- interrupt sources -------------------------------------------------------------------------

void KernelHooks::raise_intc(unsigned cause) {
    if (cause >= 15) die("raise_intc(%u): no such INTC cause", cause);
    // H-18/H-20: the game replaced the cause-12 dispatcher (SetSyscall 0x12C) with the never-analysed
    // alarm payload; nothing in the game arms T3. A pending cause 12 means the analysis missed a path.
    if (cause == 12)
        die("INTC cause 12 (TIM3) became pending; the cause-12 dispatcher is the libkernel alarm patch (0x%08X), not modelled (H-18/H-20)",
            cause12_dispatcher_);
    intc_stat_ |= 1u << cause;
    force_check();
}

void KernelHooks::dma_complete(unsigned ch) {
    if (ch >= 10) die("dma_complete(%u): no such DMAC channel", ch);
    DmaChan& c = dch_[ch];
    if (c.active) {
        // A device-driven channel (SIF0 destination chain) or a device finishing a transfer early.
        c.active = c.stalled = c.device_driven = false;
        c.phase = DmaChan::Phase::Done;
        c.chcr &= ~0x100u;
        deadline_[static_cast<unsigned>(kEvDma0) + ch] = kNever;
    }
    d_stat_ |= 1u << ch;
    force_check();
}

// ---- time base ----------------------------------------------------------------------------------

const Timebase& KernelHooks::time() const {
    tb_.cycles = ctx_.cycles;
    tb_.hlines = hlines_at(ctx_.cycles);
    return tb_;  // field / vblanks change only when VBLANK_START is processed
}

void KernelHooks::vblank_start_event() {
    const u64 at = deadline_[kEvVblankStart];
    ++vblank_index_;
    if (census_) ++census_->vblanks;
    tb_.field ^= 1u;  // GS CSR.FIELD toggles at every VBLANK_START (the GS device reports tb_.field)
    tb_.vblanks = vblank_index_;
    raise_intc(2);
    schedule(kEvVblankEnd, at + (kVblankLines * kHlineNum + kHlineDen - 1) / kHlineDen);
    deadline_[kEvVblankStart] = kNever;
    schedule(kEvVblankStart, vblank_start_cycle(vblank_index_ + 1));
    run_services();  // per-vblank device work (PADMAN frames), before the cause-2 handlers run
}

// Device services (Kernel::add_device_service): run all, then schedule the earliest deadline they return
// as the kEvService event. Not re-entered (a service that reaches the kernel again is served by the outer
// pass's result).
void KernelHooks::run_services() {
    if (in_services_ || services_.empty()) return;
    in_services_ = true;
    if (census_) ++census_->services;
    deadline_[kEvService] = kNever;
    u64 next = kNever;
    for (DeviceServiceFn& s : services_) next = std::min(next, s());
    in_services_ = false;
    if (next != kNever) schedule(kEvService, std::max(next, ctx_.cycles + 1));
}

void KernelHooks::vblank_end_event() {
    deadline_[kEvVblankEnd] = kNever;
    raise_intc(3);  // unused by the game, but the bit appears (H-44 / §5.5)
}

void KernelHooks::process_due_events(u64 t) {
    for (;;) {
        int ev = -1;
        u64 best = kNever;
        for (int i = 0; i < kEvCount; ++i) {
            const u64 d = deadline_[static_cast<unsigned>(i)];
            if (d <= t && d < best) {
                best = d;
                ev = i;
            }
        }
        if (ev < 0) return;
        ++events_processed_;
        if (ev == kEvVblankStart) vblank_start_event();
        else if (ev == kEvVblankEnd) vblank_end_event();
        else if (ev >= kEvTimer0 && ev < kEvTimer0 + 4) timer_event(ev - kEvTimer0);
        else if (ev >= kEvDma0 && ev < kEvDma0 + 10) dma_complete_event(ev - kEvDma0);
        else if (ev == kEvDmaRetry) dma_retry_event();
        else run_services();
    }
}

void KernelHooks::recompute_deadline(const EEContext& ctx) {
    u64 d = kNever;
    for (u64 v : deadline_) d = std::min(d, v);
    if ((stop_ || stop_requested_) && no_deliver_depth_ == 0) d = 0;  // run_until: every thread-level check point tests the predicate
    if ((dmac_pending() || intc_pending()) && no_deliver_depth_ == 0 && current_ != kIdleTid &&
        !cpu_can_deliver(ctx)) {
        d = std::min(d, ctx.cycles + std::max<u64>(1, opts_.masked_poll_cycles));
        if (census_) ++census_->masked_polls;
    }
    next_deadline_ = d;
}

// Slow path of a check point: advance the time base, deliver interrupts (one cause per delivery,
// highest first, re-tested after each chain as the kernel's eret would re-interrupt), take a
// preemption flagged by i* calls inside a chain, test the run_until predicate.
void KernelHooks::slow_check(EEContext& ctx) {
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Kernel);  // explicit pair: may switch fibers (L3)
    if (census_) ++census_->slow_checks;
    process_due_events(ctx.cycles);
    if (no_deliver_depth_ == 0 && current_ != kIdleTid && started_) {
        // A stop requested by a time-base event or device service is taken before this point delivers.
        if (stop_requested_) take_stop("stopped by request");
        while (cpu_can_deliver(ctx) && deliver_one()) {
            process_due_events(ctx.cycles);
            if (need_resched_) {
                need_resched_ = false;
                // Interrupt exit with g_kNeedResched (0x80000454 -> 0x8000363C): the interrupted context is saved
                // on its own stack before the pick.
                if (opts_.context_frames) frame_save(current_, ctx, ctx.gpr[GPR_V0]);
                if (census_) ++census_->preemptions;
                reschedule();  // the interrupted thread stays READY at the head of its queue
            }
        }
        if (stop_requested_) take_stop("stopped by request");
        if (stop_ && stop_()) switch_to_host(RunStatus::Stopped, "stopped by run_until predicate");
    }
    recompute_deadline(ctx);
    prof::leave(prof_zone);
}

void KernelHooks::take_stop(const char* where) {
    stop_requested_ = false;
    switch_to_host(RunStatus::Stopped, where);
}

} // namespace p3fes::hle
