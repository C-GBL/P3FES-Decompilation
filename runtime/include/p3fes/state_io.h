// Machine-state serialisation (runtime/STATE.md): one symmetric archive for saving and loading.
//
// Every component that holds machine state has a `void state(StateIo& io)` member (or a free `state_io(io, v)`
// for plain structs with containers) that lists its fields once: `io(x)` copies x out when saving and back in
// when loading. Trivially copyable values go as raw bytes; std::vector / std::deque / std::string / std::map /
// std::array / std::optional / std::pair of them recurse. Host pointers and wiring (callbacks, device pointers,
// back references) are never serialised: the loading process builds the same object graph first and the state
// only overwrites the dynamic fields. `section("name")` writes a tag that the reader checks, so an asymmetric
// list fails at the first section boundary with its name instead of corrupting everything after it.
#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace p3fes {

class StateIo;

// Raw-byte types: trivially copyable values that hold no host pointer (the caller's promise; pointers inside
// trivially copyable structs must be handled by a state_io overload instead).
template <class T>
concept StateRaw = std::is_trivially_copyable_v<T> && !std::is_pointer_v<T> && !std::is_member_pointer_v<T>;

class StateIo {
public:
    // A writer collecting into an in-memory buffer.
    StateIo() = default;
    // A reader over `data` (kept alive by the caller).
    StateIo(const std::uint8_t* data, std::size_t size) : loading_(true), rd_(data), rd_size_(size) {}

    bool loading() const noexcept { return loading_; }
    bool saving() const noexcept { return !loading_; }
    bool ok() const noexcept { return error_.empty(); }
    const std::string& error() const noexcept { return error_; }
    void fail(std::string why) {
        if (error_.empty()) error_ = std::move(why);
    }
    const std::vector<std::uint8_t>& buffer() const noexcept { return buf_; }
    std::vector<std::uint8_t> take_buffer() { return std::move(buf_); }
    std::size_t position() const noexcept { return loading_ ? rd_pos_ : buf_.size(); }
    bool at_end() const noexcept { return rd_pos_ == rd_size_; }

    void raw(void* p, std::size_t n) {
        if (n == 0) return;
        if (!loading_) {
            const auto* b = static_cast<const std::uint8_t*>(p);
            buf_.insert(buf_.end(), b, b + n);
            return;
        }
        if (!ok() || n > rd_size_ - rd_pos_) {
            fail("state data ends early");
            std::memset(p, 0, n);
            return;
        }
        std::memcpy(p, rd_ + rd_pos_, n);
        rd_pos_ += n;
    }

    // A named boundary: the reader must find the same name here.
    void section(const char* name) {
        std::uint32_t tag = 0x9E3779B9u;
        for (const char* c = name; *c; ++c) tag = (tag ^ static_cast<std::uint8_t>(*c)) * 16777619u;
        std::uint32_t got = tag;
        raw(&got, sizeof got);
        if (loading_ && ok() && got != tag) fail(std::string("state section mismatch at \"") + name + "\"");
    }
    // A value the reader must find unchanged (a size, a configuration word): mismatch fails with `what`.
    template <class T>
    void expect(T v, const char* what) {
        T got = v;
        raw(&got, sizeof got);
        if (loading_ && ok() && std::memcmp(&got, &v, sizeof v) != 0) fail(std::string("state mismatch: ") + what);
    }

    template <class T>
    void operator()(T& v) {
        io(*this, v);
    }
    template <class T, class... R>
    void operator()(T& v, R&... rest) {
        io(*this, v);
        (*this)(rest...);
    }

    std::uint64_t size_field(std::size_t n) {
        std::uint64_t s = n;
        raw(&s, sizeof s);
        if (loading_ && s > (rd_size_ - rd_pos_) + (1ull << 32)) {
            fail("state container size out of range");
            s = 0;
        }
        return s;
    }

private:
    bool loading_ = false;
    std::vector<std::uint8_t> buf_;
    const std::uint8_t* rd_ = nullptr;
    std::size_t rd_size_ = 0, rd_pos_ = 0;
    std::string error_;

};

namespace state_detail {
template <class T>
concept HasMember = requires(T& t, StateIo& s) { t.state(s); };
template <class T>
concept HasFree = requires(T& t, StateIo& s) { state_io(s, t); };
// Copied as raw bytes: raw-copyable with no state()/state_io of its own.
template <class T>
concept PlainRaw = StateRaw<T> && !HasMember<T> && !HasFree<T>;
}  // namespace state_detail

template <class T>
void io(StateIo& s, T& v) {
    if constexpr (state_detail::HasMember<T>) {
        v.state(s);
    } else if constexpr (state_detail::HasFree<T>) {
        state_io(s, v);
    } else {
        static_assert(StateRaw<T>, "no state() for this type and it is not raw-copyable");
        s.raw(&v, sizeof v);
    }
}

template <class T>
void state_io(StateIo& s, std::vector<T>& v) {
    const std::uint64_t n = s.size_field(v.size());
    // Same size: overwrite in place (components may hold pointers into fixed-size buffers, e.g. IOP RAM).
    if (s.loading() && v.size() != n) v.assign(static_cast<std::size_t>(n), T{});
    if constexpr (state_detail::PlainRaw<T>) {
        if (n) s.raw(v.data(), static_cast<std::size_t>(n) * sizeof(T));
    } else {
        for (T& e : v) s(e);
    }
}
inline void state_io(StateIo& s, std::vector<bool>& v) {
    const std::uint64_t n = s.size_field(v.size());
    if (s.loading()) v.assign(static_cast<std::size_t>(n), false);
    for (std::size_t i = 0; i < n; ++i) {
        std::uint8_t b = v[i] ? 1 : 0;
        s.raw(&b, 1);
        v[i] = b != 0;
    }
}
template <class T>
void state_io(StateIo& s, std::deque<T>& v) {
    const std::uint64_t n = s.size_field(v.size());
    if (s.loading()) v.assign(static_cast<std::size_t>(n), T{});
    for (T& e : v) s(e);
}
inline void state_io(StateIo& s, std::string& v) {
    const std::uint64_t n = s.size_field(v.size());
    if (s.loading()) v.assign(static_cast<std::size_t>(n), '\0');
    if (n) s.raw(v.data(), static_cast<std::size_t>(n));
}
template <class A, class B>
void state_io(StateIo& s, std::pair<A, B>& v) {
    s(v.first);
    s(v.second);
}
template <class T, std::size_t N>
    requires(!state_detail::PlainRaw<T>)
void state_io(StateIo& s, std::array<T, N>& v) {
    for (T& e : v) s(e);
}
template <class T>
void state_io(StateIo& s, std::optional<T>& v) {
    std::uint8_t has = v.has_value() ? 1 : 0;
    s.raw(&has, 1);
    if (s.loading()) {
        if (has) {
            if (!v) v.emplace();
        } else {
            v.reset();
        }
    }
    if (v) s(*v);
}
template <class K, class V, class C>
void state_io(StateIo& s, std::map<K, V, C>& m) {
    const std::uint64_t n = s.size_field(m.size());
    if (!s.loading()) {
        for (auto& [k, v] : m) {
            K kk = k;
            s(kk);
            s(v);
        }
        return;
    }
    m.clear();
    for (std::uint64_t i = 0; i < n && s.ok(); ++i) {
        K k{};
        s(k);
        V v{};
        s(v);
        m.emplace(std::move(k), std::move(v));
    }
}

// ---- state files ----------------------------------------------------------------------------------------
// A fixed header (everything a loader checks before it builds anything) + the payload (StateIo bytes) with long
// zero runs elided. The header is plain data so the host can read it before main() (the /GS cookie,
// runtime/app/game_state.cpp).
inline constexpr std::uint32_t kStateVersion = 2;

struct StateHeader {
    char magic[8] = {'P', '3', 'F', 'E', 'S', 'S', 'T', '\0'};
    std::uint32_t version = kStateVersion;
    std::uint32_t header_bytes = sizeof(StateHeader);
    std::uint64_t exe_hash = 0;        // the saving executable's file (frames on the fiber stacks are its code)
    std::uint64_t exe_size = 0;
    std::uint64_t image_base = 0;      // where it ran (fixed: /DYNAMICBASE:NO)
    std::uint64_t security_cookie = 0; // its /GS cookie (frames on the fiber stacks carry cookie ^ rsp)
    std::uint64_t arena_used = 0;      // pinned arena bytes handed out when the state was saved
    std::uint64_t vblanks = 0, cycles = 0, flips = 0;
    std::uint64_t payload_bytes = 0;   // uncompressed
    std::uint64_t payload_hash = 0;
    std::uint64_t stored_bytes = 0;    // as stored in the file
    std::uint32_t reference_mode = 0;  // the saver ran in reference mode (informational: the loader chooses)
    std::uint32_t reserved = 0;
    char elf_sha256[72] = {};          // hex
    char config[320] = {};             // behaviour-relevant host configuration (must match on load)
    char label[64] = {};               // the save point, e.g. "vblank:3000"
};

std::uint64_t state_hash(const void* p, std::size_t n, std::uint64_t seed = 0);
// The running executable: hash and size of its file, and its image base.
bool exe_identity(std::uint64_t& hash, std::uint64_t& size, std::uint64_t& image_base, std::string& error);
bool write_state_file(const std::string& path, StateHeader h, const std::vector<std::uint8_t>& payload, std::string& error);
bool read_state_header(const std::string& path, StateHeader& h, std::string& error);
bool read_state_file(const std::string& path, StateHeader& h, std::vector<std::uint8_t>& payload, std::string& error);

}  // namespace p3fes
