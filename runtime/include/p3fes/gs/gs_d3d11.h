// The D3D11 GS back end (docs/ANALYSIS/25_d3d11_gs_backend.md §3): GS local memory as one 4 MiB GPU buffer, the
// GS pixel pipeline in a pixel shader (gs_d3d11_hlsl.h), transfers and CLUT loads as compute shaders, the CRTC merge
// as a compute pass, executed from the op lists a GsOpRecorder (gs_ops.h) records on the EE fiber.
//
//  * GsD3D11Executor: the device-level part (no thread, no window) -- p3fes_gsreplay and the renderer use it.
//  * GsD3D11Renderer: a render thread that owns its D3D11 device and the window's swap chain; the host submits one
//    op list per vblank slice (`submit`, never waits for the GPU: when the thread falls behind, lists are appended
//    to the last queued one) and the thread executes, composes and presents with vsync. `sync_vram` (host side,
//    for snapshots, PNGs and local -> host transfers) waits until everything submitted has run and reads GS memory
//    back. Started without a window it is offscreen: no swap chain, nothing presented (headless runs).
//
// Windows / D3D11 only (library p3fes_gs_d3d11). The game host uses it for windowed play and, opt-in, for headless
// runs in exact mode (`--headless --gs-backend d3d11 --gs-exact`: byte-identical to the software rasteriser, which
// stays the default and the oracle).
#pragma once

#include "p3fes/gs/gs_ops.h"
#include "p3fes/gs/gs_priv.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <d3d11.h>
#include <wrl/client.h>

#include <array>
#include <condition_variable>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace p3fes::gs {

struct GsD3D11Caps {
    std::string adapter;
    std::string driver;  // UMD version a.b.c.d (empty when unknown)
    D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_9_1;
    bool rov = false;          // D3D11_FEATURE_D3D11_OPTIONS2.ROVsSupported
    bool doubles = false;      // D3D11_FEATURE_DOUBLES.DoublePrecisionFloatShaderOps
    bool ext_doubles = false;  // D3D11_FEATURE_D3D11_OPTIONS.ExtendedDoublesShaderInstructions
    std::string summary() const;
};
GsD3D11Caps query_caps(ID3D11Device* dev);
// With a debug device (D3D11_CREATE_DEVICE_DEBUG, the Graphics Tools feature): break into a debugger on errors when
// asked, and print the stored errors/warnings to stderr (returns how many; clears the queue). No-ops otherwise.
void enable_debug_messages(ID3D11Device* dev, bool break_on_error);
u64 drain_debug_messages(ID3D11Device* dev, const char* prefix);

// GPU time of one list by op kind (GsD3D11Executor::execute_profiled; index = GpuOpKind).
struct GpuOpProfile {
    double upload_ms = 0.0, total_ms = 0.0;
    u64 count[kGpuOpKinds] = {};  // ops
    u64 calls[kGpuOpKinds] = {};  // D3D calls (merged draws: one per run)
    double ms[kGpuOpKinds] = {};
};

class GsD3D11Executor {
public:
    GsD3D11Executor();
    ~GsD3D11Executor();
    GsD3D11Executor(const GsD3D11Executor&) = delete;
    GsD3D11Executor& operator=(const GsD3D11Executor&) = delete;

    // Compiles the shaders and creates the GS resources on `dev`/`ctx` (the caller keeps the context single-threaded).
    // `want_rov` uses rasterizer-ordered views when the device has them; `exact` needs doubles (fails otherwise).
    bool init(ID3D11Device* dev, ID3D11DeviceContext* ctx, bool want_rov, bool exact, std::string& error);
    const GsD3D11Caps& caps() const noexcept { return caps_; }
    bool rov() const noexcept { return rov_; }
    bool exact() const noexcept { return exact_; }
    bool native_stage() const noexcept;  // the native renderer's GPU vertex stage compiled (gs_native_hlsl.h)
    const char* ps_target() const noexcept { return ps_target_; }

    // GS local memory and the CLUT buffer to these contents.
    void reset(const u8* vram, const std::array<u16, 512>& clut);
    // Uploads the list's arrays into the next ring slot and issues every op.
    void execute(const OpList& l);
    // execute() between two timestamp queries; waits for the GPU and returns its milliseconds (-1 if unavailable).
    // `issue_ms` (optional): lowered to the CPU time of the execute() call itself when that is smaller.
    double execute_timed(const OpList& l, double* issue_ms = nullptr);
    // execute() with a timestamp after the upload and after every op (diagnostics, p3fes_gsreplay --gpu-profile):
    // GPU milliseconds per op kind. Waits for the GPU; false when the timestamps are unusable.
    bool execute_profiled(const OpList& l, GpuOpProfile& out);
    // Copies GS local memory to `out` (waits for the GPU).
    void readback_vram(std::vector<u8>& out);
    // Copies the CLUT buffer (512 halfwords, GsCore::clut() layout) to `out` (waits for the GPU); false on failure.
    bool readback_clut(std::array<u16, 512>& out);
    // The CRTC picture of `disp` into the executor's frame texture; false when no circuit is enabled. The SRV stays
    // valid until the next compose with another size.
    bool compose(const DisplayRegs& disp, ID3D11ShaderResourceView** srv, u32& width, u32& height);
    // compose() then read the picture back (waits for the GPU).
    bool compose_readback(const DisplayRegs& disp, Frame& out);

    // Extra GS memory banks (frame interpolation, docs/ANALYSIS/32 §7): each a copy of GS local memory + the CLUT
    // buffer on the GPU. `create_banks(n)` makes banks 0..n-1 (false on failure; again with another n: recreated);
    // save_bank: the active memory -> bank b; copy_bank: bank src -> bank dst; swap_bank: exchanges the active
    // memory with bank b (execute / compose / readbacks then work on what was in b; swap again to undo). GPU copies
    // only, never waits.
    bool create_banks(u32 n);
    u32 banks() const noexcept;
    void save_bank(u32 b);
    void copy_bank(u32 dst, u32 src);
    void swap_bank(u32 b);

private:
    struct Impl;
    std::unique_ptr<Impl> d_;
    GsD3D11Caps caps_{};
    bool rov_ = false, exact_ = false;
    const char* ps_target_ = "";
};

// How the render thread presents a submitted list (frame pacing: runtime/app/frame_pacing.h, docs/ANALYSIS/31).
//  * Auto: as before -- present after executing unless more lists are queued, but at least every 100 ms.
//  * Skip: execute only (a vblank slice that showed no new guest frame).
//  * At:   execute, then present at QPC time `at_qpc` (the picture is drawn at once; lists that present nothing
//          execute while it waits; a list that arrives after its time presents at once and counts as late).
//  * Latch: decoupled display rate (Options::display): execute, compose the guest frame and keep it as due at
//          `at_qpc`; the render thread's own display clock presents (the newest due frame, or the DisplayHook's
//          picture between two of them) at the display rate, independent of the 30 fps game rate.
struct PresentPlan {
    enum class Mode : u8 { Auto, Skip, At, Latch };
    Mode mode = Mode::Auto;
    long long at_qpc = 0;
    u64 tag = 0;  // the caller's frame id (the guest flip count), echoed in the present log
    long long submit_qpc = 0;  // when the caller submitted the list (echoed in the present log; 0 = not given)
    u32 merged = 0;  // set by the renderer: how many later lists were appended to this one (it fell behind)
};
// One Present of the window's swap chain (take_present_log). QPC ticks.
struct PresentRecord {
    u64 tag = 0;
    long long target_qpc = 0;   // PresentPlan::At: the requested time; else 0
    long long submit_qpc = 0;   // PresentPlan::submit_qpc of the presenting list
    long long dequeue_qpc = 0;  // the render thread took the presenting list from its queue
    long long ready_qpc = 0;    // the list executed and the picture composed (before waiting for target_qpc)
    long long present_qpc = 0;  // Present() called
    long long return_qpc = 0;   // Present() returned
    u32 present_id = 0;         // IDXGISwapChain::GetLastPresentCount() after the call
    long long sync_qpc = 0;     // when the display showed it (DXGI frame statistics; 0 = unknown)
    u32 sync_refresh = 0;       // the display's refresh counter then (valid when sync_qpc != 0)
    double exec_ms = 0.0;       // render-thread time executing lists since the previous present
    u32 lists = 0;              // lists executed since the previous present
    bool late = false;          // At: the list was ready only after target_qpc
};

// The display rate of the windowed renderer, decoupled from the game's frame rate (frame pacing,
// docs/ANALYSIS/31 §7). Game: one present per guest frame (PresentPlan::At). Refresh: a present every display
// refresh (mid-interval, vsync). Cap: `display_hz` presents a second (no vsync). Uncapped: as fast as the render
// thread goes (no vsync; at most one per millisecond).
enum class DisplayRate : u8 { Game, Refresh, Cap, Uncapped };

// One display tick of a decoupled display rate, for a DisplayHook (render thread). `prev` is the newest guest frame
// due at or before the tick, `next` the one after it (nullptr when none is latched yet); `alpha` in [0, 1] is where
// the tick lies between their due times. The hook draws the picture into `rtv` (the back buffer) inside
// `viewport` and returns true; false = the renderer draws `prev` as is.
struct DisplayTick {
    ID3D11Device* dev = nullptr;
    ID3D11DeviceContext* ctx = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;
    D3D11_VIEWPORT viewport{};
    ID3D11ShaderResourceView* prev = nullptr;
    ID3D11ShaderResourceView* next = nullptr;
    u32 width = 0, height = 0;  // the guest frames' size (both)
    u64 prev_tag = 0, next_tag = 0;
    double alpha = 0.0;
    long long tick_qpc = 0;
};
using DisplayHook = std::function<bool(const DisplayTick&)>;

// Frame interpolation on the render thread (track H, docs/ANALYSIS/32_high_frame_rate.md §7). All calls come from
// the render thread. before_execute: every list, after a reset_memory's reset and before the list executes (the
// interpolator records per guest frame the starting GS memory and the lists). on_reset: GS memory was replaced
// (a machine state was loaded): records are void. draw: one display tick of a decoupled display rate, where the
// DisplayHook would be called (it takes precedence over the hook); true = it drew the picture into tick.rtv, false =
// the renderer draws `prev`.
class IFrameInterpolator {
public:
    virtual ~IFrameInterpolator() = default;
    virtual void before_execute(GsD3D11Executor& ex, const OpList& ops, const DisplayRegs& disp, const PresentPlan& plan) = 0;
    virtual void on_reset() {}
    virtual bool draw(GsD3D11Executor& ex, const DisplayTick& tick) = 0;
};

class GsD3D11Renderer {
public:
    struct Options {
        bool exact = false;   // per-pixel exact attributes (doubles); default interpolated
        bool vsync = true;    // Present(1)
        bool linear = false;  // bilinear scaling of the 640x448 picture
        bool want_rov = true;
        bool debug = false;   // --gpu-debug: D3D11 debug device, its messages to stderr after each frame
        bool debug_break = false;
        // Host-side wait for sync_vram/sync_frame. Windowed: short (the window must keep responding); headless: long
        // (the render thread may be many lists behind an EE that never waits for it).
        double sync_timeout_s = 10.0;
        // Lists queued before a new one is appended to the newest instead (the EE side never waits).
        unsigned max_queued = 3;
        // Tests: the render thread takes this long to finish after stop() (a slow driver; stop() must still join).
        unsigned test_stop_delay_ms = 0;
        // Frame pacing (windowed): the render thread's scheduling (0 = leave it; else a THREAD_PRIORITY_* value),
        // MMCSS "Games" registration, and IDXGIDevice1::SetMaximumFrameLatency (0 = the DXGI default of 3).
        int thread_priority = 0;
        bool mmcss = false;
        unsigned frame_latency = 0;
        bool present_log = false;  // keep PresentRecords for take_present_log (DXGI frame statistics included)
        DisplayRate display = DisplayRate::Game;  // the host then submits new frames as PresentPlan::Latch
        double display_hz = 120.0;                // DisplayRate::Cap
        // Measurement (--zones): GPU time of every executed list from timestamp queries, read back a few lists later
        // without waiting (Stats::gpu_ms_total). Changes nothing that is drawn.
        bool gpu_timing = false;
    };
    struct Stats {
        u64 submitted = 0, merged = 0, executed = 0, presented = 0, skipped_presents = 0;
        u64 timed_presents = 0, late_presents = 0;  // PresentPlan::At presents; those whose list came after the time
        double gpu_ms_last = 0.0;  // render-thread wall time of the last execute + compose (ms)
        double busy_ms_total = 0.0;  // render-thread wall time of every execute + compose/present (ms)
        double gpu_ms_total = 0.0;   // Options::gpu_timing: GPU time between the timestamps around each list (ms)
        u64 gpu_frames = 0;          // ... lists measured (a list whose query slot was still in flight is not)
        u64 thread_cycles = 0;       // render thread CPU cycles (QueryThreadCycleTime), filled by stats()
        double host_wait_ms = 0.0;   // time the calling (game) thread spent waiting for the render thread (wait_pumping)
    };

    GsD3D11Renderer();
    ~GsD3D11Renderer();
    GsD3D11Renderer(const GsD3D11Renderer&) = delete;
    GsD3D11Renderer& operator=(const GsD3D11Renderer&) = delete;

    // Starts the render thread: hardware device, capability checks (feature level 11_0, ROVs; doubles if exact),
    // shaders, swap chain for `window` (none when `window` is nullptr: offscreen, nothing is presented). Blocks until
    // that is done; false + `why` (the thread is gone) on failure.
    bool start(HWND window, const Options& opt, std::string& why);
    void stop();
    bool running() const noexcept { return thread_.joinable(); }
    bool offscreen() const noexcept { return offscreen_; }
    const GsD3D11Caps& caps() const noexcept { return caps_; }
    std::string description() const;
    // The native renderer's GPU vertex stage is available (OpList::nat_* lists can be executed).
    bool native_stage() const noexcept { return native_stage_; }

    // The ops recorded since the previous submit and the display registers for the picture to show after them.
    void submit(OpList&& ops, const DisplayRegs& disp, const PresentPlan& plan = {});
    // Gives `out` the storage of a list the render thread has finished with (cleared, capacity kept), when there is
    // one: the host passes it to the recorder's next take() so recording never reallocates. Never waits.
    void recycle(OpList& out);
    // Moves the presents recorded since the last call into `out` (appended; Options::present_log). Bounded: the
    // oldest are dropped when nobody takes them.
    void take_present_log(std::vector<PresentRecord>& out);
    // Decoupled display rates: the picture of each display tick between two guest frames (track H's interpolated
    // frames). Set before start(); called on the render thread.
    void set_display_hook(DisplayHook hook) { display_hook_ = std::move(hook); }
    // The frame interpolator (track H). Set before start(); the renderer does not own it.
    void set_interpolator(IFrameInterpolator* fi) { interp_ = fi; }
    // Replaces GPU memory and the CLUT buffer with `vram` (kVramBytes) / `clut` before anything submitted later
    // (a machine state was loaded: runtime/STATE.md). Copies the data; never waits.
    void reset_memory(const u8* vram, const std::array<u16, 512>& clut);
    // Client area size and the destination rectangle of the picture in it (thread-safe; WM_SIZE / layout).
    void set_view(int client_w, int client_h, int x, int y, int w, int h);
    // Waits until every submitted list has executed, then copies GS local memory (and the CLUT buffer when `clut`
    // is given). Host thread; false on timeout or a lost device.
    bool sync_vram(std::vector<u8>& out, std::array<u16, 512>* clut = nullptr);
    // As sync_vram, then the composed picture of the last submitted display registers.
    bool sync_frame(Frame& out);
    Stats stats() const;

private:
    struct Frame_ {
        OpList ops;
        DisplayRegs disp{};
        PresentPlan plan{};
        std::shared_ptr<std::vector<u8>> reset_vram;  // reset_memory(): GPU memory + CLUT replaced before `ops`
        std::array<u16, 512> reset_clut{};
    };
    void run(HWND window, Options opt);
    bool init_thread(HWND window, const Options& opt, std::string& why);
    bool present_frame(const DisplayRegs& disp, PresentRecord* rec = nullptr);
    // present_frame in two steps: compose `disp` and draw it into the back buffer (ready_qpc), then wait for the
    // record's target_qpc (when set) and Present. Lists that present nothing may execute in between.
    bool prepare_present(const DisplayRegs& disp, PresentRecord* rec);
    bool commit_present(PresentRecord* rec);
    // Decoupled display: draw `srv` (w x h) into the back buffer in the letterbox rectangle; latch a composed frame.
    void draw_picture(ID3D11ShaderResourceView* srv, u32 w, u32 h, const DisplayTick* tick_for_hook);
    bool latch_frame(const DisplayRegs& disp, const PresentPlan& plan, long long submit_qpc, long long dequeue_qpc);
    D3D11_VIEWPORT picture_viewport();
    DisplayHook display_hook_;
    IFrameInterpolator* interp_ = nullptr;
    int test_fail_ = 0;  // P3FES_D3D11_TEST_FAIL (fallback tests): 1 start, 2 present
    bool resize_if_needed();

    std::thread thread_;
    mutable std::mutex m_;
    std::condition_variable cv_, done_cv_;
    std::deque<Frame_> queue_;
    std::vector<OpList> spare_;  // executed lists (recycle)
    bool stop_ = false, started_ = false, start_ok_ = false, exited_ = false;
    // Waits for `pred` (under `lk`) while dispatching the calling thread's window messages; false on timeout.
    template <class Pred>
    bool wait_pumping(std::unique_lock<std::mutex>& lk, std::condition_variable& cv, Pred pred, double timeout_s);
    std::string start_why_;
    int sync_requests_ = 0;        // host waits for a readback
    int sync_kind_ = 0;            // 1 vram, 2 frame
    bool sync_done_ = false;
    bool sync_ok_ = false;         // the readback succeeded (device not lost)
    std::vector<u8> sync_vram_;
    std::array<u16, 512> sync_clut_{};
    bool offscreen_ = false;
    double sync_timeout_s_ = 10.0;
    unsigned max_queued_ = 3;
    Frame sync_frame_;
    std::deque<PresentRecord> present_log_;      // finished records for take_present_log (under m_)
    int client_w_ = 0, client_h_ = 0, vx_ = 0, vy_ = 0, vw_ = 0, vh_ = 0;
    Stats st_{};
    GsD3D11Caps caps_{};
    std::string desc_;
    bool native_stage_ = false;

    // Render-thread objects.
    struct Gpu;
    std::unique_ptr<Gpu> g_;
};

} // namespace p3fes::gs
