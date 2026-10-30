// A synthetic scene for the host executable's --smoke / --headless runs (no game code is running yet): the game's
// SkyStart display setup (docs/ANALYSIS/10 §2: skyInitialClear, draw environment, flicker-free interlace on both
// circuits) followed by sprites, a Gouraud triangle, a PSMT8+CLUT and a PSMT4 textured sprite and an alpha-blended
// overlay, all sent through GIF PATH3 so the whole GIF -> GS -> CRTC path runs. No game data is involved.
#pragma once

#include "p3fes/gs/gs_system.h"

namespace p3fes::gs {

// Draws the scene into `gs` and returns the number of PATH3 quadwords consumed.
std::size_t run_selftest_scene(GsSystem& gs);

} // namespace p3fes::gs
