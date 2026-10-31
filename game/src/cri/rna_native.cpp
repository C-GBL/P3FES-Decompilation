// Modernize layer 3 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of CRI's PS2RNA
// (game/include/p3fes/game/sound_native.h). Reached only while p3fes::native::sound::service() is set
// (`--native sound`).
//
// The records keep the faithful layout (PS2RNA_Create's stores, the setters' fields, the command builder's old / new
// pairs), so every unhooked PS2RNA function -- the setters and getters ADXT calls, GetTime -- runs its faithful body.
// What is not made, on purpose: the per-channel PSJ (an EE SJUNI accounting for 16 KiB of IOP RAM plus a remote SJUNI
// on the IOP), the DTR (SIF DMA EE -> IOP), the IOP RNA object (urpc 8 / 9), the SJX / DTX ports and their IOP
// heap blocks (PS2RNA_Init), the IOP sound init / finish (urpc 12 / 13).
#include "p3fes/game/sound_native.h"

#include <cstring>
#include <vector>

#include "p3fes/ee_memory.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_55FC00_0055fc00(p3fes::EEContext&);
void fn_sub_561728_00561728(p3fes::EEContext&);
void fn_sub_561740_00561740(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
namespace gen = ::p3fes::recomp_gen;
using native::sound::kRnaBufBytes;
using native::sound::kRnaCount;
using native::sound::kRnaSize;
using native::sound::kRnaTable;

constexpr u32 kRefCount = 0x7A943Cu;  // PS2RNA_Init's reference count
constexpr u32 kIopCore = 0x7A9438u;   // the IOP's urpc-12 reply (the output core)
constexpr u32 kPauseAll = 0x7A9424u;  // new / old (0x7A9428)
constexpr u32 kPcmTrans = 0x7A9430u;  // the PCM-transfer flags per core

// The SJ vtable (cri1.h "the stream joints"): +24 get chunk, +28 unget, +32 put, +36 number of bytes on a line.
constexpr s32 kSjGet = 24, kSjUnget = 28, kSjPut = 32, kSjNum = 36;

u32 rd32(EEContext& ctx, u32 a) { return ctx.memory->read<u32>(a); }
void wr32(EEContext& ctx, u32 a, u32 v) { ctx.memory->write<u32>(a, v); }
void wr8(EEContext& ctx, u32 a, u8 v) { ctx.memory->write<u8>(a, v); }
s8 rd8s(EEContext& ctx, u32 a) { return static_cast<s8>(ctx.memory->read<u8>(a)); }

// A call through an SJ's vtable with up to three arguments after the handle; returns $v0. `pc` is the faithful call
// site whose link is set (the callee only stores it).
u32 sj_call(EEContext& ctx, u32 pc, u32 sj, s32 slot, u32 a1v, u32 a2v, u32 a3v = 0) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    const u32 fn = rd32(ctx, rd32(ctx, sj) + static_cast<u32>(slot));
    a0 = sj;
    a1 = a1v;
    a2 = a2v;
    a3 = a3v;
    jalr(ctx, pc, fn);
    return v0.u();
}
}  // namespace

void ps2rna_native_init(EEContext& ctx, native::sound::SoundService& s) {
    // PS2RNA_Init's first reference: PS2RNA_InitIopSnd's EE side with the IOP's answer (core 0: urpc 12 replies the
    // core the PSM output runs on, 0 for this game, 16 §1.2), then the output opens; every reference counts. No IOP
    // heap block is taken (the faithful init takes four: the SJX and RNA DTX buffers, the PSJ buffers, the PSM work),
    // so the IOP addresses later allocations get (the SK banks' in sSndcomWork 0x833710) start lower: the layer mask's
    // "IOP identity" class.
    const u32 refs = rd32(ctx, kRefCount);
    if (refs == 0) {
        wr32(ctx, kIopCore, 0);
        wr32(ctx, kPauseAll, 0);
        wr32(ctx, kPauseAll + 4, 0);
        wr32(ctx, kPcmTrans, 1);
        wr32(ctx, kPcmTrans + 4, 0);
        s.rna_open(ctx.cycles);
    }
    wr32(ctx, kRefCount, refs + 1);
}

void ps2rna_native_finish(EEContext& ctx, native::sound::SoundService& s) {
    const s32 refs = static_cast<s32>(rd32(ctx, kRefCount));
    if (refs <= 0) return;
    wr32(ctx, kRefCount, static_cast<u32>(refs - 1));
    if (refs == 1) {
        wr32(ctx, kPcmTrans, 0);  // FinishIopSnd clears both transfer flags
        wr32(ctx, kPcmTrans + 4, 0);
        s.rna_close(ctx.cycles);
    }
}

u32 ps2rna_native_create(EEContext& ctx, native::sound::SoundService& s, u32 sjs, u32 nch) {
    u32 rec = 0;
    for (u32 i = 0; i < kRnaCount && rec == 0; ++i)
        if (ctx.memory->read<u8>(kRnaTable + kRnaSize * i) == 0) rec = kRnaTable + kRnaSize * i;
    if (rec == 0) return 0;
    for (u32 o = 0; o < kRnaSize; o += 4) wr32(ctx, rec + o, 0);
    wr32(ctx, rec + 4, nch);
    const u32 n = nch > 2 ? 2u : nch;
    for (u32 c = 0; c < n; ++c) wr32(ctx, rec + 24 + 4 * c, rd32(ctx, sjs + 4 * c));
    wr32(ctx, rec + 32, rec);  // the IOP object's handle: the native side keys the commands by the record itself
    // the state bytes as PS2RNA_Create stores them (0x560A04..0x560AC8)
    wr8(ctx, rec + 82, static_cast<u8>(nch));
    wr8(ctx, rec + 83, static_cast<u8>(nch));
    const u8 core = ctx.memory->read<u8>(kIopCore);
    wr8(ctx, rec + 86, core);
    wr8(ctx, rec + 87, core);
    wr8(ctx, rec + 89, 1);
    const u32 sj0 = rd32(ctx, sjs);
    const u32 total = sj_call(ctx, 0x560A98u, sj0, kSjNum, 1, 0) + sj_call(ctx, 0x560AB0u, sj0, kSjNum, 0, 0);
    wr32(ctx, rec + 40, total);
    wr32(ctx, rec + 44, kRnaBufBytes);
    wr8(ctx, rec, 1);
    s.rna_create(ctx.cycles, rec, nch);
    return rec;
}

void ps2rna_native_destroy(EEContext& ctx, native::sound::SoundService& s, u32 rna) {
    s.rna_destroy(ctx.cycles, rna);
    wr8(ctx, rna, 0);
}

namespace {
// DTR's completion of the transfer started in the previous server call: the bytes go into the next block and the
// chunk onto the joint's free line (vtable +32, line 0). `ck` is guest scratch for the chunk.
void dma_complete(EEContext& ctx, native::sound::SoundService& s, u32 rec, u32 c, u32 sj, u32 ck,
                  std::vector<s16>& pcm) {
    u32 data = 0, len = 0;
    if (!s.rna_dma_pending(rec, c, data, len)) return;
    pcm.resize(len / 2);
    if (const u8* p = ctx.memory->ram_ptr(data, len)) {
        std::memcpy(pcm.data(), p, len & ~1u);
    } else {
        for (u32 k = 0; k < len / 2; ++k) pcm[k] = static_cast<s16>(ctx.memory->read<u16>(data + 2 * k));
    }
    s.rna_dma_done(ctx.cycles, rec, c, pcm);
    wr32(ctx, ck, data);
    wr32(ctx, ck + 4, len);
    (void)sj_call(ctx, 0x558E20u, sj, kSjPut, 0, ck);
}
}  // namespace

void ps2rna_native_transfer(EEContext& ctx, native::sound::SoundService& s, u32 rna, u32 sw) {
    using namespace hg;
    Gpr sp{ctx, 29};
    // sub_560C88: +88 = sw; any value but 1 stops the channels' DTRs (DTR_Stop completes a transfer under way;
    // +89 = 1, +88 = 0 per channel).
    wr8(ctx, rna + 88, static_cast<u8>(sw));
    const s8 nch = rd8s(ctx, rna + 82);
    if (sw != 1 && nch > 0) {
        sp = addiu(sp, -0x10);
        std::vector<s16> pcm;
        for (u32 c = 0; c < static_cast<u32>(nch) && c < 2; ++c) {
            const u32 sj = rd32(ctx, rna + 24 + 4 * c);
            if (sj != 0) dma_complete(ctx, s, rna, c, sj, sp.u(), pcm);
        }
        sp = addiu(sp, 0x10);
        wr8(ctx, rna + 89, 1);
        wr8(ctx, rna + 88, 0);
    }
    s.rna_transfer(ctx.cycles, rna, sw == 1);
}

u32 ps2rna_native_num_data(EEContext& /*ctx*/, native::sound::SoundService& s, u32 rna) {
    return s.rna_inflight_bytes(rna, 0) / 2;
}

u32 ps2rna_native_num_room(EEContext& /*ctx*/, native::sound::SoundService& s, u32 rna) {
    return (kRnaBufBytes - s.rna_inflight_bytes(rna, 0)) / 2;
}

void ps2rna_native_exec_server(EEContext& ctx, native::sound::SoundService& s) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29};
    // 1. the per-handle step (sub_560F78 under the nesting count): with the transfer asked on, the DTR restarts once
    //    every channel's buffer is wholly free again, and +91 (the discard switch) is cleared
    jal(ctx, 0x56116Cu, gen::fn_sub_561728_00561728);
    for (u32 i = 0; i < kRnaCount; ++i) {
        const u32 rec = kRnaTable + kRnaSize * i;
        if (rd8s(ctx, rec) != 1 || rd8s(ctx, rec + 88) != 1) continue;
        if (s.rna_try_restart(ctx.cycles, rec)) wr8(ctx, rec + 91, 0);
    }
    jal(ctx, 0x5611A0u, gen::fn_sub_561740_00561740);
    // 2. DTR_ExecServer's work per running channel: complete the transfer started last time, then start the next one
    //    -- the joint's data chunk (line 1) up to the buffer's head free chunk, in 64-byte units, the rest put back (SJ_SplitChunk,
    //    unget); no SIF DMA: the bytes are read when it completes
    sp = addiu(sp, -0x40);
    const u32 ck = sp.u(), ck1 = ck + 0x10, ck2 = ck + 0x18;
    std::vector<s16> pcm;
    for (u32 i = 0; i < kRnaCount; ++i) {
        const u32 rec = kRnaTable + kRnaSize * i;
        if (rd8s(ctx, rec) != 1 || !s.rna_transfer_running(rec)) continue;
        const u32 nch = rd32(ctx, rec + 4) > 2 ? 2u : rd32(ctx, rec + 4);
        for (u32 c = 0; c < nch; ++c) {
            const u32 sj = rd32(ctx, rec + 24 + 4 * c);
            if (sj == 0) continue;
            dma_complete(ctx, s, rec, c, sj, ck, pcm);
            const u32 room = s.rna_dma_room(rec, c);  // the head free chunk of the buffer
            if (room < 64) continue;
            (void)sj_call(ctx, 0x558EBCu, sj, kSjGet, 1, room, ck);
            const u32 data = rd32(ctx, ck), len = rd32(ctx, ck + 4);
            if (len == 0) continue;
            const u32 n = len & ~63u;
            if (n < len) {  // the remainder goes back on the data line (all of it when under 64 bytes)
                a0 = ck;
                a1 = n;
                a2 = ck1;
                a3 = ck2;
                jal(ctx, 0x558F20u, gen::fn_sub_563C28_00563c28);
                (void)sj_call(ctx, 0x558F38u, sj, kSjUnget, 1, ck2);
            }
            if (n != 0) s.rna_dma_start(ctx.cycles, rec, c, data, n);
        }
    }
    sp = addiu(sp, 0x40);
    // 3. the exchange (SJX / DTX's turn): accept the output's answer; when no block is in flight, CRI's own command
    //    builder (the RNA DTX port's send callback) writes its commands into that port's EE buffer and they go out
    //    with the PCM moved in since the last block
    if (s.rna_exchange(ctx.cycles)) {
        a0 = 0;
        a1 = native::sound::kRnaCmdBuf;
        jal(ctx, 0x5611A8u, gen::fn_sub_55FC00_0055fc00);
        const u32 count = rd32(ctx, native::sound::kRnaCmdBuf);
        for (u32 i = 0; i < count && i < native::sound::kRnaCmdMax; ++i) {
            const u32 e = native::sound::kRnaCmdBuf + 16 + 16 * i;
            native::sound::RnaCommand c;
            c.cmd = static_cast<s16>(ctx.memory->read<u16>(e));
            c.rna = rd32(ctx, e + 4);
            c.v8 = rd32(ctx, e + 8);
            c.v12 = rd32(ctx, e + 12);
            s.rna_command(ctx.cycles, c);
        }
        s.rna_send(ctx.cycles);
    }
}

}  // namespace p3fes::game
