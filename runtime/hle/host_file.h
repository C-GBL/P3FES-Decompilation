// Read-only host file with positioned reads (Win32), used by the disc sources.
// Private to runtime/hle. Never writes, maps or caches the file.
#pragma once

#include <cstddef>
#include <filesystem>
#include <memory>
#include <span>

#include "p3fes/hle/disc_source.h"

namespace p3fes::hle {

class HostFile {
public:
    // Truncated if the file cannot be opened or its size cannot be queried.
    static Result<std::unique_ptr<HostFile>> open(const std::filesystem::path& path);
    // As open(), but other processes may write, rename or delete the file while it is open (the mods overlay: the
    // editor saves over a mod file the port is serving). size() stays the size at open.
    static Result<std::unique_ptr<HostFile>> open_shared(const std::filesystem::path& path);

    ~HostFile();
    HostFile(const HostFile&) = delete;
    HostFile& operator=(const HostFile&) = delete;

    u64 size() const { return size_; }

    // Reads exactly dst.size() bytes at `offset`. Ok value: dst.size(). Truncated on a short or
    // failed read (the range must lie inside the file).
    Result<std::size_t> read_at(u64 offset, std::span<std::byte> dst) const;

    // Reads up to dst.size() bytes at `offset` and zero-fills the rest of `dst` (the file may have been shortened
    // since it was opened). Ok value: bytes that came from the file. Truncated only on a failed read.
    Result<std::size_t> read_zero_fill(u64 offset, std::span<std::byte> dst) const;

private:
    HostFile(void* handle, u64 size) : handle_(handle), size_(size) {}
    static Result<std::unique_ptr<HostFile>> open_with_share(const std::filesystem::path& path, unsigned long share);

    void* handle_;  // HANDLE
    u64 size_;
};

}  // namespace p3fes::hle
