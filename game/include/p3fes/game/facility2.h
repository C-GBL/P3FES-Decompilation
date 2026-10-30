// Phase 5 slice facility2: the facility code, second pass (121 functions of 0x3D0000-0x40FFFF that the fusion, shops
// and fcl slices left; docs/ANALYSIS/27_unmapped_bands.md section 8). p3fes_handgen bodies made readable: a role comment
// with a bracketed proposed name on every function, block comments, and the records below as named offsets.
//
// What the steps are (the shop sequence's step descriptors 0x6A6FC0.. {init, fini, update, draw, payload size, name};
// shops.h has the sequence): ARMSCOMBINE (weapon fusion: a base item from the list of 0x6AF180 and a persona from the
// stock make an item, ready the next day -- the recipes below), TRADE (items for materials), QUEST / QUESTCANCEL
// (Elizabeth's requests), BOOK / BOOKREGIST (the persona compendium: summon / register), HELP, TALK, MONEY, SUBTITLE,
// BG. This slice has their finis and draws, the list builders and row drawers behind them, the quantity selector of
// BUY / SELL, and the helpers of the fusion list windows (0x3D3170 .. 0x3DCFB0).
//
// Rules the bodies implement (each checked on the host by tests/game/test_facility2.cpp):
//   * the compendium price of a registered persona: 3 s^2 + 2000 with s = St + Ma + En + Ag + Lu, x4 when game flag 4889
//     is set, capped at 9,999,999 (sub_409C80);
//   * the quantity selector: count in 1..max with max = min(99, yen / price, 99 - owned, the stock left) when buying,
//     max = the count owned when selling; the returned step is 1 up / 2 down / 0 unchanged (sub_3FB0C0 / 3FB2F0 /
//     3FB530);
//   * the sale: every row's price x 0.75, x 0.7 with flag 4, x 0.5 with flag 8, never below 1 (sub_3F2320);
//   * the lineup price: the item price x the entry rate (or the lineup's) / 100 (sub_3F25E0);
//   * the weapon-fusion recipe: a fixed table {persona -> item} first; else the base item's group (itself when it is one
//     of 0x6AF180's eight, else table 0x6ACCE0) and the first recipe of 0x6ACE30 for that group whose stat mask meets the
//     persona's best-stat mask (sub_4016D0: the highest of St Ma En Ag Lu as bits 1..16; a tie only between St and Ma
//     keeps both) (sub_401A00 / sub_401DE0);
//   * a request's deadline: 3 none, 2 due today, 1 before, 0 past (sub_403410);
//   * the compendium sorts: by level, then arcana, then id; or by arcana, then level, then id (sub_40A5B0 / sub_40A640).
//
// Kept recompiled in the bands: the functions other slices' tests stand in with recorders (test_fusion, test_shops,
// test_savedata, test_fcl, test_ui6: sub_3D06D0, sub_3D1DF0, sub_3D2200, sub_3D32E0, sub_3D3620, sub_3D38B0,
// sub_3D8850, sub_3DB650, sub_3DD260, sub_3E0A10, sub_3E0C20, sub_3E6130 ... sub_40D640, sub_40E360, and the request
// accessors sub_403800 / sub_403830 / sub_403880 / sub_403900 -- 92 in all) and the 84 whose callees are such
// functions, the frFont drawers (font2), the RW random sub_488F30 or ui4's sprite handles.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// The bodies (register ABI: arguments in $a0.., the result in $v0; proposed names in brackets).
void sub_3D3170(EEContext& ctx);  // 0x3D3170 [fclCombineListCancel]
void sub_3D3760(EEContext& ctx);  // 0x3D3760 [fclCombineListPanelAnim]
void sub_3D9820(EEContext& ctx);  // 0x3D9820 [fclListPanelPartAnim]
void sub_3DCA10(EEContext& ctx);  // 0x3DCA10 [fclCombineDrawStockSlots]
void sub_3DCFB0(EEContext& ctx);  // 0x3DCFB0 [fclCombineDrawRowIcons]
void sub_3E0940(EEContext& ctx);  // 0x3E0940 [fclShopGetSequence]
void sub_3E6E20(EEContext& ctx);  // 0x3E6E20 [fclShopTestFlags]
void sub_3EAEB0(EEContext& ctx);  // 0x3EAEB0 [fclShopArmsCombineInit]
void sub_3EAF30(EEContext& ctx);  // 0x3EAF30 [fclShopArmsCombineFini]
void sub_3EB940(EEContext& ctx);  // 0x3EB940 [fclShopArmsCombineDraw]
void sub_3EBB90(EEContext& ctx);  // 0x3EBB90 [fclShopTradeInit]
void sub_3EBC70(EEContext& ctx);  // 0x3EBC70 [fclShopTradeFini]
void sub_3EBFE0(EEContext& ctx);  // 0x3EBFE0 [fclShopTradeDraw]
void sub_3EC280(EEContext& ctx);  // 0x3EC280 [fclShopQuestFini]
void sub_3EC6A0(EEContext& ctx);  // 0x3EC6A0 [fclShopQuestDraw]
void sub_3EC8E0(EEContext& ctx);  // 0x3EC8E0 [fclShopQuestCancelFini]
void sub_3ECCE0(EEContext& ctx);  // 0x3ECCE0 [fclShopQuestCancelDraw]
void sub_3ECF80(EEContext& ctx);  // 0x3ECF80 [fclShopBookFini]
void sub_3ED310(EEContext& ctx);  // 0x3ED310 [fclShopBookDraw]
void sub_3ED5A0(EEContext& ctx);  // 0x3ED5A0 [fclShopBookRegistFini]
void sub_3EDD80(EEContext& ctx);  // 0x3EDD80 [fclShopBookRegistDraw]
void sub_3EE4E0(EEContext& ctx);  // 0x3EE4E0 [fclShopTalkFini]
void sub_3EE640(EEContext& ctx);  // 0x3EE640 [fclShopMoneyFini]
void sub_3EEE50(EEContext& ctx);  // 0x3EEE50 [fclShopSubtitleFini]
void sub_3EFC20(EEContext& ctx);  // 0x3EFC20 [fclShopBgFini]
void sub_3F1910(EEContext& ctx);  // 0x3F1910 [fclShopCountOwned]
void sub_3F1BA0(EEContext& ctx);  // 0x3F1BA0 [fclShopMakeItemEntry]
void sub_3F2320(EEContext& ctx);  // 0x3F2320 [fclShopApplySale]
void sub_3F25E0(EEContext& ctx);  // 0x3F25E0 [fclShopFillLineup]
void sub_3F3E60(EEContext& ctx);  // 0x3F3E60 [fclShopRemoveListed]
void sub_3F4A90(EEContext& ctx);  // 0x3F4A90 [fclShopDrawListHeader]
void sub_3F5AB0(EEContext& ctx);  // 0x3F5AB0 [fclShopDrawUserColumnsA]
void sub_3F5D10(EEContext& ctx);  // 0x3F5D10 [fclShopDrawUserColumnsB]
void sub_3F5F50(EEContext& ctx);  // 0x3F5F50 [fclShopDrawUserColumnsC]
void sub_3F61D0(EEContext& ctx);  // 0x3F61D0 [fclShopDrawCompareA]
void sub_3F67E0(EEContext& ctx);  // 0x3F67E0 [fclShopDrawCompareB]
void sub_3F6F20(EEContext& ctx);  // 0x3F6F20 [fclShopDrawCompareC]
void sub_3F7890(EEContext& ctx);  // 0x3F7890 [fclShopDrawOwnedCount]
void sub_3F9510(EEContext& ctx);  // 0x3F9510 [fclShopDrawListRow]
void sub_3FA210(EEContext& ctx);  // 0x3FA210 [fclShopListWindowAnimA]
void sub_3FA520(EEContext& ctx);  // 0x3FA520 [fclShopListWindowAnimB]
void sub_3FA800(EEContext& ctx);  // 0x3FA800 [fclShopListWindowAnimC]
void sub_3FAAE0(EEContext& ctx);  // 0x3FAAE0 [fclShopListWindowAnimD]
void sub_3FADC0(EEContext& ctx);  // 0x3FADC0 [fclShopListWindowAnimE]
void sub_3FB0C0(EEContext& ctx);  // 0x3FB0C0 [fclShopQtyOpen]
void sub_3FB2F0(EEContext& ctx);  // 0x3FB2F0 [fclShopQtyStepBuy]
void sub_3FB530(EEContext& ctx);  // 0x3FB530 [fclShopQtyStepSell]
void sub_3FBF10(EEContext& ctx);  // 0x3FBF10 [fclShopSetWord3]
void sub_3FCA00(EEContext& ctx);  // 0x3FCA00 [fclShopDrawFrameSprites]
void sub_3FCBE0(EEContext& ctx);  // 0x3FCBE0 [fclShopDrawCategoryRowA]
void sub_3FD140(EEContext& ctx);  // 0x3FD140 [fclShopDrawCategoryRowB]
void sub_3FD7E0(EEContext& ctx);  // 0x3FD7E0 [fclShopFreeCategoryRow]
void sub_3FD8E0(EEContext& ctx);  // 0x3FD8E0 [fclShopOpenCategories]
void sub_3FD990(EEContext& ctx);  // 0x3FD990 [fclShopUpdateCategories]
void sub_3FE1F0(EEContext& ctx);  // 0x3FE1F0 [fclShopUpdateCategoryList]
void sub_3FE3E0(EEContext& ctx);  // 0x3FE3E0 [fclShopBuildFusionItemList]
void sub_3FE5D0(EEContext& ctx);  // 0x3FE5D0 [fclShopUpdateFusionItems]
void sub_3FE690(EEContext& ctx);  // 0x3FE690 [fclShopAddFusionPersonas]
void sub_3FE7D0(EEContext& ctx);  // 0x3FE7D0 [fclShopFusionPersonaFlags]
void sub_3FE850(EEContext& ctx);  // 0x3FE850 [fclShopBuildFusionPersonaList]
void sub_3FE950(EEContext& ctx);  // 0x3FE950 [fclShopUpdateFusionPersonas]
void sub_3FEA10(EEContext& ctx);  // 0x3FEA10 [fclShopAddTradeTable]
void sub_3FEB30(EEContext& ctx);  // 0x3FEB30 [fclShopTradeRowState]
void sub_3FEE40(EEContext& ctx);  // 0x3FEE40 [fclShopTradeRefresh]
void sub_3FEF30(EEContext& ctx);  // 0x3FEF30 [fclShopBuildTradeList]
void sub_3FF150(EEContext& ctx);  // 0x3FF150 [fclShopBuildOldTradeList]
void sub_3FF460(EEContext& ctx);  // 0x3FF460 [fclShopMarkNewTrades]
void sub_3FF570(EEContext& ctx);  // 0x3FF570 [fclShopUpdateTradeList]
void sub_4003A0(EEContext& ctx);  // 0x4003A0 [fclShopFreeListPair]
void sub_4006C0(EEContext& ctx);  // 0x4006C0 [fclShopBgPartsPurge]
void sub_4008F0(EEContext& ctx);  // 0x4008F0 [fclShopBgPartsDraw]
void sub_400E30(EEContext& ctx);  // 0x400E30 [fclShopBgManagerDestroy]
void sub_4016D0(EEContext& ctx);  // 0x4016D0 [fclPersonaBestStats]
void sub_401800(EEContext& ctx);  // 0x401800 [fclFusionItemFlag]
void sub_401A00(EEContext& ctx);  // 0x401A00 [fclFusionResult]
void sub_401C90(EEContext& ctx);  // 0x401C90 [fclFusionFindBand]
void sub_401CF0(EEContext& ctx);  // 0x401CF0 [fclFusionFindArcanaBand]
void sub_401D90(EEContext& ctx);  // 0x401D90 [fclFusionFindFoolEntry]
void sub_401DE0(EEContext& ctx);  // 0x401DE0 [fclFusionMakeOrder]
void sub_402400(EEContext& ctx);  // 0x402400 [fclFusionOrderItem]
void sub_402510(EEContext& ctx);  // 0x402510 [fclShopSlotHolds]
void sub_4032F0(EEContext& ctx);  // 0x4032F0 [fclQuestAccept]
void sub_403340(EEContext& ctx);  // 0x403340 [fclQuestCancel]
void sub_403410(EEContext& ctx);  // 0x403410 [fclQuestDeadline]
void sub_403760(EEContext& ctx);  // 0x403760 [fclQuestGet48]
void sub_403780(EEContext& ctx);  // 0x403780 [fclQuestGet50]
void sub_4037A0(EEContext& ctx);  // 0x4037A0 [fclQuestGet54]
void sub_4037C0(EEContext& ctx);  // 0x4037C0 [fclQuestGet52]
void sub_4037E0(EEContext& ctx);  // 0x4037E0 [fclQuestGetCond]
void sub_403860(EEContext& ctx);  // 0x403860 [fclQuestGetBlock16]
void sub_4038E0(EEContext& ctx);  // 0x4038E0 [fclQuestGet44]
void sub_404470(EEContext& ctx);  // 0x404470 [fclQuestSetFlag]
void sub_404750(EEContext& ctx);  // 0x404750 [fclQuestListAnim]
void sub_405A90(EEContext& ctx);  // 0x405A90 [fclQuestRowFree]
void sub_405D60(EEContext& ctx);  // 0x405D60 [fclQuestListDestroy]
void sub_405DB0(EEContext& ctx);  // 0x405DB0 [fclQuestCompare]
void sub_405E00(EEContext& ctx);  // 0x405E00 [fclQuestListSort]
void sub_405E30(EEContext& ctx);  // 0x405E30 [fclQuestListUpdate]
void sub_406AA0(EEContext& ctx);  // 0x406AA0 [fclShopDrawDatePanel]
void sub_407180(EEContext& ctx);  // 0x407180 [fclQuestDrawWindow]
void sub_407210(EEContext& ctx);  // 0x407210 [fclQuestDrawRow]
void sub_409C80(EEContext& ctx);  // 0x409C80 [fclBookFillList]
void sub_409E90(EEContext& ctx);  // 0x409E90 [fclBookStockRegistered]
void sub_409F20(EEContext& ctx);  // 0x409F20 [fclBookRowFree]
void sub_40A200(EEContext& ctx);  // 0x40A200 [fclBookListDestroy]
void sub_40A260(EEContext& ctx);  // 0x40A260 [fclBookRegisterAll]
void sub_40A5B0(EEContext& ctx);  // 0x40A5B0 [fclBookCompareLevel]
void sub_40A640(EEContext& ctx);  // 0x40A640 [fclBookCompareArcana]
void sub_40A6D0(EEContext& ctx);  // 0x40A6D0 [fclBookSort]
void sub_40A7C0(EEContext& ctx);  // 0x40A7C0 [fclBookDrawMark]
void sub_40B630(EEContext& ctx);  // 0x40B630 [fclBookDrawWindow]
void sub_40B780(EEContext& ctx);  // 0x40B780 [fclBookDrawRow]
void sub_40C150(EEContext& ctx);  // 0x40C150 [fclShopListFlagBit]
void sub_40C1E0(EEContext& ctx);  // 0x40C1E0 [fclShopAddOptionRows]
void sub_40C460(EEContext& ctx);  // 0x40C460 [fclShopOptionRowFree]
void sub_40C520(EEContext& ctx);  // 0x40C520 [fclListPanelCloseSub]
void sub_40C5B0(EEContext& ctx);  // 0x40C5B0 [fclListPanelClose]
void sub_40C650(EEContext& ctx);  // 0x40C650 [fclListPanelDecide]
void sub_40C6A0(EEContext& ctx);  // 0x40C6A0 [fclListPanelOpen]
void sub_40CA00(EEContext& ctx);  // 0x40CA00 [fclListPanelUpdate]
void sub_40D330(EEContext& ctx);  // 0x40D330 [fclListPanelStep]

// ---- records (offsets in bytes; evidence: the functions named in each comment) ----------------------------------------
namespace fac2 {

// nmlist objects and command lists (nm_message.h): the fields the bodies read.
namespace lst {
constexpr s32 kHead = 4;  // ptr: first node (nmlist object: the list header starts at +4)
constexpr s32 kCursor = 12;  // ptr: the cursor node (the selected row of a command list)
constexpr s32 kCount = 16;  // u16: node count; new rows are keyed count + 1
constexpr s32 kState = 36;  // ptr: the object's payload -- for a command list the window state (win::)
}  // namespace lst

// nmlist nodes.
namespace node {
constexpr s32 kWord4 = 4;  // the search word of nmListFindByWord4 (the facility lists keep the item / persona id there)
constexpr s32 kNext = 16;  // ptr: next node
constexpr s32 kPayload = 20;  // ptr: the node's payload (a command-list row: row::)
}  // namespace node

// The command-list window state (the list object's payload, lst::kState).
namespace win {
constexpr s32 kFlags = 0;  // the command list's flag word (nm_message.h)
constexpr s32 kFrame = 4;  // s16: the fade frame (the open / close animations key on it)
constexpr s32 kFadeIn = 6;  // s16: fade-in length; a facility list also keeps its mode here before the open (menu::)
constexpr s32 kFadeOut = 8;  // s16: fade-out length
constexpr s32 kSpacing = 12;  // the row spacing
constexpr s32 kFirstRow = 44;  // ptr: the first visible row (a node)
constexpr s32 kUser = 68;  // ptr: the user area (menu::, 88 bytes for the facility lists)
}  // namespace win

// A command-list row's payload (node::kPayload).
namespace row {
constexpr s32 kHighlight = 8;  // a row's highlight
constexpr s32 kNumber = 12;  // the row number from 1
constexpr s32 kUser = 28;  // ptr: the row's user area (srow::, crow::, prow:: ...)
}  // namespace row

// The user area of a facility list window (88 bytes: sub_3C58F0(0, 88, rows, spacing) in sub_3FE3E0 / sub_3FE850 /
// sub_3FEF30 / sub_3FF150; the animation fields are written by the open / close updates sub_3FA210 .. sub_3FADC0).
namespace menu {
constexpr s32 kFlags = 0;  // 2 = the sale marks are applied (sub_3F2320) / the compendium is sorted by arcana (sub_40A6D0); 1 = a for-each over the elements is running (sub_407180), 4 = the same for the compendium (sub_40B630)
constexpr s32 kShopType = 4;  // s16: the shop type (shops.h) -- the list's owner; the BG part list keeps a list object here
constexpr s32 kMode = 6;  // s16: the list kind: -2 trade, -3 trade-in, -4 weapon-fusion base items, -5 weapon-fusion personas; the row drawer sub_3F9510 picks its drawer and column set from it
constexpr s32 kElems = 8;  // ptr: the window's element set (shops.h FclElement nodes)
constexpr s32 kTask = 12;  // ptr: a task the list owns (BOOK: destroyed with its children by the step's fini)
constexpr s32 kElemsA = 28;  // ptr: element set (the compendium)
constexpr s32 kElemsB = 32;  // ptr: second element set or 0 (the compendium)
constexpr s32 kSlideX = 40;  // s16: the window's x offset (the open slide: -160 -> 0)
constexpr s32 kSlideY = 42;  // s16: the window's y offset
constexpr s32 kAlpha = 52;  // s16: the window's alpha (0..255)
constexpr s32 kBarX = 56;  // s16: the title bar's x offset (-140 / -160 / -200 -> 0)
constexpr s32 kBarY = 58;  // s16: the title bar's y offset
constexpr s32 kBarAlpha = 68;  // s16: the title bar's alpha
constexpr s32 kPop = 74;  // s16: the cursor pop (3 -> 0)
constexpr s32 kScale = 80;  // f32: the cursor scale (0.001 + 1.079 t / 5, then 1.08 - 0.08 t / 4: grows past 1 and settles)
constexpr s32 kScaleAlpha = 84;  // s16: the cursor's alpha (0 until its pop starts, then 255)
constexpr s32 kModeTrade = -2;
constexpr s32 kModeTradeIn = -3;
constexpr s32 kModeFusionItems = -4;
constexpr s32 kModeFusionPersonas = -5;
}  // namespace menu

// The 28-byte shop item entry (sub_3F1BA0: memset, id, category; the fields per item kind 0..4 of sub_170ED0 -- kind 0
// has two stats (attack / hit for a weapon), kinds 1 and 2 one, kind 3 five, kind 4 none).
namespace item {
constexpr s32 kId = 0;  // u16: the item id
constexpr s32 kCategory = 4;  // the category code of the item's flag word (sub_3F1A10; 0x100000's for key items)
constexpr s32 kKind = 8;  // u8: 2 for every item built by sub_3F1BA0
constexpr s32 kEquip = 9;  // u8: 0x82 for the equipment kinds 0..2
constexpr s32 kCount = 10;  // u16: owned / chosen count (0 at creation)
constexpr s32 kPrice = 12;  // the price from the item record (yen)
constexpr s32 kStatA = 16;  // s16: weapon attack / armour defence ... (per kind, sub_3F1BA0)
constexpr s32 kStatB = 18;  // s16
constexpr s32 kStatC = 20;  // s16
constexpr s32 kStatD = 22;  // s16
constexpr s32 kStatE = 24;  // s16
constexpr s32 kSize = 28;  // the entry's size
}  // namespace item

// The user area of a shop / trade / weapon-fusion list row (32 bytes, nmCmdListAddRow(list, key, 32, 0)).
namespace srow {
constexpr s32 kFlags = 0;  // 1 marked (the list was built with flag 1), 2 on sale, 4 / 8 sale rate 30 % / 50 % off (else 25 %), 0x10 unavailable (99 owned, materials missing, no fusion result), 0x20 sold out (stock 0), 0x40 the current persona, 0x80 new or changed since the last visit
constexpr s32 kItem = 4;  // the 28-byte shop item entry (item::)
constexpr s32 kItemCategory = 8;  // item +4
constexpr s32 kOwned = 14;  // s16: item +10, the owned count (TRADE rows)
constexpr s32 kPrice = 16;  // item +12: the price after the lineup rate and the sale
constexpr s32 kMat1 = 20;  // s16: TRADE: the first material (0 = none) / ARMSCOMBINE: the persona
constexpr s32 kMat1Count = 22;  // s16: TRADE: its count (asserted non-zero)
constexpr s32 kMat2 = 24;  // s16: TRADE: the second material / ARMSCOMBINE: the result's category code
constexpr s32 kMat2Count = 26;  // s16
constexpr s32 kResult = 28;  // u16: ARMSCOMBINE: the item the persona makes (0 = none)
}  // namespace srow

// A shop lineup (sub_3F25E0 / sub_3F2320; the per-shop tables of fclShopMisc.c).
namespace lineup {
constexpr s32 kRate = 2;  // s16: the default price rate in percent
constexpr s32 kCount = 6;  // s16: entries
constexpr s32 kEntries = 8;  // ptr: 8-byte entries (lent::)
}  // namespace lineup

// A lineup entry.
namespace lent {
constexpr s32 kId = 0;  // s16: the item (0 = empty slot)
constexpr s32 kRate = 2;  // s16: the entry's price rate in percent (<= 0: the lineup's)
constexpr s32 kCond = 4;  // s8: 1 = only with game flag 4880
constexpr s32 kFlags = 5;  // u8: 1 on sale (2 / 4 its rate), 8 limited stock (the slot +6)
constexpr s32 kStock = 6;  // s8: the stock slot for sub_17D060
constexpr s32 kSize = 8;
}  // namespace lent

// The quantity selector of the BUY / SELL steps (sub_3FB0C0 opens it, sub_3FB2F0 / sub_3FB530 step it). Pad:
// up +1, down -1, right +10, left -10 (0x7E0952 / 0x7E095A bits 0x1000 / 0x4000 / 0x2000 / 0x8000).
namespace qsel {
constexpr s32 kFlags = 0;  // 1 open, 2 buying, 4 selling, 8 at the maximum, 0x10 at 1
constexpr s32 kWord4 = 4;  // u16: 1 at the open
constexpr s32 kCount = 8;  // the chosen count (1..99)
constexpr s32 kItemId = 12;  // u16: the item (the stock lookup sub_17D250)
constexpr s32 kLimit = 22;  // s16: buying: the owned count (count + owned < 100); selling: the count owned (the maximum)
constexpr s32 kPrice = 24;  // the unit price (buying: count <= yen / price)
constexpr s32 kWord42 = 42;  // s16: 0 at the open
constexpr s32 kWord44 = 44;  // s16
constexpr s32 kWord46 = 46;  // s16
}  // namespace qsel

// A TRADE table entry (14 bytes; tables off_6AD4A0 / off_6AD4A8 and the extra tables off_6AD4B0[1..]).
namespace tent {
constexpr s32 kItem = 0;  // s16: the item offered
constexpr s32 kFlag = 4;  // s16: the game flag it needs (0: always)
constexpr s32 kMaterials = 6;  // 14 bytes copied to the row's +20 (two {item, count} pairs and the rest)
constexpr s32 kMatCount = 8;  // s16: the first material count (0: the entry is skipped)
constexpr s32 kSize = 14;
}  // namespace tent

// A weapon-fusion order (ARMSCOMBINE; sub_401DE0 builds it from the base item and the persona).
namespace order {
constexpr s32 kFlags = 0;  // u16: 1 placed, 2 a fixed result (the special persona table): ready a day later
constexpr s32 kMonth = 2;  // u8: the pick-up date (today + 1, + 2 for a fixed result)
constexpr s32 kDay = 3;  // u8
constexpr s32 kItem = 4;  // u16: the item made
constexpr s32 kRaw = 8;  // its record word +4 (category bits)
constexpr s32 kByte12 = 12;  // u8
constexpr s32 kByte13 = 13;  // u8: from the level band (per arcana) or the Fool table
constexpr s32 kStatA = 14;  // s16: from the recipe's level band (or the Fool table)
constexpr s32 kStatB = 16;  // s16
constexpr s32 kValue = 24;  // the item record's value when the item's fusion flag (4736 + i) is unset, else level / 5 + 1
constexpr s32 kSize = 28;
}  // namespace order

// An Elizabeth request record (64 bytes; the accessors sub_403760 .. sub_403900).
namespace quest {
constexpr s32 kCond = 8;  // the condition block (sub_4037E0 returns its address): +4 / +6 packed dates, +7 high nibble the kind
constexpr s32 kDate = 14;  // s16: packed date: bits 6..11 the month, bits 0..5 the day (sub_403800 / sub_403830)
constexpr s32 kText16 = 16;  // a 16-byte block (sub_403860 returns its address)
constexpr s32 kFlag = 20;  // u16: the request's game flag (0xFFFF none; sub_404470 sets / clears it)
constexpr s32 kText32 = 32;  // a block (sub_403880 returns its address)
constexpr s32 kWord44 = 44;
constexpr s32 kHalf48 = 48;  // s16
constexpr s32 kHalf50 = 50;  // s16
constexpr s32 kHalf52 = 52;  // s16
constexpr s32 kHalf54 = 54;  // s16
constexpr s32 kOrder = 58;  // s16: the sort key of the request list (sub_405DB0)
constexpr s32 kHalf60 = 60;  // s16
constexpr s32 kSize = 64;  // 100 records at *(0x7CD8F0) = 0x6AD4C0
constexpr u32 kTableSlot = 0x7CD8F0u;  // ($gp - 21504) -> the 100 records
}  // namespace quest

// A compendium (BOOK) row's user area (16 bytes, sub_409C80).
namespace crow {
constexpr s32 kPersona = 4;  // ptr: the registered persona (52-byte persona record: +2 id, +4 level)
constexpr s32 kPrice = 8;  // the summon price: 3 s^2 + 2000 (s = the five stats' sum), x4 with game flag 4889, at most 9,999,999
constexpr s32 kElems = 12;  // ptr: the row's element set
}  // namespace crow

// The 52-byte persona record (fusion.h): the fields read here.
namespace persona {
constexpr s32 kId = 2;  // u16: the persona id (PERSONA.TBL section 0 index, 14-byte records: +2 arcana)
constexpr s32 kLevel = 4;  // u8: level
}  // namespace persona

// The work of the list window part animator sub_3D9820 (the fusion and shop list windows).
namespace panel {
constexpr s32 kElems = 8;  // ptr: the window element set (the parts 2..7 of sub_3D9820)
constexpr s32 kList = 12;  // ptr: the command list whose rows carry the part 0 / 1 elements
}  // namespace panel

// A facility element (shops.h FclElement): the fields the bodies write.
namespace elem {
constexpr s32 kNode = 4;  // ptr: back to the node (shops.h FclElement)
constexpr s32 kFlags = 8;
constexpr s32 kState = 12;
constexpr s32 kId = 16;
constexpr s32 kX = 20;  // s16
constexpr s32 kY = 22;  // s16
constexpr s32 kX0 = 24;  // s16: start
constexpr s32 kY0 = 26;  // s16: start
constexpr s32 kX1 = 28;  // s16: end
constexpr s32 kY1 = 30;  // s16: end
constexpr s32 kAlpha = 38;  // s16
constexpr s32 kAlpha0 = 40;  // s16
constexpr s32 kAlpha1 = 42;  // s16
constexpr s32 kDelay = 44;  // s16
}  // namespace elem

// A shop step's payload (the descriptors' payload sizes; sub_3C5470 returns it from the step node).
namespace step {
constexpr s32 kResult = 0;  // what the step's poller returns when it ends (shops.h kStepResult)
constexpr s32 kFlags = 4;  // 2 = hidden / closing (the draws skip)
constexpr s32 kPhase = 8;  // the step's phase (1 after the init)
constexpr s32 kList = 12;  // ptr: the step's command list
constexpr s32 kList2 = 16;  // ptr: ARMSCOMBINE: the persona list (0 until built); BOOK: the compendium list
}  // namespace step

// The shop work record (shops.h kShop*): the fields read here.
namespace shopw {
constexpr s32 kType = 0;  // the shop type (shops.h kShopType)
constexpr s32 kState = 4;  // the root state machine's state (shops.h kShopState)
constexpr s32 kFlags = 8;  // shops.h kShopFlags
}  // namespace shopw

namespace cat {
constexpr s32 kList = 4;  // ptr: the category's sub-list
constexpr s32 kElems = 8;  // ptr: the category row's element set
}  // namespace cat

namespace catw {
constexpr s32 kList = 0;  // ptr: the category list
constexpr s32 kElems = 8;  // ptr: the window element set
}  // namespace catw

namespace ttab {
constexpr s32 kEntries = 0;  // ptr: the entries
constexpr s32 kCount = 4;  // the entry count
}  // namespace ttab

namespace bgm {
constexpr s32 kFlags = 0;  // shops.h kBgFlags
constexpr s32 kList = 8;  // ptr: the element list (shops.h kBgList)
constexpr s32 kTask = 12;  // ptr: "fclShopDrawBGLow" (shops.h kBgTask)
}  // namespace bgm

namespace recipe {
constexpr s32 kMask = 0;  // the best-stat mask it accepts (sub_4016D0 bits)
constexpr s32 kGroup = 4;  // u16: the base item group
constexpr s32 kItem = 6;  // u16: the item made
constexpr s32 kBands = 8;  // {ptr, count}: the level bands (sub_401C90)
constexpr s32 kSize = 16;  // 25 recipes at *(0x7CD8D0) = 0x6ACE30
}  // namespace recipe

namespace band {
constexpr s32 kLo = 0;  // u8: lowest level
constexpr s32 kHi = 1;  // u8: highest level
constexpr s32 kValueA = 2;  // u16 (the order's +14; in the 46-byte arcana bands: per arcana bytes from here)
constexpr s32 kValueB = 4;  // u16 (the order's +16)
}  // namespace band

namespace fent {
constexpr s32 kId = 0;  // u16: the persona
constexpr s32 kValueA = 2;  // u8 (the order's +14)
constexpr s32 kValueB = 3;  // u8 (the order's +16)
constexpr s32 kByte = 4;  // u8 (the order's +13)
}  // namespace fent

namespace qcond {
constexpr s32 kDateA = 4;  // s16 packed date (bits 6..11 month, 0..5 day)
constexpr s32 kDateB = 6;  // s16: a packed date, or (kind 2) a day count in the low 12 bits
constexpr s32 kKind = 7;  // high nibble: 0 no deadline, 1 the date +6, 2 the date +4 plus +6's days
}  // namespace qcond

namespace hrow {
constexpr s32 kEntry = 4;  // ptr: the option entry (hent::)
constexpr s32 kElems = 8;  // ptr: the row's element set
}  // namespace hrow

// A background part list node payload (sub_4006C0 / sub_4008F0).
namespace bgpart {
constexpr s32 kCondA = 4;  // s16: the event pair sub_3FFA20 tests; the node is removed once it holds
constexpr s32 kCondB = 6;  // s16
}  // namespace bgpart

// A 16-byte option entry of sub_40C1E0's table {entries, count}.
namespace hent {
constexpr s32 kFlagA = 0;  // game flag (0: none)
constexpr s32 kFlagB = 4;  // game flag (0: none)
constexpr s32 kSize = 16;
}  // namespace hent

}  // namespace fac2

}  // namespace p3fes::game
