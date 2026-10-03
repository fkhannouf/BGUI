
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

#if defined( DO_ERROR ) || defined( DO_INFO ) || defined( DO_DEBUG )

static struct Task *__TASK = NULL;
static struct UtilityIFace *__IU = NULL;

void VARARGS68K _MYDEBUG( U32 lvl UNUSED, STR fmt, ... )
{
struct UtilityIFace *IUtility;
struct ExecIFace *IExec;
struct Task *self;
va_list ap;
STR buf;

	// lvl : 0 = Debug, 1 = Info, 2 = Error

	IExec = (PTR)(*(struct ExecBase **)4)->MainInterface;

	if ( ! __IU )
	{
		PTR base = OpenLibrary( "utility.library", 0 );
		__IU = (PTR) GetInterface( base, "main", 1, NULL );
	}

	IUtility = __IU;

	// ---

	va_start( ap, fmt );

	if ( __IU )
	{
		buf = VASPrintf( fmt, va_getlinearva( ap, PTR ));
	}
	else
	{
		buf = NULL;
	}

	va_end( ap );

	// ---

	Disable();

	self = FindTask(NULL);

	DebugPrintF( "%s%p: %s\n",
		( self != __TASK ) ? "--\n" : "", 
		self,
		( buf ) ? buf : (STR) fmt
	);

	__TASK = self;

	Enable();

	// ---

	if ( buf )
	{
		FreeVec( buf );
	}

	//-
}

#endif

// --
