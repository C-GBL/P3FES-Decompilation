// Helpers for the VU1 tests: fixture paths, a tiny assembler for hand-built pairs, a capturing GIF sink.
//
// Tags used in test names (tests/ee convention):
//   (hand: VU User's Manual)                  expected value derived by hand from the manual's definition
//   (upstream behaviour, hardware-unverified) expected value is what ps2-web-recomp @ c0f476e does
#pragma once

#include <doctest.h>

#include "p3fes/vu1/vu1_interp.h"

#include <bit>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace p3fes::vu1::test {

inline std::filesystem::path repo_dir() {
#ifdef P3FES_REPO_DIR
    return P3FES_REPO_DIR;
#else
    return ".";
#endif
}

// The 114 gitignored microcode dumps (docs/ANALYSIS/09 §1); P3FES_VU1_DUMPS overrides. Read in place.
inline std::filesystem::path dumps_dir() {
    if (const char* env = std::getenv("P3FES_VU1_DUMPS"); env && *env) return env;
    return repo_dir() / "ida" / "logs" / "vu1";
}

inline std::optional<std::vector<u8>> read_file(const std::filesystem::path& p) {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    std::ifstream f(p, std::ios::binary);
    if (!f) return std::nullopt;
    const auto size = static_cast<std::size_t>(std::filesystem::file_size(p, ec));
    std::vector<u8> data(size);
    if (size && !f.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(size))) return std::nullopt;
    return data;
}

inline std::filesystem::path dump_path(u32 code_va) {
    char name[32];
    std::snprintf(name, sizeof name, "%08x.bin", code_va);
    return dumps_dir() / name;
}

inline u32 f2u(float f) { return std::bit_cast<u32>(f); }
inline float u2f(u32 v) { return std::bit_cast<float>(v); }

// ---- assembler ------------------------------------------------------------------------------------------------
// dest masks
inline constexpr u32 X = 8, Y = 4, Z = 2, W = 1, XYZW = 15, XYZ = 14, XYW = 13;
// broadcast / lane selectors
inline constexpr u32 bx = 0, by = 1, bz = 2, bw = 3;

inline constexpr u32 UNOP = kUpperNopWord;
inline constexpr u32 LNOP = kLowerNopWord;
inline constexpr u32 E_BIT = kFlagE;
inline constexpr u32 I_BIT = kFlagI;

inline constexpr u32 up(u32 funct, u32 fd, u32 fs, u32 ft, u32 dest) {
    return (dest << 21) | (ft << 16) | (fs << 11) | (fd << 6) | funct;
}
inline constexpr u32 up_sp(u32 index, u32 fs, u32 ft, u32 dest) { return up(0x3C | (index & 3), index >> 2, fs, ft, dest); }

// upper ops (operand order as in the assembly: fd, fs, ft)
inline constexpr u32 u_add(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x28, fd, fs, ft, d); }
inline constexpr u32 u_sub(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x2C, fd, fs, ft, d); }
inline constexpr u32 u_mul(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x2A, fd, fs, ft, d); }
inline constexpr u32 u_madd(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x29, fd, fs, ft, d); }
inline constexpr u32 u_max(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x2B, fd, fs, ft, d); }
inline constexpr u32 u_mini(u32 d, u32 fd, u32 fs, u32 ft) { return up(0x2F, fd, fs, ft, d); }
inline constexpr u32 u_addbc(u32 d, u32 fd, u32 fs, u32 ft, u32 bc) { return up(0x00 | bc, fd, fs, ft, d); }
inline constexpr u32 u_subbc(u32 d, u32 fd, u32 fs, u32 ft, u32 bc) { return up(0x04 | bc, fd, fs, ft, d); }
inline constexpr u32 u_msubbc(u32 d, u32 fd, u32 fs, u32 ft, u32 bc) { return up(0x0C | bc, fd, fs, ft, d); }
inline constexpr u32 u_mulbc(u32 d, u32 fd, u32 fs, u32 ft, u32 bc) { return up(0x18 | bc, fd, fs, ft, d); }
inline constexpr u32 u_mulq(u32 d, u32 fd, u32 fs) { return up(0x1C, fd, fs, 0, d); }
inline constexpr u32 u_muli(u32 d, u32 fd, u32 fs) { return up(0x1E, fd, fs, 0, d); }
inline constexpr u32 u_addi(u32 d, u32 fd, u32 fs) { return up(0x22, fd, fs, 0, d); }
inline constexpr u32 u_opmsub(u32 fd, u32 fs, u32 ft) { return up(0x2E, fd, fs, ft, XYZ); }
inline constexpr u32 u_mula(u32 d, u32 fs, u32 ft) { return up_sp(0x2A, fs, ft, d); }
inline constexpr u32 u_opmula(u32 fs, u32 ft) { return up_sp(0x2E, fs, ft, XYZ); }
inline constexpr u32 u_itof(u32 frac_index, u32 d, u32 ft, u32 fs) { return up_sp(0x10 + frac_index, fs, ft, d); }
inline constexpr u32 u_ftoi(u32 frac_index, u32 d, u32 ft, u32 fs) { return up_sp(0x14 + frac_index, fs, ft, d); }
inline constexpr u32 u_clip(u32 fs, u32 ft) { return up_sp(0x1F, fs, ft, XYZ); }

inline constexpr u32 lo(u32 opcode, u32 it, u32 is, u32 dest, s32 imm11) {
    return (opcode << 25) | (dest << 21) | (it << 16) | (is << 11) | (static_cast<u32>(imm11) & 0x7FFu);
}
inline constexpr u32 lo_int(u32 funct, u32 id, u32 is, u32 it) {
    return (0x40u << 25) | (it << 16) | (is << 11) | (id << 6) | funct;
}
inline constexpr u32 lo_sp(u32 index, u32 it, u32 is, u32 dest) {
    return (0x40u << 25) | (dest << 21) | (it << 16) | (is << 11) | ((index >> 2) << 6) | (0x3C | (index & 3));
}
inline constexpr u32 lo_sp_f(u32 index, u32 it, u32 is, u32 fsf, u32 ftf) { // DIV/RSQRT/MTIR/ERCPR lane fields
    return (0x40u << 25) | (ftf << 23) | (fsf << 21) | (it << 16) | (is << 11) | ((index >> 2) << 6) |
           (0x3C | (index & 3));
}

inline constexpr u32 l_lq(u32 d, u32 ft, u32 is, s32 imm) { return lo(0x00, ft, is, d, imm); }
inline constexpr u32 l_sq(u32 d, u32 fs, u32 it, s32 imm) { return lo(0x01, it, fs, d, imm); }
inline constexpr u32 l_ilw(u32 d, u32 it, u32 is, s32 imm) { return lo(0x04, it, is, d, imm); }
inline constexpr u32 l_isw(u32 d, u32 it, u32 is, s32 imm) { return lo(0x05, it, is, d, imm); }
inline constexpr u32 l_iaddiu(u32 it, u32 is, u32 imm15) {
    return (0x08u << 25) | ((imm15 & 0x7800u) << 10) | (it << 16) | (is << 11) | (imm15 & 0x7FFu);
}
inline constexpr u32 l_isubiu(u32 it, u32 is, u32 imm15) {
    return (0x09u << 25) | ((imm15 & 0x7800u) << 10) | (it << 16) | (is << 11) | (imm15 & 0x7FFu);
}
inline constexpr u32 l_fcset(u32 imm24) { return (0x11u << 25) | (imm24 & 0xFFFFFFu); }
inline constexpr u32 l_fcand(u32 imm24) { return (0x12u << 25) | (imm24 & 0xFFFFFFu); }
inline constexpr u32 l_fcor(u32 imm24) { return (0x13u << 25) | (imm24 & 0xFFFFFFu); }
inline constexpr u32 l_fmand(u32 it, u32 is) { return lo(0x1A, it, is, 0, 0); }
inline constexpr u32 l_fcget(u32 it) { return lo(0x1C, it, 0, 0, 0); }
inline constexpr u32 l_b(s32 imm11) { return lo(0x20, 0, 0, 0, imm11); }
inline constexpr u32 l_bal(u32 it, s32 imm11) { return lo(0x21, it, 0, 0, imm11); }
inline constexpr u32 l_jr(u32 is) { return lo(0x24, 0, is, 0, 0); }
inline constexpr u32 l_ibeq(u32 it, u32 is, s32 imm11) { return lo(0x28, it, is, 0, imm11); }
inline constexpr u32 l_ibne(u32 it, u32 is, s32 imm11) { return lo(0x29, it, is, 0, imm11); }
inline constexpr u32 l_ibltz(u32 is, s32 imm11) { return lo(0x2C, 0, is, 0, imm11); }
inline constexpr u32 l_ibgtz(u32 is, s32 imm11) { return lo(0x2D, 0, is, 0, imm11); }
inline constexpr u32 l_iblez(u32 is, s32 imm11) { return lo(0x2E, 0, is, 0, imm11); }
inline constexpr u32 l_ibgez(u32 is, s32 imm11) { return lo(0x2F, 0, is, 0, imm11); }
inline constexpr u32 l_iadd(u32 id, u32 is, u32 it) { return lo_int(0x30, id, is, it); }
inline constexpr u32 l_isub(u32 id, u32 is, u32 it) { return lo_int(0x31, id, is, it); }
inline constexpr u32 l_iaddi(u32 it, u32 is, s32 imm5) { return lo_int(0x32, static_cast<u32>(imm5) & 31u, is, it); }
inline constexpr u32 l_iand(u32 id, u32 is, u32 it) { return lo_int(0x34, id, is, it); }
inline constexpr u32 l_ior(u32 id, u32 is, u32 it) { return lo_int(0x35, id, is, it); }
inline constexpr u32 l_move(u32 d, u32 ft, u32 fs) { return lo_sp(0x30, ft, fs, d); }
inline constexpr u32 l_mr32(u32 d, u32 ft, u32 fs) { return lo_sp(0x31, ft, fs, d); }
inline constexpr u32 l_lqi(u32 d, u32 ft, u32 is) { return lo_sp(0x34, ft, is, d); }
inline constexpr u32 l_sqi(u32 d, u32 fs, u32 it) { return lo_sp(0x35, it, fs, d); }
inline constexpr u32 l_lqd(u32 d, u32 ft, u32 is) { return lo_sp(0x36, ft, is, d); }
inline constexpr u32 l_sqd(u32 d, u32 fs, u32 it) { return lo_sp(0x37, it, fs, d); }
inline constexpr u32 l_div(u32 fs, u32 fsf, u32 ft, u32 ftf) { return lo_sp_f(0x38, ft, fs, fsf, ftf); }
inline constexpr u32 l_sqrt(u32 ft, u32 ftf) { return lo_sp_f(0x39, ft, 0, 0, ftf); }
inline constexpr u32 l_rsqrt(u32 fs, u32 fsf, u32 ft, u32 ftf) { return lo_sp_f(0x3A, ft, fs, fsf, ftf); }
inline constexpr u32 l_waitq() { return lo_sp(0x3B, 0, 0, 0); }
inline constexpr u32 l_mtir(u32 it, u32 fs, u32 fsf) { return lo_sp_f(0x3C, it, fs, fsf, 0); }
inline constexpr u32 l_mfir(u32 d, u32 ft, u32 is) { return lo_sp(0x3D, ft, is, d); }
inline constexpr u32 l_ilwr(u32 d, u32 it, u32 is) { return lo_sp(0x3E, it, is, d); }
inline constexpr u32 l_iswr(u32 d, u32 it, u32 is) { return lo_sp(0x3F, it, is, d); }
inline constexpr u32 l_mfp(u32 d, u32 ft) { return lo_sp(0x64, ft, 0, d); }
inline constexpr u32 l_xtop(u32 it) { return lo_sp(0x68, it, 0, 0); }
inline constexpr u32 l_xitop(u32 it) { return lo_sp(0x69, it, 0, 0); }
inline constexpr u32 l_xgkick(u32 is) { return lo_sp(0x6C, 0, is, 0); }
inline constexpr u32 l_ercpr(u32 fs, u32 fsf) { return lo_sp_f(0x7A, 0, fs, fsf, 0); }

struct Pair {
    u32 hi;
    u32 lo;
};

// Program image: pairs in order, little-endian (lower word first).
inline std::vector<u8> image(std::initializer_list<Pair> pairs) {
    std::vector<u8> out;
    for (const Pair& p : pairs) {
        u8 b[8];
        std::memcpy(b, &p.lo, 4);
        std::memcpy(b + 4, &p.hi, 4);
        out.insert(out.end(), b, b + 8);
    }
    return out;
}

struct CaptureSink final : IGifSink {
    std::vector<std::vector<u128>> packets;
    void kick(std::span<const u128> qwords) override { packets.emplace_back(qwords.begin(), qwords.end()); }
    std::size_t total_qwords() const {
        std::size_t n = 0;
        for (const auto& p : packets) n += p.size();
        return n;
    }
};

// A heap interpreter with `pairs` loaded at byte offset `at` (the end of every hand program carries an E pair).
inline std::unique_ptr<VU1Interpreter> make_vu(std::initializer_list<Pair> pairs, IGifSink* sink = nullptr,
                                                u32 at = 0) {
    auto vu = std::make_unique<VU1Interpreter>(sink);
    const std::vector<u8> img = image(pairs);
    vu->load_micro(at, img);
    return vu;
}

inline void set_vf(VU1State& s, u32 r, float x, float y, float z, float w) {
    s.vf[r][0] = f2u(x);
    s.vf[r][1] = f2u(y);
    s.vf[r][2] = f2u(z);
    s.vf[r][3] = f2u(w);
}

inline void set_qword(VU1State& s, u32 index, u32 x, u32 y, u32 z, u32 w) {
    const u32 v[4] = {x, y, z, w};
    std::memcpy(s.data + (index & 1023u) * 16u, v, 16);
}

inline u32 data_word(const VU1State& s, u32 index, u32 lane) {
    u32 v;
    std::memcpy(&v, s.data + (index & 1023u) * 16u + lane * 4u, 4);
    return v;
}

} // namespace p3fes::vu1::test
