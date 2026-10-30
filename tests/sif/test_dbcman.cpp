// Memory card behind DBCMAN (runtime/hle/memcard/, runtime/hle/sif/iop/srv_dbcman.cpp + mc_mc2s1.*):
// ECC vectors and round trips, NAND program/erase rules, the file system of an in-test formatted card,
// card sources (copy-on-write never touches the source), and the DBC protocol as libdbc/libmc2 drive it --
// request/reply bytes of every DBC function and MC2 command the game issues, the async send_data3
// completion through SIF0 at a later check point, the work-area DMA. No user data: cards are made here.
#include <doctest.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "p3fes/hle/memcard/card.h"
#include "p3fes/hle/memcard/ecc.h"
#include "p3fes/hle/memcard/fs.h"
#include "p3fes/hle/memcard/iop_slot.h"
#include "p3fes/hle/memcard/source.h"
#include "sif_harness.h"

using namespace p3fes;
using namespace p3fes::test;
namespace mc = p3fes::hle::memcard;
namespace fs = std::filesystem;

namespace {

std::array<u8, 128> chunk_of(u8 fill) {
    std::array<u8, 128> c;
    c.fill(fill);
    return c;
}

fs::path temp_dir(const char* tag) {
    static std::atomic<int> n{0};
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    fs::path p = fs::temp_directory_path() / ("p3fes_mc_" + std::string(tag) + "_" + std::to_string(stamp) + "_" + std::to_string(n++));
    fs::create_directories(p);
    return p;
}

std::vector<u8> file_bytes(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    return std::vector<u8>(std::istreambuf_iterator<char>(f), {});
}

void write_file(const fs::path& p, std::span<const u8> b) {
    std::ofstream f(p, std::ios::binary | std::ios::trunc);
    f.write(reinterpret_cast<const char*>(b.data()), static_cast<std::streamsize>(b.size()));
}

}  // namespace

// ---- ECC ---------------------------------------------------------------------------------------------

TEST_CASE("memcard ECC: hand-derived vectors") {
    // Erased (and all-zero) data: every byte has even parity and an even count in each column group, so
    // every parity is 0 and the stored (inverted) code is 0x77 0x7F 0x7F.
    CHECK(mc::ecc_chunk(chunk_of(0xFF)) == std::array<u8, 3>{0x77, 0x7F, 0x7F});
    CHECK(mc::ecc_chunk(chunk_of(0x00)) == std::array<u8, 3>{0x77, 0x7F, 0x7F});
    // One byte 0x01 at index 0: odd parity -> line parity 0 ^= ~0, line 1 ^= 0; column groups 0x55, 0x33,
    // 0x0F contain bit 0 -> column parity 0x07. Inverted and masked: 0x70 0x00 0x7F.
    auto c = chunk_of(0);
    c[0] = 0x01;
    CHECK(mc::ecc_chunk(c) == std::array<u8, 3>{0x70, 0x00, 0x7F});
    // 0x80 at index 127: groups 0xAA 0xCC 0xF0 -> 0x70 -> 0x07; line 0 ^= ~127 & 0x7F = 0 -> 0x7F; line 1 ^= 127 -> 0x00.
    c = chunk_of(0);
    c[127] = 0x80;
    CHECK(mc::ecc_chunk(c) == std::array<u8, 3>{0x07, 0x7F, 0x00});
    // A page: four chunks, 12 bytes.
    std::vector<u8> page(512, 0xFF), out(12, 0);
    CHECK(mc::ecc_compute(page, out) == 12);
    for (int i = 0; i < 4; ++i) CHECK(out[3 * i] == 0x77);
    std::vector<u8> bad(100);
    CHECK(mc::ecc_compute(bad, out) == 0);
}

TEST_CASE("memcard ECC: every single-bit data error is corrected, code errors detected, double errors refused") {
    std::mt19937 rng(1234);
    std::array<u8, 128> data;
    for (auto& b : data) b = static_cast<u8>(rng());
    const auto code = mc::ecc_chunk(data);
    auto ok = data;
    CHECK(mc::ecc_check_chunk(ok, code) == mc::EccCheck::Ok);
    int corrected = 0;
    for (u32 byte = 0; byte < 128; ++byte)
        for (u32 bit = 0; bit < 8; ++bit) {
            auto d = data;
            d[byte] = static_cast<u8>(d[byte] ^ (1u << bit));
            if (mc::ecc_check_chunk(d, code) == mc::EccCheck::CorrectedData && d == data) ++corrected;
        }
    CHECK(corrected == 1024);
    for (u32 i = 0; i < 3; ++i)
        for (u32 bit = 0; bit < 7; ++bit) {
            if (i == 0 && bit == 3) continue;  // not a code bit (mask 0x77)
            auto c = code;
            c[i] = static_cast<u8>(c[i] ^ (1u << bit));
            auto d = data;
            CHECK(mc::ecc_check_chunk(d, c) == mc::EccCheck::CorrectedCode);
            CHECK(d == data);
        }
    auto d2 = data;
    d2[3] ^= 0x01;
    d2[90] ^= 0x10;
    CHECK(mc::ecc_check_chunk(d2, code) == mc::EccCheck::Uncorrectable);
    // Round trip over random pages.
    for (int t = 0; t < 32; ++t) {
        std::vector<u8> pg(512), e(12);
        for (auto& b : pg) b = static_cast<u8>(rng());
        mc::ecc_compute(pg, e);
        CHECK(mc::ecc_check(pg, e) == mc::EccCheck::Ok);
    }
}

// ---- NAND rules ---------------------------------------------------------------------------------------

TEST_CASE("memcard Card: erased 0xFF, program only clears bits, erase restores one block") {
    auto card = mc::Card::blank("t");
    REQUIRE(card->image().size() == 8'650'752);
    std::array<u8, 528> raw{};
    CHECK(card->read(5, raw));
    for (u8 b : raw) CHECK(b == 0xFF);
    const std::array<u8, 4> a{0xF0, 0x0F, 0x55, 0xFF};
    CHECK(card->program(5, a));
    CHECK(card->stats().program_conflicts == 0);
    const std::array<u8, 4> b{0x0F, 0xFF, 0xAA, 0x00};
    CHECK(card->program(5, b));  // asks 0 -> 1 in places: NAND keeps the 0
    CHECK(card->stats().program_conflicts == 1);
    std::array<u8, 4> r{};
    card->read(5, r);
    CHECK(r == std::array<u8, 4>{0x00, 0x0F, 0x00, 0x00});
    CHECK(card->raw_page(5)[4] == 0xFF);  // beyond the programmed bytes: untouched
    card->program(16, a);                 // next block
    CHECK(card->erase_block(7));          // block 0 (pages 0..15)
    for (u32 pg = 0; pg < 16; ++pg)
        for (u8 v : card->raw_page(pg)) CHECK(v == 0xFF);
    CHECK(card->raw_page(16)[0] == 0xF0);  // block 1 untouched
    CHECK_FALSE(card->read(16384, raw));
    std::vector<u8> big(529, 0);
    CHECK_FALSE(card->program(0, big));
    CHECK_FALSE(card->erase_block(16384));
    CHECK(card->stats().rejected == 3);
    CHECK(mc::Card::from_image(std::vector<u8>(100), "x") == nullptr);
}

// ---- file system ----------------------------------------------------------------------------------------

TEST_CASE("memcard FS: an in-test formatted card parses as the standard 8 MiB layout") {
    auto card = mc::Card::blank("fmt");
    std::string why;
    CHECK_FALSE(mc::parse_superblock(card->raw_page(0).first(512), &why));
    CHECK(why.find("unformatted") != std::string::npos);
    mc::DateTime t{1, 2, 3, 4, 5, 2026};
    mc::format(*card, t);
    mc::FsView v(*card);
    REQUIRE(v.ok());
    const auto& sb = v.superblock();
    CHECK(std::string(reinterpret_cast<const char*>(card->raw_page(0).data()), 35) == "Sony PS2 Memory Card Format 1.2.0.0");
    CHECK(sb.magic == "Sony PS2 Memory Card Format ");
    CHECK(sb.version == "1.2.0.0");
    CHECK(sb.page_len == 512);
    CHECK(sb.pages_per_cluster == 2);
    CHECK(sb.pages_per_block == 16);
    CHECK(sb.unused == 0xFF00);
    CHECK(sb.clusters_per_card == 8192);
    CHECK(sb.alloc_offset == 41);
    CHECK(sb.alloc_end == 8135);
    CHECK(sb.rootdir_cluster == 0);
    CHECK(sb.backup_block1 == 1023);
    CHECK(sb.backup_block2 == 1022);
    CHECK(sb.ifc_list[0] == 8);
    CHECK(sb.ifc_list[1] == 0);
    CHECK(sb.bad_block_list[0] == -1);
    CHECK(sb.card_type == 2);
    CHECK(sb.card_flags == 0x2B);
    // The checks _sceMcFatGetInfo 0x515D80 makes: 27-byte magic, version digits '1' and '2' >= 11.
    CHECK(card->raw_page(0)[28] == '1');
    CHECK(card->raw_page(0)[30] == '2');
    // Root directory.
    const auto root = v.root();
    REQUIRE(root.size() == 2);
    CHECK(root[0].name == ".");
    CHECK(root[0].mode == 0x8427);
    CHECK(root[0].length == 2);
    CHECK(root[0].created.year == 2026);
    CHECK(root[0].created.min == 2);
    CHECK(root[1].name == "..");
    CHECK(root[1].mode == 0xA426);
    // FAT through the indirect FAT cluster.
    CHECK(v.fat(0) == mc::kFatEnd);
    CHECK(v.fat(1) == mc::kFatFree);
    CHECK(v.fat(8134) == mc::kFatFree);
    CHECK(v.fat(8135) == 0xFFFFFFFFu);
    CHECK(v.chain(0) == std::vector<u32>{0});
    CHECK(v.free_clusters() == 8134);
    CHECK(v.ecc_errors() == 0);
    // Spare areas: 12 ECC bytes programmed, the last 4 still erased; unwritten pages erased.
    CHECK(card->raw_page(0)[512 + 12] == 0xFF);
    CHECK(card->raw_page(1)[0] == 0xFF);
    CHECK(card->raw_page(1022 * 16)[0] == 0xFF);  // backup block 2 erased (no pending write-back)
    std::array<u8, 12> e{};
    std::vector<u8> p0(card->raw_page(0).begin(), card->raw_page(0).begin() + 512);
    mc::ecc_compute(p0, e);
    CHECK(std::memcmp(e.data(), card->raw_page(0).data() + 512, 12) == 0);
}

// ---- sources / copy-on-write --------------------------------------------------------------------------

TEST_CASE("memcard sources: copy-on-write never touches the source; none/new/blank; PCSX2.ini lookup") {
    const fs::path dir = temp_dir("cow");
    const fs::path src = dir / "user" / "Mcd001.ps2";
    fs::create_directories(src.parent_path());
    std::vector<u8> img(mc::kImageSize, 0xFF);
    img[1000] = 0x12;  // something to recognise
    write_file(src, img);
    const auto before = fs::last_write_time(src);
    mc::SourceOptions opt;
    opt.cow_dir = dir / "ours";

    auto r = mc::open_memcard(src.string(), opt);
    REQUIRE(r.ok);
    REQUIRE(r.card);
    CHECK(r.card->image()[1000] == 0x12);
    CHECK(r.description.find("read-only") != std::string::npos);
    CHECK(r.card->erase_block(0));
    const std::array<u8, 2> w{0x00, 0x00};
    CHECK(r.card->program(40, w));
    std::string err;
    CHECK(r.card->flush(&err));
    CHECK(fs::exists(opt.cow_dir / "Mcd001.ps2"));
    // A second change goes to the copy as single pages.
    CHECK(r.card->program(41, w));
    CHECK(r.card->flush(&err));
    CHECK(file_bytes(src) == img);  // the user's card is byte-identical
    CHECK(fs::last_write_time(src) == before);
    const auto copy = file_bytes(opt.cow_dir / "Mcd001.ps2");
    REQUIRE(copy.size() == mc::kImageSize);
    CHECK(copy[1000] == 0xFF);       // erased by our run
    CHECK(copy[40 * 528] == 0x00);   // programmed
    CHECK(copy[41 * 528] == 0x00);
    CHECK(std::equal(copy.begin(), copy.end(), r.card->image().begin()));
    // Re-opening the same source continues on our copy.
    auto again = mc::open_memcard(src.string(), opt);
    REQUIRE(again.ok);
    CHECK(again.card->image()[41 * 528] == 0x00);
    CHECK(again.description.find("earlier run") != std::string::npos);
    // A path inside the copy-on-write directory is ours: written in place.
    auto ours = mc::open_memcard((opt.cow_dir / "Mcd001.ps2").string(), opt);
    REQUIRE(ours.ok);
    CHECK(ours.description.find("in place") != std::string::npos);

    auto none = mc::open_memcard("none", opt);
    CHECK(none.ok);
    CHECK(none.card == nullptr);
    auto fresh = mc::open_memcard("new", opt);
    REQUIRE(fresh.card);
    CHECK(mc::FsView(*fresh.card).ok());
    auto blank = mc::open_memcard("blank", opt);
    REQUIRE(blank.card);
    CHECK_FALSE(mc::FsView(*blank.card).ok());
    const fs::path small = dir / "small.ps2";
    write_file(small, std::vector<u8>(8 * 1024 * 1024, 0xFF));  // no-ECC size: refused
    CHECK_FALSE(mc::open_memcard(small.string(), opt).ok);

    // PCSX2.ini: relative MemoryCards folder against the PCSX2 directory (the parent of inis/).
    fs::create_directories(dir / "pcsx2" / "inis");
    fs::create_directories(dir / "pcsx2" / "cards");
    write_file(dir / "pcsx2" / "cards" / "Slot1.ps2", img);
    {
        std::ofstream ini(dir / "pcsx2" / "inis" / "PCSX2.ini");
        ini << "[Folders]\nMemoryCards = cards\n\n[MemoryCards]\nSlot1_Enable = true\nSlot1_Filename = Slot1.ps2\n";
    }
    std::string why;
    const auto found = mc::pcsx2_slot1_card(dir / "pcsx2" / "inis" / "PCSX2.ini", &why);
    REQUIRE(found);
    CHECK(fs::equivalent(*found, dir / "pcsx2" / "cards" / "Slot1.ps2"));
    opt.pcsx2_ini = dir / "pcsx2" / "inis" / "PCSX2.ini";
    auto via_ini = mc::open_memcard("", opt);
    REQUIRE(via_ini.ok);
    CHECK(via_ini.card->image()[1000] == 0x12);
    {
        std::ofstream ini(dir / "pcsx2" / "inis" / "PCSX2.ini");
        ini << "[MemoryCards]\nSlot1_Enable = false\n";
    }
    CHECK_FALSE(mc::pcsx2_slot1_card(dir / "pcsx2" / "inis" / "PCSX2.ini", &why));
    std::error_code ec;
    fs::remove_all(dir, ec);
}

// ---- DBC protocol ------------------------------------------------------------------------------------------

namespace {

// The game's EE addresses (obs, libdbc/libmc2): request/response buffers and the DBC work area.
constexpr u32 kWork = 0x00996F40;     // sceDbcInit 0x51C604 -> sceDbcSetWorkAddr
constexpr u32 kSend3 = 0x00996900;    // sceDbcSendData3 buffer (1168 bytes)
constexpr u32 kBuf0 = 0x009855C0;     // _sceMcCoreCreateSocket 0x51C1C4: socket EE buffers
constexpr u32 kBuf1 = 0x00985640;
constexpr u32 kMc2Callback = 0x0051AE38;  // sceMc2SifCallback
constexpr u32 kPageSrc = 0x00984D00;      // a 64-byte aligned EE page source

struct Dbc {
    EeSide& e;
    u32 base = 0, send3 = 0, send2 = 0;
    int ends = 0;
    explicit Dbc(EeSide& ee) : e(ee) {
        e.init_rpc();
        base = e.bind(0x80001300u);
        send3 = e.bind(0x8000131Cu);
        send2 = e.bind(0x8000131Eu);
        e.on_end = [this](u32) { ++ends; };
    }
    std::vector<u8> call(u32 fno, std::initializer_list<u32> w, std::string_view name = {}) {
        std::vector<u8> b(144, 0);
        std::size_t i = 0;
        for (u32 x : w) {
            store32(b, i, x);
            i += 4;
        }
        if (!name.empty()) std::memcpy(b.data() + 20, name.data(), name.size());
        return e.call_sync(base, fno, b, 144);
    }
    // sceDbcInit's tail + _sceMcCoreCreateSocket: SetWorkAddr, CreateSocket({3, 2, 2, 0, 0, "MC2SOCKET"}).
    s32 open_socket() {
        for (u32 i = 0; i < 128; i += 4) e.w32(kWork + i, 0);
        CHECK(load32(call(0x80001304u, {0, kWork}), 0) == 1);
        std::vector<u8> b(144, 0);
        store32(b, 0, 3);
        store32(b, 4, 2);
        store32(b, 8, 2);
        std::memcpy(b.data() + 20, "MC2SOCKET", 10);
        store32(b, 40, kBuf0);
        store32(b, 44, kBuf1);
        return static_cast<s32>(load32(e.call_sync(base, 0x80001301u, b, 144), 36));
    }
    // One libmc2 command: memset 0x9855C0..+256, the 1168-byte send, completion at a later check point.
    s32 mc2(u32 socket, u32 cmd, std::array<u32, 12> req) {
        for (u32 i = 0; i < 256; i += 4) e.w32(kBuf0 + i, 0);
        std::vector<u8> b(1168, 0);
        store32(b, 0, socket);
        store32(b, 4, cmd);
        store32(b, 8, 48);
        for (std::size_t i = 0; i < req.size(); ++i) store32(b, 12 + 4 * i, req[i]);
        e.write(kSend3, b);
        const int before = ends;
        REQUIRE(e.call(send3, 0x8000131Cu, 1, kSend3, 1168, kSend3, 1168, kMc2Callback, 0));
        e.pump();
        CHECK(ends == before);  // not inside the issuing syscall
        e.bus.advance(1);
        e.sif.service();
        e.pump();
        CHECK(ends == before + 1);  // sceMc2SifCallback ran once (-> iSignalSema)
        CHECK(e.r32(kSend3 + 8) == 48);
        return static_cast<s32>(e.r32(kSend3 + 1164));
    }
};

std::array<u32, 12> req(u32 page, u32 count, u32 ecc, u32 b1 = 0, u32 b2 = 0, u32 ee = 0) {
    return {page, count, 512, 16, 16384, b1, b2, 0, 0, ecc, ee, 0};
}

IopConfig with_card(std::shared_ptr<mc::Card> card, u64 latency = 1) {
    IopConfig c;
    auto slot = std::make_shared<mc::IopSlotConfig>();
    slot->slot1 = std::move(card);
    slot->command_latency_cycles = latency;
    c.memcard = slot;
    return c;
}

}  // namespace

TEST_CASE("dbcman + MC2_S1: the boot sequence on an erased card gives PCSX2's bytes") {
    auto card = mc::Card::blank("blank");
    EeSide e(with_card(card));
    Dbc d(e);
    CHECK(load32(d.call(0x80001363u, {}), 0) == 0x320);
    // SetWorkAddr DMAs DBCMAN's table: socket words 0, device 0 attached (state 2, type 2, driver table,
    // port 2, slot 0).
    for (u32 i = 0; i < 128; i += 4) e.w32(kWork + i, 0xAAAAAAAAu);
    CHECK(load32(d.call(0x80001304u, {0, kWork}), 0) == 1);
    for (u32 i = 0; i < 64; i += 4) CHECK(e.r32(kWork + i) == 0);
    CHECK(e.r32(kWork + 72) == 2);
    CHECK(e.r32(kWork + 76) == 2);
    CHECK(e.r32(kWork + 84) == 0x00062E30u);
    CHECK(e.r32(kWork + 88) == 2);
    CHECK(e.r32(kWork + 92) == 0);
    const s32 sock = d.open_socket();
    REQUIRE(sock == 0);
    // sceDbcGetConnection 0x51CAD0: work[socket] == 1 -> connected; the device record now says linked (3) --
    // the bytes the PCSX2 atlus_logo state holds at 0x996F40 / 0x996F88.
    CHECK(e.r32(kWork) == 1);
    CHECK(e.r32(kWork + 72) == 3);
    CHECK(load32(d.call(0x80001303u, {0}), 4) == 0);   // GetDepNumber -> device 0
    CHECK(load32(d.call(0x80001315u, {0}), 4) == 1);   // InitSocket
    CHECK(load32(d.call(0x80001317u, {0}), 4) == 0);   // GetDeviceStatus: "not support"
    CHECK(static_cast<s32>(load32(d.call(0x80001302u, {5}), 4)) == -22);  // DeleteSocket of a free socket

    // _sceMcFatGetInfo on a new, unformatted card: CheckNewCard 2 -> ClearNewCardFlag -> GetCardSpec ->
    // ReadSysInfo (ReadPage2 page 0, count 1, no ECC) -> magic mismatch (0x8101002F).
    CHECK(d.mc2(0, 4, req(0, 0, 0)) == 2);
    CHECK(e.r32(kBuf0 + 0) == 1);  // counter 1, response to buffer 0 (toggle 0)
    CHECK(e.r32(kBuf0 + 8) == 2);
    // While the new flag is set every other command answers 2 with the previous block (no counter step).
    CHECK(d.mc2(0, 1, req(0, 1, 0)) == 2);
    CHECK(e.r32(kBuf1 + 0) == 1);
    CHECK(e.r32(kBuf1 + 8) == 2);
    CHECK(d.mc2(0, 13, req(0, 0, 0)) == 1);
    CHECK(e.r32(kBuf0 + 0) == 2);  // counter 2 -> buffer 0 again (toggle flipped twice)
    CHECK(d.mc2(0, 3, req(0, 0, 0)) == 1);
    CHECK(e.r32(kBuf1 + 0) == 3);
    CHECK(e.r32(kBuf1 + 8) == 1);
    CHECK(e.r32(kBuf1 + 12) == (512u | (16u << 16)));
    CHECK(e.r32(kBuf1 + 16) == 16384);
    CHECK(d.mc2(0, 1, req(0, 1, 0)) == 1);
    // ReadPage: data at buffer 0 + 128 (512 bytes of 0xFF), response at buffer 0 + 0 (not toggled).
    CHECK(e.r32(kBuf0 + 0) == 4);
    CHECK(e.r32(kBuf0 + 4) == 0);
    CHECK(e.r32(kBuf0 + 8) == 1);
    for (u32 i = 12; i < 128; i += 4) CHECK(e.r32(kBuf0 + i) == 0);
    for (u32 i = 0; i < 512; i += 4) CHECK(e.r32(kBuf0 + 128 + i) == 0xFFFFFFFFu);
    CHECK(e.r32(kBuf0 + 640) == 0);
    // The 1168-byte reply is the request with the result at +1164.
    CHECK(e.r32(kSend3 + 0) == 0);
    CHECK(e.r32(kSend3 + 4) == 1);
    CHECK(e.r32(kSend3 + 16) == 1);
    CHECK(card->stats().page_programs == 0);
    CHECK(card->stats().block_erases == 0);
}

TEST_CASE("dbcman + MC2_S1: reads with ECC, writes with the backup-block protocol, write-back, erase, clock") {
    auto card = mc::Card::blank("fmt");
    mc::format(*card);
    std::vector<u8> before(card->image().begin(), card->image().end());
    auto slot = with_card(card);
    EeSide e(slot);
    Dbc d(e);
    REQUIRE(d.open_socket() == 0);
    CHECK(d.mc2(0, 4, req(0, 0, 0)) == 2);
    CHECK(d.mc2(0, 13, req(0, 0, 0)) == 1);
    // Superblock with ECC: the data lands at buffer 0 + 128.
    CHECK(d.mc2(0, 1, req(0, 1, 1)) == 1);
    CHECK(std::memcmp(e.read(kBuf0 + 128, 28).data(), "Sony PS2 Memory Card Format ", 28) == 0);
    // Two pages: consecutive at +128 and +640.
    CHECK(d.mc2(0, 1, req(16, 2, 1)) == 1);
    CHECK(e.read(kBuf0 + 128, 4) == std::vector<u8>{9, 0, 0, 0});    // IFC cluster: first FAT cluster 9
    CHECK(e.read(kBuf0 + 640, 4) == std::vector<u8>{0xFF, 0xFF, 0xFF, 0xFF});
    // Out of range: page + count beyond the card -> status 0.
    CHECK(d.mc2(0, 1, req(16383, 2, 1)) == 0);

    // WritePage of page 0x205 (block 0x20 = 32) with backup blocks 1023 / 1022, from EE memory.
    std::vector<u8> pattern(512);
    for (u32 i = 0; i < 512; ++i) pattern[i] = static_cast<u8>(i * 7 + 3);
    e.write(kPageSrc, pattern);
    // Give block 32 some content first (no backup: the other pages are left erased).
    std::vector<u8> fill(512, 0x5A);
    e.write(kPageSrc + 0x1000, fill);
    for (u32 pg = 512; pg < 528; ++pg) CHECK(d.mc2(0, 2, req(pg, 1, 1, 1023, 0, kPageSrc + 0x1000)) == 1);
    for (u32 pg = 512; pg < 528; ++pg) {
        if (pg < 527) CHECK(card->raw_page(pg)[0] == 0xFF);  // each write erased the block again (no backup)
    }
    CHECK(card->raw_page(527)[0] == 0x5A);
    // Now one page with the backup protocol: the rest of the block is restored from backup block 1023.
    CHECK(d.mc2(0, 2, req(512 + 5, 1, 1, 1023, 1022, kPageSrc)) == 1);
    CHECK(std::memcmp(card->raw_page(517).data(), pattern.data(), 512) == 0);
    std::array<u8, 12> ecc{};
    mc::ecc_compute(pattern, ecc);
    CHECK(std::memcmp(card->raw_page(517).data() + 512, ecc.data(), 12) == 0);
    CHECK(card->raw_page(517)[524] == 0xFF);
    CHECK(card->raw_page(527)[0] == 0x5A);          // restored
    CHECK(card->raw_page(1023 * 16 + 15)[0] == 0x5A);  // the backup copy of block 32
    for (u8 b : card->raw_page(1022 * 16)) CHECK(b == 0xFF);  // backup block 2 erased again

    // Interrupted write: block 1022 page 0/1 name block 33, block 1023 holds its copy -> WriteBack restores.
    const std::array<u8, 4> marker{33, 0, 0, 0};  // block 1022 was erased by the write above
    card->program(1022 * 16, marker);
    card->program(1022 * 16 + 1, marker);
    CHECK(d.mc2(0, 6, req(0, 0, 1, 1023, 1022)) == 2);
    for (u32 i = 0; i < 16; ++i)
        CHECK(std::equal(card->raw_page(33 * 16 + i).begin(), card->raw_page(33 * 16 + i).begin() + 524, card->raw_page(1023 * 16 + i).begin()));
    for (u8 b : card->raw_page(1022 * 16)) CHECK(b == 0xFF);
    CHECK(d.mc2(0, 6, req(0, 0, 1, 1023, 1022)) == 1);  // nothing pending now

    // BlockErase (block number at +32), ReadClock (sceCdCLOCK BCD at +12).
    auto er = req(0, 0, 1);
    er[8] = 32;
    CHECK(d.mc2(0, 9, er) == 1);
    for (u8 b : card->raw_page(517)) CHECK(b == 0xFF);
    CHECK(d.mc2(0, 10, req(0, 0, 0)) == 1);
    const u32 clock_buf = (e.r32(kBuf0 + 0) > e.r32(kBuf1 + 0)) ? kBuf0 : kBuf1;  // SyncDma 0x51AD10's pick
    CHECK(e.read(clock_buf + 12, 8) == std::vector<u8>{0x00, 0x00, 0x00, 0x12, 0x00, 0x01, 0x01, 0x26});
    // Not modelled: fast transfers fail closed and are logged.
    CHECK(d.mc2(0, 17, req(0, 1, 1)) == 0);
    bool logged = false;
    for (const auto& u : e.sif.iop().unknown_events())
        if (u.id == 0x8000131Cu && u.fno == 17) logged = true;
    CHECK(logged);
    CHECK(card->stats().program_conflicts == 0);
    CHECK(card->image().size() == before.size());
}

TEST_CASE("dbcman: no card -> not linked, work area 0, page commands get -23; send_data2 path") {
    EeSide e;  // IopConfig::memcard == nullptr
    Dbc d(e);
    const s32 sock = d.open_socket();
    CHECK(sock == 0);
    CHECK(e.r32(kWork) == 0);                     // GetConnection -> 3 (no card) -> _sceMcFatGetInfo 0x81010013
    CHECK(e.r32(kWork + 72) == 1);                // MC2_S1's device registered, not attached
    CHECK(e.r32(kWork + 88) == 0xFFFFFFFFu);      // port -1
    CHECK(static_cast<s32>(load32(d.call(0x80001303u, {0}), 4)) == -12);
    CHECK(static_cast<s32>(load32(d.call(0x80001315u, {0}), 4)) == -23);
    CHECK(d.mc2(0, 4, req(0, 0, 0)) == -23);      // DBCMAN .text 0x7D0: no linked device
    CHECK(d.mc2(9, 4, req(0, 0, 0)) == -22);      // not a socket

    // With a card, send_data2 (144 bytes, result at +140) runs the same commands.
    EeSide e2(with_card(mc::Card::blank()));
    Dbc d2(e2);
    REQUIRE(d2.open_socket() == 0);
    std::vector<u8> b(144, 0);
    store32(b, 0, 0);
    store32(b, 4, 4);
    store32(b, 8, 48);
    e2.write(0x00997000, b);
    const int before = d2.ends;
    REQUIRE(e2.call(d2.send2, 0x8000131Eu, 1, 0x00997000, 144, 0x00997000, 144, kMc2Callback, 0));
    e2.bus.advance(1);
    e2.sif.service();
    e2.pump();
    CHECK(d2.ends == before + 1);
    CHECK(e2.r32(0x00997000 + 140) == 2);  // CheckNewCard on a new card
    // DeleteSocket unlinks and clears the work word.
    CHECK(load32(d2.call(0x80001302u, {0}), 4) == 1);
    CHECK(e2.r32(kWork) == 0);
    CHECK(e2.r32(kWork + 72) == 2);
}

TEST_CASE("dbcman: a send_data3 completes only after the configured latency") {
    auto card = mc::Card::blank();
    EeSide e(with_card(card, 1000));
    Dbc d(e);
    REQUIRE(d.open_socket() == 0);
    for (u32 i = 0; i < 256; i += 4) e.w32(kBuf0 + i, 0);
    std::vector<u8> b(1168, 0);
    store32(b, 4, 4);
    store32(b, 8, 48);
    e.write(kSend3, b);
    REQUIRE(e.call(d.send3, 0x8000131Cu, 1, kSend3, 1168, kSend3, 1168, kMc2Callback, 0));
    e.bus.advance(999);
    e.sif.service();
    e.pump();
    CHECK(d.ends == 0);
    CHECK(e.r32(kBuf0) == 0);  // nothing reached the EE yet
    CHECK(e.sif.next_event_cycles() <= e.bus.tb.cycles + 1);
    e.bus.advance(1);
    e.sif.service();
    e.pump();
    CHECK(d.ends == 1);
    CHECK(e.r32(kBuf0) == 1);
    CHECK(e.r32(kBuf0 + 8) == 2);
}

TEST_CASE("memcard sources: open_or_create makes the port's own formatted card once and reopens it in place") {
    const fs::path dir = temp_dir("own");
    const fs::path card = dir / "P3FES" / "saves" / "Mcd001.ps2";  // parents do not exist yet
    REQUIRE_FALSE(fs::exists(card));
    mc::DateTime t{1, 2, 3, 4, 5, 2026};
    auto r = mc::open_or_create(card, t);
    REQUIRE(r.ok);
    REQUIRE(r.card);
    CHECK(r.description.find("created now") != std::string::npos);
    REQUIRE(fs::exists(card));
    CHECK(fs::file_size(card) == mc::kImageSize);
    {
        mc::FsView v(*r.card);
        REQUIRE(v.ok());  // formatted, not erased
    }
    // A change is written in place, and the second open sees it without creating anything.
    CHECK(r.card->erase_block(16000));  // a free data block (block 1000), not the superblock or the FAT
    CHECK(r.card->flush());
    const auto size_after = fs::file_size(card);
    CHECK(size_after == mc::kImageSize);
    auto r2 = mc::open_or_create(card, t);
    REQUIRE(r2.ok);
    CHECK(r2.description.find("created now") == std::string::npos);
    CHECK(r2.description.find("written in place") != std::string::npos);
    mc::FsView v2(*r2.card);
    CHECK(v2.ok());
    fs::remove_all(dir);
}
