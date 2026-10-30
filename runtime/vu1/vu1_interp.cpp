// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/src/vu_micro.cpp (run, upper, lower, commit, set_flags,
// mac_flags, xgkick, BranchView, read_q, q_delay_of, reset), runtime/include/ps2/vu_ops.hpp (FlagPipe, clip_value,
// u2f/f2u, the ERCPR approximation) and runtime/include/ps2/vu.hpp (div, rsqrt), MIT; adapted for p3fes-port
// (p3fes::vu1 namespace, VU1State with u32 bit-pattern registers, our decoder's UpperOp/LowerOp tables instead of raw
// switches, p3fes/ee/fpu.h as the float datapath (upstream's exact path), traps instead of stderr reports for
// encodings outside the census set, IGifSink for gif::transfer, per-instance state instead of globals).
#include "p3fes/vu1/vu1_interp.h"

#include "p3fes/ee/fpu.h"
#include "p3fes/vu1/vu1_aot.h"
#include "p3fes/vu1/vu1_profile.h"
#include "p3fes/state_io.h"
#include "vu1_qtiming.h"
#include "vu1_semantics.h"

#include <algorithm>
#include <bit>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace p3fes::vu1 {

namespace fp = ::p3fes::ee::fpu;

// ---------------------------------------------------------------------------------------------------------------
// MicroMemory
// ---------------------------------------------------------------------------------------------------------------
u32 MicroMemory::lower_word(u32 byte_pc) const noexcept {
    u32 v;
    std::memcpy(&v, bytes_.data() + (byte_pc & kMicroMask & ~7u), 4);
    return v;
}

u32 MicroMemory::upper_word(u32 byte_pc) const noexcept {
    u32 v;
    std::memcpy(&v, bytes_.data() + (byte_pc & kMicroMask & ~7u) + 4, 4);
    return v;
}

// The game re-uploads the same programs on every RenderWare pipeline switch: the generation (which the decode,
// residency and Q caches key on) moves only when a byte actually changes. Writes of more than 16 KiB keep the
// byte-loop semantics (later bytes win at a wrapped address).
void MicroMemory::write(u32 byte_offset, std::span<const u8> src) noexcept {
    if (src.size() > kMicroBytes) {
        for (std::size_t k = 0; k < src.size(); ++k) bytes_[(byte_offset + k) & kMicroMask] = src[k];
        ++generation_;
        return;
    }
    const u32 at = byte_offset & kMicroMask;
    const std::size_t first = std::min<std::size_t>(src.size(), kMicroBytes - at), rest = src.size() - first;
    const bool same = std::memcmp(bytes_.data() + at, src.data(), first) == 0 &&
                      (rest == 0 || std::memcmp(bytes_.data(), src.data() + first, rest) == 0);
    if (same) return;
    std::memcpy(bytes_.data() + at, src.data(), first);
    if (rest) std::memcpy(bytes_.data(), src.data() + first, rest);
    ++generation_;
}

void MicroMemory::clear() noexcept {
    bytes_.fill(0);
    ++generation_;
}

std::string_view to_string(TrapKind kind) noexcept {
    switch (kind) {
    case TrapKind::None: return "none";
    case TrapKind::UndefinedUpper: return "undefined upper encoding";
    case TrapKind::UndefinedLower: return "undefined lower encoding";
    case TrapKind::UncensusedUpper: return "upper op outside the census set";
    case TrapKind::UncensusedLower: return "lower op outside the census set";
    case TrapKind::DebugFlag: return "M/D/T flag set";
    }
    return "?";
}

using namespace sem;

// ---------------------------------------------------------------------------------------------------------------
// Caches keyed on the micro-memory generation.
// ---------------------------------------------------------------------------------------------------------------
struct VU1Interpreter::Caches {
    u64 generation = 0;
    std::array<DecodedPair, kMicroPairs> decoded{};
    std::array<u8, kMicroPairs> q_kind_valid{};
    std::array<detail::QRead, kMicroPairs> q_kind{};
    std::array<u8, kMicroPairs> q_delay_valid{};
    std::array<u32, kMicroPairs> q_delay{};
    std::vector<detail::Jump> jumps;
    std::array<u128, kDataQwords> kick{};
};

struct VU1Interpreter::Host final : AotHost {
    explicit Host(VU1Interpreter& v) : vu(v) {}
    void xgkick(u32 qword_addr) override { vu.xgkick(qword_addr); }
    VU1Interpreter& vu;
};

namespace {
struct CaptureSink final : IGifSink {
    std::vector<std::vector<u128>> packets;
    void kick(std::span<const u128> q) override { packets.emplace_back(q.begin(), q.end()); }
};
} // namespace

struct VU1Interpreter::DiffScratch {
    VU1State before{}, oracle{};
    CaptureSink a, b;
    u32 reported = 0;
};

VU1Interpreter::VU1Interpreter(IGifSink* sink) : sink_(sink), caches_(std::make_unique<Caches>()) {}
VU1Interpreter::~VU1Interpreter() = default;

void VU1Interpreter::set_mode(VU1Mode mode) {
    mode_ = mode;
    if (mode != VU1Mode::Interp && !aot_index_) aot_index_ = std::make_unique<AotIndex>();
    if (mode == VU1Mode::Diff && !diff_) diff_ = std::make_unique<DiffScratch>();
}

void VU1Interpreter::reset() noexcept {
    for (auto& v : s_.vf) v[0] = v[1] = v[2] = v[3] = 0;
    s_.vf[0][3] = fp::kOne;
    std::memset(s_.vi, 0, sizeof s_.vi);
    std::memset(s_.acc, 0, sizeof s_.acc);
    s_.q = s_.p = s_.i = s_.r = 0;
    s_.mac = s_.status = s_.clip = 0;
    s_.top = s_.itop = 0;
    s_.pc = 0;
    s_.npc = 8;
    s_.tpc = 0;
    s_.running = false;
    s_.ending = false;
    std::memset(s_.vi_before, 0, sizeof s_.vi_before);
    s_.vi_delay_live = false;
    s_.pipe = FlagPipe{};
    trap_ = {};
}

void VU1Interpreter::state(StateIo& io) {
    io.section("vu1");
    io.expect(static_cast<u64>(sizeof(VU1State)), "VU1State layout");
    io.raw(&s_, sizeof s_);  // plain data: registers, flag pipeline, micro memory (+ its generation), data memory
    io(stats_, aot_stats_);
    if (io.loading()) {
        // Derived from micro memory: rebuilt on the next fetch / residency check.
        caches_->generation = 0;
        if (aot_index_) *aot_index_ = AotIndex{};
        trap_ = {};
    }
}

void VU1Interpreter::load_micro(u32 byte_offset, std::span<const u8> bytes) noexcept {
    s_.micro.write(byte_offset, bytes);
    if (profile_) ++profile_->micro_writes;
}

void VU1Interpreter::sync_caches() {
    Caches& c = *caches_;
    if (c.generation == s_.micro.generation()) return;
    const u64 t0 = profile_ ? vu1_now_ns() : 0;
    for (u32 k = 0; k < kMicroPairs; ++k)
        c.decoded[k] = decode_pair(s_.micro.lower_word(k * 8u), s_.micro.upper_word(k * 8u));
    c.q_kind_valid.fill(0);
    c.q_delay_valid.fill(0);
    c.jumps = detail::collect_jumps(detail::Code(c.decoded));
    c.generation = s_.micro.generation();
    if (profile_) {
        ++profile_->rebuilds;
        profile_->rebuild_ns += vu1_now_ns() - t0;
    }
}

const DecodedPair& VU1Interpreter::fetch(u32 byte_pc) {
    sync_caches();
    return caches_->decoded[(byte_pc & kMicroMask) >> 3];
}

void VU1Interpreter::flush_q() noexcept {
    if (!s_.pipe.q_pending) return;
    s_.q = s_.pipe.q_value;
    s_.pipe.q_pending = false;
}

// A Q read sees the pending result when the static model says so (New), never (Old), or once the pair counter has
// reached its ready time (Dynamic). Upstream read_q.
void VU1Interpreter::read_q(u32 pc, const DecodedPair& d) {
    if (!s_.pipe.q_pending || !detail::reads_q(d.upper)) return;
    Caches& c = *caches_;
    const u32 k = (pc & kMicroMask) >> 3;
    if (!c.q_kind_valid[k]) {
        const u64 t0 = profile_ ? vu1_now_ns() : 0;
        c.q_kind[k] = detail::q_read_kind(detail::Code(c.decoded), c.jumps, pc);
        c.q_kind_valid[k] = 1;
        if (profile_) {
            ++profile_->q_kind_calls;
            profile_->q_kind_ns += vu1_now_ns() - t0;
        }
    }
    if (c.q_kind[k] == detail::QRead::New)
        flush_q();
    else if (c.q_kind[k] == detail::QRead::Dynamic && s_.pipe.t >= s_.pipe.q_ready)
        flush_q();
}

u32 VU1Interpreter::q_delay_of(u32 pc, u32 latency) {
    Caches& c = *caches_;
    const u32 k = (pc & kMicroMask) >> 3;
    if (!c.q_delay_valid[k]) {
        const u64 t0 = profile_ ? vu1_now_ns() : 0;
        c.q_delay[k] = detail::q_delay(detail::Code(c.decoded), pc, latency);
        c.q_delay_valid[k] = 1;
        if (profile_) {
            ++profile_->q_delay_calls;
            profile_->q_delay_ns += vu1_now_ns() - t0;
        }
    }
    return c.q_delay[k];
}

// XGKICK: walk the GIF tag chain from `qword_addr` to the first EOP tag and hand the packet to the sink. Body size
// per tag (GS User's Manual): PACKED nloop*nreg, REGLIST ceil(nloop*nreg/2), IMAGE/disabled nloop; nreg 0 = 16.
void VU1Interpreter::xgkick(u32 qword_addr) {
    auto& buf = caches_->kick;
    u32 q = qword_addr & (kDataQwords - 1u), count = 0;
    bool done = false;
    while (!done && count < kDataQwords) {
        u128 tag;
        std::memcpy(&tag, qword(s_, q), 16);
        buf[count++] = tag;
        q = (q + 1u) & (kDataQwords - 1u);
        const u64 t0 = tag.u64[0];
        const u32 nloop = static_cast<u32>(t0 & 0x7FFFu);
        const bool eop = ((t0 >> 15) & 1u) != 0;
        const u32 flg = static_cast<u32>(t0 >> 58) & 3u;
        u32 nreg = static_cast<u32>(t0 >> 60) & 0xFu;
        if (!nreg) nreg = 16;
        const u32 body = flg == 0 ? nloop * nreg : flg == 1 ? (nloop * nreg + 1u) / 2u : nloop;
        for (u32 k = 0; k < body && count < kDataQwords; ++k) {
            std::memcpy(&buf[count++], qword(s_, q), 16);
            q = (q + 1u) & (kDataQwords - 1u);
        }
        done = eop;
    }
    ++stats_.kicks;
    stats_.kick_qwords += count;
    if (!done) ++stats_.kicks_without_eop;
    if (sink_) {
        if (profile_) {
            const u64 t0 = vu1_now_ns();
            sink_->kick(std::span<const u128>(buf.data(), count));
            profile_->kick_ns_pending += vu1_now_ns() - t0;
        } else {
            sink_->kick(std::span<const u128>(buf.data(), count));
        }
    }
}

// One lower op (upstream `lower()`); returns true when it redirects the PC (`target` = new npc).
bool VU1Interpreter::lower(const DecodedPair& d, u32 pc, u32& target) {
    VU1State& r = s_;
    const LowerInsn& l = d.lower;
    const u32 dest = l.dest;
    const u32 it = l.it & 15u, is = l.is & 15u, id = l.id & 15u; // vi fields use the low 4 bits
    const u32 ft = l.it, fs = l.is;                               // vf fields use all 5
    const u32 imm11 = static_cast<u32>(static_cast<s32>(l.imm11));
    const u16* bvi = r.vi_delay_live ? r.vi_before : r.vi; // what a conditional branch reads
    const auto store_vi = [&](u32 index, u32 v) {
        if (index) r.vi[index] = static_cast<u16>(v);
    };
    const auto load_lanes = [&](u32 reg, const u8* q) {
        if (!reg) return;
        for (int i = 0; i < 4; ++i)
            if (lane(dest, i)) std::memcpy(&r.vf[reg][i], q + i * 4, 4);
    };
    const auto store_lanes = [&](u8* q, const u32 (&v)[4]) {
        for (int i = 0; i < 4; ++i)
            if (lane(dest, i)) std::memcpy(q + i * 4, &v[i], 4);
    };
    const auto load_vi_lane = [&](u32 reg, const u8* q) { // first destination lane, low 16 bits
        for (int i = 0; i < 4; ++i)
            if (lane(dest, i)) {
                u16 v;
                std::memcpy(&v, q + i * 4, 2);
                store_vi(reg, v);
                break;
            }
    };
    const auto store_vi_lanes = [&](u8* q, u32 v) {
        for (int i = 0; i < 4; ++i)
            if (lane(dest, i)) std::memcpy(q + i * 4, &v, 4);
    };
    const auto end_q = [&](u32 value, u32 latency) {
        r.pipe.q_value = value;
        r.pipe.q_ready = r.pipe.t + latency;
        r.pipe.q_pending = true;
    };
    const auto branch_to = [&](u32 to) {
        target = to & kMicroMask;
        return true;
    };

    switch (l.op) {
    case L::NOP: return false;
    case L::IADD: store_vi(id, r.vi[is] + r.vi[it]); return false;
    case L::ISUB: store_vi(id, r.vi[is] - r.vi[it]); return false;
    case L::IADDI: store_vi(it, r.vi[is] + static_cast<u32>(static_cast<s32>(l.imm5))); return false;
    case L::IAND: store_vi(id, r.vi[is] & r.vi[it]); return false;
    case L::IOR: store_vi(id, r.vi[is] | r.vi[it]); return false;
    case L::IADDIU: store_vi(it, r.vi[is] + l.imm15); return false;
    case L::ISUBIU: store_vi(it, r.vi[is] - l.imm15); return false;
    case L::MOVE:
        if (ft)
            for (int i = 0; i < 4; ++i)
                if (lane(dest, i)) r.vf[ft][i] = r.vf[fs][i];
        return false;
    case L::MR32:
        if (ft) {
            const u32 s[4] = {r.vf[fs][0], r.vf[fs][1], r.vf[fs][2], r.vf[fs][3]};
            for (int i = 0; i < 4; ++i)
                if (lane(dest, i)) r.vf[ft][i] = s[(i + 1) & 3];
        }
        return false;
    case L::LQ: load_lanes(ft, qword(r, r.vi[is] + imm11)); return false;
    case L::SQ: store_lanes(qword(r, r.vi[it] + imm11), r.vf[fs]); return false;
    case L::LQI:
        load_lanes(ft, qword(r, r.vi[is]));
        store_vi(is, r.vi[is] + 1u);
        return false;
    case L::SQI:
        store_lanes(qword(r, r.vi[it]), r.vf[fs]);
        store_vi(it, r.vi[it] + 1u);
        return false;
    case L::LQD:
        store_vi(is, r.vi[is] - 1u);
        load_lanes(ft, qword(r, r.vi[is]));
        return false;
    case L::SQD:
        store_vi(it, r.vi[it] - 1u);
        store_lanes(qword(r, r.vi[it]), r.vf[fs]);
        return false;
    case L::ILW: load_vi_lane(it, qword(r, r.vi[is] + imm11)); return false;
    case L::ISW: store_vi_lanes(qword(r, r.vi[is] + imm11), r.vi[it]); return false;
    case L::ILWR: load_vi_lane(it, qword(r, r.vi[is])); return false;
    case L::ISWR: store_vi_lanes(qword(r, r.vi[is]), r.vi[it]); return false;
    case L::MTIR: store_vi(it, r.vf[fs][l.fsf]); return false;
    case L::MFIR:
        if (ft) {
            const u32 v = static_cast<u32>(static_cast<s32>(static_cast<s16>(r.vi[is])));
            for (int i = 0; i < 4; ++i)
                if (lane(dest, i)) r.vf[ft][i] = v;
        }
        return false;
    case L::DIV: {
        flush_q(); // upstream begin_q: a previous result lands first; Q itself changes only when this one lands
        const fp::Result res = fp::div(r.vf[fs][l.fsf], r.vf[ft][l.ftf]);
        r.status = (r.status & ~0x30u) | (res.invalid ? 0x20u : 0u);
        end_q(res.value, q_delay_of(pc, 7));
        return false;
    }
    case L::RSQRT: {
        flush_q(); // upstream begin_q: a previous result lands first; Q itself changes only when this one lands
        const fp::Result res = fp::rsqrt(r.vf[fs][l.fsf], r.vf[ft][l.ftf]);
        r.status = (r.status & ~0x30u) | (res.invalid ? 0x20u : 0u);
        end_q(res.value, q_delay_of(pc, 13));
        return false;
    }
    case L::WAITQ: flush_q(); return false;
    case L::ERCPR: {
        const float v = u2f(r.vf[fs][l.fsf]);
        r.p = f2u(v != 0.0f ? 1.0f / v : 3.4e38f);
        return false;
    }
    case L::MFP:
        if (ft)
            for (int i = 0; i < 4; ++i)
                if (lane(dest, i)) r.vf[ft][i] = r.p;
        return false;
    case L::XTOP: store_vi(it, r.top); return false;
    case L::XITOP: store_vi(it, r.itop); return false;
    case L::XGKICK: xgkick(r.vi[is]); return false;
    case L::FCSET:
        r.clip = l.imm24;
        pipe_set_clip(r.pipe, r.clip, r.pipe.t - 4u);
        return false;
    case L::FCAND: store_vi(1, (pipe_clip(r.pipe) & l.imm24) ? 1u : 0u); return false;
    case L::FCOR: store_vi(1, ((pipe_clip(r.pipe) | l.imm24) & 0xFFFFFFu) == 0xFFFFFFu ? 1u : 0u); return false;
    case L::FCGET: store_vi(it, pipe_clip(r.pipe) & 0xFFFu); return false;
    case L::FMAND: store_vi(it, pipe_mac(r.pipe) & r.vi[is]); return false;
    case L::B: return branch_to(branch_target(l, pc));
    case L::BAL:
        store_vi(it, (pc + 16u) / 8u);
        return branch_to(branch_target(l, pc));
    case L::JR: return branch_to(static_cast<u32>(r.vi[is]) * 8u);
    case L::IBEQ: return bvi[is] == bvi[it] ? branch_to(branch_target(l, pc)) : false;
    case L::IBNE: return bvi[is] != bvi[it] ? branch_to(branch_target(l, pc)) : false;
    case L::IBLTZ: return static_cast<s16>(bvi[is]) < 0 ? branch_to(branch_target(l, pc)) : false;
    case L::IBGTZ: return static_cast<s16>(bvi[is]) > 0 ? branch_to(branch_target(l, pc)) : false;
    case L::IBLEZ: return static_cast<s16>(bvi[is]) <= 0 ? branch_to(branch_target(l, pc)) : false;
    case L::IBGEZ: return static_cast<s16>(bvi[is]) >= 0 ? branch_to(branch_target(l, pc)) : false;
    default:
        // Unreachable: step() traps on every op outside the census set before executing the pair.
        return false;
    }
}

void VU1Interpreter::start(u32 byte_pc) noexcept {
    s_.pc = byte_pc & kMicroMask & ~7u;
    s_.npc = (s_.pc + 8u) & kMicroMask;
    s_.running = true;
    s_.ending = false;
    s_.vi_delay_live = false;
    s_.pipe = FlagPipe{};
    pipe_start(s_.pipe, s_);
    trap_ = {};
}

RunResult VU1Interpreter::step() {
    if (!s_.running) return {RunStatus::Idle, 0};
    const u32 current = s_.pc & kMicroMask;
    const DecodedPair& d = fetch(current);

    TrapKind kind = TrapKind::None;
    if (d.m || d.d || d.t)
        kind = TrapKind::DebugFlag;
    else if (d.upper.op == U::Unknown)
        kind = TrapKind::UndefinedUpper;
    else if (d.lower.op == L::Unknown)
        kind = TrapKind::UndefinedLower;
    else if (!in_census(d.upper.op))
        kind = TrapKind::UncensusedUpper;
    else if (!in_census(d.lower.op))
        kind = TrapKind::UncensusedLower;
    if (kind != TrapKind::None) {
        trap_ = Trap{kind, current, d.lo, d.hi, mnemonic(d.upper.op), mnemonic(d.lower.op)};
        s_.running = false;
        return {RunStatus::Trapped, 0};
    }

    s_.pc = s_.npc & kMicroMask;
    s_.npc = (s_.npc + 8u) & kMicroMask;
    ++s_.pipe.t;
    read_q(current, d);
    const UpperOut out = compute_upper(s_, d.upper);

    u16 was[16];
    std::memcpy(was, s_.vi, sizeof was);
    if (d.i) {
        s_.i = d.lo; // LOI
    } else {
        u32 target = s_.npc;
        if (lower(d, current, target)) s_.npc = target;
    }
    std::memcpy(s_.vi_before, was, sizeof was);
    s_.vi_delay_live = !d.i && !detail::branch_delay_exempt(d.lower.op);

    if (out.target > 0) {
        u32(&dst)[4] = out.target == kAcc ? s_.acc : s_.vf[out.target];
        for (int i = 0; i < 4; ++i)
            if (lane(out.dest, i)) dst[i] = out.value[i];
    }
    if (out.target >= 0 && out.flags) {
        set_flags(s_, out.value, out.dest);
        pipe_set_mac(s_.pipe, s_.mac, s_.status);
    }
    if (out.has_clip) {
        s_.clip = out.clip;
        pipe_set_clip(s_.pipe, out.clip, s_.pipe.t);
    }
    s_.vf[0][0] = s_.vf[0][1] = s_.vf[0][2] = 0;
    s_.vf[0][3] = fp::kOne;
    s_.vi[0] = 0;
    ++stats_.pairs;

    if (s_.ending) {
        flush_q();
        s_.tpc = s_.pc;
        s_.running = false;
        s_.ending = false;
        return {RunStatus::Ended, 1};
    }
    if (d.e) s_.ending = true;
    return {RunStatus::Running, 1};
}

RunResult VU1Interpreter::run(u64 step_limit) {
    RunResult total{RunStatus::Idle, 0};
    if (!s_.running) return total;
    while (total.steps < step_limit) {
        const RunResult r = step();
        total.steps += r.steps;
        if (r.status != RunStatus::Running) {
            total.status = r.status;
            return total;
        }
    }
    total.status = RunStatus::StepLimit;
    return total;
}

RunResult VU1Interpreter::mscal(u32 imm, u64 step_limit) {
    if (profile_) return profiled_run(imm * 8u, step_limit);
    return exec_run(imm * 8u, step_limit);
}

RunResult VU1Interpreter::mscnt(u64 step_limit) {
    if (profile_) return profiled_run(s_.tpc, step_limit);
    return exec_run(s_.tpc, step_limit);
}

RunResult VU1Interpreter::exec_run(u32 byte_pc, u64 step_limit) {
    switch (mode_) {
    case VU1Mode::Aot: return aot_run(byte_pc, step_limit);
    case VU1Mode::Diff: return diff_run(byte_pc, step_limit);
    case VU1Mode::Interp: break;
    }
    start(byte_pc);
    return run(step_limit);
}

// AotQVerifier: the interpreter's own Q-read classification on the real micro memory (its decode cache) for every
// compiled reader that enumerated one of `targets`; all must equal the compiled kind.
bool VU1Interpreter::verify_q(void* ctx, const AotProgram& p, const u64* targets) {
    VU1Interpreter& vu = *static_cast<VU1Interpreter*>(ctx);
    vu.sync_caches();
    Caches& c = *vu.caches_;
    for (u32 r = 0; r < p.qreader_count; ++r) {
        const AotQReader& q = p.qreaders[r];
        bool affected = false;
        for (u32 n = 0; n < q.count && !affected; ++n) {
            const u32 node = p.qnodes[q.first + n];
            affected = ((targets[node / 64] >> (node % 64)) & 1u) != 0;
        }
        if (!affected) continue;
        const detail::QRead kind = detail::q_read_kind(detail::Code(c.decoded), c.jumps, q.pair * 8u);
        if (static_cast<u8>(kind) != q.kind) return false;
    }
    return true;
}

// The compiled program when one is resident; the interpreter otherwise and for whatever a bail-out leaves.
RunResult VU1Interpreter::aot_run(u32 byte_pc, u64 step_limit) {
    start(byte_pc);
    const AotProgram* p = aot_cpu_ok() ? aot_index_->resident(s_.micro, &VU1Interpreter::verify_q, this) : nullptr;
    if (!p) {
        ++aot_stats_.interp_runs;
        u64 head;
        std::memcpy(&head, s_.micro.bytes().data(), 8);
        for (VU1AotStats::InterpImage& im : aot_stats_.interp_images)
            if (im.head == head || im.runs == 0) {
                im.head = head;
                ++im.runs;
                break;
            }
        return run(step_limit);
    }
    Host host(*this);
    const AotResult r = p->fn(s_, host, s_.pc, step_limit);
    ++aot_stats_.compiled_runs;
    aot_stats_.compiled_pairs += r.steps;
    stats_.pairs += r.steps;
    if (r.ended) return {RunStatus::Ended, r.steps};
    ++aot_stats_.bails;
    RunResult rest = run(step_limit - r.steps);
    rest.steps += r.steps;
    return rest;
}

namespace {
// The MAC and clip rings (FlagPipe mac_* / clip_* / mh / ch) are not compared: the compiled code inserts only the
// entries some reader can see (flag liveness across blocks, vu1_aotgen.cpp; docs/ANALYSIS/24 §8). After a run ends
// they are dead (start() rebuilds the pipe from mac / status / clip, which are compared); within a run, every value a
// reader takes from them lands in a vi register, which is compared, and the analysis follows the interpreter's paths
// after a hand-over. pipe.t and the Q pipe are compared.
bool same_state(const VU1State& a, const VU1State& b, const char*& what) {
#define P3FES_VU1_CMP(field)                                                   \
    if (std::memcmp(&a.field, &b.field, sizeof a.field) != 0) {                \
        what = #field;                                                         \
        return false;                                                          \
    }
    P3FES_VU1_CMP(vf) P3FES_VU1_CMP(vi) P3FES_VU1_CMP(acc) P3FES_VU1_CMP(q) P3FES_VU1_CMP(p) P3FES_VU1_CMP(i)
    P3FES_VU1_CMP(r) P3FES_VU1_CMP(mac) P3FES_VU1_CMP(status) P3FES_VU1_CMP(clip) P3FES_VU1_CMP(top)
    P3FES_VU1_CMP(itop) P3FES_VU1_CMP(pc) P3FES_VU1_CMP(npc) P3FES_VU1_CMP(tpc) P3FES_VU1_CMP(running)
    P3FES_VU1_CMP(ending) P3FES_VU1_CMP(vi_before) P3FES_VU1_CMP(vi_delay_live) P3FES_VU1_CMP(pipe.t)
    P3FES_VU1_CMP(pipe.q_value) P3FES_VU1_CMP(pipe.q_ready) P3FES_VU1_CMP(pipe.q_pending) P3FES_VU1_CMP(data)
#undef P3FES_VU1_CMP
    return true;
}} // namespace

// Interpreter and Aot path from the same state; the interpreter's outcome is kept and forwarded.
RunResult VU1Interpreter::diff_run(u32 byte_pc, u64 step_limit) {
    DiffScratch& d = *diff_;
    IGifSink* const real = sink_;
    const VU1Stats stats0 = stats_;
    d.before = s_;
    d.a.packets.clear();
    d.b.packets.clear();
    sink_ = &d.a;
    start(byte_pc);
    const RunResult ra = run(step_limit);
    const Trap trap_a = trap_;
    const VU1Stats stats_a = stats_;
    d.oracle = s_;
    s_ = d.before;
    stats_ = stats0;
    sink_ = &d.b;
    const RunResult rb = aot_run(byte_pc, step_limit);
    const char* what = nullptr;
    bool same = same_state(d.oracle, s_, what);
    if (same && (ra.status != rb.status || ra.steps != rb.steps)) same = false, what = "run status/steps";
    if (same && (trap_a.kind != trap_.kind || trap_a.pc != trap_.pc)) same = false, what = "trap";
    if (same && (stats_a.pairs != stats_.pairs || stats_a.kicks != stats_.kicks)) same = false, what = "stats";
    if (same) {
        if (d.a.packets.size() != d.b.packets.size()) same = false, what = "kick count";
        for (std::size_t k = 0; same && k < d.a.packets.size(); ++k)
            if (d.a.packets[k].size() != d.b.packets[k].size() ||
                std::memcmp(d.a.packets[k].data(), d.b.packets[k].data(), d.a.packets[k].size() * sizeof(u128)) != 0)
                same = false, what = "kicked packet";
    }
    ++aot_stats_.diff_runs;
    if (!same) {
        ++aot_stats_.diff_mismatches;
        if (d.reported < 10) {
            ++d.reported;
            std::fprintf(stderr, "p3fes vu1: AOT/interpreter mismatch #%llu at start pc 0x%04X: %s\n",
                         static_cast<unsigned long long>(aot_stats_.diff_mismatches), byte_pc & kMicroMask, what);
        }
    }
    s_ = d.oracle;
    trap_ = trap_a;
    stats_ = stats_a;
    sink_ = real;
    if (sink_)
        for (const auto& pkt : d.a.packets) sink_->kick(std::span<const u128>(pkt.data(), pkt.size()));
    return ra;
}

// MSCAL/MSCNT with the run attributed to (resident program, start pc) in the profile.
RunResult VU1Interpreter::profiled_run(u32 byte_pc, u64 step_limit) {
    const int prog = profile_->programs.identify(s_.micro); // outside the timed region
    const bool cold = caches_->generation != s_.micro.generation();
    const VU1Stats before = stats_;
    const std::pair<int, u32> key{prog, byte_pc & kMicroMask & ~7u};
    if (profile_->capture_per_key) {
        u32& n = profile_->capture_counts[key];
        if (n < profile_->capture_per_key) {
            const std::string name = prog >= 0 ? profile_->programs.name(prog) : std::string("unknown");
            char file[160];
            std::snprintf(file, sizeof file, "/%s_%04x_%03u.vu1in", name.c_str(), key.second, n);
            if (save_run_input(profile_->capture_dir + file, s_, byte_pc, name)) ++profile_->captured;
            ++n;
        }
    }
    profile_->kick_ns_pending = 0;
    const u64 t0 = vu1_now_ns();
    const RunResult r = exec_run(byte_pc, step_limit);
    const u64 dt = vu1_now_ns() - t0;
    c_kick_ns_ = profile_->kick_ns_pending;
    VU1RunCounters& c = profile_->runs[key];
    ++c.runs;
    c.pairs += r.steps;
    c.kicks += stats_.kicks - before.kicks;
    c.kick_qwords += stats_.kick_qwords - before.kick_qwords;
    c.kick_ns += c_kick_ns_;
    c.ns += dt - c_kick_ns_;
    c.cold += cold ? 1u : 0u;
    return r;
}

} // namespace p3fes::vu1
