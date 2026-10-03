// --

#include "inc_private/All.h"

// --

U32 _main_Release( struct Test_LibraryIFace *Self )
{
	Self->Data.RefCount--;

	return( Self->Data.RefCount );
}

// --
