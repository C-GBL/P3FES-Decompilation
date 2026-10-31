// Modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "4. Movies", ADR-0017): the native branches of CRI's SFD video
// decoder on its "sceMpeg path" (p3fes/native/movies_service.h), taken only while the host has installed a native
// movie service (`--native movies`). Called from the faithful bodies, which then return or skip the replaced call:
//   sub_5941A8 ring reset (sweep5c.cpp)         sfd_native_ring_reset            (at the top)
//   sub_5944A8 ring flush (sweep5b.cpp)         sfd_native_ring_flush            (at the top)
//   sub_5946A8 DMA stop (sweep5b.cpp)           sfd_native_ring_stop             (at the top)
//   sub_5947A8 DMA restart (sweep5b.cpp)        sfd_native_ring_restart          (at the top)
//   sub_594AC0 ring destroy (sweep5c.cpp)       sfd_native_ring_destroy          (at the top)
//   sub_594B88 SFD init (libs13.cpp)            no sceMpegInit
//   sub_594C38 video set-up (libs13.cpp)        sfd_native_mpeg_create instead of sceMpegCreate + callbacks
//   sub_595060 release (libs13.cpp)             mpeg_reset / mpeg_delete instead of sceMpegReset / sceMpegDelete
//   sub_595390 decode (libs13.cpp)              sfd_native_get_picture instead of sceMpegGetPicture / RAW8
// The ring record (viBufCreate's, video work + 4504) keeps the faithful layout and accounting; what differs from a
// faithful run is the layer's own state: the DMA tags and the saved D4 / D3 / IPU registers (+28..+60) that are never
// written, libmpeg's work area and decoder state (the native decoder holds the references), and the timing of the
// decode (tools/ours/modernize/layer4_movies_mask.txt).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_types.h"
#include "p3fes/native/movies_service.h"

namespace p3fes::game {

namespace movies_native {
// The video-input ring record (libs13.h vibuf::).
constexpr s32 kRingBase = 0, kRingTags = 4, kRingSectors = 8, kRingHead = 12, kRingQueued = 16, kRingCount = 20,
              kRingBytes = 24, kRingSema = 64, kRingRunning = 68, kRingTotal = 72, kRingEntries = 80,
              kRingEntryCount = 84;
constexpr u32 kEndCode = 0x7CA0E8u;      // the 16-byte sequence-end block the starvation callback feeds
constexpr u32 kPrefetchBytes = 160;      // the IPU input FIFO + bit-stream buffer (10 qwords) the DMA runs ahead by
}  // namespace movies_native

void sfd_native_ring_reset(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf);
u32 sfd_native_ring_flush(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf);
void sfd_native_ring_stop(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf);
void sfd_native_ring_restart(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf);
void sfd_native_ring_destroy(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf);
// sub_594C38's sceMpegCreate + four callbacks: the 72-byte record cleared, the native decoder made.
void sfd_native_mpeg_create(EEContext& ctx, native::movies::MoviesService& s, u32 work);
// sub_595390's picture call between its DMA restart and stop: `work` the video work, `frame` the frame record
// (+32 = its buffer), `handle` the SFD handle (+56 = the output format, 2 = RGB32).
// Returns the guest cycles the faithful call would have taken (MovieDecode::cycles), which the caller charges.
u64 sfd_native_get_picture(EEContext& ctx, native::movies::MoviesService& s, u32 work, u32 frame, u32 handle);

}  // namespace p3fes::game
