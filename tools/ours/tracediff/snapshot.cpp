#include "snapshot.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cstring>
#include <sstream>

namespace tracediff::snapshot {

// ---- bands -------------------------------------------------------------------
const std::vector<Band>& bands() {
    // Boundaries from docs/ANALYSIS/00_elf_layout.md / the Phase 4 brief.
    static const std::vector<Band> b = {
        {"kernel", 0x00000000u, 0x00100000u},
        {"code", 0x00100000u, 0x005A1400u},
        {"data", 0x005A2000u, 0x007CDE04u},
        {"bss", 0x007CDE80u, 0x009ACC80u},
        {"heap", 0x009ACC80u, 0x01F60000u},
        {"stack", 0x01F60000u, 0x02000000u},
    };
    return b;
}

namespace {
std::size_t band_index(std::uint32_t off) {
    const auto& b = bands();
    for (std::size_t i = 0; i < b.size(); ++i)
        if (off >= b[i].begin && off < b[i].end) return i;
    return b.size();  // "other"
}
}  // namespace

const char* band_of(std::uint32_t offset) {
    std::size_t i = band_index(offset);
    return i < bands().size() ? bands()[i].name : "other";
}

// ---- mask --------------------------------------------------------------------
void Mask::add(Range r) {
    if (r.end <= r.begin) return;
    ranges.push_back(r);
}

void Mask::normalize() {
    std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) { return a.begin < b.begin; });
    std::vector<Range> out;
    for (const Range& r : ranges) {
        if (!out.empty() && r.begin <= out.back().end)
            out.back().end = std::max(out.back().end, r.end);
        else
            out.push_back(r);
    }
    ranges.swap(out);
}

bool Mask::covers(std::uint32_t offset) const {
    auto it = std::upper_bound(ranges.begin(), ranges.end(), offset,
                               [](std::uint32_t o, const Range& r) { return o < r.begin; });
    if (it == ranges.begin()) return false;
    --it;
    return offset >= it->begin && offset < it->end;
}

std::uint64_t Mask::masked_bytes() const {
    std::uint64_t n = 0;
    for (const Range& r : ranges) n += r.size();
    return n;
}

namespace {

std::string_view trim(std::string_view s) {
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r')) s.remove_prefix(1);
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r')) s.remove_suffix(1);
    return s;
}

bool parse_hex(std::string_view s, std::uint64_t* out) {
    s = trim(s);
    if (s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s.remove_prefix(2);
    if (s.empty()) return false;
    std::uint64_t v = 0;
    auto res = std::from_chars(s.data(), s.data() + s.size(), v, 16);
    if (res.ec != std::errc{} || res.ptr != s.data() + s.size()) return false;
    *out = v;
    return true;
}

}  // namespace

std::optional<Mask> parse_mask(std::string_view text, ParseError* err) {
    Mask m;
    int lineno = 0;
    std::size_t pos = 0;
    while (pos < text.size()) {
        std::size_t nl = text.find('\n', pos);
        std::string_view line = (nl == std::string_view::npos) ? text.substr(pos) : text.substr(pos, nl - pos);
        pos = (nl == std::string_view::npos) ? text.size() : nl + 1;
        ++lineno;
        std::size_t hash = line.find('#');
        if (hash != std::string_view::npos) line = line.substr(0, hash);
        line = trim(line);
        if (line.empty()) continue;

        auto fail = [&](const char* msg) -> std::optional<Mask> {
            if (err) *err = {lineno, msg};
            return std::nullopt;
        };
        std::uint64_t a = 0, b = 0;
        Range r;
        // '-' or an en dash (UTF-8 E2 80 93) separates an inclusive range.
        std::size_t dash = line.find('-');
        std::size_t endash = line.find("\xE2\x80\x93");
        std::size_t plus = line.find('+');
        if (dash != std::string_view::npos || endash != std::string_view::npos) {
            std::size_t cut = std::min(dash, endash);
            std::size_t seplen = (cut == dash) ? 1 : 3;
            if (!parse_hex(line.substr(0, cut), &a) || !parse_hex(line.substr(cut + seplen), &b))
                return fail("expected <hex>-<hex> (inclusive end)");
            a &= kPhysMask;
            b &= kPhysMask;
            if (b < a) return fail("range end precedes start");
            if (b >= kEeRamSize) b = kEeRamSize - 1;
            r = {static_cast<std::uint32_t>(a), static_cast<std::uint32_t>(b + 1)};
        } else if (plus != std::string_view::npos) {
            if (!parse_hex(line.substr(0, plus), &a) || !parse_hex(line.substr(plus + 1), &b))
                return fail("expected <hex>+<hex length>");
            a &= kPhysMask;
            if (b == 0) return fail("zero length");
            std::uint64_t e = std::min<std::uint64_t>(a + b, kEeRamSize);
            r = {static_cast<std::uint32_t>(a), static_cast<std::uint32_t>(e)};
        } else {
            if (!parse_hex(line, &a)) return fail("expected a hex address");
            a &= kPhysMask;
            std::uint64_t e = std::min<std::uint64_t>(a + 4, kEeRamSize);
            r = {static_cast<std::uint32_t>(a), static_cast<std::uint32_t>(e)};
        }
        if (r.begin >= kEeRamSize) return fail("address beyond 32 MiB EE RAM");
        m.add(r);
    }
    m.normalize();
    return m;
}

std::string format_mask(const Mask& m, std::string_view header_comment) {
    std::string out;
    std::size_t p = 0;
    while (p < header_comment.size()) {
        std::size_t nl = header_comment.find('\n', p);
        std::string_view l = (nl == std::string_view::npos) ? header_comment.substr(p) : header_comment.substr(p, nl - p);
        out += "# ";
        out.append(l.data(), l.size());
        out += '\n';
        p = (nl == std::string_view::npos) ? header_comment.size() : nl + 1;
    }
    char buf[64];
    for (const Range& r : m.ranges) {
        std::snprintf(buf, sizeof buf, "0x%08X-0x%08X\n", r.begin, r.end - 1);
        out += buf;
    }
    return out;
}

Mask default_mask() {
    Mask m;
    m.add({0x00000000u, 0x00100000u});  // TRACE_FORMAT §4.3: EE kernel area
    m.normalize();
    return m;
}

namespace {
// Value of `"key": <number or "0x...">` after position `from` and before `until`; false if absent.
bool scan_value(std::string_view s, std::size_t from, std::size_t until, std::string_view key, std::uint64_t* out) {
    const std::string pat = "\"" + std::string(key) + "\":";
    const std::size_t k = s.find(pat, from);
    if (k == std::string_view::npos || k >= until) return false;
    std::size_t i = k + pat.size();
    while (i < until && (s[i] == ' ' || s[i] == '"')) ++i;
    std::size_t j = i;
    while (j < until && (std::isxdigit(static_cast<unsigned char>(s[j])) || s[j] == 'x' || s[j] == 'X')) ++j;
    if (j == i) return false;
    const std::string_view num = s.substr(i, j - i);
    std::uint64_t v = 0;
    const bool hex = num.size() > 2 && num[0] == '0' && (num[1] == 'x' || num[1] == 'X');
    const auto r = std::from_chars(num.data() + (hex ? 2 : 0), num.data() + num.size(), v, hex ? 16 : 10);
    if (r.ec != std::errc{} || r.ptr != num.data() + num.size()) return false;
    *out = v;
    return true;
}
}  // namespace

std::optional<Mask> dead_stack_mask(std::string_view text, std::string* why) {
    const std::size_t threads = text.find("\"threads\":");
    if (threads == std::string_view::npos) {
        if (why) *why = "no \"threads\" array in the capture";
        return std::nullopt;
    }
    std::uint64_t current = 0, live_sp = 0;
    const bool has_current = scan_value(text, 0, text.size(), "current_thread", &current);
    const bool has_sp = scan_value(text, 0, text.size(), "sp", &live_sp);
    const std::size_t end = text.find(']', threads);
    Mask m;
    std::size_t pos = threads;
    for (;;) {
        const std::size_t open = text.find('{', pos);
        if (open == std::string_view::npos || open >= end) break;
        const std::size_t close = text.find('}', open);
        if (close == std::string_view::npos) break;
        std::uint64_t tid = 0, stack = 0, size = 0, frame = 0;
        if (scan_value(text, open, close, "tid", &tid) && scan_value(text, open, close, "stack", &stack) &&
            scan_value(text, open, close, "stack_size", &size) && scan_value(text, open, close, "frame", &frame)) {
            std::uint64_t bound = frame;
            if (has_current && has_sp && current != 0 && tid == current) bound = live_sp;
            const std::uint64_t top = stack + size;
            if (bound > top) bound = top;
            if (bound > stack && stack < kEeRamSize)
                m.add({static_cast<std::uint32_t>(stack & kPhysMask), static_cast<std::uint32_t>(bound & kPhysMask)});
        }
        pos = close + 1;
    }
    m.normalize();
    return m;
}

// ---- compare ----------------------------------------------------------------
std::optional<Run> Report::first_run() const {
    if (runs.empty()) return std::nullopt;
    return runs.front();
}

std::vector<Run> Report::largest_runs(std::size_t n) const {
    std::vector<Run> v = runs;
    std::stable_sort(v.begin(), v.end(), [](const Run& a, const Run& b) { return a.length > b.length; });
    if (v.size() > n) v.resize(n);
    return v;
}

Report compare(const std::uint8_t* ref, const std::uint8_t* ours, std::size_t size, const Mask& mask) {
    Report rep;
    for (const Range& r : mask.ranges)
        rep.masked_bytes += std::min<std::uint64_t>(r.end, size) - std::min<std::uint64_t>(r.begin, size);

    const std::size_t nb = bands().size();
    std::vector<std::uint64_t> band_bytes(nb + 1, 0), band_runs(nb + 1, 0);

    // Walk the unmasked gaps between mask ranges; compare 8 bytes at a time.
    std::size_t pos = 0;
    std::size_t mi = 0;
    const auto& mr = mask.ranges;
    while (pos < size) {
        std::size_t gap_end = size;
        while (mi < mr.size() && mr[mi].end <= pos) ++mi;
        if (mi < mr.size()) {
            if (mr[mi].begin <= pos) {
                pos = mr[mi].end;
                continue;
            }
            gap_end = std::min<std::size_t>(mr[mi].begin, size);
        }
        std::size_t i = pos;
        while (i < gap_end) {
            if (i + 8 <= gap_end) {
                std::uint64_t a, b;
                std::memcpy(&a, ref + i, 8);
                std::memcpy(&b, ours + i, 8);
                if (a == b) {
                    i += 8;
                    continue;
                }
            }
            if (ref[i] == ours[i]) {
                ++i;
                continue;
            }
            std::size_t j = i;
            while (j < gap_end && ref[j] != ours[j]) ++j;
            Run run{static_cast<std::uint32_t>(i), static_cast<std::uint32_t>(j - i)};
            rep.runs.push_back(run);
            rep.total_differing_bytes += run.length;
            // A run counts once, in the band of its first byte; its bytes are
            // split at band boundaries so per-band byte totals stay exact.
            std::uint32_t o = run.offset, e = run.offset + run.length;
            bool first = true;
            while (o < e) {
                std::size_t bi = band_index(o);
                std::uint32_t band_end = e;
                if (bi < nb) {
                    band_end = bands()[bi].end;
                } else {
                    for (const Band& bd : bands())
                        if (bd.begin > o) band_end = std::min(band_end, bd.begin);
                }
                std::uint32_t chunk_end = std::min(e, band_end);
                band_bytes[bi] += chunk_end - o;
                if (first) {
                    band_runs[bi] += 1;
                    first = false;
                }
                o = chunk_end;
            }
            i = j;
        }
        pos = gap_end;
    }
    rep.run_count = rep.runs.size();
    for (std::size_t i = 0; i < nb; ++i) rep.per_band.push_back({bands()[i].name, band_bytes[i], band_runs[i]});
    rep.per_band.push_back({"other", band_bytes[nb], band_runs[nb]});
    return rep;
}

std::vector<std::uint8_t> load_image(const std::string& path, std::string* error) {
    std::vector<std::uint8_t> data;
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) {
        if (error) *error = "cannot open " + path;
        return data;
    }
    _fseeki64(f, 0, SEEK_END);
    long long sz = _ftelli64(f);
    _fseeki64(f, 0, SEEK_SET);
    if (sz != static_cast<long long>(kEeRamSize)) {
        std::fclose(f);
        if (error) {
            char buf[160];
            std::snprintf(buf, sizeof buf, " is %lld bytes, expected %zu (32 MiB eeMemory.bin)", sz, kEeRamSize);
            *error = path + buf;
        }
        return data;
    }
    data.resize(kEeRamSize);
    std::size_t got = std::fread(data.data(), 1, data.size(), f);
    std::fclose(f);
    if (got != data.size()) {
        if (error) *error = "short read on " + path;
        data.clear();
    }
    return data;
}

std::string hex_bytes(const std::uint8_t* img, std::size_t size, std::uint32_t off, std::size_t n) {
    std::string s;
    char buf[4];
    for (std::size_t k = 0; k < n && off + k < size; ++k) {
        std::snprintf(buf, sizeof buf, "%02x", img[off + k]);
        if (!s.empty()) s += ' ';
        s += buf;
    }
    return s;
}

Mask derive_mask(const Report& r, std::uint32_t pad, std::uint32_t merge_gap) {
    Mask m;
    for (const Run& run : r.runs) {
        std::uint64_t b = run.offset > pad ? run.offset - pad : 0;
        std::uint64_t e = std::min<std::uint64_t>(static_cast<std::uint64_t>(run.offset) + run.length + pad, kEeRamSize);
        m.add({static_cast<std::uint32_t>(b), static_cast<std::uint32_t>(e)});
    }
    m.normalize();
    if (merge_gap > 0 && m.ranges.size() > 1) {
        std::vector<Range> out;
        for (const Range& x : m.ranges) {
            if (!out.empty() && x.begin <= out.back().end + merge_gap)
                out.back().end = std::max(out.back().end, x.end);
            else
                out.push_back(x);
        }
        m.ranges.swap(out);
    }
    return m;
}

namespace {
std::string json_escape(const std::string& s) {
    std::string o;
    for (char c : s) {
        if (c == '\\' || c == '"') {
            o += '\\';
            o += c;
        } else if (static_cast<unsigned char>(c) < 0x20) {
            char buf[8];
            std::snprintf(buf, sizeof buf, "\\u%04x", static_cast<unsigned>(static_cast<unsigned char>(c)));
            o += buf;
        } else {
            o += c;
        }
    }
    return o;
}
}  // namespace

std::string to_json(const Report& r, std::size_t top, const std::string& ref_path, const std::string& ours_path) {
    std::ostringstream o;
    o << "{\n";
    o << "  \"ref\": \"" << json_escape(ref_path) << "\",\n";
    o << "  \"ours\": \"" << json_escape(ours_path) << "\",\n";
    o << "  \"image_size\": " << kEeRamSize << ",\n";
    o << "  \"masked_bytes\": " << r.masked_bytes << ",\n";
    o << "  \"differing_bytes\": " << r.total_differing_bytes << ",\n";
    o << "  \"runs\": " << r.run_count << ",\n";
    char buf[96];
    if (auto f = r.first_run()) {
        std::snprintf(buf, sizeof buf, "{\"va\": \"0x%08X\", \"length\": %u, \"band\": \"%s\"}", f->offset, f->length,
                      band_of(f->offset));
        o << "  \"first_run\": " << buf << ",\n";
    } else {
        o << "  \"first_run\": null,\n";
    }
    o << "  \"largest_runs\": [";
    bool first = true;
    for (const Run& run : r.largest_runs(top)) {
        std::snprintf(buf, sizeof buf, "{\"va\": \"0x%08X\", \"length\": %u, \"band\": \"%s\"}", run.offset, run.length,
                      band_of(run.offset));
        o << (first ? "\n    " : ",\n    ") << buf;
        first = false;
    }
    o << (first ? "" : "\n  ") << "],\n";
    o << "  \"per_band\": {";
    first = true;
    for (const BandStat& b : r.per_band) {
        o << (first ? "\n    " : ",\n    ") << "\"" << b.name << "\": {\"differing_bytes\": " << b.differing_bytes
          << ", \"runs\": " << b.runs << "}";
        first = false;
    }
    o << "\n  }\n}\n";
    return o.str();
}

}  // namespace tracediff::snapshot
