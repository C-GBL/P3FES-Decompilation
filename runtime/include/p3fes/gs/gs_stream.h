// GS command-stream recording (diagnostics; docs/ANALYSIS/25_d3d11_gs_backend.md §6): every GsCore API call between
// two points, with the core's state and local memory at the start and at the end, in one file. A replay re-issues
// the calls into a fresh GsCore and must end on the recorded memory and state (`replay_software` checks it), so a
// recording is a self-contained, verifiable input for an alternative back end (tools/gsreplay: D3D11).
//
// File layout (little endian; written and read by the same build, `state_size` guards the GsCoreState layout):
//   "P3GSTRM1" | u32 version (1) | u32 state_size | u32 vram_bytes | u32 reserved
//   u64 start_vblank | u64 end_vblank | u64 start_flip | u64 end_flip
//   GsCoreState (start) | VRAM (start) | events... | kind 0 (end)
//   DisplayRegs (end) | GsCoreState (end) | VRAM (end)
// Events: 1 reg (u8 reg, u64) | 2 packed (u8 desc, 16 B) | 3 GIF tag | 4 image (u32 n, n x 16 B) | 5 HWREG (u64)
//         6 read_image (u32 n) | 7 reset.
#pragma once

#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_priv.h"

#include <filesystem>
#include <string>
#include <vector>

namespace p3fes::gs {

enum class StreamEvent : u8 { End = 0, Reg = 1, Packed = 2, GifTag = 3, Image = 4, HwReg = 5, ReadImage = 6, Reset = 7 };

// IGsStreamSink that appends the calls to a byte buffer between begin() and end().
class GsStreamRecorder final : public IGsStreamSink {
public:
    // Snapshot the start (state + memory) and attach as `core`'s sink.
    void begin(GsCore& core, u64 vblank, u64 flip);
    // Detach, snapshot the end and the display registers; then write() may be called.
    void end(GsCore& core, const DisplayRegs& disp, u64 vblank, u64 flip);
    bool recording() const noexcept { return core_ != nullptr; }
    bool finished() const noexcept { return finished_; }
    std::size_t event_bytes() const noexcept { return events_.size(); }
    bool write(const std::filesystem::path& path, std::string& error) const;

    void on_reg(u32 reg, u64 value) override;
    void on_packed(u32 desc, const u128& q) override;
    void on_gif_tag() override;
    void on_image(std::span<const u128> qwords) override;
    void on_hwreg(u64 value) override;
    void on_read_image(std::size_t qwords) override;
    void on_reset() override;

private:
    void put(const void* p, std::size_t n);
    GsCore* core_ = nullptr;
    bool finished_ = false;
    u64 start_vblank_ = 0, end_vblank_ = 0, start_flip_ = 0, end_flip_ = 0;
    GsCoreState start_state_{}, end_state_{};
    std::vector<u8> start_vram_, end_vram_;
    DisplayRegs disp_{};
    std::vector<u8> events_;
};

// A recording read back.
struct GsStream {
    u64 start_vblank = 0, end_vblank = 0, start_flip = 0, end_flip = 0;
    GsCoreState start_state{}, end_state{};
    std::vector<u8> start_vram, end_vram;
    DisplayRegs disp{};
    std::vector<u8> events;  // the event bytes including the End marker
};
bool read_stream(const std::filesystem::path& path, GsStream& out, std::string& error);

// Load the stream's start into `core` (state + memory).
void load_stream_start(const GsStream& s, GsCore& core);
// Re-issue every event into `core` (which the caller prepared, e.g. with load_stream_start). Returns the number of
// events; `error` is set on a malformed stream.
std::size_t replay_events(const GsStream& s, GsCore& core, std::string& error);

struct ReplayCheck {
    std::size_t events = 0;
    u64 vram_bytes_differing = 0;  // vs the recorded end memory
    bool state_equal = false;      // registers, queue, CLUT, transfer state vs the recorded end state
    bool ok() const noexcept { return vram_bytes_differing == 0 && state_equal; }
};
// load_stream_start + replay_events into `core` with software rasterisation, then compare with the recorded end.
ReplayCheck replay_software(const GsStream& s, GsCore& core, std::string& error);

} // namespace p3fes::gs
