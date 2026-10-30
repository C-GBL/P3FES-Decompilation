// Small GIF packet builder (tests, the host self-test scene). Produces quadwords exactly as the game's packet
// builders lay them out: a GIF tag followed by its PACKED / REGLIST / IMAGE data.
#pragma once

#include "p3fes/gs/gs_types.h"

#include <cstring>
#include <initializer_list>
#include <utility>
#include <vector>

namespace p3fes::gs {

inline u128 make_qword(u64 lo, u64 hi) noexcept {
    u128 q{};
    q.u64[0] = lo;
    q.u64[1] = hi;
    return q;
}

inline u128 make_giftag(u32 nloop, bool eop, u32 flg, u32 nreg, u64 regs, bool pre = false, u32 prim = 0) noexcept {
    const u64 lo = (static_cast<u64>(nloop) & 0x7FFFu) | (static_cast<u64>(eop) << 15) | (static_cast<u64>(pre) << 46) |
                   ((static_cast<u64>(prim) & 0x7FFu) << 47) | ((static_cast<u64>(flg) & 3u) << 58) |
                   ((static_cast<u64>(nreg) & 0xFu) << 60);
    return make_qword(lo, regs);
}

class GifBuilder {
public:
    // One tag with NLOOP = pairs.size(), NREG = 1, REGS = A+D, followed by the A+D qwords.
    GifBuilder& ad(std::initializer_list<std::pair<u8, u64>> pairs, bool eop = true) {
        q_.push_back(make_giftag(static_cast<u32>(pairs.size()), eop, 0, 1, 0xE));
        for (const auto& [r, v] : pairs) q_.push_back(make_qword(v, r));
        return *this;
    }
    GifBuilder& tag(u32 nloop, bool eop, u32 flg, u32 nreg, u64 regs, bool pre = false, u32 prim = 0) {
        q_.push_back(make_giftag(nloop, eop, flg, nreg, regs, pre, prim));
        return *this;
    }
    GifBuilder& raw(u64 lo, u64 hi) {
        q_.push_back(make_qword(lo, hi));
        return *this;
    }
    // IMAGE tag + data (padded with zeros to a whole qword).
    GifBuilder& image(const void* data, std::size_t bytes, bool eop = true) {
        const std::size_t qwc = (bytes + 15) / 16;
        q_.push_back(make_giftag(static_cast<u32>(qwc), eop, 2, 0, 0));
        const std::size_t at = q_.size();
        q_.resize(at + qwc);
        std::memcpy(q_.data() + at, data, bytes);
        if (bytes % 16) std::memset(reinterpret_cast<u8*>(q_.data() + at) + bytes, 0, 16 - bytes % 16);
        return *this;
    }
    const std::vector<u128>& qwords() const noexcept { return q_; }
    std::vector<u128>& qwords() noexcept { return q_; }

private:
    std::vector<u128> q_;
};

// Register value helpers (GS User's Manual field layouts).
inline constexpr u64 gs_prim(u32 type, bool iip = false, bool tme = false, bool fge = false, bool abe = false,
                             bool fst = false, u32 ctxt = 0) noexcept {
    return static_cast<u64>(type & 7u) | (static_cast<u64>(iip) << 3) | (static_cast<u64>(tme) << 4) |
           (static_cast<u64>(fge) << 5) | (static_cast<u64>(abe) << 6) | (static_cast<u64>(fst) << 8) |
           (static_cast<u64>(ctxt & 1u) << 9);
}
inline constexpr u64 gs_rgbaq(u32 r, u32 g, u32 b, u32 a, u32 q_bits = 0x3F800000u) noexcept {
    return (r & 0xFFu) | ((g & 0xFFu) << 8) | ((b & 0xFFu) << 16) | (static_cast<u64>(a & 0xFFu) << 24) |
           (static_cast<u64>(q_bits) << 32);
}
inline constexpr u64 gs_xyz(u32 x16, u32 y16, u32 z) noexcept {
    return (x16 & 0xFFFFu) | (static_cast<u64>(y16 & 0xFFFFu) << 16) | (static_cast<u64>(z) << 32);
}
inline constexpr u64 gs_uv(u32 u16, u32 v16) noexcept { return (u16 & 0x3FFFu) | (static_cast<u64>(v16 & 0x3FFFu) << 16); }
inline constexpr u64 gs_frame(u32 fbp, u32 fbw, u32 psm, u32 fbmsk = 0) noexcept {
    return (fbp & 0x1FFu) | (static_cast<u64>(fbw & 0x3Fu) << 16) | (static_cast<u64>(psm & 0x3Fu) << 24) |
           (static_cast<u64>(fbmsk) << 32);
}
inline constexpr u64 gs_zbuf(u32 zbp, u32 psm_nibble, bool zmsk) noexcept {
    return (zbp & 0x1FFu) | (static_cast<u64>(psm_nibble & 0xFu) << 24) | (static_cast<u64>(zmsk) << 32);
}
inline constexpr u64 gs_scissor(u32 x0, u32 x1, u32 y0, u32 y1) noexcept {
    return (x0 & 0x7FFu) | (static_cast<u64>(x1 & 0x7FFu) << 16) | (static_cast<u64>(y0 & 0x7FFu) << 32) |
           (static_cast<u64>(y1 & 0x7FFu) << 48);
}
inline constexpr u64 gs_xyoffset(u32 ofx16, u32 ofy16) noexcept { return (ofx16 & 0xFFFFu) | (static_cast<u64>(ofy16 & 0xFFFFu) << 32); }
inline constexpr u64 gs_test(bool ate, u32 atst, u32 aref, u32 afail, bool date, bool datm, bool zte, u32 ztst) noexcept {
    return static_cast<u64>(ate) | ((atst & 7u) << 1) | ((aref & 0xFFu) << 4) | ((afail & 3u) << 12) |
           (static_cast<u64>(date) << 14) | (static_cast<u64>(datm) << 15) | (static_cast<u64>(zte) << 16) |
           ((ztst & 3u) << 17);
}
inline constexpr u64 gs_alpha(u32 a, u32 b, u32 c, u32 d, u32 fix = 0) noexcept {
    return (a & 3u) | ((b & 3u) << 2) | ((c & 3u) << 4) | ((d & 3u) << 6) | (static_cast<u64>(fix & 0xFFu) << 32);
}
inline constexpr u64 gs_tex0(u32 tbp, u32 tbw, u32 psm, u32 tw, u32 th, bool tcc, u32 tfx, u32 cbp = 0, u32 cpsm = 0,
                             u32 csm = 0, u32 csa = 0, u32 cld = 0) noexcept {
    return (tbp & 0x3FFFu) | (static_cast<u64>(tbw & 0x3Fu) << 14) | (static_cast<u64>(psm & 0x3Fu) << 20) |
           (static_cast<u64>(tw & 0xFu) << 26) | (static_cast<u64>(th & 0xFu) << 30) | (static_cast<u64>(tcc) << 34) |
           (static_cast<u64>(tfx & 3u) << 35) | (static_cast<u64>(cbp & 0x3FFFu) << 37) |
           (static_cast<u64>(cpsm & 0xFu) << 51) | (static_cast<u64>(csm & 1u) << 55) |
           (static_cast<u64>(csa & 0x1Fu) << 56) | (static_cast<u64>(cld & 7u) << 61);
}
inline constexpr u64 gs_bitbltbuf(u32 sbp, u32 sbw, u32 spsm, u32 dbp, u32 dbw, u32 dpsm) noexcept {
    return (sbp & 0x3FFFu) | (static_cast<u64>(sbw & 0x3Fu) << 16) | (static_cast<u64>(spsm & 0x3Fu) << 24) |
           (static_cast<u64>(dbp & 0x3FFFu) << 32) | (static_cast<u64>(dbw & 0x3Fu) << 48) |
           (static_cast<u64>(dpsm & 0x3Fu) << 56);
}
inline constexpr u64 gs_trxpos(u32 ssax, u32 ssay, u32 dsax, u32 dsay, u32 dir = 0) noexcept {
    return (ssax & 0x7FFu) | (static_cast<u64>(ssay & 0x7FFu) << 16) | (static_cast<u64>(dsax & 0x7FFu) << 32) |
           (static_cast<u64>(dsay & 0x7FFu) << 48) | (static_cast<u64>(dir & 3u) << 59);
}
inline constexpr u64 gs_trxreg(u32 w, u32 h) noexcept { return (w & 0xFFFu) | (static_cast<u64>(h & 0xFFFu) << 32); }

// Privileged display values.
inline constexpr u64 gs_dispfb(u32 fbp, u32 fbw, u32 psm, u32 dbx = 0, u32 dby = 0) noexcept {
    return (fbp & 0x1FFu) | (static_cast<u64>(fbw & 0x3Fu) << 9) | (static_cast<u64>(psm & 0x1Fu) << 15) |
           (static_cast<u64>(dbx & 0x7FFu) << 32) | (static_cast<u64>(dby & 0x7FFu) << 43);
}
inline constexpr u64 gs_display(u32 dx, u32 dy, u32 magh, u32 magv, u32 dw, u32 dh) noexcept {
    return (dx & 0xFFFu) | (static_cast<u64>(dy & 0x7FFu) << 12) | (static_cast<u64>(magh & 0xFu) << 23) |
           (static_cast<u64>(magv & 3u) << 27) | (static_cast<u64>(dw & 0xFFFu) << 32) | (static_cast<u64>(dh & 0x7FFu) << 44);
}

} // namespace p3fes::gs
