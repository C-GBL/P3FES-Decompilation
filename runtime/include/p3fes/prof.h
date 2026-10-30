// Zone profiler: host wall time per subsystem (`p3fes --zones FILE [--zones-every N]`), diagnostics only.
//
// The guest runs on one host thread (ADR-0013 §1), so "the subsystem running now" is one variable per thread: the
// current zone. The EE (host) thread's state is `g_prof`; the threaded graphics pipeline's workers (gs_pipeline.h)
// each have their own (`g_prof_threads`), selected through the thread-local `t_prof` (`cur()`). Each subsystem entry
// point switches it -- with `Scope` (RAII), or with the explicit `enter`/`leave` pair
// where the code can switch fibers (runtime/hle/kernel/scheduler.cpp L3: nothing with a destructor lives on a guest
// fiber's stack across a switch) -- and every switch charges the time since the previous switch to the zone being
// left. Nested entries restore the outer zone on exit, so a VU1 run inside a VIF1 transfer inside a DMA kick is
// charged to VU1, the rest to VIF1, the walk to the DMAC. A fiber switch restores the zone the resumed fiber saved,
// because the saved value lives on that fiber's own stack.
//
// Time source: the TSC when the CPU reports an invariant one (CPUID 0x80000007 EDX bit 8), else steady_clock (QPC);
// runtime/app/host_zones.cpp calibrates TSC ticks against QPC over the whole run. Workload counters (primitives by
// type, textured pixels, VU1 runs per uploaded program, GS events per GIF path) are counted only while on.
//
// Off (the default) every entry point costs a thread-local load, `cur().on` and one predictable branch. Nothing here reads
// or writes guest state: a run with --zones takes exactly the same guest path as one without (the replay gates
// compare both). Writers: the entry points listed in runtime/app/host_zones.h; reader: runtime/app/host_zones.cpp.
#pragma once

#include <chrono>
#include <cstdint>
#include <intrin.h>

namespace p3fes::prof {

enum class Zone : std::uint8_t {
    Host,      // the host loop (main.cpp, snapshots, stop checks)
    Ee,        // recompiled EE code and game/, with the rt adapter's inline paths
    Kernel,    // syscalls, check-point slow path (time base, interrupt dispatch), scheduler, device services' glue
    Fiber,     // SwitchToFiber between guest threads and the host
    Hw,        // hardware-register accesses from guest code (rt slow path) and the DMAC chain walk
    Vif1,      // VIF1 code parsing, UNPACK, MPG
    Vu1,       // VU1 micro-program interpreter
    Gif,       // GIF tag parsing (PATH1/2/3) and GS register-file writes
    GsRaster,  // primitive rasterisation (GsCore::draw_queue)
    GsUpload,  // image transfers host->local / local->host / local->local, CLUT loads
    GsCrtc,    // CRTC compose (compose_output)
    Ipu,       // IPU commands, FIFOs and its device service
    Iop,       // IOP HLE: SIF registers/DMA/RPC servers, IOP kernel HLE, R3000 host calls
    IopCpu,    // R3000 interpreter (the game's SDRDRV/SK modules)
    Audio,     // SPU2 voice render, CRI ADXI PSM mix, mixer passes to the sinks
    Cdvd,      // disc sector reads (ISO / extracted volumes)
    Present,   // windowed present (D3D11), pacing waits
    GsSubmit,  // D3D11 GS back end: handing the recorded op list to the render thread (windowed d3d11)
    GsWait,    // the EE thread waiting for the graphics pipeline's workers (gs_pipeline.h sync points); on a worker:
               // waiting for work
    Count
};
inline constexpr unsigned kZones = static_cast<unsigned>(Zone::Count);
inline constexpr std::uint8_t kOff = 0xFF;  // what enter() returns while the profiler is off

inline const char* zone_name(unsigned z) {
    static constexpr const char* names[kZones] = {"host", "ee", "kernel", "fiber", "hw_dmac", "vif1", "vu1", "gif",
                                                  "gs_raster", "gs_upload", "gs_crtc", "ipu", "iop", "iop_cpu",
                                                  "audio", "cdvd", "present", "gs_submit", "gs_wait"};
    return z < kZones ? names[z] : "?";
}

// Workload counters (only while on).
struct Work {
    std::uint64_t prims[8] = {};           // primitives rasterised by PRIM type (0 point .. 6 sprite, 7 prohibited)
    std::uint64_t prim_pixels[8] = {};     // pixels written, by PRIM type
    std::uint64_t prim_ticks[8] = {};      // gs_raster zone ticks, by PRIM type
    std::uint64_t tex_pixels = 0;          // pixels written by textured primitives (TME)
    std::uint64_t bilinear_pixels = 0;     // ... of which the magnification filter is bilinear
    std::uint64_t gs_events[3][4] = {};    // [SIGNAL, FINISH, LABEL][GIF path 0 (none) .. 3]
    std::uint64_t iop_insns = 0;           // R3000 instructions retired
    std::uint64_t vu1_unattributed = 0;    // VU1 runs whose start pair no recorded MPG covered
};

// VU1 runs per uploaded program, keyed by the guest address of the program's first MPG payload minus 0x10 (the
// DMAtag that carries the MPG VIFcode: the `vu1_prog_*` labels of symbols/p3fes.sym, docs/ANALYSIS/09).
inline constexpr unsigned kVuPrograms = 256;
inline constexpr unsigned kMicroPairs = 2048;  // 16 KiB of micro memory

struct State {
    bool on = false;
    bool tsc = false;           // time source: TSC (true) or QPC
    std::uint8_t cur = 0;       // current zone
    std::uint8_t gif_path = 0;  // GIF path being parsed (Gif::feed), for Work::gs_events
    std::uint64_t last = 0;     // time of the last switch
    std::uint64_t ticks[kZones] = {};
    std::uint64_t entries[kZones] = {};
    Work work{};
    // VU1 attribution: program key of the MPG that last wrote each micro-memory pair; the MPG sequence being
    // uploaded (a chunk that starts where the previous one ended continues its program).
    const std::uint8_t* ram = nullptr;  // guest main RAM (host pointer), to turn MPG payload pointers into addresses
    std::uint32_t ram_size = 0;
    std::uint32_t micro_owner[kMicroPairs] = {};
    std::uint32_t mpg_next_pair = ~0u;
    std::uint32_t mpg_key = 0;
    unsigned vu_n = 0;
    std::uint32_t vu_key[kVuPrograms] = {};
    std::uint64_t vu_runs[kVuPrograms] = {};
    std::uint64_t vu_pairs[kVuPrograms] = {};
    std::uint64_t vu_ticks[kVuPrograms] = {};  // vu1 zone ticks (nested GIF/GS work of its XGKICKs excluded)
};
inline State g_prof;                                // the EE (host) thread
inline constexpr unsigned kProfThreads = 4;         // graphics pipeline workers (gs_pipeline.h)
inline State g_prof_threads[kProfThreads];
inline const char* g_prof_thread_names[kProfThreads] = {};
inline void* g_prof_thread_handles[kProfThreads] = {};  // OS thread handles (CPU time columns of host_zones)
inline thread_local State* t_prof = &g_prof;
inline State& cur() noexcept { return *t_prof; }

// steady_clock is QPC on Windows, in nanoseconds.
inline std::uint64_t clock_now() noexcept {
    return static_cast<std::uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count());
}

inline std::uint64_t now() noexcept { return g_prof.tsc ? __rdtsc() : clock_now(); }

inline bool on() noexcept { return cur().on; }

// Charges the time since the last switch to the current zone and makes `z` current; returns the previous zone.
inline std::uint8_t switch_to(std::uint8_t z) noexcept {
    State& s = cur();
    const std::uint64_t t = now();
    s.ticks[s.cur] += t - s.last;
    s.last = t;
    const std::uint8_t prev = s.cur;
    s.cur = z;
    return prev;
}

inline std::uint8_t enter(Zone z) noexcept {
    State& s = cur();
    if (!s.on) return kOff;
    ++s.entries[static_cast<unsigned>(z)];
    return switch_to(static_cast<std::uint8_t>(z));
}

inline void leave(std::uint8_t prev) noexcept {
    if (prev != kOff && cur().on) switch_to(prev);
}

class Scope {
public:
    explicit Scope(Zone z) noexcept : prev_(enter(z)) {}
    ~Scope() { leave(prev_); }
    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

private:
    std::uint8_t prev_;
};

// ---- workload hooks (cheap; only while on) ---------------------------------------------------------------

// The GIF path being parsed (Gif::feed), restored on exit; nothing while off.
class GifPath {
public:
    explicit GifPath(std::uint8_t p) noexcept : prev_(cur().on ? cur().gif_path : kOff) {
        if (prev_ != kOff) cur().gif_path = p;
    }
    ~GifPath() {
        if (prev_ != kOff) cur().gif_path = prev_;
    }
    GifPath(const GifPath&) = delete;
    GifPath& operator=(const GifPath&) = delete;

private:
    std::uint8_t prev_;
};

inline void gs_event(unsigned kind) noexcept {  // 0 SIGNAL, 1 FINISH, 2 LABEL
    State& s = cur();
    if (s.on) ++s.work.gs_events[kind][s.gif_path & 3u];
}

// A VIF1 MPG wrote `pairs` pairs at micro pair `dest`; `src` is the host pointer of the first payload word.
inline void vu1_mpg(std::uint32_t dest, std::uint32_t pairs, const void* src) noexcept {
    State& s = cur();
    if (!s.on) return;
    const auto* p = static_cast<const std::uint8_t*>(src);
    std::uint32_t va = 0;
    if (s.ram && p >= s.ram && p < s.ram + s.ram_size) va = static_cast<std::uint32_t>(p - s.ram);
    if (dest != s.mpg_next_pair) s.mpg_key = va ? va - 0x10u : 0u;  // not a continuation: a new program starts
    s.mpg_next_pair = dest + pairs;
    for (std::uint32_t i = 0; i < pairs; ++i) s.micro_owner[(dest + i) & (kMicroPairs - 1u)] = s.mpg_key;
}

// A VU1 run started at micro pair `start`, executed `pairs` pairs and took `ticks` of the vu1 zone.
inline void vu1_run(std::uint32_t start, std::uint64_t pairs, std::uint64_t ticks) noexcept {
    State& s = cur();
    if (!s.on) return;
    const std::uint32_t key = s.micro_owner[start & (kMicroPairs - 1u)];
    if (!key) ++s.work.vu1_unattributed;
    unsigned i = 0;
    while (i < s.vu_n && s.vu_key[i] != key) ++i;
    if (i == s.vu_n) {
        if (s.vu_n == kVuPrograms) return;
        s.vu_key[s.vu_n++] = key;
    }
    ++s.vu_runs[i];
    s.vu_pairs[i] += pairs;
    s.vu_ticks[i] += ticks;
}

} // namespace p3fes::prof
