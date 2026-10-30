// The host's window and what is shown in it (main.cpp, windowed modes only): a resizable Win32 window or a
// borderless full-screen one, the D3D11 presenter, the letterbox layout of the composed GS frame (present.h), PNG
// screenshots of the shown frame, and the window events the frame loop acts on (close, focus, hotkeys).
// Single-threaded: messages are dispatched only from `pump` and `wait`, i.e. between guest run slices.
#pragma once

#include <windows.h>

#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>

#include "p3fes/gs/d3d11_backend.h"
#include "p3fes/gs/gs_types.h"
#include "present.h"

namespace p3fes::app {

struct DisplayOptions {
    int client_w = 640, client_h = 480;  // windowed client area
    bool fullscreen = false;             // borderless, covering the monitor
    bool vsync = true;                   // Present sync interval 1 / 0
    ScaleMode scale = ScaleMode::Fit;
    std::uint8_t screenshot_key = 0x7B;  // F12; 0 = none
    std::uint8_t fullscreen_key = 0x7A;  // F11; 0 = none (Alt+Enter always toggles)
    std::uint8_t overlay_key = 0x72;     // F3: the frame-time overlay (frame_overlay.h); 0 = none
    std::filesystem::path screenshot_dir = "extracted/_ours/screens";
    // Another component presents into the window (the D3D11 GS renderer's own swap chain): open() creates no D3D11
    // device; layout changes go to `on_layout`, screenshots come from `external_frame`.
    bool external_presenter = false;
};

class HostDisplay {
public:
    HostDisplay() = default;
    ~HostDisplay();
    HostDisplay(const HostDisplay&) = delete;
    HostDisplay& operator=(const HostDisplay&) = delete;

    // Creates the window and the D3D11 device. false + `error` on failure.
    bool open(const DisplayOptions& opts, const wchar_t* title, std::string& error);
    void close();

    // Dispatches pending window messages; false once the window is gone (WM_QUIT) or a close was requested.
    bool pump();
    // Waits `seconds` on a high-resolution timer while dispatching window messages; returns early on a close.
    void wait(double seconds);

    // Uploads and presents `frame` (kept for screenshots and re-presents after a resize).
    void show(gs::Frame frame);
    // Presents the last frame again.
    void refresh();

    bool close_requested() const { return close_requested_; }
    bool focused() const;
    bool fullscreen() const { return fullscreen_; }
    void set_fullscreen(bool on);
    // Window title = base title + " - " + status (empty: the base title).
    void set_status(const std::string& status);

    // Writes the shown frame to <screenshot_dir>/<tag>.png (tag from `screenshot_tag`; "_2", "_3" ... when taken).
    // Returns the path written, empty on failure (the reason goes to stderr).
    std::filesystem::path screenshot();

    gs::D3D11Backend& backend() { return backend_; }
    HWND hwnd() const { return hwnd_; }

    std::function<void()> on_close;              // WM_CLOSE (the window stays until close())
    std::function<void()> on_overlay_key;        // DisplayOptions::overlay_key (the frame-time overlay)
    std::function<std::string()> screenshot_tag; // file stem for the next screenshot
    // External presenter: client size + picture rectangle after every layout change; the shown picture on demand.
    std::function<void(int client_w, int client_h, const ViewRect& r)> on_layout;
    std::function<gs::Frame()> external_frame;
    // Switches an external-presenter window back to the built-in presenter (fallback). false + `error` on failure.
    bool use_builtin_presenter(std::string& error);
    void relayout() { apply_layout(); }

private:
    static LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    LRESULT handle(UINT msg, WPARAM wparam, LPARAM lparam);
    void apply_layout();
    void on_key(WPARAM vk, LPARAM lparam, bool sys);

    DisplayOptions opts_{};
    std::wstring title_;
    HINSTANCE instance_ = nullptr;
    HWND hwnd_ = nullptr;
    bool class_registered_ = false;
    bool backend_ready_ = false;
    bool fullscreen_ = false;
    bool close_requested_ = false;
    bool quit_ = false;
    WINDOWPLACEMENT windowed_placement_{};
    HANDLE timer_ = nullptr;
    gs::D3D11Backend backend_;
    gs::Frame shown_;
    unsigned shots_ = 0;
};

} // namespace p3fes::app
