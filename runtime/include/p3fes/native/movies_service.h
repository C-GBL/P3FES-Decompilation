// Modernize pass, layer 4: movies (docs/MODERNIZE_PLAN.md §3 "4. Movies", ADR-0017; runtime/ipu/README.md
// "Native movies").
//
// The seam between the game's movie player and the host. The movie task's player (the Sofdec handle at 0x7CDF10)
// decodes its video through CRI's SFD video decoder; on the PS2 that decoder's "sceMpeg path" (libs13.cpp
// 0x5941A8-0x595718) feeds the video elementary stream into a ring of 2 KiB sectors that a DMA source chain (DMAC
// channel 4) streams into the IPU, and decodes each picture with Sony's libmpeg (sceMpegGetPicture), which drives
// the IPU command by command. With `--native movies` the host installs a MoviesService in `g_service`, and the
// player's own glue swaps at the calls it makes into that platform pair:
//   sub_594B88 (SFD init)            no sceMpegInit (no sceIpuInit: the IPU is never touched)
//   sub_594C38 (video work set-up)   mpeg_create instead of sceMpegCreate + its four callbacks
//   sub_5941A8 (ring reset)          ring_reset instead of the DMA tag chain and the D4 registers
//   sub_5944A8 (ring flush)          the passed sectors / the newly written whole sectors as the DMA's, from the
//                                    native read position (ring_cursor) instead of D4_MADR
//   sub_5946A8 / sub_5947A8          the DMA stop / restart around a picture: only the running flag and the
//                                    restart's sector rule (no D4 / D3 / IPU registers)
//   sub_594AC0 (ring destroy)        ring_close, no D4 registers
//   sub_595060 (release)             mpeg_reset / mpeg_delete instead of sceMpegReset / sceMpegDelete
//   sub_595390 (decode a picture)    mpeg_plan + mpeg_decode instead of sceMpegGetPicture / RAW8, and CRI's
//                                    starvation callback's end path (sub_594F68) when the picture needs more than
//                                    the queued sectors
// The decoder is runtime/native/movies (mpeg_video.h): libmpeg's picture loop on the host, with the IPU core's
// (runtime/ipu) block decode, IDCT and colour conversion called directly. The ring record keeps the faithful
// layout and accounting, so every other SFD function (the feed, the free-space query, the start-code counter, the
// frame pool, the time codes) runs its faithful body. The movie's audio is not this layer's: it is an ADX stream
// inside the .SFD that CRI's own ADX player decodes on the EE and plays through PS2RNA (layer 3: `--native sound`).
// With `g_service == nullptr` (the default) every one of them runs its faithful body.
#pragma once

#include "p3fes/ee_types.h"

namespace p3fes::native::movies {

// The SFD video work (handle + 8128 -> work) and its sceMpeg-path records (libs13.h vdec:: / vibuf::).
inline constexpr s32 kWorkIpu = 4392;       // s32: decode through sceMpeg
inline constexpr s32 kWorkInDecode = 4412;  // s32: 1 while a picture call runs (the starvation callback's test)
inline constexpr s32 kWorkAbort = 4416;     // s32: the end code was fed (the callback's abort mode); the call -> -3
inline constexpr s32 kWorkMpeg = 4432;      // the 72-byte sceMpeg record
inline constexpr s32 kWorkViBuf = 4504;     // the video-input ring
inline constexpr u32 kSectorBytes = 2048;

// What the next picture call reads (MpegDecoder::plan): `needed` bytes from the read position.
struct MoviePlan {
    enum Kind : u8 { Shown, End, NeedData } kind = NeedData;
    u64 needed = 0;
};

struct MovieDecode {
    enum Kind : u8 { Shown, End, Error } kind = End;
    u32 width = 0, height = 0;   // the sequence's
    u32 decoded = 0, shown = 0;  // pictures so far
    u32 type = 0, tref = 0;      // the shown picture's type (1 I, 2 P, 3 B) and temporal reference
    u64 bits = 0;                // bits the call consumed
    // The guest cycles the faithful call (libmpeg on the EE + the IPU + its DMA) takes for the same work, modelled:
    // the caller charges them (with check points) so the movie's timing -- when its player is ready, how far it
    // decodes ahead -- stays the faithful one (native_movies.cpp kCost*).
    u64 cycles = 0;
};

class MoviesService {
public:
    virtual ~MoviesService() = default;

    // ---- the video-input ring at guest address `vibuf` (viBufCreate's record) -------------------------------------
    // ring_reset: the ring starts over (sub_5941A8): read position 0, nothing queued. ring_close: it is destroyed.
    virtual void ring_reset(u64 cycles, u32 vibuf) = 0;
    virtual void ring_close(u64 cycles, u32 vibuf) = 0;
    // The decoder's read position in bits since the ring's reset (absolute: the ring offset is it mod the size),
    // and the end of the queued sectors in bytes since the reset (what the DMA chain covers; flushes extend it).
    virtual u64 ring_cursor(u32 vibuf) const = 0;
    virtual u64 ring_queue_end(u32 vibuf) const = 0;
    virtual void ring_set_queue_end(u32 vibuf, u64 end) = 0;

    // ---- the decoder of the sceMpeg record at guest address `mpeg`, reading the ring `vibuf` ------------------------
    virtual void mpeg_create(u64 cycles, u32 mpeg, u32 vibuf) = 0;
    virtual void mpeg_reset(u64 cycles, u32 mpeg) = 0;
    virtual void mpeg_delete(u64 cycles, u32 mpeg) = 0;
    // `ring` / `ring_size`: the ring's bytes (host view of guest RAM); `avail` bytes from the read position may be
    // read (wrapping at the ring's end).
    virtual MoviePlan mpeg_plan(u32 mpeg, const u8* ring, u32 ring_size, u64 avail) = 0;
    // Decodes up to the next shown picture into `out` (RGB32 macroblocks when `rgb32`, else RAW8; column-major) and
    // moves the read position. `cycles` / `vblank`: the call's time (statistics, the movie log).
    virtual MovieDecode mpeg_decode(u64 cycles, u32 mpeg, const u8* ring, u32 ring_size, u64 avail, bool rgb32, u8* out,
                                    u32 out_size) = 0;
};

// Installed by the host (GameHost) while `--native movies` is on; nullptr = the faithful path.
inline MoviesService* g_service = nullptr;
inline MoviesService* service() noexcept { return g_service; }

// The movie log (`--movie-log FILE`, both modes): told after every picture call of the sceMpeg path (sub_595390)
// with the video work, the frame buffer, its format and the call's result. It only reads guest memory.
class MovieLogSink {
public:
    virtual ~MovieLogSink() = default;
    virtual void picture_call(u64 cycles_start, u64 cycles_end, u32 work, u32 out, u32 format, s32 result) = 0;
};
inline MovieLogSink* g_log = nullptr;

}  // namespace p3fes::native::movies
