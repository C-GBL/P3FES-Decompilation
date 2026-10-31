// cdvdfsv over CdvdHle (runtime/hle/cdvd.h). Command set and buffer layouts: srv_cdvdfsv.h.
//
// Read path (N-command 1): the request is handed to CdvdHle at once (it keeps libcdvd's single
// N-command slot); after IopConfig::cd_*_latency the IOP completes it (CdvdHle::service), then the
// sectors are in EE RAM (64-byte aligned buffers are read straight into guest memory; others go
// through a staging buffer and the head/tail block, exactly as cdvdfsv's readee splits them), the
// 144-byte head/tail block is DMA'd to request+16, the read position word to request+20, and the
// RPC end follows. The EE's own _sceCd_cd_read_intr / _sceCd_cd_callback (0x50F8A8 / 0x50F698) then
// signal sceCd_ncmd_semid and clear sceCd_c_cb_sem; CdvdHle's completion hooks only count here.
#include "srv_cdvdfsv.h"

#include <algorithm>
#include <cstring>
#include <string>

namespace p3fes::hle::sif::detail {

std::array<u8, 8> cdl_date_from_iso(std::span<const u8, 7> rec) {
    std::array<u8, 8> d{};
    const u32 year = 1900u + rec[0];
    d[7] = static_cast<u8>(year >> 8);
    d[6] = static_cast<u8>(year & 0xFFu);
    d[5] = rec[1];  // month
    d[4] = rec[2];  // day
    d[3] = rec[3];  // hour
    d[2] = rec[4];  // minute
    d[1] = rec[5];  // second
    return d;
}

std::array<u8, kCdlFileReplySize> encode_cdl_file(u32 lsn, u32 size, std::string_view identifier,
                                                  const std::array<u8, 8>& date, u32 flags) {
    std::array<u8, kCdlFileReplySize> b{};
    store32(b, 0, lsn);
    store32(b, 4, size);
    const std::size_t n = std::min<std::size_t>(identifier.size(), 15);
    std::memcpy(b.data() + 8, identifier.data(), n);
    std::memcpy(b.data() + 24, date.data(), date.size());
    store32(b, 32, flags);
    return b;
}

CdvdfsvServer::CdvdfsvServer(DiscSource* disc) {
    if (disc != nullptr) {
        CompletionHooks hooks;
        // Guest-visible effects come from the EE's end callbacks once the RPC end arrives; the hooks
        // are only an internal witness that CdvdHle delivered the completion (once per request).
        hooks.signal_ncmd_sema = [this](const NcmdCompletion&) { ++hook_signals_; };
        cdvd_ = std::make_unique<CdvdHle>(*disc, std::move(hooks));
    }
}

void CdvdfsvServer::reboot() {
    // cdvdfsv is an IOPRP310 boot module: it comes back with the IOP. An in-flight request dies with
    // the old IOP (its RPC end is never sent; IopCore dropped the ticket).
    if (pending_ && cdvd_) {
        cdvd_->break_ncmd();
        cdvd_->service();
    }
    pending_.reset();
    error_override_ = -1;
}

int CdvdfsvServer::error() const {
    if (error_override_ >= 0) return error_override_;
    return cdvd_ ? cdvd_->get_error() : cd::kErrRead;
}

bool CdvdfsvServer::call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) {
    if (!cdvd_ && !warned_no_disc_) {
        core.log("[iop] cdvdfsv: no disc attached (reads fail with SCECdErREAD, searches find nothing)");
        warned_no_disc_ = true;
    }
    switch (req.sid) {
    case cdvd_sid::kInit:
        if (req.fno != 0) break;
        // {ret, cdvdfsv version, cdvdman version, debug mode}. sceCdInit 0x510618..0x510690: 255 / 254 in
        // the debug word are special; versions with major < 2 make it return 2 (inf values: 0x0310).
        put_word(reply.rdata, 0, cdvd_ ? static_cast<u32>(cdvd_->init(static_cast<int>(req_word(req, 0)))) : 1u);
        put_word(reply.rdata, 4, 0x0310u);
        put_word(reply.rdata, 8, 0x0310u);
        put_word(reply.rdata, 12, 0);
        return true;
    case cdvd_sid::kDiskReady:
    case cdvd_sid::kDiskReadyOld:
        if (req.fno != 0) break;
        put_word(reply.rdata, 0, static_cast<u32>(cd::kReady));
        return true;
    case cdvd_sid::kScmd:
        scmd(core, req, reply);
        return true;
    case cdvd_sid::kNcmd:
        return ncmd(core, req, reply, ticket);
    case cdvd_sid::kSearch:
        search(core, req, reply);
        return true;
    default:
        break;
    }
    core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "cdvdfsv function not modelled (answered 0)");
    put_word(reply.rdata, 0, 0);
    return true;
}

void CdvdfsvServer::scmd(IopCore& core, const RpcRequest& req, RpcReply& reply) {
    u32 r = 0;
    switch (req.fno) {
    case 3:  // sceCdGetDiskType
        r = static_cast<u32>(cd::kDiskTypePs2Dvd);
        break;
    case 4:  // sceCdGetError
        r = static_cast<u32>(error());
        break;
    case 12:  // sceCdStatus (no caller in the game; CdvdHle values are inferred)
        r = cdvd_ ? static_cast<u32>(cdvd_->status()) : static_cast<u32>(cd::kStatPause);
        break;
    case 22:  // sceCdBreak: the in-flight N-command completes at the next tick with SCECdErABRT
        r = cdvd_ ? static_cast<u32>(cdvd_->break_ncmd()) : 1u;
        if (pending_) pending_->deadline = 0;
        break;
    case 34:  // sceCdMmode
        r = cdvd_ ? static_cast<u32>(cdvd_->mmode(static_cast<int>(req_word(req, 0)))) : 1u;
        break;
    default:
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "cdvdfsv S-command not modelled (answered 0)");
        break;
    }
    put_word(reply.rdata, 0, r);
}

bool CdvdfsvServer::ncmd(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 ticket) {
    switch (req.fno) {
    case 14:  // N-command disk ready (sceCdRead pre-check 0x5100B0: 6 = not ready)
        put_word(reply.rdata, 0, static_cast<u32>(cd::kReady));
        return true;
    case 1:
    case 5:
        break;
    default:
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "cdvdfsv N-command not modelled (answered 0)");
        put_word(reply.rdata, 0, 0);
        return true;
    }

    Pending p;
    p.ticket = ticket;
    p.kind = req.fno == 1 ? NcmdKind::Read : NcmdKind::Seek;
    p.lsn = req_word(req, 0);
    if (p.kind == NcmdKind::Read) {
        p.sectors = req_word(req, 4);
        p.paddr = req_word(req, 8);
        p.remain_ee = req_word(req, 16);
        p.readpos_ee = req_word(req, 20);
    }
    const IopConfig& cfg = core.config();
    // At least one cycle: the completion is never delivered inside the issuing syscall (an actual drive
    // takes time; the EE polls sceCdSync(1) afterwards, srd_exec_dvd 0x558138).
    p.deadline = core.now() + std::max<u64>(1, cfg.cd_fixed_latency_cycles + cfg.cd_cycles_per_sector * p.sectors);

    bool accepted = false;
    if (cdvd_ && !pending_) {
        Result<Issue> r = Error{FormatError::Unsupported, "unset"};
        if (p.kind == NcmdKind::Seek) {
            r = cdvd_->seek(p.lsn);
        } else {
            ReadMode mode;
            mode.trycount = req.data.size() > 12 ? req.data[12] : 0;
            mode.spindlctrl = req.data.size() > 13 ? req.data[13] : 0;
            mode.datapattern = req.data.size() > 14 ? req.data[14] : 0;
            const u64 bytes = static_cast<u64>(p.sectors) * kSectorSize;
            const bool aligned = (p.paddr & 63u) == 0;
            std::span<std::byte> dst;
            if (aligned) {
                if (auto g = guest_read_buffer(core.ee(), p.paddr, p.sectors)) dst = g.value();
            } else if (bytes <= EEMemory::kMainRamSize) {
                p.staged = true;
                p.staging.resize(static_cast<std::size_t>(bytes));
                dst = p.staging;
            }
            if (dst.empty() && p.sectors != 0) {
                r = Error{FormatError::Overrun, "sceCdRead buffer is not inside EE memory"};
            } else {
                r = cdvd_->read(p.lsn, p.sectors, dst, mode);
            }
        }
        if (!r) {
            core.log(std::string("[iop] cdvdfsv: N-command refused: ") + std::string(formats::error_name(r.code())) + ": " + r.detail());
        } else if (r.value() == Issue::Busy) {
            core.log("[iop] cdvdfsv: N-command while one is in flight (refused)");
        } else {
            accepted = true;
        }
    } else if (pending_) {
        core.log("[iop] cdvdfsv: N-command while one is in flight (refused)");
    }

    if (!accepted) {
        // The EE still gets its RPC end (the call is asynchronous with an end callback) and then sees
        // the failure through sceCdGetError (srd_check_dvd_error 0x557FE8).
        error_override_ = cd::kErrRead;
        build_completion(p, false, reply);
        if (p.kind == NcmdKind::Read) report_read(core, p, cd::kErrRead);
        return true;
    }
    error_override_ = -1;
    if (p.kind == NcmdKind::Read) {
        ++core.stats().cd_reads;
        core.stats().cd_sectors += p.sectors;
    }
    pending_ = std::move(p);
    return false;
}

void CdvdfsvServer::tick(IopCore& core, u64 now, const Timebase& /*tb*/) {
    if (pending_ && now >= pending_->deadline) finish_pending(core);
}

u64 CdvdfsvServer::next_deadline() const { return pending_ ? pending_->deadline : kNever; }

void CdvdfsvServer::finish_pending(IopCore& core) {
    Pending p = std::move(*pending_);
    pending_.reset();
    if (cdvd_ && cdvd_->busy()) cdvd_->service();  // completes now (CdvdHle latency 0)
    if (p.kind == NcmdKind::Read) report_read(core, p, error());
    RpcReply reply;
    build_completion(p, error() == cd::kErrNone, reply);
    core.complete(p.ticket, std::move(reply));
}

void CdvdfsvServer::report_read(IopCore& core, const Pending& p, int err) {
    const auto& sink = core.config().cd_read_sink;
    if (!sink) return;
    CdReadEvent ev;
    ev.lsn = p.lsn;
    ev.sectors = p.sectors;
    ev.dst = p.paddr;
    ev.error = err;
    ev.cycle = core.now();
    ev.vblank = core.time().vblanks;
    if (err == cd::kErrNone) {
        // Read only: the bytes the drive delivered, where CdvdHle put them (the staging copy, or guest RAM).
        if (p.staged) {
            ev.data = p.staging;
        } else if (auto g = guest_read_buffer(core.ee(), p.paddr, p.sectors)) {
            ev.data = g.value().first(static_cast<std::size_t>(p.sectors) * kSectorSize);
        }
    }
    sink(ev);
}

void CdvdfsvServer::build_completion(const Pending& p, bool ok, RpcReply& reply) {
    if (p.kind != NcmdKind::Read) return;  // seek: just the RPC end
    const u32 bytes = p.sectors * kSectorSize;
    const UnalignedSplit s = split_unaligned(p.paddr, ok ? bytes : 0u);
    store32(eereadx_, 0, s.head);
    store32(eereadx_, 4, s.tail);
    store32(eereadx_, 8, p.paddr);
    store32(eereadx_, 12, ok ? s.tail_addr : (p.paddr + bytes) & ~63u);
    if (ok && p.staged) {
        const u8* src = reinterpret_cast<const u8*>(p.staging.data());
        std::memcpy(eereadx_.data() + 16, src, s.head);
        if (s.body) reply.writes.push_back(EeWrite{p.paddr + s.head, std::vector<u8>(src + s.head, src + s.head + s.body)});
        std::memcpy(eereadx_.data() + 80, src + s.head + s.body, s.tail);
    }
    reply.writes.push_back(EeWrite{p.remain_ee, std::vector<u8>(eereadx_.begin(), eereadx_.end())});
    std::vector<u8> pos(4, 0);
    store32(pos, 0, ok ? bytes : 0u);  // cdvdfsv's read position word (sceCdGetReadPos)
    reply.writes.push_back(EeWrite{p.readpos_ee, std::move(pos)});
}

void CdvdfsvServer::search(IopCore& core, const RpcRequest& req, RpcReply& reply) {
    // Only the dual-layer-aware 300-byte form is sent by this game (sceCdLayerSearchFile 0x50FC38).
    if (req.data.size() < kSearchPacketSize) {
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, static_cast<u32>(req.data.size()),
                          "sceCdSearchFile packet size other than 300 (answered not found)");
        put_word(reply.rdata, 0, 0);
        return;
    }
    const std::string path = c_string(req.data, kSearchPath, 256);
    const u32 eedest = req_word(req, kSearchEeDest);
    const u32 layer = req_word(req, kSearchLayer);
    // What the IOP's copy of the packet holds; DMA'd back even when nothing is found.
    std::array<u8, kCdlFileReplySize> fp{};
    std::memcpy(fp.data(), req.data.data(), fp.size());
    u32 found = 0;
    if (cdvd_ && layer == 0) {  // single-layer disc (DVD-5): layer 1 finds nothing (inf)
        auto r = cdvd_->search_file(path);
        if (!r) {
            core.log("[iop] cdvdfsv: search \"" + path + "\" failed: " + std::string(formats::error_name(r.code())) + ": " + r.detail());
        } else if (r->issue == Issue::Busy) {
            core.log("[iop] cdvdfsv: search \"" + path + "\" while an N-command is in flight (not found)");
        } else if (r->file) {
            // The date from the ISO directory record (cdvdman's mapping, cdl_date_from_iso); the PCSX2 first_flip
            // state holds it for the three CVMs and flag 0 (obs, 0x7A2878/0x7A28C0/0x7A2908).
            fp = encode_cdl_file(r->file->lsn, r->file->size, r->file->identifier,
                                 cdl_date_from_iso(std::span<const u8, 7>(r->file->recorded)), 0);
            found = 1;
        }
    }
    if (core.config().trace) core.log("[iop] cdvdfsv: search \"" + path + "\" -> " + (found ? "found" : "not found"));
    reply.writes.push_back(EeWrite{eedest, std::vector<u8>(fp.begin(), fp.end())});
    put_word(reply.rdata, 0, found);
}

}  // namespace p3fes::hle::sif::detail
