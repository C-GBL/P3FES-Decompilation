// Modernize pass, layer 3: sound (docs/MODERNIZE_PLAN.md §3, ADR-0017; runtime/audio/README.md "Native sound").
//
// The seam between the game's sound output and the host. With `--native sound` the host installs a SoundService
// (runtime/native/sound/native_sound.h) in `g_service`. Step 1 (ADX: BGM, voices, movie audio, everything CRI's
// ADXT / AHX / AIX / Sofdec players produce) swaps at CRI's PS2 output layer, PS2RNA -- the layer under the ADXRNA
// interface every ADX player writes its decoded PCM into (ADXRNA_Create / SetPlaySw / GetNumData ... -> PS2RNA_*):
//   PS2RNA_Init 0x55FF70        no SJRMT / SJX / DTX, no IOP heap, no urpc 10 / 12: the output opens (rna_open)
//   sub_560698 (Finish)         the last reference closes it (rna_close), no IOP frees, no urpc 13
//   PS2RNA_Create 0x560758      the slot and its fields as the faithful code lays them out, no PSJ / DTR / urpc 8
//   sub_560AF8 (Destroy)        no DTR / urpc 9 / PSJ release
//   sub_560C88 (transfer sw)    no DTR_Stop
//   sub_560EB0 / sub_560F18     GetNumData / GetNumRoom from the native output instead of the PSJ's SJUNI
//   PS2RNA_ExecServer 0x561138  the per-handle restart (sub_560F78's rule), then the PCM moves from each player's
//                               output joints to the native output (DTR_ExecServer's job, no SIF DMA), then the
//                               parameter commands CRI's own builder (ps2rna_sndcbf 0x55FC00) makes go to rna_command
//                               (the IOP's IOPRNA switch) instead of DTX port 1, at the moments DTX would send
// Every other PS2RNA function (the field setters and getters, GetTime) runs its faithful body: they only touch the
// 100-byte EE records, which the native branches keep as the faithful code does. So nothing reaches the IOP: no
// SIF RPC to CRI_ADXI (which the game then does not load either), no DTR SIF DMA, no PSM model. The decode is CRI's
// own EE decoder (game code, no PS2 part), unchanged; the mix law is the IOP PSM's (psm volume tables, linear rate
// conversion), so the PCM the native mixer consumes is the faithful stream PCM sample for sample.
// With `g_service == nullptr` (the default, `--native` without `sound`) every one of them runs its faithful body.
// The game library depends on headers only, so this is an interface plus an inline pointer.
#pragma once

#include <span>
#include <string_view>

#include "p3fes/ee_types.h"

namespace p3fes::native::sound {

// The PS2RNA record table (16 x 100 bytes) and the fields the native branches read or keep.
inline constexpr u32 kRnaTable = 0x7AB850u;
inline constexpr u32 kRnaSize = 100;
inline constexpr u32 kRnaCount = 16;
inline constexpr u32 kRnaBufBytes = 0x4000;  // the IOP buffer per channel (+44): GetNumData / GetNumRoom's 16 KiB
inline constexpr u32 kRnaCmdBuf = 0x7ABEC0u;  // the RNA DTX port's EE buffer, where the command builder writes
inline constexpr u32 kRnaCmdMax = 128;

// One IOPRNA command as CRI's builder emits it (entry {s16 cmd, _, rna, v8, v12}; docs/ANALYSIS/16 §6.1):
// 0 start, 1 stop, 2 play switch, 3 channels, 4 sfreq, 5 volume (0..255, the PSM table's value), 8 discard,
// 9 pan (v8 = channel), 10 route, 11 pause all (rna unused), 12 core, 13 output pan.
struct RnaCommand {
    s16 cmd = 0;
    u32 rna = 0;  // the record's +32 (the native branch stores the record's own address there)
    u32 v8 = 0;
    u32 v12 = 0;
};

class SoundService {
public:
    virtual ~SoundService() = default;

    // ---- ADX output (CRI PS2RNA) -------------------------------------------------------------------------------
    // PS2RNA_Init's first reference / the last Finish: the output starts (the IOP's PSM init on core 0) / stops.
    virtual void rna_open(u64 cycles) = 0;
    virtual void rna_close(u64 cycles) = 0;
    // PS2RNA_Create / Destroy of the record at guest address `rna` with `nch` channels (1..2).
    virtual void rna_create(u64 cycles, u32 rna, u32 nch) = 0;
    virtual void rna_destroy(u64 cycles, u32 rna) = 0;
    // The transfer switch (+88): off stops moving PCM in; on asks for a restart, which happens once every channel's
    // buffer is wholly free again (rna_try_restart, the faithful per-handle step's rule).
    virtual void rna_transfer(u64 cycles, u32 rna, bool on) = 0;
    virtual bool rna_try_restart(u64 cycles, u32 rna) = 0;  // true once, when the restart happens (the caller clears +91)
    virtual bool rna_transfer_running(u32 rna) const = 0;
    // Bytes of channel `ch` handed to the output and not yet given back as played: GetNumData = n / 2, GetNumRoom =
    // (kRnaBufBytes - n) / 2, the room a transfer may fill.
    virtual u32 rna_inflight_bytes(u32 rna, u32 ch) const = 0;
    // The transfer of one chunk of a player's output joint, as DTR's: started in one server call (`len` bytes at
    // guest `data` taken off the joint's data line into the head of the buffer's free space; they count as handed
    // over), completed in the next (the bytes, 16-bit little-endian as the EE wrote them, go into the next block; the
    // caller puts the chunk on the joint's free line). rna_dma_room is the head free chunk (what one transfer may
    // fill: the buffer's free space is kept as the chunk list CRI's SJUNI keeps); rna_dma_pending reports a started
    // transfer.
    virtual u32 rna_dma_room(u32 rna, u32 ch) const = 0;
    virtual void rna_dma_start(u64 cycles, u32 rna, u32 ch, u32 data, u32 len) = 0;
    virtual bool rna_dma_pending(u32 rna, u32 ch, u32& data, u32& len) const = 0;
    virtual void rna_dma_done(u64 cycles, u32 rna, u32 ch, std::span<const s16> pcm) = 0;
    // The output keeps the faithful device's cadence, so the game's timing is the faithful one: what the server
    // hands over (PCM, parameter commands) goes out as one block that the output takes at its next pass (once per
    // vblank, after the vblank-end), and what it played comes back with the answer, which the server accepts at its
    // next call. rna_exchange accepts a waiting answer and says whether a block may go out now (none in flight);
    // then rna_command adds the builder's commands and rna_send closes the block with the PCM moved in since.
    virtual bool rna_exchange(u64 cycles) = 0;
    virtual void rna_command(u64 cycles, const RnaCommand& c) = 0;
    virtual void rna_send(u64 cycles) = 0;

    // ---- the SK sound effects and the libsd remote calls (steps 2 and 3), `--native-sk direct` only -------------
    // The Standard Kit stack (SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN) on native code
    // (runtime/native/sound/sk) instead of on the IOP's R3000 interpreter. By default (`--native-sk sif`) the game keeps
    // its own sceSdRemote RPCs and the IOP model's SDRDRV server hands them to the native stack (its timing is the
    // faithful one; docs/MODERNIZE_PLAN.md "Steps 2 and 3"); with `direct` the game's sound-command layer swaps at two
    // points: kwlnInitPS2Systems 0x197030 (libs24.cpp) hands its SK module loads (and LIBSD.IRX / MODMSIN.IRX) to
    // sk_load_module instead of sceSifLoadModule, and sceSdRemote 0x5129C0 (sweep5a.cpp) -- through which every
    // sceSkSs* wrapper, H_Sndcom_Init's libsd SetParam calls and sceSdRemoteCallbackInit / Quit go -- hands its RPC to
    // SDRDRV (0x80000701) to sd_remote instead of sceSifCallRpc; sceSdRemoteInit 0x512868 (sweep5b.cpp) binds nothing.
    // sk_native() false (the stack is not installed): those keep their faithful path.
    virtual bool sk_native() const { return false; }
    // Loads path (loadfile's NUL-separated rgs): the module id (>= 0), < 0 on failure.
    virtual s32 sk_load_module(u64 cycles, std::string_view path, std::span<const u8> args) {
        (void)cycles, (void)path, (void)args;
        return -1;
    }
    // SDRDRV's function `fno` with `send` (what sceSifCallRpc would send): the reply into `recv`.
    virtual void sd_remote(u64 cycles, u32 fno, std::span<const u8> send, std::span<u8> recv) {
        (void)cycles, (void)fno, (void)send, (void)recv;
    }
};

// Installed by the host (GameHost) while `--native sound` is on; nullptr = the faithful path.
inline SoundService* g_service = nullptr;
inline SoundService* service() noexcept { return g_service; }

}  // namespace p3fes::native::sound
