// Phase 5 slice fx_epl: the EPL effect-object player API, 0x34C160-0x350034 (docs/ANALYSIS/27_unmapped_bands.md
// section 6, docs/ANALYSIS/queue_bands.txt block `fx_epl`).
//
// What is here. The band is the API the game code uses to drive "EPL" effects (the name comes from its callers'
// task names: "epl(kosaka)", "IconEplDestroyDell"; inf). It has two layers:
//
//   [kinds]  Four effect-object kinds, each a 13-slot function row in the table 0x69C368 (52 bytes a row; the row
//            order and slot meaning below are read from the table and the bodies, the slot names are proposals):
//              slot 0 create, 1 update (step + draw or draw request), 2 step, 3 draw / draw request, 4 destroy,
//              5 clone, 6 copy from another object, 7 reset, 8 set position (vec4), 9 set rotation (vec4),
//              10 set scale ($f12), 11 null, 12 set colour (RGBA word).
//            kind 1 (row 0x69C368): one character model (+148) with a lifetime (+140, 0 = forever), an age (+152), an
//              animation advance (+36, 1.0 per step), position +0 / rotation +16 / scale +32 / colour +40, the colour
//              and scale tracks +44 / +96 (sampled by sub_32A120 / sub_32A540), additive flag +144 and draw layer +84.
//            kind 2 (row 0x69C39C): a model (+160) whose frames carry effect nodes (+152, one node pointer per frame,
//              +40 frames), lifetime +144 / age +44, colour +36, colour / scale tracks +48 / +100, node mode +156.
//            kind 3 (row 0x69C3D0): a particle system (+88, the 0x3322xx layer) with one 24-byte record per particle
//              (+92), its clump (+84, an RpClump with material colours modulated), its kind word +12 (3 = emit).
//            kind 4 (row 0x69C404): a particle system (+92) with one 28-byte record per particle (+100), a shared
//              texture (+96, RwTexture: its reference count is +84), the colour +4, scroll speeds +28 / +32 added to
//              the scroll positions +84 / +88 each step.
//   [nodes]  Thin wrappers over the effect-node layer 0x324BD0-0x326170 (create, destroy, draw, release, set
//            position / rotation / scale / colour, rotation from Euler angles or a matrix, node -> matrix) and the
//            two RpClumpForAllAtomics callbacks of kind 3 (material colour, modulate flag).
//
// Kept recompiled (called through their generated entry points): the model layer (sub_316E00 create, sub_3174E0
// destroy, sub_3182D0 animation, sub_317730 / sub_317A20 frame update and draw), the node layer, the RenderWare
// stream / clump / texture-dictionary calls of kind 3's loader, and the kind constructors / destructors of the
// band that allocate through the RW memory functions (0x960178..0x96018C: sub_34C160, sub_34C1B0, sub_34C670,
// sub_34C890, sub_34C9B0, sub_34D510, sub_34D670, sub_34D6F0, sub_34D8A0, sub_34E4C0, sub_34E610, sub_34E690,
// sub_34E820). sub_34DC00 and sub_34EAE0 (kind 3 / kind 4 particle drawing, the DMA packet builders) belong to the
// rendering queue.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6, 7 and 10): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO, FPR, ACC, FCR31 and the VU0 registers hold what the original holds there, and
// the prologues write the original spills (the compiler's 128-bit frame slots included). The bodies work on the
// guest registers directly (the Cpu view in fx_epl.cpp, one named variable per register, as core3.cpp), with the
// data flow named in comments; the per-block virtual time follows the recompiled bodies (ADR-0013).
//
// Names: every function keeps its symbols/functions.json name; a bracketed role is a proposal (not imported).
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/fx/fx_epl.cpp. Each function below
// takes its guest arguments as 64-bit register values ($a0..) and returns $v0 (for the void ones, $v0 is whatever
// the original left); float arguments ($f12..$f14) and the VU0 registers are read from the context as they are.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

// --- kind 1: the model object (row 0x69C368) -----------------------------------------------------------------
u64 sub_34C250(EEContext& ctx, u64 dst, u64 src);  // [slot 6 copy]: destroy dst's model, create one like src's
u64 sub_34C320(EEContext& ctx, u64 obj);           // [slot 7 reset]: the model's animation 0 at time 0
u64 sub_34C350(EEContext& ctx, u64 obj);           // [slot 2 step]: advance 1.0 and age + 1 while alive
u64 sub_34C390(EEContext& ctx, u64 obj);           // [draw]: colour / scale tracks, transform, animate, draw
u64 sub_34C5A0(EEContext& ctx, u64 obj);           // [slot 3]: queue on the draw layer +84 (sub_3212E0)
u64 sub_34C5D0(EEContext& ctx, u64 obj);           // [slot 1 update]: step, then queue on the draw layer
u64 sub_34C630(EEContext& ctx, u64 obj, u64 v);    // [slot 8]: position (16 bytes at +0)
u64 sub_34C640(EEContext& ctx, u64 obj, u64 v);    // [slot 9]: rotation (16 bytes at +16)
u64 sub_34C650(EEContext& ctx, u64 obj, u64 rgba); // [slot 12]: colour word +40
u64 sub_34C660(EEContext& ctx, u64 obj);           // [slot 10]: scale +32 = $f12

// --- kind 2: the node-carrying model (row 0x69C39C) ----------------------------------------------------------
u64 sub_34C940(EEContext& ctx, u64 obj);           // [slot 5 clone]: create, copy 104 bytes from +48, copy-from
u64 sub_34CB60(EEContext& ctx, u64 obj);           // [slot 7 reset]: release every node, reset the animation
u64 sub_34CC00(EEContext& ctx, u64 obj);           // [slot 2 step]: transform + animate, place / colour the nodes
u64 sub_34CF30(EEContext& ctx, u64 obj);           // [slot 3 draw]: draw the nodes (mode 0: debug frame gizmos)
u64 sub_34D050(EEContext& ctx, u64 obj);           // [slot 1 update]: step, then draw
u64 sub_34D090(EEContext& ctx, u64 obj, u64 v);    // [slot 8]: position
u64 sub_34D0A0(EEContext& ctx, u64 obj, u64 v);    // [slot 9]: rotation
u64 sub_34D0B0(EEContext& ctx, u64 obj, u64 rgba); // [slot 12]: colour word +36
u64 sub_34D0C0(EEContext& ctx, u64 obj);           // [slot 10]: scale +32 = $f12

// --- kind 3: the clump particle system (row 0x69C3D0) --------------------------------------------------------
u64 sub_34D0D0(EEContext& ctx, u64 atomic, u64 rgba);  // [RpClumpForAllAtomics callback: every material's colour]
u64 sub_34D130(EEContext& ctx, u64 atomic);            // [callback: geometry flag 0x40, modulate material colour]
u64 sub_34D150(EEContext& ctx, u64 obj, u64 rec);      // [emit: direction, speed, spin, colour phase of a record]
u64 sub_34D3A0(EEContext& ctx, u64 obj, u64 rec, u64 time);  // [colour of a record at `time`: $vf10 *= key colour]
u64 sub_34D810(EEContext& ctx, u64 dst, u64 src);      // [slot 6 copy]: clone src's clump when its kind is 3
u64 sub_34D990(EEContext& ctx, u64 obj, u64 data, u64 size);  // [load the clump (+ texture dictionary) of a stream]
u64 sub_34DB00(EEContext& ctx, u64 obj);               // [slot 7 reset]: sub_332200(system)
u64 sub_34DB30(EEContext& ctx, u64 obj);               // [slot 2 step]: step the system, emit the new particles
u64 sub_34E390(EEContext& ctx, u64 obj);               // [slot 3]: queue on the system's layer (sub_321220)
u64 sub_34E3D0(EEContext& ctx, u64 obj);               // [slot 1 update]: step, then queue
u64 sub_34E420(EEContext& ctx, u64 obj, u64 v);        // [slot 8]: system position
u64 sub_34E450(EEContext& ctx, u64 obj, u64 v);        // [slot 9]: system rotation
u64 sub_34E480(EEContext& ctx, u64 obj, u64 rgba);     // [slot 12]: colour word +4
u64 sub_34E490(EEContext& ctx, u64 obj);               // [slot 10]: scale +8 = $f12, system scale

// --- kind 4: the textured particle system (row 0x69C404) -----------------------------------------------------
u64 sub_34E7C0(EEContext& ctx, u64 obj, u64 name);     // [texture +96 = sub_3210C0(name)]
u64 sub_34E800(EEContext& ctx, u64 dst, u64 src);      // [slot 6 copy]: share src's texture (reference + 1)
u64 sub_34E910(EEContext& ctx, u64 obj);               // [slot 7 reset]: sub_332200(system)
u64 sub_34E940(EEContext& ctx, u64 obj, u64 rec);      // [emit: the 28-byte record of a new particle]
u64 sub_34F6B0(EEContext& ctx, u64 obj);               // [slot 2 step]: scroll, emit, move the particles
u64 sub_34F910(EEContext& ctx, u64 obj, u64 mode);     // [draw the particles; mode 1 binds the texture raster]
u64 sub_34FB40(EEContext& ctx, u64 obj);               // [draw, mode 0]
u64 sub_34FB70(EEContext& ctx, u64 obj);               // [draw, mode 1]
u64 sub_34FBA0(EEContext& ctx, u64 obj);               // [slot 3]: queue on the system's layer (sub_3212A0)
u64 sub_34FBE0(EEContext& ctx, u64 obj);               // [slot 1 update]: step, then queue
u64 sub_34FC30(EEContext& ctx, u64 obj, u64 v);        // [slot 8]
u64 sub_34FC60(EEContext& ctx, u64 obj, u64 v);        // [slot 9]
u64 sub_34FC90(EEContext& ctx, u64 obj, u64 rgba);     // [slot 12]: colour word +4
u64 sub_34FCA0(EEContext& ctx, u64 obj);               // [slot 10]: scale +8 = $f12

// --- [nodes] the effect-node wrappers -------------------------------------------------------------------------
u64 sub_34FCD0(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 a3);  // [create a node: sub_324BD0, arguments as given]
u64 sub_34FCF0(EEContext& ctx, u64 node);              // [destroy: sub_3257E0]
u64 sub_34FD10(EEContext& ctx, u64 node);              // [release the children: sub_325B80]
u64 sub_34FD30(EEContext& ctx, u64 node);              // [draw: sub_3252A0]
u64 sub_34FD50(EEContext& ctx, u64 node);              // [sub_325920]
u64 sub_34FD70(EEContext& ctx, u64 node, u64 layer);   // [draw on a layer: sub_321120(layer), sub_325500(node)]
u64 sub_34FDB0(EEContext& ctx, u64 node, u64 layer);   // [sub_321120(layer), sub_3257A0(node)]
u64 sub_34FDF0(EEContext& ctx, u64 node, u64 pos);     // [position from a vec3 (w = 0): sub_325C10]
u64 sub_34FE30(EEContext& ctx, u64 node);              // [rotation from Euler angles $f12..$f14 (x gp-32220)]
u64 sub_34FE80(EEContext& ctx, u64 node, u64 matrix);  // [position and rotation from an RwMatrix]
u64 sub_34FF70(EEContext& ctx, u64 node);              // [scale $f12: sub_325E40]
u64 sub_34FF90(EEContext& ctx, u64 node, u64 rgba);    // [colour from *rgba: sub_326030]
u64 sub_34FFC0(EEContext& ctx, u64 node, u64 matrix);  // [node -> matrix: rotation +80 and position +64]

}  // namespace p3fes::game
