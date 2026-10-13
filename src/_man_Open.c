// --

#include "includes/private/common.h"

// --

APTR _manager_Open( struct LibraryManagerInterface *Self, uint32 version UNUSED )
{
struct LibBase *libBase;

	MYDEBUG( "Library : _manager_Open" );

	libBase = (APTR) Self->Data.LibBase;
	libBase->lib_Base.lib_OpenCnt++;
	libBase->lib_Base.lib_Flags &= ~LIBF_DELEXP;

	return( (APTR) libBase );
}

// --
