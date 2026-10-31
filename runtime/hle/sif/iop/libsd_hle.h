// libsd HLE: the SPU2 register driver the SK stack and SDRDRV import (26 functions, docs/ANALYSIS/19
// §2.1), over the host voice model (p3fes/audio/spu2_voice.h, ADR-0014 milestone 2) -- SetParam / SetSwitch /
// SetAddr / SetCoreAttr become voice and core state, KON/KOFF start and release voices, ENDX/ENVX/NAX read
// the live model, VoiceTrans/BlockTrans copy bank bytes into the model's 2 MiB of voice RAM, ProcBatch walks
// the 8-byte records. What the model does not implement (effect attributes, PMON/NON/VMIX switches, ESA/EEA,
// transfer callbacks) is stored and read back.
//
// Entry encodings are libsd's public ones (ps2sdk @ 329e2bb common/include/libsd-common.h, AFL-2.0,
// names/values only): entry = core | voice << 1 | code << 8 for voice params/switches/addresses, code << 8 |
// 0x80 | core for core-wide params (MVOLL 0x980, MVOLR 0xA80 ... as the game's SetParam calls show).
// Return values follow libsd.h's documented API (VoiceTrans returns the size, Get* the stored value);
// what the SPU2 itself would answer (transfer status) is inf and noted per function.
#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <map>
#include <span>
#include <string>
#include <vector>

#include "iop_core.h"
#include "p3fes/audio/spu2_voice.h"

namespace p3fes::hle::sif::iop {

class R3000;

inline constexpr u32 kSpuRamSize = audio::kSpuRamBytes;

class LibsdHle {
public:
    LibsdHle();

    // ---- the libsd API (ordinals as in libsd.h) -----------------------------------------------------
    s32 init(u32 flag);                                              // 4
    void set_param(u32 entry, u32 value);                            // 5
    u32 get_param(u32 entry) const;                                  // 6
    void set_switch(u32 entry, u32 value);                           // 7
    u32 get_switch(u32 entry) const;                                 // 8
    void set_addr(u32 entry, u32 value);                             // 9
    u32 get_addr(u32 entry) const;                                   // 10
    void set_core_attr(u32 entry, u32 value);                        // 11
    u32 get_core_attr(u32 entry) const;                              // 12
    u32 note_to_pitch(u32 center_note, u32 center_fine, u32 note, u32 fine) const;  // 13
    u32 pitch_to_note(u32 center_note, u32 center_fine, u32 pitch) const;           // 14
    // 17/18/19/20: transfers between IOP RAM and SPU RAM (byte addresses, byte sizes).
    s32 voice_trans(u32 channel, u32 mode, const detail::IopRam& iop, u32 iop_addr, u32 spu_addr, u32 size, detail::IopRam* iop_out);
    s32 block_trans(u32 channel, u32 mode, const detail::IopRam& iop, u32 iop_addr, u32 size, u32 start_addr, detail::IopRam* iop_out);
    u32 voice_trans_status(u32 channel, u32 flag) const;             // 19
    u32 block_trans_status(u32 channel, u32 flag) const;             // 20
    s32 set_effect_attr(u32 core, std::span<const u8> attr);         // 23: 32-byte sceSdEffectAttr
    void get_effect_attr(u32 core, std::span<u8> attr) const;        // 24
    s32 clear_effect_work_area(u32 core, u32 channel, u32 mode);     // 25
    // 15/16 ProcBatch/ProcBatchEx are executed by the kernel glue over the batch records in IOP RAM.

    // ---- the voice model ----------------------------------------------------------------------------
    audio::Spu2Voices& voices() { return voices_; }
    const audio::Spu2Voices& voices() const { return voices_; }
    // Every voice the model keys (one call per KON bit, with the voice's registers as keyed).
    std::function<void(const audio::Spu2KeyOn&)> on_key_on;
    std::function<void(u32 core, u32 voice)> on_key_off;
    // Every core-level write that changes a value (the volume law / effect evidence, --sound-log "CORE"
    // lines): kind 1 = core parameter (MMIX/MVOL/EVOL/AVOL/BVOL by sd_code), 2 = switch register (PMON/NON/
    // VMIX* by sd_code; KON/KOFF/ENDX are not reported here), 3 = core attribute (libsd SD_CORE_* code),
    // 4 = effect attribute field (0 mode, 1 depth_L, 2 depth_R, 3 delay, 4 feedback), 5 = sceSdInit(flag).
    std::function<void(u32 core, u32 kind, u32 code, u32 value, u32 old)> on_core_write;

    // ---- inspection ---------------------------------------------------------------------------------
    std::span<const u8> spu_ram() const { return voices_.ram(); }
    u64 voice_trans_bytes() const { return voice_trans_bytes_; }
    u64 block_trans_bytes() const { return block_trans_bytes_; }
    struct Transfer {
        u32 channel = 0, mode = 0, iop = 0, spu = 0, size = 0;
    };
    const std::vector<Transfer>& transfers() const { return transfers_; }
    u32 core_attr(u32 core, u32 attr) const;
    std::size_t param_writes() const { return param_writes_; }
    u64 key_ons() const { return voices_.key_ons(); }
    u64 key_offs() const { return voices_.key_offs(); }
    u32 init_calls() const { return init_calls_; }
    // The effect attributes as last set (sceSdEffectAttr fields; mode 0 until SetEffectAttr).
    struct EffectAttr {
        s32 mode = 0, depth_l = 0, depth_r = 0, delay = 0, feedback = 0;
    };
    EffectAttr effect_attr(u32 core) const;

    void state(StateIo& io);  // machine state (iop_state.cpp): the voice model + the register shadows

private:
    audio::Spu2Voices voices_;
    std::map<u32, u32> params_;    // entries the model has no register for
    std::map<u32, u32> addrs_;
    std::array<std::array<u8, 32>, 2> effect_attr_{};
    std::array<u32, 2> trans_addr_{};
    std::vector<Transfer> transfers_;
    u64 voice_trans_bytes_ = 0, block_trans_bytes_ = 0;
    std::size_t param_writes_ = 0;
    u32 init_calls_ = 0;

    void note_core_write(u32 core, u32 kind, u32 code, u32 value, u32 old) const {
        if (on_core_write && value != old) on_core_write(core, kind, code, value, old);
    }
};

// libsd ordinal ordinal with the call's arguments a0..a3 + the first stack word: what the import returns in v0.
// The interpreted modules reach it through install_libsd_calls, the native SK stack (runtime/native/sound/sk) directly.
u32 libsd_call(LibsdHle& sd, detail::IopRam& iop, u32 ordinal, const u32 (&args)[5]);

// Registers the libsd ordinals 2..33 as host calls on `cpu` (the import binder resolves "libsd" to
// them). `iop` is the RAM the transfer addresses refer to.
void install_libsd_calls(R3000& cpu, LibsdHle& sd, detail::IopRam& iop,
                         std::map<std::pair<std::string, u16>, u32>& table);

}  // namespace p3fes::hle::sif::iop
