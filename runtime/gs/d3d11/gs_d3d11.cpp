// D3D11 GS back end: executor (device-level) and renderer (render thread + swap chain). See p3fes/gs/gs_d3d11.h.
#include "p3fes/gs/gs_d3d11.h"

#include "p3fes/gs/gs_d3d11_hlsl.h"
#include "p3fes/gs/gs_native_hlsl.h"

#include <avrt.h>
#include <d3d11_3.h>
#include <dwmapi.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>

using Microsoft::WRL::ComPtr;

namespace p3fes::gs {

namespace {

constexpr u32 kRingSlots = 3;

// Compiled shaders are cached in %LOCALAPPDATA%\P3FES\shadercache, keyed by a hash of the source, entry point,
// target and macros (the big pixel shader takes seconds to compile; the cache makes later starts instant).
std::filesystem::path shader_cache_path(const std::string& src, const char* entry, const char* target, const D3D_SHADER_MACRO* defs) {
    u64 h = 0xCBF29CE484222325ull;
    auto mix = [&h](const char* p, std::size_t n) {
        for (std::size_t i = 0; i < n; ++i) h = (h ^ static_cast<u8>(p[i])) * 0x100000001B3ull;
        h = (h ^ 0xFF) * 0x100000001B3ull;
    };
    mix(src.data(), src.size());
    mix(entry, std::strlen(entry));
    mix(target, std::strlen(target));
    for (const D3D_SHADER_MACRO* d = defs; d && d->Name; ++d) {
        mix(d->Name, std::strlen(d->Name));
        mix(d->Definition, std::strlen(d->Definition));
    }
    char* base = nullptr;
    std::size_t len = 0;
    if (_dupenv_s(&base, &len, "LOCALAPPDATA") != 0 || !base) return {};
    std::filesystem::path p = std::filesystem::path(base) / "P3FES" / "shadercache";
    std::free(base);
    char name[64];
    std::snprintf(name, sizeof name, "%016llx.cso", static_cast<unsigned long long>(h));
    return p / name;
}

bool compile_one(const std::string& src, const char* entry, const char* target, const D3D_SHADER_MACRO* defs,
                 ComPtr<ID3DBlob>& blob, std::string& err) {
    const std::filesystem::path cache = shader_cache_path(src, entry, target, defs);
    if (!cache.empty()) {
        std::error_code ec;
        const auto size = std::filesystem::file_size(cache, ec);
        if (!ec && size > 0 && SUCCEEDED(D3DCreateBlob(static_cast<SIZE_T>(size), &blob))) {
            if (FILE* f = _wfopen(cache.c_str(), L"rb")) {
                const bool ok = std::fread(blob->GetBufferPointer(), 1, static_cast<std::size_t>(size), f) == size;
                std::fclose(f);
                if (ok) return true;
            }
        }
        blob.Reset();
    }
    ComPtr<ID3DBlob> errors;
    const HRESULT hr = D3DCompile(src.data(), src.size(), "p3fes_gs_d3d11", defs, nullptr, entry, target,
                                  D3DCOMPILE_OPTIMIZATION_LEVEL3, 0, &blob, &errors);
    if (FAILED(hr)) {
        err = std::string("D3DCompile ") + entry + " " + target + ": " +
              (errors ? static_cast<const char*>(errors->GetBufferPointer()) : "?");
        return false;
    }
    if (!cache.empty()) {
        std::error_code ec;
        std::filesystem::create_directories(cache.parent_path(), ec);
        const std::filesystem::path tmp = cache.wstring() + L".tmp";
        if (FILE* f = _wfopen(tmp.c_str(), L"wb")) {
            const bool ok = std::fwrite(blob->GetBufferPointer(), 1, blob->GetBufferSize(), f) == blob->GetBufferSize();
            std::fclose(f);
            if (ok) std::filesystem::rename(tmp, cache, ec);
            else std::filesystem::remove(tmp, ec);
        }
    }
    return true;
}

// The CRTC constants (cbuffer Crtc in gs_d3d11_hlsl.h).
struct CrtcCB {
    u32 ca[2][4];
    u32 cb[2][4];
    u32 cc[2][4];
    s32 geo[4];
    u32 mode[4];
    u32 mode2[4];
};

// gs::compose's circuit decode (gs_output.cpp), to the shader's constants. false: nothing to show.
bool crtc_constants(const DisplayRegs& r, CrtcCB& c, u32& w, u32& h) {
    c = CrtcCB{};
    s32 x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    bool any = false;
    for (u32 k = 0; k < 2; ++k) {
        if (!((r.pmode >> k) & 1u)) continue;
        const u64 d = r.display[k], f = r.dispfb[k];
        const u32 magh = bits(d, 23, 4) + 1u, magv = bits(d, 27, 2) + 1u;
        const u32 cw = (bits(d, 32, 12) + 1u) / magh, ch = (bits(d, 44, 11) + 1u) / magv;
        if (cw == 0 || ch == 0 || cw > 2048 || ch > 2048) continue;
        const s32 cx = static_cast<s32>(bits(d, 0, 12) / magh), cy = static_cast<s32>(bits(d, 12, 11) / magv);
        c.ca[k][0] = 1;
        c.ca[k][1] = static_cast<u32>(cx);
        c.ca[k][2] = static_cast<u32>(cy);
        c.ca[k][3] = cw;
        c.cb[k][0] = ch;
        c.cb[k][1] = bits(f, 0, 9) * kBlocksPerPage;
        c.cb[k][2] = bits(f, 9, 6);
        c.cb[k][3] = bits(f, 15, 5);
        c.cc[k][0] = bits(f, 32, 11);
        c.cc[k][1] = bits(f, 43, 11);
        x0 = std::min(x0, cx);
        y0 = std::min(y0, cy);
        x1 = std::max(x1, cx + static_cast<s32>(cw));
        y1 = std::max(y1, cy + static_cast<s32>(ch));
        any = true;
    }
    if (!any) return false;
    w = static_cast<u32>(std::min(x1 - x0, 2048));
    h = static_cast<u32>(std::min(y1 - y0, 2048));
    c.geo[0] = static_cast<s32>(w);
    c.geo[1] = static_cast<s32>(h);
    c.geo[2] = x0;
    c.geo[3] = y0;
    const bool interlaced = (r.smode2 & 1u) != 0, frame_mode = ((r.smode2 >> 1) & 1u) != 0;
    c.mode[0] = (interlaced && frame_mode) ? 1u : 0u;
    c.mode[1] = (r.pmode >> 5) & 1u;
    c.mode[2] = (r.pmode >> 7) & 1u;
    c.mode[3] = bits(r.pmode, 8, 8);
    c.mode2[0] = static_cast<u32>(r.bgcolor & 0xFFFFFFu);
    return true;
}

} // namespace

std::string GsD3D11Caps::summary() const {
    char b[512];
    std::snprintf(b, sizeof b, "adapter \"%s\", driver %s, feature level %u.%u, ROVsSupported %s, DoublePrecisionFloatShaderOps %s, "
                               "ExtendedDoublesShaderInstructions %s",
                  adapter.c_str(), driver.empty() ? "?" : driver.c_str(), (static_cast<unsigned>(feature_level) >> 12) & 0xF,
                  (static_cast<unsigned>(feature_level) >> 8) & 0xF, rov ? "yes" : "no", doubles ? "yes" : "no", ext_doubles ? "yes" : "no");
    return b;
}

GsD3D11Caps query_caps(ID3D11Device* dev) {
    GsD3D11Caps c;
    c.feature_level = dev->GetFeatureLevel();
    ComPtr<IDXGIDevice> dxgi;
    if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice), &dxgi))) {
        ComPtr<IDXGIAdapter> ad;
        if (SUCCEEDED(dxgi->GetAdapter(&ad))) {
            DXGI_ADAPTER_DESC d{};
            ad->GetDesc(&d);
            char name[128] = {};
            WideCharToMultiByte(CP_UTF8, 0, d.Description, -1, name, sizeof name - 1, nullptr, nullptr);
            c.adapter = name;
            LARGE_INTEGER umd{};
            if (SUCCEEDED(ad->CheckInterfaceSupport(__uuidof(IDXGIDevice), &umd))) {
                char v[64];
                std::snprintf(v, sizeof v, "%u.%u.%u.%u", static_cast<unsigned>(umd.HighPart >> 16), static_cast<unsigned>(umd.HighPart & 0xFFFF),
                              static_cast<unsigned>(umd.LowPart >> 16), static_cast<unsigned>(umd.LowPart & 0xFFFF));
                c.driver = v;
            }
        }
    }
    D3D11_FEATURE_DATA_D3D11_OPTIONS2 o2{};
    if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS2, &o2, sizeof o2))) c.rov = o2.ROVsSupported;
    D3D11_FEATURE_DATA_DOUBLES dbl{};
    if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_DOUBLES, &dbl, sizeof dbl))) c.doubles = dbl.DoublePrecisionFloatShaderOps;
    D3D11_FEATURE_DATA_D3D11_OPTIONS o1{};
    if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &o1, sizeof o1))) c.ext_doubles = o1.ExtendedDoublesShaderInstructions;
    return c;
}

void enable_debug_messages(ID3D11Device* dev, bool break_on_error) {
    ComPtr<ID3D11InfoQueue> q;
    if (FAILED(dev->QueryInterface(__uuidof(ID3D11InfoQueue), &q))) return;
    q->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, break_on_error ? TRUE : FALSE);
    q->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, break_on_error ? TRUE : FALSE);
}

u64 drain_debug_messages(ID3D11Device* dev, const char* prefix) {
    ComPtr<ID3D11InfoQueue> q;
    if (!dev || FAILED(dev->QueryInterface(__uuidof(ID3D11InfoQueue), &q))) return 0;
    const UINT64 n = q->GetNumStoredMessages();
    u64 shown = 0;
    for (UINT64 i = 0; i < n; ++i) {
        SIZE_T len = 0;
        q->GetMessage(i, nullptr, &len);
        std::vector<char> buf(len);
        auto* m = reinterpret_cast<D3D11_MESSAGE*>(buf.data());
        if (FAILED(q->GetMessage(i, m, &len))) continue;
        if (m->Severity > D3D11_MESSAGE_SEVERITY_WARNING) continue;  // errors, corruption, warnings
        static const char* kSev[] = {"CORRUPTION", "ERROR", "WARNING", "INFO", "MESSAGE"};
        std::fprintf(stderr, "%s D3D11 %s: %.*s\n", prefix, kSev[m->Severity], static_cast<int>(m->DescriptionByteLength), m->pDescription);
        ++shown;
    }
    q->ClearStoredMessages();
    return shown;
}

// ---- Executor ----------------------------------------------------------------------------------------------

struct GsD3D11Executor::Impl {
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    ComPtr<ID3D11DeviceContext1> ctx1;  // D3D11.1 constant buffer offsets (null: one Map per draw)
    ComPtr<ID3D11Buffer> group_cb;      // cbuffer Group: the draw call's first state and GpuPrimRec
    bool rov = false;                   // ROV pixel shader: merged draw calls allowed
    ComPtr<ID3D11VertexShader> vs;
    ComPtr<ID3D11PixelShader> ps;
    ComPtr<ID3D11ComputeShader> cs_clut, cs_scatter, cs_pages, cs_crtc, cs_clut_resolve;
    ComPtr<ID3D11ComputeShader> cs_native;  // the native renderer's GPU vertex stage (gs_native_hlsl.h)
    ComPtr<ID3D11Buffer> native_cb;
    ComPtr<ID3D11InputLayout> layout;
    ComPtr<ID3D11Buffer> vram, staging, swz, clut, clut_staging, cb, clut_cb, scatter_cb, pages_cb, crtc_cb;
    ComPtr<ID3D11UnorderedAccessView> vram_uav, clut_uav;
    ComPtr<ID3D11ShaderResourceView> swz_srv, clut_srv;
    ComPtr<ID3D11RasterizerState> rs;
    ComPtr<ID3D11Query> q_disjoint, q_t0, q_t1;
    std::vector<ComPtr<ID3D11Query>> prof_q;  // execute_profiled: one timestamp per op
    // Frame texture (CRTC output).
    ComPtr<ID3D11Texture2D> frame, frame_staging;
    ComPtr<ID3D11UnorderedAccessView> frame_uav;
    ComPtr<ID3D11ShaderResourceView> frame_srv;
    u32 frame_w = 0, frame_h = 0;
    // Upload ring: per slot a vertex buffer and two raw SRV buffers (records, scatter words), DYNAMIC + DISCARD.
    // The record and word buffers are DEFAULT buffers filled by a copy from a per-slot STAGING buffer: refilling a
    // DYNAMIC buffer that has a raw SRV with Map(WRITE_DISCARD) (or a DEFAULT one with UpdateSubresource) made the
    // GPU read stale/zero data when the slot came round again on this driver (no debug-layer message); the
    // vertex buffer (no view) is unaffected and stays DYNAMIC.
    struct Slot {
        ComPtr<ID3D11Buffer> vb, prims, words, pages, prims_up, words_up, pages_up, ctab, ctab_up, cbs;
        ComPtr<ID3D11ShaderResourceView> prims_srv, words_srv, pages_srv, ctab_srv;
        u32 vb_cap = 0, prims_cap = 0, words_cap = 0, pages_cap = 0, ctab_cap = 0, cbs_cap = 0;  // bytes
        // native GPU vertex stage: inputs, batch table, output vertices (UAV + vertex buffer)
        ComPtr<ID3D11Buffer> nin, nin_up, ntab, ntab_up, nout;
        ComPtr<ID3D11ShaderResourceView> nin_srv, ntab_srv;
        ComPtr<ID3D11UnorderedAccessView> nout_uav;
        u32 nin_cap = 0, ntab_cap = 0, nout_cap = 0;
    };
    Slot ring[kRingSlots];
    u32 slot = 0;

    void unbind_om() { ctx->OMSetRenderTargetsAndUnorderedAccessViews(0, nullptr, nullptr, 0, 0, nullptr, nullptr); }
    // Waits until the GPU has finished everything issued so far. Used after whole-memory uploads (reset, the CPU
    // local copy): on this driver a later UAV/ROV pass was observed to overtake a preceding whole-buffer update
    // (docs/ANALYSIS/25 §7, "repeatability"), so the update is fenced.
    void wait_idle() {
        if (!event) {
            D3D11_QUERY_DESC qd{D3D11_QUERY_EVENT, 0};
            dev->CreateQuery(&qd, &event);
        }
        if (!event) return;
        ctx->End(event.Get());
        BOOL done = FALSE;
        while (ctx->GetData(event.Get(), &done, sizeof done, 0) == S_FALSE || !done) {
        }
    }
    ComPtr<ID3D11Query> event;
    // Extra GS memory banks (create_banks; frame interpolation): the same resources as the active memory's.
    struct Bank {
        ComPtr<ID3D11Buffer> vram, clut;
        ComPtr<ID3D11UnorderedAccessView> vram_uav, clut_uav;
        ComPtr<ID3D11ShaderResourceView> clut_srv;
    };
    std::vector<Bank> banks;

    bool ensure(ComPtr<ID3D11Buffer>& buf, ComPtr<ID3D11ShaderResourceView>* srv, u32& cap, std::size_t bytes, UINT bind,
                ComPtr<ID3D11Buffer>* up = nullptr) {
        if (bytes <= cap && buf && (!up || *up)) return true;
        cap = static_cast<u32>(std::max<std::size_t>((bytes + (bytes >> 1) + 65535) & ~std::size_t{65535}, 65536));
        D3D11_BUFFER_DESC bd{};
        bd.ByteWidth = cap;
        bd.Usage = up ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC;
        bd.CPUAccessFlags = up ? 0u : D3D11_CPU_ACCESS_WRITE;
        bd.BindFlags = bind;
        if (srv) bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
        buf.Reset();
        if (FAILED(dev->CreateBuffer(&bd, nullptr, &buf))) {
            cap = 0;
            return false;
        }
        if (up) {
            D3D11_BUFFER_DESC sd{};
            sd.ByteWidth = cap;
            sd.Usage = D3D11_USAGE_STAGING;
            sd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            up->Reset();
            const HRESULT hr = dev->CreateBuffer(&sd, nullptr, up->GetAddressOf());
            if (FAILED(hr) || !*up) {
                std::fprintf(stderr, "p3fes: d3d11 GS: staging buffer (%u bytes) failed hr=0x%08lX\n", cap, static_cast<unsigned long>(hr));
                cap = 0;
                return false;
            }
        }
        if (srv) {
            D3D11_SHADER_RESOURCE_VIEW_DESC rv{};
            rv.Format = DXGI_FORMAT_R32_TYPELESS;
            rv.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
            rv.BufferEx.NumElements = cap / 4;
            rv.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
            srv->Reset();
            if (FAILED(dev->CreateShaderResourceView(buf.Get(), &rv, srv->GetAddressOf()))) return false;
        }
        return true;
    }
    void fill(ID3D11Buffer* buf, const void* src, std::size_t bytes) {
        D3D11_MAPPED_SUBRESOURCE m{};
        if (SUCCEEDED(ctx->Map(buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &m))) {
            std::memcpy(m.pData, src, bytes);
            ctx->Unmap(buf, 0);
        }
    }
    Slot& upload(const OpList& l) {
        slot = (slot + 1) % kRingSlots;
        Slot& s = ring[slot];
        if (!l.verts.empty() && ensure(s.vb, nullptr, s.vb_cap, l.verts.size() * sizeof(GpuVertex), D3D11_BIND_VERTEX_BUFFER))
            fill(s.vb.Get(), l.verts.data(), l.verts.size() * sizeof(GpuVertex));
        if (!l.prims.empty() &&
            ensure(s.prims, &s.prims_srv, s.prims_cap, l.prims.size() * sizeof(GpuPrimRec), D3D11_BIND_SHADER_RESOURCE, &s.prims_up))
            fill_staged(s.prims.Get(), s.prims_up.Get(), l.prims.data(), l.prims.size() * sizeof(GpuPrimRec));
        if (!l.words.empty() && ensure(s.words, &s.words_srv, s.words_cap, l.words.size() * 4, D3D11_BIND_SHADER_RESOURCE, &s.words_up))
            fill_staged(s.words.Get(), s.words_up.Get(), l.words.data(), l.words.size() * 4);
        if (!l.pages.empty() && ensure(s.pages, &s.pages_srv, s.pages_cap, l.pages.size() * 4, D3D11_BIND_SHADER_RESOURCE, &s.pages_up))
            fill_staged(s.pages.Get(), s.pages_up.Get(), l.pages.data(), l.pages.size() * 4);
        if (!l.clut_tab.empty() &&
            ensure(s.ctab, &s.ctab_srv, s.ctab_cap, l.clut_tab.size() * 4, D3D11_BIND_SHADER_RESOURCE, &s.ctab_up))
            fill_staged(s.ctab.Get(), s.ctab_up.Get(), l.clut_tab.data(), l.clut_tab.size() * 4);
        // Every draw's constant block in one buffer, bound per draw at its offset (D3D11.1 constant buffer offsets).
        // (+128 blocks: a draw call binds 128 blocks from its first one, 64 KiB, which must lie inside the buffer.)
        if (ctx1 && !l.cbs.empty() &&
            ensure(s.cbs, nullptr, s.cbs_cap, (l.cbs.size() + 128) * sizeof(GpuDrawCB), D3D11_BIND_CONSTANT_BUFFER))
            fill(s.cbs.Get(), l.cbs.data(), l.cbs.size() * sizeof(GpuDrawCB));
        in_draws = false;
        return s;
    }
    void fill_staged(ID3D11Buffer* dst, ID3D11Buffer* up, const void* src, std::size_t bytes) {
        D3D11_MAPPED_SUBRESOURCE m{};
        if (FAILED(ctx->Map(up, 0, D3D11_MAP_WRITE, 0, &m))) return;  // waits if the GPU still copies from it
        std::memcpy(m.pData, src, bytes);
        ctx->Unmap(up, 0);
        const D3D11_BOX box{0, 0, 0, static_cast<UINT>(bytes), 1, 1};
        ctx->CopySubresourceRegion(dst, 0, 0, 0, 0, up, 0, &box);
    }
    // Draw-pipeline bindings are set once per run of consecutive draws (begin_draws) and dropped before a compute op
    // (end_draws); per draw only the constant block, the scissor and the Draw call remain.
    bool in_draws = false;
    GpuRect last_sc{};
    ID3D11Buffer* bound_vb = nullptr;
    void begin_draws(Slot& s) {
        if (in_draws) return;
        in_draws = true;
        ID3D11UnorderedAccessView* uav = vram_uav.Get();
        ctx->OMSetRenderTargetsAndUnorderedAccessViews(0, nullptr, nullptr, 0, 1, &uav, nullptr);
        bound_vb = nullptr;  // draw_run binds the list's or the native stage's vertex buffer
        ctx->IASetInputLayout(layout.Get());
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->VSSetShader(vs.Get(), nullptr, 0);
        ctx->PSSetShader(ps.Get(), nullptr, 0);
        ID3D11ShaderResourceView* srvs[4] = {swz_srv.Get(), clut_srv.Get(), s.prims_srv.Get(), s.ctab_srv.Get()};
        ctx->PSSetShaderResources(0, 4, srvs);
        ctx->RSSetState(rs.Get());
        const D3D11_VIEWPORT vp{-4096.0f, -4096.0f, 8192.0f, 8192.0f, 0.0f, 1.0f};
        ctx->RSSetViewports(1, &vp);
        last_sc = GpuRect{-1, -1, -1, -1};
    }
    void end_draws() {
        if (!in_draws) return;
        in_draws = false;
        ID3D11ShaderResourceView* none[4] = {};
        ctx->PSSetShaderResources(0, 4, none);
        unbind_om();
    }
    // One D3D draw call for the Draw op at i and the merged ones after it (GpuOp::merge: ROVs, constant buffer
    // offsets, at most 128 states, contiguous vertices); returns the index after the last op drawn.
    std::size_t draw_run(const OpList& l, std::size_t i, Slot& s) {
        begin_draws(s);
        const GpuOp& op = l.ops[i];
        ID3D11Buffer* vb = op.native ? s.nout.Get() : s.vb.Get();
        if (vb != bound_vb) {
            const UINT stride = sizeof(GpuVertex), off = 0;
            ctx->IASetVertexBuffers(0, 1, &vb, &stride, &off);
            bound_vb = vb;
        }
        std::size_t j = i + 1;
        GpuRect u = op.sc;
        u32 count = op.count;
        if (rov && ctx1 && s.cbs) {
            while (j < l.ops.size() && l.ops[j].kind == GpuOpKind::Draw && l.ops[j].merge && l.ops[j].native == op.native &&
                   l.ops[j].cb - op.cb < 128 &&
                   l.ops[j].first == op.first + count) {
                const GpuRect& b = l.ops[j].sc;
                u.left = std::min(u.left, b.left);
                u.top = std::min(u.top, b.top);
                u.right = std::max(u.right, b.right);
                u.bottom = std::max(u.bottom, b.bottom);
                count += l.ops[j].count;
                ++j;
            }
        }
        {
            D3D11_MAPPED_SUBRESOURCE m{};
            if (SUCCEEDED(ctx->Map(group_cb.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &m))) {
                const u32 g[4] = {op.cb, op.prim_base, 0, 0};
                std::memcpy(m.pData, g, sizeof g);
                ctx->Unmap(group_cb.Get(), 0);
            }
            ID3D11Buffer* gcb = group_cb.Get();
            ctx->PSSetConstantBuffers(1, 1, &gcb);
        }
        if (ctx1 && s.cbs) {
            ID3D11Buffer* cbp = s.cbs.Get();
            const UINT first = op.cb * static_cast<UINT>(sizeof(GpuDrawCB) / 16), num = 4096;
            ctx1->PSSetConstantBuffers1(0, 1, &cbp, &first, &num);
        } else {
            D3D11_MAPPED_SUBRESOURCE m{};
            if (SUCCEEDED(ctx->Map(cb.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &m))) {
                std::memcpy(m.pData, &l.cbs[op.cb], sizeof(GpuDrawCB));
                ctx->Unmap(cb.Get(), 0);
            }
            ID3D11Buffer* cbp = cb.Get();
            ctx->PSSetConstantBuffers(0, 1, &cbp);
        }
        if (u.left != last_sc.left || u.top != last_sc.top || u.right != last_sc.right || u.bottom != last_sc.bottom) {
            const D3D11_RECT sc{u.left, u.top, u.right, u.bottom};
            ctx->RSSetScissorRects(1, &sc);
            last_sc = u;
        }
        ctx->Draw(count, op.first);
        ++draw_calls;
        return j;
    }
    u64 draw_calls = 0;  // D3D draw calls issued (diagnostics)
    void clut_resolve(u32 version, Slot& s) {
        end_draws();
        const u32 cbv[8] = {version, 0, 0, 0, 0, 0, 0, 0};
        ctx->UpdateSubresource(clut_cb.Get(), 0, nullptr, cbv, 0, 0);
        ID3D11UnorderedAccessView* uavs[2] = {vram_uav.Get(), clut_uav.Get()};
        ID3D11ShaderResourceView* srvs[5] = {swz_srv.Get(), nullptr, nullptr, nullptr, s.ctab_srv.Get()};
        ctx->CSSetShader(cs_clut_resolve.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 5, srvs);
        ID3D11Buffer* cbs[1] = {clut_cb.Get()};
        ctx->CSSetConstantBuffers(0, 1, cbs);
        ctx->CSSetUnorderedAccessViews(0, 2, uavs, nullptr);
        ctx->Dispatch(1, 1, 1);
        ID3D11UnorderedAccessView* none[2] = {};
        ctx->CSSetUnorderedAccessViews(0, 2, none, nullptr);
        ID3D11ShaderResourceView* nsrv[5] = {};
        ctx->CSSetShaderResources(0, 5, nsrv);
    }
    std::size_t run_op(const OpList& l, std::size_t i, Slot& s) {
        const GpuOp& op = l.ops[i];
        switch (op.kind) {
        case GpuOpKind::Draw: return draw_run(l, i, s);
        case GpuOpKind::Scatter: end_draws(); scatter(op, s); break;
        case GpuOpKind::Pages: end_draws(); pages_op(op, s); break;
        case GpuOpKind::Clut: end_draws(); clut_load(l.cluts[op.cb]); break;
        case GpuOpKind::Copy: end_draws(); copy(op); break;
        case GpuOpKind::ClutResolve: clut_resolve(op.cb, s); break;
        }
        return i + 1;
    }
    // The native renderer's GPU vertex stage: every native batch of the list at once, before the list's ops run.
    void native_stage(const OpList& l, Slot& s) {
        if (!l.nat_slots || !cs_native) return;
        if (!ensure(s.nin, &s.nin_srv, s.nin_cap, l.nat_in.size() * 4, D3D11_BIND_SHADER_RESOURCE, &s.nin_up)) return;
        fill_staged(s.nin.Get(), s.nin_up.Get(), l.nat_in.data(), l.nat_in.size() * 4);
        if (!ensure(s.ntab, &s.ntab_srv, s.ntab_cap, l.nat_tab.size() * 4, D3D11_BIND_SHADER_RESOURCE, &s.ntab_up)) return;
        fill_staged(s.ntab.Get(), s.ntab_up.Get(), l.nat_tab.data(), l.nat_tab.size() * 4);
        const std::size_t out_bytes = static_cast<std::size_t>(l.nat_slots) * 3u * sizeof(GpuVertex);
        if (out_bytes > s.nout_cap || !s.nout) {
            s.nout_cap = static_cast<u32>((out_bytes + (out_bytes >> 1) + 65535) & ~std::size_t{65535});
            D3D11_BUFFER_DESC bd{};
            bd.ByteWidth = s.nout_cap;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_VERTEX_BUFFER;
            bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
            s.nout.Reset();
            s.nout_uav.Reset();
            if (FAILED(dev->CreateBuffer(&bd, nullptr, &s.nout))) {
                s.nout_cap = 0;
                return;
            }
            D3D11_UNORDERED_ACCESS_VIEW_DESC ud{};
            ud.Format = DXGI_FORMAT_R32_TYPELESS;
            ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            ud.Buffer.NumElements = s.nout_cap / 4;
            ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
            dev->CreateUnorderedAccessView(s.nout.Get(), &ud, &s.nout_uav);
        }
        const u32 cbv[4] = {static_cast<u32>(l.nat_tab.size() / 4), l.nat_slots, 0, 0};
        ctx->UpdateSubresource(native_cb.Get(), 0, nullptr, cbv, 0, 0);
        unbind_om();
        ID3D11Buffer* none_vb = nullptr;
        const UINT zero = 0;
        ctx->IASetVertexBuffers(0, 1, &none_vb, &zero, &zero);
        ID3D11ShaderResourceView* srvs[2] = {s.nin_srv.Get(), s.ntab_srv.Get()};
        ID3D11UnorderedAccessView* uav = s.nout_uav.Get();
        ctx->CSSetShader(cs_native.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 2, srvs);
        ID3D11Buffer* cbp = native_cb.Get();
        ctx->CSSetConstantBuffers(0, 1, &cbp);
        ctx->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
        ctx->Dispatch((l.nat_slots + 63u) / 64u, 1, 1);
        ID3D11UnorderedAccessView* nuav = nullptr;
        ctx->CSSetUnorderedAccessViews(0, 1, &nuav, nullptr);
        ID3D11ShaderResourceView* nsrv[2] = {};
        ctx->CSSetShaderResources(0, 2, nsrv);
    }
    void scatter(const GpuOp& op, Slot& s) {
        const u32 cbv[4] = {op.count, op.first, 0, 0};
        ctx->UpdateSubresource(scatter_cb.Get(), 0, nullptr, cbv, 0, 0);
        unbind_om();
        ID3D11UnorderedAccessView* uav = vram_uav.Get();
        ID3D11ShaderResourceView* srvs[3] = {swz_srv.Get(), nullptr, s.words_srv.Get()};
        ctx->CSSetShader(cs_scatter.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 3, srvs);
        ID3D11Buffer* cbs[2] = {clut_cb.Get(), scatter_cb.Get()};
        ctx->CSSetConstantBuffers(0, 2, cbs);
        ctx->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
        ctx->Dispatch((op.count + 63u) / 64u, 1, 1);
        ID3D11UnorderedAccessView* none = nullptr;
        ctx->CSSetUnorderedAccessViews(0, 1, &none, nullptr);
        ID3D11ShaderResourceView* nsrv[3] = {};
        ctx->CSSetShaderResources(0, 3, nsrv);
    }
    void pages_op(const GpuOp& op, Slot& s) {
        const u32 cbv[4] = {op.count, op.first, 0, 0};
        ctx->UpdateSubresource(pages_cb.Get(), 0, nullptr, cbv, 0, 0);
        unbind_om();
        ID3D11UnorderedAccessView* uav = vram_uav.Get();
        ID3D11ShaderResourceView* srvs[4] = {swz_srv.Get(), nullptr, nullptr, s.pages_srv.Get()};
        ctx->CSSetShader(cs_pages.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 4, srvs);
        ID3D11Buffer* cbs[3] = {clut_cb.Get(), scatter_cb.Get(), pages_cb.Get()};
        ctx->CSSetConstantBuffers(0, 3, cbs);
        ctx->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
        ctx->Dispatch(op.count * 32u, 1, 1);
        ID3D11UnorderedAccessView* none = nullptr;
        ctx->CSSetUnorderedAccessViews(0, 1, &none, nullptr);
        ID3D11ShaderResourceView* nsrv[4] = {};
        ctx->CSSetShaderResources(0, 4, nsrv);
    }
    void clut_load(const GpuClutCB& c) {
        ctx->UpdateSubresource(clut_cb.Get(), 0, nullptr, &c, 0, 0);
        unbind_om();
        ID3D11UnorderedAccessView* uavs[2] = {vram_uav.Get(), clut_uav.Get()};
        ID3D11ShaderResourceView* srv = swz_srv.Get();
        ctx->CSSetShader(cs_clut.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 1, &srv);
        ID3D11Buffer* cbs[1] = {clut_cb.Get()};
        ctx->CSSetConstantBuffers(0, 1, cbs);
        ctx->CSSetUnorderedAccessViews(0, 2, uavs, nullptr);
        ctx->Dispatch(1, 1, 1);
        ID3D11UnorderedAccessView* none[2] = {};
        ctx->CSSetUnorderedAccessViews(0, 2, none, nullptr);
    }
    void readback(std::vector<u8>& out) {
        unbind_om();
        ctx->CopyResource(staging.Get(), vram.Get());
        D3D11_MAPPED_SUBRESOURCE m{};
        out.resize(kVramBytes);
        if (SUCCEEDED(ctx->Map(staging.Get(), 0, D3D11_MAP_READ, 0, &m))) {
            std::memcpy(out.data(), m.pData, kVramBytes);
            ctx->Unmap(staging.Get(), 0);
        }
    }
    // Rare (none on the measured routes): through the CPU in TRXPOS.DIR order, as GsCore::local_copy.
    void copy(const GpuOp& op) {
        std::vector<u8> mem;
        readback(mem);
        GsMemory m;
        std::memcpy(m.data(), mem.data(), kVramBytes);
        const u64 b = op.b, p = op.p, rg = op.rg;
        const u32 sbp = bits(b, 0, 14), sbw = bits(b, 16, 6), spsm = bits(b, 24, 6);
        const u32 dbp = bits(b, 32, 14), dbw = bits(b, 48, 6), dpsm = bits(b, 56, 6);
        const u32 ssax = bits(p, 0, 11), ssay = bits(p, 16, 11), dsax = bits(p, 32, 11), dsay = bits(p, 48, 11);
        const u32 dir = bits(p, 59, 2);
        const u32 rrw = bits(rg, 0, 12), rrh = bits(rg, 32, 12);
        for (u32 j = 0; j < rrh; ++j) {
            const u32 y = (dir & 1u) ? rrh - 1u - j : j;
            for (u32 i = 0; i < rrw; ++i) {
                const u32 x = (dir & 2u) ? rrw - 1u - i : i;
                m.write(dpsm, dbp, dbw, dsax + x, dsay + y, m.read(spsm, sbp, sbw, ssax + x, ssay + y));
            }
        }
        // Back through the staging buffer + CopyResource: UpdateSubresource into buffers with raw views was not
        // repeatable on this driver (docs/ANALYSIS/25 §11 driver note).
        D3D11_MAPPED_SUBRESOURCE w{};
        if (SUCCEEDED(ctx->Map(staging.Get(), 0, D3D11_MAP_WRITE, 0, &w))) {
            std::memcpy(w.pData, m.data(), kVramBytes);
            ctx->Unmap(staging.Get(), 0);
            ctx->CopyResource(vram.Get(), staging.Get());
        }
        wait_idle();
    }
    bool ensure_frame(u32 w, u32 h) {
        if (frame && frame_w == w && frame_h == h) return true;
        frame.Reset();
        frame_staging.Reset();
        frame_uav.Reset();
        frame_srv.Reset();
        D3D11_TEXTURE2D_DESC td{};
        td.Width = w;
        td.Height = h;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        td.SampleDesc.Count = 1;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(dev->CreateTexture2D(&td, nullptr, &frame))) return false;
        dev->CreateUnorderedAccessView(frame.Get(), nullptr, &frame_uav);
        dev->CreateShaderResourceView(frame.Get(), nullptr, &frame_srv);
        td.Usage = D3D11_USAGE_STAGING;
        td.BindFlags = 0;
        td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        dev->CreateTexture2D(&td, nullptr, &frame_staging);
        frame_w = w;
        frame_h = h;
        return frame_uav && frame_srv;
    }
};

GsD3D11Executor::GsD3D11Executor() : d_(std::make_unique<Impl>()) {}
GsD3D11Executor::~GsD3D11Executor() = default;

bool GsD3D11Executor::init(ID3D11Device* dev, ID3D11DeviceContext* ctx, bool want_rov, bool exact, std::string& err) {
    Impl& d = *d_;
    d.dev = dev;
    d.ctx = ctx;
    {
        D3D11_FEATURE_DATA_D3D11_OPTIONS o{};
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &o, sizeof o)) && o.ConstantBufferOffsetting)
            ctx->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(d.ctx1.GetAddressOf()));
    }
    caps_ = query_caps(dev);
    if (caps_.feature_level < D3D_FEATURE_LEVEL_11_0) {
        err = "feature level 11_0 required";
        return false;
    }
    exact_ = exact;
    if (exact_ && !(caps_.doubles && caps_.ext_doubles)) {
        err = "exact mode needs DoublePrecisionFloatShaderOps and ExtendedDoublesShaderInstructions";
        return false;
    }
    rov_ = want_rov && caps_.rov;
    const std::string draw = std::string(hlsl::kHlslCommon) + hlsl::kHlslDraw + hlsl::kHlslPixel;
    const std::string comp = std::string(hlsl::kHlslCommon) + hlsl::kHlslCompute;
    const std::string crtc = std::string(hlsl::kHlslCommon) + hlsl::kHlslCrtc;
    const D3D_SHADER_MACRO rw[] = {{"VRAM_T", "RWByteAddressBuffer"}, {nullptr, nullptr}};
    ComPtr<ID3DBlob> vs, cs1, cs2, cs3;
    if (!compile_one(draw, "vs_main", "vs_5_0", rw, vs, err)) return false;
    if (!compile_one(comp, "cs_clut", "cs_5_0", rw, cs1, err)) return false;
    if (!compile_one(comp, "cs_scatter", "cs_5_0", rw, cs2, err)) return false;
    ComPtr<ID3DBlob> cs4, cs5;
    if (!compile_one(comp, "cs_pages", "cs_5_0", rw, cs4, err)) return false;
    dev->CreateComputeShader(cs4->GetBufferPointer(), cs4->GetBufferSize(), nullptr, &d.cs_pages);
    if (!compile_one(comp, "cs_clut_resolve", "cs_5_0", rw, cs5, err)) return false;
    dev->CreateComputeShader(cs5->GetBufferPointer(), cs5->GetBufferSize(), nullptr, &d.cs_clut_resolve);
    if (!compile_one(crtc, "cs_crtc", "cs_5_0", rw, cs3, err)) return false;
    dev->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &d.vs);
    dev->CreateComputeShader(cs1->GetBufferPointer(), cs1->GetBufferSize(), nullptr, &d.cs_clut);
    dev->CreateComputeShader(cs2->GetBufferPointer(), cs2->GetBufferSize(), nullptr, &d.cs_scatter);
    dev->CreateComputeShader(cs3->GetBufferPointer(), cs3->GetBufferSize(), nullptr, &d.cs_crtc);
    {  // the native renderer's GPU vertex stage; without it native draws stay on the CPU model (not an error)
        ComPtr<ID3DBlob> csn;
        std::string en;
        if (compile_one(hlsl::kHlslNative, "cs_native", "cs_5_0", nullptr, csn, en))
            dev->CreateComputeShader(csn->GetBufferPointer(), csn->GetBufferSize(), nullptr, &d.cs_native);
        else
            std::fprintf(stderr, "p3fes: d3d11 GS: native vertex stage unavailable: %s\n", en.c_str());
    }
    auto try_ps = [&](bool use_rov, std::string& e) {
        std::vector<D3D_SHADER_MACRO> defs = {{"VRAM_T", use_rov ? "RasterizerOrderedByteAddressBuffer" : "RWByteAddressBuffer"}};
        if (exact_) defs.push_back({"EXACT", "1"});
        defs.push_back({nullptr, nullptr});
        for (const char* target : {"ps_5_0", "ps_5_1"}) {
            ComPtr<ID3DBlob> blob;
            std::string e1;
            d.ps.Reset();
            if (compile_one(draw, "ps_main", target, defs.data(), blob, e1) &&
                SUCCEEDED(dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &d.ps))) {
                ps_target_ = target;
                return true;
            }
            e += std::string(target) + ": " + (e1.empty() ? "CreatePixelShader failed" : e1) + " ";
        }
        return false;
    };
    std::string e;
    if (rov_ && !try_ps(true, e)) {
        std::fprintf(stderr, "p3fes: d3d11 GS: ROV pixel shader unavailable (%s); split draws\n", e.c_str());
        rov_ = false;
    }
    if (!rov_ && !try_ps(false, err)) return false;
    d.rov = rov_;
    const D3D11_INPUT_ELEMENT_DESC el[] = {
        {"POS", 0, DXGI_FORMAT_R32G32_SINT, 0, offsetof(GpuVertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"ZV", 0, DXGI_FORMAT_R32_FLOAT, 0, offsetof(GpuVertex, z), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COL", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, offsetof(GpuVertex, rgba), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"STQ", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(GpuVertex, s), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UV", 0, DXGI_FORMAT_R16G16_UINT, 0, offsetof(GpuVertex, uv), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"FOG", 0, DXGI_FORMAT_R32_UINT, 0, offsetof(GpuVertex, f), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"CBI", 0, DXGI_FORMAT_R32_UINT, 0, offsetof(GpuVertex, cbi), D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    if (FAILED(dev->CreateInputLayout(el, 7, vs->GetBufferPointer(), vs->GetBufferSize(), &d.layout))) {
        err = "CreateInputLayout failed";
        return false;
    }

    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = kVramBytes;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    if (FAILED(dev->CreateBuffer(&bd, nullptr, &d.vram))) {
        err = "VRAM buffer";
        return false;
    }
    D3D11_UNORDERED_ACCESS_VIEW_DESC ud{};
    ud.Format = DXGI_FORMAT_R32_TYPELESS;
    ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    ud.Buffer.NumElements = kVramBytes / 4;
    ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
    dev->CreateUnorderedAccessView(d.vram.Get(), &ud, &d.vram_uav);
    D3D11_BUFFER_DESC sd = bd;
    sd.Usage = D3D11_USAGE_STAGING;
    sd.BindFlags = 0;
    sd.MiscFlags = 0;
    sd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;  // readbacks; local copies write back
    dev->CreateBuffer(&sd, nullptr, &d.staging);

    const SwizzleTables& t = swizzle_tables();
    std::vector<u32> tab;
    tab.reserve(45056);
    for (const auto& row : t.ct32) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.z32) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.ct16) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.ct16s) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.z16) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.z16s) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.t8) for (u16 v : row) tab.push_back(v);
    for (const auto& row : t.t4) for (u16 v : row) tab.push_back(v);
    D3D11_BUFFER_DESC tb{};
    tb.ByteWidth = static_cast<UINT>(tab.size() * 4);
    tb.Usage = D3D11_USAGE_IMMUTABLE;
    tb.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tb.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    const D3D11_SUBRESOURCE_DATA init{tab.data(), 0, 0};
    dev->CreateBuffer(&tb, &init, &d.swz);
    D3D11_SHADER_RESOURCE_VIEW_DESC rv{};
    rv.Format = DXGI_FORMAT_R32_TYPELESS;
    rv.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    rv.BufferEx.NumElements = static_cast<UINT>(tab.size());
    rv.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
    dev->CreateShaderResourceView(d.swz.Get(), &rv, &d.swz_srv);

    D3D11_BUFFER_DESC cbd{};
    cbd.ByteWidth = 2048;
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    cbd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    dev->CreateBuffer(&cbd, nullptr, &d.clut);
    ud.Buffer.NumElements = 512;
    dev->CreateUnorderedAccessView(d.clut.Get(), &ud, &d.clut_uav);
    rv.BufferEx.NumElements = 512;
    dev->CreateShaderResourceView(d.clut.Get(), &rv, &d.clut_srv);
    D3D11_BUFFER_DESC csd{};
    csd.ByteWidth = 2048;
    csd.Usage = D3D11_USAGE_STAGING;
    csd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    dev->CreateBuffer(&csd, nullptr, &d.clut_staging);

    D3D11_BUFFER_DESC c1{};
    c1.ByteWidth = sizeof(GpuDrawCB);
    c1.Usage = D3D11_USAGE_DYNAMIC;
    c1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    c1.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    dev->CreateBuffer(&c1, nullptr, &d.cb);
    c1.ByteWidth = 16;
    dev->CreateBuffer(&c1, nullptr, &d.group_cb);
    D3D11_BUFFER_DESC c2{};
    c2.ByteWidth = 32;
    c2.Usage = D3D11_USAGE_DEFAULT;
    c2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    dev->CreateBuffer(&c2, nullptr, &d.clut_cb);
    c2.ByteWidth = 16;
    dev->CreateBuffer(&c2, nullptr, &d.scatter_cb);
    dev->CreateBuffer(&c2, nullptr, &d.pages_cb);
    c2.ByteWidth = sizeof(CrtcCB);
    dev->CreateBuffer(&c2, nullptr, &d.crtc_cb);
    c2.ByteWidth = 16;
    dev->CreateBuffer(&c2, nullptr, &d.native_cb);

    D3D11_RASTERIZER_DESC rd{};
    rd.FillMode = D3D11_FILL_SOLID;
    rd.CullMode = D3D11_CULL_NONE;
    rd.DepthClipEnable = FALSE;
    rd.ScissorEnable = TRUE;
    dev->CreateRasterizerState(&rd, &d.rs);

    D3D11_QUERY_DESC qd{D3D11_QUERY_TIMESTAMP_DISJOINT, 0};
    dev->CreateQuery(&qd, &d.q_disjoint);
    qd.Query = D3D11_QUERY_TIMESTAMP;
    dev->CreateQuery(&qd, &d.q_t0);
    dev->CreateQuery(&qd, &d.q_t1);
    if (!d.vram_uav || !d.swz_srv || !d.clut_uav || !d.clut_srv || !d.clut_staging || !d.cb || !d.group_cb || !d.rs || !d.crtc_cb || !d.staging) {
        err = "resource creation failed";
        return false;
    }
    return true;
}

void GsD3D11Executor::reset(const u8* vram, const std::array<u16, 512>& clut) {
    Impl& d = *d_;
    d.unbind_om();
    d.ctx->UpdateSubresource(d.vram.Get(), 0, nullptr, vram, kVramBytes, kVramBytes);
    std::vector<u32> v(512);
    for (int i = 0; i < 512; ++i) v[i] = clut[i];
    d.ctx->UpdateSubresource(d.clut.Get(), 0, nullptr, v.data(), 2048, 2048);
    d.wait_idle();
}

void GsD3D11Executor::execute(const OpList& l) {
    Impl& d = *d_;
    if (l.ops.empty()) return;
    Impl::Slot& s = d.upload(l);
    d.native_stage(l, s);
    for (std::size_t i = 0; i < l.ops.size();) i = d.run_op(l, i, s);
    d.end_draws();
    d.unbind_om();
}

double GsD3D11Executor::execute_timed(const OpList& l, double* issue_ms) {
    Impl& d = *d_;
    d.ctx->Begin(d.q_disjoint.Get());
    d.ctx->End(d.q_t0.Get());
    const auto c0 = std::chrono::steady_clock::now();
    execute(l);
    if (issue_ms)
        *issue_ms = std::min(*issue_ms, std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - c0).count());
    d.ctx->End(d.q_t1.Get());
    d.ctx->End(d.q_disjoint.Get());
    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT dj{};
    while (d.ctx->GetData(d.q_disjoint.Get(), &dj, sizeof dj, 0) == S_FALSE) {
    }
    UINT64 t0 = 0, t1 = 0;
    while (d.ctx->GetData(d.q_t0.Get(), &t0, sizeof t0, 0) == S_FALSE) {
    }
    while (d.ctx->GetData(d.q_t1.Get(), &t1, sizeof t1, 0) == S_FALSE) {
    }
    if (dj.Disjoint || dj.Frequency == 0) return -1.0;
    return static_cast<double>(t1 - t0) * 1000.0 / static_cast<double>(dj.Frequency);
}

bool GsD3D11Executor::execute_profiled(const OpList& l, GpuOpProfile& out) {
    Impl& d = *d_;
    out = GpuOpProfile{};
    if (l.ops.empty()) return true;
    const std::size_t n = l.ops.size() + 2;  // upload, every op
    while (d.prof_q.size() < n) {
        D3D11_QUERY_DESC qd{D3D11_QUERY_TIMESTAMP, 0};
        ComPtr<ID3D11Query> q;
        if (FAILED(d.dev->CreateQuery(&qd, &q))) return false;
        d.prof_q.push_back(q);
    }
    d.ctx->Begin(d.q_disjoint.Get());
    d.ctx->End(d.prof_q[0].Get());
    Impl::Slot& s = d.upload(l);
    d.native_stage(l, s);
    d.ctx->End(d.prof_q[1].Get());
    std::vector<std::size_t> run_end;  // ops [run start, run end) of each timestamp
    std::size_t q = 2;
    for (std::size_t i = 0; i < l.ops.size();) {
        const std::size_t j = d.run_op(l, i, s);
        d.ctx->End(d.prof_q[q++].Get());
        run_end.push_back(j);
        i = j;
    }
    d.end_draws();
    d.unbind_om();
    d.ctx->End(d.q_disjoint.Get());
    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT dj{};
    while (d.ctx->GetData(d.q_disjoint.Get(), &dj, sizeof dj, 0) == S_FALSE) {
    }
    if (dj.Disjoint || dj.Frequency == 0) return false;
    std::vector<UINT64> t(n);
    for (std::size_t i = 0; i < run_end.size() + 2; ++i)
        while (d.ctx->GetData(d.prof_q[i].Get(), &t[i], sizeof t[i], 0) == S_FALSE) {
        }
    const double k = 1000.0 / static_cast<double>(dj.Frequency);
    out.upload_ms = static_cast<double>(t[1] - t[0]) * k;
    std::size_t start = 0;
    for (std::size_t r = 0; r < run_end.size(); ++r) {
        const unsigned kind = static_cast<unsigned>(l.ops[start].kind);
        out.count[kind] += run_end[r] - start;
        out.calls[kind] += 1;
        out.ms[kind] += static_cast<double>(t[r + 2] - t[r + 1]) * k;
        start = run_end[r];
    }
    out.total_ms = static_cast<double>(t[run_end.size() + 1] - t[0]) * k;
    return true;
}

void GsD3D11Executor::readback_vram(std::vector<u8>& out) { d_->readback(out); }

bool GsD3D11Executor::native_stage() const noexcept { return d_->cs_native != nullptr; }

bool GsD3D11Executor::readback_clut(std::array<u16, 512>& out) {
    Impl& d = *d_;
    d.unbind_om();
    d.ctx->CopyResource(d.clut_staging.Get(), d.clut.Get());
    D3D11_MAPPED_SUBRESOURCE m{};
    if (FAILED(d.ctx->Map(d.clut_staging.Get(), 0, D3D11_MAP_READ, 0, &m))) return false;
    const u32* v = static_cast<const u32*>(m.pData);  // one u32 per entry, the halfword in the low bits
    for (int i = 0; i < 512; ++i) out[i] = static_cast<u16>(v[i]);
    d.ctx->Unmap(d.clut_staging.Get(), 0);
    return true;
}

bool GsD3D11Executor::compose(const DisplayRegs& disp, ID3D11ShaderResourceView** srv, u32& width, u32& height) {
    Impl& d = *d_;
    CrtcCB c;
    if (!crtc_constants(disp, c, width, height)) return false;
    if (!d.ensure_frame(width, height)) return false;
    d.ctx->UpdateSubresource(d.crtc_cb.Get(), 0, nullptr, &c, 0, 0);
    d.unbind_om();
    ID3D11UnorderedAccessView* uavs[2] = {d.vram_uav.Get(), d.frame_uav.Get()};
    ID3D11ShaderResourceView* sw = d.swz_srv.Get();
    d.ctx->CSSetShader(d.cs_crtc.Get(), nullptr, 0);
    d.ctx->CSSetShaderResources(0, 1, &sw);
    ID3D11Buffer* cb = d.crtc_cb.Get();
    d.ctx->CSSetConstantBuffers(0, 1, &cb);
    d.ctx->CSSetUnorderedAccessViews(0, 2, uavs, nullptr);
    d.ctx->Dispatch((width + 7u) / 8u, (height + 7u) / 8u, 1);
    ID3D11UnorderedAccessView* none[2] = {};
    d.ctx->CSSetUnorderedAccessViews(0, 2, none, nullptr);
    if (srv) *srv = d.frame_srv.Get();
    return true;
}

bool GsD3D11Executor::compose_readback(const DisplayRegs& disp, Frame& out) {
    Impl& d = *d_;
    u32 w = 0, h = 0;
    out = Frame{};
    if (!compose(disp, nullptr, w, h)) return false;
    d.ctx->CopyResource(d.frame_staging.Get(), d.frame.Get());
    D3D11_MAPPED_SUBRESOURCE m{};
    if (FAILED(d.ctx->Map(d.frame_staging.Get(), 0, D3D11_MAP_READ, 0, &m))) return false;
    out.width = w;
    out.height = h;
    out.rgba.resize(static_cast<std::size_t>(w) * h);
    for (u32 y = 0; y < h; ++y)
        std::memcpy(out.rgba.data() + static_cast<std::size_t>(y) * w, static_cast<const u8*>(m.pData) + static_cast<std::size_t>(y) * m.RowPitch, w * 4u);
    d.ctx->Unmap(d.frame_staging.Get(), 0);
    return true;
}

bool GsD3D11Executor::create_banks(u32 n) {
    Impl& d = *d_;
    d.banks.clear();
    if (!d.dev) return false;
    std::vector<Impl::Bank> nb(n);
    for (Impl::Bank& b : nb) {
        D3D11_BUFFER_DESC bd{};
        bd.ByteWidth = kVramBytes;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
        D3D11_UNORDERED_ACCESS_VIEW_DESC ud{};
        ud.Format = DXGI_FORMAT_R32_TYPELESS;
        ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
        ud.Buffer.NumElements = kVramBytes / 4;
        ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
        if (FAILED(d.dev->CreateBuffer(&bd, nullptr, &b.vram)) || FAILED(d.dev->CreateUnorderedAccessView(b.vram.Get(), &ud, &b.vram_uav)))
            return false;
        bd.ByteWidth = 2048;
        ud.Buffer.NumElements = 512;
        D3D11_SHADER_RESOURCE_VIEW_DESC rv{};
        rv.Format = DXGI_FORMAT_R32_TYPELESS;
        rv.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
        rv.BufferEx.NumElements = 512;
        rv.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
        if (FAILED(d.dev->CreateBuffer(&bd, nullptr, &b.clut)) || FAILED(d.dev->CreateUnorderedAccessView(b.clut.Get(), &ud, &b.clut_uav)) ||
            FAILED(d.dev->CreateShaderResourceView(b.clut.Get(), &rv, &b.clut_srv)))
            return false;
    }
    d.banks = std::move(nb);
    return true;
}

u32 GsD3D11Executor::banks() const noexcept { return static_cast<u32>(d_->banks.size()); }

void GsD3D11Executor::save_bank(u32 b) {
    Impl& d = *d_;
    if (b >= d.banks.size()) return;
    d.unbind_om();
    d.ctx->CopyResource(d.banks[b].vram.Get(), d.vram.Get());
    d.ctx->CopyResource(d.banks[b].clut.Get(), d.clut.Get());
}

void GsD3D11Executor::copy_bank(u32 dst, u32 src) {
    Impl& d = *d_;
    if (dst >= d.banks.size() || src >= d.banks.size() || dst == src) return;
    d.unbind_om();
    d.ctx->CopyResource(d.banks[dst].vram.Get(), d.banks[src].vram.Get());
    d.ctx->CopyResource(d.banks[dst].clut.Get(), d.banks[src].clut.Get());
}

void GsD3D11Executor::swap_bank(u32 b) {
    Impl& d = *d_;
    if (b >= d.banks.size()) return;
    d.unbind_om();
    Impl::Bank& k = d.banks[b];
    std::swap(d.vram, k.vram);
    std::swap(d.vram_uav, k.vram_uav);
    std::swap(d.clut, k.clut);
    std::swap(d.clut_uav, k.clut_uav);
    std::swap(d.clut_srv, k.clut_srv);
}

// ---- Renderer ----------------------------------------------------------------------------------------------

struct GsD3D11Renderer::Gpu {
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    ComPtr<IDXGISwapChain> swap;
    ComPtr<ID3D11RenderTargetView> rtv;
    ComPtr<ID3D11VertexShader> vs;
    ComPtr<ID3D11PixelShader> ps;
    ComPtr<ID3D11SamplerState> point, linear;
    GsD3D11Executor exec;
    Options opt;
    int buf_w = 0, buf_h = 0;
    DisplayRegs last_disp{};
    bool have_disp = false;
    bool present_error_logged = false;
    HANDLE timer = nullptr;             // PresentPlan::At waits (high-resolution waitable timer)
    std::deque<PresentRecord> pending;  // presented, waiting for their DXGI display time
    double exec_ms = 0.0;               // list execution since the previous present
    u32 lists = 0;
    // Decoupled display rate: the last guest frames composed (PresentPlan::Latch), each due at its own time.
    struct Latched {
        ComPtr<ID3D11Texture2D> tex;
        ComPtr<ID3D11ShaderResourceView> srv;
        u32 w = 0, h = 0;
        bool valid = false, have = false;  // have: a picture (a circuit was enabled)
        long long due = 0, submit = 0, dequeue = 0, ready = 0;
        u64 tag = 0;
        double exec_ms = 0.0;
        u32 lists = 0;
    };
    Latched lat[4];
    // Options::gpu_timing: a ring of timestamp query sets, polled without waiting.
    struct Timer {
        ComPtr<ID3D11Query> dj, t0, t1;
        bool pending = false;
    };
    std::array<Timer, 8> timers{};
    unsigned timer_next = 0;
};

namespace {

// Dispatches the calling thread's window messages: a host-side wait must never stop the window from responding.
void pump_thread_messages() {
    MSG m;
    bool quit = false;
    WPARAM quit_code = 0;
    while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
        if (m.message == WM_QUIT) {
            quit = true;
            quit_code = m.wParam;
            continue;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    if (quit) PostQuitMessage(static_cast<int>(quit_code));  // for the host's own pump
}

} // namespace

template <class Pred>
bool GsD3D11Renderer::wait_pumping(std::unique_lock<std::mutex>& lk, std::condition_variable& cv, Pred pred, double timeout_s) {
    // (the time waited is added to Stats::host_wait_ms under the lock, which every return path holds)
    struct Account {
        Stats& st;
        std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
        ~Account() { st.host_wait_ms += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); }
    } account{st_};
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::duration<double>(timeout_s);
    while (!pred()) {
        if (std::chrono::steady_clock::now() >= deadline) return false;
        cv.wait_for(lk, std::chrono::milliseconds(5));
        if (pred()) break;
        lk.unlock();
        pump_thread_messages();
        lk.lock();
    }
    return true;
}

GsD3D11Renderer::GsD3D11Renderer() = default;
GsD3D11Renderer::~GsD3D11Renderer() { stop(); }

std::string GsD3D11Renderer::description() const { return desc_; }

bool GsD3D11Renderer::start(HWND window, const Options& opt, std::string& why) {
    stop();
    {
        std::lock_guard<std::mutex> lk(m_);
        stop_ = false;
        started_ = false;
        start_ok_ = false;
        start_why_.clear();
        queue_.clear();
        st_ = Stats{};
        offscreen_ = window == nullptr;
        sync_timeout_s_ = opt.sync_timeout_s > 0.0 ? opt.sync_timeout_s : 10.0;
        max_queued_ = opt.max_queued ? opt.max_queued : 1u;
    }
    exited_ = false;
    const auto t_start = std::chrono::steady_clock::now();
    thread_ = std::thread([this, window, opt] { run(window, opt); });
    std::unique_lock<std::mutex> lk(m_);
    // The calling thread owns the window: keep its messages flowing while the render thread creates the device and
    // the window's swap chain (DXGI may send the window messages), and give up after a while.
    if (!wait_pumping(lk, done_cv_, [this] { return started_; }, 60.0)) {
        why = "the render thread did not finish its initialisation within 60 s";
        lk.unlock();
        stop();
        return false;
    }
    if (!start_ok_) {
        why = start_why_;
        lk.unlock();
        stop();
        return false;
    }
    char b[64];
    std::snprintf(b, sizeof b, "; started in %.2f s",
                  std::chrono::duration<double>(std::chrono::steady_clock::now() - t_start).count());
    desc_ += b;
    return true;
}

void GsD3D11Renderer::stop() {
    if (!thread_.joinable()) return;
    std::unique_lock<std::mutex> lk(m_);
    stop_ = true;
    cv_.notify_all();
    // The render thread uses this object to the end, so it is always joined (a detached thread would outlive the
    // object: a use-after-free once the owner destroys it). The calling thread keeps dispatching its window's
    // messages while it waits, so a window stays responsive however long the driver takes; a slow stop is reported.
    if (!wait_pumping(lk, done_cv_, [this] { return exited_; }, 3.0)) {
        std::fprintf(stderr, "p3fes: d3d11 GS: the render thread is still finishing after 3 s; waiting for it\n");
        while (!wait_pumping(lk, done_cv_, [this] { return exited_; }, 3600.0)) {
        }
    }
    lk.unlock();
    thread_.join();
}

void GsD3D11Renderer::submit(OpList&& ops, const DisplayRegs& disp, const PresentPlan& plan) {
    {
        std::lock_guard<std::mutex> lk(m_);
        ++st_.submitted;
        if (queue_.size() >= max_queued_ && !queue_.back().reset_vram) {
            // Behind: append to the newest queued frame (its present shows the later picture). The EE side never waits.
            // A present the newest frame was to make is kept unless the new list brings its own.
            queue_.back().ops.append(ops);
            queue_.back().disp = disp;
            const u32 merged = queue_.back().plan.merged + 1;  // (frame interpolation: the list spans slices)
            if (plan.mode != PresentPlan::Mode::Skip) queue_.back().plan = plan;
            queue_.back().plan.merged = merged;
            ++st_.merged;
        } else {
            queue_.push_back(Frame_{std::move(ops), disp, plan});
        }
    }
    cv_.notify_one();
}

void GsD3D11Renderer::recycle(OpList& out) {
    std::lock_guard<std::mutex> lk(m_);
    if (spare_.empty()) return;
    std::swap(out, spare_.back());
    spare_.pop_back();
    out.clear();
}

void GsD3D11Renderer::take_present_log(std::vector<PresentRecord>& out) {
    std::lock_guard<std::mutex> lk(m_);
    out.insert(out.end(), present_log_.begin(), present_log_.end());
    present_log_.clear();
}

void GsD3D11Renderer::reset_memory(const u8* vram, const std::array<u16, 512>& clut) {
    Frame_ f;
    f.reset_vram = std::make_shared<std::vector<u8>>(vram, vram + kVramBytes);
    f.reset_clut = clut;
    {
        std::lock_guard<std::mutex> lk(m_);
        queue_.push_back(std::move(f));  // never merged: it must stay between the frames before and after it
    }
    cv_.notify_one();
}

void GsD3D11Renderer::set_view(int client_w, int client_h, int x, int y, int w, int h) {
    {
        std::lock_guard<std::mutex> lk(m_);
        client_w_ = client_w;
        client_h_ = client_h;
        vx_ = x;
        vy_ = y;
        vw_ = w;
        vh_ = h;
    }
    cv_.notify_one();
}

bool GsD3D11Renderer::sync_vram(std::vector<u8>& out, std::array<u16, 512>* clut) {
    if (!thread_.joinable()) return false;
    std::unique_lock<std::mutex> lk(m_);
    ++sync_requests_;
    sync_kind_ = 1;
    sync_done_ = false;
    cv_.notify_one();
    wait_pumping(lk, done_cv_, [this] { return sync_done_ || stop_ || exited_; }, sync_timeout_s_);
    --sync_requests_;
    if (!sync_done_ || !sync_ok_ || sync_vram_.size() != kVramBytes) return false;
    out = std::move(sync_vram_);
    if (clut) *clut = sync_clut_;
    return true;
}

bool GsD3D11Renderer::sync_frame(Frame& out) {
    if (!thread_.joinable()) return false;
    std::unique_lock<std::mutex> lk(m_);
    ++sync_requests_;
    sync_kind_ = 2;
    sync_done_ = false;
    cv_.notify_one();
    wait_pumping(lk, done_cv_, [this] { return sync_done_ || stop_ || exited_; }, sync_timeout_s_);
    --sync_requests_;
    if (!sync_done_ || !sync_ok_) return false;
    out = std::move(sync_frame_);
    return !out.empty();
}

GsD3D11Renderer::Stats GsD3D11Renderer::stats() const {
    std::lock_guard<std::mutex> lk(m_);
    Stats s = st_;
    if (thread_.joinable()) {
        ULONG64 c = 0;
        if (QueryThreadCycleTime(const_cast<std::thread&>(thread_).native_handle(), &c)) s.thread_cycles = c;
    }
    return s;
}

bool GsD3D11Renderer::init_thread(HWND window, const Options& opt, std::string& why) {
    g_ = std::make_unique<Gpu>();
    Gpu& g = *g_;
    g.opt = opt;
    // Frame pacing (windowed): the render thread's work per frame is short and its presents are timed, so it may
    // run above the guest thread without starving it.
    if (opt.mmcss) {
        DWORD task = 0;
        if (!AvSetMmThreadCharacteristicsW(L"Games", &task) && opt.thread_priority) SetThreadPriority(GetCurrentThread(), opt.thread_priority);
    } else if (opt.thread_priority) {
        SetThreadPriority(GetCurrentThread(), opt.thread_priority);
    }
    g.timer = CreateWaitableTimerExW(nullptr, nullptr, 0x00000002 /* CREATE_WAITABLE_TIMER_HIGH_RESOLUTION */, TIMER_ALL_ACCESS);
    if (!g.timer) g.timer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    if (const char* t = std::getenv("P3FES_D3D11_TEST_FAIL")) test_fail_ = std::strcmp(t, "start") == 0 ? 1 : std::strcmp(t, "present") == 0 ? 2 : 0;
    if (test_fail_ == 1) {
        why = "forced by P3FES_D3D11_TEST_FAIL=start";
        return false;
    }
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, opt.debug ? D3D11_CREATE_DEVICE_DEBUG : 0, levels, 2,
                                   D3D11_SDK_VERSION, &g.dev, nullptr, &g.ctx);
    if (FAILED(hr) && opt.debug) {
        std::fprintf(stderr, "p3fes: d3d11 GS: no debug device (Graphics Tools missing?), using a plain one\n");
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2, D3D11_SDK_VERSION, &g.dev, nullptr, &g.ctx);
    }
    if (SUCCEEDED(hr) && opt.debug) enable_debug_messages(g.dev.Get(), opt.debug_break);
    if (FAILED(hr)) {
        char b[96];
        std::snprintf(b, sizeof b, "no hardware D3D11 device with feature level 11_0 (hr=0x%08lX)", static_cast<unsigned long>(hr));
        why = b;
        return false;
    }
    caps_ = query_caps(g.dev.Get());
    if (!caps_.rov && opt.want_rov) {
        why = "the adapter has no rasterizer-ordered views (ROVsSupported = no): " + caps_.summary();
        return false;
    }
    if (!g.exec.init(g.dev.Get(), g.ctx.Get(), opt.want_rov, opt.exact, why)) return false;
    if (!window) {
        // Offscreen (headless): no swap chain, no present shaders; GS memory and the picture are only read back.
        std::vector<u8> zeros(kVramBytes, 0);
        g.exec.reset(zeros.data(), std::array<u16, 512>{});
        char b[160];
        std::snprintf(b, sizeof b, "; pixel shader %s, %s, %s attributes, offscreen", g.exec.ps_target(),
                      g.exec.rov() ? "ROV" : "split draws", opt.exact ? "exact" : "interpolated");
        desc_ = caps_.summary() + b;
        native_stage_ = g.exec.native_stage();
        return true;
    }
    // Swap chain for the host's window.
    ComPtr<IDXGIDevice> dxgi;
    ComPtr<IDXGIAdapter> adapter;
    ComPtr<IDXGIFactory> factory;
    if (FAILED(g.dev.As(&dxgi)) || FAILED(dxgi->GetAdapter(&adapter)) || FAILED(adapter->GetParent(__uuidof(IDXGIFactory), &factory))) {
        why = "DXGI factory unavailable";
        return false;
    }
    RECT cr{};
    GetClientRect(window, &cr);
    g.buf_w = std::max<int>(1, cr.right - cr.left);
    g.buf_h = std::max<int>(1, cr.bottom - cr.top);
    DXGI_SWAP_CHAIN_DESC scd{};
    scd.BufferCount = 2;
    scd.BufferDesc.Width = static_cast<UINT>(g.buf_w);
    scd.BufferDesc.Height = static_cast<UINT>(g.buf_h);
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = window;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    if (opt.frame_latency) {
        ComPtr<IDXGIDevice1> d1;
        if (SUCCEEDED(g.dev.As(&d1))) d1->SetMaximumFrameLatency(opt.frame_latency);
    }
    hr = factory->CreateSwapChain(g.dev.Get(), &scd, &g.swap);
    if (FAILED(hr)) {
        char b[96];
        std::snprintf(b, sizeof b, "CreateSwapChain failed (hr=0x%08lX)", static_cast<unsigned long>(hr));
        why = b;
        return false;
    }
    factory->MakeWindowAssociation(window, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);
    ComPtr<ID3D11Texture2D> bb;
    g.swap->GetBuffer(0, __uuidof(ID3D11Texture2D), &bb);
    g.dev->CreateRenderTargetView(bb.Get(), nullptr, &g.rtv);
    const std::string present = hlsl::kHlslPresent;
    ComPtr<ID3DBlob> vs, ps;
    if (!compile_one(present, "vs_present", "vs_5_0", nullptr, vs, why) || !compile_one(present, "ps_present", "ps_5_0", nullptr, ps, why))
        return false;
    g.dev->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &g.vs);
    g.dev->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &g.ps);
    D3D11_SAMPLER_DESC sd{};
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    g.dev->CreateSamplerState(&sd, &g.point);
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    g.dev->CreateSamplerState(&sd, &g.linear);
    // Power-on GS memory (zeros) and CLUT, as GsCore starts.
    std::vector<u8> zeros(kVramBytes, 0);
    g.exec.reset(zeros.data(), std::array<u16, 512>{});
    char b[160];
    std::snprintf(b, sizeof b, "; pixel shader %s, %s, %s attributes, vsync %s", g.exec.ps_target(),
                  g.exec.rov() ? "ROV" : "split draws", opt.exact ? "exact" : "interpolated", opt.vsync ? "on" : "off");
    desc_ = caps_.summary() + b;
    native_stage_ = g.exec.native_stage();
    return true;
}

bool GsD3D11Renderer::resize_if_needed() {
    Gpu& g = *g_;
    int cw, ch;
    {
        std::lock_guard<std::mutex> lk(m_);
        cw = client_w_;
        ch = client_h_;
    }
    if (cw <= 0 || ch <= 0 || (cw == g.buf_w && ch == g.buf_h)) return true;
    g.ctx->OMSetRenderTargets(0, nullptr, nullptr);
    g.rtv.Reset();
    if (FAILED(g.swap->ResizeBuffers(0, static_cast<UINT>(cw), static_cast<UINT>(ch), DXGI_FORMAT_UNKNOWN, 0))) return false;
    ComPtr<ID3D11Texture2D> bb;
    g.swap->GetBuffer(0, __uuidof(ID3D11Texture2D), &bb);
    g.dev->CreateRenderTargetView(bb.Get(), nullptr, &g.rtv);
    g.buf_w = cw;
    g.buf_h = ch;
    return true;
}

bool GsD3D11Renderer::present_frame(const DisplayRegs& disp, PresentRecord* rec) {
    return prepare_present(disp, rec) && commit_present(rec);
}

D3D11_VIEWPORT GsD3D11Renderer::picture_viewport() {
    Gpu& g = *g_;
    int x, y, vw, vh;
    {
        std::lock_guard<std::mutex> lk(m_);
        x = vx_;
        y = vy_;
        vw = vw_;
        vh = vh_;
    }
    if (vw <= 0 || vh <= 0) {  // no layout yet: 4:3 fit
        vh = g.buf_h;
        vw = g.buf_h * 4 / 3;
        if (vw > g.buf_w) {
            vw = g.buf_w;
            vh = g.buf_w * 3 / 4;
        }
        x = (g.buf_w - vw) / 2;
        y = (g.buf_h - vh) / 2;
    }
    return D3D11_VIEWPORT{static_cast<float>(x), static_cast<float>(y), static_cast<float>(vw), static_cast<float>(vh), 0.0f, 1.0f};
}

bool GsD3D11Renderer::prepare_present(const DisplayRegs& disp, PresentRecord* rec) {
    if (test_fail_ == 2) return false;  // P3FES_D3D11_TEST_FAIL=present: never present (fallback test)
    Gpu& g = *g_;
    resize_if_needed();
    ID3D11ShaderResourceView* srv = nullptr;
    u32 w = 0, h = 0;
    const bool have = g.exec.compose(disp, &srv, w, h);
    draw_picture(have ? srv : nullptr, w, h, nullptr);
    if (rec) {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        rec->ready_qpc = t.QuadPart;
    }
    return true;
}

void GsD3D11Renderer::draw_picture(ID3D11ShaderResourceView* srv, u32 w, u32 h, const DisplayTick* tick_for_hook) {
    Gpu& g = *g_;
    ID3D11RenderTargetView* rtv = g.rtv.Get();
    g.ctx->OMSetRenderTargets(1, &rtv, nullptr);
    static constexpr float kBlack[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    g.ctx->ClearRenderTargetView(rtv, kBlack);
    const D3D11_VIEWPORT vp = picture_viewport();
    bool drawn = false;
    if (tick_for_hook && (display_hook_ || interp_)) {
        DisplayTick t = *tick_for_hook;
        t.dev = g.dev.Get();
        t.ctx = g.ctx.Get();
        t.rtv = rtv;
        t.viewport = vp;
        t.width = w;
        t.height = h;
        drawn = interp_ ? interp_->draw(g.exec, t) : display_hook_(t);  // track H's interpolator first
        g.ctx->OMSetRenderTargets(1, &rtv, nullptr);  // whatever the hook bound
    }
    if (!drawn && srv) {
        g.ctx->RSSetViewports(1, &vp);
        g.ctx->RSSetState(nullptr);
        g.ctx->IASetInputLayout(nullptr);
        g.ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        g.ctx->VSSetShader(g.vs.Get(), nullptr, 0);
        g.ctx->PSSetShader(g.ps.Get(), nullptr, 0);
        g.ctx->PSSetShaderResources(0, 1, &srv);
        ID3D11SamplerState* smp = g.opt.linear ? g.linear.Get() : g.point.Get();
        g.ctx->PSSetSamplers(0, 1, &smp);
        g.ctx->Draw(4, 0);
        ID3D11ShaderResourceView* none = nullptr;
        g.ctx->PSSetShaderResources(0, 1, &none);
    }
    g.ctx->OMSetRenderTargets(0, nullptr, nullptr);
}

bool GsD3D11Renderer::latch_frame(const DisplayRegs& disp, const PresentPlan& plan, long long submit_qpc, long long dequeue_qpc) {
    Gpu& g = *g_;
    // The slot of the oldest due time (four slots: the shown frame, the next one and two arriving early).
    int slot = 0;
    for (int i = 0; i < 4; ++i) {
        if (!g.lat[i].valid) {
            slot = i;
            break;
        }
        if (g.lat[i].due < g.lat[slot].due) slot = i;
    }
    Gpu::Latched& L = g.lat[slot];
    ID3D11ShaderResourceView* srv = nullptr;
    u32 w = 0, h = 0;
    L.have = g.exec.compose(disp, &srv, w, h);
    if (L.have && srv) {
        ComPtr<ID3D11Resource> res;
        srv->GetResource(&res);
        ComPtr<ID3D11Texture2D> src;
        if (FAILED(res.As(&src))) return false;
        D3D11_TEXTURE2D_DESC d{};
        src->GetDesc(&d);
        D3D11_TEXTURE2D_DESC have{};
        if (L.tex) L.tex->GetDesc(&have);
        if (!L.tex || have.Width != d.Width || have.Height != d.Height || have.Format != d.Format) {
            D3D11_TEXTURE2D_DESC nd = d;
            nd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            nd.Usage = D3D11_USAGE_DEFAULT;
            nd.CPUAccessFlags = 0;
            nd.MiscFlags = 0;
            L.tex.Reset();
            L.srv.Reset();
            if (FAILED(g.dev->CreateTexture2D(&nd, nullptr, &L.tex))) return false;
            D3D11_SHADER_RESOURCE_VIEW_DESC sd{};
            srv->GetDesc(&sd);
            if (FAILED(g.dev->CreateShaderResourceView(L.tex.Get(), &sd, &L.srv))) return false;
        }
        g.ctx->CopyResource(L.tex.Get(), src.Get());
    }
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    L.valid = true;
    L.w = w;
    L.h = h;
    L.due = plan.at_qpc;
    L.tag = plan.tag;
    L.submit = submit_qpc;
    L.dequeue = dequeue_qpc;
    L.ready = t.QuadPart;
    L.exec_ms = g.exec_ms;
    L.lists = g.lists;
    g.exec_ms = 0.0;
    g.lists = 0;
    return true;
}

bool GsD3D11Renderer::commit_present(PresentRecord* rec) {
    Gpu& g = *g_;
    if (rec) {
        // PresentPlan::At: the picture is in the back buffer; wait for its time (late: present at once).
        LARGE_INTEGER t, f;
        QueryPerformanceFrequency(&f);
        if (rec->target_qpc) {
            rec->late = rec->ready_qpc > rec->target_qpc;
            // Bounded (a bogus far-future time must not stall the thread): at most 250 ms.
            const long long until = std::min(rec->target_qpc, rec->ready_qpc + f.QuadPart / 4);
            for (;;) {
                QueryPerformanceCounter(&t);
                const long long left = until - t.QuadPart;
                if (left <= 0) break;
                const long long us = left * 1000000 / f.QuadPart;
                if (us > 700) {
                    // Wake ~0.5 ms early on the high-resolution timer, then spin the rest.
                    if (g.timer) {
                        LARGE_INTEGER due;
                        due.QuadPart = -static_cast<LONGLONG>((us - 500) * 10);
                        SetWaitableTimer(g.timer, &due, 0, nullptr, nullptr, FALSE);
                        WaitForSingleObject(g.timer, 300);
                    } else {
                        Sleep(static_cast<DWORD>((us - 500) / 1000));
                    }
                } else {
                    YieldProcessor();
                }
            }
        }
        QueryPerformanceCounter(&t);
        rec->present_qpc = t.QuadPart;
    }
    const HRESULT hr = g.swap->Present(g.opt.vsync ? 1u : 0u, 0);
    if (rec) {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        rec->return_qpc = t.QuadPart;
        UINT id = 0;
        if (SUCCEEDED(g.swap->GetLastPresentCount(&id))) rec->present_id = id;
    }
    if (FAILED(hr) && !g.present_error_logged) {
        std::fprintf(stderr, "p3fes: d3d11 GS: Present failed (hr=0x%08lX, device removed reason 0x%08lX)\n", static_cast<unsigned long>(hr),
                     static_cast<unsigned long>(g.dev->GetDeviceRemovedReason()));
        g.present_error_logged = true;
    }
    return SUCCEEDED(hr);
}

void GsD3D11Renderer::run(HWND window, Options opt) {
    std::string why;
    const bool ok = init_thread(window, opt, why);
    {
        std::lock_guard<std::mutex> lk(m_);
        started_ = true;
        start_ok_ = ok;
        start_why_ = why;
    }
    done_cv_.notify_all();
    if (!ok) {
        g_.reset();
        std::lock_guard<std::mutex> lk(m_);
        exited_ = true;
        done_cv_.notify_all();
        return;
    }
    Gpu& g = *g_;
    auto last_present = std::chrono::steady_clock::now();
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency(&qpf);
    const long long early = qpf.QuadPart * 3 / 2000;  // wake 1.5 ms before a timed present; commit_present spins the rest
    // A timed present (PresentPlan::At) whose picture is already drawn into the back buffer, waiting for its moment.
    // Lists that present nothing execute meanwhile: they change GS memory, never the back buffer.
    bool pending_on = false;
    PresentRecord pending_rec;
    // Statistics and the present log after a present (or a failed one).
    const auto finish_present = [&](PresentRecord& rec, bool presented, PresentPlan::Mode mode) {
        last_present = std::chrono::steady_clock::now();
        if (presented && g.opt.present_log) {
            // Frame statistics describe the newest present the display has shown: match it to its record.
            g.pending.push_back(rec);
            DXGI_FRAME_STATISTICS fs{};
            if (SUCCEEDED(g.swap->GetFrameStatistics(&fs))) {
                for (PresentRecord& p : g.pending)
                    if (p.present_id == fs.PresentCount && !p.sync_qpc) {
                        p.sync_qpc = fs.SyncQPCTime.QuadPart;
                        p.sync_refresh = fs.SyncRefreshCount;
                    }
            }
        }
        std::lock_guard<std::mutex> lk(m_);
        if (presented) ++st_.presented;
        if (presented && mode == PresentPlan::Mode::At) {
            ++st_.timed_presents;
            if (rec.late) ++st_.late_presents;
        }
        // Hand finished records over: those with a display time, or more than 4 presents old.
        while (!g.pending.empty() && (g.pending.front().sync_qpc || g.pending.size() > 4)) {
            present_log_.push_back(g.pending.front());
            g.pending.pop_front();
        }
        while (present_log_.size() > 4096) present_log_.pop_front();
    };
    const auto commit_pending = [&] {
        if (!pending_on) return;
        pending_on = false;
        const bool ok = commit_present(&pending_rec);
        finish_present(pending_rec, ok, PresentPlan::Mode::At);
    };
    // Decoupled display rate: the render thread's own display clock (Options::display).
    const bool decoupled = window && opt.display != DisplayRate::Game;
    long long next_tick = 0, last_tick = 0;
    u64 shown_tag = ~0ull;
    double refresh_s = 0.0, vblank_s = 0.0;
    long long next_dwm = 0;
    const auto plan_tick = [&] {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        const double hz = static_cast<double>(qpf.QuadPart);
        if (opt.display == DisplayRate::Refresh) {
            if (now.QuadPart >= next_dwm) {
                DWM_TIMING_INFO ti{};
                ti.cbSize = sizeof ti;
                if (SUCCEEDED(DwmGetCompositionTimingInfo(nullptr, &ti)) && ti.qpcRefreshPeriod) {
                    refresh_s = static_cast<double>(ti.qpcRefreshPeriod) / hz;
                    vblank_s = static_cast<double>(ti.qpcVBlank) / hz;
                }
                next_dwm = now.QuadPart + qpf.QuadPart;
            }
            const double p = refresh_s > 0.001 ? refresh_s : 1.0 / 60.0;
            // The next mid-refresh moment at least half a refresh after the last tick (and in the future).
            const double from = std::max(static_cast<double>(now.QuadPart) / hz, static_cast<double>(last_tick) / hz + 0.5 * p);
            const double k = std::ceil((from - vblank_s) / p - 0.5);
            next_tick = static_cast<long long>((vblank_s + (k + 0.5) * p) * hz);
        } else if (opt.display == DisplayRate::Cap) {
            const long long step = static_cast<long long>(hz / std::max(1.0, opt.display_hz));
            next_tick = std::max(now.QuadPart, last_tick + step);
        } else {
            next_tick = std::max(now.QuadPart, last_tick + qpf.QuadPart / 1000);
        }
    };
    // One display tick: the newest frame due by now (and the one after it, for the hook), drawn and presented.
    const auto display_tick = [&] {
        int a = -1, b = -1;
        for (int i = 0; i < 4; ++i) {
            const Gpu::Latched& L = g.lat[i];
            if (!L.valid) continue;
            if (L.due <= next_tick + qpf.QuadPart / 2000 && (a < 0 || L.due > g.lat[a].due)) a = i;
        }
        if (a < 0) {  // nothing due yet: the oldest frame there is
            for (int i = 0; i < 4; ++i)
                if (g.lat[i].valid && (a < 0 || g.lat[i].due < g.lat[a].due)) a = i;
        }
        if (a < 0) return;
        for (int i = 0; i < 4; ++i)
            if (g.lat[i].valid && g.lat[i].due > g.lat[a].due && (b < 0 || g.lat[i].due < g.lat[b].due)) b = i;
        const Gpu::Latched& A = g.lat[a];
        DisplayTick tick;
        tick.prev = A.have ? A.srv.Get() : nullptr;
        tick.prev_tag = A.tag;
        if (b >= 0) {
            const Gpu::Latched& B = g.lat[b];
            tick.next = B.have ? B.srv.Get() : nullptr;
            tick.next_tag = B.tag;
            const double span = static_cast<double>(B.due - A.due);
            tick.alpha = span > 0.0 ? std::clamp(static_cast<double>(next_tick - A.due) / span, 0.0, 1.0) : 0.0;
        }
        tick.tick_qpc = next_tick;
        resize_if_needed();
        draw_picture(A.have ? A.srv.Get() : nullptr, A.w, A.h, &tick);
        PresentRecord rec;
        rec.tag = A.tag;
        rec.target_qpc = next_tick;
        if (A.tag != shown_tag) {
            // The first display of this guest frame carries its render-side times.
            rec.submit_qpc = A.submit;
            rec.dequeue_qpc = A.dequeue;
            rec.ready_qpc = A.ready;
            rec.exec_ms = A.exec_ms;
            rec.lists = A.lists;
            shown_tag = A.tag;
        } else {
            LARGE_INTEGER q;
            QueryPerformanceCounter(&q);
            rec.ready_qpc = q.QuadPart;
        }
        const bool ok = test_fail_ != 2 && commit_present(&rec);
        if (rec.submit_qpc) rec.late = A.ready > A.due;
        finish_present(rec, ok, PresentPlan::Mode::At);
        last_tick = next_tick;
        next_tick = 0;
    };
    for (;;) {
        Frame_ f;
        bool have_frame = false, more = false, sync = false;
        {
            std::unique_lock<std::mutex> lk(m_);
            const auto work = [this] { return stop_ || !queue_.empty() || (sync_requests_ > 0 && !sync_done_); };
            const bool have_latched = decoupled && (g.lat[0].valid || g.lat[1].valid || g.lat[2].valid || g.lat[3].valid);
            if (have_latched && !next_tick) {
                lk.unlock();
                plan_tick();
                lk.lock();
            }
            if (pending_on || have_latched) {
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);
                const long long when = pending_on ? pending_rec.target_qpc : next_tick;
                const long long left = when - early - now.QuadPart;
                if (left > 0) cv_.wait_for(lk, std::chrono::microseconds(left * 1000000 / qpf.QuadPart), work);
            } else {
                cv_.wait(lk, work);
            }
            if (stop_) break;
            if (!queue_.empty()) {
                f = std::move(queue_.front());
                queue_.pop_front();
                have_frame = true;
                more = !queue_.empty();
            } else if (sync_requests_ > 0 && !sync_done_) {
                sync = true;
            }
        }
        if (pending_on) {
            // Present it when its time has come, or before anything that draws the back buffer again (a list that
            // presents, a readback's compose).
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            const bool due = now.QuadPart >= pending_rec.target_qpc - early;
            const bool redraws = sync || (have_frame && window && f.plan.mode != PresentPlan::Mode::Skip);
            if (due || redraws) commit_pending();
        }
        if (decoupled && next_tick) {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            if (now.QuadPart >= next_tick - early) display_tick();
        }
        if (have_frame) {
            const auto t0 = std::chrono::steady_clock::now();
            LARGE_INTEGER dq;
            QueryPerformanceCounter(&dq);
            // GPU timing: collect finished query sets (never waits), then open one around this list if a slot is free.
            double gpu_ms = 0.0;
            u64 gpu_n = 0;
            Gpu::Timer* timer = nullptr;
            if (g.opt.gpu_timing) {
                for (Gpu::Timer& q : g.timers) {
                    if (!q.pending) continue;
                    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT dj{};
                    UINT64 a = 0, b = 0;
                    if (g.ctx->GetData(q.dj.Get(), &dj, sizeof dj, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK ||
                        g.ctx->GetData(q.t0.Get(), &a, sizeof a, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK ||
                        g.ctx->GetData(q.t1.Get(), &b, sizeof b, D3D11_ASYNC_GETDATA_DONOTFLUSH) != S_OK)
                        continue;
                    q.pending = false;
                    if (!dj.Disjoint && dj.Frequency && b >= a) {
                        gpu_ms += static_cast<double>(b - a) * 1000.0 / static_cast<double>(dj.Frequency);
                        ++gpu_n;
                    }
                }
                Gpu::Timer& q = g.timers[g.timer_next];
                if (!q.pending) {
                    if (!q.dj) {
                        D3D11_QUERY_DESC qd{D3D11_QUERY_TIMESTAMP_DISJOINT, 0};
                        g.dev->CreateQuery(&qd, &q.dj);
                        qd.Query = D3D11_QUERY_TIMESTAMP;
                        g.dev->CreateQuery(&qd, &q.t0);
                        g.dev->CreateQuery(&qd, &q.t1);
                    }
                    if (q.dj && q.t0 && q.t1) {
                        timer = &q;
                        g.ctx->Begin(q.dj.Get());
                        g.ctx->End(q.t0.Get());
                    }
                }
            }
            if (f.reset_vram) g.exec.reset(f.reset_vram->data(), f.reset_clut);
            if (interp_) {  // frame interpolation (track H): records each guest frame's start memory and lists
                if (f.reset_vram) interp_->on_reset();
                interp_->before_execute(g.exec, f.ops, f.disp, f.plan);
            }
            g.exec.execute(f.ops);
            g.last_disp = f.disp;
            g.have_disp = true;
            g.exec_ms += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            ++g.lists;
            bool presented = false, wanted = false;
            PresentRecord rec;
            rec.tag = f.plan.tag;
            rec.submit_qpc = f.plan.submit_qpc;
            rec.dequeue_qpc = dq.QuadPart;
            if (decoupled) {
                // The display clock presents; lists only execute, and new guest frames are kept for it.
                if (f.plan.mode == PresentPlan::Mode::Latch || f.plan.mode == PresentPlan::Mode::At) latch_frame(f.disp, f.plan, f.plan.submit_qpc, dq.QuadPart);
            } else if (window) {
                switch (f.plan.mode) {
                case PresentPlan::Mode::Latch:  // (no display clock: present it as a timed present)
                    wanted = true;
                    rec.target_qpc = f.plan.at_qpc;
                    break;
                case PresentPlan::Mode::Auto:
                    // Catching up: present only the newest picture, but at least every 100 ms. Offscreen: never.
                    wanted = !more || t0 - last_present > std::chrono::milliseconds(100);
                    break;
                case PresentPlan::Mode::Skip:
                    break;
                case PresentPlan::Mode::At:
                    wanted = true;
                    rec.target_qpc = f.plan.at_qpc;
                    break;
                }
            }
            if (wanted) {
                rec.exec_ms = g.exec_ms;
                rec.lists = g.lists;
                g.exec_ms = 0.0;
                g.lists = 0;
                if (f.plan.mode == PresentPlan::Mode::At || f.plan.mode == PresentPlan::Mode::Latch) {
                    // Draw it now, present it at its time (the loop above), keep executing lists meanwhile.
                    if (prepare_present(f.disp, &rec)) {
                        pending_rec = rec;
                        pending_on = true;
                    } else {
                        finish_present(rec, false, PresentPlan::Mode::At);
                    }
                } else {
                    PresentRecord* r = g.opt.present_log ? &rec : nullptr;
                    presented = prepare_present(f.disp, r) && commit_present(r);
                    finish_present(rec, presented, f.plan.mode);
                }
            }
            if (timer) {
                g.ctx->End(timer->t1.Get());
                g.ctx->End(timer->dj.Get());
                timer->pending = true;
                g.timer_next = (g.timer_next + 1) % static_cast<unsigned>(g.timers.size());
            }
            const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            if (g.opt.debug) drain_debug_messages(g.dev.Get(), "p3fes: gpu-debug:");
            std::lock_guard<std::mutex> lk(m_);
            if (spare_.size() < 4) spare_.push_back(std::move(f.ops));  // storage for the host's next lists (recycle)
            ++st_.executed;
            if (window && f.plan.mode == PresentPlan::Mode::Auto && !presented) ++st_.skipped_presents;
            st_.gpu_ms_last = ms;
            st_.busy_ms_total += ms;
            st_.gpu_ms_total += gpu_ms;
            st_.gpu_frames += gpu_n;
            continue;
        }
        if (sync) {
            std::vector<u8> v;
            std::array<u16, 512> clut{};
            Frame fr;
            int kind;
            {
                std::lock_guard<std::mutex> lk(m_);
                kind = sync_kind_;
            }
            bool ok = true;
            if (kind == 1) {
                g.exec.readback_vram(v);
                ok = g.exec.readback_clut(clut);
            } else if (g.have_disp) {
                g.exec.compose_readback(g.last_disp, fr);
            }
            // A removed device reads back garbage (or nothing): the host must not take it for GS memory.
            const HRESULT removed = g.dev->GetDeviceRemovedReason();
            if (FAILED(removed)) {
                std::fprintf(stderr, "p3fes: d3d11 GS: device removed (reason 0x%08lX): readback refused\n",
                             static_cast<unsigned long>(removed));
                ok = false;
            }
            {
                std::lock_guard<std::mutex> lk(m_);
                sync_vram_ = std::move(v);
                sync_clut_ = clut;
                sync_frame_ = std::move(fr);
                sync_ok_ = ok;
                sync_done_ = true;
            }
            done_cv_.notify_all();
        }
    }
    if (g.timer) CloseHandle(g.timer);
    g.timer = nullptr;
    if (g.opt.test_stop_delay_ms) std::this_thread::sleep_for(std::chrono::milliseconds(g.opt.test_stop_delay_ms));  // tests: a slow stop
    {
        std::lock_guard<std::mutex> lk(m_);
        for (const PresentRecord& p : g.pending) present_log_.push_back(p);
    }
    g_.reset();
    {
        std::lock_guard<std::mutex> lk(m_);
        exited_ = true;
    }
    done_cv_.notify_all();
}

} // namespace p3fes::gs
