// --

#include "inc_private/All.h"

// --

U32 _manager_Obtain( struct LibraryManagerInterface *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
