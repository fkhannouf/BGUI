// --

#include "includes/private/common.h"

// --

APTR _manager_Expunge( struct LibraryManagerInterface *Self )
{
struct LibBase *libBase;
APTR seglist;

	__DEBUG( "Library : _manager_Expunge" );

	libBase = (APTR) Self->Data.LibBase;

	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		seglist = libBase->lib_SegList;

		Resources_Free( libBase );

		IExec->Remove( (APTR) libBase );

		IExec->DeleteLibrary( (APTR) libBase );
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
