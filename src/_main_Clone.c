
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

PTR _main_Clone( struct Test_LibraryIFace *Self )
{
//struct LibBase *libBase;
struct Interface *IFace;
struct LibData *data;
S32 error;

	MYDEBUG( "Library : _main_Clone" );

//	libBase = (PTR) Self->Data.LibBase;
	error = TRUE;

	extern const struct TagItem _main_Tags[];
	IFace = MakeInterface( Self->Data.LibBase, _main_Tags );

	if ( ! IFace )
	{
		MYERROR( "Library : Error allocating memory" );
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	data = (PTR) ( (U32) IFace - IFace->Data.NegativeSize );

	memset( data, 0, sizeof( struct LibData ));

	// Init/Alloc or Open extra resources here

	// Default
	data->LastVal = 0;

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		_main_Expunge( (PTR) IFace );
		IFace = NULL;
	}

	return( IFace );
}

// --
