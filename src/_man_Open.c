
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version UNUSED )
{
struct LibBase *libBase;

	MYDEBUG( "Library : _manager_Open" );

	libBase = (PTR) Self->Data.LibBase;
	libBase->lib_Base.lib_OpenCnt++;
	libBase->lib_Base.lib_Flags &= ~LIBF_DELEXP;

	return( (PTR) libBase );
}

// --
