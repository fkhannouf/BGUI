// --

#include "inc_private/All.h"

// --

U32 _main_Expunge( struct Test_LibraryIFace *Self )
{
//struct LibBase *libBase;
struct LibData *data;

	MYDEBUG( "Library : _main_Expunge" );

//	libBase = (PTR) Self->Data.LibBase;
	data = (PTR) ( (U32) Self - Self->Data.NegativeSize );

	// Free data obtained in _main_Clone()
	// none in this example

	FreeVec( data );
	
	return( TRUE );
}

// --
