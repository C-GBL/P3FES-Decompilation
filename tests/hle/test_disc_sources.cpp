// DiscSource tests: SYSTEM.CNF identity, synthetic-image acceptance/refusal, the kDiscLayout table,
// and byte-for-byte agreement of IsoFileSource and ExtractedVolumesSource on the user's disc.
#include <doctest.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <random>
#include <vector>

#include "hle_fixtures.h"
#include "p3fes/hle/disc_source.h"

using namespace p3fes;
using namespace p3fes::hle;

namespace {

std::span<const std::byte> text_bytes(std::string_view s) { return {reinterpret_cast<const std::byte*>(s.data()), s.size()}; }

}  // namespace

TEST_CASE("SYSTEM.CNF: parse the retail form, tolerate whitespace, reject other discs and non-text") {
    auto retail = parse_system_cnf(text_bytes("BOOT2=cdrom0:\\SLUS_216.21;1\r\nVER=1.00\r\nVMODE=NTSC\r\n"));
    REQUIRE(retail.ok());
    CHECK(retail->boot2 == kExpectedBoot2);
    CHECK(retail->version == "1.00");
    CHECK(retail->video_mode == "NTSC");
    CHECK(verify_system_cnf(retail.value()).ok());

    auto spaced = parse_system_cnf(text_bytes("BOOT2 = cdrom0:\\SLUS_216.21;1\n\nVER = 1.00\n"));
    REQUIRE(spaced.ok());
    CHECK(spaced->boot2 == kExpectedBoot2);
    CHECK(spaced->video_mode.empty());

    auto other = parse_system_cnf(text_bytes("BOOT2 = cdrom0:\\SLUS_999.99;1\r\n"));
    REQUIRE(other.ok());
    auto refused = verify_system_cnf(other.value());
    CHECK(refused.code() == FormatError::BadMagic);

    CHECK(parse_system_cnf(text_bytes("VER = 1.00\r\n")).code() == FormatError::BadMagic);  // PS1 / non-game
    CHECK(parse_system_cnf(text_bytes("BOOT2 cdrom0:\\X;1\r\n")).code() == FormatError::BadHeader);
    const std::array<std::byte, 4> binary{std::byte{0x7F}, std::byte{'E'}, std::byte{0xFF}, std::byte{1}};
    CHECK(parse_system_cnf(binary).code() == FormatError::BadHeader);
}

TEST_CASE("kDiscLayout: LSN math of DISC_LAYOUT §7 and RUNTIME_CONTRACT L-01") {
    const DiscLayoutEntry* btl = find_disc_layout("BTL.CVM");
    const DiscLayoutEntry* bgm = find_disc_layout("BGM.CVM");
    const DiscLayoutEntry* data = find_disc_layout("DATA.CVM");
    REQUIRE(btl);
    REQUIRE(bgm);
    REQUIRE(data);
    CHECK(find_disc_layout("NOPE.CVM") == nullptr);
    // L-01 extents (sector counts = file size / 2048 incl. the 3 header sectors).
    CHECK(btl->lsn == 633u);
    CHECK(btl->sectors() == 457'314u);
    CHECK(bgm->lsn == 457'947u);
    CHECK(bgm->sectors() == 126'416u);
    CHECK(data->lsn == 584'363u);
    CHECK(data->sectors() == 1'644'252u);
    // Derived: the volumes are packed back to back on the disc.
    CHECK(btl->end_lsn() == bgm->lsn);
    CHECK(bgm->end_lsn() == data->lsn);
    CHECK(data->end_lsn() == find_disc_layout("SLUS_216.21")->lsn);
    // disc LSN = LSN(CVM) + 3 + iso_lba; the CVM PVD (iso LBA 16) is CVM-file sector 19.
    CHECK(cvm_file_lsn(*data, 0) == 584'366u);
    CHECK(cvm_file_lsn(*data, 16) == data->lsn + 19u);
    CHECK(kCvmHeaderSectors * kSectorSize == 0x1800u);  // DISC_LAYOUT §1 header size
}

TEST_CASE("IsoFileSource: accepts a synthetic image whose SYSTEM.CNF names SLUS_216.21") {
    test::TempFile iso(test::make_synthetic_iso());
    auto src = test::open_synthetic(iso);
    CHECK(src->sector_count() == test::kSynthSectors);
    CHECK(src->identity().kind == DiscSourceKind::IsoImage);
    CHECK(src->identity().system_cnf.boot2 == kExpectedBoot2);
    CHECK(src->identity().system_cnf.version == "1.00");
    CHECK(src->identity().origin == iso.path());

    // Directory search: libcdvd form, nested, case-insensitive, version optional, absent.
    auto data = src->find_file("\\DATA.BIN;1");
    REQUIRE(data.ok());
    REQUIRE(data->has_value());
    CHECK(data.value()->lsn == test::kSynthDataLsn);
    CHECK(data.value()->size == test::kSynthDataSize);
    CHECK(data.value()->identifier == "DATA.BIN;1");
    auto inner = src->find_file("/sub/inner.txt");
    REQUIRE(inner.ok());
    REQUIRE(inner->has_value());
    CHECK(inner.value()->lsn == 21u);
    CHECK(inner.value()->size == 5u);
    auto absent = src->find_file("\\NOPE.BIN;1");
    REQUIRE(absent.ok());
    CHECK_FALSE(absent->has_value());
    auto through_file = src->find_file("\\DATA.BIN\\X");
    REQUIRE(through_file.ok());
    CHECK_FALSE(through_file->has_value());
    CHECK(src->find_file("\\").code() == FormatError::Unsupported);

    // Sector reads and their bounds.
    std::vector<std::byte> buf(3 * kSectorSize);
    auto rd = src->read_sectors(test::kSynthDataLsn, 3, buf);
    REQUIRE(rd.ok());
    CHECK(rd.value() == 3 * kSectorSize);
    for (u32 i = 0; i < 3 * kSectorSize; i += 997)
        CHECK(buf[i] == test::synth_data_byte(test::kSynthDataLsn + i / kSectorSize, i % kSectorSize));
    CHECK(src->read_sectors(test::kSynthSectors - 1, 2, buf).code() == FormatError::Overrun);
    CHECK(src->read_sectors(0xFFFFFFFFu, 1, buf).code() == FormatError::Overrun);
    CHECK(src->read_sectors(0, 4, buf).code() == FormatError::Overrun);  // destination too small
}

TEST_CASE("IsoFileSource: refuses a synthetic 1 MiB ISO with a different SYSTEM.CNF and other non-matching images") {
    SUBCASE("different game") {
        test::SynthOptions o;
        o.system_cnf = "BOOT2 = cdrom0:\\SLUS_999.99;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n";
        const std::vector<std::byte> bytes = test::make_synthetic_iso(o);
        CHECK(bytes.size() == 1024u * 1024u);
        test::TempFile iso(bytes);
        auto r = IsoFileSource::open(iso.path());
        CHECK(r.code() == FormatError::BadMagic);
        CHECK(std::string_view(r.detail()).find("SLUS_216.21") != std::string_view::npos);
    }
    SUBCASE("no SYSTEM.CNF") {
        test::SynthOptions o;
        o.with_system_cnf = false;
        test::TempFile iso(test::make_synthetic_iso(o));
        CHECK(IsoFileSource::open(iso.path()).code() == FormatError::BadMagic);
    }
    SUBCASE("no ISO9660 volume descriptor") {
        test::SynthOptions o;
        o.with_pvd = false;
        test::TempFile iso(test::make_synthetic_iso(o));
        CHECK(IsoFileSource::open(iso.path()).code() == FormatError::BadMagic);
    }
    SUBCASE("not 2048-byte sectors (raw BIN size)") {
        test::SynthOptions o;
        o.extra_bytes = 304;
        test::TempFile iso(test::make_synthetic_iso(o));
        CHECK(IsoFileSource::open(iso.path()).code() == FormatError::BadHeader);
    }
    SUBCASE("missing file") {
        CHECK(IsoFileSource::open(std::filesystem::temp_directory_path() / "p3fes_hle_does_not_exist.iso").code() ==
              FormatError::Truncated);
    }
}

TEST_CASE("open_user_disc: a file opens as an ISO, a directory as extracted volumes") {
    test::TempFile iso(test::make_synthetic_iso());
    auto src = open_user_disc(iso.path());
    REQUIRE(src.ok());
    CHECK(src.value()->identity().kind == DiscSourceKind::IsoImage);

    // A directory without the five kDiscLayout files is refused as incomplete.
    const std::filesystem::path empty_dir = std::filesystem::temp_directory_path() / "p3fes_hle_empty_disc_dir";
    std::filesystem::create_directories(empty_dir);
    CHECK(open_user_disc(empty_dir).code() == FormatError::Truncated);
    std::error_code ec;
    std::filesystem::remove_all(empty_dir, ec);

    CHECK(open_user_disc(std::filesystem::temp_directory_path() / "p3fes_hle_nothing_here").code() ==
          FormatError::Truncated);
}

TEST_CASE("ExtractedVolumesSource: identity, catalogue lookups, zero gaps (extracted/disc)") {
    auto src = test::open_real_extracted();
    P3FES_SKIP_UNLESS(src, "extracted/disc");
    CHECK(src->identity().kind == DiscSourceKind::ExtractedVolumes);
    CHECK(src->identity().system_cnf.boot2 == kExpectedBoot2);
    CHECK(src->sector_count() == kDiscSectors);

    for (const DiscLayoutEntry& e : kDiscLayout) {
        auto f = src->find_file("\\" + std::string(e.identifier));
        REQUIRE(f.ok());
        REQUIRE(f->has_value());
        CHECK(f.value()->lsn == e.lsn);
        CHECK(f.value()->size == e.size);
        CHECK(f.value()->recorded == e.recorded);  // the ISO recording date travels with the catalogue entry
    }
    auto no_version = src->find_file("\\data.cvm");
    REQUIRE(no_version.ok());
    REQUIRE(no_version->has_value());
    CHECK(no_version.value()->lsn == 584'363u);
    auto absent = src->find_file("\\NOPE.CVM;1");
    REQUIRE(absent.ok());
    CHECK_FALSE(absent->has_value());
    // LIB31 exists on the disc but is outside this source's catalogue: unknown, not absent.
    CHECK(src->find_file("\\LIB31\\PADMAN.IRX;1").code() == FormatError::Unsupported);
    CHECK(src->find_file("\\LIB31").code() == FormatError::Unsupported);

    std::vector<std::byte> buf(2 * kSectorSize, std::byte{0xEE});
    REQUIRE(src->read_sectors(16, 1, buf).ok());  // the outer PVD is not served: zeros
    CHECK(std::all_of(buf.begin(), buf.begin() + kSectorSize, [](std::byte b) { return b == std::byte{0}; }));
    REQUIRE(src->read_sectors(kDiscSectors - 1, 1, buf).ok());
    CHECK(std::all_of(buf.begin(), buf.begin() + kSectorSize, [](std::byte b) { return b == std::byte{0}; }));
    CHECK(src->read_sectors(kDiscSectors - 1, 2, buf).code() == FormatError::Overrun);

    // SYSTEM.CNF sector: 51 bytes of text, then zeros.
    REQUIRE(src->read_sectors(2'233'057u, 1, buf).ok());
    CHECK(std::memcmp(buf.data(), "BOOT2=cdrom0:\\SLUS_216.21;1", 27) == 0);
    CHECK(std::all_of(buf.begin() + 51, buf.begin() + kSectorSize, [](std::byte b) { return b == std::byte{0}; }));

    // The CVM PVD sits at LSN(CVM) + 3 + 16 (DISC_LAYOUT §1).
    REQUIRE(src->read_sectors(cvm_file_lsn(*find_disc_layout("DATA.CVM"), 16), 1, buf).ok());
    CHECK(std::memcmp(buf.data(), "\x01" "CD001", 6) == 0);
}

TEST_CASE("IsoFileSource: the user's ISO opens and kDiscLayout matches its root directory") {
    auto iso = test::open_real_iso();
    P3FES_SKIP_UNLESS(iso, "input/persona3fes.iso");
    CHECK(iso->sector_count() == kDiscSectors);
    CHECK(iso->identity().system_cnf.boot2 == kExpectedBoot2);
    CHECK(iso->identity().system_cnf.video_mode == "NTSC");
    auto checked = verify_disc_layout(*iso);
    REQUIRE_MESSAGE(checked.ok(), formats::error_name(checked.code()) << ": " << checked.detail());
    CHECK(checked.value() == kDiscLayout.size());
    auto lib = iso->find_file("\\LIB31\\PADMAN.IRX;1");  // only the ISO source can answer this
    REQUIRE(lib.ok());
    CHECK(lib->has_value());
    // DiscFile::recorded is the directory record's date (verify_disc_layout also compares kDiscLayout's).
    auto btl = iso->find_file("\\BTL.CVM;1");
    REQUIRE(btl.ok());
    REQUIRE(btl->has_value());
    CHECK(btl.value()->recorded == std::array<u8, 7>{108, 1, 4, 14, 59, 58, 36});  // 2008-01-04 14:59:58 GMT+9
}

TEST_CASE("Both sources agree byte-for-byte: 50 random LSNs per container, SLUS_216.21, boundary spans") {
    auto iso = test::open_real_iso();
    P3FES_SKIP_UNLESS(iso, "input/persona3fes.iso");
    auto ext = test::open_real_extracted();
    P3FES_SKIP_UNLESS(ext, "extracted/disc");

    std::vector<std::byte> a(8 * kSectorSize), b(8 * kSectorSize);
    std::size_t compared = 0, mismatched = 0;
    auto compare = [&](u32 lsn, u32 n) {
        std::fill(a.begin(), a.end(), std::byte{0xAA});
        std::fill(b.begin(), b.end(), std::byte{0x55});
        auto ra = iso->read_sectors(lsn, n, a);
        auto rb = ext->read_sectors(lsn, n, b);
        REQUIRE(ra.ok());
        REQUIRE(rb.ok());
        compared += n;
        if (std::memcmp(a.data(), b.data(), static_cast<std::size_t>(n) * kSectorSize) != 0) {
            ++mismatched;
            FAIL_CHECK("sources differ at LSN " << lsn << " (+" << n << ")");
        }
    };

    std::mt19937 rng(0x50335346u);  // fixed seed: reproducible LSN sample
    for (const char* name : {"BTL.CVM", "BGM.CVM", "DATA.CVM"}) {
        const DiscLayoutEntry& e = *find_disc_layout(name);
        std::uniform_int_distribution<u32> pick(e.lsn, e.end_lsn() - 1);
        for (int i = 0; i < 50; ++i) compare(pick(rng), 1);
        compare(e.lsn, 1);                    // CVMH header sector
        compare(cvm_file_lsn(e, 16), 1);      // CVM PVD
        compare(e.end_lsn() - 1, 1);          // last sector
    }
    const DiscLayoutEntry& slus = *find_disc_layout("SLUS_216.21");
    compare(slus.lsn, 1);                     // ELF header sector
    compare(slus.end_lsn() - 1, 1);           // partial last sector (tail zero on both)
    compare(find_disc_layout("SYSTEM.CNF")->lsn, 1);
    // Multi-sector reads across the back-to-back extents.
    compare(find_disc_layout("BGM.CVM")->lsn - 4, 8);
    compare(find_disc_layout("DATA.CVM")->lsn - 4, 8);
    compare(slus.lsn - 4, 8);
    CHECK(compared == 3 * 53 + 3 + 24);
    CHECK(mismatched == 0);
}
