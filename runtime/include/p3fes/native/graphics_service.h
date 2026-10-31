// Modernize pass, layer 5: graphics (docs/MODERNIZE_PLAN.md §2 row 5, §3 "5. Graphics", "Layer 5 status"; ADR-0017).
//
// The seam between the game's own draw submission and the host. Step 1 covers RenderWare's Im2D path (every sprite,
// glyph, window, fade and HUD quad; docs/ANALYSIS/22_rendering.md §6): the RW sky driver's packet functions
// open2DVU1Pkt 0x4EC100 and closeAndDispatchVU1Packet 0x4EC4C0 (game/src/render/render_im2d.cpp), which every Im2D
// draw of the game passes through, hand each packet they build to `g_service`: the program it runs, the three
// constant quadwords of its head and, per batch, the RwIm2DVertex records exactly as they go to the VU1. The packet
// itself is still built and queued unchanged (its DMA bytes and timing are what the EE observes); the host draws the
// batch from these records when the VU1 program would run on it (runtime/native/graphics). With `g_service ==
// nullptr` (the default, `--native` without `graphics`) nothing is reported and the game code is unchanged.
// The game library depends on headers only, so this is an interface plus an inline pointer.
#pragma once

#include <cstddef>
#include <span>

#include "p3fes/ee_types.h"

namespace p3fes::native::graphics {

// One Im2D packet as open2DVU1Pkt opened it and the builder filled it (render_im2d.h data flow):
//   program   the VU1 program image the descriptor names (the `call` target, e.g. 0x5CD980 = program 039, the no-fog
//             triangle program);
//   head      the three quadwords its head UNPACKs to VU1 0x3F9..0x3FB: the two offset floats, the GIF tag of the
//             kick with PRIM patched in, the colour scale (TME head or not);
//   batches   per batch: n primitives and their vertex quadwords (prim_qw * n: 12 per triangle, 3 RwIm2DVertex
//             records of 4 quadwords each, in the order the VU1 receives them).
struct Im2DBatchView {
    u32 n = 0;
    std::span<const u128> qw;
};

class Im2DService {
public:
    virtual ~Im2DService() = default;
    // True when packets of this program are worth reporting (the host draws them); false = skip the parse.
    virtual bool wants(u32 program) const noexcept = 0;
    // A closed packet of a program wants declined (counted only).
    virtual void other_packet(u32 program) noexcept { (void)program; }
    // One closed packet, on the EE fiber, before its DMA runs.
    virtual void packet(u32 program, const u128 (&head)[3], std::span<const Im2DBatchView> batches) = 0;
};

// Installed by the host (GameHost) while `--native graphics` is on; nullptr = the faithful path.
inline Im2DService* g_service = nullptr;

// Step 3: the PS2All bridge seam (docs/ANALYSIS/22_rendering.md §3, §8.2; game/include/p3fes/game/mesh.h data flow).
// The RW sky driver's object node and material bridges (PS2AllNodeBody's set-up callbacks, openVU1SetupPktNew,
// RpMeshPS2AllBridgeCallBack and the MatFX / skin bridges of game/src/render/bridges.cpp) report, after the guest
// state of the draw is complete, what they serialise for the g3 programs: per object the camera x object matrix and
// the light block, per mesh the GIF tag, the material colour and the surface properties quadwords (VU1 0x3FA..0x3FC),
// the GS register shadows of its A+D block, the VU1 program (code-array entry) and the resEntry whose instanced
// clusters are `call`ed. Host-side records only: no guest effect. The host matches them with the g3 runs on VU1.
struct G3ObjectRecord {
    u128 matrix[4] = {};  // the object-to-camera matrix rows as openVU1SetupPktNew packs them (all zero: none)
    u32 light_qw = 0;     // light block quadwords (the light-count header included)
};
struct G3MeshRecord {
    u128 block[3] = {};   // GIF tag (the bridge's template after the PRIM patch), material colour, surface properties
    u64 tex0 = 0, tex1 = 0, clamp = 0, test = 0;  // the raster's TEX0 after the cache placement (0 untextured), shadows
    u32 atomic = 0, material = 0, texture = 0;
    u32 program = 0;      // the code-array entry (the program's DMA packet)
    u32 res_data = 0;     // DMA address of the resEntry's instanced clusters
    u8 trans_type = 0, prim_type = 0, matfx = 0, pad = 0;  // matfx: reported by a MatFX / skin bridge
};
class G3Service {
public:
    virtual ~G3Service() = default;
    virtual void object(const G3ObjectRecord& o) = 0;
    virtual void mesh(const G3MeshRecord& m) = 0;
};
// Installed by the host while `--native graphics` is on; nullptr = nothing is reported.
inline G3Service* g_g3 = nullptr;

}  // namespace p3fes::native::graphics
