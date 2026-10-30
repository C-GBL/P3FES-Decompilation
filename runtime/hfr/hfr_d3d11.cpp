// The high-frame-rate interpolator on the D3D11 render thread (hfr_d3d11.h; docs/ANALYSIS/32_high_frame_rate.md §5).
#include "hfr_d3d11.h"

#include "p3fes/gs/gs_d3d11_hlsl.h"
#include "p3fes/gs/gs_output.h"

#include <d3dcompiler.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>

namespace p3fes::hfr {

using Microsoft::WRL::ComPtr;

struct HfrInterpolator::Gpu {
    ID3D11Device* dev = nullptr;
    ComPtr<ID3D11VertexShader> vs;
    ComPtr<ID3D11PixelShader> ps;
    ComPtr<ID3D11SamplerState> smp;
    struct Timer {
        ComPtr<ID3D11Query> disjoint, t0, t1;
        bool pending = false;
    };
    std::array<Timer, 6> timers;
    u32 next_timer = 0;
    bool failed = false;
};

HfrInterpolator::HfrInterpolator(const HfrOptions& o) : o_(o) {
    for (u32 i = 0; i < kFrames; ++i) f_[i].bank = i;
}
HfrInterpolator::~HfrInterpolator() = default;

HfrInterpolator::Frame* HfrInterpolator::find(u64 tag) {
    for (Frame& f : f_)
        if (f.valid && f.tag == tag) return &f;
    return nullptr;
}

void HfrInterpolator::on_reset() {
    for (Frame& f : f_) {
        f.valid = false;
        f.tainted = true;
    }
    m_a_ = m_b_ = work_tag_ = ~0ull;
}

void HfrInterpolator::before_execute(gs::GsD3D11Executor& ex, const gs::OpList& ops, const gs::DisplayRegs& disp,
                                     const gs::PresentPlan& plan) {
    if (!banks_ok_) {
        banks_ok_ = ex.create_banks(kFrames + 1);
        if (!banks_ok_) return;
        scratch_bank_ = kFrames;
    }
    // A list the renderer merged (it fell behind) may span a frame boundary: neither side is replayable.
    const bool merged = plan.merged != 0;
    if (merged && open_ >= 0) f_[static_cast<std::size_t>(open_)].tainted = true;
    if (plan.mode == gs::PresentPlan::Mode::Latch) {
        // The flip of frame `plan.tag` happened at this slice's start: the open record is that frame, complete.
        // A Latch without a new flip (the presenter also shows display-register changes and static screens every
        // second vblank): no frame boundary in the GS stream, so the pictures with this tag are not interpolable.
        const bool no_flip = have_last_tag_ && plan.tag == last_tag_;
        have_last_tag_ = true;
        last_tag_ = plan.tag;
        if (no_flip) {
            for (Frame& o : f_)
                if (o.tag == plan.tag) o.valid = false;
            if (open_ >= 0) f_[static_cast<std::size_t>(open_)].tainted = true;
        }
        if (open_ >= 0) {
            Frame& f = f_[static_cast<std::size_t>(open_)];
            for (Frame& o : f_)  // (a tag seen again after a state load)
                if (&o != &f && o.tag == plan.tag) o.valid = false;
            f.valid = !f.tainted;
            f.tag = plan.tag;
            f.due = plan.at_qpc;
            f.disp = disp;
            if (f.tag == m_a_ || f.tag == m_b_) m_a_ = m_b_ = ~0ull;  // (a reused tag after a state load)
            if (f.tag == work_tag_) work_tag_ = ~0ull;
            std::lock_guard<std::mutex> lk(m_);
            ++st_.frames;
        }
        // The next frame starts here: its memory before this list, and this list as its first.
        int slot = -1;
        for (u32 i = 0; i < kFrames; ++i) {
            if (static_cast<int>(i) == open_) continue;
            if (!f_[i].valid) {
                slot = static_cast<int>(i);
                break;
            }
            if (slot < 0 || f_[i].due < f_[static_cast<std::size_t>(slot)].due) slot = static_cast<int>(i);
        }
        Frame& n = f_[static_cast<std::size_t>(slot)];
        if (n.tag == m_a_ || n.tag == m_b_) m_a_ = m_b_ = ~0ull;
        if (n.tag == work_tag_) work_tag_ = ~0ull;
        n.valid = false;
        n.tainted = no_flip || merged;  // started mid-frame / with another frame's lists
        n.ops.clear();
        ex.save_bank(n.bank);
        open_ = slot;
    }
    if (open_ >= 0) f_[static_cast<std::size_t>(open_)].ops.append(ops);
}

bool HfrInterpolator::ensure_gpu(gs::GsD3D11Executor&, const gs::DisplayTick& t) {
    if (g_ && g_->dev == t.dev) return !g_->failed;
    g_ = std::make_unique<Gpu>();
    Gpu& g = *g_;
    g.dev = t.dev;
    const char* src = gs::hlsl::kHlslPresent;
    ComPtr<ID3DBlob> vsb, psb, err;
    if (FAILED(D3DCompile(src, std::strlen(src), "p3fes_hfr", nullptr, nullptr, "vs_present", "vs_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &vsb, &err)) ||
        FAILED(D3DCompile(src, std::strlen(src), "p3fes_hfr", nullptr, nullptr, "ps_present", "ps_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &psb, &err)) ||
        FAILED(t.dev->CreateVertexShader(vsb->GetBufferPointer(), vsb->GetBufferSize(), nullptr, &g.vs)) ||
        FAILED(t.dev->CreatePixelShader(psb->GetBufferPointer(), psb->GetBufferSize(), nullptr, &g.ps))) {
        std::fprintf(stderr, "p3fes: hfr: present shaders failed%s%s\n", err ? ": " : "", err ? static_cast<const char*>(err->GetBufferPointer()) : "");
        g.failed = true;
        return false;
    }
    D3D11_SAMPLER_DESC sd{};
    sd.Filter = o_.linear ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    t.dev->CreateSamplerState(&sd, &g.smp);
    if (o_.gpu_timing) {
        for (Gpu::Timer& tm : g.timers) {
            D3D11_QUERY_DESC qd{D3D11_QUERY_TIMESTAMP_DISJOINT, 0};
            t.dev->CreateQuery(&qd, &tm.disjoint);
            qd.Query = D3D11_QUERY_TIMESTAMP;
            t.dev->CreateQuery(&qd, &tm.t0);
            t.dev->CreateQuery(&qd, &tm.t1);
        }
    }
    return true;
}

bool HfrInterpolator::draw_srv(const gs::DisplayTick& t, ID3D11ShaderResourceView* srv) {
    if (!srv || !g_ || g_->failed) return false;
    ID3D11DeviceContext* ctx = t.ctx;
    ID3D11RenderTargetView* rtv = t.rtv;
    ctx->OMSetRenderTargets(1, &rtv, nullptr);
    ctx->RSSetViewports(1, &t.viewport);
    ctx->RSSetState(nullptr);
    ctx->IASetInputLayout(nullptr);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    ctx->VSSetShader(g_->vs.Get(), nullptr, 0);
    ctx->PSSetShader(g_->ps.Get(), nullptr, 0);
    ctx->PSSetShaderResources(0, 1, &srv);
    ID3D11SamplerState* s = g_->smp.Get();
    ctx->PSSetSamplers(0, 1, &s);
    ctx->Draw(4, 0);
    ID3D11ShaderResourceView* none = nullptr;
    ctx->PSSetShaderResources(0, 1, &none);
    return true;
}

void HfrInterpolator::collect_gpu_times(ID3D11DeviceContext* ctx) {
    if (!g_) return;
    for (Gpu::Timer& tm : g_->timers) {
        if (!tm.pending) continue;
        D3D11_QUERY_DATA_TIMESTAMP_DISJOINT dj{};
        UINT64 a = 0, b = 0;
        if (ctx->GetData(tm.disjoint.Get(), &dj, sizeof dj, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK) continue;
        if (ctx->GetData(tm.t0.Get(), &a, sizeof a, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK) continue;
        if (ctx->GetData(tm.t1.Get(), &b, sizeof b, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK) continue;
        tm.pending = false;
        if (dj.Disjoint || dj.Frequency == 0 || b < a) continue;
        const double ms = static_cast<double>(b - a) * 1000.0 / static_cast<double>(dj.Frequency);
        std::lock_guard<std::mutex> lk(m_);
        st_.gpu_ms_sum += ms;
        gpu_ema_ms_ = gpu_ema_ms_ > 0.0 ? gpu_ema_ms_ + (ms - gpu_ema_ms_) * 0.1 : ms;
        st_.gpu_ms_max = std::max(st_.gpu_ms_max, ms);
        ++st_.gpu_samples;
    }
}

unsigned HfrInterpolator::steps_for(const gs::DisplayTick&, const Frame& a, const Frame& b) {
    if (o_.steps) return o_.steps;
    const double period = static_cast<double>(b.due - a.due);
    if (!(tick_ema_ > 0.0) || !(period > 0.0)) return 0;
    const double r = period / tick_ema_;  // display ticks per game frame
    const double kr = std::round(r);
    unsigned k = (kr >= 2.0 && std::fabs(r - kr) < 0.04 * kr) ? static_cast<unsigned>(kr) : 0u;
    // GPU budget: at most gpu_budget of a game frame spent on in-between pictures (each costs one replay), so a
    // 120 Hz / uncapped display falls back to fewer steps instead of starving the real frames.
    static const double qpf = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return static_cast<double>(f.QuadPart);
    }();
    if (o_.gpu_budget > 0.0 && gpu_ema_ms_ > 0.0) {
        const double period_ms = period * 1000.0 / qpf;
        const unsigned kmax = 1u + static_cast<unsigned>(std::max(0.0, std::floor(o_.gpu_budget * period_ms / gpu_ema_ms_)));
        if ((k == 0 && r > static_cast<double>(kmax)) || k > kmax) {
            k = kmax;
            std::lock_guard<std::mutex> lk(m_);
            ++st_.gpu_capped;
        }
    }
    return k;
}

bool HfrInterpolator::replay(gs::GsD3D11Executor& ex, const gs::DisplayTick& t, Frame& a, Frame& b, float alpha) {
    const auto c0 = std::chrono::steady_clock::now();
    if (m_a_ != a.tag || m_b_ != b.tag) {
        const std::vector<BatchView> pv = batch_views(a.ops), nv = batch_views(b.ops);
        match_ = match_frames(pv, nv, o_.params, &a.ops, &b.ops);
        m_a_ = a.tag;
        m_b_ = b.tag;
        std::lock_guard<std::mutex> lk(m_);
        ++st_.pairs;
        st_.cuts += match_.st.cut ? 1u : 0u;
        st_.cut_empty += match_.st.cut_reason == MatchStats::CutEmpty ? 1u : 0u;
        st_.cut_unmatched += match_.st.cut_reason == MatchStats::CutUnmatched ? 1u : 0u;
        st_.cut_held += match_.st.cut_reason == MatchStats::CutHeld ? 1u : 0u;
        st_.batches += match_.st.batches;
        st_.matched += match_.st.matched;
        st_.held += match_.st.held;
        st_.unmatched += match_.st.unmatched;
        st_.verts += match_.st.verts;
        st_.matched_verts += match_.st.matched_verts;
    }
    if (match_.st.cut && !o_.force_replay) return false;
    const auto c1 = std::chrono::steady_clock::now();
    if (work_tag_ != b.tag) {
        work_ = b.ops;
        work_tag_ = b.tag;
    }
    const auto c2 = std::chrono::steady_clock::now();
    blend_vertices(a.ops, b.ops, match_, alpha, o_.params, work_.verts);
    const auto c3 = std::chrono::steady_clock::now();
    if (!o_.dump_dir.empty() && dumped_ < o_.dump_max && b.tag != dump_last_ && b.tag >= o_.dump_from &&
        (o_.dump_every <= 1 || b.tag % o_.dump_every == 0)) {
        dump_last_ = b.tag;
        ++dumped_;
        dump_pair(ex, t, a, b, alpha);
    }
    const auto c4 = std::chrono::steady_clock::now();
    ID3D11DeviceContext* ctx = t.ctx;
    Gpu::Timer* tm = nullptr;
    if (o_.gpu_timing && g_) {
        collect_gpu_times(ctx);
        Gpu::Timer& cand = g_->timers[g_->next_timer];
        if (!cand.pending && cand.disjoint) {
            tm = &cand;
            g_->next_timer = (g_->next_timer + 1) % static_cast<u32>(g_->timers.size());
            ctx->Begin(tm->disjoint.Get());
            ctx->End(tm->t0.Get());
        }
    }
    ex.copy_bank(scratch_bank_, b.bank);
    ex.swap_bank(scratch_bank_);
    ex.execute(work_);
    ID3D11ShaderResourceView* srv = nullptr;
    u32 w = 0, h = 0;
    const bool have = ex.compose(b.disp, &srv, w, h);
    ex.swap_bank(scratch_bank_);  // the real GS memory back
    const bool drawn = have && draw_srv(t, srv);
    if (tm) {
        ctx->End(tm->t1.Get());
        ctx->End(tm->disjoint.Get());
        tm->pending = true;
    }
    const auto c5 = std::chrono::steady_clock::now();
    const auto ms_of = [](auto d) { return std::chrono::duration<double, std::milli>(d).count(); };
    const double ms = ms_of(c3 - c0) + ms_of(c5 - c4);  // without the diagnostics dump
    std::lock_guard<std::mutex> lk(m_);
    st_.copy_ms_sum += ms_of(c2 - c1);
    st_.blend_ms_sum += ms_of(c3 - c2);
    st_.issue_ms_sum += ms_of(c5 - c4);
    st_.cpu_ms_sum += ms;
    st_.cpu_ms_max = std::max(st_.cpu_ms_max, ms);
    return drawn;
}

// Diagnostics (--hfr-dump): frame A replayed as it is, the in-between picture at `alpha`, frame B replayed, each
// composed and read back (waits for the GPU) into <dir>/hfr_<B tag>_{a,mNN,b}.png.
void HfrInterpolator::replay_to_png(gs::GsD3D11Executor& ex, const Frame& f, const gs::OpList& l, const std::string& path) {
    ex.copy_bank(scratch_bank_, f.bank);
    ex.swap_bank(scratch_bank_);
    ex.execute(l);
    gs::Frame fr;
    const bool ok = ex.compose_readback(f.disp, fr);
    ex.swap_bank(scratch_bank_);
    if (ok) gs::write_png(path, fr);
}

namespace {
// The latched picture of a tick (an RGBA8 texture) read back into a Frame (waits for the GPU).
bool read_srv(const gs::DisplayTick& t, ID3D11ShaderResourceView* srv, gs::Frame& out) {
    if (!srv) return false;
    ComPtr<ID3D11Resource> res;
    srv->GetResource(&res);
    ComPtr<ID3D11Texture2D> tex;
    if (FAILED(res.As(&tex))) return false;
    D3D11_TEXTURE2D_DESC d{};
    tex->GetDesc(&d);
    d.Usage = D3D11_USAGE_STAGING;
    d.BindFlags = 0;
    d.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    d.MiscFlags = 0;
    ComPtr<ID3D11Texture2D> st;
    if (FAILED(t.dev->CreateTexture2D(&d, nullptr, &st))) return false;
    t.ctx->CopyResource(st.Get(), tex.Get());
    D3D11_MAPPED_SUBRESOURCE m{};
    if (FAILED(t.ctx->Map(st.Get(), 0, D3D11_MAP_READ, 0, &m))) return false;
    out.width = d.Width;
    out.height = d.Height;
    out.rgba.resize(static_cast<std::size_t>(d.Width) * d.Height);
    for (u32 y = 0; y < d.Height; ++y)
        std::memcpy(out.rgba.data() + static_cast<std::size_t>(y) * d.Width, static_cast<const u8*>(m.pData) + static_cast<std::size_t>(y) * m.RowPitch,
                    d.Width * 4u);
    t.ctx->Unmap(st.Get(), 0);
    return true;
}
} // namespace

void HfrInterpolator::dump_pair(gs::GsD3D11Executor& ex, const gs::DisplayTick& t, Frame& a, Frame& b, float alpha) {
    char base[96];
    std::snprintf(base, sizeof base, "/hfr_%08llu", static_cast<unsigned long long>(b.tag));
    replay_to_png(ex, a, a.ops, o_.dump_dir + base + "_a.png");
    char mid[32];
    std::snprintf(mid, sizeof mid, "_m%02d.png", static_cast<int>(alpha * 100.0f + 0.5f));
    replay_to_png(ex, b, work_, o_.dump_dir + base + mid);
    replay_to_png(ex, b, b.ops, o_.dump_dir + base + "_b.png");
    gs::Frame lat;  // B as the renderer latched it (the exact path): the replay above must equal it
    if (read_srv(t, t.next, lat)) gs::write_png(o_.dump_dir + base + "_b_latched.png", lat);
    std::printf("p3fes: hfr: dumped %s (A %llu -> B %llu at %.2f; %u batches, %u matched, %u held, %u new%s)\n", base + 1,
                static_cast<unsigned long long>(a.tag), static_cast<unsigned long long>(b.tag), alpha, match_.st.batches, match_.st.matched,
                match_.st.held, match_.st.unmatched, match_.st.cut ? ", cut" : "");
}

bool HfrInterpolator::draw(gs::GsD3D11Executor& ex, const gs::DisplayTick& t) {
    {
        std::lock_guard<std::mutex> lk(m_);
        ++st_.ticks;
    }
    if (last_tick_ && t.tick_qpc > last_tick_) {
        const double d = static_cast<double>(t.tick_qpc - last_tick_);
        tick_ema_ = tick_ema_ > 0.0 ? tick_ema_ + (d - tick_ema_) * 0.1 : d;
    }
    last_tick_ = t.tick_qpc;
    if (!banks_ok_ || !ensure_gpu(ex, t)) return false;
    Frame* a = find(t.prev_tag);
    Frame* b = t.next ? find(t.next_tag) : nullptr;
    auto count = [this](u64 HfrStats::*field) {
        std::lock_guard<std::mutex> lk(m_);
        ++(st_.*field);
    };
    if (!t.next) {
        // Low latency: the next frame is not latched yet -- extrapolate A from the frame before it.
        if (o_.extrapolate && a) {
            Frame* p = nullptr;
            for (Frame& f : f_)
                if (f.valid && f.due < a->due && (!p || f.due > p->due)) p = &f;
            if (p && a->due > p->due && t.tick_qpc > a->due) {
                const double e = static_cast<double>(t.tick_qpc - a->due) / static_cast<double>(a->due - p->due);
                const unsigned k = steps_for(t, *p, *a);
                double q = k ? quantise_alpha(e, k) : e;
                q = std::min(q, static_cast<double>(o_.max_extrapolate));
                if (q > 0.0 && replay(ex, t, *p, *a, static_cast<float>(1.0 + q))) {
                    count(&HfrStats::extrapolated);
                    return true;
                }
            }
        }
        count(&HfrStats::no_next);
        return false;
    }
    const unsigned k = (a && b) ? steps_for(t, *a, *b) : 0;
    {
        std::lock_guard<std::mutex> lk(m_);
        st_.steps = k;
    }
    if (k == 1) {
        count(&HfrStats::shown_prev);
        return false;
    }
    const double alpha = quantise_alpha(t.alpha, k);
    if (!(alpha > 0.0)) {
        count(&HfrStats::shown_prev);
        return false;
    }
    if (alpha >= 1.0) {
        if (draw_srv(t, t.next)) {
            count(&HfrStats::exact_next);
            return true;
        }
        return false;
    }
    if (!a || !b) {
        count(&HfrStats::no_record);
        return false;
    }
    if (replay(ex, t, *a, *b, static_cast<float>(alpha))) {
        count(&HfrStats::interpolated);
        return true;
    }
    count(&HfrStats::shown_prev);
    return false;
}

HfrStats HfrInterpolator::stats() const {
    std::lock_guard<std::mutex> lk(m_);
    return st_;
}

std::string HfrInterpolator::overlay_line() {
    const HfrStats s = stats();
    const HfrStats& p = overlay_last_;
    const u64 ticks = s.ticks - p.ticks;
    const u64 mid = (s.interpolated + s.extrapolated) - (p.interpolated + p.extrapolated);
    const u64 late = s.no_next - p.no_next;
    const u64 gs = s.gpu_samples - p.gpu_samples;
    const double gpu = gs ? (s.gpu_ms_sum - p.gpu_ms_sum) / static_cast<double>(gs) : 0.0;
    char b[160];
    std::snprintf(b, sizeof b, "hfr: %.0f%% in-between, %.0f%% late, gpu %.1f ms", ticks ? 100.0 * static_cast<double>(mid) / static_cast<double>(ticks) : 0.0,
                  ticks ? 100.0 * static_cast<double>(late) / static_cast<double>(ticks) : 0.0, gpu);
    overlay_last_ = s;
    return b;
}

std::string HfrInterpolator::summary() const {
    const HfrStats s = stats();
    const u64 n = s.interpolated + s.extrapolated;
    const auto u = [](u64 v) { return static_cast<unsigned long long>(v); };
    const auto pct = [](u64 a, u64 b) { return b ? 100.0 * static_cast<double>(a) / static_cast<double>(b) : 0.0; };
    const auto per = [](double sum, u64 k) { return k ? sum / static_cast<double>(k) : 0.0; };
    char b[768];
    std::snprintf(b, sizeof b,
                  "hfr: %llu ticks: %llu in-between (%llu extrapolated), %llu exact next, %llu previous (%llu: next frame not latched "
                  "yet); %llu frames recorded, %llu pairs: %llu cuts (no native batch %llu, few matched %llu, many held %llu), "
                  "%llu ticks without record; batches matched %.1f %% (held %llu, new %llu), vertices matched %.1f %%; "
                  "cpu %.2f ms per in-between (copy %.2f per pair, blend %.2f, issue %.2f; max %.2f), gpu %.2f ms (max %.2f, %llu samples); "
                  "steps %u (lowered by the GPU budget on %llu ticks)",
                  u(s.ticks), u(n), u(s.extrapolated), u(s.exact_next), u(s.shown_prev + s.no_next), u(s.no_next), u(s.frames), u(s.pairs),
                  u(s.cuts), u(s.cut_empty), u(s.cut_unmatched), u(s.cut_held), u(s.no_record), pct(s.matched, s.batches), u(s.held),
                  u(s.unmatched), pct(s.matched_verts, s.verts), per(s.cpu_ms_sum, n), per(s.copy_ms_sum, s.pairs - s.cuts),
                  per(s.blend_ms_sum, n), per(s.issue_ms_sum, n), s.cpu_ms_max, per(s.gpu_ms_sum, s.gpu_samples), s.gpu_ms_max,
                  u(s.gpu_samples), s.steps, u(s.gpu_capped));
    return b;
}

} // namespace p3fes::hfr
