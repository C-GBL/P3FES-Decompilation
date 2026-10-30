// CRTC composition of the displayed picture from GS local memory, and PNG output for tests and screenshot
// comparison (runtime/gs/README.md "Output").
//
// `compose` does what the PCRTC does with PMODE/SMODE2/DISPFB1-2/DISPLAY1-2/BGCOLOR (GS User's Manual §8): each
// enabled read circuit fetches its rectangle (FBP/FBW/PSM, DBX/DBY) and places it at DX/(MAGH+1), DY/(MAGV+1);
// circuit 1 is blended over circuit 2 (or BGCOLOR when SLBG=1 or where circuit 2 has no pixel) with ALP (MMOD=1)
// or circuit 1's pixel alpha (MMOD=0), 0xFF = 1.0. The result is in buffer pixels (one output pixel per
// read-circuit pixel; MAGH/MAGV are divided out). Interlace: SMODE2.INT=1 with FFMD=0 (FIELD mode) reads every
// other line per field, so both fields of a frame come from one buffer and the woven frame is the buffer's lines
// in order; FFMD=1 (FRAME mode) reads every line in each field, so each buffer line covers two woven lines.
#pragma once

#include "p3fes/gs/gs_mem.h"
#include "p3fes/gs/gs_priv.h"

#include <span>
#include <string>
#include <vector>

namespace p3fes::gs {

struct ComposeInfo {
    bool circuit_enabled[2] = {false, false};
    u32 circuit_width[2] = {0, 0};
    u32 circuit_height[2] = {0, 0};
    s32 circuit_x[2] = {0, 0}; // placement inside the composed frame
    s32 circuit_y[2] = {0, 0};
};

// Compose the woven frame. Returns an empty frame when no circuit is enabled or the display is degenerate.
Frame compose(const GsMemory& mem, const DisplayRegs& regs, ComposeInfo* info = nullptr);

// PNG (8-bit RGB, stored deflate blocks) of `frame`; alpha is dropped.
std::vector<u8> encode_png(const Frame& frame);
bool write_png(const std::string& path, const Frame& frame);

// FNV-1a over the RGB bytes: a stable fingerprint for logs and tests.
u64 frame_hash(const Frame& frame) noexcept;

// Bilinear resample (used to compare a 640x448 frame with a 640x480 PCSX2 screenshot).
Frame resample_bilinear(const Frame& src, u32 width, u32 height);

struct FrameDiff {
    u32 max_abs = 0;         // over R, G, B
    double mean_abs = 0.0;   // over R, G, B of all pixels
    u64 pixels_over = 0;     // pixels with any channel difference > tolerance
    u64 pixels = 0;
    double psnr_db = 0.0;    // infinity reported as 999
};
// Sizes must match. Optionally writes |a-b| * 4 per channel into `diff_image`.
FrameDiff diff_frames(const Frame& a, const Frame& b, u32 tolerance, Frame* diff_image = nullptr);

} // namespace p3fes::gs
