// The on-screen frame-time overlay (windowed runs; F3 or --frame-overlay): a small translucent, click-through
// window over the top-left corner of the game window showing the new-frame rate, interval percentiles, the host's
// work per frame, hitches, the audio queue and a bar graph of the last 240 frame intervals against the 33.4 ms
// (green line) and 50 ms marks. Drawn with GDI into its own layered window, so it costs nothing on the render
// thread or in the swap chain; redrawn at most four times a second from the host loop. Diagnostics only.
#pragma once

#include <windows.h>

#include "frame_telemetry.h"

namespace p3fes::app {

class FrameOverlay {
public:
    FrameOverlay() = default;
    ~FrameOverlay();
    FrameOverlay(const FrameOverlay&) = delete;
    FrameOverlay& operator=(const FrameOverlay&) = delete;

    // Creates the (hidden) overlay window owned by `owner`. false when it cannot.
    bool create(HWND owner);
    void destroy();
    void set_visible(bool on);
    void toggle() { set_visible(!visible_); }
    bool visible() const { return visible_; }
    // New readout: redraws and follows the owner's client area (call from the host loop; cheap when hidden).
    void update(const FrameTelemetry::Live& l);

private:
    static LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    void paint(HDC dc);
    void follow();

    HWND owner_ = nullptr, hwnd_ = nullptr;
    bool visible_ = false, registered_ = false;
    HFONT font_ = nullptr;
    FrameTelemetry::Live live_{};
};

} // namespace p3fes::app
