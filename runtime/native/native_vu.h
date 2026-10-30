// The native renderer's VU1 hook (docs/ANALYSIS/31_native_renderer.md §3): in windowed play with
// `--renderer native`, the MSCAL/MSCNT runs of RenderWare's g3 programs (vu1_prog_042_g3_generic,
// vu1_prog_064_g3_skin, vu1_prog_063_g3_skin) are not interpreted: the batch is computed by the semantic model
// (g3_model.h) and its triangles go straight into the GPU op list (GsOpRecorder::on_native_triangles), skipping the
// VU1 program, the PATH1 packet, the GIF and the GS vertex queue. Everything the EE can observe is unchanged: VIF1 has
// already done its register update and the UNPACKs, the DMAC timing does not depend on VU1 work, and the GS state the
// packet would have set (PRIM) is written to the core. Anything else falls back to the exact run of that batch.
//
// Two stages (§3.3): `run` is the VU1 stage (reads VU1 memory, runs the model, decides); the GS-side work (the PRIM
// write, the GsVertex values that depend on GS registers, the recorder call) is a separate step `apply_gs` that runs at
// once, or, with an emitter installed (a pipelined host), at that point of the GS command stream.
//
// Modes: native (default), diff (`--renderer native-diff`: every batch runs exactly, the model's packet is compared
// with the one the VU1 kicks and the VU state the exact run leaves with what the native path leaves), verify
// (`--renderer native-verify`: native, but every K-th batch runs exactly on the native path's own VU state and its
// packet is compared with the model: measures that skipped runs leave nothing a later exact run depends on).
#pragma once

#include "g3_model.h"

#include "p3fes/gs/gs_ops.h"
#include "p3fes/gs/vif1.h"
#include "p3fes/vu1/vu1_interp.h"

#include <array>
#include <cstdio>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace p3fes::gs {
class GsCore;
}

namespace p3fes::native {

struct NativeStats {
    u64 runs = 0;          // runs seen with a g3 program resident
    u64 native = 0;        // handled natively
    u64 inits = 0;         // MSCAL 0 inits emulated
    u64 fb_gif_busy = 0;   // fell back: the GIF was not idle (a PATH1 packet would have queued)
    u64 fb_model = 0;      // fell back: the model does not cover the batch (clipper, odd tag, ...)
    u64 fb_entry = 0;      // fell back: an entry point other than MSCAL 0 / the MSCNT resume point
    u64 tris = 0, culled = 0, verts = 0;
    u64 variant[static_cast<int>(G3Variant::Count) + 1] = {};
    u64 identifies = 0;
    u64 fb_clipped = 0;               // of fb_model: full-clipper batches whose triangles needed clipping
    u64 model_ns = 0, submit_ns = 0;  // wall time in the model / in building and recording the triangles
    u64 captured = 0;
    u64 clipped_native = 0;           // full-clipper batches clipped in the model
    u64 gpu_batches = 0, gpu_words = 0;  // batches sent to the GPU vertex stage, record words
    // diff / verify modes
    u64 diff_batches = 0, diff_bad = 0, diff_adc = 0, diff_kick_count = 0, diff_verts = 0;
    // diff mode, VU state after the exact run vs what the native path leaves: runs compared, runs with any
    // difference, differences per VF / VI register, in the other registers, per 16-qword block of data memory
    u64 st_runs = 0, st_runs_diff = 0;
    u64 st_vf[32] = {}, st_vi[16] = {}, st_misc = 0, st_data[64] = {};
};

class NativeG3 final : public gs::IVuRunHook, public vu1::IGifSink {
public:
    // `gif_sink` = what the VU1 kicks into on the exact path (GsSystem); diff/verify modes tee in front of it.
    NativeG3(gs::GsCore& core, gs::GsOpRecorder& rec, vu1::IGifSink& gif_sink);
    bool run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    void after_exact(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    const NativeStats& stats() const noexcept { return st_; }
    // Which programs to take natively (tests / diagnosis): bit 0 generic, bit 1 skin, bit 2 parallel skin.
    void set_mask(u32 m) noexcept { mask_ = m; }
    // Diff mode: never handle a run, compare instead (install `this` as the VU1's sink: GameHost does).
    void set_diff(bool on, std::FILE* log) noexcept {
        diff_ = on;
        log_ = log;
    }
    // Verify mode: native, every `every`-th batch exact + compared (install `this` as the VU1's sink).
    void set_verify(u32 every, std::FILE* log) noexcept {
        verify_every_ = every;
        log_ = log;
    }
    bool diff() const noexcept { return diff_; }
    bool verify() const noexcept { return verify_every_ != 0; }
    // Save the input of every `every`-th g3 run (save_run_input format, p3fes_native_check reads it), at most `max`.
    void set_capture(std::string dir, u32 every, u64 max) {
        capture_dir_ = std::move(dir);
        capture_every_ = every ? every : 1;
        capture_max_ = max;
    }
    void kick(std::span<const u128> q) override;  // diff / verify mode tee
    // The renderer evaluates attributes per pixel from GS vertex records (exact mode): write them for native draws.
    void set_prim_records(bool on) noexcept { prim_records_ = on; }
    // A pipelined host: GS-side work goes through `emit` (it runs the closure at this point of the GS stream).
    void set_emitter(std::function<void(std::function<void()>)> emit) { emit_ = std::move(emit); }
    // The renderer can run the GPU vertex stage (gs_native_hlsl.h): batches other than the full clipper's are sent
    // as records and their vertices are computed on the GPU (the CPU model still decides the clipper batches).
    void set_gpu(bool on) noexcept { gpu_ = on; }
    bool gpu() const noexcept { return gpu_; }

    // What the GS stage needs from one native batch (self-contained: no pointer into VU1 memory).
    struct GsWork {
        bool write_prim = false;
        u32 prim = 0;
        bool fogged = false;
        u32 type = 4;  // GS primitive type: 3 triangle list, 4 strip
        std::vector<G3OutVertex> v;
        std::vector<u16> idx;  // triangle index triples (ADC-culled triangles left out)
        // Frame interpolation (docs/ANALYSIS/32 §3): the batch's identity (key: a hash of its input vertex block, N and
        // the program; stable per geometry cluster across frames) and transform rows (VU1 0x3F0-0x3F3).
        gs::NativeBatchTag tag;
        bool has_tag = false;
        // GPU vertex stage: the batch record (gs_native_hlsl.h) and its triangle slots, instead of v / idx
        bool gpu = false;
        std::vector<u32> rec;
        std::vector<u32> pal;  // the bone palette rows the record indexes
        u32 slots = 0;
    };
    // The batch identity (track H's key, doc 32 §3): hash of the first 8 input vertices + the last + N + program,
    // the object rows. `top` = the batch's TOP, `n` = its vertex count.
    static gs::NativeBatchTag batch_tag(G3Prog p, const vu1::VU1State& s, u32 top, u32 n);

private:
    G3Prog identify(const vu1::MicroMemory& m);
    bool prepare(const G3Batch& b, GsWork& w);
    bool prepare_gpu(G3Prog p, const vu1::VU1State& s, GsWork& w);
    void apply_gs(const GsWork& w);
    void diff_close();
    void compare_packet(std::span<const u128> q);
    void fallback_begin(const gs::NativeBatchTag& tag);

    gs::GsCore& core_;
    gs::GsOpRecorder& rec_;
    vu1::IGifSink& sink_;
    NativeStats st_{};
    u64 gen_ = 0;
    G3Prog prog_ = G3Prog::None;
    u32 mask_ = 7;
    G3Batch batch_;  // clip_in_model set by the constructor
    GsWork work_;
    std::vector<gs::GsVertex> verts_;
    bool prim_records_ = false;
    bool gpu_ = false;
    std::function<void(std::function<void()>)> emit_;
    bool diff_ = false;
    u32 verify_every_ = 0;
    u64 verify_seq_ = 0;
    std::FILE* log_ = nullptr;
    bool pending_ = false;  // diff/verify: a modelled batch waits for its kick
    u32 kicks_ = 0;
    u64 logged_ = 0;
    std::unique_ptr<vu1::VU1State> pre_;  // diff mode: the state the native path would leave
    bool pre_valid_ = false;
    bool fb_open_ = false;  // a declined g3 batch is bracketed in the recorder until after_exact
    std::string capture_dir_;
    u32 capture_every_ = 1;
    u64 capture_max_ = 0, capture_seq_ = 0;
};

} // namespace p3fes::native
