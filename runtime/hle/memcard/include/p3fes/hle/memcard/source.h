// Where the card in MEMORY CARD slot 1 comes from (the host's `--memcard` option).
//
//   ""  / "pcsx2"  the card PCSX2 uses in slot 1, found through PCSX2.ini ([Folders] MemoryCards,
//                  [MemoryCards] Slot1_Enable / Slot1_Filename; tools/third_party/pcsx2/inis/PCSX2.ini by
//                  default, docs/PCSX2.md) -- the user's data, opened READ-ONLY, copy-on-write
//   PATH           a raw 8 MiB card image (8,650,752 bytes: 16,384 x 528). A file outside `cow_dir` is
//                  opened read-only, copy-on-write; a file inside `cow_dir` is our own and written in place
//   "new"          a card formatted in memory by our formatter (fs.h); nothing is written to disk
//   "blank"        an erased (unformatted) card in memory
//   "none"         no card in slot 1
//
// Copy-on-write: the source file is only ever opened for reading. The first change is written as a full
// copy to `cow_dir/<source file name>` (default extracted/_ours/memcards/, gitignored), later changes as the
// modified pages only, whenever Card::flush runs (the DBCMAN server flushes after every command that
// programmed or erased). If that copy already exists it is the card (an earlier run's saves win over the
// PCSX2 file); delete it to start from the PCSX2 card again. PCSX2 folder cards and other sizes fail.
#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "p3fes/hle/memcard/card.h"
#include "p3fes/hle/memcard/fs.h"

namespace p3fes::hle::memcard {

struct SourceOptions {
    std::filesystem::path pcsx2_ini = "tools/third_party/pcsx2/inis/PCSX2.ini";
    std::filesystem::path cow_dir = "extracted/_ours/memcards";
    DateTime format_time{};  // root-entry stamp for "new"
};

struct OpenResult {
    bool ok = false;
    std::shared_ptr<Card> card;  // nullptr with ok == true: "none"
    std::string error;           // !ok
    std::string description;     // what was opened, for the host log
};

OpenResult open_memcard(std::string_view spec, const SourceOptions& opt = {});

// PCSX2's slot-1 card file from its ini; nullopt + `why` when disabled, missing or not a regular file.
std::optional<std::filesystem::path> pcsx2_slot1_card(const std::filesystem::path& ini, std::string* why = nullptr);

// Opens `source` read-only with copy-on-write into `cow_dir` (see above).
OpenResult open_copy_on_write(const std::filesystem::path& source, const std::filesystem::path& cow_dir);

// Opens one of our own images read-write in place.
OpenResult open_in_place(const std::filesystem::path& file);

// The port's own persistent card: opens `file` in place, creating it as a freshly formatted image
// (directories included) when it does not exist. The host uses it for %APPDATA%\P3FES\saves\Mcd001.ps2
// when no explicit --memcard and no PCSX2 card is available (GOAL.md Phase 3: saves in %APPDATA%).
OpenResult open_or_create(const std::filesystem::path& file, const DateTime& format_time = {});

}  // namespace p3fes::hle::memcard
