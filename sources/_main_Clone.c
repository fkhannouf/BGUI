#include "includes/private/common.h"

APTR _main_Clone( struct Test_LibraryIFace *Self )
{
//struct LibBase *libBase;
struct Interface *IFace;
struct LibData *data;
int32 error;

	MYDEBUG( "Library : _main_Clone" );

//	libBase = (APTR) Self->Data.LibBase;
	error = TRUE;

	extern const struct TagItem _main_Tags[];
	IFace = MakeInterface( Self->Data.LibBase, _main_Tags );

	if ( ! IFace )
	{
		MYERROR( "Library : Error allocating memory" );
		goto bailout;
	}

	IFace->Data.Flags |= IFLF_CLONED;

	data = (APTR) ( (uint32) IFace - IFace->Data.NegativeSize );

	memset( data, 0, sizeof( struct LibData ));

	// Init/Alloc or Open extra resources here

	// Default
	data->LastVal = 0;

	error = FALSE;

bailout:

	if (( IFace ) && ( error ))
	{
		_main_Expunge( (APTR) IFace );
		IFace = NULL;
	}

	return( IFace );
}

// --
