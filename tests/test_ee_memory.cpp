#include <doctest.h>

#include "p3fes/ee_memory.h"

using namespace p3fes;

TEST_CASE("EEMemory round-trips scalar reads and writes in main RAM") {
    EEMemory mem;

    // Typical ELF load address for the EE (and this title: base 0x00100000).
    mem.write<u32>(0x00100000, 0xDEADBEEFu);
    CHECK(mem.read<u32>(0x00100000) == 0xDEADBEEFu);
    CHECK(mem.read<u8>(0x00100000) == 0xEF);
    CHECK(mem.read<u8>(0x00100003) == 0xDE);
    CHECK(mem.read<u16>(0x00100002) == 0xDEADu);

    mem.write<u64>(0x01FFFFF8, 0x0102030405060708ull);  // last quadword of 32 MiB
    CHECK(mem.read<u64>(0x01FFFFF8) == 0x0102030405060708ull);

    u128 q = u128::from_u64(0xAAAAAAAABBBBBBBBull);
    q.u64[1] = 0xCCCCCCCCDDDDDDDDull;
    mem.write<u128>(0x00200000, q);
    const u128 back = mem.read<u128>(0x00200000);
    CHECK(back.u64[0] == q.u64[0]);
    CHECK(back.u64[1] == q.u64[1]);

    CHECK(mem.unmapped_accesses() == 0);
}

TEST_CASE("KSEG0/KSEG1 and KUSEG mirrors alias main RAM") {
    EEMemory mem;

    mem.write<u32>(0x00123450, 0x11111111u);
    CHECK(mem.read<u32>(0x80123450) == 0x11111111u);   // KSEG0
    CHECK(mem.read<u32>(0xA0123450) == 0x11111111u);   // KSEG1
    CHECK(mem.read<u32>(0x20123450) == 0x11111111u);   // uncached
    CHECK(mem.read<u32>(0x30123450) == 0x11111111u);   // uncached accelerated

    mem.write<u32>(0x80123450, 0x22222222u);
    CHECK(mem.read<u32>(0x00123450) == 0x22222222u);

    CHECK(mem.unmapped_accesses() == 0);
}

TEST_CASE("scratchpad is a separate 16 KiB region at 0x70000000") {
    EEMemory mem;

    mem.write<u32>(0x70000000, 0x5CA7C4ADu);
    mem.write<u32>(0x70003FFC, 0x0000BEEFu);
    CHECK(mem.read<u32>(0x70000000) == 0x5CA7C4ADu);
    CHECK(mem.read<u32>(0x70003FFC) == 0x0000BEEFu);

    // Scratchpad storage is distinct from main RAM.
    CHECK(mem.main_ram()[0] == 0);
    CHECK(mem.scratchpad()[0] == 0xAD);

    CHECK(mem.unmapped_accesses() == 0);

    // One byte past the end is not scratchpad and lands in the (unmapped)
    // 0x70004000 region.
    CHECK(mem.read<u32>(0x70004000) == 0);
    CHECK(mem.unmapped_accesses() == 1);
}

TEST_CASE("BIOS window is backed; hardware registers are not") {
    EEMemory mem;

    mem.write<u32>(0xBFC00000, 0x3C1A8000u);   // KSEG1 view of ROM start
    CHECK(mem.read<u32>(0x1FC00000) == 0x3C1A8000u);
    CHECK(mem.read<u32>(0x9FC00000) == 0x3C1A8000u);
    CHECK(mem.unmapped_accesses() == 0);

    // ADR-0013: the windows are reported by is_hw() (the rt adapter routes them to RtHooks::bus())
    // but are still not backed by resolve()/read()/write().
    CHECK(EEMemory::is_hw(0x10000000));
    CHECK(EEMemory::is_hw(0x12000000));
    CHECK(mem.resolve(0x10000000, 4) == nullptr);
    CHECK(mem.resolve(0x12000000, 4) == nullptr);

    mem.write<u32>(0x10000000, 1u);           // DMAC/INTC region: dropped
    CHECK(mem.read<u32>(0x12000000) == 0);    // GS privileged: reads as zero
    CHECK(mem.unmapped_accesses() == 2);

    // Accesses straddling the end of a region are rejected whole.
    CHECK(mem.resolve(0x01FFFFFE, 4) == nullptr);
    CHECK(mem.resolve(0x70003FFE, 4) == nullptr);
    CHECK(mem.resolve(0x1FFFFFFE, 4) == nullptr);
}

TEST_CASE("is_hw: EE register and GS privileged windows, physical and through KSEG0/KSEG1 only") {
    // Physical windows (ADR-0013 consequences): 0x10000000-0x1000FFFF and 0x12000000-0x12001FFF.
    CHECK(EEMemory::is_hw_physical(0x10000000u));
    CHECK(EEMemory::is_hw_physical(0x1000FFFFu));
    CHECK_FALSE(EEMemory::is_hw_physical(0x10010000u));
    CHECK_FALSE(EEMemory::is_hw_physical(0x0FFFFFFFu));
    CHECK(EEMemory::is_hw_physical(0x12000000u));
    CHECK(EEMemory::is_hw_physical(0x12001FFFu));
    CHECK_FALSE(EEMemory::is_hw_physical(0x12002000u));
    CHECK_FALSE(EEMemory::is_hw_physical(0x11FFFFFFu));

    // Virtual: identity KUSEG and the KSEG0/KSEG1 windows.
    CHECK(EEMemory::is_hw(0x1000F000u));   // INTC_STAT
    CHECK(EEMemory::is_hw(0xB000F000u));   // KSEG1 view
    CHECK(EEMemory::is_hw(0x9000E010u));   // KSEG0 view of D_STAT
    CHECK(EEMemory::is_hw(0xB2001000u));   // GS CSR through KSEG1
    CHECK_FALSE(EEMemory::is_hw(0x10010000u));
    CHECK_FALSE(EEMemory::is_hw(0x12002000u));
    // RAM, BIOS and scratchpad are never hardware.
    CHECK_FALSE(EEMemory::is_hw(0x00100000u));
    CHECK_FALSE(EEMemory::is_hw(0x1FC00000u));
    CHECK_FALSE(EEMemory::is_hw(0x70000000u));
    // Segments whose `& 0x1FFFFFFF` fold would land on a register address are not hardware.
    CHECK_FALSE(EEMemory::is_hw(0x70004000u));  // just past the scratchpad -> 0x10004000 by masking
    CHECK_FALSE(EEMemory::is_hw(0x30000000u));
    CHECK_FALSE(EEMemory::is_hw(0x50000000u));
    CHECK_FALSE(EEMemory::is_hw(0xF0000000u));
    CHECK_FALSE(EEMemory::is_hw(0xD2000000u));
}
