#include "includes/private/common.h"

uint32 _main_FuncAdd( struct Test_LibraryIFace *Self, uint32 a, uint32 b )
{
// struct LibBase *libBase;
struct LibData *data;
uint32 retval;
uint32 c;

//	libBase = (APTR) Self->Data.LibBase;
	data = (APTR) ( (uint32) Self - Self->Data.NegativeSize );

	__DEBUG( "Libray : _main_FuncAdd" );

	c = data->LastVal;

	retval = a + b + c;

	data->LastVal = retval;

	return( retval );
}

// --
