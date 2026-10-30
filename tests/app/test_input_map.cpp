// Keyboard mapping and config/input.ini (runtime/app/input.h).
#include <doctest.h>

#include <set>
#include <string>

#include "input.h"

using namespace p3fes::app;
namespace pb = p3fes::hle::sif::pad_button;

namespace {

PadInput keys(std::initializer_list<int> vks, const InputConfig& c = default_input_config()) {
    KeyState k;
    for (int vk : vks) k.set(static_cast<std::size_t>(vk));
    return map_keyboard(c, k);
}

bool centred(const PadInput& p) { return p.lx == 0x80 && p.ly == 0x80 && p.rx == 0x80 && p.ry == 0x80; }

} // namespace

TEST_CASE("key names: letters, digits, F-keys, numpad and named keys; every named key round-trips") {
    CHECK(key_from_name("A") == 'A');
    CHECK(key_from_name("k") == 'K');
    CHECK(key_from_name("7") == '7');
    CHECK(key_from_name("F1") == 0x70);
    CHECK(key_from_name("f12") == 0x7B);
    CHECK(key_from_name("F24") == 0x87);
    CHECK(key_from_name("F25") == -1);
    CHECK(key_from_name("F0") == -1);
    CHECK(key_from_name("F01") == -1);
    CHECK(key_from_name("NUMPAD5") == 0x65);
    CHECK(key_from_name("enter") == 0x0D);
    CHECK(key_from_name("RETURN") == 0x0D);
    CHECK(key_from_name("Esc") == 0x1B);
    CHECK(key_from_name(" Up ") == 0x26);
    CHECK(key_from_name("BACKSPACE") == 0x08);
    CHECK(key_from_name("nope") == -1);
    CHECK(key_from_name("") == -1);
    CHECK(key_name(0x0D) == "ENTER");
    CHECK(key_name(0x1B) == "ESCAPE");
    CHECK(key_name(0x07) == "VK_0x07");
    int named = 0;
    for (int vk = 0; vk < 256; ++vk) {
        const std::string n = key_name(vk);
        if (n.rfind("VK_0x", 0) == 0) continue;
        ++named;
        CHECK_MESSAGE(key_from_name(n) == vk, n);
    }
    CHECK(named == 26 + 10 + 24 + 10 + 42);
}

TEST_CASE("default map: one distinct key per control, 16 buttons covering the libpad mask, hotkeys apart") {
    const InputConfig c = default_input_config();
    std::set<int> seen;
    std::uint16_t all = 0;
    int buttons = 0;
    for (std::size_t i = 0; i < kPadControlCount; ++i) {
        REQUIRE(c.keys[i].size() == 1);
        seen.insert(c.keys[i][0]);
        const std::uint16_t b = control_button(static_cast<PadControl>(i));
        CHECK((all & b) == 0);
        all = static_cast<std::uint16_t>(all | b);
        buttons += b != 0;
    }
    CHECK(seen.size() == kPadControlCount);
    CHECK(all == 0xFFFF);
    CHECK(buttons == 16);
    CHECK(seen.count(c.screenshot_key) == 0);
    CHECK(seen.count(c.fullscreen_key) == 0);
    CHECK(c.screenshot_key == 0x7B);
    CHECK(c.fullscreen_key == 0x7A);
}

TEST_CASE("map_keyboard: each default key presses exactly its DUALSHOCK 2 button") {
    const struct {
        int vk;
        std::uint16_t bit;
    } cases[] = {
        {0x26, pb::kUp},  {0x28, pb::kDown}, {0x25, pb::kLeft}, {0x27, pb::kRight}, {'I', pb::kTriangle}, {'L', pb::kCircle},
        {'K', pb::kCross}, {'J', pb::kSquare}, {'Q', pb::kL1},  {'1', pb::kL2},     {'E', pb::kR1},       {'3', pb::kR2},
        {'2', pb::kL3},   {'4', pb::kR3},    {0x0D, pb::kStart}, {0x08, pb::kSelect},
    };
    for (const auto& t : cases) {
        const PadInput p = keys({t.vk});
        CHECK_MESSAGE(p.buttons == t.bit, key_name(t.vk));
        CHECK(centred(p));
        CHECK(p.connected);
    }
    CHECK(keys({'K', 0x0D, 0x26}).buttons == (pb::kCross | pb::kStart | pb::kUp));
    const PadInput none = keys({});
    CHECK(none.buttons == 0);
    CHECK(centred(none));
    CHECK(keys({'Z', 0x20}).buttons == 0);  // unmapped keys
}

TEST_CASE("map_keyboard: stick directions go to full deflection, opposite keys cancel") {
    CHECK(keys({'W'}).ly == 0x00);
    CHECK(keys({'S'}).ly == 0xFF);
    CHECK(keys({'A'}).lx == 0x00);
    CHECK(keys({'D'}).lx == 0xFF);
    CHECK(keys({'A', 'D'}).lx == 0x80);
    CHECK(keys({'W', 'S'}).ly == 0x80);
    const PadInput diag = keys({'W', 'D'});
    CHECK(diag.lx == 0xFF);
    CHECK(diag.ly == 0x00);
    CHECK(diag.rx == 0x80);
    CHECK(diag.ry == 0x80);
    CHECK(diag.buttons == 0);
    const PadInput r = keys({'T', 'F'});
    CHECK(r.rx == 0x00);
    CHECK(r.ry == 0x00);
    CHECK(keys({'G', 'H'}).ry == 0xFF);
    CHECK(keys({'G', 'H'}).rx == 0xFF);
}

TEST_CASE("input.ini: overrides, several keys per control, unbinding, gamepad and hotkey settings") {
    InputConfig c = default_input_config();
    std::string err;
    REQUIRE(parse_input_config("# comment\r\n[keyboard]\r\ncross = SPACE, k ; two keys\r\ncircle =\r\n\r\n[gamepad]\r\n"
                               "index = 2\r\ndeadzone_left = 0.1\r\ntrigger_threshold = 0x40\r\n[hotkeys]\r\n"
                               "screenshot = F9\r\nfullscreen =\r\n",
                               c, err));
    CHECK(c.keys[static_cast<std::size_t>(PadControl::Cross)] == std::vector<std::uint8_t>{0x20, 'K'});
    CHECK(c.keys[static_cast<std::size_t>(PadControl::Circle)].empty());
    CHECK(c.keys[static_cast<std::size_t>(PadControl::Square)] == std::vector<std::uint8_t>{'J'});
    CHECK(c.gamepad_index == 2);
    CHECK(c.deadzone_left == doctest::Approx(0.1));
    CHECK(c.deadzone_right == doctest::Approx(0.265));
    CHECK(c.trigger_threshold == 64);
    CHECK(c.screenshot_key == 0x78);
    CHECK(c.fullscreen_key == 0);
    CHECK(keys({0x20}, c).buttons == pb::kCross);
    CHECK(keys({'K'}, c).buttons == pb::kCross);
    CHECK(keys({'L'}, c).buttons == 0);
    InputConfig auto_idx = c;
    REQUIRE(parse_input_config("[gamepad]\nindex = auto\n", auto_idx, err));
    CHECK(auto_idx.gamepad_index == -1);
}

TEST_CASE("input.ini: errors name the line and leave the configuration untouched") {
    const struct {
        const char* text;
        const char* where;
    } bad[] = {
        {"[keyboard]\nfoo = A\n", "line 2"},          {"cross = A\n", "line 1"},
        {"[mouse]\n", "line 1"},                      {"[keyboard]\ncross = NOPE\n", "line 2"},
        {"[gamepad]\ndeadzone_left = 0.99\n", "line 2"}, {"[gamepad]\nindex = 4\n", "line 2"},
        {"[gamepad]\ntrigger_threshold = 256\n", "line 2"}, {"[keyboard]\n\ncross\n", "line 3"},
        {"[hotkeys]\nmenu = F1\n", "line 2"},         {"[keyboard\n", "line 1"},
        {"[gamepad]\ndeadzone_right = x\n", "line 2"}, {"[hotkeys]\nscreenshot = F1, F2\n", "line 2"},
    };
    for (const auto& t : bad) {
        InputConfig c = default_input_config();
        std::string err;
        CHECK_FALSE_MESSAGE(parse_input_config(t.text, c, err), t.text);
        CHECK_MESSAGE(err.rfind(t.where, 0) == 0, err);
        CHECK(same_config(c, default_input_config()));
    }
}

TEST_CASE("format_input_config round-trips through parse_input_config") {
    InputConfig blank;  // every control unbound
    std::string err;
    REQUIRE(parse_input_config(format_input_config(default_input_config()), blank, err));
    CHECK(same_config(blank, default_input_config()));

    InputConfig m = default_input_config();
    m.keys[static_cast<std::size_t>(PadControl::Start)] = {0x0D, 0x20, 0x70};
    m.keys[static_cast<std::size_t>(PadControl::L3)].clear();
    m.gamepad_index = 1;
    m.deadzone_left = 0.3125;
    m.deadzone_right = 0.0;
    m.trigger_threshold = 0;
    m.screenshot_key = 0;
    InputConfig back = default_input_config();
    REQUIRE(parse_input_config(format_input_config(m), back, err));
    CHECK(same_config(back, m));
}

TEST_CASE("the shipped config/input.ini sets every value to the built-in map") {
    // Poisoned start: if the file left anything out, the comparison fails.
    InputConfig c;
    c.gamepad_index = 3;
    c.deadzone_left = c.deadzone_right = 0.5;
    c.trigger_threshold = 1;
    c.screenshot_key = c.fullscreen_key = 0;
    std::string err;
    REQUIRE_MESSAGE(load_input_config(P3FES_SOURCE_DIR "/config/input.ini", c, /*missing_ok=*/false, err), err);
    CHECK(same_config(c, default_input_config()));
    // A missing optional file leaves the configuration as it was; a missing explicit one is an error.
    InputConfig d = default_input_config();
    CHECK(load_input_config(P3FES_SOURCE_DIR "/config/no_such_input.ini", d, true, err));
    CHECK(same_config(d, default_input_config()));
    CHECK_FALSE(load_input_config(P3FES_SOURCE_DIR "/config/no_such_input.ini", d, false, err));
}

TEST_CASE("button names (scripts) are the 16 buttons only") {
    CHECK(button_from_name("Start") == pb::kStart);
    CHECK(button_from_name("select") == pb::kSelect);
    CHECK(button_from_name("CROSS") == pb::kCross);
    CHECK(button_from_name("r3") == pb::kR3);
    CHECK(button_from_name("lstick_up") == 0);
    CHECK(button_from_name("x") == 0);
    CHECK(control_name(PadControl::RStickRight) == "rstick_right");
}
