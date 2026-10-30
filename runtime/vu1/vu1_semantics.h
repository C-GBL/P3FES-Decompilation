// Pair semantics shared by the VU1 interpreter (vu1_interp.cpp) and the ahead-of-time compiled programs
// (vu1_aot.h, the generated vu1_aot_programs.cpp): the upper-op descriptor table, the FMAC datapath of one upper op,
// MAC/status/clip flag rules and the timestamped flag pipe. Moved here verbatim from vu1_interp.cpp so both paths
// execute the same code; provenance as in vu1_interp.cpp (ps2-web-recomp @ c0f476e, MIT). Private to p3fes_vu1.
#pragma once

#include "p3fes/ee/fpu.h"
#include "p3fes/vu1/vu1_interp.h"

#include <bit>

namespace p3fes::vu1::sem {

namespace fp = ::p3fes::ee::fpu;
using U = UpperOp;
using L = LowerOp;

// ---------------------------------------------------------------------------------------------------------------
// Upper ops: what each form-qualified op computes (upstream `upper()` / `decode_upper` kinds and sources).
// ---------------------------------------------------------------------------------------------------------------
enum class Kind : u8 { None, Add, Sub, Madd, Msub, Max, Min, Mul, Abs, Ftoi, Itof, Clip, Opmula, Opmsub };
enum class Src : u8 { Vec, Bc, Q, I };

struct UpperDesc {
    Kind kind = Kind::None;
    Src src = Src::Vec;
    bool to_acc = false;
    bool flags = false; // updates MAC/status flags (MAX/MINI/ABS/FTOI/ITOF/CLIP do not)
    u8 frac = 0;        // ITOF/FTOI fraction bits
};

constexpr UpperDesc describe(UpperOp op) noexcept {
    switch (op) {
    case U::ADDbc: return {Kind::Add, Src::Bc, false, true};
    case U::SUBbc: return {Kind::Sub, Src::Bc, false, true};
    case U::MADDbc: return {Kind::Madd, Src::Bc, false, true};
    case U::MSUBbc: return {Kind::Msub, Src::Bc, false, true};
    case U::MAXbc: return {Kind::Max, Src::Bc, false, false};
    case U::MINIbc: return {Kind::Min, Src::Bc, false, false};
    case U::MULbc: return {Kind::Mul, Src::Bc, false, true};
    case U::MULq: return {Kind::Mul, Src::Q, false, true};
    case U::MAXi: return {Kind::Max, Src::I, false, false};
    case U::MULi: return {Kind::Mul, Src::I, false, true};
    case U::MINIi: return {Kind::Min, Src::I, false, false};
    case U::ADDq: return {Kind::Add, Src::Q, false, true};
    case U::MADDq: return {Kind::Madd, Src::Q, false, true};
    case U::ADDi: return {Kind::Add, Src::I, false, true};
    case U::MADDi: return {Kind::Madd, Src::I, false, true};
    case U::SUBq: return {Kind::Sub, Src::Q, false, true};
    case U::MSUBq: return {Kind::Msub, Src::Q, false, true};
    case U::SUBi: return {Kind::Sub, Src::I, false, true};
    case U::MSUBi: return {Kind::Msub, Src::I, false, true};
    case U::ADD: return {Kind::Add, Src::Vec, false, true};
    case U::MADD: return {Kind::Madd, Src::Vec, false, true};
    case U::MUL: return {Kind::Mul, Src::Vec, false, true};
    case U::MAX: return {Kind::Max, Src::Vec, false, false};
    case U::SUB: return {Kind::Sub, Src::Vec, false, true};
    case U::MSUB: return {Kind::Msub, Src::Vec, false, true};
    case U::OPMSUB: return {Kind::Opmsub, Src::Vec, false, true};
    case U::MINI: return {Kind::Min, Src::Vec, false, false};
    case U::ADDAbc: return {Kind::Add, Src::Bc, true, true};
    case U::SUBAbc: return {Kind::Sub, Src::Bc, true, true};
    case U::MADDAbc: return {Kind::Madd, Src::Bc, true, true};
    case U::MSUBAbc: return {Kind::Msub, Src::Bc, true, true};
    case U::ITOF0: return {Kind::Itof, Src::Vec, false, false, 0};
    case U::ITOF4: return {Kind::Itof, Src::Vec, false, false, 4};
    case U::ITOF12: return {Kind::Itof, Src::Vec, false, false, 12};
    case U::ITOF15: return {Kind::Itof, Src::Vec, false, false, 15};
    case U::FTOI0: return {Kind::Ftoi, Src::Vec, false, false, 0};
    case U::FTOI4: return {Kind::Ftoi, Src::Vec, false, false, 4};
    case U::FTOI12: return {Kind::Ftoi, Src::Vec, false, false, 12};
    case U::FTOI15: return {Kind::Ftoi, Src::Vec, false, false, 15};
    case U::MULAbc: return {Kind::Mul, Src::Bc, true, true};
    case U::MULAq: return {Kind::Mul, Src::Q, true, true};
    case U::ABS: return {Kind::Abs, Src::Vec, false, false};
    case U::MULAi: return {Kind::Mul, Src::I, true, true};
    case U::CLIP: return {Kind::Clip};
    case U::ADDAq: return {Kind::Add, Src::Q, true, true};
    case U::MADDAq: return {Kind::Madd, Src::Q, true, true};
    case U::ADDAi: return {Kind::Add, Src::I, true, true};
    case U::MADDAi: return {Kind::Madd, Src::I, true, true};
    case U::SUBAq: return {Kind::Sub, Src::Q, true, true};
    case U::MSUBAq: return {Kind::Msub, Src::Q, true, true};
    case U::SUBAi: return {Kind::Sub, Src::I, true, true};
    case U::MSUBAi: return {Kind::Msub, Src::I, true, true};
    case U::ADDA: return {Kind::Add, Src::Vec, true, true};
    case U::MADDA: return {Kind::Madd, Src::Vec, true, true};
    case U::MULA: return {Kind::Mul, Src::Vec, true, true};
    case U::SUBA: return {Kind::Sub, Src::Vec, true, true};
    case U::MSUBA: return {Kind::Msub, Src::Vec, true, true};
    case U::OPMULA: return {Kind::Opmula, Src::Vec, true, true};
    case U::NOP: case U::Unknown: case U::Count: break;
    }
    return {};
}

constexpr int kAcc = 32;

struct UpperOut {
    int target = -1; // -1 none, 0 vf00 (flags only), 1..31 vf, kAcc
    u32 value[4] = {};
    u32 dest = 0;
    bool flags = false;
    bool has_clip = false;
    u32 clip = 0;
};

inline bool lane(u32 dest, int i) noexcept { return (dest & (8u >> i)) != 0; }

// MAC flags: per destination lane i (bit 3 - i): Z if the exponent is zero, S if negative, O if the magnitude is
// the clamp value 0x7FFFFFFF. Underflow bits are never set (upstream).
inline u32 mac_flags(const u32 (&v)[4], u32 dest) noexcept {
    u32 mac = 0;
    for (int i = 0; i < 4; ++i) {
        if (!lane(dest, i)) continue;
        const u32 bit = 3u - static_cast<u32>(i);
        const u32 x = v[i];
        if (!(x & 0x7F800000u)) mac |= 1u << bit;
        if (x & 0x80000000u) mac |= 1u << (bit + 4);
        if ((x & 0x7FFFFFFFu) == 0x7FFFFFFFu) mac |= 1u << (bit + 12);
    }
    return mac;
}

inline void set_flags(VU1State& r, const u32 (&v)[4], u32 dest) noexcept {
    const u32 mac = mac_flags(v, dest);
    r.mac = mac;
    u32 status = r.status & 0xFF0u;
    if (mac & 0x000Fu) status |= 0x1u;
    if (mac & 0x00F0u) status |= 0x2u;
    if (mac & 0x0F00u) status |= 0x4u;
    if (mac & 0xF000u) status |= 0x8u;
    status |= (status & 0xFu) << 6;
    r.status = (status & ~0x30u) | (r.status & 0x30u);
}

// CLIP: x > +|w| -> bit 0, x < -|w| -> bit 1, then y (bits 2, 3) and z (bits 4, 5); older judgements shift up.
inline u32 clip_value(u32 history, const u32 (&s)[4], u32 w) noexcept {
    const s32 lim = fp::key(w & fp::kAbs);
    u32 f = 0;
    for (int i = 0; i < 3; ++i) {
        const s32 x = fp::key(s[i]);
        if (x > lim) f |= 1u << (i * 2);
        if (x < -lim) f |= 2u << (i * 2);
    }
    return ((history << 6) | f) & 0xFFFFFFu;
}

inline UpperOut compute_upper(const VU1State& r, const UpperInsn& u) noexcept {
    UpperOut o;
    const UpperDesc dsc = describe(u.op);
    const u32(&s)[4] = r.vf[u.fs];
    const u32(&t)[4] = r.vf[u.ft];
    switch (dsc.kind) {
    case Kind::None:
        return o;
    case Kind::Clip:
        o.has_clip = true;
        o.clip = clip_value(r.clip, s, t[3]);
        return o;
    case Kind::Opmula:
        o.target = kAcc;
        o.dest = 0xEu;
        o.flags = true;
        o.value[0] = fp::mul(s[1], t[2]);
        o.value[1] = fp::mul(s[2], t[0]);
        o.value[2] = fp::mul(s[0], t[1]);
        return o;
    case Kind::Opmsub:
        o.target = u.fd;
        o.dest = 0xEu;
        o.flags = true;
        o.value[0] = fp::sub(r.acc[0], fp::mul(s[1], t[2]));
        o.value[1] = fp::sub(r.acc[1], fp::mul(s[2], t[0]));
        o.value[2] = fp::sub(r.acc[2], fp::mul(s[0], t[1]));
        return o;
    default:
        break;
    }
    const bool to_ft = dsc.kind == Kind::Itof || dsc.kind == Kind::Ftoi || dsc.kind == Kind::Abs;
    o.target = dsc.to_acc ? kAcc : (to_ft ? u.ft : u.fd);
    o.dest = u.dest;
    o.flags = dsc.flags;
    for (int i = 0; i < 4; ++i) {
        if (!lane(u.dest, i)) continue;
        u32 b = 0;
        switch (dsc.src) {
        case Src::Vec: b = t[i]; break;
        case Src::Bc: b = t[u.bc]; break;
        case Src::Q: b = r.q; break;
        case Src::I: b = r.i; break;
        }
        u32 v = 0;
        switch (dsc.kind) {
        case Kind::Add: v = fp::add(s[i], b); break;
        case Kind::Sub: v = fp::sub(s[i], b); break;
        case Kind::Mul: v = fp::mul(s[i], b); break;
        case Kind::Madd: v = fp::add(r.acc[i], fp::mul(s[i], b)); break;
        case Kind::Msub: v = fp::sub(r.acc[i], fp::mul(s[i], b)); break;
        case Kind::Max: v = fp::max(s[i], b); break;
        case Kind::Min: v = fp::min(s[i], b); break;
        case Kind::Abs: v = s[i] & fp::kAbs; break;
        case Kind::Ftoi: v = fp::to_fixed(s[i], dsc.frac); break;
        case Kind::Itof: v = fp::from_fixed(static_cast<s32>(s[i]), dsc.frac); break;
        default: break;
        }
        o.value[i] = v;
    }
    return o;
}

// ---------------------------------------------------------------------------------------------------------------
// FlagPipe operations (upstream vuops::FlagPipe members).
// ---------------------------------------------------------------------------------------------------------------
inline void pipe_start(FlagPipe& p, const VU1State& r) noexcept {
    for (int i = 0; i < 8; ++i) {
        p.mac_ts[i] = p.clip_ts[i] = 0;
        p.mac_v[i] = r.mac;
        p.status_v[i] = r.status;
        p.clip_v[i] = r.clip;
    }
}

inline void pipe_set_mac(FlagPipe& p, u32 mac, u32 status) noexcept {
    const u32 i = p.mh++ & 7u;
    p.mac_ts[i] = p.t;
    p.mac_v[i] = mac;
    p.status_v[i] = status;
}

inline void pipe_set_clip(FlagPipe& p, u32 clip, u32 at) noexcept {
    const u32 i = p.ch++ & 7u;
    p.clip_ts[i] = at;
    p.clip_v[i] = clip;
}

inline u32 pipe_mac(const FlagPipe& p) noexcept {
    for (u32 k = 1; k <= 8; ++k) {
        const u32 i = (p.mh - k) & 7u;
        if (p.mac_ts[i] + 4u <= p.t) return p.mac_v[i];
    }
    return p.mac_v[(p.mh - 8u) & 7u];
}

inline u32 pipe_clip(const FlagPipe& p) noexcept {
    for (u32 k = 1; k <= 8; ++k) {
        const u32 i = (p.ch - k) & 7u;
        if (p.clip_ts[i] + 3u <= p.t) return p.clip_v[i];
    }
    return p.clip_v[(p.ch - 8u) & 7u];
}

// Host-float helpers of upstream's EFU P ops: inputs flushed/clamped like the VU datapath, outputs raw.
inline u32 f2u(float f) noexcept { return std::bit_cast<u32>(f); }
inline float u2f(u32 v) noexcept {
    if (!(v & 0x7F800000u)) v &= 0x80000000u;
    if ((v & 0x7F800000u) == 0x7F800000u) v = (v & 0x80000000u) | 0x7F7FFFFFu;
    return std::bit_cast<float>(v);
}

inline u8* qword(VU1State& r, u32 index) noexcept { return r.data + (index & (kDataQwords - 1u)) * 16u; }

} // namespace p3fes::vu1::sem
