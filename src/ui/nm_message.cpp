// nmlist.c / nmSequence.c / nmCmdList.c and the shared message-window helpers (nm_message.h has the groups, the data
// each function works on and the register contract; docs/ANALYSIS/27_unmapped_bands.md, band 0x3C4430-0x3C7794).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated; backedge() sits wherever that body has a check point on a backward jump. Loops whose test block
// comes first ("goto test" in the recompiled body) charge the test block, then take the check point before every
// pass through the body. A block that ends in a `jal` is charged in full before the call (the recompiler keeps the
// call inside its block), so a call's return continues in the same block.
//
// Registers: register-faithful (nm_message.h). Each body runs on the Cpu view of the guest context: one variable per
// GPR (64-bit writes keep bits 64..127, as the EE does; the prologue / epilogue spills are 128-bit), the FPU and HI/LO
// operations through the runtime's own instruction semantics. The band was compiled without delay-slot scheduling
// (every slot is a nop), so the statements follow the instructions in order.
#include "p3fes/game/nm_message.h"

#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);         // K_Assert(file, line): `jr $ra` in retail
void fn_sub_3C4430_003c4430(p3fes::EEContext&);         // [nmNodeCreate]: RwHeapMalloc(24 + size) (kept recompiled)
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);         // [nmListCreate]: RwHeapMalloc(40 + size) (kept recompiled)
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);         // [nmListDestroy]: clear + RwFree (kept recompiled)
void fn_sub_3C4650_003c4650(p3fes::EEContext&);         // [nmNodeCreateKeyed]: RwHeapMalloc (kept recompiled)
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);         // [nmListRemove]: unlink + on-remove + RwFree (kept recompiled)
void fn_sub_3C4A90_003c4a90(p3fes::EEContext&);         // [nmListClear]: on-remove + RwFree each (kept recompiled)
void fn_sub_3C4F30_003c4f30(p3fes::EEContext&);         // [nmNodeFree]: memset + RwFree (kept recompiled)
void fn_sub_3C4FC0_003c4fc0(p3fes::EEContext&);         // [nmListSort]: RwHeapMalloc'd array + qsort (kept recompiled)
void fn_memset_00521408(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);         // the menu cursor / row highlight draw
void fn_itfMesMngInitialize_003a2d80(p3fes::EEContext&);
void fn_itfMesMngSetStateFlags_003a3e10(p3fes::EEContext&);
void fn_itfMesMngClearStateFlags_003a3e90(p3fes::EEContext&);
void fn_itfMesMngRequestMessage_003a30c0(p3fes::EEContext&);
void fn_itfMesMngSetSelectWord84_003a27c0(p3fes::EEContext&);
void fn_itfMesMngGetSelection_003a2830(p3fes::EEContext&);
void fn_itfMesMngSetBusy_003a25f0(p3fes::EEContext&);
void fn_sub_3A4360_003a4360(p3fes::EEContext&);         // itfMesManager.c: the window-type switch (topic 20)
void fn_sub_3A2A30_003a2a30(p3fes::EEContext&);         // itfMesManager.c: close a slot's window
void fn_sub_3A3420_003a3420(p3fes::EEContext&);         // itfMesManager.c: release a slot's panels
void fn_sub_3C7C90_003c7c90(p3fes::EEContext&);         // the message-window record: open / close the panel
void fn_sub_3C7D50_003c7d50(p3fes::EEContext&);         // the message-window record: returns 0x95BE90
void fn_sub_3C8230_003c8230(p3fes::EEContext&);         // the message-window record: set the window type
// this slice (called through their entry points, as the original's jal)
void fn_nmListInsertAfter_003c4710(p3fes::EEContext&);
void fn_nmListUnlink_003c4820(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListCursorNext_003c4c80(p3fes::EEContext&);
void fn_nmListCursorPrev_003c4d20(p3fes::EEContext&);
void fn_nmListCursorClearEnd_003c4dc0(p3fes::EEContext&);
void fn_sub_3C4DE0_003c4de0(p3fes::EEContext&);
void fn_nmListRemoveFiltered_003c4e70(p3fes::EEContext&);
void fn_nmByteSum_003c4f80(p3fes::EEContext&);
void fn_sub_3C53E0_003c53e0(p3fes::EEContext&);
void fn_nmSeqStepRun_003c5840(p3fes::EEContext&);
void fn_nmSeqStepCall36_003c5870(p3fes::EEContext&);
void fn_sub_3C5AF0_003c5af0(p3fes::EEContext&);
void fn_sub_3C5C50_003c5c50(p3fes::EEContext&);
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);
void fn_sub_3C63F0_003c63f0(p3fes::EEContext&);
void fn_nmCmdListStartFade_003c6900(p3fes::EEContext&);
void fn_sub_3C69D0_003c69d0(p3fes::EEContext&);
void fn_nmCmdListScrollBar_003c6b70(p3fes::EEContext&);
void fn_nmCmdListDecidedRow_003c6c50(p3fes::EEContext&);
void fn_nmCmdListCancelled_003c6c80(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_nmCmdListVisibleRows_003c6f80(p3fes::EEContext&);
void fn_msgWinRecordInit_003c72a0(p3fes::EEContext&);
void fn_msgWinGetSelection_003c75b0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace nm::detail {

namespace gen = ::p3fes::recomp_gen;

// --- the Cpu helpers the header declares ------------------------------------------------------------------------------
void Cpu::k_assert(u32 file, u32 line, u32 pc) {
    a0 = sx(file);  // lui a0, 0x6A; addiu a0, a0, file
    a1 = line;
    jal(pc, gen::fn_sub_19D3F0_0019d3f0);
}

void Cpu::open_frame(unsigned n) {
    sp = addiu(sp, -static_cast<s32>(16 * n + 16));
    sd(sp + 16 * n, ra);
    for (unsigned i = n; i-- > 0;) sq(sp + 16 * i, Gpr{c, GPR_S0 + i});
}

void Cpu::close_frame(unsigned n) {
    ra = ld(sp + 16 * n);
    for (unsigned i = n; i-- > 0;) {
        Gpr s{c, GPR_S0 + i};
        lq(s, sp + 16 * i);
    }
    sp = addiu(sp, static_cast<s32>(16 * n + 16));
}

// The bodies, named as the functions they are (nm_message.h documents each).
class Nm : public Cpu {
public:
    using Cpu::Cpu;

    // [nmlist]
    void nmListInsertAfter();
    void nmListUnlink();
    void nmListAppendNew();
    void find_tail(s32 field);
    void nmListFindByKey();
    void nmListFindByWord4();
    void cursor_step(s32 link, s32 wrap_to);
    void nmListCursorNext();
    void nmListCursorPrev();
    void nmListCursorClearEnd();
    void sub_3C4DE0();
    void nmListCursorSeek();
    void nmListCursorHead();
    void sub_3C4E60();
    void nmListRemoveFiltered();
    void nmByteSum();
    void nmListRebuild();
    // [nmSequence]
    void nmSeqNullStep();
    void nmSequenceCreate();
    void sub_3C5210();
    void destroy_tail(u32 pc);
    void nmSequenceDestroy();
    void nmSequenceAddStep();
    void sub_3C53E0();
    void nmObjPayloadWord12();
    void sub_3C5470();
    void nmNodePayloadArea40();
    void sub_3C5490();
    void nmSequenceCallAll36();
    void step_call(s32 slot, u64 first, u32 pc, bool keep_result);
    void sub_3C57E0();
    void nmSeqStepOnRemove();
    void nmSeqStepRun();
    void nmSeqStepCall36();
    void nullsub();
    // [nmCmdList]
    void sub_3C58F0();
    void nmCmdListDestroy();
    void nmCmdListAddRow();
    void sub_3C5AF0();
    void down_after_next();
    void nmCmdListCursorDown();
    void sub_3C5C50();
    void nmCmdListSelect();
    void set_callback(s32 slot, u32 line, u32 pc);
    void nmCmdListSetDrawFunc();
    void nmCmdListSetUpdateFunc();
    void nmCmdListSetRowDrawFunc();
    void nmCmdListSetRowRemoveFunc();
    void nmCmdListRemoveRow();
    void nmCmdListOnInsert();
    void nmCmdListOnRemove();
    void nmCmdListDrawRow();
    void nmCmdListUpdate();
    void nmCmdListDraw();
    void scroll_up_inline(u32 pc);
    bool cursor_down_inline(u32 pc);
    void release_check(u32 hold, u32 other, u64 last, u32 pc);
    void sub_3C63F0();
    void nmCmdListStartFade();
    void sub_3C69D0();
    void nmCmdListScrollBar();
    void flag_row(u32 mask);
    void nmCmdListDecidedRow();
    void flag_word(u64 first, u64 mask);
    void nmCmdListCancelled();
    void nmCmdListPagedDown();
    void nmCmdListMovedUp();
    void nmCmdListMovedDownRow();
    void nmCmdListScrolledRow();
    void nmCmdListSetPosition();
    void sub_3C6D60();
    void status_word(bool tail_branch);
    void nmCmdListStatus();
    void nmCmdListStatus28();
    void nmCmdListHold();
    void nmCmdListRelease();
    void sub_3C6EE0();
    void nmCmdListClose();
    void nmCmdListCloseNow();
    void nmCmdListVisibleRows();
    void nmCmdListCursorLine();
    void nmCmdListSort();
    void sub_3C7070();
    // [msgwin]
    void msgWinReset();
    void msgWinRecordInit();
    void sub_3C72D0();
    void state_flags(u32 pc, rt::Fn op, u32 op_pc);
    void msgWinSetStateFlags();
    void sub_3C73E0();
    void msgWinRequestMessage();
    void sub_3C74E0();
    void msgWinSetType();
    void msgWinGetSelection();
    void msgWinLastSelection();
    void msgWinClose();
    void sub_3C7700();
};

// =====================================================================================================================
// [nmlist]
// =====================================================================================================================

// nmListInsertAfter [nmListInsertAfter]: $a0 the list header, $a1 the node to insert after (0: at the head), $a2 the new node.
// Counts the node even when it is null (then nothing is linked); a first node becomes the tail and the cursor.
void Nm::nmListInsertAfter() {
    enter(10);
    open_frame(3);
    s2 = a0;  // list
    s1 = a1;  // after
    s0 = a2;  // node
    if (s2 == 0) {
        charge(5);
        k_assert(kNmListFile, 277, 0x3c4744);
    }
    charge(5);
    v1 = lhu(s2 + 12);
    v1 = addiu(v1, 1);
    sh(s2 + 12, v1);  // ++count
    if (s0 != 0) {
        charge(4);
        sw(s0 + 16, zero);  // next
        sw(s0 + 12, zero);  // prev
        if (s1 == 0) {
            // at the head
            charge(3);
            v1 = lw(s2);
            if (v1 != 0) {
                charge(5);
                sw(s0 + 12, zero);
                v1 = lw(s2);
                sw(s0 + 16, v1);  // node->next = head
                v1 = lw(s2);
                sw(v1 + 12, s0);  // head->prev = node
            }
            charge(4);
            sw(s2, s0);  // head = node
            v1 = lw(s2 + 4);
            if (v1 == 0) {
                charge(3);
                sw(s2 + 4, s0);  // tail = node
            }
        } else {
            charge(3);
            v1 = lw(s1 + 16);
            if (v1 != 0) {
                // between `after` and its successor
                charge(8);
                sw(s0 + 12, s1);
                v1 = lw(s1 + 16);
                sw(s0 + 16, v1);
                sw(s1 + 16, s0);
                v1 = lw(s0 + 16);
                sw(v1 + 12, s0);
            } else {
                // after the tail
                charge(4);
                sw(s0 + 12, s1);
                sw(s0 + 16, zero);
                sw(s1 + 16, s0);
                sw(s2 + 4, s0);
            }
        }
        charge(3);
        v1 = lw(s2 + 8);
        if (v1 == 0) {
            charge(1);
            sw(s2 + 8, s0);  // cursor = node when there was none
        }
    }
    charge(7);
    close_frame(3);
}

// nmListUnlink [nmListUnlink]: $a0 the list header, $a1 the node. Unlinks it (count - 1, node prev / next cleared) and
// returns its successor -- its predecessor when it was the tail, 0 when it was alone (or not in the list).
void Nm::nmListUnlink() {
    enter(8);
    open_frame(2);
    s1 = a0;  // list
    s0 = a1;  // node
    if (s1 == 0) {
        charge(5);
        k_assert(kNmListFile, 329, 0x3c484c);
    }
    charge(2);
    if (s0 == 0) {
        charge(5);
        k_assert(kNmListFile, 330, 0x3c4868);
    }
    charge(6);
    v0 = lhu(s1 + 12);
    v0 = addiu(v0, -1);
    sh(s1 + 12, v0);  // --count
    v0 = lw(s0 + 12);  // prev
    if (v0 == 0) {
        charge(3);
        v0 = lw(s0 + 16);  // next
        if (v0 == 0) {
            charge(3);
            v0 = lw(s1);
            if (v0 == s0) {  // the only node: the list becomes empty
                charge(2);
                sw(s1 + 4, zero);
                sw(s1, zero);
            }
            charge(3);
            v0 = 0;
        } else {  // the head: next becomes the head
            charge(4);
            sw(v0 + 12, zero);
            sw(s1, v0);
        }
    } else {
        charge(3);
        v1 = lw(s0 + 16);
        if (v1 == 0) {  // the tail: prev becomes the tail
            charge(4);
            sw(v0 + 16, zero);
            sw(s1 + 4, v0);
        } else {  // in between
            charge(3);
            sw(v0 + 16, v1);
            sw(v1 + 12, v0);
            v0 = lw(v0 + 16);
        }
    }
    charge(8);
    sw(s0 + 12, zero);
    sw(s0 + 16, zero);
    close_frame(2);
}

// nmListAppendNew [nmListAppendNew]: $a0 the list object, $a1 the key (0: the node itself), $a2 the payload size. Creates the
// node (sub_3C4430), appends it after the tail, calls the object's on-insert callback (+20) and returns the node.
void Nm::nmListAppendNew() {
    enter(10);
    open_frame(3);
    s2 = a0;  // obj
    s1 = a1;  // key
    s0 = a2;  // size
    if (s2 == 0) {
        charge(5);
        k_assert(kNmListFile, 381, 0x3c4944);
    }
    charge(6);
    a0 = s0;
    jal(0x3c4950, gen::fn_sub_3C4430_003c4430);
    s0 = v0;  // node
    if (s1 == 0) {
        charge(3);
        sw(s0, s0);
    } else {
        charge(1);
        sw(s0, s1);
    }
    charge(2);
    if (s0 == 0) {
        charge(5);
        k_assert(kNmListFile, 384, 0x3c4988);
    }
    charge(18);
    a0 = addiu(s2, 4);
    a1 = lw(s2 + 8);  // after the tail
    a2 = s0;
    jal(0x3c499c, gen::fn_nmListInsertAfter_003c4710);
    a0 = s2;
    a1 = s0;
    v0 = lw(s2 + 20);
    jalr(0x3c49b0, w(v0));  // on-insert(obj, node)
    v0 = s0;
    close_frame(3);
}

// The search loop of nmListFindByKey / nmListFindByWord4: from $v0 = list->head, the first node whose word at `field` equals $s0
// (64-bit compare of the loaded word with the argument register), 0 at the end.
void Nm::find_tail(s32 field) {
    charge(3);
    v0 = lw(s1);
    for (;;) {
        charge(2);
        if (v0 == 0) {
            charge(1);
            v0 = 0;
            break;
        }
        backedge();
        charge(3);
        v1 = lw(v0 + field);
        if (v1 == s0) {
            charge(2);
            break;
        }
        charge(1);
        v0 = lw(v0 + 16);
    }
    charge(6);
    close_frame(2);
}

// nmListFindByKey [nmListFindByKey]: $a0 the object (asserted only), $a1 the list header, $a2 the key.
void Nm::nmListFindByKey() {
    enter(8);
    open_frame(2);
    s1 = a1;
    s0 = a2;
    if (a0 == 0) {
        charge(5);
        k_assert(kNmListFile, 455, 0x3c4b7c);
    }
    charge(2);
    if (s1 == 0) {
        charge(5);
        k_assert(kNmListFile, 456, 0x3c4b98);
    }
    find_tail(0);
}

// nmListFindByWord4 [nmListFindByWord4]: as nmListFindByKey on the node's word +4; one assert covers both pointers.
void Nm::nmListFindByWord4() {
    enter(8);
    open_frame(2);
    s1 = a1;
    s0 = a2;
    bool bad = a0 == 0;
    if (!bad) {
        charge(2);
        bad = s1 == 0;
    }
    if (bad) {
        charge(5);
        k_assert(kNmListFile, 503, 0x3c4c24);
    }
    find_tail(4);
}

// nmListCursorNext / nmListCursorPrev [nmListCursorNext / Prev]: $a0 the object, $a1 the list header. Moves the cursor (+8) along
// `link` (+16 next / +12 prev); at the end it wraps to `wrap_to` (+0 head / +4 tail) once -- only while the flag bit 1
// (+14) is clear -- and every move sets the bit. Returns the new cursor, 0 when it did not move.
void Nm::cursor_step(s32 link, s32 wrap_to) {
    enter(2);
    bool moved = false;
    if (a0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(2);
        if (a1 == 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(3);
            v0 = lw(a1 + 8);
            if (v0 == 0) {
                charge(3);
                v0 = 0;
            } else {
                charge(3);
                v0 = lw(v0 + link);
                if (v0 != 0) {
                    charge(3);
                    sw(a1 + 8, v0);
                    moved = true;
                } else {
                    charge(4);
                    v0 = lh(a1 + 14);
                    v0 = v0 & 0x2;
                    if (v0 == 0) {
                        charge(4);
                        v0 = lw(a1 + wrap_to);
                        sw(a1 + 8, v0);
                        moved = true;
                    } else {
                        charge(3);
                        v0 = 0;
                    }
                }
            }
        }
    }
    if (moved) {
        charge(4);
        v0 = lh(a1 + 14);
        v0 = v0 | 0x2;
        sh(a1 + 14, v0);
        v0 = lw(a1 + 8);
    }
    charge(2);
}

void Nm::nmListCursorNext() { cursor_step(16, 0); }
void Nm::nmListCursorPrev() { cursor_step(12, 4); }

// nmListCursorClearEnd [nmListCursorClearEnd]: $a1 the list header: clears the flag bit 1 (+14).
void Nm::nmListCursorClearEnd() {
    enter(2);
    if (a1 != 0) {
        charge(4);
        a0 = lh(a1 + 14);
        v1 = si(-3);
        v1 = a0 & v1;
        sh(a1 + 14, v1);
    }
    charge(2);
}

// sub_3C4DE0 [nmListCursorSet]: list->cursor = $a2; returns 0.
void Nm::sub_3C4DE0() {
    enter(4);
    sw(a1 + 8, a2);
    v0 = 0;
}

// nmListCursorSeek [nmListCursorSeek]: $a1 the list header, $a2 an index. -1 returns the tail (the cursor is left alone);
// otherwise the cursor moves to the index-th node, which is returned (0 past the end, cursor unchanged).
void Nm::nmListCursorSeek() {
    enter(4);
    v1 = 0;
    v0 = si(-1);
    if (a2 == v0) {
        charge(3);
        v0 = lw(a1 + 4);
    } else {
        charge(3);
        v0 = lw(a1);
        for (;;) {
            charge(2);
            if (v0 == 0) {
                charge(1);
                v0 = 0;
                break;
            }
            backedge();
            charge(2);
            if (v1 == a2) {
                charge(3);
                sw(a1 + 8, v0);
                break;
            }
            charge(2);
            v0 = lw(v0 + 16);
            v1 = addiu(v1, 1);
        }
    }
    charge(2);
}

// nmListCursorHead / sub_3C4E60 [nmListCursorHead / Tail]: cursor = head / tail, returned.
void Nm::nmListCursorHead() {
    enter(4);
    v0 = lw(a1);
    sw(a1 + 8, v0);
}

void Nm::sub_3C4E60() {
    enter(4);
    v0 = lw(a1 + 4);
    sw(a1 + 8, v0);
}

// nmListRemoveFiltered [nmListRemoveFiltered]: $a0 the object. Every node the filter (+28) accepts is unlinked (the cursor moves
// to its neighbour when it pointed at it), handed to the on-remove callback (+24) and freed (sub_3C4F30). Returns 0.
void Nm::nmListRemoveFiltered() {
    enter(9);
    open_frame(3);
    s2 = a0;
    s1 = lw(a0 + 4);  // head
    for (;;) {
        charge(2);
        if (s1 == 0) break;
        backedge();
        charge(7);
        a0 = s2;
        a1 = s1;
        v0 = lw(s2 + 28);
        jalr(0x3c4ea0, w(v0));  // filter(obj, node)
        if (v0 != 0) {
            charge(8);
            a0 = addiu(s2, 4);
            a1 = s1;
            jal(0x3c4eb8, gen::fn_nmListUnlink_003c4820);
            s0 = v0;  // the neighbour
            v0 = lw(s2 + 12);
            if (s1 == v0) {
                charge(1);
                sw(s2 + 12, s0);  // cursor
            }
            charge(11);
            a0 = s2;
            a1 = s1;
            v0 = lw(s2 + 24);
            jalr(0x3c4ee0, w(v0));  // on-remove(obj, node)
            a0 = s1;
            jal(0x3c4eec, gen::fn_sub_3C4F30_003c4f30);
            s1 = s0;
        } else {
            charge(1);
            s1 = lw(s1 + 16);
        }
    }
    charge(8);
    v0 = 0;
    close_frame(3);
}

// nmByteSum [nmByteSum]: the sum of a C string's bytes as signed chars (the step key of nmSequence).
void Nm::nmByteSum() {
    enter(4);
    v0 = 0;
    a1 = 0;
    for (;;) {
        charge(4);
        v1 = addu(a0, a1);
        v1 = lb(v1);
        if (v1 == 0) break;
        backedge();
        charge(4);
        v1 = dsll32(v1, 24);
        v1 = dsra32(v1, 24);
        v0 = addu(v0, v1);
        a1 = addiu(a1, 1);
    }
    charge(2);
}

// nmListRebuild [nmListRebuild]: $a0 the object, $a1 an array of $a2 node pointers. Clears the list header and appends the
// nodes in array order; returns the count (0 without an array or a count). The sort of sub_3C4FC0 ends here.
void Nm::nmListRebuild() {
    enter(11);
    open_frame(4);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    bool none = s1 == 0;
    if (!none) {
        charge(2);
        none = s0 == 0;
    }
    if (none) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        a0 = addiu(s2, 4);
        if (a0 != 0) {
            charge(4);
            a1 = 0;
            a2 = 16;
            jal(0x3c5104, gen::fn_memset_00521408);
        }
        charge(3);
        s3 = 0;
        for (;;) {
            charge(3);
            v0 = slt(s3, s0);
            if (v0 == 0) break;
            backedge();
            charge(8);
            v0 = sll(s3, 2);
            v0 = addu(s1, v0);
            a0 = addiu(s2, 4);
            a1 = lw(s2 + 8);  // after the tail
            a2 = lw(v0);
            jal(0x3c512c, gen::fn_nmListInsertAfter_003c4710);
            s3 = addiu(s3, 1);
        }
        charge(1);
        v0 = s3;
    }
    charge(8);
    close_frame(4);
}

// =====================================================================================================================
// [nmSequence]
// =====================================================================================================================

// nmSeqNullStep / sub_3C5210 [the default step function / sequence function]: return 0.
void Nm::nmSeqNullStep() {
    enter(3);
    v0 = 0;
}

void Nm::sub_3C5210() {
    enter(3);
    v0 = 0;
}

// nmSequenceCreate [nmSequenceCreate]: $a0 the sequence function (0: sub_3C5210), $a1 the user payload size. A list object
// of 48 + size payload bytes with the step callbacks sub_3C57E0 / nmSeqStepOnRemove / nmSeqStepRun; payload +8 the function,
// +12 the user area (payload + 48) when there is one. Returns the object.
void Nm::nmSequenceCreate() {
    enter(18);
    open_frame(2);
    s1 = a0;  // func
    s0 = a1;  // size
    a0 = addiu(s0, 48);
    a1 = sx(0x3C57E0);  // on-insert
    a2 = sx(0x3C5810);  // on-remove
    a3 = sx(0x3C5840);  // filter (the step's run function)
    jal(0x3c51b4, gen::fn_sub_3C44D0_003c44d0);
    a0 = lw(v0 + 36);  // payload
    if (s1 == 0) {
        charge(5);
        v1 = sx(0x3C5210);
        sw(a0 + 8, v1);
    } else {
        charge(1);
        sw(a0 + 8, s1);
    }
    charge(2);
    if (s0 != 0) {
        charge(2);
        v1 = addiu(a0, 48);
        sw(a0 + 12, v1);
    }
    charge(6);
    close_frame(2);
}

// nmSequenceDestroy / nmCmdListDestroy [nmSequenceDestroy / nmCmdListDestroy]: sub_3C45F0($a0) in a 16-byte frame.
void Nm::destroy_tail(u32 pc) {
    enter(8);
    open_frame(0);
    jal(pc, gen::fn_sub_3C45F0_003c45f0);
    close_frame(0);
}

void Nm::nmSequenceDestroy() { destroy_tail(0x3c5228); }

// nmSequenceAddStep [nmSequenceAddStep]: $a0 the sequence, $a1 the key, $a2 the step descriptor {four callbacks, user size,
// name[16]}, $a3 the start delay, $t0 the life. Creates the keyed node (sub_3C4650, 48 + user size), fills the step
// payload (+0 the byte sum of the name, +4 the name, +20 flag bit 2, +24..+36 the callbacks, +40 the user area, +44 delay,
// +46 life), queues it by key in the pending list (payload +16), calls the on-insert callback (+20) and returns it.
void Nm::nmSequenceAddStep() {
    enter(16);
    open_frame(7);
    s5 = a0;  // sequence
    s0 = a1;  // key
    s4 = a2;  // descriptor
    s3 = a3;  // delay
    s2 = t0;  // life
    if (s5 == 0) {
        charge(5);
        k_assert(kNmSequenceFile, 134, 0x3c528c);
    }
    charge(2);
    if (s4 == 0) {
        charge(5);
        k_assert(kNmSequenceFile, 135, 0x3c52a8);
    }
    charge(3);
    v0 = addiu(s4, 20);
    if (v0 == 0) {
        charge(5);
        k_assert(kNmSequenceFile, 136, 0x3c52c8);
    }
    charge(3);
    s6 = lw(s5 + 36);  // the sequence payload
    if (s0 == 0) {
        charge(5);
        k_assert(kNmSequenceFile, 140, 0x3c52e8);
    }
    charge(33);
    v0 = lw(s4 + 16);
    a2 = addiu(v0, 48);
    a0 = s5;
    a1 = s0;
    jal(0x3c5300, gen::fn_sub_3C4650_003c4650);
    s1 = v0;            // node
    s0 = lw(v0 + 20);   // step payload
    a0 = addiu(s4, 20);
    jal(0x3c5314, gen::fn_nmByteSum_003c4f80);
    sw(s0, v0);  // the name's byte sum
    a0 = addiu(s0, 4);
    a1 = addiu(s4, 20);
    a2 = 16;
    jal(0x3c532c, gen::fn_memcpy_00521250);
    v0 = lw(s0 + 20);
    v0 = v0 | 0x4;  // queued
    sw(s0 + 20, v0);
    v0 = lw(s4);
    sw(s0 + 24, v0);
    v0 = lw(s4 + 4);
    sw(s0 + 28, v0);
    v0 = lw(s4 + 8);
    sw(s0 + 32, v0);
    v0 = lw(s4 + 12);
    sw(s0 + 36, v0);
    sh(s0 + 44, s3);
    sh(s0 + 46, s2);
    v0 = lw(s4 + 16);
    if (v0 != 0) {
        charge(2);
        v0 = addiu(s0, 48);
        sw(s0 + 40, v0);
    }
    charge(22);
    a0 = addiu(s6, 16);
    a1 = lw(s1);
    a2 = s1;
    jal(0x3c5388, gen::fn_sub_3C53E0_003c53e0);
    a0 = s5;
    a1 = s1;
    v0 = lw(s5 + 20);
    jalr(0x3c539c, w(v0));  // on-insert(sequence, node)
    v0 = s1;
    close_frame(7);
}

// sub_3C53E0 [nmListInsertSorted]: $a0 the list header, $a1 the key, $a2 the node: inserted before the first node whose
// key (+0) is greater (unsigned), after the tail when there is none.
void Nm::sub_3C53E0() {
    enter(5);
    open_frame(0);
    v1 = lw(a0);  // head
    bool appended = false;
    for (;;) {
        charge(2);
        if (v1 == 0) break;
        backedge();
        charge(4);
        v0 = lw(v1);
        at = sltu(a1, v0);
        if (at != 0) {
            charge(3);
            v1 = lw(v1 + 12);  // insert after its predecessor
            break;
        }
        charge(3);
        v1 = lw(v1 + 16);
        if (v1 == 0) {
            charge(5);
            a1 = lw(a0 + 4);  // after the tail
            jal(0x3c5420, gen::fn_nmListInsertAfter_003c4710);
            appended = true;
            break;
        }
    }
    if (!appended) {
        charge(3);
        a1 = v1;
        jal(0x3c543c, gen::fn_nmListInsertAfter_003c4710);
    }
    charge(4);
    close_frame(0);
}

// nmObjPayloadWord12 [nmObjPayloadWord12]: obj->payload (+36) word +12.
void Nm::nmObjPayloadWord12() {
    enter(4);
    v0 = lw(a0 + 36);
    v0 = lw(v0 + 12);
}

// sub_3C5470 / nmNodePayloadArea40: a node's payload (+20) word +40 (the step's user area) / the address payload + 40.
void Nm::sub_3C5470() {
    enter(4);
    v0 = lw(a0 + 20);
    v0 = lw(v0 + 40);
}

void Nm::nmNodePayloadArea40() {
    enter(4);
    v0 = lw(a0 + 20);
    v0 = addiu(v0, 40);
}

// sub_3C5490 [nmSequenceUpdate]: $a0 the sequence (-1 when null). Per frame:
//   1. the finished steps (payload +32): life (+46) counts down; a step at 0 is removed (sub_3C49E0);
//   2. the pending steps (payload +16): delay (+44) counts down; a due step moves to the active list (the object's
//      own list, by key) and loses flag bit 2 -- and the walk resumes after the successor nmListUnlink returned, so
//      that successor is not counted down on this frame (pass 1 skips the same way after a removal);
//   3. when the sequence's flag bit 0 is set (a previous frame ended it): clear it, empty the three lists, return 1;
//   4. the sequence function (payload +8) runs; non-zero sets flag bit 0;
//   5. every active step whose run function (nmSeqStepRun) returns a state function -- or whose flag bit 0 is set --
//      follows the returned functions until one returns 0, then it is marked done (bit 3), unlinked and moved to the
//      finished list by key (the sorted insert inlined). Returns 0.
void Nm::sub_3C5490() {
    enter(11);
    open_frame(6);
    s0 = a0;
    if (s0 == 0) {
        charge(3);
        v0 = si(-1);
        charge(10);
        close_frame(6);
        return;
    }
    // 1. the finished steps
    charge(4);
    s3 = lw(s0 + 36);  // payload
    a2 = lw(s3 + 32);
    for (;;) {
        charge(2);
        if (a2 == 0) break;
        backedge();
        charge(4);
        a0 = lw(a2 + 20);
        v1 = lhu(a0 + 46);  // life
        bool alive = false;
        if (v1 != 0) {
            charge(4);
            v0 = addiu(v1, -1);
            sh(a0 + 46, v0);
            alive = v1 != 0;
        }
        if (!alive) {
            charge(7);
            a0 = s0;
            a1 = addiu(s3, 32);
            jal(0x3c5500, gen::fn_sub_3C49E0_003c49e0);
            a2 = v0;  // the neighbour
            if (v0 == 0) continue;
        }
        charge(1);
        a2 = lw(a2 + 16);
    }
    // 2. the pending steps
    charge(4);
    s2 = lw(s0 + 36);
    s5 = lw(s2 + 16);
    for (;;) {
        charge(2);
        if (s5 == 0) break;
        backedge();
        charge(4);
        s1 = lw(s5 + 20);
        v1 = lhu(s1 + 44);  // delay
        bool waiting = false;
        if (v1 != 0) {
            charge(4);
            v0 = addiu(v1, -1);
            sh(s1 + 44, v0);
            waiting = v1 != 0;
        }
        if (!waiting) {
            charge(17);
            a0 = addiu(s2, 16);
            a1 = s5;
            jal(0x3c5558, gen::fn_nmListUnlink_003c4820);
            s4 = v0;
            a1 = lw(s5);
            a0 = addiu(s0, 4);
            a2 = s5;
            jal(0x3c5570, gen::fn_sub_3C53E0_003c53e0);
            v1 = lw(s1 + 20);
            v0 = si(-5);
            v0 = v1 & v0;  // no longer queued
            sw(s1 + 20, v0);
            s5 = s4;
            if (s4 == 0) continue;
        }
        charge(1);
        s5 = lw(s5 + 16);
    }
    // 3. ended on a previous frame
    charge(4);
    v1 = lw(s3);
    v0 = v1 & 0x1;
    if (v0 != 0) {
        charge(18);
        v0 = si(-2);
        v0 = v1 & v0;
        sw(s3, v0);
        a0 = s0;
        a1 = addiu(s3, 16);
        jal(0x3c55c4, gen::fn_sub_3C4A90_003c4a90);
        a0 = s0;
        a1 = addiu(s3, 32);
        jal(0x3c55d4, gen::fn_sub_3C4A90_003c4a90);
        a0 = s0;
        a1 = addiu(s0, 4);
        jal(0x3c55e4, gen::fn_sub_3C4A90_003c4a90);
        v0 = 1;
        charge(10);
        close_frame(6);
        return;
    }
    // 4. the sequence function
    charge(6);
    a0 = s0;
    v0 = lw(s3 + 8);
    jalr(0x3c5600, w(v0));
    if (v0 != 0) {
        charge(3);
        v0 = lw(s3);
        v0 = v0 | 0x1;
        sw(s3, v0);
    }
    // 5. the active steps
    charge(3);
    s2 = lw(s0 + 4);
    for (;;) {
        charge(2);
        if (s2 == 0) break;
        backedge();
        charge(8);
        sw(s0 + 12, s2);  // cursor = the step
        s1 = lw(s2 + 20);
        a0 = s0;
        a1 = s2;
        jal(0x3c5638, gen::fn_nmSeqStepRun_003c5840);
        bool run = v0 != 0;
        if (!run) {
            charge(4);
            v1 = lw(s1 + 20);
            v1 = v1 & 0x1;
            run = v1 != 0;
        }
        if (!run) {
            charge(1);
            s2 = lw(s2 + 16);
            continue;
        }
        for (;;) {  // the returned state functions
            charge(2);
            if (v0 == 0) break;
            charge(6);
            a0 = s0;
            a1 = s2;
            jalr(0x3c5668, w(v0));
            if (v0 == 0) break;
            backedge();
        }
        charge(15);
        v1 = lw(s1 + 20);
        v0 = si(-5);
        v0 = v1 & v0;
        sw(s1 + 20, v0);
        v0 = v0 | 0x8;  // done
        sw(s1 + 20, v0);
        s1 = lw(s2 + 16);  // the next active step
        a0 = addiu(s0, 4);
        a1 = s2;
        jal(0x3c569c, gen::fn_nmListUnlink_003c4820);
        v1 = lw(s2);        // key
        a1 = lw(s3 + 32);   // the finished list's head
        bool appended = false;
        for (;;) {
            charge(2);
            if (a1 == 0) break;
            backedge();
            charge(4);
            v0 = lw(a1);
            at = sltu(v1, v0);
            if (at != 0) {
                charge(3);
                a1 = lw(a1 + 12);
                break;
            }
            charge(3);
            a1 = lw(a1 + 16);
            if (a1 == 0) {
                charge(7);
                a0 = addiu(s3, 32);
                a1 = lw(s3 + 36);  // after the tail
                a2 = s2;
                jal(0x3c56e8, gen::fn_nmListInsertAfter_003c4710);
                appended = true;
                break;
            }
        }
        if (!appended) {
            charge(4);
            a0 = addiu(s3, 32);
            a2 = s2;
            jal(0x3c5708, gen::fn_nmListInsertAfter_003c4710);
        }
        charge(3);
        s2 = s1;
    }
    charge(1);
    v0 = 0;
    charge(10);
    close_frame(6);
}

// nmSequenceCallAll36 [nmSequenceCallAll36]: $a0 the sequence: nmSeqStepCall36 for every active step; returns 0.
void Nm::nmSequenceCallAll36() {
    enter(7);
    open_frame(2);
    s1 = a0;
    if (s1 == 0) {
        charge(5);
        k_assert(kNmSequenceFile, 462, 0x3c5788);
    }
    charge(3);
    s0 = lw(s1 + 4);
    for (;;) {
        charge(3);
        if (s0 == 0) break;
        backedge();
        charge(5);
        a0 = s1;
        a1 = s0;
        jal(0x3c57a4, gen::fn_nmSeqStepCall36_003c5870);
        s0 = lw(s0 + 16);
    }
    charge(7);
    v0 = 0;
    close_frame(2);
}

// sub_3C57E0 / nmSeqStepOnRemove / nmSeqStepRun / nmSeqStepCall36: call the step callback at `slot` of the node's payload with
// ($a0, $a1) unchanged, in a 16-byte frame; all but nmSeqStepRun (the run function) return 0.
void Nm::step_call(s32 slot, u64 first, u32 pc, bool keep_result) {
    enter(first);
    open_frame(0);
    v0 = lw(a1 + 20);
    v0 = lw(v0 + slot);
    jalr(pc, w(v0));
    if (!keep_result) v0 = 0;
    close_frame(0);
}

void Nm::sub_3C57E0() { step_call(24, 11, 0x3c57f0, false); }
void Nm::nmSeqStepOnRemove() { step_call(28, 11, 0x3c5820, false); }
void Nm::nmSeqStepRun() { step_call(32, 10, 0x3c5850, true); }
void Nm::nmSeqStepCall36() { step_call(36, 11, 0x3c5880, false); }

// nullsub_54..58: the default nmCmdList callbacks.
void Nm::nullsub() { enter(2); }

// =====================================================================================================================
// [nmCmdList]
// =====================================================================================================================

// sub_3C58F0 [nmCmdListCreate]: $a0 the create flags (bit 0: open at once and report the decided row), $a1 the user
// payload size, $a2 the visible rows, $a3 the row spacing. A list object of 72 + size payload bytes with the row
// callbacks nmCmdListOnInsert (number the row) / nmCmdListOnRemove (row removed) / nmCmdListDrawRow (draw the row, as the remove-filter);
// window state: fade lengths 5 / 5, the nullsub callbacks, state 0, flags | 0x1008 (idle, no draw in the update); bit 0
// of the create flags opens it (sub_3C6EE0) and sets flag bit 9. Returns the object.
void Nm::sub_3C58F0() {
    enter(25);
    open_frame(6);
    s3 = a0;  // flags
    s5 = a1;  // size
    s2 = a2;  // rows
    s4 = a3;  // spacing
    a0 = addiu(s5, 72);
    a1 = sx(0x3C60C0);
    a2 = sx(0x3C60F0);
    a3 = sx(0x3C6120);
    jal(0x3c593c, gen::fn_sub_3C44D0_003c44d0);
    s1 = v0;            // obj
    s0 = lw(v0 + 36);   // window state
    if (s5 != 0) {
        charge(2);
        v0 = addiu(s0, 72);
        sw(s0 + 68, v0);
    }
    charge(29);
    sw(s0 + 12, s4);
    v0 = 5;
    sh(s0 + 6, v0);
    sh(s0 + 8, v0);
    sw(s0 + 32, s2);
    v0 = sx(0x3C58C0);  // nullsub_54
    sw(s0 + 48, v0);
    v0 = sx(0x3C58D0);  // nullsub_55
    sw(s0 + 52, v0);
    v0 = sx(0x3C58A0);  // nullsub_56
    sw(s0 + 56, v0);
    v0 = sx(0x3C58B0);  // nullsub_57
    sw(s0 + 60, v0);
    v0 = sx(0x3C58E0);  // nullsub_58
    sw(s0 + 64, v0);
    sh(s0 + 10, zero);
    v0 = lw(s0);
    v0 = v0 | 0x8;
    sw(s0, v0);
    v0 = v0 | 0x1000;
    sw(s0, v0);
    v0 = s3 & 0x1;
    if (v0 != 0) {
        charge(6);
        a0 = s1;
        jal(0x3c59d4, gen::fn_sub_3C6EE0_003c6ee0);
        v0 = lw(s0);
        v0 = v0 | 0x200;
        sw(s0, v0);
    }
    charge(11);
    v0 = s1;
    close_frame(6);
}

void Nm::nmCmdListDestroy() { destroy_tail(0x3c5a28); }

// nmCmdListAddRow [nmCmdListAddRow]: $a0 the list, $a1 the key, $a2 the row's user size, $a3 a name (copied after the user
// area) or 0. Appends a node of 32 + size (+ 32) payload bytes (nmListAppendNew): payload +28 the user area (payload + 32),
// +8 the name copy; the first visible row (+44) goes back to the head. Returns the node.
void Nm::nmCmdListAddRow() {
    enter(12);
    open_frame(4);
    s0 = a0;
    s3 = a2;  // size
    s2 = a3;  // name
    a2 = addiu(s3, 32);
    if (s2 != 0) {
        charge(1);
        a2 = addiu(a2, 32);
    }
    charge(7);
    a0 = s0;
    jal(0x3c5a78, gen::fn_nmListAppendNew_003c4910);
    s1 = v0;
    v1 = lw(v0 + 20);  // payload
    if (s3 != 0) {
        charge(2);
        v0 = addiu(v1, 32);
        sw(v1 + 28, v0);
    }
    charge(2);
    if (s2 != 0) {
        charge(6);
        v0 = addu(s3, v1);
        a0 = addiu(v0, 32);
        sw(v1 + 8, a0);
        a1 = s2;
        jal(0x3c5ab0, gen::fn_strcpy_00524270);
    }
    charge(12);
    v1 = lw(s0 + 4);
    v0 = lw(s0 + 36);
    sw(v0 + 44, v1);
    v0 = s1;
    close_frame(4);
}

// sub_3C5AF0 [nmCmdListCursorUp]: moves the cursor back (nmListCursorPrev); when it leaves the window at the top the first
// visible row (+44) follows it, and a wrap to the tail scrolls the window to show the last rows.
void Nm::sub_3C5AF0() {
    enter(11);
    open_frame(2);
    s1 = a0;
    s0 = lw(a0 + 36);
    a1 = addiu(s1, 4);
    jal(0x3c5b0c, gen::fn_nmListCursorPrev_003c4d20);
    if (v0 != 0) {
        charge(8);
        a1 = lw(s0 + 44);
        v1 = lw(a1 + 20);
        a0 = lw(v1 + 12);  // the first visible row's number
        v1 = lw(v0 + 20);
        v1 = lw(v1 + 12);  // the cursor's
        at = slt(a0, v1);
        if (at == 0) {
            charge(3);
            v1 = lw(a1 + 12);
            if (v1 != 0) {
                charge(3);
                sw(s0 + 44, v1);
            }
        } else {
            charge(3);
            v1 = lw(s1 + 8);
            if (v0 == v1) {  // wrapped to the tail: rows - 1 rows above it
                charge(4);
                v1 = lw(s0 + 32);
                a0 = addiu(v1, -1);
                for (;;) {
                    charge(3);
                    if (sgn(a0) <= 0) break;
                    backedge();
                    charge(3);
                    v1 = lw(v0 + 12);
                    if (v1 == 0) break;
                    charge(2);
                    v0 = v1;
                    a0 = addiu(a0, -1);
                }
                charge(1);
                sw(s0 + 44, v0);
            }
        }
    }
    charge(6);
    close_frame(2);
}

// The body of nmCmdListCursorDown after its nmListCursorNext call ($v0 the new cursor, $s0 the window state, $s1 the list): when the
// cursor passes the last visible row the window scrolls one row down; a wrap to the head scrolls back to the top.
void Nm::down_after_next() {
    charge(11);
    a1 = lw(s0 + 44);
    v1 = lw(a1 + 20);
    a0 = lw(v1 + 12);
    v1 = lw(s0 + 32);
    v1 = addu(v1, a0);
    a0 = addiu(v1, -1);  // the last visible row's number
    v1 = lw(v0 + 20);
    v1 = lw(v1 + 12);
    v1 = sltu(v1, a0);
    if (v1 == 0) {
        charge(3);
        v1 = lhu(s1 + 16);  // count
        if (a0 != v1) {
            charge(4);
            v1 = lw(a1 + 16);
            sw(s0 + 44, v1);
        }
    } else {
        charge(3);
        v1 = lw(s1 + 4);
        if (v0 == v1) {
            charge(1);
            sw(s0 + 44, v0);
        }
    }
}

// nmCmdListCursorDown [nmCmdListCursorDown].
void Nm::nmCmdListCursorDown() {
    enter(11);
    open_frame(2);
    s1 = a0;
    s0 = lw(a0 + 36);
    a1 = addiu(s1, 4);
    jal(0x3c5bcc, gen::fn_nmListCursorNext_003c4c80);
    if (v0 != 0) down_after_next();
    charge(6);
    close_frame(2);
}

// sub_3C5C50 [nmCmdListPageDown]: from the first visible row, finds the last visible one (0 when the list is shorter),
// then moves the window and the cursor down until the cursor reaches the tail or `rows` steps were taken. Returns the
// last nmListCursorNext result (0 when nothing moved).
void Nm::sub_3C5C50() {
    enter(19);
    open_frame(6);
    s5 = a0;
    s4 = 0;
    s1 = lw(a0 + 36);
    s0 = lw(s1 + 32);  // rows
    s3 = lw(s1 + 44);  // the first visible row
    jal(0x3c5c84, gen::fn_nmCmdListVisibleRows_003c6f80);
    a0 = 0;
    v1 = addiu(v0, -1);
    bool short_list = false;
    for (;;) {
        charge(3);
        v0 = slt(a0, v1);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (s3 == 0) {
            charge(3);
            v0 = 0;
            short_list = true;
            break;
        }
        charge(2);
        s3 = lw(s3 + 16);
        a0 = addiu(a0, 1);
    }
    if (!short_list) {
        charge(3);
        s2 = 0;
        for (;;) {
            charge(3);
            v0 = slt(s2, s0);
            if (v0 == 0) break;
            backedge();
            charge(3);
            v0 = lw(s5 + 8);  // tail
            if (s3 == v0) break;
            charge(10);
            s3 = lw(s3 + 16);
            v0 = lw(s1 + 44);
            v0 = lw(v0 + 16);
            sw(s1 + 44, v0);
            a0 = s5;
            a1 = addiu(s5, 4);
            jal(0x3c5cf4, gen::fn_nmListCursorNext_003c4c80);
            s4 = v0;
            s2 = addiu(s2, 1);
        }
        charge(1);
        v0 = s4;
    }
    charge(10);
    close_frame(6);
}

// nmCmdListSelect [nmCmdListSelect]: $a0 the list, $a1 a row node, $a2 the screen line it should be on. The first visible
// row (+44) becomes the row `rows - 1` back from the node `rows - line - 1` rows below it (the head when that runs off),
// and the cursor is set to the node (sub_3C4DE0). Nothing happens for a null node.
void Nm::nmCmdListSelect() {
    enter(15);
    open_frame(4);
    s2 = a0;
    s1 = a1;  // node
    s3 = a2;  // line
    s0 = lw(a0 + 36);
    jal(0x3c5d68, gen::fn_nmCmdListVisibleRows_003c6f80);
    a2 = s1;
    if (s1 != 0) {
        charge(5);
        a1 = 0;
        v1 = subu(v0, s3);
        a0 = addiu(v1, -1);
        for (;;) {
            charge(3);
            v1 = slt(a1, a0);
            if (v1 == 0) break;
            backedge();
            charge(3);
            v1 = lw(a2 + 16);
            if (v1 == 0) break;
            charge(2);
            a2 = v1;
            a1 = addiu(a1, 1);
        }
        charge(3);
        v1 = addiu(v0, -1);
        for (;;) {
            charge(4);
            v0 = sltu(zero, a2);
            v0 = v0 ^ 0x1;
            if (v0 != 0) break;
            charge(2);
            if (v1 == 0) break;
            backedge();
            charge(2);
            v1 = addiu(v1, -1);
            a2 = lw(a2 + 12);
        }
        charge(2);
        if (a2 == 0) {
            charge(1);
            a2 = lw(s2 + 4);
        }
        charge(6);
        sw(s0 + 44, a2);
        a0 = s2;
        a1 = addiu(s2, 4);
        a2 = s1;
        jal(0x3c5df8, gen::fn_sub_3C4DE0_003c4de0);
    }
    charge(8);
    close_frame(4);
}

// nmCmdListSetDrawFunc / nmCmdListSetUpdateFunc / nmCmdListSetRowDrawFunc / nmCmdListSetRowRemoveFunc: window callback `slot` = $a1 (asserted non-null): the window draw
// (+52), the update (+56), the row draw (+48), the row-removed callback (+64).
void Nm::set_callback(s32 slot, u32 line, u32 pc) {
    enter(8);
    open_frame(2);
    s1 = a0;
    s0 = a1;
    if (s0 == 0) {
        charge(5);
        k_assert(kNmCmdListFile, line, pc);
    }
    charge(8);
    v1 = lw(s1 + 36);
    sw(v1 + slot, s0);
    close_frame(2);
}

void Nm::nmCmdListSetDrawFunc() { set_callback(52, 324, 0x3c5e4c); }
void Nm::nmCmdListSetUpdateFunc() { set_callback(56, 339, 0x3c5eac); }
void Nm::nmCmdListSetRowDrawFunc() { set_callback(48, 370, 0x3c5f0c); }
void Nm::nmCmdListSetRowRemoveFunc() { set_callback(64, 385, 0x3c5f6c); }

// nmCmdListRemoveRow [nmCmdListRemoveRow]: $a0 the list, $a1 the row node. Removes it (sub_3C49E0); unless it was the tail the
// rows after it are renumbered (payload +12 - 1) and a first visible row equal to it moves to the neighbour. Then, when
// fewer than `rows` rows follow the first visible one, the window scrolls back up as far as the rows allow.
void Nm::nmCmdListRemoveRow() {
    enter(11);
    open_frame(3);
    s2 = a1;  // row
    s0 = lw(a0 + 36);
    s1 = 1;
    v0 = lw(a0 + 8);
    if (v0 == s2) {
        charge(1);
        s1 = 0;  // the tail
    }
    charge(6);
    a1 = addiu(a0, 4);
    a2 = s2;
    jal(0x3c5fd8, gen::fn_sub_3C49E0_003c49e0);
    if (s1 != 0) {
        charge(4);
        a1 = v0;
        v1 = lw(s0 + 44);
        if (s2 == v1) {
            charge(3);
            sw(s0 + 44, v0);
        }
        for (;;) {
            charge(2);
            if (a1 == 0) break;
            backedge();
            charge(5);
            a0 = lw(a1 + 20);
            v1 = lw(a0 + 12);
            v1 = addiu(v1, -1);
            sw(a0 + 12, v1);
            a1 = lw(a1 + 16);
        }
    }
    charge(5);
    a1 = lw(s0 + 44);
    a0 = a1;
    a2 = lw(s0 + 32);  // rows
    for (;;) {
        charge(4);
        v1 = sltu(zero, a0);
        v1 = v1 ^ 0x1;
        if (v1 != 0) break;
        charge(2);
        if (a2 == 0) break;
        backedge();
        charge(2);
        a0 = lw(a0 + 16);
        a2 = addiu(a2, -1);
    }
    charge(2);
    if (a0 == 0) {
        charge(2);
        if (a2 != 0) {
            charge(2);
            for (;;) {
                charge(4);
                v1 = sltu(zero, a2);
                v1 = v1 ^ 0x1;
                if (v1 != 0) break;
                charge(2);
                if (a1 == 0) break;
                backedge();
                charge(3);
                a1 = lw(a1 + 12);
                if (a1 != 0) {
                    charge(1);
                    sw(s0 + 44, a1);
                }
                charge(1);
                a2 = addiu(a2, -1);
            }
        }
    }
    charge(7);
    close_frame(3);
}

// nmCmdListOnInsert [nmCmdListOnInsert]: numbers the new row (payload +12 = ++window count +16); returns 0.
void Nm::nmCmdListOnInsert() {
    enter(9);
    a0 = lw(a0 + 36);
    v1 = lw(a1 + 20);
    v0 = lw(a0 + 16);
    v0 = addiu(v0, 1);
    sw(a0 + 16, v0);
    sw(v1 + 12, v0);
    v0 = 0;
}

// nmCmdListOnRemove [nmCmdListOnRemove]: the window's callback +64 with ($a0, $a1); returns 0.
void Nm::nmCmdListOnRemove() {
    enter(11);
    open_frame(0);
    v0 = lw(a0 + 36);
    v0 = lw(v0 + 64);
    jalr(0x3c6100, w(v0));
    v0 = 0;
    close_frame(0);
}

// nmCmdListDrawRow [nmCmdListDrawRow]: $a0 the list, $a1 the row (the remove-filter slot: returns 0, so it never removes).
// Rows inside the window (first visible .. + rows) get their screen position (row payload +0 / +4: x / y + line *
// spacing +12, along x when flag bit 11) and colour (+16 = window +28); a row with a highlight (+8) is drawn through
// sub_3B2CB0 (the colour | 0xFFFFFF00, the cursor flag, f12 = 0); then the row callback (+48) gets (x, y, colour, list,
// row).
void Nm::nmCmdListDrawRow() {
    enter(17);
    open_frame(4);
    s3 = a0;  // list
    s2 = a1;  // row
    s1 = lw(a0 + 36);  // window
    s0 = lw(a1 + 20);  // row payload
    v0 = lw(s1 + 44);
    v0 = lw(v0 + 20);
    a2 = lw(v0 + 12);  // the first visible row's number
    v1 = lw(s0 + 12);  // this row's
    at = slt(v1, a2);
    if (at != 0) {
        charge(3);
        v0 = 0;
        charge(8);
        close_frame(4);
        return;
    }
    charge(5);
    v0 = lw(s1 + 32);
    v0 = addu(v0, a2);
    v0 = slt(v1, v0);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
        charge(8);
        close_frame(4);
        return;
    }
    charge(11);
    a1 = lw(s1 + 20);  // x
    a0 = lw(s1 + 24);  // y
    v1 = subu(v1, a2);  // the screen line
    v0 = lw(s1 + 12);   // spacing
    mult(v1, v0, v1);
    v0 = lw(s1 + 28);
    sw(s0 + 16, v0);
    v0 = lw(s1);
    v0 = v0 & 0x800;
    if (v0 != 0) {
        charge(5);
        v0 = addu(a1, v1);
        sw(s0, v0);
        sw(s0 + 4, a0);
    } else {
        charge(3);
        sw(s0, a1);
        v0 = addu(a0, v1);
        sw(s0 + 4, v0);
    }
    charge(3);
    t1 = lw(s0 + 8);
    if (t1 != 0) {
        charge(14);
        mtc1(zero, F12);
        v1 = lw(s0 + 16);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = lw(s3 + 12);  // the cursor
        a3 = s2 ^ v0;
        a3 = sltiu(a3, 1);
        a0 = lw(s0);
        a1 = lw(s0 + 4);
        t0 = 4;
        t2 = 16;
        t3 = 0;
        jal(0x3c6218, gen::fn_sub_3B2CB0_003b2cb0);
    }
    charge(9);
    a0 = lw(s0);
    a1 = lw(s0 + 4);
    a2 = lw(s0 + 16);
    a3 = s3;
    t0 = s2;
    v0 = lw(s1 + 48);
    jalr(0x3c6238, w(v0));
    v0 = 0;
    charge(8);
    close_frame(4);
}

// nmCmdListUpdate [nmCmdListUpdate]: the per-frame update -- input (sub_3C63F0), fade start / step (nmCmdListStartFade /
// sub_3C69D0), the scroll bar (nmCmdListScrollBar), the update callback (+56), the draw (nmCmdListDraw) unless flag bit 12. The
// result: with flag bit 9 the decided row's first word (nmCmdListDecidedRow) or 1 when cancelled (nmCmdListCancelled); otherwise 0 while
// active (bit 1), 3 when open (bit 0), 2 when closed.
void Nm::nmCmdListUpdate() {
    enter(25);
    open_frame(2);
    s1 = a0;
    s0 = lw(a0 + 36);
    jal(0x3c6288, gen::fn_sub_3C63F0_003c63f0);
    a0 = s1;
    jal(0x3c6294, gen::fn_nmCmdListStartFade_003c6900);
    a0 = s1;
    jal(0x3c62a0, gen::fn_sub_3C69D0_003c69d0);
    a0 = s1;
    jal(0x3c62ac, gen::fn_nmCmdListScrollBar_003c6b70);
    a0 = s1;
    v0 = lw(s0 + 56);
    jalr(0x3c62bc, w(v0));
    v0 = lw(s0);
    v0 = v0 & 0x1000;
    if (v0 == 0) {
        charge(3);
        a0 = s1;
        jal(0x3c62d8, gen::fn_nmCmdListDraw_003c6380);
    }
    charge(4);
    v0 = lw(s0);
    v0 = v0 & 0x200;
    bool done = false;
    if (v0 != 0) {
        charge(5);
        a0 = s1;
        jal(0x3c62f4, gen::fn_nmCmdListDecidedRow_003c6c50);
        if (v0 != 0) {
            charge(3);
            v0 = lw(v0);
            done = true;
        } else {
            charge(5);
            a0 = s1;
            jal(0x3c6314, gen::fn_nmCmdListCancelled_003c6c80);
            if (v0 != 0) {
                charge(3);
                v0 = 1;
                done = true;
            }
        }
    }
    if (!done) {
        charge(4);
        v1 = lw(s0);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            charge(3);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                charge(3);
                v0 = 3;
            } else {
                charge(1);
                v0 = 2;
            }
            charge(2);
        } else {
            charge(1);
            v0 = 0;
        }
    }
    charge(6);
    close_frame(2);
}

// nmCmdListDraw [nmCmdListDraw]: the draw callback (+52) with (x, y, alpha, list); with flag bit 6 the rows are drawn too
// (nmListRemoveFiltered over the row-draw filter nmCmdListDrawRow). Returns 0.
void Nm::nmCmdListDraw() {
    enter(17);
    open_frame(2);
    s1 = a0;
    s0 = lw(a0 + 36);
    a0 = lw(s0 + 20);
    a1 = lw(s0 + 24);
    a2 = lw(s0 + 28);
    a3 = s1;
    v0 = lw(s0 + 52);
    jalr(0x3c63ac, w(v0));
    v0 = lw(s0);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        charge(3);
        a0 = s1;
        jal(0x3c63c8, gen::fn_nmListRemoveFiltered_003c4e70);
    }
    charge(7);
    v0 = 0;
    close_frame(2);
}

// --- sub_3C63F0 [nmCmdListInput] and its repeated blocks ------------------------------------------------------------
// The pad words (lui 0x7E): +2380 0x7E094C / +2390 0x7E0956 the held buttons, +2382 0x7E094E / +2392 0x7E0958 the
// pressed ones, +2386 0x7E0952 / +2394 0x7E095A the repeat-pressed ones -- each pair for the two pads.

// cursor up (sub_3C5AF0); a move sets flag bit 14
void Nm::scroll_up_inline(u32 pc) {
    charge(5);
    a0 = s0;
    jal(pc, gen::fn_sub_3C5AF0_003c5af0);
    if (v0 != 0) {
        charge(5);
        v0 = lw(s3);
        v0 = v0 | 0x4000;
        sw(s3, v0);
    }
}

// cursor down: nmCmdListCursorDown inlined ($s1 the window state here); returns whether the cursor moved (the caller sets bit 13)
bool Nm::cursor_down_inline(u32 pc) {
    charge(7);
    s1 = lw(s0 + 36);
    a0 = s0;
    a1 = addiu(s0, 4);
    jal(pc, gen::fn_nmListCursorNext_003c4c80);
    if (v0 != 0) {
        charge(11);
        a1 = lw(s1 + 44);
        v1 = lw(a1 + 20);
        a0 = lw(v1 + 12);
        v1 = lw(s1 + 32);
        v1 = addu(v1, a0);
        a0 = addiu(v1, -1);
        v1 = lw(v0 + 20);
        v1 = lw(v1 + 12);
        v1 = sltu(v1, a0);
        if (v1 == 0) {
            charge(3);
            v1 = lhu(s0 + 16);
            if (a0 != v1) {
                charge(4);
                v1 = lw(a1 + 16);
                sw(s1 + 44, v1);
            }
        } else {
            charge(3);
            v1 = lw(s0 + 4);
            if (v0 == v1) {
                charge(1);
                sw(s1 + 44, v0);
            }
        }
    }
    charge(2);
    return v0 != 0;
}

// no direction held on either pad (`hold`: up, `other`: down): the cursor's end flag is cleared (nmListCursorClearEnd), so the
// next press may wrap again
void Nm::release_check(u32 hold, u32 other, u64 last, u32 pc) {
    charge(6);
    a0 = 1;
    v0 = lui(0x7e);
    v1 = lhu(v0 + 2380);
    v0 = v1 & hold;
    if (v0 == 0) {
        charge(5);
        v0 = lui(0x7e);
        v0 = lhu(v0 + 2390);
        v0 = v0 & hold;
        if (v0 == 0) {
            charge(1);
            a0 = 0;
        }
    }
    charge(2);
    if (a0 != 0) return;
    charge(4);
    v0 = v1 & other;
    v0 = sltu(zero, v0);
    if (v0 == 0) {
        charge(4);
        v0 = lui(0x7e);
        v0 = lhu(v0 + 2390);
        v0 = v0 & other;
        v0 = sltu(zero, v0);
    }
    charge(2);
    if (v0 != 0) return;
    charge(last);
    a0 = s0;
    a1 = addiu(s0, 4);
    jal(pc, gen::fn_nmListCursorClearEnd_003c4dc0);
}

// sub_3C63F0 [nmCmdListInput]: $a0 the list. Clears the per-frame result bits (4, 5, 13, 14, 15, 16); when visible (bit
// 2) and not held (bit 10): up / down (left / right with bit 11) move the cursor (bits 14 / 13); else page up (pad bit 0:
// the window and cursor go back up to `rows` rows, bit 16) / page down (bit 1: sub_3C5C50, bit 15); else decide (pressed
// 0x40: bit 4) / cancel (0x20: bit 5); else, with no direction held, the cursor's end flag is cleared. Then the input
// callback (+60). Returns 0.
void Nm::sub_3C63F0() {
    enter(33);
    open_frame(5);
    s0 = a0;
    s3 = lw(a0 + 36);  // window
    v1 = lw(s3);
    v0 = si(-17);
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = si(-33);
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = si(-16385);
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = si(-8193);
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = lui(0xfffe);
    v0 = v0 | 0xffff;
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = lui(0xffff);
    v0 = v0 | 0x7fff;
    v1 = v1 & v0;
    sw(s3, v1);
    v0 = v1 & 0x4;
    bool skip = v0 == 0;
    if (!skip) {
        charge(3);
        v0 = v1 & 0x400;
        skip = v0 != 0;
    }
    if (!skip) {
        charge(3);
        v0 = v1 & 0x800;
        if (v0 != 0) {
            // horizontal: left (0x8000) / right (0x2000)
            charge(5);
            v0 = lui(0x7e);
            a0 = lhu(v0 + 2386);
            v0 = a0 & 0x8000;
            bool up = v0 != 0;
            if (!up) {
                charge(5);
                v0 = lui(0x7e);
                v1 = lhu(v0 + 2394);
                v0 = v1 & 0x8000;
                up = v0 != 0;
            }
            if (up) {
                scroll_up_inline(0x3c64b8);
            } else {
                charge(3);
                v0 = a0 & 0x2000;
                bool down = v0 != 0;
                if (!down) {
                    charge(3);
                    v0 = v1 & 0x2000;
                    down = v0 != 0;
                }
                if (down && cursor_down_inline(0x3c6500)) {
                    charge(5);
                    v0 = lw(s3);
                    v0 = v0 | 0x2000;
                    sw(s3, v0);
                }
            }
        } else {
            // vertical: up (0x1000) / down (0x4000)
            charge(5);
            v0 = lui(0x7e);
            a0 = lhu(v0 + 2386);
            v0 = a0 & 0x1000;
            bool up = v0 != 0;
            if (!up) {
                charge(5);
                v0 = lui(0x7e);
                v1 = lhu(v0 + 2394);
                v0 = v1 & 0x1000;
                up = v0 != 0;
            }
            if (up) {
                scroll_up_inline(0x3c65b0);
            } else {
                charge(3);
                v0 = a0 & 0x4000;
                bool down = v0 != 0;
                if (!down) {
                    charge(3);
                    v0 = v1 & 0x4000;
                    down = v0 != 0;
                }
                if (down && cursor_down_inline(0x3c65f8)) {
                    charge(3);
                    v0 = lw(s3);
                    v0 = v0 | 0x2000;
                    sw(s3, v0);
                }
            }
        }
        charge(4);
        a1 = lw(s3);
        v0 = a1 & 0x4000;
        bool moved = v0 != 0;
        if (!moved) {
            charge(3);
            v0 = a1 & 0x2000;
            moved = v0 != 0;
        }
        if (!moved) {
            charge(5);
            v0 = lui(0x7e);
            a0 = lhu(v0 + 2386);
            v0 = a0 & 0x1;
            bool page_up = v0 != 0;
            if (!page_up) {
                charge(5);
                v0 = lui(0x7e);
                v1 = lhu(v0 + 2394);
                v0 = v1 & 0x1;
                page_up = v0 != 0;
            }
            if (page_up) {
                charge(6);
                v0 = 0;
                s2 = lw(s0 + 36);
                s1 = lw(s2 + 32);  // rows
                s4 = 0;
                for (;;) {
                    charge(3);
                    v1 = slt(s4, s1);
                    if (v1 == 0) break;
                    backedge();
                    charge(4);
                    a0 = lw(s2 + 44);
                    v1 = lw(s0 + 4);
                    if (a0 == v1) break;  // the window is at the top
                    charge(7);
                    v0 = lw(a0 + 12);
                    sw(s2 + 44, v0);
                    a0 = s0;
                    a1 = addiu(s0, 4);
                    jal(0x3c66f0, gen::fn_nmListCursorPrev_003c4d20);
                    s4 = addiu(s4, 1);
                }
                charge(2);
                if (v0 != 0) {
                    charge(6);
                    v1 = lw(s3);
                    v0 = lui(0x1);
                    v0 = v1 | v0;
                    sw(s3, v0);
                }
            } else {
                charge(3);
                v0 = a0 & 0x2;
                bool page_down = v0 != 0;
                if (!page_down) {
                    charge(3);
                    v0 = v1 & 0x2;
                    page_down = v0 != 0;
                }
                if (page_down) {
                    charge(5);
                    a0 = s0;
                    jal(0x3c6744, gen::fn_sub_3C5C50_003c5c50);
                    if (v0 != 0) {
                        charge(5);
                        v0 = lw(s3);
                        v0 = v0 | 0x8000;
                        sw(s3, v0);
                    }
                } else {
                    charge(5);
                    v0 = lui(0x7e);
                    a0 = lhu(v0 + 2382);
                    v0 = a0 & 0x40;
                    bool decide = v0 != 0;
                    if (!decide) {
                        charge(5);
                        v0 = lui(0x7e);
                        v1 = lhu(v0 + 2392);
                        v0 = v1 & 0x40;
                        decide = v0 != 0;
                    }
                    if (decide) {
                        charge(5);
                        v0 = lw(s3);
                        v0 = v0 | 0x10;
                        sw(s3, v0);
                    } else {
                        charge(3);
                        v0 = a0 & 0x20;
                        bool cancel = v0 != 0;
                        if (!cancel) {
                            charge(3);
                            v0 = v1 & 0x20;
                            cancel = v0 != 0;
                        }
                        if (cancel) {
                            charge(5);
                            v0 = lw(s3);
                            v0 = v0 | 0x20;
                            sw(s3, v0);
                        } else {
                            charge(3);
                            v0 = a1 & 0x800;
                            if (v0 != 0) release_check(0x8000, 0x2000, 6, 0x3c6844);
                            else release_check(0x1000, 0x4000, 4, 0x3c68bc);
                        }
                    }
                }
            }
        }
    }
    charge(14);
    a0 = s0;
    v0 = lw(s3 + 60);
    jalr(0x3c68cc, w(v0));  // input callback(list)
    v0 = 0;
    close_frame(5);
}

// nmCmdListStartFade [nmCmdListStartFade]: while idle (bit 3): an open request (bit 20) starts the fade-in (state 1, bits 2 / 20
// / 0 cleared), a close request (bit 21) the fade-out (state 3); a close-now request (bit 22) also sets bit 0.
void Nm::nmCmdListStartFade() {
    enter(5);
    v1 = lw(a0 + 36);
    a1 = lw(v1);
    a0 = a1 & 0x8;
    if (a0 == 0) {
        charge(2);
        return;
    }
    charge(4);
    a0 = lui(0x10);
    a0 = a1 & a0;
    if (a0 != 0) {
        charge(14);
        a0 = si(-5);
        a1 = a1 & a0;
        sw(v1, a1);
        a0 = lui(0xffef);
        a0 = a0 | 0xffff;
        a1 = a1 & a0;
        sw(v1, a1);
        a0 = si(-2);
        a0 = a1 & a0;
        sw(v1, a0);
        a0 = 1;
        sh(v1 + 10, a0);
    } else {
        charge(4);
        a0 = lui(0x20);
        a0 = a1 & a0;
        if (a0 != 0) {
            charge(9);
            a0 = si(-5);
            a1 = a1 & a0;
            sw(v1, a1);
            a0 = lui(0xffdf);
            a0 = a0 | 0xffff;
            a0 = a1 & a0;
            sw(v1, a0);
            a0 = 3;
            sh(v1 + 10, a0);
        }
    }
    charge(5);
    a1 = lw(v1);
    a0 = lui(0x40);
    a0 = a1 & a0;
    if (a0 != 0) {
        charge(9);
        a0 = si(-5);
        a1 = a1 & a0;
        sw(v1, a1);
        a0 = lui(0xffbf);
        a0 = a0 | 0xffff;
        a0 = a1 & a0;
        sw(v1, a0);
        a0 = a0 | 0x1;
        sw(v1, a0);
    }
    charge(2);
}

// sub_3C69D0 [nmCmdListFadeStep]: the window state machine on +10 through the jump table 0x7BB4C0 (read from guest
// memory, as the original's `jr`): 1 start the fade-in, 2 fading in (alpha +28 = 255 * frame / length; at the end:
// alpha 255, idle + visible, state 5), 3 start the fade-out, 4 fading out (alpha 255 - ...; at the end: alpha 0, idle,
// state 0); 0, 5 and anything >= 6 do nothing.
void Nm::sub_3C69D0() {
    enter(5);
    v1 = lw(a0 + 36);
    a0 = lh(v1 + 10);
    at = sltiu(a0, 6);
    if (at == 0) {
        charge(2);
        return;
    }
    charge(7);
    a1 = sx(0x7BB4C0);  // lui a1, 0x7C; addiu a1, a1, -19264
    a0 = sll(a0, 2);
    a0 = addu(a0, a1);
    a0 = lw(a0);
    switch (w(a0)) {
    case 0x3c6a00u:  // 1: start the fade-in
        charge(13);
        a1 = lw(v1);
        a0 = si(-9);
        a0 = a1 & a0;
        sw(v1, a0);
        a0 = a0 | 0x2;
        sw(v1, a0);
        a0 = a0 | 0x40;
        sw(v1, a0);
        a0 = a0 | 0x80;
        sw(v1, a0);
        a0 = 2;
        sh(v1 + 10, a0);
        sh(v1 + 4, zero);
        [[fallthrough]];
    case 0x3c6a34u:  // 2: fading in
        charge(16);
        a0 = lh(v1 + 4);
        a0 = addiu(a0, 1);
        sh(v1 + 4, a0);
        a1 = dsll32(a0, 16);
        a1 = dsra32(a1, 16);
        a0 = sll(a1, 8);
        a1 = subu(a0, a1);  // frame * 255
        a0 = lh(v1 + 6);
        div(a1, a0);
        mflo(a0);
        sw(v1 + 28, a0);
        a1 = lh(v1 + 4);
        a0 = lh(v1 + 6);
        a0 = slt(a1, a0);
        if (a0 == 0) {
            charge(15);
            a0 = 255;
            sw(v1 + 28, a0);
            sh(v1 + 4, zero);
            a0 = lw(v1);
            a0 = a0 | 0x8;
            sw(v1, a0);
            a1 = a0 | 0x4;
            sw(v1, a1);
            a0 = si(-129);
            a0 = a1 & a0;
            sw(v1, a0);
            a0 = 5;
            sh(v1 + 10, a0);
        }
        break;
    case 0x3c6ab0u:  // 3: start the fade-out
        charge(12);
        a1 = lw(v1);
        a0 = si(-9);
        a1 = a1 & a0;
        sw(v1, a1);
        a0 = si(-5);
        a0 = a1 & a0;
        sw(v1, a0);
        a0 = a0 | 0x100;
        sw(v1, a0);
        a0 = 4;
        sh(v1 + 10, a0);
        sh(v1 + 4, zero);
        [[fallthrough]];
    case 0x3c6ae0u:  // 4: fading out
        charge(18);
        a0 = lh(v1 + 4);
        a0 = addiu(a0, 1);
        sh(v1 + 4, a0);
        a1 = dsll32(a0, 16);
        a1 = dsra32(a1, 16);
        a0 = sll(a1, 8);
        a1 = subu(a0, a1);
        a0 = lh(v1 + 8);
        div(a1, a0);
        mflo(a1);
        a0 = 255;
        a0 = subu(a0, a1);
        sw(v1 + 28, a0);
        a1 = lh(v1 + 4);
        a0 = lh(v1 + 8);
        a0 = slt(a1, a0);
        if (a0 == 0) {
            charge(14);
            sw(v1 + 28, zero);
            sh(v1 + 4, zero);
            a0 = lw(v1);
            a1 = a0 | 0x8;
            sw(v1, a1);
            a0 = si(-3);
            a0 = a1 & a0;
            sw(v1, a0);
            a1 = a0 | 0x40;
            sw(v1, a1);
            a0 = si(-257);
            a0 = a1 & a0;
            sw(v1, a0);
            sh(v1 + 10, zero);
        }
        break;
    case 0x3c6b60u:  // 0, 5
        break;
    default:  // a patched table: the `jr` goes wherever it points
        rt::lookup_func(w(a0))(c);
        return;
    }
    charge(2);
}

// nmCmdListScrollBar [nmCmdListScrollBar]: the two 16.16 ratios at window +36 / +40 -- (cursor row - 1) * 0xFFFF / (count - 1)
// and (first visible row - 1) * 0xFFFF / (count - visible rows); 0 when a divisor is not positive or the list is empty.
// Returns 0.
void Nm::nmCmdListScrollBar() {
    enter(10);
    open_frame(3);
    a2 = lw(a0 + 36);
    s1 = addiu(a2, 36);
    v1 = lhu(a0 + 16);  // count
    if (v1 == 0) {
        charge(5);
        sw(s1, zero);
        sw(s1 + 4, zero);
        v0 = 0;
    } else {
        charge(11);
        v0 = lw(a0 + 12);
        v0 = lw(v0 + 20);
        v0 = lw(v0 + 12);
        a1 = addiu(v0, -1);  // the cursor's row - 1
        v0 = lw(a2 + 44);
        v0 = lw(v0 + 20);
        v0 = lw(v0 + 12);
        s0 = addiu(v0, -1);  // the first visible row - 1
        v1 = addiu(v1, -1);
        if (sgn(v1) > 0) {
            charge(7);
            v0 = sll(a1, 16);
            v0 = subu(v0, a1);
            div(v0, v1);
            mflo(v0);
            sw(s1, v0);
        } else {
            charge(1);
            sw(s1, zero);
        }
        charge(6);
        s2 = lhu(a0 + 16);
        jal(0x3c6bfc, gen::fn_nmCmdListVisibleRows_003c6f80);
        v1 = subu(s2, v0);
        if (sgn(v1) > 0) {
            charge(7);
            v0 = sll(s0, 16);
            v0 = subu(v0, s0);
            div(v0, v1);
            mflo(v0);
            sw(s1 + 4, v0);
        } else {
            charge(1);
            sw(s1 + 4, zero);
        }
        charge(1);
        v0 = 0;
    }
    charge(7);
    close_frame(3);
}

// nmCmdListDecidedRow / nmCmdListMovedDownRow / nmCmdListScrolledRow: the cursor (+12) when the window flag `mask` is set (bits 4 / 13 / 14), else 0.
void Nm::flag_row(u32 mask) {
    enter(5);
    v0 = lw(a0 + 36);
    v0 = lw(v0);
    v0 = v0 & mask;
    if (v0 != 0) {
        charge(3);
        v0 = lw(a0 + 12);
    } else {
        charge(1);
        v0 = 0;
    }
    charge(2);
}

void Nm::nmCmdListDecidedRow() { flag_row(0x10); }
void Nm::nmCmdListMovedDownRow() { flag_row(0x2000); }
void Nm::nmCmdListScrolledRow() { flag_row(0x4000); }

// nmCmdListCancelled / nmCmdListPagedDown / nmCmdListMovedUp: the window flag word & mask (bits 5 / 15 / 16).
void Nm::nmCmdListCancelled() {
    enter(5);
    v0 = lw(a0 + 36);
    v0 = lw(v0);
    v0 = v0 & 0x20;
}

void Nm::nmCmdListPagedDown() {
    enter(5);
    v0 = lw(a0 + 36);
    v0 = lw(v0);
    v0 = v0 & 0x8000;
}

void Nm::nmCmdListMovedUp() {
    enter(6);
    v0 = lw(a0 + 36);
    v1 = lw(v0);
    v0 = lui(0x1);
    v0 = v1 & v0;
}

// nmCmdListSetPosition [nmCmdListSetPosition]: window +20 / +24 = $a1 / $a2.
void Nm::nmCmdListSetPosition() {
    enter(5);
    v1 = lw(a0 + 36);
    sw(v1 + 20, a1);
    sw(v1 + 24, a2);
}

// sub_3C6D60 [nmCmdListSetFlags]: window flags |= $a1; returns 0.
void Nm::sub_3C6D60() {
    enter(7);
    v1 = lw(a0 + 36);
    v0 = lw(v1);
    v0 = v0 | a1;
    sw(v1, v0);
    v0 = 0;
}

// nmCmdListStatus / nmCmdListStatus28 [nmCmdListStatus]: bit 31 input held off (flag 10), bit 30 ready (flag 2); then active (flag
// 1): 0x14 fading out (flag 8), 0xC fading in (flag 7), else 1; inactive: 2. nmCmdListStatus28 keeps only the low 28 bits
// (dsll32 / dsrl32 by 4 shift by 36: the two top bits and the sign extension go); its arms branch straight to that tail,
// so the two block layouts differ.
void Nm::status_word(bool top_cleared) {
    enter(6);
    a1 = 0;
    v0 = lw(a0 + 36);
    v1 = lw(v0);
    v0 = v1 & 0x400;
    if (v0 != 0) {
        charge(2);
        v0 = lui(0x8000);
        a1 = a1 | v0;
    }
    charge(3);
    v0 = v1 & 0x4;
    if (v0 != 0) {
        charge(2);
        v0 = lui(0x4000);
        a1 = a1 | v0;
    }
    charge(3);
    v0 = v1 & 0x2;
    if (v0 == 0) {
        charge(1);
        v0 = a1 | 0x2;
    } else {
        charge(3);
        v0 = v1 & 0x100;
        if (v0 != 0) {
            charge(3);
            v0 = a1 | 0x14;
        } else {
            charge(3);
            v0 = v1 & 0x80;
            if (v0 != 0) {
                charge(3);
                v0 = a1 | 0xc;
                if (!top_cleared) charge(2);  // nmCmdListStatus: the inner arms' shared `b`
            } else if (top_cleared) {
                charge(3);
                v0 = a1 | 0x1;
            } else {
                charge(1);
                v0 = a1 | 0x1;
                charge(2);
            }
        }
    }
    if (top_cleared) {
        charge(4);
        v0 = dsll32(v0, 4);
        v0 = dsrl32(v0, 4);
    } else {
        charge(2);
    }
}

void Nm::nmCmdListStatus() { status_word(false); }
void Nm::nmCmdListStatus28() { status_word(true); }

// nmCmdListHold / nmCmdListRelease [nmCmdListHold / Release]: window flag bit 10 set / cleared.
void Nm::nmCmdListHold() {
    enter(6);
    a0 = lw(a0 + 36);
    v1 = lw(a0);
    v1 = v1 | 0x400;
    sw(a0, v1);
}

void Nm::nmCmdListRelease() {
    enter(7);
    a1 = lw(a0 + 36);
    a0 = lw(a1);
    v1 = si(-1025);
    v1 = a0 & v1;
    sw(a1, v1);
}

// sub_3C6EE0 [nmCmdListOpen]: requests the fade-in (bit 20) unless active (bit 1).
void Nm::sub_3C6EE0() {
    enter(5);
    a1 = lw(a0 + 36);
    a0 = lw(a1);
    v1 = a0 & 0x2;
    if (v1 == 0) {
        charge(3);
        v1 = lui(0x10);
        v1 = a0 | v1;
        sw(a1, v1);
    }
    charge(2);
}

// nmCmdListClose [nmCmdListClose]: requests the fade-out (bit 21) when active and not already closing (bit 8).
void Nm::nmCmdListClose() {
    enter(5);
    a1 = lw(a0 + 36);
    a0 = lw(a1);
    v1 = a0 & 0x2;
    if (v1 != 0) {
        charge(3);
        v1 = a0 & 0x100;
        if (v1 == 0) {
            charge(3);
            v1 = lui(0x20);
            v1 = a0 | v1;
            sw(a1, v1);
        }
    }
    charge(2);
}

// nmCmdListCloseNow [nmCmdListCloseNow]: bits 22 and 21.
void Nm::nmCmdListCloseNow() {
    enter(10);
    a1 = lw(a0 + 36);
    a0 = lw(a1);
    v1 = lui(0x40);
    a0 = a0 | v1;
    sw(a1, a0);
    v1 = lui(0x20);
    v1 = a0 | v1;
    sw(a1, v1);
}

// nmCmdListVisibleRows [nmCmdListVisibleRows]: min(rows (+32, signed), count (list +16)).
void Nm::nmCmdListVisibleRows() {
    enter(6);
    v1 = lhu(a0 + 16);
    v0 = lw(a0 + 36);
    v0 = lw(v0 + 32);
    at = slt(v0, v1);
    if (at != 0) {
        charge(2);
    } else {
        charge(1);
        v0 = v1;
    }
    charge(2);
}

// nmCmdListCursorLine [nmCmdListCursorLine]: the number of steps back from the cursor to the first visible row (0 when there is
// none; the walk stops at the head).
void Nm::nmCmdListCursorLine() {
    enter(6);
    v0 = 0;
    v1 = lw(a0 + 36);
    a1 = lw(a0 + 12);  // cursor
    a0 = lw(v1 + 44);  // the first visible row
    if (a0 == 0) {
        charge(2);
        charge(2);
        return;
    }
    for (;;) {
        charge(4);
        v1 = sltu(zero, a1);
        v1 = v1 ^ 0x1;
        if (v1 != 0) break;
        charge(2);
        if (a0 == a1) break;
        backedge();
        charge(2);
        a1 = lw(a1 + 12);
        v0 = addiu(v0, 1);
    }
    charge(2);
}

// nmCmdListSort [nmCmdListSort]: $a0 the list, $a1 a qsort comparator: sorts (sub_3C4FC0), renumbers the rows 1.., puts
// the window at the head and recomputes the scroll bar (nmCmdListScrollBar).
void Nm::nmCmdListSort() {
    enter(10);
    open_frame(1);
    s0 = a0;
    jal(0x3c7010, gen::fn_sub_3C4FC0_003c4fc0);
    v1 = 1;
    a0 = lw(s0 + 4);
    for (;;) {
        charge(3);
        if (a0 == 0) break;
        backedge();
        charge(4);
        v0 = lw(a0 + 20);
        sw(v0 + 12, v1);
        a0 = lw(a0 + 16);
        v1 = addiu(v1, 1);
    }
    charge(11);
    v1 = lw(s0 + 4);
    v0 = lw(s0 + 36);
    sw(v0 + 44, v1);
    a0 = s0;
    jal(0x3c7054, gen::fn_nmCmdListScrollBar_003c6b70);
    close_frame(1);
}

// sub_3C7070 [quaternion slerp]: $a0 out, $a1 q0, $a2 q1, $f12 t. cos = the dot product as compiled (the x*x' product
// counted twice); for cos in (gp-31956, gp-32472) the spherical weights sin((1-t)w) / sin(w), sin(tw) / sin(w) with
// w = acos(cos); otherwise the linear blend renormalised. The linear branch reads $f5, which nothing in the function
// writes: the caller's value (kept, as the original).
void Nm::sub_3C7070() {
    enter(27);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s2 = a0;  // out
    s1 = a1;  // q0
    s0 = a2;  // q1
    mov_s(F20, F12);  // t
    lwc1(F4, a1);
    lwc1(F1, a2 + 8);
    lwc1(F0, a1 + 8);
    mul_s(F3, F0, F1);
    lwc1(F2, a2);
    lwc1(F1, a1 + 4);
    lwc1(F0, a2 + 4);
    mula_s(F1, F0);
    madd_s(F0, F4, F2);
    add_s(F0, F3, F0);
    add_s(F12, F3, F0);
    lwc1(F0, gp - 31956);
    c_le_s(F12, F0);
    bool spherical = false;
    if (!cop1_cond()) {
        charge(4);
        lwc1(F0, gp - 32472);
        c_lt_s(F12, F0);
        spherical = cop1_cond();
    }
    if (spherical) {
        charge(46);
        jal(0x3c70ec, gen::fn_acosf_0052e9e8);
        mov_s(F22, F0);  // w
        v0 = lui(0x3f80);
        mtc1(v0, F0);
        sub_s(F0, F0, F20);
        mul_s(F12, F22, F0);
        jal(0x3c710c, gen::fn_sinf_0052e878);
        mov_s(F21, F0);  // sin((1 - t) w)
        mul_s(F12, F22, F20);
        jal(0x3c711c, gen::fn_sinf_0052e878);
        mov_s(F20, F0);  // sin(t w)
        mov_s(F12, F22);
        jal(0x3c712c, gen::fn_sinf_0052e878);  // sin(w) in $f0
        for (s32 k = 0; k < 16; k += 4) {
            lwc1(F2, s1 + k);
            lwc1(F1, s0 + k);
            mula_s(F1, F20);
            madd_s(F1, F2, F21);
            div_s(k == 12 ? F0 : F1, F1, F0);
            swc1(k == 12 ? F0 : F1, s2 + k);
        }
    } else {
        charge(39);
        v1 = lui(0x3f80);
        mtc1(v1, F0);
        sub_s(F1, F0, F20);  // 1 - t
        mula_s(F5, F20);
        madd_s(F0, F4, F1);
        swc1(F0, s2);
        for (s32 k = 4; k < 16; k += 4) {
            lwc1(F0, s1 + k);
            mula_s(F5, F20);
            madd_s(F0, F0, F1);
            swc1(F0, s2 + k);
        }
        lwc1(F3, s2 + 4);
        lwc1(F2, s2);
        lwc1(F1, s2 + 8);
        lwc1(F0, s2 + 12);
        mula_s(F3, F3);
        madda_s(F2, F2);
        madda_s(F1, F1);
        madd_s(F0, F0, F0);
        sqrt_s(F1, F0);  // the length
        div_s(F0, F2, F1);
        swc1(F0, s2);
        for (s32 k = 4; k < 16; k += 4) {
            lwc1(F0, s2 + k);
            div_s(F0, F0, F1);
            swc1(F0, s2 + k);
        }
    }
    charge(10);
    ra = ld(sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 80);
}

// =====================================================================================================================
// [msgwin] the shared message-window record 0x95BE90 (sub_3C7D50 returns it; the null checks below are never taken)
// =====================================================================================================================

// msgWinReset [msgWinReset]: msgWinRecordInit(0x95BE90).
void Nm::msgWinReset() {
    enter(10);
    open_frame(0);
    a0 = sx(kMsgWinRecord);  // lui a0, 0x96; addiu a0, a0, -16752
    jal(0x3c7280, gen::fn_msgWinRecordInit_003c72a0);
    close_frame(0);
}

// msgWinRecordInit [msgWinRecordInit]: handle -1, the two bytes +4 / +5 0, +8 -1, +12 / +13 1.
void Nm::msgWinRecordInit() {
    enter(2);
    if (a0 != 0) {
        charge(8);
        v1 = si(-1);
        sw(a0, v1);
        sb(a0 + 4, zero);
        sb(a0 + 5, zero);
        sw(a0 + 8, v1);
        v1 = 1;
        sb(a0 + 12, v1);
        sb(a0 + 13, v1);
    }
    charge(2);
}

// sub_3C72D0 [msgWinOpen]: $a0 a BMD. Re-initialises the record (msgWinRecordInit inlined), and when it holds no handle
// binds the BMD (itfMesMngInitialize) and sets the window type 0 (sub_3C8230); returns 1 then, else 0.
void Nm::sub_3C72D0() {
    enter(9);
    open_frame(2);
    s0 = a0;
    v0 = sx(kMsgWinRecord);
    if (v0 != 0) {
        charge(14);
        v1 = si(-1);
        v0 = lui(0x96);  // each store re-loads 0x960000; the stores go to 0x95BE90 + n
        sw(v0 - 16752, v1);
        sb(v0 - 16748, zero);
        sb(v0 - 16747, zero);
        sw(v0 - 16744, v1);
        v1 = 1;
        sb(v0 - 16740, v1);
        sb(v0 - 16739, v1);
    }
    charge(6);
    jal(0x3c732c, gen::fn_sub_3C7D50_003c7d50);
    s1 = v0;
    v0 = lw(v0);  // the handle
    if (sgn(v0) < 0) {
        charge(11);
        a0 = s0;
        jal(0x3c7348, gen::fn_itfMesMngInitialize_003a2d80);
        sw(s1, v0);
        a0 = s1;
        a1 = 0;
        jal(0x3c735c, gen::fn_sub_3C8230_003c8230);
        v0 = 1;
    } else {
        charge(1);
        v0 = 0;
    }
    charge(6);
    close_frame(2);
}

// msgWinSetStateFlags / sub_3C73E0 [msgWinSetStateFlags / ClearStateFlags]: `op`(handle, $a0) when the record holds a handle.
void Nm::state_flags(u32 pc, rt::Fn op, u32 op_pc) {
    enter(8);
    open_frame(1);
    s0 = a0;
    jal(pc, gen::fn_sub_3C7D50_003c7d50);
    if (v0 != 0) {
        charge(3);
        a0 = lw(v0);
        if (sgn(a0) >= 0) {
            charge(3);
            a1 = s0;
            jal(op_pc, op);
        }
    }
    charge(5);
    close_frame(1);
}

void Nm::msgWinSetStateFlags() { state_flags(0x3c73a0, gen::fn_itfMesMngSetStateFlags_003a3e10, 0x3c73c0); }
void Nm::sub_3C73E0() { state_flags(0x3c73f0, gen::fn_itfMesMngClearStateFlags_003a3e90, 0x3c7410); }

// msgWinRequestMessage [msgWinRequestMessage]: $a0 a message index. With a handle: window type 4 (sub_3A4360), state flag bit 21,
// itfMesMngRequestMessage(handle, index, 0), selection word -1, busy byte 1; returns 1 (0 without a handle).
void Nm::msgWinRequestMessage() {
    enter(10);
    open_frame(2);
    s1 = a0;
    jal(0x3c7444, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        a0 = lw(s0);
        if (sgn(a0) < 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(18);
            a1 = 4;
            jal(0x3c7480, gen::fn_sub_3A4360_003a4360);
            a0 = lw(s0);
            a1 = lui(0x20);
            jal(0x3c7490, gen::fn_itfMesMngSetStateFlags_003a3e10);
            a0 = lw(s0);
            a1 = s1;
            a2 = 0;
            jal(0x3c74a4, gen::fn_itfMesMngRequestMessage_003a30c0);
            a0 = lw(s0);
            a1 = si(-1);
            jal(0x3c74b4, gen::fn_itfMesMngSetSelectWord84_003a27c0);
            v0 = 1;
            sb(s0 + 4, v0);
        }
    }
    charge(6);
    close_frame(2);
}

// sub_3C74E0 [msgWinRequestSelection]: $a0 the default; with a handle stores it (+8) and the current selection
// (msgWinGetSelection) in +13; returns 1 (0 without a handle).
void Nm::sub_3C74E0() {
    enter(10);
    open_frame(2);
    s1 = a0;
    jal(0x3c74f4, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        v0 = lw(s0);
        if (sgn(v0) < 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(5);
            sw(s0 + 8, s1);
            jal(0x3c7530, gen::fn_msgWinGetSelection_003c75b0);
            sb(s0 + 13, v0);
            v0 = 1;
        }
    }
    charge(6);
    close_frame(2);
}

// msgWinSetType [msgWinSetType]: record +12 = $a0 when there is a handle.
void Nm::msgWinSetType() {
    enter(8);
    open_frame(1);
    s0 = a0;
    jal(0x3c7570, gen::fn_sub_3C7D50_003c7d50);
    if (v0 != 0) {
        charge(3);
        v1 = lw(v0);
        if (sgn(v1) >= 0) {
            charge(1);
            sb(v0 + 12, s0);
        }
    }
    charge(5);
    close_frame(1);
}

// msgWinGetSelection [msgWinGetSelection]: itfMesMngGetSelection(handle), -1 without a handle.
void Nm::msgWinGetSelection() {
    enter(6);
    open_frame(0);
    jal(0x3c75b8, gen::fn_sub_3C7D50_003c7d50);
    if (v0 == 0) {
        charge(3);
        v0 = si(-1);
    } else {
        charge(3);
        a0 = lw(v0);
        if (sgn(a0) < 0) {
            charge(3);
            v0 = si(-1);
        } else {
            charge(2);
            jal(0x3c75ec, gen::fn_itfMesMngGetSelection_003a2830);
        }
    }
    charge(4);
    close_frame(0);
}

// msgWinLastSelection [msgWinLastSelection]: the signed byte +13 (1 without a record).
void Nm::msgWinLastSelection() {
    enter(6);
    open_frame(0);
    jal(0x3c7618, gen::fn_sub_3C7D50_003c7d50);
    if (v0 == 0) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = lb(v0 + 13);
    }
    charge(4);
    close_frame(0);
}

// msgWinClose [msgWinClose]: $a0 non-zero also closes the slot's window (sub_3A2A30). With a handle: busy 0
// (itfMesMngSetBusy), the panels released (sub_3A3420), the record's panel closed (sub_3C7C90(1)), busy byte 0;
// returns 1 (0 without a handle).
void Nm::msgWinClose() {
    enter(10);
    open_frame(2);
    s1 = a0;
    jal(0x3c7664, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        a0 = lw(s0);
        if (sgn(a0) < 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(5);
            a1 = 0;
            jal(0x3c76a0, gen::fn_itfMesMngSetBusy_003a25f0);
            if (s1 != 0) {
                charge(3);
                a0 = lw(s0);
                jal(0x3c76b4, gen::fn_sub_3A2A30_003a2a30);
            }
            charge(9);
            a0 = lw(s0);
            a1 = 0;
            jal(0x3c76c4, gen::fn_sub_3A3420_003a3420);
            a0 = 1;
            jal(0x3c76d0, gen::fn_sub_3C7C90_003c7c90);
            sb(s0 + 4, zero);
            v0 = 1;
        }
    }
    charge(6);
    close_frame(2);
}

// sub_3C7700 [msgWinCloseAll]: msgWinClose(1) with its own frame and block layout.
void Nm::sub_3C7700() {
    enter(8);
    open_frame(1);
    jal(0x3c770c, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        a0 = lw(s0);
        if (sgn(a0) < 0) {
            charge(3);
            v0 = 0;
        } else {
            charge(15);
            a1 = 0;
            jal(0x3c7748, gen::fn_itfMesMngSetBusy_003a25f0);
            a0 = lw(s0);
            jal(0x3c7754, gen::fn_sub_3A2A30_003a2a30);
            a0 = lw(s0);
            a1 = 0;
            jal(0x3c7764, gen::fn_sub_3A3420_003a3420);
            a0 = 1;
            jal(0x3c7770, gen::fn_sub_3C7C90_003c7c90);
            sb(s0 + 4, zero);
            v0 = 1;
        }
    }
    charge(5);
    close_frame(1);
}

}  // namespace nm::detail
// =====================================================================================================================
// The public entry points (nm_message.h) and the recompiled program's entry points
// =====================================================================================================================

u64 nmListInsertAfter(EEContext& ctx, u64 list, u64 after, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, list);
    ee::core::set_gpr64(ctx, GPR_A1, after);
    ee::core::set_gpr64(ctx, GPR_A2, node);
    nm::detail::Nm(ctx).nmListInsertAfter();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListUnlink(EEContext& ctx, u64 list, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, list);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmListUnlink();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListAppendNew(EEContext& ctx, u64 obj, u64 key, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, key);
    ee::core::set_gpr64(ctx, GPR_A2, size);
    nm::detail::Nm(ctx).nmListAppendNew();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListFindByKey(EEContext& ctx, u64 obj, u64 list, u64 key) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    ee::core::set_gpr64(ctx, GPR_A2, key);
    nm::detail::Nm(ctx).nmListFindByKey();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListFindByWord4(EEContext& ctx, u64 obj, u64 list, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    ee::core::set_gpr64(ctx, GPR_A2, value);
    nm::detail::Nm(ctx).nmListFindByWord4();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListCursorNext(EEContext& ctx, u64 obj, u64 list) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    nm::detail::Nm(ctx).nmListCursorNext();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListCursorPrev(EEContext& ctx, u64 obj, u64 list) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    nm::detail::Nm(ctx).nmListCursorPrev();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListCursorClearEnd(EEContext& ctx, u64 obj, u64 list) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    nm::detail::Nm(ctx).nmListCursorClearEnd();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C4DE0(EEContext& ctx, u64 obj, u64 list, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    ee::core::set_gpr64(ctx, GPR_A2, node);
    nm::detail::Nm(ctx).sub_3C4DE0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListCursorSeek(EEContext& ctx, u64 obj, u64 list, u64 index) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    ee::core::set_gpr64(ctx, GPR_A2, index);
    nm::detail::Nm(ctx).nmListCursorSeek();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListCursorHead(EEContext& ctx, u64 obj, u64 list) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    nm::detail::Nm(ctx).nmListCursorHead();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C4E60(EEContext& ctx, u64 obj, u64 list) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, list);
    nm::detail::Nm(ctx).sub_3C4E60();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListRemoveFiltered(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmListRemoveFiltered();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmByteSum(EEContext& ctx, u64 str) {
    ee::core::set_gpr64(ctx, GPR_A0, str);
    nm::detail::Nm(ctx).nmByteSum();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmListRebuild(EEContext& ctx, u64 obj, u64 nodes, u64 count) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, nodes);
    ee::core::set_gpr64(ctx, GPR_A2, count);
    nm::detail::Nm(ctx).nmListRebuild();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSeqNullStep(EEContext& ctx) {
    nm::detail::Nm(ctx).nmSeqNullStep();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSequenceCreate(EEContext& ctx, u64 func, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, func);
    ee::core::set_gpr64(ctx, GPR_A1, size);
    nm::detail::Nm(ctx).nmSequenceCreate();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C5210(EEContext& ctx) {
    nm::detail::Nm(ctx).sub_3C5210();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSequenceDestroy(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmSequenceDestroy();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSequenceAddStep(EEContext& ctx, u64 obj, u64 key, u64 desc, u64 delay, u64 life) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, key);
    ee::core::set_gpr64(ctx, GPR_A2, desc);
    ee::core::set_gpr64(ctx, GPR_A3, delay);
    ee::core::set_gpr64(ctx, GPR_T0, life);
    nm::detail::Nm(ctx).nmSequenceAddStep();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C53E0(EEContext& ctx, u64 list, u64 key, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, list);
    ee::core::set_gpr64(ctx, GPR_A1, key);
    ee::core::set_gpr64(ctx, GPR_A2, node);
    nm::detail::Nm(ctx).sub_3C53E0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmObjPayloadWord12(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmObjPayloadWord12();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C5470(EEContext& ctx, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    nm::detail::Nm(ctx).sub_3C5470();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmNodePayloadArea40(EEContext& ctx, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    nm::detail::Nm(ctx).nmNodePayloadArea40();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C5490(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C5490();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSequenceCallAll36(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmSequenceCallAll36();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C57E0(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).sub_3C57E0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSeqStepOnRemove(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmSeqStepOnRemove();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSeqStepRun(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmSeqStepRun();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmSeqStepCall36(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmSeqStepCall36();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nullsub_56(EEContext& ctx) {
    nm::detail::Nm(ctx).nullsub();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nullsub_57(EEContext& ctx) {
    nm::detail::Nm(ctx).nullsub();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nullsub_54(EEContext& ctx) {
    nm::detail::Nm(ctx).nullsub();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nullsub_55(EEContext& ctx) {
    nm::detail::Nm(ctx).nullsub();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nullsub_58(EEContext& ctx) {
    nm::detail::Nm(ctx).nullsub();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C58F0(EEContext& ctx, u64 flags, u64 size, u64 rows, u64 spacing) {
    ee::core::set_gpr64(ctx, GPR_A0, flags);
    ee::core::set_gpr64(ctx, GPR_A1, size);
    ee::core::set_gpr64(ctx, GPR_A2, rows);
    ee::core::set_gpr64(ctx, GPR_A3, spacing);
    nm::detail::Nm(ctx).sub_3C58F0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListDestroy(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListDestroy();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListAddRow(EEContext& ctx, u64 obj, u64 key, u64 size, u64 name) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, key);
    ee::core::set_gpr64(ctx, GPR_A2, size);
    ee::core::set_gpr64(ctx, GPR_A3, name);
    nm::detail::Nm(ctx).nmCmdListAddRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C5AF0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C5AF0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListCursorDown(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListCursorDown();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C5C50(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C5C50();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSelect(EEContext& ctx, u64 obj, u64 node, u64 line) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    ee::core::set_gpr64(ctx, GPR_A2, line);
    nm::detail::Nm(ctx).nmCmdListSelect();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSetDrawFunc(EEContext& ctx, u64 obj, u64 func) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, func);
    nm::detail::Nm(ctx).nmCmdListSetDrawFunc();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSetUpdateFunc(EEContext& ctx, u64 obj, u64 func) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, func);
    nm::detail::Nm(ctx).nmCmdListSetUpdateFunc();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSetRowDrawFunc(EEContext& ctx, u64 obj, u64 func) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, func);
    nm::detail::Nm(ctx).nmCmdListSetRowDrawFunc();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSetRowRemoveFunc(EEContext& ctx, u64 obj, u64 func) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, func);
    nm::detail::Nm(ctx).nmCmdListSetRowRemoveFunc();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListRemoveRow(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmCmdListRemoveRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListOnInsert(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmCmdListOnInsert();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListOnRemove(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmCmdListOnRemove();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListDrawRow(EEContext& ctx, u64 obj, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, node);
    nm::detail::Nm(ctx).nmCmdListDrawRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListUpdate(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListUpdate();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListDraw(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListDraw();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C63F0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C63F0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListStartFade(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListStartFade();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C69D0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C69D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListScrollBar(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListScrollBar();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListDecidedRow(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListDecidedRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListCancelled(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListCancelled();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListPagedDown(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListPagedDown();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListMovedUp(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListMovedUp();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListMovedDownRow(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListMovedDownRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListScrolledRow(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListScrolledRow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSetPosition(EEContext& ctx, u64 obj, u64 x, u64 y) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, x);
    ee::core::set_gpr64(ctx, GPR_A2, y);
    nm::detail::Nm(ctx).nmCmdListSetPosition();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C6D60(EEContext& ctx, u64 obj, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, flags);
    nm::detail::Nm(ctx).sub_3C6D60();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListStatus(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListStatus();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListStatus28(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListStatus28();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListHold(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListHold();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListRelease(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListRelease();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C6EE0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).sub_3C6EE0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListClose(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListClose();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListCloseNow(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListCloseNow();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListVisibleRows(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListVisibleRows();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListCursorLine(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    nm::detail::Nm(ctx).nmCmdListCursorLine();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 nmCmdListSort(EEContext& ctx, u64 obj, u64 compare) {
    ee::core::set_gpr64(ctx, GPR_A0, obj);
    ee::core::set_gpr64(ctx, GPR_A1, compare);
    nm::detail::Nm(ctx).nmCmdListSort();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C7070(EEContext& ctx, u64 out, u64 q0, u64 q1) {
    ee::core::set_gpr64(ctx, GPR_A0, out);
    ee::core::set_gpr64(ctx, GPR_A1, q0);
    ee::core::set_gpr64(ctx, GPR_A2, q1);
    nm::detail::Nm(ctx).sub_3C7070();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinReset(EEContext& ctx) {
    nm::detail::Nm(ctx).msgWinReset();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinRecordInit(EEContext& ctx, u64 rec) {
    ee::core::set_gpr64(ctx, GPR_A0, rec);
    nm::detail::Nm(ctx).msgWinRecordInit();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C72D0(EEContext& ctx, u64 bmd) {
    ee::core::set_gpr64(ctx, GPR_A0, bmd);
    nm::detail::Nm(ctx).sub_3C72D0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinSetStateFlags(EEContext& ctx, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, flags);
    nm::detail::Nm(ctx).msgWinSetStateFlags();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C73E0(EEContext& ctx, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, flags);
    nm::detail::Nm(ctx).sub_3C73E0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinRequestMessage(EEContext& ctx, u64 message) {
    ee::core::set_gpr64(ctx, GPR_A0, message);
    nm::detail::Nm(ctx).msgWinRequestMessage();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C74E0(EEContext& ctx, u64 selection) {
    ee::core::set_gpr64(ctx, GPR_A0, selection);
    nm::detail::Nm(ctx).sub_3C74E0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinSetType(EEContext& ctx, u64 type) {
    ee::core::set_gpr64(ctx, GPR_A0, type);
    nm::detail::Nm(ctx).msgWinSetType();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinGetSelection(EEContext& ctx) {
    nm::detail::Nm(ctx).msgWinGetSelection();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinLastSelection(EEContext& ctx) {
    nm::detail::Nm(ctx).msgWinLastSelection();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 msgWinClose(EEContext& ctx, u64 close_panel) {
    ee::core::set_gpr64(ctx, GPR_A0, close_panel);
    nm::detail::Nm(ctx).msgWinClose();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_3C7700(EEContext& ctx) {
    nm::detail::Nm(ctx).sub_3C7700();
    return ee::core::gpr64(ctx, GPR_V0);
}

}  // namespace p3fes::game

namespace p3fes::recomp_gen {
namespace pg = ::p3fes::game;

void fn_nmListInsertAfter_003c4710(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListInsertAfter(); }
void fn_nmListUnlink_003c4820(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListUnlink(); }
void fn_nmListAppendNew_003c4910(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListAppendNew(); }
void fn_nmListFindByKey_003c4b50(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListFindByKey(); }
void fn_nmListFindByWord4_003c4bf0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListFindByWord4(); }
void fn_nmListCursorNext_003c4c80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListCursorNext(); }
void fn_nmListCursorPrev_003c4d20(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListCursorPrev(); }
void fn_nmListCursorClearEnd_003c4dc0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListCursorClearEnd(); }
void fn_sub_3C4DE0_003c4de0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C4DE0(); }
void fn_nmListCursorSeek_003c4df0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListCursorSeek(); }
void fn_nmListCursorHead_003c4e50(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListCursorHead(); }
void fn_sub_3C4E60_003c4e60(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C4E60(); }
void fn_nmListRemoveFiltered_003c4e70(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListRemoveFiltered(); }
void fn_nmByteSum_003c4f80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmByteSum(); }
void fn_nmListRebuild_003c50b0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmListRebuild(); }
void fn_nmSeqNullStep_003c5170(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSeqNullStep(); }
void fn_nmSequenceCreate_003c5180(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSequenceCreate(); }
void fn_sub_3C5210_003c5210(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C5210(); }
void fn_nmSequenceDestroy_003c5220(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSequenceDestroy(); }
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSequenceAddStep(); }
void fn_sub_3C53E0_003c53e0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C53E0(); }
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmObjPayloadWord12(); }
void fn_sub_3C5470_003c5470(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C5470(); }
void fn_nmNodePayloadArea40_003c5480(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmNodePayloadArea40(); }
void fn_sub_3C5490_003c5490(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C5490(); }
void fn_nmSequenceCallAll36_003c5760(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSequenceCallAll36(); }
void fn_sub_3C57E0_003c57e0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C57E0(); }
void fn_nmSeqStepOnRemove_003c5810(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSeqStepOnRemove(); }
void fn_nmSeqStepRun_003c5840(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSeqStepRun(); }
void fn_nmSeqStepCall36_003c5870(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmSeqStepCall36(); }
void fn_nullsub_56_003c58a0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nullsub(); }
void fn_nullsub_57_003c58b0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nullsub(); }
void fn_nullsub_54_003c58c0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nullsub(); }
void fn_nullsub_55_003c58d0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nullsub(); }
void fn_nullsub_58_003c58e0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nullsub(); }
void fn_sub_3C58F0_003c58f0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C58F0(); }
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListDestroy(); }
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListAddRow(); }
void fn_sub_3C5AF0_003c5af0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C5AF0(); }
void fn_nmCmdListCursorDown_003c5bb0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListCursorDown(); }
void fn_sub_3C5C50_003c5c50(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C5C50(); }
void fn_nmCmdListSelect_003c5d40(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSelect(); }
void fn_nmCmdListSetDrawFunc_003c5e20(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSetDrawFunc(); }
void fn_nmCmdListSetUpdateFunc_003c5e80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSetUpdateFunc(); }
void fn_nmCmdListSetRowDrawFunc_003c5ee0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSetRowDrawFunc(); }
void fn_nmCmdListSetRowRemoveFunc_003c5f40(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSetRowRemoveFunc(); }
void fn_nmCmdListRemoveRow_003c5fa0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListRemoveRow(); }
void fn_nmCmdListOnInsert_003c60c0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListOnInsert(); }
void fn_nmCmdListOnRemove_003c60f0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListOnRemove(); }
void fn_nmCmdListDrawRow_003c6120(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListDrawRow(); }
void fn_nmCmdListUpdate_003c6270(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListUpdate(); }
void fn_nmCmdListDraw_003c6380(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListDraw(); }
void fn_sub_3C63F0_003c63f0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C63F0(); }
void fn_nmCmdListStartFade_003c6900(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListStartFade(); }
void fn_sub_3C69D0_003c69d0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C69D0(); }
void fn_nmCmdListScrollBar_003c6b70(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListScrollBar(); }
void fn_nmCmdListDecidedRow_003c6c50(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListDecidedRow(); }
void fn_nmCmdListCancelled_003c6c80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListCancelled(); }
void fn_nmCmdListPagedDown_003c6ca0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListPagedDown(); }
void fn_nmCmdListMovedUp_003c6cc0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListMovedUp(); }
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListMovedDownRow(); }
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListScrolledRow(); }
void fn_nmCmdListSetPosition_003c6d40(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSetPosition(); }
void fn_sub_3C6D60_003c6d60(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C6D60(); }
void fn_nmCmdListStatus_003c6d80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListStatus(); }
void fn_nmCmdListStatus28_003c6e10(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListStatus28(); }
void fn_nmCmdListHold_003c6ea0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListHold(); }
void fn_nmCmdListRelease_003c6ec0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListRelease(); }
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C6EE0(); }
void fn_nmCmdListClose_003c6f10(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListClose(); }
void fn_nmCmdListCloseNow_003c6f50(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListCloseNow(); }
void fn_nmCmdListVisibleRows_003c6f80(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListVisibleRows(); }
void fn_nmCmdListCursorLine_003c6fb0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListCursorLine(); }
void fn_nmCmdListSort_003c7000(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).nmCmdListSort(); }
void fn_sub_3C7070_003c7070(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C7070(); }
void fn_msgWinReset_003c7270(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinReset(); }
void fn_msgWinRecordInit_003c72a0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinRecordInit(); }
void fn_sub_3C72D0_003c72d0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C72D0(); }
void fn_msgWinSetStateFlags_003c7390(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinSetStateFlags(); }
void fn_sub_3C73E0_003c73e0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C73E0(); }
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinRequestMessage(); }
void fn_sub_3C74E0_003c74e0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C74E0(); }
void fn_msgWinSetType_003c7560(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinSetType(); }
void fn_msgWinGetSelection_003c75b0(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinGetSelection(); }
void fn_msgWinLastSelection_003c7610(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinLastSelection(); }
void fn_msgWinClose_003c7650(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).msgWinClose(); }
void fn_sub_3C7700_003c7700(p3fes::EEContext& ctx) { pg::nm::detail::Nm(ctx).sub_3C7700(); }

}  // namespace p3fes::recomp_gen
