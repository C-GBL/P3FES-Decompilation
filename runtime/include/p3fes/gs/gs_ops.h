// The GS front end's hand-off to a GPU back end (docs/ANALYSIS/25_d3d11_gs_backend.md §3): `GsOpRecorder` is an
// IGsDrawObserver that turns what GsCore does with software rasterisation off into an `OpList` -- draw batches
// (triangles in GS window coordinates + one constant block per state run + per-triangle GS vertex records for exact
// attribute evaluation), transfer scatters (32-bit words with the masks of the bits uploaded), CLUT loads and local
// copies -- in the order the GS performed them. A list is self-contained (no pointers into GsCore), so it can be
// moved to a render thread; lists append (`OpList::append`) when a renderer falls behind. Pure C++; the D3D11
// executor is runtime/gs/d3d11 (p3fes_gs_d3d11). The layouts below are shared with the HLSL in gs_d3d11_hlsl.h.
#pragma once

#include "p3fes/gs/gs_core.h"

#include <cstddef>
#include <functional>
#include <vector>

namespace p3fes::gs {

// One D3D vertex, 40 bytes. The vertex shader widens the integer fields to float (all exact: below 2^24), so the
// interpolated attributes equal those of the earlier all-float layout.
struct GpuVertex {
    s32 x, y;     // window coordinates, 12.4 (XYOFFSET subtracted)
    float z;
    u32 rgba;     // r | g << 8 | b << 16 | a << 24 (flat shading: the kicking vertex's colour on every vertex)
    float s, t, q;
    u32 uv;       // u | v << 16, 1/16 texel (14 bits each)
    u32 f;        // fog coefficient
    u32 cbi;      // the primitive's GpuDrawCB (OpList::cbs index): merged draws carry several states
};
static_assert(sizeof(GpuVertex) == 40);
inline constexpr u32 kClutLive = 0xFFFFFFFFu;
// A CLUT version is 512 u32 (the GS CLUT buffer's halfwords in GsCore::clut() order); kClutInherit = the entry is the
// GPU CLUT buffer's as it was when the list started (no load in this list wrote that slot).
inline constexpr u32 kClutInherit = 0x80000000u;

// One D3D triangle's GS vertices (a sprite's two triangles carry the same record). 128 bytes.
struct GpuPrimRec {
    s32 xy01[4];  // triangle: X0 Y0 X1 Y1 (kick order); sprite: x0 y0 x1 y1 after the min/max swap
    s32 xy2k[4];  // X2 Y2 kind (0 triangle, 1 sprite) 0
    u32 rgba[4];  // rgba8 per vertex (sprite: [1] = the second vertex)
    u32 zf[4];    // Z0 Z1 Z2, fog f0 | f1 << 8 | f2 << 16
    u32 uv[4];    // u | v << 16 per vertex (sprite: [0] = u0 v0, [1] = u1 v1)
    float s[4], t[4], q[4];
};
static_assert(sizeof(GpuPrimRec) == 128);

// The decoded draw state (cbuffer Draw in the HLSL; 16-byte rows).
struct GpuDrawCB {
    u32 tme, fge, abe, fst;
    u32 iip, sprite, fbp, fbw;
    u32 fpsm, fbmsk, zbp, zpsm;
    u32 zmsk, ate, atst, aref;
    u32 afail, date, datm, ztst;
    u32 ba, bb, bc, bd;
    u32 fix, pabe, fba, colclamp;
    u32 dthe, scanmsk, fogcol, zmax;
    s32 dimx[4][4];
    u32 tpsm, tcc, tfx, cpsm;
    u32 csa, wms, wmt, minu;
    u32 maxu, minv, maxv, ta0;
    u32 ta1, aem, mmag_linear, mmin;
    u32 mxl, lcm, lshift, prim_base;
    s32 k16, pad1, pad2, pad3;
    u32 lv[7][4];
    s32 sc[4];     // scissor left, top, right, bottom (exclusive): tested in the shader (merged draws)
    u32 clut_ver;  // CLUT version (OpList::clut_tab index) the draw reads, or kClutLive: the GPU's CLUT buffer
    u32 pad4, pad5, pad6;
    u32 tail[20];  // to 512 bytes: the executor binds 128 blocks from a 256-byte-aligned offset of one buffer
};
static_assert(sizeof(GpuDrawCB) == 512);

struct GpuClutCB {
    u32 cbp, cpsm, csm2, csa, eight, cbw, cou, cov;
};

struct GpuRect {
    s32 left = 0, top = 0, right = 0, bottom = 0;  // right/bottom exclusive
};

// ClutResolve: the GPU CLUT buffer := CLUT version cb (inherited slots keep their value); see GsOpRecorder.
enum class GpuOpKind : u8 { Draw, Scatter, Pages, Clut, Copy, ClutResolve };
inline constexpr unsigned kGpuOpKinds = 6;
// A Pages op carries whole 8 KiB pages written by full-word (32-bit) transfers: per page a record of
// kPageRecordWords u32 = page index, 64 u32 of "word written" bits, the page's 2048 words from CPU memory.
inline constexpr u32 kPageRecordWords = 1 + 64 + 2048;
struct GpuOp {
    GpuOpKind kind = GpuOpKind::Draw;
    // Draw: may execute in one D3D draw call with the Draw op before it (same frame / Z buffers, no texture reads of
    // pages the other writes; GsOpRecorder::close_draw). Only with ROVs (pixel order inside a draw call).
    u8 merge = 0;
    u32 first = 0, count = 0;  // Draw: vertices; Scatter: word triples; Pages: page records
    u32 prim_base = 0;         // Draw: first GpuPrimRec
    u32 cb = 0;                // Draw: GpuDrawCB index; Clut: GpuClutCB index; ClutResolve: CLUT version
    GpuRect sc{};              // Draw: scissor
    u64 b = 0, p = 0, rg = 0;  // Copy: BITBLTBUF, TRXPOS, TRXREG
    u8 native = 0;             // Draw: the vertices are the GPU vertex stage's output (first/count in that buffer)
};

// Frame interpolation (track H, docs/ANALYSIS/32_high_frame_rate.md §3): what the native renderer knows about one
// batch it drew, so that a later frame's batch can be matched with it and its vertices blended.
//  * key: identity of the batch's geometry, stable across frames (the native renderer hashes the batch's INPUT
//    vertex block -- object-space positions, uv, prelit colours, normals / weights -- with N and the program);
//  * rows: the batch's transform rows (VU1 0x3F0-0x3F3, camera x object): instance disambiguation, diagnostics.
struct NativeBatchTag {
    u64 key = 0;
    float rows[16] = {};
    u8 prog = 0;
};
// One native batch in an OpList (OpList::nat_batches). Its triangles are verts[dfirst .. dfirst + dcount) (3 per
// triangle, contiguous, possibly spread over several Draw ops); nat_src[sfirst + i] is the source vertex of
// verts[dfirst + i]; nat_verts[vfirst .. vfirst + nv) are all `nv` source vertices converted as the recorder converts
// them (GpuVertex), including those that only belong to culled triangles (a later frame may draw them).
struct NativeBatchRec {
    u64 key = 0;
    float rows[16] = {};
    u32 nv = 0, vfirst = 0;
    u32 dfirst = 0, dcount = 0;
    u32 sfirst = 0;
    u8 prog = 0;
    u8 flat = 0;  // !IIP: every triangle takes its third (kicking) vertex's colour
    u8 pad[2] = {};
};

struct OpList {
    std::vector<GpuOp> ops;
    std::vector<GpuVertex> verts;
    std::vector<GpuPrimRec> prims;
    std::vector<GpuDrawCB> cbs;
    std::vector<GpuClutCB> cluts;
    std::vector<u32> words;  // (word index, mask, value) triples
    std::vector<u32> pages;  // page records (kPageRecordWords each)
    // The native renderer's GPU vertex stage (gs_native_hlsl.h): batch records + inputs, the batch table
    // {first slot, record word, slots, 0}, and the triangle slots (3 output vertices each) they produce.
    std::vector<u32> nat_in;
    std::vector<u32> nat_tab;
    u32 nat_slots = 0;
    // Frame interpolation side table (empty unless GsOpRecorder::set_native_side_table is on). Not read by the
    // executor: executing a list does not depend on it.
    std::vector<NativeBatchRec> nat_batches;
    std::vector<GpuVertex> nat_verts;
    std::vector<u16> nat_src;
    std::vector<u32> clut_tab;  // CLUT versions, 512 u32 each (GpuDrawCB::clut_ver)
    bool empty() const noexcept { return ops.empty(); }
    void clear();
    // Appends `o` after this list's ops (indices rebased): executing the result = executing both in order.
    void append(const OpList& o);
};

struct GpuRecorderStats {
    u64 prims = 0, tris = 0, sprites = 0, unsupported = 0, draws = 0, state_breaks = 0, overlap_breaks = 0;
    u64 clut_loads = 0, scatter_words = 0, scatters = 0, local_copies = 0, local_reads = 0, frames = 0;
    u64 page_words = 0, pages = 0;  // full-word transfer words / page records
    u64 clut_versions = 0;          // CLUT loads resolved on the CPU into a version (clut_tab), not loaded on the GPU
    u64 clut_gpu_loads = 0;         // CLUT loads whose source may hold draw output: loaded on the GPU (Clut op)
    u64 merged_draws = 0;           // Draw ops that share a D3D draw call with the one before (GpuOp::merge)
};

// Why the recorder calls its sync hook (GsOpRecorder::sync_hook).
enum class GpuSyncReason : u8 {
    LocalRead,    // a local -> host transfer starts: GsCore will serve it from its CPU memory
    Unsupported,  // a primitive the GPU path cannot draw (points, lines; none in this game, docs/ANALYSIS/25 §1)
};

class GsOpRecorder final : public IGsDrawObserver {
public:
    // `core` is the GsCore being observed: transfer values are read from its (CPU) local memory when a scatter is
    // closed. `split_overlaps`: no two primitives of a draw may touch the same 8x8 tile (back ends without ROVs).
    // `prim_records`: one GpuPrimRec per D3D triangle (`OpList::prims`), which only the exact pixel shader reads;
    // the interpolated mode (windowed play) passes false and the list carries vertices only.
    GsOpRecorder(const GsCore& core, bool split_overlaps, bool prim_records = true);
    // Called on the EE fiber where the CPU copy of local memory is about to matter (above). The host takes the
    // recorded ops (`take` is allowed inside the hook), lets the GPU execute them and copies GPU memory back into the
    // core; for Unsupported it may also hand rasterisation back to the core (GsCore::set_software_raster(true) from
    // inside the hook: the core then draws the primitive itself). Empty = the event is only counted.
    std::function<void(GpuSyncReason)> sync_hook;
    // Closes the open draw and the pending transfer words.
    void finish();
    // finish() and move the recorded ops out; the recorder continues in `out`'s previous storage (cleared), so a host
    // that hands back a spent list (GsD3D11Renderer::recycle) records without reallocating.
    void take(OpList& out);
    OpList& list() noexcept { return l_; }
    const GpuRecorderStats& stats() const noexcept { return st_; }
    // Frame interpolation (play mode with a display rate above the game's): record OpList::nat_* for native batches
    // that come with a NativeBatchTag. Off by default (headless runs and the gates never turn it on).
    void set_native_side_table(bool on) noexcept { side_table_ = on; }
    bool native_side_table() const noexcept { return side_table_; }
    // Appends one native batch's side record: `all` = its nv converted source vertices, `src` = the source vertex
    // of each of the `dcount` vertices it has just appended to verts (from verts.size() - dcount on). No-op when the
    // side table is off.
    void note_native_batch(const NativeBatchTag& tag, const GpuVertex* all, u32 nv, const u16* src, u32 dcount, bool flat);

    void on_draw(const GsRegs& r, const GsVertex* v, u32 count, u64 pixels, u64 ns) override;
    // The native renderer (runtime/native, play mode): `nv` vertices and `ntri` triangles given as index triples in
    // kick order (the third is the kicking vertex: flat colour), drawn with the state `r` exactly as `ntri` on_draw
    // calls of triangle primitives would record them, but with the state decoded and each vertex converted once.
    // `prim_records`: also write the per-triangle GS vertex records (only the exact pixel shader reads them).
    // `tag` (frame interpolation, docs/ANALYSIS/32): with the side table on, the batch's side record (all `nv`
    // converted vertices, the source vertex of each emitted one) goes into OpList::nat_*.
    void on_native_triangles(const GsRegs& r, const GsVertex* v, u32 nv, const u16* idx, u32 ntri, bool prim_records,
                             const NativeBatchTag* tag = nullptr);
    // The native renderer's GPU path: one batch record (gs_native_hlsl.h layout, `words` a multiple of 4) whose
    // `slots` triangles the GPU vertex stage computes; drawn with the state `r` (same op / state-break rules).
    // The record's ofx / ofy / UV / FOG / draw-state words are filled here from `r`. The triangles' positions are
    // not known here, so the draw counts as writing every row of its scissor (merge and CLUT-source checks).
    // `pal` / `palwords`: the skin palette rows (VU1 0x2B8..) the record indexes; equal to the previous batch's, the
    // stored copy is shared (the record's word 10 = palette offset in qwords relative to the record).
    void on_native_gpu_batch(const GsRegs& r, const u32* words, u32 nwords, u32 slots, const NativeBatchTag* tag = nullptr,
                             const u32* pal = nullptr, u32 palwords = 0);
    // A batch the native renderer recognised but left to the exact VU1 run: the primitives recorded between begin and
    // end are that batch (same tag as it would have had natively). Bookkeeping only; nothing is drawn differently.
    void on_native_fallback_begin(const NativeBatchTag& tag);
    void on_native_fallback_end();
    u64 native_fallbacks() const noexcept { return native_fallbacks_; }
    void on_clut_load(u64 tex0, u64 texclut) override;
    void on_transfer_span(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 n) override;
    void on_local_copy(u64 bitbltbuf, u64 trxpos, u64 trxreg) override;
    void on_local_read(u64 bitbltbuf, u64 trxpos, u64 trxreg) override;

private:
    void open_draw(const GpuDrawCB& cb, const GpuRect& sc);
    void close_draw();
    void close_writes();
    void refresh_state(const GsRegs& r, u64 gen);
    void mark_drawn();
    bool clut_clean(const GpuClutCB& c);
    void capture_clut();
    void end_list();
    void set_clut_version(u32 v);
    void decide_merge();
    // 512 pages of 8 KiB (GS local memory), as a set.
    struct PageSet {
        u64 b[8] = {};
        void add(u32 p0, u32 p1);  // [p0, p1) modulo 512; 512 or more: all
        bool hits(const PageSet& o) const noexcept {
            u64 x = 0;
            for (int i = 0; i < 8; ++i) x |= b[i] & o.b[i];
            return x != 0;
        }
        void join(const PageSet& o) noexcept {
            for (int i = 0; i < 8; ++i) b[i] |= o.b[i];
        }
    };
    static void texture_pages(const GpuDrawCB& c, PageSet& out);
    static void target_pages(const GpuDrawCB& c, s32 y0, s32 y1, PageSet& out);

    const GsCore& core_;
    // CLUT loads (docs/ANALYSIS/25 "Fast front end"). GsCore loads the CLUT buffer from its CPU memory, which holds
    // every upload but no draw output. When none of the CLUT's source words can hold draw output (their page was
    // never drawn, or the words were uploaded after the page's last draw), the CPU result is what the GPU would load:
    // the recorder captures it as a CLUT version (OpList::clut_tab) that the following primitives read, instead of a
    // GPU load between draws (which serialises the GPU and splits the draw). A load that is not clean is a GPU load
    // (Clut op), preceded by a ClutResolve that brings the GPU CLUT buffer up to the current version; later versions
    // inherit from the buffer as that load leaves it. A list that ends with a version ends with a ClutResolve too.
    bool clut_cpu_ = true;      // CPU-resolved CLUT loads allowed (P3FES_GS_GPU_CLUT=1: never)
    bool clut_pending_ = false; // a CPU-resolved load happened; its version is captured at the next primitive
    u32 cur_clut_ = kClutLive;  // the version the next primitives read
    u64 list_slots_[8] = {};    // CLUT slots written by this list's loads
    std::vector<u32> drawn_gen_;   // per 8 KiB page: seq_ when a draw last (possibly) wrote it, 0 = never
    std::vector<u32> upload_gen_;  // per word: seq_ of the last full-word upload
    u32 seq_ = 0;
    bool dbox_ = false;            // the open draw's pixel rows since the last mark_drawn (frame / Z rows it may write)
    s32 dby0_ = 0, dby1_ = 0;
    s32 wy0_ = 0, wy1_ = 0;        // the open draw's pixel rows, all of them (decide_merge)
    PageSet run_w_, run_r_;        // pages the current run of merged draws writes / fetches textures from
    bool run_open_ = false;
    struct ClutWords {
        u64 key;
        std::vector<u32> words;
    };
    std::vector<ClutWords> clut_words_;  // source words per CLUT location (a few distinct ones per scene)
    struct RecentClut {
        u64 hash = 0;
        u32 ver = ~0u;
    };
    RecentClut recent_[8];  // the last versions of this list (a palette loaded again reuses its version)
    u32 recent_next_ = 0;
    bool split_;
    bool records_;
    // The draw state decoded at GsCore::state_generation() == gen_ (refresh_state): what on_draw needs per primitive.
    u64 gen_ = 0;
    u32 kind_ = 0;          // 0 point/line (unsupported), 1 triangle, 2 sprite
    bool iip_ = false;
    s32 ofx_ = 0, ofy_ = 0;
    GpuRect sc_{};
    bool sc_empty_ = true;
    bool open_match_ = false;  // the open draw has cb_ and sc_ (valid while open_)
    GpuDrawCB cb_{};
    OpList l_;
    GpuRecorderStats st_{};
    GpuOp cur_{};
    bool open_ = false;
    std::vector<u32> mask_, dirty_;
    std::vector<u64> page_bits_;     // 512 pages x 32 u64: words written by full-word transfers since the last close
    std::vector<u16> dirty_pages_;
    std::vector<u8> page_dirty_;
    std::vector<u32> tiles_;
    u32 tile_gen_ = 1;
    std::vector<GpuVertex> native_gv_;  // on_native_triangles scratch
    u64 native_fallbacks_ = 0;
    u64 nat_pal_at_ = ~0ull;  // nat_in word index of the last stored palette (this list), its size
    u32 nat_pal_words_ = 0;
    // on_native_gpu_batch: the draw state decoded for the last GsRegs seen (consecutive batches rarely change it)
    bool nat_cache_ = false;
    GsRegs nat_regs_{};
    GpuDrawCB nat_cb_{};
    GpuRect nat_sc_{};
    s32 nat_ofx_ = 0, nat_ofy_ = 0;
    bool in_native_fallback_ = false;
    bool side_table_ = false;
    std::vector<u16> native_src_;       // on_native_triangles: the source vertex of each emitted vertex (side table)
};

} // namespace p3fes::gs
