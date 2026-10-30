// CRI ADX decoder (runtime/audio/adx_decoder.cpp) against vectors computed independently of the code:
// an oracle written from the public format description plus the arithmetic read from the game's
// ADX_DecodeMono4 0x53A410 (Python, not in the repo), with the first samples of each vector also
// checked by hand in the comments. Synthetic frames only; no game data.
#include <doctest.h>

#include <array>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#include "p3fes/audio/adx_decoder.h"
#include "p3fes/audio/wav.h"

using namespace p3fes;
using namespace p3fes::audio;

namespace {

std::vector<std::byte> bytes(std::initializer_list<int> v) {
    std::vector<std::byte> b;
    for (int x : v) b.push_back(static_cast<std::byte>(x));
    return b;
}

// Frame A: scale word 0x0007 (effective 8), nibbles 7,-8, 1,-1, 0,0, 0,0, 3,4, 5,6, -7,-6, -5,-4, 0,0,
// 0,0, 7,-1, -8,1, 2,2, -2,-2, 0,0, 0,0.
const std::vector<std::byte> kFrameA = bytes({0x00, 0x07, 0x78, 0x1F, 0x00, 0x00, 0x34, 0x56, 0x9A, 0xBC, 0x00, 0x00,
                                              0x7F, 0x81, 0x22, 0xEE, 0x00, 0x00});
const std::vector<std::byte> kFrameB = bytes({0x01, 0x23, 0x11, 0xF0, 0x0F, 0x87, 0x65, 0x43, 0x21, 0x0C, 0xDE, 0xF0,
                                              0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC});
const std::vector<std::byte> kFrameS = bytes({0x1F, 0xFF, 0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x70, 0x70,
                                              0x70, 0x70, 0x70, 0x70, 0x70, 0x70});
const std::vector<std::byte> kEnd = bytes({0x80, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

// From zero history with the 48 kHz / 500 Hz coefficients (7400, -3342):
//   s0 = 0 + 7*8 = 56; s1 = (7400*56) >> 12 = 101, - 8*8 -> 37;
//   s2 = (7400*37 - 3342*56) >> 12 = 86648 >> 12 = 21, + 1*8 -> 29.
const std::array<s16, 32> kA48 = {56,   37,   29,   14,   1,    -10,  -19,  -27,  -10,  35,   111,
                                  219,  249,  223,  159,  73,   2,    -56,  -103, -141, -115, -101,
                                  -153, -187, -198, -190, -198, -219, -235, -246, -253, -257};
// Frame B continuing A's history (h1 = -257, h2 = -253); effective scale 0x124:
//   s0 = (7400*-257 - 3342*-253) >> 12 = (-1901800 + 845526) >> 12 = -258 (floor), + 1*292 -> 34.
const std::array<s16, 32> kB48 = {34,    563,   697,   799,   874,   635,   -1902, -1911, -149,  2750,  6257,
                                  9936,  13429, 16446, 18755, 19296, 18682, 17423, 15942, 14585, 13634, 13315,
                                  13807, 15248, 17742, 21364, 26165, 27503, 26295, 23313, 19203, 14503};
// Scale 0x1FFF (8192): 7*8192 saturates to 32767, -8*8192 to -32768.
const std::array<s16, 32> kS48 = {32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,  -32768, -32768, -32768,
                                  -32768, -32768, -32768, -32768, -32768, 24880,  32767,  32767,  32463,  32767,  32711,
                                  32767,  32508,  32767,  32674,  32767,  32538,  32767,  32649,  32767,  32559};
// Frame A with the 24 kHz coefficients (6687, -2729) from history (100, -50):
//   s0 = (6687*100 - 2729*-50) >> 12 = 805150 >> 12 = 196, + 56 -> 252.
const std::array<s16, 32> kA24 = {252, 280, 297, 290, 275, 255, 233, 210, 211, 236, 284, 354, 332, 258, 160, 57,
                                  -14, -61, -91, -108, -60, -34, -80, -100, -94, -71, -70, -83, -89, -90, -88, -84};

void put16be(std::vector<std::byte>& b, std::size_t o, u32 v) {
    b[o] = static_cast<std::byte>(v >> 8);
    b[o + 1] = static_cast<std::byte>(v);
}
void put32be(std::vector<std::byte>& b, std::size_t o, u32 v) {
    for (int i = 0; i < 4; ++i) b[o + i] = static_cast<std::byte>(v >> (24 - 8 * i));
}

// A synthetic ADX file: header (v3 without loop, or v4 with a loop block), `frames` frames per channel
// (frame f of channel c = frames[f][c]), then the 0x8001 end frame.
std::vector<std::byte> make_adx(u32 channels, u32 rate, u32 samples, const std::vector<std::vector<std::vector<std::byte>>>& frames,
                                bool loop = false, u32 loop_begin = 0, u32 loop_end = 0) {
    const u32 coff = loop ? 0x3C : 0x1C;  // data at coff + 4
    std::vector<std::byte> b(coff + 4, std::byte{0});
    put16be(b, 0, 0x8000);
    put16be(b, 2, coff);
    b[4] = std::byte{3};
    b[5] = std::byte{18};
    b[6] = std::byte{4};
    b[7] = static_cast<std::byte>(channels);
    put32be(b, 8, rate);
    put32be(b, 12, samples);
    put16be(b, 16, 500);
    b[18] = static_cast<std::byte>(loop ? 4 : 3);
    b[19] = std::byte{0};
    if (loop) {
        const std::size_t lo = 0x18 + 4 * channels;  // v4: after a pad word and per-channel history
        put32be(b, lo + 0, 1);
        put32be(b, lo + 4, 1);
        put32be(b, lo + 8, loop_begin);
        put32be(b, lo + 12, coff + 4 + (loop_begin / 32) * 18 * channels);
        put32be(b, lo + 16, loop_end);
        put32be(b, lo + 20, coff + 4 + (loop_end / 32) * 18 * channels);
    }
    std::memcpy(b.data() + coff - 2, "(c)CRI", 6);
    for (const auto& f : frames)
        for (u32 c = 0; c < channels; ++c) b.insert(b.end(), f[c].begin(), f[c].end());
    b.insert(b.end(), kEnd.begin(), kEnd.end());
    return b;
}

formats::Bytes view(const std::vector<std::byte>& v) { return formats::Bytes(v.data(), v.size()); }

}  // namespace

TEST_CASE("ADX coefficients for the 500 Hz cutoff (derived; truncation toward zero as cvt.w.s)") {
    CHECK(adx_coefficients(500, 48000).k0 == 7400);
    CHECK(adx_coefficients(500, 48000).k1 == -3342);
    CHECK(adx_coefficients(500, 24000).k0 == 6687);
    CHECK(adx_coefficients(500, 24000).k1 == -2729);
    CHECK(adx_coefficients(500, 44100).k0 == 7334);
    CHECK(adx_coefficients(500, 44100).k1 == -3283);
    CHECK(adx_coefficients(500, 22050).k0 == 6569);
    CHECK(adx_coefficients(500, 22050).k1 == -2634);
    CHECK(adx_coefficients(500, 32000).k0 == 7034);
    CHECK(adx_coefficients(500, 32000).k1 == -3020);
    CHECK(adx_coefficients(500, 0).k0 == 0);
}

TEST_CASE("ADX frame decode: hand-checked vectors, history carry, saturation, end marker") {
    const AdxCoefficients k48 = adx_coefficients(500, 48000);
    std::array<s16, 32> out{};
    s16 h1 = 0, h2 = 0;
    SUBCASE("zero coefficients reduce to nibble * (scale + 1)") {
        REQUIRE(adx_decode_frame(kFrameA, AdxCoefficients{0, 0}, h1, h2, out));
        const std::array<s16, 32> z = {56, -64, 8, -8, 0, 0, 0, 0, 24, 32, 40, 48, -56, -48, -40, -32,
                                       0,  0,   0, 0,  56, -8, -64, 8, 16, 16, -16, -16, 0, 0, 0, 0};
        CHECK(out == z);
    }
    SUBCASE("frame A then frame B (history carried)") {
        REQUIRE(adx_decode_frame(kFrameA, k48, h1, h2, out));
        CHECK(out == kA48);
        CHECK(h1 == -257);
        CHECK(h2 == -253);
        REQUIRE(adx_decode_frame(kFrameB, k48, h1, h2, out));
        CHECK(out == kB48);
        CHECK(h1 == 14503);
        CHECK(h2 == 19203);
    }
    SUBCASE("saturation") {
        REQUIRE(adx_decode_frame(kFrameS, k48, h1, h2, out));
        CHECK(out == kS48);
    }
    SUBCASE("24 kHz coefficients from a non-zero history") {
        h1 = 100;
        h2 = -50;
        REQUIRE(adx_decode_frame(kFrameA, adx_coefficients(500, 24000), h1, h2, out));
        CHECK(out == kA24);
    }
    SUBCASE("a scale word with bit 15 ends decoding and leaves the history alone") {
        h1 = 5;
        h2 = 6;
        out.fill(123);
        CHECK_FALSE(adx_decode_frame(kEnd, k48, h1, h2, out));
        CHECK(h1 == 5);
        CHECK(h2 == 6);
        CHECK(out[0] == 123);
    }
}

TEST_CASE("AdxDecoder: mono file, sample count stops mid-frame") {
    const auto f = make_adx(1, 48000, 40, {{kFrameA}, {kFrameB}});
    auto d = AdxDecoder::open(view(f));
    REQUIRE(d.ok());
    CHECK(d->channels() == 1);
    CHECK(d->sample_rate() == 48000);
    CHECK_FALSE(d->has_loop());
    std::vector<s16> pcm(100, 0);
    const std::size_t n = d->decode(pcm);
    REQUIRE(n == 40);
    for (int i = 0; i < 32; ++i) CHECK(pcm[i] == kA48[i]);
    for (int i = 0; i < 8; ++i) CHECK(pcm[32 + i] == kB48[i]);
    CHECK(d->decode(pcm) == 0);
    CHECK(d->frames_out() == 40);
}

TEST_CASE("AdxDecoder: stereo interleaves one frame per channel with separate histories") {
    // ch0 = A, B; ch1 = S, A. Channel 1's second frame starts from S's history, not from channel 0's.
    const auto f = make_adx(2, 48000, 64, {{kFrameA, kFrameS}, {kFrameB, kFrameA}});
    auto d = AdxDecoder::open(view(f));
    REQUIRE(d.ok());
    std::vector<s16> pcm(256, 0);
    REQUIRE(d->decode(pcm) == 64);
    for (int i = 0; i < 32; ++i) {
        CHECK(pcm[2 * i] == kA48[i]);
        CHECK(pcm[2 * i + 1] == kS48[i]);
        CHECK(pcm[64 + 2 * i] == kB48[i]);
    }
    // Channel 1, frame 2 = A from S's final history (h1 32559, h2 32767), oracle:
    //   s0 = (7400*32559 - 3342*32767) >> 12 = 131429286 >> 12 = 32087, + 56 -> 32143.
    const std::array<s16, 32> exp = {32143, 31441, 30584, 29593, 28509, 27360, 26168, 24952, 23752, 22584, 21461,
                                     20393, 19276, 18137, 16999, 15880, 14819, 13815, 12867, 11974, 11190, 10438,
                                     9663,  8949,  8299,  7707,  7136,  6587,  6077,  5604,  5166,  4760};
    for (int i = 0; i < 32; ++i) CHECK(pcm[64 + 2 * i + 1] == exp[i]);
}

TEST_CASE("AdxDecoder: v4 loop block repeats the loop region bit-exactly, then plays the tail") {
    // 3 frames (A, B, A), loop [32, 64) = the B frame. loops = 1: 0..64, 32..64 again, 64..96.
    const auto f = make_adx(1, 24000, 96, {{kFrameA}, {kFrameB}, {kFrameA}}, true, 32, 64);
    auto d = AdxDecoder::open(view(f));
    REQUIRE(d.ok());
    REQUIRE(d->has_loop());
    d->set_loops(1);
    std::vector<s16> pcm(512, 0);
    const std::size_t n = d->decode(pcm);
    REQUIRE(n == 128);
    for (int i = 0; i < 32; ++i) CHECK(pcm[64 + i] == pcm[32 + i]);  // the repetition equals pass 1
    // The tail frame continues from the end-of-B history either way, so it equals a plain decode's.
    auto plain = AdxDecoder::open(view(f));
    REQUIRE(plain.ok());
    std::vector<s16> ref(512, 0);
    REQUIRE(plain->decode(ref) == 96);
    for (int i = 0; i < 64; ++i) CHECK(pcm[i] == ref[i]);
    for (int i = 0; i < 32; ++i) CHECK(pcm[96 + i] == ref[64 + i]);
    CHECK(d->decode(pcm) == 0);
}

TEST_CASE("AdxDecoder: refuses what it does not decode") {
    auto f = make_adx(1, 48000, 32, {{kFrameA}});
    f[19] = std::byte{0x08};  // encrypted flag
    CHECK_FALSE(AdxDecoder::open(view(f)).ok());
    auto g = make_adx(1, 48000, 32, {{kFrameA}});
    g[4] = std::byte{2};  // encoding
    CHECK_FALSE(AdxDecoder::open(view(g)).ok());
    CHECK_FALSE(decode_adx(view(g)).ok());
    CHECK_FALSE(decode_adx(view(f), -1).ok());
}

TEST_CASE("decode_adx_to_wav writes a canonical PCM16 WAV") {
    const auto f = make_adx(1, 48000, 64, {{kFrameA}, {kFrameB}});
    const std::filesystem::path out = std::filesystem::path(P3FES_TEST_TMP_DIR) / "adx_ab.wav";
    REQUIRE(decode_adx_to_wav(view(f), out));
    std::ifstream in(out, std::ios::binary);
    std::vector<char> w((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    REQUIRE(w.size() == 44 + 64 * 2);
    CHECK(std::memcmp(w.data(), "RIFF", 4) == 0);
    CHECK(std::memcmp(w.data() + 8, "WAVEfmt ", 8) == 0);
    s16 first = 0;
    std::memcpy(&first, w.data() + 44, 2);
    CHECK(first == 56);
    s16 s33 = 0;
    std::memcpy(&s33, w.data() + 44 + 2 * 33, 2);
    CHECK(s33 == kB48[1]);
}

TEST_CASE("real file (skips without extracted/): BGM/0501.ADX decodes to its header's sample count") {
    const std::filesystem::path p = std::filesystem::path(P3FES_EXTRACTED_DIR) / "BGM" / "0501.ADX";
    if (!std::filesystem::exists(p)) {
        MESSAGE("skipped: " << p.string() << " not present");
        return;
    }
    std::ifstream in(p, std::ios::binary);
    std::vector<char> raw((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    const formats::Bytes b(reinterpret_cast<const std::byte*>(raw.data()), raw.size());
    auto d = AdxDecoder::open(b);
    REQUIRE(d.ok());
    const u64 frames = d->header().sample_count;
    auto pcm = decode_adx(b);
    REQUIRE(pcm.ok());
    CHECK(pcm->size() == frames * d->channels());
    s32 peak = 0;
    for (s16 s : pcm.value()) peak = std::max<s32>(peak, s < 0 ? -s : s);
    CHECK(peak > 1000);  // music, not silence
}
