// The threaded graphics pipeline: VIF1's VU1 work and the GS front end on worker threads behind the EE, with the
// EE waiting only where it can observe them (docs/ANALYSIS/23 §7; docs/ANALYSIS/32_threaded_graphics.md).
//
//   EE thread    guest code, DMAC, VIF1 codes + registers + stalls + interrupts, GIF arbitration and PATH2/PATH3 tag
//                walking, GS privileged registers                       -> commands (gs_pipe.h), in guest order
//   VU1 stage    UNPACK / MPG into VU1 memory, VU1 runs (MSCAL/MSCALF/MSCNT), their XGKICKs: PATH1 packets, the
//                PATH1 queue (kicks while the GIF was busy), the SIGNAL/FINISH/LABEL writes in PATH1 packets
//   GS stage     the GsCore calls of PATH2/PATH3 and the PATH1 packets in that same order (GsCore front end, the
//                software rasteriser or the D3D11 op recorder), and the op-list hand-off at every vblank marker
//
// Threads: `threads` = 2 runs the two stages on two workers (EE -> VU1 worker -> GS worker), 1 runs both on one
// worker, 0 runs them on the EE thread at every hand-off ("inline": the command stream without threads, a test of
// the encoding). Each stage executes its commands in order on the objects the synchronous model uses (the
// VU1Interpreter, GsCore, a Gif used for PATH1 packets only), so the result is the synchronous model's, whatever the
// threads' timing.
//
// Sync rules (what the EE can observe of the stages, and what it waits for there; everything else never waits):
//   * GS CSR / SIGLBLID reads, CSR / IMR / SIGLBLID writes: the VU1 stage catches up (sync_vu) and the SIGNAL /
//     FINISH / LABEL writes its PATH1 packets made visible are applied to the privileged registers, in order. PATH2 /
//     PATH3 event writes are applied by the EE itself at their place in the stream (after a sync_vu). While IMR lets
//     SIGNAL or FINISH interrupt, every VU1 run is followed by a sync_vu (interrupts are raised where the
//     synchronous model raises them). The GS stage is never waited for here: it cannot change CSR.
//   * GIF_STAT.P1Q, only while a run kicked into the PATH1 queue: sync_vu. GIF TAG0-3 / CNT: drain.
//   * Local -> host data (VIF1 FIFO / channel 1 with BUSDIR = 1), CSR.RESET: drain (all stages idle), then the EE
//     thread executes the access on the GsCore itself.
//   * VU1 traps (fail closed) are reported at the next sync_vu (at the latest the next vblank's CSR read).
//   * The host drains before it touches GS state (snapshots, machine states, the CRTC compose, stopping).
// What never needs a sync: VIF1 registers, stalls and interrupts, FLUSHA, MSKPATH3, DMAC completion timing (all EE
// side: they depend on PATH2/PATH3 arbitration, which PATH1 never changes in the synchronous model), VPU_STAT (reads
// 0), the D3D11 op lists (handed to the renderer by the GS stage at the vblank marker the EE queued).
#pragma once

#include "p3fes/gs/gif.h"
#include "p3fes/gs/gs_pipe.h"
#include "p3fes/gs/gs_priv.h"
#include "p3fes/gs/vif1.h"

#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace p3fes::gs {

struct GsPipelineOptions {
    unsigned threads = 2;                 // 2: VU1 worker + GS worker; 1: one worker; 0: inline on the EE thread
    std::size_t batch_bytes = 32u << 10;  // the EE hands a batch over when it holds this much (and at every sync)
    std::size_t max_batches = 1024;       // batches in flight before the EE waits (back pressure)
    // Opt-in, NOT the exact default: a GS CSR read does not wait for the VU1 stage; it answers as if the VU1 work in
    // flight wrote no SIGNAL / FINISH (true on every recorded route: 0 PATH1 events). The first PATH1 SIGNAL / FINISH
    // / LABEL write the VU1 stage meets stops the run (fail closed: `on_fail`), because the guest may have read CSR
    // before it. Lets the VU1 stage run across vblanks instead of catching up at every vblank handler's CSR read.
    bool speculate_csr = false;
};

struct GsPipelineStats {
    std::uint64_t commands = 0, batches = 0, bytes = 0;
    std::uint64_t vu_runs = 0, vu_runs_queued = 0;  // VU1 runs; of those, kicked while the GIF was busy
    std::uint64_t p1_packets = 0, p1_events = 0;    // PATH1 packets; SIGNAL/FINISH/LABEL writes in them
    std::uint64_t syncs[static_cast<unsigned>(SyncWhy::Count)] = {};  // sync points reached
    std::uint64_t waits[static_cast<unsigned>(SyncWhy::Count)] = {};  // ... of which had to wait for a worker
    std::uint64_t wait_ns[static_cast<unsigned>(SyncWhy::Count)] = {};
    std::uint64_t backpressure_waits = 0, backpressure_ns = 0;
    std::uint64_t speculated_reads = 0;  // CSR reads answered without waiting (speculate_csr)
};

class GsPipeline final : public GsPipe {
public:
    // The objects the stages run on (GsSystem's). `priv` receives PATH1 events on the EE thread.
    GsPipeline(vu1::VU1Interpreter& vu, GsCore& core, Gif& gif, Vif1& vif, GsPrivRegs& priv, vu1::IGifSink& sync_sink);
    ~GsPipeline() override;
    GsPipeline(const GsPipeline&) = delete;
    GsPipeline& operator=(const GsPipeline&) = delete;

    // Starts the workers and routes VIF1 / GIF / the privileged registers / VU1 kicks through the pipeline. A PATH1
    // queue the GIF holds (a loaded machine state) moves to the VU1 stage.
    void start(const GsPipelineOptions& o);
    // Drains, joins the workers and gives everything back to the synchronous model (the PATH1 queue to the GIF).
    void stop();
    bool running() const noexcept { return running_; }
    unsigned threads() const noexcept { return opt_.threads; }

    // EE / host thread: run `f` on the GS stage after every GS command queued before it (the vblank op-list hand-off,
    // GameHost::end_vblank_slice), and hand the batch over. threads 0: now.
    void call_on_gs(std::function<void()> f);
    // The VU1 run hook (Vif1::set_run_hook, track E's native renderer) is consulted on the VU1 stage before every run,
    // with the run's inputs (VuRunInfo::gif_busy = the run's kicks would queue); `after_exact` follows the runs it
    // declined. Its GS-side work goes through emit_gs, never straight into GS-stage objects (the op recorder): the GS
    // worker may still be executing earlier commands. From the VU1 stage: run `f` on the GS stage at this point of
    // the stream (threads 0 / 1: now). Without the pipeline the caller just runs it.
    void emit_gs(std::function<void()> f);
    // speculate_csr failed (called on the EE thread at a sync point; expected not to return). Default: abort.
    void set_fail_handler(std::function<void(const char*)> f) { on_fail_ = std::move(f); }
    // The GIF path of the GsCore call the GS stage is executing (the host's GS register observer); 0 outside one.
    u32 gs_path() const noexcept { return gs_path_.load(std::memory_order_relaxed); }
    // True on a pipeline worker thread (the host must not drain from there).
    static bool on_worker() noexcept;
    // Machine states: drain, then put the VU1 stage's PATH1 queue and PATH1 last tag into the GIF (save), or take a
    // loaded queue from it (load).
    void export_to_gif();
    void import_from_gif();

    const GsPipelineStats& stats() const noexcept { return st_; }
    std::uint64_t p1_packets() const noexcept { return p1_packets_.load(std::memory_order_relaxed); }
    std::uint64_t p1_events() const noexcept { return p1_events_.load(std::memory_order_relaxed); }
    const GifStats& p1_gif_stats() const noexcept { return gif1_.stats(); }
    u64 p1_host_packets() const noexcept { return gif1_.host_packets(); }  // Gif::path1_host on the GS stage
    // Worker CPU time so far (thread times, ns): [0] VU1 worker (or the single worker), [1] GS worker.
    std::array<std::uint64_t, 2> worker_cpu_ns() const;

    // ---- GsPipe ------------------------------------------------------------------------------------------------
    void unpack(const UnpackArgs& a, const u32* words, std::size_t n) override;
    void mpg(u32 byte_off, const u32* words, std::size_t n, const void* src) override;
    u32* unpack_reserve(const UnpackArgs& a, u32 nwords) override;
    u32* mpg_reserve(u32 byte_off, u32 nwords, const void* src) override;
    void reserve_done() override;
    void vu_run(u32 op, u32 imm, u32 top, u32 itop, u32 code, u64 step_limit) override;
    void vu_reset() override;
    void gs_tag(u32 path) override;
    void gs_reg(u32 path, u32 reg, u64 value) override;
    void gs_packed(u32 path, u32 desc, const u128& q) override;
    void gs_image(u32 path, std::span<const u128> q) override;
    void p1_flush() override;
    void p1_clear() override;
    u64 seq() const noexcept override { return seq_; }
    void sync_vu(SyncWhy why) override;
    void drain(SyncWhy why) override;
    std::size_t p1_queued() override;
    bool p1_last_tag(u64 after_seq, u32 tag[4]) override;

private:
    struct Batch {
        std::vector<u8> buf;
        std::size_t n = 0;
        u64 index = 0;  // EE batch number this batch carries (GS batches: the EE batch they came from)
    };
    struct Queue {
        std::mutex m;
        std::condition_variable cv;
        std::deque<Batch*> q;
        bool stop = false;
        std::atomic<std::size_t> n{0};  // q.size(), for the worker's spin before it sleeps
    };
    struct Event {
        u32 reg = 0;
        u64 value = 0;
    };
    class KickSink;

    // EE side
    u8* put(u8 op, u8 path, u32 payload);
    void flush();
    void wait_progress(const std::atomic<u64>& done, u64 target, SyncWhy why, bool count);
    void apply_events_and_traps();
    void event_now(u32 reg, u64 value);
    Batch* get_batch();
    void free_batch(Batch* b);

    // stages
    void vu_thread();
    void gs_thread();
    void run_vu_batch(Batch& b);
    void gs_record(const u8* rec);      // VU1 stage: forward a GS command (threads 2) or execute it
    void run_gs_record(const u8* rec);  // GS stage
    void p1_packet(std::span<const u128> q, u64 seq, bool host = false);  // host: a kick_host packet (path1_host first)
    void exec_p1(std::span<const u128> q, u64 seq, bool host = false);
    void publish_vu(u64 index);
    void publish_gs(u64 index);

    vu1::VU1Interpreter& vu_;
    GsCore& core_;
    Gif& gif_;
    Vif1& vif_;
    GsPrivRegs& priv_;
    vu1::IGifSink& sync_sink_;
    Gif gif1_;  // PATH1 packets on the GS stage (its owner is always idle there)
    GifStats p1_stats_folded_{};
    std::unique_ptr<KickSink> kick_;
    GsPipelineOptions opt_{};
    bool running_ = false;
    std::function<void(const char*)> on_fail_;
    void check_spec();
    Batch* pop(Queue& q);

    // EE side
    Batch* cur_ = nullptr;
    u64 seq_ = 0;     // commands issued
    u64 issued_ = 0;  // batches handed to the VU1 stage
    GsPipelineStats st_{};

    // VU1 stage (only its thread touches these while running, except what is under evm_)
    std::vector<std::vector<u128>> p1_pending_;  // kicks of runs made while the GIF was busy
    std::size_t p1_pending_count_ = 0;          // published copy for p1_queued (under evm_)
    bool run_queued_ = false;
    u64 run_seq_ = 0;
    Batch* vu_out_ = nullptr;  // the batch being filled for the GS stage (threads 2)
    std::mutex evm_;
    std::vector<Event> events_;   // PATH1 SIGNAL/FINISH/LABEL writes not yet applied (under evm_)
    std::vector<VifTrap> traps_;  // VU1 traps not yet reported (under evm_)
    std::atomic<u64> p1_packets_{0}, p1_events_{0};
    bool spec_failed_ = false;  // speculate_csr: a PATH1 event was met (under evm_)

    // GS stage
    std::atomic<u32> gs_path_{0};
    u64 p1_tag_seq_ = 0;  // command number of the last PATH1 packet fed (its tags are the GS stage's last)
    u32 p1_tag_[4] = {};

    Queue vq_, gq_;
    std::mutex poolm_;
    std::vector<Batch*> pool_;
    std::atomic<u64> vu_done_{0}, gs_done_{0};
    std::mutex progm_;
    std::condition_variable progcv_;
    std::thread vt_, gt_;
    void* vt_handle_ = nullptr;
    void* gt_handle_ = nullptr;
};

} // namespace p3fes::gs
