
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef LIBRARIES_TEST_LIBRARY_H
#define LIBRARIES_TEST_LIBRARY_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --
// Our Test Library defines/structs

#define TESTLIB_SomeValue	123

struct TESTLIB_Struct
{
	int	dummy;
};

// --

#endif
