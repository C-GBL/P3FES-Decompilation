#include "emit_program.h"

#include "elf_image.h"
#include "emit_analyze.h"
#include "json_lite.h"

#include <algorithm>
#include <cstring>

namespace p3fes::recomp {

std::optional<std::uint32_t> ElfWordSource::word_at(std::uint32_t va) const noexcept {
    return elf.word_at(va);
}

std::optional<std::uint32_t> VectorWordSource::word_at(std::uint32_t va) const noexcept {
    if (va < base || (va & 3u) != 0) return std::nullopt;
    const std::uint32_t idx = (va - base) / 4u;
    if (idx >= words.size()) return std::nullopt;
    return words[idx];
}

std::uint8_t gpr_index_from_name(const std::string& name) noexcept {
    static const char* const kNames[32] = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra",
    };
    for (std::uint8_t i = 0; i < 32; ++i)
        if (name == kNames[i]) return i;
    // IDA's EE module names $a4..$a7 / $t0..$t3 for registers 8..11 in some configurations.
    static const char* const kAlt[4] = {"$a4", "$a5", "$a6", "$a7"};
    for (std::uint8_t i = 0; i < 4; ++i)
        if (name == kAlt[i]) return static_cast<std::uint8_t>(8 + i);
    if (name == "$s8") return 30;
    return 0xFF;
}

const char* SwitchTables::load_json(const std::string& text) {
    json::ParseResult pr = json::Parser::parse(text);
    if (pr.error) return pr.error;
    const json::Value* resolved = pr.value.get("resolved");
    const json::Value* unresolved = pr.value.get("unresolved");
    if (!resolved || !resolved->is_array()) return "jumptables.json: missing resolved[]";
    if (!unresolved || !unresolved->is_array()) return "jumptables.json: missing unresolved[]";
    by_jr.clear();
    unresolved_jr.clear();
    total_cases = 0;
    for (const json::Value& e : resolved->items) {
        const json::Value* jr = e.get("jr_ea");
        const json::Value* fn = e.get("func_ea");
        const json::Value* reg = e.get("reg");
        const json::Value* table = e.get("table_ea");
        const json::Value* def = e.get("default_ea");
        const json::Value* targets = e.get("targets");
        const json::Value* cases = e.get("cases");
        const json::Value* elem = e.get("elem_size");
        std::uint64_t jr_v = 0, fn_v = 0, table_v = 0, def_v = 0, elem_v = 0;
        if (!jr || !fn || !reg || !table || !targets || !jr->to_u64(jr_v) || !fn->to_u64(fn_v) ||
            !table->to_u64(table_v) || !reg->is_string() || !targets->is_array())
            return "jumptables.json: resolved entry without jr_ea/func_ea/reg/table_ea/targets";
        if (def && !def->is_null() && !def->to_u64(def_v)) return "jumptables.json: bad default_ea";
        if (elem && elem->to_u64(elem_v) && elem_v != 4) return "jumptables.json: only 4-byte table elements are supported";
        SwitchSite s;
        s.jr_ea = static_cast<std::uint32_t>(jr_v);
        s.func_ea = static_cast<std::uint32_t>(fn_v);
        s.table_ea = static_cast<std::uint32_t>(table_v);
        s.default_ea = static_cast<std::uint32_t>(def_v);
        s.reg = gpr_index_from_name(reg->str);
        if (s.reg > 31) return "jumptables.json: unknown register name in resolved entry";
        for (const json::Value& t : targets->items) {
            std::uint64_t tv = 0;
            if (!t.to_u64(tv)) return "jumptables.json: bad target";
            s.targets.push_back(static_cast<std::uint32_t>(tv));
        }
        std::sort(s.targets.begin(), s.targets.end());
        s.targets.erase(std::unique(s.targets.begin(), s.targets.end()), s.targets.end());
        if (cases && cases->is_array()) total_cases += cases->items.size();
        by_jr[s.jr_ea] = std::move(s);
    }
    for (const json::Value& e : unresolved->items) {
        const json::Value* jr = e.get("jr_ea");
        std::uint64_t jr_v = 0;
        if (!jr || !jr->to_u64(jr_v)) return "jumptables.json: unresolved entry without jr_ea";
        unresolved_jr.insert(static_cast<std::uint32_t>(jr_v));
    }
    return nullptr;
}

Program::Program(const FunctionList& fl, const WordSource& words, const SwitchTables& switches)
    : fl_(fl), words_(words), switches_(switches) {
    for (std::size_t i = 0; i < fl.functions.size(); ++i) {
        const Function& f = fl.functions[i];
        if (f.chunks.empty()) {
            ranges_.push_back({f.start, f.start + f.size, static_cast<std::uint32_t>(i), 0});
        } else {
            for (const Range& r : f.chunks) ranges_.push_back({r.start, r.end, static_cast<std::uint32_t>(i), 0});
        }
    }
    std::sort(ranges_.begin(), ranges_.end(), [](const OwnedRange& a, const OwnedRange& b) {
        return a.start != b.start ? a.start < b.start : a.fn_index < b.fn_index;
    });
    std::uint32_t m = 0;
    for (OwnedRange& r : ranges_) {
        m = std::max(m, r.end);
        r.max_end_so_far = m;
    }
}

bool Program::contains(const Function& f, std::uint32_t va) noexcept {
    if (f.chunks.empty()) return va >= f.start && va < f.start + f.size;
    for (const Range& r : f.chunks)
        if (va >= r.start && va < r.end) return true;
    return false;
}

const Function* Program::owner_of(std::uint32_t va) const noexcept {
    // Last range with start <= va, then walk backwards while some earlier range may still reach va.
    auto it = std::upper_bound(ranges_.begin(), ranges_.end(), va,
                               [](std::uint32_t v, const OwnedRange& r) { return v < r.start; });
    const Function* best = nullptr;
    while (it != ranges_.begin()) {
        --it;
        if (it->max_end_so_far <= va) break;
        if (va >= it->start && va < it->end) {
            const Function* f = &fl_.functions[it->fn_index];
            if (!best || f->start < best->start) best = f;
        }
    }
    return best;
}

const std::set<std::uint32_t>& Program::entries_of(const Function& f) const noexcept {
    static const std::set<std::uint32_t> kNone;
    auto it = entries_.find(f.start);
    return it == entries_.end() ? kNone : it->second;
}

std::size_t Program::entry_count() const noexcept {
    std::size_t n = 0;
    for (const auto& [start, set] : entries_) n += set.size();
    return n;
}

void Program::compute_entries_and_returns(std::vector<std::pair<std::uint32_t, std::uint32_t>>* unowned) {
    entries_.clear();
    returns_.clear();
    // Who may need re-analysis when a root starts returning: every function with a call or tail
    // edge to it, live or not (a superset is enough; it only schedules work).
    std::unordered_map<std::uint32_t, std::vector<const Function*>> callers;
    std::vector<const Function*> todo;
    for (const Function& f : fl_.functions) {
        todo.push_back(&f);
        const FunctionAnalysis a = analyze_function(*this, f);
        auto add = [&](const Edge& e) {
            if (e.kind == EdgeKind::CallFunc || e.kind == EdgeKind::CallEntry || e.kind == EdgeKind::TailFunc ||
                e.kind == EdgeKind::TailEntry)
                callers[e.target].push_back(&f);
        };
        for (const ChunkAnalysis& c : a.chunks) {
            for (const Item& it : c.items) {
                if (!it.is_cf) continue;
                add(it.edge);
                for (const Edge& e : it.sw_edges) add(e);
            }
            add(c.end_edge);
        }
    }
    for (auto& [root, v] : callers) {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
    while (!todo.empty()) {
        std::set<const Function*, bool (*)(const Function*, const Function*)> again(
            [](const Function* x, const Function* y) { return x->start < y->start; });
        for (const Function* f : todo) {
            const FunctionAnalysis a = analyze_function(*this, *f);
            for (const auto& [root, ret] : a.root_returns) {
                if (!ret || !returns_.insert(root).second) continue;
                auto c = callers.find(root);
                if (c != callers.end()) again.insert(c->second.begin(), c->second.end());
            }
            auto note = [&](const Edge& e) {
                if ((e.kind == EdgeKind::CallEntry || e.kind == EdgeKind::TailEntry) && e.fn &&
                    entries_[e.fn->start].insert(e.target).second)
                    again.insert(e.fn);
            };
            for (const ChunkAnalysis& c : a.chunks) {
                for (const Item& it : c.items) {
                    if (!it.reachable || !it.is_cf) continue;
                    note(it.edge);
                    for (const Edge& e : it.sw_edges) note(e);
                }
                if (c.end_reachable) note(c.end_edge);
            }
        }
        todo.assign(again.begin(), again.end());
    }
    for (auto it = entries_.begin(); it != entries_.end();) {
        if (it->second.empty()) it = entries_.erase(it);
        else ++it;
    }
    if (unowned) {
        unowned->clear();
        for (const Function& f : fl_.functions) {
            const FunctionAnalysis a = analyze_function(*this, f);
            for (const ChunkAnalysis& c : a.chunks)
                for (const Item& it : c.items) {
                    if (!it.reachable || !it.is_cf) continue;
                    if (it.edge.kind == EdgeKind::Unowned) unowned->emplace_back(it.pc, it.edge.target);
                    for (const Edge& e : it.sw_edges)
                        if (e.kind == EdgeKind::Unowned) unowned->emplace_back(it.pc, e.target);
                }
        }
    }
}

}  // namespace p3fes::recomp
