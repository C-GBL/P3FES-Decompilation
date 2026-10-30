// Direct3D 11 implementation of IGsBackend: uploads the composed GS frame into a dynamic texture and draws it as
// one quad (a full-screen triangle pair generated from SV_VertexID), letterboxed to the PS2's 4:3 display aspect,
// point-sampled. Shaders are compiled at init with D3DCompile; if that fails, presents only clear the window
// (`shaders_ready()` reports it) and the frame is still available to --headless / PNG output.
//
// Host options (runtime/app/host_display.h sets them; the defaults are the self-test behaviour): the Present sync
// interval (--vsync), point or bilinear sampling, an explicit destination rectangle in back-buffer pixels (the
// letterbox policy lives in runtime/app/present.h), and `resize` to follow the window's client area. DXGI's own
// Alt+Enter (exclusive full screen) is disabled; the host toggles a borderless window instead.
#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

#include "p3fes/gs/gs_backend.h"

namespace p3fes::gs {

class D3D11Backend final : public IGsBackend {
public:
    D3D11Backend() = default;
    ~D3D11Backend() override;

    D3D11Backend(const D3D11Backend&) = delete;
    D3D11Backend& operator=(const D3D11Backend&) = delete;

    bool init(HWND window) override;
    void present_frame(const Frame& frame) override;
    void present() override;
    void shutdown() override;

    // Present(sync_interval): 1 waits for the display's vblank (default), 0 does not.
    void set_sync_interval(unsigned interval) noexcept { sync_interval_ = interval; }
    // Bilinear instead of point sampling of the frame texture.
    void set_linear_filter(bool linear) noexcept { linear_filter_ = linear; }
    // Destination rectangle in back-buffer pixels; a non-positive width or height restores the built-in 4:3 fit.
    void set_target_rect(int x, int y, int width, int height) noexcept {
        target_x_ = x;
        target_y_ = y;
        target_w_ = width;
        target_h_ = height;
    }
    // Resizes the swap chain's buffers (call when the client area changes); 0 x 0 (minimised) is ignored.
    bool resize(unsigned width, unsigned height);

    ID3D11Device*     device() const noexcept { return device_.Get(); }
    D3D_FEATURE_LEVEL feature_level() const noexcept { return feature_level_; }
    HRESULT           last_hresult() const noexcept { return last_hr_; }
    bool              shaders_ready() const noexcept { return vs_ != nullptr && ps_ != nullptr; }
    unsigned          frames_presented() const noexcept { return presented_; }

private:
    bool create_render_target();
    bool create_pipeline();
    bool ensure_texture(unsigned width, unsigned height);
    void draw();

    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    ComPtr<ID3D11Device>             device_;
    ComPtr<ID3D11DeviceContext>      context_;
    ComPtr<IDXGISwapChain>           swap_chain_;
    ComPtr<ID3D11RenderTargetView>   back_buffer_rtv_;
    ComPtr<ID3D11VertexShader>       vs_;
    ComPtr<ID3D11PixelShader>        ps_;
    ComPtr<ID3D11SamplerState>       sampler_;
    ComPtr<ID3D11SamplerState>       sampler_linear_;
    ComPtr<ID3D11Texture2D>          frame_tex_;
    ComPtr<ID3D11ShaderResourceView> frame_srv_;
    unsigned                         tex_w_ = 0, tex_h_ = 0;
    bool                             have_frame_ = false;
    unsigned                         presented_ = 0;
    D3D_FEATURE_LEVEL                feature_level_ = D3D_FEATURE_LEVEL_9_1;
    HRESULT                          last_hr_ = S_OK;
    HWND                             window_ = nullptr;
    unsigned                         sync_interval_ = 1;
    bool                             linear_filter_ = false;
    int                              target_x_ = 0, target_y_ = 0, target_w_ = 0, target_h_ = 0;
};

} // namespace p3fes::gs
