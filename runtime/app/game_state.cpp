// GameHost machine states (runtime/STATE.md): save_state / load_state and the file header checks.
#include "game_host.h"

#include <windows.h>

#include <cstdio>
#include <cstring>

#include "host_watch.h"
#include "input.h"
#include "p3fes/hle/cdvd.h"
#include "p3fes/pinned.h"
#include "p3fes/rt/rt_adapter.h"
#include "p3fes/state_io.h"

#if defined(P3FES_MACHINE_STATES)
extern "C" std::uintptr_t __security_cookie;  // the /GS cookie (vcruntime); state_boot.cpp adopts a state's
#endif

namespace p3fes::app {

namespace {

[[maybe_unused]] void copy_str(char* dst, std::size_t n, const std::string& s) {
    std::memset(dst, 0, n);
    std::memcpy(dst, s.data(), std::min(s.size(), n - 1));
}

} // namespace

void state_io(StateIo& io, FlipRecord& f) { io(f.count, f.vblank, f.cycles, f.circuit, f.fbp, f.sky, f.wall); }
void state_io(StateIo& io, MarkerEdge& m) {
    std::uint64_t what = reinterpret_cast<std::uint64_t>(m.what);  // a string literal of this executable
    io(what, m.from, m.to, m.vblank, m.cycles, m.sky, m.wall);
    m.what = reinterpret_cast<const char*>(what);
}

std::string GameHost::state_config() const {
    // Everything that changes what the guest sees and is chosen on the command line (the rest -- GS backend, VU1
    // engine, headless/windowed, audio outputs -- is exact either way or host-only).
    return "sk=" + cfg_.sk_mode + " layout=" + cfg_.iop_layout + " interp=" + cfg_.spu2_interp +
           " disc=" + std::string(disc_ && disc_->identity().kind == hle::DiscSourceKind::ExtractedVolumes ? "extracted" : "iso") +
           " sectors=" + std::to_string(disc_ ? disc_->sector_count() : 0) +
           (mods_ ? " mods=" + mods_->fingerprint() : std::string()) +  // ADR-0016: absent without --mods
           // ADR-0017 stage 0: the native layer set, absent while every layer is faithful (the baseline's string)
           (cfg_.native.any() ? " native=" + cfg_.native.to_string() : std::string()) +
           // layer 6's (b) set changes the timing: absent with the default (faithful) timing
           (cfg_.native_kernel_timing != "faithful" ? " ktiming=" + cfg_.native_kernel_timing : std::string());
}

std::string GameHost::state_summary() {
    int fibers = 0, threads = 0;
    for (int tid = 1; tid < 256; ++tid) {
        const hle::ThreadView v = kernel_->thread(tid);
        if (v.status == 0) continue;
        ++threads;
        if (v.has_fiber) ++fibers;
    }
    const hle::CdvdHle* cd = sif_->iop().cdvd();
    const hle::sif::AdxiStats as = sif_->iop().adxi_stats();
    return "threads " + std::to_string(threads) + " (" + std::to_string(fibers) + " on fibers), current " +
           std::to_string(kernel_->current_thread()) + ", CD read in flight " + (cd && cd->busy() ? "yes" : "no") +
           " (" + std::to_string(sif_->iop().stats().cd_reads) + " reads so far), IPU " + (ipu_->core().busy() ? "busy" : "idle") +
           " (" + std::to_string(ipu_->core().stats().macroblocks) + " macroblocks), ADX streams playing " +
           std::to_string(as.rna_playing);
}

bool GameHost::state_body(StateIo& io, PadFeed* feed) {
    io.section("host");
    mem_->state(io);
    if (!kernel_->state(io)) return false;
    gs_->state(io);
    ipu_->state(io);
    sif_->state(io);
    audio_->state(io);
    io.section("host-counters");
    // the census in its string form (the state format is unchanged): fold the fast counters in first
    fold_census(census_);
    census_fast_.clear();
    io(flips_, markers_, movie_flag_, movie_obj_, census_, bitbltbuf_, trxreg_, last_vblank_seen_, reason_);
    io(fatal_message_);
    bool has_feed = io.saving() ? (feed != nullptr && active_pad_feed() == feed) : false;
    io(has_feed);
    if (has_feed) {
        if (!feed) {
            io.fail("the state replays pad input but this run has no pad feed");
            return false;
        }
        feed->state(io);
        if (io.loading()) set_active_pad_feed(feed);
    }
    if (native_pad_) {  // --native input (state_config() records the layer set, so both sides have the pad)
        io.section("native-input");
        native_pad_->state(io);
    }
    if (native_sound_) {  // --native sound (layer 3)
        io.section("native-sound");
        native_sound_->state(io);
    }
    bool native_sk = native_sk_ != nullptr;  // steps 2-3: the native SK stack (IOP RAM and libsd are the IOP's)
    io.expect(native_sk, "native SK stack");
    if (native_sk_) {
        io.section("native-sk");
        native_sk_->state(io);
    }
    if (native_movies_) {  // --native movies (layer 4)
        io.section("native-movies");
        native_movies_->state(io);
    }
    io.section("end");
    return io.ok();
}

namespace {
[[maybe_unused]] constexpr const char* kNoStates =
    "this p3fes.exe was built without machine states: they need a dev-only build configured with "
    "-DP3FES_MACHINE_STATES=ON (fixed image base, adopted /GS cookie; runtime/STATE.md)";
}  // namespace

#if !defined(P3FES_MACHINE_STATES)
bool GameHost::save_state(const std::string&, const std::string&, PadFeed*, std::string& error) {
    error = kNoStates;
    return false;
}
bool GameHost::load_state(const std::string&, PadFeed*, std::string& error, StateHeader*) {
    error = kNoStates;
    return false;
}
#else
bool GameHost::save_state(const std::string& path, const std::string& label, PadFeed* feed, std::string& error) {
    gs_quiesce();  // the GS worker's census and every stage's state
    if (!started_ || dead_) {
        error = "no running machine to save";
        return false;
    }
    if (tracing_) {
        error = "machine states are not available with --trace-syscalls / --trace-hw (their wrapper sits on the guest stacks)";
        return false;
    }
    // D3D11 back end: GS memory from the GPU into the CPU copy, which the state carries (a loading run with the
    // D3D11 back end uploads it to the GPU again).
    if (!sync_gpu_memory(error)) return false;
    StateHeader h;
    std::string why;
    if (!exe_identity(h.exe_hash, h.exe_size, h.image_base, why)) {
        error = why;
        return false;
    }
    h.security_cookie = static_cast<std::uint64_t>(__security_cookie);
    h.reference_mode = rt::reference_mode() ? 1u : 0u;
    h.arena_used = pinned::arena_used();
    const hle::Timebase& t = kernel_->bus().time();
    h.vblanks = t.vblanks;
    h.cycles = t.cycles;
    h.flips = gs_->flip_count();
    copy_str(h.elf_sha256, sizeof h.elf_sha256, elf_sha256_);
    copy_str(h.config, sizeof h.config, state_config());
    copy_str(h.label, sizeof h.label, label);
    StateIo io;
    if (!state_body(io, feed) || !io.ok()) {
        error = io.error().empty() ? "state not saved" : io.error();
        return false;
    }
    return write_state_file(path, h, io.buffer(), error);
}

bool GameHost::load_state(const std::string& path, PadFeed* feed, std::string& error, StateHeader* header_out) {
    if (started_) {
        error = "load_state: the machine already ran (load right after init)";
        return false;
    }
    StateHeader h;
    std::vector<std::uint8_t> payload;
    if (!read_state_file(path, h, payload, error)) return false;
    std::uint64_t hash = 0, size = 0, base = 0;
    if (!exe_identity(hash, size, base, error)) return false;
    if (hash != h.exe_hash || size != h.exe_size) {
        error = path + " was saved by another p3fes.exe (states carry the guest threads' host stacks: same executable only)";
        return false;
    }
    if (base != h.image_base) {
        error = "p3fes.exe is loaded at another base than when the state was saved (ASLR?)";
        return false;
    }
    if (static_cast<std::uint64_t>(__security_cookie) != h.security_cookie) {
        error = "the /GS cookie was not adopted from the state (name it with --load-state on the command line)";
        return false;
    }
    if (h.arena_used != pinned::arena_used() || !pinned::enabled()) {
        error = "the pinned arena differs from the saver's (another allocation order or no fixed regions)";
        return false;
    }
    if (std::strncmp(h.elf_sha256, elf_sha256_.c_str(), sizeof h.elf_sha256) != 0) {
        error = "the state was saved with another ELF";
        return false;
    }
    const std::string cfg = state_config();
    if (std::strncmp(h.config, cfg.c_str(), sizeof h.config) != 0) {
        error = std::string("configuration mismatch: state \"") + h.config + "\", this run \"" + cfg + "\"";
        return false;
    }
    if (tracing_) {
        error = "machine states are not available with --trace-syscalls / --trace-hw";
        return false;
    }
    // --watch-write protects guest RAM pages: off while the state is copied in (those are not guest writes).
    if (cfg_.watch_len) disarm_write_watch();
    StateIo io(payload.data(), payload.size());
    const bool body_ok = state_body(io, feed);
    if (cfg_.watch_len)
        arm_write_watch(mem_->main_ram(), cfg_.watch_va & 0x01FFFFFFu, cfg_.watch_len, cfg_.watch_hits, syms_, &ctx_->cycles,
                        [this](const std::string& s) { log(s); });
    if (!body_ok || !io.ok()) {
        error = path + ": " + (io.error().empty() ? std::string("state not loaded") : io.error());
        dead_ = true;  // partially overwritten: never run it
        return false;
    }
    if (!io.at_end()) {
        error = path + ": trailing state data (a component reads less than it wrote)";
        dead_ = true;
        return false;
    }
    started_ = true;  // run() resumes the kernel instead of starting it
    // The state's RAM holds the saver's text (a headless saver had --pc-text off); not part of state_config(): the
    // wording is fixed data the guest only reads, so a state from either kind of run loads into either.
    apply_pc_text();
    if (header_out) *header_out = h;
    return true;
}
#endif  // P3FES_MACHINE_STATES

} // namespace p3fes::app
