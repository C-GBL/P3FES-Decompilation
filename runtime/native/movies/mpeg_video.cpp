// Modernize layer 4: the native MPEG video decoder (mpeg_video.h). Written from ISO/IEC 11172-2 / 13818-2 and the
// game's own libmpeg (game/src/cri/cri2_mpeg.cpp: _getpic, _getRef0's reference fetch, the _rix_* / _ri0_* kernels,
// _copyAddRefImage, _dispRefImage); the block layer is the IPU's (runtime/ipu/ipu_core.cpp BDEC, same mpeg2::
// functions). No GPL or SDK source.
#include "mpeg_video.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

#include "p3fes/ipu/ipu_core.h"
#include "p3fes/ipu/ipu_regs.h"
#include "p3fes/state_io.h"

namespace p3fes::native::movies {

namespace m2 = ::p3fes::ipu::mpeg2;
using m2::Vlc;

const char* to_string(Status s) {
    switch (s) {
    case Status::Shown: return "shown";
    case Status::End: return "end";
    case Status::NeedData: return "need-data";
    case Status::Error: return "error";
    case Status::Unsupported: return "unsupported";
    }
    return "?";
}

u64 fnv1a64(const u8* p, std::size_t n, u64 h) {
    for (std::size_t i = 0; i < n; ++i) h = (h ^ p[i]) * 0x100000001B3ull;
    return h;
}

namespace {
inline int clamp255(int v) { return v < 0 ? 0 : (v > 255 ? 255 : v); }
// MbAddrInc follows the picture's MPEG-1 bit (the IPU's VDEC TBL 0 does: MP1 adds macroblock_stuffing).
Vlc mbai_table(bool mpeg1) { return mpeg1 ? Vlc::MbAddrIncMpeg1 : Vlc::MbAddrInc; }
}  // namespace

// ---- DirectEngine ------------------------------------------------------------------------------------------------

DirectEngine::DirectEngine(const u8* data, std::size_t size, unsigned bit0)
    : data_(data), size_(size), pos_(bit0), end_bits_(u64{size} * 8u) {
    std::memcpy(intra_q_, m2::kDefaultIntraMatrix, 64);
    std::memset(nonintra_q_, 16, 64);
}

u32 DirectEngine::window() const {
    const u64 byte = pos_ >> 3;
    u64 v = 0;
    for (unsigned i = 0; i < 5; ++i) {
        v <<= 8;
        if (byte + i < size_) v |= data_[byte + i];
    }
    v <<= (pos_ & 7u);
    return static_cast<u32>(v >> 8);
}

u32 DirectEngine::peek(unsigned n) { return n == 0 ? 0u : window() >> (32u - n); }

void DirectEngine::skip(unsigned n) {
    pos_ += n;
    if (pos_ > end_bits_) overrun_ = true;
}

bool DirectEngine::vlc(Vlc t, int& value) {
    if (t == Vlc::MbAddrInc || t == Vlc::MbAddrIncMpeg1) t = mbai_table(mode_.mpeg1);
    unsigned len = 0;
    if (m2::decode_vlc(t, window(), 32, len, value) != m2::Decode::Ok) return false;
    skip(len);
    return true;
}

// One block exactly as the IPU's BDEC decodes it (ipu_core.cpp step_dc / step_first / step_ac / end_block).
bool DirectEngine::block(unsigned b, bool intra, s16 out[64]) {
    s32 qf[64] = {};
    unsigned k = 0;
    if (intra) {
        const bool luma = b < 4;
        const u32 w = window();
        unsigned len = 0;
        int size = 0;
        if (m2::decode_vlc(luma ? Vlc::DcSizeLuma : Vlc::DcSizeChroma, w, 32, len, size) != m2::Decode::Ok) return false;
        const unsigned sz = static_cast<unsigned>(size);
        int diff = 0;
        if (sz) {
            const u32 bits = (w << len) >> (32u - sz);
            diff = bits < (1u << (sz - 1u)) ? static_cast<int>(bits) + 1 - (1 << sz) : static_cast<int>(bits);
        }
        skip(len + sz);
        const unsigned c = luma ? 0u : b - 3u;
        dc_[c] += diff;
        qf[0] = dc_[c];
        k = 1;
    } else {
        const u32 w = window();
        if (w >> 31) {  // '1s': run 0, level +-1
            qf[0] = ((w >> 30) & 1u) ? -1 : 1;
            skip(2);
            k = 1;
        }
    }
    const bool table_one = intra && !mode_.mpeg1 && mode_.ivf;
    for (;;) {
        const u32 w = window();
        m2::DctCode dc;
        if (m2::decode_dct(table_one, w, 32, dc) != m2::Decode::Ok) return false;
        if (dc.kind == m2::DctCode::Eob) {
            skip(dc.length);
            break;
        }
        int run = 0, level = 0;
        unsigned used = 0;
        if (dc.kind == m2::DctCode::Coef) {
            run = dc.run;
            level = ((w >> (31u - dc.length)) & 1u) ? -static_cast<int>(dc.level) : static_cast<int>(dc.level);
            used = dc.length + 1u;
            skip(used);
        } else {  // escape: 6-bit run, 12-bit level (MPEG-2) or 8 / 16-bit level (MPEG-1)
            skip(dc.length);
            run = static_cast<int>(get(6));
            if (mode_.mpeg1) {
                const int v = static_cast<int>(get(8));
                if (v == 0 || v == 128) {
                    const int v2 = static_cast<int>(get(8));
                    level = v == 0 ? v2 : v2 - 256;
                } else {
                    level = v > 128 ? v - 256 : v;
                }
            } else {
                const int v = static_cast<int>(get(12));
                level = (v & 0x800) ? v - 0x1000 : v;
            }
        }
        if (k + static_cast<unsigned>(run) >= 64u) return false;
        k += static_cast<unsigned>(run);
        qf[k++] = level;
    }
    m2::QuantParams p;
    p.intra = intra;
    p.mpeg1 = mode_.mpeg1;
    p.dc_precision = mode_.idp;
    p.quantiser_scale = m2::quantiser_scale(qsc_, mode_.qst, mode_.mpeg1);
    p.matrix = intra ? intra_q_ : nonintra_q_;
    p.alternate_scan = !mode_.mpeg1 && mode_.alt;
    s32 f[64];
    m2::inverse_quantize(qf, p, f);
    m2::idct(f, out);
    return true;
}

bool DirectEngine::bdec(const BdecArgs& a, s16 raw16[384], unsigned& cbp) {
    if (a.dc_reset) dc_[0] = dc_[1] = dc_[2] = static_cast<int>(1u << (7u + mode_.idp));
    qsc_ = a.qsc;
    if (a.intra) {
        cbp = 0x3F;
    } else {
        unsigned len = 0;
        int v = 0;
        if (m2::decode_vlc(Vlc::Cbp, window(), 32, len, v) != m2::Decode::Ok) return false;
        skip(len);
        cbp = static_cast<unsigned>(v);
    }
    alignas(16) s16 blocks[6][64];
    for (unsigned b = 0; b < 6; ++b) {
        if (cbp & (32u >> b)) {
            if (!block(b, a.intra, blocks[b])) return false;
        } else {
            std::fill(std::begin(blocks[b]), std::end(blocks[b]), s16{0});
        }
    }
    m2::assemble_raw16(blocks, false, raw16);
    return true;
}

void DirectEngine::load_matrix(bool intra, const u8* raster) {
    u8* m = intra ? intra_q_ : nonintra_q_;
    if (raster) {
        std::memcpy(m, raster, 64);
        return;
    }
    for (unsigned k = 0; k < 64; ++k) m[m2::kZigzag[k]] = static_cast<u8>(get(8));
}

void DirectEngine::matrix(bool intra, u8 raster[64]) const { std::memcpy(raster, intra ? intra_q_ : nonintra_q_, 64); }

void DirectEngine::set_matrices(const u8 intra[64], const u8 nonintra[64]) {
    std::memcpy(intra_q_, intra, 64);
    std::memcpy(nonintra_q_, nonintra, 64);
}

void DirectEngine::csc(const u8* raw8, unsigned mbs, u8* rgb32) {
    m2::CscParams p;  // RGB32, no dither, TH0 = TH1 = 0 (sceIpuInit's SETTH)
    for (unsigned i = 0; i < mbs; ++i) m2::csc(raw8 + std::size_t{i} * 384u, p, rgb32 + std::size_t{i} * 1024u);
}

// ---- IpuEngine ---------------------------------------------------------------------------------------------------

IpuEngine::IpuEngine(const u8* data, std::size_t size, unsigned bit0) : core_(std::make_unique<ipu::IpuCore>()) {
    stream_qw_ = (size + 15u) / 16u;
    q_.assign(stream_qw_ + 4u, u128{});  // + zero padding for the last peeks
    if (size) std::memcpy(q_.data(), data, size);
    core_->set_trap_handler([this](const ipu::IpuTrap&) { overrun_ = true; });
    feed_stream_ = false;
    run(ipu::kCmdSetth);  // sceIpuInit: SETTH(0, 0)
    reposition(bit0);
}

IpuEngine::~IpuEngine() = default;

u64 IpuEngine::bitpos() const { return u64{fed_} * 128u - core_->buffered_bits() + fb_; }

void IpuEngine::set_mode(const PictureMode& m) {
    ctrl_ = (m.idp << ipu::kCtrlIdpShift) | (m.alt ? ipu::kCtrlAs : 0u) | (m.ivf ? ipu::kCtrlIvf : 0u) |
            (m.qst ? ipu::kCtrlQst : 0u) | (m.mpeg1 ? ipu::kCtrlMp1 : 0u) | (m.pct << ipu::kCtrlPctShift);
    core_->write_ctrl(ctrl_, now_);
}

// One command to completion: the stream (or `in`, for CSC / a matrix from memory) goes in as the core takes it, the
// output (`out_qw` qwords) comes out. Returns IPU_CMD's DATA.
u32 IpuEngine::run(u32 cmd, u8* out, unsigned out_qw, const u8* in, unsigned in_qw) {
    core_->write_cmd(cmd, now_);
    unsigned got = 0, put = 0;
    for (unsigned guard = 0; guard < 1u << 22; ++guard) {
        if (in) {
            while (put < in_qw && core_->in_qwords() < ipu::kInCapacityQw) {
                u128 q;
                std::memcpy(&q, in + std::size_t{put} * 16u, 16);
                if (core_->push_input(&q, 1, now_) != 1) break;
                ++put;
            }
        } else if (feed_stream_) {
            while (core_->in_qwords() < ipu::kInCapacityQw) {
                if (fed_ >= q_.size()) q_.push_back(u128{});  // past the padding: zeros
                if (core_->push_input(&q_[fed_], 1, now_) != 1) break;
                ++fed_;
            }
        }
        if (out_qw) got += static_cast<unsigned>(core_->pop_output(reinterpret_cast<u128*>(out) + got, out_qw - got, now_));
        now_ += 1u << 16;
        core_->update(now_);
        if (!core_->busy() && got == out_qw) break;
    }
    if (core_->read_ctrl(now_) & ipu::kCtrlEcd) overrun_ = true;  // reported as an error by the caller's check
    return static_cast<u32>(core_->read_cmd(now_));
}

// BCLR(BP) at the qword holding `bit`; the stream then feeds from that qword (sceIpuRestartDMA's rewind).
void IpuEngine::reposition(u64 bit) {
    fb_ = 0;
    fed_ = static_cast<std::size_t>(bit >> 7);
    feed_stream_ = true;
    run(static_cast<u32>(bit & 127u));
}

u32 IpuEngine::peek(unsigned n) {
    const u32 v = run(ipu::kCmdFdec | fb_);  // FDEC: skip the pending bits, the next 32 bits (not consumed)
    fb_ = 0;
    return n == 0 ? 0u : v >> (32u - n);
}

void IpuEngine::skip(unsigned n) {
    fb_ += n;
    while (fb_ > 32) {  // FB is 6 bits: apply long skips in steps
        run(ipu::kCmdFdec | 32u);
        fb_ -= 32;
    }
}

bool IpuEngine::vlc(Vlc t, int& value) {
    u32 cmd = ipu::kCmdVdecMbai;
    switch (t) {
    case Vlc::MbAddrInc:
    case Vlc::MbAddrIncMpeg1: cmd = ipu::kCmdVdecMbai; break;
    case Vlc::MbTypeI:
    case Vlc::MbTypeP:
    case Vlc::MbTypeB:
    case Vlc::MbTypeD: cmd = ipu::kCmdVdecMbType; break;
    case Vlc::MotionCode: cmd = ipu::kCmdVdecMotion; break;
    case Vlc::DmVector: cmd = ipu::kCmdVdecDmv; break;
    default: return false;
    }
    const bool before = overrun_;
    const u32 d = run(cmd | fb_);
    fb_ = 0;
    if (core_->read_ctrl(now_) & ipu::kCtrlEcd) return false;
    overrun_ = before;
    value = static_cast<s16>(d & 0xFFFFu);
    return true;
}

bool IpuEngine::bdec(const BdecArgs& a, s16 raw16[384], unsigned& cbp) {
    const u32 cmd = 0x20000000u | (a.intra ? 1u << 27 : 0u) | (a.dc_reset ? 1u << 26 : 0u) | ((a.qsc & 31u) << 16) | fb_;
    fb_ = 0;
    alignas(16) u8 buf[ipu::mpeg2::kRaw16Bytes];
    run(cmd, buf, ipu::mpeg2::kRaw16Bytes / 16u);
    if (core_->read_ctrl(now_) & ipu::kCtrlEcd) return false;
    cbp = (core_->read_ctrl(now_) >> ipu::kCtrlCbpShift) & 0x3Fu;
    std::memcpy(raw16, buf, sizeof buf);
    return true;
}

void IpuEngine::load_matrix(bool intra, const u8* raster) {
    const u32 cmd = intra ? ipu::kCmdSetiqIntra : ipu::kCmdSetiqNonIntra;
    if (!raster) {  // from the stream (_sequenceHeader's SETIQ at the matrix)
        run(cmd | fb_);
        fb_ = 0;
        return;
    }
    // from memory, as _sequenceHeader does for a default matrix: stop the stream, BCLR, 4 qwords, SETIQ, restart
    const u64 at = bitpos();
    alignas(16) u8 zz[64];
    for (unsigned k = 0; k < 64; ++k) zz[k] = raster[m2::kZigzag[k]];
    feed_stream_ = false;
    run(0);  // BCLR(0)
    run(cmd, nullptr, 0, zz, 4);
    reposition(at);
}

void IpuEngine::matrix(bool intra, u8 raster[64]) const {
    std::memcpy(raster, intra ? core_->intra_matrix() : core_->nonintra_matrix(), 64);
}

void IpuEngine::set_matrices(const u8 intra[64], const u8 nonintra[64]) {
    if (std::memcmp(core_->intra_matrix(), intra, 64) != 0) load_matrix(true, intra);
    if (std::memcmp(core_->nonintra_matrix(), nonintra, 64) != 0) load_matrix(false, nonintra);
}

void IpuEngine::csc(const u8* raw8, unsigned mbs, u8* rgb32) {
    // _sceMpegCscStoreRefImage / _doCSC2: stream DMA stopped, BCLR, CSC rounds of up to 1,023 macroblocks, restart
    const u64 at = bitpos();
    feed_stream_ = false;
    run(0);
    unsigned done = 0;
    while (done < mbs) {
        const unsigned n = std::min(mbs - done, 1023u);
        run(ipu::kCmdCsc | n, rgb32 + std::size_t{done} * 1024u, n * 64u, raw8 + std::size_t{done} * 384u, n * 24u);
        done += n;
    }
    reposition(at);
}

// ---- MpegDecoder -------------------------------------------------------------------------------------------------

MpegDecoder::MpegDecoder() { reset(); }

void MpegDecoder::reset() {
    have_seq_ = mpeg2_ = ended_ = false;
    width_ = height_ = mbw_ = mbh_ = 0;
    mode_ = PictureMode{};
    old_ = new_ = -1;
    held_ = false;
    decoded_ = shown_ = last_type_ = last_tref_ = 0;
    for (Frame& f : frames_) f = Frame{};
    st_ = DecoderStats{};
}

void MpegDecoder::alloc(Frame& f) const {
    const std::size_t luma = std::size_t{mbw_} * 16u * mbh_ * 16u;
    if (f.y.size() != luma) {
        f.y.assign(luma, 0);
        f.cb.assign(luma / 4u, 128);
        f.cr.assign(luma / 4u, 128);
    }
}

Status MpegDecoder::sequence_header(Engine& e) {
    width_ = e.get(12);
    height_ = e.get(12);
    e.skip(4 + 4);       // aspect_ratio_information, frame_rate_code
    e.skip(18 + 1 + 10);  // bit_rate_value, marker, vbv_buffer_size_value
    e.skip(1);            // constrained_parameters_flag
    if (e.get(1)) e.load_matrix(true, nullptr);
    else e.load_matrix(true, m2::kDefaultIntraMatrix);
    static const u8 kFlat[64] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                                 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                                 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
    if (e.get(1)) e.load_matrix(false, nullptr);
    else e.load_matrix(false, kFlat);
    e.matrix(true, intra_q_);
    e.matrix(false, nonintra_q_);
    const unsigned mbw = (width_ + 15u) / 16u, mbh = (height_ + 15u) / 16u;
    if (mbw == 0 || mbh == 0 || mbw > 64 || mbh > 64) return Status::Unsupported;
    if (mbw != mbw_ || mbh != mbh_) {
        mbw_ = mbw;
        mbh_ = mbh;
        old_ = new_ = -1;
        held_ = false;
        for (Frame& f : frames_) f = Frame{};
    }
    for (Frame& f : frames_) alloc(f);
    have_seq_ = true;
    return Status::Shown;  // (ok)
}

// Luma / chroma prediction of one macroblock from `ref` with the half-pel vector (mx, my) (_getRef0 + the _rix_* /
// _ri0_* kernels: (a + b + 1) >> 1, (a + b + c + d + 2) >> 2; averaged with the prediction already there as
// (p + q + 1) >> 1; the chroma vector is the luma vector / 2 truncated toward zero). One quirk is libmpeg's own and
// kept: the averaged luma kernel with both half-pel bits (_rix_111, the backward half of a bidirectional
// macroblock) reuses its rounding register for the averaging's 1 after the first row, so rows 1..15 compute
// (a + b + c + d + 1) >> 2 (row 0: + 2).
void MpegDecoder::predict(const Frame& ref, int mx, int my, unsigned mbx, unsigned mby, bool average, u8* py, u8* pcb,
                          u8* pcr) const {
    auto plane = [](const std::vector<u8>& src, int w, int h, int x0, int y0, int hx, int hy, int n, bool avg, u8* dst,
                    bool rix111) {
        auto at = [&](int x, int y) -> int {
            x = x < 0 ? 0 : (x >= w ? w - 1 : x);
            y = y < 0 ? 0 : (y >= h ? h - 1 : y);
            return src[static_cast<std::size_t>(y) * static_cast<std::size_t>(w) + static_cast<std::size_t>(x)];
        };
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < n; ++x) {
                const int sx = x0 + x, sy = y0 + y;
                int v;
                if (!hx && !hy) v = at(sx, sy);
                else if (hx && !hy) v = (at(sx, sy) + at(sx + 1, sy) + 1) >> 1;
                else if (!hx && hy) v = (at(sx, sy) + at(sx, sy + 1) + 1) >> 1;
                else v = (at(sx, sy) + at(sx + 1, sy) + at(sx, sy + 1) + at(sx + 1, sy + 1) + (rix111 && y > 0 ? 1 : 2)) >> 2;
                u8& d = dst[y * n + x];
                d = static_cast<u8>(avg ? (d + v + 1) >> 1 : v);
            }
    };
    const int W = static_cast<int>(mbw_ * 16u), H = static_cast<int>(mbh_ * 16u);
    plane(ref.y, W, H, static_cast<int>(mbx * 16u) + (mx >> 1), static_cast<int>(mby * 16u) + (my >> 1), mx & 1, my & 1,
          16, average, py, average);
    const int cmx = mx / 2, cmy = my / 2;
    plane(ref.cb, W / 2, H / 2, static_cast<int>(mbx * 8u) + (cmx >> 1), static_cast<int>(mby * 8u) + (cmy >> 1),
          cmx & 1, cmy & 1, 8, average, pcb, false);
    plane(ref.cr, W / 2, H / 2, static_cast<int>(mbx * 8u) + (cmx >> 1), static_cast<int>(mby * 8u) + (cmy >> 1),
          cmx & 1, cmy & 1, 8, average, pcr, false);
}

// The macroblock into the frame: intra samples clamped, else prediction + residual clamped (_copyAddRefImage).
void MpegDecoder::store_mb(Frame& dst, unsigned mbx, unsigned mby, const u8* py, const u8* pcb, const u8* pcr,
                           const s16* raw16, unsigned cbp, bool intra) const {
    const std::size_t W = std::size_t{mbw_} * 16u, CW = W / 2u;
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) {
            const int r = raw16 ? raw16[y * 16 + x] : 0;
            dst.y[(mby * 16u + y) * W + mbx * 16u + x] = static_cast<u8>(intra ? clamp255(r) : clamp255(py[y * 16 + x] + r));
        }
    for (unsigned y = 0; y < 8; ++y)
        for (unsigned x = 0; x < 8; ++x) {
            const int rb = raw16 ? raw16[256 + y * 8 + x] : 0, rr = raw16 ? raw16[320 + y * 8 + x] : 0;
            const std::size_t o = (mby * 8u + y) * CW + mbx * 8u + x;
            dst.cb[o] = static_cast<u8>(intra ? clamp255(rb) : clamp255(pcb[y * 8 + x] + rb));
            dst.cr[o] = static_cast<u8>(intra ? clamp255(rr) : clamp255(pcr[y * 8 + x] + rr));
        }
    (void)cbp;
}

Status MpegDecoder::slice(Engine& e, Frame& dst, unsigned row) {
    if (row >= mbh_) return Status::Error;
    qsc_ = e.get(5);
    if (mpeg2_ && e.peek(1)) e.skip(1 + 1 + 7);  // intra_slice_flag, intra_slice, reserved_bits
    while (e.get(1)) e.skip(8);                  // extra_bit_slice + extra_information_slice
    std::memset(pmv_, 0, sizeof pmv_);
    bool dc_reset = true, first = true;
    int addr = static_cast<int>(row * mbw_) - 1;
    const unsigned pct = mode_.pct;
    const Frame* fwd_ref = pct == 3 ? &frames_[old_] : (new_ >= 0 ? &frames_[new_] : nullptr);
    const Frame* bwd_ref = pct == 3 ? &frames_[new_] : nullptr;
    alignas(16) u8 py[256], pcb[64], pcr[64];
    alignas(16) s16 raw[384];
    for (;;) {
        // macroblock_address_increment (MPEG-2: libmpeg skips '0000 0001 111' stuffing before the VDEC)
        int inc = 0;
        for (;;) {
            if (mpeg2_ && e.peek(11) == 0x00Fu) {
                e.skip(11);
                continue;
            }
            int v = 0;
            if (!e.vlc(Vlc::MbAddrInc, v)) return Status::Error;
            if (v == m2::kMbaiStuffing) continue;
            if (v == m2::kMbaiEscape) {
                inc += 33;
                continue;
            }
            inc += v;
            break;
        }
        if (!first && inc > 1) {  // skipped macroblocks
            for (int k = 1; k < inc; ++k) {
                const int a = addr + k;
                if (a < 0 || a >= static_cast<int>(mbw_ * mbh_)) return Status::Error;
                const unsigned mbx = static_cast<unsigned>(a) % mbw_, mby = static_cast<unsigned>(a) / mbw_;
                if (pct == 1) return Status::Error;
                if (pct == 2) {
                    std::memset(pmv_, 0, sizeof pmv_);
                    std::memset(mv_, 0, sizeof mv_);
                    predict(*fwd_ref, 0, 0, mbx, mby, false, py, pcb, pcr);
                } else {
                    bool any = false;
                    if (last_dir_ & m2::kMbForward) {
                        predict(*fwd_ref, mv_[0][0], mv_[0][1], mbx, mby, false, py, pcb, pcr);
                        any = true;
                    }
                    if (last_dir_ & m2::kMbBackward) {
                        predict(*bwd_ref, mv_[1][0], mv_[1][1], mbx, mby, any, py, pcb, pcr);
                        any = true;
                    }
                    if (!any) return Status::Error;
                }
                store_mb(dst, mbx, mby, py, pcb, pcr, nullptr, 0, false);
                ++st_.skipped_mbs;
                if (trace) trace(mbx, mby, 0x100u | (pct == 2 ? m2::kMbForward : last_dir_), mv_);
            }
            dc_reset = true;
        }
        addr += inc;
        first = false;
        if (addr < 0 || addr >= static_cast<int>(mbw_ * mbh_)) return Status::Error;
        const unsigned mbx = static_cast<unsigned>(addr) % mbw_, mby = static_cast<unsigned>(addr) / mbw_;
        int type = 0;
        if (!e.vlc(pct == 1 ? Vlc::MbTypeI : pct == 2 ? Vlc::MbTypeP : Vlc::MbTypeB, type)) return Status::Error;
        if (type & m2::kMbQuant) qsc_ = e.get(5);
        const bool intra = (type & m2::kMbIntra) != 0;
        unsigned dir = static_cast<unsigned>(type) & (m2::kMbForward | m2::kMbBackward);
        if (intra) {
            std::memset(pmv_, 0, sizeof pmv_);
            dir = 0;
        }
        for (unsigned s = 0; s < 2; ++s) {
            if (!(dir & (s == 0 ? m2::kMbForward : m2::kMbBackward))) continue;
            for (unsigned t = 0; t < 2; ++t) {
                const unsigned r_size = fcode_[s][t] - 1u;
                int code = 0;
                if (!e.vlc(Vlc::MotionCode, code)) return Status::Error;
                int delta = 0;
                if (code != 0) {
                    const int residual = r_size ? static_cast<int>(e.get(r_size)) : 0;
                    delta = ((std::abs(code) - 1) << r_size) + residual + 1;
                    if (code < 0) delta = -delta;
                }
                const int f = 1 << r_size, high = 16 * f - 1, low = -16 * f, range = 32 * f;
                int pred = pmv_[s][t] + delta;
                if (pred > high) pred -= range;
                if (pred < low) pred += range;
                pmv_[s][t] = pred;
                mv_[s][t] = full_pel_[s] ? pred * 2 : pred;
            }
        }
        if (!intra && pct == 2 && !(dir & m2::kMbForward)) {  // P, no motion compensation: zero vector, reset
            std::memset(pmv_[0], 0, sizeof pmv_[0]);
            mv_[0][0] = mv_[0][1] = 0;
            dir = m2::kMbForward;
        }
        if (!intra) {
            bool any = false;
            if (dir & m2::kMbForward) {
                if (!fwd_ref) return Status::Error;
                predict(*fwd_ref, mv_[0][0], mv_[0][1], mbx, mby, false, py, pcb, pcr);
                any = true;
            }
            if (dir & m2::kMbBackward) {
                if (!bwd_ref) return Status::Error;
                predict(*bwd_ref, mv_[1][0], mv_[1][1], mbx, mby, any, py, pcb, pcr);
            }
            last_dir_ = dir;
        }
        const bool coded = intra || (type & m2::kMbPattern);
        unsigned cbp = 0;
        if (coded) {
            BdecArgs a;
            a.intra = intra;
            a.dc_reset = dc_reset;
            a.qsc = qsc_;
            if (!e.bdec(a, raw, cbp)) return Status::Error;
        }
        dc_reset = !intra;
        store_mb(dst, mbx, mby, py, pcb, pcr, coded ? raw : nullptr, cbp, intra);
        ++st_.macroblocks;
        if (intra) ++st_.mb_intra;
        else if (dir == (m2::kMbForward | m2::kMbBackward)) ++st_.mb_bi;
        else if (dir == m2::kMbBackward) ++st_.mb_bwd;
        else if (type & (m2::kMbForward | m2::kMbBackward)) ++st_.mb_fwd;
        else ++st_.mb_nomc;
        for (unsigned b = 0; b < 6; ++b) st_.blocks += (cbp >> b) & 1u;
        if (trace) trace(mbx, mby, static_cast<unsigned>(type) | (dir << 9), mv_);
        if (e.overrun()) return Status::Error;
        if (e.peek(23) == 0) break;  // a start code follows: the slice ends
    }
    return Status::Shown;  // (ok)
}

// The picture after its header's start code: the header, its extensions / user data, then every slice.
Status MpegDecoder::picture(Engine& e, Frame& dst, int& ptype, bool decode_it) {
    tref_ = e.get(10);
    ptype = static_cast<int>(e.get(3));
    e.skip(16);  // vbv_delay
    full_pel_[0] = full_pel_[1] = false;
    if (ptype == 2 || ptype == 3) {
        full_pel_[0] = e.get(1) != 0;
        fcode_[0][0] = fcode_[0][1] = e.get(3);
    }
    if (ptype == 3) {
        full_pel_[1] = e.get(1) != 0;
        fcode_[1][0] = fcode_[1][1] = e.get(3);
    }
    while (e.get(1)) e.skip(8);  // extra_bit_picture
    mode_ = PictureMode{};
    mode_.mpeg1 = !mpeg2_;
    mode_.pct = static_cast<unsigned>(ptype);
    pic_struct_ = 3;
    fpfd_ = true;
    cmv_ = false;
    for (;;) {  // extensions and user data, then the slices
        e.align();
        while (e.peek(24) != 1u) {
            e.skip(8);
            if (e.overrun()) return Status::Error;
        }
        const u32 code = e.peek(32) & 0xFFu;
        if (code == 0xB5) {
            e.skip(32);
            const u32 id = e.get(4);
            if (id == 8) {  // picture_coding_extension
                fcode_[0][0] = e.get(4);
                fcode_[0][1] = e.get(4);
                fcode_[1][0] = e.get(4);
                fcode_[1][1] = e.get(4);
                mode_.idp = e.get(2);
                pic_struct_ = e.get(2);
                e.skip(1);  // top_field_first
                fpfd_ = e.get(1) != 0;
                cmv_ = e.get(1) != 0;
                mode_.qst = e.get(1) != 0;
                mode_.ivf = e.get(1) != 0;
                mode_.alt = e.get(1) != 0;
                e.skip(1 + 1 + 1);  // repeat_first_field, chroma_420_type, progressive_frame
                if (e.get(1)) e.skip(20);  // composite_display
            }
            continue;
        }
        if (code == 0xB2) {
            e.skip(32);
            continue;
        }
        break;
    }
    if (mpeg2_ && (pic_struct_ != 3 || !fpfd_ || cmv_)) return Status::Unsupported;
    if (ptype < 1 || ptype > 3) return Status::Unsupported;
    if (decode_it) e.set_mode(mode_);
    for (;;) {
        e.align();
        for (; e.peek(24) != 1u;) {
            e.skip(8);
            if (e.overrun()) return Status::Error;
        }
        const u32 code = e.peek(32) & 0xFFu;
        if (code < 0x01 || code > 0xAF) break;
        e.skip(32);
        if (!decode_it) continue;  // skipped picture: scan over its slices
        const Status s = slice(e, dst, code - 1u);
        if (s != Status::Shown) return s;
    }
    return Status::Shown;  // (ok)
}

void MpegDecoder::output(Engine& e, const Frame& f, bool rgb32, u8* out) const {
    const std::size_t W = std::size_t{mbw_} * 16u, CW = W / 2u, n = std::size_t{mbw_} * mbh_;
    std::vector<u8> raw8(n * 384u);
    std::size_t i = 0;
    for (unsigned c = 0; c < mbw_; ++c)
        for (unsigned r = 0; r < mbh_; ++r, ++i) {  // column-major: (c, r) at c * mbh + r
            u8* m = raw8.data() + i * 384u;
            for (unsigned y = 0; y < 16; ++y) std::memcpy(m + y * 16u, f.y.data() + (r * 16u + y) * W + c * 16u, 16);
            for (unsigned y = 0; y < 8; ++y) {
                std::memcpy(m + 256 + y * 8u, f.cb.data() + (r * 8u + y) * CW + c * 8u, 8);
                std::memcpy(m + 320 + y * 8u, f.cr.data() + (r * 8u + y) * CW + c * 8u, 8);
            }
        }
    if (rgb32) e.csc(raw8.data(), static_cast<unsigned>(n), out);
    else std::memcpy(out, raw8.data(), raw8.size());
}

Status MpegDecoder::decode(Engine& e, bool rgb32, u8* out, std::size_t out_size) {
    if (ended_) return Status::End;
    if (have_seq_) e.set_matrices(intra_q_, nonintra_q_);
    auto show = [&](Frame& f) -> Status {
        if (out && out_size >= frame_bytes(rgb32)) output(e, f, rgb32, out);
        ++shown_;
        ++st_.shown;
        last_type_ = f.type;
        last_tref_ = f.tref;
        return Status::Shown;
    };
    for (;;) {
        e.align();
        while (e.peek(24) != 1u) {
            e.skip(8);
            if (e.overrun()) return Status::Error;
        }
        const u32 code = e.peek(32) & 0xFFu;
        e.skip(32);
        if (code == 0xB7) {  // sequence_end_code: the held reference is shown (_sceMpegFlush)
            ended_ = true;
            if (held_) {
                held_ = false;
                return show(frames_[new_]);
            }
            return Status::End;
        }
        if (code == 0xB3) {
            const Status s = sequence_header(e);
            if (s != Status::Shown) return s;
            continue;
        }
        if (code == 0xB5) {
            if (e.peek(4) == 1) mpeg2_ = true;  // sequence_extension
            continue;
        }
        if (code == 0xB8) {  // group_of_pictures_header (time code, closed_gop, broken_link: no broken links on the disc)
            e.skip(27);
            continue;
        }
        if (code != 0x00) continue;  // user data, stray slices
        if (!have_seq_) return Status::Error;
        // the picture's header type decides where it goes: peek it without consuming (temporal_reference 10 bits)
        const unsigned ptype = (e.peek(13) & 7u);
        const bool decodable = ptype == 1 || (ptype == 2 && new_ >= 0) || (ptype == 3 && old_ >= 0 && new_ >= 0);
        int idx = 3;
        if (ptype != 3) {
            for (idx = 0; idx < 3 && (idx == old_ || idx == new_); ++idx) {
            }
        }
        int pt = 0;
        const Status s = picture(e, frames_[idx], pt, decodable);
        if (s != Status::Shown) return s;
        if (!decodable) {
            ++st_.skipped;
            continue;
        }
        frames_[idx].type = static_cast<u32>(pt);
        frames_[idx].tref = tref_;
        ++decoded_;
        ++st_.pictures[pt & 3];
        if (pt == 3) return show(frames_[3]);
        const bool show_prev = held_;
        old_ = new_;
        new_ = idx;
        held_ = true;
        if (show_prev) return show(frames_[old_]);
    }
}

Plan MpegDecoder::plan(const u8* d, std::size_t n, unsigned bit0) const {
    Plan p;
    if (ended_) {
        p.status = Status::End;
        return p;
    }
    bool have_old = old_ >= 0, have_new = new_ >= 0, held = held_;
    std::size_t pos = bit0 ? 1u : 0u;
    auto next_sc = [&](std::size_t from, std::size_t& at) -> bool {
        for (std::size_t k = from; k + 4 <= n; ++k)
            if (d[k] == 0 && d[k + 1] == 0 && d[k + 2] == 1) {
                at = k;
                return true;
            }
        return false;
    };
    for (;;) {
        std::size_t k = 0;
        if (!next_sc(pos, k)) {
            p.status = Status::NeedData;
            p.needed = n + 1;
            return p;
        }
        const u8 code = d[k + 3];
        if (code == 0xB7) {
            p.status = held ? Status::Shown : Status::End;
            p.needed = k + 4;
            return p;
        }
        if (code != 0x00) {
            pos = k + 4;
            continue;
        }
        if (k + 6 > n) {
            p.status = Status::NeedData;
            p.needed = k + 6;
            return p;
        }
        const unsigned type = (d[k + 5] >> 3) & 7u;
        std::size_t j = k + 4, end = 0;
        for (;;) {
            std::size_t c = 0;
            if (!next_sc(j, c)) {
                p.status = Status::NeedData;
                p.needed = n + 1;
                return p;
            }
            const u8 cc = d[c + 3];
            if ((cc >= 0x01 && cc <= 0xAF) || cc == 0xB5 || cc == 0xB2) {
                j = c + 4;
                continue;
            }
            end = c;
            break;
        }
        const bool decodable = type == 1 || (type == 2 && have_new) || (type == 3 && have_old && have_new);
        pos = end;
        if (!decodable) continue;
        if (type == 3 || held) {
            p.status = Status::Shown;
            p.needed = end + 4;
            return p;
        }
        have_old = have_new;
        have_new = true;
        held = true;
    }
}

void MpegDecoder::state(StateIo& io) {
    io(have_seq_, mpeg2_, ended_, width_, height_, mbw_, mbh_, mode_, fcode_, full_pel_, pic_struct_, fpfd_, cmv_, tref_);
    io(pmv_, mv_, last_dir_, qsc_, old_, new_, held_, intra_q_, nonintra_q_, decoded_, shown_, last_type_, last_tref_, st_);
    for (Frame& f : frames_) io(f.y, f.cb, f.cr, f.type, f.tref);
}

// ---- the .SFD demultiplexer (MPEG-1 system stream) ----------------------------------------------------------------

bool demux_sfd(const u8* d, std::size_t n, SfdStreams& out) {
    std::size_t i = 0;
    while (i + 4 <= n) {
        if (!(d[i] == 0 && d[i + 1] == 0 && d[i + 2] == 1)) {
            ++i;
            continue;
        }
        const u8 c = d[i + 3];
        if (c == 0xBA) {  // pack header: MPEG-1 12 bytes, MPEG-2 14 + stuffing
            ++out.packs;
            if (i + 14 <= n && (d[i + 4] >> 6) == 1) i += 14 + (d[i + 13] & 7u);
            else i += 12;
            continue;
        }
        if (c == 0xB9) {
            i += 4;
            continue;
        }
        if (c < 0xBB) {
            ++i;
            continue;
        }
        if (i + 6 > n) break;
        const std::size_t len = (std::size_t{d[i + 4]} << 8) | d[i + 5];
        const std::size_t p = i + 6, end = std::min(n, p + len);
        if ((c >= 0xC0 && c <= 0xEF) && p < end) {
            ++out.pes;
            std::size_t q = p;
            if ((d[q] >> 6) == 2) {  // MPEG-2 PES header
                q = p + 3 + d[p + 2];
            } else {
                while (q < end && d[q] == 0xFF) ++q;  // stuffing
                if (q < end && (d[q] >> 6) == 1) q += 2;  // STD buffer
                if (q < end && (d[q] >> 4) == 2) q += 5;  // PTS
                else if (q < end && (d[q] >> 4) == 3) q += 10;  // PTS + DTS
                else ++q;  // 0x0F
            }
            if (q < end) {
                std::vector<u8>& dst = c == 0xE0 ? out.video : out.audio;
                if (c == 0xE0 || c == 0xC0) dst.insert(dst.end(), d + q, d + end);
            }
        }
        i = p + len;
    }
    return !out.video.empty();
}

}  // namespace p3fes::native::movies
