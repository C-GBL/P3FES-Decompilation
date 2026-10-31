// Modernize layer 5, step 1 (docs/MODERNIZE_PLAN.md "Layer 5 status"): RenderWare's Im2D triangles drawn by the host.
//
// Every Im2D draw of the game (sprites, glyphs, windows, fades, the HUD, the movie quad: docs/ANALYSIS/22_rendering.md
// §6) is a packet that the RW sky driver's open2DVU1Pkt / closeAndDispatchVU1Packet build for VU1 program 039 (the
// no-fog triangle program, 47 pairs): per batch of at most 16 triangles, three RwIm2DVertex records per triangle,
// which the program turns into one PATH1 GIF packet (per triangle a tag with NLOOP 3 and ST / RGBAQ / XYZF2 per
// vertex: ST = (u, v) x 1/z, RGBA = FTOI0(colour x scale), XYZ = FTOI4(x + ox, y + oy, z), fog 0xFF) and XGKICKs.
//
// With `--native graphics` the game side reports each packet's typed records here (p3fes/native/graphics_service.h)
// when it closes the packet, and this object stands in for the VU1 when the program would run on one of its batches:
// it is the VIF1's VU1 run hook (gs::IVuRunHook; on the VU1 stage when the graphics pipeline runs), and for a run of
// program 039 whose inputs in VU1 memory are a reported batch it computes the program's outputs from the record
// itself -- the PATH1 packet, every VU1 data word and register the program writes, its MAC / status flags, TPC --
// and hands the packet to the VU1's own GIF sink (the GIF / GS path every XGKICK takes, the D3D11 op recorder behind
// it). The VU1 program does not run. Everything downstream (GIF, GS registers, the rasteriser or the D3D11 backend)
// therefore sees byte for byte what the faithful run produces, and every later VU1 run starts from the same state.
//
// Matching: the records queue in submission order, the runs come in the same order (one VIF1 chain per frame, after
// the EE built it). A run takes the first queued record whose triangle count and vertex / head words equal what the
// program would read from VU1 memory (the lanes it reads; the UNPACK's masked lanes are never read); earlier records
// are dropped. A run with no matching record (a batch built before a machine-state load, a packet the game side did
// not report) runs the program exactly. Since a run is computed only from words that equal VU1 memory and from the
// VU1's own registers / leftover words, the result does not depend on the matching being right, only on it being
// verified.
//
// Step 2: the packet goes to the VU1's sink as a host packet (IGifSink::kick_host): with the GIF idle,
// gs::Gif::path1_host applies it without the tag walk (GsCore::packed_run: the same registers, queue, draws and
// counters, the draw state decoded once per packet), and the builders' vertex UNPACK is written here as an image
// (`unpack`) instead of vif_unpack's generic masked decode. set_direct(false) keeps step 1's kick and vif_unpack.
#pragma once

#include "p3fes/gs/vif1.h"
#include "p3fes/native/graphics_service.h"
#include "p3fes/vu1/vu1_interp.h"

#include <cstdio>
#include <deque>
#include <memory>
#include <mutex>
#include <span>
#include <vector>

namespace p3fes::native::graphics {

// VU1 program 039 (tag 0x5CD980, code 0x5CD98C, 376 bytes; vu1_prog_039 of symbols/vu1_micro_census.json).
inline constexpr u32 kIm2DTriProgram = 0x5CD980u;
inline constexpr u32 kIm2DTriEndTpc = 0x2Du * 8u;  // TPC after a run (E at pair 0x2B): MSCNT resumes at `b 0x1`
inline constexpr u32 kIm2DMaxTris = 16;            // per batch (the builders' batch size)
inline constexpr u32 kIm2DOutOffset = 0xC0;        // output buffer = TOP + 0xC0, 10 qw per triangle + the EOP tag

// True when micro memory holds program 039 from address 0.
bool im2d_tri_resident(const vu1::MicroMemory& m) noexcept;

// One run of program 039 on `s`, computed natively: `from_mscal` = MSCAL 0 (else MSCNT from kIm2DTriEndTpc); the
// batch is s.itop triangles at s.top whose vertex quadwords are `verts` (12 per triangle) and whose head words
// (VU1 0x3F9..0x3FB) are `head`, both as the program reads them (the caller has verified that VU1 memory holds them).
// Writes every register, flag and data word the program writes, leaves s as after the program's end (TPC, PC), and
// sets `kick` to the PATH1 packet its XGKICK sends (empty when there are no triangles: the program does not kick).
void im2d_tri_run(vu1::VU1State& s, bool from_mscal, const u128 (&head)[3], const u128* verts, std::vector<u128>& kick);
// The float arithmetic of im2d_tri_run: true (default) = the SSE kernels when the CPU allows, false = fp:: only (tests).
extern bool g_im2d_fast;

// True when VU1 memory holds `verts` (n triangles at `top`) and `head` in every lane program 039 reads.
bool im2d_inputs_match(const vu1::VU1State& s, u32 top, u32 n, const u128 (&head)[3], const u128* verts) noexcept;

struct Im2DStats {
    // reported by the game side (closeAndDispatchVU1Packet)
    u64 packets = 0, batches = 0, tris = 0;
    u64 packets_other = 0;  // packets of other Im2D programs (lines 038, the fog pair 036 / 037): not reported
    // VU1 runs
    u64 runs = 0;           // runs with program 039 resident
    u64 native = 0, native_tris = 0, native_kick_qw = 0;
    u64 fb_entry = 0;       // MSCAL at another entry / MSCNT from another TPC
    u64 fb_count = 0;       // ITOP 0 or above 16
    u64 fb_nomatch = 0;     // no queued record holds these inputs
    u64 dropped = 0;        // records passed over by a later match (their run was not matched)
    u64 overflow = 0;       // records discarded at the queue bound
    u64 other_runs = 0;     // runs of other programs (left to the next hook / the VU1)
    u64 ns = 0;             // host time in run() for the native runs, without the kick (the check mode's runs included)
    u64 kick_ns = 0;        // host time in the GIF sink for their packets (the GIF / GS / renderer work)
    u64 kick_host = 0;      // step 2: packets handed over as host packets (Gif::path1_host), not walked by the GIF
    u64 unpacks = 0, unpack_qw = 0;  // step 2: Im2D vertex UNPACKs written by the host (no generic VIF decode)
    // --native-graphics-check N
    u64 checked = 0, check_bad = 0;
};

class NativeIm2D final : public Im2DService, public gs::IVuRunHook {
public:
    NativeIm2D();
    ~NativeIm2D() override;

    // Im2DService (EE fiber)
    bool wants(u32 program) const noexcept override { return program == kIm2DTriProgram; }
    void packet(u32 program, const u128 (&head)[3], std::span<const Im2DBatchView> batches) override;
    void other_packet(u32 program) noexcept override;

    // gs::IVuRunHook (VIF1 / the pipeline's VU1 stage)
    bool run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    void after_exact(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    bool unpack(const gs::UnpackArgs& a, const u32* words, std::size_t n, u8* mem, u32* row, u32& vectors) override;
    // Step 2: the packets go to the GS side as host packets (IGifSink::kick_host: applied without the GIF walk when the
    // GIF is idle) and the vertex UNPACKs are written here (true, the default); false = step 1 (kick, vif_unpack).
    void set_direct(bool on) noexcept { direct_ = on; }
    bool direct() const noexcept { return direct_; }

    // Another hook (the play-mode native renderer, runtime/native/native_vu.h) for the runs this one leaves.
    void set_next(gs::IVuRunHook* h) noexcept { next_ = h; }
    gs::IVuRunHook* next() const noexcept { return next_; }
    // Every `every`-th native run also runs the program exactly on a scratch VU1 from the same state and compares
    // registers, flags, data memory and the kicked packet (0 = off). Mismatches are described on `log`.
    void set_check(u32 every, std::FILE* log);
    // A machine state was loaded: the queued records belong to the old timeline.
    void clear_queue();

    const Im2DStats& stats() const noexcept { return st_; }

private:
    struct Rec {
        u128 head[3] = {};
        std::vector<u128> qw;
        u32 n = 0, spare = 0;  // (80 bytes: no tail padding)
    };
    bool take(const vu1::VU1State& s, u32 top, u32 n, Rec& out);
    void check(const gs::VuRunInfo& r, const vu1::VU1State& before, const vu1::VU1State& after);

    std::mutex m_;
    std::deque<Rec> q_;
    std::vector<std::vector<u128>> spare_;
    Rec cur_;
    std::vector<u128> kick_;
    gs::IVuRunHook* next_ = nullptr;
    bool forwarded_ = false;
    bool direct_ = true;
    u64 micro_gen_ = 0;
    bool resident_ = false;
    Im2DStats st_{};
    // check mode
    u32 check_every_ = 0;
    u64 check_seq_ = 0;
    std::FILE* log_ = nullptr;
    struct Checker;
    std::unique_ptr<Checker> chk_;
};

}  // namespace p3fes::native::graphics
