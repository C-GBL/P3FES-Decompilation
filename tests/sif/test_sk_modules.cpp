// ADR-0014 B-lite, increment 1 (docs/ANALYSIS/19 §4 phases 0-1): the R3000 interpreter on hand-written
// vectors; the IRX loader, the kernel HLE and the silent libsd on the six SK/libsd modules of the user's
// disc (extracted/disc/LIB31, P3FES_EXTRACTED overrides; skipped with a message when absent) -- every
// module parses, relocates, resolves its imports and runs its entry to completion; RegisterLibraryEntries
// registers the libraries in load order; SKSOUND's tick thread and hard timer exist and tick on virtual
// time; a SOUND_Send of COMSE.BD lands at SPU RAM 0x5010 byte for byte (and equals PCSX2's SPU2.bin at
// 0x15014 when that state is present); two runs are identical. Increment 2 (ADR-0014 milestones 1-2): the
// H_Sndcom flow re-enacted on the EE side against the IOP HLE in SkMode::Modules -- the loadfile requests load
// the six modules at PCSX2's addresses, SDRDRV's bind reports the module's own server data / buffer, the heap
// RPC hands out PCSX2's addresses, every Bind / Control / Send is answered by the IRX code, MODSESQ's track ids
// come back, and the first SESQ_Control play keys SPU2 voices that make the mix non-silent. Increment 3 (milestone
// 3): the longest COMSE SE runs out by itself and, stopped while it sounds, releases its voice (KOFF, back to 0 active);
// SOUND_Control 0x80 sets core 1's MVOL to (value x 129) & 0x7FFF through libsd; an SE census (skipped by default).
#include <doctest.h>

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "iop_core.h"
#include "iop_kernel_hle.h"
#include "sif_harness.h"
#include "irx_loader.h"
#include "libsd_hle.h"
#include "p3fes/audio/audio_sink.h"
#include "p3fes/audio/spu2_voice.h"
#include "r3000.h"

namespace {

using namespace p3fes;
using namespace p3fes::hle::sif;
using namespace p3fes::hle::sif::iop;

std::filesystem::path extracted_dir() {
    if (const char* env = std::getenv("P3FES_EXTRACTED"); env && *env) return env;
    return P3FES_EXTRACTED_DIR;
}

std::optional<std::vector<u8>> read_file(const std::filesystem::path& p) {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(p, ec)) return std::nullopt;
    std::ifstream f(p, std::ios::binary);
    if (!f) return std::nullopt;
    std::vector<u8> d(static_cast<std::size_t>(std::filesystem::file_size(p, ec)));
    if (!d.empty() && !f.read(reinterpret_cast<char*>(d.data()), static_cast<std::streamsize>(d.size()))) return std::nullopt;
    return d;
}

// The six modules in the order kwlnInitPS2Systems loads them (docs/ANALYSIS/12 §1: 8 SDRDRV, 9 MODHSYN,
// 11 MODSESQ, 12 SKSOUND, 13 SKHSYNTH, 15 SKSESQ; MODMSIN between them is not part of the SFX path).
struct ModuleSpec {
    const char* file;
    const char* library;      // export-table name
    const char* iopmod_name;
    u32 text, data, bss;      // .iopmod sizes (study §2.1 text sizes)
};
constexpr ModuleSpec kModules[] = {
    {"SDRDRV.IRX", "sdrdrv", "sdr_driver", 0x1330, 0x1C0, 0x7D8},
    {"MODHSYN.IRX", "modhsyn", "SPU2_Synthesizer_Module", 0xBE40, 0x640, 0x4092},
    {"MODSESQ.IRX", "modsesq", "SE_Sequencer_Module", 0x2960, 0x210, 0x4},
    {"SKSOUND.IRX", "sksound", "StandardKit/Sound/Foundation", 0x15F0, 0x160, 0xB8},
    {"SKHSYNTH.IRX", "skhsynth", "StandardKit/Sound/HardwareSynthesizer", 0x1600, 0x160, 0xF4},
    {"SKSESQ.IRX", "sksesq", "StandardKit/Sound/SE_Seq_Player", 0x1410, 0x5D0, 0x54},  // args: maxtrack=16, maxentry=16 (load_all)
};
constexpr std::size_t kModuleCount = sizeof kModules / sizeof kModules[0];

struct Stack {
    detail::IopRam ram;
    LibsdHle sd;
    IopKernel k{ram, sd};
    std::vector<LoadedIrx> loaded;
    std::string error;
    bool load_all() {
        for (const ModuleSpec& m : kModules) {
            const auto file = read_file(extracted_dir() / "disc" / "LIB31" / m.file);
            if (!file) {
                error = std::string("missing ") + m.file;
                return false;
            }
            const std::string_view args = std::strcmp(m.file, "SKSESQ.IRX") == 0 ? std::string_view("maxtrack=16\0maxentry=16\0", 24) : std::string_view();
            auto r = k.load_module(*file, std::string("cdrom0:\\LIB31\\") + m.file + ";1", args, error);
            if (!r) return false;
            loaded.push_back(*r);
        }
        return true;
    }
    const LoadedIrx* module(const char* library) const {
        for (const LoadedIrx& m : loaded)
            for (const IrxExport& e : m.info.exports)
                if (e.library == library) return &m;
        return nullptr;
    }
};

bool have_modules() {
    std::error_code ec;
    return std::filesystem::is_regular_file(extracted_dir() / "disc" / "LIB31" / "SKSOUND.IRX", ec);
}

// ---- a tiny assembler for the vectors ----------------------------------------------------------------
constexpr u32 R(u32 op, u32 rs, u32 rt, u32 rd, u32 sa, u32 fn) { return (op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | fn; }
constexpr u32 I(u32 op, u32 rs, u32 rt, u32 imm) { return (op << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFFu); }
constexpr u32 J(u32 op, u32 target) { return (op << 26) | ((target >> 2) & 0x03FFFFFFu); }
constexpr u32 kNop = 0;
constexpr u32 kJrRa = R(0, 31, 0, 0, 0, 8);
enum : u32 { zero, at, v0, v1, a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7, s0, s1, s2, s3, s4, s5, s6, s7, t8, t9, k0, k1, gp, sp, fp, ra };

struct Cpu {
    detail::IopRam ram;
    R3000 cpu{ram};
    static constexpr u32 kCode = 0x1000;
    // Places `words` at kCode, sets ra to the sentinel and runs until it returns.
    R3000::Result run(const std::vector<u32>& words, u64 budget = 10000) {
        for (std::size_t i = 0; i < words.size(); ++i) cpu.write32(kCode + static_cast<u32>(4 * i), words[i]);
        cpu.state().r[ra] = kExitSentinel;
        cpu.state().r[sp] = 0x1F0000;
        cpu.state().pc = kCode;
        cpu.state().npc = kCode + 4;
        return cpu.run(budget);
    }
    u32 r(u32 i) const { return cpu.state().r[i]; }
};

}  // namespace

TEST_CASE("R3000: arithmetic, logic, shifts and set-on-less-than") {
    Cpu c;
    const auto res = c.run({
        I(0x09, zero, t0, 0xFFFF),          // addiu t0, zero, -1
        I(0x09, t0, t1, 0x0005),            // addiu t1, t0, 5        -> 4
        R(0, t0, t1, t2, 0, 0x21),          // addu t2, t0, t1        -> 3
        R(0, t1, t0, t3, 0, 0x23),          // subu t3, t1, t0        -> 5
        I(0x0F, zero, t4, 0x1234),          // lui t4, 0x1234
        I(0x0D, t4, t4, 0x5678),            // ori t4, t4, 0x5678     -> 0x12345678
        I(0x0C, t4, t5, 0xF0F0),            // andi t5, t4, 0xF0F0    -> 0x5070
        I(0x0E, t4, t6, 0xFFFF),            // xori t6, t4, 0xFFFF    -> 0x1234A987
        R(0, t4, t0, t7, 0, 0x24),          // and t7, t4, t0         -> 0x12345678
        R(0, t4, t5, s0, 0, 0x25),          // or s0, t4, t5          -> 0x1234F6F8
        R(0, t4, t4, s1, 0, 0x26),          // xor s1, t4, t4         -> 0
        R(0, zero, t4, s2, 0, 0x27),        // nor s2, zero, t4       -> ~0x12345678
        R(0, 0, t4, s3, 4, 0x00),           // sll s3, t4, 4          -> 0x23456780
        R(0, 0, t0, s4, 4, 0x02),           // srl s4, t0, 4          -> 0x0FFFFFFF
        R(0, 0, t0, s5, 4, 0x03),           // sra s5, t0, 4          -> 0xFFFFFFFF
        I(0x09, zero, s6, 36),              // addiu s6, zero, 36  (shift amount & 31 = 4)
        R(0, s6, t4, s7, 0, 0x04),          // sllv s7, t4, s6        -> 0x23456780
        R(0, s6, t4, t8, 0, 0x06),          // srlv t8, t4, s6        -> 0x01234567
        R(0, s6, t0, t9, 0, 0x07),          // srav t9, t0, s6        -> 0xFFFFFFFF
        R(0, t0, t1, k0, 0, 0x2A),          // slt k0, t0, t1         -> 1 (-1 < 4)
        R(0, t0, t1, k1, 0, 0x2B),          // sltu k1, t0, t1        -> 0
        I(0x0A, t0, a0, 0),                 // slti a0, t0, 0         -> 1
        I(0x0B, t0, a1, 0xFFFF),            // sltiu a1, t0, -1       -> 0 (equal)
        I(0x08, t1, a2, 0xFFFE),            // addi a2, t1, -2        -> 2
        I(0x09, zero, zero, 0x1234),        // addiu zero, zero, x    -> $0 stays 0
        kJrRa, kNop,
    });
    CHECK_MESSAGE(res.stop == R3000::Stop::Sentinel, res.what << " at " << res.pc);
    CHECK(c.r(t0) == 0xFFFFFFFFu);
    CHECK(c.r(t1) == 4u);
    CHECK(c.r(t2) == 3u);
    CHECK(c.r(t3) == 5u);
    CHECK(c.r(t4) == 0x12345678u);
    CHECK(c.r(t5) == 0x5070u);
    CHECK(c.r(t6) == 0x1234A987u);
    CHECK(c.r(t7) == 0x12345678u);
    CHECK(c.r(s0) == 0x12345678u);  // 0x5070 is a subset of 0x5678
    CHECK(c.r(s1) == 0u);
    CHECK(c.r(s2) == ~0x12345678u);
    CHECK(c.r(s3) == 0x23456780u);
    CHECK(c.r(s4) == 0x0FFFFFFFu);
    CHECK(c.r(s5) == 0xFFFFFFFFu);
    CHECK(c.r(s7) == 0x23456780u);
    CHECK(c.r(t8) == 0x01234567u);
    CHECK(c.r(t9) == 0xFFFFFFFFu);
    CHECK(c.r(k0) == 1u);
    CHECK(c.r(k1) == 0u);
    CHECK(c.r(a0) == 1u);
    CHECK(c.r(a1) == 0u);
    CHECK(c.r(a2) == 2u);
    CHECK(c.r(zero) == 0u);
    CHECK(c.cpu.instructions() == 27);
}

TEST_CASE("R3000: branches and jumps execute their delay slot; link registers hold pc + 8") {
    Cpu c;
    // B(): a branch at `from` to `to` (offset relative to the delay-slot address).
    auto B = [](u32 op, u32 rs, u32 rt, u32 from, u32 to) { return I(op, rs, rt, static_cast<u32>(static_cast<s32>(to - (from + 4)) >> 2)); };
    c.cpu.state().r[s1] = 0x1070;
    const auto res = c.run({
        R(0, ra, 0, s6, 0, 0x21),                 // 0x1000: s6 = ra (the sentinel)
        B(0x04, zero, zero, 0x1004, 0x1018),      // 0x1004: beq zero, zero -> 0x1018
        I(0x09, zero, t0, 1),                     // 0x1008: slot: t0 = 1
        I(0x09, zero, t0, 99),                    // 0x100C: skipped
        I(0x09, zero, t0, 98),                    // 0x1010: skipped
        I(0x09, zero, t0, 97),                    // 0x1014: skipped
        B(0x05, t0, zero, 0x1018, 0x1024),        // 0x1018: bne t0, zero -> 0x1024 (taken)
        I(0x09, zero, t1, 2),                     // 0x101C: slot: t1 = 2
        I(0x09, zero, t1, 99),                    // 0x1020: skipped
        B(0x06, t0, 0, 0x1024, 0x1030),           // 0x1024: blez t0 (not taken: t0 = 1)
        I(0x09, zero, t2, 3),                     // 0x1028: slot: t2 = 3
        I(0x09, zero, t3, 4),                     // 0x102C: t3 = 4
        B(0x07, t0, 0, 0x1030, 0x103C),           // 0x1030: bgtz t0 -> 0x103C (taken)
        I(0x09, zero, t4, 5),                     // 0x1034: slot: t4 = 5
        I(0x09, zero, t4, 99),                    // 0x1038: skipped
        J(0x03, 0x1054),                          // 0x103C: jal 0x1054 (ra = 0x1044)
        I(0x09, zero, t5, 6),                     // 0x1040: slot: t5 = 6
        B(0x01, t0, 0, 0x1044, 0x1050),           // 0x1044: bltz t0 (not taken)
        I(0x09, zero, t6, 7),                     // 0x1048: slot: t6 = 7
        J(0x02, 0x1064),                          // 0x104C: j 0x1064
        I(0x09, zero, t7, 8),                     // 0x1050: slot: t7 = 8
        kJrRa,                                    // 0x1054: subroutine: jr ra (-> 0x1044)
        I(0x09, zero, s0, 9),                     // 0x1058: slot: s0 = 9
        kNop,                                     // 0x105C
        kNop,                                     // 0x1060
        R(0, s1, 0, s3, 0, 9),                    // 0x1064: jalr s3, s1 (-> 0x1070; s3 = 0x106C)
        I(0x09, zero, s2, 10),                    // 0x1068: slot: s2 = 10
        R(0, s6, 0, 0, 0, 8),                     // 0x106C: jr s6 (back to the sentinel)
        I(0x09, zero, s4, 11),                    // 0x1070: slot of jr s6 is only reached via jr s3 below... see next
        R(0, s3, 0, 0, 0, 8),                     // 0x1074: (unused)
    });
    // Note on 0x1070: jalr lands at 0x1070 = `addiu s4, 11`, then 0x1074 `jr s3` -> 0x106C `jr s6` whose
    // delay slot is 0x1070 again (s4 = 11 twice), then the sentinel.
    CHECK_MESSAGE(res.stop == R3000::Stop::Sentinel, res.what << " at " << res.pc);
    CHECK(c.r(t0) == 1u);
    CHECK(c.r(t1) == 2u);
    CHECK(c.r(t2) == 3u);
    CHECK(c.r(t3) == 4u);
    CHECK(c.r(t4) == 5u);
    CHECK(c.r(t5) == 6u);
    CHECK(c.r(t6) == 7u);
    CHECK(c.r(t7) == 8u);
    CHECK(c.r(s0) == 9u);
    CHECK(c.r(s2) == 10u);
    CHECK(c.r(s3) == 0x106Cu);
    CHECK(c.r(s4) == 11u);
    CHECK(c.r(ra) == 0x1044u);
    // bltzal / bgezal link even when not taken: s0 = ra after a not-taken bltzal at 0x1004 = 0x100C.
    Cpu d;
    const auto lk = d.run({R(0, ra, 0, s1, 0, 0x21), I(0x01, zero, 0x10, 1), kNop, R(0, ra, 0, s0, 0, 0x21), R(0, s1, 0, 0, 0, 8), kNop});
    CHECK(lk.stop == R3000::Stop::Sentinel);
    CHECK(d.r(s0) == 0x100Cu);
    // Backward branch: a counted loop of 5 iterations.
    Cpu e;
    const auto lp = e.run({
        I(0x09, zero, t0, 5),                     // 0x1000: t0 = 5
        I(0x09, t0, t0, 0xFFFF),                  // 0x1004: loop: t0 -= 1
        B(0x05, t0, zero, 0x1008, 0x1004),        // 0x1008: bne t0, zero -> 0x1004
        I(0x09, t1, t1, 1),                       // 0x100C: slot: t1 += 1
        kJrRa, kNop,
    });
    CHECK(lp.stop == R3000::Stop::Sentinel);
    CHECK(e.r(t0) == 0u);
    CHECK(e.r(t1) == 5u);
}

TEST_CASE("R3000: loads and stores, sign extension and the unaligned merges") {
    Cpu c;
    c.cpu.write32(0x2000, 0x8899AABBu);
    c.cpu.write32(0x2004, 0xCCDDEEFFu);
    const auto res = c.run({
        I(0x0F, zero, t0, 0), I(0x0D, t0, t0, 0x2000),  // t0 = 0x2000
        I(0x20, t0, t1, 0),      // lb  t1, 0(t0)  -> 0xFFFFFFBB
        I(0x24, t0, t2, 0),      // lbu t2, 0(t0)  -> 0xBB
        I(0x21, t0, t3, 0),      // lh  t3, 0(t0)  -> 0xFFFFAABB
        I(0x25, t0, t4, 2),      // lhu t4, 2(t0)  -> 0x8899
        I(0x23, t0, t5, 4),      // lw  t5, 4(t0)  -> 0xCCDDEEFF
        I(0x0F, zero, t6, 0x1111), I(0x0D, t6, t6, 0x2222),  // t6 = 0x11112222
        I(0x2B, t0, t6, 8),      // sw  t6, 8(t0)
        I(0x29, t0, t6, 12),     // sh  t6, 12(t0)  -> 0x2222 at 0x200C
        I(0x28, t0, t6, 14),     // sb  t6, 14(t0)  -> 0x22 at 0x200E
        I(0x09, zero, t7, 0),    // t7 = 0
        I(0x22, t0, t7, 1),      // lwl t7, 1(t0): bytes 0..1 of the word -> high half: 0xAABB0000
        I(0x26, t0, t7, 6),      // lwr t7, 6(t0): bytes 2..3 of 0x2004 -> low half: 0xAABBCCDD
        I(0x0F, zero, s0, 0xA1B2), I(0x0D, s0, s0, 0xC3D4),  // s0 = 0xA1B2C3D4
        I(0x2A, t0, s0, 17),     // swl s0, 17(t0): word 0x2010 bytes 0..1 <- high half (0xA1B2) -> 0x0000A1B2
        I(0x2E, t0, s0, 22),     // swr s0, 22(t0): word 0x2014 bytes 2..3 <- low half (0xC3D4) -> 0xC3D40000
        kJrRa, kNop,
    });
    CHECK_MESSAGE(res.stop == R3000::Stop::Sentinel, res.what << " at " << res.pc);
    CHECK(c.r(t1) == 0xFFFFFFBBu);
    CHECK(c.r(t2) == 0xBBu);
    CHECK(c.r(t3) == 0xFFFFAABBu);
    CHECK(c.r(t4) == 0x8899u);
    CHECK(c.r(t5) == 0xCCDDEEFFu);
    CHECK(c.cpu.read32(0x2008) == 0x11112222u);
    CHECK(c.cpu.read16(0x200C) == 0x2222u);
    CHECK(c.cpu.read8(0x200E) == 0x22u);
    CHECK(c.r(t7) == 0xAABBCCDDu);
    CHECK(c.cpu.read32(0x2010) == 0x0000A1B2u);
    CHECK(c.cpu.read32(0x2014) == 0xC3D40000u);
    // A misaligned lw traps and names the address.
    Cpu d;
    const auto bad = d.run({I(0x09, zero, t0, 0x2002), I(0x23, t0, t1, 0), kJrRa, kNop});
    CHECK(bad.stop == R3000::Stop::Trap);
    CHECK(bad.pc == 0x1004u);
    CHECK(bad.what.find("misaligned") != std::string::npos);
}

TEST_CASE("R3000: mult/div and the HI/LO pipe") {
    Cpu c;
    const auto res = c.run({
        I(0x09, zero, t0, 0xFFFD),      // t0 = -3
        I(0x09, zero, t1, 7),           // t1 = 7
        R(0, t0, t1, 0, 0, 0x18),       // mult  -3 * 7 = -21
        R(0, 0, 0, t2, 0, 0x10),        // mfhi t2 -> 0xFFFFFFFF
        R(0, 0, 0, t3, 0, 0x12),        // mflo t3 -> -21
        R(0, t0, t1, 0, 0, 0x19),       // multu 0xFFFFFFFD * 7 = 0x6FFFFFFEB
        R(0, 0, 0, t4, 0, 0x10),        // mfhi t4 -> 6
        R(0, 0, 0, t5, 0, 0x12),        // mflo t5 -> 0xFFFFFFEB
        R(0, t0, t1, 0, 0, 0x1A),       // div -3 / 7: lo 0, hi -3
        R(0, 0, 0, t6, 0, 0x10),        // mfhi t6 -> -3
        R(0, 0, 0, t7, 0, 0x12),        // mflo t7 -> 0
        R(0, t1, t0, 0, 0, 0x1B),       // divu 7 / 0xFFFFFFFD: lo 0, hi 7
        R(0, 0, 0, s0, 0, 0x10),        // mfhi s0 -> 7
        R(0, 0, 0, s1, 0, 0x12),        // mflo s1 -> 0
        R(0, t1, zero, 0, 0, 0x1A),     // div 7 / 0: lo -1, hi 7
        R(0, 0, 0, s2, 0, 0x10),        // s2 -> 7
        R(0, 0, 0, s3, 0, 0x12),        // s3 -> 0xFFFFFFFF
        R(0, t0, zero, 0, 0, 0x1A),     // div -3 / 0: lo 1, hi -3
        R(0, 0, 0, s4, 0, 0x12),        // s4 -> 1
        I(0x0F, zero, s5, 0x8000),      // s5 = INT_MIN
        R(0, s5, t0, 0, 0, 0x1A),       // div INT_MIN / -3 = 715827882 rem -2
        R(0, 0, 0, s6, 0, 0x12),        // s6
        R(0, 0, 0, s7, 0, 0x10),        // s7
        I(0x09, zero, t8, 0xFFFF),      // t8 = -1
        R(0, s5, t8, 0, 0, 0x1A),       // div INT_MIN / -1: lo INT_MIN, hi 0
        R(0, 0, 0, t9, 0, 0x12),        // t9 -> 0x80000000
        R(0, 0, 0, k0, 0, 0x10),        // k0 -> 0
        R(0, t1, 0, 0, 0, 0x11),        // mthi t1
        R(0, t0, 0, 0, 0, 0x13),        // mtlo t0
        R(0, 0, 0, a0, 0, 0x10),        // a0 -> 7
        R(0, 0, 0, a1, 0, 0x12),        // a1 -> -3
        kJrRa, kNop,
    });
    CHECK_MESSAGE(res.stop == R3000::Stop::Sentinel, res.what << " at " << res.pc);
    CHECK(c.r(t2) == 0xFFFFFFFFu);
    CHECK(c.r(t3) == static_cast<u32>(-21));
    CHECK(c.r(t4) == 6u);
    CHECK(c.r(t5) == 0xFFFFFFEBu);
    CHECK(c.r(t6) == static_cast<u32>(-3));
    CHECK(c.r(t7) == 0u);
    CHECK(c.r(s0) == 7u);
    CHECK(c.r(s1) == 0u);
    CHECK(c.r(s2) == 7u);
    CHECK(c.r(s3) == 0xFFFFFFFFu);
    CHECK(c.r(s4) == 1u);
    CHECK(c.r(s6) == 715827882u);
    CHECK(c.r(s7) == static_cast<u32>(-2));
    CHECK(c.r(t9) == 0x80000000u);
    CHECK(c.r(k0) == 0u);
    CHECK(c.r(a0) == 7u);
    CHECK(c.r(a1) == static_cast<u32>(-3));
}

TEST_CASE("R3000: host-call words return to ra with v0; reserved words and the step budget stop the run") {
    Cpu c;
    int calls = 0;
    const u32 id = c.cpu.register_host_call("test.add", [&](R3000& cpu) {
        ++calls;
        cpu.set_result(cpu.arg(0) + cpu.arg(1) + cpu.arg(4));  // a0 + a1 + the first stack argument
    });
    c.cpu.write32(0x1F0000 + 16, 1000);  // arg 4 at sp + 16
    const auto res = c.run({
        I(0x09, zero, a0, 5), I(0x09, zero, a1, 6),
        R(0, ra, 0, s6, 0, 0x21),              // s6 = ra (the sentinel; jal clobbers ra)
        J(0x03, 0x1020), kNop,                 // 0x100C: jal stub (ra = 0x1014)
        R(0, v0, 0, s0, 0, 0x21),              // 0x1014: s0 = v0 (addu s0, v0, zero)
        R(0, s6, 0, 0, 0, 8), kNop,            // jr s6
        (kHleOpcode << 26) | id, I(0x09, zero, zero, 7),  // 0x1020: the stub: host-call word + `li $0, 7`
    });
    CHECK_MESSAGE(res.stop == R3000::Stop::Sentinel, res.what << " at " << res.pc);
    CHECK(c.r(ra) == 0x1014u);
    CHECK(calls == 1);
    CHECK(c.r(s0) == 1011u);
    CHECK(c.cpu.host_calls_made() == 1);
    Cpu d;
    const auto bad = d.run({0x7C000000u, kJrRa, kNop});  // major opcode 0x1F: reserved on the R3000
    CHECK(bad.stop == R3000::Stop::Trap);
    CHECK(bad.word == 0x7C000000u);
    Cpu e;
    const auto loop = e.run({J(0x02, 0x1000), kNop}, 1000);
    CHECK(loop.stop == R3000::Stop::Budget);
    CHECK(e.cpu.instructions() == 1000);
    // A host call that requests a stop returns HostStop with pc already at ra.
    Cpu f;
    const u32 stop_id = f.cpu.register_host_call("test.stop", [](R3000& cpu) { cpu.request_stop(); });
    const auto hs = f.run({J(0x03, 0x1010), kNop, kJrRa, kNop, (kHleOpcode << 26) | stop_id, kNop});
    CHECK(hs.stop == R3000::Stop::HostStop);
    CHECK(hs.pc == 0x1008u);
}

// ---- the six modules -------------------------------------------------------------------------------------

TEST_CASE("IRX loader: the six SK/libsd modules parse, relocate and resolve every import") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    Stack s;
    REQUIRE_MESSAGE(s.load_all(), s.error);
    REQUIRE(s.loaded.size() == kModuleCount);
    REQUIRE_MESSAGE(s.k.fault().empty(), s.k.fault());
    // Per-module relocation counts by type, read from the files with an independent reader (python
    // struct over .rel.*; docs/INTEGRATION_LOG.md "SK modules, increment 1").
    struct Expect {
        u32 r32, r26, hi16, lo16, imports, import_libs, exports;
    };
    const Expect expect[kModuleCount] = {
        {7, 157, 112, 112, 52, 7, 6},      // SDRDRV: text 6+157+112+112, data 1
        {243, 693, 278, 278, 24, 4, 0},    // MODHSYN: text 30, rodata 192, data 21; exports read below
        {55, 110, 32, 32, 9, 4, 0},        // MODSESQ: text 15, rodata 35, data 5
        {31, 128, 107, 107, 34, 9, 19},    // SKSOUND: text 19, rodata 11, data 1
        {12, 127, 111, 111, 33, 7, 11},    // SKHSYNTH
        {10, 129, 118, 118, 33, 8, 9},     // SKSESQ
    };
    for (std::size_t i = 0; i < kModuleCount; ++i) {
        const LoadedIrx& m = s.loaded[i];
        INFO(kModules[i].file);
        CHECK(m.info.name == kModules[i].iopmod_name);
        CHECK(m.info.text_size == kModules[i].text);
        CHECK(m.info.data_size == kModules[i].data);
        CHECK(m.info.bss_size == kModules[i].bss);
        CHECK(m.info.base % 16 == 0);
        CHECK(m.info.base >= detail::kIopHeapBegin);
        CHECK(m.info.entry == m.info.base + (std::strcmp(kModules[i].file, "SDRDRV.IRX") == 0 ? 0x3A0u
                                            : std::strcmp(kModules[i].file, "SKSOUND.IRX") == 0 ? 0x34Cu
                                            : std::strcmp(kModules[i].file, "SKHSYNTH.IRX") == 0 ? 0x188u
                                            : std::strcmp(kModules[i].file, "SKSESQ.IRX") == 0 ? 0x20Cu : 0u));
        auto count = [&](u32 type) {
            const auto it = m.info.relocations.find(type);
            return it == m.info.relocations.end() ? 0u : it->second;
        };
        CHECK(count(2) == expect[i].r32);
        CHECK(count(4) == expect[i].r26);
        CHECK(count(5) == expect[i].hi16);
        CHECK(count(6) == expect[i].lo16);
        u32 imports = 0;
        for (const IrxImport& imp : m.info.imports) imports += static_cast<u32>(imp.ordinals.size());
        CHECK(imports == expect[i].imports);
        CHECK(m.info.imports.size() == expect[i].import_libs);
        REQUIRE(m.info.exports.size() == 1);
        CHECK(m.info.exports[0].library == kModules[i].library);
        if (expect[i].exports) CHECK(m.info.exports[0].functions.size() == expect[i].exports);
        CHECK(m.info.exports[0].functions[0] == m.info.entry);  // export 0 is _start
        std::string missing;
        for (const UnresolvedImport& u : m.unresolved) missing += " " + u.library + "#" + std::to_string(u.ordinal);
        CHECK_MESSAGE(m.unresolved.empty(), "unresolved imports:" << missing);
    }
    // MODHSYN / MODSESQ export tables: the ordinals SKHSYNTH / SKSESQ import must exist (28 / 12 highest).
    CHECK(s.module("modhsyn")->info.exports[0].functions.size() >= 29);
    CHECK(s.module("modsesq")->info.exports[0].functions.size() >= 13);
    // Every stub now jumps into a guest export or a host call -- no `jr ra` stub left.
    for (const LoadedIrx& m : s.loaded)
        for (const IrxImport& imp : m.info.imports)
            for (u32 stub : imp.stubs) CHECK(s.k.cpu().read32(stub) != 0x03E00008u);
}

TEST_CASE("Kernel HLE: every module entry runs to completion and registers its library in load order") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    Stack s;
    REQUIRE_MESSAGE(s.load_all(), s.error);
    REQUIRE_MESSAGE(s.k.fault().empty(), s.k.fault());
    for (std::size_t i = 0; i < kModuleCount; ++i) {
        INFO(std::string(kModules[i].file));
        CHECK(s.loaded[i].start_returned);
        // 0 MODULE_RESIDENT_END or 2 MODULE_REMOVABLE_RESIDENT_END; 1 would mean "not resident" (irx.h).
        CHECK_MESSAGE((s.loaded[i].start_result == 0 || s.loaded[i].start_result == 2), "start result " << s.loaded[i].start_result);
        MESSAGE(std::string(kModules[i].file) << ": _start returned " << s.loaded[i].start_result << " after " << s.loaded[i].start_instructions << " instructions");
        CHECK(s.loaded[i].start_instructions > 0);
    }
    REQUIRE(s.k.libraries().size() == kModuleCount);
    for (std::size_t i = 0; i < kModuleCount; ++i) {
        CHECK(s.k.libraries()[i].name == kModules[i].library);
        CHECK(s.k.libraries()[i].order == i);
        CHECK(s.k.libraries()[i].module_id == s.loaded[i].id);
    }
    // SDRDRV's RPC thread registered server 0x80000701 with its handler (0x588) and blocked in RpcLoop.
    const LoadedIrx* sdr = s.module("sdrdrv");
    REQUIRE(sdr != nullptr);
    bool found = false;
    for (const RpcServerRecord& r : s.k.rpc_servers())
        if (r.sid == 0x80000701u) {
            found = true;
            CHECK(r.func == sdr->info.base + 0x588u);
            CHECK(r.buf == sdr->info.base + 0x1C30u);
            CHECK(r.queue_thread != 0);
            const auto t = s.k.threads().find(r.queue_thread);
            REQUIRE(t != s.k.threads().end());
            CHECK(t->second.status == ThreadStatus::Wait);
            CHECK(t->second.wait == WaitKind::Rpc);
        }
    CHECK(found);
    // Loading SKHSYNTH a second time (the game does, `12` §1) fails RegisterLibraryEntries and the entry
    // answers 1 (MODULE_NO_RESIDENT_END) -- the duplicate instance registers nothing.
    const auto file = read_file(extracted_dir() / "disc" / "LIB31" / "SKHSYNTH.IRX");
    REQUIRE(file);
    std::string err;
    const auto again = s.k.load_module(*file, "cdrom0:\\LIB31\\SKHSYNTH.IRX;1", {}, err);
    REQUIRE_MESSAGE(again, err);
    CHECK(again->start_returned);
    CHECK(again->start_result == 1);
    CHECK(s.k.libraries().size() == kModuleCount);
    CHECK(s.k.fault().empty());
}

TEST_CASE("Kernel HLE: SKSOUND's tick thread and hard timer exist after its start and tick on virtual time") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    Stack s;
    REQUIRE_MESSAGE(s.load_all(), s.error);
    REQUIRE_MESSAGE(s.k.fault().empty(), s.k.fault());
    const LoadedIrx* sk = s.module("sksound");
    REQUIRE(sk != nullptr);
    // The thread SKSOUND's start thread (entry 0x1060) created: entry 0xEE0, stack 0x800, sleeping.
    const KernelThread* tick = nullptr;
    const KernelThread* starter = nullptr;
    for (const auto& [id, t] : s.k.threads()) {
        if (t.entry == sk->info.base + 0xEE0u) tick = &t;
        if (t.entry == sk->info.base + 0x1060u) starter = &t;
    }
    REQUIRE(tick != nullptr);
    REQUIRE(starter != nullptr);
    CHECK(tick->status == ThreadStatus::Wait);
    CHECK(tick->wait == WaitKind::Sleep);
    CHECK(tick->stack_size == 0x800u);
    CHECK(tick->attr == 0x02000000u);
    CHECK(starter->status == ThreadStatus::Wait);
    CHECK(starter->wait == WaitKind::Sema);  // waits for the shutdown semaphore (0x10E8)
    CHECK(tick->priority + 1 == starter->priority);
    // One hard timer: AllocHardTimer(1, 32, 1), handler 0x1140, compare = USec2SysClock(0x1047) = 153,612.
    REQUIRE(s.k.timers().size() == 1);
    const HardTimer& hw = s.k.timers().begin()->second;
    CHECK(hw.running);
    CHECK(hw.source == 1u);
    CHECK(hw.size == 32u);
    CHECK(hw.prescale == 1u);
    CHECK(hw.compare == 153612u);
    CHECK(hw.handler == sk->info.base + 0x1140u);
    CHECK(hw.deadline == static_cast<u64>(153612) * 8);
    CHECK(s.k.next_deadline() == hw.deadline);
    // One virtual second: the handler fires every 1,228,896 EE cycles (4,167 us) = 239.98 Hz, i.e. 239
    // times in the first second and 240 in most others; each run wakes the tick thread once.
    const u64 runs_before = tick->runs;
    const u64 second = 294'912'000ull;
    CHECK(s.k.advance_to(second) == 239);
    CHECK(s.k.timer_handler_runs() == 239);
    CHECK(tick->runs == runs_before + 239);
    CHECK(tick->status == ThreadStatus::Wait);
    CHECK(s.k.advance_to(2 * second) == 240);
    CHECK(s.k.advance_to(60 * second) == 13919);  // 60 s / 4,167 us = 14,398.9 -> 14,398 deadlines in all
    CHECK(s.k.timer_handler_runs() == 14398);
    CHECK(tick->runs == runs_before + s.k.timer_handler_runs());
    CHECK(hw.deadline > 60 * second);
    CHECK(s.k.fault().empty());
    MESSAGE("instructions after 60 virtual seconds of ticks: " << s.k.instructions() << " (tick thread " << tick->instructions << ")");
}

TEST_CASE("libsd HLE: SOUND_Send through SKSOUND lands COMSE.BD at SPU RAM 0x5010, byte for byte") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    const auto bd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.BD");
    if (!bd) {
        MESSAGE("skipped: extracted/DATA/SOUND/SPU/COMSE.BD not present");
        return;
    }
    REQUIRE(bd->size() == 573824u);
    Stack s;
    REQUIRE_MESSAGE(s.load_all(), s.error);
    const LoadedIrx* sk = s.module("sksound");
    REQUIRE(sk != nullptr);
    REQUIRE(sk->info.exports[0].functions.size() > 18);
    const u32 send = sk->info.exports[0].functions[18];  // sksound export 18 = SOUND_Send (IRX 0xA00)
    CHECK(send == sk->info.base + 0xA00u);
    // The game's state-5 path: the body goes through a 4096-byte IOP buffer (H_Sndcom_Update 0x10D0F4).
    const u32 iop_buf = s.ram.alloc(4096, 0, 0);
    REQUIRE(iop_buf != 0);
    u32 spu = 0x5010;
    u64 sent = 0;
    for (std::size_t off = 0; off < bd->size(); off += 4096) {
        const u32 n = static_cast<u32>(std::min<std::size_t>(4096, bd->size() - off));
        std::memcpy(s.ram.at(iop_buf, n), bd->data() + off, n);
        const u32 args[4] = {1, iop_buf, spu, n};
        std::string err;
        const auto r = s.k.call(send, args, err);
        REQUIRE_MESSAGE(r, err);
        CHECK(*r == n);  // SKSOUND returns sceSdVoiceTrans's result: the size (`16` §9.2, libsd.h)
        spu += n;
        sent += n;
    }
    CHECK(sent == bd->size());
    CHECK(s.sd.voice_trans_bytes() == bd->size());
    CHECK(s.sd.transfers().size() == 141);
    CHECK(s.sd.transfers()[0].channel == 1u);
    CHECK(s.sd.transfers()[0].mode == 0u);
    CHECK(std::memcmp(s.sd.spu_ram().data() + 0x5010, bd->data(), bd->size()) == 0);
    // Cross-check with PCSX2's dorm save state (read-only, optional): SPU2.bin holds SPU RAM after a
    // 0x10004-byte header (docs/ANALYSIS/19 §1.3), so the bank sits at 0x15014.
    const auto pcsx2 = read_file(extracted_dir() / "_pcsx2" / "dorm" / "SPU2.bin");
    if (pcsx2 && pcsx2->size() >= 0x15014u + bd->size()) {
        CHECK(std::memcmp(pcsx2->data() + 0x15014, bd->data(), bd->size()) == 0);
        CHECK(std::memcmp(pcsx2->data() + 0x15014, s.sd.spu_ram().data() + 0x5010, bd->size()) == 0);
    } else {
        MESSAGE("PCSX2 dorm SPU2.bin not present; cross-check skipped");
    }
    // The direct libsd path agrees (a VoiceTrans with the bytes in IOP RAM at once).
    LibsdHle direct;
    detail::IopRam ram2;
    const u32 big = ram2.alloc(static_cast<u32>(bd->size()), 0, 0);
    REQUIRE(big != 0);
    std::memcpy(ram2.at(big, static_cast<u32>(bd->size())), bd->data(), bd->size());
    CHECK(direct.voice_trans(0, 0, ram2, big, 0x5010, static_cast<u32>(bd->size()), nullptr) == static_cast<s32>(bd->size()));
    CHECK(std::memcmp(direct.spu_ram().data() + 0x5010, s.sd.spu_ram().data() + 0x5010, bd->size()) == 0);
    CHECK(s.k.fault().empty());
}

TEST_CASE("Kernel HLE: two runs of the stack are identical") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    Stack a, b;
    REQUIRE_MESSAGE(a.load_all(), a.error);
    REQUIRE_MESSAGE(b.load_all(), b.error);
    a.k.advance_to(294'912'000ull);
    b.k.advance_to(294'912'000ull);
    CHECK(a.k.instructions() == b.k.instructions());
    CHECK(a.k.timer_handler_runs() == b.k.timer_handler_runs());
    CHECK(a.k.printf_log() == b.k.printf_log());
    REQUIRE(a.loaded.size() == b.loaded.size());
    for (std::size_t i = 0; i < a.loaded.size(); ++i) {
        CHECK(a.loaded[i].info.base == b.loaded[i].info.base);
        CHECK(a.loaded[i].start_instructions == b.loaded[i].start_instructions);
    }
    CHECK(a.k.threads().size() == b.k.threads().size());
    for (auto ia = a.k.threads().begin(), ib = b.k.threads().begin(); ia != a.k.threads().end(); ++ia, ++ib) {
        CHECK(ia->second.entry == ib->second.entry);
        CHECK(ia->second.status == ib->second.status);
        CHECK(ia->second.instructions == ib->second.instructions);
        CHECK(std::memcmp(ia->second.ctx.r, ib->second.ctx.r, sizeof ia->second.ctx.r) == 0);
    }
    CHECK(a.ram.image().size() == b.ram.image().size());
    CHECK(std::memcmp(a.ram.image().data(), b.ram.image().data(), a.ram.image().size()) == 0);
    CHECK(std::memcmp(a.sd.spu_ram().data(), b.sd.spu_ram().data(), a.sd.spu_ram().size()) == 0);
}

// ---- phase 0: the sound log ----------------------------------------------------------------------------------

TEST_CASE("Sound log: every request reaches the sink in order with its vblank; verbs and the census name them") {
    std::vector<SoundRequest> seen;
    IopConfig cfg;
    cfg.sound_sink = [&](const SoundRequest& r) { seen.push_back(r); };
    p3fes::test::EeSide e(cfg);
    e.init_rpc();
    const u32 sd = e.bind(0x80000701u);
    auto sk = [&](u32 module, u32 fn, std::initializer_list<u32> args) {
        std::vector<u8> blk(64, 0);
        store32(blk, 0, module);
        store32(blk, 4, fn);
        std::size_t i = 8;
        for (u32 a : args) {
            store32(blk, i, a);
            i += 4;
        }
        return static_cast<s32>(load32(e.call_sync(sd, 0x90F0, blk, 16), 0));
    };
    auto sd_call = [&](u32 code, u32 a1, u32 a2) {
        return static_cast<s32>(load32(e.call_sync(sd, code, p3fes::test::words({0x96E000, a1, a2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 16), 0));
    };
    const u32 m1 = static_cast<u32>(-1);
    CHECK(sd_call(0x8010, 0x980, 0x3FFF) == 0);          // SetParam
    CHECK(sd_call(0xE620, 0x780000, 0x780000) == 0);     // CallbackInit
    CHECK(sk(0, 2, {3, 128, 127, 127}) == 0);            // SOUND_Control 0x80
    e.bus.vblank();
    e.bus.vblank();
    CHECK(sk(0, 2, {3, 128, 127, 127}) == 0);
    CHECK(sk(0x1000000, 0, {3, m1, 0x100000, 100, 0x5000, 200}) == 0);  // HSYNTH_Bind 3
    CHECK(sk(0x1000000, 0, {5, m1, 0, 0}) == 0);                        // HSYNTH_Bind 5
    CHECK(sk(0x4000000, 0, {0, m1, 0x110000, 300}) == 0);               // SESQ_Bind 0
    CHECK(sk(0x4000000, 0, {5, 0, 0}) == 0);                            // SESQ_Bind 5
    CHECK(sk(0x4000000, 2, {0, 0, 10, 4}) == 0);                        // SESQ_Control play
    CHECK(sk(0x4000000, 3, {0, 1, 10, 0}) == 0);                        // SESQ_Status
    CHECK(sk(0x4000000, 2, {0, 2, 10, 0}) == 0);                        // SESQ_Control stop
    const std::vector<std::string> verbs = {"SetParam", "CallbackInit", "SOUND_Control 0x80", "SOUND_Control 0x80", "HSYNTH_Bind 3",
                                            "HSYNTH_Bind 5", "SESQ_Bind 0", "SESQ_Bind 5", "SESQ_Control play", "SESQ_Status",
                                            "SESQ_Control stop"};
    REQUIRE(seen.size() == verbs.size());
    for (std::size_t i = 0; i < verbs.size(); ++i) {
        INFO(i);
        CHECK(sound_verb(seen[i]) == verbs[i]);
        CHECK(seen[i].sid == 0x80000701u);
        CHECK(seen[i].vblank == (i < 3 ? 0u : 2u));
    }
    CHECK(seen[0].fno == 0x8010u);
    CHECK(seen[0].args[0] == 0x980u);
    CHECK(seen[8].sk_module == 0x4000000u);
    CHECK(seen[8].args[3] == 4u);
    const auto census = e.sif.iop().sound_census();
    CHECK(census.size() == 10);
    CHECK(census.at("SOUND_Control 0x80") == 2);
    CHECK(census.at("SESQ_Control play") == 1);
    CHECK(census.at("SetParam") == 1);
    CHECK(e.sif.iop().sound_requests() == verbs.size());
    CHECK(e.sif.iop().sound_log().size() == verbs.size());  // the ring still serves inspection
    // Verb names for codes the game never sends stay distinct.
    SoundRequest other;
    other.sid = 0x80000701u;
    other.fno = 0x8090u;
    CHECK(sound_verb(other) == "libsd 0x8090");
    other.fno = 0x90F0u;
    other.sk_module = 0x2000000u;
    CHECK(sound_verb(other) == "SK 2/0");
    other.sid = 0x90000200u;
    other.fno = 1024 + 12;
    CHECK(sound_verb(other) == "DTX urpc");
}

// ---- increment 2: the routed flow ------------------------------------------------------------------------------

namespace {

struct RoutedRig {
    std::vector<SoundRequest> log;
    std::vector<std::string> lines;  // the IOP's log (module printf, kernel faults)
    IopConfig cfg;
    std::unique_ptr<p3fes::test::EeSide> e;
    audio::NullSink sink;
    u32 lf = 0, heap = 0, sd = 0;

    explicit RoutedRig(IopLayout layout = IopLayout::Pcsx2) {
        cfg.sk_mode = SkMode::Modules;
        cfg.iop_layout = layout;
        cfg.module_source = [](std::string_view name) { return read_file(extracted_dir() / "disc" / "LIB31" / std::string(name)); };
        cfg.sound_sink = [this](const SoundRequest& r) { log.push_back(r); };
        cfg.log = [this](std::string_view l) { lines.emplace_back(l); };
        e = std::make_unique<p3fes::test::EeSide>(cfg);
        e->sif.iop().set_audio_output(&sink, nullptr);
        e->init_rpc();
        lf = e->bind(0x80000006u);
    }
    // _sceSifLoadModule 0x50C2C0: fn 0, 512 bytes {arglen, modres, path[252], args[252]} -> {id, modres}.
    s32 load(const char* name, std::string_view args = {}) {
        std::vector<u8> b(512, 0);
        store32(b, 0, static_cast<u32>(args.size()));
        const std::string path = std::string("cdrom0:\\LIB31\\") + name + ";1";
        std::memcpy(b.data() + 8, path.data(), path.size());
        if (!args.empty()) std::memcpy(b.data() + 260, args.data(), args.size());
        return static_cast<s32>(load32(e->call_sync(lf, 0, b, 8), 0));
    }
    // kwlnInitPS2Systems' order (12 §1): SDRDRV, MODHSYN, MODMSIN, MODSESQ, SKSOUND, SKHSYNTH, SKHSYNTH again, SKSESQ.
    void load_all() {
        CHECK(load("SDRDRV.IRX") > 0);
        CHECK(load("MODHSYN.IRX") > 0);
        CHECK(load("MODMSIN.IRX") > 0);
        CHECK(load("MODSESQ.IRX") > 0);
        CHECK(load("SKSOUND.IRX") > 0);
        CHECK(load("SKHSYNTH.IRX") > 0);
        CHECK(load("SKHSYNTH.IRX") > 0);
        CHECK(load("SKSESQ.IRX", std::string_view("maxtrack=16\0maxentry=16\0", 24)) > 0);
        heap = e->bind(0x80000003u);
        sd = e->bind(0x80000701u);
    }
    u32 alloc(u32 size) { return load32(e->call_sync(heap, 4, p3fes::test::words({size, 0, 0}), 4), 0); }
    void dma(u32 ee_addr, u32 iop_addr, const std::vector<u8>& bytes) {
        e->write(ee_addr, bytes);
        e->set_dma({DmaTransfer{ee_addr, iop_addr, static_cast<u32>(bytes.size()), 0}});
    }
    s32 sd_call(u32 code, u32 a1, u32 a2) {
        return static_cast<s32>(load32(e->call_sync(sd, code, p3fes::test::words({0x96E000, a1, a2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), 16), 0));
    }
    s32 sk(u32 module, u32 fn, std::initializer_list<u32> args) {
        std::vector<u8> blk(64, 0);
        store32(blk, 0, module);
        store32(blk, 4, fn);
        std::size_t i = 8;
        for (u32 a : args) {
            store32(blk, i, a);
            i += 4;
        }
        return static_cast<s32>(load32(e->call_sync(sd, 0x90F0, blk, 16), 0));
    }
    // Virtual time: `ms` milliseconds in 1 ms steps, each a SIF check point (the SK tick runs there).
    void run_ms(u32 ms) {
        for (u32 i = 0; i < ms; ++i) {
            e->bus.advance(294'912);
            e->sif.service();
        }
    }
    u64 count(const char* verb) const {
        u64 n = 0;
        for (const SoundRequest& r : log)
            if (sound_verb(r) == verb) ++n;
        return n;
    }
    std::string tail(std::size_t n = 12) const {
        std::string t;
        for (std::size_t i = lines.size() > n ? lines.size() - n : 0; i < lines.size(); ++i) t += " | " + lines[i];
        return t;
    }
};

}  // namespace

TEST_CASE("Routing: the H_Sndcom flow is answered by the interpreted modules at PCSX2's IOP addresses; the first play keys voices") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    const auto hd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.HD");
    const auto bd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.BD");
    const auto sq = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.SQ");
    if (!hd || !bd || !sq) {
        MESSAGE("skipped: extracted/DATA/SOUND/SPU/COMSE.* not present");
        return;
    }
    REQUIRE(hd->size() == 0x2860u);
    REQUIRE(bd->size() == 0x8C180u);
    REQUIRE(sq->size() == 0xF40u);

    RoutedRig r;
    r.load_all();
    const SkStats after_load = r.e->sif.iop().sk_stats();
    REQUIRE_MESSAGE(after_load.fault.empty(), after_load.fault << r.tail());
    CHECK(after_load.modules);
    CHECK(after_load.modules_loaded == 7);  // the duplicate SKHSYNTH loads, answers 1 and is freed
    // The EE's client data (sdr_rpc_cd 0x96E040 layout: +36 server, +20 buffer) now holds the module's
    // SifRpcServerData_t and receive buffer -- PCSX2's dorm state has 0x84810 / 0x84E60 (SDRDRV at 0x83230).
    CHECK(r.e->r32(r.sd + 36) == 0x84810u);
    CHECK(r.e->r32(r.sd + 20) == 0x84E60u);
    // H_Sndcom_Update's first IOP allocation (the COMSE header) lands where PCSX2's does.
    const u32 hd_iop = r.alloc(static_cast<u32>(hd->size()));
    CHECK(hd_iop == 0x000BD400u);
    const u32 sq_iop = r.alloc(static_cast<u32>(sq->size()));
    const u32 tmp = r.alloc(4096);
    CHECK(sq_iop != 0);
    CHECK(tmp != 0);
    r.dma(0x01100000u, hd_iop, *hd);
    r.dma(0x01110000u, sq_iop, *sq);

    // H_Sndcom_Init / sceSkSsInit, in the order of the game's sound log (INTEGRATION_LOG "SK modules, increment 1").
    CHECK(r.sd_call(0xE620, 0x780000, 0x780000) == 0);
    CHECK(r.sd_call(0x8010, 0x980, 0x3FFF) == 0);
    CHECK(r.sd_call(0x8010, 0xA80, 0x3FFF) == 0);
    CHECK(r.sd_call(0x8010, 0x981, 0) == 0);
    CHECK(r.sd_call(0x8010, 0xA81, 0) == 0);
    CHECK(r.sk(0, 2, {0, 0x8F, 0}) == 0);
    CHECK(r.sk(0, 2, {3, 0x83, 0x105, 0x3C}) == 0);
    CHECK(r.sk(0, 2, {3, 0x84, 0x3C, 0x3C}) == 0);
    CHECK(r.sk(0, 2, {3, 0x82, 1, 0x40}) == 0);
    CHECK(r.sd_call(0x8010, 0x800, 0xFC0) == 0);
    CHECK(r.sd_call(0x8010, 0x801, 0xFCC) == 0);
    CHECK(r.sk(0, 2, {3, 0x80, 0x7F, 0x7F}) == 0);
    CHECK(r.sd_call(0x8020, 0x980, 0) == 0x3FFF);  // GetParam reads the model back
    // The bank body: 141 SOUND_Send chunks of 4096 through the temp buffer, as H_Sndcom_Update state 5 does.
    u32 spu = 0x5010;
    for (std::size_t off = 0; off < bd->size(); off += 4096) {
        const u32 n = static_cast<u32>(std::min<std::size_t>(4096, bd->size() - off));
        r.dma(0x01200000u, tmp, std::vector<u8>(bd->begin() + static_cast<std::ptrdiff_t>(off), bd->begin() + static_cast<std::ptrdiff_t>(off + n)));
        REQUIRE(r.sk(0, 10, {1, tmp, spu, n}) == static_cast<s32>(n));
        spu += n;
    }
    CHECK(r.count("SOUND_Send") == 141);
    // Binds: the IRX code answers (entry 0 / port 0 / sequence 0 / the port), as the constant model predicted.
    const s32 entry = r.sk(0x1000000, 0, {3, 0xFFFFFFFFu, hd_iop, 0x2860, 0x5010, 0x8C180});
    REQUIRE_MESSAGE(entry >= 0, "HSYNTH_Bind 3 -> " << entry << "; IOP log:" << r.tail(40));
    const s32 port = r.sk(0x1000000, 0, {5, 0xFFFFFFFFu, static_cast<u32>(entry), 0});
    REQUIRE(port >= 0);
    const s32 seq = r.sk(0x4000000, 0, {0, 0xFFFFFFFFu, sq_iop, 0xF40});
    REQUIRE(seq >= 0);
    const s32 ctl = r.sk(0x4000000, 0, {5, static_cast<u32>(port), static_cast<u32>(seq)});
    CHECK(ctl == port);
    MESSAGE("HSYNTH entry " << entry << ", port " << port << ", SESQ entry " << seq << ", ctl " << ctl);
    CHECK(entry == 0);
    CHECK(port == 0);
    CHECK(seq == 0);
    // Rebinding the same port is refused by the IRX as the constant model said (-202); an unbound entry -201.
    CHECK(r.sk(0x4000000, 0, {5, static_cast<u32>(port), static_cast<u32>(seq)}) == -202);
    CHECK(r.sk(0x1000000, 0, {5, 0xFFFFFFFFu, 7, 0}) == -201);
    CHECK(r.sk(0x2000000, 0, {}) == -310);  // module slot 2 is empty
    CHECK(r.sk(0, 2, {3, 0x77, 0}) == -310);

    // The memory-card prompt's SE: SESQ_Control(port, 0, 10, group 0, entry 1), as the dorm route's first play.
    const SkStats before = r.e->sif.iop().sk_stats();
    CHECK(before.key_ons == 0);
    const s32 t0 = r.sk(0x4000000, 2, {static_cast<u32>(port), 0, 10, 0, 1});
    REQUIRE(t0 >= 0);
    CHECK(r.sk(0x4000000, 3, {static_cast<u32>(port), 1, 10, static_cast<u32>(t0)}) >= 0);
    r.run_ms(100);  // 24 SK ticks: MODSESQ steps the sequence, MODHSYN keys the voices through libsd
    const SkStats playing = r.e->sif.iop().sk_stats();
    REQUIRE_MESSAGE(playing.fault.empty(), playing.fault << r.tail());
    CHECK(playing.tick_runs >= before.tick_runs + 23);
    CHECK(playing.key_ons >= 1);
    CHECK(playing.voices_active >= 1);
    CHECK(playing.voice_frames > 0);
    CHECK(r.count("KON") == playing.key_ons);
    MESSAGE("track " << t0 << ": " << playing.key_ons << " key-ons after 100 ms, voices active " << playing.voices_active << ", first voice frame "
                     << playing.first_voice_frame << ", ticks " << playing.tick_runs << ", instructions " << playing.instructions);
    // Every key-on reads the COMSE bank the SOUND_Sends placed at 0x5010 (SSA inside it), on core 1 (the per-frame
    // SOUND_Control 0x80 sets core 1's master volume).
    for (const SoundRequest& ev : r.log) {
        if (sound_verb(ev) != "KON") continue;
        CHECK(ev.args[2] >= 0x5010u);
        CHECK(ev.args[2] < 0x5010u + bd->size());
        CHECK(ev.args[4] != 0);  // pitch
    }
    // The mix reaches the sink two passes behind the clock.
    r.run_ms(60);
    CHECK(r.sink.non_silent_frames() > 0);
    CHECK(r.sink.first_non_silent_frame() != ~0ull);
    MESSAGE("mix: first non-silent frame " << r.sink.first_non_silent_frame() << ", " << r.sink.non_silent_frames() << " non-silent of " << r.sink.frames()
                                            << " pushed frames, peak " << r.sink.peak());
    // A second play gets the next track of MODSESQ's round-robin allocator (19 §1.4), a stop answers 0.
    const s32 t1 = r.sk(0x4000000, 2, {static_cast<u32>(port), 0, 10, 0, 1});
    CHECK(t1 >= 0);
    CHECK(t1 != t0);
    MESSAGE("tracks " << t0 << " then " << t1);
    // Stop: the IRX's own reply (the constant model answered 0; H_Sndcom_StopVoice 0x10DA70 drops it).
    const s32 st0 = r.sk(0x4000000, 2, {static_cast<u32>(port), 2, 10, static_cast<u32>(t0)});
    const s32 st1 = r.sk(0x4000000, 2, {static_cast<u32>(port), 2, 10, static_cast<u32>(t1)});
    // SKSESQ 0xCFC answers -302 when MODSESQ's stop finds the track no longer running (the first SE is a short
    // one-shot; the game never looks at this value) -- recorded, not asserted beyond consistency.
    MESSAGE("SESQ_Control stop -> " << st0 << ", " << st1);
    CHECK(st0 == st1);
    r.run_ms(50);
    const SkStats end = r.e->sif.iop().sk_stats();
    CHECK(end.key_offs >= 1);  // MODHSYN keys every voice off at init, and releases through libsd
    CHECK(end.rpc_routed == r.e->sif.iop().sound_requests());  // every SDRDRV request went to the handler
    CHECK(end.rpc_pending == 0);
    CHECK(end.fault.empty());
}

TEST_CASE("Routing: two runs of the routed flow are identical (requests, key-ons, mix fingerprint)") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    const auto hd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.HD");
    const auto bd = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.BD");
    const auto sq = read_file(extracted_dir() / "DATA" / "SOUND" / "SPU" / "COMSE.SQ");
    if (!hd || !bd || !sq) {
        MESSAGE("skipped: extracted/DATA/SOUND/SPU/COMSE.* not present");
        return;
    }
    auto run = [&](RoutedRig& r) {
        r.load_all();
        const u32 hd_iop = r.alloc(static_cast<u32>(hd->size()));
        const u32 sq_iop = r.alloc(static_cast<u32>(sq->size()));
        const u32 tmp = r.alloc(4096);
        r.dma(0x01100000u, hd_iop, *hd);
        r.dma(0x01110000u, sq_iop, *sq);
        r.sd_call(0x8010, 0x980, 0x3FFF);
        r.sd_call(0x8010, 0xA80, 0x3FFF);
        r.sk(0, 2, {3, 0x80, 0x7F, 0x7F});
        u32 spu = 0x5010;
        for (std::size_t off = 0; off < bd->size(); off += 4096) {
            const u32 n = static_cast<u32>(std::min<std::size_t>(4096, bd->size() - off));
            r.dma(0x01200000u, tmp, std::vector<u8>(bd->begin() + static_cast<std::ptrdiff_t>(off), bd->begin() + static_cast<std::ptrdiff_t>(off + n)));
            r.sk(0, 10, {1, tmp, spu, n});
            spu += n;
        }
        const s32 entry = r.sk(0x1000000, 0, {3, 0xFFFFFFFFu, hd_iop, 0x2860, 0x5010, 0x8C180});
        const s32 port = r.sk(0x1000000, 0, {5, 0xFFFFFFFFu, static_cast<u32>(entry), 0});
        const s32 seq = r.sk(0x4000000, 0, {0, 0xFFFFFFFFu, sq_iop, 0xF40});
        r.sk(0x4000000, 0, {5, static_cast<u32>(port), static_cast<u32>(seq)});
        r.sk(0x4000000, 2, {static_cast<u32>(port), 0, 10, 0, 1});
        r.run_ms(150);
        r.sk(0x4000000, 2, {static_cast<u32>(port), 0, 10, 1, 2});
        r.run_ms(150);
        r.e->sif.iop().flush_audio();
    };
    RoutedRig a, b;
    run(a);
    run(b);
    REQUIRE(a.log.size() == b.log.size());
    for (std::size_t i = 0; i < a.log.size(); ++i) {
        CHECK(a.log[i].fno == b.log[i].fno);
        CHECK(a.log[i].result == b.log[i].result);
        CHECK(a.log[i].args == b.log[i].args);
        CHECK(a.log[i].cycle == b.log[i].cycle);
    }
    const SkStats sa = a.e->sif.iop().sk_stats(), sb = b.e->sif.iop().sk_stats();
    CHECK(sa.key_ons == sb.key_ons);
    CHECK(sa.key_ons >= 1);
    CHECK(sa.instructions == sb.instructions);
    CHECK(sa.tick_runs == sb.tick_runs);
    CHECK(a.sink.hash() == b.sink.hash());
    CHECK(a.sink.frames() == b.sink.frames());
    CHECK(a.sink.non_silent_frames() == b.sink.non_silent_frames());
    CHECK(a.sink.non_silent_frames() > 0);
    MESSAGE("two runs: " << sa.key_ons << " key-ons, " << a.sink.non_silent_frames() << " non-silent frames, hash " << a.sink.hash());
}

TEST_CASE("Routing: the legacy layout keeps the game's heap addresses and loads the modules above them") {
    if (!have_modules()) {
        MESSAGE("skipped: extracted/disc/LIB31 not present");
        return;
    }
    RoutedRig r(IopLayout::Legacy);
    r.load_all();
    const SkStats s = r.e->sif.iop().sk_stats();
    REQUIRE_MESSAGE(s.fault.empty(), s.fault << r.tail());
    CHECK(s.modules);
    // The first game allocation is where every pre-increment-2 snapshot had it; the module images sit in the
    // kernel's range at the top of the legacy heap, out of the game's way.
    CHECK(r.alloc(0x2860) == detail::kIopHeapBegin);
    CHECK(r.e->r32(r.sd + 36) >= 0x1A0000u);
    CHECK(r.e->r32(r.sd + 20) >= 0x1A0000u);
    CHECK(r.sd_call(0x8010, 0x980, 0x3FFF) == 0);
    CHECK(r.sd_call(0x8020, 0x980, 0) == 0x3FFF);
}

TEST_CASE("Routing: without module files SDRDRV keeps the constant replies (no disc, no reader)") {
    IopConfig cfg;
    cfg.sk_mode = SkMode::Modules;
    cfg.module_source = [](std::string_view) { return std::optional<std::vector<u8>>{}; };
    p3fes::test::EeSide e(cfg);
    e.init_rpc();
    const u32 lf = e.bind(0x80000006u);
    std::vector<u8> b(512, 0);
    const std::string path = "cdrom0:\\LIB31\\SDRDRV.IRX;1";
    std::memcpy(b.data() + 8, path.data(), path.size());
    CHECK(static_cast<s32>(load32(e.call_sync(lf, 0, b, 8), 0)) > 0);
    CHECK_FALSE(e.sif.iop().sk_stats().modules);
    const u32 sd = e.bind(0x80000701u);
    CHECK(e.r32(sd + 36) < detail::kIopServerArenaEnd);  // the HLE's own server data
    std::vector<u8> blk(64, 0);
    store32(blk, 0, 0x4000000u);
    store32(blk, 4, 2);
    store32(blk, 8, 0);
    store32(blk, 12, 0);
    store32(blk, 16, 10);
    CHECK(static_cast<s32>(load32(e.call_sync(sd, 0x90F0, blk, 16), 0)) == 0);  // the constant model's track 0
}

// ---- increment 3: long sound effects, key-off while sounding, the volume law ------------------------------------

namespace {

struct ComseFiles {
    std::optional<std::vector<u8>> hd, bd, sq;
    bool ok() const { return hd && bd && sq; }
};
ComseFiles comse_files() {
    const auto dir = extracted_dir() / "DATA" / "SOUND" / "SPU";
    return {read_file(dir / "COMSE.HD"), read_file(dir / "COMSE.BD"), read_file(dir / "COMSE.SQ")};
}

// H_Sndcom_Init + the COMSE bank upload + the binds, as the dorm route's sound log has them (the routed case
// above, condensed); returns the SESQ port.
s32 comse_setup(RoutedRig& r, const ComseFiles& f) {
    r.load_all();
    const u32 hd_iop = r.alloc(static_cast<u32>(f.hd->size()));
    const u32 sq_iop = r.alloc(static_cast<u32>(f.sq->size()));
    const u32 tmp = r.alloc(4096);
    r.dma(0x01100000u, hd_iop, *f.hd);
    r.dma(0x01110000u, sq_iop, *f.sq);
    r.sd_call(0xE620, 0x780000, 0x780000);
    r.sd_call(0x8010, 0x980, 0x3FFF);
    r.sd_call(0x8010, 0xA80, 0x3FFF);
    r.sd_call(0x8010, 0x981, 0);
    r.sd_call(0x8010, 0xA81, 0);
    r.sk(0, 2, {0, 0x8F, 0});
    r.sk(0, 2, {3, 0x83, 0x105, 0x3C});
    r.sk(0, 2, {3, 0x84, 0x3C, 0x3C});
    r.sk(0, 2, {3, 0x82, 1, 0x40});
    r.sd_call(0x8010, 0x800, 0xFC0);
    r.sd_call(0x8010, 0x801, 0xFCC);
    r.sk(0, 2, {3, 0x80, 0x7F, 0x7F});
    u32 spu = 0x5010;
    for (std::size_t off = 0; off < f.bd->size(); off += 4096) {
        const u32 n = static_cast<u32>(std::min<std::size_t>(4096, f.bd->size() - off));
        r.dma(0x01200000u, tmp, std::vector<u8>(f.bd->begin() + static_cast<std::ptrdiff_t>(off), f.bd->begin() + static_cast<std::ptrdiff_t>(off + n)));
        r.sk(0, 10, {1, tmp, spu, n});
        spu += n;
    }
    const s32 entry = r.sk(0x1000000, 0, {3, 0xFFFFFFFFu, hd_iop, 0x2860, 0x5010, 0x8C180});
    const s32 port = r.sk(0x1000000, 0, {5, 0xFFFFFFFFu, static_cast<u32>(entry), 0});
    const s32 seq = r.sk(0x4000000, 0, {0, 0xFFFFFFFFu, sq_iop, 0xF40});
    r.sk(0x4000000, 0, {5, static_cast<u32>(port), static_cast<u32>(seq)});
    return port;
}

}  // namespace

TEST_CASE("SE census: how long every COMSE (group, entry) sounds (exploration; run with --no-skip)" * doctest::skip()) {
    const ComseFiles f = comse_files();
    if (!have_modules() || !f.ok()) return;
    RoutedRig r;
    const s32 port = comse_setup(r, f);
    for (u32 g = 0; g < 7; ++g) {
        for (u32 e = 0; e < 16; ++e) {
            const u64 kons = r.e->sif.iop().sk_stats().key_ons;
            const s32 t = r.sk(0x4000000, 2, {static_cast<u32>(port), 0, 10, g, e});
            u32 ms = 0, max_active = 0;
            r.run_ms(5);
            while (ms < 6000) {
                r.run_ms(10);
                ms += 10;
                const SkStats s = r.e->sif.iop().sk_stats();
                max_active = std::max(max_active, s.voices_active);
                if (s.voices_active == 0) break;
            }
            const SkStats s = r.e->sif.iop().sk_stats();
            const s32 status = r.sk(0x4000000, 3, {static_cast<u32>(port), 1, 10, static_cast<u32>(t)});
            MESSAGE("group " << g << " entry " << e << ": track " << t << ", key-ons " << s.key_ons - kons << ", max voices " << max_active
                             << ", silent after " << ms << " ms, status " << status);
            if (ms >= 6000) r.sk(0x4000000, 2, {static_cast<u32>(port), 2, 10, static_cast<u32>(t)});
            r.run_ms(200);
        }
    }
}

TEST_CASE("Routing: a long SE (COMSE group 3 entry 0, ~5.6 s) runs out by itself; a stop while it sounds releases its voices") {
    const ComseFiles f = comse_files();
    if (!have_modules() || !f.ok()) {
        MESSAGE("skipped: extracted/disc/LIB31 or COMSE.* not present");
        return;
    }
    // Uninterrupted: the census's longest SE keys 3 voices; every one ends (the sample's end flag or MODHSYN's
    // own key-off) and voices_active returns to 0 -- no stuck voice.
    RoutedRig a;
    const s32 pa = comse_setup(a, f);
    const SkStats a0 = a.e->sif.iop().sk_stats();
    const s32 ta = a.sk(0x4000000, 2, {static_cast<u32>(pa), 0, 10, 3, 0});
    REQUIRE(ta >= 0);
    u32 ms = 0;
    a.run_ms(5);
    while (ms < 8000 && a.e->sif.iop().sk_stats().voices_active != 0) {
        a.run_ms(10);
        ms += 10;
    }
    const SkStats a1 = a.e->sif.iop().sk_stats();
    REQUIRE_MESSAGE(a1.fault.empty(), a1.fault << a.tail());
    CHECK(a1.key_ons - a0.key_ons == 3);
    CHECK(a1.voices_active == 0);
    CHECK(ms > 5000);
    CHECK(ms < 8000);
    CHECK(a1.voices_active_max >= 3);
    CHECK(a1.voice_longest_frames > 48000u * 4u);  // one voice sounds for more than 4 s
    CHECK(a.sk(0x4000000, 3, {static_cast<u32>(pa), 1, 10, static_cast<u32>(ta)}) == -299);  // finished
    MESSAGE("group 3 entry 0 alone: silent after " << ms << " ms, " << a1.key_ons - a0.key_ons << " key-ons, longest voice "
                                                      << a1.voice_longest_frames << " frames, key-offs " << a1.key_offs - a0.key_offs << " ("
                                                      << a1.key_offs_sounding - a0.key_offs_sounding << " while sounding)");

    // Stopped after 500 ms: SESQ_Status still reports the track, SESQ_Control stop answers the IRX's -302 (not
    // the -304 of a track that has already finished), MODHSYN keys the sounding voice off through libsd (a
    // KOFF line), it releases to Off within its release rate, and the track is gone.
    RoutedRig b;
    const s32 pb = comse_setup(b, f);
    const s32 tb = b.sk(0x4000000, 2, {static_cast<u32>(pb), 0, 10, 3, 0});
    REQUIRE(tb == ta);
    b.run_ms(500);
    const SkStats b0 = b.e->sif.iop().sk_stats();
    CHECK(b0.voices_active >= 1);
    CHECK(b.sk(0x4000000, 3, {static_cast<u32>(pb), 1, 10, static_cast<u32>(tb)}) >= 0);  // still running
    const s32 st = b.sk(0x4000000, 2, {static_cast<u32>(pb), 2, 10, static_cast<u32>(tb)});
    CHECK(st == -302);
    u32 rel = 0;
    while (rel < 2000 && b.e->sif.iop().sk_stats().voices_active != 0) {
        b.run_ms(1);
        ++rel;
    }
    const SkStats b1 = b.e->sif.iop().sk_stats();
    REQUIRE_MESSAGE(b1.fault.empty(), b1.fault << b.tail());
    CHECK(b1.voices_active == 0);
    CHECK(b1.key_offs_sounding - b0.key_offs_sounding >= b0.voices_active);  // every sounding voice was released
    CHECK(rel < 1000);
    CHECK(b1.voice_longest_frames < 48000u * 2u);
    CHECK(b.sk(0x4000000, 3, {static_cast<u32>(pb), 1, 10, static_cast<u32>(tb)}) == -299);
    CHECK(b.sk(0x4000000, 2, {static_cast<u32>(pb), 2, 10, static_cast<u32>(tb)}) == -304);  // a second stop: gone
    // The key-offs reach the sound log as KOFF lines after the stop request.
    u64 koff_after = 0;
    bool seen_stop = false;
    for (const SoundRequest& ev : b.log) {
        if (sound_verb(ev) == "SESQ_Control stop") seen_stop = true;
        if (seen_stop && sound_verb(ev) == "KOFF") ++koff_after;
    }
    MESSAGE("stopped at 500 ms with " << b0.voices_active << " voices: reply " << st << ", silent " << rel << " ms later, key-offs while sounding "
                                       << b1.key_offs_sounding - b0.key_offs_sounding << ", KOFF lines after the stop " << koff_after
                                       << ", longest voice " << b1.voice_longest_frames << " frames");
    CHECK(koff_after >= b0.voices_active);
}

TEST_CASE("Volume law: SOUND_Control 0x80 sets core 1's MVOL through libsd ((value x 129) & 0x7FFF); the init and the game's writes before it") {
    const ComseFiles f = comse_files();
    if (!have_modules() || !f.ok()) {
        MESSAGE("skipped: extracted/disc/LIB31 or COMSE.* not present");
        return;
    }
    RoutedRig r;
    comse_setup(r, f);
    r.run_ms(20);
    // The CORE lines of the setup, in order (core, kind, code, value, old): the same sequence as the dorm route's
    // sound log -- sceSdInit(0); effect mode 0x105 on both cores; MVOL0 0x3FFF (the game's SetParam 0x980/0xA80);
    // EVOL 0x3C78 and effect delay 0x3C; core attribute 1 (effect enable) = 1; MMIX FC0 / FCC; MVOL1 0x3FFF
    // from SOUND_Control 0x80 (127, 127) after the game's own MVOL1 = 0 (no change from the init image).
    auto core_lines = [&](std::size_t from) {
        std::vector<std::array<u32, 5>> out;
        for (std::size_t i = from; i < r.log.size(); ++i)
            if (sound_verb(r.log[i]) == "CORE") out.push_back({r.log[i].args[0], r.log[i].args[1], r.log[i].args[2], r.log[i].args[3], r.log[i].args[4]});
        return out;
    };
    const auto init = core_lines(0);
    std::string seen;
    for (const auto& c : init) {
        char b[64];
        std::snprintf(b, sizeof b, " [%u %u %X %X<-%X]", c[0], c[1], c[2], c[3], c[4]);
        seen += b;
    }
    MESSAGE("CORE lines of the setup:" << seen);
    auto has = [&](const std::vector<std::array<u32, 5>>& v, u32 core, u32 kind, u32 code, u32 value) {
        return std::any_of(v.begin(), v.end(), [&](const std::array<u32, 5>& c) { return c[0] == core && c[1] == kind && c[2] == code && c[3] == value; });
    };
    CHECK(has(init, 0, 5, 0, 0));             // sceSdInit(0)
    CHECK(has(init, 0, 1, 0x9, 0x3FFF));      // MVOL0 L
    CHECK(has(init, 1, 1, 0x9, 0x3FFF));      // MVOL1 L (SOUND_Control 0x80)
    CHECK(has(init, 1, 1, 0xA, 0x3FFF));      // MVOL1 R
    CHECK(has(init, 0, 1, 0x8, 0xFC0));       // MMIX0
    CHECK(has(init, 1, 1, 0x8, 0xFCC));       // MMIX1
    CHECK(r.sd_call(0x8020, 0x981, 0) == 0x3FFF);
    CHECK(r.sd_call(0x8020, 0xA81, 0) == 0x3FFF);
    // The law: SOUND_Control (3, 0x80, L, R) -> MVOL1 L/R = (value x 129) & 0x7FFF (127 -> 0x3FFF, 64 -> 0x2040, 1 -> 0x81,
    // 0 -> 0); above 127 the product reaches bit 14, the sign of the 15-bit level (128 -> 0x4080, a phase-inverted
    // gain), and 255 -> 0x807F loses bit 15 (-> 0x7F). The game sends 127 every frame (sub_108BC0).
    struct Case {
        u32 l, r;
    };
    for (const Case c : {Case{64, 32}, Case{1, 100}, Case{0, 0}, Case{128, 255}, Case{127, 127}}) {
        CAPTURE(c.l);
        CAPTURE(c.r);
        const std::size_t from = r.log.size();
        CHECK(r.sk(0, 2, {3, 0x80, c.l, c.r}) == 0);
        r.run_ms(5);
        const u32 got_l = static_cast<u32>(r.sd_call(0x8020, 0x981, 0)), got_r = static_cast<u32>(r.sd_call(0x8020, 0xA81, 0));
        MESSAGE("SOUND_Control 0x80 (" << c.l << ", " << c.r << ") -> MVOL1 " << got_l << " / " << got_r);
        CHECK(got_l == ((c.l * 129) & 0x7FFFu));
        CHECK(got_r == ((c.r * 129) & 0x7FFFu));
        // Only core 1's MVOL moves (no voice volume, no core-0 register).
        for (const auto& line : core_lines(from)) {
            CHECK(line[0] == 1);
            CHECK(line[1] == 1);
            CHECK((line[2] == 0x9 || line[2] == 0xA));
        }
    }
    // The model's gain from it: the stream (core 1) and a core-1 voice get MVOL1 doubled (0x3FFF -> 0x7FFE).
    CHECK(audio::spu2_fixed_gain(127 * 129) == 0x7FFE);
    CHECK(audio::spu2_fixed_gain(64 * 129) == 0x4080);
    CHECK(audio::spu2_fixed_gain(128 * 129) == -0x7F00);  // 0x4080: bit 14 set, a negative 15-bit level
}
