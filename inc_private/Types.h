
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_TYPES_H
#define INC_PRIVATE_TYPES_H

// --

#ifndef U8
typedef uint8_t U8;
#endif

#ifndef U16
typedef uint16_t U16;
#endif

#ifndef U32
typedef uint32_t U32;
#endif

#ifndef U64
typedef uint64_t U64;
#endif

#ifndef S8
typedef int8_t S8;
#endif

#ifndef S16
typedef int16_t S16;
#endif

#ifndef S32
typedef int32_t S32;
#endif

#ifndef S64
typedef int64_t S64;
#endif

#ifndef PTR
typedef void* PTR;
#endif

#ifndef STR
typedef char* STR;
#endif

#ifndef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(x) 		((x) < 0 ? -(x) : (x))
#endif

// --
#if defined(__GNUC__)

#ifndef USED
#define USED		__attribute__((used))
#endif

#ifndef UNUSED
#define UNUSED		__attribute__((unused))
#endif

#else

#ifndef USED
#define USED
#endif

#ifndef UNUSED
#define UNUSED
#endif

#endif
// --

#endif
