// VIF1 command processor. VIFcode encodings, data lengths, the UNPACK write-cycle / mask / mode rules and the
// MSCAL double-buffer register update follow the EE User's Manual VIF chapter, cross-checked against
// ps2-web-recomp @ c0f476e runtime/src/vif.cpp (unpack_words, run_vu, unpack, execute; MIT). The word-stream
// state machine (commands split across DMA transfers, backlog, stalls) is our own.
#include "p3fes/gs/vif1.h"
#include "p3fes/prof.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace p3fes::gs {

namespace {
constexpr u32 kStatVgw = 1u << 3, kStatMrk = 1u << 6, kStatDbf = 1u << 7, kStatVss = 1u << 8, kStatVfs = 1u << 9,
              kStatVis = 1u << 10, kStatInt = 1u << 11, kStatEr0 = 1u << 12, kStatEr1 = 1u << 13;
constexpr u32 kStallMask = kStatVss | kStatVfs | kStatVis | kStatInt | kStatEr0 | kStatEr1;
constexpr unsigned kIntcVif1 = 5;

u32 unpack_words(u32 code, u32 cycle) {
    const u32 cmd = (code >> 24) & 0x7Fu;
    const u32 vn = (cmd >> 2) & 3u, vl = cmd & 3u;
    u32 num = (code >> 16) & 0xFFu;
    if (num == 0) num = 256;
    const u32 cl = cycle & 0xFFu, wl = (cycle >> 8) & 0xFFu;
    const u32 vectors = (wl > cl && wl != 0) ? (num / wl) * cl + std::min(num % wl, cl) : num;
    const u32 ebits = vl == 0 ? 32u : (vl == 1 ? 16u : 8u);
    const u32 vbits = (vn == 3 && vl == 3) ? 16u : (vn + 1u) * ebits;
    return (vectors * vbits + 31u) / 32u;
}
} // namespace

const char* to_string(VifTrapKind k) noexcept {
    switch (k) {
    case VifTrapKind::InvalidCode: return "invalid VIFcode";
    case VifTrapKind::InvalidUnpack: return "invalid UNPACK format";
    case VifTrapKind::VuTrap: return "VU1 trap";
    case VifTrapKind::VuStepLimit: return "VU1 step limit";
    case VifTrapKind::Vif0Used: return "VIF0 data (unused by the game)";
    }
    return "?";
}

void Vif1::report(const VifTrap& t) {
    ++stats_.traps;
    if (trap_) {
        trap_(t);
    } else {
        std::fprintf(stderr, "p3fes gs: VIF1 trap: %s (code 0x%08X)\n", to_string(t.kind), t.code);
    }
}

void Vif1::reset_state() {
    err_ = mark_ = cycle_ = mode_ = num_ = mask_ = code_ = 0;
    itops_ = base_ = ofst_ = tops_ = itop_ = top_ = 0;
    std::memset(row_, 0, sizeof row_);
    std::memset(col_, 0, sizeof col_);
    dbf_ = mrk_ = false;
    stall_flags_ = 0;
    gif_wait_ = false;
    state_ = State::Idle;
    cmd_ = skip_ = need_ = 0;
    buf_.clear();
    direct_part_n_ = 0;
    word_pos_ = 0;
    backlog_.clear();
    gif_.set_path2_waiting(false);
}

void Vif1::finish_code() {
    state_ = State::Idle;
    buf_.clear();
    num_ = 0;
    if ((code_ & 0x80000000u) && !(err_ & 1u)) { // interrupt bit, not masked by ERR.MII
        stall_flags_ |= kStatVis | kStatInt;
        ++stats_.interrupts;
        if (bus_) bus_->raise_intc(kIntcVif1);
    }
}

void Vif1::run_vu(u32 op, u32 imm) {
    top_ = tops_;
    itop_ = itops_;
    dbf_ = !dbf_;
    tops_ = base_ + (dbf_ ? ofst_ : 0u);
    if (pipe_) {
        ++stats_.vu_runs;
        pipe_->vu_run(op, imm, top_, itop_, code_, vu_step_limit_);
        return;
    }
    vu_.set_tops(top_, itop_);
    VuRunInfo hook_info;
    if (run_hook_) [[unlikely]] {  // the native renderer (play mode only; docs/ANALYSIS/31 §3.3)
        hook_info.op = op;
        hook_info.imm = imm;
        hook_info.top = top_;
        hook_info.itop = itop_;
        hook_info.gif_busy = !gif_.idle();
        bool handled;
        {
            const prof::Scope prof_zone(prof::Zone::Vu1);
            handled = run_hook_->run(hook_info, vu_);
        }
        if (handled) {
            ++hooked_runs_;
            ++stats_.vu_runs;
            return;
        }
    }
    vu1::RunResult r;
    const u32 start_pair = op == 0x17 ? vu_.state().tpc / 8u : imm;
    const u64 vu_ticks0 = prof::cur().ticks[static_cast<unsigned>(prof::Zone::Vu1)];
    {
        const prof::Scope prof_zone(prof::Zone::Vu1);
        if (op == 0x17) r = vu_.mscnt(vu_step_limit_);
        else if (op == 0x15) r = vu_.mscalf(imm, vu_step_limit_);
        else r = vu_.mscal(imm, vu_step_limit_);
    }
    prof::vu1_run(start_pair, r.steps, prof::cur().ticks[static_cast<unsigned>(prof::Zone::Vu1)] - vu_ticks0);
    ++stats_.vu_runs;
    stats_.vu_pairs += r.steps;
    if (run_hook_) [[unlikely]]
        run_hook_->after_exact(hook_info, vu_);
    if (r.status == vu1::RunStatus::Trapped) {
        VifTrap t;
        t.kind = VifTrapKind::VuTrap;
        t.code = code_;
        t.vu = vu_.trap();
        report(t);
    } else if (r.status == vu1::RunStatus::StepLimit) {
        VifTrap t;
        t.kind = VifTrapKind::VuStepLimit;
        t.code = code_;
        report(t);
    }
}

void Vif1::begin_code(u32 code) {
    code_ = code;
    const u32 cmd = (code >> 24) & 0x7Fu;
    const u32 imm = code & 0xFFFFu;
    const u32 num = (code >> 16) & 0xFFu;
    cmd_ = cmd;
    ++stats_.codes[cmd];
    switch (cmd) {
    case 0x00: finish_code(); break; // NOP
    case 0x01: cycle_ = imm; finish_code(); break; // STCYCL: CL = imm[7:0], WL = imm[15:8]
    case 0x02: // OFFSET
        ofst_ = imm & 0x3FFu;
        dbf_ = false;
        tops_ = base_;
        finish_code();
        break;
    case 0x03: base_ = imm & 0x3FFu; finish_code(); break;  // BASE
    case 0x04: itops_ = imm & 0x3FFu; finish_code(); break; // ITOP
    case 0x05: mode_ = imm & 3u; finish_code(); break;      // STMOD
    case 0x06: gif_.set_m3p(((imm >> 15) & 1u) != 0); finish_code(); break; // MSKPATH3
    case 0x07: mark_ = imm; mrk_ = true; finish_code(); break; // MARK
    case 0x10: // FLUSHE: the VU is never running here
    case 0x11: // FLUSH: PATH1 packets are complete (or queued in the GIF) when the VU returns
        finish_code();
        break;
    case 0x13: // FLUSHA: wait for the end of the PATH3 transfer (Gif::path3_pending: GIF mid-packet, stalled
               // PATH3 data, or DMAC channel 2 still running)
        if (gif_.path3_pending()) {
            state_ = State::Skip; // reused as "waiting for FLUSHA"
            need_ = 0;
            gif_wait_ = true;
        } else {
            finish_code();
        }
        break;
    case 0x14: case 0x15: case 0x17: // MSCAL, MSCALF, MSCNT
        run_vu(cmd, imm);
        finish_code();
        break;
    case 0x20: state_ = State::Imm; need_ = 1; break;      // STMASK
    case 0x30: case 0x31: state_ = State::Imm; need_ = 4; break; // STROW, STCOL
    case 0x4A: // MPG: data starts at a 64-bit boundary
        state_ = State::Mpg;
        need_ = (num ? num : 256u) * 2u;
        skip_ = static_cast<u32>(word_pos_ & 1u);
        num_ = num;
        break;
    case 0x50: case 0x51: // DIRECT, DIRECTHL: data starts at a qword boundary
        state_ = State::Direct;
        need_ = imm ? imm : 0x10000u;
        skip_ = static_cast<u32>((4u - (word_pos_ & 3u)) & 3u);
        direct_part_n_ = 0;
        break;
    default:
        if ((cmd & 0x60u) == 0x60u) { // UNPACK
            const u32 vn = (cmd >> 2) & 3u, vl = cmd & 3u;
            if (vl == 3 && vn != 3) {
                VifTrap t;
                t.kind = VifTrapKind::InvalidUnpack;
                t.code = code;
                stall_flags_ |= kStatEr1;
                report(t);
                state_ = State::Idle;
                break;
            }
            state_ = State::Unpack;
            need_ = unpack_words(code, cycle_);
            num_ = num ? num : 256u;
            if (need_ == 0) {
                exec_unpack();
                finish_code();
            }
            break;
        }
        {
            VifTrap t;
            t.kind = VifTrapKind::InvalidCode;
            t.code = code;
            if (!(err_ & 4u)) stall_flags_ |= kStatEr1; // ERR.ME1 masks the VIFcode error stall
            report(t);
            state_ = State::Idle;
        }
        break;
    }
}

u32 unpack_data_words(u32 code, u32 cycle) { return unpack_words(code, cycle); }

namespace {

// Unmasked UNPACK with no filling write (WL <= CL) of a byte-aligned format (S/V2/V3/V4 x 32/16/8 bits): the same
// result as unpack_generic, element by element from byte offsets. MODE 0/1/2 as there; V3 leaves W = 0 (+ ROW).
template <u32 Comps, u32 Bytes, bool Usn>
void unpack_fast(const UnpackArgs& a, const u8* src, u8* mem, u32 row[4]) {
    const u32 code = a.code;
    u32 num = (code >> 16) & 0xFFu;
    if (num == 0) num = 256;
    u32 addr = (code & 0x3FFu) + (((code >> 15) & 1u) ? a.tops : 0u);
    const u32 cl = a.cycle & 0xFFu, wl = (a.cycle >> 8) & 0xFFu;
    const u32 mode = a.mode;
    u32 cyc = 0;
    for (u32 n = 0; n < num; ++n) {
        u32 val[4] = {0, 0, 0, 0};
        for (u32 j = 0; j < Comps; ++j) {
            if constexpr (Bytes == 4) {
                std::memcpy(&val[j], src, 4);
            } else if constexpr (Bytes == 2) {
                u16 h;
                std::memcpy(&h, src, 2);
                val[j] = Usn ? h : static_cast<u32>(static_cast<s32>(static_cast<s16>(h)));
            } else {
                val[j] = Usn ? *src : static_cast<u32>(static_cast<s32>(static_cast<s8>(*src)));
            }
            src += Bytes;
        }
        if constexpr (Comps == 1) val[1] = val[2] = val[3] = val[0];
        if constexpr (Comps == 2) {
            val[2] = val[0];
            val[3] = val[1];
        }
        if (mode == 1) {
            for (u32 j = 0; j < 4; ++j) val[j] += row[j];
        } else if (mode == 2) {
            for (u32 j = 0; j < 4; ++j) row[j] = val[j] += row[j];
        }
        if (mem) std::memcpy(mem + (addr & 1023u) * 16u, val, 16);
        ++addr;
        ++cyc;
        if (wl != 0 && cyc >= wl) {
            addr += cl - wl;
            cyc = 0;
        }
    }
}

template <u32 Comps, u32 Bytes>
void unpack_fast_usn(const UnpackArgs& a, const u8* src, u8* mem, u32 row[4]) {
    if ((a.code >> 14) & 1u) unpack_fast<Comps, Bytes, true>(a, src, mem, row);
    else unpack_fast<Comps, Bytes, false>(a, src, mem, row);
}

} // namespace

u32 vif_unpack(const UnpackArgs& a, const u32* words, std::size_t nwords, u8* mem, u32 row[4]) {
    const u32 code = a.code;
    const u32 cmd = (code >> 24) & 0x7Fu;
    const u32 vn = (cmd >> 2) & 3u, vl = cmd & 3u;
    const bool masked = ((cmd >> 4) & 1u) != 0;
    const bool usn = ((code >> 14) & 1u) != 0;
    const bool flg = ((code >> 15) & 1u) != 0;
    u32 num = (code >> 16) & 0xFFu;
    if (num == 0) num = 256;
    // Registers only (the threaded pipeline's EE side): just the ROW update of mode 2.
    if (!mem && a.mode != 2) return num;
    // Unmasked, no filling write (WL <= CL), byte-aligned formats: element loops without the generic bit reader.
    {
        const u32 cl0 = a.cycle & 0xFFu, wl0 = (a.cycle >> 8) & 0xFFu;
        if (!masked && wl0 <= cl0 && vl != 3 && a.mode <= 2 && nwords >= unpack_words(code, a.cycle)) {
            const u8* src = reinterpret_cast<const u8*>(words);
            switch (cmd & 0x0Fu) {
            case 0x0: unpack_fast_usn<1, 4>(a, src, mem, row); return num;
            case 0x1: unpack_fast_usn<1, 2>(a, src, mem, row); return num;
            case 0x2: unpack_fast_usn<1, 1>(a, src, mem, row); return num;
            case 0x4: unpack_fast_usn<2, 4>(a, src, mem, row); return num;
            case 0x5: unpack_fast_usn<2, 2>(a, src, mem, row); return num;
            case 0x6: unpack_fast_usn<2, 1>(a, src, mem, row); return num;
            case 0x8: unpack_fast_usn<3, 4>(a, src, mem, row); return num;
            case 0x9: unpack_fast_usn<3, 2>(a, src, mem, row); return num;
            case 0xA: unpack_fast_usn<3, 1>(a, src, mem, row); return num;
            case 0xC: unpack_fast_usn<4, 4>(a, src, mem, row); return num;
            case 0xD: unpack_fast_usn<4, 2>(a, src, mem, row); return num;
            case 0xE: unpack_fast_usn<4, 1>(a, src, mem, row); return num;
            default: break;
            }
        }
    }    u32 addr = (code & 0x3FFu) + (flg ? a.tops : 0u);
    const u32 cl = a.cycle & 0xFFu, wl = (a.cycle >> 8) & 0xFFu;
    const bool v45 = vn == 3 && vl == 3;
    const u32 ebits = v45 ? 16u : (vl == 0 ? 32u : (vl == 1 ? 16u : 8u));
    const u32 comps = v45 ? 1u : vn + 1u;
    std::size_t bitpos = 0;
    const auto next = [&]() -> u32 {
        const std::size_t word = bitpos >> 5, sh = bitpos & 31u;
        u64 raw = word < nwords ? words[word] : 0u;
        if (word + 1 < nwords) raw |= static_cast<u64>(words[word + 1]) << 32;
        u32 v = static_cast<u32>(raw >> sh);
        if (ebits < 32) v &= (1u << ebits) - 1u;
        bitpos += ebits;
        return v;
    };
    u32 cyc = 0;
    for (u32 n = 0; n < num; ++n) {
        const bool fill = wl > cl && cyc >= cl;
        u32 val[4] = {0, 0, 0, 0};
        if (!fill) {
            if (v45) {
                const u32 c = next();
                val[0] = (c & 0x1Fu) << 3;
                val[1] = ((c >> 5) & 0x1Fu) << 3;
                val[2] = ((c >> 10) & 0x1Fu) << 3;
                val[3] = ((c >> 15) & 1u) << 7;
            } else {
                for (u32 j = 0; j < comps; ++j) {
                    u32 e = next();
                    if (!usn && ebits == 16) e = static_cast<u32>(static_cast<s32>(static_cast<s16>(e)));
                    if (!usn && ebits == 8) e = static_cast<u32>(static_cast<s32>(static_cast<s8>(e)));
                    val[j] = e;
                }
                if (comps == 1) val[1] = val[2] = val[3] = val[0];
                else if (comps == 2) {
                    val[2] = val[0];
                    val[3] = val[1];
                }
            }
        }
        const u32 mrow = std::min<u32>(cyc, 3u);
        u8* qp = mem ? mem + (addr & 1023u) * 16u : nullptr;
        for (u32 j = 0; j < 4; ++j) {
            u32 m = masked ? (a.mask >> ((mrow * 4u + j) * 2u)) & 3u : 0u;
            if (fill && m == 0) m = 1; // filling write with no mask: the row register (upstream behaviour)
            if (m == 3) continue;      // write-protected
            u32 out;
            if (m == 1) out = row[j];
            else if (m == 2) out = a.col[mrow];
            else if (a.mode == 1) out = val[j] + row[j];
            else if (a.mode == 2) {
                out = val[j] + row[j];
                row[j] = out;
            } else out = val[j];
            if (qp) std::memcpy(qp + j * 4u, &out, 4);
        }
        ++addr;
        ++cyc;
        if (cl >= wl) {
            if (wl != 0 && cyc >= wl) {
                addr += cl - wl;
                cyc = 0;
            }
        } else if (cyc >= wl) {
            cyc = 0;
        }
    }
    return num;
}

void Vif1::exec_unpack(const u32* words, std::size_t n) {
    UnpackArgs a;
    a.code = code_;
    a.cycle = cycle_;
    a.mode = mode_;
    a.mask = mask_;
    a.tops = tops_;
    std::memcpy(a.row, row_, sizeof row_);
    std::memcpy(a.col, col_, sizeof col_);
    if (pipe_) {
        // The VU1 stage writes VU1 memory with ROW as it was; the EE side keeps VIF1's own registers (mode 2).
        stats_.unpack_qwords += vif_unpack(a, words, n, nullptr, row_);
        if (n) {
            std::memcpy(pipe_->unpack_reserve(a, static_cast<u32>(n)), words, n * 4u);
            pipe_->reserve_done();
        } else {
            pipe_->unpack(a, words, 0);
        }
        return;
    }
    stats_.unpack_qwords += vif_unpack(a, words, n, vu_.state().data, row_);
}

std::size_t Vif1::run_words(const u32* w, std::size_t n, bool aligned_source) {
    std::size_t i = 0;
    gif_wait_ = false;
    for (;;) {
        if (stall_flags_) break;
        // States that can make progress without input: a pending assembled DIRECT qword, a FLUSHA wait.
        const bool needs_input = !(state_ == State::Skip || (state_ == State::Direct && direct_part_n_ == 4));
        if (needs_input && i >= n) break;
        switch (state_) {
        case State::Idle:
            ++word_pos_;
            begin_code(w[i++]);
            break;
        case State::Skip: // FLUSHA wait
            if (gif_.path3_pending()) {
                gif_wait_ = true;
                return i;
            }
            finish_code();
            break;
        case State::Imm:
            buf_.push_back(w[i++]);
            ++word_pos_;
            if (buf_.size() >= need_) {
                if (cmd_ == 0x20) mask_ = buf_[0];
                else if (cmd_ == 0x30) std::memcpy(row_, buf_.data(), 16);
                else std::memcpy(col_, buf_.data(), 16);
                finish_code();
            }
            break;
        case State::Mpg:
            if (skip_) {
                --skip_;
                ++i;
                ++word_pos_;
                break;
            }
        {
            // The payload in bulk: straight from the stream when it is all here, else gathered across transfers.
            const u32* data;
            if (buf_.empty() && n - i >= need_) {
                data = w + i;
                if (prof::on()) mpg_src_ = data;  // VU1 program attribution (prof.h)
                i += need_;
                word_pos_ += need_;
            } else {
                const std::size_t take = std::min<std::size_t>(need_ - buf_.size(), n - i);
                if (buf_.empty() && prof::on()) mpg_src_ = w + i;
                buf_.insert(buf_.end(), w + i, w + i + take);
                i += take;
                word_pos_ += take;
                if (buf_.size() < need_) break;
                data = buf_.data();
            }
            stats_.mpg_pairs += need_ / 2u;
            if (pipe_) {
                std::memcpy(pipe_->mpg_reserve((code_ & 0xFFFFu) * 8u, need_, mpg_src_), data, need_ * 4u);
                pipe_->reserve_done();
            } else {
                vu_.load_micro((code_ & 0xFFFFu) * 8u, std::span<const u8>(reinterpret_cast<const u8*>(data), need_ * 4u));
                prof::vu1_mpg(code_ & 0xFFFFu, need_ / 2u, mpg_src_);
            }
            finish_code();
            break;
        }
        case State::Unpack: {
            const u32* data;
            if (buf_.empty() && n - i >= need_) {
                data = w + i;
                i += need_;
                word_pos_ += need_;
            } else {
                const std::size_t take = std::min<std::size_t>(need_ - buf_.size(), n - i);
                buf_.insert(buf_.end(), w + i, w + i + take);
                i += take;
                word_pos_ += take;
                if (buf_.size() < need_) break;
                data = buf_.data();
            }
            exec_unpack(data, need_);
            finish_code();
            break;
        }
        case State::Direct: {
            if (skip_) {
                --skip_;
                ++i;
                ++word_pos_;
                break;
            }
            if (direct_part_n_ == 4) { // a qword assembled from unaligned words waits for the GIF
                u128 q;
                std::memcpy(&q, direct_part_, 16);
                if (gif_.path2(std::span<const u128>(&q, 1)) == 0) {
                    gif_wait_ = true;
                    ++stats_.gif_stalls;
                    return i;
                }
                direct_part_n_ = 0;
                ++stats_.direct_qwords;
                if (--need_ == 0) finish_code();
                break;
            }
            const u32* p = w + i;
            const bool aligned = aligned_source && (reinterpret_cast<std::uintptr_t>(p) & 15u) == 0;
            if (aligned && direct_part_n_ == 0 && n - i >= 4) {
                const std::size_t count = std::min<std::size_t>(need_, (n - i) / 4u);
                const std::size_t used = gif_.path2(std::span<const u128>(reinterpret_cast<const u128*>(p), count));
                i += used * 4u;
                word_pos_ += used * 4u;
                need_ -= static_cast<u32>(used);
                stats_.direct_qwords += used;
                if (need_ == 0) finish_code();
                else if (used < count) {
                    gif_wait_ = true;
                    ++stats_.gif_stalls;
                    return i;
                }
                break;
            }
            direct_part_[direct_part_n_++] = w[i++];
            ++word_pos_;
            break;
        }
        }
    }
    return i;
}

std::size_t Vif1::transfer(std::span<const u128> q) {
    if (stall_flags_) return 0;
    const prof::Scope prof_zone(prof::Zone::Vif1);
    if (!backlog_.empty()) {
        const std::size_t used = run_words(backlog_.data(), backlog_.size(), false);
        backlog_.erase(backlog_.begin(), backlog_.begin() + static_cast<std::ptrdiff_t>(used));
        if (!backlog_.empty() || stall_flags_) return 0;
    }
    const u32* w = reinterpret_cast<const u32*>(q.data());
    const std::size_t n = q.size() * 4u;
    const std::size_t used = run_words(w, n, true);
    const std::size_t full = used / 4u, rem = used % 4u;
    if (rem) {
        // Stalled inside a qword: keep its remaining words so the DMAC can treat the qword as consumed.
        backlog_.assign(w + used, w + (full + 1u) * 4u);
        return full + 1u;
    }
    return full;
}

void Vif1::fifo_write(const u128& q) {
    backlog_.insert(backlog_.end(), q.u32, q.u32 + 4);
    resume();
}

void Vif1::resume() {
    if (stall_flags_ || backlog_.empty()) return;
    const prof::Scope prof_zone(prof::Zone::Vif1);
    const std::size_t used = run_words(backlog_.data(), backlog_.size(), false);
    backlog_.erase(backlog_.begin(), backlog_.begin() + static_cast<std::ptrdiff_t>(used));
}

u128 Vif1::fifo_read() {
    if (pipe_) pipe_->drain(SyncWhy::LocalRead);  // local -> host: GS memory as every command so far left it
    u128 out{};
    core_.read_image(std::span<u128>(&out, 1));
    return out;
}

u32 Vif1::read_reg(u32 off) const {
    switch (off) {
    case 0x00: {
        u32 s = 0;
        if (state_ != State::Idle || !backlog_.empty()) s |= state_ == State::Direct ? 3u : 1u; // VPS
        if (gif_wait_) s |= kStatVgw;
        if (mrk_) s |= kStatMrk;
        if (dbf_) s |= kStatDbf;
        s |= stall_flags_;
        if (busdir_ && (*busdir_ & 1u)) s |= 1u << 23; // FDR
        s |= static_cast<u32>(std::min<std::size_t>(backlog_.size() / 4u, 16u)) << 24; // FQC
        return s;
    }
    case 0x20: return err_;
    case 0x30: return mark_;
    case 0x40: return cycle_;
    case 0x50: return mode_;
    case 0x60: return num_;
    case 0x70: return mask_;
    case 0x80: return code_;
    case 0x90: return itops_;
    case 0xA0: return base_;
    case 0xB0: return ofst_;
    case 0xC0: return tops_;
    case 0xD0: return itop_;
    case 0xE0: return top_;
    default:
        if (off >= 0x100 && off < 0x140 && (off & 0xFu) == 0) return row_[(off - 0x100u) >> 4];
        if (off >= 0x140 && off < 0x180 && (off & 0xFu) == 0) return col_[(off - 0x140u) >> 4];
        return 0; // FBRST is write-only
    }
}

void Vif1::write_reg(u32 off, u32 v) {
    switch (off) {
    case 0x10: // FBRST
        if (v & 1u) reset_state();
        if (v & 2u) stall_flags_ |= kStatVfs;
        if (v & 4u) stall_flags_ |= kStatVss;
        if (v & 8u) {
            stall_flags_ &= ~kStallMask;
            resume();
        }
        break;
    case 0x20: err_ = v & 7u; break;
    case 0x30:
        mark_ = v & 0xFFFFu;
        mrk_ = false;
        break;
    default: break; // the other VIF1 registers are read-only
    }
}

std::size_t Vif1DmaHandler::transfer(u128* data, std::size_t qwc, u64 tag) {
    (void)tag;
    if (busdir_ && (*busdir_ & 1u)) { // local -> host: the channel runs from the VIF into memory
        for (std::size_t i = 0; i < qwc; ++i) data[i] = vif_.fifo_read();
        return qwc;
    }
    return vif_.transfer(std::span<const u128>(data, qwc));
}

u32 Vif0StubDevice::read32(u32 pa) {
    switch (pa - kBase) {
    case 0x20: return err_;
    case 0x30: return mark_;
    default: return 0; // STAT idle; everything else reads 0
    }
}

void Vif0StubDevice::write32(u32 pa, u32 v) {
    switch (pa - kBase) {
    case 0x20: err_ = v & 7u; break;
    case 0x30: mark_ = v & 0xFFFFu; break;
    default: break; // FBRST and the rest are accepted (the game resets VIF0 once, B-42)
    }
}

void Vif0StubDevice::write128(u32 pa, const u128& v) {
    (void)pa;
    ++data_traps_;
    VifTrap t;
    t.kind = VifTrapKind::Vif0Used;
    t.code = v.u32[0];
    if (trap_ && *trap_) (*trap_)(t);
    else std::fprintf(stderr, "p3fes gs: VIF0 FIFO write (VIF0 is unused by the game)\n");
}

std::size_t Vif0DmaTrap::transfer(u128* data, std::size_t qwc, u64 tag) {
    (void)tag;
    if (qwc) dev_.write128(Vif0StubDevice::kFifoBase, data[0]);
    return qwc;
}

} // namespace p3fes::gs
