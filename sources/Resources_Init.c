#include "includes/private/common.h"

int32 Resources_Init( struct LibBase *libBase UNUSED )
{
int32 retval;

	__DEBUG( "Library : Resources_Init" );

	retval = FALSE;

	// --
	// Open Resources first
	//
	if ( ! myOpenResources( INT_MAX ))
	{
		__ERROR( "Library : myOpenResources() failed" );
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	return( retval );
}

// --
