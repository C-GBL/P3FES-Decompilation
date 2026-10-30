#include "handgen.h"

#include "elf_image.h"
#include "emit_cgen.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>

namespace p3fes::recomp {

// ---------------------------------------------------------------------------------------------------------------------
// Symbols (symbols/p3fes.sym)
// ---------------------------------------------------------------------------------------------------------------------

const char* SymbolTable::load_sym(const std::string& text) {
    syms.clear();
    std::size_t pos = 0;
    while (pos < text.size()) {
        std::size_t eol = text.find('\n', pos);
        if (eol == std::string::npos) eol = text.size();
        std::string line = text.substr(pos, eol - pos);
        pos = eol + 1;
        if (line.empty() || line[0] == '#') continue;
        unsigned addr = 0, size = 0;
        char kind = 0;
        char name[512] = {};
        if (std::sscanf(line.c_str(), "%x %x %c %511s", &addr, &size, &kind, name) != 4) continue;
        if (kind != 'F' && kind != 'D' && kind != 'L') continue;
        syms.push_back({addr, size, kind, name});
    }
    std::sort(syms.begin(), syms.end(), [](const Sym& a, const Sym& b) { return a.addr < b.addr; });
    return syms.empty() ? "p3fes.sym: no records" : nullptr;
}

const SymbolTable::Sym* SymbolTable::describe(std::uint32_t va) const noexcept {
    auto it = std::upper_bound(syms.begin(), syms.end(), va, [](std::uint32_t v, const Sym& s) { return v < s.addr; });
    // the last record starting at or below va; walk back over a few in case of overlaps
    for (int k = 0; k < 8 && it != syms.begin(); ++k) {
        --it;
        if (it->addr == va && it->kind != 'L') return &*it;
        if (it->kind == 'D' && va >= it->addr && va - it->addr < std::max<std::uint32_t>(it->size, 1u)) return &*it;
        if (it->kind == 'F' && va >= it->addr && va - it->addr < it->size) return nullptr;  // inside code: no data name
    }
    return nullptr;
}

namespace {

// ---------------------------------------------------------------------------------------------------------------------
// Small text helpers
// ---------------------------------------------------------------------------------------------------------------------

std::string fmt(const char* f, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, f);
    std::vsnprintf(buf, sizeof buf, f, ap);
    va_end(ap);
    return buf;
}
std::string hexu(std::uint32_t v) { return fmt("0x%Xu", v); }
std::string hex(std::uint32_t v) { return fmt("0x%X", v); }
std::string shex(std::int32_t v) { return v < 0 ? fmt("-0x%X", static_cast<unsigned>(-static_cast<long long>(v))) : fmt("0x%X", static_cast<unsigned>(v)); }

std::string sanitize(const std::string& name) {
    std::string s;
    for (char c : name) {
        const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        s += ok ? c : '_';
    }
    return s;
}

const char* const kGpr[32] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
                              "s0",   "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"};

constexpr std::uint32_t bit(unsigned r) { return r < 32 ? (1u << r) : 0u; }

// ---------------------------------------------------------------------------------------------------------------------
// What an instruction reads and writes (for the delay-slot placement decisions)
// ---------------------------------------------------------------------------------------------------------------------

struct RW {
    std::uint32_t gr = 0, gw = 0;  // GPRs read / written
    bool fcc_w = false;            // writes FCR31's C bit (c.cond.s, ctc1)
    bool may_cp = true;            // may reach a check point or the bus (memory, system, COP0, COP2 transfers)
};

RW rw_of(const Insn& in) {
    using enum Op;
    RW r;
    auto pure = [&] { r.may_cp = false; };
    switch (in.op) {
    case Add: case Addu: case Sub: case Subu: case And: case Or: case Xor: case Nor: case Slt: case Sltu:
    case Daddu: case Dsubu: case Movn: case Movz:
    case Paddh: case Paddub: case Padduw: case Paddw: case Pand: case Pcgth: case Pcpyld: case Pcpyud:
    case Pextlb: case Pextlh: case Pextlw: case Pextub: case Pextuw: case Pmaxh: case Pminh:
    case Pnor: case Por: case Ppacb: case Ppach: case Ppacw: case Psubb: case Psubw: case Pxor: case Qfsrv:
    case Mult: case Multu: case Madd: case Maddu: case Mult1: case Multu1: case Maddu1: case Phmadh:
        r.gr = bit(in.rs) | bit(in.rt) | ((in.op == Movn || in.op == Movz) ? bit(in.rd) : 0u);
        r.gw = bit(in.rd);
        pure();
        break;
    case Sllv: case Srlv: case Srav: case Dsllv: case Dsrlv:
        r.gr = bit(in.rs) | bit(in.rt); r.gw = bit(in.rd); pure(); break;
    case Div: case Divu: case Div1:
        r.gr = bit(in.rs) | bit(in.rt); pure(); break;
    case Addi: case Addiu: case Daddiu: case Slti: case Sltiu: case Andi: case Ori: case Xori:
        r.gr = bit(in.rs); r.gw = bit(in.rt); pure(); break;
    case Lui:
        r.gw = bit(in.rt); pure(); break;
    case Sll: case Srl: case Sra: case Dsll: case Dsrl: case Dsra: case Dsll32: case Dsrl32: case Dsra32:
    case Psllh: case Psrlh: case Psrah: case Psraw: case Pcpyh: case Pexew: case Prot3w:
        r.gr = bit(in.rt); r.gw = bit(in.rd); pure(); break;
    case Mfhi: case Mflo: case Mfhi1: case Mflo1: case Mfsa: case Pmfhl:
        r.gw = bit(in.rd); pure(); break;
    case Mthi: case Mtlo: case Mthi1: case Mtlo1: case Mtsa: case Mtsab: case Mtsah:
        r.gr = bit(in.rs); pure(); break;
    case Lb: case Lbu: case Lh: case Lhu: case Lw: case Lwu: case Ld: case Lq:
        r.gr = bit(in.rs); r.gw = bit(in.rt); break;
    case Lwl: case Lwr: case Ldl: case Ldr:
        r.gr = bit(in.rs) | bit(in.rt); r.gw = bit(in.rt); break;
    case Sb: case Sh: case Sw: case Swl: case Swr: case Sd: case Sdl: case Sdr: case Sq:
        r.gr = bit(in.rs) | bit(in.rt); break;
    case Lwc1: case Swc1: case Lqc2: case Sqc2: case Cache:
        r.gr = bit(in.rs); break;
    case AddS: case SubS: case MulS: case DivS: case MaddS: case MsubS: case AddaS: case SubaS: case MulaS:
    case MaddaS: case MsubaS: case AbsS: case MovS: case NegS: case CvtSW: case CvtWS: case SqrtS:
    case Vadd: case Vsub: case Vmul: case Vmadd: case Vmsub: case Vmax: case Vmini: case Vopmsub: case Vadda:
    case Vmadda: case Vmsuba: case Vmula: case Vopmula: case Vaddi: case Vmuli: case Vmulq: case Vabs: case Vmove:
    case Vftoi0: case Vitof0: case Vsqrt: case Vrsqrt: case Vnop: case Vwaitq:
        pure(); break;
    case CEqS: case CLeS: case CLtS:
        r.fcc_w = true; pure(); break;
    case Mfc1:
        r.gw = bit(in.rt); pure(); break;
    case Mtc1:
        r.gr = bit(in.rt); pure(); break;
    case Ctc1:
        r.gr = bit(in.rt); r.fcc_w = true; pure(); break;
    case Mfc0: case Qmfc2: case Cfc2:
        r.gw = bit(in.rt); break;
    case Mtc0: case Qmtc2: case Ctc2:
        r.gr = bit(in.rt); break;
    case Syscall:
        r.gr = 0xFFFFFFFFu; r.gw = 0xFFFFFFFEu; break;
    default:
        break;  // sync / ei / di / break / eret / invalid: conservative
    }
    r.gr &= ~1u;
    r.gw &= ~1u;
    return r;
}

// ---------------------------------------------------------------------------------------------------------------------
// The CFG mirrored from generate_function
// ---------------------------------------------------------------------------------------------------------------------

struct Cond {
    enum K : std::uint8_t { Eq, Ne, Lez, Gtz, Ltz, Gez, C1T, C1F, C0T, C0F, Saved, NotSaved } k = Eq;
    std::uint8_t rs = 0, rt = 0;
};

Cond negate(Cond c) {
    static const Cond::K neg[] = {Cond::Ne, Cond::Eq, Cond::Gtz, Cond::Lez, Cond::Gez, Cond::Ltz,
                                  Cond::C1F, Cond::C1T, Cond::C0F, Cond::C0T, Cond::NotSaved, Cond::Saved};
    c.k = neg[c.k];
    return c;
}

Cond cond_of(const Insn& in) {
    using enum Op;
    Cond c;
    c.rs = in.rs;
    c.rt = in.rt;
    switch (in.op) {
    case Beq: case Beql: c.k = Cond::Eq; break;
    case Bne: case Bnel: c.k = Cond::Ne; break;
    case Blez: case Blezl: c.k = Cond::Lez; break;
    case Bgtz: case Bgtzl: c.k = Cond::Gtz; break;
    case Bltz: case Bltzl: c.k = Cond::Ltz; break;
    case Bgez: case Bgezl: c.k = Cond::Gez; break;
    case Bc1t: case Bc1tl: c.k = Cond::C1T; break;
    case Bc1f: case Bc1fl: c.k = Cond::C1F; break;
    case Bc0f: c.k = Cond::C0F; break;
    default: c.k = Cond::Eq; break;
    }
    return c;
}

// Does the delay slot change what the branch condition reads?
bool slot_conflicts(const Cond& c, const Insn& slot) {
    const RW r = rw_of(slot);
    switch (c.k) {
    case Cond::Eq: case Cond::Ne: return (r.gw & (bit(c.rs) | bit(c.rt)) & ~1u) != 0;
    case Cond::Lez: case Cond::Gtz: case Cond::Ltz: case Cond::Gez: return (r.gw & bit(c.rs) & ~1u) != 0;
    case Cond::C1T: case Cond::C1F: return r.fcc_w;
    case Cond::C0T: case Cond::C0F: return r.may_cp;
    default: return true;
    }
}

struct Stmt {
    enum K : std::uint8_t { Ins, Charge, Check, Call, SaveCond, SaveJt, TailNoRet, Eret } k = Ins;
    Insn insn;                // Ins / Eret; Call: the jal / jalr
    std::size_t n = 0;        // Charge
    bool has_slot = false;    // Call
    Insn slot;
    bool slot_first = false;  // Call: the slot is written before the call statement (independent of the link / target)
    bool noreturn = false;    // Call: the callee cannot return (the recompiled body falls through textually after it)
    Edge edge;                // Call (direct) / TailNoRet
    bool indirect = false;    // Call: jalr
    Cond cond;                // SaveCond
    std::uint8_t reg = 0;     // SaveJt
};

struct Target {
    // Shared: a jump into the region another entry point of the same function owns (a function with mid-body
    // entries): the shared body of that entry is called and this function returns.
    enum K : std::uint8_t { Block, Return, Tail, TailEntry, Unreachable, Shared } k = Block;
    int block = -1;
    std::uint32_t label = 0;  // Block: the label address (resolved to `block` after the walk)
    bool by_label = false;    // resolve `label` (false: `block` already set)
    const Function* fn = nullptr;
    std::uint32_t addr = 0;   // Tail / TailEntry / Unreachable / Shared (the entry's address)
};

struct EdgeT {
    std::vector<Stmt> actions;
    Target t;
};

struct Term {
    enum K : std::uint8_t { Open, Goto, Cond, Switch, Return, Tail, TailEntry, TailPtr, Unreachable, Shared } k = Open;
    EdgeT e;            // Goto: the edge; Cond: the taken edge; Tail / TailEntry: fn / addr; Unreachable / Shared: addr
    int fall = -1;      // Cond: not taken
    struct Cond cond;
    bool jt_saved = false;
    std::uint8_t jt_reg = 0;
    std::vector<std::pair<std::uint32_t, EdgeT>> cases;  // Switch
    const SwitchSite* sw = nullptr;
    std::uint32_t pc = 0;
};

struct Block {
    std::uint32_t pc = 0;
    bool label = false;
    std::vector<Stmt> stmts;
    Term term;
};

// ---------------------------------------------------------------------------------------------------------------------
// emit_cgen's block model (copied rule for rule: a basic block's words, leaders, the slot-label continuation)
// ---------------------------------------------------------------------------------------------------------------------

bool is_conditional(const Item& it) noexcept { return it.is_cf && it.has_slot && !it.unconditional; }

bool is_leader(const FunctionAnalysis& a, const ChunkAnalysis& ch, std::size_t i) {
    const Item& it = ch.items[i];
    if (it.pc == a.fn->start) return true;
    if (a.labels.count(it.pc)) return true;
    return i > 0 && ch.items[i - 1].reachable && is_conditional(ch.items[i - 1]);
}

std::size_t block_words(const FunctionAnalysis& a, const ChunkAnalysis& ch, std::size_t i) {
    std::size_t n = 0;
    for (std::size_t k = i; k < ch.items.size(); ++k) {
        const Item& it = ch.items[k];
        if (!it.reachable) break;
        if (k != i && is_leader(a, ch, k)) break;
        if (it.kind == Item::Kind::Data) break;
        if (!it.is_cf) {
            ++n;
            continue;
        }
        if (!it.has_slot) {
            ++n;
            break;
        }
        if (is_conditional(it)) {
            n += (it.slot_is_label && !it.insn.is_likely) ? 1u : 2u;
            break;
        }
        n += 2;
        if (it.terminates) break;
    }
    return n;
}

std::size_t continuation_words(const FunctionAnalysis& a, const ChunkAnalysis& ch, std::size_t i) {
    if (i >= ch.items.size() || !ch.items[i].reachable || is_leader(a, ch, i)) return 0;
    return block_words(a, ch, i);
}

bool is_backedge(const Edge& e, std::uint32_t from_pc) noexcept { return e.kind == EdgeKind::Local && e.target <= from_pc; }

// ---------------------------------------------------------------------------------------------------------------------
// The walker: one pass over the analysis in generate_function's order, building blocks instead of text.
// ---------------------------------------------------------------------------------------------------------------------

class Builder {
public:
    Builder(const FunctionAnalysis& a) : a_(a) {}

    std::vector<Block> blocks;
    std::map<std::uint32_t, int> label_block;
    int entry = -1;
    std::string error;

    bool build() {
        for (const ChunkAnalysis& ch : a_.chunks) {
            for (std::size_t i = 0; i < ch.items.size(); ++i) {
                const Item& it = ch.items[i];
                if (!it.reachable) {
                    if (it.is_cf && it.slot_is_label) slot_label_tail(ch, i);
                    continue;
                }
                const bool lab = a_.labels.count(it.pc) && !emitted_labels_.count(it.pc);
                if (lab) {
                    emitted_labels_.insert(it.pc);
                    start(it.pc, true);
                } else if (!open_ || (is_leader(a_, ch, i) && !blocks[cur_].stmts.empty())) {
                    start(it.pc, false);
                }
                if (entry < 0) entry = cur_;
                if (is_leader(a_, ch, i)) {
                    const std::size_t n = block_words(a_, ch, i);
                    if (n) add(charge(n));
                }
                if (it.kind == Item::Kind::Data) {
                    Term t;
                    t.k = Term::Unreachable;
                    t.e.t.k = Target::Unreachable;
                    t.e.t.addr = it.pc;
                    close(t);
                    continue;
                }
                if (it.is_cf) {
                    if (!cf(ch, i)) return false;
                    continue;
                }
                if (it.insn.word != 0) {
                    Stmt s;
                    s.insn = it.insn;
                    add(s);
                }
            }
            if (ch.end_reachable) {
                if (!open_) start(ch.end_pc, false);
                if (!uncond_edge(ch.end_edge, 0, false)) return false;
            }
        }
        for (std::uint32_t l : a_.labels) {
            if (emitted_labels_.count(l)) continue;
            emitted_labels_.insert(l);
            start(l, true);
            Term t;
            t.k = Term::Unreachable;
            t.e.t.k = Target::Unreachable;
            t.e.t.addr = l;
            close(t);
        }
        if (open_ || !pending_.empty()) {
            // Falling off the end of the generated function returns.
            if (!open_) start(0, false);
            Term t;
            t.k = Term::Return;
            close(t);
        }
        // Resolve label targets.
        auto resolve = [&](Target& t) {
            if (t.k != Target::Block || !t.by_label) return true;
            auto it = label_block.find(t.label);
            if (it == label_block.end()) {
                error = fmt("no block for label 0x%08x", t.label);
                return false;
            }
            t.block = it->second;
            t.by_label = false;
            return true;
        };
        for (Block& b : blocks) {
            if (!resolve(b.term.e.t)) return false;
            for (auto& c : b.term.cases)
                if (!resolve(c.second.t)) return false;
        }
        if (entry < 0 || blocks[entry].pc != a_.fn->start) {
            error = "the first emitted block is not the function start";
            return false;
        }
        return true;
    }

private:
    const FunctionAnalysis& a_;
    int cur_ = -1;
    bool open_ = false;
    std::vector<int> pending_;  // blocks whose fall-through successor is the next started block
    std::set<std::uint32_t> emitted_labels_;

    static Stmt charge(std::size_t n) {
        Stmt s;
        s.k = Stmt::Charge;
        s.n = n;
        return s;
    }
    static Stmt check() {
        Stmt s;
        s.k = Stmt::Check;
        return s;
    }
    static Stmt ins(const Insn& in) {
        Stmt s;
        s.insn = in;
        return s;
    }

    int new_block(std::uint32_t pc, bool label) {
        Block b;
        b.pc = pc;
        b.label = label;
        blocks.push_back(std::move(b));
        const int id = static_cast<int>(blocks.size()) - 1;
        if (label) label_block[pc] = id;
        return id;
    }
    // Start a block at `pc`: the open block (and every pending one) falls into it.
    void start(std::uint32_t pc, bool label) {
        const int b = new_block(pc, label);
        if (open_) fall_into(cur_, b);
        for (int p : pending_) patch_fall(p, b);
        pending_.clear();
        cur_ = b;
        open_ = true;
    }
    void fall_into(int from, int to) {
        Term t;
        t.k = Term::Goto;
        t.e.t.block = to;
        blocks[from].term = t;
    }
    void patch_fall(int p, int to) {
        if (blocks[p].term.k == Term::Cond) blocks[p].term.fall = to;
        else fall_into(p, to);
    }
    // Continue in an already created block (the code after a call whose delay slot is a branch target).
    void resume(int b) {
        cur_ = b;
        open_ = true;
    }
    void add(const Stmt& s) {
        if (!open_) start(0, false);  // dead text (never reached; dropped with the unreachable blocks)
        blocks[cur_].stmts.push_back(s);
    }
    void close(const Term& t) {
        if (!open_) start(0, false);
        blocks[cur_].term = t;
        open_ = false;
    }
    void close_pending(Term t) {  // a Cond whose not-taken successor is the next started block
        close(t);
        pending_.push_back(cur_);
    }

    void add_slot(const Item& it, std::vector<Stmt>& to) {
        if (it.has_slot && it.slot.word != 0) to.push_back(ins(it.slot));
    }
    void add_slot(const Item& it) {
        if (it.has_slot && it.slot.word != 0) add(ins(it.slot));
    }

    // emit_cgen's emit_slot_label_tail: the slot word again under its own label, charged 1 + the continuation.
    void slot_label_tail(const ChunkAnalysis& ch, std::size_t idx) {
        const Item& it = ch.items[idx];
        emitted_labels_.insert(it.pc + 4);
        start(it.pc + 4, true);
        add(charge(1 + continuation_words(a_, ch, idx + 1)));
        add_slot(it);
    }

    // A branch / switch edge as a Target (+ actions). False for a no-return tail call inside a branch edge (the
    // recompiled body would fall out of its `if`: not mirrored, the function is refused).
    bool edge_target(const Edge& e, std::uint32_t from_pc, bool branch, EdgeT& out) {
        if (branch && is_backedge(e, from_pc)) out.actions.push_back(check());
        switch (e.kind) {
        case EdgeKind::Local:
            out.t.k = Target::Block;
            out.t.label = e.target;
            out.t.by_label = true;
            return true;
        case EdgeKind::TailFunc:
        case EdgeKind::TailEntry:
            if (!e.returns) {
                error = fmt("a tail call to a root that cannot return inside a branch edge (to 0x%08x)", e.target);
                return false;
            }
            out.t.k = e.kind == EdgeKind::TailFunc ? Target::Tail : Target::TailEntry;
            out.t.fn = e.fn;
            out.t.addr = e.target;
            return true;
        case EdgeKind::Return:
            out.t.k = Target::Return;
            return true;
        case EdgeKind::Unreachable:
        case EdgeKind::Unowned:
            out.t.k = Target::Unreachable;
            out.t.addr = e.target;
            return true;
        default:
            error = fmt("unexpected edge kind in a branch at 0x%08x", from_pc);
            return false;
        }
    }

    // The taken edge of an unconditional jump (or a chunk's fall-through end): closes the block, or keeps it open
    // when the recompiled body falls through textually (a tail call to a root that cannot return).
    bool uncond_edge(const Edge& e, std::uint32_t from_pc, bool branch) {
        if ((e.kind == EdgeKind::TailFunc || e.kind == EdgeKind::TailEntry) && !e.returns) {
            Stmt s;
            s.k = Stmt::TailNoRet;
            s.edge = e;
            add(s);
            return true;
        }
        Term t;
        t.pc = from_pc;
        if (!edge_target(e, from_pc, branch, t.e)) return false;
        switch (t.e.t.k) {
        case Target::Block: t.k = Term::Goto; break;
        case Target::Return: t.k = Term::Return; break;
        case Target::Tail: t.k = Term::Tail; break;
        case Target::TailEntry: t.k = Term::TailEntry; break;
        case Target::Unreachable: t.k = Term::Unreachable; break;
        }
        close(t);
        return true;
    }

    Stmt call_stmt(const Item& it) {
        Stmt s;
        s.k = Stmt::Call;
        s.insn = it.insn;
        s.has_slot = it.has_slot && it.slot.word != 0;
        s.slot = it.slot;
        s.indirect = it.edge.kind == EdgeKind::IndirectCall;
        s.edge = it.edge;
        s.noreturn = !s.indirect && it.terminates;
        if (s.has_slot) {
            const RW r = rw_of(it.slot);
            const std::uint32_t link = s.indirect ? bit(it.insn.rd) : bit(31);
            bool ok = !r.may_cp && !(r.gr & link) && !(r.gw & link);
            if (s.indirect && (r.gw & bit(it.insn.rs))) ok = false;
            s.slot_first = ok;
        }
        return s;
    }

    bool cf(const ChunkAnalysis& ch, std::size_t idx) {
        const Item& it = ch.items[idx];
        const Insn& in = it.insn;
        if (in.op == Op::Eret) {
            Stmt s;
            s.k = Stmt::Eret;
            s.insn = in;
            add(s);
            Term t;
            t.k = Term::Return;
            close(t);
            return true;
        }
        const EdgeKind ek = it.edge.kind;
        if (ek == EdgeKind::Switch || ek == EdgeKind::IndirectTail) {
            Term t;
            t.pc = in.pc;
            t.jt_reg = in.rs;
            const bool slot = it.has_slot && it.slot.word != 0;
            t.jt_saved = slot && (rw_of(it.slot).gw & bit(in.rs)) != 0;
            if (t.jt_saved) {
                Stmt s;
                s.k = Stmt::SaveJt;
                s.reg = in.rs;
                add(s);
            }
            add_slot(it);
            if (ek == EdgeKind::Switch) {
                t.k = Term::Switch;
                t.sw = it.sw;
                for (const Edge& e : it.sw_edges) {
                    EdgeT et;
                    if (!edge_target(e, in.pc, true, et)) return false;
                    t.cases.emplace_back(e.target, std::move(et));
                }
            } else {
                t.k = Term::TailPtr;
            }
            close(t);
            if (it.slot_is_label) slot_label_tail(ch, idx);
            return true;
        }
        if (ek == EdgeKind::IndirectCall || ek == EdgeKind::CallFunc || ek == EdgeKind::CallEntry) {
            add(call_stmt(it));
            const bool noreturn = ek != EdgeKind::IndirectCall && it.terminates;
            if (it.slot_is_label) {
                if (noreturn) {
                    // `{ link; slot; fn(ctx); }` then the slot label: the text falls into it.
                    slot_label_tail(ch, idx);
                } else {
                    // `{ link; slot; call; goto skip; } L_slot: charge(1 + cont); slot; skip:`
                    const int skip = new_block(in.pc + 8, false);
                    fall_into(cur_, skip);
                    open_ = false;
                    slot_label_tail(ch, idx);
                    fall_into(cur_, skip);
                    resume(skip);
                }
            }
            return true;
        }
        if (it.unconditional) {
            add_slot(it);
            if (!uncond_edge(it.edge, in.pc, true)) return false;
            if (it.slot_is_label) slot_label_tail(ch, idx);
            return true;
        }
        // Conditional branch.
        Term t;
        t.k = Term::Cond;
        t.pc = in.pc;
        t.cond = cond_of(in);
        if (in.is_likely) {
            add_slot(it, t.e.actions);  // the slot runs only when taken
            if (!edge_target(it.edge, in.pc, true, t.e)) return false;
            if (it.slot_is_label) {
                // not taken: `goto skip` past the slot label; the slot label falls into skip too
                const int skip = new_block(in.pc + 8, false);
                close(t);
                blocks[cur_].term.fall = skip;
                slot_label_tail(ch, idx);
                fall_into(cur_, skip);
                resume(skip);
            } else {
                close_pending(t);
            }
            return true;
        }
        if (it.slot_is_label) {
            // taken: charge 1, the slot, the edge; not taken: the slot under its label (falls into the next block)
            t.e.actions.push_back(charge(1));
            add_slot(it, t.e.actions);
            if (!edge_target(it.edge, in.pc, true, t.e)) return false;
            close_pending(t);
            slot_label_tail(ch, idx);
            return true;
        }
        // The slot runs on both paths: written before the test when it leaves the condition's operands alone,
        // otherwise after the test's value is saved.
        if (it.has_slot && it.slot.word != 0 && slot_conflicts(t.cond, it.slot)) {
            Stmt s;
            s.k = Stmt::SaveCond;
            s.cond = t.cond;
            add(s);
            t.cond.k = Cond::Saved;
        }
        add_slot(it);
        if (!edge_target(it.edge, in.pc, true, t.e)) return false;
        close_pending(t);
        return true;
    }
};

// ---------------------------------------------------------------------------------------------------------------------
// Graph analysis: reachability, dominators, post-dominators, natural loops
// ---------------------------------------------------------------------------------------------------------------------

struct Loop {
    int header = -1;
    std::vector<char> body;
    int size = 0;
    int parent = -1;
    int follow = -1;
};

struct Graph {
    int n = 0;
    int entry = 0;
    std::vector<std::vector<int>> succ, pred;
    std::vector<char> exits;  // has an edge out of the function (return, tail, unreachable, switch default)
    std::vector<char> reach;
    std::vector<int> idom, ipdom;
    std::vector<Loop> loops;
    std::vector<int> loop_of, header_loop;

    void build(const std::vector<Block>& bl, int e) {
        n = static_cast<int>(bl.size());
        entry = e;
        succ.assign(n, {});
        pred.assign(n, {});
        exits.assign(n, 0);
        for (int b = 0; b < n; ++b) {
            const Term& t = bl[b].term;
            auto add = [&](const Target& x) {
                if (x.k == Target::Block) {
                    if (std::find(succ[b].begin(), succ[b].end(), x.block) == succ[b].end()) succ[b].push_back(x.block);
                } else {
                    exits[b] = 1;
                }
            };
            switch (t.k) {
            case Term::Goto: add(t.e.t); break;
            case Term::Cond:
                add(t.e.t);
                if (t.fall >= 0 && std::find(succ[b].begin(), succ[b].end(), t.fall) == succ[b].end()) succ[b].push_back(t.fall);
                break;
            case Term::Switch:
                for (const auto& c : t.cases) add(c.second.t);
                // The default (an entry that is not one of the table's targets: the dispatch table) is not counted as
                // an exit: retail tables hold only their targets, and counting it would hide the cases' merge point.
                // (Post-dominance only decides the layout, never what runs.)
                break;
            default: exits[b] = 1; break;
            }
        }
        // reachability from the entry
        reach.assign(n, 0);
        std::vector<int> st{entry};
        reach[entry] = 1;
        while (!st.empty()) {
            const int b = st.back();
            st.pop_back();
            for (int s : succ[b])
                if (!reach[s]) {
                    reach[s] = 1;
                    st.push_back(s);
                }
        }
        for (int b = 0; b < n; ++b)
            if (reach[b])
                for (int s : succ[b]) pred[s].push_back(b);
        dominators();
        postdominators();
        find_loops(bl);
    }

    bool dominates(int a, int b) const {  // a dom b
        while (b >= 0) {
            if (a == b) return true;
            if (b == entry) return false;
            b = idom[b];
        }
        return false;
    }

private:
    // Cooper, Harvey, Kennedy: "A Simple, Fast Dominance Algorithm".
    static void dom_solve(int nn, int root, const std::vector<std::vector<int>>& fwd, const std::vector<std::vector<int>>& back,
                          std::vector<int>& out) {
        std::vector<int> order, index(nn, -1);
        std::vector<char> seen(nn, 0);
        // iterative post-order DFS
        std::vector<std::pair<int, std::size_t>> st{{root, 0}};
        seen[root] = 1;
        while (!st.empty()) {
            auto& [b, k] = st.back();
            if (k < fwd[b].size()) {
                const int s = fwd[b][k++];
                if (!seen[s]) {
                    seen[s] = 1;
                    st.push_back({s, 0});
                }
            } else {
                order.push_back(b);
                st.pop_back();
            }
        }
        std::reverse(order.begin(), order.end());  // reverse post-order
        for (std::size_t i = 0; i < order.size(); ++i) index[order[i]] = static_cast<int>(i);
        out.assign(nn, -1);
        out[root] = root;
        auto intersect = [&](int b1, int b2) {
            while (b1 != b2) {
                while (index[b1] > index[b2]) b1 = out[b1];
                while (index[b2] > index[b1]) b2 = out[b2];
            }
            return b1;
        };
        for (bool changed = true; changed;) {
            changed = false;
            for (std::size_t i = 1; i < order.size(); ++i) {
                const int b = order[i];
                int nd = -1;
                for (int p : back[b]) {
                    if (index[p] < 0 || out[p] < 0) continue;
                    nd = nd < 0 ? p : intersect(p, nd);
                }
                if (nd >= 0 && out[b] != nd) {
                    out[b] = nd;
                    changed = true;
                }
            }
        }
    }

    void dominators() {
        dom_solve(n, entry, succ, pred, idom);
        idom[entry] = -1;
    }

    void postdominators() {
        // reverse graph with a virtual exit X = n
        const int X = n;
        std::vector<std::vector<int>> rf(n + 1), rb(n + 1);
        for (int b = 0; b < n; ++b) {
            if (!reach[b]) continue;
            for (int s : succ[b]) {
                rf[s].push_back(b);
                rb[b].push_back(s);
            }
            if (exits[b]) {
                rf[X].push_back(b);
                rb[b].push_back(X);
            }
        }
        std::vector<int> pd;
        dom_solve(n + 1, X, rf, rb, pd);
        ipdom.assign(n, -1);
        for (int b = 0; b < n; ++b) ipdom[b] = (pd[b] >= 0 && pd[b] != X && pd[b] != b) ? pd[b] : -1;
    }

    void find_loops(const std::vector<Block>& bl) {
        std::map<int, std::vector<int>> latches;  // header -> latches
        for (int b = 0; b < n; ++b) {
            if (!reach[b]) continue;
            for (int s : succ[b])
                if (dominates(s, b)) latches[s].push_back(b);
        }
        for (const auto& [h, ls] : latches) {
            Loop L;
            L.header = h;
            L.body.assign(n, 0);
            L.body[h] = 1;
            std::vector<int> st;
            for (int l : ls)
                if (!L.body[l]) {
                    L.body[l] = 1;
                    st.push_back(l);
                }
            while (!st.empty()) {
                const int b = st.back();
                st.pop_back();
                for (int p : pred[b])
                    if (!L.body[p]) {
                        L.body[p] = 1;
                        st.push_back(p);
                    }
            }
            for (char c : L.body) L.size += c;
            loops.push_back(std::move(L));
        }
        const int nl = static_cast<int>(loops.size());
        for (int i = 0; i < nl; ++i) {
            int best = -1;
            for (int j = 0; j < nl; ++j) {
                if (i == j || !loops[j].body[loops[i].header] || loops[j].size <= loops[i].size) continue;
                if (best < 0 || loops[j].size < loops[best].size) best = j;
            }
            loops[i].parent = best;
        }
        loop_of.assign(n, -1);
        header_loop.assign(n, -1);
        for (int i = 0; i < nl; ++i) {
            header_loop[loops[i].header] = i;
            for (int b = 0; b < n; ++b)
                if (loops[i].body[b] && (loop_of[b] < 0 || loops[loop_of[b]].size > loops[i].size)) loop_of[b] = i;
        }
        // The follow: the post-dominator of the header when it lies outside, else the exit just after the body's
        // last block (the compiler's layout), else the lowest exit.
        for (Loop& L : loops) {
            std::set<int> exits_set;
            std::uint32_t max_pc = 0;
            for (int b = 0; b < n; ++b) {
                if (!L.body[b]) continue;
                max_pc = std::max(max_pc, bl[b].pc);
                for (int s : succ[b])
                    if (!L.body[s]) exits_set.insert(s);
            }
            if (exits_set.empty()) continue;
            const int p = ipdom[L.header];
            if (p >= 0 && exits_set.count(p)) {
                L.follow = p;
                continue;
            }
            int after = -1, lowest = -1;
            for (int e : exits_set) {
                if (bl[e].pc > max_pc && (after < 0 || bl[e].pc < bl[after].pc)) after = e;
                if (lowest < 0 || bl[e].pc < bl[lowest].pc) lowest = e;
            }
            L.follow = after >= 0 ? after : lowest;
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------
// The structured body (a small AST) and its printer
// ---------------------------------------------------------------------------------------------------------------------

struct Node {
    enum K : std::uint8_t { Line, Label, If, For, Switch } k = Line;
    std::string text;      // Line: the statement; If: the condition; Switch: the expression
    std::string comment;   // Line: trailing comment
    int target = -1;       // Line: goto target block; Label: the block
    bool term = false;     // Line: control does not continue after it
    std::vector<Node> a, b;
    struct Case {
        std::string head;  // "case 0x...u:  // table[...]"
        std::vector<Node> body;
    };
    std::vector<Case> cases;
};
using Seq = std::vector<Node>;

Node line(std::string t, std::string c = {}, bool term = false) {
    Node n;
    n.text = std::move(t);
    n.comment = std::move(c);
    n.term = term;
    return n;
}

// ---------------------------------------------------------------------------------------------------------------------
// The generator for one function
// ---------------------------------------------------------------------------------------------------------------------

class Gen {
public:
    Gen(const FunctionAnalysis& a, const ElfImage* elf, const SymbolTable* syms, const HandgenOptions& opt, HandgenFunction& out)
        : a_(a), elf_(elf), syms_(syms), opt_(opt), out_(out) {}

    bool run() {
        const Function& f = *a_.fn;
        if (!a_.problems.empty()) return fail("the analysis reports problems");
        Builder b(a_);
        if (!b.build()) return fail(b.error);
        base_blocks_ = std::move(b.blocks);
        const std::string name = sanitize(f.name);
        out_.start = f.start;
        out_.name = name;
        out_.symbol = function_symbol(f);
        out_.replaced_row = fmt("0x%x %s", f.start, f.name.c_str());
        const char* banner =
            "// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra\n"
            "// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.\n";
        std::string& o = out_.body;
        const std::string sfx = opt_.body_suffix;
        const auto definition = [&](const std::string& fname, bool is_static, const Root& r) {
            return std::string(is_static ? "static " : "") + "void " + fname + "(EEContext& ctx) {\n    using namespace hg;\n" + r.decls +
                   r.text + "}\n";
        };
        if (!a_.entry_form) {
            Root r;
            if (!emit_root(b.entry, {}, true, r)) return false;
            o += fmt("// 0x%08X %s -- %u bytes", f.start, f.name.c_str(), f.size);
            if (a_.chunks.size() > 1) o += fmt(", %zu chunks", a_.chunks.size());
            o += r.frame + "\n" + banner;
            o += definition(name + sfx, false, r);
            if (opt_.shim) {
                out_.shim = "void p3fes::recomp_gen::" + out_.symbol + opt_.shim_suffix + "(p3fes::EEContext& ctx) { p3fes::game::" + name + sfx +
                            "(ctx); }\n";
            }
            out_.decl = fmt("void %s%s(EEContext& ctx);  // 0x%X (register ABI: arguments in $a0.., the result in $v0)\n", name.c_str(), sfx.c_str(),
                            f.start);
            for (const auto& [sym, decl] : callees_) out_.callees.push_back(decl);
            return true;
        }

        // --- a function with mid-body entries (the recompiled entry form): one game:: function per entry point. The
        // region an entry point reaches and that never flows back to another one is its own; a root that flows into
        // such an entry calls the entry's shared body there (static, forward-declared) and returns, so every path
        // runs the same statements, charges and check points as the recompiled body: one entry check per call, the
        // blocks from the entered address on. A region two roots reach without passing through an entry (an entry
        // inside a loop with the start) is written in both.
        std::vector<int> roots{b.entry};
        std::vector<std::uint32_t> root_pc{f.start};
        for (std::uint32_t e : a_.entries) {
            const auto it = b.label_block.find(e);
            if (it == b.label_block.end()) return fail(fmt("no block for the entry 0x%08x", e));
            roots.push_back(it->second);
            root_pc.push_back(e);
            out_.replaced_row += fmt(" @0x%x", e);
        }
        const std::size_t n_entry_roots = roots.size();
        std::vector<std::vector<char>> R(roots.size());
        for (std::size_t i = 0; i < roots.size(); ++i) R[i] = reach_from(base_blocks_, roots[i]);
        // Join blocks: a block two entry points reach along different paths without passing through an entry (two
        // wrappers that both jump into one worker) is a root of its own, a common body both call, instead of a copy in
        // each; a small return block (an epilogue) is not (it is written out at each arrival, as in any function).
        {
            const std::size_t nb = base_blocks_.size();
            std::vector<unsigned> rs(nb, 0);  // which roots reach the block (bit per root)
            for (std::size_t i = 0; i < roots.size(); ++i)
                for (std::size_t b = 0; b < nb; ++b)
                    if (R[i][b]) rs[b] |= 1u << i;
            std::vector<std::vector<int>> preds(nb);
            for (std::size_t b = 0; b < nb; ++b) {
                const Term& tm = base_blocks_[b].term;
                const auto add = [&](const Target& x) {
                    if (x.k == Target::Block && x.block >= 0) preds[static_cast<std::size_t>(x.block)].push_back(static_cast<int>(b));
                };
                add(tm.e.t);
                if (tm.k == Term::Cond && tm.fall >= 0) preds[static_cast<std::size_t>(tm.fall)].push_back(static_cast<int>(b));
                for (const auto& c : tm.cases) add(c.second.t);
            }
            for (std::size_t b = 0; b < nb; ++b) {
                if (!rs[b] || !(rs[b] & (rs[b] - 1))) continue;  // reached by fewer than two roots
                if (std::find(roots.begin(), roots.end(), static_cast<int>(b)) != roots.end()) continue;
                const Block& bl = base_blocks_[b];
                bool epilogue = bl.term.k == Term::Return && bl.stmts.size() <= 24;
                for (const Stmt& s : bl.stmts) epilogue = epilogue && (s.k == Stmt::Ins || s.k == Stmt::Charge);
                if (epilogue) continue;
                bool join = false;
                for (int pr : preds[b]) join = join || rs[static_cast<std::size_t>(pr)] != rs[b];
                if (!join) continue;
                roots.push_back(static_cast<int>(b));
                root_pc.push_back(bl.pc);
                R.push_back(reach_from(base_blocks_, static_cast<int>(b)));
            }
        }
        const std::size_t nr = roots.size();
        for (std::size_t i = 1; i < nr; ++i)
            shared_names_[root_pc[i]] = i < n_entry_roots ? name + fmt("_at_%08x_body", root_pc[i]) + sfx : name + fmt("_common_%08x", root_pc[i]) + sfx;
        std::vector<std::vector<std::size_t>> cut(nr);      // the roots (entries, joins) root i flows into and that never flow back
        std::vector<std::vector<std::size_t>> callers(nr);  // root j: the roots that call its shared body
        for (std::size_t i = 0; i < nr; ++i)
            for (std::size_t j = 1; j < nr; ++j)
                if (j != i && R[i][static_cast<std::size_t>(roots[j])] && !R[j][static_cast<std::size_t>(roots[i])]) {
                    cut[i].push_back(j);
                    callers[j].push_back(i);
                }
        const auto root_desc = [&](std::size_t i) {
            return i == 0 ? std::string("the start") : i < n_entry_roots ? fmt("entry 0x%X", root_pc[i]) : fmt("the common body at 0x%X", root_pc[i]);
        };
        std::string fwd, text;
        for (std::size_t i = 0; i < nr; ++i) {
            std::vector<std::pair<int, std::uint32_t>> ext;
            for (std::size_t j : cut[i]) ext.emplace_back(roots[j], root_pc[j]);
            const bool shared = !callers[i].empty();
            if (i >= n_entry_roots && !shared) continue;  // a join nobody calls after the cuts: copied where it is reached
            Root r;
            if (!emit_root(roots[i], ext, /*check=*/!shared, r)) return false;
            if (i >= n_entry_roots) {
                const std::string bn = shared_names_[root_pc[i]];
                std::string from;
                for (std::size_t c : callers[i]) from += (from.empty() ? "" : ", ") + root_desc(c);
                fwd += "static void " + bn + "(EEContext& ctx);  // the body " + from + " share (a join of their paths)\n";
                text += fmt("\n// 0x%08X: the body %s share: their paths join here (no check point of its own: the entry points do it)", root_pc[i],
                            from.c_str());
                text += r.frame + "\n";
                text += definition(bn, true, r);
                continue;
            }
            if (i == 0) {
                text += fmt("// 0x%08X %s -- %u bytes", f.start, f.name.c_str(), f.size);
                if (a_.chunks.size() > 1) text += fmt(", %zu chunks", a_.chunks.size());
                text += r.frame + "; mid-body entries:";
                for (std::size_t j = 1; j < nr; ++j) text += fmt(" 0x%X", root_pc[j]);
                text += "\n";
                text += banner;
                text += "// The function's start. The entry points below (callers jump or call into the body) run their own entry check\n"
                        "// point and then the body from their address, as the recompiled entry form does (one check, a switch to the\n"
                        "// entry label); a region two entry points reach is one shared body, called where the flow enters it.\n";
                text += definition(name + sfx, false, r);
                continue;
            }
            const std::string ename = name + fmt("_at_%08x", root_pc[i]);
            HandgenFunction::Entry en;
            en.pc = root_pc[i];
            en.name = ename;  // the case name; the game:: function is en.name + body_suffix
            en.symbol = at_symbol(f, root_pc[i]);
            if (opt_.shim) {
                en.shim = "void p3fes::recomp_gen::" + en.symbol + opt_.shim_suffix + "(p3fes::EEContext& ctx) { p3fes::game::" + ename + sfx + "(ctx); }\n";
            }
            out_.entries.push_back(en);
            if (shared) {
                const std::string bn = shared_names_[root_pc[i]];
                std::string from;
                for (std::size_t c : callers[i]) from += (from.empty() ? "" : ", ") + root_desc(c);
                fwd += "static void " + bn + "(EEContext& ctx);  // the body shared by " + from + " and entry " + fmt("0x%X", root_pc[i]) + "\n";
                text += fmt("\n// Entry 0x%X of %s (a caller's jal or jump into the body): its own entry check point, then the shared body.\n",
                            root_pc[i], f.name.c_str());
                text += "void " + ename + sfx + "(EEContext& ctx) {\n    using namespace hg;\n    check_events(ctx);  // entry check point\n    " + bn +
                        "(ctx);\n}\n";
                text += fmt("\n// 0x%08X: the body shared by %s and entry 0x%X (no check point of its own: the entry points do it)",
                            root_pc[i], from.c_str(), root_pc[i]);
                text += r.frame + "\n";
                text += definition(bn, true, r);
            } else {
                text += fmt("\n// Entry 0x%X of %s (a caller's jal or jump into the body)", root_pc[i], f.name.c_str()) + r.frame + "\n";
                text += definition(ename + sfx, false, r);
            }
        }
        o += fwd;
        if (!fwd.empty()) o += "\n";
        o += text;
        if (opt_.shim) {
            out_.shim = "void p3fes::recomp_gen::" + out_.symbol + opt_.shim_suffix + "(p3fes::EEContext& ctx) { p3fes::game::" + name + sfx +
                        "(ctx); }\n";
        }
        out_.decl = fmt("void %s%s(EEContext& ctx);  // 0x%X (register ABI: arguments in $a0.., the result in $v0)\n", name.c_str(), sfx.c_str(),
                        f.start);
        for (const HandgenFunction::Entry& en : out_.entries)
            out_.decl += fmt("void %s%s(EEContext& ctx);  // 0x%X: mid-body entry of %s\n", en.name.c_str(), sfx.c_str(), en.pc, f.name.c_str());
        for (const auto& [sym, decl] : callees_) out_.callees.push_back(decl);
        return true;
    }

private:
    struct Ctx {
        int loop = -1;       // the innermost loop being emitted (level checks)
        int H = -1, F = -1;  // `continue` / `break` targets of the enclosing C++ loop
        bool can_break = false;
        int stop = -1;       // the merge the current branch body falls out to
        bool in_switch = false;
        bool* sw_broke = nullptr;  // set when a `break;` leaves the switch from inside a case (the merge is reached)
        std::vector<int> outer;  // merges of enclosing constructs: reached from inside, they are jumped to, never placed
        int sw_merge = -1;
    };

    const FunctionAnalysis& a_;
    const ElfImage* elf_;
    const SymbolTable* syms_;
    const HandgenOptions& opt_;
    HandgenFunction& out_;
    std::vector<Block> base_blocks_;  // the function's blocks (Builder)
    std::vector<Block> blocks_;       // the root being written: base_blocks_ with the other entries' regions stubbed
    Graph g_;
    std::vector<char> emitted_;
    std::vector<char> dupable_;  // small return blocks (an epilogue) written out again at each arrival: early returns
    bool enter_pending_ = false;
    std::uint32_t used_gpr_ = 0, used_fpr_ = 0, used_vf_ = 0;
    bool used_jt_ = false, used_cc_ = false;
    std::map<std::string, std::string> callees_;
    std::set<int> targets_;
    // constant tracking for the comments (per block)
    bool known_[32] = {};
    std::uint64_t kval_[32] = {};


    // ---- one root (the function start or a mid-body entry): its region as structured text ----
    struct Root {
        std::string text;   // the printed body
        std::string decls;  // the register views it uses
        std::string frame;  // frame_summary()
    };

    // Blocks reachable from `root` over the block graph (the successors Graph::build sees).
    static std::vector<char> reach_from(const std::vector<Block>& bl, int root) {
        std::vector<char> r(bl.size(), 0);
        std::vector<int> st{root};
        r[static_cast<std::size_t>(root)] = 1;
        auto push = [&](const Target& x) {
            if (x.k == Target::Block && x.block >= 0 && !r[static_cast<std::size_t>(x.block)]) {
                r[static_cast<std::size_t>(x.block)] = 1;
                st.push_back(x.block);
            }
        };
        while (!st.empty()) {
            const Term& t = bl[static_cast<std::size_t>(st.back())].term;
            st.pop_back();
            push(t.e.t);
            if (t.k == Term::Cond && t.fall >= 0 && !r[static_cast<std::size_t>(t.fall)]) {
                r[static_cast<std::size_t>(t.fall)] = 1;
                st.push_back(t.fall);
            }
            for (const auto& c : t.cases) push(c.second.t);
        }
        return r;
    }

    std::map<std::uint32_t, std::string> shared_names_;  // the shared bodies by their address (run() fills it)
    std::string shared_body_name(std::uint32_t pc) const {
        const auto it = shared_names_.find(pc);
        return it != shared_names_.end() ? it->second : sanitize(a_.fn->name) + fmt("_at_%08x_body", pc) + opt_.body_suffix;
    }

    // Write the region of `root`. `ext`: {block, entry pc} of the entries whose regions belong to another function
    // (every edge into such a block is redirected to a stub that calls the entry's shared body and returns). `check`:
    // the region starts with the entry check point (false for a shared body: the entry points do it).
    bool emit_root(int root, const std::vector<std::pair<int, std::uint32_t>>& ext, bool check, Root& r) {
        blocks_ = base_blocks_;
        for (const auto& [blk, pc] : ext) {
            Block s;
            s.term.k = Term::Shared;
            s.term.e.t.k = Target::Shared;
            s.term.e.t.addr = pc;
            blocks_.push_back(s);
            const int sid = static_cast<int>(blocks_.size()) - 1;
            for (Block& b : blocks_) {
                Term& t = b.term;
                const auto redirect = [&](Target& x) {
                    if (x.k == Target::Block && x.block == blk) x.block = sid;
                };
                redirect(t.e.t);
                if (t.k == Term::Cond && t.fall == blk) t.fall = sid;
                for (auto& c : t.cases) redirect(c.second.t);
            }
        }
        g_ = Graph();
        g_.build(blocks_, root);
        emitted_.assign(blocks_.size(), 0);
        // An epilogue reached from several places is written where each path arrives (the same statements in the same
        // order on every path: faithful), instead of one copy and gotos to it.
        dupable_.assign(blocks_.size(), 0);
        for (int i = 0; i < g_.n; ++i) {
            const Block& bl = blocks_[static_cast<std::size_t>(i)];
            if (!g_.reach[static_cast<std::size_t>(i)] || i == g_.entry || bl.term.k != Term::Return || g_.pred[static_cast<std::size_t>(i)].size() < 2) continue;
            bool simple = bl.stmts.size() <= 24;
            for (const Stmt& s : bl.stmts) simple = simple && (s.k == Stmt::Ins || s.k == Stmt::Charge);
            dupable_[static_cast<std::size_t>(i)] = simple;
        }
        for (int i = 0; i < g_.n; ++i)
            if (g_.reach[static_cast<std::size_t>(i)] && blocks_[static_cast<std::size_t>(i)].term.k != Term::Shared) ++out_.stats.blocks;
        used_gpr_ = used_fpr_ = used_vf_ = 0;
        used_jt_ = used_cc_ = false;
        targets_.clear();

        Seq body;
        const int e = g_.entry;
        if (!check) {
            enter_pending_ = false;
        } else if (g_.header_loop[static_cast<std::size_t>(e)] >= 0) {
            body.push_back(line("check_events(ctx);", "entry check point (the first block heads a loop)"));
            enter_pending_ = false;
        } else if (blocks_[static_cast<std::size_t>(e)].stmts.empty() || blocks_[static_cast<std::size_t>(e)].stmts.front().k != Stmt::Charge) {
            body.push_back(line("check_events(ctx);", "entry check point"));
            enter_pending_ = false;
        } else {
            enter_pending_ = true;
        }
        Ctx top;
        emit_seq(body, e, top, false);
        // Blocks only gotos reach (shared tails, irreducible flow) follow the main sequence, each under its label.
        for (int bi = 0; bi < g_.n; ++bi) {
            int best = -1;
            for (int k = 0; k < g_.n; ++k)
                if (g_.reach[static_cast<std::size_t>(k)] && !emitted_[static_cast<std::size_t>(k)] &&
                    !(blocks_[static_cast<std::size_t>(k)].term.k == Term::Shared && blocks_[static_cast<std::size_t>(k)].stmts.empty()) &&
                    (best < 0 || blocks_[static_cast<std::size_t>(k)].pc < blocks_[static_cast<std::size_t>(best)].pc))
                    best = k;
            if (best < 0) break;
            Ctx c;
            c.loop = g_.loop_of[static_cast<std::size_t>(best)];
            emit_seq(body, best, c, true);
        }
        // Trailing `return;` of the function.
        if (!body.empty() && body.back().k == Node::Line && body.back().text == "return;" && body.back().target < 0) body.pop_back();

        collect_targets(body);
        print_seq(r.text, body, 1);
        r.decls = declarations();
        r.frame = frame_summary();
        return true;
    }

    bool fail(const std::string& why) {
        out_.error = why;
        return false;
    }

    // ---- registers ----
    std::string gpr(unsigned r) {  // a proxy (statement operand)
        used_gpr_ |= bit(r);
        return kGpr[r];
    }
    std::string val(unsigned r) {  // a value (expression operand): $zero reads as 0
        if (r == 0) return "0";
        return gpr(r);
    }
    std::string fpr(unsigned r) {
        used_fpr_ |= bit(r);
        return fmt("f%u", r);
    }
    std::string vf(unsigned r) {
        used_vf_ |= bit(r);
        return fmt("vf%u", r);
    }
    std::string off(unsigned base, std::int32_t imm) { return (base == 29 || base == 30) ? shex(imm) : fmt("%d", imm); }
    static std::string imm_value(std::int32_t imm, bool hexa) {
        if (imm < 0) return hexa ? "si(" + shex(imm) + ")" : fmt("si(%d)", imm);
        return hexa ? shex(imm) : fmt("%d", imm);
    }

    std::string declarations() {
        std::string d;
        auto list = [&](const char* type, std::uint32_t mask, auto name, unsigned from) {
            std::string l;
            for (unsigned r = from; r < 32; ++r) {
                if (!(mask & bit(r))) continue;
                if (!l.empty()) l += ", ";
                l += name(r) + "{ctx, " + std::to_string(r) + "}";
            }
            if (!l.empty()) d += std::string("    ") + type + " " + l + ";\n";
        };
        list("Gpr", used_gpr_, [](unsigned r) { return std::string(kGpr[r]); }, 0);
        list("Fpr", used_fpr_, [](unsigned r) { return fmt("f%u", r); }, 0);
        list("Vf", used_vf_, [](unsigned r) { return fmt("vf%u", r); }, 0);
        if (used_jt_) d += "    u32 jt = 0;    // a jump target read before its delay slot\n";
        if (used_cc_) d += "    bool cc = false;  // a branch condition read before its delay slot\n";
        return d;
    }

    // ---- readability comments ----
    std::string describe_addr(std::uint32_t va) const {
        if (syms_) {
            if (const SymbolTable::Sym* s = syms_->describe(va)) {
                if (s->addr == va) return s->name;
                return fmt("%s+0x%X", s->name.c_str(), va - s->addr);
            }
        }
        return fmt("0x%X", va);
    }
    std::string string_at(std::uint32_t va) const {
        if (!elf_) return {};
        std::string s;
        for (std::uint32_t i = 0; i < 96; ++i) {
            const std::uint8_t* p = elf_->bytes_at(va + i, 1);
            if (!p) return {};
            const unsigned char c = *p;
            if (c == 0) break;
            if (c == '\n') s += "\\n";
            else if (c == '\t') s += "\\t";
            else if (c == '"' || c == '\\') { s += '\\'; s += static_cast<char>(c); }
            else if (c >= 0x20 && c < 0x7F) s += static_cast<char>(c);
            else return {};
            if (i == 95) return {};
        }
        if (s.size() < 2) return {};
        return "\"" + s + "\"";
    }
    std::string describe_ptr(std::uint32_t va) const {
        if (va < 0x100000u || va >= 0x2000000u) return {};
        if (syms_) {
            if (const SymbolTable::Sym* s = syms_->describe(va)) {
                if (s->kind == 'F') return "&" + s->name;
            }
        }
        const std::string str = string_at(va);
        if (!str.empty()) return str;
        return "&" + describe_addr(va);
    }
    void reset_known() {
        std::fill(std::begin(known_), std::end(known_), false);
        known_[0] = true;
        kval_[0] = 0;
        known_[28] = true;
        kval_[28] = static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(opt_.gp)));
    }
    void forget_caller_saved() {
        for (unsigned r = 1; r < 32; ++r)
            if (!(r >= 16 && r <= 23) && r != 28 && r != 29 && r != 30) known_[r] = false;
    }
    // Comment for a memory access / address computation, and the constant-tracking update.
    std::string track(const Insn& in) {
        using enum Op;
        std::string c;
        const RW r = rw_of(in);
        auto set = [&](unsigned d, std::uint64_t v) {
            if (d == 0) return;
            known_[d] = true;
            kval_[d] = v;
        };
        bool handled = false;
        switch (in.op) {
        case Lui: set(in.rt, ee_lui(in.uimm())); handled = true; break;
        case Addiu: case Addi: case Daddiu:
            if (known_[in.rs] && in.rs != 29 && in.rs != 30) {
                const std::uint64_t v = in.op == Daddiu ? kval_[in.rs] + static_cast<std::uint64_t>(static_cast<std::int64_t>(in.imm))
                                                        : sx32(static_cast<std::uint32_t>(kval_[in.rs]) + static_cast<std::uint32_t>(in.imm));
                set(in.rt, v);
                if (in.rs != 0) c = describe_ptr(static_cast<std::uint32_t>(v));
                handled = true;
            }
            break;
        case Ori:
            if (known_[in.rs]) {
                const std::uint64_t v = kval_[in.rs] | in.uimm();
                set(in.rt, v);
                if (in.rs != 0) c = describe_ptr(static_cast<std::uint32_t>(v));
                handled = true;
            }
            break;
        case Daddu: case Or: case Addu:
            if (in.rt == 0 && known_[in.rs]) {
                set(in.rd, in.op == Addu ? sx32(static_cast<std::uint32_t>(kval_[in.rs])) : kval_[in.rs]);
                handled = true;
            } else if (in.rs == 0 && known_[in.rt]) {
                set(in.rd, in.op == Addu ? sx32(static_cast<std::uint32_t>(kval_[in.rt])) : kval_[in.rt]);
                handled = true;
            }
            break;
        case Lb: case Lbu: case Lh: case Lhu: case Lw: case Lwu: case Ld: case Lq: case Lwl: case Lwr: case Ldl: case Ldr:
        case Sb: case Sh: case Sw: case Swl: case Swr: case Sd: case Sdl: case Sdr: case Sq:
        case Lwc1: case Swc1: case Lqc2: case Sqc2:
            if (known_[in.rs] && in.rs != 29 && in.rs != 30)
                c = describe_addr(static_cast<std::uint32_t>(kval_[in.rs]) + static_cast<std::uint32_t>(in.imm));
            break;
        default:
            break;
        }
        if (!handled)
            for (unsigned d = 1; d < 32; ++d)
                if (r.gw & bit(d)) known_[d] = false;
        return c;
    }
    static std::uint64_t sx32(std::uint32_t v) { return static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(v))); }
    static std::uint64_t ee_lui(std::uint32_t u) { return sx32((u & 0xFFFFu) << 16); }

    // ---- instructions ----
    // The statement for one non-control-flow instruction ("" for a nop or a dropped $zero write).
    std::string insn_text(const Insn& in, std::string& comment) {
        using enum Op;
        comment = track(in);
        if (in.word == 0) return {};
        const unsigned rd = in.rd, rs = in.rs, rt = in.rt;
        auto assign = [&](unsigned d, const std::string& e) { return gpr(d) + " = " + e + ";"; };
        auto mnem = [&] {
            char m[48];
            variant_mnemonic(in, m, sizeof m);
            return std::string(m);
        };
        const bool sp_imm = rs == 29 || rt == 29 || rs == 30 || rt == 30;
        switch (in.op) {
        case Add: case Addu:
            if (rd == 0) return {};
            if (rs == 0 && rt == 0) return assign(rd, "0");
            return assign(rd, "addu(" + val(rs) + ", " + val(rt) + ")");
        case Sub: case Subu:
            if (rd == 0) return {};
            return assign(rd, "subu(" + val(rs) + ", " + val(rt) + ")");
        case And:
            if (rd == 0) return {};
            if (rs == 0 || rt == 0) return assign(rd, "0");
            return assign(rd, val(rs) + " & " + val(rt));
        case Or: case Xor: case Daddu:
            if (rd == 0) return {};
            if (rs == 0 && rt == 0) return assign(rd, "0");
            if ((rt == 0 && rs == rd) || (rs == 0 && rt == rd)) {
                comment = mnem() + " " + kGpr[rd] + ": a 64-bit move to itself (no effect)";
                return {};
            }
            if (rt == 0) return assign(rd, val(rs));
            if (rs == 0) return assign(rd, val(rt));
            return assign(rd, val(rs) + (in.op == Or ? " | " : in.op == Xor ? " ^ " : " + ") + val(rt));
        case Dsubu:
            if (rd == 0) return {};
            if (rt == 0 && rs == rd) {
                comment = mnem() + " " + kGpr[rd] + ": a 64-bit move to itself (no effect)";
                return {};
            }
            if (rt == 0) return assign(rd, val(rs));
            return assign(rd, val(rs) + " - " + val(rt));
        case Nor: if (rd == 0) return {}; return assign(rd, "nor(" + val(rs) + ", " + val(rt) + ")");
        case Slt: if (rd == 0) return {}; return assign(rd, "slt(" + val(rs) + ", " + val(rt) + ")");
        case Sltu: if (rd == 0) return {}; return assign(rd, "sltu(" + val(rs) + ", " + val(rt) + ")");
        case Movn:
            if (rd == 0 || rt == 0) return {};  // never moves
            return "if (" + val(rt) + " != 0) " + assign(rd, val(rs)) ;
        case Movz:
            if (rd == 0) return {};
            if (rt == 0) return assign(rd, val(rs));
            return "if (" + val(rt) + " == 0) " + assign(rd, val(rs));
        case Paddh: case Paddub: case Padduw: case Paddw: case Pand: case Pcgth: case Pcpyld: case Pcpyud:
        case Pextlb: case Pextlh: case Pextlw: case Pextub: case Pextuw: case Pmaxh: case Pminh:
        case Pnor: case Por: case Ppacb: case Ppach: case Ppacw: case Psubb: case Psubw: case Pxor: case Qfsrv:
            if (rd == 0) return {};
            return rt_name(in) + "(" + gpr(rd) + ", " + gpr(rs) + ", " + gpr(rt) + ");";
        case Mult: case Multu: case Madd: case Maddu: case Mult1: case Multu1: case Maddu1: case Phmadh:
            return rt_name(in) + "(" + gpr(rd) + ", " + gpr(rs) + ", " + gpr(rt) + ");";
        case Sllv: case Srlv: case Srav: case Dsllv: case Dsrlv:
            if (rd == 0) return {};
            return assign(rd, rt_name(in) + "(" + val(rt) + ", " + val(rs) + ")");
        case Div: case Divu: case Div1:
            return rt_name(in) + "(" + gpr(rs) + ", " + gpr(rt) + ");";
        case Addi: case Addiu: case Daddiu:
            if (rt == 0) return {};
            if (rs == 0) return assign(rt, imm_value(in.imm, sp_imm));
            return assign(rt, std::string(in.op == Daddiu ? "daddiu(" : "addiu(") + val(rs) + ", " + (sp_imm ? shex(in.imm) : fmt("%d", in.imm)) + ")");
        case Slti: case Sltiu:
            if (rt == 0) return {};
            return assign(rt, rt_name(in) + "(" + val(rs) + ", " + fmt("%d", in.imm) + ")");
        case Andi:
            if (rt == 0) return {};
            if (rs == 0) return assign(rt, "0");
            return assign(rt, val(rs) + " & " + hex(in.uimm()));
        case Ori: case Xori:
            if (rt == 0) return {};
            if (rs == 0) return assign(rt, hex(in.uimm()));
            return assign(rt, val(rs) + (in.op == Ori ? " | " : " ^ ") + hex(in.uimm()));
        case Lui:
            if (rt == 0) return {};
            if (in.uimm() < 0x8000u) return assign(rt, hex(in.uimm() << 16));
            return assign(rt, "lui(" + hex(in.uimm()) + ")");
        case Sll: case Srl: case Sra: case Dsll: case Dsrl: case Dsra: case Dsll32: case Dsrl32: case Dsra32:
            if (rd == 0) return {};
            return assign(rd, rt_name(in) + "(" + val(rt) + ", " + std::to_string(in.sa) + ")");
        case Psllh: case Psrlh: case Psrah: case Psraw:
            if (rd == 0) return {};
            return rt_name(in) + "(" + gpr(rd) + ", " + gpr(rt) + ", " + std::to_string(in.sa) + ");";
        case Mfhi: case Mflo: case Mfhi1: case Mflo1: case Mfsa:
            if (rd == 0) return {};
            return rt_name(in) + "(" + gpr(rd) + ");";
        case Mthi: case Mtlo: case Mthi1: case Mtlo1: case Mtsa:
            return rt_name(in) + "(" + gpr(rs) + ");";
        case Mtsab: case Mtsah:
            return rt_name(in) + "(" + gpr(rs) + ", " + fmt("%d", in.imm) + ");";
        case Lb: case Lbu: case Lh: case Lhu: case Lw: case Lwu: case Lwl: case Lwr: case Ld: case Ldl: case Ldr:
        case Sb: case Sh: case Sw: case Swl: case Swr: case Sd: case Sdl: case Sdr: case Lq: case Sq:
            return rt_name(in) + "(" + gpr(rt) + ", " + gpr(rs) + ", " + off(rs, in.imm) + ");";
        case Lwc1: case Swc1:
            return rt_name(in) + "(" + fpr(in.ft) + ", " + gpr(rs) + ", " + off(rs, in.imm) + ");";
        case Lqc2: case Sqc2:
            return rt_name(in) + "(" + vf(in.ft) + ", " + gpr(rs) + ", " + off(rs, in.imm) + ");";
        case AddS: case SubS: case MulS: case DivS: case MaddS: case MsubS:
            return rt_name(in) + "(" + fpr(in.fd) + ", " + fpr(in.fs) + ", " + fpr(in.ft) + ");";
        case AddaS: case SubaS: case MulaS: case MaddaS: case MsubaS: case CEqS: case CLeS: case CLtS:
            return rt_name(in) + "(" + fpr(in.fs) + ", " + fpr(in.ft) + ");";
        case AbsS: case MovS: case NegS: case CvtSW: case CvtWS:
            return rt_name(in) + "(" + fpr(in.fd) + ", " + fpr(in.fs) + ");";
        case SqrtS:
            return "sqrt_s(" + fpr(in.fd) + ", " + fpr(in.ft) + ");";
        case Mfc1:
            if (rt == 0) return {};
            return "mfc1(" + gpr(rt) + ", " + fpr(in.fs) + ");";
        case Mtc1:
            return "mtc1(" + gpr(rt) + ", " + fpr(in.fs) + ");";
        case Ctc1:
            return "ctc1(" + gpr(rt) + ", " + std::to_string(in.fs) + ");";
        case Mfc0:
            if (rt == 0) return {};
            return "mfc0(" + gpr(rt) + ", " + std::to_string(rd) + ");";
        case Mtc0:
            return "mtc0(" + gpr(rt) + ", " + std::to_string(rd) + ");";
        case Sync: return "sync(ctx, " + std::to_string(in.fmt) + ");";
        case Ei: return "ei(ctx);";
        case Di: return "di(ctx);";
        case Vnop: return "vnop(ctx);";
        case Vwaitq: return "vwaitq(ctx);";
        case Cache: return "cache(ctx, " + std::to_string(rt) + ", " + gpr(rs) + ", " + fmt("%d", in.imm) + ");";
        case Pmfhl:
            if (rd == 0) return {};
            return "pmfhl(" + gpr(rd) + ", " + std::to_string(in.fmt) + ");";
        case Pcpyh: case Pexew: case Prot3w:
            if (rd == 0) return {};
            return rt_name(in) + "(" + gpr(rd) + ", " + gpr(rt) + ");";
        case Qmfc2: case Cfc2:
            if (rt == 0) return {};
            comment = mnem();
            return rt_name(in) + "(" + gpr(rt) + ", " + (in.op == Qmfc2 ? vf(in.fs) : std::to_string(in.fs)) + (in.interlock ? ", true);" : ", false);");
        case Qmtc2: case Ctc2:
            comment = mnem();
            return rt_name(in) + "(" + gpr(rt) + ", " + (in.op == Qmtc2 ? vf(in.fs) : std::to_string(in.fs)) + (in.interlock ? ", true);" : ", false);");
        case Vadd: case Vsub: case Vmul: case Vmadd: case Vmsub: case Vmax: case Vmini: case Vopmsub: {
            comment = mnem();
            std::string s = rt_name(in) + "(" + hex(in.dest) + ", " + vf(in.fd) + ", " + vf(in.fs) + ", " + vf(in.ft);
            if (in.vu_bc) s += ", " + std::to_string(in.bc);
            return s + ");";
        }
        case Vadda: case Vmadda: case Vmsuba: case Vmula: case Vopmula: {
            comment = mnem();
            std::string s = rt_name(in) + "(" + hex(in.dest) + ", " + vf(in.fs) + ", " + vf(in.ft);
            if (in.vu_bc) s += ", " + std::to_string(in.bc);
            return s + ");";
        }
        case Vaddi: case Vmuli: case Vmulq:
            comment = mnem();
            return rt_name(in) + "(" + hex(in.dest) + ", " + vf(in.fd) + ", " + vf(in.fs) + ");";
        case Vabs: case Vmove: case Vftoi0: case Vitof0:
            comment = mnem();
            return rt_name(in) + "(" + hex(in.dest) + ", " + vf(in.ft) + ", " + vf(in.fs) + ");";
        case Vsqrt:
            comment = mnem();
            return "vsqrt(" + vf(in.ft) + ", " + std::to_string(in.vftf()) + ");";
        case Vrsqrt:
            comment = mnem();
            return "vrsqrt(" + vf(in.fs) + ", " + std::to_string(in.vfsf()) + ", " + vf(in.ft) + ", " + std::to_string(in.vftf()) + ");";
        case Syscall: return "syscall(ctx, " + hexu(in.pc) + ");";
        case Break: return "brk(ctx, " + hexu(in.pc) + ", " + hexu(in.code()) + ");";
        default:
            return "rt::trap(ctx, " + hexu(in.pc) + ", rt::Trap::Unsupported, " + hexu(in.word) + ");";
        }
    }

    void push_insn(Seq& out, const Insn& in) {
        std::string c;
        std::string t = insn_text(in, c);
        if (t.empty()) {
            if (c.find("(no effect)") != std::string::npos) out.push_back(line("", c));  // a no-op worth naming
            return;
        }
        ++out_.stats.statements;
        out.push_back(line(std::move(t), std::move(c)));
    }

    std::string cond_text(const Cond& c) {
        auto cmp = [&](const char* op) {
            if (c.rt == 0) return val(c.rs) + op + "0";
            if (c.rs == 0) return val(c.rt) + op + "0";
            return val(c.rs) + op + val(c.rt);
        };
        switch (c.k) {
        case Cond::Eq: return cmp(" == ");
        case Cond::Ne: return cmp(" != ");
        case Cond::Lez: return "i64(" + val(c.rs) + ") <= 0";
        case Cond::Gtz: return "i64(" + val(c.rs) + ") > 0";
        case Cond::Ltz: return "i64(" + val(c.rs) + ") < 0";
        case Cond::Gez: return "i64(" + val(c.rs) + ") >= 0";
        case Cond::C1T: return "cond(ctx)";
        case Cond::C1F: return "!cond(ctx)";
        case Cond::C0T: return "cop0_cond(ctx)";
        case Cond::C0F: return "!cop0_cond(ctx)";
        case Cond::Saved: used_cc_ = true; return "cc";
        case Cond::NotSaved: used_cc_ = true; return "!cc";
        }
        return "false";
    }

    // A callee's recomp_gen entry point; a mid-body entry through its fn_<name>_<addr8>_at_<pc8> wrapper (generated
    // when the callee stays recompiled, a forwarder to game::<name>_at_<pc8> once it is replaced).
    std::string callee(const Function* fn, std::uint32_t at = 0) {
        const std::string sym = at ? at_symbol(*fn, at) : function_symbol(*fn);
        callees_[sym] = "void " + sym + "(p3fes::EEContext&);";
        return "gen::" + sym;
    }

    void push_stmt(Seq& out, const Stmt& s, bool& first_charge) {
        switch (s.k) {
        case Stmt::Ins: push_insn(out, s.insn); break;
        case Stmt::Charge:
            ++out_.stats.charges;
            if (first_charge) {
                out.push_back(line(fmt("enter(ctx, %zu);", s.n), "entry check point + this block's cycles"));
                first_charge = false;
            } else {
                out.push_back(line(fmt("charge(ctx, %zu);", s.n)));
            }
            break;
        case Stmt::Check:
            ++out_.stats.backedges;
            out.push_back(line("backedge(ctx);"));
            break;
        case Stmt::SaveCond:
            out.push_back(line("cc = " + cond_text(s.cond) + ";", "the condition, before the delay slot changes it"));
            used_cc_ = true;
            break;
        case Stmt::SaveJt:
            used_jt_ = true;
            out.push_back(line("jt = " + gpr(s.reg) + ".u();", "the target, before the delay slot changes it"));
            break;
        case Stmt::TailNoRet: {
            const std::string f = callee(s.edge.fn, s.edge.kind == EdgeKind::TailEntry ? s.edge.target : 0);
            out.push_back(line(f + "(ctx);", "a tail call that does not return (the recompiled body falls through after it)"));
            break;
        }
        case Stmt::Eret:
            out.push_back(line("rt::eret(ctx, " + hexu(s.insn.pc) + ");"));
            break;
        case Stmt::Call: {
            ++out_.stats.calls;
            const Insn& in = s.insn;
            const std::string note = s.noreturn ? "does not return" : "";
            if (s.has_slot) (s.slot_first ? out_.stats.hoisted_slots : out_.stats.ordered_slots)++;
            if (s.has_slot && s.slot_first) push_insn(out, s.slot);
            forget_caller_saved();
            if (s.indirect) {
                const unsigned rd = in.rd;
                if (s.has_slot && !s.slot_first) {
                    used_jt_ = true;
                    out.push_back(line("jt = " + gpr(in.rs) + ".u();", "the target, read before the delay slot"));
                    if (rd == 31) out.push_back(line("link(ctx, " + hexu(in.pc) + ");", "$ra = the return address"));
                    else if (rd != 0) out.push_back(line(fmt("rt::jalr(ctx, %u, ", rd) + hexu(in.pc) + ");"));
                    push_insn(out, s.slot);
                    out.push_back(line("call_ptr(ctx, jt);", note));
                } else if (rd == 31) {
                    out.push_back(line("jalr(ctx, " + hexu(in.pc) + ", " + gpr(in.rs) + ".u());", note));
                } else {
                    out.push_back(line(fmt("jalr_rd(ctx, %u, ", rd) + hexu(in.pc) + ", " + gpr(in.rs) + ".u());", note));
                }
                known_[31] = false;
                return;
            }
            const std::string f = callee(s.edge.fn, s.edge.kind == EdgeKind::CallEntry ? s.edge.target : 0);
            if (s.has_slot && !s.slot_first) {
                out.push_back(line("link(ctx, " + hexu(in.pc) + ");", "$ra first: the delay slot below depends on it"));
                push_insn(out, s.slot);
                out.push_back(line("call(ctx, " + f + ");", note));
            } else {
                out.push_back(line("jal(ctx, " + hexu(in.pc) + ", " + f + ");", note));
            }
            known_[31] = false;
            return;
        }
        }
    }

    // ---- structure ----
    bool level_ok(int t, const Ctx& c) const {
        const int L = g_.loop_of[t];
        if (L == c.loop) return true;
        const int hl = g_.header_loop[t];
        return hl >= 0 && g_.loops[hl].parent == c.loop;
    }

    Node goto_line(int t) {
        Node n = line("goto " + label_name(t) + ";", {}, true);
        n.target = t;
        return n;
    }

    std::string label_name(int b) const {
        // label blocks by their address; synthetic blocks (the code after a call whose slot is a target) get a suffix
        const Block& bl = blocks_[b];
        if (bl.label) return fmt("L_%08x", bl.pc);
        return fmt("L_%08x_%d", bl.pc, b);
    }

    int merge_of(int n, const Ctx& c) const {
        const int p = g_.ipdom[n];
        if (p < 0) return -1;
        if (p == c.stop || p == c.H || p == c.F || (c.in_switch && p == c.sw_merge)) return p;
        if (!level_ok(p, c)) return -1;
        return p;
    }

    static bool is_outer(int n, const Ctx& c) { return std::find(c.outer.begin(), c.outer.end(), n) != c.outer.end(); }
    static void push_outer(Ctx& c, int n) {
        if (n >= 0) c.outer.push_back(n);
    }

    // Can `to` be reached from `from` without passing `avoid`?
    bool reaches(int from, int to, int avoid) const {
        if (from < 0 || to < 0) return false;
        std::vector<char> seen(static_cast<std::size_t>(g_.n), 0);
        std::vector<int> st{from};
        seen[from] = 1;
        while (!st.empty()) {
            const int b = st.back();
            st.pop_back();
            if (b == to) return true;
            for (int s : g_.succ[b])
                if (s != avoid && !seen[s]) {
                    seen[s] = 1;
                    st.push_back(s);
                }
        }
        return false;
    }

    static std::size_t weight(const Seq& s) {
        std::size_t n = 0;
        for (const Node& x : s) n += 1 + weight(x.a) + weight(x.b);
        return n;
    }

    // A copy of a small return block where a path arrives (dupable_).
    void emit_copy(Seq& out, int n) {
        emitted_[n] = 1;
        reset_known();
        out.push_back(line("", fmt("0x%08x (the shared epilogue, written out on this path)", blocks_[n].pc)));
        bool fc = false;
        for (const Stmt& s : blocks_[n].stmts) push_stmt(out, s, fc);
        out.push_back(line("return;", {}, true));
    }

    // Emit the edge's actions and its target. Returns true when control falls out to c.stop.
    bool transfer(Seq& out, const EdgeT& e, const Ctx& c) {
        bool fc = false;
        for (const Stmt& s : e.actions) push_stmt(out, s, fc);
        switch (e.t.k) {
        case Target::Block: return emit_seq(out, e.t.block, c, false);
        case Target::Return: out.push_back(line("return;", {}, true)); return false;
        case Target::Tail:
            out.push_back(line(callee(e.t.fn, false) + "(ctx);", "tail call"));
            out.push_back(line("return;", {}, true));
            return false;
        case Target::TailEntry:
            out.push_back(line(callee(e.t.fn, e.t.addr) + "(ctx);", "tail call (into the callee's body at " + hexu(e.t.addr) + ")"));
            out.push_back(line("return;", {}, true));
            return false;
        case Target::Unreachable:
            out.push_back(line("rt::unreachable(" + hexu(e.t.addr) + ");", {}, true));
            return false;
        case Target::Shared:
            out.push_back(line(shared_body_name(e.t.addr) + "(ctx);", fmt("into the shared body at 0x%X", e.t.addr)));
            out.push_back(line("return;", {}, true));
            return false;
        }
        return false;
    }

    // Arrive at block n (edge actions done). Returns true when control falls out to c.stop.
    bool emit_seq(Seq& out, int n, Ctx c, bool force) {
        for (;;) {
            if (!force) {
                if (n == c.stop) return true;
                if (c.in_switch && n == c.sw_merge) {
                    out.push_back(line("break;", {}, true));
                    if (c.sw_broke) *c.sw_broke = true;
                    return false;
                }
                if (n == c.H) {
                    out.push_back(line("continue;", {}, true));
                    return false;
                }
                if (n == c.F && c.can_break) {
                    out.push_back(line("break;", {}, true));
                    return false;
                }
                if (dupable_[n]) {
                    emit_copy(out, n);
                    return false;
                }
                if (blocks_[n].term.k == Term::Shared && blocks_[n].stmts.empty()) {  // a stub: written at each arrival
                    transfer(out, blocks_[n].term.e, c);
                    return false;
                }
                if (emitted_[n] || !level_ok(n, c) || is_outer(n, c)) {
                    out.push_back(goto_line(n));
                    return false;
                }
                const int hl = g_.header_loop[n];
                if (hl >= 0 && hl != c.loop) {
                    ++out_.stats.loops;
                    Node f;
                    f.k = Node::For;
                    Ctx lc;
                    lc.loop = hl;
                    lc.H = n;
                    lc.F = g_.loops[hl].follow;
                    lc.can_break = true;
                    emit_seq(f.a, n, lc, true);
                    if (!f.a.empty() && f.a.back().k == Node::Line && f.a.back().text == "continue;") f.a.pop_back();
                    out.push_back(std::move(f));
                    const int fol = g_.loops[hl].follow;
                    if (fol < 0) return false;
                    n = fol;
                    continue;
                }
            }
            force = false;
            emitted_[n] = 1;
            Node lab;
            lab.k = Node::Label;
            lab.target = n;
            out.push_back(lab);
            reset_known();
            const Block& b = blocks_[n];
            bool first_charge = enter_pending_ && n == g_.entry;
            if (n == g_.entry) enter_pending_ = false;
            for (const Stmt& s : b.stmts) push_stmt(out, s, first_charge);
            const Term& t = b.term;
            switch (t.k) {
            case Term::Open:
            case Term::Return:
                out.push_back(line("return;", {}, true));
                return false;
            case Term::Goto: {
                bool fc = false;
                for (const Stmt& s : t.e.actions) push_stmt(out, s, fc);
                n = t.e.t.block;
                continue;
            }
            case Term::Tail:
            case Term::TailEntry:
            case Term::Unreachable:
            case Term::Shared:
                return transfer(out, t.e, c);
            case Term::TailPtr:
                out.push_back(line("tail(ctx, " + (t.jt_saved ? std::string("jt") : gpr(t.jt_reg) + ".u()") + ");", "jr: the target's entry point"));
                if (t.jt_saved) used_jt_ = true;
                out.push_back(line("return;", {}, true));
                return false;
            case Term::Cond: {
                ++out_.stats.ifs;
                const int m = merge_of(n, c);
                const std::string ct = cond_text(t.cond);
                const std::string cn = cond_text(negate(t.cond));
                Node i;
                i.k = Node::If;
                // One branch's region flows into the other branch's block (which only this test reaches directly):
                // that block goes after the region, `if (...) { region } block...`, even when it is no merge point
                // (the region also leaves elsewhere: an early return, a jump to the outer merge).
                const int tb = t.e.t.k == Target::Block ? t.e.t.block : -1;
                auto placeable = [&](int x) {
                    return x >= 0 && x != m && x != c.stop && x != c.H && x != c.F && !(c.in_switch && x == c.sw_merge) &&
                           !emitted_[x] && !dupable_[x] && level_ok(x, c) && g_.idom[x] == n && !is_outer(x, c);
                };
                if (placeable(tb) && tb != t.fall && reaches(t.fall, tb, n) && !reaches(tb, t.fall, n)) {
                    Ctx fc = c;
                    push_outer(fc, c.stop);
                    push_outer(fc, m);
                    fc.stop = tb;
                    Seq A, F;
                    bool fcg = false;
                    for (const Stmt& s : t.e.actions) push_stmt(A, s, fcg);
                    emit_seq(F, t.fall, fc, false);
                    if (A.empty()) {
                        i.text = cn;
                        i.a = std::move(F);
                    } else {
                        i.text = ct;
                        i.a = std::move(A);
                        i.b = std::move(F);
                    }
                    out.push_back(std::move(i));
                    n = tb;
                    continue;
                }
                if (tb >= 0 && placeable(t.fall) && tb != t.fall && reaches(tb, t.fall, n) && !reaches(t.fall, tb, n)) {
                    Ctx tc = c;
                    push_outer(tc, c.stop);
                    push_outer(tc, m);
                    tc.stop = t.fall;
                    Seq T;
                    transfer(T, t.e, tc);
                    i.text = ct;
                    i.a = std::move(T);
                    out.push_back(std::move(i));
                    n = t.fall;
                    continue;
                }
                Ctx ic = c;
                ic.stop = m;
                if (c.stop >= 0 && c.stop != m) push_outer(ic, c.stop);  // m lies past the region's end: jump there
                Seq T, F;
                bool tf = transfer(T, t.e, ic);
                bool ff = emit_seq(F, t.fall, ic, false);
                // A branch that only reaches a loop's continue / break point while the other leaves: spell the jump
                // out, so the short one goes first (`if (...) break;` at the top of a test-first loop).
                const bool loop_merge = m >= 0 && m != c.stop && (m == c.H || (m == c.F && c.can_break));
                if (loop_merge && F.empty() && ff && !tf) {
                    F.push_back(line(m == c.H ? "continue;" : "break;", {}, true));
                    ff = false;
                } else if (loop_merge && T.empty() && tf && !ff) {
                    T.push_back(line(m == c.H ? "continue;" : "break;", {}, true));
                    tf = false;
                }
                if (T.empty()) {  // the taken edge goes straight to the merge
                    i.text = cn;
                    i.a = std::move(F);
                    out.push_back(std::move(i));
                } else if (F.empty()) {
                    i.text = ct;
                    i.a = std::move(T);
                    out.push_back(std::move(i));
                } else if (!tf && !ff && weight(F) < weight(T)) {  // both leave: the shorter one in the `if`
                    i.text = cn;
                    i.a = std::move(F);
                    out.push_back(std::move(i));
                    for (Node& x : T) out.push_back(std::move(x));
                } else if (!tf) {  // the taken path leaves: no else
                    i.text = ct;
                    i.a = std::move(T);
                    out.push_back(std::move(i));
                    for (Node& x : F) out.push_back(std::move(x));
                } else if (!ff) {  // the not-taken path leaves (an early return): it goes first
                    i.text = cn;
                    i.a = std::move(F);
                    out.push_back(std::move(i));
                    for (Node& x : T) out.push_back(std::move(x));
                } else {
                    i.text = ct;
                    i.a = std::move(T);
                    i.b = std::move(F);
                    out.push_back(std::move(i));
                }
                if (!tf && !ff) return false;
                if (m < 0) return false;  // (cannot fall: both bodies end)
                n = m;
                continue;
            }
            case Term::Switch: {
                ++out_.stats.switches;
                const int m = merge_of(n, c);
                Ctx sc = c;
                sc.stop = m;
                sc.in_switch = true;
                sc.sw_merge = m;
                sc.can_break = false;
                bool broke = false;
                sc.sw_broke = &broke;
                Node s;
                s.k = Node::Switch;
                if (t.jt_saved) used_jt_ = true;
                s.text = t.jt_saved ? std::string("jt") : gpr(t.jt_reg) + ".u()";
                std::map<std::uint32_t, std::vector<unsigned>> idx = table_indices(t);
                bool any = false;
                for (const auto& [target, e] : t.cases) {
                    Node::Case k;
                    k.head = "case " + hexu(target) + ":";
                    auto it = idx.find(target);
                    if (it != idx.end()) {
                        std::string l;
                        for (unsigned v : it->second) l += (l.empty() ? "" : ", ") + std::to_string(v);
                        k.head += "  // table[" + l + "]";
                    }
                    const bool falls = transfer(k.body, e, sc);
                    if (falls) {
                        k.body.push_back(line("break;", {}, true));
                        any = true;
                    }
                    s.cases.push_back(std::move(k));
                }
                Node::Case d;
                d.head = "default:  // not one of the table's targets: the dispatch table, as the recompiled body";
                d.body.push_back(line("tail(ctx, " + s.text + ");"));
                d.body.push_back(line("return;", {}, true));
                s.cases.push_back(std::move(d));
                out.push_back(std::move(s));
                if ((!any && !broke) || m < 0) return false;  // a case falls out, or a nested `break;` leaves
                n = m;
                continue;
            }
            }
            return false;
        }
    }

    std::map<std::uint32_t, std::vector<unsigned>> table_indices(const Term& t) const {
        std::map<std::uint32_t, std::vector<unsigned>> r;
        if (!t.sw || !elf_) return r;
        std::set<std::uint32_t> targets(t.sw->targets.begin(), t.sw->targets.end());
        for (unsigned i = 0; i < 1024; ++i) {
            const auto w = elf_->word_at(t.sw->table_ea + 4 * i);
            if (!w || !targets.count(*w)) break;
            r[*w].push_back(i);
        }
        return r;
    }

    // ---- printing ----
    void collect_targets(const Seq& s) {
        for (const Node& n : s) {
            if (n.k == Node::Line && n.target >= 0) targets_.insert(n.target);
            collect_targets(n.a);
            collect_targets(n.b);
            for (const auto& c : n.cases) collect_targets(c.body);
        }
    }

    static void ind(std::string& o, int d) { o.append(static_cast<std::size_t>(d) * 4, ' '); }

    void print_seq(std::string& o, const Seq& s, int d) {
        for (std::size_t i = 0; i < s.size(); ++i) {
            const Node& n = s[i];
            switch (n.k) {
            case Node::Label: {
                const Block& b = blocks_[n.target];
                if (targets_.count(n.target)) {
                    ++out_.stats.labels;
                    ind(o, d > 0 ? d - 1 : 0);
                    o += label_name(n.target) + ":";
                    if (i + 1 == s.size()) o += ";";
                    o += "\n";
                } else if (b.pc) {
                    ind(o, d);
                    o += fmt("// 0x%08x\n", b.pc);
                }
                break;
            }
            case Node::Line:
                if (n.target >= 0) ++out_.stats.gotos;
                ind(o, d);
                if (n.text.empty()) {
                    o += "// " + n.comment;
                    o += '\n';
                    break;
                }
                o += n.text;
                if (!n.comment.empty()) o += "  // " + n.comment;
                o += "\n";
                break;
            case Node::If:
                ind(o, d);
                o += "if (" + n.text + ") {\n";
                print_seq(o, n.a, d + 1);
                ind(o, d);
                if (!n.b.empty()) {
                    o += "} else {\n";
                    print_seq(o, n.b, d + 1);
                    ind(o, d);
                }
                o += "}\n";
                break;
            case Node::For:
                ind(o, d);
                o += "for (;;) {\n";
                print_seq(o, n.a, d + 1);
                ind(o, d);
                o += "}\n";
                break;
            case Node::Switch:
                ind(o, d);
                o += "switch (" + n.text + ") {\n";
                for (const auto& c : n.cases) {
                    ind(o, d);
                    o += c.head + "\n";
                    print_seq(o, c.body, d + 1);
                }
                ind(o, d);
                o += "}\n";
                break;
            }
        }
    }

    // The prologue's frame: `addiu sp, sp, -N` and the stores of callee-saved registers to it in the entry block.
    std::string frame_summary() const {
        const Block& b = blocks_[g_.entry];
        std::int32_t frame = 0;
        std::string saves;
        for (const Stmt& s : b.stmts) {
            const Insn* in = nullptr;
            if (s.k == Stmt::Ins) in = &s.insn;
            else if (s.k == Stmt::Call && s.has_slot) in = &s.slot;
            if (!in) continue;
            if ((in->op == Op::Addiu || in->op == Op::Daddiu) && in->rs == 29 && in->rt == 29 && in->imm < 0 && !frame) frame = -in->imm;
            const bool store = in->op == Op::Sd || in->op == Op::Sq || in->op == Op::Sw || in->op == Op::Swc1;
            if (store && in->rs == 29) {
                const unsigned r = in->rt;
                const bool saved = in->op == Op::Swc1 ? (r >= 20) : ((r >= 16 && r <= 23) || r == 28 || r == 30 || r == 31);
                if (!saved) continue;
                if (!saves.empty()) saves += ", ";
                saves += (in->op == Op::Swc1 ? fmt("f%u", r) : std::string(kGpr[r])) + fmt(" sp+0x%X", static_cast<unsigned>(in->imm));
                if (in->op == Op::Sq) saves += " (sq)";
            }
        }
        if (!frame) return "; leaf frame (no stack)";
        std::string s = fmt("; frame 0x%X", static_cast<unsigned>(frame));
        if (!saves.empty()) s += ": " + saves;
        return s;
    }
};

}  // namespace

HandgenFunction handgen_function(const Program& prog, const FunctionAnalysis& a, const ElfImage* elf, const SymbolTable* syms,
                                 const HandgenOptions& opt) {
    HandgenFunction out;
    out.start = a.fn ? a.fn->start : 0;
    out.name = a.fn ? sanitize(a.fn->name) : std::string();
    (void)prog;  // the analysis already holds what the body needs (entries, returns, switch tables)
    Gen g(a, elf, syms, opt, out);
    if (!g.run()) {
        out.body.clear();
        out.shim.clear();
    }
    return out;
}

}  // namespace p3fes::recomp
