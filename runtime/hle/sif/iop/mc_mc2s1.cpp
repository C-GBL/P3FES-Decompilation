// MC2_S1.IRX model (mc_mc2s1.h). Each step cites the IRX instruction it follows (.text offsets with the
// module loaded at 0; disc LIB31/MC2_S1.IRX, objdump'd with the ps2dev toolchain).
#include "mc_mc2s1.h"

#include <algorithm>
#include <cstring>

#include "p3fes/hle/memcard/ecc.h"
#include "p3fes/hle/sif/protocol.h"

namespace p3fes::hle::sif::detail {
namespace {

s32 field(std::span<const u8> req, std::size_t off) { return static_cast<s32>(load32(req, off)); }

}  // namespace

Mc2s1Model::Mc2s1Model(std::shared_ptr<memcard::Card> card, std::array<u8, 8> rtc) : card_(std::move(card)), rtc_(rtc) {}

void Mc2s1Model::reboot() {
    resp_.fill(0);
    page_buf_.fill(0);
    check_buf_.fill(0);
    new_card_ = true;  // .text 0x188: the port-2 flag is set when the module starts
    toggle_ = 0;
    ecc_size_ = xfer_size_ = 0;
}

void Mc2s1Model::set_status(s32 s) { store32(resp_, 8, static_cast<u32>(s)); }
s32 Mc2s1Model::status() const { return static_cast<s32>(load32(resp_, 8)); }

void Mc2s1Model::respond_toggled(const Io& io) {
    // .text 0x1E8C: dbcman_8(device, toggle, block, 128), then toggle = !toggle.
    if (io.to_buf) io.to_buf(toggle_, resp_);
    toggle_ ^= 1u;
}

bool Mc2s1Model::read_page(u32 page, std::span<u8> buf) {
    return static_cast<s32>(page) >= 0 && card_->read(page, buf);  // .text 0xCF8 (SIO2 0x81 0x23 / 0x43)
}

bool Mc2s1Model::program_page(u32 page, std::span<const u8> buf) {
    return static_cast<s32>(page) >= 0 && card_->program(page, buf);  // .text 0x108C (0x81 0x22 / 0x42)
}

bool Mc2s1Model::erase(u32 page) {
    return static_cast<s32>(page) >= 0 && card_->erase_block(page);  // .text 0xB00 (0x81 0x21 / 0x82)
}

void Mc2s1Model::ecc_into(std::span<u8> buf, u32 data_size) const {
    // .text 0x2BDC: nothing when the ECC size is 0, else 3 bytes per 128 right after the data.
    if (ecc_size_ == 0) return;
    memcard::ecc_compute(buf.first(data_size), buf.subspan(data_size, ecc_size_));
}

s32 Mc2s1Model::copy_block(s32 dst, s32 src, std::span<const u8> req) {
    // .text 0x2EF0: bounds, erase dst, then every page src -> dst with a read-back compare.
    const s32 ppb = field(req, mc2req::kPagesPerBlock), card_pages = field(req, mc2req::kCardPages);
    if (card_pages < (dst + 1) * ppb || dst < 0) return 0;
    if (card_pages < (src + 1) * ppb || src < 0) return 0;
    if (!erase(static_cast<u32>(dst * ppb))) return 0;
    const auto buf = std::span<u8>(page_buf_).first(xfer_size_);
    const auto chk = std::span<u8>(check_buf_).first(xfer_size_);
    for (s32 i = 0; i < ppb; ++i) {
        if (!read_page(static_cast<u32>(src * ppb + i), buf)) return 0;
        if (!program_page(static_cast<u32>(dst * ppb + i), buf)) return 0;
        if (!read_page(static_cast<u32>(dst * ppb + i), chk)) return 0;
        if (std::memcmp(buf.data(), chk.data(), buf.size()) != 0) return 0;
    }
    return 1;
}

s32 Mc2s1Model::check_write_back(std::span<const u8> req, s32& block) {
    // .text 0x2C88: page 0 of backup block 2 names the block an interrupted write was backing up; page 1
    // repeats it once the backup copy in backup block 1 is complete.
    block = -1;
    const s32 ppb = field(req, mc2req::kPagesPerBlock), card_pages = field(req, mc2req::kCardPages);
    const s32 b2 = field(req, mc2req::kBackup2);
    const auto buf = std::span<u8>(page_buf_).first(xfer_size_);
    if (!read_page(static_cast<u32>(b2 * ppb), buf)) return 0;
    const s32 marked = static_cast<s32>(load32(page_buf_, 0));
    if (marked == -1) return 1;
    if (card_pages < (marked + 1) * ppb) return 0;
    if (!read_page(static_cast<u32>(b2 * ppb + 1), buf)) return 0;
    const s32 confirmed = static_cast<s32>(load32(page_buf_, 0));
    if (confirmed != -1 && confirmed == marked) {
        block = marked;
        return 2;
    }
    erase(static_cast<u32>(b2 * ppb));  // result ignored (.text 0x2DB4 -> li v0, 1)
    return 1;
}

s32 Mc2s1Model::write_back(std::span<const u8> req) {
    // .text 0x2E8C / 0x2DE4: restore the marked block from backup block 1, then erase backup block 2.
    s32 block = -1;
    const s32 r = check_write_back(req, block);
    if (r != 2) return r;
    const s32 ppb = field(req, mc2req::kPagesPerBlock), card_pages = field(req, mc2req::kCardPages);
    if (card_pages < (block + 1) * ppb || block < 0) return 0;
    if (!copy_block(block, field(req, mc2req::kBackup1), req)) return 0;
    return erase(static_cast<u32>(field(req, mc2req::kBackup2) * ppb)) ? 2 : 0;
}

s32 Mc2s1Model::write_pages(std::span<const u8> req, const Io& io) {
    // .text 0x2460-0x29E8. Per erase block touched: optional backup (block number into page 0 of backup
    // block 2, the whole block copied to backup block 1, the number again into page 1), erase the block,
    // program the requested pages from EE memory (each read back), restore the block's other pages from
    // the backup copy (each verified), erase backup block 2. Without the backup (backup block 2 == 0, as
    // before libmc2 has read a superblock, or a write to a backup block itself) the other pages of the
    // block are left erased.
    const s32 ppb = field(req, mc2req::kPagesPerBlock), page_size = field(req, mc2req::kPageSize);
    const s32 end = field(req, mc2req::kPage) + field(req, mc2req::kCount);
    const s32 b1 = field(req, mc2req::kBackup1), b2 = field(req, mc2req::kBackup2);
    const auto buf = std::span<u8>(page_buf_).first(xfer_size_);
    const auto chk = std::span<u8>(check_buf_).first(xfer_size_);
    auto fail = [&] {
        set_status(0);
        return 0;
    };
    u32 ee_off = 0;
    s32 pg = field(req, mc2req::kPage);
    do {
        const s32 blk_page = pg - pg % ppb;
        const bool backup = blk_page != b1 * ppb && blk_page != b2 * ppb && b2 != 0;
        if (backup) {
            store32(page_buf_, 0, static_cast<u32>(blk_page / ppb));
            ecc_into(page_buf_, static_cast<u32>(page_size));
            if (!program_page(static_cast<u32>(b2 * ppb), buf)) return fail();
            if (!copy_block(b1, blk_page / ppb, req)) return fail();
            store32(page_buf_, 0, static_cast<u32>(blk_page / ppb));
            ecc_into(page_buf_, static_cast<u32>(page_size));
            if (!program_page(static_cast<u32>(b2 * ppb + 1), buf)) return fail();
        }
        if (!erase(static_cast<u32>(blk_page))) return fail();
        for (s32 i = 0; i < ppb; ++i) {
            if (i == pg % ppb && pg < end) {
                // sceSifGetOtherData from EE req+40 + offset (an unaligned source is fetched from the
                // 64-byte line below and moved into place, .text 0x2780-0x27CC: the same bytes).
                if (io.from_ee) io.from_ee(static_cast<u32>(field(req, mc2req::kEeData)) + ee_off, buf.first(static_cast<u32>(page_size)));
                ecc_into(page_buf_, static_cast<u32>(page_size));
                bool ok = program_page(static_cast<u32>(pg), buf);
                if (ok) ok = read_page(static_cast<u32>(pg), buf);  // read back; the ECC check (.text 0x2C78) always passes
                if (!ok) set_status(0);
                ++pg;
                ee_off += static_cast<u32>(page_size);
                if (status() == 0) return 0;  // .text 0x2948
            } else if (backup) {
                if (!read_page(static_cast<u32>(b1 * ppb + i), buf)) return fail();
                if (!program_page(static_cast<u32>(blk_page + i), buf)) return fail();
                if (!read_page(static_cast<u32>(blk_page + i), chk)) return fail();
                // A mismatch only sets the status; the loop goes on (.text 0x2918-0x2940 -> 0x295C).
                set_status(std::memcmp(buf.data(), chk.data(), buf.size()) == 0 ? 1 : 0);
            }
        }
        if (backup && !erase(static_cast<u32>(b2 * ppb))) return fail();
    } while (pg < end);
    return status();
}

s32 Mc2s1Model::send(u32 device, u32 cmd, u32& size, std::span<u8> req, const Io& io) {
    ++stats_.commands;
    ++stats_.by_cmd[cmd < stats_.by_cmd.size() ? cmd : 0];
    // .text 0x30E8: only device 0 (port 2) exists; anything else returns 0 with no DMA (.text 0x207C).
    if (device != 0 || !card_ || req.size() < mc2req::kSize) return 0;

    // .text 0x2084-0x20B8: while the new-card flag is set only commands 4 and 13 run; the others DMA the
    // previous response block with status 2 (no counter increment, no clear).
    if (new_card_ && cmd != mc2cmd::kCheckNewCard && cmd != mc2cmd::kClearNewCard) {
        ++stats_.rejected_new_card;
        set_status(2);
        respond_toggled(io);
        return 2;
    }
    // .text 0x20BC-0x2178: clear the payload, size word 48, device, status 1, counter + 1, ECC sizes.
    std::fill(resp_.begin() + 12, resp_.end(), u8{0});
    size = 48;
    store32(resp_, 4, device);
    set_status(1);
    store32(resp_, 0, load32(resp_, 0) + 1);
    const s32 page_size = field(req, mc2req::kPageSize);
    const s32 ppb = field(req, mc2req::kPagesPerBlock);
    const bool with_ecc = field(req, mc2req::kEcc) != 0 || cmd == mc2cmd::kReadPageRaw;
    // Guard (not in the IRX, which would divide by zero or overrun its page buffers): the commands that use
    // the geometry need the card's. The others run with whatever the block holds -- libmc2's
    // _sceMcCoreGetCardSpec 0x51B044 sends it zeroed.
    const bool uses_pages = cmd == mc2cmd::kReadPage || cmd == mc2cmd::kWritePage || cmd == mc2cmd::kReadPageRaw;
    const bool uses_blocks = cmd == mc2cmd::kWritePage || cmd == mc2cmd::kCheckWriteBack || cmd == mc2cmd::kWriteBack ||
                             cmd == mc2cmd::kCopyBlock || cmd == mc2cmd::kEraseBlock;
    const bool page_ok = page_size >= 0 && page_size <= static_cast<s32>(memcard::kPageSize) && page_size % 128 == 0;
    if ((uses_pages && (!page_ok || page_size == 0)) || (uses_blocks && (ppb <= 0 || !page_ok))) {
        if (io.unmodelled) io.unmodelled(cmd, "request with a page size / block size the card does not have (status 0)");
        set_status(0);
        respond_toggled(io);
        return 0;
    }
    ecc_size_ = with_ecc && page_ok ? static_cast<u32>(page_size / 128 * 3) : 0u;
    xfer_size_ = page_ok ? static_cast<u32>(page_size) + ecc_size_ : 0u;

    // .text 0x217C-0x2214: commands 1, 2, 5, 6, 8, 11 check the page range and both backup blocks.
    if (cmd == 1 || cmd == 2 || cmd == 5 || cmd == 6 || cmd == 8 || cmd == 11) {
        const s32 card_pages = field(req, mc2req::kCardPages);
        if (card_pages < field(req, mc2req::kPage) + field(req, mc2req::kCount) ||
            card_pages < (field(req, mc2req::kBackup1) + 1) * ppb || card_pages < (field(req, mc2req::kBackup2) + 1) * ppb) {
            set_status(0);
            respond_toggled(io);
            return 0;
        }
    }

    auto to_buf0 = [&](u32 off, std::span<const u8> b) {
        if (io.to_buf0) io.to_buf0(off, b);
    };
    switch (cmd) {
    case mc2cmd::kReadPage:
    case mc2cmd::kReadPageRaw: {
        // .text 0x230C-0x2458: page by page into buffer 0 + 128 (+ page size per page for command 1;
        // command 8 always at +128 with the page, its ECC bytes and the rest of the 128-byte line + 128),
        // then the response block to buffer 0 + 0 -- not toggled, SyncDmaForRead 0x51ADE0 reads buffer 0.
        if (cmd == mc2cmd::kReadPageRaw) store32(req, mc2req::kCount, 1);
        const s32 count = field(req, mc2req::kCount);
        u32 off = 128;
        for (s32 i = 0; i < count; ++i) {
            const u32 page = static_cast<u32>(field(req, mc2req::kPage) + i);
            const bool ok = read_page(page, std::span<u8>(page_buf_).first(xfer_size_));
            if (!ok) set_status(0);
            if (ok && ecc_size_ != 0) {
                std::array<u8, memcard::kPageSize> copy{};
                std::memcpy(copy.data(), page_buf_.data(), static_cast<u32>(page_size));
                if (memcard::ecc_check(std::span<u8>(copy.data(), static_cast<u32>(page_size)),
                                       std::span<const u8>(page_buf_.data() + page_size, ecc_size_)) != memcard::EccCheck::Ok)
                    ++stats_.ecc_mismatches;
            }
            if (cmd == mc2cmd::kReadPage) {
                to_buf0(off, std::span<const u8>(page_buf_).first(static_cast<u32>(page_size)));
                off += static_cast<u32>(page_size);
            } else {
                const u32 n = ((xfer_size_ + 127u) / 128u + 1u) * 128u;
                to_buf0(off, std::span<const u8>(page_buf_).first(n));
            }
        }
        to_buf0(0, resp_);
        return status();
    }
    case mc2cmd::kWritePage:
        write_pages(req, io);
        break;
    case mc2cmd::kGetSpec:
        // .text 0x29EC: the card's 8-byte spec reply (u16 page size, u16 pages per block, u32 pages).
        store32(resp_, 12, memcard::kPageSize | (memcard::kPagesPerBlock << 16));
        store32(resp_, 16, memcard::kPages);
        break;
    case mc2cmd::kCheckNewCard:
        set_status(new_card_ ? 2 : 1);  // .text 0x2A2C: card present -> new flag ? 2 : 1
        break;
    case mc2cmd::kCheckWriteBack: {
        s32 block = -1;
        set_status(check_write_back(req, block));  // .text 0x2AC0
        store32(resp_, 12, static_cast<u32>(block));
        break;
    }
    case mc2cmd::kWriteBack:
        set_status(write_back(req));  // .text 0x2AA8
        break;
    case mc2cmd::kCopyBlock:
        set_status(copy_block(field(req, mc2req::kDstBlock), field(req, mc2req::kSrcBlock), req));  // .text 0x2AE8
        break;
    case mc2cmd::kEraseBlock:
        set_status(erase(static_cast<u32>(field(req, mc2req::kDstBlock) * ppb)) ? 1 : 0);  // .text 0x2B14
        break;
    case mc2cmd::kReadClock:
        std::memcpy(resp_.data() + 12, rtc_.data(), rtc_.size());  // .text 0x2B4C: sceCdReadClock
        break;
    case mc2cmd::kAuthenticate:
        // .text 0x2B78 -> 0x6A0: the secrman card authentication over SIO2. inf: succeeds (1); no EE
        // caller outside sceMc2Unformat.
        break;
    case mc2cmd::kClearNewCard:
        new_card_ = false;  // .text 0x2A84
        break;
    case mc2cmd::kWriteFast:
    case mc2cmd::kReadFast:
        // .text 0x223C / 0x2298 -> 0x4820 / 0x4790: SIO2 DMA straight between the card and EE req+40 (not
        // modelled; libmc2's *FastFile paths are not used by the game). Fail closed: status 0; the response
        // block goes to buffer 0 as on that path.
        if (io.unmodelled) io.unmodelled(cmd, "fast page transfer not modelled (status 0)");
        set_status(0);
        to_buf0(0, resp_);
        return 0;
    case mc2cmd::kWriteSameData:
    case 14:
    case 15:
        break;  // the jump table sends these to the exit with status 1 (.text 0x2B90): a no-op in this module
    default:
        if (io.unmodelled) io.unmodelled(cmd, "command outside MC2_S1's table (status 1, as the IRX)");
        break;
    }
    respond_toggled(io);
    return status();
}

}  // namespace p3fes::hle::sif::detail
