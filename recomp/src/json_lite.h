// Minimal JSON reader for the recompiler's inputs (symbols/functions.json, insn_census.json,
// jumptables.json). Header-only, no exceptions, no dependencies. Parses a whole document into
// a tree of Value nodes; numbers are kept as double plus the source text (so 0x-free large
// integers survive). Not a general-purpose library: no \u escapes beyond ASCII, no streaming.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace p3fes::recomp::json {

struct Value {
    enum class Kind : std::uint8_t { Null, Bool, Number, String, Array, Object };
    Kind kind = Kind::Null;
    bool b = false;
    double num = 0.0;
    std::string str;                                   // String, or the source text of a Number
    std::vector<Value> items;                          // Array
    std::vector<std::pair<std::string, Value>> fields; // Object (insertion order kept)

    bool is_null() const noexcept { return kind == Kind::Null; }
    bool is_object() const noexcept { return kind == Kind::Object; }
    bool is_array() const noexcept { return kind == Kind::Array; }
    bool is_string() const noexcept { return kind == Kind::String; }
    bool is_number() const noexcept { return kind == Kind::Number; }

    const Value* get(std::string_view key) const noexcept {
        if (kind != Kind::Object) return nullptr;
        for (const auto& [k, v] : fields)
            if (k == key) return &v;
        return nullptr;
    }
    // Integer view of a Number (truncating) or of a String holding "0x.." / decimal text.
    bool to_u64(std::uint64_t& out) const noexcept {
        if (kind == Kind::Number) {
            if (num < 0) return false;
            out = static_cast<std::uint64_t>(num);
            return true;
        }
        if (kind == Kind::String && !str.empty()) {
            char* end = nullptr;
            const unsigned long long v = std::strtoull(str.c_str(), &end, 0);
            if (end == str.c_str() || *end != '\0') return false;
            out = v;
            return true;
        }
        return false;
    }
};

struct ParseResult {
    Value value;
    const char* error = nullptr;  // nullptr on success
    std::size_t error_offset = 0;
};

class Parser {
public:
    static ParseResult parse(std::string_view text) {
        Parser p{text};
        ParseResult r;
        p.skip_ws();
        if (!p.parse_value(r.value, 0)) {
            r.error = p.err_ ? p.err_ : "malformed JSON";
            r.error_offset = p.pos_;
            r.value = Value{};
            return r;
        }
        p.skip_ws();
        if (p.pos_ != p.text_.size()) {
            r.error = "trailing characters";
            r.error_offset = p.pos_;
            r.value = Value{};
        }
        return r;
    }

private:
    explicit Parser(std::string_view t) : text_(t) {}

    std::string_view text_;
    std::size_t pos_ = 0;
    const char* err_ = nullptr;

    bool fail(const char* m) noexcept { if (!err_) err_ = m; return false; }
    bool at_end() const noexcept { return pos_ >= text_.size(); }
    char peek() const noexcept { return at_end() ? '\0' : text_[pos_]; }
    void skip_ws() noexcept {
        while (!at_end()) {
            const char c = text_[pos_];
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') ++pos_; else break;
        }
    }
    bool consume(char c) noexcept {
        if (peek() != c) return false;
        ++pos_;
        return true;
    }
    bool consume_word(const char* w) noexcept {
        const std::size_t n = std::strlen(w);
        if (text_.substr(pos_, n) != w) return false;
        pos_ += n;
        return true;
    }

    bool parse_value(Value& v, int depth) {
        if (depth > 256) return fail("nesting too deep");
        switch (peek()) {
        case '{': return parse_object(v, depth);
        case '[': return parse_array(v, depth);
        case '"': v.kind = Value::Kind::String; return parse_string(v.str);
        case 't': if (!consume_word("true")) return fail("bad literal"); v.kind = Value::Kind::Bool; v.b = true; return true;
        case 'f': if (!consume_word("false")) return fail("bad literal"); v.kind = Value::Kind::Bool; v.b = false; return true;
        case 'n': if (!consume_word("null")) return fail("bad literal"); v.kind = Value::Kind::Null; return true;
        default: return parse_number(v);
        }
    }

    bool parse_number(Value& v) {
        const std::size_t start = pos_;
        if (peek() == '-') ++pos_;
        while (!at_end()) {
            const char c = text_[pos_];
            if ((c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-') ++pos_; else break;
        }
        if (pos_ == start) return fail("expected value");
        v.kind = Value::Kind::Number;
        v.str.assign(text_.data() + start, pos_ - start);
        v.num = std::strtod(v.str.c_str(), nullptr);
        return true;
    }

    bool parse_string(std::string& out) {
        if (!consume('"')) return fail("expected string");
        out.clear();
        while (true) {
            if (at_end()) return fail("unterminated string");
            char c = text_[pos_++];
            if (c == '"') return true;
            if (c != '\\') { out.push_back(c); continue; }
            if (at_end()) return fail("bad escape");
            c = text_[pos_++];
            switch (c) {
            case '"': out.push_back('"'); break;
            case '\\': out.push_back('\\'); break;
            case '/': out.push_back('/'); break;
            case 'b': out.push_back('\b'); break;
            case 'f': out.push_back('\f'); break;
            case 'n': out.push_back('\n'); break;
            case 'r': out.push_back('\r'); break;
            case 't': out.push_back('\t'); break;
            case 'u': {
                if (pos_ + 4 > text_.size()) return fail("bad \\u escape");
                unsigned cp = 0;
                for (int i = 0; i < 4; ++i) {
                    const char h = text_[pos_++];
                    cp <<= 4;
                    if (h >= '0' && h <= '9') cp |= unsigned(h - '0');
                    else if (h >= 'a' && h <= 'f') cp |= unsigned(h - 'a' + 10);
                    else if (h >= 'A' && h <= 'F') cp |= unsigned(h - 'A' + 10);
                    else return fail("bad \\u escape");
                }
                if (cp < 0x80) out.push_back(char(cp));
                else if (cp < 0x800) { out.push_back(char(0xC0 | (cp >> 6))); out.push_back(char(0x80 | (cp & 0x3F))); }
                else { out.push_back(char(0xE0 | (cp >> 12))); out.push_back(char(0x80 | ((cp >> 6) & 0x3F))); out.push_back(char(0x80 | (cp & 0x3F))); }
                break;
            }
            default: return fail("bad escape");
            }
        }
    }

    bool parse_array(Value& v, int depth) {
        consume('[');
        v.kind = Value::Kind::Array;
        skip_ws();
        if (consume(']')) return true;
        while (true) {
            skip_ws();
            Value item;
            if (!parse_value(item, depth + 1)) return false;
            v.items.push_back(std::move(item));
            skip_ws();
            if (consume(',')) continue;
            if (consume(']')) return true;
            return fail("expected ',' or ']'");
        }
    }

    bool parse_object(Value& v, int depth) {
        consume('{');
        v.kind = Value::Kind::Object;
        skip_ws();
        if (consume('}')) return true;
        while (true) {
            skip_ws();
            std::string key;
            if (!parse_string(key)) return false;
            skip_ws();
            if (!consume(':')) return fail("expected ':'");
            skip_ws();
            Value item;
            if (!parse_value(item, depth + 1)) return false;
            v.fields.emplace_back(std::move(key), std::move(item));
            skip_ws();
            if (consume(',')) continue;
            if (consume('}')) return true;
            return fail("expected ',' or '}'");
        }
    }
};

}  // namespace p3fes::recomp::json
