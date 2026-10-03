
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _main_FuncAdd( struct Test_LibraryIFace *Self, U32 a, U32 b )
{
// struct LibBase *libBase;
struct LibData *data;
U32 retval;
U32 c;

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	MYDEBUG( "Libray : _main_FuncAdd" );

	c = data->LastVal;

	retval = a + b + c;

	data->LastVal = retval;

	return( retval );
}

// --
