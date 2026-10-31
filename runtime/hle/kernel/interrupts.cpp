// INTC/DMAC handler lists and their dispatch, exactly per docs/ANALYSIS/15 §2.1-2.3 (obs from the BIOS
// v02.30 kernel) and §8 H-01..H-06:
//   * one pool of node ids 1..128 shared by INTC and DMAC handlers, FIFO free list;
//   * AddXxxHandler(cause, fn, next, arg): next 0 -> head, -1 -> tail, id -> immediately before id;
//     INTC cause >= 15 or == 1 -> -1, DMAC channel >= 16 -> -1;
//   * delivery: one cause per interrupt, DMAC (COP0 IP3) before INTC (IP2), highest cause/channel first;
//     the STAT bit is acknowledged before dispatch; SetVSyncFlag is serviced before any cause-2 handler;
//     the chain runs head -> tail with interrupts disabled, each handler called as
//     handler(cause|channel, arg, EPC) with the registrant's $gp on the trampoline stack 0x81FC0;
//     a negative return stops the chain;
//   * an empty list prints "# INTC(%d) Handler does not exist." and KExits on hardware -> fatal here.
// Handlers are recompiled functions run as nested host calls on the current fiber; the interrupted
// context is saved before the chain and restored after it (all of EEContext except `cycles`; H-05).
#include "kernel_core.h"

#include <bit>

namespace p3fes::hle {

using namespace kc;

bool KernelHooks::cpu_can_deliver(const EEContext& ctx) const {
    const u32 st = ctx.cop0[12];
    return (st & kStEie) && (st & kStIe) && !(st & (kStExl | kStErl));
}

int KernelHooks::handler_count(bool dmac, int idx) const {
    if (dmac) return (idx >= 0 && idx < kDmacLists) ? counts_[static_cast<unsigned>(kIntcLists + idx)] : -1;
    return (idx >= 0 && idx < kIntcLists) ? counts_[static_cast<unsigned>(idx)] : -1;
}

// list: 0..14 INTC cause, 15..30 DMAC channel (15 + ch).
s64 KernelHooks::add_handler(int list, u32 handler, s32 next, u32 arg, u32 gp) {
    if (node_free_.empty()) return -1;
    const int sentinel = list < kIntcLists ? kIntcSentinel0 + list : kDmacSentinel0 + (list - kIntcLists);
    int pos = 0;
    if (next == 0) {
        pos = nodes_[static_cast<unsigned>(sentinel)].R;  // head: before the current first node
    } else if (next == -1) {
        pos = sentinel;  // tail: before the sentinel
    } else if (next >= 1 && next <= kNodeIds) {
        const HNode& at = nodes_[static_cast<unsigned>(next)];
        if (!at.used) return -1;
        if (at.list != list)
            die("Add%sHandler(%d, next=%d): node %d belongs to another list (%d); the kernel would link across lists",
                list < kIntcLists ? "Intc" : "Dmac", list < kIntcLists ? list : list - kIntcLists, next, next, at.list);
        pos = next;
    } else {
        return -1;
    }
    const int id = node_free_.front();
    node_free_.pop_front();
    HNode& n = nodes_[static_cast<unsigned>(id)];
    n.handler = handler;
    n.gp = gp;
    n.arg = arg;
    n.mode = 2;
    n.used = true;
    n.list = list;
    // klist_insert_before(pos, node)
    HNode& p = nodes_[static_cast<unsigned>(pos)];
    n.R = pos;
    n.L = p.L;
    nodes_[static_cast<unsigned>(p.L)].R = id;
    p.L = id;
    ++counts_[static_cast<unsigned>(list)];
    return id;
}

s64 KernelHooks::remove_handler(int list, s32 id) {
    if (id < 1 || id > kNodeIds || !nodes_[static_cast<unsigned>(id)].used) return -1;
    HNode& n = nodes_[static_cast<unsigned>(id)];
    if (n.list != list)
        die("Remove%sHandler(%d, %d): handler %d is on list %d (the kernel would corrupt the counts)",
            list < kIntcLists ? "Intc" : "Dmac", list < kIntcLists ? list : list - kIntcLists, id, id, n.list);
    nodes_[static_cast<unsigned>(n.L)].R = n.R;
    nodes_[static_cast<unsigned>(n.R)].L = n.L;
    // The node keeps its R link: a chain walking past a handler that removed itself continues (kernel shape).
    n.used = false;
    n.mode = 0;
    n.list = -1;
    node_free_.push_back(id);
    --counts_[static_cast<unsigned>(list)];
    return 0;  // inf: success value not recorded in `15`
}

void KernelHooks::service_vsync_flag() {
    if (!vsync_flag_ptr_) return;
    mem_.write<u32>(vsync_flag_ptr_, 1u);
    vsync_flag_ptr_ = 0;
    if (vsync_csr_ptr_) {
        const u64 csr = read64(kGsCsrPa);
        mem_.write<u64>(vsync_csr_ptr_, csr);
        vsync_csr_ptr_ = 0;
    }
}

bool KernelHooks::deliver_one() {
    if (const u32 dp = dmac_pending()) {  // IP3 outranks IP2
        const unsigned ch = static_cast<unsigned>(std::bit_width(dp) - 1);
        d_stat_ &= ~(1u << ch);  // ack before dispatch
        need_resched_ = false;
        run_chain(kIntcLists + static_cast<int>(ch), ch);
        return true;
    }
    if (const u32 ip = intc_pending()) {
        const unsigned cause = static_cast<unsigned>(std::bit_width(ip) - 1);
        intc_stat_ &= ~(1u << cause);
        need_resched_ = false;
        if (cause == 2) service_vsync_flag();  // H-06: before the handlers, regardless of their results
        run_chain(static_cast<int>(cause), cause);
        return true;
    }
    return false;
}

void KernelHooks::run_chain(int list, u32 code) {
    const bool dmac = list >= kIntcLists;
    const int n = counts_[static_cast<unsigned>(list)];
    if (n <= 0) die("# %s(%u) Handler does not exist.", dmac ? "DMAC" : "INTC", code);
    const int sentinel = dmac ? kDmacSentinel0 + (list - kIntcLists) : kIntcSentinel0 + list;
    if (census_) ++(dmac ? census_->dmac_chains[static_cast<unsigned>(list - kIntcLists)] : census_->intc_chains[static_cast<unsigned>(list)]);

    // kintr_save_gprs; the HLE saves everything (H-05). Only `cycles` survives the restore.
    const EEContext saved = ctx_;
    ++no_deliver_depth_;
    ctx_.cop0[12] &= ~kStIe;  // handlers run with IE = 0: EI/DI only touch EIE (`15` §2.3)
    const u32 epc = saved.pc;
    int node = nodes_[static_cast<unsigned>(sentinel)].R;
    for (int i = 0; i < n && node != sentinel; ++i) {
        const HNode h = nodes_[static_cast<unsigned>(node)];
        if (h.mode == 2) {
            set_gpr(ctx_, GPR_A0, static_cast<s64>(code));
            set_gpr(ctx_, GPR_A1, static_cast<s32>(h.arg));
            set_gpr(ctx_, GPR_A2, static_cast<s32>(epc));
            set_gpr(ctx_, GPR_GP, static_cast<s32>(h.gp));
            set_gpr(ctx_, GPR_SP, static_cast<s32>(kIntrStackVa));
            set_gpr(ctx_, GPR_RA, static_cast<s32>(kIntrReturnVa));
            set_gpr(ctx_, GPR_V1, static_cast<s32>(h.handler));
            ctx_.pc = h.handler;
            if (census_) ++census_->handler_runs[h.handler];
            const std::uint8_t prof_zone = prof::enter(prof::Zone::Ee);
            lookup(h.handler)(ctx_);
            prof::leave(prof_zone);
            if (static_cast<s64>(ctx_.gpr[GPR_V0].u64[0]) < 0) break;  // bgez: a negative return stops the chain
        }
        node = nodes_[static_cast<unsigned>(node)].R;  // live link, read after the call (kernel shape)
    }
    --no_deliver_depth_;
    const u64 cycles = ctx_.cycles;
    ctx_ = saved;
    ctx_.cycles = cycles;
}

} // namespace p3fes::hle
