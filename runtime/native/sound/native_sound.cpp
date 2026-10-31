// Modernize layer 3: the native ADX output (native_sound.h).
#include "native_sound.h"

#include <algorithm>

#include "p3fes/state_io.h"
#include "sk_host.h"

namespace p3fes::native::sound {

namespace {
// The PSM pan tables (CRI_ADXI.IRX .data 0xD310 / 0xD38C, 31 entries for -15..15).
constexpr std::array<u32, 31> kPanLaw = {255, 254, 253, 251, 249, 246, 242, 238, 232, 227, 220, 213, 206, 198, 189, 180,
                                         170, 160, 149, 138, 127, 115, 103, 91,  78,  65,  53,  39,  26,  13,  0};
constexpr std::array<u32, 31> kOutPanLaw = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                                            238, 221, 204, 187, 170, 153, 136, 119, 102, 85,  68,  51,  34,  17,  0};
// The IOPRNA command numbers (docs/ANALYSIS/16 §6.1).
enum : s16 {
    kStart = 0, kStop = 1, kPlaySw = 2, kNumChan = 3, kSfreq = 4, kVolume = 5, kDiscard = 8, kPan = 9, kRoute = 10,
    kPauseAll = 11, kCore = 12, kOutPan = 13,
};
}  // namespace

u32 psm_side_gain(s32 vol, s32 pan, s32 mpan, bool right) {
    // x = vol * law[15+pan] * outlaw[15+mpan] (left; right uses 15-pan, 15-mpan), q = (10x * 0x81018203) >> 47
    // (~ 10x / 65025), result = q / 10 rounded half up.
    vol = std::clamp(vol, 0, 255);
    pan = std::clamp(pan, -15, 15);
    mpan = std::clamp(mpan, -15, 15);
    const u32 p = right ? kPanLaw[static_cast<std::size_t>(15 - pan)] : kPanLaw[static_cast<std::size_t>(15 + pan)];
    const u32 m = right ? kOutPanLaw[static_cast<std::size_t>(15 - mpan)] : kOutPanLaw[static_cast<std::size_t>(15 + mpan)];
    const u64 x10 = static_cast<u64>(static_cast<u32>(vol) * p * m) * 10u;
    const u32 q = static_cast<u32>((x10 * 0x81018203ull) >> 47);
    return q / 10 + ((q % 10) >= 5 ? 1u : 0u);
}

NativeSound::NativeSound() { mixbuf_.resize(static_cast<std::size_t>(kPassFrames) * audio::kOutputChannels); }

int NativeSound::index_of(u32 rna) const {
    if (rna < kRnaTable || rna >= kRnaTable + kRnaSize * kRnaCount || (rna - kRnaTable) % kRnaSize != 0) return -1;
    const u32 i = (rna - kRnaTable) / kRnaSize;
    return rna_[i].used ? static_cast<int>(i) : -1;
}

// ---- the server's side (the EE's calls) ---------------------------------------------------------------------------

void NativeSound::rna_open(u64 cycles) {
    if (open_) return;
    open_ = true;
    next_frame_ = std::max(next_frame_, audio::frames_at_cycles(cycles));
}

void NativeSound::rna_close(u64 cycles) {
    for (Rna& r : rna_)
        if (r.used) stop(r, cycles);
    open_ = false;
}

void NativeSound::rna_create(u64 cycles, u32 rna, u32 nch) {
    if (rna < kRnaTable || (rna - kRnaTable) % kRnaSize != 0 || (rna - kRnaTable) / kRnaSize >= kRnaCount) return;
    Rna& r = rna_[(rna - kRnaTable) / kRnaSize];
    if (r.used) stop(r, cycles);
    r = Rna{};
    r.used = true;
    r.nch = r.psm_nch = std::min<u32>(nch, 2);
    reset_buffers(r);
    ++st_.creates;
}

void NativeSound::put_merge(std::deque<Chunk>& line, Chunk c) {
    // sjuni_PutChunk, mode 1: an empty chunk is ignored; one that continues the tail extends it
    if (c.len == 0) return;
    if (!line.empty() && line.back().off + line.back().len == c.off) {
        line.back().len += c.len;
        return;
    }
    line.push_back(c);
}

u32 NativeSound::line_bytes(const std::deque<Chunk>& line) {
    u32 n = 0;
    for (const Chunk& c : line) n += c.len;
    return n;
}

void NativeSound::reset_buffers(Rna& r) {
    for (Chan& c : r.ch) {
        c = Chan{};
        c.efree.push_back(Chunk{0, kRnaBufBytes});  // the PSJ's free line starts as the whole buffer
    }
}

void NativeSound::rna_destroy(u64 cycles, u32 rna) {
    const int i = index_of(rna);
    if (i < 0) return;
    stop(rna_[static_cast<std::size_t>(i)], cycles);
    rna_[static_cast<std::size_t>(i)] = Rna{};
    ++st_.destroys;
}

void NativeSound::rna_transfer(u64 /*cycles*/, u32 rna, bool on) {
    const int i = index_of(rna);
    if (i < 0) return;
    Rna& r = rna_[static_cast<std::size_t>(i)];
    r.transfer = on;
    if (!on) r.running = false;  // DTR_Stop
}

bool NativeSound::rna_try_restart(u64 /*cycles*/, u32 rna) {
    // sub_560F78: with the transfer asked on and no transfer running, once every channel's buffer is wholly free
    // again, the buffer is taken whole and put back (one chunk), and the DTR restarts (the caller clears +91, the
    // discard switch).
    const int i = index_of(rna);
    if (i < 0) return false;
    Rna& r = rna_[static_cast<std::size_t>(i)];
    if (!r.transfer || r.running) return false;
    for (u32 c = 0; c < r.nch; ++c)
        if (line_bytes(r.ch[c].efree) != kRnaBufBytes || r.ch[c].dma.len != 0) return false;
    for (u32 c = 0; c < r.nch; ++c) {
        r.ch[c].efree.clear();
        r.ch[c].efree.push_back(Chunk{0, kRnaBufBytes});
    }
    r.running = true;
    ++st_.restarts;
    return true;
}

bool NativeSound::rna_transfer_running(u32 rna) const {
    const int i = index_of(rna);
    return i >= 0 && rna_[static_cast<std::size_t>(i)].running;
}

u32 NativeSound::rna_inflight_bytes(u32 rna, u32 ch) const {
    const int i = index_of(rna);
    if (i < 0 || ch >= 2) return 0;
    return kRnaBufBytes - line_bytes(rna_[static_cast<std::size_t>(i)].ch[ch].efree);
}

u32 NativeSound::rna_dma_room(u32 rna, u32 ch) const {
    const int i = index_of(rna);
    if (i < 0 || ch >= 2) return 0;
    const Chan& c = rna_[static_cast<std::size_t>(i)].ch[ch];
    return c.efree.empty() ? 0u : c.efree.front().len;
}

void NativeSound::rna_dma_start(u64 /*cycles*/, u32 rna, u32 ch, u32 data, u32 len) {
    // DTR: the head free chunk, split at `len` (the rest stays at the head)
    const int i = index_of(rna);
    if (i < 0 || ch >= 2 || len == 0) return;
    Chan& c = rna_[static_cast<std::size_t>(i)].ch[ch];
    if (c.efree.empty()) return;
    Chunk& h = c.efree.front();
    len = std::min(len, h.len);
    c.dma = Chunk{h.off, len};
    c.dma_src = data;
    h.off += len;
    h.len -= len;
    if (h.len == 0) c.efree.pop_front();
}

bool NativeSound::rna_dma_pending(u32 rna, u32 ch, u32& data, u32& len) const {
    const int i = index_of(rna);
    if (i < 0 || ch >= 2) return false;
    const Chan& c = rna_[static_cast<std::size_t>(i)].ch[ch];
    data = c.dma_src;
    len = c.dma.len;
    return len != 0;
}

void NativeSound::rna_dma_done(u64 /*cycles*/, u32 rna, u32 ch, std::span<const s16> pcm) {
    // the completed transfer goes onto the EE's data line (sent with the next block)
    const int i = index_of(rna);
    if (i < 0 || ch >= 2) return;
    Chan& c = rna_[static_cast<std::size_t>(i)].ch[ch];
    if (c.dma.len == 0) return;
    Data d;
    d.off = c.dma.off;
    d.len = c.dma.len;
    d.pcm.assign(pcm.begin(), pcm.begin() + std::min<std::size_t>(pcm.size(), c.dma.len / 2));
    d.pcm.resize(c.dma.len / 2, 0);
    c.edata.push_back(std::move(d));
    c.dma = Chunk{};
    st_.pcm_bytes_in += pcm.size() * 2u;
}

bool NativeSound::rna_exchange(u64 /*cycles*/) {
    if (answer_waiting_) {  // sjx_rcvcbf: every chunk the output gave back goes onto the EE's free line
        for (Rna& r : rna_)
            for (Chan& c : r.ch) {
                for (const Chunk& k : c.answered) put_merge(c.efree, k);
                c.answered.clear();
            }
        answer_waiting_ = false;
    }
    return !block_in_flight_;
}

void NativeSound::rna_command(u64 /*cycles*/, const RnaCommand& c) { building_.push_back(c); }

void NativeSound::rna_send(u64 /*cycles*/) {
    // sjx_sndcbf: the EE's data chunks go out with the block (the IOP puts them on its data line)
    for (Rna& r : rna_)
        for (Chan& c : r.ch) {
            for (Data& d : c.edata) c.sent.push_back(std::move(d));
            c.edata.clear();
        }
    in_flight_.insert(in_flight_.end(), building_.begin(), building_.end());
    building_.clear();
    block_in_flight_ = true;
    ++st_.blocks;
}

// ---- the output's side (the host's clock) -------------------------------------------------------------------------

void NativeSound::vblank(u64 vblank_count, u64 cycles) {
    if (vblank_count == seen_vblank_) return;
    seen_vblank_ = vblank_count;
    if (pass_due_ == ~0ull) pass_due_ = cycles + delay_;
}

void NativeSound::advance(u64 cycles) {
    if (pass_due_ != ~0ull && cycles >= pass_due_) {
        pass_due_ = ~0ull;
        pass(cycles);
    }
}

void NativeSound::pass(u64 cycles) {
    // CRI_ADXI's thread after WaitVblankEnd: the passes due, the discard (every data chunk onto the free line), then
    // the block (PCM, then commands) and the answer (the free line's chunks, at most 128 per answer).
    ++st_.passes_run;
    render_until(cycles);
    for (Rna& r : rna_) {
        if (!r.used || r.discard != 1) continue;
        for (u32 k = 0; k < r.nch; ++k) {
            Chan& c = r.ch[k];
            for (const Data& d : c.idata) {
                put_merge(c.ifree, Chunk{d.off + d.pos, d.len - d.pos});
                st_.discarded_bytes += d.len - d.pos;
            }
            c.idata.clear();
        }
    }
    if (!block_in_flight_) return;
    for (Rna& r : rna_)
        for (Chan& c : r.ch) {
            for (Data& d : c.sent) c.idata.push_back(std::move(d));
            c.sent.clear();
        }
    for (const RnaCommand& c : in_flight_) apply(c, cycles);
    in_flight_.clear();
    block_in_flight_ = false;
    u32 entries = 0;
    for (Rna& r : rna_)
        for (Chan& c : r.ch)
            while (!c.ifree.empty() && entries < kRnaCmdMax) {
                c.answered.push_back(c.ifree.front());
                c.ifree.pop_front();
                ++entries;
            }
    answer_waiting_ = true;
}


void NativeSound::apply(const RnaCommand& c, u64 cycles) {
    ++st_.commands;
    if (c.cmd == kPauseAll) {  // global (IRX 0xF24 -> 0x21C8): both outputs stop / start
        const bool pause = static_cast<s8>(c.v8) == 1;
        if (pause != paused_ && !pause) next_frame_ = std::max(next_frame_, audio::frames_at_cycles(cycles));
        paused_ = pause;
        return;
    }
    const int i = index_of(c.rna);
    if (i < 0 || c.cmd < 0 || c.cmd > 13) return;
    Rna& r = rna_[static_cast<std::size_t>(i)];
    const u32 idx = static_cast<u32>(i);
    switch (c.cmd) {
    case kStart: start(r, idx, cycles); break;
    case kStop: stop(r, cycles); break;
    case kPlaySw:
        if (c.v8 == 1) start(r, idx, cycles);
        else stop(r, cycles);
        break;
    case kNumChan:  // the data channels; the PSM's count only while stopped and <= the created count
        if (!r.playing && c.v8 <= r.nch) r.psm_nch = c.v8;
        break;
    case kSfreq:
        if (c.v8 != r.sfreq) {
            r.sfreq = c.v8;
            if (r.playing && r.stream && tap_) {  // a new tap session at the new rate, as the faithful model
                tap_->stream_end(r.stream);
                r.stream = ++stream_seq_;
                tap_->stream_begin(audio::StreamInfo{r.stream, idx, r.psm_nch, r.sfreq});
            }
        }
        break;
    case kVolume:
        for (auto& v : r.vol) v = std::clamp(static_cast<s32>(c.v12), 0, 255);
        break;
    case kDiscard: r.discard = static_cast<s8>(c.v8); break;
    case kPan:
        if (c.v8 < 2) r.pan[c.v8] = std::clamp(static_cast<s32>(c.v12), -15, 15);
        break;
    case kRoute: r.core = static_cast<s8>(c.v8) == 1 ? 0u : 1u; break;
    case kCore:
        if (static_cast<s8>(c.v8) >= 0 && static_cast<s8>(c.v8) < 2) r.core = static_cast<u32>(static_cast<s8>(c.v8));
        break;
    case kOutPan:
        if (static_cast<s32>(c.v8) != -128) r.mpan = std::clamp(static_cast<s32>(c.v8), -15, 15);
        break;
    default: break;  // 6, 7: no action
    }
}

void NativeSound::emit(u64 cycles, u32 fno, const Rna& r, u32 index, bool with_vol) {
    if (!events_) return;
    NativeSoundEvent e;
    e.cycles = cycles;
    e.fno = fno;
    e.args = {fno == 0x8000u ? index : 0u, r.sfreq, r.psm_nch, r.core, with_vol ? static_cast<u32>(r.vol[0]) : 0u,
              with_vol ? static_cast<u32>(r.vol[1]) : 0u, r.stream, 0};
    e.frame = audio::frames_at_cycles(cycles);
    events_(e);
}

void NativeSound::start(Rna& r, u32 index, u64 cycles) {
    // IRX 0x265C: stop, restart every slot's rate converter, playing.
    if (r.playing) stop(r, cycles);
    r.playing = true;
    for (Chan& c : r.ch) c.rs = {};
    if (tap_) {
        r.stream = ++stream_seq_;
        tap_->stream_begin(audio::StreamInfo{r.stream, index, r.psm_nch, r.sfreq});
    }
    ++st_.starts;
    emit(cycles, 0x8000u, r, index, true);
}

void NativeSound::stop(Rna& r, u64 cycles) {
    if (!r.playing) return;
    emit(cycles, 0x8001u, r, 0, false);
    r.playing = false;
    if (tap_ && r.stream) tap_->stream_end(r.stream);
    r.stream = 0;
    ++st_.stops;
}

void NativeSound::render_until(u64 cycles) {
    if (!open_ || paused_) return;
    for (int guard = 0; guard < 1 << 22; ++guard) {
        if (audio::cycles_at_frame(next_frame_ + kPassFrames) > cycles) break;
        render_pass();
    }
}

void NativeSound::render_pass() {
    ++st_.passes;
    std::array<std::array<s32, kPassFrames>, 2> acc{};
    std::vector<s16> in;
    for (u32 ri = 0; ri < kRnaCount; ++ri) {
        Rna& r = rna_[ri];
        if (!r.used || !r.playing || r.core > 1 || r.sfreq == 0) continue;
        const u32 nch = std::min<u32>(r.psm_nch, 2);
        for (u32 c = 0; c < nch; ++c) {
            Chan& ch = r.ch[c];
            Resampler& rs = ch.rs;
            // input samples this pass: one per 48000 of accumulated phase (rate sfreq / 48000), taken from the head of
            // the data line, each piece onto the free line (the faithful model's read_samples)
            const u64 pops = (static_cast<u64>(rs.phase) + static_cast<u64>(r.sfreq) * kPassFrames) / audio::kOutputRate;
            in.clear();
            while (in.size() < pops && !ch.idata.empty()) {
                Data& d = ch.idata.front();
                const u32 have = (d.len - d.pos) / 2;
                const u32 take = static_cast<u32>(std::min<u64>(have, pops - in.size()));
                const std::size_t first = d.pos / 2;
                in.insert(in.end(), d.pcm.begin() + first, d.pcm.begin() + first + take);
                put_merge(ch.ifree, Chunk{d.off + d.pos, take * 2});
                d.pos += take * 2;
                if (d.pos >= d.len) ch.idata.pop_front();
            }
            const u32 got = static_cast<u32>(in.size());
            st_.pcm_bytes_played += got * 2ull;
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
                acc[0][f] += s * static_cast<s32>(gl) / 255;
                acc[1][f] += s * static_cast<s32>(gr) / 255;
            }
        }
    }
    for (u32 f = 0; f < kPassFrames; ++f) {
        mixbuf_[2 * f] = static_cast<s16>(std::clamp(acc[0][f], -32768, 32767));
        mixbuf_[2 * f + 1] = static_cast<s16>(std::clamp(acc[1][f], -32768, 32767));
    }
    if (out_) out_->push(next_frame_, mixbuf_);
    next_frame_ += kPassFrames;
}

NativeSoundStats NativeSound::stats() const {
    NativeSoundStats s = st_;
    s.playing = 0;
    for (const Rna& r : rna_) s.playing += r.used && r.playing ? 1u : 0u;
    return s;
}

void NativeSound::state(StateIo& io) {
    for (Rna& r : rna_) {
        io(r.used, r.nch, r.psm_nch, r.transfer, r.running, r.playing, r.discard, r.sfreq, r.vol, r.pan, r.mpan, r.core);
        io(r.stream);
        for (Chan& c : r.ch) {
            io(c.efree, c.ifree, c.answered, c.dma, c.dma_src, c.rs);
            for (std::deque<Data>* line : {&c.edata, &c.sent, &c.idata}) {
                u32 n = static_cast<u32>(line->size());
                io(n);
                if (io.loading()) line->resize(n);
                for (Data& d : *line) io(d.off, d.len, d.pos, d.pcm);
            }
        }
    }
    io(building_, in_flight_, block_in_flight_, answer_waiting_, open_, paused_, delay_, pass_due_, seen_vblank_);
    io(next_frame_);
    io(stream_seq_, st_);
}

// ---- steps 2-3: the SK stack (sk/sk_host.h) --------------------------------------------------------------------------

bool NativeSound::sk_native() const { return sk_ != nullptr && sk_->installed(); }

s32 NativeSound::sk_load_module(u64 cycles, std::string_view path, std::span<const u8> args) {
    if (!sk_) return -1;
    return sk_->load_module(cycles, path, std::string_view(reinterpret_cast<const char*>(args.data()), args.size()));
}

void NativeSound::sd_remote(u64 cycles, u32 fno, std::span<const u8> send, std::span<u8> recv) {
    if (sk_) sk_->sd_remote(cycles, fno, send, recv);
}
}  // namespace p3fes::native::sound
