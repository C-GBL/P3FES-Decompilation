#include "host_file.h"

#include <windows.h>

#include <algorithm>
#include <cstring>

namespace p3fes::hle {

Result<std::unique_ptr<HostFile>> HostFile::open_with_share(const std::filesystem::path& path, unsigned long share) {
    HANDLE h = ::CreateFileW(path.c_str(), GENERIC_READ, share, nullptr, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, nullptr);
    if (h == INVALID_HANDLE_VALUE) return Error{FormatError::Truncated, "cannot open host file"};
    LARGE_INTEGER sz{};
    if (!::GetFileSizeEx(h, &sz) || sz.QuadPart < 0) {
        ::CloseHandle(h);
        return Error{FormatError::Truncated, "cannot query host file size"};
    }
    return std::unique_ptr<HostFile>(new HostFile(h, static_cast<u64>(sz.QuadPart)));
}

Result<std::unique_ptr<HostFile>> HostFile::open(const std::filesystem::path& path) {
    return open_with_share(path, FILE_SHARE_READ);
}

Result<std::unique_ptr<HostFile>> HostFile::open_shared(const std::filesystem::path& path) {
    return open_with_share(path, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
}

HostFile::~HostFile() {
    if (handle_ != nullptr && handle_ != INVALID_HANDLE_VALUE) ::CloseHandle(static_cast<HANDLE>(handle_));
}

Result<std::size_t> HostFile::read_at(u64 offset, std::span<std::byte> dst) const {
    if (offset > size_ || dst.size() > size_ - offset)
        return Error{FormatError::Truncated, "host file ends before the requested range"};
    // ReadFile takes a DWORD length; split very large requests.
    constexpr std::size_t kMaxChunk = std::size_t{1} << 30;
    std::size_t done = 0;
    while (done < dst.size()) {
        const std::size_t want = std::min(dst.size() - done, kMaxChunk);
        const u64 pos = offset + done;
        OVERLAPPED ov{};
        ov.Offset = static_cast<DWORD>(pos & 0xFFFFFFFFu);
        ov.OffsetHigh = static_cast<DWORD>(pos >> 32);
        DWORD got = 0;
        if (!::ReadFile(static_cast<HANDLE>(handle_), dst.data() + done, static_cast<DWORD>(want), &got, &ov) ||
            got != want)
            return Error{FormatError::Truncated, "host file read failed or was short"};
        done += want;
    }
    return done;
}

Result<std::size_t> HostFile::read_zero_fill(u64 offset, std::span<std::byte> dst) const {
    constexpr std::size_t kMaxChunk = std::size_t{1} << 30;
    std::size_t done = 0;
    while (done < dst.size()) {
        const std::size_t want = std::min(dst.size() - done, kMaxChunk);
        const u64 pos = offset + done;
        OVERLAPPED ov{};
        ov.Offset = static_cast<DWORD>(pos & 0xFFFFFFFFu);
        ov.OffsetHigh = static_cast<DWORD>(pos >> 32);
        DWORD got = 0;
        if (!::ReadFile(static_cast<HANDLE>(handle_), dst.data() + done, static_cast<DWORD>(want), &got, &ov)) {
            if (::GetLastError() != ERROR_HANDLE_EOF) return Error{FormatError::Truncated, "host file read failed"};
            got = 0;
        }
        done += got;
        if (got < want) break;  // end of file
    }
    if (done < dst.size()) std::memset(dst.data() + done, 0, dst.size() - done);
    return done;
}

}  // namespace p3fes::hle
