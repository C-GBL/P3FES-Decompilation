// Phase 5 slice gamedata: the game-state data layer of g_data.c (0x5E3098) and datPersona.c (0x5E3278) in the low band
// 0x16C470-0x1761B0 -- the state a future authoritative server owns: the party member records, the hero's persona
// stock, the equipment entries and item counts, money and the party list, the social links and the day-event
// records. The bodies (game/src/data/gamedata.cpp) are p3fes_handgen's: register for register and block for block as
// the recompiled bodies (frame, spills, $ra links, cycle charges, check points); their roles, the record offsets and
// the branch meanings are named on top (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
//
// Names: the functions keep their symbols/functions.json names (sub_XXXXXX); a proposed name is given in brackets in
// the comments (ADR-0009: from the instructions, the callers and the snapshots; not imported). Field names below are
// from this slice's own evidence; tools/ours/types/deltas/gamedata.json feeds them to type recovery.
//
// ---------------------------------------------------------------------------------------------------------------
// The state (all in the ELF's .bss; read from the instructions, checked on dorm_replay_4900, climb_ref_17000,
// fusion_vr_5000 and shop_ref_4100):
//
//   gGlobalWork 0x836200 (calendar.h's proposed layout; the offsets this slice touches):
//     +0x20   the hero's party record head (the layout of PartyRecord below up to +0x54): +0x24 DatUnit,
//             +0x60 s16 social stats[3], +0x68 s32 exp, +0x6C u16 condition, +0x6E / +0x70 u16
//     +0x74   the social-link block, 1,288 bytes (sub_16DB70 clears it): +0x74 s16 (sub_16DD40 / sub_16E920),
//             +0x76 s8 rank[30], +0x94 s32 points[30], +0x10C s8 comu_b[30] (0..9), +0x12A s16 day[30] (0..360),
//             +0x166 s16 comu_c[30] (sub_3BDDD0's initial values, counted down), +0x1A2 s16 day2[30] (a day stamp),
//             +0x1DE s16 comu_e[30] (counted up to 32), +0x21A u16 comu_f[30]
//     +0x258  day-event record A, 56 bytes (flag 0x980 = set): +8 u8, +0x10 s32 (sub_172A20), +0x24 u8 (0xFF none)
//     +0x290  u8 / +0x292 s16 / +0x294 s16 day stamp (sub_172AB0)
//     +0x298  36 bytes cleared on the date change (sub_172E10)
//     +0x2BC  day-event record B, 56 bytes (flag 0x983 = set); +0 u8 its comu id
//     +0x534  u8 comu month[30], +0x552 u8 comu day of month[30] (sub_172CC0: today's date per link)
//     +0x573  u8 counter8[8], capped at 200
//     +0x58C  s16 hero equipment index[4] (datGetEquipmentIdx / sub_16DA50)
//     +0x594  EquipEntry* the hero's equipment stock (300 entries), +0x598 u16* the hero's item counts, biased so
//             that item id 4000 is entry 0 (counts[id - 4000])
//     +0x59C  s16 days since Apr 5, +0x59E u8 time of day (ui2.h)
//     +0x9A8  s16 the hero's current persona slot, +0x9AC Persona stock[12] (624 bytes; the stock size 4..12 is
//             set by the flag bits of kPersonaStockFlags)
//     +0xC1C  13,312 bytes = 256 x 52: a Persona-sized record per persona id (sub_175C70 clears it)
//     +0x401C flag words, +0x42DC counters (ui2.h), +0x44DC s32 money (< 10,000,000), +0x44E0 s16 party[4]
//
//   Party records 0x834010 + 868 * (pc - 2), pc 2..10 (battle_data.h kPartyRecords; pc 1 is the hero, whose head
//   lives in gGlobalWork +0x20):
//     +0x04   DatUnit unit (60 bytes, battle.h: +0 flags, +2 id, +4 base_id, +6 level, +8 hp, +0xA sp,
//             +0xC status, +0x10 a byte 0..10, 1 on init)
//     +0x40   s16 social stats[3] (meaningful for the hero), +0x48 s32 exp (the hero's; a member's exp is its
//             persona's), +0x4C u16 condition (0..5), +0x4E u16, +0x50 u16 (copied to +0x4E when condition 3 ends)
//     +0x54   s16 equipment index[4] (into the owner's entries)
//     +0x5C   EquipEntry equipment[4] (owner = pc)
//     +0xAC   {u16, s16} pairs (sub_170670 / sub_1706C0)
//     +0xDC   Persona persona (datPersonaGetByPcId)
//     +0x180  EquipEntry equipment2[4] (owner = pc + 256)
//     +0x310  {u16 id, s16 count} pouch[20] (owner = pc + 256 in the item functions)
//   An "owner" in the equipment / item functions is -1 (the 20-entry table 0x833E80 and the count table 0x831CE0),
//   1 (the hero), 2..255 (a member's record) or 256 + pc (the second blocks of record pc).
//
//   EquipEntry (20 bytes): +0 u16 item id (0 = empty), +4 s32, +8 u8, +9 u8 effect, +0xA u16 power, +0xC u16
//   accuracy (the weapon's, datCalcGetWeaponParam), +0xE u16 evasion, +0x10 u16 defense (the armour's,
//   datCalcGetArmorParam).
//   Persona (52 bytes): +0 u16 flags (bit 0 used; bits 2 / 3 survive a refill), +2 u16 id (1..255; 0xC0..0xDF the
//   party members' personas), +4 u8 level (1..99), +8 s32 exp, +0xC u16 skills[8], +0x1C u8 base stats[5] (St Ma En
//   Ag Lu), +0x21 s8 bonus A[5], +0x26 s8 bonus B[5]; a stat is base + A + B (+ the equipment bonus, sub_173C60),
//   0..99.
//   Item ids: 1000-wide kinds -- < 1000 weapons, 1000.. armour, 2000.. accessories, 3000.., 4000.. consumables
//   (counted in the hero's table), 5000..5127 key items (a flag bit each: datSetFlag(id - 0x1188)).
//   Social links: comu ids 0..29; the arcana of each in the s8 table 0x5E3220; ranks 0..10 (0 = not started); the
//   per-rank flag rows 0x400 + 32 comu + rank - 1 ('ready') and 0x410 + 32 comu + rank - 1 ('seen'); the per-link
//   flags 0x900 / 0x920 / 0x940 + comu.
// ---------------------------------------------------------------------------------------------------------------
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

namespace gamedata {

// --- gGlobalWork --------------------------------------------------------------------------------------------------
inline constexpr u32 kGlobalWork = 0x836200u;
inline constexpr u32 kHeroUnit = 0x836224u;           // gGlobalWork +0x24: the hero's DatUnit
inline constexpr u32 kHeroExp = 0x836268u;            // +0x68 s32
inline constexpr u32 kHeroCondition = 0x83626Cu;      // +0x6C u16
inline constexpr u32 kComuBlock = 0x836274u;          // +0x74, kComuBlockSize bytes
inline constexpr u32 kComuBlockSize = 1288;
inline constexpr u32 kComuRank = 0x836276u;           // s8[30]
inline constexpr u32 kComuPoints = 0x836294u;         // s32[30]
inline constexpr u32 kComuB = 0x83630Cu;              // s8[30], 0..9
inline constexpr u32 kComuDay = 0x83632Au;            // s16[30], 0..360
inline constexpr u32 kComuC = 0x836366u;              // s16[30]
inline constexpr u32 kComuDay2 = 0x8363A2u;           // s16[30]
inline constexpr u32 kComuE = 0x8363DEu;              // s16[30], capped at 32
inline constexpr u32 kComuF = 0x83641Au;              // u16[30]
inline constexpr s32 kComuCount = 30;
inline constexpr s32 kComuMaxRank = 10;
inline constexpr u32 kEventA = 0x836458u;             // 56 bytes, flag kEventAFlag
inline constexpr u32 kEventB = 0x8364BCu;             // 56 bytes, flag kEventBFlag
inline constexpr u32 kEventSize = 56;
inline constexpr s32 kEventAFlag = 0x980, kEventBFlag = 0x983;
inline constexpr u32 kDateResetArray = 0x836498u;     // 36 bytes
inline constexpr u32 kComuMonth = 0x836734u;          // u8[30]
inline constexpr u32 kComuDayOfMonth = 0x836752u;     // u8[30]
inline constexpr u32 kCounter8 = 0x836773u;           // u8[8], capped at 200
inline constexpr u32 kHeroEquipment = 0x83678Cu;      // s16[4]
inline constexpr u32 kHeroEquipmentStock = 0x836794u; // EquipEntry* (300)
inline constexpr u32 kHeroItemNum = 0x836798u;        // u16* counts[id - 4000]
inline constexpr u32 kHeroPersonaIdx = 0x836BA8u;     // s16
inline constexpr u32 kHeroPersonaStock = 0x836BACu;   // Persona[12]
inline constexpr u32 kPersonaById = 0x836E1Cu;        // 256 x 52 bytes
inline constexpr u32 kMoney = 0x83A6DCu;              // s32
inline constexpr u32 kParty = 0x83A6E0u;              // s16[4]
inline constexpr u32 kPersonaStockFlags = 0x83A45Cu;  // flag word 144: bits 0, 1, 2, 12, 13 size the stock
inline constexpr s32 kMoneyLimit = 10000000;          // money < 10,000,000 (K_Assert line 1674)
inline constexpr s32 kMoneyMax = 9999999;
inline constexpr s32 kItemMax = 99;                   // an item count < 100 (K_Assert line 2341)

// --- party records ------------------------------------------------------------------------------------------------
inline constexpr u32 kPartyRecords = 0x834010u;       // pc 2's record; + 868 * (pc - 2)
inline constexpr u32 kPartyRecordSize = 868;
inline constexpr s32 kHeroPc = 1;
inline constexpr u32 kTempEquipment = 0x833E80u;      // owner -1: EquipEntry[20]
inline constexpr u32 kTempItemNum = 0x831CE0u;        // owner -1: u16 counts[id]
inline constexpr u32 kHeroExpTable = 0x5DC050u;       // s32[99]
inline constexpr u32 kComuArcana = 0x5E3220u;         // s8[30]
inline constexpr u32 kPersonaTable = 0x7CE420u;       // $gp slot: the 14-byte persona records (+2 u8 arcana)

#pragma pack(push, 1)
// DatUnit is battle.h's; the party record and the two records the functions index (host-side views for tests and
// documentation: guest pointers are u32).
struct EquipEntry {
    u16 item_id;   // +0x00, 0 = empty
    u16 pad02;
    s32 unk04;     // +0x04 (sub_16F720 / sub_16FF90)
    u8 unk08;      // +0x08 (sub_16F810 / sub_170080)
    u8 effect;     // +0x09 (sub_16F900 / sub_170170)
    u16 power;     // +0x0A weapon (sub_16F9F0 / sub_170260)
    u16 accuracy;  // +0x0C weapon (sub_16FAE0 / sub_170350)
    u16 evasion;   // +0x0E armour (sub_16FBD0 / sub_170440)
    u16 defense;   // +0x10 armour (sub_16FCC0 / sub_170530)
    u16 pad12;
};
static_assert(sizeof(EquipEntry) == 20 && offsetof(EquipEntry, effect) == 9 && offsetof(EquipEntry, defense) == 0x10);

struct Persona {
    u16 flags;          // +0x00 bit 0 = used
    u16 id;             // +0x02
    u8 level;           // +0x04
    u8 pad05[3];
    s32 exp;            // +0x08
    u16 skills[8];      // +0x0C
    u8 base_stats[5];   // +0x1C
    s8 bonus_a[5];      // +0x21
    s8 bonus_b[5];      // +0x26
    u8 pad2b[9];
};
static_assert(sizeof(Persona) == 52 && offsetof(Persona, exp) == 8 && offsetof(Persona, base_stats) == 0x1C &&
              offsetof(Persona, bonus_a) == 0x21 && offsetof(Persona, bonus_b) == 0x26);

struct PouchEntry {
    u16 id;
    s16 count;
};

struct PartyRecord {
    u32 unk00;                 // +0x000
    u8 unit[60];               // +0x004 DatUnit
    s16 stats[3];              // +0x040
    u16 pad46;
    s32 exp;                   // +0x048
    u16 condition;             // +0x04C
    u16 unk4E;                 // +0x04E
    u16 unk50;                 // +0x050
    u16 pad52;
    s16 equipment_idx[4];      // +0x054
    EquipEntry equipment[4];   // +0x05C
    u8 pairs[0x30];            // +0x0AC {u16, s16}
    Persona persona;           // +0x0DC
    u8 gap110[0x70];
    EquipEntry equipment2[4];  // +0x180
    u8 gap1d0[0x140];
    PouchEntry pouch[20];      // +0x310
    u8 gap360[4];
};
static_assert(sizeof(PartyRecord) == 868 && offsetof(PartyRecord, unit) == 4 && offsetof(PartyRecord, condition) == 0x4C &&
              offsetof(PartyRecord, equipment_idx) == 0x54 && offsetof(PartyRecord, equipment) == 0x5C &&
              offsetof(PartyRecord, pairs) == 0xAC && offsetof(PartyRecord, persona) == 0xDC &&
              offsetof(PartyRecord, equipment2) == 0x180 && offsetof(PartyRecord, pouch) == 0x310);
#pragma pack(pop)

// The guest address of member pc's record (pc 2..10; the arithmetic also covers the -1 / 256 + pc owners' tables
// the way the bodies index them).
constexpr u32 party_record(s32 pc) { return kPartyRecords + kPartyRecordSize * static_cast<u32>(pc - 2); }

// Persona field offsets (the bodies' loads and stores on a persona pointer)
namespace persona {
inline constexpr s32 kFlags = 0x00, kId = 0x02, kLevel = 0x04, kExp = 0x08, kSkills = 0x0C, kBaseStats = 0x1C,
                     kBonusA = 0x21, kBonusB = 0x26;
inline constexpr s32 kUpLevels = 0, kUpStats = 34;  // the level-up record (40 bytes, sub_175CE0 / sub_176100)
}  // namespace persona

}  // namespace gamedata

// --- the register-ABI bodies (arguments in $a0.., the result in $v0; game/src/data/gamedata.cpp) ---------------
// Each: its address, (arguments) and [the proposed name]; the role is in the .cpp.
void sub_16C470(EEContext& ctx);  // 0x16C470 (pc) [datGetPcLevel]
void sub_16C4F0(EEContext& ctx);  // 0x16C4F0 (pc) [datGetPcHp]
void sub_16C570(EEContext& ctx);  // 0x16C570 (pc) [datGetPcSp]
void sub_16C5F0(EEContext& ctx);  // 0x16C5F0 (pc) [datGetPcMaxHp]
void sub_16C670(EEContext& ctx);  // 0x16C670 (pc) [datGetPcMaxSp]
void sub_16C7E0(EEContext& ctx);  // 0x16C7E0 (pc) [datGetPcExp]
void sub_16C860(EEContext& ctx);  // 0x16C860 (pc) [datGetPcPersonaId]
void sub_16C910(EEContext& ctx);  // 0x16C910 () [datGetHeroPersonaIdx]
void sub_16C920(EEContext& ctx);  // 0x16C920 (pc) [datGetPcCondition]
void sub_16C970(EEContext& ctx);  // 0x16C970 (pc) [datGetPcBadStatus]
void sub_16C9F0(EEContext& ctx);  // 0x16C9F0 (pc)
void sub_16CA40(EEContext& ctx);  // 0x16CA40 (pc)
void sub_16CA90(EEContext& ctx);  // 0x16CA90 (pc)
void sub_16CDF0(EEContext& ctx);  // 0x16CDF0 (pc) [datInitPcUnit]
void sub_16CEF0(EEContext& ctx);  // 0x16CEF0 (pc, level) [datSetHeroLevel]
void sub_16CF40(EEContext& ctx);  // 0x16CF40 (pc, value) [datSetPcHp]
void sub_16CF90(EEContext& ctx);  // 0x16CF90 (pc, value) [datSetPcSp]
void sub_16D230(EEContext& ctx);  // 0x16D230 (pc, value) [datSetHeroExp]
void sub_16D280(EEContext& ctx);  // 0x16D280 (exp) [datGetLevelForExp]
void sub_16D560(EEContext& ctx);  // 0x16D560 (pc, exp) [datAddHeroExp]
void sub_16D6B0(EEContext& ctx);  // 0x16D6B0 (pc, condition) [datSetPcCondition]
void sub_16D8B0(EEContext& ctx);  // 0x16D8B0 (pc) [datSetPcBadStatus]
void sub_16D930(EEContext& ctx);  // 0x16D930 (pc, value)
void sub_16D980(EEContext& ctx);  // 0x16D980 (pc, value)
void sub_16D9D0(EEContext& ctx);  // 0x16D9D0 (pc) [datClearPcBadStatus]
void sub_16DA50(EEContext& ctx);  // 0x16DA50 (pc, slot, value) [datSetEquipmentIdx]
void sub_16DAD0(EEContext& ctx);  // 0x16DAD0 (pc, value)
void sub_16DD80(EEContext& ctx);  // 0x16DD80 (pc)
void sub_16DB70(EEContext& ctx);  // 0x16DB70 () [datComuClearAll]
void sub_16DBA0(EEContext& ctx);  // 0x16DBA0 (comu) [datComuGetRank]
void sub_16DCE0(EEContext& ctx);  // 0x16DCE0 (comu) [datComuIsValidId]
void sub_16DD20(EEContext& ctx);  // 0x16DD20 (comu)
void sub_16DD40(EEContext& ctx);  // 0x16DD40 ()
void sub_16DEB0(EEContext& ctx);  // 0x16DEB0 (arcana) [datComuFindByArcana]
void sub_16DF30(EEContext& ctx);  // 0x16DF30 (comu) [datComuGetArcana]
void sub_16DFB0(EEContext& ctx);  // 0x16DFB0 (comu) [datComuStart]
void sub_16E100(EEContext& ctx);  // 0x16E100 (comu) [datComuIsActive]
void sub_16E2B0(EEContext& ctx);  // 0x16E2B0 (comu, points) [datComuAddPoints]
void sub_16E410(EEContext& ctx);  // 0x16E410 (comu, rank) [datComuSetRank]
void sub_16E5F0(EEContext& ctx);  // 0x16E5F0 (comu, value)
void sub_16E670(EEContext& ctx);  // 0x16E670 (comu)
void sub_16E7A0(EEContext& ctx);  // 0x16E7A0 (comu, value)
void sub_16E850(EEContext& ctx);  // 0x16E850 (comu) [datComuDaysSince]
void sub_16E920(EEContext& ctx);  // 0x16E920 (value)
void sub_1717B0(EEContext& ctx);  // 0x1717B0 () [datComuGetBlock]
void sub_1717C0(EEContext& ctx);  // 0x1717C0 (comu)
void sub_1718B0(EEContext& ctx);  // 0x1718B0 (comu)
void sub_171960(EEContext& ctx);  // 0x171960 (comu, value)
void sub_171AC0(EEContext& ctx);  // 0x171AC0 (comu)
void sub_171B50(EEContext& ctx);  // 0x171B50 (comu)
void sub_171C40(EEContext& ctx);  // 0x171C40 (comu, on)
void sub_171E90(EEContext& ctx);  // 0x171E90 (comu, value)
void sub_171F50(EEContext& ctx);  // 0x171F50 (comu, on)
void sub_1720C0(EEContext& ctx);  // 0x1720C0 (comu, out)
void sub_172160(EEContext& ctx);  // 0x172160 (comu)
void sub_172200(EEContext& ctx);  // 0x172200 (comu, on)
void sub_1723A0(EEContext& ctx);  // 0x1723A0 (comu, rank, on) [datComuSetRankReady]
void sub_1724A0(EEContext& ctx);  // 0x1724A0 (comu, rank, on) [datComuSetRankSeen]
void sub_1725A0(EEContext& ctx);  // 0x1725A0 (comu) [datComuRankUp]
void sub_172660(EEContext& ctx);  // 0x172660 (comu) [datComuHasPendingRank]
void sub_16DD50(EEContext& ctx);  // 0x16DD50 () [datGetMoney]
void sub_16DD60(EEContext& ctx);  // 0x16DD60 (i) [datGetPartyMember]
void sub_16E930(EEContext& ctx);  // 0x16E930 (value) [datSetMoney]
void sub_16E990(EEContext& ctx);  // 0x16E990 (i, pc) [datSetPartyMember]
void sub_16E9B0(EEContext& ctx);  // 0x16E9B0 (delta) [datAddMoney]
void sub_16EA40(EEContext& ctx);  // 0x16EA40 (delta) [datCheckMoneyDelta]
void sub_16DDD0(EEContext& ctx);  // 0x16DDD0 (i)
void sub_16DE50(EEContext& ctx);  // 0x16DE50 (i)
void sub_16F490(EEContext& ctx);  // 0x16F490 (owner) [datCountEquipmentEntries]
void sub_16F720(EEContext& ctx);  // 0x16F720 (owner, idx)
void sub_16F810(EEContext& ctx);  // 0x16F810 (owner, idx)
void sub_16F9F0(EEContext& ctx);  // 0x16F9F0 (owner, idx) [datGetEquipmentPower]
void sub_16FAE0(EEContext& ctx);  // 0x16FAE0 (owner, idx) [datGetEquipmentAccuracy]
void sub_16FBD0(EEContext& ctx);  // 0x16FBD0 (owner, idx) [datGetEquipmentEvasion]
void sub_16FCC0(EEContext& ctx);  // 0x16FCC0 (owner, idx) [datGetEquipmentDefense]
void sub_16FDB0(EEContext& ctx);  // 0x16FDB0 (owner, idx) [datGetEquipmentEntry]
void sub_16FEA0(EEContext& ctx);  // 0x16FEA0 (owner, idx, value) [datSetEquipmentItemId]
void sub_16FF90(EEContext& ctx);  // 0x16FF90 (owner, idx, value)
void sub_170080(EEContext& ctx);  // 0x170080 (owner, idx, value)
void sub_170170(EEContext& ctx);  // 0x170170 (owner, idx, value) [datSetEquipmentEffect]
void sub_170260(EEContext& ctx);  // 0x170260 (owner, idx, value) [datSetEquipmentPower]
void sub_170350(EEContext& ctx);  // 0x170350 (owner, idx, value) [datSetEquipmentAccuracy]
void sub_170440(EEContext& ctx);  // 0x170440 (owner, idx, value) [datSetEquipmentEvasion]
void sub_170530(EEContext& ctx);  // 0x170530 (owner, idx, value) [datSetEquipmentDefense]
void sub_170620(EEContext& ctx);  // 0x170620 (pc, i)
void sub_170670(EEContext& ctx);  // 0x170670 (pc, i)
void sub_1706C0(EEContext& ctx);  // 0x1706C0 (pc, i)
void sub_170710(EEContext& ctx);  // 0x170710 (pc, i, value)
void sub_170A40(EEContext& ctx);  // 0x170A40 (pc, i) [datGetPouchItemId]
void sub_170AB0(EEContext& ctx);  // 0x170AB0 (pc, i) [datGetPouchItemNum]
void sub_170B20(EEContext& ctx);  // 0x170B20 (pc, i, value) [datSetPouchItemId]
void sub_170B90(EEContext& ctx);  // 0x170B90 (pc, i, value) [datSetPouchItemNum]
void sub_170760(EEContext& ctx);  // 0x170760 (owner, id) [datGetItemNum]
void sub_170860(EEContext& ctx);  // 0x170860 (owner, id, count) [datSetItemNum]
void sub_170C00(EEContext& ctx);  // 0x170C00 (owner, id, delta) [datAddItemNum]
void sub_171060(EEContext& ctx);  // 0x171060 (id) [datItemLocalIndex]
void sub_171110(EEContext& ctx);  // 0x171110 (id, column) [datGetItemName]
void sub_171250(EEContext& ctx);  // 0x171250 (id) [datGetItemKind]
void sub_171360(EEContext& ctx);  // 0x171360 (id) [datIsKeyItem]
void sub_171390(EEContext& ctx);  // 0x171390 (id) [datSetKeyItemFlag]
void sub_172820(EEContext& ctx);  // 0x172820 (value)
void sub_172890(EEContext& ctx);  // 0x172890 () [datEventAClear]
void sub_1728D0(EEContext& ctx);  // 0x1728D0 (src) [datEventASet]
void sub_172990(EEContext& ctx);  // 0x172990 () [datEventAGet]
void sub_1729A0(EEContext& ctx);  // 0x1729A0 () [datEventAIsSet]
void sub_1729D0(EEContext& ctx);  // 0x1729D0 (out)
void sub_172A10(EEContext& ctx);  // 0x172A10 ()
void sub_172A20(EEContext& ctx);  // 0x172A20 (value)
void sub_172A30(EEContext& ctx);  // 0x172A30 ()
void sub_172AB0(EEContext& ctx);  // 0x172AB0 (value)
void sub_172AE0(EEContext& ctx);  // 0x172AE0 () [datEventBClear]
void sub_172B20(EEContext& ctx);  // 0x172B20 ()
void sub_172C50(EEContext& ctx);  // 0x172C50 (out) [datEventBGet]
void sub_172CC0(EEContext& ctx);  // 0x172CC0 (comu) [datComuSetDate]
void sub_172D70(EEContext& ctx);  // 0x172D70 (out) [datComuListToday]
void sub_172E10(EEContext& ctx);  // 0x172E10 ()
void sub_172E40(EEContext& ctx);  // 0x172E40 ()
void sub_173280(EEContext& ctx);  // 0x173280 (id) [datPersonaGetArcana]
void sub_173300(EEContext& ctx);  // 0x173300 (pc) [datPersonaGetLevelByPcId]
void sub_173330(EEContext& ctx);  // 0x173330 (persona) [datPersonaGetExp]
void sub_173340(EEContext& ctx);  // 0x173340 (persona, level)
void sub_173370(EEContext& ctx);  // 0x173370 (persona) [datPersonaGetSkills]
void sub_173580(EEContext& ctx);  // 0x173580 (persona, stat)
void sub_173660(EEContext& ctx);  // 0x173660 (persona, stat) [datPersonaGetTotalStat]
void sub_173780(EEContext& ctx);  // 0x173780 (slot, stat)
void sub_173A00(EEContext& ctx);  // 0x173A00 (persona, stat)
void sub_173B00(EEContext& ctx);  // 0x173B00 (persona, stat) [datPersonaGetBonusA]
void sub_173B60(EEContext& ctx);  // 0x173B60 (pc, stat, value) [datPersonaSetBonusAByPcId]
void sub_173BB0(EEContext& ctx);  // 0x173BB0 (pc, stat, value) [datPersonaAddBonusAByPcId]
void sub_173C00(EEContext& ctx);  // 0x173C00 (persona, stat) [datPersonaGetBonusB]
void sub_174650(EEContext& ctx);  // 0x174650 (persona, stat, delta) [datPersonaAddBaseStat]
void sub_174710(EEContext& ctx);  // 0x174710 (slot, stat, delta)
void sub_1748C0(EEContext& ctx);  // 0x1748C0 () [datPersonaFindFreeSlot]
void sub_174960(EEContext& ctx);  // 0x174960 (slot) [datPersonaIsSlotUsed]
void sub_1749A0(EEContext& ctx);  // 0x1749A0 (id) [datPersonaFindById]
void sub_174B40(EEContext& ctx);  // 0x174B40 (id) [datPersonaRemoveById]
void sub_174E20(EEContext& ctx);  // 0x174E20 (id) [datPersonaAddChecked]
void sub_174E70(EEContext& ctx);  // 0x174E70 (id) [datPersonaAdd]
void sub_174FB0(EEContext& ctx);  // 0x174FB0 (src) [datPersonaAddCopy]
void sub_175130(EEContext& ctx);  // 0x175130 (id) [datPersonaSelectById]
void sub_175200(EEContext& ctx);  // 0x175200 (slot) [datPersonaSelectSlot]
void sub_1752B0(EEContext& ctx);  // 0x1752B0 () [datPersonaGetCurrentId]
void sub_175360(EEContext& ctx);  // 0x175360 () [datPersonaGetCurrentSlot]
void sub_1754A0(EEContext& ctx);  // 0x1754A0 (level) [datPersonaSetStockLevel]
void sub_1755C0(EEContext& ctx);  // 0x1755C0 () [datPersonaGetStockLevel]
void sub_1756F0(EEContext& ctx);  // 0x1756F0 () [datPersonaCountStock]
void sub_1757F0(EEContext& ctx);  // 0x1757F0 () [datPersonaClearStock]
void sub_175BE0(EEContext& ctx);  // 0x175BE0 (pc) [datPersonaClearPc]
void sub_175C70(EEContext& ctx);  // 0x175C70 ()
void sub_175CA0(EEContext& ctx);  // 0x175CA0 (persona) [datPersonaIsPartyPersona]
void sub_176100(EEContext& ctx);  // 0x176100 (persona, up) [datPersonaApplyLevelUp]
void sub_1761B0(EEContext& ctx);  // 0x1761B0 (persona) [datPersonaCanLevelUp]

}  // namespace p3fes::game
