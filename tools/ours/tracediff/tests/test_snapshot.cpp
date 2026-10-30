// doctest tests for tracediff snapshot mode: synthetic 32 MiB images with known
// runs, mask parsing/application, derived masks, size-mismatch refusal.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "../snapshot.h"

namespace snap = tracediff::snapshot;
namespace fs = std::filesystem;

namespace {

std::vector<std::uint8_t> blank_image() { return std::vector<std::uint8_t>(snap::kEeRamSize, 0); }

// Fills a deterministic non-zero pattern so matching bytes are not just zeros.
void pattern(std::vector<std::uint8_t>& img) {
    for (std::size_t i = 0; i < img.size(); i += 4096) img[i] = static_cast<std::uint8_t>(0x80 | (i >> 12));
}

void poke(std::vector<std::uint8_t>& img, std::uint32_t off, std::uint32_t len, std::uint8_t delta = 1) {
    for (std::uint32_t k = 0; k < len; ++k) img[off + k] = static_cast<std::uint8_t>(img[off + k] + delta);
}

fs::path temp_dir() {
    fs::path d = fs::temp_directory_path() / "tracediff_snapshot_tests";
    fs::create_directories(d);
    return d;
}

void write_file(const fs::path& p, const std::vector<std::uint8_t>& data) {
    std::ofstream f(p, std::ios::binary);
    f.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
}

}  // namespace

TEST_CASE("snapshot: identical images -> no runs, kernel mask accounted") {
    auto a = blank_image();
    pattern(a);
    auto b = a;
    snap::Report r = snap::compare(a.data(), b.data(), a.size(), snap::default_mask());
    CHECK(r.total_differing_bytes == 0);
    CHECK(r.run_count == 0);
    CHECK(r.masked_bytes == 0x100000);
    CHECK_FALSE(r.first_run().has_value());
    REQUIRE(r.per_band.size() == 7);  // 6 bands + other
    for (const auto& bs : r.per_band) CHECK(bs.differing_bytes == 0);
}

TEST_CASE("snapshot: known runs are found, ordered, sized and attributed to bands") {
    auto a = blank_image();
    pattern(a);
    auto b = a;
    // kernel area (masked by default) must not show up
    poke(b, 0x00001000, 64);
    // code band: a 3-byte run at an unaligned offset
    poke(b, 0x00123457, 3);
    // data band: a run that spans a 8-byte word boundary
    poke(b, 0x005A2FFD, 10);
    // bss: a 1-byte run and a large run
    poke(b, 0x007CE10C, 1);
    poke(b, 0x00800000, 5000);
    // heap and stack
    poke(b, 0x00A00000, 2);
    poke(b, 0x01FF0000, 7);
    // ELF gap -> "other"
    poke(b, 0x005A1500, 4);

    snap::Report r = snap::compare(a.data(), b.data(), a.size(), snap::default_mask());
    CHECK(r.total_differing_bytes == 3 + 10 + 1 + 5000 + 2 + 7 + 4);
    CHECK(r.run_count == 7);
    REQUIRE(r.first_run().has_value());
    CHECK(r.first_run()->offset == 0x00123457);
    CHECK(r.first_run()->length == 3);
    // address order
    CHECK(r.runs[1].offset == 0x005A1500);
    CHECK(r.runs[2].offset == 0x005A2FFD);
    CHECK(r.runs[2].length == 10);
    CHECK(r.runs[3].offset == 0x007CE10C);
    CHECK(r.runs[3].length == 1);
    CHECK(r.runs[4].length == 5000);
    CHECK(r.runs[6].offset == 0x01FF0000);

    auto top = r.largest_runs(3);
    REQUIRE(top.size() == 3);
    CHECK(top[0].length == 5000);
    CHECK(top[1].length == 10);
    CHECK(top[2].length == 7);

    auto band = [&](const char* name) {
        for (const auto& bs : r.per_band)
            if (bs.name == name) return bs;
        FAIL("missing band ", name);
        return snap::BandStat{};
    };
    CHECK(band("kernel").differing_bytes == 0);
    CHECK(band("code").differing_bytes == 3);
    CHECK(band("code").runs == 1);
    CHECK(band("data").differing_bytes == 10);
    CHECK(band("bss").differing_bytes == 5001);
    CHECK(band("bss").runs == 2);
    CHECK(band("heap").differing_bytes == 2);
    CHECK(band("stack").differing_bytes == 7);
    CHECK(band("other").differing_bytes == 4);

    SUBCASE("a run spanning a band boundary is split for byte totals but counted once") {
        auto c = a;
        poke(c, 0x009ACC7E, 4);  // 2 bytes bss + 2 bytes heap
        snap::Report r2 = snap::compare(a.data(), c.data(), a.size(), snap::default_mask());
        CHECK(r2.run_count == 1);
        CHECK(r2.total_differing_bytes == 4);
        std::uint64_t bss = 0, heap = 0, bss_runs = 0, heap_runs = 0;
        for (const auto& bs : r2.per_band) {
            if (bs.name == "bss") bss = bs.differing_bytes, bss_runs = bs.runs;
            if (bs.name == "heap") heap = bs.differing_bytes, heap_runs = bs.runs;
        }
        CHECK(bss == 2);
        CHECK(heap == 2);
        CHECK(bss_runs == 1);
        CHECK(heap_runs == 0);
    }

    SUBCASE("without the default mask the kernel run appears first") {
        snap::Mask none;
        snap::Report r3 = snap::compare(a.data(), b.data(), a.size(), none);
        CHECK(r3.run_count == 8);
        CHECK(r3.first_run()->offset == 0x00001000);
        CHECK(r3.first_run()->length == 64);
        CHECK(r3.masked_bytes == 0);
    }

    SUBCASE("to_json names the first run and per-band table") {
        std::string j = snap::to_json(r, 20, "ref.bin", "ours.bin");
        CHECK(j.find("\"first_run\": {\"va\": \"0x00123457\", \"length\": 3, \"band\": \"code\"}") != std::string::npos);
        CHECK(j.find("\"differing_bytes\": 5027") != std::string::npos);
        CHECK(j.find("\"bss\": {\"differing_bytes\": 5001, \"runs\": 2}") != std::string::npos);
    }
}

TEST_CASE("snapshot: mask parsing accepts the three line forms, comments, kseg0 and clips") {
    snap::ParseError err;
    auto m = snap::parse_mask(
        "# kernel\n"
        "0x00000000-0x000FFFFF\n"
        "  7CE10C   # frame counter (one word)\n"
        "0x807CE0FC+8   # kseg0 address, length form\n"
        "0x7CE100 \xE2\x80\x93 0x7CE103\n"  // en dash, adjacent to the previous -> merged
        "0x01FFFFF0-0x02000FFF  # clipped to the image\n",
        &err);
    REQUIRE(m.has_value());
    REQUIRE(m->ranges.size() == 4);
    CHECK(m->ranges[0].begin == 0);
    CHECK(m->ranges[0].end == 0x100000);
    CHECK(m->ranges[1].begin == 0x7CE0FC);
    CHECK(m->ranges[1].end == 0x7CE104);  // 0x7CE0FC+8 merged with 0x7CE100-0x7CE103
    CHECK(m->ranges[2].begin == 0x7CE10C);
    CHECK(m->ranges[2].end == 0x7CE110);
    CHECK(m->ranges[3].begin == 0x01FFFFF0);
    CHECK(m->ranges[3].end == snap::kEeRamSize);
    CHECK(m->covers(0x7CE10D));
    CHECK_FALSE(m->covers(0x7CE110));
    CHECK(m->masked_bytes() == 0x100000 + 8 + 4 + 16);

    SUBCASE("errors carry the line number") {
        auto bad = snap::parse_mask("0x100000-0xFFFFF\n", &err);
        CHECK_FALSE(bad.has_value());
        CHECK(err.line == 1);
        bad = snap::parse_mask("\n\nzz\n", &err);
        CHECK_FALSE(bad.has_value());
        CHECK(err.line == 3);
        bad = snap::parse_mask("0x7CE10C+0\n", &err);
        CHECK_FALSE(bad.has_value());
        bad = snap::parse_mask("0x02000000\n", &err);
        CHECK_FALSE(bad.has_value());
    }

    SUBCASE("format_mask round-trips") {
        std::string text = snap::format_mask(*m, "hdr line 1\nline 2");
        CHECK(text.rfind("# hdr line 1\n# line 2\n", 0) == 0);
        auto again = snap::parse_mask(text, &err);
        REQUIRE(again.has_value());
        REQUIRE(again->ranges.size() == m->ranges.size());
        for (std::size_t i = 0; i < m->ranges.size(); ++i) {
            CHECK(again->ranges[i].begin == m->ranges[i].begin);
            CHECK(again->ranges[i].end == m->ranges[i].end);
        }
    }
}

TEST_CASE("snapshot: a mask hides runs and never lets a run span a masked range") {
    auto a = blank_image();
    auto b = a;
    poke(b, 0x00700000, 32);  // will be partially masked: bytes 0x700008..0x70000F
    poke(b, 0x00710000, 4);   // fully masked
    poke(b, 0x00720000, 4);   // untouched
    auto m = snap::parse_mask("0x700008-0x70000F\n0x710000+4\n");
    REQUIRE(m.has_value());
    for (const auto& r : snap::default_mask().ranges) m->add(r);
    m->normalize();
    snap::Report r = snap::compare(a.data(), b.data(), a.size(), *m);
    CHECK(r.total_differing_bytes == 24 + 4);
    REQUIRE(r.run_count == 3);
    CHECK(r.runs[0].offset == 0x700000);
    CHECK(r.runs[0].length == 8);
    CHECK(r.runs[1].offset == 0x700010);
    CHECK(r.runs[1].length == 16);
    CHECK(r.runs[2].offset == 0x720000);
}

TEST_CASE("snapshot-mask: derive_mask pads and merges the noise runs") {
    auto a = blank_image();
    auto b = a;
    poke(b, 0x007CE10C, 4);
    poke(b, 0x007CE118, 2);
    poke(b, 0x00900000, 1);
    snap::Report r = snap::compare(a.data(), b.data(), a.size(), snap::default_mask());
    REQUIRE(r.run_count == 3);

    snap::Mask m0 = snap::derive_mask(r, 0, 0);
    REQUIRE(m0.ranges.size() == 3);
    CHECK(m0.ranges[0].begin == 0x7CE10C);
    CHECK(m0.ranges[0].end == 0x7CE110);

    snap::Mask m1 = snap::derive_mask(r, 4, 16);
    REQUIRE(m1.ranges.size() == 2);
    CHECK(m1.ranges[0].begin == 0x7CE108);
    CHECK(m1.ranges[0].end == 0x7CE11E);
    CHECK(m1.ranges[1].begin == 0x8FFFFC);
    CHECK(m1.ranges[1].end == 0x900005);

    // Applying the derived mask to the same pair yields no differences.
    snap::Mask full = m1;
    for (const auto& x : snap::default_mask().ranges) full.add(x);
    full.normalize();
    snap::Report r2 = snap::compare(a.data(), b.data(), a.size(), full);
    CHECK(r2.total_differing_bytes == 0);
}

TEST_CASE("snapshot: dead_stack_mask reads thread stacks from a p3fes capture.json") {
    // Two waiting threads and the main thread running (current_thread 1, live sp recorded).
    const std::string cap =
        "{\n  \"pc\": \"0x00503084\",\n  \"sp\": \"0x01FFF100\",\n  \"current_thread\": 1,\n  \"threads\": [\n"
        "    {\"tid\": 1, \"status\": \"RUN\", \"priority\": 0, \"entry\": \"0x00000000\", \"stack\": \"0x01F60000\", \"stack_size\": \"0xA0000\", \"frame\": \"0x01FFF9D0\"},\n"
        "    {\"tid\": 7, \"status\": \"WAIT\", \"priority\": 18, \"entry\": \"0x0053FCF8\", \"stack\": \"0x0078AF70\", \"stack_size\": \"0x1000\", \"frame\": \"0x0078BC90\"},\n"
        "    {\"tid\": 9, \"status\": \"WAIT\", \"priority\": 28, \"entry\": \"0x0010C7D0\", \"stack\": \"0x00803640\", \"stack_size\": \"0x20000\", \"frame\": \"0x00803640\"}\n"
        "  ],\n  \"state_globals\": {\"g_skyFrameCount\": 2246}\n}\n";
    std::string why;
    auto m = snap::dead_stack_mask(cap, &why);
    REQUIRE(m);
    // Running thread: [stack, live sp); waiting thread: [stack, frame); a frame at the stack base masks nothing.
    REQUIRE(m->ranges.size() == 2);
    CHECK(m->ranges[0].begin == 0x0078AF70u);
    CHECK(m->ranges[0].end == 0x0078BC90u);
    CHECK(m->ranges[1].begin == 0x01F60000u);
    CHECK(m->ranges[1].end == 0x01FFF100u);
    CHECK(m->covers(0x0078B6B0u));       // the ADX fs thread's dead area
    CHECK_FALSE(m->covers(0x0078BC90u)); // its saved context frame is live
    CHECK_FALSE(m->covers(0x01FFF100u)); // the running thread's live frame
    CHECK(m->covers(0x01FFF0FFu));
    // Idle at the snapshot (current_thread 0): every thread uses its frame, the sp key is ignored.
    std::string idle = cap;
    idle.replace(idle.find("\"current_thread\": 1"), 19, "\"current_thread\": 0");
    auto mi = snap::dead_stack_mask(idle, &why);
    REQUIRE(mi);
    REQUIRE(mi->ranges.size() == 2);
    CHECK(mi->ranges[1].end == 0x01FFF9D0u);
    // No threads array: refused with a reason.
    CHECK_FALSE(snap::dead_stack_mask("{\"pc\": \"0x1\"}", &why));
    CHECK(why.find("threads") != std::string::npos);
}

TEST_CASE("load_image refuses anything but a 32 MiB image") {
    fs::path d = temp_dir();
    fs::path small = d / "small.bin", exact = d / "exact.bin", missing = d / "does_not_exist.bin";
    write_file(small, std::vector<std::uint8_t>(1024, 0));
    write_file(exact, blank_image());
    std::string err;
    CHECK(snap::load_image(small.string(), &err).empty());
    CHECK(err.find("expected 33554432") != std::string::npos);
    err.clear();
    CHECK(snap::load_image(missing.string(), &err).empty());
    CHECK(err.find("cannot open") != std::string::npos);
    auto img = snap::load_image(exact.string(), &err);
    CHECK(img.size() == snap::kEeRamSize);
    fs::remove(small);
    fs::remove(exact);
}

TEST_CASE("band_of covers the ELF layout") {
    CHECK(std::string(snap::band_of(0x00000000)) == "kernel");
    CHECK(std::string(snap::band_of(0x000FFFFF)) == "kernel");
    CHECK(std::string(snap::band_of(0x00100000)) == "code");
    CHECK(std::string(snap::band_of(0x005A13FF)) == "code");
    CHECK(std::string(snap::band_of(0x005A1400)) == "other");
    CHECK(std::string(snap::band_of(0x005A2000)) == "data");
    CHECK(std::string(snap::band_of(0x007CDE04)) == "other");
    CHECK(std::string(snap::band_of(0x007CDE80)) == "bss");
    CHECK(std::string(snap::band_of(0x009ACC80)) == "heap");
    CHECK(std::string(snap::band_of(0x01F5FFFF)) == "heap");
    CHECK(std::string(snap::band_of(0x01F60000)) == "stack");
    CHECK(std::string(snap::band_of(0x01FFFFFF)) == "stack");
}
