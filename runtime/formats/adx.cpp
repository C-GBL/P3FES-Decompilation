#include "p3fes/formats/adx.h"

#include <cstring>

namespace p3fes::formats {

bool is_adx(Bytes buf) {
    if (buf.size() < 0x14) return false;
    if (ld_u16be(buf, 0) != 0x8000) return false;
    const u16 coff = ld_u16be(buf, 2);
    // "(c)CRI" ends at copyright_offset + 4 and must fit the buffer.
    return coff >= 0x12 + 2 && in_bounds(buf, static_cast<std::size_t>(coff) - 2, 6) &&
           std::memcmp(buf.data() + coff - 2, "(c)CRI", 6) == 0;
}

Result<AdxInfo> parse_adx(Bytes buf) {
    Reader r(buf);
    AdxInfo info;
    AdxHeader& h = info.header;
    const u16 magic = r.u16be();
    h.copyright_offset = r.u16be();
    h.encoding = r.u8_();
    h.block_size = r.u8_();
    h.sample_bit_depth = r.u8_();
    h.channels = r.u8_();
    h.sample_rate = r.u32be();
    h.sample_count = r.u32be();
    h.highpass_cutoff = r.u16be();
    h.version = r.u8_();
    h.flags = r.u8_();
    if (r.failed()) return {FormatError::Truncated, "header (0x14 bytes)"};
    if (magic != 0x8000) return {FormatError::BadMagic, "0x8000"};
    if (h.block_size == 0 || h.channels == 0 || h.sample_bit_depth == 0)
        return {FormatError::BadHeader, "block size / channels / bit depth"};
    if (h.version != 3 && h.version != 4) return {FormatError::Unsupported, "version"};

    info.file_size = buf.size();
    const std::size_t data = h.data_offset();
    if (data > buf.size()) return {FormatError::Overrun, "copyright offset"};
    info.copyright_ok = h.copyright_offset >= 2 && in_bounds(buf, h.copyright_offset - 2, 6) &&
                        std::memcmp(buf.data() + h.copyright_offset - 2, "(c)CRI", 6) == 0;

    // Loop block: v3 at 0x14; v4 after a u32 pad and 4 bytes of decoder history
    // per channel (verified byte-consistent on stereo v4 files; mono v4 and any
    // v3 file with loop data were not present on this disc).
    const std::size_t loop_off = h.version == 3 ? 0x14 : 0x18 + 4u * h.channels;
    if (data >= loop_off + 0x18) {
        AdxLoop lp;
        lp.alignment_samples = ld_u32be(buf, loop_off);
        lp.enabled = ld_u32be(buf, loop_off + 4);
        lp.begin_sample = ld_u32be(buf, loop_off + 8);
        lp.begin_byte = ld_u32be(buf, loop_off + 12);
        lp.end_sample = ld_u32be(buf, loop_off + 16);
        lp.end_byte = ld_u32be(buf, loop_off + 20);
        h.loop = lp;
    }

    const u64 body = h.expected_body_bytes();
    info.body_fits = body <= buf.size() - data;
    if (info.body_fits) {
        const std::size_t end = data + static_cast<std::size_t>(body);
        info.end_marker = in_bounds(buf, end, 2) && ld_u16be(buf, end) == 0x8001;
    }
    return info;
}

}  // namespace p3fes::formats
