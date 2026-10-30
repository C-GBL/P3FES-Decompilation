// Machine state of the kernel (runtime/STATE.md): the time base and events, INTC / timers / DMAC, the handler
// chains, threads and semaphores, the installed-syscall table, the live EEContext, and every live guest-thread
// fiber with its host stack. Wiring (devices, DMA handlers, host syscalls, services, sinks) is not saved: the
// loading process builds and wires the same kernel first.
//
// Fibers: each guest thread's host stack holds its recompiled call chain. With the pinned regions enabled
// (p3fes/pinned.h) a fiber is a fixed stack slot and the objects its frames point at (this KernelHooks, the
// EEContext, guest RAM) sit at fixed addresses, so the bytes [rsp, top) of each slot plus its saved rsp resume
// in another process running the same executable. The executable identity is the caller's check (the state
// file header records its hash and image base).
#include "kernel_core.h"

#include <windows.h>

#include <cstdio>
#include <cstdlib>

namespace p3fes::hle {

using namespace kc;

namespace {

// P3FES_STATE_AUDIT=1: classify every qword of a saved fiber stack that looks like a host address. Values into the
// executable image, the pinned regions or the stack itself survive a reload; one into the heap or another module
// would not if a frame still used it (a stale slot is harmless, so this is a diagnostic, not a check).
void audit_stack(int slot, std::uint64_t rsp, std::uint64_t hi) {
    const auto exe = reinterpret_cast<std::uint64_t>(GetModuleHandleW(nullptr));
    std::size_t image = 0, pinned_hits = 0, self = 0, heap = 0, other = 0;
    for (std::uint64_t a = rsp; a + 8 <= hi; a += 8) {
        const std::uint64_t v = *reinterpret_cast<const std::uint64_t*>(a);
        if (v < 0x10000ull || v > 0x00007FFFFFFFFFFFull) continue;
        if (v >= rsp - 0x100000ull && v < hi) { ++self; continue; }
        if (pinned::owns(reinterpret_cast<const void*>(v)) ||
            (v >= pinned::kFiberBase && v < pinned::kFiberBase + pinned::kFiberSlots * pinned::kFiberSlotStride)) {
            ++pinned_hits;
            continue;
        }
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(reinterpret_cast<const void*>(v), &mbi, sizeof mbi) || mbi.State != MEM_COMMIT) continue;
        if (mbi.Type == MEM_IMAGE) {
            if (reinterpret_cast<std::uint64_t>(mbi.AllocationBase) == exe) {
                ++image;
                if (std::getenv("P3FES_STATE_AUDIT")[0] == '2')
                    std::fprintf(stderr, "p3fes: state audit: slot %d  [rsp+0x%llx] = exe+0x%llx\n", slot,
                                 static_cast<unsigned long long>(a - rsp), static_cast<unsigned long long>(v - exe));
            } else {
                ++other;
            }
            continue;
        }
        if (mbi.Type == MEM_PRIVATE) {
            ++heap;
            std::fprintf(stderr, "p3fes: state audit: slot %d  [rsp+0x%llx] = 0x%llx (private memory)\n", slot,
                         static_cast<unsigned long long>(a - rsp), static_cast<unsigned long long>(v));
        } else {
            ++other;
        }
    }
    std::fprintf(stderr, "p3fes: state audit: slot %d, %llu bytes: image %zu, pinned %zu, own stack %zu, private %zu, other %zu\n",
                 slot, static_cast<unsigned long long>(hi - rsp), image, pinned_hits, self, heap, other);
}

void tcb_io(StateIo& io, Tcb& t, int& fiber_slot) {
    io(t.status, t.entry, t.stack, t.stack_size, t.gp, t.root, t.attr, t.option, t.heap_end);
    io(t.init_prio, t.cur_prio, t.wait_type, t.wait_id, t.wakeup_count, t.arg, t.q_prev, t.q_next, t.queued);
    // The main thread's host entry: a function of this executable (fixed image base), stored as its address.
    std::uint64_t entry = reinterpret_cast<std::uint64_t>(t.host_entry);
    io(entry);
    t.host_entry = reinterpret_cast<GuestFn>(entry);
    io(t.frame, t.start_from_frame, fiber_slot);
    EEMemory* const m = t.saved.memory;
    io.raw(&t.saved, sizeof t.saved);
    t.saved.memory = m;
}

} // namespace

bool KernelHooks::state(StateIo& io) {
    io.section("kernel");
    if (io.saving()) {
        if (!pinned::enabled()) {
            io.fail("kernel: the pinned regions are not enabled (machine states need them before the kernel is built)");
            return false;
        }
        if (!started_ || dead_ || cur_fiber_ != &host_fiber_ || !resume_fiber_ || last_.status != RunStatus::Stopped) {
            io.fail("kernel: not stopped between run slices (save after a Stopped run_until, on the host side)");
            return false;
        }
        if (in_services_ || no_deliver_depth_ != 0) {
            io.fail("kernel: stopped inside a service or a handler chain");
            return false;
        }
    } else {
        if (started_ || cur_fiber_ != &host_fiber_) {
            io.fail("kernel: loading needs a kernel that was never started");
            return false;
        }
        if (!pinned::enabled()) {
            io.fail("kernel: the pinned regions are not enabled in this process");
            return false;
        }
    }
    io.expect(static_cast<std::uint64_t>(sizeof(Tcb)), "Tcb layout");
    io.expect(static_cast<std::uint64_t>(sizeof(EEContext)), "EEContext layout");
    io.expect(reinterpret_cast<std::uint64_t>(this), "kernel object address (pinned arena)");
    io.expect(reinterpret_cast<std::uint64_t>(&ctx_), "EEContext address (pinned arena)");
    io.expect(reinterpret_cast<std::uint64_t>(mem_.main_ram()), "guest RAM address (pinned arena)");

    // The live CPU context.
    {
        EEMemory* const m = ctx_.memory;
        io.raw(&ctx_, sizeof ctx_);
        ctx_.memory = m;
    }

    // time base + events
    io(tb_, next_deadline_, deadline_, vblank_index_, events_processed_);
    // bus diagnostics, INTC + timers, DMAC
    io(unhandled_.e, unhandled_.total);
    io(intc_stat_, intc_mask_, timers_);
    io(dch_, d_ctrl_, d_stat_, d_pcr_, d_sqwc_, d_rbsr_, d_rbor_, d_stadr_, d_enable_);
    // handler chains
    io(nodes_, counts_, node_free_, need_resched_, no_deliver_depth_, vsync_flag_ptr_, vsync_csr_ptr_);

    io.section("kernel-threads");
    for (Tcb& t : tcbs_) {
        int slot = fiber_slot_index(t.fiber);
        if (io.saving() && t.fiber && slot < 0) {
            io.fail("kernel: a thread fiber is not on a pinned slot");
            return false;
        }
        tcb_io(io, t, slot);
        if (io.loading()) t.fiber = slot >= 0 ? fiber_at_slot(slot) : nullptr;
    }
    io(q_head_, q_tail_, tcb_free_, current_, loaded_tid_, idle_since_);
    for (Sema& s : semas_) io(s);
    io(sema_free_);

    // harness / syscalls
    io(started_, dead_, last_.status, last_.message, stop_requested_);
    io(guest_table_, guest_installed_, kernel_patches_, cause12_dispatcher_, gs_crt_, gs_imr_, osd_param_, machine_type_,
       positive_in_handler_);

    io.section("kernel-fibers");
    io(slot_used_);
    int resume = fiber_slot_index(resume_fiber_);
    io(resume);
    std::vector<int> zombies;
    for (Fiber* z : zombies_) zombies.push_back(fiber_slot_index(z));
    io(zombies);
    for (std::size_t i = 0; i < slots_.size() && io.ok(); ++i) {
        if (!slot_used_[i]) continue;
        Fiber& f = slots_[i];
        if (io.loading()) {
            f = Fiber{};
            void* lo = pinned::fiber_slot_lo(i);
            if (!lo) {
                io.fail("kernel: a pinned fiber slot cannot be committed");
                return false;
            }
            f.slot = static_cast<int>(i);
            f.lo = static_cast<std::uint8_t*>(lo);
            f.hi = static_cast<std::uint8_t*>(pinned::fiber_slot_hi(i));
        }
        // Everything from the saved stack pointer to the top: the callee-saved registers p3fes_fiber_switch
        // pushed, then every frame of the thread's call chain.
        std::uint64_t rsp = reinterpret_cast<std::uint64_t>(f.ctx.rsp);
        io(rsp);
        const auto lo = reinterpret_cast<std::uint64_t>(f.lo), hi = reinterpret_cast<std::uint64_t>(f.hi);
        if (rsp < lo || rsp >= hi) {
            io.fail("kernel: a fiber's saved stack pointer lies outside its slot");
            return false;
        }
        if (io.saving() && std::getenv("P3FES_STATE_AUDIT")) audit_stack(static_cast<int>(i), rsp, hi);
        io.raw(reinterpret_cast<void*>(rsp), static_cast<std::size_t>(hi - rsp));
        if (io.loading()) {
            f.ctx.rsp = reinterpret_cast<void*>(rsp);
            f.ctx.stack_base = f.hi;
            f.ctx.stack_limit = f.lo;
            f.ctx.dealloc = f.lo - pinned::kFiberGuardBytes;
        }
    }
    if (io.loading() && io.ok()) {
        resume_fiber_ = fiber_at_slot(resume);
        zombies_.clear();
        for (int z : zombies) zombies_.push_back(fiber_at_slot(z));
        cur_fiber_ = &host_fiber_;
        stop_ = nullptr;
        force_check();
        if (!resume_fiber_ || !started_) io.fail("kernel: the state has no stopped fiber to resume");
    }
    return io.ok();
}

} // namespace p3fes::hle
