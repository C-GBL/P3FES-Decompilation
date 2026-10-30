// Private: a model of MC2_S1.IRX (disc LIB31/MC2_S1.IRX, the memory-card driver libmc2 talks to through
// DBCMAN) over hle::memcard::Card. DBCMAN calls the driver's table entry 5 (.text 0x1FA4 -> 0x2024) with
// the `cmd` and the 48-byte request block of every sceDbcSendData3 (docs/ANALYSIS/17_memory_card.md §3).
// Everything below is read from the module's instructions (offsets are .text/.data of the IRX as loaded at
// 0) and from the EE senders, the _sceMcCore* functions of libmc2 (0x51AFD8-0x51C0BC).
#pragma once

#include <array>
#include <functional>
#include <memory>
#include <span>

#include "p3fes/ee_types.h"
#include "p3fes/hle/memcard/card.h"

namespace p3fes::hle::sif::detail {

// Command numbers: the jump table at .rodata 0x4BE0 (index cmd - 1) and the EE senders.
namespace mc2cmd {
inline constexpr u32 kReadPage = 1;        // _sceMcCoreReadPage2 0x51B708 (ECC flag at +36)
inline constexpr u32 kWritePage = 2;       // _sceMcCoreWritePage 0x51B8F0 (erase + backup-block protocol)
inline constexpr u32 kGetSpec = 3;         // _sceMcCoreGetCardSpec 0x51AFD8
inline constexpr u32 kCheckNewCard = 4;    // _sceMcCoreCheckNewCard 0x51B1B0
inline constexpr u32 kCheckWriteBack = 5;  // (no EE sender) the interrupted-write probe of command 6
inline constexpr u32 kWriteBack = 6;       // _sceMcCoreWriteBack 0x51B4A0
inline constexpr u32 kCopyBlock = 7;       // (no EE sender)
inline constexpr u32 kReadPageRaw = 8;     // (no EE sender) page + ECC bytes, count forced to 1
inline constexpr u32 kEraseBlock = 9;      // _sceMcCoreBlockErase 0x51BBD8
inline constexpr u32 kReadClock = 10;      // _sceMcCoreReadClock 0x51B5F0
inline constexpr u32 kWriteSameData = 11;  // _sceMcCoreWriteSameData 0x51BA88 -- a no-op in this MC2_S1
inline constexpr u32 kAuthenticate = 12;   // _sceMcCoreAuthentication 0x51B3B0
inline constexpr u32 kClearNewCard = 13;   // _sceMcCoreClearNewCardFlag 0x51B2C0
inline constexpr u32 kWriteFast = 16;      // _sceMcCoreWritePageFast 0x51BF40 (not modelled)
inline constexpr u32 kReadFast = 17;       // _sceMcCoreReadPageFast 0x51BD10 (not modelled)
}  // namespace mc2cmd

// The 48-byte request block (libmc2's 0x985580; the IOP keeps a pointer to it at .bss 0x4F40).
namespace mc2req {
inline constexpr std::size_t kPage = 0, kCount = 4, kPageSize = 8, kPagesPerBlock = 12, kCardPages = 16;
inline constexpr std::size_t kBackup1 = 20, kBackup2 = 24, kSrcBlock = 28, kDstBlock = 32, kEcc = 36;
inline constexpr std::size_t kEeData = 40, kEeScratch = 44, kSize = 48;
}  // namespace mc2req

// The 128-byte response block (.bss 0x4F48): +0 sequence counter, +4 device, +8 status, +12 payload.
inline constexpr std::size_t kMc2ResponseSize = 128;

class Mc2s1Model {
public:
    // What DBCMAN provides to the driver (its exports 8 and 9 and sifcmd's sceSifGetOtherData).
    struct Io {
        // dbcman_9 (DBCMAN .text 0x428): to the linked socket's EE buffer 0 + offset.
        std::function<void(u32 offset, std::span<const u8> bytes)> to_buf0;
        // dbcman_8 (DBCMAN .text 0x31C): to the socket's EE buffer `index` (0 or 1).
        std::function<void(u32 index, std::span<const u8> bytes)> to_buf;
        // sceSifGetOtherData (sifcmd 23): EE memory -> IOP. false: not EE memory.
        std::function<bool(u32 ee_addr, std::span<u8> out)> from_ee;
        // Not-modelled command (logged once by the caller).
        std::function<void(u32 cmd, const char* what)> unmodelled;
    };

    struct Stats {
        u64 commands = 0;
        std::array<u64, 18> by_cmd{};  // index = cmd (0 and > 17 in [0])
        u64 rejected_new_card = 0;     // answered 2 while the new-card flag was set
        u64 ecc_mismatches = 0;        // pages whose stored ECC disagreed (MC2_S1 never checks; counted only)
    };

    Mc2s1Model(std::shared_ptr<memcard::Card> card, std::array<u8, 8> rtc);

    // Driver entry 5: returns the status word DBCMAN stores as the call's result. `size` is the request's
    // size word (set to 48 on the normal path); `req` the request block in DBCMAN's buffer (command 8
    // rewrites its count).
    s32 send(u32 device, u32 cmd, u32& size, std::span<u8> req, const Io& io);

    // An IOP reboot reloads the module: counter 0, toggle 0, buffers zero, new-card flag set (.text 0x188).
    void reboot();

    memcard::Card* card() const { return card_.get(); }
    const Stats& stats() const { return stats_; }
    void state(StateIo& io);  // machine state (iop_state.cpp); the card image is saved by IopCore

private:
    std::shared_ptr<memcard::Card> card_;
    std::array<u8, 8> rtc_;
    std::array<u8, kMc2ResponseSize> resp_{};  // .bss 0x4F48
    std::array<u8, 1088> page_buf_{};          // .bss 0x8CE0 (page + ECC, kept between commands)
    std::array<u8, 1088> check_buf_{};         // .bss 0x88A0 (read-back for verification)
    bool new_card_ = true;                     // .bss 0x4E08 (port 2)
    u32 toggle_ = 0;                           // .data 0x4CD0
    Stats stats_;

    // Per-command state the IRX keeps in globals (.bss 0x4FC8 / 0x4FCC).
    u32 ecc_size_ = 0, xfer_size_ = 0;

    void set_status(s32 s);
    s32 status() const;
    void respond_toggled(const Io& io);
    bool read_page(u32 page, std::span<u8> buf);
    bool program_page(u32 page, std::span<const u8> buf);
    bool erase(u32 page);
    void ecc_into(std::span<u8> buf, u32 data_size) const;
    s32 copy_block(s32 dst, s32 src, std::span<const u8> req);
    s32 check_write_back(std::span<const u8> req, s32& block);
    s32 write_back(std::span<const u8> req);
    s32 write_pages(std::span<const u8> req, const Io& io);
};

}  // namespace p3fes::hle::sif::detail
