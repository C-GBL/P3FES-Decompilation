// p3fes/state_io.h: the machine-state archive (runtime/STATE.md) -- symmetric save/load of raw values and the
// standard containers, section tags, expected values, truncation, and the state file container (header,
// zero-run elision, payload hash).
#include "doctest.h"

#include "p3fes/state_io.h"

#include <cstdio>
#include <filesystem>
#include <string>

namespace {

struct Plain {
    int a = 0;
    double b = 0;
};

struct Composite {
    std::string name;
    std::vector<int> v;
    std::map<std::string, std::uint64_t> m;
    std::deque<std::vector<std::uint8_t>> q;
    std::optional<Plain> opt;
    void state(p3fes::StateIo& io) { io(name, v, m, q, opt); }
};

}  // namespace

TEST_CASE("state_io: a composite round-trips and sections are checked") {
    Composite c;
    c.name = "kernel";
    c.v = {1, 2, 3};
    c.m = {{"x", 7}, {"y", 9}};
    c.q = {{1, 2}, {}, {3}};
    c.opt = Plain{5, 2.5};
    std::array<std::uint32_t, 4> arr{4, 3, 2, 1};
    p3fes::StateIo w;
    w.section("one");
    w(c, arr);
    w.expect(std::uint64_t{42}, "answer");
    w.section("two");
    REQUIRE(w.ok());

    Composite d;
    d.v = {9, 9, 9};  // same size: overwritten in place
    const int* before = d.v.data();
    std::array<std::uint32_t, 4> arr2{};
    p3fes::StateIo r(w.buffer().data(), w.buffer().size());
    r.section("one");
    r(d, arr2);
    r.expect(std::uint64_t{42}, "answer");
    r.section("two");
    CHECK(r.ok());
    CHECK(r.at_end());
    CHECK(d.name == "kernel");
    CHECK(d.v == c.v);
    CHECK(d.v.data() == before);
    CHECK(d.m == c.m);
    CHECK(d.q == c.q);
    REQUIRE(d.opt.has_value());
    CHECK(d.opt->a == 5);
    CHECK(arr2 == arr);
}

TEST_CASE("state_io: a section or expected-value mismatch and truncation fail by name") {
    p3fes::StateIo w;
    w.section("gs-core");
    std::uint32_t x = 1;
    w(x);
    w.expect(std::uint64_t{3}, "layout");
    {
        p3fes::StateIo r(w.buffer().data(), w.buffer().size());
        r.section("gif");
        CHECK_FALSE(r.ok());
        CHECK(r.error().find("gif") != std::string::npos);
    }
    {
        p3fes::StateIo r(w.buffer().data(), w.buffer().size());
        r.section("gs-core");
        std::uint32_t y = 0;
        r(y);
        r.expect(std::uint64_t{4}, "layout");
        CHECK_FALSE(r.ok());
        CHECK(r.error().find("layout") != std::string::npos);
    }
    {
        p3fes::StateIo r(w.buffer().data(), 6);
        r.section("gs-core");
        std::uint32_t y = 0;
        r(y);
        CHECK_FALSE(r.ok());
    }
}

TEST_CASE("state_io: the state file keeps the payload exactly (zero runs elided) and rejects damage") {
    std::vector<std::uint8_t> payload(300000, 0);
    for (std::size_t i = 0; i < payload.size(); i += 4099) payload[i] = static_cast<std::uint8_t>(i * 7 + 1);
    payload.back() = 0x5A;
    const std::string path = (std::filesystem::temp_directory_path() / "p3fes_state_io_test.p3st").string();
    p3fes::StateHeader h;
    h.vblanks = 1234;
    std::string err;
    REQUIRE(p3fes::write_state_file(path, h, payload, err));
    p3fes::StateHeader g;
    std::vector<std::uint8_t> back;
    REQUIRE(p3fes::read_state_file(path, g, back, err));
    CHECK(back == payload);
    CHECK(g.vblanks == 1234);
    CHECK(g.stored_bytes < payload.size() / 10);
    // one flipped byte in the stored data: the payload hash catches it
    {
        std::FILE* f = std::fopen(path.c_str(), "r+b");
        REQUIRE(f);
        std::fseek(f, static_cast<long>(sizeof(p3fes::StateHeader) + 8), SEEK_SET);
        const int c = std::fgetc(f);
        std::fseek(f, static_cast<long>(sizeof(p3fes::StateHeader) + 8), SEEK_SET);
        std::fputc(c ^ 0xFF, f);
        std::fclose(f);
    }
    CHECK_FALSE(p3fes::read_state_file(path, g, back, err));
    std::remove(path.c_str());
}
