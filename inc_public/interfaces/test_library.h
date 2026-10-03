
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INTERFACES_TEST_LIBRARY_H
#define INTERFACES_TEST_LIBRARY_H

// --

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdint.h>

// --

struct Test_LibraryIFace
{
	struct InterfaceData Data;
	uint32_t					APICALL (*Obtain)(struct Test_LibraryIFace *Self);
	uint32_t					APICALL (*Release)(struct Test_LibraryIFace *Self);
	void						APICALL (*Expunge)(struct Test_LibraryIFace *Self);
	struct Interface *			APICALL (*Clone)(struct Test_LibraryIFace *Self);
	uint32_t					APICALL (*TESTLIB_FuncAdd)(struct Test_LibraryIFace *Self, uint32_t a, uint32_t b);
};

// --

#endif
