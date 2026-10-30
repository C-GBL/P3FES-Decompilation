#include "host_zones.h"

#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <intrin.h>

namespace p3fes::app {

namespace {

constexpr double kVblankHz = 59.94;

std::uint64_t qpc() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return static_cast<std::uint64_t>(t.QuadPart);
}

double qpc_hz() {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return static_cast<double>(f.QuadPart);
}

std::uint64_t thread_cycles(void* h) {
    ULONG64 c = 0;
    if (h) QueryThreadCycleTime(static_cast<HANDLE>(h), &c);
    return c;
}

std::uint64_t process_cycles() {
    ULONG64 c = 0;
    QueryProcessCycleTime(GetCurrentProcess(), &c);
    return c;
}


bool invariant_tsc() {
    int r[4] = {};
    __cpuid(r, static_cast<int>(0x80000000u));
    if (static_cast<unsigned>(r[0]) < 0x80000007u) return false;
    __cpuid(r, static_cast<int>(0x80000007u));
    return (static_cast<unsigned>(r[3]) >> 8) & 1u;
}

} // namespace

ZoneRecorder::ZoneRecorder(unsigned every, const std::uint8_t* ram, std::uint32_t ram_size)
    : every_(std::max(1u, every)), next_(std::max(1u, every)) {
    HANDLE h = nullptr;
    if (DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &h, THREAD_QUERY_LIMITED_INFORMATION, FALSE, 0))
        thread_ = h;
    prof::State& s = prof::g_prof;
    s = prof::State{};
    s.tsc = invariant_tsc();
    s.ram = ram;
    s.ram_size = ram_size;
    s.cur = static_cast<std::uint8_t>(prof::Zone::Host);
    qpc0_ = qpc();
    tsc0_ = __rdtsc();
    s.last = prof::now();
    for (prof::State& w : prof::g_prof_threads) {  // started before the pipeline's workers
        w = prof::State{};
        w.tsc = s.tsc;
        w.cur = static_cast<std::uint8_t>(prof::Zone::GsWait);
        w.last = s.last;
        w.ram = ram;
        w.ram_size = ram_size;
        w.on = true;
    }
    s.on = true;
    marks_.push_back(mark(0, 0, ZoneWork{}));
    FrameRec f;
    f.qpc = marks_[0].qpc;
    f.thr_cyc = marks_[0].thr_cyc;
    frames_.reserve(1 << 14);
    frames_.push_back(f);
}

ZoneRecorder::~ZoneRecorder() {
    prof::g_prof.on = false;
    for (prof::State& w : prof::g_prof_threads) w.on = false;
    if (thread_) CloseHandle(static_cast<HANDLE>(thread_));
}

void ZoneRecorder::vblank(std::uint64_t vblank, std::uint64_t flips) {
    if (flips == last_flips_) return;
    last_flips_ = flips;
    prof::State& s = prof::g_prof;
    if (s.on) prof::switch_to(s.cur);
    FrameRec f;
    f.vblank = vblank;
    f.flips = flips;
    f.qpc = qpc();
    f.thr_cyc = thread_cycles(thread_);
    std::copy(std::begin(s.ticks), std::end(s.ticks), std::begin(f.ticks));
    frames_.push_back(f);
}

ZoneRecorder::Mark ZoneRecorder::mark(std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w) const {
    prof::State& s = prof::g_prof;
    if (s.on) prof::switch_to(s.cur);  // charge the current zone up to now
    Mark m;
    m.vblank = vblank;
    m.cycles = cycles;
    m.qpc = qpc();
    m.thr_cyc = thread_cycles(thread_);
    m.proc_cyc = process_cycles();
    // (No GetSystemTimes here: on the loaded 16-thread host it took from ~1 ms up to seconds per call, and that wait
    // was charged to the zone current at VBLANK_START -- the kernel's. tools/ours/perf/bench.py samples the machine's
    // load from its own process instead.)
    std::copy(std::begin(s.ticks), std::end(s.ticks), std::begin(m.ticks));
    for (unsigned t = 0; t < prof::kProfThreads; ++t)
        for (unsigned z = 0; z < prof::kZones; ++z) m.tticks[t][z] = prof::g_prof_threads[t].ticks[z];
    for (unsigned t = 0; t < prof::kProfThreads; ++t) m.cpu_cycles[t] = thread_cycles(prof::g_prof_thread_handles[t]);
    m.work = s.work;
    m.dev = w;
    m.vu_runs.assign(s.vu_runs, s.vu_runs + s.vu_n);
    m.vu_pairs.assign(s.vu_pairs, s.vu_pairs + s.vu_n);
    m.vu_ticks.assign(s.vu_ticks, s.vu_ticks + s.vu_n);
    return m;
}

void ZoneRecorder::row(std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w) {
    marks_.push_back(mark(vblank, cycles, w));
    next_ = (vblank / every_ + 1) * every_;
}

bool ZoneRecorder::write(const std::string& path, std::uint64_t vblank, std::uint64_t cycles, const ZoneWork& w,
                         const std::function<std::string(std::uint32_t)>& name) {
    if (vblank > marks_.back().vblank || marks_.size() == 1) marks_.push_back(mark(vblank, cycles, w));
    const prof::State& s = prof::g_prof;
    const double qhz = qpc_hz();
    const Mark& first = marks_.front();
    const Mark& last = marks_.back();
    const double wall = static_cast<double>(last.qpc - first.qpc) / qhz;
    // Ticks per second: TSC calibrated against QPC over the run, or steady_clock nanoseconds.
    const double hz = s.tsc ? static_cast<double>(__rdtsc() - tsc0_) / (static_cast<double>(qpc() - qpc0_) / qhz) : 1e9;
    auto ms = [hz](std::uint64_t t) { return 1e3 * static_cast<double>(t) / hz; };

    std::FILE* f = std::fopen(path.c_str(), "w");
    if (!f) {
        std::fprintf(stderr, "p3fes: cannot write %s\n", path.c_str());
        return false;
    }
    std::fprintf(f, "# p3fes --zones: %zu segments of %u vblanks; time source %s (%.0f ticks/s); wall %.3f s for %llu vblanks"
                    " (%.3fx real time); zone times in ms; counters are per segment\n",
                 marks_.size() - 1, every_, s.tsc ? "TSC" : "steady_clock", hz, wall,
                 static_cast<unsigned long long>(last.vblank), wall > 0 ? static_cast<double>(last.vblank) / kVblankHz / wall : 0.0);
    std::fprintf(f, "# zone entries over the run:");
    for (unsigned z = 0; z < prof::kZones; ++z)
        std::fprintf(f, " %s=%llu", prof::zone_name(z), static_cast<unsigned long long>(s.entries[z]));
    std::fprintf(f, "\n");
    std::fprintf(f, "seg\tv0\tv1\tcycles\twall_s\tspeed");
    for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(f, "\t%s", prof::zone_name(z));
    std::fprintf(f, "\tflips\tprims\tpoint\tline\tlinestrip\ttri\ttristrip\ttrifan\tsprite\tprohibited\tpixels\ttex_pixels"
                    "\tbilinear_pixels\timage_qw_in\timage_qw_out\tlocal_copies\tclut_loads\tgs_reg_writes\tgif_p1_qw\tgif_p2_qw"
                    "\tgif_p3_qw\tvu1_runs\tvu1_pairs\tmpg_pairs\tvu1_kicks\tvu1_kick_qw\tvu1_unattributed\tiop_insns"
                    "\tsignal_p0\tsignal_p1\tsignal_p2\tsignal_p3\tfinish_p0\tfinish_p1\tfinish_p2\tfinish_p3"
                    "\tlabel_p0\tlabel_p1\tlabel_p2\tlabel_p3");
    static constexpr const char* kPrim[8] = {"point", "line", "linestrip", "tri", "tristrip", "trifan", "sprite", "prohibited"};
    for (const char* p : kPrim) std::fprintf(f, "\tpx_%s", p);
    for (const char* p : kPrim) std::fprintf(f, "\tms_%s", p);
    static constexpr prof::Zone kWorkerZones[] = {prof::Zone::Vif1, prof::Zone::Vu1, prof::Zone::Gif, prof::Zone::GsRaster,
                                                  prof::Zone::GsUpload, prof::Zone::GsSubmit, prof::Zone::GsWait};
    for (unsigned t = 0; t < 2; ++t) {
        for (prof::Zone z : kWorkerZones) std::fprintf(f, "\tw%u_%s", t, prof::zone_name(static_cast<unsigned>(z)));
        std::fprintf(f, "\tw%u_busy", t);
    }
    std::fprintf(f, "\tcpu_w0\tcpu_w1");  // the pipeline workers' CPU time (QueryThreadCycleTime, ms at the TSC rate)
    std::fprintf(f, "\tcpu_host_ms\tcpu_proc_ms\tcpu_other_ms\tr_submitted\tr_merged\tr_executed\tr_presented"
                    "\tr_busy_ms\tr_cpu_ms\tgpu_ms\tgpu_frames\tr_wait_ms\tmovie\ttasks\n");
    for (std::size_t i = 1; i < marks_.size(); ++i) {
        const Mark& a = marks_[i - 1];
        const Mark& b = marks_[i];
        const double sw = static_cast<double>(b.qpc - a.qpc) / qhz;
        const double vb = static_cast<double>(b.vblank - a.vblank);
        std::fprintf(f, "%zu\t%llu\t%llu\t%llu\t%.6f\t%.4f", i - 1, static_cast<unsigned long long>(a.vblank),
                     static_cast<unsigned long long>(b.vblank), static_cast<unsigned long long>(b.cycles - a.cycles), sw,
                     sw > 0 ? vb / kVblankHz / sw : 0.0);
        for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(f, "\t%.3f", ms(b.ticks[z] - a.ticks[z]));
        // (a counter that went backwards -- the renderer restarted -- counts as 0)
        auto d = [](std::uint64_t x, std::uint64_t y) { return static_cast<unsigned long long>(y >= x ? y - x : 0); };
        std::fprintf(f, "\t%llu\t%llu", d(a.dev.flips, b.dev.flips), d(a.dev.gs_prims, b.dev.gs_prims));
        for (unsigned p = 0; p < 8; ++p) std::fprintf(f, "\t%llu", d(a.work.prims[p], b.work.prims[p]));
        std::fprintf(f, "\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu", d(a.dev.gs_pixels, b.dev.gs_pixels),
                     d(a.work.tex_pixels, b.work.tex_pixels), d(a.work.bilinear_pixels, b.work.bilinear_pixels),
                     d(a.dev.gs_image_qw_in, b.dev.gs_image_qw_in), d(a.dev.gs_image_qw_out, b.dev.gs_image_qw_out),
                     d(a.dev.gs_local_copies, b.dev.gs_local_copies), d(a.dev.gs_clut_loads, b.dev.gs_clut_loads),
                     d(a.dev.gs_reg_writes, b.dev.gs_reg_writes));
        for (unsigned p = 1; p < 4; ++p) std::fprintf(f, "\t%llu", d(a.dev.gif_qw[p], b.dev.gif_qw[p]));
        std::fprintf(f, "\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu", d(a.dev.vif_vu_runs, b.dev.vif_vu_runs),
                     d(a.dev.vif_vu_pairs, b.dev.vif_vu_pairs), d(a.dev.vif_mpg_pairs, b.dev.vif_mpg_pairs),
                     d(a.dev.vu1_kicks, b.dev.vu1_kicks), d(a.dev.vu1_kick_qw, b.dev.vu1_kick_qw),
                     d(a.work.vu1_unattributed, b.work.vu1_unattributed), d(a.work.iop_insns, b.work.iop_insns));
        for (unsigned k = 0; k < 3; ++k)
            for (unsigned p = 0; p < 4; ++p) std::fprintf(f, "\t%llu", d(a.work.gs_events[k][p], b.work.gs_events[k][p]));
        for (unsigned p = 0; p < 8; ++p) std::fprintf(f, "\t%llu", d(a.work.prim_pixels[p], b.work.prim_pixels[p]));
        for (unsigned p = 0; p < 8; ++p) std::fprintf(f, "\t%.3f", ms(b.work.prim_ticks[p] - a.work.prim_ticks[p]));
        for (unsigned t = 0; t < 2; ++t) {
            for (prof::Zone z : kWorkerZones) {
                const unsigned zi = static_cast<unsigned>(z);
                std::fprintf(f, "\t%.3f", ms(b.tticks[t][zi] - a.tticks[t][zi]));
            }
            std::uint64_t busy = 0;
            for (unsigned z = 0; z < prof::kZones; ++z)
                if (z != static_cast<unsigned>(prof::Zone::GsWait)) busy += b.tticks[t][z] - a.tticks[t][z];
            std::fprintf(f, "\t%.3f", ms(busy));
        }
        for (unsigned t = 0; t < 2; ++t) {
            // a worker started or stopped inside the segment: its counter restarts (count from 0)
            const std::uint64_t c0 = a.cpu_cycles[t] <= b.cpu_cycles[t] ? a.cpu_cycles[t] : 0;
            std::fprintf(f, "\t%.3f", ms(b.cpu_cycles[t] - c0));
        }
        // CPU time (cycles at the TSC rate), the machine's busy share, the renderer, what is on screen.
        const double host_cpu = ms(b.thr_cyc - a.thr_cyc), proc_cpu = ms(b.proc_cyc - a.proc_cyc);
        std::fprintf(f, "\t%.3f\t%.3f\t%.3f", host_cpu, proc_cpu, std::max(0.0, proc_cpu - host_cpu));
        std::fprintf(f, "\t%llu\t%llu\t%llu\t%llu\t%.3f\t%.3f\t%.3f\t%llu", d(a.dev.r_submitted, b.dev.r_submitted),
                     d(a.dev.r_merged, b.dev.r_merged), d(a.dev.r_executed, b.dev.r_executed), d(a.dev.r_presented, b.dev.r_presented),
                     b.dev.r_busy_ms - a.dev.r_busy_ms, ms(d(a.dev.r_cycles, b.dev.r_cycles)), b.dev.r_gpu_ms - a.dev.r_gpu_ms,
                     d(a.dev.r_gpu_frames, b.dev.r_gpu_frames));
        std::fprintf(f, "\t%.3f", std::max(0.0, b.dev.r_wait_ms - a.dev.r_wait_ms));
        const bool same = i > 1 && b.dev.tasks == a.dev.tasks;
        std::fprintf(f, "\t%d\t%s\n", b.dev.movie ? 1 : 0, same ? "=" : (b.dev.tasks.empty() ? "-" : b.dev.tasks.c_str()));
    }
    // VU1 programs per segment: seg, key (guest address of the program's MPG DMAtag), name, runs, pairs, vu1 ms.
    std::fprintf(f, "# vu1\tseg\tkey\tname\truns\tpairs\tms\n");
    for (std::size_t i = 1; i < marks_.size(); ++i) {
        const Mark& a = marks_[i - 1];
        const Mark& b = marks_[i];
        for (std::size_t k = 0; k < b.vu_runs.size(); ++k) {
            const bool seen = k < a.vu_runs.size();
            const std::uint64_t r0 = seen ? a.vu_runs[k] : 0, p0 = seen ? a.vu_pairs[k] : 0, t0 = seen ? a.vu_ticks[k] : 0;
            if (b.vu_runs[k] == r0) continue;
            std::fprintf(f, "vu1\t%zu\t0x%06X\t%s\t%llu\t%llu\t%.3f\n", i - 1, s.vu_key[k], name ? name(s.vu_key[k]).c_str() : "",
                         static_cast<unsigned long long>(b.vu_runs[k] - r0), static_cast<unsigned long long>(b.vu_pairs[k] - p0),
                         ms(b.vu_ticks[k] - t0));
        }
    }
    std::fclose(f);
    write_frames(path + ".frames.tsv", qhz, hz);

    // Console: the whole run.
    std::uint64_t total = 0;
    for (unsigned z = 0; z < prof::kZones; ++z) total += last.ticks[z] - first.ticks[z];
    std::printf("p3fes: zones: %llu vblanks in %.2f s wall (%.3fx real time), %zu segments of %u vblanks -> %s\n",
                static_cast<unsigned long long>(last.vblank), wall,
                wall > 0 ? static_cast<double>(last.vblank) / kVblankHz / wall : 0.0, marks_.size() - 1, every_, path.c_str());
    for (unsigned z = 0; z < prof::kZones; ++z) {
        const std::uint64_t t = last.ticks[z] - first.ticks[z];
        if (!t) continue;
        std::printf("p3fes:   %-10s %10.1f ms  %5.1f%%  %12llu entries\n", prof::zone_name(z), ms(t),
                    total ? 100.0 * static_cast<double>(t) / static_cast<double>(total) : 0.0,
                    static_cast<unsigned long long>(s.entries[z]));
    }
    for (unsigned t = 0; t < prof::kProfThreads; ++t) {
        std::uint64_t tt = 0;
        for (unsigned z = 0; z < prof::kZones; ++z) tt += last.tticks[t][z] - first.tticks[t][z];
        if (!tt) continue;
        const char* nm = prof::g_prof_thread_names[t] ? prof::g_prof_thread_names[t] : "worker";
        std::printf("p3fes: zones of thread w%u (%s):\n", t, nm);
        for (unsigned z = 0; z < prof::kZones; ++z) {
            const std::uint64_t v = last.tticks[t][z] - first.tticks[t][z];
            if (!v) continue;
            std::printf("p3fes:   %-10s %10.1f ms  %5.1f%%\n", prof::zone_name(z), ms(v), 100.0 * static_cast<double>(v) / static_cast<double>(tt));
        }
    }
    return true;
}

// One row per game frame (flip): the wall time since the previous flip, the host thread's CPU time and the zone
// times in it. In an unpaced run that is the host's cost of the frame; paced, it is the presented frame interval.
void ZoneRecorder::write_frames(const std::string& path, double qhz, double hz) const {
    std::FILE* f = std::fopen(path.c_str(), "w");
    if (!f) {
        std::fprintf(stderr, "p3fes: cannot write %s\n", path.c_str());
        return;
    }
    auto ms = [hz](std::uint64_t t) { return 1e3 * static_cast<double>(t) / hz; };
    std::fprintf(f, "# p3fes --zones frames: one row per flip; wall_ms = QPC time since the previous flip, cpu_ms = host-thread"
                    " CPU time, zones in ms\n");
    std::fprintf(f, "flip\tvblank\twall_ms\tcpu_ms");
    for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(f, "\t%s", prof::zone_name(z));
    std::fprintf(f, "\n");
    for (std::size_t i = 1; i < frames_.size(); ++i) {
        const FrameRec& a = frames_[i - 1];
        const FrameRec& b = frames_[i];
        std::fprintf(f, "%llu\t%llu\t%.3f\t%.3f", static_cast<unsigned long long>(b.flips), static_cast<unsigned long long>(b.vblank),
                     1e3 * static_cast<double>(b.qpc - a.qpc) / qhz, ms(b.thr_cyc - a.thr_cyc));
        for (unsigned z = 0; z < prof::kZones; ++z) std::fprintf(f, "\t%.3f", ms(b.ticks[z] - a.ticks[z]));
        std::fprintf(f, "\n");
    }
    std::fclose(f);
}

} // namespace p3fes::app
