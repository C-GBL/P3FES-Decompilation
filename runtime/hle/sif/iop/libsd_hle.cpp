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

u32 libsd_call(LibsdHle& sd, detail::IopRam& iop, u32 ordinal, const u32 (&a)[5]) {
    u8* const mem = iop.at(0, detail::kIopRamSize);
    auto mask = [](u32 x) { return x & (detail::kIopRamSize - 1u); };
    auto rd8 = [&](u32 x) { return mem[mask(x)]; };
    auto wr8 = [&](u32 x, u8 v) { mem[mask(x)] = v; };
    auto rd16 = [&](u32 x) { u16 v; std::memcpy(&v, mem + mask(x & ~1u), 2); return v; };
    auto rd32 = [&](u32 x) { u32 v; std::memcpy(&v, mem + mask(x & ~3u), 4); return v; };
    auto wr32 = [&](u32 x, u32 v) { std::memcpy(mem + mask(x & ~3u), &v, 4); };
    switch (ordinal) {
    case 2: return 0;  // sceSdQuit
    case 4: return static_cast<u32>(sd.init(a[0]));
    case 5: sd.set_param(a[0], a[1]); return 0;
    case 6: return sd.get_param(a[0]);
    case 7: sd.set_switch(a[0], a[1]); return 0;
    case 8: return sd.get_switch(a[0]);
    case 9: sd.set_addr(a[0], a[1]); return 0;
    case 10: return sd.get_addr(a[0]);
    case 11: sd.set_core_attr(a[0], a[1]); return 0;
    case 12: return sd.get_core_attr(a[0]);
    case 13: return sd.note_to_pitch(a[0], a[1], a[2], a[3]);
    case 14: return sd.pitch_to_note(a[0], a[1], a[2]);
    case 15:
    case 16: {
        // ProcBatch(batch*, rets*, num): 8-byte records {u16 func, u16 entry, u32 value} (libsd-common.h
        // sceSdBatch); results go to rets[i] when given. Returns the number of records processed; a bad
        // function code stops with -(index) (libsd.h: "returns the number of entries processed").
        const u32 batch = a[0], rets = a[1], num = a[2];
        for (u32 i = 0; i < num; ++i) {
            const u32 rec = batch + i * 8u;
            const u32 func = rd16(rec), entry = rd16(rec + 2), value = rd32(rec + 4);
            u32 r = 0;
            switch (func) {
            case 0x1: sd.set_param(entry, value); break;
            case 0x2: sd.set_switch(entry, value); break;
            case 0x3: sd.set_addr(entry, value); break;
            case 0x4: sd.set_core_attr(entry, value); break;
            case 0x5: wr32(entry, value); break;  // WRITEIOP (inf: entry = IOP address low half; unused)
            case 0x11: r = sd.get_param(entry); break;
            case 0x12: r = sd.get_switch(entry); break;
            case 0x13: r = sd.get_addr(entry); break;
            case 0x14: r = sd.get_core_attr(entry); break;
            default: return static_cast<u32>(-static_cast<s32>(i));
            }
            if (rets) wr32(rets + i * 4u, r);
        }
        return num;
    }
    case 17: return static_cast<u32>(sd.voice_trans(a[0], a[1], iop, a[2], a[3], a[4], &iop));
    case 18: return static_cast<u32>(sd.block_trans(a[0], a[1], iop, a[2], a[3], a[4], &iop));
    case 19: return sd.voice_trans_status(a[0], a[1]);
    case 20: return sd.block_trans_status(a[0], a[1]);
    case 23: {
        u8 attr[32];
        for (u32 i = 0; i < 32; ++i) attr[i] = rd8(a[1] + i);
        return static_cast<u32>(sd.set_effect_attr(a[0], attr));
    }
    case 24: {
        u8 attr[32];
        sd.get_effect_attr(a[0], attr);
        for (u32 i = 0; i < 32; ++i) wr8(a[1] + i, attr[i]);
        return 0;
    }
    case 25: return static_cast<u32>(sd.clear_effect_work_area(a[0], a[1], a[2]));
    // 21 SetTransCallback, 22 SetIRQCallback, 26 SetTransIntrHandler (previous handler: none), 27 SetSpu2IntrHandler,
    // 28 / 29 the handler arguments, 30 StopTrans, 31 CleanEffectWorkArea, 32 / 33 SetEffectMode(Params)
    default: return 0;
    }
}

void install_libsd_calls(R3000& cpu, LibsdHle& sd, detail::IopRam& iop, std::map<std::pair<std::string, u16>, u32>& table) {
    // One host call per ordinal, all through libsd_call (the native SK stack, runtime/native/sound/sk, calls it too).
    static constexpr std::pair<u16, const char*> kNames[] = {
        {2, "sceSdQuit"}, {4, "sceSdInit"}, {5, "sceSdSetParam"}, {6, "sceSdGetParam"}, {7, "sceSdSetSwitch"},
        {8, "sceSdGetSwitch"}, {9, "sceSdSetAddr"}, {10, "sceSdGetAddr"}, {11, "sceSdSetCoreAttr"},
        {12, "sceSdGetCoreAttr"}, {13, "sceSdNote2Pitch"}, {14, "sceSdPitch2Note"}, {15, "sceSdProcBatch"},
        {16, "sceSdProcBatchEx"}, {17, "sceSdVoiceTrans"}, {18, "sceSdBlockTrans"}, {19, "sceSdVoiceTransStatus"},
        {20, "sceSdBlockTransStatus"}, {21, "sceSdSetTransCallback"}, {22, "sceSdSetIRQCallback"},
        {23, "sceSdSetEffectAttr"}, {24, "sceSdGetEffectAttr"}, {25, "sceSdClearEffectWorkArea"},
        {26, "sceSdSetTransIntrHandler"}, {27, "sceSdSetSpu2IntrHandler"}, {28, "sceSdGetTransIntrHandlerArgument"},
        {29, "sceSdGetSpu2IntrHandlerArgument"}, {30, "sceSdStopTrans"}, {31, "sceSdCleanEffectWorkArea"},
        {32, "sceSdSetEffectMode"}, {33, "sceSdSetEffectModeParams"},
    };
    for (const auto& [ordinal, name] : kNames) {
        const u32 o = ordinal;
        table[{"libsd", ordinal}] = cpu.register_host_call(std::string("libsd.") + name, [&sd, &iop, o](R3000& c) {
            const u32 args[5] = {c.arg(0), c.arg(1), c.arg(2), c.arg(3), c.arg(4)};
            c.set_result(libsd_call(sd, iop, o, args));
        });
    }
}
}  // namespace p3fes::hle::sif::iop
