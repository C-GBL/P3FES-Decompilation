// Card (card.h): the raw 8 MiB image and its NAND read / program / erase rules.
#include "p3fes/hle/memcard/card.h"
#include "p3fes/state_io.h"

#include <algorithm>
#include <cstring>

namespace p3fes::hle::memcard {

void Card::state(StateIo& io) {
    io.expect(static_cast<u64>(image_.size()), "memory card image size");
    io(image_, dirty_, dirty_mark_, stats_);
}

Card::Card(std::vector<u8> image, std::string name)
    : image_(std::move(image)), name_(std::move(name)), dirty_mark_(kPages, 0) {
    image_.resize(kImageSize, kErasedByte);  // from_image() checks the size; this keeps every page addressable
}

std::shared_ptr<Card> Card::blank(std::string name) {
    return std::make_shared<Card>(std::vector<u8>(kImageSize, kErasedByte), std::move(name));
}

std::shared_ptr<Card> Card::from_image(std::vector<u8> image, std::string name) {
    if (image.size() != kImageSize) return nullptr;
    return std::make_shared<Card>(std::move(image), std::move(name));
}

std::span<const u8> Card::raw_page(u32 page) const {
    if (page >= kPages) return {};
    return std::span<const u8>(image_).subspan(std::size_t{page} * kRawPageSize, kRawPageSize);
}

bool Card::read(u32 page, std::span<u8> out) const {
    if (page >= kPages || out.size() > kRawPageSize) {
        ++stats_.rejected;
        return false;
    }
    std::memcpy(out.data(), image_.data() + std::size_t{page} * kRawPageSize, out.size());
    ++stats_.page_reads;
    return true;
}

void Card::mark(u32 page) {
    if (dirty_mark_[page]) return;
    dirty_mark_[page] = 1;
    dirty_.insert(std::upper_bound(dirty_.begin(), dirty_.end(), page), page);
}

bool Card::program(u32 page, std::span<const u8> in) {
    if (page >= kPages || in.size() > kRawPageSize) {
        ++stats_.rejected;
        return false;
    }
    u8* p = image_.data() + std::size_t{page} * kRawPageSize;
    bool conflict = false;
    bool changed = false;
    for (std::size_t i = 0; i < in.size(); ++i) {
        const u8 v = static_cast<u8>(p[i] & in[i]);
        if (v != in[i]) conflict = true;
        if (v != p[i]) changed = true;
        p[i] = v;
    }
    if (conflict) ++stats_.program_conflicts;
    if (changed) mark(page);
    ++stats_.page_programs;
    return true;
}

bool Card::erase_block(u32 page) {
    if (page >= kPages) {
        ++stats_.rejected;
        return false;
    }
    const u32 first = page - page % kPagesPerBlock;
    for (u32 pg = first; pg < first + kPagesPerBlock; ++pg) {
        u8* p = image_.data() + std::size_t{pg} * kRawPageSize;
        bool changed = false;
        for (u32 i = 0; i < kRawPageSize; ++i)
            if (p[i] != kErasedByte) {
                changed = true;
                break;
            }
        if (!changed) continue;
        std::memset(p, kErasedByte, kRawPageSize);
        mark(pg);
    }
    ++stats_.block_erases;
    return true;
}

bool Card::flush(std::string* error) {
    if (dirty_.empty() || !backing_) return true;
    std::string err;
    if (!backing_->store(*this, dirty_, err)) {
        if (error) *error = err;
        return false;
    }
    for (u32 p : dirty_) dirty_mark_[p] = 0;
    dirty_.clear();
    ++stats_.flushes;
    return true;
}

}  // namespace p3fes::hle::memcard
