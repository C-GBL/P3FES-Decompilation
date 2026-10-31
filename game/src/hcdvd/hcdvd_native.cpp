// Modernize layer 1 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of the game's CD wrappers
// (game/include/p3fes/game/files_native.h). Reached only while p3fes::native::files::service() is set
// (`--native files`); the faithful bodies call them at their swap point and are otherwise unchanged.
//
// What is *not* done here, on purpose: no SRD request, no libcdvd call, no SIF RPC, no ADXF handle. Guest-visible
// differences from a faithful load are confined to the CD layer's own state (README §7 "exclusion mask"): the
// ADXF / ADXSTM / ROFS handle pools and the SRD slot are never touched by a whole-file load, the dvCi handle gets no
// SRD (+28 stays 0) and its mode bytes are copied without a request, and the node's poll counter (+862) stays 0.
#include "p3fes/game/files_native.h"

#include <cstring>
#include <span>
#include <string>
#include <string_view>

#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_AddFile_00101e30(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

namespace {

constexpr u32 kSector = 2048;

u32 rd32(EEContext& ctx, u32 va) { return ctx.memory->read<u32>(va); }
void wr32(EEContext& ctx, u32 va, u32 v) { ctx.memory->write<u32>(va, v); }

// A NUL-terminated guest string of at most `max` bytes.
std::string guest_string(EEContext& ctx, u32 va, u32 max) {
    std::string s;
    const u8* p = ctx.memory->ram_ptr(va, 1);
    if (!p) return s;
    for (u32 i = 0; i < max; ++i) {
        const u8* q = ctx.memory->ram_ptr(va + i, 1);
        if (!q || *q == 0) break;
        s += static_cast<char>(*q);
    }
    return s;
}

bool iequals(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        char x = a[i], y = b[i];
        if (x >= 'a' && x <= 'z') x = static_cast<char>(x - 32);
        if (y >= 'a' && y <= 'z') y = static_cast<char>(y - 32);
        if (x != y) return false;
    }
    return true;
}

// The ROFS volumes kwlnInitMain mounts (ADXF_AddRofsVol): VOL = data.cvm, BGM = bgm.cvm, BTL = btl.cvm.
const char* volume_container(std::string_view vol) {
    if (iequals(vol, "BTL")) return "BTL.CVM";
    if (iequals(vol, "BGM")) return "BGM.CVM";
    return "DATA.CVM";
}

}  // namespace

bool hcdvd_native_load(EEContext& ctx, native::files::FileService& fs, u32 node) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // node +344 "VOL:NAME" (H_Cdvd_BuildVolumePaths), node +600 the directory ("\FIELD\").
    const std::string vol_file = guest_string(ctx, node + 344, 256);
    // node +600: the directory as H_Cdvd_SplitPath leaves it, with the volume prefix ("VOL:\FONT\SIZE12\"); the
    // CVM comes from +344's volume (BTL: for the battle directories).
    std::string dir = guest_string(ctx, node + 600, 256);
    if (const auto c = dir.find(':'); c != std::string::npos) dir.erase(0, c + 1);
    const auto colon = vol_file.find(':');
    const std::string_view vol = colon == std::string::npos ? std::string_view("VOL") : std::string_view(vol_file).substr(0, colon);
    const std::string_view name = colon == std::string::npos ? std::string_view(vol_file) : std::string_view(vol_file).substr(colon + 1);
    const std::string path = std::string(volume_container(vol)) + ":\\" + dir + "\\" + std::string(name);
    const auto f = fs.find(path);
    if (!f || f->size > 0x7FFFF800u) return false;
    const u32 size = static_cast<u32>(f->size);
    const u32 sectors = (size + kSector - 1) / kSector;
    wr32(ctx, node + 292, size);
    wr32(ctx, node + 280, size);
    // The buffer exactly as state 1 allocates it (H_Cdvd_Update 0x100A3C / 0x100A70): the heap hook at 0x960178.
    const bool archive = rd32(ctx, node + 336) != 0;
    a0 = (sectors << 11) + (archive ? 320u : 64u);
    a1 = 0x40000u;
    jalr(ctx, 0x100A90u, rd32(ctx, 0x960178u));
    const u32 raw = v0.u();
    if (raw == 0) return false;
    const u32 data = (raw + 63u) & ~63u;
    wr32(ctx, node + 276, raw);
    wr32(ctx, node + 272, data);
    u8* p = ctx.memory->ram_ptr(data, sectors * kSector);
    if (sectors && (!p || !fs.read(*f, 0, std::span<std::byte>(reinterpret_cast<std::byte*>(p), sectors * kSector), data))) {
        // As a failed faithful read (state 2 -> error): the buffer goes back unless the node has an owner at +8.
        if (rd32(ctx, node + 8) == 0) {
            a0 = raw;
            jalr(ctx, 0x100B48u, rd32(ctx, 0x96017Cu));
            wr32(ctx, node + 272, 0);
            wr32(ctx, node + 276, 0);
        }
        return false;
    }
    if (archive) {  // the PAK terminator after the data (0x100BB4 memset)
        if (u8* t = ctx.memory->ram_ptr(data + size, 256)) std::memset(t, 0, 256);
    }
    wr32(ctx, node + 12, 3);
    a0 = node + 8;
    jal(ctx, 0x100C18u, gen::fn_H_Cdvd_AddFile_00101e30);
    wr32(ctx, node + 12, 4);
    wr32(ctx, node + 340, 0);
    return true;
}

u32 dvci_native_read(EEContext& ctx, native::files::FileService& fs, u32 h, u32 nsct, u32 buf) {
    // The clamp and the mode bytes as dvCiReqRd 0x55A52C writes them (dvg_ci_cdrmode 0x7A2A70..72 -> +68..70).
    const s32 pos = static_cast<s32>(rd32(ctx, h + 12));
    const s32 left = static_cast<s32>(rd32(ctx, h + 8)) - pos;
    const s32 n = static_cast<s32>(nsct) < left ? static_cast<s32>(nsct) : left;
    for (u32 i = 0; i < 3; ++i) ctx.memory->write<u8>(h + 68 + i, ctx.memory->read<u8>(0x7A2A70u + i));
    wr32(ctx, h + 16, static_cast<u32>(n));
    wr32(ctx, h + 24, buf);
    wr32(ctx, h + 28, 0);
    bool ok = false;
    if (const auto f = fs.outer_at(rd32(ctx, h + 32))) {
        const u32 bytes = n > 0 ? static_cast<u32>(n) * kSector : 0u;
        u8* p = bytes ? ctx.memory->ram_ptr(buf, bytes) : nullptr;
        ok = bytes == 0 || (p && fs.read(*f, static_cast<u64>(pos) * kSector,
                                         std::span<std::byte>(reinterpret_cast<std::byte*>(p), bytes), buf));
    }
    if (ok) {  // dvCiExecHndl's "complete" (0x559EE8): +20 = n, +12 += n, state 1
        wr32(ctx, h + 20, static_cast<u32>(n));
        wr32(ctx, h + 12, static_cast<u32>(pos + n));
        ctx.memory->write<u8>(h + 2, 1);
    } else {  // its "error" (0x559ED8): state 3
        ctx.memory->write<u8>(h + 2, 3);
    }
    return static_cast<u32>(n);
}

u32 dvci_native_search(EEContext& ctx, native::files::FileService& fs, u32 fp, u32 name) {
    const auto o = fs.search(guest_string(ctx, name, 256));
    if (!o) return 0;
    u8* p = ctx.memory->ram_ptr(fp, 36);
    if (!p) return 0;
    // sceCdlFILE as cdvdfsv's search answer (srv_cdvdfsv.cpp encode_cdl_file / cdl_date_from_iso).
    std::memset(p, 0, 36);
    const u32 lsn = o->file.lsn, size = static_cast<u32>(o->file.size);
    std::memcpy(p + 0, &lsn, 4);
    std::memcpy(p + 4, &size, 4);
    std::memcpy(p + 8, o->identifier.data(), o->identifier.size() < 15 ? o->identifier.size() : 15);
    const u32 year = 1900u + o->recorded[0];
    p[24 + 7] = static_cast<u8>(year >> 8);
    p[24 + 6] = static_cast<u8>(year & 0xFFu);
    p[24 + 5] = o->recorded[1];
    p[24 + 4] = o->recorded[2];
    p[24 + 3] = o->recorded[3];
    p[24 + 2] = o->recorded[4];
    p[24 + 1] = o->recorded[5];
    return 1;
}

}  // namespace p3fes::game
