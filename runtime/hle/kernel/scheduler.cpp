// Fiber scheduler (ADR-0013 §1) with the EE kernel's queue rules (docs/ANALYSIS/15 §3, H-08..H-17):
// strict priority 0 (highest) .. 127, FIFO per level, 128 = idle; the RUN thread stays at the head of
// its queue while it runs; pick = head of the lowest non-empty queue.
//
// Execution: every guest thread owns one fiber (fiber.h; the kernel's own stack switch since 2026-10-21,
// Win32 fibers before; created lazily when the thread is first activated); the host thread that calls
// run/run_until is the host fiber and never runs guest code. A thread switch saves EEContext into the
// outgoing TCB, loads the incoming TCB into the one EEContext (keeping `cycles`), then switches stacks.
// Lifecycle invariants (README "Fiber lifecycle"):
//   L1 a fiber is never deleted while it is executing: an exiting/terminated thread whose fiber is the
//      executing one becomes a zombie, deleted by the next fiber that resumes (reap_zombies) or ~Kernel;
//   L2 a thread restarted after Exit/Terminate gets a new fiber; the old stack is never resumed;
//   L3 nothing with a destructor lives on a guest fiber's stack across a switch (kernel frames hold none;
//      the adapter must not either), because abandoned fibers are deleted without unwinding;
//   L4 ~Kernel runs on the host fiber, deletes every fiber and converts the host fiber back to a thread
//      if run_until converted it.
#include "kernel_core.h"

#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace p3fes::hle {

using namespace kc;

// ---- fibers (fiber.h) ----------------------------------------------------------------------------

void kc::fiber_prepare(Fiber& f, FiberEntry entry, void* arg) {
    // Top of the stack: 32 zero bytes; the first switch "returns" into p3fes_fiber_start with rsp = hi - 32
    // (16-byte aligned, [rsp] = 0 ends host stack walks). Below: the frame p3fes_fiber_switch unwinds -- 160
    // bytes xmm6-xmm15 (0), MXCSR 0x1F80 and x87 CW 0x027F (the power-on defaults a FIBER_FLAG_FLOAT_SWITCH
    // fiber started with), r15 r14 r13 r12 rsi(arg) rdi rbp rbx(entry), the return address.
    std::uint8_t* const e = f.hi - 32;
    std::memset(e, 0, 32);
    std::uint8_t* const s = e - 240;
    std::memset(s, 0, 240);
    const std::uint32_t mxcsr = 0x1F80u;
    const std::uint16_t fpucw = 0x027Fu;
    std::memcpy(s + 160, &mxcsr, 4);
    std::memcpy(s + 164, &fpucw, 2);
    auto* g = reinterpret_cast<std::uint64_t*>(s + 168);
    g[4] = reinterpret_cast<std::uint64_t>(arg);                      // rsi
    g[7] = reinterpret_cast<std::uint64_t>(entry);                    // rbx
    g[8] = reinterpret_cast<std::uint64_t>(&p3fes_fiber_start);       // return address
    f.ctx.rsp = s;
    f.ctx.stack_base = f.hi;
    f.ctx.stack_limit = f.lo;
    f.ctx.dealloc = f.slot >= 0 ? f.lo - pinned::kFiberGuardBytes : static_cast<std::uint8_t*>(f.alloc_base);
}

void KernelHooks::fiber_entry(void* self) { static_cast<KernelHooks*>(self)->thread_fiber_main(); }

int KernelHooks::fiber_slot_index(const Fiber* f) const {
    if (!f || f < slots_.data() || f >= slots_.data() + slots_.size()) return -1;
    return static_cast<int>(f - slots_.data());
}

Fiber* KernelHooks::fiber_at_slot(int i) {
    if (i < 0 || i >= static_cast<int>(slots_.size())) return nullptr;
    return &slots_[static_cast<unsigned>(i)];
}

Fiber* KernelHooks::create_fiber() {
    Fiber* f = nullptr;
    if (pinned::enabled()) {
        // A fixed stack slot (lowest free): the same slot -> the same stack addresses in every process.
        for (std::size_t i = 0; i < slots_.size(); ++i) {
            if (slot_used_[i]) continue;
            void* lo = pinned::fiber_slot_lo(i);
            if (!lo) die("pinned fiber slot %zu cannot be committed (error %lu)", i, GetLastError());
            slot_used_[i] = true;
            f = &slots_[i];
            *f = Fiber{};
            f->slot = static_cast<int>(i);
            f->lo = static_cast<std::uint8_t*>(lo);
            f->hi = static_cast<std::uint8_t*>(pinned::fiber_slot_hi(i));
            break;
        }
        if (!f) die("all %zu pinned fiber slots are in use", slots_.size());
    } else {
        const std::size_t guard = pinned::kFiberGuardBytes;
        const std::size_t bytes = (opts_.fiber_stack_bytes + 0xFFFFu) & ~std::size_t{0xFFFFu};
        void* base = VirtualAlloc(nullptr, guard + bytes, MEM_RESERVE, PAGE_NOACCESS);
        void* lo = base ? VirtualAlloc(static_cast<std::uint8_t*>(base) + guard, bytes, MEM_COMMIT, PAGE_READWRITE) : nullptr;
        if (!lo) die("fiber stack allocation failed (error %lu, stack %zu bytes)", GetLastError(), bytes);
        f = new Fiber;
        f->alloc_base = base;
        f->lo = static_cast<std::uint8_t*>(lo);
        f->hi = f->lo + bytes;
    }
    fiber_prepare(*f, &KernelHooks::fiber_entry, this);
    return f;
}

void KernelHooks::delete_fiber(Fiber* f) {
    if (!f || f == &host_fiber_) return;
    if (f->slot >= 0) {
        slot_used_[static_cast<unsigned>(f->slot)] = false;
        *f = Fiber{};
        return;
    }
    VirtualFree(f->alloc_base, 0, MEM_RELEASE);
    delete f;
}

// Switch the host thread to fiber `to`; returns when some fiber switches back to the caller's.
void KernelHooks::switch_fiber(Fiber* to) {
    Fiber* const from = cur_fiber_;
    cur_fiber_ = to;
    p3fes_fiber_switch(&from->ctx, &to->ctx);
}

void KernelHooks::delete_fiber_or_zombie(Fiber* f) {
    if (!f) return;
    if (f == cur_fiber_) zombies_.push_back(f);  // L1
    else delete_fiber(f);
}

void KernelHooks::reap_zombies() {
    Fiber* const cur = cur_fiber_;
    for (std::size_t i = 0; i < zombies_.size();) {
        if (zombies_[i] != cur && zombies_[i] != resume_fiber_) {  // never the host's resume target
            delete_fiber(zombies_[i]);
            zombies_[i] = zombies_.back();
            zombies_.pop_back();
        } else {
            ++i;
        }
    }
}

[[noreturn]] void KernelHooks::thread_fiber_main() {
    reap_zombies();
    if (prof::on()) prof::switch_to(static_cast<std::uint8_t>(prof::Zone::Ee));  // a new fiber: no zone to restore
    const int tid = current_;
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.host_entry) {
        t.host_entry(ctx_);
        // The main thread's entry returned: the run ends (README "Harness").
        exit_current(false);
    }
    lookup(t.entry)(ctx_);
    // `jr $ra` out of the entry lands on root_func (SetupThread's, inherited: the game's 0x100220 ExitThread).
    const u32 root = tcbs_[static_cast<unsigned>(tid)].root;
    if (root) lookup(root)(ctx_);
    exit_current(false);
}

void KernelHooks::switch_to_host(RunStatus st, std::string msg) {
    last_.status = st;
    last_.message = std::move(msg);
    if (st != RunStatus::Stopped) dead_ = true;
    resume_fiber_ = cur_fiber_;
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Fiber);
    switch_fiber(&host_fiber_);
    prof::leave(prof_zone);
    // Resumed by run_until (Stopped only).
    reap_zombies();
}

// ---- context save / load ---------------------------------------------------------------------------

void KernelHooks::save_loaded() {
    if (loaded_tid_ < 0) return;
    Tcb& t = tcbs_[static_cast<unsigned>(loaded_tid_)];
    t.saved = ctx_;
    loaded_tid_ = -1;
}

void KernelHooks::load(int tid) {
    const u64 cycles = ctx_.cycles;
    EEMemory* const m = ctx_.memory;
    ctx_ = tcbs_[static_cast<unsigned>(tid)].saved;
    ctx_.cycles = cycles;
    ctx_.memory = m;
    loaded_tid_ = tid;
}

// ---- ready queues ------------------------------------------------------------------------------------

void KernelHooks::q_push_tail(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    const unsigned p = static_cast<unsigned>(t.cur_prio);
    t.q_prev = q_tail_[p];
    t.q_next = -1;
    if (q_tail_[p] >= 0) tcbs_[static_cast<unsigned>(q_tail_[p])].q_next = tid;
    else q_head_[p] = tid;
    q_tail_[p] = tid;
    t.queued = true;
}

void KernelHooks::q_remove(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (!t.queued) return;
    const unsigned p = static_cast<unsigned>(t.cur_prio);
    if (t.q_prev >= 0) tcbs_[static_cast<unsigned>(t.q_prev)].q_next = t.q_next;
    else q_head_[p] = t.q_next;
    if (t.q_next >= 0) tcbs_[static_cast<unsigned>(t.q_next)].q_prev = t.q_prev;
    else q_tail_[p] = t.q_prev;
    t.q_prev = t.q_next = -1;
    t.queued = false;
}

int KernelHooks::q_top() const {
    for (int p = 0; p < kPrioLevels - 1; ++p)
        if (q_head_[static_cast<unsigned>(p)] >= 0) return p;
    return kPrioLevels - 1;  // idle
}

void KernelHooks::ready_insert(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.cur_prio < 0 || t.cur_prio > 127)
        die("thread %d made READY with priority %d (CreateThread does not range-check; 0..127 required)", tid,
            t.cur_prio);
    const int top = q_top();
    t.status = TStatus::Ready;
    q_push_tail(tid);
    // i* workers flag a reschedule for a strictly higher priority than every ready thread (incl. RUN).
    if (t.cur_prio < top) need_resched_ = true;
}

int KernelHooks::pick() const {
    for (int p = 0; p < kPrioLevels - 1; ++p) {
        const int h = q_head_[static_cast<unsigned>(p)];
        if (h >= 0) return h;
    }
    return kIdleTid;
}

// ---- scheduling ----------------------------------------------------------------------------------------

// Make `next` the RUN thread. Returns at once if it already owns the executing fiber, else switches to
// its fiber (creating it on first activation) and returns when this fiber's thread is activated again.
void KernelHooks::activate(int next) {
    Tcb& n = tcbs_[static_cast<unsigned>(next)];
    if (current_ != kIdleTid && current_ != next) {
        Tcb& c = tcbs_[static_cast<unsigned>(current_)];
        if (c.status == TStatus::Run) c.status = TStatus::Ready;  // preempted: still queued at its head
    }
    idle_since_ = kNever;
    if (n.wait_type != kWaitNone) {  // released wait (DeleteSema / ReleaseWaitThread): $v0 = -1 (`15` §3)
        n.wait_type = kWaitNone;
        n.wait_id = 0;
        if (opts_.context_frames && n.frame) {
            // ksched_preempt 0x80003A58: `sw -1, 32(frame)` -- only the low word of the saved $v0 changes.
            n.saved.gpr[GPR_V0].u32[0] = 0xFFFFFFFFu;
            mem_.write<u32>(n.frame + 32u, 0xFFFFFFFFu);
        } else {
            set_gpr(n.saved, GPR_V0, -1);
        }
    }
    if (n.start_from_frame) {  // first activation after StartThread: the BIOS restores the frame (0x80003800)
        n.start_from_frame = false;
        frame_load(next, n.saved);
    }
    n.status = TStatus::Run;
    current_ = next;
    if (loaded_tid_ != next) {
        save_loaded();
        load(next);
    }
    if (n.fiber == cur_fiber_) return;
    if (!n.fiber) n.fiber = create_fiber();
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Fiber);
    switch_fiber(n.fiber);
    prof::leave(prof_zone);
    reap_zombies();
}

void KernelHooks::reschedule() {
    for (;;) {
        const int next = pick();
        if (next == kIdleTid) {
            idle_step();
            continue;
        }
        activate(next);
        return;
    }
}

// The idle thread (tid 0, priority 128): no thread is READY, so jump virtual time to the next deadline,
// process it and deliver what became pending (ADR-0013 §2 idle rule: never spin, never sleep the host).
void KernelHooks::idle_step() {
    if (current_ != kIdleTid) {
        Tcb& c = tcbs_[static_cast<unsigned>(current_)];
        if (c.status == TStatus::Run) c.status = TStatus::Ready;
        current_ = kIdleTid;
    }
    save_loaded();  // ctx_ becomes scratch for the idle thread
    ctx_.cop0[12] = opts_.thread_status;
    if (idle_since_ == kNever) idle_since_ = ctx_.cycles;
    if (!(dmac_pending() || intc_pending())) {
        u64 d = kNever;
        for (u64 v : deadline_) d = std::min(d, v);
        if (d == kNever) die("deadlock: no runnable thread and no pending event");
        if (d > ctx_.cycles) {
            if (d - idle_since_ > opts_.idle_limit_cycles)
                die("deadlock: no thread became runnable within %llu idle cycles (next event at %llu)",
                    static_cast<unsigned long long>(opts_.idle_limit_cycles), static_cast<unsigned long long>(d));
            ctx_.cycles = d;
        }
    }
    process_due_events(ctx_.cycles);
    if (stop_requested_) take_stop("stopped by request (idle)");  // before delivery, as in slow_check
    while (deliver_one()) process_due_events(ctx_.cycles);
    need_resched_ = false;  // the pick that follows serves it
    if (stop_requested_) take_stop("stopped by request (idle)");
    if (stop_ && stop_()) switch_to_host(RunStatus::Stopped, "stopped by run_until predicate (idle)");
}

// Block the RUN thread (SleepThread / WaitSema): leave the ready queue, WAIT, save its context with the
// $v0 a normal wake returns, pick. Returns when the thread runs again ($v0 already in ctx).
void KernelHooks::block(u32 wait_type, u32 wait_id, s64 normal_result) {
    const int tid = current_;
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    q_remove(tid);
    t.status = TStatus::Wait;
    t.wait_type = wait_type;
    t.wait_id = wait_id;
    set_gpr(ctx_, GPR_V0, normal_result);
    save_loaded();
    current_ = kIdleTid;
    reschedule();
}

void KernelHooks::build_initial_ctx(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    EEContext c{};
    for (unsigned i = 0; i < 32; ++i) c.cop0[i] = ctx_.cop0[i];  // PRId and friends as the runtime set them
    c.cop0[12] = opts_.thread_status;
    const u32 sp = t.stack + t.stack_size - 0x20u;  // `15` §3: sp = fp = stack + size - 0x20
    set_gpr(c, GPR_SP, static_cast<s32>(sp));
    set_gpr(c, GPR_FP, static_cast<s32>(sp));
    set_gpr(c, GPR_GP, static_cast<s32>(t.gp));
    set_gpr(c, GPR_RA, static_cast<s32>(t.root));
    set_gpr(c, GPR_A0, static_cast<s32>(t.arg));
    c.pc = t.entry;
    c.memory = &mem_;
    t.saved = c;
}

// ---- context frames in guest memory (KernelOptions::context_frames) -----------------------------------------
// Layout of kctx_save_on_thread_stack 0x80003680 / the restore 0x80003800 (BIOS v02.30, obs): +0 SA, +4 FCSR,
// +8 ACC, +16*r GPR r for r = 1..25 (128-bit), +416 HI, +424 HI1, +432 LO, +440 LO1, +448 gp, +464 sp,
// +480 fp, +496 ra (128-bit), +512 + 4*i FPR i. k0/k1 are not saved.

u32 KernelHooks::frame_save(int tid, const EEContext& c, const u128& v0) {
    const u32 f = c.gpr[GPR_SP].u32[0] - 0x280u;
    mem_.write<u32>(f + 0u, c.sa);
    mem_.write<u32>(f + 4u, c.fcr31);
    mem_.write<u32>(f + 8u, c.acc);  // inf: the BIOS reads ACC out with madd.s ACC + 0 * -0.0
    for (unsigned r = 1; r <= 25; ++r) mem_.write<u128>(f + 16u * r, r == GPR_V0 ? v0 : c.gpr[r]);
    mem_.write<u64>(f + 416u, c.hi.u64[0]);
    mem_.write<u64>(f + 424u, c.hi.u64[1]);
    mem_.write<u64>(f + 432u, c.lo.u64[0]);
    mem_.write<u64>(f + 440u, c.lo.u64[1]);
    for (unsigned r : {GPR_GP, GPR_SP, GPR_FP, GPR_RA}) mem_.write<u128>(f + 16u * r, c.gpr[r]);
    for (unsigned i = 0; i < 32; ++i) mem_.write<u32>(f + 512u + 4u * i, c.fpr[i]);
    if (tid > 0) tcbs_[static_cast<unsigned>(tid)].frame = f;
    return f;
}

// CreateThread 0x80003DBC, SetupThread 0x800051FC, kthread_reset_dormant 0x80003C24: four words of a fresh frame.
void KernelHooks::frame_init(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    const u32 f = t.stack + t.stack_size - 0x2A0u;
    const u32 sp = t.stack + t.stack_size - 0x20u;
    mem_.write<u32>(f + 448u, t.gp);
    mem_.write<u32>(f + 464u, sp);
    mem_.write<u32>(f + 480u, sp);
    mem_.write<u32>(f + 496u, t.root);
    t.frame = f;
}

void KernelHooks::frame_load(int tid, EEContext& c) const {
    const u32 f = tcbs_[static_cast<unsigned>(tid)].frame;
    c.sa = mem_.read<u32>(f + 0u);
    c.fcr31 = mem_.read<u32>(f + 4u);
    c.acc = mem_.read<u32>(f + 8u);  // inf: restored with adda.s frame[8] + -0.0
    for (unsigned r = 1; r <= 25; ++r) c.gpr[r] = mem_.read<u128>(f + 16u * r);
    c.hi.u64[0] = mem_.read<u64>(f + 416u);
    c.hi.u64[1] = mem_.read<u64>(f + 424u);
    c.lo.u64[0] = mem_.read<u64>(f + 432u);
    c.lo.u64[1] = mem_.read<u64>(f + 440u);
    for (unsigned r : {GPR_GP, GPR_SP, GPR_FP, GPR_RA}) c.gpr[r] = mem_.read<u128>(f + 16u * r);
    for (unsigned i = 0; i < 32; ++i) c.fpr[i] = mem_.read<u32>(f + 512u + 4u * i);
}

void KernelHooks::reset_dormant(int tid) {
    Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    q_remove(tid);
    if (t.status == TStatus::Wait || t.status == TStatus::WaitSuspend) sema_drop_waiter(tid);
    t.status = TStatus::Dormant;
    t.cur_prio = t.init_prio;
    t.wait_type = kWaitNone;
    t.wait_id = 0;
    t.wakeup_count = 0;  // inf
    delete_fiber_or_zombie(t.fiber);
    t.fiber = nullptr;
    if (loaded_tid_ == tid) loaded_tid_ = -1;
    if (opts_.context_frames) frame_init(tid);  // "fresh context" (kthread_reset_dormant 0x80003BB8)
}

[[noreturn]] void KernelHooks::exit_current(bool del) {
    const int tid = current_;
    if (tid == kIdleTid) die("ExitThread from the idle thread (an interrupt handler?)");
    reset_dormant(tid);
    current_ = kIdleTid;
    if (del) {
        tcbs_[static_cast<unsigned>(tid)].status = TStatus::Free;
        tcb_free_.push_back(tid);
    }
    if (tid == kMainTid) {
        switch_to_host(RunStatus::MainExited, del ? "main thread ExitDeleteThread" : "main thread exited");
        std::abort();  // never resumed
    }
    reschedule();
    die("thread %d resumed after exiting", tid);
}

void KernelHooks::sema_drop_waiter(int tid) {
    const Tcb& t = tcbs_[static_cast<unsigned>(tid)];
    if (t.wait_type != kWaitSema || !sema_valid(static_cast<s32>(t.wait_id))) return;
    std::deque<int>& w = semas_[t.wait_id].waiters;
    w.erase(std::remove(w.begin(), w.end(), tid), w.end());
}

// ---- harness -------------------------------------------------------------------------------------------

void KernelHooks::start(GuestFn main_fn) {
    if (started_) die("Kernel::start called twice");
    Tcb& m = tcbs_[kMainTid];
    m = Tcb{};
    m.status = TStatus::Run;
    m.init_prio = m.cur_prio = 0;  // ExecPS2: the caller keeps its tid at priority 0 (H-15)
    m.host_entry = main_fn;
    if (!ctx_.memory) ctx_.memory = &mem_;
    ctx_.cop0[12] = opts_.main_status;
    q_push_tail(kMainTid);
    current_ = kMainTid;
    loaded_tid_ = kMainTid;
    started_ = true;
    run_services();  // the devices' first deadlines
}

RunResult KernelHooks::run_until(std::function<bool()> stop) {
    if (dead_) return last_;
    if (!started_) {
        std::fputs("p3fes kernel: run_until before start\n", stderr);
        std::abort();
    }
    if (cur_fiber_ != &host_fiber_) {
        std::fputs("p3fes kernel: run_until called from guest code\n", stderr);
        std::abort();
    }
    stop_ = std::move(stop);
    force_check();
    if (!resume_fiber_) {
        Tcb& m = tcbs_[kMainTid];
        m.fiber = create_fiber();
        resume_fiber_ = m.fiber;
    }
    Fiber* const f = resume_fiber_;
    resume_fiber_ = nullptr;
    const std::uint8_t prof_zone = prof::enter(prof::Zone::Fiber);
    switch_fiber(f);
    prof::leave(prof_zone);
    // Back on the host fiber.
    if (dead_) resume_fiber_ = nullptr;  // MainExited / Fatal: that fiber is never resumed
    reap_zombies();
    stop_ = nullptr;
    force_check();
    return last_;
}

} // namespace p3fes::hle
