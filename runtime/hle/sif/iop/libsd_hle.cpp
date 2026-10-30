// libsd HLE (libsd_hle.h): the libsd entry model over the SPU2 voice model.
#include "libsd_hle.h"

#include <cmath>
#include <cstring>

#include "r3000.h"

namespace p3fes::hle::sif::iop {

namespace sd_code = audio::sd_code;
namespace {
inline u32 entry_core(u32 entry) { return entry & 1u; }
inline u32 entry_voice(u32 entry) { return (entry >> 1) & 0x1Fu; }
inline u32 entry_code(u32 entry) { return (entry >> 8) & 0xFFu; }
inline bool entry_is_core_param(u32 entry) { return (entry & 0x80u) != 0; }
inline bool is_voice_param(u32 code) { return code <= sd_code::kVolxr; }
inline bool is_voice_addr(u32 code) { return code >= sd_code::kSsa && code <= sd_code::kNax; }
}  // namespace

LibsdHle::LibsdHle() = default;

s32 LibsdHle::init(u32 flag) {
    // sceSdInit(flag): resets both cores to libsd's register image (Spu2Voices::reset: voices keyed off,
    // VMIX on, MMIX 0xFF0/0xFFC, AVOL1 0x7FFF, BVOL 0; flag bit 0 clear also MVOL 0 / EVOL 0), effects off.
    // libsd returns 0 on success (libsd.h; inf: no failure path modelled). The voice RAM is kept, as the
    // hardware keeps it.
    ++init_calls_;
    voices_.reset(flag);
    params_.clear();
    addrs_.clear();
    for (auto& e : effect_attr_) e.fill(0);
    if (on_core_write) on_core_write(0, 5, 0, flag, ~0u);
    return 0;
}

void LibsdHle::set_param(u32 entry, u32 value) {
    ++param_writes_;
    const u32 code = entry_code(entry);
    if (entry_is_core_param(entry) || !is_voice_param(code)) {
        const u32 core = entry_core(entry);
        const u32 old = voices_.core_param(core, code);
        voices_.set_core_param(core, code, static_cast<u16>(value));
        params_[entry & 0xFFFFu] = value & 0xFFFFu;
        note_core_write(core, 1, code, value & 0xFFFFu, old);
        return;
    }
    voices_.set_voice_param(entry_core(entry), entry_voice(entry), code, static_cast<u16>(value));
}
u32 LibsdHle::get_param(u32 entry) const {
    const u32 code = entry_code(entry);
    if (entry_is_core_param(entry) || !is_voice_param(code)) return voices_.core_param(entry_core(entry), code);
    return voices_.voice_param(entry_core(entry), entry_voice(entry), code);
}

void LibsdHle::set_switch(u32 entry, u32 value) {
    // Switch registers are 24-bit masks per core: entry = core | code << 8.
    const u32 core = entry_core(entry), code = entry_code(entry);
    if (code == sd_code::kKon) {
        for (u32 i = 0; i < audio::kSpuVoicesPerCore; ++i) {
            if (!(value & (1u << i)) || !on_key_on) continue;
            const audio::Spu2Voice& v = voices_.voice(core, i);
            on_key_on(audio::Spu2KeyOn{core, i, v.ssa, v.lsax, v.pitch, v.adsr1, v.adsr2, v.voll, v.volr});
        }
    } else if (code == sd_code::kKoff && on_key_off) {
        for (u32 i = 0; i < audio::kSpuVoicesPerCore; ++i)
            if (value & (1u << i)) on_key_off(core, i);
    }
    const u32 old = voices_.get_switch(core, code);
    voices_.set_switch(core, code, value & 0xFFFFFFu);
    if (code != sd_code::kKon && code != sd_code::kKoff && code != sd_code::kEndx) note_core_write(core, 2, code, value & 0xFFFFFFu, old);
}
u32 LibsdHle::get_switch(u32 entry) const { return voices_.get_switch(entry_core(entry), entry_code(entry)); }

void LibsdHle::set_addr(u32 entry, u32 value) {
    const u32 code = entry_code(entry);
    if (is_voice_addr(code)) voices_.set_voice_addr(entry_core(entry), entry_voice(entry), code, value);
    else voices_.set_core_addr(entry_core(entry), code, value);
    addrs_[entry & 0xFFFFu] = value & 0x1FFFFFu;
}
u32 LibsdHle::get_addr(u32 entry) const {
    const u32 code = entry_code(entry);
    if (is_voice_addr(code)) return voices_.voice_addr(entry_core(entry), entry_voice(entry), code);
    return voices_.core_addr(entry_core(entry), code);
}

void LibsdHle::set_core_attr(u32 entry, u32 value) {
    const u32 core = entry & 1u, attr = (entry >> 1) & 0xFu;
    const u32 old = voices_.core_attr(core, attr);
    voices_.set_core_attr(core, attr, static_cast<u16>(value));
    note_core_write(core, 3, attr, value & 0xFFFFu, old);
}
u32 LibsdHle::get_core_attr(u32 entry) const { return core_attr(entry & 1u, (entry >> 1) & 0xFu); }
u32 LibsdHle::core_attr(u32 core, u32 attr) const { return voices_.core_attr(core & 1u, attr & 0xFu); }

u32 LibsdHle::note_to_pitch(u32 center_note, u32 center_fine, u32 note, u32 fine) const {
    // 0x1000 = the sample's own rate at (center_note, center_fine); one octave doubles (libsd.h names;
    // inf: libsd's table-driven rounding is not reproduced -- revisit against PCSX2 when voices play).
    const double semis = (static_cast<double>(static_cast<int>(note)) - static_cast<double>(static_cast<int>(center_note))) +
                         (static_cast<double>(static_cast<int>(fine)) - static_cast<double>(static_cast<int>(center_fine))) / 128.0;
    const double p = 4096.0 * std::pow(2.0, semis / 12.0);
    if (p <= 0) return 0;
    if (p >= 0x3FFF) return 0x3FFFu;
    return static_cast<u32>(p + 0.5);
}
u32 LibsdHle::pitch_to_note(u32 center_note, u32 center_fine, u32 pitch) const {
    if (pitch == 0) return 0;
    const double semis = 12.0 * std::log2(static_cast<double>(pitch) / 4096.0);
    const double total = static_cast<double>(static_cast<int>(center_note)) * 128.0 + static_cast<double>(static_cast<int>(center_fine)) + semis * 128.0;
    const int t = static_cast<int>(total + 0.5);
    const int n = t / 128, f = t % 128;
    return static_cast<u32>(((n & 0xFF) << 8) | (f & 0xFF));
}

s32 LibsdHle::voice_trans(u32 channel, u32 mode, const detail::IopRam& iop, u32 iop_addr, u32 spu_addr, u32 size, detail::IopRam* iop_out) {
    // sceSdVoiceTrans(channel, mode, iopaddr, spuaddr, size): mode & 1 read (SPU -> IOP) else write; the
    // DMA/IO bit (8) changes nothing here. Returns the size transferred (libsd.h), -1 on a bad range.
    const u32 spu = spu_addr & 0x1FFFFFu;
    auto ram = voices_.ram();
    if (static_cast<u64>(spu) + size > ram.size()) return -1;
    if ((mode & 1u) == 0) {
        const u8* src = iop.at(iop_addr, size);
        if (!src) return -1;
        std::memcpy(ram.data() + spu, src, size);
    } else if (iop_out) {
        u8* dst = iop_out->at(iop_addr, size);
        if (!dst) return -1;
        std::memcpy(dst, ram.data() + spu, size);
    }
    voice_trans_bytes_ += size;
    trans_addr_[channel & 1u] = spu + size;
    transfers_.push_back({channel, mode, iop_addr, spu_addr, size});
    return static_cast<s32>(size);
}

s32 LibsdHle::block_trans(u32 channel, u32 mode, const detail::IopRam& iop, u32 iop_addr, u32 size, u32 start_addr, detail::IopRam* iop_out) {
    // sceSdBlockTrans(channel, mode, iopaddr, size, startaddr): WRITE/WRITE_FROM copy to the core's
    // transfer address (TSA) / startaddr; READ copies out; STOP ends a looping AutoDMA (nothing here).
    const u32 kind = mode & 3u;
    if (kind == 2u) return 0;
    const u32 tsa = kind == 3u ? (start_addr & 0x1FFFFFu) : voices_.core_addr(channel & 1u, sd_code::kTsa);
    auto ram = voices_.ram();
    if (static_cast<u64>(tsa) + size > ram.size()) return -1;
    if (kind == 1u) {
        if (iop_out) {
            u8* dst = iop_out->at(iop_addr, size);
            if (!dst) return -1;
            std::memcpy(dst, ram.data() + tsa, size);
        }
    } else {
        const u8* src = iop.at(iop_addr, size);
        if (!src) return -1;
        std::memcpy(ram.data() + tsa, src, size);
    }
    block_trans_bytes_ += size;
    transfers_.push_back({channel, mode | 0x100u, iop_addr, tsa, size});
    return static_cast<s32>(size);
}

u32 LibsdHle::voice_trans_status(u32 /*channel*/, u32 /*flag*/) const { return 1u; }  // complete at once (inf)
u32 LibsdHle::block_trans_status(u32 channel, u32 /*flag*/) const { return trans_addr_[channel & 1u]; }

s32 LibsdHle::set_effect_attr(u32 core, std::span<const u8> attr) {
    const EffectAttr before = effect_attr(core);
    auto& e = effect_attr_[core & 1u];
    std::memcpy(e.data(), attr.data(), std::min<std::size_t>(attr.size(), e.size()));
    const EffectAttr after = effect_attr(core);
    // libsd (ps2sdk effect.c, AFL-2.0, behaviour only): the depth fields are written to EVOLL/EVOLR of the
    // core; the mode selects a preset of reverb registers and a work area below EEA. The model stores the
    // attributes and mirrors the depths into EVOL so the register image is what the hardware would hold;
    // the reverb itself is not rendered (runtime/audio/README.md "Reverb").
    const u32 old_l = voices_.core_param(core & 1u, sd_code::kEvoll), old_r = voices_.core_param(core & 1u, sd_code::kEvolr);
    voices_.set_core_param(core & 1u, sd_code::kEvoll, static_cast<u16>(after.depth_l));
    voices_.set_core_param(core & 1u, sd_code::kEvolr, static_cast<u16>(after.depth_r));
    note_core_write(core & 1u, 4, 0, static_cast<u32>(after.mode), static_cast<u32>(before.mode));
    note_core_write(core & 1u, 4, 1, static_cast<u32>(after.depth_l) & 0xFFFFu, old_l);
    note_core_write(core & 1u, 4, 2, static_cast<u32>(after.depth_r) & 0xFFFFu, old_r);
    note_core_write(core & 1u, 4, 3, static_cast<u32>(after.delay), static_cast<u32>(before.delay));
    note_core_write(core & 1u, 4, 4, static_cast<u32>(after.feedback), static_cast<u32>(before.feedback));
    return 0;  // libsd.h: 0 on success; -100 on a bad mode (inf: modes not validated; reverb not rendered)
}
LibsdHle::EffectAttr LibsdHle::effect_attr(u32 core) const {
    // sceSdEffectAttr {int core; int mode; short depth_L; short depth_R; int delay; int feedback;} (libsd-common.h).
    const auto& e = effect_attr_[core & 1u];
    EffectAttr a;
    s16 dl = 0, dr = 0;
    std::memcpy(&a.mode, e.data() + 4, 4);
    std::memcpy(&dl, e.data() + 8, 2);
    std::memcpy(&dr, e.data() + 10, 2);
    std::memcpy(&a.delay, e.data() + 12, 4);
    std::memcpy(&a.feedback, e.data() + 16, 4);
    a.depth_l = dl;
    a.depth_r = dr;
    return a;
}
void LibsdHle::get_effect_attr(u32 core, std::span<u8> attr) const {
    const auto& e = effect_attr_[core & 1u];
    std::memcpy(attr.data(), e.data(), std::min<std::size_t>(attr.size(), e.size()));
}
s32 LibsdHle::clear_effect_work_area(u32 /*core*/, u32 /*channel*/, u32 /*mode*/) { return 0; }

// ---- host-call glue -------------------------------------------------------------------------------

void install_libsd_calls(R3000& cpu, LibsdHle& sd, detail::IopRam& iop, std::map<std::pair<std::string, u16>, u32>& table) {
    auto def = [&](u16 ordinal, const char* name, R3000::HostCall fn) {
        table[{"libsd", ordinal}] = cpu.register_host_call(std::string("libsd.") + name, std::move(fn));
    };
    def(2, "sceSdQuit", [](R3000& c) { c.set_result(0); });
    def(4, "sceSdInit", [&sd](R3000& c) { c.set_result(static_cast<u32>(sd.init(c.arg(0)))); });
    def(5, "sceSdSetParam", [&sd](R3000& c) { sd.set_param(c.arg(0), c.arg(1)); c.set_result(0); });
    def(6, "sceSdGetParam", [&sd](R3000& c) { c.set_result(sd.get_param(c.arg(0))); });
    def(7, "sceSdSetSwitch", [&sd](R3000& c) { sd.set_switch(c.arg(0), c.arg(1)); c.set_result(0); });
    def(8, "sceSdGetSwitch", [&sd](R3000& c) { c.set_result(sd.get_switch(c.arg(0))); });
    def(9, "sceSdSetAddr", [&sd](R3000& c) { sd.set_addr(c.arg(0), c.arg(1)); c.set_result(0); });
    def(10, "sceSdGetAddr", [&sd](R3000& c) { c.set_result(sd.get_addr(c.arg(0))); });
    def(11, "sceSdSetCoreAttr", [&sd](R3000& c) { sd.set_core_attr(c.arg(0), c.arg(1)); c.set_result(0); });
    def(12, "sceSdGetCoreAttr", [&sd](R3000& c) { c.set_result(sd.get_core_attr(c.arg(0))); });
    def(13, "sceSdNote2Pitch", [&sd](R3000& c) { c.set_result(sd.note_to_pitch(c.arg(0), c.arg(1), c.arg(2), c.arg(3))); });
    def(14, "sceSdPitch2Note", [&sd](R3000& c) { c.set_result(sd.pitch_to_note(c.arg(0), c.arg(1), c.arg(2))); });
    // ProcBatch(batch*, rets*, num): 8-byte records {u16 func, u16 entry, u32 value} (libsd-common.h
    // sceSdBatch); results go to rets[i] when given. Returns the number of records processed; a bad
    // function code stops with -(index) (libsd.h: "returns the number of entries processed").
    auto batch = [&sd](R3000& c, u32 batch_addr, u32 rets, u32 num) {
        for (u32 i = 0; i < num; ++i) {
            const u32 rec = batch_addr + i * 8u;
            const u32 func = c.read16(rec), entry = c.read16(rec + 2), value = c.read32(rec + 4);
            u32 r = 0;
            switch (func) {
            case 0x1: sd.set_param(entry, value); break;
            case 0x2: sd.set_switch(entry, value); break;
            case 0x3: sd.set_addr(entry, value); break;
            case 0x4: sd.set_core_attr(entry, value); break;
            case 0x5: c.write32(entry, value); break;  // WRITEIOP (inf: entry = IOP address low half; unused)
            case 0x11: r = sd.get_param(entry); break;
            case 0x12: r = sd.get_switch(entry); break;
            case 0x13: r = sd.get_addr(entry); break;
            case 0x14: r = sd.get_core_attr(entry); break;
            default:
                c.set_result(static_cast<u32>(-static_cast<s32>(i)));
                return;
            }
            if (rets) c.write32(rets + i * 4u, r);
        }
        c.set_result(num);
    };
    def(15, "sceSdProcBatch", [batch](R3000& c) { batch(c, c.arg(0), c.arg(1), c.arg(2)); });
    def(16, "sceSdProcBatchEx", [batch](R3000& c) { batch(c, c.arg(0), c.arg(1), c.arg(2)); });
    def(17, "sceSdVoiceTrans", [&sd, &iop](R3000& c) {
        c.set_result(static_cast<u32>(sd.voice_trans(c.arg(0), c.arg(1), iop, c.arg(2), c.arg(3), c.arg(4), &iop)));
    });
    def(18, "sceSdBlockTrans", [&sd, &iop](R3000& c) {
        c.set_result(static_cast<u32>(sd.block_trans(c.arg(0), c.arg(1), iop, c.arg(2), c.arg(3), c.arg(4), &iop)));
    });
    def(19, "sceSdVoiceTransStatus", [&sd](R3000& c) { c.set_result(sd.voice_trans_status(c.arg(0), c.arg(1))); });
    def(20, "sceSdBlockTransStatus", [&sd](R3000& c) { c.set_result(sd.block_trans_status(c.arg(0), c.arg(1))); });
    def(21, "sceSdSetTransCallback", [](R3000& c) { c.set_result(0); });
    def(22, "sceSdSetIRQCallback", [](R3000& c) { c.set_result(0); });
    def(23, "sceSdSetEffectAttr", [&sd](R3000& c) {
        u8 a[32];
        for (u32 i = 0; i < 32; ++i) a[i] = c.read8(c.arg(1) + i);
        c.set_result(static_cast<u32>(sd.set_effect_attr(c.arg(0), a)));
    });
    def(24, "sceSdGetEffectAttr", [&sd](R3000& c) {
        u8 a[32];
        sd.get_effect_attr(c.arg(0), a);
        for (u32 i = 0; i < 32; ++i) c.write8(c.arg(1) + i, a[i]);
        c.set_result(0);
    });
    def(25, "sceSdClearEffectWorkArea", [&sd](R3000& c) { c.set_result(static_cast<u32>(sd.clear_effect_work_area(c.arg(0), c.arg(1), c.arg(2)))); });
    def(26, "sceSdSetTransIntrHandler", [](R3000& c) { c.set_result(0); });  // previous handler: none
    def(27, "sceSdSetSpu2IntrHandler", [](R3000& c) { c.set_result(0); });
    def(28, "sceSdGetTransIntrHandlerArgument", [](R3000& c) { c.set_result(0); });
    def(29, "sceSdGetSpu2IntrHandlerArgument", [](R3000& c) { c.set_result(0); });
    def(30, "sceSdStopTrans", [](R3000& c) { c.set_result(0); });
    def(31, "sceSdCleanEffectWorkArea", [](R3000& c) { c.set_result(0); });
    def(32, "sceSdSetEffectMode", [](R3000& c) { c.set_result(0); });
    def(33, "sceSdSetEffectModeParams", [](R3000& c) { c.set_result(0); });
}

}  // namespace p3fes::hle::sif::iop
