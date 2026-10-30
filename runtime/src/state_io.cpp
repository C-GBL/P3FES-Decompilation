#include "p3fes/state_io.h"

#include <windows.h>

#include <cstdio>
#include <memory>

namespace p3fes {

std::uint64_t state_hash(const void* p, std::size_t n, std::uint64_t seed) {
    const auto* b = static_cast<const std::uint8_t*>(p);
    std::uint64_t h = seed ^ 0x6A09E667F3BCC908ull ^ (n * 0x9E3779B97F4A7C15ull);
    std::size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        std::uint64_t w;
        std::memcpy(&w, b + i, 8);
        h = (h ^ w) * 0x9E3779B97F4A7C15ull;
        h ^= h >> 29;
    }
    for (; i < n; ++i) {
        h = (h ^ b[i]) * 0x100000001B3ull;
        h ^= h >> 29;
    }
    return h;
}

bool exe_identity(std::uint64_t& hash, std::uint64_t& size, std::uint64_t& image_base, std::string& error) {
    wchar_t path[MAX_PATH * 4];
    const DWORD n = GetModuleFileNameW(nullptr, path, static_cast<DWORD>(std::size(path)));
    if (n == 0 || n >= std::size(path)) {
        error = "cannot name the running executable";
        return false;
    }
    image_base = reinterpret_cast<std::uint64_t>(GetModuleHandleW(nullptr));
    std::FILE* f = _wfopen(path, L"rb");
    if (!f) {
        error = "cannot read the running executable";
        return false;
    }
    std::vector<std::uint8_t> buf(1u << 22);
    std::uint64_t h = 0, total = 0;
    for (;;) {
        const std::size_t got = std::fread(buf.data(), 1, buf.size(), f);
        if (got == 0) break;
        h = state_hash(buf.data(), got, h);
        total += got;
    }
    std::fclose(f);
    hash = h;
    size = total;
    return true;
}

namespace {

// Zero-run elision: [u32 literal length][literal bytes][u32 zero run length] ... (runs shorter than 64 bytes stay
// literal). Guest RAM, GS memory and the IOP/SPU2 RAM images are mostly zero-filled early on.
std::vector<std::uint8_t> squeeze(const std::vector<std::uint8_t>& in) {
    std::vector<std::uint8_t> out;
    out.reserve(in.size() / 2 + 64);
    const std::size_t n = in.size();
    auto put32 = [&out](std::size_t v) {
        const std::uint32_t w = static_cast<std::uint32_t>(v);
        out.insert(out.end(), reinterpret_cast<const std::uint8_t*>(&w), reinterpret_cast<const std::uint8_t*>(&w) + 4);
    };
    auto emit = [&](std::size_t from, std::size_t to, std::size_t zeros) {
        put32(to - from);
        out.insert(out.end(), in.begin() + static_cast<std::ptrdiff_t>(from), in.begin() + static_cast<std::ptrdiff_t>(to));
        put32(zeros);
    };
    std::size_t i = 0, lit = 0;
    while (i < n) {
        if (in[i] != 0) {
            ++i;
            continue;
        }
        std::size_t j = i;
        while (j + 8 <= n) {
            std::uint64_t w;
            std::memcpy(&w, in.data() + j, 8);
            if (w) break;
            j += 8;
        }
        while (j < n && in[j] == 0) ++j;
        if (j - i >= 64) {
            emit(lit, i, j - i);
            lit = j;
        }
        i = j;
    }
    emit(lit, n, 0);
    return out;
}
bool expand(const std::uint8_t* p, std::size_t n, std::uint64_t want, std::vector<std::uint8_t>& out) {
    out.clear();
    out.reserve(static_cast<std::size_t>(want));
    std::size_t i = 0;
    while (i < n) {
        std::uint32_t lit, zero;
        if (n - i < 4) return false;
        std::memcpy(&lit, p + i, 4);
        i += 4;
        if (n - i < lit) return false;
        out.insert(out.end(), p + i, p + i + lit);
        i += lit;
        if (n - i < 4) return false;
        std::memcpy(&zero, p + i, 4);
        i += 4;
        if (out.size() + zero > want) return false;
        out.resize(out.size() + zero, 0);
    }
    return out.size() == want;
}

bool header_ok(const StateHeader& h, std::string& error) {
    const StateHeader ref;
    if (std::memcmp(h.magic, ref.magic, sizeof ref.magic) != 0) {
        error = "not a p3fes machine state";
        return false;
    }
    if (h.version != kStateVersion || h.header_bytes != sizeof(StateHeader)) {
        error = "machine state version " + std::to_string(h.version) + " (this build reads version " +
                std::to_string(kStateVersion) + ")";
        return false;
    }
    return true;
}

} // namespace

bool write_state_file(const std::string& path, StateHeader h, const std::vector<std::uint8_t>& payload, std::string& error) {
    const std::vector<std::uint8_t> stored = squeeze(payload);
    h.payload_bytes = payload.size();
    h.payload_hash = state_hash(payload.data(), payload.size());
    h.stored_bytes = stored.size();
    const std::string tmp = path + ".tmp";
    std::FILE* f = std::fopen(tmp.c_str(), "wb");
    if (!f) {
        error = "cannot write " + tmp;
        return false;
    }
    bool ok = std::fwrite(&h, sizeof h, 1, f) == 1 && std::fwrite(stored.data(), 1, stored.size(), f) == stored.size();
    ok = std::fclose(f) == 0 && ok;
    if (!ok || !MoveFileExA(tmp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING)) {
        std::remove(tmp.c_str());
        error = "cannot write " + path;
        return false;
    }
    return true;
}

bool read_state_header(const std::string& path, StateHeader& h, std::string& error) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) {
        error = "cannot open " + path;
        return false;
    }
    const bool got = std::fread(&h, sizeof h, 1, f) == 1;
    std::fclose(f);
    if (!got) {
        error = path + ": too short for a machine state";
        return false;
    }
    return header_ok(h, error);
}

bool read_state_file(const std::string& path, StateHeader& h, std::vector<std::uint8_t>& payload, std::string& error) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) {
        error = "cannot open " + path;
        return false;
    }
    bool ok = std::fread(&h, sizeof h, 1, f) == 1 && header_ok(h, error);
    std::vector<std::uint8_t> stored;
    if (ok) {
        stored.resize(static_cast<std::size_t>(h.stored_bytes));
        ok = std::fread(stored.data(), 1, stored.size(), f) == stored.size();
        if (!ok) error = path + ": truncated";
    }
    std::fclose(f);
    if (!ok) {
        if (error.empty()) error = path + ": not a p3fes machine state";
        return false;
    }
    if (!expand(stored.data(), stored.size(), h.payload_bytes, payload) ||
        state_hash(payload.data(), payload.size()) != h.payload_hash) {
        error = path + ": payload damaged (hash mismatch)";
        return false;
    }
    return true;
}

} // namespace p3fes
