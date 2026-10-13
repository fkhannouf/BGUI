// --

#include "includes/private/common.h"

// --

uint32 _manager_Obtain( struct LibraryManagerInterface *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
