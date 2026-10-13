// --

#include "includes/private/common.h"

// --

#if BGUI_LOG_LEVEL > BGUI_LOG_LEVEL_NONE

static struct Task *__TASK = NULL;
static struct UtilityIFace *__IU = NULL;

void VARARGS68K _MYDEBUG( uint32 lvl, STRPTR fmt, ... )
{
struct UtilityIFace *IUtility;
struct ExecIFace *IExec;
struct Task *self;
va_list ap;
STRPTR buf;
STRPTR level_name;

	switch ( lvl )
	{
		case BGUI_LOG_LEVEL_ERROR: level_name = (STRPTR) "ERROR"; break;
		case BGUI_LOG_LEVEL_INFO:  level_name = (STRPTR) "INFO";  break;
		case BGUI_LOG_LEVEL_DEBUG: level_name = (STRPTR) "DEBUG"; break;
		default:                   level_name = (STRPTR) "LOG";   break;
	}

	IExec = (APTR)(*(struct ExecBase **)4)->MainInterface;

	if ( ! __IU )
	{
		APTR base = IExec->OpenLibrary( "utility.library", 0 );
		__IU = (APTR) IExec->GetInterface( base, "main", 1, NULL );
	}

	IUtility = __IU;

	// ---

	va_start( ap, fmt );

	if ( __IU )
	{
		buf = IUtility->VASPrintf( fmt, va_getlinearva( ap, APTR ));
	}
	else
	{
		buf = NULL;
	}

	va_end( ap );

	// ---

	IExec->Disable();

	self = IExec->FindTask(NULL);

	IExec->DebugPrintF( "%s%p [%s]: %s\n",
		( self != __TASK ) ? "--\n" : "", 
		self,
		level_name,
		( buf ) ? buf : (STRPTR) fmt
	);

	__TASK = self;

	IExec->Enable();

	// ---

	if ( buf )
	{
		IExec->FreeVec( buf );
	}

	//-
}

#endif

// --
