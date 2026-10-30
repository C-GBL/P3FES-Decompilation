// Shared helpers for the IPU tests: an MSB-first bit writer for hand-built MPEG bit streams, a minimal HwBus,
// and small drivers for IpuCore. Every stream in these tests is synthetic; codes are written out from the tables
// of ISO/IEC 13818-2 Annex B with the table and row named next to them.
#pragma once

#include "p3fes/hle/hw_bus.h"
#include "p3fes/ipu/ipu_core.h"
#include "p3fes/ipu/ipu_system.h"
#include "p3fes/ipu/mpeg2.h"

#include <doctest.h>

#include <cstring>
#include <ios>
#include <string>
#include <vector>

namespace it {

using namespace p3fes;
using namespace p3fes::ipu;

// MSB-first bit packer (the MPEG byte stream: bytes in memory order, bits MSB first).
struct Bits {
    std::vector<u8> bytes;
    unsigned nbits = 0;

    void bit(unsigned b) {
        if ((nbits & 7u) == 0) bytes.push_back(0);
        if (b) bytes.back() = static_cast<u8>(bytes.back() | (0x80u >> (nbits & 7u)));
        ++nbits;
    }
    // "0101 1" style; spaces, '_' and '|' are separators.
    Bits& s(const char* str) {
        for (const char* p = str; *p; ++p)
            if (*p == '0' || *p == '1') bit(static_cast<unsigned>(*p - '0'));
        return *this;
    }
    Bits& v(u32 value, unsigned n) {
        for (unsigned i = n; i-- > 0;) bit((value >> i) & 1u);
        return *this;
    }
    Bits& align() {
        while (nbits & 7u) bit(0);
        return *this;
    }
    Bits& byte(u8 b) { return v(b, 8); }
    Bits& start_code(u8 code) { return align().byte(0).byte(0).byte(1).byte(code); }
    // Quadwords, zero-padded to a whole number of qwords (plus `extra` zero qwords).
    std::vector<u128> qwords(unsigned extra = 0) const {
        std::vector<u128> q((bytes.size() + 15) / 16 + extra);
        if (!bytes.empty()) std::memcpy(q.data(), bytes.data(), bytes.size());
        return q;
    }
};

inline u128 qw_bytes(const u8* b) {
    u128 q{};
    std::memcpy(&q, b, 16);
    return q;
}

// A bus that records maps, DMA handlers and interrupts and routes accesses to the mapped devices.
struct FakeBus final : hle::HwBus {
    struct Range {
        u32 b, e;
        hle::HwDevice* d;
    };
    hle::Timebase tb;
    std::vector<Range> ranges;
    hle::DmaChannelHandler* dma[10] = {};
    std::vector<unsigned> intc;
    std::vector<unsigned> dma_done;

    hle::HwDevice* at(u32 pa) {
        for (const Range& r : ranges)
            if (pa >= r.b && pa < r.e) return r.d;
        FAIL("FakeBus: access to unmapped 0x" << std::hex << pa);
        return nullptr;
    }
    void map(u32 b, u32 e, hle::HwDevice* d) override { ranges.push_back({b, e, d}); }
    void set_dma_handler(unsigned ch, hle::DmaChannelHandler* h) override { dma[ch] = h; }
    void raise_intc(unsigned c) override { intc.push_back(c); }
    void dma_complete(unsigned ch) override { dma_done.push_back(ch); }
    const hle::Timebase& time() const override { return tb; }
    u32 read32(u32 pa) override { return at(pa)->read32(pa); }
    void write32(u32 pa, u32 v) override { at(pa)->write32(pa, v); }
    u64 read64(u32 pa) override { return at(pa)->read64(pa); }
    void write64(u32 pa, u64 v) override { at(pa)->write64(pa, v); }
    u128 read128(u32 pa) override { return at(pa)->read128(pa); }
    void write128(u32 pa, const u128& v) override { at(pa)->write128(pa, v); }
    u8 read8(u32 pa) override { return at(pa)->read8(pa); }
    u16 read16(u32 pa) override { return at(pa)->read16(pa); }
    void write8(u32 pa, u8 v) override { at(pa)->write8(pa, v); }
    void write16(u32 pa, u16 v) override { at(pa)->write16(pa, v); }
};

// A core with its traps collected (tests assert on them instead of stderr).
struct Core {
    IpuCore c;
    std::vector<IpuTrap> traps;
    unsigned interrupts = 0;
    u64 t = 1000;  // virtual time used by the helpers

    explicit Core(IpuCosts costs = {}) : c(costs) {
        c.set_trap_handler([this](const IpuTrap& tr) { traps.push_back(tr); });
        c.set_completion_handler([this] { ++interrupts; });
    }
    void ctrl(u32 v) { c.write_ctrl(v, t); }
    void cmd(u32 v) { c.write_cmd(v, t); }
    std::size_t feed(const std::vector<u128>& q) { return c.push_input(q.data(), q.size(), t); }
    // Advance time until the command completes (bounded), returning the cycles waited.
    u64 wait_idle(u64 limit = 1u << 20) {
        const u64 t0 = t;
        while ((c.read_ctrl(t) & kCtrlBusy) && t - t0 < limit) ++t;
        return t - t0;
    }
    // Feed `in` (as much as the input side takes per call) and collect output 8 qwords per call, one cycle per round,
    // until the input is used up and the command has completed (bounded).
    std::vector<u8> stream(const std::vector<u128>& in, std::size_t out_per_call = 8, int max_rounds = 100000) {
        std::vector<u8> out;
        std::size_t fed = 0;
        for (int round = 0; round < max_rounds && (fed < in.size() || c.busy() || c.out_qwords()); ++round) {
            if (fed < in.size()) fed += c.push_input(in.data() + fed, in.size() - fed, t);
            const std::vector<u8> d = drain(out_per_call);
            out.insert(out.end(), d.begin(), d.end());
            ++t;
            c.update(t);
        }
        return out;
    }
    std::vector<u8> drain(std::size_t max_qw = 4096) {
        std::vector<u128> q(max_qw);
        const std::size_t n = c.pop_output(q.data(), q.size(), t);
        std::vector<u8> out(n * 16);
        if (n) std::memcpy(out.data(), q.data(), n * 16);
        return out;
    }
};

inline s16 s16_at(const std::vector<u8>& b, std::size_t i) {
    s16 v = 0;
    std::memcpy(&v, b.data() + 2 * i, 2);
    return v;
}

// IPU_CTRL mode word.
inline u32 mode(unsigned pct, unsigned idp = 0, bool mp1 = false, bool ivf = false, bool as = false, bool qst = false) {
    return (pct << kCtrlPctShift) | (idp << kCtrlIdpShift) | (mp1 ? kCtrlMp1 : 0u) | (ivf ? kCtrlIvf : 0u) |
           (as ? kCtrlAs : 0u) | (qst ? kCtrlQst : 0u);
}

// BDEC / IDEC / VDEC / FDEC command words.
inline u32 bdec(bool mbi, bool dcr, bool dt, unsigned qsc, unsigned fb = 0) {
    return 0x20000000u | (mbi ? 1u << 27 : 0u) | (dcr ? 1u << 26 : 0u) | (dt ? 1u << 25 : 0u) | (qsc << 16) | fb;
}
inline u32 idec(unsigned qsc, bool dtd = false, bool ofm_rgb16 = false, bool dte = false, unsigned fb = 0) {
    return 0x10000000u | (ofm_rgb16 ? 1u << 27 : 0u) | (dte ? 1u << 26 : 0u) | (dtd ? 1u << 24 : 0u) | (qsc << 16) | fb;
}
inline u32 vdec(unsigned tbl, unsigned fb = 0) { return 0x30000000u | (tbl << 26) | fb; }
inline u32 fdec(unsigned fb) { return 0x40000000u | fb; }

// The six DC-only intra blocks used by several tests (hand-derived; README "Tests"):
//   Y0 size 2 (B.12 '01') diff '10' = +2   -> pred 128 -> 130, EOB (B.14 '10')
//   Y1 size 0 (B.12 '100')                 -> 130,        EOB
//   Y2 size 1 (B.12 '00')  diff '0'  = -1  -> 129,        EOB
//   Y3 size 3 (B.12 '101') diff '101' = +5 -> 134,        EOB
//   Cb size 4 (B.13 '1110') diff '0101' = 5 + 1 - 16 = -10 -> 128 - 10 = 118, EOB
//   Cr size 5 (B.13 '11110') diff '10100' = +20 -> 148, EOB
// 46 bits. With intra_dc_precision 0 each F[0][0] = 8 x DC; mismatch control sets F[7][7] = 1 (|its basis| <= 0.241), so
// every sample of each block is exactly the DC value.
inline void put_dc_only_blocks(Bits& b) {
    b.s("01 10 10").s("100 10").s("00 0 10").s("101 101 10").s("1110 0101 10").s("11110 10100 10");
}
inline constexpr int kDcY[4] = {130, 130, 129, 134};
inline constexpr int kDcCb = 118, kDcCr = 148;

} // namespace it
