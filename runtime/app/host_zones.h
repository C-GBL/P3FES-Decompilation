// Zone profiler recorder (`p3fes --zones FILE [--zones-every N]`), diagnostics only: turns the zone profiler of
// p3fes/prof.h on, cuts the run into segments of N vblanks (default 50) at VBLANK_START, and at exit writes one TSV
// row per segment -- wall time, speed (x real time, 59.94 vblanks/s), milliseconds per zone, workload counters --
// plus the VU1 programs each segment ran, and prints the whole-run zone table. tools/ours/perf/zones_report.py
// folds the rows into named vblank ranges (BUILDING.md "Profiling", docs/ANALYSIS/23).
//
// Zone entry points (who charges what): rt slow load/store (hw_dmac); KernelHooks::syscall / slow_check (kernel),
// interrupt handlers and kernel-mode calls (ee), SwitchToFiber sites (fiber), dma_pump (hw_dmac) and dma_sink by
// channel; GS: Vif1::transfer / resume (vif1), Vif1::run_vu (vu1), Gif::feed (gif), GsCore::draw_queue (gs_raster),
// image transfers / CLUT loads (gs_upload); IpuSystem service / registers / FIFO, DMAC channels 3-4 (ipu); SifHle
// service / syscalls, DMAC channels 5-7, R3000 host calls (iop), R3000::run (iop_cpu); Spu2Voices::render,
// AdxiServer::render_pass, Spu2Mixer::emit_pass (audio); disc sources' read_sectors (cdvd); main.cpp compose (gs_crtc)
// and present/pacing (present).
//
// Besides the zones, every row carries CPU time from the OS (the host thread's and the whole process's cycle counts,
// QueryThreadCycleTime / QueryProcessCycleTime, converted with the TSC rate; "other threads" = process - host
// thread: the D3D11 render thread, driver and audio threads), the machine's busy share over the segment
// is not sampled here: GetSystemTimes is far too slow on the loaded host), the D3D11 renderer's counters (lists, presents, render-thread
// busy time and cycles, GPU time from timestamp queries) and the names of the guest's running kwln tasks at the row's
// end (what is on screen: tools/ours/perf/bench.py classifies segments by them). Per flip, a second file
// FILE.frames.tsv gets the wall time, host-thread CPU time and zone times of every game frame (frame-time
// percentiles).
//
// Nothing here touches guest state (the task names are read, never written); the recorder is called from
// GameHost::host_service at VBLANK_START.
//
// Graphics pipeline workers (p3fes/gs/gs_pipeline.h) keep their own zone times (prof::g_prof_threads); each row
// carries them as w<N>_<zone> columns (w0 = the VU1 worker, or the single worker; w1 = the GS worker) plus their CPU
// time (cpu_w0, cpu_w1), and the console table lists them per thread. Their reads from this thread are
// unsynchronised (diagnostics: a zone a worker is still inside is charged at its next switch).
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "p3fes/prof.h"

namespace p3fes::app {

// Cumulative device counters at one instant (GameHost::zone_work).
struct ZoneWork {
    std::uint64_t flips = 0;
    std::uint64_t gs_prims = 0, gs_pixels = 0, gs_image_qw_in = 0, gs_image_qw_out = 0, gs_local_copies = 0,
                  gs_clut_loads = 0, gs_reg_writes = 0;
    std::uint64_t gif_qw[4] = {};
    std::uint64_t vif_vu_runs = 0, vif_vu_pairs = 0, vif_mpg_pairs = 0, vu1_kicks = 0, vu1_kick_qw = 0;
    // D3D11 renderer (cumulative; zero without one): op lists submitted / appended to a queued one / executed,
    // presents, render-thread busy time (execute + present, wall), GPU time (timestamp queries) and its frame count,
    // render-thread CPU cycles.
    std::uint64_t r_submitted = 0, r_merged = 0, r_executed = 0, r_presented = 0, r_gpu_frames = 0, r_cycles = 0;
    double r_busy_ms = 0.0, r_gpu_ms = 0.0;
    double r_wait_ms = 0.0;  // time the game thread waited for the render thread (readbacks, start / stop)
    // Not cumulative: the guest's running kwln tasks at this instant ("name|name|..."), and whether a Sofdec movie
    // is playing (the movie task's player pointer 0x7CDF10 is set).
    std::string tasks;
    bool movie = false;
};

class ZoneRecorder {
public:
    // Turns the profiler on with the host zone current. `ram` is guest main RAM (VU1 program attribution).
    ZoneRecorder(unsigned every, const std::uint8_t* ram, std::uint32_t ram_size);
    ~ZoneRecorder();  // turns it off
    ZoneRecorder(const ZoneRecorder&) = delete;
    ZoneRecorder& operator=(const ZoneRecorder&) = delete;

    bool due(std::uint64_t vblank) const noexcept { return vblank >= next_; }
    // Every VBLANK_START: records a frame when the flip counter moved (FILE.frames.tsv).
    void vblank(std::uint64_t vblank, std::uint64_t flips);
    // Closes the segment that ends at `vblank`.
    void row(std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w);
    // Closes the last (partial) segment, writes `path` and prints the whole-run table. `name` describes a VU1
    // program key (guest address) for the report.
    bool write(const std::string& path, std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w,
               const std::function<std::string(std::uint32_t)>& name);

private:
    struct Mark {
        std::uint64_t vblank = 0, cycles = 0, qpc = 0;
        std::uint64_t thr_cyc = 0, proc_cyc = 0;            // host thread / process CPU cycles
        std::uint64_t ticks[prof::kZones] = {};
        std::uint64_t tticks[prof::kProfThreads][prof::kZones] = {};  // graphics pipeline workers (gs_pipeline.h)
        std::uint64_t cpu_cycles[prof::kProfThreads] = {};              // the workers' CPU cycles
        prof::Work work{};
        ZoneWork dev{};
        std::vector<std::uint64_t> vu_runs, vu_pairs, vu_ticks;  // indexed like prof::State::vu_key
    };
    Mark mark(std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w) const;

    struct FrameRec {
        std::uint64_t vblank = 0, flips = 0, qpc = 0, thr_cyc = 0;
        std::uint64_t ticks[prof::kZones] = {};
    };
    void write_frames(const std::string& path, double qhz, double hz) const;

    unsigned every_;
    std::uint64_t next_;
    std::uint64_t qpc0_ = 0, tsc0_ = 0;
    void* thread_ = nullptr;  // the host thread (a real handle: QueryThreadCycleTime)
    std::uint64_t last_flips_ = 0;
    std::vector<FrameRec> frames_;  // frames_[0] = start
    std::vector<Mark> marks_;  // marks_[0] = start; row i spans marks_[i] .. marks_[i + 1]
};

} // namespace p3fes::app
