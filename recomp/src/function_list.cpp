#include "function_list.h"

#include "json_lite.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>

namespace p3fes::recomp {

bool Function::is_data(std::uint32_t ea) const noexcept {
    // data is sorted by ea; find the first item ending after ea.
    auto it = std::upper_bound(data.begin(), data.end(), ea,
                               [](std::uint32_t v, const DataItem& d) { return v < d.ea; });
    if (it == data.begin()) return false;
    --it;
    return ea >= it->ea && ea < it->ea + it->size;
}

bool read_file(const char* path, std::string& out) {
    std::FILE* f = std::fopen(path, "rb");
    if (!f) return false;
    out.clear();
    char buf[1 << 16];
    std::size_t n;
    while ((n = std::fread(buf, 1, sizeof buf, f)) > 0) out.append(buf, n);
    const bool ok = std::ferror(f) == 0;
    std::fclose(f);
    return ok;
}

const char* FunctionList::load_functions_json(const std::string& text) {
    json::ParseResult pr = json::Parser::parse(text);
    if (pr.error) return pr.error;
    if (!pr.value.is_array()) return "functions.json: top level is not an array";
    functions.clear();
    functions.reserve(pr.value.items.size());
    for (const json::Value& e : pr.value.items) {
        const json::Value* a = e.get("a");
        const json::Value* s = e.get("s");
        const json::Value* n = e.get("n");
        std::uint64_t av = 0, sv = 0;
        if (!a || !s || !n || !a->to_u64(av) || !s->to_u64(sv) || !n->is_string())
            return "functions.json: entry without a/s/n";
        if (av > 0xFFFFFFFFull || sv > 0xFFFFFFFFull) return "functions.json: value out of range";
        Function f;
        f.start = static_cast<std::uint32_t>(av);
        f.size = static_cast<std::uint32_t>(sv);
        f.name = n->str;
        functions.push_back(std::move(f));
    }
    std::sort(functions.begin(), functions.end(),
              [](const Function& x, const Function& y) { return x.start < y.start; });
    has_chunks = false;
    return nullptr;
}

namespace {

bool parse_hex(const char*& p, std::uint32_t& out) noexcept {
    char* end = nullptr;
    const unsigned long long v = std::strtoull(p, &end, 16);
    if (end == p || v > 0xFFFFFFFFull) return false;
    out = static_cast<std::uint32_t>(v);
    p = end;
    return true;
}
bool parse_dec(const char*& p, std::uint32_t& out) noexcept {
    char* end = nullptr;
    const unsigned long long v = std::strtoull(p, &end, 10);
    if (end == p || v > 0xFFFFFFFFull) return false;
    out = static_cast<std::uint32_t>(v);
    p = end;
    return true;
}
void skip_spaces(const char*& p) noexcept { while (*p == ' ' || *p == '\t') ++p; }

}  // namespace

const char* FunctionList::apply_chunk_list(const std::string& text, std::size_t* mismatches) {
    std::size_t only_in_chunks = 0, matched = 0;
    std::vector<Function> extra;
    std::size_t line_start = 0;
    while (line_start < text.size()) {
        std::size_t line_end = text.find('\n', line_start);
        if (line_end == std::string::npos) line_end = text.size();
        std::string line = text.substr(line_start, line_end - line_start);
        line_start = line_end + 1;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;

        const char* p = line.c_str();
        std::uint32_t start = 0;
        if (!parse_hex(p, start)) return "chunk list: bad start address";
        skip_spaces(p);
        const char* name_begin = p;
        while (*p && *p != ' ' && *p != '\t') ++p;
        std::string name(name_begin, p);
        skip_spaces(p);
        if (*p != 'C') return "chunk list: expected 'C'";
        ++p;
        std::vector<Range> chunks;
        std::vector<DataItem> data;
        skip_spaces(p);
        while (*p && *p != 'D') {
            Range r;
            if (!parse_hex(p, r.start) || *p != '-') return "chunk list: bad chunk range";
            ++p;
            if (!parse_hex(p, r.end) || r.end < r.start) return "chunk list: bad chunk range";
            chunks.push_back(r);
            skip_spaces(p);
        }
        if (*p == 'D') {
            ++p;
            skip_spaces(p);
            while (*p) {
                DataItem d;
                if (!parse_hex(p, d.ea) || *p != ':') return "chunk list: bad data item";
                ++p;
                if (!parse_dec(p, d.size)) return "chunk list: bad data item";
                data.push_back(d);
                skip_spaces(p);
            }
        }
        if (chunks.empty()) return "chunk list: function without chunks";
        std::sort(data.begin(), data.end(), [](const DataItem& x, const DataItem& y) { return x.ea < y.ea; });

        auto it = std::lower_bound(functions.begin(), functions.end(), start,
                                   [](const Function& f, std::uint32_t v) { return f.start < v; });
        if (it != functions.end() && it->start == start) {
            it->chunks = std::move(chunks);
            it->data = std::move(data);
            ++matched;
        } else {
            Function f;
            f.start = start;
            f.name = std::move(name);
            f.chunks = std::move(chunks);
            f.data = std::move(data);
            for (const Range& r : f.chunks) f.size += r.end - r.start;
            extra.push_back(std::move(f));
            ++only_in_chunks;
        }
    }
    const std::size_t only_in_json = functions.size() - matched;
    for (Function& f : extra) functions.push_back(std::move(f));
    std::sort(functions.begin(), functions.end(),
              [](const Function& x, const Function& y) { return x.start < y.start; });
    has_chunks = true;
    if (mismatches) *mismatches = only_in_chunks + only_in_json;
    return nullptr;
}

const Function* FunctionList::find(std::uint32_t start) const noexcept {
    auto it = std::lower_bound(functions.begin(), functions.end(), start,
                               [](const Function& f, std::uint32_t v) { return f.start < v; });
    return (it != functions.end() && it->start == start) ? &*it : nullptr;
}

}  // namespace p3fes::recomp
