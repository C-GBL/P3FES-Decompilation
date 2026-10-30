// Error algebra for the Atlus/CRI/RenderWare format parsers (runtime/formats/).
//
// No exceptions cross this API: every parser returns Result<T>, which is either
// a value or a FormatError plus a short static detail string pointing at the
// field that failed. Parsers are *views*: they never copy payload bytes, so a
// Result<View> stays valid only as long as the span it was parsed from.
#pragma once

#include <optional>
#include <string_view>
#include <utility>

#include "p3fes/ee_types.h"

namespace p3fes::formats {

enum class FormatError : u8 {
    None = 0,
    Truncated,    // buffer ended before a required field/section
    BadMagic,     // identifying bytes do not match
    BadHeader,    // a header field has a value the format forbids
    Overrun,      // a size/offset points outside the buffer
    Unsupported,  // syntactically fine, but a variant this parser does not handle
    Corrupt,      // internal inconsistency (e.g. sections do not tile the file)
};

constexpr std::string_view error_name(FormatError e) {
    switch (e) {
    case FormatError::None:        return "ok";
    case FormatError::Truncated:   return "truncated";
    case FormatError::BadMagic:    return "bad_magic";
    case FormatError::BadHeader:   return "bad_header";
    case FormatError::Overrun:     return "overrun";
    case FormatError::Unsupported: return "unsupported";
    case FormatError::Corrupt:     return "corrupt";
    }
    return "unknown";
}

struct Error {
    FormatError code = FormatError::None;
    const char* detail = "";  // static string naming the field/stage that failed
};

template <class T>
class [[nodiscard]] Result {
public:
    Result(T value) : value_(std::move(value)) {}            // NOLINT(google-explicit-constructor)
    Result(Error e) : error_(e) {}                           // NOLINT(google-explicit-constructor)
    Result(FormatError code, const char* detail) : error_{code, detail} {}

    [[nodiscard]] bool ok() const { return value_.has_value(); }
    explicit operator bool() const { return ok(); }

    const T& value() const& { return *value_; }
    T& value() & { return *value_; }
    T&& value() && { return std::move(*value_); }
    const T* operator->() const { return &*value_; }
    T* operator->() { return &*value_; }

    [[nodiscard]] Error error() const { return error_; }
    [[nodiscard]] FormatError code() const { return error_.code; }
    [[nodiscard]] const char* detail() const { return error_.detail; }

private:
    std::optional<T> value_;
    Error error_{};
};

}  // namespace p3fes::formats
