// Decoder acceptance tests (ADR-0011 §3, oracle 1 of 3: census equivalence).
//
// Part A (always runs): table invariants, encoding spot checks and the fail-closed policy.
// Part B (needs the ELF): decode every instruction word inside every IDA function chunk of
// SLUS_216.21 and reproduce symbols/insn_census.json exactly: per-mnemonic counts, total word
// count, 0 Invalid. Skips cleanly (MESSAGE + return) when the ELF is absent.
//
// Scope source: symbols/function_chunks.txt (IDA chunk ranges + data items inside
// chunks, exported read-only from the same database state the census used). symbols/functions.json
// carries only start+total size, which cannot reproduce the census for the 173 multi-chunk
// functions nor exclude the 1,553 data words; the test reports how the two inputs differ.
//
// Oracles 2 and 3 (rabbitizer, binutils objdump) are recomp/tests/oracle_decode.py.
#include "doctest.h"

#include "elf_image.h"
#include "function_list.h"
#include "json_lite.h"
#include "r5900_decode.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace p3fes::recomp;

// ---------------------------------------------------------------------------------------------
// Part A: static properties.

static_assert(static_cast<int>(Op::Count) == 199, "198 census mnemonics + Invalid");

// Encodings observed in the binary (VAs from docs/ANALYSIS/08_instruction_census.md).
static_assert(decode_op(0x70000c28) == Op::Padduw);   // 0x100008  padduw at,zero,zero
static_assert(decode_op(0x4be25ad8) == Op::Vmul);     // 0x285a9c  vmulx.xyzw
static_assert(decode(0x4be25ad8, 0x285a9c).vu_bc && decode(0x4be25ad8, 0x285a9c).bc == 0);
static_assert(decode(0x4be25ad8, 0x285a9c).dest == 0xF);
static_assert(decode_op(0x4beb593c) == Op::Vitof0);   // 0x285a8c  vitof0.xyzw
static_assert(!decode(0x4beb593c, 0).vu_bc);
static_assert(decode_op(0x48225000) == Op::Qmfc2);    // 0x285b14  qmfc2 v0,vf10 (.ni)
static_assert(!decode(0x48225000, 0).interlock);
static_assert(decode(0x48225001, 0).interlock);
static_assert(decode_op(0x0000040f) == Op::Sync);     // 0x100114  sync.p
static_assert(decode(0x0000040f, 0).sync_p());
static_assert(!decode(0x0000000f, 0).sync_p());      // 0x10e6b8  sync (.l)
static_assert(decode_op(0x4a0203bd) == Op::Vsqrt);    // 0x3262ec  vsqrt (binutils prints raw c2)
static_assert(decode_op(0x70000830) == Op::Pmfhl);    // pmfhl.lw at
static_assert(decode(0x70000830, 0).pmfhl_fmt() == PmfhlFmt::Lw);
static_assert(decode_op(0x41000000 | (8u << 21)) == Op::Bc0f);  // IDA's "mfthc1 $ra,$f0"
static_assert(decode_op(0x70000000 | (9u) | (0x1Eu << 6)) == Op::Pexew);  // IDA's "pexow"

// Control-flow flags and targets.
static_assert(decode(0x0c040002, 0x100000).is_call && decode(0x0c040002, 0x100000).target == 0x100008);  // jal
static_assert(decode(0x10000003, 0x100000).is_branch && decode(0x10000003, 0x100000).target == 0x100010);  // beq +3
static_assert(decode(0x1000fffe, 0x100008).target == 0x100004);  // beq -2 (backwards)
static_assert(decode(0x50000001, 0).is_likely && decode(0x50000001, 0).has_delay_slot);  // beql
static_assert(decode(0x03e00008, 0).is_jump && !decode(0x03e00008, 0).is_call);  // jr ra
static_assert(decode(0x0040f809, 0).is_call);  // jalr v0
static_assert(decode(0x45000000, 0).is_branch && !decode(0x45000000, 0).is_likely);  // bc1f
static_assert(decode(0x45020000, 0).is_likely);  // bc1fl
static_assert(!decode(0x0000000c, 0).has_delay_slot);  // syscall

// Fail closed: EE-less generic MIPS encodings and EE instructions outside the census.
static_assert(decode_op(0xc0000000) == Op::Invalid);  // ll
static_assert(decode_op(0xe0000000) == Op::Invalid);  // sc
static_assert(decode_op(0x0000001c) == Op::Invalid);  // dmult
static_assert(decode_op(0x0000001e) == Op::Invalid);  // ddiv
static_assert(decode_op(0xd4000000) == Op::Invalid);  // ldc1
static_assert(decode_op(0xf4000000) == Op::Invalid);  // sdc1
static_assert(decode_op(0x46200000) == Op::Invalid);  // add.d (COP1 fmt D)
static_assert(decode_op(0x46000021) == Op::Invalid);  // cvt.d.s
static_assert(decode_op(0xcc000000) == Op::Invalid);  // pref
static_assert(decode_op(0x42000002) == Op::Invalid);  // tlbwi
static_assert(decode_op(0x42000008) == Op::Invalid);  // tlbp
static_assert(decode_op(0x0000002c) == Op::Invalid);  // dadd (EE, unused)
static_assert(decode_op(0x00000030) == Op::Invalid);  // tge (EE, unused)
static_assert(decode_op(0x04100000) == Op::Invalid);  // bltzal (EE, unused)
static_assert(decode_op(0x49000000) == Op::Invalid);  // bc2f (EE, unused)
static_assert(decode_op(0x4a000038) == Op::Invalid);  // vcallms (EE, unused)
static_assert(decode_op(0x4a00037c) == Op::Invalid);  // vlqi (special2 row 0 col 13)
static_assert(decode_op(0x70000004) == Op::Invalid);  // plzcw (EE, unused)
static_assert(decode_op(0x70000031) == Op::Invalid);  // pmthl (EE, unused)
static_assert(decode_op(0x70000970) == Op::Invalid);  // pmfhl fmt 5 does not exist
static_assert(decode_op(0x74000000) == Op::Invalid);  // opcode 0x1d (unused)
static_assert(decode_op(0x7c000000) == Op::Sq);       // opcode 0x1f is sq

TEST_CASE("r5900: every op has a unique census spelling") {
    std::set<std::string> seen;
    for (int i = 0; i < static_cast<int>(Op::Count); ++i) {
        const char* m = mnemonic(static_cast<Op>(i));
        REQUIRE(m != nullptr);
        CHECK(seen.insert(m).second);
    }
    CHECK(std::strcmp(mnemonic(Op::Invalid), "<invalid>") == 0);
    CHECK(std::strcmp(mnemonic(Op::CvtSW), "cvt.s.w") == 0);
    CHECK(std::strcmp(mnemonic(Op::CLeS), "c.le.s") == 0);
}

TEST_CASE("r5900: variant spellings match the census") {
    char buf[48];
    auto var = [&](std::uint32_t w) { variant_mnemonic(decode(w, 0), buf, sizeof buf); return std::string(buf); };
    CHECK(var(0x4be25ad8) == "vmulx.xyzw");
    CHECK(var(0x4beb593c) == "vitof0.xyzw");
    CHECK(var(0x0000040f) == "sync.p");
    CHECK(var(0x0000000f) == "sync.l");
    CHECK(var(0x70000830) == "pmfhl.lw");
    CHECK(var(0x48225000) == "qmfc2");
    CHECK(var(0x48225001) == "qmfc2.i");
    CHECK(var(0x4a0203bd) == "vsqrt");
    CHECK(var(0x70000c28) == "padduw");
    // Truncation reports the needed length and still terminates.
    char tiny[4];
    CHECK(variant_mnemonic(decode(0x4be25ad8, 0), tiny, sizeof tiny) == std::strlen("vmulx.xyzw"));
    CHECK(std::strlen(tiny) == 3);
}

TEST_CASE("r5900: table slots for excluded ops decode every field but no op") {
    const Insn i = decode(0x0000002c, 0x1000);  // dadd zero,zero,zero
    CHECK(i.op == Op::Invalid);
    CHECK(unit_of(i.op) == Unit::Invalid);
    CHECK(!i.has_delay_slot);
    CHECK(i.word == 0x0000002c);
    CHECK(i.pc == 0x1000);
}

TEST_CASE("elf_image: sha256 known answers") {
    char hex[65];
    sha256_hex(nullptr, 0, hex);
    CHECK(std::string(hex) == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    const char* abc = "abc";
    sha256_hex(reinterpret_cast<const std::uint8_t*>(abc), 3, hex);
    CHECK(std::string(hex) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    // 56 bytes: exercises the two-block padding path.
    const char* s56 = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    sha256_hex(reinterpret_cast<const std::uint8_t*>(s56), 56, hex);
    CHECK(std::string(hex) == "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}

TEST_CASE("function_list: parses functions.json entries and a chunk list") {
    FunctionList fl;
    REQUIRE(fl.load_functions_json(R"([{"a":"0x100008","s":520,"n":"start"},{"a":"0x46bfb0","s":896,"n":"sub_46BFB0"}])") == nullptr);
    REQUIRE(fl.functions.size() == 2);
    CHECK(fl.find(0x100008)->name == "start");
    CHECK(fl.find(0x100008)->size == 520);
    std::size_t mism = 0;
    REQUIRE(fl.apply_chunk_list("# comment\n100008 start C 100008-100210\n46bfb0 sub_46BFB0 C 46bfb0-46c000 46c100-46c330 D 46c000:16\n"
                                "500000 extra C 500000-500010\n", &mism) == nullptr);
    CHECK(mism == 1);  // `extra` only in the chunk list
    const Function* f = fl.find(0x46bfb0);
    REQUIRE(f != nullptr);
    REQUIRE(f->chunks.size() == 2);
    CHECK(f->chunks[1].start == 0x46c100);
    CHECK(f->is_data(0x46c008));
    CHECK(!f->is_data(0x46c010));
    CHECK(fl.find(0x500000)->size == 0x10);
    CHECK(fl.apply_chunk_list("zzz\n", nullptr) != nullptr);
}

// ---------------------------------------------------------------------------------------------
// Part B: census equivalence over the real ELF.

namespace {

std::string elf_path() {
    if (const char* env = std::getenv("P3FES_ELF"); env && *env) return env;
    return P3FES_ELF_DEFAULT;
}

bool load_text(const char* path, std::string& out) { return read_file(path, out); }

std::string hex32(std::uint32_t v) {
    char buf[16];
    std::snprintf(buf, sizeof buf, "0x%08x", v);
    return buf;
}

}  // namespace

TEST_CASE("census: our table reproduces symbols/insn_census.json over every function word") {
    ElfImage elf;
    const std::string path = elf_path();
    {
        std::string probe;
        if (!load_text(path.c_str(), probe)) {
            MESSAGE("SKIP: ELF not present at ", path, " (set P3FES_ELF)");
            return;
        }
    }
    const ElfImage::LoadResult lr = elf.load(path.c_str());
    const std::string load_error = lr.error ? lr.error : "";
    REQUIRE_MESSAGE(lr.error == nullptr, load_error, " sha256=", lr.sha256_hex);
    CHECK(std::string(lr.sha256_hex) == kSlusSha256);
    CHECK(elf.entry() == 0x100008);
    REQUIRE(elf.segments().size() >= 1);
    // docs/ANALYSIS/00_elf_layout.md: one PT_LOAD with bytes, p_offset 0x80, p_vaddr 0x100000, filesz == memsz.
    std::size_t with_bytes = 0;
    for (const ElfSegment& s : elf.segments()) {
        if (!s.filesz) continue;
        ++with_bytes;
        CHECK(s.offset == 0x80);
        CHECK(s.vaddr == 0x100000);
        CHECK(s.filesz == s.memsz);
    }
    CHECK(with_bytes == 1);
    CHECK(elf.file_offset(0x100000) == std::size_t(0x80));
    CHECK(elf.word_at(0x100008) == 0x70000c28u);
    CHECK(!elf.word_at(0x100009).has_value());
    CHECK(!elf.word_at(0x00000000).has_value());

    // Census JSON.
    std::string census_text;
    REQUIRE_MESSAGE(load_text(P3FES_CENSUS_JSON, census_text), "cannot read ", P3FES_CENSUS_JSON);
    json::ParseResult census = json::Parser::parse(census_text);
    const std::string census_error = census.error ? census.error : "";
    REQUIRE_MESSAGE(census.error == nullptr, census_error);
    std::map<std::string, std::uint64_t> expected;
    {
        const json::Value* units = census.value.get("units");
        REQUIRE(units != nullptr);
        REQUIRE(units->is_object());
        for (const auto& [unit, table] : units->fields) {
            REQUIRE(table.is_object());
            for (const auto& [mn, cnt] : table.fields) {
                std::uint64_t c = 0;
                REQUIRE(cnt.to_u64(c));
                CHECK_MESSAGE(expected.emplace(mn, c).second, "mnemonic listed under two units: ", mn);
            }
        }
    }
    std::uint64_t expected_words = 0, expected_functions = 0, expected_data_items = 0;
    REQUIRE(census.value.get("words_decoded")->to_u64(expected_words));
    REQUIRE(census.value.get("functions")->to_u64(expected_functions));
    REQUIRE(census.value.get("data_items_in_functions")->get("items")->to_u64(expected_data_items));

    // The enum covers exactly the census set.
    {
        std::set<std::string> ours;
        for (int i = 1; i < static_cast<int>(Op::Count); ++i) ours.insert(mnemonic(static_cast<Op>(i)));
        for (const auto& [mn, _] : expected) CHECK_MESSAGE(ours.count(mn) == 1, "census mnemonic missing from Op: ", mn);
        for (const std::string& mn : ours) CHECK_MESSAGE(expected.count(mn) == 1, "Op not in the census: ", mn);
        CHECK(ours.size() == expected.size());
    }

    // Scope: functions.json + chunk list.
    FunctionList fl;
    std::string text;
    REQUIRE_MESSAGE(load_text(P3FES_FUNCTIONS_JSON, text), "cannot read ", P3FES_FUNCTIONS_JSON);
    REQUIRE(fl.load_functions_json(text) == nullptr);
    const std::size_t functions_json_count = fl.functions.size();
    REQUIRE_MESSAGE(load_text(P3FES_FUNCTION_CHUNKS, text), "cannot read ", P3FES_FUNCTION_CHUNKS);
    std::size_t set_mismatches = 0;
    REQUIRE(fl.apply_chunk_list(text, &set_mismatches) == nullptr);
    std::size_t with_chunks = 0, data_items = 0, multi_chunk = 0;
    for (const Function& f : fl.functions) {
        if (!f.chunks.empty()) ++with_chunks;
        if (f.chunks.size() > 1) ++multi_chunk;
        data_items += f.data.size();
    }
    MESSAGE("functions.json: ", functions_json_count, " functions; chunk list: ", with_chunks,
            " functions (", multi_chunk, " multi-chunk, ", data_items, " data items); starts in only one input: ",
            set_mismatches);
    CHECK(with_chunks == expected_functions);
    CHECK(data_items == expected_data_items);

    // Decode. Functions without chunk info (present only in functions.json) are outside the census scope.
    std::vector<std::uint64_t> counts(static_cast<std::size_t>(Op::Count), 0);
    std::uint64_t words = 0, skipped_data = 0, unbacked = 0, outside_scope = 0;
    std::uint32_t first_invalid = 0, first_unbacked = 0;
    for (const Function& f : fl.functions) {
        if (f.chunks.empty()) { ++outside_scope; continue; }
        for (const Range& r : f.chunks) {
            REQUIRE((r.start & 3u) == 0);
            for (std::uint32_t va = r.start; va + 4 <= r.end; va += 4) {
                if (f.is_data(va)) { ++skipped_data; continue; }
                const auto w = elf.word_at(va);
                if (!w) { if (!unbacked) first_unbacked = va; ++unbacked; continue; }
                const Insn insn = decode(*w, va);
                ++words;
                if (insn.op == Op::Invalid && counts[0] == 0) first_invalid = va;
                ++counts[static_cast<std::size_t>(insn.op)];
            }
        }
    }
    MESSAGE("decoded ", words, " words, skipped ", skipped_data, " data words, ", outside_scope,
            " functions only in functions.json (not in the census scope)");
    CHECK_MESSAGE(unbacked == 0, "first address without file bytes: ", hex32(first_unbacked));
    CHECK_MESSAGE(counts[0] == 0, "first Invalid word at ", hex32(first_invalid));
    CHECK(words == expected_words);
    CHECK(skipped_data == expected_data_items);

    // Exact per-mnemonic equality, reported with the first VA of each mismatching mnemonic.
    std::size_t mismatches = 0;
    for (int i = 1; i < static_cast<int>(Op::Count); ++i) {
        const Op op = static_cast<Op>(i);
        const std::string mn = mnemonic(op);
        const auto it = expected.find(mn);
        const std::uint64_t want = it == expected.end() ? 0 : it->second;
        if (counts[static_cast<std::size_t>(op)] == want) continue;
        ++mismatches;
        std::uint32_t first = 0;
        for (const Function& f : fl.functions) {
            for (const Range& r : f.chunks) {
                for (std::uint32_t va = r.start; va + 4 <= r.end && !first; va += 4) {
                    if (f.is_data(va)) continue;
                    const auto w = elf.word_at(va);
                    if (w && decode_op(*w) == op) first = va;
                }
                if (first) break;
            }
            if (first) break;
        }
        MESSAGE("MISMATCH ", mn, ": ours ", counts[static_cast<std::size_t>(op)], " census ", want,
                " (first VA ", hex32(first), ")");
    }
    CHECK(mismatches == 0);
}
