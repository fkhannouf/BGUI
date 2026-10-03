
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _manager_Obtain( struct LibraryManagerInterface *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
