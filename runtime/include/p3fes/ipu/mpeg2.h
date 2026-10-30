// The MPEG-1/MPEG-2 video pieces the IPU implements, as pure functions (no IPU state): Annex B variable-length
// codes, scan orders, inverse quantisation, the 8x8 IDCT, macroblock assembly, and the IPU's colour-space
// conversion (CSC) and packing (PACK) back ends. runtime/ipu/ipu_core.cpp drives them from the FIFO; the tests
// call them directly. Definitions: ISO/IEC 13818-2 (MPEG-2 video) §7.2-7.5 and Annex B, ISO/IEC 11172-2
// (MPEG-1) §2.4.4; IPU-specific conventions are tagged in runtime/ipu/README.md.
#pragma once

#include "p3fes/ee_types.h"

#include <vector>

namespace p3fes::ipu::mpeg2 {

// ---- variable-length codes -------------------------------------------------------------------------------

// The VDEC tables (IPU_CMD TBL field + IPU_CTRL.PCT/MP1 select one) and the BDEC/IDEC-internal ones.
enum class Vlc : u8 {
    MbAddrInc,       // B.1 without the MPEG-1 stuffing code (MPEG-2: '0000 0001 111' is not a code)
    MbAddrIncMpeg1,  // B.1 + macroblock_stuffing (MPEG-1, value 0x22)
    MbTypeI,         // B.2
    MbTypeP,         // B.3
    MbTypeB,         // B.4
    MbTypeD,         // MPEG-1 D-picture: '1' = intra (ISO 11172-2 Table B.2d)
    MotionCode,      // B.10, value -16..16
    DmVector,        // B.11, value -1..1
    DcSizeLuma,      // B.12
    DcSizeChroma,    // B.13
    Cbp,             // B.9 (4:2:0), value 0..63
    Count,
};

// Value conventions (the IPU's VDEC DATA[15:0]; see README "VDEC result"): macroblock_address_increment 1..33,
// escape 0x23, stuffing 0x22; macroblock_type flags quant 0x10 | forward 0x08 | backward 0x04 | pattern 0x02 |
// intra 0x01; motion_code and dmvector signed.
inline constexpr int kMbaiStuffing = 0x22;
inline constexpr int kMbaiEscape = 0x23;
inline constexpr int kMbQuant = 0x10, kMbForward = 0x08, kMbBackward = 0x04, kMbPattern = 0x02, kMbIntra = 0x01;

enum class Decode : u8 {
    Ok,        // a complete code lies inside the available bits
    NeedBits,  // the available bits are a proper prefix of (possibly) a code: wait for more data
    Invalid,   // no code of the table starts with these bits
};

// Longest code of a table (bits).
unsigned vlc_max_length(Vlc t);

// `window`: the next bits of the stream, MSB-aligned, bits beyond `avail` (<= 32) zero. On Ok sets the code
// length and the decoded value.
Decode decode_vlc(Vlc t, u32 window, unsigned avail, unsigned& length, int& value);

// One DCT coefficient code of B.14 (table zero) or B.15 (table one). `length` excludes the sign bit (a Coef code
// is followed by one sign bit) and the escape payload (an Escape is followed by run 6 + level 12 bits in MPEG-2,
// run 6 + level 8 or 16 bits in MPEG-1). The first coefficient of a non-intra block ('1s' = run 0, level 1) is
// handled by the caller.
struct DctCode {
    enum Kind : u8 { Coef, Eob, Escape } kind = Coef;
    u8 length = 0;
    u8 run = 0;
    u8 level = 0;  // magnitude
};
Decode decode_dct(bool table_one, u32 window, unsigned avail, DctCode& out);

// The code rows behind the decoders (tests: prefix-freeness, Kraft sums, hand vectors). `vdec_length` is the
// length the VDEC DATA word carries in bits 31:16.
struct VlcCodeInfo {
    u16 code;
    u8 length;
    int value;
    u32 vdec_length;
};
std::vector<VlcCodeInfo> vlc_codes(Vlc t);
struct DctCodeInfo {
    u16 code;
    u8 length;
    DctCode::Kind kind;
    u8 run;
    u8 level;
};
std::vector<DctCodeInfo> dct_codes(bool table_one);

// ---- scans and quantisation ---------------------------------------------------------------------------------

// scan position -> raster index (v * 8 + u). §7.3, Figure 7-2 (zigzag) and Figure 7-3 (alternate).
extern const u8 kZigzag[64];
extern const u8 kAlternate[64];
// The default intra matrix (§6.3.11) in raster order; the default non-intra matrix is all 16.
extern const u8 kDefaultIntraMatrix[64];
// Table 7-6, quantiser_scale for q_scale_type = 1, indexed by quantiser_scale_code.
extern const u8 kNonLinearScale[32];

// quantiser_scale from quantiser_scale_code: MPEG-1 the code itself, MPEG-2 linear 2 * code, non-linear Table 7-6.
// Returned in MPEG-2 units (the factor in (2 QF + k) W qs / 32): MPEG-1 yields 2 * code so that one formula serves
// both (ISO 11172-2's (2 QF qs W) / 16 equals (2 QF W (2 qs)) / 32 exactly in truncating integer division).
int quantiser_scale(unsigned code, bool q_scale_type, bool mpeg1);

struct QuantParams {
    bool intra = true;
    bool mpeg1 = false;
    unsigned dc_precision = 0;     // intra_dc_precision 0..3 (MPEG-2); ignored for MPEG-1 (DC multiplier 8)
    int quantiser_scale = 2;       // from quantiser_scale()
    const u8* matrix = nullptr;    // 64 weights, raster order
    bool alternate_scan = false;
};

// §7.4.2-7.4.4 (MPEG-2) / ISO 11172-2 §2.4.4.1-2 (MPEG-1). `qf` holds the quantised levels in scan order
// (qf[0] = the reconstructed DC value dct_dc_pred for intra blocks); `out` receives F[v][u] in raster order,
// saturated to [-2048, 2047], with MPEG-2 mismatch control or MPEG-1 oddification applied.
void inverse_quantize(const s32 qf[64], const QuantParams& p, s32 out[64]);

// ---- IDCT --------------------------------------------------------------------------------------------------

// The 8x8 inverse DCT of §A (IEEE 1180 reference form): f[y][x] = sum_v sum_u C(u)C(v)/4 F[v][u]
// cos((2x+1)u pi/16) cos((2y+1)v pi/16), evaluated in double precision as a direct 2-D sum over the non-zero
// coefficients in raster order, with fixed basis constants (cos(k pi/16) literals; the four basis functions with
// u, v in {0, 4} pinned to their exact value +-1/8, so DC-only blocks are exact); result rounded half up
// (floor(s + 0.5)) and saturated to [-256, 255]. No FMA contraction: deterministic across compilers.
void idct(const s32 in[64], s16 out[64]);

// ---- macroblock assembly -------------------------------------------------------------------------------------

// The IPU's RAW16 macroblock (BDEC output): Y[16][16], Cb[8][8], Cr[8][8] as s16, 768 bytes. Luma blocks 0-3 are
// top-left, top-right, bottom-left, bottom-right; with field DCT (dct_type 1) block rows interleave (blocks 0/1
// take the even lines, 2/3 the odd lines).
inline constexpr unsigned kRaw16Bytes = 768;
inline constexpr unsigned kRaw8Bytes = 384;   // RAW8: Y[16][16], Cb[8][8], Cr[8][8] as u8 (CSC input)
inline constexpr unsigned kRgb32Bytes = 1024; // 16 x 16 x (R, G, B, A), raster order
inline constexpr unsigned kRgb16Bytes = 512;  // 16 x 16 x u16 A1B5G5R5, raster order
inline constexpr unsigned kIndx4Bytes = 128;  // 16 x 16 x 4-bit CLUT indices
void assemble_raw16(const s16 blocks[6][64], bool field_dct, s16 out[384]);

// ---- colour-space conversion and packing (IPU back end) --------------------------------------------------------

// YCbCr (studio swing, BT.601) to RGB in 7-bit fixed point: R = (149 (Y-16) + 204 (Cr-128) + 64) >> 7,
// G = (149 (Y-16) - 50 (Cb-128) - 104 (Cr-128) + 64) >> 7, B = (149 (Y-16) + 258 (Cb-128) + 64) >> 7, each
// clamped to 0..255; Y - 16 clamped at 0. (Coefficients = 128 x {1.164, 1.596, 0.391, 0.813, 2.018}, rounded.)
void ycbcr_to_rgb(int y, int cb, int cr, int& r, int& g, int& b);

// The alpha of a converted pixel from SETTH's thresholds: 0 when R, G and B are all < TH0; else 0x40 when all
// are < TH1; else 0x80.
u8 threshold_alpha(int r, int g, int b, unsigned th0, unsigned th1);

// The 4x4 ordered-dither offsets applied to 8-bit R/G/B before truncation to 5 bits (DTE = 1, RGB16 outputs),
// indexed [y & 3][x & 3].
extern const s8 kDither[4][4];

// RGB32 (A = threshold alpha) to RGB16 A1B5G5R5: A bit = alpha bit 7.
u16 rgb16_of(int r, int g, int b, u8 a, bool dither, unsigned x, unsigned y);

struct CscParams {
    bool rgb16 = false;  // OFM
    bool dither = false; // DTE (RGB16 only)
    unsigned th0 = 0, th1 = 0;
};
// One RAW8 macroblock to RGB32 (1024 bytes) or RGB16 (512 bytes); chroma 4:2:0 upsampled by replication (each
// Cb/Cr sample covers its 2 x 2 luma pixels).
void csc(const u8 raw8[384], const CscParams& p, u8* out);

// One RGB32 macroblock (1024 bytes, alpha byte kept) to RGB16 (512 bytes; A bit = alpha bit 7) or, with
// `rgb16 = false`, INDX4 (128 bytes: per pixel the index of the nearest VQ CLUT entry by squared distance of the
// 5-bit components, lowest index on a tie; even pixel in the low nibble).
void pack(const u8 rgb32[1024], bool rgb16, bool dither, const u16 vqclut[16], u8* out);

} // namespace p3fes::ipu::mpeg2
