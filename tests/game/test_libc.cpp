// Pair tests for slice libc (game/src/libc/*.cpp: newlib's string / memory / stdlib / locale / mprec leaves, libm, libgcc's
// 64-bit division and soft-float doubles). Every body against its recompiled body, compared by tests/game/handgen_pairs.h:
// the whole register file and cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead
// stack included), the scratchpad, the BIOS window and the bus log. On top of the generic sweep (random worlds), each
// family runs on meaningful inputs with documented-rule checks against the host:
//   * <string.h> on random buffers / strings at every alignment and the edge lengths of the word loops;
//   * strtok's and setlocale's state in the _reent over several calls, __errno, localeconv, mbtowc;
//   * strtol / strtoul / atoi against strtoll / strtoull (long is 64-bit), end pointer and errno = ERANGE;
//   * the 64-bit multiply / divide / modulo helpers against host u64 / s64 (powers of two, the extreme values);
//   * the soft-float doubles against host IEEE doubles (the library truncates: each result is the host's or the next
//     value toward zero), the pack / unpack record layout, the conversions;
//   * libm against <cmath> with the measured worst error in ulps;
//   * the mprec Bigint leaves on built Bigints, __sccl's scansets, printf's exponent digits.
// Bulk documented-rule checks run the recompiled body alone (call1); every family also has hand / recompiled pairs.
#include "handgen_pairs.h"

#include "p3fes/game/libc.h"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <map>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace libc = p3fes::game::libc;

namespace p3fes::recomp_gen {
void fn_abs_0051e0e0(EEContext&);  // generated body
void fn_abs_0051e0e0__recomp(EEContext&);  // recompiled
void fn_atoi_0051e0f0(EEContext&);  // generated body
void fn_atoi_0051e0f0__recomp(EEContext&);  // recompiled
void fn_bzero_0051e118(EEContext&);  // generated body
void fn_bzero_0051e118__recomp(EEContext&);  // recompiled
void fn_quorem_0051e280(EEContext&);  // generated body
void fn_quorem_0051e280__recomp(EEContext&);  // recompiled
void fn_sub_51F690_0051f690(EEContext&);  // generated body
void fn_sub_51F690_0051f690__recomp(EEContext&);  // recompiled
void fn_std_0051f838(EEContext&);  // generated body
void fn_std_0051f838__recomp(EEContext&);  // recompiled
void fn__setlocale_r_005204a0(EEContext&);  // generated body
void fn__setlocale_r_005204a0__recomp(EEContext&);  // recompiled
void fn_setlocale_00520538(EEContext&);  // generated body
void fn_setlocale_00520538__recomp(EEContext&);  // recompiled
void fn_localeconv_00520560(EEContext&);  // generated body
void fn_localeconv_00520560__recomp(EEContext&);  // recompiled
void fn__mbtowc_r_005210a8(EEContext&);  // generated body
void fn__mbtowc_r_005210a8__recomp(EEContext&);  // recompiled
void fn_memchr_005210d8(EEContext&);  // generated body
void fn_memchr_005210d8__recomp(EEContext&);  // recompiled
void fn_memcmp_005211b8(EEContext&);  // generated body
void fn_memcmp_005211b8__recomp(EEContext&);  // recompiled
void fn_memcpy_00521250(EEContext&);  // generated body
void fn_memcpy_00521250__recomp(EEContext&);  // recompiled
void fn_memmove_00521300(EEContext&);  // generated body
void fn_memmove_00521300__recomp(EEContext&);  // recompiled
void fn_memset_00521408(EEContext&);  // generated body
void fn_memset_00521408__recomp(EEContext&);  // recompiled
void fn__Bfree_00521620(EEContext&);  // generated body
void fn__Bfree_00521620__recomp(EEContext&);  // recompiled
void fn__hi0bits_00521888(EEContext&);  // generated body
void fn__hi0bits_00521888__recomp(EEContext&);  // recompiled
void fn__lo0bits_00521908(EEContext&);  // generated body
void fn__lo0bits_00521908__recomp(EEContext&);  // recompiled
void fn___mcmp_00521e70(EEContext&);  // generated body
void fn___mcmp_00521e70__recomp(EEContext&);  // recompiled
void fn__ulp_00522058(EEContext&);  // generated body
void fn__ulp_00522058__recomp(EEContext&);  // recompiled
void fn__b2d_00522118(EEContext&);  // generated body
void fn__b2d_00522118__recomp(EEContext&);  // recompiled
void fn__ratio_00522440(EEContext&);  // generated body
void fn__ratio_00522440__recomp(EEContext&);  // recompiled
void fn__mprec_log10_005224f8(EEContext&);  // generated body
void fn__mprec_log10_005224f8__recomp(EEContext&);  // recompiled
void fn_copysign_005236f0(EEContext&);  // generated body
void fn_copysign_005236f0__recomp(EEContext&);  // recompiled
void fn_scalbn_005237b0(EEContext&);  // generated body
void fn_scalbn_005237b0__recomp(EEContext&);  // recompiled
void fn_copysignf_00523980(EEContext&);  // generated body
void fn_copysignf_00523980__recomp(EEContext&);  // recompiled
void fn_scalbnf_005239a8(EEContext&);  // generated body
void fn_scalbnf_005239a8__recomp(EEContext&);  // recompiled
void fn_eofread_00523b38(EEContext&);  // generated body
void fn_eofread_00523b38__recomp(EEContext&);  // recompiled
void fn_strcasecmp_00523dc8(EEContext&);  // generated body
void fn_strcasecmp_00523dc8__recomp(EEContext&);  // recompiled
void fn_strcat_00523e68(EEContext&);  // generated body
void fn_strcat_00523e68__recomp(EEContext&);  // recompiled
void fn_strchr_00523f98(EEContext&);  // generated body
void fn_strchr_00523f98__recomp(EEContext&);  // recompiled
void fn_strcmp_00524128(EEContext&);  // generated body
void fn_strcmp_00524128__recomp(EEContext&);  // recompiled
void fn_strcpy_00524270(EEContext&);  // generated body
void fn_strcpy_00524270__recomp(EEContext&);  // recompiled
void fn_strlen_00524388(EEContext&);  // generated body
void fn_strlen_00524388__recomp(EEContext&);  // recompiled
void fn_strncat_005244c0(EEContext&);  // generated body
void fn_strncat_005244c0__recomp(EEContext&);  // recompiled
void fn_strncpy_00524828(EEContext&);  // generated body
void fn_strncpy_00524828__recomp(EEContext&);  // recompiled
void fn_strrchr_005249e8(EEContext&);  // generated body
void fn_strrchr_005249e8__recomp(EEContext&);  // recompiled
void fn_strstr_00524a50(EEContext&);  // generated body
void fn_strstr_00524a50__recomp(EEContext&);  // recompiled
void fn_strtok_00525958(EEContext&);  // generated body
void fn_strtok_00525958__recomp(EEContext&);  // recompiled
void fn__strtol_r_00525a10(EEContext&);  // generated body
void fn__strtol_r_00525a10__recomp(EEContext&);  // recompiled
void fn_strtol_00525c50(EEContext&);  // generated body
void fn_strtol_00525c50__recomp(EEContext&);  // recompiled
void fn__strtoul_r_00525c80(EEContext&);  // generated body
void fn__strtoul_r_00525c80__recomp(EEContext&);  // recompiled
void fn_strtoul_00525e98(EEContext&);  // generated body
void fn_strtoul_00525e98__recomp(EEContext&);  // recompiled
void fn_exponent_005279b8(EEContext&);  // generated body
void fn_exponent_005279b8__recomp(EEContext&);  // recompiled
void fn___sccl_005287d8(EEContext&);  // generated body
void fn___sccl_005287d8__recomp(EEContext&);  // recompiled
void fn___ieee754_acos_00528ae0(EEContext&);  // generated body
void fn___ieee754_acos_00528ae0__recomp(EEContext&);  // recompiled
void fn___ieee754_log_005290a0(EEContext&);  // generated body
void fn___ieee754_log_005290a0__recomp(EEContext&);  // recompiled
void fn___ieee754_log10_00529578(EEContext&);  // generated body
void fn___ieee754_log10_00529578__recomp(EEContext&);  // recompiled
void fn___ieee754_sqrt_0052a8c8(EEContext&);  // generated body
void fn___ieee754_sqrt_0052a8c8__recomp(EEContext&);  // recompiled
void fn___ieee754_acosf_0052abd8(EEContext&);  // generated body
void fn___ieee754_acosf_0052abd8__recomp(EEContext&);  // recompiled
void fn___ieee754_asinf_0052afe8(EEContext&);  // generated body
void fn___ieee754_asinf_0052afe8__recomp(EEContext&);  // recompiled
void fn___ieee754_powf_0052b800(EEContext&);  // generated body
void fn___ieee754_powf_0052b800__recomp(EEContext&);  // recompiled
void fn___ieee754_rem_pio2f_0052c000(EEContext&);  // generated body
void fn___ieee754_rem_pio2f_0052c000__recomp(EEContext&);  // recompiled
void fn___ieee754_sqrtf_0052c398(EEContext&);  // generated body
void fn___ieee754_sqrtf_0052c398__recomp(EEContext&);  // recompiled
void fn___kernel_cos_0052c478(EEContext&);  // generated body
void fn___kernel_cos_0052c478__recomp(EEContext&);  // recompiled
void fn___kernel_rem_pio2_0052c6d0(EEContext&);  // generated body
void fn___kernel_rem_pio2_0052c6d0__recomp(EEContext&);  // recompiled
void fn___kernel_sin_0052d108(EEContext&);  // generated body
void fn___kernel_sin_0052d108__recomp(EEContext&);  // recompiled
void fn___kernel_cosf_0052d2d8(EEContext&);  // generated body
void fn___kernel_cosf_0052d2d8__recomp(EEContext&);  // recompiled
void fn___kernel_rem_pio2f_0052d428(EEContext&);  // generated body
void fn___kernel_rem_pio2f_0052d428__recomp(EEContext&);  // recompiled
void fn___kernel_sinf_0052dc48(EEContext&);  // generated body
void fn___kernel_sinf_0052dc48__recomp(EEContext&);  // recompiled
void fn___kernel_tanf_0052dd40(EEContext&);  // generated body
void fn___kernel_tanf_0052dd40__recomp(EEContext&);  // recompiled
void fn_floor_0052e148(EEContext&);  // generated body
void fn_floor_0052e148__recomp(EEContext&);  // recompiled
void fn_atanf_0052e408(EEContext&);  // generated body
void fn_atanf_0052e408__recomp(EEContext&);  // recompiled
void fn_cosf_0052e6d8(EEContext&);  // generated body
void fn_cosf_0052e6d8__recomp(EEContext&);  // recompiled
void fn_fabsf_0052e788(EEContext&);  // generated body
void fn_fabsf_0052e788__recomp(EEContext&);  // recompiled
void fn_floorf_0052e7a0(EEContext&);  // generated body
void fn_floorf_0052e7a0__recomp(EEContext&);  // recompiled
void fn_sinf_0052e878(EEContext&);  // generated body
void fn_sinf_0052e878__recomp(EEContext&);  // recompiled
void fn_tanf_0052e930(EEContext&);  // generated body
void fn_tanf_0052e930__recomp(EEContext&);  // recompiled
void fn_acos_0052e9a0(EEContext&);  // generated body
void fn_acos_0052e9a0__recomp(EEContext&);  // recompiled
void fn_log10_0052e9b8(EEContext&);  // generated body
void fn_log10_0052e9b8__recomp(EEContext&);  // recompiled
void fn_acosf_0052e9e8(EEContext&);  // generated body
void fn_acosf_0052e9e8__recomp(EEContext&);  // recompiled
void fn_asinf_0052ea00(EEContext&);  // generated body
void fn_asinf_0052ea00__recomp(EEContext&);  // recompiled
void fn_atan2f_0052ea18(EEContext&);  // generated body
void fn_atan2f_0052ea18__recomp(EEContext&);  // recompiled
void fn_logf_0052ea30(EEContext&);  // generated body
void fn_logf_0052ea30__recomp(EEContext&);  // recompiled
void fn_powf_0052ea48(EEContext&);  // generated body
void fn_powf_0052ea48__recomp(EEContext&);  // recompiled
void fn_sqrtf_0052ea60(EEContext&);  // generated body
void fn_sqrtf_0052ea60__recomp(EEContext&);  // recompiled
void fn___muldi3_0052ea78(EEContext&);  // generated body
void fn___muldi3_0052ea78__recomp(EEContext&);  // recompiled
void fn___floatdidf_0052eac8(EEContext&);  // generated body
void fn___floatdidf_0052eac8__recomp(EEContext&);  // recompiled
void fn___floatdisf_0052eb60(EEContext&);  // generated body
void fn___floatdisf_0052eb60__recomp(EEContext&);  // recompiled
void fn___fixunsdfdi_0052ec28(EEContext&);  // generated body
void fn___fixunsdfdi_0052ec28__recomp(EEContext&);  // recompiled
void fn___fixdfdi_0052ed30(EEContext&);  // generated body
void fn___fixdfdi_0052ed30__recomp(EEContext&);  // recompiled
void fn___divdi3_0052eeb0(EEContext&);  // generated body
void fn___divdi3_0052eeb0__recomp(EEContext&);  // recompiled
void fn___udivmoddi4_0052efd8(EEContext&);  // generated body
void fn___udivmoddi4_0052efd8__recomp(EEContext&);  // recompiled
void fn___moddi3_0052f6a0(EEContext&);  // generated body
void fn___moddi3_0052f6a0__recomp(EEContext&);  // recompiled
void fn___udivmoddi4_0_0052f7d0(EEContext&);  // generated body
void fn___udivmoddi4_0_0052f7d0__recomp(EEContext&);  // recompiled
void fn___udivdi3_0052fe98(EEContext&);  // generated body
void fn___udivdi3_0052fe98__recomp(EEContext&);  // recompiled
void fn___umoddi3_00530578(EEContext&);  // generated body
void fn___umoddi3_00530578__recomp(EEContext&);  // recompiled
void fn___udivmoddi4_2_00530598(EEContext&);  // generated body
void fn___udivmoddi4_2_00530598__recomp(EEContext&);  // recompiled
void fn___pack_f_00530c60(EEContext&);  // generated body
void fn___pack_f_00530c60__recomp(EEContext&);  // recompiled
void fn___unpack_f_00530d18(EEContext&);  // generated body
void fn___unpack_f_00530d18__recomp(EEContext&);  // recompiled
void fn___make_fp_00530d70(EEContext&);  // generated body
void fn___make_fp_00530d70__recomp(EEContext&);  // recompiled
void fn___pack_d_00530de0(EEContext&);  // generated body
void fn___pack_d_00530de0__recomp(EEContext&);  // recompiled
void fn___unpack_d_00530eb8(EEContext&);  // generated body
void fn___unpack_d_00530eb8__recomp(EEContext&);  // recompiled
void fn__fpadd_parts_00530f48(EEContext&);  // generated body
void fn__fpadd_parts_00530f48__recomp(EEContext&);  // recompiled
void fn_dpadd_00531170(EEContext&);  // generated body
void fn_dpadd_00531170__recomp(EEContext&);  // recompiled
void fn_dpsub_005311c8(EEContext&);  // generated body
void fn_dpsub_005311c8__recomp(EEContext&);  // recompiled
void fn_dpmul_00531230(EEContext&);  // generated body
void fn_dpmul_00531230__recomp(EEContext&);  // recompiled
void fn__fpmul_parts_00531288(EEContext&);  // generated body
void fn__fpmul_parts_00531288__recomp(EEContext&);  // recompiled
void fn_dpdiv_00531480(EEContext&);  // generated body
void fn_dpdiv_00531480__recomp(EEContext&);  // recompiled
void fn__fpdiv_parts_005314d8(EEContext&);  // generated body
void fn__fpdiv_parts_005314d8__recomp(EEContext&);  // recompiled
void fn___fpcmp_parts_d_005315d0(EEContext&);  // generated body
void fn___fpcmp_parts_d_005315d0__recomp(EEContext&);  // recompiled
void fn_dpcmp_005316d0(EEContext&);  // generated body
void fn_dpcmp_005316d0__recomp(EEContext&);  // recompiled
void fn_litodp_00531720(EEContext&);  // generated body
void fn_litodp_00531720__recomp(EEContext&);  // recompiled
void fn_dptoli_005317d0(EEContext&);  // generated body
void fn_dptoli_005317d0__recomp(EEContext&);  // recompiled
void fn___make_dp_00531870(EEContext&);  // generated body
void fn___make_dp_00531870__recomp(EEContext&);  // recompiled
void fn_dptofp_005318a0(EEContext&);  // generated body
void fn_dptofp_005318a0__recomp(EEContext&);  // recompiled
void fn_dptoul_005318f8(EEContext&);  // generated body
void fn_dptoul_005318f8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"abs", 0x51E0E0, &recomp_gen::fn_abs_0051e0e0, &recomp_gen::fn_abs_0051e0e0__recomp},
    {"atoi", 0x51E0F0, &recomp_gen::fn_atoi_0051e0f0, &recomp_gen::fn_atoi_0051e0f0__recomp},
    {"bzero", 0x51E118, &recomp_gen::fn_bzero_0051e118, &recomp_gen::fn_bzero_0051e118__recomp},
    {"quorem", 0x51E280, &recomp_gen::fn_quorem_0051e280, &recomp_gen::fn_quorem_0051e280__recomp},
    {"sub_51F690", 0x51F690, &recomp_gen::fn_sub_51F690_0051f690, &recomp_gen::fn_sub_51F690_0051f690__recomp},
    {"std", 0x51F838, &recomp_gen::fn_std_0051f838, &recomp_gen::fn_std_0051f838__recomp},
    {"_setlocale_r", 0x5204A0, &recomp_gen::fn__setlocale_r_005204a0, &recomp_gen::fn__setlocale_r_005204a0__recomp},
    {"setlocale", 0x520538, &recomp_gen::fn_setlocale_00520538, &recomp_gen::fn_setlocale_00520538__recomp},
    {"localeconv", 0x520560, &recomp_gen::fn_localeconv_00520560, &recomp_gen::fn_localeconv_00520560__recomp},
    {"_mbtowc_r", 0x5210A8, &recomp_gen::fn__mbtowc_r_005210a8, &recomp_gen::fn__mbtowc_r_005210a8__recomp},
    {"memchr", 0x5210D8, &recomp_gen::fn_memchr_005210d8, &recomp_gen::fn_memchr_005210d8__recomp},
    {"memcmp", 0x5211B8, &recomp_gen::fn_memcmp_005211b8, &recomp_gen::fn_memcmp_005211b8__recomp},
    {"memcpy", 0x521250, &recomp_gen::fn_memcpy_00521250, &recomp_gen::fn_memcpy_00521250__recomp},
    {"memmove", 0x521300, &recomp_gen::fn_memmove_00521300, &recomp_gen::fn_memmove_00521300__recomp},
    {"memset", 0x521408, &recomp_gen::fn_memset_00521408, &recomp_gen::fn_memset_00521408__recomp},
    {"_Bfree", 0x521620, &recomp_gen::fn__Bfree_00521620, &recomp_gen::fn__Bfree_00521620__recomp},
    {"_hi0bits", 0x521888, &recomp_gen::fn__hi0bits_00521888, &recomp_gen::fn__hi0bits_00521888__recomp},
    {"_lo0bits", 0x521908, &recomp_gen::fn__lo0bits_00521908, &recomp_gen::fn__lo0bits_00521908__recomp},
    {"__mcmp", 0x521E70, &recomp_gen::fn___mcmp_00521e70, &recomp_gen::fn___mcmp_00521e70__recomp},
    {"_ulp", 0x522058, &recomp_gen::fn__ulp_00522058, &recomp_gen::fn__ulp_00522058__recomp},
    {"_b2d", 0x522118, &recomp_gen::fn__b2d_00522118, &recomp_gen::fn__b2d_00522118__recomp},
    {"_ratio", 0x522440, &recomp_gen::fn__ratio_00522440, &recomp_gen::fn__ratio_00522440__recomp},
    {"_mprec_log10", 0x5224F8, &recomp_gen::fn__mprec_log10_005224f8, &recomp_gen::fn__mprec_log10_005224f8__recomp},
    {"copysign", 0x5236F0, &recomp_gen::fn_copysign_005236f0, &recomp_gen::fn_copysign_005236f0__recomp},
    {"scalbn", 0x5237B0, &recomp_gen::fn_scalbn_005237b0, &recomp_gen::fn_scalbn_005237b0__recomp},
    {"copysignf", 0x523980, &recomp_gen::fn_copysignf_00523980, &recomp_gen::fn_copysignf_00523980__recomp},
    {"scalbnf", 0x5239A8, &recomp_gen::fn_scalbnf_005239a8, &recomp_gen::fn_scalbnf_005239a8__recomp},
    {"eofread", 0x523B38, &recomp_gen::fn_eofread_00523b38, &recomp_gen::fn_eofread_00523b38__recomp},
    {"strcasecmp", 0x523DC8, &recomp_gen::fn_strcasecmp_00523dc8, &recomp_gen::fn_strcasecmp_00523dc8__recomp},
    {"strcat", 0x523E68, &recomp_gen::fn_strcat_00523e68, &recomp_gen::fn_strcat_00523e68__recomp},
    {"strchr", 0x523F98, &recomp_gen::fn_strchr_00523f98, &recomp_gen::fn_strchr_00523f98__recomp},
    {"strcmp", 0x524128, &recomp_gen::fn_strcmp_00524128, &recomp_gen::fn_strcmp_00524128__recomp},
    {"strcpy", 0x524270, &recomp_gen::fn_strcpy_00524270, &recomp_gen::fn_strcpy_00524270__recomp},
    {"strlen", 0x524388, &recomp_gen::fn_strlen_00524388, &recomp_gen::fn_strlen_00524388__recomp},
    {"strncat", 0x5244C0, &recomp_gen::fn_strncat_005244c0, &recomp_gen::fn_strncat_005244c0__recomp},
    {"strncpy", 0x524828, &recomp_gen::fn_strncpy_00524828, &recomp_gen::fn_strncpy_00524828__recomp},
    {"strrchr", 0x5249E8, &recomp_gen::fn_strrchr_005249e8, &recomp_gen::fn_strrchr_005249e8__recomp},
    {"strstr", 0x524A50, &recomp_gen::fn_strstr_00524a50, &recomp_gen::fn_strstr_00524a50__recomp},
    {"strtok", 0x525958, &recomp_gen::fn_strtok_00525958, &recomp_gen::fn_strtok_00525958__recomp},
    {"_strtol_r", 0x525A10, &recomp_gen::fn__strtol_r_00525a10, &recomp_gen::fn__strtol_r_00525a10__recomp},
    {"strtol", 0x525C50, &recomp_gen::fn_strtol_00525c50, &recomp_gen::fn_strtol_00525c50__recomp},
    {"_strtoul_r", 0x525C80, &recomp_gen::fn__strtoul_r_00525c80, &recomp_gen::fn__strtoul_r_00525c80__recomp},
    {"strtoul", 0x525E98, &recomp_gen::fn_strtoul_00525e98, &recomp_gen::fn_strtoul_00525e98__recomp},
    {"exponent", 0x5279B8, &recomp_gen::fn_exponent_005279b8, &recomp_gen::fn_exponent_005279b8__recomp},
    {"__sccl", 0x5287D8, &recomp_gen::fn___sccl_005287d8, &recomp_gen::fn___sccl_005287d8__recomp},
    {"__ieee754_acos", 0x528AE0, &recomp_gen::fn___ieee754_acos_00528ae0, &recomp_gen::fn___ieee754_acos_00528ae0__recomp},
    {"__ieee754_log", 0x5290A0, &recomp_gen::fn___ieee754_log_005290a0, &recomp_gen::fn___ieee754_log_005290a0__recomp},
    {"__ieee754_log10", 0x529578, &recomp_gen::fn___ieee754_log10_00529578, &recomp_gen::fn___ieee754_log10_00529578__recomp},
    {"__ieee754_sqrt", 0x52A8C8, &recomp_gen::fn___ieee754_sqrt_0052a8c8, &recomp_gen::fn___ieee754_sqrt_0052a8c8__recomp},
    {"__ieee754_acosf", 0x52ABD8, &recomp_gen::fn___ieee754_acosf_0052abd8, &recomp_gen::fn___ieee754_acosf_0052abd8__recomp},
    {"__ieee754_asinf", 0x52AFE8, &recomp_gen::fn___ieee754_asinf_0052afe8, &recomp_gen::fn___ieee754_asinf_0052afe8__recomp},
    {"__ieee754_powf", 0x52B800, &recomp_gen::fn___ieee754_powf_0052b800, &recomp_gen::fn___ieee754_powf_0052b800__recomp},
    {"__ieee754_rem_pio2f", 0x52C000, &recomp_gen::fn___ieee754_rem_pio2f_0052c000, &recomp_gen::fn___ieee754_rem_pio2f_0052c000__recomp},
    {"__ieee754_sqrtf", 0x52C398, &recomp_gen::fn___ieee754_sqrtf_0052c398, &recomp_gen::fn___ieee754_sqrtf_0052c398__recomp},
    {"__kernel_cos", 0x52C478, &recomp_gen::fn___kernel_cos_0052c478, &recomp_gen::fn___kernel_cos_0052c478__recomp},
    {"__kernel_rem_pio2", 0x52C6D0, &recomp_gen::fn___kernel_rem_pio2_0052c6d0, &recomp_gen::fn___kernel_rem_pio2_0052c6d0__recomp},
    {"__kernel_sin", 0x52D108, &recomp_gen::fn___kernel_sin_0052d108, &recomp_gen::fn___kernel_sin_0052d108__recomp},
    {"__kernel_cosf", 0x52D2D8, &recomp_gen::fn___kernel_cosf_0052d2d8, &recomp_gen::fn___kernel_cosf_0052d2d8__recomp},
    {"__kernel_rem_pio2f", 0x52D428, &recomp_gen::fn___kernel_rem_pio2f_0052d428, &recomp_gen::fn___kernel_rem_pio2f_0052d428__recomp},
    {"__kernel_sinf", 0x52DC48, &recomp_gen::fn___kernel_sinf_0052dc48, &recomp_gen::fn___kernel_sinf_0052dc48__recomp},
    {"__kernel_tanf", 0x52DD40, &recomp_gen::fn___kernel_tanf_0052dd40, &recomp_gen::fn___kernel_tanf_0052dd40__recomp},
    {"floor", 0x52E148, &recomp_gen::fn_floor_0052e148, &recomp_gen::fn_floor_0052e148__recomp},
    {"atanf", 0x52E408, &recomp_gen::fn_atanf_0052e408, &recomp_gen::fn_atanf_0052e408__recomp},
    {"cosf", 0x52E6D8, &recomp_gen::fn_cosf_0052e6d8, &recomp_gen::fn_cosf_0052e6d8__recomp},
    {"fabsf", 0x52E788, &recomp_gen::fn_fabsf_0052e788, &recomp_gen::fn_fabsf_0052e788__recomp},
    {"floorf", 0x52E7A0, &recomp_gen::fn_floorf_0052e7a0, &recomp_gen::fn_floorf_0052e7a0__recomp},
    {"sinf", 0x52E878, &recomp_gen::fn_sinf_0052e878, &recomp_gen::fn_sinf_0052e878__recomp},
    {"tanf", 0x52E930, &recomp_gen::fn_tanf_0052e930, &recomp_gen::fn_tanf_0052e930__recomp},
    {"acos", 0x52E9A0, &recomp_gen::fn_acos_0052e9a0, &recomp_gen::fn_acos_0052e9a0__recomp},
    {"log10", 0x52E9B8, &recomp_gen::fn_log10_0052e9b8, &recomp_gen::fn_log10_0052e9b8__recomp},
    {"acosf", 0x52E9E8, &recomp_gen::fn_acosf_0052e9e8, &recomp_gen::fn_acosf_0052e9e8__recomp},
    {"asinf", 0x52EA00, &recomp_gen::fn_asinf_0052ea00, &recomp_gen::fn_asinf_0052ea00__recomp},
    {"atan2f", 0x52EA18, &recomp_gen::fn_atan2f_0052ea18, &recomp_gen::fn_atan2f_0052ea18__recomp},
    {"logf", 0x52EA30, &recomp_gen::fn_logf_0052ea30, &recomp_gen::fn_logf_0052ea30__recomp},
    {"powf", 0x52EA48, &recomp_gen::fn_powf_0052ea48, &recomp_gen::fn_powf_0052ea48__recomp},
    {"sqrtf", 0x52EA60, &recomp_gen::fn_sqrtf_0052ea60, &recomp_gen::fn_sqrtf_0052ea60__recomp},
    {"__muldi3", 0x52EA78, &recomp_gen::fn___muldi3_0052ea78, &recomp_gen::fn___muldi3_0052ea78__recomp},
    {"__floatdidf", 0x52EAC8, &recomp_gen::fn___floatdidf_0052eac8, &recomp_gen::fn___floatdidf_0052eac8__recomp},
    {"__floatdisf", 0x52EB60, &recomp_gen::fn___floatdisf_0052eb60, &recomp_gen::fn___floatdisf_0052eb60__recomp},
    {"__fixunsdfdi", 0x52EC28, &recomp_gen::fn___fixunsdfdi_0052ec28, &recomp_gen::fn___fixunsdfdi_0052ec28__recomp},
    {"__fixdfdi", 0x52ED30, &recomp_gen::fn___fixdfdi_0052ed30, &recomp_gen::fn___fixdfdi_0052ed30__recomp},
    {"__divdi3", 0x52EEB0, &recomp_gen::fn___divdi3_0052eeb0, &recomp_gen::fn___divdi3_0052eeb0__recomp},
    {"__udivmoddi4", 0x52EFD8, &recomp_gen::fn___udivmoddi4_0052efd8, &recomp_gen::fn___udivmoddi4_0052efd8__recomp},
    {"__moddi3", 0x52F6A0, &recomp_gen::fn___moddi3_0052f6a0, &recomp_gen::fn___moddi3_0052f6a0__recomp},
    {"__udivmoddi4_0", 0x52F7D0, &recomp_gen::fn___udivmoddi4_0_0052f7d0, &recomp_gen::fn___udivmoddi4_0_0052f7d0__recomp},
    {"__udivdi3", 0x52FE98, &recomp_gen::fn___udivdi3_0052fe98, &recomp_gen::fn___udivdi3_0052fe98__recomp},
    {"__umoddi3", 0x530578, &recomp_gen::fn___umoddi3_00530578, &recomp_gen::fn___umoddi3_00530578__recomp},
    {"__udivmoddi4_2", 0x530598, &recomp_gen::fn___udivmoddi4_2_00530598, &recomp_gen::fn___udivmoddi4_2_00530598__recomp},
    {"__pack_f", 0x530C60, &recomp_gen::fn___pack_f_00530c60, &recomp_gen::fn___pack_f_00530c60__recomp},
    {"__unpack_f", 0x530D18, &recomp_gen::fn___unpack_f_00530d18, &recomp_gen::fn___unpack_f_00530d18__recomp},
    {"__make_fp", 0x530D70, &recomp_gen::fn___make_fp_00530d70, &recomp_gen::fn___make_fp_00530d70__recomp},
    {"__pack_d", 0x530DE0, &recomp_gen::fn___pack_d_00530de0, &recomp_gen::fn___pack_d_00530de0__recomp},
    {"__unpack_d", 0x530EB8, &recomp_gen::fn___unpack_d_00530eb8, &recomp_gen::fn___unpack_d_00530eb8__recomp},
    {"_fpadd_parts", 0x530F48, &recomp_gen::fn__fpadd_parts_00530f48, &recomp_gen::fn__fpadd_parts_00530f48__recomp},
    {"dpadd", 0x531170, &recomp_gen::fn_dpadd_00531170, &recomp_gen::fn_dpadd_00531170__recomp},
    {"dpsub", 0x5311C8, &recomp_gen::fn_dpsub_005311c8, &recomp_gen::fn_dpsub_005311c8__recomp},
    {"dpmul", 0x531230, &recomp_gen::fn_dpmul_00531230, &recomp_gen::fn_dpmul_00531230__recomp},
    {"_fpmul_parts", 0x531288, &recomp_gen::fn__fpmul_parts_00531288, &recomp_gen::fn__fpmul_parts_00531288__recomp},
    {"dpdiv", 0x531480, &recomp_gen::fn_dpdiv_00531480, &recomp_gen::fn_dpdiv_00531480__recomp},
    {"_fpdiv_parts", 0x5314D8, &recomp_gen::fn__fpdiv_parts_005314d8, &recomp_gen::fn__fpdiv_parts_005314d8__recomp},
    {"__fpcmp_parts_d", 0x5315D0, &recomp_gen::fn___fpcmp_parts_d_005315d0, &recomp_gen::fn___fpcmp_parts_d_005315d0__recomp},
    {"dpcmp", 0x5316D0, &recomp_gen::fn_dpcmp_005316d0, &recomp_gen::fn_dpcmp_005316d0__recomp},
    {"litodp", 0x531720, &recomp_gen::fn_litodp_00531720, &recomp_gen::fn_litodp_00531720__recomp},
    {"dptoli", 0x5317D0, &recomp_gen::fn_dptoli_005317d0, &recomp_gen::fn_dptoli_005317d0__recomp},
    {"__make_dp", 0x531870, &recomp_gen::fn___make_dp_00531870, &recomp_gen::fn___make_dp_00531870__recomp},
    {"dptofp", 0x5318A0, &recomp_gen::fn_dptofp_005318a0, &recomp_gen::fn_dptofp_005318a0__recomp},
    {"dptoul", 0x5318F8, &recomp_gen::fn_dptoul_005318f8, &recomp_gen::fn_dptoul_005318f8__recomp},
};


// --- helpers -----------------------------------------------------------------------------------------------------------

constexpr u32 kWorld = 0x01810000u;  // 64 KiB of free RAM above the harness's arena: buffers, strings, records
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;            // generic sweep: pairs per function (P3FES_HG_SEEDS overrides)
constexpr u32 kSrc = kWorld + 0x0100u, kDst = kWorld + 0x4000u, kAux = kWorld + 0x8000u, kOut = kWorld + 0xC000u;

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, name) == 0) return c;
    std::fprintf(stderr, "test_libc: no case %s\n", name);
    std::abort();
}

std::map<std::string, int> g_pairs;  // pairs per function (the meaningful sections)

// One pair, hand vs recompiled: everything hgp::pair compares (registers and cycles at every check point and at the
// return, all of RAM with the dead stack, scratchpad, BIOS window, bus). Afterwards the recompiled run's memory is in place.
hgp::Run pair_fn(Machine& m, const char* fn, Args a, u32 seed) {
    const Case& c = find_case(fn);
    ++g_pairs[fn];
    return hgp::pair(m, c.hand, c.recomp, a, seed, fn);
}

// $f12 / $f13 arguments: both bodies of a pair start through a wrapper that sets them (after the random register file).
u32 g_f12 = 0, g_f13 = 0;
Fn g_hand = nullptr, g_recomp = nullptr;
void hand_f(EEContext& c) {
    c.fpr[12] = g_f12;
    c.fpr[13] = g_f13;
    g_hand(c);
}
void recomp_f(EEContext& c) {
    c.fpr[12] = g_f12;
    c.fpr[13] = g_f13;
    g_recomp(c);
}
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float bitsf(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
u64 dbits(double d) {
    u64 b;
    std::memcpy(&b, &d, 8);
    return b;
}
double bitsd(u64 b) {
    double d;
    std::memcpy(&d, &b, 8);
    return d;
}
hgp::Run pair_f(Machine& m, const char* fn, Args a, float x, float y, u32 seed) {
    const Case& c = find_case(fn);
    g_f12 = fbits(x);
    g_f13 = fbits(y);
    g_hand = c.hand;
    g_recomp = c.recomp;
    ++g_pairs[fn];
    return hgp::pair(m, &hand_f, &recomp_f, a, seed, fn);
}

// One run of the recompiled body (the original program) for the bulk documented-rule checks: $v0 and $f0 back.
struct One {
    u64 v0 = 0;
    u32 f0 = 0;
    bool stopped = false;
};
One call1(Machine& m, const char* fn, Args a, u32 f12 = 0, u32 f13 = 0) {
    const Fn body = find_case(fn).recomp;
    rt_test::HooksScope scope{&m.hooks};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{1};
    m.fresh_context(a, rng);
    m.ctx.fpr[12] = f12;
    m.ctx.fpr[13] = f13;
    One o;
    try {
        body(m.ctx);
    } catch (const rt_test::FatalEvent&) {
        o.stopped = true;
    }
    o.v0 = m.ctx.gpr[GPR_V0].u64[0];
    o.f0 = m.ctx.fpr[0];
    return o;
}

u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u64 r64(Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.at(va), 8);
    return v;
}
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }

// Distance in units in the last place between two finite values of the same type (bit patterns as signed magnitude).
s64 ulps_d(double a, double b) {
    auto key = [](double x) {
        const s64 i = static_cast<s64>(dbits(x));
        return i < 0 ? static_cast<s64>(0x8000000000000000ull) - i : i;
    };
    const s64 d = key(a) - key(b);
    return d < 0 ? -d : d;
}
s64 ulps_f(float a, float b) {
    auto key = [](float x) {
        const s32 i = static_cast<s32>(fbits(x));
        return i < 0 ? static_cast<s64>(INT32_MIN) - i : static_cast<s64>(i);
    };
    const s64 d = key(a) - key(b);
    return d < 0 ? -d : d;
}

std::string rand_text(std::mt19937& rng, std::size_t n, bool ascii) {
    std::string s(n, ' ');
    for (char& ch : s) {
        const u32 k = rng() % 10;
        ch = static_cast<char>(k < 3 ? 'A' + rng() % 26 : k < 6 ? 'a' + rng() % 26 : ascii ? 1 + rng() % 127 : 1 + rng() % 255);
    }
    return s;
}
std::size_t rand_len(std::mt19937& rng) {
    static const std::size_t edges[] = {0, 1, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64, 100};
    return rng() % 3 == 0 ? edges[rng() % std::size(edges)] : rng() % 300;
}

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}

void report_pairs(const char* section) {
    int total = 0;
    std::string s;
    for (const auto& [fn, n] : g_pairs) {
        total += n;
        s += " " + fn + " " + std::to_string(n);
    }
    const std::string line = std::string(section) + ": " + std::to_string(total) + " pairs:" + s;
    MESSAGE(line);
    g_pairs.clear();
}

}  // namespace

// ======================================================================================================================
// 1. The generic sweep: every body against its recompiled body on random worlds (mostly bad-input paths).
TEST_CASE("game(libc): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    u32 pairs = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("generic sweep: " << pairs << " pairs, " << stops << " stopped early (identically)");
}

// ======================================================================================================================
// 2. <string.h> on random buffers and strings at every alignment, against the host's own functions.
TEST_CASE("game(libc): string and memory functions on random buffers") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{20261022u};
    u32 seed = 1;
    for (int round = 0; round < 24; ++round) {
        const u32 sa = kSrc + rng() % 32, da = kDst + rng() % 32;
        const std::size_t n = rand_len(rng);
        std::vector<u8> src(n + 64), dst0(n + 64);
        for (u8& b : src) b = static_cast<u8>(rng());
        for (u8& b : dst0) b = static_cast<u8>(rng());
        auto load = [&] {
            std::memcpy(m->at(sa), src.data(), src.size());
            std::memcpy(m->at(da), dst0.data(), dst0.size());
        };
        // memcpy: the n bytes, nothing after them; returns dst
        load();
        hgp::Run r = pair_fn(*m, "memcpy", {sx(da), sx(sa), n, 0}, seed++);
        CHECK(std::memcmp(m->at(da), src.data(), n) == 0);
        CHECK(std::memcmp(m->at(da + static_cast<u32>(n)), dst0.data() + n, 64) == 0);
        CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == da);
        // memmove inside one buffer, both directions of overlap
        for (int dir = 0; dir < 2; ++dir) {
            load();
            const u32 k = 1 + rng() % 40;
            const u32 from = dir ? sa : sa + k, to = dir ? sa + k : sa;
            std::vector<u8> ref(src);
            const std::size_t len = n;  // to + n stays inside the n + 64 bytes loaded at sa
            std::memmove(ref.data() + (to - sa), ref.data() + (from - sa), len);
            r = pair_fn(*m, "memmove", {sx(to), sx(from), len, 0}, seed++);
            CHECK(std::memcmp(m->at(sa), ref.data(), src.size()) == 0);
            CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == to);
        }
        // memset / bzero
        load();
        const u32 c = rng() & 0x1FF;  // only the low byte counts
        r = pair_fn(*m, "memset", {sx(da), c, n, 0}, seed++);
        for (std::size_t i = 0; i < n; ++i) CHECK(m->at(da)[i] == static_cast<u8>(c));
        CHECK(std::memcmp(m->at(da + static_cast<u32>(n)), dst0.data() + n, 64) == 0);
        CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == da);
        load();
        pair_fn(*m, "bzero", {sx(da), n, 0, 0}, seed++);
        for (std::size_t i = 0; i < n; ++i) CHECK(m->at(da)[i] == 0);
        CHECK(m->at(da + static_cast<u32>(n))[0] == dst0[n]);
        // memcmp: equal, or one byte changed (the sign and value are a[i] - b[i] as unsigned chars)
        load();
        std::memcpy(m->at(da), src.data(), n);
        int want = 0;
        if (n && rng() % 4) {
            const std::size_t at = rng() % n;
            const u8 b = static_cast<u8>(rng());
            m->at(da)[at] = b;
            want = src[at] - b;
        }
        r = pair_fn(*m, "memcmp", {sx(sa), sx(da), n, 0}, seed++);
        CHECK(static_cast<s32>(r.end.gpr[GPR_V0].u64[0]) == want);
        // memchr
        load();
        const u8 key = n && rng() % 2 ? src[rng() % n] : static_cast<u8>(rng());
        r = pair_fn(*m, "memchr", {sx(sa), key | 0x100u, n, 0}, seed++);
        const void* hit = std::memchr(src.data(), key, n);
        const u32 want_hit = hit ? sa + static_cast<u32>(static_cast<const u8*>(hit) - src.data()) : 0;
        CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == want_hit);
    }
    for (int round = 0; round < 24; ++round) {
        const bool ascii = round % 2 == 0;
        const u32 sa = kSrc + (round % 4 == 0 ? 0 : rng() % 32), da = kDst + (round % 4 == 0 ? 0 : rng() % 32);
        const std::string s = rand_text(rng, rand_len(rng), ascii);
        std::string d0 = rand_text(rng, rng() % 40, ascii);
        auto load = [&] {
            std::memset(m->at(kSrc), 0x5A, 0x400);
            std::memset(m->at(kDst), 0xA5, 0x800);
            m->put(sa, s);
            m->put(da, d0);
        };
        load();
        hgp::Run r = pair_fn(*m, "strlen", {sx(sa), 0, 0, 0}, seed++);
        CHECK(r.end.gpr[GPR_V0].u64[0] == s.size());
        load();
        r = pair_fn(*m, "strcpy", {sx(da), sx(sa), 0, 0}, seed++);
        CHECK(m->str(da, 2048) == s);
        CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == da);
        load();
        pair_fn(*m, "strcat", {sx(da), sx(sa), 0, 0}, seed++);
        CHECK(m->str(da, 2048) == d0 + s);
        load();
        std::size_t k = rng() % (s.size() + 3);
        pair_fn(*m, "strncat", {sx(da), sx(sa), k, 0}, seed++);
        CHECK(m->str(da, 2048) == d0 + s.substr(0, std::min(k, s.size())));
        load();
        k = rng() % (s.size() + 8);
        {
            const std::vector<u8> before = m->bytes(da, static_cast<u32>(k) + 1);
            pair_fn(*m, "strncpy", {sx(da), sx(sa), k, 0}, seed++);
            // k bytes written: the source bytes, then NUL padding up to k; the byte after them untouched
            for (std::size_t i = 0; i < k; ++i) CHECK(m->at(da)[i] == (i < s.size() ? static_cast<u8>(s[i]) : 0));
            CHECK(m->at(da + static_cast<u32>(k))[0] == before[k]);
        }
        // strcmp / strcasecmp: against a copy with one byte changed (or equal, or a prefix)
        std::string t = s;
        if (!t.empty()) {
            const u32 mode = rng() % 4;
            if (mode == 1) t[rng() % t.size()] = static_cast<char>(1 + rng() % (ascii ? 127 : 255));
            if (mode == 2) t.resize(rng() % t.size());
            if (mode == 3 && ascii)
                for (char& ch : t) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
        }
        load();
        m->put(kAux, t);
        r = pair_fn(*m, "strcmp", {sx(sa), sx(kAux), 0, 0}, seed++);
        {
            const int h = std::strcmp(s.c_str(), t.c_str());
            const s32 g = static_cast<s32>(r.end.gpr[GPR_V0].u64[0]);
            CHECK((g < 0) == (h < 0));
            CHECK((g == 0) == (h == 0));
            // the value is the difference of the first differing bytes as unsigned chars
            std::size_t i = 0;
            while (i < s.size() && s[i] == t[i]) ++i;
            CHECK(g == static_cast<u8>(s.c_str()[i]) - static_cast<u8>(t.c_str()[i]));
        }
        if (ascii) {
            r = pair_fn(*m, "strcasecmp", {sx(sa), sx(kAux), 0, 0}, seed++);
            std::size_t i = 0;
            auto low = [](char ch) { return std::tolower(static_cast<unsigned char>(ch)); };
            while (i < s.size() && low(s[i]) == low(t.c_str()[i])) ++i;
            CHECK(static_cast<s32>(r.end.gpr[GPR_V0].u64[0]) == low(s.c_str()[i]) - low(t.c_str()[i]));
        }
        // strchr / strrchr (c == 0 finds the terminator) / strstr
        const char ch = s.empty() || rng() % 3 == 0 ? static_cast<char>(rng() % 3 ? 'q' : 0) : s[rng() % s.size()];
        load();
        r = pair_fn(*m, "strchr", {sx(sa), static_cast<u8>(ch) | 0x300u, 0, 0}, seed++);
        {
            const char* h = std::strchr(s.c_str(), ch);
            CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == (h ? sa + static_cast<u32>(h - s.c_str()) : 0));
        }
        r = pair_fn(*m, "strrchr", {sx(sa), static_cast<u8>(ch), 0, 0}, seed++);
        {
            const char* h = std::strrchr(s.c_str(), ch);
            CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == (h ? sa + static_cast<u32>(h - s.c_str()) : 0));
        }
        std::string needle;
        if (!s.empty() && rng() % 3) {
            const std::size_t at = rng() % s.size();
            needle = s.substr(at, 1 + rng() % 6);
        } else if (rng() % 2) {
            needle = "zz@";
        }
        m->put(kAux, needle);
        r = pair_fn(*m, "strstr", {sx(sa), sx(kAux), 0, 0}, seed++);
        {
            const char* h = std::strstr(s.c_str(), needle.c_str());
            CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == (h ? sa + static_cast<u32>(h - s.c_str()) : 0));
        }
    }
    report_pairs("string / memory");
}

// ======================================================================================================================
// 3. State over several calls: strtok's saved position in the _reent, setlocale's category / name.
TEST_CASE("game(libc): strtok and setlocale keep their state in the _reent over several calls") {
    auto m = machine();
    if (!m) return;
    const u32 reent = r32(*m, libc::kImpurePtr);
    REQUIRE(reent != 0);
    u32 seed = 1;
    const char* inputs[] = {"  alpha,beta,,gamma  ", ",,,", "", "one", "a b\tc,d", "x,,y,"};
    for (const char* in : inputs) {
        std::string host(in);
        m->put(kSrc, in);
        m->put(kAux, " ,\t");
        std::vector<std::string> want;
        for (char* t = std::strtok(host.data(), " ,\t"); t; t = std::strtok(nullptr, " ,\t")) want.push_back(t);
        std::vector<std::string> got;
        for (int call = 0; call < 8; ++call) {
            hgp::Run r = pair_fn(*m, "strtok", {call == 0 ? sx(kSrc) : 0, sx(kAux), 0, 0}, seed++);
            const u32 tok = static_cast<u32>(r.end.gpr[GPR_V0].u64[0]);
            const u32 saved = r32(*m, reent + libc::reent::kStrtokLast);
            if (!tok) {
                CHECK(saved == 0);  // the end cleared the saved position
                break;
            }
            got.push_back(m->str(tok));
            CHECK((saved == 0 || (saved > tok && saved <= kSrc + std::strlen(in))));
        }
        CHECK(got == want);
    }
    // setlocale: "C" accepted (stored with its category), NULL queries, anything else refused (NULL, no change)
    const u32 kC = 0x7BEB60u, kOther = 0x7BEB28u;
    CHECK(m->str(kC) == "C");
    m->put(kAux, "C");
    m->put(kAux + 0x40, "fr_FR");
    struct Step {
        u32 cat, name;
        u32 want;
    };
    const std::string other = m->str(kOther);
    m->put(kAux + 0x80, other);
    const Step steps[] = {{6, kAux, kC}, {2, 0, kC}, {3, kAux + 0x40, 0}, {4, kAux + 0x80, kC}, {0, kAux, kC}, {5, 0, kC}};
    u32 cat = r32(*m, reent + libc::reent::kCategory), name = r32(*m, reent + libc::reent::kLocale);
    for (const Step& st : steps) {
        hgp::Run r = pair_fn(*m, "setlocale", {st.cat, st.name ? sx(st.name) : 0, 0, 0}, seed++);
        CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == st.want);
        if (st.name && st.want) {
            cat = st.cat;
            name = st.name;
        }
        CHECK(r32(*m, reent + libc::reent::kCategory) == cat);
        CHECK(r32(*m, reent + libc::reent::kLocale) == name);
    }
    hgp::Run r = pair_fn(*m, "localeconv", {0, 0, 0, 0}, seed++);
    CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == 0x7BEB30u);
    // __errno: the _reent itself
    r = pair_fn(*m, "sub_51F690", {0, 0, 0, 0}, seed++);
    CHECK(static_cast<u32>(r.end.gpr[GPR_V0].u64[0]) == reent);
    // _mbtowc_r: the C locale's single bytes
    m->put(kSrc, "A");
    r = pair_fn(*m, "_mbtowc_r", {sx(reent), sx(kOut), sx(kSrc), 1}, seed++);
    CHECK(r.end.gpr[GPR_V0].u64[0] == 1);
    CHECK(r32(*m, kOut) == 'A');
    r = pair_fn(*m, "_mbtowc_r", {sx(reent), sx(kOut), sx(kSrc), 0}, seed++);
    CHECK(static_cast<s64>(r.end.gpr[GPR_V0].u64[0]) == -1);
    r = pair_fn(*m, "_mbtowc_r", {sx(reent), 0, 0, 1}, seed++);
    CHECK(r.end.gpr[GPR_V0].u64[0] == 0);
    report_pairs("state");
}

// ======================================================================================================================
// 4. strtol / strtoul / atoi (long is 64-bit in this build) against the host's strtoll / strtoull: value, end
//    pointer, errno = ERANGE on overflow.
TEST_CASE("game(libc): strtol, strtoul and atoi follow the C standard") {
    auto m = machine();
    if (!m) return;
    const u32 reent = r32(*m, libc::kImpurePtr);
    std::mt19937 rng{77u};
    const int bases[] = {0, 2, 8, 10, 16, 36, 0, 10};
    const char* fixed[] = {"0", "-0", "  42", "+17x", "0x1F", "0X", "077", "-9223372036854775808", "9223372036854775807",
                           "9223372036854775808", "-9223372036854775809", "18446744073709551615", "18446744073709551616",
                           "zz", "  -", "", "\t\n 123abc", "0b101", "-1"};
    u32 seed = 1, checks = 0;
    for (int i = 0; i < 400; ++i) {
        std::string s;
        int base = bases[rng() % std::size(bases)];
        if (i < static_cast<int>(std::size(fixed)) * 3) {
            s = fixed[i % std::size(fixed)];
            base = i / static_cast<int>(std::size(fixed)) == 0 ? 0 : i / static_cast<int>(std::size(fixed)) == 1 ? 10 : 16;
        } else {
            static const char* pre[] = {"", " ", "  \t", "-", "+", "0x", "-0x", "0"};
            s = pre[rng() % std::size(pre)];
            const int digits = 1 + rng() % 24;
            for (int d = 0; d < digits; ++d) s += "0123456789abcdefghijklmnopqrstuvwxyzABCXYZ"[rng() % 42];
            if (rng() % 4 == 0) s += "!";
        }
        m->put(kSrc, s);
        for (int which = 0; which < 2; ++which) {
            const char* fn = which ? "strtoul" : "strtol";
            w32(*m, reent + libc::reent::kErrno, 0);
            w32(*m, kOut, 0xDEADBEEFu);
            const bool paired = i % 8 == 0;
            u64 v0;
            if (paired) {
                v0 = pair_fn(*m, fn, {sx(kSrc), sx(kOut), static_cast<u64>(base), 0}, seed++).end.gpr[GPR_V0].u64[0];
            } else {
                v0 = call1(*m, fn, {sx(kSrc), sx(kOut), static_cast<u64>(base), 0}).v0;
            }
            char* end = nullptr;
            errno = 0;
            const u64 want = which ? static_cast<u64>(std::strtoull(s.c_str(), &end, base)) : static_cast<u64>(std::strtoll(s.c_str(), &end, base));
            const bool range = errno == ERANGE;
            INFO(fn << "(\"" << s << "\", " << base << ")");
            CHECK(v0 == want);
            CHECK(r32(*m, kOut) == kSrc + static_cast<u32>(end - s.c_str()));
            CHECK((r32(*m, reent + libc::reent::kErrno) == 34) == range);
            ++checks;
        }
        if (base == 10 && i % 4 == 0) {
            const u64 v = call1(*m, "atoi", {sx(kSrc), 0, 0, 0}).v0;
            CHECK(v == sx(static_cast<u32>(std::strtoll(s.c_str(), nullptr, 10))));
        }
    }
    // abs
    for (s32 j : {0, 1, -1, 123, -123, INT32_MAX, INT32_MIN + 1, INT32_MIN}) {
        const u64 v = pair_fn(*m, "abs", {sx(static_cast<u32>(j)), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0];
        CHECK(static_cast<s32>(v) == (j == INT32_MIN ? INT32_MIN : std::abs(j)));
    }
    MESSAGE("strtol / strtoul: " << checks << " conversions checked against the host");
    report_pairs("strtol");
}

// ======================================================================================================================
// 5. libgcc's 64-bit integer helpers against host u64 / s64 arithmetic.
TEST_CASE("game(libc): 64-bit multiply, divide and modulo equal host u64 / s64 arithmetic") {
    auto m = machine();
    if (!m) return;
    std::mt19937_64 rng{0x5EEDull};
    auto value = [&](int k) -> u64 {
        switch (k % 8) {
            case 0: return rng() >> (rng() % 64);                  // any bit length
            case 1: return 1ull << (rng() % 64);                   // a power of two
            case 2: return ~0ull - (rng() % 4);                    // near UINT64_MAX
            case 3: return 0x8000000000000000ull + (rng() % 3);    // near INT64_MIN
            case 4: return rng() % 1000;                           // small
            case 5: return (rng() % 0xFFFFFFFFull) + 1;            // one 32-bit digit
            case 6: return (rng() | 0x8000000000000000ull) >> (rng() % 32);
            default: return rng();
        }
    };
    u32 seed = 1, bulk = 0;
    for (int i = 0; i < 3000; ++i) {
        const u64 a = value(static_cast<int>(rng() % 8)), b = value(static_cast<int>(rng() % 8));
        const bool paired = i % 50 == 0;
        auto run = [&](const char* fn, u64 x, u64 y, u64 z = 0) {
            return paired ? pair_fn(*m, fn, {x, y, z, 0}, seed++).end.gpr[GPR_V0].u64[0] : call1(*m, fn, {x, y, z, 0}).v0;
        };
        INFO("a=" << hex64(a) << " b=" << hex64(b));
        CHECK(run("__muldi3", a, b) == a * b);
        if (b == 0) continue;  // division by zero traps (break 7) in the original
        CHECK(run("__udivdi3", a, b) == a / b);
        CHECK(run("__umoddi3", a, b) == a % b);
        w64(*m, kOut, 0x1111111111111111ull);
        CHECK(run("__udivmoddi4", a, b, sx(kOut)) == a / b);
        CHECK(r64(*m, kOut) == a % b);
        CHECK(run("__udivmoddi4_0", a, b, 0) == a / b);
        CHECK(run("__udivmoddi4_2", a, b, sx(kOut)) == a / b);
        const s64 sa = static_cast<s64>(a), sb = static_cast<s64>(b);
        if (!(sa == INT64_MIN && sb == -1)) {
            CHECK(static_cast<s64>(run("__divdi3", a, b)) == sa / sb);
            CHECK(static_cast<s64>(run("__moddi3", a, b)) == sa % sb);
        }
        bulk += 8;
    }
    MESSAGE("64-bit helpers: " << bulk << " results checked against the host");
    report_pairs("64-bit integers");
}

// ======================================================================================================================
// 6. The soft-float doubles against the host's IEEE doubles. Precision found (and asserted): add, sub, mul, div and
//    the conversions never round -- the guard bits are truncated -- so every result is the host's correctly rounded
//    value or the next value toward zero (counted below); comparisons and integer conversions are exact; denormals
//    are flushed to zero.
TEST_CASE("game(libc): soft-float doubles against the host (truncating, within one ulp toward zero)") {
    auto m = machine();
    if (!m) return;
    std::mt19937_64 rng{0xD0Bull};
    auto value = [&]() -> double {
        const u32 k = static_cast<u32>(rng() % 10);
        if (k == 0) return 0.0;
        if (k == 1) return static_cast<double>(static_cast<s64>(rng() % 2001) - 1000);
        const double mant = 1.0 + static_cast<double>(rng() >> 11) / 9007199254740992.0;
        const int e = static_cast<int>(rng() % (k < 6 ? 60 : 600)) - (k < 6 ? 30 : 300);
        return (rng() & 1 ? -1.0 : 1.0) * std::ldexp(mant, e);
    };
    auto toward_zero_ok = [](double g, double h, int& exact) {
        if (dbits(g) == dbits(h) || (g == 0.0 && h == 0.0)) {
            ++exact;
            return true;
        }
        return g == std::nextafter(h, 0.0);
    };
    int n = 0, exact_add = 0, exact_sub = 0, exact_mul = 0, exact_div = 0, exact_f = 0;
    u32 seed = 1;
    for (int i = 0; i < 4000; ++i) {
        const double a = value(), b = value();
        const bool paired = i % 80 == 0;
        auto run = [&](const char* fn, u64 x, u64 y) {
            return paired ? pair_fn(*m, fn, {x, y, 0, 0}, seed++).end.gpr[GPR_V0].u64[0] : call1(*m, fn, {x, y, 0, 0}).v0;
        };
        INFO("a=" << a << " b=" << b);
        CHECK(toward_zero_ok(bitsd(run("dpadd", dbits(a), dbits(b))), a + b, exact_add));
        CHECK(toward_zero_ok(bitsd(run("dpsub", dbits(a), dbits(b))), a - b, exact_sub));
        CHECK(toward_zero_ok(bitsd(run("dpmul", dbits(a), dbits(b))), a * b, exact_mul));
        if (b != 0.0) CHECK(toward_zero_ok(bitsd(run("dpdiv", dbits(a), dbits(b))), a / b, exact_div));
        const s64 c = static_cast<s64>(run("dpcmp", dbits(a), dbits(b)));
        CHECK(c == (a < b ? -1 : a > b ? 1 : 0));
        // conversions
        const s32 iv = static_cast<s32>(rng());
        CHECK(bitsd(run("litodp", sx(static_cast<u32>(iv)), 0)) == static_cast<double>(iv));
        if (std::fabs(a) < 2147483647.0) CHECK(static_cast<s32>(run("dptoli", dbits(a), 0)) == static_cast<s32>(a));
        if (a >= 0 && a < 4294967295.0) CHECK(static_cast<u32>(run("dptoul", dbits(a), 0)) == static_cast<u32>(a));
        const float f = bitsf(static_cast<u32>(paired ? pair_fn(*m, "dptofp", {dbits(a), 0, 0, 0}, seed++).end.fpr[0]
                                                       : call1(*m, "dptofp", {dbits(a), 0, 0, 0}).f0));
        if (std::fabs(a) < 1e38 && std::fabs(a) > 1e-37) {
            const float h = static_cast<float>(a);
            if (fbits(f) == fbits(h)) ++exact_f;
            else CHECK(f == std::nextafter(h, 0.0f));
        }
        const s64 big = static_cast<s64>(rng() >> (rng() % 64)) * (rng() & 1 ? -1 : 1);
        int dummy = 0;
        CHECK(toward_zero_ok(bitsd(run("__floatdidf", static_cast<u64>(big), 0)), static_cast<double>(big), dummy));
        if (std::fabs(a) < 9.2e18) CHECK(static_cast<s64>(run("__fixdfdi", dbits(a), 0)) == static_cast<s64>(a));
        if (a >= 0 && a < 1.8e19) CHECK(run("__fixunsdfdi", dbits(a), 0) == static_cast<u64>(a));
        ++n;
    }
    // the special values the parts routines handle
    const double inf = std::numeric_limits<double>::infinity();
    CHECK(bitsd(call1(*m, "dpadd", {dbits(inf), dbits(1.0), 0, 0}).v0) == inf);
    CHECK(std::isnan(bitsd(call1(*m, "dpsub", {dbits(inf), dbits(inf), 0, 0}).v0)));
    CHECK(std::isnan(bitsd(call1(*m, "dpmul", {dbits(inf), dbits(0.0), 0, 0}).v0)));
    CHECK(bitsd(call1(*m, "dpdiv", {dbits(1.0), dbits(0.0), 0, 0}).v0) == inf);
    CHECK(bitsd(call1(*m, "dpdiv", {dbits(-1.0), dbits(inf), 0, 0}).v0) == 0.0);
    CHECK(static_cast<s64>(call1(*m, "dpcmp", {dbits(std::nan("")), dbits(1.0), 0, 0}).v0) == 1);
    CHECK(bitsd(call1(*m, "dpmul", {dbits(1e-300), dbits(1e-300), 0, 0}).v0) == 0.0);           // underflow: 0
    CHECK(bitsd(call1(*m, "dpadd", {dbits(4.9e-324), dbits(0.0), 0, 0}).v0) == 0.0);            // denormal flushed
    CHECK(static_cast<s32>(call1(*m, "dptoli", {dbits(1e12), 0, 0, 0}).v0) == INT32_MAX);        // saturates
    CHECK(static_cast<s32>(call1(*m, "dptoli", {dbits(-1e12), 0, 0, 0}).v0) == INT32_MIN);
    MESSAGE("soft-float doubles: " << n << " operand pairs; results equal to the host's rounded value: add " << exact_add
                                   << ", sub " << exact_sub << ", mul " << exact_mul << ", div " << exact_div << ", to float "
                                   << exact_f << " (all others exactly one ulp toward zero)");
    report_pairs("soft-float doubles");
}

// ======================================================================================================================
// 7. The pack / unpack layer: the fp-bit records (+0 class, +4 sign, +8 exponent, +12 / +16 fraction).
TEST_CASE("game(libc): soft-float pack and unpack round trips and record layout") {
    auto m = machine();
    if (!m) return;
    std::mt19937_64 rng{0xFACEull};
    u32 seed = 1;
    for (int i = 0; i < 300; ++i) {
        const u64 bits = rng();
        const double d = bitsd(bits);
        w64(*m, kSrc, bits);
        std::memset(m->at(kOut), 0xCC, 24);
        if (i % 10 == 0) pair_fn(*m, "__unpack_d", {sx(kSrc), sx(kOut), 0, 0}, seed++);
        else call1(*m, "__unpack_d", {sx(kSrc), sx(kOut), 0, 0});
        const u32 exp = static_cast<u32>(bits >> 52) & 0x7FF;
        const u64 frac = bits & 0xFFFFFFFFFFFFFull;
        const u32 cls = r32(*m, kOut + libc::parts::kClass);
        CHECK(r32(*m, kOut + libc::parts::kSign) == static_cast<u32>(bits >> 63));
        if (exp == 0) {
            CHECK(cls == static_cast<u32>(libc::parts::kZero));
        } else if (exp == 0x7FF) {
            CHECK(cls == static_cast<u32>(frac == 0 ? libc::parts::kInfinity : (frac >> 51) & 1 ? libc::parts::kQNan : libc::parts::kSNan));
        } else {
            CHECK(cls == static_cast<u32>(libc::parts::kNormal));
            CHECK(static_cast<s32>(r32(*m, kOut + libc::parts::kExp)) == static_cast<s32>(exp) - 1023);
            CHECK(r64(*m, kOut + libc::parts::kFrac) == ((frac << 8) | (1ull << 60)));
            // and back
            const u64 back = i % 10 == 0 ? pair_fn(*m, "__pack_d", {sx(kOut), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]
                                         : call1(*m, "__pack_d", {sx(kOut), 0, 0, 0}).v0;
            CHECK(back == bits);
            (void)d;
        }
        // singles: no Inf / NaN class (exponent 0xFF is an ordinary exponent on the EE)
        const u32 fb = static_cast<u32>(rng());
        w32(*m, kSrc, fb);
        call1(*m, "__unpack_f", {sx(kSrc), sx(kOut), 0, 0});
        const u32 fe = (fb >> 23) & 0xFF;
        CHECK(r32(*m, kOut + libc::parts::kSign) == fb >> 31);
        if (fe == 0) {
            CHECK(r32(*m, kOut) == static_cast<u32>(libc::parts::kZero));
        } else {
            CHECK(r32(*m, kOut) == static_cast<u32>(libc::parts::kNormal));
            CHECK(static_cast<s32>(r32(*m, kOut + libc::parts::kExp)) == static_cast<s32>(fe) - 127);
            CHECK(r32(*m, kOut + libc::parts::kFracF) == (((fb & 0x7FFFFF) << 7) | 0x40000000u));
            // and back: exponent 0xFF is an ordinary exponent both ways
            CHECK(call1(*m, "__pack_f", {sx(kOut), 0, 0, 0}).f0 == fb);
        }
    }
    // __make_fp / __make_dp build the record on their own stack
    hgp::Run r = pair_fn(*m, "__make_fp", {static_cast<u64>(libc::parts::kNormal), 1, sx(static_cast<u32>(-2)), 0x60000000u}, seed++);
    CHECK(bitsf(r.end.fpr[0]) == -0.375f);  // -1.5 * 2^-2
    r = pair_fn(*m, "__make_dp", {static_cast<u64>(libc::parts::kNormal), 0, 10, 0x1800000000000000ull}, seed++);
    CHECK(bitsd(r.end.gpr[GPR_V0].u64[0]) == 1536.0);  // 1.5 * 2^10
    report_pairs("pack / unpack");
}

// ======================================================================================================================
// 8. libm against the host's <cmath>. Precision found (and asserted, 600 inputs per single function, 300 per double):
//    the single-precision functions run on the EE FPU model (no denormals; the R5900 truncates), the double ones on the
//    truncating soft-float helpers. Measured worst error against the correctly rounded host value: sinf, cosf, tanf,
//    acosf, asinf, logf 1 ulp; atanf, atan2f, powf 2 ulps; sqrtf, floorf, fabsf, scalbnf, copysignf exact; acos,
//    log10, log 1 ulp; sqrt, floor, scalbn, copysign exact; 10^n exact below 10^23.
TEST_CASE("game(libc): libm against the host within the precision the PS2 code has") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0x11B4u};
    auto uni = [&](double lo, double hi) { return lo + (hi - lo) * (static_cast<double>(rng()) / 4294967295.0); };
    struct F1 {
        const char* name;
        double lo, hi;
        double (*ref)(double);
        s64 bound;  // ulps
    };
    const F1 singles[] = {
        {"sinf", -10.0, 10.0, [](double x) { return std::sin(x); }, 1},
        {"cosf", -10.0, 10.0, [](double x) { return std::cos(x); }, 1},
        {"tanf", -1.4, 1.4, [](double x) { return std::tan(x); }, 1},
        {"atanf", -50.0, 50.0, [](double x) { return std::atan(x); }, 2},
        {"sqrtf", 0.0, 1e6, [](double x) { return std::sqrt(x); }, 0},
        {"acosf", -1.0, 1.0, [](double x) { return std::acos(x); }, 1},
        {"asinf", -1.0, 1.0, [](double x) { return std::asin(x); }, 1},
        {"logf", 1e-3, 1e6, [](double x) { return std::log(x); }, 1},
        {"floorf", -1e6, 1e6, [](double x) { return std::floor(x); }, 0},
        {"fabsf", -1e6, 1e6, [](double x) { return std::fabs(x); }, 0},
    };
    u32 seed = 1;
    std::string summary;
    for (const F1& f : singles) {
        s64 worst = 0;
        double worst_x = 0;
        for (int i = 0; i < 600; ++i) {
            const float x = static_cast<float>(uni(f.lo, f.hi));
            const u32 got = i % 30 == 0 ? pair_f(*m, f.name, {0, 0, 0, 0}, x, 0.0f, seed++).end.fpr[0]
                                        : call1(*m, f.name, {0, 0, 0, 0}, fbits(x)).f0;
            const float want = static_cast<float>(f.ref(static_cast<double>(x)));
            const float g = bitsf(got);
            s64 e = (std::fabs(want) < 1e-30f && std::fabs(g) < 1e-6f) ? 0 : ulps_f(g, want);
            if (std::fabs(want) < 1e-4f) e = std::fabs(g - want) < 1e-9f ? 0 : e;  // near a zero of the function: absolute error
            if (e > worst) {
                worst = e;
                worst_x = x;
            }
        }
        summary += std::string(" ") + f.name + " " + std::to_string(worst);
        INFO(f.name << " worst " << worst << " ulps at x=" << worst_x);
        CHECK(worst <= f.bound);
    }
    // two-argument singles
    {
        s64 worst_atan2 = 0, worst_pow = 0;
        for (int i = 0; i < 600; ++i) {
            const float y = static_cast<float>(uni(-100, 100)), x = static_cast<float>(uni(-100, 100));
            u32 got = i % 30 == 0 ? pair_f(*m, "atan2f", {0, 0, 0, 0}, y, x, seed++).end.fpr[0] : call1(*m, "atan2f", {0, 0, 0, 0}, fbits(y), fbits(x)).f0;
            worst_atan2 = std::max(worst_atan2, ulps_f(bitsf(got), static_cast<float>(std::atan2(static_cast<double>(y), static_cast<double>(x)))));
            const float b = static_cast<float>(uni(0.01, 20)), p = static_cast<float>(uni(-8, 8));
            got = i % 30 == 0 ? pair_f(*m, "powf", {0, 0, 0, 0}, b, p, seed++).end.fpr[0] : call1(*m, "powf", {0, 0, 0, 0}, fbits(b), fbits(p)).f0;
            const double want = std::pow(static_cast<double>(b), static_cast<double>(p));
            if (want > 1e-30 && want < 1e30) worst_pow = std::max(worst_pow, ulps_f(bitsf(got), static_cast<float>(want)));
        }
        summary += " atan2f " + std::to_string(worst_atan2) + " powf " + std::to_string(worst_pow);
        CHECK(worst_atan2 <= 2);
        CHECK(worst_pow <= 2);
    }
    // copysignf / scalbnf (exact)
    for (int i = 0; i < 100; ++i) {
        const float x = static_cast<float>(uni(-1000, 1000)), y = static_cast<float>(uni(-1, 1));
        CHECK(bitsf(call1(*m, "copysignf", {0, 0, 0, 0}, fbits(x), fbits(y)).f0) == std::copysign(x, y));
        const int k = static_cast<int>(rng() % 40) - 20;
        const u32 got = i % 10 == 0 ? pair_f(*m, "scalbnf", {static_cast<u64>(static_cast<s64>(k)), 0, 0, 0}, x, 0.0f, seed++).end.fpr[0]
                                    : call1(*m, "scalbnf", {static_cast<u64>(static_cast<s64>(k)), 0, 0, 0}, fbits(x)).f0;
        CHECK(bitsf(got) == std::ldexp(x, k));
    }
    // doubles in $a0
    struct D1 {
        const char* name;
        double lo, hi;
        double (*ref)(double);
        s64 bound;
    };
    const D1 doubles[] = {
        {"acos", -1.0, 1.0, [](double x) { return std::acos(x); }, 1},
        {"log10", 1e-6, 1e9, [](double x) { return std::log10(x); }, 1},
        {"__ieee754_log", 1e-6, 1e9, [](double x) { return std::log(x); }, 1},
        {"__ieee754_sqrt", 0.0, 1e12, [](double x) { return std::sqrt(x); }, 0},
        {"floor", -1e9, 1e9, [](double x) { return std::floor(x); }, 0},
    };
    for (const D1& f : doubles) {
        s64 worst = 0;
        for (int i = 0; i < 300; ++i) {
            const double x = uni(f.lo, f.hi);
            const u64 got = i % 30 == 0 ? pair_fn(*m, f.name, {dbits(x), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]
                                        : call1(*m, f.name, {dbits(x), 0, 0, 0}).v0;
            const double want = f.ref(x);
            const s64 e = std::fabs(want) < 1e-12 ? (std::fabs(bitsd(got) - want) < 1e-15 ? 0 : 99) : ulps_d(bitsd(got), want);
            worst = std::max(worst, e);
        }
        summary += std::string(" ") + f.name + " " + std::to_string(worst);
        INFO(f.name << " worst " << worst << " ulps");
        CHECK(worst <= f.bound);
    }
    // scalbn / copysign / _mprec_log10 (exact powers of ten below 10^23)
    for (int i = 0; i < 100; ++i) {
        const double x = uni(-1e6, 1e6);
        const int k = static_cast<int>(rng() % 200) - 100;
        CHECK(bitsd(call1(*m, "scalbn", {dbits(x), static_cast<u64>(static_cast<s64>(k)), 0, 0}).v0) == std::ldexp(x, k));
        CHECK(bitsd(call1(*m, "copysign", {dbits(x), dbits(-x), 0, 0}).v0) == -x);
    }
    double p10 = 1.0;
    for (int n = 0; n < 23; ++n, p10 *= 10.0) CHECK(bitsd(pair_fn(*m, "_mprec_log10", {static_cast<u64>(n), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]) == p10);
    MESSAGE("libm worst errors in ulps (EE singles / soft-float doubles vs host <cmath>):" << summary);
    report_pairs("libm");
}

// ======================================================================================================================
// 9. The mprec bignum leaves of strtod / dtoa on built Bigints (+4 k, +16 word count, +20 words).
TEST_CASE("game(libc): mprec bignum helpers on built Bigints") {
    auto m = machine();
    if (!m) return;
    std::mt19937 rng{0xB16u};
    u32 seed = 1;
    auto put_big = [&](u32 va, const std::vector<u32>& words, u32 k) {
        w32(*m, va + libc::bigint::kNext, 0);
        w32(*m, va + libc::bigint::kK, k);
        w32(*m, va + libc::bigint::kMaxWds, 1u << k);
        w32(*m, va + libc::bigint::kSign, 0);
        w32(*m, va + libc::bigint::kWds, static_cast<u32>(words.size()));
        for (std::size_t i = 0; i < words.size(); ++i) w32(*m, va + libc::bigint::kX + 4 * static_cast<u32>(i), words[i]);
    };
    auto get_big = [&](u32 va) {
        std::vector<u32> w(r32(*m, va + libc::bigint::kWds));
        for (std::size_t i = 0; i < w.size(); ++i) w[i] = r32(*m, va + libc::bigint::kX + 4 * static_cast<u32>(i));
        return w;
    };
    for (int i = 0; i < 60; ++i) {
        // __mcmp
        const std::size_t n = 1 + rng() % 6;
        std::vector<u32> a(n), b;
        for (u32& x : a) x = rng();
        a.back() |= 1;
        b = a;
        const u32 mode = rng() % 3;
        if (mode == 1) b[rng() % n] ^= 1u << (rng() % 32);
        if (mode == 2 && n > 1) b.pop_back();
        put_big(kSrc, a, 3);
        put_big(kAux, b, 3);
        const s32 g = static_cast<s32>(pair_fn(*m, "__mcmp", {sx(kSrc), sx(kAux), 0, 0}, seed++).end.gpr[GPR_V0].u64[0]);
        int want = static_cast<int>(a.size()) - static_cast<int>(b.size());
        if (!want)
            for (std::size_t j = n; j-- > 0;)
                if (a[j] != b[j]) {
                    want = a[j] < b[j] ? -1 : 1;
                    break;
                }
        CHECK(g == want);
        // _hi0bits / _lo0bits
        const u32 x = rng() >> (rng() % 32);
        // (the 32-bit argument sign-extended, as every caller's register holds it: the last test is a 64-bit bgez)
        const s32 hz = static_cast<s32>(pair_fn(*m, "_hi0bits", {sx(x), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]);
        int clz = 0;
        while (clz < 32 && !(x & (0x80000000u >> clz))) ++clz;
        CHECK(hz == clz);
        w32(*m, kOut, x);
        const s32 lz = static_cast<s32>(pair_fn(*m, "_lo0bits", {sx(kOut), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]);
        int ctz = 0;
        while (ctz < 32 && !(x & (1u << ctz))) ++ctz;
        CHECK(lz == ctz);
        CHECK(r32(*m, kOut) == (x ? x >> ctz : 0));
        // quorem: b = q * S + r with r < S (dtoa keeps q <= 9)
        std::vector<u32> S(1 + rng() % 5);
        for (u32& w : S) w = rng();
        S.back() |= 0x10000000u;
        S.back() &= 0x7FFFFFFFu;
        const u32 q = rng() % 10;
        std::vector<u32> r(S.size());
        for (u32& w : r) w = rng();
        r.back() = S.back() > 1 ? rng() % (S.back() - 1) : 0;
        std::vector<u32> bb(S.size() + 1, 0);
        u64 carry = 0;
        for (std::size_t j = 0; j < S.size(); ++j) {
            const u64 t = static_cast<u64>(S[j]) * q + r[j] + carry;
            bb[j] = static_cast<u32>(t);
            carry = t >> 32;
        }
        bb[S.size()] = static_cast<u32>(carry);
        while (bb.size() > 1 && bb.back() == 0) bb.pop_back();
        if (bb.size() > S.size()) continue;  // dtoa never asks for a quotient past one word
        put_big(kSrc, bb, 3);
        put_big(kAux, S, 3);
        const u64 gq = pair_fn(*m, "quorem", {sx(kSrc), sx(kAux), 0, 0}, seed++).end.gpr[GPR_V0].u64[0];
        CHECK(gq == q);
        std::vector<u32> rem = r;
        while (rem.size() > 1 && rem.back() == 0) rem.pop_back();
        std::vector<u32> got = get_big(kSrc);
        while (got.size() > 1 && got.back() == 0) got.pop_back();
        CHECK(got == rem);
    }
    // _Bfree: onto its size class's free list (the _reent's list table at +0x4C)
    const u32 reent = r32(*m, libc::kImpurePtr);
    const u32 table = kOut + 0x100;
    for (u32 k = 0; k < 6; ++k) w32(*m, table + 4 * k, 0x1234560u + k);
    w32(*m, reent + libc::reent::kFreelist, table);
    put_big(kSrc, {1, 2}, 2);
    pair_fn(*m, "_Bfree", {sx(reent), sx(kSrc), 0, 0}, seed++);
    CHECK(r32(*m, table + 8) == kSrc);
    CHECK(r32(*m, kSrc + libc::bigint::kNext) == 0x1234562u);
    pair_fn(*m, "_Bfree", {sx(reent), 0, 0, 0}, seed++);  // NULL: nothing
    // _ulp of normal doubles: 2^(e - 52)
    for (int i = 0; i < 40; ++i) {
        const double x = std::ldexp(1.0 + (rng() % 1000) / 1000.0, static_cast<int>(rng() % 1200) - 600);
        int e = 0;
        std::frexp(x, &e);
        const double want = std::ldexp(1.0, e - 1 - 52);
        CHECK(bitsd(pair_fn(*m, "_ulp", {dbits(x), 0, 0, 0}, seed++).end.gpr[GPR_V0].u64[0]) == want);
    }
    report_pairs("mprec");
}

// ======================================================================================================================
// 10. Small leaves: __sccl's scanset, exponent()'s digits, eofread.
TEST_CASE("game(libc): scanf scanset, printf exponent digits") {
    auto m = machine();
    if (!m) return;
    u32 seed = 1;
    struct Set {
        const char* fmt;       // after the '['
        const char* listed;    // bytes the format names (in the set, or out of it after '^')
        const char* unlisted;  // bytes it does not name
        u32 used;              // the result: fmt + used (the byte after ']', or fmt's NUL)
    };
    const Set sets[] = {{"abc]x", "abc", "dx]", 4}, {"^abc]", "abc", "dx", 5}, {"a-e]", "abcde", "f-", 4},
                        {"-a]", "-a", "b", 3},     {"a-]", "a-", "b", 3},     {"]abc", "]abc", "d", 4},
                        {"z-a]", "z-a", "b", 4},   {"abc", "abc", "d", 3}};
    for (const Set& s : sets) {
        m->put(kSrc, s.fmt);
        std::memset(m->at(kOut), 0xEE, 256);
        const u32 end = static_cast<u32>(pair_fn(*m, "__sccl", {sx(kOut), sx(kSrc), 0, 0}, seed++).end.gpr[GPR_V0].u64[0]);
        INFO("scanset [" << s.fmt);
        const u8 mark = s.fmt[0] == '^' ? 0 : 1;  // the fill is 1 - mark
        for (const char* p = s.listed; *p; ++p) CHECK(m->at(kOut)[static_cast<u8>(*p)] == mark);
        for (const char* p = s.unlisted; *p; ++p) CHECK(m->at(kOut)[static_cast<u8>(*p)] == 1 - mark);
        CHECK(end == kSrc + s.used);
    }
    for (s32 e : {0, 5, -5, 10, -10, 99, 100, -307, 308, 1234}) {
        for (char ch : {'e', 'E'}) {
            std::memset(m->at(kOut), 0, 16);
            const u64 n = pair_fn(*m, "exponent", {sx(kOut), sx(static_cast<u32>(e)), static_cast<u64>(ch), 0}, seed++).end.gpr[GPR_V0].u64[0];
            char want[16];
            std::snprintf(want, sizeof want, "%c%c%02d", ch, e < 0 ? '-' : '+', e < 0 ? -e : e);
            CHECK(m->str(kOut) == want);
            CHECK(n == std::strlen(want));
        }
    }
    CHECK(pair_fn(*m, "eofread", {1, 2, 3, 4}, seed++).end.gpr[GPR_V0].u64[0] == 0);
    report_pairs("scanset / exponent");
}

#else

TEST_CASE("game(libc): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
