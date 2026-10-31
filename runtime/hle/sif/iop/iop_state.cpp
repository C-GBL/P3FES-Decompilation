// Machine state of the IOP side (runtime/STATE.md): IOP RAM + its heap, the SIF register file, queued SIF0
// packets, RPC bindings and pending calls, every RPC server (CDVD with an in-flight read, PADMAN, DBCMAN + the
// MC2_S1 model, fileio, CRI_ADXI, SDRDRV with the interpreted SK modules: R3000, IOP kernel, libsd + SPU2 voices),
// the SPU2 mixer and the memory card image. Wiring (servers' identities, host calls, sinks, hooks) is built by the
// loading process exactly as by the saver; only the dynamic fields travel.
#include <cstddef>
#include <cstring>

#include "iop_core.h"
#include "iop_kernel_hle.h"
#include "libsd_hle.h"
#include "mc_mc2s1.h"
#include "r3000.h"
#include "srv_adxi.h"
#include "srv_cdvdfsv.h"
#include "srv_padman.h"
#include "srv_sdr.h"
#include "p3fes/audio/spu2_voice.h"
#include "p3fes/hle/cdvd.h"
#include "p3fes/hle/memcard/card.h"
#include "p3fes/hle/memcard/iop_slot.h"
#include "p3fes/state_io.h"

namespace p3fes::hle::sif::detail {

void state_io(StateIo& io, EeWrite& w) { io(w.addr, w.bytes); }
void state_io(StateIo& io, Sif0Item& s) { io(s.writes, s.has_packet, s.packet, s.packet_size, s.not_before); }
void state_io(StateIo& io, RpcReply& r) { io(r.rdata, r.writes); }

}  // namespace p3fes::hle::sif::detail

namespace p3fes::hle::sif {
void state_io(StateIo& io, LoadedModule& m) { io(m.id, m.path, m.args); }
}  // namespace p3fes::hle::sif

namespace p3fes::hle::sif::iop {

void state_io(StateIo& io, KernelThread& t) {
    io(t.id, t.owner, t.attr, t.option, t.entry, t.stack, t.stack_size, t.gp, t.init_priority, t.priority);
    io(t.status, t.wait, t.wait_id, t.wait_until, t.wakeups, t.ready_seq, t.ctx, t.exit_value, t.runs, t.instructions);
}
void state_io(StateIo& io, KernelSema& s) { io(s.id, s.attr, s.option, s.count, s.max, s.waiters); }
void state_io(StateIo& io, GuestLibrary& l) { io(l.name, l.version, l.table, l.functions, l.module_id, l.order); }
void state_io(StateIo& io, IrxImport& i) { io(i.library, i.version, i.table, i.ordinals, i.stubs); }
void state_io(StateIo& io, IrxExport& e) { io(e.library, e.version, e.table, e.functions); }
void state_io(StateIo& io, IrxModule& m) {
    io(m.name, m.version, m.base, m.entry, m.gp, m.text_size, m.data_size, m.bss_size, m.image_size);
    io(m.relocations, m.imports, m.exports);
}
void state_io(StateIo& io, UnresolvedImport& u) { io(u.library, u.ordinal); }
void state_io(StateIo& io, LoadedIrx& m) {
    io(m.id, m.path, m.info, m.unresolved, m.start_thread, m.start_result, m.start_returned, m.start_instructions);
    io(m.argv, m.block, m.resident);
}

void R3000::state(StateIo& io) {
    io.section("r3000");
    io(s_, stop_requested_, instructions_, host_calls_made_, trapped_);
    io(trap_.stop, trap_.pc, trap_.word, trap_.what);
}

void IopKernel::state(StateIo& io) {
    io.section("iop-kernel");
    io.expect(static_cast<u64>(cpu_.host_call_count()), "IOP host-call table");
    io(now_, fault_, printf_log_, threads_, next_thread_id_, current_, ready_counter_, in_handler_);
    io(semas_, next_sema_id_, timers_, next_timer_id_, handler_runs_, suspend_depth_);
    io(libraries_, modules_, next_module_id_, rpc_servers_, intr_stack_);
    io(rpc_.active, rpc_.done, rpc_.thread, rpc_.saved, rpc_.saved_wait_id, rpc_.result);
    io(rpc_return_addr_, rpc_calls_, rpc_pending_runs_);
    cpu_.state(io);
}

void LibsdHle::state(StateIo& io) {
    io.section("libsd");
    voices_.state(io);
    io(params_, addrs_, effect_attr_, trans_addr_, transfers_, voice_trans_bytes_, block_trans_bytes_);
    u64 pw = param_writes_;
    io(pw);
    param_writes_ = static_cast<std::size_t>(pw);
    io(init_calls_);
}

}  // namespace p3fes::hle::sif::iop

namespace p3fes::hle {

void CdvdHle::state(StateIo& io, const std::function<u64(std::span<std::byte>)>& encode,
                    const std::function<std::span<std::byte>(u64, std::size_t)>& decode) {
    io.section("cdvd");
    bool has = pending_.has_value();
    io(has);
    if (has) {
        if (io.loading()) pending_.emplace(Pending{});
        Pending& p = *pending_;
        u64 dst = io.saving() ? encode(p.dst) : 0;
        u64 len = p.dst.size();
        io(p.kind, p.lsn, p.sectors, dst, len, p.steps_left, p.aborted);
        if (io.loading()) p.dst = decode(dst, static_cast<std::size_t>(len));
    } else if (io.loading()) {
        pending_.reset();
    }
    io(last_read_mode_);
    bool err = last_host_error_.has_value();
    io(err);
    if (err) {
        if (io.loading()) last_host_error_.emplace();
        u64 detail = reinterpret_cast<u64>(last_host_error_->detail);  // a static string of this executable
        io(last_host_error_->code, detail);
        last_host_error_->detail = reinterpret_cast<const char*>(detail);
    } else if (io.loading()) {
        last_host_error_.reset();
    }
    io(completions_, latency_, error_, media_mode_);
}

}  // namespace p3fes::hle

namespace p3fes::hle::sif::detail {

void IopRam::state(StateIo& io) {
    io.section("iop-ram");
    io(ram_, blocks_, arena_next_, heap_begin_, heap_end_);
}

void SjUni::state(StateIo& io) { io(used_, mode_, pool_, nodes_, lines_); }

void CdvdfsvServer::state(StateIo& io, IopCore& /*core*/) {
    bool has = pending_.has_value();
    io(has);
    if (has) {
        if (io.loading()) pending_.emplace();
        Pending& p = *pending_;
        io(p.ticket, p.kind, p.lsn, p.sectors, p.paddr, p.remain_ee, p.readpos_ee, p.staged, p.staging, p.deadline);
    } else if (io.loading()) {
        pending_.reset();
    }
    io(eereadx_, error_override_, hook_signals_, warned_no_disc_);
    // CdvdHle's in-flight read writes into this server's staging buffer or into guest RAM (pinned arena, the same
    // address in every process): bit 63 marks a staging offset.
    const auto encode = [this](std::span<std::byte> s) -> u64 {
        if (pending_ && !pending_->staging.empty()) {
            const std::byte* b = pending_->staging.data();
            if (s.data() >= b && s.data() < b + pending_->staging.size())
                return (1ull << 63) | static_cast<u64>(s.data() - b);
        }
        return reinterpret_cast<u64>(s.data());
    };
    const auto decode = [this](u64 v, std::size_t len) -> std::span<std::byte> {
        if (v >> 63) {
            if (!pending_ || (v & ~(1ull << 63)) + len > pending_->staging.size()) return {};
            return {pending_->staging.data() + (v & ~(1ull << 63)), len};
        }
        return {reinterpret_cast<std::byte*>(v), len};
    };
    bool has_cd = cdvd_ != nullptr;
    io.expect(has_cd, "CDVD presence");
    if (cdvd_) cdvd_->state(io, encode, decode);
}

void PadmanServer::state(StateIo& io, IopCore& /*core*/) { io(ports_, inputs_, last_vblank_); }

void AdxiServer::state(StateIo& io, IopCore& core) {
    io(base_, dtx_, rna_, sjx_);
    for (SjUni& s : sj_) s.state(io);
    io(core_no_, sfreq_default_, psm_voices_, init_count_, paused_, out_running_, next_frame_);
    io(seen_vblank_, tick_due_, now_, stream_seq_, st_, mixbuf_);
    bool bound = core_ != nullptr;
    io(bound);
    if (io.loading()) core_ = bound ? &core : nullptr;
}

void SdrdrvServer::state(StateIo& io, IopCore& core) {
    io(params_, spu2_, spu2_sent_, hs_entry_, port_, sq_entry_, track_, track_next_);
    io(routed_, module_failed_, modules_loaded_, rpc_routed_, rpc_pending_, pending_);
    bool bound = core_ != nullptr, has_kernel = kernel_ != nullptr;
    io(bound, has_kernel);
    if (io.loading()) {
        if (has_kernel) ensure_kernel(core);  // builds LibsdHle + IopKernel and their wiring as the first module load did
        core_ = bound ? &core : nullptr;
    }
    if (has_kernel) {
        sd_->state(io);
        kernel_->state(io);
    }
    // --native sound (runtime/native/sound/sk): libsd and the voices without the interpreter's kernel.
    bool native_sd = sd_ != nullptr && kernel_ == nullptr;
    io(native_sd, native_now_);
    if (native_sd) {
        if (io.loading()) ensure_libsd(core);
        sd_->state(io);
    }
}

void Mc2s1Model::state(StateIo& io) {
    io.section("mc2s1");
    io(rtc_, resp_, page_buf_, check_buf_, new_card_, toggle_, stats_, ecc_size_, xfer_size_);
}

void IopCore::state(StateIo& io) {
    io.section("iop-core");
    ram_.state(io);
    io(regs_, stats_, sif0_, ee_recv_buf_, iop_sregs_, rebooting_, reboot_deadline_);

    // Bindings: the server as its index in servers_ (the order register_servers built them in).
    io.expect(static_cast<u64>(servers_.size()), "IOP server count");
    u64 n = by_sid_.size();
    io(n);
    if (io.saving()) {
        for (auto& [sid, b] : by_sid_) {
            s32 idx = -1;
            for (std::size_t i = 0; i < servers_.size(); ++i)
                if (servers_[i].get() == b.server) idx = static_cast<s32>(i);
            u32 k = sid;
            io(k, idx, b.sid, b.sd, b.buf, b.buf_size);
        }
    } else {
        by_sid_.clear();
        for (u64 i = 0; i < n && io.ok(); ++i) {
            u32 k = 0;
            s32 idx = -1;
            Binding b;
            io(k, idx, b.sid, b.sd, b.buf, b.buf_size);
            b.server = (idx >= 0 && static_cast<std::size_t>(idx) < servers_.size()) ? servers_[static_cast<std::size_t>(idx)].get() : nullptr;
            by_sid_[k] = b;
        }
    }
    io(sid_by_sd_, pending_, next_ticket_, modules_, next_module_id_);
    io(sound_ring_, sound_total_, sound_census_, unknown_, unknown_total_);

    for (auto& s : servers_) {
        const std::string tag = "iop-server " + std::string(s->name());
        io.section(tag.c_str());
        s->state(io, *this);
    }

    bool mixer = mixer_ != nullptr;
    io.expect(mixer, "SPU2 mixer presence (--sk mode)");
    if (mixer_) mixer_->state(io);

    io.section("memcard");
    memcard::Card* card = (config_.memcard && config_.memcard->slot1) ? config_.memcard->slot1.get() : nullptr;
    bool has_card = card != nullptr;
    io.expect(has_card, "memory card presence (--memcard: a card in the saver means a card here, any image)");
    if (card) card->state(io);
}

}  // namespace p3fes::hle::sif::detail
