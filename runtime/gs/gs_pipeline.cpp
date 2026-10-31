// The threaded graphics pipeline (gs_pipeline.h): the EE side turns VIF1 / GIF work into an ordered command stream,
// the VU1 stage and the GS stage execute it in order on worker threads, and the EE waits only at the sync points.
#include "p3fes/gs/gs_pipeline.h"

#include "p3fes/gs/gif.h"
#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/vif1.h"
#include "p3fes/prof.h"
#include "p3fes/vu1/vu1_interp.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <intrin.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace p3fes::gs {

const char* to_string(SyncWhy w) noexcept {
    switch (w) {
    case SyncWhy::CsrRead: return "csr-read";
    case SyncWhy::SiglblidRead: return "siglblid-read";
    case SyncWhy::PrivWrite: return "priv-write";
    case SyncWhy::CsrReset: return "csr-reset";
    case SyncWhy::GifEvent: return "gif-event";
    case SyncWhy::ImrUnmasked: return "imr-unmasked-run";
    case SyncWhy::GifP1q: return "gif-p1q";
    case SyncWhy::GifTagRead: return "gif-tag-read";
    case SyncWhy::LocalRead: return "local-read";
    case SyncWhy::Host: return "host";
    case SyncWhy::Count: break;
    }
    return "?";
}

namespace {

// Command records: a 16-byte header, then the payload padded to 16 bytes (qword payloads stay aligned).
enum Op : u8 {
    kUnpack = 1, kMpg, kVuRun, kVuReset,                        // VU1 stage
    kGsTag, kGsReg, kGsPacked, kGsImage, kGsFn,                   // GS stage (the VU1 stage forwards them)
    kP1Flush, kP1Clear,                                           // VU1 stage: the PATH1 queue
    kP1Packet,                                                    // VU1 stage -> GS stage: one PATH1 packet
};
// kGsFn: a closure for the GS stage (aux = a heap std::function<void()>), from call_on_gs (EE) or emit_gs (VU1).

struct Hdr {
    u8 op = 0, path = 0;
    u16 pad = 0;
    u32 bytes = 0;  // payload bytes (unpadded)
    u64 aux = 0;
};
static_assert(sizeof(Hdr) == 16);

constexpr std::size_t pad16(std::size_t n) { return (n + 15u) & ~static_cast<std::size_t>(15u); }

struct VuRunRec {
    u32 op, imm, top, itop, code, queued;
    u64 step_limit;
};
struct MpgRec {
    u32 byte_off, pad;
    u64 src;
};
struct RegRec {
    u32 reg, pad;
    u64 value;
};
struct PackedRec {
    u32 desc, pad[3];
    u128 q;
};

bool is_event_reg(u32 reg) noexcept { return reg == reg::SIGNAL || reg == reg::FINISH || reg == reg::LABEL; }

thread_local bool t_on_worker = false;

std::uint64_t now_ns() {
    return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

// The A+D writes of one PATH1 packet, walked exactly as Gif::feed walks path 1 from a closed state (Gif::path1 always
// closes PATH1 after a packet): only PACKED A+D (descriptor 0xE) can reach SIGNAL / FINISH / LABEL.
template <class F>
void scan_ad(std::span<const u128> q, F&& on_ad) {
    bool in_tag = false;
    GifTag t{};
    u32 loop = 0, r = 0;
    std::size_t i = 0;
    const std::size_t n = q.size();
    while (i < n) {
        if (!in_tag) {
            t = GifTag::decode(q[i]);
            ++i;
            loop = 0;
            r = 0;
            in_tag = t.nloop != 0;
            continue;
        }
        switch (t.flg) {
        case 0:
            if (t.reg(r) == 0xEu) on_ad(q[i]);
            ++i;
            if (++r >= t.nreg) {
                r = 0;
                ++loop;
            }
            break;
        case 1:
            for (u32 half = 0; half < 2 && loop < t.nloop; ++half) {
                if (++r >= t.nreg) {
                    r = 0;
                    ++loop;
                }
            }
            ++i;
            break;
        default: {
            const std::size_t take = std::min<std::size_t>(n - i, t.nloop - loop);
            i += take;
            loop += static_cast<u32>(take);
            break;
        }
        }
        if (loop >= t.nloop) in_tag = false;
    }
}

} // namespace

// VU1 kicks on the VU1 stage: straight on as a PATH1 packet, or into the PATH1 queue when the run was made while the
// GIF was busy (Gif::path1's two cases).
class GsPipeline::KickSink final : public vu1::IGifSink {
public:
    explicit KickSink(GsPipeline& p) : p_(p) {}
    void kick(std::span<const u128> q) override {
        if (p_.run_queued_) {
            p_.p1_pending_.emplace_back(q.begin(), q.end());
            std::lock_guard<std::mutex> l(p_.evm_);
            p_.p1_pending_count_ = p_.p1_pending_.size();
            return;
        }
        p_.p1_packet(q, p_.run_seq_);
    }
    // A host stand-in's packet (Gif::path1_host's forms): queued like any kick while the GIF is busy (the queue is
    // flushed through path1), else marked for the GS stage's path1_host.
    void kick_host(std::span<const u128> q) override {
        if (p_.run_queued_) {
            kick(q);
            return;
        }
        p_.p1_packet(q, p_.run_seq_, true);
    }

private:
    GsPipeline& p_;
};

GsPipeline::GsPipeline(vu1::VU1Interpreter& vu, GsCore& core, Gif& gif, Vif1& vif, GsPrivRegs& priv,
                       vu1::IGifSink& sync_sink)
    : vu_(vu), core_(core), gif_(gif), vif_(vif), priv_(priv), sync_sink_(sync_sink), gif1_(core),
      kick_(std::make_unique<KickSink>(*this)) {}

GsPipeline::~GsPipeline() {
    stop();
    delete cur_;
    delete vu_out_;
    for (Batch* b : pool_) delete b;
}

bool GsPipeline::on_worker() noexcept { return t_on_worker; }

// ---- lifetime ---------------------------------------------------------------------------------------------------

void GsPipeline::start(const GsPipelineOptions& o) {
    if (running_) return;
    opt_ = o;
    if (opt_.threads > 2) opt_.threads = 2;
    opt_.batch_bytes = std::max<std::size_t>(opt_.batch_bytes, 4096);
    opt_.max_batches = std::max<std::size_t>(opt_.max_batches, 4);
    st_ = GsPipelineStats{};
    issued_ = 0;
    vu_done_ = 0;
    gs_done_ = 0;
    vq_.stop = gq_.stop = false;
    if (!cur_) cur_ = get_batch();
    cur_->n = 0;
    if (!vu_out_) vu_out_ = get_batch();
    vu_out_->n = 0;
    import_from_gif();
    vif_.set_pipe(this);
    gif_.set_pipe(this);
    priv_.set_pipe(this);
    vu_.set_sink(kick_.get());
    core_.set_events(nullptr);  // PATH2/PATH3 events: the EE side (event_now); PATH1: the VU1 stage's scan
    running_ = true;
    if (opt_.threads >= 1) vt_ = std::thread([this] { vu_thread(); });
    if (opt_.threads == 2) gt_ = std::thread([this] { gs_thread(); });
#if defined(_WIN32)
    if (vt_.joinable()) vt_handle_ = vt_.native_handle();
    if (gt_.joinable()) gt_handle_ = gt_.native_handle();
    prof::g_prof_thread_handles[0] = vt_handle_;
    prof::g_prof_thread_handles[1] = gt_handle_;
#endif
}

void GsPipeline::stop() {
    if (!running_) return;
    drain(SyncWhy::Host);
    {
        std::lock_guard<std::mutex> l(vq_.m);
        vq_.stop = true;
    }
    vq_.cv.notify_all();
    if (vt_.joinable()) vt_.join();
    {
        std::lock_guard<std::mutex> l(gq_.m);
        gq_.stop = true;
    }
    gq_.cv.notify_all();
    if (gt_.joinable()) gt_.join();
    vt_handle_ = gt_handle_ = nullptr;
    prof::g_prof_thread_handles[0] = prof::g_prof_thread_handles[1] = nullptr;
    export_to_gif();
    p1_pending_.clear();
    p1_pending_count_ = 0;
    gif_.clear_p1_pending();
    vif_.set_pipe(nullptr);
    gif_.set_pipe(nullptr);
    priv_.set_pipe(nullptr);
    vu_.set_sink(&sync_sink_);
    core_.set_events(&priv_);
    running_ = false;
}

void GsPipeline::import_from_gif() {
    auto& q = gif_.p1_queue();
    if (q.empty()) return;
    for (auto& pkt : q) p1_pending_.push_back(std::move(pkt));
    q.clear();
    p1_pending_count_ = p1_pending_.size();
    gif_.note_p1_queued();
}

void GsPipeline::export_to_gif() {
    if (running_) drain(SyncWhy::Host);
    auto& q = gif_.p1_queue();
    q.clear();
    for (const auto& pkt : p1_pending_) q.push_back(pkt);
    if (p1_tag_seq_ > gif_.last_tag_seq()) gif_.set_last_tag(p1_tag_, 1);
    // PATH1 counters of the GS stage's GIF, folded into the GIF's (statistics only).
    GifStats& a = gif_.mutable_stats();
    const GifStats& b = gif1_.stats();
    a.qwords[1] += b.qwords[1] - p1_stats_folded_.qwords[1];
    for (unsigned f = 0; f < 4; ++f) a.tags[1][f] += b.tags[1][f] - p1_stats_folded_.tags[1][f];
    a.path1_truncated += b.path1_truncated - p1_stats_folded_.path1_truncated;
    p1_stats_folded_ = b;
}

std::array<std::uint64_t, 2> GsPipeline::worker_cpu_ns() const {
    std::array<std::uint64_t, 2> r{};
#if defined(_WIN32)
    void* h[2] = {vt_handle_, gt_handle_};
    for (int i = 0; i < 2; ++i) {
        if (!h[i]) continue;
        FILETIME c, e, k, u;
        if (GetThreadTimes(static_cast<HANDLE>(h[i]), &c, &e, &k, &u)) {
            const auto ft = [](const FILETIME& f) { return (static_cast<std::uint64_t>(f.dwHighDateTime) << 32) | f.dwLowDateTime; };
            r[i] = (ft(k) + ft(u)) * 100u;
        }
    }
#endif
    return r;
}

// ---- EE side: batches ---------------------------------------------------------------------------------------------

GsPipeline::Batch* GsPipeline::get_batch() {
    {
        std::lock_guard<std::mutex> l(poolm_);
        if (!pool_.empty()) {
            Batch* b = pool_.back();
            pool_.pop_back();
            b->n = 0;
            return b;
        }
    }
    Batch* b = new Batch;
    b->buf.resize(opt_.batch_bytes + (64u << 10));
    return b;
}

void GsPipeline::free_batch(Batch* b) {
    b->n = 0;
    std::lock_guard<std::mutex> l(poolm_);
    pool_.push_back(b);
}

u8* GsPipeline::put(u8 op, u8 path, u32 payload) {
    const std::size_t need = sizeof(Hdr) + pad16(payload);
    if (cur_->n + need > cur_->buf.size()) {
        if (cur_->n) flush();
        if (need > cur_->buf.size()) cur_->buf.resize(need);
    }
    u8* p = cur_->buf.data() + cur_->n;
    Hdr h;
    h.op = op;
    h.path = path;
    h.bytes = payload;
    h.aux = ++seq_;
    std::memcpy(p, &h, sizeof h);
    cur_->n += need;
    ++st_.commands;
    st_.bytes += need;
    return p + sizeof(Hdr);
}

// Hands the current batch to the VU1 stage (threads 0: executes it here and now).
void GsPipeline::flush() {
    if (!cur_ || cur_->n == 0) return;
    cur_->index = ++issued_;
    ++st_.batches;
    if (opt_.threads == 0) {
        run_vu_batch(*cur_);
        const u64 idx = cur_->index;
        cur_->n = 0;
        publish_vu(idx);
        publish_gs(idx);
        return;
    }
    if (issued_ - gs_done_.load(std::memory_order_acquire) > opt_.max_batches) {
        ++st_.backpressure_waits;
        const std::uint64_t t0 = now_ns();
        const std::uint8_t z = prof::enter(prof::Zone::GsWait);
        std::unique_lock<std::mutex> l(progm_);
        progcv_.wait(l, [&] { return issued_ - gs_done_.load(std::memory_order_acquire) <= opt_.max_batches / 2; });
        l.unlock();
        prof::leave(z);
        st_.backpressure_ns += now_ns() - t0;
    }
    {
        std::lock_guard<std::mutex> l(vq_.m);
        vq_.q.push_back(cur_);
        vq_.n.store(vq_.q.size(), std::memory_order_release);
    }
    vq_.cv.notify_one();
    cur_ = get_batch();
}

void GsPipeline::wait_progress(const std::atomic<u64>& done, u64 target, SyncWhy why, bool count) {
    if (done.load(std::memory_order_acquire) >= target) return;
    const unsigned w = static_cast<unsigned>(why);
    if (count) ++st_.waits[w];
    const std::uint64_t t0 = now_ns();
    const std::uint8_t z = prof::enter(prof::Zone::GsWait);
    // A short spin first: most waits at the vblank are a fraction of a millisecond.
    for (int i = 0; i < 4000 && done.load(std::memory_order_acquire) < target; ++i) _mm_pause();
    if (done.load(std::memory_order_acquire) < target) {
        std::unique_lock<std::mutex> l(progm_);
        progcv_.wait(l, [&] { return done.load(std::memory_order_acquire) >= target; });
    }
    prof::leave(z);
    st_.wait_ns[w] += now_ns() - t0;
}

void GsPipeline::publish_vu(u64 index) {
    vu_done_.store(index, std::memory_order_release);
    { std::lock_guard<std::mutex> l(progm_); }
    progcv_.notify_all();
}

void GsPipeline::publish_gs(u64 index) {
    gs_done_.store(index, std::memory_order_release);
    { std::lock_guard<std::mutex> l(progm_); }
    progcv_.notify_all();
}

// ---- EE side: sync points -----------------------------------------------------------------------------------------

void GsPipeline::sync_vu(SyncWhy why) {
    if (!running_ || t_on_worker) return;
    ++st_.syncs[static_cast<unsigned>(why)];
    if (opt_.speculate_csr && why == SyncWhy::CsrRead) {
        flush();
        ++st_.speculated_reads;
        check_spec();
        return;
    }
    flush();
    wait_progress(vu_done_, issued_, why, true);
    apply_events_and_traps();
}

void GsPipeline::drain(SyncWhy why) {
    if (!running_ || t_on_worker) return;
    ++st_.syncs[static_cast<unsigned>(why)];
    flush();
    const bool behind = vu_done_.load(std::memory_order_acquire) < issued_ || gs_done_.load(std::memory_order_acquire) < issued_;
    if (behind) ++st_.waits[static_cast<unsigned>(why)];
    wait_progress(vu_done_, issued_, why, false);
    wait_progress(gs_done_, issued_, why, false);
    apply_events_and_traps();
}

void GsPipeline::check_spec() {
    bool failed;
    {
        std::lock_guard<std::mutex> l(evm_);
        failed = spec_failed_;
    }
    if (!failed) return;
    const char* msg = "gs-threads: a PATH1 packet wrote SIGNAL / FINISH / LABEL while CSR reads were speculated "
                      "(--gs-speculate): the run is not exact any more; run without --gs-speculate";
    if (on_fail_) on_fail_(msg);
    std::fprintf(stderr, "p3fes: %s\n", msg);
    std::abort();
}

void GsPipeline::apply_events_and_traps() {
    if (opt_.speculate_csr) check_spec();
    std::vector<Event> ev;
    std::vector<VifTrap> tr;
    {
        std::lock_guard<std::mutex> l(evm_);
        if (events_.empty() && traps_.empty()) return;
        ev.swap(events_);
        tr.swap(traps_);
    }
    for (const Event& e : ev) {
        if (e.reg == reg::SIGNAL) priv_.on_signal(static_cast<u32>(e.value), static_cast<u32>(e.value >> 32));
        else if (e.reg == reg::FINISH) priv_.on_finish();
        else priv_.on_label(static_cast<u32>(e.value), static_cast<u32>(e.value >> 32));
    }
    for (const VifTrap& t : tr) vif_.report_trap(t);  // may not return (fatal): no lock held
}

std::size_t GsPipeline::p1_queued() {
    sync_vu(SyncWhy::GifP1q);
    std::lock_guard<std::mutex> l(evm_);
    return p1_pending_count_;
}

bool GsPipeline::p1_last_tag(u64 after_seq, u32 tag[4]) {
    drain(SyncWhy::GifTagRead);
    if (p1_tag_seq_ <= after_seq) return false;
    std::memcpy(tag, p1_tag_, sizeof p1_tag_);
    return true;
}

// A PATH2/PATH3 SIGNAL / FINISH / LABEL write: PATH1 events made visible before it go first, then this one, here.
void GsPipeline::event_now(u32 reg, u64 value) {
    sync_vu(SyncWhy::GifEvent);
    if (reg == reg::SIGNAL) priv_.on_signal(static_cast<u32>(value), static_cast<u32>(value >> 32));
    else if (reg == reg::FINISH) priv_.on_finish();
    else priv_.on_label(static_cast<u32>(value), static_cast<u32>(value >> 32));
}

// ---- EE side: producers -------------------------------------------------------------------------------------------

void GsPipeline::unpack(const UnpackArgs& a, const u32* words, std::size_t n) {
    u8* p = put(kUnpack, 0, static_cast<u32>(sizeof(UnpackArgs) + n * 4u));
    std::memcpy(p, &a, sizeof a);
    if (n) std::memcpy(p + sizeof a, words, n * 4u);
    if (cur_->n >= opt_.batch_bytes) flush();
}

void GsPipeline::mpg(u32 byte_off, const u32* words, std::size_t n, const void* src) {
    u8* p = put(kMpg, 0, static_cast<u32>(sizeof(MpgRec) + n * 4u));
    MpgRec r{byte_off, 0, reinterpret_cast<std::uintptr_t>(src)};
    std::memcpy(p, &r, sizeof r);
    if (n) std::memcpy(p + sizeof r, words, n * 4u);
    if (cur_->n >= opt_.batch_bytes) flush();
}

u32* GsPipeline::unpack_reserve(const UnpackArgs& a, u32 nwords) {
    u8* p = put(kUnpack, 0, static_cast<u32>(sizeof(UnpackArgs) + nwords * 4u));
    std::memcpy(p, &a, sizeof a);
    return reinterpret_cast<u32*>(p + sizeof a);  // 4-byte aligned: payloads start 16-aligned, UnpackArgs is 52 bytes
}

u32* GsPipeline::mpg_reserve(u32 byte_off, u32 nwords, const void* src) {
    u8* p = put(kMpg, 0, static_cast<u32>(sizeof(MpgRec) + nwords * 4u));
    MpgRec r{byte_off, 0, reinterpret_cast<std::uintptr_t>(src)};
    std::memcpy(p, &r, sizeof r);
    return reinterpret_cast<u32*>(p + sizeof r);
}

void GsPipeline::reserve_done() {
    if (cur_->n >= opt_.batch_bytes) flush();
}

void GsPipeline::vu_run(u32 op, u32 imm, u32 top, u32 itop, u32 code, u64 step_limit) {
    // Gif::path1: kicks run at once when the GIF is idle, else they queue until run_path1_queue.
    const bool queued = gif_.active_path() != 0;
    if (queued) {
        gif_.note_p1_queued();
        ++st_.vu_runs_queued;
    }
    ++st_.vu_runs;
    u8* p = put(kVuRun, 0, sizeof(VuRunRec));
    VuRunRec r{op, imm, top, itop, code, queued ? 1u : 0u, step_limit};
    std::memcpy(p, &r, sizeof r);
    if ((priv_.imr() & 0x300u) != 0x300u) sync_vu(SyncWhy::ImrUnmasked);  // SIGNAL / FINISH may interrupt
    else if (cur_->n >= opt_.batch_bytes) flush();
}

void GsPipeline::vu_reset() {
    put(kVuReset, 0, 0);
}

void GsPipeline::gs_tag(u32 path) {
    put(kGsTag, static_cast<u8>(path), 0);
}

void GsPipeline::gs_reg(u32 path, u32 reg, u64 value) {
    if (is_event_reg(reg)) event_now(reg, value);
    u8* p = put(kGsReg, static_cast<u8>(path), sizeof(RegRec));
    RegRec r{reg, 0, value};
    std::memcpy(p, &r, sizeof r);
}

void GsPipeline::gs_packed(u32 path, u32 desc, const u128& q) {
    if ((desc & 0xFu) == 0xEu && is_event_reg(q.u8[8])) event_now(q.u8[8], q.u64[0]);
    u8* p = put(kGsPacked, static_cast<u8>(path), sizeof(PackedRec));
    PackedRec r{};
    r.desc = desc;
    r.q = q;
    std::memcpy(p, &r, sizeof r);
}

void GsPipeline::gs_image(u32 path, std::span<const u128> q) {
    u8* p = put(kGsImage, static_cast<u8>(path), static_cast<u32>(q.size() * 16u));
    if (!q.empty()) std::memcpy(p, q.data(), q.size() * 16u);
    if (cur_->n >= opt_.batch_bytes) flush();
}

void GsPipeline::p1_flush() {
    put(kP1Flush, 0, 0);
}

void GsPipeline::p1_clear() {
    put(kP1Clear, 0, 0);
}

void GsPipeline::call_on_gs(std::function<void()> f) {
    if (!running_) {
        f();
        return;
    }
    u8* p = put(kGsFn, 0, 0);
    (void)p;
    // the closure rides in the header's aux field (put() set aux = the command number: overwrite it)
    Hdr h;
    std::memcpy(&h, p - sizeof(Hdr), sizeof h);
    h.aux = reinterpret_cast<std::uintptr_t>(new std::function<void()>(std::move(f)));
    std::memcpy(p - sizeof(Hdr), &h, sizeof h);
    flush();  // the vblank: hand everything over
}

// ---- VU1 stage ----------------------------------------------------------------------------------------------------

// The next batch of a stage's queue (nullptr: stopped and empty). Spins ~20 us before sleeping: the EE hands batches
// over every few hundred microseconds while it renders, and a condition-variable wake-up costs more than that spin.
GsPipeline::Batch* GsPipeline::pop(Queue& q) {
    const std::uint8_t z = prof::enter(prof::Zone::GsWait);
    for (int i = 0; i < 2000 && q.n.load(std::memory_order_acquire) == 0; ++i) _mm_pause();
    std::unique_lock<std::mutex> l(q.m);
    q.cv.wait(l, [&] { return !q.q.empty() || q.stop; });
    prof::leave(z);
    if (q.q.empty()) return nullptr;
    Batch* b = q.q.front();
    q.q.pop_front();
    q.n.store(q.q.size(), std::memory_order_release);
    return b;
}

void GsPipeline::vu_thread() {
    t_on_worker = true;
    prof::t_prof = &prof::g_prof_threads[0];
    prof::g_prof_thread_names[0] = opt_.threads == 2 ? "gfx-vu1" : "gfx";
#if defined(_WIN32)
    SetThreadDescription(GetCurrentThread(), opt_.threads == 2 ? L"p3fes gfx VU1" : L"p3fes gfx");
#endif
    for (;;) {
        Batch* b = pop(vq_);
        if (!b) break;
        run_vu_batch(*b);
        const u64 idx = b->index;
        free_batch(b);
        if (opt_.threads == 2) {
            vu_out_->index = idx;
            {
                std::lock_guard<std::mutex> l(gq_.m);
                gq_.q.push_back(vu_out_);
                gq_.n.store(gq_.q.size(), std::memory_order_release);
            }
            gq_.cv.notify_one();
            vu_out_ = get_batch();
            publish_vu(idx);
        } else {
            publish_vu(idx);
            publish_gs(idx);
        }
    }
}

void GsPipeline::run_vu_batch(Batch& b) {
    const prof::Scope zone(prof::Zone::Vif1);
    std::size_t off = 0;
    while (off < b.n) {
        const u8* rec = b.buf.data() + off;
        Hdr h;
        std::memcpy(&h, rec, sizeof h);
        const u8* p = rec + sizeof(Hdr);
        off += sizeof(Hdr) + pad16(h.bytes);
        switch (h.op) {
        case kUnpack: {
            UnpackArgs a;
            std::memcpy(&a, p, sizeof a);
            const std::size_t n = (h.bytes - sizeof a) / 4u;
            u32 row[4];
            std::memcpy(row, a.row, sizeof row);
            const u32* words = reinterpret_cast<const u32*>(p + sizeof a);
            u32 vectors = 0;
            IVuRunHook* uh = vif_.run_hook();
            if (!(uh && uh->unpack(a, words, n, vu_.state().data, row, vectors))) vif_unpack(a, words, n, vu_.state().data, row);
            break;
        }
        case kMpg: {
            MpgRec r;
            std::memcpy(&r, p, sizeof r);
            const std::size_t bytes = h.bytes - sizeof r;
            vu_.load_micro(r.byte_off, std::span<const u8>(p + sizeof r, bytes));
            prof::vu1_mpg(r.byte_off / 8u, static_cast<u32>(bytes / 8u), reinterpret_cast<const void*>(r.src));
            break;
        }
        case kVuRun: {
            VuRunRec r;
            std::memcpy(&r, p, sizeof r);
            run_queued_ = r.queued != 0;
            run_seq_ = h.aux;
            vu_.set_tops(r.top, r.itop);
            IVuRunHook* hook = vif_.run_hook();
            VuRunInfo info;
            if (hook) [[unlikely]] {  // the native renderer (play mode): may draw the batch itself
                info.op = r.op;
                info.imm = r.imm;
                info.top = r.top;
                info.itop = r.itop;
                info.gif_busy = r.queued != 0;
                bool handled;
                {
                    const prof::Scope vz(prof::Zone::Vu1);
                    handled = hook->run(info, vu_);
                }
                if (handled) {
                    vif_.note_hooked_run();
                    run_queued_ = false;
                    break;  // the VU1 did not run
                }
            }
            const u32 start_pair = r.op == 0x17 ? vu_.state().tpc / 8u : r.imm;
            const u64 t0 = prof::cur().ticks[static_cast<unsigned>(prof::Zone::Vu1)];
            vu1::RunResult res;
            {
                const prof::Scope vz(prof::Zone::Vu1);
                if (r.op == 0x17) res = vu_.mscnt(r.step_limit);
                else if (r.op == 0x15) res = vu_.mscalf(r.imm, r.step_limit);
                else res = vu_.mscal(r.imm, r.step_limit);
            }
            prof::vu1_run(start_pair, res.steps, prof::cur().ticks[static_cast<unsigned>(prof::Zone::Vu1)] - t0);
            vif_.add_vu_pairs(res.steps);
            if (hook) [[unlikely]]
                hook->after_exact(info, vu_);
            if (res.status == vu1::RunStatus::Trapped || res.status == vu1::RunStatus::StepLimit) {
                VifTrap t;
                t.kind = res.status == vu1::RunStatus::Trapped ? VifTrapKind::VuTrap : VifTrapKind::VuStepLimit;
                t.code = r.code;
                if (res.status == vu1::RunStatus::Trapped) t.vu = vu_.trap();
                std::lock_guard<std::mutex> l(evm_);
                traps_.push_back(t);
            }
            run_queued_ = false;
            break;
        }
        case kVuReset: vu_.reset(); break;
        case kP1Flush:
            for (const auto& pkt : p1_pending_) p1_packet(pkt, h.aux);
            p1_pending_.clear();
            {
                std::lock_guard<std::mutex> l(evm_);
                p1_pending_count_ = 0;
            }
            break;
        case kP1Clear:
            p1_pending_.clear();
            {
                std::lock_guard<std::mutex> l(evm_);
                p1_pending_count_ = 0;
            }
            break;
        default: gs_record(rec); break;
        }
    }
}

// A PATH1 packet becomes visible to the GS: its SIGNAL / FINISH / LABEL writes are recorded for the EE (applied at
// its next sync point), the packet goes to the GS stage.
void GsPipeline::p1_packet(std::span<const u128> q, u64 seq, bool host) {
    p1_packets_.fetch_add(1, std::memory_order_relaxed);
    scan_ad(q, [&](const u128& d) {
        if (!is_event_reg(d.u8[8])) return;
        p1_events_.fetch_add(1, std::memory_order_relaxed);
        std::lock_guard<std::mutex> l(evm_);
        events_.push_back(Event{d.u8[8], d.u64[0]});
        if (opt_.speculate_csr) spec_failed_ = true;
    });
    if (opt_.threads != 2) {
        exec_p1(q, seq, host);
        return;
    }
    const std::size_t need = sizeof(Hdr) + q.size() * 16u;
    if (vu_out_->n + need > vu_out_->buf.size()) vu_out_->buf.resize(std::max(vu_out_->buf.size() * 2, vu_out_->n + need));
    Hdr h;
    h.op = kP1Packet;
    h.pad = host ? 1u : 0u;
    h.bytes = static_cast<u32>(q.size() * 16u);
    h.aux = seq;
    u8* p = vu_out_->buf.data() + vu_out_->n;
    std::memcpy(p, &h, sizeof h);
    if (!q.empty()) std::memcpy(p + sizeof h, q.data(), q.size() * 16u);
    vu_out_->n += need;
}

void GsPipeline::emit_gs(std::function<void()> f) {
    if (opt_.threads != 2 || !running_) {
        f();
        return;
    }
    const std::size_t need = sizeof(Hdr);
    if (vu_out_->n + need > vu_out_->buf.size()) vu_out_->buf.resize(std::max(vu_out_->buf.size() * 2, vu_out_->n + need));
    Hdr h;
    h.op = kGsFn;
    h.aux = reinterpret_cast<std::uintptr_t>(new std::function<void()>(std::move(f)));
    std::memcpy(vu_out_->buf.data() + vu_out_->n, &h, sizeof h);
    vu_out_->n += need;
}

// A GS command reaching the VU1 stage: forwarded in order (threads 2) or executed here.
void GsPipeline::gs_record(const u8* rec) {
    Hdr h;
    std::memcpy(&h, rec, sizeof h);
    if (opt_.threads != 2) {
        const prof::Scope z(prof::Zone::Gif);
        run_gs_record(rec);
        return;
    }
    const std::size_t need = sizeof(Hdr) + pad16(h.bytes);
    if (vu_out_->n + need > vu_out_->buf.size()) vu_out_->buf.resize(std::max(vu_out_->buf.size() * 2, vu_out_->n + need));
    std::memcpy(vu_out_->buf.data() + vu_out_->n, rec, need);
    vu_out_->n += need;
}

// ---- GS stage -----------------------------------------------------------------------------------------------------

void GsPipeline::gs_thread() {
    t_on_worker = true;
    prof::t_prof = &prof::g_prof_threads[1];
    prof::g_prof_thread_names[1] = "gfx-gs";
#if defined(_WIN32)
    SetThreadDescription(GetCurrentThread(), L"p3fes gfx GS");
#endif
    for (;;) {
        Batch* b = pop(gq_);
        if (!b) break;
        {
            const prof::Scope zone(prof::Zone::Gif);
            std::size_t off = 0;
            while (off < b->n) {
                const u8* rec = b->buf.data() + off;
                Hdr h;
                std::memcpy(&h, rec, sizeof h);
                off += sizeof(Hdr) + pad16(h.bytes);
                run_gs_record(rec);
            }
        }
        const u64 idx = b->index;
        free_batch(b);
        publish_gs(idx);
    }
}

void GsPipeline::run_gs_record(const u8* rec) {
    Hdr h;
    std::memcpy(&h, rec, sizeof h);
    const u8* p = rec + sizeof(Hdr);
    gs_path_.store(h.path, std::memory_order_relaxed);
    switch (h.op) {
    case kGsTag: core_.on_gif_tag(); break;
    case kGsReg: {
        RegRec r;
        std::memcpy(&r, p, sizeof r);
        core_.write_reg(r.reg, r.value);
        break;
    }
    case kGsPacked: {
        PackedRec r;
        std::memcpy(&r, p, sizeof r);
        core_.write_packed(r.desc, r.q);
        break;
    }
    case kGsImage:
        core_.write_image(std::span<const u128>(reinterpret_cast<const u128*>(p), h.bytes / 16u));
        break;
    case kP1Packet:
        exec_p1(std::span<const u128>(reinterpret_cast<const u128*>(p), h.bytes / 16u), h.aux, h.pad != 0);
        break;
    case kGsFn: {
        auto* f = reinterpret_cast<std::function<void()>*>(static_cast<std::uintptr_t>(h.aux));
        (*f)();
        delete f;
        break;
    }
    default: break;
    }
    gs_path_.store(0, std::memory_order_relaxed);
}

void GsPipeline::exec_p1(std::span<const u128> q, u64 seq, bool host) {
    gs_path_.store(1, std::memory_order_relaxed);
    if (!host || !gif1_.path1_host(q)) gif1_.path1(q);
    gs_path_.store(0, std::memory_order_relaxed);
    if (!q.empty()) {
        p1_tag_seq_ = seq;
        for (u32 w = 0; w < 4; ++w) p1_tag_[w] = gif1_.read_reg(0x40u + 16u * w);
    }
}

} // namespace p3fes::gs
