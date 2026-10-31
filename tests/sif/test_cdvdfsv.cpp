// cdvdfsv through the SIF: libcdvd's calls re-enacted (sceCdInit 0x510460, sceCdMmode 0x511040,
// sceCdRead 0x510B80 + _sceCd_cd_read_intr 0x50F8A8, sceCdSync(1) 0x510148, sceCdBreak 0x510F88,
// sceCdLayerSearchFile 0x50FC38) against a synthetic disc, and against the user's ISO when present.
#include <doctest.h>

#include <algorithm>
#include <cstring>

#include "../hle/hle_fixtures.h"
#include "p3fes/hle/cdvd.h"
#include "sif_harness.h"

using namespace p3fes;
using namespace p3fes::test;

namespace {

// libcdvd's EE globals (obs).
constexpr u32 kNcmdSend = 0x00780C80;  // sceCd_ncmdsdata
constexpr u32 kRdData = 0x00781C80;    // 144-byte head/tail block (end_param)
constexpr u32 kReadPos = 0x00781D40;
constexpr u32 kCbSem = 0x00780BB4;     // sceCd_c_cb_sem
constexpr u32 kReadIntr = 0x0050F8A8;  // _sceCd_cd_read_intr (end function)
constexpr u32 kCdCallback = 0x0050F698;
constexpr u32 kSearchPkt = 0x0096DA80;

struct Cd {
    EeSide& e;
    u32 init, s, n, srch, ready;
    int read_ends = 0, other_ends = 0;
    explicit Cd(EeSide& ee) : e(ee) {
        e.init_rpc();
        init = e.bind(0x80000592u);
        s = e.bind(0x80000593u);
        n = e.bind(0x80000595u);
        srch = e.bind(0x80000597u);
        ready = e.bind(0x8000059Cu);
        e.on_end = [this](u32 param) {
            if (param == kRdData) {  // _sceCd_cd_read_intr: copy head/tail, then _sceCd_cd_callback
                const u32 hl = e.r32(kRdData), tl = e.r32(kRdData + 4);
                if (hl) e.write(e.r32(kRdData + 8), e.read(kRdData + 16, hl));
                if (tl) e.write(e.r32(kRdData + 12), e.read(kRdData + 80, tl));
                ++read_ends;
            } else {
                ++other_ends;
            }
            e.w32(kCbSem, 0);
        };
    }
    u32 scmd(u32 fno, std::vector<u8> send = {}) { return load32(e.call_sync(s, fno, send, 4), 0); }
    void read(u32 lsn, u32 sectors, u32 buf) {
        e.w32(kCbSem, 1);
        e.write(kNcmdSend, words({lsn, sectors, buf, 0, kRdData, kReadPos}));
        e.w32(kReadPos, 0);
        e.call(n, 1, 1, kNcmdSend, 24, 0, 0, kReadIntr, kRdData);
    }
    void seek(u32 lsn) {
        e.w32(kCbSem, 1);
        e.write(kNcmdSend, words({lsn}));
        e.call(n, 5, 1, kNcmdSend, 4, 0, 0, kCdCallback, 0x780BE0);
    }
    bool busy() { return e.r32(kCbSem) != 0 || e.check_stat(n); }  // sceCdSync(1)
    // srd_exec_dvd-style: poll until done, advancing virtual time like the fs thread's wake-ups.
    int wait(u64 step = 1000, int max_steps = 100000) {
        int steps = 0;
        while (busy()) {
            e.bus.advance(step);
            e.sif.service();
            e.pump();
            REQUIRE(++steps < max_steps);
        }
        return steps;
    }
    std::vector<u8> search(const std::string& path, u32 layer = 0) {
        std::vector<u8> pkt(300, 0);
        std::fill(pkt.begin(), pkt.begin() + 36, u8{0xAB});
        std::memcpy(pkt.data() + 36, path.data(), path.size());
        store32(pkt, 292, kSearchPkt);
        store32(pkt, 296, layer);
        e.write(kSearchPkt, pkt);
        last_search = load32(e.call_sync(srch, 0, pkt, 4), 0);
        return e.read(kSearchPkt, 36);
    }
    u32 last_search = 0;
};

void fill(EeSide& e, u32 a, u32 n, u8 v) {
    std::vector<u8> b(n, v);
    e.write(a, b);
}

}  // namespace

TEST_CASE("cdvdfsv: init, mmode, disk type, error, disk ready") {
    SynthDisc disc;
    EeSide e({}, &disc);
    Cd cd(e);
    const auto r = e.call_sync(cd.init, 0, words({0}), 16);
    CHECK(load32(r, 0) == 1);
    CHECK((load32(r, 4) >> 8) >= 2);  // sceCdInit returns 2 for old modules
    CHECK((load32(r, 8) >> 8) >= 2);
    CHECK(load32(r, 12) != 254);
    CHECK(load32(r, 12) != 255);
    CHECK(cd.scmd(34, words({2})) == 1);  // sceCdMmode(SCECdMmodeDvd)
    CHECK(e.sif.iop().cdvd()->media_mode() == 2);
    CHECK(cd.scmd(3) == 0x14);  // SCECdPS2DVD
    CHECK(cd.scmd(4) == 0);
    CHECK(load32(e.call_sync(cd.ready, 0, words({0}), 4), 0) == 2);
    CHECK(load32(e.call_sync(cd.n, 14, {}, 4), 0) == 2);  // sceCdRead's pre-check
}

TEST_CASE("cdvdfsv: sceCdRead lands at the requested buffer only at completion, then the RPC end") {
    SynthDisc disc;
    IopConfig cfg;
    cfg.cd_fixed_latency_cycles = 1000;
    EeSide e(cfg, &disc);
    Cd cd(e);
    const u32 buf = 0x00A00000, n = 4, lsn = 100;
    fill(e, buf, n * 2048, 0xEE);
    const u64 t0 = e.bus.tb.cycles;
    cd.read(lsn, n, buf);
    CHECK(cd.busy());
    CHECK(e.read(buf, 1)[0] == 0xEE);
    CHECK(e.sif.next_event_cycles() == t0 + 1000);
    e.bus.advance(999);
    e.sif.service();
    CHECK(e.pump() == 0);
    CHECK(cd.busy());
    e.bus.advance(1);
    e.sif.service();
    CHECK(e.pump() == 1);
    CHECK_FALSE(cd.busy());
    CHECK(cd.read_ends == 1);
    const auto data = e.read(buf, n * 2048);
    bool same = true;
    for (u32 s = 0; s < n; ++s)
        for (u32 i = 0; i < 2048; ++i) same = same && data[s * 2048 + i] == SynthDisc::pattern(lsn + s, i);
    CHECK(same);
    CHECK(e.r32(kRdData + 0) == 0);  // aligned: no head
    CHECK(e.r32(kRdData + 4) == 0);  // no tail
    CHECK(e.r32(kRdData + 8) == buf);
    CHECK(e.r32(kRdData + 12) == buf + n * 2048);
    CHECK(e.r32(kReadPos) == n * 2048);
    CHECK(cd.scmd(4) == 0);
    CHECK(e.sif.iop().cdvd()->completions() == 1);
    CHECK(e.sif.iop().stats().cd_sectors == n);
    // second read right away: the one-request contract is free again
    cd.read(lsn + n, 2, buf);
    cd.wait();
    CHECK(cd.read_ends == 2);
    CHECK(e.read(buf, 1)[0] == SynthDisc::pattern(lsn + n, 0));
}

TEST_CASE("cdvdfsv: default latency still completes after the issuing syscall, never inside it") {
    SynthDisc disc;
    EeSide e({}, &disc);
    Cd cd(e);
    cd.read(10, 1, 0x00A00000);
    CHECK(cd.busy());
    CHECK(e.bus.pending_ch5 == 0);
    CHECK(cd.wait() == 1);
}

TEST_CASE("cdvdfsv: unaligned destination goes through the head/tail block") {
    SynthDisc disc;
    EeSide e({}, &disc);
    Cd cd(e);
    const u32 buf = 0x00A00010, n = 2, lsn = 300;
    fill(e, buf - 64, n * 2048 + 128, 0xEE);
    cd.read(lsn, n, buf);
    cd.wait();
    CHECK(e.r32(kRdData + 0) == 48);
    CHECK(e.r32(kRdData + 4) == 16);
    const auto data = e.read(buf, n * 2048);
    bool same = true;
    for (u32 s = 0; s < n; ++s)
        for (u32 i = 0; i < 2048; ++i) same = same && data[s * 2048 + i] == SynthDisc::pattern(lsn + s, i);
    CHECK(same);
    CHECK(e.read(buf - 1, 1)[0] == 0xEE);
    CHECK(e.read(buf + n * 2048, 1)[0] == 0xEE);
}

TEST_CASE("cdvdfsv: sceCdBreak aborts the in-flight read; seek completes through the callback") {
    SynthDisc disc;
    IopConfig cfg;
    cfg.cd_fixed_latency_cycles = 1'000'000;
    EeSide e(cfg, &disc);
    Cd cd(e);
    const u32 buf = 0x00A00000;
    fill(e, buf, 2048, 0xEE);
    cd.read(50, 1, buf);
    CHECK(cd.scmd(22) == 1);  // the S-command's end arrives first, the aborted read's right behind it
    CHECK_FALSE(cd.busy());
    CHECK(cd.read_ends == 1);
    CHECK(cd.scmd(4) == static_cast<u32>(hle::cd::kErrAbort));
    CHECK(e.read(buf, 1)[0] == 0xEE);
    CHECK(e.r32(kReadPos) == 0);
    cd.seek(1234);
    cd.wait(100'000);
    CHECK(cd.other_ends == 1);
    CHECK(cd.scmd(4) == 0);
}

TEST_CASE("cdvdfsv: refused reads still end, and report SCECdErREAD") {
    EeSide e;  // no disc
    Cd cd(e);
    cd.read(10, 1, 0x00A00000);
    cd.wait();
    CHECK(cd.read_ends == 1);
    CHECK(cd.scmd(4) == static_cast<u32>(hle::cd::kErrRead));
    SynthDisc disc;
    EeSide e2({}, &disc);
    Cd cd2(e2);
    cd2.read(SynthDisc::kSectors - 1, 4, 0x00A00000);  // past the end of the disc
    cd2.wait();
    CHECK(cd2.read_ends == 1);
    CHECK(cd2.scmd(4) == static_cast<u32>(hle::cd::kErrRead));
    cd2.read(1, 1, 0x00A00000);  // and the next one works
    cd2.wait();
    CHECK(cd2.scmd(4) == 0);
}

// IopConfig::cd_read_sink (the host's --read-log; docs/MODERNIZE_PLAN.md §3 stage 0): one event per read with the
// bytes delivered, and the same guest memory as a run without the sink.
TEST_CASE("cdvdfsv: the read sink reports every read with its bytes and leaves guest memory untouched") {
    struct Run {
        std::vector<CdReadEvent> events;
        std::vector<std::vector<std::byte>> data;
        std::vector<u8> ram;
    };
    auto run = [](bool with_sink) {
        Run out;
        SynthDisc disc;
        IopConfig cfg;
        if (with_sink)
            cfg.cd_read_sink = [&out](const CdReadEvent& ev) {
                out.events.push_back(ev);
                out.data.emplace_back(ev.data.begin(), ev.data.end());
            };
        EeSide e(cfg, &disc);
        Cd cd(e);
        fill(e, 0x00A00000, 0x10000, 0xEE);
        cd.read(100, 4, 0x00A00000);  // aligned: straight into guest RAM
        cd.wait();
        cd.read(300, 2, 0x00A08010);  // unaligned: the staging copy + head / tail block
        cd.wait();
        cd.read(SynthDisc::kSectors - 1, 4, 0x00A00000);  // past the end: refused
        cd.wait();
        cd.read(7, 1, 0x00A04000);
        cd.wait();
        out.ram = e.read(0, static_cast<u32>(EEMemory::kMainRamSize));
        return out;
    };
    const Run plain = run(false), logged = run(true);
    CHECK(plain.events.empty());
    CHECK(plain.ram == logged.ram);  // the sink changes nothing the guest sees
    REQUIRE(logged.events.size() == 4);
    auto expect = [](u32 lsn, u32 n) {
        std::vector<std::byte> v(static_cast<std::size_t>(n) * 2048);
        for (u32 s = 0; s < n; ++s)
            for (u32 i = 0; i < 2048; ++i) v[static_cast<std::size_t>(s) * 2048 + i] = std::byte{SynthDisc::pattern(lsn + s, i)};
        return v;
    };
    const CdReadEvent& a = logged.events[0];
    CHECK(a.lsn == 100);
    CHECK(a.sectors == 4);
    CHECK(a.dst == 0x00A00000);
    CHECK(a.error == 0);
    CHECK(logged.data[0] == expect(100, 4));
    CHECK(logged.events[1].dst == 0x00A08010);
    CHECK(logged.data[1] == expect(300, 2));
    CHECK(logged.events[2].error == hle::cd::kErrRead);
    CHECK(logged.data[2].empty());
    CHECK(logged.events[3].lsn == 7);
    CHECK(logged.data[3] == expect(7, 1));
    CHECK(logged.events[3].cycle > logged.events[0].cycle);
}

TEST_CASE("cdvdfsv: sceCdLayerSearchFile reply fields") {
    SynthDisc disc;
    EeSide e({}, &disc);
    Cd cd(e);
    const auto fp = cd.search("\\DATA.CVM;1");
    CHECK(cd.last_search == 1);
    CHECK(load32(fp, 0) == 1000);
    CHECK(load32(fp, 4) == 3 * 2048 + 17);
    CHECK(std::string(reinterpret_cast<const char*>(fp.data() + 8)) == "DATA.CVM;1");
    for (int i = 8 + 10; i < 24; ++i) CHECK(fp[i] == 0);
    // Date from the ISO directory record in cdvdman's mapping: {0, sec, min, hour, day, month, year LE}; flag 0.
    // The PCSX2 first_flip state holds exactly these bytes for DATA.CVM at 0x7A2928 (2008-01-04 14:55:42).
    const u8 date[8] = {0, 42, 55, 14, 4, 1, 0xD8, 0x07};
    for (int i = 0; i < 8; ++i) CHECK(fp[static_cast<std::size_t>(24 + i)] == date[i]);
    for (int i = 32; i < 36; ++i) CHECK(fp[i] == 0);
    const auto none = cd.search("\\NOPE.BIN;1");
    CHECK(cd.last_search == 0);
    for (u8 b : none) CHECK(b == 0xAB);  // the IOP's copy of the request goes back unchanged
    cd.search("\\DATA.CVM;1", 1);
    CHECK(cd.last_search == 0);  // single-layer disc
}

TEST_CASE("cdvdfsv on the user's ISO: boot-time CVM searches and manifest files byte-exact") {
    auto iso = open_real_iso();
    if (!iso) {
        MESSAGE("input/persona3fes.iso absent (set P3FES_ISO): skipped");
        return;
    }
    EeSide e({}, iso.get());
    Cd cd(e);
    for (const char* name : {"DATA.CVM", "BGM.CVM", "BTL.CVM"}) {
        const auto* lay = hle::find_disc_layout(name);
        REQUIRE(lay != nullptr);
        const auto fp = cd.search(std::string("\\") + name + ";1");
        CHECK(cd.last_search == 1);
        CHECK(load32(fp, 0) == lay->lsn);
        CHECK(load32(fp, 4) == lay->size);
        CHECK(std::string(reinterpret_cast<const char*>(fp.data() + 8)) == std::string(lay->identifier));
    }
    auto manifest = load_manifest();
    if (!manifest) {
        MESSAGE("extracted/manifest.json absent: file comparisons skipped");
        return;
    }
    std::map<std::string, int> taken;
    int compared = 0;
    for (const auto& m : *manifest) {
        if (m.size == 0 || m.size > 200'000 || taken[m.container] >= 3) continue;
        const auto* lay = hle::find_disc_layout(m.container);
        if (!lay) continue;
        auto host = read_host_file(extracted_dir() / m.path);
        if (!host) continue;
        ++taken[m.container];
        const u32 sectors = static_cast<u32>((m.size + 2047) / 2048);
        const u32 buf = 0x01000000;
        for (u32 done = 0; done < sectors;) {
            const u32 chunk = std::min<u32>(32, sectors - done);
            cd.read(hle::cvm_file_lsn(*lay, m.lba) + done, chunk, buf + done * 2048);
            cd.wait();
            REQUIRE(cd.scmd(4) == 0);
            done += chunk;
        }
        const auto got = e.read(buf, static_cast<u32>(m.size));
        CAPTURE(m.path);
        CHECK(std::memcmp(got.data(), host->data(), static_cast<std::size_t>(m.size)) == 0);
        ++compared;
    }
    MESSAGE("compared " << compared << " manifest files through cdvdfsv");
    CHECK(compared >= 3);
}
