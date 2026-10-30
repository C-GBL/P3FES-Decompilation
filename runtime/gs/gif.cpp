// GIF tag decoding and path arbitration. Tag fields and PACKED/REGLIST/IMAGE data sizes are the GS User's
// Manual's; the walking loop was cross-checked against ps2-web-recomp @ c0f476e runtime/src/gs/gif.cpp (walk, MIT).
// Arbitration, the PATH1 queue and the register file are our own (runtime/gs/README.md "Paths").
#include "p3fes/gs/gif.h"
#include "p3fes/prof.h"

#include <algorithm>

namespace p3fes::gs {

GifTag GifTag::decode(const u128& q) noexcept {
    GifTag t;
    const u64 lo = q.u64[0];
    t.nloop = static_cast<u32>(lo & 0x7FFFu);
    t.eop = ((lo >> 15) & 1u) != 0;
    t.pre = ((lo >> 46) & 1u) != 0;
    t.prim = static_cast<u32>((lo >> 47) & 0x7FFu);
    t.flg = static_cast<u32>((lo >> 58) & 3u);
    t.nreg = static_cast<u32>((lo >> 60) & 0xFu);
    if (t.nreg == 0) t.nreg = 16;
    t.regs = q.u64[1];
    return t;
}

std::size_t Gif::feed(u32 p, std::span<const u128> q) {
    const prof::Scope prof_zone(prof::Zone::Gif);
    const prof::GifPath prof_path(static_cast<u8>(p));
    std::size_t i = 0;
    const std::size_t n = q.size();
    while (i < n) {
        Path& s = path_[p];
        if (!s.in_tag) {
            if (!s.open) {
                // Packet boundary: the arbitration point.
                if (p != 1) run_path1_queue();
                if (owner_ != 0 && owner_ != p) break;
                if (p == 3) {
                    if (p3_window_ && p3_window_done_) {
                        // One EOP packet per unmask window (begin/end_path3_window): the rest waits for
                        // the DMAC's retry, by which time the VIF has usually masked PATH3 again.
                        p3_stalled_ = true;
                        p3_stall_qwc_ = n - i;
                        ++stats_.path3_window_stops;
                        break;
                    }
                    if (path3_masked()) {
                        p3_stalled_ = true;
                        p3_stall_qwc_ = n - i;
                        ++stats_.path3_mask_stalls;
                        break;
                    }
                    if (p2_waiting_ && path2_resume_) path2_resume_();
                    if (p2_waiting_) {
                        p3_stalled_ = true;
                        p3_stall_qwc_ = n - i;
                        ++stats_.path3_yields;
                        break;
                    }
                }
            }
            s.tag = GifTag::decode(q[i]);
            ++i;
            ++stats_.qwords[p];
            ++stats_.tags[p][s.tag.flg];
            s.open = true;
            owner_ = p;
            s.loop = 0;
            s.reg = 0;
            for (u32 w = 0; w < 4; ++w) last_tag_[w] = q[i - 1].u32[w];
            last_tag_path_ = p;
            if (p == 3) p3_last_tag_ = q[i - 1].u32[0];
            if (fwd_) {
                last_tag_seq_ = fwd_->seq();
                fwd_->gs_tag(p);
                if (s.tag.pre && s.tag.flg == 0) fwd_->gs_reg(p, reg::PRIM, s.tag.prim);
            } else {
                core_.on_gif_tag();
                if (s.tag.pre && s.tag.flg == 0) core_.write_reg(reg::PRIM, s.tag.prim);
            }
            s.in_tag = s.tag.nloop != 0;
            if (!s.in_tag && s.tag.eop) {
                s.open = false;
                owner_ = 0;
                if (p == 3 && p3_window_) p3_window_done_ = true;
            }
            continue;
        }
        switch (s.tag.flg) {
        case 0: { // PACKED: one register per qword; the tag's data in one tight loop (the vertex stream's path)
            const u64 regs = s.tag.regs;
            const u32 nreg = s.tag.nreg, nloop = s.tag.nloop;
            u32 reg = s.reg, loop = s.loop;
            const std::size_t i0 = i;
            while (i < n && loop < nloop) {
                const u32 r = static_cast<u32>(regs >> (4u * reg)) & 0xFu;
                if (fwd_) fwd_->gs_packed(p, r, q[i]);
                else core_.write_packed(r, q[i]);
                ++i;
                if (++reg >= nreg) {
                    reg = 0;
                    ++loop;
                }
            }
            s.reg = reg;
            s.loop = loop;
            stats_.qwords[p] += i - i0;
            break;
        }
        case 1: // REGLIST: two 64-bit registers per qword; an odd tail half is discarded
            for (u32 half = 0; half < 2 && s.loop < s.tag.nloop; ++half) {
                const u32 r = s.tag.reg(s.reg);
                if (r < reg::PACKED_AD) {
                    if (fwd_) fwd_->gs_reg(p, r, q[i].u64[half]);
                    else core_.write_reg(r, q[i].u64[half]);
                }
                else if (r == reg::PACKED_AD) ++stats_.unhandled_reg_writes; // A+D has no meaning in REGLIST
                if (++s.reg >= s.tag.nreg) {
                    s.reg = 0;
                    ++s.loop;
                }
            }
            ++i;
            ++stats_.qwords[p];
            break;
        default: { // IMAGE (2) and the disabled form (3) transfer image data
            const std::size_t take = std::min<std::size_t>(n - i, s.tag.nloop - s.loop);
            if (fwd_) fwd_->gs_image(p, q.subspan(i, take));
            else core_.write_image(q.subspan(i, take));
            i += take;
            stats_.qwords[p] += take;
            s.loop += static_cast<u32>(take);
            break;
        }
        }
        if (s.loop >= s.tag.nloop) {
            s.in_tag = false;
            if (s.tag.eop) {
                s.open = false;
                owner_ = 0;
                if (p == 3 && p3_window_) p3_window_done_ = true;
            }
        }
    }
    return i;
}

void Gif::close_path1() {
    if (path_[1].open || path_[1].in_tag) ++stats_.path1_truncated;
    path_[1] = Path{};
    if (owner_ == 1) owner_ = 0;
}

void Gif::run_path1_queue() {
    if (fwd_) {
        // Pipeline: the queue lives on the VU1 worker; this is the point where the synchronous GIF would run it.
        if (p1_pending_ && owner_ == 0) {
            p1_pending_ = false;
            fwd_->p1_flush();
        }
        return;
    }
    if (running_p1_queue_) return;
    running_p1_queue_ = true;
    while (!p1_queue_.empty() && owner_ == 0) {
        const std::vector<u128> pkt = std::move(p1_queue_.front());
        p1_queue_.pop_front();
        feed(1, pkt);
        close_path1();
    }
    running_p1_queue_ = false;
}

void Gif::path1(std::span<const u128> q) {
    if (owner_ == 0) {
        run_path1_queue();
        if (owner_ == 0 && p1_queue_.empty()) {
            feed(1, q);
            close_path1();
            return;
        }
    }
    p1_queue_.emplace_back(q.begin(), q.end());
    ++stats_.path1_queued;
}

std::size_t Gif::path2(std::span<const u128> q) {
    if (owner_ != 0 && owner_ != 2) {
        p2_waiting_ = true;
        ++stats_.path2_stalls;
        return 0;
    }
    p2_waiting_ = false;
    const std::size_t used = feed(2, q);
    if (owner_ == 0) run_path1_queue();
    return used;
}

std::size_t Gif::path3(std::span<const u128> q) {
    if (owner_ != 0 && owner_ != 3) {
        p3_stalled_ = true;
        p3_stall_qwc_ = q.size();
        return 0;
    }
    const std::size_t used = feed(3, q);
    if (used == q.size()) p3_stalled_ = false;
    if (owner_ == 0) run_path1_queue();
    return used;
}

void Gif::set_m3p(bool masked) {
    const bool was = path3_masked();
    m3p_ = masked;
    if (was && !path3_masked() && path3_ready_) path3_ready_();
}

void Gif::reset() {
    ++stats_.resets;
    for (Path& p : path_) p = Path{};
    owner_ = 0;
    m3p_ = m3r_ = imt_ = pse_ = false;
    p2_waiting_ = p3_stalled_ = false;
    p3_stall_qwc_ = 0;
    p1_queue_.clear();
    if (fwd_) {
        p1_pending_ = false;
        fwd_->p1_clear();
    }
}

u32 Gif::stat() const {
    u32 s = 0;
    if (m3r_) s |= 1u << 0;
    if (m3p_) s |= 1u << 1;
    if (imt_) s |= 1u << 2;
    if (pse_) s |= 1u << 3;
    if (p3_stalled_) s |= 1u << 6;     // P3Q
    if (p2_waiting_) s |= 1u << 7;     // P2Q
    if (!p1_queue_.empty() || (fwd_ && p1_pending_ && fwd_->p1_queued() != 0)) s |= 1u << 8; // P1Q
    if (owner_) s |= (1u << 9) | (owner_ << 10); // OPH, APATH
    if (busdir_ && (*busdir_ & 1u)) s |= 1u << 12;
    if (p3_stalled_) s |= static_cast<u32>(std::min<std::size_t>(p3_stall_qwc_, 16u)) << 24; // FQC (inferred)
    return s;
}

u32 Gif::read_reg(u32 off) const {
    if (fwd_ && off >= 0x40 && off <= 0x80) {
        // TAG0-3 / CNT: the last tag may be a PATH1 tag the worker read (its Path state is reset after each packet,
        // so CNT reads 0 then, as after close_path1).
        u32 t[4];
        if (fwd_->p1_last_tag(last_tag_seq_, t)) return off == 0x80 ? 0u : t[(off - 0x40u) >> 4];
    }
    switch (off) {
    case 0x20: return stat();
    case 0x40: case 0x50: case 0x60: case 0x70: return last_tag_[(off - 0x40u) >> 4];
    case 0x80: {
        const Path& s = path_[last_tag_path_];
        const u32 left = s.in_tag ? s.tag.nloop - s.loop : 0u;
        return (left & 0x7FFFu) | ((s.reg & 0xFu) << 16);
    }
    case 0x90: {
        const Path& s = path_[3];
        return (s.in_tag && s.tag.flg >= 2) ? (s.tag.nloop - s.loop) & 0x7FFFu : 0u;
    }
    case 0xA0: return p3_last_tag_ & 0xFFFFu;
    default: return 0; // CTRL and MODE are write-only
    }
}

void Gif::write_reg(u32 off, u32 v) {
    switch (off) {
    case 0x00:
        if (v & 1u) reset();
        pse_ = ((v >> 3) & 1u) != 0;
        break;
    case 0x10: {
        const bool was = path3_masked();
        m3r_ = (v & 1u) != 0;
        imt_ = ((v >> 2) & 1u) != 0;
        if (was && !path3_masked() && path3_ready_) path3_ready_();
        break;
    }
    default: ++stats_.unhandled_reg_writes; break;
    }
}

void GifFifoDevice::write128(u32, const u128& v) {
    pending_.push_back(v);
    drain();
}

void GifFifoDevice::drain() {
    if (pending_.empty()) return;
    const std::size_t used = gif_.path3(pending_);
    pending_.erase(pending_.begin(), pending_.begin() + static_cast<std::ptrdiff_t>(used));
}

} // namespace p3fes::gs
