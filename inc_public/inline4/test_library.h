
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INLINE4_TEST_LIBRARY_H
#define INLINE4_TEST_LIBRARY_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --

#define TESTLIB_FuncAdd(x,y)		ITest_Library->TESTLIB_FuncAdd(x,y)

// --

#endif
