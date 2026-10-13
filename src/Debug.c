// --

#include "includes/private/common.h"

// --

#if defined( DO_ERROR ) || defined( DO_INFO ) || defined( DO_DEBUG )

static struct Task *__TASK = NULL;
static struct UtilityIFace *__IU = NULL;

void VARARGS68K _MYDEBUG( uint32 lvl UNUSED, STRPTR fmt, ... )
{
struct UtilityIFace *IUtility;
struct ExecIFace *IExec;
struct Task *self;
va_list ap;
STRPTR buf;

	// lvl : 0 = Debug, 1 = Info, 2 = Error

	IExec = (APTR)(*(struct ExecBase **)4)->MainInterface;

	if ( ! __IU )
	{
		APTR base = OpenLibrary( "utility.library", 0 );
		__IU = (APTR) GetInterface( base, "main", 1, NULL );
	}

	IUtility = __IU;

	// ---

	va_start( ap, fmt );

	if ( __IU )
	{
		buf = VASPrintf( fmt, va_getlinearva( ap, APTR ));
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
		( buf ) ? buf : (STRPTR) fmt
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
