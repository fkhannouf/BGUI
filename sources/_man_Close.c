// --

#include "includes/private/common.h"

// --

APTR _manager_Close( struct LibraryManagerInterface *Self )
{
struct LibBase *libBase;
APTR seglist;

	MYDEBUG( "Library : _manager_Close" );

	seglist = NULL;

	libBase = (APTR) Self->Data.LibBase;

	// Update Library open count
	if ( libBase->lib_Base.lib_OpenCnt )
	{
		libBase->lib_Base.lib_OpenCnt--;
	}

	// Check if we can expunge our self
	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		if ( libBase->lib_Base.lib_Flags & LIBF_DELEXP )
		{
			seglist = _manager_Expunge( Self );
		}
	}

	// Return NULL or SegList
	return( seglist );
}

// --
