// Modernize pass, stage 0 (runtime/app/modernize.h): --native parsing and formatting, the stage-0 notices, the scene
// sampler over a fake guest RAM, and the scene-log line.
#include <doctest.h>

#include <cstdint>
#include <map>
#include <string>

#include "modernize.h"

using namespace p3fes::app;

TEST_CASE("modernize: --native accepts layer lists, all and none") {
    NativeLayers n;
    std::string err;
    REQUIRE(parse_native_layers("files", n, err));
    CHECK(n.files);
    CHECK_FALSE(n.input);
    CHECK(n.to_string() == "files");

    REQUIRE(parse_native_layers("Sound, files,INPUT,files", n, err));  // any order, case, spaces, repeats
    CHECK(n.files);
    CHECK(n.input);
    CHECK(n.sound);
    CHECK_FALSE(n.movies);
    CHECK(n.to_string() == "files,input,sound");  // fixed layer order

    REQUIRE(parse_native_layers("all", n, err));
    CHECK(n.to_string() == "files,input,sound,movies,graphics,kernel");
    CHECK(n.enabled().size() == kNativeLayerCount);

    REQUIRE(parse_native_layers("none", n, err));
    CHECK_FALSE(n.any());
    CHECK(n.to_string() == "none");
    CHECK(n == NativeLayers{});

    // to_string round-trips through the parser
    NativeLayers m;
    m.movies = m.kernel = true;
    NativeLayers back;
    REQUIRE(parse_native_layers(m.to_string(), back, err));
    CHECK(back == m);
}

TEST_CASE("modernize: --native refuses unknown names, empty items and all / none inside a list") {
    NativeLayers n;
    n.graphics = true;  // untouched on failure
    std::string err;
    for (const char* bad : {"", " ", "file", "files,audio", "files,", ",files", "files,,input", "files,all", "none,sound",
                            "gpu"}) {
        CAPTURE(bad);
        err.clear();
        CHECK_FALSE(parse_native_layers(bad, n, err));
        CHECK_FALSE(err.empty());
    }
    CHECK(n.graphics);
    CHECK_FALSE(n.files);
    CHECK(err.find("unknown layer 'gpu'") != std::string::npos);
}

TEST_CASE("modernize: every layer (files, input, sound, movies, graphics, kernel) has a native implementation; no notices") {
    for (std::size_t i = 0; i < kNativeLayerCount; ++i) CHECK(native_layer_implemented(static_cast<NativeLayer>(i)));
    CHECK(native_layer_notices(NativeLayers{}).empty());
    NativeLayers n;
    n.files = n.input = n.graphics = n.sound = n.movies = n.kernel = true;
    CHECK(native_layer_notices(n).empty());
}

namespace {
struct FakeRam {
    std::map<std::uint32_t, std::uint32_t> words;
    std::uint32_t operator()(std::uint32_t va) const {
        auto it = words.find(va);
        return it == words.end() ? 0u : it->second;
    }
};
}  // namespace

TEST_CASE("modernize: the scene sampler reads the scene record, the field root, gBtl and the movie player") {
    using namespace scene_addr;
    FakeRam ram;
    CHECK(sample_scene(ram) == SceneSample{});  // nothing set up yet: -1 / -1, no root, none

    ram.words[kSceneRecordPtr] = 0x95AFC0u;
    ram.words[0x95AFC0u] = 32;
    ram.words[0x95AFC4u] = 2;
    SceneSample s = sample_scene(ram);
    CHECK(s.major == 32);
    CHECK(s.minor == 2);
    CHECK(s.entry == -1);
    CHECK(s.kind == SceneKind::Field);

    const std::uint32_t task = 0x1023F20u, work = 0x1024000u;
    ram.words[kFieldRootSlot] = task;
    ram.words[task + kTaskWork] = work;
    ram.words[work + kRootEntry] = 0xABCD0003u;  // u16 entry 3; the next u16 is not part of it
    s = sample_scene(ram);
    CHECK(s.entry == 3);
    CHECK(s.kind == SceneKind::Field);

    ram.words[work + kRootEventViewer] = 0x1030000u;
    ram.words[work + kRootEvent] = 139;
    s = sample_scene(ram);
    CHECK(s.kind == SceneKind::Event);
    CHECK(s.event == 139);

    ram.words[kMovieObject] = 0x1100000u;  // movie beats event
    s = sample_scene(ram);
    CHECK(s.kind == SceneKind::Movie);
    CHECK(s.event == -1);

    ram.words[kBattle] = 0x1200000u;  // battle beats both
    CHECK(sample_scene(ram).kind == SceneKind::Battle);

    ram.words[0x95AFC0u] = static_cast<std::uint32_t>(-1);
    ram.words[kBattle] = ram.words[kMovieObject] = ram.words[work + kRootEventViewer] = 0;
    CHECK(sample_scene(ram).kind == SceneKind::None);
}

TEST_CASE("modernize: scene log line format") {
    SceneSample s;
    CHECK(format_scene_log_line(0, s) == "0 major=-1 minor=-1 entry=- kind=none");
    s.major = 51;
    s.minor = 1;
    s.entry = 0;
    s.kind = SceneKind::Field;
    CHECK(format_scene_log_line(2631, s) == "2631 major=51 minor=1 entry=0 kind=field");
    s.kind = SceneKind::Event;
    s.event = 139;
    CHECK(format_scene_log_line(3000, s) == "3000 major=51 minor=1 entry=0 kind=event event=139");
    s.kind = SceneKind::Battle;
    CHECK(format_scene_log_line(4700, s) == "4700 major=51 minor=1 entry=0 kind=battle");
    CHECK(kSceneLogHeader.front() == '#');
}

TEST_CASE("modernize: --vblank-dump ranges and header") {
    DumpRanges r;
    std::string err;
    REQUIRE(parse_vblank_dump_ranges("0x7E0700+0x340,0x822DD0+1624", r, err));
    REQUIRE(r.size() == 2);
    CHECK(r[0] == std::pair<std::uint32_t, std::uint32_t>{0x7E0700u, 0x340u});
    CHECK(r[1] == std::pair<std::uint32_t, std::uint32_t>{0x822DD0u, 1624u});
    CHECK(vblank_dump_bytes(r) == 0x340u + 1624u);
    CHECK(format_vblank_dump_header(r) == "# p3fes vblank dump v1: 0x7E0700+832,0x822DD0+1624");
    for (const char* bad : {"", "0x100", "0x100+", "+4", "0x100+0", "0x100+4,", "0x1FFFFFF+2", "x+4", "0x100+4z"}) {
        INFO(bad);
        CHECK_FALSE(parse_vblank_dump_ranges(bad, r, err));
        CHECK(err.find("--vblank-dump") != std::string::npos);
    }
}
