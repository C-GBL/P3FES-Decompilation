// The composed runtime (ADR-0013): one EEContext + EEMemory, the kernel/timing HLE (its HwBus and RtHooks),
// the GS (GIF/VIF1/VU1, DMAC ch1/2), the IPU (DMAC ch3/4), the SIF + IOP HLE over the user's disc (DMAC ch5/6), the rt adapter's
// hooks, and the recompiled program (`rt::lookup_func`). `GameHost` owns them in dependency order, loads the
// verified ELF into guest RAM and runs guest code in slices that end on host stop conditions (flip count,
// vblank count, virtual cycles, a guest counter at VBLANK_START) without a per-check-point predicate.
//
// Wiring (who calls whom), all single-threaded on the host thread (ADR-0013 §1):
//   * rt adapter -> RtHooks = the kernel's (or the tracing wrapper around it, --trace-syscalls/--trace-hw);
//   * kernel HwBus <- GsSystem::attach (GIF/VIF0/VIF1/FIFOs/GS privileged, DMAC ch0/1/2 data paths),
//     IpuSystem::attach (IPU_CMD/CTRL/BP/TOP, IPU FIFOs, DMAC ch3/4 data paths, INTC 8),
//     SifHle::attach (SIF registers, DMAC ch5/6), install_sif_syscalls (0x6B 0x76-0x7A 0x7C);
//   * kernel device services (registered before Kernel::start): IpuSystem::service (timed command completion),
//     SifHle::service (+ its next_event_cycles) and the host's stop/vblank service;
//   * GS flip callback -> flip log + stop on --until-flip / --snapshot-at flip:N;
//   * GS VIF/VU1 traps and IPU traps (reserved command/register, command while busy, FIFO over/underflow,
//     unsupported feature) -> RtHooks::fatal (fail closed); CTC2 vi28 FBRST bit 9 -> GsSystem::vu1().reset().
//   * memory card: HostConfig::memcard -> hle::memcard::open_memcard -> IopConfig::memcard (DBCMAN + MC2_S1,
//     docs/ANALYSIS/17 §6); audio: audio::HostAudio from HostConfig::audio, handed to the IOP's CRI_ADXI mixer
//     model with IopHle::set_audio_output right after the SifHle exists (runtime/audio/README.md "Host wiring").
#pragma once

#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <map>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "gs_probe.h"
#include "guest_symbols.h"
#include "host_zones.h"
#include "p3fes/audio/host_audio.h"
#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes/gs/gs_ops.h"
#include "p3fes/gs/gs_system.h"
#include "p3fes/hle/disc_source.h"
#include "p3fes/hle/kernel.h"
#include "p3fes/hle/mods_overlay.h"
#include "p3fes/hle/sif/sif.h"
#include "p3fes/ipu/ipu_system.h"
#include "native_vu.h"

namespace p3fes {
struct StateHeader;  // p3fes/state_io.h
class StateIo;
}

namespace p3fes::app {

class TracingHooks;
class PadFeed;  // input.h

struct HostConfig {
    std::filesystem::path elf = "extracted/disc/SLUS_216.21";
    std::filesystem::path disc = "input/persona3fes.iso";  // regular file: ISO; directory: extracted volumes
    // --mods DIR, repeatable (ADR-0016, p3fes/hle/mods_overlay.h): host folders whose files replace whole disc files
    // (later folders win per file). Empty and mods_overlay false = off: the disc source is the plain ISO / extracted
    // volumes, exactly as without this feature.
    std::vector<std::filesystem::path> mods;
    // Build the overlay even with no folder (the editor: folders added / mods enabled later through GameHost). The
    // overlay must exist from boot to be switchable at all: the game caches the CVMs' LSNs at boot.
    bool mods_overlay = false;
    bool mods_enabled = true;  // false: overlay built, nothing replaced until set_mods_enabled(true)
    // --pc-text on|off (pc_text.h): the memory-card messages in PC wording ("Checking save data..." instead of
    // "Checking memory card (8MB) (for PlayStation(R)2)..."), patched into guest RAM right after the ELF is loaded
    // (and again after a load_state), checked against the original bytes first. It changes guest memory, so
    // p3fes.exe turns it off for --headless runs (the replay gates compare eeMemory.bin); on for windowed play and
    // for every other GameHost user that keeps the default (the editor).
    bool pc_text = true;
    std::filesystem::path symbols = "symbols/p3fes.sym";   // diagnostics only; optional
    unsigned trace_syscalls = 0;  // log the first N calls of each syscall number (0 = off)
    unsigned trace_hw = 0;        // log the first N guest accesses per (register, direction) (0 = off)
    bool trace_sif = false;       // IopConfig::trace (every bind/call/command)
    // --trace-gs A-B: log every GS placement-register write (TEX0/TEX2, FRAME, ZBUF, BITBLTBUF, TRXPOS, TRXREG,
    // TRXDIR) with its GIF path while vblanks are in [A, B]; compare with tools/ours/pcsx2/gsdump_regs.py's
    // listing of a PCSX2 GS dump. 0-0 = off.
    std::uint64_t trace_gs_from = 0, trace_gs_to = 0;
    bool quiet = false;           // suppress _print / IOP chatter (fatals and summaries still print)
    std::uint32_t watch_va = 0, watch_len = 0;  // --watch-write: report writes to guest [va, va+len) (host_watch.h)
    unsigned watch_hits = 16;
    // --memcard SPEC (p3fes/hle/memcard/source.h): "" = PCSX2's slot-1 card found through PCSX2.ini, opened
    // read-only with copy-on-write; when no such card is available (no ini, slot disabled, file missing) the
    // port's own card %APPDATA%\P3FES\saves\Mcd001.ps2 is used, created formatted on first use ("appdata"
    // selects it explicitly). "pcsx2" (strict), PATH, "new", "blank", "none" as in source.h.
    std::string memcard;
    // Host audio (runtime/audio/README.md): device + pacing when windowed, --dump-wav DIR, a borrowed XAudio2
    // engine (main.cpp's XAudio2Backend). Headless without --dump-wav: only the NullSink fingerprint.
    audio::HostAudioOptions audio;
    // --sound-log FILE: every sound-side RPC the EE makes (SDRDRV libsd codes, SK 0x90F0 blocks, CRI DTX), one
    // line each -- vblank, virtual cycles, server/function, verb, payload words, reply (IopConfig::sound_sink;
    // docs/ANALYSIS/19 §4 phase 0). Empty = off. Logging changes nothing the guest sees.
    std::filesystem::path sound_log;
    // ADR-0014 B-lite (runtime/hle/sif/README.md §9): who answers the SK sound RPCs -- "modules" (default: the
    // game's SDRDRV/SK/MOD IRX files interpreted in place, SPU2 voices audible) or "constants" (the silent
    // increment-1 replies) -- and the IOP memory map, "pcsx2" (default: module images and the game's heap
    // where PCSX2 puts them) or "legacy" (the map of every snapshot before increment 2). --sk / --iop-layout.
    std::string sk_mode = "modules";
    std::string iop_layout = "pcsx2";
    // SPU2 voice interpolation: "gaussian" (the hardware's 4-tap table, default) | "linear" (increment 2). --spu2-interp.
    std::string spu2_interp = "gaussian";
    // --gs-census / --gs-record (gs_probe.h): opt-in GS diagnostics; never change guest-visible state.
    GsProbeConfig gs_probe;
    // --zones FILE: the zone profiler (host_zones.h) with segments of this many vblanks; 0 = off.
    unsigned zones_every = 0;
};

// Stop conditions of one `run` slice; 0 = not used. All are checked by the host, not the guest.
struct StopPlan {
    std::uint64_t until_flip = 0;     // GsSystem::flip_count() reaches this
    std::uint64_t until_vblank = 0;   // Timebase::vblanks reaches this (VBLANK_START, before its handlers)
    std::uint64_t until_cycles = 0;   // virtual EE cycles reach this
    std::uint32_t until_sky = 0;      // g_skyFrameCount (0x7CEA78) >= this at a VBLANK_START
    bool every_vblank = false;        // windowed pump: stop at every VBLANK_START
};

enum class StopReason { None, Flip, Vblank, Cycles, Sky, EveryVblank, MainExited, Fatal };
const char* to_string(StopReason r);

struct FlipRecord {
    std::uint64_t count = 0, vblank = 0, cycles = 0;
    std::uint32_t circuit = 0, fbp = 0, sky = 0;
    double wall = 0;  // host seconds inside run() at the flip
};

// A change of one of the game's own movie markers, sampled at VBLANK_START (docs/INTEGRATION_LOG.md M3-FMV):
// the movie task sub_10A860 sets game flag 5127 (flag array 0x83A21C, word 160 bit 7) and stores its Sofdec
// player object at 0x7CDF10 for the movie's lifetime and clears both in its teardown (0x10AC10-0x10AC20).
struct MarkerEdge {
    const char* what = "";
    std::uint32_t from = 0, to = 0;
    std::uint64_t vblank = 0, cycles = 0;
    std::uint32_t sky = 0;
    double wall = 0;  // host seconds inside run() at the sample
};

class GameHost {
public:
    GameHost();
    ~GameHost();
    GameHost(const GameHost&) = delete;
    GameHost& operator=(const GameHost&) = delete;

    // Opens the disc, loads + verifies the ELF, builds and wires every module. false + `error` on failure.
    bool init(const HostConfig& cfg, std::string& error);

    // Runs guest code until a condition of `plan` holds, the main thread exits, or a fatal.
    StopReason run(const StopPlan& plan);

    // Writes eeMemory.bin (32 MiB, PCSX2 layout), frame.png (composed CRTC picture) and capture.json.
    bool snapshot(const std::filesystem::path& dir, const std::string& label, std::string& error);

    // Machine state (runtime/STATE.md, game_state.cpp). save_state: between run slices (after a stop), the whole
    // machine -- EE context + memory, kernel + every guest-thread fiber's host stack, GS/VIF/GIF/VU1, IPU, SIF + IOP
    // (servers, interpreted SK modules, SPU2, memory card image), the audio fingerprint, this host's counters and
    // the pad feed `feed` (may be null) -- into `path`. load_state: right after init(), before the first run();
    // the next run() resumes where the saver stopped. Refuses a file from another executable, ELF or
    // behaviour-relevant configuration. A state carrying a pad feed needs `feed` (made the active feed).
    bool save_state(const std::string& path, const std::string& label, PadFeed* feed, std::string& error);
    bool load_state(const std::string& path, PadFeed* feed, std::string& error, StateHeader* header_out = nullptr);
    // The configuration words a state must match (sk mode, IOP layout, SPU2 interpolation, disc kind, ...).
    std::string state_config() const;
    // One line about what is in flight (guest threads on fibers, the current thread, a CD read, ADX streams).
    std::string state_summary();

    // ---- Mods overlay (ADR-0016; p3fes/hle/mods_overlay.h) -----------------------------------------------------
    // Exists when HostConfig::mods is non-empty or HostConfig::mods_overlay is set; otherwise every call below is a
    // no-op that fails (mods_active() false) and the disc is untouched. All calls: between run slices only.
    // What the guest sees after a change (mods_overlay.h "Reload"): the next file open gets the new bytes; open
    // handles, and files the game already loaded (H_Cdvd keeps them until the scene drops them), keep the old bytes.
    bool mods_active() const { return mods_ != nullptr; }
    const hle::ModsOverlay* mods() const { return mods_; }
    // Re-scans the folders and re-patches the game's ROFS tables in guest RAM (the editor's "reload mods").
    // false + `error` on a scan failure (a folder missing): the previous overrides stay in force.
    bool reload_mods(std::string& error);
    // Switch replacing on / off, or replace the folder list (in load order, later wins); both reload at once.
    bool set_mods_enabled(bool on, std::string& error);
    bool set_mod_folders(std::vector<std::filesystem::path> folders, std::string& error);
    // The files served from mods now (sorted by disc path), the mods found, and the files refused at the last scan.
    const std::vector<hle::ModOverride>& mod_overrides() const;
    const hle::ModsScan* mod_scan() const { return mods_ ? &mods_->scan() : nullptr; }
    // Disc files ("DATA\FIELD\F005_001.PAC") the guest has read since the last reload, sorted; and a callback at the
    // first read of each (inside run(): it must not call back into the host). After a reload,
    // mods_stale_after_reload() lists the changed files the guest had already read: show "needs a scene reload".
    std::vector<std::string> mod_files_read_since_reload() const;
    void set_mod_read_callback(std::function<void(const std::string&)> f);
    std::vector<std::string> mods_stale_after_reload() const;

    // Summary of the run for the console: time base, flips, threads, SIF/IOP counters, memory card, CRI_ADXI and
    // host audio counters, unhandled accesses. Call flush_audio() first at exit.
    void print_summary() const;
    // Ends the audio outputs (WAV headers patched, per-stream dumps closed; later mixer pushes are dropped).
    void flush_audio();
    // Writes the --gs-census file / a pending --gs-record recording (no-op without them).
    void finish_diagnostics();

    // D3D11 GS back end (windowed play, or headless exact mode; docs/ANALYSIS/25 §3, §12): GS rasterisation off,
    // primitives / transfers / CLUT loads recorded into op lists the host hands to the render thread. Registers,
    // transfers into the CPU copy of GS memory and everything the guest can observe are unchanged. false when a
    // --gs-census observer is installed.
    bool enable_gpu_recording(bool split_overlaps, bool prim_records = true);
    bool gpu_recording() const { return gpu_rec_ != nullptr; }
    // The native renderer (windowed play only, needs GPU recording; docs/ANALYSIS/31): the g3 VU1 batches go
    // straight into the op list (runtime/native/native_vu.h). Nothing the guest observes changes. `mask`: bit 0
    // g3_generic, bit 1 g3_skin. false without GPU recording.
    // `mode`: 0 native, 1 diff (exact drawing, every batch checked), 2 verify (native, every 16th batch exact + checked).
    bool enable_native_renderer(std::uint32_t mask, int mode = 0);
    const native::NativeG3* native_renderer() const { return native_.get(); }
    native::NativeG3* native_renderer() { return native_.get(); }
    // Back to software rasterisation (the D3D11 renderer failed); later frames redraw into the CPU copy.
    void disable_gpu_recording();
    // The ops recorded since the last call (call between run slices only).
    void take_gpu_ops(gs::OpList& out);
    // Frame interpolation (docs/ANALYSIS/32): the recorder keeps the native batches' side table in every op list.
    // Play mode with a display rate above the game's only; false without GPU recording.
    bool set_native_side_table(bool on);
    // Executes `ops` on the GPU and returns GS memory (4 MiB) and the CLUT buffer as the GPU has them afterwards;
    // false when the renderer cannot (timeout, lost device). Set by the code that owns the renderer.
    using GpuMemorySource = std::function<bool(gs::OpList&& ops, std::vector<std::uint8_t>& vram, std::array<std::uint16_t, 512>& clut)>;
    void set_gpu_memory_source(GpuMemorySource f) { gpu_memory_source_ = std::move(f); }
    // Copies GPU memory (everything recorded so far, executed) into the GS core's CPU copy, so snapshots, --png and
    // local -> host transfers see rendered pixels. Called by snapshot() and at the recorder's sync points; no-op
    // without GPU recording or a memory source. false + `error` when the GPU could not deliver.
    bool sync_gpu_memory(std::string& error);
    // At a primitive the GPU path cannot draw (points/lines), headless exact runs hand rasterisation back to the
    // software GS for the rest of the run (memory and CLUT synced first); windowed runs skip the primitive.
    void set_gpu_fallback_on_unsupported(bool on) { gpu_fallback_on_unsupported_ = on; }
    // Set when that hand-back happened inside run(): the owner then calls disable_gpu_recording() and stops its
    // renderer. `gpu_sync_failed()`: a sync point could not get GPU memory (the run is no longer exact).
    bool gpu_handed_back() const { return gpu_handed_back_.load(); }
    bool gpu_sync_failed() const { return gpu_sync_failed_; }
    std::uint64_t gpu_syncs() const { return gpu_syncs_; }
    // Source of the picture in snapshots (frame.png) and --png; default gs().compose_output().
    void set_frame_source(std::function<gs::Frame()> f) { frame_source_ = std::move(f); }
    gs::Frame shown_frame() { return frame_source_ ? frame_source_() : gs_->compose_output(); }

    // ---- Threaded graphics pipeline (p3fes/gs/gs_pipeline.h) --------------------------------------------------------
    // VU1 work and the GS front end on worker threads (threads 2: VU1 worker + GS worker; 1: one worker; 0: inline).
    // Start between run slices, after load_state; guest-visible behaviour is unchanged (the gates compare both).
    // false: not started (the native renderer's diff / verify modes observe VU1 kicks on the EE side).
    bool start_gs_pipeline(const gs::GsPipelineOptions& o);
    void stop_gs_pipeline();
    gs::GsPipeline* gs_pipeline() { return gs_ ? gs_->pipeline() : nullptr; }
    // Waits until the pipeline's workers are idle (no-op without it): before host code reads GS core / VU1 state.
    void gs_quiesce() const;
    // The end of a vblank slice (D3D11 back end): `submit` gets the ops recorded since the last one and the display
    // registers of now -- at once on the host thread without the pipeline, or on the GS worker when it reaches this
    // point of the stream with it (the closure travels with the stream; it carries whatever the host decided at the
    // vblank, e.g. the present plan). No-op without GPU recording.
    using GpuSubmit = std::function<void(gs::OpList&& ops, const gs::DisplayRegs& display)>;
    void end_vblank_slice(GpuSubmit submit);
    // Storage of op lists the renderer has executed (GsD3D11Renderer::recycle): the recorder's next list reuses it
    // instead of growing from empty every vblank. Called where the ops are taken (the GS worker with a pipeline).
    void set_gpu_recycle(std::function<void(gs::OpList&)> f) { gpu_recycle_ = std::move(f); }

    gs::GsSystem& gs() { return *gs_; }
    ipu::IpuSystem& ipu() { return *ipu_; }
    hle::Kernel& kernel() { return *kernel_; }
    EEMemory& memory() { return *mem_; }
    const EEContext& cpu() const { return *ctx_; }
    const std::vector<FlipRecord>& flips() const { return flips_; }
    const std::vector<MarkerEdge>& markers() const { return markers_; }
    const std::string& fatal_message() const { return fatal_message_; }
    double wall_seconds() const;  // host time spent inside run()
    const audio::HostAudio* host_audio() const { return audio_.get(); }  // frame telemetry (audio queue, waits)

    std::uint32_t guest_u32(std::uint32_t va) const { return mem_->read<std::uint32_t>(va); }
    // GS feature census since start (texture uploads by PSM and GIF path, TEX0/TEX1/CLAMP/ALPHA/TEST/PRIM
    // states, VIF codes, GIF tags per path, GS core counters): "key" -> count, keys sorted.
    std::map<std::string, std::uint64_t> gs_census() const;
    std::uint8_t guest_u8(std::uint32_t va) const { return mem_->read<std::uint8_t>(va); }
    // --zones: closes the last segment and writes the zone report (host_zones.h); false when off or on error.
    bool write_zones(const std::string& path);
    // --zones: the D3D11 renderer's cumulative counters for each row (set by the code that owns the renderer).
    void set_zone_render_counters(std::function<void(ZoneWork&)> f) { zone_render_counters_ = std::move(f); }

private:
    bool load_elf(std::string& error);
    bool state_body(StateIo& io, PadFeed* feed);
    std::string elf_sha256_;
    std::uint64_t host_service();
    void on_fatal(const hle::FatalInfo& info);
    void log(std::string_view s) const;

    HostConfig cfg_{};
    GuestSymbols syms_;
    // Construction order = dependency order; destruction runs in reverse (SIF before the disc, devices before the
    // kernel that owns their bus, kernel last).
    std::unique_ptr<EEMemory> mem_;
    struct CtxDelete {  // the EEContext lives in the pinned arena when it is enabled (p3fes/pinned.h)
        void operator()(EEContext* c) const noexcept;
    };
    std::unique_ptr<EEContext, CtxDelete> ctx_;
    std::unique_ptr<hle::Kernel> kernel_;
    std::unique_ptr<gs::GsSystem> gs_;
    std::unique_ptr<ipu::IpuSystem> ipu_;
    std::unique_ptr<hle::DiscSource> disc_;
    hle::ModsOverlay* mods_ = nullptr;           // == disc_ when --mods is given
    std::uint32_t elf_image_va_ = 0, elf_image_bytes_ = 0;  // the ELF's file bytes in guest RAM (load_elf)
    bool patch_mods_tables(std::string& error);
    void apply_pc_text();                         // HostConfig::pc_text (pc_text.h); logs the outcome, never fails init
    std::unique_ptr<audio::HostAudio> audio_;  // borrowed by the IOP's mixer model: destroyed after sif_
    std::unique_ptr<hle::sif::SifHle> sif_;
    std::unique_ptr<TracingHooks> tracing_;
    std::unique_ptr<GsProbe> gs_probe_;        // --gs-census / --gs-record; destroyed before gs_
    std::unique_ptr<ZoneRecorder> zones_;      // --zones (host_zones.h); null when off
    ZoneWork zone_work() const;
    std::function<void(ZoneWork&)> zone_render_counters_;
    std::unique_ptr<gs::GsOpRecorder> gpu_rec_;  // D3D11 GS back end op recorder; destroyed before gs_
    std::unique_ptr<native::NativeG3> native_;   // --renderer native (uses gpu_rec_; unhooked before it goes)
    std::function<gs::Frame()> frame_source_;
    GpuMemorySource gpu_memory_source_;
    bool gpu_fallback_on_unsupported_ = false, gpu_sync_failed_ = false;
    std::atomic<bool> gpu_handed_back_{false};  // set on the GS worker with the pipeline
    void submit_ops(const gs::DisplayRegs& display, const GpuSubmit& submit);
    std::function<void(gs::OpList&)> gpu_recycle_;  // set_gpu_recycle
    std::uint64_t gpu_syncs_ = 0;
    void gpu_sync_point(gs::GpuSyncReason why);
    std::string memcard_desc_;                 // what --memcard opened (open_memcard description)
    std::FILE* sound_log_ = nullptr;           // --sound-log sink (closed in the destructor)
    bool open_memcard(hle::sif::IopConfig& ic, std::string& error);
    static std::filesystem::path appdata_card_path();  // %APPDATA%\P3FES\saves\Mcd001.ps2, or empty

    StopPlan plan_{};
    StopReason reason_ = StopReason::None;
    std::uint64_t last_vblank_seen_ = 0;
    std::map<std::string, std::uint64_t> census_;  // GsCore state-register observer (gs_census)
    // ... its hot part: counts per (register, census bits of the value), named when read (fold_census)
    struct CensusKey {
        std::uint64_t v;
        std::uint32_t reg;
        bool operator==(const CensusKey& o) const noexcept { return v == o.v && reg == o.reg; }
    };
    struct CensusHash {
        std::size_t operator()(const CensusKey& k) const noexcept {
            return static_cast<std::size_t>((k.v ^ (static_cast<std::uint64_t>(k.reg) << 56) ^ (k.v >> 29)) * 0x9E3779B97F4A7C15ull);
        }
    };
    std::unordered_map<CensusKey, std::uint64_t, CensusHash> census_fast_;
    void fold_census(std::map<std::string, std::uint64_t>& m) const;
    std::uint64_t bitbltbuf_ = 0, trxreg_ = 0;
    void observe_gs_reg(std::uint32_t reg, std::uint64_t v);
    std::vector<FlipRecord> flips_;
    std::vector<MarkerEdge> markers_;
    std::uint32_t movie_flag_ = 0, movie_obj_ = 0;  // last sampled values of the two markers
    void sample_markers(std::uint64_t vblank);
    double host_seconds() const;  // wall_seconds() plus the current run() slice so far (call inside run())
    std::string fatal_message_;
    std::uint64_t wall_ticks_ = 0;  // QueryPerformanceCounter ticks inside run()
    std::uint64_t run_t0_ = 0;      // QPC at the start of the current run() slice
    bool started_ = false;
    bool dead_ = false;
};

} // namespace p3fes::app
