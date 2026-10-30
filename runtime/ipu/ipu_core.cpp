// IPU command engine: registers, input FIFO + bit-stream buffer, output FIFO, the ten commands. Written for
// p3fes-port (no upstream text); the register semantics the game depends on are derived from its own
// libmpeg/libipu (recomp/generated; runtime/ipu/README.md "Game usage"), the MPEG reconstruction from
// ISO/IEC 13818-2 / 11172-2 (runtime/ipu/mpeg2.cpp).
#include "p3fes/ipu/ipu_core.h"
#include "p3fes/state_io.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace p3fes::ipu {

using namespace mpeg2;

namespace {

std::string format(const char* fmt, ...) {
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    return buf;
}

inline int clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

} // namespace

IpuCore::IpuCore(IpuCosts costs) : costs_(costs) { power_on(); }

void IpuCore::state(StateIo& io) {
    io.section("ipu");
    io(in_, in_head_, in_count_, bp_, cur_, out_, out_head_, out_count_, pend_, pend_qw_, pend_pos_);
    io(mode_, lmode_, ecd_, scd_, cbp_, data_, iq_intra_, iq_nonintra_, vqclut_, th0_, th1_, dc_);
    io(cmd_, busy_, finished_, work_done_, issue_at_, complete_at_, phase_, after_fb_);
    io(load_total_, load_n_, load_, mb_left_, intra_, field_dct_, qsc_, cbp_mb_, blk_, k_, qf_, blocks_, stats_);
}

void IpuCore::power_on() {
    reset_fifos();
    mode_ = lmode_ = 0;
    ecd_ = scd_ = false;
    cbp_ = 0;
    data_ = 0;
    std::memcpy(iq_intra_, kDefaultIntraMatrix, 64);
    std::fill(std::begin(iq_nonintra_), std::end(iq_nonintra_), u8{16});
    std::fill(std::begin(vqclut_), std::end(vqclut_), u16{0});
    th0_ = th1_ = 0;
    dc_[0] = dc_[1] = dc_[2] = 128;
    cmd_ = 0;
    busy_ = finished_ = work_done_ = false;
    issue_at_ = 0;
    complete_at_ = kNever;
    phase_ = after_fb_ = Phase::Idle;
    stats_ = {};
}

void IpuCore::reset_fifos() noexcept {
    in_head_ = in_count_ = bp_ = cur_ = 0;
    out_head_ = out_count_ = 0;
    pend_qw_ = pend_pos_ = 0;
}

void IpuCore::trap(IpuTrap::Kind k, u32 pa, u64 value, std::string msg) {
    IpuTrap t;
    t.kind = k;
    t.pa = pa;
    t.value = value;
    t.message = std::move(msg);
    if (on_trap_) on_trap_(t);
    else std::fprintf(stderr, "[ipu] trap: %s\n", t.message.c_str());
}

// ---- bit access ---------------------------------------------------------------------------------------------

u8 IpuCore::in_byte(unsigned b) const noexcept {
    if (b >= in_count_ * 16u) return 0;
    return in_[(in_head_ + (b >> 4)) & 15u][b & 15u];
}

unsigned IpuCore::avail() const noexcept {
    const unsigned total = in_count_ * 128u;
    return total > cur_ ? total - cur_ : 0u;
}

unsigned IpuCore::buffered_bits() const noexcept {
    const unsigned total = in_count_ * 128u;
    return total > bp_ ? total - bp_ : 0u;
}

// The 32 bits at the cursor, MSB first (bytes in FIFO order, bits MSB first: the MPEG byte stream), zero past
// the buffered data.
u32 IpuCore::window() const noexcept {
    const unsigned b0 = cur_ >> 3;
    u64 v = 0;
    for (unsigned i = 0; i < 5; ++i) v = (v << 8) | in_byte(b0 + i);
    v <<= (cur_ & 7u);
    return static_cast<u32>(v >> 8);
}

bool IpuCore::take(unsigned n, u32& v) noexcept {
    if (n == 0) {
        v = 0;
        return true;
    }
    if (avail() < n) return false;
    v = window() >> (32u - n);
    cur_ += n;
    return true;
}

// The step's consumption becomes real: BP moves, fully consumed qwords leave the buffer (freeing FIFO space).
void IpuCore::commit() noexcept {
    bp_ = cur_;
    while (bp_ >= 128u && in_count_ > 0) {
        in_head_ = (in_head_ + 1u) & 15u;
        --in_count_;
        bp_ -= 128u;
    }
}

void IpuCore::push_in(const u128& q) noexcept {
    std::memcpy(in_[(in_head_ + in_count_) & 15u], &q, 16);
    ++in_count_;
    ++stats_.in_qwords;
}

// ---- output staging ---------------------------------------------------------------------------------------

void IpuCore::stage(const u8* bytes, unsigned qwords) noexcept {
    std::memcpy(pend_, bytes, std::size_t{qwords} * 16u);
    pend_qw_ = qwords;
    pend_pos_ = 0;
    drain_stage();
}

void IpuCore::drain_stage() noexcept {
    while (pend_pos_ < pend_qw_ && out_count_ < kOutFifoQw) {
        std::memcpy(out_[(out_head_ + out_count_) & (kOutFifoQw - 1u)], pend_ + std::size_t{pend_pos_} * 16u, 16);
        ++out_count_;
        ++pend_pos_;
    }
    if (pend_pos_ == pend_qw_) pend_pos_ = pend_qw_ = 0;
}

// ---- time ---------------------------------------------------------------------------------------------------

u64 IpuCore::update(u64 now) {
    if (busy_ && work_done_ && now >= complete_at_) {
        busy_ = false;
        work_done_ = false;
        phase_ = Phase::Idle;
        complete_at_ = kNever;
        ++stats_.interrupts;
        if (on_complete_) on_complete_();
    }
    return busy_ && work_done_ ? complete_at_ : kNever;
}

// ---- registers ----------------------------------------------------------------------------------------------

void IpuCore::write_cmd(u32 v, u64 now) {
    update(now);
    const unsigned c = v >> 28;
    if (busy_) {
        trap(IpuTrap::Kind::CommandWhileBusy, kIpuCmd, v,
             format("IPU_CMD 0x%08X (%s) written while 0x%08X (%s) is in progress (issued at cycle %llu); ignored", v,
                    kCmdName[c], cmd_, kCmdName[code()], static_cast<unsigned long long>(issue_at_)));
        return;
    }
    if (c >= 10) {
        ++stats_.commands[c];
        trap(IpuTrap::Kind::ReservedCommand, kIpuCmd, v, format("IPU_CMD 0x%08X: reserved command code 0x%X", v, c));
        return;
    }
    start(v, now);
    run(now);
    update(now);
}

void IpuCore::start(u32 v, u64 now) {
    const unsigned c = v >> 28;
    ++stats_.commands[c];
    cmd_ = v;
    lmode_ = mode_;
    busy_ = true;
    finished_ = work_done_ = false;
    issue_at_ = now;
    complete_at_ = kNever;
    ecd_ = scd_ = false;
    const unsigned dc_reset = 1u << (7u + ((lmode_ >> kCtrlIdpShift) & 3u));
    switch (static_cast<Cmd>(c)) {
    case Cmd::Bclr:
        in_head_ = in_count_ = 0;
        bp_ = v & kBpMask;
        finished_ = true;
        break;
    case Cmd::Setth:
        th0_ = v & 0x1FFu;
        th1_ = (v >> 16) & 0x1FFu;
        finished_ = true;
        break;
    case Cmd::Fdec: after_fb_ = Phase::Fdec; break;
    case Cmd::Vdec: after_fb_ = Phase::Vdec; break;
    case Cmd::Setiq:
    case Cmd::Setvq:
        load_total_ = static_cast<Cmd>(c) == Cmd::Setiq ? 64u : 32u;
        load_n_ = 0;
        after_fb_ = Phase::LoadBytes;
        break;
    case Cmd::Csc:
    case Cmd::Pack:
        mb_left_ = cmd_mbc(v);
        load_total_ = static_cast<Cmd>(c) == Cmd::Csc ? kRaw8Bytes : kRgb32Bytes;
        load_n_ = 0;
        after_fb_ = Phase::LoadBytes;
        if (mb_left_ == 0) finished_ = true;
        break;
    case Cmd::Bdec:
        intra_ = cmd_bit(v, 27);
        field_dct_ = cmd_bit(v, 25);
        qsc_ = cmd_qsc(v);
        if (cmd_bit(v, 26)) dc_[0] = dc_[1] = dc_[2] = static_cast<int>(dc_reset);
        after_fb_ = Phase::BdecCbp;
        break;
    case Cmd::Idec:
        intra_ = true;
        field_dct_ = false;
        qsc_ = cmd_qsc(v);
        dc_[0] = dc_[1] = dc_[2] = static_cast<int>(dc_reset);  // a slice starts: predictors reset (§7.2.1)
        if (cmd_bit(v, 25))
            trap(IpuTrap::Kind::Unsupported, kIpuCmd, v,
                 format("IDEC 0x%08X with SGN = 1: the pseudo-sign offset is not modelled (treated as 0)", v));
        after_fb_ = Phase::IdecHeader;
        break;
    }
    if (finished_) {
        phase_ = Phase::Idle;
        return;
    }
    const bool has_fb = static_cast<Cmd>(c) != Cmd::Csc && static_cast<Cmd>(c) != Cmd::Pack;
    phase_ = has_fb && cmd_fb(v) != 0 ? Phase::SkipFb : after_fb_;
}

void IpuCore::write_ctrl(u32 v, u64 now) {
    update(now);
    if (v & kCtrlRst) {
        // Reset: FIFOs, bit pointer, the command in progress (no completion interrupt), status bits. The quantiser
        // matrices, VQ CLUT and thresholds survive (sceIpuInit loads them before its final reset; README "Data path").
        reset_fifos();
        busy_ = finished_ = work_done_ = false;
        phase_ = Phase::Idle;
        complete_at_ = kNever;
        ecd_ = scd_ = false;
        cbp_ = 0;
    }
    mode_ = v & kCtrlModeMask;
}

u64 IpuCore::read_cmd(u64 now) {
    update(now);
    return u64{data_} | (busy_ ? (u64{1} << 63) : 0u);
}

u32 IpuCore::read_ctrl(u64 now) {
    update(now);
    const unsigned fp = std::min(in_count_, kFpQw);
    return (in_count_ - fp) | (out_count_ << kCtrlOfcShift) | ((cbp_ & 0x3Fu) << kCtrlCbpShift) |
           (ecd_ ? kCtrlEcd : 0u) | (scd_ ? kCtrlScd : 0u) | mode_ | (busy_ ? kCtrlBusy : 0u);
}

u32 IpuCore::read_bp(u64 now) {
    update(now);
    const unsigned fp = std::min(in_count_, kFpQw);
    return (bp_ & kBpMask) | ((in_count_ - fp) << kBpIfcShift) | (fp << kBpFpShift);
}

// BSTOP is invalid while the decoder still consumes bits (a command whose data flow has not ended) or when fewer
// than 32 bits are buffered. Once a command's data flow is over its bit pointer is final, so TOP is valid even
// while BUSY waits out the command's cost (the game's `_slice0` reads TOP as soon as D3_QWC reaches 0 after BDEC).
u64 IpuCore::read_top(u64 now) {
    update(now);
    cur_ = bp_;
    const bool short_data = avail() < 32u;
    const bool decoding = busy_ && !work_done_;
    return u64{window()} | ((decoding || short_data) ? (u64{1} << 63) : 0u);
}

bool IpuCore::write_in_fifo(const u128& q, u64 now) {
    update(now);
    if (in_count_ >= kInCapacityQw) run(now);
    if (in_count_ >= kInCapacityQw) {
        trap(IpuTrap::Kind::InFifoOverflow, kInFifo, q.lo(),
             format("input FIFO write with %u qwords buffered (IFC %u + FP %u): dropped", in_count_, kInFifoQw, kFpQw));
        return false;
    }
    push_in(q);
    run(now);
    update(now);
    return true;
}

bool IpuCore::read_out_fifo(u128& q, u64 now) {
    update(now);
    if (out_count_ == 0) run(now);
    if (out_count_ == 0) {
        trap(IpuTrap::Kind::OutFifoUnderflow, kOutFifo, 0, "output FIFO read while empty: reads 0");
        q = u128{};
        return false;
    }
    std::memcpy(&q, out_[out_head_], 16);
    out_head_ = (out_head_ + 1u) & (kOutFifoQw - 1u);
    --out_count_;
    ++stats_.out_qwords;
    run(now);
    update(now);
    return true;
}

std::size_t IpuCore::push_input(const u128* q, std::size_t n, u64 now) {
    update(now);
    std::size_t k = 0;
    for (;;) {
        while (k < n && in_count_ < kInCapacityQw) push_in(q[k++]);
        const unsigned before = in_count_;
        run(now);
        if (k == n || in_count_ == before) break;  // all taken, or decoding freed no room
    }
    update(now);
    return k;
}

std::size_t IpuCore::pop_output(u128* q, std::size_t n, u64 now) {
    update(now);
    std::size_t k = 0;
    for (;;) {
        while (k < n && out_count_ > 0) {
            std::memcpy(q + k, out_[out_head_], 16);
            out_head_ = (out_head_ + 1u) & (kOutFifoQw - 1u);
            --out_count_;
            ++k;
            ++stats_.out_qwords;
        }
        if (k == n) break;
        run(now);
        if (out_count_ == 0) break;
    }
    run(now);  // the freed FIFO space lets a waiting command stage/finish
    update(now);
    return k;
}

// ---- engine -------------------------------------------------------------------------------------------------

void IpuCore::run(u64 now) {
    for (;;) {
        drain_stage();
        if (!busy_ || work_done_) return;
        if (finished_) {
            if (!stage_free()) return;
            work_done_ = true;
            complete_at_ = std::max(issue_at_ + costs_.cycles[code()], now);
            return;
        }
        cur_ = bp_;
        switch (step()) {
        case St::Progress: commit(); break;
        case St::Finished:
            commit();
            finished_ = true;
            break;
        case St::Error:
            // Invalid code: ECD, the command ends; the offending bits stay unconsumed; output of macroblocks that
            // were complete before the error is still delivered.
            ecd_ = true;
            ++stats_.errors;
            finished_ = true;
            phase_ = Phase::Idle;
            break;
        case St::NeedInput: ++stats_.input_stalls; return;
        case St::NeedOutput: ++stats_.output_stalls; return;
        }
    }
}

IpuCore::St IpuCore::step() {
    switch (phase_) {
    case Phase::SkipFb: {
        u32 v = 0;
        if (!take(cmd_fb(cmd_), v)) return St::NeedInput;
        phase_ = after_fb_;
        return St::Progress;
    }
    case Phase::Fdec:
        if (avail() < 32u) return St::NeedInput;  // FDEC returns a full 32-bit window (not consumed)
        data_ = window();
        return St::Finished;
    case Phase::Vdec: return step_vdec();
    case Phase::LoadBytes: return step_load();
    case Phase::Convert: return step_convert();
    case Phase::BdecCbp: {
        if (intra_) {
            cbp_mb_ = 0x3F;
        } else {
            unsigned len = 0;
            int v = 0;
            switch (decode_vlc(Vlc::Cbp, window(), std::min(avail(), 32u), len, v)) {
            case Decode::NeedBits: return St::NeedInput;
            case Decode::Invalid: return St::Error;
            case Decode::Ok: break;
            }
            cur_ += len;
            cbp_mb_ = static_cast<unsigned>(v);
        }
        blk_ = 0;
        phase_ = Phase::Block;
        return St::Progress;
    }
    case Phase::IdecHeader: return step_header();
    case Phase::Block: return step_block();
    case Phase::BlockDc: return step_dc();
    case Phase::BlockFirst: return step_first();
    case Phase::BlockAc: return step_ac();
    case Phase::MbOut: return step_mbout();
    case Phase::IdecNext: return step_idec_next();
    case Phase::IdecScan: return step_idec_scan();
    case Phase::Idle: break;
    }
    return St::Finished;
}

IpuCore::St IpuCore::step_vdec() {
    Vlc t = Vlc::MbAddrInc;
    switch ((cmd_ >> 26) & 3u) {
    case 0: t = mpeg1() ? Vlc::MbAddrIncMpeg1 : Vlc::MbAddrInc; break;
    case 1:
        switch ((lmode_ >> kCtrlPctShift) & 7u) {
        case 1: t = Vlc::MbTypeI; break;
        case 2: t = Vlc::MbTypeP; break;
        case 3: t = Vlc::MbTypeB; break;
        case 4: t = Vlc::MbTypeD; break;
        default: data_ = 0; return St::Error;  // no macroblock_type table for this picture coding type
        }
        break;
    case 2: t = Vlc::MotionCode; break;
    default: t = Vlc::DmVector; break;
    }
    unsigned len = 0;
    int v = 0;
    switch (decode_vlc(t, window(), std::min(avail(), 32u), len, v)) {
    case Decode::NeedBits: return St::NeedInput;
    case Decode::Invalid: data_ = 0; return St::Error;
    case Decode::Ok: break;
    }
    cur_ += len;
    data_ = (len << 16) | (static_cast<u32>(v) & 0xFFFFu);
    return St::Finished;
}

IpuCore::St IpuCore::step_load() {
    unsigned got = 0;
    if ((cur_ & 7u) == 0) {  // byte-aligned: copy whole bytes, a qword slot at a time
        const unsigned bytes = std::min(avail() / 8u, load_total_ - load_n_);
        unsigned b = cur_ >> 3, done = 0;
        while (done < bytes) {
            const unsigned off = b & 15u, n = std::min(16u - off, bytes - done);
            std::memcpy(load_ + load_n_ + done, in_[(in_head_ + (b >> 4)) & 15u] + off, n);
            done += n;
            b += n;
        }
        load_n_ += bytes;
        cur_ += bytes * 8u;
        got = bytes;
    } else {
        u32 v = 0;
        while (load_n_ < load_total_ && take(8, v)) {
            load_[load_n_++] = static_cast<u8>(v);
            ++got;
        }
    }
    if (load_n_ < load_total_) return got ? St::Progress : St::NeedInput;
    switch (static_cast<Cmd>(code())) {
    case Cmd::Setiq: {
        u8* m = cmd_bit(cmd_, 27) ? iq_nonintra_ : iq_intra_;
        for (unsigned k = 0; k < 64; ++k) m[kZigzag[k]] = load_[k];  // matrices arrive in zigzag scan order
        return St::Finished;
    }
    case Cmd::Setvq:
        for (unsigned i = 0; i < 16; ++i)  // 16-bit entries in memory (little-endian) order
            vqclut_[i] = static_cast<u16>(load_[2 * i] | (load_[2 * i + 1] << 8));
        return St::Finished;
    default:  // CSC / PACK: the macroblock's input is complete
        phase_ = Phase::Convert;
        return St::Progress;
    }
}

IpuCore::St IpuCore::step_convert() {
    if (!stage_free()) return St::NeedOutput;
    alignas(16) u8 out[kRgb32Bytes];
    const bool ofm = cmd_bit(cmd_, 27), dte = cmd_bit(cmd_, 26);
    if (static_cast<Cmd>(code()) == Cmd::Csc) {
        CscParams p;
        p.rgb16 = ofm;
        p.dither = dte;
        p.th0 = th0_;
        p.th1 = th1_;
        csc(load_, p, out);
        stage(out, ofm ? kRgb16Bytes / 16u : kRgb32Bytes / 16u);
    } else {
        pack(load_, ofm, dte, vqclut_, out);
        stage(out, ofm ? kRgb16Bytes / 16u : kIndx4Bytes / 16u);
    }
    ++stats_.macroblocks;
    if (--mb_left_ == 0) return St::Finished;
    load_n_ = 0;
    phase_ = Phase::LoadBytes;
    return St::Progress;
}

// IDEC macroblock header: macroblock_type (B.2), dct_type if DTD, quantiser_scale_code if macroblock_quant —
// decoded as one element (<= 8 bits).
IpuCore::St IpuCore::step_header() {
    const unsigned av = std::min(avail(), 32u);
    const u32 w = window();
    unsigned len = 0;
    int type = 0;
    switch (decode_vlc(Vlc::MbTypeI, w, av, len, type)) {
    case Decode::NeedBits: return St::NeedInput;
    case Decode::Invalid: return St::Error;
    case Decode::Ok: break;
    }
    const bool dtd = cmd_bit(cmd_, 24);
    const unsigned need = len + (dtd ? 1u : 0u) + ((type & kMbQuant) ? 5u : 0u);
    if (av < need) return St::NeedInput;
    unsigned pos = len;
    bool dt = false;
    unsigned q = qsc_;
    if (dtd) {
        dt = ((w >> (31u - pos)) & 1u) != 0;
        pos += 1;
    }
    if (type & kMbQuant) {
        q = (w >> (27u - pos)) & 31u;
        pos += 5;
    }
    cur_ += pos;
    field_dct_ = dt;
    qsc_ = q;
    cbp_mb_ = 0x3F;
    blk_ = 0;
    phase_ = Phase::Block;
    return St::Progress;
}

IpuCore::St IpuCore::step_block() {
    while (blk_ < 6 && !(cbp_mb_ & (32u >> blk_))) {
        std::fill(std::begin(blocks_[blk_]), std::end(blocks_[blk_]), s16{0});
        ++blk_;
    }
    if (blk_ == 6) {
        phase_ = Phase::MbOut;
        return St::Progress;
    }
    std::fill(std::begin(qf_), std::end(qf_), 0);
    k_ = 0;
    phase_ = intra_ ? Phase::BlockDc : Phase::BlockFirst;
    return St::Progress;
}

// Intra DC: dct_dc_size (B.12 / B.13) + dct_dc_differential, one element (<= 21 bits).
IpuCore::St IpuCore::step_dc() {
    const bool luma = blk_ < 4;
    const unsigned av = std::min(avail(), 32u);
    const u32 w = window();
    unsigned len = 0;
    int size = 0;
    switch (decode_vlc(luma ? Vlc::DcSizeLuma : Vlc::DcSizeChroma, w, av, len, size)) {
    case Decode::NeedBits: return St::NeedInput;
    case Decode::Invalid: return St::Error;
    case Decode::Ok: break;
    }
    const unsigned sz = static_cast<unsigned>(size);
    if (av < len + sz) return St::NeedInput;
    int diff = 0;
    if (sz) {
        const u32 bits = (w << len) >> (32u - sz);
        diff = bits < (1u << (sz - 1u)) ? static_cast<int>(bits) + 1 - (1 << sz) : static_cast<int>(bits);
    }
    cur_ += len + sz;
    const unsigned c = luma ? 0u : blk_ - 3u;
    dc_[c] += diff;
    qf_[0] = dc_[c];
    k_ = 1;
    phase_ = Phase::BlockAc;
    return St::Progress;
}

// First coefficient of a non-intra block: '1s' is run 0 / level +-1 (B.14 note), otherwise an ordinary code.
IpuCore::St IpuCore::step_first() {
    const unsigned av = std::min(avail(), 32u);
    if (av == 0) return St::NeedInput;
    const u32 w = window();
    if (w >> 31) {
        if (av < 2) return St::NeedInput;
        qf_[0] = ((w >> 30) & 1u) ? -1 : 1;
        cur_ += 2;
        k_ = 1;
        phase_ = Phase::BlockAc;
        return St::Progress;
    }
    return step_ac();
}

IpuCore::St IpuCore::step_ac() {
    const bool table_one = intra_ && !mpeg1() && (lmode_ & kCtrlIvf) != 0;
    const unsigned av = std::min(avail(), 32u);
    const u32 w = window();
    DctCode dc;
    switch (decode_dct(table_one, w, av, dc)) {
    case Decode::NeedBits: return St::NeedInput;
    case Decode::Invalid: return St::Error;
    case Decode::Ok: break;
    }
    if (dc.kind == DctCode::Eob) {
        cur_ += dc.length;
        end_block();
        return St::Progress;
    }
    int run = 0, level = 0;
    unsigned used = 0;
    if (dc.kind == DctCode::Coef) {
        if (av < dc.length + 1u) return St::NeedInput;
        run = dc.run;
        level = ((w >> (31u - dc.length)) & 1u) ? -static_cast<int>(dc.level) : static_cast<int>(dc.level);
        used = dc.length + 1u;
    } else {  // escape: 6-bit run, then a 12-bit signed level (MPEG-2) or 8/16-bit level (MPEG-1)
        unsigned pos = dc.length;
        if (av < pos + 6u) return St::NeedInput;
        run = static_cast<int>((w << pos) >> 26);
        pos += 6;
        if (mpeg1()) {
            if (av < pos + 8u) return St::NeedInput;
            const int v = static_cast<int>((w << pos) >> 24);
            pos += 8;
            if (v == 0 || v == 128) {
                if (av < pos + 8u) return St::NeedInput;
                const int v2 = static_cast<int>((w << pos) >> 24);
                pos += 8;
                level = v == 0 ? v2 : v2 - 256;
            } else {
                level = v > 128 ? v - 256 : v;
            }
        } else {
            if (av < pos + 12u) return St::NeedInput;
            const int v = static_cast<int>((w << pos) >> 20);
            pos += 12;
            level = (v & 0x800) ? v - 0x1000 : v;
        }
        used = pos;
    }
    if (k_ + static_cast<unsigned>(run) >= 64u) return St::Error;  // run past the block
    cur_ += used;
    k_ += static_cast<unsigned>(run);
    qf_[k_++] = level;
    phase_ = Phase::BlockAc;
    return St::Progress;
}

void IpuCore::end_block() {
    QuantParams p;
    p.intra = intra_;
    p.mpeg1 = mpeg1();
    p.dc_precision = (lmode_ >> kCtrlIdpShift) & 3u;
    p.quantiser_scale = quantiser_scale(qsc_, (lmode_ & kCtrlQst) != 0, mpeg1());
    p.matrix = intra_ ? iq_intra_ : iq_nonintra_;
    p.alternate_scan = !mpeg1() && (lmode_ & kCtrlAs) != 0;
    s32 f[64];
    inverse_quantize(qf_, p, f);
    idct(f, blocks_[blk_]);
    ++blk_;
    phase_ = Phase::Block;
}

IpuCore::St IpuCore::step_mbout() {
    if (!stage_free()) return St::NeedOutput;
    alignas(16) s16 raw[384];
    assemble_raw16(blocks_, field_dct_, raw);
    cbp_ = cbp_mb_;
    ++stats_.macroblocks;
    if (static_cast<Cmd>(code()) == Cmd::Bdec) {
        stage(reinterpret_cast<const u8*>(raw), kRaw16Bytes / 16u);  // the host is little-endian, like the EE
        return St::Finished;
    }
    // IDEC: the intra samples (0..255 after saturation) through CSC.
    alignas(16) u8 raw8[kRaw8Bytes];
    for (unsigned i = 0; i < kRaw8Bytes; ++i) raw8[i] = static_cast<u8>(clamp(raw[i], 0, 255));
    alignas(16) u8 out[kRgb32Bytes];
    CscParams p;
    p.rgb16 = cmd_bit(cmd_, 27);
    p.dither = cmd_bit(cmd_, 26);
    p.th0 = th0_;
    p.th1 = th1_;
    csc(raw8, p, out);
    stage(out, p.rgb16 ? kRgb16Bytes / 16u : kRgb32Bytes / 16u);
    phase_ = Phase::IdecNext;
    return St::Progress;
}

// After an IDEC macroblock: eight zero bits cannot begin a macroblock_address_increment, so they announce a start
// code (byte-align, then scan); otherwise decode the increment (stuffing / escape loop here) and the next MB.
IpuCore::St IpuCore::step_idec_next() {
    const unsigned av = std::min(avail(), 32u);
    if (av < 8u) return St::NeedInput;
    const u32 w = window();
    if ((w >> 24) == 0) {
        cur_ = (cur_ + 7u) & ~7u;
        phase_ = Phase::IdecScan;
        return St::Progress;
    }
    unsigned len = 0;
    int v = 0;
    switch (decode_vlc(mpeg1() ? Vlc::MbAddrIncMpeg1 : Vlc::MbAddrInc, w, av, len, v)) {
    case Decode::NeedBits: return St::NeedInput;
    case Decode::Invalid: return St::Error;
    case Decode::Ok: break;
    }
    cur_ += len;
    if (v != kMbaiStuffing && v != kMbaiEscape) phase_ = Phase::IdecHeader;
    return St::Progress;
}

IpuCore::St IpuCore::step_idec_scan() {
    if (std::min(avail(), 32u) < 24u) return St::NeedInput;
    const u32 w = window();
    if ((w >> 8) == 1u) {  // 0x000001: stop in front of the start code, SCD
        scd_ = true;
        return St::Finished;
    }
    if ((w >> 24) == 0) {  // zero stuffing byte
        cur_ += 8;
        return St::Progress;
    }
    return St::Error;
}

} // namespace p3fes::ipu
