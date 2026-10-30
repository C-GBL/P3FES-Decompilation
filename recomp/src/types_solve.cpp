// p3fes_types phase 2: union-find over the type variables, with layout and anchor vetoes; JSON output (types.h).
#include "types.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace p3fes::recomp::types {

namespace {

struct FieldSum {
    std::uint8_t widths = 0;  // bit0 1, bit1 2, bit2 4, bit3 8, bit4 16
    std::uint8_t kinds = 0;
};

std::uint8_t wbit(std::uint8_t w) {
    switch (w) {
    case 1: return 1;
    case 2: return 2;
    case 4: return 4;
    case 8: return 8;
    default: return 16;
    }
}

struct Cls {
    std::map<std::int32_t, FieldSum> sum;           // fixed-offset accesses (veto + evidence)
    std::unordered_map<std::int32_t, std::uint32_t> deref;  // field offset -> pointee tv
    std::vector<std::uint32_t> code;                 // code objects (function starts), capped
    std::set<std::int32_t> poly;                     // fields whose pointee merge was vetoed
    int anchor = -1;
    std::uint32_t members = 1;
    bool has_global = false;                         // contains a GSlot/GObj tv
};

class Solver {
public:
    Solver(Facts& f, const SolveOptions& opt, SolveStats& st) : f_(f), opt_(opt), st_(st) {
        const std::size_t n = f_.tvs.size();
        parent_.resize(n);
        for (std::size_t i = 0; i < n; ++i) parent_[i] = static_cast<std::uint32_t>(i);
        cls_.resize(n);
        for (std::size_t i = 0; i < n; ++i) {
            const Tv& t = f_.tvs[i];
            if (t.kind == TvKind::Code && i != 0) cls_[i].code.push_back(t.a);
            if (t.kind == TvKind::GSlot || t.kind == TvKind::GObj) cls_[i].has_global = true;
        }
        for (const Access& a : f_.accesses) {
            if (a.stride != 0) continue;
            FieldSum& s = cls_[a.tv].sum[a.off];
            s.widths |= wbit(a.width);
            s.kinds |= a.kind;
        }
    }

    std::uint32_t find(std::uint32_t x) {
        while (parent_[x] != x) {
            parent_[x] = parent_[parent_[x]];
            x = parent_[x];
        }
        return x;
    }

    // Conflicting offsets between two summaries (exact offset, integer widths 1/2/4 only, disjoint).
    // Integer width of a field summary when it is accessed only as 1/2/4-byte integers or floats (0 when 8- or
    // 16-byte accesses copy it: struct copies say nothing about the layout).
    static int plain_width(const FieldSum& f) {
        if (f.widths & 24) return 0;
        if (f.widths & 4) return 4;
        if (f.widths & 2) return 2;
        if (f.widths & 1) return 1;
        return 0;
    }

    // Conflicting offsets between two summaries: the same offset accessed with disjoint integer widths, a float
    // against a sub-word integer, or an access starting inside another one's bytes (a u8 at +0x11 against a u32 at
    // +0x10). `common` receives the number of offsets both summaries access.
    static int conflicts(const std::map<std::int32_t, FieldSum>& a, const std::map<std::int32_t, FieldSum>& b,
                         int* common) {
        const auto& small = a.size() <= b.size() ? a : b;
        const auto& large = a.size() <= b.size() ? b : a;
        int c = 0, k = 0;
        for (const auto& [off, fs] : small) {
            const int ws = plain_width(fs);
            auto it = large.find(off);
            if (it != large.end()) {
                ++k;
                const std::uint8_t wa = fs.widths & 7, wb = it->second.widths & 7;
                const int wl = plain_width(it->second);
                if (ws && wl && (wa & wb) == 0) { ++c; continue; }
                const bool fa = (fs.kinds & kKFloat) != 0, fb = (it->second.kinds & kKFloat) != 0;
                if ((fa && wl && wl < 4) || (fb && ws && ws < 4)) { ++c; continue; }
            }
            if (!ws) continue;
            // an access of `large` starting inside this one's bytes
            bool overlap = false;
            for (auto j = large.upper_bound(off); j != large.end() && j->first < off + ws; ++j)
                if (plain_width(j->second)) { overlap = true; break; }
            // this access starting inside an access of `large`
            if (!overlap) {
                auto j = large.lower_bound(off);
                for (int n = 0; n < 3 && j != large.begin(); ++n) {
                    --j;
                    const int wj = plain_width(j->second);
                    if (wj && j->first + wj > off) { overlap = true; break; }
                }
            }
            if (overlap) ++c;
        }
        if (common) *common = k;
        return c;
    }

    // Two layouts agree when nothing conflicts, or when a few odd accesses sit among many agreeing offsets (a union
    // member, a byte of a flag word).
    bool agree(int c, int common) const { return c == 0 || (c <= opt_.max_conflicts && common >= 10 * c); }

    bool compatible(std::uint32_t ra, std::uint32_t rb, bool* anchor_clash) {
        const Cls& A = cls_[ra];
        const Cls& B = cls_[rb];
        *anchor_clash = false;
        if (A.anchor >= 0 && B.anchor >= 0 && A.anchor != B.anchor) {
            *anchor_clash = true;
            return false;
        }
        // a record of documented size never gains an access at or past its end (or before its start)
        if ((A.anchor >= 0 && outside(A, B)) || (B.anchor >= 0 && outside(B, A))) {
            *anchor_clash = true;
            return false;
        }
        // code objects never merge with data objects that have fields
        if ((!A.code.empty() && !B.sum.empty()) || (!B.code.empty() && !A.sum.empty())) return false;
        int common = 0;
        const int c = conflicts(A.sum, B.sum, &common);
        return agree(c, common);
    }

    bool outside(const Cls& an, const Cls& other) const {
        const std::uint32_t size = anchor_size_[static_cast<std::size_t>(an.anchor)];
        if (!size || other.sum.empty()) return false;
        const auto& last = *other.sum.rbegin();
        int w = 1;
        for (int b = 4; b >= 0; --b)
            if (last.second.widths & (1 << b)) { w = 1 << b; break; }
        if (w > 4) w = 1;  // a struct copy may run past a field
        return other.sum.begin()->first < 0 || last.first + w > static_cast<std::int32_t>(size);
    }

    // Unify two type variables; returns false when the top-level merge was vetoed.
    bool unify(std::uint32_t x, std::uint32_t y, bool veto) {
        struct Pending {
            std::uint32_t a, b;
            std::uint32_t ctx_rep;  // class whose field is being merged (for poly marking), or ~0
            std::int32_t ctx_off;
        };
        std::vector<Pending> work{{x, y, ~0u, 0}};
        bool top_ok = true;
        bool first = true;
        while (!work.empty()) {
            const Pending p = work.back();
            work.pop_back();
            std::uint32_t ra = find(p.a), rb = find(p.b);
            const bool is_top = first;
            first = false;
            if (ra == rb) continue;
            bool clash = false;
            const bool ok = compatible(ra, rb, &clash);
            if (!ok && (veto || clash)) {
                ++st_.vetoes;
                if (clash) ++st_.vetoes_anchor;
                if (is_top) top_ok = false;
                if (p.ctx_rep != ~0u) cls_[find(p.ctx_rep)].poly.insert(p.ctx_off);
                continue;
            }
            ++st_.unions;
            if (debug_ && cls_[ra].members >= 100 && cls_[rb].members >= 100)
                std::fprintf(stderr, "big merge [%s] %u + %u (fields %zu + %zu) ctx_off=%d cur_pc=0x%X\n", cur_kind_,
                             cls_[ra].members, cls_[rb].members, cls_[ra].sum.size(), cls_[rb].sum.size(),
                             p.ctx_rep == ~0u ? -1 : p.ctx_off, cur_pc_);
            if (debug_ && (cls_[ra].anchor >= 0) != (cls_[rb].anchor >= 0)) {
                const Cls& an = cls_[ra].anchor >= 0 ? cls_[ra] : cls_[rb];
                const Cls& ot = cls_[ra].anchor >= 0 ? cls_[rb] : cls_[ra];
                if (ot.sum.size() >= 4)
                    std::fprintf(stderr, "anchored merge [%s] %s(+%zu fields) <- %zu fields, %u members ctx_off=%d at 0x%X\n",
                                 cur_kind_, opt_.anchors[static_cast<std::size_t>(an.anchor)].name.c_str(), an.sum.size(),
                                 ot.sum.size(), ot.members, p.ctx_rep == ~0u ? -1 : p.ctx_off, cur_pc_);
            }
            if (cls_[ra].members < cls_[rb].members) std::swap(ra, rb);
            parent_[rb] = ra;
            Cls& A = cls_[ra];
            Cls& B = cls_[rb];
            A.members += B.members;
            A.has_global = A.has_global || B.has_global;
            if (A.anchor < 0) A.anchor = B.anchor;
            for (const auto& [off, fs] : B.sum) {
                FieldSum& d = A.sum[off];
                d.widths |= fs.widths;
                d.kinds |= fs.kinds;
            }
            for (std::uint32_t c : B.code)
                if (A.code.size() < 256 && std::find(A.code.begin(), A.code.end(), c) == A.code.end()) A.code.push_back(c);
            for (std::int32_t o : B.poly) A.poly.insert(o);
            for (const auto& [off, tv] : B.deref) {
                auto it = A.deref.find(off);
                if (it == A.deref.end()) A.deref.emplace(off, tv);
                else work.push_back({it->second, tv, ra, off});
            }
            B.sum.clear();
            B.deref.clear();
            B.code.clear();
            B.poly.clear();
        }
        return top_ok;
    }

    bool evidence(std::uint32_t r) {
        const Cls& c = cls_[r];
        return !c.sum.empty() || c.anchor >= 0 || !c.code.empty();
    }

    void run() {
        // 0. anchors (several anchors of one record share its id: the first line naming it)
        std::map<std::string, int> first_of;
        for (std::size_t i = 0; i < opt_.anchors.size(); ++i) first_of.emplace(opt_.anchors[i].name, static_cast<int>(i));
        anchor_size_.assign(opt_.anchors.size(), 0);
        for (std::size_t i = 0; i < opt_.anchors.size(); ++i) {
            auto it = opt_.sizes.find(opt_.anchors[i].name);
            if (it != opt_.sizes.end()) anchor_size_[i] = it->second;
        }
        for (std::size_t i = 0; i < opt_.anchors.size(); ++i) {
            const Anchor& an = opt_.anchors[i];
            const int id = first_of[an.name];
            std::uint32_t tv = 0;
            if (an.how == "param") tv = f_.param_tv(an.addr, an.index);
            else if (an.how == "ret") tv = f_.ret_tv(an.addr);
            else if (an.how == "gslot") tv = f_.gslot_tv(an.addr);
            else if (an.how == "gobj") tv = f_.gobj_tv(an.addr);
            grow();
            if (!tv) continue;
            const std::uint32_t r = find(tv);
            if (cls_[r].anchor >= 0 && cls_[r].anchor != id) {
                std::fprintf(stderr, "p3fes_types: anchor %s lands on a class already anchored as %s\n", an.name.c_str(),
                             opt_.anchors[static_cast<std::size_t>(cls_[r].anchor)].name.c_str());
                continue;
            }
            if (cls_[r].anchor < 0) ++st_.anchors_applied;
            cls_[r].anchor = id;
        }
        // 1. joins inside a function: the same register value (anchor clashes still veto)
        cur_kind_ = "join";
        for (const Constraint& c : f_.cons)
            if (c.kind == CKind::Join) { cur_pc_ = c.fn; unify(c.a, c.b, false); }
        // 2. field derefs: loads of one field of one class have one pointee type
        cur_kind_ = "deref";
        for (const Constraint& c : f_.cons) {
            if (c.kind != CKind::Deref) continue;
            cur_pc_ = c.fn;
            const Tv& d = f_.tvs[c.a];
            const std::uint32_t r = find(d.a);
            const std::int32_t off = static_cast<std::int32_t>(d.b);
            auto it = cls_[r].deref.find(off);
            if (it == cls_[r].deref.end()) cls_[r].deref.emplace(off, c.a);
            else if (!unify(it->second, c.a, true)) cls_[find(d.a)].poly.insert(off);
        }
        // 3. pointer stores into fields / global slots
        cur_kind_ = "store";
        for (const Constraint& c : f_.cons)
            if (c.kind == CKind::Store) { cur_pc_ = c.pc; unify(c.a, c.b, true); }
        // 4. returns inside each function: what leaves in $v0
        cur_kind_ = "return";
        for (const Constraint& c : f_.cons)
            if (c.kind == CKind::Return && f_.tvs[c.a].kind != TvKind::Ret) { cur_pc_ = c.pc; unify(c.a, c.b, true); }
        // 5. call arguments, through parameters with evidence that are not polymorphic
        cur_kind_ = "arg";
        link_through(CKind::Arg);
        // 6. tail-call returns, then call results through returns with evidence
        for (const Constraint& c : f_.cons)
            if (c.kind == CKind::Return && f_.tvs[c.a].kind == TvKind::Ret) unify(c.a, c.b, true);
        cur_kind_ = "result";
        link_through(CKind::Result);
        // 7. calls through function-pointer fields whose stored callbacks are known
        cur_kind_ = "icall";
        for (int round = 0; round < 2; ++round) {
            for (const Constraint& c : f_.cons) {
                if (c.kind != CKind::ICall) continue;
                const std::uint32_t r = find(c.a);
                if (cls_[r].code.empty() || cls_[r].code.size() > 64) continue;
                // Only the "self" pattern links: obj->fn(..., obj, ...) -- an argument of the class the function
                // pointer was loaded from (task->update(task), a state table's handler(ctx)). Other arguments of a
                // callback (user data) are as polymorphic as the callbacks stored in the field.
                const Tv& called = f_.tvs[c.a];
                if (called.kind != TvKind::Deref || called.b == 0xFFFFFFFFu || called.a == 0) continue;
                const std::uint32_t self_cls = find(called.a);
                const std::vector<std::uint32_t> targets = cls_[r].code;
                const auto& args = f_.icall_args[static_cast<std::size_t>(c.c)];
                for (std::uint32_t fnaddr : targets) {
                    for (std::uint32_t i = 0; i < 8; ++i) {
                        if (!args[i] || find(args[i]) != self_cls) continue;
                        const std::uint32_t pt = f_.param_tv(fnaddr, i);
                        grow();
                        if (!evidence(find(pt))) continue;
                        cur_pc_ = fnaddr;
                        if (unify(args[i], pt, true) && round == 0) ++st_.icall_resolved;
                    }
                }
            }
        }
    }

    // Args (value -> callee param) or Results (call result <- callee Ret): group by the callee-side tv, drop
    // callee sides without evidence, and callee sides whose caller-side classes conflict among themselves
    // (a polymorphic parameter / return: memcpy, free, a void* getter).
    void link_through(CKind kind) {
        if (kind == CKind::Result) {
            for (const Constraint& c : f_.cons) {
                if (c.kind != CKind::Return) continue;
                const Tv& t = f_.tvs[c.a];
                if (t.kind == TvKind::Deref && t.b != 0xFFFFFFFFu && f_.tvs[t.a].kind == TvKind::Param)
                    field_getters_.insert(c.b);
            }
        }
        std::unordered_map<std::uint32_t, std::vector<std::uint32_t>> by_callee;  // callee tv -> caller tvs
        for (const Constraint& c : f_.cons) {
            if (c.kind != kind) continue;
            by_callee[c.b].push_back(c.a);
        }
        std::vector<std::uint32_t> keys;
        keys.reserve(by_callee.size());
        for (const auto& kv : by_callee) keys.push_back(kv.first);
        std::sort(keys.begin(), keys.end());
        for (std::uint32_t callee : keys) {
            const std::uint32_t rc = find(callee);
            bool ev = kind == CKind::Arg ? evidence(rc) : (evidence(rc) || cls_[rc].has_global);
            // A function that returns a pointer field of its own parameter (a getter: kwlnTaskGetWorkData) hands
            // out whatever its callers stored there; its callers' results are never linked through it.
            if (kind == CKind::Result && field_getters_.count(callee)) ev = false;
            if (!ev) {
                st_.args_no_evidence += by_callee[callee].size();
                continue;
            }
            // polymorphism check among the caller-side classes that carry fields
            std::map<std::int32_t, FieldSum> acc;
            int anchor = -1;
            bool poly = false;
            std::set<std::uint32_t> seen;
            for (std::uint32_t a : by_callee[callee]) {
                const std::uint32_t ra = find(a);
                if (!seen.insert(ra).second) continue;
                const Cls& c = cls_[ra];
                if (c.anchor >= 0) {
                    if (anchor >= 0 && anchor != c.anchor) { poly = true; break; }
                    anchor = c.anchor;
                }
                if (c.sum.empty()) continue;
                int common = 0;
                const int k = conflicts(acc, c.sum, &common);
                if (!agree(k, common)) { poly = true; break; }
                for (const auto& [off, fs] : c.sum) {
                    FieldSum& d = acc[off];
                    d.widths |= fs.widths;
                    d.kinds |= fs.kinds;
                }
            }
            if (poly) {
                polymorphic_.insert(callee);
                continue;
            }
            cur_pc_ = f_.tvs[callee].a;
            for (std::uint32_t a : by_callee[callee]) unify(a, callee, true);
        }
    }

    void grow() {  // tvs created after construction (anchors / icall params)
        const std::size_t n = f_.tvs.size();
        while (parent_.size() < n) {
            parent_.push_back(static_cast<std::uint32_t>(parent_.size()));
            cls_.emplace_back();
            const Tv& t = f_.tvs[parent_.size() - 1];
            if (t.kind == TvKind::Code) cls_.back().code.push_back(t.a);
            if (t.kind == TvKind::GSlot || t.kind == TvKind::GObj) cls_.back().has_global = true;
        }
    }

    bool debug_ = std::getenv("P3FES_TYPES_DEBUG") != nullptr;
    const char* cur_kind_ = "";
    std::uint32_t cur_pc_ = 0;
    Facts& f_;
    const SolveOptions& opt_;
    SolveStats& st_;
    std::vector<std::uint32_t> parent_;
    std::vector<Cls> cls_;
    std::unordered_set<std::uint32_t> polymorphic_;
    std::vector<std::uint32_t> anchor_size_;  // per anchor line (documented size, 0 = unknown)
    std::unordered_set<std::uint32_t> field_getters_;  // Ret tvs of functions returning a field of a parameter
};

// --- JSON output ---------------------------------------------------------------------------------------------------

std::string hex(std::uint32_t v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%X", v);
    return b;
}

std::string kinds_str(std::uint8_t k) {
    std::string s;
    if (k & kKSigned) s += 's';
    if (k & kKUnsigned) s += 'u';
    if (k & kKFloat) s += 'f';
    if (k & kKVector) s += 'v';
    if (k & kKInt128) s += 'q';
    if (k & kKInt64) s += 'd';
    return s;
}

std::string widths_str(std::uint8_t w) {
    std::string s = "[";
    bool first = true;
    for (int i = 0; i < 5; ++i)
        if (w & (1 << i)) {
            if (!first) s += ',';
            s += std::to_string(1 << i);
            first = false;
        }
    return s + "]";
}

struct FieldOut {
    std::uint8_t widths = 0, kinds = 0;
    std::uint32_t loads = 0, stores = 0;
    std::vector<std::uint32_t> fns;  // distinct accessor functions (sorted later)
    std::vector<std::uint32_t> pcs;  // first few access pcs
};

void add_fn(std::vector<std::uint32_t>& v, std::uint32_t f) {
    if (v.size() < 4096 && std::find(v.begin(), v.end(), f) == v.end()) v.push_back(f);
}

}  // namespace

bool solve_and_write(const Program& prog, Facts& facts, const SolveOptions& opt, SolveStats& st,
                     const std::string& out_path, const AnalyzeStats& ast, double phase1_seconds) {
    Solver s(facts, opt, st);
    s.run();
    s.grow();

    // Per-class fields (fixed and indexed).
    std::unordered_map<std::uint32_t, std::map<std::int32_t, FieldOut>> fixed;
    std::unordered_map<std::uint32_t, std::map<std::pair<std::int32_t, std::int32_t>, FieldOut>> indexed;
    for (const Access& a : facts.accesses) {
        const std::uint32_t r = s.find(a.tv);
        FieldOut& fo = a.stride == 0 ? fixed[r][a.off] : indexed[r][{a.stride, a.off}];
        fo.widths |= wbit(a.width);
        fo.kinds |= static_cast<std::uint8_t>(a.kind & ~kKStore);
        if (a.kind & kKStore) ++fo.stores; else ++fo.loads;
        add_fn(fo.fns, a.fn);
        if (fo.pcs.size() < 4) fo.pcs.push_back(a.pc);
    }
    // Which classes are called (jalr through a value of the class).
    std::unordered_set<std::uint32_t> called;
    for (const Constraint& c : facts.cons)
        if (c.kind == CKind::ICall) called.insert(s.find(c.a));
    // Embedded sub-objects: pointer to (X + off) passed where class P is expected.
    std::map<std::uint32_t, std::set<std::pair<std::int32_t, std::uint32_t>>> embeds;
    for (const Constraint& c : facts.cons)
        if (c.kind == CKind::Embed) embeds[s.find(c.a)].insert({c.c, s.find(c.b)});

    // Members per class.
    struct Members {
        std::vector<std::pair<std::uint32_t, std::uint32_t>> params;
        std::vector<std::uint32_t> rets, gslots, gobjs;
        std::uint32_t nparams = 0, nstack = 0, nderef = 0, ncallres = 0;
    };
    std::unordered_map<std::uint32_t, Members> members;
    for (std::uint32_t i = 1; i < facts.tvs.size(); ++i) {
        const Tv& t = facts.tvs[i];
        const std::uint32_t r = s.find(i);
        switch (t.kind) {
        case TvKind::Param: {
            auto& m = members[r];
            ++m.nparams;
            m.params.push_back({t.a, t.b});
            break;
        }
        case TvKind::Ret: members[r].rets.push_back(t.a); break;
        case TvKind::GSlot: members[r].gslots.push_back(t.a); break;
        case TvKind::GObj: members[r].gobjs.push_back(t.a); break;
        case TvKind::Stack: ++members[r].nstack; break;
        case TvKind::Deref: ++members[r].nderef; break;
        case TvKind::CallRes: ++members[r].ncallres; break;
        default: break;
        }
    }

    // Which classes are emitted: fields, an anchor, code, or the pointee of an emitted field.
    auto interesting = [&](std::uint32_t r) {
        const Cls& c = s.cls_[r];
        return fixed.count(r) || indexed.count(r) || c.anchor >= 0 || !c.code.empty();
    };
    std::vector<std::uint32_t> reps;
    std::unordered_map<std::uint32_t, std::uint32_t> cid;  // rep -> output id
    for (std::uint32_t i = 1; i < facts.tvs.size(); ++i)
        if (s.find(i) == i && interesting(i)) reps.push_back(i);
    // stable ids: order by (anchor first, then field count desc, then rep)
    std::sort(reps.begin(), reps.end(), [&](std::uint32_t a, std::uint32_t b) {
        const std::size_t fa = fixed.count(a) ? fixed[a].size() : 0, fb = fixed.count(b) ? fixed[b].size() : 0;
        if (fa != fb) return fa > fb;
        return a < b;
    });
    for (std::size_t i = 0; i < reps.size(); ++i) cid[reps[i]] = static_cast<std::uint32_t>(i + 1);
    auto cls_ref = [&](std::uint32_t tv) -> std::string {
        const std::uint32_t r = s.find(tv);
        auto it = cid.find(r);
        return it == cid.end() ? "null" : std::to_string(it->second);
    };

    std::FILE* out = std::fopen(out_path.c_str(), "wb");
    if (!out) return false;
    std::fprintf(out, "{\n\"tool\": \"p3fes_types\",\n\"stats\": {\"functions\": %zu, \"analysed\": %zu, \"skipped\": %zu, "
                      "\"instructions\": %zu, \"node_visits\": %zu, \"type_vars\": %zu, \"accesses\": %zu, "
                      "\"global_accesses\": %zu, \"constraints\": %zu, \"unions\": %zu, \"vetoes\": %zu, "
                      "\"vetoes_anchor\": %zu, \"links_without_evidence\": %zu, \"polymorphic_links\": %zu, "
                      "\"icall_param_links\": %zu, \"anchors_applied\": %zu, \"classes\": %zu, \"phase1_s\": %.2f},\n",
                 ast.functions, ast.analysed, ast.skipped, ast.instructions, ast.iterations, facts.tvs.size(),
                 facts.accesses.size(), facts.gaccesses.size(), facts.cons.size(), st.unions, st.vetoes,
                 st.vetoes_anchor, st.args_no_evidence, s.polymorphic_.size(), st.icall_resolved, st.anchors_applied,
                 reps.size(), phase1_seconds);
    std::fputs("\"anchors\": [", out);
    for (std::size_t i = 0; i < opt.anchors.size(); ++i) {
        const Anchor& a = opt.anchors[i];
        std::uint32_t tv = 0;
        if (a.how == "param") tv = facts.param_tv(a.addr, a.index);
        else if (a.how == "ret") tv = facts.ret_tv(a.addr);
        else if (a.how == "gslot") tv = facts.gslot_tv(a.addr);
        else if (a.how == "gobj") tv = facts.gobj_tv(a.addr);
        s.grow();
        std::fprintf(out, "%s\n {\"name\": \"%s\", \"how\": \"%s\", \"addr\": \"%s\", \"index\": %u, \"class\": %s}",
                     i ? "," : "", a.name.c_str(), a.how.c_str(), hex(a.addr).c_str(), a.index,
                     tv ? cls_ref(tv).c_str() : "null");
    }
    std::fputs("],\n\"classes\": [", out);
    auto write_fns = [&](std::vector<std::uint32_t> v, std::size_t cap) {
        std::sort(v.begin(), v.end());
        std::string o = "[";
        for (std::size_t i = 0; i < v.size() && i < cap; ++i) o += (i ? ",\"" : "\"") + hex(v[i]) + "\"";
        return o + "]";
    };
    for (std::size_t i = 0; i < reps.size(); ++i) {
        const std::uint32_t r = reps[i];
        const Cls& c = s.cls_[r];
        const Members& m = members[r];
        std::fprintf(out, "%s\n{\"id\": %zu, \"anchor\": %s", i ? "," : "", i + 1,
                     c.anchor >= 0 ? ("\"" + opt.anchors[static_cast<std::size_t>(c.anchor)].name + "\"").c_str() : "null");
        // size lower bound
        std::int64_t size = 0;
        if (fixed.count(r))
            for (const auto& [off, fo] : fixed[r]) {
                std::int32_t w = 1;
                for (int b = 4; b >= 0; --b)
                    if (fo.widths & (1 << b)) { w = 1 << b; break; }
                size = std::max<std::int64_t>(size, static_cast<std::int64_t>(off) + w);
            }
        std::fprintf(out, ", \"size_min\": %lld, \"called\": %s, \"n_members\": %u", static_cast<long long>(size),
                     called.count(r) ? "true" : "false", c.members);
        // members
        std::string ps = "[";
        auto params = m.params;
        std::sort(params.begin(), params.end());
        for (std::size_t k = 0; k < params.size() && k < 400; ++k)
            ps += (k ? ",[\"" : "[\"") + hex(params[k].first) + "\"," + std::to_string(params[k].second) + "]";
        ps += "]";
        std::fprintf(out, ", \"params\": %s, \"n_params\": %u, \"rets\": %s, \"gslots\": %s, \"gobjs\": %s, "
                          "\"n_stack\": %u, \"n_deref\": %u, \"n_callres\": %u",
                     ps.c_str(), m.nparams, write_fns(m.rets, 200).c_str(), write_fns(m.gslots, 200).c_str(),
                     write_fns(m.gobjs, 200).c_str(), m.nstack, m.nderef, m.ncallres);
        std::fprintf(out, ", \"code\": %s", write_fns(c.code, 256).c_str());
        // fields
        std::fputs(", \"fields\": [", out);
        bool first = true;
        if (fixed.count(r)) {
            for (const auto& [off, fo] : fixed[r]) {
                std::string ptr = "null";
                bool fcalled = false;
                bool fcode = false;
                auto dit = c.deref.find(off);
                if (dit != c.deref.end()) {
                    const std::uint32_t pr = s.find(dit->second);
                    ptr = cls_ref(dit->second);
                    fcalled = called.count(pr) != 0;
                    fcode = !s.cls_[pr].code.empty();
                }
                std::fprintf(out, "%s\n {\"off\": %d, \"w\": %s, \"k\": \"%s\", \"ld\": %u, \"st\": %u, \"n_fns\": %zu, "
                                  "\"fns\": %s, \"ptr\": %s, \"poly\": %s, \"called\": %s, \"code\": %s}",
                             first ? "" : ",", off, widths_str(fo.widths).c_str(), kinds_str(fo.kinds).c_str(), fo.loads,
                             fo.stores, fo.fns.size(), write_fns(fo.fns, 8).c_str(), ptr.c_str(),
                             c.poly.count(off) ? "true" : "false", fcalled ? "true" : "false", fcode ? "true" : "false");
                first = false;
            }
        }
        std::fputs("], \"arrays\": [", out);
        first = true;
        if (indexed.count(r)) {
            for (const auto& [key, fo] : indexed[r]) {
                std::fprintf(out, "%s\n {\"stride\": %d, \"off\": %d, \"w\": %s, \"k\": \"%s\", \"ld\": %u, \"st\": %u, "
                                  "\"n_fns\": %zu, \"fns\": %s}",
                             first ? "" : ",", key.first, key.second, widths_str(fo.widths).c_str(),
                             kinds_str(fo.kinds).c_str(), fo.loads, fo.stores, fo.fns.size(), write_fns(fo.fns, 4).c_str());
                first = false;
            }
        }
        std::fputs("], \"embeds\": [", out);
        first = true;
        if (embeds.count(r)) {
            for (const auto& [off, pr] : embeds[r]) {
                auto it = cid.find(pr);
                if (it == cid.end()) continue;
                std::fprintf(out, "%s{\"off\": %d, \"class\": %u}", first ? "" : ",", off, it->second);
                first = false;
            }
        }
        std::fputs("]}", out);
    }
    // functions: parameter / return classes
    std::fputs("\n],\n\"functions\": {", out);
    bool firstf = true;
    for (const Function& fn : prog.functions().functions) {
        std::string ps;
        int last = -1;
        std::string items[8];
        for (std::uint32_t i = 0; i < 8; ++i) {
            auto it = facts.param.find((static_cast<std::uint64_t>(fn.start) << 32) | i);
            items[i] = it == facts.param.end() ? "null" : cls_ref(it->second);
            if (items[i] != "null") last = static_cast<int>(i);
        }
        auto rt = facts.ret.find(static_cast<std::uint64_t>(fn.start) << 32);
        const std::string rs = rt == facts.ret.end() ? "null" : cls_ref(rt->second);
        if (last < 0 && rs == "null") continue;
        ps = "[";
        for (int i = 0; i <= last; ++i) ps += (i ? "," : "") + items[i];
        ps += "]";
        std::fprintf(out, "%s\n\"%s\": {\"p\": %s, \"r\": %s}", firstf ? "" : ",", hex(fn.start).c_str(), ps.c_str(), rs.c_str());
        firstf = false;
    }
    // globals: absolute-address accesses
    std::map<std::pair<std::uint32_t, std::int32_t>, FieldOut> gl;
    for (const GAccess& g : facts.gaccesses) {
        FieldOut& fo = gl[{g.addr, g.stride}];
        fo.widths |= wbit(g.width);
        fo.kinds |= static_cast<std::uint8_t>(g.kind & ~kKStore);
        if (g.kind & kKStore) ++fo.stores; else ++fo.loads;
        add_fn(fo.fns, g.fn);
    }
    std::fputs("\n},\n\"globals\": [", out);
    bool firstg = true;
    for (const auto& [key, fo] : gl) {
        std::string ptr = "null";
        if (key.second == 0) {
            auto it = facts.gslot.find(static_cast<std::uint64_t>(key.first) << 32);
            if (it != facts.gslot.end()) ptr = cls_ref(it->second);
        }
        std::fprintf(out, "%s\n[\"%s\", %d, %s, \"%s\", %u, %u, %zu, %s, %s]", firstg ? "" : ",", hex(key.first).c_str(),
                     key.second, widths_str(fo.widths).c_str(), kinds_str(fo.kinds).c_str(), fo.loads, fo.stores,
                     fo.fns.size(), write_fns(fo.fns, 4).c_str(), ptr.c_str());
        firstg = false;
    }
    std::fputs("\n]\n}\n", out);
    std::fclose(out);
    return true;
}

}  // namespace p3fes::recomp::types
