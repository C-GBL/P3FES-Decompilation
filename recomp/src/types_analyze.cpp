// p3fes_types phase 1: per-function dataflow over the emitter's analysis (types.h).
#include "emit_analyze.h"
#include "types.h"

#include <algorithm>
#include <cstring>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace p3fes::recomp::types {

namespace {

constexpr std::uint32_t kGp = 0x7D2CF0u;  // crt0 sets $gp once (docs/ANALYSIS/00_elf_layout.md)

enum VK : std::uint8_t { kUnknown = 0, kConst, kPtr, kStack, kScaled, kGIdx };

struct Val {
    std::uint8_t k = kUnknown;
    std::uint8_t full = 0;  // Const: built as a complete address (lui+addiu/ori, gp+imm), not just a %hi part
    std::int32_t off = 0;   // Ptr / Stack offset
    std::uint32_t x = 0;    // Unknown/Scaled: var; Const/GIdx: value; Ptr: tv
    std::int32_t s = 0;     // Ptr/GIdx: stride (0 = fixed); Scaled: factor
    bool operator==(const Val& o) const noexcept {
        return k == o.k && full == o.full && off == o.off && x == o.x && s == o.s;
    }
    bool operator!=(const Val& o) const noexcept { return !(*this == o); }
};

Val unknown(std::uint32_t var) { Val v; v.k = kUnknown; v.x = var; return v; }
Val cnst(std::uint32_t c, bool full) { Val v; v.k = kConst; v.x = c; v.full = full ? 1 : 0; return v; }
Val ptr(std::uint32_t tv, std::int32_t off, std::int32_t s) { Val v; v.k = kPtr; v.x = tv; v.off = off; v.s = s; return v; }
Val stack(std::int32_t off) { Val v; v.k = kStack; v.off = off; return v; }
Val scaled(std::uint32_t var, std::int32_t f) {
    if (f == 1) return unknown(var);
    Val v; v.k = kScaled; v.x = var; v.s = f; return v;
}
Val gidx(std::uint32_t c, std::int32_t s) { Val v; v.k = kGIdx; v.x = c; v.s = s; return v; }

std::int32_t gcd32(std::int32_t a, std::int32_t b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b) { const std::int32_t t = a % b; a = b; b = t; }
    return a == 0 ? 1 : a;
}

struct State {
    bool valid = false;
    Val r[32];
    Val lo;
    std::vector<std::pair<std::int32_t, Val>> slots;  // sorted by offset; spills at entry-$sp offsets

    const Val* slot(std::int32_t off) const {
        auto it = std::lower_bound(slots.begin(), slots.end(), off,
                                   [](const std::pair<std::int32_t, Val>& p, std::int32_t o) { return p.first < o; });
        return it != slots.end() && it->first == off ? &it->second : nullptr;
    }
    void set_slot(std::int32_t off, const Val& v) {
        auto it = std::lower_bound(slots.begin(), slots.end(), off,
                                   [](const std::pair<std::int32_t, Val>& p, std::int32_t o) { return p.first < o; });
        if (it != slots.end() && it->first == off) it->second = v;
        else if (slots.size() < 96) slots.insert(it, {off, v});
    }
    void kill_slot_range(std::int32_t off, int width) {
        slots.erase(std::remove_if(slots.begin(), slots.end(),
                                   [&](const std::pair<std::int32_t, Val>& p) {
                                       return p.first > off - 16 && p.first < off + width && p.first != off;
                                   }),
                    slots.end());
    }
};

bool is_code_addr(const Program& prog, std::uint32_t c) { return prog.function_at(c) != nullptr; }
bool is_data_addr(std::uint32_t c) {
    return (c >= 0x5A1400u && c < 0x2000000u) || (c >= 0x70000000u && c < 0x70004000u);
}

// Which GPR an instruction writes (0 = none).
int dest_gpr(const Insn& in) {
    switch (in.op) {
    case Op::Addi: case Op::Addiu: case Op::Andi: case Op::Daddiu: case Op::Lb: case Op::Lbu: case Op::Ld:
    case Op::Ldl: case Op::Ldr: case Op::Lh: case Op::Lhu: case Op::Lui: case Op::Lw: case Op::Lwl: case Op::Lwr:
    case Op::Lwu: case Op::Ori: case Op::Slti: case Op::Sltiu: case Op::Xori: case Op::Lq: case Op::Mfc0:
    case Op::Mfc1: case Op::Cfc2: case Op::Qmfc2:
        return in.rt;
    case Op::Div: case Op::Divu: case Op::Div1: case Op::Mthi: case Op::Mtlo: case Op::Mthi1: case Op::Mtlo1:
    case Op::Mtsa: case Op::Mtsab: case Op::Mtsah:
        return 0;
    default:
        break;
    }
    const Unit u = [&] {
        switch (in.op) {
        case Op::Add: case Op::Addu: case Op::And: case Op::Daddu: case Op::Dsll: case Op::Dsll32: case Op::Dsllv:
        case Op::Dsra: case Op::Dsra32: case Op::Dsrl: case Op::Dsrl32: case Op::Dsrlv: case Op::Dsubu: case Op::Mfhi:
        case Op::Mflo: case Op::Movn: case Op::Movz: case Op::Nor: case Op::Or: case Op::Sll: case Op::Sllv:
        case Op::Slt: case Op::Sltu: case Op::Sra: case Op::Srav: case Op::Srl: case Op::Srlv: case Op::Sub:
        case Op::Subu: case Op::Xor: case Op::Mult: case Op::Multu: case Op::Jalr:
            return Unit::Integer;
        default:
            return Unit::Invalid;
        }
    }();
    if (u == Unit::Integer) return in.rd;
    // MMI register ops (p*, madd*, mult1, mfhi1, mflo1, mfsa, qfsrv): rd
    const std::uint16_t o = static_cast<std::uint16_t>(in.op);
    if (o >= static_cast<std::uint16_t>(Op::Div1) && o <= static_cast<std::uint16_t>(Op::Sq) && in.op != Op::Lq &&
        in.op != Op::Sq)
        return in.rd;
    return 0;
}

struct MemOp {
    bool is = false;
    bool store = false;
    std::uint8_t width = 0;
    std::uint8_t kind = 0;
    bool unaligned = false;
};

MemOp mem_op(Op op) {
    MemOp m;
    m.is = true;
    switch (op) {
    case Op::Lb: m.width = 1; m.kind = kKSigned; break;
    case Op::Lbu: m.width = 1; m.kind = kKUnsigned; break;
    case Op::Lh: m.width = 2; m.kind = kKSigned; break;
    case Op::Lhu: m.width = 2; m.kind = kKUnsigned; break;
    case Op::Lw: m.width = 4; m.kind = kKSigned; break;
    case Op::Lwu: m.width = 4; m.kind = kKUnsigned; break;
    case Op::Ld: m.width = 8; m.kind = kKInt64; break;
    case Op::Lq: m.width = 16; m.kind = kKInt128; break;
    case Op::Lwc1: m.width = 4; m.kind = kKFloat; break;
    case Op::Lqc2: m.width = 16; m.kind = kKVector; break;
    case Op::Sb: m.width = 1; m.store = true; break;
    case Op::Sh: m.width = 2; m.store = true; break;
    case Op::Sw: m.width = 4; m.store = true; break;
    case Op::Sd: m.width = 8; m.kind = kKInt64; m.store = true; break;
    case Op::Sq: m.width = 16; m.kind = kKInt128; m.store = true; break;
    case Op::Swc1: m.width = 4; m.kind = kKFloat; m.store = true; break;
    case Op::Sqc2: m.width = 16; m.kind = kKVector; m.store = true; break;
    case Op::Lwl: case Op::Lwr: m.width = 4; m.unaligned = true; break;
    case Op::Ldl: case Op::Ldr: m.width = 8; m.unaligned = true; break;
    case Op::Swl: case Op::Swr: m.width = 4; m.unaligned = true; m.store = true; break;
    case Op::Sdl: case Op::Sdr: m.width = 8; m.unaligned = true; m.store = true; break;
    default: m.is = false; break;
    }
    if (m.store) m.kind |= kKStore;
    return m;
}

class FnAnalyzer {
public:
    FnAnalyzer(const Program& prog, Facts& facts, const FunctionAnalysis& a, AnalyzeStats& st)
        : prog_(prog), f_(facts), a_(a), st_(st), self_(a.fn->start) {}

    void run() {
        // Nodes: every reachable item.
        for (std::size_t ci = 0; ci < a_.chunks.size(); ++ci) {
            const ChunkAnalysis& c = a_.chunks[ci];
            for (std::size_t ii = 0; ii < c.items.size(); ++ii) {
                const Item& it = c.items[ii];
                if (!it.reachable) continue;
                node_of_[it.pc] = static_cast<std::uint32_t>(nodes_.size());
                nodes_.push_back({&it, &c});
                if (it.is_cf && it.has_slot) slot_owner_[it.pc + 4] = static_cast<std::uint32_t>(nodes_.size() - 1);
            }
        }
        if (nodes_.empty()) return;
        in_.assign(nodes_.size(), State{});
        visits_.assign(nodes_.size(), 0);

        State entry;
        entry.valid = true;
        for (int r = 0; r < 32; ++r) entry.r[r] = unknown(static_cast<std::uint32_t>(r) << 24);
        entry.r[0] = cnst(0, false);
        for (int i = 0; i < 8; ++i) entry.r[4 + i] = ptr(f_.param_tv(self_, static_cast<std::uint32_t>(i)), 0, 0);
        entry.r[28] = cnst(kGp, true);
        entry.r[29] = stack(0);
        entry.lo = unknown(0xFE000000u);
        flow_to(a_.fn->start, entry);
        for (std::uint32_t e : a_.entries) {  // mid-body entries: unknown registers, ABI-preserved sp/gp
            State s = entry;
            for (int i = 0; i < 8; ++i) s.r[4 + i] = unknown((static_cast<std::uint32_t>(4 + i) << 24) | 1);
            flow_to(e, s);
        }
        // Fixpoint without recording.
        recording_ = false;
        std::size_t budget = nodes_.size() * 256;  // a safety net; the lattice is finite
        while (!work_.empty() && budget-- > 0) {
            const std::uint32_t n = *work_.begin();
            work_.erase(work_.begin());
            ++st_.iterations;
            if (++visits_[n] > 64) widen(in_[n]);
            transfer(n);
        }
        // Record pass over the converged in-states.
        recording_ = true;
        cons_begin_ = f_.cons.size();
        acc_begin_ = f_.accesses.size();
        for (std::uint32_t n = 0; n < nodes_.size(); ++n)
            if (in_[n].valid) transfer(n);
        filter_joins();
    }

private:
    struct Node {
        const Item* it;
        const ChunkAnalysis* chunk;
    };

    const Program& prog_;
    Facts& f_;
    const FunctionAnalysis& a_;
    AnalyzeStats& st_;
    std::uint32_t self_;
    std::vector<Node> nodes_;
    std::unordered_map<std::uint32_t, std::uint32_t> node_of_, slot_owner_;
    std::vector<State> in_;
    std::vector<int> visits_;
    std::set<std::uint32_t> work_;
    bool recording_ = false;
    std::set<std::pair<std::uint32_t, std::uint32_t>> joins_;  // (phi, incoming)
    std::unordered_map<std::uint32_t, std::uint32_t> phi_;      // joinvar -> phi tv
    std::size_t cons_begin_ = 0, acc_begin_ = 0;

    std::uint32_t phi_tv(std::uint32_t joinvar) {
        auto it = phi_.find(joinvar);
        if (it != phi_.end()) return it->second;
        const std::uint32_t t = f_.new_tv(TvKind::Deref, 0, 0xFFFFFFFFu, self_);  // a Deref without a base: a phi
        phi_.emplace(joinvar, t);
        return t;
    }

    // Keep the join links of the phis whose value is used (a base of an access, a deref base, a call argument, a
    // stored or returned value, an indirect call), transitively through phis feeding phis.
    void filter_joins() {
        std::unordered_set<std::uint32_t> used;
        for (std::size_t i = acc_begin_; i < f_.accesses.size(); ++i) used.insert(f_.accesses[i].tv);
        for (std::size_t i = cons_begin_; i < f_.cons.size(); ++i) {
            const Constraint& c = f_.cons[i];
            switch (c.kind) {
            case CKind::Deref: used.insert(f_.tvs[c.a].a); break;
            case CKind::Store: case CKind::Arg: case CKind::Return: case CKind::Embed: used.insert(c.a); break;
            case CKind::ICall: {
                used.insert(c.a);
                for (std::uint32_t t : f_.icall_args[static_cast<std::size_t>(c.c)])
                    if (t) used.insert(t);
                break;
            }
            default: break;
            }
        }
        bool grew = true;
        while (grew) {
            grew = false;
            for (const auto& jp : joins_)
                if (used.count(jp.first) && used.insert(jp.second).second) grew = true;
        }
        for (const auto& jp : joins_)
            if (used.count(jp.first)) f_.cons.push_back({CKind::Join, jp.first, jp.second, 0, 0, self_});
    }
    std::unordered_map<std::uint32_t, std::uint32_t> load_tv_, store_tv_, call_tv_;  // by pc

    static void widen(State& s) {
        for (int r = 1; r < 32; ++r)
            if (s.r[r].k == kPtr && s.r[r].s == 0) s.r[r].s = 1;
    }

    Val join_val(const Val& a, const Val& b, std::uint32_t joinvar) {
        if (a == b) return a;
        if (a.k == kPtr && b.k == kConst && b.x == 0) return a;
        if (b.k == kPtr && a.k == kConst && a.x == 0) return b;
        if (a.k == kPtr && b.k == kPtr) {
            std::uint32_t tv = a.x;
            if (a.x != b.x) {
                // A phi type variable per merge point and register: it is linked to both incoming values, and the
                // links count only when the merged value is used afterwards (filter_joins), so a dead register that
                // happens to hold two unrelated pointers at a merge does not unify them.
                tv = phi_tv(joinvar);
                if (a.x != tv) joins_.insert({tv, a.x});
                if (b.x != tv) joins_.insert({tv, b.x});
            }
            std::int32_t s = a.s;
            if (b.s) s = s ? gcd32(s, b.s) : b.s;
            // `a` is the state already at the merge point: keep its offset (the phase) so that a pointer walking
            // downwards cannot lower the offset forever; the stride absorbs the difference.
            if (a.off != b.off) s = s ? gcd32(s, a.off - b.off) : gcd32(a.off - b.off, 0);
            return ptr(tv, a.off, s);
        }
        if (a.k == kGIdx && b.k == kGIdx && a.x == b.x) return gidx(a.x, gcd32(a.s, b.s));
        if (a.k == kConst && b.k == kConst && a.full && b.full && is_data_addr(a.x) && is_data_addr(b.x)) {
            // two global objects reaching one register: indexed global
            return gidx(std::min(a.x, b.x), gcd32(static_cast<std::int32_t>(a.x - b.x), 0));
        }
        return unknown(joinvar);
    }

    void flow_to(std::uint32_t pc, const State& s) {
        auto it = node_of_.find(pc);
        if (it == node_of_.end()) {
            auto so = slot_owner_.find(pc);  // a branch into a delay slot: run the slot, continue after it
            if (so == slot_owner_.end()) return;
            State t = s;
            const Item& owner = *nodes_[so->second].it;
            exec(t, owner.slot, false);
            flow_to(owner.pc + 8, t);
            return;
        }
        const std::uint32_t n = it->second;
        State& d = in_[n];
        if (!d.valid) {
            d = s;
            work_.insert(n);
            return;
        }
        bool changed = false;
        for (int r = 1; r < 32; ++r) {
            const Val j = join_val(d.r[r], s.r[r], (pc | 2u) ^ (static_cast<std::uint32_t>(r) << 24));
            if (j != d.r[r]) { d.r[r] = j; changed = true; }
        }
        {
            const Val j = join_val(d.lo, s.lo, (pc | 2u) ^ 0x3F000000u);
            if (j != d.lo) { d.lo = j; changed = true; }
        }
        std::vector<std::pair<std::int32_t, Val>> ns;
        for (const auto& p : d.slots) {
            const Val* o = s.slot(p.first);
            if (!o) { changed = true; continue; }
            const Val j = join_val(p.second, *o, (pc | 3u) ^ (static_cast<std::uint32_t>(p.first & 0xFFF) << 20));
            if (j != p.second) changed = true;
            ns.push_back({p.first, j});
        }
        if (ns.size() != d.slots.size() || changed) d.slots = std::move(ns);
        if (changed) work_.insert(n);
    }

    // --- recording helpers -------------------------------------------------------------------------------------
    std::uint32_t value_tv(const Val& v) {  // the type variable a pointer-like value denotes (0 = none)
        if (v.k == kPtr && v.off == 0 && v.s == 0) return v.x;
        if (v.k == kConst && v.x != 0) {
            if (is_code_addr(prog_, v.x)) return f_.code_tv(v.x);
            if (v.full && is_data_addr(v.x)) return f_.gobj_tv(v.x);
        }
        if (v.k == kStack) return f_.stack_tv(self_, v.off);
        return 0;
    }

    void record_access(std::uint32_t tv, std::int32_t off, std::int32_t s, const MemOp& m, std::uint32_t pc) {
        if (!recording_ || m.unaligned) return;
        f_.accesses.push_back({tv, off, s, pc, self_, m.width, m.kind});
    }
    void record_gaccess(std::uint32_t addr, std::int32_t s, const MemOp& m, std::uint32_t pc) {
        if (!recording_ || m.unaligned) return;
        f_.gaccesses.push_back({addr, s, pc, self_, m.width, m.kind});
    }

    std::uint32_t deref_tv(std::unordered_map<std::uint32_t, std::uint32_t>& memo, std::uint32_t pc) {
        auto it = memo.find(pc);
        if (it != memo.end()) return it->second;
        const std::uint32_t t = f_.new_tv(TvKind::Deref, 0, 0, self_);
        memo.emplace(pc, t);
        return t;
    }

    void bind_deref(std::uint32_t d, std::uint32_t base, std::int32_t off) {
        if (!recording_) return;
        f_.tvs[d].a = base;
        f_.tvs[d].b = static_cast<std::uint32_t>(off);
        f_.cons.push_back({CKind::Deref, d, 0, 0, 0, self_});
    }

    // --- the transfer function ---------------------------------------------------------------------------------
    void exec(State& s, const Insn& in, bool /*in_slot*/) {
        const std::uint32_t pc = in.pc;
        ++st_.instructions;
        const std::uint32_t defvar = pc | 1u;
        Val* R = s.r;
        auto set = [&](int r, const Val& v) {
            if (r != 0) R[r] = v;
        };
        const MemOp m = mem_op(in.op);
        if (m.is) {
            const Val& base = R[in.rs];
            const std::int32_t disp = in.imm;
            Val result = unknown(defvar);
            if (base.k == kPtr) {
                const std::int32_t off = base.off + disp;
                record_access(base.x, off, base.s, m, pc);
                if (!m.store && (in.op == Op::Lw || in.op == Op::Lwu)) {
                    const std::uint32_t d = deref_tv(load_tv_, pc);
                    bind_deref(d, base.x, off);
                    result = ptr(d, 0, 0);
                } else if (m.store && m.width == 4 && in.op == Op::Sw) {
                    const std::uint32_t vt = value_tv(R[in.rt]);
                    if (vt && recording_) {
                        const std::uint32_t d = deref_tv(store_tv_, pc);
                        bind_deref(d, base.x, off);
                        f_.cons.push_back({CKind::Store, vt, d, 0, pc, self_});
                    } else if (R[in.rt].k == kPtr && R[in.rt].s == 0 && recording_) {
                        const std::uint32_t d = deref_tv(store_tv_, pc);
                        bind_deref(d, base.x, off);
                        f_.cons.push_back({CKind::Embed, R[in.rt].x, d, R[in.rt].off, pc, self_});
                    }
                }
            } else if ((base.k == kConst || base.k == kGIdx) &&
                       is_data_addr(base.x + static_cast<std::uint32_t>(disp))) {  // not a null-path / small-int base
                const std::uint32_t addr = base.x + static_cast<std::uint32_t>(disp);
                const std::int32_t stride = base.k == kGIdx ? base.s : 0;
                record_gaccess(addr, stride, m, pc);
                if (base.k == kConst && base.full && base.x != 0 && base.x != kGp && is_data_addr(base.x) && disp != 0)
                    record_access(f_.gobj_tv(base.x), disp, 0, m, pc);
                if (!m.store && (in.op == Op::Lw || in.op == Op::Lwu)) {
                    result = ptr(f_.gslot_tv(addr), 0, 0);
                } else if (m.store && in.op == Op::Sw && recording_) {
                    const std::uint32_t vt = value_tv(R[in.rt]);
                    if (vt) f_.cons.push_back({CKind::Store, vt, f_.gslot_tv(addr), 0, pc, self_});
                }
            } else if (base.k == kStack) {
                const std::int32_t off = base.off + disp;
                if (m.store) {
                    s.kill_slot_range(off, m.width);
                    if (m.width >= 4 && !m.unaligned) s.set_slot(off, R[in.rt]);
                    else s.set_slot(off, unknown(defvar));
                } else if (m.width >= 4 && !m.unaligned) {
                    if (const Val* v = s.slot(off)) result = *v;
                }
            }
            if (!m.store && in.op != Op::Lwc1 && in.op != Op::Lqc2) set(in.rt, result);
            return;
        }

        const Val& A = R[in.rs];
        const Val& B = R[in.rt];
        switch (in.op) {
        case Op::Lui:
            set(in.rt, cnst(static_cast<std::uint32_t>(in.uimm()) << 16, false));
            return;
        case Op::Addiu: case Op::Daddiu: case Op::Addi: {
            Val v = unknown(defvar);
            if (in.rs == 0) v = cnst(static_cast<std::uint32_t>(in.imm), false);
            else if (A.k == kConst) v = cnst(A.x + static_cast<std::uint32_t>(in.imm), A.full || in.imm != 0);
            else if (A.k == kPtr) v = ptr(A.x, A.off + in.imm, A.s);
            else if (A.k == kStack) v = stack(A.off + in.imm);
            else if (A.k == kGIdx) v = gidx(A.x + static_cast<std::uint32_t>(in.imm), A.s);
            else if (in.imm == 0) v = A;
            set(in.rt, v);
            return;
        }
        case Op::Ori: {
            Val v = unknown(defvar);
            if (in.rs == 0) v = cnst(in.uimm(), false);
            else if (A.k == kConst) v = cnst(A.x | in.uimm(), true);
            else if (in.uimm() == 0) v = A;
            set(in.rt, v);
            return;
        }
        case Op::Addu: case Op::Daddu: case Op::Or: {
            if (in.rt == 0) { set(in.rd, A); return; }
            if (in.rs == 0) { set(in.rd, B); return; }
            if (in.op == Op::Or) { set(in.rd, unknown(defvar)); return; }
            set(in.rd, add(A, B, defvar));
            return;
        }
        case Op::Subu: case Op::Dsubu: {
            Val v = unknown(defvar);
            if (in.rt == 0) v = A;
            else if (A.k == kPtr && B.k == kConst) v = ptr(A.x, A.off - static_cast<std::int32_t>(B.x), A.s);
            else if (A.k == kConst && B.k == kConst) v = cnst(A.x - B.x, A.full);
            else if ((A.k == kScaled || A.k == kUnknown) && (B.k == kScaled || B.k == kUnknown) && A.x == B.x) {
                const std::int32_t fa = A.k == kScaled ? A.s : 1, fb = B.k == kScaled ? B.s : 1;
                if (fa != fb) v = scaled(A.x, fa - fb);
            }
            set(in.rd, v);
            return;
        }
        case Op::Sll: case Op::Dsll: {
            Val v = unknown(defvar);
            if (in.rt == 0) v = cnst(0, false);
            else if (B.k == kConst) v = cnst(B.x << in.sa, false);
            else if (B.k == kUnknown) v = scaled(B.x, 1 << in.sa);
            else if (B.k == kScaled && in.sa < 16) v = scaled(B.x, B.s << in.sa);
            set(in.rd, v);
            return;
        }
        case Op::Mult: case Op::Multu: {
            Val lo = unknown(defvar ^ 0x40000000u);
            auto sc = [&](const Val& c, const Val& x) {
                if (c.k == kConst && c.x < 0x10000u && (x.k == kUnknown || x.k == kScaled))
                    lo = scaled(x.x, static_cast<std::int32_t>(c.x) * (x.k == kScaled ? x.s : 1));
            };
            sc(A, B);
            sc(B, A);
            s.lo = lo;
            set(in.rd, lo);
            return;
        }
        case Op::Mflo:
            set(in.rd, s.lo);
            return;
        case Op::Movn: case Op::Movz: {
            const Val& D = R[in.rd];
            if (D == A) return;
            Val v = unknown(defvar);
            if (D.k == kPtr && A.k == kPtr && D.x == A.x && D.off == A.off) v = D;
            set(in.rd, v);
            return;
        }
        default:
            break;
        }
        if (in.op == Op::Div || in.op == Op::Divu || in.op == Op::Div1) s.lo = unknown(defvar ^ 0x40000000u);
        if (const int d = dest_gpr(in)) set(d, unknown(defvar));
    }

    Val add(const Val& A, const Val& B, std::uint32_t defvar) {
        auto idx_factor = [](const Val& v) -> std::int32_t {
            if (v.k == kScaled) return v.s;
            if (v.k == kUnknown) return 1;
            return 0;
        };
        const Val* p = nullptr;
        const Val* q = nullptr;
        if (A.k == kPtr || A.k == kStack || A.k == kGIdx) { p = &A; q = &B; }
        else if (B.k == kPtr || B.k == kStack || B.k == kGIdx) { p = &B; q = &A; }
        if (p) {
            if (q->k == kConst && q->x < 0x100000u) {
                if (p->k == kPtr) return ptr(p->x, p->off + static_cast<std::int32_t>(q->x), p->s);
                if (p->k == kStack) return stack(p->off + static_cast<std::int32_t>(q->x));
                return gidx(p->x + q->x, p->s);
            }
            const std::int32_t f = idx_factor(*q);
            if (!f) return unknown(defvar);
            if (p->k == kPtr) return ptr(p->x, p->off, p->s ? gcd32(p->s, f) : f);
            if (p->k == kGIdx) return gidx(p->x, gcd32(p->s, f));
            return ptr(f_.stack_tv(self_, p->off), 0, f);  // a local array
        }
        if (A.k == kConst && B.k == kConst) return cnst(A.x + B.x, A.full || B.full);
        const Val* c = A.k == kConst ? &A : (B.k == kConst ? &B : nullptr);
        if (c) {
            const Val& o = c == &A ? B : A;
            const std::int32_t f = idx_factor(o);
            if (f && c->x >= 0x100000u) return gidx(c->x, f);
            return unknown(defvar);
        }
        if ((A.k == kScaled || A.k == kUnknown) && (B.k == kScaled || B.k == kUnknown) && A.x == B.x)
            return scaled(A.x, idx_factor(A) + idx_factor(B));
        return unknown(defvar);
    }

    // Arguments of a call: record constraints for $a0..$t3.
    void record_call(const State& s, std::uint32_t callee, std::uint32_t pc) {
        if (!recording_) return;
        for (int i = 0; i < 8; ++i) {
            const Val& v = s.r[4 + i];
            const std::uint32_t pt = f_.param_tv(callee, static_cast<std::uint32_t>(i));
            if (v.k == kPtr && v.s == 0 && v.off != 0) {
                f_.cons.push_back({CKind::Embed, v.x, pt, v.off, pc, self_});
                continue;
            }
            const std::uint32_t vt = value_tv(v);
            if (vt) f_.cons.push_back({CKind::Arg, vt, pt, i, pc, self_});
        }
    }

    void clobber_after_call(State& s, std::uint32_t pc, std::uint32_t callee) {
        for (int r : {1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 24, 25, 26, 27})
            s.r[r] = unknown((pc | 3u) ^ (static_cast<std::uint32_t>(r) << 24));
        s.lo = unknown((pc | 3u) ^ 0x3F000000u);
        if (callee) {
            const std::uint32_t t = deref_tv(call_tv_, pc);
            if (recording_) {
                f_.tvs[t].kind = TvKind::CallRes;
                f_.tvs[t].a = pc;
                f_.tvs[t].b = callee;
                f_.cons.push_back({CKind::Result, t, f_.ret_tv(callee), 0, pc, self_});
            }
            s.r[2] = ptr(t, 0, 0);
        } else {
            s.r[2] = unknown((pc | 3u) ^ (2u << 24));
        }
    }

    void record_return(const State& s, std::uint32_t pc) {
        if (!recording_) return;
        const std::uint32_t vt = value_tv(s.r[2]);
        if (vt && s.r[2].k != kStack) f_.cons.push_back({CKind::Return, vt, f_.ret_tv(self_), 0, pc, self_});
    }

    void tail_call(const State& s, std::uint32_t callee, std::uint32_t pc) {
        record_call(s, callee, pc);
        if (recording_) f_.cons.push_back({CKind::Return, f_.ret_tv(callee), f_.ret_tv(self_), 0, pc, self_});
    }

    void fall(const State& s, const Node& nd, std::uint32_t next_pc) {
        if (node_of_.count(next_pc) || slot_owner_.count(next_pc)) {
            flow_to(next_pc, s);
            return;
        }
        if (next_pc == nd.chunk->end_pc) {
            const Edge& e = nd.chunk->end_edge;
            if (e.kind == EdgeKind::Local) flow_to(e.target, s);
            else if (e.kind == EdgeKind::TailFunc && e.fn) tail_call(s, e.fn->start, next_pc);
        }
    }

    void take(const State& s, const Edge& e, std::uint32_t pc) {
        switch (e.kind) {
        case EdgeKind::Local: flow_to(e.target, s); break;
        case EdgeKind::TailFunc: if (e.fn) tail_call(s, e.fn->start, pc); break;
        case EdgeKind::Return: record_return(s, pc); break;
        default: break;
        }
    }

    void transfer(std::uint32_t n) {
        const Node nd = nodes_[n];
        const Item& it = *nd.it;
        State s = in_[n];
        if (it.kind != Item::Kind::Code) return;
        if (!it.is_cf) {
            exec(s, it.insn, false);
            fall(s, nd, it.pc + 4);
            return;
        }
        if (!it.has_slot) return;  // eret
        const Insn& in = it.insn;
        const Val target_val = s.r[in.rs];
        State t = s;
        exec(t, it.slot, true);
        switch (in.op) {
        case Op::Jal: {
            if (it.edge.kind == EdgeKind::CallFunc && it.edge.fn) {
                record_call(t, it.edge.fn->start, it.pc);
                clobber_after_call(t, it.pc, it.edge.fn->start);
            } else {
                clobber_after_call(t, it.pc, 0);
            }
            t.r[31] = cnst(it.pc + 8, false);
            if (it.edge.returns) fall(t, nd, it.pc + 8);
            return;
        }
        case Op::Jalr: {
            if (recording_ && target_val.k == kPtr && target_val.off == 0 && target_val.s == 0) {
                std::vector<std::uint32_t> args(8, 0);
                for (int i = 0; i < 8; ++i) {
                    const Val& v = t.r[4 + i];
                    args[static_cast<std::size_t>(i)] = (v.k == kPtr && v.s == 0 && v.off == 0) ? v.x : value_tv(v);
                }
                f_.icall_args.push_back(std::move(args));
                f_.cons.push_back({CKind::ICall, target_val.x, 0,
                                   static_cast<std::int32_t>(f_.icall_args.size() - 1), it.pc, self_});
            }
            clobber_after_call(t, it.pc, 0);
            fall(t, nd, it.pc + 8);
            return;
        }
        case Op::Jr: {
            if (it.edge.kind == EdgeKind::Return) { record_return(t, it.pc); return; }
            if (it.edge.kind == EdgeKind::Switch) {
                for (const Edge& e : it.sw_edges) take(t, e, it.pc);
                return;
            }
            return;  // indirect tail
        }
        case Op::J:
            take(t, it.edge, it.pc);
            return;
        default:
            break;
        }
        // conditional branch
        if (in.is_likely) {
            take(t, it.edge, it.pc);
            if (!it.terminates) fall(s, nd, it.pc + 8);
        } else {
            take(t, it.edge, it.pc);
            if (!it.terminates) fall(t, nd, it.pc + 8);
        }
    }
};

}  // namespace

void analyze_program(const Program& prog, Facts& facts, AnalyzeStats& st) {
    facts.tvs.reserve(1u << 20);
    facts.new_tv(TvKind::Code, 0, 0, 0);  // tv 0 = "none"
    for (const Function& fn : prog.functions().functions) {
        ++st.functions;
        const FunctionAnalysis a = analyze_function(prog, fn);
        bool bad = false;
        for (const Problem& p : a.problems)
            if (p.kind != ProblemKind::UnownedTarget && p.kind != ProblemKind::UnownedSwitchTarget) bad = true;
        if (bad && a.problems.size() > 4) {
            ++st.skipped;
            continue;
        }
        FnAnalyzer fa(prog, facts, a, st);
        fa.run();
        ++st.analysed;
    }
}

}  // namespace p3fes::recomp::types
