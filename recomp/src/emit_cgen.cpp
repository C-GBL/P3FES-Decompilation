#include "emit_cgen.h"

#include <cstdio>
#include <cstring>

namespace p3fes::recomp {

namespace {

// Operand signature classes; the rt declaration for every op of a class has the same shape.
enum class Sig : std::uint8_t {
    None,      // control flow / Invalid (handled elsewhere)
    Rrr,       // (rd, rs, rt), pure: dropped when rd == 0
    MulRrr,    // (rd, rs, rt) writing hi/lo as well: kept when rd == 0
    ShiftV,    // (rd, rt, rs)
    DivLike,   // (rs, rt)
    Rri,       // (rt, rs, imm)
    Rru,       // (rt, rs, uimm)
    Lui,       // (rt, uimm)
    ShiftI,    // (rd, rt, sa)
    MoveFrom,  // (rd)
    MoveTo,    // (rs)
    MtsaX,     // (rs, imm)
    Mem,       // (rt, base, imm)
    FMem,      // (ft, base, imm)
    F3,        // (fd, fs, ft)
    F2acc,     // (fs, ft)
    F2,        // (fd, fs)
    Fdt,       // sqrt.s (fd, ft): the EE reads the ft field
    FToGpr,    // mfc1 (rt, fs): dropped when rt == 0
    FFromGpr,  // mtc1 / ctc1 (rt, fs)
    Cop0From,  // mfc0 (rt, rd): dropped when rt == 0
    Cop0To,    // mtc0 (rt, rd)
    Sync,      // (stype)
    Plain,     // ()
    Eret,      // (pc) -- emitted by the control-flow path
    Cache,     // (op, base, imm)
    Pmfhl,     // (rd, fmt)
    Rrt,       // (rd, rt)
    Cop2From,  // qmfc2 / cfc2 (rt, vf-or-vi = fs field, interlock): dropped when rt == 0
    Cop2To,    // qmtc2 / ctc2 (rt, vf-or-vi = fs field, interlock)
    V3,        // (dest, fd, fs, ft[, bc])
    V2acc,     // (dest, fs, ft[, bc])
    Vi,        // (dest, fd, fs)
    Vftfs,     // (dest, ft, fs)
    Vsqrt,     // (ft, ftf)
    Vrsqrt,    // (fs, fsf, ft, ftf)
    Syscall,   // (pc)
    Break,     // rt::trap(pc, Trap::Break, code)
};

Sig sig_of(Op op) noexcept {
    using enum Op;
    switch (op) {
    case Add: case Addu: case Sub: case Subu: case And: case Or: case Xor: case Nor: case Slt: case Sltu:
    case Daddu: case Dsubu: case Movn: case Movz:
    case Paddh: case Paddub: case Padduw: case Paddw: case Pand: case Pcgth: case Pcpyld: case Pcpyud:
    case Pextlb: case Pextlh: case Pextlw: case Pextub: case Pextuw: case Pmaxh: case Pminh:
    case Pnor: case Por: case Ppacb: case Ppach: case Ppacw: case Psubb: case Psubw: case Pxor: case Qfsrv:
        return Sig::Rrr;
    case Mult: case Multu: case Madd: case Maddu: case Mult1: case Multu1: case Maddu1: case Phmadh:
        return Sig::MulRrr;
    case Sllv: case Srlv: case Srav: case Dsllv: case Dsrlv:
        return Sig::ShiftV;
    case Div: case Divu: case Div1:
        return Sig::DivLike;
    case Addi: case Addiu: case Daddiu: case Slti: case Sltiu:
        return Sig::Rri;
    case Andi: case Ori: case Xori:
        return Sig::Rru;
    case Lui:
        return Sig::Lui;
    case Sll: case Srl: case Sra: case Dsll: case Dsrl: case Dsra: case Dsll32: case Dsrl32: case Dsra32:
    case Psllh: case Psrlh: case Psrah: case Psraw:
        return Sig::ShiftI;
    case Mfhi: case Mflo: case Mfhi1: case Mflo1: case Mfsa:
        return Sig::MoveFrom;
    case Mthi: case Mtlo: case Mthi1: case Mtlo1: case Mtsa:
        return Sig::MoveTo;
    case Mtsab: case Mtsah:
        return Sig::MtsaX;
    case Lb: case Lbu: case Lh: case Lhu: case Lw: case Lwu: case Lwl: case Lwr: case Ld: case Ldl: case Ldr:
    case Sb: case Sh: case Sw: case Swl: case Swr: case Sd: case Sdl: case Sdr: case Lq: case Sq:
        return Sig::Mem;
    case Lwc1: case Swc1: case Lqc2: case Sqc2:
        return Sig::FMem;
    case AddS: case SubS: case MulS: case DivS: case MaddS: case MsubS:
        return Sig::F3;
    case AddaS: case SubaS: case MulaS: case MaddaS: case MsubaS: case CEqS: case CLeS: case CLtS:
        return Sig::F2acc;
    case AbsS: case MovS: case NegS: case CvtSW: case CvtWS:
        return Sig::F2;
    case SqrtS:
        return Sig::Fdt;
    case Mfc1:
        return Sig::FToGpr;
    case Mtc1: case Ctc1:
        return Sig::FFromGpr;
    case Mfc0:
        return Sig::Cop0From;
    case Mtc0:
        return Sig::Cop0To;
    case Sync:
        return Sig::Sync;
    case Ei: case Di: case Vnop: case Vwaitq:
        return Sig::Plain;
    case Eret:
        return Sig::Eret;
    case Cache:
        return Sig::Cache;
    case Pmfhl:
        return Sig::Pmfhl;
    case Pcpyh: case Pexew: case Prot3w:
        return Sig::Rrt;
    case Qmfc2: case Cfc2:
        return Sig::Cop2From;
    case Qmtc2: case Ctc2:
        return Sig::Cop2To;
    case Vadd: case Vsub: case Vmul: case Vmadd: case Vmsub: case Vmax: case Vmini: case Vopmsub:
        return Sig::V3;
    case Vadda: case Vmadda: case Vmsuba: case Vmula: case Vopmula:
        return Sig::V2acc;
    case Vaddi: case Vmuli: case Vmulq:
        return Sig::Vi;
    case Vabs: case Vmove: case Vftoi0: case Vitof0:
        return Sig::Vftfs;
    case Vsqrt:
        return Sig::Vsqrt;
    case Vrsqrt:
        return Sig::Vrsqrt;
    case Syscall:
        return Sig::Syscall;
    case Break:
        return Sig::Break;
    default:
        return Sig::None;
    }
}

void hex8(std::string& out, std::uint32_t v) {
    char buf[16];
    std::snprintf(buf, sizeof buf, "%08x", v);
    out += buf;
}
void hexu(std::string& out, std::uint32_t v) {  // 0x%xu
    char buf[20];
    std::snprintf(buf, sizeof buf, "0x%xu", v);
    out += buf;
}
void dec(std::string& out, long long v) {
    char buf[24];
    std::snprintf(buf, sizeof buf, "%lld", v);
    out += buf;
}
void label(std::string& out, std::uint32_t pc) {
    out += "L_";
    hex8(out, pc);
}
void skip_label(std::string& out, std::uint32_t pc) {
    out += "L_";
    hex8(out, pc);
    out += "_s";
}

void annotate(std::string& out, const Insn& insn, const GenOptions& opt) {
    if (!opt.annotate) {
        out += '\n';
        return;
    }
    char m[48];
    variant_mnemonic(insn, m, sizeof m);
    out += "  // 0x";
    hex8(out, insn.pc);
    out += ' ';
    out += m;
    out += '\n';
}

std::string sanitize(const std::string& name) {
    std::string s;
    s.reserve(name.size());
    for (char c : name) {
        const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
        s += ok ? c : '_';
    }
    return s;
}

}  // namespace

std::string function_symbol(const Function& f) {
    std::string s = "fn_" + sanitize(f.name) + "_";
    hex8(s, f.start);
    return s;
}
std::string entry_symbol(const Function& f) { return function_symbol(f) + "_entry"; }
std::string at_symbol(const Function& f, std::uint32_t pc) {
    std::string s = function_symbol(f) + "_at_";
    hex8(s, pc);
    return s;
}

std::string rt_name(const Insn& insn) {
    std::string n = mnemonic(insn.op);
    for (char& c : n)
        if (c == '.') c = '_';
    if (n == "and" || n == "or" || n == "xor") n += '_';
    if (insn.vu_bc) n += "_bc";
    return n;
}

bool generate_insn(std::string& out, const Insn& insn, const GenOptions& opt, GenStats& st) {
    if (insn.word == 0) {  // nop (sll $zero,$zero,0)
        ++st.nops_dropped;
        return false;
    }
    const Sig sig = sig_of(insn.op);
    // Pure register writes to $zero are dropped (loads keep their memory access).
    switch (sig) {
    case Sig::Rrr: case Sig::ShiftV: case Sig::ShiftI: case Sig::MoveFrom: case Sig::Pmfhl: case Sig::Rrt:
        if (insn.rd == 0) { ++st.zero_writes_dropped; return false; }
        break;
    case Sig::Rri: case Sig::Rru: case Sig::Lui: case Sig::FToGpr: case Sig::Cop0From: case Sig::Cop2From:
        if (insn.rt == 0) { ++st.zero_writes_dropped; return false; }
        break;
    default:
        break;
    }
    const std::string name = rt_name(insn);
    auto open = [&] { out += "    rt::"; out += name; out += "(ctx"; };
    auto reg = [&](unsigned r) { out += ", "; dec(out, r); };
    auto close = [&] { out += ");"; annotate(out, insn, opt); ++st.statements; };
    switch (sig) {
    case Sig::Rrr: case Sig::MulRrr: open(); reg(insn.rd); reg(insn.rs); reg(insn.rt); close(); return true;
    case Sig::ShiftV: open(); reg(insn.rd); reg(insn.rt); reg(insn.rs); close(); return true;
    case Sig::DivLike: open(); reg(insn.rs); reg(insn.rt); close(); return true;
    case Sig::Rri: open(); reg(insn.rt); reg(insn.rs); out += ", "; dec(out, insn.imm); close(); return true;
    case Sig::Rru: open(); reg(insn.rt); reg(insn.rs); out += ", "; hexu(out, insn.uimm()); close(); return true;
    case Sig::Lui: open(); reg(insn.rt); out += ", "; hexu(out, insn.uimm()); close(); return true;
    case Sig::ShiftI: open(); reg(insn.rd); reg(insn.rt); reg(insn.sa); close(); return true;
    case Sig::MoveFrom: open(); reg(insn.rd); close(); return true;
    case Sig::MoveTo: open(); reg(insn.rs); close(); return true;
    case Sig::MtsaX: open(); reg(insn.rs); out += ", "; dec(out, insn.imm); close(); return true;
    case Sig::Mem: open(); reg(insn.rt); reg(insn.rs); out += ", "; dec(out, insn.imm); close(); return true;
    case Sig::FMem: open(); reg(insn.ft); reg(insn.rs); out += ", "; dec(out, insn.imm); close(); return true;
    case Sig::F3: open(); reg(insn.fd); reg(insn.fs); reg(insn.ft); close(); return true;
    case Sig::F2acc: open(); reg(insn.fs); reg(insn.ft); close(); return true;
    case Sig::F2: open(); reg(insn.fd); reg(insn.fs); close(); return true;
    case Sig::Fdt: open(); reg(insn.fd); reg(insn.ft); close(); return true;
    case Sig::FToGpr: case Sig::FFromGpr: open(); reg(insn.rt); reg(insn.fs); close(); return true;
    case Sig::Cop0From: case Sig::Cop0To: open(); reg(insn.rt); reg(insn.rd); close(); return true;
    case Sig::Sync: open(); reg(insn.fmt); close(); return true;
    case Sig::Plain: open(); close(); return true;
    case Sig::Cache: open(); reg(insn.rt); reg(insn.rs); out += ", "; dec(out, insn.imm); close(); return true;
    case Sig::Pmfhl: open(); reg(insn.rd); reg(insn.fmt); close(); return true;
    case Sig::Rrt: open(); reg(insn.rd); reg(insn.rt); close(); return true;
    case Sig::Cop2From: case Sig::Cop2To:
        open(); reg(insn.rt); reg(insn.fs);
        out += insn.interlock ? ", true" : ", false";
        close(); return true;
    case Sig::V3:
        open(); reg(insn.dest); reg(insn.fd); reg(insn.fs); reg(insn.ft);
        if (insn.vu_bc) reg(insn.bc);
        close(); return true;
    case Sig::V2acc:
        open(); reg(insn.dest); reg(insn.fs); reg(insn.ft);
        if (insn.vu_bc) reg(insn.bc);
        close(); return true;
    case Sig::Vi: open(); reg(insn.dest); reg(insn.fd); reg(insn.fs); close(); return true;
    case Sig::Vftfs: open(); reg(insn.dest); reg(insn.ft); reg(insn.fs); close(); return true;
    case Sig::Vsqrt: open(); reg(insn.ft); reg(insn.vftf()); close(); return true;
    case Sig::Vrsqrt: open(); reg(insn.fs); reg(insn.vfsf()); reg(insn.ft); reg(insn.vftf()); close(); return true;
    case Sig::Syscall: open(); out += ", "; hexu(out, insn.pc); close(); return true;
    case Sig::Break:
        out += "    rt::trap(ctx, "; hexu(out, insn.pc); out += ", rt::Trap::Break, "; hexu(out, insn.code()); out += ");";
        annotate(out, insn, opt); ++st.statements;
        return true;
    case Sig::Eret:
        out += "    rt::eret(ctx, "; hexu(out, insn.pc); out += ");"; annotate(out, insn, opt); ++st.statements;
        return true;
    case Sig::None:
        break;
    }
    // Op::Invalid (only with --keep-going) or a control-flow op reaching this path by mistake.
    ++st.invalid_words;
    out += "    rt::trap(ctx, "; hexu(out, insn.pc); out += ", rt::Trap::Unsupported, "; hexu(out, insn.word); out += ");";
    out += "  // undecodable word";
    out += '\n';
    ++st.statements;
    return true;
}

namespace {

struct Ctx {
    const Program& prog;
    const FunctionAnalysis& a;
    const GenOptions& opt;
    GenStats& st;
    std::set<std::uint32_t> emitted_labels;
};

// A loop back-edge (ADR-0013 §2): a local edge whose target lies at or below the branch's own
// address. Switch cases are judged against the `jr`'s address.
bool is_backedge(const Edge& e, std::uint32_t from_pc) noexcept {
    return e.kind == EdgeKind::Local && e.target <= from_pc;
}

// Text of a taken edge (ends the current block: goto / return / noreturn call). A tail call to a
// root that cannot return gets no `return;` (it would be unreachable code once inlined).
// `branch` = the edge leaves a branch/jump at `from_pc` (false for a chunk's fall-through end
// edge, which is never backward); a backward local edge is preceded by rt::check_events.
void edge_text(std::string& out, const Edge& e, Ctx& c, bool branch, std::uint32_t from_pc) {
    if (branch && c.opt.check_events && is_backedge(e, from_pc)) {
        out += "rt::check_events(ctx); ";
        ++c.st.backedge_checks;
    }
    // a replaced callee: its reference-mode selector (functions.h); a mid-body entry through its _at_<pc8> wrapper
    // (the entry point game/ defines when the function is replaced; the generated one-liner otherwise)
    const auto callee = [&c](const Function& f, std::uint32_t at = 0) {
        std::string s = at ? at_symbol(f, at) : function_symbol(f);
        if (c.opt.replaced && c.opt.replaced->count(f.start)) s += "__sel";
        return s;
    };
    switch (e.kind) {
    case EdgeKind::Local: out += "goto "; label(out, e.target); out += ';'; break;
    case EdgeKind::TailFunc: out += callee(*e.fn); out += e.returns ? "(ctx); return;" : "(ctx);"; break;
    case EdgeKind::TailEntry: out += callee(*e.fn, e.target); out += e.returns ? "(ctx); return;" : "(ctx);"; break;
    case EdgeKind::CallFunc: out += callee(*e.fn); out += "(ctx);"; break;
    case EdgeKind::CallEntry: out += callee(*e.fn, e.target); out += "(ctx);"; break;
    case EdgeKind::Return: out += "return;"; break;
    case EdgeKind::Unreachable:
    case EdgeKind::Unowned: out += "rt::unreachable("; hexu(out, e.target); out += ");"; break;
    case EdgeKind::Switch: case EdgeKind::IndirectCall: case EdgeKind::IndirectTail:
        out += "/* register edge */";  // never emitted through this path
        break;
    }
}

void condition_text(std::string& out, const Insn& in) {
    using enum Op;
    auto two = [&](const char* f) { out += "rt::"; out += f; out += "(ctx, "; dec(out, in.rs); out += ", "; dec(out, in.rt); out += ')'; };
    auto one = [&](const char* f) { out += "rt::"; out += f; out += "(ctx, "; dec(out, in.rs); out += ')'; };
    switch (in.op) {
    case Beq: case Beql: two("cmp_eq"); break;
    case Bne: case Bnel: two("cmp_ne"); break;
    case Blez: case Blezl: one("cmp_lez"); break;
    case Bgtz: case Bgtzl: one("cmp_gtz"); break;
    case Bltz: case Bltzl: one("cmp_ltz"); break;
    case Bgez: case Bgezl: one("cmp_gez"); break;
    case Bc1t: case Bc1tl: out += "rt::cop1_cond(ctx)"; break;
    case Bc1f: case Bc1fl: out += "!rt::cop1_cond(ctx)"; break;
    case Bc0f: out += "!rt::cop0_cond(ctx)"; break;
    default: out += "false /* not a branch */"; break;
    }
}

// ---------------------------------------------------------------------------------------------
// Cycle accounting (recomp/README.md "Cycle accounting and check points").
//
// A basic block starts at (1) the function start, (2) every emitted label (branch / switch /
// entry targets, chunk starts), (3) the fall-through of a reached conditional branch, and (4) a
// delay slot that is itself a branch target (its own label, emitted after the branch). It runs
// to the first conditional branch or terminator (inclusive of its delay slot) or to the next
// leader. Calls that return (jal/jalr) do not end a block: the words after the delay slot are
// charged with the words before the call. N = instruction words, delay slots included, `nop`s
// included; a likely branch's slot is counted once whether or not it runs. The one exception
// keeps every path exact: a non-likely conditional branch whose delay slot is a branch target
// charges only the branch word; its slot is charged inside the taken path (`ctx.cycles += 1;`)
// and under the slot's label, which the not-taken path falls through.
// ---------------------------------------------------------------------------------------------
bool is_conditional(const Item& it) noexcept { return it.is_cf && it.has_slot && !it.unconditional; }

bool is_leader(const Ctx& c, const ChunkAnalysis& ch, std::size_t i) {
    const Item& it = ch.items[i];
    if (it.pc == c.a.fn->start) return true;
    if (c.a.labels.count(it.pc)) return true;
    return i > 0 && ch.items[i - 1].reachable && is_conditional(ch.items[i - 1]);
}

// Words from the leader at item `i` to the end of its block.
std::size_t block_words(const Ctx& c, const ChunkAnalysis& ch, std::size_t i) {
    std::size_t n = 0;
    for (std::size_t k = i; k < ch.items.size(); ++k) {
        const Item& it = ch.items[k];
        if (!it.reachable) break;
        if (k != i && is_leader(c, ch, k)) break;
        if (it.kind == Item::Kind::Data) break;  // rt::unreachable: nothing executes
        if (!it.is_cf) {
            ++n;
            continue;
        }
        if (!it.has_slot) {  // eret
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

// Words charged after a delay-slot label for the code that follows the slot (item `i` = the item
// at slot + 4): nothing when that item starts its own block.
std::size_t continuation_words(const Ctx& c, const ChunkAnalysis& ch, std::size_t i) {
    if (i >= ch.items.size() || !ch.items[i].reachable || is_leader(c, ch, i)) return 0;
    return block_words(c, ch, i);
}

void cycles_text(std::string& out, std::size_t n, Ctx& c, bool nested = false) {
    if (!c.opt.cycles || n == 0) return;
    out += nested ? "        ctx.cycles += " : "    ctx.cycles += ";
    dec(out, static_cast<long long>(n));
    out += ";\n";
    ++c.st.cycle_adds;
    c.st.cycle_words += n;
}

// The delay-slot statement; `nested` adds one indent level (inside a { } block).
void slot_text(std::string& out, const Item& it, Ctx& c, bool nested) {
    if (!it.has_slot) return;
    std::string s;
    generate_insn(s, it.slot, c.opt, c.st);
    if (s.empty()) return;
    if (nested) out += "    ";
    out += s;  // "    rt::...;\n"
}

void emit_label(std::string& out, std::uint32_t pc, Ctx& c) {
    if (c.a.labels.count(pc) && !c.emitted_labels.count(pc)) {
        label(out, pc);
        out += ":\n";
        c.emitted_labels.insert(pc);
    }
}

// A branch elsewhere targets this item's delay slot: the slot word runs again under its own
// label as an ordinary instruction, and execution continues with the item at pc + 8.
void emit_slot_label_tail(std::string& out, const ChunkAnalysis& ch, std::size_t idx, Ctx& c) {
    const Item& it = ch.items[idx];
    label(out, it.pc + 4);
    out += ":\n";
    c.emitted_labels.insert(it.pc + 4);
    cycles_text(out, 1 + continuation_words(c, ch, idx + 1), c);
    std::string s;
    if (!generate_insn(s, it.slot, c.opt, c.st)) s = "    ;\n";
    out += s;
}

// Link-register write of jal / jalr (gpr[rd] = pc + 8), before the delay slot as on hardware.
void link_text(std::string& out, const Insn& in, bool nested) {
    if (in.op == Op::Jal) {
        out += nested ? "        " : "    ";
        out += "rt::jal(ctx, "; hexu(out, in.pc); out += ");\n";
    } else if (in.op == Op::Jalr && in.rd != 0) {
        out += nested ? "        " : "    ";
        out += "rt::jalr(ctx, "; dec(out, in.rd); out += ", "; hexu(out, in.pc); out += ");\n";
    }
}

void emit_cf(std::string& out, const ChunkAnalysis& ch, std::size_t idx, Ctx& c) {
    const Item& it = ch.items[idx];
    const Insn& in = it.insn;
    const bool reg_edge = it.edge.kind == EdgeKind::Switch || it.edge.kind == EdgeKind::IndirectCall ||
                          it.edge.kind == EdgeKind::IndirectTail;
    if (c.opt.annotate) {
        char m[48];
        variant_mnemonic(in, m, sizeof m);
        out += "    // 0x"; hex8(out, in.pc); out += ' '; out += m; out += '\n';
    }

    if (in.op == Op::Eret) {
        out += "    rt::eret(ctx, "; hexu(out, in.pc); out += ");\n    return;\n";
        c.st.statements += 2;
        return;
    }

    if (reg_edge) {
        // The target register is read before the delay slot runs (the slot may overwrite it).
        out += "    {\n        const std::uint32_t t = rt::reg32(ctx, "; dec(out, in.rs); out += ");\n";
        link_text(out, in, true);
        slot_text(out, it, c, true);
        if (it.edge.kind == EdgeKind::Switch) {
            out += "        switch (t) {\n";
            for (const Edge& e : it.sw_edges) {
                out += "        case "; hexu(out, e.target); out += ": ";
                edge_text(out, e, c, true, in.pc);
                out += '\n';
            }
            out += "        default: rt::lookup_func(t)(ctx); return;\n        }\n";
        } else if (it.edge.kind == EdgeKind::IndirectTail) {
            out += "        rt::lookup_func(t)(ctx);\n        return;\n";
        } else {  // IndirectCall
            out += "        rt::lookup_func(t)(ctx);\n";
            if (it.slot_is_label) { out += "        goto "; skip_label(out, in.pc + 8); out += ";\n"; }
        }
        out += "    }\n";
        c.st.statements += 2;
        if (it.slot_is_label) {
            emit_slot_label_tail(out, ch, idx, c);
            if (it.edge.kind == EdgeKind::IndirectCall) { skip_label(out, in.pc + 8); out += ":\n"; }
        }
        return;
    }

    if (it.unconditional) {
        // j / jal / jr $ra / beq r,r: link, slot, then the edge.
        if (!it.slot_is_label) {
            link_text(out, in, false);
            slot_text(out, it, c, false);
            out += "    "; edge_text(out, it.edge, c, true, in.pc); out += '\n';
            ++c.st.statements;
            return;
        }
        out += "    {\n";
        link_text(out, in, true);
        slot_text(out, it, c, true);
        out += "        "; edge_text(out, it.edge, c, true, in.pc); out += '\n';
        if (!it.terminates) { out += "        goto "; skip_label(out, in.pc + 8); out += ";\n"; }
        out += "    }\n";
        ++c.st.statements;
        emit_slot_label_tail(out, ch, idx, c);
        if (!it.terminates) { skip_label(out, in.pc + 8); out += ":\n"; }
        return;
    }

    // Conditional branch: the condition is evaluated first (the slot may change its operands),
    // the slot runs on the taken path inside the block.
    out += "    if ("; condition_text(out, in); out += ") {\n";
    if (it.slot_is_label && !in.is_likely) cycles_text(out, 1, c, true);  // see "Cycle accounting" above
    slot_text(out, it, c, true);
    out += "        "; edge_text(out, it.edge, c, true, in.pc); out += "\n    }\n";
    ++c.st.statements;
    if (in.is_likely) {
        // Not taken: the slot is skipped (it runs only when a branch targets it directly).
        if (it.slot_is_label) {
            out += "    goto "; skip_label(out, in.pc + 8); out += ";\n";
            emit_slot_label_tail(out, ch, idx, c);
            skip_label(out, in.pc + 8); out += ":\n";
        }
        return;
    }
    // Not taken: the slot runs once, under its label when a branch targets it.
    if (it.slot_is_label) emit_slot_label_tail(out, ch, idx, c);
    else slot_text(out, it, c, false);
}

// One comment line for a run of words no static path reaches.
void dead_run_comment(std::string& out, std::uint32_t lo, std::uint32_t hi, std::size_t words, std::size_t data) {
    out += "    // 0x"; hex8(out, lo); out += "..0x"; hex8(out, hi);
    out += ": not reached by any static path, not emitted ("; dec(out, static_cast<long long>(words)); out += " word";
    if (words != 1) out += 's';
    if (data) { out += ", "; dec(out, static_cast<long long>(data)); out += " IDA data"; }
    out += ")\n";
}

}  // namespace

void generate_declaration(std::string& out, const Program& prog, const Function& f) {
    out += "void "; out += function_symbol(f); out += "(p3fes::EEContext&);\n";
    if (prog.has_entries(f)) {
        out += "void "; out += entry_symbol(f); out += "(p3fes::EEContext&, std::uint32_t);\n";
        for (std::uint32_t e : prog.entries_of(f)) {
            out += "void "; out += at_symbol(f, e); out += "(p3fes::EEContext&);\n";
        }
    }
}

void generate_function(std::string& out, const Program& prog, const FunctionAnalysis& a, const GenOptions& opt, GenStats& st) {
    const Function& f = *a.fn;
    Ctx c{prog, a, opt, st, {}};
    std::string body;

    // Check point once per invocation: before the entry dispatch (entry form) or at the top of the
    // body, ahead of any label a back-edge could reach, so a loop to the start checks only once.
    if (opt.check_events) {
        body += "    rt::check_events(ctx);\n";
        ++st.entry_checks;
    }
    if (a.entry_form) {
        body += "    switch (entry_pc) {\n";
        body += "    case "; hexu(body, f.start); body += ": goto "; label(body, f.start); body += ";\n";
        for (std::uint32_t e : a.entries) {
            body += "    case "; hexu(body, e); body += ": goto "; label(body, e); body += ";\n";
        }
        body += "    default: rt::bad_entry("; hexu(body, f.start); body += ", entry_pc);\n    }\n";
    }

    for (const ChunkAnalysis& ch : a.chunks) {
        if (opt.annotate) {
            body += "    // chunk 0x"; hex8(body, ch.range.start); body += "..0x"; hex8(body, ch.range.end); body += '\n';
        }
        // Words no static path reaches are not emitted (one comment per run); everything that is
        // emitted is reachable in the C++ as well, so no C4702 suppression is needed.
        std::uint32_t run_lo = 0, run_hi = 0;
        std::size_t run_words = 0, run_data = 0;
        auto flush_run = [&] {
            if (run_words) dead_run_comment(body, run_lo, run_hi, run_words, run_data);
            run_words = run_data = 0;
        };
        for (std::size_t i = 0; i < ch.items.size(); ++i) {
            const Item& it = ch.items[i];
            if (!it.reachable) {
                if (!run_words) run_lo = it.pc;
                const std::uint32_t n = it.has_slot ? 2u : 1u;
                run_hi = it.pc + 4 * n;
                run_words += n;
                if (it.kind == Item::Kind::Data) ++run_data;
                if (it.is_cf && it.slot_is_label) {
                    // The branch is dead but its slot is a target: the slot stays, under its label.
                    run_hi -= 4;
                    --run_words;
                    flush_run();
                    emit_slot_label_tail(body, ch, i, c);
                }
                continue;
            }
            flush_run();
            emit_label(body, it.pc, c);
            if (is_leader(c, ch, i)) cycles_text(body, block_words(c, ch, i), c);
            if (it.kind == Item::Kind::Data) {
                body += "    rt::unreachable("; hexu(body, it.pc); body += ");  // IDA data word reached by fall-through\n";
                ++st.statements;
                continue;
            }
            if (it.is_cf) {
                emit_cf(body, ch, i, c);
                continue;
            }
            generate_insn(body, it.insn, opt, st);
        }
        flush_run();
        if (ch.end_reachable) {
            if (opt.annotate) { body += "    // fall-through at 0x"; hex8(body, ch.end_pc); body += '\n'; }
            body += "    "; edge_text(body, ch.end_edge, c, false, 0); body += '\n';
            ++st.statements;
        }
    }
    // Labels nobody emitted (a target with no item at that address): fail closed with a trap
    // that names the address.
    for (std::uint32_t l : a.labels) {
        if (c.emitted_labels.count(l)) continue;
        label(body, l); body += ":\n    rt::unreachable("; hexu(body, l); body += ");  // dangling label\n";
        ++st.dangling_labels;
        c.emitted_labels.insert(l);
    }

    const bool uses_ctx = body.find("ctx") != std::string::npos;
    out += "// "; out += f.name; out += " @ 0x"; hex8(out, f.start);
    out += " (size "; dec(out, f.size); out += ", chunks "; dec(out, static_cast<long long>(a.chunks.size()));
    if (a.entry_form) { out += ", entries "; dec(out, static_cast<long long>(a.entries.size())); }
    out += ")\n";
    if (a.entry_form) {
        // The suffix (a replaced function's __recomp) goes on the entry form and on every wrapper: game/ defines the
        // plain fn_X and fn_X_at_<pc8> (the call sites and dispatch rows use those), nothing uses a plain fn_X_entry.
        const std::string& sfx = opt.symbol_suffix;
        out += "void "; out += entry_symbol(f); out += sfx; out += "(p3fes::EEContext& "; if (!uses_ctx) out += "/*"; out += "ctx"; if (!uses_ctx) out += "*/";
        out += ", std::uint32_t entry_pc) {\n";
        out += body;
        out += "}\n";
        out += "void "; out += function_symbol(f); out += sfx; out += "(p3fes::EEContext& ctx) { "; out += entry_symbol(f); out += sfx;
        out += "(ctx, "; hexu(out, f.start); out += "); }\n";
        for (std::uint32_t e : a.entries) {
            out += "void "; out += at_symbol(f, e); out += sfx; out += "(p3fes::EEContext& ctx) { "; out += entry_symbol(f); out += sfx;
            out += "(ctx, "; hexu(out, e); out += "); }\n";
        }
    } else {
        out += "void "; out += function_symbol(f); out += opt.symbol_suffix; out += "(p3fes::EEContext& "; if (!uses_ctx) out += "/*"; out += "ctx"; if (!uses_ctx) out += "*/";
        out += ") {\n";
        out += body;
        out += "}\n";
    }
    out += '\n';
}

}  // namespace p3fes::recomp
