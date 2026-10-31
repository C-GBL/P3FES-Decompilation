// Modernize pass, stage 0: the native-layer switch set and the scene log line (modernize.h).
#include "modernize.h"

#include <array>
#include <cctype>
#include <cstdio>
#include <cstdlib>

namespace p3fes::app {

namespace {

constexpr std::array<NativeLayer, kNativeLayerCount> kAll = {NativeLayer::Files,  NativeLayer::Input,
                                                            NativeLayer::Sound,  NativeLayer::Movies,
                                                            NativeLayer::Graphics, NativeLayer::Kernel};

std::string lower_trim(std::string_view s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.remove_suffix(1);
    std::string out(s);
    for (char& c : out) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return out;
}

}  // namespace

const char* to_string(NativeLayer l) {
    switch (l) {
    case NativeLayer::Files: return "files";
    case NativeLayer::Input: return "input";
    case NativeLayer::Sound: return "sound";
    case NativeLayer::Movies: return "movies";
    case NativeLayer::Graphics: return "graphics";
    case NativeLayer::Kernel: return "kernel";
    }
    return "?";
}

bool NativeLayers::on(NativeLayer l) const {
    switch (l) {
    case NativeLayer::Files: return files;
    case NativeLayer::Input: return input;
    case NativeLayer::Sound: return sound;
    case NativeLayer::Movies: return movies;
    case NativeLayer::Graphics: return graphics;
    case NativeLayer::Kernel: return kernel;
    }
    return false;
}

void NativeLayers::set(NativeLayer l, bool v) {
    switch (l) {
    case NativeLayer::Files: files = v; break;
    case NativeLayer::Input: input = v; break;
    case NativeLayer::Sound: sound = v; break;
    case NativeLayer::Movies: movies = v; break;
    case NativeLayer::Graphics: graphics = v; break;
    case NativeLayer::Kernel: kernel = v; break;
    }
}

bool NativeLayers::any() const { return files || input || sound || movies || graphics || kernel; }

std::vector<NativeLayer> NativeLayers::enabled() const {
    std::vector<NativeLayer> v;
    for (NativeLayer l : kAll)
        if (on(l)) v.push_back(l);
    return v;
}

std::string NativeLayers::to_string() const {
    std::string s;
    for (NativeLayer l : enabled()) {
        if (!s.empty()) s += ',';
        s += app::to_string(l);
    }
    return s.empty() ? "none" : s;
}

bool parse_native_layers(std::string_view list, NativeLayers& out, std::string& error) {
    NativeLayers n;
    const std::string whole = lower_trim(list);
    if (whole.empty()) {
        error = "--native wants a comma-separated list of layers (files, input, sound, movies, graphics, kernel), all "
                "or none";
        return false;
    }
    if (whole == "none") {
        out = n;
        return true;
    }
    if (whole == "all") {
        for (NativeLayer l : kAll) n.set(l, true);
        out = n;
        return true;
    }
    std::size_t pos = 0;
    while (pos <= list.size()) {
        const std::size_t comma = list.find(',', pos);
        const std::string item = lower_trim(list.substr(pos, comma == std::string_view::npos ? std::string_view::npos : comma - pos));
        if (item.empty()) {
            error = "--native: empty layer name in '" + std::string(list) + "'";
            return false;
        }
        bool known = false;
        for (NativeLayer l : kAll)
            if (item == to_string(l)) {
                n.set(l, true);
                known = true;
            }
        if (!known) {
            error = "--native: unknown layer '" + item +
                    "' (files, input, sound, movies, graphics, kernel; or all / none alone)";
            return false;
        }
        if (comma == std::string_view::npos) break;
        pos = comma + 1;
    }
    out = n;
    return true;
}

// Layer 1 (files) since 2026-10-30: runtime/native/files, p3fes/native/files_service.h. Layer 2 (input) since
// 2026-10-30: runtime/native/input, p3fes/native/input_service.h. Layer 3 (sound) since 2026-10-30, step 1 (the ADX
// output): runtime/native/sound, p3fes/native/sound_service.h.
// Layer 4 (movies) since 2026-10-30: runtime/native/movies, p3fes/native/movies_service.h. Layer 5 (graphics) since
// 2026-10-31, step 1 (RW Im2D): runtime/native/graphics, p3fes/native/graphics_service.h. Layer 6 (kernel) since
// 2026-10-31, step 1 (the (a) set): runtime/native/kernel, p3fes/native/kernel_service.h. Every layer has one now.
bool native_layer_implemented(NativeLayer l) {
    return l == NativeLayer::Files || l == NativeLayer::Input || l == NativeLayer::Sound || l == NativeLayer::Movies ||
           l == NativeLayer::Graphics || l == NativeLayer::Kernel;
}

bool parse_vblank_dump_ranges(std::string_view text, DumpRanges& out, std::string& error) {
    out.clear();
    const std::string s(text);
    std::size_t at = 0;
    while (at <= s.size()) {
        const std::size_t comma = s.find(',', at);
        const std::string item = s.substr(at, comma == std::string::npos ? std::string::npos : comma - at);
        const std::size_t plus = item.find('+');
        char* end = nullptr;
        const unsigned long long va = plus == std::string::npos ? 0 : std::strtoull(item.c_str(), &end, 0);
        const bool va_ok = plus != std::string::npos && end == item.c_str() + plus;
        const unsigned long long len = va_ok ? std::strtoull(item.c_str() + plus + 1, &end, 0) : 0;
        if (!va_ok || end != item.c_str() + item.size() || plus + 1 == item.size() || len == 0 ||
            va + len > 0x2000000ull) {
            error = "--vblank-dump: bad range '" + item + "' (want VA+LEN inside main RAM, e.g. 0x7E0700+0x340)";
            return false;
        }
        out.emplace_back(static_cast<std::uint32_t>(va), static_cast<std::uint32_t>(len));
        if (comma == std::string::npos) break;
        at = comma + 1;
    }
    return true;
}

std::size_t vblank_dump_bytes(const DumpRanges& r) {
    std::size_t n = 0;
    for (const auto& x : r) n += x.second;
    return n;
}

std::string format_vblank_dump_header(const DumpRanges& r) {
    std::string h = "# p3fes vblank dump v1: ";
    char buf[48];
    for (std::size_t i = 0; i < r.size(); ++i) {
        std::snprintf(buf, sizeof buf, "%s0x%X+%u", i ? "," : "", r[i].first, r[i].second);
        h += buf;
    }
    return h;
}

std::vector<std::string> native_layer_notices(const NativeLayers& n) {
    std::vector<std::string> v;
    for (NativeLayer l : n.enabled())
        if (!native_layer_implemented(l))
            v.push_back(std::string("p3fes: --native: layer ") + to_string(l) +
                        " has no native implementation yet; running faithful");
    return v;
}

const char* to_string(SceneKind k) {
    switch (k) {
    case SceneKind::None: return "none";
    case SceneKind::Field: return "field";
    case SceneKind::Event: return "event";
    case SceneKind::Battle: return "battle";
    case SceneKind::Movie: return "movie";
    }
    return "?";
}

std::string format_scene_log_line(std::uint64_t vblank, const SceneSample& s) {
    char buf[160];
    char entry[16];
    if (s.entry >= 0) std::snprintf(entry, sizeof entry, "%d", s.entry);
    else std::snprintf(entry, sizeof entry, "-");
    int n = std::snprintf(buf, sizeof buf, "%llu major=%d minor=%d entry=%s kind=%s", static_cast<unsigned long long>(vblank),
                          s.major, s.minor, entry, to_string(s.kind));
    if (s.kind == SceneKind::Event && n > 0 && static_cast<std::size_t>(n) < sizeof buf)
        std::snprintf(buf + n, sizeof buf - static_cast<std::size_t>(n), " event=%d", s.event);
    return buf;
}

}  // namespace p3fes::app
