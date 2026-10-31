// Modernize pass, stage 0 (docs/MODERNIZE_PLAN.md, ADR-0017): the native-layer switch set and the scene log.
//
// NativeLayers is HostConfig::native, set by `--native <list>`. Each layer will have a faithful mode (the code that
// runs now) and a native mode (runtime/native/<layer>/), chosen at the game's own wrapper by `if (native.files)`.
// Layer 1 (files) is implemented (runtime/native/files, p3fes/native/files_service.h: the game's CD wrappers read
// host files by path and complete at once), and layer 2 (input: runtime/native/input, p3fes/native/input_service.h:
// the game's pad wrapper asks the host's pad instead of libpad / PADMAN), and layer 3 step 1 (sound: runtime/native/sound,
// p3fes/native/sound_service.h: CRI's PS2 ADX output plays on the host), and layer 4 (movies: runtime/native/movies,
// p3fes/native/movies_service.h: the movie player's video decodes on the host instead of libmpeg + the IPU), layer 5
// (graphics: runtime/native/graphics) and layer 6 step 1 (kernel: runtime/native/kernel, p3fes/native/kernel_service.h:
// the game's kernel calls go to the host kernel directly). Every
// other layer that is switched on is reported once at start ("layer X
// has no native implementation yet; running faithful") and changes nothing else -- except that machine states and
// capture.json record the set (" native=files,..."), as they record `mods=` (ADR-0016). With the set empty
// (the default, `--native none`) the program is the baseline build byte for byte (the replay gates prove it).
//
// The scene log (`--scene-log FILE`, one line per change, sampled at VBLANK_START; never writes guest memory):
//   <vblank> major=<s32> minor=<s32> entry=<u16 | -> kind=<none|field|event|battle|movie> [event=<id>]
// major / minor: MT_Scene's record (*(0x7CD540) = 0x95AFC0: +0 s32 major, +4 s32 minor; -1 = none);
// entry: the field root work's u16 +20 (sField 0x869F60 +0 -> the root task, its work at task +60), "-" without a
// root; kind: battle while gBtl (*0x7CE3EC) is set, else movie while the movie task's Sofdec player (*0x7CDF10) is
// set, else event while the field root's event viewer task (work +60) runs (event= the PM file id, work +12), else
// field when a scene is loaded (major >= 0), else none. Layer 1's check (c) compares the order of these lines,
// not their vblanks (tools/ours/modernize/logcmp.py).
#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace p3fes::app {

enum class NativeLayer : std::uint8_t { Files, Input, Sound, Movies, Graphics, Kernel };
inline constexpr std::size_t kNativeLayerCount = 6;
const char* to_string(NativeLayer l);  // "files", "input", ...

struct NativeLayers {
    bool files = false, input = false, sound = false, movies = false, graphics = false, kernel = false;

    bool on(NativeLayer l) const;
    void set(NativeLayer l, bool v);
    bool any() const;
    std::vector<NativeLayer> enabled() const;
    // "files,sound" in the fixed layer order, "none" when empty (the form --native accepts back).
    std::string to_string() const;
    bool operator==(const NativeLayers&) const = default;
};

// --native: a comma-separated list of layer names (any order, case-insensitive, repeats allowed), or "all", or
// "none". An empty list, an empty item or an unknown name is refused (`error` says which).
bool parse_native_layers(std::string_view list, NativeLayers& out, std::string& error);

// true for the layers with a native implementation (files, input, sound, movies); each later layer flips its own entry.
bool native_layer_implemented(NativeLayer l);

// The start-up notice for each switched-on layer without an implementation (empty when there is none).
std::vector<std::string> native_layer_notices(const NativeLayers& n);

// ---- Vblank dump (layer 2's check) ----------------------------------------------------------------------------
// `--vblank-dump FILE RANGES`: at every VBLANK_START the bytes of the guest ranges RANGES ("VA+LEN[,VA+LEN...]", C
// integer syntax, e.g. "0x7E0700+0x340,0x822DD0+0x658"; main RAM only) are appended to FILE as one record: the
// vblank as u64 little-endian, then each range's bytes in order. The file starts with one text line, the header.
// Read through EEMemory::ram_ptr: nothing the guest sees changes. tools/ours/modernize/logcmp.py `dumps A B`
// compares two of them record by record.
using DumpRanges = std::vector<std::pair<std::uint32_t, std::uint32_t>>;  // (va, bytes)
bool parse_vblank_dump_ranges(std::string_view text, DumpRanges& out, std::string& error);
std::size_t vblank_dump_bytes(const DumpRanges& r);  // per record, the vblank excluded
// "# p3fes vblank dump v1: 0x7E0700+832,0x822DD0+1624" (no newline)
std::string format_vblank_dump_header(const DumpRanges& r);

// ---- Scene log ------------------------------------------------------------------------------------------------
enum class SceneKind : std::uint8_t { None, Field, Event, Battle, Movie };
const char* to_string(SceneKind k);

struct SceneSample {
    std::int32_t major = -1, minor = -1;
    std::int32_t entry = -1;  // -1 = no field root
    std::int32_t event = -1;  // the PM file id while kind == Event
    SceneKind kind = SceneKind::None;
    bool operator==(const SceneSample&) const = default;
};

// Reads the scene from guest RAM through `read_u32` (a pure reader: main RAM only, 0 elsewhere).
template <typename ReadU32>
SceneSample sample_scene(ReadU32&& read_u32);

inline constexpr std::string_view kSceneLogHeader =
    "# p3fes scene log v1: vblank major= minor= entry= kind= [event=] (docs/MODERNIZE_PLAN.md section 3)";
std::string format_scene_log_line(std::uint64_t vblank, const SceneSample& s);  // without the newline

// ---- guest addresses (game/include/p3fes/game: scene.h, field.h / field4.h, battle3.h; game_host.cpp markers) ----
namespace scene_addr {
inline constexpr std::uint32_t kSceneRecordPtr = 0x7CD540u;  // gp-0x57B0 -> MT_Scene's record (0x95AFC0)
inline constexpr std::uint32_t kFieldRootSlot = 0x869F60u;   // sField +0: the field root task (NULL outside a field)
inline constexpr std::uint32_t kTaskWork = 60;               // KwlnTask +0x3C: the task's work
inline constexpr std::uint32_t kRootEvent = 12;              // root work +12: the event PM file id (sequence 3)
inline constexpr std::uint32_t kRootEntry = 20;              // root work +20: u16 the entry point
inline constexpr std::uint32_t kRootEventViewer = 60;        // root work +60: the event viewer task
inline constexpr std::uint32_t kBattle = 0x7CE3ECu;          // gBtl
inline constexpr std::uint32_t kMovieObject = 0x7CDF10u;     // the movie task's Sofdec player
}  // namespace scene_addr

template <typename ReadU32>
SceneSample sample_scene(ReadU32&& read_u32) {
    using namespace scene_addr;
    SceneSample s;
    if (const std::uint32_t rec = read_u32(kSceneRecordPtr)) {
        s.major = static_cast<std::int32_t>(read_u32(rec));
        s.minor = static_cast<std::int32_t>(read_u32(rec + 4));
    }
    std::uint32_t work = 0;
    if (const std::uint32_t root = read_u32(kFieldRootSlot)) work = read_u32(root + kTaskWork);
    if (work) s.entry = static_cast<std::int32_t>(read_u32(work + kRootEntry) & 0xFFFFu);
    if (read_u32(kBattle)) s.kind = SceneKind::Battle;
    else if (read_u32(kMovieObject)) s.kind = SceneKind::Movie;
    else if (work && read_u32(work + kRootEventViewer)) s.kind = SceneKind::Event;
    else if (s.major >= 0 && read_u32(kSceneRecordPtr)) s.kind = SceneKind::Field;
    if (s.kind == SceneKind::Event) s.event = static_cast<std::int32_t>(read_u32(work + kRootEvent));
    return s;
}

}  // namespace p3fes::app
