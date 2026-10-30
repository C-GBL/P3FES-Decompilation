// R3000 interpreter (r3000.h). Dispatch shape and the unaligned-access merge formulas after the MIT
// reference ps2-web-recomp runtime/src/iop/cpu.cpp @ c0f476e (THIRD_PARTY_NOTICES.md); the stop model,
// traps and host-call table are p3fes-port's.
#include "r3000.h"

#include "p3fes/prof.h"

#include <cstdint>
#include <cstring>

namespace p3fes::hle::sif::iop {

namespace {
inline u32 simm(u32 w) { return static_cast<u32>(static_cast<s32>(static_cast<s16>(w & 0xFFFFu))); }
inline u32 mask(u32 a) { return a & (detail::kIopRamSize - 1u); }
}  // namespace

R3000::R3000(detail::IopRam& ram) : ram_(ram), mem_(ram.at(0, detail::kIopRamSize)) {}

u32 R3000::register_host_call(std::string name, HostCall fn) {
    calls_.emplace_back(std::move(name), std::move(fn));
    return static_cast<u32>(calls_.size() - 1);
}

std::string_view R3000::host_call_name(u32 id) const {
    return id < calls_.size() ? std::string_view(calls_[id].first) : std::string_view("?");
}

u8 R3000::read8(u32 a) const { return mem_[mask(a)]; }
u16 R3000::read16(u32 a) const {
    u16 v;
    std::memcpy(&v, mem_ + mask(a & ~1u), 2);
    return v;
}
u32 R3000::read32(u32 a) const {
    u32 v;
    std::memcpy(&v, mem_ + mask(a & ~3u), 4);
    return v;
}
void R3000::write8(u32 a, u8 v) { mem_[mask(a)] = v; }
void R3000::write16(u32 a, u16 v) { std::memcpy(mem_ + mask(a & ~1u), &v, 2); }
void R3000::write32(u32 a, u32 v) { std::memcpy(mem_ + mask(a & ~3u), &v, 4); }

std::string R3000::c_string(u32 a, std::size_t max) const {
    std::string s;
    for (std::size_t i = 0; i < max; ++i) {
        const char ch = static_cast<char>(read8(a + static_cast<u32>(i)));
        if (!ch) break;
        s.push_back(ch);
    }
    return s;
}

u32 R3000::arg(unsigned i) const {
    if (i < 4) return s_.r[4 + i];
    return read32(s_.r[29] + 4u * i);  // the caller reserves the four home slots; arg 4 is at sp + 16
}

void R3000::trap(u32 pc, u32 word, std::string what) {
    trapped_ = true;
    trap_.stop = Stop::Trap;
    trap_.pc = pc;
    trap_.word = word;
    trap_.what = std::move(what);
}

bool R3000::check_addr(u32 a, u32 size, u32 pc, u32 word) {
    if ((a & (size - 1u)) != 0) {
        trap(pc, word, "misaligned access at " + detail::hex32(a));
        return false;
    }
    // kuseg/kseg0/kseg1 views of the 2 MiB RAM fold; the hardware window (kHwBase) and anything else
    // outside RAM traps -- libsd, the only register driver in the stack, is HLE'd.
    if ((a & 0x1FFFFFFFu) >= detail::kIopRamSize) {
        trap(pc, word, "access outside IOP RAM at " + detail::hex32(a));
        return false;
    }
    return true;
}

R3000::Result R3000::run(u64 budget) {
    const prof::Scope prof_zone(prof::Zone::IopCpu);
    stop_requested_ = false;
    trapped_ = false;
    R3000State& c = s_;
    u32* r = c.r;
    while (budget-- > 0) {
        const u32 pc = c.pc;
        if (pc == kExitSentinel) return Result{Stop::Sentinel, pc, 0, {}};
        if ((pc & 3u) != 0 || (pc & 0x1FFFFFFFu) >= detail::kIopRamSize) {
            return Result{Stop::Trap, pc, 0, "fetch outside IOP RAM at " + detail::hex32(pc)};
        }
        const u32 w = read32(pc);
        c.pc = c.npc;
        c.npc += 4;
        ++instructions_;
        const u32 rs = (w >> 21) & 31u, rt = (w >> 16) & 31u, rd = (w >> 11) & 31u, sa = (w >> 6) & 31u;
        const u32 op = w >> 26;
        switch (op) {
        case 0x00:
            switch (w & 63u) {
            case 0x00: r[rd] = r[rt] << sa; break;                                                          // sll
            case 0x02: r[rd] = r[rt] >> sa; break;                                                          // srl
            case 0x03: r[rd] = static_cast<u32>(static_cast<s32>(r[rt]) >> sa); break;                      // sra
            case 0x04: r[rd] = r[rt] << (r[rs] & 31u); break;                                               // sllv
            case 0x06: r[rd] = r[rt] >> (r[rs] & 31u); break;                                               // srlv
            case 0x07: r[rd] = static_cast<u32>(static_cast<s32>(r[rt]) >> (r[rs] & 31u)); break;           // srav
            case 0x08: c.npc = r[rs]; break;                                                                // jr
            case 0x09: { const u32 t = r[rs]; r[rd] = pc + 8; c.npc = t; break; }                           // jalr
            case 0x0C: trap(pc, w, "syscall"); break;
            case 0x0D: trap(pc, w, "break"); break;
            case 0x10: r[rd] = c.hi; break;                                                                 // mfhi
            case 0x11: c.hi = r[rs]; break;                                                                 // mthi
            case 0x12: r[rd] = c.lo; break;                                                                 // mflo
            case 0x13: c.lo = r[rs]; break;                                                                 // mtlo
            case 0x18: {                                                                                    // mult
                const s64 p = static_cast<s64>(static_cast<s32>(r[rs])) * static_cast<s32>(r[rt]);
                c.lo = static_cast<u32>(static_cast<u64>(p));
                c.hi = static_cast<u32>(static_cast<u64>(p) >> 32);
                break;
            }
            case 0x19: {                                                                                    // multu
                const u64 p = static_cast<u64>(r[rs]) * r[rt];
                c.lo = static_cast<u32>(p);
                c.hi = static_cast<u32>(p >> 32);
                break;
            }
            case 0x1A: {                                                                                    // div
                const s32 n = static_cast<s32>(r[rs]), d = static_cast<s32>(r[rt]);
                if (d == 0) { c.lo = n < 0 ? 1u : 0xFFFFFFFFu; c.hi = static_cast<u32>(n); }
                else if (n == INT32_MIN && d == -1) { c.lo = static_cast<u32>(INT32_MIN); c.hi = 0; }
                else { c.lo = static_cast<u32>(n / d); c.hi = static_cast<u32>(n % d); }
                break;
            }
            case 0x1B:                                                                                      // divu
                if (r[rt] == 0) { c.lo = 0xFFFFFFFFu; c.hi = r[rs]; }
                else { c.lo = r[rs] / r[rt]; c.hi = r[rs] % r[rt]; }
                break;
            case 0x20: case 0x21: r[rd] = r[rs] + r[rt]; break;   // add/addu (overflow exceptions not modelled)
            case 0x22: case 0x23: r[rd] = r[rs] - r[rt]; break;   // sub/subu
            case 0x24: r[rd] = r[rs] & r[rt]; break;
            case 0x25: r[rd] = r[rs] | r[rt]; break;
            case 0x26: r[rd] = r[rs] ^ r[rt]; break;
            case 0x27: r[rd] = ~(r[rs] | r[rt]); break;
            case 0x2A: r[rd] = static_cast<s32>(r[rs]) < static_cast<s32>(r[rt]) ? 1u : 0u; break;
            case 0x2B: r[rd] = r[rs] < r[rt] ? 1u : 0u; break;
            default: trap(pc, w, "reserved SPECIAL function"); break;
            }
            break;
        case 0x01: {  // REGIMM: bltz 0, bgez 1, bltzal 16, bgezal 17
            const bool link = (rt & 0x1Eu) == 0x10u;
            const bool taken = (rt & 1u) ? static_cast<s32>(r[rs]) >= 0 : static_cast<s32>(r[rs]) < 0;
            if (link) r[31] = pc + 8;
            if (taken) c.npc = pc + 4 + (simm(w) << 2);
            break;
        }
        case 0x02: c.npc = (pc & 0xF0000000u) | ((w & 0x03FFFFFFu) << 2); break;                  // j
        case 0x03: r[31] = pc + 8; c.npc = (pc & 0xF0000000u) | ((w & 0x03FFFFFFu) << 2); break;  // jal
        case 0x04: if (r[rs] == r[rt]) c.npc = pc + 4 + (simm(w) << 2); break;                     // beq
        case 0x05: if (r[rs] != r[rt]) c.npc = pc + 4 + (simm(w) << 2); break;                     // bne
        case 0x06: if (static_cast<s32>(r[rs]) <= 0) c.npc = pc + 4 + (simm(w) << 2); break;       // blez
        case 0x07: if (static_cast<s32>(r[rs]) > 0) c.npc = pc + 4 + (simm(w) << 2); break;        // bgtz
        case 0x08: case 0x09: r[rt] = r[rs] + simm(w); break;                                      // addi/addiu
        case 0x0A: r[rt] = static_cast<s32>(r[rs]) < static_cast<s32>(simm(w)) ? 1u : 0u; break;   // slti
        case 0x0B: r[rt] = r[rs] < simm(w) ? 1u : 0u; break;                                       // sltiu
        case 0x0C: r[rt] = r[rs] & (w & 0xFFFFu); break;
        case 0x0D: r[rt] = r[rs] | (w & 0xFFFFu); break;
        case 0x0E: r[rt] = r[rs] ^ (w & 0xFFFFu); break;
        case 0x0F: r[rt] = w << 16; break;                                                         // lui
        case 0x20: {  // lb
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 1, pc, w)) r[rt] = static_cast<u32>(static_cast<s32>(static_cast<s8>(read8(a))));
            break;
        }
        case 0x21: {  // lh
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 2, pc, w)) r[rt] = static_cast<u32>(static_cast<s32>(static_cast<s16>(read16(a))));
            break;
        }
        case 0x22: {  // lwl
            const u32 a = r[rs] + simm(w), shift = (3u - (a & 3u)) * 8u;
            if (!check_addr(a, 1, pc, w)) break;
            const u32 mem = read32(a & ~3u);
            r[rt] = (mem << shift) | (shift ? (r[rt] & ((1u << shift) - 1u)) : 0u);
            break;
        }
        case 0x23: {  // lw
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 4, pc, w)) r[rt] = read32(a);
            break;
        }
        case 0x24: {  // lbu
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 1, pc, w)) r[rt] = read8(a);
            break;
        }
        case 0x25: {  // lhu
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 2, pc, w)) r[rt] = read16(a);
            break;
        }
        case 0x26: {  // lwr
            const u32 a = r[rs] + simm(w), shift = (a & 3u) * 8u;
            if (!check_addr(a, 1, pc, w)) break;
            const u32 mem = read32(a & ~3u);
            r[rt] = (mem >> shift) | (shift ? (r[rt] & ~(0xFFFFFFFFu >> shift)) : 0u);
            break;
        }
        case 0x28: {  // sb
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 1, pc, w)) write8(a, static_cast<u8>(r[rt]));
            break;
        }
        case 0x29: {  // sh
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 2, pc, w)) write16(a, static_cast<u16>(r[rt]));
            break;
        }
        case 0x2A: {  // swl
            const u32 a = r[rs] + simm(w), shift = (3u - (a & 3u)) * 8u;
            if (!check_addr(a, 1, pc, w)) break;
            const u32 mem = read32(a & ~3u);
            write32(a & ~3u, (r[rt] >> shift) | (shift ? (mem & ~(0xFFFFFFFFu >> shift)) : 0u));
            break;
        }
        case 0x2B: {  // sw
            const u32 a = r[rs] + simm(w);
            if (check_addr(a, 4, pc, w)) write32(a, r[rt]);
            break;
        }
        case 0x2E: {  // swr
            const u32 a = r[rs] + simm(w), shift = (a & 3u) * 8u;
            if (!check_addr(a, 1, pc, w)) break;
            const u32 mem = read32(a & ~3u);
            write32(a & ~3u, (r[rt] << shift) | (shift ? (mem & ((1u << shift) - 1u)) : 0u));
            break;
        }
        case kHleOpcode: {
            const u32 id = w & kHleIdMask;
            if (id >= calls_.size()) {
                trap(pc, w, "host call id out of range");
                break;
            }
            // The stub was `jr ra; li $0, n`: return to the caller as the stub would have.
            c.pc = r[31];
            c.npc = c.pc + 4;
            r[0] = 0;
            ++host_calls_made_;
            {
                const prof::Scope prof_call(prof::Zone::Iop);
                calls_[id].second(*this);
            }
            r[0] = 0;
            if (trapped_) return trap_;
            if (stop_requested_) return Result{Stop::HostStop, c.pc, 0, {}};
            continue;
        }
        default:
            trap(pc, w, "reserved opcode");
            break;
        }
        r[0] = 0;
        if (trapped_) return trap_;
        if (stop_requested_) return Result{Stop::HostStop, c.pc, 0, {}};
    }
    return Result{Stop::Budget, c.pc, 0, {}};
}

}  // namespace p3fes::hle::sif::iop
