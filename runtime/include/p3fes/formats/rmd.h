// RenderWare binary stream chunk walker for Atlus .RMD models (3,234 files).
//
// Chunk header: u32 type, u32 size (payload bytes), u32 libraryID. RW 3.7
// chunks carry libraryID 0x1C020037 (0x1C02002D in 14 files); Atlus-custom
// chunks (type 0xF0F000xx) carry 0x40000000. Chunks are usually contiguous;
// after an Atlus chunk the next header may be padded to a 16-byte boundary with
// zero or junk bytes (observed only after 0xF0F000E0/0xF0F000F0). Container
// chunks hold a sequence of child chunks that exactly tiles the payload.
// Enumeration only; no geometry decoding (docs/FORMATS.md §5).
#pragma once

#include <functional>
#include <string_view>
#include <vector>

#include "p3fes/formats/bytes.h"
#include "p3fes/formats/result.h"

namespace p3fes::formats {

namespace rw {
inline constexpr u32 kStruct = 0x01, kString = 0x02, kExtension = 0x03, kTexture = 0x06,
                     kMaterial = 0x07, kMaterialList = 0x08, kFrameList = 0x0E, kGeometry = 0x0F,
                     kClump = 0x10, kAtomic = 0x14, kTextureNative = 0x15, kTexDictionary = 0x16,
                     kGeometryList = 0x1A, kAnimAnimation = 0x1B, kUvAnimDict = 0x2B,
                     kHAnimPlugin = 0x11E, kAtlusMask = 0xF0F00000u, kAtlusSceneTag = 0xF0F000F0u;
inline constexpr u32 kAtlusLibraryId = 0x40000000u;
inline constexpr u32 kP3LibraryId = 0x1C020037u;

// RW libraryID -> version (0x3xxxx for RW 3.x) and build.
constexpr u32 version(u32 lib) {
    if ((lib & 0xFFFF0000u) == 0) return lib << 8;  // pre-3.1 encoding: version only
    return ((lib >> 14) & 0x3FF00u) + 0x30000u + ((lib >> 16) & 0x3Fu);
}
constexpr u32 build(u32 lib) { return (lib & 0xFFFF0000u) ? (lib & 0xFFFFu) : 0; }
constexpr bool is_atlus(u32 type) { return (type & 0xFFFF0000u) == 0xF0F00000u; }
std::string_view type_name(u32 type);
}  // namespace rw

struct RwChunk {
    u32 type = 0;
    u32 size = 0;        // payload size
    u32 library_id = 0;
    std::size_t offset = 0;  // header offset in the buffer
    u32 depth = 0;
    u32 parent = 0xFFFFFFFFu;  // index into the chunk list, or none

    [[nodiscard]] std::size_t payload_offset() const { return offset + 12; }
    [[nodiscard]] std::size_t end() const { return offset + 12 + size; }
};

struct RwStream {
    std::vector<RwChunk> chunks;  // pre-order
    std::size_t consumed = 0;      // bytes covered by the top-level walk
    std::size_t padding_bytes = 0; // inter-chunk padding skipped at any depth
    bool trailing_bytes = false;   // consumed < buffer size (88 files per community survey)

    [[nodiscard]] Bytes payload(Bytes buf, const RwChunk& c) const {
        return subspan_or_empty(buf, c.payload_offset(), c.size);
    }
    [[nodiscard]] std::size_t count(u32 type) const;
};

// Walks the whole buffer. Fails only when the very first header is implausible;
// a corrupt later header truncates the walk and sets `trailing_bytes`.
Result<RwStream> parse_rmd(Bytes buf);
bool looks_like_rmd(Bytes buf);

}  // namespace p3fes::formats
