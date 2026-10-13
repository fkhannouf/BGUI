#include "includes/private/common.h"

uint32 _main_Expunge( struct Test_LibraryIFace *Self )
{
//struct LibBase *libBase;
struct LibData *data;

	__DEBUG( "Library : _main_Expunge" );

//	libBase = (APTR) Self->Data.LibBase;
	data = (APTR) ( (uint32) Self - Self->Data.NegativeSize );

	// Free data obtained in _main_Clone()
	// none in this example

	IExec->FreeVec( data );
	
	return( TRUE );
}

// --
