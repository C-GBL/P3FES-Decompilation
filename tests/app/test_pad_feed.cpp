// Input scripts, record/replay logs and the per-vblank latch (runtime/app/input.h PadFeed).
#include <doctest.h>

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "input.h"

using namespace p3fes::app;
namespace pb = p3fes::hle::sif::pad_button;

namespace {

std::filesystem::path temp_file(const char* name) {
    const auto tick = std::chrono::steady_clock::now().time_since_epoch().count();
    return std::filesystem::temp_directory_path() / ("p3fes_app_tests_" + std::to_string(tick) + "_" + name);
}

std::string slurp(const std::filesystem::path& p) {
    std::ifstream f(p, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

std::vector<ScriptPress> script(const char* text) {
    std::vector<ScriptPress> out;
    std::string err;
    REQUIRE_MESSAGE(parse_input_script(text, out, err), err);
    return out;
}

// A deterministic stand-in for a player: a new state every few vblanks (LCG), sometimes repeating the old one.
struct FakePlayer {
    std::uint32_t s = 12345;
    PadInput state{};
    std::uint32_t next() { return s = s * 1664525u + 1013904223u; }
    const PadInput& at(std::uint64_t v) {
        if (v % 7 == 0) {
            const std::uint32_t r = next();
            if (r & 0x10000000u) {
                state.buttons = static_cast<std::uint16_t>(r & 0xFFFFu);
                state.lx = static_cast<std::uint8_t>(next() >> 24);
                state.ry = static_cast<std::uint8_t>(next() >> 24);
            }
        }
        return state;
    }
};

} // namespace

TEST_CASE("input scripts: V:BUTTONS[:N] entries, --press form, stick values, errors") {
    const auto s = script(" 120:start , 600:cross+circle:8,700:lx=0x00+ly=255+up ");
    REQUIRE(s.size() == 3);
    CHECK(s[0].vblank == 120);
    CHECK(s[0].frames == 4);
    CHECK(s[0].buttons == pb::kStart);
    CHECK(s[0].lx == -1);
    CHECK(s[1].vblank == 600);
    CHECK(s[1].frames == 8);
    CHECK(s[1].buttons == (pb::kCross | pb::kCircle));
    CHECK(s[2].buttons == pb::kUp);
    CHECK(s[2].lx == 0);
    CHECK(s[2].ly == 255);
    CHECK(s[2].rx == -1);

    std::vector<ScriptPress> p;
    std::string err;
    REQUIRE(parse_press("START@600", p, err));
    REQUIRE(parse_press("cross+up@10:2", p, err));
    REQUIRE(p.size() == 2);
    CHECK(p[0].vblank == 600);
    CHECK(p[0].frames == 4);
    CHECK(p[0].buttons == pb::kStart);
    CHECK(p[1].vblank == 10);
    CHECK(p[1].frames == 2);
    CHECK(p[1].buttons == (pb::kCross | pb::kUp));

    for (const char* bad : {"abc", "12", "12:", "12:foo", "12:start:0", "x:start", "12:lx=256", "12:qx=1", "12:start:x", "-1:start"}) {
        std::vector<ScriptPress> o;
        CHECK_FALSE_MESSAGE(parse_input_script(bad, o, err), bad);
        CHECK(o.empty());
    }
    for (const char* bad : {"start", "@5", "start@", "start@5:0", "nope@5"}) {
        std::vector<ScriptPress> o;
        CHECK_FALSE_MESSAGE(parse_press(bad, o, err), bad);
    }
    std::vector<ScriptPress> empty;
    CHECK(parse_input_script("", empty, err));
    CHECK(empty.empty());
}

TEST_CASE("--input-script takes the P3FES_PAD_SCRIPT format with the same activation rule") {
    // The M2 drive's memory-card dialog answer (INTEGRATION_LOG, commit 4befea7).
    const auto m2 = script("560:left:4,580:cross:4");
    REQUIRE(m2.size() == 2);
    CHECK(m2[0].vblank == 560);
    CHECK(m2[0].frames == 4);
    CHECK(m2[0].buttons == pb::kLeft);
    CHECK(m2[1].vblank == 580);
    CHECK(m2[1].buttons == pb::kCross);
    // Every button name of that format, '+'-joined, with and without a frame count; the state latched at each
    // VBLANK_START equals the former host_service rule: OR of the presses with vblank <= V < vblank + frames.
    const char* names[] = {"up", "down", "left", "right", "circle", "cross", "square", "triangle",
                           "start", "select", "l1", "l2", "r1", "r2", "l3", "r3"};
    std::string text;
    std::uint32_t r = 7;
    for (int i = 0; i < 40; ++i) {
        r = r * 1664525u + 1013904223u;
        const char* a = names[(r >> 8) % 16];
        const char* b = names[(r >> 16) % 16];
        text += std::to_string(10 + (r >> 20) % 400) + ":" + a + ((r & 1) ? std::string("+") + b : std::string());
        if (r & 2) text += ":" + std::to_string(1 + (r >> 4) % 9);
        text += ",";
    }
    const auto presses = script(text.c_str());
    REQUIRE(presses.size() == 40);
    PadFeed f;
    f.add_script(presses);
    for (std::uint64_t v = 1; v <= 450; ++v) {
        std::uint16_t want = 0;
        for (const ScriptPress& p : presses)
            if (v >= p.vblank && v < p.vblank + p.frames) want = static_cast<std::uint16_t>(want | p.buttons);
        f.latch(v);
        CHECK_MESSAGE(f.current().buttons == want, "vblank " << v);
        CHECK(f.current().lx == 0x80);  // sticks centred, as the former block's PadInput{}
        CHECK(f.current().connected);
    }
}

TEST_CASE("a scripted press lands exactly at VBLANK_START N and lasts N frames") {
    PadFeed f;
    f.add_script(script("100:start:3,102:cross:1"));
    std::map<std::uint64_t, std::uint16_t> seen;
    for (std::uint64_t v = 0; v <= 110; ++v) {
        CHECK(f.latch(v));
        // Later device-service calls in the same vblank (SIF syscalls) latch nothing new.
        CHECK_FALSE(f.latch(v));
        CHECK_FALSE(f.latch(v));
        seen[v] = f.current().buttons;
        CHECK(f.current_vblank() == v);
    }
    CHECK(seen[99] == 0);
    CHECK(seen[100] == pb::kStart);
    CHECK(seen[101] == pb::kStart);
    CHECK(seen[102] == (pb::kStart | pb::kCross));
    CHECK(seen[103] == 0);
    CHECK(f.latches() == 111);
    CHECK(f.changes() == 4);  // the first latch (neutral), 100 (start), 102 (+cross), 103 (neutral)
}

TEST_CASE("live input changes only at vblank edges") {
    PadFeed f;
    PadInput cross;
    cross.buttons = pb::kCross;
    f.latch(50);
    CHECK(f.current().buttons == 0);
    f.set_live(cross);  // sampled by the host between run slices
    CHECK_FALSE(f.latch(50));
    CHECK(f.current().buttons == 0);  // still vblank 50's state
    CHECK(f.latch(51));
    CHECK(f.current().buttons == pb::kCross);
    f.set_live(PadInput{});
    CHECK(f.current().buttons == pb::kCross);
    f.latch(52);
    CHECK(f.current().buttons == 0);
}

TEST_CASE("record -> replay reproduces the PadInput sequence; the log holds one line per change") {
    const std::filesystem::path rec_path = temp_file("rec.txt"), rerec_path = temp_file("rerec.txt");
    std::string err;
    std::map<std::uint64_t, PadInput> recorded;
    std::uint64_t changes = 0;
    {
        PadFeed rec;
        REQUIRE_MESSAGE(rec.open_record(rec_path, err), err);
        rec.add_script(script("500:start:3"));  // scripted presses land in the log as well
        FakePlayer player;
        for (std::uint64_t v = 1; v <= 2000; ++v) {
            rec.set_live(player.at(v));
            rec.latch(v);
            rec.latch(v);
            recorded[v] = rec.current();
        }
        changes = rec.changes();
        rec.close_record();
        CHECK_FALSE(rec.record_failed());
    }
    const std::string text = slurp(rec_path);
    CHECK(text.rfind(std::string(kInputLogHeader), 0) == 0);
    std::vector<InputEvent> events;
    REQUIRE_MESSAGE(parse_input_log(text, events, err), err);
    CHECK(events.size() == changes);
    CHECK(events.size() > 100);
    CHECK(events.size() < 2000);  // only changes
    CHECK(events.front().vblank == 1);
    for (std::size_t i = 1; i < events.size(); ++i) CHECK_FALSE(same_pad(events[i].pad, events[i - 1].pad));

    PadFeed rep;
    REQUIRE(load_input_log(rec_path, events, err));
    rep.set_replay(events);
    REQUIRE(rep.open_record(rerec_path, err));
    PadInput noise;
    noise.buttons = 0xFFFF;
    noise.lx = 0;
    for (std::uint64_t v = 1; v <= 2000; ++v) {
        rep.set_live(noise);  // ignored while replaying
        rep.latch(v);
        CHECK_MESSAGE(same_pad(rep.current(), recorded[v]), "vblank " << v);
    }
    // Past the end of the log the last state holds.
    rep.latch(5000);
    CHECK(same_pad(rep.current(), recorded[2000]));
    rep.close_record();
    // Re-recording the replay gives the same log byte for byte (vblanks 1..2000; 5000 adds nothing new).
    CHECK(slurp(rerec_path) == text);

    // Before the first logged vblank: the neutral pad.
    PadFeed late;
    std::vector<InputEvent> one = {{10, PadInput{}}};
    one[0].pad.buttons = pb::kCircle;
    late.set_replay(one);
    late.latch(9);
    CHECK(late.current().buttons == 0);
    late.latch(10);
    CHECK(late.current().buttons == pb::kCircle);

    std::filesystem::remove(rec_path);
    std::filesystem::remove(rerec_path);
}

TEST_CASE("input log parsing: format and errors") {
    InputEvent e{12345, PadInput{}};
    e.pad.buttons = pb::kCross | pb::kStart;
    e.pad.lx = 0x00;
    e.pad.ry = 0xFF;
    CHECK(format_input_event(e) == "12345 4008 00 80 80 FF");
    std::vector<InputEvent> out;
    std::string err;
    REQUIRE(parse_input_log("# header\n\n1 0000 80 80 80 80\r\n  12345 4008 00 80 80 FF  \n", out, err));
    REQUIRE(out.size() == 2);
    CHECK(out[1].vblank == 12345);
    CHECK(same_pad(out[1].pad, e.pad));
    const struct {
        const char* text;
        const char* where;
    } bad[] = {
        {"5 0000 80 80 80 80\n5 0001 80 80 80 80\n", "line 2"},  // not increasing
        {"5 0000 80 80 80\n", "line 1"},                         // field count
        {"5 00G0 80 80 80 80\n", "line 1"},                      // hex
        {"0x5 0000 80 80 80 80\n", "line 1"},                    // vblank is decimal
        {"5 10000 80 80 80 80\n", "line 1"},                     // 5 hex digits
        {"5 0000 180 80 80 80\n", "line 1"},                     // stick > 0xFF
        {"# ok\n7 0000 80 80 80 80\n3 0000 80 80 80 80\n", "line 3"},
    };
    for (const auto& t : bad) {
        std::vector<InputEvent> o = out;
        CHECK_FALSE_MESSAGE(parse_input_log(t.text, o, err), t.text);
        CHECK_MESSAGE(err.rfind(t.where, 0) == 0, err);
        CHECK(o.size() == 2);  // untouched
    }
    CHECK_FALSE(load_input_log(temp_file("missing.txt"), out, err));
}

TEST_CASE("active feed registration") {
    PadFeed f;
    CHECK(active_pad_feed() == nullptr);
    set_active_pad_feed(&f);
    CHECK(active_pad_feed() == &f);
    set_active_pad_feed(nullptr);
    CHECK(active_pad_feed() == nullptr);
}
