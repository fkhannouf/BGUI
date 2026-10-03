
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>

#include <proto/test_library.h>

#include <stdio.h>

// --

struct Library *			Test_LibraryBase	= NULL;
struct Test_LibraryIFace *	ITest_Library		= NULL;

// --

static int myInit( void );
static void myFree( void );

// --

int main( void )
{
uint32_t val;

	if ( ! myInit())
	{
		goto bailout;
	}

	val = ITest_Library->TESTLIB_FuncAdd( 1, 2 );

	// Should be : 0 + 1 + 2 == 3

	if ( val != 3 )
	{
		printf( "Incorrect value %lu expected 3\n", val );
	}
	else
	{
		printf( "Correct value %lu\n", val );
	}

	val = ITest_Library->TESTLIB_FuncAdd( 4, 5 );

	// Should be : 3 + 4 + 5 == 12

	if ( val != 12 )
	{
		printf( "Incorrect value %lu expected 12\n", val );
	}
	else
	{
		printf( "Correct value %lu\n", val );
	}

	printf( "Test Library Okay\n" );

bailout:

	myFree();

	return( 0 );
}


// -- 

static int myInit( void )
{
int retval;

	retval = FALSE;
	Test_LibraryBase = IExec->OpenLibrary( "test_library.library", 1 );

	if ( ! Test_LibraryBase )
	{
		printf( "Error opening Test library v1\n" );
		goto bailout;
	}

	ITest_Library = (APTR) IExec->GetInterface( Test_LibraryBase, "main", 1, NULL );

	if ( ! ITest_Library )
	{
		printf( "Error opening Test interface v1\n" );
		goto bailout;
	}

	retval = TRUE;

bailout:

	return( retval );
}

// -- 

static void myFree( void )
{
	if ( ITest_Library )
	{
		IExec->DropInterface( (APTR) ITest_Library );
	}

	if ( Test_LibraryBase )
	{
		IExec->CloseLibrary( Test_LibraryBase );
	}
}

// --