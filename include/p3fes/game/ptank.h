// Phase 5 slice render_ptank: RenderWare's particle tanks (RpPTank) on the PS2 driver -- the battle effects' sprites
// (docs/ANALYSIS/22_rendering.md sections 2.4, 4 and 7; queue_rendering.txt rows tagged [ptank]). The battle frame
// at vblank 5800 draws 22 PTank batches (ptank_spr3d, programs 028-035).
//
// Data flow of one tank (an atomic whose plugin data, at the gp-17792 offset, is the tank block):
//
//   the tank block (`tank` below)
//     +4 / +8      positions {pointer, stride}          (3 floats per particle)
//     +12 / +16    per-particle matrices {pointer, stride}  (right, up, at, pos rows)
//     +20 / +24    a second 3-float component (the +52 writer's source)
//     +28 / +32    per-particle size {pointer, stride}  (w, h)
//     +36 / +40    per-particle colour {pointer, stride}
//     +44 / +48    per-particle vertex colours {pointer, stride} (4 words)
//     +52 / +56    per-particle rotation {pointer, stride}
//     +60 / +64    per-particle UV rectangle {pointer, stride} (u0, v0, u1, v1)
//     +68 / +72    per-particle UV quad {pointer, stride} (4 pairs)
//     +88          the camera-axes flags (0x8000 own axes at +176 / +192, 0x20000 rotated by the angle at +120)
//     +104 / +108  the pivot (x, y) of the sprite in units of its size
//     +112 / +116  the constant size (w, h)       +124  the constant colour (RGBA bytes)
//     +128..+143   the constant vertex colours   +144..+175  the constant UV rectangle / quad
//     +156         the pipeline record (+184 .. +208 the GS context-2 words, +220 the instance state)
//     +168         the format / attribute flags: 0x4 size per particle, 0x8 matrix per particle, 0x20 rotation per
//                  particle, 0x1000000 pivot; 0x2 / 0x40 / 0x40000 colour, 0x10 the second component,
//                  0x80 / 0x100 / 0x80000 / 0x100000 UV
//
//   3-D tanks: the format set-up (sub_4866C0, or sub_47BF80 for the writers that stream through the scratchpad)
//   installs the instance callbacks at block +36 .. +56: +36 the instance begin sub_488550 (geometry growth, camera
//   axes, the geometry parts locked), +40 the position writer of the format, +44 the UV writer, +48 the colour writer,
//   +52 the second component, +56 the instance end sub_488B80. Every writer turns each particle into four vertices of
//   the lock record's stream ({dst, stride}, a vertex every `stride` bytes): v0 = p - r - u, v1 = p + r - u,
//   v2 = p + r + u, v3 = p - r + u with r / u the camera axes scaled by half the size. sub_4866C0's writers are
//   sub_486980 .. sub_4884A0 below; sub_47BF80's are the class-b instance writers sub_47C240 .. sub_485750 (D8 / D9 DMA,
//   kept recompiled) and, of this slice, sub_485070 / sub_485E20 / sub_485110 / sub_485440 / sub_486100, which hand a
//   stream laid out like their source to the scratchpad streamers (sub_476C20 copy, sub_476140 / sub_476720 fills).
//   The lock callbacks sub_479590 / sub_479170 fill the lock record; the bridge sub_479900 builds the VIF packet.
//   2-D tanks (sub_478440 installs them): the locks sub_477470 / sub_477150 and the one-vertex-per-particle writers
//   sub_477610 / sub_477A20 / sub_477EB0 / sub_478280; the bridge sub_478520.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO, FPR, ACC, FCR31 and VU0 register holds what the original holds there, and the
// prologues write the original spills (including the compiler's own spill slots of the big writers). The bodies
// work on the guest registers directly (the Cpu view in ptank.cpp, one named variable per register, as mesh.cpp),
// with the data flow named in comments; the per-block virtual time follows the recompiled bodies (ADR-0013).
//
// Names: every function keeps its symbols/functions.json name (all sub_*); a bracketed role is a proposal.
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/render/ptank.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

// --- 3-D sprite writers of sub_4866C0 (block +40 / +44 / +48 / +52): (stream {dst, stride}, ...). Counts are
// compared as whole 64-bit registers (signed): a count <= 0 writes nothing. ----------------------------------------
void sub_486980(EEContext& ctx);  // [register ABI] [positions, constant size]
void sub_486AE0(EEContext& ctx);  // [register ABI] [positions, constant size, pivot]
void sub_486EC0(EEContext& ctx);  // [register ABI] [positions, size per particle]
void sub_487520(EEContext& ctx);  // [register ABI] [positions, size per particle, pivot]
void sub_487990(EEContext& ctx);  // [register ABI] [matrix per particle]
void sub_487AC0(EEContext& ctx);  // [register ABI] [matrix per particle, pivot]
// ... with a rotation per particle {+52, +56}: sinf / cosf (recompiled) rotate the camera axes first.
void sub_486C80(EEContext& ctx);  // [register ABI] [rotation, constant size]
void sub_487030(EEContext& ctx);  // [register ABI] [rotation, size per particle]
void sub_487280(EEContext& ctx);  // [register ABI] [rotation, constant size, pivot]
void sub_4876F0(EEContext& ctx);  // [register ABI] [rotation, size per particle, pivot]
void sub_487BF0(EEContext& ctx);  // [register ABI] [colour per particle] {+36, +40} to all four vertices
void sub_488260(EEContext& ctx);  // [register ABI] [UV rectangle per particle]
void sub_4882F0(EEContext& ctx);  // [register ABI] [UV quad per particle]
void sub_488390(EEContext& ctx);  // [register ABI] [constant UV rectangle]
void sub_488410(EEContext& ctx);  // [register ABI] [constant UV quad]
void sub_487E80(EEContext& ctx);  // [register ABI] [vertex colours per particle]
void sub_487EF0(EEContext& ctx);  // [register ABI] [constant vertex colours]
void sub_4880B0(EEContext& ctx);  // [register ABI] [constant colour]
void sub_4884A0(EEContext& ctx);  // [register ABI] [second component per particle (+20)]
void sub_488B80(EEContext& ctx);  // [register ABI] [instance end]: sub_4933D0(lock +24), a tail call

// --- 3-D writers of sub_47BF80 with a scratchpad-streamer fast path ------------------------------------------------
void sub_486100(EEContext& ctx);  // [register ABI] [second component per particle (+20)]
void sub_485070(EEContext& ctx);  // [register ABI] [vertex colours per particle] (streamer copy)
void sub_485E20(EEContext& ctx);  // [register ABI] [UV quad per particle] (streamer copy)
void sub_485110(EEContext& ctx);  // [register ABI] [constant vertex colours] (+128.., fill streamer)
void sub_485440(EEContext& ctx);  // [register ABI] [constant colour] (+124, fill streamer)

// --- 2-D writers: one vertex per particle (the sprite is expanded on VU1); a source laid out as the stream goes
// through the copy streamer, the rest eight per iteration while count is in 9..0x7FFFFFFE, then one by one. ---------
void sub_477610(EEContext& ctx);  // [register ABI] [positions] ($a3 count, $t0 {+4, +8})
void sub_477A20(EEContext& ctx);  // [register ABI] [colours] {+36, +40}, RGBA bytes
void sub_477EB0(EEContext& ctx);  // [register ABI] [UV rectangles] {+60, +64}
void sub_478280(EEContext& ctx);  // [register ABI] [sizes] {+28, +32}

// --- lock callbacks, the format set-ups, the bridges ---------------------------------------------------------------
// The lock record at `lock`: +0 / +4 / +8 / +12 which components, +16 .. +44 their {pointer, stride}; `data` the
// tank data (+76 the pipeline record: buffer ring +224 / +228 / +232, 36-byte buffer records); flag 0x10000000 resets
// the tank first (sub_474A80, recompiled).
void sub_477150(EEContext& ctx);  // [register ABI] [2-D lock, next buffer]
void sub_479170(EEContext& ctx);  // [register ABI] [3-D lock, next buffer] + camera axes
void sub_479590(EEContext& ctx);  // [register ABI] [3-D lock] + camera axes
// [3-D instance begin]: geometry growth (default normals), camera axes, the geometry parts locked by geometryLock.
void sub_488550(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_4866C0(EEContext& ctx);  // [register ABI] [3-D format set-up]: the instance callbacks at block +36 .. +56
void sub_47BF80(EEContext& ctx);  // [register ABI] [3-D format set-up, streamed writers]
// [PTank material bridges] (PS2All pipe data): one VIF packet per batch; 1, or 0 when no packet could be opened.
void sub_478520(EEContext& ctx);  // [register ABI] [2-D bridge]
void sub_479900(EEContext& ctx);  // [register ABI] [3-D bridge]
// [tank as one object per particle matrix]: frustum test of the atomic's bounding sphere per 64-byte matrix, 80-byte
// VU1 records at 0x95C4A0 (matrix, clip flag, a per-particle vector), 48 a batch: sub_46C330 + RxPipelineExecute
// (recompiled). The count is compared unsigned. Returns the atomic.
void sub_47B280(EEContext& ctx);  // [register ABI] colours / 255
void sub_47B750(EEContext& ctx);  // [register ABI] vector in the matrix's axes

// --- the per-frame drivers and the tank's GS words ---------------------------------------------------------------
// [run the instance callbacks] the lock record on its own frame, instance begin (+36), the writers (+40 .. +52) of the
// components the record asks for, instance end (+56) -- all through jalr (rt::lookup_func). Returns 1.
void sub_4861B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_474160(EEContext& ctx);  // [register ABI] [tank atomic render callback]: lock (+28), instance (+32), render (+16)
void sub_488B90(EEContext& ctx);  // [register ABI] [render with the tank's blend states] (+100, +96, +92)
void sub_474A80(EEContext& ctx);  // [register ABI] [ALPHA word from the blend modes] (+92, +96 -> pipeline record +184)
void sub_4749A0(EEContext& ctx);  // [register ABI] [CLAMP from the address modes] (-> pipeline record +192)

}  // namespace p3fes::game
