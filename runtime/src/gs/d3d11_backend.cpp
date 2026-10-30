#include "p3fes/gs/d3d11_backend.h"

#include <d3dcompiler.h>

#include <cstring>

namespace p3fes::gs {

namespace {

// A quad as a 4-vertex triangle strip generated from SV_VertexID; the frame texture is point-sampled so a
// 640x448 GS frame keeps its pixels at integer scales.
constexpr char kShaderSource[] = R"(
Texture2D frame_tex : register(t0);
SamplerState frame_smp : register(s0);
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut vs_main(uint id : SV_VertexID) {
    VSOut o;
    float2 uv = float2(id & 1, id >> 1);
    o.pos = float4(uv.x * 2.0 - 1.0, 1.0 - uv.y * 2.0, 0.0, 1.0);
    o.uv = uv;
    return o;
}
float4 ps_main(VSOut i) : SV_Target { return float4(frame_tex.Sample(frame_smp, i.uv).rgb, 1.0); }
)";

} // namespace

D3D11Backend::~D3D11Backend() {
    shutdown();
}

bool D3D11Backend::init(HWND window) {
    shutdown();
    window_ = window;

    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 2;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = window;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
    // The debug layer is optional: it needs the Graphics Tools feature. Fall
    // back to a plain device if it is not installed.
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static constexpr D3D_FEATURE_LEVEL kLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
        kLevels, static_cast<UINT>(sizeof(kLevels) / sizeof(kLevels[0])),
        D3D11_SDK_VERSION, &scd, &swap_chain_, &device_, &feature_level_, &context_);

#if defined(_DEBUG)
    if (hr == DXGI_ERROR_SDK_COMPONENT_MISSING) {
        flags &= ~static_cast<UINT>(D3D11_CREATE_DEVICE_DEBUG);
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
            kLevels, static_cast<UINT>(sizeof(kLevels) / sizeof(kLevels[0])),
            D3D11_SDK_VERSION, &scd, &swap_chain_, &device_, &feature_level_, &context_);
    }
#endif

    if (FAILED(hr)) {
        // No hardware adapter (e.g. headless CI / RDP session): try WARP so the
        // smoke test can still exercise the pipeline.
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_WARP, nullptr, flags & ~static_cast<UINT>(D3D11_CREATE_DEVICE_DEBUG),
            kLevels, static_cast<UINT>(sizeof(kLevels) / sizeof(kLevels[0])),
            D3D11_SDK_VERSION, &scd, &swap_chain_, &device_, &feature_level_, &context_);
    }

    last_hr_ = hr;
    if (FAILED(hr)) {
        shutdown();
        return false;
    }

    if (!create_render_target()) {
        shutdown();
        return false;
    }
    // The host owns full-screen switching (a borderless window); keep DXGI's exclusive-mode Alt+Enter out of it.
    ComPtr<IDXGIFactory> factory;
    if (SUCCEEDED(swap_chain_->GetParent(__uuidof(IDXGIFactory), &factory))) factory->MakeWindowAssociation(window, DXGI_MWA_NO_ALT_ENTER);
    // A missing shader compiler is not fatal: presents then only clear the window.
    create_pipeline();
    return true;
}

bool D3D11Backend::resize(unsigned width, unsigned height) {
    if (!swap_chain_ || !context_ || width == 0 || height == 0) return false;
    context_->OMSetRenderTargets(0, nullptr, nullptr);
    back_buffer_rtv_.Reset();
    const HRESULT hr = swap_chain_->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr)) {
        last_hr_ = hr;
        return false;
    }
    return create_render_target();
}

bool D3D11Backend::create_render_target() {
    ComPtr<ID3D11Texture2D> back_buffer;
    HRESULT hr = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &back_buffer);
    if (FAILED(hr)) {
        last_hr_ = hr;
        return false;
    }
    hr = device_->CreateRenderTargetView(back_buffer.Get(), nullptr, &back_buffer_rtv_);
    if (FAILED(hr)) {
        last_hr_ = hr;
        return false;
    }
    return true;
}

bool D3D11Backend::create_pipeline() {
    ComPtr<ID3DBlob> vs_blob, ps_blob, errors;
    HRESULT hr = D3DCompile(kShaderSource, sizeof(kShaderSource) - 1, "gs_present", nullptr, nullptr, "vs_main",
                            "vs_4_0", 0, 0, &vs_blob, &errors);
    if (FAILED(hr)) {
        last_hr_ = hr;
        return false;
    }
    hr = D3DCompile(kShaderSource, sizeof(kShaderSource) - 1, "gs_present", nullptr, nullptr, "ps_main", "ps_4_0", 0, 0,
                    &ps_blob, &errors);
    if (FAILED(hr)) {
        last_hr_ = hr;
        return false;
    }
    if (FAILED(device_->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs_)) ||
        FAILED(device_->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &ps_))) {
        vs_.Reset();
        ps_.Reset();
        return false;
    }
    D3D11_SAMPLER_DESC sd = {};
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    if (FAILED(device_->CreateSamplerState(&sd, &sampler_))) return false;
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    return SUCCEEDED(device_->CreateSamplerState(&sd, &sampler_linear_));
}

bool D3D11Backend::ensure_texture(unsigned width, unsigned height) {
    if (frame_tex_ && tex_w_ == width && tex_h_ == height) return true;
    frame_srv_.Reset();
    frame_tex_.Reset();
    D3D11_TEXTURE2D_DESC td = {};
    td.Width = width;
    td.Height = height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Frame pixels are 0xAABBGGRR = bytes R, G, B, A
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DYNAMIC;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    HRESULT hr = device_->CreateTexture2D(&td, nullptr, &frame_tex_);
    if (SUCCEEDED(hr)) hr = device_->CreateShaderResourceView(frame_tex_.Get(), nullptr, &frame_srv_);
    last_hr_ = hr;
    if (FAILED(hr)) {
        frame_tex_.Reset();
        return false;
    }
    tex_w_ = width;
    tex_h_ = height;
    return true;
}

void D3D11Backend::present_frame(const Frame& frame) {
    if (!context_ || frame.empty()) {
        present();
        return;
    }
    if (ensure_texture(frame.width, frame.height)) {
        D3D11_MAPPED_SUBRESOURCE m = {};
        if (SUCCEEDED(context_->Map(frame_tex_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &m))) {
            for (u32 y = 0; y < frame.height; ++y) {
                std::memcpy(static_cast<u8*>(m.pData) + static_cast<std::size_t>(y) * m.RowPitch,
                            frame.rgba.data() + static_cast<std::size_t>(y) * frame.width, frame.width * 4u);
            }
            context_->Unmap(frame_tex_.Get(), 0);
            have_frame_ = true;
        }
    }
    present();
}

void D3D11Backend::draw() {
    ID3D11RenderTargetView* rtv = back_buffer_rtv_.Get();
    context_->OMSetRenderTargets(1, &rtv, nullptr);
    static constexpr float kClear[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    static constexpr float kNoFrame[4] = {0.05f, 0.10f, 0.20f, 1.0f};
    context_->ClearRenderTargetView(rtv, have_frame_ && shaders_ready() ? kClear : kNoFrame);
    if (!have_frame_ || !shaders_ready()) return;

    RECT rc = {};
    GetClientRect(window_, &rc);
    const float cw = static_cast<float>(rc.right - rc.left), ch = static_cast<float>(rc.bottom - rc.top);
    if (cw <= 0.0f || ch <= 0.0f) return;
    // The swap chain's buffers keep the window's creation size; DXGI stretches them to the client area. Fit a 4:3
    // rectangle (the PS2 display aspect) into the buffer.
    ComPtr<ID3D11Texture2D> bb;
    D3D11_TEXTURE2D_DESC bd = {};
    if (SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &bb))) bb->GetDesc(&bd);
    const float bw = bd.Width ? static_cast<float>(bd.Width) : cw, bh = bd.Height ? static_cast<float>(bd.Height) : ch;
    D3D11_VIEWPORT vp = {};
    if (target_w_ > 0 && target_h_ > 0) {
        vp.TopLeftX = static_cast<float>(target_x_);
        vp.TopLeftY = static_cast<float>(target_y_);
        vp.Width = static_cast<float>(target_w_);
        vp.Height = static_cast<float>(target_h_);
    } else if (bw * 3.0f > bh * 4.0f) {
        vp.Height = bh;
        vp.Width = bh * 4.0f / 3.0f;
        vp.TopLeftX = (bw - vp.Width) * 0.5f;
    } else {
        vp.Width = bw;
        vp.Height = bw * 3.0f / 4.0f;
        vp.TopLeftY = (bh - vp.Height) * 0.5f;
    }
    vp.MaxDepth = 1.0f;
    context_->RSSetViewports(1, &vp);
    context_->IASetInputLayout(nullptr);
    context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    context_->VSSetShader(vs_.Get(), nullptr, 0);
    context_->PSSetShader(ps_.Get(), nullptr, 0);
    ID3D11ShaderResourceView* srv = frame_srv_.Get();
    ID3D11SamplerState* smp = linear_filter_ && sampler_linear_ ? sampler_linear_.Get() : sampler_.Get();
    context_->PSSetShaderResources(0, 1, &srv);
    context_->PSSetSamplers(0, 1, &smp);
    context_->Draw(4, 0);
}

void D3D11Backend::present() {
    if (!context_ || !swap_chain_) {
        return;
    }
    draw();
    last_hr_ = swap_chain_->Present(sync_interval_, 0);
    if (SUCCEEDED(last_hr_)) ++presented_;
}

void D3D11Backend::shutdown() {
    if (context_) {
        context_->ClearState();
    }
    frame_srv_.Reset();
    frame_tex_.Reset();
    sampler_.Reset();
    sampler_linear_.Reset();
    ps_.Reset();
    vs_.Reset();
    tex_w_ = tex_h_ = 0;
    have_frame_ = false;
    back_buffer_rtv_.Reset();
    swap_chain_.Reset();
    context_.Reset();
    device_.Reset();
    window_ = nullptr;
}

} // namespace p3fes::gs
