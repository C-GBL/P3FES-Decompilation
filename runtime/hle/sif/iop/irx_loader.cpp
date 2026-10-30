// IRX loader (irx_loader.h).
#include "irx_loader.h"

#include <algorithm>
#include <cstring>

#include "r3000.h"

namespace p3fes::hle::sif::iop {
namespace {

struct File {
    std::span<const u8> d;
    bool has(std::size_t off, std::size_t n) const { return off <= d.size() && n <= d.size() - off; }
    u32 u32_at(std::size_t off) const {
        u32 v = 0;
        if (has(off, 4)) std::memcpy(&v, d.data() + off, 4);
        return v;
    }
    u16 u16_at(std::size_t off) const {
        u16 v = 0;
        if (has(off, 2)) std::memcpy(&v, d.data() + off, 2);
        return v;
    }
};

struct Header {
    u16 type = 0;
    u32 phoff = 0, shoff = 0;
    u16 phentsize = 0, phnum = 0, shentsize = 0, shnum = 0, shstrndx = 0;
    u32 load_off = 0, load_filesz = 0, load_memsz = 0;
    u32 iopmod_off = 0, iopmod_size = 0;
};

bool parse_header(const File& f, Header& h, std::string& error) {
    if (f.d.size() < 52 || std::memcmp(f.d.data(), "\x7f" "ELF", 4) != 0) {
        error = "not an ELF file";
        return false;
    }
    if (f.d[4] != 1 || f.d[5] != 1) {
        error = "not a 32-bit little-endian ELF";
        return false;
    }
    h.type = f.u16_at(16);
    if (f.u16_at(18) != 8) {
        error = "not a MIPS ELF";
        return false;
    }
    if (h.type != 0xFF80u && h.type != 0xFF81u) {
        error = "e_type is not an IRX (0xFF80)";
        return false;
    }
    h.phoff = f.u32_at(28);
    h.shoff = f.u32_at(32);
    h.phentsize = f.u16_at(42);
    h.phnum = f.u16_at(44);
    h.shentsize = f.u16_at(46);
    h.shnum = f.u16_at(48);
    h.shstrndx = f.u16_at(50);
    bool have_load = false;
    for (u32 i = 0; i < h.phnum; ++i) {
        const std::size_t ph = static_cast<std::size_t>(h.phoff) + static_cast<std::size_t>(i) * h.phentsize;
        if (!f.has(ph, 32)) {
            error = "program header outside the file";
            return false;
        }
        const u32 ptype = f.u32_at(ph);
        if (ptype == 1 && !have_load) {
            have_load = true;
            h.load_off = f.u32_at(ph + 4);
            if (f.u32_at(ph + 8) != 0) {
                error = "PT_LOAD is not linked at 0";
                return false;
            }
            h.load_filesz = f.u32_at(ph + 16);
            h.load_memsz = f.u32_at(ph + 20);
        } else if (ptype == 0x70000080u && h.iopmod_off == 0) {  // PT_MIPS_IOPMOD: the same bytes as .iopmod
            h.iopmod_off = f.u32_at(ph + 4);
            h.iopmod_size = f.u32_at(ph + 16);
        }
    }
    if (h.iopmod_off == 0) {  // fall back to the section table
        const std::size_t strsh = static_cast<std::size_t>(h.shoff) + static_cast<std::size_t>(h.shstrndx) * h.shentsize;
        const u32 stroff = f.u32_at(strsh + 16);
        for (u32 i = 0; i < h.shnum; ++i) {
            const std::size_t sh = static_cast<std::size_t>(h.shoff) + static_cast<std::size_t>(i) * h.shentsize;
            const u32 name = f.u32_at(sh);
            const std::size_t at = static_cast<std::size_t>(stroff) + name;
            if (f.has(at, 8) && std::memcmp(f.d.data() + at, ".iopmod", 8) == 0) {
                h.iopmod_off = f.u32_at(sh + 16);
                h.iopmod_size = f.u32_at(sh + 20);
                break;
            }
        }
    }
    if (!have_load || !f.has(h.load_off, h.load_filesz) || h.load_memsz < h.load_filesz) {
        error = "no usable PT_LOAD";
        return false;
    }
    if (h.iopmod_off == 0 || !f.has(h.iopmod_off, 28)) {
        error = "no .iopmod";
        return false;
    }
    return true;
}

u32 image_size_of(const File& f, const Header& h) {
    const u32 text = f.u32_at(h.iopmod_off + 12), data = f.u32_at(h.iopmod_off + 16), bss = f.u32_at(h.iopmod_off + 20);
    return std::max(h.load_memsz, text + data + bss);
}

}  // namespace

std::optional<u32> irx_image_size(std::span<const u8> file, std::string& error) {
    const File f{file};
    Header h;
    if (!parse_header(f, h, error)) return std::nullopt;
    return image_size_of(f, h);
}

std::optional<IrxModule> load_irx(detail::IopRam& ram, std::span<const u8> file, u32 base, std::string& error) {
    const File f{file};
    Header h;
    if (!parse_header(f, h, error)) return std::nullopt;
    IrxModule m;
    m.base = base & 0x1FFFFFFFu;
    m.image_size = image_size_of(f, h);
    if ((m.base & 15u) != 0) {
        error = "load base is not 16-byte aligned";
        return std::nullopt;
    }
    u8* img = ram.at(m.base, m.image_size);
    if (!img) {
        error = "image does not fit in IOP RAM";
        return std::nullopt;
    }
    std::memset(img, 0, m.image_size);
    std::memcpy(img, file.data() + h.load_off, h.load_filesz);

    // .iopmod
    m.entry = m.base + f.u32_at(h.iopmod_off + 4);
    m.gp = m.base + f.u32_at(h.iopmod_off + 8);
    m.text_size = f.u32_at(h.iopmod_off + 12);
    m.data_size = f.u32_at(h.iopmod_off + 16);
    m.bss_size = f.u32_at(h.iopmod_off + 20);
    m.version = f.u16_at(h.iopmod_off + 24);
    for (std::size_t i = h.iopmod_off + 26; i < h.iopmod_off + h.iopmod_size && i < file.size() && file[i]; ++i)
        m.name.push_back(static_cast<char>(file[i]));

    // Relocations (REL sections; the linker emits them against section 0 = the whole image).
    auto word = [&](u32 off) -> u32 {
        u32 v = 0;
        if (off + 4 <= m.image_size) std::memcpy(&v, img + off, 4);
        return v;
    };
    auto put = [&](u32 off, u32 v) {
        if (off + 4 <= m.image_size) std::memcpy(img + off, &v, 4);
    };
    const bool v2 = h.type == 0xFF81u;  // never seen on this disc; kept for the reference's rule
    for (u32 i = 0; i < h.shnum; ++i) {
        const std::size_t sh = static_cast<std::size_t>(h.shoff) + static_cast<std::size_t>(i) * h.shentsize;
        if (!f.has(sh, 40) || f.u32_at(sh + 4) != 9) continue;  // SHT_REL
        const u32 off = f.u32_at(sh + 16), size = f.u32_at(sh + 20);
        if (!f.has(off, size)) {
            error = "relocation section outside the file";
            return std::nullopt;
        }
        const u32 count = size / 8;
        bool have_hi = false;
        u32 hi_at = 0, hi_word = 0;
        for (u32 k = 0; k < count; ++k) {
            const u32 at = f.u32_at(off + k * 8);
            const u32 type = f.u32_at(off + k * 8 + 4) & 0xFFu;
            if (at + 4 > m.image_size) {
                error = "relocation outside the image";
                return std::nullopt;
            }
            const u32 insn = word(at);
            switch (type) {
            case 2:  // R_MIPS_32
                put(at, insn + m.base);
                break;
            case 4:  // R_MIPS_26
                put(at, (insn & ~0x03FFFFFFu) | (((insn & 0x03FFFFFFu) + (m.base >> 2)) & 0x03FFFFFFu));
                break;
            case 5:  // R_MIPS_HI16: resolved with the LO16 that follows
                if (v2 && k + 1 < count) {
                    const u32 next = f.u32_at(off + (k + 1) * 8);
                    u32 value = static_cast<u32>(static_cast<s32>(static_cast<s16>(word(next) & 0xFFFFu))) + (insn << 16) + m.base;
                    if (value & 0x8000u) value += 0x10000u;
                    put(at, (insn & ~0xFFFFu) | (value >> 16));
                } else {
                    if (have_hi) {
                        error = "two R_MIPS_HI16 without a LO16 between them";
                        return std::nullopt;
                    }
                    have_hi = true;
                    hi_at = at;
                    hi_word = insn;
                }
                break;
            case 6: {  // R_MIPS_LO16
                const u32 lo = static_cast<u32>(static_cast<s32>(static_cast<s16>(insn & 0xFFFFu)));
                if (v2) {
                    put(at, (insn & ~0xFFFFu) | ((lo + m.base) & 0xFFFFu));
                } else if (have_hi) {
                    u32 value = lo + (hi_word << 16) + m.base;
                    put(at, (insn & ~0xFFFFu) | (value & 0xFFFFu));
                    if (value & 0x8000u) value += 0x10000u;
                    put(hi_at, (hi_word & ~0xFFFFu) | (value >> 16));
                    have_hi = false;
                } else {
                    put(at, (insn & ~0xFFFFu) | ((lo + m.base) & 0xFFFFu));  // an orphan LO16 (none on this disc)
                }
                break;
            }
            default:
                error = "unsupported relocation type " + std::to_string(type);
                return std::nullopt;
            }
            ++m.relocations[type];
        }
        if (have_hi) {
            error = "R_MIPS_HI16 without a following LO16";
            return std::nullopt;
        }
    }

    // Import / export tables (after relocation; the text segment holds them before the first function
    // on this disc's modules, but the scan covers the whole image).
    auto name8 = [&](u32 off) {
        std::string s;
        for (u32 i = 0; i < 8 && off + i < m.image_size && img[off + i]; ++i) s.push_back(static_cast<char>(img[off + i]));
        return s;
    };
    for (u32 a = 0; a + 20 <= m.image_size;) {
        const u32 w0 = word(a);
        if (w0 == kImportMagic && word(a + 4) == 0) {
            IrxImport imp;
            imp.table = m.base + a;
            imp.version = static_cast<u16>(word(a + 8));
            imp.library = name8(a + 12);
            u32 s = a + 20;
            for (; s + 8 <= m.image_size; s += 8) {
                const u32 j = word(s), li = word(s + 4);
                const bool stub = (j == 0x03E00008u || (j >> 26) == 2u || (j >> 26) == kHleOpcode) && (li & 0xFFFF0000u) == 0x24000000u;
                if (!stub) break;
                imp.ordinals.push_back(static_cast<u16>(li & 0xFFFFu));
                imp.stubs.push_back(m.base + s);
            }
            if (!imp.library.empty()) m.imports.push_back(std::move(imp));
            a = s + 8;  // the zero pair
            continue;
        }
        if (w0 == kExportMagic && word(a + 4) == 0) {
            IrxExport ex;
            ex.table = m.base + a;
            ex.version = static_cast<u16>(word(a + 8));
            ex.library = name8(a + 12);
            u32 s = a + 20;
            for (; s + 4 <= m.image_size && word(s) != 0; s += 4) ex.functions.push_back(word(s));
            if (!ex.library.empty()) m.exports.push_back(std::move(ex));
            a = s + 4;
            continue;
        }
        a += 4;
    }
    return m;
}

std::vector<UnresolvedImport> bind_imports(detail::IopRam& ram, IrxModule& m, ImportBinder& binder, u32 trap_id) {
    std::vector<UnresolvedImport> missing;
    for (const IrxImport& imp : m.imports) {
        for (std::size_t i = 0; i < imp.stubs.size(); ++i) {
            u8* p = ram.at(imp.stubs[i], 8);
            if (!p) continue;
            const ImportTarget t = binder.resolve(imp.library, imp.ordinals[i]);
            u32 w0 = 0;
            switch (t.kind) {
            case ImportTarget::Kind::Guest:
                w0 = 0x08000000u | ((t.value >> 2) & 0x03FFFFFFu);  // j target (delay slot: the li, harmless)
                break;
            case ImportTarget::Kind::Host:
                w0 = (kHleOpcode << 26) | (t.value & kHleIdMask);
                break;
            case ImportTarget::Kind::Unresolved:
                w0 = (kHleOpcode << 26) | (trap_id & kHleIdMask);
                missing.push_back({imp.library, imp.ordinals[i]});
                break;
            }
            std::memcpy(p, &w0, 4);
        }
    }
    return missing;
}

}  // namespace p3fes::hle::sif::iop
