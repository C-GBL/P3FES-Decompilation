// Pair tests for slice sweep5f (game/src/render/sweep5f.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log). Worlds: random worlds; the live
// RAM of the replay snapshots with the arguments pointing at the CRI globals the bodies use (the AIXP slots, the DVCI
// name buffers, the file-cache tables) and into the snapshot heap; and documented rules from the instructions (pixel
// pack / unpack, path-name compare, header bit fields, setters / getters, the scratchpad copies, "LSN,size" parsing).
// The standard stand-ins (heap, printf / sprintf, the H_Cdvd layer) are installed in both runs and the call logs must be
// equal; any other callee this build does not emit stops both runs at the same call (no test asserts such a stop).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/sweep5f.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_28B800_0028b800(EEContext&);  // generated body
void fn_sub_28B800_0028b800__recomp(EEContext&);  // recompiled
void fn_sub_335A70_00335a70(EEContext&);  // generated body
void fn_sub_335A70_00335a70__recomp(EEContext&);  // recompiled
void fn_sub_4D9510_004d9510(EEContext&);  // generated body
void fn_sub_4D9510_004d9510__recomp(EEContext&);  // recompiled
void fn_sub_4E96C0_004e96c0(EEContext&);  // generated body
void fn_sub_4E96C0_004e96c0__recomp(EEContext&);  // recompiled
void fn_sub_4E97C0_004e97c0(EEContext&);  // generated body
void fn_sub_4E97C0_004e97c0__recomp(EEContext&);  // recompiled
void fn_sub_4E9AA0_004e9aa0(EEContext&);  // generated body
void fn_sub_4E9AA0_004e9aa0__recomp(EEContext&);  // recompiled
void fn__unknown_extension_004ff5b0(EEContext&);  // generated body
void fn__unknown_extension_004ff5b0__recomp(EEContext&);  // recompiled
void fn__pictureCodingExtension_004ff5c0(EEContext&);  // generated body
void fn__pictureCodingExtension_004ff5c0__recomp(EEContext&);  // recompiled
void fn_sub_542DC0_00542dc0(EEContext&);  // generated body
void fn_sub_542DC0_00542dc0__recomp(EEContext&);  // recompiled
void fn_sub_5433A0_005433a0(EEContext&);  // generated body
void fn_sub_5433A0_005433a0__recomp(EEContext&);  // recompiled
void fn_sub_54A680_0054a680(EEContext&);  // generated body
void fn_sub_54A680_0054a680__recomp(EEContext&);  // recompiled
void fn_sub_54B3A0_0054b3a0(EEContext&);  // generated body
void fn_sub_54B3A0_0054b3a0__recomp(EEContext&);  // recompiled
void fn_sub_54F5C0_0054f5c0(EEContext&);  // generated body
void fn_sub_54F5C0_0054f5c0__recomp(EEContext&);  // recompiled
void fn_sub_552760_00552760(EEContext&);  // generated body
void fn_sub_552760_00552760__recomp(EEContext&);  // recompiled
void fn_sub_552830_00552830(EEContext&);  // generated body
void fn_sub_552830_00552830__recomp(EEContext&);  // recompiled
void fn_sub_5528B0_005528b0(EEContext&);  // generated body
void fn_sub_5528B0_005528b0__recomp(EEContext&);  // recompiled
void fn_sub_552EA8_00552ea8(EEContext&);  // generated body
void fn_sub_552EA8_00552ea8__recomp(EEContext&);  // recompiled
void fn_sub_552EC8_00552ec8(EEContext&);  // generated body
void fn_sub_552EC8_00552ec8__recomp(EEContext&);  // recompiled
void fn_sub_553028_00553028(EEContext&);  // generated body
void fn_sub_553028_00553028__recomp(EEContext&);  // recompiled
void fn_sub_5533D8_005533d8(EEContext&);  // generated body
void fn_sub_5533D8_005533d8__recomp(EEContext&);  // recompiled
void fn_sub_553590_00553590(EEContext&);  // generated body
void fn_sub_553590_00553590__recomp(EEContext&);  // recompiled
void fn_sub_553658_00553658(EEContext&);  // generated body
void fn_sub_553658_00553658__recomp(EEContext&);  // recompiled
void fn_sub_5540E8_005540e8(EEContext&);  // generated body
void fn_sub_5540E8_005540e8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_5_00555f90(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_5_00555f90__recomp(EEContext&);  // recompiled
void fn_srd_wait_dvd_00557d58(EEContext&);  // generated body
void fn_srd_wait_dvd_00557d58__recomp(EEContext&);  // recompiled
void fn_SRD_GetReadStatusDvd_00558768(EEContext&);  // generated body
void fn_SRD_GetReadStatusDvd_00558768__recomp(EEContext&);  // recompiled
void fn_SRD_SetDvdSeekPos_00558ae0(EEContext&);  // generated body
void fn_SRD_SetDvdSeekPos_00558ae0__recomp(EEContext&);  // recompiled
void fn_dtx_destroy_rmt_005595f8(EEContext&);  // generated body
void fn_dtx_destroy_rmt_005595f8__recomp(EEContext&);  // recompiled
void fn_dvCiIsExistFile_0055a050(EEContext&);  // generated body
void fn_dvCiIsExistFile_0055a050__recomp(EEContext&);  // recompiled
void fn_dvCiGetFileSize_0055a0d8(EEContext&);  // generated body
void fn_dvCiGetFileSize_0055a0d8__recomp(EEContext&);  // recompiled
void fn_dvCiClose_0055a368(EEContext&);  // generated body
void fn_dvCiClose_0055a368__recomp(EEContext&);  // recompiled
void fn_sub_55A458_0055a458(EEContext&);  // generated body
void fn_sub_55A458_0055a458__recomp(EEContext&);  // recompiled
void fn_sceInsockGetErrnoMode_3_0055a7c0(EEContext&);  // generated body
void fn_sceInsockGetErrnoMode_3_0055a7c0__recomp(EEContext&);  // recompiled
void fn_sub_55A800_0055a800(EEContext&);  // generated body
void fn_sub_55A800_0055a800__recomp(EEContext&);  // recompiled
void fn_sub_55A8C8_0055a8c8(EEContext&);  // generated body
void fn_sub_55A8C8_0055a8c8__recomp(EEContext&);  // recompiled
void fn_sub_55A8D0_0055a8d0(EEContext&);  // generated body
void fn_sub_55A8D0_0055a8d0__recomp(EEContext&);  // recompiled
void fn_sub_55AA58_0055aa58(EEContext&);  // generated body
void fn_sub_55AA58_0055aa58__recomp(EEContext&);  // recompiled
void fn_sub_55AA90_0055aa90(EEContext&);  // generated body
void fn_sub_55AA90_0055aa90__recomp(EEContext&);  // recompiled
void fn_sub_55AAE8_0055aae8(EEContext&);  // generated body
void fn_sub_55AAE8_0055aae8__recomp(EEContext&);  // recompiled
void fn_dvci_load_flist_0055ad18(EEContext&);  // generated body
void fn_dvci_load_flist_0055ad18__recomp(EEContext&);  // recompiled
void fn_dvci_get_fp_from_fname_0055b030(EEContext&);  // generated body
void fn_dvci_get_fp_from_fname_0055b030__recomp(EEContext&);  // recompiled
void fn_dvci_get_adr_size_0055b160(EEContext&);  // generated body
void fn_dvci_get_adr_size_0055b160__recomp(EEContext&);  // recompiled
void fn_sub_55E978_0055e978(EEContext&);  // generated body
void fn_sub_55E978_0055e978__recomp(EEContext&);  // recompiled
void fn_sub_55EA00_0055ea00(EEContext&);  // generated body
void fn_sub_55EA00_0055ea00__recomp(EEContext&);  // recompiled
void fn_sub_55F4F0_0055f4f0(EEContext&);  // generated body
void fn_sub_55F4F0_0055f4f0__recomp(EEContext&);  // recompiled
void fn_sub_570030_00570030(EEContext&);  // generated body
void fn_sub_570030_00570030__recomp(EEContext&);  // recompiled
void fn_sub_57FA98_0057fa98(EEContext&);  // generated body
void fn_sub_57FA98_0057fa98__recomp(EEContext&);  // recompiled
void fn_sub_580ED8_00580ed8(EEContext&);  // generated body
void fn_sub_580ED8_00580ed8__recomp(EEContext&);  // recompiled
void fn_sub_580FB8_00580fb8(EEContext&);  // generated body
void fn_sub_580FB8_00580fb8__recomp(EEContext&);  // recompiled
void fn_sub_5827C0_005827c0(EEContext&);  // generated body
void fn_sub_5827C0_005827c0__recomp(EEContext&);  // recompiled
void fn_sub_5840D0_005840d0(EEContext&);  // generated body
void fn_sub_5840D0_005840d0__recomp(EEContext&);  // recompiled
void fn_sub_584B18_00584b18(EEContext&);  // generated body
void fn_sub_584B18_00584b18__recomp(EEContext&);  // recompiled
void fn_sub_584C38_00584c38(EEContext&);  // generated body
void fn_sub_584C38_00584c38__recomp(EEContext&);  // recompiled
void fn_sub_584D30_00584d30(EEContext&);  // generated body
void fn_sub_584D30_00584d30__recomp(EEContext&);  // recompiled
void fn_sub_586FE0_00586fe0(EEContext&);  // generated body
void fn_sub_586FE0_00586fe0__recomp(EEContext&);  // recompiled
void fn_sub_587618_00587618(EEContext&);  // generated body
void fn_sub_587618_00587618__recomp(EEContext&);  // recompiled
void fn_sub_588168_00588168(EEContext&);  // generated body
void fn_sub_588168_00588168__recomp(EEContext&);  // recompiled
void fn_sub_5881F8_005881f8(EEContext&);  // generated body
void fn_sub_5881F8_005881f8__recomp(EEContext&);  // recompiled
void fn_sub_588270_00588270(EEContext&);  // generated body
void fn_sub_588270_00588270__recomp(EEContext&);  // recompiled
void fn_sub_5882F0_005882f0(EEContext&);  // generated body
void fn_sub_5882F0_005882f0__recomp(EEContext&);  // recompiled
void fn_sub_58ABA0_0058aba0(EEContext&);  // generated body
void fn_sub_58ABA0_0058aba0__recomp(EEContext&);  // recompiled
void fn_sub_58AF20_0058af20(EEContext&);  // generated body
void fn_sub_58AF20_0058af20__recomp(EEContext&);  // recompiled
void fn_sub_58CA60_0058ca60(EEContext&);  // generated body
void fn_sub_58CA60_0058ca60__recomp(EEContext&);  // recompiled
void fn_sub_58CAA0_0058caa0(EEContext&);  // generated body
void fn_sub_58CAA0_0058caa0__recomp(EEContext&);  // recompiled
void fn_sub_58CCA0_0058cca0(EEContext&);  // generated body
void fn_sub_58CCA0_0058cca0__recomp(EEContext&);  // recompiled
void fn_sub_58D300_0058d300(EEContext&);  // generated body
void fn_sub_58D300_0058d300__recomp(EEContext&);  // recompiled
void fn_sub_58D5E8_0058d5e8(EEContext&);  // generated body
void fn_sub_58D5E8_0058d5e8__recomp(EEContext&);  // recompiled
void fn_sub_58EFB8_0058efb8(EEContext&);  // generated body
void fn_sub_58EFB8_0058efb8__recomp(EEContext&);  // recompiled
void fn_sub_58FB28_0058fb28(EEContext&);  // generated body
void fn_sub_58FB28_0058fb28__recomp(EEContext&);  // recompiled
void fn_sub_58FBE0_0058fbe0(EEContext&);  // generated body
void fn_sub_58FBE0_0058fbe0__recomp(EEContext&);  // recompiled
void fn_sub_591B18_00591b18(EEContext&);  // generated body
void fn_sub_591B18_00591b18__recomp(EEContext&);  // recompiled
void fn_sub_5957D8_005957d8(EEContext&);  // generated body
void fn_sub_5957D8_005957d8__recomp(EEContext&);  // recompiled
void fn_sub_599418_00599418(EEContext&);  // generated body
void fn_sub_599418_00599418__recomp(EEContext&);  // recompiled
void fn_sub_599D70_00599d70(EEContext&);  // generated body
void fn_sub_599D70_00599d70__recomp(EEContext&);  // recompiled
void fn_sub_59BE90_0059be90(EEContext&);  // generated body
void fn_sub_59BE90_0059be90__recomp(EEContext&);  // recompiled
void fn_sub_59CAC8_0059cac8(EEContext&);  // generated body
void fn_sub_59CAC8_0059cac8__recomp(EEContext&);  // recompiled
void fn_sub_59CDE0_0059cde0(EEContext&);  // generated body
void fn_sub_59CDE0_0059cde0__recomp(EEContext&);  // recompiled
void fn_sub_59FA38_0059fa38(EEContext&);  // generated body
void fn_sub_59FA38_0059fa38__recomp(EEContext&);  // recompiled
void fn_sub_59FDB8_0059fdb8(EEContext&);  // generated body
void fn_sub_59FDB8_0059fdb8__recomp(EEContext&);  // recompiled
void fn_sub_5A1380_005a1380(EEContext&);  // generated body
void fn_sub_5A1380_005a1380__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_28B800", 0x28B800, &recomp_gen::fn_sub_28B800_0028b800, &recomp_gen::fn_sub_28B800_0028b800__recomp},
    {"sub_335A70", 0x335A70, &recomp_gen::fn_sub_335A70_00335a70, &recomp_gen::fn_sub_335A70_00335a70__recomp},
    {"sub_4D9510", 0x4D9510, &recomp_gen::fn_sub_4D9510_004d9510, &recomp_gen::fn_sub_4D9510_004d9510__recomp},
    {"sub_4E96C0", 0x4E96C0, &recomp_gen::fn_sub_4E96C0_004e96c0, &recomp_gen::fn_sub_4E96C0_004e96c0__recomp},
    {"sub_4E97C0", 0x4E97C0, &recomp_gen::fn_sub_4E97C0_004e97c0, &recomp_gen::fn_sub_4E97C0_004e97c0__recomp},
    {"sub_4E9AA0", 0x4E9AA0, &recomp_gen::fn_sub_4E9AA0_004e9aa0, &recomp_gen::fn_sub_4E9AA0_004e9aa0__recomp},
    {"_unknown_extension", 0x4FF5B0, &recomp_gen::fn__unknown_extension_004ff5b0, &recomp_gen::fn__unknown_extension_004ff5b0__recomp},
    {"_pictureCodingExtension", 0x4FF5C0, &recomp_gen::fn__pictureCodingExtension_004ff5c0, &recomp_gen::fn__pictureCodingExtension_004ff5c0__recomp},
    {"sub_542DC0", 0x542DC0, &recomp_gen::fn_sub_542DC0_00542dc0, &recomp_gen::fn_sub_542DC0_00542dc0__recomp},
    {"sub_5433A0", 0x5433A0, &recomp_gen::fn_sub_5433A0_005433a0, &recomp_gen::fn_sub_5433A0_005433a0__recomp},
    {"sub_54A680", 0x54A680, &recomp_gen::fn_sub_54A680_0054a680, &recomp_gen::fn_sub_54A680_0054a680__recomp},
    {"sub_54B3A0", 0x54B3A0, &recomp_gen::fn_sub_54B3A0_0054b3a0, &recomp_gen::fn_sub_54B3A0_0054b3a0__recomp},
    {"sub_54F5C0", 0x54F5C0, &recomp_gen::fn_sub_54F5C0_0054f5c0, &recomp_gen::fn_sub_54F5C0_0054f5c0__recomp},
    {"sub_552760", 0x552760, &recomp_gen::fn_sub_552760_00552760, &recomp_gen::fn_sub_552760_00552760__recomp},
    {"sub_552830", 0x552830, &recomp_gen::fn_sub_552830_00552830, &recomp_gen::fn_sub_552830_00552830__recomp},
    {"sub_5528B0", 0x5528B0, &recomp_gen::fn_sub_5528B0_005528b0, &recomp_gen::fn_sub_5528B0_005528b0__recomp},
    {"sub_552EA8", 0x552EA8, &recomp_gen::fn_sub_552EA8_00552ea8, &recomp_gen::fn_sub_552EA8_00552ea8__recomp},
    {"sub_552EC8", 0x552EC8, &recomp_gen::fn_sub_552EC8_00552ec8, &recomp_gen::fn_sub_552EC8_00552ec8__recomp},
    {"sub_553028", 0x553028, &recomp_gen::fn_sub_553028_00553028, &recomp_gen::fn_sub_553028_00553028__recomp},
    {"sub_5533D8", 0x5533D8, &recomp_gen::fn_sub_5533D8_005533d8, &recomp_gen::fn_sub_5533D8_005533d8__recomp},
    {"sub_553590", 0x553590, &recomp_gen::fn_sub_553590_00553590, &recomp_gen::fn_sub_553590_00553590__recomp},
    {"sub_553658", 0x553658, &recomp_gen::fn_sub_553658_00553658, &recomp_gen::fn_sub_553658_00553658__recomp},
    {"sub_5540E8", 0x5540E8, &recomp_gen::fn_sub_5540E8_005540e8, &recomp_gen::fn_sub_5540E8_005540e8__recomp},
    {"sceLibgcc32GetErxEntries_5", 0x555F90, &recomp_gen::fn_sceLibgcc32GetErxEntries_5_00555f90, &recomp_gen::fn_sceLibgcc32GetErxEntries_5_00555f90__recomp},
    {"srd_wait_dvd", 0x557D58, &recomp_gen::fn_srd_wait_dvd_00557d58, &recomp_gen::fn_srd_wait_dvd_00557d58__recomp},
    {"SRD_GetReadStatusDvd", 0x558768, &recomp_gen::fn_SRD_GetReadStatusDvd_00558768, &recomp_gen::fn_SRD_GetReadStatusDvd_00558768__recomp},
    {"SRD_SetDvdSeekPos", 0x558AE0, &recomp_gen::fn_SRD_SetDvdSeekPos_00558ae0, &recomp_gen::fn_SRD_SetDvdSeekPos_00558ae0__recomp},
    {"dtx_destroy_rmt", 0x5595F8, &recomp_gen::fn_dtx_destroy_rmt_005595f8, &recomp_gen::fn_dtx_destroy_rmt_005595f8__recomp},
    {"dvCiIsExistFile", 0x55A050, &recomp_gen::fn_dvCiIsExistFile_0055a050, &recomp_gen::fn_dvCiIsExistFile_0055a050__recomp},
    {"dvCiGetFileSize", 0x55A0D8, &recomp_gen::fn_dvCiGetFileSize_0055a0d8, &recomp_gen::fn_dvCiGetFileSize_0055a0d8__recomp},
    {"dvCiClose", 0x55A368, &recomp_gen::fn_dvCiClose_0055a368, &recomp_gen::fn_dvCiClose_0055a368__recomp},
    {"sub_55A458", 0x55A458, &recomp_gen::fn_sub_55A458_0055a458, &recomp_gen::fn_sub_55A458_0055a458__recomp},
    {"sceInsockGetErrnoMode_3", 0x55A7C0, &recomp_gen::fn_sceInsockGetErrnoMode_3_0055a7c0, &recomp_gen::fn_sceInsockGetErrnoMode_3_0055a7c0__recomp},
    {"sub_55A800", 0x55A800, &recomp_gen::fn_sub_55A800_0055a800, &recomp_gen::fn_sub_55A800_0055a800__recomp},
    {"sub_55A8C8", 0x55A8C8, &recomp_gen::fn_sub_55A8C8_0055a8c8, &recomp_gen::fn_sub_55A8C8_0055a8c8__recomp},
    {"sub_55A8D0", 0x55A8D0, &recomp_gen::fn_sub_55A8D0_0055a8d0, &recomp_gen::fn_sub_55A8D0_0055a8d0__recomp},
    {"sub_55AA58", 0x55AA58, &recomp_gen::fn_sub_55AA58_0055aa58, &recomp_gen::fn_sub_55AA58_0055aa58__recomp},
    {"sub_55AA90", 0x55AA90, &recomp_gen::fn_sub_55AA90_0055aa90, &recomp_gen::fn_sub_55AA90_0055aa90__recomp},
    {"sub_55AAE8", 0x55AAE8, &recomp_gen::fn_sub_55AAE8_0055aae8, &recomp_gen::fn_sub_55AAE8_0055aae8__recomp},
    {"dvci_load_flist", 0x55AD18, &recomp_gen::fn_dvci_load_flist_0055ad18, &recomp_gen::fn_dvci_load_flist_0055ad18__recomp},
    {"dvci_get_fp_from_fname", 0x55B030, &recomp_gen::fn_dvci_get_fp_from_fname_0055b030, &recomp_gen::fn_dvci_get_fp_from_fname_0055b030__recomp},
    {"dvci_get_adr_size", 0x55B160, &recomp_gen::fn_dvci_get_adr_size_0055b160, &recomp_gen::fn_dvci_get_adr_size_0055b160__recomp},
    {"sub_55E978", 0x55E978, &recomp_gen::fn_sub_55E978_0055e978, &recomp_gen::fn_sub_55E978_0055e978__recomp},
    {"sub_55EA00", 0x55EA00, &recomp_gen::fn_sub_55EA00_0055ea00, &recomp_gen::fn_sub_55EA00_0055ea00__recomp},
    {"sub_55F4F0", 0x55F4F0, &recomp_gen::fn_sub_55F4F0_0055f4f0, &recomp_gen::fn_sub_55F4F0_0055f4f0__recomp},
    {"sub_570030", 0x570030, &recomp_gen::fn_sub_570030_00570030, &recomp_gen::fn_sub_570030_00570030__recomp},
    {"sub_57FA98", 0x57FA98, &recomp_gen::fn_sub_57FA98_0057fa98, &recomp_gen::fn_sub_57FA98_0057fa98__recomp},
    {"sub_580ED8", 0x580ED8, &recomp_gen::fn_sub_580ED8_00580ed8, &recomp_gen::fn_sub_580ED8_00580ed8__recomp},
    {"sub_580FB8", 0x580FB8, &recomp_gen::fn_sub_580FB8_00580fb8, &recomp_gen::fn_sub_580FB8_00580fb8__recomp},
    {"sub_5827C0", 0x5827C0, &recomp_gen::fn_sub_5827C0_005827c0, &recomp_gen::fn_sub_5827C0_005827c0__recomp},
    {"sub_5840D0", 0x5840D0, &recomp_gen::fn_sub_5840D0_005840d0, &recomp_gen::fn_sub_5840D0_005840d0__recomp},
    {"sub_584B18", 0x584B18, &recomp_gen::fn_sub_584B18_00584b18, &recomp_gen::fn_sub_584B18_00584b18__recomp},
    {"sub_584C38", 0x584C38, &recomp_gen::fn_sub_584C38_00584c38, &recomp_gen::fn_sub_584C38_00584c38__recomp},
    {"sub_584D30", 0x584D30, &recomp_gen::fn_sub_584D30_00584d30, &recomp_gen::fn_sub_584D30_00584d30__recomp},
    {"sub_586FE0", 0x586FE0, &recomp_gen::fn_sub_586FE0_00586fe0, &recomp_gen::fn_sub_586FE0_00586fe0__recomp},
    {"sub_587618", 0x587618, &recomp_gen::fn_sub_587618_00587618, &recomp_gen::fn_sub_587618_00587618__recomp},
    {"sub_588168", 0x588168, &recomp_gen::fn_sub_588168_00588168, &recomp_gen::fn_sub_588168_00588168__recomp},
    {"sub_5881F8", 0x5881F8, &recomp_gen::fn_sub_5881F8_005881f8, &recomp_gen::fn_sub_5881F8_005881f8__recomp},
    {"sub_588270", 0x588270, &recomp_gen::fn_sub_588270_00588270, &recomp_gen::fn_sub_588270_00588270__recomp},
    {"sub_5882F0", 0x5882F0, &recomp_gen::fn_sub_5882F0_005882f0, &recomp_gen::fn_sub_5882F0_005882f0__recomp},
    {"sub_58ABA0", 0x58ABA0, &recomp_gen::fn_sub_58ABA0_0058aba0, &recomp_gen::fn_sub_58ABA0_0058aba0__recomp},
    {"sub_58AF20", 0x58AF20, &recomp_gen::fn_sub_58AF20_0058af20, &recomp_gen::fn_sub_58AF20_0058af20__recomp},
    {"sub_58CA60", 0x58CA60, &recomp_gen::fn_sub_58CA60_0058ca60, &recomp_gen::fn_sub_58CA60_0058ca60__recomp},
    {"sub_58CAA0", 0x58CAA0, &recomp_gen::fn_sub_58CAA0_0058caa0, &recomp_gen::fn_sub_58CAA0_0058caa0__recomp},
    {"sub_58CCA0", 0x58CCA0, &recomp_gen::fn_sub_58CCA0_0058cca0, &recomp_gen::fn_sub_58CCA0_0058cca0__recomp},
    {"sub_58D300", 0x58D300, &recomp_gen::fn_sub_58D300_0058d300, &recomp_gen::fn_sub_58D300_0058d300__recomp},
    {"sub_58D5E8", 0x58D5E8, &recomp_gen::fn_sub_58D5E8_0058d5e8, &recomp_gen::fn_sub_58D5E8_0058d5e8__recomp},
    {"sub_58EFB8", 0x58EFB8, &recomp_gen::fn_sub_58EFB8_0058efb8, &recomp_gen::fn_sub_58EFB8_0058efb8__recomp},
    {"sub_58FB28", 0x58FB28, &recomp_gen::fn_sub_58FB28_0058fb28, &recomp_gen::fn_sub_58FB28_0058fb28__recomp},
    {"sub_58FBE0", 0x58FBE0, &recomp_gen::fn_sub_58FBE0_0058fbe0, &recomp_gen::fn_sub_58FBE0_0058fbe0__recomp},
    {"sub_591B18", 0x591B18, &recomp_gen::fn_sub_591B18_00591b18, &recomp_gen::fn_sub_591B18_00591b18__recomp},
    {"sub_5957D8", 0x5957D8, &recomp_gen::fn_sub_5957D8_005957d8, &recomp_gen::fn_sub_5957D8_005957d8__recomp},
    {"sub_599418", 0x599418, &recomp_gen::fn_sub_599418_00599418, &recomp_gen::fn_sub_599418_00599418__recomp},
    {"sub_599D70", 0x599D70, &recomp_gen::fn_sub_599D70_00599d70, &recomp_gen::fn_sub_599D70_00599d70__recomp},
    {"sub_59BE90", 0x59BE90, &recomp_gen::fn_sub_59BE90_0059be90, &recomp_gen::fn_sub_59BE90_0059be90__recomp},
    {"sub_59CAC8", 0x59CAC8, &recomp_gen::fn_sub_59CAC8_0059cac8, &recomp_gen::fn_sub_59CAC8_0059cac8__recomp},
    {"sub_59CDE0", 0x59CDE0, &recomp_gen::fn_sub_59CDE0_0059cde0, &recomp_gen::fn_sub_59CDE0_0059cde0__recomp},
    {"sub_59FA38", 0x59FA38, &recomp_gen::fn_sub_59FA38_0059fa38, &recomp_gen::fn_sub_59FA38_0059fa38__recomp},
    {"sub_59FDB8", 0x59FDB8, &recomp_gen::fn_sub_59FDB8_0059fdb8, &recomp_gen::fn_sub_59FDB8_0059fdb8__recomp},
    {"sub_5A1380", 0x5A1380, &recomp_gen::fn_sub_5A1380_005a1380, &recomp_gen::fn_sub_5A1380_005a1380__recomp},
};

// Random worlds: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// CRI globals the bodies read or write (from the instructions).
constexpr u32 kAixpSlots = 0x799978u;      // 4 AIX player slots of 620 bytes (sub_552760)
constexpr u32 kAixpSlotSize = 620u;
constexpr u32 kDvciName = 0x7A2930u;       // the converted file name (dvCiIsExistFile / dvCiGetFileSize / sub_55A800)
constexpr u32 kDvciFlistName = 0x7A2B88u;  // dvci_load_flist's name buffer
constexpr u32 kDvciMode = 0x7A2A78u;       // sceInsockGetErrnoMode_3
constexpr u32 kDevNames = 0x997858u;       // sceLibgcc32GetErxEntries_5

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }

// Pairs with the stand-ins: both bodies get a fresh standard set and the two call logs must be equal.
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
int g_pairs = 0;
int g_stops = 0;
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw = {}) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    install_standard(*wh);
    install_standard(*wr);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    ++g_pairs;
    g_stops += r.stopped ? 1 : 0;
    return r;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s64 sv(const hgp::Run& r) { return static_cast<s64>(v0_of(r)); }

// Snapshot arguments: the CRI globals above, a pointer into the snapshot heap (16-aligned), a world pointer, small
// values (the ids and counts the branches compare: 0, 1, 2, 4, 6, 15, 71, 201, 203, 205), zero or a wide value.
u64 snap_arg(std::mt19937& rng) {
    static const u32 kSmall[] = {0u, 1u, 2u, 4u, 6u, 15u, 71u, 201u, 203u, 205u, 18u, 36u};
    const u32 k = rng() % 12;
    if (k < 2) return sx(kAixpSlots + kAixpSlotSize * (rng() % 4));
    if (k < 3) return sx(rng() % 2 ? kDvciName : kDvciFlistName);
    if (k < 6) return sx(0x00800000u + ((rng() % 0x00F00000u) & ~15u));
    if (k < 8) return sx(kWorld + ((rng() % kWorldSize) & ~15u));
    if (k < 10) return kSmall[rng() % 12];
    if (k < 11) return 0;
    return sx(rng());
}

const char* const kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000"};

}  // namespace

TEST_CASE("game(sweep5f): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    g_pairs = g_stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            spair(*m, c.hand, c.recomp, args, seed, c.name);
        }
    }
    MESSAGE(g_pairs << " pairs on random worlds, " << g_stops << " stopped early (identically)");
}

// Every body over the RAM of the replay snapshots: the live CRI state (ADX / AIX players, the DVCI file cache, the
// Sofdec library globals), the battle and effect objects, with the arguments of snap_arg.
TEST_CASE("game(sweep5f): every body equals its recompiled body on the replay snapshots' live state") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? std::max<u32>(1, static_cast<u32>(std::strtoul(env, nullptr, 10)) / 8) : 8u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    g_pairs = g_stops = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 seed = 1; seed <= seeds; ++seed) {
                if (trace) std::fprintf(stderr, "%s %s seed %u\n", dir, c.name, seed);
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                std::mt19937 rng{seed * 131u + c.addr};
                hgp::random_world(*m, kWorld, kWorldSize, rng);
                const Args args{snap_arg(rng), snap_arg(rng), snap_arg(rng), snap_arg(rng)};
                spair(*m, c.hand, c.recomp, args, seed, c.name);
            }
        }
    }
    MESSAGE(g_pairs << " pairs on snapshot state, " << g_stops << " stopped early (identically)");
}

// Documented rules, from the instructions (both bodies run and are compared, then the result is checked). Only results
// that hold whatever the callees are (replaced or recompiled) are checked.
TEST_CASE("game(sweep5f): pixel pack / unpack, path names, bit fields, setters and getters") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto run = [&](const char* name, const Args& a) {
        const Case& c = find_case(name);
        return spair(*m, c.hand, c.recomp, a, 1, c.name);
    };
    g_pairs = g_stops = 0;
    const u32 a = kWorld, b = kWorld + 0x100, c = kWorld + 0x200;
    std::memset(m->at(kWorld), 0, 0x1000);

    // sub_4D9510 / sub_59BE90: setters; sub_5433A0: +88; sub_59FDB8: the word +4 (sign-extended)
    CHECK(v0_of(run("sub_4D9510", Args{sx(a), 0x12345678, 0, 0})) == 1u);
    CHECK(r32(*m, a) == 0x12345678u);
    run("sub_59BE90", Args{sx(a), 0xCAFEF00Du, 0, 0});
    CHECK(r32(*m, a + 12) == 0xCAFEF00Du);
    CHECK(v0_of(run("sub_5433A0", Args{sx(a), 0, 0, 0})) == a + 88u);
    w32(*m, a + 4, 0x80000001u);
    CHECK(v0_of(run("sub_59FDB8", Args{sx(a), 0, 0, 0})) == sx(0x80000001u));
    CHECK(v0_of(run("sub_59CAC8", Args{0, 0, 0, 0})) == 1u);
    CHECK(v0_of(run("sub_55A8C8", Args{0, 0, 0, 0})) == 0u);
    CHECK(v0_of(run("sceLibgcc32GetErxEntries_5", Args{0, 0, 0, 0})) == kDevNames);
    w32(*m, kDvciMode, 7);
    CHECK(v0_of(run("sceInsockGetErrnoMode_3", Args{0, 0, 0, 0})) == 7u);

    // AIXP / DVCI field getters and setters on a non-NULL handle
    w32(*m, a + 424, 3);
    CHECK(v0_of(run("sub_553658", Args{sx(a), 0, 0, 0})) == 3u);
    w32(*m, a + 12, 0x4000);
    CHECK(v0_of(run("sub_55A458", Args{sx(a), 0, 0, 0})) == 0x4000u);
    run("sub_5533D8", Args{sx(a), 0x5A, 0, 0});
    CHECK(*m->at(a + 432) == 0x5A);
    // sub_58D5E8: ++*(*(a + 8060) + 32)
    w32(*m, a + 8060, b);
    w32(*m, b + 32, 41);
    CHECK(v0_of(run("sub_58D5E8", Args{sx(a), 0, 0, 0})) == 42u);
    CHECK(r32(*m, b + 32) == 42u);

    // sub_4E96C0 / sub_4E97C0: pixel pack / unpack by the raster format bits (0xF00 of $a2)
    const u8 rgba[4] = {0x9C, 0x47, 0xE5, 0x80};
    std::memcpy(m->at(b), rgba, 4);
    CHECK(v0_of(run("sub_4E96C0", Args{sx(a), sx(b), 0x600, 0})) == 1u);
    CHECK(r32(*m, a) == (0x80000000u | 0xE5u << 16 | 0x47u << 8 | 0x9Cu));
    CHECK(v0_of(run("sub_4E97C0", Args{sx(c), sx(a), 0x600, 0})) == 1u);
    CHECK(r32(*m, c) == (0xFF000000u | 0xE5u << 16 | 0x47u << 8 | 0x9Cu));
    CHECK(v0_of(run("sub_4E96C0", Args{sx(a), sx(b), 0x100, 0})) == 1u);  // 1555
    const u32 p1555 = (0x80u << 8 & 0x8000u) | (0x9Cu >> 3) | (0xE5u << 7 & 0x7C00u) | (0x47u * 4 & 0x3E0u);
    CHECK(r32(*m, a) == p1555);
    CHECK(v0_of(run("sub_4E97C0", Args{sx(c), sx(a), 0x000, 0})) == 1u);
    CHECK(*m->at(c + 0) == (0x9C & 0xF8));
    CHECK(*m->at(c + 1) == (0x47 & 0xF8));
    CHECK(*m->at(c + 2) == (0xE5 & 0xF8));
    CHECK(*m->at(c + 3) == 0xFF);
    CHECK(v0_of(run("sub_4E96C0", Args{sx(a), sx(b), 0x300, 0})) == 0u);  // other formats: refused
    CHECK(v0_of(run("sub_4E97C0", Args{sx(c), sx(a), 0x400, 0})) == 0u);

    // sub_55AA58: upper case, '\' -> '/'; sub_55AA90: 0 when equal after that, else -1
    CHECK(v0_of(run("sub_55AA58", Args{'a', 0, 0, 0})) == u64('A'));
    CHECK(v0_of(run("sub_55AA58", Args{'z', 0, 0, 0})) == u64('Z'));
    CHECK(v0_of(run("sub_55AA58", Args{'\\', 0, 0, 0})) == u64('/'));
    CHECK(v0_of(run("sub_55AA58", Args{'7', 0, 0, 0})) == u64('7'));
    CHECK(sv(run("sub_55AA90", Args{'q', 'Q', 0, 0})) == 0);
    CHECK(sv(run("sub_55AA90", Args{'q', 'R', 0, 0})) == -1);
    // sub_55AAE8: whole names (strlen runs)
    wstr(*m, b, "\\bgm\\adx_01.adx");
    wstr(*m, c, "/BGM/ADX_01.ADX");
    CHECK(sv(run("sub_55AAE8", Args{sx(b), sx(c), 0, 0})) == 0);
    wstr(*m, c, "/BGM/ADX_02.ADX");
    CHECK(sv(run("sub_55AAE8", Args{sx(b), sx(c), 0, 0})) == -1);
    wstr(*m, c, "/BGM/ADX_01.AD");
    CHECK(sv(run("sub_55AAE8", Args{sx(b), sx(c), 0, 0})) == -1);

    // sub_58CA60: 1 when the n bytes are all zero
    std::memset(m->at(b), 0, 32);
    CHECK(v0_of(run("sub_58CA60", Args{sx(b), 32, 0, 0})) == 1u);
    CHECK(v0_of(run("sub_58CA60", Args{sx(b), 0, 0, 0})) == 1u);
    *m->at(b + 31) = 1;
    CHECK(v0_of(run("sub_58CA60", Args{sx(b), 32, 0, 0})) == 0u);
    CHECK(v0_of(run("sub_58CA60", Args{sx(b), 31, 0, 0})) == 1u);

    // sub_58AF20: header bytes 1..3 into eleven bit fields
    const u8 hdr[4] = {0x00, 0x07, 0xB7, 0xE6};
    std::memcpy(m->at(b), hdr, 4);
    std::memset(m->at(a), 0xEE, 16);
    run("sub_58AF20", Args{sx(a), sx(b), 0, 0});
    const u8 want[11] = {(0x07 >> 1) & 3, 0x07 & 1, 0xB7 >> 4, (0xB7 >> 2) & 3, (0xB7 & 2) ? 1 : 0, 0xB7 & 1,
                         0xE6 >> 6, (0xE6 >> 4) & 3, (0xE6 >> 3) & 1, (0xE6 >> 2) & 1, 0xE6 & 3};
    for (u32 i = 0; i < 11; ++i) CHECK(*m->at(a + i) == want[i]);

    // sub_580FB8 / sub_580ED8: copies to and from the scratchpad (0x70000000 + offset); both return 0
    for (u32 i = 0; i < 64; ++i) *m->at(b + i) = static_cast<u8>(i * 7 + 3);
    std::memset(m->at(c), 0, 64);
    CHECK(v0_of(run("sub_580FB8", Args{sx(b), 64, 0x200, 0})) == 0u);
    CHECK(v0_of(run("sub_580ED8", Args{0x200, 64, sx(c), 0})) == 0u);
    CHECK(std::memcmp(m->at(b), m->at(c), 64) == 0);

    // dvci_get_adr_size: "<LSN>,<size>" in hex -> *a1, *a2; returns 1
    wstr(*m, b, "1A2,3f");
    w32(*m, a, 0);
    w32(*m, a + 4, 0);
    {
        const hgp::Run r = run("dvci_get_adr_size", Args{sx(b), sx(a), sx(a + 4), 0});
        if (!r.stopped) CHECK(v0_of(r) == 1u);  // (the prints after the stores may stop at an absent callee)
        CHECK(r32(*m, a) == 0x1A2u);
        CHECK(r32(*m, a + 4) == 0x3Fu);
    }
    MESSAGE(g_pairs << " rule pairs, " << g_stops << " stopped early (identically)");
}

#else

TEST_CASE("game(sweep5f): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
