// AudioSink timeline math and the Null/Tee/WAV sinks (runtime/audio). Hand-derived values.
#include <doctest.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#include "p3fes/audio/audio_sink.h"
#include "p3fes/audio/host_audio.h"
#include "p3fes/audio/wav.h"

using namespace p3fes;
using namespace p3fes::audio;

namespace {
std::vector<char> slurp(const std::filesystem::path& p) {
    std::ifstream in(p, std::ios::binary);
    return std::vector<char>((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}
u32 le32(const std::vector<char>& v, std::size_t o) {
    u32 x = 0;
    std::memcpy(&x, v.data() + o, 4);
    return x;
}
std::filesystem::path tmp(const char* name) { return std::filesystem::path(P3FES_TEST_TMP_DIR) / name; }
}  // namespace

TEST_CASE("timeline: 48 kHz frames are exactly 6144 EE cycles; other rates floor/ceil consistently") {
    CHECK(kCyclesPerOutputFrame == 6144);
    CHECK(frames_at_cycles(0) == 0);
    CHECK(frames_at_cycles(6143) == 0);
    CHECK(frames_at_cycles(6144) == 1);
    CHECK(frames_at_cycles(294'912'000) == 48'000);       // one virtual second
    CHECK(cycles_at_frame(512) == 512ull * 6144);          // one PSM pass = 3,145,728 cycles (10.67 ms)
    CHECK(frames_at_cycles(10ull * 294'912'000 * 3600) == 10ull * 48'000 * 3600);  // 10 h, no overflow
    // 44.1 kHz: 294,912,000 / 44,100 = 6687.34 cycles per frame.
    CHECK(frames_at_cycles(6687, 44'100) == 0);
    CHECK(frames_at_cycles(6688, 44'100) == 1);
    CHECK(cycles_at_frame(1, 44'100) == 6688);
    for (u64 f : {0ull, 1ull, 2ull, 44'099ull, 44'100ull, 44'101ull, 123'456'789ull}) {
        const u64 c = cycles_at_frame(f, 44'100);
        CHECK(frames_at_cycles(c, 44'100) >= f);
        if (c > 0) CHECK(frames_at_cycles(c - 1, 44'100) < f);
    }
}

TEST_CASE("TimelineCursor: first push is the origin; gaps become silence, overlaps are skipped") {
    TimelineCursor t;
    auto p = t.place(1000, 512);
    CHECK(t.origin() == 1000);
    CHECK(p.silence == 0);
    CHECK(p.skip == 0);
    p = t.place(1512, 512);  // contiguous
    CHECK(p.silence == 0);
    p = t.place(3000, 100);  // gap of 3000 - 2024 = 976 frames
    CHECK(p.silence == 976);
    CHECK(t.next() == 3100);
    p = t.place(3050, 100);  // overlaps 50 frames
    CHECK(p.silence == 0);
    CHECK(p.skip == 50);
    CHECK(t.next() == 3150);
}

TEST_CASE("NullSink: counts, gaps, clipping, deterministic fingerprint") {
    std::vector<s16> a(512 * 2, 0), b(512 * 2);
    for (std::size_t i = 0; i < b.size(); ++i) b[i] = static_cast<s16>(i * 7 - 1000);
    NullSink n1, n2;
    for (NullSink* n : {&n1, &n2}) {
        n->push(100, a);
        n->push(612, b);
        n->push(2000, b);   // gap 2000 - 1124 = 876
        n->push(2400, a);   // overlaps 112 frames of the previous push
    }
    CHECK(n1.frames() == 512 * 4 - 112);
    CHECK(n1.first_frame() == 100);
    CHECK(n1.end_frame() == 2912);
    CHECK(n1.gap_frames() == 876);
    CHECK(n1.clipped_frames() == 112);
    CHECK(n1.non_silent_frames() == 1024);
    CHECK(n1.peak() == 6161);  // b[i] = 7i - 1000 for i < 1024
    CHECK(n1.hash() == n2.hash());
    NullSink n3;
    n3.push(100, a);
    n3.push(613, b);  // one frame later: different fingerprint
    CHECK(n3.hash() != n1.hash());
}

TEST_CASE("wav_image and WavWriter produce the canonical 44-byte PCM16 header") {
    const std::vector<s16> pcm = {1, -1, 2, -2, 300, -300};
    const auto img = wav_image(48000, 2, pcm);
    REQUIRE(img.size() == 44 + 12);
    CHECK(std::memcmp(img.data(), "RIFF", 4) == 0);
    std::vector<char> v(img.begin(), img.end());
    CHECK(le32(v, 4) == 36 + 12);
    CHECK(le32(v, 16) == 16);
    CHECK((le32(v, 20) & 0xFFFF) == 1);       // PCM
    CHECK((le32(v, 20) >> 16) == 2);          // channels
    CHECK(le32(v, 24) == 48000);
    CHECK(le32(v, 28) == 48000 * 4);
    CHECK((le32(v, 32) & 0xFFFF) == 4);       // block align
    CHECK((le32(v, 32) >> 16) == 16);         // bits
    CHECK(le32(v, 40) == 12);
    WavWriter w;
    REQUIRE(w.open(tmp("writer.wav"), 48000, 2));
    w.write(pcm);
    w.write_silence(2);
    CHECK(w.frames() == 5);
    REQUIRE(w.close());
    const auto f = slurp(tmp("writer.wav"));
    REQUIRE(f.size() == 44 + 20);
    CHECK(le32(f, 40) == 20);
    CHECK(std::memcmp(f.data() + 44, img.data() + 44, 12) == 0);
    for (int i = 56; i < 64; ++i) CHECK(f[i] == 0);
}

TEST_CASE("WavSink fills gaps with silence relative to the first push") {
    {
        WavSink s(tmp("sink.wav"));
        std::vector<s16> x(4 * 2, 1000);
        s.push(48000, x);   // origin
        s.push(48010, x);   // 6 frames of silence first
        s.flush();
        CHECK(s.origin_frame() == 48000);
        CHECK(s.ok());
    }
    const auto f = slurp(tmp("sink.wav"));
    REQUIRE(f.size() == 44 + (4 + 6 + 4) * 4);
    s16 v = 0;
    std::memcpy(&v, f.data() + 44 + 4 * 4, 2);
    CHECK(v == 0);
    std::memcpy(&v, f.data() + 44 + 10 * 4, 2);
    CHECK(v == 1000);
}

TEST_CASE("WavStreamDumper interleaves planar channels and pads the short one at the end") {
    std::filesystem::path out;
    {
        WavStreamDumper d(tmp("streams"));
        d.stream_begin(StreamInfo{7, 3, 2, 24000});
        const std::vector<s16> l = {1, 2, 3}, r = {-1, -2};
        d.stream_data(7, 0, l);
        d.stream_data(7, 1, r);
        d.stream_end(7);
        REQUIRE(d.files().size() == 1);
        out = d.files()[0];
    }
    CHECK(out.filename().string() == "stream_0007_slot03_24000hz_2ch.wav");
    const auto f = slurp(out);
    REQUIRE(f.size() == 44 + 3 * 4);
    CHECK(le32(f, 24) == 24000);
    std::vector<s16> s(6);
    std::memcpy(s.data(), f.data() + 44, 12);
    CHECK(s == std::vector<s16>{1, -1, 2, -2, 3, 0});
}

TEST_CASE("HostAudio headless: NullSink fingerprint always fed; WAV dumps on request") {
    HostAudio a({});
    CHECK_FALSE(a.xaudio2_active());
    CHECK(a.stream_tap() == nullptr);
    std::vector<s16> x(512 * 2, 3);
    a.mix_sink()->push(0, x);
    CHECK(a.fingerprint().frames() == 512);
    HostAudio b({.dump_wav_dir = tmp("host")});
    REQUIRE(b.stream_tap() != nullptr);
    b.mix_sink()->push(10, x);
    b.flush();
    CHECK(std::filesystem::file_size(tmp("host") / "mix_48k.wav") == 44 + 512 * 4);
    CHECK(default_dump_dir("C:/repo").generic_string() == "C:/repo/extracted/_ours/wav");
}
