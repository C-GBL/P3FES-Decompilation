// IOP core: IOP RAM + heap, sifcmd system commands, sifrpc bind/call/rdata, the SIF0 queue, reboot.
// Protocol facts are the game's (runtime/hle/sif/include/p3fes/hle/sif/protocol.h cites each).
#include "iop_core.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

#include "p3fes/audio/spu2_voice.h"
#include "srv_adxi.h"
#include "srv_cdvdfsv.h"
#include "srv_padman.h"
#include "srv_sdr.h"

namespace p3fes::hle::sif::detail {

std::string hex32(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%08X", v);
    return b;
}

// ---- IopRam ------------------------------------------------------------------------------------

IopRam::IopRam() : ram_(kIopRamSize, 0) {}

static u32 iop_phys(u32 addr) { return addr & (kIopRamSize - 1u); }  // kseg mirrors and 2 MiB wrap

u8* IopRam::at(u32 addr, u32 len) {
    const u32 a = iop_phys(addr);
    if (static_cast<u64>(a) + len > ram_.size()) return nullptr;
    return ram_.data() + a;
}
const u8* IopRam::at(u32 addr, u32 len) const {
    const u32 a = iop_phys(addr);
    if (static_cast<u64>(a) + len > ram_.size()) return nullptr;
    return ram_.data() + a;
}

static u32 round_up(u32 v, u32 a) { return (v + a - 1u) & ~(a - 1u); }

bool IopRam::overlaps(u32 start, u32 size) const {
    const u64 end = static_cast<u64>(start) + size;
    if (end > kIopRamSize) return true;
    if (start < kIopServerArenaEnd && end > kIopServerArena && start < arena_next_) return true;  // the server arena in use
    if (start < kIopCmdBuffer + kIopCmdBufferSize && end > kIopCmdBuffer) return true;
    for (const auto& [bs, bl] : blocks_)
        if (start < bs + bl && end > bs) return true;
    return false;
}

u32 IopRam::alloc(u32 size, u32 mode, u32 addr) {
    if (size == 0) return 0;
    if (mode == 2) {
        // At `addr` exactly: anywhere in RAM that no block, the live server arena or the sifcmd buffer uses.
        const u32 want = iop_phys(addr) & ~15u;
        const u32 need = round_up(size, 16u);
        if (want == 0 || overlaps(want, need)) return 0;
        blocks_[want] = need;
        return want;
    }
    if (size > heap_end_ - heap_begin_) return 0;
    const u32 need = round_up(size, kIopHeapAlign);
    // Gaps between blocks in address order.
    std::vector<std::pair<u32, u32>> gaps;  // start, size
    u32 cur = heap_begin_;
    for (const auto& [start, len] : blocks_) {
        if (start + len <= heap_begin_) continue;
        if (start >= heap_end_) break;
        if (start > cur) gaps.emplace_back(cur, start - cur);
        cur = std::max(cur, start + len);
    }
    if (heap_end_ > cur) gaps.emplace_back(cur, heap_end_ - cur);

    u32 got = 0;
    if (mode == 1) {
        for (auto it = gaps.rbegin(); it != gaps.rend() && got == 0; ++it)
            if (it->second >= need) got = it->first + it->second - need;
    } else {
        for (const auto& [gs, gl] : gaps)
            if (gl >= need) {
                got = gs;
                break;
            }
    }
    if (got == 0) return 0;
    blocks_[got] = need;
    return got;
}

u32 IopRam::alloc_in(u32 lo, u32 hi, u32 size) {
    if (size == 0 || lo >= hi) return 0;
    const u32 need = round_up(size, kIopHeapAlign);
    u32 cur = round_up(lo, kIopHeapAlign);
    for (const auto& [start, len] : blocks_) {
        if (start + len <= cur) continue;
        if (start >= hi) break;
        if (start >= cur + need) break;
        cur = round_up(start + len, kIopHeapAlign);
    }
    if (static_cast<u64>(cur) + need > hi) return 0;
    blocks_[cur] = need;
    return cur;
}

bool IopRam::free(u32 addr) { return blocks_.erase(iop_phys(addr)) != 0; }

u32 IopRam::free_total() const {
    u32 used = 0;
    for (const auto& [start, len] : blocks_) {
        const u32 b = std::max(start, heap_begin_), e = std::min(start + len, heap_end_);
        if (e > b) used += e - b;
    }
    return (heap_end_ - heap_begin_) - used;
}

u32 IopRam::free_max() const {
    u32 best = 0, cur = heap_begin_;
    for (const auto& [start, len] : blocks_) {
        if (start + len <= heap_begin_) continue;
        if (start >= heap_end_) break;
        if (start > cur) best = std::max(best, start - cur);
        cur = std::max(cur, start + len);
    }
    return std::max(best, heap_end_ > cur ? heap_end_ - cur : 0u);
}

u32 IopRam::block_size(u32 addr) const {
    auto it = blocks_.find(iop_phys(addr));
    return it == blocks_.end() ? 0 : it->second;
}

void IopRam::reset_heap() { blocks_.clear(); }

u32 IopRam::arena_alloc(u32 size) {
    const u32 need = round_up(std::max<u32>(size, 16u), 64u);
    if (arena_next_ + need > kIopServerArenaEnd) return 0;
    const u32 a = arena_next_;
    arena_next_ += need;
    return a;
}

// ---- IopCore -------------------------------------------------------------------------------------

IopCore::IopCore(EEMemory& mem, HwBus& bus, IopConfig config, DiscSource* disc)
    : mem_(mem), bus_(bus), config_(std::move(config)) {
    next_module_id_ = config_.first_module_id;
    // IopLayout::Pcsx2: the game's heap allocations start where PCSX2's first one lands (srv_sdr.h).
    if (config_.iop_layout == IopLayout::Pcsx2) ram_.set_heap(kIopHeapBeginPcsx2, kIopHeapEndPcsx2);
    register_servers(disc);
}

IopCore::~IopCore() = default;

Binding& IopCore::bind_server(u32 sid, RpcServer* server, u32 buf_size) {
    Binding b;
    b.sid = sid;
    b.server = server;
    b.sd = ram_.arena_alloc(64);      // stands in for the module's SifRpcServerData_t
    b.buf = ram_.arena_alloc(buf_size);
    b.buf_size = buf_size;
    sid_by_sd_[b.sd] = sid;
    return by_sid_[sid] = b;
}

void IopCore::register_servers(DiscSource* disc) {
    auto add = [this](std::unique_ptr<RpcServer> s) -> RpcServer* {
        servers_.push_back(std::move(s));
        return servers_.back().get();
    };
    // Receive-buffer sizes cover the largest send each client makes (`12` §2.1, obs sizes).
    bind_server(0x80000001u, add(make_fileio_server()), 4096);   // fileio: up to 3092 (sceMount)
    bind_server(0x80000003u, add(make_heap_server()), 512);      // heaplib: <= 4 + 252
    bind_server(0x80000006u, add(make_loadfile_server()), 1024); // loadfile: 512

    auto cd = std::make_unique<CdvdfsvServer>(disc);
    cdvd_ = cd.get();
    RpcServer* cds = add(std::move(cd));
    bind_server(cdvd_sid::kInit, cds, 256);
    bind_server(cdvd_sid::kScmd, cds, 256);
    bind_server(cdvd_sid::kNcmd, cds, 256);
    bind_server(cdvd_sid::kSearch, cds, 512);
    bind_server(cdvd_sid::kDiskReadyOld, cds, 256);
    bind_server(cdvd_sid::kDiskReady, cds, 256);

    auto pad = std::make_unique<PadmanServer>();
    pad_ = pad.get();
    RpcServer* pads = add(std::move(pad));
    bind_server(pad_sid::kMain, pads, 256);
    bind_server(pad_sid::kSecond, pads, 256);

    RpcServer* dbc = add(make_dbcman_server());
    bind_server(0x80001300u, dbc, 256);
    bind_server(0x8000131Cu, dbc, 2048);  // 1168-byte page packets
    bind_server(0x8000131Eu, dbc, 256);
    bind_server(0x8000131Fu, dbc, 256);

    auto sdr = make_sdrdrv_server(disc);
    sdr_ = sdr.get();
    servers_.push_back(std::move(sdr));
    bind_server(0x80000701u, sdr_, 2048);
    if (config_.sk_mode == SkMode::Modules) {
        mixer_ = std::make_unique<audio::Spu2Mixer>();
        sdr_->set_mixer(mixer_.get());
    }
    // CRI_ADXI's RPC buffer is 256 bytes (IRX 0xE190..0xE290); DTX_CallUrpc sends <= 64 words.
    auto adxi = make_adxi_server();
    adxi_ = adxi.get();
    servers_.push_back(std::move(adxi));
    bind_server(0x90000200u, adxi_, 256);
}

Binding& IopCore::binding_for(u32 sid) {
    auto it = by_sid_.find(sid);
    if (it != by_sid_.end()) return it->second;
    note_unknown(UnknownEvent::Kind::Server, sid, 0, "bind to an RPC server the HLE does not model (answered)");
    return bind_server(sid, nullptr, 4096);
}

void IopCore::log(std::string_view line) const {
    if (config_.log) {
        config_.log(line);
        return;
    }
    std::fprintf(stderr, "%.*s\n", static_cast<int>(line.size()), line.data());
}

void IopCore::note_unknown(UnknownEvent::Kind kind, u32 id, u32 fno, std::string_view what) {
    ++unknown_total_;
    const auto key = std::make_pair(static_cast<int>(kind), (static_cast<u64>(id) << 32) | fno);
    auto [it, inserted] = unknown_.try_emplace(key, UnknownEvent{kind, id, fno, 0});
    ++it->second.count;
    if (inserted) {
        static constexpr const char* kKind[] = {"server", "function", "command", "dma"};
        log("[iop] UNKNOWN " + std::string(kKind[static_cast<int>(kind)]) + " id=" + hex32(id) + " fn=" + hex32(fno) +
            ": " + std::string(what));
    }
}

std::vector<UnknownEvent> IopCore::unknown_events() const {
    std::vector<UnknownEvent> v;
    for (const auto& e : unknown_) v.push_back(e.second);
    return v;
}

void IopCore::record_sound(const SoundRequest& r0) {
    SoundRequest r = r0;
    r.vblank = time().vblanks;
    sound_ring_[sound_total_ % sound_ring_.size()] = r;
    ++sound_total_;
    ++sound_census_[sound_verb(r)];
    if (config_.sound_sink) config_.sound_sink(r);
}

std::vector<SoundRequest> IopCore::sound_log() const {
    std::vector<SoundRequest> v;
    const u64 n = std::min<u64>(sound_total_, sound_ring_.size());
    for (u64 i = sound_total_ - n; i < sound_total_; ++i) v.push_back(sound_ring_[i % sound_ring_.size()]);
    return v;
}

CdvdHle* IopCore::cdvd() { return cdvd_ ? cdvd_->cdvd() : nullptr; }

void IopCore::set_pad_input(unsigned port, const PadInput& in) {
    if (pad_) pad_->set_input(port, in);
}

void IopCore::set_audio_output(audio::AudioSink* mix, audio::StreamTap* tap) {
    if (mixer_) {
        // Modules mode: the PSM stream and the SPU2 voices meet in the mixer, which pushes the sum.
        mixer_->set_sink(mix);
        if (adxi_) adxi_->set_output(&mixer_->stream_sink(), tap);
        return;
    }
    if (adxi_) adxi_->set_output(mix, tap);
}

void IopCore::flush_audio() {
    if (mixer_) mixer_->finish();
}

SkStats IopCore::sk_stats() const { return sdr_ ? sdr_->sk_stats() : SkStats{}; }

void IopCore::rebind_server(u32 sid, u32 sd, u32 buf, u32 buf_size) {
    const auto it = by_sid_.find(sid);
    if (it == by_sid_.end()) return;
    Binding& b = it->second;
    sid_by_sd_.erase(b.sd);
    b.sd = sd;
    b.buf = buf;
    b.buf_size = buf_size;
    sid_by_sd_[sd] = sid;
}

std::optional<s32> IopCore::load_sk_module(std::string_view path, std::string_view args) {
    return sdr_ ? sdr_->on_module_load(*this, path, args) : std::nullopt;
}

void IopCore::record_event(const SoundRequest& r0) {
    SoundRequest r = r0;
    r.vblank = time().vblanks;
    ++sound_census_[sound_verb(r)];
    if (config_.sound_sink) config_.sound_sink(r);
}

AdxiStats IopCore::adxi_stats() const { return adxi_ ? adxi_->stats() : AdxiStats{}; }

void IopCore::queue_ee_write(u32 addr, std::vector<u8> bytes) {
    Sif0Item it;
    it.not_before = now();
    it.writes.push_back(EeWrite{addr, std::move(bytes)});
    push(std::move(it));
}

bool IopCore::ee_store(u32 addr, std::span<const u8> bytes) {
    if (bytes.empty()) return true;
    u8* p = mem_.resolve(addr, static_cast<u32>(bytes.size()));
    if (p == nullptr) {
        ++stats_.ee_write_failures;
        note_unknown(UnknownEvent::Kind::Dma, addr, static_cast<u32>(bytes.size()), "IOP -> EE write outside EE memory (dropped)");
        return false;
    }
    std::memcpy(p, bytes.data(), bytes.size());
    ++stats_.sif0_data_writes;
    return true;
}

bool IopCore::ee_load(u32 addr, std::span<u8> out) const {
    const u8* p = mem_.resolve(addr, static_cast<u32>(out.size()));
    if (p == nullptr) return false;
    std::memcpy(out.data(), p, out.size());
    return true;
}

// ---- SIF1 (EE -> IOP) ------------------------------------------------------------------------------

void IopCore::sif1_receive(u32 iop_dest, std::span<const u8> bytes, u32 attr) {
    ++stats_.sif1_transfers;
    u8* p = ram_.at(iop_dest, static_cast<u32>(bytes.size()));
    if (p == nullptr) {
        note_unknown(UnknownEvent::Kind::Dma, iop_dest, static_cast<u32>(bytes.size()), "EE -> IOP DMA outside IOP RAM (dropped)");
        return;
    }
    std::memcpy(p, bytes.data(), bytes.size());
    // The IOP's sifcmd takes an interrupt for transfers marked INT_O and parses its receive buffer.
    if ((iop_dest & (kIopRamSize - 1u)) != kIopCmdBuffer || (attr & dma_attr::kIntO) == 0) return;
    if (rebooting_) {
        log("[iop] command packet while the IOP reboots: ignored");
        return;
    }
    const u32 psize = p[0];
    if (psize < kCmdHeaderSize || psize > kCmdPacketMax || psize > bytes.size()) {
        note_unknown(UnknownEvent::Kind::Command, psize, 0, "malformed command packet size (ignored)");
        return;
    }
    std::array<u8, kCmdPacketMax> pkt{};
    std::memcpy(pkt.data(), p, psize);
    on_command(std::span<const u8>(pkt.data(), psize));
}

void IopCore::on_command(std::span<const u8> pkt) {
    ++stats_.commands;
    const CmdHeader h = decode_cmd_header(pkt);
    if (config_.trace) log("[iop] cmd " + hex32(h.cid) + " psize " + std::to_string(h.psize));
    switch (h.cid) {
    case cid::kChangeSaddr:
        ee_recv_buf_ = load32(pkt, kChangeSaddrBuf);
        break;
    case cid::kSetSreg:
        iop_sregs_[load32(pkt, kSetSregIndex) & 31u] = load32(pkt, kSetSregValue);
        break;
    case cid::kInitCmd:
        if (h.opt == 0) {
            // sifcmd init from the EE (sceSifInitCmd 0x5063BC): remember its receive buffer.
            ee_recv_buf_ = load32(pkt, kChangeSaddrBuf);
        } else {
            // sifrpc init (sceSifInitRpc 0x5069F4, opt 1): the IOP's sifrpc answers SET_SREG(RPCINIT, 1);
            // the EE spins on sceSifGetSreg(0) (0x506A00).
            std::array<u8, kSetSregSize - kCmdHeaderSize> payload{};
            store32(payload, 0, 0);  // SIF_SREG_RPCINIT
            store32(payload, 4, 1);
            send_command(cid::kSetSreg, payload);
        }
        break;
    case cid::kResetCmd:
        begin_reboot(pkt);
        break;
    case cid::kDmaSync:
        ++stats_.sync_packets;
        break;
    case cid::kRpcBind:
        on_bind(pkt);
        break;
    case cid::kRpcCall:
        on_call(pkt);
        break;
    case cid::kRpcRdata:
        on_rdata(pkt);
        break;
    default:
        // kRpcEnd (the IOP never calls EE servers), kPad (scePadEnd / cdvd_exit at shutdown), ...
        note_unknown(UnknownEvent::Kind::Command, h.cid, 0, "SIF command the IOP HLE does not handle (ignored)");
        break;
    }
}

void IopCore::on_bind(std::span<const u8> pkt) {
    ++stats_.binds;
    const RpcBind b = decode_rpc_bind(pkt);
    const Binding& s = binding_for(b.sid);
    if (config_.trace) log("[iop] bind " + hex32(b.sid) + " -> sd " + hex32(s.sd));
    // _request_end 0x506BA8, cid == BIND: cd->server = +36, cd->buf = +40. A non-zero server ends the
    // clients' bind loops (e.g. scePadInit 0x5111A4).
    RpcEnd e{b.rec_id, b.pkt_addr, b.rpc_id, b.client, cid::kRpcBind, s.sd, s.buf, 0};
    const RpcPacket p = encode_rpc_end(e);
    Sif0Item it;
    it.has_packet = true;
    std::memcpy(it.packet.data(), p.data(), p.size());
    it.packet_size = static_cast<u32>(p.size());
    it.not_before = now();
    push(std::move(it));
}

void IopCore::on_call(std::span<const u8> pkt) {
    ++stats_.calls;
    const RpcCall c = decode_rpc_call(pkt);
    auto sid_it = sid_by_sd_.find(c.server);
    if (sid_it == sid_by_sd_.end()) {
        note_unknown(UnknownEvent::Kind::Server, c.server, c.rpc_number, "call to an unbound server data address (answered with zeros)");
        Binding dummy;
        dummy.sd = c.server;
        finish_call(c, dummy, RpcReply{});
        return;
    }
    const Binding& b = by_sid_[sid_it->second];
    if (config_.trace) log("[iop] call " + hex32(b.sid) + " fn " + hex32(c.rpc_number) + " send " + std::to_string(c.send_size));
    if (c.send_size > b.buf_size)
        note_unknown(UnknownEvent::Kind::Function, b.sid, c.rpc_number, "send data larger than the modelled receive buffer");
    RpcRequest req;
    req.sid = b.sid;
    req.fno = c.rpc_number;
    const u32 n = std::min(c.send_size, b.buf_size);
    const u8* data = ram_.at(b.buf, n);
    req.data = data ? std::span<const u8>(data, n) : std::span<const u8>();
    req.data_iop = b.buf;
    req.recv_size = c.recv_size;
    req.recv_ee = c.recv_buf;
    req.client_ee = c.client;
    req.rmode = c.rmode;
    RpcReply reply;
    if (b.server == nullptr) {
        note_unknown(UnknownEvent::Kind::Function, b.sid, c.rpc_number, "call on an unmodelled server (answered with zeros)");
        finish_call(c, b, std::move(reply));
        return;
    }
    const u32 ticket = next_ticket_++;
    if (b.server->call(*this, req, reply, ticket)) {
        finish_call(c, b, std::move(reply));
    } else {
        pending_[ticket] = PendingCall{c, b.sid};
    }
}

void IopCore::complete(u32 ticket, RpcReply reply) {
    auto it = pending_.find(ticket);
    if (it == pending_.end()) return;  // dropped by a reboot
    const PendingCall p = it->second;
    pending_.erase(it);
    finish_call(p.call, by_sid_[p.sid], std::move(reply));
}

void IopCore::finish_call(const RpcCall& call, const Binding& b, RpcReply reply) {
    Sif0Item it;
    it.not_before = now();
    it.writes = std::move(reply.writes);
    const bool has_rdata = call.recv_size > 0 && call.recv_buf != 0;
    if (has_rdata) {
        reply.rdata.resize(call.recv_size, 0);  // inf: bytes past the server's answer read as 0
        it.writes.push_back(EeWrite{call.recv_buf, std::move(reply.rdata)});
    }
    RpcEnd e{call.rec_id, call.pkt_addr, call.rpc_id, call.client, cid::kRpcCall, b.sd, b.buf, 0};
    if (call.rmode != 0) {
        // RPC_END; the receive data travels as the command's extra data (dsize/dest in the header).
        const RpcPacket p = encode_rpc_end(e, has_rdata ? call.recv_size : 0, has_rdata ? call.recv_buf : 0);
        it.has_packet = true;
        std::memcpy(it.packet.data(), p.data(), p.size());
        it.packet_size = static_cast<u32>(p.size());
    } else {
        // NOWAIT without end function: no interrupt; the rend packet with rpc_id = rec_id = 0 lands on
        // the EE's request packet so sceSifCheckStatRpc 0x507430 sees the call done.
        e.rec_id = 0;
        e.rpc_id = 0;
        const RpcPacket p = encode_rpc_end(e);
        it.writes.push_back(EeWrite{call.pkt_addr, std::vector<u8>(p.begin(), p.end())});
    }
    push(std::move(it));
}

void IopCore::on_rdata(std::span<const u8> pkt) {
    // sceSifGetOtherData (no caller in this game, `12` §2.1): IOP RAM [src, src+size) -> EE dest.
    const RpcRdata r = decode_rpc_rdata(pkt);
    Sif0Item it;
    it.not_before = now();
    if (r.size > 0) {
        const u8* src = ram_.at(r.src, r.size);
        if (src) it.writes.push_back(EeWrite{r.dest, std::vector<u8>(src, src + r.size)});
        else note_unknown(UnknownEvent::Kind::Dma, r.src, r.size, "rdata source outside IOP RAM");
    }
    RpcEnd e{r.rec_id, r.pkt_addr, r.rpc_id, r.recv_data, cid::kRpcRdata, r.src, r.dest, r.size};
    const RpcPacket p = encode_rpc_end(e, r.size, r.dest);
    it.has_packet = true;
    std::memcpy(it.packet.data(), p.data(), p.size());
    it.packet_size = static_cast<u32>(p.size());
    push(std::move(it));
}

void IopCore::send_command(u32 command, std::span<const u8> payload, std::vector<EeWrite> writes, u32 opt) {
    Sif0Item it;
    it.not_before = now();
    const std::size_t psize = std::min(kCmdHeaderSize + payload.size(), kCmdPacketMax);
    const u32 dsize = writes.size() == 1 ? static_cast<u32>(writes[0].bytes.size()) : 0;
    const u32 dest = writes.size() == 1 ? writes[0].addr : 0;
    encode_cmd_header(CmdHeader{static_cast<u32>(psize), dsize, dest, command, opt}, it.packet);
    std::memcpy(it.packet.data() + kCmdHeaderSize, payload.data(), psize - kCmdHeaderSize);
    it.packet_size = static_cast<u32>(psize);
    it.has_packet = true;
    it.writes = std::move(writes);
    push(std::move(it));
}

void IopCore::push(Sif0Item item) { sif0_.push_back(std::move(item)); }

// ---- SIF0 (IOP -> EE) delivery --------------------------------------------------------------------

void IopCore::flush_sif0(bool& sif0_started) {
    const u64 t = now();
    while (!sif0_.empty()) {
        Sif0Item& it = sif0_.front();
        if (it.not_before > t) break;
        if (it.has_packet) {
            // One packet per armed chain; the EE's sceSifCmdIntrHdlr 0x5066B0 clears psize (byte 0) of
            // its buffer after copying the packet and re-arms with isceSifSetDChain (0x506724).
            if (!sif0_started || ee_recv_buf_ == 0) break;
            const u8* rb = mem_.resolve(ee_recv_buf_, 1);
            if (rb == nullptr) {
                note_unknown(UnknownEvent::Kind::Dma, ee_recv_buf_, 0, "EE receive buffer not in EE memory (packet dropped)");
                sif0_.pop_front();
                continue;
            }
            if (*rb != 0) break;
        }
        for (const EeWrite& w : it.writes) ee_store(w.addr, w.bytes);
        if (it.has_packet) {
            ee_store(ee_recv_buf_, std::span<const u8>(it.packet.data(), it.packet_size));
            sif0_started = false;
            ++stats_.sif0_packets;
            sif0_.pop_front();
            bus_.dma_complete(5);
            break;  // the chain ended (ERT): nothing more until the EE re-arms SIF0
        }
        sif0_.pop_front();
    }
}

u64 IopCore::next_event_cycles(bool sif0_started) const {
    u64 t = kNever;
    if (!sif0_.empty()) {
        const Sif0Item& f = sif0_.front();
        if (f.not_before > now()) {
            t = f.not_before;
        } else if (!f.has_packet) {
            t = now();
        } else if (sif0_started && ee_recv_buf_ != 0) {
            const u8* rb = mem_.resolve(ee_recv_buf_, 1);
            if (rb == nullptr || *rb == 0) t = now();
        }
    }
    if (rebooting_) t = std::min(t, reboot_deadline_);
    for (const auto& s : servers_) t = std::min(t, s->next_deadline());
    return t;
}

void IopCore::tick() {
    if (rebooting_ && now() >= reboot_deadline_) finish_reboot();
    if (rebooting_) return;
    for (const auto& s : servers_) s->tick(*this, now(), time());
    // After the PSM model rendered its due passes: emit the mixer's passes two passes behind the clock.
    if (mixer_) mixer_->flush(audio::frames_at_cycles(now()));
}

// ---- reboot ----------------------------------------------------------------------------------------

void IopCore::begin_reboot(std::span<const u8> pkt) {
    const u32 arglen = std::min<u32>(load32(pkt, kResetArglen), 80u);
    std::string arg;
    for (u32 i = 0; i < arglen && kResetArg + i < pkt.size(); ++i) arg.push_back(static_cast<char>(pkt[kResetArg + i]));
    log("[iop] reboot requested: \"" + arg + "\" mode " + std::to_string(load32(pkt, kResetMode)));
    rebooting_ = true;
    // Strictly later than now: the EE clears SMFLAG SIFINIT/CMDINIT after this DMA returns
    // (sceSifResetIop 0x50C94C/0x50C958), so the flags must come back after those writes.
    reboot_deadline_ = now() + std::max<u64>(config_.reboot_cycles, 1);
    sif0_.clear();
    pending_.clear();
    ++stats_.reboots;
}

void IopCore::finish_reboot() {
    rebooting_ = false;
    reboot_deadline_ = kNever;
    ram_.reset_heap();
    modules_.clear();
    next_module_id_ = config_.first_module_id;
    ee_recv_buf_ = 0;
    iop_sregs_.fill(0);
    for (const auto& s : servers_) s->reboot();
    // IOPRP310's SIFMAN/SIFCMD/EESYNC come up: SIFINIT, the sifcmd buffer in SMCOM + CMDINIT, BOOTEND.
    regs_.smcom = kIopCmdBuffer;
    regs_.smflg |= flag::kAllBooted;
    log("[iop] reboot complete (SMFLAG " + hex32(regs_.smflg) + ")");
}

}  // namespace p3fes::hle::sif::detail

// ---- IopHle --------------------------------------------------------------------------------------

namespace p3fes::hle::sif {

IopHle::IopHle(std::unique_ptr<detail::IopCore> core) : core_(std::move(core)) {}
IopHle::~IopHle() = default;

void IopHle::set_pad_input(unsigned port, const PadInput& in) { core_->set_pad_input(port, in); }
const IopStats& IopHle::stats() const { return core_->stats(); }
std::vector<LoadedModule> IopHle::modules() const { return core_->modules(); }
std::vector<SoundRequest> IopHle::sound_log() const { return core_->sound_log(); }
u64 IopHle::sound_requests() const { return core_->sound_requests(); }
std::map<std::string, u64> IopHle::sound_census() const { return core_->sound_census(); }

// Verb names follow docs/ANALYSIS/19 §1.1 (EE wrappers sceSdRemote 0x5129C0, sceSkSs* 0x51DB00..0x51E0DC,
// DTX_CallUrpc 0x559C10); the SK selectors are block word0 >> 24 (module) and word1 (function).
std::string sound_verb(const SoundRequest& r) {
    char b[48];
    if (r.sid == 0x90000200u) {
        if (r.fno == 2) return "DTX create";
        if (r.fno == 3) return "DTX destroy";
        if (r.fno == 0x8000) return "RNA start";
        if (r.fno == 0x8001) return "RNA stop";
        if (r.fno >= 1024 && r.fno < 1024 + 64) return "DTX urpc";
        std::snprintf(b, sizeof b, "DTX %u", r.fno);
        return b;
    }
    if (r.sid == 0) return r.fno == 1 ? "KON" : r.fno == 2 ? "KOFF" : r.fno == 3 ? "CORE" : "voice";
    const u32 code = r.fno & 0xFFF0u;
    if (code != 0x90F0u) {
        switch (code) {
        case 0x8000u: return "SdInit";
        case 0x8010u: return "SetParam";
        case 0x8020u: return "GetParam";
        case 0x8030u: return "SetSwitch";
        case 0x8040u: return "GetSwitch";
        case 0x8050u: return "SetAddr";
        case 0x8060u: return "GetAddr";
        case 0x8070u: return "SetCoreAttr";
        case 0x8080u: return "GetCoreAttr";
        case 0x8F10u: return "SetThreadPriorities";
        case 0xE620u: return "CallbackInit";
        case 0xE630u: return "CallbackDelete";
        default:
            std::snprintf(b, sizeof b, "libsd 0x%04X", r.fno);
            return b;
        }
    }
    const u32 module = (r.sk_module >> 24) & 0x7Fu;
    if (module == 0) {
        if (r.sk_function == 2) {
            std::snprintf(b, sizeof b, "SOUND_Control 0x%X", r.args[1]);
            return b;
        }
        if (r.sk_function == 10) return "SOUND_Send";
        std::snprintf(b, sizeof b, "SOUND %u", r.sk_function);
        return b;
    }
    const char* mod = module == 1 ? "HSYNTH" : module == 4 ? "SESQ" : nullptr;
    if (!mod) {
        std::snprintf(b, sizeof b, "SK %u/%u", module, r.sk_function);
        return b;
    }
    switch (r.sk_function) {
    case 0: std::snprintf(b, sizeof b, "%s_Bind %u", mod, r.args[0]); return b;
    case 1: std::snprintf(b, sizeof b, "%s_Unbind %u", mod, r.args[0]); return b;
    case 2:
        if (module == 4) {
            const char* cmd = r.args[1] == 0 || r.args[1] == 7 ? "play" : r.args[1] == 2 ? "stop" : nullptr;
            if (cmd) {
                std::snprintf(b, sizeof b, "SESQ_Control %s", cmd);
                return b;
            }
            std::snprintf(b, sizeof b, "SESQ_Control %u", r.args[1]);
            return b;
        }
        return "HSYNTH 2";
    case 3: return module == 4 ? "SESQ_Status" : "HSYNTH 3";
    default:
        std::snprintf(b, sizeof b, "%s %u", mod, r.sk_function);
        return b;
    }
}
std::vector<UnknownEvent> IopHle::unknown_events() const { return core_->unknown_events(); }
u64 IopHle::unknown_total() const { return core_->unknown_total(); }
bool IopHle::rebooting() const { return core_->rebooting(); }
u32 IopHle::ee_receive_buffer() const { return core_->ee_receive_buffer(); }
std::span<const u8> IopHle::ram() const { return core_->ram().image(); }
u32 IopHle::heap_free_total() const { return core_->ram().free_total(); }
CdvdHle* IopHle::cdvd() { return core_->cdvd(); }
void IopHle::set_audio_output(audio::AudioSink* mix, audio::StreamTap* tap) { core_->set_audio_output(mix, tap); }
AdxiStats IopHle::adxi_stats() const { return core_->adxi_stats(); }
void IopHle::flush_audio() { core_->flush_audio(); }
SkStats IopHle::sk_stats() const { return core_->sk_stats(); }

}  // namespace p3fes::hle::sif
