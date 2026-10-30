// Minimal JSON reader for test fixtures (symbols/vu1_micro_census.json). Objects keep member order; numbers are
// doubles (the census holds integers well below 2^53). Returns nullopt on malformed input.
#pragma once

#include <cctype>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace p3fes::test::json {

struct Value {
    enum class Type { Null, Bool, Number, String, Array, Object } type = Type::Null;
    bool boolean = false;
    double number = 0.0;
    std::string string;
    std::vector<Value> array;
    std::vector<std::pair<std::string, Value>> object;

    const Value* get(std::string_view key) const {
        for (const auto& [k, v] : object)
            if (k == key) return &v;
        return nullptr;
    }
    long long as_int() const { return static_cast<long long>(number); }
};

class Parser {
public:
    explicit Parser(std::string_view text) : s_(text) {}

    std::optional<Value> parse() {
        Value v;
        if (!value(v, 0)) return std::nullopt;
        ws();
        if (p_ != s_.size()) return std::nullopt;
        return v;
    }

private:
    void ws() {
        while (p_ < s_.size() && (s_[p_] == ' ' || s_[p_] == '\n' || s_[p_] == '\r' || s_[p_] == '\t')) ++p_;
    }
    bool lit(std::string_view w) {
        if (s_.substr(p_, w.size()) != w) return false;
        p_ += w.size();
        return true;
    }
    bool str(std::string& out) {
        if (p_ >= s_.size() || s_[p_] != '"') return false;
        ++p_;
        while (p_ < s_.size() && s_[p_] != '"') {
            char c = s_[p_++];
            if (c == '\\') {
                if (p_ >= s_.size()) return false;
                const char e = s_[p_++];
                switch (e) {
                case 'n': c = '\n'; break;
                case 't': c = '\t'; break;
                case 'r': c = '\r'; break;
                case 'b': c = '\b'; break;
                case 'f': c = '\f'; break;
                case 'u': {
                    if (p_ + 4 > s_.size()) return false;
                    const unsigned long cp = std::strtoul(std::string(s_.substr(p_, 4)).c_str(), nullptr, 16);
                    p_ += 4;
                    c = cp < 0x80 ? static_cast<char>(cp) : '?'; // fixtures are ASCII; keep a placeholder
                    break;
                }
                default: c = e; break;
                }
            }
            out.push_back(c);
        }
        if (p_ >= s_.size()) return false;
        ++p_;
        return true;
    }
    bool value(Value& v, int depth) {
        if (depth > 64) return false;
        ws();
        if (p_ >= s_.size()) return false;
        const char c = s_[p_];
        if (c == '{') {
            v.type = Value::Type::Object;
            ++p_;
            ws();
            if (p_ < s_.size() && s_[p_] == '}') return ++p_, true;
            for (;;) {
                ws();
                std::string key;
                if (!str(key)) return false;
                ws();
                if (p_ >= s_.size() || s_[p_++] != ':') return false;
                Value member;
                if (!value(member, depth + 1)) return false;
                v.object.emplace_back(std::move(key), std::move(member));
                ws();
                if (p_ >= s_.size()) return false;
                if (s_[p_] == ',') { ++p_; continue; }
                if (s_[p_] == '}') return ++p_, true;
                return false;
            }
        }
        if (c == '[') {
            v.type = Value::Type::Array;
            ++p_;
            ws();
            if (p_ < s_.size() && s_[p_] == ']') return ++p_, true;
            for (;;) {
                Value item;
                if (!value(item, depth + 1)) return false;
                v.array.push_back(std::move(item));
                ws();
                if (p_ >= s_.size()) return false;
                if (s_[p_] == ',') { ++p_; continue; }
                if (s_[p_] == ']') return ++p_, true;
                return false;
            }
        }
        if (c == '"') {
            v.type = Value::Type::String;
            return str(v.string);
        }
        if (lit("true")) { v.type = Value::Type::Bool; v.boolean = true; return true; }
        if (lit("false")) { v.type = Value::Type::Bool; v.boolean = false; return true; }
        if (lit("null")) { v.type = Value::Type::Null; return true; }
        const std::size_t start = p_;
        while (p_ < s_.size() && (std::isdigit(static_cast<unsigned char>(s_[p_])) || s_[p_] == '-' || s_[p_] == '+' ||
                                  s_[p_] == '.' || s_[p_] == 'e' || s_[p_] == 'E'))
            ++p_;
        if (p_ == start) return false;
        v.type = Value::Type::Number;
        v.number = std::strtod(std::string(s_.substr(start, p_ - start)).c_str(), nullptr);
        return true;
    }

    std::string_view s_;
    std::size_t p_ = 0;
};

inline std::optional<Value> parse(std::string_view text) { return Parser(text).parse(); }

} // namespace p3fes::test::json
