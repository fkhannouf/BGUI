#include "includes/private/common.h"

int32 Resources_Init( struct LibBase *libBase UNUSED )
{
int32 retval;

	MYDEBUG( "Library : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first
	//
	if ( ! myOpenResources( INT_MAX ))
	{
		MYERROR( "Library : myOpenResources() failed" );
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
