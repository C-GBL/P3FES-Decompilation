// Phase 5 slice fx_layers: the effect layers -- the after effects (eff_after.c / eff_afpack.c, 0x1E8330-0x1EF000)
// and the effect manager's layer lists, keyframe tracks, sprite players and mesh builders (0x320060-0x324158).
// docs/ANALYSIS/27_unmapped_bands.md sections 2 and 6; queue docs/ANALYSIS/queue_bands.txt "slice fx_layers".
// Live on all three replay routes: the kwlnTask "after effect render" (update sub_1EF060, created by effAfter_CreateAfterEffectRenderTask from
// kwlnInitMain) and the nine effect layer tasks of effMng_CreateEffectProgramTasks exist in every snapshot.
//
// After effects: weapon / limb trails. One after effect per pack instance, linked from gp-18980 (head) / gp-18984
// (tail) through +24 prev / +28 next; the task walks the list every frame:
//
//   sub_1EF060 (task, recompiled)
//     |  flag 8 (killed) or 2 (anchors fresh): sub_1EDBE0 [update]
//     |      per trail i (descriptor +4 -> +4 s16 count):
//     |        frame step (model +244) != 0: the trail script runs (sub_1EBA80: wait / trail on-off / fade / kill)
//     |        trail on: a new sample from the anchor pair (+20 [i], through the inverse model matrix unless the
//     |          script state says local) -> sub_1EB920 [push]: the ring's rails take it, then sub_1EBD80 builds
//     |          the Bezier handles of the newest segments (sub_1E8360 side vectors <- sub_1E88F0 segment normals,
//     |          sub_1ECD90 segment lengths, sub_1ECEC0 bends)
//     |        the ring's clock advances (sub_1ED0D0), a changed colour goes to the trail's material
//     |        sub_1E9AF0 [rebuild]: the trail geometry's prelit colours (sub_1ED0F0 per key and fade) and its
//     |          vertices from the cubic segments, picked by arc length (sub_1E7F90, queue_field)
//     |  flag 8 or 4 (draw requested, sub_1EDED0): sub_1EDF10 draws it
//
//   creation: sub_1EDA00 (none while flag 0x1400) -> sub_1EE2E0 / sub_1EEB90 (heap, recompiled; the trail rings
//   get their geometry from sub_1E8E80 and sub_1ED8A0) -> sub_1EEFC0 [link] -> sub_1EEE40 [start the scripts]
//
// The after effect (obs: instructions): +0 flags (1 started, 2 anchors fresh, 4 draw, 8 killed, 0x10 colour
// changed), +4 the pack descriptor (+4 s16 trail count, +24 bone-id pairs, +28 the trail scripts, +32 the model),
// +8 the 76-byte trail rings, +12 {atomic, material} per trail, +16 the 32-byte script states {+0 flags (1
// waiting, 2 trail on, 8 local anchors), +4 pc, +8 script start, +16 the ring, +20 wait counter, +24 u16 fade time,
// +28 fade frames}, +20 the 24-byte anchor pairs, +24 / +28 links, +32 RGBA.
// The trail ring: +0 the curve descriptor (+0 -> the curve parameters (weights +0..+24, side factors +28..+40),
// +4 -> the colour keys (8 bytes: +8 / +12 the two colour pointers; word 0 bit 0 textured), +8 capacity, +12 n
// segments), +4 flags (1 fading, 2 colours fresh), +8 sample count, +12 head, +16 / +20 the two rails (12-byte points),
// +24 / +32 start handles and +28 / +36 end handles per rail, +60 clock, +64 fade start, +68 fade length, +72 s16 shape
// (0 strip, 1 ribbon with a middle row, 2 camera-facing ribbon).
//
// Effect manager: the effect record's keyframe tracks (four slots at +12 + 16k, element array at +80, list link +84)
// run through the type table 0x69BB10 (16-byte entries {track(t), track(t, u, v), track(t, &record +64, u),
// apply(value, element)}, all jalr); the seven layer lists (tables of 9 banks x 7 layers, bank = gp-25288):
//   sub_321140 0x957920 (+24)   sub_321180 0x957820 (+44, bank >= 5)   sub_3211D0 0x957720 (+44, bank >= 5)
//   sub_321220 0x957620 (+100)  sub_321260 0x957520 (+92)              sub_3212A0 0x957420 (+108)
//   sub_3212E0 0x957320 (+156)
// drawn by sub_321360 (recompiled) from the layer tasks effMng_UpdateEffect3dTask [effect_3d] / effMng_UpdateEffect2dTask [effect_2d] /
// sub_321FE0; the sprite players (sub_3226B0 start, sub_322AB0 step, sub_322D40 seek) over effpack sprite sets; the
// image sequences (sub_322FD0); the effect meshes (grid / band builders over sub_3230F0 / sub_323C20, copy, texture
// swap) and the placement matrices (sub_323920 / sub_323A30). bands.sym names effMng_UpdateEffectProgramTask / effMng_UpdateEffect3dTask /
// effMng_UpdateEffect2dTask (task updates); the rest keep their functions.json names, roles in brackets in fx_layers.cpp.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): register-faithful bodies on a Cpu view of the guest
// context (as mesh.cpp / ptank.cpp): every GPR in 128 bits, HI/LO, FPRs, ACC and FCR31 hold what the original holds at
// every check point, call and return; prologue spills and frame buffers on the guest stack as compiled.
//
// Since the stand-ins (2026-10-21) the slice also holds the heap / file users wave 10 left out: the after-effect pack
// unpacker, ring allocator, creator and destroyer, the effect manager's records, image-sequence lists and chunks,
// sprite sets / players, image sequences, effect mesh objects and the two set-up functions (effMng_CreateEffectProgramTasks,
// effAfter_CreateAfterEffectRenderTask): the register-ABI declarations at the end, tests in test_fx_layers_si.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

// --- the C++ entry points (arguments as the EE ABI passes them; each runs the register-faithful body) -----------
// After effects
s32 sub_1E8330(EEContext& ctx, u32 ring, s32 k);                       // [ring slot of the k-th newest sample]
void sub_1E8360(EEContext& ctx, u32 ring, s32 sample, s32 side, u32 out);  // [out-of-plane vector at a sample]
void sub_1E88F0(EEContext& ctx, u32 ring, s32 sample, u32 out);        // [side vector at a sample]
u32 sub_1E8E80(EEContext& ctx, u32 ring, u32 material);                // [create a trail's geometry]
void sub_1E9AF0(EEContext& ctx, u32 ring, u32 geometry_slot);          // [rebuild a trail's geometry]
void sub_1EB920(EEContext& ctx, u32 ring, u32 rail0, u32 rail1);       // [push a sample]
void sub_1EBA50(EEContext& ctx, u32 state);                            // [restart a trail script]
void sub_1EBA80(EEContext& ctx, u32 state);                            // [run a trail script until it waits]
void sub_1EBD80(EEContext& ctx, u32 ring, s32 sample);                 // [Bezier handles of a segment]
float sub_1ECD90(EEContext& ctx, u32 ring, s32 sample, s32 rail);      // [segment length on a rail]
float sub_1ECEC0(EEContext& ctx, u32 ring, s32 sample);                // [bend at a sample]
void sub_1ED080(EEContext& ctx, u32 ring, float duration);             // [start the fade]
void sub_1ED0B0(EEContext& ctx, u32 ring);                             // [reset the timing record]
void sub_1ED0D0(EEContext& ctx, u32 ring, u32 step);                   // [advance the clock]
void sub_1ED0F0(EEContext& ctx, u32 ring, s32 key, u32 out, float t);  // [colour of a key pair at t]
void sub_1ED8A0(EEContext& ctx, u32 ring, u32 geometry);               // [clear the trail geometry]
u32 sub_1ED9E0(EEContext& ctx, u32 keys);                              // [a key list has keys]
u32 sub_1EDA00(EEContext& ctx, u32 pack, u32 colour);                  // [create an after effect]
void sub_1EDA90(EEContext& ctx, u32 effect);                           // [anchors from the model's bones]
void sub_1EDBE0(EEContext& ctx, u32 effect);                           // [update an after effect]
void sub_1EDED0(EEContext& ctx, u32 effect);                           // [request a draw]
void sub_1EE1D0(EEContext& ctx, u32 effect);                           // [kill an after effect]
void nullsub_10(EEContext& ctx);
void sub_1EE230(EEContext& ctx, u32 effect, u32 rgba);                 // [set the colour]
void sub_1EEE40(EEContext& ctx, u32 effect);                           // [start an after effect's scripts]
void sub_1EEFC0(EEContext& ctx, u32 effect);                           // [append to the live list]
u32 sub_1EF000(EEContext& ctx, u32 effect);                            // [live and not killed]

// Effect manager
u32 sub_320060(EEContext& ctx);                                        // [type table entry 2, slot 0]
void nullsub_106(EEContext& ctx);
void sub_320080(EEContext& ctx, u32 a, u32 b, float t, float u, float v);  // [apply two effects' tracks]
void sub_320380(EEContext& ctx, u32 list, float t);                    // [apply a list's tracks, one time]
void sub_3204A0(EEContext& ctx, u32 list, float t, float u, float v);  // [... three times]
void sub_320640(EEContext& ctx, u32 list, float t, float u);           // [... two times]
void sub_320770(EEContext& ctx, u32 list);                             // [colour and vector to the elements]
float sub_320810(EEContext& ctx, u32 list);                            // [the longest track]
u32 sub_320BA0(EEContext& ctx, u32 material, u32 record);              // [register a tagged material]
u32 sub_320CF0(EEContext& ctx, u32 atomic, u32 record);                // [collect an atomic's tagged materials]
u32 sub_320DA0(EEContext& ctx, u32 clump, u32 record);                 // [collect a clump's tagged materials]
u32 sub_320DE0(EEContext& ctx, u32 atomic, u32 record);                // [count an atomic's tagged materials]
u32 sub_320F70(EEContext& ctx, u32 clump, u32 name);                   // [count a clump's tagged materials]
u32 sub_321050(EEContext& ctx, u32 object);                            // [reference count +1 (+8)]
void sub_321070(EEContext& ctx, u32 list, u32 item);                   // [append to a pointer list]
u32 sub_3210A0(EEContext& ctx, u32 id);                                // [effect texture by id]
u32 sub_3210C0(EEContext& ctx, u32 image);                             // [texture from an image]
void sub_321120(EEContext& ctx, u32 bank);                             // [set the layer bank]
u32 sub_321130(EEContext& ctx);                                        // [the layer bank]
void sub_321140(EEContext& ctx, u32 object, u32 layer);                // [push on a layer list] (and the six below)
void sub_321180(EEContext& ctx, u32 object, u32 layer);
void sub_3211D0(EEContext& ctx, u32 object, u32 layer);
void sub_321220(EEContext& ctx, u32 object, u32 layer);
void sub_321260(EEContext& ctx, u32 object, u32 layer);
void sub_3212A0(EEContext& ctx, u32 object, u32 layer);
void sub_3212E0(EEContext& ctx, u32 object, u32 layer);
void sub_321320(EEContext& ctx, u32 matrix);                           // [set the effect view matrix]
u32 effMng_UpdateEffectProgramTask(EEContext& ctx);                                        // [effMng_UpdateEffectProgramTask]
u32 effMng_UpdateEffect3dTask(EEContext& ctx);                                        // [effMng_UpdateEffect3dTask]
u32 effMng_UpdateEffect2dTask(EEContext& ctx);                                        // [effMng_UpdateEffect2dTask]
void sub_321FE0(EEContext& ctx);                                       // [layer task: bank 8]
void sub_321F10(EEContext& ctx, u32 bank);                             // [clear a bank]
void sub_3226B0(EEContext& ctx, u32 player, s32 animation);            // [start a sprite animation]
void sub_322AB0(EEContext& ctx, u32 player, u32 track, u32 quad);      // [step a sprite track]
void sub_322D10(EEContext& ctx, u32 player, u32 quad);                 // [step the first track]
void sub_322D40(EEContext& ctx, u32 player, u32 frame);                // [seek every track]
u32 sub_322DA0(EEContext& ctx, u32 player, s32 index);                 // [texture of a sprite set]
u32 sub_322FB0(EEContext& ctx, u32 object);                            // [reference count +1 (+28)]
void sub_322FD0(EEContext& ctx, u32 sequence, u32 time, u32 out);      // [image of a sequence at a time]
u32 sub_323240(EEContext& ctx, u32 rows, u32 indices, u32 cols, u32 flags);  // [grid mesh]
u32 sub_3233A0(EEContext& ctx, u32 rows, u32 per_row, u32 stride, u32 indices, u32 flags);  // [grid mesh, open]
u32 sub_323640(EEContext& ctx, u32 source);                            // [copy an effect mesh]
void sub_323860(EEContext& ctx, u32 object, u32 layer);                // [push on 0x957920]
void sub_323880(EEContext& ctx, u32 object, u32 translation, u32 rotation, float scale);  // [place: R, s, T]
void sub_3238D0(EEContext& ctx, u32 object, u32 translation, u32 rotation, u32 scale);    // [place: S, R, T]
void sub_323920(EEContext& ctx, u32 matrix, u32 translation, u32 rotation, float scale);  // [matrix: R, s, T]
void sub_323A30(EEContext& ctx, u32 matrix, u32 translation, u32 rotation, u32 scale);    // [matrix: S, R, T]
void sub_323B90(EEContext& ctx, u32 mesh, u32 image);                  // [replace a mesh's texture]
void sub_323BF0(EEContext& ctx, u32 mesh, u32 out);                    // [texture size of a mesh]
u32 sub_323E10(EEContext& ctx, u32 bands, u32 rows, u32 cols, u32 stride, u32 indices, u32 flags);  // [band mesh]
u32 sub_323FB0(EEContext& ctx, u32 bands, u32 rows, u32 indices, u32 cols, u32 flags);              // [band mesh+]


// The functions taken with the stand-ins (2026-10-21; p3fes_handgen bodies on the register view hg_cpu.h): register
// ABI, the arguments in $a0.. and the result in $v0 as the EE passes them. Layouts above each body in fx_layers.cpp.
void sub_1E9920(EEContext& ctx);                              // [allocate a trail ring]
void sub_1E9A90(EEContext& ctx);                              // [free a trail ring]
void sub_1EE2E0(EEContext& ctx);                              // [unpack an after-effect pack]
void sub_1EEB90(EEContext& ctx);                              // [create an after effect]
void sub_1EF340(EEContext& ctx);                              // [destroy a model's after effects]
void sub_320230(EEContext& ctx);                              // [new list head]
void sub_320290(EEContext& ctx);                              // [free an image-sequence list]
void sub_320880(EEContext& ctx);                              // [read an image-sequence chunk]
void sub_320FB0(EEContext& ctx);                              // [new tagged-material record]
void sub_321010(EEContext& ctx);                              // [release a record]
void effMng_CreateEffectProgramTasks(EEContext& ctx);         // [start the effect manager]
void sub_322530(EEContext& ctx);                              // [new sprite player]
void sub_3225D0(EEContext& ctx);                              // [clone a sprite player]
void sub_322660(EEContext& ctx);                              // [free a sprite player]
void sub_322880(EEContext& ctx);                              // [build a sprite set]
void sub_322A20(EEContext& ctx);                              // [release a sprite set]
void sub_322DC0(EEContext& ctx);                              // [build an image sequence]
void sub_322F20(EEContext& ctx);                              // [release an image sequence]
void sub_3230F0(EEContext& ctx);                              // [effect mesh object]
void sub_3234F0(EEContext& ctx);                              // [effect model object]
void sub_3237C0(EEContext& ctx);                              // [destroy an effect mesh object]
void sub_323C20(EEContext& ctx);                              // [effect mesh object, a material per band]
void effAfter_CreateAfterEffectRenderTask(EEContext& ctx);    // [start the after effects]

}  // namespace p3fes::game
