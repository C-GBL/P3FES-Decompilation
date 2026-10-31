// Modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "4. Movies", ADR-0017): the native branches of CRI's SFD video
// decoder, sceMpeg path (game/include/p3fes/game/movies_native.h). Reached only while p3fes::native::movies::service()
// is set (`--native movies`).
//
// The ring (viBufCreate's record) is a 256-sector ring of the video elementary stream. On the PS2 the DMAC streams
// its queued sectors (+16 from the head sector +12) into the IPU; whole sectors written since (the byte count +20)
// are added to the chain by the flush (sub_5944A8), which also frees the sectors the DMA has passed (D4_MADR's sector).
// Natively the "DMA position" is the decoder's read position (ring_cursor) plus the 10 qwords the DMA would have run
// ahead into the IPU's FIFOs, never past the queued end; the record's fields then evolve by the faithful arithmetic,
// so the feed (sub_594EC8 and its free-space query sub_5942E8) and every other SFD function run their faithful bodies.
#include "p3fes/game/movies_native.h"

#include <algorithm>
#include <cstring>

#include "p3fes/ee_memory.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn_sub_594EC8_00594ec8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
namespace gen = ::p3fes::recomp_gen;
using namespace movies_native;
using native::movies::kSectorBytes;

u32 rd32(EEContext& ctx, u32 a) { return ctx.memory->read<u32>(a); }
void wr32(EEContext& ctx, u32 a, u32 v) { ctx.memory->write<u32>(a, v); }

void sema(EEContext& ctx, u32 pc, u32 vibuf, bool wait) {
    using namespace hg;
    Gpr a0{ctx, 4};
    a0 = rd32(ctx, vibuf + kRingSema);
    jal(ctx, pc, wait ? gen::fn__sceWaitSema_005031a0 : gen::fn__sceSignalSema_00503180);
}

// The flush's arithmetic (sub_5944A8 0x594500-0x59464C) with the DMA position `dma` (bytes since the ring's reset).
void flush_at(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf, u64 dma) {
    const u32 sectors = rd32(ctx, vibuf + kRingSectors);
    if (sectors == 0) return;
    const u32 head = rd32(ctx, vibuf + kRingHead);
    const s32 queued = static_cast<s32>(rd32(ctx, vibuf + kRingQueued));
    const s32 count = static_cast<s32>(rd32(ctx, vibuf + kRingCount));
    const u32 cur = static_cast<u32>((dma / kSectorBytes) % sectors);  // sub_593FE8: the sector of D4_MADR
    const u32 consumed = (cur + sectors - head) % sectors;
    wr32(ctx, vibuf + kRingQueued, static_cast<u32>(queued - static_cast<s32>(consumed)));
    wr32(ctx, vibuf + kRingHead, (head + consumed) % sectors);
    const s32 n = count / static_cast<s32>(kSectorBytes);  // whole sectors written since: into the chain
    wr32(ctx, vibuf + kRingCount, static_cast<u32>(count - n * static_cast<s32>(kSectorBytes)));
    if (n > 0) {
        wr32(ctx, vibuf + kRingQueued, rd32(ctx, vibuf + kRingQueued) + static_cast<u32>(n));
        s.ring_set_queue_end(vibuf, s.ring_queue_end(vibuf) + u64{static_cast<u32>(n)} * kSectorBytes);
    }
}

u64 dma_position(const native::movies::MoviesService& s, u32 vibuf) {
    const u64 q = (s.ring_cursor(vibuf) / 8u) & ~u64{15};  // the qword holding the next bit (the rewind's restart)
    return std::min(q + kPrefetchBytes, s.ring_queue_end(vibuf));
}
}  // namespace

void sfd_native_ring_reset(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf) {
    // sub_5941A8 without the DMA tag chain and the D4 registers
    wr32(ctx, vibuf + kRingRunning, 1);
    for (s32 o : {kRingHead, kRingQueued, kRingCount, 88, 92}) wr32(ctx, vibuf + static_cast<u32>(o), 0);
    const s32 n = static_cast<s32>(rd32(ctx, vibuf + kRingEntryCount));
    u32 e = rd32(ctx, vibuf + kRingEntries);
    for (s32 i = 0; i < n; ++i, e += 24) {
        wr32(ctx, e + 16, 0);
        wr32(ctx, e + 20, 0);
    }
    s.ring_reset(ctx.cycles, vibuf);
    hg::Gpr v0{ctx, 2};
    v0 = 1;
}

u32 sfd_native_ring_flush(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf) {
    sema(ctx, 0x5944D8u, vibuf, true);
    u32 r = 0;
    if (rd32(ctx, vibuf + kRingRunning) != 0) {
        flush_at(ctx, s, vibuf, dma_position(s, vibuf));
        r = 1;
    }
    sema(ctx, 0x59466Cu, vibuf, false);
    hg::Gpr v0{ctx, 2};
    v0 = r;
    return r;
}

void sfd_native_ring_stop(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf) {
    (void)s;
    sema(ctx, 0x5946B8u, vibuf, true);
    wr32(ctx, vibuf + kRingRunning, 0);
    sema(ctx, 0x59478Cu, vibuf, false);
    hg::Gpr v0{ctx, 2};
    v0 = 1;
}

void sfd_native_ring_restart(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf) {
    // sub_5947A8: the transfer restarts at the qword holding the read position; when that lies before the head
    // sector (the DMA had run into the next sector), the head moves back and the sector is queued again.
    sema(ctx, 0x5947D0u, vibuf, true);
    const u32 sectors = rd32(ctx, vibuf + kRingSectors);
    if (sectors) {
        const u64 q = (s.ring_cursor(vibuf) / 8u) & ~u64{15};
        const u32 queued = rd32(ctx, vibuf + kRingQueued);
        const u64 end_sector = s.ring_queue_end(vibuf) / kSectorBytes;
        const u64 head_abs = end_sector >= queued ? end_sector - queued : 0;
        const u64 cur = q / kSectorBytes;
        if (cur < head_abs) {
            wr32(ctx, vibuf + kRingHead, static_cast<u32>(cur % sectors));
            wr32(ctx, vibuf + kRingQueued, queued + static_cast<u32>(head_abs - cur));
        }
    }
    wr32(ctx, vibuf + kRingRunning, 1);
    sema(ctx, 0x594A88u, vibuf, false);
    hg::Gpr v0{ctx, 2};
    v0 = 1;
}

void sfd_native_ring_destroy(EEContext& ctx, native::movies::MoviesService& s, u32 vibuf) {
    using namespace hg;
    s.ring_close(ctx.cycles, vibuf);
    Gpr v0{ctx, 2}, a0{ctx, 4};
    a0 = rd32(ctx, vibuf + kRingSema);
    jal(ctx, 0x594AFCu, gen::fn__sceDeleteSema_00503170);
    v0 = 1;
}

void sfd_native_mpeg_create(EEContext& ctx, native::movies::MoviesService& s, u32 work) {
    const u32 rec = work + static_cast<u32>(native::movies::kWorkMpeg);
    for (u32 o = 0; o < 72; o += 4) wr32(ctx, rec + o, 0);  // sceMpegCreate's memset; no libmpeg work area
    s.mpeg_create(ctx.cycles, rec, work + static_cast<u32>(native::movies::kWorkViBuf));
}

u64 sfd_native_get_picture(EEContext& ctx, native::movies::MoviesService& s, u32 work, u32 frame, u32 handle) {
    using namespace hg;
    namespace nm = native::movies;
    const u32 vibuf = work + static_cast<u32>(nm::kWorkViBuf), rec = work + static_cast<u32>(nm::kWorkMpeg);
    const u32 base = rd32(ctx, vibuf + kRingBase), size = rd32(ctx, vibuf + kRingBytes);
    const u8* ring = ctx.memory->ram_ptr(base, size);
    auto avail = [&] {
        const u64 c = s.ring_cursor(vibuf) / 8u, e = s.ring_queue_end(vibuf);
        return e > c ? e - c : u64{0};
    };
    if (!ring || size == 0) return 0;
    nm::MoviePlan p = s.mpeg_plan(rec, ring, size, avail());
    if (p.kind == nm::MoviePlan::NeedData || p.needed > avail()) {
        // libmpeg would starve at the end of the queued sectors: CRI's callback (sub_594F68), in decode (+4412 = 1)
        if (rd32(ctx, work + static_cast<u32>(nm::kWorkAbort)) == 1) return 0;  // abort mode: no picture (-1)
        flush_at(ctx, s, vibuf, s.ring_queue_end(vibuf));  // the DMA stands at the chain's end
        if (rd32(ctx, vibuf + kRingQueued) == 0) {
            wr32(ctx, work + static_cast<u32>(nm::kWorkAbort), 1);
            Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
            a0 = vibuf;
            a1 = kEndCode;
            a2 = 16;
            jal(ctx, 0x594FD8u, gen::fn_sub_594EC8_00594ec8);  // the end code after the written data
            wr32(ctx, vibuf + kRingCount, rd32(ctx, vibuf + kRingBytes));
            flush_at(ctx, s, vibuf, s.ring_queue_end(vibuf));
        }
    }
    const bool rgb32 = rd32(ctx, handle + 56) == 2;
    const s32 w = static_cast<s32>(rd32(ctx, work + 12)), h = static_cast<s32>(rd32(ctx, work + 16));
    const u32 mbs = static_cast<u32>(((w + 15) >> 4) * ((h + 15) >> 4));
    const u32 out = rd32(ctx, frame + 32), out_size = mbs * (rgb32 ? 1024u : 384u);
    u8* dst = out_size ? ctx.memory->ram_ptr(out, out_size) : nullptr;
    const u64 a = std::min<u64>(avail(), size);
    const nm::MovieDecode d = s.mpeg_decode(ctx.cycles, rec, ring, size, a, rgb32, dst, dst ? out_size : 0);
    // the public sceMpeg fields libmpeg keeps: width, height, frameCount = the shown picture's number (0-based)
    wr32(ctx, rec + 0, d.width);
    wr32(ctx, rec + 4, d.height);
    if (d.shown) wr32(ctx, rec + 8, d.shown - 1);
    for (u32 o : {16u, 24u, 40u, 48u}) {  // pts, dts, pts2nd, dts2nd: none (no time-stamp callback), as libmpeg's
        wr32(ctx, rec + o, 0xFFFFFFFFu);
        wr32(ctx, rec + o + 4, 0xFFFFFFFFu);
    }
    return d.cycles;
}

}  // namespace p3fes::game
