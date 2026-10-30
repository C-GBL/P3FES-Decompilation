// Presentation backend for the GS output.
//
// The GS itself is emulated in software (runtime/gs: GIF -> GS core -> 4 MiB local memory); the CRTC composition
// of the displayed picture (`p3fes::gs::compose`) produces an RGBA frame, and a backend only shows that frame in a
// window. No GS drawing happens on the host GPU (correctness first; runtime/gs/README.md).
#pragma once

#include "p3fes/gs/gs_types.h"

// Forward-declare HWND without dragging <windows.h> into every consumer.
// Matches the SDK's own DECLARE_HANDLE(HWND) expansion.
#ifndef _WINDEF_
struct HWND__;
using HWND = HWND__*;
#endif

namespace p3fes::gs {

class IGsBackend {
public:
    virtual ~IGsBackend() = default;

    // Create device resources bound to `window`. Returns false on failure.
    virtual bool init(HWND window) = 0;

    // Upload a composed frame and present it.
    virtual void present_frame(const Frame& frame) = 0;

    // Present again (the last uploaded frame, or a clear before the first one).
    virtual void present() = 0;

    virtual void shutdown() = 0;
};

} // namespace p3fes::gs
