#include "includes/private/common.h"

uint32 _main_Release( struct Test_LibraryIFace *Self )
{
	Self->Data.RefCount--;

	return( Self->Data.RefCount );
}

// --
