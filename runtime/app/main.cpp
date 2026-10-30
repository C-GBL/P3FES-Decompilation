// p3fes host executable.
//
// Game mode (the default when the recompiled program is linked, P3FES_HAVE_PROGRAM): composes the runtime
// (runtime/app/game_host.h: kernel + GS + SIF/IOP + rt hooks + recompiled program), loads the verified ELF and
// runs `start` (0x100008). Windowed, it stops the guest at every VBLANK_START, presents the composed CRTC picture
// whenever the GS flipped (host_display.h), paces virtual time to the wall clock (present.h) and samples the
// keyboard / XInput pad once per vblank into the pad feed (input.h), which hands it to PADMAN at the next VBLANK_START;
// --headless runs without a window as fast as possible (ADR-0013 §4). The IOP's CRI_ADXI mix plays through XAudio2
// when windowed (HostAudio on this file's XAudio2Backend engine; --dump-wav DIR writes it as WAV in either mode), and
// --memcard picks the card in MEMORY CARD slot 1 (default: PCSX2's). Scripted (--input-script / --press) and
// replayed (--replay-input) input are functions of the vblank index, so a headless replay of a --record-input log
// reproduces the recorded run.
//
// Self-test mode (--smoke, --selftest, or any run of a build without the program): the GS draws its synthetic
// scene through GIF PATH3 (runtime/include/p3fes/gs/gs_selftest.h); --smoke presents it through D3D11 + XAudio2
// for three frames and exits 0.
#include <windows.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "frame_overlay.h"
#include "hfr_d3d11.h"
#include "frame_pacing.h"
#include "frame_telemetry.h"
#include "host_display.h"
#include "host_timing.h"
#include "input.h"
#include "input_win32.h"
#include "p3fes/audio/spu2_backend.h"
#include "p3fes/audio/xaudio2_sink.h"
#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/gs/gs_d3d11.h"
#include "p3fes/gs/gs_output.h"
#include "p3fes/gs/gs_selftest.h"
#include "p3fes/gs/gs_system.h"
#include "p3fes/vu1/vu1_aot.h"
#include "p3fes/vu1/vu1_profile.h"
#include "present.h"

#if defined(P3FES_HAVE_PROGRAM)
#include "game_host.h"
#include "host_crash.h"
#include "host_profile.h"
#endif
#include "p3fes/prof.h"
#if defined(P3FES_HAVE_PROGRAM)
#include "p3fes/rt/rt_adapter.h"  // --reference-mode
#endif
#include "p3fes/state_io.h"

namespace {

using p3fes::app::DisplayOptions;
using p3fes::app::HostDisplay;
using p3fes::app::InputConfig;
using p3fes::app::ScriptPress;

constexpr wchar_t kWindowTitle[] = L"Persona 3 FES (native port)";
constexpr char kDefaultInputConfig[] = "config/input.ini";

// Window, presentation and input options (shared by the game and the self-test where they apply).
struct HostOptions {
    DisplayOptions display;
    bool screenshot_key_set = false;  // --screenshot overrides [hotkeys] screenshot
    bool stats = false;
    bool background_input = false;
    std::string input_config;  // --input-config (default: config/input.ini when present)
    std::string record, replay;
    std::vector<ScriptPress> script;
    InputConfig input = p3fes::app::default_input_config();
    std::string input_source = "built-in";
};

double wall_now() {
    static const double freq = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return static_cast<double>(f.QuadPart);
    }();
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return static_cast<double>(t.QuadPart) / freq;
}

std::string keyboard_map_summary(const InputConfig& c) {
    std::string o;
    for (std::size_t i = 0; i < p3fes::app::kPadControlCount; ++i) {
        o += (i ? (i % 8 == 0 ? "\n    " : "  ") : "    ");
        o += std::string(p3fes::app::control_name(static_cast<p3fes::app::PadControl>(i))) + "=";
        if (c.keys[i].empty()) o += "-";
        for (std::size_t k = 0; k < c.keys[i].size(); ++k) o += (k ? "," : "") + p3fes::app::key_name(c.keys[i][k]);
    }
    return o;
}

void print_usage() {
    std::puts(
        "usage: p3fes [game options] [window/input options] | --smoke | --selftest [--headless] [--png PATH]\n"
        "game (needs a build with the recompiled program, -DP3FES_RECOMP_GENERATED=ON):\n"
        "  --iso PATH            the user's disc image (default input\\persona3fes.iso)\n"
        "  --extracted DIR       serve the disc from extracted volumes (extracted\\disc) instead of the ISO\n"
        "  --mods DIR            mods overlay (ADR-0016): files under DIR (DATA\\FIELD\\X.PAC, BTL\\..., BGM\\...) replace\n"
        "                        those disc files without touching the ISO; DIR is one mod or a folder of mods;\n"
        "                        repeatable, later ones win per file; every applied file is logged. Off by default\n"
        "  --elf PATH            SLUS_216.21 (default extracted\\disc\\SLUS_216.21; SHA-256 checked)\n"
        "  --symbols PATH        symbols\\p3fes.sym for diagnostics (default; optional)\n"
        "  --headless            no window/D3D11/audio device; run as fast as possible\n"
        "  --memcard SPEC        MEMORY CARD slot 1 (docs\\ANALYSIS\\17_memory_card.md): default = PCSX2's slot-1 card\n"
        "                        from tools\\third_party\\pcsx2\\inis\\PCSX2.ini, read-only with copy-on-write into\n"
        "                        extracted\\_ours\\memcards\\; without one, the port's own card\n"
        "                        %APPDATA%\\P3FES\\saves\\Mcd001.ps2 (created formatted on first use); appdata | pcsx2 |\n"
        "                        PATH (raw 8 MiB image) | new (formatted in memory) | blank (erased) | none\n"
        "  --pc-text on|off      the memory-card messages in PC wording (\"Checking save data...\"; runtime\\app\\pc_text.h):\n"
        "                        default on windowed, off with --headless (it changes guest memory; the replay gates\n"
        "                        compare it)\n"
        "  --dump-wav DIR        write the CRI_ADXI mix to DIR\\mix_48k.wav and every ADX stream the IOP consumed\n"
        "                        to DIR\\stream_*.wav (suggested: extracted\\_ours\\wav); off by default\n"
        "  --frames N            stop after N vblanks (fields, 59.94/s)\n"
        "  --until-flip N        stop when the GS flip counter reaches N (SkyStart's PutDispEnv is flip 1)\n"
        "  --until-cycles N      stop at N virtual EE cycles\n"
        "  --until-sky N         stop at the first VBLANK_START with g_skyFrameCount >= N\n"
        "  --snapshot-at K:N DIR dump eeMemory.bin + frame.png + capture.json into DIR when K (flip | vblank |\n"
        "                        cycles | sky) reaches N; repeatable; the run ends after the last one unless\n"
        "                        a later --until/--frames is given\n"
        "  --save-state-at K:N FILE  save the whole machine (runtime\\STATE.md) to FILE when K (flip | vblank | cycles\n"
        "                        | sky) reaches N; repeatable; ends the run like --snapshot-at\n"
        "  --reference-mode      run every replaced function (game\\replaced.txt) as its recompiled original: the\n"
        "                        zero-replacement program; with --load-state it applies from the loaded point on\n"
        "  --load-state FILE     resume a saved machine instead of booting (same p3fes.exe, ELF and --sk/--iop-layout/\n"
        "                        --spu2-interp/disc kind; give --memcard if the saver had a card: its image is replaced;\n"
        "                        the state's pad replay is used unless --replay-input names another log)\n"
        "  --png PATH            write the composed frame at the end\n"
        "  --trace-syscalls N    log the first N calls of each syscall number\n"
        "  --trace-hw N          log the first N guest accesses per hardware register and direction\n"
        "  --trace-sif           log every SIF bind/call/command (IopConfig::trace)\n"
        "  --sound-log FILE      write every sound-side RPC (SDRDRV/SK blocks, CRI DTX) to FILE, one line each:\n"
        "                        vblank, cycles, server, function, verb, payload words, reply; plus KON/KOFF of\n"
        "                        the SPU2 voice model and RNA start/stop of the ADX model\n"
        "  --sk MODE             who answers the SK sound RPCs (ADR-0014): modules (default: the game's SDRDRV/SK IRX\n"
        "                        files interpreted in place, SFX audible) | constants (the silent increment-1 replies)\n"
        "  --iop-layout L        IOP memory map: pcsx2 (default: module images and the game's IOP heap where PCSX2\n"
        "                        puts them) | legacy (the map of every snapshot before SK increment 2)\n"
        "  --spu2-interp I       SPU2 voice interpolation: gaussian (default: the hardware's 4-tap table) | linear\n"
        "                        (SK increment 2's form, for A/B)\n"
        "  --trace-gs A-B        log every GS placement-register write (TEX0/TEX2, FRAME, ZBUF, BITBLTBUF, TRXPOS,\n"
        "                        TRXREG, TRXDIR) with its GIF path while the vblank count is in [A, B]\n"
        "  --gs-backend B        software | d3d11 | auto (default): who rasterises the GS in windowed play; auto = d3d11\n"
        "                        when the GPU has what it needs (feature level 11_0, ROVs), else software. Headless runs\n"
        "                        use software (the oracle) unless given --gs-backend d3d11 --gs-exact: an offscreen GPU\n"
        "                        in exact mode, snapshots byte-identical to software (falls back without ROVs/doubles)\n"
        "  --gs-exact            d3d11: per-pixel exact attribute evaluation (doubles; bit-identical to software, slower)\n"
        "  --gpu-debug           d3d11: the D3D11 debug device (Graphics Tools), its errors/warnings on stderr\n"
        "  --renderer R          windowed d3d11 play: emulated (default: every draw through VU1 + the GS front end) |\n"
        "                        native (RenderWare's g3 batches drawn without VU1/GIF, visually equivalent, the EE\n"
        "                        state unchanged; docs\\ANALYSIS\\31) | native-generic | native-skin | native-diff (exact\n"
        "                        drawing, the native model checked against every VU1 packet) | native-verify (native,\n"
        "                        every 16th batch run exactly on the native VU state and checked). Headless: ignored\n"
        "  --native-capture DIR EVERY MAX  with a native renderer mode: save every EVERY-th g3 batch input (at most\n"
        "                        MAX) for p3fes_native_check\n"
        "  --unpaced             windowed: do not pace virtual time to the wall clock (speed measurements)\n"
        "  --gs-threads N        graphics pipeline (docs\\ANALYSIS\\32): VU1 work and the GS front end on worker threads\n"
        "                        behind the EE, guest-visible behaviour unchanged: 2 (default: a VU1 worker and a GS\n"
        "                        worker) | 1 (one worker) | 0 (the command stream on the EE thread, no threads) | off\n"
        "                        (the synchronous model). Off with --gs-census/--gs-record/--trace-gs/--vu1-stats\n"
        "  --gs-batch-kb N       graphics pipeline hand-off size in KiB (default 32)\n"
        "  --gs-speculate        graphics pipeline: GS CSR reads do not wait for VU1 work (NOT the exact default: the\n"
        "                        run stops if a VU1 packet ever writes SIGNAL/FINISH/LABEL, which no route does)\n"
        "  --pacing MODE         windowed frame pacing (docs\\ANALYSIS\\31): display (default: one guest vblank = k display\n"
        "                        refreshes when the refresh is a multiple of 59.94 Hz, else clock) | clock (real time\n"
        "                        on the QPC) | legacy (the pre-2026-10-25 loop: presents every vblank, 0.25 s catch-up)\n"
        "  --display-rate R      windowed d3d11: game (default: one present per guest frame) | refresh (a present every\n"
        "                        display refresh) | HZ (that many a second) | uncapped -- the display rate decoupled from\n"
        "                        the game's 30 fps (game logic unchanged; the frames between come from a display hook,\n"
        "                        else the newest guest frame is shown again)\n"
        "  --fps F               windowed d3d11, play: 30 (default: the game's own rate, exactly as without this switch) |\n"
        "                        60 | 120 | HZ | monitor (every display refresh) | unlimited -- the display rate, with\n"
        "                        interpolated pictures between the game's 30 fps frames (docs\\ANALYSIS\\32; the game logic\n"
        "                        stays at 30 fps). Shorthand for --display-rate + --hfr on\n"
        "  --hfr on|off          interpolated pictures under a --display-rate other than game (default on)\n"
        "  --hfr-latency L       normal (default: the presenter holds the next game frame, +1 game frame of delay) | low\n"
        "                        (F's adaptive delay; extrapolates up to half a frame when the next one is not there)\n"
        "  --hfr-steps K         in-between pictures at 1/K steps (default: automatic from the display rate; 1 = none)\n"
        "  --hfr-dump DIR        diagnostics: every --hfr-dump-every N-th game frame (default 30, at most --hfr-dump-max M,\n"
        "                        default 20, from flip --hfr-dump-from F) write frame A, the in-between picture and\n"
        "                        frame B (replayed and as latched)\n"
        "  --hfr-test-replay     diagnostics: in-between pictures also without native batches (frame B replayed as is)\n"
        "  --present-delay-ms N  timed presents: a frame is presented N ms after the end of the vblank slice that\n"
        "                        flipped it (default: one vblank + the render thread's recent p90, adaptive, so a\n"
        "                        frame that fits 33.4 ms is on time; a given N is fixed)\n"
        "  --frame-log FILE      windowed: one CSV row per guest frame (host work, CPU time, zones, present interval,\n"
        "                        display refreshes, lateness, events); the summary is printed at exit either way\n"
        "  --frame-overlay       windowed: show the frame-time overlay from the start (F3 toggles it)\n"
        "  --frame-stats off     windowed: no frame-time telemetry (and no zone profiler for it)\n"
        "  --wall-marks V1,...   print the wall time and flip count when the vblank count reaches each mark\n"
        "  --gs-census FILE      per-draw GS feature census (PRIM, FRAME/ZBUF, TEST, ALPHA, TEX0/TEX1/CLAMP, uploads,\n"
        "                        readbacks, privileged-register reads, raster time), bucketed by --gs-census-marks\n"
        "                        V1,V2,... (vblank segment starts); diagnostics only (docs\\ANALYSIS\\25)\n"
        "  --gs-record FILE      record the GS command stream of one frame (first flip at vblank >= --gs-record-at N\n"
        "                        to the next flip) with the start/end GS state; replay: p3fes_gsreplay FILE\n"
        "  --profile FILE        sample the host thread's instruction pointer (default every 1000 us, --profile-us N)\n"
        "                        and report the hottest functions (needs a PDB: BUILDING.md \"Profiling\");\n"
        "                        --profile-from N starts sampling at vblank N\n"
        "  --zones FILE          zone profiler: host wall time per subsystem (EE code, kernel, fibers, DMAC, VIF1,\n"
        "                        VU1, GIF, GS raster/upload, IPU, IOP, R3000, audio, CDVD) and workload counters per\n"
        "                        segment of --zones-every N vblanks (default 50), written to FILE as TSV at exit\n"
        "                        (BUILDING.md \"Profiling\"; tools\\ours\\perf\\zones_report.py folds segments)\n"
        "  --vu1 MODE            VU1 engine: interp (the interpreter, the oracle) | aot (the ahead-of-time compiled\n"
        "                        programs, exact; the default in builds with P3FES_VU1_AOT, where the interpreter\n"
        "                        takes any other image) | diff (both on every run, compared; the interpreter's result\n"
        "                        is used)\n"
        "  --vu1-stats FILE      VU1 workload per resident program and start pc (runs, pairs, kicks, wall time) to\n"
        "                        FILE; --vu1-stats-at V1,V2,... closes an interval at each vblank; programs are\n"
        "                        named from the dumps in P3FES_VU1_DUMPS (default ida\\logs\\vu1, vu1_dump.py)\n"
        "  --vu1-capture DIR N   with --vu1-stats: from the second-to-last --vu1-stats-at mark, save the input state\n"
        "                        of the first N runs of every (program, start pc) to DIR (differential tests)\n"
        "  --quiet               drop guest _print / IOP chatter\n"
        "  --watch-write VA[+LEN] N  log the first N writes to guest RAM [VA, VA+LEN) with the guest call chain\n"
        "input (pad port 0; a change is handed to PADMAN at a VBLANK_START and is in its next frame):\n"
        "  --input-config PATH   keyboard/gamepad map (default config\\input.ini when present, else built-in)\n"
        "  --record-input FILE   write one line per change of the pad state: vblank buttons lx ly rx ry\n"
        "  --replay-input FILE   feed a recorded log back (no keyboard/gamepad polling; works --headless)\n"
        "  --input-script S      scripted presses \"V:BUTTONS[:N],...\" (the former P3FES_PAD_SCRIPT format, e.g.\n"
        "                        560:left:4,580:cross:4): BUTTONS '+'-joined from up down left right triangle circle\n"
        "                        cross square l1 l2 r1 r2 l3 r3 start select and lx=B ly=B rx=B ry=B (0..255), held\n"
        "                        for the N (default 4) VBLANK_STARTs from V; repeatable\n"
        "  --press BUTTONS@V[:N] one scripted press (e.g. --press start@600); repeatable\n"
        "  --background-input    keep sampling the keyboard/gamepad while the window is not in the foreground\n"
        "window (ignored with --headless):\n"
        "  --fullscreen          borderless full screen (Alt+Enter / F11 toggle)\n"
        "  --vsync on|off        Present waits for the display's vblank (default on)\n"
        "  --scale fit|integer|smooth  4:3 fit point-sampled (default) | whole multiples of the frame height |\n"
        "                        4:3 fit bilinear\n"
        "  --stats               FPS / vblank rate / virtual time on the console and in the title, once a second\n"
        "  --screenshot KEY      screenshot hotkey (default F12): the shown frame to extracted\\_ours\\screens\\*.png\n"
        "self-test:\n"
        "  --smoke               initialise D3D11 + XAudio2, present a few GS self-test frames, exit 0\n"
        "  --selftest            run the GS self-test scene (with --headless: no window), exit 0\n"
        "  --help                show this message\n"
        "default keyboard map (config\\input.ini; any XInput pad works alongside it):");
    std::puts(keyboard_map_summary(p3fes::app::default_input_config()).c_str());
}

// ---- self-test (the GS synthetic scene) -------------------------------------------------------------------

int run_selftest(bool smoke, bool headless, int headless_frames, const char* png_path, const HostOptions& h) {
    p3fes::EEMemory memory;
    p3fes::EEContext cpu;
    cpu.memory = &memory;
    std::printf("p3fes: EE memory ready (%u MiB RAM, %u KiB scratchpad)\n",
                p3fes::EEMemory::kMainRamSize >> 20, p3fes::EEMemory::kScratchpadSize >> 10);

    // No bus is attached in the self-test; it drives GIF PATH3 directly.
    auto gs = std::make_unique<p3fes::gs::GsSystem>();
    const std::size_t qwords = p3fes::gs::run_selftest_scene(*gs);
    const p3fes::gs::Frame frame = gs->compose_output();
    std::printf("p3fes: GS self-test: %zu PATH3 qwords, %llu primitives, flips %llu, frame %ux%u, hash %016llX\n",
                qwords, static_cast<unsigned long long>(gs->core().stats().primitives),
                static_cast<unsigned long long>(gs->flip_count()), frame.width, frame.height,
                static_cast<unsigned long long>(p3fes::gs::frame_hash(frame)));
    if (png_path) {
        if (!p3fes::gs::write_png(png_path, frame)) {
            std::fprintf(stderr, "p3fes: cannot write %s\n", png_path);
            return 1;
        }
        std::printf("p3fes: wrote %s\n", png_path);
    }

    if (headless && !smoke) {
        p3fes::gs::Frame last = frame;
        for (int f = 1; f < headless_frames; ++f) last = gs->compose_output();
        std::printf("p3fes: headless OK (%d frames composed, %ux%u)\n", headless_frames, last.width, last.height);
        return frame.empty() ? 1 : 0;
    }

    HostDisplay display;
    std::string err;
    if (!display.open(h.display, kWindowTitle, err)) {
        std::fprintf(stderr, "p3fes: %s\n", err.c_str());
        return 1;
    }
    std::printf("p3fes: D3D11 device created (feature level 0x%04X, present shaders %s)\n",
                static_cast<unsigned>(display.backend().feature_level()), display.backend().shaders_ready() ? "ready" : "unavailable");
    display.screenshot_tag = [&gs] {
        char b[48];
        std::snprintf(b, sizeof b, "selftest_f%05llu", static_cast<unsigned long long>(gs->flip_count()));
        return std::string(b);
    };

    p3fes::audio::XAudio2Backend spu2;
    if (!spu2.init()) {
        std::fprintf(stderr, "p3fes: XAudio2 init failed (hr=0x%08lX)\n",
                     static_cast<unsigned long>(spu2.last_hresult()));
        return 1;
    }
    std::puts("p3fes: XAudio2 engine + mastering voice created");

    const int smoke_frames = 3;
    int frames = 0;
    p3fes::u64 presented_flip = ~0ull;
    while (display.pump()) {
        // Present whenever the GS flipped (ADR-0013 §4); otherwise re-present the last frame.
        if (gs->flip_count() != presented_flip) {
            presented_flip = gs->flip_count();
            display.show(gs->compose_output());
        } else {
            display.refresh();
        }
        ++frames;
        if (smoke && frames >= smoke_frames) break;
    }

    spu2.shutdown();
    display.close();
    if (smoke) std::printf("p3fes: smoke OK (%d frames presented)\n", frames);
    return 0;
}

#if defined(P3FES_HAVE_PROGRAM)

// ---- game mode -----------------------------------------------------------------------------------------------

using p3fes::app::StopPlan;
using p3fes::app::StopReason;

constexpr double kEeHz = 294912000.0;

struct SnapshotSpec {
    StopReason kind = StopReason::None;
    unsigned long long n = 0;
    std::string dir, label;  // dir: the state file for --save-state-at
    bool done = false;
    bool state = false;      // --save-state-at
};

bool parse_snapshot_spec(const char* spec, const char* dir, SnapshotSpec& out) {
    const char* colon = std::strchr(spec, ':');
    if (!colon) return false;
    const std::string k(spec, colon);
    char* end = nullptr;
    out.n = std::strtoull(colon + 1, &end, 0);
    if (!end || *end || out.n == 0) return false;
    if (k == "flip") out.kind = StopReason::Flip;
    else if (k == "vblank") out.kind = StopReason::Vblank;
    else if (k == "cycles") out.kind = StopReason::Cycles;
    else if (k == "sky") out.kind = StopReason::Sky;
    else return false;
    out.dir = dir;
    out.label = spec;
    return true;
}

bool spec_holds(const SnapshotSpec& s, p3fes::app::GameHost& host) {
    switch (s.kind) {
    case StopReason::Flip: return host.gs().flip_count() >= s.n;
    case StopReason::Vblank: return host.kernel().time().vblanks >= s.n;
    case StopReason::Cycles: return host.kernel().time().cycles >= s.n;
    case StopReason::Sky: return host.guest_u32(0x7CEA78u) >= s.n;
    default: return false;
    }
}

struct GameArgs {
    p3fes::app::HostConfig cfg;
    bool headless = false;
    unsigned long long frames = 0, until_flip = 0, until_cycles = 0, until_sky = 0;
    std::vector<SnapshotSpec> snaps;
    const char* png = nullptr;
    const char* profile = nullptr;  // --profile FILE (host_profile.h)
    unsigned profile_us = 1000;
    unsigned long long profile_from_vblank = 0;  // --profile-from N: start sampling at that vblank
    const char* zones = nullptr;  // --zones FILE (host_zones.h); segment length in cfg.zones_every
    // --vu1 interp|aot|diff; aot when the build has compiled programs (exact: docs/ANALYSIS/24 §8)
    p3fes::vu1::VU1Mode vu1_mode = p3fes::vu1::aot_program_count() ? p3fes::vu1::VU1Mode::Aot : p3fes::vu1::VU1Mode::Interp;
    const char* vu1_stats = nullptr;             // --vu1-stats FILE (p3fes/vu1/vu1_profile.h)
    std::vector<unsigned long long> vu1_marks;   // --vu1-stats-at V1,V2,...
    const char* vu1_capture = nullptr;           // --vu1-capture DIR N
    unsigned vu1_capture_n = 0;
    // --gs-backend software|d3d11|auto (headless: software unless d3d11 + --gs-exact), --gs-exact, --gpu-debug.
    std::string gs_backend = "auto";
    bool gs_exact = false, gpu_debug = false;
    std::string renderer = "emulated";          // --renderer emulated|native|native-generic|native-skin|native-diff
    const char* native_capture = nullptr;        // --native-capture DIR EVERY MAX (with a native renderer mode)
    bool native_cpu = false;                     // --native-cpu: the native model on the CPU, not the GPU stage
    unsigned native_capture_every = 1;
    unsigned long long native_capture_max = 0;
    bool unpaced = false;                        // --unpaced: windowed runs as fast as possible (measurements)
    int gs_threads = 2;                          // --gs-threads 0|1|2|off (-1): the graphics pipeline (gs_pipeline.h)
    unsigned gs_batch_kb = 0;                    // --gs-batch-kb N: the pipeline's hand-off size (0 = default)
    bool gs_speculate = false;                   // --gs-speculate: CSR reads do not wait (fail closed on PATH1 events)
    std::string pacing = "display";              // --pacing display|clock|legacy (frame_pacing.h)
    std::string display_rate = "game";           // --display-rate game|refresh|uncapped|HZ (gs_d3d11.h DisplayRate)
    double present_delay_ms = 1000.0 * p3fes::app::kGuestVblankS;  // --present-delay-ms
    bool present_delay_fixed = false;            // --present-delay-ms given: no adaptation
    bool hfr = true;                             // --hfr on|off (only under a decoupled --display-rate)
    bool hfr_low_latency = false;                // --hfr-latency low
    unsigned hfr_steps = 0;                      // --hfr-steps K
    std::string hfr_dump;                        // --hfr-dump DIR (diagnostics: A / in-between / B PNGs)
    unsigned hfr_dump_every = 30, hfr_dump_max = 20;  // --hfr-dump-every N, --hfr-dump-max M
    unsigned long long hfr_dump_from = 0;        // --hfr-dump-from FLIP
    bool hfr_test_replay = false;                // --hfr-test-replay (diagnostics: replay frames without blending)
    std::string frame_log;                       // --frame-log FILE
    bool frame_overlay = false;                  // --frame-overlay
    bool frame_stats = true;                     // --frame-stats off
    std::vector<unsigned long long> wall_marks;  // --wall-marks V1,V2,...: print wall time / flips at these vblanks
    std::string load_state;                      // --load-state FILE (runtime/STATE.md)
    bool reference_mode = false;                 // --reference-mode (runtime/STATE.md "Reference mode")
    int pc_text = -1;                            // --pc-text on (1) | off (0); -1: on windowed, off headless (pc_text.h)
};

// Makes `feed` the one GameHost::host_service consults (input.h feed_pad_input) for the scope's lifetime.
struct ActivePadFeed {
    explicit ActivePadFeed(p3fes::app::PadFeed* f) { p3fes::app::set_active_pad_feed(f); }
    ~ActivePadFeed() { p3fes::app::set_active_pad_feed(nullptr); }
    ActivePadFeed(const ActivePadFeed&) = delete;
    ActivePadFeed& operator=(const ActivePadFeed&) = delete;
};

// One line of guest state for the host crash report (host_crash.h).
std::string crash_context(void* user) {
    auto* host = static_cast<p3fes::app::GameHost*>(user);
    char b[160];
    std::snprintf(b, sizeof b, "vblank %llu, cycles %llu, flips %llu, thread %d, g_skyFrameCount %u",
                  static_cast<unsigned long long>(host->kernel().time().vblanks),
                  static_cast<unsigned long long>(host->kernel().time().cycles),
                  static_cast<unsigned long long>(host->gs().flip_count()), host->kernel().current_thread(),
                  host->guest_u32(0x7CEA78u));
    return b;
}

// Clears the crash context when the host goes away.
struct CrashContextScope {
    explicit CrashContextScope(p3fes::app::GameHost* h) { p3fes::app::set_crash_context(crash_context, h); }
    ~CrashContextScope() { p3fes::app::set_crash_context(nullptr, nullptr); }
    CrashContextScope(const CrashContextScope&) = delete;
    CrashContextScope& operator=(const CrashContextScope&) = delete;
};

int run_game(GameArgs& a, HostOptions& h) {
    p3fes::app::install_crash_reporter();
    // Windowed runs: unbuffered console output, so a log written to a file shows everything up to a hang or a crash.
    if (!a.headless) std::setvbuf(stdout, nullptr, _IONBF, 0);
    // Audio (runtime/audio/README.md "Host wiring"): windowed runs play the IOP's mix through XAudio2 on this engine,
    // paced; headless runs have no device. Declared before the host, which borrows the engine.
    p3fes::audio::XAudio2Backend spu2;
    if (!a.headless && !spu2.init())
        std::fprintf(stderr, "p3fes: XAudio2 init failed (hr=0x%08lX); the audio sink tries its own engine\n",
                     static_cast<unsigned long>(spu2.last_hresult()));
    a.cfg.audio.xaudio2 = !a.headless;
    a.cfg.audio.pace = !a.headless && !a.unpaced;
    // Frame pacing (docs/ANALYSIS/31): the audio queue follows the video clock by rate control, not back-pressure.
    const bool legacy_pacing = a.pacing == "legacy";
    a.cfg.audio.rate_control = !a.headless && !a.unpaced && !legacy_pacing;
    // 1 ms timer granularity for the host's waits (and the audio back-pressure's Sleep(1)) in windowed play.
    const p3fes::app::TimerResolution timer_res(!a.headless && !legacy_pacing);
    a.cfg.audio.engine = spu2.is_initialised() ? spu2.engine() : nullptr;
    // PC wording of the memory-card messages: it changes guest memory, so headless runs (the replay gates) keep the
    // disc's bytes unless --pc-text on is given.
    a.cfg.pc_text = a.pc_text < 0 ? !a.headless : a.pc_text != 0;

    p3fes::app::GameHost host;
    std::string err;
    if (!host.init(a.cfg, err)) {
        std::fprintf(stderr, "p3fes: %s\n", err.c_str());
        return 1;
    }
    const CrashContextScope crash_scope(&host);
    std::printf("p3fes: ELF %s loaded, disc %s, %s\n", a.cfg.elf.string().c_str(), a.cfg.disc.string().c_str(),
                a.headless ? "headless" : "windowed");
    const bool has_final = a.frames || a.until_flip || a.until_cycles || a.until_sky;
    bool profiling = false;  // --profile (host_profile.h)
    if (a.headless && !has_final && a.snaps.empty()) a.frames = 600;  // 10 virtual seconds

    // Pad input: live devices only when windowed and not replaying; scripts and replays work in both modes.
    p3fes::app::PadFeed feed;
    if (!h.replay.empty()) {
        std::vector<p3fes::app::InputEvent> events;
        if (!p3fes::app::load_input_log(h.replay, events, err)) {
            std::fprintf(stderr, "p3fes: --replay-input %s\n", err.c_str());
            return 2;
        }
        std::printf("p3fes: input: replaying %zu changes from %s (last at vblank %llu), no device polling\n", events.size(),
                    h.replay.c_str(), static_cast<unsigned long long>(events.empty() ? 0 : events.back().vblank));
        feed.set_replay(std::move(events));
    }
    if (!h.script.empty()) {
        feed.add_script(h.script);
        std::printf("p3fes: input: %zu scripted presses\n", h.script.size());
    }
    if (!h.record.empty()) {
        if (!feed.open_record(h.record, err)) {
            std::fprintf(stderr, "p3fes: --record-input: %s\n", err.c_str());
            return 2;
        }
        std::printf("p3fes: input: recording to %s\n", h.record.c_str());
    }
    const bool live = !a.headless && !feed.replaying();
    const bool feed_used = live || feed.replaying() || feed.scripted() || feed.recording();
    const bool recording = feed.recording();
    ActivePadFeed active(feed_used ? &feed : nullptr);
    p3fes::app::HostInputSampler sampler(h.input);

    // GS back end (docs/ANALYSIS/25 §3, §12): windowed play uses the D3D11 renderer when asked or by default (auto),
    // with the software path as the fallback. Headless runs rasterise in software (the oracle) unless asked for
    // `--gs-backend d3d11 --gs-exact`: an offscreen device in exact mode, byte-identical to software (the gates'
    // fast mode); without ROVs/doubles it falls back to software with the reason logged.
    bool want_gpu = false;
    if (a.gs_backend == "d3d11" || a.gs_backend == "auto") {
        if (a.cfg.gs_probe.enabled()) {
            if (!a.headless || a.gs_backend == "d3d11")
                std::printf("p3fes: gs-backend: software (--gs-census/--gs-record observe the software rasteriser)\n");
        } else if (a.headless) {
            if (a.gs_backend == "d3d11" && a.gs_exact) want_gpu = true;
            else if (a.gs_backend == "d3d11")
                std::printf("p3fes: gs-backend: software (headless d3d11 needs --gs-exact: snapshots must equal the software GS)\n");
        } else {
            want_gpu = true;
        }
    }
    HostDisplay display;
    // Track H's interpolated frames between guest frames plug in here (decoupled --display-rate; render thread).
    p3fes::gs::DisplayHook display_hook_for_renderer;
    // Track H: the interpolator (docs/ANALYSIS/32); declared before the renderer, which stops first.
    std::unique_ptr<p3fes::hfr::HfrInterpolator> hfr_interp;
    p3fes::gs::GsD3D11Renderer renderer;  // after `display`: stopped (swap chain released) before the window goes
    bool gpu = false;
    if (a.zones)
        host.set_zone_render_counters([&renderer](p3fes::app::ZoneWork& w) {
            const p3fes::gs::GsD3D11Renderer::Stats st = renderer.stats();
            w.r_submitted = st.submitted;
            w.r_merged = st.merged;
            w.r_executed = st.executed;
            w.r_presented = st.presented;
            w.r_busy_ms = st.busy_ms_total;
            w.r_gpu_ms = st.gpu_ms_total;
            w.r_gpu_frames = st.gpu_frames;
            w.r_cycles = st.thread_cycles;
            w.r_wait_ms = st.host_wait_ms;
        });
    // GS memory as the GPU has it after `ops` (snapshots, --png, local -> host transfers): GameHost::sync_gpu_memory.
    const auto gpu_memory = [&renderer, &host](p3fes::gs::OpList&& ops, std::vector<std::uint8_t>& vram, std::array<std::uint16_t, 512>& clut) {
        renderer.submit(std::move(ops), host.gs().priv().display());
        return renderer.sync_vram(vram, &clut);
    };
    if (a.headless && want_gpu) {
        p3fes::gs::GsD3D11Renderer::Options ro;
        ro.exact = true;
        ro.vsync = false;
        ro.debug = a.gpu_debug;
        ro.sync_timeout_s = 900.0;  // no window to keep alive; the render thread may be many lists behind
        ro.max_queued = 8;
        ro.gpu_timing = a.zones != nullptr;
        std::string why;
        if (renderer.start(nullptr, ro, why)) {
            gpu = host.enable_gpu_recording(false);  // ROVs required: no overlap splitting
            if (gpu) {
                host.set_gpu_memory_source(gpu_memory);
                host.set_gpu_recycle([&renderer](p3fes::gs::OpList& o) { renderer.recycle(o); });  // spent list storage back
                host.set_gpu_fallback_on_unsupported(true);
                std::printf("p3fes: gs-backend: d3d11 headless -- %s\n", renderer.description().c_str());
            } else {
                renderer.stop();
                std::printf("p3fes: gs-backend: software (GPU recording unavailable)\n");
            }
        } else {
            std::printf("p3fes: gs-backend: software (d3d11 unavailable: %s)\n", why.c_str());
        }
    }
    if (!a.headless) {
        h.display.external_presenter = want_gpu;
        if (!display.open(h.display, kWindowTitle, err)) {
            std::fprintf(stderr, "p3fes: window / D3D11 init failed: %s\n", err.c_str());
            return 1;
        }
        if (want_gpu) {
            p3fes::gs::GsD3D11Renderer::Options ro;
            ro.exact = a.gs_exact;
            ro.vsync = h.display.vsync;
            ro.linear = h.display.scale == p3fes::app::ScaleMode::Smooth;
            ro.debug = a.gpu_debug;
            ro.present_log = a.frame_stats || !legacy_pacing;
            if (!legacy_pacing) {
                // Timed presents: the render thread wakes for them on time even while the guest thread is busy.
                ro.thread_priority = THREAD_PRIORITY_HIGHEST;
                ro.frame_latency = 2;
                // The display rate, decoupled from the 30 fps game rate (--display-rate).
                if (a.display_rate == "refresh") ro.display = p3fes::gs::DisplayRate::Refresh;
                else if (a.display_rate == "uncapped") ro.display = p3fes::gs::DisplayRate::Uncapped;
                else if (a.display_rate != "game") {
                    ro.display = p3fes::gs::DisplayRate::Cap;
                    ro.display_hz = std::strtod(a.display_rate.c_str(), nullptr);
                }
                if (ro.display == p3fes::gs::DisplayRate::Cap || ro.display == p3fes::gs::DisplayRate::Uncapped) ro.vsync = false;
                if (ro.display != p3fes::gs::DisplayRate::Game)
                    std::printf("p3fes: pacing: display rate %s, decoupled from the game's frames\n", a.display_rate.c_str());
            }
            if (display_hook_for_renderer) renderer.set_display_hook(display_hook_for_renderer);
            if (!legacy_pacing && ro.display != p3fes::gs::DisplayRate::Game && a.hfr && !a.gs_exact) {
                // In-between pictures from the native batches of two game frames (docs/ANALYSIS/32).
                p3fes::hfr::HfrOptions ho;
                ho.steps = a.hfr_steps;
                ho.extrapolate = a.hfr_low_latency;
                ho.linear = ro.linear;
                ho.force_replay = a.hfr_test_replay;
                if (!a.hfr_dump.empty()) {
                    std::filesystem::create_directories(a.hfr_dump);
                    ho.dump_dir = a.hfr_dump;
                    ho.dump_every = a.hfr_dump_every;
                    ho.dump_max = a.hfr_dump_max;
                    ho.dump_from = a.hfr_dump_from;
                }
                hfr_interp = std::make_unique<p3fes::hfr::HfrInterpolator>(ho);
                renderer.set_interpolator(hfr_interp.get());
                std::printf("p3fes: hfr: interpolated pictures between game frames (latency %s, steps %s)\n",
                            a.hfr_low_latency ? "low" : "normal", a.hfr_steps ? std::to_string(a.hfr_steps).c_str() : "auto");
            }
            ro.gpu_timing = a.zones != nullptr;
            std::string why;
            if (renderer.start(display.hwnd(), ro, why)) {
                gpu = host.enable_gpu_recording(false, ro.exact);  // ROVs required: no overlap splitting; records only for exact mode
                if (gpu && hfr_interp) host.set_native_side_table(true);
                std::printf("p3fes: gs-backend: d3d11 -- %s\n", renderer.description().c_str());
                if (gpu && a.renderer != "emulated") {
                    const std::uint32_t mask = a.renderer == "native-generic" ? 1u : a.renderer == "native-skin" ? 6u : 7u;
                    const int nmode = a.renderer == "native-diff" ? 1 : a.renderer == "native-verify" ? 2 : 0;
                    if (host.enable_native_renderer(mask, nmode)) {
                        std::printf("p3fes: renderer: %s\n", a.renderer.c_str());
                        host.native_renderer()->set_prim_records(a.gs_exact);
                        // the GPU vertex stage (interpolated attributes only; --native-cpu keeps the CPU model)
                        host.native_renderer()->set_gpu(!a.gs_exact && !a.native_cpu && renderer.native_stage());
                        std::printf("p3fes: native vertex stage: %s\n", host.native_renderer()->gpu() ? "GPU" : "CPU");
                        if (a.native_capture) {
                            std::filesystem::create_directories(a.native_capture);
                            host.native_renderer()
                                ->set_capture(a.native_capture, a.native_capture_every, a.native_capture_max);
                        }
                    }
                }
                display.on_layout = [&renderer](int cw, int ch, const p3fes::app::ViewRect& r) { renderer.set_view(cw, ch, r.x, r.y, r.w, r.h); };
                const auto gpu_frame = [&renderer, &host]() {
                    p3fes::gs::OpList ops;
                    host.take_gpu_ops(ops);
                    renderer.submit(std::move(ops), host.gs().priv().display());
                    p3fes::gs::Frame f;
                    renderer.sync_frame(f);
                    return f;
                };
                display.external_frame = gpu_frame;
                host.set_frame_source(gpu_frame);
                host.set_gpu_memory_source(gpu_memory);
                host.set_gpu_recycle([&renderer](p3fes::gs::OpList& o) { renderer.recycle(o); });  // spent list storage back
                display.relayout();
            } else {
                std::printf("p3fes: gs-backend: software (d3d11 unavailable: %s)\n", why.c_str());
                if (!display.use_builtin_presenter(err)) {
                    std::fprintf(stderr, "p3fes: D3D11 presenter init failed: %s\n", err.c_str());
                    return 1;
                }
            }
        } else {
            std::printf("p3fes: gs-backend: software\n");
        }
        // WM_CLOSE: stop through the host's stop path; the loop below ends the run after this slice.
        display.on_close = [&host] { host.kernel().request_stop(); };
        display.screenshot_tag = [&host] {
            char b[64];
            std::snprintf(b, sizeof b, "p3fes_v%06llu_f%05llu", static_cast<unsigned long long>(host.kernel().time().vblanks),
                          static_cast<unsigned long long>(host.gs().flip_count()));
            return std::string(b);
        };
        if (live)
            std::printf("p3fes: input: keyboard (%s map) + XInput, sampled once per vblank%s\n", h.input_source.c_str(),
                        h.background_input ? ", also in the background" : "");
        std::printf("p3fes: window: %s, vsync %s, scale %s\n", h.display.fullscreen ? "full screen" : "windowed",
                    h.display.vsync ? "on" : "off", p3fes::app::to_string(h.display.scale));
    }
    // The state for the first VBLANK_START.
    if (live) feed.set_live(sampler.sample(display.focused() || h.background_input));

    host.gs().vu1().set_mode(a.vu1_mode);
    if (a.vu1_mode != p3fes::vu1::VU1Mode::Interp)
        std::printf("p3fes: vu1: %s mode, %zu compiled programs\n", a.vu1_mode == p3fes::vu1::VU1Mode::Aot ? "aot" : "diff",
                    p3fes::vu1::aot_program_count());
    // --reference-mode: the replaced functions run as their recompiled originals from the first call on (after a
    // --load-state: from the loaded point on; frames suspended in the state keep the bodies they entered).
    p3fes::rt::set_reference_mode(a.reference_mode);
    if (a.reference_mode)
        std::printf("p3fes: reference mode: %zu replaced functions run as their recompiled originals\n", p3fes::rt::replaced_count());
    // --load-state (runtime/STATE.md): the saved machine replaces the boot; the D3D11 back end gets GS memory and
    // the CLUT buffer uploaded from it. The state's pad replay is used unless --replay-input named a log.
    if (!a.load_state.empty()) {
        const double t0 = wall_now();
        p3fes::StateHeader sh;
        if (!host.load_state(a.load_state, &feed, err, &sh)) {
            std::fprintf(stderr, "p3fes: --load-state %s: %s\n", a.load_state.c_str(), err.c_str());
            return 1;
        }
        if (!h.replay.empty()) {
            std::vector<p3fes::app::InputEvent> events;
            if (p3fes::app::load_input_log(h.replay, events, err)) feed.set_replay(std::move(events));
            if (p3fes::app::active_pad_feed() != &feed) p3fes::app::set_active_pad_feed(&feed);
        }
        if (gpu) renderer.reset_memory(host.gs().core().mem().data(), host.gs().core().clut());
        std::printf("p3fes: state %s loaded in %.3f s (%s: vblank %llu, cycles %llu, flips %llu; saved in %s mode, continuing in %s mode)\n",
                    a.load_state.c_str(), wall_now() - t0, sh.label, static_cast<unsigned long long>(sh.vblanks),
                    static_cast<unsigned long long>(sh.cycles), static_cast<unsigned long long>(sh.flips),
                    sh.reference_mode ? "reference" : "hand", a.reference_mode ? "reference" : "hand");
    }
    // --vu1-stats: interval accounting of the VU1 interpreter.
    std::unique_ptr<p3fes::vu1::VU1Profile> vu1_prof;
    std::FILE* vu1_out = nullptr;
    std::size_t vu1_next_mark = 0;
    double vu1_mark_wall = wall_now();
    unsigned long long vu1_mark_vblank = 0;
    if (a.vu1_stats) {
        vu1_prof = std::make_unique<p3fes::vu1::VU1Profile>();
        const char* env = std::getenv("P3FES_VU1_DUMPS");
        const std::string dir = (env && *env) ? env : "ida/logs/vu1";
        const std::size_t n = p3fes::vu1::load_program_dumps(vu1_prof->programs, dir);
        vu1_out = std::fopen(a.vu1_stats, "w");
        if (!vu1_out) {
            std::fprintf(stderr, "p3fes: cannot write %s\n", a.vu1_stats);
            return 2;
        }
        std::printf("p3fes: vu1-stats: %zu program images from %s, %zu interval marks\n", n, dir.c_str(), a.vu1_marks.size());
        host.gs().vu1().set_profile(vu1_prof.get());
    }
    const auto vu1_close_interval = [&](const char* why) {
        if (!vu1_prof) return;
        const unsigned long long vb = host.kernel().time().vblanks;
        char label[96];
        std::snprintf(label, sizeof label, "vblanks %llu-%llu (%s)", vu1_mark_vblank, vb, why);
        const double now = wall_now();
        vu1_prof->write(vu1_out, label, now - vu1_mark_wall, vb - vu1_mark_vblank);
        std::fflush(vu1_out);
        vu1_prof->reset_counters();
        vu1_mark_wall = wall_now();
        vu1_mark_vblank = vb;
    };

    // The graphics pipeline (p3fes/gs/gs_pipeline.h): after --load-state, before the first slice.
    if (a.gs_threads >= 0 && (a.cfg.gs_probe.enabled() || a.cfg.trace_gs_to || a.vu1_stats)) {
        std::printf("p3fes: gs-threads: off (--gs-census / --gs-record / --trace-gs / --vu1-stats observe the synchronous model)\n");
        a.gs_threads = -1;
    }
    if (a.gs_threads >= 0) {
        p3fes::gs::GsPipelineOptions po;
        po.threads = static_cast<unsigned>(a.gs_threads);
        if (a.gs_batch_kb) po.batch_bytes = static_cast<std::size_t>(a.gs_batch_kb) << 10;
        po.speculate_csr = a.gs_speculate;
        if (!host.start_gs_pipeline(po)) {
            std::printf("p3fes: gs-threads: off (the native renderer's diff / verify modes observe the synchronous model)\n");
        } else {
            if (a.gs_speculate)
                std::printf("p3fes: gs-threads: --gs-speculate: CSR reads do not wait (not the exact default; stops at a PATH1 GS event)\n");
            std::printf("p3fes: gs-threads: %d (%s)\n", a.gs_threads,
                        a.gs_threads == 2 ? "VU1 worker + GS worker" : a.gs_threads == 1 ? "one worker" : "inline, no threads");
        }
    }

    p3fes::app::Pacer pacer;
    p3fes::app::StatsMeter meter;
    // Frame pacing (docs/ANALYSIS/31_frame_pacing.md): the virtual -> wall mapping, which slices present, the
    // display lock; frame-time telemetry and its overlay. Windowed only; legacy keeps the loop of before.
    p3fes::app::FramePacer::Config fpc;
    fpc.present_delay_s = std::max(0.0, a.present_delay_ms) / 1000.0;
    // Interpolated pictures (docs/ANALYSIS/32 §8): a tick between frames N-1 and N needs N latched, so the base delay
    // is one game frame (+ the render p90, adaptive) unless --hfr-latency low or --present-delay-ms says otherwise.
    if (hfr_interp && !a.hfr_low_latency && !a.present_delay_fixed) fpc.present_delay_s = p3fes::app::kGuestFrameS;
    p3fes::app::FramePacer fpacer(fpc);
    p3fes::app::PresentGate present_gate;
    p3fes::gs::DisplayRegs presented_disp{};
    std::uint64_t presented_vblank = 0;  // the vblank of the last timed present
    // The present delay: one vblank plus the render thread's recent p90 (PresentDelayController); fixed when given.
    const bool fixed_present_delay = a.present_delay_fixed;
    p3fes::app::PresentDelayController delay_ctl(fpc.present_delay_s);
    unsigned delay_changes = 0;
    const double qpc_hz = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return static_cast<double>(f.QuadPart);
    }();
    p3fes::app::DisplayTiming dtiming;
    double next_dtiming = 0.0;
    int lock_k = -1;
    const bool display_lock = a.pacing == "display";
    const bool decoupled_display = gpu && !a.headless && !legacy_pacing && a.display_rate != "game";
    const auto pacing_name = [&]() -> std::string {
        if (a.unpaced) return "unpaced";
        if (legacy_pacing) return "legacy";
        char b[96];
        if (display_lock && lock_k > 0)
            std::snprintf(b, sizeof b, "display %.2f Hz x%d, delay %.1f ms", 1.0 / dtiming.refresh_s, lock_k, fpacer.config().present_delay_s * 1000.0);
        else
            std::snprintf(b, sizeof b, "clock, delay %.1f ms", fpacer.config().present_delay_s * 1000.0);
        return b;
    };
    // The display lock: re-read DWM's timing twice a second; one guest vblank = k refreshes when it fits.
    const auto update_display_lock = [&](double virt) {
        if (!display_lock || a.unpaced) return;
        const double now = wall_now();
        if (now < next_dtiming) return;
        next_dtiming = now + 0.5;
        dtiming = p3fes::app::query_display_timing();
        const int k = dtiming.valid ? p3fes::app::display_lock_ratio(dtiming.refresh_s) : 0;
        fpacer.set_scale(k ? k * dtiming.refresh_s / p3fes::app::kGuestVblankS : 1.0, virt);
        if (k != lock_k) {
            lock_k = k;
            if (k)
                std::printf("p3fes: pacing: display lock, one guest vblank = %d refresh(es) of %.3f Hz (guest speed %.3f%%)\n", k,
                            1.0 / dtiming.refresh_s, 100.0 * p3fes::app::kGuestVblankS / (k * dtiming.refresh_s));
            else
                std::printf("p3fes: pacing: clock (display %.3f Hz is no multiple of 59.94 Hz)\n", dtiming.valid ? 1.0 / dtiming.refresh_s : 0.0);
        }
    };
    std::unique_ptr<p3fes::app::FrameTelemetry> ftel;
    p3fes::app::FrameOverlay overlay;
    std::vector<p3fes::gs::PresentRecord> present_recs;
    double next_overlay = 0.0;
    if (!a.headless && a.frame_stats) {
        p3fes::app::FrameTelemetry::Options fo;
        fo.log_path = a.frame_log;
        fo.pacing = pacing_name();
        ftel = std::make_unique<p3fes::app::FrameTelemetry>(fo);
        if (overlay.create(display.hwnd())) {
            overlay.set_visible(a.frame_overlay);
            display.on_overlay_key = [&overlay] { overlay.toggle(); };
        }
    }
    if (!a.headless && !legacy_pacing && !a.unpaced) std::printf("p3fes: pacing: %s\n", p3fes::app::boost_guest_thread().c_str());
    const auto frame_events = [&]() {
        p3fes::app::FrameEvents ev;
        if (gpu) ev.merged = renderer.stats().merged;
        ev.resyncs = legacy_pacing ? pacer.resyncs() : fpacer.resyncs();
        if (const p3fes::audio::HostAudio* ha = host.host_audio())
            if (const p3fes::audio::XAudio2Sink* xs = ha->xaudio2()) {
                const auto& st = xs->stats();
                ev.audio_waits = st.pace_waits;
                ev.audio_wait_ms = st.pace_wait_ms;
                ev.underruns = st.underruns;
                ev.audio_queued_ms = st.queued_ms;
                ev.audio_ratio = st.ratio;
            }
        return ev;
    };
    p3fes::u64 presented_flip = 0;
    bool closed = false;
    int rc = 0;
    std::sort(a.wall_marks.begin(), a.wall_marks.end());
    std::size_t next_mark = 0;
    const double wall_t0 = wall_now();
    double gpu_t0 = 0.0;
    bool gpu_presented = false;
    for (;;) {
        StopPlan plan;
        plan.until_flip = a.until_flip;
        plan.until_vblank = a.frames;
        plan.until_cycles = a.until_cycles;
        plan.until_sky = static_cast<std::uint32_t>(a.until_sky);
        for (const SnapshotSpec& s : a.snaps) {
            if (s.done) continue;
            auto arm = [](auto& field, unsigned long long v) {
                if (!field || v < field) field = static_cast<std::remove_reference_t<decltype(field)>>(v);
            };
            if (s.kind == StopReason::Flip) arm(plan.until_flip, s.n);
            if (s.kind == StopReason::Vblank) arm(plan.until_vblank, s.n);
            if (s.kind == StopReason::Cycles) arm(plan.until_cycles, s.n);
            if (s.kind == StopReason::Sky) arm(plan.until_sky, s.n);
        }
        if (vu1_prof && vu1_next_mark < a.vu1_marks.size() &&
            (!plan.until_vblank || a.vu1_marks[vu1_next_mark] < plan.until_vblank))
            plan.until_vblank = a.vu1_marks[vu1_next_mark];
        if (a.profile && !profiling && a.profile_from_vblank > host.kernel().time().vblanks &&
            (!plan.until_vblank || a.profile_from_vblank < plan.until_vblank))
            plan.until_vblank = a.profile_from_vblank;
        if (next_mark < a.wall_marks.size() && (!plan.until_vblank || a.wall_marks[next_mark] < plan.until_vblank))
            plan.until_vblank = a.wall_marks[next_mark];
        // Windowed, and headless with the D3D11 back end: a slice per vblank (the op hand-off point, as windowed).
        plan.every_vblank = !a.headless || gpu;
        if (ftel) ftel->slice_begin();
        const StopReason r = host.run(plan);
        while (next_mark < a.wall_marks.size() && host.kernel().time().vblanks >= a.wall_marks[next_mark]) {
            std::printf("p3fes: wall-mark vblank %llu: wall %.3f s (guest %.3f s), flips %llu\n",
                        static_cast<unsigned long long>(host.kernel().time().vblanks), wall_now() - wall_t0, host.wall_seconds(),
                        static_cast<unsigned long long>(host.gs().flip_count()));
            ++next_mark;
        }
        if (a.profile && !profiling && host.kernel().time().vblanks >= a.profile_from_vblank) {
            p3fes::app::ProfileOptions po;
            po.interval_us = a.profile_us;
            profiling = p3fes::app::start_profiler(po);
            std::printf("p3fes: profiling %s from vblank %llu every %u us\n", profiling ? "started" : "FAILED to start",
                        static_cast<unsigned long long>(host.kernel().time().vblanks), a.profile_us);
        }
        while (vu1_prof && vu1_next_mark < a.vu1_marks.size() &&
               host.kernel().time().vblanks >= a.vu1_marks[vu1_next_mark]) {
            vu1_close_interval("mark");
            ++vu1_next_mark;
            if (a.vu1_capture && a.vu1_marks.size() >= 2 && vu1_next_mark == a.vu1_marks.size() - 1) {
                vu1_prof->capture_dir = a.vu1_capture;
                vu1_prof->capture_per_key = a.vu1_capture_n;
                std::filesystem::create_directories(a.vu1_capture);
                std::printf("p3fes: vu1-capture on at vblank %llu -> %s\n",
                            static_cast<unsigned long long>(host.kernel().time().vblanks), a.vu1_capture);
            }
            if (vu1_next_mark == a.vu1_marks.size()) vu1_prof->capture_per_key = 0;
        }
        if (r == StopReason::Fatal) {
            rc = 1;
            break;
        }
        if (r == StopReason::MainExited) {
            std::printf("p3fes: the main thread exited\n");
            rc = 3;
            break;
        }
        for (SnapshotSpec& s : a.snaps) {
            if (s.done || !spec_holds(s, host)) continue;
            std::string serr;
            if (s.state) {
                const double t0 = wall_now();
                if (!host.save_state(s.dir, s.label, &feed, serr)) {
                    std::fprintf(stderr, "p3fes: save-state %s: %s\n", s.label.c_str(), serr.c_str());
                    rc = 1;
                } else {
                    std::error_code fec;
                    const auto bytes = std::filesystem::file_size(s.dir, fec);
                    std::printf("p3fes: state %s -> %s (%.1f MiB, %.3f s; flips %llu, vblanks %llu, cycles %llu; %s)\n", s.label.c_str(),
                                s.dir.c_str(), fec ? 0.0 : static_cast<double>(bytes) / 1048576.0, wall_now() - t0,
                                static_cast<unsigned long long>(host.gs().flip_count()),
                                static_cast<unsigned long long>(host.kernel().time().vblanks),
                                static_cast<unsigned long long>(host.kernel().time().cycles), host.state_summary().c_str());
                }
                s.done = true;
                continue;
            }
            if (!host.snapshot(s.dir, s.label, serr)) {
                std::fprintf(stderr, "p3fes: snapshot %s: %s\n", s.label.c_str(), serr.c_str());
                rc = 1;
            } else {
                std::printf("p3fes: snapshot %s -> %s (stop: %s, flips %llu, vblanks %llu, cycles %llu)\n", s.label.c_str(),
                            s.dir.c_str(), p3fes::app::to_string(r), static_cast<unsigned long long>(host.gs().flip_count()),
                            static_cast<unsigned long long>(host.kernel().time().vblanks),
                            static_cast<unsigned long long>(host.kernel().time().cycles));
            }
            s.done = true;
        }
        bool final_hit = (a.frames && host.kernel().time().vblanks >= a.frames) ||
                         (a.until_flip && host.gs().flip_count() >= a.until_flip) ||
                         (a.until_cycles && host.kernel().time().cycles >= a.until_cycles) ||
                         (a.until_sky && host.guest_u32(0x7CEA78u) >= a.until_sky);
        bool snaps_left = false;
        for (const SnapshotSpec& s : a.snaps) snaps_left |= !s.done;
        if (!has_final && !a.snaps.empty() && !snaps_left && a.headless) final_hit = true;
        if (final_hit) break;
        if (a.headless && gpu && host.gpu_sync_failed()) {
            std::fprintf(stderr, "p3fes: gs-backend: GS memory could not be synced from the GPU; stopping (not exact any more)\n");
            rc = 1;
            break;
        }
        if (gpu && host.gpu_handed_back()) {
            // A primitive the GPU path cannot draw: the software GS took over inside the slice (GameHost::gpu_sync_point).
            host.disable_gpu_recording();  // waits for the pipeline first
            renderer.stop();
            gpu = false;
            std::printf("p3fes: gs-backend: software from vblank %llu on\n", static_cast<unsigned long long>(host.kernel().time().vblanks));
        }
        if (a.headless && gpu) {
            // The ops of this vblank slice to the offscreen renderer; never waits (lists append when it falls behind).
            // With the graphics pipeline the GS worker hands them over when it reaches this point of the stream.
            host.end_vblank_slice([&renderer](p3fes::gs::OpList&& ops, const p3fes::gs::DisplayRegs& d) {
                renderer.submit(std::move(ops), d);
            });
        }
        if (!a.headless) {
            if (!display.pump()) {
                closed = true;
                break;
            }
            // Pacing: how long to wait before the next slice (absolute, so the work below is not added to it).
            const double virt_now = static_cast<double>(host.kernel().time().cycles) / kEeHz;
            double wake = 0.0;
            if (!a.unpaced) {
                if (legacy_pacing) {
                    wake = wall_now() + pacer.delay(virt_now, wall_now());
                } else {
                    update_display_lock(virt_now);
                    wake = wall_now() + fpacer.delay(virt_now, wall_now());
                }
            }
            if (gpu) {
                // Every vblank slice: the ops since the last one + the display registers now. The render thread
                // executes them at once; submit never waits for it (lists append when it falls behind). Legacy: it
                // presents after every list. Otherwise only the slices that show a new guest frame present, at their
                // timed moment (frame_pacing.h): one Present per guest frame on a steady cadence.
                {
                    // With the graphics pipeline the GS worker submits the list when it reaches this point of the
                    // stream (GameHost::end_vblank_slice); the present plan is decided here, at the vblank.
                    const p3fes::prof::Scope z(p3fes::prof::Zone::GsSubmit);
                    const p3fes::gs::DisplayRegs disp = host.gs().priv().display();
                    p3fes::gs::PresentPlan pp;
                    pp.tag = host.gs().flip_count();
                    if (!legacy_pacing) {
                        const bool changed = std::memcmp(&disp, &presented_disp, sizeof disp) != 0;
                        if (present_gate.should_present(pp.tag, host.kernel().time().vblanks, changed)) {
                            presented_disp = disp;
                            static const double qpf = [] {
                                LARGE_INTEGER f;
                                QueryPerformanceFrequency(&f);
                                return static_cast<double>(f.QuadPart);
                            }();
                            if (decoupled_display && a.unpaced) {
                                // Decoupled and uncapped: the display clock shows the newest frame.
                                pp.mode = p3fes::gs::PresentPlan::Mode::Latch;
                                pp.at_qpc = static_cast<long long>(wall_now() * qpf);
                            } else if (!a.unpaced) {
                                pp.mode = decoupled_display ? p3fes::gs::PresentPlan::Mode::Latch : p3fes::gs::PresentPlan::Mode::At;
                                if (display_lock && lock_k > 0) {
                                    // Phase lock: steer the presents to the middle of a refresh interval, slowly. Decoupled,
                                    // the render thread presents mid-refresh itself, so the frames fall due on the vblanks
                                    // (half a refresh away from every display tick: no tick is ever ambiguous).
                                    const double half = decoupled_display ? 0.5 * dtiming.refresh_s : 0.0;
                                    const double e = p3fes::app::present_phase_error(fpacer.present_at(virt_now) + half, dtiming.vblank_s,
                                                                                     dtiming.refresh_s);
                                    fpacer.shift(-0.1 * e * dtiming.refresh_s);
                                }
                                const std::uint64_t vb_now = host.kernel().time().vblanks;
                                const double at = fpacer.schedule_present(virt_now, wall_now(),
                                                                          presented_vblank ? vb_now - presented_vblank : 0);
                                presented_vblank = vb_now;
                                pp.at_qpc = static_cast<long long>(at * qpf);
                            }
                        } else {
                            pp.mode = p3fes::gs::PresentPlan::Mode::Skip;
                        }
                    }
                    host.end_vblank_slice([&renderer, pp](p3fes::gs::OpList&& ops, const p3fes::gs::DisplayRegs& d) mutable {
                        LARGE_INTEGER q;
                        QueryPerformanceCounter(&q);
                        pp.submit_qpc = q.QuadPart;
                        renderer.submit(std::move(ops), d, pp);
                    });
                }
                // Fail-safe: no picture presented within 5 s of the first submit -> software rasteriser.
                if (gpu_t0 == 0.0) gpu_t0 = wall_now();
                if (!gpu_presented) {
                    gpu_presented = renderer.stats().presented > 0;
                    if (!gpu_presented && wall_now() - gpu_t0 > 5.0) {
                        std::printf("p3fes: gs-backend: the d3d11 renderer presented nothing within 5 s; falling back to software\n");
                        host.gs_quiesce();
                        renderer.stop();
                        host.disable_gpu_recording();
                        display.external_frame = nullptr;
                        if (!display.use_builtin_presenter(err)) {
                            std::fprintf(stderr, "p3fes: D3D11 presenter init failed: %s\n", err.c_str());
                            rc = 1;
                            break;
                        }
                        gpu = false;
                    }
                }
            } else if (host.gs().flip_count() != presented_flip) {
                presented_flip = host.gs().flip_count();
                p3fes::gs::Frame shown;
                {
                    host.gs_quiesce();  // the software GS draws on the pipeline's GS worker
                    const p3fes::prof::Scope z(p3fes::prof::Zone::GsCrtc);
                    shown = host.gs().compose_output();
                }
                const p3fes::prof::Scope z(p3fes::prof::Zone::Present);
                display.show(shown);
            }
            const double virt = virt_now;
            if (h.stats) {
                p3fes::app::StatsReport rep;
                if (meter.update({wall_now(), virt, host.wall_seconds(), host.gs().flip_count(), host.kernel().time().vblanks}, rep)) {
                    const std::string line = p3fes::app::format_stats(rep);
                    std::printf("p3fes: [stats] %s\n", line.c_str());
                    display.set_status(line);
                }
            }
            // Pace virtual time to the wall clock (the guest never sees this), then sample the devices for the next
            // VBLANK_START as late as possible.
            {
                const p3fes::prof::Scope z(p3fes::prof::Zone::Present);
                if (ftel) ftel->wait_begin();
                display.wait(std::max(0.0, wake - wall_now()));
                if (ftel) ftel->wait_end();
            }
            if (gpu && (ftel || !legacy_pacing)) {
                present_recs.clear();
                renderer.take_present_log(present_recs);
                // The present delay follows the render thread's time from submit to picture ready (frame_pacing.h).
                if (!legacy_pacing && !fixed_present_delay)
                    for (const p3fes::gs::PresentRecord& pr : present_recs)
                        // (only lists the host submitted before their time: when it is behind, presents go at once and
                        // the render time says nothing about the delay a frame on time needs)
                        if (pr.target_qpc > pr.submit_qpc && pr.submit_qpc && pr.ready_qpc > pr.submit_qpc)
                        {
                            const double was = fpacer.config().present_delay_s;
                            fpacer.set_present_delay(delay_ctl.add(static_cast<double>(pr.ready_qpc - pr.submit_qpc) / qpc_hz));
                            if (std::fabs(fpacer.config().present_delay_s - was) > 0.002 && delay_changes++ < 50)
                                std::printf("p3fes: pacing: present delay %.1f ms at vblank %llu\n", fpacer.config().present_delay_s * 1000.0,
                                            static_cast<unsigned long long>(host.kernel().time().vblanks));
                        }
            }
            if (ftel) {
                ftel->slice_close(host.kernel().time().vblanks, host.gs().flip_count(), frame_events());
                if (gpu) ftel->presents(present_recs);
                const double now = wall_now();
                if (now >= next_overlay) {
                    next_overlay = now + 0.25;
                    ftel->set_pacing(pacing_name());
                    if (overlay.visible()) {
                        p3fes::app::FrameTelemetry::Live lv = ftel->live();
                        if (hfr_interp) lv.pacing += " | " + hfr_interp->overlay_line();  // docs/ANALYSIS/32
                        overlay.update(lv);
                    }
                }
            }
            if (display.close_requested()) {
                closed = true;
                break;
            }
            if (live) feed.set_live(sampler.sample(display.focused() || h.background_input));
        }
    }
    if (closed)
        std::printf("p3fes: window closed at vblank %llu, flip %llu (clean stop)\n",
                    static_cast<unsigned long long>(host.kernel().time().vblanks), static_cast<unsigned long long>(host.gs().flip_count()));

    if (p3fes::gs::GsPipeline* gp = host.gs_pipeline()) {
        host.gs_quiesce();
        const p3fes::gs::GsPipelineStats& ps = gp->stats();
        const auto cpu = gp->worker_cpu_ns();
        std::printf("p3fes: gs-threads: %llu commands in %llu batches (%.1f MiB), %llu VU1 runs (%llu kicked while the GIF was "
                    "busy), %llu PATH1 packets, %llu PATH1 GS events; worker CPU %.2f s + %.2f s; back-pressure waits %llu (%.3f s)\n",
                    static_cast<unsigned long long>(ps.commands), static_cast<unsigned long long>(ps.batches),
                    static_cast<double>(ps.bytes) / 1048576.0, static_cast<unsigned long long>(ps.vu_runs),
                    static_cast<unsigned long long>(ps.vu_runs_queued), static_cast<unsigned long long>(gp->p1_packets()),
                    static_cast<unsigned long long>(gp->p1_events()), static_cast<double>(cpu[0]) * 1e-9,
                    static_cast<double>(cpu[1]) * 1e-9, static_cast<unsigned long long>(ps.backpressure_waits),
                    static_cast<double>(ps.backpressure_ns) * 1e-9);
        for (unsigned w = 0; w < static_cast<unsigned>(p3fes::gs::SyncWhy::Count); ++w) {
            if (!ps.syncs[w]) continue;
            std::printf("p3fes: gs-threads: sync %-16s %10llu times, waited %10llu times, %.3f s\n",
                        p3fes::gs::to_string(static_cast<p3fes::gs::SyncWhy>(w)), static_cast<unsigned long long>(ps.syncs[w]),
                        static_cast<unsigned long long>(ps.waits[w]), static_cast<double>(ps.wait_ns[w]) * 1e-9);
        }
    }
    if (vu1_prof) {
        vu1_close_interval("end");
        std::fclose(vu1_out);
        host.gs().vu1().set_profile(nullptr);
        std::printf("p3fes: vu1-stats written to %s (%llu captures)\n", a.vu1_stats,
                    static_cast<unsigned long long>(vu1_prof->captured));
    }
    if (a.vu1_mode != p3fes::vu1::VU1Mode::Interp) {
        const p3fes::vu1::VU1AotStats& as = host.gs().vu1().aot_stats();
        std::printf("p3fes: vu1 aot: compiled runs %llu (bails %llu, compiled pairs %llu), interpreted runs %llu, diff runs %llu, "
                    "diff mismatches %llu\n",
                    static_cast<unsigned long long>(as.compiled_runs), static_cast<unsigned long long>(as.bails),
                    static_cast<unsigned long long>(as.compiled_pairs), static_cast<unsigned long long>(as.interp_runs),
                    static_cast<unsigned long long>(as.diff_runs), static_cast<unsigned long long>(as.diff_mismatches));
        std::printf("p3fes: vu1 aot: slow-path FMAC ops %llu\n", static_cast<unsigned long long>(p3fes::vu1::aot_slow_ops()));
        for (const auto& site : p3fes::vu1::aot_slow_sites(12)) // P3FES_VU1_SLOW_SITES=1
            std::printf("p3fes: vu1 aot: slow-path site %08X pc 0x%04X: %llu\n", site.code_va, site.pc,
                        static_cast<unsigned long long>(site.count));
        for (const auto& im : as.interp_images)
            if (im.runs)
                std::printf("p3fes: vu1 aot: interpreted image %016llX: %llu runs\n", static_cast<unsigned long long>(im.head),
                            static_cast<unsigned long long>(im.runs));
        if (as.diff_mismatches && rc == 0) rc = 5;
    }
    if (const p3fes::native::NativeG3* nr = host.native_renderer()) {
        const p3fes::native::NativeStats& ns = nr->stats();
        std::printf("p3fes: native renderer: runs %llu, native %llu (inits %llu), fallbacks gif-busy %llu / model %llu / "
                    "entry %llu, vertices %llu, triangles %llu, culled %llu, identifies %llu\n",
                    static_cast<unsigned long long>(ns.runs), static_cast<unsigned long long>(ns.native),
                    static_cast<unsigned long long>(ns.inits), static_cast<unsigned long long>(ns.fb_gif_busy),
                    static_cast<unsigned long long>(ns.fb_model), static_cast<unsigned long long>(ns.fb_entry),
                    static_cast<unsigned long long>(ns.verts), static_cast<unsigned long long>(ns.tris),
                    static_cast<unsigned long long>(ns.culled), static_cast<unsigned long long>(ns.identifies));
        std::printf("p3fes: native renderer: GPU batches %llu (%.1f MB of records)\n", static_cast<unsigned long long>(ns.gpu_batches),
                    ns.gpu_words * 4.0 / 1e6);
        std::printf("p3fes: native renderer: model %.1f ms, submit %.1f ms, clipped fallbacks %llu, clipped in the model %llu, captured %llu\n",
                    ns.model_ns / 1e6, ns.submit_ns / 1e6, static_cast<unsigned long long>(ns.fb_clipped), static_cast<unsigned long long>(ns.clipped_native),
                    static_cast<unsigned long long>(ns.captured));
        if (nr->diff()) {
            std::printf("p3fes: native-diff: VU state after the exact run vs the native path's: %llu runs, %llu differ;",
                        static_cast<unsigned long long>(ns.st_runs), static_cast<unsigned long long>(ns.st_runs_diff));
            for (int r = 1; r < 32; ++r)
                if (ns.st_vf[r]) std::printf(" vf%02d %llu", r, static_cast<unsigned long long>(ns.st_vf[r]));
            for (int r = 1; r < 16; ++r)
                if (ns.st_vi[r]) std::printf(" vi%02d %llu", r, static_cast<unsigned long long>(ns.st_vi[r]));
            std::printf(" other-regs %llu; data blocks (16 qw):", static_cast<unsigned long long>(ns.st_misc));
            for (int b = 0; b < 64; ++b)
                if (ns.st_data[b]) std::printf(" %03X %llu", b * 16, static_cast<unsigned long long>(ns.st_data[b]));
            std::printf("\n");
        }
        if (nr->diff() || nr->verify())
            std::printf("p3fes: native-diff: batches %llu, mismatched %llu (no kick %llu), vertices %llu, ADC flips %llu\n",
                        static_cast<unsigned long long>(ns.diff_batches), static_cast<unsigned long long>(ns.diff_bad),
                        static_cast<unsigned long long>(ns.diff_kick_count), static_cast<unsigned long long>(ns.diff_verts),
                        static_cast<unsigned long long>(ns.diff_adc));
        std::printf("p3fes: native renderer variants:");
        for (int v = 0; v < static_cast<int>(p3fes::native::G3Variant::Count); ++v)
            if (ns.variant[v])
                std::printf(" %s %llu", p3fes::native::to_string(static_cast<p3fes::native::G3Variant>(v)),
                            static_cast<unsigned long long>(ns.variant[v]));
        std::printf("\n");
    }
    host.flush_audio();
    host.finish_diagnostics();
    if (a.zones) host.write_zones(a.zones);
    host.stop_gs_pipeline();  // after the zones' last segment (the workers' CPU times)
    host.print_summary();
    for (const auto& f : host.flips())
        std::printf("p3fes:   flip %llu: vblank %llu, cycles %llu, DISPFB%u FBP %u, g_skyFrameCount %u\n",
                    static_cast<unsigned long long>(f.count), static_cast<unsigned long long>(f.vblank),
                    static_cast<unsigned long long>(f.cycles), f.circuit + 1, f.fbp, f.sky);
    if (a.png) {
        std::string perr;
        if (!host.sync_gpu_memory(perr)) std::fprintf(stderr, "p3fes: --png: %s\n", perr.c_str());  // headless d3d11
        if (!p3fes::gs::write_png(a.png, host.shown_frame())) std::fprintf(stderr, "p3fes: cannot write %s\n", a.png);
        else std::printf("p3fes: wrote %s\n", a.png);
    }
    if (gpu) {
        const auto st = renderer.stats();
        if (renderer.offscreen())
            std::printf("p3fes: d3d11 GS (headless): %llu op lists submitted (%llu appended to a queued one), %llu executed, "
                        "%llu GS memory syncs, last execute %.2f ms\n",
                        static_cast<unsigned long long>(st.submitted), static_cast<unsigned long long>(st.merged),
                        static_cast<unsigned long long>(st.executed), static_cast<unsigned long long>(host.gpu_syncs()), st.gpu_ms_last);
        else
            std::printf("p3fes: d3d11 GS: %llu op lists submitted (%llu appended to a queued one), %llu executed, %llu presented "
                        "(%llu presents skipped to catch up), last execute+compose %.2f ms\n",
                        static_cast<unsigned long long>(st.submitted), static_cast<unsigned long long>(st.merged),
                        static_cast<unsigned long long>(st.executed), static_cast<unsigned long long>(st.presented),
                        static_cast<unsigned long long>(st.skipped_presents), st.gpu_ms_last);
    }
    renderer.stop();
    if (hfr_interp) std::printf("p3fes: %s\n", hfr_interp->summary().c_str());

    // Input epilogue: fail closed when scripted or replayed input never reached the guest.
    feed.close_record();
    if (feed.record_failed()) {
        std::fprintf(stderr, "p3fes: input: writing %s failed\n", h.record.c_str());
        if (rc == 0) rc = 1;
    }
    const bool deterministic = feed.replaying() || feed.scripted();
    if (feed_used && feed.latches() == 0 && host.kernel().time().vblanks > 0) {
        std::fprintf(stderr, "p3fes: input: the host never consulted the pad feed (GameHost::host_service does not call "
                             "app::feed_pad_input) -- %s\n",
                     deterministic ? "scripted/replayed input was NOT applied" : "keyboard/gamepad input did not reach the guest");
        if (deterministic && rc == 0) rc = 4;
    } else if (feed.latches()) {
        std::printf("p3fes: input: %llu vblanks latched, %llu state changes%s%s\n", static_cast<unsigned long long>(feed.latches()),
                    static_cast<unsigned long long>(feed.changes()), recording ? ", recorded to " : "", recording ? h.record.c_str() : "");
        if (feed.replaying() && host.kernel().time().vblanks > feed.replay_last_vblank())
            std::printf("p3fes: input: the replay log ends at vblank %llu; its last state held to vblank %llu\n",
                        static_cast<unsigned long long>(feed.replay_last_vblank()),
                        static_cast<unsigned long long>(host.kernel().time().vblanks));
    }
    if (!a.headless && pacer.resyncs())
        std::printf("p3fes: pacing re-anchored %llu times (host fell > 0.25 s behind virtual time)\n",
                    static_cast<unsigned long long>(pacer.resyncs()));
    if (!a.headless && fpacer.resyncs())
        std::printf("p3fes: pacing re-anchored %llu times (host fell > %.1f ms behind; %.3f s of virtual time not caught up)\n",
                    static_cast<unsigned long long>(fpacer.resyncs()), fpc.max_debt_s * 1000.0, fpacer.dropped_s());
    if (ftel) {
        if (gpu) {
            present_recs.clear();
            renderer.take_present_log(present_recs);
            ftel->presents(present_recs);
        }
        ftel->finish();
        ftel->set_pacing(pacing_name());
        std::fputs(ftel->summary().c_str(), stdout);
        if (!a.frame_log.empty()) std::printf("p3fes: frame-time: per-frame log %s\n", a.frame_log.c_str());
    }
    overlay.destroy();
    if (profiling) p3fes::app::stop_profiler(a.profile);
    display.close();
    return rc;
}

#endif  // P3FES_HAVE_PROGRAM

bool parse_on_off(const char* s, bool& out) {
    if (std::strcmp(s, "on") == 0) out = true;
    else if (std::strcmp(s, "off") == 0) out = false;
    else return false;
    return true;
}

} // namespace

int main(int argc, char** argv) {
    bool smoke = false, selftest = false, headless = false;
    int headless_frames = 1;
    const char* png_path = nullptr;
    HostOptions host_opts;
    std::string screenshot_key;
#if defined(P3FES_HAVE_PROGRAM)
    GameArgs game;
#endif
    for (int i = 1; i < argc; ++i) {
        const char* a = argv[i];
        const bool has1 = i + 1 < argc;
        if (std::strcmp(a, "--smoke") == 0) {
            smoke = true;
        } else if (std::strcmp(a, "--selftest") == 0) {
            selftest = true;
        } else if (std::strcmp(a, "--headless") == 0) {
            headless = true;
        } else if (std::strcmp(a, "--frames") == 0 && has1) {
            const unsigned long long n = std::strtoull(argv[++i], nullptr, 0);
            headless_frames = n < 1 ? 1 : static_cast<int>(n);
#if defined(P3FES_HAVE_PROGRAM)
            game.frames = n;
#endif
        } else if (std::strcmp(a, "--png") == 0 && has1) {
            png_path = argv[++i];
        } else if (std::strcmp(a, "--help") == 0 || std::strcmp(a, "-h") == 0) {
            print_usage();
            return 0;
        } else if (std::strcmp(a, "--fullscreen") == 0) {
            host_opts.display.fullscreen = true;
        } else if (std::strcmp(a, "--vsync") == 0 && has1) {
            if (!parse_on_off(argv[++i], host_opts.display.vsync)) {
                std::fprintf(stderr, "p3fes: --vsync wants on or off, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--scale") == 0 && has1) {
            if (!p3fes::app::parse_scale_mode(argv[++i], host_opts.display.scale)) {
                std::fprintf(stderr, "p3fes: --scale wants fit, integer or smooth, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--stats") == 0) {
            host_opts.stats = true;
        } else if (std::strcmp(a, "--screenshot") == 0 && has1) {
            screenshot_key = argv[++i];
        } else if (std::strcmp(a, "--background-input") == 0) {
            host_opts.background_input = true;
        } else if (std::strcmp(a, "--input-config") == 0 && has1) {
            host_opts.input_config = argv[++i];
        } else if (std::strcmp(a, "--record-input") == 0 && has1) {
            host_opts.record = argv[++i];
        } else if (std::strcmp(a, "--replay-input") == 0 && has1) {
            host_opts.replay = argv[++i];
        } else if (std::strcmp(a, "--input-script") == 0 && has1) {
            std::string err;
            if (!p3fes::app::parse_input_script(argv[++i], host_opts.script, err)) {
                std::fprintf(stderr, "p3fes: %s\n", err.c_str());
                return 2;
            }
        } else if (std::strcmp(a, "--press") == 0 && has1) {
            std::string err;
            if (!p3fes::app::parse_press(argv[++i], host_opts.script, err)) {
                std::fprintf(stderr, "p3fes: %s\n", err.c_str());
                return 2;
            }
#if defined(P3FES_HAVE_PROGRAM)
        } else if (std::strcmp(a, "--iso") == 0 && has1) {
            game.cfg.disc = argv[++i];
        } else if (std::strcmp(a, "--extracted") == 0 && has1) {
            game.cfg.disc = std::filesystem::path(argv[++i]);
            if (std::filesystem::is_directory(game.cfg.disc / "disc")) game.cfg.disc /= "disc";
        } else if (std::strcmp(a, "--mods") == 0 && has1) {
            game.cfg.mods.emplace_back(argv[++i]);
        } else if (std::strcmp(a, "--elf") == 0 && has1) {
            game.cfg.elf = argv[++i];
        } else if (std::strcmp(a, "--symbols") == 0 && has1) {
            game.cfg.symbols = argv[++i];
        } else if (std::strcmp(a, "--memcard") == 0 && has1) {
            game.cfg.memcard = argv[++i];
        } else if (std::strcmp(a, "--dump-wav") == 0 && has1) {
            game.cfg.audio.dump_wav_dir = argv[++i];
        } else if (std::strcmp(a, "--until-flip") == 0 && has1) {
            game.until_flip = std::strtoull(argv[++i], nullptr, 0);
        } else if (std::strcmp(a, "--until-cycles") == 0 && has1) {
            game.until_cycles = std::strtoull(argv[++i], nullptr, 0);
        } else if (std::strcmp(a, "--until-sky") == 0 && has1) {
            game.until_sky = std::strtoull(argv[++i], nullptr, 0);
        } else if (std::strcmp(a, "--snapshot-at") == 0 && i + 2 < argc) {
            SnapshotSpec s;
            if (!parse_snapshot_spec(argv[i + 1], argv[i + 2], s)) {
                std::fprintf(stderr, "p3fes: bad --snapshot-at '%s' (want flip:N | vblank:N | cycles:N | sky:N)\n", argv[i + 1]);
                return 2;
            }
            game.snaps.push_back(s);
            i += 2;
        } else if (std::strcmp(a, "--save-state-at") == 0 && i + 2 < argc) {
            SnapshotSpec s;
            if (!parse_snapshot_spec(argv[i + 1], argv[i + 2], s)) {
                std::fprintf(stderr, "p3fes: bad --save-state-at '%s' (want flip:N | vblank:N | cycles:N | sky:N)\n", argv[i + 1]);
                return 2;
            }
            s.state = true;
            game.snaps.push_back(s);
            i += 2;
        } else if (std::strcmp(a, "--load-state") == 0 && has1) {
            game.load_state = argv[++i];
        } else if (std::strcmp(a, "--reference-mode") == 0) {
            game.reference_mode = true;
        } else if (std::strcmp(a, "--trace-syscalls") == 0 && has1) {
            game.cfg.trace_syscalls = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 0));
        } else if (std::strcmp(a, "--trace-hw") == 0 && has1) {
            game.cfg.trace_hw = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 0));
        } else if (std::strcmp(a, "--trace-sif") == 0) {
            game.cfg.trace_sif = true;
        } else if (std::strcmp(a, "--sound-log") == 0 && has1) {
            game.cfg.sound_log = argv[++i];
        } else if (std::strcmp(a, "--sk") == 0 && has1) {
            game.cfg.sk_mode = argv[++i];
        } else if (std::strcmp(a, "--iop-layout") == 0 && has1) {
            game.cfg.iop_layout = argv[++i];
        } else if (std::strcmp(a, "--spu2-interp") == 0 && has1) {
            game.cfg.spu2_interp = argv[++i];
        } else if (std::strcmp(a, "--profile") == 0 && has1) {
            game.profile = argv[++i];
        } else if (std::strcmp(a, "--profile-us") == 0 && has1) {
            game.profile_us = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 0));
        } else if (std::strcmp(a, "--profile-from") == 0 && has1) {
            game.profile_from_vblank = std::strtoull(argv[++i], nullptr, 0);
        } else if (std::strcmp(a, "--gs-backend") == 0 && has1) {
            game.gs_backend = argv[++i];
            if (game.gs_backend != "software" && game.gs_backend != "d3d11" && game.gs_backend != "auto") {
                std::fprintf(stderr, "p3fes: --gs-backend wants software, d3d11 or auto, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--gs-exact") == 0) {
            game.gs_exact = true;
        } else if (std::strcmp(a, "--native-cpu") == 0) {
            game.native_cpu = true;
        } else if (std::strcmp(a, "--native-capture") == 0 && i + 3 < argc) {
            game.native_capture = argv[i + 1];
            game.native_capture_every = static_cast<unsigned>(std::strtoul(argv[i + 2], nullptr, 0));
            game.native_capture_max = std::strtoull(argv[i + 3], nullptr, 0);
            i += 3;
        } else if (std::strcmp(a, "--renderer") == 0 && has1) {
            game.renderer = argv[++i];
            if (game.renderer != "emulated" && game.renderer != "native" && game.renderer != "native-generic" &&
                game.renderer != "native-skin" && game.renderer != "native-diff" &&
                game.renderer != "native-verify") {
                std::fprintf(stderr, "p3fes: --renderer wants emulated, native, native-generic or native-skin, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--gpu-debug") == 0) {
            game.gpu_debug = true;
        } else if (std::strcmp(a, "--unpaced") == 0) {
            game.unpaced = true;
        } else if (std::strcmp(a, "--gs-batch-kb") == 0 && has1) {
            game.gs_batch_kb = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 0));
        } else if (std::strcmp(a, "--gs-speculate") == 0) {
            game.gs_speculate = true;
        } else if (std::strcmp(a, "--gs-threads") == 0 && has1) {
            const char* v = argv[++i];
            if (std::strcmp(v, "off") == 0) game.gs_threads = -1;
            else if (std::strcmp(v, "0") == 0 || std::strcmp(v, "1") == 0 || std::strcmp(v, "2") == 0) game.gs_threads = v[0] - '0';
            else {
                std::fprintf(stderr, "p3fes: --gs-threads wants 0, 1, 2 or off, got '%s'\n", v);
                return 2;
            }
        } else if (std::strcmp(a, "--pacing") == 0 && has1) {
            game.pacing = argv[++i];
            if (game.pacing != "display" && game.pacing != "clock" && game.pacing != "legacy") {
                std::fprintf(stderr, "p3fes: --pacing wants display, clock or legacy, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--display-rate") == 0 && has1) {
            game.display_rate = argv[++i];
            const bool num = std::strtod(game.display_rate.c_str(), nullptr) >= 1.0;
            if (game.display_rate != "game" && game.display_rate != "refresh" && game.display_rate != "uncapped" && !num) {
                std::fprintf(stderr, "p3fes: --display-rate wants game, refresh, uncapped or a rate in Hz, got '%s'\n", argv[i]);
                return 2;
            }
        } else if (std::strcmp(a, "--fps") == 0 && has1) {
            // docs/ANALYSIS/32: the display rate (with interpolated in-between pictures); 30 = the game's own rate.
            const std::string f = argv[++i];
            const double hz = std::strtod(f.c_str(), nullptr);
            if (f == "30") game.display_rate = "game";
            else if (f == "monitor") game.display_rate = "refresh";
            else if (f == "unlimited" || f == "uncapped") game.display_rate = "uncapped";
            else if (hz >= 1.0) game.display_rate = f;
            else {
                std::fprintf(stderr, "p3fes: --fps wants 30, 60, 120, a rate in Hz, monitor or unlimited, got '%s'\n", f.c_str());
                return 2;
            }
        } else if (std::strcmp(a, "--pc-text") == 0 && has1) {
            const char* m = argv[++i];
            if (std::strcmp(m, "on") == 0) game.pc_text = 1;
            else if (std::strcmp(m, "off") == 0) game.pc_text = 0;
            else {
                std::fprintf(stderr, "p3fes: --pc-text wants on or off, got '%s'\n", m);
                return 2;
            }
        } else if (std::strcmp(a, "--hfr") == 0 && has1) {
            const char* m = argv[++i];
            if (std::strcmp(m, "on") == 0) game.hfr = true;
            else if (std::strcmp(m, "off") == 0) game.hfr = false;
            else {
                std::fprintf(stderr, "p3fes: --hfr wants on or off, got '%s'\n", m);
                return 2;
            }
        } else if (std::strcmp(a, "--hfr-latency") == 0 && has1) {
            const char* m = argv[++i];
            if (std::strcmp(m, "normal") == 0) game.hfr_low_latency = false;
            else if (std::strcmp(m, "low") == 0) game.hfr_low_latency = true;
            else {
                std::fprintf(stderr, "p3fes: --hfr-latency wants normal or low, got '%s'\n", m);
                return 2;
            }
        } else if (std::strcmp(a, "--hfr-steps") == 0 && has1) {
            game.hfr_steps = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 10));
        } else if (std::strcmp(a, "--hfr-dump") == 0 && has1) {
            game.hfr_dump = argv[++i];
        } else if (std::strcmp(a, "--hfr-dump-every") == 0 && has1) {
            game.hfr_dump_every = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 10));
        } else if (std::strcmp(a, "--hfr-dump-from") == 0 && has1) {
            game.hfr_dump_from = std::strtoull(argv[++i], nullptr, 10);
        } else if (std::strcmp(a, "--hfr-dump-max") == 0 && has1) {
            game.hfr_dump_max = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 10));
        } else if (std::strcmp(a, "--hfr-test-replay") == 0) {
            game.hfr_test_replay = true;
        } else if (std::strcmp(a, "--present-delay-ms") == 0 && has1) {
            game.present_delay_ms = std::strtod(argv[++i], nullptr);
            game.present_delay_fixed = true;
        } else if (std::strcmp(a, "--frame-log") == 0 && has1) {
            game.frame_log = argv[++i];
        } else if (std::strcmp(a, "--frame-overlay") == 0) {
            game.frame_overlay = true;
        } else if (std::strcmp(a, "--frame-stats") == 0 && has1) {
            const char* m = argv[++i];
            if (std::strcmp(m, "off") == 0) game.frame_stats = false;
            else if (std::strcmp(m, "on") == 0) game.frame_stats = true;
            else {
                std::fprintf(stderr, "p3fes: --frame-stats wants on or off, got '%s'\n", m);
                return 2;
            }
        } else if (std::strcmp(a, "--wall-marks") == 0 && has1) {
            for (const char* p = argv[++i]; *p;) {
                char* end = nullptr;
                game.wall_marks.push_back(std::strtoull(p, &end, 0));
                if (!end || end == p) break;
                p = *end == ',' ? end + 1 : end;
            }
        } else if (std::strcmp(a, "--gs-census") == 0 && has1) {
            game.cfg.gs_probe.census = argv[++i];
        } else if (std::strcmp(a, "--gs-census-marks") == 0 && has1) {
            for (const char* p = argv[++i]; *p;) {
                char* end = nullptr;
                game.cfg.gs_probe.marks.push_back(std::strtoull(p, &end, 0));
                if (!end || end == p) break;
                p = *end == ',' ? end + 1 : end;
            }
        } else if (std::strcmp(a, "--gs-record") == 0 && has1) {
            game.cfg.gs_probe.record = argv[++i];
        } else if (std::strcmp(a, "--gs-record-at") == 0 && has1) {
            for (const char* p = argv[++i]; *p;) {
                char* end = nullptr;
                game.cfg.gs_probe.record_at.push_back(std::strtoull(p, &end, 0));
                if (!end || end == p) break;
                p = *end == ',' ? end + 1 : end;
            }
        } else if (std::strcmp(a, "--zones") == 0 && has1) {
            game.zones = argv[++i];
            if (!game.cfg.zones_every) game.cfg.zones_every = 50;
        } else if (std::strcmp(a, "--zones-every") == 0 && has1) {
            game.cfg.zones_every = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 0));
        } else if (std::strcmp(a, "--vu1") == 0 && has1) {
            const char* m = argv[++i];
            if (std::strcmp(m, "interp") == 0) game.vu1_mode = p3fes::vu1::VU1Mode::Interp;
            else if (std::strcmp(m, "aot") == 0) game.vu1_mode = p3fes::vu1::VU1Mode::Aot;
            else if (std::strcmp(m, "diff") == 0) game.vu1_mode = p3fes::vu1::VU1Mode::Diff;
            else {
                std::fprintf(stderr, "p3fes: --vu1 wants interp | aot | diff\n");
                return 2;
            }
        } else if (std::strcmp(a, "--vu1-stats") == 0 && has1) {
            game.vu1_stats = argv[++i];
        } else if (std::strcmp(a, "--vu1-stats-at") == 0 && has1) {
            for (char* q = argv[++i]; *q;) {
                char* end = nullptr;
                game.vu1_marks.push_back(std::strtoull(q, &end, 0));
                if (end == q) break;
                q = (*end == ',') ? end + 1 : end;
            }
        } else if (std::strcmp(a, "--vu1-capture") == 0 && i + 2 < argc) {
            game.vu1_capture = argv[i + 1];
            game.vu1_capture_n = static_cast<unsigned>(std::strtoul(argv[i + 2], nullptr, 0));
            i += 2;
        } else if (std::strcmp(a, "--trace-gs") == 0 && has1) {
            char* end = nullptr;
            game.cfg.trace_gs_from = std::strtoull(argv[++i], &end, 0);
            game.cfg.trace_gs_to = (end && *end == '-') ? std::strtoull(end + 1, nullptr, 0) : game.cfg.trace_gs_from;
        } else if (std::strcmp(a, "--quiet") == 0) {
            game.cfg.quiet = true;
        } else if (std::strcmp(a, "--watch-write") == 0 && i + 2 < argc) {
            char* end = nullptr;
            game.cfg.watch_va = static_cast<std::uint32_t>(std::strtoul(argv[i + 1], &end, 0));
            game.cfg.watch_len = (end && *end == '+') ? static_cast<std::uint32_t>(std::strtoul(end + 1, nullptr, 0)) : 4u;
            game.cfg.watch_hits = static_cast<unsigned>(std::strtoul(argv[i + 2], nullptr, 0));
            i += 2;
#endif
        } else {
            std::fprintf(stderr, "p3fes: unknown argument '%s'\n", a);
            print_usage();
            return 2;
        }
    }

    // Input map: --input-config must exist; the default config/input.ini is optional.
    {
        std::string err;
        const bool explicit_cfg = !host_opts.input_config.empty();
        const std::filesystem::path path = explicit_cfg ? std::filesystem::path(host_opts.input_config) : kDefaultInputConfig;
        std::error_code ec;
        const bool present = std::filesystem::exists(path, ec);
        if (!p3fes::app::load_input_config(path, host_opts.input, /*missing_ok=*/!explicit_cfg, err)) {
            std::fprintf(stderr, "p3fes: input config %s\n", err.c_str());
            return 2;
        }
        if (present) host_opts.input_source = path.string();
    }
    host_opts.display.screenshot_key = host_opts.input.screenshot_key;
    host_opts.display.fullscreen_key = host_opts.input.fullscreen_key;
    if (!screenshot_key.empty()) {
        const int vk = p3fes::app::key_from_name(screenshot_key);
        if (vk < 0) {
            std::fprintf(stderr, "p3fes: --screenshot: unknown key '%s'\n", screenshot_key.c_str());
            return 2;
        }
        host_opts.display.screenshot_key = static_cast<std::uint8_t>(vk);
    }
    if (!host_opts.record.empty() && !host_opts.replay.empty() &&
        std::filesystem::absolute(host_opts.record) == std::filesystem::absolute(host_opts.replay)) {
        std::fprintf(stderr, "p3fes: --record-input and --replay-input name the same file\n");
        return 2;
    }

    (void)selftest;  // only distinguishes modes when the program is linked
#if defined(P3FES_HAVE_PROGRAM)
    if (!smoke && !selftest) {
        game.headless = headless;
        game.png = png_path;
        if (!game.zones) game.cfg.zones_every = 0;  // --zones-every alone does nothing
        return run_game(game, host_opts);
    }
#endif
    if (!host_opts.record.empty() || !host_opts.replay.empty() || !host_opts.script.empty())
        std::fprintf(stderr, "p3fes: input options apply to game mode only; ignored by the self-test\n");
    return run_selftest(smoke, headless, headless_frames, png_path, host_opts);
}
