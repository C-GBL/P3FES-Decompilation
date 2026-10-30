// rt adapter memory path (runtime/rt/rt_mem.cpp): every load/store width and its extension, the
// RAM mirrors / scratchpad / BIOS window, the unaligned pairs at every offset, LQ/SQ/LQC2/SQC2
// masking, the hardware windows routed to the bus by width at the physical address followed by a
// check point, and the fatal paths (address error, unmapped, no EEMemory).
#include "fake_hooks.h"

#include "p3fes/ee_memory.h"
#include "p3fes_recomp_rt.h"

#include <cstring>
#include <string>

using namespace p3fes;
using rt_test::FatalEvent;
using rt_test::HooksScope;
using rt_test::TestHooks;

namespace {

struct MemFixture {
    EEMemory mem;
    EEContext ctx;
    TestHooks hooks;
    HooksScope scope{&hooks};
    MemFixture() { ctx.memory = &mem; }
    void base(unsigned r, u32 va) { ctx.gpr[r].u64[0] = static_cast<u64>(static_cast<s64>(static_cast<s32>(va))); }
    u64 g(unsigned r) const { return ctx.gpr[r].u64[0]; }
};

bool contains(const std::string& hay, const char* needle) { return hay.find(needle) != std::string::npos; }

} // namespace

TEST_CASE("rt mem: aligned loads of every width extend as the instruction says; the upper GPR half is kept") {
    MemFixture f;
    const u8 bytes[16] = {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    std::memcpy(f.mem.main_ram() + 0x100000, bytes, 16);
    f.base(4, 0x100010);  // offsets are negative: base + imm
    f.ctx.gpr[2].u64[1] = 0xDEADDEADDEADDEADull;
    rt::lb(f.ctx, 2, 4, -16);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFF81ull);
    CHECK(f.ctx.gpr[2].u64[1] == 0xDEADDEADDEADDEADull);
    rt::lbu(f.ctx, 2, 4, -16);
    CHECK(f.g(2) == 0x81u);
    rt::lh(f.ctx, 2, 4, -14);
    CHECK(f.g(2) == 0xFFFFFFFFFFFF8483ull);
    rt::lhu(f.ctx, 2, 4, -14);
    CHECK(f.g(2) == 0x8483u);
    rt::lw(f.ctx, 2, 4, -12);
    CHECK(f.g(2) == 0xFFFFFFFF88878685ull);
    rt::lwu(f.ctx, 2, 4, -12);
    CHECK(f.g(2) == 0x88878685u);
    rt::lw(f.ctx, 2, 4, -8);
    CHECK(f.g(2) == 0x04030201u);
    rt::ld(f.ctx, 2, 4, -16);
    CHECK(f.g(2) == 0x8887868584838281ull);
    CHECK(f.ctx.gpr[2].u64[1] == 0xDEADDEADDEADDEADull);
    CHECK(f.hooks.checks == 0);  // RAM accesses are not check points
    CHECK(f.mem.unmapped_accesses() == 0);
}

TEST_CASE("rt mem: stores write the low bytes of rt little-endian") {
    MemFixture f;
    f.base(4, 0x200000);
    f.ctx.gpr[5].u64[0] = 0x1122334455667788ull;
    rt::sb(f.ctx, 5, 4, 0);
    rt::sh(f.ctx, 5, 4, 2);
    rt::sw(f.ctx, 5, 4, 4);
    rt::sd(f.ctx, 5, 4, 8);
    const u8 expect[16] = {0x88, 0, 0x88, 0x77, 0x88, 0x77, 0x66, 0x55, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
    CHECK(std::memcmp(f.mem.main_ram() + 0x200000, expect, 16) == 0);
    // sw $zero stores zero.
    rt::sw(f.ctx, 0, 4, 4);
    CHECK(f.mem.read<u32>(0x200004) == 0u);
}

TEST_CASE("rt mem: KSEG0/KSEG1/uncached mirrors, scratchpad and BIOS resolve through EEMemory") {
    MemFixture f;
    f.ctx.gpr[5].u64[0] = 0xCAFEF00Du;
    f.base(4, 0x80123450);
    rt::sw(f.ctx, 5, 4, 0);
    CHECK(f.mem.read<u32>(0x00123450) == 0xCAFEF00Du);
    for (u32 mirror : {0x00123450u, 0x20123450u, 0x30123450u, 0xA0123450u}) {
        CAPTURE(mirror);
        f.base(6, mirror);
        rt::lwu(f.ctx, 2, 6, 0);
        CHECK(f.g(2) == 0xCAFEF00Du);
    }
    f.base(4, 0x70003FF0);
    rt::sd(f.ctx, 5, 4, 8);
    CHECK(f.mem.read<u64>(0x70003FF8) == 0xCAFEF00Du);
    CHECK(f.mem.main_ram()[0x3FF8] == 0);  // scratchpad is its own storage
    std::memcpy(f.mem.bios(), "\x00\x80\x1A\x3C", 4);
    f.base(4, 0xBFC00000);
    rt::lw(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0x3C1A8000u);
    CHECK(f.hooks.checks == 0);
}

TEST_CASE("rt mem: LWR/LWL and LDR/LDL pairs read an unaligned value at every offset") {
    MemFixture f;
    for (int i = 0; i < 32; ++i) f.mem.main_ram()[0x300000 + i] = static_cast<u8>(0xA0 + i);
    for (u32 off = 0; off < 8; ++off) {
        CAPTURE(off);
        u64 expect64;
        std::memcpy(&expect64, f.mem.main_ram() + 0x300000 + off, 8);
        u32 expect32;
        std::memcpy(&expect32, f.mem.main_ram() + 0x300000 + off, 4);
        f.base(4, 0x300000 + off);
        f.ctx.gpr[2].u64[0] = 0x0123456789ABCDEFull;
        rt::lwr(f.ctx, 2, 4, 0);
        rt::lwl(f.ctx, 2, 4, 3);
        CHECK(f.g(2) == static_cast<u64>(static_cast<s64>(static_cast<s32>(expect32))));
        f.ctx.gpr[3].u64[0] = 0x0123456789ABCDEFull;
        rt::ldr(f.ctx, 3, 4, 0);
        rt::ldl(f.ctx, 3, 4, 7);
        CHECK(f.g(3) == expect64);
    }
    // A lone LWR at offset 1 keeps the upper word of rt (core.h: EE choice, hardware-unverified).
    f.base(4, 0x300001);
    f.ctx.gpr[2].u64[0] = 0xFFFFFFFF12345678ull;
    rt::lwr(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0xFFFFFFFF12A3A2A1ull);
}

TEST_CASE("rt mem: SWR/SWL and SDR/SDL pairs store an unaligned value without touching neighbours") {
    MemFixture f;
    for (u32 off = 0; off < 8; ++off) {
        CAPTURE(off);
        std::memset(f.mem.main_ram() + 0x310000, 0xEE, 32);
        f.base(4, 0x310000 + off);
        f.ctx.gpr[5].u64[0] = 0x0807060504030201ull;
        rt::swr(f.ctx, 5, 4, 0);
        rt::swl(f.ctx, 5, 4, 3);
        u8 expect[32];
        std::memset(expect, 0xEE, 32);
        for (int i = 0; i < 4; ++i) expect[off + i] = static_cast<u8>(i + 1);
        CHECK(std::memcmp(f.mem.main_ram() + 0x310000, expect, 32) == 0);
        std::memset(f.mem.main_ram() + 0x310000, 0xEE, 32);
        rt::sdr(f.ctx, 5, 4, 0);
        rt::sdl(f.ctx, 5, 4, 7);
        std::memset(expect, 0xEE, 32);
        for (int i = 0; i < 8; ++i) expect[off + i] = static_cast<u8>(i + 1);
        CHECK(std::memcmp(f.mem.main_ram() + 0x310000, expect, 32) == 0);
    }
}

TEST_CASE("rt mem: LQ/SQ and LQC2/SQC2 ignore the low four address bits; LWC1/SWC1 move FPR bits") {
    MemFixture f;
    for (int i = 0; i < 16; ++i) f.mem.main_ram()[0x400000 + i] = static_cast<u8>(i);
    f.base(4, 0x40000F);  // low four bits set: still the quadword at 0x400000
    rt::lq(f.ctx, 2, 4, 0);
    CHECK(f.ctx.gpr[2].u64[0] == 0x0706050403020100ull);
    CHECK(f.ctx.gpr[2].u64[1] == 0x0F0E0D0C0B0A0908ull);
    f.base(6, 0x400019);
    rt::sq(f.ctx, 2, 6, 0);  // -> 0x400010
    CHECK(std::memcmp(f.mem.main_ram() + 0x400010, f.mem.main_ram() + 0x400000, 16) == 0);
    rt::lqc2(f.ctx, 3, 4, -8);  // 0x400007 -> 0x400000
    CHECK(f.ctx.vu0.vf[3][0] == 0x03020100u);
    CHECK(f.ctx.vu0.vf[3][3] == 0x0F0E0D0Cu);
    rt::lqc2(f.ctx, 0, 4, 0);  // vf00 is read-only: the read happens, the register keeps (0,0,0,1)
    CHECK(f.ctx.vu0.vf[0][3] == 0x3F800000u);
    CHECK(f.ctx.vu0.vf[0][0] == 0u);
    rt::sqc2(f.ctx, 3, 6, 0x10);  // 0x400029 -> 0x400020
    CHECK(f.mem.read<u32>(0x40002C) == 0x0F0E0D0Cu);
    f.base(4, 0x400100);
    f.mem.write<u32>(0x400100, 0x3F800000u);
    rt::lwc1(f.ctx, 7, 4, 0);
    CHECK(f.ctx.fpr[7] == 0x3F800000u);
    rt::swc1(f.ctx, 7, 4, 4);
    CHECK(f.mem.read<u32>(0x400104) == 0x3F800000u);
    // lq into $zero performs the read but writes nothing.
    rt::lq(f.ctx, 0, 4, 0);
    CHECK(f.ctx.gpr[0].u64[0] == 0u);
    CHECK(f.ctx.gpr[0].u64[1] == 0u);
}

TEST_CASE("rt mem: hardware windows go to the bus by width at the physical address, then a check point") {
    MemFixture f;
    rt_test::RecordingBus& bus = f.hooks.bus_;
    bus.regs[0x1000F000u] = 0x00000004u;  // INTC_STAT
    f.base(4, 0xB000F000);  // KSEG1 view of INTC_STAT
    rt::lw(f.ctx, 2, 4, 0);
    REQUIRE(bus.log.size() == 1);
    CHECK_FALSE(bus.log[0].write);
    CHECK(bus.log[0].bits == 32);
    CHECK(bus.log[0].pa == 0x1000F000u);
    CHECK(f.g(2) == 4u);
    CHECK(f.hooks.checks == 1);

    // Every width, read and write, physical address passed through.
    bus.log.clear();
    f.base(4, 0x12001000);  // GS CSR
    rt::lb(f.ctx, 2, 4, 0);
    rt::lbu(f.ctx, 2, 4, 1);
    rt::lh(f.ctx, 2, 4, 2);
    rt::lhu(f.ctx, 2, 4, 2);
    rt::lwu(f.ctx, 2, 4, 4);
    rt::ld(f.ctx, 2, 4, 8);
    rt::lq(f.ctx, 2, 4, 0);
    f.ctx.gpr[5].u64[0] = 0x1122334455667788ull;
    f.ctx.gpr[5].u64[1] = 0x99AABBCCDDEEFF00ull;
    rt::sb(f.ctx, 5, 4, 0);
    rt::sh(f.ctx, 5, 4, 2);
    rt::sw(f.ctx, 5, 4, 4);
    rt::sd(f.ctx, 5, 4, 8);
    rt::sq(f.ctx, 5, 4, 0);
    const struct { bool write; unsigned bits; u32 pa; } want[] = {
        {false, 8, 0x12001000u}, {false, 8, 0x12001001u}, {false, 16, 0x12001002u}, {false, 16, 0x12001002u},
        {false, 32, 0x12001004u}, {false, 64, 0x12001008u}, {false, 128, 0x12001000u},
        {true, 8, 0x12001000u}, {true, 16, 0x12001002u}, {true, 32, 0x12001004u}, {true, 64, 0x12001008u},
        {true, 128, 0x12001000u},
    };
    REQUIRE(bus.log.size() == std::size(want));
    for (std::size_t i = 0; i < std::size(want); ++i) {
        CAPTURE(i);
        CHECK(bus.log[i].write == want[i].write);
        CHECK(bus.log[i].bits == want[i].bits);
        CHECK(bus.log[i].pa == want[i].pa);
    }
    CHECK(bus.log[7].lo == 0x88u);
    CHECK(bus.log[8].lo == 0x7788u);
    CHECK(bus.log[9].lo == 0x55667788u);
    CHECK(bus.log[10].lo == 0x1122334455667788ull);
    CHECK(bus.log[11].lo == 0x1122334455667788ull);
    CHECK(bus.log[11].hi == 0x99AABBCCDDEEFF00ull);
    CHECK(f.hooks.checks == 1 + 12);
    CHECK(f.mem.unmapped_accesses() == 0);

    // Read values and extension through the bus.
    bus.regs[0x10000000u] = 0xFFFFFF80u;  // T0_COUNT
    f.base(4, 0x10000000);
    rt::lb(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFF80ull);
    rt::lhu(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0xFF80u);
    rt::lw(f.ctx, 2, 4, 0);
    CHECK(f.g(2) == 0xFFFFFFFFFFFFFF80ull);
    rt::lq(f.ctx, 3, 4, 0);
    CHECK(f.ctx.gpr[3].u64[0] == 0xFFFFFF80u);
    CHECK(f.ctx.gpr[3].u64[1] == ~0xFFFFFF80ull);

    // FPU / VU0 transfers to a FIFO window (VIF0 FIFO 0x10004000).
    bus.log.clear();
    f.base(4, 0x10004000);
    f.ctx.fpr[1] = 0x40000000u;
    rt::swc1(f.ctx, 1, 4, 0);
    rt::lwc1(f.ctx, 2, 4, 0);
    CHECK(f.ctx.fpr[2] == 0x40000000u);
    f.ctx.vu0.vf[4][0] = 1; f.ctx.vu0.vf[4][1] = 2; f.ctx.vu0.vf[4][2] = 3; f.ctx.vu0.vf[4][3] = 4;
    rt::sqc2(f.ctx, 4, 4, 0);
    rt::lqc2(f.ctx, 5, 4, 0);
    REQUIRE(bus.log.size() == 4);
    CHECK(bus.log[0].bits == 32);
    CHECK(bus.log[2].bits == 128);
    CHECK(bus.log[2].lo == 0x0000000200000001ull);
    CHECK(bus.log[3].bits == 128);
    CHECK(f.ctx.vu0.vf[5][0] == 1u);

    // Unaligned forms on a register: the containing aligned unit, read-modify-write for stores.
    bus.log.clear();
    f.base(4, 0x1000F012);
    rt::lwl(f.ctx, 2, 4, 0);
    rt::swr(f.ctx, 5, 4, 0);
    REQUIRE(bus.log.size() == 3);
    CHECK(bus.log[0].pa == 0x1000F010u);
    CHECK(bus.log[1].pa == 0x1000F010u);
    CHECK_FALSE(bus.log[1].write);
    CHECK(bus.log[2].write);
    CHECK(bus.log[2].bits == 32);
}

TEST_CASE("rt mem: a load into $zero from a register still performs the read") {
    MemFixture f;
    f.base(4, 0x1000F000);
    rt::lw(f.ctx, 0, 4, 0);
    CHECK(f.hooks.bus_.log.size() == 1);
    CHECK(f.ctx.gpr[0].u64[0] == 0u);
    CHECK(f.hooks.checks == 1);
}

TEST_CASE("rt mem: misaligned natural accesses are fatal (EE address error)") {
    MemFixture f;
    f.base(4, 0x100002);
    try {
        rt::lw(f.ctx, 2, 4, 0);
        FAIL("lw at 0x100002 returned");
    } catch (const FatalEvent& e) {
        CHECK(contains(e.what, "lw: address error: unaligned 4-byte load at virtual 0x00100002"));
        CHECK(e.ctx == &f.ctx);
    }
    CHECK_THROWS_AS(rt::lh(f.ctx, 2, 4, 1), FatalEvent);
    CHECK_THROWS_AS(rt::sh(f.ctx, 2, 4, 1), FatalEvent);
    CHECK_THROWS_AS(rt::ld(f.ctx, 2, 4, 2), FatalEvent);
    CHECK_THROWS_AS(rt::sd(f.ctx, 2, 4, 2), FatalEvent);
    CHECK_THROWS_AS(rt::sw(f.ctx, 2, 4, 1), FatalEvent);
    CHECK_THROWS_AS(rt::lwc1(f.ctx, 2, 4, 1), FatalEvent);
    CHECK_THROWS_AS(rt::swc1(f.ctx, 2, 4, 1), FatalEvent);
    // A misaligned access to a register window is an address error too, not a bus access.
    f.base(4, 0x1000F001);
    CHECK_THROWS_AS(rt::lw(f.ctx, 2, 4, 0), FatalEvent);
    CHECK(f.hooks.bus_.log.empty());
    // lb/sb, the unaligned forms and LQ are never misaligned.
    f.base(4, 0x100003);
    rt::lb(f.ctx, 2, 4, 0);
    rt::lwl(f.ctx, 2, 4, 0);
    rt::lq(f.ctx, 2, 4, 0);
}

TEST_CASE("rt mem: an address that resolves nowhere is fatal and names the address") {
    MemFixture f;
    for (u32 va : {0x02000000u, 0x0FFFFFF0u, 0x10010000u, 0x12002000u, 0x70004000u, 0x1E000000u}) {
        CAPTURE(va);
        f.base(4, va);
        try {
            rt::sw(f.ctx, 2, 4, 0);
            FAIL("store returned");
        } catch (const FatalEvent& e) {
            char want[64];
            std::snprintf(want, sizeof want, "sw: unmapped 4-byte store at virtual 0x%08x", va);
            CHECK(contains(e.what, want));
            CHECK(contains(e.what, "host return address"));
        }
    }
    CHECK(f.hooks.bus_.log.empty());
    CHECK(f.hooks.checks == 0);
}

TEST_CASE("rt mem: an EEContext without EEMemory is fatal, not a crash") {
    MemFixture f;
    f.ctx.memory = nullptr;
    f.base(4, 0x100000);
    try {
        rt::lw(f.ctx, 2, 4, 0);
        FAIL("lw returned");
    } catch (const FatalEvent& e) {
        CHECK(contains(e.what, "no EEMemory bound"));
    }
}
