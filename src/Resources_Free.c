#include "includes/private/common.h"

void Resources_Free( struct LibBase *libBase UNUSED )
{
	MYDEBUG( "Library : Resources_Free" );

	// --
	// Free Resources last
	myCloseResources();

// bailout:

	return;
}

// --
