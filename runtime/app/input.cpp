#include "input.h"

#include "p3fes/state_io.h"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <fstream>
#include <iterator>
#include <sstream>
#include <system_error>

namespace p3fes::app {

namespace pb = hle::sif::pad_button;

namespace {

// ---- small text helpers ----

std::string_view trim(std::string_view s) {
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r' || s.front() == '\n')) s.remove_prefix(1);
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '\n')) s.remove_suffix(1);
    return s;
}

std::string upper(std::string_view s) {
    std::string o(s);
    for (char& c : o)
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
    return o;
}

std::string lower(std::string_view s) {
    std::string o(s);
    for (char& c : o)
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
    return o;
}

// Splits on `sep`, keeping empty pieces.
std::vector<std::string_view> split(std::string_view s, char sep) {
    std::vector<std::string_view> out;
    std::size_t pos = 0;
    for (;;) {
        const std::size_t e = s.find(sep, pos);
        out.push_back(s.substr(pos, e == std::string_view::npos ? std::string_view::npos : e - pos));
        if (e == std::string_view::npos) break;
        pos = e + 1;
    }
    return out;
}

std::vector<std::string_view> lines_of(std::string_view text) { return split(text, '\n'); }

// Whole-string unsigned parse: decimal, or hexadecimal with a 0x prefix.
bool parse_uint(std::string_view s, std::uint64_t& out) {
    s = trim(s);
    int base = 10;
    if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        base = 16;
        s.remove_prefix(2);
    }
    if (s.empty()) return false;
    const auto r = std::from_chars(s.data(), s.data() + s.size(), out, base);
    return r.ec == std::errc{} && r.ptr == s.data() + s.size();
}

// Whole-string hexadecimal without prefix (log fields), at most `max_digits` digits.
bool parse_hex(std::string_view s, std::size_t max_digits, std::uint64_t& out) {
    if (s.empty() || s.size() > max_digits) return false;
    const auto r = std::from_chars(s.data(), s.data() + s.size(), out, 16);
    return r.ec == std::errc{} && r.ptr == s.data() + s.size();
}

bool parse_double(std::string_view s, double& out) {
    s = trim(s);
    if (s.empty()) return false;
    const auto r = std::from_chars(s.data(), s.data() + s.size(), out);
    return r.ec == std::errc{} && r.ptr == s.data() + s.size();
}

std::string format_double(double v) {
    char b[64];
    const auto r = std::to_chars(b, b + sizeof b, v);  // shortest round-trip form
    return std::string(b, r.ptr);
}

std::string line_error(std::size_t line, const std::string& what) { return "line " + std::to_string(line) + ": " + what; }

// ---- tables ----

struct ControlInfo {
    std::string_view name;
    std::uint16_t button;
};
constexpr std::array<ControlInfo, kPadControlCount> kControls = {{
    {"up", pb::kUp},
    {"down", pb::kDown},
    {"left", pb::kLeft},
    {"right", pb::kRight},
    {"triangle", pb::kTriangle},
    {"circle", pb::kCircle},
    {"cross", pb::kCross},
    {"square", pb::kSquare},
    {"l1", pb::kL1},
    {"l2", pb::kL2},
    {"r1", pb::kR1},
    {"r2", pb::kR2},
    {"l3", pb::kL3},
    {"r3", pb::kR3},
    {"start", pb::kStart},
    {"select", pb::kSelect},
    {"lstick_up", 0},
    {"lstick_down", 0},
    {"lstick_left", 0},
    {"lstick_right", 0},
    {"rstick_up", 0},
    {"rstick_down", 0},
    {"rstick_left", 0},
    {"rstick_right", 0},
}};

struct KeyInfo {
    std::string_view name;
    std::uint8_t vk;
};
// Canonical names first; RETURN and ESC are accepted spellings of ENTER and ESCAPE.
constexpr KeyInfo kNamedKeys[] = {
    {"BACKSPACE", 0x08}, {"TAB", 0x09},      {"ENTER", 0x0D},     {"SHIFT", 0x10},     {"CTRL", 0x11},
    {"ALT", 0x12},       {"PAUSE", 0x13},    {"CAPSLOCK", 0x14},  {"ESCAPE", 0x1B},    {"SPACE", 0x20},
    {"PAGEUP", 0x21},    {"PAGEDOWN", 0x22}, {"END", 0x23},       {"HOME", 0x24},      {"LEFT", 0x25},
    {"UP", 0x26},        {"RIGHT", 0x27},    {"DOWN", 0x28},      {"INSERT", 0x2D},    {"DELETE", 0x2E},
    {"NUMPAD_MULTIPLY", 0x6A}, {"NUMPAD_ADD", 0x6B}, {"NUMPAD_SUBTRACT", 0x6D}, {"NUMPAD_DECIMAL", 0x6E},
    {"NUMPAD_DIVIDE", 0x6F},   {"LSHIFT", 0xA0},     {"RSHIFT", 0xA1},          {"LCTRL", 0xA2},
    {"RCTRL", 0xA3},     {"LALT", 0xA4},     {"RALT", 0xA5},      {"SEMICOLON", 0xBA}, {"EQUALS", 0xBB},
    {"COMMA", 0xBC},     {"MINUS", 0xBD},    {"PERIOD", 0xBE},    {"SLASH", 0xBF},     {"GRAVE", 0xC0},
    {"LBRACKET", 0xDB},  {"BACKSLASH", 0xDC}, {"RBRACKET", 0xDD}, {"APOSTROPHE", 0xDE},
    {"RETURN", 0x0D},    {"ESC", 0x1B},
};

bool parse_key_list(std::string_view value, std::vector<std::uint8_t>& out, std::string& error) {
    out.clear();
    value = trim(value);
    if (value.empty()) return true;  // unbound
    for (std::string_view part : split(value, ',')) {
        part = trim(part);
        const int vk = key_from_name(part);
        if (vk < 0) {
            error = "unknown key '" + std::string(part) + "'";
            return false;
        }
        if (std::find(out.begin(), out.end(), static_cast<std::uint8_t>(vk)) == out.end()) out.push_back(static_cast<std::uint8_t>(vk));
    }
    return true;
}

bool parse_single_key(std::string_view value, std::uint8_t& out, std::string& error) {
    value = trim(value);
    if (value.empty()) {
        out = 0;  // disabled
        return true;
    }
    const int vk = key_from_name(value);
    if (vk < 0) {
        error = "unknown key '" + std::string(value) + "'";
        return false;
    }
    out = static_cast<std::uint8_t>(vk);
    return true;
}

// One "V", "BUTTONS", "N" triple of a script entry.
bool parse_script_entry(std::string_view vblank, std::string_view names, std::string_view frames, bool has_frames,
                        std::vector<ScriptPress>& out, std::string& error) {
    ScriptPress p;
    if (!parse_uint(vblank, p.vblank)) {
        error = "bad vblank '" + std::string(trim(vblank)) + "'";
        return false;
    }
    if (has_frames && (!parse_uint(frames, p.frames) || p.frames == 0)) {
        error = "bad frame count '" + std::string(trim(frames)) + "' (want >= 1)";
        return false;
    }
    bool any = false;
    for (std::string_view tok : split(names, '+')) {
        tok = trim(tok);
        if (tok.empty()) continue;
        const std::size_t eq = tok.find('=');
        if (eq != std::string_view::npos) {
            const std::string axis = lower(trim(tok.substr(0, eq)));
            std::uint64_t v = 0;
            if (!parse_uint(tok.substr(eq + 1), v) || v > 0xFF) {
                error = "bad stick value '" + std::string(tok) + "' (want 0..255)";
                return false;
            }
            std::int16_t* slot = axis == "lx" ? &p.lx : axis == "ly" ? &p.ly : axis == "rx" ? &p.rx : axis == "ry" ? &p.ry : nullptr;
            if (!slot) {
                error = "unknown stick axis '" + axis + "' (want lx ly rx ry)";
                return false;
            }
            *slot = static_cast<std::int16_t>(v);
            any = true;
            continue;
        }
        const std::uint16_t b = button_from_name(tok);
        if (!b) {
            error = "unknown button '" + std::string(tok) + "'";
            return false;
        }
        p.buttons = static_cast<std::uint16_t>(p.buttons | b);
        any = true;
    }
    if (!any) {
        error = "entry at vblank " + std::to_string(p.vblank) + " presses nothing";
        return false;
    }
    out.push_back(p);
    return true;
}

bool read_file(const std::filesystem::path& path, std::string& text, std::string& error) {
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        error = "cannot open " + path.string();
        return false;
    }
    std::ostringstream ss;
    ss << f.rdbuf();
    text = ss.str();
    return true;
}

PadFeed* g_active_feed = nullptr;

} // namespace

// ---- controls and keys ----

std::string_view control_name(PadControl c) {
    const auto i = static_cast<std::size_t>(c);
    return i < kControls.size() ? kControls[i].name : std::string_view{};
}

std::uint16_t control_button(PadControl c) {
    const auto i = static_cast<std::size_t>(c);
    return i < kControls.size() ? kControls[i].button : 0;
}

std::uint16_t button_from_name(std::string_view name) {
    const std::string n = lower(trim(name));
    for (const ControlInfo& c : kControls)
        if (c.button && c.name == n) return c.button;
    return 0;
}

int key_from_name(std::string_view name) {
    const std::string n = upper(trim(name));
    if (n.size() == 1 && ((n[0] >= 'A' && n[0] <= 'Z') || (n[0] >= '0' && n[0] <= '9'))) return n[0];  // VK_A.. = 'A'..
    if (n.size() >= 2 && n.size() <= 3 && n[0] == 'F') {
        std::uint64_t f = 0;
        if (parse_uint(std::string_view(n).substr(1), f) && f >= 1 && f <= 24 && n[1] != '0') return 0x70 + static_cast<int>(f) - 1;
    }
    if (n.size() == 7 && n.rfind("NUMPAD", 0) == 0 && n[6] >= '0' && n[6] <= '9') return 0x60 + (n[6] - '0');
    for (const KeyInfo& k : kNamedKeys)
        if (k.name == n) return k.vk;
    return -1;
}

std::string key_name(int vk) {
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) return std::string(1, static_cast<char>(vk));
    if (vk >= 0x70 && vk <= 0x87) return "F" + std::to_string(vk - 0x70 + 1);
    if (vk >= 0x60 && vk <= 0x69) return "NUMPAD" + std::to_string(vk - 0x60);
    for (const KeyInfo& k : kNamedKeys)
        if (k.vk == vk) return std::string(k.name);
    char b[16];
    std::snprintf(b, sizeof b, "VK_0x%02X", static_cast<unsigned>(vk & 0xFF));
    return b;
}

// ---- configuration ----

InputConfig default_input_config() {
    InputConfig c;
    auto bind = [&c](PadControl ctl, std::initializer_list<std::uint8_t> vks) { c.keys[static_cast<std::size_t>(ctl)] = vks; };
    bind(PadControl::Up, {0x26});
    bind(PadControl::Down, {0x28});
    bind(PadControl::Left, {0x25});
    bind(PadControl::Right, {0x27});
    bind(PadControl::Triangle, {'I'});
    bind(PadControl::Circle, {'L'});
    bind(PadControl::Cross, {'K'});
    bind(PadControl::Square, {'J'});
    bind(PadControl::L1, {'Q'});
    bind(PadControl::L2, {'1'});
    bind(PadControl::R1, {'E'});
    bind(PadControl::R2, {'3'});
    bind(PadControl::L3, {'2'});
    bind(PadControl::R3, {'4'});
    bind(PadControl::Start, {0x0D});
    bind(PadControl::Select, {0x08});
    bind(PadControl::LStickUp, {'W'});
    bind(PadControl::LStickDown, {'S'});
    bind(PadControl::LStickLeft, {'A'});
    bind(PadControl::LStickRight, {'D'});
    bind(PadControl::RStickUp, {'T'});
    bind(PadControl::RStickDown, {'G'});
    bind(PadControl::RStickLeft, {'F'});
    bind(PadControl::RStickRight, {'H'});
    return c;
}

bool parse_input_config(std::string_view text, InputConfig& cfg, std::string& error) {
    InputConfig c = cfg;
    std::string section;
    std::size_t lineno = 0;
    for (std::string_view raw : lines_of(text)) {
        ++lineno;
        std::string_view line = raw;
        const std::size_t cmt = line.find_first_of("#;");
        if (cmt != std::string_view::npos) line = line.substr(0, cmt);
        line = trim(line);
        if (line.empty()) continue;
        if (line.front() == '[') {
            if (line.back() != ']') {
                error = line_error(lineno, "bad section header '" + std::string(line) + "'");
                return false;
            }
            section = lower(trim(line.substr(1, line.size() - 2)));
            if (section != "keyboard" && section != "gamepad" && section != "hotkeys") {
                error = line_error(lineno, "unknown section [" + section + "] (want keyboard, gamepad, hotkeys)");
                return false;
            }
            continue;
        }
        const std::size_t eq = line.find('=');
        if (eq == std::string_view::npos) {
            error = line_error(lineno, "expected 'name = value'");
            return false;
        }
        const std::string key = lower(trim(line.substr(0, eq)));
        const std::string_view value = trim(line.substr(eq + 1));
        std::string why;
        if (section.empty()) {
            error = line_error(lineno, "'" + key + "' outside a section");
            return false;
        } else if (section == "keyboard") {
            std::size_t idx = kControls.size();
            for (std::size_t i = 0; i < kControls.size(); ++i)
                if (kControls[i].name == key) idx = i;
            if (idx == kControls.size()) {
                error = line_error(lineno, "unknown control '" + key + "'");
                return false;
            }
            if (!parse_key_list(value, c.keys[idx], why)) {
                error = line_error(lineno, why);
                return false;
            }
        } else if (section == "gamepad") {
            if (key == "index") {
                std::uint64_t v = 0;
                if (lower(value) == "auto") c.gamepad_index = -1;
                else if (parse_uint(value, v) && v <= 3) c.gamepad_index = static_cast<int>(v);
                else {
                    error = line_error(lineno, "index must be auto or 0..3");
                    return false;
                }
            } else if (key == "deadzone_left" || key == "deadzone_right") {
                double d = 0;
                if (!parse_double(value, d) || !(d >= 0.0 && d <= 0.95)) {
                    error = line_error(lineno, key + " must be a fraction in 0..0.95");
                    return false;
                }
                (key == "deadzone_left" ? c.deadzone_left : c.deadzone_right) = d;
            } else if (key == "trigger_threshold") {
                std::uint64_t v = 0;
                if (!parse_uint(value, v) || v > 255) {
                    error = line_error(lineno, "trigger_threshold must be 0..255");
                    return false;
                }
                c.trigger_threshold = static_cast<std::uint8_t>(v);
            } else {
                error = line_error(lineno, "unknown [gamepad] setting '" + key + "'");
                return false;
            }
        } else {  // hotkeys
            std::uint8_t* slot = key == "screenshot" ? &c.screenshot_key : key == "fullscreen" ? &c.fullscreen_key : nullptr;
            if (!slot) {
                error = line_error(lineno, "unknown hotkey '" + key + "' (want screenshot, fullscreen)");
                return false;
            }
            if (!parse_single_key(value, *slot, why)) {
                error = line_error(lineno, why);
                return false;
            }
        }
    }
    cfg = c;
    return true;
}

bool load_input_config(const std::filesystem::path& path, InputConfig& cfg, bool missing_ok, std::string& error) {
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) {
        if (missing_ok) return true;
        error = path.string() + ": no such file";
        return false;
    }
    std::string text;
    if (!read_file(path, text, error)) return false;
    std::string why;
    if (!parse_input_config(text, cfg, why)) {
        error = path.string() + ": " + why;
        return false;
    }
    return true;
}

std::string format_input_config(const InputConfig& cfg) {
    std::string o = "[keyboard]\n";
    for (std::size_t i = 0; i < kControls.size(); ++i) {
        o += std::string(kControls[i].name) + " =";
        for (std::size_t k = 0; k < cfg.keys[i].size(); ++k) o += (k ? ", " : " ") + key_name(cfg.keys[i][k]);
        o += "\n";
    }
    o += "\n[gamepad]\nindex = " + (cfg.gamepad_index < 0 ? std::string("auto") : std::to_string(cfg.gamepad_index)) + "\n";
    o += "deadzone_left = " + format_double(cfg.deadzone_left) + "\n";
    o += "deadzone_right = " + format_double(cfg.deadzone_right) + "\n";
    o += "trigger_threshold = " + std::to_string(cfg.trigger_threshold) + "\n";
    o += "\n[hotkeys]\nscreenshot =" + (cfg.screenshot_key ? " " + key_name(cfg.screenshot_key) : std::string()) + "\n";
    o += "fullscreen =" + (cfg.fullscreen_key ? " " + key_name(cfg.fullscreen_key) : std::string()) + "\n";
    return o;
}

bool same_config(const InputConfig& a, const InputConfig& b) {
    return a.keys == b.keys && a.gamepad_index == b.gamepad_index && a.deadzone_left == b.deadzone_left &&
           a.deadzone_right == b.deadzone_right && a.trigger_threshold == b.trigger_threshold &&
           a.screenshot_key == b.screenshot_key && a.fullscreen_key == b.fullscreen_key;
}

// ---- mapping ----

PadInput map_keyboard(const InputConfig& cfg, const KeyState& held) {
    auto down = [&](PadControl c) {
        for (std::uint8_t vk : cfg.keys[static_cast<std::size_t>(c)])
            if (held.test(vk)) return true;
        return false;
    };
    PadInput p;
    for (std::size_t i = 0; i < kControls.size(); ++i)
        if (kControls[i].button && down(static_cast<PadControl>(i))) p.buttons = static_cast<std::uint16_t>(p.buttons | kControls[i].button);
    auto axis = [&](PadControl neg, PadControl pos) -> std::uint8_t {
        const bool n = down(neg), q = down(pos);
        if (n == q) return 0x80;
        return n ? 0x00 : 0xFF;
    };
    p.lx = axis(PadControl::LStickLeft, PadControl::LStickRight);
    p.ly = axis(PadControl::LStickUp, PadControl::LStickDown);
    p.rx = axis(PadControl::RStickLeft, PadControl::RStickRight);
    p.ry = axis(PadControl::RStickUp, PadControl::RStickDown);
    return p;
}

StickXY apply_radial_deadzone(std::int16_t x, std::int16_t y, double deadzone) {
    const double fx = std::clamp(static_cast<double>(x) / 32767.0, -1.0, 1.0);
    const double fy = std::clamp(static_cast<double>(y) / 32767.0, -1.0, 1.0);
    const double m = std::sqrt(fx * fx + fy * fy);
    if (m <= deadzone || m == 0.0) return {};
    const double dz = std::clamp(deadzone, 0.0, 0.95);
    const double k = (std::min(m, 1.0) - dz) / (1.0 - dz);
    return {fx / m * k, fy / m * k};
}

std::uint8_t axis_to_byte(double v) {
    v = std::clamp(v, -1.0, 1.0);
    const double r = v < 0.0 ? 128.0 + v * 128.0 : 128.0 + v * 127.0;
    return static_cast<std::uint8_t>(std::clamp(std::floor(r + 0.5), 0.0, 255.0));
}

PadInput map_gamepad(const InputConfig& cfg, const GamepadState& g) {
    PadInput p;
    if (!g.connected) return p;
    namespace xb = xinput_button;
    static constexpr std::pair<std::uint16_t, std::uint16_t> kMap[] = {
        {xb::kDpadUp, pb::kUp},          {xb::kDpadDown, pb::kDown},    {xb::kDpadLeft, pb::kLeft},
        {xb::kDpadRight, pb::kRight},    {xb::kStart, pb::kStart},      {xb::kBack, pb::kSelect},
        {xb::kLeftThumb, pb::kL3},       {xb::kRightThumb, pb::kR3},    {xb::kLeftShoulder, pb::kL1},
        {xb::kRightShoulder, pb::kR1},   {xb::kA, pb::kCross},          {xb::kB, pb::kCircle},
        {xb::kX, pb::kSquare},           {xb::kY, pb::kTriangle},
    };
    for (const auto& [x, b] : kMap)
        if (g.buttons & x) p.buttons = static_cast<std::uint16_t>(p.buttons | b);
    if (g.left_trigger > cfg.trigger_threshold) p.buttons = static_cast<std::uint16_t>(p.buttons | pb::kL2);
    if (g.right_trigger > cfg.trigger_threshold) p.buttons = static_cast<std::uint16_t>(p.buttons | pb::kR2);
    const StickXY l = apply_radial_deadzone(g.lx, g.ly, cfg.deadzone_left);
    const StickXY r = apply_radial_deadzone(g.rx, g.ry, cfg.deadzone_right);
    p.lx = axis_to_byte(l.x);
    p.ly = axis_to_byte(-l.y);
    p.rx = axis_to_byte(r.x);
    p.ry = axis_to_byte(-r.y);
    return p;
}

PadInput merge_inputs(const PadInput& keyboard, const PadInput& gamepad) {
    PadInput o = gamepad;
    o.connected = true;
    o.buttons = static_cast<std::uint16_t>(keyboard.buttons | gamepad.buttons);
    if (keyboard.lx != 0x80 || keyboard.ly != 0x80) {
        o.lx = keyboard.lx;
        o.ly = keyboard.ly;
    }
    if (keyboard.rx != 0x80 || keyboard.ry != 0x80) {
        o.rx = keyboard.rx;
        o.ry = keyboard.ry;
    }
    return o;
}

bool same_pad(const PadInput& a, const PadInput& b) {
    return a.connected == b.connected && a.buttons == b.buttons && a.lx == b.lx && a.ly == b.ly && a.rx == b.rx && a.ry == b.ry;
}

// ---- scripts and logs ----

bool parse_input_script(std::string_view text, std::vector<ScriptPress>& out, std::string& error) {
    for (std::string_view item : split(text, ',')) {
        item = trim(item);
        if (item.empty()) continue;
        const std::size_t c1 = item.find(':');
        if (c1 == std::string_view::npos) {
            error = "input script entry '" + std::string(item) + "' needs VBLANK:BUTTONS[:FRAMES]";
            return false;
        }
        const std::size_t c2 = item.find(':', c1 + 1);
        const std::string_view names = item.substr(c1 + 1, c2 == std::string_view::npos ? std::string_view::npos : c2 - c1 - 1);
        const std::string_view frames = c2 == std::string_view::npos ? std::string_view{} : item.substr(c2 + 1);
        std::string why;
        if (!parse_script_entry(item.substr(0, c1), names, frames, c2 != std::string_view::npos, out, why)) {
            error = "input script entry '" + std::string(item) + "': " + why;
            return false;
        }
    }
    return true;
}

bool parse_press(std::string_view text, std::vector<ScriptPress>& out, std::string& error) {
    text = trim(text);
    const std::size_t at = text.find('@');
    if (at == std::string_view::npos) {
        error = "--press '" + std::string(text) + "' needs BUTTONS@VBLANK[:FRAMES]";
        return false;
    }
    const std::string_view rest = text.substr(at + 1);
    const std::size_t c = rest.find(':');
    std::string why;
    if (!parse_script_entry(rest.substr(0, c), text.substr(0, at), c == std::string_view::npos ? std::string_view{} : rest.substr(c + 1),
                            c != std::string_view::npos, out, why)) {
        error = "--press '" + std::string(text) + "': " + why;
        return false;
    }
    return true;
}

bool parse_input_log(std::string_view text, std::vector<InputEvent>& out, std::string& error) {
    std::vector<InputEvent> events;
    std::size_t lineno = 0;
    for (std::string_view raw : lines_of(text)) {
        ++lineno;
        const std::string_view line = trim(raw);
        if (line.empty() || line.front() == '#') continue;
        std::vector<std::string_view> f;
        for (std::string_view t : split(line, ' '))
            if (!trim(t).empty()) f.push_back(trim(t));
        if (f.size() != 6) {
            error = line_error(lineno, "expected 'VBLANK BUTTONS LX LY RX RY', got " + std::to_string(f.size()) + " fields");
            return false;
        }
        InputEvent e;
        std::uint64_t v[5] = {};
        const bool ok = parse_uint(f[0], e.vblank) && f[0].find('x') == std::string_view::npos && f[0].find('X') == std::string_view::npos &&
                        parse_hex(f[1], 4, v[0]) && parse_hex(f[2], 2, v[1]) && parse_hex(f[3], 2, v[2]) &&
                        parse_hex(f[4], 2, v[3]) && parse_hex(f[5], 2, v[4]);
        if (!ok) {
            error = line_error(lineno, "bad field in '" + std::string(line) + "' (decimal vblank, hex buttons/sticks)");
            return false;
        }
        if (!events.empty() && e.vblank <= events.back().vblank) {
            error = line_error(lineno, "vblank " + std::to_string(e.vblank) + " does not increase");
            return false;
        }
        e.pad.buttons = static_cast<std::uint16_t>(v[0]);
        e.pad.lx = static_cast<std::uint8_t>(v[1]);
        e.pad.ly = static_cast<std::uint8_t>(v[2]);
        e.pad.rx = static_cast<std::uint8_t>(v[3]);
        e.pad.ry = static_cast<std::uint8_t>(v[4]);
        events.push_back(e);
    }
    out = std::move(events);
    return true;
}

bool load_input_log(const std::filesystem::path& path, std::vector<InputEvent>& out, std::string& error) {
    std::string text;
    if (!read_file(path, text, error)) return false;
    std::string why;
    if (!parse_input_log(text, out, why)) {
        error = path.string() + ": " + why;
        return false;
    }
    return true;
}

std::string format_input_event(const InputEvent& e) {
    char b[96];
    std::snprintf(b, sizeof b, "%llu %04X %02X %02X %02X %02X", static_cast<unsigned long long>(e.vblank), e.pad.buttons, e.pad.lx,
                  e.pad.ly, e.pad.rx, e.pad.ry);
    return b;
}

// ---- PadFeed ----

PadFeed::~PadFeed() { close_record(); }

void PadFeed::add_script(const std::vector<ScriptPress>& presses) { script_.insert(script_.end(), presses.begin(), presses.end()); }

void PadFeed::set_replay(std::vector<InputEvent> events) {
    replay_ = std::move(events);
    replay_set_ = true;
}

bool PadFeed::open_record(const std::filesystem::path& path, std::string& error) {
    close_record();
    std::error_code ec;
    if (path.has_parent_path()) std::filesystem::create_directories(path.parent_path(), ec);
    record_ = std::fopen(path.string().c_str(), "wb");
    if (!record_) {
        error = "cannot create " + path.string();
        return false;
    }
    if (std::fwrite(kInputLogHeader.data(), 1, kInputLogHeader.size(), record_) != kInputLogHeader.size() || std::fflush(record_) != 0)
        record_failed_ = true;
    written_any_ = false;
    return true;
}

void PadFeed::close_record() {
    if (!record_) return;
    if (std::fclose(record_) != 0) record_failed_ = true;
    record_ = nullptr;
}

PadInput PadFeed::compute(std::uint64_t vblank) const {
    PadInput p = live_;
    if (replay_set_) {
        p = PadInput{};
        const auto it = std::upper_bound(replay_.begin(), replay_.end(), vblank,
                                         [](std::uint64_t v, const InputEvent& e) { return v < e.vblank; });
        if (it != replay_.begin()) p = std::prev(it)->pad;
    }
    for (const ScriptPress& s : script_) {
        if (vblank < s.vblank || vblank - s.vblank >= s.frames) continue;
        p.buttons = static_cast<std::uint16_t>(p.buttons | s.buttons);
        if (s.lx >= 0) p.lx = static_cast<std::uint8_t>(s.lx);
        if (s.ly >= 0) p.ly = static_cast<std::uint8_t>(s.ly);
        if (s.rx >= 0) p.rx = static_cast<std::uint8_t>(s.rx);
        if (s.ry >= 0) p.ry = static_cast<std::uint8_t>(s.ry);
    }
    p.connected = true;
    return p;
}

bool PadFeed::latch(std::uint64_t vblank) {
    if (have_latch_ && vblank == latched_vblank_) return false;
    const PadInput next = compute(vblank);
    if (!have_latch_ || !same_pad(next, current_)) ++changes_;
    have_latch_ = true;
    latched_vblank_ = vblank;
    current_ = next;
    ++latches_;
    if (record_ && (!written_any_ || !same_pad(next, last_written_))) {
        const std::string line = format_input_event({vblank, next}) + "\n";
        if (std::fwrite(line.data(), 1, line.size(), record_) != line.size() || std::fflush(record_) != 0) record_failed_ = true;
        last_written_ = next;
        written_any_ = true;
    }
    return true;
}

// ---- the host hook ----

void PadFeed::state(StateIo& io) {
    io.section("pad-feed");
    io(live_, script_, replay_, replay_set_, have_latch_, latched_vblank_, current_, last_written_, written_any_);
    io(latches_, changes_);
}

void feed_pad_input(std::uint64_t vblank, hle::sif::IopHle& iop) {
    if (g_active_feed && g_active_feed->latch(vblank)) iop.set_pad_input(0, g_active_feed->current());
}

void set_active_pad_feed(PadFeed* feed) { g_active_feed = feed; }

PadFeed* active_pad_feed() { return g_active_feed; }

} // namespace p3fes::app
