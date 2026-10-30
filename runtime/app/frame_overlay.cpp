#include "frame_overlay.h"

#include <algorithm>
#include <cstdio>

namespace p3fes::app {

namespace {

constexpr wchar_t kClass[] = L"P3FES_FrameOverlay";
constexpr int kW = 330, kH = 132;
constexpr int kGraphTop = 62, kGraphH = 64;
constexpr double kGraphMaxMs = 66.7;  // the graph's top

} // namespace

FrameOverlay::~FrameOverlay() { destroy(); }

bool FrameOverlay::create(HWND owner) {
    destroy();
    owner_ = owner;
    HINSTANCE inst = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof wc;
    wc.lpfnWndProc = proc;
    wc.hInstance = inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kClass;
    registered_ = RegisterClassExW(&wc) != 0 || GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
    if (!registered_) return false;
    // Owned popup (stays above the game window), layered (translucent), transparent to the mouse, never activated.
    hwnd_ = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kClass, L"p3fes frame time",
                            WS_POPUP, 0, 0, kW, kH, owner, nullptr, inst, this);
    if (!hwnd_) return false;
    SetLayeredWindowAttributes(hwnd_, 0, 208, LWA_ALPHA);
    font_ = CreateFontW(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        NONANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, L"Consolas");
    return true;
}

void FrameOverlay::destroy() {
    if (hwnd_ && IsWindow(hwnd_)) DestroyWindow(hwnd_);
    hwnd_ = nullptr;
    if (font_) DeleteObject(font_);
    font_ = nullptr;
    visible_ = false;
}

void FrameOverlay::set_visible(bool on) {
    visible_ = on;
    if (!hwnd_) return;
    if (on) {
        follow();
        ShowWindow(hwnd_, SW_SHOWNOACTIVATE);
        InvalidateRect(hwnd_, nullptr, FALSE);
    } else {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

void FrameOverlay::follow() {
    if (!hwnd_ || !owner_) return;
    POINT p{8, 8};
    ClientToScreen(owner_, &p);
    RECT r{};
    GetWindowRect(hwnd_, &r);
    if (r.left != p.x || r.top != p.y) SetWindowPos(hwnd_, nullptr, p.x, p.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    // Hidden while the game window is minimised.
    const bool show = visible_ && !IsIconic(owner_);
    if (show != (IsWindowVisible(hwnd_) != FALSE)) ShowWindow(hwnd_, show ? SW_SHOWNOACTIVATE : SW_HIDE);
}

void FrameOverlay::update(const FrameTelemetry::Live& l) {
    if (!hwnd_ || !visible_) return;
    live_ = l;
    follow();
    InvalidateRect(hwnd_, nullptr, FALSE);
    UpdateWindow(hwnd_);
}

LRESULT CALLBACK FrameOverlay::proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_NCCREATE) {
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCTW*>(lparam)->lpCreateParams));
        return DefWindowProcW(hwnd, msg, wparam, lparam);
    }
    auto* self = reinterpret_cast<FrameOverlay*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (msg) {
    case WM_NCHITTEST:
        return HTTRANSPARENT;
    case WM_MOUSEACTIVATE:
        return MA_NOACTIVATE;
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        if (self) {
            // Double-buffered: draw into a memory bitmap, then one blit.
            HDC mem = CreateCompatibleDC(dc);
            HBITMAP bmp = CreateCompatibleBitmap(dc, kW, kH);
            HGDIOBJ old = SelectObject(mem, bmp);
            self->paint(mem);
            BitBlt(dc, 0, 0, kW, kH, mem, 0, 0, SRCCOPY);
            SelectObject(mem, old);
            DeleteObject(bmp);
            DeleteDC(mem);
        }
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_NCDESTROY:
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
        break;
    default:
        break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

void FrameOverlay::paint(HDC dc) {
    const RECT all{0, 0, kW, kH};
    HBRUSH bg = CreateSolidBrush(RGB(12, 12, 16));
    FillRect(dc, &all, bg);
    DeleteObject(bg);
    HGDIOBJ oldf = SelectObject(dc, font_ ? static_cast<HGDIOBJ>(font_) : GetStockObject(ANSI_FIXED_FONT));
    SetBkMode(dc, TRANSPARENT);
    const FrameTelemetry::Live& l = live_;
    const bool good = l.p99 > 0.0 && l.p99 <= 34.5 && l.fps >= 29.5 && l.work_p95 <= 15.0;
    wchar_t b[160];
    SetTextColor(dc, good ? RGB(120, 230, 120) : RGB(255, 200, 80));
    swprintf_s(b, L"game %4.1f  display %5.1f fps  max %5.1f", l.fps, l.display_fps, l.max);
    TextOutW(dc, 6, 3, b, static_cast<int>(wcslen(b)));
    SetTextColor(dc, RGB(220, 220, 220));
    swprintf_s(b, L"frame p50 %4.1f p99 %5.1f | work p50 %4.1f p95 %5.1f", l.p50, l.p99, l.work_p50, l.work_p95);
    TextOutW(dc, 6, 17, b, static_cast<int>(wcslen(b)));
    swprintf_s(b, L"hitch %llu late %llu audio %2.0fms x%.3f u%llu", static_cast<unsigned long long>(l.hitches),
               static_cast<unsigned long long>(l.late), l.audio_ms, l.ratio, static_cast<unsigned long long>(l.underruns));
    TextOutW(dc, 6, 31, b, static_cast<int>(wcslen(b)));
    SetTextColor(dc, RGB(150, 150, 170));
    swprintf_s(b, L"%hs  (F3)", l.pacing.c_str());
    TextOutW(dc, 6, 45, b, static_cast<int>(wcslen(b)));
    // Bar graph: one column per frame interval (newest right); host work as a dim bar behind it.
    const int x0 = 6, w = kW - 12, ybot = kGraphTop + kGraphH;
    auto y_of = [&](double ms) { return ybot - static_cast<int>(std::min(ms, kGraphMaxMs) / kGraphMaxMs * kGraphH); };
    HBRUSH frame = CreateSolidBrush(RGB(30, 30, 38));
    const RECT g{x0, kGraphTop, x0 + w, ybot};
    FillRect(dc, &g, frame);
    DeleteObject(frame);
    const std::size_t n = l.intervals.size();
    const int col = 1;  // 240 columns of ~1.5 px in 368 px
    HBRUSH ok = CreateSolidBrush(RGB(80, 200, 90)), bad = CreateSolidBrush(RGB(235, 70, 60)), dim = CreateSolidBrush(RGB(70, 70, 110));
    for (std::size_t i = 0; i < n; ++i) {
        const int x = x0 + w - static_cast<int>((n - i) * w / 240);
        const int x1 = std::max(x + col, x0 + w - static_cast<int>((n - i - 1) * w / 240));
        const RECT wr{x, y_of(l.work[i]), x1, ybot};
        FillRect(dc, &wr, dim);
        const double ms = l.intervals[i];
        const RECT r{x, y_of(ms), x1, std::min(ybot, y_of(ms) + 2)};
        FillRect(dc, &r, ms > 34.5 ? bad : ok);
    }
    DeleteObject(ok);
    DeleteObject(bad);
    DeleteObject(dim);
    // 33.4 ms and 50 ms lines.
    HPEN green = CreatePen(PS_SOLID, 1, RGB(60, 160, 70)), red = CreatePen(PS_DOT, 1, RGB(160, 60, 60));
    HGDIOBJ oldp = SelectObject(dc, green);
    MoveToEx(dc, x0, y_of(33.37), nullptr);
    LineTo(dc, x0 + w, y_of(33.37));
    SelectObject(dc, red);
    MoveToEx(dc, x0, y_of(50.05), nullptr);
    LineTo(dc, x0 + w, y_of(50.05));
    // The 15 ms host-work budget (the 60 fps target) against the dim work bars.
    HPEN amber = CreatePen(PS_DOT, 1, RGB(200, 170, 60));
    SelectObject(dc, amber);
    MoveToEx(dc, x0, y_of(15.0), nullptr);
    LineTo(dc, x0 + w, y_of(15.0));
    SelectObject(dc, oldp);
    DeleteObject(green);
    DeleteObject(red);
    DeleteObject(amber);
    SelectObject(dc, oldf);
}

} // namespace p3fes::app
