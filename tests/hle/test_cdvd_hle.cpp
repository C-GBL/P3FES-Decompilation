// CdvdHle tests: the async N-command contract (RUNTIME_CONTRACT L-02/L-03), S-command answers
// (L-06, I-04..I-08), search-file (I-07), and whole-file reads of manifest entries on the user's disc.
#include <doctest.h>

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "hle_fixtures.h"
#include "p3fes/hle/cdvd.h"

using namespace p3fes;
using namespace p3fes::hle;

namespace {

// Records hook calls in order, as the kernel HLE would map them onto guest kernel objects.
struct HookLog {
    std::vector<std::string> calls;
    std::vector<NcmdCompletion> done;

    CompletionHooks hooks() {
        return CompletionHooks{
            [this](const NcmdCompletion& c) { calls.push_back("signal_ncmd_sema"); done.push_back(c); },
            [this](const NcmdCompletion&) { calls.push_back("clear_cb_sem"); },
        };
    }
};

constexpr std::byte kSentinel{0xCD};

bool all_sentinel(const std::vector<std::byte>& v) {
    return std::all_of(v.begin(), v.end(), [](std::byte b) { return b == kSentinel; });
}

bool matches_synth(const std::vector<std::byte>& v, u32 lsn) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        const u32 s = lsn + static_cast<u32>(i / kSectorSize);
        if (v[i] != test::synth_data_byte(s, static_cast<u32>(i % kSectorSize))) return false;
    }
    return true;
}

// A disc whose reads always fail on the host side.
class FailingDisc final : public DiscSource {
public:
    Result<std::size_t> read_sectors(u32 lsn, u32 count, std::span<std::byte> dst) override {
        auto ok = check_read(lsn, count, dst);
        if (!ok) return ok.error();
        return Error{FormatError::Truncated, "simulated host read failure"};
    }
    u32 sector_count() const override { return 1000; }
    const DiscIdentity& identity() const override { return id_; }

private:
    DiscIdentity id_;
};

}  // namespace

TEST_CASE("CdvdHle: one N-command in flight; busy rejection; non-blocking poll; completion fires once") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    HookLog log;
    CdvdHle cd(*disc, log.hooks());
    cd.set_latency(2);

    std::vector<std::byte> buf(4 * kSectorSize, kSentinel);
    auto first = cd.read(test::kSynthDataLsn, 4, buf, ReadMode{});
    REQUIRE(first.ok());
    CHECK(first.value() == Issue::Accepted);
    CHECK(cd.busy());
    CHECK(cd.status() == cd::kStatRead);
    CHECK(all_sentinel(buf));  // nothing is transferred at issue time

    // While busy every N-command and the search-file RPC is rejected (libcdvd "Ncmd fail").
    std::vector<std::byte> other(kSectorSize, kSentinel);
    auto second = cd.read(test::kSynthDataLsn + 8, 1, other, ReadMode{});
    REQUIRE(second.ok());
    CHECK(second.value() == Issue::Busy);
    auto seek = cd.seek(100);
    REQUIRE(seek.ok());
    CHECK(seek.value() == Issue::Busy);
    auto search = cd.search_file("\\DATA.BIN;1");
    REQUIRE(search.ok());
    CHECK(search->issue == Issue::Busy);
    CHECK_FALSE(search->file.has_value());

    // sceCdSync(1): busy for `latency` polls, then completes on the next one.
    CHECK(cd.sync(SyncMode::Poll) == 1);
    CHECK(cd.sync(SyncMode::Poll) == 1);
    CHECK(log.calls.empty());
    CHECK(all_sentinel(buf));
    CHECK(cd.sync(SyncMode::Poll) == 0);
    CHECK_FALSE(cd.busy());
    REQUIRE(log.calls.size() == 2);
    CHECK(log.calls[0] == "signal_ncmd_sema");  // _sceCd_cd_callback order
    CHECK(log.calls[1] == "clear_cb_sem");
    REQUIRE(log.done.size() == 1);
    CHECK(log.done[0].kind == NcmdKind::Read);
    CHECK(log.done[0].lsn == test::kSynthDataLsn);
    CHECK(log.done[0].sectors == 4);
    CHECK(log.done[0].error == cd::kErrNone);
    CHECK(matches_synth(buf, test::kSynthDataLsn));
    CHECK(all_sentinel(other));  // the rejected request never ran
    CHECK(cd.get_error() == cd::kErrNone);
    CHECK(cd.status() == cd::kStatPause);

    // Completion is delivered exactly once.
    CHECK(cd.sync(SyncMode::Poll) == 0);
    CHECK(cd.sync(SyncMode::Block) == 0);
    CHECK_FALSE(cd.service());
    CHECK(log.calls.size() == 2);
    CHECK(cd.completions() == 1);

    // The slot is free again (ncmd semaphore re-signalled).
    auto third = cd.read(test::kSynthDataLsn + 8, 1, other, ReadMode{});
    REQUIRE(third.ok());
    CHECK(third.value() == Issue::Accepted);
}

TEST_CASE("CdvdHle: sceCdSync(0) completes at once; service() alone drives completion") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    HookLog log;
    CdvdHle cd(*disc, log.hooks());

    SUBCASE("blocking sync ignores latency") {
        cd.set_latency(1000);
        std::vector<std::byte> buf(2 * kSectorSize, kSentinel);
        REQUIRE(cd.read(test::kSynthDataLsn, 2, buf, ReadMode{}).ok());
        CHECK(cd.sync(SyncMode::Block) == 0);
        CHECK(matches_synth(buf, test::kSynthDataLsn));
        CHECK(log.calls.size() == 2);
    }
    SUBCASE("service steps (recompiled sceCdSync polls guest memory instead)") {
        cd.set_latency(1);
        std::vector<std::byte> buf(kSectorSize, kSentinel);
        REQUIRE(cd.read(test::kSynthDataLsn + 1, 1, buf, ReadMode{}).ok());
        CHECK_FALSE(cd.service());
        CHECK(cd.busy());
        CHECK(cd.service());
        CHECK_FALSE(cd.busy());
        CHECK_FALSE(cd.service());
        CHECK(log.calls.size() == 2);
        CHECK(matches_synth(buf, test::kSynthDataLsn + 1));
    }
    SUBCASE("default latency 0: the first poll completes") {
        std::vector<std::byte> buf(kSectorSize, kSentinel);
        REQUIRE(cd.read(test::kSynthDataLsn, 1, buf, ReadMode{}).ok());
        CHECK(cd.sync(SyncMode::Poll) == 0);
        CHECK(log.calls.size() == 2);
    }
    SUBCASE("no hooks bound") {
        CdvdHle bare(*disc);
        std::vector<std::byte> buf(kSectorSize, kSentinel);
        REQUIRE(bare.read(test::kSynthDataLsn, 1, buf, ReadMode{}).ok());
        CHECK(bare.sync(SyncMode::Poll) == 0);
        CHECK(bare.completions() == 1);
    }
}

TEST_CASE("CdvdHle: seek is an N-command; sceCdBreak aborts with SCECdErABRT and no data") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    HookLog log;
    CdvdHle cd(*disc, log.hooks());
    cd.set_latency(5);

    auto seek = cd.seek(300);
    REQUIRE(seek.ok());
    CHECK(seek.value() == Issue::Accepted);
    CHECK(cd.status() == cd::kStatSeek);
    CHECK(cd.sync(SyncMode::Block) == 0);
    REQUIRE(log.done.size() == 1);
    CHECK(log.done[0].kind == NcmdKind::Seek);
    CHECK(log.done[0].lsn == 300u);

    std::vector<std::byte> buf(2 * kSectorSize, kSentinel);
    REQUIRE(cd.read(test::kSynthDataLsn, 2, buf, ReadMode{}).ok());
    CHECK(cd.break_ncmd() == 1);
    CHECK(cd.busy());                        // completes on the next step, like the game's break + sceCdSync(0)
    CHECK(cd.sync(SyncMode::Poll) == 0);     // latency is cancelled by the break
    REQUIRE(log.done.size() == 2);
    CHECK(log.done[1].error == cd::kErrAbort);
    CHECK(cd.get_error() == cd::kErrAbort);
    CHECK(all_sentinel(buf));
    CHECK(cd.break_ncmd() == 1);             // idle break is harmless
    CHECK(log.done.size() == 2);
    CHECK(cd.init(0) == 1);                  // sceCdInit clears the drive error
    CHECK(cd.get_error() == cd::kErrNone);
}

TEST_CASE("CdvdHle: unmodelled modes and bad ranges fail explicitly and leave the drive idle") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    CdvdHle cd(*disc);
    std::vector<std::byte> buf(4 * kSectorSize, kSentinel);

    CHECK(cd.read(test::kSynthDataLsn, 1, buf, ReadMode{0, 0, cd::kSecS2328}).code() == FormatError::Unsupported);
    CHECK(cd.read(test::kSynthDataLsn, 1, buf, ReadMode{0, 0, cd::kSecS2340}).code() == FormatError::Unsupported);
    CHECK(cd.read(test::kSynthDataLsn, 0, buf, ReadMode{}).code() == FormatError::Unsupported);
    CHECK(cd.read(test::kSynthSectors - 1, 2, buf, ReadMode{}).code() == FormatError::Overrun);
    CHECK(cd.read(0, 5, buf, ReadMode{}).code() == FormatError::Overrun);  // destination too small
    CHECK(cd.seek(test::kSynthSectors).code() == FormatError::Overrun);
    CHECK_FALSE(cd.busy());
    CHECK(cd.completions() == 0);

    // trycount / spindlctrl are recorded, not interpreted (ADX streams toggle spindlctrl).
    REQUIRE(cd.read(test::kSynthDataLsn, 1, buf, ReadMode{3, 1, cd::kSecS2048}).ok());
    CHECK(cd.last_read_mode().trycount == 3);
    CHECK(cd.last_read_mode().spindlctrl == 1);
    CHECK(cd.sync(SyncMode::Block) == 0);
}

TEST_CASE("CdvdHle: a host read failure completes with SCECdErREAD and keeps the cause") {
    FailingDisc disc;
    HookLog log;
    CdvdHle cd(disc, log.hooks());
    std::vector<std::byte> buf(kSectorSize);
    REQUIRE(cd.read(10, 1, buf, ReadMode{}).ok());
    CHECK(cd.sync(SyncMode::Poll) == 0);
    CHECK(cd.get_error() == cd::kErrRead);
    REQUIRE(cd.last_host_error().has_value());
    CHECK(cd.last_host_error()->code == FormatError::Truncated);
    REQUIRE(log.done.size() == 1);
    CHECK(log.done[0].error == cd::kErrRead);
    CHECK(log.calls.size() == 2);  // the semaphores are released on failure too
}

TEST_CASE("CdvdHle: S-command answers (L-06, I-04..I-08)") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    CdvdHle cd(*disc);
    CHECK(cd.init(0) == 1);
    CHECK(cd.get_disk_type() == 0x14);  // SCECdPS2DVD
    CHECK(cd.disk_ready(0) == 2);       // SCECdComplete
    CHECK(cd.disk_ready(1) == 2);
    CHECK(cd.media_mode() == 0);
    CHECK(cd.mmode(cd::kMmodeDvd) == 1);
    CHECK(cd.media_mode() == cd::kMmodeDvd);
    CHECK(cd.mmode(7) == 0);
    CHECK(cd.media_mode() == cd::kMmodeDvd);
    CHECK(cd.get_error() == cd::kErrNone);
    CHECK(cd.status() == cd::kStatPause);
    std::vector<std::byte> toc(2064);
    CHECK(cd.read_toc(toc).code() == FormatError::Unsupported);

    auto hit = cd.search_file("\\SUB\\INNER.TXT;1");
    REQUIRE(hit.ok());
    CHECK(hit->issue == Issue::Accepted);
    REQUIRE(hit->file.has_value());
    CHECK(hit->file->lsn == 21u);
    auto miss = cd.search_file("\\MISSING.BIN;1");
    REQUIRE(miss.ok());
    CHECK(miss->issue == Issue::Accepted);
    CHECK_FALSE(miss->file.has_value());
    CHECK(cd.search_file(std::string(256, 'A')).code() == FormatError::Unsupported);
}

TEST_CASE("CdvdHle: guest_read_buffer resolves sceCdRead's EE buffer through EEMemory") {
    test::TempFile iso(test::make_synthetic_iso());
    auto disc = test::open_synthetic(iso);
    EEMemory mem;
    CdvdHle cd(*disc);

    for (const u32 addr : {0x00100000u, 0x20100000u, 0x80100000u, 0xA0100000u}) {
        auto span = guest_read_buffer(mem, addr, 2);
        REQUIRE(span.ok());
        CHECK(span->size() == 2 * kSectorSize);
        CHECK(reinterpret_cast<u8*>(span->data()) == mem.main_ram() + 0x00100000u);
    }
    CHECK(guest_read_buffer(mem, EEMemory::kMainRamSize - kSectorSize, 2).code() == FormatError::Overrun);

    auto span = guest_read_buffer(mem, 0x00200040u, 3);
    REQUIRE(span.ok());
    REQUIRE(cd.read(test::kSynthDataLsn, 3, span.value(), ReadMode{}).ok());
    CHECK(cd.sync(SyncMode::Block) == 0);
    for (u32 i = 0; i < 3 * kSectorSize; i += 501)
        CHECK(mem.read<u8>(0x00200040u + i) ==
              static_cast<u8>(test::synth_data_byte(test::kSynthDataLsn + i / kSectorSize, i % kSectorSize)));
}

// ---- the user's disc ------------------------------------------------------------------------

namespace {

// Real sources available on this machine (ISO first).
std::vector<std::unique_ptr<DiscSource>> real_sources() {
    std::vector<std::unique_ptr<DiscSource>> out;
    if (auto iso = test::open_real_iso()) out.push_back(std::move(iso));
    if (auto ext = test::open_real_extracted()) out.push_back(std::move(ext));
    return out;
}

const char* kind_name(const DiscSource& d) {
    return d.identity().kind == DiscSourceKind::IsoImage ? "IsoFileSource" : "ExtractedVolumesSource";
}

}  // namespace

TEST_CASE("CdvdHle: search_file answers the three boot-time CVM searches (I-07)") {
    auto sources = real_sources();
    if (sources.empty()) {
        MESSAGE("skipped: neither input/persona3fes.iso nor extracted/disc present");
        return;
    }
    for (auto& disc : sources) {
        CAPTURE(kind_name(*disc));
        CdvdHle cd(*disc);
        struct Want { const char* path; u32 lsn; u32 size; };
        for (const Want& w : {Want{"\\DATA.CVM;1", 584'363u, 3'367'428'096u}, Want{"\\BGM.CVM;1", 457'947u, 258'899'968u},
                              Want{"\\BTL.CVM;1", 633u, 936'579'072u}}) {
            CAPTURE(w.path);
            auto r = cd.search_file(w.path);
            REQUIRE_MESSAGE(r.ok(), formats::error_name(r.code()) << ": " << r.detail());
            CHECK(r->issue == Issue::Accepted);
            REQUIRE(r->file.has_value());
            CHECK(r->file->lsn == w.lsn);
            CHECK(r->file->size == w.size);
            CHECK(r->file->sectors() == w.size / kSectorSize);
        }
    }
}

TEST_CASE("CdvdHle: 20 manifest files read at LSN(container)+3+lba equal the extracted files") {
    auto sources = real_sources();
    if (sources.empty()) {
        MESSAGE("skipped: neither input/persona3fes.iso nor extracted/disc present");
        return;
    }
    auto manifest = test::load_manifest();
    if (!manifest) {
        MESSAGE("skipped: extracted/manifest.json not present or unreadable");
        return;
    }

    // Deterministic pick: 8 DATA, 7 BTL, 5 BGM files spread across each container's entries,
    // non-empty and <= 8 MiB so the suite stays fast.
    std::vector<test::ManifestEntry> picked;
    for (const auto& [container, want] : {std::pair{"DATA.CVM", 8}, std::pair{"BTL.CVM", 7}, std::pair{"BGM.CVM", 5}}) {
        std::vector<const test::ManifestEntry*> pool;
        for (const auto& e : *manifest)
            if (e.container == container && e.size > 0 && e.size <= 8u * 1024u * 1024u) pool.push_back(&e);
        REQUIRE(pool.size() >= static_cast<std::size_t>(want));
        for (int i = 0; i < want; ++i) picked.push_back(*pool[(pool.size() * static_cast<std::size_t>(2 * i + 1)) / (2 * want)]);
    }
    REQUIRE(picked.size() == 20);

    for (auto& disc : sources) {
        CAPTURE(kind_name(*disc));
        CdvdHle cd(*disc);
        for (const test::ManifestEntry& e : picked) {
            CAPTURE(e.path);
            const DiscLayoutEntry* cvm = find_disc_layout(e.container);
            REQUIRE(cvm != nullptr);
            auto want = test::read_host_file(test::extracted_dir() / e.path);
            REQUIRE(want.has_value());
            REQUIRE(want->size() == e.size);

            // Whole-file load as the game does it: a 64-byte-aligned buffer of size_sct*2048,
            // filled by a sequence of one-at-a-time sceCdRead + sceCdSync(1) polls.
            const u32 size_sct = static_cast<u32>((e.size + kSectorSize - 1) / kSectorSize);
            std::vector<std::byte> raw(static_cast<std::size_t>(size_sct) * kSectorSize + 64);
            const std::size_t pad = (64 - reinterpret_cast<std::uintptr_t>(raw.data()) % 64) % 64;
            std::span<std::byte> dst{raw.data() + pad, static_cast<std::size_t>(size_sct) * kSectorSize};
            const u32 first_lsn = cvm_file_lsn(*cvm, e.lba);
            constexpr u32 kChunk = 32;
            for (u32 done = 0; done < size_sct;) {
                const u32 n = std::min(kChunk, size_sct - done);
                auto issued = cd.read(first_lsn + done, n, dst.subspan(static_cast<std::size_t>(done) * kSectorSize), ReadMode{});
                REQUIRE_MESSAGE(issued.ok(), formats::error_name(issued.code()) << ": " << issued.detail());
                REQUIRE(issued.value() == Issue::Accepted);
                while (cd.sync(SyncMode::Poll) != 0) {
                }
                REQUIRE(cd.get_error() == cd::kErrNone);
                done += n;
            }
            CHECK(std::memcmp(dst.data(), want->data(), want->size()) == 0);
        }
    }
}
