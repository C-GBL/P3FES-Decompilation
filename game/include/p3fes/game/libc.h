// Slice libc: the C runtime linked into the ELF -- newlib's string / memory / stdlib / locale leaves and its mprec
// bignum leaves, the maths library, and libgcc's 64-bit division and soft-float double helpers (game/src/libc/,
// tests/game/test_libc.cpp). Every function is a p3fes_handgen body on the register ABI (arguments in $a0..$t3 /
// $f12.., the result in $v0 / $f0) with its recompiled entry point fn_<name>_<addr8> as the shim; names are
// symbols/functions.json's (ADR-0009), a [bracketed] role where the name is a sub_.
//
// The records these functions touch, as named offsets (confirmed from the instructions; tools/ours/types/deltas/libc.json):
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libc {

constexpr u32 kImpurePtr = 0x782F30u;  // _impure_ptr: the address of the program's one _reent record
constexpr u32 kCtypeTable = 0x7BE9C8u;  // the <ctype.h> class table the string / strtol code indexes by char (bit 0 upper)
constexpr u32 kBitLength = 0x7C0388u;   // 256 bytes: the number of significant bits of each byte value (division normalisation)
constexpr u32 kNanRecord = 0x7C0488u;   // the unpacked double NaN the parts routines return for Inf - Inf, 0 * Inf, 0 / 0

// newlib's struct _reent (per-thread C library state), the fields this slice reads or writes
namespace reent {
constexpr s32 kErrno = 0x00;       // errno (sub_51F690 [__errno] returns the record's address; strtol stores ERANGE here)
constexpr s32 kCategory = 0x30;    // the last setlocale category
constexpr s32 kLocale = 0x34;      // the last setlocale name
constexpr s32 kFreelist = 0x4C;    // Bigint free lists, one per size class k (_Bfree / _Balloc)
constexpr s32 kStrtokLast = 0x5C;  // strtok's saved position
}  // namespace reent

// dtoa / strtod's Bigint: arbitrary-precision unsigned integer, 32-bit words least significant first
namespace bigint {
constexpr s32 kNext = 0x00;    // free-list link
constexpr s32 kK = 0x04;       // size class: room for 1 << k words
constexpr s32 kMaxWds = 0x08;  // capacity in words
constexpr s32 kSign = 0x0C;
constexpr s32 kWds = 0x10;     // words in use
constexpr s32 kX = 0x14;       // the words
}  // namespace bigint

// newlib's FILE record as std() initialises it
namespace file {
constexpr s32 kP = 0x00;        // current position in the buffer
constexpr s32 kR = 0x04;        // bytes left to read
constexpr s32 kW = 0x08;        // bytes left to write
constexpr s32 kFlags = 0x0C;    // s16
constexpr s32 kFile = 0x0E;     // s16 file number
constexpr s32 kBufBase = 0x10;  // the buffer
constexpr s32 kBufSize = 0x14;
constexpr s32 kLbfSize = 0x18;  // line-buffer size
constexpr s32 kCookie = 0x1C;   // passed to the callbacks (the FILE itself)
constexpr s32 kRead = 0x20;     // callbacks: __sread / __swrite / __sseek / __sclose
constexpr s32 kWrite = 0x24;
constexpr s32 kSeek = 0x28;
constexpr s32 kClose = 0x2C;
constexpr s32 kData = 0x54;     // the owning _reent
}  // namespace file

// the soft-float library's unpacked number (24 bytes for a double, 16 for a single)
namespace parts {
constexpr s32 kClass = 0x00;  // s32: kSNan, kQNan, kZero, kNormal, kInfinity
constexpr s32 kSign = 0x04;   // s32: 0 / 1
constexpr s32 kExp = 0x08;    // s32: unbiased binary exponent
constexpr s32 kFracF = 0x0C;  // u32 (single): fraction, implicit bit at bit 30
constexpr s32 kFrac = 0x10;   // u64 (double): fraction, implicit bit at bit 60, 8 guard bits below the 52 kept
constexpr s32 kSNan = 0, kQNan = 1, kZero = 2, kNormal = 3, kInfinity = 4;
}  // namespace parts

}  // namespace libc

// --- newlib: <string.h>, <stdlib.h>, <locale.h>, the stdio and mprec leaves (game/src/libc/libc_string.cpp, libc_stdlib.cpp)
void abs(EEContext& ctx);  // 0x51E0E0
void atoi(EEContext& ctx);  // 0x51E0F0
void bzero(EEContext& ctx);  // 0x51E118
void quorem(EEContext& ctx);  // 0x51E280
void sub_51F690(EEContext& ctx);  // 0x51F690
void std(EEContext& ctx);  // 0x51F838
void _setlocale_r(EEContext& ctx);  // 0x5204A0
void setlocale(EEContext& ctx);  // 0x520538
void localeconv(EEContext& ctx);  // 0x520560
void _mbtowc_r(EEContext& ctx);  // 0x5210A8
void memchr(EEContext& ctx);  // 0x5210D8
void memcmp(EEContext& ctx);  // 0x5211B8
void memcpy(EEContext& ctx);  // 0x521250
void memmove(EEContext& ctx);  // 0x521300
void memset(EEContext& ctx);  // 0x521408
void _Bfree(EEContext& ctx);  // 0x521620
void _hi0bits(EEContext& ctx);  // 0x521888
void _lo0bits(EEContext& ctx);  // 0x521908
void __mcmp(EEContext& ctx);  // 0x521E70
void _ulp(EEContext& ctx);  // 0x522058
void _b2d(EEContext& ctx);  // 0x522118
void _ratio(EEContext& ctx);  // 0x522440
void _mprec_log10(EEContext& ctx);  // 0x5224F8
void copysign(EEContext& ctx);  // 0x5236F0
void scalbn(EEContext& ctx);  // 0x5237B0
void copysignf(EEContext& ctx);  // 0x523980
void scalbnf(EEContext& ctx);  // 0x5239A8
void eofread(EEContext& ctx);  // 0x523B38
void strcasecmp(EEContext& ctx);  // 0x523DC8
void strcat(EEContext& ctx);  // 0x523E68
void strchr(EEContext& ctx);  // 0x523F98
void strcmp(EEContext& ctx);  // 0x524128
void strcpy(EEContext& ctx);  // 0x524270
void strlen(EEContext& ctx);  // 0x524388
void strncat(EEContext& ctx);  // 0x5244C0
void strncpy(EEContext& ctx);  // 0x524828
void strrchr(EEContext& ctx);  // 0x5249E8
void strstr(EEContext& ctx);  // 0x524A50
void strtok(EEContext& ctx);  // 0x525958
void _strtol_r(EEContext& ctx);  // 0x525A10
void strtol(EEContext& ctx);  // 0x525C50
void _strtoul_r(EEContext& ctx);  // 0x525C80
void strtoul(EEContext& ctx);  // 0x525E98
void exponent(EEContext& ctx);  // 0x5279B8
void __sccl(EEContext& ctx);  // 0x5287D8

// --- libm (game/src/libc/libm.cpp): doubles in one 64-bit GPR ($a0.. / $v0), singles in $f12.. / $f0
void __ieee754_acos(EEContext& ctx);  // 0x528AE0
void __ieee754_log(EEContext& ctx);  // 0x5290A0
void __ieee754_log10(EEContext& ctx);  // 0x529578
void __ieee754_sqrt(EEContext& ctx);  // 0x52A8C8
void __ieee754_acosf(EEContext& ctx);  // 0x52ABD8
void __ieee754_asinf(EEContext& ctx);  // 0x52AFE8
void __ieee754_powf(EEContext& ctx);  // 0x52B800
void __ieee754_rem_pio2f(EEContext& ctx);  // 0x52C000
void __ieee754_sqrtf(EEContext& ctx);  // 0x52C398
void __kernel_cos(EEContext& ctx);  // 0x52C478
void __kernel_rem_pio2(EEContext& ctx);  // 0x52C6D0
void __kernel_sin(EEContext& ctx);  // 0x52D108
void __kernel_cosf(EEContext& ctx);  // 0x52D2D8
void __kernel_rem_pio2f(EEContext& ctx);  // 0x52D428
void __kernel_sinf(EEContext& ctx);  // 0x52DC48
void __kernel_tanf(EEContext& ctx);  // 0x52DD40
void floor(EEContext& ctx);  // 0x52E148
void atanf(EEContext& ctx);  // 0x52E408
void cosf(EEContext& ctx);  // 0x52E6D8
void fabsf(EEContext& ctx);  // 0x52E788
void floorf(EEContext& ctx);  // 0x52E7A0
void sinf(EEContext& ctx);  // 0x52E878
void tanf(EEContext& ctx);  // 0x52E930
void acos(EEContext& ctx);  // 0x52E9A0
void log10(EEContext& ctx);  // 0x52E9B8
void acosf(EEContext& ctx);  // 0x52E9E8
void asinf(EEContext& ctx);  // 0x52EA00
void atan2f(EEContext& ctx);  // 0x52EA18
void logf(EEContext& ctx);  // 0x52EA30
void powf(EEContext& ctx);  // 0x52EA48
void sqrtf(EEContext& ctx);  // 0x52EA60

// --- libgcc (game/src/libc/libgcc_div.cpp, libgcc_float.cpp): 64-bit integers and doubles in one 64-bit GPR each
void __muldi3(EEContext& ctx);  // 0x52EA78
void __floatdidf(EEContext& ctx);  // 0x52EAC8
void __floatdisf(EEContext& ctx);  // 0x52EB60
void __fixunsdfdi(EEContext& ctx);  // 0x52EC28
void __fixdfdi(EEContext& ctx);  // 0x52ED30
void __divdi3(EEContext& ctx);  // 0x52EEB0
void __udivmoddi4(EEContext& ctx);  // 0x52EFD8
void __moddi3(EEContext& ctx);  // 0x52F6A0
void __udivmoddi4_0(EEContext& ctx);  // 0x52F7D0
void __udivdi3(EEContext& ctx);  // 0x52FE98
void __umoddi3(EEContext& ctx);  // 0x530578
void __udivmoddi4_2(EEContext& ctx);  // 0x530598
void __pack_f(EEContext& ctx);  // 0x530C60
void __unpack_f(EEContext& ctx);  // 0x530D18
void __make_fp(EEContext& ctx);  // 0x530D70
void __pack_d(EEContext& ctx);  // 0x530DE0
void __unpack_d(EEContext& ctx);  // 0x530EB8
void _fpadd_parts(EEContext& ctx);  // 0x530F48
void dpadd(EEContext& ctx);  // 0x531170
void dpsub(EEContext& ctx);  // 0x5311C8
void dpmul(EEContext& ctx);  // 0x531230
void _fpmul_parts(EEContext& ctx);  // 0x531288
void dpdiv(EEContext& ctx);  // 0x531480
void _fpdiv_parts(EEContext& ctx);  // 0x5314D8
void __fpcmp_parts_d(EEContext& ctx);  // 0x5315D0
void dpcmp(EEContext& ctx);  // 0x5316D0
void litodp(EEContext& ctx);  // 0x531720
void dptoli(EEContext& ctx);  // 0x5317D0
void __make_dp(EEContext& ctx);  // 0x531870
void dptofp(EEContext& ctx);  // 0x5318A0
void dptoul(EEContext& ctx);  // 0x5318F8

}  // namespace p3fes::game
