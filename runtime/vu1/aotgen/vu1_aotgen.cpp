// p3fes_vu1_aotgen: ahead-of-time translation of the game's VU1 microprograms to C++ (runtime/include/p3fes/vu1/
// vu1_aot.h, docs/ANALYSIS/24_vu1_acceleration.md).
//
// usage: p3fes_vu1_aotgen --dumps DIR --census symbols/vu1_micro_census.json --out DIR [--only VA,VA,...]
//
// Input: the microcode dumps `<code_va>.bin` (tools/ours/vu1/vu1_dump.py re-creates them from the ELF) and the
// census JSON for the program names. Output: `vu1_aot_<code_va>.cpp` per program and `vu1_aot_programs.cpp` (the
// table). The output embeds game code bytes: it is build output, never committed.
//
// Every pair is translated to the statements VU1Interpreter::step() executes for it, with the decoded fields as
// constants: pair counter, Q read (the interpreter's static classification, computed here with the same
// detail::q_read_kind), upper op into locals, branch condition on the branch-VI view, lower op, upper commit, MAC
// and clip flag pipe, E handling. Control flow: labels at the entry, branch targets, fall-throughs after delay
// slots, MSCNT resume points and every `iaddiu viN, vi00, imm` constant (the JR targets the programs build); one
// function per label block, a branch to the block's own label a loop inside it, JR a switch over the labels in the
// driver. Anything else bails out to the interpreter at a pair boundary (see vu1_aot.h).
//
// Round 3 (docs/ANALYSIS/24 §8): vf / ACC live in SSE locals and vi / clip in integer locals for a whole block
// (written back at its exits), float ops are host SSE under round toward zero with a per-lane exact fallback
// (vu1_aot_rt.h), and the MAC / clip flag rings get only the entries some reader can see (flag liveness across
// blocks, Gen::analyse_flags); readers whose entry was written earlier in the same block read a local.
#include "p3fes/vu1/vu1_decode.h"
#include "../vu1_qtiming.h"
#include "../vu1_semantics.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace p3fes;
using namespace p3fes::vu1;
namespace fs = std::filesystem;

namespace {

std::string va8(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "%08x", v);
    return b;
}

std::string hex(u32 v, int w = 0) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%0*X", w, v);
    return b;
}

struct Program {
    std::string name;
    u32 code_va = 0;
    std::vector<u8> image;
    u32 n = 0;
    std::vector<DecodedPair> d;
};

using sem::describe;
using sem::Kind;
using sem::Src;
using sem::UpperDesc;

bool traps(const DecodedPair& d) {
    return d.m || d.d || d.t || d.upper.op == UpperOp::Unknown || d.lower.op == LowerOp::Unknown ||
           !in_census(d.upper.op) || !in_census(d.lower.op);
}
bool is_br(const DecodedPair& d) { return !d.i && is_branch(d.lower.op); }

// vi register the lower op writes (0 = none) and whether that write leaves the branch-VI snapshot live.
struct ViWrite {
    u32 reg = 0;
    bool exempt = false;
};
ViWrite vi_write(const DecodedPair& d) {
    if (d.i) return {};
    const LowerInsn& l = d.lower;
    const u32 it = l.it & 15u, is = l.is & 15u, id = l.id & 15u;
    using L = LowerOp;
    switch (l.op) {
    case L::IADD: case L::ISUB: case L::IAND: case L::IOR: return {id, false};
    case L::IADDI: case L::IADDIU: case L::ISUBIU: return {it, false};
    case L::LQI: case L::LQD: return {is, false};
    case L::SQI: case L::SQD: return {it, false};
    case L::ILW: case L::ILWR: case L::MTIR: case L::XTOP: case L::XITOP: return {it, false};
    case L::FCAND: case L::FCOR: return {1u, true};
    case L::FCGET: case L::FMAND: case L::BAL: return {it, true};
    default: return {};
    }
}

struct Gen {
    const Program& p;
    std::vector<detail::QRead> qkind;   // per pair (meaningful where the upper reads Q)
    std::vector<u32> qdelay;            // per pair (DIV/RSQRT)
    std::set<u32> labels;               // pair indices
    std::ostringstream o;               // the program's source
    std::ostringstream scratch;         // dry runs of a block
    std::ostream* out = &o;
    int uid = 0;
    // footprint
    std::set<u32> reads, expanded;
    struct QReader {
        u32 pair;
        detail::QRead kind;
        std::vector<u32> nodes; // pairs whose jump-list predecessors this reader's classification enumerated
    };
    std::vector<QReader> qreaders;
    std::vector<DecodedPair> code; // 2048 pairs: the program, then the assumed outside (lower/upper NOP)
    bool all_constant_labels = false;

    explicit Gen(const Program& prog) : p(prog) {}

    bool label(u32 k) const { return labels.count(k) != 0; }

    // ---------------------------------------------------------------------------------------------------------------
    // Labels and blocks (unchanged from round 2)
    // ---------------------------------------------------------------------------------------------------------------
    void analyse() {
        code.assign(kMicroPairs, decode_pair(kLowerNopWord, kUpperNopWord));
        for (u32 k = 0; k < p.n; ++k) code[k] = p.d[k];
        const detail::Code c(code.data(), kMicroPairs);
        const std::vector<detail::Jump> jumps = detail::collect_jumps(c);
        qkind.assign(p.n, detail::QRead::Dynamic);
        qdelay.assign(p.n, 0);
        for (u32 k = 0; k < p.n; ++k) {
            const DecodedPair& d = p.d[k];
            if (traps(d)) continue;
            detail::Footprint f;
            if (detail::reads_q(d.upper)) qkind[k] = detail::q_read_kind(c, jumps, k * 8u, &f);
            if (!d.i && d.lower.op == LowerOp::DIV) qdelay[k] = detail::q_delay(c, k * 8u, 7, &f);
            if (!d.i && d.lower.op == LowerOp::RSQRT) qdelay[k] = detail::q_delay(c, k * 8u, 13, &f);
            for (u32 a : f.reads) reads.insert(a >> 3);
            for (u32 a : f.expanded) expanded.insert(a >> 3);
            if (detail::reads_q(d.upper)) {
                std::set<u32> nodes;
                for (u32 a : f.expanded) nodes.insert(a >> 3);
                qreaders.push_back({k, qkind[k], std::vector<u32>(nodes.begin(), nodes.end())});
            }
        }
        // labels. JR targets: `iaddiu viN, vi00, imm` constants whose register some JR jumps through or some ISW/ISWR
        // stores (the 0x3FF.y continuations); every other constant is data and would only split blocks. A JR to a pc
        // that is not a label still works: it bails out to the interpreter.
        u32 jr_regs = 0;
        for (u32 k = 0; k < p.n; ++k) {
            const DecodedPair& d = p.d[k];
            if (d.i) continue;
            if (d.lower.op == LowerOp::JR) jr_regs |= 1u << (d.lower.is & 15u);
            if (d.lower.op == LowerOp::ISW || d.lower.op == LowerOp::ISWR) jr_regs |= 1u << (d.lower.it & 15u);
        }
        if (all_constant_labels) jr_regs = 0xFFFFu;
        labels.insert(0);
        for (u32 k = 0; k < p.n; ++k) {
            const DecodedPair& d = p.d[k];
            if (is_br(d)) {
                if (!is_jump_register(d.lower.op)) {
                    const u32 t = branch_target(d.lower, k * 8u) >> 3;
                    if (t < p.n) labels.insert(t);
                }
                if (d.lower.op == LowerOp::BAL && k + 2 < p.n) labels.insert(k + 2); // the JR return address
            }
            if (d.e && k + 2 < p.n) labels.insert(k + 2);
            if (!d.i && d.lower.op == LowerOp::IADDIU && (d.lower.is & 15u) == 0 && d.lower.imm15 < p.n &&
                (jr_regs >> (d.lower.it & 15u)) & 1u)
                labels.insert(d.lower.imm15);
        }
        close_labels();
        cap_blocks();
        close_labels();
        analyse_flags();
    }

    // MSVC /O2 did not finish (> 40 min) on one 309-pair straight-line block of vu1_prog_006 with the round-2 code:
    // split blocks every kMaxBlock pairs at a pair that is neither a delay slot nor the pair after an E.
    static constexpr u32 kMaxBlock = 96;
    void cap_blocks() {
        u32 run = 0;
        for (u32 k = 0; k < p.n; ++k) {
            if (label(k)) run = 0;
            const bool after_delay_or_e = k > 0 && (is_br(p.d[k - 1]) || p.d[k - 1].e);
            if (run >= kMaxBlock && !after_delay_or_e && !label(k)) {
                labels.insert(k);
                run = 0;
            }
            ++run;
        }
    }

    // The branch at k has a delay slot the compiled code executes (else the interpreter takes over there).
    bool delay_ok(u32 k) const {
        const DecodedPair& d = p.d[k];
        const u32 j = k + 1;
        return !(j >= p.n || traps(p.d[j]) || is_br(p.d[j]) || d.e || p.d[j].e);
    }
    // A conditional branch whose not-taken path continues inside the same block function (no label at k + 1 or
    // k + 2): fewer, longer blocks, which MSVC optimises better and the driver dispatches less often.
    bool continues(u32 k) const {
        const DecodedPair& d = p.d[k];
        return is_br(d) && !is_unconditional(d.lower.op) && !is_jump_register(d.lower.op) && delay_ok(k) &&
               k + 2 < p.n && !label(k + 1) && !label(k + 2);
    }
    // After the base labels: the not-taken path of a conditional branch whose delay slot is itself a label must
    // re-enter at k + 2 through the driver.
    void close_labels() {
        for (bool changed = true; changed;) {
            changed = false;
            for (u32 k = 0; k + 2 < p.n; ++k) {
                const DecodedPair& d = p.d[k];
                if (is_br(d) && !is_unconditional(d.lower.op) && !is_jump_register(d.lower.op) && delay_ok(k) &&
                    label(k + 1) && !label(k + 2)) {
                    labels.insert(k + 2);
                    changed = true;
                }
            }
        }
    }

    // pairs executed from label k before the next label check (bound for the step-limit test): the longest
    // straight-line path through the block (the taken branch exits earlier)
    u32 seglen(u32 k) const {
        u32 count = 0;
        for (u32 m = k; m < p.n;) {
            const DecodedPair& d = p.d[m];
            if (traps(d)) break;
            ++count;
            if (is_br(d) || d.e) {
                ++count;
                if (continues(m)) {
                    m += 2;
                    continue;
                }
                break;
            }
            ++m;
            if (label(m)) break;
        }
        return count;
    }

    // ---------------------------------------------------------------------------------------------------------------
    // Flag-pipe liveness across blocks (round 3)
    //
    // Nodes: (pair, context) with context normal, delay slot of the branch before it, or the pair after an E. The
    // MAC ring holds a write for the FMANDs that read it (an FMAND at time q reads the newest entry inserted with
    // ts <= q - 4); the clip ring likewise for FCAND/FCOR/FCGET (ts <= q - 3; FCSET inserts with ts = q - 4, i.e.
    // visible from the next pair on). A reader is "static" when the entry it reads is inserted earlier in the same
    // block (straight line from the block's label): it then reads a local. A ring entry is needed only when some
    // ring reader on some path can read it before it is superseded; control the analysis cannot follow (JR, a pair
    // outside the program, a trap, a delay slot the compiled code does not run) counts as a reader of everything
    // still visible, the end of a run (the pair after E) as none (start() resets the pipe for the next run). A bail-out
    // at the step limit hands over at a label and the interpreter follows the same paths, so it needs no special case.
    // ---------------------------------------------------------------------------------------------------------------
    enum : u8 { kNormal = 0, kDelay = 1, kAfterE = 2 };
    static u32 node(u32 k, u8 ctx) { return k * 3u + ctx; }
    static constexpr int kInf = 4; // window end "never superseded"

    struct Seq {
        std::vector<std::pair<u32, u8>> pairs; // emission order
    };
    // The pairs a block starting at label k executes in straight line (body order), with their contexts.
    Seq simulate(u32 k) const {
        Seq s;
        for (u32 m = k;;) {
            if (m >= p.n) return s;
            if (m != k && label(m)) return s;
            const DecodedPair& d = p.d[m];
            if (traps(d)) return s;
            if (is_br(d)) {
                s.pairs.push_back({m, kNormal});
                if (!delay_ok(m)) return s;
                s.pairs.push_back({m + 1, kDelay});
                if (continues(m)) {
                    m += 2;
                    continue;
                }
                return s;
            }
            if (d.e) {
                s.pairs.push_back({m, kNormal});
                if (m + 1 < p.n && !traps(p.d[m + 1])) s.pairs.push_back({m + 1, kAfterE});
                return s;
            }
            s.pairs.push_back({m, kNormal});
            ++m;
        }
    }

    struct Succ {
        std::vector<u32> nodes;
        bool unknown = false; // control the analysis cannot follow; no nodes and not unknown = end of run
    };
    Succ succ(u32 nd) const {
        const u32 k = nd / 3;
        const u8 ctx = static_cast<u8>(nd % 3);
        Succ r;
        if (ctx == kAfterE) return r;
        if (ctx == kDelay) {
            const DecodedPair& b = p.d[k - 1];
            if (is_jump_register(b.lower.op)) {
                r.unknown = true;
                return r;
            }
            const u32 tgt = branch_target(b.lower, (k - 1) * 8u) >> 3;
            if (tgt < p.n) r.nodes.push_back(node(tgt, kNormal));
            else r.unknown = true;
            if (!is_unconditional(b.lower.op)) r.nodes.push_back(node(k + 1, kNormal));
            return r;
        }
        if (k >= p.n || traps(p.d[k])) {
            r.unknown = true;
            return r;
        }
        const DecodedPair& d = p.d[k];
        if (is_br(d)) {
            if (!delay_ok(k)) r.unknown = true;
            else r.nodes.push_back(node(k + 1, kDelay));
            return r;
        }
        if (d.e) {
            if (k + 1 >= p.n || traps(p.d[k + 1])) r.unknown = true;
            else r.nodes.push_back(node(k + 1, kAfterE));
            return r;
        }
        r.nodes.push_back(node(k + 1, kNormal));
        return r;
    }

    // flag kinds: 0 = MAC, 1 = clip
    // a node the compiled code can reach as such (inside the program; a delay slot of a branch whose delay slot runs,
    // or the pair after a non-branch E)
    bool valid(u32 nd) const {
        const u32 k = nd / 3;
        const u8 ctx = static_cast<u8>(nd % 3);
        if (k >= p.n) return false;
        if (ctx == kNormal) return true;
        if (k == 0) return false;
        const DecodedPair& b = p.d[k - 1];
        if (traps(b)) return false;
        if (ctx == kDelay) return is_br(b) && delay_ok(k - 1);
        return !is_br(b) && b.e && !traps(p.d[k]);
    }
    bool executes(u32 nd) const { return valid(nd) && (nd % 3 != kNormal || !traps(p.d[nd / 3])); }
    bool mac_writes(u32 k) const { return describe(p.d[k].upper.op).flags; }
    bool clip_upper(u32 k) const { return describe(p.d[k].upper.op).kind == Kind::Clip; }
    bool fcset(u32 k) const { return !p.d[k].i && p.d[k].lower.op == LowerOp::FCSET; }
    bool mac_reader(u32 k) const { return !p.d[k].i && p.d[k].lower.op == LowerOp::FMAND; }
    bool clip_reader(u32 k) const {
        const LowerOp op = p.d[k].lower.op;
        return !p.d[k].i && (op == LowerOp::FCAND || op == LowerOp::FCOR || op == LowerOp::FCGET);
    }
    // per node results
    std::vector<u8> ring_live[2][2]; // [kind][which]: which = 0 the pair's (upper) write; for clip 1 = its FCSET
    std::vector<u8> static_need[2][2];
    std::vector<int> static_src[2];  // reader node -> source node * 2 + which, or -1 (ring reader)
    std::vector<u8> table[2];        // R(node, lo, hi): node * 20 + lo * 5 + hi
    std::vector<Succ> succs;         // per valid node
    u64 n_writes[2] = {}, n_ring[2] = {}, n_static_w[2] = {}, n_readers[2] = {}, n_static_r[2] = {};

    bool ring_reader(int kind, u32 nd) const {
        const u32 k = nd / 3;
        if (k >= p.n || !executes(nd)) return false;
        return (kind == 0 ? mac_reader(k) : clip_reader(k)) && static_src[kind][nd] < 0;
    }
    // smallest window end the pair's writes impose on an older entry (relative to the pair, which is j = 0)
    int supersede(int kind, u32 k, int hi) const {
        if (kind == 0) {
            if (mac_writes(k)) hi = std::min(hi, 3);
        } else {
            if (clip_upper(k)) hi = std::min(hi, 2);
            if (fcset(k)) hi = std::min(hi, 0);
        }
        return hi;
    }
    bool R(int kind, u32 nd, int lo, int hi) const {
        if (hi < lo) return false;
        return table[kind][nd * 20u + static_cast<u32>(lo) * 5u + static_cast<u32>(hi)] != 0;
    }
    // readers at j >= 1 within [max(lo, 1), h] through the successors
    bool through(int kind, u32 nd, int lo, int h) const {
        if (h < std::max(lo, 1)) return false;
        const Succ& s = succs[nd];
        if (s.unknown) return true;
        for (u32 y : s.nodes)
            if (R(kind, y, std::max(lo - 1, 0), h == kInf ? kInf : h - 1)) return true;
        return false;
    }
    bool eval(int kind, u32 nd, int lo, int hi) const {
        if (hi < lo) return false;
        if (!valid(nd)) return nd % 3 == kNormal; // past the program: the interpreter; other invalid nodes: unreachable
        if (!executes(nd)) return true;           // a trap: the interpreter takes over here
        if (lo == 0 && ring_reader(kind, nd)) return true;
        return through(kind, nd, lo, supersede(kind, nd / 3, hi));
    }

    void analyse_flags() {
        const u32 nodes = (p.n + 2) * 3;
        for (int kind = 0; kind < 2; ++kind) {
            for (int w = 0; w < 2; ++w) {
                ring_live[kind][w].assign(nodes, 0);
                static_need[kind][w].assign(nodes, 0);
            }
            static_src[kind].assign(nodes, -1);
            table[kind].assign(nodes * 20u, 0);
        }
        succs.resize(nodes);
        for (u32 nd = 0; nd < nodes; ++nd)
            if (valid(nd)) succs[nd] = succ(nd);
        // static readers per block
        for (u32 k : labels) {
            const Seq s = simulate(k);
            for (std::size_t q = 0; q < s.pairs.size(); ++q) {
                const auto [rk, rc] = s.pairs[q];
                const u32 rn = node(rk, rc);
                if (mac_reader(rk)) {
                    for (std::size_t pp = q; pp-- > 0;) {
                        if (pp + 4 > q) continue;
                        if (mac_writes(s.pairs[pp].first)) {
                            const u32 wn = node(s.pairs[pp].first, s.pairs[pp].second);
                            static_src[0][rn] = static_cast<int>(wn * 2);
                            static_need[0][0][wn] = 1;
                            break;
                        }
                    }
                }
                if (clip_reader(rk)) {
                    for (std::size_t pp = q; pp-- > 0;) {
                        const u32 wk = s.pairs[pp].first;
                        const u32 wn = node(wk, s.pairs[pp].second);
                        if (pp + 3 <= q && clip_upper(wk)) {
                            static_src[1][rn] = static_cast<int>(wn * 2);
                            static_need[1][0][wn] = 1;
                            break;
                        }
                        if (fcset(wk)) {
                            static_src[1][rn] = static_cast<int>(wn * 2 + 1);
                            static_need[1][1][wn] = 1;
                            break;
                        }
                    }
                }
            }
        }
        // least fixpoint of R
        for (int kind = 0; kind < 2; ++kind) {
            for (bool changed = true; changed;) {
                changed = false;
                for (u32 nd = nodes; nd-- > 0;) // successors mostly follow: backwards converges in few passes
                    for (int lo = 0; lo < 4; ++lo)
                        for (int hi = lo; hi <= kInf; ++hi) {
                            u8& v = table[kind][nd * 20u + static_cast<u32>(lo) * 5u + static_cast<u32>(hi)];
                            if (v) continue;
                            if (eval(kind, nd, lo, hi)) {
                                v = 1;
                                changed = true;
                            }
                        }
            }
        }
        // write liveness
        for (u32 nd = 0; nd < nodes; ++nd) {
            const u32 k = nd / 3;
            if (k >= p.n || !executes(nd)) continue;
            if (mac_writes(k)) {
                ++n_writes[0];
                ring_live[0][0][nd] = through(0, nd, 4, kInf) ? 1 : 0;
                n_ring[0] += ring_live[0][0][nd];
                n_static_w[0] += static_need[0][0][nd];
            }
            if (fcset(k)) {
                ++n_writes[1];
                // inserted before the pair's CLIP (if any), visible from the next pair on
                ring_live[1][1][nd] = through(1, nd, 1, clip_upper(k) ? 2 : kInf) ? 1 : 0;
                n_ring[1] += ring_live[1][1][nd];
                n_static_w[1] += static_need[1][1][nd];
            }
            if (clip_upper(k)) {
                ++n_writes[1];
                ring_live[1][0][nd] = through(1, nd, 3, kInf) ? 1 : 0;
                n_ring[1] += ring_live[1][0][nd];
                n_static_w[1] += static_need[1][0][nd];
            }
            if (mac_reader(k)) {
                ++n_readers[0];
                n_static_r[0] += static_src[0][nd] >= 0;
            }
            if (clip_reader(k)) {
                ++n_readers[1];
                n_static_r[1] += static_src[1][nd] >= 0;
            }
        }
    }

    // ---------------------------------------------------------------------------------------------------------------
    // Emission: one function per label block; vf / ACC in SSE locals, vi / clip in integer locals, written back at
    // every exit. The block is emitted twice: a dry run records which registers it uses and writes.
    // ---------------------------------------------------------------------------------------------------------------
    struct Fp {
        u32 vf_used = 0, vf_w = 0;
        u32 vi_used = 0, vi_w = 0;
        bool acc_used = false, acc_w = false, cl_used = false, cl_w = false, mac_w = false;
    };
    Fp blk, sofar, full;
    bool loop = false;     // the block branches to its own label (`goto top`)
    u32 cur = 0;           // the block's label
    u64 vector_ops = 0, peepholes = 0, loops = 0;

    std::string vfR(u32 n) {
        if (!n) return "vf0()";
        blk.vf_used |= 1u << n;
        return "f" + std::to_string(n);
    }
    std::string vfW(u32 n) {
        blk.vf_used |= 1u << n;
        blk.vf_w |= 1u << n;
        sofar.vf_w |= 1u << n;
        return "f" + std::to_string(n);
    }
    std::string viR(u32 n) {
        if (!n) return "0u";
        blk.vi_used |= 1u << n;
        return "i" + std::to_string(n);
    }
    std::string viW(u32 n) {
        blk.vi_used |= 1u << n;
        blk.vi_w |= 1u << n;
        sofar.vi_w |= 1u << n;
        return "i" + std::to_string(n);
    }
    std::string accR() {
        blk.acc_used = true;
        return "fa";
    }
    std::string accW() {
        blk.acc_used = blk.acc_w = sofar.acc_w = true;
        return "fa";
    }
    std::string clR() {
        blk.cl_used = true;
        return "cl";
    }
    std::string clW() {
        blk.cl_used = blk.cl_w = sofar.cl_w = true;
        return "cl";
    }

    // write back what the block changed (all of it in a block that loops: an exit can follow any earlier iteration)
    std::string sync() const {
        const Fp& f = loop ? full : sofar;
        std::string r;
        for (u32 n = 1; n < 32; ++n)
            if ((f.vf_w >> n) & 1u) r += "st(s.vf[" + std::to_string(n) + "], f" + std::to_string(n) + "); ";
        if (f.acc_w) r += "st(s.acc, fa); ";
        for (u32 n = 1; n < 16; ++n)
            if ((f.vi_w >> n) & 1u) r += "s.vi[" + std::to_string(n) + "] = static_cast<u16>(i" + std::to_string(n) + "); ";
        if (f.cl_w) r += "s.clip = cl; ";
        if (f.mac_w)
            r += "if (wm) { const u32 ml_ = mac_of(mlv, mld); s.mac = ml_; const u32 lo_ = status_low(ml_); "
                 "s.status = (s.status & 0xFF0u) | lo_ | (lo_ << 6); } ";
        return r;
    }
    std::string bail(u32 pc_pair, const std::string& npc, bool ending) const {
        return "{ " + sync() + "c.res = bail(s, " + hex(pc_pair * 8u) + "u, " + npc + ", t, pw, pv, pl, " +
               (ending ? "true" : "false") + ", steps); return kExit; }";
    }
    static constexpr const char* kSave = "c.t = t; c.pw = pw; c.pv = pv; c.pl = pl; c.steps = steps;";
    std::string goto_pair(u32 t_pair) const {
        if (t_pair < p.n && label(t_pair)) return "{ " + sync() + kSave + " return " + std::to_string(t_pair) + "u; }";
        return bail(t_pair, hex((t_pair * 8u + 8u) & kMicroMask) + "u", false);
    }
    // a branch to the block's own label stays in the function
    std::string goto_or_loop(u32 t_pair) {
        if (t_pair != cur) return goto_pair(t_pair);
        loop = true;
        return "{ if (steps + " + std::to_string(seglen(cur)) + "u > c.limit) " + bail(cur, hex(cur * 8u + 8u) + "u", false) +
               " goto top; }";
    }

    std::string bvi(u32 r) {
        if (r == 0) return "0u";
        return "((pl && pw == " + std::to_string(r) + "u) ? (pv & 0xFFFFu) : " + viR(r) + ")";
    }

    // Emits one pair.
    void pair(u32 k, u8 ctx) {
        std::ostream& w = *out;
        const u32 nd = node(k, ctx);
        const DecodedPair& d = p.d[k];
        const UpperInsn& u = d.upper;
        const LowerInsn& l = d.lower;
        w << "    { /* " << hex(k * 8u, 4) << " " << mnemonic(u.op) << " | " << mnemonic(l.op) << (d.e ? " [E]" : "")
          << " */\n";
        w << "    ++t; ++steps;\n";
        // Q read
        if (detail::reads_q(u)) {
            switch (qkind[k]) {
            case detail::QRead::New: w << "    flush_q(s);\n"; break;
            case detail::QRead::Dynamic: w << "    if (s.pipe.q_pending && t >= s.pipe.q_ready) flush_q(s);\n"; break;
            case detail::QRead::Old: break;
            }
        }
        // upper compute (into a temporary; committed after the lower op)
        const UpperDesc dsc = describe(u.op);
        int target = -1;
        u32 udest = 0;
        bool uflags = false, uclip = false;
        const std::string id = std::to_string(++uid);
        const std::string U = "u" + id;
        const std::string SP = ", s.status, " + hex(k * 8u) + "u)"; // slow path: sticky O bit into the status register; site
        const auto src_b = [&](Src s) -> std::string {
            switch (s) {
            case Src::Vec: return vfR(u.ft);
            case Src::Bc: return "bc<" + std::to_string(u.bc) + ">(" + vfR(u.ft) + ")";
            case Src::Q: return "splat(s.q)";
            case Src::I: return "splat(s.i)";
            }
            return "";
        };
        switch (dsc.kind) {
        case Kind::None: break;
        case Kind::Clip:
            uclip = true;
            w << "    const u32 uc" << id << " = vclip(" << clR() << ", " << vfR(u.fs) << ", lane<3>(" << vfR(u.ft) << "));\n";
            break;
        case Kind::Opmula:
            target = 32;
            udest = 0xEu;
            uflags = true;
            w << "    const V " << U << " = vmul<14u>(yzx(" << vfR(u.fs) << "), zxy(" << vfR(u.ft) << ")" << SP << ";\n";
            ++vector_ops;
            break;
        case Kind::Opmsub:
            target = u.fd;
            udest = 0xEu;
            uflags = true;
            w << "    const V " << U << " = vmsub<14u>(" << accR() << ", yzx(" << vfR(u.fs) << "), zxy(" << vfR(u.ft) << ")" << SP << ";\n";
            ++vector_ops;
            break;
        default: {
            const bool to_ft = dsc.kind == Kind::Itof || dsc.kind == Kind::Ftoi || dsc.kind == Kind::Abs;
            target = dsc.to_acc ? 32 : (to_ft ? u.ft : u.fd);
            udest = u.dest;
            uflags = dsc.flags;
            const std::string D = std::to_string(udest) + "u";
            const std::string FS = vfR(u.fs);
            std::string e;
            switch (dsc.kind) {
            case Kind::Add: e = "vadd<" + D + ">(" + FS + ", " + src_b(dsc.src) + SP; break;
            case Kind::Sub: e = "vsub<" + D + ">(" + FS + ", " + src_b(dsc.src) + SP; break;
            case Kind::Mul: e = "vmul<" + D + ">(" + FS + ", " + src_b(dsc.src) + SP; break;
            case Kind::Madd: e = "vmadd<" + D + ">(" + accR() + ", " + FS + ", " + src_b(dsc.src) + SP; break;
            case Kind::Msub: e = "vmsub<" + D + ">(" + accR() + ", " + FS + ", " + src_b(dsc.src) + SP; break;
            case Kind::Max: e = "vmax(" + FS + ", " + src_b(dsc.src) + ")"; break;
            case Kind::Min: e = "vmin(" + FS + ", " + src_b(dsc.src) + ")"; break;
            case Kind::Abs: e = "_mm_and_si128(" + FS + ", kAbsV())"; break;
            case Kind::Ftoi: e = "vftoi<" + std::to_string(dsc.frac) + ">(" + FS + ")"; break;
            case Kind::Itof: e = "vitof<" + std::to_string(dsc.frac) + ">(" + FS + ")"; break;
            default: break;
            }
            // broadcast of a constant lane of vf00 (1.0 for w, +0 otherwise): the forms fp:: reduces to without a
            // multiply (exact: fp::mul(x, 1.0) = flush(x), fp::mul(x, +0) = sign(x) zero, fp::add(x, +0) = flush(x)
            // with a zero result +0, fp::sub(x, +0) = flush(x), and fp::add flushes its operands itself)
            if (dsc.src == Src::Bc && u.ft == 0) {
                const bool one = u.bc == 3;
                switch (dsc.kind) {
                case Kind::Mul: e = one ? "vflush(" + FS + ")" : "_mm_and_si128(" + FS + ", kSignV())"; ++peepholes; break;
                case Kind::Add: if (!one) e = "vaddz(" + FS + ")", ++peepholes; break;
                case Kind::Sub: if (!one) e = "vflush(" + FS + ")", ++peepholes; break;
                case Kind::Madd:
                    e = "vadd<" + D + ">(" + accR() + ", " + (one ? FS : "_mm_and_si128(" + FS + ", kSignV())") + SP;
                    ++peepholes;
                    break;
                case Kind::Msub:
                    e = "vsub<" + D + ">(" + accR() + ", " + (one ? FS : "_mm_and_si128(" + FS + ", kSignV())") + SP;
                    ++peepholes;
                    break;
                default: break;
                }
            }
            if (dsc.flags) ++vector_ops;
            w << "    const V " << U << " = " << e << ";\n";
            break;
        }
        }
        // lower
        const ViWrite vwr = vi_write(d);
        // branch-VI snapshot of this pair: the vi register its lower op writes, the old value, and whether the
        // snapshot is live for the next pair (step(): vi_before / vi_delay_live)
        const std::string snap = vwr.reg ? "pv = " + viR(vwr.reg) + "; pw = " + std::to_string(vwr.reg) + "u; pl = " +
                                               (vwr.exempt ? "false" : "true") + ";"
                                         : std::string("pw = 0; pl = ") + (d.i || detail::branch_delay_exempt(l.op) ? "false" : "true") + ";";
        if (d.i) {
            w << "    s.i = " << hex(d.lo) << "u; pw = 0; pl = false;\n";
        } else {
            const u32 it = l.it & 15u, is = l.is & 15u, idr = l.id & 15u, ft = l.it, fsr = l.is, dest = l.dest;
            const std::string D = std::to_string(dest) + "u";
            const std::string imm11 = hex(static_cast<u32>(static_cast<s32>(l.imm11))) + "u";
            using L = LowerOp;
            const auto setvi = [&](u32 r, const std::string& v) {
                if (r) w << "    " << viW(r) << " = (" << v << ") & 0xFFFFu;\n";
            };
            // branch conditions read the snapshot of the previous pair before this pair's pw update
            if (is_branch(l.op)) {
                switch (l.op) {
                case L::B: w << "    tk = true;\n"; break;
                case L::BAL: w << "    tk = true;\n"; break;
                case L::JR: w << "    jt = (" << viR(is) << " * 8u) & kMicroMask;\n"; break;
                case L::IBEQ: w << "    tk = " << bvi(is) << " == " << bvi(it) << ";\n"; break;
                case L::IBNE: w << "    tk = " << bvi(is) << " != " << bvi(it) << ";\n"; break;
                case L::IBLTZ: w << "    tk = static_cast<s16>(" << bvi(is) << ") < 0;\n"; break;
                case L::IBGTZ: w << "    tk = static_cast<s16>(" << bvi(is) << ") > 0;\n"; break;
                case L::IBLEZ: w << "    tk = static_cast<s16>(" << bvi(is) << ") <= 0;\n"; break;
                case L::IBGEZ: w << "    tk = static_cast<s16>(" << bvi(is) << ") >= 0;\n"; break;
                default: break;
                }
                w << "    " << snap << "\n";
                if (l.op == L::BAL) setvi(it, hex((k * 8u + 16u) / 8u) + "u");
            } else {
                w << "    " << snap << "\n";
                const auto addr = [&](u32 r, bool off) {
                    return "qw(s, " + viR(r) + (off ? " + " + imm11 : std::string()) + ")";
                };
                switch (l.op) {
                case L::NOP: break;
                case L::IADD: setvi(idr, viR(is) + " + " + viR(it)); break;
                case L::ISUB: setvi(idr, viR(is) + " - " + viR(it)); break;
                case L::IAND: setvi(idr, viR(is) + " & " + viR(it)); break;
                case L::IOR: setvi(idr, viR(is) + " | " + viR(it)); break;
                case L::IADDI: setvi(it, viR(is) + " + " + hex(static_cast<u32>(static_cast<s32>(l.imm5))) + "u"); break;
                case L::IADDIU: setvi(it, viR(is) + " + " + std::to_string(l.imm15) + "u"); break;
                case L::ISUBIU: setvi(it, viR(is) + " - " + std::to_string(l.imm15) + "u"); break;
                case L::MOVE:
                    if (ft) w << "    " << vfW(ft) << " = blend<" << D << ">(" << vfR(ft) << ", " << vfR(fsr) << ");\n";
                    break;
                case L::MR32:
                    if (ft) w << "    " << vfW(ft) << " = blend<" << D << ">(" << vfR(ft) << ", mr32(" << vfR(fsr) << "));\n";
                    break;
                case L::LQ:
                    if (ft) w << "    " << vfW(ft) << " = lq<" << D << ">(" << vfR(ft) << ", " << addr(is, true) << ");\n";
                    break;
                case L::SQ: w << "    sq<" << D << ">(" << addr(it, true) << ", " << vfR(fsr) << ");\n"; break;
                case L::LQI:
                    if (ft) w << "    " << vfW(ft) << " = lq<" << D << ">(" << vfR(ft) << ", " << addr(is, false) << ");\n";
                    setvi(is, viR(is) + " + 1u");
                    break;
                case L::SQI:
                    w << "    sq<" << D << ">(" << addr(it, false) << ", " << vfR(fsr) << ");\n";
                    setvi(it, viR(it) + " + 1u");
                    break;
                case L::LQD:
                    setvi(is, viR(is) + " - 1u");
                    if (ft) w << "    " << vfW(ft) << " = lq<" << D << ">(" << vfR(ft) << ", " << addr(is, false) << ");\n";
                    break;
                case L::SQD:
                    setvi(it, viR(it) + " - 1u");
                    w << "    sq<" << D << ">(" << addr(it, false) << ", " << vfR(fsr) << ");\n";
                    break;
                case L::ILW: if (it) setvi(it, "ilw<" + D + ">(" + addr(is, true) + ")"); break;
                case L::ISW: w << "    isw<" << D << ">(" << addr(is, true) << ", " << viR(it) << ");\n"; break;
                case L::ILWR: if (it) setvi(it, "ilw<" + D + ">(" + addr(is, false) + ")"); break;
                case L::ISWR: w << "    isw<" << D << ">(" << addr(is, false) << ", " << viR(it) << ");\n"; break;
                case L::MTIR: setvi(it, "lane<" + std::to_string(l.fsf) + ">(" + vfR(fsr) + ")"); break;
                case L::MFIR:
                    if (ft)
                        w << "    " << vfW(ft) << " = blend<" << D << ">(" << vfR(ft) << ", splat(static_cast<u32>(static_cast<s32>(static_cast<s16>("
                          << viR(is) << ")))));\n";
                    break;
                case L::DIV:
                    w << "    div_q(s, t, lane<" << int(l.fsf) << ">(" << vfR(fsr) << "), lane<" << int(l.ftf) << ">(" << vfR(ft) << "), "
                      << qdelay[k] << "u);\n";
                    break;
                case L::RSQRT:
                    w << "    rsqrt_q(s, c.host_csr, t, lane<" << int(l.fsf) << ">(" << vfR(fsr) << "), lane<" << int(l.ftf) << ">("
                      << vfR(ft) << "), " << qdelay[k] << "u);\n";
                    break;
                case L::WAITQ: w << "    flush_q(s);\n"; break;
                case L::ERCPR: w << "    ercpr(s, c.host_csr, lane<" << int(l.fsf) << ">(" << vfR(fsr) << "));\n"; break;
                case L::MFP:
                    if (ft) w << "    " << vfW(ft) << " = blend<" << D << ">(" << vfR(ft) << ", splat(s.p));\n";
                    break;
                case L::XTOP: setvi(it, "s.top"); break;
                case L::XITOP: setvi(it, "s.itop"); break;
                case L::XGKICK: w << "    xgkick(host, c.host_csr, " << viR(is) << ");\n"; break;
                case L::FCSET:
                    w << "    " << clW() << " = " << hex(l.imm24) << "u;";
                    if (ring_live[1][1][nd]) w << " clip_write(s.pipe, " << hex(l.imm24) << "u, t - 4u);";
                    w << "\n";
                    break;
                case L::FCAND:
                    setvi(1, "(" + clip_value(nd) + " & " + hex(l.imm24) + "u) ? 1u : 0u");
                    break;
                case L::FCOR:
                    setvi(1, "((" + clip_value(nd) + " | " + hex(l.imm24) + "u) & 0xFFFFFFu) == 0xFFFFFFu ? 1u : 0u");
                    break;
                case L::FCGET: setvi(it, clip_value(nd) + " & 0xFFFu"); break;
                case L::FMAND: setvi(it, mac_value(nd) + " & " + viR(is)); break;
                default:
                    std::fprintf(stderr, "aotgen: %s pair %u: lower op %s not handled\n", p.name.c_str(), k,
                                 std::string(mnemonic(l.op)).c_str());
                    std::exit(3);
                }
            }
        }
        // upper commit
        if (target > 0) {
            const std::string dst = target == 32 ? accW() : vfW(static_cast<u32>(target));
            w << "    " << dst << " = blend<" << udest << "u>(" << dst << ", " << U << ");\n";
        }
        if (target >= 0 && uflags) {
            blk.mac_w = sofar.mac_w = true;
            // (sticky Z / S: the driver runs only with ZS and SS already set, rt sticky_zs_set; OS: the slow path)
            w << "    mlv = " << U << "; mld = " << udest << "u; wm = true;\n";
            const bool ring = ring_live[0][0][nd] != 0, need = static_need[0][0][nd] != 0;
            if (ring || need) {
                w << "    { const u32 m_ = mac_of(" << U << ", " << udest << "u);";
                if (need) w << " m" << nd << " = m_;";
                if (ring) w << " mac_ring(s, t, m_);";
                w << " }\n";
            }
        }
        if (uclip) {
            w << "    " << clW() << " = uc" << id << ";";
            if (static_need[1][0][nd]) w << " c" << nd << " = uc" << id << ";";
            if (ring_live[1][0][nd]) w << " clip_write(s.pipe, uc" << id << ", t);";
            w << "\n";
        }
    }
    std::string mac_value(u32 rn) const {
        const int src = static_src[0][rn];
        if (src < 0) return "mac_read(s.pipe, t)";
        return "m" + std::to_string(src / 2);
    }
    std::string clip_value(u32 rn) const {
        const int src = static_src[1][rn];
        if (src < 0) return "clip_read(s.pipe, t)";
        if (src & 1) return hex(p.d[static_cast<u32>(src / 2) / 3].lower.imm24) + "u"; // FCSET's immediate
        return "c" + std::to_string(src / 2);
    }

    // The block starting at label k (body order as simulate()).
    void emit_block(u32 k, std::ostream& dest) {
        std::ostringstream bodytext;
        out = &bodytext;
        cur = k;
        blk = Fp{};
        sofar = Fp{};
        std::ostream& w = bodytext;
        for (u32 m = k;;) {
            if (m >= p.n) {
                w << "    " << bail(m, hex((m * 8u + 8u) & kMicroMask) + "u", false) << "\n";
                break;
            }
            if (m != k && label(m)) {
                w << "    " << goto_pair(m) << "\n";
                break;
            }
            const DecodedPair& d = p.d[m];
            if (traps(d)) {
                w << "    " << bail(m, hex((m * 8u + 8u) & kMicroMask) + "u", false) << "\n";
                break;
            }
            if (is_br(d)) {
                pair(m, kNormal);
                w << "    }\n";
                const u32 j = m + 1;
                const bool jr = is_jump_register(d.lower.op);
                const u32 tgt = jr ? 0 : branch_target(d.lower, m * 8u) >> 3;
                const std::string npc_if =
                    jr ? std::string("jt") : (is_unconditional(d.lower.op) ? hex(tgt * 8u) + "u"
                                                                             : "(tk ? " + hex(tgt * 8u) + "u : " + hex((j * 8u + 8u) & kMicroMask) + "u)");
                if (!delay_ok(m)) {
                    // delay slot the compiled code does not handle: the interpreter executes it
                    w << "    " << bail(j, npc_if, d.e) << "\n";
                    break;
                }
                pair(j, kDelay);
                w << "    }\n";
                if (jr) {
                    w << "    " << sync() << kSave << " return jt >> 3;\n";
                } else if (is_unconditional(d.lower.op)) {
                    w << "    " << goto_or_loop(tgt) << "\n";
                } else if (continues(m)) {
                    // not taken: carry on with pair m + 2 in this block
                    w << "    if (tk) " << goto_or_loop(tgt) << "\n";
                    m += 2;
                    continue;
                } else {
                    w << "    if (tk) " << goto_or_loop(tgt) << "\n    " << goto_pair(m + 2) << "\n";
                }
                break;
            }
            if (d.e) {
                pair(m, kNormal);
                w << "    }\n";
                const u32 j = m + 1;
                if (j >= p.n || traps(p.d[j])) {
                    w << "    " << bail(j, hex((j * 8u + 8u) & kMicroMask) + "u", true) << "\n";
                } else {
                    pair(j, kAfterE);
                    std::string npc = hex((j * 8u + 16u) & kMicroMask) + "u";
                    const DecodedPair& dj = p.d[j];
                    if (is_br(dj)) {
                        if (is_jump_register(dj.lower.op))
                            npc = "jt";
                        else if (is_unconditional(dj.lower.op))
                            npc = hex(branch_target(dj.lower, j * 8u)) + "u";
                        else
                            npc = "(tk ? " + hex(branch_target(dj.lower, j * 8u)) + "u : " + npc + ")";
                    }
                    w << "    " << sync() << "c.res = finish(s, " << hex((j * 8u + 8u) & kMicroMask) << "u, " << npc
                      << ", t, pw, pv, pl, steps);\n    return kExit;\n    }\n";
                }
                break;
            }
            pair(m, kNormal);
            w << "    }\n";
            ++m;
        }
        out = nullptr;
        // header: locals for everything the block uses, loaded once
        const std::string va = va8(p.code_va);
        dest << "P3FES_VU1_BLOCK u32 blk_" << va << "_" << k << "(VU1State& s, AotHost& host, Ctx& c) {\n";
        dest << "    u32 t = c.t, pw = c.pw, pv = c.pv, jt = 0;\n    u64 steps = c.steps;\n    bool pl = c.pl, tk = false;\n";
        dest << "    (void)jt; (void)tk; (void)host;\n";
        dest << "    if (steps + " << seglen(k) << "u > c.limit) { c.res = bail(s, " << hex(k * 8u) << "u, " << hex(k * 8u + 8u)
          << "u, t, pw, pv, pl, false, steps); return kExit; }\n";
        for (u32 n = 1; n < 32; ++n)
            if ((blk.vf_used >> n) & 1u) dest << "    V f" << n << " = ld(s.vf[" << n << "]);\n";
        if (blk.acc_used) dest << "    V fa = ld(s.acc);\n";
        for (u32 n = 1; n < 16; ++n)
            if ((blk.vi_used >> n) & 1u) dest << "    u32 i" << n << " = s.vi[" << n << "];\n";
        if (blk.cl_used) dest << "    u32 cl = s.clip;\n";
       if (blk.mac_w)
            dest << "    V mlv = _mm_setzero_si128();\n"
                 "    u32 mld = 0; bool wm = false;\n";
        // locals of static flag reads in this block
        const Seq sq = simulate(k);
        for (const auto& [pk, pc] : sq.pairs) {
            const u32 nd = node(pk, pc);
            if (static_need[0][0][nd]) dest << "    u32 m" << nd << " = 0;\n";
            if (static_need[1][0][nd]) dest << "    u32 c" << nd << " = 0;\n";
        }
        if (loop) dest << "top:\n";
        dest << bodytext.str() << "}\n\n";
    }

    void body() {
        const std::string va = va8(p.code_va);
        for (u32 k : labels) {
            // dry run: the registers the block uses and writes, and whether it loops
            loop = false;
            full = Fp{};
            emit_block(k, scratch);
            scratch.str("");
            full = blk;
            if (loop) ++loops;
            emit_block(k, o);
        }
        // driver
        o << "AotResult run_" << va << "(VU1State& s, AotHost& host, u32 start_pc, u64 limit) {\n";
        o << "    if (!canonical_zero_regs(s) || !sticky_zs_set(s)) return AotResult{false, 0};\n";
        o << "    const CsrScope csr;\n    detail::g_aot_cur_va = " << hex(p.code_va) << "u;\n";
        o << "    Ctx c;\n    c.t = s.pipe.t;\n    c.limit = limit;\n    c.host_csr = csr.saved;\n";
        o << "    u32 b = (start_pc & kMicroMask) >> 3;\n    for (;;) {\n        switch (b) {\n";
        for (u32 k : labels) o << "        case " << k << ": b = blk_" << va << "_" << k << "(s, host, c); break;\n";
        o << "        case kExit: return c.res;\n";
        o << "        default: return bail(s, b * 8u, b * 8u + 8u, c.t, c.pw, c.pv, c.pl, false, c.steps);\n";
        o << "        }\n    }\n}\n";
    }
};

std::vector<u8> read_file(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

} // namespace

int main(int argc, char** argv) {
    std::string dumps, census, out;
    std::set<u32> only;
    for (int i = 1; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--dumps" && i + 1 < argc) dumps = argv[++i];
        else if (a == "--census" && i + 1 < argc) census = argv[++i];
        else if (a == "--out" && i + 1 < argc) out = argv[++i];
        else if (a == "--only" && i + 1 < argc) {
            std::stringstream ss(argv[++i]);
            std::string tok;
            while (std::getline(ss, tok, ','))
                if (!tok.empty()) only.insert(static_cast<u32>(std::strtoul(tok.c_str(), nullptr, 16)));
        } else {
            std::fprintf(stderr, "usage: p3fes_vu1_aotgen --dumps DIR --census JSON --out DIR [--only VA,...]\n");
            return 2;
        }
    }
    if (dumps.empty() || census.empty() || out.empty()) {
        std::fprintf(stderr, "usage: p3fes_vu1_aotgen --dumps DIR --census JSON --out DIR [--only VA,...]\n");
        return 2;
    }
    // names from the census
    std::map<u32, std::string> names;
    {
        std::ifstream f(census);
        const std::string text((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        // every program object carries "name": "vu1_prog_..." followed by its "code_va": "0x..."
        const std::string kName = "\"name\": \"vu1_prog_", kVa = "\"code_va\": \"0x";
        for (std::size_t pos = text.find(kName); pos != std::string::npos; pos = text.find(kName, pos + 1)) {
            const std::size_t n0 = pos + 9, n1 = text.find('"', n0);
            const std::size_t v = text.find(kVa, n1);
            if (n1 == std::string::npos || v == std::string::npos) break;
            names[static_cast<u32>(std::strtoul(text.c_str() + v + kVa.size(), nullptr, 16))] = text.substr(n0, n1 - n0);
        }
    }
    if (names.empty()) {
        std::fprintf(stderr, "aotgen: no programs in %s\n", census.c_str());
        return 1;
    }
    fs::create_directories(out);
    std::vector<Program> progs;
    for (const auto& [va, name] : names) {
        if (!only.empty() && !only.count(va)) continue;
        char file[32];
        std::snprintf(file, sizeof file, "%08x.bin", va);
        Program p;
        p.name = name;
        p.code_va = va;
        p.image = read_file(fs::path(dumps) / file);
        if (p.image.size() < 8) {
            std::fprintf(stderr, "aotgen: missing dump %s\n", (fs::path(dumps) / file).string().c_str());
            return 1;
        }
        p.image.resize(p.image.size() & ~std::size_t{7});
        p.n = static_cast<u32>(p.image.size() / 8);
        for (u32 k = 0; k < p.n; ++k) {
            u32 lo, hi;
            std::memcpy(&lo, p.image.data() + k * 8, 4);
            std::memcpy(&hi, p.image.data() + k * 8 + 4, 4);
            p.d.push_back(decode_pair(lo, hi));
        }
        progs.push_back(std::move(p));
    }
    std::ostringstream table;
    table << "// Generated by p3fes_vu1_aotgen: the compiled-program table. Build output (embeds game code); never commit.\n"
             "#include \"p3fes/vu1/vu1_aot.h\"\n\nnamespace p3fes::vu1 {\nnamespace aot {\n";
    std::ostringstream entries;
    u32 total_pairs = 0, total_labels = 0, outside_progs = 0;
    u64 all_writes[2] = {}, all_ring[2] = {};
    for (const Program& p : progs) {
        Gen g(p);
        g.analyse();
        const std::string va = va8(p.code_va);
        std::ostringstream& o = g.o;
        o << "// Generated by p3fes_vu1_aotgen from " << p.name << " (code VA " << hex(p.code_va) << ", " << p.n
          << " pairs). Build output (embeds game code); never commit.\n";
        o << "#include \"vu1_aot_rt.h\"\n\n#if defined(_MSC_VER) && !defined(__clang__)\n#pragma warning(disable : 4100 4102 4189 4702)\n#endif\n"
             "#if defined(__clang__)\n#pragma clang diagnostic ignored \"-Wunused-label\"\n#pragma clang diagnostic ignored \"-Wunused-variable\"\n#pragma clang diagnostic ignored \"-Wunused-but-set-variable\"\n#endif\n\n"
             "namespace p3fes::vu1::aot {\n\n";
        g.body();
        o << "\n} // namespace p3fes::vu1::aot\n";
        std::ofstream(fs::path(out) / ("vu1_aot_" + va + ".cpp"), std::ios::binary) << o.str();
        // table entry data
        std::vector<u32> outside;
        for (u32 r : g.reads)
            if (r >= p.n) outside.push_back(r);
        if (!outside.empty()) ++outside_progs;
        table << "AotResult run_" << va << "(VU1State&, AotHost&, u32, u64);\n";
        table << "alignas(16) const u8 image_" << va << "[] = {";
        for (std::size_t b = 0; b < p.image.size(); ++b) table << (b % 32 ? "" : "\n    ") << unsigned(p.image[b]) << ",";
        table << "\n};\n";
        table << "const AotOutsideRead outside_" << va << "[] = {";
        for (u32 r : outside) table << "{" << r << ", " << hex(kLowerNopWord) << "u, " << hex(kUpperNopWord) << "u}, ";
        if (outside.empty()) table << "{0, 0, 0}";
        table << "};\n";
        u64 bits[kMicroPairs / 64] = {};
        for (u32 e : g.expanded) bits[e / 64] |= 1ull << (e % 64);
        table << "const u64 expanded_" << va << "[] = {";
        for (u32 w = 0; w < kMicroPairs / 64; ++w) {
            char b[24];
            std::snprintf(b, sizeof b, "0x%016llXull,", static_cast<unsigned long long>(bits[w]));
            table << (w % 4 ? " " : "\n    ") << b;
        }
        table << "\n};\n";
        table << "const AotQReader qreaders_" << va << "[] = {";
        std::vector<u32> nodes;
        for (const auto& q : g.qreaders) {
            table << "{" << q.pair << ", " << static_cast<int>(q.kind) << ", " << nodes.size() << ", " << q.nodes.size() << "}, ";
            nodes.insert(nodes.end(), q.nodes.begin(), q.nodes.end());
        }
        if (g.qreaders.empty()) table << "{0, 0, 0, 0}";
        table << "};\nconst u16 qnodes_" << va << "[] = {";
        for (std::size_t i = 0; i < nodes.size(); ++i) table << (i % 24 ? " " : "\n    ") << nodes[i] << ",";
        if (nodes.empty()) table << "0";
        table << "};\n";
        entries << "    {\"" << p.name << "\", " << hex(p.code_va) << "u, image_" << va << ", " << p.n << "u, run_" << va
                << ", outside_" << va << ", " << outside.size() << "u, expanded_" << va << ", qreaders_" << va << ", "
                << g.qreaders.size() << "u, qnodes_" << va << "},\n";
        total_pairs += p.n;
        total_labels += static_cast<u32>(g.labels.size());
        const auto ull = [](u64 v) { return static_cast<unsigned long long>(v); };
        std::printf("aotgen: %s %u pairs, %zu labels (%llu loop in place), %zu outside reads, %zu expanded, %llu FMAC ops (%llu on vf00 lanes); "
                    "MAC writes %llu: %llu ring, %llu local; FMAND %llu: %llu local; clip writes %llu: %llu ring, %llu local; "
                    "clip reads %llu: %llu local\n",
                    p.name.c_str(), p.n, g.labels.size(), ull(g.loops), outside.size(), g.expanded.size(), ull(g.vector_ops), ull(g.peepholes),
                    ull(g.n_writes[0]), ull(g.n_ring[0]), ull(g.n_static_w[0]), ull(g.n_readers[0]), ull(g.n_static_r[0]),
                    ull(g.n_writes[1]), ull(g.n_ring[1]), ull(g.n_static_w[1]), ull(g.n_readers[1]), ull(g.n_static_r[1]));
        for (int kind = 0; kind < 2; ++kind) {
            all_writes[kind] += g.n_writes[kind];
            all_ring[kind] += g.n_ring[kind];
        }
    }
    table << "\nconst AotProgram kPrograms[] = {\n" << entries.str();
    if (progs.empty()) table << "    {nullptr, 0, nullptr, 0, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr},\n";
    table << "};\n\n} // namespace aot\n\n"
          << "std::size_t aot_program_count() noexcept { return " << progs.size() << "; }\n"
          << "const AotProgram* aot_programs() noexcept { return aot::kPrograms; }\n\n} // namespace p3fes::vu1\n";
    std::ofstream(fs::path(out) / "vu1_aot_programs.cpp", std::ios::binary) << table.str();
    std::printf("aotgen: %zu programs, %u pairs, %u labels, %u programs with outside reads; ring entries kept: MAC "
                "%llu of %llu writes, clip %llu of %llu -> %s\n",
                progs.size(), total_pairs, total_labels, outside_progs, static_cast<unsigned long long>(all_ring[0]),
                static_cast<unsigned long long>(all_writes[0]), static_cast<unsigned long long>(all_ring[1]),
                static_cast<unsigned long long>(all_writes[1]), out.c_str());
    return 0;
}
