// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/vu_ops.hpp (VfUse/vf_use, issue, retire,
// q_delay, q_unit_latency, waits_q, reads_q, q_read_kind, branch_delay_exempt), MIT; adapted for p3fes-port (reads the
// decoder's DecodedPair fields instead of re-parsing raw words; jump list built once per code generation).
#include "vu1_qtiming.h"

#include <algorithm>

namespace p3fes::vu1::detail {
namespace {

struct VfUse {
    u8 reg[4] = {}, mask[4] = {}, wreg[2] = {}, wmask[2] = {};
    unsigned n = 0, wn = 0;
    u16 vi_reads = 0;
    unsigned vi_load = 0;

    void read_vi(unsigned r) noexcept { vi_reads = static_cast<u16>(vi_reads | ((1u << (r & 15u)) & ~1u)); }
    void read(unsigned r, unsigned m) noexcept {
        if (r && m && n < 4) {
            reg[n] = static_cast<u8>(r);
            mask[n++] = static_cast<u8>(m);
        }
    }
    void write(unsigned r, unsigned m) noexcept {
        if (r && m && wn < 2) {
            wreg[wn] = static_cast<u8>(r);
            wmask[wn++] = static_cast<u8>(m);
        }
    }
};

// Operands of one pair for the interlock model. Undefined halves (which the interpreter traps on) read nothing.
VfUse vf_use(const DecodedPair& d) noexcept {
    VfUse u;
    const UpperInsn& up = d.upper;
    const unsigned dest = up.dest, ft = up.ft, fs = up.fs, fd = up.fd, bc = 8u >> up.bc, funct = up.funct;
    if (up.op != UpperOp::Unknown) {
        if (funct < 0x3C) {
            if (funct < 0x1C) {
                u.read(fs, dest);
                u.read(ft, bc);
            } else if (funct < 0x28) {
                u.read(fs, dest);
            } else if (funct == 0x2E) {
                u.read(fs, 0xE);
                u.read(ft, 0xE);
            } else {
                u.read(fs, dest);
                u.read(ft, dest);
            }
            u.write(fd, funct == 0x2E ? 0xEu : dest);
        } else {
            const unsigned index = up.index;
            if (index < 0x10 || (index >= 0x18 && index < 0x1C)) {
                u.read(fs, dest);
                u.read(ft, bc);
            } else if (index < 0x18 || index == 0x1D) {
                u.read(fs, dest);
                u.write(ft, dest);
            } else if (index == 0x1F) {
                u.read(fs, 0xE);
                u.read(ft, 1);
            } else if (index < 0x28) {
                u.read(fs, dest);
            } else if (index == 0x2E) {
                u.read(fs, 0xE);
                u.read(ft, 0xE);
            } else if (index < 0x2F) {
                u.read(fs, dest);
                u.read(ft, dest);
            }
        }
    }
    if (d.i || d.lower.op == LowerOp::Unknown) return u;
    const LowerInsn& lw = d.lower;
    const unsigned ldest = lw.dest, lft = lw.it, lfs = lw.is, fsf = 8u >> lw.fsf, ftf = 8u >> lw.ftf;
    const unsigned it = lw.it & 15u, is = lw.is & 15u, major = lw.opcode;
    if (major == 0x00 || major == 0x08 || major == 0x09 || major == 0x18 || major == 0x1A || major == 0x1B ||
        major == 0x24 || major == 0x25 || (major >= 0x2C && major <= 0x2F))
        u.read_vi(is);
    if (major == 0x01) u.read_vi(it);
    if (major == 0x04 || major == 0x05 || major == 0x28 || major == 0x29) u.read_vi(is);
    if (major == 0x05 || major == 0x28 || major == 0x29) u.read_vi(it);
    if (major == 0x04) u.vi_load = it;
    if (major == 0x40 && lw.funct < 0x3C) {
        const unsigned f = lw.funct;
        if (f == 0x30 || f == 0x31 || f == 0x32 || f == 0x34 || f == 0x35) u.read_vi(is);
        if (f == 0x30 || f == 0x31 || f == 0x34 || f == 0x35) u.read_vi(it);
    }
    if (major == 0x40 && lw.funct >= 0x3C) {
        const unsigned index = lw.index;
        if (index == 0x34 || index == 0x36 || index == 0x3D || index == 0x3E || index == 0x3F || index == 0x6C)
            u.read_vi(is);
        if (index == 0x35 || index == 0x37 || index == 0x3F) u.read_vi(it);
        if (index == 0x3E) u.vi_load = it;
    }
    if (major == 0x00) {
        u.write(lft, ldest);
    } else if (major == 0x01) {
        u.read(lfs, ldest);
    } else if (major == 0x40 && lw.funct >= 0x3C) {
        switch (lw.index) {
        case 0x30: u.read(lfs, ldest); u.write(lft, ldest); break;
        case 0x31: u.read(lfs, ((ldest >> 1) | (ldest << 3)) & 15u); u.write(lft, ldest); break;
        case 0x34: case 0x36: case 0x3D: case 0x40: case 0x41: case 0x64: u.write(lft, ldest); break;
        case 0x35: case 0x37: u.read(lfs, ldest); break;
        case 0x38: case 0x3A: u.read(lfs, fsf); u.read(lft, ftf); break;
        case 0x39: u.read(lft, ftf); break;
        case 0x3C: case 0x42: case 0x43: u.read(lfs, fsf); break;
        default: if (lw.index >= 0x70) u.read(lfs, 0xF); break;
        }
    }
    return u;
}

using Ready = u32[32][4];
using ViReady = u32[16];

u32 issue(const VfUse& u, u32 cycle, const Ready& ready, const ViReady& vi_ready) noexcept {
    for (unsigned i = 0; i < u.n; ++i)
        for (unsigned lane = 0; lane < 4; ++lane)
            if (u.mask[i] & (8u >> lane)) cycle = std::max(cycle, ready[u.reg[i]][lane]);
    for (unsigned r = 1; r < 16; ++r)
        if (u.vi_reads & (1u << r)) cycle = std::max(cycle, vi_ready[r]);
    return cycle;
}

void retire(const VfUse& u, u32 cycle, Ready& ready, ViReady& vi_ready) noexcept {
    for (unsigned i = 0; i < u.wn; ++i)
        for (unsigned lane = 0; lane < 4; ++lane)
            if (u.wmask[i] & (8u >> lane)) ready[u.wreg[i]][lane] = cycle + 4u;
    if (u.vi_load) vi_ready[u.vi_load] = cycle + 4u;
}

} // namespace

u32 q_unit_latency(const DecodedPair& d) noexcept {
    switch (d.lower.op) {
    case LowerOp::DIV: case LowerOp::SQRT: return 7u;
    case LowerOp::RSQRT: return 13u;
    default: return 0u;
    }
}

bool waits_q(const DecodedPair& d) noexcept { return d.lower.op == LowerOp::WAITQ; }

bool reads_q(const UpperInsn& u) noexcept {
    const unsigned op = u.funct < 0x3C ? u.funct : u.index;
    return u.op != UpperOp::Unknown && (op == 0x1C || op == 0x20 || op == 0x21 || op == 0x24 || op == 0x25);
}

bool branch_delay_exempt(LowerOp op) noexcept {
    switch (op) {
    case LowerOp::FCEQ: case LowerOp::FCAND: case LowerOp::FCOR: case LowerOp::FSEQ: case LowerOp::FSAND:
    case LowerOp::FSOR: case LowerOp::FMEQ: case LowerOp::FMAND: case LowerOp::FMOR: case LowerOp::FCGET:
    case LowerOp::BAL: case LowerOp::JALR:
        return true;
    default:
        return false;
    }
}

std::vector<Jump> collect_jumps(Code code) {
    std::vector<Jump> jumps;
    for (u32 a = 0; a < kMicroBytes; a += 8) {
        const DecodedPair& d = at(code, a);
        if (is_branch(d.lower.op) && !is_jump_register(d.lower.op))
            jumps.emplace_back(branch_target(d.lower, a), (a + 8u) & kMicroMask);
    }
    return jumps;
}

u32 q_delay(Code code, u32 pc, u32 latency, Footprint* footprint) {
    Ready ready = {};
    ViReady vi_ready = {};
    u32 cycle = 0, issued = 0;
    for (int k = -3; k <= static_cast<int>(latency); ++k) {
        const u32 a = (pc + static_cast<u32>(k) * 8u) & kMicroMask;
        if (footprint) footprint->reads.push_back(a);
        const VfUse u = vf_use(at(code, a));
        cycle = issue(u, cycle + 1u, ready, vi_ready);
        if (k == 0)
            issued = cycle;
        else if (k > 0 && cycle >= issued + latency)
            return static_cast<u32>(k);
        retire(u, cycle, ready, vi_ready);
    }
    return latency;
}

QRead q_read_kind(Code code, std::span<const Jump> jumps, u32 pc, Footprint* footprint) {
    pc &= kMicroMask;
    const auto at = [&](Code c, u32 byte_pc) -> const DecodedPair& {
        if (footprint) footprint->reads.push_back(byte_pc & kMicroMask);
        return detail::at(c, byte_pc);
    };
    {
        const DecodedPair& d = at(code, pc);
        if (waits_q(d) || q_unit_latency(d)) return QRead::New;
    }
    const auto preds = [&](u32 y) {
        if (footprint) footprint->expanded.push_back(y & kMicroMask);
        std::vector<u32> out;
        const DecodedPair& before = at(code, y - 16u);
        const bool jumped = is_branch(before.lower.op) &&
                            (is_unconditional(before.lower.op) || is_jump_register(before.lower.op));
        if (!jumped && !before.e) out.push_back((y - 8u) & kMicroMask);
        for (const auto& [target, slot] : jumps)
            if (target == (y & kMicroMask)) out.push_back(slot);
        return out;
    };
    const auto complete = [&](const std::vector<u32>& back, u32 latency) {
        std::vector<u32> order;
        const u32 producer = back.back();
        for (u32 k = 3; k > 0; --k) order.push_back((producer - 8u * k) & kMicroMask);
        order.insert(order.end(), back.rbegin(), back.rend());
        Ready ready = {};
        ViReady vi_ready = {};
        u32 cycle = 0, issued = 0;
        for (std::size_t i = 0; i < order.size(); ++i) {
            const VfUse u = vf_use(at(code, order[i]));
            cycle = issue(u, cycle + 1u, ready, vi_ready);
            if (i == 3) issued = cycle;
            retire(u, cycle, ready, vi_ready);
        }
        return cycle >= issued + latency;
    };
    // Upstream quirk kept: the "both seen" early exit is only tested after a node expands its predecessors.
    bool any_new = false, any_old = false;
    unsigned budget = 4096;
    std::vector<std::vector<u32>> stack{{pc}};
    while (!stack.empty()) {
        if (!--budget) return QRead::Dynamic;
        const std::vector<u32> path = std::move(stack.back());
        stack.pop_back();
        const u32 here = path.back();
        if (path.size() > 1) {
            const DecodedPair& d = at(code, here);
            if (const u32 latency = q_unit_latency(d)) {
                (complete(path, latency) ? any_new : any_old) = true;
                continue;
            }
            if (waits_q(d) || path.size() > 15) {
                any_new = true;
                continue;
            }
        }
        const std::vector<u32> from = preds(here);
        if (from.empty()) any_new = true;
        for (const u32 p : from) {
            std::vector<u32> next = path;
            next.push_back(p);
            stack.push_back(std::move(next));
        }
        if (any_new && any_old) return QRead::Dynamic;
    }
    return any_old ? QRead::Old : QRead::New;
}

} // namespace p3fes::vu1::detail
