// Modernize layer 4 (docs/MODERNIZE_PLAN.md Â§3 "4. Movies", ADR-0017; runtime/ipu/README.md "Native movies"): the
// MPEG-1 / MPEG-2 video decoder the native movie path calls directly. It does what the game's libmpeg does on the EE
// (headers, slices, macroblock headers, motion vectors, motion compensation, the reference / display order) and
// takes every bit-exact piece from the IPU's own core (runtime/ipu, p3fes/ipu/mpeg2.h): the Annex B tables, the
// coefficient decode, inverse quantisation, the IDCT, the RAW16 assembly and the colour-space conversion.
//
// The parsing runs over an Engine -- the macroblock layer the IPU implements in hardware:
//   * DirectEngine: a host bit reader plus the mpeg2:: functions, the native path's engine;
//   * IpuEngine: the emulated IPU (p3fes::ipu::IpuCore) driven by commands the way libmpeg drives it (FDEC / VDEC /
//     BDEC / SETIQ / CSC with the stream fed as qwords): the sweep's oracle for "the same frames as the IPU path".
// Scope (every .SFD of the disc, checked by p3fes_native_movies_check sweep): MPEG-1, and MPEG-2 4:2:0 frame
// pictures with frame_pred_frame_dct = 1 (progressive, as every MPEG-2 movie of the disc). Field pictures, field /
// dual-prime motion, field DCT, concealment vectors and D pictures report Status::Unsupported.
//
// Output (libmpeg's): the shown picture as macroblocks in column-major order (macroblock (c, r) at index c * mbh +
// r, the order the game uploads it in, 16-pixel-wide columns), each 1,024 bytes RGB32 (the IPU's CSC: TH0 = TH1 =
// 0, no dither) or 384 bytes RAW8 (Y 16 x 16, Cb 8 x 8, Cr 8 x 8).
#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

#include "p3fes/ee_types.h"
#include "p3fes/ipu/mpeg2.h"

namespace p3fes {
class StateIo;
}
namespace p3fes::ipu {
class IpuCore;
}

namespace p3fes::native::movies {

// One BDEC: the macroblock's blocks (with its coded_block_pattern unless intra) into RAW16.
struct BdecArgs {
    bool intra = false;
    bool dc_reset = false;  // reset the DC predictors first (slice start, after a non-intra or skipped macroblock)
    unsigned qsc = 1;       // quantiser_scale_code
};

// The picture's IPU mode (IPU_CTRL's IDP / AS / IVF / QST / MP1 / PCT).
struct PictureMode {
    bool mpeg1 = true;
    unsigned pct = 1;  // 1 I, 2 P, 3 B
    unsigned idp = 0;  // intra_dc_precision
    bool qst = false;  // q_scale_type
    bool ivf = false;  // intra_vlc_format
    bool alt = false;  // alternate_scan
};

class Engine {
public:
    virtual ~Engine() = default;
    virtual void set_mode(const PictureMode& m) = 0;
    virtual u32 peek(unsigned n) = 0;  // the next n (1..32) bits, MSB first, not consumed
    virtual void skip(unsigned n) = 0;
    u32 get(unsigned n) {
        const u32 v = peek(n);
        skip(n);
        return v;
    }
    // A VLC of table t (MbAddrInc*, MbType*, MotionCode, DmVector): its value; false on an invalid code.
    virtual bool vlc(ipu::mpeg2::Vlc t, int& value) = 0;
    // The macroblock's blocks into RAW16 (assemble_raw16, frame DCT); cbp = the coded blocks (0x3F when intra).
    virtual bool bdec(const BdecArgs& a, s16 raw16[384], unsigned& cbp) = 0;
    // A quantiser matrix: 64 bytes from the stream (zigzag order) when `raster` is null, else the given one.
    virtual void load_matrix(bool intra, const u8* raster) = 0;
    // The engine's matrices (raster order): read back after a load, and put back into a fresh engine (the native
    // path makes one per picture call; the IPU keeps its matrices across calls, as the hardware does).
    virtual void matrix(bool intra, u8 raster[64]) const = 0;
    virtual void set_matrices(const u8 intra[64], const u8 nonintra[64]) = 0;
    // `mbs` RAW8 macroblocks (384 bytes each) to RGB32 (1,024 bytes each).
    virtual void csc(const u8* raw8, unsigned mbs, u8* rgb32) = 0;
    // Bits consumed since the stream start; whether a read went past the data end.
    virtual u64 bitpos() const = 0;
    virtual bool overrun() const = 0;
    void align() {
        const unsigned r = static_cast<unsigned>(bitpos() & 7u);
        if (r) skip(8 - r);
    }
};

// The native engine: a host bit reader over [data, data + size) from bit `bit0` of data[0]; reads past the end see
// zero bits (and set overrun()).
class DirectEngine final : public Engine {
public:
    DirectEngine(const u8* data, std::size_t size, unsigned bit0 = 0);
    void set_mode(const PictureMode& m) override { mode_ = m; }
    u32 peek(unsigned n) override;
    void skip(unsigned n) override;
    bool vlc(ipu::mpeg2::Vlc t, int& value) override;
    bool bdec(const BdecArgs& a, s16 raw16[384], unsigned& cbp) override;
    void load_matrix(bool intra, const u8* raster) override;
    void matrix(bool intra, u8 raster[64]) const override;
    void set_matrices(const u8 intra[64], const u8 nonintra[64]) override;
    void csc(const u8* raw8, unsigned mbs, u8* rgb32) override;
    u64 bitpos() const override { return pos_; }
    bool overrun() const override { return overrun_; }

private:
    u32 window() const;  // 32 bits at pos_
    bool block(unsigned b, bool intra, s16 out[64]);
    const u8* data_;
    std::size_t size_;
    u64 pos_ = 0, end_bits_ = 0;
    bool overrun_ = false;
    PictureMode mode_;
    int dc_[3] = {128, 128, 128};
    unsigned qsc_ = 1;
    u8 intra_q_[64], nonintra_q_[64];  // raster order
};

// The IPU oracle: an IpuCore driven by commands; the stream goes in as qwords from data[0] (bit0 = the first bit).
class IpuEngine final : public Engine {
public:
    IpuEngine(const u8* data, std::size_t size, unsigned bit0 = 0);
    ~IpuEngine() override;
    void set_mode(const PictureMode& m) override;
    u32 peek(unsigned n) override;
    void skip(unsigned n) override;
    bool vlc(ipu::mpeg2::Vlc t, int& value) override;
    bool bdec(const BdecArgs& a, s16 raw16[384], unsigned& cbp) override;
    void load_matrix(bool intra, const u8* raster) override;
    void matrix(bool intra, u8 raster[64]) const override;
    void set_matrices(const u8 intra[64], const u8 nonintra[64]) override;
    void csc(const u8* raw8, unsigned mbs, u8* rgb32) override;
    u64 bitpos() const override;
    bool overrun() const override { return overrun_; }

private:
    u32 run(u32 cmd, u8* out = nullptr, unsigned out_qw = 0, const u8* in = nullptr, unsigned in_qw = 0);
    void reposition(u64 bit);
    std::unique_ptr<ipu::IpuCore> core_;
    std::vector<u128> q_;      // the stream as qwords (zero padded)
    std::size_t fed_ = 0;      // qwords pushed
    std::size_t stream_qw_ = 0;
    unsigned fb_ = 0;          // bits to skip with the next command
    u32 ctrl_ = 0;
    u64 now_ = 0;
    bool overrun_ = false;
    bool feed_stream_ = true;  // the stream feeds the input FIFO (off while CSC / a matrix from memory runs)
};

enum class Status : u8 {
    Shown,        // a picture was written to the output
    End,          // the sequence end: nothing (more) to show
    NeedData,     // plan(): the input ends before the call's last picture does
    Error,        // a syntax error (an invalid code, an overrun)
    Unsupported,  // a feature outside the scope above
};
const char* to_string(Status s);

struct DecoderStats {
    u64 pictures[4] = {};  // decoded by type (index 1 I, 2 P, 3 B)
    u64 skipped = 0;       // pictures not decodable (missing references)
    u64 shown = 0;
    u64 macroblocks = 0, skipped_mbs = 0;
    // macroblocks by kind (the guest-time model's terms, native_movies.cpp) and coded blocks
    u64 mb_intra = 0, mb_fwd = 0, mb_bwd = 0, mb_bi = 0, mb_nomc = 0, blocks = 0;
};

// What one decode call (libmpeg's sceMpegGetPicture / _getpic) will consume: the byte offset after the start code
// that ends its last picture (its first byte + 4, the 32 bits libmpeg peeks), and how it ends.
struct Plan {
    Status status = Status::NeedData;  // Shown / End / NeedData
    std::size_t needed = 0;            // bytes of the input the call reads (NeedData: at least this many)
};

class MpegDecoder {
public:
    MpegDecoder();
    // The decoder at a new stream (sceMpegCreate / sceMpegReset): no sequence, no references.
    void reset();
    // Decodes pictures from the engine's position until one is shown (written to `out` in the format above, RGB32
    // when `rgb32`, else RAW8) or the sequence ends. The engine's position is then libmpeg's: after the last
    // macroblock of the picture that made the show (or after the sequence end code).
    Status decode(Engine& e, bool rgb32, u8* out, std::size_t out_size);
    // Without decoding, which input the next decode() needs (start codes only; the reference state is read).
    Plan plan(const u8* data, std::size_t size, unsigned bit0) const;

    unsigned width() const { return width_; }
    unsigned height() const { return height_; }
    unsigned mb_width() const { return mbw_; }
    unsigned mb_height() const { return mbh_; }
    bool has_sequence() const { return have_seq_; }
    bool ended() const { return ended_; }
    u32 frames_decoded() const { return decoded_; }
    u32 frames_shown() const { return shown_; }
    u32 last_shown_type() const { return last_type_; }
    u32 last_shown_tref() const { return last_tref_; }
    std::size_t frame_bytes(bool rgb32) const { return std::size_t{mbw_} * mbh_ * (rgb32 ? 1024u : 384u); }
    const DecoderStats& stats() const { return st_; }
    void state(StateIo& io);
    // Diagnostics (the check tool's `frames --trace`): every macroblock as decoded -- position, macroblock_type
    // flags (0x100 = skipped), the half-pel vectors [forward / backward][x / y].
    std::function<void(unsigned mbx, unsigned mby, unsigned flags, const int (&mv)[2][2])> trace;

private:
    struct Frame {
        std::vector<u8> y, cb, cr;
        u32 type = 0, tref = 0;
    };
    Status sequence_header(Engine& e);
    Status picture(Engine& e, Frame& dst, int& ptype, bool decode_it);
    Status slice(Engine& e, Frame& dst, unsigned row);
    void predict(const Frame& ref, int mx, int my, unsigned mbx, unsigned mby, bool average, u8* py, u8* pcb, u8* pcr) const;
    void store_mb(Frame& dst, unsigned mbx, unsigned mby, const u8* py, const u8* pcb, const u8* pcr,
                  const s16* raw16, unsigned cbp, bool intra) const;
    void output(Engine& e, const Frame& f, bool rgb32, u8* out) const;
    void alloc(Frame& f) const;

    // sequence
    bool have_seq_ = false, mpeg2_ = false, ended_ = false;
    unsigned width_ = 0, height_ = 0, mbw_ = 0, mbh_ = 0;
    // picture
    PictureMode mode_;
    unsigned fcode_[2][2] = {{1, 1}, {1, 1}};  // [forward / backward][horizontal / vertical]
    bool full_pel_[2] = {false, false};
    unsigned pic_struct_ = 3;
    bool fpfd_ = true, cmv_ = false;
    u32 tref_ = 0;
    // macroblock state within a slice
    int pmv_[2][2] = {};  // the motion vector predictors [forward / backward][x / y], in the transmitted units
    int mv_[2][2] = {};   // the last macroblock's vectors in half-pel units (B skipped macroblocks reuse them)
    unsigned last_dir_ = 0;  // the last macroblock's prediction directions (kMbForward | kMbBackward)
    unsigned qsc_ = 1;
    // references: ref_[old_] / ref_[new_]; frames_[3] decodes B pictures
    Frame frames_[4];
    int old_ = -1, new_ = -1;
    bool held_ = false;  // ref_[new_] not yet shown
    u8 intra_q_[64] = {}, nonintra_q_[64] = {};  // the sequence's matrices (raster), as loaded
    u32 decoded_ = 0, shown_ = 0, last_type_ = 0, last_tref_ = 0;
    DecoderStats st_;
};

// FNV-1a 64 over a byte range (the movie log's and the sweep's picture hash).
u64 fnv1a64(const u8* p, std::size_t n, u64 h = 0xCBF29CE484222325ull);

// The video and audio elementary streams of a Sofdec .SFD (an MPEG-1 system stream: pack headers, PES 0xE0 video,
// 0xC0 ADX audio, 0xBB / 0xBE / 0xBF system / padding / private).
struct SfdStreams {
    std::vector<u8> video, audio;
    u64 packs = 0, pes = 0;
};
bool demux_sfd(const u8* data, std::size_t size, SfdStreams& out);

}  // namespace p3fes::native::movies
