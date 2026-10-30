// CSC (YCbCr 4:2:0 -> RGB32/RGB16) and PACK (RGB32 -> RGB16/INDX4) on known values, hand-computed from the
// fixed-point formula documented in mpeg2.h (R = (149 (Y-16) + 204 (Cr-128) + 64) >> 7, ...).
#include "ipu_test_util.h"

using namespace it;
using namespace p3fes::ipu::mpeg2;

TEST_CASE("ycbcr_to_rgb: black, white, red and the DC-only macroblock's colours (hand-computed)") {
    int r = 0, g = 0, b = 0;
    ycbcr_to_rgb(16, 128, 128, r, g, b);
    CHECK((r == 0 && g == 0 && b == 0));
    // Y 235: 149 * 219 = 32631; (32631 + 64) >> 7 = 255
    ycbcr_to_rgb(235, 128, 128, r, g, b);
    CHECK((r == 255 && g == 255 && b == 255));
    // BT.601 red (81, 90, 240): lum 9685, u -38, v 112: R (9685+22848+64)>>7 = 254, G (9685+1900-11648+64)>>7 = 0,
    // B (9685-9804+64) = -55 >> 7 = -1 -> 0
    ycbcr_to_rgb(81, 90, 240, r, g, b);
    CHECK((r == 254 && g == 0 && b == 0));
    // Y 130, Cb 118, Cr 148: lum 16986: R 21130>>7 = 165, G 15470>>7 = 120, B 14470>>7 = 113
    ycbcr_to_rgb(130, 118, 148, r, g, b);
    CHECK((r == 165 && g == 120 && b == 113));
    ycbcr_to_rgb(129, 118, 148, r, g, b);  // lum 16837: 20981>>7 = 163, 15321>>7 = 119, 14321>>7 = 111
    CHECK((r == 163 && g == 119 && b == 111));
    ycbcr_to_rgb(134, 118, 148, r, g, b);  // lum 17582: 21726>>7 = 169, 16066>>7 = 125, 15066>>7 = 117
    CHECK((r == 169 && g == 125 && b == 117));
    ycbcr_to_rgb(0, 128, 128, r, g, b);  // Y below 16 clamps to 16
    CHECK((r == 0 && g == 0 && b == 0));
    // saturation: lum 149 * 239 = 35611, u = v = 127: R (35611 + 25908 + 64) >> 7 = 481 -> 255,
    // G (35611 - 6350 - 13208 + 64) >> 7 = 16117 >> 7 = 125, B (35611 + 32766 + 64) >> 7 = 534 -> 255
    ycbcr_to_rgb(255, 255, 255, r, g, b);
    CHECK((r == 255 && g == 125 && b == 255));
}

TEST_CASE("threshold alpha (SETTH): 0 below TH0, 0x40 below TH1, else 0x80") {
    CHECK(threshold_alpha(0, 0, 0, 0, 0) == 0x80);  // the game's SETTH(0, 0): always opaque
    CHECK(threshold_alpha(0x1F, 0x1F, 0x1F, 0x20, 0x80) == 0x00);
    CHECK(threshold_alpha(0x20, 0x1F, 0x1F, 0x20, 0x80) == 0x40);  // one channel at TH0: not transparent
    CHECK(threshold_alpha(0x7F, 0x7F, 0x7F, 0x20, 0x80) == 0x40);
    CHECK(threshold_alpha(0x80, 0x00, 0x00, 0x20, 0x80) == 0x80);
    CHECK(threshold_alpha(255, 255, 255, 0x1FF, 0x1FF) == 0x00);  // 9-bit thresholds above 255
}

TEST_CASE("CSC: RGB32 raster output with 4:2:0 chroma replication, RGB16 packing and alpha bit, dither") {
    u8 raw[384];
    for (int i = 0; i < 256; ++i) raw[i] = static_cast<u8>(16 + i % 220);  // Y ramp
    for (int i = 0; i < 64; ++i) {
        raw[256 + i] = static_cast<u8>(64 + i);   // Cb per 2x2 block
        raw[320 + i] = static_cast<u8>(200 - i);  // Cr
    }
    u8 out[1024];
    CscParams p;
    csc(raw, p, out);
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) {
            int r = 0, g = 0, b = 0;
            const unsigned c = (y / 2) * 8 + x / 2;  // pixels (2i, 2j), (2i+1, 2j), (2i, 2j+1), (2i+1, 2j+1) share
            ycbcr_to_rgb(raw[y * 16 + x], raw[256 + c], raw[320 + c], r, g, b);
            const u8* px = out + 4 * (y * 16 + x);
            CHECK(px[0] == r);
            CHECK(px[1] == g);
            CHECK(px[2] == b);
            CHECK(px[3] == 0x80);
        }
    // pixel (1,1) and (0,0) share chroma sample 0; (2,0) uses sample 1: check by hand for Y = 16 + 17 = 33 at (1,1):
    // lum 149*17 = 2533, u = 64-128 = -64, v = 200-128 = 72: R (2533 + 14688 + 64) >> 7 = 135, G (2533 + 3200 - 7488
    // + 64) = -1691 >> 7 -> 0, B (2533 - 16512 + 64) < 0 -> 0
    CHECK(out[4 * 17 + 0] == 135);
    CHECK(out[4 * 17 + 1] == 0);
    CHECK(out[4 * 17 + 2] == 0);
    // RGB16: A1 B5 G5 R5 of the same values, alpha bit from 0x80
    p.rgb16 = true;
    u8 o16[512];
    csc(raw, p, o16);
    for (unsigned i = 0; i < 256; ++i) {
        const u16 v = static_cast<u16>(o16[2 * i] | (o16[2 * i + 1] << 8));
        const u8* px = out + 4 * i;
        CHECK(v == static_cast<u16>((px[0] >> 3) | ((px[1] >> 3) << 5) | ((px[2] >> 3) << 10) | 0x8000));
    }
    // thresholds: a black macroblock (Y 16, Cb Cr 128) with TH0 1 is transparent: RGB32 A 0, RGB16 A bit 0
    u8 black[384];
    std::fill(black, black + 256, u8{16});
    std::fill(black + 256, black + 384, u8{128});
    CscParams pt;
    pt.th0 = 1;
    pt.th1 = 1;
    csc(black, pt, out);
    CHECK(out[3] == 0);
    pt.rgb16 = true;
    csc(black, pt, o16);
    CHECK(o16[1] == 0);
    // dither (DTE) on RGB16: grey 100 + offset at (x & 3, y & 3), then >> 3: (100 - 4) >> 3 = 12, (100 + 3) >> 3 = 12,
    // (100 + 2) >> 3 = 12 ... use 101 so the offsets straddle a step: 97 >> 3 = 12, 104 >> 3 = 13
    CHECK(rgb16_of(101, 101, 101, 0x80, true, 0, 0) == static_cast<u16>(12 | 12 << 5 | 12 << 10 | 0x8000));  // -4
    CHECK(rgb16_of(101, 101, 101, 0x80, true, 3, 0) == static_cast<u16>(13 | 13 << 5 | 13 << 10 | 0x8000));  // +3
    CHECK(rgb16_of(101, 101, 101, 0x80, false, 0, 0) == static_cast<u16>(12 | 12 << 5 | 12 << 10 | 0x8000));
    CHECK(rgb16_of(255, 255, 255, 0x40, true, 3, 0) == static_cast<u16>(0x7FFF));  // clamp; 0x40 has no bit 7
}

TEST_CASE("PACK: RGB32 -> RGB16 and RGB32 -> INDX4 against a VQ CLUT (nearest, lowest index on ties)") {
    u8 in[1024];
    for (unsigned i = 0; i < 256; ++i) {
        in[4 * i + 0] = static_cast<u8>(i);
        in[4 * i + 1] = static_cast<u8>(255 - i);
        in[4 * i + 2] = static_cast<u8>(i * 7);
        in[4 * i + 3] = static_cast<u8>(i & 1 ? 0x80 : 0x00);
    }
    // the hand case: (255, 128, 8, 0x80) -> 31 | 16 << 5 | 1 << 10 | 0x8000 = 0x861F
    in[0] = 255;
    in[1] = 128;
    in[2] = 8;
    in[3] = 0x80;
    u16 clut[16] = {};
    u8 out[512];
    pack(in, true, false, clut, out);
    CHECK((out[0] | (out[1] << 8)) == 0x861F);
    for (unsigned i = 1; i < 256; ++i) {
        const u16 v = static_cast<u16>(out[2 * i] | (out[2 * i + 1] << 8));
        CHECK(v == static_cast<u16>((in[4 * i] >> 3) | ((in[4 * i + 1] >> 3) << 5) | ((in[4 * i + 2] >> 3) << 10) |
                                    ((in[4 * i + 3] & 0x80) ? 0x8000 : 0)));
    }
    // INDX4: a CLUT with black, red, green, blue, white (A1B5G5R5) and grey; duplicates of black after
    const u16 vq[16] = {0x0000, 0x001F, 0x03E0, 0x7C00, 0x7FFF, 0x4210, 0x0000, 0x0000,
                        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};
    u8 px[1024] = {};
    const u8 colours[6][3] = {{0, 0, 0}, {250, 0, 0}, {0, 250, 0}, {0, 0, 250}, {250, 250, 250}, {130, 130, 130}};
    for (unsigned i = 0; i < 256; ++i)
        for (int ch = 0; ch < 3; ++ch) px[4 * i + static_cast<unsigned>(ch)] = colours[i % 6][ch];
    u8 idx[128];
    pack(px, false, false, vq, idx);
    for (unsigned i = 0; i < 256; ++i) {
        const unsigned v = (idx[i >> 1] >> ((i & 1) * 4)) & 0xF;
        INFO("pixel " << i);
        CHECK(v == i % 6);  // nearest entry; black matches entry 0 before its duplicates
    }
}
