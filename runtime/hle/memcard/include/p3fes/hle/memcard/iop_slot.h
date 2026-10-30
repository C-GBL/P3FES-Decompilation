// What the host plugs into the IOP HLE's DBCMAN + MC2_S1 model (runtime/hle/sif/iop/srv_dbcman.cpp):
// hle::sif::IopConfig::memcard points at one of these (nullptr = no card, the behaviour before this model).
//
// Only MEMORY CARD slot 1 exists for this game: MC2_S1.IRX registers and polls DBC port 2 only (its setup
// loop at .text 0x170-0x1D8 runs once), so a card in slot 2 is never seen (PCSX2 has one there too, and
// the PCSX2 atlus_logo IOP state holds a single DBCMAN device, port 2 slot 0 -- obs).
#pragma once

#include <array>
#include <memory>

#include "p3fes/ee_types.h"
#include "p3fes/hle/memcard/card.h"

namespace p3fes::hle::memcard {

struct IopSlotConfig {
    std::shared_ptr<Card> slot1;  // nullptr: no card inserted
    // Virtual EE cycles from an MC2_S1 command arriving (sceDbcSendData3) to its RPC end being queued.
    // At least 1, so the completion is delivered at a later check point than the issuing syscall (the
    // cdvdfsv rule). The real driver's SIO2 transfers take milliseconds; inf, not measured.
    u64 command_latency_cycles = 1;
    // sceCdReadClock's answer for MC2_S1 command 10 (cdvdman export 24): sceCdCLOCK
    // {stat, second, minute, hour, pad, day, month, year} in BCD. Fixed for deterministic runs
    // (ADR-0013 §4); libmc2 stamps created/modified times of new directory entries with it.
    std::array<u8, 8> rtc = {0x00, 0x00, 0x00, 0x12, 0x00, 0x01, 0x01, 0x26};  // 2026-01-01 12:00:00
};

}  // namespace p3fes::hle::memcard
