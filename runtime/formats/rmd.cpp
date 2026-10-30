#include "p3fes/formats/rmd.h"

namespace p3fes::formats {

namespace rw {

std::string_view type_name(u32 type) {
    switch (type) {
    case kStruct: return "Struct";
    case kString: return "String";
    case kExtension: return "Extension";
    case kTexture: return "Texture";
    case kMaterial: return "Material";
    case kMaterialList: return "MaterialList";
    case kFrameList: return "FrameList";
    case kGeometry: return "Geometry";
    case kClump: return "Clump";
    case kAtomic: return "Atomic";
    case kTextureNative: return "TextureNative";
    case kTexDictionary: return "TexDictionary";
    case kGeometryList: return "GeometryList";
    case kAnimAnimation: return "AnimAnimation";
    case kUvAnimDict: return "UVAnimDict";
    case kHAnimPlugin: return "HAnimPLG";
    case 0x11D: return "SkinPLG";
    case 0x120: return "BinMeshPLG";
    case 0x510: return "NativeDataPLG";
    case kAtlusSceneTag: return "AtlusSceneTag";
    default: return is_atlus(type) ? "AtlusChunk" : "?";
    }
}

// Chunk types whose payload is a sequence of child chunks.
bool is_container(u32 type) {
    switch (type) {
    case kExtension: case kTexture: case kMaterial: case kMaterialList: case kFrameList:
    case kGeometry: case kClump: case kAtomic: case kTextureNative: case kTexDictionary:
    case kGeometryList: case kAnimAnimation: case kUvAnimDict:
        return true;
    default:
        return false;
    }
}

}  // namespace rw

namespace {

bool plausible_library_id(u32 lib) {
    if (lib == rw::kAtlusLibraryId) return true;
    const u32 ver = rw::version(lib);
    return ver >= 0x30000 && ver < 0x40000;
}

bool read_header(Bytes buf, std::size_t off, std::size_t end, RwChunk& c) {
    if (off + 12 > end) return false;
    c.type = ld_u32le(buf, off);
    c.size = ld_u32le(buf, off + 4);
    c.library_id = ld_u32le(buf, off + 8);
    c.offset = off;
    if (c.type == 0 || c.type == 0xFFFFFFFFu) return false;
    if (!plausible_library_id(c.library_id)) return false;
    return c.size <= end - off - 12;
}

// Walks [off, end). Returns false when the walk stopped early (corrupt header).
bool walk(Bytes buf, std::size_t off, std::size_t end, u32 depth, u32 parent, RwStream& out,
          std::size_t& consumed) {
    while (off < end) {
        RwChunk c;
        if (!read_header(buf, off, end, c)) {
            // Padding to a 16-byte boundary (zero or junk) is allowed between
            // chunks; accept it only if a plausible header follows.
            const std::size_t aligned = align_up(off, 16);
            RwChunk probe;
            if (aligned > off && aligned < end && read_header(buf, aligned, end, probe)) {
                out.padding_bytes += aligned - off;
                off = aligned;
                continue;
            }
            // Trailing zero fill up to `end` is tolerated silently.
            bool all_zero = true;
            for (std::size_t i = off; i < end && all_zero; ++i) all_zero = buf[i] == std::byte{0};
            consumed = all_zero ? end : off;
            return all_zero;
        }
        c.depth = depth;
        c.parent = parent;
        const u32 index = static_cast<u32>(out.chunks.size());
        out.chunks.push_back(c);
        const std::size_t payload = c.payload_offset();
        const std::size_t child_end = c.end();
        if (rw::is_container(c.type) && c.size >= 12) {
            std::size_t child_consumed = 0;
            const std::size_t before = out.chunks.size();
            if (!walk(buf, payload, child_end, depth + 1, index, out, child_consumed)) {
                // Not actually a container of chunks: keep it as a leaf.
                out.chunks.resize(before);
            }
        }
        off = child_end;
    }
    consumed = end;
    return true;
}

}  // namespace

std::size_t RwStream::count(u32 type) const {
    std::size_t n = 0;
    for (const RwChunk& c : chunks) n += c.type == type;
    return n;
}

bool looks_like_rmd(Bytes buf) {
    RwChunk c;
    return read_header(buf, 0, buf.size(), c) &&
           (rw::is_atlus(c.type) || c.type == rw::kClump || c.type == rw::kTexDictionary ||
            c.type == rw::kAnimAnimation || c.type == rw::kUvAnimDict);
}

Result<RwStream> parse_rmd(Bytes buf) {
    if (buf.size() < 12) return {FormatError::Truncated, "first chunk header"};
    RwChunk first;
    if (!read_header(buf, 0, buf.size(), first)) {
        return {ld_u32le(buf, 4) > buf.size() ? FormatError::Overrun : FormatError::BadMagic,
                "first chunk header"};
    }
    RwStream s;
    std::size_t consumed = 0;
    walk(buf, 0, buf.size(), 0, 0xFFFFFFFFu, s, consumed);
    s.consumed = consumed;
    s.trailing_bytes = consumed < buf.size();
    return s;
}

}  // namespace p3fes::formats
