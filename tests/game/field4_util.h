// Shared helpers of the field4 pair tests (test_field4_root / _dungeon / _event / _npc.cpp): guest reads and writes on
// a machine, the replay snapshots as machines, the extracted data files, and the HwCheck of a whole-RAM stand-in pair.
#pragma once

#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/field4.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace p3fes::game_test::f4t {

inline u8 r8(Machine& m, u32 va) { return *m.at(va); }
inline s8 rs8(Machine& m, u32 va) { return static_cast<s8>(*m.at(va)); }
inline u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
inline s16 rs16(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
inline u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
inline s32 rs32(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
inline f32 rf32(Machine& m, u32 va) { f32 v; std::memcpy(&v, m.at(va), 4); return v; }
inline void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
inline void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
inline void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
inline void wf32(Machine& m, u32 va, f32 v) { std::memcpy(m.at(va), &v, 4); }
constexpr u64 S(s64 v) { return static_cast<u64>(v); }
// $v0 of a run as the callers read it: the low 32 bits, signed.
inline s64 v0_of(const hgp::Run& r) { return static_cast<s32>(static_cast<u32>(r.end.gpr[GPR_V0].u64[0])); }
inline s64 v0_of(const HwPair& p) { return static_cast<s32>(static_cast<u32>(p.recomp.base.v0)); }

constexpr u32 kSField = game::f4::kSField;
constexpr u32 kSceneRecord = 0x95AFC0u;   // MT_Scene's record (*(gp-0x57B0))
constexpr u32 kGp = 0x7D2CF0u;
constexpr u32 gpv(s32 off) { return kGp + static_cast<u32>(off); }
// Free in every replay snapshot used here (zero from 0x1BC0000 to the stand-in heap at 0x1C00000).
constexpr u32 kScratch = 0x01BC0000u;

// One snapshot as a machine (nullptr when the ELF or the snapshot is absent); `base` keeps the 32 MiB for resets.
inline std::unique_ptr<Machine> real_machine(const char* snapshot, std::vector<u8>& base) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    base = read_snapshot(snapshot);
    if (base.size() != EEMemory::kMainRamSize) return nullptr;
    std::memcpy(m->mem.main_ram(), base.data(), base.size());
    return m;
}
inline void reset(Machine& m, const std::vector<u8>& base) { std::memcpy(m.mem.main_ram(), base.data(), base.size()); }

// A file of the extracted tree (DATA/FIELD/...), empty when absent.
inline std::vector<u8> read_extracted(const std::string& rel) {
    std::ifstream f(extracted_root() + "/" + rel, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}
inline bool guest_equals(Machine& m, u32 va, const std::vector<u8>& bytes) {
    return !bytes.empty() && std::memcmp(m.at(va), bytes.data(), bytes.size()) == 0;
}

// The pair check of the stand-in runs: the whole RAM (write-tracked), every GPR at every check point, the dead stack.
inline HwCheck whole_ram_check() {
    HwCheck hw;
    hw.ranges = {{0u, EEMemory::kMainRamSize}};
    hw.gpr_mask = kAllGprs;
    hw.compare_hilo = true;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    return hw;
}

// H_Cdvd_FileExists on the stand-ins' file layer (FakeCd: the extracted tree): logs the path, 1 when the file is there.
inline void install_file_exists(StandInWorld& w) {
    FakeCd* cd = &w.cd;
    w.si.install(kHCdvdFileExistsFn, "H_Cdvd_FileExists", [cd](EEContext& ctx, StandIns&, StandInCall& c) {
        std::string s;
        for (u32 i = 0; i < 1024; ++i) {
            const char ch = static_cast<char>(ctx.memory->read<u8>(static_cast<u32>(c.args[0]) + i));
            if (ch == 0) break;
            s.push_back(ch);
        }
        c.text = s;
        c.v0 = cd->host_path(s).empty() ? 0 : 1;
    });
}
// The standard world (heap, printf / sprintf, the file layer) plus FileExists.
inline void install_field_world(StandInWorld& w) {
    install_standard(w);
    install_file_exists(w);
}

// A stand-in pair that also stands in every callee this build did not emit (a recorder returning `v0`, named
// "absent"): it runs the pair, and on a missing-function stop adds that address and runs it again from `base`
// (at most 24 times). `prepare` re-applies the test's edits after each reset. The absent callees are reported.
inline SiPair run_pair_si_absent(Machine& m, const std::vector<u8>& base, Fn hand, Fn recomp, const Args& args, u32 seed,
                                 const char* what, const HwCheck& hw, const std::function<void(Machine&)>& prepare,
                                 std::vector<u32>& absent, u64 v0 = 0) {
    for (int tries = 0;; ++tries) {
        reset(m, base);
        prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, hand, recomp, args, seed, what, hw, [list, v0](StandInWorld& w) {
                install_field_world(w);
                for (u32 va : list) w.si.install_recorder(va, "absent", v0);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 24) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}

// A finished H_Cdvd node in guest memory (the retail layout, game/include/p3fes/game/hcdvd.h: +12 state 4 = loaded,
// +272 the data, +280 its size) holding `bytes` at `data`: what the K_Fldrc "try load" functions consume.
inline void make_loaded_node(Machine& m, u32 node, u32 data, const std::vector<u8>& bytes) {
    std::memset(m.at(node), 0, 868);
    w32(m, node + 12, 4);
    w32(m, node + 272, data);
    w32(m, node + 280, static_cast<u32>(bytes.size()));
    std::memcpy(m.at(data), bytes.data(), bytes.size());
}

}  // namespace p3fes::game_test::f4t
