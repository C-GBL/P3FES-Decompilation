// CRI_ADXI.IRX model (srv_adxi.h; docs/ANALYSIS/16_iop_audio_modules.md). Tags in comments: IRX
// offsets are module-relative (`IRX 0x...`), EE addresses are SLUS_216.21 VAs.
#include "srv_adxi.h"

#include <algorithm>
#include <cstring>

#include "p3fes/audio/audio_sink.h"
#include "p3fes/prof.h"

namespace p3fes::hle::sif::detail {
namespace {

// RNA command ids (EE ps2rna_sndcbf 0x55FC00 -> IOP 0xEA0 switch, 14 cases).
enum RnaCmd : u32 {
    kCmdStart = 0, kCmdStop = 1, kCmdPlaySw = 2, kCmdNumChan = 3, kCmdSfreq = 4, kCmdVolume = 5,
    kCmdDiscard = 8, kCmdPan = 9, kCmdRoute = 10, kCmdPauseAll = 11, kCmdCore = 12, kCmdOutPan = 13,
};

// PSM pan tables (IRX .data 0xD310 / 0xD38C, 31 entries for -15..15; obs).
constexpr std::array<u32, 31> kPanLaw = {255, 254, 253, 251, 249, 246, 242, 238, 232, 227, 220, 213, 206, 198, 189, 180,
                                         170, 160, 149, 138, 127, 115, 103, 91,  78,  65,  53,  39,  26,  13,  0};
constexpr std::array<u32, 31> kOutPanLaw = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                                            238, 221, 204, 187, 170, 153, 136, 119, 102, 85,  68,  51,  34,  17,  0};

u32 rd32(IopCore& core, u32 a) {
    const u8* p = core.ram().at(a, 4);
    u32 v = 0;
    if (p) std::memcpy(&v, p, 4);
    return v;
}
void wr32(IopCore& core, u32 a, u32 v) {
    if (u8* p = core.ram().at(a, 4)) std::memcpy(p, &v, 4);
}
u32 word(std::span<const u8> b, std::size_t i) { return load32(b, 4 * i); }

}  // namespace

u32 psm_side_gain(s32 vol, s32 pan, s32 mpan, bool right) {
    // IRX 0x27E4 (obs): x = vol * law[15+pan] * outlaw[15+mpan] (left; right uses 15-pan, 15-mpan),
    // q = (10x * 0x81018203) >> 47 (~ 10x / 65025), result = q / 10 rounded half up.
    vol = std::clamp(vol, 0, 255);
    pan = std::clamp(pan, -15, 15);
    mpan = std::clamp(mpan, -15, 15);
    const u32 p = right ? kPanLaw[15 - pan] : kPanLaw[15 + pan];
    const u32 m = right ? kOutPanLaw[15 - mpan] : kOutPanLaw[15 + mpan];
    const u64 x10 = static_cast<u64>(static_cast<u32>(vol) * p * m) * 10u;
    const u32 q = static_cast<u32>((x10 * 0x81018203ull) >> 47);
    return q / 10 + ((q % 10) >= 5 ? 1u : 0u);
}

// ---- SjUni ------------------------------------------------------------------------------------------

void SjUni::create(u32 mode, u32 pool, u32 pool_size) {
    *this = SjUni{};
    used_ = true;
    mode_ = mode;
    pool_ = pool;
    nodes_ = pool_size / 16u;  // sjuni_Create 0x562FE8: +16 = size / 16
}

u32 SjUni::nodes_in_use() const {
    u32 n = 0;
    for (const auto& l : lines_) n += static_cast<u32>(l.size());
    return n;
}

bool SjUni::put(u32 line, SjChunk c) {
    if (line > 3 || c.len == 0 || c.ptr == 0) return true;  // ignored (0x56372C/0x563738)
    auto& l = lines_[line];
    if (mode_ == 1 && !l.empty() && l.back().ptr + l.back().len == c.ptr) {  // merge (0x563788)
        l.back().len += c.len;
        return true;
    }
    if (nodes_in_use() >= nodes_) return false;  // error callback -3 (0x5637C4)
    l.push_back(c);
    return true;
}

SjChunk SjUni::get(u32 line, u32 max) {
    if (line > 3) return {};
    auto& l = lines_[line];
    if (l.empty()) return {};
    SjChunk& h = l.front();
    if (h.len <= max) {  // whole chunk (0x5635E0)
        const SjChunk c = h;
        l.pop_front();
        return c;
    }
    if (mode_ != 1) return {};
    const SjChunk c{h.ptr, max};  // split (SJ_SplitChunk 0x563C28)
    h.ptr += max;
    h.len -= max;
    return c;
}

bool SjUni::unget(u32 line, SjChunk c) {
    if (line > 3 || c.len == 0) return true;
    auto& l = lines_[line];
    if (mode_ == 1 && !l.empty() && c.ptr + c.len == l.front().ptr) {
        l.front().ptr = c.ptr;
        l.front().len += c.len;
        return true;
    }
    if (nodes_in_use() >= nodes_) return false;
    l.push_front(c);
    return true;
}

u32 SjUni::num_data(u32 line) const {
    if (line > 3) return 0;
    u32 n = 0;
    for (const SjChunk& c : lines_[line]) n += c.len;
    return n;
}

void SjUni::reset() {
    // inf: SJUNI_Reset returns every chunk to line 0 (not traced; no game caller of urpc 37).
    std::deque<SjChunk> all;
    for (auto& l : lines_) {
        for (const SjChunk& c : l) all.push_back(c);
        l.clear();
    }
    for (const SjChunk& c : all) put(0, c);
}

// ---- AdxiServer: objects ---------------------------------------------------------------------------

std::unique_ptr<AdxiServer> make_adxi_server() { return std::make_unique<AdxiServer>(); }

void AdxiServer::ensure_image(IopCore& core) {
    if (base_ != 0) return;
    // The module's object tables (IRX bss 0xE290 DTX x16 @68, 0xE770 RNA x16 @0x1C, 0x14650 SJUNI @0x30,
    // 0x15190 SJX x32 @20; strides obs) at an HLE-chosen IOP address (inf). Allocated once.
    base_ = core.ram().arena_alloc(0x1600);
    if (base_ == 0) base_ = 0x0007F000u;  // arena exhausted (not expected): still non-zero handles
}

int AdxiServer::rna_index(u32 handle) const {
    for (u32 i = 0; i < kRnaMax; ++i)
        if (rna_[i].used && rna_handle(i) == handle) return static_cast<int>(i);
    return -1;
}
int AdxiServer::sjx_index(u32 handle) const {
    for (u32 i = 0; i < kSjxMax; ++i)
        if (sjx_[i].used && sjx_handle(i) == handle) return static_cast<int>(i);
    return -1;
}
int AdxiServer::sj_index(u32 handle) const {
    for (u32 i = 0; i < kSjMax; ++i)
        if (sj_[i].used() && sj_handle(i) == handle) return static_cast<int>(i);
    return -1;
}
SjUni* AdxiServer::sj_at(u32 handle) {
    const int i = sj_index(handle);
    return i < 0 ? nullptr : &sj_[static_cast<std::size_t>(i)];
}
AdxiStats AdxiServer::stats() const {
    AdxiStats s = st_;
    s.dtx_open = 0;
    s.rna_playing = 0;
    for (const Dtx& d : dtx_) s.dtx_open += d.used ? 1u : 0u;
    for (const Rna& r : rna_) s.rna_playing += (r.used && r.playing) ? 1u : 0u;
    return s;
}

AdxiServer::AdxiServer() { bind_module_defaults(); }

void AdxiServer::bind_module_defaults() {
    // Module start binds both DTX ports' callbacks before any create (IRX 0x1614 -> 0x1408(0,0,0),
    // 0x929C -> 0x9228): the EE's DTX_Create keeps them (0x9D0 leaves obj+32..44 alone); a destroy
    // clears them (memset 68) until urpc 3 / 10 binds again.
    dtx_[0].rcv = dtx_[0].snd = Cb::Sjx;
    dtx_[1].rcv = dtx_[1].snd = Cb::Rna;
}

void AdxiServer::reboot() {
    for (Rna& r : rna_)
        if (r.used) psm_stop(r);  // ends open tap sessions; the mix sink's timeline just continues
    const u32 base = base_;
    audio::AudioSink* mix = mix_;
    audio::StreamTap* tap = tap_;
    const u32 seq = stream_seq_;
    const AdxiStats st = st_;
    *this = AdxiServer{};
    base_ = base;  // the arena block survives reboots (IopRam::reset_arena is not called by reboots)
    mix_ = mix;
    tap_ = tap;
    stream_seq_ = seq;
    st_ = st;
}

bool AdxiServer::active() const {
    for (const Dtx& d : dtx_)
        if (d.used) return true;
    return out_running_[0] || out_running_[1];
}

// ---- RPC ----------------------------------------------------------------------------------------------

bool AdxiServer::call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 /*ticket*/) {
    ensure_image(core);
    core_ = &core;
    now_ = core.now();
    render_until(core, core.now());
    // IRX 0x720: the reply is the receive buffer itself, modified in place.
    std::vector<u8> b(req.data.begin(), req.data.end());
    b.resize(std::max<std::size_t>({b.size(), req.recv_size, 16}), 0);
    SoundRequest log;
    log.sid = req.sid;
    log.fno = req.fno;
    log.cycle = core.now();
    for (std::size_t i = 0; i < log.args.size(); ++i) log.args[i] = word(b, i);

    if (req.fno == 2) {
        // DTX_Create (IRX 0x9D0): {id, eewk (64-aligned), iopwk (32-aligned), wklen (64*N)} -> obj or 0.
        const u32 id = word(b, 0), eewk = word(b, 1), iopwk = word(b, 2), wklen = word(b, 3);
        u32 result = 0;
        if ((eewk & 63u) == 0 && (iopwk & 31u) == 0 && (wklen & 63u) == 0 && wklen >= 128 && id < kDtxMax &&
            !dtx_[id].used) {
            Dtx& d = dtx_[id];
            d.used = true;
            d.stat = 1;
            d.enable = 1;
            d.cnt = 0;
            d.ee_buf = eewk;
            d.iop_buf = iopwk;
            d.wklen = wklen;
            if (u8* p = core.ram().at(iopwk, wklen)) std::memset(p, 0, wklen);  // memset(iopwk, 0, wklen)
            result = dtx_handle(id);
        } else {
            core.note_unknown(UnknownEvent::Kind::Function, req.sid, 2, "DTX create refused (alignment / id / in use)");
        }
        store32(b, 0, result);
        log.result = static_cast<s32>(result);
    } else if (req.fno == 3) {
        // DTX_Destroy (IRX 0xAE8): memset(obj, 0, 68) -- clears the callbacks too.
        const u32 h = word(b, 0);
        for (u32 i = 0; i < kDtxMax; ++i)
            if (dtx_handle(i) == h) dtx_[i] = Dtx{};
    } else if (req.fno >= 1024 && req.fno < 1024 + 64) {
        ++st_.urpc_calls;
        urpc(core, req.fno - 1024, b);
        log.result = static_cast<s32>(word(b, 0));
    }
    // fn < 2 and fn >= 1088: no action, buffer echoed (IRX 0x738/0x78C).
    core.record_sound(log);
    b.resize(req.recv_size);
    reply.rdata = std::move(b);
    return true;
}

void AdxiServer::urpc(IopCore& core, u32 n, std::vector<u8>& b) {
    auto put = [&](std::size_t i, u32 v) { store32(b, 4 * i, v); };
    auto w = [&](std::size_t i) { return word(b, i); };
    switch (n) {
    case 0: {  // SJX_Create (IRX 0x914C): {ee_sj, iop_sj, mode, ee_sjx} -> obj / 0
        u32 h = 0;
        for (u32 i = 0; i < kSjxMax; ++i) {
            if (sjx_[i].used) continue;
            sjx_[i] = Sjx{true, 0, w(1), w(0), w(2) == 1 ? 0u : 1u, w(3)};
            h = sjx_handle(i);
            break;
        }
        put(0, h);
        break;
    }
    case 1: {  // SJX_Destroy (0x920C)
        const int i = sjx_index(w(0));
        if (i >= 0) sjx_[static_cast<std::size_t>(i)].used = false;
        break;
    }
    case 2: {  // SJX id (0x9218)
        const int i = sjx_index(w(0));
        if (i >= 0) sjx_[static_cast<std::size_t>(i)].id = static_cast<u16>(w(1));
        break;
    }
    case 3:  // SJX_Init (0x9228): DTX id 0 <- SJX callbacks
        dtx_[0].rcv = dtx_[0].snd = Cb::Sjx;
        break;
    case 8: {  // IOPRNA create (0x12B8): {nch, core, sj0, sj1} -> rna / 0
        u32 h = 0;
        const u32 nch = w(0);
        for (u32 i = 0; i < kRnaMax && h == 0; ++i) {
            if (rna_[i].used) continue;
            if (w(1) >= 2 || nch > 2) {  // PSM_Create refuses core_no >= 2 (0x2364); vol/pan arrays hold 2 ch
                core.note_unknown(UnknownEvent::Kind::Function, 0x90000200u, 1024 + 8, "IOPRNA create: PSM refused");
                break;
            }
            Rna r;
            r.used = true;
            r.maxnch = r.nch = nch;
            for (u32 c = 0; c < nch; ++c) r.sj[c] = w(2 + c);
            r.psm_nch = nch;                  // 0x2DC4(psm, nch)
            r.sfreq = sfreq_default_;         // 0x2768(psm, 0xD7F4)
            r.core = core_no_ == 2 ? 1u : core_no_;  // 0x2478..0x24DC
            rna_[i] = r;
            h = rna_handle(i);
        }
        put(0, h);
        break;
    }
    case 9: {  // IOPRNA destroy (0x13D0)
        const int i = rna_index(w(0));
        if (i >= 0) {
            psm_stop(rna_[static_cast<std::size_t>(i)]);
            rna_[static_cast<std::size_t>(i)] = Rna{};
        }
        break;
    }
    case 10:  // PSM init (0x1408): {voices, work, size}; DTX id 1 <- RNA callbacks
        psm_voices_ = w(0);
        dtx_[1].rcv = dtx_[1].snd = Cb::Rna;
        break;
    case 11:  // restore IOP sound (0x1494): core select, finish, init
        if (w(0) < 3) core_no_ = w(0);
        psm_finish();
        psm_init(core);
        break;
    case 12:  // init IOP sound (0x14C8): sfreq -> 0xD7F4, init, reply = core (0xD410)
        sfreq_default_ = w(0);
        psm_init(core);
        put(0, core_no_);
        break;
    case 13:  // finish IOP sound (0x150C)
        psm_finish();
        break;
    case 14:  // Dolby on (0x152C -> 0x1B34): core 0 prints and does nothing (0x1B40)
    case 15:  // Dolby off (0x154C)
        core.note_unknown(UnknownEvent::Kind::Function, 0x90000200u, 1024 + n, "Dolby Pro Logic II switch (not modelled)");
        break;
    case 16:  // start PCM trans (0x156C -> PSMOUT start)
        if (w(0) < 2) out_start(core, w(0));
        break;
    case 17:  // stop PCM trans (0x1590)
        if (w(0) < 2) out_stop(w(0));
        break;
    case 34: {  // SJUNI_CreateRmt (0x8B5C -> 0x7A68): {mode, pool, size} -> sj / 0
        u32 h = 0;
        for (u32 i = 0; i < kSjMax; ++i) {
            if (sj_[i].used()) continue;
            sj_[i].create(w(0), w(1), w(2));
            h = sj_handle(i);
            break;
        }
        put(0, h);
        break;
    }
    case 35: {  // SJ destroy (vtable +0x0C)
        if (SjUni* s = sj_at(w(0))) s->destroy();
        break;
    }
    case 37: {  // SJ reset (+0x14)
        if (SjUni* s = sj_at(w(0))) s->reset();
        break;
    }
    case 38: {  // SJ GetChunk (+0x18): {sj, line, max} -> {ptr, len}
        SjChunk c;
        if (SjUni* s = sj_at(w(0))) c = s->get(w(1), w(2));
        put(0, c.ptr);
        put(1, c.len);
        break;
    }
    case 39:  // SJ UngetChunk (+0x1C): {sj, line, ptr, len}
    case 40: {  // SJ PutChunk (+0x20)
        if (SjUni* s = sj_at(w(0))) {
            const bool ok = n == 39 ? s->unget(w(1), SjChunk{w(2), w(3)}) : s->put(w(1), SjChunk{w(2), w(3)});
            if (!ok) ++st_.sj_errors;
        }
        break;
    }
    case 41: {  // SJ GetNumData (+0x24): {sj, line} -> n
        const SjUni* s = sj_at(w(0));
        put(0, s ? s->num_data(w(1)) : 0u);
        break;
    }
    case 42: {  // SJ IsGetChunk (+0x28): {sj, line, n} -> {r, avail}; inf semantics, no game caller
        const SjUni* s = sj_at(w(0));
        const u32 first = (s && !s->line(w(1)).empty()) ? s->line(w(1)).front().len : 0u;
        put(0, first >= w(2) ? 1u : 0u);
        put(1, first);
        break;
    }
    case 32:  // SJRBF_CreateRmt (0x8AE0), 33 SJMEM_CreateRmt (0x8B20), 36 GetUuid: no EE caller
    case 33:
    case 36:
    default:
        core.note_unknown(UnknownEvent::Kind::Function, 0x90000200u, 1024 + n, "CRI_ADXI urpc not modelled (buffer echoed)");
        break;
    }
}

// ---- server pass (IOP vblank-end) ---------------------------------------------------------------------

void AdxiServer::tick(IopCore& core, u64 now, const Timebase& tb) {
    if (!active()) {
        seen_vblank_ = tb.vblanks;
        tick_due_ = kNever;
        return;
    }
    if (tb.vblanks != seen_vblank_) {
        seen_vblank_ = tb.vblanks;
        if (tick_due_ == kNever) tick_due_ = now + core.config().adxi_tick_delay_cycles;
    }
    if (tick_due_ != kNever && now >= tick_due_) {
        tick_due_ = kNever;
        server_pass(core, now);
    }
}

void AdxiServer::server_pass(IopCore& core, u64 now) {
    ++st_.ticks;
    core_ = &core;
    now_ = now;
    render_until(core, now);
    // IRX 0x1234: RNA discard (0x1140) for every RNA, then the DTX server (0x912C -> 0xE14).
    for (Rna& r : rna_) {
        if (!r.used || r.discard != 1) continue;
        for (u32 c = 0; c < r.nch; ++c) {
            SjUni* s = sj_at(r.sj[c]);
            if (!s) continue;
            for (SjChunk ch = s->get(1, 0x7FFFFFFFu); ch.len != 0; ch = s->get(1, 0x7FFFFFFFu))
                if (!s->put(0, ch)) ++st_.sj_errors;
        }
    }
    for (Dtx& d : dtx_)
        if (d.used) dtx_exec(core, d);
}

void AdxiServer::dtx_exec(IopCore& core, Dtx& d) {
    // IRX 0xB24 (obs).
    const u32 data_len = d.wklen - 64;
    u8* p = core.ram().at(d.iop_buf, d.wklen);
    if (p == nullptr) return;
    std::span<u8> data(p, data_len);
    if (d.stat == 1) {
        const u32 ctrl = rd32(core, d.iop_buf + d.wklen - 4);  // obj+20 -> +0x3C
        if (static_cast<s32>(d.cnt) < static_cast<s32>(ctrl)) {
            if (d.rcv == Cb::Sjx) sjx_receive(core, data);
            else if (d.rcv == Cb::Rna) rna_receive(core, data);
            d.stat = 0;
            d.cnt = ctrl;
            ++st_.dtx_blocks_in;
        }
    }
    if (d.stat == 0 && d.enable) {
        if (d.snd == Cb::Sjx) sjx_send(core, data);
        else if (d.snd == Cb::Rna) store32(data, 0, 0);  // 0x10F8: zero entries
        d.cnt += 1;
        wr32(core, d.iop_buf + d.wklen - 4, d.cnt);
        // sceSifSetDma({iopwk, eewk, wklen, 0}) (0xC50..0xC68): the whole buffer back to the EE.
        core.queue_ee_write(d.ee_buf, std::vector<u8>(p, p + d.wklen));
        d.stat = 1;
        ++st_.dtx_blocks_out;
    }
}

void AdxiServer::sjx_receive(IopCore& /*core*/, std::span<u8> buf) {
    // IRX 0x8F60: n = word0; entries at +16: {u8 flag (0 = valid), u8 line, u16 id, sjx, ptr, len};
    // each valid entry is put on line 1 (data) of the SJX's SJUNI.
    const u32 cap = static_cast<u32>((buf.size() - 16) / 16);
    const u32 n = std::min<u32>(load32(buf, 0), cap);
    for (u32 i = 0; i < n; ++i) {
        const std::size_t e = 16 + 16 * i;
        if (buf[e] != 0) continue;
        const int x = sjx_index(load32(buf, e + 4));
        if (x < 0) {
            ++st_.sj_errors;
            continue;
        }
        SjUni* s = sj_at(sjx_[static_cast<std::size_t>(x)].sj);
        if (!s) {
            ++st_.sj_errors;
            continue;
        }
        if (!s->put(1, SjChunk{load32(buf, e + 8), load32(buf, e + 12)})) ++st_.sj_errors;
        ++st_.sjx_chunks_in;
    }
}

void AdxiServer::sjx_send(IopCore& /*core*/, std::span<u8> buf) {
    // IRX 0x900C: every SJX in table order hands back its line's chunks, <= 128 entries in all.
    u32 count = 0;
    for (const Sjx& x : sjx_) {
        if (!x.used) continue;
        SjUni* s = sj_at(x.sj);
        while (s && count < 128 && 16 + 16 * (count + 1) <= buf.size()) {
            const SjChunk c = s->get(x.line, 0x7FFFFFFFu);
            if (c.len == 0) break;
            const std::size_t e = 16 + 16 * count;
            buf[e] = 0;
            buf[e + 1] = static_cast<u8>(x.line);
            buf[e + 2] = static_cast<u8>(x.id);
            buf[e + 3] = static_cast<u8>(x.id >> 8);
            store32(buf, e + 4, x.ee_sjx);
            store32(buf, e + 8, c.ptr);
            store32(buf, e + 12, c.len);
            ++count;
            ++st_.sjx_chunks_out;
        }
    }
    store32(buf, 0, count);
}

void AdxiServer::rna_receive(IopCore& core, std::span<u8> buf) {
    // IRX 0xEA0: n = word0; entries at +16: {s16 cmd, _, rna, v8, v12}.
    const u32 cap = static_cast<u32>((buf.size() - 16) / 16);
    const u32 n = std::min<u32>(load32(buf, 0), cap);
    for (u32 i = 0; i < n; ++i) {
        const std::size_t e = 16 + 16 * i;
        const s16 cmd = static_cast<s16>(buf[e] | (buf[e + 1] << 8));
        const u32 v8 = load32(buf, e + 8), v12 = load32(buf, e + 12);
        ++st_.rna_commands;
        if (cmd == kCmdPauseAll) {  // global (0xF24 -> 0x21C8)
            const bool pause = static_cast<s8>(v8) == 1;
            if (pause != paused_) {
                paused_ = pause;
                for (u32 c = 0; c < 2; ++c) {
                    if (pause) out_stop(c);
                    else out_start(core, c);
                }
            }
            continue;
        }
        const int ri = rna_index(load32(buf, e + 4));
        if (ri < 0 || cmd < 0 || cmd > 13) continue;
        Rna& r = rna_[static_cast<std::size_t>(ri)];
        const u32 idx = static_cast<u32>(ri);
        switch (static_cast<u32>(cmd)) {
        case kCmdStart: psm_start(r, idx); break;
        case kCmdStop: psm_stop(r); break;
        case kCmdPlaySw:
            if (v8 == 1) psm_start(r, idx);
            else psm_stop(r);
            break;
        case kCmdNumChan:  // 0x101C: rna+8 = v8; 0x2DC4 only while stopped and <= maxnch
            r.nch = std::min<u32>(v8, 2);
            if (!r.playing && v8 <= r.maxnch) r.psm_nch = v8;
            break;
        case kCmdSfreq:  // 0x1034 -> 0x2768 (every slot's RCV input rate)
            if (v8 != r.sfreq) {
                r.sfreq = v8;
                if (r.playing && r.stream && tap_) {  // a new tap session at the new rate
                    tap_->stream_end(r.stream);
                    r.stream = ++stream_seq_;
                    tap_->stream_begin(audio::StreamInfo{r.stream, idx, r.psm_nch, r.sfreq});
                }
            }
            break;
        case kCmdVolume:  // 0x104C: rna+0x18 = v12; every channel 0x2998(psm, ch, v12)
            r.vol_all = v12;
            for (auto& v : r.vol) v = std::clamp(static_cast<s32>(v12), 0, 255);
            break;
        case kCmdDiscard: r.discard = static_cast<s8>(v8); break;  // 0xF40
        case kCmdPan:  // 0x108C -> 0x2A24(psm, v8 = ch, v12)
            if (v8 < 2) r.pan[v8] = std::clamp(static_cast<s32>(v12), -15, 15);
            break;
        case kCmdRoute:  // 0xF84: rna+2; output core 0 when 1 else 1 (re-applies volumes) -- routing only
            r.b2 = static_cast<u8>(v8);
            r.core = static_cast<s8>(v8) == 1 ? 0u : 1u;
            break;
        case kCmdCore:  // 0xFFC: rna+3 = v8; 0x2C38(psm, v8)
            r.b3 = static_cast<u8>(v8);
            if (static_cast<s8>(v8) >= 0 && static_cast<s8>(v8) < 2) r.core = static_cast<u32>(static_cast<s8>(v8));
            break;
        case kCmdOutPan:  // 0x10A8 -> 0x2ACC: -128 re-applies, else clamp to -15..15
            if (static_cast<s32>(v8) != -128) r.mpan = std::clamp(static_cast<s32>(v8), -15, 15);
            break;
        default:  // 6, 7: no action (0x10B8)
            break;
        }
    }
}

// ---- PSM -----------------------------------------------------------------------------------------------

void AdxiServer::psm_init(IopCore& core) {
    // 0x1FAC: first init starts PSMOUT for the current core (both for core 2); counted.
    if (init_count_++ == 0) {
        if (core_no_ == 2) {
            out_start(core, 0);
            out_start(core, 1);
        } else {
            out_start(core, core_no_);
        }
    }
}

void AdxiServer::psm_finish() {
    // 0x20C8: last finish destroys the PSMs and stops both outputs.
    if (init_count_ == 0) return;
    if (--init_count_ != 0) return;
    for (Rna& r : rna_)
        if (r.used) psm_stop(r);
    out_stop(0);
    out_stop(1);
}

void AdxiServer::out_start(IopCore& core, u32 core_no) {
    if (core_no > 1 || out_running_[core_no]) return;
    if (!out_running_[0] && !out_running_[1]) next_frame_ = std::max(next_frame_, audio::frames_at_cycles(core.now()));
    out_running_[core_no] = true;
}

void AdxiServer::out_stop(u32 core_no) {
    if (core_no <= 1) out_running_[core_no] = false;
}

void AdxiServer::psm_start(Rna& r, u32 index) {
    // 0x265C: stop, restart every slot (RCV state reset, 0x6234), playing = 1.
    if (r.playing) psm_stop(r);
    r.playing = true;
    r.rs = {};
    if (tap_) {
        r.stream = ++stream_seq_;
        tap_->stream_begin(audio::StreamInfo{r.stream, index, r.psm_nch, r.sfreq});
    }
    if (core_) {
        SoundRequest ev;
        ev.sid = 0x90000200u;
        ev.fno = 0x8000u;
        ev.args = {index, r.sfreq, r.psm_nch, r.core, static_cast<u32>(r.vol[0]), static_cast<u32>(r.vol[1]), r.stream, 0};
        ev.cycle = now_;
        ev.result = static_cast<s32>(audio::frames_at_cycles(now_));
        core_->record_event(ev);
    }
}

void AdxiServer::psm_stop(Rna& r) {
    if (core_ && r.playing) {
        SoundRequest ev;
        ev.sid = 0x90000200u;
        ev.fno = 0x8001u;
        ev.args = {0, r.sfreq, r.psm_nch, r.core, 0, 0, r.stream, 0};
        ev.cycle = now_;
        ev.result = static_cast<s32>(audio::frames_at_cycles(now_));
        core_->record_event(ev);
    }

    if (!r.playing) return;
    r.playing = false;
    if (tap_ && r.stream) tap_->stream_end(r.stream);
    r.stream = 0;
}

u32 AdxiServer::read_samples(IopCore& core, Rna& r, u32 ch, std::span<s16> out) {
    // Pops s16 samples from the head of the SJUNI data line (IOP RAM) and returns the consumed bytes to
    // the free line, merged (mode 1).
    SjUni* s = sj_at(r.sj[ch]);
    if (!s) return 0;
    u32 got = 0;
    while (got < out.size()) {
        const u32 want_bytes = static_cast<u32>(out.size() - got) * 2u;
        const SjChunk c = s->get(1, want_bytes);
        if (c.len == 0) break;
        const u32 n = c.len / 2;
        if (const u8* p = core.ram().at(c.ptr, n * 2)) std::memcpy(out.data() + got, p, n * 2u);
        else std::fill(out.begin() + got, out.begin() + got + n, static_cast<s16>(0));
        got += n;
        st_.pcm_bytes_consumed += c.len;
        if (!s->put(0, c)) ++st_.sj_errors;
        if ((c.len & 1u) != 0) break;  // odd length (not produced by DTR's 64-byte units)
    }
    return got;
}

void AdxiServer::render_until(IopCore& core, u64 now) {
    if (!out_running_[0] && !out_running_[1]) return;
    // A pass is due once the output clock has passed its last frame (the half-buffer interrupt).
    for (int guard = 0; guard < 1 << 22; ++guard) {
        if (audio::cycles_at_frame(next_frame_ + kPassFrames) > now) break;
        render_pass(core);
    }
}

void AdxiServer::render_pass(IopCore& core) {
    const prof::Scope prof_zone(prof::Zone::Audio);
    ++st_.psm_passes;
    mixbuf_.assign(static_cast<std::size_t>(kPassFrames) * audio::kOutputChannels, 0);
    std::array<std::array<s32, kPassFrames>, 2> acc{};
    std::vector<s16> in;
    for (u32 ri = 0; ri < kRnaMax; ++ri) {
        Rna& r = rna_[ri];
        if (!r.used || !r.playing || r.core > 1 || !out_running_[r.core] || r.sfreq == 0) continue;
        const u32 nch = std::min<u32>(r.psm_nch, 2);
        for (u32 c = 0; c < nch; ++c) {
            Resampler& rs = r.rs[c];
            // Input samples this pass: one per 48000 of accumulated phase (rate sfreq/48000; inf
            // linear interpolation for the RCV converter, IRX 0x9DBC/0xA044 not traced).
            const u64 pops = (static_cast<u64>(rs.phase) + static_cast<u64>(r.sfreq) * kPassFrames) / audio::kOutputRate;
            in.assign(static_cast<std::size_t>(pops), 0);
            const u32 got = read_samples(core, r, c, in);
            if (got < pops) st_.underrun_samples += pops - got;
            if (tap_ && r.stream && got > 0) tap_->stream_data(r.stream, c, std::span<const s16>(in.data(), got));
            const u32 gl = psm_side_gain(r.vol[c], r.pan[c], r.mpan, false);
            const u32 gr = psm_side_gain(r.vol[c], r.pan[c], r.mpan, true);
            std::size_t k = 0;
            for (u32 f = 0; f < kPassFrames; ++f) {
                rs.phase += r.sfreq;
                while (rs.phase >= audio::kOutputRate) {
                    rs.phase -= audio::kOutputRate;
                    rs.prev = rs.cur;
                    rs.cur = k < got ? in[k] : static_cast<s16>(0);
                    ++k;
                }
                const s32 s = rs.prev + static_cast<s32>((static_cast<s64>(rs.cur - rs.prev) * rs.phase) / audio::kOutputRate);
                // inf: PSMMIX applies the 0..255 side gains as gain/255 (mixer 0x30A4 not traced).
                acc[0][f] += s * static_cast<s32>(gl) / 255;
                acc[1][f] += s * static_cast<s32>(gr) / 255;
            }
        }
    }
    for (u32 f = 0; f < kPassFrames; ++f) {
        mixbuf_[2 * f] = static_cast<s16>(std::clamp(acc[0][f], -32768, 32767));
        mixbuf_[2 * f + 1] = static_cast<s16>(std::clamp(acc[1][f], -32768, 32767));
    }
    if (mix_) mix_->push(next_frame_, mixbuf_);
    next_frame_ += kPassFrames;
}

}  // namespace p3fes::hle::sif::detail
