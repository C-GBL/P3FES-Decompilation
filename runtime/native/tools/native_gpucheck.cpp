// p3fes_native_gpucheck: the native renderer's GPU vertex stage (p3fes/gs/gs_native_hlsl.h) against the CPU semantic
// model (runtime/native/g3_model.h) on captured batch inputs (p3fes --native-capture). For every capture the GPU
// path takes (every variant but the full clipper): build the record, run cs_native on a hardware D3D11 device, read
// the triangle slots back and compare each vertex (window X/Y, Z, colour, STQ, fog) and each culling decision with
// what the CPU model's packet gives.
//
//   p3fes_native_gpucheck DIR [--verbose N]
#include "../g3_model.h"

#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_native_hlsl.h"
#include "p3fes/gs/gs_ops.h"
#include "p3fes/vu1/vu1_interp.h"
#include "p3fes/vu1/vu1_profile.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

using namespace p3fes;
using Microsoft::WRL::ComPtr;

namespace {

using Out = gs::GpuVertex;

ComPtr<ID3D11Buffer> make_buf(ID3D11Device* dev, UINT bytes, UINT bind, UINT misc, D3D11_USAGE usage, UINT cpu,
                              const void* init) {
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = (bytes + 15u) & ~15u;
    bd.Usage = usage;
    bd.BindFlags = bind;
    bd.MiscFlags = misc;
    bd.CPUAccessFlags = cpu;
    D3D11_SUBRESOURCE_DATA sd{init, 0, 0};
    ComPtr<ID3D11Buffer> b;
    dev->CreateBuffer(&bd, init ? &sd : nullptr, &b);
    return b;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: p3fes_native_gpucheck DIR [--verbose N]\n");
        return 2;
    }
    int verbose = 0;
    for (int i = 2; i < argc; ++i)
        if (!std::strcmp(argv[i], "--verbose") && i + 1 < argc) verbose = std::atoi(argv[++i]);
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    D3D_FEATURE_LEVEL fl;
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dev, &fl, &ctx))) {
        std::fprintf(stderr, "no D3D11 device\n");
        return 1;
    }
    ComPtr<ID3DBlob> blob, errs;
    const std::string src = gs::hlsl::kHlslNative;
    if (FAILED(D3DCompile(src.data(), src.size(), "native", nullptr, nullptr, "cs_native", "cs_5_0", 0, 0, &blob, &errs))) {
        std::fprintf(stderr, "compile: %s\n", errs ? static_cast<const char*>(errs->GetBufferPointer()) : "?");
        return 1;
    }
    ComPtr<ID3D11ComputeShader> cs;
    dev->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &cs);

    auto st = std::make_unique<vu1::VU1State>();
    u64 files = 0, batches = 0, verts = 0, bad_pos = 0, bad_col = 0, bad_stq = 0, bad_z = 0, bad_fog = 0, bad_cull = 0;
    double max_xy = 0;
    int shown = 0;
    // Batches go through GsOpRecorder::on_native_gpu_batch in groups (as in the game: one list, many records, shared
    // palettes, header words filled by the recorder), one dispatch per group.
    gs::GsCore core;
    gs::GsOpRecorder recorder(core, false);
    struct Item {
        native::G3Batch b;
        u32 flags = 0, slots = 0, prog = 0;
        std::string name;
    };
    std::vector<Item> group;
    double rec_ns = 0, recq_ns = 0;
    u64 timed = 0;
    std::vector<u32> rec;
    const auto flush = [&]() {
        if (group.empty()) return;
        gs::OpList l;
        recorder.take(l);
        const u32 total = l.nat_slots;
        const u32 nb = static_cast<u32>(l.nat_tab.size() / 4);
        if (nb != group.size() || total == 0) {
            std::printf("group mismatch: %u records for %zu batches\n", nb, group.size());
            group.clear();
            return;
        }
        auto nin = make_buf(dev.Get(), static_cast<UINT>(l.nat_in.size() * 4), D3D11_BIND_SHADER_RESOURCE,
                            D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS, D3D11_USAGE_DEFAULT, 0, l.nat_in.data());
        auto ntab = make_buf(dev.Get(), static_cast<UINT>(l.nat_tab.size() * 4), D3D11_BIND_SHADER_RESOURCE,
                             D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS, D3D11_USAGE_DEFAULT, 0, l.nat_tab.data());
        const UINT out_bytes = total * 3u * static_cast<UINT>(sizeof(Out));
        auto nout = make_buf(dev.Get(), out_bytes, D3D11_BIND_UNORDERED_ACCESS, D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS,
                             D3D11_USAGE_DEFAULT, 0, nullptr);
        auto stg = make_buf(dev.Get(), out_bytes, 0, 0, D3D11_USAGE_STAGING, D3D11_CPU_ACCESS_READ, nullptr);
        const u32 cbv[4] = {nb, total, 0, 0};
        auto cb = make_buf(dev.Get(), 16, D3D11_BIND_CONSTANT_BUFFER, 0, D3D11_USAGE_DEFAULT, 0, cbv);
        D3D11_SHADER_RESOURCE_VIEW_DESC rv{};
        rv.Format = DXGI_FORMAT_R32_TYPELESS;
        rv.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
        rv.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
        rv.BufferEx.NumElements = static_cast<UINT>((l.nat_in.size() + 3) & ~std::size_t{3});
        ComPtr<ID3D11ShaderResourceView> s0, s1;
        dev->CreateShaderResourceView(nin.Get(), &rv, &s0);
        rv.BufferEx.NumElements = static_cast<UINT>(l.nat_tab.size());
        dev->CreateShaderResourceView(ntab.Get(), &rv, &s1);
        D3D11_UNORDERED_ACCESS_VIEW_DESC ud{};
        ud.Format = DXGI_FORMAT_R32_TYPELESS;
        ud.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
        ud.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
        ud.Buffer.NumElements = ((out_bytes + 15u) & ~15u) / 4u;
        ComPtr<ID3D11UnorderedAccessView> u0;
        dev->CreateUnorderedAccessView(nout.Get(), &ud, &u0);
        ID3D11ShaderResourceView* srvs[2] = {s0.Get(), s1.Get()};
        ctx->CSSetShader(cs.Get(), nullptr, 0);
        ctx->CSSetShaderResources(0, 2, srvs);
        ID3D11Buffer* cbp = cb.Get();
        ctx->CSSetConstantBuffers(0, 1, &cbp);
        ID3D11UnorderedAccessView* uav = u0.Get();
        ctx->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
        ctx->Dispatch((total + 63u) / 64u, 1, 1);
        ctx->CopyResource(stg.Get(), nout.Get());
        D3D11_MAPPED_SUBRESOURCE m{};
        if (FAILED(ctx->Map(stg.Get(), 0, D3D11_MAP_READ, 0, &m))) {
            group.clear();
            return;
        }
        for (u32 gi = 0; gi < nb; ++gi) {
            const Item& it = group[gi];
            const native::G3Batch& b = it.b;
            const Out* o = static_cast<const Out*>(m.pData) + static_cast<std::size_t>(l.nat_tab[gi * 4]) * 3u;
            const bool fogged = (it.flags & 1u) != 0;
            const bool list = (it.flags & 4u) != 0;
            bool shown_this = false;
            for (u32 t = 0; t < it.slots; ++t) {
                const u32 i0 = list ? 3u * t : t;
                const bool culled_m = ((static_cast<u32>(b.v[i0 + 2].xyzw[3]) >> 15) & 1u) != 0;
                const bool zero = o[t * 3].x == -1073741824 && o[t * 3 + 1].x == -1073741824 && o[t * 3].y == -1073741824;
                if (culled_m != zero) ++bad_cull;
                if (culled_m || zero) continue;
                for (u32 k = 0; k < 3; ++k) {
                    const native::G3OutVertex& mv = b.v[i0 + k];
                    const Out& g = o[t * 3 + k];
                    ++verts;
                    const s32 mx = mv.xyzw[0] & 0xFFFF, my = mv.xyzw[1] & 0xFFFF;
                    const double dxy = std::max(std::abs(mx - g.x), std::abs(my - g.y));
                    max_xy = std::max(max_xy, dxy);
                    bool bad = false;
                    if (dxy > 2) {
                        ++bad_pos;
                        bad = true;
                    }
                    const double mz = fogged ? double((static_cast<u32>(mv.xyzw[2]) >> 4) & 0xFFFFFFu) : double(static_cast<u32>(mv.xyzw[2]));
                    if (std::fabs(mz - g.z) > std::max(4.0, 1e-4 * std::fabs(mz))) {
                        ++bad_z;
                        bad = true;
                    }
                    const float mc[4] = {float(mv.rgba[0] & 0xFF), float(mv.rgba[1] & 0xFF), float(mv.rgba[2] & 0xFF), float(mv.rgba[3] & 0xFF)};
                    const float gc[4] = {float(g.rgba & 0xFF), float((g.rgba >> 8) & 0xFF), float((g.rgba >> 16) & 0xFF), float(g.rgba >> 24)};
                    for (int j = 0; j < 4 && !(it.flags & 2u); ++j)
                        if (std::fabs(mc[j] - gc[j]) > 2) {
                            ++bad_col;
                            bad = true;
                            break;
                        }
                    const auto rel = [](float a, float c) {
                        const double d = std::fabs(double(a) - c), mm = std::max(std::fabs(double(a)), std::fabs(double(c)));
                        return mm == 0 ? 0.0 : d / mm;
                    };
                    if (rel(mv.s, g.s) > 1e-4 || rel(mv.t, g.t) > 1e-4 || rel(mv.q, g.q) > 1e-4) {
                        ++bad_stq;
                        bad = true;
                    }
                    if (fogged &&
                        std::fabs(double((static_cast<u32>(mv.xyzw[3]) >> 4) & 0xFFu) - double(g.f)) > 1) {
                        ++bad_fog;
                        bad = true;
                    }
                    if (bad && shown < verbose && !shown_this) {
                        ++shown;
                        shown_this = true;
                        std::printf("%s prog %u variant %s n=%u slot %u v%u: model x %d y %d z %.0f rgba %.0f %.0f %.0f %.0f stq %g %g %g\n"
                                    "      gpu   x %d y %d z %.0f rgba %.0f %.0f %.0f %.0f stq %g %g %g f %.0f\n",
                                    it.name.c_str(), it.prog, native::to_string(b.variant), b.n, t, k, mx, my, mz, mc[0], mc[1],
                                    mc[2], mc[3], mv.s, mv.t, mv.q, g.x, g.y, g.z, gc[0], gc[1], gc[2], gc[3], g.s, g.t, g.q, double(g.f));
                    }
                }
            }
        }
        ctx->Unmap(stg.Get(), 0);
        group.clear();
    };
    for (const auto& de : std::filesystem::recursive_directory_iterator(argv[1])) {
        if (!de.is_regular_file()) continue;
        u32 pc = 0;
        std::string prog;
        if (!vu1::load_run_input(de.path().string(), *st, pc, prog)) continue;
        const native::G3Prog gp = native::g3_identify(st->micro.bytes().data());
        if (gp == native::G3Prog::None) continue;
        ++files;
        if (pc == 0) native::g3_init(gp, *st);
        u32 slots = 0, prim = 0, palq = 0;
        const auto tr0 = std::chrono::steady_clock::now();
        bool okrec = false;
        for (int rep = 0; rep < 10; ++rep) okrec = native::g3_gpu_record(gp, *st, rec, slots, prim, palq);
        rec_ns += std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - tr0).count() / 10.0;
        if (!okrec) continue;
        Item it;
        if (!native::g3_model(gp, *st, it.b) || it.b.explicit_tris || it.b.culled_all) continue;
        ++batches;
        it.flags = rec[2];
        it.slots = slots;
        it.prog = rec[1];
        it.name = de.path().filename().string();
        std::vector<u32> pal(palq * 4u);
        if (palq) std::memcpy(pal.data(), st->data + 0x2B8u * 16u, palq * 16u);
        const auto tq0 = std::chrono::steady_clock::now();
        recorder.on_native_gpu_batch(core.regs(), rec.data(), static_cast<u32>(rec.size()), slots, nullptr, pal.data(),
                                     static_cast<u32>(pal.size()));
        recq_ns += std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - tq0).count();
        ++timed;
        group.push_back(std::move(it));
        if (group.size() >= 64) flush();
    }
    flush();
    std::printf("CPU per batch: record %.0f ns, recorder %.0f ns\n", rec_ns / double(timed ? timed : 1), recq_ns / double(timed ? timed : 1));
    std::printf("%llu captures, %llu GPU batches, %llu vertices compared: position %llu (max %.0f), Z %llu, colour %llu, STQ %llu, "
                "fog %llu, culling %llu mismatches\n",
                (unsigned long long)files, (unsigned long long)batches, (unsigned long long)verts, (unsigned long long)bad_pos, max_xy,
                (unsigned long long)bad_z, (unsigned long long)bad_col, (unsigned long long)bad_stq, (unsigned long long)bad_fog,
                (unsigned long long)bad_cull);
    return 0;
}
