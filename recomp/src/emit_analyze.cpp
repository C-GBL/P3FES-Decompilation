#include "emit_analyze.h"

#include <unordered_map>

namespace p3fes::recomp {

const char* problem_name(ProblemKind k) noexcept {
    switch (k) {
    case ProblemKind::InvalidWord: return "invalid_word";
    case ProblemKind::UnbackedWord: return "unbacked_word";
    case ProblemKind::BranchInSlot: return "branch_in_delay_slot";
    case ProblemKind::SlotIsData: return "delay_slot_is_data";
    case ProblemKind::SlotUnbacked: return "delay_slot_unbacked";
    case ProblemKind::UnownedTarget: return "target_in_no_function";
    case ProblemKind::UnownedSwitchTarget: return "switch_target_in_no_function";
    }
    return "?";
}

Edge classify_static_target(const Program& prog, const Function& self, std::uint32_t target, bool is_call) noexcept {
    if (is_call) {
        if (const Function* g = prog.function_at(target)) return {EdgeKind::CallFunc, target, g};
        if (Program::contains(self, target)) return {EdgeKind::CallEntry, target, &self};
        if (const Function* o = prog.owner_of(target)) return {EdgeKind::CallEntry, target, o};
        return {EdgeKind::Unowned, target, nullptr};
    }
    if (Program::contains(self, target)) return {EdgeKind::Local, target, nullptr};
    if (const Function* g = prog.function_at(target)) return {EdgeKind::TailFunc, target, g};
    if (const Function* o = prog.owner_of(target)) return {EdgeKind::TailEntry, target, o};
    return {EdgeKind::Unowned, target, nullptr};
}

namespace {

constexpr Insn kNop = decode(0u, 0u);

void count_edge(FunctionStats& st, const Edge& e) {
    switch (e.kind) {
    case EdgeKind::CallFunc: ++st.calls; break;
    case EdgeKind::CallEntry: ++st.mid_body_calls; break;
    case EdgeKind::TailFunc:
    case EdgeKind::TailEntry: ++st.tail_calls; break;
    default: break;
    }
}

// Pass 1: decode every word of every chunk (data items by address, never decoded) and classify
// each control-flow item's edges. Nothing here depends on reachability.
void decode_chunks(const Program& prog, const Function& fn, FunctionAnalysis& a) {
    std::vector<Range> single;
    const std::vector<Range>* chunks = &fn.chunks;
    if (chunks->empty()) {
        single.assign(1, Range{fn.start, fn.start + fn.size});
        chunks = &single;
    }
    const WordSource& words = prog.words();
    const SwitchTables& sw = prog.switches();

    for (const Range& r : *chunks) {
        ChunkAnalysis c;
        c.range = r;
        std::uint32_t va = r.start;
        while (va < r.end) {
            Item it;
            it.pc = va;
            if (fn.is_data(va)) {
                it.kind = Item::Kind::Data;
                ++a.stats.data_words;
                c.items.push_back(std::move(it));
                va += 4;
                continue;
            }
            const auto w = words.word_at(va);
            if (!w) {
                a.problems.push_back({ProblemKind::UnbackedWord, va, 0});
                it.kind = Item::Kind::Data;
                c.items.push_back(std::move(it));
                va += 4;
                continue;
            }
            it.insn = decode(*w, va);
            ++a.stats.words;
            const Insn& in = it.insn;
            if (in.op == Op::Invalid) {
                a.problems.push_back({ProblemKind::InvalidWord, va, 0});
                c.items.push_back(std::move(it));
                va += 4;
                continue;
            }
            if (in.op == Op::Eret) {
                it.is_cf = true;
                it.unconditional = true;
                it.terminates = true;
                it.edge = {EdgeKind::Return, 0, nullptr};
                c.items.push_back(std::move(it));
                va += 4;
                continue;
            }
            if (!in.has_delay_slot) {
                c.items.push_back(std::move(it));
                va += 4;
                continue;
            }

            // Branch or jump: fetch the slot by address, even past the chunk end.
            it.is_cf = true;
            it.has_slot = true;
            const std::uint32_t slot_pc = va + 4;
            it.slot = kNop;
            it.slot_outside_chunk = slot_pc >= r.end;
            if (fn.is_data(slot_pc)) {
                a.problems.push_back({ProblemKind::SlotIsData, va, slot_pc});
            } else if (const auto sw_word = words.word_at(slot_pc)) {
                it.slot = decode(*sw_word, slot_pc);
                ++a.stats.words;
                if (it.slot.op == Op::Invalid) a.problems.push_back({ProblemKind::InvalidWord, slot_pc, 0});
                if (it.slot.has_delay_slot || it.slot.op == Op::Eret)
                    a.problems.push_back({ProblemKind::BranchInSlot, va, slot_pc});
            } else {
                a.problems.push_back({ProblemKind::SlotUnbacked, va, slot_pc});
            }

            switch (in.op) {
            case Op::J:
                it.edge = classify_static_target(prog, fn, in.target, false);
                it.unconditional = it.terminates = true;
                break;
            case Op::Jal:
                it.edge = classify_static_target(prog, fn, in.target, true);
                it.unconditional = true;
                break;
            case Op::Jr: {
                auto s = sw.by_jr.find(va);
                if (s != sw.by_jr.end()) {
                    it.edge = {EdgeKind::Switch, 0, nullptr};
                    it.sw = &s->second;
                    for (std::uint32_t t : s->second.targets) {
                        Edge e = classify_static_target(prog, fn, t, false);
                        if (e.kind == EdgeKind::Unowned) a.problems.push_back({ProblemKind::UnownedSwitchTarget, va, t});
                        it.sw_edges.push_back(e);
                    }
                } else if (in.rs == 31) {
                    it.edge = {EdgeKind::Return, 0, nullptr};
                } else {
                    it.edge = {EdgeKind::IndirectTail, 0, nullptr};
                }
                it.unconditional = it.terminates = true;
                break;
            }
            case Op::Jalr:
                it.edge = {EdgeKind::IndirectCall, 0, nullptr};
                it.unconditional = true;
                break;
            default:  // conditional branches, including bc0f / bc1*
                it.edge = classify_static_target(prog, fn, in.target, false);
                if ((in.op == Op::Beq || in.op == Op::Beql) && in.rs == in.rt) it.unconditional = it.terminates = true;
                break;
            }
            if (it.edge.kind == EdgeKind::Unowned) a.problems.push_back({ProblemKind::UnownedTarget, va, it.edge.target});
            c.items.push_back(std::move(it));
            va += 8;
        }

        // Where a fall-through off the end of this chunk would go. A delay slot beyond the chunk
        // end was already executed with its branch, so execution resumes after it.
        c.end_pc = r.end;
        if (!c.items.empty() && c.items.back().is_cf && c.items.back().slot_outside_chunk)
            c.end_pc = c.items.back().pc + 8;
        c.end_edge = classify_static_target(prog, fn, c.end_pc, false);
        if (c.end_edge.kind == EdgeKind::Unowned) c.end_edge.kind = EdgeKind::Unreachable;
        a.chunks.push_back(std::move(c));
    }
}

bool is_call(EdgeKind k) noexcept { return k == EdgeKind::CallFunc || k == EdgeKind::CallEntry; }
bool is_tail(EdgeKind k) noexcept { return k == EdgeKind::TailFunc || k == EdgeKind::TailEntry; }

// Pass 2: what the callees do. A call or tail call to a root that cannot return (as far as the
// program-wide fixpoint has proven, Program::returns_from) ends the path: the call item then
// terminates, and a tail call is emitted without the `return;` that would follow it.
void apply_callee_returns(const Program& prog, FunctionAnalysis& a) {
    auto set = [&](Edge& e) {
        if (is_call(e.kind) || is_tail(e.kind)) e.returns = prog.returns_from(e.target);
    };
    for (ChunkAnalysis& c : a.chunks) {
        for (Item& it : c.items) {
            if (!it.is_cf) continue;
            set(it.edge);
            for (Edge& e : it.sw_edges) set(e);
            if (is_call(it.edge.kind) && !it.edge.returns) it.terminates = true;
        }
        set(c.end_edge);
    }
}

// Pass 3: the static walk from `roots` over the decoded items. Returns whether some path from the
// roots leaves the function (a `return;` in the emitted C++: jr $ra, eret, a register tail jump, a
// switch default, or a tail call to a root that returns). With `record`, the reached items,
// entered delay slots and reached chunk ends are stored in `a` for the generator.
bool walk(FunctionAnalysis& a, const std::vector<std::uint32_t>& roots, bool record) {
    struct Pos {
        std::uint32_t chunk, item;
    };
    std::unordered_map<std::uint32_t, Pos> item_at;  // item start -> position
    std::unordered_map<std::uint32_t, Pos> slot_at;  // delay-slot word -> position of its branch
    std::vector<std::vector<char>> reached(a.chunks.size()), slot_entered(a.chunks.size());
    std::vector<char> end_reached(a.chunks.size(), 0);
    for (std::uint32_t ci = 0; ci < a.chunks.size(); ++ci) {
        const ChunkAnalysis& c = a.chunks[ci];
        reached[ci].assign(c.items.size(), 0);
        slot_entered[ci].assign(c.items.size(), 0);
        for (std::uint32_t ii = 0; ii < c.items.size(); ++ii) {
            item_at.emplace(c.items[ii].pc, Pos{ci, ii});
            if (c.items[ii].has_slot) slot_at.emplace(c.items[ii].pc + 4, Pos{ci, ii});
        }
    }
    bool exits = false;
    std::vector<Pos> work;
    auto mark = [&](Pos p) {
        if (!reached[p.chunk][p.item]) {
            reached[p.chunk][p.item] = 1;
            work.push_back(p);
        }
    };
    // Falling off the end of chunk `ci`; reach() and end() recurse through Local end edges.
    auto reach = [&](auto& self, std::uint32_t va) -> void {
        auto end = [&](std::uint32_t ci) {
            if (end_reached[ci]) return;
            end_reached[ci] = 1;
            const Edge& e = a.chunks[ci].end_edge;
            if (e.kind == EdgeKind::Local) self(self, e.target);
            else if (is_tail(e.kind) && e.returns) exits = true;
        };
        auto i = item_at.find(va);
        if (i != item_at.end()) {
            mark(i->second);
            return;
        }
        auto s = slot_at.find(va);
        if (s == slot_at.end()) return;  // no item: a dangling label, trapped by the generator
        const Pos p = s->second;
        if (slot_entered[p.chunk][p.item]) return;
        slot_entered[p.chunk][p.item] = 1;  // the slot runs as an ordinary instruction, then pc + 8
        if (p.item + 1 < a.chunks[p.chunk].items.size()) mark({p.chunk, p.item + 1});
        else end(p.chunk);
    };
    auto next = [&](Pos p) {
        ChunkAnalysis& c = a.chunks[p.chunk];
        if (p.item + 1 < c.items.size()) {
            mark({p.chunk, p.item + 1});
            return;
        }
        if (end_reached[p.chunk]) return;
        end_reached[p.chunk] = 1;
        const Edge& e = c.end_edge;
        if (e.kind == EdgeKind::Local) reach(reach, e.target);
        else if (is_tail(e.kind) && e.returns) exits = true;
    };

    for (std::uint32_t r : roots) reach(reach, r);
    while (!work.empty()) {
        const Pos p = work.back();
        work.pop_back();
        const Item& it = a.chunks[p.chunk].items[p.item];
        if (it.kind == Item::Kind::Data) continue;      // rt::unreachable ([[noreturn]]): no successor
        if (it.insn.op == Op::Invalid) continue;        // fail closed: no successor
        if (!it.is_cf) {
            next(p);
            continue;
        }
        switch (it.edge.kind) {
        case EdgeKind::Local: reach(reach, it.edge.target); break;
        case EdgeKind::Return: case EdgeKind::IndirectTail: case EdgeKind::Switch: exits = true; break;
        case EdgeKind::TailFunc: case EdgeKind::TailEntry: if (it.edge.returns) exits = true; break;
        default: break;
        }
        for (const Edge& e : it.sw_edges) {
            if (e.kind == EdgeKind::Local) reach(reach, e.target);
            else if (is_tail(e.kind) && e.returns) exits = true;
        }
        if (!it.terminates) next(p);
    }
    if (record) {
        for (std::uint32_t ci = 0; ci < a.chunks.size(); ++ci) {
            ChunkAnalysis& c = a.chunks[ci];
            c.end_reachable = end_reached[ci] != 0;
            for (std::uint32_t ii = 0; ii < c.items.size(); ++ii) {
                c.items[ii].reachable = reached[ci][ii] != 0;
                c.items[ii].slot_is_label = slot_entered[ci][ii] != 0;
            }
        }
    }
    return exits;
}

void collect_labels_and_stats(FunctionAnalysis& a) {
    FunctionStats& st = a.stats;
    for (const ChunkAnalysis& c : a.chunks) {
        for (const Item& it : c.items) {
            if (!it.reachable) {
                if (it.kind == Item::Kind::Data) ++st.dead_data_words;
                else ++st.dead_words;
                if (it.has_slot && !it.slot_is_label) ++st.dead_words;
                continue;
            }
            if (it.kind == Item::Kind::Data) {
                ++st.reached_data_words;
                continue;
            }
            if (it.insn.op == Op::Syscall) ++st.syscalls;
            if (it.insn.op == Op::Break) ++st.breaks;
            if (!it.is_cf) continue;
            if (it.insn.op == Op::Eret) ++st.erets;
            if (it.edge.kind == EdgeKind::Local) a.labels.insert(it.edge.target);
            for (const Edge& e : it.sw_edges)
                if (e.kind == EdgeKind::Local) a.labels.insert(e.target);
            if (is_tail(it.edge.kind) && !it.edge.returns) ++st.noreturn_tail_calls;
            if (is_call(it.edge.kind) && !it.edge.returns) ++st.noreturn_calls;
            if (it.insn.is_branch) {
                ++st.branches;
                if (it.insn.is_likely) ++st.likely_branches;
            }
            switch (it.edge.kind) {
            case EdgeKind::Return: if (it.insn.op == Op::Jr) ++st.returns; break;
            case EdgeKind::IndirectCall: ++st.indirect_calls; break;
            case EdgeKind::IndirectTail: ++st.indirect_tails; break;
            case EdgeKind::Switch:
                ++st.switches;
                st.switch_targets += it.sw_edges.size();
                break;
            default: break;
            }
            count_edge(st, it.edge);
            for (const Edge& e : it.sw_edges) count_edge(st, e);
            if (it.slot_outside_chunk) ++st.slots_outside_chunk;
        }
        if (c.end_reachable) {
            if (c.end_edge.kind == EdgeKind::Local) a.labels.insert(c.end_edge.target);
            if (is_tail(c.end_edge.kind) && !c.end_edge.returns) ++st.noreturn_tail_calls;
            if (c.end_edge.kind == EdgeKind::Unreachable) ++st.unreachable_ends;
            count_edge(st, c.end_edge);
        }
    }
    for (const ChunkAnalysis& c : a.chunks)
        for (const Item& it : c.items)
            if (it.slot_is_label) ++st.slot_labels;
}

}  // namespace

FunctionAnalysis analyze_function(const Program& prog, const Function& fn) {
    FunctionAnalysis a;
    a.fn = &fn;
    a.entries = prog.entries_of(fn);
    a.entry_form = !a.entries.empty();
    for (std::uint32_t e : a.entries) a.labels.insert(e);
    if (a.entry_form) a.labels.insert(fn.start);

    decode_chunks(prog, fn, a);
    apply_callee_returns(prog, a);
    std::vector<std::uint32_t> roots{fn.start};
    roots.insert(roots.end(), a.entries.begin(), a.entries.end());
    const bool exits = walk(a, roots, /*record=*/true);
    if (roots.size() == 1) {
        a.root_returns.emplace(fn.start, exits);
    } else {
        // Each entry separately: a caller entering mid-body may reach a different set of exits.
        for (std::uint32_t r : roots) a.root_returns.emplace(r, exits && walk(a, {r}, /*record=*/false));
    }
    a.returns = exits;
    collect_labels_and_stats(a);
    return a;
}

}  // namespace p3fes::recomp
