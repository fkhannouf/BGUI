
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _manager_Expunge( struct LibraryManagerInterface *Self )
{
struct LibBase *libBase;
PTR seglist;

	MYDEBUG( "Library : _manager_Expunge" );

	libBase = (PTR) Self->Data.LibBase;

	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		seglist = libBase->lib_SegList;

		Resources_Free( libBase );

		Remove( (PTR) libBase );

		DeleteLibrary( (PTR) libBase );
		libBase = NULL;
	}
	else
	{
		libBase->lib_Base.lib_Flags |= LIBF_DELEXP;
		seglist = NULL;
	}

	// Return NULL or SegList
	return( seglist );
}

// --
