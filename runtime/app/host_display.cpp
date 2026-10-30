#include "host_display.h"

#include <cstdio>
#include <system_error>
#include <utility>

#include "p3fes/gs/gs_output.h"

#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

namespace p3fes::app {

namespace {

constexpr wchar_t kWindowClass[] = L"P3FES_MainWindow";
constexpr DWORD kWindowedStyle = WS_OVERLAPPEDWINDOW;
constexpr DWORD kFullscreenStyle = WS_POPUP;
constexpr int kDefaultFrameHeight = 448;  // this title's NTSC output until the first frame is shown

double now_seconds() {
    static const double freq = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return static_cast<double>(f.QuadPart);
    }();
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return static_cast<double>(t.QuadPart) / freq;
}

std::wstring widen(const std::string& s) {
    if (s.empty()) return {};
    const int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
    std::wstring w(static_cast<std::size_t>(n > 0 ? n : 0), L'\0');
    if (n > 0) MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), w.data(), n);
    return w;
}

} // namespace

HostDisplay::~HostDisplay() { close(); }

bool HostDisplay::open(const DisplayOptions& opts, const wchar_t* title, std::string& error) {
    close();
    opts_ = opts;
    title_ = title;
    instance_ = GetModuleHandleW(nullptr);
    // Per-monitor DPI awareness: the swap chain gets physical pixels, so integer scaling stays exact on scaled
    // displays (no DWM bitmap stretch). Fails harmlessly when the process already has a DPI mode.
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = proc;
    wc.hInstance = instance_;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWindowClass;
    if (!RegisterClassExW(&wc)) {
        error = "RegisterClassExW failed (error " + std::to_string(GetLastError()) + ")";
        return false;
    }
    class_registered_ = true;

    const UINT dpi = GetDpiForSystem();
    RECT rc = {0, 0, MulDiv(opts_.client_w, static_cast<int>(dpi), 96), MulDiv(opts_.client_h, static_cast<int>(dpi), 96)};
    AdjustWindowRectExForDpi(&rc, kWindowedStyle, FALSE, 0, dpi);
    hwnd_ = CreateWindowExW(0, kWindowClass, title_.c_str(), kWindowedStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
                            rc.bottom - rc.top, nullptr, nullptr, instance_, this);
    if (!hwnd_) {
        error = "CreateWindowExW failed (error " + std::to_string(GetLastError()) + ")";
        return false;
    }
    windowed_placement_.length = sizeof(WINDOWPLACEMENT);
    if (opts_.fullscreen) set_fullscreen(true);
    ShowWindow(hwnd_, SW_SHOW);

    if (!opts_.external_presenter && !use_builtin_presenter(error)) return false;
    apply_layout();

    timer_ = CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    if (!timer_) timer_ = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    return true;
}

bool HostDisplay::use_builtin_presenter(std::string& error) {
    if (backend_ready_) return true;
    if (!backend_.init(hwnd_)) {
        char b[96];
        std::snprintf(b, sizeof b, "D3D11 init failed (hr=0x%08lX)", static_cast<unsigned long>(backend_.last_hresult()));
        error = b;
        return false;
    }
    opts_.external_presenter = false;
    backend_ready_ = true;
    backend_.set_sync_interval(opts_.vsync ? 1u : 0u);
    backend_.set_linear_filter(opts_.scale == ScaleMode::Smooth);
    RECT cr = {};
    GetClientRect(hwnd_, &cr);
    backend_.resize(static_cast<unsigned>(cr.right), static_cast<unsigned>(cr.bottom));
    apply_layout();
    return true;
}

void HostDisplay::close() {
    if (timer_) CloseHandle(timer_);
    timer_ = nullptr;
    if (backend_ready_) backend_.shutdown();
    backend_ready_ = false;
    if (hwnd_ && IsWindow(hwnd_)) DestroyWindow(hwnd_);
    hwnd_ = nullptr;
    if (class_registered_) UnregisterClassW(kWindowClass, instance_);
    class_registered_ = false;
    fullscreen_ = close_requested_ = quit_ = false;
    shown_ = {};
}

LRESULT CALLBACK HostDisplay::proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_NCCREATE) {
        auto* self = static_cast<HostDisplay*>(reinterpret_cast<CREATESTRUCTW*>(lparam)->lpCreateParams);
        self->hwnd_ = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }
    auto* self = reinterpret_cast<HostDisplay*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (msg == WM_NCDESTROY) SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
    return self ? self->handle(msg, wparam, lparam) : DefWindowProcW(hwnd, msg, wparam, lparam);
}

LRESULT HostDisplay::handle(UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_CLOSE:
        // A request only: the frame loop stops the guest cleanly and destroys the window in close().
        close_requested_ = true;
        if (on_close) on_close();
        return 0;
    case WM_SIZE:
        if (opts_.external_presenter && wparam != SIZE_MINIMIZED && LOWORD(lparam) && HIWORD(lparam)) {
            apply_layout();
            return 0;
        }
        if (backend_ready_ && wparam != SIZE_MINIMIZED && LOWORD(lparam) && HIWORD(lparam)) {
            backend_.resize(LOWORD(lparam), HIWORD(lparam));
            apply_layout();
            backend_.present();
        }
        return 0;
    case WM_DPICHANGED: {
        const RECT* r = reinterpret_cast<const RECT*>(lparam);
        if (!fullscreen_) SetWindowPos(hwnd_, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER | SWP_NOACTIVATE);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYDOWN:
        on_key(wparam, lparam, false);
        return 0;
    case WM_SYSKEYDOWN:
        // Alt+Enter is ours; everything else (Alt+F4, Alt+Tab ...) keeps the default handling.
        if (wparam == VK_RETURN && (lparam & (1 << 29))) {
            on_key(wparam, lparam, true);
            return 0;
        }
        if (wparam == opts_.fullscreen_key || wparam == opts_.screenshot_key) on_key(wparam, lparam, true);
        break;
    case WM_SYSCHAR:
        if (wparam == '\r') return 0;  // no beep for Alt+Enter
        break;
    case WM_SYSCOMMAND:
        // Alt or F10 alone would enter the (absent) menu and swallow the next key presses.
        if ((wparam & 0xFFF0) == SC_KEYMENU && lparam == 0) return 0;
        break;
    default:
        break;
    }
    return DefWindowProcW(hwnd_, msg, wparam, lparam);
}

void HostDisplay::on_key(WPARAM vk, LPARAM lparam, bool sys) {
    if (lparam & (1 << 30)) return;  // auto-repeat
    if (sys && vk == VK_RETURN) {
        set_fullscreen(!fullscreen_);
        return;
    }
    if (opts_.fullscreen_key && vk == opts_.fullscreen_key) set_fullscreen(!fullscreen_);
    else if (opts_.screenshot_key && vk == opts_.screenshot_key) screenshot();
    else if (opts_.overlay_key && vk == opts_.overlay_key && on_overlay_key) on_overlay_key();
}

bool HostDisplay::pump() {
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) quit_ = true;
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return hwnd_ && !quit_ && !close_requested_ && IsWindow(hwnd_);
}

void HostDisplay::wait(double seconds) {
    const double end = now_seconds() + (seconds > 0.0 ? seconds : 0.0);
    for (;;) {
        if (!pump()) return;
        const double left = end - now_seconds();
        if (left <= 0.0) return;
        if (timer_) {
            LARGE_INTEGER due;
            due.QuadPart = -static_cast<LONGLONG>(left * 1e7);  // relative, 100 ns units
            if (due.QuadPart == 0) due.QuadPart = -1;
            SetWaitableTimer(timer_, &due, 0, nullptr, nullptr, FALSE);
            MsgWaitForMultipleObjectsEx(1, &timer_, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        } else {
            MsgWaitForMultipleObjectsEx(0, nullptr, static_cast<DWORD>(left * 1000.0), QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        }
    }
}

void HostDisplay::apply_layout() {
    if (!hwnd_ || (!backend_ready_ && !opts_.external_presenter)) return;
    RECT cr = {};
    GetClientRect(hwnd_, &cr);
    const int src_h = shown_.empty() ? kDefaultFrameHeight : static_cast<int>(shown_.height);
    const ViewRect r = display_rect(cr.right - cr.left, cr.bottom - cr.top, src_h, opts_.scale);
    if (opts_.external_presenter) {
        if (on_layout) on_layout(cr.right - cr.left, cr.bottom - cr.top, r);
        return;
    }
    backend_.set_target_rect(r.x, r.y, r.w, r.h);
}

void HostDisplay::show(gs::Frame frame) {
    if (opts_.external_presenter) return;
    const bool relayout = frame.height != shown_.height;
    shown_ = std::move(frame);
    if (relayout) apply_layout();
    backend_.present_frame(shown_);
}

void HostDisplay::refresh() {
    if (backend_ready_) backend_.present();
}

bool HostDisplay::focused() const { return hwnd_ && GetForegroundWindow() == hwnd_; }

void HostDisplay::set_fullscreen(bool on) {
    if (!hwnd_ || on == fullscreen_) return;
    const LONG_PTR visible = GetWindowLongPtrW(hwnd_, GWL_STYLE) & WS_VISIBLE;
    if (on) {
        GetWindowPlacement(hwnd_, &windowed_placement_);
        MONITORINFO mi = {};
        mi.cbSize = sizeof(mi);
        GetMonitorInfoW(MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST), &mi);
        const RECT& m = mi.rcMonitor;
        SetWindowLongPtrW(hwnd_, GWL_STYLE, static_cast<LONG_PTR>(kFullscreenStyle) | visible);
        SetWindowPos(hwnd_, HWND_TOP, m.left, m.top, m.right - m.left, m.bottom - m.top, SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
    } else {
        SetWindowLongPtrW(hwnd_, GWL_STYLE, static_cast<LONG_PTR>(kWindowedStyle) | visible);
        SetWindowPlacement(hwnd_, &windowed_placement_);
        SetWindowPos(hwnd_, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
    fullscreen_ = on;
}

void HostDisplay::set_status(const std::string& status) {
    if (!hwnd_) return;
    const std::wstring t = status.empty() ? title_ : title_ + L" - " + widen(status);
    SetWindowTextW(hwnd_, t.c_str());
}

std::filesystem::path HostDisplay::screenshot() {
    if (opts_.external_presenter && external_frame) shown_ = external_frame();
    if (shown_.empty()) {
        std::fprintf(stderr, "p3fes: screenshot: no frame shown yet\n");
        return {};
    }
    std::error_code ec;
    std::filesystem::create_directories(opts_.screenshot_dir, ec);
    const std::string stem = screenshot_tag ? screenshot_tag() : "shot_" + std::to_string(shots_);
    std::filesystem::path p = (opts_.screenshot_dir / (stem + ".png")).make_preferred();
    for (int n = 2; std::filesystem::exists(p, ec); ++n)
        p = (opts_.screenshot_dir / (stem + "_" + std::to_string(n) + ".png")).make_preferred();
    if (!gs::write_png(p.string(), shown_)) {
        std::fprintf(stderr, "p3fes: screenshot: cannot write %s\n", p.string().c_str());
        return {};
    }
    ++shots_;
    std::printf("p3fes: screenshot %s (%ux%u)\n", p.string().c_str(), shown_.width, shown_.height);
    return p;
}

} // namespace p3fes::app
