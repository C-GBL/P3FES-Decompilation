// Modernize layer 5, step 3 (docs/MODERNIZE_PLAN.md "Layer 5 status"): RenderWare's g3 pipelines -- g3_generic,
// g3_skin and their MatFX forms -- at the PS2All bridge seam, their packets handed to the GS as host packets.
//
// The seam (p3fes/native/graphics_service.h G3Service): the RW sky driver's object node and material bridges report
// per object the camera x object matrix and the light block size, per mesh the quadwords they send to VU1 0x3FA..0x3FC
// (the GIF tag, the material colour, the surface properties), the GS register shadows, the program and the resEntry.
// The records queue in submission order; each g3 run on VU1 is matched with the first queued record whose quadwords
// VU1 memory holds (every cluster of a mesh is one run with the same block; records before the match are dropped:
// draws that never reached VU1), so a run is known to be the draw of one mesh of one object of the frame -- the
// identity step 5 draws from when there are no packets any more.
//
// The model: a g3 batch's output is what the game's own program computes from VU1 memory, and that program already
// runs as exact native code -- its ahead-of-time translation (runtime/vu1/vu1_aot.h: every pair's semantics, the
// VU float datapath, flags, Q / P timing, checked against the interpreter by Mode::Diff). The hook keeps it as the
// model: it lets the VU1 run (compiled when resident, interpreter otherwise; traps, step limits and statistics as
// always), takes the run's XGKICKs off the GIF path and hands them to the VU1's sink as host packets
// (IGifSink::kick_host: Gif::path1_host applies a PACKED STQ / RGBAQ / XYZ packet without the tag walk, through
// GsCore::packed_run, into the d3d11 op recorder or the software GS). The packets reach the sink in the order and at
// the point of the stream the program kicks them (after the run; nothing else touches the GIF during a VU1 run).
// A hand-written model was measured not to pay here (docs/MODERNIZE_PLAN.md "Layer 5 status", step 3): the compiled
// g3 programs run at ~5 ns a pair on the VU1 worker, off the EE thread's critical path.
//
// Check mode (--native-graphics-check N): every N-th g3 run also runs on a scratch VU1 in the interpreter from the
// same state (the oracle), and every register, flag, data word, TPC / PC, the branch view and the kicked packets are
// compared with what the run left.
#pragma once

#include "p3fes/gs/vif1.h"
#include "p3fes/native/graphics_service.h"
#include "p3fes/vu1/vu1_interp.h"

#include <cstdio>
#include <deque>
#include <memory>
#include <mutex>
#include <span>
#include <string>
#include <vector>

namespace p3fes::native::graphics {

enum class G3Family : u8 { None, Generic, Skin, MatFx, SkinMatFx, Count };
const char* to_string(G3Family f) noexcept;
// The family of a census program name ("vu1_prog_064_g3_skin" -> Skin); None for every other program.
G3Family g3_family_of(const char* name) noexcept;

struct G3Stats {
    // reported by the game side
    u64 objects = 0, meshes = 0, meshes_matfx = 0;
    // VU1 runs
    u64 runs = 0;                                      // runs with a g3-family program resident
    u64 family[static_cast<int>(G3Family::Count)] = {};
    u64 matched = 0, unmatched = 0;                    // runs whose 0x3FA..0x3FC block a queued mesh record holds
    u64 dropped = 0, overflow = 0;                     // records passed over / discarded at the queue bound
    u64 kicks = 0, kick_qw = 0, host_kicks = 0;        // XGKICKs of those runs; handed over as host packets
    u64 other_form[static_cast<int>(G3Family::Count)] = {};  // kicks not of Gif::path1_host's form (the GIF walks them)
    u64 other_runs = 0;                                // runs of other programs (left to the next hook)
    u64 checked = 0, check_bad = 0;                    // --native-graphics-check N
};

class NativeG3Seam final : public G3Service, public gs::IVuRunHook, public vu1::IGifSink {
public:
    NativeG3Seam();
    ~NativeG3Seam() override;

    // The programs it takes (the g3 families of the compiled table, vu1::aot_programs(), at construction); tests add
    // a dumped program image.
    void add_program(std::span<const u8> image, G3Family f);

    // G3Service (EE fiber)
    void object(const G3ObjectRecord& o) override;
    void mesh(const G3MeshRecord& m) override;

    // gs::IVuRunHook (VIF1 / the pipeline's VU1 stage)
    bool run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    void after_exact(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) override;
    // vu1::IGifSink: the kicks of the run in flight
    void kick(std::span<const u128> q) override;

    void set_next(gs::IVuRunHook* h) noexcept { next_ = h; }
    gs::IVuRunHook* next() const noexcept { return next_; }
    // false: the kicks go to the sink as ordinary kicks (the GIF walk), the seam and the check stay.
    void set_direct(bool on) noexcept { direct_ = on; }
    void set_check(u32 every, std::FILE* log);
    void clear_queue();

    const G3Stats& stats() const noexcept { return st_; }

private:
    struct Prog {
        std::vector<u8> image;
        u64 head = 0;
        G3Family fam = G3Family::None;
    };
    G3Family identify(const vu1::MicroMemory& m);
    void match(const vu1::VU1State& s);
    void check(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu);

    std::vector<Prog> progs_;
    u64 gen_ = ~0ull;
    G3Family fam_ = G3Family::None;
    std::mutex m_;
    std::deque<G3MeshRecord> q_;
    u8 miss_block_[48] = {};  // the last unmatched run's block and the queue length then (under m_)
    std::size_t miss_queue_ = 0;
    bool miss_valid_ = false;
    gs::IVuRunHook* next_ = nullptr;
    bool forwarded_ = false;
    bool capturing_ = false;
    bool direct_ = true;
    vu1::IGifSink* saved_ = nullptr;
    std::vector<std::vector<u128>> pk_;  // the run's kicks, in order
    std::size_t npk_ = 0;
    G3Stats st_{};
    // check mode
    u32 check_every_ = 0;
    u64 check_seq_ = 0;
    std::FILE* log_ = nullptr;
    std::unique_ptr<vu1::VU1State> before_;
    bool checking_ = false;
    struct Checker;
    std::unique_ptr<Checker> chk_;
};

}  // namespace p3fes::native::graphics
