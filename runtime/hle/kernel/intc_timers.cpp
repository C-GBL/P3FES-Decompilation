// Provenance: timer event/flag structure (count base + tick base, next compare/overflow, W1C flags) ported from snuri00/ps2-web-recomp @ c0f476e runtime/src/hw.cpp (MIT); see THIRD_PARTY.md.
// INTC (0x1000F000 INTC_STAT W1C, 0x1000F010 INTC_MASK toggle-on-1) and timers T0-T3
// (0x10000000 + n*0x800: COUNT +0, MODE +0x10, COMP +0x20, HOLD +0x30), driven from virtual time.
//
// Timer model (EE User's Manual timer chapter; the edge rule is inf): a 16-bit up-counter clocked by
// BUSCLK (EE/2), BUSCLK/16, BUSCLK/256 or H-BLANK (CLKS 0..3) while CUE is set. When the count becomes
// equal to COMP, EQUF sets (and with ZRET the count restarts at 0); when it wraps 0xFFFF -> 0, OVFF sets.
// An interrupt (cause 9 + n) is raised when EQUF/OVFF goes 0 -> 1 with CMPE/OVFE set; the flags are
// write-1-to-clear. GATE is not modelled and traps. Events are computed exactly from the cycle count:
// a read processes every compare/overflow that happened up to "now", and an INTC deadline is scheduled
// only when CMPE or OVFE could raise one.
#include "kernel_core.h"

#include <algorithm>

namespace p3fes::hle {

using namespace kc;

namespace {

constexpr u32 kIntcStat = 0x1000F000u, kIntcMask = 0x1000F010u;
constexpr u32 kModeClks = 3u, kModeGate = 1u << 2, kModeZret = 1u << 6, kModeCue = 1u << 7, kModeCmpe = 1u << 8,
              kModeOvfe = 1u << 9, kModeEquf = 1u << 10, kModeOvff = 1u << 11;

class IntcDev final : public HwDevice {
public:
    explicit IntcDev(KernelHooks& k) : k_(k) {}
    u32 read32(u32 pa) override { return k_.intc_read(pa); }
    void write32(u32 pa, u32 v) override { k_.intc_write(pa, v); }

private:
    KernelHooks& k_;
};

class TimerDev final : public HwDevice {
public:
    explicit TimerDev(KernelHooks& k) : k_(k) {}
    u32 read32(u32 pa) override { return k_.timer_read(pa); }
    void write32(u32 pa, u32 v) override { k_.timer_write(pa, v); }

private:
    KernelHooks& k_;
};

// Ticks to the next compare match and to the next overflow from count c (`comp == c` means the next
// match is a full wrap away: equality is detected when the count becomes equal, not on a write).
struct NextEvent {
    u64 step;
    bool cmp, ovf;
};
NextEvent next_timer_event(u32 c, u32 comp) {
    const u64 to_cmp = comp > c ? u64{comp - c} : u64{0x10000u - c + comp};
    const u64 to_ovf = 0x10000u - c;
    const u64 step = std::min(to_cmp, to_ovf);
    return {step, step == to_cmp, step == to_ovf};
}

} // namespace

std::unique_ptr<HwDevice> kc::make_intc_device(KernelHooks& k) { return std::make_unique<IntcDev>(k); }
std::unique_ptr<HwDevice> kc::make_timer_device(KernelHooks& k) { return std::make_unique<TimerDev>(k); }

// ---- INTC ----------------------------------------------------------------------------------------

u32 KernelHooks::intc_read(u32 pa) {
    if (pa == kIntcStat) return intc_stat_;
    if (pa == kIntcMask) return intc_mask_;
    report_unhandled(pa, 32, false, 0);
    return 0;
}

void KernelHooks::intc_write(u32 pa, u32 v) {
    if (pa == kIntcStat) {
        intc_stat_ &= ~(v & 0x7FFFu);
    } else if (pa == kIntcMask) {
        set_intc_mask(intc_mask_ ^ (v & 0x7FFFu));
    } else {
        report_unhandled(pa, 32, true, v);
        return;
    }
    force_check();
}

void KernelHooks::set_intc_mask(u32 new_mask) {
    if ((new_mask & ~intc_mask_) & (1u << 12))
        die("INTC cause 12 (TIM3) enabled; its dispatcher is the libkernel alarm patch (SetSyscall 0x12C -> 0x%08X), "
            "not modelled (H-18/H-20)",
            cause12_dispatcher_);
    intc_mask_ = new_mask;
    force_check();
}

// ---- timers --------------------------------------------------------------------------------------

u64 KernelHooks::timer_ticks(const Timer& t, u64 cycle) const {
    switch (t.mode & kModeClks) {
    case 0: return cycle / 2;     // BUSCLK = EE / 2
    case 1: return cycle / 32;    // BUSCLK / 16
    case 2: return cycle / 512;   // BUSCLK / 256
    default: return hlines_at(cycle);  // H-BLANK
    }
}

u64 KernelHooks::timer_tick_cycle(const Timer& t, u64 tick) const {
    switch (t.mode & kModeClks) {
    case 0: return tick * 2;
    case 1: return tick * 32;
    case 2: return tick * 512;
    default: return hline_start(tick);
    }
}

u32 KernelHooks::timer_count(int n, u64 cycle) const {
    const Timer& t = timers_[static_cast<unsigned>(n)];
    if (!(t.mode & kModeCue)) return t.count_base;
    const u64 ticks = timer_ticks(t, cycle);
    return static_cast<u32>((t.count_base + (ticks - t.tick_base)) & 0xFFFFu);
}

void KernelHooks::timer_advance(int n, u64 cycle) {
    Timer& t = timers_[static_cast<unsigned>(n)];
    if (!(t.mode & kModeCue)) return;
    const u64 target = timer_ticks(t, cycle);
    for (;;) {
        const NextEvent e = next_timer_event(t.count_base, t.comp);
        if (t.tick_base + e.step > target) return;
        u32 c = static_cast<u32>((t.count_base + e.step) & 0xFFFFu);
        if (e.cmp) {
            if (!(t.mode & kModeEquf)) {
                t.mode |= kModeEquf;
                if (t.mode & kModeCmpe) raise_intc(9u + static_cast<unsigned>(n));
            }
            if (t.mode & kModeZret) c = 0;
        }
        if (e.ovf && !(t.mode & kModeOvff)) {
            t.mode |= kModeOvff;
            if (t.mode & kModeOvfe) raise_intc(9u + static_cast<unsigned>(n));
        }
        t.count_base = c;
        t.tick_base += e.step;
    }
}

void KernelHooks::timer_reschedule(int n) {
    const Timer& t = timers_[static_cast<unsigned>(n)];
    const unsigned ev = static_cast<unsigned>(kEvTimer0 + n);
    if (!(t.mode & kModeCue) || !(t.mode & (kModeCmpe | kModeOvfe))) {
        deadline_[ev] = kNever;
        return;
    }
    const NextEvent e = next_timer_event(t.count_base, t.comp);
    schedule(static_cast<int>(ev), timer_tick_cycle(t, t.tick_base + e.step));
}

void KernelHooks::timer_event(int n) {
    deadline_[static_cast<unsigned>(kEvTimer0 + n)] = kNever;
    timer_advance(n, now());
    timer_reschedule(n);
}

u32 KernelHooks::timer_read(u32 pa) {
    const int n = static_cast<int>((pa >> 11) & 3u);
    const Timer& t = timers_[static_cast<unsigned>(n)];
    switch (pa & 0x7FFu) {
    case 0x00: timer_advance(n, now()); return timer_count(n, now());
    case 0x10: timer_advance(n, now()); return t.mode;
    case 0x20: return t.comp;
    case 0x30: return t.hold;
    default: break;
    }
    report_unhandled(pa, 32, false, 0);
    return 0;
}

void KernelHooks::timer_write(u32 pa, u32 v) {
    const int n = static_cast<int>((pa >> 11) & 3u);
    Timer& t = timers_[static_cast<unsigned>(n)];
    const u32 reg = pa & 0x7FFu;
    if (reg != 0x00 && reg != 0x10 && reg != 0x20 && reg != 0x30) {
        report_unhandled(pa, 32, true, v);
        return;
    }
    if (reg == 0x30) {  // HOLD: plain storage (T0/T1 SBUS capture; unused)
        t.hold = v & 0xFFFFu;
        return;
    }
    // Every write re-anchors the counter at "now" after processing what happened before it.
    timer_advance(n, now());
    u32 count = timer_count(n, now());
    switch (reg) {
    case 0x00: count = v & 0xFFFFu; break;
    case 0x10:
        if (v & kModeGate) die("T%d_MODE = 0x%X: GATE is not modelled (no game use found)", n, v);
        t.mode = (t.mode & (kModeEquf | kModeOvff) & ~(v & (kModeEquf | kModeOvff))) | (v & 0x3FFu);
        break;
    default: t.comp = v & 0xFFFFu; break;
    }
    t.count_base = count;
    t.tick_base = timer_ticks(t, now());
    timer_reschedule(n);
    force_check();
}

} // namespace p3fes::hle
